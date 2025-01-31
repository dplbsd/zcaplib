/* $NetBSD: arith.h,v 1.1 2006/01/25 15:33:28 kleink Exp $ */
/* $FreeBSD: soc2013/dpl/head/lib/libc/mips/gdtoa/arith.h 178623 2008-04-26 12:08:02Z imp $ */

#include <machine/endian.h>

#if BYTE_ORDER == BIG_ENDIAN
#define IEEE_BIG_ENDIAN
#else
#define IEEE_LITTLE_ENDIAN
#endif
