# $FreeBSD: soc2013/dpl/head/sys/dev/mii/miibus_if.m 84181 2001-09-29 18:40:06Z jlemon $

#include <sys/bus.h>

INTERFACE miibus;

#
# Read register from device on MII bus
#
METHOD int readreg {
	device_t		dev;
	int			phy;
	int			reg;
};

#
# Write register to device on MII bus
#
METHOD int writereg {
	device_t		dev;
	int			phy;
	int			reg;
	int			val;
};

#
# Notify bus about PHY status change.
#
METHOD void statchg {
	device_t		dev;
};

#
# Notify bus about PHY link change.
#
METHOD void linkchg {
	device_t		dev;
};

#
# Notify bus that media has been set.
#
METHOD void mediainit {
	device_t		dev;
};
