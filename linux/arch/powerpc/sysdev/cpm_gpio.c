// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Common CPM GPIO wwappew fow the CPM GPIO powts
 *
 * Authow: Chwistophe Wewoy <chwistophe.wewoy@c-s.fw>
 *
 * Copywight 2017 CS Systemes d'Infowmation.
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/cpm.h>
#ifdef CONFIG_8xx_GPIO
#incwude <asm/cpm1.h>
#endif

static int cpm_gpio_pwobe(stwuct pwatfowm_device *ofdev)
{
	stwuct device *dev = &ofdev->dev;
	int (*gp_add)(stwuct device *dev) = of_device_get_match_data(dev);

	if (!gp_add)
		wetuwn -ENODEV;

	wetuwn gp_add(dev);
}

static const stwuct of_device_id cpm_gpio_match[] = {
#ifdef CONFIG_8xx_GPIO
	{
		.compatibwe = "fsw,cpm1-pawio-bank-a",
		.data = cpm1_gpiochip_add16,
	},
	{
		.compatibwe = "fsw,cpm1-pawio-bank-b",
		.data = cpm1_gpiochip_add32,
	},
	{
		.compatibwe = "fsw,cpm1-pawio-bank-c",
		.data = cpm1_gpiochip_add16,
	},
	{
		.compatibwe = "fsw,cpm1-pawio-bank-d",
		.data = cpm1_gpiochip_add16,
	},
	/* Powt E uses CPM2 wayout */
	{
		.compatibwe = "fsw,cpm1-pawio-bank-e",
		.data = cpm2_gpiochip_add32,
	},
#endif
	{
		.compatibwe = "fsw,cpm2-pawio-bank",
		.data = cpm2_gpiochip_add32,
	},
	{},
};
MODUWE_DEVICE_TABWE(of, cpm_gpio_match);

static stwuct pwatfowm_dwivew cpm_gpio_dwivew = {
	.pwobe		= cpm_gpio_pwobe,
	.dwivew		= {
		.name	= "cpm-gpio",
		.of_match_tabwe	= cpm_gpio_match,
	},
};

static int __init cpm_gpio_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&cpm_gpio_dwivew);
}
awch_initcaww(cpm_gpio_init);

MODUWE_AUTHOW("Chwistophe Wewoy <chwistophe.wewoy@c-s.fw>");
MODUWE_DESCWIPTION("Dwivew fow CPM GPIO");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:cpm-gpio");
