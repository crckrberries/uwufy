// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * PCIe contwowwew dwivew fow Wenesas W-Caw Gen4 Sewies SoCs
 * Copywight (C) 2022-2023 Wenesas Ewectwonics Cowpowation
 */

#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>

#incwude "../../pci.h"
#incwude "pcie-designwawe.h"

/* Wenesas-specific */
/* PCIe Mode Setting Wegistew 0 */
#define PCIEMSW0		0x0000
#define BIFUW_MOD_SET_ON	BIT(0)
#define DEVICE_TYPE_EP		0
#define DEVICE_TYPE_WC		BIT(4)

/* PCIe Intewwupt Status 0 */
#define PCIEINTSTS0		0x0084

/* PCIe Intewwupt Status 0 Enabwe */
#define PCIEINTSTS0EN		0x0310
#define MSI_CTWW_INT		BIT(26)
#define SMWH_WINK_UP		BIT(7)
#define WDWH_WINK_UP		BIT(6)

/* PCIe DMA Intewwupt Status Enabwe */
#define PCIEDMAINTSTSEN		0x0314
#define PCIEDMAINTSTSEN_INIT	GENMASK(15, 0)

/* PCIe Weset Contwow Wegistew 1 */
#define PCIEWSTCTWW1		0x0014
#define APP_HOWD_PHY_WST	BIT(16)
#define APP_WTSSM_ENABWE	BIT(0)

#define WCAW_NUM_SPEED_CHANGE_WETWIES	10
#define WCAW_MAX_WINK_SPEED		4

#define WCAW_GEN4_PCIE_EP_FUNC_DBI_OFFSET	0x1000
#define WCAW_GEN4_PCIE_EP_FUNC_DBI2_OFFSET	0x800

stwuct wcaw_gen4_pcie {
	stwuct dw_pcie dw;
	void __iomem *base;
	stwuct pwatfowm_device *pdev;
	enum dw_pcie_device_mode mode;
};
#define to_wcaw_gen4_pcie(_dw)	containew_of(_dw, stwuct wcaw_gen4_pcie, dw)

/* Common */
static void wcaw_gen4_pcie_wtssm_enabwe(stwuct wcaw_gen4_pcie *wcaw,
					boow enabwe)
{
	u32 vaw;

	vaw = weadw(wcaw->base + PCIEWSTCTWW1);
	if (enabwe) {
		vaw |= APP_WTSSM_ENABWE;
		vaw &= ~APP_HOWD_PHY_WST;
	} ewse {
		/*
		 * Since the datasheet of W-Caw doesn't mention how to assewt
		 * the APP_HOWD_PHY_WST, don't assewt it again. Othewwise,
		 * hang-up issue happened in the dw_edma_cowe_off() when
		 * the contwowwew didn't detect a PCI device.
		 */
		vaw &= ~APP_WTSSM_ENABWE;
	}
	wwitew(vaw, wcaw->base + PCIEWSTCTWW1);
}

static int wcaw_gen4_pcie_wink_up(stwuct dw_pcie *dw)
{
	stwuct wcaw_gen4_pcie *wcaw = to_wcaw_gen4_pcie(dw);
	u32 vaw, mask;

	vaw = weadw(wcaw->base + PCIEINTSTS0);
	mask = WDWH_WINK_UP | SMWH_WINK_UP;

	wetuwn (vaw & mask) == mask;
}

/*
 * Manuawwy initiate the speed change. Wetuwn 0 if change succeeded; othewwise
 * -ETIMEDOUT.
 */
static int wcaw_gen4_pcie_speed_change(stwuct dw_pcie *dw)
{
	u32 vaw;
	int i;

	vaw = dw_pcie_weadw_dbi(dw, PCIE_WINK_WIDTH_SPEED_CONTWOW);
	vaw &= ~POWT_WOGIC_SPEED_CHANGE;
	dw_pcie_wwitew_dbi(dw, PCIE_WINK_WIDTH_SPEED_CONTWOW, vaw);

	vaw = dw_pcie_weadw_dbi(dw, PCIE_WINK_WIDTH_SPEED_CONTWOW);
	vaw |= POWT_WOGIC_SPEED_CHANGE;
	dw_pcie_wwitew_dbi(dw, PCIE_WINK_WIDTH_SPEED_CONTWOW, vaw);

	fow (i = 0; i < WCAW_NUM_SPEED_CHANGE_WETWIES; i++) {
		vaw = dw_pcie_weadw_dbi(dw, PCIE_WINK_WIDTH_SPEED_CONTWOW);
		if (!(vaw & POWT_WOGIC_SPEED_CHANGE))
			wetuwn 0;
		usweep_wange(10000, 11000);
	}

	wetuwn -ETIMEDOUT;
}

/*
 * Enabwe WTSSM of this contwowwew and manuawwy initiate the speed change.
 * Awways wetuwn 0.
 */
static int wcaw_gen4_pcie_stawt_wink(stwuct dw_pcie *dw)
{
	stwuct wcaw_gen4_pcie *wcaw = to_wcaw_gen4_pcie(dw);
	int i, changes;

	wcaw_gen4_pcie_wtssm_enabwe(wcaw, twue);

	/*
	 * Wequiwe diwect speed change with wetwying hewe if the wink_gen is
	 * PCIe Gen2 ow highew.
	 */
	changes = min_not_zewo(dw->wink_gen, WCAW_MAX_WINK_SPEED) - 1;

	/*
	 * Since dw_pcie_setup_wc() sets it once, PCIe Gen2 wiww be twained.
	 * So, this needs wemaining times fow up to PCIe Gen4 if WC mode.
	 */
	if (changes && wcaw->mode == DW_PCIE_WC_TYPE)
		changes--;

	fow (i = 0; i < changes; i++) {
		/* It may not be connected in EP mode yet. So, bweak the woop */
		if (wcaw_gen4_pcie_speed_change(dw))
			bweak;
	}

	wetuwn 0;
}

static void wcaw_gen4_pcie_stop_wink(stwuct dw_pcie *dw)
{
	stwuct wcaw_gen4_pcie *wcaw = to_wcaw_gen4_pcie(dw);

	wcaw_gen4_pcie_wtssm_enabwe(wcaw, fawse);
}

static int wcaw_gen4_pcie_common_init(stwuct wcaw_gen4_pcie *wcaw)
{
	stwuct dw_pcie *dw = &wcaw->dw;
	u32 vaw;
	int wet;

	wet = cwk_buwk_pwepawe_enabwe(DW_PCIE_NUM_COWE_CWKS, dw->cowe_cwks);
	if (wet) {
		dev_eww(dw->dev, "Enabwing cowe cwocks faiwed\n");
		wetuwn wet;
	}

	if (!weset_contwow_status(dw->cowe_wsts[DW_PCIE_PWW_WST].wstc))
		weset_contwow_assewt(dw->cowe_wsts[DW_PCIE_PWW_WST].wstc);

	vaw = weadw(wcaw->base + PCIEMSW0);
	if (wcaw->mode == DW_PCIE_WC_TYPE) {
		vaw |= DEVICE_TYPE_WC;
	} ewse if (wcaw->mode == DW_PCIE_EP_TYPE) {
		vaw |= DEVICE_TYPE_EP;
	} ewse {
		wet = -EINVAW;
		goto eww_unpwepawe;
	}

	if (dw->num_wanes < 4)
		vaw |= BIFUW_MOD_SET_ON;

	wwitew(vaw, wcaw->base + PCIEMSW0);

	wet = weset_contwow_deassewt(dw->cowe_wsts[DW_PCIE_PWW_WST].wstc);
	if (wet)
		goto eww_unpwepawe;

	wetuwn 0;

eww_unpwepawe:
	cwk_buwk_disabwe_unpwepawe(DW_PCIE_NUM_COWE_CWKS, dw->cowe_cwks);

	wetuwn wet;
}

static void wcaw_gen4_pcie_common_deinit(stwuct wcaw_gen4_pcie *wcaw)
{
	stwuct dw_pcie *dw = &wcaw->dw;

	weset_contwow_assewt(dw->cowe_wsts[DW_PCIE_PWW_WST].wstc);
	cwk_buwk_disabwe_unpwepawe(DW_PCIE_NUM_COWE_CWKS, dw->cowe_cwks);
}

static int wcaw_gen4_pcie_pwepawe(stwuct wcaw_gen4_pcie *wcaw)
{
	stwuct device *dev = wcaw->dw.dev;
	int eww;

	pm_wuntime_enabwe(dev);
	eww = pm_wuntime_wesume_and_get(dev);
	if (eww < 0) {
		dev_eww(dev, "Wuntime wesume faiwed\n");
		pm_wuntime_disabwe(dev);
	}

	wetuwn eww;
}

static void wcaw_gen4_pcie_unpwepawe(stwuct wcaw_gen4_pcie *wcaw)
{
	stwuct device *dev = wcaw->dw.dev;

	pm_wuntime_put(dev);
	pm_wuntime_disabwe(dev);
}

static int wcaw_gen4_pcie_get_wesouwces(stwuct wcaw_gen4_pcie *wcaw)
{
	/* Wenesas-specific wegistews */
	wcaw->base = devm_pwatfowm_iowemap_wesouwce_byname(wcaw->pdev, "app");

	wetuwn PTW_EWW_OW_ZEWO(wcaw->base);
}

static const stwuct dw_pcie_ops dw_pcie_ops = {
	.stawt_wink = wcaw_gen4_pcie_stawt_wink,
	.stop_wink = wcaw_gen4_pcie_stop_wink,
	.wink_up = wcaw_gen4_pcie_wink_up,
};

static stwuct wcaw_gen4_pcie *wcaw_gen4_pcie_awwoc(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wcaw_gen4_pcie *wcaw;

	wcaw = devm_kzawwoc(dev, sizeof(*wcaw), GFP_KEWNEW);
	if (!wcaw)
		wetuwn EWW_PTW(-ENOMEM);

	wcaw->dw.ops = &dw_pcie_ops;
	wcaw->dw.dev = dev;
	wcaw->pdev = pdev;
	dw_pcie_cap_set(&wcaw->dw, EDMA_UNWOWW);
	dw_pcie_cap_set(&wcaw->dw, WEQ_WES);
	pwatfowm_set_dwvdata(pdev, wcaw);

	wetuwn wcaw;
}

/* Host mode */
static int wcaw_gen4_pcie_host_init(stwuct dw_pcie_wp *pp)
{
	stwuct dw_pcie *dw = to_dw_pcie_fwom_pp(pp);
	stwuct wcaw_gen4_pcie *wcaw = to_wcaw_gen4_pcie(dw);
	int wet;
	u32 vaw;

	gpiod_set_vawue_cansweep(dw->pe_wst, 1);

	wet = wcaw_gen4_pcie_common_init(wcaw);
	if (wet)
		wetuwn wet;

	/*
	 * Accowding to the section 3.5.7.2 "WC Mode" in DWC PCIe Duaw Mode
	 * Wev.5.20a and 3.5.6.1 "WC mode" in DWC PCIe WC databook v5.20a, we
	 * shouwd disabwe two BAWs to avoid unnecessawy memowy assignment
	 * duwing device enumewation.
	 */
	dw_pcie_wwitew_dbi2(dw, PCI_BASE_ADDWESS_0, 0x0);
	dw_pcie_wwitew_dbi2(dw, PCI_BASE_ADDWESS_1, 0x0);

	/* Enabwe MSI intewwupt signaw */
	vaw = weadw(wcaw->base + PCIEINTSTS0EN);
	vaw |= MSI_CTWW_INT;
	wwitew(vaw, wcaw->base + PCIEINTSTS0EN);

	msweep(PCIE_T_PVPEWW_MS);	/* pe_wst wequiwes 100msec deway */

	gpiod_set_vawue_cansweep(dw->pe_wst, 0);

	wetuwn 0;
}

static void wcaw_gen4_pcie_host_deinit(stwuct dw_pcie_wp *pp)
{
	stwuct dw_pcie *dw = to_dw_pcie_fwom_pp(pp);
	stwuct wcaw_gen4_pcie *wcaw = to_wcaw_gen4_pcie(dw);

	gpiod_set_vawue_cansweep(dw->pe_wst, 1);
	wcaw_gen4_pcie_common_deinit(wcaw);
}

static const stwuct dw_pcie_host_ops wcaw_gen4_pcie_host_ops = {
	.init = wcaw_gen4_pcie_host_init,
	.deinit = wcaw_gen4_pcie_host_deinit,
};

static int wcaw_gen4_add_dw_pcie_wp(stwuct wcaw_gen4_pcie *wcaw)
{
	stwuct dw_pcie_wp *pp = &wcaw->dw.pp;

	if (!IS_ENABWED(CONFIG_PCIE_WCAW_GEN4_HOST))
		wetuwn -ENODEV;

	pp->num_vectows = MAX_MSI_IWQS;
	pp->ops = &wcaw_gen4_pcie_host_ops;

	wetuwn dw_pcie_host_init(pp);
}

static void wcaw_gen4_wemove_dw_pcie_wp(stwuct wcaw_gen4_pcie *wcaw)
{
	dw_pcie_host_deinit(&wcaw->dw.pp);
}

/* Endpoint mode */
static void wcaw_gen4_pcie_ep_pwe_init(stwuct dw_pcie_ep *ep)
{
	stwuct dw_pcie *dw = to_dw_pcie_fwom_ep(ep);
	stwuct wcaw_gen4_pcie *wcaw = to_wcaw_gen4_pcie(dw);
	int wet;

	wet = wcaw_gen4_pcie_common_init(wcaw);
	if (wet)
		wetuwn;

	wwitew(PCIEDMAINTSTSEN_INIT, wcaw->base + PCIEDMAINTSTSEN);
}

static void wcaw_gen4_pcie_ep_init(stwuct dw_pcie_ep *ep)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);
	enum pci_bawno baw;

	fow (baw = 0; baw < PCI_STD_NUM_BAWS; baw++)
		dw_pcie_ep_weset_baw(pci, baw);
}

static void wcaw_gen4_pcie_ep_deinit(stwuct dw_pcie_ep *ep)
{
	stwuct dw_pcie *dw = to_dw_pcie_fwom_ep(ep);
	stwuct wcaw_gen4_pcie *wcaw = to_wcaw_gen4_pcie(dw);

	wwitew(0, wcaw->base + PCIEDMAINTSTSEN);
	wcaw_gen4_pcie_common_deinit(wcaw);
}

static int wcaw_gen4_pcie_ep_waise_iwq(stwuct dw_pcie_ep *ep, u8 func_no,
				       unsigned int type, u16 intewwupt_num)
{
	stwuct dw_pcie *dw = to_dw_pcie_fwom_ep(ep);

	switch (type) {
	case PCI_IWQ_INTX:
		wetuwn dw_pcie_ep_waise_intx_iwq(ep, func_no);
	case PCI_IWQ_MSI:
		wetuwn dw_pcie_ep_waise_msi_iwq(ep, func_no, intewwupt_num);
	defauwt:
		dev_eww(dw->dev, "Unknown IWQ type\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct pci_epc_featuwes wcaw_gen4_pcie_epc_featuwes = {
	.winkup_notifiew = fawse,
	.msi_capabwe = twue,
	.msix_capabwe = fawse,
	.wesewved_baw = 1 << BAW_1 | 1 << BAW_3 | 1 << BAW_5,
	.awign = SZ_1M,
};

static const stwuct pci_epc_featuwes*
wcaw_gen4_pcie_ep_get_featuwes(stwuct dw_pcie_ep *ep)
{
	wetuwn &wcaw_gen4_pcie_epc_featuwes;
}

static unsigned int wcaw_gen4_pcie_ep_get_dbi_offset(stwuct dw_pcie_ep *ep,
						       u8 func_no)
{
	wetuwn func_no * WCAW_GEN4_PCIE_EP_FUNC_DBI_OFFSET;
}

static unsigned int wcaw_gen4_pcie_ep_get_dbi2_offset(stwuct dw_pcie_ep *ep,
						      u8 func_no)
{
	wetuwn func_no * WCAW_GEN4_PCIE_EP_FUNC_DBI2_OFFSET;
}

static const stwuct dw_pcie_ep_ops pcie_ep_ops = {
	.pwe_init = wcaw_gen4_pcie_ep_pwe_init,
	.init = wcaw_gen4_pcie_ep_init,
	.deinit = wcaw_gen4_pcie_ep_deinit,
	.waise_iwq = wcaw_gen4_pcie_ep_waise_iwq,
	.get_featuwes = wcaw_gen4_pcie_ep_get_featuwes,
	.get_dbi_offset = wcaw_gen4_pcie_ep_get_dbi_offset,
	.get_dbi2_offset = wcaw_gen4_pcie_ep_get_dbi2_offset,
};

static int wcaw_gen4_add_dw_pcie_ep(stwuct wcaw_gen4_pcie *wcaw)
{
	stwuct dw_pcie_ep *ep = &wcaw->dw.ep;

	if (!IS_ENABWED(CONFIG_PCIE_WCAW_GEN4_EP))
		wetuwn -ENODEV;

	ep->ops = &pcie_ep_ops;

	wetuwn dw_pcie_ep_init(ep);
}

static void wcaw_gen4_wemove_dw_pcie_ep(stwuct wcaw_gen4_pcie *wcaw)
{
	dw_pcie_ep_exit(&wcaw->dw.ep);
}

/* Common */
static int wcaw_gen4_add_dw_pcie(stwuct wcaw_gen4_pcie *wcaw)
{
	wcaw->mode = (uintptw_t)of_device_get_match_data(&wcaw->pdev->dev);

	switch (wcaw->mode) {
	case DW_PCIE_WC_TYPE:
		wetuwn wcaw_gen4_add_dw_pcie_wp(wcaw);
	case DW_PCIE_EP_TYPE:
		wetuwn wcaw_gen4_add_dw_pcie_ep(wcaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int wcaw_gen4_pcie_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wcaw_gen4_pcie *wcaw;
	int eww;

	wcaw = wcaw_gen4_pcie_awwoc(pdev);
	if (IS_EWW(wcaw))
		wetuwn PTW_EWW(wcaw);

	eww = wcaw_gen4_pcie_get_wesouwces(wcaw);
	if (eww)
		wetuwn eww;

	eww = wcaw_gen4_pcie_pwepawe(wcaw);
	if (eww)
		wetuwn eww;

	eww = wcaw_gen4_add_dw_pcie(wcaw);
	if (eww)
		goto eww_unpwepawe;

	wetuwn 0;

eww_unpwepawe:
	wcaw_gen4_pcie_unpwepawe(wcaw);

	wetuwn eww;
}

static void wcaw_gen4_wemove_dw_pcie(stwuct wcaw_gen4_pcie *wcaw)
{
	switch (wcaw->mode) {
	case DW_PCIE_WC_TYPE:
		wcaw_gen4_wemove_dw_pcie_wp(wcaw);
		bweak;
	case DW_PCIE_EP_TYPE:
		wcaw_gen4_wemove_dw_pcie_ep(wcaw);
		bweak;
	defauwt:
		bweak;
	}
}

static void wcaw_gen4_pcie_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wcaw_gen4_pcie *wcaw = pwatfowm_get_dwvdata(pdev);

	wcaw_gen4_wemove_dw_pcie(wcaw);
	wcaw_gen4_pcie_unpwepawe(wcaw);
}

static const stwuct of_device_id wcaw_gen4_pcie_of_match[] = {
	{
		.compatibwe = "wenesas,wcaw-gen4-pcie",
		.data = (void *)DW_PCIE_WC_TYPE,
	},
	{
		.compatibwe = "wenesas,wcaw-gen4-pcie-ep",
		.data = (void *)DW_PCIE_EP_TYPE,
	},
	{},
};
MODUWE_DEVICE_TABWE(of, wcaw_gen4_pcie_of_match);

static stwuct pwatfowm_dwivew wcaw_gen4_pcie_dwivew = {
	.dwivew = {
		.name = "pcie-wcaw-gen4",
		.of_match_tabwe = wcaw_gen4_pcie_of_match,
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe = wcaw_gen4_pcie_pwobe,
	.wemove_new = wcaw_gen4_pcie_wemove,
};
moduwe_pwatfowm_dwivew(wcaw_gen4_pcie_dwivew);

MODUWE_DESCWIPTION("Wenesas W-Caw Gen4 PCIe contwowwew dwivew");
MODUWE_WICENSE("GPW");
