/*	$FreeBSD: soc2013/dpl/head/contrib/ipfilter/lib/fill6bits.c 170311 2007-06-04 02:54:36Z darrenr $	*/

/*
 * Copyright (C) 2000-2002 by Darren Reed.
 *
 * See the IPFILTER.LICENCE file for details on licencing.
 *
 * $Id: fill6bits.c,v 1.5.4.1 2006/06/16 17:20:58 darrenr Exp $
 */

#include "ipf.h"


void fill6bits(bits, msk)
int bits;
u_int *msk;
{
	if (bits == 0) {
		msk[0] = 0;
		msk[1] = 0;
		msk[2] = 0;
		msk[3] = 0;
		return;
	}

	msk[0] = 0xffffffff;
	msk[1] = 0xffffffff;
	msk[2] = 0xffffffff;
	msk[3] = 0xffffffff;

	if (bits == 128)
		return;
	if (bits > 96) {
		msk[3] = htonl(msk[3] << (128 - bits));
	} else if (bits > 64) {
		msk[3] = 0;
		msk[2] = htonl(msk[2] << (96 - bits));
	} else if (bits > 32) {
		msk[3] = 0;
		msk[2] = 0;
		msk[1] = htonl(msk[1] << (64 - bits));
	} else {
		msk[3] = 0;
		msk[2] = 0;
		msk[1] = 0;
		msk[0] = htonl(msk[0] << (32 - bits));
	}
}
