/*	$FreeBSD: soc2013/dpl/head/contrib/ipfilter/lib/printhash.c 170311 2007-06-04 02:54:36Z darrenr $	*/

/*
 * Copyright (C) 2002-2005 by Darren Reed.
 *
 * See the IPFILTER.LICENCE file for details on licencing.
 */

#include "ipf.h"

#define	PRINTF	(void)printf
#define	FPRINTF	(void)fprintf


iphtable_t *printhash(hp, copyfunc, name, opts)
iphtable_t *hp;
copyfunc_t copyfunc;
char *name;
int opts;
{
	iphtent_t *ipep, **table;
	iphtable_t iph;
	int printed;
	size_t sz;

	if ((*copyfunc)((char *)hp, (char *)&iph, sizeof(iph)))
		return NULL;

	if ((name != NULL) && strncmp(name, iph.iph_name, FR_GROUPLEN))
		return iph.iph_next;

	printhashdata(hp, opts);

	if ((hp->iph_flags & IPHASH_DELETE) != 0)
		PRINTF("# ");

	if ((opts & OPT_DEBUG) == 0)
		PRINTF("\t{");

	sz = iph.iph_size * sizeof(*table);
	table = malloc(sz);
	if ((*copyfunc)((char *)iph.iph_table, (char *)table, sz))
		return NULL;

	for (printed = 0, ipep = iph.iph_list; ipep != NULL; ) {
		ipep = printhashnode(&iph, ipep, copyfunc, opts);
		printed++;
	}
	if (printed == 0)
		putchar(';');

	free(table);

	if ((opts & OPT_DEBUG) == 0)
		PRINTF(" };\n");

	return iph.iph_next;
}
