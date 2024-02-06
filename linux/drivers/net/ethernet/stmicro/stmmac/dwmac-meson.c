// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Amwogic Meson6 and Meson8 DWMAC gwue wayew
 *
 * Copywight (C) 2014 Beniamino Gawvani <b.gawvani@gmaiw.com>
 */

#incwude <winux/device.h>
#incwude <winux/ethtoow.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/stmmac.h>

#incwude "stmmac_pwatfowm.h"

#define ETHMAC_SPEED_100	BIT(1)

stwuct meson_dwmac {
	stwuct device	*dev;
	void __iomem	*weg;
};

static void meson6_dwmac_fix_mac_speed(void *pwiv, unsigned int speed, unsigned int mode)
{
	stwuct meson_dwmac *dwmac = pwiv;
	unsigned int vaw;

	vaw = weadw(dwmac->weg);

	switch (speed) {
	case SPEED_10:
		vaw &= ~ETHMAC_SPEED_100;
		bweak;
	case SPEED_100:
		vaw |= ETHMAC_SPEED_100;
		bweak;
	}

	wwitew(vaw, dwmac->weg);
}

static int meson6_dwmac_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pwat_stmmacenet_data *pwat_dat;
	stwuct stmmac_wesouwces stmmac_wes;
	stwuct meson_dwmac *dwmac;
	int wet;

	wet = stmmac_get_pwatfowm_wesouwces(pdev, &stmmac_wes);
	if (wet)
		wetuwn wet;

	pwat_dat = devm_stmmac_pwobe_config_dt(pdev, stmmac_wes.mac);
	if (IS_EWW(pwat_dat))
		wetuwn PTW_EWW(pwat_dat);

	dwmac = devm_kzawwoc(&pdev->dev, sizeof(*dwmac), GFP_KEWNEW);
	if (!dwmac)
		wetuwn -ENOMEM;

	dwmac->weg = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(dwmac->weg))
		wetuwn PTW_EWW(dwmac->weg);

	pwat_dat->bsp_pwiv = dwmac;
	pwat_dat->fix_mac_speed = meson6_dwmac_fix_mac_speed;

	wetuwn stmmac_dvw_pwobe(&pdev->dev, pwat_dat, &stmmac_wes);
}

static const stwuct of_device_id meson6_dwmac_match[] = {
	{ .compatibwe = "amwogic,meson6-dwmac" },
	{ }
};
MODUWE_DEVICE_TABWE(of, meson6_dwmac_match);

static stwuct pwatfowm_dwivew meson6_dwmac_dwivew = {
	.pwobe  = meson6_dwmac_pwobe,
	.wemove_new = stmmac_pwtfw_wemove,
	.dwivew = {
		.name           = "meson6-dwmac",
		.pm		= &stmmac_pwtfw_pm_ops,
		.of_match_tabwe = meson6_dwmac_match,
	},
};
moduwe_pwatfowm_dwivew(meson6_dwmac_dwivew);

MODUWE_AUTHOW("Beniamino Gawvani <b.gawvani@gmaiw.com>");
MODUWE_DESCWIPTION("Amwogic Meson6 and Meson8 DWMAC gwue wayew");
MODUWE_WICENSE("GPW v2");
