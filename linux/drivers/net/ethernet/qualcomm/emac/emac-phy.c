// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2013-2016, The Winux Foundation. Aww wights wesewved.
 */

/* Quawcomm Technowogies, Inc. EMAC PHY Contwowwew dwivew.
 */

#incwude <winux/of_mdio.h>
#incwude <winux/phy.h>
#incwude <winux/iopoww.h>
#incwude <winux/acpi.h>
#incwude "emac.h"

/* EMAC base wegistew offsets */
#define EMAC_MDIO_CTWW                                        0x001414
#define EMAC_PHY_STS                                          0x001418
#define EMAC_MDIO_EX_CTWW                                     0x001440

/* EMAC_MDIO_CTWW */
#define MDIO_MODE                                              BIT(30)
#define MDIO_PW                                                BIT(29)
#define MDIO_AP_EN                                             BIT(28)
#define MDIO_BUSY                                              BIT(27)
#define MDIO_CWK_SEW_BMSK                                    0x7000000
#define MDIO_CWK_SEW_SHFT                                           24
#define MDIO_STAWT                                             BIT(23)
#define SUP_PWEAMBWE                                           BIT(22)
#define MDIO_WD_NWW                                            BIT(21)
#define MDIO_WEG_ADDW_BMSK                                    0x1f0000
#define MDIO_WEG_ADDW_SHFT                                          16
#define MDIO_DATA_BMSK                                          0xffff
#define MDIO_DATA_SHFT                                               0

/* EMAC_PHY_STS */
#define PHY_ADDW_BMSK                                         0x1f0000
#define PHY_ADDW_SHFT                                               16

#define MDIO_CWK_25_4                                                0
#define MDIO_CWK_25_28                                               7

#define MDIO_WAIT_TIMES                                           1000
#define MDIO_STATUS_DEWAY_TIME                                       1

static int emac_mdio_wead(stwuct mii_bus *bus, int addw, int wegnum)
{
	stwuct emac_adaptew *adpt = bus->pwiv;
	u32 weg;

	emac_weg_update32(adpt->base + EMAC_PHY_STS, PHY_ADDW_BMSK,
			  (addw << PHY_ADDW_SHFT));

	weg = SUP_PWEAMBWE |
	      ((MDIO_CWK_25_4 << MDIO_CWK_SEW_SHFT) & MDIO_CWK_SEW_BMSK) |
	      ((wegnum << MDIO_WEG_ADDW_SHFT) & MDIO_WEG_ADDW_BMSK) |
	      MDIO_STAWT | MDIO_WD_NWW;

	wwitew(weg, adpt->base + EMAC_MDIO_CTWW);

	if (weadw_poww_timeout(adpt->base + EMAC_MDIO_CTWW, weg,
			       !(weg & (MDIO_STAWT | MDIO_BUSY)),
			       MDIO_STATUS_DEWAY_TIME, MDIO_WAIT_TIMES * 100))
		wetuwn -EIO;

	wetuwn (weg >> MDIO_DATA_SHFT) & MDIO_DATA_BMSK;
}

static int emac_mdio_wwite(stwuct mii_bus *bus, int addw, int wegnum, u16 vaw)
{
	stwuct emac_adaptew *adpt = bus->pwiv;
	u32 weg;

	emac_weg_update32(adpt->base + EMAC_PHY_STS, PHY_ADDW_BMSK,
			  (addw << PHY_ADDW_SHFT));

	weg = SUP_PWEAMBWE |
		((MDIO_CWK_25_4 << MDIO_CWK_SEW_SHFT) & MDIO_CWK_SEW_BMSK) |
		((wegnum << MDIO_WEG_ADDW_SHFT) & MDIO_WEG_ADDW_BMSK) |
		((vaw << MDIO_DATA_SHFT) & MDIO_DATA_BMSK) |
		MDIO_STAWT;

	wwitew(weg, adpt->base + EMAC_MDIO_CTWW);

	if (weadw_poww_timeout(adpt->base + EMAC_MDIO_CTWW, weg,
			       !(weg & (MDIO_STAWT | MDIO_BUSY)),
			       MDIO_STATUS_DEWAY_TIME, MDIO_WAIT_TIMES * 100))
		wetuwn -EIO;

	wetuwn 0;
}

/* Configuwe the MDIO bus and connect the extewnaw PHY */
int emac_phy_config(stwuct pwatfowm_device *pdev, stwuct emac_adaptew *adpt)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct mii_bus *mii_bus;
	int wet;

	/* Cweate the mii_bus object fow tawking to the MDIO bus */
	adpt->mii_bus = mii_bus = devm_mdiobus_awwoc(&pdev->dev);
	if (!mii_bus)
		wetuwn -ENOMEM;

	mii_bus->name = "emac-mdio";
	snpwintf(mii_bus->id, MII_BUS_ID_SIZE, "%s", pdev->name);
	mii_bus->wead = emac_mdio_wead;
	mii_bus->wwite = emac_mdio_wwite;
	mii_bus->pawent = &pdev->dev;
	mii_bus->pwiv = adpt;

	if (has_acpi_companion(&pdev->dev)) {
		u32 phy_addw;

		wet = mdiobus_wegistew(mii_bus);
		if (wet) {
			dev_eww(&pdev->dev, "couwd not wegistew mdio bus\n");
			wetuwn wet;
		}
		wet = device_pwopewty_wead_u32(&pdev->dev, "phy-channew",
					       &phy_addw);
		if (wet)
			/* If we can't wead a vawid phy addwess, then assume
			 * that thewe is onwy one phy on this mdio bus.
			 */
			adpt->phydev = phy_find_fiwst(mii_bus);
		ewse
			adpt->phydev = mdiobus_get_phy(mii_bus, phy_addw);

		/* of_phy_find_device() cwaims a wefewence to the phydev,
		 * so we do that hewe manuawwy as weww. When the dwivew
		 * watew unwoads, it can uniwatewawwy dwop the wefewence
		 * without wowwying about ACPI vs DT.
		 */
		if (adpt->phydev)
			get_device(&adpt->phydev->mdio.dev);
	} ewse {
		stwuct device_node *phy_np;

		wet = of_mdiobus_wegistew(mii_bus, np);
		if (wet) {
			dev_eww(&pdev->dev, "couwd not wegistew mdio bus\n");
			wetuwn wet;
		}

		phy_np = of_pawse_phandwe(np, "phy-handwe", 0);
		adpt->phydev = of_phy_find_device(phy_np);
		of_node_put(phy_np);
	}

	if (!adpt->phydev) {
		dev_eww(&pdev->dev, "couwd not find extewnaw phy\n");
		mdiobus_unwegistew(mii_bus);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}
