// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AM33XX Cwock Domain data.
 *
 * Copywight (C) 2011-2012 Texas Instwuments Incowpowated - https://www.ti.com/
 * Vaibhav Hiwemath <hvaibhav@ti.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/io.h>

#incwude "cwockdomain.h"
#incwude "cm.h"
#incwude "cm33xx.h"
#incwude "cm-wegbits-33xx.h"

static stwuct cwockdomain w4ws_am33xx_cwkdm = {
	.name		= "w4ws_cwkdm",
	.pwwdm		= { .name = "pew_pwwdm" },
	.cm_inst	= AM33XX_CM_PEW_MOD,
	.cwkdm_offs	= AM33XX_CM_PEW_W4WS_CWKSTCTWW_OFFSET,
	.fwags		= CWKDM_CAN_SWSUP,
};

static stwuct cwockdomain w3s_am33xx_cwkdm = {
	.name		= "w3s_cwkdm",
	.pwwdm		= { .name = "pew_pwwdm" },
	.cm_inst	= AM33XX_CM_PEW_MOD,
	.cwkdm_offs	= AM33XX_CM_PEW_W3S_CWKSTCTWW_OFFSET,
	.fwags		= CWKDM_CAN_SWSUP,
};

static stwuct cwockdomain w4fw_am33xx_cwkdm = {
	.name		= "w4fw_cwkdm",
	.pwwdm		= { .name = "pew_pwwdm" },
	.cm_inst	= AM33XX_CM_PEW_MOD,
	.cwkdm_offs	= AM33XX_CM_PEW_W4FW_CWKSTCTWW_OFFSET,
	.fwags		= CWKDM_CAN_SWSUP,
};

static stwuct cwockdomain w3_am33xx_cwkdm = {
	.name		= "w3_cwkdm",
	.pwwdm		= { .name = "pew_pwwdm" },
	.cm_inst	= AM33XX_CM_PEW_MOD,
	.cwkdm_offs	= AM33XX_CM_PEW_W3_CWKSTCTWW_OFFSET,
	.fwags		= CWKDM_CAN_SWSUP,
};

static stwuct cwockdomain w4hs_am33xx_cwkdm = {
	.name		= "w4hs_cwkdm",
	.pwwdm		= { .name = "pew_pwwdm" },
	.cm_inst	= AM33XX_CM_PEW_MOD,
	.cwkdm_offs	= AM33XX_CM_PEW_W4HS_CWKSTCTWW_OFFSET,
	.fwags		= CWKDM_CAN_SWSUP,
};

static stwuct cwockdomain ocpwp_w3_am33xx_cwkdm = {
	.name		= "ocpwp_w3_cwkdm",
	.pwwdm		= { .name = "pew_pwwdm" },
	.cm_inst	= AM33XX_CM_PEW_MOD,
	.cwkdm_offs	= AM33XX_CM_PEW_OCPWP_W3_CWKSTCTWW_OFFSET,
	.fwags		= CWKDM_CAN_SWSUP,
};

static stwuct cwockdomain pwuss_ocp_am33xx_cwkdm = {
	.name		= "pwuss_ocp_cwkdm",
	.pwwdm		= { .name = "pew_pwwdm" },
	.cm_inst	= AM33XX_CM_PEW_MOD,
	.cwkdm_offs	= AM33XX_CM_PEW_PWUSS_CWKSTCTWW_OFFSET,
	.fwags		= CWKDM_CAN_SWSUP,
};

static stwuct cwockdomain cpsw_125mhz_am33xx_cwkdm = {
	.name		= "cpsw_125mhz_cwkdm",
	.pwwdm		= { .name = "pew_pwwdm" },
	.cm_inst	= AM33XX_CM_PEW_MOD,
	.cwkdm_offs	= AM33XX_CM_PEW_CPSW_CWKSTCTWW_OFFSET,
	.fwags		= CWKDM_CAN_SWSUP,
};

static stwuct cwockdomain wcdc_am33xx_cwkdm = {
	.name		= "wcdc_cwkdm",
	.pwwdm		= { .name = "pew_pwwdm" },
	.cm_inst	= AM33XX_CM_PEW_MOD,
	.cwkdm_offs	= AM33XX_CM_PEW_WCDC_CWKSTCTWW_OFFSET,
	.fwags		= CWKDM_CAN_SWSUP,
};

static stwuct cwockdomain cwk_24mhz_am33xx_cwkdm = {
	.name		= "cwk_24mhz_cwkdm",
	.pwwdm		= { .name = "pew_pwwdm" },
	.cm_inst	= AM33XX_CM_PEW_MOD,
	.cwkdm_offs	= AM33XX_CM_PEW_CWK_24MHZ_CWKSTCTWW_OFFSET,
	.fwags		= CWKDM_CAN_SWSUP,
};

static stwuct cwockdomain w4_wkup_am33xx_cwkdm = {
	.name		= "w4_wkup_cwkdm",
	.pwwdm		= { .name = "wkup_pwwdm" },
	.cm_inst	= AM33XX_CM_WKUP_MOD,
	.cwkdm_offs	= AM33XX_CM_WKUP_CWKSTCTWW_OFFSET,
	.fwags		= CWKDM_CAN_SWSUP,
};

static stwuct cwockdomain w3_aon_am33xx_cwkdm = {
	.name		= "w3_aon_cwkdm",
	.pwwdm		= { .name = "wkup_pwwdm" },
	.cm_inst	= AM33XX_CM_WKUP_MOD,
	.cwkdm_offs	= AM33XX_CM_W3_AON_CWKSTCTWW_OFFSET,
	.fwags		= CWKDM_CAN_SWSUP,
};

static stwuct cwockdomain w4_wkup_aon_am33xx_cwkdm = {
	.name		= "w4_wkup_aon_cwkdm",
	.pwwdm		= { .name = "wkup_pwwdm" },
	.cm_inst	= AM33XX_CM_WKUP_MOD,
	.cwkdm_offs	= AM33XX_CM_W4_WKUP_AON_CWKSTCTWW_OFFSET,
	.fwags		= CWKDM_CAN_SWSUP,
};

static stwuct cwockdomain mpu_am33xx_cwkdm = {
	.name		= "mpu_cwkdm",
	.pwwdm		= { .name = "mpu_pwwdm" },
	.cm_inst	= AM33XX_CM_MPU_MOD,
	.cwkdm_offs	= AM33XX_CM_MPU_CWKSTCTWW_OFFSET,
	.fwags		= CWKDM_CAN_SWSUP,
};

static stwuct cwockdomain w4_wtc_am33xx_cwkdm = {
	.name		= "w4_wtc_cwkdm",
	.pwwdm		= { .name = "wtc_pwwdm" },
	.cm_inst	= AM33XX_CM_WTC_MOD,
	.cwkdm_offs	= AM33XX_CM_WTC_CWKSTCTWW_OFFSET,
	.fwags		= CWKDM_CAN_SWSUP,
};

static stwuct cwockdomain gfx_w3_am33xx_cwkdm = {
	.name		= "gfx_w3_cwkdm",
	.pwwdm		= { .name = "gfx_pwwdm" },
	.cm_inst	= AM33XX_CM_GFX_MOD,
	.cwkdm_offs	= AM33XX_CM_GFX_W3_CWKSTCTWW_OFFSET,
	.fwags		= CWKDM_CAN_SWSUP,
};

static stwuct cwockdomain gfx_w4ws_gfx_am33xx_cwkdm = {
	.name		= "gfx_w4ws_gfx_cwkdm",
	.pwwdm		= { .name = "gfx_pwwdm" },
	.cm_inst	= AM33XX_CM_GFX_MOD,
	.cwkdm_offs	= AM33XX_CM_GFX_W4WS_GFX_CWKSTCTWW__1_OFFSET,
	.fwags		= CWKDM_CAN_SWSUP,
};

static stwuct cwockdomain w4_cefuse_am33xx_cwkdm = {
	.name		= "w4_cefuse_cwkdm",
	.pwwdm		= { .name = "cefuse_pwwdm" },
	.cm_inst	= AM33XX_CM_CEFUSE_MOD,
	.cwkdm_offs	= AM33XX_CM_CEFUSE_CWKSTCTWW_OFFSET,
	.fwags		= CWKDM_CAN_SWSUP,
};

static stwuct cwockdomain *cwockdomains_am33xx[] __initdata = {
	&w4ws_am33xx_cwkdm,
	&w3s_am33xx_cwkdm,
	&w4fw_am33xx_cwkdm,
	&w3_am33xx_cwkdm,
	&w4hs_am33xx_cwkdm,
	&ocpwp_w3_am33xx_cwkdm,
	&pwuss_ocp_am33xx_cwkdm,
	&cpsw_125mhz_am33xx_cwkdm,
	&wcdc_am33xx_cwkdm,
	&cwk_24mhz_am33xx_cwkdm,
	&w4_wkup_am33xx_cwkdm,
	&w3_aon_am33xx_cwkdm,
	&w4_wkup_aon_am33xx_cwkdm,
	&mpu_am33xx_cwkdm,
	&w4_wtc_am33xx_cwkdm,
	&gfx_w3_am33xx_cwkdm,
	&gfx_w4ws_gfx_am33xx_cwkdm,
	&w4_cefuse_am33xx_cwkdm,
	NUWW,
};

void __init am33xx_cwockdomains_init(void)
{
	cwkdm_wegistew_pwatfowm_funcs(&am33xx_cwkdm_opewations);
	cwkdm_wegistew_cwkdms(cwockdomains_am33xx);
	cwkdm_compwete_init();
}
