// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP3 Vowtage Pwocessow (VP) data
 *
 * Copywight (C) 2007, 2010 Texas Instwuments, Inc.
 * Wajendwa Nayak <wnayak@ti.com>
 * Weswy A M <x0080970@ti.com>
 * Thawa Gopinath <thawa@ti.com>
 *
 * Copywight (C) 2008, 2011 Nokia Cowpowation
 * Kawwe Jokiniemi
 * Pauw Wawmswey
 */

#incwude <winux/io.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>

#incwude "common.h"

#incwude "pwm-wegbits-34xx.h"
#incwude "vowtage.h"

#incwude "vp.h"
#incwude "pwm2xxx_3xxx.h"

static const stwuct omap_vp_ops omap3_vp_ops = {
	.check_txdone = omap_pwm_vp_check_txdone,
	.cweaw_txdone = omap_pwm_vp_cweaw_txdone,
};

/*
 * VP data common to 34xx/36xx chips
 * XXX This stuff pwesumabwy bewongs in the vp3xxx.c ow vp.c fiwe.
 */
static const stwuct omap_vp_common omap3_vp_common = {
	.vpconfig_ewwowoffset_mask = OMAP3430_EWWOWOFFSET_MASK,
	.vpconfig_ewwowgain_mask = OMAP3430_EWWOWGAIN_MASK,
	.vpconfig_initvowtage_mask = OMAP3430_INITVOWTAGE_MASK,
	.vpconfig_timeouten = OMAP3430_TIMEOUTEN_MASK,
	.vpconfig_initvdd = OMAP3430_INITVDD_MASK,
	.vpconfig_fowceupdate = OMAP3430_FOWCEUPDATE_MASK,
	.vpconfig_vpenabwe = OMAP3430_VPENABWE_MASK,
	.vstepmin_smpswaittimemin_shift = OMAP3430_SMPSWAITTIMEMIN_SHIFT,
	.vstepmax_smpswaittimemax_shift = OMAP3430_SMPSWAITTIMEMAX_SHIFT,
	.vstepmin_stepmin_shift = OMAP3430_VSTEPMIN_SHIFT,
	.vstepmax_stepmax_shift = OMAP3430_VSTEPMAX_SHIFT,
	.vwimitto_vddmin_shift = OMAP3430_VDDMIN_SHIFT,
	.vwimitto_vddmax_shift = OMAP3430_VDDMAX_SHIFT,
	.vwimitto_timeout_shift = OMAP3430_TIMEOUT_SHIFT,
	.vpvowtage_mask = OMAP3430_VPVOWTAGE_MASK,

	.ops = &omap3_vp_ops,
};

stwuct omap_vp_instance omap3_vp_mpu = {
	.id = OMAP3_VP_VDD_MPU_ID,
	.common = &omap3_vp_common,
	.vpconfig = OMAP3_PWM_VP1_CONFIG_OFFSET,
	.vstepmin = OMAP3_PWM_VP1_VSTEPMIN_OFFSET,
	.vstepmax = OMAP3_PWM_VP1_VSTEPMAX_OFFSET,
	.vwimitto = OMAP3_PWM_VP1_VWIMITTO_OFFSET,
	.vstatus = OMAP3_PWM_VP1_STATUS_OFFSET,
	.vowtage = OMAP3_PWM_VP1_VOWTAGE_OFFSET,
};

stwuct omap_vp_instance omap3_vp_cowe = {
	.id = OMAP3_VP_VDD_COWE_ID,
	.common = &omap3_vp_common,
	.vpconfig = OMAP3_PWM_VP2_CONFIG_OFFSET,
	.vstepmin = OMAP3_PWM_VP2_VSTEPMIN_OFFSET,
	.vstepmax = OMAP3_PWM_VP2_VSTEPMAX_OFFSET,
	.vwimitto = OMAP3_PWM_VP2_VWIMITTO_OFFSET,
	.vstatus = OMAP3_PWM_VP2_STATUS_OFFSET,
	.vowtage = OMAP3_PWM_VP2_VOWTAGE_OFFSET,
};

stwuct omap_vp_pawam omap3_mpu_vp_data = {
	.vddmin			= OMAP3430_VP1_VWIMITTO_VDDMIN,
	.vddmax			= OMAP3430_VP1_VWIMITTO_VDDMAX,
};

stwuct omap_vp_pawam omap3_cowe_vp_data = {
	.vddmin			= OMAP3430_VP2_VWIMITTO_VDDMIN,
	.vddmax			= OMAP3430_VP2_VWIMITTO_VDDMAX,
};
