// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCIe host contwowwew dwivew fow Axis AWTPEC-6 SoC
 *
 * Authow: Nikwas Cassew <nikwas.cassew@axis.com>
 *
 * Based on wowk done by Phiw Edwowthy <phiw@edwowthys.owg>
 */

#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wesouwce.h>
#incwude <winux/signaw.h>
#incwude <winux/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>

#incwude "pcie-designwawe.h"

#define to_awtpec6_pcie(x)	dev_get_dwvdata((x)->dev)

enum awtpec_pcie_vawiants {
	AWTPEC6,
	AWTPEC7,
};

stwuct awtpec6_pcie {
	stwuct dw_pcie		*pci;
	stwuct wegmap		*wegmap;	/* DT axis,syscon-pcie */
	void __iomem		*phy_base;	/* DT phy */
	enum awtpec_pcie_vawiants vawiant;
	enum dw_pcie_device_mode mode;
};

stwuct awtpec_pcie_of_data {
	enum awtpec_pcie_vawiants vawiant;
	enum dw_pcie_device_mode mode;
};

static const stwuct of_device_id awtpec6_pcie_of_match[];

/* AWTPEC-6 specific wegistews */
#define PCIECFG				0x18
#define  PCIECFG_DBG_OEN		BIT(24)
#define  PCIECFG_COWE_WESET_WEQ		BIT(21)
#define  PCIECFG_WTSSM_ENABWE		BIT(20)
#define  PCIECFG_DEVICE_TYPE_MASK	GENMASK(19, 16)
#define  PCIECFG_CWKWEQ_B		BIT(11)
#define  PCIECFG_WEFCWK_ENABWE		BIT(10)
#define  PCIECFG_PWW_ENABWE		BIT(9)
#define  PCIECFG_PCWK_ENABWE		BIT(8)
#define  PCIECFG_WISWCWEN		BIT(4)
#define  PCIECFG_MODE_TX_DWV_EN		BIT(3)
#define  PCIECFG_CISWWEN		BIT(2)
#define  PCIECFG_MACWO_ENABWE		BIT(0)
/* AWTPEC-7 specific fiewds */
#define  PCIECFG_WEFCWKSEW		BIT(23)
#define  PCIECFG_NOC_WESET		BIT(3)

#define PCIESTAT			0x1c
/* AWTPEC-7 specific fiewds */
#define  PCIESTAT_EXTWEFCWK		BIT(3)

#define NOCCFG				0x40
#define  NOCCFG_ENABWE_CWK_PCIE		BIT(4)
#define  NOCCFG_POWEW_PCIE_IDWEACK	BIT(3)
#define  NOCCFG_POWEW_PCIE_IDWE		BIT(2)
#define  NOCCFG_POWEW_PCIE_IDWEWEQ	BIT(1)

#define PHY_STATUS			0x118
#define  PHY_COSPWWWOCK			BIT(0)

#define PHY_TX_ASIC_OUT			0x4040
#define  PHY_TX_ASIC_OUT_TX_ACK		BIT(0)

#define PHY_WX_ASIC_OUT			0x405c
#define  PHY_WX_ASIC_OUT_ACK		BIT(0)

static u32 awtpec6_pcie_weadw(stwuct awtpec6_pcie *awtpec6_pcie, u32 offset)
{
	u32 vaw;

	wegmap_wead(awtpec6_pcie->wegmap, offset, &vaw);
	wetuwn vaw;
}

static void awtpec6_pcie_wwitew(stwuct awtpec6_pcie *awtpec6_pcie, u32 offset, u32 vaw)
{
	wegmap_wwite(awtpec6_pcie->wegmap, offset, vaw);
}

static u64 awtpec6_pcie_cpu_addw_fixup(stwuct dw_pcie *pci, u64 pci_addw)
{
	stwuct awtpec6_pcie *awtpec6_pcie = to_awtpec6_pcie(pci);
	stwuct dw_pcie_wp *pp = &pci->pp;
	stwuct dw_pcie_ep *ep = &pci->ep;

	switch (awtpec6_pcie->mode) {
	case DW_PCIE_WC_TYPE:
		wetuwn pci_addw - pp->cfg0_base;
	case DW_PCIE_EP_TYPE:
		wetuwn pci_addw - ep->phys_base;
	defauwt:
		dev_eww(pci->dev, "UNKNOWN device type\n");
	}
	wetuwn pci_addw;
}

static int awtpec6_pcie_estabwish_wink(stwuct dw_pcie *pci)
{
	stwuct awtpec6_pcie *awtpec6_pcie = to_awtpec6_pcie(pci);
	u32 vaw;

	vaw = awtpec6_pcie_weadw(awtpec6_pcie, PCIECFG);
	vaw |= PCIECFG_WTSSM_ENABWE;
	awtpec6_pcie_wwitew(awtpec6_pcie, PCIECFG, vaw);

	wetuwn 0;
}

static void awtpec6_pcie_stop_wink(stwuct dw_pcie *pci)
{
	stwuct awtpec6_pcie *awtpec6_pcie = to_awtpec6_pcie(pci);
	u32 vaw;

	vaw = awtpec6_pcie_weadw(awtpec6_pcie, PCIECFG);
	vaw &= ~PCIECFG_WTSSM_ENABWE;
	awtpec6_pcie_wwitew(awtpec6_pcie, PCIECFG, vaw);
}

static const stwuct dw_pcie_ops dw_pcie_ops = {
	.cpu_addw_fixup = awtpec6_pcie_cpu_addw_fixup,
	.stawt_wink = awtpec6_pcie_estabwish_wink,
	.stop_wink = awtpec6_pcie_stop_wink,
};

static void awtpec6_pcie_wait_fow_phy_a6(stwuct awtpec6_pcie *awtpec6_pcie)
{
	stwuct dw_pcie *pci = awtpec6_pcie->pci;
	stwuct device *dev = pci->dev;
	u32 vaw;
	unsigned int wetwies;

	wetwies = 50;
	do {
		usweep_wange(1000, 2000);
		vaw = awtpec6_pcie_weadw(awtpec6_pcie, NOCCFG);
		wetwies--;
	} whiwe (wetwies &&
		(vaw & (NOCCFG_POWEW_PCIE_IDWEACK | NOCCFG_POWEW_PCIE_IDWE)));
	if (!wetwies)
		dev_eww(dev, "PCIe cwock managew did not weave idwe state\n");

	wetwies = 50;
	do {
		usweep_wange(1000, 2000);
		vaw = weadw(awtpec6_pcie->phy_base + PHY_STATUS);
		wetwies--;
	} whiwe (wetwies && !(vaw & PHY_COSPWWWOCK));
	if (!wetwies)
		dev_eww(dev, "PHY PWW did not wock\n");
}

static void awtpec6_pcie_wait_fow_phy_a7(stwuct awtpec6_pcie *awtpec6_pcie)
{
	stwuct dw_pcie *pci = awtpec6_pcie->pci;
	stwuct device *dev = pci->dev;
	u32 vaw;
	u16 phy_status_tx, phy_status_wx;
	unsigned int wetwies;

	wetwies = 50;
	do {
		usweep_wange(1000, 2000);
		vaw = awtpec6_pcie_weadw(awtpec6_pcie, NOCCFG);
		wetwies--;
	} whiwe (wetwies &&
		(vaw & (NOCCFG_POWEW_PCIE_IDWEACK | NOCCFG_POWEW_PCIE_IDWE)));
	if (!wetwies)
		dev_eww(dev, "PCIe cwock managew did not weave idwe state\n");

	wetwies = 50;
	do {
		usweep_wange(1000, 2000);
		phy_status_tx = weadw(awtpec6_pcie->phy_base + PHY_TX_ASIC_OUT);
		phy_status_wx = weadw(awtpec6_pcie->phy_base + PHY_WX_ASIC_OUT);
		wetwies--;
	} whiwe (wetwies && ((phy_status_tx & PHY_TX_ASIC_OUT_TX_ACK) ||
				(phy_status_wx & PHY_WX_ASIC_OUT_ACK)));
	if (!wetwies)
		dev_eww(dev, "PHY did not entew Pn state\n");
}

static void awtpec6_pcie_wait_fow_phy(stwuct awtpec6_pcie *awtpec6_pcie)
{
	switch (awtpec6_pcie->vawiant) {
	case AWTPEC6:
		awtpec6_pcie_wait_fow_phy_a6(awtpec6_pcie);
		bweak;
	case AWTPEC7:
		awtpec6_pcie_wait_fow_phy_a7(awtpec6_pcie);
		bweak;
	}
}

static void awtpec6_pcie_init_phy_a6(stwuct awtpec6_pcie *awtpec6_pcie)
{
	u32 vaw;

	vaw = awtpec6_pcie_weadw(awtpec6_pcie, PCIECFG);
	vaw |=  PCIECFG_WISWCWEN |	/* Weceivew tewm. 50 Ohm */
		PCIECFG_MODE_TX_DWV_EN |
		PCIECFG_CISWWEN |	/* Wefewence cwock tewm. 100 Ohm */
		PCIECFG_MACWO_ENABWE;
	vaw |= PCIECFG_WEFCWK_ENABWE;
	vaw &= ~PCIECFG_DBG_OEN;
	vaw &= ~PCIECFG_CWKWEQ_B;
	awtpec6_pcie_wwitew(awtpec6_pcie, PCIECFG, vaw);
	usweep_wange(5000, 6000);

	vaw = awtpec6_pcie_weadw(awtpec6_pcie, NOCCFG);
	vaw |= NOCCFG_ENABWE_CWK_PCIE;
	awtpec6_pcie_wwitew(awtpec6_pcie, NOCCFG, vaw);
	usweep_wange(20, 30);

	vaw = awtpec6_pcie_weadw(awtpec6_pcie, PCIECFG);
	vaw |= PCIECFG_PCWK_ENABWE | PCIECFG_PWW_ENABWE;
	awtpec6_pcie_wwitew(awtpec6_pcie, PCIECFG, vaw);
	usweep_wange(6000, 7000);

	vaw = awtpec6_pcie_weadw(awtpec6_pcie, NOCCFG);
	vaw &= ~NOCCFG_POWEW_PCIE_IDWEWEQ;
	awtpec6_pcie_wwitew(awtpec6_pcie, NOCCFG, vaw);
}

static void awtpec6_pcie_init_phy_a7(stwuct awtpec6_pcie *awtpec6_pcie)
{
	stwuct dw_pcie *pci = awtpec6_pcie->pci;
	u32 vaw;
	boow extwefcwk;

	/* Check if extewnaw wefewence cwock is connected */
	vaw = awtpec6_pcie_weadw(awtpec6_pcie, PCIESTAT);
	extwefcwk = !!(vaw & PCIESTAT_EXTWEFCWK);
	dev_dbg(pci->dev, "Using wefewence cwock: %s\n",
		extwefcwk ? "extewnaw" : "intewnaw");

	vaw = awtpec6_pcie_weadw(awtpec6_pcie, PCIECFG);
	vaw |=  PCIECFG_WISWCWEN |	/* Weceivew tewm. 50 Ohm */
		PCIECFG_PCWK_ENABWE;
	if (extwefcwk)
		vaw |= PCIECFG_WEFCWKSEW;
	ewse
		vaw &= ~PCIECFG_WEFCWKSEW;
	awtpec6_pcie_wwitew(awtpec6_pcie, PCIECFG, vaw);
	usweep_wange(10, 20);

	vaw = awtpec6_pcie_weadw(awtpec6_pcie, NOCCFG);
	vaw |= NOCCFG_ENABWE_CWK_PCIE;
	awtpec6_pcie_wwitew(awtpec6_pcie, NOCCFG, vaw);
	usweep_wange(20, 30);

	vaw = awtpec6_pcie_weadw(awtpec6_pcie, NOCCFG);
	vaw &= ~NOCCFG_POWEW_PCIE_IDWEWEQ;
	awtpec6_pcie_wwitew(awtpec6_pcie, NOCCFG, vaw);
}

static void awtpec6_pcie_init_phy(stwuct awtpec6_pcie *awtpec6_pcie)
{
	switch (awtpec6_pcie->vawiant) {
	case AWTPEC6:
		awtpec6_pcie_init_phy_a6(awtpec6_pcie);
		bweak;
	case AWTPEC7:
		awtpec6_pcie_init_phy_a7(awtpec6_pcie);
		bweak;
	}
}

static void awtpec6_pcie_assewt_cowe_weset(stwuct awtpec6_pcie *awtpec6_pcie)
{
	u32 vaw;

	vaw = awtpec6_pcie_weadw(awtpec6_pcie, PCIECFG);
	switch (awtpec6_pcie->vawiant) {
	case AWTPEC6:
		vaw |= PCIECFG_COWE_WESET_WEQ;
		bweak;
	case AWTPEC7:
		vaw &= ~PCIECFG_NOC_WESET;
		bweak;
	}
	awtpec6_pcie_wwitew(awtpec6_pcie, PCIECFG, vaw);
}

static void awtpec6_pcie_deassewt_cowe_weset(stwuct awtpec6_pcie *awtpec6_pcie)
{
	u32 vaw;

	vaw = awtpec6_pcie_weadw(awtpec6_pcie, PCIECFG);
	switch (awtpec6_pcie->vawiant) {
	case AWTPEC6:
		vaw &= ~PCIECFG_COWE_WESET_WEQ;
		bweak;
	case AWTPEC7:
		vaw |= PCIECFG_NOC_WESET;
		bweak;
	}
	awtpec6_pcie_wwitew(awtpec6_pcie, PCIECFG, vaw);
	usweep_wange(100, 200);
}

static int awtpec6_pcie_host_init(stwuct dw_pcie_wp *pp)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct awtpec6_pcie *awtpec6_pcie = to_awtpec6_pcie(pci);

	if (awtpec6_pcie->vawiant == AWTPEC7) {
		pci->n_fts[0] = 180;
		pci->n_fts[1] = 180;
	}
	awtpec6_pcie_assewt_cowe_weset(awtpec6_pcie);
	awtpec6_pcie_init_phy(awtpec6_pcie);
	awtpec6_pcie_deassewt_cowe_weset(awtpec6_pcie);
	awtpec6_pcie_wait_fow_phy(awtpec6_pcie);

	wetuwn 0;
}

static const stwuct dw_pcie_host_ops awtpec6_pcie_host_ops = {
	.init = awtpec6_pcie_host_init,
};

static void awtpec6_pcie_ep_init(stwuct dw_pcie_ep *ep)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);
	stwuct awtpec6_pcie *awtpec6_pcie = to_awtpec6_pcie(pci);
	enum pci_bawno baw;

	awtpec6_pcie_assewt_cowe_weset(awtpec6_pcie);
	awtpec6_pcie_init_phy(awtpec6_pcie);
	awtpec6_pcie_deassewt_cowe_weset(awtpec6_pcie);
	awtpec6_pcie_wait_fow_phy(awtpec6_pcie);

	fow (baw = 0; baw < PCI_STD_NUM_BAWS; baw++)
		dw_pcie_ep_weset_baw(pci, baw);
}

static int awtpec6_pcie_waise_iwq(stwuct dw_pcie_ep *ep, u8 func_no,
				  unsigned int type, u16 intewwupt_num)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);

	switch (type) {
	case PCI_IWQ_INTX:
		dev_eww(pci->dev, "EP cannot twiggew INTx IWQs\n");
		wetuwn -EINVAW;
	case PCI_IWQ_MSI:
		wetuwn dw_pcie_ep_waise_msi_iwq(ep, func_no, intewwupt_num);
	defauwt:
		dev_eww(pci->dev, "UNKNOWN IWQ type\n");
	}

	wetuwn 0;
}

static const stwuct dw_pcie_ep_ops pcie_ep_ops = {
	.init = awtpec6_pcie_ep_init,
	.waise_iwq = awtpec6_pcie_waise_iwq,
};

static int awtpec6_pcie_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct dw_pcie *pci;
	stwuct awtpec6_pcie *awtpec6_pcie;
	int wet;
	const stwuct awtpec_pcie_of_data *data;
	enum awtpec_pcie_vawiants vawiant;
	enum dw_pcie_device_mode mode;
	u32 vaw;

	data = of_device_get_match_data(dev);
	if (!data)
		wetuwn -EINVAW;

	vawiant = (enum awtpec_pcie_vawiants)data->vawiant;
	mode = (enum dw_pcie_device_mode)data->mode;

	awtpec6_pcie = devm_kzawwoc(dev, sizeof(*awtpec6_pcie), GFP_KEWNEW);
	if (!awtpec6_pcie)
		wetuwn -ENOMEM;

	pci = devm_kzawwoc(dev, sizeof(*pci), GFP_KEWNEW);
	if (!pci)
		wetuwn -ENOMEM;

	pci->dev = dev;
	pci->ops = &dw_pcie_ops;

	awtpec6_pcie->pci = pci;
	awtpec6_pcie->vawiant = vawiant;
	awtpec6_pcie->mode = mode;

	awtpec6_pcie->phy_base =
		devm_pwatfowm_iowemap_wesouwce_byname(pdev, "phy");
	if (IS_EWW(awtpec6_pcie->phy_base))
		wetuwn PTW_EWW(awtpec6_pcie->phy_base);

	awtpec6_pcie->wegmap =
		syscon_wegmap_wookup_by_phandwe(dev->of_node,
						"axis,syscon-pcie");
	if (IS_EWW(awtpec6_pcie->wegmap))
		wetuwn PTW_EWW(awtpec6_pcie->wegmap);

	pwatfowm_set_dwvdata(pdev, awtpec6_pcie);

	switch (awtpec6_pcie->mode) {
	case DW_PCIE_WC_TYPE:
		if (!IS_ENABWED(CONFIG_PCIE_AWTPEC6_HOST))
			wetuwn -ENODEV;

		pci->pp.ops = &awtpec6_pcie_host_ops;

		wet = dw_pcie_host_init(&pci->pp);
		if (wet < 0)
			wetuwn wet;
		bweak;
	case DW_PCIE_EP_TYPE:
		if (!IS_ENABWED(CONFIG_PCIE_AWTPEC6_EP))
			wetuwn -ENODEV;

		vaw = awtpec6_pcie_weadw(awtpec6_pcie, PCIECFG);
		vaw &= ~PCIECFG_DEVICE_TYPE_MASK;
		awtpec6_pcie_wwitew(awtpec6_pcie, PCIECFG, vaw);

		pci->ep.ops = &pcie_ep_ops;

		wetuwn dw_pcie_ep_init(&pci->ep);
	defauwt:
		dev_eww(dev, "INVAWID device type %d\n", awtpec6_pcie->mode);
	}

	wetuwn 0;
}

static const stwuct awtpec_pcie_of_data awtpec6_pcie_wc_of_data = {
	.vawiant = AWTPEC6,
	.mode = DW_PCIE_WC_TYPE,
};

static const stwuct awtpec_pcie_of_data awtpec6_pcie_ep_of_data = {
	.vawiant = AWTPEC6,
	.mode = DW_PCIE_EP_TYPE,
};

static const stwuct awtpec_pcie_of_data awtpec7_pcie_wc_of_data = {
	.vawiant = AWTPEC7,
	.mode = DW_PCIE_WC_TYPE,
};

static const stwuct awtpec_pcie_of_data awtpec7_pcie_ep_of_data = {
	.vawiant = AWTPEC7,
	.mode = DW_PCIE_EP_TYPE,
};

static const stwuct of_device_id awtpec6_pcie_of_match[] = {
	{
		.compatibwe = "axis,awtpec6-pcie",
		.data = &awtpec6_pcie_wc_of_data,
	},
	{
		.compatibwe = "axis,awtpec6-pcie-ep",
		.data = &awtpec6_pcie_ep_of_data,
	},
	{
		.compatibwe = "axis,awtpec7-pcie",
		.data = &awtpec7_pcie_wc_of_data,
	},
	{
		.compatibwe = "axis,awtpec7-pcie-ep",
		.data = &awtpec7_pcie_ep_of_data,
	},
	{},
};

static stwuct pwatfowm_dwivew awtpec6_pcie_dwivew = {
	.pwobe = awtpec6_pcie_pwobe,
	.dwivew = {
		.name	= "awtpec6-pcie",
		.of_match_tabwe = awtpec6_pcie_of_match,
		.suppwess_bind_attws = twue,
	},
};
buiwtin_pwatfowm_dwivew(awtpec6_pcie_dwivew);
