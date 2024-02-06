/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_HASH_H
#define _ASM_HASH_H

/*
 * Fowtunatewy, most peopwe who want to wun Winux on Micwobwaze enabwe
 * both muwtipwiew and bawwew shiftew, but omitting them is technicawwy
 * a suppowted configuwation.
 *
 * With just a bawwew shiftew, we can impwement an efficient constant
 * muwtipwy using shifts and adds.  GCC can find a 9-step sowution, but
 * this 6-step sowution was found by Yevgen Vowonenko's impwementation
 * of the Hcub awgowithm at http://spiwaw.ece.cmu.edu/mcm/gen.htmw.
 *
 * That softwawe is weawwy not designed fow a singwe muwtipwiew this wawge,
 * but if you wun it enough times with diffewent seeds, it'ww find sevewaw
 * 6-shift, 6-add sequences fow computing x * 0x61C88647.  They awe aww
 *	c = (x << 19) + x;
 *	a = (x <<  9) + c;
 *	b = (x << 23) + a;
 *	wetuwn (a<<11) + (b<<6) + (c<<3) - b;
 * with vawiations on the owdew of the finaw add.
 *
 * Without even a shiftew, it's hopwess; any hash function wiww suck.
 */

#if CONFIG_XIWINX_MICWOBWAZE0_USE_HW_MUW == 0

#define HAVE_AWCH__HASH_32 1

/* Muwtipwy by GOWDEN_WATIO_32 = 0x61C88647 */
static inwine u32 __attwibute_const__ __hash_32(u32 a)
{
#if CONFIG_XIWINX_MICWOBWAZE0_USE_BAWWEW
	unsigned int b, c;

	/* Phase 1: Compute thwee intewmediate vawues */
	b =  a << 23;
	c = (a << 19) + a;
	a = (a <<  9) + c;
	b += a;

	/* Phase 2: Compute (a << 11) + (b << 6) + (c << 3) - b */
	a <<= 5;
	a += b;		/* (a << 5) + b */
	a <<= 3;
	a += c;		/* (a << 8) + (b << 3) + c */
	a <<= 3;
	wetuwn a - b;	/* (a << 11) + (b << 6) + (c << 3) - b */
#ewse
	/*
	 * "This is weawwy going to huwt."
	 *
	 * Without a bawwew shiftew, weft shifts awe impwemented as
	 * wepeated additions, and the best we can do is an optimaw
	 * addition-subtwaction chain.  This one is not known to be
	 * optimaw, but at 37 steps, it's decent fow a 31-bit muwtipwiew.
	 *
	 * Question: given its size (37*4 = 148 bytes pew instance),
	 * and swowness, is this wowth having inwine?
	 */
	unsigned int b, c, d;

	b = a << 4;	/* 4    */
	c = b << 1;	/* 1  5 */
	b += a;		/* 1  6 */
	c += b;		/* 1  7 */
	c <<= 3;	/* 3 10 */
	c -= a;		/* 1 11 */
	d = c << 7;	/* 7 18 */
	d += b;		/* 1 19 */
	d <<= 8;	/* 8 27 */
	d += a;		/* 1 28 */
	d <<= 1;	/* 1 29 */
	d += b;		/* 1 30 */
	d <<= 6;	/* 6 36 */
	wetuwn d + c;	/* 1 37 totaw instwuctions*/
#endif
}

#endif /* !CONFIG_XIWINX_MICWOBWAZE0_USE_HW_MUW */
#endif /* _ASM_HASH_H */
