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

#ifndef LIBC_BIONIC_DLMALLOC_H_
#define LIBC_BIONIC_DLMALLOC_H_


/* Include the proper definitions. */
#include "../upstream-dlmalloc/malloc.h"

/* OXYGEN these methods are still needed in libcutils and libdvm */

#ifdef __cplusplus
extern "C" {
#endif

#if MSPACES
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

/*
  mspace_max_allowed_footprint() returns the number of bytes that
  this space is allowed to obtain from the system. See
  malloc_max_allowed_footprint() for a more in-depth description.

  This function is only available if dlmalloc.c was compiled
  with USE_MAX_ALLOWED_FOOTPRINT set.
*/
size_t mspace_max_allowed_footprint(mspace msp);

/*
  mspace_set_max_allowed_footprint() sets the maximum number of
  bytes (rounded up to a page) that this space is allowed to
  obtain from the system.  See malloc_set_max_allowed_footprint()
  for a more in-depth description.

  This function is only available if dlmalloc.c was compiled
  with USE_MAX_ALLOWED_FOOTPRINT set.
*/
void mspace_set_max_allowed_footprint(mspace msp, size_t bytes);

#endif  /* MSPACES */

#ifdef __cplusplus
};  /* end of extern "C" */
#endif

#endif  // LIBC_BIONIC_DLMALLOC_H_
