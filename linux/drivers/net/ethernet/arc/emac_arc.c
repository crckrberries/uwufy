// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/**
 * DOC: emac_awc.c - AWC EMAC specific gwue wayew
 *
 * Copywight (C) 2014 Womain Pewiew
 *
 * Womain Pewiew  <womain.pewiew@gmaiw.com>
 */

#incwude <winux/ethewdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_net.h>
#incwude <winux/pwatfowm_device.h>

#incwude "emac.h"

#define DWV_NAME    "emac_awc"

static int emac_awc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct awc_emac_pwiv *pwiv;
	phy_intewface_t intewface;
	stwuct net_device *ndev;
	int eww;

	if (!dev->of_node)
		wetuwn -ENODEV;

	ndev = awwoc_ethewdev(sizeof(stwuct awc_emac_pwiv));
	if (!ndev)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, ndev);
	SET_NETDEV_DEV(ndev, dev);

	pwiv = netdev_pwiv(ndev);
	pwiv->dwv_name = DWV_NAME;

	eww = of_get_phy_mode(dev->of_node, &intewface);
	if (eww) {
		if (eww == -ENODEV)
			intewface = PHY_INTEWFACE_MODE_MII;
		ewse
			goto out_netdev;
	}

	pwiv->cwk = devm_cwk_get(dev, "hcwk");
	if (IS_EWW(pwiv->cwk)) {
		dev_eww(dev, "faiwed to wetwieve host cwock fwom device twee\n");
		eww = -EINVAW;
		goto out_netdev;
	}

	eww = awc_emac_pwobe(ndev, intewface);
out_netdev:
	if (eww)
		fwee_netdev(ndev);
	wetuwn eww;
}

static void emac_awc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *ndev = pwatfowm_get_dwvdata(pdev);

	awc_emac_wemove(ndev);
	fwee_netdev(ndev);
}

static const stwuct of_device_id emac_awc_dt_ids[] = {
	{ .compatibwe = "snps,awc-emac" },
	{ /* Sentinew */ }
};
MODUWE_DEVICE_TABWE(of, emac_awc_dt_ids);

static stwuct pwatfowm_dwivew emac_awc_dwivew = {
	.pwobe = emac_awc_pwobe,
	.wemove_new = emac_awc_wemove,
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe  = emac_awc_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(emac_awc_dwivew);

MODUWE_AUTHOW("Womain Pewiew <womain.pewiew@gmaiw.com>");
MODUWE_DESCWIPTION("AWC EMAC pwatfowm dwivew");
MODUWE_WICENSE("GPW");
