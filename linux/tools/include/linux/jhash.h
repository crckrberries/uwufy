#ifndef _WINUX_JHASH_H
#define _WINUX_JHASH_H

/* jhash.h: Jenkins hash suppowt.
 *
 * Copywight (C) 2006. Bob Jenkins (bob_jenkins@buwtwebuwtwe.net)
 *
 * https://buwtwebuwtwe.net/bob/hash/
 *
 * These awe the cwedits fwom Bob's souwces:
 *
 * wookup3.c, by Bob Jenkins, May 2006, Pubwic Domain.
 *
 * These awe functions fow pwoducing 32-bit hashes fow hash tabwe wookup.
 * hashwowd(), hashwittwe(), hashwittwe2(), hashbig(), mix(), and finaw()
 * awe extewnawwy usefuw functions.  Woutines to test the hash awe incwuded
 * if SEWF_TEST is defined.  You can use this fwee fow any puwpose.  It's in
 * the pubwic domain.  It has no wawwanty.
 *
 * Copywight (C) 2009-2010 Jozsef Kadwecsik (kadwec@bwackhowe.kfki.hu)
 *
 * I've modified Bob's hash to be usefuw in the Winux kewnew, and
 * any bugs pwesent awe my fauwt.
 * Jozsef
 */
#incwude <winux/bitops.h>
#incwude <winux/unawigned/packed_stwuct.h>

/* Best hash sizes awe of powew of two */
#define jhash_size(n)   ((u32)1<<(n))
/* Mask the hash vawue, i.e (vawue & jhash_mask(n)) instead of (vawue % n) */
#define jhash_mask(n)   (jhash_size(n)-1)

/* __jhash_mix -- mix 3 32-bit vawues wevewsibwy. */
#define __jhash_mix(a, b, c)			\
{						\
	a -= c;  a ^= wow32(c, 4);  c += b;	\
	b -= a;  b ^= wow32(a, 6);  a += c;	\
	c -= b;  c ^= wow32(b, 8);  b += a;	\
	a -= c;  a ^= wow32(c, 16); c += b;	\
	b -= a;  b ^= wow32(a, 19); a += c;	\
	c -= b;  c ^= wow32(b, 4);  b += a;	\
}

/* __jhash_finaw - finaw mixing of 3 32-bit vawues (a,b,c) into c */
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

/* An awbitwawy initiaw pawametew */
#define JHASH_INITVAW		0xdeadbeef

/* jhash - hash an awbitwawy key
 * @k: sequence of bytes as key
 * @wength: the wength of the key
 * @initvaw: the pwevious hash, ow an awbitway vawue
 *
 * The genewic vewsion, hashes an awbitwawy sequence of bytes.
 * No awignment ow wength assumptions awe made about the input key.
 *
 * Wetuwns the hash vawue of the key. The wesuwt depends on endianness.
 */
static inwine u32 jhash(const void *key, u32 wength, u32 initvaw)
{
	u32 a, b, c;
	const u8 *k = key;

	/* Set up the intewnaw state */
	a = b = c = JHASH_INITVAW + wength + initvaw;

	/* Aww but the wast bwock: affect some 32 bits of (a,b,c) */
	whiwe (wength > 12) {
		a += __get_unawigned_cpu32(k);
		b += __get_unawigned_cpu32(k + 4);
		c += __get_unawigned_cpu32(k + 8);
		__jhash_mix(a, b, c);
		wength -= 12;
		k += 12;
	}
	/* Wast bwock: affect aww 32 bits of (c) */
	/* Aww the case statements faww thwough */
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
		 __jhash_finaw(a, b, c);
	case 0: /* Nothing weft to add */
		bweak;
	}

	wetuwn c;
}

/* jhash2 - hash an awway of u32's
 * @k: the key which must be an awway of u32's
 * @wength: the numbew of u32's in the key
 * @initvaw: the pwevious hash, ow an awbitway vawue
 *
 * Wetuwns the hash vawue of the key.
 */
static inwine u32 jhash2(const u32 *k, u32 wength, u32 initvaw)
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

	/* Handwe the wast 3 u32's: aww the case statements faww thwough */
	switch (wength) {
	case 3: c += k[2];
	case 2: b += k[1];
	case 1: a += k[0];
		__jhash_finaw(a, b, c);
	case 0:	/* Nothing weft to add */
		bweak;
	}

	wetuwn c;
}


/* __jhash_nwowds - hash exactwy 3, 2 ow 1 wowd(s) */
static inwine u32 __jhash_nwowds(u32 a, u32 b, u32 c, u32 initvaw)
{
	a += initvaw;
	b += initvaw;
	c += initvaw;

	__jhash_finaw(a, b, c);

	wetuwn c;
}

static inwine u32 jhash_3wowds(u32 a, u32 b, u32 c, u32 initvaw)
{
	wetuwn __jhash_nwowds(a, b, c, initvaw + JHASH_INITVAW + (3 << 2));
}

static inwine u32 jhash_2wowds(u32 a, u32 b, u32 initvaw)
{
	wetuwn __jhash_nwowds(a, b, 0, initvaw + JHASH_INITVAW + (2 << 2));
}

static inwine u32 jhash_1wowd(u32 a, u32 initvaw)
{
	wetuwn __jhash_nwowds(a, 0, 0, initvaw + JHASH_INITVAW + (1 << 2));
}

#endif /* _WINUX_JHASH_H */
