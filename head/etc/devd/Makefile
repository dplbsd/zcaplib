# $FreeBSD: soc2013/dpl/head/etc/devd/Makefile 226729 2011-10-16 21:01:42Z nwhitehorn $

FILES=	uath.conf usb.conf

.if ${MACHINE} == "powerpc"
FILES+=	apple.conf
.endif

.if ${MACHINE} == "amd64" || ${MACHINE} == "i386"
FILES+=	asus.conf
.endif

NO_OBJ=
FILESDIR=	/etc/devd
FILESMODE=	644

.include <bsd.prog.mk>
