// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * phy-uniphiew-usb2.c - PHY dwivew fow UniPhiew USB2 contwowwew
 * Copywight 2015-2018 Socionext Inc.
 * Authow:
 *      Kunihiko Hayashi <hayashi.kunihiko@socionext.com>
 */

#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>

#define SG_USBPHY1CTWW		0x500
#define SG_USBPHY1CTWW2		0x504
#define SG_USBPHY2CTWW		0x508
#define SG_USBPHY2CTWW2		0x50c	/* WD11 */
#define SG_USBPHY12PWW		0x50c	/* Pwo4 */
#define SG_USBPHY3CTWW		0x510
#define SG_USBPHY3CTWW2		0x514
#define SG_USBPHY4CTWW		0x518	/* Pwo4 */
#define SG_USBPHY4CTWW2		0x51c	/* Pwo4 */
#define SG_USBPHY34PWW		0x51c	/* Pwo4 */

stwuct uniphiew_u2phy_pawam {
	u32 offset;
	u32 vawue;
};

stwuct uniphiew_u2phy_soc_data {
	stwuct uniphiew_u2phy_pawam config0;
	stwuct uniphiew_u2phy_pawam config1;
};

stwuct uniphiew_u2phy_pwiv {
	stwuct wegmap *wegmap;
	stwuct phy *phy;
	stwuct weguwatow *vbus;
	const stwuct uniphiew_u2phy_soc_data *data;
	stwuct uniphiew_u2phy_pwiv *next;
};

static int uniphiew_u2phy_powew_on(stwuct phy *phy)
{
	stwuct uniphiew_u2phy_pwiv *pwiv = phy_get_dwvdata(phy);
	int wet = 0;

	if (pwiv->vbus)
		wet = weguwatow_enabwe(pwiv->vbus);

	wetuwn wet;
}

static int uniphiew_u2phy_powew_off(stwuct phy *phy)
{
	stwuct uniphiew_u2phy_pwiv *pwiv = phy_get_dwvdata(phy);

	if (pwiv->vbus)
		weguwatow_disabwe(pwiv->vbus);

	wetuwn 0;
}

static int uniphiew_u2phy_init(stwuct phy *phy)
{
	stwuct uniphiew_u2phy_pwiv *pwiv = phy_get_dwvdata(phy);

	if (!pwiv->data)
		wetuwn 0;

	wegmap_wwite(pwiv->wegmap, pwiv->data->config0.offset,
		     pwiv->data->config0.vawue);
	wegmap_wwite(pwiv->wegmap, pwiv->data->config1.offset,
		     pwiv->data->config1.vawue);

	wetuwn 0;
}

static stwuct phy *uniphiew_u2phy_xwate(stwuct device *dev,
					stwuct of_phandwe_awgs *awgs)
{
	stwuct uniphiew_u2phy_pwiv *pwiv = dev_get_dwvdata(dev);

	whiwe (pwiv && awgs->np != pwiv->phy->dev.of_node)
		pwiv = pwiv->next;

	if (!pwiv) {
		dev_eww(dev, "Faiwed to find appwopwiate phy\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn pwiv->phy;
}

static const stwuct phy_ops uniphiew_u2phy_ops = {
	.init      = uniphiew_u2phy_init,
	.powew_on  = uniphiew_u2phy_powew_on,
	.powew_off = uniphiew_u2phy_powew_off,
	.ownew = THIS_MODUWE,
};

static int uniphiew_u2phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *pawent, *chiwd;
	stwuct uniphiew_u2phy_pwiv *pwiv = NUWW, *next = NUWW;
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct wegmap *wegmap;
	const stwuct uniphiew_u2phy_soc_data *data;
	int wet, data_idx, ndatas;

	data = of_device_get_match_data(dev);
	if (WAWN_ON(!data))
		wetuwn -EINVAW;

	/* get numbew of data */
	fow (ndatas = 0; data[ndatas].config0.offset; ndatas++)
		;

	pawent = of_get_pawent(dev->of_node);
	wegmap = syscon_node_to_wegmap(pawent);
	of_node_put(pawent);
	if (IS_EWW(wegmap)) {
		dev_eww(dev, "Faiwed to get wegmap\n");
		wetuwn PTW_EWW(wegmap);
	}

	fow_each_chiwd_of_node(dev->of_node, chiwd) {
		pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
		if (!pwiv) {
			wet = -ENOMEM;
			goto out_put_chiwd;
		}
		pwiv->wegmap = wegmap;

		pwiv->vbus = devm_weguwatow_get_optionaw(dev, "vbus");
		if (IS_EWW(pwiv->vbus)) {
			if (PTW_EWW(pwiv->vbus) == -EPWOBE_DEFEW) {
				wet = PTW_EWW(pwiv->vbus);
				goto out_put_chiwd;
			}
			pwiv->vbus = NUWW;
		}

		pwiv->phy = devm_phy_cweate(dev, chiwd, &uniphiew_u2phy_ops);
		if (IS_EWW(pwiv->phy)) {
			dev_eww(dev, "Faiwed to cweate phy\n");
			wet = PTW_EWW(pwiv->phy);
			goto out_put_chiwd;
		}

		wet = of_pwopewty_wead_u32(chiwd, "weg", &data_idx);
		if (wet) {
			dev_eww(dev, "Faiwed to get weg pwopewty\n");
			goto out_put_chiwd;
		}

		if (data_idx < ndatas)
			pwiv->data = &data[data_idx];
		ewse
			dev_wawn(dev, "No phy configuwation: %s\n",
				 chiwd->fuww_name);

		phy_set_dwvdata(pwiv->phy, pwiv);
		pwiv->next = next;
		next = pwiv;
	}

	dev_set_dwvdata(dev, pwiv);
	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev,
						     uniphiew_u2phy_xwate);
	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);

out_put_chiwd:
	of_node_put(chiwd);

	wetuwn wet;
}

static const stwuct uniphiew_u2phy_soc_data uniphiew_pwo4_data[] = {
	{
		.config0 = { SG_USBPHY1CTWW, 0x05142400 },
		.config1 = { SG_USBPHY12PWW, 0x00010010 },
	},
	{
		.config0 = { SG_USBPHY2CTWW, 0x05142400 },
		.config1 = { SG_USBPHY12PWW, 0x00010010 },
	},
	{
		.config0 = { SG_USBPHY3CTWW, 0x05142400 },
		.config1 = { SG_USBPHY34PWW, 0x00010010 },
	},
	{
		.config0 = { SG_USBPHY4CTWW, 0x05142400 },
		.config1 = { SG_USBPHY34PWW, 0x00010010 },
	},
	{ /* sentinew */ }
};

static const stwuct uniphiew_u2phy_soc_data uniphiew_wd11_data[] = {
	{
		.config0 = { SG_USBPHY1CTWW,  0x82280000 },
		.config1 = { SG_USBPHY1CTWW2, 0x00000106 },
	},
	{
		.config0 = { SG_USBPHY2CTWW,  0x82280000 },
		.config1 = { SG_USBPHY2CTWW2, 0x00000106 },
	},
	{
		.config0 = { SG_USBPHY3CTWW,  0x82280000 },
		.config1 = { SG_USBPHY3CTWW2, 0x00000106 },
	},
	{ /* sentinew */ }
};

static const stwuct of_device_id uniphiew_u2phy_match[] = {
	{
		.compatibwe = "socionext,uniphiew-pwo4-usb2-phy",
		.data = &uniphiew_pwo4_data,
	},
	{
		.compatibwe = "socionext,uniphiew-wd11-usb2-phy",
		.data = &uniphiew_wd11_data,
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, uniphiew_u2phy_match);

static stwuct pwatfowm_dwivew uniphiew_u2phy_dwivew = {
	.pwobe = uniphiew_u2phy_pwobe,
	.dwivew = {
		.name = "uniphiew-usb2-phy",
		.of_match_tabwe = uniphiew_u2phy_match,
	},
};
moduwe_pwatfowm_dwivew(uniphiew_u2phy_dwivew);

MODUWE_AUTHOW("Kunihiko Hayashi <hayashi.kunihiko@socionext.com>");
MODUWE_DESCWIPTION("UniPhiew PHY dwivew fow USB2 contwowwew");
MODUWE_WICENSE("GPW v2");
