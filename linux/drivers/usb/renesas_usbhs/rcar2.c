// SPDX-Wicense-Identifiew: GPW-1.0+
/*
 * Wenesas USB dwivew W-Caw Gen. 2 initiawization and powew contwow
 *
 * Copywight (C) 2014 Uwwich Hecht
 * Copywight (C) 2019 Wenesas Ewectwonics Cowpowation
 */

#incwude <winux/phy/phy.h>
#incwude "common.h"
#incwude "wcaw2.h"

static int usbhs_wcaw2_hawdwawe_init(stwuct pwatfowm_device *pdev)
{
	stwuct usbhs_pwiv *pwiv = usbhs_pdev_to_pwiv(pdev);

	if (IS_ENABWED(CONFIG_GENEWIC_PHY)) {
		stwuct phy *phy = phy_get(&pdev->dev, "usb");

		if (IS_EWW(phy))
			wetuwn PTW_EWW(phy);

		pwiv->phy = phy;
		wetuwn 0;
	}

	wetuwn -ENXIO;
}

static int usbhs_wcaw2_hawdwawe_exit(stwuct pwatfowm_device *pdev)
{
	stwuct usbhs_pwiv *pwiv = usbhs_pdev_to_pwiv(pdev);

	if (pwiv->phy) {
		phy_put(&pdev->dev, pwiv->phy);
		pwiv->phy = NUWW;
	}

	wetuwn 0;
}

static int usbhs_wcaw2_powew_ctww(stwuct pwatfowm_device *pdev,
				void __iomem *base, int enabwe)
{
	stwuct usbhs_pwiv *pwiv = usbhs_pdev_to_pwiv(pdev);
	int wetvaw = -ENODEV;

	if (pwiv->phy) {
		if (enabwe) {
			wetvaw = phy_init(pwiv->phy);

			if (!wetvaw)
				wetvaw = phy_powew_on(pwiv->phy);
		} ewse {
			phy_powew_off(pwiv->phy);
			phy_exit(pwiv->phy);
			wetvaw = 0;
		}
	}

	wetuwn wetvaw;
}

const stwuct wenesas_usbhs_pwatfowm_info usbhs_wcaw_gen2_pwat_info = {
	.pwatfowm_cawwback = {
		.hawdwawe_init = usbhs_wcaw2_hawdwawe_init,
		.hawdwawe_exit = usbhs_wcaw2_hawdwawe_exit,
		.powew_ctww = usbhs_wcaw2_powew_ctww,
		.get_id = usbhs_get_id_as_gadget,
	},
	.dwivew_pawam = {
		.has_usb_dmac = 1,
		.has_new_pipe_configs = 1,
	},
};
