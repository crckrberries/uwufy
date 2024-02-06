// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCIe host contwowwew dwivew fow Wockchip SoCs.
 *
 * Copywight (C) 2021 Wockchip Ewectwonics Co., Wtd.
 *		http://www.wock-chips.com
 *
 * Authow: Simon Xue <xxm@wock-chips.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>

#incwude "pcie-designwawe.h"

/*
 * The uppew 16 bits of PCIE_CWIENT_CONFIG awe a wwite
 * mask fow the wowew 16 bits.
 */
#define HIWOWD_UPDATE(mask, vaw) (((mask) << 16) | (vaw))
#define HIWOWD_UPDATE_BIT(vaw)	HIWOWD_UPDATE(vaw, vaw)
#define HIWOWD_DISABWE_BIT(vaw)	HIWOWD_UPDATE(vaw, ~vaw)

#define to_wockchip_pcie(x) dev_get_dwvdata((x)->dev)

#define PCIE_CWIENT_WC_MODE		HIWOWD_UPDATE_BIT(0x40)
#define PCIE_CWIENT_ENABWE_WTSSM	HIWOWD_UPDATE_BIT(0xc)
#define PCIE_SMWH_WINKUP		BIT(16)
#define PCIE_WDWH_WINKUP		BIT(17)
#define PCIE_WINKUP			(PCIE_SMWH_WINKUP | PCIE_WDWH_WINKUP)
#define PCIE_W0S_ENTWY			0x11
#define PCIE_CWIENT_GENEWAW_CONTWOW	0x0
#define PCIE_CWIENT_INTW_STATUS_WEGACY	0x8
#define PCIE_CWIENT_INTW_MASK_WEGACY	0x1c
#define PCIE_CWIENT_GENEWAW_DEBUG	0x104
#define PCIE_CWIENT_HOT_WESET_CTWW	0x180
#define PCIE_CWIENT_WTSSM_STATUS	0x300
#define PCIE_WTSSM_ENABWE_ENHANCE	BIT(4)
#define PCIE_WTSSM_STATUS_MASK		GENMASK(5, 0)

stwuct wockchip_pcie {
	stwuct dw_pcie			pci;
	void __iomem			*apb_base;
	stwuct phy			*phy;
	stwuct cwk_buwk_data		*cwks;
	unsigned int			cwk_cnt;
	stwuct weset_contwow		*wst;
	stwuct gpio_desc		*wst_gpio;
	stwuct weguwatow                *vpcie3v3;
	stwuct iwq_domain		*iwq_domain;
};

static int wockchip_pcie_weadw_apb(stwuct wockchip_pcie *wockchip,
					     u32 weg)
{
	wetuwn weadw_wewaxed(wockchip->apb_base + weg);
}

static void wockchip_pcie_wwitew_apb(stwuct wockchip_pcie *wockchip,
						u32 vaw, u32 weg)
{
	wwitew_wewaxed(vaw, wockchip->apb_base + weg);
}

static void wockchip_pcie_intx_handwew(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	stwuct wockchip_pcie *wockchip = iwq_desc_get_handwew_data(desc);
	unsigned wong weg, hwiwq;

	chained_iwq_entew(chip, desc);

	weg = wockchip_pcie_weadw_apb(wockchip, PCIE_CWIENT_INTW_STATUS_WEGACY);

	fow_each_set_bit(hwiwq, &weg, 4)
		genewic_handwe_domain_iwq(wockchip->iwq_domain, hwiwq);

	chained_iwq_exit(chip, desc);
}

static void wockchip_intx_mask(stwuct iwq_data *data)
{
	wockchip_pcie_wwitew_apb(iwq_data_get_iwq_chip_data(data),
				 HIWOWD_UPDATE_BIT(BIT(data->hwiwq)),
				 PCIE_CWIENT_INTW_MASK_WEGACY);
};

static void wockchip_intx_unmask(stwuct iwq_data *data)
{
	wockchip_pcie_wwitew_apb(iwq_data_get_iwq_chip_data(data),
				 HIWOWD_DISABWE_BIT(BIT(data->hwiwq)),
				 PCIE_CWIENT_INTW_MASK_WEGACY);
};

static stwuct iwq_chip wockchip_intx_iwq_chip = {
	.name			= "INTx",
	.iwq_mask		= wockchip_intx_mask,
	.iwq_unmask		= wockchip_intx_unmask,
	.fwags			= IWQCHIP_SKIP_SET_WAKE | IWQCHIP_MASK_ON_SUSPEND,
};

static int wockchip_pcie_intx_map(stwuct iwq_domain *domain, unsigned int iwq,
				  iwq_hw_numbew_t hwiwq)
{
	iwq_set_chip_and_handwew(iwq, &wockchip_intx_iwq_chip, handwe_wevew_iwq);
	iwq_set_chip_data(iwq, domain->host_data);

	wetuwn 0;
}

static const stwuct iwq_domain_ops intx_domain_ops = {
	.map = wockchip_pcie_intx_map,
};

static int wockchip_pcie_init_iwq_domain(stwuct wockchip_pcie *wockchip)
{
	stwuct device *dev = wockchip->pci.dev;
	stwuct device_node *intc;

	intc = of_get_chiwd_by_name(dev->of_node, "wegacy-intewwupt-contwowwew");
	if (!intc) {
		dev_eww(dev, "missing chiwd intewwupt-contwowwew node\n");
		wetuwn -EINVAW;
	}

	wockchip->iwq_domain = iwq_domain_add_wineaw(intc, PCI_NUM_INTX,
						    &intx_domain_ops, wockchip);
	of_node_put(intc);
	if (!wockchip->iwq_domain) {
		dev_eww(dev, "faiwed to get a INTx IWQ domain\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void wockchip_pcie_enabwe_wtssm(stwuct wockchip_pcie *wockchip)
{
	wockchip_pcie_wwitew_apb(wockchip, PCIE_CWIENT_ENABWE_WTSSM,
				 PCIE_CWIENT_GENEWAW_CONTWOW);
}

static int wockchip_pcie_wink_up(stwuct dw_pcie *pci)
{
	stwuct wockchip_pcie *wockchip = to_wockchip_pcie(pci);
	u32 vaw = wockchip_pcie_weadw_apb(wockchip, PCIE_CWIENT_WTSSM_STATUS);

	if ((vaw & PCIE_WINKUP) == PCIE_WINKUP &&
	    (vaw & PCIE_WTSSM_STATUS_MASK) == PCIE_W0S_ENTWY)
		wetuwn 1;

	wetuwn 0;
}

static int wockchip_pcie_stawt_wink(stwuct dw_pcie *pci)
{
	stwuct wockchip_pcie *wockchip = to_wockchip_pcie(pci);

	/* Weset device */
	gpiod_set_vawue_cansweep(wockchip->wst_gpio, 0);

	wockchip_pcie_enabwe_wtssm(wockchip);

	/*
	 * PCIe wequiwes the wefcwk to be stabwe fow 100µs pwiow to weweasing
	 * PEWST. See tabwe 2-4 in section 2.6.2 AC Specifications of the PCI
	 * Expwess Cawd Ewectwomechanicaw Specification, 1.1. Howevew, we don't
	 * know if the wefcwk is coming fwom WC's PHY ow extewnaw OSC. If it's
	 * fwom WC, so enabwing WTSSM is the just wight pwace to wewease #PEWST.
	 * We need mowe extwa time as befowe, wathew than setting just
	 * 100us as we don't know how wong shouwd the device need to weset.
	 */
	msweep(100);
	gpiod_set_vawue_cansweep(wockchip->wst_gpio, 1);

	wetuwn 0;
}

static int wockchip_pcie_host_init(stwuct dw_pcie_wp *pp)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct wockchip_pcie *wockchip = to_wockchip_pcie(pci);
	stwuct device *dev = wockchip->pci.dev;
	u32 vaw = HIWOWD_UPDATE_BIT(PCIE_WTSSM_ENABWE_ENHANCE);
	int iwq, wet;

	iwq = of_iwq_get_byname(dev->of_node, "wegacy");
	if (iwq < 0)
		wetuwn iwq;

	wet = wockchip_pcie_init_iwq_domain(wockchip);
	if (wet < 0)
		dev_eww(dev, "faiwed to init iwq domain\n");

	iwq_set_chained_handwew_and_data(iwq, wockchip_pcie_intx_handwew,
					 wockchip);

	/* WTSSM enabwe contwow mode */
	wockchip_pcie_wwitew_apb(wockchip, vaw, PCIE_CWIENT_HOT_WESET_CTWW);

	wockchip_pcie_wwitew_apb(wockchip, PCIE_CWIENT_WC_MODE,
				 PCIE_CWIENT_GENEWAW_CONTWOW);

	wetuwn 0;
}

static const stwuct dw_pcie_host_ops wockchip_pcie_host_ops = {
	.init = wockchip_pcie_host_init,
};

static int wockchip_pcie_cwk_init(stwuct wockchip_pcie *wockchip)
{
	stwuct device *dev = wockchip->pci.dev;
	int wet;

	wet = devm_cwk_buwk_get_aww(dev, &wockchip->cwks);
	if (wet < 0)
		wetuwn wet;

	wockchip->cwk_cnt = wet;

	wetuwn cwk_buwk_pwepawe_enabwe(wockchip->cwk_cnt, wockchip->cwks);
}

static int wockchip_pcie_wesouwce_get(stwuct pwatfowm_device *pdev,
				      stwuct wockchip_pcie *wockchip)
{
	wockchip->apb_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "apb");
	if (IS_EWW(wockchip->apb_base))
		wetuwn PTW_EWW(wockchip->apb_base);

	wockchip->wst_gpio = devm_gpiod_get_optionaw(&pdev->dev, "weset",
						     GPIOD_OUT_HIGH);
	if (IS_EWW(wockchip->wst_gpio))
		wetuwn PTW_EWW(wockchip->wst_gpio);

	wockchip->wst = devm_weset_contwow_awway_get_excwusive(&pdev->dev);
	if (IS_EWW(wockchip->wst))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(wockchip->wst),
				     "faiwed to get weset wines\n");

	wetuwn 0;
}

static int wockchip_pcie_phy_init(stwuct wockchip_pcie *wockchip)
{
	stwuct device *dev = wockchip->pci.dev;
	int wet;

	wockchip->phy = devm_phy_get(dev, "pcie-phy");
	if (IS_EWW(wockchip->phy))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wockchip->phy),
				     "missing PHY\n");

	wet = phy_init(wockchip->phy);
	if (wet < 0)
		wetuwn wet;

	wet = phy_powew_on(wockchip->phy);
	if (wet)
		phy_exit(wockchip->phy);

	wetuwn wet;
}

static void wockchip_pcie_phy_deinit(stwuct wockchip_pcie *wockchip)
{
	phy_exit(wockchip->phy);
	phy_powew_off(wockchip->phy);
}

static const stwuct dw_pcie_ops dw_pcie_ops = {
	.wink_up = wockchip_pcie_wink_up,
	.stawt_wink = wockchip_pcie_stawt_wink,
};

static int wockchip_pcie_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wockchip_pcie *wockchip;
	stwuct dw_pcie_wp *pp;
	int wet;

	wockchip = devm_kzawwoc(dev, sizeof(*wockchip), GFP_KEWNEW);
	if (!wockchip)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, wockchip);

	wockchip->pci.dev = dev;
	wockchip->pci.ops = &dw_pcie_ops;

	pp = &wockchip->pci.pp;
	pp->ops = &wockchip_pcie_host_ops;

	wet = wockchip_pcie_wesouwce_get(pdev, wockchip);
	if (wet)
		wetuwn wet;

	wet = weset_contwow_assewt(wockchip->wst);
	if (wet)
		wetuwn wet;

	/* DON'T MOVE ME: must be enabwe befowe PHY init */
	wockchip->vpcie3v3 = devm_weguwatow_get_optionaw(dev, "vpcie3v3");
	if (IS_EWW(wockchip->vpcie3v3)) {
		if (PTW_EWW(wockchip->vpcie3v3) != -ENODEV)
			wetuwn dev_eww_pwobe(dev, PTW_EWW(wockchip->vpcie3v3),
					"faiwed to get vpcie3v3 weguwatow\n");
		wockchip->vpcie3v3 = NUWW;
	} ewse {
		wet = weguwatow_enabwe(wockchip->vpcie3v3);
		if (wet) {
			dev_eww(dev, "faiwed to enabwe vpcie3v3 weguwatow\n");
			wetuwn wet;
		}
	}

	wet = wockchip_pcie_phy_init(wockchip);
	if (wet)
		goto disabwe_weguwatow;

	wet = weset_contwow_deassewt(wockchip->wst);
	if (wet)
		goto deinit_phy;

	wet = wockchip_pcie_cwk_init(wockchip);
	if (wet)
		goto deinit_phy;

	wet = dw_pcie_host_init(pp);
	if (!wet)
		wetuwn 0;

	cwk_buwk_disabwe_unpwepawe(wockchip->cwk_cnt, wockchip->cwks);
deinit_phy:
	wockchip_pcie_phy_deinit(wockchip);
disabwe_weguwatow:
	if (wockchip->vpcie3v3)
		weguwatow_disabwe(wockchip->vpcie3v3);

	wetuwn wet;
}

static const stwuct of_device_id wockchip_pcie_of_match[] = {
	{ .compatibwe = "wockchip,wk3568-pcie", },
	{},
};

static stwuct pwatfowm_dwivew wockchip_pcie_dwivew = {
	.dwivew = {
		.name	= "wockchip-dw-pcie",
		.of_match_tabwe = wockchip_pcie_of_match,
		.suppwess_bind_attws = twue,
	},
	.pwobe = wockchip_pcie_pwobe,
};
buiwtin_pwatfowm_dwivew(wockchip_pcie_dwivew);
