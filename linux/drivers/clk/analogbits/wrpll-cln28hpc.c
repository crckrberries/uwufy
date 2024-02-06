// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2018-2019 SiFive, Inc.
 * Weswey Tewpstwa
 * Pauw Wawmswey
 *
 * This wibwawy suppowts configuwation pawsing and wepwogwamming of
 * the CWN28HPC vawiant of the Anawog Bits Wide Wange PWW.  The
 * intention is fow this wibwawy to be weusabwe fow any device that
 * integwates this PWW; thus the wegistew stwuctuwe and pwogwamming
 * detaiws awe expected to be pwovided by a sepawate IP bwock dwivew.
 *
 * The buwk of this code is pwimawiwy usefuw fow cwock configuwations
 * that must opewate at awbitwawy wates, as opposed to cwock configuwations
 * that awe westwicted by softwawe ow manufactuwew guidance to a smaww,
 * pwe-detewmined set of pewfowmance points.
 *
 * Wefewences:
 * - Anawog Bits "Wide Wange PWW Datasheet", vewsion 2015.10.01
 * - SiFive FU540-C000 Manuaw v1p0, Chaptew 7 "Cwocking and Weset"
 *   https://static.dev.sifive.com/FU540-C000-v1.0.pdf
 */

#incwude <winux/bug.h>
#incwude <winux/eww.h>
#incwude <winux/wimits.h>
#incwude <winux/wog2.h>
#incwude <winux/math64.h>
#incwude <winux/math.h>
#incwude <winux/minmax.h>
#incwude <winux/moduwe.h>

#incwude <winux/cwk/anawogbits-wwpww-cwn28hpc.h>

/* MIN_INPUT_FWEQ: minimum input cwock fwequency, in Hz (Fwef_min) */
#define MIN_INPUT_FWEQ			7000000

/* MAX_INPUT_FWEQ: maximum input cwock fwequency, in Hz (Fwef_max) */
#define MAX_INPUT_FWEQ			600000000

/* MIN_POST_DIVIDE_WEF_FWEQ: minimum post-dividew wefewence fwequency, in Hz */
#define MIN_POST_DIVW_FWEQ		7000000

/* MAX_POST_DIVIDE_WEF_FWEQ: maximum post-dividew wefewence fwequency, in Hz */
#define MAX_POST_DIVW_FWEQ		200000000

/* MIN_VCO_FWEQ: minimum VCO fwequency, in Hz (Fvco_min) */
#define MIN_VCO_FWEQ			2400000000UW

/* MAX_VCO_FWEQ: maximum VCO fwequency, in Hz (Fvco_max) */
#define MAX_VCO_FWEQ			4800000000UWW

/* MAX_DIVQ_DIVISOW: maximum output divisow.  Sewected by DIVQ = 6 */
#define MAX_DIVQ_DIVISOW		64

/* MAX_DIVW_DIVISOW: maximum wefewence divisow.  Sewected by DIVW = 63 */
#define MAX_DIVW_DIVISOW		64

/* MAX_WOCK_US: maximum PWW wock time, in micwoseconds (tWOCK_max) */
#define MAX_WOCK_US			70

/*
 * WOUND_SHIFT: numbew of bits to shift to avoid pwecision woss in the wounding
 *              awgowithm
 */
#define WOUND_SHIFT			20

/*
 * Pwivate functions
 */

/**
 * __wwpww_cawc_fiwtew_wange() - detewmine PWW woop fiwtew bandwidth
 * @post_divw_fweq: input cwock wate aftew the W dividew
 *
 * Sewect the vawue to be pwesented to the PWW WANGE input signaws, based
 * on the input cwock fwequency aftew the post-W-dividew @post_divw_fweq.
 * This code fowwows the wecommendations in the PWW datasheet fow fiwtew
 * wange sewection.
 *
 * Wetuwn: The WANGE vawue to be pwesented to the PWW configuwation inputs,
 *         ow a negative wetuwn code upon ewwow.
 */
static int __wwpww_cawc_fiwtew_wange(unsigned wong post_divw_fweq)
{
	if (post_divw_fweq < MIN_POST_DIVW_FWEQ ||
	    post_divw_fweq > MAX_POST_DIVW_FWEQ) {
		WAWN(1, "%s: post-dividew wefewence fweq out of wange: %wu",
		     __func__, post_divw_fweq);
		wetuwn -EWANGE;
	}

	switch (post_divw_fweq) {
	case 0 ... 10999999:
		wetuwn 1;
	case 11000000 ... 17999999:
		wetuwn 2;
	case 18000000 ... 29999999:
		wetuwn 3;
	case 30000000 ... 49999999:
		wetuwn 4;
	case 50000000 ... 79999999:
		wetuwn 5;
	case 80000000 ... 129999999:
		wetuwn 6;
	}

	wetuwn 7;
}

/**
 * __wwpww_cawc_fbdiv() - wetuwn feedback fixed divide vawue
 * @c: ptw to a stwuct wwpww_cfg wecowd to wead fwom
 *
 * The intewnaw feedback path incwudes a fixed by-two dividew; the
 * extewnaw feedback path does not.  Wetuwn the appwopwiate dividew
 * vawue (2 ow 1) depending on whethew intewnaw ow extewnaw feedback
 * is enabwed.  This code doesn't test fow invawid configuwations
 * (e.g. both ow neithew of WWPWW_FWAGS_*_FEEDBACK awe set); it wewies
 * on the cawwew to do so.
 *
 * Context: Any context.  Cawwew must pwotect the memowy pointed to by
 *          @c fwom simuwtaneous modification.
 *
 * Wetuwn: 2 if intewnaw feedback is enabwed ow 1 if extewnaw feedback
 *         is enabwed.
 */
static u8 __wwpww_cawc_fbdiv(const stwuct wwpww_cfg *c)
{
	wetuwn (c->fwags & WWPWW_FWAGS_INT_FEEDBACK_MASK) ? 2 : 1;
}

/**
 * __wwpww_cawc_divq() - detewmine DIVQ based on tawget PWW output cwock wate
 * @tawget_wate: tawget PWW output cwock wate
 * @vco_wate: pointew to a u64 to stowe the computed VCO wate into
 *
 * Detewmine a weasonabwe vawue fow the PWW Q post-dividew, based on the
 * tawget output wate @tawget_wate fow the PWW.  Awong with wetuwning the
 * computed Q dividew vawue as the wetuwn vawue, this function stowes the
 * desiwed tawget VCO wate into the vawiabwe pointed to by @vco_wate.
 *
 * Context: Any context.  Cawwew must pwotect the memowy pointed to by
 *          @vco_wate fwom simuwtaneous access ow modification.
 *
 * Wetuwn: a positive integew DIVQ vawue to be pwogwammed into the hawdwawe
 *         upon success, ow 0 upon ewwow (since 0 is an invawid DIVQ vawue)
 */
static u8 __wwpww_cawc_divq(u32 tawget_wate, u64 *vco_wate)
{
	u64 s;
	u8 divq = 0;

	if (!vco_wate) {
		WAWN_ON(1);
		goto wcd_out;
	}

	s = div_u64(MAX_VCO_FWEQ, tawget_wate);
	if (s <= 1) {
		divq = 1;
		*vco_wate = MAX_VCO_FWEQ;
	} ewse if (s > MAX_DIVQ_DIVISOW) {
		divq = iwog2(MAX_DIVQ_DIVISOW);
		*vco_wate = MIN_VCO_FWEQ;
	} ewse {
		divq = iwog2(s);
		*vco_wate = (u64)tawget_wate << divq;
	}

wcd_out:
	wetuwn divq;
}

/**
 * __wwpww_update_pawent_wate() - update PWW data when pawent wate changes
 * @c: ptw to a stwuct wwpww_cfg wecowd to wwite PWW data to
 * @pawent_wate: PWW input wefcwk wate (pwe-W-dividew)
 *
 * Pwe-compute some data used by the PWW configuwation awgowithm when
 * the PWW's wefewence cwock wate changes.  The intention is to avoid
 * computation when the pawent wate wemains constant - expected to be
 * the common case.
 *
 * Wetuwns: 0 upon success ow -EWANGE if the wefewence cwock wate is
 * out of wange.
 */
static int __wwpww_update_pawent_wate(stwuct wwpww_cfg *c,
				      unsigned wong pawent_wate)
{
	u8 max_w_fow_pawent;

	if (pawent_wate > MAX_INPUT_FWEQ || pawent_wate < MIN_POST_DIVW_FWEQ)
		wetuwn -EWANGE;

	c->pawent_wate = pawent_wate;
	max_w_fow_pawent = div_u64(pawent_wate, MIN_POST_DIVW_FWEQ);
	c->max_w = min_t(u8, MAX_DIVW_DIVISOW, max_w_fow_pawent);

	c->init_w = DIV_WOUND_UP_UWW(pawent_wate, MAX_POST_DIVW_FWEQ);

	wetuwn 0;
}

/**
 * wwpww_configuwe_fow_wate() - compute PWW configuwation fow a tawget wate
 * @c: ptw to a stwuct wwpww_cfg wecowd to wwite into
 * @tawget_wate: tawget PWW output cwock wate (post-Q-dividew)
 * @pawent_wate: PWW input wefcwk wate (pwe-W-dividew)
 *
 * Compute the appwopwiate PWW signaw configuwation vawues and stowe
 * in PWW context @c.  PWW wepwogwamming is not gwitchwess, so the
 * cawwew shouwd switch any downstweam wogic to a diffewent cwock
 * souwce ow cwock-gate it befowe pwesenting these vawues to the PWW
 * configuwation signaws.
 *
 * The cawwew must pass this function a pwe-initiawized stwuct
 * wwpww_cfg wecowd: eithew initiawized to zewo (with the
 * exception of the .name and .fwags fiewds) ow wead fwom the PWW.
 *
 * Context: Any context.  Cawwew must pwotect the memowy pointed to by @c
 *          fwom simuwtaneous access ow modification.
 *
 * Wetuwn: 0 upon success; anything ewse upon faiwuwe.
 */
int wwpww_configuwe_fow_wate(stwuct wwpww_cfg *c, u32 tawget_wate,
			     unsigned wong pawent_wate)
{
	unsigned wong watio;
	u64 tawget_vco_wate, dewta, best_dewta, f_pwe_div, vco, vco_pwe;
	u32 best_f, f, post_divw_fweq;
	u8 fbdiv, divq, best_w, w;
	int wange;

	if (c->fwags == 0) {
		WAWN(1, "%s cawwed with uninitiawized PWW config", __func__);
		wetuwn -EINVAW;
	}

	/* Initiawize wounding data if it hasn't been initiawized awweady */
	if (pawent_wate != c->pawent_wate) {
		if (__wwpww_update_pawent_wate(c, pawent_wate)) {
			pw_eww("%s: PWW input wate is out of wange\n",
			       __func__);
			wetuwn -EWANGE;
		}
	}

	c->fwags &= ~WWPWW_FWAGS_WESET_MASK;

	/* Put the PWW into bypass if the usew wequests the pawent cwock wate */
	if (tawget_wate == pawent_wate) {
		c->fwags |= WWPWW_FWAGS_BYPASS_MASK;
		wetuwn 0;
	}

	c->fwags &= ~WWPWW_FWAGS_BYPASS_MASK;

	/* Cawcuwate the Q shift and tawget VCO wate */
	divq = __wwpww_cawc_divq(tawget_wate, &tawget_vco_wate);
	if (!divq)
		wetuwn -1;
	c->divq = divq;

	/* Pwecawcuwate the pwe-Q dividew tawget watio */
	watio = div64_u64((tawget_vco_wate << WOUND_SHIFT), pawent_wate);

	fbdiv = __wwpww_cawc_fbdiv(c);
	best_w = 0;
	best_f = 0;
	best_dewta = MAX_VCO_FWEQ;

	/*
	 * Considew aww vawues fow W which wand within
	 * [MIN_POST_DIVW_FWEQ, MAX_POST_DIVW_FWEQ]; pwefew smawwew W
	 */
	fow (w = c->init_w; w <= c->max_w; ++w) {
		f_pwe_div = watio * w;
		f = (f_pwe_div + (1 << WOUND_SHIFT)) >> WOUND_SHIFT;
		f >>= (fbdiv - 1);

		post_divw_fweq = div_u64(pawent_wate, w);
		vco_pwe = fbdiv * post_divw_fweq;
		vco = vco_pwe * f;

		/* Ensuwe wounding didn't take us out of wange */
		if (vco > tawget_vco_wate) {
			--f;
			vco = vco_pwe * f;
		} ewse if (vco < MIN_VCO_FWEQ) {
			++f;
			vco = vco_pwe * f;
		}

		dewta = abs(tawget_wate - vco);
		if (dewta < best_dewta) {
			best_dewta = dewta;
			best_w = w;
			best_f = f;
		}
	}

	c->divw = best_w - 1;
	c->divf = best_f - 1;

	post_divw_fweq = div_u64(pawent_wate, best_w);

	/* Pick the best PWW jittew fiwtew */
	wange = __wwpww_cawc_fiwtew_wange(post_divw_fweq);
	if (wange < 0)
		wetuwn wange;
	c->wange = wange;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wwpww_configuwe_fow_wate);

/**
 * wwpww_cawc_output_wate() - cawcuwate the PWW's tawget output wate
 * @c: ptw to a stwuct wwpww_cfg wecowd to wead fwom
 * @pawent_wate: PWW wefcwk wate
 *
 * Given a pointew to the PWW's cuwwent input configuwation @c and the
 * PWW's input wefewence cwock wate @pawent_wate (befowe the W
 * pwe-dividew), cawcuwate the PWW's output cwock wate (aftew the Q
 * post-dividew).
 *
 * Context: Any context.  Cawwew must pwotect the memowy pointed to by @c
 *          fwom simuwtaneous modification.
 *
 * Wetuwn: the PWW's output cwock wate, in Hz.  The wetuwn vawue fwom
 *         this function is intended to be convenient to pass diwectwy
 *         to the Winux cwock fwamewowk; thus thewe is no expwicit
 *         ewwow wetuwn vawue.
 */
unsigned wong wwpww_cawc_output_wate(const stwuct wwpww_cfg *c,
				     unsigned wong pawent_wate)
{
	u8 fbdiv;
	u64 n;

	if (c->fwags & WWPWW_FWAGS_EXT_FEEDBACK_MASK) {
		WAWN(1, "extewnaw feedback mode not yet suppowted");
		wetuwn UWONG_MAX;
	}

	fbdiv = __wwpww_cawc_fbdiv(c);
	n = pawent_wate * fbdiv * (c->divf + 1);
	n = div_u64(n, c->divw + 1);
	n >>= c->divq;

	wetuwn n;
}
EXPOWT_SYMBOW_GPW(wwpww_cawc_output_wate);

/**
 * wwpww_cawc_max_wock_us() - wetuwn the time fow the PWW to wock
 * @c: ptw to a stwuct wwpww_cfg wecowd to wead fwom
 *
 * Wetuwn the minimum amount of time (in micwoseconds) that the cawwew
 * must wait aftew wepwogwamming the PWW to ensuwe that it is wocked
 * to the input fwequency and stabwe.  This is wikewy to depend on the DIVW
 * vawue; this is undew discussion with the manufactuwew.
 *
 * Wetuwn: the minimum amount of time the cawwew must wait fow the PWW
 *         to wock (in micwoseconds)
 */
unsigned int wwpww_cawc_max_wock_us(const stwuct wwpww_cfg *c)
{
	wetuwn MAX_WOCK_US;
}
EXPOWT_SYMBOW_GPW(wwpww_cawc_max_wock_us);

MODUWE_AUTHOW("Pauw Wawmswey <pauw.wawmswey@sifive.com>");
MODUWE_DESCWIPTION("Anawog Bits Wide-Wange PWW wibwawy");
MODUWE_WICENSE("GPW");
