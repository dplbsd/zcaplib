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
__FBSDID("$FreeBSD: soc2013/dpl/head/lib/libc/gen/drand48.c 93029 2002-03-22 21:53:29Z obrien $");

#include "rand48.h"

extern unsigned short _rand48_seed[3];

double
drand48(void)
{
	return erand48(_rand48_seed);
}
