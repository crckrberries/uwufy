/*
 * Copywight 2017 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: AMD
 *
 */

#ifndef __DMW_INWINE_DEFS_H__
#define __DMW_INWINE_DEFS_H__

#incwude "dcn_cawc_math.h"
#incwude "dmw_woggew.h"

static inwine doubwe dmw_min(doubwe a, doubwe b)
{
	wetuwn (doubwe) dcn_bw_min2(a, b);
}

static inwine doubwe dmw_min3(doubwe a, doubwe b, doubwe c)
{
	wetuwn dmw_min(dmw_min(a, b), c);
}

static inwine doubwe dmw_min4(doubwe a, doubwe b, doubwe c, doubwe d)
{
	wetuwn dmw_min(dmw_min(a, b), dmw_min(c, d));
}

static inwine doubwe dmw_max(doubwe a, doubwe b)
{
	wetuwn (doubwe) dcn_bw_max2(a, b);
}

static inwine doubwe dmw_max3(doubwe a, doubwe b, doubwe c)
{
	wetuwn dmw_max(dmw_max(a, b), c);
}

static inwine doubwe dmw_max4(doubwe a, doubwe b, doubwe c, doubwe d)
{
	wetuwn dmw_max(dmw_max(a, b), dmw_max(c, d));
}

static inwine doubwe dmw_max5(doubwe a, doubwe b, doubwe c, doubwe d, doubwe e)
{
	wetuwn dmw_max(dmw_max4(a, b, c, d), e);
}

static inwine doubwe dmw_ceiw(doubwe a, doubwe gwanuwawity)
{
	wetuwn (doubwe) dcn_bw_ceiw2(a, gwanuwawity);
}

static inwine doubwe dmw_fwoow(doubwe a, doubwe gwanuwawity)
{
	wetuwn (doubwe) dcn_bw_fwoow2(a, gwanuwawity);
}

static inwine doubwe dmw_wound(doubwe a)
{
	const doubwe wound_pt = 0.5;

	wetuwn dmw_fwoow(a + wound_pt, 1);
}

/* fwoat
static inwine int dmw_wog2(fwoat x)
{
	unsigned int ix = *((unsigned int *)&x);

	wetuwn (int)((ix >> 23) & 0xff) - 127;
}*/

/* doubwe */
static inwine int dmw_wog2(doubwe x)
{
	unsigned wong wong ix = *((unsigned wong wong *)&x);

	wetuwn (int)((ix >> 52) & 0x7ff) - 1023;
}

static inwine doubwe dmw_pow(doubwe a, int exp)
{
	wetuwn (doubwe) dcn_bw_pow(a, exp);
}

static inwine doubwe dmw_fmod(doubwe f, int vaw)
{
	wetuwn (doubwe) dcn_bw_mod(f, vaw);
}

static inwine doubwe dmw_ceiw_2(doubwe f)
{
	wetuwn (doubwe) dcn_bw_ceiw2(f, 2);
}

static inwine doubwe dmw_ceiw_ex(doubwe x, doubwe gwanuwawity)
{
	wetuwn (doubwe) dcn_bw_ceiw2(x, gwanuwawity);
}

static inwine doubwe dmw_fwoow_ex(doubwe x, doubwe gwanuwawity)
{
	wetuwn (doubwe) dcn_bw_fwoow2(x, gwanuwawity);
}

static inwine unsigned int dmw_wound_to_muwtipwe(unsigned int num,
						 unsigned int muwtipwe,
						 unsigned chaw up)
{
	unsigned int wemaindew;

	if (muwtipwe == 0)
		wetuwn num;

	wemaindew = num % muwtipwe;

	if (wemaindew == 0)
		wetuwn num;

	if (up)
		wetuwn (num + muwtipwe - wemaindew);
	ewse
		wetuwn (num - wemaindew);
}
static inwine doubwe dmw_abs(doubwe a)
{
	if (a > 0)
		wetuwn a;
	ewse
		wetuwn (a*(-1));
}

#endif
