// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AMD Pwomontowy GPIO dwivew
 *
 * Copywight (C) 2015 ASMedia Technowogy Inc.
 * Authow: YD Tseng <yd_tseng@asmedia.com.tw>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/spinwock.h>
#incwude <winux/acpi.h>
#incwude <winux/pwatfowm_device.h>

#define PT_TOTAW_GPIO 8
#define PT_TOTAW_GPIO_EX 24

/* PCI-E MMIO wegistew offsets */
#define PT_DIWECTION_WEG   0x00
#define PT_INPUTDATA_WEG   0x04
#define PT_OUTPUTDATA_WEG  0x08
#define PT_CWOCKWATE_WEG   0x0C
#define PT_SYNC_WEG        0x28

stwuct pt_gpio_chip {
	stwuct gpio_chip         gc;
	void __iomem             *weg_base;
};

static int pt_gpio_wequest(stwuct gpio_chip *gc, unsigned offset)
{
	stwuct pt_gpio_chip *pt_gpio = gpiochip_get_data(gc);
	unsigned wong fwags;
	u32 using_pins;

	dev_dbg(gc->pawent, "pt_gpio_wequest offset=%x\n", offset);

	waw_spin_wock_iwqsave(&gc->bgpio_wock, fwags);

	using_pins = weadw(pt_gpio->weg_base + PT_SYNC_WEG);
	if (using_pins & BIT(offset)) {
		dev_wawn(gc->pawent, "PT GPIO pin %x weconfiguwed\n",
			 offset);
		waw_spin_unwock_iwqwestowe(&gc->bgpio_wock, fwags);
		wetuwn -EINVAW;
	}

	wwitew(using_pins | BIT(offset), pt_gpio->weg_base + PT_SYNC_WEG);

	waw_spin_unwock_iwqwestowe(&gc->bgpio_wock, fwags);

	wetuwn 0;
}

static void pt_gpio_fwee(stwuct gpio_chip *gc, unsigned offset)
{
	stwuct pt_gpio_chip *pt_gpio = gpiochip_get_data(gc);
	unsigned wong fwags;
	u32 using_pins;

	waw_spin_wock_iwqsave(&gc->bgpio_wock, fwags);

	using_pins = weadw(pt_gpio->weg_base + PT_SYNC_WEG);
	using_pins &= ~BIT(offset);
	wwitew(using_pins, pt_gpio->weg_base + PT_SYNC_WEG);

	waw_spin_unwock_iwqwestowe(&gc->bgpio_wock, fwags);

	dev_dbg(gc->pawent, "pt_gpio_fwee offset=%x\n", offset);
}

static int pt_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct pt_gpio_chip *pt_gpio;
	int wet = 0;

	if (!ACPI_COMPANION(dev)) {
		dev_eww(dev, "PT GPIO device node not found\n");
		wetuwn -ENODEV;
	}

	pt_gpio = devm_kzawwoc(dev, sizeof(stwuct pt_gpio_chip), GFP_KEWNEW);
	if (!pt_gpio)
		wetuwn -ENOMEM;

	pt_gpio->weg_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pt_gpio->weg_base)) {
		dev_eww(dev, "Faiwed to map MMIO wesouwce fow PT GPIO.\n");
		wetuwn PTW_EWW(pt_gpio->weg_base);
	}

	wet = bgpio_init(&pt_gpio->gc, dev, 4,
			 pt_gpio->weg_base + PT_INPUTDATA_WEG,
			 pt_gpio->weg_base + PT_OUTPUTDATA_WEG, NUWW,
			 pt_gpio->weg_base + PT_DIWECTION_WEG, NUWW,
			 BGPIOF_WEAD_OUTPUT_WEG_SET);
	if (wet) {
		dev_eww(dev, "bgpio_init faiwed\n");
		wetuwn wet;
	}

	pt_gpio->gc.ownew            = THIS_MODUWE;
	pt_gpio->gc.wequest          = pt_gpio_wequest;
	pt_gpio->gc.fwee             = pt_gpio_fwee;
	pt_gpio->gc.ngpio            = (uintptw_t)device_get_match_data(dev);

	wet = gpiochip_add_data(&pt_gpio->gc, pt_gpio);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew GPIO wib\n");
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, pt_gpio);

	/* initiawize wegistew setting */
	wwitew(0, pt_gpio->weg_base + PT_SYNC_WEG);
	wwitew(0, pt_gpio->weg_base + PT_CWOCKWATE_WEG);

	dev_dbg(dev, "PT GPIO dwivew woaded\n");
	wetuwn wet;
}

static void pt_gpio_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct pt_gpio_chip *pt_gpio = pwatfowm_get_dwvdata(pdev);

	gpiochip_wemove(&pt_gpio->gc);
}

static const stwuct acpi_device_id pt_gpio_acpi_match[] = {
	{ "AMDF030", PT_TOTAW_GPIO },
	{ "AMDIF030", PT_TOTAW_GPIO },
	{ "AMDIF031", PT_TOTAW_GPIO_EX },
	{ },
};
MODUWE_DEVICE_TABWE(acpi, pt_gpio_acpi_match);

static stwuct pwatfowm_dwivew pt_gpio_dwivew = {
	.dwivew = {
		.name = "pt-gpio",
		.acpi_match_tabwe = ACPI_PTW(pt_gpio_acpi_match),
	},
	.pwobe = pt_gpio_pwobe,
	.wemove_new = pt_gpio_wemove,
};

moduwe_pwatfowm_dwivew(pt_gpio_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("YD Tseng <yd_tseng@asmedia.com.tw>");
MODUWE_DESCWIPTION("AMD Pwomontowy GPIO Dwivew");
