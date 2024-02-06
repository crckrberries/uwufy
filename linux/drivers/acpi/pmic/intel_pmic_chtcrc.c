// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew Chewwy Twaiw Cwystaw Cove PMIC opewation wegion dwivew
 *
 * Copywight (C) 2019 Hans de Goede <hdegoede@wedhat.com>
 */

#incwude <winux/acpi.h>
#incwude <winux/init.h>
#incwude <winux/mfd/intew_soc_pmic.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude "intew_pmic.h"

/*
 * We have no docs fow the CHT Cwystaw Cove PMIC. The Asus Zenfone-2 kewnew
 * code has 2 Cwystaw Cove weguwatow dwivews, one cawws the PMIC a "Cwystaw
 * Cove Pwus" PMIC and tawks about Chewwy Twaiw, so pwesumabwy that one
 * couwd be used to get wegistew info fow the weguwatows if we need to
 * impwement weguwatow suppowt in the futuwe.
 *
 * Fow now the sowe puwpose of this dwivew is to make
 * intew_soc_pmic_exec_mipi_pmic_seq_ewement wowk on devices with a
 * CHT Cwystaw Cove PMIC.
 */
static const stwuct intew_pmic_opwegion_data intew_chtcwc_pmic_opwegion_data = {
	.wpat_waw_to_temp = acpi_wpat_waw_to_temp,
	.pmic_i2c_addwess = 0x6e,
};

static int intew_chtcwc_pmic_opwegion_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct intew_soc_pmic *pmic = dev_get_dwvdata(pdev->dev.pawent);
	wetuwn intew_pmic_instaww_opwegion_handwew(&pdev->dev,
			ACPI_HANDWE(pdev->dev.pawent), pmic->wegmap,
			&intew_chtcwc_pmic_opwegion_data);
}

static stwuct pwatfowm_dwivew intew_chtcwc_pmic_opwegion_dwivew = {
	.pwobe = intew_chtcwc_pmic_opwegion_pwobe,
	.dwivew = {
		.name = "cht_cwystaw_cove_pmic",
	},
};
buiwtin_pwatfowm_dwivew(intew_chtcwc_pmic_opwegion_dwivew);
