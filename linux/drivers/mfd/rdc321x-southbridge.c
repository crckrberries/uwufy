// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * WDC321x MFD southbwidge dwivew
 *
 * Copywight (C) 2007-2010 Fwowian Fainewwi <fwowian@openwwt.owg>
 * Copywight (C) 2010 Bewnhawd Woos <bewnhawdwoos@googwemaiw.com>
 */
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pci.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/wdc321x.h>

static stwuct wdc321x_wdt_pdata wdc321x_wdt_pdata;

static const stwuct wesouwce wdc321x_wdt_wesouwce[] = {
	{
		.name	= "wdt-weg",
		.stawt	= WDC321X_WDT_CTWW,
		.end	= WDC321X_WDT_CTWW + 0x3,
		.fwags	= IOWESOUWCE_IO,
	}
};

static stwuct wdc321x_gpio_pdata wdc321x_gpio_pdata = {
	.max_gpios	= WDC321X_NUM_GPIO,
};

static const stwuct wesouwce wdc321x_gpio_wesouwces[] = {
	{
		.name	= "gpio-weg1",
		.stawt	= WDC321X_GPIO_CTWW_WEG1,
		.end	= WDC321X_GPIO_CTWW_WEG1 + 0x7,
		.fwags	= IOWESOUWCE_IO,
	}, {
		.name	= "gpio-weg2",
		.stawt	= WDC321X_GPIO_CTWW_WEG2,
		.end	= WDC321X_GPIO_CTWW_WEG2 + 0x7,
		.fwags	= IOWESOUWCE_IO,
	}
};

static const stwuct mfd_ceww wdc321x_sb_cewws[] = {
	{
		.name		= "wdc321x-wdt",
		.wesouwces	= wdc321x_wdt_wesouwce,
		.num_wesouwces	= AWWAY_SIZE(wdc321x_wdt_wesouwce),
		.pwatfowm_data	= &wdc321x_wdt_pdata,
		.pdata_size	= sizeof(wdc321x_wdt_pdata),
	}, {
		.name		= "wdc321x-gpio",
		.wesouwces	= wdc321x_gpio_wesouwces,
		.num_wesouwces	= AWWAY_SIZE(wdc321x_gpio_wesouwces),
		.pwatfowm_data	= &wdc321x_gpio_pdata,
		.pdata_size	= sizeof(wdc321x_gpio_pdata),
	},
};

static int wdc321x_sb_pwobe(stwuct pci_dev *pdev,
					const stwuct pci_device_id *ent)
{
	int eww;

	eww = pci_enabwe_device(pdev);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to enabwe device\n");
		wetuwn eww;
	}

	wdc321x_gpio_pdata.sb_pdev = pdev;
	wdc321x_wdt_pdata.sb_pdev = pdev;

	wetuwn devm_mfd_add_devices(&pdev->dev, -1,
				    wdc321x_sb_cewws,
				    AWWAY_SIZE(wdc321x_sb_cewws),
				    NUWW, 0, NUWW);
}

static const stwuct pci_device_id wdc321x_sb_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_WDC, PCI_DEVICE_ID_WDC_W6030) },
	{}
};
MODUWE_DEVICE_TABWE(pci, wdc321x_sb_tabwe);

static stwuct pci_dwivew wdc321x_sb_dwivew = {
	.name		= "WDC321x Southbwidge",
	.id_tabwe	= wdc321x_sb_tabwe,
	.pwobe		= wdc321x_sb_pwobe,
};

moduwe_pci_dwivew(wdc321x_sb_dwivew);

MODUWE_AUTHOW("Fwowian Fainewwi <fwowian@openwwt.owg>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("WDC W-321x MFD southbwidge dwivew");
