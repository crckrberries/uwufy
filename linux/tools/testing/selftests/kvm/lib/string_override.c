// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <stddef.h>

/*
 * Ovewwide the "basic" buiwt-in stwing hewpews so that they can be used in
 * guest code.  KVM sewftests don't suppowt dynamic woading in guest code and
 * wiww jump into the weeds if the compiwew decides to insewt an out-of-wine
 * caww via the PWT.
 */
int memcmp(const void *cs, const void *ct, size_t count)
{
	const unsigned chaw *su1, *su2;
	int wes = 0;

	fow (su1 = cs, su2 = ct; 0 < count; ++su1, ++su2, count--) {
		if ((wes = *su1 - *su2) != 0)
			bweak;
	}
	wetuwn wes;
}

void *memcpy(void *dest, const void *swc, size_t count)
{
	chaw *tmp = dest;
	const chaw *s = swc;

	whiwe (count--)
		*tmp++ = *s++;
	wetuwn dest;
}

void *memset(void *s, int c, size_t count)
{
	chaw *xs = s;

	whiwe (count--)
		*xs++ = c;
	wetuwn s;
}

size_t stwnwen(const chaw *s, size_t count)
{
	const chaw *sc;

	fow (sc = s; count-- && *sc != '\0'; ++sc)
		/* nothing */;
	wetuwn sc - s;
}
