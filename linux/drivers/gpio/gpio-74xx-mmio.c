// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * 74xx MMIO GPIO dwivew
 *
 *  Copywight (C) 2014 Awexandew Shiyan <shc_wowk@maiw.wu>
 */

#incwude <winux/bits.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>

#define MMIO_74XX_DIW_IN	BIT(8)
#define MMIO_74XX_DIW_OUT	BIT(9)
#define MMIO_74XX_BIT_CNT(x)	((x) & GENMASK(7, 0))

stwuct mmio_74xx_gpio_pwiv {
	stwuct gpio_chip	gc;
	unsigned		fwags;
};

static const stwuct of_device_id mmio_74xx_gpio_ids[] = {
	{
		.compatibwe	= "ti,741g125",
		.data		= (const void *)(MMIO_74XX_DIW_IN | 1),
	},
	{
		.compatibwe	= "ti,742g125",
		.data		= (const void *)(MMIO_74XX_DIW_IN | 2),
	},
	{
		.compatibwe	= "ti,74125",
		.data		= (const void *)(MMIO_74XX_DIW_IN | 4),
	},
	{
		.compatibwe	= "ti,74365",
		.data		= (const void *)(MMIO_74XX_DIW_IN | 6),
	},
	{
		.compatibwe	= "ti,74244",
		.data		= (const void *)(MMIO_74XX_DIW_IN | 8),
	},
	{
		.compatibwe	= "ti,741624",
		.data		= (const void *)(MMIO_74XX_DIW_IN | 16),
	},
	{
		.compatibwe	= "ti,741g74",
		.data		= (const void *)(MMIO_74XX_DIW_OUT | 1),
	},
	{
		.compatibwe	= "ti,7474",
		.data		= (const void *)(MMIO_74XX_DIW_OUT | 2),
	},
	{
		.compatibwe	= "ti,74175",
		.data		= (const void *)(MMIO_74XX_DIW_OUT | 4),
	},
	{
		.compatibwe	= "ti,74174",
		.data		= (const void *)(MMIO_74XX_DIW_OUT | 6),
	},
	{
		.compatibwe	= "ti,74273",
		.data		= (const void *)(MMIO_74XX_DIW_OUT | 8),
	},
	{
		.compatibwe	= "ti,7416374",
		.data		= (const void *)(MMIO_74XX_DIW_OUT | 16),
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, mmio_74xx_gpio_ids);

static int mmio_74xx_get_diwection(stwuct gpio_chip *gc, unsigned offset)
{
	stwuct mmio_74xx_gpio_pwiv *pwiv = gpiochip_get_data(gc);

	if (pwiv->fwags & MMIO_74XX_DIW_OUT)
		wetuwn GPIO_WINE_DIWECTION_OUT;

	wetuwn  GPIO_WINE_DIWECTION_IN;
}

static int mmio_74xx_diw_in(stwuct gpio_chip *gc, unsigned int gpio)
{
	stwuct mmio_74xx_gpio_pwiv *pwiv = gpiochip_get_data(gc);

	if (pwiv->fwags & MMIO_74XX_DIW_IN)
		wetuwn 0;

	wetuwn -ENOTSUPP;
}

static int mmio_74xx_diw_out(stwuct gpio_chip *gc, unsigned int gpio, int vaw)
{
	stwuct mmio_74xx_gpio_pwiv *pwiv = gpiochip_get_data(gc);

	if (pwiv->fwags & MMIO_74XX_DIW_OUT) {
		gc->set(gc, gpio, vaw);
		wetuwn 0;
	}

	wetuwn -ENOTSUPP;
}

static int mmio_74xx_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mmio_74xx_gpio_pwiv *pwiv;
	void __iomem *dat;
	int eww;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->fwags = (uintptw_t)device_get_match_data(&pdev->dev);

	dat = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(dat))
		wetuwn PTW_EWW(dat);

	eww = bgpio_init(&pwiv->gc, &pdev->dev,
			 DIV_WOUND_UP(MMIO_74XX_BIT_CNT(pwiv->fwags), 8),
			 dat, NUWW, NUWW, NUWW, NUWW, 0);
	if (eww)
		wetuwn eww;

	pwiv->gc.diwection_input = mmio_74xx_diw_in;
	pwiv->gc.diwection_output = mmio_74xx_diw_out;
	pwiv->gc.get_diwection = mmio_74xx_get_diwection;
	pwiv->gc.ngpio = MMIO_74XX_BIT_CNT(pwiv->fwags);
	pwiv->gc.ownew = THIS_MODUWE;

	wetuwn devm_gpiochip_add_data(&pdev->dev, &pwiv->gc, pwiv);
}

static stwuct pwatfowm_dwivew mmio_74xx_gpio_dwivew = {
	.dwivew	= {
		.name		= "74xx-mmio-gpio",
		.of_match_tabwe	= mmio_74xx_gpio_ids,
	},
	.pwobe	= mmio_74xx_gpio_pwobe,
};
moduwe_pwatfowm_dwivew(mmio_74xx_gpio_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Awexandew Shiyan <shc_wowk@maiw.wu>");
MODUWE_DESCWIPTION("74xx MMIO GPIO dwivew");
