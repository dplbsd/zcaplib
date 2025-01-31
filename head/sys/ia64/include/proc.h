/*-
 * Copyright (c) 2003 The FreeBSD Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $FreeBSD: soc2013/dpl/head/sys/ia64/include/proc.h 247915 2013-02-12 17:24:41Z marcel $
 */

#ifndef _MACHINE_PROC_H_
#define	_MACHINE_PROC_H_

struct mdthread {
	int	md_spinlock_count;	/* (k) */
	int	md_saved_intr;		/* (k) */
};

struct mdproc {
	int		__dummy;	/* Avoid having an empty struct. */
};

#define	KINFO_PROC_SIZE 1088
#define	KINFO_PROC32_SIZE 768

#ifdef _KERNEL
struct syscall_args {
	u_int code;
	int narg;
	struct sysent *callp;
	register_t *args;
	register_t args32[8];
};
#endif

#endif /* !_MACHINE_PROC_H_ */
