/*
 * bventry.h
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

#ifndef BVENTRY_H
#define BVENTRY_H

/* Forward declarations */
struct bvbuffdesc;
struct bvbltparams;
struct bvcopparams;
/*
 * bv_*() - These are the API calls for BLTsville.  The client needs to
 * import these from the shared library.
 */
typedef enum bverror (*BVFN_MAP)(struct bvbuffdesc *buffdesc);
typedef enum bverror (*BVFN_BLT)(struct bvbltparams *bltparms);
typedef enum bverror (*BVFN_UNMAP)(struct bvbuffdesc *buffdesc);
typedef enum bverror (*BVFN_CACHE)(struct bvcopparams *copparams);

#endif /* BVENTRY_H */
