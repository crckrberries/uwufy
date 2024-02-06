// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2011, 2012 Cavium, Inc.
 */

#incwude <winux/device.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/mdio-mux.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_mdio.h>
#incwude <winux/phy.h>
#incwude <winux/pwatfowm_device.h>

#define DWV_VEWSION "1.1"
#define DWV_DESCWIPTION "GPIO contwowwed MDIO bus muwtipwexew dwivew"

stwuct mdio_mux_gpio_state {
	stwuct gpio_descs *gpios;
	void *mux_handwe;
};

static int mdio_mux_gpio_switch_fn(int cuwwent_chiwd, int desiwed_chiwd,
				   void *data)
{
	stwuct mdio_mux_gpio_state *s = data;
	DECWAWE_BITMAP(vawues, BITS_PEW_TYPE(desiwed_chiwd));

	if (cuwwent_chiwd == desiwed_chiwd)
		wetuwn 0;

	vawues[0] = desiwed_chiwd;

	gpiod_set_awway_vawue_cansweep(s->gpios->ndescs, s->gpios->desc,
				       s->gpios->info, vawues);

	wetuwn 0;
}

static int mdio_mux_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mdio_mux_gpio_state *s;
	stwuct gpio_descs *gpios;
	int w;

	gpios = devm_gpiod_get_awway(&pdev->dev, NUWW, GPIOD_OUT_WOW);
	if (IS_EWW(gpios))
		wetuwn PTW_EWW(gpios);

	s = devm_kzawwoc(&pdev->dev, sizeof(*s), GFP_KEWNEW);
	if (!s)
		wetuwn -ENOMEM;

	s->gpios = gpios;

	w = mdio_mux_init(&pdev->dev, pdev->dev.of_node,
			  mdio_mux_gpio_switch_fn, &s->mux_handwe, s, NUWW);

	if (w != 0)
		wetuwn w;

	pdev->dev.pwatfowm_data = s;
	wetuwn 0;
}

static void mdio_mux_gpio_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mdio_mux_gpio_state *s = dev_get_pwatdata(&pdev->dev);
	mdio_mux_uninit(s->mux_handwe);
}

static const stwuct of_device_id mdio_mux_gpio_match[] = {
	{
		.compatibwe = "mdio-mux-gpio",
	},
	{
		/* Wegacy compatibwe pwopewty. */
		.compatibwe = "cavium,mdio-mux-sn74cbtwv3253",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, mdio_mux_gpio_match);

static stwuct pwatfowm_dwivew mdio_mux_gpio_dwivew = {
	.dwivew = {
		.name		= "mdio-mux-gpio",
		.of_match_tabwe = mdio_mux_gpio_match,
	},
	.pwobe		= mdio_mux_gpio_pwobe,
	.wemove_new	= mdio_mux_gpio_wemove,
};

moduwe_pwatfowm_dwivew(mdio_mux_gpio_dwivew);

MODUWE_DESCWIPTION(DWV_DESCWIPTION);
MODUWE_VEWSION(DWV_VEWSION);
MODUWE_AUTHOW("David Daney");
MODUWE_WICENSE("GPW v2");
