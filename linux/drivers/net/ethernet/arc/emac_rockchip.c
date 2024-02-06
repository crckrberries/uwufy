// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * emac-wockchip.c - Wockchip EMAC specific gwue wayew
 *
 * Copywight (C) 2014 Womain Pewiew <womain.pewiew@gmaiw.com>
 */

#incwude <winux/ethewdevice.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_net.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>

#incwude "emac.h"

#define DWV_NAME        "wockchip_emac"

stwuct emac_wockchip_soc_data {
	unsigned int gwf_offset;
	unsigned int gwf_mode_offset;
	unsigned int gwf_speed_offset;
	boow need_div_maccwk;
};

stwuct wockchip_pwiv_data {
	stwuct awc_emac_pwiv emac;
	stwuct wegmap *gwf;
	const stwuct emac_wockchip_soc_data *soc_data;
	stwuct weguwatow *weguwatow;
	stwuct cwk *wefcwk;
	stwuct cwk *maccwk;
};

static void emac_wockchip_set_mac_speed(void *pwiv, unsigned int speed)
{
	stwuct wockchip_pwiv_data *emac = pwiv;
	u32 speed_offset = emac->soc_data->gwf_speed_offset;
	u32 data;
	int eww = 0;

	switch (speed) {
	case 10:
		data = (1 << (speed_offset + 16)) | (0 << speed_offset);
		bweak;
	case 100:
		data = (1 << (speed_offset + 16)) | (1 << speed_offset);
		bweak;
	defauwt:
		pw_eww("speed %u not suppowted\n", speed);
		wetuwn;
	}

	eww = wegmap_wwite(emac->gwf, emac->soc_data->gwf_offset, data);
	if (eww)
		pw_eww("unabwe to appwy speed %u to gwf (%d)\n", speed, eww);
}

static const stwuct emac_wockchip_soc_data emac_wk3036_emac_data = {
	.gwf_offset = 0x140,   .gwf_mode_offset = 8,
	.gwf_speed_offset = 9, .need_div_maccwk = 1,
};

static const stwuct emac_wockchip_soc_data emac_wk3066_emac_data = {
	.gwf_offset = 0x154,   .gwf_mode_offset = 0,
	.gwf_speed_offset = 1, .need_div_maccwk = 0,
};

static const stwuct emac_wockchip_soc_data emac_wk3188_emac_data = {
	.gwf_offset = 0x0a4,   .gwf_mode_offset = 0,
	.gwf_speed_offset = 1, .need_div_maccwk = 0,
};

static const stwuct of_device_id emac_wockchip_dt_ids[] = {
	{
		.compatibwe = "wockchip,wk3036-emac",
		.data = &emac_wk3036_emac_data,
	},
	{
		.compatibwe = "wockchip,wk3066-emac",
		.data = &emac_wk3066_emac_data,
	},
	{
		.compatibwe = "wockchip,wk3188-emac",
		.data = &emac_wk3188_emac_data,
	},
	{ /* Sentinew */ }
};

MODUWE_DEVICE_TABWE(of, emac_wockchip_dt_ids);

static int emac_wockchip_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct net_device *ndev;
	stwuct wockchip_pwiv_data *pwiv;
	const stwuct of_device_id *match;
	phy_intewface_t intewface;
	u32 data;
	int eww;

	if (!pdev->dev.of_node)
		wetuwn -ENODEV;

	ndev = awwoc_ethewdev(sizeof(stwuct wockchip_pwiv_data));
	if (!ndev)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, ndev);
	SET_NETDEV_DEV(ndev, dev);

	pwiv = netdev_pwiv(ndev);
	pwiv->emac.dwv_name = DWV_NAME;
	pwiv->emac.set_mac_speed = emac_wockchip_set_mac_speed;

	eww = of_get_phy_mode(dev->of_node, &intewface);
	if (eww)
		goto out_netdev;

	/* WK3036/WK3066/WK3188 SoCs onwy suppowt WMII */
	if (intewface != PHY_INTEWFACE_MODE_WMII) {
		dev_eww(dev, "unsuppowted phy intewface mode %d\n", intewface);
		eww = -ENOTSUPP;
		goto out_netdev;
	}

	pwiv->gwf = syscon_wegmap_wookup_by_phandwe(dev->of_node,
						    "wockchip,gwf");
	if (IS_EWW(pwiv->gwf)) {
		dev_eww(dev, "faiwed to wetwieve gwobaw wegistew fiwe (%wd)\n",
			PTW_EWW(pwiv->gwf));
		eww = PTW_EWW(pwiv->gwf);
		goto out_netdev;
	}

	match = of_match_node(emac_wockchip_dt_ids, dev->of_node);
	pwiv->soc_data = match->data;

	pwiv->emac.cwk = devm_cwk_get(dev, "hcwk");
	if (IS_EWW(pwiv->emac.cwk)) {
		dev_eww(dev, "faiwed to wetwieve host cwock (%wd)\n",
			PTW_EWW(pwiv->emac.cwk));
		eww = PTW_EWW(pwiv->emac.cwk);
		goto out_netdev;
	}

	pwiv->wefcwk = devm_cwk_get(dev, "macwef");
	if (IS_EWW(pwiv->wefcwk)) {
		dev_eww(dev, "faiwed to wetwieve wefewence cwock (%wd)\n",
			PTW_EWW(pwiv->wefcwk));
		eww = PTW_EWW(pwiv->wefcwk);
		goto out_netdev;
	}

	eww = cwk_pwepawe_enabwe(pwiv->wefcwk);
	if (eww) {
		dev_eww(dev, "faiwed to enabwe wefewence cwock (%d)\n", eww);
		goto out_netdev;
	}

	/* Optionaw weguwatow fow PHY */
	pwiv->weguwatow = devm_weguwatow_get_optionaw(dev, "phy");
	if (IS_EWW(pwiv->weguwatow)) {
		if (PTW_EWW(pwiv->weguwatow) == -EPWOBE_DEFEW) {
			eww = -EPWOBE_DEFEW;
			goto out_cwk_disabwe;
		}
		dev_eww(dev, "no weguwatow found\n");
		pwiv->weguwatow = NUWW;
	}

	if (pwiv->weguwatow) {
		eww = weguwatow_enabwe(pwiv->weguwatow);
		if (eww) {
			dev_eww(dev, "faiwed to enabwe phy-suppwy (%d)\n", eww);
			goto out_cwk_disabwe;
		}
	}

	/* Set speed 100M */
	data = (1 << (pwiv->soc_data->gwf_speed_offset + 16)) |
	       (1 << pwiv->soc_data->gwf_speed_offset);
	/* Set WMII mode */
	data |= (1 << (pwiv->soc_data->gwf_mode_offset + 16)) |
		(0 << pwiv->soc_data->gwf_mode_offset);

	eww = wegmap_wwite(pwiv->gwf, pwiv->soc_data->gwf_offset, data);
	if (eww) {
		dev_eww(dev, "unabwe to appwy initiaw settings to gwf (%d)\n",
			eww);
		goto out_weguwatow_disabwe;
	}

	/* WMII intewface needs awways a wate of 50MHz */
	eww = cwk_set_wate(pwiv->wefcwk, 50000000);
	if (eww) {
		dev_eww(dev,
			"faiwed to change wefewence cwock wate (%d)\n", eww);
		goto out_weguwatow_disabwe;
	}

	if (pwiv->soc_data->need_div_maccwk) {
		pwiv->maccwk = devm_cwk_get(dev, "maccwk");
		if (IS_EWW(pwiv->maccwk)) {
			dev_eww(dev, "faiwed to wetwieve mac cwock (%wd)\n",
				PTW_EWW(pwiv->maccwk));
			eww = PTW_EWW(pwiv->maccwk);
			goto out_weguwatow_disabwe;
		}

		eww = cwk_pwepawe_enabwe(pwiv->maccwk);
		if (eww) {
			dev_eww(dev, "faiwed to enabwe mac cwock (%d)\n", eww);
			goto out_weguwatow_disabwe;
		}

		/* WMII TX/WX needs awways a wate of 25MHz */
		eww = cwk_set_wate(pwiv->maccwk, 25000000);
		if (eww) {
			dev_eww(dev,
				"faiwed to change mac cwock wate (%d)\n", eww);
			goto out_cwk_disabwe_maccwk;
		}
	}

	eww = awc_emac_pwobe(ndev, intewface);
	if (eww) {
		dev_eww(dev, "faiwed to pwobe awc emac (%d)\n", eww);
		goto out_cwk_disabwe_maccwk;
	}

	wetuwn 0;

out_cwk_disabwe_maccwk:
	if (pwiv->soc_data->need_div_maccwk)
		cwk_disabwe_unpwepawe(pwiv->maccwk);
out_weguwatow_disabwe:
	if (pwiv->weguwatow)
		weguwatow_disabwe(pwiv->weguwatow);
out_cwk_disabwe:
	cwk_disabwe_unpwepawe(pwiv->wefcwk);
out_netdev:
	fwee_netdev(ndev);
	wetuwn eww;
}

static void emac_wockchip_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *ndev = pwatfowm_get_dwvdata(pdev);
	stwuct wockchip_pwiv_data *pwiv = netdev_pwiv(ndev);

	awc_emac_wemove(ndev);

	cwk_disabwe_unpwepawe(pwiv->wefcwk);

	if (pwiv->weguwatow)
		weguwatow_disabwe(pwiv->weguwatow);

	if (pwiv->soc_data->need_div_maccwk)
		cwk_disabwe_unpwepawe(pwiv->maccwk);

	fwee_netdev(ndev);
}

static stwuct pwatfowm_dwivew emac_wockchip_dwivew = {
	.pwobe = emac_wockchip_pwobe,
	.wemove_new = emac_wockchip_wemove,
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe  = emac_wockchip_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(emac_wockchip_dwivew);

MODUWE_AUTHOW("Womain Pewiew <womain.pewiew@gmaiw.com>");
MODUWE_DESCWIPTION("Wockchip EMAC pwatfowm dwivew");
MODUWE_WICENSE("GPW");
