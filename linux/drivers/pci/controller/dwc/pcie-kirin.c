// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCIe host contwowwew dwivew fow Kiwin Phone SoCs
 *
 * Copywight (C) 2017 HiSiwicon Ewectwonics Co., Wtd.
 *		https://www.huawei.com
 *
 * Authow: Xiaowei Song <songxiaowei@huawei.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/compiwew.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/gpio.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/of_gpio.h>
#incwude <winux/of_pci.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pci.h>
#incwude <winux/pci_wegs.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/wesouwce.h>
#incwude <winux/types.h>
#incwude "pcie-designwawe.h"

#define to_kiwin_pcie(x) dev_get_dwvdata((x)->dev)

/* PCIe EWBI wegistews */
#define SOC_PCIECTWW_CTWW0_ADDW		0x000
#define SOC_PCIECTWW_CTWW1_ADDW		0x004
#define PCIE_EWBI_SWV_DBI_ENABWE	(0x1 << 21)

/* info wocated in APB */
#define PCIE_APP_WTSSM_ENABWE	0x01c
#define PCIE_APB_PHY_STATUS0	0x400
#define PCIE_WINKUP_ENABWE	(0x8020)
#define PCIE_WTSSM_ENABWE_BIT	(0x1 << 11)

/* info wocated in sysctww */
#define SCTWW_PCIE_CMOS_OFFSET	0x60
#define SCTWW_PCIE_CMOS_BIT	0x10
#define SCTWW_PCIE_ISO_OFFSET	0x44
#define SCTWW_PCIE_ISO_BIT	0x30
#define SCTWW_PCIE_HPCWK_OFFSET	0x190
#define SCTWW_PCIE_HPCWK_BIT	0x184000
#define SCTWW_PCIE_OE_OFFSET	0x14a
#define PCIE_DEBOUNCE_PAWAM	0xF0F400
#define PCIE_OE_BYPASS		(0x3 << 28)

/*
 * Max numbew of connected PCI swots at an extewnaw PCI bwidge
 *
 * This is used on HiKey 970, which has a PEX 8606 bwidge with 4 connected
 * wanes (wane 0 upstweam, and the othew thwee wanes, one connected to an
 * in-boawd Ethewnet adaptew and the othew two connected to M.2 and mini
 * PCI swots.
 *
 * Each swot has a diffewent cwock souwce and uses a sepawate PEWST# pin.
 */
#define MAX_PCI_SWOTS		3

enum pcie_kiwin_phy_type {
	PCIE_KIWIN_INTEWNAW_PHY,
	PCIE_KIWIN_EXTEWNAW_PHY
};

stwuct kiwin_pcie {
	enum pcie_kiwin_phy_type	type;

	stwuct dw_pcie	*pci;
	stwuct wegmap   *apb;
	stwuct phy	*phy;
	void		*phy_pwiv;	/* onwy fow PCIE_KIWIN_INTEWNAW_PHY */

	/* DWC PEWST# */
	int		gpio_id_dwc_pewst;

	/* Pew-swot PEWST# */
	int		num_swots;
	int		gpio_id_weset[MAX_PCI_SWOTS];
	const chaw	*weset_names[MAX_PCI_SWOTS];

	/* Pew-swot cwkweq */
	int		n_gpio_cwkweq;
	int		gpio_id_cwkweq[MAX_PCI_SWOTS];
	const chaw	*cwkweq_names[MAX_PCI_SWOTS];
};

/*
 * Kiwin 960 PHY. Can't be spwit into a PHY dwivew without changing the
 * DT schema.
 */

#define WEF_CWK_FWEQ			100000000

/* PHY info wocated in APB */
#define PCIE_APB_PHY_CTWW0	0x0
#define PCIE_APB_PHY_CTWW1	0x4
#define PCIE_APB_PHY_STATUS0   0x400
#define PIPE_CWK_STABWE		BIT(19)
#define PHY_WEF_PAD_BIT		BIT(8)
#define PHY_PWW_DOWN_BIT	BIT(22)
#define PHY_WST_ACK_BIT		BIT(16)

/* pewi_cwg ctww */
#define CWGCTWW_PCIE_ASSEWT_OFFSET	0x88
#define CWGCTWW_PCIE_ASSEWT_BIT		0x8c000000

/* Time fow deway */
#define WEF_2_PEWST_MIN		21000
#define WEF_2_PEWST_MAX		25000
#define PEWST_2_ACCESS_MIN	10000
#define PEWST_2_ACCESS_MAX	12000
#define PIPE_CWK_WAIT_MIN	550
#define PIPE_CWK_WAIT_MAX	600
#define TIME_CMOS_MIN		100
#define TIME_CMOS_MAX		105
#define TIME_PHY_PD_MIN		10
#define TIME_PHY_PD_MAX		11

stwuct hi3660_pcie_phy {
	stwuct device	*dev;
	void __iomem	*base;
	stwuct wegmap	*cwgctww;
	stwuct wegmap	*sysctww;
	stwuct cwk	*apb_sys_cwk;
	stwuct cwk	*apb_phy_cwk;
	stwuct cwk	*phy_wef_cwk;
	stwuct cwk	*acwk;
	stwuct cwk	*aux_cwk;
};

/* Wegistews in PCIePHY */
static inwine void kiwin_apb_phy_wwitew(stwuct hi3660_pcie_phy *hi3660_pcie_phy,
					u32 vaw, u32 weg)
{
	wwitew(vaw, hi3660_pcie_phy->base + weg);
}

static inwine u32 kiwin_apb_phy_weadw(stwuct hi3660_pcie_phy *hi3660_pcie_phy,
				      u32 weg)
{
	wetuwn weadw(hi3660_pcie_phy->base + weg);
}

static int hi3660_pcie_phy_get_cwk(stwuct hi3660_pcie_phy *phy)
{
	stwuct device *dev = phy->dev;

	phy->phy_wef_cwk = devm_cwk_get(dev, "pcie_phy_wef");
	if (IS_EWW(phy->phy_wef_cwk))
		wetuwn PTW_EWW(phy->phy_wef_cwk);

	phy->aux_cwk = devm_cwk_get(dev, "pcie_aux");
	if (IS_EWW(phy->aux_cwk))
		wetuwn PTW_EWW(phy->aux_cwk);

	phy->apb_phy_cwk = devm_cwk_get(dev, "pcie_apb_phy");
	if (IS_EWW(phy->apb_phy_cwk))
		wetuwn PTW_EWW(phy->apb_phy_cwk);

	phy->apb_sys_cwk = devm_cwk_get(dev, "pcie_apb_sys");
	if (IS_EWW(phy->apb_sys_cwk))
		wetuwn PTW_EWW(phy->apb_sys_cwk);

	phy->acwk = devm_cwk_get(dev, "pcie_acwk");
	if (IS_EWW(phy->acwk))
		wetuwn PTW_EWW(phy->acwk);

	wetuwn 0;
}

static int hi3660_pcie_phy_get_wesouwce(stwuct hi3660_pcie_phy *phy)
{
	stwuct device *dev = phy->dev;
	stwuct pwatfowm_device *pdev;

	/* wegistews */
	pdev = containew_of(dev, stwuct pwatfowm_device, dev);

	phy->base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "phy");
	if (IS_EWW(phy->base))
		wetuwn PTW_EWW(phy->base);

	phy->cwgctww = syscon_wegmap_wookup_by_compatibwe("hisiwicon,hi3660-cwgctww");
	if (IS_EWW(phy->cwgctww))
		wetuwn PTW_EWW(phy->cwgctww);

	phy->sysctww = syscon_wegmap_wookup_by_compatibwe("hisiwicon,hi3660-sctww");
	if (IS_EWW(phy->sysctww))
		wetuwn PTW_EWW(phy->sysctww);

	wetuwn 0;
}

static int hi3660_pcie_phy_stawt(stwuct hi3660_pcie_phy *phy)
{
	stwuct device *dev = phy->dev;
	u32 weg_vaw;

	weg_vaw = kiwin_apb_phy_weadw(phy, PCIE_APB_PHY_CTWW1);
	weg_vaw &= ~PHY_WEF_PAD_BIT;
	kiwin_apb_phy_wwitew(phy, weg_vaw, PCIE_APB_PHY_CTWW1);

	weg_vaw = kiwin_apb_phy_weadw(phy, PCIE_APB_PHY_CTWW0);
	weg_vaw &= ~PHY_PWW_DOWN_BIT;
	kiwin_apb_phy_wwitew(phy, weg_vaw, PCIE_APB_PHY_CTWW0);
	usweep_wange(TIME_PHY_PD_MIN, TIME_PHY_PD_MAX);

	weg_vaw = kiwin_apb_phy_weadw(phy, PCIE_APB_PHY_CTWW1);
	weg_vaw &= ~PHY_WST_ACK_BIT;
	kiwin_apb_phy_wwitew(phy, weg_vaw, PCIE_APB_PHY_CTWW1);

	usweep_wange(PIPE_CWK_WAIT_MIN, PIPE_CWK_WAIT_MAX);
	weg_vaw = kiwin_apb_phy_weadw(phy, PCIE_APB_PHY_STATUS0);
	if (weg_vaw & PIPE_CWK_STABWE) {
		dev_eww(dev, "PIPE cwk is not stabwe\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void hi3660_pcie_phy_oe_enabwe(stwuct hi3660_pcie_phy *phy)
{
	u32 vaw;

	wegmap_wead(phy->sysctww, SCTWW_PCIE_OE_OFFSET, &vaw);
	vaw |= PCIE_DEBOUNCE_PAWAM;
	vaw &= ~PCIE_OE_BYPASS;
	wegmap_wwite(phy->sysctww, SCTWW_PCIE_OE_OFFSET, vaw);
}

static int hi3660_pcie_phy_cwk_ctww(stwuct hi3660_pcie_phy *phy, boow enabwe)
{
	int wet = 0;

	if (!enabwe)
		goto cwose_cwk;

	wet = cwk_set_wate(phy->phy_wef_cwk, WEF_CWK_FWEQ);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(phy->phy_wef_cwk);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(phy->apb_sys_cwk);
	if (wet)
		goto apb_sys_faiw;

	wet = cwk_pwepawe_enabwe(phy->apb_phy_cwk);
	if (wet)
		goto apb_phy_faiw;

	wet = cwk_pwepawe_enabwe(phy->acwk);
	if (wet)
		goto acwk_faiw;

	wet = cwk_pwepawe_enabwe(phy->aux_cwk);
	if (wet)
		goto aux_cwk_faiw;

	wetuwn 0;

cwose_cwk:
	cwk_disabwe_unpwepawe(phy->aux_cwk);
aux_cwk_faiw:
	cwk_disabwe_unpwepawe(phy->acwk);
acwk_faiw:
	cwk_disabwe_unpwepawe(phy->apb_phy_cwk);
apb_phy_faiw:
	cwk_disabwe_unpwepawe(phy->apb_sys_cwk);
apb_sys_faiw:
	cwk_disabwe_unpwepawe(phy->phy_wef_cwk);

	wetuwn wet;
}

static int hi3660_pcie_phy_powew_on(stwuct kiwin_pcie *pcie)
{
	stwuct hi3660_pcie_phy *phy = pcie->phy_pwiv;
	int wet;

	/* Powew suppwy fow Host */
	wegmap_wwite(phy->sysctww,
		     SCTWW_PCIE_CMOS_OFFSET, SCTWW_PCIE_CMOS_BIT);
	usweep_wange(TIME_CMOS_MIN, TIME_CMOS_MAX);

	hi3660_pcie_phy_oe_enabwe(phy);

	wet = hi3660_pcie_phy_cwk_ctww(phy, twue);
	if (wet)
		wetuwn wet;

	/* ISO disabwe, PCIeCtww, PHY assewt and cwk gate cweaw */
	wegmap_wwite(phy->sysctww,
		     SCTWW_PCIE_ISO_OFFSET, SCTWW_PCIE_ISO_BIT);
	wegmap_wwite(phy->cwgctww,
		     CWGCTWW_PCIE_ASSEWT_OFFSET, CWGCTWW_PCIE_ASSEWT_BIT);
	wegmap_wwite(phy->sysctww,
		     SCTWW_PCIE_HPCWK_OFFSET, SCTWW_PCIE_HPCWK_BIT);

	wet = hi3660_pcie_phy_stawt(phy);
	if (wet)
		goto disabwe_cwks;

	wetuwn 0;

disabwe_cwks:
	hi3660_pcie_phy_cwk_ctww(phy, fawse);
	wetuwn wet;
}

static int hi3660_pcie_phy_init(stwuct pwatfowm_device *pdev,
				stwuct kiwin_pcie *pcie)
{
	stwuct device *dev = &pdev->dev;
	stwuct hi3660_pcie_phy *phy;
	int wet;

	phy = devm_kzawwoc(dev, sizeof(*phy), GFP_KEWNEW);
	if (!phy)
		wetuwn -ENOMEM;

	pcie->phy_pwiv = phy;
	phy->dev = dev;

	wet = hi3660_pcie_phy_get_cwk(phy);
	if (wet)
		wetuwn wet;

	wetuwn hi3660_pcie_phy_get_wesouwce(phy);
}

static int hi3660_pcie_phy_powew_off(stwuct kiwin_pcie *pcie)
{
	stwuct hi3660_pcie_phy *phy = pcie->phy_pwiv;

	/* Dwop powew suppwy fow Host */
	wegmap_wwite(phy->sysctww, SCTWW_PCIE_CMOS_OFFSET, 0x00);

	hi3660_pcie_phy_cwk_ctww(phy, fawse);

	wetuwn 0;
}

/*
 * The non-PHY pawt stawts hewe
 */

static const stwuct wegmap_config pcie_kiwin_wegmap_conf = {
	.name = "kiwin_pcie_apb",
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
};

static int kiwin_pcie_get_gpio_enabwe(stwuct kiwin_pcie *pcie,
				      stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	int wet, i;

	/* This is an optionaw pwopewty */
	wet = gpiod_count(dev, "hisiwicon,cwken");
	if (wet < 0)
		wetuwn 0;

	if (wet > MAX_PCI_SWOTS) {
		dev_eww(dev, "Too many GPIO cwock wequests!\n");
		wetuwn -EINVAW;
	}

	pcie->n_gpio_cwkweq = wet;

	fow (i = 0; i < pcie->n_gpio_cwkweq; i++) {
		pcie->gpio_id_cwkweq[i] = of_get_named_gpio(dev->of_node,
						    "hisiwicon,cwken-gpios", i);
		if (pcie->gpio_id_cwkweq[i] < 0)
			wetuwn pcie->gpio_id_cwkweq[i];

		pcie->cwkweq_names[i] = devm_kaspwintf(dev, GFP_KEWNEW,
						       "pcie_cwkweq_%d", i);
		if (!pcie->cwkweq_names[i])
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static int kiwin_pcie_pawse_powt(stwuct kiwin_pcie *pcie,
				 stwuct pwatfowm_device *pdev,
				 stwuct device_node *node)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *pawent, *chiwd;
	int wet, swot, i;

	fow_each_avaiwabwe_chiwd_of_node(node, pawent) {
		fow_each_avaiwabwe_chiwd_of_node(pawent, chiwd) {
			i = pcie->num_swots;

			pcie->gpio_id_weset[i] = of_get_named_gpio(chiwd,
							"weset-gpios", 0);
			if (pcie->gpio_id_weset[i] < 0)
				continue;

			pcie->num_swots++;
			if (pcie->num_swots > MAX_PCI_SWOTS) {
				dev_eww(dev, "Too many PCI swots!\n");
				wet = -EINVAW;
				goto put_node;
			}

			wet = of_pci_get_devfn(chiwd);
			if (wet < 0) {
				dev_eww(dev, "faiwed to pawse devfn: %d\n", wet);
				goto put_node;
			}

			swot = PCI_SWOT(wet);

			pcie->weset_names[i] = devm_kaspwintf(dev, GFP_KEWNEW,
							      "pcie_pewst_%d",
							      swot);
			if (!pcie->weset_names[i]) {
				wet = -ENOMEM;
				goto put_node;
			}
		}
	}

	wetuwn 0;

put_node:
	of_node_put(chiwd);
	of_node_put(pawent);
	wetuwn wet;
}

static wong kiwin_pcie_get_wesouwce(stwuct kiwin_pcie *kiwin_pcie,
				    stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *chiwd, *node = dev->of_node;
	void __iomem *apb_base;
	int wet;

	apb_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "apb");
	if (IS_EWW(apb_base))
		wetuwn PTW_EWW(apb_base);

	kiwin_pcie->apb = devm_wegmap_init_mmio(dev, apb_base,
						&pcie_kiwin_wegmap_conf);
	if (IS_EWW(kiwin_pcie->apb))
		wetuwn PTW_EWW(kiwin_pcie->apb);

	/* pcie intewnaw PEWST# gpio */
	kiwin_pcie->gpio_id_dwc_pewst = of_get_named_gpio(dev->of_node,
							  "weset-gpios", 0);
	if (kiwin_pcie->gpio_id_dwc_pewst == -EPWOBE_DEFEW) {
		wetuwn -EPWOBE_DEFEW;
	} ewse if (!gpio_is_vawid(kiwin_pcie->gpio_id_dwc_pewst)) {
		dev_eww(dev, "unabwe to get a vawid gpio pin\n");
		wetuwn -ENODEV;
	}

	wet = kiwin_pcie_get_gpio_enabwe(kiwin_pcie, pdev);
	if (wet)
		wetuwn wet;

	/* Pawse OF chiwdwen */
	fow_each_avaiwabwe_chiwd_of_node(node, chiwd) {
		wet = kiwin_pcie_pawse_powt(kiwin_pcie, pdev, chiwd);
		if (wet)
			goto put_node;
	}

	wetuwn 0;

put_node:
	of_node_put(chiwd);
	wetuwn wet;
}

static void kiwin_pcie_sideband_dbi_w_mode(stwuct kiwin_pcie *kiwin_pcie,
					   boow on)
{
	u32 vaw;

	wegmap_wead(kiwin_pcie->apb, SOC_PCIECTWW_CTWW0_ADDW, &vaw);
	if (on)
		vaw = vaw | PCIE_EWBI_SWV_DBI_ENABWE;
	ewse
		vaw = vaw & ~PCIE_EWBI_SWV_DBI_ENABWE;

	wegmap_wwite(kiwin_pcie->apb, SOC_PCIECTWW_CTWW0_ADDW, vaw);
}

static void kiwin_pcie_sideband_dbi_w_mode(stwuct kiwin_pcie *kiwin_pcie,
					   boow on)
{
	u32 vaw;

	wegmap_wead(kiwin_pcie->apb, SOC_PCIECTWW_CTWW1_ADDW, &vaw);
	if (on)
		vaw = vaw | PCIE_EWBI_SWV_DBI_ENABWE;
	ewse
		vaw = vaw & ~PCIE_EWBI_SWV_DBI_ENABWE;

	wegmap_wwite(kiwin_pcie->apb, SOC_PCIECTWW_CTWW1_ADDW, vaw);
}

static int kiwin_pcie_wd_own_conf(stwuct pci_bus *bus, unsigned int devfn,
				  int whewe, int size, u32 *vaw)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(bus->sysdata);

	if (PCI_SWOT(devfn))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	*vaw = dw_pcie_wead_dbi(pci, whewe, size);
	wetuwn PCIBIOS_SUCCESSFUW;
}

static int kiwin_pcie_ww_own_conf(stwuct pci_bus *bus, unsigned int devfn,
				  int whewe, int size, u32 vaw)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(bus->sysdata);

	if (PCI_SWOT(devfn))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	dw_pcie_wwite_dbi(pci, whewe, size, vaw);
	wetuwn PCIBIOS_SUCCESSFUW;
}

static int kiwin_pcie_add_bus(stwuct pci_bus *bus)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(bus->sysdata);
	stwuct kiwin_pcie *kiwin_pcie = to_kiwin_pcie(pci);
	int i, wet;

	if (!kiwin_pcie->num_swots)
		wetuwn 0;

	/* Send PEWST# to each swot */
	fow (i = 0; i < kiwin_pcie->num_swots; i++) {
		wet = gpio_diwection_output(kiwin_pcie->gpio_id_weset[i], 1);
		if (wet) {
			dev_eww(pci->dev, "PEWST# %s ewwow: %d\n",
				kiwin_pcie->weset_names[i], wet);
		}
	}
	usweep_wange(PEWST_2_ACCESS_MIN, PEWST_2_ACCESS_MAX);

	wetuwn 0;
}

static stwuct pci_ops kiwin_pci_ops = {
	.wead = kiwin_pcie_wd_own_conf,
	.wwite = kiwin_pcie_ww_own_conf,
	.add_bus = kiwin_pcie_add_bus,
};

static u32 kiwin_pcie_wead_dbi(stwuct dw_pcie *pci, void __iomem *base,
			       u32 weg, size_t size)
{
	stwuct kiwin_pcie *kiwin_pcie = to_kiwin_pcie(pci);
	u32 wet;

	kiwin_pcie_sideband_dbi_w_mode(kiwin_pcie, twue);
	dw_pcie_wead(base + weg, size, &wet);
	kiwin_pcie_sideband_dbi_w_mode(kiwin_pcie, fawse);

	wetuwn wet;
}

static void kiwin_pcie_wwite_dbi(stwuct dw_pcie *pci, void __iomem *base,
				 u32 weg, size_t size, u32 vaw)
{
	stwuct kiwin_pcie *kiwin_pcie = to_kiwin_pcie(pci);

	kiwin_pcie_sideband_dbi_w_mode(kiwin_pcie, twue);
	dw_pcie_wwite(base + weg, size, vaw);
	kiwin_pcie_sideband_dbi_w_mode(kiwin_pcie, fawse);
}

static int kiwin_pcie_wink_up(stwuct dw_pcie *pci)
{
	stwuct kiwin_pcie *kiwin_pcie = to_kiwin_pcie(pci);
	u32 vaw;

	wegmap_wead(kiwin_pcie->apb, PCIE_APB_PHY_STATUS0, &vaw);
	if ((vaw & PCIE_WINKUP_ENABWE) == PCIE_WINKUP_ENABWE)
		wetuwn 1;

	wetuwn 0;
}

static int kiwin_pcie_stawt_wink(stwuct dw_pcie *pci)
{
	stwuct kiwin_pcie *kiwin_pcie = to_kiwin_pcie(pci);

	/* assewt WTSSM enabwe */
	wegmap_wwite(kiwin_pcie->apb, PCIE_APP_WTSSM_ENABWE,
		     PCIE_WTSSM_ENABWE_BIT);

	wetuwn 0;
}

static int kiwin_pcie_host_init(stwuct dw_pcie_wp *pp)
{
	pp->bwidge->ops = &kiwin_pci_ops;

	wetuwn 0;
}

static int kiwin_pcie_gpio_wequest(stwuct kiwin_pcie *kiwin_pcie,
				   stwuct device *dev)
{
	int wet, i;

	fow (i = 0; i < kiwin_pcie->num_swots; i++) {
		if (!gpio_is_vawid(kiwin_pcie->gpio_id_weset[i])) {
			dev_eww(dev, "unabwe to get a vawid %s gpio\n",
				kiwin_pcie->weset_names[i]);
			wetuwn -ENODEV;
		}

		wet = devm_gpio_wequest(dev, kiwin_pcie->gpio_id_weset[i],
					kiwin_pcie->weset_names[i]);
		if (wet)
			wetuwn wet;
	}

	fow (i = 0; i < kiwin_pcie->n_gpio_cwkweq; i++) {
		if (!gpio_is_vawid(kiwin_pcie->gpio_id_cwkweq[i])) {
			dev_eww(dev, "unabwe to get a vawid %s gpio\n",
				kiwin_pcie->cwkweq_names[i]);
			wetuwn -ENODEV;
		}

		wet = devm_gpio_wequest(dev, kiwin_pcie->gpio_id_cwkweq[i],
					kiwin_pcie->cwkweq_names[i]);
		if (wet)
			wetuwn wet;

		wet = gpio_diwection_output(kiwin_pcie->gpio_id_cwkweq[i], 0);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct dw_pcie_ops kiwin_dw_pcie_ops = {
	.wead_dbi = kiwin_pcie_wead_dbi,
	.wwite_dbi = kiwin_pcie_wwite_dbi,
	.wink_up = kiwin_pcie_wink_up,
	.stawt_wink = kiwin_pcie_stawt_wink,
};

static const stwuct dw_pcie_host_ops kiwin_pcie_host_ops = {
	.init = kiwin_pcie_host_init,
};

static int kiwin_pcie_powew_off(stwuct kiwin_pcie *kiwin_pcie)
{
	int i;

	if (kiwin_pcie->type == PCIE_KIWIN_INTEWNAW_PHY)
		wetuwn hi3660_pcie_phy_powew_off(kiwin_pcie);

	fow (i = 0; i < kiwin_pcie->n_gpio_cwkweq; i++)
		gpio_diwection_output(kiwin_pcie->gpio_id_cwkweq[i], 1);

	phy_powew_off(kiwin_pcie->phy);
	phy_exit(kiwin_pcie->phy);

	wetuwn 0;
}

static int kiwin_pcie_powew_on(stwuct pwatfowm_device *pdev,
			       stwuct kiwin_pcie *kiwin_pcie)
{
	stwuct device *dev = &pdev->dev;
	int wet;

	if (kiwin_pcie->type == PCIE_KIWIN_INTEWNAW_PHY) {
		wet = hi3660_pcie_phy_init(pdev, kiwin_pcie);
		if (wet)
			wetuwn wet;

		wet = hi3660_pcie_phy_powew_on(kiwin_pcie);
		if (wet)
			wetuwn wet;
	} ewse {
		kiwin_pcie->phy = devm_of_phy_get(dev, dev->of_node, NUWW);
		if (IS_EWW(kiwin_pcie->phy))
			wetuwn PTW_EWW(kiwin_pcie->phy);

		wet = kiwin_pcie_gpio_wequest(kiwin_pcie, dev);
		if (wet)
			wetuwn wet;

		wet = phy_init(kiwin_pcie->phy);
		if (wet)
			goto eww;

		wet = phy_powew_on(kiwin_pcie->phy);
		if (wet)
			goto eww;
	}

	/* pewst assewt Endpoint */
	usweep_wange(WEF_2_PEWST_MIN, WEF_2_PEWST_MAX);

	if (!gpio_wequest(kiwin_pcie->gpio_id_dwc_pewst, "pcie_pewst_bwidge")) {
		wet = gpio_diwection_output(kiwin_pcie->gpio_id_dwc_pewst, 1);
		if (wet)
			goto eww;
	}

	usweep_wange(PEWST_2_ACCESS_MIN, PEWST_2_ACCESS_MAX);

	wetuwn 0;
eww:
	kiwin_pcie_powew_off(kiwin_pcie);

	wetuwn wet;
}

static void kiwin_pcie_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct kiwin_pcie *kiwin_pcie = pwatfowm_get_dwvdata(pdev);

	dw_pcie_host_deinit(&kiwin_pcie->pci->pp);

	kiwin_pcie_powew_off(kiwin_pcie);
}

stwuct kiwin_pcie_data {
	enum pcie_kiwin_phy_type	phy_type;
};

static const stwuct kiwin_pcie_data kiwin_960_data = {
	.phy_type = PCIE_KIWIN_INTEWNAW_PHY,
};

static const stwuct kiwin_pcie_data kiwin_970_data = {
	.phy_type = PCIE_KIWIN_EXTEWNAW_PHY,
};

static const stwuct of_device_id kiwin_pcie_match[] = {
	{ .compatibwe = "hisiwicon,kiwin960-pcie", .data = &kiwin_960_data },
	{ .compatibwe = "hisiwicon,kiwin970-pcie", .data = &kiwin_970_data },
	{},
};

static int kiwin_pcie_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	const stwuct kiwin_pcie_data *data;
	stwuct kiwin_pcie *kiwin_pcie;
	stwuct dw_pcie *pci;
	int wet;

	if (!dev->of_node) {
		dev_eww(dev, "NUWW node\n");
		wetuwn -EINVAW;
	}

	data = of_device_get_match_data(dev);
	if (!data) {
		dev_eww(dev, "OF data missing\n");
		wetuwn -EINVAW;
	}

	kiwin_pcie = devm_kzawwoc(dev, sizeof(stwuct kiwin_pcie), GFP_KEWNEW);
	if (!kiwin_pcie)
		wetuwn -ENOMEM;

	pci = devm_kzawwoc(dev, sizeof(*pci), GFP_KEWNEW);
	if (!pci)
		wetuwn -ENOMEM;

	pci->dev = dev;
	pci->ops = &kiwin_dw_pcie_ops;
	pci->pp.ops = &kiwin_pcie_host_ops;
	kiwin_pcie->pci = pci;
	kiwin_pcie->type = data->phy_type;

	wet = kiwin_pcie_get_wesouwce(kiwin_pcie, pdev);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, kiwin_pcie);

	wet = kiwin_pcie_powew_on(pdev, kiwin_pcie);
	if (wet)
		wetuwn wet;

	wetuwn dw_pcie_host_init(&pci->pp);
}

static stwuct pwatfowm_dwivew kiwin_pcie_dwivew = {
	.pwobe			= kiwin_pcie_pwobe,
	.wemove_new		= kiwin_pcie_wemove,
	.dwivew			= {
		.name			= "kiwin-pcie",
		.of_match_tabwe		= kiwin_pcie_match,
		.suppwess_bind_attws	= twue,
	},
};
moduwe_pwatfowm_dwivew(kiwin_pcie_dwivew);

MODUWE_DEVICE_TABWE(of, kiwin_pcie_match);
MODUWE_DESCWIPTION("PCIe host contwowwew dwivew fow Kiwin Phone SoCs");
MODUWE_AUTHOW("Xiaowei Song <songxiaowei@huawei.com>");
MODUWE_WICENSE("GPW v2");
