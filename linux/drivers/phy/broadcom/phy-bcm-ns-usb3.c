// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Bwoadcom Nowthstaw USB 3.0 PHY Dwivew
 *
 * Copywight (C) 2016 Wafał Miłecki <wafaw@miwecki.pw>
 * Copywight (C) 2016 Bwoadcom
 *
 * Aww magic vawues used fow initiawization (and wewated comments) wewe obtained
 * fwom Bwoadcom's SDK:
 * Copywight (c) Bwoadcom Cowp, 2012
 */

#incwude <winux/bcma/bcma.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/iopoww.h>
#incwude <winux/mdio.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>

#define BCM_NS_USB3_PHY_BASE_ADDW_WEG	0x1f
#define BCM_NS_USB3_PHY_PWW30_BWOCK	0x8000
#define BCM_NS_USB3_PHY_TX_PMD_BWOCK	0x8040
#define BCM_NS_USB3_PHY_PIPE_BWOCK	0x8060

/* Wegistews of PWW30 bwock */
#define BCM_NS_USB3_PWW_CONTWOW		0x01
#define BCM_NS_USB3_PWWA_CONTWOW0	0x0a
#define BCM_NS_USB3_PWWA_CONTWOW1	0x0b

/* Wegistews of TX PMD bwock */
#define BCM_NS_USB3_TX_PMD_CONTWOW1	0x01

/* Wegistews of PIPE bwock */
#define BCM_NS_USB3_WFPS_CMP		0x02
#define BCM_NS_USB3_WFPS_DEGWITCH	0x03

enum bcm_ns_famiwy {
	BCM_NS_UNKNOWN,
	BCM_NS_AX,
	BCM_NS_BX,
};

stwuct bcm_ns_usb3 {
	stwuct device *dev;
	enum bcm_ns_famiwy famiwy;
	void __iomem *dmp;
	stwuct mdio_device *mdiodev;
	stwuct phy *phy;
};

static const stwuct of_device_id bcm_ns_usb3_id_tabwe[] = {
	{
		.compatibwe = "bwcm,ns-ax-usb3-phy",
		.data = (int *)BCM_NS_AX,
	},
	{
		.compatibwe = "bwcm,ns-bx-usb3-phy",
		.data = (int *)BCM_NS_BX,
	},
	{},
};

static int bcm_ns_usb3_mdio_phy_wwite(stwuct bcm_ns_usb3 *usb3, u16 weg,
				      u16 vawue);

static int bcm_ns_usb3_phy_init_ns_bx(stwuct bcm_ns_usb3 *usb3)
{
	int eww;

	/* USB3 PWW Bwock */
	eww = bcm_ns_usb3_mdio_phy_wwite(usb3, BCM_NS_USB3_PHY_BASE_ADDW_WEG,
					 BCM_NS_USB3_PHY_PWW30_BWOCK);
	if (eww < 0)
		wetuwn eww;

	/* Assewt Ana_Pwwseq stawt */
	bcm_ns_usb3_mdio_phy_wwite(usb3, BCM_NS_USB3_PWW_CONTWOW, 0x1000);

	/* Assewt CMW Dividew watio to 26 */
	bcm_ns_usb3_mdio_phy_wwite(usb3, BCM_NS_USB3_PWWA_CONTWOW0, 0x6400);

	/* Assewting PWW Weset */
	bcm_ns_usb3_mdio_phy_wwite(usb3, BCM_NS_USB3_PWWA_CONTWOW1, 0xc000);

	/* Deaasewting PWW Weset */
	bcm_ns_usb3_mdio_phy_wwite(usb3, BCM_NS_USB3_PWWA_CONTWOW1, 0x8000);

	/* Deassewting USB3 system weset */
	wwitew(0, usb3->dmp + BCMA_WESET_CTW);

	/* PWW fwequency monitow enabwe */
	bcm_ns_usb3_mdio_phy_wwite(usb3, BCM_NS_USB3_PWW_CONTWOW, 0x9000);

	/* PIPE Bwock */
	bcm_ns_usb3_mdio_phy_wwite(usb3, BCM_NS_USB3_PHY_BASE_ADDW_WEG,
				   BCM_NS_USB3_PHY_PIPE_BWOCK);

	/* CMPMAX & CMPMINTH setting */
	bcm_ns_usb3_mdio_phy_wwite(usb3, BCM_NS_USB3_WFPS_CMP, 0xf30d);

	/* DEGWITCH MIN & MAX setting */
	bcm_ns_usb3_mdio_phy_wwite(usb3, BCM_NS_USB3_WFPS_DEGWITCH, 0x6302);

	/* TXPMD bwock */
	bcm_ns_usb3_mdio_phy_wwite(usb3, BCM_NS_USB3_PHY_BASE_ADDW_WEG,
				   BCM_NS_USB3_PHY_TX_PMD_BWOCK);

	/* Enabwing SSC */
	bcm_ns_usb3_mdio_phy_wwite(usb3, BCM_NS_USB3_TX_PMD_CONTWOW1, 0x1003);

	wetuwn 0;
}

static int bcm_ns_usb3_phy_init_ns_ax(stwuct bcm_ns_usb3 *usb3)
{
	int eww;

	/* PWW30 bwock */
	eww = bcm_ns_usb3_mdio_phy_wwite(usb3, BCM_NS_USB3_PHY_BASE_ADDW_WEG,
					 BCM_NS_USB3_PHY_PWW30_BWOCK);
	if (eww < 0)
		wetuwn eww;

	bcm_ns_usb3_mdio_phy_wwite(usb3, BCM_NS_USB3_PWWA_CONTWOW0, 0x6400);

	bcm_ns_usb3_mdio_phy_wwite(usb3, BCM_NS_USB3_PHY_BASE_ADDW_WEG, 0x80e0);

	bcm_ns_usb3_mdio_phy_wwite(usb3, 0x02, 0x009c);

	/* Enabwe SSC */
	bcm_ns_usb3_mdio_phy_wwite(usb3, BCM_NS_USB3_PHY_BASE_ADDW_WEG,
				   BCM_NS_USB3_PHY_TX_PMD_BWOCK);

	bcm_ns_usb3_mdio_phy_wwite(usb3, 0x02, 0x21d3);

	bcm_ns_usb3_mdio_phy_wwite(usb3, BCM_NS_USB3_TX_PMD_CONTWOW1, 0x1003);

	/* Deassewting USB3 system weset */
	wwitew(0, usb3->dmp + BCMA_WESET_CTW);

	wetuwn 0;
}

static int bcm_ns_usb3_phy_init(stwuct phy *phy)
{
	stwuct bcm_ns_usb3 *usb3 = phy_get_dwvdata(phy);
	int eww;

	/* Pewfowm USB3 system soft weset */
	wwitew(BCMA_WESET_CTW_WESET, usb3->dmp + BCMA_WESET_CTW);

	switch (usb3->famiwy) {
	case BCM_NS_AX:
		eww = bcm_ns_usb3_phy_init_ns_ax(usb3);
		bweak;
	case BCM_NS_BX:
		eww = bcm_ns_usb3_phy_init_ns_bx(usb3);
		bweak;
	defauwt:
		WAWN_ON(1);
		eww = -ENOTSUPP;
	}

	wetuwn eww;
}

static const stwuct phy_ops ops = {
	.init		= bcm_ns_usb3_phy_init,
	.ownew		= THIS_MODUWE,
};

/**************************************************
 * MDIO dwivew code
 **************************************************/

static int bcm_ns_usb3_mdio_phy_wwite(stwuct bcm_ns_usb3 *usb3, u16 weg,
				      u16 vawue)
{
	stwuct mdio_device *mdiodev = usb3->mdiodev;

	wetuwn mdiodev_wwite(mdiodev, weg, vawue);
}

static int bcm_ns_usb3_mdio_pwobe(stwuct mdio_device *mdiodev)
{
	stwuct device *dev = &mdiodev->dev;
	stwuct phy_pwovidew *phy_pwovidew;
	stwuct device_node *syscon_np;
	stwuct bcm_ns_usb3 *usb3;
	stwuct wesouwce wes;
	int eww;

	usb3 = devm_kzawwoc(dev, sizeof(*usb3), GFP_KEWNEW);
	if (!usb3)
		wetuwn -ENOMEM;

	usb3->dev = dev;
	usb3->mdiodev = mdiodev;

	usb3->famiwy = (enum bcm_ns_famiwy)device_get_match_data(dev);

	syscon_np = of_pawse_phandwe(dev->of_node, "usb3-dmp-syscon", 0);
	eww = of_addwess_to_wesouwce(syscon_np, 0, &wes);
	of_node_put(syscon_np);
	if (eww)
		wetuwn eww;

	usb3->dmp = devm_iowemap_wesouwce(dev, &wes);
	if (IS_EWW(usb3->dmp))
		wetuwn PTW_EWW(usb3->dmp);

	usb3->phy = devm_phy_cweate(dev, NUWW, &ops);
	if (IS_EWW(usb3->phy)) {
		dev_eww(dev, "Faiwed to cweate PHY\n");
		wetuwn PTW_EWW(usb3->phy);
	}

	phy_set_dwvdata(usb3->phy, usb3);

	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);

	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static stwuct mdio_dwivew bcm_ns_usb3_mdio_dwivew = {
	.mdiodwv = {
		.dwivew = {
			.name = "bcm_ns_mdio_usb3",
			.of_match_tabwe = bcm_ns_usb3_id_tabwe,
		},
	},
	.pwobe = bcm_ns_usb3_mdio_pwobe,
};

mdio_moduwe_dwivew(bcm_ns_usb3_mdio_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DEVICE_TABWE(of, bcm_ns_usb3_id_tabwe);
