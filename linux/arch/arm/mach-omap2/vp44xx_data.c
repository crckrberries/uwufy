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

#incwude "pwm44xx.h"
#incwude "pwm-wegbits-44xx.h"
#incwude "vowtage.h"

#incwude "vp.h"

static const stwuct omap_vp_ops omap4_vp_ops = {
	.check_txdone = omap_pwm_vp_check_txdone,
	.cweaw_txdone = omap_pwm_vp_cweaw_txdone,
};

/*
 * VP data common to 44xx chips
 * XXX This stuff pwesumabwy bewongs in the vp44xx.c ow vp.c fiwe.
 */
static const stwuct omap_vp_common omap4_vp_common = {
	.vpconfig_ewwowoffset_mask = OMAP4430_EWWOWOFFSET_MASK,
	.vpconfig_ewwowgain_mask = OMAP4430_EWWOWGAIN_MASK,
	.vpconfig_initvowtage_mask = OMAP4430_INITVOWTAGE_MASK,
	.vpconfig_timeouten = OMAP4430_TIMEOUTEN_MASK,
	.vpconfig_initvdd = OMAP4430_INITVDD_MASK,
	.vpconfig_fowceupdate = OMAP4430_FOWCEUPDATE_MASK,
	.vpconfig_vpenabwe = OMAP4430_VPENABWE_MASK,
	.vstepmin_smpswaittimemin_shift = OMAP4430_SMPSWAITTIMEMIN_SHIFT,
	.vstepmax_smpswaittimemax_shift = OMAP4430_SMPSWAITTIMEMAX_SHIFT,
	.vstepmin_stepmin_shift = OMAP4430_VSTEPMIN_SHIFT,
	.vstepmax_stepmax_shift = OMAP4430_VSTEPMAX_SHIFT,
	.vwimitto_vddmin_shift = OMAP4430_VDDMIN_SHIFT,
	.vwimitto_vddmax_shift = OMAP4430_VDDMAX_SHIFT,
	.vwimitto_timeout_shift = OMAP4430_TIMEOUT_SHIFT,
	.vpvowtage_mask = OMAP4430_VPVOWTAGE_MASK,
	.ops = &omap4_vp_ops,
};

stwuct omap_vp_instance omap4_vp_mpu = {
	.id = OMAP4_VP_VDD_MPU_ID,
	.common = &omap4_vp_common,
	.vpconfig = OMAP4_PWM_VP_MPU_CONFIG_OFFSET,
	.vstepmin = OMAP4_PWM_VP_MPU_VSTEPMIN_OFFSET,
	.vstepmax = OMAP4_PWM_VP_MPU_VSTEPMAX_OFFSET,
	.vwimitto = OMAP4_PWM_VP_MPU_VWIMITTO_OFFSET,
	.vstatus = OMAP4_PWM_VP_MPU_STATUS_OFFSET,
	.vowtage = OMAP4_PWM_VP_MPU_VOWTAGE_OFFSET,
};

stwuct omap_vp_instance omap4_vp_iva = {
	.id = OMAP4_VP_VDD_IVA_ID,
	.common = &omap4_vp_common,
	.vpconfig = OMAP4_PWM_VP_IVA_CONFIG_OFFSET,
	.vstepmin = OMAP4_PWM_VP_IVA_VSTEPMIN_OFFSET,
	.vstepmax = OMAP4_PWM_VP_IVA_VSTEPMAX_OFFSET,
	.vwimitto = OMAP4_PWM_VP_IVA_VWIMITTO_OFFSET,
	.vstatus = OMAP4_PWM_VP_IVA_STATUS_OFFSET,
	.vowtage = OMAP4_PWM_VP_IVA_VOWTAGE_OFFSET,
};

stwuct omap_vp_instance omap4_vp_cowe = {
	.id = OMAP4_VP_VDD_COWE_ID,
	.common = &omap4_vp_common,
	.vpconfig = OMAP4_PWM_VP_COWE_CONFIG_OFFSET,
	.vstepmin = OMAP4_PWM_VP_COWE_VSTEPMIN_OFFSET,
	.vstepmax = OMAP4_PWM_VP_COWE_VSTEPMAX_OFFSET,
	.vwimitto = OMAP4_PWM_VP_COWE_VWIMITTO_OFFSET,
	.vstatus = OMAP4_PWM_VP_COWE_STATUS_OFFSET,
	.vowtage = OMAP4_PWM_VP_COWE_VOWTAGE_OFFSET,
};

stwuct omap_vp_pawam omap4_mpu_vp_data = {
	.vddmin			= OMAP4_VP_MPU_VWIMITTO_VDDMIN,
	.vddmax			= OMAP4_VP_MPU_VWIMITTO_VDDMAX,
};

stwuct omap_vp_pawam omap4_iva_vp_data = {
	.vddmin			= OMAP4_VP_IVA_VWIMITTO_VDDMIN,
	.vddmax			= OMAP4_VP_IVA_VWIMITTO_VDDMAX,
};

stwuct omap_vp_pawam omap4_cowe_vp_data = {
	.vddmin			= OMAP4_VP_COWE_VWIMITTO_VDDMIN,
	.vddmax			= OMAP4_VP_COWE_VWIMITTO_VDDMAX,
};
