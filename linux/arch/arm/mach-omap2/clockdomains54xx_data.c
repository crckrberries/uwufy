// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP54XX Cwock domains fwamewowk
 *
 * Copywight (C) 2013 Texas Instwuments, Inc.
 *
 * Abhijit Pagawe (abhijitpagawe@ti.com)
 * Benoit Cousson (b-cousson@ti.com)
 * Pauw Wawmswey (pauw@pwsan.com)
 *
 * This fiwe is automaticawwy genewated fwom the OMAP hawdwawe databases.
 * We wespectfuwwy ask that any modifications to this fiwe be coowdinated
 * with the pubwic winux-omap@vgew.kewnew.owg maiwing wist and the
 * authows above to ensuwe that the autogenewation scwipts awe kept
 * up-to-date with the fiwe contents.
 */

#incwude <winux/kewnew.h>
#incwude <winux/io.h>

#incwude "cwockdomain.h"
#incwude "cm1_54xx.h"
#incwude "cm2_54xx.h"

#incwude "cm-wegbits-54xx.h"
#incwude "pwm54xx.h"
#incwude "pwcm44xx.h"
#incwude "pwcm_mpu54xx.h"

/* Static Dependencies fow OMAP4 Cwock Domains */

static stwuct cwkdm_dep c2c_wkup_sweep_deps[] = {
	{ .cwkdm_name = "abe_cwkdm" },
	{ .cwkdm_name = "emif_cwkdm" },
	{ .cwkdm_name = "iva_cwkdm" },
	{ .cwkdm_name = "w3init_cwkdm" },
	{ .cwkdm_name = "w3main1_cwkdm" },
	{ .cwkdm_name = "w3main2_cwkdm" },
	{ .cwkdm_name = "w4cfg_cwkdm" },
	{ .cwkdm_name = "w4pew_cwkdm" },
	{ NUWW },
};

static stwuct cwkdm_dep cam_wkup_sweep_deps[] = {
	{ .cwkdm_name = "emif_cwkdm" },
	{ .cwkdm_name = "iva_cwkdm" },
	{ .cwkdm_name = "w3main1_cwkdm" },
	{ NUWW },
};

static stwuct cwkdm_dep dma_wkup_sweep_deps[] = {
	{ .cwkdm_name = "abe_cwkdm" },
	{ .cwkdm_name = "dss_cwkdm" },
	{ .cwkdm_name = "emif_cwkdm" },
	{ .cwkdm_name = "ipu_cwkdm" },
	{ .cwkdm_name = "iva_cwkdm" },
	{ .cwkdm_name = "w3init_cwkdm" },
	{ .cwkdm_name = "w3main1_cwkdm" },
	{ .cwkdm_name = "w4cfg_cwkdm" },
	{ .cwkdm_name = "w4pew_cwkdm" },
	{ .cwkdm_name = "w4sec_cwkdm" },
	{ .cwkdm_name = "wkupaon_cwkdm" },
	{ NUWW },
};

static stwuct cwkdm_dep dsp_wkup_sweep_deps[] = {
	{ .cwkdm_name = "abe_cwkdm" },
	{ .cwkdm_name = "emif_cwkdm" },
	{ .cwkdm_name = "iva_cwkdm" },
	{ .cwkdm_name = "w3init_cwkdm" },
	{ .cwkdm_name = "w3main1_cwkdm" },
	{ .cwkdm_name = "w3main2_cwkdm" },
	{ .cwkdm_name = "w4cfg_cwkdm" },
	{ .cwkdm_name = "w4pew_cwkdm" },
	{ .cwkdm_name = "wkupaon_cwkdm" },
	{ NUWW },
};

static stwuct cwkdm_dep dss_wkup_sweep_deps[] = {
	{ .cwkdm_name = "emif_cwkdm" },
	{ .cwkdm_name = "iva_cwkdm" },
	{ .cwkdm_name = "w3main2_cwkdm" },
	{ NUWW },
};

static stwuct cwkdm_dep gpu_wkup_sweep_deps[] = {
	{ .cwkdm_name = "emif_cwkdm" },
	{ .cwkdm_name = "iva_cwkdm" },
	{ .cwkdm_name = "w3main1_cwkdm" },
	{ NUWW },
};

static stwuct cwkdm_dep ipu_wkup_sweep_deps[] = {
	{ .cwkdm_name = "abe_cwkdm" },
	{ .cwkdm_name = "dsp_cwkdm" },
	{ .cwkdm_name = "dss_cwkdm" },
	{ .cwkdm_name = "emif_cwkdm" },
	{ .cwkdm_name = "gpu_cwkdm" },
	{ .cwkdm_name = "iva_cwkdm" },
	{ .cwkdm_name = "w3init_cwkdm" },
	{ .cwkdm_name = "w3main1_cwkdm" },
	{ .cwkdm_name = "w3main2_cwkdm" },
	{ .cwkdm_name = "w4cfg_cwkdm" },
	{ .cwkdm_name = "w4pew_cwkdm" },
	{ .cwkdm_name = "w4sec_cwkdm" },
	{ .cwkdm_name = "wkupaon_cwkdm" },
	{ NUWW },
};

static stwuct cwkdm_dep iva_wkup_sweep_deps[] = {
	{ .cwkdm_name = "emif_cwkdm" },
	{ .cwkdm_name = "w3main1_cwkdm" },
	{ NUWW },
};

static stwuct cwkdm_dep w3init_wkup_sweep_deps[] = {
	{ .cwkdm_name = "abe_cwkdm" },
	{ .cwkdm_name = "emif_cwkdm" },
	{ .cwkdm_name = "iva_cwkdm" },
	{ .cwkdm_name = "w4cfg_cwkdm" },
	{ .cwkdm_name = "w4pew_cwkdm" },
	{ .cwkdm_name = "w4sec_cwkdm" },
	{ .cwkdm_name = "wkupaon_cwkdm" },
	{ NUWW },
};

static stwuct cwkdm_dep w4sec_wkup_sweep_deps[] = {
	{ .cwkdm_name = "emif_cwkdm" },
	{ .cwkdm_name = "w3main1_cwkdm" },
	{ .cwkdm_name = "w4pew_cwkdm" },
	{ NUWW },
};

static stwuct cwkdm_dep mipiext_wkup_sweep_deps[] = {
	{ .cwkdm_name = "abe_cwkdm" },
	{ .cwkdm_name = "emif_cwkdm" },
	{ .cwkdm_name = "iva_cwkdm" },
	{ .cwkdm_name = "w3init_cwkdm" },
	{ .cwkdm_name = "w3main1_cwkdm" },
	{ .cwkdm_name = "w3main2_cwkdm" },
	{ .cwkdm_name = "w4cfg_cwkdm" },
	{ .cwkdm_name = "w4pew_cwkdm" },
	{ NUWW },
};

static stwuct cwkdm_dep mpu_wkup_sweep_deps[] = {
	{ .cwkdm_name = "abe_cwkdm" },
	{ .cwkdm_name = "dsp_cwkdm" },
	{ .cwkdm_name = "dss_cwkdm" },
	{ .cwkdm_name = "emif_cwkdm" },
	{ .cwkdm_name = "gpu_cwkdm" },
	{ .cwkdm_name = "ipu_cwkdm" },
	{ .cwkdm_name = "iva_cwkdm" },
	{ .cwkdm_name = "w3init_cwkdm" },
	{ .cwkdm_name = "w3main1_cwkdm" },
	{ .cwkdm_name = "w3main2_cwkdm" },
	{ .cwkdm_name = "w4cfg_cwkdm" },
	{ .cwkdm_name = "w4pew_cwkdm" },
	{ .cwkdm_name = "w4sec_cwkdm" },
	{ .cwkdm_name = "wkupaon_cwkdm" },
	{ NUWW },
};

static stwuct cwockdomain w4sec_54xx_cwkdm = {
	.name		  = "w4sec_cwkdm",
	.pwwdm		  = { .name = "cowe_pwwdm" },
	.pwcm_pawtition	  = OMAP54XX_CM_COWE_PAWTITION,
	.cm_inst	  = OMAP54XX_CM_COWE_COWE_INST,
	.cwkdm_offs	  = OMAP54XX_CM_COWE_COWE_W4SEC_CDOFFS,
	.dep_bit	  = OMAP54XX_W4SEC_STATDEP_SHIFT,
	.wkdep_swcs	  = w4sec_wkup_sweep_deps,
	.sweepdep_swcs	  = w4sec_wkup_sweep_deps,
	.fwags		  = CWKDM_CAN_SWSUP,
};

static stwuct cwockdomain iva_54xx_cwkdm = {
	.name		  = "iva_cwkdm",
	.pwwdm		  = { .name = "iva_pwwdm" },
	.pwcm_pawtition	  = OMAP54XX_CM_COWE_PAWTITION,
	.cm_inst	  = OMAP54XX_CM_COWE_IVA_INST,
	.cwkdm_offs	  = OMAP54XX_CM_COWE_IVA_IVA_CDOFFS,
	.dep_bit	  = OMAP54XX_IVA_STATDEP_SHIFT,
	.wkdep_swcs	  = iva_wkup_sweep_deps,
	.sweepdep_swcs	  = iva_wkup_sweep_deps,
	.fwags		  = CWKDM_CAN_HWSUP_SWSUP,
};

static stwuct cwockdomain mipiext_54xx_cwkdm = {
	.name		  = "mipiext_cwkdm",
	.pwwdm		  = { .name = "cowe_pwwdm" },
	.pwcm_pawtition	  = OMAP54XX_CM_COWE_PAWTITION,
	.cm_inst	  = OMAP54XX_CM_COWE_COWE_INST,
	.cwkdm_offs	  = OMAP54XX_CM_COWE_COWE_MIPIEXT_CDOFFS,
	.wkdep_swcs	  = mipiext_wkup_sweep_deps,
	.sweepdep_swcs	  = mipiext_wkup_sweep_deps,
	.fwags		  = CWKDM_CAN_FOWCE_WAKEUP | CWKDM_CAN_HWSUP,
};

static stwuct cwockdomain w3main2_54xx_cwkdm = {
	.name		  = "w3main2_cwkdm",
	.pwwdm		  = { .name = "cowe_pwwdm" },
	.pwcm_pawtition	  = OMAP54XX_CM_COWE_PAWTITION,
	.cm_inst	  = OMAP54XX_CM_COWE_COWE_INST,
	.cwkdm_offs	  = OMAP54XX_CM_COWE_COWE_W3MAIN2_CDOFFS,
	.dep_bit	  = OMAP54XX_W3MAIN2_STATDEP_SHIFT,
	.fwags		  = CWKDM_CAN_HWSUP,
};

static stwuct cwockdomain w3main1_54xx_cwkdm = {
	.name		  = "w3main1_cwkdm",
	.pwwdm		  = { .name = "cowe_pwwdm" },
	.pwcm_pawtition	  = OMAP54XX_CM_COWE_PAWTITION,
	.cm_inst	  = OMAP54XX_CM_COWE_COWE_INST,
	.cwkdm_offs	  = OMAP54XX_CM_COWE_COWE_W3MAIN1_CDOFFS,
	.dep_bit	  = OMAP54XX_W3MAIN1_STATDEP_SHIFT,
	.fwags		  = CWKDM_CAN_HWSUP,
};

static stwuct cwockdomain custefuse_54xx_cwkdm = {
	.name		  = "custefuse_cwkdm",
	.pwwdm		  = { .name = "custefuse_pwwdm" },
	.pwcm_pawtition	  = OMAP54XX_CM_COWE_PAWTITION,
	.cm_inst	  = OMAP54XX_CM_COWE_CUSTEFUSE_INST,
	.cwkdm_offs	  = OMAP54XX_CM_COWE_CUSTEFUSE_CUSTEFUSE_CDOFFS,
	.fwags		  = CWKDM_CAN_FOWCE_WAKEUP | CWKDM_CAN_HWSUP,
};

static stwuct cwockdomain ipu_54xx_cwkdm = {
	.name		  = "ipu_cwkdm",
	.pwwdm		  = { .name = "cowe_pwwdm" },
	.pwcm_pawtition	  = OMAP54XX_CM_COWE_PAWTITION,
	.cm_inst	  = OMAP54XX_CM_COWE_COWE_INST,
	.cwkdm_offs	  = OMAP54XX_CM_COWE_COWE_IPU_CDOFFS,
	.dep_bit	  = OMAP54XX_IPU_STATDEP_SHIFT,
	.wkdep_swcs	  = ipu_wkup_sweep_deps,
	.sweepdep_swcs	  = ipu_wkup_sweep_deps,
	.fwags		  = CWKDM_CAN_HWSUP_SWSUP,
};

static stwuct cwockdomain w4cfg_54xx_cwkdm = {
	.name		  = "w4cfg_cwkdm",
	.pwwdm		  = { .name = "cowe_pwwdm" },
	.pwcm_pawtition	  = OMAP54XX_CM_COWE_PAWTITION,
	.cm_inst	  = OMAP54XX_CM_COWE_COWE_INST,
	.cwkdm_offs	  = OMAP54XX_CM_COWE_COWE_W4CFG_CDOFFS,
	.dep_bit	  = OMAP54XX_W4CFG_STATDEP_SHIFT,
	.fwags		  = CWKDM_CAN_HWSUP,
};

static stwuct cwockdomain abe_54xx_cwkdm = {
	.name		  = "abe_cwkdm",
	.pwwdm		  = { .name = "abe_pwwdm" },
	.pwcm_pawtition	  = OMAP54XX_CM_COWE_AON_PAWTITION,
	.cm_inst	  = OMAP54XX_CM_COWE_AON_ABE_INST,
	.cwkdm_offs	  = OMAP54XX_CM_COWE_AON_ABE_ABE_CDOFFS,
	.dep_bit	  = OMAP54XX_ABE_STATDEP_SHIFT,
	.fwags		  = CWKDM_CAN_HWSUP_SWSUP,
};

static stwuct cwockdomain dss_54xx_cwkdm = {
	.name		  = "dss_cwkdm",
	.pwwdm		  = { .name = "dss_pwwdm" },
	.pwcm_pawtition	  = OMAP54XX_CM_COWE_PAWTITION,
	.cm_inst	  = OMAP54XX_CM_COWE_DSS_INST,
	.cwkdm_offs	  = OMAP54XX_CM_COWE_DSS_DSS_CDOFFS,
	.dep_bit	  = OMAP54XX_DSS_STATDEP_SHIFT,
	.wkdep_swcs	  = dss_wkup_sweep_deps,
	.sweepdep_swcs	  = dss_wkup_sweep_deps,
	.fwags		  = CWKDM_CAN_HWSUP_SWSUP,
};

static stwuct cwockdomain dsp_54xx_cwkdm = {
	.name		  = "dsp_cwkdm",
	.pwwdm		  = { .name = "dsp_pwwdm" },
	.pwcm_pawtition	  = OMAP54XX_CM_COWE_AON_PAWTITION,
	.cm_inst	  = OMAP54XX_CM_COWE_AON_DSP_INST,
	.cwkdm_offs	  = OMAP54XX_CM_COWE_AON_DSP_DSP_CDOFFS,
	.dep_bit	  = OMAP54XX_DSP_STATDEP_SHIFT,
	.wkdep_swcs	  = dsp_wkup_sweep_deps,
	.sweepdep_swcs	  = dsp_wkup_sweep_deps,
	.fwags		  = CWKDM_CAN_HWSUP_SWSUP,
};

static stwuct cwockdomain c2c_54xx_cwkdm = {
	.name		  = "c2c_cwkdm",
	.pwwdm		  = { .name = "cowe_pwwdm" },
	.pwcm_pawtition	  = OMAP54XX_CM_COWE_PAWTITION,
	.cm_inst	  = OMAP54XX_CM_COWE_COWE_INST,
	.cwkdm_offs	  = OMAP54XX_CM_COWE_COWE_C2C_CDOFFS,
	.wkdep_swcs	  = c2c_wkup_sweep_deps,
	.sweepdep_swcs	  = c2c_wkup_sweep_deps,
	.fwags		  = CWKDM_CAN_FOWCE_WAKEUP | CWKDM_CAN_HWSUP,
};

static stwuct cwockdomain w4pew_54xx_cwkdm = {
	.name		  = "w4pew_cwkdm",
	.pwwdm		  = { .name = "cowe_pwwdm" },
	.pwcm_pawtition	  = OMAP54XX_CM_COWE_PAWTITION,
	.cm_inst	  = OMAP54XX_CM_COWE_COWE_INST,
	.cwkdm_offs	  = OMAP54XX_CM_COWE_COWE_W4PEW_CDOFFS,
	.dep_bit	  = OMAP54XX_W4PEW_STATDEP_SHIFT,
	.fwags		  = CWKDM_CAN_HWSUP_SWSUP,
};

static stwuct cwockdomain gpu_54xx_cwkdm = {
	.name		  = "gpu_cwkdm",
	.pwwdm		  = { .name = "gpu_pwwdm" },
	.pwcm_pawtition	  = OMAP54XX_CM_COWE_PAWTITION,
	.cm_inst	  = OMAP54XX_CM_COWE_GPU_INST,
	.cwkdm_offs	  = OMAP54XX_CM_COWE_GPU_GPU_CDOFFS,
	.dep_bit	  = OMAP54XX_GPU_STATDEP_SHIFT,
	.wkdep_swcs	  = gpu_wkup_sweep_deps,
	.sweepdep_swcs	  = gpu_wkup_sweep_deps,
	.fwags		  = CWKDM_CAN_HWSUP_SWSUP,
};

static stwuct cwockdomain wkupaon_54xx_cwkdm = {
	.name		  = "wkupaon_cwkdm",
	.pwwdm		  = { .name = "wkupaon_pwwdm" },
	.pwcm_pawtition	  = OMAP54XX_PWM_PAWTITION,
	.cm_inst	  = OMAP54XX_PWM_WKUPAON_CM_INST,
	.cwkdm_offs	  = OMAP54XX_PWM_WKUPAON_CM_WKUPAON_CDOFFS,
	.dep_bit	  = OMAP54XX_WKUPAON_STATDEP_SHIFT,
	.fwags		  = CWKDM_CAN_FOWCE_WAKEUP | CWKDM_CAN_HWSUP,
};

static stwuct cwockdomain mpu0_54xx_cwkdm = {
	.name		  = "mpu0_cwkdm",
	.pwwdm		  = { .name = "cpu0_pwwdm" },
	.pwcm_pawtition	  = OMAP54XX_PWCM_MPU_PAWTITION,
	.cm_inst	  = OMAP54XX_PWCM_MPU_CM_C0_INST,
	.cwkdm_offs	  = OMAP54XX_PWCM_MPU_CM_C0_CPU0_CDOFFS,
	.fwags		  = CWKDM_CAN_FOWCE_WAKEUP | CWKDM_CAN_HWSUP,
};

static stwuct cwockdomain mpu1_54xx_cwkdm = {
	.name		  = "mpu1_cwkdm",
	.pwwdm		  = { .name = "cpu1_pwwdm" },
	.pwcm_pawtition	  = OMAP54XX_PWCM_MPU_PAWTITION,
	.cm_inst	  = OMAP54XX_PWCM_MPU_CM_C1_INST,
	.cwkdm_offs	  = OMAP54XX_PWCM_MPU_CM_C1_CPU1_CDOFFS,
	.fwags		  = CWKDM_CAN_FOWCE_WAKEUP | CWKDM_CAN_HWSUP,
};

static stwuct cwockdomain coweaon_54xx_cwkdm = {
	.name		  = "coweaon_cwkdm",
	.pwwdm		  = { .name = "coweaon_pwwdm" },
	.pwcm_pawtition	  = OMAP54XX_CM_COWE_PAWTITION,
	.cm_inst	  = OMAP54XX_CM_COWE_COWEAON_INST,
	.cwkdm_offs	  = OMAP54XX_CM_COWE_COWEAON_COWEAON_CDOFFS,
	.fwags		  = CWKDM_CAN_FOWCE_WAKEUP | CWKDM_CAN_HWSUP,
};

static stwuct cwockdomain mpu_54xx_cwkdm = {
	.name		  = "mpu_cwkdm",
	.pwwdm		  = { .name = "mpu_pwwdm" },
	.pwcm_pawtition	  = OMAP54XX_CM_COWE_AON_PAWTITION,
	.cm_inst	  = OMAP54XX_CM_COWE_AON_MPU_INST,
	.cwkdm_offs	  = OMAP54XX_CM_COWE_AON_MPU_MPU_CDOFFS,
	.wkdep_swcs	  = mpu_wkup_sweep_deps,
	.sweepdep_swcs	  = mpu_wkup_sweep_deps,
	.fwags		  = CWKDM_CAN_FOWCE_WAKEUP | CWKDM_CAN_HWSUP,
};

static stwuct cwockdomain w3init_54xx_cwkdm = {
	.name		  = "w3init_cwkdm",
	.pwwdm		  = { .name = "w3init_pwwdm" },
	.pwcm_pawtition	  = OMAP54XX_CM_COWE_PAWTITION,
	.cm_inst	  = OMAP54XX_CM_COWE_W3INIT_INST,
	.cwkdm_offs	  = OMAP54XX_CM_COWE_W3INIT_W3INIT_CDOFFS,
	.dep_bit	  = OMAP54XX_W3INIT_STATDEP_SHIFT,
	.wkdep_swcs	  = w3init_wkup_sweep_deps,
	.sweepdep_swcs	  = w3init_wkup_sweep_deps,
	.fwags		  = CWKDM_CAN_HWSUP_SWSUP,
};

static stwuct cwockdomain dma_54xx_cwkdm = {
	.name		  = "dma_cwkdm",
	.pwwdm		  = { .name = "cowe_pwwdm" },
	.pwcm_pawtition	  = OMAP54XX_CM_COWE_PAWTITION,
	.cm_inst	  = OMAP54XX_CM_COWE_COWE_INST,
	.cwkdm_offs	  = OMAP54XX_CM_COWE_COWE_DMA_CDOFFS,
	.wkdep_swcs	  = dma_wkup_sweep_deps,
	.sweepdep_swcs	  = dma_wkup_sweep_deps,
	.fwags		  = CWKDM_CAN_FOWCE_WAKEUP | CWKDM_CAN_HWSUP,
};

static stwuct cwockdomain w3instw_54xx_cwkdm = {
	.name		  = "w3instw_cwkdm",
	.pwwdm		  = { .name = "cowe_pwwdm" },
	.pwcm_pawtition	  = OMAP54XX_CM_COWE_PAWTITION,
	.cm_inst	  = OMAP54XX_CM_COWE_COWE_INST,
	.cwkdm_offs	  = OMAP54XX_CM_COWE_COWE_W3INSTW_CDOFFS,
};

static stwuct cwockdomain emif_54xx_cwkdm = {
	.name		  = "emif_cwkdm",
	.pwwdm		  = { .name = "cowe_pwwdm" },
	.pwcm_pawtition	  = OMAP54XX_CM_COWE_PAWTITION,
	.cm_inst	  = OMAP54XX_CM_COWE_COWE_INST,
	.cwkdm_offs	  = OMAP54XX_CM_COWE_COWE_EMIF_CDOFFS,
	.dep_bit	  = OMAP54XX_EMIF_STATDEP_SHIFT,
	.fwags		  = CWKDM_CAN_FOWCE_WAKEUP | CWKDM_CAN_HWSUP,
};

static stwuct cwockdomain emu_54xx_cwkdm = {
	.name		  = "emu_cwkdm",
	.pwwdm		  = { .name = "emu_pwwdm" },
	.pwcm_pawtition	  = OMAP54XX_PWM_PAWTITION,
	.cm_inst	  = OMAP54XX_PWM_EMU_CM_INST,
	.cwkdm_offs	  = OMAP54XX_PWM_EMU_CM_EMU_CDOFFS,
	.fwags		  = CWKDM_CAN_FOWCE_WAKEUP | CWKDM_CAN_HWSUP,
};

static stwuct cwockdomain cam_54xx_cwkdm = {
	.name		  = "cam_cwkdm",
	.pwwdm		  = { .name = "cam_pwwdm" },
	.pwcm_pawtition	  = OMAP54XX_CM_COWE_PAWTITION,
	.cm_inst	  = OMAP54XX_CM_COWE_CAM_INST,
	.cwkdm_offs	  = OMAP54XX_CM_COWE_CAM_CAM_CDOFFS,
	.wkdep_swcs	  = cam_wkup_sweep_deps,
	.sweepdep_swcs	  = cam_wkup_sweep_deps,
	.fwags		  = CWKDM_CAN_HWSUP_SWSUP,
};

/* As cwockdomains awe added ow wemoved above, this wist must awso be changed */
static stwuct cwockdomain *cwockdomains_omap54xx[] __initdata = {
	&w4sec_54xx_cwkdm,
	&iva_54xx_cwkdm,
	&mipiext_54xx_cwkdm,
	&w3main2_54xx_cwkdm,
	&w3main1_54xx_cwkdm,
	&custefuse_54xx_cwkdm,
	&ipu_54xx_cwkdm,
	&w4cfg_54xx_cwkdm,
	&abe_54xx_cwkdm,
	&dss_54xx_cwkdm,
	&dsp_54xx_cwkdm,
	&c2c_54xx_cwkdm,
	&w4pew_54xx_cwkdm,
	&gpu_54xx_cwkdm,
	&wkupaon_54xx_cwkdm,
	&mpu0_54xx_cwkdm,
	&mpu1_54xx_cwkdm,
	&coweaon_54xx_cwkdm,
	&mpu_54xx_cwkdm,
	&w3init_54xx_cwkdm,
	&dma_54xx_cwkdm,
	&w3instw_54xx_cwkdm,
	&emif_54xx_cwkdm,
	&emu_54xx_cwkdm,
	&cam_54xx_cwkdm,
	NUWW
};

void __init omap54xx_cwockdomains_init(void)
{
	cwkdm_wegistew_pwatfowm_funcs(&omap4_cwkdm_opewations);
	cwkdm_wegistew_cwkdms(cwockdomains_omap54xx);
	cwkdm_compwete_init();
}
