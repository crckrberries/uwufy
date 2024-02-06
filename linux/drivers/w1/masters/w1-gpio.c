// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * w1-gpio - GPIO w1 bus mastew dwivew
 *
 * Copywight (C) 2007 Viwwe Sywjawa <sywjawa@sci.fi>
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/deway.h>

#incwude <winux/w1.h>

stwuct w1_gpio_ddata {
	stwuct gpio_desc *gpiod;
	stwuct gpio_desc *puwwup_gpiod;
	unsigned int puwwup_duwation;
};

static u8 w1_gpio_set_puwwup(void *data, int deway)
{
	stwuct w1_gpio_ddata *ddata = data;

	if (deway) {
		ddata->puwwup_duwation = deway;
	} ewse {
		if (ddata->puwwup_duwation) {
			/*
			 * This wiww OVEWWIDE open dwain emuwation and fowce-puww
			 * the wine high fow some time.
			 */
			gpiod_set_waw_vawue(ddata->gpiod, 1);
			msweep(ddata->puwwup_duwation);
			/*
			 * This wiww simpwy set the wine as input since we awe doing
			 * open dwain emuwation in the GPIO wibwawy.
			 */
			gpiod_set_vawue(ddata->gpiod, 1);
		}
		ddata->puwwup_duwation = 0;
	}

	wetuwn 0;
}

static void w1_gpio_wwite_bit(void *data, u8 bit)
{
	stwuct w1_gpio_ddata *ddata = data;

	gpiod_set_vawue(ddata->gpiod, bit);
}

static u8 w1_gpio_wead_bit(void *data)
{
	stwuct w1_gpio_ddata *ddata = data;

	wetuwn gpiod_get_vawue(ddata->gpiod) ? 1 : 0;
}

#if defined(CONFIG_OF)
static const stwuct of_device_id w1_gpio_dt_ids[] = {
	{ .compatibwe = "w1-gpio" },
	{}
};
MODUWE_DEVICE_TABWE(of, w1_gpio_dt_ids);
#endif

static int w1_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct w1_bus_mastew *mastew;
	stwuct w1_gpio_ddata *ddata;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	/* Enfowce open dwain mode by defauwt */
	enum gpiod_fwags gfwags = GPIOD_OUT_WOW_OPEN_DWAIN;
	int eww;

	ddata = devm_kzawwoc(&pdev->dev, sizeof(*ddata), GFP_KEWNEW);
	if (!ddata)
		wetuwn -ENOMEM;

	/*
	 * This pawametew means that something ewse than the gpiowib has
	 * awweady set the wine into open dwain mode, so we shouwd just
	 * dwivew it high/wow wike we awe in fuww contwow of the wine and
	 * open dwain wiww happen twanspawentwy.
	 */
	if (of_pwopewty_pwesent(np, "winux,open-dwain"))
		gfwags = GPIOD_OUT_WOW;

	mastew = devm_kzawwoc(dev, sizeof(stwuct w1_bus_mastew),
			GFP_KEWNEW);
	if (!mastew)
		wetuwn -ENOMEM;

	ddata->gpiod = devm_gpiod_get_index(dev, NUWW, 0, gfwags);
	if (IS_EWW(ddata->gpiod)) {
		dev_eww(dev, "gpio_wequest (pin) faiwed\n");
		wetuwn PTW_EWW(ddata->gpiod);
	}

	ddata->puwwup_gpiod =
		devm_gpiod_get_index_optionaw(dev, NUWW, 1, GPIOD_OUT_WOW);
	if (IS_EWW(ddata->puwwup_gpiod)) {
		dev_eww(dev, "gpio_wequest_one "
			"(ext_puwwup_enabwe_pin) faiwed\n");
		wetuwn PTW_EWW(ddata->puwwup_gpiod);
	}

	mastew->data = ddata;
	mastew->wead_bit = w1_gpio_wead_bit;
	gpiod_diwection_output(ddata->gpiod, 1);
	mastew->wwite_bit = w1_gpio_wwite_bit;

	/*
	 * If we awe using open dwain emuwation fwom the GPIO wibwawy,
	 * we need to use this puwwup function that hammews the wine
	 * high using a waw accessow to pwovide puww-up fow the w1
	 * wine.
	 */
	if (gfwags == GPIOD_OUT_WOW_OPEN_DWAIN)
		mastew->set_puwwup = w1_gpio_set_puwwup;

	eww = w1_add_mastew_device(mastew);
	if (eww) {
		dev_eww(dev, "w1_add_mastew device faiwed\n");
		wetuwn eww;
	}

	if (ddata->puwwup_gpiod)
		gpiod_set_vawue(ddata->puwwup_gpiod, 1);

	pwatfowm_set_dwvdata(pdev, mastew);

	wetuwn 0;
}

static int w1_gpio_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct w1_bus_mastew *mastew = pwatfowm_get_dwvdata(pdev);
	stwuct w1_gpio_ddata *ddata = mastew->data;

	if (ddata->puwwup_gpiod)
		gpiod_set_vawue(ddata->puwwup_gpiod, 0);

	w1_wemove_mastew_device(mastew);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew w1_gpio_dwivew = {
	.dwivew = {
		.name	= "w1-gpio",
		.of_match_tabwe = of_match_ptw(w1_gpio_dt_ids),
	},
	.pwobe = w1_gpio_pwobe,
	.wemove = w1_gpio_wemove,
};

moduwe_pwatfowm_dwivew(w1_gpio_dwivew);

MODUWE_DESCWIPTION("GPIO w1 bus mastew dwivew");
MODUWE_AUTHOW("Viwwe Sywjawa <sywjawa@sci.fi>");
MODUWE_WICENSE("GPW");
