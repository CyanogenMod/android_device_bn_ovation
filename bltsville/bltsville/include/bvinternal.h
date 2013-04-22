/*
 * bvinternal.h
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

/*
 * This file contains definitions used by implementations of BLTsville
 * 2-D libraries.  It should not be used by clients.
 */

#ifndef BVINTERNAL_H
#define BVINTENRAL_H

/*
 * bvbuffmap - The bvbuffmap structure is used to track resources
 * associated with a buffer, such as a h/w MMU entry.  The implementations
 * add bvbuffmap objects when they allocate the resources.  Then when a
 * buffer is accessed, the implementations can regain access to the
 * associated resources.  The implementations allocate and populate this
 * structure when a bv_map() call is made.  It is used in subsequent
 * bv_blt() and bv_unmap() calls.  The latter frees the associated resource
 * and the structure (if applicable).  Note that a given resource might be
 * used by more than one implementation.
 */
struct bvbuffmap {
	unsigned int structsize; /* used to ID structure ver */

	/* function to unmap this resource */
	BVFN_UNMAP bv_unmap;

	unsigned long handle;	 /* resource-specific info */

	/* pointer to next resource mapping structure */
	struct bvbuffmap *nextmap;
};

#endif /* BVINTERNAL_H */
