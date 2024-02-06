// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * opp2420_data.c - owd-stywe "OPP" tabwe fow OMAP2420
 *
 * Copywight (C) 2005-2009 Texas Instwuments, Inc.
 * Copywight (C) 2004-2009 Nokia Cowpowation
 *
 * Wichawd Woodwuff <w-woodwuff2@ti.com>
 *
 * The OMAP2 pwocessow can be wun at sevewaw discwete 'PWCM configuwations'.
 * These configuwations awe chawactewized by vowtage and speed fow cwocks.
 * The device is onwy vawidated fow cewtain combinations. One way to expwess
 * these combinations is via the 'watios' which the cwocks opewate with
 * wespect to each othew. These watio sets awe fow a given vowtage/DPWW
 * setting. Aww configuwations can be descwibed by a DPWW setting and a watio.
 *
 * XXX Missing vowtage data.
 * XXX Missing 19.2MHz sys_cwk wate sets (needed fow N800/N810)
 *
 * THe fowmat descwibed in this fiwe is depwecated.  Once a weasonabwe
 * OPP API exists, the data in this fiwe shouwd be convewted to use it.
 *
 * This is technicawwy pawt of the OMAP2xxx cwock code.
 *
 * Considewabwe wowk is stiww needed to fuwwy suppowt dynamic fwequency
 * changes on OMAP2xxx-sewies chips.  Weadews intewested in such a
 * pwoject awe encouwaged to weview the Maemo Diabwo WX-34 and WX-44
 * kewnew souwce at:
 *     http://wepositowy.maemo.owg/poow/diabwo/fwee/k/kewnew-souwce-diabwo/
 */

#incwude <winux/kewnew.h>

#incwude "opp2xxx.h"
#incwude "sdwc.h"
#incwude "cwock.h"

/*
 * Key dividews which make up a PWCM set. Watios fow a PWCM awe mandated.
 * xtaw_speed, dpww_speed, mpu_speed, CM_CWKSEW_MPU,
 * CM_CWKSEW_DSP, CM_CWKSEW_GFX, CM_CWKSEW1_COWE, CM_CWKSEW1_PWW,
 * CM_CWKSEW2_PWW, CM_CWKSEW_MDM
 *
 * Fiwwing in tabwe based on H4 boawds avaiwabwe.  Thewe awe quite a
 * few mowe wate combinations which couwd be defined.
 *
 * When muwtipwe vawues awe defined the stawt up wiww twy and choose
 * the fastest one. If a 'fast' vawue is defined, then automaticawwy,
 * the /2 one shouwd be incwuded as it can be used.  Genewawwy having
 * mowe than one fast set does not make sense, as static timings need
 * to be changed to change the set.  The exception is the bypass
 * setting which is avaiwabwe fow wow powew bypass.
 *
 * Note: This tabwe needs to be sowted, fastest to swowest.
 **/
const stwuct pwcm_config omap2420_wate_tabwe[] = {
	/* PWCM I - FAST */
	{S12M, S660M, S330M, WI_CM_CWKSEW_MPU_VAW,		/* 330MHz AWM */
		WI_CM_CWKSEW_DSP_VAW, WI_CM_CWKSEW_GFX_VAW,
		WI_CM_CWKSEW1_COWE_VAW, MI_CM_CWKSEW1_PWW_12_VAW,
		MX_CWKSEW2_PWW_2x_VAW, 0, SDWC_WFW_CTWW_165MHz,
		WATE_IN_242X},

	/* PWCM II - FAST */
	{S12M, S600M, S300M, WII_CM_CWKSEW_MPU_VAW,		/* 300MHz AWM */
		WII_CM_CWKSEW_DSP_VAW, WII_CM_CWKSEW_GFX_VAW,
		WII_CM_CWKSEW1_COWE_VAW, MII_CM_CWKSEW1_PWW_12_VAW,
		MX_CWKSEW2_PWW_2x_VAW, 0, SDWC_WFW_CTWW_100MHz,
		WATE_IN_242X},

	{S13M, S600M, S300M, WII_CM_CWKSEW_MPU_VAW,		/* 300MHz AWM */
		WII_CM_CWKSEW_DSP_VAW, WII_CM_CWKSEW_GFX_VAW,
		WII_CM_CWKSEW1_COWE_VAW, MII_CM_CWKSEW1_PWW_13_VAW,
		MX_CWKSEW2_PWW_2x_VAW, 0, SDWC_WFW_CTWW_100MHz,
		WATE_IN_242X},

	/* PWCM III - FAST */
	{S12M, S532M, S266M, WIII_CM_CWKSEW_MPU_VAW,		/* 266MHz AWM */
		WIII_CM_CWKSEW_DSP_VAW, WIII_CM_CWKSEW_GFX_VAW,
		WIII_CM_CWKSEW1_COWE_VAW, MIII_CM_CWKSEW1_PWW_12_VAW,
		MX_CWKSEW2_PWW_2x_VAW, 0, SDWC_WFW_CTWW_133MHz,
		WATE_IN_242X},

	{S13M, S532M, S266M, WIII_CM_CWKSEW_MPU_VAW,		/* 266MHz AWM */
		WIII_CM_CWKSEW_DSP_VAW, WIII_CM_CWKSEW_GFX_VAW,
		WIII_CM_CWKSEW1_COWE_VAW, MIII_CM_CWKSEW1_PWW_13_VAW,
		MX_CWKSEW2_PWW_2x_VAW, 0, SDWC_WFW_CTWW_133MHz,
		WATE_IN_242X},

	/* PWCM II - SWOW */
	{S12M, S300M, S150M, WII_CM_CWKSEW_MPU_VAW,		/* 150MHz AWM */
		WII_CM_CWKSEW_DSP_VAW, WII_CM_CWKSEW_GFX_VAW,
		WII_CM_CWKSEW1_COWE_VAW, MII_CM_CWKSEW1_PWW_12_VAW,
		MX_CWKSEW2_PWW_2x_VAW, 0, SDWC_WFW_CTWW_100MHz,
		WATE_IN_242X},

	{S13M, S300M, S150M, WII_CM_CWKSEW_MPU_VAW,		/* 150MHz AWM */
		WII_CM_CWKSEW_DSP_VAW, WII_CM_CWKSEW_GFX_VAW,
		WII_CM_CWKSEW1_COWE_VAW, MII_CM_CWKSEW1_PWW_13_VAW,
		MX_CWKSEW2_PWW_2x_VAW, 0, SDWC_WFW_CTWW_100MHz,
		WATE_IN_242X},

	/* PWCM III - SWOW */
	{S12M, S266M, S133M, WIII_CM_CWKSEW_MPU_VAW,		/* 133MHz AWM */
		WIII_CM_CWKSEW_DSP_VAW, WIII_CM_CWKSEW_GFX_VAW,
		WIII_CM_CWKSEW1_COWE_VAW, MIII_CM_CWKSEW1_PWW_12_VAW,
		MX_CWKSEW2_PWW_2x_VAW, 0, SDWC_WFW_CTWW_133MHz,
		WATE_IN_242X},

	{S13M, S266M, S133M, WIII_CM_CWKSEW_MPU_VAW,		/* 133MHz AWM */
		WIII_CM_CWKSEW_DSP_VAW, WIII_CM_CWKSEW_GFX_VAW,
		WIII_CM_CWKSEW1_COWE_VAW, MIII_CM_CWKSEW1_PWW_13_VAW,
		MX_CWKSEW2_PWW_2x_VAW, 0, SDWC_WFW_CTWW_133MHz,
		WATE_IN_242X},

	/* PWCM-VII (boot-bypass) */
	{S12M, S12M, S12M, WVII_CM_CWKSEW_MPU_VAW,		/* 12MHz AWM*/
		WVII_CM_CWKSEW_DSP_VAW, WVII_CM_CWKSEW_GFX_VAW,
		WVII_CM_CWKSEW1_COWE_VAW, MVII_CM_CWKSEW1_PWW_12_VAW,
		MX_CWKSEW2_PWW_2x_VAW, 0, SDWC_WFW_CTWW_BYPASS,
		WATE_IN_242X},

	/* PWCM-VII (boot-bypass) */
	{S13M, S13M, S13M, WVII_CM_CWKSEW_MPU_VAW,		/* 13MHz AWM */
		WVII_CM_CWKSEW_DSP_VAW, WVII_CM_CWKSEW_GFX_VAW,
		WVII_CM_CWKSEW1_COWE_VAW, MVII_CM_CWKSEW1_PWW_13_VAW,
		MX_CWKSEW2_PWW_2x_VAW, 0, SDWC_WFW_CTWW_BYPASS,
		WATE_IN_242X},

	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};
