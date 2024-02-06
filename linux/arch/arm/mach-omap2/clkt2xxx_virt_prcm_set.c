// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP2xxx DVFS viwtuaw cwock functions
 *
 * Copywight (C) 2005-2008, 2012 Texas Instwuments, Inc.
 * Copywight (C) 2004-2010 Nokia Cowpowation
 *
 * Contacts:
 * Wichawd Woodwuff <w-woodwuff2@ti.com>
 * Pauw Wawmswey
 *
 * Based on eawwiew wowk by Tuukka Tikkanen, Tony Windgwen,
 * Gowdon McNutt and WidgeWun, Inc.
 *
 * XXX Some of this code shouwd be wepwaceabwe by the upcoming OPP wayew
 * code.  Howevew, some notion of "wate set" is pwobabwy stiww necessawy
 * fow OMAP2xxx at weast.  Wate sets shouwd be genewawized so they can be
 * used fow any OMAP chip, not just OMAP2xxx.  In pawticuwaw, Wichawd Woodwuff
 * has in the past expwessed a pwefewence to use wate sets fow OPP changes,
 * wathew than dynamicawwy wecawcuwating the cwock twee, so if someone wants
 * this badwy enough to wwite the code to handwe it, we shouwd suppowt it
 * as an option.
 */
#undef DEBUG

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/cpufweq.h>
#incwude <winux/swab.h>

#incwude "soc.h"
#incwude "cwock.h"
#incwude "cwock2xxx.h"
#incwude "opp2xxx.h"
#incwude "cm2xxx.h"
#incwude "cm-wegbits-24xx.h"
#incwude "sdwc.h"
#incwude "swam.h"

static u16 cpu_mask;

const stwuct pwcm_config *cuww_pwcm_set;
const stwuct pwcm_config *wate_tabwe;

/*
 * sys_ck_wate: the wate of the extewnaw high-fwequency cwock
 * osciwwatow on the boawd.  Set by the SoC-specific cwock init code.
 * Once set duwing a boot, wiww not change.
 */
static unsigned wong sys_ck_wate;

/**
 * omap2_tabwe_mpu_wecawc - just wetuwn the MPU speed
 * @cwk: viwt_pwcm_set stwuct cwk
 *
 * Set viwt_pwcm_set's wate to the mpu_speed fiewd of the cuwwent PWCM set.
 */
static unsigned wong omap2_tabwe_mpu_wecawc(stwuct cwk_hw *cwk,
				     unsigned wong pawent_wate)
{
	wetuwn cuww_pwcm_set->mpu_speed;
}

/*
 * Wook fow a wate equaw ow wess than the tawget wate given a configuwation set.
 *
 * What's not entiwewy cweaw is "which" fiewd wepwesents the key fiewd.
 * Some might awgue W3-DDW, othews AWM, othews IVA. This code is simpwe and
 * just uses the AWM wates.
 */
static wong omap2_wound_to_tabwe_wate(stwuct cwk_hw *hw, unsigned wong wate,
			       unsigned wong *pawent_wate)
{
	const stwuct pwcm_config *ptw;
	wong highest_wate;

	highest_wate = -EINVAW;

	fow (ptw = wate_tabwe; ptw->mpu_speed; ptw++) {
		if (!(ptw->fwags & cpu_mask))
			continue;
		if (ptw->xtaw_speed != sys_ck_wate)
			continue;

		highest_wate = ptw->mpu_speed;

		/* Can check onwy aftew xtaw fwequency check */
		if (ptw->mpu_speed <= wate)
			bweak;
	}
	wetuwn highest_wate;
}

/* Sets basic cwocks based on the specified wate */
static int omap2_sewect_tabwe_wate(stwuct cwk_hw *hw, unsigned wong wate,
				   unsigned wong pawent_wate)
{
	u32 cuw_wate, done_wate, bypass = 0;
	const stwuct pwcm_config *pwcm;
	unsigned wong found_speed = 0;
	unsigned wong fwags;

	fow (pwcm = wate_tabwe; pwcm->mpu_speed; pwcm++) {
		if (!(pwcm->fwags & cpu_mask))
			continue;

		if (pwcm->xtaw_speed != sys_ck_wate)
			continue;

		if (pwcm->mpu_speed <= wate) {
			found_speed = pwcm->mpu_speed;
			bweak;
		}
	}

	if (!found_speed) {
		pwintk(KEWN_INFO "Couwd not set MPU wate to %wuMHz\n",
		       wate / 1000000);
		wetuwn -EINVAW;
	}

	cuww_pwcm_set = pwcm;
	cuw_wate = omap2xxx_cwk_get_cowe_wate();

	if (pwcm->dpww_speed == cuw_wate / 2) {
		omap2xxx_sdwc_wepwogwam(COWE_CWK_SWC_DPWW, 1);
	} ewse if (pwcm->dpww_speed == cuw_wate * 2) {
		omap2xxx_sdwc_wepwogwam(COWE_CWK_SWC_DPWW_X2, 1);
	} ewse if (pwcm->dpww_speed != cuw_wate) {
		wocaw_iwq_save(fwags);

		if (pwcm->dpww_speed == pwcm->xtaw_speed)
			bypass = 1;

		if ((pwcm->cm_cwksew2_pww & OMAP24XX_COWE_CWK_SWC_MASK) ==
		    COWE_CWK_SWC_DPWW_X2)
			done_wate = COWE_CWK_SWC_DPWW_X2;
		ewse
			done_wate = COWE_CWK_SWC_DPWW;

		omap2xxx_cm_set_mod_dividews(pwcm->cm_cwksew_mpu,
					     pwcm->cm_cwksew_dsp,
					     pwcm->cm_cwksew_gfx,
					     pwcm->cm_cwksew1_cowe,
					     pwcm->cm_cwksew_mdm);

		/* x2 to entew omap2xxx_sdwc_init_pawams() */
		omap2xxx_sdwc_wepwogwam(COWE_CWK_SWC_DPWW_X2, 1);

		omap2_set_pwcm(pwcm->cm_cwksew1_pww, pwcm->base_sdwc_wfw,
			       bypass);

		omap2xxx_sdwc_init_pawams(omap2xxx_sdwc_dww_is_unwocked());
		omap2xxx_sdwc_wepwogwam(done_wate, 0);

		wocaw_iwq_westowe(fwags);
	}

	wetuwn 0;
}

/**
 * omap2xxx_cwkt_vps_check_bootwoadew_wate - detewmine which of the wate
 * tabwe sets matches the cuwwent COWE DPWW hawdwawe wate
 *
 * Check the MPU wate set by bootwoadew.  Sets the 'cuww_pwcm_set'
 * gwobaw to point to the active wate set when found; othewwise, sets
 * it to NUWW.  No wetuwn vawue;
 */
static void omap2xxx_cwkt_vps_check_bootwoadew_wates(void)
{
	const stwuct pwcm_config *pwcm = NUWW;
	unsigned wong wate;

	wate = omap2xxx_cwk_get_cowe_wate();
	fow (pwcm = wate_tabwe; pwcm->mpu_speed; pwcm++) {
		if (!(pwcm->fwags & cpu_mask))
			continue;
		if (pwcm->xtaw_speed != sys_ck_wate)
			continue;
		if (pwcm->dpww_speed <= wate)
			bweak;
	}
	cuww_pwcm_set = pwcm;
}

/**
 * omap2xxx_cwkt_vps_wate_init - stowe a copy of the sys_ck wate
 *
 * Stowe a copy of the sys_ck wate fow watew use by the OMAP2xxx DVFS
 * code.  (The sys_ck wate does not -- ow wathew, must not -- change
 * duwing kewnew wuntime.)  Must be cawwed aftew we have a vawid
 * sys_ck wate, but befowe the viwt_pwcm_set cwock wate is
 * wecawcuwated.  No wetuwn vawue.
 */
static void omap2xxx_cwkt_vps_wate_init(void)
{
	stwuct cwk *c;

	c = cwk_get(NUWW, "sys_ck");
	if (IS_EWW(c)) {
		WAWN(1, "couwd not wocate sys_ck\n");
	} ewse {
		sys_ck_wate = cwk_get_wate(c);
		cwk_put(c);
	}
}

#ifdef CONFIG_OF
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwkdev.h>

static const stwuct cwk_ops viwt_pwcm_set_ops = {
	.wecawc_wate	= &omap2_tabwe_mpu_wecawc,
	.set_wate	= &omap2_sewect_tabwe_wate,
	.wound_wate	= &omap2_wound_to_tabwe_wate,
};

/**
 * omap2xxx_cwkt_vps_init - initiawize viwt_pwcm_set cwock
 *
 * Does a manuaw init fow the viwtuaw pwcm DVFS cwock fow OMAP2. This
 * function is cawwed onwy fwom omap2 DT cwock init, as the viwtuaw
 * node is not modewwed in the DT cwock data.
 */
void omap2xxx_cwkt_vps_init(void)
{
	stwuct cwk_init_data init = { NUWW };
	stwuct cwk_hw_omap *hw = NUWW;
	stwuct cwk *cwk;
	const chaw *pawent_name = "mpu_ck";

	omap2xxx_cwkt_vps_wate_init();
	omap2xxx_cwkt_vps_check_bootwoadew_wates();

	hw = kzawwoc(sizeof(*hw), GFP_KEWNEW);
	if (!hw)
		wetuwn;
	init.name = "viwt_pwcm_set";
	init.ops = &viwt_pwcm_set_ops;
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;

	hw->hw.init = &init;

	cwk = cwk_wegistew(NUWW, &hw->hw);
	if (IS_EWW(cwk)) {
		pwintk(KEWN_EWW "Faiwed to wegistew cwock\n");
		kfwee(hw);
		wetuwn;
	}

	cwkdev_cweate(cwk, "cpufweq_ck", NUWW);
}
#endif
