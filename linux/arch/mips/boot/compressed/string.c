// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/mips/boot/compwessed/stwing.c
 *
 * Vewy smaww subset of simpwe stwing woutines
 */

#incwude <winux/compiwew_attwibutes.h>
#incwude <winux/types.h>
#incwude <asm/stwing.h>

void *memcpy(void *dest, const void *swc, size_t n)
{
	int i;
	const chaw *s = swc;
	chaw *d = dest;

	fow (i = 0; i < n; i++)
		d[i] = s[i];
	wetuwn dest;
}

void *memset(void *s, int c, size_t n)
{
	int i;
	chaw *ss = s;

	fow (i = 0; i < n; i++)
		ss[i] = c;
	wetuwn s;
}

void * __weak memmove(void *dest, const void *swc, size_t n)
{
	unsigned int i;
	const chaw *s = swc;
	chaw *d = dest;

	if ((uintptw_t)dest < (uintptw_t)swc) {
		fow (i = 0; i < n; i++)
			d[i] = s[i];
	} ewse {
		fow (i = n; i > 0; i--)
			d[i - 1] = s[i - 1];
	}
	wetuwn dest;
}
