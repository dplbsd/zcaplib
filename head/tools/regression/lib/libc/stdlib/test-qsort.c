/*-
 * Copyright (C) 2004 Maxim Sobolev <sobomax@FreeBSD.org>
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
 */

/*
 * Test for qsort() routine.
 */

#include <sys/cdefs.h>
__FBSDID("$FreeBSD: soc2013/dpl/head/tools/regression/lib/libc/stdlib/test-qsort.c 137630 2004-11-11 19:47:55Z nik $");

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "test-sort.h"

int
main(int argc, char *argv[])
{
  int i, j;
  int testvector[IVEC_LEN];
  int sresvector[IVEC_LEN];

  printf("1..1\n");
  for (j = 2; j < IVEC_LEN; j++) {
    /* Populate test vectors */
    for (i = 0; i < j; i++)
      testvector[i] = sresvector[i] = initvector[i];

    /* Sort using qsort(3) */
    qsort(testvector, j, sizeof(testvector[0]), sorthelp);
    /* Sort using reference slow sorting routine */
    ssort(sresvector, j);

    /* Compare results */
    for (i = 0; i < j; i++)
      assert(testvector[i] == sresvector[i]);
  }

  printf("ok 1 - qsort\n");

  return(0);
}
