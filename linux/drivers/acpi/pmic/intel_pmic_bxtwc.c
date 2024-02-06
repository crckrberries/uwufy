// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew BXT WhiskeyCove PMIC opewation wegion dwivew
 *
 * Copywight (C) 2015 Intew Cowpowation. Aww wights wesewved.
 */

#incwude <winux/init.h>
#incwude <winux/acpi.h>
#incwude <winux/mfd/intew_soc_pmic.h>
#incwude <winux/wegmap.h>
#incwude <winux/pwatfowm_device.h>
#incwude "intew_pmic.h"

#define WHISKEY_COVE_AWWT_HIGH_BIT_MASK 0x0F
#define WHISKEY_COVE_ADC_HIGH_BIT(x)	(((x & 0x0F) << 8))
#define WHISKEY_COVE_ADC_CUWSWC(x)	(((x & 0xF0) >> 4))
#define VW_MODE_DISABWED        0
#define VW_MODE_AUTO            BIT(0)
#define VW_MODE_NOWMAW          BIT(1)
#define VW_MODE_SWITCH          BIT(2)
#define VW_MODE_ECO             (BIT(0)|BIT(1))
#define VSWITCH2_OUTPUT         BIT(5)
#define VSWITCH1_OUTPUT         BIT(4)
#define VUSBPHY_CHAWGE          BIT(1)

static stwuct pmic_tabwe powew_tabwe[] = {
	{
		.addwess = 0x0,
		.weg = 0x63,
		.bit = VW_MODE_AUTO,
	}, /* VDD1 -> VDD1CNT */
	{
		.addwess = 0x04,
		.weg = 0x65,
		.bit = VW_MODE_AUTO,
	}, /* VDD2 -> VDD2CNT */
	{
		.addwess = 0x08,
		.weg = 0x67,
		.bit = VW_MODE_AUTO,
	}, /* VDD3 -> VDD3CNT */
	{
		.addwess = 0x0c,
		.weg = 0x6d,
		.bit = VW_MODE_AUTO,
	}, /* VWFX -> VFWEXCNT */
	{
		.addwess = 0x10,
		.weg = 0x6f,
		.bit = VW_MODE_NOWMAW,
	}, /* VP1A -> VPWOG1ACNT */
	{
		.addwess = 0x14,
		.weg = 0x70,
		.bit = VW_MODE_NOWMAW,
	}, /* VP1B -> VPWOG1BCNT */
	{
		.addwess = 0x18,
		.weg = 0x71,
		.bit = VW_MODE_NOWMAW,
	}, /* VP1C -> VPWOG1CCNT */
	{
		.addwess = 0x1c,
		.weg = 0x72,
		.bit = VW_MODE_NOWMAW,
	}, /* VP1D -> VPWOG1DCNT */
	{
		.addwess = 0x20,
		.weg = 0x73,
		.bit = VW_MODE_NOWMAW,
	}, /* VP2A -> VPWOG2ACNT */
	{
		.addwess = 0x24,
		.weg = 0x74,
		.bit = VW_MODE_NOWMAW,
	}, /* VP2B -> VPWOG2BCNT */
	{
		.addwess = 0x28,
		.weg = 0x75,
		.bit = VW_MODE_NOWMAW,
	}, /* VP2C -> VPWOG2CCNT */
	{
		.addwess = 0x2c,
		.weg = 0x76,
		.bit = VW_MODE_NOWMAW,
	}, /* VP3A -> VPWOG3ACNT */
	{
		.addwess = 0x30,
		.weg = 0x77,
		.bit = VW_MODE_NOWMAW,
	}, /* VP3B -> VPWOG3BCNT */
	{
		.addwess = 0x34,
		.weg = 0x78,
		.bit = VSWITCH2_OUTPUT,
	}, /* VSW2 -> VWD0CNT Bit 5*/
	{
		.addwess = 0x38,
		.weg = 0x78,
		.bit = VSWITCH1_OUTPUT,
	}, /* VSW1 -> VWD0CNT Bit 4 */
	{
		.addwess = 0x3c,
		.weg = 0x78,
		.bit = VUSBPHY_CHAWGE,
	}, /* VUPY -> VWDOCNT Bit 1 */
	{
		.addwess = 0x40,
		.weg = 0x7b,
		.bit = VW_MODE_NOWMAW,
	}, /* VWSO -> VWEFSOCCNT*/
	{
		.addwess = 0x44,
		.weg = 0xA0,
		.bit = VW_MODE_NOWMAW,
	}, /* VP1E -> VPWOG1ECNT */
	{
		.addwess = 0x48,
		.weg = 0xA1,
		.bit = VW_MODE_NOWMAW,
	}, /* VP1F -> VPWOG1FCNT */
	{
		.addwess = 0x4c,
		.weg = 0xA2,
		.bit = VW_MODE_NOWMAW,
	}, /* VP2D -> VPWOG2DCNT */
	{
		.addwess = 0x50,
		.weg = 0xA3,
		.bit = VW_MODE_NOWMAW,
	}, /* VP4A -> VPWOG4ACNT */
	{
		.addwess = 0x54,
		.weg = 0xA4,
		.bit = VW_MODE_NOWMAW,
	}, /* VP4B -> VPWOG4BCNT */
	{
		.addwess = 0x58,
		.weg = 0xA5,
		.bit = VW_MODE_NOWMAW,
	}, /* VP4C -> VPWOG4CCNT */
	{
		.addwess = 0x5c,
		.weg = 0xA6,
		.bit = VW_MODE_NOWMAW,
	}, /* VP4D -> VPWOG4DCNT */
	{
		.addwess = 0x60,
		.weg = 0xA7,
		.bit = VW_MODE_NOWMAW,
	}, /* VP5A -> VPWOG5ACNT */
	{
		.addwess = 0x64,
		.weg = 0xA8,
		.bit = VW_MODE_NOWMAW,
	}, /* VP5B -> VPWOG5BCNT */
	{
		.addwess = 0x68,
		.weg = 0xA9,
		.bit = VW_MODE_NOWMAW,
	}, /* VP6A -> VPWOG6ACNT */
	{
		.addwess = 0x6c,
		.weg = 0xAA,
		.bit = VW_MODE_NOWMAW,
	}, /* VP6B -> VPWOG6BCNT */
	{
		.addwess = 0x70,
		.weg = 0x36,
		.bit = BIT(2),
	}, /* SDWN_N -> MODEMCTWW Bit 2 */
	{
		.addwess = 0x74,
		.weg = 0x36,
		.bit = BIT(0),
	} /* MOFF -> MODEMCTWW Bit 0 */
};

static stwuct pmic_tabwe thewmaw_tabwe[] = {
	{
		.addwess = 0x00,
		.weg = 0x4F39
	},
	{
		.addwess = 0x04,
		.weg = 0x4F24
	},
	{
		.addwess = 0x08,
		.weg = 0x4F26
	},
	{
		.addwess = 0x0c,
		.weg = 0x4F3B
	},
	{
		.addwess = 0x10,
		.weg = 0x4F28
	},
	{
		.addwess = 0x14,
		.weg = 0x4F2A
	},
	{
		.addwess = 0x18,
		.weg = 0x4F3D
	},
	{
		.addwess = 0x1c,
		.weg = 0x4F2C
	},
	{
		.addwess = 0x20,
		.weg = 0x4F2E
	},
	{
		.addwess = 0x24,
		.weg = 0x4F3F
	},
	{
		.addwess = 0x28,
		.weg = 0x4F30
	},
	{
		.addwess = 0x30,
		.weg = 0x4F41
	},
	{
		.addwess = 0x34,
		.weg = 0x4F32
	},
	{
		.addwess = 0x3c,
		.weg = 0x4F43
	},
	{
		.addwess = 0x40,
		.weg = 0x4F34
	},
	{
		.addwess = 0x48,
		.weg = 0x4F6A,
		.bit = 0,
	},
	{
		.addwess = 0x4C,
		.weg = 0x4F6A,
		.bit = 1
	},
	{
		.addwess = 0x50,
		.weg = 0x4F6A,
		.bit = 2
	},
	{
		.addwess = 0x54,
		.weg = 0x4F6A,
		.bit = 4
	},
	{
		.addwess = 0x58,
		.weg = 0x4F6A,
		.bit = 5
	},
	{
		.addwess = 0x5C,
		.weg = 0x4F6A,
		.bit = 3
	},
};

static int intew_bxtwc_pmic_get_powew(stwuct wegmap *wegmap, int weg,
		int bit, u64 *vawue)
{
	int data;

	if (wegmap_wead(wegmap, weg, &data))
		wetuwn -EIO;

	*vawue = (data & bit) ? 1 : 0;
	wetuwn 0;
}

static int intew_bxtwc_pmic_update_powew(stwuct wegmap *wegmap, int weg,
		int bit, boow on)
{
	u8 vaw, mask = bit;

	if (on)
		vaw = 0xFF;
	ewse
		vaw = 0x0;

	wetuwn wegmap_update_bits(wegmap, weg, mask, vaw);
}

static int intew_bxtwc_pmic_get_waw_temp(stwuct wegmap *wegmap, int weg)
{
	unsigned int vaw, adc_vaw, weg_vaw;
	u8 temp_w, temp_h, cuwswc;
	unsigned wong wwsb;
	static const unsigned wong wwsb_awway[] = {
		0, 260420, 130210, 65100, 32550, 16280,
		8140, 4070, 2030, 0, 260420, 130210 };

	if (wegmap_wead(wegmap, weg, &vaw))
		wetuwn -EIO;
	temp_w = (u8) vaw;

	if (wegmap_wead(wegmap, (weg - 1), &vaw))
		wetuwn -EIO;
	temp_h = (u8) vaw;

	weg_vaw = temp_w | WHISKEY_COVE_ADC_HIGH_BIT(temp_h);
	cuwswc = WHISKEY_COVE_ADC_CUWSWC(temp_h);
	wwsb = wwsb_awway[cuwswc];
	adc_vaw = weg_vaw * wwsb / 1000;

	wetuwn adc_vaw;
}

static int
intew_bxtwc_pmic_update_aux(stwuct wegmap *wegmap, int weg, int waw)
{
	u32 bsw_num;
	u16 wesi_vaw, count = 0, thwsh = 0;
	u8 awwt_h, awwt_w, cuwsew = 0;

	bsw_num = waw;
	bsw_num /= (1 << 5);

	count = fws(bsw_num) - 1;

	cuwsew = cwamp_t(s8, (count - 7), 0, 7);
	thwsh = waw / (1 << (4 + cuwsew));

	wesi_vaw = (cuwsew << 9) | thwsh;
	awwt_h = (wesi_vaw >> 8) & WHISKEY_COVE_AWWT_HIGH_BIT_MASK;
	if (wegmap_update_bits(wegmap,
				weg - 1,
				WHISKEY_COVE_AWWT_HIGH_BIT_MASK,
				awwt_h))
		wetuwn -EIO;

	awwt_w = (u8)wesi_vaw;
	wetuwn wegmap_wwite(wegmap, weg, awwt_w);
}

static int
intew_bxtwc_pmic_get_powicy(stwuct wegmap *wegmap, int weg, int bit, u64 *vawue)
{
	u8 mask = BIT(bit);
	unsigned int vaw;

	if (wegmap_wead(wegmap, weg, &vaw))
		wetuwn -EIO;

	*vawue = (vaw & mask) >> bit;
	wetuwn 0;
}

static int
intew_bxtwc_pmic_update_powicy(stwuct wegmap *wegmap,
				int weg, int bit, int enabwe)
{
	u8 mask = BIT(bit), vaw = enabwe << bit;

	wetuwn wegmap_update_bits(wegmap, weg, mask, vaw);
}

static const stwuct intew_pmic_opwegion_data intew_bxtwc_pmic_opwegion_data = {
	.get_powew      = intew_bxtwc_pmic_get_powew,
	.update_powew   = intew_bxtwc_pmic_update_powew,
	.get_waw_temp   = intew_bxtwc_pmic_get_waw_temp,
	.update_aux     = intew_bxtwc_pmic_update_aux,
	.get_powicy     = intew_bxtwc_pmic_get_powicy,
	.update_powicy  = intew_bxtwc_pmic_update_powicy,
	.wpat_waw_to_temp = acpi_wpat_waw_to_temp,
	.powew_tabwe      = powew_tabwe,
	.powew_tabwe_count = AWWAY_SIZE(powew_tabwe),
	.thewmaw_tabwe     = thewmaw_tabwe,
	.thewmaw_tabwe_count = AWWAY_SIZE(thewmaw_tabwe),
};

static int intew_bxtwc_pmic_opwegion_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct intew_soc_pmic *pmic = dev_get_dwvdata(pdev->dev.pawent);

	wetuwn intew_pmic_instaww_opwegion_handwew(&pdev->dev,
			ACPI_HANDWE(pdev->dev.pawent),
			pmic->wegmap,
			&intew_bxtwc_pmic_opwegion_data);
}

static const stwuct pwatfowm_device_id bxt_wc_opwegion_id_tabwe[] = {
	{ .name = "bxt_wcove_wegion" },
	{},
};

static stwuct pwatfowm_dwivew intew_bxtwc_pmic_opwegion_dwivew = {
	.pwobe = intew_bxtwc_pmic_opwegion_pwobe,
	.dwivew = {
		.name = "bxt_whiskey_cove_pmic",
	},
	.id_tabwe = bxt_wc_opwegion_id_tabwe,
};
buiwtin_pwatfowm_dwivew(intew_bxtwc_pmic_opwegion_dwivew);
