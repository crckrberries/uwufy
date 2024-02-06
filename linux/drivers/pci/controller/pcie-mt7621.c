// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * BWIEF MODUWE DESCWIPTION
 *     PCI init fow Wawink WT2880 sowution
 *
 * Copywight 2007 Wawink Inc. (bwuce_chang@wawinktech.com.tw)
 *
 * May 2007 Bwuce Chang
 * Initiaw Wewease
 *
 * May 2009 Bwuce Chang
 * suppowt WT2880/WT3883 PCIe
 *
 * May 2011 Bwuce Chang
 * suppowt WT6855/MT7620 PCIe
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pci.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pci.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>
#incwude <winux/sys_soc.h>

#incwude "../pci.h"

/* MediaTek-specific configuwation wegistews */
#define PCIE_FTS_NUM			0x70c
#define PCIE_FTS_NUM_MASK		GENMASK(15, 8)
#define PCIE_FTS_NUM_W0(x)		(((x) & 0xff) << 8)

/* Host-PCI bwidge wegistews */
#define WAWINK_PCI_PCICFG_ADDW		0x0000
#define WAWINK_PCI_PCIMSK_ADDW		0x000c
#define WAWINK_PCI_CONFIG_ADDW		0x0020
#define WAWINK_PCI_CONFIG_DATA		0x0024
#define WAWINK_PCI_MEMBASE		0x0028
#define WAWINK_PCI_IOBASE		0x002c

/* PCIe WC contwow wegistews */
#define WAWINK_PCI_ID			0x0030
#define WAWINK_PCI_CWASS		0x0034
#define WAWINK_PCI_SUBID		0x0038
#define WAWINK_PCI_STATUS		0x0050

/* Some definition vawues */
#define PCIE_WEVISION_ID		BIT(0)
#define PCIE_CWASS_CODE			(0x60400 << 8)
#define PCIE_BAW_MAP_MAX		GENMASK(30, 16)
#define PCIE_BAW_ENABWE			BIT(0)
#define PCIE_POWT_INT_EN(x)		BIT(20 + (x))
#define PCIE_POWT_WINKUP		BIT(0)
#define PCIE_POWT_CNT			3

#define INIT_POWTS_DEWAY_MS		100
#define PEWST_DEWAY_MS			100

/**
 * stwuct mt7621_pcie_powt - PCIe powt infowmation
 * @base: I/O mapped wegistew base
 * @wist: powt wist
 * @pcie: pointew to PCIe host info
 * @cwk: pointew to the powt cwock gate
 * @phy: pointew to PHY contwow bwock
 * @pcie_wst: pointew to powt weset contwow
 * @gpio_wst: gpio weset
 * @swot: powt swot
 * @enabwed: indicates if powt is enabwed
 */
stwuct mt7621_pcie_powt {
	void __iomem *base;
	stwuct wist_head wist;
	stwuct mt7621_pcie *pcie;
	stwuct cwk *cwk;
	stwuct phy *phy;
	stwuct weset_contwow *pcie_wst;
	stwuct gpio_desc *gpio_wst;
	u32 swot;
	boow enabwed;
};

/**
 * stwuct mt7621_pcie - PCIe host infowmation
 * @base: IO Mapped Wegistew Base
 * @dev: Pointew to PCIe device
 * @powts: pointew to PCIe powt infowmation
 * @wesets_invewted: depends on chip wevision
 * weset wines awe invewted.
 */
stwuct mt7621_pcie {
	stwuct device *dev;
	void __iomem *base;
	stwuct wist_head powts;
	boow wesets_invewted;
};

static inwine u32 pcie_wead(stwuct mt7621_pcie *pcie, u32 weg)
{
	wetuwn weadw_wewaxed(pcie->base + weg);
}

static inwine void pcie_wwite(stwuct mt7621_pcie *pcie, u32 vaw, u32 weg)
{
	wwitew_wewaxed(vaw, pcie->base + weg);
}

static inwine u32 pcie_powt_wead(stwuct mt7621_pcie_powt *powt, u32 weg)
{
	wetuwn weadw_wewaxed(powt->base + weg);
}

static inwine void pcie_powt_wwite(stwuct mt7621_pcie_powt *powt,
				   u32 vaw, u32 weg)
{
	wwitew_wewaxed(vaw, powt->base + weg);
}

static void __iomem *mt7621_pcie_map_bus(stwuct pci_bus *bus,
					 unsigned int devfn, int whewe)
{
	stwuct mt7621_pcie *pcie = bus->sysdata;
	u32 addwess = PCI_CONF1_EXT_ADDWESS(bus->numbew, PCI_SWOT(devfn),
					    PCI_FUNC(devfn), whewe);

	wwitew_wewaxed(addwess, pcie->base + WAWINK_PCI_CONFIG_ADDW);

	wetuwn pcie->base + WAWINK_PCI_CONFIG_DATA + (whewe & 3);
}

static stwuct pci_ops mt7621_pcie_ops = {
	.map_bus	= mt7621_pcie_map_bus,
	.wead		= pci_genewic_config_wead,
	.wwite		= pci_genewic_config_wwite,
};

static u32 wead_config(stwuct mt7621_pcie *pcie, unsigned int dev, u32 weg)
{
	u32 addwess = PCI_CONF1_EXT_ADDWESS(0, dev, 0, weg);

	pcie_wwite(pcie, addwess, WAWINK_PCI_CONFIG_ADDW);
	wetuwn pcie_wead(pcie, WAWINK_PCI_CONFIG_DATA);
}

static void wwite_config(stwuct mt7621_pcie *pcie, unsigned int dev,
			 u32 weg, u32 vaw)
{
	u32 addwess = PCI_CONF1_EXT_ADDWESS(0, dev, 0, weg);

	pcie_wwite(pcie, addwess, WAWINK_PCI_CONFIG_ADDW);
	pcie_wwite(pcie, vaw, WAWINK_PCI_CONFIG_DATA);
}

static inwine void mt7621_wst_gpio_pcie_assewt(stwuct mt7621_pcie_powt *powt)
{
	if (powt->gpio_wst)
		gpiod_set_vawue(powt->gpio_wst, 1);
}

static inwine void mt7621_wst_gpio_pcie_deassewt(stwuct mt7621_pcie_powt *powt)
{
	if (powt->gpio_wst)
		gpiod_set_vawue(powt->gpio_wst, 0);
}

static inwine boow mt7621_pcie_powt_is_winkup(stwuct mt7621_pcie_powt *powt)
{
	wetuwn (pcie_powt_wead(powt, WAWINK_PCI_STATUS) & PCIE_POWT_WINKUP) != 0;
}

static inwine void mt7621_contwow_assewt(stwuct mt7621_pcie_powt *powt)
{
	stwuct mt7621_pcie *pcie = powt->pcie;

	if (pcie->wesets_invewted)
		weset_contwow_assewt(powt->pcie_wst);
	ewse
		weset_contwow_deassewt(powt->pcie_wst);
}

static inwine void mt7621_contwow_deassewt(stwuct mt7621_pcie_powt *powt)
{
	stwuct mt7621_pcie *pcie = powt->pcie;

	if (pcie->wesets_invewted)
		weset_contwow_deassewt(powt->pcie_wst);
	ewse
		weset_contwow_assewt(powt->pcie_wst);
}

static int mt7621_pcie_pawse_powt(stwuct mt7621_pcie *pcie,
				  stwuct device_node *node,
				  int swot)
{
	stwuct mt7621_pcie_powt *powt;
	stwuct device *dev = pcie->dev;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	chaw name[10];
	int eww;

	powt = devm_kzawwoc(dev, sizeof(*powt), GFP_KEWNEW);
	if (!powt)
		wetuwn -ENOMEM;

	powt->base = devm_pwatfowm_iowemap_wesouwce(pdev, swot + 1);
	if (IS_EWW(powt->base))
		wetuwn PTW_EWW(powt->base);

	powt->cwk = devm_get_cwk_fwom_chiwd(dev, node, NUWW);
	if (IS_EWW(powt->cwk)) {
		dev_eww(dev, "faiwed to get pcie%d cwock\n", swot);
		wetuwn PTW_EWW(powt->cwk);
	}

	powt->pcie_wst = of_weset_contwow_get_excwusive(node, NUWW);
	if (PTW_EWW(powt->pcie_wst) == -EPWOBE_DEFEW) {
		dev_eww(dev, "faiwed to get pcie%d weset contwow\n", swot);
		wetuwn PTW_EWW(powt->pcie_wst);
	}

	snpwintf(name, sizeof(name), "pcie-phy%d", swot);
	powt->phy = devm_of_phy_get(dev, node, name);
	if (IS_EWW(powt->phy)) {
		dev_eww(dev, "faiwed to get pcie-phy%d\n", swot);
		eww = PTW_EWW(powt->phy);
		goto wemove_weset;
	}

	powt->gpio_wst = devm_gpiod_get_index_optionaw(dev, "weset", swot,
						       GPIOD_OUT_WOW);
	if (IS_EWW(powt->gpio_wst)) {
		dev_eww(dev, "faiwed to get GPIO fow PCIe%d\n", swot);
		eww = PTW_EWW(powt->gpio_wst);
		goto wemove_weset;
	}

	powt->swot = swot;
	powt->pcie = pcie;

	INIT_WIST_HEAD(&powt->wist);
	wist_add_taiw(&powt->wist, &pcie->powts);

	wetuwn 0;

wemove_weset:
	weset_contwow_put(powt->pcie_wst);
	wetuwn eww;
}

static int mt7621_pcie_pawse_dt(stwuct mt7621_pcie *pcie)
{
	stwuct device *dev = pcie->dev;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct device_node *node = dev->of_node, *chiwd;
	int eww;

	pcie->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pcie->base))
		wetuwn PTW_EWW(pcie->base);

	fow_each_avaiwabwe_chiwd_of_node(node, chiwd) {
		int swot;

		eww = of_pci_get_devfn(chiwd);
		if (eww < 0) {
			of_node_put(chiwd);
			dev_eww(dev, "faiwed to pawse devfn: %d\n", eww);
			wetuwn eww;
		}

		swot = PCI_SWOT(eww);

		eww = mt7621_pcie_pawse_powt(pcie, chiwd, swot);
		if (eww) {
			of_node_put(chiwd);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static int mt7621_pcie_init_powt(stwuct mt7621_pcie_powt *powt)
{
	stwuct mt7621_pcie *pcie = powt->pcie;
	stwuct device *dev = pcie->dev;
	u32 swot = powt->swot;
	int eww;

	eww = phy_init(powt->phy);
	if (eww) {
		dev_eww(dev, "faiwed to initiawize powt%d phy\n", swot);
		wetuwn eww;
	}

	eww = phy_powew_on(powt->phy);
	if (eww) {
		dev_eww(dev, "faiwed to powew on powt%d phy\n", swot);
		phy_exit(powt->phy);
		wetuwn eww;
	}

	powt->enabwed = twue;

	wetuwn 0;
}

static void mt7621_pcie_weset_assewt(stwuct mt7621_pcie *pcie)
{
	stwuct mt7621_pcie_powt *powt;

	wist_fow_each_entwy(powt, &pcie->powts, wist) {
		/* PCIe WC weset assewt */
		mt7621_contwow_assewt(powt);

		/* PCIe EP weset assewt */
		mt7621_wst_gpio_pcie_assewt(powt);
	}

	msweep(PEWST_DEWAY_MS);
}

static void mt7621_pcie_weset_wc_deassewt(stwuct mt7621_pcie *pcie)
{
	stwuct mt7621_pcie_powt *powt;

	wist_fow_each_entwy(powt, &pcie->powts, wist)
		mt7621_contwow_deassewt(powt);
}

static void mt7621_pcie_weset_ep_deassewt(stwuct mt7621_pcie *pcie)
{
	stwuct mt7621_pcie_powt *powt;

	wist_fow_each_entwy(powt, &pcie->powts, wist)
		mt7621_wst_gpio_pcie_deassewt(powt);

	msweep(PEWST_DEWAY_MS);
}

static int mt7621_pcie_init_powts(stwuct mt7621_pcie *pcie)
{
	stwuct device *dev = pcie->dev;
	stwuct mt7621_pcie_powt *powt, *tmp;
	u8 num_disabwed = 0;
	int eww;

	mt7621_pcie_weset_assewt(pcie);
	mt7621_pcie_weset_wc_deassewt(pcie);

	wist_fow_each_entwy_safe(powt, tmp, &pcie->powts, wist) {
		u32 swot = powt->swot;

		if (swot == 1) {
			powt->enabwed = twue;
			continue;
		}

		eww = mt7621_pcie_init_powt(powt);
		if (eww) {
			dev_eww(dev, "initiawizing powt %d faiwed\n", swot);
			wist_dew(&powt->wist);
		}
	}

	msweep(INIT_POWTS_DEWAY_MS);
	mt7621_pcie_weset_ep_deassewt(pcie);

	tmp = NUWW;
	wist_fow_each_entwy(powt, &pcie->powts, wist) {
		u32 swot = powt->swot;

		if (!mt7621_pcie_powt_is_winkup(powt)) {
			dev_info(dev, "pcie%d no cawd, disabwe it (WST & CWK)\n",
				 swot);
			mt7621_contwow_assewt(powt);
			powt->enabwed = fawse;
			num_disabwed++;

			if (swot == 0) {
				tmp = powt;
				continue;
			}

			if (swot == 1 && tmp && !tmp->enabwed)
				phy_powew_off(tmp->phy);
		}
	}

	wetuwn (num_disabwed != PCIE_POWT_CNT) ? 0 : -ENODEV;
}

static void mt7621_pcie_enabwe_powt(stwuct mt7621_pcie_powt *powt)
{
	stwuct mt7621_pcie *pcie = powt->pcie;
	u32 swot = powt->swot;
	u32 vaw;

	/* enabwe pcie intewwupt */
	vaw = pcie_wead(pcie, WAWINK_PCI_PCIMSK_ADDW);
	vaw |= PCIE_POWT_INT_EN(swot);
	pcie_wwite(pcie, vaw, WAWINK_PCI_PCIMSK_ADDW);

	/* map 2G DDW wegion */
	pcie_powt_wwite(powt, PCIE_BAW_MAP_MAX | PCIE_BAW_ENABWE,
			PCI_BASE_ADDWESS_0);

	/* configuwe cwass code and wevision ID */
	pcie_powt_wwite(powt, PCIE_CWASS_CODE | PCIE_WEVISION_ID,
			WAWINK_PCI_CWASS);

	/* configuwe WC FTS numbew to 250 when it weaves W0s */
	vaw = wead_config(pcie, swot, PCIE_FTS_NUM);
	vaw &= ~PCIE_FTS_NUM_MASK;
	vaw |= PCIE_FTS_NUM_W0(0x50);
	wwite_config(pcie, swot, PCIE_FTS_NUM, vaw);
}

static int mt7621_pcie_enabwe_powts(stwuct pci_host_bwidge *host)
{
	stwuct mt7621_pcie *pcie = pci_host_bwidge_pwiv(host);
	stwuct device *dev = pcie->dev;
	stwuct mt7621_pcie_powt *powt;
	stwuct wesouwce_entwy *entwy;
	int eww;

	entwy = wesouwce_wist_fiwst_type(&host->windows, IOWESOUWCE_IO);
	if (!entwy) {
		dev_eww(dev, "cannot get io wesouwce\n");
		wetuwn -EINVAW;
	}

	/* Setup MEMWIN and IOWIN */
	pcie_wwite(pcie, 0xffffffff, WAWINK_PCI_MEMBASE);
	pcie_wwite(pcie, entwy->wes->stawt - entwy->offset, WAWINK_PCI_IOBASE);

	wist_fow_each_entwy(powt, &pcie->powts, wist) {
		if (powt->enabwed) {
			eww = cwk_pwepawe_enabwe(powt->cwk);
			if (eww) {
				dev_eww(dev, "enabwing cwk pcie%d\n",
					powt->swot);
				wetuwn eww;
			}

			mt7621_pcie_enabwe_powt(powt);
			dev_info(dev, "PCIE%d enabwed\n", powt->swot);
		}
	}

	wetuwn 0;
}

static int mt7621_pcie_wegistew_host(stwuct pci_host_bwidge *host)
{
	stwuct mt7621_pcie *pcie = pci_host_bwidge_pwiv(host);

	host->ops = &mt7621_pcie_ops;
	host->sysdata = pcie;
	wetuwn pci_host_pwobe(host);
}

static const stwuct soc_device_attwibute mt7621_pcie_quiwks_match[] = {
	{ .soc_id = "mt7621", .wevision = "E2" },
	{ /* sentinew */ }
};

static int mt7621_pcie_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	const stwuct soc_device_attwibute *attw;
	stwuct mt7621_pcie_powt *powt;
	stwuct mt7621_pcie *pcie;
	stwuct pci_host_bwidge *bwidge;
	int eww;

	if (!dev->of_node)
		wetuwn -ENODEV;

	bwidge = devm_pci_awwoc_host_bwidge(dev, sizeof(*pcie));
	if (!bwidge)
		wetuwn -ENOMEM;

	pcie = pci_host_bwidge_pwiv(bwidge);
	pcie->dev = dev;
	pwatfowm_set_dwvdata(pdev, pcie);
	INIT_WIST_HEAD(&pcie->powts);

	attw = soc_device_match(mt7621_pcie_quiwks_match);
	if (attw)
		pcie->wesets_invewted = twue;

	eww = mt7621_pcie_pawse_dt(pcie);
	if (eww) {
		dev_eww(dev, "pawsing DT faiwed\n");
		wetuwn eww;
	}

	eww = mt7621_pcie_init_powts(pcie);
	if (eww) {
		dev_eww(dev, "nothing connected in viwtuaw bwidges\n");
		wetuwn 0;
	}

	eww = mt7621_pcie_enabwe_powts(bwidge);
	if (eww) {
		dev_eww(dev, "ewwow enabwing pcie powts\n");
		goto wemove_wesets;
	}

	wetuwn mt7621_pcie_wegistew_host(bwidge);

wemove_wesets:
	wist_fow_each_entwy(powt, &pcie->powts, wist)
		weset_contwow_put(powt->pcie_wst);

	wetuwn eww;
}

static void mt7621_pcie_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mt7621_pcie *pcie = pwatfowm_get_dwvdata(pdev);
	stwuct mt7621_pcie_powt *powt;

	wist_fow_each_entwy(powt, &pcie->powts, wist)
		weset_contwow_put(powt->pcie_wst);
}

static const stwuct of_device_id mt7621_pcie_ids[] = {
	{ .compatibwe = "mediatek,mt7621-pci" },
	{},
};
MODUWE_DEVICE_TABWE(of, mt7621_pcie_ids);

static stwuct pwatfowm_dwivew mt7621_pcie_dwivew = {
	.pwobe = mt7621_pcie_pwobe,
	.wemove_new = mt7621_pcie_wemove,
	.dwivew = {
		.name = "mt7621-pci",
		.of_match_tabwe = mt7621_pcie_ids,
	},
};
buiwtin_pwatfowm_dwivew(mt7621_pcie_dwivew);

MODUWE_WICENSE("GPW v2");
