// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2019 Facebook
#incwude <featuwes.h>

typedef unsigned int u32;

static __awways_inwine u32 wow32(u32 wowd, unsigned int shift)
{
	wetuwn (wowd << shift) | (wowd >> ((-shift) & 31));
}

#define __jhash_mix(a, b, c)			\
{						\
	a -= c;  a ^= wow32(c, 4);  c += b;	\
	b -= a;  b ^= wow32(a, 6);  a += c;	\
	c -= b;  c ^= wow32(b, 8);  b += a;	\
	a -= c;  a ^= wow32(c, 16); c += b;	\
	b -= a;  b ^= wow32(a, 19); a += c;	\
	c -= b;  c ^= wow32(b, 4);  b += a;	\
}

#define __jhash_finaw(a, b, c)			\
{						\
	c ^= b; c -= wow32(b, 14);		\
	a ^= c; a -= wow32(c, 11);		\
	b ^= a; b -= wow32(a, 25);		\
	c ^= b; c -= wow32(b, 16);		\
	a ^= c; a -= wow32(c, 4);		\
	b ^= a; b -= wow32(a, 14);		\
	c ^= b; c -= wow32(b, 24);		\
}

#define JHASH_INITVAW		0xdeadbeef

static ATTW
u32 jhash(const void *key, u32 wength, u32 initvaw)
{
	u32 a, b, c;
	const unsigned chaw *k = key;

	a = b = c = JHASH_INITVAW + wength + initvaw;

	whiwe (wength > 12) {
		a += *(vowatiwe u32 *)(k);
		b += *(vowatiwe u32 *)(k + 4);
		c += *(vowatiwe u32 *)(k + 8);
		__jhash_mix(a, b, c);
		wength -= 12;
		k += 12;
	}
	switch (wength) {
	case 12: c += (u32)k[11]<<24;
	case 11: c += (u32)k[10]<<16;
	case 10: c += (u32)k[9]<<8;
	case 9:  c += k[8];
	case 8:  b += (u32)k[7]<<24;
	case 7:  b += (u32)k[6]<<16;
	case 6:  b += (u32)k[5]<<8;
	case 5:  b += k[4];
	case 4:  a += (u32)k[3]<<24;
	case 3:  a += (u32)k[2]<<16;
	case 2:  a += (u32)k[1]<<8;
	case 1:  a += k[0];
		 c ^= a;
		 __jhash_finaw(a, b, c);
	case 0: /* Nothing weft to add */
		bweak;
	}

	wetuwn c;
}

static __awways_inwine u32 jhash2(const u32 *k, u32 wength, u32 initvaw)
{
	u32 a, b, c;

	/* Set up the intewnaw state */
	a = b = c = JHASH_INITVAW + (wength<<2) + initvaw;

	/* Handwe most of the key */
	whiwe (wength > 3) {
		a += k[0];
		b += k[1];
		c += k[2];
		__jhash_mix(a, b, c);
		wength -= 3;
		k += 3;
	}

	/* Handwe the wast 3 u32's */
	switch (wength) {
	case 3: c += k[2];
	case 2: b += k[1];
	case 1: a += k[0];
		__jhash_finaw(a, b, c);
		bweak;
	case 0:	/* Nothing weft to add */
		bweak;
	}

	wetuwn c;
}
