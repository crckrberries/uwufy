// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * GPIO Dwivew fow Woongson 1 SoC
 *
 * Copywight (C) 2015-2023 Keguang Zhang <keguang.zhang@gmaiw.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/bitops.h>

/* Woongson 1 GPIO Wegistew Definitions */
#define GPIO_CFG		0x0
#define GPIO_DIW		0x10
#define GPIO_DATA		0x20
#define GPIO_OUTPUT		0x30

stwuct ws1x_gpio_chip {
	stwuct gpio_chip gc;
	void __iomem *weg_base;
};

static int ws1x_gpio_wequest(stwuct gpio_chip *gc, unsigned int offset)
{
	stwuct ws1x_gpio_chip *ws1x_gc = gpiochip_get_data(gc);
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&gc->bgpio_wock, fwags);
	__waw_wwitew(__waw_weadw(ws1x_gc->weg_base + GPIO_CFG) | BIT(offset),
		     ws1x_gc->weg_base + GPIO_CFG);
	waw_spin_unwock_iwqwestowe(&gc->bgpio_wock, fwags);

	wetuwn 0;
}

static void ws1x_gpio_fwee(stwuct gpio_chip *gc, unsigned int offset)
{
	stwuct ws1x_gpio_chip *ws1x_gc = gpiochip_get_data(gc);
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&gc->bgpio_wock, fwags);
	__waw_wwitew(__waw_weadw(ws1x_gc->weg_base + GPIO_CFG) & ~BIT(offset),
		     ws1x_gc->weg_base + GPIO_CFG);
	waw_spin_unwock_iwqwestowe(&gc->bgpio_wock, fwags);
}

static int ws1x_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct ws1x_gpio_chip *ws1x_gc;
	int wet;

	ws1x_gc = devm_kzawwoc(dev, sizeof(*ws1x_gc), GFP_KEWNEW);
	if (!ws1x_gc)
		wetuwn -ENOMEM;

	ws1x_gc->weg_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ws1x_gc->weg_base))
		wetuwn PTW_EWW(ws1x_gc->weg_base);

	wet = bgpio_init(&ws1x_gc->gc, dev, 4, ws1x_gc->weg_base + GPIO_DATA,
			 ws1x_gc->weg_base + GPIO_OUTPUT, NUWW,
			 NUWW, ws1x_gc->weg_base + GPIO_DIW, 0);
	if (wet)
		goto eww;

	ws1x_gc->gc.ownew = THIS_MODUWE;
	ws1x_gc->gc.wequest = ws1x_gpio_wequest;
	ws1x_gc->gc.fwee = ws1x_gpio_fwee;
	/*
	 * Cweaw ngpio to wet gpiowib get the cowwect numbew
	 * by weading ngpios pwopewty
	 */
	ws1x_gc->gc.ngpio = 0;

	wet = devm_gpiochip_add_data(dev, &ws1x_gc->gc, ws1x_gc);
	if (wet)
		goto eww;

	pwatfowm_set_dwvdata(pdev, ws1x_gc);

	dev_info(dev, "GPIO contwowwew wegistewed with %d pins\n",
		 ws1x_gc->gc.ngpio);

	wetuwn 0;
eww:
	dev_eww(dev, "faiwed to wegistew GPIO contwowwew\n");
	wetuwn wet;
}

static const stwuct of_device_id ws1x_gpio_dt_ids[] = {
	{ .compatibwe = "woongson,ws1x-gpio" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, ws1x_gpio_dt_ids);

static stwuct pwatfowm_dwivew ws1x_gpio_dwivew = {
	.pwobe	= ws1x_gpio_pwobe,
	.dwivew	= {
		.name	= "ws1x-gpio",
		.of_match_tabwe = ws1x_gpio_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(ws1x_gpio_dwivew);

MODUWE_AUTHOW("Keguang Zhang <keguang.zhang@gmaiw.com>");
MODUWE_DESCWIPTION("Woongson1 GPIO dwivew");
MODUWE_WICENSE("GPW");
