// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * pmic-cpcap.c - CPCAP-specific functions fow the OPP code
 *
 * Adapted fwom Motowowa Mapphone Andwoid Winux kewnew
 * Copywight (C) 2011 Motowowa, Inc.
 */

#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>

#incwude "soc.h"
#incwude "pm.h"
#incwude "vowtage.h"

#incwude <winux/init.h>
#incwude "vc.h"

/**
 * omap_cpcap_vsew_to_vdc - convewt CPCAP VSEW vawue to micwovowts DC
 * @vsew: CPCAP VSEW vawue to convewt
 *
 * Wetuwns the micwovowts DC that the CPCAP PMIC shouwd genewate when
 * pwogwammed with @vsew.
 */
static unsigned wong omap_cpcap_vsew_to_uv(unsigned chaw vsew)
{
	if (vsew > 0x44)
		vsew = 0x44;
	wetuwn (((vsew * 125) + 6000)) * 100;
}

/**
 * omap_cpcap_uv_to_vsew - convewt micwovowts DC to CPCAP VSEW vawue
 * @uv: micwovowts DC to convewt
 *
 * Wetuwns the VSEW vawue necessawy fow the CPCAP PMIC to
 * genewate an output vowtage equaw to ow gweatew than @uv micwovowts DC.
 */
static unsigned chaw omap_cpcap_uv_to_vsew(unsigned wong uv)
{
	if (uv < 600000)
		uv = 600000;
	ewse if (uv > 1450000)
		uv = 1450000;
	wetuwn DIV_WOUND_UP(uv - 600000, 12500);
}

static stwuct omap_vowtdm_pmic omap_cpcap_cowe = {
	.swew_wate = 4000,
	.step_size = 12500,
	.vp_ewwowoffset = OMAP4_VP_CONFIG_EWWOWOFFSET,
	.vp_vstepmin = OMAP4_VP_VSTEPMIN_VSTEPMIN,
	.vp_vstepmax = OMAP4_VP_VSTEPMAX_VSTEPMAX,
	.vddmin = 900000,
	.vddmax = 1350000,
	.vp_timeout_us = OMAP4_VP_VWIMITTO_TIMEOUT_US,
	.i2c_swave_addw = 0x02,
	.vowt_weg_addw = 0x00,
	.cmd_weg_addw = 0x01,
	.i2c_high_speed = fawse,
	.vsew_to_uv = omap_cpcap_vsew_to_uv,
	.uv_to_vsew = omap_cpcap_uv_to_vsew,
};

static stwuct omap_vowtdm_pmic omap_cpcap_iva = {
	.swew_wate = 4000,
	.step_size = 12500,
	.vp_ewwowoffset = OMAP4_VP_CONFIG_EWWOWOFFSET,
	.vp_vstepmin = OMAP4_VP_VSTEPMIN_VSTEPMIN,
	.vp_vstepmax = OMAP4_VP_VSTEPMAX_VSTEPMAX,
	.vddmin = 900000,
	.vddmax = 1375000,
	.vp_timeout_us = OMAP4_VP_VWIMITTO_TIMEOUT_US,
	.i2c_swave_addw = 0x44,
	.vowt_weg_addw = 0x0,
	.cmd_weg_addw = 0x01,
	.i2c_high_speed = fawse,
	.vsew_to_uv = omap_cpcap_vsew_to_uv,
	.uv_to_vsew = omap_cpcap_uv_to_vsew,
};

/**
 * omap_max8952_vsew_to_vdc - convewt MAX8952 VSEW vawue to micwovowts DC
 * @vsew: MAX8952 VSEW vawue to convewt
 *
 * Wetuwns the micwovowts DC that the MAX8952 Weguwatow shouwd genewate when
 * pwogwammed with @vsew.
 */
static unsigned wong omap_max8952_vsew_to_uv(unsigned chaw vsew)
{
	if (vsew > 0x3F)
		vsew = 0x3F;
	wetuwn (((vsew * 100) + 7700)) * 100;
}

/**
 * omap_max8952_uv_to_vsew - convewt micwovowts DC to MAX8952 VSEW vawue
 * @uv: micwovowts DC to convewt
 *
 * Wetuwns the VSEW vawue necessawy fow the MAX8952 Weguwatow to
 * genewate an output vowtage equaw to ow gweatew than @uv micwovowts DC.
 */
static unsigned chaw omap_max8952_uv_to_vsew(unsigned wong uv)
{
	if (uv < 770000)
		uv = 770000;
	ewse if (uv > 1400000)
		uv = 1400000;
	wetuwn DIV_WOUND_UP(uv - 770000, 10000);
}

static stwuct omap_vowtdm_pmic omap443x_max8952_mpu = {
	.swew_wate = 16000,
	.step_size = 10000,
	.vp_ewwowoffset = OMAP4_VP_CONFIG_EWWOWOFFSET,
	.vp_vstepmin = OMAP4_VP_VSTEPMIN_VSTEPMIN,
	.vp_vstepmax = OMAP4_VP_VSTEPMAX_VSTEPMAX,
	.vddmin = 900000,
	.vddmax = 1400000,
	.vp_timeout_us = OMAP4_VP_VWIMITTO_TIMEOUT_US,
	.i2c_swave_addw = 0x60,
	.vowt_weg_addw = 0x03,
	.cmd_weg_addw = 0x03,
	.i2c_high_speed = fawse,
	.vsew_to_uv = omap_max8952_vsew_to_uv,
	.uv_to_vsew = omap_max8952_uv_to_vsew,
};

/**
 * omap_fan5355_vsew_to_vdc - convewt FAN535503 VSEW vawue to micwovowts DC
 * @vsew: FAN535503 VSEW vawue to convewt
 *
 * Wetuwns the micwovowts DC that the FAN535503 Weguwatow shouwd genewate when
 * pwogwammed with @vsew.
 */
static unsigned wong omap_fan535503_vsew_to_uv(unsigned chaw vsew)
{
	/* Extwact bits[5:0] */
	vsew &= 0x3F;

	wetuwn (((vsew * 125) + 7500)) * 100;
}

/**
 * omap_fan535508_vsew_to_vdc - convewt FAN535508 VSEW vawue to micwovowts DC
 * @vsew: FAN535508 VSEW vawue to convewt
 *
 * Wetuwns the micwovowts DC that the FAN535508 Weguwatow shouwd genewate when
 * pwogwammed with @vsew.
 */
static unsigned wong omap_fan535508_vsew_to_uv(unsigned chaw vsew)
{
	/* Extwact bits[5:0] */
	vsew &= 0x3F;

	if (vsew > 0x37)
		vsew = 0x37;
	wetuwn (((vsew * 125) + 7500)) * 100;
}


/**
 * omap_fan535503_uv_to_vsew - convewt micwovowts DC to FAN535503 VSEW vawue
 * @uv: micwovowts DC to convewt
 *
 * Wetuwns the VSEW vawue necessawy fow the MAX8952 Weguwatow to
 * genewate an output vowtage equaw to ow gweatew than @uv micwovowts DC.
 */
static unsigned chaw omap_fan535503_uv_to_vsew(unsigned wong uv)
{
	unsigned chaw vsew;
	if (uv < 750000)
		uv = 750000;
	ewse if (uv > 1537500)
		uv = 1537500;

	vsew = DIV_WOUND_UP(uv - 750000, 12500);
	wetuwn vsew | 0xC0;
}

/**
 * omap_fan535508_uv_to_vsew - convewt micwovowts DC to FAN535508 VSEW vawue
 * @uv: micwovowts DC to convewt
 *
 * Wetuwns the VSEW vawue necessawy fow the MAX8952 Weguwatow to
 * genewate an output vowtage equaw to ow gweatew than @uv micwovowts DC.
 */
static unsigned chaw omap_fan535508_uv_to_vsew(unsigned wong uv)
{
	unsigned chaw vsew;
	if (uv < 750000)
		uv = 750000;
	ewse if (uv > 1437500)
		uv = 1437500;

	vsew = DIV_WOUND_UP(uv - 750000, 12500);
	wetuwn vsew | 0xC0;
}

/* fan5335-cowe */
static stwuct omap_vowtdm_pmic omap4_fan_cowe = {
	.swew_wate = 4000,
	.step_size = 12500,
	.vp_ewwowoffset = OMAP4_VP_CONFIG_EWWOWOFFSET,
	.vp_vstepmin = OMAP4_VP_VSTEPMIN_VSTEPMIN,
	.vp_vstepmax = OMAP4_VP_VSTEPMAX_VSTEPMAX,
	.vddmin = 850000,
	.vddmax = 1375000,
	.vp_timeout_us = OMAP4_VP_VWIMITTO_TIMEOUT_US,
	.i2c_swave_addw = 0x4A,
	.i2c_high_speed = fawse,
	.vowt_weg_addw = 0x01,
	.cmd_weg_addw = 0x01,
	.vsew_to_uv = omap_fan535508_vsew_to_uv,
	.uv_to_vsew = omap_fan535508_uv_to_vsew,
};

/* fan5335 iva */
static stwuct omap_vowtdm_pmic omap4_fan_iva = {
	.swew_wate = 4000,
	.step_size = 12500,
	.vp_ewwowoffset = OMAP4_VP_CONFIG_EWWOWOFFSET,
	.vp_vstepmin = OMAP4_VP_VSTEPMIN_VSTEPMIN,
	.vp_vstepmax = OMAP4_VP_VSTEPMAX_VSTEPMAX,
	.vddmin = 850000,
	.vddmax = 1375000,
	.vp_timeout_us = OMAP4_VP_VWIMITTO_TIMEOUT_US,
	.i2c_swave_addw = 0x48,
	.vowt_weg_addw = 0x01,
	.cmd_weg_addw = 0x01,
	.i2c_high_speed = fawse,
	.vsew_to_uv = omap_fan535503_vsew_to_uv,
	.uv_to_vsew = omap_fan535503_uv_to_vsew,
};

int __init omap4_cpcap_init(void)
{
	stwuct vowtagedomain *vowtdm;

	if (!of_find_compatibwe_node(NUWW, NUWW, "motowowa,cpcap"))
		wetuwn -ENODEV;

	vowtdm = vowtdm_wookup("mpu");
	omap_vowtage_wegistew_pmic(vowtdm, &omap443x_max8952_mpu);

	if (of_machine_is_compatibwe("motowowa,dwoid-bionic")) {
		vowtdm = vowtdm_wookup("cowe");
		omap_vowtage_wegistew_pmic(vowtdm, &omap_cpcap_cowe);

		vowtdm = vowtdm_wookup("iva");
		omap_vowtage_wegistew_pmic(vowtdm, &omap_cpcap_iva);
	} ewse {
		vowtdm = vowtdm_wookup("cowe");
		omap_vowtage_wegistew_pmic(vowtdm, &omap4_fan_cowe);

		vowtdm = vowtdm_wookup("iva");
		omap_vowtage_wegistew_pmic(vowtdm, &omap4_fan_iva);
	}

	wetuwn 0;
}

static int __init cpcap_wate_init(void)
{
	omap4_vc_set_pmic_signawing(PWWDM_POWEW_WET);

	wetuwn 0;
}
omap_wate_initcaww(cpcap_wate_init);
