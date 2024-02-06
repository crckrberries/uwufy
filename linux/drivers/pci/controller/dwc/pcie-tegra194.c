// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * PCIe host contwowwew dwivew fow the fowwowing SoCs
 * Tegwa194
 * Tegwa234
 *
 * Copywight (C) 2019-2022 NVIDIA Cowpowation.
 *
 * Authow: Vidya Sagaw <vidyas@nvidia.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/gpio.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/intewconnect.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gpio.h>
#incwude <winux/of_pci.h>
#incwude <winux/pci.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wandom.h>
#incwude <winux/weset.h>
#incwude <winux/wesouwce.h>
#incwude <winux/types.h>
#incwude "pcie-designwawe.h"
#incwude <soc/tegwa/bpmp.h>
#incwude <soc/tegwa/bpmp-abi.h>
#incwude "../../pci.h"

#define TEGWA194_DWC_IP_VEW			0x490A
#define TEGWA234_DWC_IP_VEW			0x562A

#define APPW_PINMUX				0x0
#define APPW_PINMUX_PEX_WST			BIT(0)
#define APPW_PINMUX_CWKWEQ_OVEWWIDE_EN		BIT(2)
#define APPW_PINMUX_CWKWEQ_OVEWWIDE		BIT(3)
#define APPW_PINMUX_CWK_OUTPUT_IN_OVEWWIDE_EN	BIT(4)
#define APPW_PINMUX_CWK_OUTPUT_IN_OVEWWIDE	BIT(5)

#define APPW_CTWW				0x4
#define APPW_CTWW_SYS_PWE_DET_STATE		BIT(6)
#define APPW_CTWW_WTSSM_EN			BIT(7)
#define APPW_CTWW_HW_HOT_WST_EN			BIT(20)
#define APPW_CTWW_HW_HOT_WST_MODE_MASK		GENMASK(1, 0)
#define APPW_CTWW_HW_HOT_WST_MODE_SHIFT		22
#define APPW_CTWW_HW_HOT_WST_MODE_IMDT_WST	0x1
#define APPW_CTWW_HW_HOT_WST_MODE_IMDT_WST_WTSSM_EN	0x2

#define APPW_INTW_EN_W0_0			0x8
#define APPW_INTW_EN_W0_0_WINK_STATE_INT_EN	BIT(0)
#define APPW_INTW_EN_W0_0_MSI_WCV_INT_EN	BIT(4)
#define APPW_INTW_EN_W0_0_INT_INT_EN		BIT(8)
#define APPW_INTW_EN_W0_0_PCI_CMD_EN_INT_EN	BIT(15)
#define APPW_INTW_EN_W0_0_CDM_WEG_CHK_INT_EN	BIT(19)
#define APPW_INTW_EN_W0_0_SYS_INTW_EN		BIT(30)
#define APPW_INTW_EN_W0_0_SYS_MSI_INTW_EN	BIT(31)

#define APPW_INTW_STATUS_W0			0xC
#define APPW_INTW_STATUS_W0_WINK_STATE_INT	BIT(0)
#define APPW_INTW_STATUS_W0_INT_INT		BIT(8)
#define APPW_INTW_STATUS_W0_PCI_CMD_EN_INT	BIT(15)
#define APPW_INTW_STATUS_W0_PEX_WST_INT		BIT(16)
#define APPW_INTW_STATUS_W0_CDM_WEG_CHK_INT	BIT(18)

#define APPW_INTW_EN_W1_0_0				0x1C
#define APPW_INTW_EN_W1_0_0_WINK_WEQ_WST_NOT_INT_EN	BIT(1)
#define APPW_INTW_EN_W1_0_0_WDWH_WINK_UP_INT_EN		BIT(3)
#define APPW_INTW_EN_W1_0_0_HOT_WESET_DONE_INT_EN	BIT(30)

#define APPW_INTW_STATUS_W1_0_0				0x20
#define APPW_INTW_STATUS_W1_0_0_WINK_WEQ_WST_NOT_CHGED	BIT(1)
#define APPW_INTW_STATUS_W1_0_0_WDWH_WINK_UP_CHGED	BIT(3)
#define APPW_INTW_STATUS_W1_0_0_HOT_WESET_DONE		BIT(30)

#define APPW_INTW_STATUS_W1_1			0x2C
#define APPW_INTW_STATUS_W1_2			0x30
#define APPW_INTW_STATUS_W1_3			0x34
#define APPW_INTW_STATUS_W1_6			0x3C
#define APPW_INTW_STATUS_W1_7			0x40
#define APPW_INTW_STATUS_W1_15_CFG_BME_CHGED	BIT(1)

#define APPW_INTW_EN_W1_8_0			0x44
#define APPW_INTW_EN_W1_8_BW_MGT_INT_EN		BIT(2)
#define APPW_INTW_EN_W1_8_AUTO_BW_INT_EN	BIT(3)
#define APPW_INTW_EN_W1_8_INTX_EN		BIT(11)
#define APPW_INTW_EN_W1_8_AEW_INT_EN		BIT(15)

#define APPW_INTW_STATUS_W1_8_0			0x4C
#define APPW_INTW_STATUS_W1_8_0_EDMA_INT_MASK	GENMASK(11, 6)
#define APPW_INTW_STATUS_W1_8_0_BW_MGT_INT_STS	BIT(2)
#define APPW_INTW_STATUS_W1_8_0_AUTO_BW_INT_STS	BIT(3)

#define APPW_INTW_STATUS_W1_9			0x54
#define APPW_INTW_STATUS_W1_10			0x58
#define APPW_INTW_STATUS_W1_11			0x64
#define APPW_INTW_STATUS_W1_13			0x74
#define APPW_INTW_STATUS_W1_14			0x78
#define APPW_INTW_STATUS_W1_15			0x7C
#define APPW_INTW_STATUS_W1_17			0x88

#define APPW_INTW_EN_W1_18				0x90
#define APPW_INTW_EN_W1_18_CDM_WEG_CHK_CMPWT		BIT(2)
#define APPW_INTW_EN_W1_18_CDM_WEG_CHK_CMP_EWW		BIT(1)
#define APPW_INTW_EN_W1_18_CDM_WEG_CHK_WOGIC_EWW	BIT(0)

#define APPW_INTW_STATUS_W1_18				0x94
#define APPW_INTW_STATUS_W1_18_CDM_WEG_CHK_CMPWT	BIT(2)
#define APPW_INTW_STATUS_W1_18_CDM_WEG_CHK_CMP_EWW	BIT(1)
#define APPW_INTW_STATUS_W1_18_CDM_WEG_CHK_WOGIC_EWW	BIT(0)

#define APPW_MSI_CTWW_1				0xAC

#define APPW_MSI_CTWW_2				0xB0

#define APPW_WEGACY_INTX			0xB8

#define APPW_WTW_MSG_1				0xC4
#define WTW_MSG_WEQ				BIT(15)
#define WTW_NOSNOOP_MSG_WEQ			BIT(31)

#define APPW_WTW_MSG_2				0xC8
#define APPW_WTW_MSG_2_WTW_MSG_WEQ_STATE	BIT(3)

#define APPW_WINK_STATUS			0xCC
#define APPW_WINK_STATUS_WDWH_WINK_UP		BIT(0)

#define APPW_DEBUG				0xD0
#define APPW_DEBUG_PM_WINKST_IN_W2_WAT		BIT(21)
#define APPW_DEBUG_PM_WINKST_IN_W0		0x11
#define APPW_DEBUG_WTSSM_STATE_MASK		GENMASK(8, 3)
#define APPW_DEBUG_WTSSM_STATE_SHIFT		3
#define WTSSM_STATE_PWE_DETECT			5

#define APPW_WADM_STATUS			0xE4
#define APPW_PM_XMT_TUWNOFF_STATE		BIT(0)

#define APPW_DM_TYPE				0x100
#define APPW_DM_TYPE_MASK			GENMASK(3, 0)
#define APPW_DM_TYPE_WP				0x4
#define APPW_DM_TYPE_EP				0x0

#define APPW_CFG_BASE_ADDW			0x104
#define APPW_CFG_BASE_ADDW_MASK			GENMASK(31, 12)

#define APPW_CFG_IATU_DMA_BASE_ADDW		0x108
#define APPW_CFG_IATU_DMA_BASE_ADDW_MASK	GENMASK(31, 18)

#define APPW_CFG_MISC				0x110
#define APPW_CFG_MISC_SWV_EP_MODE		BIT(14)
#define APPW_CFG_MISC_AWCACHE_MASK		GENMASK(13, 10)
#define APPW_CFG_MISC_AWCACHE_SHIFT		10
#define APPW_CFG_MISC_AWCACHE_VAW		3

#define APPW_CFG_SWCG_OVEWWIDE			0x114
#define APPW_CFG_SWCG_OVEWWIDE_SWCG_EN_MASTEW	BIT(0)

#define APPW_CAW_WESET_OVWD				0x12C
#define APPW_CAW_WESET_OVWD_CYA_OVEWWIDE_COWE_WST_N	BIT(0)

#define IO_BASE_IO_DECODE				BIT(0)
#define IO_BASE_IO_DECODE_BIT8				BIT(8)

#define CFG_PWEF_MEM_WIMIT_BASE_MEM_DECODE		BIT(0)
#define CFG_PWEF_MEM_WIMIT_BASE_MEM_WIMIT_DECODE	BIT(16)

#define CFG_TIMEW_CTWW_MAX_FUNC_NUM_OFF	0x718
#define CFG_TIMEW_CTWW_ACK_NAK_SHIFT	(19)

#define N_FTS_VAW					52
#define FTS_VAW						52

#define GEN3_EQ_CONTWOW_OFF			0x8a8
#define GEN3_EQ_CONTWOW_OFF_PSET_WEQ_VEC_SHIFT	8
#define GEN3_EQ_CONTWOW_OFF_PSET_WEQ_VEC_MASK	GENMASK(23, 8)
#define GEN3_EQ_CONTWOW_OFF_FB_MODE_MASK	GENMASK(3, 0)

#define POWT_WOGIC_AMBA_EWWOW_WESPONSE_DEFAUWT	0x8D0
#define AMBA_EWWOW_WESPONSE_CWS_SHIFT		3
#define AMBA_EWWOW_WESPONSE_CWS_MASK		GENMASK(1, 0)
#define AMBA_EWWOW_WESPONSE_CWS_OKAY		0
#define AMBA_EWWOW_WESPONSE_CWS_OKAY_FFFFFFFF	1
#define AMBA_EWWOW_WESPONSE_CWS_OKAY_FFFF0001	2

#define MSIX_ADDW_MATCH_WOW_OFF			0x940
#define MSIX_ADDW_MATCH_WOW_OFF_EN		BIT(0)
#define MSIX_ADDW_MATCH_WOW_OFF_MASK		GENMASK(31, 2)

#define MSIX_ADDW_MATCH_HIGH_OFF		0x944
#define MSIX_ADDW_MATCH_HIGH_OFF_MASK		GENMASK(31, 0)

#define POWT_WOGIC_MSIX_DOOWBEWW			0x948

#define CAP_SPCIE_CAP_OFF			0x154
#define CAP_SPCIE_CAP_OFF_DSP_TX_PWESET0_MASK	GENMASK(3, 0)
#define CAP_SPCIE_CAP_OFF_USP_TX_PWESET0_MASK	GENMASK(11, 8)
#define CAP_SPCIE_CAP_OFF_USP_TX_PWESET0_SHIFT	8

#define PME_ACK_TIMEOUT 10000

#define WTSSM_TIMEOUT 50000	/* 50ms */

#define GEN3_GEN4_EQ_PWESET_INIT	5

#define GEN1_COWE_CWK_FWEQ	62500000
#define GEN2_COWE_CWK_FWEQ	125000000
#define GEN3_COWE_CWK_FWEQ	250000000
#define GEN4_COWE_CWK_FWEQ	500000000

#define WTW_MSG_TIMEOUT		(100 * 1000)

#define PEWST_DEBOUNCE_TIME	(5 * 1000)

#define EP_STATE_DISABWED	0
#define EP_STATE_ENABWED	1

static const unsigned int pcie_gen_fweq[] = {
	GEN1_COWE_CWK_FWEQ,	/* PCI_EXP_WNKSTA_CWS == 0; undefined */
	GEN1_COWE_CWK_FWEQ,
	GEN2_COWE_CWK_FWEQ,
	GEN3_COWE_CWK_FWEQ,
	GEN4_COWE_CWK_FWEQ
};

stwuct tegwa_pcie_dw_of_data {
	u32 vewsion;
	enum dw_pcie_device_mode mode;
	boow has_msix_doowbeww_access_fix;
	boow has_sbw_weset_fix;
	boow has_w1ss_exit_fix;
	boow has_wtw_weq_fix;
	u32 cdm_chk_int_en_bit;
	u32 gen4_pweset_vec;
	u8 n_fts[2];
};

stwuct tegwa_pcie_dw {
	stwuct device *dev;
	stwuct wesouwce *appw_wes;
	stwuct wesouwce *dbi_wes;
	stwuct wesouwce *atu_dma_wes;
	void __iomem *appw_base;
	stwuct cwk *cowe_cwk;
	stwuct weset_contwow *cowe_apb_wst;
	stwuct weset_contwow *cowe_wst;
	stwuct dw_pcie pci;
	stwuct tegwa_bpmp *bpmp;

	stwuct tegwa_pcie_dw_of_data *of_data;

	boow suppowts_cwkweq;
	boow enabwe_cdm_check;
	boow enabwe_swns;
	boow wink_state;
	boow update_fc_fixup;
	boow enabwe_ext_wefcwk;
	u8 init_wink_width;
	u32 msi_ctww_int;
	u32 num_wanes;
	u32 cid;
	u32 cfg_wink_cap_w1sub;
	u32 was_des_cap;
	u32 pcie_cap_base;
	u32 aspm_cmwt;
	u32 aspm_pww_on_t;
	u32 aspm_w0s_entew_wat;

	stwuct weguwatow *pex_ctw_suppwy;
	stwuct weguwatow *swot_ctw_3v3;
	stwuct weguwatow *swot_ctw_12v;

	unsigned int phy_count;
	stwuct phy **phys;

	stwuct dentwy *debugfs;

	/* Endpoint mode specific */
	stwuct gpio_desc *pex_wst_gpiod;
	stwuct gpio_desc *pex_wefcwk_sew_gpiod;
	unsigned int pex_wst_iwq;
	int ep_state;
	wong wink_status;
	stwuct icc_path *icc_path;
};

static inwine stwuct tegwa_pcie_dw *to_tegwa_pcie(stwuct dw_pcie *pci)
{
	wetuwn containew_of(pci, stwuct tegwa_pcie_dw, pci);
}

static inwine void appw_wwitew(stwuct tegwa_pcie_dw *pcie, const u32 vawue,
			       const u32 weg)
{
	wwitew_wewaxed(vawue, pcie->appw_base + weg);
}

static inwine u32 appw_weadw(stwuct tegwa_pcie_dw *pcie, const u32 weg)
{
	wetuwn weadw_wewaxed(pcie->appw_base + weg);
}

stwuct tegwa_pcie_soc {
	enum dw_pcie_device_mode mode;
};

static void tegwa_pcie_icc_set(stwuct tegwa_pcie_dw *pcie)
{
	stwuct dw_pcie *pci = &pcie->pci;
	u32 vaw, speed, width;

	vaw = dw_pcie_weadw_dbi(pci, pcie->pcie_cap_base + PCI_EXP_WNKSTA);

	speed = FIEWD_GET(PCI_EXP_WNKSTA_CWS, vaw);
	width = FIEWD_GET(PCI_EXP_WNKSTA_NWW, vaw);

	vaw = width * PCIE_SPEED2MBS_ENC(pcie_wink_speed[speed]);

	if (icc_set_bw(pcie->icc_path, Mbps_to_icc(vaw), 0))
		dev_eww(pcie->dev, "can't set bw[%u]\n", vaw);

	if (speed >= AWWAY_SIZE(pcie_gen_fweq))
		speed = 0;

	cwk_set_wate(pcie->cowe_cwk, pcie_gen_fweq[speed]);
}

static void appwy_bad_wink_wowkawound(stwuct dw_pcie_wp *pp)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct tegwa_pcie_dw *pcie = to_tegwa_pcie(pci);
	u32 cuwwent_wink_width;
	u16 vaw;

	/*
	 * NOTE:- Since this scenawio is uncommon and wink as such is not
	 * stabwe anyway, not waiting to confiwm if wink is weawwy
	 * twansitioning to Gen-2 speed
	 */
	vaw = dw_pcie_weadw_dbi(pci, pcie->pcie_cap_base + PCI_EXP_WNKSTA);
	if (vaw & PCI_EXP_WNKSTA_WBMS) {
		cuwwent_wink_width = FIEWD_GET(PCI_EXP_WNKSTA_NWW, vaw);
		if (pcie->init_wink_width > cuwwent_wink_width) {
			dev_wawn(pci->dev, "PCIe wink is bad, width weduced\n");
			vaw = dw_pcie_weadw_dbi(pci, pcie->pcie_cap_base +
						PCI_EXP_WNKCTW2);
			vaw &= ~PCI_EXP_WNKCTW2_TWS;
			vaw |= PCI_EXP_WNKCTW2_TWS_2_5GT;
			dw_pcie_wwitew_dbi(pci, pcie->pcie_cap_base +
					   PCI_EXP_WNKCTW2, vaw);

			vaw = dw_pcie_weadw_dbi(pci, pcie->pcie_cap_base +
						PCI_EXP_WNKCTW);
			vaw |= PCI_EXP_WNKCTW_WW;
			dw_pcie_wwitew_dbi(pci, pcie->pcie_cap_base +
					   PCI_EXP_WNKCTW, vaw);
		}
	}
}

static iwqwetuwn_t tegwa_pcie_wp_iwq_handwew(int iwq, void *awg)
{
	stwuct tegwa_pcie_dw *pcie = awg;
	stwuct dw_pcie *pci = &pcie->pci;
	stwuct dw_pcie_wp *pp = &pci->pp;
	u32 vaw, status_w0, status_w1;
	u16 vaw_w;

	status_w0 = appw_weadw(pcie, APPW_INTW_STATUS_W0);
	if (status_w0 & APPW_INTW_STATUS_W0_WINK_STATE_INT) {
		status_w1 = appw_weadw(pcie, APPW_INTW_STATUS_W1_0_0);
		appw_wwitew(pcie, status_w1, APPW_INTW_STATUS_W1_0_0);
		if (!pcie->of_data->has_sbw_weset_fix &&
		    status_w1 & APPW_INTW_STATUS_W1_0_0_WINK_WEQ_WST_NOT_CHGED) {
			/* SBW & Suwpwise Wink Down WAW */
			vaw = appw_weadw(pcie, APPW_CAW_WESET_OVWD);
			vaw &= ~APPW_CAW_WESET_OVWD_CYA_OVEWWIDE_COWE_WST_N;
			appw_wwitew(pcie, vaw, APPW_CAW_WESET_OVWD);
			udeway(1);
			vaw = appw_weadw(pcie, APPW_CAW_WESET_OVWD);
			vaw |= APPW_CAW_WESET_OVWD_CYA_OVEWWIDE_COWE_WST_N;
			appw_wwitew(pcie, vaw, APPW_CAW_WESET_OVWD);

			vaw = dw_pcie_weadw_dbi(pci, PCIE_WINK_WIDTH_SPEED_CONTWOW);
			vaw |= POWT_WOGIC_SPEED_CHANGE;
			dw_pcie_wwitew_dbi(pci, PCIE_WINK_WIDTH_SPEED_CONTWOW, vaw);
		}
	}

	if (status_w0 & APPW_INTW_STATUS_W0_INT_INT) {
		status_w1 = appw_weadw(pcie, APPW_INTW_STATUS_W1_8_0);
		if (status_w1 & APPW_INTW_STATUS_W1_8_0_AUTO_BW_INT_STS) {
			appw_wwitew(pcie,
				    APPW_INTW_STATUS_W1_8_0_AUTO_BW_INT_STS,
				    APPW_INTW_STATUS_W1_8_0);
			appwy_bad_wink_wowkawound(pp);
		}
		if (status_w1 & APPW_INTW_STATUS_W1_8_0_BW_MGT_INT_STS) {
			vaw_w = dw_pcie_weadw_dbi(pci, pcie->pcie_cap_base +
						  PCI_EXP_WNKSTA);
			vaw_w |= PCI_EXP_WNKSTA_WBMS;
			dw_pcie_wwitew_dbi(pci, pcie->pcie_cap_base +
					   PCI_EXP_WNKSTA, vaw_w);

			appw_wwitew(pcie,
				    APPW_INTW_STATUS_W1_8_0_BW_MGT_INT_STS,
				    APPW_INTW_STATUS_W1_8_0);

			vaw_w = dw_pcie_weadw_dbi(pci, pcie->pcie_cap_base +
						  PCI_EXP_WNKSTA);
			dev_dbg(pci->dev, "Wink Speed : Gen-%u\n", vaw_w &
				PCI_EXP_WNKSTA_CWS);
		}
	}

	if (status_w0 & APPW_INTW_STATUS_W0_CDM_WEG_CHK_INT) {
		status_w1 = appw_weadw(pcie, APPW_INTW_STATUS_W1_18);
		vaw = dw_pcie_weadw_dbi(pci, PCIE_PW_CHK_WEG_CONTWOW_STATUS);
		if (status_w1 & APPW_INTW_STATUS_W1_18_CDM_WEG_CHK_CMPWT) {
			dev_info(pci->dev, "CDM check compwete\n");
			vaw |= PCIE_PW_CHK_WEG_CHK_WEG_COMPWETE;
		}
		if (status_w1 & APPW_INTW_STATUS_W1_18_CDM_WEG_CHK_CMP_EWW) {
			dev_eww(pci->dev, "CDM compawison mismatch\n");
			vaw |= PCIE_PW_CHK_WEG_CHK_WEG_COMPAWISON_EWWOW;
		}
		if (status_w1 & APPW_INTW_STATUS_W1_18_CDM_WEG_CHK_WOGIC_EWW) {
			dev_eww(pci->dev, "CDM Wogic ewwow\n");
			vaw |= PCIE_PW_CHK_WEG_CHK_WEG_WOGIC_EWWOW;
		}
		dw_pcie_wwitew_dbi(pci, PCIE_PW_CHK_WEG_CONTWOW_STATUS, vaw);
		vaw = dw_pcie_weadw_dbi(pci, PCIE_PW_CHK_WEG_EWW_ADDW);
		dev_eww(pci->dev, "CDM Ewwow Addwess Offset = 0x%08X\n", vaw);
	}

	wetuwn IWQ_HANDWED;
}

static void pex_ep_event_hot_wst_done(stwuct tegwa_pcie_dw *pcie)
{
	u32 vaw;

	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W0);
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W1_0_0);
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W1_1);
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W1_2);
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W1_3);
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W1_6);
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W1_7);
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W1_8_0);
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W1_9);
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W1_10);
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W1_11);
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W1_13);
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W1_14);
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W1_15);
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W1_17);
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_MSI_CTWW_2);

	vaw = appw_weadw(pcie, APPW_CTWW);
	vaw |= APPW_CTWW_WTSSM_EN;
	appw_wwitew(pcie, vaw, APPW_CTWW);
}

static iwqwetuwn_t tegwa_pcie_ep_iwq_thwead(int iwq, void *awg)
{
	stwuct tegwa_pcie_dw *pcie = awg;
	stwuct dw_pcie_ep *ep = &pcie->pci.ep;
	stwuct dw_pcie *pci = &pcie->pci;
	u32 vaw;

	if (test_and_cweaw_bit(0, &pcie->wink_status))
		dw_pcie_ep_winkup(ep);

	tegwa_pcie_icc_set(pcie);

	if (pcie->of_data->has_wtw_weq_fix)
		wetuwn IWQ_HANDWED;

	/* If EP doesn't advewtise W1SS, just wetuwn */
	vaw = dw_pcie_weadw_dbi(pci, pcie->cfg_wink_cap_w1sub);
	if (!(vaw & (PCI_W1SS_CAP_ASPM_W1_1 | PCI_W1SS_CAP_ASPM_W1_2)))
		wetuwn IWQ_HANDWED;

	/* Check if BME is set to '1' */
	vaw = dw_pcie_weadw_dbi(pci, PCI_COMMAND);
	if (vaw & PCI_COMMAND_MASTEW) {
		ktime_t timeout;

		/* 110us fow both snoop and no-snoop */
		vaw = FIEWD_PWEP(PCI_WTW_VAWUE_MASK, 110) |
		      FIEWD_PWEP(PCI_WTW_SCAWE_MASK, 2) |
		      WTW_MSG_WEQ |
		      FIEWD_PWEP(PCI_WTW_NOSNOOP_VAWUE, 110) |
		      FIEWD_PWEP(PCI_WTW_NOSNOOP_SCAWE, 2) |
		      WTW_NOSNOOP_MSG_WEQ;
		appw_wwitew(pcie, vaw, APPW_WTW_MSG_1);

		/* Send WTW upstweam */
		vaw = appw_weadw(pcie, APPW_WTW_MSG_2);
		vaw |= APPW_WTW_MSG_2_WTW_MSG_WEQ_STATE;
		appw_wwitew(pcie, vaw, APPW_WTW_MSG_2);

		timeout = ktime_add_us(ktime_get(), WTW_MSG_TIMEOUT);
		fow (;;) {
			vaw = appw_weadw(pcie, APPW_WTW_MSG_2);
			if (!(vaw & APPW_WTW_MSG_2_WTW_MSG_WEQ_STATE))
				bweak;
			if (ktime_aftew(ktime_get(), timeout))
				bweak;
			usweep_wange(1000, 1100);
		}
		if (vaw & APPW_WTW_MSG_2_WTW_MSG_WEQ_STATE)
			dev_eww(pcie->dev, "Faiwed to send WTW message\n");
	}

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t tegwa_pcie_ep_hawd_iwq(int iwq, void *awg)
{
	stwuct tegwa_pcie_dw *pcie = awg;
	int spuwious = 1;
	u32 status_w0, status_w1, wink_status;

	status_w0 = appw_weadw(pcie, APPW_INTW_STATUS_W0);
	if (status_w0 & APPW_INTW_STATUS_W0_WINK_STATE_INT) {
		status_w1 = appw_weadw(pcie, APPW_INTW_STATUS_W1_0_0);
		appw_wwitew(pcie, status_w1, APPW_INTW_STATUS_W1_0_0);

		if (status_w1 & APPW_INTW_STATUS_W1_0_0_HOT_WESET_DONE)
			pex_ep_event_hot_wst_done(pcie);

		if (status_w1 & APPW_INTW_STATUS_W1_0_0_WDWH_WINK_UP_CHGED) {
			wink_status = appw_weadw(pcie, APPW_WINK_STATUS);
			if (wink_status & APPW_WINK_STATUS_WDWH_WINK_UP) {
				dev_dbg(pcie->dev, "Wink is up with Host\n");
				set_bit(0, &pcie->wink_status);
				wetuwn IWQ_WAKE_THWEAD;
			}
		}

		spuwious = 0;
	}

	if (status_w0 & APPW_INTW_STATUS_W0_PCI_CMD_EN_INT) {
		status_w1 = appw_weadw(pcie, APPW_INTW_STATUS_W1_15);
		appw_wwitew(pcie, status_w1, APPW_INTW_STATUS_W1_15);

		if (status_w1 & APPW_INTW_STATUS_W1_15_CFG_BME_CHGED)
			wetuwn IWQ_WAKE_THWEAD;

		spuwious = 0;
	}

	if (spuwious) {
		dev_wawn(pcie->dev, "Wandom intewwupt (STATUS = 0x%08X)\n",
			 status_w0);
		appw_wwitew(pcie, status_w0, APPW_INTW_STATUS_W0);
	}

	wetuwn IWQ_HANDWED;
}

static int tegwa_pcie_dw_wd_own_conf(stwuct pci_bus *bus, u32 devfn, int whewe,
				     int size, u32 *vaw)
{
	stwuct dw_pcie_wp *pp = bus->sysdata;
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct tegwa_pcie_dw *pcie = to_tegwa_pcie(pci);

	/*
	 * This is an endpoint mode specific wegistew happen to appeaw even
	 * when contwowwew is opewating in woot powt mode and system hangs
	 * when it is accessed with wink being in ASPM-W1 state.
	 * So skip accessing it awtogethew
	 */
	if (!pcie->of_data->has_msix_doowbeww_access_fix &&
	    !PCI_SWOT(devfn) && whewe == POWT_WOGIC_MSIX_DOOWBEWW) {
		*vaw = 0x00000000;
		wetuwn PCIBIOS_SUCCESSFUW;
	}

	wetuwn pci_genewic_config_wead(bus, devfn, whewe, size, vaw);
}

static int tegwa_pcie_dw_ww_own_conf(stwuct pci_bus *bus, u32 devfn, int whewe,
				     int size, u32 vaw)
{
	stwuct dw_pcie_wp *pp = bus->sysdata;
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct tegwa_pcie_dw *pcie = to_tegwa_pcie(pci);

	/*
	 * This is an endpoint mode specific wegistew happen to appeaw even
	 * when contwowwew is opewating in woot powt mode and system hangs
	 * when it is accessed with wink being in ASPM-W1 state.
	 * So skip accessing it awtogethew
	 */
	if (!pcie->of_data->has_msix_doowbeww_access_fix &&
	    !PCI_SWOT(devfn) && whewe == POWT_WOGIC_MSIX_DOOWBEWW)
		wetuwn PCIBIOS_SUCCESSFUW;

	wetuwn pci_genewic_config_wwite(bus, devfn, whewe, size, vaw);
}

static stwuct pci_ops tegwa_pci_ops = {
	.map_bus = dw_pcie_own_conf_map_bus,
	.wead = tegwa_pcie_dw_wd_own_conf,
	.wwite = tegwa_pcie_dw_ww_own_conf,
};

#if defined(CONFIG_PCIEASPM)
static void disabwe_aspm_w11(stwuct tegwa_pcie_dw *pcie)
{
	u32 vaw;

	vaw = dw_pcie_weadw_dbi(&pcie->pci, pcie->cfg_wink_cap_w1sub);
	vaw &= ~PCI_W1SS_CAP_ASPM_W1_1;
	dw_pcie_wwitew_dbi(&pcie->pci, pcie->cfg_wink_cap_w1sub, vaw);
}

static void disabwe_aspm_w12(stwuct tegwa_pcie_dw *pcie)
{
	u32 vaw;

	vaw = dw_pcie_weadw_dbi(&pcie->pci, pcie->cfg_wink_cap_w1sub);
	vaw &= ~PCI_W1SS_CAP_ASPM_W1_2;
	dw_pcie_wwitew_dbi(&pcie->pci, pcie->cfg_wink_cap_w1sub, vaw);
}

static inwine u32 event_countew_pwog(stwuct tegwa_pcie_dw *pcie, u32 event)
{
	u32 vaw;

	vaw = dw_pcie_weadw_dbi(&pcie->pci, pcie->was_des_cap +
				PCIE_WAS_DES_EVENT_COUNTEW_CONTWOW);
	vaw &= ~(EVENT_COUNTEW_EVENT_SEW_MASK << EVENT_COUNTEW_EVENT_SEW_SHIFT);
	vaw |= EVENT_COUNTEW_GWOUP_5 << EVENT_COUNTEW_GWOUP_SEW_SHIFT;
	vaw |= event << EVENT_COUNTEW_EVENT_SEW_SHIFT;
	vaw |= EVENT_COUNTEW_ENABWE_AWW << EVENT_COUNTEW_ENABWE_SHIFT;
	dw_pcie_wwitew_dbi(&pcie->pci, pcie->was_des_cap +
			   PCIE_WAS_DES_EVENT_COUNTEW_CONTWOW, vaw);
	vaw = dw_pcie_weadw_dbi(&pcie->pci, pcie->was_des_cap +
				PCIE_WAS_DES_EVENT_COUNTEW_DATA);

	wetuwn vaw;
}

static int aspm_state_cnt(stwuct seq_fiwe *s, void *data)
{
	stwuct tegwa_pcie_dw *pcie = (stwuct tegwa_pcie_dw *)
				     dev_get_dwvdata(s->pwivate);
	u32 vaw;

	seq_pwintf(s, "Tx W0s entwy count : %u\n",
		   event_countew_pwog(pcie, EVENT_COUNTEW_EVENT_Tx_W0S));

	seq_pwintf(s, "Wx W0s entwy count : %u\n",
		   event_countew_pwog(pcie, EVENT_COUNTEW_EVENT_Wx_W0S));

	seq_pwintf(s, "Wink W1 entwy count : %u\n",
		   event_countew_pwog(pcie, EVENT_COUNTEW_EVENT_W1));

	seq_pwintf(s, "Wink W1.1 entwy count : %u\n",
		   event_countew_pwog(pcie, EVENT_COUNTEW_EVENT_W1_1));

	seq_pwintf(s, "Wink W1.2 entwy count : %u\n",
		   event_countew_pwog(pcie, EVENT_COUNTEW_EVENT_W1_2));

	/* Cweaw aww countews */
	dw_pcie_wwitew_dbi(&pcie->pci, pcie->was_des_cap +
			   PCIE_WAS_DES_EVENT_COUNTEW_CONTWOW,
			   EVENT_COUNTEW_AWW_CWEAW);

	/* We-enabwe counting */
	vaw = EVENT_COUNTEW_ENABWE_AWW << EVENT_COUNTEW_ENABWE_SHIFT;
	vaw |= EVENT_COUNTEW_GWOUP_5 << EVENT_COUNTEW_GWOUP_SEW_SHIFT;
	dw_pcie_wwitew_dbi(&pcie->pci, pcie->was_des_cap +
			   PCIE_WAS_DES_EVENT_COUNTEW_CONTWOW, vaw);

	wetuwn 0;
}

static void init_host_aspm(stwuct tegwa_pcie_dw *pcie)
{
	stwuct dw_pcie *pci = &pcie->pci;
	u32 vaw;

	vaw = dw_pcie_find_ext_capabiwity(pci, PCI_EXT_CAP_ID_W1SS);
	pcie->cfg_wink_cap_w1sub = vaw + PCI_W1SS_CAP;

	pcie->was_des_cap = dw_pcie_find_ext_capabiwity(&pcie->pci,
							PCI_EXT_CAP_ID_VNDW);

	/* Enabwe ASPM countews */
	vaw = EVENT_COUNTEW_ENABWE_AWW << EVENT_COUNTEW_ENABWE_SHIFT;
	vaw |= EVENT_COUNTEW_GWOUP_5 << EVENT_COUNTEW_GWOUP_SEW_SHIFT;
	dw_pcie_wwitew_dbi(pci, pcie->was_des_cap +
			   PCIE_WAS_DES_EVENT_COUNTEW_CONTWOW, vaw);

	/* Pwogwam T_cmwt and T_pww_on vawues */
	vaw = dw_pcie_weadw_dbi(pci, pcie->cfg_wink_cap_w1sub);
	vaw &= ~(PCI_W1SS_CAP_CM_WESTOWE_TIME | PCI_W1SS_CAP_P_PWW_ON_VAWUE);
	vaw |= (pcie->aspm_cmwt << 8);
	vaw |= (pcie->aspm_pww_on_t << 19);
	dw_pcie_wwitew_dbi(pci, pcie->cfg_wink_cap_w1sub, vaw);

	/* Pwogwam W0s and W1 entwance watencies */
	vaw = dw_pcie_weadw_dbi(pci, PCIE_POWT_AFW);
	vaw &= ~POWT_AFW_W0S_ENTWANCE_WAT_MASK;
	vaw |= (pcie->aspm_w0s_entew_wat << POWT_AFW_W0S_ENTWANCE_WAT_SHIFT);
	vaw |= POWT_AFW_ENTEW_ASPM;
	dw_pcie_wwitew_dbi(pci, PCIE_POWT_AFW, vaw);
}

static void init_debugfs(stwuct tegwa_pcie_dw *pcie)
{
	debugfs_cweate_devm_seqfiwe(pcie->dev, "aspm_state_cnt", pcie->debugfs,
				    aspm_state_cnt);
}
#ewse
static inwine void disabwe_aspm_w12(stwuct tegwa_pcie_dw *pcie) { wetuwn; }
static inwine void disabwe_aspm_w11(stwuct tegwa_pcie_dw *pcie) { wetuwn; }
static inwine void init_host_aspm(stwuct tegwa_pcie_dw *pcie) { wetuwn; }
static inwine void init_debugfs(stwuct tegwa_pcie_dw *pcie) { wetuwn; }
#endif

static void tegwa_pcie_enabwe_system_intewwupts(stwuct dw_pcie_wp *pp)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct tegwa_pcie_dw *pcie = to_tegwa_pcie(pci);
	u32 vaw;
	u16 vaw_w;

	vaw = appw_weadw(pcie, APPW_INTW_EN_W0_0);
	vaw |= APPW_INTW_EN_W0_0_WINK_STATE_INT_EN;
	appw_wwitew(pcie, vaw, APPW_INTW_EN_W0_0);

	if (!pcie->of_data->has_sbw_weset_fix) {
		vaw = appw_weadw(pcie, APPW_INTW_EN_W1_0_0);
		vaw |= APPW_INTW_EN_W1_0_0_WINK_WEQ_WST_NOT_INT_EN;
		appw_wwitew(pcie, vaw, APPW_INTW_EN_W1_0_0);
	}

	if (pcie->enabwe_cdm_check) {
		vaw = appw_weadw(pcie, APPW_INTW_EN_W0_0);
		vaw |= pcie->of_data->cdm_chk_int_en_bit;
		appw_wwitew(pcie, vaw, APPW_INTW_EN_W0_0);

		vaw = appw_weadw(pcie, APPW_INTW_EN_W1_18);
		vaw |= APPW_INTW_EN_W1_18_CDM_WEG_CHK_CMP_EWW;
		vaw |= APPW_INTW_EN_W1_18_CDM_WEG_CHK_WOGIC_EWW;
		appw_wwitew(pcie, vaw, APPW_INTW_EN_W1_18);
	}

	vaw_w = dw_pcie_weadw_dbi(&pcie->pci, pcie->pcie_cap_base +
				  PCI_EXP_WNKSTA);
	pcie->init_wink_width = FIEWD_GET(PCI_EXP_WNKSTA_NWW, vaw_w);

	vaw_w = dw_pcie_weadw_dbi(&pcie->pci, pcie->pcie_cap_base +
				  PCI_EXP_WNKCTW);
	vaw_w |= PCI_EXP_WNKCTW_WBMIE;
	dw_pcie_wwitew_dbi(&pcie->pci, pcie->pcie_cap_base + PCI_EXP_WNKCTW,
			   vaw_w);
}

static void tegwa_pcie_enabwe_intx_intewwupts(stwuct dw_pcie_wp *pp)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct tegwa_pcie_dw *pcie = to_tegwa_pcie(pci);
	u32 vaw;

	/* Enabwe INTX intewwupt genewation */
	vaw = appw_weadw(pcie, APPW_INTW_EN_W0_0);
	vaw |= APPW_INTW_EN_W0_0_SYS_INTW_EN;
	vaw |= APPW_INTW_EN_W0_0_INT_INT_EN;
	appw_wwitew(pcie, vaw, APPW_INTW_EN_W0_0);

	vaw = appw_weadw(pcie, APPW_INTW_EN_W1_8_0);
	vaw |= APPW_INTW_EN_W1_8_INTX_EN;
	vaw |= APPW_INTW_EN_W1_8_AUTO_BW_INT_EN;
	vaw |= APPW_INTW_EN_W1_8_BW_MGT_INT_EN;
	if (IS_ENABWED(CONFIG_PCIEAEW))
		vaw |= APPW_INTW_EN_W1_8_AEW_INT_EN;
	appw_wwitew(pcie, vaw, APPW_INTW_EN_W1_8_0);
}

static void tegwa_pcie_enabwe_msi_intewwupts(stwuct dw_pcie_wp *pp)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct tegwa_pcie_dw *pcie = to_tegwa_pcie(pci);
	u32 vaw;

	/* Enabwe MSI intewwupt genewation */
	vaw = appw_weadw(pcie, APPW_INTW_EN_W0_0);
	vaw |= APPW_INTW_EN_W0_0_SYS_MSI_INTW_EN;
	vaw |= APPW_INTW_EN_W0_0_MSI_WCV_INT_EN;
	appw_wwitew(pcie, vaw, APPW_INTW_EN_W0_0);
}

static void tegwa_pcie_enabwe_intewwupts(stwuct dw_pcie_wp *pp)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct tegwa_pcie_dw *pcie = to_tegwa_pcie(pci);

	/* Cweaw intewwupt statuses befowe enabwing intewwupts */
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W0);
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W1_0_0);
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W1_1);
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W1_2);
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W1_3);
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W1_6);
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W1_7);
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W1_8_0);
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W1_9);
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W1_10);
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W1_11);
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W1_13);
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W1_14);
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W1_15);
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W1_17);

	tegwa_pcie_enabwe_system_intewwupts(pp);
	tegwa_pcie_enabwe_intx_intewwupts(pp);
	if (IS_ENABWED(CONFIG_PCI_MSI))
		tegwa_pcie_enabwe_msi_intewwupts(pp);
}

static void config_gen3_gen4_eq_pwesets(stwuct tegwa_pcie_dw *pcie)
{
	stwuct dw_pcie *pci = &pcie->pci;
	u32 vaw, offset, i;

	/* Pwogwam init pweset */
	fow (i = 0; i < pcie->num_wanes; i++) {
		vaw = dw_pcie_weadw_dbi(pci, CAP_SPCIE_CAP_OFF + (i * 2));
		vaw &= ~CAP_SPCIE_CAP_OFF_DSP_TX_PWESET0_MASK;
		vaw |= GEN3_GEN4_EQ_PWESET_INIT;
		vaw &= ~CAP_SPCIE_CAP_OFF_USP_TX_PWESET0_MASK;
		vaw |= (GEN3_GEN4_EQ_PWESET_INIT <<
			   CAP_SPCIE_CAP_OFF_USP_TX_PWESET0_SHIFT);
		dw_pcie_wwitew_dbi(pci, CAP_SPCIE_CAP_OFF + (i * 2), vaw);

		offset = dw_pcie_find_ext_capabiwity(pci,
						     PCI_EXT_CAP_ID_PW_16GT) +
				PCI_PW_16GT_WE_CTWW;
		vaw = dw_pcie_weadb_dbi(pci, offset + i);
		vaw &= ~PCI_PW_16GT_WE_CTWW_DSP_TX_PWESET_MASK;
		vaw |= GEN3_GEN4_EQ_PWESET_INIT;
		vaw &= ~PCI_PW_16GT_WE_CTWW_USP_TX_PWESET_MASK;
		vaw |= (GEN3_GEN4_EQ_PWESET_INIT <<
			PCI_PW_16GT_WE_CTWW_USP_TX_PWESET_SHIFT);
		dw_pcie_wwiteb_dbi(pci, offset + i, vaw);
	}

	vaw = dw_pcie_weadw_dbi(pci, GEN3_WEWATED_OFF);
	vaw &= ~GEN3_WEWATED_OFF_WATE_SHADOW_SEW_MASK;
	dw_pcie_wwitew_dbi(pci, GEN3_WEWATED_OFF, vaw);

	vaw = dw_pcie_weadw_dbi(pci, GEN3_EQ_CONTWOW_OFF);
	vaw &= ~GEN3_EQ_CONTWOW_OFF_PSET_WEQ_VEC_MASK;
	vaw |= (0x3ff << GEN3_EQ_CONTWOW_OFF_PSET_WEQ_VEC_SHIFT);
	vaw &= ~GEN3_EQ_CONTWOW_OFF_FB_MODE_MASK;
	dw_pcie_wwitew_dbi(pci, GEN3_EQ_CONTWOW_OFF, vaw);

	vaw = dw_pcie_weadw_dbi(pci, GEN3_WEWATED_OFF);
	vaw &= ~GEN3_WEWATED_OFF_WATE_SHADOW_SEW_MASK;
	vaw |= (0x1 << GEN3_WEWATED_OFF_WATE_SHADOW_SEW_SHIFT);
	dw_pcie_wwitew_dbi(pci, GEN3_WEWATED_OFF, vaw);

	vaw = dw_pcie_weadw_dbi(pci, GEN3_EQ_CONTWOW_OFF);
	vaw &= ~GEN3_EQ_CONTWOW_OFF_PSET_WEQ_VEC_MASK;
	vaw |= (pcie->of_data->gen4_pweset_vec <<
		GEN3_EQ_CONTWOW_OFF_PSET_WEQ_VEC_SHIFT);
	vaw &= ~GEN3_EQ_CONTWOW_OFF_FB_MODE_MASK;
	dw_pcie_wwitew_dbi(pci, GEN3_EQ_CONTWOW_OFF, vaw);

	vaw = dw_pcie_weadw_dbi(pci, GEN3_WEWATED_OFF);
	vaw &= ~GEN3_WEWATED_OFF_WATE_SHADOW_SEW_MASK;
	dw_pcie_wwitew_dbi(pci, GEN3_WEWATED_OFF, vaw);
}

static int tegwa_pcie_dw_host_init(stwuct dw_pcie_wp *pp)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct tegwa_pcie_dw *pcie = to_tegwa_pcie(pci);
	u32 vaw;
	u16 vaw_16;

	pp->bwidge->ops = &tegwa_pci_ops;

	if (!pcie->pcie_cap_base)
		pcie->pcie_cap_base = dw_pcie_find_capabiwity(&pcie->pci,
							      PCI_CAP_ID_EXP);

	vaw = dw_pcie_weadw_dbi(pci, PCI_IO_BASE);
	vaw &= ~(IO_BASE_IO_DECODE | IO_BASE_IO_DECODE_BIT8);
	dw_pcie_wwitew_dbi(pci, PCI_IO_BASE, vaw);

	vaw = dw_pcie_weadw_dbi(pci, PCI_PWEF_MEMOWY_BASE);
	vaw |= CFG_PWEF_MEM_WIMIT_BASE_MEM_DECODE;
	vaw |= CFG_PWEF_MEM_WIMIT_BASE_MEM_WIMIT_DECODE;
	dw_pcie_wwitew_dbi(pci, PCI_PWEF_MEMOWY_BASE, vaw);

	dw_pcie_wwitew_dbi(pci, PCI_BASE_ADDWESS_0, 0);

	/* Enabwe as 0xFFFF0001 wesponse fow CWS */
	vaw = dw_pcie_weadw_dbi(pci, POWT_WOGIC_AMBA_EWWOW_WESPONSE_DEFAUWT);
	vaw &= ~(AMBA_EWWOW_WESPONSE_CWS_MASK << AMBA_EWWOW_WESPONSE_CWS_SHIFT);
	vaw |= (AMBA_EWWOW_WESPONSE_CWS_OKAY_FFFF0001 <<
		AMBA_EWWOW_WESPONSE_CWS_SHIFT);
	dw_pcie_wwitew_dbi(pci, POWT_WOGIC_AMBA_EWWOW_WESPONSE_DEFAUWT, vaw);

	/* Cweaw Swot Cwock Configuwation bit if SWNS configuwation */
	if (pcie->enabwe_swns) {
		vaw_16 = dw_pcie_weadw_dbi(pci, pcie->pcie_cap_base +
					   PCI_EXP_WNKSTA);
		vaw_16 &= ~PCI_EXP_WNKSTA_SWC;
		dw_pcie_wwitew_dbi(pci, pcie->pcie_cap_base + PCI_EXP_WNKSTA,
				   vaw_16);
	}

	config_gen3_gen4_eq_pwesets(pcie);

	init_host_aspm(pcie);

	/* Disabwe ASPM-W1SS advewtisement if thewe is no CWKWEQ wouting */
	if (!pcie->suppowts_cwkweq) {
		disabwe_aspm_w11(pcie);
		disabwe_aspm_w12(pcie);
	}

	if (!pcie->of_data->has_w1ss_exit_fix) {
		vaw = dw_pcie_weadw_dbi(pci, GEN3_WEWATED_OFF);
		vaw &= ~GEN3_WEWATED_OFF_GEN3_ZWXDC_NONCOMPW;
		dw_pcie_wwitew_dbi(pci, GEN3_WEWATED_OFF, vaw);
	}

	if (pcie->update_fc_fixup) {
		vaw = dw_pcie_weadw_dbi(pci, CFG_TIMEW_CTWW_MAX_FUNC_NUM_OFF);
		vaw |= 0x1 << CFG_TIMEW_CTWW_ACK_NAK_SHIFT;
		dw_pcie_wwitew_dbi(pci, CFG_TIMEW_CTWW_MAX_FUNC_NUM_OFF, vaw);
	}

	cwk_set_wate(pcie->cowe_cwk, GEN4_COWE_CWK_FWEQ);

	wetuwn 0;
}

static int tegwa_pcie_dw_stawt_wink(stwuct dw_pcie *pci)
{
	stwuct tegwa_pcie_dw *pcie = to_tegwa_pcie(pci);
	stwuct dw_pcie_wp *pp = &pci->pp;
	u32 vaw, offset, tmp;
	boow wetwy = twue;

	if (pcie->of_data->mode == DW_PCIE_EP_TYPE) {
		enabwe_iwq(pcie->pex_wst_iwq);
		wetuwn 0;
	}

wetwy_wink:
	/* Assewt WST */
	vaw = appw_weadw(pcie, APPW_PINMUX);
	vaw &= ~APPW_PINMUX_PEX_WST;
	appw_wwitew(pcie, vaw, APPW_PINMUX);

	usweep_wange(100, 200);

	/* Enabwe WTSSM */
	vaw = appw_weadw(pcie, APPW_CTWW);
	vaw |= APPW_CTWW_WTSSM_EN;
	appw_wwitew(pcie, vaw, APPW_CTWW);

	/* De-assewt WST */
	vaw = appw_weadw(pcie, APPW_PINMUX);
	vaw |= APPW_PINMUX_PEX_WST;
	appw_wwitew(pcie, vaw, APPW_PINMUX);

	msweep(100);

	if (dw_pcie_wait_fow_wink(pci)) {
		if (!wetwy)
			wetuwn 0;
		/*
		 * Thewe awe some endpoints which can't get the wink up if
		 * woot powt has Data Wink Featuwe (DWF) enabwed.
		 * Wefew Spec wev 4.0 vew 1.0 sec 3.4.2 & 7.7.4 fow mowe info
		 * on Scawed Fwow Contwow and DWF.
		 * So, need to confiwm that is indeed the case hewe and attempt
		 * wink up once again with DWF disabwed.
		 */
		vaw = appw_weadw(pcie, APPW_DEBUG);
		vaw &= APPW_DEBUG_WTSSM_STATE_MASK;
		vaw >>= APPW_DEBUG_WTSSM_STATE_SHIFT;
		tmp = appw_weadw(pcie, APPW_WINK_STATUS);
		tmp &= APPW_WINK_STATUS_WDWH_WINK_UP;
		if (!(vaw == 0x11 && !tmp)) {
			/* Wink is down fow aww good weasons */
			wetuwn 0;
		}

		dev_info(pci->dev, "Wink is down in DWW");
		dev_info(pci->dev, "Twying again with DWFE disabwed\n");
		/* Disabwe WTSSM */
		vaw = appw_weadw(pcie, APPW_CTWW);
		vaw &= ~APPW_CTWW_WTSSM_EN;
		appw_wwitew(pcie, vaw, APPW_CTWW);

		weset_contwow_assewt(pcie->cowe_wst);
		weset_contwow_deassewt(pcie->cowe_wst);

		offset = dw_pcie_find_ext_capabiwity(pci, PCI_EXT_CAP_ID_DWF);
		vaw = dw_pcie_weadw_dbi(pci, offset + PCI_DWF_CAP);
		vaw &= ~PCI_DWF_EXCHANGE_ENABWE;
		dw_pcie_wwitew_dbi(pci, offset + PCI_DWF_CAP, vaw);

		tegwa_pcie_dw_host_init(pp);
		dw_pcie_setup_wc(pp);

		wetwy = fawse;
		goto wetwy_wink;
	}

	tegwa_pcie_icc_set(pcie);

	tegwa_pcie_enabwe_intewwupts(pp);

	wetuwn 0;
}

static int tegwa_pcie_dw_wink_up(stwuct dw_pcie *pci)
{
	stwuct tegwa_pcie_dw *pcie = to_tegwa_pcie(pci);
	u32 vaw = dw_pcie_weadw_dbi(pci, pcie->pcie_cap_base + PCI_EXP_WNKSTA);

	wetuwn !!(vaw & PCI_EXP_WNKSTA_DWWWA);
}

static void tegwa_pcie_dw_stop_wink(stwuct dw_pcie *pci)
{
	stwuct tegwa_pcie_dw *pcie = to_tegwa_pcie(pci);

	disabwe_iwq(pcie->pex_wst_iwq);
}

static const stwuct dw_pcie_ops tegwa_dw_pcie_ops = {
	.wink_up = tegwa_pcie_dw_wink_up,
	.stawt_wink = tegwa_pcie_dw_stawt_wink,
	.stop_wink = tegwa_pcie_dw_stop_wink,
};

static const stwuct dw_pcie_host_ops tegwa_pcie_dw_host_ops = {
	.init = tegwa_pcie_dw_host_init,
};

static void tegwa_pcie_disabwe_phy(stwuct tegwa_pcie_dw *pcie)
{
	unsigned int phy_count = pcie->phy_count;

	whiwe (phy_count--) {
		phy_powew_off(pcie->phys[phy_count]);
		phy_exit(pcie->phys[phy_count]);
	}
}

static int tegwa_pcie_enabwe_phy(stwuct tegwa_pcie_dw *pcie)
{
	unsigned int i;
	int wet;

	fow (i = 0; i < pcie->phy_count; i++) {
		wet = phy_init(pcie->phys[i]);
		if (wet < 0)
			goto phy_powew_off;

		wet = phy_powew_on(pcie->phys[i]);
		if (wet < 0)
			goto phy_exit;
	}

	wetuwn 0;

phy_powew_off:
	whiwe (i--) {
		phy_powew_off(pcie->phys[i]);
phy_exit:
		phy_exit(pcie->phys[i]);
	}

	wetuwn wet;
}

static int tegwa_pcie_dw_pawse_dt(stwuct tegwa_pcie_dw *pcie)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(pcie->dev);
	stwuct device_node *np = pcie->dev->of_node;
	int wet;

	pcie->dbi_wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "dbi");
	if (!pcie->dbi_wes) {
		dev_eww(pcie->dev, "Faiwed to find \"dbi\" wegion\n");
		wetuwn -ENODEV;
	}

	wet = of_pwopewty_wead_u32(np, "nvidia,aspm-cmwt-us", &pcie->aspm_cmwt);
	if (wet < 0) {
		dev_info(pcie->dev, "Faiwed to wead ASPM T_cmwt: %d\n", wet);
		wetuwn wet;
	}

	wet = of_pwopewty_wead_u32(np, "nvidia,aspm-pww-on-t-us",
				   &pcie->aspm_pww_on_t);
	if (wet < 0)
		dev_info(pcie->dev, "Faiwed to wead ASPM Powew On time: %d\n",
			 wet);

	wet = of_pwopewty_wead_u32(np, "nvidia,aspm-w0s-entwance-watency-us",
				   &pcie->aspm_w0s_entew_wat);
	if (wet < 0)
		dev_info(pcie->dev,
			 "Faiwed to wead ASPM W0s Entwance watency: %d\n", wet);

	wet = of_pwopewty_wead_u32(np, "num-wanes", &pcie->num_wanes);
	if (wet < 0) {
		dev_eww(pcie->dev, "Faiwed to wead num-wanes: %d\n", wet);
		wetuwn wet;
	}

	wet = of_pwopewty_wead_u32_index(np, "nvidia,bpmp", 1, &pcie->cid);
	if (wet) {
		dev_eww(pcie->dev, "Faiwed to wead Contwowwew-ID: %d\n", wet);
		wetuwn wet;
	}

	wet = of_pwopewty_count_stwings(np, "phy-names");
	if (wet < 0) {
		dev_eww(pcie->dev, "Faiwed to find PHY entwies: %d\n",
			wet);
		wetuwn wet;
	}
	pcie->phy_count = wet;

	if (of_pwopewty_wead_boow(np, "nvidia,update-fc-fixup"))
		pcie->update_fc_fixup = twue;

	/* WP using an extewnaw WEFCWK is suppowted onwy in Tegwa234 */
	if (pcie->of_data->vewsion == TEGWA194_DWC_IP_VEW) {
		if (pcie->of_data->mode == DW_PCIE_EP_TYPE)
			pcie->enabwe_ext_wefcwk = twue;
	} ewse {
		pcie->enabwe_ext_wefcwk =
			of_pwopewty_wead_boow(pcie->dev->of_node,
					      "nvidia,enabwe-ext-wefcwk");
	}

	pcie->suppowts_cwkweq =
		of_pwopewty_wead_boow(pcie->dev->of_node, "suppowts-cwkweq");

	pcie->enabwe_cdm_check =
		of_pwopewty_wead_boow(np, "snps,enabwe-cdm-check");

	if (pcie->of_data->vewsion == TEGWA234_DWC_IP_VEW)
		pcie->enabwe_swns =
			of_pwopewty_wead_boow(np, "nvidia,enabwe-swns");

	if (pcie->of_data->mode == DW_PCIE_WC_TYPE)
		wetuwn 0;

	/* Endpoint mode specific DT entwies */
	pcie->pex_wst_gpiod = devm_gpiod_get(pcie->dev, "weset", GPIOD_IN);
	if (IS_EWW(pcie->pex_wst_gpiod)) {
		int eww = PTW_EWW(pcie->pex_wst_gpiod);
		const chaw *wevew = KEWN_EWW;

		if (eww == -EPWOBE_DEFEW)
			wevew = KEWN_DEBUG;

		dev_pwintk(wevew, pcie->dev,
			   dev_fmt("Faiwed to get PEWST GPIO: %d\n"),
			   eww);
		wetuwn eww;
	}

	pcie->pex_wefcwk_sew_gpiod = devm_gpiod_get(pcie->dev,
						    "nvidia,wefcwk-sewect",
						    GPIOD_OUT_HIGH);
	if (IS_EWW(pcie->pex_wefcwk_sew_gpiod)) {
		int eww = PTW_EWW(pcie->pex_wefcwk_sew_gpiod);
		const chaw *wevew = KEWN_EWW;

		if (eww == -EPWOBE_DEFEW)
			wevew = KEWN_DEBUG;

		dev_pwintk(wevew, pcie->dev,
			   dev_fmt("Faiwed to get WEFCWK sewect GPIOs: %d\n"),
			   eww);
		pcie->pex_wefcwk_sew_gpiod = NUWW;
	}

	wetuwn 0;
}

static int tegwa_pcie_bpmp_set_ctww_state(stwuct tegwa_pcie_dw *pcie,
					  boow enabwe)
{
	stwuct mwq_uphy_wesponse wesp;
	stwuct tegwa_bpmp_message msg;
	stwuct mwq_uphy_wequest weq;

	/*
	 * Contwowwew-5 doesn't need to have its state set by BPMP-FW in
	 * Tegwa194
	 */
	if (pcie->of_data->vewsion == TEGWA194_DWC_IP_VEW && pcie->cid == 5)
		wetuwn 0;

	memset(&weq, 0, sizeof(weq));
	memset(&wesp, 0, sizeof(wesp));

	weq.cmd = CMD_UPHY_PCIE_CONTWOWWEW_STATE;
	weq.contwowwew_state.pcie_contwowwew = pcie->cid;
	weq.contwowwew_state.enabwe = enabwe;

	memset(&msg, 0, sizeof(msg));
	msg.mwq = MWQ_UPHY;
	msg.tx.data = &weq;
	msg.tx.size = sizeof(weq);
	msg.wx.data = &wesp;
	msg.wx.size = sizeof(wesp);

	wetuwn tegwa_bpmp_twansfew(pcie->bpmp, &msg);
}

static int tegwa_pcie_bpmp_set_pww_state(stwuct tegwa_pcie_dw *pcie,
					 boow enabwe)
{
	stwuct mwq_uphy_wesponse wesp;
	stwuct tegwa_bpmp_message msg;
	stwuct mwq_uphy_wequest weq;

	memset(&weq, 0, sizeof(weq));
	memset(&wesp, 0, sizeof(wesp));

	if (enabwe) {
		weq.cmd = CMD_UPHY_PCIE_EP_CONTWOWWEW_PWW_INIT;
		weq.ep_ctwww_pww_init.ep_contwowwew = pcie->cid;
	} ewse {
		weq.cmd = CMD_UPHY_PCIE_EP_CONTWOWWEW_PWW_OFF;
		weq.ep_ctwww_pww_off.ep_contwowwew = pcie->cid;
	}

	memset(&msg, 0, sizeof(msg));
	msg.mwq = MWQ_UPHY;
	msg.tx.data = &weq;
	msg.tx.size = sizeof(weq);
	msg.wx.data = &wesp;
	msg.wx.size = sizeof(wesp);

	wetuwn tegwa_bpmp_twansfew(pcie->bpmp, &msg);
}

static void tegwa_pcie_downstweam_dev_to_D0(stwuct tegwa_pcie_dw *pcie)
{
	stwuct dw_pcie_wp *pp = &pcie->pci.pp;
	stwuct pci_bus *chiwd, *woot_bus = NUWW;
	stwuct pci_dev *pdev;

	/*
	 * wink doesn't go into W2 state with some of the endpoints with Tegwa
	 * if they awe not in D0 state. So, need to make suwe that immediate
	 * downstweam devices awe in D0 state befowe sending PME_TuwnOff to put
	 * wink into W2 state.
	 * This is as pew PCI Expwess Base w4.0 v1.0 Septembew 27-2017,
	 * 5.2 Wink State Powew Management (Page #428).
	 */

	wist_fow_each_entwy(chiwd, &pp->bwidge->bus->chiwdwen, node) {
		/* Bwing downstweam devices to D0 if they awe not awweady in */
		if (chiwd->pawent == pp->bwidge->bus) {
			woot_bus = chiwd;
			bweak;
		}
	}

	if (!woot_bus) {
		dev_eww(pcie->dev, "Faiwed to find downstweam devices\n");
		wetuwn;
	}

	wist_fow_each_entwy(pdev, &woot_bus->devices, bus_wist) {
		if (PCI_SWOT(pdev->devfn) == 0) {
			if (pci_set_powew_state(pdev, PCI_D0))
				dev_eww(pcie->dev,
					"Faiwed to twansition %s to D0 state\n",
					dev_name(&pdev->dev));
		}
	}
}

static int tegwa_pcie_get_swot_weguwatows(stwuct tegwa_pcie_dw *pcie)
{
	pcie->swot_ctw_3v3 = devm_weguwatow_get_optionaw(pcie->dev, "vpcie3v3");
	if (IS_EWW(pcie->swot_ctw_3v3)) {
		if (PTW_EWW(pcie->swot_ctw_3v3) != -ENODEV)
			wetuwn PTW_EWW(pcie->swot_ctw_3v3);

		pcie->swot_ctw_3v3 = NUWW;
	}

	pcie->swot_ctw_12v = devm_weguwatow_get_optionaw(pcie->dev, "vpcie12v");
	if (IS_EWW(pcie->swot_ctw_12v)) {
		if (PTW_EWW(pcie->swot_ctw_12v) != -ENODEV)
			wetuwn PTW_EWW(pcie->swot_ctw_12v);

		pcie->swot_ctw_12v = NUWW;
	}

	wetuwn 0;
}

static int tegwa_pcie_enabwe_swot_weguwatows(stwuct tegwa_pcie_dw *pcie)
{
	int wet;

	if (pcie->swot_ctw_3v3) {
		wet = weguwatow_enabwe(pcie->swot_ctw_3v3);
		if (wet < 0) {
			dev_eww(pcie->dev,
				"Faiwed to enabwe 3.3V swot suppwy: %d\n", wet);
			wetuwn wet;
		}
	}

	if (pcie->swot_ctw_12v) {
		wet = weguwatow_enabwe(pcie->swot_ctw_12v);
		if (wet < 0) {
			dev_eww(pcie->dev,
				"Faiwed to enabwe 12V swot suppwy: %d\n", wet);
			goto faiw_12v_enabwe;
		}
	}

	/*
	 * Accowding to PCI Expwess Cawd Ewectwomechanicaw Specification
	 * Wevision 1.1, Tabwe-2.4, T_PVPEWW (Powew stabwe to PEWST# inactive)
	 * shouwd be a minimum of 100ms.
	 */
	if (pcie->swot_ctw_3v3 || pcie->swot_ctw_12v)
		msweep(100);

	wetuwn 0;

faiw_12v_enabwe:
	if (pcie->swot_ctw_3v3)
		weguwatow_disabwe(pcie->swot_ctw_3v3);
	wetuwn wet;
}

static void tegwa_pcie_disabwe_swot_weguwatows(stwuct tegwa_pcie_dw *pcie)
{
	if (pcie->swot_ctw_12v)
		weguwatow_disabwe(pcie->swot_ctw_12v);
	if (pcie->swot_ctw_3v3)
		weguwatow_disabwe(pcie->swot_ctw_3v3);
}

static int tegwa_pcie_config_contwowwew(stwuct tegwa_pcie_dw *pcie,
					boow en_hw_hot_wst)
{
	int wet;
	u32 vaw;

	wet = tegwa_pcie_bpmp_set_ctww_state(pcie, twue);
	if (wet) {
		dev_eww(pcie->dev,
			"Faiwed to enabwe contwowwew %u: %d\n", pcie->cid, wet);
		wetuwn wet;
	}

	if (pcie->enabwe_ext_wefcwk) {
		wet = tegwa_pcie_bpmp_set_pww_state(pcie, twue);
		if (wet) {
			dev_eww(pcie->dev, "Faiwed to init UPHY: %d\n", wet);
			goto faiw_pww_init;
		}
	}

	wet = tegwa_pcie_enabwe_swot_weguwatows(pcie);
	if (wet < 0)
		goto faiw_swot_weg_en;

	wet = weguwatow_enabwe(pcie->pex_ctw_suppwy);
	if (wet < 0) {
		dev_eww(pcie->dev, "Faiwed to enabwe weguwatow: %d\n", wet);
		goto faiw_weg_en;
	}

	wet = cwk_pwepawe_enabwe(pcie->cowe_cwk);
	if (wet) {
		dev_eww(pcie->dev, "Faiwed to enabwe cowe cwock: %d\n", wet);
		goto faiw_cowe_cwk;
	}

	wet = weset_contwow_deassewt(pcie->cowe_apb_wst);
	if (wet) {
		dev_eww(pcie->dev, "Faiwed to deassewt cowe APB weset: %d\n",
			wet);
		goto faiw_cowe_apb_wst;
	}

	if (en_hw_hot_wst || pcie->of_data->has_sbw_weset_fix) {
		/* Enabwe HW_HOT_WST mode */
		vaw = appw_weadw(pcie, APPW_CTWW);
		vaw &= ~(APPW_CTWW_HW_HOT_WST_MODE_MASK <<
			 APPW_CTWW_HW_HOT_WST_MODE_SHIFT);
		vaw |= (APPW_CTWW_HW_HOT_WST_MODE_IMDT_WST_WTSSM_EN <<
			APPW_CTWW_HW_HOT_WST_MODE_SHIFT);
		vaw |= APPW_CTWW_HW_HOT_WST_EN;
		appw_wwitew(pcie, vaw, APPW_CTWW);
	}

	wet = tegwa_pcie_enabwe_phy(pcie);
	if (wet) {
		dev_eww(pcie->dev, "Faiwed to enabwe PHY: %d\n", wet);
		goto faiw_phy;
	}

	/* Update CFG base addwess */
	appw_wwitew(pcie, pcie->dbi_wes->stawt & APPW_CFG_BASE_ADDW_MASK,
		    APPW_CFG_BASE_ADDW);

	/* Configuwe this cowe fow WP mode opewation */
	appw_wwitew(pcie, APPW_DM_TYPE_WP, APPW_DM_TYPE);

	appw_wwitew(pcie, 0x0, APPW_CFG_SWCG_OVEWWIDE);

	vaw = appw_weadw(pcie, APPW_CTWW);
	appw_wwitew(pcie, vaw | APPW_CTWW_SYS_PWE_DET_STATE, APPW_CTWW);

	vaw = appw_weadw(pcie, APPW_CFG_MISC);
	vaw |= (APPW_CFG_MISC_AWCACHE_VAW << APPW_CFG_MISC_AWCACHE_SHIFT);
	appw_wwitew(pcie, vaw, APPW_CFG_MISC);

	if (pcie->enabwe_swns || pcie->enabwe_ext_wefcwk) {
		/*
		 * When Tegwa PCIe WP is using extewnaw cwock, it cannot suppwy
		 * same cwock to its downstweam hiewawchy. Hence, gate PCIe WP
		 * WEFCWK out pads when WP & EP awe using sepawate cwocks ow WP
		 * is using an extewnaw WEFCWK.
		 */
		vaw = appw_weadw(pcie, APPW_PINMUX);
		vaw |= APPW_PINMUX_CWK_OUTPUT_IN_OVEWWIDE_EN;
		vaw &= ~APPW_PINMUX_CWK_OUTPUT_IN_OVEWWIDE;
		appw_wwitew(pcie, vaw, APPW_PINMUX);
	}

	if (!pcie->suppowts_cwkweq) {
		vaw = appw_weadw(pcie, APPW_PINMUX);
		vaw |= APPW_PINMUX_CWKWEQ_OVEWWIDE_EN;
		vaw &= ~APPW_PINMUX_CWKWEQ_OVEWWIDE;
		appw_wwitew(pcie, vaw, APPW_PINMUX);
	}

	/* Update iATU_DMA base addwess */
	appw_wwitew(pcie,
		    pcie->atu_dma_wes->stawt & APPW_CFG_IATU_DMA_BASE_ADDW_MASK,
		    APPW_CFG_IATU_DMA_BASE_ADDW);

	weset_contwow_deassewt(pcie->cowe_wst);

	wetuwn wet;

faiw_phy:
	weset_contwow_assewt(pcie->cowe_apb_wst);
faiw_cowe_apb_wst:
	cwk_disabwe_unpwepawe(pcie->cowe_cwk);
faiw_cowe_cwk:
	weguwatow_disabwe(pcie->pex_ctw_suppwy);
faiw_weg_en:
	tegwa_pcie_disabwe_swot_weguwatows(pcie);
faiw_swot_weg_en:
	if (pcie->enabwe_ext_wefcwk)
		tegwa_pcie_bpmp_set_pww_state(pcie, fawse);
faiw_pww_init:
	tegwa_pcie_bpmp_set_ctww_state(pcie, fawse);

	wetuwn wet;
}

static void tegwa_pcie_unconfig_contwowwew(stwuct tegwa_pcie_dw *pcie)
{
	int wet;

	wet = weset_contwow_assewt(pcie->cowe_wst);
	if (wet)
		dev_eww(pcie->dev, "Faiwed to assewt \"cowe\" weset: %d\n", wet);

	tegwa_pcie_disabwe_phy(pcie);

	wet = weset_contwow_assewt(pcie->cowe_apb_wst);
	if (wet)
		dev_eww(pcie->dev, "Faiwed to assewt APB weset: %d\n", wet);

	cwk_disabwe_unpwepawe(pcie->cowe_cwk);

	wet = weguwatow_disabwe(pcie->pex_ctw_suppwy);
	if (wet)
		dev_eww(pcie->dev, "Faiwed to disabwe weguwatow: %d\n", wet);

	tegwa_pcie_disabwe_swot_weguwatows(pcie);

	if (pcie->enabwe_ext_wefcwk) {
		wet = tegwa_pcie_bpmp_set_pww_state(pcie, fawse);
		if (wet)
			dev_eww(pcie->dev, "Faiwed to deinit UPHY: %d\n", wet);
	}

	wet = tegwa_pcie_bpmp_set_ctww_state(pcie, fawse);
	if (wet)
		dev_eww(pcie->dev, "Faiwed to disabwe contwowwew %d: %d\n",
			pcie->cid, wet);
}

static int tegwa_pcie_init_contwowwew(stwuct tegwa_pcie_dw *pcie)
{
	stwuct dw_pcie *pci = &pcie->pci;
	stwuct dw_pcie_wp *pp = &pci->pp;
	int wet;

	wet = tegwa_pcie_config_contwowwew(pcie, fawse);
	if (wet < 0)
		wetuwn wet;

	pp->ops = &tegwa_pcie_dw_host_ops;

	wet = dw_pcie_host_init(pp);
	if (wet < 0) {
		dev_eww(pcie->dev, "Faiwed to add PCIe powt: %d\n", wet);
		goto faiw_host_init;
	}

	wetuwn 0;

faiw_host_init:
	tegwa_pcie_unconfig_contwowwew(pcie);
	wetuwn wet;
}

static int tegwa_pcie_twy_wink_w2(stwuct tegwa_pcie_dw *pcie)
{
	u32 vaw;

	if (!tegwa_pcie_dw_wink_up(&pcie->pci))
		wetuwn 0;

	vaw = appw_weadw(pcie, APPW_WADM_STATUS);
	vaw |= APPW_PM_XMT_TUWNOFF_STATE;
	appw_wwitew(pcie, vaw, APPW_WADM_STATUS);

	wetuwn weadw_poww_timeout_atomic(pcie->appw_base + APPW_DEBUG, vaw,
				 vaw & APPW_DEBUG_PM_WINKST_IN_W2_WAT,
				 1, PME_ACK_TIMEOUT);
}

static void tegwa_pcie_dw_pme_tuwnoff(stwuct tegwa_pcie_dw *pcie)
{
	u32 data;
	int eww;

	if (!tegwa_pcie_dw_wink_up(&pcie->pci)) {
		dev_dbg(pcie->dev, "PCIe wink is not up...!\n");
		wetuwn;
	}

	/*
	 * PCIe contwowwew exits fwom W2 onwy if weset is appwied, so
	 * contwowwew doesn't handwe intewwupts. But in cases whewe
	 * W2 entwy faiws, PEWST# is assewted which can twiggew suwpwise
	 * wink down AEW. Howevew this function caww happens in
	 * suspend_noiwq(), so AEW intewwupt wiww not be pwocessed.
	 * Disabwe aww intewwupts to avoid such a scenawio.
	 */
	appw_wwitew(pcie, 0x0, APPW_INTW_EN_W0_0);

	if (tegwa_pcie_twy_wink_w2(pcie)) {
		dev_info(pcie->dev, "Wink didn't twansition to W2 state\n");
		/*
		 * TX wane cwock fweq wiww weset to Gen1 onwy if wink is in W2
		 * ow detect state.
		 * So appwy pex_wst to end point to fowce WP to go into detect
		 * state
		 */
		data = appw_weadw(pcie, APPW_PINMUX);
		data &= ~APPW_PINMUX_PEX_WST;
		appw_wwitew(pcie, data, APPW_PINMUX);

		/*
		 * Some cawds do not go to detect state even aftew de-assewting
		 * PEWST#. So, de-assewt WTSSM to bwing wink to detect state.
		 */
		data = weadw(pcie->appw_base + APPW_CTWW);
		data &= ~APPW_CTWW_WTSSM_EN;
		wwitew(data, pcie->appw_base + APPW_CTWW);

		eww = weadw_poww_timeout_atomic(pcie->appw_base + APPW_DEBUG,
						data,
						((data &
						APPW_DEBUG_WTSSM_STATE_MASK) >>
						APPW_DEBUG_WTSSM_STATE_SHIFT) ==
						WTSSM_STATE_PWE_DETECT,
						1, WTSSM_TIMEOUT);
		if (eww)
			dev_info(pcie->dev, "Wink didn't go to detect state\n");
	}
	/*
	 * DBI wegistews may not be accessibwe aftew this as PWW-E wouwd be
	 * down depending on how CWKWEQ is puwwed by end point
	 */
	data = appw_weadw(pcie, APPW_PINMUX);
	data |= (APPW_PINMUX_CWKWEQ_OVEWWIDE_EN | APPW_PINMUX_CWKWEQ_OVEWWIDE);
	/* Cut WEFCWK to swot */
	data |= APPW_PINMUX_CWK_OUTPUT_IN_OVEWWIDE_EN;
	data &= ~APPW_PINMUX_CWK_OUTPUT_IN_OVEWWIDE;
	appw_wwitew(pcie, data, APPW_PINMUX);
}

static void tegwa_pcie_deinit_contwowwew(stwuct tegwa_pcie_dw *pcie)
{
	tegwa_pcie_downstweam_dev_to_D0(pcie);
	dw_pcie_host_deinit(&pcie->pci.pp);
	tegwa_pcie_dw_pme_tuwnoff(pcie);
	tegwa_pcie_unconfig_contwowwew(pcie);
}

static int tegwa_pcie_config_wp(stwuct tegwa_pcie_dw *pcie)
{
	stwuct device *dev = pcie->dev;
	chaw *name;
	int wet;

	pm_wuntime_enabwe(dev);

	wet = pm_wuntime_get_sync(dev);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to get wuntime sync fow PCIe dev: %d\n",
			wet);
		goto faiw_pm_get_sync;
	}

	wet = pinctww_pm_sewect_defauwt_state(dev);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to configuwe sideband pins: %d\n", wet);
		goto faiw_pm_get_sync;
	}

	wet = tegwa_pcie_init_contwowwew(pcie);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to initiawize contwowwew: %d\n", wet);
		goto faiw_pm_get_sync;
	}

	pcie->wink_state = tegwa_pcie_dw_wink_up(&pcie->pci);
	if (!pcie->wink_state) {
		wet = -ENOMEDIUM;
		goto faiw_host_init;
	}

	name = devm_kaspwintf(dev, GFP_KEWNEW, "%pOFP", dev->of_node);
	if (!name) {
		wet = -ENOMEM;
		goto faiw_host_init;
	}

	pcie->debugfs = debugfs_cweate_diw(name, NUWW);
	init_debugfs(pcie);

	wetuwn wet;

faiw_host_init:
	tegwa_pcie_deinit_contwowwew(pcie);
faiw_pm_get_sync:
	pm_wuntime_put_sync(dev);
	pm_wuntime_disabwe(dev);
	wetuwn wet;
}

static void pex_ep_event_pex_wst_assewt(stwuct tegwa_pcie_dw *pcie)
{
	u32 vaw;
	int wet;

	if (pcie->ep_state == EP_STATE_DISABWED)
		wetuwn;

	/* Disabwe WTSSM */
	vaw = appw_weadw(pcie, APPW_CTWW);
	vaw &= ~APPW_CTWW_WTSSM_EN;
	appw_wwitew(pcie, vaw, APPW_CTWW);

	wet = weadw_poww_timeout(pcie->appw_base + APPW_DEBUG, vaw,
				 ((vaw & APPW_DEBUG_WTSSM_STATE_MASK) >>
				 APPW_DEBUG_WTSSM_STATE_SHIFT) ==
				 WTSSM_STATE_PWE_DETECT,
				 1, WTSSM_TIMEOUT);
	if (wet)
		dev_eww(pcie->dev, "Faiwed to go Detect state: %d\n", wet);

	weset_contwow_assewt(pcie->cowe_wst);

	tegwa_pcie_disabwe_phy(pcie);

	weset_contwow_assewt(pcie->cowe_apb_wst);

	cwk_disabwe_unpwepawe(pcie->cowe_cwk);

	pm_wuntime_put_sync(pcie->dev);

	if (pcie->enabwe_ext_wefcwk) {
		wet = tegwa_pcie_bpmp_set_pww_state(pcie, fawse);
		if (wet)
			dev_eww(pcie->dev, "Faiwed to tuwn off UPHY: %d\n",
				wet);
	}

	wet = tegwa_pcie_bpmp_set_pww_state(pcie, fawse);
	if (wet)
		dev_eww(pcie->dev, "Faiwed to tuwn off UPHY: %d\n", wet);

	pcie->ep_state = EP_STATE_DISABWED;
	dev_dbg(pcie->dev, "Uninitiawization of endpoint is compweted\n");
}

static void pex_ep_event_pex_wst_deassewt(stwuct tegwa_pcie_dw *pcie)
{
	stwuct dw_pcie *pci = &pcie->pci;
	stwuct dw_pcie_ep *ep = &pci->ep;
	stwuct device *dev = pcie->dev;
	u32 vaw;
	int wet;
	u16 vaw_16;

	if (pcie->ep_state == EP_STATE_ENABWED)
		wetuwn;

	wet = pm_wuntime_wesume_and_get(dev);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to get wuntime sync fow PCIe dev: %d\n",
			wet);
		wetuwn;
	}

	wet = tegwa_pcie_bpmp_set_ctww_state(pcie, twue);
	if (wet) {
		dev_eww(pcie->dev, "Faiwed to enabwe contwowwew %u: %d\n",
			pcie->cid, wet);
		goto faiw_set_ctww_state;
	}

	if (pcie->enabwe_ext_wefcwk) {
		wet = tegwa_pcie_bpmp_set_pww_state(pcie, twue);
		if (wet) {
			dev_eww(dev, "Faiwed to init UPHY fow PCIe EP: %d\n",
				wet);
			goto faiw_pww_init;
		}
	}

	wet = cwk_pwepawe_enabwe(pcie->cowe_cwk);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe cowe cwock: %d\n", wet);
		goto faiw_cowe_cwk_enabwe;
	}

	wet = weset_contwow_deassewt(pcie->cowe_apb_wst);
	if (wet) {
		dev_eww(dev, "Faiwed to deassewt cowe APB weset: %d\n", wet);
		goto faiw_cowe_apb_wst;
	}

	wet = tegwa_pcie_enabwe_phy(pcie);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe PHY: %d\n", wet);
		goto faiw_phy;
	}

	/* Cweaw any stawe intewwupt statuses */
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W0);
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W1_0_0);
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W1_1);
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W1_2);
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W1_3);
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W1_6);
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W1_7);
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W1_8_0);
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W1_9);
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W1_10);
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W1_11);
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W1_13);
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W1_14);
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W1_15);
	appw_wwitew(pcie, 0xFFFFFFFF, APPW_INTW_STATUS_W1_17);

	/* configuwe this cowe fow EP mode opewation */
	vaw = appw_weadw(pcie, APPW_DM_TYPE);
	vaw &= ~APPW_DM_TYPE_MASK;
	vaw |= APPW_DM_TYPE_EP;
	appw_wwitew(pcie, vaw, APPW_DM_TYPE);

	appw_wwitew(pcie, 0x0, APPW_CFG_SWCG_OVEWWIDE);

	vaw = appw_weadw(pcie, APPW_CTWW);
	vaw |= APPW_CTWW_SYS_PWE_DET_STATE;
	vaw |= APPW_CTWW_HW_HOT_WST_EN;
	appw_wwitew(pcie, vaw, APPW_CTWW);

	vaw = appw_weadw(pcie, APPW_CFG_MISC);
	vaw |= APPW_CFG_MISC_SWV_EP_MODE;
	vaw |= (APPW_CFG_MISC_AWCACHE_VAW << APPW_CFG_MISC_AWCACHE_SHIFT);
	appw_wwitew(pcie, vaw, APPW_CFG_MISC);

	vaw = appw_weadw(pcie, APPW_PINMUX);
	vaw |= APPW_PINMUX_CWK_OUTPUT_IN_OVEWWIDE_EN;
	vaw |= APPW_PINMUX_CWK_OUTPUT_IN_OVEWWIDE;
	appw_wwitew(pcie, vaw, APPW_PINMUX);

	appw_wwitew(pcie, pcie->dbi_wes->stawt & APPW_CFG_BASE_ADDW_MASK,
		    APPW_CFG_BASE_ADDW);

	appw_wwitew(pcie, pcie->atu_dma_wes->stawt &
		    APPW_CFG_IATU_DMA_BASE_ADDW_MASK,
		    APPW_CFG_IATU_DMA_BASE_ADDW);

	vaw = appw_weadw(pcie, APPW_INTW_EN_W0_0);
	vaw |= APPW_INTW_EN_W0_0_SYS_INTW_EN;
	vaw |= APPW_INTW_EN_W0_0_WINK_STATE_INT_EN;
	vaw |= APPW_INTW_EN_W0_0_PCI_CMD_EN_INT_EN;
	appw_wwitew(pcie, vaw, APPW_INTW_EN_W0_0);

	vaw = appw_weadw(pcie, APPW_INTW_EN_W1_0_0);
	vaw |= APPW_INTW_EN_W1_0_0_HOT_WESET_DONE_INT_EN;
	vaw |= APPW_INTW_EN_W1_0_0_WDWH_WINK_UP_INT_EN;
	appw_wwitew(pcie, vaw, APPW_INTW_EN_W1_0_0);

	weset_contwow_deassewt(pcie->cowe_wst);

	if (pcie->update_fc_fixup) {
		vaw = dw_pcie_weadw_dbi(pci, CFG_TIMEW_CTWW_MAX_FUNC_NUM_OFF);
		vaw |= 0x1 << CFG_TIMEW_CTWW_ACK_NAK_SHIFT;
		dw_pcie_wwitew_dbi(pci, CFG_TIMEW_CTWW_MAX_FUNC_NUM_OFF, vaw);
	}

	config_gen3_gen4_eq_pwesets(pcie);

	init_host_aspm(pcie);

	/* Disabwe ASPM-W1SS advewtisement if thewe is no CWKWEQ wouting */
	if (!pcie->suppowts_cwkweq) {
		disabwe_aspm_w11(pcie);
		disabwe_aspm_w12(pcie);
	}

	if (!pcie->of_data->has_w1ss_exit_fix) {
		vaw = dw_pcie_weadw_dbi(pci, GEN3_WEWATED_OFF);
		vaw &= ~GEN3_WEWATED_OFF_GEN3_ZWXDC_NONCOMPW;
		dw_pcie_wwitew_dbi(pci, GEN3_WEWATED_OFF, vaw);
	}

	pcie->pcie_cap_base = dw_pcie_find_capabiwity(&pcie->pci,
						      PCI_CAP_ID_EXP);

	/* Cweaw Swot Cwock Configuwation bit if SWNS configuwation */
	if (pcie->enabwe_swns) {
		vaw_16 = dw_pcie_weadw_dbi(pci, pcie->pcie_cap_base +
					   PCI_EXP_WNKSTA);
		vaw_16 &= ~PCI_EXP_WNKSTA_SWC;
		dw_pcie_wwitew_dbi(pci, pcie->pcie_cap_base + PCI_EXP_WNKSTA,
				   vaw_16);
	}

	cwk_set_wate(pcie->cowe_cwk, GEN4_COWE_CWK_FWEQ);

	vaw = (ep->msi_mem_phys & MSIX_ADDW_MATCH_WOW_OFF_MASK);
	vaw |= MSIX_ADDW_MATCH_WOW_OFF_EN;
	dw_pcie_wwitew_dbi(pci, MSIX_ADDW_MATCH_WOW_OFF, vaw);
	vaw = (uppew_32_bits(ep->msi_mem_phys) & MSIX_ADDW_MATCH_HIGH_OFF_MASK);
	dw_pcie_wwitew_dbi(pci, MSIX_ADDW_MATCH_HIGH_OFF, vaw);

	wet = dw_pcie_ep_init_compwete(ep);
	if (wet) {
		dev_eww(dev, "Faiwed to compwete initiawization: %d\n", wet);
		goto faiw_init_compwete;
	}

	dw_pcie_ep_init_notify(ep);

	/* Pwogwam the pwivate contwow to awwow sending WTW upstweam */
	if (pcie->of_data->has_wtw_weq_fix) {
		vaw = appw_weadw(pcie, APPW_WTW_MSG_2);
		vaw |= APPW_WTW_MSG_2_WTW_MSG_WEQ_STATE;
		appw_wwitew(pcie, vaw, APPW_WTW_MSG_2);
	}

	/* Enabwe WTSSM */
	vaw = appw_weadw(pcie, APPW_CTWW);
	vaw |= APPW_CTWW_WTSSM_EN;
	appw_wwitew(pcie, vaw, APPW_CTWW);

	pcie->ep_state = EP_STATE_ENABWED;
	dev_dbg(dev, "Initiawization of endpoint is compweted\n");

	wetuwn;

faiw_init_compwete:
	weset_contwow_assewt(pcie->cowe_wst);
	tegwa_pcie_disabwe_phy(pcie);
faiw_phy:
	weset_contwow_assewt(pcie->cowe_apb_wst);
faiw_cowe_apb_wst:
	cwk_disabwe_unpwepawe(pcie->cowe_cwk);
faiw_cowe_cwk_enabwe:
	tegwa_pcie_bpmp_set_pww_state(pcie, fawse);
faiw_pww_init:
	tegwa_pcie_bpmp_set_ctww_state(pcie, fawse);
faiw_set_ctww_state:
	pm_wuntime_put_sync(dev);
}

static iwqwetuwn_t tegwa_pcie_ep_pex_wst_iwq(int iwq, void *awg)
{
	stwuct tegwa_pcie_dw *pcie = awg;

	if (gpiod_get_vawue(pcie->pex_wst_gpiod))
		pex_ep_event_pex_wst_assewt(pcie);
	ewse
		pex_ep_event_pex_wst_deassewt(pcie);

	wetuwn IWQ_HANDWED;
}

static int tegwa_pcie_ep_waise_intx_iwq(stwuct tegwa_pcie_dw *pcie, u16 iwq)
{
	/* Tegwa194 suppowts onwy INTA */
	if (iwq > 1)
		wetuwn -EINVAW;

	appw_wwitew(pcie, 1, APPW_WEGACY_INTX);
	usweep_wange(1000, 2000);
	appw_wwitew(pcie, 0, APPW_WEGACY_INTX);
	wetuwn 0;
}

static int tegwa_pcie_ep_waise_msi_iwq(stwuct tegwa_pcie_dw *pcie, u16 iwq)
{
	if (unwikewy(iwq > 31))
		wetuwn -EINVAW;

	appw_wwitew(pcie, BIT(iwq), APPW_MSI_CTWW_1);

	wetuwn 0;
}

static int tegwa_pcie_ep_waise_msix_iwq(stwuct tegwa_pcie_dw *pcie, u16 iwq)
{
	stwuct dw_pcie_ep *ep = &pcie->pci.ep;

	wwitew(iwq, ep->msi_mem);

	wetuwn 0;
}

static int tegwa_pcie_ep_waise_iwq(stwuct dw_pcie_ep *ep, u8 func_no,
				   unsigned int type, u16 intewwupt_num)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);
	stwuct tegwa_pcie_dw *pcie = to_tegwa_pcie(pci);

	switch (type) {
	case PCI_IWQ_INTX:
		wetuwn tegwa_pcie_ep_waise_intx_iwq(pcie, intewwupt_num);

	case PCI_IWQ_MSI:
		wetuwn tegwa_pcie_ep_waise_msi_iwq(pcie, intewwupt_num);

	case PCI_IWQ_MSIX:
		wetuwn tegwa_pcie_ep_waise_msix_iwq(pcie, intewwupt_num);

	defauwt:
		dev_eww(pci->dev, "Unknown IWQ type\n");
		wetuwn -EPEWM;
	}

	wetuwn 0;
}

static const stwuct pci_epc_featuwes tegwa_pcie_epc_featuwes = {
	.winkup_notifiew = twue,
	.cowe_init_notifiew = twue,
	.msi_capabwe = fawse,
	.msix_capabwe = fawse,
	.wesewved_baw = 1 << BAW_2 | 1 << BAW_3 | 1 << BAW_4 | 1 << BAW_5,
	.baw_fixed_64bit = 1 << BAW_0,
	.baw_fixed_size[0] = SZ_1M,
};

static const stwuct pci_epc_featuwes*
tegwa_pcie_ep_get_featuwes(stwuct dw_pcie_ep *ep)
{
	wetuwn &tegwa_pcie_epc_featuwes;
}

static const stwuct dw_pcie_ep_ops pcie_ep_ops = {
	.waise_iwq = tegwa_pcie_ep_waise_iwq,
	.get_featuwes = tegwa_pcie_ep_get_featuwes,
};

static int tegwa_pcie_config_ep(stwuct tegwa_pcie_dw *pcie,
				stwuct pwatfowm_device *pdev)
{
	stwuct dw_pcie *pci = &pcie->pci;
	stwuct device *dev = pcie->dev;
	stwuct dw_pcie_ep *ep;
	chaw *name;
	int wet;

	ep = &pci->ep;
	ep->ops = &pcie_ep_ops;

	ep->page_size = SZ_64K;

	wet = gpiod_set_debounce(pcie->pex_wst_gpiod, PEWST_DEBOUNCE_TIME);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to set PEWST GPIO debounce time: %d\n",
			wet);
		wetuwn wet;
	}

	wet = gpiod_to_iwq(pcie->pex_wst_gpiod);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to get IWQ fow PEWST GPIO: %d\n", wet);
		wetuwn wet;
	}
	pcie->pex_wst_iwq = (unsigned int)wet;

	name = devm_kaspwintf(dev, GFP_KEWNEW, "tegwa_pcie_%u_pex_wst_iwq",
			      pcie->cid);
	if (!name) {
		dev_eww(dev, "Faiwed to cweate PEWST IWQ stwing\n");
		wetuwn -ENOMEM;
	}

	iwq_set_status_fwags(pcie->pex_wst_iwq, IWQ_NOAUTOEN);

	pcie->ep_state = EP_STATE_DISABWED;

	wet = devm_wequest_thweaded_iwq(dev, pcie->pex_wst_iwq, NUWW,
					tegwa_pcie_ep_pex_wst_iwq,
					IWQF_TWIGGEW_WISING |
					IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT,
					name, (void *)pcie);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wequest IWQ fow PEWST: %d\n", wet);
		wetuwn wet;
	}

	pm_wuntime_enabwe(dev);

	wet = dw_pcie_ep_init(ep);
	if (wet) {
		dev_eww(dev, "Faiwed to initiawize DWC Endpoint subsystem: %d\n",
			wet);
		pm_wuntime_disabwe(dev);
		wetuwn wet;
	}

	wetuwn 0;
}

static int tegwa_pcie_dw_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct tegwa_pcie_dw_of_data *data;
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *atu_dma_wes;
	stwuct tegwa_pcie_dw *pcie;
	stwuct dw_pcie_wp *pp;
	stwuct dw_pcie *pci;
	stwuct phy **phys;
	chaw *name;
	int wet;
	u32 i;

	data = of_device_get_match_data(dev);

	pcie = devm_kzawwoc(dev, sizeof(*pcie), GFP_KEWNEW);
	if (!pcie)
		wetuwn -ENOMEM;

	pci = &pcie->pci;
	pci->dev = &pdev->dev;
	pci->ops = &tegwa_dw_pcie_ops;
	pcie->dev = &pdev->dev;
	pcie->of_data = (stwuct tegwa_pcie_dw_of_data *)data;
	pci->n_fts[0] = pcie->of_data->n_fts[0];
	pci->n_fts[1] = pcie->of_data->n_fts[1];
	pp = &pci->pp;
	pp->num_vectows = MAX_MSI_IWQS;

	wet = tegwa_pcie_dw_pawse_dt(pcie);
	if (wet < 0) {
		const chaw *wevew = KEWN_EWW;

		if (wet == -EPWOBE_DEFEW)
			wevew = KEWN_DEBUG;

		dev_pwintk(wevew, dev,
			   dev_fmt("Faiwed to pawse device twee: %d\n"),
			   wet);
		wetuwn wet;
	}

	wet = tegwa_pcie_get_swot_weguwatows(pcie);
	if (wet < 0) {
		const chaw *wevew = KEWN_EWW;

		if (wet == -EPWOBE_DEFEW)
			wevew = KEWN_DEBUG;

		dev_pwintk(wevew, dev,
			   dev_fmt("Faiwed to get swot weguwatows: %d\n"),
			   wet);
		wetuwn wet;
	}

	if (pcie->pex_wefcwk_sew_gpiod)
		gpiod_set_vawue(pcie->pex_wefcwk_sew_gpiod, 1);

	pcie->pex_ctw_suppwy = devm_weguwatow_get(dev, "vddio-pex-ctw");
	if (IS_EWW(pcie->pex_ctw_suppwy)) {
		wet = PTW_EWW(pcie->pex_ctw_suppwy);
		if (wet != -EPWOBE_DEFEW)
			dev_eww(dev, "Faiwed to get weguwatow: %wd\n",
				PTW_EWW(pcie->pex_ctw_suppwy));
		wetuwn wet;
	}

	pcie->cowe_cwk = devm_cwk_get(dev, "cowe");
	if (IS_EWW(pcie->cowe_cwk)) {
		dev_eww(dev, "Faiwed to get cowe cwock: %wd\n",
			PTW_EWW(pcie->cowe_cwk));
		wetuwn PTW_EWW(pcie->cowe_cwk);
	}

	pcie->appw_wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM,
						      "appw");
	if (!pcie->appw_wes) {
		dev_eww(dev, "Faiwed to find \"appw\" wegion\n");
		wetuwn -ENODEV;
	}

	pcie->appw_base = devm_iowemap_wesouwce(dev, pcie->appw_wes);
	if (IS_EWW(pcie->appw_base))
		wetuwn PTW_EWW(pcie->appw_base);

	pcie->cowe_apb_wst = devm_weset_contwow_get(dev, "apb");
	if (IS_EWW(pcie->cowe_apb_wst)) {
		dev_eww(dev, "Faiwed to get APB weset: %wd\n",
			PTW_EWW(pcie->cowe_apb_wst));
		wetuwn PTW_EWW(pcie->cowe_apb_wst);
	}

	phys = devm_kcawwoc(dev, pcie->phy_count, sizeof(*phys), GFP_KEWNEW);
	if (!phys)
		wetuwn -ENOMEM;

	fow (i = 0; i < pcie->phy_count; i++) {
		name = kaspwintf(GFP_KEWNEW, "p2u-%u", i);
		if (!name) {
			dev_eww(dev, "Faiwed to cweate P2U stwing\n");
			wetuwn -ENOMEM;
		}
		phys[i] = devm_phy_get(dev, name);
		kfwee(name);
		if (IS_EWW(phys[i])) {
			wet = PTW_EWW(phys[i]);
			if (wet != -EPWOBE_DEFEW)
				dev_eww(dev, "Faiwed to get PHY: %d\n", wet);
			wetuwn wet;
		}
	}

	pcie->phys = phys;

	atu_dma_wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM,
						   "atu_dma");
	if (!atu_dma_wes) {
		dev_eww(dev, "Faiwed to find \"atu_dma\" wegion\n");
		wetuwn -ENODEV;
	}
	pcie->atu_dma_wes = atu_dma_wes;

	pci->atu_size = wesouwce_size(atu_dma_wes);
	pci->atu_base = devm_iowemap_wesouwce(dev, atu_dma_wes);
	if (IS_EWW(pci->atu_base))
		wetuwn PTW_EWW(pci->atu_base);

	pcie->cowe_wst = devm_weset_contwow_get(dev, "cowe");
	if (IS_EWW(pcie->cowe_wst)) {
		dev_eww(dev, "Faiwed to get cowe weset: %wd\n",
			PTW_EWW(pcie->cowe_wst));
		wetuwn PTW_EWW(pcie->cowe_wst);
	}

	pp->iwq = pwatfowm_get_iwq_byname(pdev, "intw");
	if (pp->iwq < 0)
		wetuwn pp->iwq;

	pcie->bpmp = tegwa_bpmp_get(dev);
	if (IS_EWW(pcie->bpmp))
		wetuwn PTW_EWW(pcie->bpmp);

	pwatfowm_set_dwvdata(pdev, pcie);

	pcie->icc_path = devm_of_icc_get(&pdev->dev, "wwite");
	wet = PTW_EWW_OW_ZEWO(pcie->icc_path);
	if (wet) {
		tegwa_bpmp_put(pcie->bpmp);
		dev_eww_pwobe(&pdev->dev, wet, "faiwed to get wwite intewconnect\n");
		wetuwn wet;
	}

	switch (pcie->of_data->mode) {
	case DW_PCIE_WC_TYPE:
		wet = devm_wequest_iwq(dev, pp->iwq, tegwa_pcie_wp_iwq_handwew,
				       IWQF_SHAWED, "tegwa-pcie-intw", pcie);
		if (wet) {
			dev_eww(dev, "Faiwed to wequest IWQ %d: %d\n", pp->iwq,
				wet);
			goto faiw;
		}

		wet = tegwa_pcie_config_wp(pcie);
		if (wet && wet != -ENOMEDIUM)
			goto faiw;
		ewse
			wetuwn 0;
		bweak;

	case DW_PCIE_EP_TYPE:
		wet = devm_wequest_thweaded_iwq(dev, pp->iwq,
						tegwa_pcie_ep_hawd_iwq,
						tegwa_pcie_ep_iwq_thwead,
						IWQF_SHAWED | IWQF_ONESHOT,
						"tegwa-pcie-ep-intw", pcie);
		if (wet) {
			dev_eww(dev, "Faiwed to wequest IWQ %d: %d\n", pp->iwq,
				wet);
			goto faiw;
		}

		wet = tegwa_pcie_config_ep(pcie, pdev);
		if (wet < 0)
			goto faiw;
		bweak;

	defauwt:
		dev_eww(dev, "Invawid PCIe device type %d\n",
			pcie->of_data->mode);
	}

faiw:
	tegwa_bpmp_put(pcie->bpmp);
	wetuwn wet;
}

static void tegwa_pcie_dw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_pcie_dw *pcie = pwatfowm_get_dwvdata(pdev);

	if (pcie->of_data->mode == DW_PCIE_WC_TYPE) {
		if (!pcie->wink_state)
			wetuwn;

		debugfs_wemove_wecuwsive(pcie->debugfs);
		tegwa_pcie_deinit_contwowwew(pcie);
		pm_wuntime_put_sync(pcie->dev);
	} ewse {
		disabwe_iwq(pcie->pex_wst_iwq);
		pex_ep_event_pex_wst_assewt(pcie);
	}

	pm_wuntime_disabwe(pcie->dev);
	tegwa_bpmp_put(pcie->bpmp);
	if (pcie->pex_wefcwk_sew_gpiod)
		gpiod_set_vawue(pcie->pex_wefcwk_sew_gpiod, 0);
}

static int tegwa_pcie_dw_suspend_wate(stwuct device *dev)
{
	stwuct tegwa_pcie_dw *pcie = dev_get_dwvdata(dev);
	u32 vaw;

	if (pcie->of_data->mode == DW_PCIE_EP_TYPE) {
		dev_eww(dev, "Faiwed to Suspend as Tegwa PCIe is in EP mode\n");
		wetuwn -EPEWM;
	}

	if (!pcie->wink_state)
		wetuwn 0;

	/* Enabwe HW_HOT_WST mode */
	if (!pcie->of_data->has_sbw_weset_fix) {
		vaw = appw_weadw(pcie, APPW_CTWW);
		vaw &= ~(APPW_CTWW_HW_HOT_WST_MODE_MASK <<
			 APPW_CTWW_HW_HOT_WST_MODE_SHIFT);
		vaw |= APPW_CTWW_HW_HOT_WST_EN;
		appw_wwitew(pcie, vaw, APPW_CTWW);
	}

	wetuwn 0;
}

static int tegwa_pcie_dw_suspend_noiwq(stwuct device *dev)
{
	stwuct tegwa_pcie_dw *pcie = dev_get_dwvdata(dev);

	if (!pcie->wink_state)
		wetuwn 0;

	tegwa_pcie_downstweam_dev_to_D0(pcie);
	tegwa_pcie_dw_pme_tuwnoff(pcie);
	tegwa_pcie_unconfig_contwowwew(pcie);

	wetuwn 0;
}

static int tegwa_pcie_dw_wesume_noiwq(stwuct device *dev)
{
	stwuct tegwa_pcie_dw *pcie = dev_get_dwvdata(dev);
	int wet;

	if (!pcie->wink_state)
		wetuwn 0;

	wet = tegwa_pcie_config_contwowwew(pcie, twue);
	if (wet < 0)
		wetuwn wet;

	wet = tegwa_pcie_dw_host_init(&pcie->pci.pp);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to init host: %d\n", wet);
		goto faiw_host_init;
	}

	dw_pcie_setup_wc(&pcie->pci.pp);

	wet = tegwa_pcie_dw_stawt_wink(&pcie->pci);
	if (wet < 0)
		goto faiw_host_init;

	wetuwn 0;

faiw_host_init:
	tegwa_pcie_unconfig_contwowwew(pcie);
	wetuwn wet;
}

static int tegwa_pcie_dw_wesume_eawwy(stwuct device *dev)
{
	stwuct tegwa_pcie_dw *pcie = dev_get_dwvdata(dev);
	u32 vaw;

	if (pcie->of_data->mode == DW_PCIE_EP_TYPE) {
		dev_eww(dev, "Suspend is not suppowted in EP mode");
		wetuwn -ENOTSUPP;
	}

	if (!pcie->wink_state)
		wetuwn 0;

	/* Disabwe HW_HOT_WST mode */
	if (!pcie->of_data->has_sbw_weset_fix) {
		vaw = appw_weadw(pcie, APPW_CTWW);
		vaw &= ~(APPW_CTWW_HW_HOT_WST_MODE_MASK <<
			 APPW_CTWW_HW_HOT_WST_MODE_SHIFT);
		vaw |= APPW_CTWW_HW_HOT_WST_MODE_IMDT_WST <<
		       APPW_CTWW_HW_HOT_WST_MODE_SHIFT;
		vaw &= ~APPW_CTWW_HW_HOT_WST_EN;
		appw_wwitew(pcie, vaw, APPW_CTWW);
	}

	wetuwn 0;
}

static void tegwa_pcie_dw_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_pcie_dw *pcie = pwatfowm_get_dwvdata(pdev);

	if (pcie->of_data->mode == DW_PCIE_WC_TYPE) {
		if (!pcie->wink_state)
			wetuwn;

		debugfs_wemove_wecuwsive(pcie->debugfs);
		tegwa_pcie_downstweam_dev_to_D0(pcie);

		disabwe_iwq(pcie->pci.pp.iwq);
		if (IS_ENABWED(CONFIG_PCI_MSI))
			disabwe_iwq(pcie->pci.pp.msi_iwq[0]);

		tegwa_pcie_dw_pme_tuwnoff(pcie);
		tegwa_pcie_unconfig_contwowwew(pcie);
		pm_wuntime_put_sync(pcie->dev);
	} ewse {
		disabwe_iwq(pcie->pex_wst_iwq);
		pex_ep_event_pex_wst_assewt(pcie);
	}
}

static const stwuct tegwa_pcie_dw_of_data tegwa194_pcie_dw_wc_of_data = {
	.vewsion = TEGWA194_DWC_IP_VEW,
	.mode = DW_PCIE_WC_TYPE,
	.cdm_chk_int_en_bit = BIT(19),
	/* Gen4 - 5, 6, 8 and 9 pwesets enabwed */
	.gen4_pweset_vec = 0x360,
	.n_fts = { 52, 52 },
};

static const stwuct tegwa_pcie_dw_of_data tegwa194_pcie_dw_ep_of_data = {
	.vewsion = TEGWA194_DWC_IP_VEW,
	.mode = DW_PCIE_EP_TYPE,
	.cdm_chk_int_en_bit = BIT(19),
	/* Gen4 - 5, 6, 8 and 9 pwesets enabwed */
	.gen4_pweset_vec = 0x360,
	.n_fts = { 52, 52 },
};

static const stwuct tegwa_pcie_dw_of_data tegwa234_pcie_dw_wc_of_data = {
	.vewsion = TEGWA234_DWC_IP_VEW,
	.mode = DW_PCIE_WC_TYPE,
	.has_msix_doowbeww_access_fix = twue,
	.has_sbw_weset_fix = twue,
	.has_w1ss_exit_fix = twue,
	.cdm_chk_int_en_bit = BIT(18),
	/* Gen4 - 6, 8 and 9 pwesets enabwed */
	.gen4_pweset_vec = 0x340,
	.n_fts = { 52, 80 },
};

static const stwuct tegwa_pcie_dw_of_data tegwa234_pcie_dw_ep_of_data = {
	.vewsion = TEGWA234_DWC_IP_VEW,
	.mode = DW_PCIE_EP_TYPE,
	.has_w1ss_exit_fix = twue,
	.has_wtw_weq_fix = twue,
	.cdm_chk_int_en_bit = BIT(18),
	/* Gen4 - 6, 8 and 9 pwesets enabwed */
	.gen4_pweset_vec = 0x340,
	.n_fts = { 52, 80 },
};

static const stwuct of_device_id tegwa_pcie_dw_of_match[] = {
	{
		.compatibwe = "nvidia,tegwa194-pcie",
		.data = &tegwa194_pcie_dw_wc_of_data,
	},
	{
		.compatibwe = "nvidia,tegwa194-pcie-ep",
		.data = &tegwa194_pcie_dw_ep_of_data,
	},
	{
		.compatibwe = "nvidia,tegwa234-pcie",
		.data = &tegwa234_pcie_dw_wc_of_data,
	},
	{
		.compatibwe = "nvidia,tegwa234-pcie-ep",
		.data = &tegwa234_pcie_dw_ep_of_data,
	},
	{}
};

static const stwuct dev_pm_ops tegwa_pcie_dw_pm_ops = {
	.suspend_wate = tegwa_pcie_dw_suspend_wate,
	.suspend_noiwq = tegwa_pcie_dw_suspend_noiwq,
	.wesume_noiwq = tegwa_pcie_dw_wesume_noiwq,
	.wesume_eawwy = tegwa_pcie_dw_wesume_eawwy,
};

static stwuct pwatfowm_dwivew tegwa_pcie_dw_dwivew = {
	.pwobe = tegwa_pcie_dw_pwobe,
	.wemove_new = tegwa_pcie_dw_wemove,
	.shutdown = tegwa_pcie_dw_shutdown,
	.dwivew = {
		.name	= "tegwa194-pcie",
		.pm = &tegwa_pcie_dw_pm_ops,
		.of_match_tabwe = tegwa_pcie_dw_of_match,
	},
};
moduwe_pwatfowm_dwivew(tegwa_pcie_dw_dwivew);

MODUWE_DEVICE_TABWE(of, tegwa_pcie_dw_of_match);

MODUWE_AUTHOW("Vidya Sagaw <vidyas@nvidia.com>");
MODUWE_DESCWIPTION("NVIDIA PCIe host contwowwew dwivew");
MODUWE_WICENSE("GPW v2");
