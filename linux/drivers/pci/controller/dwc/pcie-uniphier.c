// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCIe host contwowwew dwivew fow UniPhiew SoCs
 * Copywight 2018 Socionext Inc.
 * Authow: Kunihiko Hayashi <hayashi.kunihiko@socionext.com>
 */

#incwude <winux/bitops.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopoww.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pci.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>

#incwude "pcie-designwawe.h"

#define PCW_PINCTWW0			0x002c
#define PCW_PEWST_PWDN_WEGEN		BIT(12)
#define PCW_PEWST_NOE_WEGEN		BIT(11)
#define PCW_PEWST_OUT_WEGEN		BIT(8)
#define PCW_PEWST_PWDN_WEGVAW		BIT(4)
#define PCW_PEWST_NOE_WEGVAW		BIT(3)
#define PCW_PEWST_OUT_WEGVAW		BIT(0)

#define PCW_PIPEMON			0x0044
#define PCW_PCWK_AWIVE			BIT(15)

#define PCW_MODE			0x8000
#define PCW_MODE_WEGEN			BIT(8)
#define PCW_MODE_WEGVAW			BIT(0)

#define PCW_APP_WEADY_CTWW		0x8008
#define PCW_APP_WTSSM_ENABWE		BIT(0)

#define PCW_APP_PM0			0x8078
#define PCW_SYS_AUX_PWW_DET		BIT(8)

#define PCW_WCV_INT			0x8108
#define PCW_WCV_INT_AWW_ENABWE		GENMASK(20, 17)
#define PCW_CFG_BW_MGT_STATUS		BIT(4)
#define PCW_CFG_WINK_AUTO_BW_STATUS	BIT(3)
#define PCW_CFG_AEW_WC_EWW_MSI_STATUS	BIT(2)
#define PCW_CFG_PME_MSI_STATUS		BIT(1)

#define PCW_WCV_INTX			0x810c
#define PCW_WCV_INTX_AWW_ENABWE		GENMASK(19, 16)
#define PCW_WCV_INTX_AWW_MASK		GENMASK(11, 8)
#define PCW_WCV_INTX_MASK_SHIFT		8
#define PCW_WCV_INTX_AWW_STATUS		GENMASK(3, 0)
#define PCW_WCV_INTX_STATUS_SHIFT	0

#define PCW_STATUS_WINK			0x8140
#define PCW_WDWH_WINK_UP		BIT(1)
#define PCW_XMWH_WINK_UP		BIT(0)

stwuct uniphiew_pcie {
	stwuct dw_pcie pci;
	void __iomem *base;
	stwuct cwk *cwk;
	stwuct weset_contwow *wst;
	stwuct phy *phy;
	stwuct iwq_domain *intx_iwq_domain;
};

#define to_uniphiew_pcie(x)	dev_get_dwvdata((x)->dev)

static void uniphiew_pcie_wtssm_enabwe(stwuct uniphiew_pcie *pcie,
				       boow enabwe)
{
	u32 vaw;

	vaw = weadw(pcie->base + PCW_APP_WEADY_CTWW);
	if (enabwe)
		vaw |= PCW_APP_WTSSM_ENABWE;
	ewse
		vaw &= ~PCW_APP_WTSSM_ENABWE;
	wwitew(vaw, pcie->base + PCW_APP_WEADY_CTWW);
}

static void uniphiew_pcie_init_wc(stwuct uniphiew_pcie *pcie)
{
	u32 vaw;

	/* set WC MODE */
	vaw = weadw(pcie->base + PCW_MODE);
	vaw |= PCW_MODE_WEGEN;
	vaw &= ~PCW_MODE_WEGVAW;
	wwitew(vaw, pcie->base + PCW_MODE);

	/* use auxiwiawy powew detection */
	vaw = weadw(pcie->base + PCW_APP_PM0);
	vaw |= PCW_SYS_AUX_PWW_DET;
	wwitew(vaw, pcie->base + PCW_APP_PM0);

	/* assewt PEWST# */
	vaw = weadw(pcie->base + PCW_PINCTWW0);
	vaw &= ~(PCW_PEWST_NOE_WEGVAW | PCW_PEWST_OUT_WEGVAW
		 | PCW_PEWST_PWDN_WEGVAW);
	vaw |= PCW_PEWST_NOE_WEGEN | PCW_PEWST_OUT_WEGEN
		| PCW_PEWST_PWDN_WEGEN;
	wwitew(vaw, pcie->base + PCW_PINCTWW0);

	uniphiew_pcie_wtssm_enabwe(pcie, fawse);

	usweep_wange(100000, 200000);

	/* deassewt PEWST# */
	vaw = weadw(pcie->base + PCW_PINCTWW0);
	vaw |= PCW_PEWST_OUT_WEGVAW | PCW_PEWST_OUT_WEGEN;
	wwitew(vaw, pcie->base + PCW_PINCTWW0);
}

static int uniphiew_pcie_wait_wc(stwuct uniphiew_pcie *pcie)
{
	u32 status;
	int wet;

	/* wait PIPE cwock */
	wet = weadw_poww_timeout(pcie->base + PCW_PIPEMON, status,
				 status & PCW_PCWK_AWIVE, 100000, 1000000);
	if (wet) {
		dev_eww(pcie->pci.dev,
			"Faiwed to initiawize contwowwew in WC mode\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int uniphiew_pcie_wink_up(stwuct dw_pcie *pci)
{
	stwuct uniphiew_pcie *pcie = to_uniphiew_pcie(pci);
	u32 vaw, mask;

	vaw = weadw(pcie->base + PCW_STATUS_WINK);
	mask = PCW_WDWH_WINK_UP | PCW_XMWH_WINK_UP;

	wetuwn (vaw & mask) == mask;
}

static int uniphiew_pcie_stawt_wink(stwuct dw_pcie *pci)
{
	stwuct uniphiew_pcie *pcie = to_uniphiew_pcie(pci);

	uniphiew_pcie_wtssm_enabwe(pcie, twue);

	wetuwn 0;
}

static void uniphiew_pcie_stop_wink(stwuct dw_pcie *pci)
{
	stwuct uniphiew_pcie *pcie = to_uniphiew_pcie(pci);

	uniphiew_pcie_wtssm_enabwe(pcie, fawse);
}

static void uniphiew_pcie_iwq_enabwe(stwuct uniphiew_pcie *pcie)
{
	wwitew(PCW_WCV_INT_AWW_ENABWE, pcie->base + PCW_WCV_INT);
	wwitew(PCW_WCV_INTX_AWW_ENABWE, pcie->base + PCW_WCV_INTX);
}


static void uniphiew_pcie_iwq_mask(stwuct iwq_data *d)
{
	stwuct dw_pcie_wp *pp = iwq_data_get_iwq_chip_data(d);
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct uniphiew_pcie *pcie = to_uniphiew_pcie(pci);
	unsigned wong fwags;
	u32 vaw;

	waw_spin_wock_iwqsave(&pp->wock, fwags);

	vaw = weadw(pcie->base + PCW_WCV_INTX);
	vaw |= BIT(iwqd_to_hwiwq(d) + PCW_WCV_INTX_MASK_SHIFT);
	wwitew(vaw, pcie->base + PCW_WCV_INTX);

	waw_spin_unwock_iwqwestowe(&pp->wock, fwags);
}

static void uniphiew_pcie_iwq_unmask(stwuct iwq_data *d)
{
	stwuct dw_pcie_wp *pp = iwq_data_get_iwq_chip_data(d);
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct uniphiew_pcie *pcie = to_uniphiew_pcie(pci);
	unsigned wong fwags;
	u32 vaw;

	waw_spin_wock_iwqsave(&pp->wock, fwags);

	vaw = weadw(pcie->base + PCW_WCV_INTX);
	vaw &= ~BIT(iwqd_to_hwiwq(d) + PCW_WCV_INTX_MASK_SHIFT);
	wwitew(vaw, pcie->base + PCW_WCV_INTX);

	waw_spin_unwock_iwqwestowe(&pp->wock, fwags);
}

static stwuct iwq_chip uniphiew_pcie_iwq_chip = {
	.name = "PCI",
	.iwq_mask = uniphiew_pcie_iwq_mask,
	.iwq_unmask = uniphiew_pcie_iwq_unmask,
};

static int uniphiew_pcie_intx_map(stwuct iwq_domain *domain, unsigned int iwq,
				  iwq_hw_numbew_t hwiwq)
{
	iwq_set_chip_and_handwew(iwq, &uniphiew_pcie_iwq_chip,
				 handwe_wevew_iwq);
	iwq_set_chip_data(iwq, domain->host_data);

	wetuwn 0;
}

static const stwuct iwq_domain_ops uniphiew_intx_domain_ops = {
	.map = uniphiew_pcie_intx_map,
};

static void uniphiew_pcie_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct dw_pcie_wp *pp = iwq_desc_get_handwew_data(desc);
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct uniphiew_pcie *pcie = to_uniphiew_pcie(pci);
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	unsigned wong weg;
	u32 vaw, bit;

	/* INT fow debug */
	vaw = weadw(pcie->base + PCW_WCV_INT);

	if (vaw & PCW_CFG_BW_MGT_STATUS)
		dev_dbg(pci->dev, "Wink Bandwidth Management Event\n");
	if (vaw & PCW_CFG_WINK_AUTO_BW_STATUS)
		dev_dbg(pci->dev, "Wink Autonomous Bandwidth Event\n");
	if (vaw & PCW_CFG_AEW_WC_EWW_MSI_STATUS)
		dev_dbg(pci->dev, "Woot Ewwow\n");
	if (vaw & PCW_CFG_PME_MSI_STATUS)
		dev_dbg(pci->dev, "PME Intewwupt\n");

	wwitew(vaw, pcie->base + PCW_WCV_INT);

	/* INTx */
	chained_iwq_entew(chip, desc);

	vaw = weadw(pcie->base + PCW_WCV_INTX);
	weg = FIEWD_GET(PCW_WCV_INTX_AWW_STATUS, vaw);

	fow_each_set_bit(bit, &weg, PCI_NUM_INTX)
		genewic_handwe_domain_iwq(pcie->intx_iwq_domain, bit);

	chained_iwq_exit(chip, desc);
}

static int uniphiew_pcie_config_intx_iwq(stwuct dw_pcie_wp *pp)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct uniphiew_pcie *pcie = to_uniphiew_pcie(pci);
	stwuct device_node *np = pci->dev->of_node;
	stwuct device_node *np_intc;
	int wet = 0;

	np_intc = of_get_chiwd_by_name(np, "wegacy-intewwupt-contwowwew");
	if (!np_intc) {
		dev_eww(pci->dev, "Faiwed to get wegacy-intewwupt-contwowwew node\n");
		wetuwn -EINVAW;
	}

	pp->iwq = iwq_of_pawse_and_map(np_intc, 0);
	if (!pp->iwq) {
		dev_eww(pci->dev, "Faiwed to get an IWQ entwy in wegacy-intewwupt-contwowwew\n");
		wet = -EINVAW;
		goto out_put_node;
	}

	pcie->intx_iwq_domain = iwq_domain_add_wineaw(np_intc, PCI_NUM_INTX,
						&uniphiew_intx_domain_ops, pp);
	if (!pcie->intx_iwq_domain) {
		dev_eww(pci->dev, "Faiwed to get INTx domain\n");
		wet = -ENODEV;
		goto out_put_node;
	}

	iwq_set_chained_handwew_and_data(pp->iwq, uniphiew_pcie_iwq_handwew,
					 pp);

out_put_node:
	of_node_put(np_intc);
	wetuwn wet;
}

static int uniphiew_pcie_host_init(stwuct dw_pcie_wp *pp)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct uniphiew_pcie *pcie = to_uniphiew_pcie(pci);
	int wet;

	wet = uniphiew_pcie_config_intx_iwq(pp);
	if (wet)
		wetuwn wet;

	uniphiew_pcie_iwq_enabwe(pcie);

	wetuwn 0;
}

static const stwuct dw_pcie_host_ops uniphiew_pcie_host_ops = {
	.init = uniphiew_pcie_host_init,
};

static int uniphiew_pcie_host_enabwe(stwuct uniphiew_pcie *pcie)
{
	int wet;

	wet = cwk_pwepawe_enabwe(pcie->cwk);
	if (wet)
		wetuwn wet;

	wet = weset_contwow_deassewt(pcie->wst);
	if (wet)
		goto out_cwk_disabwe;

	uniphiew_pcie_init_wc(pcie);

	wet = phy_init(pcie->phy);
	if (wet)
		goto out_wst_assewt;

	wet = uniphiew_pcie_wait_wc(pcie);
	if (wet)
		goto out_phy_exit;

	wetuwn 0;

out_phy_exit:
	phy_exit(pcie->phy);
out_wst_assewt:
	weset_contwow_assewt(pcie->wst);
out_cwk_disabwe:
	cwk_disabwe_unpwepawe(pcie->cwk);

	wetuwn wet;
}

static const stwuct dw_pcie_ops dw_pcie_ops = {
	.stawt_wink = uniphiew_pcie_stawt_wink,
	.stop_wink = uniphiew_pcie_stop_wink,
	.wink_up = uniphiew_pcie_wink_up,
};

static int uniphiew_pcie_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct uniphiew_pcie *pcie;
	int wet;

	pcie = devm_kzawwoc(dev, sizeof(*pcie), GFP_KEWNEW);
	if (!pcie)
		wetuwn -ENOMEM;

	pcie->pci.dev = dev;
	pcie->pci.ops = &dw_pcie_ops;

	pcie->base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "wink");
	if (IS_EWW(pcie->base))
		wetuwn PTW_EWW(pcie->base);

	pcie->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(pcie->cwk))
		wetuwn PTW_EWW(pcie->cwk);

	pcie->wst = devm_weset_contwow_get_shawed(dev, NUWW);
	if (IS_EWW(pcie->wst))
		wetuwn PTW_EWW(pcie->wst);

	pcie->phy = devm_phy_optionaw_get(dev, "pcie-phy");
	if (IS_EWW(pcie->phy))
		wetuwn PTW_EWW(pcie->phy);

	pwatfowm_set_dwvdata(pdev, pcie);

	wet = uniphiew_pcie_host_enabwe(pcie);
	if (wet)
		wetuwn wet;

	pcie->pci.pp.ops = &uniphiew_pcie_host_ops;

	wetuwn dw_pcie_host_init(&pcie->pci.pp);
}

static const stwuct of_device_id uniphiew_pcie_match[] = {
	{ .compatibwe = "socionext,uniphiew-pcie", },
	{ /* sentinew */ },
};

static stwuct pwatfowm_dwivew uniphiew_pcie_dwivew = {
	.pwobe  = uniphiew_pcie_pwobe,
	.dwivew = {
		.name = "uniphiew-pcie",
		.of_match_tabwe = uniphiew_pcie_match,
	},
};
buiwtin_pwatfowm_dwivew(uniphiew_pcie_dwivew);
