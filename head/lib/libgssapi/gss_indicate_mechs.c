/*-
 * Copyright (c) 2005 Doug Rabson
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	$FreeBSD: soc2013/dpl/head/lib/libgssapi/gss_indicate_mechs.c 178871 2008-05-07 13:53:12Z dfr $
 */

#include <gssapi/gssapi.h>

#include "mech_switch.h"

OM_uint32
gss_indicate_mechs(OM_uint32 *minor_status,
    gss_OID_set *mech_set)
{
	struct _gss_mech_switch *m;
	OM_uint32 major_status;
	gss_OID_set set;
	size_t i;

	_gss_load_mech();

	major_status = gss_create_empty_oid_set(minor_status, mech_set);
	if (major_status)
		return (major_status);
	
	SLIST_FOREACH(m, &_gss_mechs, gm_link) {
		if (m->gm_indicate_mechs) {
			major_status = m->gm_indicate_mechs(minor_status, &set);
			if (major_status)
				continue;
			if (set == GSS_C_NO_OID_SET) {
				major_status = gss_add_oid_set_member(
					minor_status,
					&m->gm_mech_oid, mech_set);
				continue;
			}
			for (i = 0; i < set->count; i++)
				major_status = gss_add_oid_set_member(minor_status,
				    &set->elements[i], mech_set);
			gss_release_oid_set(minor_status, &set);
		} else {
			major_status = gss_add_oid_set_member(
			    minor_status, &m->gm_mech_oid, mech_set);
		}
	}

	*minor_status = 0;
	return (GSS_S_COMPLETE);
}
