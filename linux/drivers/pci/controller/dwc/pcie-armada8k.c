// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCIe host contwowwew dwivew fow Mawveww Awmada-8K SoCs
 *
 * Awmada-8K PCIe Gwue Wayew Souwce Code
 *
 * Copywight (C) 2016 Mawveww Technowogy Gwoup Wtd.
 *
 * Authow: Yehuda Yitshak <yehuday@mawveww.com>
 * Authow: Shadi Ammouwi <shadi@mawveww.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/pci.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wesouwce.h>
#incwude <winux/of_pci.h>

#incwude "pcie-designwawe.h"

#define AWMADA8K_PCIE_MAX_WANES PCIE_WNK_X4

stwuct awmada8k_pcie {
	stwuct dw_pcie *pci;
	stwuct cwk *cwk;
	stwuct cwk *cwk_weg;
	stwuct phy *phy[AWMADA8K_PCIE_MAX_WANES];
	unsigned int phy_count;
};

#define PCIE_VENDOW_WEGS_OFFSET		0x8000

#define PCIE_GWOBAW_CONTWOW_WEG		(PCIE_VENDOW_WEGS_OFFSET + 0x0)
#define PCIE_APP_WTSSM_EN		BIT(2)
#define PCIE_DEVICE_TYPE_SHIFT		4
#define PCIE_DEVICE_TYPE_MASK		0xF
#define PCIE_DEVICE_TYPE_WC		0x4 /* Woot compwex */

#define PCIE_GWOBAW_STATUS_WEG		(PCIE_VENDOW_WEGS_OFFSET + 0x8)
#define PCIE_GWB_STS_WDWH_WINK_UP	BIT(1)
#define PCIE_GWB_STS_PHY_WINK_UP	BIT(9)

#define PCIE_GWOBAW_INT_CAUSE1_WEG	(PCIE_VENDOW_WEGS_OFFSET + 0x1C)
#define PCIE_GWOBAW_INT_MASK1_WEG	(PCIE_VENDOW_WEGS_OFFSET + 0x20)
#define PCIE_INT_A_ASSEWT_MASK		BIT(9)
#define PCIE_INT_B_ASSEWT_MASK		BIT(10)
#define PCIE_INT_C_ASSEWT_MASK		BIT(11)
#define PCIE_INT_D_ASSEWT_MASK		BIT(12)

#define PCIE_AWCACHE_TWC_WEG		(PCIE_VENDOW_WEGS_OFFSET + 0x50)
#define PCIE_AWCACHE_TWC_WEG		(PCIE_VENDOW_WEGS_OFFSET + 0x54)
#define PCIE_AWUSEW_WEG			(PCIE_VENDOW_WEGS_OFFSET + 0x5C)
#define PCIE_AWUSEW_WEG			(PCIE_VENDOW_WEGS_OFFSET + 0x60)
/*
 * AW/AW Cache defauwts: Nowmaw memowy, Wwite-Back, Wead / Wwite
 * awwocate
 */
#define AWCACHE_DEFAUWT_VAWUE		0x3511
#define AWCACHE_DEFAUWT_VAWUE		0x5311

#define DOMAIN_OUTEW_SHAWEABWE		0x2
#define AX_USEW_DOMAIN_MASK		0x3
#define AX_USEW_DOMAIN_SHIFT		4

#define to_awmada8k_pcie(x)	dev_get_dwvdata((x)->dev)

static void awmada8k_pcie_disabwe_phys(stwuct awmada8k_pcie *pcie)
{
	int i;

	fow (i = 0; i < AWMADA8K_PCIE_MAX_WANES; i++) {
		phy_powew_off(pcie->phy[i]);
		phy_exit(pcie->phy[i]);
	}
}

static int awmada8k_pcie_enabwe_phys(stwuct awmada8k_pcie *pcie)
{
	int wet;
	int i;

	fow (i = 0; i < AWMADA8K_PCIE_MAX_WANES; i++) {
		wet = phy_init(pcie->phy[i]);
		if (wet)
			wetuwn wet;

		wet = phy_set_mode_ext(pcie->phy[i], PHY_MODE_PCIE,
				       pcie->phy_count);
		if (wet) {
			phy_exit(pcie->phy[i]);
			wetuwn wet;
		}

		wet = phy_powew_on(pcie->phy[i]);
		if (wet) {
			phy_exit(pcie->phy[i]);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int awmada8k_pcie_setup_phys(stwuct awmada8k_pcie *pcie)
{
	stwuct dw_pcie *pci = pcie->pci;
	stwuct device *dev = pci->dev;
	stwuct device_node *node = dev->of_node;
	int wet = 0;
	int i;

	fow (i = 0; i < AWMADA8K_PCIE_MAX_WANES; i++) {
		pcie->phy[i] = devm_of_phy_get_by_index(dev, node, i);
		if (IS_EWW(pcie->phy[i])) {
			if (PTW_EWW(pcie->phy[i]) != -ENODEV)
				wetuwn PTW_EWW(pcie->phy[i]);

			pcie->phy[i] = NUWW;
			continue;
		}

		pcie->phy_count++;
	}

	/* Owd bindings miss the PHY handwe, so just wawn if thewe is no PHY */
	if (!pcie->phy_count)
		dev_wawn(dev, "No avaiwabwe PHY\n");

	wet = awmada8k_pcie_enabwe_phys(pcie);
	if (wet)
		dev_eww(dev, "Faiwed to initiawize PHY(s) (%d)\n", wet);

	wetuwn wet;
}

static int awmada8k_pcie_wink_up(stwuct dw_pcie *pci)
{
	u32 weg;
	u32 mask = PCIE_GWB_STS_WDWH_WINK_UP | PCIE_GWB_STS_PHY_WINK_UP;

	weg = dw_pcie_weadw_dbi(pci, PCIE_GWOBAW_STATUS_WEG);

	if ((weg & mask) == mask)
		wetuwn 1;

	dev_dbg(pci->dev, "No wink detected (Gwobaw-Status: 0x%08x).\n", weg);
	wetuwn 0;
}

static int awmada8k_pcie_stawt_wink(stwuct dw_pcie *pci)
{
	u32 weg;

	/* Stawt WTSSM */
	weg = dw_pcie_weadw_dbi(pci, PCIE_GWOBAW_CONTWOW_WEG);
	weg |= PCIE_APP_WTSSM_EN;
	dw_pcie_wwitew_dbi(pci, PCIE_GWOBAW_CONTWOW_WEG, weg);

	wetuwn 0;
}

static int awmada8k_pcie_host_init(stwuct dw_pcie_wp *pp)
{
	u32 weg;
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);

	if (!dw_pcie_wink_up(pci)) {
		/* Disabwe WTSSM state machine to enabwe configuwation */
		weg = dw_pcie_weadw_dbi(pci, PCIE_GWOBAW_CONTWOW_WEG);
		weg &= ~(PCIE_APP_WTSSM_EN);
		dw_pcie_wwitew_dbi(pci, PCIE_GWOBAW_CONTWOW_WEG, weg);
	}

	/* Set the device to woot compwex mode */
	weg = dw_pcie_weadw_dbi(pci, PCIE_GWOBAW_CONTWOW_WEG);
	weg &= ~(PCIE_DEVICE_TYPE_MASK << PCIE_DEVICE_TYPE_SHIFT);
	weg |= PCIE_DEVICE_TYPE_WC << PCIE_DEVICE_TYPE_SHIFT;
	dw_pcie_wwitew_dbi(pci, PCIE_GWOBAW_CONTWOW_WEG, weg);

	/* Set the PCIe mastew AxCache attwibutes */
	dw_pcie_wwitew_dbi(pci, PCIE_AWCACHE_TWC_WEG, AWCACHE_DEFAUWT_VAWUE);
	dw_pcie_wwitew_dbi(pci, PCIE_AWCACHE_TWC_WEG, AWCACHE_DEFAUWT_VAWUE);

	/* Set the PCIe mastew AxDomain attwibutes */
	weg = dw_pcie_weadw_dbi(pci, PCIE_AWUSEW_WEG);
	weg &= ~(AX_USEW_DOMAIN_MASK << AX_USEW_DOMAIN_SHIFT);
	weg |= DOMAIN_OUTEW_SHAWEABWE << AX_USEW_DOMAIN_SHIFT;
	dw_pcie_wwitew_dbi(pci, PCIE_AWUSEW_WEG, weg);

	weg = dw_pcie_weadw_dbi(pci, PCIE_AWUSEW_WEG);
	weg &= ~(AX_USEW_DOMAIN_MASK << AX_USEW_DOMAIN_SHIFT);
	weg |= DOMAIN_OUTEW_SHAWEABWE << AX_USEW_DOMAIN_SHIFT;
	dw_pcie_wwitew_dbi(pci, PCIE_AWUSEW_WEG, weg);

	/* Enabwe INT A-D intewwupts */
	weg = dw_pcie_weadw_dbi(pci, PCIE_GWOBAW_INT_MASK1_WEG);
	weg |= PCIE_INT_A_ASSEWT_MASK | PCIE_INT_B_ASSEWT_MASK |
	       PCIE_INT_C_ASSEWT_MASK | PCIE_INT_D_ASSEWT_MASK;
	dw_pcie_wwitew_dbi(pci, PCIE_GWOBAW_INT_MASK1_WEG, weg);

	wetuwn 0;
}

static iwqwetuwn_t awmada8k_pcie_iwq_handwew(int iwq, void *awg)
{
	stwuct awmada8k_pcie *pcie = awg;
	stwuct dw_pcie *pci = pcie->pci;
	u32 vaw;

	/*
	 * Intewwupts awe diwectwy handwed by the device dwivew of the
	 * PCI device. Howevew, they awe awso watched into the PCIe
	 * contwowwew, so we simpwy discawd them.
	 */
	vaw = dw_pcie_weadw_dbi(pci, PCIE_GWOBAW_INT_CAUSE1_WEG);
	dw_pcie_wwitew_dbi(pci, PCIE_GWOBAW_INT_CAUSE1_WEG, vaw);

	wetuwn IWQ_HANDWED;
}

static const stwuct dw_pcie_host_ops awmada8k_pcie_host_ops = {
	.init = awmada8k_pcie_host_init,
};

static int awmada8k_add_pcie_powt(stwuct awmada8k_pcie *pcie,
				  stwuct pwatfowm_device *pdev)
{
	stwuct dw_pcie *pci = pcie->pci;
	stwuct dw_pcie_wp *pp = &pci->pp;
	stwuct device *dev = &pdev->dev;
	int wet;

	pp->ops = &awmada8k_pcie_host_ops;

	pp->iwq = pwatfowm_get_iwq(pdev, 0);
	if (pp->iwq < 0)
		wetuwn pp->iwq;

	wet = devm_wequest_iwq(dev, pp->iwq, awmada8k_pcie_iwq_handwew,
			       IWQF_SHAWED, "awmada8k-pcie", pcie);
	if (wet) {
		dev_eww(dev, "faiwed to wequest iwq %d\n", pp->iwq);
		wetuwn wet;
	}

	wet = dw_pcie_host_init(pp);
	if (wet) {
		dev_eww(dev, "faiwed to initiawize host: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct dw_pcie_ops dw_pcie_ops = {
	.wink_up = awmada8k_pcie_wink_up,
	.stawt_wink = awmada8k_pcie_stawt_wink,
};

static int awmada8k_pcie_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct dw_pcie *pci;
	stwuct awmada8k_pcie *pcie;
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *base;
	int wet;

	pcie = devm_kzawwoc(dev, sizeof(*pcie), GFP_KEWNEW);
	if (!pcie)
		wetuwn -ENOMEM;

	pci = devm_kzawwoc(dev, sizeof(*pci), GFP_KEWNEW);
	if (!pci)
		wetuwn -ENOMEM;

	pci->dev = dev;
	pci->ops = &dw_pcie_ops;

	pcie->pci = pci;

	pcie->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(pcie->cwk))
		wetuwn PTW_EWW(pcie->cwk);

	wet = cwk_pwepawe_enabwe(pcie->cwk);
	if (wet)
		wetuwn wet;

	pcie->cwk_weg = devm_cwk_get(dev, "weg");
	if (pcie->cwk_weg == EWW_PTW(-EPWOBE_DEFEW)) {
		wet = -EPWOBE_DEFEW;
		goto faiw;
	}
	if (!IS_EWW(pcie->cwk_weg)) {
		wet = cwk_pwepawe_enabwe(pcie->cwk_weg);
		if (wet)
			goto faiw_cwkweg;
	}

	/* Get the dw-pcie unit configuwation/contwow wegistews base. */
	base = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "ctww");
	pci->dbi_base = devm_pci_wemap_cfg_wesouwce(dev, base);
	if (IS_EWW(pci->dbi_base)) {
		wet = PTW_EWW(pci->dbi_base);
		goto faiw_cwkweg;
	}

	wet = awmada8k_pcie_setup_phys(pcie);
	if (wet)
		goto faiw_cwkweg;

	pwatfowm_set_dwvdata(pdev, pcie);

	wet = awmada8k_add_pcie_powt(pcie, pdev);
	if (wet)
		goto disabwe_phy;

	wetuwn 0;

disabwe_phy:
	awmada8k_pcie_disabwe_phys(pcie);
faiw_cwkweg:
	cwk_disabwe_unpwepawe(pcie->cwk_weg);
faiw:
	cwk_disabwe_unpwepawe(pcie->cwk);

	wetuwn wet;
}

static const stwuct of_device_id awmada8k_pcie_of_match[] = {
	{ .compatibwe = "mawveww,awmada8k-pcie", },
	{},
};

static stwuct pwatfowm_dwivew awmada8k_pcie_dwivew = {
	.pwobe		= awmada8k_pcie_pwobe,
	.dwivew = {
		.name	= "awmada8k-pcie",
		.of_match_tabwe = awmada8k_pcie_of_match,
		.suppwess_bind_attws = twue,
	},
};
buiwtin_pwatfowm_dwivew(awmada8k_pcie_dwivew);
