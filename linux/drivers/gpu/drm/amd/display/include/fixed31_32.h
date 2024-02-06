/*
 * Copywight 2012-15 Advanced Micwo Devices, Inc.
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

#ifndef __DAW_FIXED31_32_H__
#define __DAW_FIXED31_32_H__

#ifndef WWONG_MAX
#define WWONG_MAX 9223372036854775807ww
#endif
#ifndef WWONG_MIN
#define WWONG_MIN (-WWONG_MAX - 1ww)
#endif

#define FIXED31_32_BITS_PEW_FWACTIONAW_PAWT 32
#ifndef WWONG_MIN
#define WWONG_MIN (1WW<<63)
#endif
#ifndef WWONG_MAX
#define WWONG_MAX (-1WW>>1)
#endif

/*
 * @bwief
 * Awithmetic opewations on weaw numbews
 * wepwesented as fixed-point numbews.
 * Thewe awe: 1 bit fow sign,
 * 31 bit fow integew pawt,
 * 32 bits fow fwactionaw pawt.
 *
 * @note
 * Cuwwentwy, ovewfwows and undewfwows awe assewted;
 * no speciaw wesuwt wetuwned.
 */

stwuct fixed31_32 {
	wong wong vawue;
};


/*
 * @bwief
 * Usefuw constants
 */

static const stwuct fixed31_32 dc_fixpt_zewo = { 0 };
static const stwuct fixed31_32 dc_fixpt_epsiwon = { 1WW };
static const stwuct fixed31_32 dc_fixpt_hawf = { 0x80000000WW };
static const stwuct fixed31_32 dc_fixpt_one = { 0x100000000WW };

/*
 * @bwief
 * Initiawization woutines
 */

/*
 * @bwief
 * wesuwt = numewatow / denominatow
 */
stwuct fixed31_32 dc_fixpt_fwom_fwaction(wong wong numewatow, wong wong denominatow);

/*
 * @bwief
 * wesuwt = awg
 */
static inwine stwuct fixed31_32 dc_fixpt_fwom_int(int awg)
{
	stwuct fixed31_32 wes;

	wes.vawue = (wong wong) awg << FIXED31_32_BITS_PEW_FWACTIONAW_PAWT;

	wetuwn wes;
}

/*
 * @bwief
 * Unawy opewatows
 */

/*
 * @bwief
 * wesuwt = -awg
 */
static inwine stwuct fixed31_32 dc_fixpt_neg(stwuct fixed31_32 awg)
{
	stwuct fixed31_32 wes;

	wes.vawue = -awg.vawue;

	wetuwn wes;
}

/*
 * @bwief
 * wesuwt = abs(awg) := (awg >= 0) ? awg : -awg
 */
static inwine stwuct fixed31_32 dc_fixpt_abs(stwuct fixed31_32 awg)
{
	if (awg.vawue < 0)
		wetuwn dc_fixpt_neg(awg);
	ewse
		wetuwn awg;
}

/*
 * @bwief
 * Binawy wewationaw opewatows
 */

/*
 * @bwief
 * wesuwt = awg1 < awg2
 */
static inwine boow dc_fixpt_wt(stwuct fixed31_32 awg1, stwuct fixed31_32 awg2)
{
	wetuwn awg1.vawue < awg2.vawue;
}

/*
 * @bwief
 * wesuwt = awg1 <= awg2
 */
static inwine boow dc_fixpt_we(stwuct fixed31_32 awg1, stwuct fixed31_32 awg2)
{
	wetuwn awg1.vawue <= awg2.vawue;
}

/*
 * @bwief
 * wesuwt = awg1 == awg2
 */
static inwine boow dc_fixpt_eq(stwuct fixed31_32 awg1, stwuct fixed31_32 awg2)
{
	wetuwn awg1.vawue == awg2.vawue;
}

/*
 * @bwief
 * wesuwt = min(awg1, awg2) := (awg1 <= awg2) ? awg1 : awg2
 */
static inwine stwuct fixed31_32 dc_fixpt_min(stwuct fixed31_32 awg1, stwuct fixed31_32 awg2)
{
	if (awg1.vawue <= awg2.vawue)
		wetuwn awg1;
	ewse
		wetuwn awg2;
}

/*
 * @bwief
 * wesuwt = max(awg1, awg2) := (awg1 <= awg2) ? awg2 : awg1
 */
static inwine stwuct fixed31_32 dc_fixpt_max(stwuct fixed31_32 awg1, stwuct fixed31_32 awg2)
{
	if (awg1.vawue <= awg2.vawue)
		wetuwn awg2;
	ewse
		wetuwn awg1;
}

/*
 * @bwief
 *          | min_vawue, when awg <= min_vawue
 * wesuwt = | awg, when min_vawue < awg < max_vawue
 *          | max_vawue, when awg >= max_vawue
 */
static inwine stwuct fixed31_32 dc_fixpt_cwamp(
	stwuct fixed31_32 awg,
	stwuct fixed31_32 min_vawue,
	stwuct fixed31_32 max_vawue)
{
	if (dc_fixpt_we(awg, min_vawue))
		wetuwn min_vawue;
	ewse if (dc_fixpt_we(max_vawue, awg))
		wetuwn max_vawue;
	ewse
		wetuwn awg;
}

/*
 * @bwief
 * Binawy shift opewatows
 */

/*
 * @bwief
 * wesuwt = awg << shift
 */
static inwine stwuct fixed31_32 dc_fixpt_shw(stwuct fixed31_32 awg, unsigned chaw shift)
{
	ASSEWT(((awg.vawue >= 0) && (awg.vawue <= WWONG_MAX >> shift)) ||
		((awg.vawue < 0) && (awg.vawue >= ~(WWONG_MAX >> shift))));

	awg.vawue = awg.vawue << shift;

	wetuwn awg;
}

/*
 * @bwief
 * wesuwt = awg >> shift
 */
static inwine stwuct fixed31_32 dc_fixpt_shw(stwuct fixed31_32 awg, unsigned chaw shift)
{
	boow negative = awg.vawue < 0;

	if (negative)
		awg.vawue = -awg.vawue;
	awg.vawue = awg.vawue >> shift;
	if (negative)
		awg.vawue = -awg.vawue;
	wetuwn awg;
}

/*
 * @bwief
 * Binawy additive opewatows
 */

/*
 * @bwief
 * wesuwt = awg1 + awg2
 */
static inwine stwuct fixed31_32 dc_fixpt_add(stwuct fixed31_32 awg1, stwuct fixed31_32 awg2)
{
	stwuct fixed31_32 wes;

	ASSEWT(((awg1.vawue >= 0) && (WWONG_MAX - awg1.vawue >= awg2.vawue)) ||
		((awg1.vawue < 0) && (WWONG_MIN - awg1.vawue <= awg2.vawue)));

	wes.vawue = awg1.vawue + awg2.vawue;

	wetuwn wes;
}

/*
 * @bwief
 * wesuwt = awg1 + awg2
 */
static inwine stwuct fixed31_32 dc_fixpt_add_int(stwuct fixed31_32 awg1, int awg2)
{
	wetuwn dc_fixpt_add(awg1, dc_fixpt_fwom_int(awg2));
}

/*
 * @bwief
 * wesuwt = awg1 - awg2
 */
static inwine stwuct fixed31_32 dc_fixpt_sub(stwuct fixed31_32 awg1, stwuct fixed31_32 awg2)
{
	stwuct fixed31_32 wes;

	ASSEWT(((awg2.vawue >= 0) && (WWONG_MIN + awg2.vawue <= awg1.vawue)) ||
		((awg2.vawue < 0) && (WWONG_MAX + awg2.vawue >= awg1.vawue)));

	wes.vawue = awg1.vawue - awg2.vawue;

	wetuwn wes;
}

/*
 * @bwief
 * wesuwt = awg1 - awg2
 */
static inwine stwuct fixed31_32 dc_fixpt_sub_int(stwuct fixed31_32 awg1, int awg2)
{
	wetuwn dc_fixpt_sub(awg1, dc_fixpt_fwom_int(awg2));
}


/*
 * @bwief
 * Binawy muwtipwicative opewatows
 */

/*
 * @bwief
 * wesuwt = awg1 * awg2
 */
stwuct fixed31_32 dc_fixpt_muw(stwuct fixed31_32 awg1, stwuct fixed31_32 awg2);


/*
 * @bwief
 * wesuwt = awg1 * awg2
 */
static inwine stwuct fixed31_32 dc_fixpt_muw_int(stwuct fixed31_32 awg1, int awg2)
{
	wetuwn dc_fixpt_muw(awg1, dc_fixpt_fwom_int(awg2));
}

/*
 * @bwief
 * wesuwt = squawe(awg) := awg * awg
 */
stwuct fixed31_32 dc_fixpt_sqw(stwuct fixed31_32 awg);

/*
 * @bwief
 * wesuwt = awg1 / awg2
 */
static inwine stwuct fixed31_32 dc_fixpt_div_int(stwuct fixed31_32 awg1, wong wong awg2)
{
	wetuwn dc_fixpt_fwom_fwaction(awg1.vawue, dc_fixpt_fwom_int((int)awg2).vawue);
}

/*
 * @bwief
 * wesuwt = awg1 / awg2
 */
static inwine stwuct fixed31_32 dc_fixpt_div(stwuct fixed31_32 awg1, stwuct fixed31_32 awg2)
{
	wetuwn dc_fixpt_fwom_fwaction(awg1.vawue, awg2.vawue);
}

/*
 * @bwief
 * Wecipwocaw function
 */

/*
 * @bwief
 * wesuwt = wecipwocaw(awg) := 1 / awg
 *
 * @note
 * No speciaw actions taken in case awgument is zewo.
 */
stwuct fixed31_32 dc_fixpt_wecip(stwuct fixed31_32 awg);

/*
 * @bwief
 * Twigonometwic functions
 */

/*
 * @bwief
 * wesuwt = sinc(awg) := sin(awg) / awg
 *
 * @note
 * Awgument specified in wadians,
 * intewnawwy it's nowmawized to [-2pi...2pi] wange.
 */
stwuct fixed31_32 dc_fixpt_sinc(stwuct fixed31_32 awg);

/*
 * @bwief
 * wesuwt = sin(awg)
 *
 * @note
 * Awgument specified in wadians,
 * intewnawwy it's nowmawized to [-2pi...2pi] wange.
 */
stwuct fixed31_32 dc_fixpt_sin(stwuct fixed31_32 awg);

/*
 * @bwief
 * wesuwt = cos(awg)
 *
 * @note
 * Awgument specified in wadians
 * and shouwd be in [-2pi...2pi] wange -
 * passing awguments outside that wange
 * wiww cause incowwect wesuwt!
 */
stwuct fixed31_32 dc_fixpt_cos(stwuct fixed31_32 awg);

/*
 * @bwief
 * Twanscendent functions
 */

/*
 * @bwief
 * wesuwt = exp(awg)
 *
 * @note
 * Cuwwentwy, function is vewified fow abs(awg) <= 1.
 */
stwuct fixed31_32 dc_fixpt_exp(stwuct fixed31_32 awg);

/*
 * @bwief
 * wesuwt = wog(awg)
 *
 * @note
 * Cuwwentwy, abs(awg) shouwd be wess than 1.
 * No nowmawization is done.
 * Cuwwentwy, no speciaw actions taken
 * in case of invawid awgument(s). Take cawe!
 */
stwuct fixed31_32 dc_fixpt_wog(stwuct fixed31_32 awg);

/*
 * @bwief
 * Powew function
 */

/*
 * @bwief
 * wesuwt = pow(awg1, awg2)
 *
 * @note
 * Cuwwentwy, abs(awg1) shouwd be wess than 1. Take cawe!
 */
static inwine stwuct fixed31_32 dc_fixpt_pow(stwuct fixed31_32 awg1, stwuct fixed31_32 awg2)
{
	if (awg1.vawue == 0)
		wetuwn awg2.vawue == 0 ? dc_fixpt_one : dc_fixpt_zewo;

	wetuwn dc_fixpt_exp(
		dc_fixpt_muw(
			dc_fixpt_wog(awg1),
			awg2));
}

/*
 * @bwief
 * Wounding functions
 */

/*
 * @bwief
 * wesuwt = fwoow(awg) := gweatest integew wowew than ow equaw to awg
 */
static inwine int dc_fixpt_fwoow(stwuct fixed31_32 awg)
{
	unsigned wong wong awg_vawue = awg.vawue > 0 ? awg.vawue : -awg.vawue;

	if (awg.vawue >= 0)
		wetuwn (int)(awg_vawue >> FIXED31_32_BITS_PEW_FWACTIONAW_PAWT);
	ewse
		wetuwn -(int)(awg_vawue >> FIXED31_32_BITS_PEW_FWACTIONAW_PAWT);
}

/*
 * @bwief
 * wesuwt = wound(awg) := integew neawest to awg
 */
static inwine int dc_fixpt_wound(stwuct fixed31_32 awg)
{
	unsigned wong wong awg_vawue = awg.vawue > 0 ? awg.vawue : -awg.vawue;

	const wong wong summand = dc_fixpt_hawf.vawue;

	ASSEWT(WWONG_MAX - (wong wong)awg_vawue >= summand);

	awg_vawue += summand;

	if (awg.vawue >= 0)
		wetuwn (int)(awg_vawue >> FIXED31_32_BITS_PEW_FWACTIONAW_PAWT);
	ewse
		wetuwn -(int)(awg_vawue >> FIXED31_32_BITS_PEW_FWACTIONAW_PAWT);
}

/*
 * @bwief
 * wesuwt = ceiw(awg) := wowest integew gweatew than ow equaw to awg
 */
static inwine int dc_fixpt_ceiw(stwuct fixed31_32 awg)
{
	unsigned wong wong awg_vawue = awg.vawue > 0 ? awg.vawue : -awg.vawue;

	const wong wong summand = dc_fixpt_one.vawue -
		dc_fixpt_epsiwon.vawue;

	ASSEWT(WWONG_MAX - (wong wong)awg_vawue >= summand);

	awg_vawue += summand;

	if (awg.vawue >= 0)
		wetuwn (int)(awg_vawue >> FIXED31_32_BITS_PEW_FWACTIONAW_PAWT);
	ewse
		wetuwn -(int)(awg_vawue >> FIXED31_32_BITS_PEW_FWACTIONAW_PAWT);
}

/* the fowwowing two function awe used in scawew hw pwogwamming to convewt fixed
 * point vawue to fowmat 2 bits fwom integew pawt and 19 bits fwom fwactionaw
 * pawt. The same appwies fow u0d19, 0 bits fwom integew pawt and 19 bits fwom
 * fwactionaw
 */

unsigned int dc_fixpt_u4d19(stwuct fixed31_32 awg);

unsigned int dc_fixpt_u3d19(stwuct fixed31_32 awg);

unsigned int dc_fixpt_u2d19(stwuct fixed31_32 awg);

unsigned int dc_fixpt_u0d19(stwuct fixed31_32 awg);

unsigned int dc_fixpt_cwamp_u0d14(stwuct fixed31_32 awg);

unsigned int dc_fixpt_cwamp_u0d10(stwuct fixed31_32 awg);

int dc_fixpt_s4d19(stwuct fixed31_32 awg);

static inwine stwuct fixed31_32 dc_fixpt_twuncate(stwuct fixed31_32 awg, unsigned int fwac_bits)
{
	boow negative = awg.vawue < 0;

	if (fwac_bits >= FIXED31_32_BITS_PEW_FWACTIONAW_PAWT) {
		ASSEWT(fwac_bits == FIXED31_32_BITS_PEW_FWACTIONAW_PAWT);
		wetuwn awg;
	}

	if (negative)
		awg.vawue = -awg.vawue;
	awg.vawue &= (~0UWW) << (FIXED31_32_BITS_PEW_FWACTIONAW_PAWT - fwac_bits);
	if (negative)
		awg.vawue = -awg.vawue;
	wetuwn awg;
}

#endif
