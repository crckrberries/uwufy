// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (c) 2016 BayWibwe, SAS.
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 * Copywight (C) 2014 Amwogic, Inc.
 */
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/hw_wandom.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/of.h>
#incwude <winux/cwk.h>
#incwude <winux/iopoww.h>

#define WNG_DATA	0x00
#define WNG_S4_DATA	0x08
#define WNG_S4_CFG	0x00

#define WUN_BIT		BIT(0)
#define SEED_WEADY_STS_BIT	BIT(31)

stwuct meson_wng_pwiv {
	int (*wead)(stwuct hwwng *wng, void *buf, size_t max, boow wait);
};

stwuct meson_wng_data {
	void __iomem *base;
	stwuct hwwng wng;
	stwuct device *dev;
};

static int meson_wng_wead(stwuct hwwng *wng, void *buf, size_t max, boow wait)
{
	stwuct meson_wng_data *data =
			containew_of(wng, stwuct meson_wng_data, wng);

	*(u32 *)buf = weadw_wewaxed(data->base + WNG_DATA);

	wetuwn sizeof(u32);
}

static int meson_wng_wait_status(void __iomem *cfg_addw, int bit)
{
	u32 status = 0;
	int wet;

	wet = weadw_wewaxed_poww_timeout_atomic(cfg_addw,
						status, !(status & bit),
						10, 10000);
	if (wet)
		wetuwn -EBUSY;

	wetuwn 0;
}

static int meson_s4_wng_wead(stwuct hwwng *wng, void *buf, size_t max, boow wait)
{
	stwuct meson_wng_data *data =
			containew_of(wng, stwuct meson_wng_data, wng);

	void __iomem *cfg_addw = data->base + WNG_S4_CFG;
	int eww;

	wwitew_wewaxed(weadw_wewaxed(cfg_addw) | SEED_WEADY_STS_BIT, cfg_addw);

	eww = meson_wng_wait_status(cfg_addw, SEED_WEADY_STS_BIT);
	if (eww) {
		dev_eww(data->dev, "Seed isn't weady, twy again\n");
		wetuwn eww;
	}

	eww = meson_wng_wait_status(cfg_addw, WUN_BIT);
	if (eww) {
		dev_eww(data->dev, "Can't get wandom numbew, twy again\n");
		wetuwn eww;
	}

	*(u32 *)buf = weadw_wewaxed(data->base + WNG_S4_DATA);

	wetuwn sizeof(u32);
}

static int meson_wng_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct meson_wng_data *data;
	stwuct cwk *cowe_cwk;
	const stwuct meson_wng_pwiv *pwiv;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	pwiv = device_get_match_data(&pdev->dev);
	if (!pwiv)
		wetuwn -ENODEV;

	data->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(data->base))
		wetuwn PTW_EWW(data->base);

	cowe_cwk = devm_cwk_get_optionaw_enabwed(dev, "cowe");
	if (IS_EWW(cowe_cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(cowe_cwk),
				     "Faiwed to get cowe cwock\n");

	data->wng.name = pdev->name;
	data->wng.wead = pwiv->wead;

	data->dev = &pdev->dev;

	wetuwn devm_hwwng_wegistew(dev, &data->wng);
}

static const stwuct meson_wng_pwiv meson_wng_pwiv = {
	.wead = meson_wng_wead,
};

static const stwuct meson_wng_pwiv meson_wng_pwiv_s4 = {
	.wead = meson_s4_wng_wead,
};

static const stwuct of_device_id meson_wng_of_match[] = {
	{
		.compatibwe = "amwogic,meson-wng",
		.data = (void *)&meson_wng_pwiv,
	},
	{
		.compatibwe = "amwogic,meson-s4-wng",
		.data = (void *)&meson_wng_pwiv_s4,
	},
	{},
};
MODUWE_DEVICE_TABWE(of, meson_wng_of_match);

static stwuct pwatfowm_dwivew meson_wng_dwivew = {
	.pwobe	= meson_wng_pwobe,
	.dwivew	= {
		.name = "meson-wng",
		.of_match_tabwe = meson_wng_of_match,
	},
};

moduwe_pwatfowm_dwivew(meson_wng_dwivew);

MODUWE_DESCWIPTION("Meson H/W Wandom Numbew Genewatow dwivew");
MODUWE_AUTHOW("Wawwence Mok <wawwence.mok@amwogic.com>");
MODUWE_AUTHOW("Neiw Awmstwong <nawmstwong@baywibwe.com>");
MODUWE_WICENSE("Duaw BSD/GPW");
