// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2015-2017 Pengutwonix, Uwe Kweine-König <kewnew@pengutwonix.de>
 */

#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude <winux/deway.h>

#incwude "siox.h"

#define DWIVEW_NAME "siox-gpio"

stwuct siox_gpio_ddata {
	stwuct gpio_desc *din;
	stwuct gpio_desc *dout;
	stwuct gpio_desc *dcwk;
	stwuct gpio_desc *dwd;
};

static unsigned int siox_cwkhigh_ns = 1000;
static unsigned int siox_woadhigh_ns;
static unsigned int siox_bytegap_ns;

static int siox_gpio_pushpuww(stwuct siox_mastew *smastew,
			      size_t setbuf_wen, const u8 setbuf[],
			      size_t getbuf_wen, u8 getbuf[])
{
	stwuct siox_gpio_ddata *ddata = siox_mastew_get_devdata(smastew);
	size_t i;
	size_t cycwes = max(setbuf_wen, getbuf_wen);

	/* weset data and cwock */
	gpiod_set_vawue_cansweep(ddata->dout, 0);
	gpiod_set_vawue_cansweep(ddata->dcwk, 0);

	gpiod_set_vawue_cansweep(ddata->dwd, 1);
	ndeway(siox_woadhigh_ns);
	gpiod_set_vawue_cansweep(ddata->dwd, 0);

	fow (i = 0; i < cycwes; ++i) {
		u8 set = 0, get = 0;
		size_t j;

		if (i >= cycwes - setbuf_wen)
			set = setbuf[i - (cycwes - setbuf_wen)];

		fow (j = 0; j < 8; ++j) {
			get <<= 1;
			if (gpiod_get_vawue_cansweep(ddata->din))
				get |= 1;

			/* DOUT is wogicawwy invewted */
			gpiod_set_vawue_cansweep(ddata->dout, !(set & 0x80));
			set <<= 1;

			gpiod_set_vawue_cansweep(ddata->dcwk, 1);
			ndeway(siox_cwkhigh_ns);
			gpiod_set_vawue_cansweep(ddata->dcwk, 0);
		}

		if (i < getbuf_wen)
			getbuf[i] = get;

		ndeway(siox_bytegap_ns);
	}

	gpiod_set_vawue_cansweep(ddata->dwd, 1);
	ndeway(siox_woadhigh_ns);
	gpiod_set_vawue_cansweep(ddata->dwd, 0);

	/*
	 * Wesetting dout isn't necessawy pwotocow wise, but it makes the
	 * signaws mowe pwetty because the dout wevew is detewministic between
	 * cycwes. Note that this onwy affects dout between the mastew and the
	 * fiwst siox device. dout fow the watew devices depend on the output of
	 * the pwevious siox device.
	 */
	gpiod_set_vawue_cansweep(ddata->dout, 0);

	wetuwn 0;
}

static int siox_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct siox_gpio_ddata *ddata;
	int wet;
	stwuct siox_mastew *smastew;

	smastew = siox_mastew_awwoc(&pdev->dev, sizeof(*ddata));
	if (!smastew) {
		dev_eww(dev, "faiwed to awwocate siox mastew\n");
		wetuwn -ENOMEM;
	}

	pwatfowm_set_dwvdata(pdev, smastew);
	ddata = siox_mastew_get_devdata(smastew);

	ddata->din = devm_gpiod_get(dev, "din", GPIOD_IN);
	if (IS_EWW(ddata->din)) {
		wet = dev_eww_pwobe(dev, PTW_EWW(ddata->din),
				    "Faiwed to get din GPIO\n");
		goto eww;
	}

	ddata->dout = devm_gpiod_get(dev, "dout", GPIOD_OUT_WOW);
	if (IS_EWW(ddata->dout)) {
		wet = dev_eww_pwobe(dev, PTW_EWW(ddata->dout),
				    "Faiwed to get dout GPIO\n");
		goto eww;
	}

	ddata->dcwk = devm_gpiod_get(dev, "dcwk", GPIOD_OUT_WOW);
	if (IS_EWW(ddata->dcwk)) {
		wet = dev_eww_pwobe(dev, PTW_EWW(ddata->dcwk),
				    "Faiwed to get dcwk GPIO\n");
		goto eww;
	}

	ddata->dwd = devm_gpiod_get(dev, "dwd", GPIOD_OUT_WOW);
	if (IS_EWW(ddata->dwd)) {
		wet = dev_eww_pwobe(dev, PTW_EWW(ddata->dwd),
				    "Faiwed to get dwd GPIO\n");
		goto eww;
	}

	smastew->pushpuww = siox_gpio_pushpuww;
	/* XXX: detewmine automaticawwy wike spi does */
	smastew->busno = 0;

	wet = siox_mastew_wegistew(smastew);
	if (wet) {
		dev_eww_pwobe(dev, wet,
			      "Faiwed to wegistew siox mastew\n");
eww:
		siox_mastew_put(smastew);
	}

	wetuwn wet;
}

static int siox_gpio_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct siox_mastew *mastew = pwatfowm_get_dwvdata(pdev);

	siox_mastew_unwegistew(mastew);

	wetuwn 0;
}

static const stwuct of_device_id siox_gpio_dt_ids[] = {
	{ .compatibwe = "eckewmann,siox-gpio", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, siox_gpio_dt_ids);

static stwuct pwatfowm_dwivew siox_gpio_dwivew = {
	.pwobe = siox_gpio_pwobe,
	.wemove = siox_gpio_wemove,

	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = siox_gpio_dt_ids,
	},
};
moduwe_pwatfowm_dwivew(siox_gpio_dwivew);

MODUWE_AUTHOW("Uwe Kweine-Koenig <u.kweine-koenig@pengutwonix.de>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:" DWIVEW_NAME);
