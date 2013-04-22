/*
 * bvfilter.h
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
 * This file defines the types of shared filters available and the associated
 * parameters.
 *
 * To extend the list of filters, create a file containing additional
 * enumerations to be added to enum bvfilter below.  Then #define
 * BVFILTER_EXTERNAL_INCLUDE as the name of that file before including
 * this file in your project.  Parameters need to be in a different file.
 */

#ifndef BVFILTER_H
#define BVFILTER_H

/*
 * bvfilter is an enumeration used to designate the type of filter being used.
 */
enum bvfiltertype {
	BVFILTER_DUMMY
	/* TBD */

#ifdef BVFILTER_EXTERNAL_INCLUDE
#include BVFILTER_EXTERNAL_INCLUDE
#endif
};

/*
 * bvfilterop contains the filter type and a pointer to the associated
 * parameters when the BVFLAG_FILTER operation is specified in
 * bvbltparams.flags.
 */
struct bvfilter {
	enum bvfiltertype filter;
	void *params;
};

#endif /* BVFILTER_H */
