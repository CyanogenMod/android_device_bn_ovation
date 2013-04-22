/*
 * bvcache.h
 *
 * Copyright (C) 2012 Texas Instruments, Inc.
 *
 * This file is part of BLTsville, an open application programming interface
 * (API) for accessing 2-D software or hardware implementations.
 *
 * This work is licensed under the Creative Commons Attribution-NoDerivs 3.0
 * Unported License. To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nd/3.0/ or send a letter to
 * Creative Commons, 444 Castro Street, Suite 900, Mountain View, California,
 * 94041, USA.
 */

#ifndef BVCACHE_H_
#define BVCACHE_H_

/* Forward declarations */
struct bvbuffdesc;
struct bvsurfgeom;
struct bvrect;

/*
 * This defines which cache operation the user intends to use
 * BVCACHE_CPU_TO_DEVICE = clean
 * BVCACHE_CPU_FROM_DEVICE = invalidate
 * BVCACHE_BIDIRECTIONAL = flush
 */
enum bvcacheop {
	BVCACHE_BIDIRECTIONAL = 0,
	BVCACHE_CPU_TO_DEVICE = 1,
	BVCACHE_CPU_FROM_DEVICE = 2,
	BVCACHE_RESERVED3 = 3,
};

struct bvcopparams {
	unsigned int structsize;	/* used to identify struct version */
	struct bvbuffdesc *desc;
	struct bvsurfgeom *geom;
	struct bvrect     *rect;
	enum bvcacheop cacheop;
};

#endif /* BVCACHE_H_ */
