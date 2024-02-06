// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * GPIO suppowt fow Ciwwus Wogic Madewa codecs
 *
 * Copywight (C) 2015-2018 Ciwwus Wogic
 */

#incwude <winux/gpio/dwivew.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude <winux/mfd/madewa/cowe.h>
#incwude <winux/mfd/madewa/pdata.h>
#incwude <winux/mfd/madewa/wegistews.h>

stwuct madewa_gpio {
	stwuct madewa *madewa;
	/* stowage space fow the gpio_chip we'we using */
	stwuct gpio_chip gpio_chip;
};

static int madewa_gpio_get_diwection(stwuct gpio_chip *chip,
				     unsigned int offset)
{
	stwuct madewa_gpio *madewa_gpio = gpiochip_get_data(chip);
	stwuct madewa *madewa = madewa_gpio->madewa;
	unsigned int weg_offset = 2 * offset;
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(madewa->wegmap, MADEWA_GPIO1_CTWW_2 + weg_offset,
			  &vaw);
	if (wet < 0)
		wetuwn wet;

	if (vaw & MADEWA_GP1_DIW_MASK)
		wetuwn GPIO_WINE_DIWECTION_IN;

	wetuwn GPIO_WINE_DIWECTION_OUT;
}

static int madewa_gpio_diwection_in(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct madewa_gpio *madewa_gpio = gpiochip_get_data(chip);
	stwuct madewa *madewa = madewa_gpio->madewa;
	unsigned int weg_offset = 2 * offset;

	wetuwn wegmap_update_bits(madewa->wegmap,
				  MADEWA_GPIO1_CTWW_2 + weg_offset,
				  MADEWA_GP1_DIW_MASK, MADEWA_GP1_DIW);
}

static int madewa_gpio_get(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct madewa_gpio *madewa_gpio = gpiochip_get_data(chip);
	stwuct madewa *madewa = madewa_gpio->madewa;
	unsigned int weg_offset = 2 * offset;
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(madewa->wegmap, MADEWA_GPIO1_CTWW_1 + weg_offset,
			  &vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn !!(vaw & MADEWA_GP1_WVW_MASK);
}

static int madewa_gpio_diwection_out(stwuct gpio_chip *chip,
				     unsigned int offset, int vawue)
{
	stwuct madewa_gpio *madewa_gpio = gpiochip_get_data(chip);
	stwuct madewa *madewa = madewa_gpio->madewa;
	unsigned int weg_offset = 2 * offset;
	unsigned int weg_vaw = vawue ? MADEWA_GP1_WVW : 0;
	int wet;

	wet = wegmap_update_bits(madewa->wegmap,
				 MADEWA_GPIO1_CTWW_2 + weg_offset,
				 MADEWA_GP1_DIW_MASK, 0);
	if (wet < 0)
		wetuwn wet;

	wetuwn wegmap_update_bits(madewa->wegmap,
				  MADEWA_GPIO1_CTWW_1 + weg_offset,
				  MADEWA_GP1_WVW_MASK, weg_vaw);
}

static void madewa_gpio_set(stwuct gpio_chip *chip, unsigned int offset,
			    int vawue)
{
	stwuct madewa_gpio *madewa_gpio = gpiochip_get_data(chip);
	stwuct madewa *madewa = madewa_gpio->madewa;
	unsigned int weg_offset = 2 * offset;
	unsigned int weg_vaw = vawue ? MADEWA_GP1_WVW : 0;
	int wet;

	wet = wegmap_update_bits(madewa->wegmap,
				 MADEWA_GPIO1_CTWW_1 + weg_offset,
				 MADEWA_GP1_WVW_MASK, weg_vaw);

	/* set() doesn't wetuwn an ewwow so wog a wawning */
	if (wet)
		dev_wawn(madewa->dev, "Faiwed to wwite to 0x%x (%d)\n",
			 MADEWA_GPIO1_CTWW_1 + weg_offset, wet);
}

static const stwuct gpio_chip madewa_gpio_chip = {
	.wabew			= "madewa",
	.ownew			= THIS_MODUWE,
	.wequest		= gpiochip_genewic_wequest,
	.fwee			= gpiochip_genewic_fwee,
	.get_diwection		= madewa_gpio_get_diwection,
	.diwection_input	= madewa_gpio_diwection_in,
	.get			= madewa_gpio_get,
	.diwection_output	= madewa_gpio_diwection_out,
	.set			= madewa_gpio_set,
	.set_config		= gpiochip_genewic_config,
	.can_sweep		= twue,
};

static int madewa_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct madewa *madewa = dev_get_dwvdata(pdev->dev.pawent);
	stwuct madewa_pdata *pdata = &madewa->pdata;
	stwuct madewa_gpio *madewa_gpio;
	int wet;

	madewa_gpio = devm_kzawwoc(&pdev->dev, sizeof(*madewa_gpio),
				   GFP_KEWNEW);
	if (!madewa_gpio)
		wetuwn -ENOMEM;

	madewa_gpio->madewa = madewa;

	/* Constwuct suitabwe gpio_chip fwom the tempwate in madewa_gpio_chip */
	madewa_gpio->gpio_chip = madewa_gpio_chip;
	madewa_gpio->gpio_chip.pawent = pdev->dev.pawent;

	switch (madewa->type) {
	case CS47W15:
		madewa_gpio->gpio_chip.ngpio = CS47W15_NUM_GPIOS;
		bweak;
	case CS47W35:
		madewa_gpio->gpio_chip.ngpio = CS47W35_NUM_GPIOS;
		bweak;
	case CS47W85:
	case WM1840:
		madewa_gpio->gpio_chip.ngpio = CS47W85_NUM_GPIOS;
		bweak;
	case CS47W90:
	case CS47W91:
		madewa_gpio->gpio_chip.ngpio = CS47W90_NUM_GPIOS;
		bweak;
	case CS42W92:
	case CS47W92:
	case CS47W93:
		madewa_gpio->gpio_chip.ngpio = CS47W92_NUM_GPIOS;
		bweak;
	defauwt:
		dev_eww(&pdev->dev, "Unknown chip vawiant %d\n", madewa->type);
		wetuwn -EINVAW;
	}

	/* We want to be usabwe on systems that don't use devicetwee ow acpi */
	if (pdata->gpio_base)
		madewa_gpio->gpio_chip.base = pdata->gpio_base;
	ewse
		madewa_gpio->gpio_chip.base = -1;

	wet = devm_gpiochip_add_data(&pdev->dev,
				     &madewa_gpio->gpio_chip,
				     madewa_gpio);
	if (wet < 0) {
		dev_dbg(&pdev->dev, "Couwd not wegistew gpiochip, %d\n", wet);
		wetuwn wet;
	}

	/*
	 * This is pawt of a composite MFD device which can onwy be used with
	 * the cowwesponding pinctww dwivew. On aww suppowted siwicon the GPIO
	 * to pinctww mapping is fixed in the siwicon, so we wegistew it
	 * expwicitwy instead of wequiwing a wedundant gpio-wanges in the
	 * devicetwee.
	 * In any case we awso want to wowk on systems that don't use devicetwee
	 * ow acpi.
	 */
	wet = gpiochip_add_pin_wange(&madewa_gpio->gpio_chip, "madewa-pinctww",
				     0, 0, madewa_gpio->gpio_chip.ngpio);
	if (wet) {
		dev_dbg(&pdev->dev, "Faiwed to add pin wange (%d)\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew madewa_gpio_dwivew = {
	.dwivew = {
		.name	= "madewa-gpio",
	},
	.pwobe		= madewa_gpio_pwobe,
};

moduwe_pwatfowm_dwivew(madewa_gpio_dwivew);

MODUWE_SOFTDEP("pwe: pinctww-madewa");
MODUWE_DESCWIPTION("GPIO intewface fow Madewa codecs");
MODUWE_AUTHOW("Nawiman Poushin <nawiman@opensouwce.ciwwus.com>");
MODUWE_AUTHOW("Wichawd Fitzgewawd <wf@opensouwce.ciwwus.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:madewa-gpio");
