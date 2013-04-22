/*
 * Copyright (c) 2012,
 * Texas Instruments, Inc. and Vivante Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Texas Instruments, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL TEXAS INSTRUMENTS, INC. BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef GCMAIN_H
#define GCMAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <gcx.h>
#include <gcioctl.h>
#include <bltsville.h>
#include <bvinternal.h>
#include <bverror.h>

#define GC_DEV_NAME	"gc2duser"


/*******************************************************************************
 * Miscellaneous macros.
 */

/* Not present in userspace bltsville headers */
#define BVAT_PHYSDESC     0xDEADBEEF

#define gcalloc(type, size) \
	(type *) malloc(size)

#define gcfree(ptr) \
	free(ptr)

#define max(x, y) (x > y ? x : y)
#define min(x, y) (x < y ? x : y)

#define EXPORT_SYMBOL(sym)

#define gc_debug_blt(...)

typedef int64_t s64;
typedef uint64_t u64;

#define div_u64(x, y) ((x) / (y))
#define div_s64(x, y) ((x) / (y))
#define div64_u64(x, y) ((x) / (y))
#define div64_s64(x, y) ((x) / (y))

#define PAGE_SHIFT              12
#define PAGE_SIZE               (1 << PAGE_SHIFT)
#define PAGE_MASK               (~(PAGE_SIZE-1))

/*******************************************************************************
 * Not defined in bltsville userspace headers.
 */

struct bvphysdesc {
	unsigned int structsize;	/* used to identify struct version */
	unsigned long pagesize;		/* page size in bytes */
	unsigned long *pagearray;	/* array of physical pages */
	unsigned int pagecount;		/* number of pages in the pagearray */
	unsigned long pageoffset;	/* page offset in bytes */
};


/*******************************************************************************
 * IOCTL wrappers.
 */

void gc_getcaps_wrapper(struct gcicaps *gcicaps);
void gc_map_wrapper(struct gcimap *gcimap);
void gc_unmap_wrapper(struct gcimap *gcimap);
void gc_commit_wrapper(struct gcicommit *gcicommit);
void gc_callback_wrapper(struct gcicallbackarm *gcicallbackarm);


/*******************************************************************************
 * Surface allocation.
 */
enum bverror allocate_surface(struct bvbuffdesc **bvbuffdesc,
			      void **buffer,
			      unsigned int size);

void free_surface(struct bvbuffdesc *bvbuffdesc,
		  void *buffer);


/*******************************************************************************
 * Floating point conversions.
 */

unsigned char gcfp2norm8(float value);


/*******************************************************************************
 * Cache operation wrapper.
 */

enum bverror gcbvcacheop(int count, struct c2dmrgn rgn[],
			 enum bvcacheop cacheop);


/*******************************************************************************
 * BLTsville API.
 */

void bv_init(void);
void bv_exit(void);

enum bverror bv_map(struct bvbuffdesc *buffdesc);
enum bverror bv_unmap(struct bvbuffdesc *buffdesc);
enum bverror bv_blt(struct bvbltparams *bltparams);
enum bverror bv_cache(struct bvcopparams *copparams);

#endif
