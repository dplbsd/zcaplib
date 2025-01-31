/*-
 * Copyright (c) 2006 nCircle Network Security, Inc.
 * Copyright (c) 2007 Robert N. M. Watson
 * All rights reserved.
 *
 * This software was developed by Robert N. M. Watson for the TrustedBSD
 * Project under contract to nCircle Network Security, Inc.
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
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR, NCIRCLE NETWORK SECURITY,
 * INC., OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $FreeBSD: soc2013/dpl/head/tools/regression/priv/priv_vfs_stickyfile.c 172149 2007-09-09 23:08:39Z rwatson $
 */

/*
 * Check that privilege is required to set the sticky bit on a file but not a
 * directory.
 */

#include <sys/stat.h>

#include <err.h>
#include <errno.h>
#include <unistd.h>

#include "main.h"

char fpath[1024];
int fpath_initialized;

char dpath[1024];
int dpath_initialized;

int
priv_vfs_stickyfile_dir_fowner_setup(int asroot, int injail,
    struct test *test)
{

	setup_dir("priv_vfs_stickyfile_fowner_setup: dpath", dpath,
	    UID_OWNER, GID_OWNER, 0700);
	dpath_initialized = 1;
	return (0);
}

int
priv_vfs_stickyfile_dir_fother_setup(int asroot, int injail,
    struct test *test)
{

	setup_dir("priv_vfs_stickyfile_fother_setup: dpath", dpath,
	    UID_OTHER, GID_OTHER, 0700);
	dpath_initialized = 1;
	return (0);
}

int
priv_vfs_stickyfile_file_fowner_setup(int asroot, int injail,
    struct test *test)
{

	setup_file("priv_vfs_stickyfile_fowner_setup: fpath", fpath,
	    UID_OWNER, GID_OWNER, 0600);
	fpath_initialized = 1;
	return (0);
}

int
priv_vfs_stickyfile_file_fother_setup(int asroot, int injail,
    struct test *test)
{

	setup_file("priv_vfs_stickyfile_fother_setup: fpath", fpath,
	    UID_OTHER, GID_OTHER, 0600);
	fpath_initialized = 1;
	return (0);
}

void
priv_vfs_stickyfile_dir_fowner(int asroot, int injail, struct test *test)
{
	int error;

	error = chmod(dpath, 0700 | S_ISTXT);
	if (asroot && injail)
		expect("priv_vfs_stickyfile_dir_fowner(root, jail)", error,
		    0, 0);
	if (asroot && !injail)
		expect("priv_vfs_stickyfile_dir_fowner(root, !jail)", error,
		    0, 0);
	if (!asroot && injail)
		expect("priv_vfs_stickyfile_dir_fowner(!root, jail)", error,
		    0, 0);
	if (!asroot && !injail)
		expect("priv_vfs_stickyfile_dir_fowner(!root, !jail)", error,
		    0, 0);
}

void
priv_vfs_stickyfile_dir_fother(int asroot, int injail, struct test *test)
{
	int error;

	error = chmod(dpath, 0700 | S_ISTXT);
	if (asroot && injail)
		expect("priv_vfs_stickyfile_dir_fother(root, jail)", error,
		    0, 0);
	if (asroot && !injail)
		expect("priv_vfs_stickyfile_dir_fother(root, !jail)", error,
		    0, 0);
	if (!asroot && injail)
		expect("priv_vfs_stickyfile_dir_fother(!root, jail)", error,
		    -1, EPERM);
	if (!asroot && !injail)
		expect("priv_vfs_stickyfile_dir_fother(!root, !jail)", error,
		    -1, EPERM);
}

void
priv_vfs_stickyfile_file_fowner(int asroot, int injail, struct test *test)
{
	int error;

	error = chmod(fpath, 0600 | S_ISTXT);
	if (asroot && injail)
		expect("priv_vfs_stickyfile_file_fowner(root, jail)", error,
		    0, 0);
	if (asroot && !injail)
		expect("priv_vfs_stickyfile_file_fowner(root, !jail)", error,
		    0, 0);
	if (!asroot && injail)
		expect("priv_vfs_stickyfile_file_fowner(!root, jail)", error,
		    -1, EFTYPE);
	if (!asroot && !injail)
		expect("priv_vfs_stickyfile_file_fowner(!root, !jail)", error,
		    -1, EFTYPE);
}

void
priv_vfs_stickyfile_file_fother(int asroot, int injail, struct test *test)
{
	int error;

	error = chmod(fpath, 0600 | S_ISTXT);
	if (asroot && injail)
		expect("priv_vfs_stickyfile_file_fother(root, jail)", error,
		    0, 0);
	if (asroot && !injail)
		expect("priv_vfs_stickyfile_file_fother(root, !jail)", error,
		    0, 0);
	if (!asroot && injail)
		expect("priv_vfs_stickyfile_file_fother(!root, jail)", error,
		    -1, EPERM);
	if (!asroot && !injail)
		expect("priv_vfs_stickyfile_file_fother(!root, !jail)", error,
		    -1, EPERM);
}

void
priv_vfs_stickyfile_dir_cleanup(int asroot, int injail, struct test *test)
{

	if (dpath_initialized) {
		(void)rmdir(dpath);
		dpath_initialized = 0;
	}
}

void
priv_vfs_stickyfile_file_cleanup(int asroot, int injail, struct test *test)
{

	if (fpath_initialized) {
		(void)unlink(fpath);
		fpath_initialized = 0;
	}
}
