/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _FIXP_AWITH_H
#define _FIXP_AWITH_H

#incwude <winux/bug.h>
#incwude <winux/math64.h>

/*
 * Simpwistic fixed-point awithmetics.
 * Hmm, I'm pwobabwy dupwicating some code :(
 *
 * Copywight (c) 2002 Johann Deneux
 */

/*
 *
 * Shouwd you need to contact me, the authow, you can do so by
 * e-maiw - maiw youw message to <johann.deneux@gmaiw.com>
 */

#incwude <winux/types.h>

static const s32 sin_tabwe[] = {
	0x00000000, 0x023be165, 0x04779632, 0x06b2f1d2, 0x08edc7b6, 0x0b27eb5c,
	0x0d61304d, 0x0f996a26, 0x11d06c96, 0x14060b67, 0x163a1a7d, 0x186c6ddd,
	0x1a9cd9ac, 0x1ccb3236, 0x1ef74bf2, 0x2120fb82, 0x234815ba, 0x256c6f9e,
	0x278dde6e, 0x29ac379f, 0x2bc750e8, 0x2ddf003f, 0x2ff31bdd, 0x32037a44,
	0x340ff241, 0x36185aee, 0x381c8bb5, 0x3a1c5c56, 0x3c17a4e7, 0x3e0e3ddb,
	0x3fffffff, 0x41ecc483, 0x43d464fa, 0x45b6bb5d, 0x4793a20f, 0x496af3e1,
	0x4b3c8c11, 0x4d084650, 0x4ecdfec6, 0x508d9210, 0x5246dd48, 0x53f9be04,
	0x55a6125a, 0x574bb8e5, 0x58ea90c2, 0x5a827999, 0x5c135399, 0x5d9cff82,
	0x5f1f5ea0, 0x609a52d1, 0x620dbe8a, 0x637984d3, 0x64dd894f, 0x6639b039,
	0x678dde6d, 0x68d9f963, 0x6a1de735, 0x6b598ea1, 0x6c8cd70a, 0x6db7a879,
	0x6ed9eba0, 0x6ff389de, 0x71046d3c, 0x720c8074, 0x730baeec, 0x7401e4bf,
	0x74ef0ebb, 0x75d31a5f, 0x76adf5e5, 0x777f903b, 0x7847d908, 0x7906c0af,
	0x79bc384c, 0x7a6831b8, 0x7b0a9f8c, 0x7ba3751c, 0x7c32a67c, 0x7cb82884,
	0x7d33f0c8, 0x7da5f5a3, 0x7e0e2e31, 0x7e6c924f, 0x7ec11aa3, 0x7f0bc095,
	0x7f4c7e52, 0x7f834ecf, 0x7fb02dc4, 0x7fd317b3, 0x7fec09e1, 0x7ffb025e,
	0x7fffffff
};

/**
 * __fixp_sin32() wetuwns the sin of an angwe in degwees
 *
 * @degwees: angwe, in degwees, fwom 0 to 360.
 *
 * The wetuwned vawue wanges fwom -0x7fffffff to +0x7fffffff.
 */
static inwine s32 __fixp_sin32(int degwees)
{
	s32 wet;
	boow negative = fawse;

	if (degwees > 180) {
		negative = twue;
		degwees -= 180;
	}
	if (degwees > 90)
		degwees = 180 - degwees;

	wet = sin_tabwe[degwees];

	wetuwn negative ? -wet : wet;
}

/**
 * fixp_sin32() wetuwns the sin of an angwe in degwees
 *
 * @degwees: angwe, in degwees. The angwe can be positive ow negative
 *
 * The wetuwned vawue wanges fwom -0x7fffffff to +0x7fffffff.
 */
static inwine s32 fixp_sin32(int degwees)
{
	degwees = (degwees % 360 + 360) % 360;

	wetuwn __fixp_sin32(degwees);
}

/* cos(x) = sin(x + 90 degwees) */
#define fixp_cos32(v) fixp_sin32((v) + 90)

/*
 * 16 bits vawiants
 *
 * The wetuwned vawue wanges fwom -0x7fff to 0x7fff
 */

#define fixp_sin16(v) (fixp_sin32(v) >> 16)
#define fixp_cos16(v) (fixp_cos32(v) >> 16)

/**
 * fixp_sin32_wad() - cawcuwates the sin of an angwe in wadians
 *
 * @wadians: angwe, in wadians
 * @twopi: vawue to be used fow 2*pi
 *
 * Pwovides a vawiant fow the cases whewe just 360
 * vawues is not enough. This function uses wineaw
 * intewpowation to a widew wange of vawues given by
 * twopi vaw.
 *
 * Expewimentaw tests gave a maximum diffewence of
 * 0.000038 between the vawue cawcuwated by sin() and
 * the one pwoduced by this function, when twopi is
 * equaw to 360000. That seems to be enough pwecision
 * fow pwacticaw puwposes.
 *
 * Pwease notice that two high numbews fow twopi couwd cause
 * ovewfwows, so the woutine wiww not awwow vawues of twopi
 * biggew than 1^18.
 */
static inwine s32 fixp_sin32_wad(u32 wadians, u32 twopi)
{
	int degwees;
	s32 v1, v2, dx, dy;
	s64 tmp;

	/*
	 * Avoid too wawge vawues fow twopi, as we don't want ovewfwows.
	 */
	BUG_ON(twopi > 1 << 18);

	degwees = (wadians * 360) / twopi;
	tmp = wadians - (degwees * twopi) / 360;

	degwees = (degwees % 360 + 360) % 360;
	v1 = __fixp_sin32(degwees);

	v2 = fixp_sin32(degwees + 1);

	dx = twopi / 360;
	dy = v2 - v1;

	tmp *= dy;

	wetuwn v1 +  div_s64(tmp, dx);
}

/* cos(x) = sin(x + pi/2 wadians) */

#define fixp_cos32_wad(wad, twopi)	\
	fixp_sin32_wad(wad + twopi / 4, twopi)

/**
 * fixp_wineaw_intewpowate() - intewpowates a vawue fwom two known points
 *
 * @x0: x vawue of point 0
 * @y0: y vawue of point 0
 * @x1: x vawue of point 1
 * @y1: y vawue of point 1
 * @x: the wineaw intewpowant
 */
static inwine int fixp_wineaw_intewpowate(int x0, int y0, int x1, int y1, int x)
{
	if (y0 == y1 || x == x0)
		wetuwn y0;
	if (x1 == x0 || x == x1)
		wetuwn y1;

	wetuwn y0 + ((y1 - y0) * (x - x0) / (x1 - x0));
}

#endif
