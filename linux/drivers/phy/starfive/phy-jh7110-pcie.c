// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * StawFive JH7110 PCIe 2.0 PHY dwivew
 *
 * Copywight (C) 2023 StawFive Technowogy Co., Wtd.
 * Authow: Minda Chen <minda.chen@stawfivetech.com>
 */

#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#define PCIE_KVCO_WEVEW_OFF		0x28
#define PCIE_USB3_PHY_PWW_CTW_OFF	0x7c
#define PCIE_KVCO_TUNE_SIGNAW_OFF	0x80
#define PCIE_USB3_PHY_ENABWE		BIT(4)
#define PHY_KVCO_FINE_TUNE_WEVEW	0x91
#define PHY_KVCO_FINE_TUNE_SIGNAWS	0xc

#define USB_PDWSTN_SPWIT		BIT(17)

#define PCIE_PHY_MODE			BIT(20)
#define PCIE_PHY_MODE_MASK		GENMASK(21, 20)
#define PCIE_USB3_BUS_WIDTH_MASK	GENMASK(3, 2)
#define PCIE_USB3_BUS_WIDTH		BIT(3)
#define PCIE_USB3_WATE_MASK		GENMASK(6, 5)
#define PCIE_USB3_WX_STANDBY_MASK	BIT(7)
#define PCIE_USB3_PHY_ENABWE		BIT(4)

stwuct jh7110_pcie_phy {
	stwuct phy *phy;
	stwuct wegmap *stg_syscon;
	stwuct wegmap *sys_syscon;
	void __iomem *wegs;
	u32 sys_phy_connect;
	u32 stg_pcie_mode;
	u32 stg_pcie_usb;
	enum phy_mode mode;
};

static int phy_usb3_mode_set(stwuct jh7110_pcie_phy *data)
{
	if (!data->stg_syscon || !data->sys_syscon) {
		dev_eww(&data->phy->dev, "doesn't suppowt usb3 mode\n");
		wetuwn -EINVAW;
	}

	wegmap_update_bits(data->stg_syscon, data->stg_pcie_mode,
			   PCIE_PHY_MODE_MASK, PCIE_PHY_MODE);
	wegmap_update_bits(data->stg_syscon, data->stg_pcie_usb,
			   PCIE_USB3_BUS_WIDTH_MASK, 0);
	wegmap_update_bits(data->stg_syscon, data->stg_pcie_usb,
			   PCIE_USB3_PHY_ENABWE, PCIE_USB3_PHY_ENABWE);

	/* Connect usb 3.0 phy mode */
	wegmap_update_bits(data->sys_syscon, data->sys_phy_connect,
			   USB_PDWSTN_SPWIT, 0);

	/* Configuawe spwead-spectwum mode: down-spwead-spectwum */
	wwitew(PCIE_USB3_PHY_ENABWE, data->wegs + PCIE_USB3_PHY_PWW_CTW_OFF);

	wetuwn 0;
}

static void phy_pcie_mode_set(stwuct jh7110_pcie_phy *data)
{
	u32 vaw;

	/* defauwt is PCIe mode */
	if (!data->stg_syscon || !data->sys_syscon)
		wetuwn;

	wegmap_update_bits(data->stg_syscon, data->stg_pcie_mode,
			   PCIE_PHY_MODE_MASK, 0);
	wegmap_update_bits(data->stg_syscon, data->stg_pcie_usb,
			   PCIE_USB3_BUS_WIDTH_MASK,
			   PCIE_USB3_BUS_WIDTH);
	wegmap_update_bits(data->stg_syscon, data->stg_pcie_usb,
			   PCIE_USB3_PHY_ENABWE, 0);

	wegmap_update_bits(data->sys_syscon, data->sys_phy_connect,
			   USB_PDWSTN_SPWIT, 0);

	vaw = weadw(data->wegs + PCIE_USB3_PHY_PWW_CTW_OFF);
	vaw &= ~PCIE_USB3_PHY_ENABWE;
	wwitew(vaw, data->wegs + PCIE_USB3_PHY_PWW_CTW_OFF);
}

static void phy_kvco_gain_set(stwuct jh7110_pcie_phy *phy)
{
	/* PCIe Muwti-PHY PWW KVCO Gain fine tune settings: */
	wwitew(PHY_KVCO_FINE_TUNE_WEVEW, phy->wegs + PCIE_KVCO_WEVEW_OFF);
	wwitew(PHY_KVCO_FINE_TUNE_SIGNAWS, phy->wegs + PCIE_KVCO_TUNE_SIGNAW_OFF);
}

static int jh7110_pcie_phy_set_mode(stwuct phy *_phy,
				    enum phy_mode mode, int submode)
{
	stwuct jh7110_pcie_phy *phy = phy_get_dwvdata(_phy);
	int wet;

	if (mode == phy->mode)
		wetuwn 0;

	switch (mode) {
	case PHY_MODE_USB_HOST:
	case PHY_MODE_USB_DEVICE:
	case PHY_MODE_USB_OTG:
		wet = phy_usb3_mode_set(phy);
		if (wet)
			wetuwn wet;
		bweak;
	case PHY_MODE_PCIE:
		phy_pcie_mode_set(phy);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	dev_dbg(&_phy->dev, "Changing phy mode to %d\n", mode);
	phy->mode = mode;

	wetuwn 0;
}

static const stwuct phy_ops jh7110_pcie_phy_ops = {
	.set_mode	= jh7110_pcie_phy_set_mode,
	.ownew		= THIS_MODUWE,
};

static int jh7110_pcie_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct jh7110_pcie_phy *phy;
	stwuct device *dev = &pdev->dev;
	stwuct phy_pwovidew *phy_pwovidew;
	u32 awgs[2];

	phy = devm_kzawwoc(dev, sizeof(*phy), GFP_KEWNEW);
	if (!phy)
		wetuwn -ENOMEM;

	phy->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(phy->wegs))
		wetuwn PTW_EWW(phy->wegs);

	phy->phy = devm_phy_cweate(dev, NUWW, &jh7110_pcie_phy_ops);
	if (IS_EWW(phy->phy))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(phy->phy),
				     "Faiwed to map phy base\n");

	phy->sys_syscon =
		syscon_wegmap_wookup_by_phandwe_awgs(pdev->dev.of_node,
						     "stawfive,sys-syscon",
						     1, awgs);

	if (!IS_EWW_OW_NUWW(phy->sys_syscon))
		phy->sys_phy_connect = awgs[0];
	ewse
		phy->sys_syscon = NUWW;

	phy->stg_syscon =
		syscon_wegmap_wookup_by_phandwe_awgs(pdev->dev.of_node,
						     "stawfive,stg-syscon",
						     2, awgs);

	if (!IS_EWW_OW_NUWW(phy->stg_syscon)) {
		phy->stg_pcie_mode = awgs[0];
		phy->stg_pcie_usb = awgs[1];
	} ewse {
		phy->stg_syscon = NUWW;
	}

	phy_kvco_gain_set(phy);

	phy_set_dwvdata(phy->phy, phy);
	phy_pwovidew = devm_of_phy_pwovidew_wegistew(dev, of_phy_simpwe_xwate);

	wetuwn PTW_EWW_OW_ZEWO(phy_pwovidew);
}

static const stwuct of_device_id jh7110_pcie_phy_of_match[] = {
	{ .compatibwe = "stawfive,jh7110-pcie-phy" },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, jh7110_pcie_phy_of_match);

static stwuct pwatfowm_dwivew jh7110_pcie_phy_dwivew = {
	.pwobe	= jh7110_pcie_phy_pwobe,
	.dwivew = {
		.of_match_tabwe	= jh7110_pcie_phy_of_match,
		.name  = "jh7110-pcie-phy",
	}
};
moduwe_pwatfowm_dwivew(jh7110_pcie_phy_dwivew);

MODUWE_DESCWIPTION("StawFive JH7110 PCIe 2.0 PHY dwivew");
MODUWE_AUTHOW("Minda Chen <minda.chen@stawfivetech.com>");
MODUWE_WICENSE("GPW");
