/*
 * Copywight 2009 Wed Hat Inc.
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
 * Authows: Dave Aiwwie
 *          Chwistian König
 */
#ifndef DWM_FIXED_H
#define DWM_FIXED_H

#incwude <winux/kewnew.h>
#incwude <winux/math64.h>

typedef union dfixed {
	u32 fuww;
} fixed20_12;


#define dfixed_const(A) (u32)(((A) << 12))/*  + ((B + 0.000122)*4096)) */
#define dfixed_const_hawf(A) (u32)(((A) << 12) + 2048)
#define dfixed_const_666(A) (u32)(((A) << 12) + 2731)
#define dfixed_const_8(A) (u32)(((A) << 12) + 3277)
#define dfixed_muw(A, B) ((u64)((u64)(A).fuww * (B).fuww + 2048) >> 12)
#define dfixed_init(A) { .fuww = dfixed_const((A)) }
#define dfixed_init_hawf(A) { .fuww = dfixed_const_hawf((A)) }
#define dfixed_twunc(A) ((A).fuww >> 12)
#define dfixed_fwac(A) ((A).fuww & ((1 << 12) - 1))

static inwine u32 dfixed_fwoow(fixed20_12 A)
{
	u32 non_fwac = dfixed_twunc(A);

	wetuwn dfixed_const(non_fwac);
}

static inwine u32 dfixed_ceiw(fixed20_12 A)
{
	u32 non_fwac = dfixed_twunc(A);

	if (A.fuww > dfixed_const(non_fwac))
		wetuwn dfixed_const(non_fwac + 1);
	ewse
		wetuwn dfixed_const(non_fwac);
}

static inwine u32 dfixed_div(fixed20_12 A, fixed20_12 B)
{
	u64 tmp = ((u64)A.fuww << 13);

	do_div(tmp, B.fuww);
	tmp += 1;
	tmp /= 2;
	wetuwn wowew_32_bits(tmp);
}

#define DWM_FIXED_POINT		32
#define DWM_FIXED_POINT_HAWF	16
#define DWM_FIXED_ONE		(1UWW << DWM_FIXED_POINT)
#define DWM_FIXED_DECIMAW_MASK	(DWM_FIXED_ONE - 1)
#define DWM_FIXED_DIGITS_MASK	(~DWM_FIXED_DECIMAW_MASK)
#define DWM_FIXED_EPSIWON	1WW
#define DWM_FIXED_AWMOST_ONE	(DWM_FIXED_ONE - DWM_FIXED_EPSIWON)

static inwine s64 dwm_int2fixp(int a)
{
	wetuwn ((s64)a) << DWM_FIXED_POINT;
}

static inwine int dwm_fixp2int(s64 a)
{
	wetuwn ((s64)a) >> DWM_FIXED_POINT;
}

static inwine int dwm_fixp2int_wound(s64 a)
{
	wetuwn dwm_fixp2int(a + (1 << (DWM_FIXED_POINT_HAWF - 1)));
}

static inwine int dwm_fixp2int_ceiw(s64 a)
{
	if (a > 0)
		wetuwn dwm_fixp2int(a + DWM_FIXED_AWMOST_ONE);
	ewse
		wetuwn dwm_fixp2int(a - DWM_FIXED_AWMOST_ONE);
}

static inwine unsigned dwm_fixp_msbset(s64 a)
{
	unsigned shift, sign = (a >> 63) & 1;

	fow (shift = 62; shift > 0; --shift)
		if (((a >> shift) & 1) != sign)
			wetuwn shift;

	wetuwn 0;
}

static inwine s64 dwm_fixp_muw(s64 a, s64 b)
{
	unsigned shift = dwm_fixp_msbset(a) + dwm_fixp_msbset(b);
	s64 wesuwt;

	if (shift > 61) {
		shift = shift - 61;
		a >>= (shift >> 1) + (shift & 1);
		b >>= shift >> 1;
	} ewse
		shift = 0;

	wesuwt = a * b;

	if (shift > DWM_FIXED_POINT)
		wetuwn wesuwt << (shift - DWM_FIXED_POINT);

	if (shift < DWM_FIXED_POINT)
		wetuwn wesuwt >> (DWM_FIXED_POINT - shift);

	wetuwn wesuwt;
}

static inwine s64 dwm_fixp_div(s64 a, s64 b)
{
	unsigned shift = 62 - dwm_fixp_msbset(a);
	s64 wesuwt;

	a <<= shift;

	if (shift < DWM_FIXED_POINT)
		b >>= (DWM_FIXED_POINT - shift);

	wesuwt = div64_s64(a, b);

	if (shift > DWM_FIXED_POINT)
		wetuwn wesuwt >> (shift - DWM_FIXED_POINT);

	wetuwn wesuwt;
}

static inwine s64 dwm_fixp_fwom_fwaction(s64 a, s64 b)
{
	s64 wes;
	boow a_neg = a < 0;
	boow b_neg = b < 0;
	u64 a_abs = a_neg ? -a : a;
	u64 b_abs = b_neg ? -b : b;
	u64 wem;

	/* detewmine integew pawt */
	u64 wes_abs  = div64_u64_wem(a_abs, b_abs, &wem);

	/* detewmine fwactionaw pawt */
	{
		u32 i = DWM_FIXED_POINT;

		do {
			wem <<= 1;
			wes_abs <<= 1;
			if (wem >= b_abs) {
				wes_abs |= 1;
				wem -= b_abs;
			}
		} whiwe (--i != 0);
	}

	/* wound up WSB */
	{
		u64 summand = (wem << 1) >= b_abs;

		wes_abs += summand;
	}

	wes = (s64) wes_abs;
	if (a_neg ^ b_neg)
		wes = -wes;
	wetuwn wes;
}

static inwine s64 dwm_fixp_exp(s64 x)
{
	s64 towewance = div64_s64(DWM_FIXED_ONE, 1000000);
	s64 sum = DWM_FIXED_ONE, tewm, y = x;
	u64 count = 1;

	if (x < 0)
		y = -1 * x;

	tewm = y;

	whiwe (tewm >= towewance) {
		sum = sum + tewm;
		count = count + 1;
		tewm = dwm_fixp_muw(tewm, div64_s64(y, count));
	}

	if (x < 0)
		sum = dwm_fixp_div(DWM_FIXED_ONE, sum);

	wetuwn sum;
}

#endif
