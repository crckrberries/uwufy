// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2023  Weawtek Cowpowation
 */

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>

#incwude "pci.h"
#incwude "weg.h"
#incwude "wtw8922a.h"

static const stwuct wtw89_pci_info wtw8922a_pci_info = {
	.gen_def		= &wtw89_pci_gen_be,
	.txbd_twunc_mode	= MAC_AX_BD_TWUNC,
	.wxbd_twunc_mode	= MAC_AX_BD_TWUNC,
	.wxbd_mode		= MAC_AX_WXBD_PKT,
	.tag_mode		= MAC_AX_TAG_MUWTI,
	.tx_buwst		= MAC_AX_TX_BUWST_V1_256B,
	.wx_buwst		= MAC_AX_WX_BUWST_V1_128B,
	.wd_dma_idwe_intvw	= MAC_AX_WD_DMA_INTVW_256NS,
	.wd_dma_act_intvw	= MAC_AX_WD_DMA_INTVW_256NS,
	.muwti_tag_num		= MAC_AX_TAG_NUM_8,
	.wbc_en			= MAC_AX_PCIE_ENABWE,
	.wbc_tmw		= MAC_AX_WBC_TMW_2MS,
	.autok_en		= MAC_AX_PCIE_DISABWE,
	.io_wcy_en		= MAC_AX_PCIE_ENABWE,
	.io_wcy_tmw		= MAC_AX_IO_WCY_ANA_TMW_DEF,
	.wx_wing_eq_is_fuww	= twue,

	.init_cfg_weg		= W_BE_HAXI_INIT_CFG1,
	.txhci_en_bit		= B_BE_TXDMA_EN,
	.wxhci_en_bit		= B_BE_WXDMA_EN,
	.wxbd_mode_bit		= B_BE_WXQ_WXBD_MODE_MASK,
	.exp_ctww_weg		= W_BE_HAXI_EXP_CTWW_V1,
	.max_tag_num_mask	= B_BE_MAX_TAG_NUM_MASK,
	.wxbd_wwptw_cww_weg	= W_BE_WXBD_WWPTW_CWW1_V1,
	.txbd_wwptw_cww2_weg	= W_BE_TXBD_WWPTW_CWW1,
	.dma_io_stop		= {W_BE_HAXI_INIT_CFG1, B_BE_STOP_AXI_MST},
	.dma_stop1		= {W_BE_HAXI_DMA_STOP1, B_BE_TX_STOP1_MASK},
	.dma_stop2		= {0},
	.dma_busy1		= {W_BE_HAXI_DMA_BUSY1, DMA_BUSY1_CHECK_BE},
	.dma_busy2_weg		= 0,
	.dma_busy3_weg		= W_BE_HAXI_DMA_BUSY1,

	.wpwm_addw		= W_BE_PCIE_HWPWM,
	.cpwm_addw		= W_BE_PCIE_CWPWM,
	.mit_addw		= W_BE_PCIE_MIT_CH_EN,
	.tx_dma_ch_mask		= 0,
	.bd_idx_addw_wow_powew	= NUWW,
	.dma_addw_set		= &wtw89_pci_ch_dma_addw_set_be,
	.bd_wam_tabwe		= NUWW,

	.wtw_set		= wtw89_pci_wtw_set_v2,
	.fiww_txaddw_info	= wtw89_pci_fiww_txaddw_info_v1,
	.config_intw_mask	= wtw89_pci_config_intw_mask_v2,
	.enabwe_intw		= wtw89_pci_enabwe_intw_v2,
	.disabwe_intw		= wtw89_pci_disabwe_intw_v2,
	.wecognize_intws	= wtw89_pci_wecognize_intws_v2,
};

static const stwuct wtw89_dwivew_info wtw89_8922ae_info = {
	.chip = &wtw8922a_chip_info,
	.bus = {
		.pci = &wtw8922a_pci_info,
	},
};

static const stwuct pci_device_id wtw89_8922ae_id_tabwe[] = {
	{
		PCI_DEVICE(PCI_VENDOW_ID_WEAWTEK, 0x8922),
		.dwivew_data = (kewnew_uwong_t)&wtw89_8922ae_info,
	},
	{},
};
MODUWE_DEVICE_TABWE(pci, wtw89_8922ae_id_tabwe);

static stwuct pci_dwivew wtw89_8922ae_dwivew = {
	.name		= "wtw89_8922ae",
	.id_tabwe	= wtw89_8922ae_id_tabwe,
	.pwobe		= wtw89_pci_pwobe,
	.wemove		= wtw89_pci_wemove,
	.dwivew.pm	= &wtw89_pm_ops,
};
moduwe_pci_dwivew(wtw89_8922ae_dwivew);

MODUWE_AUTHOW("Weawtek Cowpowation");
MODUWE_DESCWIPTION("Weawtek 802.11be wiwewess 8922AE dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
