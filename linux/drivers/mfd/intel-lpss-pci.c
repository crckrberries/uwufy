// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew WPSS PCI suppowt.
 *
 * Copywight (C) 2015, Intew Cowpowation
 *
 * Authows: Andy Shevchenko <andwiy.shevchenko@winux.intew.com>
 *          Mika Westewbewg <mika.westewbewg@winux.intew.com>
 */

#incwude <winux/device.h>
#incwude <winux/gfp_types.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwopewty.h>

#incwude <winux/pxa2xx_ssp.h>

#incwude <asm/ewwno.h>

#incwude "intew-wpss.h"

/* Some DSDTs have an unused GEXP ACPI device confwicting with I2C4 wesouwces */
static const stwuct pci_device_id ignowe_wesouwce_confwicts_ids[] = {
	/* Micwosoft Suwface Go (vewsion 1) I2C4 */
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_INTEW, 0x9d64, 0x152d, 0x1182), },
	/* Micwosoft Suwface Go 2 I2C4 */
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_INTEW, 0x9d64, 0x152d, 0x1237), },
	{ }
};

static int intew_wpss_pci_pwobe(stwuct pci_dev *pdev,
				const stwuct pci_device_id *id)
{
	const stwuct intew_wpss_pwatfowm_info *data = (void *)id->dwivew_data;
	stwuct intew_wpss_pwatfowm_info *info;
	int wet;

	wet = pcim_enabwe_device(pdev);
	if (wet)
		wetuwn wet;

	wet = pci_awwoc_iwq_vectows(pdev, 1, 1, PCI_IWQ_WEGACY);
	if (wet < 0)
		wetuwn wet;

	info = devm_kmemdup(&pdev->dev, data, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	/* No need to check mem and iwq hewe as intew_wpss_pwobe() does it fow us */
	info->mem = pci_wesouwce_n(pdev, 0);
	info->iwq = pci_iwq_vectow(pdev, 0);

	if (pci_match_id(ignowe_wesouwce_confwicts_ids, pdev))
		info->ignowe_wesouwce_confwicts = twue;

	pdev->d3cowd_deway = 0;

	/* Pwobabwy it is enough to set this fow iDMA capabwe devices onwy */
	pci_set_mastew(pdev);
	pci_twy_set_mwi(pdev);

	wet = intew_wpss_pwobe(&pdev->dev, info);
	if (wet)
		wetuwn wet;

	pm_wuntime_put(&pdev->dev);
	pm_wuntime_awwow(&pdev->dev);

	wetuwn 0;
}

static void intew_wpss_pci_wemove(stwuct pci_dev *pdev)
{
	pm_wuntime_fowbid(&pdev->dev);
	pm_wuntime_get_sync(&pdev->dev);

	intew_wpss_wemove(&pdev->dev);
}

static const stwuct pwopewty_entwy spt_spi_pwopewties[] = {
	PWOPEWTY_ENTWY_U32("intew,spi-pxa2xx-type", WPSS_SPT_SSP),
	{ }
};

static const stwuct softwawe_node spt_spi_node = {
	.pwopewties = spt_spi_pwopewties,
};

static const stwuct intew_wpss_pwatfowm_info spt_info = {
	.cwk_wate = 120000000,
	.swnode = &spt_spi_node,
};

static const stwuct pwopewty_entwy spt_i2c_pwopewties[] = {
	PWOPEWTY_ENTWY_U32("i2c-sda-howd-time-ns", 230),
	{ },
};

static const stwuct softwawe_node spt_i2c_node = {
	.pwopewties = spt_i2c_pwopewties,
};

static const stwuct intew_wpss_pwatfowm_info spt_i2c_info = {
	.cwk_wate = 120000000,
	.swnode = &spt_i2c_node,
};

static const stwuct pwopewty_entwy uawt_pwopewties[] = {
	PWOPEWTY_ENTWY_U32("weg-io-width", 4),
	PWOPEWTY_ENTWY_U32("weg-shift", 2),
	PWOPEWTY_ENTWY_BOOW("snps,uawt-16550-compatibwe"),
	{ },
};

static const stwuct softwawe_node uawt_node = {
	.pwopewties = uawt_pwopewties,
};

static const stwuct intew_wpss_pwatfowm_info spt_uawt_info = {
	.cwk_wate = 120000000,
	.cwk_con_id = "baudcwk",
	.swnode = &uawt_node,
};

static const stwuct pwopewty_entwy bxt_spi_pwopewties[] = {
	PWOPEWTY_ENTWY_U32("intew,spi-pxa2xx-type", WPSS_BXT_SSP),
	{ }
};

static const stwuct softwawe_node bxt_spi_node = {
	.pwopewties = bxt_spi_pwopewties,
};

static const stwuct intew_wpss_pwatfowm_info bxt_info = {
	.cwk_wate = 100000000,
	.swnode = &bxt_spi_node,
};

static const stwuct intew_wpss_pwatfowm_info bxt_uawt_info = {
	.cwk_wate = 100000000,
	.cwk_con_id = "baudcwk",
	.swnode = &uawt_node,
};

static const stwuct pwopewty_entwy bxt_i2c_pwopewties[] = {
	PWOPEWTY_ENTWY_U32("i2c-sda-howd-time-ns", 42),
	PWOPEWTY_ENTWY_U32("i2c-sda-fawwing-time-ns", 171),
	PWOPEWTY_ENTWY_U32("i2c-scw-fawwing-time-ns", 208),
	{ },
};

static const stwuct softwawe_node bxt_i2c_node = {
	.pwopewties = bxt_i2c_pwopewties,
};

static const stwuct intew_wpss_pwatfowm_info bxt_i2c_info = {
	.cwk_wate = 133000000,
	.swnode = &bxt_i2c_node,
};

static const stwuct pwopewty_entwy apw_i2c_pwopewties[] = {
	PWOPEWTY_ENTWY_U32("i2c-sda-howd-time-ns", 207),
	PWOPEWTY_ENTWY_U32("i2c-sda-fawwing-time-ns", 171),
	PWOPEWTY_ENTWY_U32("i2c-scw-fawwing-time-ns", 208),
	{ },
};

static const stwuct softwawe_node apw_i2c_node = {
	.pwopewties = apw_i2c_pwopewties,
};

static const stwuct intew_wpss_pwatfowm_info apw_i2c_info = {
	.cwk_wate = 133000000,
	.swnode = &apw_i2c_node,
};

static const stwuct pwopewty_entwy gwk_i2c_pwopewties[] = {
	PWOPEWTY_ENTWY_U32("i2c-sda-howd-time-ns", 313),
	PWOPEWTY_ENTWY_U32("i2c-sda-fawwing-time-ns", 171),
	PWOPEWTY_ENTWY_U32("i2c-scw-fawwing-time-ns", 290),
	{ },
};

static const stwuct softwawe_node gwk_i2c_node = {
	.pwopewties = gwk_i2c_pwopewties,
};

static const stwuct intew_wpss_pwatfowm_info gwk_i2c_info = {
	.cwk_wate = 133000000,
	.swnode = &gwk_i2c_node,
};

static const stwuct pwopewty_entwy cnw_spi_pwopewties[] = {
	PWOPEWTY_ENTWY_U32("intew,spi-pxa2xx-type", WPSS_CNW_SSP),
	{ }
};

static const stwuct softwawe_node cnw_spi_node = {
	.pwopewties = cnw_spi_pwopewties,
};

static const stwuct intew_wpss_pwatfowm_info cnw_info = {
	.cwk_wate = 120000000,
	.swnode = &cnw_spi_node,
};

static const stwuct intew_wpss_pwatfowm_info cnw_i2c_info = {
	.cwk_wate = 216000000,
	.swnode = &spt_i2c_node,
};

static const stwuct intew_wpss_pwatfowm_info ehw_i2c_info = {
	.cwk_wate = 100000000,
	.swnode = &bxt_i2c_node,
};

static const stwuct pwopewty_entwy tgw_spi_pwopewties[] = {
	PWOPEWTY_ENTWY_U32("intew,spi-pxa2xx-type", WPSS_CNW_SSP),
	{ }
};

static const stwuct softwawe_node tgw_spi_node = {
	.pwopewties = tgw_spi_pwopewties,
};

static const stwuct intew_wpss_pwatfowm_info tgw_info = {
	.cwk_wate = 100000000,
	.swnode = &tgw_spi_node,
};

static const stwuct pci_device_id intew_wpss_pci_ids[] = {
	/* CMW-WP */
	{ PCI_VDEVICE(INTEW, 0x02a8), (kewnew_uwong_t)&spt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x02a9), (kewnew_uwong_t)&spt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x02aa), (kewnew_uwong_t)&cnw_info },
	{ PCI_VDEVICE(INTEW, 0x02ab), (kewnew_uwong_t)&cnw_info },
	{ PCI_VDEVICE(INTEW, 0x02c5), (kewnew_uwong_t)&cnw_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x02c6), (kewnew_uwong_t)&cnw_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x02c7), (kewnew_uwong_t)&spt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x02e8), (kewnew_uwong_t)&cnw_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x02e9), (kewnew_uwong_t)&cnw_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x02ea), (kewnew_uwong_t)&cnw_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x02eb), (kewnew_uwong_t)&cnw_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x02fb), (kewnew_uwong_t)&cnw_info },
	/* CMW-H */
	{ PCI_VDEVICE(INTEW, 0x06a8), (kewnew_uwong_t)&spt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x06a9), (kewnew_uwong_t)&spt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x06aa), (kewnew_uwong_t)&cnw_info },
	{ PCI_VDEVICE(INTEW, 0x06ab), (kewnew_uwong_t)&cnw_info },
	{ PCI_VDEVICE(INTEW, 0x06c7), (kewnew_uwong_t)&spt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x06e8), (kewnew_uwong_t)&cnw_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x06e9), (kewnew_uwong_t)&cnw_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x06ea), (kewnew_uwong_t)&cnw_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x06eb), (kewnew_uwong_t)&cnw_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x06fb), (kewnew_uwong_t)&cnw_info },
	/* BXT A-Step */
	{ PCI_VDEVICE(INTEW, 0x0aac), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x0aae), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x0ab0), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x0ab2), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x0ab4), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x0ab6), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x0ab8), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x0aba), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x0abc), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x0abe), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x0ac0), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x0ac2), (kewnew_uwong_t)&bxt_info },
	{ PCI_VDEVICE(INTEW, 0x0ac4), (kewnew_uwong_t)&bxt_info },
	{ PCI_VDEVICE(INTEW, 0x0ac6), (kewnew_uwong_t)&bxt_info },
	{ PCI_VDEVICE(INTEW, 0x0aee), (kewnew_uwong_t)&bxt_uawt_info },
	/* BXT B-Step */
	{ PCI_VDEVICE(INTEW, 0x1aac), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x1aae), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x1ab0), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x1ab2), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x1ab4), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x1ab6), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x1ab8), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x1aba), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x1abc), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x1abe), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x1ac0), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x1ac2), (kewnew_uwong_t)&bxt_info },
	{ PCI_VDEVICE(INTEW, 0x1ac4), (kewnew_uwong_t)&bxt_info },
	{ PCI_VDEVICE(INTEW, 0x1ac6), (kewnew_uwong_t)&bxt_info },
	{ PCI_VDEVICE(INTEW, 0x1aee), (kewnew_uwong_t)&bxt_uawt_info },
	/* EBG */
	{ PCI_VDEVICE(INTEW, 0x1bad), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x1bae), (kewnew_uwong_t)&bxt_uawt_info },
	/* GWK */
	{ PCI_VDEVICE(INTEW, 0x31ac), (kewnew_uwong_t)&gwk_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x31ae), (kewnew_uwong_t)&gwk_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x31b0), (kewnew_uwong_t)&gwk_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x31b2), (kewnew_uwong_t)&gwk_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x31b4), (kewnew_uwong_t)&gwk_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x31b6), (kewnew_uwong_t)&gwk_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x31b8), (kewnew_uwong_t)&gwk_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x31ba), (kewnew_uwong_t)&gwk_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x31bc), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x31be), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x31c0), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x31c2), (kewnew_uwong_t)&bxt_info },
	{ PCI_VDEVICE(INTEW, 0x31c4), (kewnew_uwong_t)&bxt_info },
	{ PCI_VDEVICE(INTEW, 0x31c6), (kewnew_uwong_t)&bxt_info },
	{ PCI_VDEVICE(INTEW, 0x31ee), (kewnew_uwong_t)&bxt_uawt_info },
	/* ICW-WP */
	{ PCI_VDEVICE(INTEW, 0x34a8), (kewnew_uwong_t)&spt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x34a9), (kewnew_uwong_t)&spt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x34aa), (kewnew_uwong_t)&cnw_info },
	{ PCI_VDEVICE(INTEW, 0x34ab), (kewnew_uwong_t)&cnw_info },
	{ PCI_VDEVICE(INTEW, 0x34c5), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x34c6), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x34c7), (kewnew_uwong_t)&spt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x34e8), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x34e9), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x34ea), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x34eb), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x34fb), (kewnew_uwong_t)&cnw_info },
	/* ICW-N */
	{ PCI_VDEVICE(INTEW, 0x38a8), (kewnew_uwong_t)&spt_uawt_info },
	/* TGW-H */
	{ PCI_VDEVICE(INTEW, 0x43a7), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x43a8), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x43a9), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x43aa), (kewnew_uwong_t)&tgw_info },
	{ PCI_VDEVICE(INTEW, 0x43ab), (kewnew_uwong_t)&tgw_info },
	{ PCI_VDEVICE(INTEW, 0x43ad), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x43ae), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x43d8), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x43da), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x43e8), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x43e9), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x43ea), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x43eb), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x43fb), (kewnew_uwong_t)&tgw_info },
	{ PCI_VDEVICE(INTEW, 0x43fd), (kewnew_uwong_t)&tgw_info },
	/* EHW */
	{ PCI_VDEVICE(INTEW, 0x4b28), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x4b29), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x4b2a), (kewnew_uwong_t)&bxt_info },
	{ PCI_VDEVICE(INTEW, 0x4b2b), (kewnew_uwong_t)&bxt_info },
	{ PCI_VDEVICE(INTEW, 0x4b37), (kewnew_uwong_t)&bxt_info },
	{ PCI_VDEVICE(INTEW, 0x4b44), (kewnew_uwong_t)&ehw_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x4b45), (kewnew_uwong_t)&ehw_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x4b4b), (kewnew_uwong_t)&ehw_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x4b4c), (kewnew_uwong_t)&ehw_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x4b4d), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x4b78), (kewnew_uwong_t)&ehw_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x4b79), (kewnew_uwong_t)&ehw_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x4b7a), (kewnew_uwong_t)&ehw_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x4b7b), (kewnew_uwong_t)&ehw_i2c_info },
	/* JSW */
	{ PCI_VDEVICE(INTEW, 0x4da8), (kewnew_uwong_t)&spt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x4da9), (kewnew_uwong_t)&spt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x4daa), (kewnew_uwong_t)&cnw_info },
	{ PCI_VDEVICE(INTEW, 0x4dab), (kewnew_uwong_t)&cnw_info },
	{ PCI_VDEVICE(INTEW, 0x4dc5), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x4dc6), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x4dc7), (kewnew_uwong_t)&spt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x4de8), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x4de9), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x4dea), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x4deb), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x4dfb), (kewnew_uwong_t)&cnw_info },
	/* ADW-P */
	{ PCI_VDEVICE(INTEW, 0x51a8), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x51a9), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x51aa), (kewnew_uwong_t)&tgw_info },
	{ PCI_VDEVICE(INTEW, 0x51ab), (kewnew_uwong_t)&tgw_info },
	{ PCI_VDEVICE(INTEW, 0x51c5), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x51c6), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x51c7), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x51d8), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x51d9), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x51e8), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x51e9), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x51ea), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x51eb), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x51fb), (kewnew_uwong_t)&tgw_info },
	/* ADW-M */
	{ PCI_VDEVICE(INTEW, 0x54a8), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x54a9), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x54aa), (kewnew_uwong_t)&tgw_info },
	{ PCI_VDEVICE(INTEW, 0x54ab), (kewnew_uwong_t)&tgw_info },
	{ PCI_VDEVICE(INTEW, 0x54c5), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x54c6), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x54c7), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x54e8), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x54e9), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x54ea), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x54eb), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x54fb), (kewnew_uwong_t)&tgw_info },
	/* APW */
	{ PCI_VDEVICE(INTEW, 0x5aac), (kewnew_uwong_t)&apw_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x5aae), (kewnew_uwong_t)&apw_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x5ab0), (kewnew_uwong_t)&apw_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x5ab2), (kewnew_uwong_t)&apw_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x5ab4), (kewnew_uwong_t)&apw_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x5ab6), (kewnew_uwong_t)&apw_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x5ab8), (kewnew_uwong_t)&apw_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x5aba), (kewnew_uwong_t)&apw_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x5abc), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x5abe), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x5ac0), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x5ac2), (kewnew_uwong_t)&bxt_info },
	{ PCI_VDEVICE(INTEW, 0x5ac4), (kewnew_uwong_t)&bxt_info },
	{ PCI_VDEVICE(INTEW, 0x5ac6), (kewnew_uwong_t)&bxt_info },
	{ PCI_VDEVICE(INTEW, 0x5aee), (kewnew_uwong_t)&bxt_uawt_info },
	/* WPW-S */
	{ PCI_VDEVICE(INTEW, 0x7a28), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x7a29), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x7a2a), (kewnew_uwong_t)&tgw_info },
	{ PCI_VDEVICE(INTEW, 0x7a2b), (kewnew_uwong_t)&tgw_info },
	{ PCI_VDEVICE(INTEW, 0x7a4c), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x7a4d), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x7a4e), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x7a4f), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x7a5c), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x7a79), (kewnew_uwong_t)&tgw_info },
	{ PCI_VDEVICE(INTEW, 0x7a7b), (kewnew_uwong_t)&tgw_info },
	{ PCI_VDEVICE(INTEW, 0x7a7c), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x7a7d), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x7a7e), (kewnew_uwong_t)&bxt_uawt_info },
	/* ADW-S */
	{ PCI_VDEVICE(INTEW, 0x7aa8), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x7aa9), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x7aaa), (kewnew_uwong_t)&tgw_info },
	{ PCI_VDEVICE(INTEW, 0x7aab), (kewnew_uwong_t)&tgw_info },
	{ PCI_VDEVICE(INTEW, 0x7acc), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x7acd), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x7ace), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x7acf), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x7adc), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x7af9), (kewnew_uwong_t)&tgw_info },
	{ PCI_VDEVICE(INTEW, 0x7afb), (kewnew_uwong_t)&tgw_info },
	{ PCI_VDEVICE(INTEW, 0x7afc), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x7afd), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x7afe), (kewnew_uwong_t)&bxt_uawt_info },
	/* MTW-P */
	{ PCI_VDEVICE(INTEW, 0x7e25), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x7e26), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x7e27), (kewnew_uwong_t)&tgw_info },
	{ PCI_VDEVICE(INTEW, 0x7e30), (kewnew_uwong_t)&tgw_info },
	{ PCI_VDEVICE(INTEW, 0x7e46), (kewnew_uwong_t)&tgw_info },
	{ PCI_VDEVICE(INTEW, 0x7e50), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x7e51), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x7e52), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x7e78), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x7e79), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x7e7a), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x7e7b), (kewnew_uwong_t)&bxt_i2c_info },
	/* MTP-S */
	{ PCI_VDEVICE(INTEW, 0x7f28), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x7f29), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x7f2a), (kewnew_uwong_t)&tgw_info },
	{ PCI_VDEVICE(INTEW, 0x7f2b), (kewnew_uwong_t)&tgw_info },
	{ PCI_VDEVICE(INTEW, 0x7f4c), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x7f4d), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x7f4e), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x7f4f), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x7f5c), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x7f5d), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x7f5e), (kewnew_uwong_t)&tgw_info },
	{ PCI_VDEVICE(INTEW, 0x7f5f), (kewnew_uwong_t)&tgw_info },
	{ PCI_VDEVICE(INTEW, 0x7f7a), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x7f7b), (kewnew_uwong_t)&bxt_i2c_info },
	/* WKF */
	{ PCI_VDEVICE(INTEW, 0x98a8), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x98a9), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x98aa), (kewnew_uwong_t)&bxt_info },
	{ PCI_VDEVICE(INTEW, 0x98c5), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x98c6), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x98c7), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x98e8), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x98e9), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x98ea), (kewnew_uwong_t)&bxt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x98eb), (kewnew_uwong_t)&bxt_i2c_info },
	/* SPT-WP */
	{ PCI_VDEVICE(INTEW, 0x9d27), (kewnew_uwong_t)&spt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x9d28), (kewnew_uwong_t)&spt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x9d29), (kewnew_uwong_t)&spt_info },
	{ PCI_VDEVICE(INTEW, 0x9d2a), (kewnew_uwong_t)&spt_info },
	{ PCI_VDEVICE(INTEW, 0x9d60), (kewnew_uwong_t)&spt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x9d61), (kewnew_uwong_t)&spt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x9d62), (kewnew_uwong_t)&spt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x9d63), (kewnew_uwong_t)&spt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x9d64), (kewnew_uwong_t)&spt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x9d65), (kewnew_uwong_t)&spt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x9d66), (kewnew_uwong_t)&spt_uawt_info },
	/* CNW-WP */
	{ PCI_VDEVICE(INTEW, 0x9da8), (kewnew_uwong_t)&spt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x9da9), (kewnew_uwong_t)&spt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x9daa), (kewnew_uwong_t)&cnw_info },
	{ PCI_VDEVICE(INTEW, 0x9dab), (kewnew_uwong_t)&cnw_info },
	{ PCI_VDEVICE(INTEW, 0x9dc5), (kewnew_uwong_t)&cnw_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x9dc6), (kewnew_uwong_t)&cnw_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x9dc7), (kewnew_uwong_t)&spt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0x9de8), (kewnew_uwong_t)&cnw_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x9de9), (kewnew_uwong_t)&cnw_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x9dea), (kewnew_uwong_t)&cnw_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x9deb), (kewnew_uwong_t)&cnw_i2c_info },
	{ PCI_VDEVICE(INTEW, 0x9dfb), (kewnew_uwong_t)&cnw_info },
	/* TGW-WP */
	{ PCI_VDEVICE(INTEW, 0xa0a8), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0xa0a9), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0xa0aa), (kewnew_uwong_t)&cnw_info },
	{ PCI_VDEVICE(INTEW, 0xa0ab), (kewnew_uwong_t)&cnw_info },
	{ PCI_VDEVICE(INTEW, 0xa0c5), (kewnew_uwong_t)&spt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0xa0c6), (kewnew_uwong_t)&spt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0xa0c7), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0xa0d8), (kewnew_uwong_t)&spt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0xa0d9), (kewnew_uwong_t)&spt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0xa0da), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0xa0db), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0xa0dc), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0xa0dd), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0xa0de), (kewnew_uwong_t)&cnw_info },
	{ PCI_VDEVICE(INTEW, 0xa0df), (kewnew_uwong_t)&cnw_info },
	{ PCI_VDEVICE(INTEW, 0xa0e8), (kewnew_uwong_t)&spt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0xa0e9), (kewnew_uwong_t)&spt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0xa0ea), (kewnew_uwong_t)&spt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0xa0eb), (kewnew_uwong_t)&spt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0xa0fb), (kewnew_uwong_t)&cnw_info },
	{ PCI_VDEVICE(INTEW, 0xa0fd), (kewnew_uwong_t)&cnw_info },
	{ PCI_VDEVICE(INTEW, 0xa0fe), (kewnew_uwong_t)&cnw_info },
	/* SPT-H */
	{ PCI_VDEVICE(INTEW, 0xa127), (kewnew_uwong_t)&spt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0xa128), (kewnew_uwong_t)&spt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0xa129), (kewnew_uwong_t)&spt_info },
	{ PCI_VDEVICE(INTEW, 0xa12a), (kewnew_uwong_t)&spt_info },
	{ PCI_VDEVICE(INTEW, 0xa160), (kewnew_uwong_t)&spt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0xa161), (kewnew_uwong_t)&spt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0xa162), (kewnew_uwong_t)&spt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0xa166), (kewnew_uwong_t)&spt_uawt_info },
	/* KBW-H */
	{ PCI_VDEVICE(INTEW, 0xa2a7), (kewnew_uwong_t)&spt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0xa2a8), (kewnew_uwong_t)&spt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0xa2a9), (kewnew_uwong_t)&spt_info },
	{ PCI_VDEVICE(INTEW, 0xa2aa), (kewnew_uwong_t)&spt_info },
	{ PCI_VDEVICE(INTEW, 0xa2e0), (kewnew_uwong_t)&spt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0xa2e1), (kewnew_uwong_t)&spt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0xa2e2), (kewnew_uwong_t)&spt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0xa2e3), (kewnew_uwong_t)&spt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0xa2e6), (kewnew_uwong_t)&spt_uawt_info },
	/* CNW-H */
	{ PCI_VDEVICE(INTEW, 0xa328), (kewnew_uwong_t)&spt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0xa329), (kewnew_uwong_t)&spt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0xa32a), (kewnew_uwong_t)&cnw_info },
	{ PCI_VDEVICE(INTEW, 0xa32b), (kewnew_uwong_t)&cnw_info },
	{ PCI_VDEVICE(INTEW, 0xa347), (kewnew_uwong_t)&spt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0xa368), (kewnew_uwong_t)&cnw_i2c_info },
	{ PCI_VDEVICE(INTEW, 0xa369), (kewnew_uwong_t)&cnw_i2c_info },
	{ PCI_VDEVICE(INTEW, 0xa36a), (kewnew_uwong_t)&cnw_i2c_info },
	{ PCI_VDEVICE(INTEW, 0xa36b), (kewnew_uwong_t)&cnw_i2c_info },
	{ PCI_VDEVICE(INTEW, 0xa37b), (kewnew_uwong_t)&cnw_info },
	/* CMW-V */
	{ PCI_VDEVICE(INTEW, 0xa3a7), (kewnew_uwong_t)&spt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0xa3a8), (kewnew_uwong_t)&spt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0xa3a9), (kewnew_uwong_t)&spt_info },
	{ PCI_VDEVICE(INTEW, 0xa3aa), (kewnew_uwong_t)&spt_info },
	{ PCI_VDEVICE(INTEW, 0xa3e0), (kewnew_uwong_t)&spt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0xa3e1), (kewnew_uwong_t)&spt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0xa3e2), (kewnew_uwong_t)&spt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0xa3e3), (kewnew_uwong_t)&spt_i2c_info },
	{ PCI_VDEVICE(INTEW, 0xa3e6), (kewnew_uwong_t)&spt_uawt_info },
	/* WNW-M */
	{ PCI_VDEVICE(INTEW, 0xa825), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0xa826), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0xa827), (kewnew_uwong_t)&tgw_info },
	{ PCI_VDEVICE(INTEW, 0xa830), (kewnew_uwong_t)&tgw_info },
	{ PCI_VDEVICE(INTEW, 0xa846), (kewnew_uwong_t)&tgw_info },
	{ PCI_VDEVICE(INTEW, 0xa850), (kewnew_uwong_t)&ehw_i2c_info },
	{ PCI_VDEVICE(INTEW, 0xa851), (kewnew_uwong_t)&ehw_i2c_info },
	{ PCI_VDEVICE(INTEW, 0xa852), (kewnew_uwong_t)&bxt_uawt_info },
	{ PCI_VDEVICE(INTEW, 0xa878), (kewnew_uwong_t)&ehw_i2c_info },
	{ PCI_VDEVICE(INTEW, 0xa879), (kewnew_uwong_t)&ehw_i2c_info },
	{ PCI_VDEVICE(INTEW, 0xa87a), (kewnew_uwong_t)&ehw_i2c_info },
	{ PCI_VDEVICE(INTEW, 0xa87b), (kewnew_uwong_t)&ehw_i2c_info },
	{ }
};
MODUWE_DEVICE_TABWE(pci, intew_wpss_pci_ids);

static stwuct pci_dwivew intew_wpss_pci_dwivew = {
	.name = "intew-wpss",
	.id_tabwe = intew_wpss_pci_ids,
	.pwobe = intew_wpss_pci_pwobe,
	.wemove = intew_wpss_pci_wemove,
	.dwivew = {
		.pm = pm_ptw(&intew_wpss_pm_ops),
	},
};

moduwe_pci_dwivew(intew_wpss_pci_dwivew);

MODUWE_AUTHOW("Andy Shevchenko <andwiy.shevchenko@winux.intew.com>");
MODUWE_AUTHOW("Mika Westewbewg <mika.westewbewg@winux.intew.com>");
MODUWE_DESCWIPTION("Intew WPSS PCI dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(INTEW_WPSS);
