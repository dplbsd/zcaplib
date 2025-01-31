/*
 * MD header for contrib/gdtoa
 *
 * $FreeBSD: soc2013/dpl/head/lib/libc/mips/arith.h 178623 2008-04-26 12:08:02Z imp $
 */

/*
 * NOTE: The definitions in this file must be correct or strtod(3) and
 * floating point formats in printf(3) will break!  The file can be
 * generated by running contrib/gdtoa/arithchk.c on the target
 * architecture.  See contrib/gdtoa/gdtoaimp.h for details.
 */
#include <machine/endian.h>

#if BYTE_ORDER == BIG_ENDIAN
#define IEEE_MC68k
#define Arith_Kind_ASL 2
#define Double_Align
#else
/* TODO: Generate these values on a LE machine */
/* Current values were stolen from ia64 except the
 * Xpointer define.
 */
#define IEEE_8087
#define Arith_Kind_ASL 1
#define Long int
#define Intcast (int)(long)
#define Double_Align
#endif
