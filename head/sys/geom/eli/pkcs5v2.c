/*-
 * Copyright (c) 2005 Pawel Jakub Dawidek <pjd@FreeBSD.org>
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
 * THIS SOFTWARE IS PROVIDED BY THE AUTHORS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>
__FBSDID("$FreeBSD: soc2013/dpl/head/sys/geom/eli/pkcs5v2.c 155217 2006-02-01 12:06:01Z pjd $");

#include <sys/param.h>
#ifdef _KERNEL
#include <sys/systm.h>
#include <sys/kernel.h>
#else
#include <sys/resource.h>
#include <stdint.h>
#include <strings.h>
#endif

#include <geom/eli/g_eli.h>
#include <geom/eli/pkcs5v2.h>

static __inline void
xor(uint8_t *dst, const uint8_t *src, size_t size)
{

	for (; size > 0; size--)
		*dst++ ^= *src++;
}

void
pkcs5v2_genkey(uint8_t *key, unsigned keylen, const uint8_t *salt,
    size_t saltsize, const char *passphrase, u_int iterations)
{
	uint8_t md[SHA512_MDLEN], saltcount[saltsize + sizeof(uint32_t)];
	uint8_t *counter, *keyp;
	u_int i, bsize, passlen;
	uint32_t count;

	passlen = strlen(passphrase);
	bzero(key, keylen);
	bcopy(salt, saltcount, saltsize);
	counter = saltcount + saltsize;

	keyp = key;
	for (count = 1; keylen > 0; count++, keylen -= bsize, keyp += bsize) {
		bsize = MIN(keylen, sizeof(md));

		counter[0] = (count >> 24) & 0xff;
		counter[1] = (count >> 16) & 0xff;
		counter[2] = (count >> 8) & 0xff;
		counter[3] = count & 0xff;
		g_eli_crypto_hmac(passphrase, passlen, saltcount,
		    sizeof(saltcount), md, 0);
		xor(keyp, md, bsize);

		for(i = 1; i < iterations; i++) {
			g_eli_crypto_hmac(passphrase, passlen, md, sizeof(md),
			    md, 0);
			xor(keyp, md, bsize);
		}
	}
}

#ifndef _KERNEL
/*
 * Return the number of microseconds needed for 'interations' iterations.
 */
static int
pkcs5v2_probe(int iterations)
{
	uint8_t	key[G_ELI_USERKEYLEN], salt[G_ELI_SALTLEN];
	uint8_t passphrase[] = "passphrase";
	struct rusage start, end;
	int usecs;

	getrusage(RUSAGE_SELF, &start);
	pkcs5v2_genkey(key, sizeof(key), salt, sizeof(salt), passphrase,
	    iterations);
	getrusage(RUSAGE_SELF, &end);

	usecs = end.ru_utime.tv_sec - start.ru_utime.tv_sec;
	usecs *= 1000000;
	usecs += end.ru_utime.tv_usec - start.ru_utime.tv_usec;
	return (usecs);
}

/*
 * Return the number of iterations which takes 'usecs' microseconds.
 */
int
pkcs5v2_calculate(int usecs)
{
	int iterations, v;

	for (iterations = 1; ; iterations <<= 1) {
		v = pkcs5v2_probe(iterations);
		if (v > 2000000)
			break;
	}
	return (((intmax_t)iterations * (intmax_t)usecs) / v);
}
#endif	/* !_KERNEL */
