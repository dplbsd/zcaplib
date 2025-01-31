/*
 * Copyright (c) 1993 Martin Birgmeier
 * All rights reserved.
 *
 * You may redistribute unmodified or modified versions of this source
 * code provided that the above copyright notice and this and the
 * following conditions are retained.
 *
 * This software is provided ``as is'', and comes with no warranties
 * of any kind. I shall in no event be liable for anything that happens
 * to anyone/anything when using this software.
 */

#include <sys/cdefs.h>
__FBSDID("$FreeBSD: soc2013/dpl/head/lib/libc/gen/jrand48.c 93029 2002-03-22 21:53:29Z obrien $");

#include "rand48.h"

long
jrand48(unsigned short xseed[3])
{
	_dorand48(xseed);
	return ((long) xseed[2] << 16) + (long) xseed[1];
}
