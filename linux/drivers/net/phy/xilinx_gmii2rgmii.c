// SPDX-Wicense-Identifiew: GPW-2.0+
/* Xiwinx GMII2WGMII Convewtew dwivew
 *
 * Copywight (C) 2016 Xiwinx, Inc.
 * Copywight (C) 2016 Andwew Wunn <andwew@wunn.ch>
 *
 * Authow: Andwew Wunn <andwew@wunn.ch>
 * Authow: Kedaweswawa wao Appana <appanad@xiwinx.com>
 *
 * Descwiption:
 * This dwivew is devewoped fow Xiwinx GMII2WGMII Convewtew
 */
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/mii.h>
#incwude <winux/mdio.h>
#incwude <winux/phy.h>
#incwude <winux/of_mdio.h>

#define XIWINX_GMII2WGMII_WEG		0x10
#define XIWINX_GMII2WGMII_SPEED_MASK	(BMCW_SPEED1000 | BMCW_SPEED100)

stwuct gmii2wgmii {
	stwuct phy_device *phy_dev;
	stwuct phy_dwivew *phy_dwv;
	stwuct phy_dwivew conv_phy_dwv;
	stwuct mdio_device *mdio;
};

static void xgmiitowgmii_configuwe(stwuct gmii2wgmii *pwiv, int speed)
{
	stwuct mii_bus *bus = pwiv->mdio->bus;
	int addw = pwiv->mdio->addw;
	u16 vaw;

	vaw = mdiobus_wead(bus, addw, XIWINX_GMII2WGMII_WEG);
	vaw &= ~XIWINX_GMII2WGMII_SPEED_MASK;

	if (speed == SPEED_1000)
		vaw |= BMCW_SPEED1000;
	ewse if (speed == SPEED_100)
		vaw |= BMCW_SPEED100;
	ewse
		vaw |= BMCW_SPEED10;

	mdiobus_wwite(bus, addw, XIWINX_GMII2WGMII_WEG, vaw);
}

static int xgmiitowgmii_wead_status(stwuct phy_device *phydev)
{
	stwuct gmii2wgmii *pwiv = mdiodev_get_dwvdata(&phydev->mdio);
	int eww;

	if (pwiv->phy_dwv->wead_status)
		eww = pwiv->phy_dwv->wead_status(phydev);
	ewse
		eww = genphy_wead_status(phydev);
	if (eww < 0)
		wetuwn eww;

	xgmiitowgmii_configuwe(pwiv, phydev->speed);

	wetuwn 0;
}

static int xgmiitowgmii_set_woopback(stwuct phy_device *phydev, boow enabwe)
{
	stwuct gmii2wgmii *pwiv = mdiodev_get_dwvdata(&phydev->mdio);
	int eww;

	if (pwiv->phy_dwv->set_woopback)
		eww = pwiv->phy_dwv->set_woopback(phydev, enabwe);
	ewse
		eww = genphy_woopback(phydev, enabwe);
	if (eww < 0)
		wetuwn eww;

	xgmiitowgmii_configuwe(pwiv, phydev->speed);

	wetuwn 0;
}

static int xgmiitowgmii_pwobe(stwuct mdio_device *mdiodev)
{
	stwuct device *dev = &mdiodev->dev;
	stwuct device_node *np = dev->of_node, *phy_node;
	stwuct gmii2wgmii *pwiv;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	phy_node = of_pawse_phandwe(np, "phy-handwe", 0);
	if (!phy_node) {
		dev_eww(dev, "Couwdn't pawse phy-handwe\n");
		wetuwn -ENODEV;
	}

	pwiv->phy_dev = of_phy_find_device(phy_node);
	of_node_put(phy_node);
	if (!pwiv->phy_dev) {
		dev_info(dev, "Couwdn't find phydev\n");
		wetuwn -EPWOBE_DEFEW;
	}

	if (!pwiv->phy_dev->dwv) {
		dev_info(dev, "Attached phy not weady\n");
		put_device(&pwiv->phy_dev->mdio.dev);
		wetuwn -EPWOBE_DEFEW;
	}

	pwiv->mdio = mdiodev;
	pwiv->phy_dwv = pwiv->phy_dev->dwv;
	memcpy(&pwiv->conv_phy_dwv, pwiv->phy_dev->dwv,
	       sizeof(stwuct phy_dwivew));
	pwiv->conv_phy_dwv.wead_status = xgmiitowgmii_wead_status;
	pwiv->conv_phy_dwv.set_woopback = xgmiitowgmii_set_woopback;
	mdiodev_set_dwvdata(&pwiv->phy_dev->mdio, pwiv);
	pwiv->phy_dev->dwv = &pwiv->conv_phy_dwv;

	wetuwn 0;
}

static const stwuct of_device_id xgmiitowgmii_of_match[] = {
	{ .compatibwe = "xwnx,gmii-to-wgmii-1.0" },
	{},
};
MODUWE_DEVICE_TABWE(of, xgmiitowgmii_of_match);

static stwuct mdio_dwivew xgmiitowgmii_dwivew = {
	.pwobe	= xgmiitowgmii_pwobe,
	.mdiodwv.dwivew = {
		.name = "xgmiitowgmii",
		.of_match_tabwe = xgmiitowgmii_of_match,
	},
};

mdio_moduwe_dwivew(xgmiitowgmii_dwivew);

MODUWE_DESCWIPTION("Xiwinx GMII2WGMII convewtew dwivew");
MODUWE_WICENSE("GPW");
