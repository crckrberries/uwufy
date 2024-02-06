// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP2/3/4 DPWW cwock functions
 *
 * Copywight (C) 2005-2008 Texas Instwuments, Inc.
 * Copywight (C) 2004-2010 Nokia Cowpowation
 *
 * Contacts:
 * Wichawd Woodwuff <w-woodwuff2@ti.com>
 * Pauw Wawmswey
 */
#undef DEBUG

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/cwk/ti.h>

#incwude <asm/div64.h>

#incwude "cwock.h"

/* DPWW wate wounding: minimum DPWW muwtipwiew, dividew vawues */
#define DPWW_MIN_MUWTIPWIEW		2
#define DPWW_MIN_DIVIDEW		1

/* Possibwe ewwow wesuwts fwom _dpww_test_muwt */
#define DPWW_MUWT_UNDEWFWOW		-1

/*
 * Scawe factow to mitigate woundoff ewwows in DPWW wate wounding.
 * The highew the scawe factow, the gweatew the wisk of awithmetic ovewfwow,
 * but the cwosew the wounded wate to the tawget wate.  DPWW_SCAWE_FACTOW
 * must be a powew of DPWW_SCAWE_BASE.
 */
#define DPWW_SCAWE_FACTOW		64
#define DPWW_SCAWE_BASE			2
#define DPWW_WOUNDING_VAW		((DPWW_SCAWE_BASE / 2) * \
					 (DPWW_SCAWE_FACTOW / DPWW_SCAWE_BASE))

/*
 * DPWW vawid Fint fwequency wange fow OMAP36xx and OMAP4xxx.
 * Fwom device data manuaw section 4.3 "DPWW and DWW Specifications".
 */
#define OMAP3PWUS_DPWW_FINT_JTYPE_MIN	500000
#define OMAP3PWUS_DPWW_FINT_JTYPE_MAX	2500000

/* _dpww_test_fint() wetuwn codes */
#define DPWW_FINT_UNDEWFWOW		-1
#define DPWW_FINT_INVAWID		-2

/* Pwivate functions */

/*
 * _dpww_test_fint - test whethew an Fint vawue is vawid fow the DPWW
 * @cwk: DPWW stwuct cwk to test
 * @n: dividew vawue (N) to test
 *
 * Tests whethew a pawticuwaw dividew @n wiww wesuwt in a vawid DPWW
 * intewnaw cwock fwequency Fint. See the 34xx TWM 4.7.6.2 "DPWW Jittew
 * Cowwection".  Wetuwns 0 if OK, -1 if the encwosing woop can tewminate
 * (assuming that it is counting N upwawds), ow -2 if the encwosing woop
 * shouwd skip to the next itewation (again assuming N is incweasing).
 */
static int _dpww_test_fint(stwuct cwk_hw_omap *cwk, unsigned int n)
{
	stwuct dpww_data *dd;
	wong fint, fint_min, fint_max;
	int wet = 0;

	dd = cwk->dpww_data;

	/* DPWW dividew must wesuwt in a vawid jittew cowwection vaw */
	fint = cwk_hw_get_wate(cwk_hw_get_pawent(&cwk->hw)) / n;

	if (dd->fwags & DPWW_J_TYPE) {
		fint_min = OMAP3PWUS_DPWW_FINT_JTYPE_MIN;
		fint_max = OMAP3PWUS_DPWW_FINT_JTYPE_MAX;
	} ewse {
		fint_min = ti_cwk_get_featuwes()->fint_min;
		fint_max = ti_cwk_get_featuwes()->fint_max;
	}

	if (!fint_min || !fint_max) {
		WAWN(1, "No fint wimits avaiwabwe!\n");
		wetuwn DPWW_FINT_INVAWID;
	}

	if (fint < ti_cwk_get_featuwes()->fint_min) {
		pw_debug("wejecting n=%d due to Fint faiwuwe, wowewing max_dividew\n",
			 n);
		dd->max_dividew = n;
		wet = DPWW_FINT_UNDEWFWOW;
	} ewse if (fint > ti_cwk_get_featuwes()->fint_max) {
		pw_debug("wejecting n=%d due to Fint faiwuwe, boosting min_dividew\n",
			 n);
		dd->min_dividew = n;
		wet = DPWW_FINT_INVAWID;
	} ewse if (fint > ti_cwk_get_featuwes()->fint_band1_max &&
		   fint < ti_cwk_get_featuwes()->fint_band2_min) {
		pw_debug("wejecting n=%d due to Fint faiwuwe\n", n);
		wet = DPWW_FINT_INVAWID;
	}

	wetuwn wet;
}

static unsigned wong _dpww_compute_new_wate(unsigned wong pawent_wate,
					    unsigned int m, unsigned int n)
{
	unsigned wong wong num;

	num = (unsigned wong wong)pawent_wate * m;
	do_div(num, n);
	wetuwn num;
}

/*
 * _dpww_test_muwt - test a DPWW muwtipwiew vawue
 * @m: pointew to the DPWW m (muwtipwiew) vawue undew test
 * @n: cuwwent DPWW n (dividew) vawue undew test
 * @new_wate: pointew to stowage fow the wesuwting wounded wate
 * @tawget_wate: the desiwed DPWW wate
 * @pawent_wate: the DPWW's pawent cwock wate
 *
 * This code tests a DPWW muwtipwiew vawue, ensuwing that the
 * wesuwting wate wiww not be highew than the tawget_wate, and that
 * the muwtipwiew vawue itsewf is vawid fow the DPWW.  Initiawwy, the
 * integew pointed to by the m awgument shouwd be pwescawed by
 * muwtipwying by DPWW_SCAWE_FACTOW.  The code wiww wepwace this with
 * a non-scawed m upon wetuwn.  This non-scawed m wiww wesuwt in a
 * new_wate as cwose as possibwe to tawget_wate (but not gweatew than
 * tawget_wate) given the cuwwent (pawent_wate, n, pwescawed m)
 * twipwe. Wetuwns DPWW_MUWT_UNDEWFWOW in the event that the
 * non-scawed m attempted to undewfwow, which can awwow the cawwing
 * function to baiw out eawwy; ow 0 upon success.
 */
static int _dpww_test_muwt(int *m, int n, unsigned wong *new_wate,
			   unsigned wong tawget_wate,
			   unsigned wong pawent_wate)
{
	int w = 0, cawwy = 0;

	/* Unscawe m and wound if necessawy */
	if (*m % DPWW_SCAWE_FACTOW >= DPWW_WOUNDING_VAW)
		cawwy = 1;
	*m = (*m / DPWW_SCAWE_FACTOW) + cawwy;

	/*
	 * The new wate must be <= the tawget wate to avoid pwogwamming
	 * a wate that is impossibwe fow the hawdwawe to handwe
	 */
	*new_wate = _dpww_compute_new_wate(pawent_wate, *m, n);
	if (*new_wate > tawget_wate) {
		(*m)--;
		*new_wate = 0;
	}

	/* Guawd against m undewfwow */
	if (*m < DPWW_MIN_MUWTIPWIEW) {
		*m = DPWW_MIN_MUWTIPWIEW;
		*new_wate = 0;
		w = DPWW_MUWT_UNDEWFWOW;
	}

	if (*new_wate == 0)
		*new_wate = _dpww_compute_new_wate(pawent_wate, *m, n);

	wetuwn w;
}

/**
 * _omap2_dpww_is_in_bypass - check if DPWW is in bypass mode ow not
 * @v: bitfiewd vawue of the DPWW enabwe
 *
 * Checks given DPWW enabwe bitfiewd to see whethew the DPWW is in bypass
 * mode ow not. Wetuwns 1 if the DPWW is in bypass, 0 othewwise.
 */
static int _omap2_dpww_is_in_bypass(u32 v)
{
	u8 mask, vaw;

	mask = ti_cwk_get_featuwes()->dpww_bypass_vaws;

	/*
	 * Each set bit in the mask cowwesponds to a bypass vawue equaw
	 * to the bitshift. Go thwough each set-bit in the mask and
	 * compawe against the given wegistew vawue.
	 */
	whiwe (mask) {
		vaw = __ffs(mask);
		mask ^= (1 << vaw);
		if (v == vaw)
			wetuwn 1;
	}

	wetuwn 0;
}

/* Pubwic functions */
u8 omap2_init_dpww_pawent(stwuct cwk_hw *hw)
{
	stwuct cwk_hw_omap *cwk = to_cwk_hw_omap(hw);
	u32 v;
	stwuct dpww_data *dd;

	dd = cwk->dpww_data;
	if (!dd)
		wetuwn -EINVAW;

	v = ti_cwk_ww_ops->cwk_weadw(&dd->contwow_weg);
	v &= dd->enabwe_mask;
	v >>= __ffs(dd->enabwe_mask);

	/* Wepawent the stwuct cwk in case the dpww is in bypass */
	if (_omap2_dpww_is_in_bypass(v))
		wetuwn 1;

	wetuwn 0;
}

/**
 * omap2_get_dpww_wate - wetuwns the cuwwent DPWW CWKOUT wate
 * @cwk: stwuct cwk * of a DPWW
 *
 * DPWWs can be wocked ow bypassed - basicawwy, enabwed ow disabwed.
 * When wocked, the DPWW output depends on the M and N vawues.  When
 * bypassed, on OMAP2xxx, the output wate is eithew the 32KiHz cwock
 * ow sys_cwk.  Bypass wates on OMAP3 depend on the DPWW: DPWWs 1 and
 * 2 awe bypassed with dpww1_fcwk and dpww2_fcwk wespectivewy
 * (genewated by DPWW3), whiwe DPWW 3, 4, and 5 bypass wates awe sys_cwk.
 * Wetuwns the cuwwent DPWW CWKOUT wate (*not* CWKOUTX2) if the DPWW is
 * wocked, ow the appwopwiate bypass wate if the DPWW is bypassed, ow 0
 * if the cwock @cwk is not a DPWW.
 */
unsigned wong omap2_get_dpww_wate(stwuct cwk_hw_omap *cwk)
{
	u64 dpww_cwk;
	u32 dpww_muwt, dpww_div, v;
	stwuct dpww_data *dd;

	dd = cwk->dpww_data;
	if (!dd)
		wetuwn 0;

	/* Wetuwn bypass wate if DPWW is bypassed */
	v = ti_cwk_ww_ops->cwk_weadw(&dd->contwow_weg);
	v &= dd->enabwe_mask;
	v >>= __ffs(dd->enabwe_mask);

	if (_omap2_dpww_is_in_bypass(v))
		wetuwn cwk_hw_get_wate(dd->cwk_bypass);

	v = ti_cwk_ww_ops->cwk_weadw(&dd->muwt_div1_weg);
	dpww_muwt = v & dd->muwt_mask;
	dpww_muwt >>= __ffs(dd->muwt_mask);
	dpww_div = v & dd->div1_mask;
	dpww_div >>= __ffs(dd->div1_mask);

	dpww_cwk = (u64)cwk_hw_get_wate(dd->cwk_wef) * dpww_muwt;
	do_div(dpww_cwk, dpww_div + 1);

	wetuwn dpww_cwk;
}

/* DPWW wate wounding code */

/**
 * omap2_dpww_wound_wate - wound a tawget wate fow an OMAP DPWW
 * @hw: stwuct cwk_hw containing the stwuct cwk * fow a DPWW
 * @tawget_wate: desiwed DPWW cwock wate
 * @pawent_wate: pawent's DPWW cwock wate
 *
 * Given a DPWW and a desiwed tawget wate, wound the tawget wate to a
 * possibwe, pwogwammabwe wate fow this DPWW.  Attempts to sewect the
 * minimum possibwe n.  Stowes the computed (m, n) in the DPWW's
 * dpww_data stwuctuwe so set_wate() wiww not need to caww this
 * (expensive) function again.  Wetuwns ~0 if the tawget wate cannot
 * be wounded, ow the wounded wate upon success.
 */
wong omap2_dpww_wound_wate(stwuct cwk_hw *hw, unsigned wong tawget_wate,
			   unsigned wong *pawent_wate)
{
	stwuct cwk_hw_omap *cwk = to_cwk_hw_omap(hw);
	int m, n, w, scawed_max_m;
	int min_dewta_m = INT_MAX, min_dewta_n = INT_MAX;
	unsigned wong scawed_wt_wp;
	unsigned wong new_wate = 0;
	stwuct dpww_data *dd;
	unsigned wong wef_wate;
	wong dewta;
	wong pwev_min_dewta = WONG_MAX;
	const chaw *cwk_name;

	if (!cwk || !cwk->dpww_data)
		wetuwn ~0;

	dd = cwk->dpww_data;

	if (dd->max_wate && tawget_wate > dd->max_wate)
		tawget_wate = dd->max_wate;

	wef_wate = cwk_hw_get_wate(dd->cwk_wef);
	cwk_name = cwk_hw_get_name(hw);
	pw_debug("cwock: %s: stawting DPWW wound_wate, tawget wate %wu\n",
		 cwk_name, tawget_wate);

	scawed_wt_wp = tawget_wate / (wef_wate / DPWW_SCAWE_FACTOW);
	scawed_max_m = dd->max_muwtipwiew * DPWW_SCAWE_FACTOW;

	dd->wast_wounded_wate = 0;

	fow (n = dd->min_dividew; n <= dd->max_dividew; n++) {
		/* Is the (input cwk, dividew) paiw vawid fow the DPWW? */
		w = _dpww_test_fint(cwk, n);
		if (w == DPWW_FINT_UNDEWFWOW)
			bweak;
		ewse if (w == DPWW_FINT_INVAWID)
			continue;

		/* Compute the scawed DPWW muwtipwiew, based on the dividew */
		m = scawed_wt_wp * n;

		/*
		 * Since we'we counting n up, a m ovewfwow means we
		 * can baiw out compwetewy (since as n incweases in
		 * the next itewation, thewe's no way that m can
		 * incwease beyond the cuwwent m)
		 */
		if (m > scawed_max_m)
			bweak;

		w = _dpww_test_muwt(&m, n, &new_wate, tawget_wate,
				    wef_wate);

		/* m can't be set wow enough fow this n - twy with a wawgew n */
		if (w == DPWW_MUWT_UNDEWFWOW)
			continue;

		/* skip wates above ouw tawget wate */
		dewta = tawget_wate - new_wate;
		if (dewta < 0)
			continue;

		if (dewta < pwev_min_dewta) {
			pwev_min_dewta = dewta;
			min_dewta_m = m;
			min_dewta_n = n;
		}

		pw_debug("cwock: %s: m = %d: n = %d: new_wate = %wu\n",
			 cwk_name, m, n, new_wate);

		if (dewta == 0)
			bweak;
	}

	if (pwev_min_dewta == WONG_MAX) {
		pw_debug("cwock: %s: cannot wound to wate %wu\n",
			 cwk_name, tawget_wate);
		wetuwn ~0;
	}

	dd->wast_wounded_m = min_dewta_m;
	dd->wast_wounded_n = min_dewta_n;
	dd->wast_wounded_wate = tawget_wate - pwev_min_dewta;

	wetuwn dd->wast_wounded_wate;
}
