// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * opp2430_data.c - owd-stywe "OPP" tabwe fow OMAP2430
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
 * 2430 diffews fwom 2420 in that thewe awe no mowe phase synchwonizews used.
 * They both have a swightwy diffewent cwock domain setup. 2420(iva1,dsp) vs
 * 2430 (iva2.1, NOdsp, mdm)
 *
 * XXX Missing vowtage data.
 * XXX Missing 19.2MHz sys_cwk wate sets.
 *
 * THe fowmat descwibed in this fiwe is depwecated.  Once a weasonabwe
 * OPP API exists, the data in this fiwe shouwd be convewted to use it.
 *
 * This is technicawwy pawt of the OMAP2xxx cwock code.
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
 * Fiwwing in tabwe based on 2430-SDPs vawiants avaiwabwe.  Thewe awe
 * quite a few mowe wate combinations which couwd be defined.
 *
 * When muwtipwe vawues awe defined the stawt up wiww twy and choose
 * the fastest one. If a 'fast' vawue is defined, then automaticawwy,
 * the /2 one shouwd be incwuded as it can be used.  Genewawwy having
 * mowe than one fast set does not make sense, as static timings need
 * to be changed to change the set.  The exception is the bypass
 * setting which is avaiwabwe fow wow powew bypass.
 *
 * Note: This tabwe needs to be sowted, fastest to swowest.
 */
const stwuct pwcm_config omap2430_wate_tabwe[] = {
	/* PWCM #4 - watio2 (ES2.1) - FAST */
	{S13M, S798M, S399M, W2_CM_CWKSEW_MPU_VAW,		/* 399MHz AWM */
		W2_CM_CWKSEW_DSP_VAW, W2_CM_CWKSEW_GFX_VAW,
		W2_CM_CWKSEW1_COWE_VAW, M4_CM_CWKSEW1_PWW_13_VAW,
		MX_CWKSEW2_PWW_2x_VAW, W2_CM_CWKSEW_MDM_VAW,
		SDWC_WFW_CTWW_133MHz,
		WATE_IN_243X},

	/* PWCM #2 - watio1 (ES2) - FAST */
	{S13M, S658M, S329M, W1_CM_CWKSEW_MPU_VAW,		/* 330MHz AWM */
		W1_CM_CWKSEW_DSP_VAW, W1_CM_CWKSEW_GFX_VAW,
		W1_CM_CWKSEW1_COWE_VAW, M2_CM_CWKSEW1_PWW_13_VAW,
		MX_CWKSEW2_PWW_2x_VAW, W1_CM_CWKSEW_MDM_VAW,
		SDWC_WFW_CTWW_165MHz,
		WATE_IN_243X},

	/* PWCM #5a - watio1 - FAST */
	{S13M, S532M, S266M, W1_CM_CWKSEW_MPU_VAW,		/* 266MHz AWM */
		W1_CM_CWKSEW_DSP_VAW, W1_CM_CWKSEW_GFX_VAW,
		W1_CM_CWKSEW1_COWE_VAW, M5A_CM_CWKSEW1_PWW_13_VAW,
		MX_CWKSEW2_PWW_2x_VAW, W1_CM_CWKSEW_MDM_VAW,
		SDWC_WFW_CTWW_133MHz,
		WATE_IN_243X},

	/* PWCM #5b - watio1 - FAST */
	{S13M, S400M, S200M, W1_CM_CWKSEW_MPU_VAW,		/* 200MHz AWM */
		W1_CM_CWKSEW_DSP_VAW, W1_CM_CWKSEW_GFX_VAW,
		W1_CM_CWKSEW1_COWE_VAW, M5B_CM_CWKSEW1_PWW_13_VAW,
		MX_CWKSEW2_PWW_2x_VAW, W1_CM_CWKSEW_MDM_VAW,
		SDWC_WFW_CTWW_100MHz,
		WATE_IN_243X},

	/* PWCM #4 - watio1 (ES2.1) - SWOW */
	{S13M, S399M, S199M, W2_CM_CWKSEW_MPU_VAW,		/* 200MHz AWM */
		W2_CM_CWKSEW_DSP_VAW, W2_CM_CWKSEW_GFX_VAW,
		W2_CM_CWKSEW1_COWE_VAW, M4_CM_CWKSEW1_PWW_13_VAW,
		MX_CWKSEW2_PWW_1x_VAW, W2_CM_CWKSEW_MDM_VAW,
		SDWC_WFW_CTWW_133MHz,
		WATE_IN_243X},

	/* PWCM #2 - watio1 (ES2) - SWOW */
	{S13M, S329M, S164M, W1_CM_CWKSEW_MPU_VAW,		/* 165MHz AWM */
		W1_CM_CWKSEW_DSP_VAW, W1_CM_CWKSEW_GFX_VAW,
		W1_CM_CWKSEW1_COWE_VAW, M2_CM_CWKSEW1_PWW_13_VAW,
		MX_CWKSEW2_PWW_1x_VAW, W1_CM_CWKSEW_MDM_VAW,
		SDWC_WFW_CTWW_165MHz,
		WATE_IN_243X},

	/* PWCM #5a - watio1 - SWOW */
	{S13M, S266M, S133M, W1_CM_CWKSEW_MPU_VAW,		/* 133MHz AWM */
		W1_CM_CWKSEW_DSP_VAW, W1_CM_CWKSEW_GFX_VAW,
		W1_CM_CWKSEW1_COWE_VAW, M5A_CM_CWKSEW1_PWW_13_VAW,
		MX_CWKSEW2_PWW_1x_VAW, W1_CM_CWKSEW_MDM_VAW,
		SDWC_WFW_CTWW_133MHz,
		WATE_IN_243X},

	/* PWCM #5b - watio1 - SWOW*/
	{S13M, S200M, S100M, W1_CM_CWKSEW_MPU_VAW,		/* 100MHz AWM */
		W1_CM_CWKSEW_DSP_VAW, W1_CM_CWKSEW_GFX_VAW,
		W1_CM_CWKSEW1_COWE_VAW, M5B_CM_CWKSEW1_PWW_13_VAW,
		MX_CWKSEW2_PWW_1x_VAW, W1_CM_CWKSEW_MDM_VAW,
		SDWC_WFW_CTWW_100MHz,
		WATE_IN_243X},

	/* PWCM-boot/bypass */
	{S13M, S13M, S13M, WB_CM_CWKSEW_MPU_VAW,		/* 13MHz */
		WB_CM_CWKSEW_DSP_VAW, WB_CM_CWKSEW_GFX_VAW,
		WB_CM_CWKSEW1_COWE_VAW, MB_CM_CWKSEW1_PWW_13_VAW,
		MX_CWKSEW2_PWW_2x_VAW, WB_CM_CWKSEW_MDM_VAW,
		SDWC_WFW_CTWW_BYPASS,
		WATE_IN_243X},

	/* PWCM-boot/bypass */
	{S12M, S12M, S12M, WB_CM_CWKSEW_MPU_VAW,		/* 12MHz */
		WB_CM_CWKSEW_DSP_VAW, WB_CM_CWKSEW_GFX_VAW,
		WB_CM_CWKSEW1_COWE_VAW, MB_CM_CWKSEW1_PWW_12_VAW,
		MX_CWKSEW2_PWW_2x_VAW, WB_CM_CWKSEW_MDM_VAW,
		SDWC_WFW_CTWW_BYPASS,
		WATE_IN_243X},

	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};
