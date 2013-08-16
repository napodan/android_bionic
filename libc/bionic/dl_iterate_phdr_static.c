/*
 * Copyright (C) 2006 The Android Open Source Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <elf.h>
#include <sys/types.h>
#include <link.h>

/* Dynamic binaries get this from the dynamic linker (system/linker), which
 * we don't pull in for static bins. We also don't have a list of so's to
 * iterate over, since there's really only a single monolithic blob of
 * code/data.
 *
 * All we need to do is to find where the executable is in memory, and grab the
 * phdr and phnum from there.
 */

/* ld provides this to us in the default link script */
extern void *__executable_start;

int
dl_iterate_phdr(int (*cb)(struct dl_phdr_info *info, size_t size, void *data),
                void *data)
{
    struct dl_phdr_info dl_info;
    Elf32_Ehdr *ehdr = (Elf32_Ehdr *) &__executable_start;
    Elf32_Phdr *phdr = (Elf32_Phdr *)((unsigned long)ehdr + ehdr->e_phoff);

    /* TODO: again, copied from linker.c. Find a better home for this
     * later. */
    if (ehdr->e_ident[EI_MAG0] != ELFMAG0) return -1;
    if (ehdr->e_ident[EI_MAG1] != ELFMAG1) return -1;
    if (ehdr->e_ident[EI_MAG2] != ELFMAG2) return -1;
    if (ehdr->e_ident[EI_MAG3] != ELFMAG3) return -1;

    dl_info.dlpi_addr = 0;
    dl_info.dlpi_name = NULL;
    dl_info.dlpi_phdr = phdr;
    dl_info.dlpi_phnum = ehdr->e_phnum;
    return cb(&dl_info, sizeof (struct dl_phdr_info), data);
}
