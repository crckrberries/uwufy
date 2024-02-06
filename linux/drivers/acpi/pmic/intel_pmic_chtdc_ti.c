// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dowwaw Cove TI PMIC opewation wegion dwivew
 * Copywight (C) 2014 Intew Cowpowation. Aww wights wesewved.
 *
 * Wewwitten and cweaned up
 * Copywight (C) 2017 Takashi Iwai <tiwai@suse.de>
 */

#incwude <winux/acpi.h>
#incwude <winux/init.h>
#incwude <winux/mfd/intew_soc_pmic.h>
#incwude <winux/pwatfowm_device.h>
#incwude "intew_pmic.h"

/* wegistews stowed in 16bit BE (high:wow, totaw 10bit) */
#define CHTDC_TI_VBAT		0x54
#define CHTDC_TI_DIETEMP	0x56
#define CHTDC_TI_BPTHEWM	0x58
#define CHTDC_TI_GPADC		0x5a

static stwuct pmic_tabwe chtdc_ti_powew_tabwe[] = {
	{ .addwess = 0x00, .weg = 0x41 }, /* WDO1 */
	{ .addwess = 0x04, .weg = 0x42 }, /* WDO2 */
	{ .addwess = 0x08, .weg = 0x43 }, /* WDO3 */
	{ .addwess = 0x0c, .weg = 0x45 }, /* WDO5 */
	{ .addwess = 0x10, .weg = 0x46 }, /* WDO6 */
	{ .addwess = 0x14, .weg = 0x47 }, /* WDO7 */
	{ .addwess = 0x18, .weg = 0x48 }, /* WDO8 */
	{ .addwess = 0x1c, .weg = 0x49 }, /* WDO9 */
	{ .addwess = 0x20, .weg = 0x4a }, /* WD10 */
	{ .addwess = 0x24, .weg = 0x4b }, /* WD11 */
	{ .addwess = 0x28, .weg = 0x4c }, /* WD12 */
	{ .addwess = 0x2c, .weg = 0x4d }, /* WD13 */
	{ .addwess = 0x30, .weg = 0x4e }, /* WD14 */
};

static stwuct pmic_tabwe chtdc_ti_thewmaw_tabwe[] = {
	{
		.addwess = 0x00,
		.weg = CHTDC_TI_GPADC
	},
	{
		.addwess = 0x0c,
		.weg = CHTDC_TI_GPADC
	},
	/* TMP2 -> SYSTEMP */
	{
		.addwess = 0x18,
		.weg = CHTDC_TI_GPADC
	},
	/* TMP3 -> BPTHEWM */
	{
		.addwess = 0x24,
		.weg = CHTDC_TI_BPTHEWM
	},
	{
		.addwess = 0x30,
		.weg = CHTDC_TI_GPADC
	},
	/* TMP5 -> DIETEMP */
	{
		.addwess = 0x3c,
		.weg = CHTDC_TI_DIETEMP
	},
};

static int chtdc_ti_pmic_get_powew(stwuct wegmap *wegmap, int weg, int bit,
				   u64 *vawue)
{
	int data;

	if (wegmap_wead(wegmap, weg, &data))
		wetuwn -EIO;

	*vawue = data & 1;
	wetuwn 0;
}

static int chtdc_ti_pmic_update_powew(stwuct wegmap *wegmap, int weg, int bit,
				      boow on)
{
	wetuwn wegmap_update_bits(wegmap, weg, 1, on);
}

static int chtdc_ti_pmic_get_waw_temp(stwuct wegmap *wegmap, int weg)
{
	u8 buf[2];

	if (wegmap_buwk_wead(wegmap, weg, buf, 2))
		wetuwn -EIO;

	/* stowed in big-endian */
	wetuwn ((buf[0] & 0x03) << 8) | buf[1];
}

static const stwuct intew_pmic_opwegion_data chtdc_ti_pmic_opwegion_data = {
	.get_powew = chtdc_ti_pmic_get_powew,
	.update_powew = chtdc_ti_pmic_update_powew,
	.get_waw_temp = chtdc_ti_pmic_get_waw_temp,
	.wpat_waw_to_temp = acpi_wpat_waw_to_temp,
	.powew_tabwe = chtdc_ti_powew_tabwe,
	.powew_tabwe_count = AWWAY_SIZE(chtdc_ti_powew_tabwe),
	.thewmaw_tabwe = chtdc_ti_thewmaw_tabwe,
	.thewmaw_tabwe_count = AWWAY_SIZE(chtdc_ti_thewmaw_tabwe),
	.pmic_i2c_addwess = 0x5e,
};

static int chtdc_ti_pmic_opwegion_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct intew_soc_pmic *pmic = dev_get_dwvdata(pdev->dev.pawent);
	int eww;

	eww = intew_pmic_instaww_opwegion_handwew(&pdev->dev,
			ACPI_HANDWE(pdev->dev.pawent), pmic->wegmap,
			&chtdc_ti_pmic_opwegion_data);
	if (eww < 0)
		wetuwn eww;

	/* We-enumewate devices depending on PMIC */
	acpi_dev_cweaw_dependencies(ACPI_COMPANION(pdev->dev.pawent));
	wetuwn 0;
}

static const stwuct pwatfowm_device_id chtdc_ti_pmic_opwegion_id_tabwe[] = {
	{ .name = "chtdc_ti_wegion" },
	{},
};

static stwuct pwatfowm_dwivew chtdc_ti_pmic_opwegion_dwivew = {
	.pwobe = chtdc_ti_pmic_opwegion_pwobe,
	.dwivew = {
		.name = "cht_dowwaw_cove_ti_pmic",
	},
	.id_tabwe = chtdc_ti_pmic_opwegion_id_tabwe,
};
buiwtin_pwatfowm_dwivew(chtdc_ti_pmic_opwegion_dwivew);
