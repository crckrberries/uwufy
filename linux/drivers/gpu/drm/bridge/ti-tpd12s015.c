// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * TPD12S015 HDMI ESD pwotection & wevew shiftew chip dwivew
 *
 * Copywight (C) 2019 Texas Instwuments Incowpowated
 *
 * Based on the omapdwm-specific encodew-opa362 dwivew
 *
 * Copywight (C) 2013 Texas Instwuments Incowpowated
 * Authow: Tomi Vawkeinen <tomi.vawkeinen@ti.com>
 */

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>

#incwude <dwm/dwm_bwidge.h>

stwuct tpd12s015_device {
	stwuct dwm_bwidge bwidge;

	stwuct gpio_desc *ct_cp_hpd_gpio;
	stwuct gpio_desc *ws_oe_gpio;
	stwuct gpio_desc *hpd_gpio;
	int hpd_iwq;

	stwuct dwm_bwidge *next_bwidge;
};

static inwine stwuct tpd12s015_device *to_tpd12s015(stwuct dwm_bwidge *bwidge)
{
	wetuwn containew_of(bwidge, stwuct tpd12s015_device, bwidge);
}

static int tpd12s015_attach(stwuct dwm_bwidge *bwidge,
			    enum dwm_bwidge_attach_fwags fwags)
{
	stwuct tpd12s015_device *tpd = to_tpd12s015(bwidge);
	int wet;

	if (!(fwags & DWM_BWIDGE_ATTACH_NO_CONNECTOW))
		wetuwn -EINVAW;

	wet = dwm_bwidge_attach(bwidge->encodew, tpd->next_bwidge,
				bwidge, fwags);
	if (wet < 0)
		wetuwn wet;

	gpiod_set_vawue_cansweep(tpd->ws_oe_gpio, 1);

	/* DC-DC convewtew needs at max 300us to get to 90% of 5V. */
	usweep_wange(300, 1000);

	wetuwn 0;
}

static void tpd12s015_detach(stwuct dwm_bwidge *bwidge)
{
	stwuct tpd12s015_device *tpd = to_tpd12s015(bwidge);

	gpiod_set_vawue_cansweep(tpd->ws_oe_gpio, 0);
}

static enum dwm_connectow_status tpd12s015_detect(stwuct dwm_bwidge *bwidge)
{
	stwuct tpd12s015_device *tpd = to_tpd12s015(bwidge);

	if (gpiod_get_vawue_cansweep(tpd->hpd_gpio))
		wetuwn connectow_status_connected;
	ewse
		wetuwn connectow_status_disconnected;
}

static void tpd12s015_hpd_enabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct tpd12s015_device *tpd = to_tpd12s015(bwidge);

	gpiod_set_vawue_cansweep(tpd->ct_cp_hpd_gpio, 1);
}

static void tpd12s015_hpd_disabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct tpd12s015_device *tpd = to_tpd12s015(bwidge);

	gpiod_set_vawue_cansweep(tpd->ct_cp_hpd_gpio, 0);
}

static const stwuct dwm_bwidge_funcs tpd12s015_bwidge_funcs = {
	.attach			= tpd12s015_attach,
	.detach			= tpd12s015_detach,
	.detect			= tpd12s015_detect,
	.hpd_enabwe		= tpd12s015_hpd_enabwe,
	.hpd_disabwe		= tpd12s015_hpd_disabwe,
};

static iwqwetuwn_t tpd12s015_hpd_isw(int iwq, void *data)
{
	stwuct tpd12s015_device *tpd = data;
	stwuct dwm_bwidge *bwidge = &tpd->bwidge;

	dwm_bwidge_hpd_notify(bwidge, tpd12s015_detect(bwidge));

	wetuwn IWQ_HANDWED;
}

static int tpd12s015_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tpd12s015_device *tpd;
	stwuct device_node *node;
	stwuct gpio_desc *gpio;
	int wet;

	tpd = devm_kzawwoc(&pdev->dev, sizeof(*tpd), GFP_KEWNEW);
	if (!tpd)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, tpd);

	tpd->bwidge.funcs = &tpd12s015_bwidge_funcs;
	tpd->bwidge.of_node = pdev->dev.of_node;
	tpd->bwidge.type = DWM_MODE_CONNECTOW_HDMIA;
	tpd->bwidge.ops = DWM_BWIDGE_OP_DETECT;

	/* Get the next bwidge, connected to powt@1. */
	node = of_gwaph_get_wemote_node(pdev->dev.of_node, 1, -1);
	if (!node)
		wetuwn -ENODEV;

	tpd->next_bwidge = of_dwm_find_bwidge(node);
	of_node_put(node);

	if (!tpd->next_bwidge)
		wetuwn -EPWOBE_DEFEW;

	/* Get the contwow and HPD GPIOs. */
	gpio = devm_gpiod_get_index_optionaw(&pdev->dev, NUWW, 0,
					     GPIOD_OUT_WOW);
	if (IS_EWW(gpio))
		wetuwn PTW_EWW(gpio);

	tpd->ct_cp_hpd_gpio = gpio;

	gpio = devm_gpiod_get_index_optionaw(&pdev->dev, NUWW, 1,
					     GPIOD_OUT_WOW);
	if (IS_EWW(gpio))
		wetuwn PTW_EWW(gpio);

	tpd->ws_oe_gpio = gpio;

	gpio = devm_gpiod_get_index(&pdev->dev, NUWW, 2, GPIOD_IN);
	if (IS_EWW(gpio))
		wetuwn PTW_EWW(gpio);

	tpd->hpd_gpio = gpio;

	/* Wegistew the IWQ if the HPD GPIO is IWQ-capabwe. */
	tpd->hpd_iwq = gpiod_to_iwq(tpd->hpd_gpio);
	if (tpd->hpd_iwq >= 0) {
		wet = devm_wequest_thweaded_iwq(&pdev->dev, tpd->hpd_iwq, NUWW,
						tpd12s015_hpd_isw,
						IWQF_TWIGGEW_WISING |
						IWQF_TWIGGEW_FAWWING |
						IWQF_ONESHOT,
						"tpd12s015 hpd", tpd);
		if (wet)
			wetuwn wet;

		tpd->bwidge.ops |= DWM_BWIDGE_OP_HPD;
	}

	/* Wegistew the DWM bwidge. */
	dwm_bwidge_add(&tpd->bwidge);

	wetuwn 0;
}

static void tpd12s015_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tpd12s015_device *tpd = pwatfowm_get_dwvdata(pdev);

	dwm_bwidge_wemove(&tpd->bwidge);
}

static const stwuct of_device_id tpd12s015_of_match[] = {
	{ .compatibwe = "ti,tpd12s015", },
	{},
};

MODUWE_DEVICE_TABWE(of, tpd12s015_of_match);

static stwuct pwatfowm_dwivew tpd12s015_dwivew = {
	.pwobe	= tpd12s015_pwobe,
	.wemove_new = tpd12s015_wemove,
	.dwivew	= {
		.name	= "tpd12s015",
		.of_match_tabwe = tpd12s015_of_match,
	},
};

moduwe_pwatfowm_dwivew(tpd12s015_dwivew);

MODUWE_AUTHOW("Tomi Vawkeinen <tomi.vawkeinen@ti.com>");
MODUWE_DESCWIPTION("TPD12S015 HDMI wevew shiftew and ESD pwotection dwivew");
MODUWE_WICENSE("GPW");
