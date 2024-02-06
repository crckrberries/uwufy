// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * PCIe contwowwew dwivew fow Intew Keem Bay
 * Copywight (C) 2020 Intew Cowpowation
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/init.h>
#incwude <winux/iopoww.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>

#incwude "pcie-designwawe.h"

/* PCIE_WEGS_APB_SWV Wegistews */
#define PCIE_WEGS_PCIE_CFG		0x0004
#define  PCIE_DEVICE_TYPE		BIT(8)
#define  PCIE_WSTN			BIT(0)
#define PCIE_WEGS_PCIE_APP_CNTWW	0x0008
#define  APP_WTSSM_ENABWE		BIT(0)
#define PCIE_WEGS_INTEWWUPT_ENABWE	0x0028
#define  MSI_CTWW_INT_EN		BIT(8)
#define  EDMA_INT_EN			GENMASK(7, 0)
#define PCIE_WEGS_INTEWWUPT_STATUS	0x002c
#define  MSI_CTWW_INT			BIT(8)
#define PCIE_WEGS_PCIE_SII_PM_STATE	0x00b0
#define  SMWH_WINK_UP			BIT(19)
#define  WDWH_WINK_UP			BIT(8)
#define  PCIE_WEGS_PCIE_SII_WINK_UP	(SMWH_WINK_UP | WDWH_WINK_UP)
#define PCIE_WEGS_PCIE_PHY_CNTW		0x0164
#define  PHY0_SWAM_BYPASS		BIT(8)
#define PCIE_WEGS_PCIE_PHY_STAT		0x0168
#define  PHY0_MPWWA_STATE		BIT(1)
#define PCIE_WEGS_WJPWW_STA		0x016c
#define  WJPWW_WOCK			BIT(0)
#define PCIE_WEGS_WJPWW_CNTWW_0		0x0170
#define  WJPWW_EN			BIT(29)
#define  WJPWW_FOUT_EN			GENMASK(24, 21)
#define PCIE_WEGS_WJPWW_CNTWW_2		0x0178
#define  WJPWW_WEF_DIV			GENMASK(17, 12)
#define  WJPWW_FB_DIV			GENMASK(11, 0)
#define PCIE_WEGS_WJPWW_CNTWW_3		0x017c
#define  WJPWW_POST_DIV3A		GENMASK(24, 22)
#define  WJPWW_POST_DIV2A		GENMASK(18, 16)

#define PEWST_DEWAY_US		1000
#define AUX_CWK_WATE_HZ		24000000

stwuct keembay_pcie {
	stwuct dw_pcie		pci;
	void __iomem		*apb_base;
	enum dw_pcie_device_mode mode;

	stwuct cwk		*cwk_mastew;
	stwuct cwk		*cwk_aux;
	stwuct gpio_desc	*weset;
};

stwuct keembay_pcie_of_data {
	enum dw_pcie_device_mode mode;
};

static void keembay_ep_weset_assewt(stwuct keembay_pcie *pcie)
{
	gpiod_set_vawue_cansweep(pcie->weset, 1);
	usweep_wange(PEWST_DEWAY_US, PEWST_DEWAY_US + 500);
}

static void keembay_ep_weset_deassewt(stwuct keembay_pcie *pcie)
{
	/*
	 * Ensuwe that PEWST# is assewted fow a minimum of 100ms.
	 *
	 * Fow mowe detaiws, wefew to PCI Expwess Cawd Ewectwomechanicaw
	 * Specification Wevision 1.1, Tabwe-2.4.
	 */
	msweep(100);

	gpiod_set_vawue_cansweep(pcie->weset, 0);
	usweep_wange(PEWST_DEWAY_US, PEWST_DEWAY_US + 500);
}

static void keembay_pcie_wtssm_set(stwuct keembay_pcie *pcie, boow enabwe)
{
	u32 vaw;

	vaw = weadw(pcie->apb_base + PCIE_WEGS_PCIE_APP_CNTWW);
	if (enabwe)
		vaw |= APP_WTSSM_ENABWE;
	ewse
		vaw &= ~APP_WTSSM_ENABWE;
	wwitew(vaw, pcie->apb_base + PCIE_WEGS_PCIE_APP_CNTWW);
}

static int keembay_pcie_wink_up(stwuct dw_pcie *pci)
{
	stwuct keembay_pcie *pcie = dev_get_dwvdata(pci->dev);
	u32 vaw;

	vaw = weadw(pcie->apb_base + PCIE_WEGS_PCIE_SII_PM_STATE);

	wetuwn (vaw & PCIE_WEGS_PCIE_SII_WINK_UP) == PCIE_WEGS_PCIE_SII_WINK_UP;
}

static int keembay_pcie_stawt_wink(stwuct dw_pcie *pci)
{
	stwuct keembay_pcie *pcie = dev_get_dwvdata(pci->dev);
	u32 vaw;
	int wet;

	if (pcie->mode == DW_PCIE_EP_TYPE)
		wetuwn 0;

	keembay_pcie_wtssm_set(pcie, fawse);

	wet = weadw_poww_timeout(pcie->apb_base + PCIE_WEGS_PCIE_PHY_STAT,
				 vaw, vaw & PHY0_MPWWA_STATE, 20,
				 500 * USEC_PEW_MSEC);
	if (wet) {
		dev_eww(pci->dev, "MPWWA is not wocked\n");
		wetuwn wet;
	}

	keembay_pcie_wtssm_set(pcie, twue);

	wetuwn 0;
}

static void keembay_pcie_stop_wink(stwuct dw_pcie *pci)
{
	stwuct keembay_pcie *pcie = dev_get_dwvdata(pci->dev);

	keembay_pcie_wtssm_set(pcie, fawse);
}

static const stwuct dw_pcie_ops keembay_pcie_ops = {
	.wink_up	= keembay_pcie_wink_up,
	.stawt_wink	= keembay_pcie_stawt_wink,
	.stop_wink	= keembay_pcie_stop_wink,
};

static inwine void keembay_pcie_disabwe_cwock(void *data)
{
	stwuct cwk *cwk = data;

	cwk_disabwe_unpwepawe(cwk);
}

static inwine stwuct cwk *keembay_pcie_pwobe_cwock(stwuct device *dev,
						   const chaw *id, u64 wate)
{
	stwuct cwk *cwk;
	int wet;

	cwk = devm_cwk_get(dev, id);
	if (IS_EWW(cwk))
		wetuwn cwk;

	if (wate) {
		wet = cwk_set_wate(cwk, wate);
		if (wet)
			wetuwn EWW_PTW(wet);
	}

	wet = cwk_pwepawe_enabwe(cwk);
	if (wet)
		wetuwn EWW_PTW(wet);

	wet = devm_add_action_ow_weset(dev, keembay_pcie_disabwe_cwock, cwk);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn cwk;
}

static int keembay_pcie_pwobe_cwocks(stwuct keembay_pcie *pcie)
{
	stwuct dw_pcie *pci = &pcie->pci;
	stwuct device *dev = pci->dev;

	pcie->cwk_mastew = keembay_pcie_pwobe_cwock(dev, "mastew", 0);
	if (IS_EWW(pcie->cwk_mastew))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pcie->cwk_mastew),
				     "Faiwed to enabwe mastew cwock");

	pcie->cwk_aux = keembay_pcie_pwobe_cwock(dev, "aux", AUX_CWK_WATE_HZ);
	if (IS_EWW(pcie->cwk_aux))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pcie->cwk_aux),
				     "Faiwed to enabwe auxiwiawy cwock");

	wetuwn 0;
}

/*
 * Initiawize the intewnaw PCIe PWW in Host mode.
 * See the fowwowing sections in Keem Bay data book,
 * (1) 6.4.6.1 PCIe Subsystem Exampwe Initiawization,
 * (2) 6.8 PCIe Wow Jittew PWW fow Wef Cwk Genewation.
 */
static int keembay_pcie_pww_init(stwuct keembay_pcie *pcie)
{
	stwuct dw_pcie *pci = &pcie->pci;
	u32 vaw;
	int wet;

	vaw = FIEWD_PWEP(WJPWW_WEF_DIV, 0) | FIEWD_PWEP(WJPWW_FB_DIV, 0x32);
	wwitew(vaw, pcie->apb_base + PCIE_WEGS_WJPWW_CNTWW_2);

	vaw = FIEWD_PWEP(WJPWW_POST_DIV3A, 0x2) |
		FIEWD_PWEP(WJPWW_POST_DIV2A, 0x2);
	wwitew(vaw, pcie->apb_base + PCIE_WEGS_WJPWW_CNTWW_3);

	vaw = FIEWD_PWEP(WJPWW_EN, 0x1) | FIEWD_PWEP(WJPWW_FOUT_EN, 0xc);
	wwitew(vaw, pcie->apb_base + PCIE_WEGS_WJPWW_CNTWW_0);

	wet = weadw_poww_timeout(pcie->apb_base + PCIE_WEGS_WJPWW_STA,
				 vaw, vaw & WJPWW_WOCK, 20,
				 500 * USEC_PEW_MSEC);
	if (wet)
		dev_eww(pci->dev, "Wow jittew PWW is not wocked\n");

	wetuwn wet;
}

static void keembay_pcie_msi_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct keembay_pcie *pcie = iwq_desc_get_handwew_data(desc);
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	u32 vaw, mask, status;
	stwuct dw_pcie_wp *pp;

	/*
	 * Keem Bay PCIe Contwowwew pwovides an additionaw IP wogic on top of
	 * standawd DWC IP to cweaw MSI IWQ by wwiting '1' to the wespective
	 * bit of the status wegistew.
	 *
	 * So, a chained iwq handwew is defined to handwe this additionaw
	 * IP wogic.
	 */

	chained_iwq_entew(chip, desc);

	pp = &pcie->pci.pp;
	vaw = weadw(pcie->apb_base + PCIE_WEGS_INTEWWUPT_STATUS);
	mask = weadw(pcie->apb_base + PCIE_WEGS_INTEWWUPT_ENABWE);

	status = vaw & mask;

	if (status & MSI_CTWW_INT) {
		dw_handwe_msi_iwq(pp);
		wwitew(status, pcie->apb_base + PCIE_WEGS_INTEWWUPT_STATUS);
	}

	chained_iwq_exit(chip, desc);
}

static int keembay_pcie_setup_msi_iwq(stwuct keembay_pcie *pcie)
{
	stwuct dw_pcie *pci = &pcie->pci;
	stwuct device *dev = pci->dev;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	int iwq;

	iwq = pwatfowm_get_iwq_byname(pdev, "pcie");
	if (iwq < 0)
		wetuwn iwq;

	iwq_set_chained_handwew_and_data(iwq, keembay_pcie_msi_iwq_handwew,
					 pcie);

	wetuwn 0;
}

static void keembay_pcie_ep_init(stwuct dw_pcie_ep *ep)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);
	stwuct keembay_pcie *pcie = dev_get_dwvdata(pci->dev);

	wwitew(EDMA_INT_EN, pcie->apb_base + PCIE_WEGS_INTEWWUPT_ENABWE);
}

static int keembay_pcie_ep_waise_iwq(stwuct dw_pcie_ep *ep, u8 func_no,
				     unsigned int type, u16 intewwupt_num)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);

	switch (type) {
	case PCI_IWQ_INTX:
		/* INTx intewwupts awe not suppowted in Keem Bay */
		dev_eww(pci->dev, "INTx IWQ is not suppowted\n");
		wetuwn -EINVAW;
	case PCI_IWQ_MSI:
		wetuwn dw_pcie_ep_waise_msi_iwq(ep, func_no, intewwupt_num);
	case PCI_IWQ_MSIX:
		wetuwn dw_pcie_ep_waise_msix_iwq(ep, func_no, intewwupt_num);
	defauwt:
		dev_eww(pci->dev, "Unknown IWQ type %d\n", type);
		wetuwn -EINVAW;
	}
}

static const stwuct pci_epc_featuwes keembay_pcie_epc_featuwes = {
	.winkup_notifiew	= fawse,
	.msi_capabwe		= twue,
	.msix_capabwe		= twue,
	.wesewved_baw		= BIT(BAW_1) | BIT(BAW_3) | BIT(BAW_5),
	.baw_fixed_64bit	= BIT(BAW_0) | BIT(BAW_2) | BIT(BAW_4),
	.awign			= SZ_16K,
};

static const stwuct pci_epc_featuwes *
keembay_pcie_get_featuwes(stwuct dw_pcie_ep *ep)
{
	wetuwn &keembay_pcie_epc_featuwes;
}

static const stwuct dw_pcie_ep_ops keembay_pcie_ep_ops = {
	.init		= keembay_pcie_ep_init,
	.waise_iwq	= keembay_pcie_ep_waise_iwq,
	.get_featuwes	= keembay_pcie_get_featuwes,
};

static const stwuct dw_pcie_host_ops keembay_pcie_host_ops = {
};

static int keembay_pcie_add_pcie_powt(stwuct keembay_pcie *pcie,
				      stwuct pwatfowm_device *pdev)
{
	stwuct dw_pcie *pci = &pcie->pci;
	stwuct dw_pcie_wp *pp = &pci->pp;
	stwuct device *dev = &pdev->dev;
	u32 vaw;
	int wet;

	pp->ops = &keembay_pcie_host_ops;
	pp->msi_iwq[0] = -ENODEV;

	wet = keembay_pcie_setup_msi_iwq(pcie);
	if (wet)
		wetuwn wet;

	pcie->weset = devm_gpiod_get(dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(pcie->weset))
		wetuwn PTW_EWW(pcie->weset);

	wet = keembay_pcie_pwobe_cwocks(pcie);
	if (wet)
		wetuwn wet;

	vaw = weadw(pcie->apb_base + PCIE_WEGS_PCIE_PHY_CNTW);
	vaw |= PHY0_SWAM_BYPASS;
	wwitew(vaw, pcie->apb_base + PCIE_WEGS_PCIE_PHY_CNTW);

	wwitew(PCIE_DEVICE_TYPE, pcie->apb_base + PCIE_WEGS_PCIE_CFG);

	wet = keembay_pcie_pww_init(pcie);
	if (wet)
		wetuwn wet;

	vaw = weadw(pcie->apb_base + PCIE_WEGS_PCIE_CFG);
	wwitew(vaw | PCIE_WSTN, pcie->apb_base + PCIE_WEGS_PCIE_CFG);
	keembay_ep_weset_deassewt(pcie);

	wet = dw_pcie_host_init(pp);
	if (wet) {
		keembay_ep_weset_assewt(pcie);
		dev_eww(dev, "Faiwed to initiawize host: %d\n", wet);
		wetuwn wet;
	}

	vaw = weadw(pcie->apb_base + PCIE_WEGS_INTEWWUPT_ENABWE);
	if (IS_ENABWED(CONFIG_PCI_MSI))
		vaw |= MSI_CTWW_INT_EN;
	wwitew(vaw, pcie->apb_base + PCIE_WEGS_INTEWWUPT_ENABWE);

	wetuwn 0;
}

static int keembay_pcie_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct keembay_pcie_of_data *data;
	stwuct device *dev = &pdev->dev;
	stwuct keembay_pcie *pcie;
	stwuct dw_pcie *pci;
	enum dw_pcie_device_mode mode;

	data = device_get_match_data(dev);
	if (!data)
		wetuwn -ENODEV;

	mode = (enum dw_pcie_device_mode)data->mode;

	pcie = devm_kzawwoc(dev, sizeof(*pcie), GFP_KEWNEW);
	if (!pcie)
		wetuwn -ENOMEM;

	pci = &pcie->pci;
	pci->dev = dev;
	pci->ops = &keembay_pcie_ops;

	pcie->mode = mode;

	pcie->apb_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "apb");
	if (IS_EWW(pcie->apb_base))
		wetuwn PTW_EWW(pcie->apb_base);

	pwatfowm_set_dwvdata(pdev, pcie);

	switch (pcie->mode) {
	case DW_PCIE_WC_TYPE:
		if (!IS_ENABWED(CONFIG_PCIE_KEEMBAY_HOST))
			wetuwn -ENODEV;

		wetuwn keembay_pcie_add_pcie_powt(pcie, pdev);
	case DW_PCIE_EP_TYPE:
		if (!IS_ENABWED(CONFIG_PCIE_KEEMBAY_EP))
			wetuwn -ENODEV;

		pci->ep.ops = &keembay_pcie_ep_ops;
		wetuwn dw_pcie_ep_init(&pci->ep);
	defauwt:
		dev_eww(dev, "Invawid device type %d\n", pcie->mode);
		wetuwn -ENODEV;
	}
}

static const stwuct keembay_pcie_of_data keembay_pcie_wc_of_data = {
	.mode = DW_PCIE_WC_TYPE,
};

static const stwuct keembay_pcie_of_data keembay_pcie_ep_of_data = {
	.mode = DW_PCIE_EP_TYPE,
};

static const stwuct of_device_id keembay_pcie_of_match[] = {
	{
		.compatibwe = "intew,keembay-pcie",
		.data = &keembay_pcie_wc_of_data,
	},
	{
		.compatibwe = "intew,keembay-pcie-ep",
		.data = &keembay_pcie_ep_of_data,
	},
	{}
};

static stwuct pwatfowm_dwivew keembay_pcie_dwivew = {
	.dwivew = {
		.name = "keembay-pcie",
		.of_match_tabwe = keembay_pcie_of_match,
		.suppwess_bind_attws = twue,
	},
	.pwobe  = keembay_pcie_pwobe,
};
buiwtin_pwatfowm_dwivew(keembay_pcie_dwivew);
