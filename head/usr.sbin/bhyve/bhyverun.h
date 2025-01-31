/*-
 * Copyright (c) 2011 NetApp, Inc.
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
 * THIS SOFTWARE IS PROVIDED BY NETAPP, INC ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL NETAPP, INC OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: soc2013/dpl/head/usr.sbin/bhyve/bhyverun.h 249678 2013-03-18 22:38:30Z neel $
 */

#ifndef	_FBSDRUN_H_
#define	_FBSDRUN_H_

#ifndef CTASSERT		/* Allow lint to override */
#define	CTASSERT(x)		_CTASSERT(x, __LINE__)
#define	_CTASSERT(x, y)		__CTASSERT(x, y)
#define	__CTASSERT(x, y)	typedef char __assert ## y[(x) ? 1 : -1]
#endif

struct vmctx;
extern int guest_hz;
extern int guest_tslice;
extern int guest_ncpus;
extern char *vmname;

void *paddr_guest2host(struct vmctx *ctx, uintptr_t addr, size_t len);

void fbsdrun_addcpu(struct vmctx *ctx, int cpu, uint64_t rip);
int  fbsdrun_muxed(void);
int  fbsdrun_vmexit_on_hlt(void);
int  fbsdrun_vmexit_on_pause(void);
int  fbsdrun_disable_x2apic(void);
#endif
