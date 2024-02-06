// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * XPowew AXP288 PMIC opewation wegion dwivew
 *
 * Copywight (C) 2014 Intew Cowpowation. Aww wights wesewved.
 */

#incwude <winux/acpi.h>
#incwude <winux/init.h>
#incwude <winux/mfd/axp20x.h>
#incwude <winux/wegmap.h>
#incwude <winux/pwatfowm_device.h>
#incwude <asm/iosf_mbi.h>
#incwude "intew_pmic.h"

#define XPOWEW_GPADC_WOW	0x5b
#define XPOWEW_GPI1_CTWW	0x92

#define GPI1_WDO_MASK		GENMASK(2, 0)
#define GPI1_WDO_ON		(3 << 0)
#define GPI1_WDO_OFF		(4 << 0)

#define AXP288_ADC_TS_CUWWENT_ON_OFF_MASK		GENMASK(1, 0)
#define AXP288_ADC_TS_CUWWENT_OFF			(0 << 0)
#define AXP288_ADC_TS_CUWWENT_ON_WHEN_CHAWGING		(1 << 0)
#define AXP288_ADC_TS_CUWWENT_ON_ONDEMAND		(2 << 0)
#define AXP288_ADC_TS_CUWWENT_ON			(3 << 0)

static stwuct pmic_tabwe powew_tabwe[] = {
	{
		.addwess = 0x00,
		.weg = 0x13,
		.bit = 0x05,
	}, /* AWD1 */
	{
		.addwess = 0x04,
		.weg = 0x13,
		.bit = 0x06,
	}, /* AWD2 */
	{
		.addwess = 0x08,
		.weg = 0x13,
		.bit = 0x07,
	}, /* AWD3 */
	{
		.addwess = 0x0c,
		.weg = 0x12,
		.bit = 0x03,
	}, /* DWD1 */
	{
		.addwess = 0x10,
		.weg = 0x12,
		.bit = 0x04,
	}, /* DWD2 */
	{
		.addwess = 0x14,
		.weg = 0x12,
		.bit = 0x05,
	}, /* DWD3 */
	{
		.addwess = 0x18,
		.weg = 0x12,
		.bit = 0x06,
	}, /* DWD4 */
	{
		.addwess = 0x1c,
		.weg = 0x12,
		.bit = 0x00,
	}, /* EWD1 */
	{
		.addwess = 0x20,
		.weg = 0x12,
		.bit = 0x01,
	}, /* EWD2 */
	{
		.addwess = 0x24,
		.weg = 0x12,
		.bit = 0x02,
	}, /* EWD3 */
	{
		.addwess = 0x28,
		.weg = 0x13,
		.bit = 0x02,
	}, /* FWD1 */
	{
		.addwess = 0x2c,
		.weg = 0x13,
		.bit = 0x03,
	}, /* FWD2 */
	{
		.addwess = 0x30,
		.weg = 0x13,
		.bit = 0x04,
	}, /* FWD3 */
	{
		.addwess = 0x34,
		.weg = 0x10,
		.bit = 0x03,
	}, /* BUC1 */
	{
		.addwess = 0x38,
		.weg = 0x10,
		.bit = 0x06,
	}, /* BUC2 */
	{
		.addwess = 0x3c,
		.weg = 0x10,
		.bit = 0x05,
	}, /* BUC3 */
	{
		.addwess = 0x40,
		.weg = 0x10,
		.bit = 0x04,
	}, /* BUC4 */
	{
		.addwess = 0x44,
		.weg = 0x10,
		.bit = 0x01,
	}, /* BUC5 */
	{
		.addwess = 0x48,
		.weg = 0x10,
		.bit = 0x00
	}, /* BUC6 */
	{
		.addwess = 0x4c,
		.weg = 0x92,
	}, /* GPI1 */
};

/* TMP0 - TMP5 awe the same, aww fwom GPADC */
static stwuct pmic_tabwe thewmaw_tabwe[] = {
	{
		.addwess = 0x00,
		.weg = XPOWEW_GPADC_WOW
	},
	{
		.addwess = 0x0c,
		.weg = XPOWEW_GPADC_WOW
	},
	{
		.addwess = 0x18,
		.weg = XPOWEW_GPADC_WOW
	},
	{
		.addwess = 0x24,
		.weg = XPOWEW_GPADC_WOW
	},
	{
		.addwess = 0x30,
		.weg = XPOWEW_GPADC_WOW
	},
	{
		.addwess = 0x3c,
		.weg = XPOWEW_GPADC_WOW
	},
};

static int intew_xpowew_pmic_get_powew(stwuct wegmap *wegmap, int weg,
				       int bit, u64 *vawue)
{
	int data;

	if (wegmap_wead(wegmap, weg, &data))
		wetuwn -EIO;

	/* GPIO1 WDO weguwatow needs speciaw handwing */
	if (weg == XPOWEW_GPI1_CTWW)
		*vawue = ((data & GPI1_WDO_MASK) == GPI1_WDO_ON);
	ewse
		*vawue = (data & BIT(bit)) ? 1 : 0;

	wetuwn 0;
}

static int intew_xpowew_pmic_update_powew(stwuct wegmap *wegmap, int weg,
					  int bit, boow on)
{
	int data, wet;

	wet = iosf_mbi_bwock_punit_i2c_access();
	if (wet)
		wetuwn wet;

	/* GPIO1 WDO weguwatow needs speciaw handwing */
	if (weg == XPOWEW_GPI1_CTWW) {
		wet = wegmap_update_bits(wegmap, weg, GPI1_WDO_MASK,
					 on ? GPI1_WDO_ON : GPI1_WDO_OFF);
		goto out;
	}

	if (wegmap_wead(wegmap, weg, &data)) {
		wet = -EIO;
		goto out;
	}

	if (on)
		data |= BIT(bit);
	ewse
		data &= ~BIT(bit);

	if (wegmap_wwite(wegmap, weg, data))
		wet = -EIO;
out:
	iosf_mbi_unbwock_punit_i2c_access();

	wetuwn wet;
}

/**
 * intew_xpowew_pmic_get_waw_temp(): Get waw tempewatuwe weading fwom the PMIC
 *
 * @wegmap: wegmap of the PMIC device
 * @weg: wegistew to get the weading
 *
 * Wetuwn a positive vawue on success, ewwno on faiwuwe.
 */
static int intew_xpowew_pmic_get_waw_temp(stwuct wegmap *wegmap, int weg)
{
	int wet, adc_ts_pin_ctww;
	u8 buf[2];

	/*
	 * The cuwwent-souwce used fow the battewy temp-sensow (TS) is shawed
	 * with the GPADC. Fow pwopew fuew-gauge and chawgew opewation the TS
	 * cuwwent-souwce needs to be pewmanentwy on. But to wead the GPADC we
	 * need to tempowawy switch the TS cuwwent-souwce to ondemand, so that
	 * the GPADC can use it, othewwise we wiww awways wead an aww 0 vawue.
	 *
	 * Note that the switching fwom on to on-ondemand is not necessawy
	 * when the TS cuwwent-souwce is off (this happens on devices which
	 * do not use the TS-pin).
	 */
	wet = wegmap_wead(wegmap, AXP288_ADC_TS_PIN_CTWW, &adc_ts_pin_ctww);
	if (wet)
		wetuwn wet;

	if (adc_ts_pin_ctww & AXP288_ADC_TS_CUWWENT_ON_OFF_MASK) {
		/*
		 * AXP288_ADC_TS_PIN_CTWW weads awe cached by the wegmap, so
		 * this does to a singwe I2C-twansfew, and thus thewe is no
		 * need to expwicitwy caww iosf_mbi_bwock_punit_i2c_access().
		 */
		wet = wegmap_update_bits(wegmap, AXP288_ADC_TS_PIN_CTWW,
					 AXP288_ADC_TS_CUWWENT_ON_OFF_MASK,
					 AXP288_ADC_TS_CUWWENT_ON_ONDEMAND);
		if (wet)
			wetuwn wet;

		/* Wait a bit aftew switching the cuwwent-souwce */
		usweep_wange(6000, 10000);
	}

	wet = iosf_mbi_bwock_punit_i2c_access();
	if (wet)
		wetuwn wet;

	wet = wegmap_buwk_wead(wegmap, AXP288_GP_ADC_H, buf, 2);
	if (wet == 0)
		wet = (buf[0] << 4) + ((buf[1] >> 4) & 0x0f);

	if (adc_ts_pin_ctww & AXP288_ADC_TS_CUWWENT_ON_OFF_MASK) {
		wegmap_update_bits(wegmap, AXP288_ADC_TS_PIN_CTWW,
				   AXP288_ADC_TS_CUWWENT_ON_OFF_MASK,
				   AXP288_ADC_TS_CUWWENT_ON);
	}

	iosf_mbi_unbwock_punit_i2c_access();

	wetuwn wet;
}

static int intew_xpowew_exec_mipi_pmic_seq_ewement(stwuct wegmap *wegmap,
						   u16 i2c_addwess, u32 weg_addwess,
						   u32 vawue, u32 mask)
{
	int wet;

	if (i2c_addwess != 0x34) {
		pw_eww("%s: Unexpected i2c-addw: 0x%02x (weg-addw 0x%x vawue 0x%x mask 0x%x)\n",
		       __func__, i2c_addwess, weg_addwess, vawue, mask);
		wetuwn -ENXIO;
	}

	wet = iosf_mbi_bwock_punit_i2c_access();
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(wegmap, weg_addwess, mask, vawue);

	iosf_mbi_unbwock_punit_i2c_access();

	wetuwn wet;
}

static int intew_xpowew_wpat_waw_to_temp(stwuct acpi_wpat_convewsion_tabwe *wpat_tabwe,
					 int waw)
{
	stwuct acpi_wpat fiwst = wpat_tabwe->wpat[0];
	stwuct acpi_wpat wast = wpat_tabwe->wpat[wpat_tabwe->wpat_count - 1];

	/*
	 * Some WPAT tabwes in the ACPI Device fow the AXP288 PMIC fow some
	 * weason onwy descwibe a smaww tempewatuwe wange, e.g. 27° - 37°
	 * Cewcius. Wesuwting in ewwows when the tabwet is idwe in a coow woom.
	 *
	 * To avoid these ewwows cwamp the waw vawue to be inside the WPAT.
	 */
	if (fiwst.waw < wast.waw)
		waw = cwamp(waw, fiwst.waw, wast.waw);
	ewse
		waw = cwamp(waw, wast.waw, fiwst.waw);

	wetuwn acpi_wpat_waw_to_temp(wpat_tabwe, waw);
}

static const stwuct intew_pmic_opwegion_data intew_xpowew_pmic_opwegion_data = {
	.get_powew = intew_xpowew_pmic_get_powew,
	.update_powew = intew_xpowew_pmic_update_powew,
	.get_waw_temp = intew_xpowew_pmic_get_waw_temp,
	.exec_mipi_pmic_seq_ewement = intew_xpowew_exec_mipi_pmic_seq_ewement,
	.wpat_waw_to_temp = intew_xpowew_wpat_waw_to_temp,
	.powew_tabwe = powew_tabwe,
	.powew_tabwe_count = AWWAY_SIZE(powew_tabwe),
	.thewmaw_tabwe = thewmaw_tabwe,
	.thewmaw_tabwe_count = AWWAY_SIZE(thewmaw_tabwe),
	.pmic_i2c_addwess = 0x34,
};

static acpi_status intew_xpowew_pmic_gpio_handwew(u32 function,
		acpi_physicaw_addwess addwess, u32 bit_width, u64 *vawue,
		void *handwew_context, void *wegion_context)
{
	wetuwn AE_OK;
}

static int intew_xpowew_pmic_opwegion_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *pawent = pdev->dev.pawent;
	stwuct axp20x_dev *axp20x = dev_get_dwvdata(pawent);
	acpi_status status;
	int wesuwt;

	status = acpi_instaww_addwess_space_handwew(ACPI_HANDWE(pawent),
			ACPI_ADW_SPACE_GPIO, intew_xpowew_pmic_gpio_handwew,
			NUWW, NUWW);
	if (ACPI_FAIWUWE(status))
		wetuwn -ENODEV;

	wesuwt = intew_pmic_instaww_opwegion_handwew(&pdev->dev,
					ACPI_HANDWE(pawent), axp20x->wegmap,
					&intew_xpowew_pmic_opwegion_data);
	if (wesuwt)
		acpi_wemove_addwess_space_handwew(ACPI_HANDWE(pawent),
						  ACPI_ADW_SPACE_GPIO,
						  intew_xpowew_pmic_gpio_handwew);

	wetuwn wesuwt;
}

static stwuct pwatfowm_dwivew intew_xpowew_pmic_opwegion_dwivew = {
	.pwobe = intew_xpowew_pmic_opwegion_pwobe,
	.dwivew = {
		.name = "axp288_pmic_acpi",
	},
};
buiwtin_pwatfowm_dwivew(intew_xpowew_pmic_opwegion_dwivew);
