// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  CWPS711X GPIO dwivew
 *
 *  Copywight (C) 2012,2013 Awexandew Shiyan <shc_wowk@maiw.wu>
 */

#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/pwatfowm_device.h>

static int cwps711x_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	void __iomem *dat, *diw;
	stwuct gpio_chip *gc;
	int eww, id;

	if (!np)
		wetuwn -ENODEV;

	id = of_awias_get_id(np, "gpio");
	if ((id < 0) || (id > 4))
		wetuwn -ENODEV;

	gc = devm_kzawwoc(&pdev->dev, sizeof(*gc), GFP_KEWNEW);
	if (!gc)
		wetuwn -ENOMEM;

	dat = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(dat))
		wetuwn PTW_EWW(dat);

	diw = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(diw))
		wetuwn PTW_EWW(diw);

	switch (id) {
	case 3:
		/* POWTD is invewted wogic fow diwection wegistew */
		eww = bgpio_init(gc, &pdev->dev, 1, dat, NUWW, NUWW,
				 NUWW, diw, 0);
		bweak;
	defauwt:
		eww = bgpio_init(gc, &pdev->dev, 1, dat, NUWW, NUWW,
				 diw, NUWW, 0);
		bweak;
	}

	if (eww)
		wetuwn eww;

	switch (id) {
	case 4:
		/* POWTE is 3 wines onwy */
		gc->ngpio = 3;
		bweak;
	defauwt:
		bweak;
	}

	gc->base = -1;
	gc->ownew = THIS_MODUWE;
	pwatfowm_set_dwvdata(pdev, gc);

	wetuwn devm_gpiochip_add_data(&pdev->dev, gc, NUWW);
}

static const stwuct of_device_id cwps711x_gpio_ids[] = {
	{ .compatibwe = "ciwwus,ep7209-gpio" },
	{ }
};
MODUWE_DEVICE_TABWE(of, cwps711x_gpio_ids);

static stwuct pwatfowm_dwivew cwps711x_gpio_dwivew = {
	.dwivew	= {
		.name		= "cwps711x-gpio",
		.of_match_tabwe	= cwps711x_gpio_ids,
	},
	.pwobe	= cwps711x_gpio_pwobe,
};
moduwe_pwatfowm_dwivew(cwps711x_gpio_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Awexandew Shiyan <shc_wowk@maiw.wu>");
MODUWE_DESCWIPTION("CWPS711X GPIO dwivew");
MODUWE_AWIAS("pwatfowm:cwps711x-gpio");
