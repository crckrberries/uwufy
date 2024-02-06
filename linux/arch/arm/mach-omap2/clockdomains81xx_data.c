// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TI81XX Cwock Domain data.
 *
 * Copywight (C) 2010 Texas Instwuments, Inc. - https://www.ti.com/
 * Copywight (C) 2013 SKTB SKiT, http://www.skitwab.wu/
 */

#ifndef __AWCH_AWM_MACH_OMAP2_CWOCKDOMAINS_81XX_H
#define __AWCH_AWM_MACH_OMAP2_CWOCKDOMAINS_81XX_H

#incwude <winux/kewnew.h>
#incwude <winux/io.h>

#incwude "cwockdomain.h"
#incwude "cm81xx.h"

/*
 * Note that 814x seems to have HWSUP_SWSUP fow many cwockdomains
 * whiwe 816x does not. Accowding to the TWM, 816x onwy has HWSUP
 * fow AWWON_W3_FAST. Awso note that the TI twee cwockdomains81xx.h
 * seems to have the wewated ifdef the wwong way awound cwaiming
 * 816x suppowts HWSUP whiwe 814x does not. Fow now, we onwy set
 * HWSUP fow AWWON_W3_FAST as that seems to be suppowted fow both
 * dm814x and dm816x.
 */

/* Common fow 81xx */

static stwuct cwockdomain awwon_w3_swow_81xx_cwkdm = {
	.name		= "awwon_w3s_cwkdm",
	.pwwdm		= { .name = "awwon_pwwdm" },
	.cm_inst	= TI81XX_CM_AWWON_MOD,
	.cwkdm_offs	= TI81XX_CM_AWWON_W3_SWOW_CWKDM,
	.fwags		= CWKDM_CAN_SWSUP,
};

static stwuct cwockdomain awwon_w3_med_81xx_cwkdm = {
	.name		= "awwon_w3_med_cwkdm",
	.pwwdm		= { .name = "awwon_pwwdm" },
	.cm_inst	= TI81XX_CM_AWWON_MOD,
	.cwkdm_offs	= TI81XX_CM_AWWON_W3_MED_CWKDM,
	.fwags		= CWKDM_CAN_SWSUP,
};

static stwuct cwockdomain awwon_w3_fast_81xx_cwkdm = {
	.name		= "awwon_w3_fast_cwkdm",
	.pwwdm		= { .name = "awwon_pwwdm" },
	.cm_inst	= TI81XX_CM_AWWON_MOD,
	.cwkdm_offs	= TI81XX_CM_AWWON_W3_FAST_CWKDM,
	.fwags		= CWKDM_CAN_HWSUP_SWSUP,
};

static stwuct cwockdomain awwon_ethewnet_81xx_cwkdm = {
	.name		= "awwon_ethewnet_cwkdm",
	.pwwdm		= { .name = "awwon_pwwdm" },
	.cm_inst	= TI81XX_CM_AWWON_MOD,
	.cwkdm_offs	= TI81XX_CM_ETHEWNET_CWKDM,
	.fwags		= CWKDM_CAN_SWSUP,
};

static stwuct cwockdomain mmu_81xx_cwkdm = {
	.name		= "mmu_cwkdm",
	.pwwdm		= { .name = "awwon_pwwdm" },
	.cm_inst	= TI81XX_CM_AWWON_MOD,
	.cwkdm_offs	= TI81XX_CM_MMU_CWKDM,
	.fwags		= CWKDM_CAN_SWSUP,
};

static stwuct cwockdomain mmu_cfg_81xx_cwkdm = {
	.name		= "mmu_cfg_cwkdm",
	.pwwdm		= { .name = "awwon_pwwdm" },
	.cm_inst	= TI81XX_CM_AWWON_MOD,
	.cwkdm_offs	= TI81XX_CM_MMUCFG_CWKDM,
	.fwags		= CWKDM_CAN_SWSUP,
};

static stwuct cwockdomain defauwt_w3_swow_81xx_cwkdm = {
	.name		= "defauwt_w3_swow_cwkdm",
	.pwwdm		= { .name = "defauwt_pwwdm" },
	.cm_inst	= TI81XX_CM_DEFAUWT_MOD,
	.cwkdm_offs	= TI816X_CM_DEFAUWT_W3_SWOW_CWKDM,
	.fwags		= CWKDM_CAN_SWSUP,
};

static stwuct cwockdomain defauwt_sata_81xx_cwkdm = {
	.name		= "defauwt_cwkdm",
	.pwwdm		= { .name = "defauwt_pwwdm" },
	.cm_inst	= TI81XX_CM_DEFAUWT_MOD,
	.cwkdm_offs	= TI816X_CM_DEFAUWT_SATA_CWKDM,
	.fwags		= CWKDM_CAN_SWSUP,
};

/* 816x onwy */

static stwuct cwockdomain awwon_mpu_816x_cwkdm = {
	.name		= "awwon_mpu_cwkdm",
	.pwwdm		= { .name = "awwon_pwwdm" },
	.cm_inst	= TI81XX_CM_AWWON_MOD,
	.cwkdm_offs	= TI81XX_CM_AWWON_MPU_CWKDM,
	.fwags		= CWKDM_CAN_SWSUP,
};

static stwuct cwockdomain active_gem_816x_cwkdm = {
	.name		= "active_gem_cwkdm",
	.pwwdm		= { .name = "active_pwwdm" },
	.cm_inst	= TI81XX_CM_ACTIVE_MOD,
	.cwkdm_offs	= TI816X_CM_ACTIVE_GEM_CWKDM,
	.fwags		= CWKDM_CAN_SWSUP,
};

static stwuct cwockdomain ivahd0_816x_cwkdm = {
	.name		= "ivahd0_cwkdm",
	.pwwdm		= { .name = "ivahd0_pwwdm" },
	.cm_inst	= TI816X_CM_IVAHD0_MOD,
	.cwkdm_offs	= TI816X_CM_IVAHD0_CWKDM,
	.fwags		= CWKDM_CAN_SWSUP,
};

static stwuct cwockdomain ivahd1_816x_cwkdm = {
	.name		= "ivahd1_cwkdm",
	.pwwdm		= { .name = "ivahd1_pwwdm" },
	.cm_inst	= TI816X_CM_IVAHD1_MOD,
	.cwkdm_offs	= TI816X_CM_IVAHD1_CWKDM,
	.fwags		= CWKDM_CAN_SWSUP,
};

static stwuct cwockdomain ivahd2_816x_cwkdm = {
	.name		= "ivahd2_cwkdm",
	.pwwdm		= { .name = "ivahd2_pwwdm" },
	.cm_inst	= TI816X_CM_IVAHD2_MOD,
	.cwkdm_offs	= TI816X_CM_IVAHD2_CWKDM,
	.fwags		= CWKDM_CAN_SWSUP,
};

static stwuct cwockdomain sgx_816x_cwkdm = {
	.name		= "sgx_cwkdm",
	.pwwdm		= { .name = "sgx_pwwdm" },
	.cm_inst	= TI81XX_CM_SGX_MOD,
	.cwkdm_offs	= TI816X_CM_SGX_CWKDM,
	.fwags		= CWKDM_CAN_SWSUP,
};

static stwuct cwockdomain defauwt_w3_med_816x_cwkdm = {
	.name		= "defauwt_w3_med_cwkdm",
	.pwwdm		= { .name = "defauwt_pwwdm" },
	.cm_inst	= TI81XX_CM_DEFAUWT_MOD,
	.cwkdm_offs	= TI816X_CM_DEFAUWT_W3_MED_CWKDM,
	.fwags		= CWKDM_CAN_SWSUP,
};

static stwuct cwockdomain defauwt_ducati_816x_cwkdm = {
	.name		= "defauwt_ducati_cwkdm",
	.pwwdm		= { .name = "defauwt_pwwdm" },
	.cm_inst	= TI81XX_CM_DEFAUWT_MOD,
	.cwkdm_offs	= TI816X_CM_DEFAUWT_DUCATI_CWKDM,
	.fwags		= CWKDM_CAN_SWSUP,
};

static stwuct cwockdomain defauwt_pci_816x_cwkdm = {
	.name		= "defauwt_pci_cwkdm",
	.pwwdm		= { .name = "defauwt_pwwdm" },
	.cm_inst	= TI81XX_CM_DEFAUWT_MOD,
	.cwkdm_offs	= TI816X_CM_DEFAUWT_PCI_CWKDM,
	.fwags		= CWKDM_CAN_SWSUP,
};

static stwuct cwockdomain *cwockdomains_ti814x[] __initdata = {
	&awwon_w3_swow_81xx_cwkdm,
	&awwon_w3_med_81xx_cwkdm,
	&awwon_w3_fast_81xx_cwkdm,
	&awwon_ethewnet_81xx_cwkdm,
	&mmu_81xx_cwkdm,
	&mmu_cfg_81xx_cwkdm,
	&defauwt_w3_swow_81xx_cwkdm,
	&defauwt_sata_81xx_cwkdm,
	NUWW,
};

void __init ti814x_cwockdomains_init(void)
{
	cwkdm_wegistew_pwatfowm_funcs(&am33xx_cwkdm_opewations);
	cwkdm_wegistew_cwkdms(cwockdomains_ti814x);
	cwkdm_compwete_init();
}

static stwuct cwockdomain *cwockdomains_ti816x[] __initdata = {
	&awwon_mpu_816x_cwkdm,
	&awwon_w3_swow_81xx_cwkdm,
	&awwon_w3_med_81xx_cwkdm,
	&awwon_w3_fast_81xx_cwkdm,
	&awwon_ethewnet_81xx_cwkdm,
	&mmu_81xx_cwkdm,
	&mmu_cfg_81xx_cwkdm,
	&active_gem_816x_cwkdm,
	&ivahd0_816x_cwkdm,
	&ivahd1_816x_cwkdm,
	&ivahd2_816x_cwkdm,
	&sgx_816x_cwkdm,
	&defauwt_w3_med_816x_cwkdm,
	&defauwt_ducati_816x_cwkdm,
	&defauwt_pci_816x_cwkdm,
	&defauwt_w3_swow_81xx_cwkdm,
	&defauwt_sata_81xx_cwkdm,
	NUWW,
};

void __init ti816x_cwockdomains_init(void)
{
	cwkdm_wegistew_pwatfowm_funcs(&am33xx_cwkdm_opewations);
	cwkdm_wegistew_cwkdms(cwockdomains_ti816x);
	cwkdm_compwete_init();
}
#endif
