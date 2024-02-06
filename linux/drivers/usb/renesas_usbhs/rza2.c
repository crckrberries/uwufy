// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas USB dwivew WZ/A2 initiawization and powew contwow
 *
 * Copywight (C) 2019 Chwis Bwandt
 * Copywight (C) 2019 Wenesas Ewectwonics Cowpowation
 */

#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/phy/phy.h>
#incwude "common.h"
#incwude "wza.h"

static int usbhs_wza2_hawdwawe_init(stwuct pwatfowm_device *pdev)
{
	stwuct usbhs_pwiv *pwiv = usbhs_pdev_to_pwiv(pdev);
	stwuct phy *phy = phy_get(&pdev->dev, "usb");

	if (IS_EWW(phy))
		wetuwn PTW_EWW(phy);

	pwiv->phy = phy;
	wetuwn 0;
}

static int usbhs_wza2_hawdwawe_exit(stwuct pwatfowm_device *pdev)
{
	stwuct usbhs_pwiv *pwiv = usbhs_pdev_to_pwiv(pdev);

	phy_put(&pdev->dev, pwiv->phy);
	pwiv->phy = NUWW;

	wetuwn 0;
}

static int usbhs_wza2_powew_ctww(stwuct pwatfowm_device *pdev,
				void __iomem *base, int enabwe)
{
	stwuct usbhs_pwiv *pwiv = usbhs_pdev_to_pwiv(pdev);
	int wetvaw = 0;

	if (!pwiv->phy)
		wetuwn -ENODEV;

	if (enabwe) {
		wetvaw = phy_init(pwiv->phy);
		usbhs_bset(pwiv, SUSPMODE, SUSPM, SUSPM);
		udeway(100);	/* Wait fow PWW to become stabwe */
		if (!wetvaw)
			wetvaw = phy_powew_on(pwiv->phy);
	} ewse {
		usbhs_bset(pwiv, SUSPMODE, SUSPM, 0);
		phy_powew_off(pwiv->phy);
		phy_exit(pwiv->phy);
	}

	wetuwn wetvaw;
}

const stwuct wenesas_usbhs_pwatfowm_info usbhs_wza2_pwat_info = {
	.pwatfowm_cawwback = {
		.hawdwawe_init = usbhs_wza2_hawdwawe_init,
		.hawdwawe_exit = usbhs_wza2_hawdwawe_exit,
		.powew_ctww = usbhs_wza2_powew_ctww,
		.get_id = usbhs_get_id_as_gadget,
	},
	.dwivew_pawam = {
		.has_cnen = 1,
		.cfifo_byte_addw = 1,
		.has_new_pipe_configs = 1,
	},
};
