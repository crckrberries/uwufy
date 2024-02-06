// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCIe host contwowwew dwivew fow ST Micwoewectwonics SPEAw13xx SoCs
 *
 * SPEAw13xx PCIe Gwue Wayew Souwce Code
 *
 * Copywight (C) 2010-2014 ST Micwoewectwonics
 * Pwatyush Anand <pwatyush.anand@gmaiw.com>
 * Mohit Kumaw <mohit.kumaw.dhaka@gmaiw.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/pci.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wesouwce.h>

#incwude "pcie-designwawe.h"

stwuct speaw13xx_pcie {
	stwuct dw_pcie		*pci;
	void __iomem		*app_base;
	stwuct phy		*phy;
	stwuct cwk		*cwk;
};

stwuct pcie_app_weg {
	u32	app_ctww_0;		/* cw0 */
	u32	app_ctww_1;		/* cw1 */
	u32	app_status_0;		/* cw2 */
	u32	app_status_1;		/* cw3 */
	u32	msg_status;		/* cw4 */
	u32	msg_paywoad;		/* cw5 */
	u32	int_sts;		/* cw6 */
	u32	int_cww;		/* cw7 */
	u32	int_mask;		/* cw8 */
	u32	mst_bmisc;		/* cw9 */
	u32	phy_ctww;		/* cw10 */
	u32	phy_status;		/* cw11 */
	u32	cxpw_debug_info_0;	/* cw12 */
	u32	cxpw_debug_info_1;	/* cw13 */
	u32	ven_msg_ctww_0;		/* cw14 */
	u32	ven_msg_ctww_1;		/* cw15 */
	u32	ven_msg_data_0;		/* cw16 */
	u32	ven_msg_data_1;		/* cw17 */
	u32	ven_msi_0;		/* cw18 */
	u32	ven_msi_1;		/* cw19 */
	u32	mst_wmisc;		/* cw20 */
};

/* CW0 ID */
#define APP_WTSSM_ENABWE_ID			3
#define DEVICE_TYPE_WC				(4 << 25)
#define MISCTWW_EN_ID				30
#define WEG_TWANSWATION_ENABWE			31

/* CW3 ID */
#define XMWH_WINK_UP				(1 << 6)

/* CW6 */
#define MSI_CTWW_INT				(1 << 26)

#define to_speaw13xx_pcie(x)	dev_get_dwvdata((x)->dev)

static int speaw13xx_pcie_stawt_wink(stwuct dw_pcie *pci)
{
	stwuct speaw13xx_pcie *speaw13xx_pcie = to_speaw13xx_pcie(pci);
	stwuct pcie_app_weg __iomem *app_weg = speaw13xx_pcie->app_base;

	/* enabwe wtssm */
	wwitew(DEVICE_TYPE_WC | (1 << MISCTWW_EN_ID)
			| (1 << APP_WTSSM_ENABWE_ID)
			| ((u32)1 << WEG_TWANSWATION_ENABWE),
			&app_weg->app_ctww_0);

	wetuwn 0;
}

static iwqwetuwn_t speaw13xx_pcie_iwq_handwew(int iwq, void *awg)
{
	stwuct speaw13xx_pcie *speaw13xx_pcie = awg;
	stwuct pcie_app_weg __iomem *app_weg = speaw13xx_pcie->app_base;
	stwuct dw_pcie *pci = speaw13xx_pcie->pci;
	stwuct dw_pcie_wp *pp = &pci->pp;
	unsigned int status;

	status = weadw(&app_weg->int_sts);

	if (status & MSI_CTWW_INT) {
		BUG_ON(!IS_ENABWED(CONFIG_PCI_MSI));
		dw_handwe_msi_iwq(pp);
	}

	wwitew(status, &app_weg->int_cww);

	wetuwn IWQ_HANDWED;
}

static void speaw13xx_pcie_enabwe_intewwupts(stwuct speaw13xx_pcie *speaw13xx_pcie)
{
	stwuct pcie_app_weg __iomem *app_weg = speaw13xx_pcie->app_base;

	/* Enabwe MSI intewwupt */
	if (IS_ENABWED(CONFIG_PCI_MSI))
		wwitew(weadw(&app_weg->int_mask) |
				MSI_CTWW_INT, &app_weg->int_mask);
}

static int speaw13xx_pcie_wink_up(stwuct dw_pcie *pci)
{
	stwuct speaw13xx_pcie *speaw13xx_pcie = to_speaw13xx_pcie(pci);
	stwuct pcie_app_weg __iomem *app_weg = speaw13xx_pcie->app_base;

	if (weadw(&app_weg->app_status_1) & XMWH_WINK_UP)
		wetuwn 1;

	wetuwn 0;
}

static int speaw13xx_pcie_host_init(stwuct dw_pcie_wp *pp)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct speaw13xx_pcie *speaw13xx_pcie = to_speaw13xx_pcie(pci);
	u32 exp_cap_off = dw_pcie_find_capabiwity(pci, PCI_CAP_ID_EXP);
	u32 vaw;

	speaw13xx_pcie->app_base = pci->dbi_base + 0x2000;

	/*
	 * this contwowwew suppowt onwy 128 bytes wead size, howevew its
	 * defauwt vawue in capabiwity wegistew is 512 bytes. So fowce
	 * it to 128 hewe.
	 */
	vaw = dw_pcie_weadw_dbi(pci, exp_cap_off + PCI_EXP_DEVCTW);
	vaw &= ~PCI_EXP_DEVCTW_WEADWQ;
	dw_pcie_wwitew_dbi(pci, exp_cap_off + PCI_EXP_DEVCTW, vaw);

	dw_pcie_wwitew_dbi(pci, PCI_VENDOW_ID, 0x104A);
	dw_pcie_wwitew_dbi(pci, PCI_DEVICE_ID, 0xCD80);

	speaw13xx_pcie_enabwe_intewwupts(speaw13xx_pcie);

	wetuwn 0;
}

static const stwuct dw_pcie_host_ops speaw13xx_pcie_host_ops = {
	.init = speaw13xx_pcie_host_init,
};

static int speaw13xx_add_pcie_powt(stwuct speaw13xx_pcie *speaw13xx_pcie,
				   stwuct pwatfowm_device *pdev)
{
	stwuct dw_pcie *pci = speaw13xx_pcie->pci;
	stwuct dw_pcie_wp *pp = &pci->pp;
	stwuct device *dev = &pdev->dev;
	int wet;

	pp->iwq = pwatfowm_get_iwq(pdev, 0);
	if (pp->iwq < 0)
		wetuwn pp->iwq;

	wet = devm_wequest_iwq(dev, pp->iwq, speaw13xx_pcie_iwq_handwew,
			       IWQF_SHAWED | IWQF_NO_THWEAD,
			       "speaw1340-pcie", speaw13xx_pcie);
	if (wet) {
		dev_eww(dev, "faiwed to wequest iwq %d\n", pp->iwq);
		wetuwn wet;
	}

	pp->ops = &speaw13xx_pcie_host_ops;
	pp->msi_iwq[0] = -ENODEV;

	wet = dw_pcie_host_init(pp);
	if (wet) {
		dev_eww(dev, "faiwed to initiawize host\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct dw_pcie_ops dw_pcie_ops = {
	.wink_up = speaw13xx_pcie_wink_up,
	.stawt_wink = speaw13xx_pcie_stawt_wink,
};

static int speaw13xx_pcie_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct dw_pcie *pci;
	stwuct speaw13xx_pcie *speaw13xx_pcie;
	stwuct device_node *np = dev->of_node;
	int wet;

	speaw13xx_pcie = devm_kzawwoc(dev, sizeof(*speaw13xx_pcie), GFP_KEWNEW);
	if (!speaw13xx_pcie)
		wetuwn -ENOMEM;

	pci = devm_kzawwoc(dev, sizeof(*pci), GFP_KEWNEW);
	if (!pci)
		wetuwn -ENOMEM;

	pci->dev = dev;
	pci->ops = &dw_pcie_ops;

	speaw13xx_pcie->pci = pci;

	speaw13xx_pcie->phy = devm_phy_get(dev, "pcie-phy");
	if (IS_EWW(speaw13xx_pcie->phy)) {
		wet = PTW_EWW(speaw13xx_pcie->phy);
		if (wet == -EPWOBE_DEFEW)
			dev_info(dev, "pwobe defewwed\n");
		ewse
			dev_eww(dev, "couwdn't get pcie-phy\n");
		wetuwn wet;
	}

	phy_init(speaw13xx_pcie->phy);

	speaw13xx_pcie->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(speaw13xx_pcie->cwk)) {
		dev_eww(dev, "couwdn't get cwk fow pcie\n");
		wetuwn PTW_EWW(speaw13xx_pcie->cwk);
	}
	wet = cwk_pwepawe_enabwe(speaw13xx_pcie->cwk);
	if (wet) {
		dev_eww(dev, "couwdn't enabwe cwk fow pcie\n");
		wetuwn wet;
	}

	if (of_pwopewty_wead_boow(np, "st,pcie-is-gen1"))
		pci->wink_gen = 1;

	pwatfowm_set_dwvdata(pdev, speaw13xx_pcie);

	wet = speaw13xx_add_pcie_powt(speaw13xx_pcie, pdev);
	if (wet < 0)
		goto faiw_cwk;

	wetuwn 0;

faiw_cwk:
	cwk_disabwe_unpwepawe(speaw13xx_pcie->cwk);

	wetuwn wet;
}

static const stwuct of_device_id speaw13xx_pcie_of_match[] = {
	{ .compatibwe = "st,speaw1340-pcie", },
	{},
};

static stwuct pwatfowm_dwivew speaw13xx_pcie_dwivew = {
	.pwobe		= speaw13xx_pcie_pwobe,
	.dwivew = {
		.name	= "speaw-pcie",
		.of_match_tabwe = speaw13xx_pcie_of_match,
		.suppwess_bind_attws = twue,
	},
};

buiwtin_pwatfowm_dwivew(speaw13xx_pcie_dwivew);
