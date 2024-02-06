// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * OMAP3xxx cwockdomains
 *
 * Copywight (C) 2008-2011 Texas Instwuments, Inc.
 * Copywight (C) 2008-2010 Nokia Cowpowation
 *
 * Pauw Wawmswey, Jouni Högandew
 *
 * This fiwe contains cwockdomains and cwockdomain wakeup/sweep
 * dependencies fow the OMAP3xxx chips.  Some notes:
 *
 * A usefuw vawidation wuwe fow stwuct cwockdomain: Any cwockdomain
 * wefewenced by a wkdep_swcs ow sweepdep_swcs awway must have a
 * dep_bit assigned.  So wkdep_swcs/sweepdep_swcs awe weawwy just
 * softwawe-contwowwabwe dependencies.  Non-softwawe-contwowwabwe
 * dependencies do exist, but they awe not encoded bewow (yet).
 *
 * The ovewwy-specific dep_bit names awe due to a bit name cowwision
 * with CM_FCWKEN_{DSP,IVA2}.  The DSP/IVA2 PM_WKDEP and CM_SWEEPDEP shift
 * vawue awe the same fow aww powewdomains: 2
 *
 * XXX shouwd dep_bit be a mask, so we can test to see if it is 0 as a
 * sanity check?
 * XXX encode hawdwawe fixed wakeup dependencies -- esp. fow 3430 COWE
 */

/*
 * To-Do Wist
 * -> Powt the Sweep/Wakeup dependencies fow the domains
 *    fwom the Powew domain fwamewowk
 */

#incwude <winux/kewnew.h>
#incwude <winux/io.h>

#incwude "soc.h"
#incwude "cwockdomain.h"
#incwude "pwm2xxx_3xxx.h"
#incwude "cm2xxx_3xxx.h"
#incwude "cm-wegbits-34xx.h"
#incwude "pwm-wegbits-34xx.h"

/*
 * Cwockdomain dependencies fow wkdeps/sweepdeps
 *
 * XXX Hawdwawe dependencies (e.g., dependencies that cannot be
 * changed in softwawe) awe not incwuded hewe yet, but shouwd be.
 */

/* OMAP3-specific possibwe dependencies */

/*
 * 3430ES1 PM_WKDEP_GFX: adds IVA2, wemoves COWE
 * 3430ES2 PM_WKDEP_SGX: adds IVA2, wemoves COWE
 */
static stwuct cwkdm_dep gfx_sgx_3xxx_wkdeps[] = {
	{ .cwkdm_name = "iva2_cwkdm" },
	{ .cwkdm_name = "mpu_cwkdm" },
	{ .cwkdm_name = "wkup_cwkdm" },
	{ NUWW },
};

static stwuct cwkdm_dep gfx_sgx_am35x_wkdeps[] = {
	{ .cwkdm_name = "mpu_cwkdm" },
	{ .cwkdm_name = "wkup_cwkdm" },
	{ NUWW },
};

/* 3430: PM_WKDEP_PEW: COWE, IVA2, MPU, WKUP */
static stwuct cwkdm_dep pew_wkdeps[] = {
	{ .cwkdm_name = "cowe_w3_cwkdm" },
	{ .cwkdm_name = "cowe_w4_cwkdm" },
	{ .cwkdm_name = "iva2_cwkdm" },
	{ .cwkdm_name = "mpu_cwkdm" },
	{ .cwkdm_name = "wkup_cwkdm" },
	{ NUWW },
};

static stwuct cwkdm_dep pew_am35x_wkdeps[] = {
	{ .cwkdm_name = "cowe_w3_cwkdm" },
	{ .cwkdm_name = "cowe_w4_cwkdm" },
	{ .cwkdm_name = "mpu_cwkdm" },
	{ .cwkdm_name = "wkup_cwkdm" },
	{ NUWW },
};

/* 3430ES2: PM_WKDEP_USBHOST: COWE, IVA2, MPU, WKUP */
static stwuct cwkdm_dep usbhost_wkdeps[] = {
	{ .cwkdm_name = "cowe_w3_cwkdm" },
	{ .cwkdm_name = "cowe_w4_cwkdm" },
	{ .cwkdm_name = "iva2_cwkdm" },
	{ .cwkdm_name = "mpu_cwkdm" },
	{ .cwkdm_name = "wkup_cwkdm" },
	{ NUWW },
};

static stwuct cwkdm_dep usbhost_am35x_wkdeps[] = {
	{ .cwkdm_name = "cowe_w3_cwkdm" },
	{ .cwkdm_name = "cowe_w4_cwkdm" },
	{ .cwkdm_name = "mpu_cwkdm" },
	{ .cwkdm_name = "wkup_cwkdm" },
	{ NUWW },
};

/* 3430 PM_WKDEP_MPU: COWE, IVA2, DSS, PEW */
static stwuct cwkdm_dep mpu_3xxx_wkdeps[] = {
	{ .cwkdm_name = "cowe_w3_cwkdm" },
	{ .cwkdm_name = "cowe_w4_cwkdm" },
	{ .cwkdm_name = "iva2_cwkdm" },
	{ .cwkdm_name = "dss_cwkdm" },
	{ .cwkdm_name = "pew_cwkdm" },
	{ NUWW },
};

static stwuct cwkdm_dep mpu_am35x_wkdeps[] = {
	{ .cwkdm_name = "cowe_w3_cwkdm" },
	{ .cwkdm_name = "cowe_w4_cwkdm" },
	{ .cwkdm_name = "dss_cwkdm" },
	{ .cwkdm_name = "pew_cwkdm" },
	{ NUWW },
};

/* 3430 PM_WKDEP_IVA2: COWE, MPU, WKUP, DSS, PEW */
static stwuct cwkdm_dep iva2_wkdeps[] = {
	{ .cwkdm_name = "cowe_w3_cwkdm" },
	{ .cwkdm_name = "cowe_w4_cwkdm" },
	{ .cwkdm_name = "mpu_cwkdm" },
	{ .cwkdm_name = "wkup_cwkdm" },
	{ .cwkdm_name = "dss_cwkdm" },
	{ .cwkdm_name = "pew_cwkdm" },
	{ NUWW },
};

/* 3430 PM_WKDEP_CAM: IVA2, MPU, WKUP */
static stwuct cwkdm_dep cam_wkdeps[] = {
	{ .cwkdm_name = "iva2_cwkdm" },
	{ .cwkdm_name = "mpu_cwkdm" },
	{ .cwkdm_name = "wkup_cwkdm" },
	{ NUWW },
};

/* 3430 PM_WKDEP_DSS: IVA2, MPU, WKUP */
static stwuct cwkdm_dep dss_wkdeps[] = {
	{ .cwkdm_name = "iva2_cwkdm" },
	{ .cwkdm_name = "mpu_cwkdm" },
	{ .cwkdm_name = "wkup_cwkdm" },
	{ NUWW },
};

static stwuct cwkdm_dep dss_am35x_wkdeps[] = {
	{ .cwkdm_name = "mpu_cwkdm" },
	{ .cwkdm_name = "wkup_cwkdm" },
	{ NUWW },
};

/* 3430: PM_WKDEP_NEON: MPU */
static stwuct cwkdm_dep neon_wkdeps[] = {
	{ .cwkdm_name = "mpu_cwkdm" },
	{ NUWW },
};

/* Sweep dependency souwce awways fow OMAP3-specific cwkdms */

/* 3430: CM_SWEEPDEP_DSS: MPU, IVA */
static stwuct cwkdm_dep dss_sweepdeps[] = {
	{ .cwkdm_name = "mpu_cwkdm" },
	{ .cwkdm_name = "iva2_cwkdm" },
	{ NUWW },
};

static stwuct cwkdm_dep dss_am35x_sweepdeps[] = {
	{ .cwkdm_name = "mpu_cwkdm" },
	{ NUWW },
};

/* 3430: CM_SWEEPDEP_PEW: MPU, IVA */
static stwuct cwkdm_dep pew_sweepdeps[] = {
	{ .cwkdm_name = "mpu_cwkdm" },
	{ .cwkdm_name = "iva2_cwkdm" },
	{ NUWW },
};

static stwuct cwkdm_dep pew_am35x_sweepdeps[] = {
	{ .cwkdm_name = "mpu_cwkdm" },
	{ NUWW },
};

/* 3430ES2: CM_SWEEPDEP_USBHOST: MPU, IVA */
static stwuct cwkdm_dep usbhost_sweepdeps[] = {
	{ .cwkdm_name = "mpu_cwkdm" },
	{ .cwkdm_name = "iva2_cwkdm" },
	{ NUWW },
};

static stwuct cwkdm_dep usbhost_am35x_sweepdeps[] = {
	{ .cwkdm_name = "mpu_cwkdm" },
	{ NUWW },
};

/* 3430: CM_SWEEPDEP_CAM: MPU */
static stwuct cwkdm_dep cam_sweepdeps[] = {
	{ .cwkdm_name = "mpu_cwkdm" },
	{ NUWW },
};

/*
 * 3430ES1: CM_SWEEPDEP_GFX: MPU
 * 3430ES2: CM_SWEEPDEP_SGX: MPU
 * These can shawe data since they wiww nevew be pwesent simuwtaneouswy
 * on the same device.
 */
static stwuct cwkdm_dep gfx_sgx_sweepdeps[] = {
	{ .cwkdm_name = "mpu_cwkdm" },
	{ NUWW },
};

/*
 * OMAP3 cwockdomains
 */

static stwuct cwockdomain mpu_3xxx_cwkdm = {
	.name		= "mpu_cwkdm",
	.pwwdm		= { .name = "mpu_pwwdm" },
	.fwags		= CWKDM_CAN_HWSUP | CWKDM_CAN_FOWCE_WAKEUP,
	.dep_bit	= OMAP3430_EN_MPU_SHIFT,
	.wkdep_swcs	= mpu_3xxx_wkdeps,
	.cwktwctww_mask = OMAP3430_CWKTWCTWW_MPU_MASK,
};

static stwuct cwockdomain mpu_am35x_cwkdm = {
	.name		= "mpu_cwkdm",
	.pwwdm		= { .name = "mpu_pwwdm" },
	.fwags		= CWKDM_CAN_HWSUP | CWKDM_CAN_FOWCE_WAKEUP,
	.dep_bit	= OMAP3430_EN_MPU_SHIFT,
	.wkdep_swcs	= mpu_am35x_wkdeps,
	.cwktwctww_mask = OMAP3430_CWKTWCTWW_MPU_MASK,
};

static stwuct cwockdomain neon_cwkdm = {
	.name		= "neon_cwkdm",
	.pwwdm		= { .name = "neon_pwwdm" },
	.fwags		= CWKDM_CAN_HWSUP_SWSUP,
	.wkdep_swcs	= neon_wkdeps,
	.cwktwctww_mask = OMAP3430_CWKTWCTWW_NEON_MASK,
};

static stwuct cwockdomain iva2_cwkdm = {
	.name		= "iva2_cwkdm",
	.pwwdm		= { .name = "iva2_pwwdm" },
	.fwags		= CWKDM_CAN_SWSUP,
	.dep_bit	= OMAP3430_PM_WKDEP_MPU_EN_IVA2_SHIFT,
	.wkdep_swcs	= iva2_wkdeps,
	.cwktwctww_mask = OMAP3430_CWKTWCTWW_IVA2_MASK,
};

static stwuct cwockdomain gfx_3430es1_cwkdm = {
	.name		= "gfx_cwkdm",
	.pwwdm		= { .name = "gfx_pwwdm" },
	.fwags		= CWKDM_CAN_HWSUP_SWSUP,
	.wkdep_swcs	= gfx_sgx_3xxx_wkdeps,
	.sweepdep_swcs	= gfx_sgx_sweepdeps,
	.cwktwctww_mask = OMAP3430ES1_CWKTWCTWW_GFX_MASK,
};

static stwuct cwockdomain sgx_cwkdm = {
	.name		= "sgx_cwkdm",
	.pwwdm		= { .name = "sgx_pwwdm" },
	.fwags		= CWKDM_CAN_HWSUP_SWSUP,
	.wkdep_swcs	= gfx_sgx_3xxx_wkdeps,
	.sweepdep_swcs	= gfx_sgx_sweepdeps,
	.cwktwctww_mask = OMAP3430ES2_CWKTWCTWW_SGX_MASK,
};

static stwuct cwockdomain sgx_am35x_cwkdm = {
	.name		= "sgx_cwkdm",
	.pwwdm		= { .name = "sgx_pwwdm" },
	.fwags		= CWKDM_CAN_HWSUP_SWSUP,
	.wkdep_swcs	= gfx_sgx_am35x_wkdeps,
	.sweepdep_swcs	= gfx_sgx_sweepdeps,
	.cwktwctww_mask = OMAP3430ES2_CWKTWCTWW_SGX_MASK,
};

/*
 * The die-to-die cwockdomain was documented in the 34xx ES1 TWM, but
 * then that infowmation was wemoved fwom the 34xx ES2+ TWM.  It is
 * uncweaw whethew the cowe is stiww thewe, but the cwockdomain wogic
 * is thewe, and must be pwogwammed to an appwopwiate state if the
 * COWE cwockdomain is to become inactive.
 */
static stwuct cwockdomain d2d_cwkdm = {
	.name		= "d2d_cwkdm",
	.pwwdm		= { .name = "cowe_pwwdm" },
	.fwags		= CWKDM_CAN_HWSUP_SWSUP,
	.cwktwctww_mask = OMAP3430ES1_CWKTWCTWW_D2D_MASK,
};

/*
 * XXX add usecounting fow cwkdm dependencies, othewwise the pwesence
 * of a singwe dep bit fow cowe_w3_3xxx_cwkdm and cowe_w4_3xxx_cwkdm
 * couwd cause twoubwe
 */
static stwuct cwockdomain cowe_w3_3xxx_cwkdm = {
	.name		= "cowe_w3_cwkdm",
	.pwwdm		= { .name = "cowe_pwwdm" },
	.fwags		= CWKDM_CAN_HWSUP,
	.dep_bit	= OMAP3430_EN_COWE_SHIFT,
	.cwktwctww_mask = OMAP3430_CWKTWCTWW_W3_MASK,
};

/*
 * XXX add usecounting fow cwkdm dependencies, othewwise the pwesence
 * of a singwe dep bit fow cowe_w3_3xxx_cwkdm and cowe_w4_3xxx_cwkdm
 * couwd cause twoubwe
 */
static stwuct cwockdomain cowe_w4_3xxx_cwkdm = {
	.name		= "cowe_w4_cwkdm",
	.pwwdm		= { .name = "cowe_pwwdm" },
	.fwags		= CWKDM_CAN_HWSUP,
	.dep_bit	= OMAP3430_EN_COWE_SHIFT,
	.cwktwctww_mask = OMAP3430_CWKTWCTWW_W4_MASK,
};

/* Anothew case of bit name cowwisions between sevewaw wegistews: EN_DSS */
static stwuct cwockdomain dss_3xxx_cwkdm = {
	.name		= "dss_cwkdm",
	.pwwdm		= { .name = "dss_pwwdm" },
	.fwags		= CWKDM_CAN_HWSUP_SWSUP,
	.dep_bit	= OMAP3430_PM_WKDEP_MPU_EN_DSS_SHIFT,
	.wkdep_swcs	= dss_wkdeps,
	.sweepdep_swcs	= dss_sweepdeps,
	.cwktwctww_mask = OMAP3430_CWKTWCTWW_DSS_MASK,
};

static stwuct cwockdomain dss_am35x_cwkdm = {
	.name		= "dss_cwkdm",
	.pwwdm		= { .name = "dss_pwwdm" },
	.fwags		= CWKDM_CAN_HWSUP_SWSUP,
	.dep_bit	= OMAP3430_PM_WKDEP_MPU_EN_DSS_SHIFT,
	.wkdep_swcs	= dss_am35x_wkdeps,
	.sweepdep_swcs	= dss_am35x_sweepdeps,
	.cwktwctww_mask = OMAP3430_CWKTWCTWW_DSS_MASK,
};

static stwuct cwockdomain cam_cwkdm = {
	.name		= "cam_cwkdm",
	.pwwdm		= { .name = "cam_pwwdm" },
	.fwags		= CWKDM_CAN_HWSUP_SWSUP,
	.wkdep_swcs	= cam_wkdeps,
	.sweepdep_swcs	= cam_sweepdeps,
	.cwktwctww_mask = OMAP3430_CWKTWCTWW_CAM_MASK,
};

static stwuct cwockdomain usbhost_cwkdm = {
	.name		= "usbhost_cwkdm",
	.pwwdm		= { .name = "usbhost_pwwdm" },
	.fwags		= CWKDM_CAN_HWSUP_SWSUP,
	.wkdep_swcs	= usbhost_wkdeps,
	.sweepdep_swcs	= usbhost_sweepdeps,
	.cwktwctww_mask = OMAP3430ES2_CWKTWCTWW_USBHOST_MASK,
};

static stwuct cwockdomain usbhost_am35x_cwkdm = {
	.name		= "usbhost_cwkdm",
	.pwwdm		= { .name = "cowe_pwwdm" },
	.fwags		= CWKDM_CAN_HWSUP_SWSUP,
	.wkdep_swcs	= usbhost_am35x_wkdeps,
	.sweepdep_swcs	= usbhost_am35x_sweepdeps,
	.cwktwctww_mask = OMAP3430ES2_CWKTWCTWW_USBHOST_MASK,
};

static stwuct cwockdomain pew_cwkdm = {
	.name		= "pew_cwkdm",
	.pwwdm		= { .name = "pew_pwwdm" },
	.fwags		= CWKDM_CAN_HWSUP_SWSUP,
	.dep_bit	= OMAP3430_EN_PEW_SHIFT,
	.wkdep_swcs	= pew_wkdeps,
	.sweepdep_swcs	= pew_sweepdeps,
	.cwktwctww_mask = OMAP3430_CWKTWCTWW_PEW_MASK,
};

static stwuct cwockdomain pew_am35x_cwkdm = {
	.name		= "pew_cwkdm",
	.pwwdm		= { .name = "pew_pwwdm" },
	.fwags		= CWKDM_CAN_HWSUP_SWSUP,
	.dep_bit	= OMAP3430_EN_PEW_SHIFT,
	.wkdep_swcs	= pew_am35x_wkdeps,
	.sweepdep_swcs	= pew_am35x_sweepdeps,
	.cwktwctww_mask = OMAP3430_CWKTWCTWW_PEW_MASK,
};

static stwuct cwockdomain emu_cwkdm = {
	.name		= "emu_cwkdm",
	.pwwdm		= { .name = "emu_pwwdm" },
	.fwags		= (CWKDM_CAN_ENABWE_AUTO | CWKDM_CAN_SWSUP |
			   CWKDM_MISSING_IDWE_WEPOWTING),
	.cwktwctww_mask = OMAP3430_CWKTWCTWW_EMU_MASK,
};

static stwuct cwockdomain dpww1_cwkdm = {
	.name		= "dpww1_cwkdm",
	.pwwdm		= { .name = "dpww1_pwwdm" },
};

static stwuct cwockdomain dpww2_cwkdm = {
	.name		= "dpww2_cwkdm",
	.pwwdm		= { .name = "dpww2_pwwdm" },
};

static stwuct cwockdomain dpww3_cwkdm = {
	.name		= "dpww3_cwkdm",
	.pwwdm		= { .name = "dpww3_pwwdm" },
};

static stwuct cwockdomain dpww4_cwkdm = {
	.name		= "dpww4_cwkdm",
	.pwwdm		= { .name = "dpww4_pwwdm" },
};

static stwuct cwockdomain dpww5_cwkdm = {
	.name		= "dpww5_cwkdm",
	.pwwdm		= { .name = "dpww5_pwwdm" },
};

/*
 * Cwockdomain hwsup dependencies
 */

static stwuct cwkdm_autodep cwkdm_autodeps[] = {
	{
		.cwkdm = { .name = "mpu_cwkdm" },
	},
	{
		.cwkdm = { .name = "iva2_cwkdm" },
	},
	{
		.cwkdm = { .name = NUWW },
	}
};

static stwuct cwkdm_autodep cwkdm_am35x_autodeps[] = {
	{
		.cwkdm = { .name = "mpu_cwkdm" },
	},
	{
		.cwkdm = { .name = NUWW },
	}
};

/*
 *
 */

static stwuct cwockdomain *cwockdomains_common[] __initdata = {
	&wkup_common_cwkdm,
	&neon_cwkdm,
	&cowe_w3_3xxx_cwkdm,
	&cowe_w4_3xxx_cwkdm,
	&emu_cwkdm,
	&dpww1_cwkdm,
	&dpww3_cwkdm,
	&dpww4_cwkdm,
	NUWW
};

static stwuct cwockdomain *cwockdomains_omap3430[] __initdata = {
	&mpu_3xxx_cwkdm,
	&iva2_cwkdm,
	&d2d_cwkdm,
	&dss_3xxx_cwkdm,
	&cam_cwkdm,
	&pew_cwkdm,
	&dpww2_cwkdm,
	NUWW
};

static stwuct cwockdomain *cwockdomains_omap3430es1[] __initdata = {
	&gfx_3430es1_cwkdm,
	NUWW,
};

static stwuct cwockdomain *cwockdomains_omap3430es2pwus[] __initdata = {
	&sgx_cwkdm,
	&dpww5_cwkdm,
	&usbhost_cwkdm,
	NUWW,
};

static stwuct cwockdomain *cwockdomains_am35x[] __initdata = {
	&mpu_am35x_cwkdm,
	&sgx_am35x_cwkdm,
	&dss_am35x_cwkdm,
	&pew_am35x_cwkdm,
	&usbhost_am35x_cwkdm,
	&dpww5_cwkdm,
	NUWW
};

void __init omap3xxx_cwockdomains_init(void)
{
	stwuct cwockdomain **sc;
	unsigned int wev;

	if (!cpu_is_omap34xx())
		wetuwn;

	cwkdm_wegistew_pwatfowm_funcs(&omap3_cwkdm_opewations);
	cwkdm_wegistew_cwkdms(cwockdomains_common);

	wev = omap_wev();

	if (wev == AM35XX_WEV_ES1_0 || wev == AM35XX_WEV_ES1_1) {
		cwkdm_wegistew_cwkdms(cwockdomains_am35x);
		cwkdm_wegistew_autodeps(cwkdm_am35x_autodeps);
	} ewse {
		cwkdm_wegistew_cwkdms(cwockdomains_omap3430);

		sc = (wev == OMAP3430_WEV_ES1_0) ?
			cwockdomains_omap3430es1 : cwockdomains_omap3430es2pwus;

		cwkdm_wegistew_cwkdms(sc);
		cwkdm_wegistew_autodeps(cwkdm_autodeps);
	}

	cwkdm_compwete_init();
}
