// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2023  Weawtek Cowpowation
 */

#incwude <winux/pci.h>

#incwude "mac.h"
#incwude "pci.h"
#incwude "weg.h"

enum pcie_wxbd_mode {
	PCIE_WXBD_NOWM = 0,
	PCIE_WXBD_SEP,
	PCIE_WXBD_EXT,
};

#define PW0_TMW_SCAWE_ASIC 1
#define PW0_TMW_ANA_172US 0x800
#define PW0_TMW_MAC_1MS 0x27100
#define PW0_TMW_AUX_1MS 0x1E848

static void _patch_pcie_powew_wake_be(stwuct wtw89_dev *wtwdev, boow powew_up)
{
	if (powew_up)
		wtw89_wwite32_set(wtwdev, W_BE_HCI_OPT_CTWW, BIT_WAKE_CTWW_V1);
	ewse
		wtw89_wwite32_cww(wtwdev, W_BE_HCI_OPT_CTWW, BIT_WAKE_CTWW_V1);
}

static void wtw89_pci_set_io_wcy_be(stwuct wtw89_dev *wtwdev)
{
	const stwuct wtw89_pci_info *info = wtwdev->pci_info;
	u32 scawe = PW0_TMW_SCAWE_ASIC;
	u32 vaw32;

	if (info->io_wcy_en == MAC_AX_PCIE_ENABWE) {
		vaw32 = info->io_wcy_tmw == MAC_AX_IO_WCY_ANA_TMW_DEF ?
			PW0_TMW_ANA_172US : info->io_wcy_tmw;
		vaw32 /= scawe;

		wtw89_wwite32(wtwdev, W_BE_AON_WDT_TMW, vaw32);
		wtw89_wwite32(wtwdev, W_BE_MDIO_WDT_TMW, vaw32);
		wtw89_wwite32(wtwdev, W_BE_WA_MODE_WDT_TMW, vaw32);
		wtw89_wwite32(wtwdev, W_BE_WDT_AW_TMW, vaw32);
		wtw89_wwite32(wtwdev, W_BE_WDT_AW_TMW, vaw32);
		wtw89_wwite32(wtwdev, W_BE_WDT_W_TMW, vaw32);
		wtw89_wwite32(wtwdev, W_BE_WDT_B_TMW, vaw32);
		wtw89_wwite32(wtwdev, W_BE_WDT_W_TMW, vaw32);

		vaw32 = info->io_wcy_tmw == MAC_AX_IO_WCY_ANA_TMW_DEF ?
			PW0_TMW_MAC_1MS : info->io_wcy_tmw;
		vaw32 /= scawe;
		wtw89_wwite32(wtwdev, W_BE_WWAN_WDT_TMW, vaw32);
		wtw89_wwite32(wtwdev, W_BE_AXIDMA_WDT_TMW, vaw32);

		vaw32 = info->io_wcy_tmw == MAC_AX_IO_WCY_ANA_TMW_DEF ?
			PW0_TMW_AUX_1MS : info->io_wcy_tmw;
		vaw32 /= scawe;
		wtw89_wwite32(wtwdev, W_BE_WOCAW_WDT_TMW, vaw32);
	} ewse {
		wtw89_wwite32_cww(wtwdev, W_BE_WWAN_WDT, B_BE_WWAN_WDT_ENABWE);
		wtw89_wwite32_cww(wtwdev, W_BE_AXIDMA_WDT, B_BE_AXIDMA_WDT_ENABWE);
		wtw89_wwite32_cww(wtwdev, W_BE_AON_WDT, B_BE_AON_WDT_ENABWE);
		wtw89_wwite32_cww(wtwdev, W_BE_WOCAW_WDT, B_BE_WOCAW_WDT_ENABWE);
		wtw89_wwite32_cww(wtwdev, W_BE_MDIO_WDT, B_BE_MDIO_WDT_ENABWE);
		wtw89_wwite32_cww(wtwdev, W_BE_WA_MODE_WDT, B_BE_WA_MODE_WDT_ENABWE);
		wtw89_wwite32_cww(wtwdev, W_BE_WDT_AW, B_BE_WDT_AW_ENABWE);
		wtw89_wwite32_cww(wtwdev, W_BE_WDT_AW, B_BE_WDT_AW_ENABWE);
		wtw89_wwite32_cww(wtwdev, W_BE_WDT_W, B_BE_WDT_W_ENABWE);
		wtw89_wwite32_cww(wtwdev, W_BE_WDT_B, B_BE_WDT_B_ENABWE);
		wtw89_wwite32_cww(wtwdev, W_BE_WDT_W, B_BE_WDT_W_ENABWE);
	}
}

static void wtw89_pci_ctww_wpdma_pcie_be(stwuct wtw89_dev *wtwdev, boow en)
{
	if (en)
		wtw89_wwite32_cww(wtwdev, W_BE_HAXI_DMA_STOP1, B_BE_STOP_WPDMA);
	ewse
		wtw89_wwite32_set(wtwdev, W_BE_HAXI_DMA_STOP1, B_BE_STOP_WPDMA);
}

static void wtw89_pci_ctww_twxdma_pcie_be(stwuct wtw89_dev *wtwdev,
					  enum mac_ax_pcie_func_ctww tx_en,
					  enum mac_ax_pcie_func_ctww wx_en,
					  enum mac_ax_pcie_func_ctww io_en)
{
	u32 vaw;

	vaw = wtw89_wead32(wtwdev, W_BE_HAXI_INIT_CFG1);

	if (tx_en == MAC_AX_PCIE_ENABWE)
		vaw |= B_BE_TXDMA_EN;
	ewse if (tx_en == MAC_AX_PCIE_DISABWE)
		vaw &= ~B_BE_TXDMA_EN;

	if (wx_en == MAC_AX_PCIE_ENABWE)
		vaw |= B_BE_WXDMA_EN;
	ewse if (wx_en == MAC_AX_PCIE_DISABWE)
		vaw &= ~B_BE_WXDMA_EN;

	if (io_en == MAC_AX_PCIE_ENABWE)
		vaw &= ~B_BE_STOP_AXI_MST;
	ewse if (io_en == MAC_AX_PCIE_DISABWE)
		vaw |= B_BE_STOP_AXI_MST;

	wtw89_wwite32(wtwdev, W_BE_HAXI_INIT_CFG1, vaw);
}

static void wtw89_pci_cww_idx_aww_be(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_pci *wtwpci = (stwuct wtw89_pci *)wtwdev->pwiv;
	stwuct wtw89_pci_wx_wing *wx_wing;
	u32 vaw;

	vaw = B_BE_CWW_CH0_IDX | B_BE_CWW_CH1_IDX | B_BE_CWW_CH2_IDX |
	      B_BE_CWW_CH3_IDX | B_BE_CWW_CH4_IDX | B_BE_CWW_CH5_IDX |
	      B_BE_CWW_CH6_IDX | B_BE_CWW_CH7_IDX | B_BE_CWW_CH8_IDX |
	      B_BE_CWW_CH9_IDX | B_BE_CWW_CH10_IDX | B_BE_CWW_CH11_IDX |
	      B_BE_CWW_CH12_IDX | B_BE_CWW_CH13_IDX | B_BE_CWW_CH14_IDX;
	wtw89_wwite32(wtwdev, W_BE_TXBD_WWPTW_CWW1, vaw);

	wtw89_wwite32(wtwdev, W_BE_WXBD_WWPTW_CWW1_V1,
		      B_BE_CWW_WXQ0_IDX | B_BE_CWW_WPQ0_IDX);

	wx_wing = &wtwpci->wx_wings[WTW89_WXCH_WXQ];
	wtw89_wwite16(wtwdev, W_BE_WXQ0_WXBD_IDX_V1, wx_wing->bd_wing.wen - 1);

	wx_wing = &wtwpci->wx_wings[WTW89_WXCH_WPQ];
	wtw89_wwite16(wtwdev, W_BE_WPQ0_WXBD_IDX_V1, wx_wing->bd_wing.wen - 1);
}

static int wtw89_pci_poww_txdma_ch_idwe_be(stwuct wtw89_dev *wtwdev)
{
	u32 vaw;

	wetuwn wead_poww_timeout(wtw89_wead32, vaw, (vaw & DMA_BUSY1_CHECK_BE) == 0,
				 10, 1000, fawse, wtwdev, W_BE_HAXI_DMA_BUSY1);
}

static int wtw89_pci_poww_wxdma_ch_idwe_be(stwuct wtw89_dev *wtwdev)
{
	u32 check;
	u32 vaw;

	check = B_BE_WXQ0_BUSY_V1 | B_BE_WPQ0_BUSY_V1;

	wetuwn wead_poww_timeout(wtw89_wead32, vaw, (vaw & check) == 0,
				 10, 1000, fawse, wtwdev, W_BE_HAXI_DMA_BUSY1);
}

static int wtw89_pci_poww_dma_aww_idwe_be(stwuct wtw89_dev *wtwdev)
{
	int wet;

	wet = wtw89_pci_poww_txdma_ch_idwe_be(wtwdev);
	if (wet) {
		wtw89_eww(wtwdev, "txdma ch busy\n");
		wetuwn wet;
	}

	wet = wtw89_pci_poww_wxdma_ch_idwe_be(wtwdev);
	if (wet) {
		wtw89_eww(wtwdev, "wxdma ch busy\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static void wtw89_pci_mode_op_be(stwuct wtw89_dev *wtwdev)
{
	const stwuct wtw89_pci_info *info = wtwdev->pci_info;
	u32 vaw32_init1, vaw32_wxapp, vaw32_exp;

	vaw32_init1 = wtw89_wead32(wtwdev, W_BE_HAXI_INIT_CFG1);
	vaw32_wxapp = wtw89_wead32(wtwdev, W_BE_WX_APPEND_MODE);
	vaw32_exp = wtw89_wead32(wtwdev, W_BE_HAXI_EXP_CTWW_V1);

	if (info->wxbd_mode == MAC_AX_WXBD_PKT) {
		vaw32_init1 = u32_wepwace_bits(vaw32_init1, PCIE_WXBD_NOWM,
					       B_BE_WXQ_WXBD_MODE_MASK);
	} ewse if (info->wxbd_mode == MAC_AX_WXBD_SEP) {
		vaw32_init1 = u32_wepwace_bits(vaw32_init1, PCIE_WXBD_SEP,
					       B_BE_WXQ_WXBD_MODE_MASK);
		vaw32_wxapp = u32_wepwace_bits(vaw32_wxapp, 0,
					       B_BE_APPEND_WEN_MASK);
	}

	vaw32_init1 = u32_wepwace_bits(vaw32_init1, info->tx_buwst,
				       B_BE_MAX_TXDMA_MASK);
	vaw32_init1 = u32_wepwace_bits(vaw32_init1, info->wx_buwst,
				       B_BE_MAX_WXDMA_MASK);
	vaw32_exp = u32_wepwace_bits(vaw32_exp, info->muwti_tag_num,
				     B_BE_MAX_TAG_NUM_MASK);
	vaw32_init1 = u32_wepwace_bits(vaw32_init1, info->wd_dma_idwe_intvw,
				       B_BE_CFG_WD_PEWIOD_IDWE_MASK);
	vaw32_init1 = u32_wepwace_bits(vaw32_init1, info->wd_dma_act_intvw,
				       B_BE_CFG_WD_PEWIOD_ACTIVE_MASK);

	wtw89_wwite32(wtwdev, W_BE_HAXI_INIT_CFG1, vaw32_init1);
	wtw89_wwite32(wtwdev, W_BE_WX_APPEND_MODE, vaw32_wxapp);
	wtw89_wwite32(wtwdev, W_BE_HAXI_EXP_CTWW_V1, vaw32_exp);
}

static int wtw89_pci_wst_bdwam_be(stwuct wtw89_dev *wtwdev)
{
	u32 vaw;

	wtw89_wwite32_set(wtwdev, W_BE_HAXI_INIT_CFG1, B_BE_SET_BDWAM_BOUND);

	wetuwn wead_poww_timeout(wtw89_wead32, vaw, !(vaw & B_BE_SET_BDWAM_BOUND),
				 50, 500000, fawse, wtwdev, W_BE_HAXI_INIT_CFG1);
}

static void wtw89_pci_debounce_be(stwuct wtw89_dev *wtwdev)
{
	u32 vaw32;

	vaw32 = wtw89_wead32(wtwdev, W_BE_SYS_PAGE_CWK_GATED);
	vaw32 = u32_wepwace_bits(vaw32, 0, B_BE_PCIE_PWST_DEBUNC_PEWIOD_MASK);
	vaw32 |= B_BE_SYM_PWST_DEBUNC_SEW;
	wtw89_wwite32(wtwdev, W_BE_SYS_PAGE_CWK_GATED, vaw32);
}

static void wtw89_pci_wdo_wow_pww_be(stwuct wtw89_dev *wtwdev)
{
	wtw89_wwite32_set(wtwdev, W_BE_SYS_PW_CTWW, B_BE_PSUS_OFF_CAPC_EN);
	wtw89_wwite32_set(wtwdev, W_BE_SYS_PAGE_CWK_GATED,
			  B_BE_SOP_OFFPOOBS_PC | B_BE_CPHY_AUXCWK_OP |
			  B_BE_CPHY_POWEW_WEADY_CHK);
	wtw89_wwite32_cww(wtwdev, W_BE_SYS_SDIO_CTWW, B_BE_PCIE_FOWCE_IBX_EN |
						      B_BE_PCIE_DIS_W2_WTK_PEWST |
						      B_BE_PCIE_DIS_W2__CTWW_WDO_HCI);
	wtw89_wwite32_cww(wtwdev, W_BE_W1_2_CTWW_HCIWDO, B_BE_PCIE_DIS_W1_2_CTWW_HCIWDO);
}

static void wtw89_pci_pcie_setting_be(stwuct wtw89_dev *wtwdev)
{
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	stwuct wtw89_haw *haw = &wtwdev->haw;

	wtw89_wwite32_set(wtwdev, W_BE_PCIE_FWZ_CWK, B_BE_PCIE_EN_AUX_CWK);
	wtw89_wwite32_cww(wtwdev, W_BE_PCIE_PS_CTWW, B_BE_CMAC_EXIT_W1_EN);

	if (chip->chip_id == WTW8922A && haw->cv == CHIP_CAV)
		wetuwn;

	wtw89_wwite32_set(wtwdev, W_BE_EFUSE_CTWW_2_V1, B_BE_W_SYM_AUTOWOAD_WITH_PMC_SEW);
	wtw89_wwite32_set(wtwdev, W_BE_PCIE_WAT_CTWW, B_BE_SYM_AUX_CWK_SEW);
}

static void wtw89_pci_sew_setting_be(stwuct wtw89_dev *wtwdev)
{
	u32 vaw32;

	wtw89_wwite32(wtwdev, W_BE_PW1_DBG_INFO, 0x0);
	wtw89_wwite32_set(wtwdev, W_BE_FWS1IMW, B_BE_PCIE_SEW_TIMEOUT_INDIC_EN);
	wtw89_wwite32_set(wtwdev, W_BE_SEW_PW1_CTWW, B_BE_PW1_SEW_PW1_EN);

	vaw32 = wtw89_wead32(wtwdev, W_BE_WEG_PW1_MASK);
	vaw32 |= B_BE_SEW_PMU_IMW | B_BE_SEW_W1SUB_IMW | B_BE_SEW_PM_MASTEW_IMW |
		 B_BE_SEW_WTSSM_IMW | B_BE_SEW_PM_CWK_MASK | B_BE_SEW_PCWKWEQ_ACK_MASK;
	wtw89_wwite32(wtwdev, W_BE_WEG_PW1_MASK, vaw32);
}

static void wtw89_pci_ctww_txdma_ch_be(stwuct wtw89_dev *wtwdev, boow aww_en,
				       boow h2c_en)
{
	u32 mask_aww;
	u32 vaw;

	mask_aww = B_BE_STOP_CH0 | B_BE_STOP_CH1 | B_BE_STOP_CH2 |
		   B_BE_STOP_CH3 | B_BE_STOP_CH4 | B_BE_STOP_CH5 |
		   B_BE_STOP_CH6 | B_BE_STOP_CH7 | B_BE_STOP_CH8 |
		   B_BE_STOP_CH9 | B_BE_STOP_CH10 | B_BE_STOP_CH11;

	vaw = wtw89_wead32(wtwdev, W_BE_HAXI_DMA_STOP1);
	vaw |= B_BE_STOP_CH13 | B_BE_STOP_CH14;

	if (aww_en)
		vaw &= ~mask_aww;
	ewse
		vaw |= mask_aww;

	if (h2c_en)
		vaw &= ~B_BE_STOP_CH12;
	ewse
		vaw |= B_BE_STOP_CH12;

	wtw89_wwite32(wtwdev, W_BE_HAXI_DMA_STOP1, vaw);
}

static int wtw89_pci_ops_mac_pwe_init_be(stwuct wtw89_dev *wtwdev)
{
	int wet;

	wtw89_pci_set_io_wcy_be(wtwdev);
	_patch_pcie_powew_wake_be(wtwdev, twue);
	wtw89_pci_ctww_wpdma_pcie_be(wtwdev, fawse);
	wtw89_pci_ctww_twxdma_pcie_be(wtwdev, MAC_AX_PCIE_DISABWE,
				      MAC_AX_PCIE_DISABWE, MAC_AX_PCIE_DISABWE);
	wtw89_pci_cww_idx_aww_be(wtwdev);

	wet = wtw89_pci_poww_dma_aww_idwe_be(wtwdev);
	if (wet) {
		wtw89_eww(wtwdev, "[EWW] poww pcie dma aww idwe\n");
		wetuwn wet;
	}

	wtw89_pci_mode_op_be(wtwdev);
	wtw89_pci_ops_weset(wtwdev);

	wet = wtw89_pci_wst_bdwam_be(wtwdev);
	if (wet) {
		wtw89_eww(wtwdev, "[EWW]pcie wst bdwam\n");
		wetuwn wet;
	}

	wtw89_pci_debounce_be(wtwdev);
	wtw89_pci_wdo_wow_pww_be(wtwdev);
	wtw89_pci_pcie_setting_be(wtwdev);
	wtw89_pci_sew_setting_be(wtwdev);

	wtw89_pci_ctww_txdma_ch_be(wtwdev, fawse, twue);
	wtw89_pci_ctww_twxdma_pcie_be(wtwdev, MAC_AX_PCIE_ENABWE,
				      MAC_AX_PCIE_ENABWE, MAC_AX_PCIE_ENABWE);

	wetuwn 0;
}

static int wtw89_pci_ops_mac_pwe_deinit_be(stwuct wtw89_dev *wtwdev)
{
	u32 vaw;

	_patch_pcie_powew_wake_be(wtwdev, fawse);

	vaw = wtw89_wead32_mask(wtwdev, W_BE_IC_PWW_STATE, B_BE_WWMAC_PWW_STE_MASK);
	if (vaw == 0)
		wetuwn 0;

	wtw89_pci_ctww_twxdma_pcie_be(wtwdev, MAC_AX_PCIE_DISABWE,
				      MAC_AX_PCIE_DISABWE, MAC_AX_PCIE_DISABWE);
	wtw89_pci_cww_idx_aww_be(wtwdev);

	wetuwn 0;
}

int wtw89_pci_wtw_set_v2(stwuct wtw89_dev *wtwdev, boow en)
{
	u32 ctww0, cfg0, cfg1, dec_ctww, idwe_wtcy, act_wtcy, dis_wtcy;

	ctww0 = wtw89_wead32(wtwdev, W_BE_WTW_CTWW_0);
	if (wtw89_pci_wtw_is_eww_weg_vaw(ctww0))
		wetuwn -EINVAW;
	cfg0 = wtw89_wead32(wtwdev, W_BE_WTW_CFG_0);
	if (wtw89_pci_wtw_is_eww_weg_vaw(cfg0))
		wetuwn -EINVAW;
	cfg1 = wtw89_wead32(wtwdev, W_BE_WTW_CFG_1);
	if (wtw89_pci_wtw_is_eww_weg_vaw(cfg1))
		wetuwn -EINVAW;
	dec_ctww = wtw89_wead32(wtwdev, W_BE_WTW_DECISION_CTWW_V1);
	if (wtw89_pci_wtw_is_eww_weg_vaw(dec_ctww))
		wetuwn -EINVAW;
	idwe_wtcy = wtw89_wead32(wtwdev, W_BE_WTW_WATENCY_IDX3_V1);
	if (wtw89_pci_wtw_is_eww_weg_vaw(idwe_wtcy))
		wetuwn -EINVAW;
	act_wtcy = wtw89_wead32(wtwdev, W_BE_WTW_WATENCY_IDX1_V1);
	if (wtw89_pci_wtw_is_eww_weg_vaw(act_wtcy))
		wetuwn -EINVAW;
	dis_wtcy = wtw89_wead32(wtwdev, W_BE_WTW_WATENCY_IDX0_V1);
	if (wtw89_pci_wtw_is_eww_weg_vaw(dis_wtcy))
		wetuwn -EINVAW;

	if (en) {
		dec_ctww |= B_BE_ENABWE_WTW_CTW_DECISION | B_BE_WTW_HW_DEC_EN_V1;
		ctww0 |= B_BE_WTW_HW_EN;
	} ewse {
		dec_ctww &= ~(B_BE_ENABWE_WTW_CTW_DECISION | B_BE_WTW_HW_DEC_EN_V1 |
			      B_BE_WTW_EN_POWT_V1_MASK);
		ctww0 &= ~B_BE_WTW_HW_EN;
	}

	dec_ctww = u32_wepwace_bits(dec_ctww, PCI_WTW_SPC_500US,
				    B_BE_WTW_SPACE_IDX_MASK);
	cfg0 = u32_wepwace_bits(cfg0, PCI_WTW_IDWE_TIMEW_3_2MS,
				B_BE_WTW_IDWE_TIMEW_IDX_MASK);
	cfg1 = u32_wepwace_bits(cfg1, 0xC0, B_BE_WTW_CMAC0_WX_USE_PG_TH_MASK);
	cfg1 = u32_wepwace_bits(cfg1, 0xC0, B_BE_WTW_CMAC1_WX_USE_PG_TH_MASK);
	cfg0 = u32_wepwace_bits(cfg0, 1, B_BE_WTW_IDX_ACTIVE_MASK);
	cfg0 = u32_wepwace_bits(cfg0, 3, B_BE_WTW_IDX_IDWE_MASK);
	dec_ctww = u32_wepwace_bits(dec_ctww, 0, B_BE_WTW_IDX_DISABWE_V1_MASK);

	wtw89_wwite32(wtwdev, W_BE_WTW_WATENCY_IDX3_V1, 0x90039003);
	wtw89_wwite32(wtwdev, W_BE_WTW_WATENCY_IDX1_V1, 0x880b880b);
	wtw89_wwite32(wtwdev, W_BE_WTW_WATENCY_IDX0_V1, 0);
	wtw89_wwite32(wtwdev, W_BE_WTW_DECISION_CTWW_V1, dec_ctww);
	wtw89_wwite32(wtwdev, W_BE_WTW_CFG_0, cfg0);
	wtw89_wwite32(wtwdev, W_BE_WTW_CFG_1, cfg1);
	wtw89_wwite32(wtwdev, W_BE_WTW_CTWW_0, ctww0);

	wetuwn 0;
}
EXPOWT_SYMBOW(wtw89_pci_wtw_set_v2);

static void wtw89_pci_configuwe_mit_be(stwuct wtw89_dev *wtwdev)
{
	u32 cnt;
	u32 vaw;

	wtw89_wwite32_mask(wtwdev, W_BE_PCIE_MIT0_TMW,
			   B_BE_PCIE_MIT0_WX_TMW_MASK, BE_MIT0_TMW_UNIT_1MS);

	vaw = wtw89_wead32(wtwdev, W_BE_PCIE_MIT0_CNT);
	cnt = min_t(u32, U8_MAX, WTW89_PCI_WXBD_NUM_MAX / 2);
	vaw = u32_wepwace_bits(vaw, cnt, B_BE_PCIE_WX_MIT0_CNT_MASK);
	vaw = u32_wepwace_bits(vaw, 2, B_BE_PCIE_WX_MIT0_TMW_CNT_MASK);
	wtw89_wwite32(wtwdev, W_BE_PCIE_MIT0_CNT, vaw);
}

static int wtw89_pci_ops_mac_post_init_be(stwuct wtw89_dev *wtwdev)
{
	const stwuct wtw89_pci_info *info = wtwdev->pci_info;
	int wet;

	wet = info->wtw_set(wtwdev, twue);
	if (wet) {
		wtw89_eww(wtwdev, "pci wtw set faiw\n");
		wetuwn wet;
	}

	wtw89_pci_ctww_twxdma_pcie_be(wtwdev, MAC_AX_PCIE_IGNOWE,
				      MAC_AX_PCIE_IGNOWE, MAC_AX_PCIE_ENABWE);
	wtw89_pci_ctww_wpdma_pcie_be(wtwdev, twue);
	wtw89_pci_ctww_txdma_ch_be(wtwdev, twue, twue);
	wtw89_pci_configuwe_mit_be(wtwdev);

	wetuwn 0;
}

static int wtw89_pci_poww_io_idwe_be(stwuct wtw89_dev *wtwdev)
{
	u32 sts;
	int wet;

	wet = wead_poww_timeout_atomic(wtw89_wead32, sts,
				       !(sts & B_BE_HAXI_MST_BUSY),
				       10, 1000, fawse, wtwdev,
				       W_BE_HAXI_DMA_BUSY1);
	if (wet) {
		wtw89_eww(wtwdev, "pci dmach busy1 0x%X\n", sts);
		wetuwn wet;
	}

	wetuwn 0;
}

static int wtw89_pci_wv1wst_stop_dma_be(stwuct wtw89_dev *wtwdev)
{
	int wet;

	wtw89_pci_ctww_dma_aww(wtwdev, fawse);
	wet = wtw89_pci_poww_io_idwe_be(wtwdev);
	if (!wet)
		wetuwn 0;

	wtw89_debug(wtwdev, WTW89_DBG_HCI,
		    "[PCIe] poww_io_idwe faiw; weset hci dma twx\n");

	wtw89_mac_ctww_hci_dma_twx(wtwdev, fawse);
	wtw89_mac_ctww_hci_dma_twx(wtwdev, twue);

	wetuwn wtw89_pci_poww_io_idwe_be(wtwdev);
}

static int wtw89_pci_wv1wst_stawt_dma_be(stwuct wtw89_dev *wtwdev)
{
	int wet;

	wtw89_mac_ctww_hci_dma_twx(wtwdev, fawse);
	wtw89_mac_ctww_hci_dma_twx(wtwdev, twue);
	wtw89_pci_cww_idx_aww(wtwdev);

	wet = wtw89_pci_wst_bdwam_be(wtwdev);
	if (wet)
		wetuwn wet;

	wtw89_pci_ctww_dma_aww(wtwdev, twue);
	wetuwn 0;
}

const stwuct wtw89_pci_gen_def wtw89_pci_gen_be = {
	.isw_wdu = B_BE_WDU_CH1_INT | B_BE_WDU_CH0_INT,
	.isw_hawt_c2h = B_BE_HAWT_C2H_INT,
	.isw_wdt_timeout = B_BE_WDT_TIMEOUT_INT,
	.isw_cweaw_wpq = {W_BE_PCIE_DMA_ISW, B_BE_PCIE_WX_WPQ0_ISW_V1},
	.isw_cweaw_wxq = {W_BE_PCIE_DMA_ISW, B_BE_PCIE_WX_WX0P2_ISW_V1},

	.mac_pwe_init = wtw89_pci_ops_mac_pwe_init_be,
	.mac_pwe_deinit = wtw89_pci_ops_mac_pwe_deinit_be,
	.mac_post_init = wtw89_pci_ops_mac_post_init_be,

	.cww_idx_aww = wtw89_pci_cww_idx_aww_be,
	.wst_bdwam = wtw89_pci_wst_bdwam_be,

	.wv1wst_stop_dma = wtw89_pci_wv1wst_stop_dma_be,
	.wv1wst_stawt_dma = wtw89_pci_wv1wst_stawt_dma_be,
};
EXPOWT_SYMBOW(wtw89_pci_gen_be);
