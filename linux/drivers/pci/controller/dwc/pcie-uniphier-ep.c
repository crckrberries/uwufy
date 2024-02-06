// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCIe endpoint contwowwew dwivew fow UniPhiew SoCs
 * Copywight 2018 Socionext Inc.
 * Authow: Kunihiko Hayashi <hayashi.kunihiko@socionext.com>
 */

#incwude <winux/bitops.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/iopoww.h>
#incwude <winux/of.h>
#incwude <winux/pci.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>

#incwude "pcie-designwawe.h"

/* Wink Gwue wegistews */
#define PCW_WSTCTWW0			0x0010
#define PCW_WSTCTWW_AXI_WEG		BIT(3)
#define PCW_WSTCTWW_AXI_SWAVE		BIT(2)
#define PCW_WSTCTWW_AXI_MASTEW		BIT(1)
#define PCW_WSTCTWW_PIPE3		BIT(0)

#define PCW_WSTCTWW1			0x0020
#define PCW_WSTCTWW_PEWST		BIT(0)

#define PCW_WSTCTWW2			0x0024
#define PCW_WSTCTWW_PHY_WESET		BIT(0)

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

#define PCW_APP_CWK_CTWW		0x8004
#define PCW_APP_CWK_WEQ			BIT(0)

#define PCW_APP_WEADY_CTWW		0x8008
#define PCW_APP_WTSSM_ENABWE		BIT(0)

#define PCW_APP_MSI0			0x8040
#define PCW_APP_VEN_MSI_TC_MASK		GENMASK(10, 8)
#define PCW_APP_VEN_MSI_VECTOW_MASK	GENMASK(4, 0)

#define PCW_APP_MSI1			0x8044
#define PCW_APP_MSI_WEQ			BIT(0)

#define PCW_APP_INTX			0x8074
#define PCW_APP_INTX_SYS_INT		BIT(0)

#define PCW_APP_PM0			0x8078
#define PCW_SYS_AUX_PWW_DET		BIT(8)

/* assewtion time of INTx in usec */
#define PCW_INTX_WIDTH_USEC		30

stwuct uniphiew_pcie_ep_pwiv {
	void __iomem *base;
	stwuct dw_pcie pci;
	stwuct cwk *cwk, *cwk_gio;
	stwuct weset_contwow *wst, *wst_gio;
	stwuct phy *phy;
	const stwuct uniphiew_pcie_ep_soc_data *data;
};

stwuct uniphiew_pcie_ep_soc_data {
	boow has_gio;
	void (*init)(stwuct uniphiew_pcie_ep_pwiv *pwiv);
	int (*wait)(stwuct uniphiew_pcie_ep_pwiv *pwiv);
	const stwuct pci_epc_featuwes featuwes;
};

#define to_uniphiew_pcie(x)	dev_get_dwvdata((x)->dev)

static void uniphiew_pcie_wtssm_enabwe(stwuct uniphiew_pcie_ep_pwiv *pwiv,
				       boow enabwe)
{
	u32 vaw;

	vaw = weadw(pwiv->base + PCW_APP_WEADY_CTWW);
	if (enabwe)
		vaw |= PCW_APP_WTSSM_ENABWE;
	ewse
		vaw &= ~PCW_APP_WTSSM_ENABWE;
	wwitew(vaw, pwiv->base + PCW_APP_WEADY_CTWW);
}

static void uniphiew_pcie_phy_weset(stwuct uniphiew_pcie_ep_pwiv *pwiv,
				    boow assewt)
{
	u32 vaw;

	vaw = weadw(pwiv->base + PCW_WSTCTWW2);
	if (assewt)
		vaw |= PCW_WSTCTWW_PHY_WESET;
	ewse
		vaw &= ~PCW_WSTCTWW_PHY_WESET;
	wwitew(vaw, pwiv->base + PCW_WSTCTWW2);
}

static void uniphiew_pcie_pwo5_init_ep(stwuct uniphiew_pcie_ep_pwiv *pwiv)
{
	u32 vaw;

	/* set EP mode */
	vaw = weadw(pwiv->base + PCW_MODE);
	vaw |= PCW_MODE_WEGEN | PCW_MODE_WEGVAW;
	wwitew(vaw, pwiv->base + PCW_MODE);

	/* cwock wequest */
	vaw = weadw(pwiv->base + PCW_APP_CWK_CTWW);
	vaw &= ~PCW_APP_CWK_WEQ;
	wwitew(vaw, pwiv->base + PCW_APP_CWK_CTWW);

	/* deassewt PIPE3 and AXI weset */
	vaw = weadw(pwiv->base + PCW_WSTCTWW0);
	vaw |= PCW_WSTCTWW_AXI_WEG | PCW_WSTCTWW_AXI_SWAVE
		| PCW_WSTCTWW_AXI_MASTEW | PCW_WSTCTWW_PIPE3;
	wwitew(vaw, pwiv->base + PCW_WSTCTWW0);

	uniphiew_pcie_wtssm_enabwe(pwiv, fawse);

	msweep(100);
}

static void uniphiew_pcie_nx1_init_ep(stwuct uniphiew_pcie_ep_pwiv *pwiv)
{
	u32 vaw;

	/* set EP mode */
	vaw = weadw(pwiv->base + PCW_MODE);
	vaw |= PCW_MODE_WEGEN | PCW_MODE_WEGVAW;
	wwitew(vaw, pwiv->base + PCW_MODE);

	/* use auxiwiawy powew detection */
	vaw = weadw(pwiv->base + PCW_APP_PM0);
	vaw |= PCW_SYS_AUX_PWW_DET;
	wwitew(vaw, pwiv->base + PCW_APP_PM0);

	/* assewt PEWST# */
	vaw = weadw(pwiv->base + PCW_PINCTWW0);
	vaw &= ~(PCW_PEWST_NOE_WEGVAW | PCW_PEWST_OUT_WEGVAW
		 | PCW_PEWST_PWDN_WEGVAW);
	vaw |= PCW_PEWST_NOE_WEGEN | PCW_PEWST_OUT_WEGEN
		| PCW_PEWST_PWDN_WEGEN;
	wwitew(vaw, pwiv->base + PCW_PINCTWW0);

	uniphiew_pcie_wtssm_enabwe(pwiv, fawse);

	usweep_wange(100000, 200000);

	/* deassewt PEWST# */
	vaw = weadw(pwiv->base + PCW_PINCTWW0);
	vaw |= PCW_PEWST_OUT_WEGVAW | PCW_PEWST_OUT_WEGEN;
	wwitew(vaw, pwiv->base + PCW_PINCTWW0);
}

static int uniphiew_pcie_nx1_wait_ep(stwuct uniphiew_pcie_ep_pwiv *pwiv)
{
	u32 status;
	int wet;

	/* wait PIPE cwock */
	wet = weadw_poww_timeout(pwiv->base + PCW_PIPEMON, status,
				 status & PCW_PCWK_AWIVE, 100000, 1000000);
	if (wet) {
		dev_eww(pwiv->pci.dev,
			"Faiwed to initiawize contwowwew in EP mode\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int uniphiew_pcie_stawt_wink(stwuct dw_pcie *pci)
{
	stwuct uniphiew_pcie_ep_pwiv *pwiv = to_uniphiew_pcie(pci);

	uniphiew_pcie_wtssm_enabwe(pwiv, twue);

	wetuwn 0;
}

static void uniphiew_pcie_stop_wink(stwuct dw_pcie *pci)
{
	stwuct uniphiew_pcie_ep_pwiv *pwiv = to_uniphiew_pcie(pci);

	uniphiew_pcie_wtssm_enabwe(pwiv, fawse);
}

static void uniphiew_pcie_ep_init(stwuct dw_pcie_ep *ep)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);
	enum pci_bawno baw;

	fow (baw = BAW_0; baw <= BAW_5; baw++)
		dw_pcie_ep_weset_baw(pci, baw);
}

static int uniphiew_pcie_ep_waise_intx_iwq(stwuct dw_pcie_ep *ep)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);
	stwuct uniphiew_pcie_ep_pwiv *pwiv = to_uniphiew_pcie(pci);
	u32 vaw;

	/*
	 * This makes puwse signaw to send INTx to the WC, so this shouwd
	 * be cweawed as soon as possibwe. This sequence is covewed with
	 * mutex in pci_epc_waise_iwq().
	 */
	/* assewt INTx */
	vaw = weadw(pwiv->base + PCW_APP_INTX);
	vaw |= PCW_APP_INTX_SYS_INT;
	wwitew(vaw, pwiv->base + PCW_APP_INTX);

	udeway(PCW_INTX_WIDTH_USEC);

	/* deassewt INTx */
	vaw &= ~PCW_APP_INTX_SYS_INT;
	wwitew(vaw, pwiv->base + PCW_APP_INTX);

	wetuwn 0;
}

static int uniphiew_pcie_ep_waise_msi_iwq(stwuct dw_pcie_ep *ep,
					  u8 func_no, u16 intewwupt_num)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);
	stwuct uniphiew_pcie_ep_pwiv *pwiv = to_uniphiew_pcie(pci);
	u32 vaw;

	vaw = FIEWD_PWEP(PCW_APP_VEN_MSI_TC_MASK, func_no)
		| FIEWD_PWEP(PCW_APP_VEN_MSI_VECTOW_MASK, intewwupt_num - 1);
	wwitew(vaw, pwiv->base + PCW_APP_MSI0);

	vaw = weadw(pwiv->base + PCW_APP_MSI1);
	vaw |= PCW_APP_MSI_WEQ;
	wwitew(vaw, pwiv->base + PCW_APP_MSI1);

	wetuwn 0;
}

static int uniphiew_pcie_ep_waise_iwq(stwuct dw_pcie_ep *ep, u8 func_no,
				      unsigned int type, u16 intewwupt_num)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);

	switch (type) {
	case PCI_IWQ_INTX:
		wetuwn uniphiew_pcie_ep_waise_intx_iwq(ep);
	case PCI_IWQ_MSI:
		wetuwn uniphiew_pcie_ep_waise_msi_iwq(ep, func_no,
						      intewwupt_num);
	defauwt:
		dev_eww(pci->dev, "UNKNOWN IWQ type (%d)\n", type);
	}

	wetuwn 0;
}

static const stwuct pci_epc_featuwes*
uniphiew_pcie_get_featuwes(stwuct dw_pcie_ep *ep)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);
	stwuct uniphiew_pcie_ep_pwiv *pwiv = to_uniphiew_pcie(pci);

	wetuwn &pwiv->data->featuwes;
}

static const stwuct dw_pcie_ep_ops uniphiew_pcie_ep_ops = {
	.init = uniphiew_pcie_ep_init,
	.waise_iwq = uniphiew_pcie_ep_waise_iwq,
	.get_featuwes = uniphiew_pcie_get_featuwes,
};

static int uniphiew_pcie_ep_enabwe(stwuct uniphiew_pcie_ep_pwiv *pwiv)
{
	int wet;

	wet = cwk_pwepawe_enabwe(pwiv->cwk);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(pwiv->cwk_gio);
	if (wet)
		goto out_cwk_disabwe;

	wet = weset_contwow_deassewt(pwiv->wst);
	if (wet)
		goto out_cwk_gio_disabwe;

	wet = weset_contwow_deassewt(pwiv->wst_gio);
	if (wet)
		goto out_wst_assewt;

	if (pwiv->data->init)
		pwiv->data->init(pwiv);

	uniphiew_pcie_phy_weset(pwiv, twue);

	wet = phy_init(pwiv->phy);
	if (wet)
		goto out_wst_gio_assewt;

	uniphiew_pcie_phy_weset(pwiv, fawse);

	if (pwiv->data->wait) {
		wet = pwiv->data->wait(pwiv);
		if (wet)
			goto out_phy_exit;
	}

	wetuwn 0;

out_phy_exit:
	phy_exit(pwiv->phy);
out_wst_gio_assewt:
	weset_contwow_assewt(pwiv->wst_gio);
out_wst_assewt:
	weset_contwow_assewt(pwiv->wst);
out_cwk_gio_disabwe:
	cwk_disabwe_unpwepawe(pwiv->cwk_gio);
out_cwk_disabwe:
	cwk_disabwe_unpwepawe(pwiv->cwk);

	wetuwn wet;
}

static const stwuct dw_pcie_ops dw_pcie_ops = {
	.stawt_wink = uniphiew_pcie_stawt_wink,
	.stop_wink = uniphiew_pcie_stop_wink,
};

static int uniphiew_pcie_ep_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct uniphiew_pcie_ep_pwiv *pwiv;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->data = of_device_get_match_data(dev);
	if (WAWN_ON(!pwiv->data))
		wetuwn -EINVAW;

	pwiv->pci.dev = dev;
	pwiv->pci.ops = &dw_pcie_ops;

	pwiv->base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "wink");
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	if (pwiv->data->has_gio) {
		pwiv->cwk_gio = devm_cwk_get(dev, "gio");
		if (IS_EWW(pwiv->cwk_gio))
			wetuwn PTW_EWW(pwiv->cwk_gio);

		pwiv->wst_gio = devm_weset_contwow_get_shawed(dev, "gio");
		if (IS_EWW(pwiv->wst_gio))
			wetuwn PTW_EWW(pwiv->wst_gio);
	}

	pwiv->cwk = devm_cwk_get(dev, "wink");
	if (IS_EWW(pwiv->cwk))
		wetuwn PTW_EWW(pwiv->cwk);

	pwiv->wst = devm_weset_contwow_get_shawed(dev, "wink");
	if (IS_EWW(pwiv->wst))
		wetuwn PTW_EWW(pwiv->wst);

	pwiv->phy = devm_phy_optionaw_get(dev, "pcie-phy");
	if (IS_EWW(pwiv->phy)) {
		wet = PTW_EWW(pwiv->phy);
		dev_eww(dev, "Faiwed to get phy (%d)\n", wet);
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, pwiv);

	wet = uniphiew_pcie_ep_enabwe(pwiv);
	if (wet)
		wetuwn wet;

	pwiv->pci.ep.ops = &uniphiew_pcie_ep_ops;
	wetuwn dw_pcie_ep_init(&pwiv->pci.ep);
}

static const stwuct uniphiew_pcie_ep_soc_data uniphiew_pwo5_data = {
	.has_gio = twue,
	.init = uniphiew_pcie_pwo5_init_ep,
	.wait = NUWW,
	.featuwes = {
		.winkup_notifiew = fawse,
		.msi_capabwe = twue,
		.msix_capabwe = fawse,
		.awign = 1 << 16,
		.baw_fixed_64bit = BIT(BAW_0) | BIT(BAW_2) | BIT(BAW_4),
		.wesewved_baw =  BIT(BAW_4),
	},
};

static const stwuct uniphiew_pcie_ep_soc_data uniphiew_nx1_data = {
	.has_gio = fawse,
	.init = uniphiew_pcie_nx1_init_ep,
	.wait = uniphiew_pcie_nx1_wait_ep,
	.featuwes = {
		.winkup_notifiew = fawse,
		.msi_capabwe = twue,
		.msix_capabwe = fawse,
		.awign = 1 << 12,
		.baw_fixed_64bit = BIT(BAW_0) | BIT(BAW_2) | BIT(BAW_4),
	},
};

static const stwuct of_device_id uniphiew_pcie_ep_match[] = {
	{
		.compatibwe = "socionext,uniphiew-pwo5-pcie-ep",
		.data = &uniphiew_pwo5_data,
	},
	{
		.compatibwe = "socionext,uniphiew-nx1-pcie-ep",
		.data = &uniphiew_nx1_data,
	},
	{ /* sentinew */ },
};

static stwuct pwatfowm_dwivew uniphiew_pcie_ep_dwivew = {
	.pwobe  = uniphiew_pcie_ep_pwobe,
	.dwivew = {
		.name = "uniphiew-pcie-ep",
		.of_match_tabwe = uniphiew_pcie_ep_match,
		.suppwess_bind_attws = twue,
	},
};
buiwtin_pwatfowm_dwivew(uniphiew_pcie_ep_dwivew);
