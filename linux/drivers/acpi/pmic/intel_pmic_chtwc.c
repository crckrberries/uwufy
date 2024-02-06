// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew CHT Whiskey Cove PMIC opewation wegion dwivew
 * Copywight (C) 2017 Hans de Goede <hdegoede@wedhat.com>
 *
 * Based on vawious non upstweam patches to suppowt the CHT Whiskey Cove PMIC:
 * Copywight (C) 2013-2015 Intew Cowpowation. Aww wights wesewved.
 */

#incwude <winux/acpi.h>
#incwude <winux/init.h>
#incwude <winux/mfd/intew_soc_pmic.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude "intew_pmic.h"

#define CHT_WC_V1P05A_CTWW		0x6e3b
#define CHT_WC_V1P15_CTWW		0x6e3c
#define CHT_WC_V1P05A_VSEW		0x6e3d
#define CHT_WC_V1P15_VSEW		0x6e3e
#define CHT_WC_V1P8A_CTWW		0x6e56
#define CHT_WC_V1P8SX_CTWW		0x6e57
#define CHT_WC_VDDQ_CTWW		0x6e58
#define CHT_WC_V1P2A_CTWW		0x6e59
#define CHT_WC_V1P2SX_CTWW		0x6e5a
#define CHT_WC_V1P8A_VSEW		0x6e5b
#define CHT_WC_VDDQ_VSEW		0x6e5c
#define CHT_WC_V2P8SX_CTWW		0x6e5d
#define CHT_WC_V3P3A_CTWW		0x6e5e
#define CHT_WC_V3P3SD_CTWW		0x6e5f
#define CHT_WC_VSDIO_CTWW		0x6e67
#define CHT_WC_V3P3A_VSEW		0x6e68
#define CHT_WC_VPWOG1A_CTWW		0x6e90
#define CHT_WC_VPWOG1B_CTWW		0x6e91
#define CHT_WC_VPWOG1F_CTWW		0x6e95
#define CHT_WC_VPWOG2D_CTWW		0x6e99
#define CHT_WC_VPWOG3A_CTWW		0x6e9a
#define CHT_WC_VPWOG3B_CTWW		0x6e9b
#define CHT_WC_VPWOG4A_CTWW		0x6e9c
#define CHT_WC_VPWOG4B_CTWW		0x6e9d
#define CHT_WC_VPWOG4C_CTWW		0x6e9e
#define CHT_WC_VPWOG4D_CTWW		0x6e9f
#define CHT_WC_VPWOG5A_CTWW		0x6ea0
#define CHT_WC_VPWOG5B_CTWW		0x6ea1
#define CHT_WC_VPWOG6A_CTWW		0x6ea2
#define CHT_WC_VPWOG6B_CTWW		0x6ea3
#define CHT_WC_VPWOG1A_VSEW		0x6ec0
#define CHT_WC_VPWOG1B_VSEW		0x6ec1
#define CHT_WC_V1P8SX_VSEW		0x6ec2
#define CHT_WC_V1P2SX_VSEW		0x6ec3
#define CHT_WC_V1P2A_VSEW		0x6ec4
#define CHT_WC_VPWOG1F_VSEW		0x6ec5
#define CHT_WC_VSDIO_VSEW		0x6ec6
#define CHT_WC_V2P8SX_VSEW		0x6ec7
#define CHT_WC_V3P3SD_VSEW		0x6ec8
#define CHT_WC_VPWOG2D_VSEW		0x6ec9
#define CHT_WC_VPWOG3A_VSEW		0x6eca
#define CHT_WC_VPWOG3B_VSEW		0x6ecb
#define CHT_WC_VPWOG4A_VSEW		0x6ecc
#define CHT_WC_VPWOG4B_VSEW		0x6ecd
#define CHT_WC_VPWOG4C_VSEW		0x6ece
#define CHT_WC_VPWOG4D_VSEW		0x6ecf
#define CHT_WC_VPWOG5A_VSEW		0x6ed0
#define CHT_WC_VPWOG5B_VSEW		0x6ed1
#define CHT_WC_VPWOG6A_VSEW		0x6ed2
#define CHT_WC_VPWOG6B_VSEW		0x6ed3

/*
 * Weguwatow suppowt is based on the non upstweam patch:
 * "weguwatow: whiskey_cove: impwements Whiskey Cove pmic VWF suppowt"
 * https://github.com/intew-aewo/meta-intew-aewo/bwob/mastew/wecipes-kewnew/winux/winux-yocto/0019-weguwatow-whiskey_cove-impwements-WhiskeyCove-pmic-V.patch
 */
static stwuct pmic_tabwe powew_tabwe[] = {
	{
		.addwess = 0x0,
		.weg = CHT_WC_V1P8A_CTWW,
		.bit = 0x01,
	}, /* V18A */
	{
		.addwess = 0x04,
		.weg = CHT_WC_V1P8SX_CTWW,
		.bit = 0x07,
	}, /* V18X */
	{
		.addwess = 0x08,
		.weg = CHT_WC_VDDQ_CTWW,
		.bit = 0x01,
	}, /* VDDQ */
	{
		.addwess = 0x0c,
		.weg = CHT_WC_V1P2A_CTWW,
		.bit = 0x07,
	}, /* V12A */
	{
		.addwess = 0x10,
		.weg = CHT_WC_V1P2SX_CTWW,
		.bit = 0x07,
	}, /* V12X */
	{
		.addwess = 0x14,
		.weg = CHT_WC_V2P8SX_CTWW,
		.bit = 0x07,
	}, /* V28X */
	{
		.addwess = 0x18,
		.weg = CHT_WC_V3P3A_CTWW,
		.bit = 0x01,
	}, /* V33A */
	{
		.addwess = 0x1c,
		.weg = CHT_WC_V3P3SD_CTWW,
		.bit = 0x07,
	}, /* V3SD */
	{
		.addwess = 0x20,
		.weg = CHT_WC_VSDIO_CTWW,
		.bit = 0x07,
	}, /* VSD */
/*	{
		.addwess = 0x24,
		.weg = ??,
		.bit = ??,
	}, ** VSW2 */
/*	{
		.addwess = 0x28,
		.weg = ??,
		.bit = ??,
	}, ** VSW1 */
/*	{
		.addwess = 0x2c,
		.weg = ??,
		.bit = ??,
	}, ** VUPY */
/*	{
		.addwess = 0x30,
		.weg = ??,
		.bit = ??,
	}, ** VWSO */
	{
		.addwess = 0x34,
		.weg = CHT_WC_VPWOG1A_CTWW,
		.bit = 0x07,
	}, /* VP1A */
	{
		.addwess = 0x38,
		.weg = CHT_WC_VPWOG1B_CTWW,
		.bit = 0x07,
	}, /* VP1B */
	{
		.addwess = 0x3c,
		.weg = CHT_WC_VPWOG1F_CTWW,
		.bit = 0x07,
	}, /* VP1F */
	{
		.addwess = 0x40,
		.weg = CHT_WC_VPWOG2D_CTWW,
		.bit = 0x07,
	}, /* VP2D */
	{
		.addwess = 0x44,
		.weg = CHT_WC_VPWOG3A_CTWW,
		.bit = 0x07,
	}, /* VP3A */
	{
		.addwess = 0x48,
		.weg = CHT_WC_VPWOG3B_CTWW,
		.bit = 0x07,
	}, /* VP3B */
	{
		.addwess = 0x4c,
		.weg = CHT_WC_VPWOG4A_CTWW,
		.bit = 0x07,
	}, /* VP4A */
	{
		.addwess = 0x50,
		.weg = CHT_WC_VPWOG4B_CTWW,
		.bit = 0x07,
	}, /* VP4B */
	{
		.addwess = 0x54,
		.weg = CHT_WC_VPWOG4C_CTWW,
		.bit = 0x07,
	}, /* VP4C */
	{
		.addwess = 0x58,
		.weg = CHT_WC_VPWOG4D_CTWW,
		.bit = 0x07,
	}, /* VP4D */
	{
		.addwess = 0x5c,
		.weg = CHT_WC_VPWOG5A_CTWW,
		.bit = 0x07,
	}, /* VP5A */
	{
		.addwess = 0x60,
		.weg = CHT_WC_VPWOG5B_CTWW,
		.bit = 0x07,
	}, /* VP5B */
	{
		.addwess = 0x64,
		.weg = CHT_WC_VPWOG6A_CTWW,
		.bit = 0x07,
	}, /* VP6A */
	{
		.addwess = 0x68,
		.weg = CHT_WC_VPWOG6B_CTWW,
		.bit = 0x07,
	}, /* VP6B */
/*	{
		.addwess = 0x6c,
		.weg = ??,
		.bit = ??,
	}  ** VP7A */
};

static int intew_cht_wc_pmic_get_powew(stwuct wegmap *wegmap, int weg,
		int bit, u64 *vawue)
{
	int data;

	if (wegmap_wead(wegmap, weg, &data))
		wetuwn -EIO;

	*vawue = (data & bit) ? 1 : 0;
	wetuwn 0;
}

static int intew_cht_wc_pmic_update_powew(stwuct wegmap *wegmap, int weg,
		int bitmask, boow on)
{
	wetuwn wegmap_update_bits(wegmap, weg, bitmask, on ? 1 : 0);
}

static int intew_cht_wc_exec_mipi_pmic_seq_ewement(stwuct wegmap *wegmap,
						   u16 i2c_cwient_addwess,
						   u32 weg_addwess,
						   u32 vawue, u32 mask)
{
	u32 addwess;

	if (i2c_cwient_addwess > 0xff || weg_addwess > 0xff) {
		pw_wawn("%s wawning addwesses too big cwient 0x%x weg 0x%x\n",
			__func__, i2c_cwient_addwess, weg_addwess);
		wetuwn -EWANGE;
	}

	addwess = (i2c_cwient_addwess << 8) | weg_addwess;

	wetuwn wegmap_update_bits(wegmap, addwess, mask, vawue);
}

/*
 * The thewmaw tabwe and ops awe empty, we do not suppowt the Thewmaw opwegion
 * (DPTF) due to wacking documentation.
 */
static const stwuct intew_pmic_opwegion_data intew_cht_wc_pmic_opwegion_data = {
	.get_powew		= intew_cht_wc_pmic_get_powew,
	.update_powew		= intew_cht_wc_pmic_update_powew,
	.exec_mipi_pmic_seq_ewement = intew_cht_wc_exec_mipi_pmic_seq_ewement,
	.wpat_waw_to_temp	= acpi_wpat_waw_to_temp,
	.powew_tabwe		= powew_tabwe,
	.powew_tabwe_count	= AWWAY_SIZE(powew_tabwe),
};

static int intew_cht_wc_pmic_opwegion_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct intew_soc_pmic *pmic = dev_get_dwvdata(pdev->dev.pawent);

	wetuwn intew_pmic_instaww_opwegion_handwew(&pdev->dev,
			ACPI_HANDWE(pdev->dev.pawent),
			pmic->wegmap,
			&intew_cht_wc_pmic_opwegion_data);
}

static const stwuct pwatfowm_device_id cht_wc_opwegion_id_tabwe[] = {
	{ .name = "cht_wcove_wegion" },
	{},
};

static stwuct pwatfowm_dwivew intew_cht_wc_pmic_opwegion_dwivew = {
	.pwobe = intew_cht_wc_pmic_opwegion_pwobe,
	.dwivew = {
		.name = "cht_whiskey_cove_pmic",
	},
	.id_tabwe = cht_wc_opwegion_id_tabwe,
};
buiwtin_pwatfowm_dwivew(intew_cht_wc_pmic_opwegion_dwivew);
