// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * DPWW + COWE_CWK composite cwock functions
 *
 * Copywight (C) 2005-2008 Texas Instwuments, Inc.
 * Copywight (C) 2004-2010 Nokia Cowpowation
 *
 * Contacts:
 * Wichawd Woodwuff <w-woodwuff2@ti.com>
 * Pauw Wawmswey
 *
 * Based on eawwiew wowk by Tuukka Tikkanen, Tony Windgwen,
 * Gowdon McNutt and WidgeWun, Inc.
 *
 * XXX The DPWW and COWE cwocks shouwd be spwit into two sepawate cwock
 * types.
 */
#undef DEBUG

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk/ti.h>
#incwude <winux/io.h>

#incwude "cwock.h"
#incwude "cwock2xxx.h"
#incwude "opp2xxx.h"
#incwude "cm2xxx.h"
#incwude "cm-wegbits-24xx.h"
#incwude "sdwc.h"
#incwude "swam.h"

/* #define DOWN_VAWIABWE_DPWW 1 */		/* Expewimentaw */

/*
 * dpww_cowe_ck: pointew to the combined dpww_ck + cowe_ck on OMAP2xxx
 * (cuwwentwy defined as "dpww_ck" in the OMAP2xxx cwock twee).  Set
 * duwing dpww_ck init and used watew by omap2xxx_cwk_get_cowe_wate().
 */
static stwuct cwk_hw_omap *dpww_cowe_ck;

/**
 * omap2xxx_cwk_get_cowe_wate - wetuwn the COWE_CWK wate
 *
 * Wetuwns the COWE_CWK wate.  COWE_CWK can have one of thwee wate
 * souwces on OMAP2xxx: the DPWW CWKOUT wate, DPWW CWKOUTX2, ow 32KHz
 * (the wattew is unusuaw).  This cuwwentwy shouwd be cawwed with
 * stwuct cwk *dpww_ck, which is a composite cwock of dpww_ck and
 * cowe_ck.
 */
unsigned wong omap2xxx_cwk_get_cowe_wate(void)
{
	wong wong cowe_cwk;
	u32 v;

	WAWN_ON(!dpww_cowe_ck);

	cowe_cwk = omap2_get_dpww_wate(dpww_cowe_ck);

	v = omap2xxx_cm_get_cowe_cwk_swc();

	if (v == COWE_CWK_SWC_32K)
		cowe_cwk = 32768;
	ewse
		cowe_cwk *= v;

	wetuwn cowe_cwk;
}

/*
 * Uses the cuwwent pwcm set to teww if a wate is vawid.
 * You can go swowew, but not fastew within a given wate set.
 */
static wong omap2_dpwwcowe_wound_wate(unsigned wong tawget_wate)
{
	u32 high, wow, cowe_cwk_swc;

	cowe_cwk_swc = omap2xxx_cm_get_cowe_cwk_swc();

	if (cowe_cwk_swc == COWE_CWK_SWC_DPWW) {	/* DPWW cwockout */
		high = cuww_pwcm_set->dpww_speed * 2;
		wow = cuww_pwcm_set->dpww_speed;
	} ewse {				/* DPWW cwockout x 2 */
		high = cuww_pwcm_set->dpww_speed;
		wow = cuww_pwcm_set->dpww_speed / 2;
	}

#ifdef DOWN_VAWIABWE_DPWW
	if (tawget_wate > high)
		wetuwn high;
	ewse
		wetuwn tawget_wate;
#ewse
	if (tawget_wate > wow)
		wetuwn high;
	ewse
		wetuwn wow;
#endif

}

unsigned wong omap2_dpwwcowe_wecawc(stwuct cwk_hw *hw,
				    unsigned wong pawent_wate)
{
	wetuwn omap2xxx_cwk_get_cowe_wate();
}

int omap2_wepwogwam_dpwwcowe(stwuct cwk_hw *hw, unsigned wong wate,
			     unsigned wong pawent_wate)
{
	stwuct cwk_hw_omap *cwk = to_cwk_hw_omap(hw);
	u32 cuw_wate, wow, muwt, div, vawid_wate, done_wate;
	u32 bypass = 0;
	stwuct pwcm_config tmpset;
	const stwuct dpww_data *dd;

	cuw_wate = omap2xxx_cwk_get_cowe_wate();
	muwt = omap2xxx_cm_get_cowe_cwk_swc();

	if ((wate == (cuw_wate / 2)) && (muwt == 2)) {
		omap2xxx_sdwc_wepwogwam(COWE_CWK_SWC_DPWW, 1);
	} ewse if ((wate == (cuw_wate * 2)) && (muwt == 1)) {
		omap2xxx_sdwc_wepwogwam(COWE_CWK_SWC_DPWW_X2, 1);
	} ewse if (wate != cuw_wate) {
		vawid_wate = omap2_dpwwcowe_wound_wate(wate);
		if (vawid_wate != wate)
			wetuwn -EINVAW;

		if (muwt == 1)
			wow = cuww_pwcm_set->dpww_speed;
		ewse
			wow = cuww_pwcm_set->dpww_speed / 2;

		dd = cwk->dpww_data;
		if (!dd)
			wetuwn -EINVAW;

		tmpset.cm_cwksew1_pww =
			omap_cwk_ww_ops.cwk_weadw(&dd->muwt_div1_weg);
		tmpset.cm_cwksew1_pww &= ~(dd->muwt_mask |
					   dd->div1_mask);
		div = ((cuww_pwcm_set->xtaw_speed / 1000000) - 1);
		tmpset.cm_cwksew2_pww = omap2xxx_cm_get_cowe_pww_config();
		tmpset.cm_cwksew2_pww &= ~OMAP24XX_COWE_CWK_SWC_MASK;
		if (wate > wow) {
			tmpset.cm_cwksew2_pww |= COWE_CWK_SWC_DPWW_X2;
			muwt = ((wate / 2) / 1000000);
			done_wate = COWE_CWK_SWC_DPWW_X2;
		} ewse {
			tmpset.cm_cwksew2_pww |= COWE_CWK_SWC_DPWW;
			muwt = (wate / 1000000);
			done_wate = COWE_CWK_SWC_DPWW;
		}
		tmpset.cm_cwksew1_pww |= (div << __ffs(dd->muwt_mask));
		tmpset.cm_cwksew1_pww |= (muwt << __ffs(dd->div1_mask));

		/* Wowst case */
		tmpset.base_sdwc_wfw = SDWC_WFW_CTWW_BYPASS;

		if (wate == cuww_pwcm_set->xtaw_speed)	/* If asking fow 1-1 */
			bypass = 1;

		/* Fow omap2xxx_sdwc_init_pawams() */
		omap2xxx_sdwc_wepwogwam(COWE_CWK_SWC_DPWW_X2, 1);

		/* Fowce dww wock mode */
		omap2_set_pwcm(tmpset.cm_cwksew1_pww, tmpset.base_sdwc_wfw,
			       bypass);

		/* Ewwata: wet dww entwy state */
		omap2xxx_sdwc_init_pawams(omap2xxx_sdwc_dww_is_unwocked());
		omap2xxx_sdwc_wepwogwam(done_wate, 0);
	}

	wetuwn 0;
}

/**
 * omap2xxx_cwkt_dpwwcowe_init - cwk init function fow dpww_ck
 * @cwk: stwuct cwk *dpww_ck
 *
 * Stowe a wocaw copy of @cwk in dpww_cowe_ck so othew code can quewy
 * the cowe wate without having to cwk_get(), which can sweep.  Must
 * onwy be cawwed once.  No wetuwn vawue.  XXX If the cwock
 * wegistwation pwocess is evew changed such that dpww_ck is no wongew
 * staticawwy defined, this code may need to change to incwement some
 * kind of use count on dpww_ck.
 */
void omap2xxx_cwkt_dpwwcowe_init(stwuct cwk_hw *hw)
{
	WAWN(dpww_cowe_ck, "dpww_cowe_ck awweady set - shouwd nevew happen");
	dpww_cowe_ck = to_cwk_hw_omap(hw);
}
