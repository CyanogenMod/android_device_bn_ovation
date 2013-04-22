/*
 * bvbuffdesc.h
 *
 * Copyright (C) 2011 Texas Instruments, Inc.
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

#ifndef BVBUFFDESC_H
#define BVBUFFDESC_H

/*
 * bvbuffmap - This is a private structure used by BLTsville
 * implementations to manage resources associated with a buffer.  A pointer
 * to this is returned from bv_map() and used in subsequent bv_blt() and
 * bv_unmap() calls.
 */
struct bvbuffmap;

#define BVATDEF_VENDOR_SHIFT	24
#define BVATDEF_VENDOR_MASK	(0xFF << BVATDEF_VENDOR_SHIFT)

/* Common aux type */
#define BVATDEF_VENDOR_ALL	(0x00 << BVATDEF_VENDOR_SHIFT)

/* Texas Instruments, Inc. */
#define BVATDEF_VENDOR_TI	(0x01 << BVATDEF_VENDOR_SHIFT)

enum bvauxtype {
	BVAT_NONE = 0,	/* auxptr not used */
	BVAT_reserved1 = /* reserved */
		BVATDEF_VENDOR_ALL + 1,
	BVAT_reserved2 = /* reserved */
		BVATDEF_VENDOR_ALL + 2,
#ifdef BVAT_EXTERNAL_INCLUDE
#include BVAT_EXTERNAL_INCLUDE
#endif
};

/*
 * bvbuffdesc - This structure is used to specify the buffer parameters
 * in a call to bv_map().
 */
struct bvbuffdesc {
	unsigned int structsize;	/* used to identify struct version */
	void *virtaddr;			/* virtual ptr to start of buffer */
	unsigned long length;		/* length of the buffer in bytes */
	struct bvbuffmap *map;		/* resource(s) associated w/buffer */
	enum bvauxtype auxtype;		/* type of auxptr */
	void *auxptr;			/* additional buffer description data;
					type depends on auxtype */
};

#endif /* BVBUFFDESC_H */
