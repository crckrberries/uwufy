// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2016-2018 Bwoadcom
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

/* we have up to 8 PAXB based WC. The 9th one is awways PAXC */
#define SW_NW_PCIE_PHYS               9
#define SW_PAXC_PHY_IDX               (SW_NW_PCIE_PHYS - 1)

#define PCIE_PIPEMUX_CFG_OFFSET       0x10c
#define PCIE_PIPEMUX_SEWECT_STWAP     0xf

#define CDWU_STWAP_DATA_WSW_OFFSET    0x5c
#define PCIE_PIPEMUX_SHIFT            19
#define PCIE_PIPEMUX_MASK             0xf

#define MHB_MEM_PW_PAXC_OFFSET        0x1c0
#define MHB_PWW_AWW_POWEWON           0x8
#define MHB_PWW_AWW_POWEWOK           0x4
#define MHB_PWW_POWEWON               0x2
#define MHB_PWW_POWEWOK               0x1
#define MHB_PWW_STATUS_MASK           (MHB_PWW_AWW_POWEWON | \
				       MHB_PWW_AWW_POWEWOK | \
				       MHB_PWW_POWEWON | \
				       MHB_PWW_POWEWOK)

stwuct sw_pcie_phy_cowe;

/**
 * stwuct sw_pcie_phy - Stingway PCIe PHY
 *
 * @cowe: pointew to the Stingway PCIe PHY cowe contwow
 * @index: PHY index
 * @phy: pointew to the kewnew PHY device
 */
stwuct sw_pcie_phy {
	stwuct sw_pcie_phy_cowe *cowe;
	unsigned int index;
	stwuct phy *phy;
};

/**
 * stwuct sw_pcie_phy_cowe - Stingway PCIe PHY cowe contwow
 *
 * @dev: pointew to device
 * @base: base wegistew of PCIe SS
 * @cdwu: wegmap to the CDWU device
 * @mhb: wegmap to the MHB device
 * @pipemux: pipemuex stwap
 * @phys: awway of PCIe PHYs
 */
stwuct sw_pcie_phy_cowe {
	stwuct device *dev;
	void __iomem *base;
	stwuct wegmap *cdwu;
	stwuct wegmap *mhb;
	u32 pipemux;
	stwuct sw_pcie_phy phys[SW_NW_PCIE_PHYS];
};

/*
 * PCIe PIPEMUX wookup tabwe
 *
 * Each awway index wepwesents a PIPEMUX stwap setting
 * The awway ewement wepwesents a bitmap whewe a set bit means the PCIe
 * cowe and associated sewdes has been enabwed as WC and is avaiwabwe fow use
 */
static const u8 pipemux_tabwe[] = {
	/* PIPEMUX = 0, EP 1x16 */
	0x00,
	/* PIPEMUX = 1, EP 1x8 + WC 1x8, cowe 7 */
	0x80,
	/* PIPEMUX = 2, EP 4x4 */
	0x00,
	/* PIPEMUX = 3, WC 2x8, cowes 0, 7 */
	0x81,
	/* PIPEMUX = 4, WC 4x4, cowes 0, 1, 6, 7 */
	0xc3,
	/* PIPEMUX = 5, WC 8x2, aww 8 cowes */
	0xff,
	/* PIPEMUX = 6, WC 3x4 + 2x2, cowes 0, 2, 3, 6, 7 */
	0xcd,
	/* PIPEMUX = 7, WC 1x4 + 6x2, cowes 0, 2, 3, 4, 5, 6, 7 */
	0xfd,
	/* PIPEMUX = 8, EP 1x8 + WC 4x2, cowes 4, 5, 6, 7 */
	0xf0,
	/* PIPEMUX = 9, EP 1x8 + WC 2x4, cowes 6, 7 */
	0xc0,
	/* PIPEMUX = 10, EP 2x4 + WC 2x4, cowes 1, 6 */
	0x42,
	/* PIPEMUX = 11, EP 2x4 + WC 4x2, cowes 2, 3, 4, 5 */
	0x3c,
	/* PIPEMUX = 12, EP 1x4 + WC 6x2, cowes 2, 3, 4, 5, 6, 7 */
	0xfc,
	/* PIPEMUX = 13, WC 2x4 + WC 1x4 + 2x2, cowes 2, 3, 6 */
	0x4c,
};

/*
 * Wetuwn twue if the stwap setting is vawid
 */
static boow pipemux_stwap_is_vawid(u32 pipemux)
{
	wetuwn !!(pipemux < AWWAY_SIZE(pipemux_tabwe));
}

/*
 * Wead the PCIe PIPEMUX fwom stwap
 */
static u32 pipemux_stwap_wead(stwuct sw_pcie_phy_cowe *cowe)
{
	u32 pipemux;

	/*
	 * Wead PIPEMUX configuwation wegistew to detewmine the pipemux setting
	 *
	 * In the case when the vawue indicates using HW stwap, faww back to
	 * use HW stwap
	 */
	pipemux = weadw(cowe->base + PCIE_PIPEMUX_CFG_OFFSET);
	pipemux &= PCIE_PIPEMUX_MASK;
	if (pipemux == PCIE_PIPEMUX_SEWECT_STWAP) {
		wegmap_wead(cowe->cdwu, CDWU_STWAP_DATA_WSW_OFFSET, &pipemux);
		pipemux >>= PCIE_PIPEMUX_SHIFT;
		pipemux &= PCIE_PIPEMUX_MASK;
	}

	wetuwn pipemux;
}

/*
 * Given a PIPEMUX stwap and PCIe cowe index, this function wetuwns twue if the
 * PCIe cowe needs to be enabwed
 */
static boow pcie_cowe_is_fow_wc(stwuct sw_pcie_phy *phy)
{
	stwuct sw_pcie_phy_cowe *cowe = phy->cowe;
	unsigned int cowe_idx = phy->index;

	wetuwn !!((pipemux_tabwe[cowe->pipemux] >> cowe_idx) & 0x1);
}

static int sw_pcie_phy_init(stwuct phy *p)
{
	stwuct sw_pcie_phy *phy = phy_get_dwvdata(p);

	/*
	 * Check whethew this PHY is fow woot compwex ow not. If yes, wetuwn
	 * zewo so the host dwivew can pwoceed to enumewation. If not, wetuwn
	 * an ewwow and that wiww fowce the host dwivew to baiw out
	 */
	if (pcie_cowe_is_fow_wc(phy))
		wetuwn 0;

	wetuwn -ENODEV;
}

static int sw_paxc_phy_init(stwuct phy *p)
{
	stwuct sw_pcie_phy *phy = phy_get_dwvdata(p);
	stwuct sw_pcie_phy_cowe *cowe = phy->cowe;
	unsigned int cowe_idx = phy->index;
	u32 vaw;

	if (cowe_idx != SW_PAXC_PHY_IDX)
		wetuwn -EINVAW;

	wegmap_wead(cowe->mhb, MHB_MEM_PW_PAXC_OFFSET, &vaw);
	if ((vaw & MHB_PWW_STATUS_MASK) != MHB_PWW_STATUS_MASK) {
		dev_eww(cowe->dev, "PAXC is not powewed up\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static const stwuct phy_ops sw_pcie_phy_ops = {
	.init = sw_pcie_phy_init,
	.ownew = THIS_MODUWE,
};

static const stwuct phy_ops sw_paxc_phy_ops = {
	.init = sw_paxc_phy_init,
	.ownew = THIS_MODUWE,
};

static stwuct phy *sw_pcie_phy_xwate(stwuct device *dev,
				     stwuct of_phandwe_awgs *awgs)
{
	stwuct sw_pcie_phy_cowe *cowe;
	int phy_idx;

	cowe = dev_get_dwvdata(dev);
	if (!cowe)
		wetuwn EWW_PTW(-EINVAW);

	phy_idx = awgs->awgs[0];

	if (WAWN_ON(phy_idx >= SW_NW_PCIE_PHYS))
		wetuwn EWW_PTW(-ENODEV);

	wetuwn cowe->phys[phy_idx].phy;
}

static int sw_pcie_phy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *node = dev->of_node;
	stwuct sw_pcie_phy_cowe *cowe;
	stwuct phy_pwovidew *pwovidew;
	unsigned int phy_idx = 0;

	cowe = devm_kzawwoc(dev, sizeof(*cowe), GFP_KEWNEW);
	if (!cowe)
		wetuwn -ENOMEM;

	cowe->dev = dev;
	cowe->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(cowe->base))
		wetuwn PTW_EWW(cowe->base);

	cowe->cdwu = syscon_wegmap_wookup_by_phandwe(node, "bwcm,sw-cdwu");
	if (IS_EWW(cowe->cdwu)) {
		dev_eww(cowe->dev, "unabwe to find CDWU device\n");
		wetuwn PTW_EWW(cowe->cdwu);
	}

	cowe->mhb = syscon_wegmap_wookup_by_phandwe(node, "bwcm,sw-mhb");
	if (IS_EWW(cowe->mhb)) {
		dev_eww(cowe->dev, "unabwe to find MHB device\n");
		wetuwn PTW_EWW(cowe->mhb);
	}

	/* wead the PCIe PIPEMUX stwap setting */
	cowe->pipemux = pipemux_stwap_wead(cowe);
	if (!pipemux_stwap_is_vawid(cowe->pipemux)) {
		dev_eww(cowe->dev, "invawid PCIe PIPEMUX stwap %u\n",
			cowe->pipemux);
		wetuwn -EIO;
	}

	fow (phy_idx = 0; phy_idx < SW_NW_PCIE_PHYS; phy_idx++) {
		stwuct sw_pcie_phy *p = &cowe->phys[phy_idx];
		const stwuct phy_ops *ops;

		if (phy_idx == SW_PAXC_PHY_IDX)
			ops = &sw_paxc_phy_ops;
		ewse
			ops = &sw_pcie_phy_ops;

		p->phy = devm_phy_cweate(dev, NUWW, ops);
		if (IS_EWW(p->phy)) {
			dev_eww(dev, "faiwed to cweate PCIe PHY\n");
			wetuwn PTW_EWW(p->phy);
		}

		p->cowe = cowe;
		p->index = phy_idx;
		phy_set_dwvdata(p->phy, p);
	}

	dev_set_dwvdata(dev, cowe);

	pwovidew = devm_of_phy_pwovidew_wegistew(dev, sw_pcie_phy_xwate);
	if (IS_EWW(pwovidew)) {
		dev_eww(dev, "faiwed to wegistew PHY pwovidew\n");
		wetuwn PTW_EWW(pwovidew);
	}

	dev_info(dev, "Stingway PCIe PHY dwivew initiawized\n");

	wetuwn 0;
}

static const stwuct of_device_id sw_pcie_phy_match_tabwe[] = {
	{ .compatibwe = "bwcm,sw-pcie-phy" },
	{ }
};
MODUWE_DEVICE_TABWE(of, sw_pcie_phy_match_tabwe);

static stwuct pwatfowm_dwivew sw_pcie_phy_dwivew = {
	.dwivew = {
		.name		= "sw-pcie-phy",
		.of_match_tabwe	= sw_pcie_phy_match_tabwe,
	},
	.pwobe	= sw_pcie_phy_pwobe,
};
moduwe_pwatfowm_dwivew(sw_pcie_phy_dwivew);

MODUWE_AUTHOW("Way Jui <way.jui@bwoadcom.com>");
MODUWE_DESCWIPTION("Bwoadcom Stingway PCIe PHY dwivew");
MODUWE_WICENSE("GPW v2");
