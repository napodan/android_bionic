/*
 * Copyright (C) 2012 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


/*
 * Ugly inclusion of C file so that bionic specific #defines configure
 * dlmalloc.
 */
#include "../upstream-dlmalloc/malloc.c"


/*
  malloc_walk_free_pages(handler, harg)

  Calls the provided handler on each free region in the heap.  The
  memory between start and end are guaranteed not to contain any
  important data, so the handler is free to alter the contents
  in any way.  This can be used to advise the OS that large free
  regions may be swapped out.

  The value in harg will be passed to each call of the handler.
 */
void dlmalloc_walk_free_pages(void(*)(void*, void*, void*), void*);

/*
  malloc_walk_heap(handler, harg)

  Calls the provided handler on each object or free region in the
  heap.  The handler will receive the chunk pointer and length, the
  object pointer and length, and the value in harg on each call.
 */
void dlmalloc_walk_heap(void(*)(const void*, size_t,
                                const void*, size_t, void*),
                        void*);

#if MSPACES

#if ANDROID /* Added for Android, not part of dlmalloc as released */
/*
  mspace_merge_objects will merge allocated memory mema and memb
  together, provided memb immediately follows mema.  It is roughly as
  if memb has been freed and mema has been realloced to a larger size.
  On successfully merging, mema will be returned. If either argument
  is null or memb does not immediately follow mema, null will be
  returned.

  Both mema and memb should have been previously allocated using
  malloc or a related routine such as realloc. If either mema or memb
  was not malloced or was previously freed, the result is undefined,
  but like mspace_free, the default is to abort the program.
*/
void* mspace_merge_objects(mspace msp, void* mema, void* memb);
#endif /* ANDROID */

#endif /* MSPACES */

#if MSPACES && ONLY_MSPACES
void mspace_walk_free_pages(mspace msp,
    void(*handler)(void *start, void *end, void *arg), void *harg)
{
  mstate m = (mstate)msp;
  if (!ok_magic(m)) {
    USAGE_ERROR_ACTION(m,m);
    return;
  }
#else
void dlmalloc_walk_free_pages(void(*handler)(void *start, void *end, void *arg),
    void *harg)
{
  mstate m = (mstate)gm;
#endif
  if (!PREACTION(m)) {
    if (is_initialized(m)) {
      msegmentptr s = &m->seg;
      while (s != 0) {
        mchunkptr p = align_as_chunk(s->base);
        while (segment_holds(s, p) &&
               p != m->top && p->head != FENCEPOST_HEAD) {
          void *chunkptr, *userptr;
          size_t chunklen, userlen;
          chunkptr = p;
          chunklen = chunksize(p);
          if (!cinuse(p)) {
            void *start;
            if (is_small(chunklen)) {
              start = (void *)(p + 1);
            }
            else {
              start = (void *)((tchunkptr)p + 1);
            }
            handler(start, next_chunk(p), harg);
          }
          p = next_chunk(p);
        }
        if (p == m->top) {
          handler((void *)(p + 1), next_chunk(p), harg);
        }
        s = s->next;
      }
    }
    POSTACTION(m);
  }
}


#if MSPACES && ONLY_MSPACES
void mspace_walk_heap(mspace msp,
                      void(*handler)(const void *chunkptr, size_t chunklen,
                                     const void *userptr, size_t userlen,
                                     void *arg),
                      void *harg)
{
  msegmentptr s;
  mstate m = (mstate)msp;
  if (!ok_magic(m)) {
    USAGE_ERROR_ACTION(m,m);
    return;
  }
#else
void dlmalloc_walk_heap(void(*handler)(const void *chunkptr, size_t chunklen,
                                       const void *userptr, size_t userlen,
                                       void *arg),
                        void *harg)
{
  msegmentptr s;
  mstate m = (mstate)gm;
#endif

  s = &m->seg;
  while (s != 0) {
    mchunkptr p = align_as_chunk(s->base);
    while (segment_holds(s, p) &&
           p != m->top && p->head != FENCEPOST_HEAD) {
      void *chunkptr, *userptr;
      size_t chunklen, userlen;
      chunkptr = p;
      chunklen = chunksize(p);
      if (cinuse(p)) {
        userptr = chunk2mem(p);
        userlen = chunklen - overhead_for(p);
      }
      else {
        userptr = NULL;
        userlen = 0;
      }
      handler(chunkptr, chunklen, userptr, userlen, harg);
      p = next_chunk(p);
    }
    if (p == m->top) {
      /* The top chunk is just a big free chunk for our purposes.
       */
      handler(m->top, m->topsize, NULL, 0, harg);
    }
    s = s->next;
  }
}

#if MSPACES
#if ANDROID
void* mspace_merge_objects(mspace msp, void* mema, void* memb)
{
  /* PREACTION/POSTACTION aren't necessary because we are only
     modifying fields of inuse chunks owned by the current thread, in
     which case no other malloc operations can touch them.
   */
  if (mema == NULL || memb == NULL) {
    return NULL;
  }
  mchunkptr pa = mem2chunk(mema);
  mchunkptr pb = mem2chunk(memb);

#if FOOTERS
  mstate fm = get_mstate_for(pa);
#else /* FOOTERS */
  mstate fm = (mstate)msp;
#endif /* FOOTERS */
  if (!ok_magic(fm)) {
    USAGE_ERROR_ACTION(fm, pa);
    return NULL;
  }
  check_inuse_chunk(fm, pa);
  if (RTCHECK(ok_address(fm, pa) && ok_inuse(pa))) {
    if (next_chunk(pa) != pb) {
      /* Since pb may not be in fm, we can't check ok_address(fm, pb);
         since ok_inuse(pb) would be unsafe before an address check,
         return NULL rather than invoke USAGE_ERROR_ACTION if pb is not
         in use or is a bogus address.
       */
      return NULL;
    }
    /* Since b follows a, they share the mspace. */
#if FOOTERS
    assert(fm == get_mstate_for(pb));
#endif /* FOOTERS */
    check_inuse_chunk(fm, pb);
    if (RTCHECK(ok_address(fm, pb) && ok_inuse(pb))) {
      size_t sz = chunksize(pb);
      pa->head += sz;
      /* Make sure pa still passes. */
      check_inuse_chunk(fm, pa);
      return mema;
    }
    else {
      USAGE_ERROR_ACTION(fm, pb);
      return NULL;
    }
  }
  else {
    USAGE_ERROR_ACTION(fm, pa);
    return NULL;
  }
}
#endif /* ANDROID */
#endif /* MSPACES */
