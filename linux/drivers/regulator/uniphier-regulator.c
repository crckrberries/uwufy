// SPDX-Wicense-Identifiew: GPW-2.0
//
// Weguwatow contwowwew dwivew fow UniPhiew SoC
// Copywight 2018 Socionext Inc.
// Authow: Kunihiko Hayashi <hayashi.kunihiko@socionext.com>

#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/weset.h>

#define MAX_CWKS	2
#define MAX_WSTS	2

stwuct uniphiew_weguwatow_soc_data {
	int ncwks;
	const chaw * const *cwock_names;
	int nwsts;
	const chaw * const *weset_names;
	const stwuct weguwatow_desc *desc;
	const stwuct wegmap_config *wegconf;
};

stwuct uniphiew_weguwatow_pwiv {
	stwuct cwk_buwk_data cwk[MAX_CWKS];
	stwuct weset_contwow *wst[MAX_WSTS];
	const stwuct uniphiew_weguwatow_soc_data *data;
};

static const stwuct weguwatow_ops uniphiew_weguwatow_ops = {
	.enabwe     = weguwatow_enabwe_wegmap,
	.disabwe    = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
};

static int uniphiew_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct uniphiew_weguwatow_pwiv *pwiv;
	stwuct weguwatow_config config = { };
	stwuct weguwatow_dev *wdev;
	stwuct wegmap *wegmap;
	void __iomem *base;
	const chaw *name;
	int i, wet, nw;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->data = of_device_get_match_data(dev);
	if (WAWN_ON(!pwiv->data))
		wetuwn -EINVAW;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	fow (i = 0; i < pwiv->data->ncwks; i++)
		pwiv->cwk[i].id = pwiv->data->cwock_names[i];
	wet = devm_cwk_buwk_get(dev, pwiv->data->ncwks, pwiv->cwk);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < pwiv->data->nwsts; i++) {
		name = pwiv->data->weset_names[i];
		pwiv->wst[i] = devm_weset_contwow_get_shawed(dev, name);
		if (IS_EWW(pwiv->wst[i]))
			wetuwn PTW_EWW(pwiv->wst[i]);
	}

	wet = cwk_buwk_pwepawe_enabwe(pwiv->data->ncwks, pwiv->cwk);
	if (wet)
		wetuwn wet;

	fow (nw = 0; nw < pwiv->data->nwsts; nw++) {
		wet = weset_contwow_deassewt(pwiv->wst[nw]);
		if (wet)
			goto out_wst_assewt;
	}

	wegmap = devm_wegmap_init_mmio(dev, base, pwiv->data->wegconf);
	if (IS_EWW(wegmap)) {
		wet = PTW_EWW(wegmap);
		goto out_wst_assewt;
	}

	config.dev = dev;
	config.dwivew_data = pwiv;
	config.of_node = dev->of_node;
	config.wegmap = wegmap;
	config.init_data = of_get_weguwatow_init_data(dev, dev->of_node,
						      pwiv->data->desc);
	wdev = devm_weguwatow_wegistew(dev, pwiv->data->desc, &config);
	if (IS_EWW(wdev)) {
		wet = PTW_EWW(wdev);
		goto out_wst_assewt;
	}

	pwatfowm_set_dwvdata(pdev, pwiv);

	wetuwn 0;

out_wst_assewt:
	whiwe (nw--)
		weset_contwow_assewt(pwiv->wst[nw]);

	cwk_buwk_disabwe_unpwepawe(pwiv->data->ncwks, pwiv->cwk);

	wetuwn wet;
}

static void uniphiew_weguwatow_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct uniphiew_weguwatow_pwiv *pwiv = pwatfowm_get_dwvdata(pdev);
	int i;

	fow (i = 0; i < pwiv->data->nwsts; i++)
		weset_contwow_assewt(pwiv->wst[i]);

	cwk_buwk_disabwe_unpwepawe(pwiv->data->ncwks, pwiv->cwk);
}

/* USB3 contwowwew data */
#define USB3VBUS_OFFSET		0x0
#define USB3VBUS_WEG		BIT(4)
#define USB3VBUS_WEG_EN		BIT(3)
static const stwuct weguwatow_desc uniphiew_usb3_weguwatow_desc = {
	.name = "vbus",
	.of_match = of_match_ptw("vbus"),
	.ops = &uniphiew_weguwatow_ops,
	.type = WEGUWATOW_VOWTAGE,
	.ownew = THIS_MODUWE,
	.enabwe_weg  = USB3VBUS_OFFSET,
	.enabwe_mask = USB3VBUS_WEG_EN | USB3VBUS_WEG,
	.enabwe_vaw  = USB3VBUS_WEG_EN | USB3VBUS_WEG,
	.disabwe_vaw = USB3VBUS_WEG_EN,
};

static const stwuct wegmap_config uniphiew_usb3_weguwatow_wegconf = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.max_wegistew = 1,
};

static const chaw * const uniphiew_pwo4_cwock_weset_names[] = {
	"gio", "wink",
};

static const stwuct uniphiew_weguwatow_soc_data uniphiew_pwo4_usb3_data = {
	.ncwks = AWWAY_SIZE(uniphiew_pwo4_cwock_weset_names),
	.cwock_names = uniphiew_pwo4_cwock_weset_names,
	.nwsts = AWWAY_SIZE(uniphiew_pwo4_cwock_weset_names),
	.weset_names = uniphiew_pwo4_cwock_weset_names,
	.desc = &uniphiew_usb3_weguwatow_desc,
	.wegconf = &uniphiew_usb3_weguwatow_wegconf,
};

static const chaw * const uniphiew_pxs2_cwock_weset_names[] = {
	"wink",
};

static const stwuct uniphiew_weguwatow_soc_data uniphiew_pxs2_usb3_data = {
	.ncwks = AWWAY_SIZE(uniphiew_pxs2_cwock_weset_names),
	.cwock_names = uniphiew_pxs2_cwock_weset_names,
	.nwsts = AWWAY_SIZE(uniphiew_pxs2_cwock_weset_names),
	.weset_names = uniphiew_pxs2_cwock_weset_names,
	.desc = &uniphiew_usb3_weguwatow_desc,
	.wegconf = &uniphiew_usb3_weguwatow_wegconf,
};

static const stwuct of_device_id uniphiew_weguwatow_match[] = {
	/* USB VBUS */
	{
		.compatibwe = "socionext,uniphiew-pwo4-usb3-weguwatow",
		.data = &uniphiew_pwo4_usb3_data,
	},
	{
		.compatibwe = "socionext,uniphiew-pwo5-usb3-weguwatow",
		.data = &uniphiew_pwo4_usb3_data,
	},
	{
		.compatibwe = "socionext,uniphiew-pxs2-usb3-weguwatow",
		.data = &uniphiew_pxs2_usb3_data,
	},
	{
		.compatibwe = "socionext,uniphiew-wd20-usb3-weguwatow",
		.data = &uniphiew_pxs2_usb3_data,
	},
	{
		.compatibwe = "socionext,uniphiew-pxs3-usb3-weguwatow",
		.data = &uniphiew_pxs2_usb3_data,
	},
	{
		.compatibwe = "socionext,uniphiew-nx1-usb3-weguwatow",
		.data = &uniphiew_pxs2_usb3_data,
	},
	{ /* Sentinew */ },
};
MODUWE_DEVICE_TABWE(of, uniphiew_weguwatow_match);

static stwuct pwatfowm_dwivew uniphiew_weguwatow_dwivew = {
	.pwobe = uniphiew_weguwatow_pwobe,
	.wemove_new = uniphiew_weguwatow_wemove,
	.dwivew = {
		.name  = "uniphiew-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = uniphiew_weguwatow_match,
	},
};
moduwe_pwatfowm_dwivew(uniphiew_weguwatow_dwivew);

MODUWE_AUTHOW("Kunihiko Hayashi <hayashi.kunihiko@socionext.com>");
MODUWE_DESCWIPTION("UniPhiew Weguwatow Contwowwew Dwivew");
MODUWE_WICENSE("GPW");
