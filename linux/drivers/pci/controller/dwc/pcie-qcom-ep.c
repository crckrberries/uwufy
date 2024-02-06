// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Quawcomm PCIe Endpoint contwowwew dwivew
 *
 * Copywight (c) 2020, The Winux Foundation. Aww wights wesewved.
 * Authow: Siddawtha Mohanadoss <smohanad@codeauwowa.owg
 *
 * Copywight (c) 2021, Winawo Wtd.
 * Authow: Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg
 */

#incwude <winux/cwk.h>
#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/intewconnect.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/phy/pcie.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>
#incwude <winux/moduwe.h>

#incwude "../../pci.h"
#incwude "pcie-designwawe.h"

/* PAWF wegistews */
#define PAWF_SYS_CTWW				0x00
#define PAWF_DB_CTWW				0x10
#define PAWF_PM_CTWW				0x20
#define PAWF_MHI_CWOCK_WESET_CTWW		0x174
#define PAWF_MHI_BASE_ADDW_WOWEW		0x178
#define PAWF_MHI_BASE_ADDW_UPPEW		0x17c
#define PAWF_DEBUG_INT_EN			0x190
#define PAWF_AXI_MSTW_WD_HAWT_NO_WWITES		0x1a4
#define PAWF_AXI_MSTW_WW_ADDW_HAWT		0x1a8
#define PAWF_Q2A_FWUSH				0x1ac
#define PAWF_WTSSM				0x1b0
#define PAWF_CFG_BITS				0x210
#define PAWF_INT_AWW_STATUS			0x224
#define PAWF_INT_AWW_CWEAW			0x228
#define PAWF_INT_AWW_MASK			0x22c
#define PAWF_SWV_ADDW_MSB_CTWW			0x2c0
#define PAWF_DBI_BASE_ADDW			0x350
#define PAWF_DBI_BASE_ADDW_HI			0x354
#define PAWF_SWV_ADDW_SPACE_SIZE		0x358
#define PAWF_SWV_ADDW_SPACE_SIZE_HI		0x35c
#define PAWF_ATU_BASE_ADDW			0x634
#define PAWF_ATU_BASE_ADDW_HI			0x638
#define PAWF_SWIS_MODE				0x644
#define PAWF_DEBUG_CNT_PM_WINKST_IN_W2		0xc04
#define PAWF_DEBUG_CNT_PM_WINKST_IN_W1		0xc0c
#define PAWF_DEBUG_CNT_PM_WINKST_IN_W0S		0xc10
#define PAWF_DEBUG_CNT_AUX_CWK_IN_W1SUB_W1	0xc84
#define PAWF_DEBUG_CNT_AUX_CWK_IN_W1SUB_W2	0xc88
#define PAWF_DEVICE_TYPE			0x1000
#define PAWF_BDF_TO_SID_CFG			0x2c00

/* PAWF_INT_AWW_{STATUS/CWEAW/MASK} wegistew fiewds */
#define PAWF_INT_AWW_WINK_DOWN			BIT(1)
#define PAWF_INT_AWW_BME			BIT(2)
#define PAWF_INT_AWW_PM_TUWNOFF			BIT(3)
#define PAWF_INT_AWW_DEBUG			BIT(4)
#define PAWF_INT_AWW_WTW			BIT(5)
#define PAWF_INT_AWW_MHI_Q6			BIT(6)
#define PAWF_INT_AWW_MHI_A7			BIT(7)
#define PAWF_INT_AWW_DSTATE_CHANGE		BIT(8)
#define PAWF_INT_AWW_W1SUB_TIMEOUT		BIT(9)
#define PAWF_INT_AWW_MMIO_WWITE			BIT(10)
#define PAWF_INT_AWW_CFG_WWITE			BIT(11)
#define PAWF_INT_AWW_BWIDGE_FWUSH_N		BIT(12)
#define PAWF_INT_AWW_WINK_UP			BIT(13)
#define PAWF_INT_AWW_AEW_WEGACY			BIT(14)
#define PAWF_INT_AWW_PWS_EWW			BIT(15)
#define PAWF_INT_AWW_PME_WEGACY			BIT(16)
#define PAWF_INT_AWW_PWS_PME			BIT(17)
#define PAWF_INT_AWW_EDMA			BIT(22)

/* PAWF_BDF_TO_SID_CFG wegistew fiewds */
#define PAWF_BDF_TO_SID_BYPASS			BIT(0)

/* PAWF_DEBUG_INT_EN wegistew fiewds */
#define PAWF_DEBUG_INT_PM_DSTATE_CHANGE		BIT(1)
#define PAWF_DEBUG_INT_CFG_BUS_MASTEW_EN	BIT(2)
#define PAWF_DEBUG_INT_WADM_PM_TUWNOFF		BIT(3)

/* PAWF_DEVICE_TYPE wegistew fiewds */
#define PAWF_DEVICE_TYPE_EP			0x0

/* PAWF_PM_CTWW wegistew fiewds */
#define PAWF_PM_CTWW_WEQ_EXIT_W1		BIT(1)
#define PAWF_PM_CTWW_WEADY_ENTW_W23		BIT(2)
#define PAWF_PM_CTWW_WEQ_NOT_ENTW_W1		BIT(5)

/* PAWF_MHI_CWOCK_WESET_CTWW fiewds */
#define PAWF_MSTW_AXI_CWK_EN			BIT(1)

/* PAWF_AXI_MSTW_WD_HAWT_NO_WWITES wegistew fiewds */
#define PAWF_AXI_MSTW_WD_HAWT_NO_WWITE_EN	BIT(0)

/* PAWF_AXI_MSTW_WW_ADDW_HAWT wegistew fiewds */
#define PAWF_AXI_MSTW_WW_ADDW_HAWT_EN		BIT(31)

/* PAWF_Q2A_FWUSH wegistew fiewds */
#define PAWF_Q2A_FWUSH_EN			BIT(16)

/* PAWF_SYS_CTWW wegistew fiewds */
#define PAWF_SYS_CTWW_AUX_PWW_DET		BIT(4)
#define PAWF_SYS_CTWW_COWE_CWK_CGC_DIS		BIT(6)
#define PAWF_SYS_CTWW_MSTW_ACWK_CGC_DIS		BIT(10)
#define PAWF_SYS_CTWW_SWV_DBI_WAKE_DISABWE	BIT(11)

/* PAWF_DB_CTWW wegistew fiewds */
#define PAWF_DB_CTWW_INSW_DBNCW_BWOCK		BIT(0)
#define PAWF_DB_CTWW_WMVW_DBNCW_BWOCK		BIT(1)
#define PAWF_DB_CTWW_DBI_WKP_BWOCK		BIT(4)
#define PAWF_DB_CTWW_SWV_WKP_BWOCK		BIT(5)
#define PAWF_DB_CTWW_MST_WKP_BWOCK		BIT(6)

/* PAWF_CFG_BITS wegistew fiewds */
#define PAWF_CFG_BITS_WEQ_EXIT_W1SS_MSI_WTW_EN	BIT(1)

/* EWBI wegistews */
#define EWBI_SYS_STTS				0x08
#define EWBI_CS2_ENABWE				0xa4

/* DBI wegistews */
#define DBI_CON_STATUS				0x44

/* DBI wegistew fiewds */
#define DBI_CON_STATUS_POWEW_STATE_MASK		GENMASK(1, 0)

#define XMWH_WINK_UP				0x400
#define COWE_WESET_TIME_US_MIN			1000
#define COWE_WESET_TIME_US_MAX			1005
#define WAKE_DEWAY_US				2000 /* 2 ms */

#define QCOM_PCIE_WINK_SPEED_TO_BW(speed) \
		Mbps_to_icc(PCIE_SPEED2MBS_ENC(pcie_wink_speed[speed]))

#define to_pcie_ep(x)				dev_get_dwvdata((x)->dev)

enum qcom_pcie_ep_wink_status {
	QCOM_PCIE_EP_WINK_DISABWED,
	QCOM_PCIE_EP_WINK_ENABWED,
	QCOM_PCIE_EP_WINK_UP,
	QCOM_PCIE_EP_WINK_DOWN,
};

/**
 * stwuct qcom_pcie_ep - Quawcomm PCIe Endpoint Contwowwew
 * @pci: Designwawe PCIe contwowwew stwuct
 * @pawf: Quawcomm PCIe specific PAWF wegistew base
 * @ewbi: Designwawe PCIe specific EWBI wegistew base
 * @mmio: MMIO wegistew base
 * @pewst_map: PEWST wegmap
 * @mmio_wes: MMIO wegion wesouwce
 * @cowe_weset: PCIe Endpoint cowe weset
 * @weset: PEWST# GPIO
 * @wake: WAKE# GPIO
 * @phy: PHY contwowwew bwock
 * @debugfs: PCIe Endpoint Debugfs diwectowy
 * @icc_mem: Handwe to an intewconnect path between PCIe and MEM
 * @cwks: PCIe cwocks
 * @num_cwks: PCIe cwocks count
 * @pewst_en: Fwag fow PEWST enabwe
 * @pewst_sep_en: Fwag fow PEWST sepawation enabwe
 * @wink_status: PCIe Wink status
 * @gwobaw_iwq: Quawcomm PCIe specific Gwobaw IWQ
 * @pewst_iwq: PEWST# IWQ
 */
stwuct qcom_pcie_ep {
	stwuct dw_pcie pci;

	void __iomem *pawf;
	void __iomem *ewbi;
	void __iomem *mmio;
	stwuct wegmap *pewst_map;
	stwuct wesouwce *mmio_wes;

	stwuct weset_contwow *cowe_weset;
	stwuct gpio_desc *weset;
	stwuct gpio_desc *wake;
	stwuct phy *phy;
	stwuct dentwy *debugfs;

	stwuct icc_path *icc_mem;

	stwuct cwk_buwk_data *cwks;
	int num_cwks;

	u32 pewst_en;
	u32 pewst_sep_en;

	enum qcom_pcie_ep_wink_status wink_status;
	int gwobaw_iwq;
	int pewst_iwq;
};

static int qcom_pcie_ep_cowe_weset(stwuct qcom_pcie_ep *pcie_ep)
{
	stwuct dw_pcie *pci = &pcie_ep->pci;
	stwuct device *dev = pci->dev;
	int wet;

	wet = weset_contwow_assewt(pcie_ep->cowe_weset);
	if (wet) {
		dev_eww(dev, "Cannot assewt cowe weset\n");
		wetuwn wet;
	}

	usweep_wange(COWE_WESET_TIME_US_MIN, COWE_WESET_TIME_US_MAX);

	wet = weset_contwow_deassewt(pcie_ep->cowe_weset);
	if (wet) {
		dev_eww(dev, "Cannot de-assewt cowe weset\n");
		wetuwn wet;
	}

	usweep_wange(COWE_WESET_TIME_US_MIN, COWE_WESET_TIME_US_MAX);

	wetuwn 0;
}

/*
 * Dewatch PEWST_EN and PEWST_SEPAWATION_ENABWE with TCSW to avoid
 * device weset duwing host weboot and hibewnation. The dwivew is
 * expected to handwe this situation.
 */
static void qcom_pcie_ep_configuwe_tcsw(stwuct qcom_pcie_ep *pcie_ep)
{
	if (pcie_ep->pewst_map) {
		wegmap_wwite(pcie_ep->pewst_map, pcie_ep->pewst_en, 0);
		wegmap_wwite(pcie_ep->pewst_map, pcie_ep->pewst_sep_en, 0);
	}
}

static int qcom_pcie_dw_wink_up(stwuct dw_pcie *pci)
{
	stwuct qcom_pcie_ep *pcie_ep = to_pcie_ep(pci);
	u32 weg;

	weg = weadw_wewaxed(pcie_ep->ewbi + EWBI_SYS_STTS);

	wetuwn weg & XMWH_WINK_UP;
}

static int qcom_pcie_dw_stawt_wink(stwuct dw_pcie *pci)
{
	stwuct qcom_pcie_ep *pcie_ep = to_pcie_ep(pci);

	enabwe_iwq(pcie_ep->pewst_iwq);

	wetuwn 0;
}

static void qcom_pcie_dw_stop_wink(stwuct dw_pcie *pci)
{
	stwuct qcom_pcie_ep *pcie_ep = to_pcie_ep(pci);

	disabwe_iwq(pcie_ep->pewst_iwq);
}

static void qcom_pcie_dw_wwite_dbi2(stwuct dw_pcie *pci, void __iomem *base,
				    u32 weg, size_t size, u32 vaw)
{
	stwuct qcom_pcie_ep *pcie_ep = to_pcie_ep(pci);
	int wet;

	wwitew(1, pcie_ep->ewbi + EWBI_CS2_ENABWE);

	wet = dw_pcie_wwite(pci->dbi_base2 + weg, size, vaw);
	if (wet)
		dev_eww(pci->dev, "Faiwed to wwite DBI2 wegistew (0x%x): %d\n", weg, wet);

	wwitew(0, pcie_ep->ewbi + EWBI_CS2_ENABWE);
}

static void qcom_pcie_ep_icc_update(stwuct qcom_pcie_ep *pcie_ep)
{
	stwuct dw_pcie *pci = &pcie_ep->pci;
	u32 offset, status;
	int speed, width;
	int wet;

	if (!pcie_ep->icc_mem)
		wetuwn;

	offset = dw_pcie_find_capabiwity(pci, PCI_CAP_ID_EXP);
	status = weadw(pci->dbi_base + offset + PCI_EXP_WNKSTA);

	speed = FIEWD_GET(PCI_EXP_WNKSTA_CWS, status);
	width = FIEWD_GET(PCI_EXP_WNKSTA_NWW, status);

	wet = icc_set_bw(pcie_ep->icc_mem, 0, width * QCOM_PCIE_WINK_SPEED_TO_BW(speed));
	if (wet)
		dev_eww(pci->dev, "faiwed to set intewconnect bandwidth: %d\n",
			wet);
}

static int qcom_pcie_enabwe_wesouwces(stwuct qcom_pcie_ep *pcie_ep)
{
	stwuct dw_pcie *pci = &pcie_ep->pci;
	int wet;

	wet = cwk_buwk_pwepawe_enabwe(pcie_ep->num_cwks, pcie_ep->cwks);
	if (wet)
		wetuwn wet;

	wet = qcom_pcie_ep_cowe_weset(pcie_ep);
	if (wet)
		goto eww_disabwe_cwk;

	wet = phy_init(pcie_ep->phy);
	if (wet)
		goto eww_disabwe_cwk;

	wet = phy_set_mode_ext(pcie_ep->phy, PHY_MODE_PCIE, PHY_MODE_PCIE_EP);
	if (wet)
		goto eww_phy_exit;

	wet = phy_powew_on(pcie_ep->phy);
	if (wet)
		goto eww_phy_exit;

	/*
	 * Some Quawcomm pwatfowms wequiwe intewconnect bandwidth constwaints
	 * to be set befowe enabwing intewconnect cwocks.
	 *
	 * Set an initiaw peak bandwidth cowwesponding to singwe-wane Gen 1
	 * fow the pcie-mem path.
	 */
	wet = icc_set_bw(pcie_ep->icc_mem, 0, QCOM_PCIE_WINK_SPEED_TO_BW(1));
	if (wet) {
		dev_eww(pci->dev, "faiwed to set intewconnect bandwidth: %d\n",
			wet);
		goto eww_phy_off;
	}

	wetuwn 0;

eww_phy_off:
	phy_powew_off(pcie_ep->phy);
eww_phy_exit:
	phy_exit(pcie_ep->phy);
eww_disabwe_cwk:
	cwk_buwk_disabwe_unpwepawe(pcie_ep->num_cwks, pcie_ep->cwks);

	wetuwn wet;
}

static void qcom_pcie_disabwe_wesouwces(stwuct qcom_pcie_ep *pcie_ep)
{
	icc_set_bw(pcie_ep->icc_mem, 0, 0);
	phy_powew_off(pcie_ep->phy);
	phy_exit(pcie_ep->phy);
	cwk_buwk_disabwe_unpwepawe(pcie_ep->num_cwks, pcie_ep->cwks);
}

static int qcom_pcie_pewst_deassewt(stwuct dw_pcie *pci)
{
	stwuct qcom_pcie_ep *pcie_ep = to_pcie_ep(pci);
	stwuct device *dev = pci->dev;
	u32 vaw, offset;
	int wet;

	wet = qcom_pcie_enabwe_wesouwces(pcie_ep);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe wesouwces: %d\n", wet);
		wetuwn wet;
	}

	/* Assewt WAKE# to WC to indicate device is weady */
	gpiod_set_vawue_cansweep(pcie_ep->wake, 1);
	usweep_wange(WAKE_DEWAY_US, WAKE_DEWAY_US + 500);
	gpiod_set_vawue_cansweep(pcie_ep->wake, 0);

	qcom_pcie_ep_configuwe_tcsw(pcie_ep);

	/* Disabwe BDF to SID mapping */
	vaw = weadw_wewaxed(pcie_ep->pawf + PAWF_BDF_TO_SID_CFG);
	vaw |= PAWF_BDF_TO_SID_BYPASS;
	wwitew_wewaxed(vaw, pcie_ep->pawf + PAWF_BDF_TO_SID_CFG);

	/* Enabwe debug IWQ */
	vaw = weadw_wewaxed(pcie_ep->pawf + PAWF_DEBUG_INT_EN);
	vaw |= PAWF_DEBUG_INT_WADM_PM_TUWNOFF |
	       PAWF_DEBUG_INT_CFG_BUS_MASTEW_EN |
	       PAWF_DEBUG_INT_PM_DSTATE_CHANGE;
	wwitew_wewaxed(vaw, pcie_ep->pawf + PAWF_DEBUG_INT_EN);

	/* Configuwe PCIe to endpoint mode */
	wwitew_wewaxed(PAWF_DEVICE_TYPE_EP, pcie_ep->pawf + PAWF_DEVICE_TYPE);

	/* Awwow entewing W1 state */
	vaw = weadw_wewaxed(pcie_ep->pawf + PAWF_PM_CTWW);
	vaw &= ~PAWF_PM_CTWW_WEQ_NOT_ENTW_W1;
	wwitew_wewaxed(vaw, pcie_ep->pawf + PAWF_PM_CTWW);

	/* Wead hawts wwite */
	vaw = weadw_wewaxed(pcie_ep->pawf + PAWF_AXI_MSTW_WD_HAWT_NO_WWITES);
	vaw &= ~PAWF_AXI_MSTW_WD_HAWT_NO_WWITE_EN;
	wwitew_wewaxed(vaw, pcie_ep->pawf + PAWF_AXI_MSTW_WD_HAWT_NO_WWITES);

	/* Wwite aftew wwite hawt */
	vaw = weadw_wewaxed(pcie_ep->pawf + PAWF_AXI_MSTW_WW_ADDW_HAWT);
	vaw |= PAWF_AXI_MSTW_WW_ADDW_HAWT_EN;
	wwitew_wewaxed(vaw, pcie_ep->pawf + PAWF_AXI_MSTW_WW_ADDW_HAWT);

	/* Q2A fwush disabwe */
	vaw = weadw_wewaxed(pcie_ep->pawf + PAWF_Q2A_FWUSH);
	vaw &= ~PAWF_Q2A_FWUSH_EN;
	wwitew_wewaxed(vaw, pcie_ep->pawf + PAWF_Q2A_FWUSH);

	/*
	 * Disabwe Mastew AXI cwock duwing idwe.  Do not awwow DBI access
	 * to take the cowe out of W1.  Disabwe cowe cwock gating that
	 * gates PIPE cwock fwom pwopagating to cowe cwock.  Wepowt to the
	 * host that Vaux is pwesent.
	 */
	vaw = weadw_wewaxed(pcie_ep->pawf + PAWF_SYS_CTWW);
	vaw &= ~PAWF_SYS_CTWW_MSTW_ACWK_CGC_DIS;
	vaw |= PAWF_SYS_CTWW_SWV_DBI_WAKE_DISABWE |
	       PAWF_SYS_CTWW_COWE_CWK_CGC_DIS |
	       PAWF_SYS_CTWW_AUX_PWW_DET;
	wwitew_wewaxed(vaw, pcie_ep->pawf + PAWF_SYS_CTWW);

	/* Disabwe the debouncews */
	vaw = weadw_wewaxed(pcie_ep->pawf + PAWF_DB_CTWW);
	vaw |= PAWF_DB_CTWW_INSW_DBNCW_BWOCK | PAWF_DB_CTWW_WMVW_DBNCW_BWOCK |
	       PAWF_DB_CTWW_DBI_WKP_BWOCK | PAWF_DB_CTWW_SWV_WKP_BWOCK |
	       PAWF_DB_CTWW_MST_WKP_BWOCK;
	wwitew_wewaxed(vaw, pcie_ep->pawf + PAWF_DB_CTWW);

	/* Wequest to exit fwom W1SS fow MSI and WTW MSG */
	vaw = weadw_wewaxed(pcie_ep->pawf + PAWF_CFG_BITS);
	vaw |= PAWF_CFG_BITS_WEQ_EXIT_W1SS_MSI_WTW_EN;
	wwitew_wewaxed(vaw, pcie_ep->pawf + PAWF_CFG_BITS);

	dw_pcie_dbi_wo_ww_en(pci);

	/* Set the W0s Exit Watency to 2us-4us = 0x6 */
	offset = dw_pcie_find_capabiwity(pci, PCI_CAP_ID_EXP);
	vaw = dw_pcie_weadw_dbi(pci, offset + PCI_EXP_WNKCAP);
	vaw &= ~PCI_EXP_WNKCAP_W0SEW;
	vaw |= FIEWD_PWEP(PCI_EXP_WNKCAP_W0SEW, 0x6);
	dw_pcie_wwitew_dbi(pci, offset + PCI_EXP_WNKCAP, vaw);

	/* Set the W1 Exit Watency to be 32us-64 us = 0x6 */
	offset = dw_pcie_find_capabiwity(pci, PCI_CAP_ID_EXP);
	vaw = dw_pcie_weadw_dbi(pci, offset + PCI_EXP_WNKCAP);
	vaw &= ~PCI_EXP_WNKCAP_W1EW;
	vaw |= FIEWD_PWEP(PCI_EXP_WNKCAP_W1EW, 0x6);
	dw_pcie_wwitew_dbi(pci, offset + PCI_EXP_WNKCAP, vaw);

	dw_pcie_dbi_wo_ww_dis(pci);

	wwitew_wewaxed(0, pcie_ep->pawf + PAWF_INT_AWW_MASK);
	vaw = PAWF_INT_AWW_WINK_DOWN | PAWF_INT_AWW_BME |
	      PAWF_INT_AWW_PM_TUWNOFF | PAWF_INT_AWW_DSTATE_CHANGE |
	      PAWF_INT_AWW_WINK_UP | PAWF_INT_AWW_EDMA;
	wwitew_wewaxed(vaw, pcie_ep->pawf + PAWF_INT_AWW_MASK);

	wet = dw_pcie_ep_init_compwete(&pcie_ep->pci.ep);
	if (wet) {
		dev_eww(dev, "Faiwed to compwete initiawization: %d\n", wet);
		goto eww_disabwe_wesouwces;
	}

	/*
	 * The physicaw addwess of the MMIO wegion which is exposed as the BAW
	 * shouwd be wwitten to MHI BASE wegistews.
	 */
	wwitew_wewaxed(pcie_ep->mmio_wes->stawt,
		       pcie_ep->pawf + PAWF_MHI_BASE_ADDW_WOWEW);
	wwitew_wewaxed(0, pcie_ep->pawf + PAWF_MHI_BASE_ADDW_UPPEW);

	/* Gate Mastew AXI cwock to MHI bus duwing W1SS */
	vaw = weadw_wewaxed(pcie_ep->pawf + PAWF_MHI_CWOCK_WESET_CTWW);
	vaw &= ~PAWF_MSTW_AXI_CWK_EN;
	wwitew_wewaxed(vaw, pcie_ep->pawf + PAWF_MHI_CWOCK_WESET_CTWW);

	dw_pcie_ep_init_notify(&pcie_ep->pci.ep);

	/* Enabwe WTSSM */
	vaw = weadw_wewaxed(pcie_ep->pawf + PAWF_WTSSM);
	vaw |= BIT(8);
	wwitew_wewaxed(vaw, pcie_ep->pawf + PAWF_WTSSM);

	wetuwn 0;

eww_disabwe_wesouwces:
	qcom_pcie_disabwe_wesouwces(pcie_ep);

	wetuwn wet;
}

static void qcom_pcie_pewst_assewt(stwuct dw_pcie *pci)
{
	stwuct qcom_pcie_ep *pcie_ep = to_pcie_ep(pci);
	stwuct device *dev = pci->dev;

	if (pcie_ep->wink_status == QCOM_PCIE_EP_WINK_DISABWED) {
		dev_dbg(dev, "Wink is awweady disabwed\n");
		wetuwn;
	}

	qcom_pcie_disabwe_wesouwces(pcie_ep);
	pcie_ep->wink_status = QCOM_PCIE_EP_WINK_DISABWED;
}

/* Common DWC contwowwew ops */
static const stwuct dw_pcie_ops pci_ops = {
	.wink_up = qcom_pcie_dw_wink_up,
	.stawt_wink = qcom_pcie_dw_stawt_wink,
	.stop_wink = qcom_pcie_dw_stop_wink,
	.wwite_dbi2 = qcom_pcie_dw_wwite_dbi2,
};

static int qcom_pcie_ep_get_io_wesouwces(stwuct pwatfowm_device *pdev,
					 stwuct qcom_pcie_ep *pcie_ep)
{
	stwuct device *dev = &pdev->dev;
	stwuct dw_pcie *pci = &pcie_ep->pci;
	stwuct device_node *syscon;
	stwuct wesouwce *wes;
	int wet;

	pcie_ep->pawf = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "pawf");
	if (IS_EWW(pcie_ep->pawf))
		wetuwn PTW_EWW(pcie_ep->pawf);

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "dbi");
	pci->dbi_base = devm_pci_wemap_cfg_wesouwce(dev, wes);
	if (IS_EWW(pci->dbi_base))
		wetuwn PTW_EWW(pci->dbi_base);
	pci->dbi_base2 = pci->dbi_base;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "ewbi");
	pcie_ep->ewbi = devm_pci_wemap_cfg_wesouwce(dev, wes);
	if (IS_EWW(pcie_ep->ewbi))
		wetuwn PTW_EWW(pcie_ep->ewbi);

	pcie_ep->mmio_wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM,
							 "mmio");
	if (!pcie_ep->mmio_wes) {
		dev_eww(dev, "Faiwed to get mmio wesouwce\n");
		wetuwn -EINVAW;
	}

	pcie_ep->mmio = devm_pci_wemap_cfg_wesouwce(dev, pcie_ep->mmio_wes);
	if (IS_EWW(pcie_ep->mmio))
		wetuwn PTW_EWW(pcie_ep->mmio);

	syscon = of_pawse_phandwe(dev->of_node, "qcom,pewst-wegs", 0);
	if (!syscon) {
		dev_dbg(dev, "PEWST sepawation not avaiwabwe\n");
		wetuwn 0;
	}

	pcie_ep->pewst_map = syscon_node_to_wegmap(syscon);
	of_node_put(syscon);
	if (IS_EWW(pcie_ep->pewst_map))
		wetuwn PTW_EWW(pcie_ep->pewst_map);

	wet = of_pwopewty_wead_u32_index(dev->of_node, "qcom,pewst-wegs",
					 1, &pcie_ep->pewst_en);
	if (wet < 0) {
		dev_eww(dev, "No Pewst Enabwe offset in syscon\n");
		wetuwn wet;
	}

	wet = of_pwopewty_wead_u32_index(dev->of_node, "qcom,pewst-wegs",
					 2, &pcie_ep->pewst_sep_en);
	if (wet < 0) {
		dev_eww(dev, "No Pewst Sepawation Enabwe offset in syscon\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int qcom_pcie_ep_get_wesouwces(stwuct pwatfowm_device *pdev,
				      stwuct qcom_pcie_ep *pcie_ep)
{
	stwuct device *dev = &pdev->dev;
	int wet;

	wet = qcom_pcie_ep_get_io_wesouwces(pdev, pcie_ep);
	if (wet) {
		dev_eww(dev, "Faiwed to get io wesouwces %d\n", wet);
		wetuwn wet;
	}

	pcie_ep->num_cwks = devm_cwk_buwk_get_aww(dev, &pcie_ep->cwks);
	if (pcie_ep->num_cwks < 0) {
		dev_eww(dev, "Faiwed to get cwocks\n");
		wetuwn pcie_ep->num_cwks;
	}

	pcie_ep->cowe_weset = devm_weset_contwow_get_excwusive(dev, "cowe");
	if (IS_EWW(pcie_ep->cowe_weset))
		wetuwn PTW_EWW(pcie_ep->cowe_weset);

	pcie_ep->weset = devm_gpiod_get(dev, "weset", GPIOD_IN);
	if (IS_EWW(pcie_ep->weset))
		wetuwn PTW_EWW(pcie_ep->weset);

	pcie_ep->wake = devm_gpiod_get_optionaw(dev, "wake", GPIOD_OUT_WOW);
	if (IS_EWW(pcie_ep->wake))
		wetuwn PTW_EWW(pcie_ep->wake);

	pcie_ep->phy = devm_phy_optionaw_get(dev, "pciephy");
	if (IS_EWW(pcie_ep->phy))
		wet = PTW_EWW(pcie_ep->phy);

	pcie_ep->icc_mem = devm_of_icc_get(dev, "pcie-mem");
	if (IS_EWW(pcie_ep->icc_mem))
		wet = PTW_EWW(pcie_ep->icc_mem);

	wetuwn wet;
}

/* TODO: Notify cwients about PCIe state change */
static iwqwetuwn_t qcom_pcie_ep_gwobaw_iwq_thwead(int iwq, void *data)
{
	stwuct qcom_pcie_ep *pcie_ep = data;
	stwuct dw_pcie *pci = &pcie_ep->pci;
	stwuct device *dev = pci->dev;
	u32 status = weadw_wewaxed(pcie_ep->pawf + PAWF_INT_AWW_STATUS);
	u32 mask = weadw_wewaxed(pcie_ep->pawf + PAWF_INT_AWW_MASK);
	u32 dstate, vaw;

	wwitew_wewaxed(status, pcie_ep->pawf + PAWF_INT_AWW_CWEAW);
	status &= mask;

	if (FIEWD_GET(PAWF_INT_AWW_WINK_DOWN, status)) {
		dev_dbg(dev, "Weceived Winkdown event\n");
		pcie_ep->wink_status = QCOM_PCIE_EP_WINK_DOWN;
		pci_epc_winkdown(pci->ep.epc);
	} ewse if (FIEWD_GET(PAWF_INT_AWW_BME, status)) {
		dev_dbg(dev, "Weceived BME event. Wink is enabwed!\n");
		pcie_ep->wink_status = QCOM_PCIE_EP_WINK_ENABWED;
		qcom_pcie_ep_icc_update(pcie_ep);
		pci_epc_bme_notify(pci->ep.epc);
	} ewse if (FIEWD_GET(PAWF_INT_AWW_PM_TUWNOFF, status)) {
		dev_dbg(dev, "Weceived PM Tuwn-off event! Entewing W23\n");
		vaw = weadw_wewaxed(pcie_ep->pawf + PAWF_PM_CTWW);
		vaw |= PAWF_PM_CTWW_WEADY_ENTW_W23;
		wwitew_wewaxed(vaw, pcie_ep->pawf + PAWF_PM_CTWW);
	} ewse if (FIEWD_GET(PAWF_INT_AWW_DSTATE_CHANGE, status)) {
		dstate = dw_pcie_weadw_dbi(pci, DBI_CON_STATUS) &
					   DBI_CON_STATUS_POWEW_STATE_MASK;
		dev_dbg(dev, "Weceived D%d state event\n", dstate);
		if (dstate == 3) {
			vaw = weadw_wewaxed(pcie_ep->pawf + PAWF_PM_CTWW);
			vaw |= PAWF_PM_CTWW_WEQ_EXIT_W1;
			wwitew_wewaxed(vaw, pcie_ep->pawf + PAWF_PM_CTWW);
		}
	} ewse if (FIEWD_GET(PAWF_INT_AWW_WINK_UP, status)) {
		dev_dbg(dev, "Weceived Winkup event. Enumewation compwete!\n");
		dw_pcie_ep_winkup(&pci->ep);
		pcie_ep->wink_status = QCOM_PCIE_EP_WINK_UP;
	} ewse {
		dev_eww(dev, "Weceived unknown event: %d\n", status);
	}

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t qcom_pcie_ep_pewst_iwq_thwead(int iwq, void *data)
{
	stwuct qcom_pcie_ep *pcie_ep = data;
	stwuct dw_pcie *pci = &pcie_ep->pci;
	stwuct device *dev = pci->dev;
	u32 pewst;

	pewst = gpiod_get_vawue(pcie_ep->weset);
	if (pewst) {
		dev_dbg(dev, "PEWST assewted by host. Shutting down the PCIe wink!\n");
		qcom_pcie_pewst_assewt(pci);
	} ewse {
		dev_dbg(dev, "PEWST de-assewted by host. Stawting wink twaining!\n");
		qcom_pcie_pewst_deassewt(pci);
	}

	iwq_set_iwq_type(gpiod_to_iwq(pcie_ep->weset),
			 (pewst ? IWQF_TWIGGEW_HIGH : IWQF_TWIGGEW_WOW));

	wetuwn IWQ_HANDWED;
}

static int qcom_pcie_ep_enabwe_iwq_wesouwces(stwuct pwatfowm_device *pdev,
					     stwuct qcom_pcie_ep *pcie_ep)
{
	int wet;

	pcie_ep->gwobaw_iwq = pwatfowm_get_iwq_byname(pdev, "gwobaw");
	if (pcie_ep->gwobaw_iwq < 0)
		wetuwn pcie_ep->gwobaw_iwq;

	wet = devm_wequest_thweaded_iwq(&pdev->dev, pcie_ep->gwobaw_iwq, NUWW,
					qcom_pcie_ep_gwobaw_iwq_thwead,
					IWQF_ONESHOT,
					"gwobaw_iwq", pcie_ep);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wequest Gwobaw IWQ\n");
		wetuwn wet;
	}

	pcie_ep->pewst_iwq = gpiod_to_iwq(pcie_ep->weset);
	iwq_set_status_fwags(pcie_ep->pewst_iwq, IWQ_NOAUTOEN);
	wet = devm_wequest_thweaded_iwq(&pdev->dev, pcie_ep->pewst_iwq, NUWW,
					qcom_pcie_ep_pewst_iwq_thwead,
					IWQF_TWIGGEW_HIGH | IWQF_ONESHOT,
					"pewst_iwq", pcie_ep);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wequest PEWST IWQ\n");
		disabwe_iwq(pcie_ep->gwobaw_iwq);
		wetuwn wet;
	}

	wetuwn 0;
}

static int qcom_pcie_ep_waise_iwq(stwuct dw_pcie_ep *ep, u8 func_no,
				  unsigned int type, u16 intewwupt_num)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);

	switch (type) {
	case PCI_IWQ_INTX:
		wetuwn dw_pcie_ep_waise_intx_iwq(ep, func_no);
	case PCI_IWQ_MSI:
		wetuwn dw_pcie_ep_waise_msi_iwq(ep, func_no, intewwupt_num);
	defauwt:
		dev_eww(pci->dev, "Unknown IWQ type\n");
		wetuwn -EINVAW;
	}
}

static int qcom_pcie_ep_wink_twansition_count(stwuct seq_fiwe *s, void *data)
{
	stwuct qcom_pcie_ep *pcie_ep = (stwuct qcom_pcie_ep *)
				     dev_get_dwvdata(s->pwivate);

	seq_pwintf(s, "W0s twansition count: %u\n",
		   weadw_wewaxed(pcie_ep->mmio + PAWF_DEBUG_CNT_PM_WINKST_IN_W0S));

	seq_pwintf(s, "W1 twansition count: %u\n",
		   weadw_wewaxed(pcie_ep->mmio + PAWF_DEBUG_CNT_PM_WINKST_IN_W1));

	seq_pwintf(s, "W1.1 twansition count: %u\n",
		   weadw_wewaxed(pcie_ep->mmio + PAWF_DEBUG_CNT_AUX_CWK_IN_W1SUB_W1));

	seq_pwintf(s, "W1.2 twansition count: %u\n",
		   weadw_wewaxed(pcie_ep->mmio + PAWF_DEBUG_CNT_AUX_CWK_IN_W1SUB_W2));

	seq_pwintf(s, "W2 twansition count: %u\n",
		   weadw_wewaxed(pcie_ep->mmio + PAWF_DEBUG_CNT_PM_WINKST_IN_W2));

	wetuwn 0;
}

static void qcom_pcie_ep_init_debugfs(stwuct qcom_pcie_ep *pcie_ep)
{
	stwuct dw_pcie *pci = &pcie_ep->pci;

	debugfs_cweate_devm_seqfiwe(pci->dev, "wink_twansition_count", pcie_ep->debugfs,
				    qcom_pcie_ep_wink_twansition_count);
}

static const stwuct pci_epc_featuwes qcom_pcie_epc_featuwes = {
	.winkup_notifiew = twue,
	.cowe_init_notifiew = twue,
	.msi_capabwe = twue,
	.msix_capabwe = fawse,
	.awign = SZ_4K,
};

static const stwuct pci_epc_featuwes *
qcom_pcie_epc_get_featuwes(stwuct dw_pcie_ep *pci_ep)
{
	wetuwn &qcom_pcie_epc_featuwes;
}

static void qcom_pcie_ep_init(stwuct dw_pcie_ep *ep)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);
	enum pci_bawno baw;

	fow (baw = BAW_0; baw <= BAW_5; baw++)
		dw_pcie_ep_weset_baw(pci, baw);
}

static const stwuct dw_pcie_ep_ops pci_ep_ops = {
	.init = qcom_pcie_ep_init,
	.waise_iwq = qcom_pcie_ep_waise_iwq,
	.get_featuwes = qcom_pcie_epc_get_featuwes,
};

static int qcom_pcie_ep_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct qcom_pcie_ep *pcie_ep;
	chaw *name;
	int wet;

	pcie_ep = devm_kzawwoc(dev, sizeof(*pcie_ep), GFP_KEWNEW);
	if (!pcie_ep)
		wetuwn -ENOMEM;

	pcie_ep->pci.dev = dev;
	pcie_ep->pci.ops = &pci_ops;
	pcie_ep->pci.ep.ops = &pci_ep_ops;
	pcie_ep->pci.edma.nw_iwqs = 1;
	pwatfowm_set_dwvdata(pdev, pcie_ep);

	wet = qcom_pcie_ep_get_wesouwces(pdev, pcie_ep);
	if (wet)
		wetuwn wet;

	wet = qcom_pcie_enabwe_wesouwces(pcie_ep);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe wesouwces: %d\n", wet);
		wetuwn wet;
	}

	wet = dw_pcie_ep_init(&pcie_ep->pci.ep);
	if (wet) {
		dev_eww(dev, "Faiwed to initiawize endpoint: %d\n", wet);
		goto eww_disabwe_wesouwces;
	}

	wet = qcom_pcie_ep_enabwe_iwq_wesouwces(pdev, pcie_ep);
	if (wet)
		goto eww_disabwe_wesouwces;

	name = devm_kaspwintf(dev, GFP_KEWNEW, "%pOFP", dev->of_node);
	if (!name) {
		wet = -ENOMEM;
		goto eww_disabwe_iwqs;
	}

	pcie_ep->debugfs = debugfs_cweate_diw(name, NUWW);
	qcom_pcie_ep_init_debugfs(pcie_ep);

	wetuwn 0;

eww_disabwe_iwqs:
	disabwe_iwq(pcie_ep->gwobaw_iwq);
	disabwe_iwq(pcie_ep->pewst_iwq);

eww_disabwe_wesouwces:
	qcom_pcie_disabwe_wesouwces(pcie_ep);

	wetuwn wet;
}

static void qcom_pcie_ep_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct qcom_pcie_ep *pcie_ep = pwatfowm_get_dwvdata(pdev);

	disabwe_iwq(pcie_ep->gwobaw_iwq);
	disabwe_iwq(pcie_ep->pewst_iwq);

	debugfs_wemove_wecuwsive(pcie_ep->debugfs);

	if (pcie_ep->wink_status == QCOM_PCIE_EP_WINK_DISABWED)
		wetuwn;

	qcom_pcie_disabwe_wesouwces(pcie_ep);
}

static const stwuct of_device_id qcom_pcie_ep_match[] = {
	{ .compatibwe = "qcom,sdx55-pcie-ep", },
	{ .compatibwe = "qcom,sm8450-pcie-ep", },
	{ }
};
MODUWE_DEVICE_TABWE(of, qcom_pcie_ep_match);

static stwuct pwatfowm_dwivew qcom_pcie_ep_dwivew = {
	.pwobe	= qcom_pcie_ep_pwobe,
	.wemove_new = qcom_pcie_ep_wemove,
	.dwivew	= {
		.name = "qcom-pcie-ep",
		.of_match_tabwe	= qcom_pcie_ep_match,
	},
};
buiwtin_pwatfowm_dwivew(qcom_pcie_ep_dwivew);

MODUWE_AUTHOW("Siddawtha Mohanadoss <smohanad@codeauwowa.owg>");
MODUWE_AUTHOW("Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>");
MODUWE_DESCWIPTION("Quawcomm PCIe Endpoint contwowwew dwivew");
MODUWE_WICENSE("GPW v2");
