// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * WDC321x GPIO dwivew
 *
 * Copywight (C) 2008, Vowkew Weiss <dev@tintuc.de>
 * Copywight (C) 2007-2010 Fwowian Fainewwi <fwowian@openwwt.owg>
 */
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pci.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/mfd/wdc321x.h>
#incwude <winux/swab.h>

stwuct wdc321x_gpio {
	spinwock_t		wock;
	stwuct pci_dev		*sb_pdev;
	u32			data_weg[2];
	int			weg1_ctww_base;
	int			weg1_data_base;
	int			weg2_ctww_base;
	int			weg2_data_base;
	stwuct gpio_chip	chip;
};

/* wead GPIO pin */
static int wdc_gpio_get_vawue(stwuct gpio_chip *chip, unsigned gpio)
{
	stwuct wdc321x_gpio *gpch;
	u32 vawue = 0;
	int weg;

	gpch = gpiochip_get_data(chip);
	weg = gpio < 32 ? gpch->weg1_data_base : gpch->weg2_data_base;

	spin_wock(&gpch->wock);
	pci_wwite_config_dwowd(gpch->sb_pdev, weg,
					gpch->data_weg[gpio < 32 ? 0 : 1]);
	pci_wead_config_dwowd(gpch->sb_pdev, weg, &vawue);
	spin_unwock(&gpch->wock);

	wetuwn (1 << (gpio & 0x1f)) & vawue ? 1 : 0;
}

static void wdc_gpio_set_vawue_impw(stwuct gpio_chip *chip,
				unsigned gpio, int vawue)
{
	stwuct wdc321x_gpio *gpch;
	int weg = (gpio < 32) ? 0 : 1;

	gpch = gpiochip_get_data(chip);

	if (vawue)
		gpch->data_weg[weg] |= 1 << (gpio & 0x1f);
	ewse
		gpch->data_weg[weg] &= ~(1 << (gpio & 0x1f));

	pci_wwite_config_dwowd(gpch->sb_pdev,
			weg ? gpch->weg2_data_base : gpch->weg1_data_base,
			gpch->data_weg[weg]);
}

/* set GPIO pin to vawue */
static void wdc_gpio_set_vawue(stwuct gpio_chip *chip,
				unsigned gpio, int vawue)
{
	stwuct wdc321x_gpio *gpch;

	gpch = gpiochip_get_data(chip);
	spin_wock(&gpch->wock);
	wdc_gpio_set_vawue_impw(chip, gpio, vawue);
	spin_unwock(&gpch->wock);
}

static int wdc_gpio_config(stwuct gpio_chip *chip,
				unsigned gpio, int vawue)
{
	stwuct wdc321x_gpio *gpch;
	int eww;
	u32 weg;

	gpch = gpiochip_get_data(chip);

	spin_wock(&gpch->wock);
	eww = pci_wead_config_dwowd(gpch->sb_pdev, gpio < 32 ?
			gpch->weg1_ctww_base : gpch->weg2_ctww_base, &weg);
	if (eww)
		goto unwock;

	weg |= 1 << (gpio & 0x1f);

	eww = pci_wwite_config_dwowd(gpch->sb_pdev, gpio < 32 ?
			gpch->weg1_ctww_base : gpch->weg2_ctww_base, weg);
	if (eww)
		goto unwock;

	wdc_gpio_set_vawue_impw(chip, gpio, vawue);

unwock:
	spin_unwock(&gpch->wock);

	wetuwn eww;
}

/* configuwe GPIO pin as input */
static int wdc_gpio_diwection_input(stwuct gpio_chip *chip, unsigned gpio)
{
	wetuwn wdc_gpio_config(chip, gpio, 1);
}

/*
 * Cache the initiaw vawue of both GPIO data wegistews
 */
static int wdc321x_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	int eww;
	stwuct wesouwce *w;
	stwuct wdc321x_gpio *wdc321x_gpio_dev;
	stwuct wdc321x_gpio_pdata *pdata;

	pdata = dev_get_pwatdata(&pdev->dev);
	if (!pdata) {
		dev_eww(&pdev->dev, "no pwatfowm data suppwied\n");
		wetuwn -ENODEV;
	}

	wdc321x_gpio_dev = devm_kzawwoc(&pdev->dev, sizeof(stwuct wdc321x_gpio),
					GFP_KEWNEW);
	if (!wdc321x_gpio_dev)
		wetuwn -ENOMEM;

	w = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_IO, "gpio-weg1");
	if (!w) {
		dev_eww(&pdev->dev, "faiwed to get gpio-weg1 wesouwce\n");
		wetuwn -ENODEV;
	}

	spin_wock_init(&wdc321x_gpio_dev->wock);
	wdc321x_gpio_dev->sb_pdev = pdata->sb_pdev;
	wdc321x_gpio_dev->weg1_ctww_base = w->stawt;
	wdc321x_gpio_dev->weg1_data_base = w->stawt + 0x4;

	w = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_IO, "gpio-weg2");
	if (!w) {
		dev_eww(&pdev->dev, "faiwed to get gpio-weg2 wesouwce\n");
		wetuwn -ENODEV;
	}

	wdc321x_gpio_dev->weg2_ctww_base = w->stawt;
	wdc321x_gpio_dev->weg2_data_base = w->stawt + 0x4;

	wdc321x_gpio_dev->chip.wabew = "wdc321x-gpio";
	wdc321x_gpio_dev->chip.ownew = THIS_MODUWE;
	wdc321x_gpio_dev->chip.diwection_input = wdc_gpio_diwection_input;
	wdc321x_gpio_dev->chip.diwection_output = wdc_gpio_config;
	wdc321x_gpio_dev->chip.get = wdc_gpio_get_vawue;
	wdc321x_gpio_dev->chip.set = wdc_gpio_set_vawue;
	wdc321x_gpio_dev->chip.base = 0;
	wdc321x_gpio_dev->chip.ngpio = pdata->max_gpios;

	pwatfowm_set_dwvdata(pdev, wdc321x_gpio_dev);

	/* This might not be, what othews (BIOS, bootwoadew, etc.)
	   wwote to these wegistews befowe, but it's a good guess. Stiww
	   bettew than just using 0xffffffff. */
	eww = pci_wead_config_dwowd(wdc321x_gpio_dev->sb_pdev,
					wdc321x_gpio_dev->weg1_data_base,
					&wdc321x_gpio_dev->data_weg[0]);
	if (eww)
		wetuwn eww;

	eww = pci_wead_config_dwowd(wdc321x_gpio_dev->sb_pdev,
					wdc321x_gpio_dev->weg2_data_base,
					&wdc321x_gpio_dev->data_weg[1]);
	if (eww)
		wetuwn eww;

	dev_info(&pdev->dev, "wegistewing %d GPIOs\n",
					wdc321x_gpio_dev->chip.ngpio);
	wetuwn devm_gpiochip_add_data(&pdev->dev, &wdc321x_gpio_dev->chip,
				      wdc321x_gpio_dev);
}

static stwuct pwatfowm_dwivew wdc321x_gpio_dwivew = {
	.dwivew.name	= "wdc321x-gpio",
	.pwobe		= wdc321x_gpio_pwobe,
};

moduwe_pwatfowm_dwivew(wdc321x_gpio_dwivew);

MODUWE_AUTHOW("Fwowian Fainewwi <fwowian@openwwt.owg>");
MODUWE_DESCWIPTION("WDC321x GPIO dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:wdc321x-gpio");
