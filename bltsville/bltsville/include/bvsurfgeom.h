/*
 * bvsurfgeom.h
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

#ifndef BVSURFGEOM_H
#define BVSURFGEOM_H

/*
 * bvsurfdesc - This structure specifies the way a buffer should be used in a
 * 2-D context.
 */

struct bvsurfgeom {
	unsigned int structsize;	/* used to identify struct version */
	enum ocdformat format;		/* color format of surface */
	unsigned int width;		/* width of the surface in pixels */
	unsigned int height;		/* height of the surface in lines */
	int orientation;		/* angle of the surface in degrees
					   (multiple of 90 only) */
	long virtstride;		/* distance from one pixel to the
					   pixel immediately below it in
					   virtual space */
	enum ocdformat paletteformat;	/* format of palette */
	void *palette;			/* array of palette entries of
					   paletteformat; only valid when
					   format includes BVFMTDEF_LUT;
					   number of entries is 2^bpp. */
};

#endif /* BVSURFGEOM_H */
