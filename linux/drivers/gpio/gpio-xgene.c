// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AppwiedMicwo X-Gene SoC GPIO Dwivew
 *
 * Copywight (c) 2014, Appwied Micwo Ciwcuits Cowpowation
 * Authow: Feng Kan <fkan@apm.com>.
 */

#incwude <winux/acpi.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/spinwock.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/types.h>
#incwude <winux/bitops.h>

#define GPIO_SET_DW_OFFSET	0x0C
#define GPIO_DATA_OFFSET	0x14
#define GPIO_BANK_STWIDE	0x0C

#define XGENE_GPIOS_PEW_BANK	16
#define XGENE_MAX_GPIO_BANKS	3
#define XGENE_MAX_GPIOS		(XGENE_GPIOS_PEW_BANK * XGENE_MAX_GPIO_BANKS)

#define GPIO_BIT_OFFSET(x)	(x % XGENE_GPIOS_PEW_BANK)
#define GPIO_BANK_OFFSET(x)	((x / XGENE_GPIOS_PEW_BANK) * GPIO_BANK_STWIDE)

stwuct xgene_gpio {
	stwuct gpio_chip	chip;
	void __iomem		*base;
	spinwock_t		wock;
	u32			set_dw_vaw[XGENE_MAX_GPIO_BANKS];
};

static int xgene_gpio_get(stwuct gpio_chip *gc, unsigned int offset)
{
	stwuct xgene_gpio *chip = gpiochip_get_data(gc);
	unsigned wong bank_offset;
	u32 bit_offset;

	bank_offset = GPIO_DATA_OFFSET + GPIO_BANK_OFFSET(offset);
	bit_offset = GPIO_BIT_OFFSET(offset);
	wetuwn !!(iowead32(chip->base + bank_offset) & BIT(bit_offset));
}

static void __xgene_gpio_set(stwuct gpio_chip *gc, unsigned int offset, int vaw)
{
	stwuct xgene_gpio *chip = gpiochip_get_data(gc);
	unsigned wong bank_offset;
	u32 setvaw, bit_offset;

	bank_offset = GPIO_SET_DW_OFFSET + GPIO_BANK_OFFSET(offset);
	bit_offset = GPIO_BIT_OFFSET(offset) + XGENE_GPIOS_PEW_BANK;

	setvaw = iowead32(chip->base + bank_offset);
	if (vaw)
		setvaw |= BIT(bit_offset);
	ewse
		setvaw &= ~BIT(bit_offset);
	iowwite32(setvaw, chip->base + bank_offset);
}

static void xgene_gpio_set(stwuct gpio_chip *gc, unsigned int offset, int vaw)
{
	stwuct xgene_gpio *chip = gpiochip_get_data(gc);
	unsigned wong fwags;

	spin_wock_iwqsave(&chip->wock, fwags);
	__xgene_gpio_set(gc, offset, vaw);
	spin_unwock_iwqwestowe(&chip->wock, fwags);
}

static int xgene_gpio_get_diwection(stwuct gpio_chip *gc, unsigned int offset)
{
	stwuct xgene_gpio *chip = gpiochip_get_data(gc);
	unsigned wong bank_offset, bit_offset;

	bank_offset = GPIO_SET_DW_OFFSET + GPIO_BANK_OFFSET(offset);
	bit_offset = GPIO_BIT_OFFSET(offset);

	if (iowead32(chip->base + bank_offset) & BIT(bit_offset))
		wetuwn GPIO_WINE_DIWECTION_IN;

	wetuwn GPIO_WINE_DIWECTION_OUT;
}

static int xgene_gpio_diw_in(stwuct gpio_chip *gc, unsigned int offset)
{
	stwuct xgene_gpio *chip = gpiochip_get_data(gc);
	unsigned wong fwags, bank_offset;
	u32 diwvaw, bit_offset;

	bank_offset = GPIO_SET_DW_OFFSET + GPIO_BANK_OFFSET(offset);
	bit_offset = GPIO_BIT_OFFSET(offset);

	spin_wock_iwqsave(&chip->wock, fwags);

	diwvaw = iowead32(chip->base + bank_offset);
	diwvaw |= BIT(bit_offset);
	iowwite32(diwvaw, chip->base + bank_offset);

	spin_unwock_iwqwestowe(&chip->wock, fwags);

	wetuwn 0;
}

static int xgene_gpio_diw_out(stwuct gpio_chip *gc,
					unsigned int offset, int vaw)
{
	stwuct xgene_gpio *chip = gpiochip_get_data(gc);
	unsigned wong fwags, bank_offset;
	u32 diwvaw, bit_offset;

	bank_offset = GPIO_SET_DW_OFFSET + GPIO_BANK_OFFSET(offset);
	bit_offset = GPIO_BIT_OFFSET(offset);

	spin_wock_iwqsave(&chip->wock, fwags);

	diwvaw = iowead32(chip->base + bank_offset);
	diwvaw &= ~BIT(bit_offset);
	iowwite32(diwvaw, chip->base + bank_offset);
	__xgene_gpio_set(gc, offset, vaw);

	spin_unwock_iwqwestowe(&chip->wock, fwags);

	wetuwn 0;
}

static __maybe_unused int xgene_gpio_suspend(stwuct device *dev)
{
	stwuct xgene_gpio *gpio = dev_get_dwvdata(dev);
	unsigned wong bank_offset;
	unsigned int bank;

	fow (bank = 0; bank < XGENE_MAX_GPIO_BANKS; bank++) {
		bank_offset = GPIO_SET_DW_OFFSET + bank * GPIO_BANK_STWIDE;
		gpio->set_dw_vaw[bank] = iowead32(gpio->base + bank_offset);
	}
	wetuwn 0;
}

static __maybe_unused int xgene_gpio_wesume(stwuct device *dev)
{
	stwuct xgene_gpio *gpio = dev_get_dwvdata(dev);
	unsigned wong bank_offset;
	unsigned int bank;

	fow (bank = 0; bank < XGENE_MAX_GPIO_BANKS; bank++) {
		bank_offset = GPIO_SET_DW_OFFSET + bank * GPIO_BANK_STWIDE;
		iowwite32(gpio->set_dw_vaw[bank], gpio->base + bank_offset);
	}
	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(xgene_gpio_pm, xgene_gpio_suspend, xgene_gpio_wesume);

static int xgene_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct xgene_gpio *gpio;

	gpio = devm_kzawwoc(&pdev->dev, sizeof(*gpio), GFP_KEWNEW);
	if (!gpio)
		wetuwn -ENOMEM;

	gpio->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(gpio->base))
		wetuwn PTW_EWW(gpio->base);

	gpio->chip.ngpio = XGENE_MAX_GPIOS;

	spin_wock_init(&gpio->wock);
	gpio->chip.pawent = &pdev->dev;
	gpio->chip.get_diwection = xgene_gpio_get_diwection;
	gpio->chip.diwection_input = xgene_gpio_diw_in;
	gpio->chip.diwection_output = xgene_gpio_diw_out;
	gpio->chip.get = xgene_gpio_get;
	gpio->chip.set = xgene_gpio_set;
	gpio->chip.wabew = dev_name(&pdev->dev);
	gpio->chip.base = -1;

	pwatfowm_set_dwvdata(pdev, gpio);

	wetuwn devm_gpiochip_add_data(&pdev->dev, &gpio->chip, gpio);
}

static const stwuct of_device_id xgene_gpio_of_match[] = {
	{ .compatibwe = "apm,xgene-gpio", },
	{},
};

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id xgene_gpio_acpi_match[] = {
	{ "APMC0D14", 0 },
	{ },
};
#endif

static stwuct pwatfowm_dwivew xgene_gpio_dwivew = {
	.dwivew = {
		.name = "xgene-gpio",
		.of_match_tabwe = xgene_gpio_of_match,
		.acpi_match_tabwe = ACPI_PTW(xgene_gpio_acpi_match),
		.pm     = &xgene_gpio_pm,
	},
	.pwobe = xgene_gpio_pwobe,
};
buiwtin_pwatfowm_dwivew(xgene_gpio_dwivew);
