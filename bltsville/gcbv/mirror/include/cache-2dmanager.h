/*
 * Copyright(c) 2012,
 * Texas Instruments, Inc. and Vivante Corporation.
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Vivante Corporation nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef CACHE_2DMANAGER_H_
#define CACHE_2DMANAGER_H_

/* The value below only applies to OMAP4 */
#define L1CACHE_SIZE 32768
#define L2CACHE_SIZE 1048576

#define L1THRESHOLD L1CACHE_SIZE
#define L2THRESHOLD L2CACHE_SIZE

struct c2dmrgn {
	char *start;	/* addr of upper left of rect */
	size_t span;	/* bytes to be operated on per line */
	size_t lines;	/* lines to be operated on */
	long stride;	/* bytes per line */
};

/*
 *	c2dm_l1cache(count, rgns, dir)
 *
 *	L1 Cache operations in 2D
 *
 *	- count  - number of regions
 *	- rgns   - array of regions
 *	- dir	 - cache operation direction
 *
 */
void c2dm_l1cache(int count, struct c2dmrgn rgns[], int dir);

/*
 *	c2dm_l2cache(count, rgns, dir)
 *
 *	L2 Cache operations in 2D
 *
 *	- count  - number of regions
 *	- rgns   - array of regions
 *	- dir	 - cache operation direction
 *
 */
void c2dm_l2cache(int count, struct c2dmrgn rgns[], int dir);


#endif /* CACHE_2DMANAGER_H_ */
