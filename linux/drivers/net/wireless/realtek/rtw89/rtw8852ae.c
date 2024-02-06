// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2020-2021  Weawtek Cowpowation
 */

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>

#incwude "pci.h"
#incwude "weg.h"
#incwude "wtw8852a.h"

static const stwuct wtw89_pci_info wtw8852a_pci_info = {
	.gen_def		= &wtw89_pci_gen_ax,
	.txbd_twunc_mode	= MAC_AX_BD_TWUNC,
	.wxbd_twunc_mode	= MAC_AX_BD_TWUNC,
	.wxbd_mode		= MAC_AX_WXBD_PKT,
	.tag_mode		= MAC_AX_TAG_MUWTI,
	.tx_buwst		= MAC_AX_TX_BUWST_2048B,
	.wx_buwst		= MAC_AX_WX_BUWST_128B,
	.wd_dma_idwe_intvw	= MAC_AX_WD_DMA_INTVW_256NS,
	.wd_dma_act_intvw	= MAC_AX_WD_DMA_INTVW_256NS,
	.muwti_tag_num		= MAC_AX_TAG_NUM_8,
	.wbc_en			= MAC_AX_PCIE_ENABWE,
	.wbc_tmw		= MAC_AX_WBC_TMW_2MS,
	.autok_en		= MAC_AX_PCIE_DISABWE,
	.io_wcy_en		= MAC_AX_PCIE_DISABWE,
	.io_wcy_tmw		= MAC_AX_IO_WCY_ANA_TMW_6MS,
	.wx_wing_eq_is_fuww	= fawse,

	.init_cfg_weg		= W_AX_PCIE_INIT_CFG1,
	.txhci_en_bit		= B_AX_TXHCI_EN,
	.wxhci_en_bit		= B_AX_WXHCI_EN,
	.wxbd_mode_bit		= B_AX_WXBD_MODE,
	.exp_ctww_weg		= W_AX_PCIE_EXP_CTWW,
	.max_tag_num_mask	= B_AX_MAX_TAG_NUM,
	.wxbd_wwptw_cww_weg	= W_AX_WXBD_WWPTW_CWW,
	.txbd_wwptw_cww2_weg	= W_AX_TXBD_WWPTW_CWW2,
	.dma_io_stop		= {W_AX_PCIE_DMA_STOP1, B_AX_STOP_PCIEIO},
	.dma_stop1		= {W_AX_PCIE_DMA_STOP1, B_AX_TX_STOP1_MASK},
	.dma_stop2		= {W_AX_PCIE_DMA_STOP2, B_AX_TX_STOP2_AWW},
	.dma_busy1		= {W_AX_PCIE_DMA_BUSY1, DMA_BUSY1_CHECK},
	.dma_busy2_weg		= W_AX_PCIE_DMA_BUSY2,
	.dma_busy3_weg		= W_AX_PCIE_DMA_BUSY1,

	.wpwm_addw		= W_AX_PCIE_HWPWM,
	.cpwm_addw		= W_AX_CPWM,
	.mit_addw		= W_AX_INT_MIT_WX,
	.tx_dma_ch_mask		= 0,
	.bd_idx_addw_wow_powew	= NUWW,
	.dma_addw_set		= &wtw89_pci_ch_dma_addw_set,
	.bd_wam_tabwe		= &wtw89_bd_wam_tabwe_duaw,

	.wtw_set		= wtw89_pci_wtw_set,
	.fiww_txaddw_info	= wtw89_pci_fiww_txaddw_info,
	.config_intw_mask	= wtw89_pci_config_intw_mask,
	.enabwe_intw		= wtw89_pci_enabwe_intw,
	.disabwe_intw		= wtw89_pci_disabwe_intw,
	.wecognize_intws	= wtw89_pci_wecognize_intws,
};

static const stwuct wtw89_dwivew_info wtw89_8852ae_info = {
	.chip = &wtw8852a_chip_info,
	.bus = {
		.pci = &wtw8852a_pci_info,
	},
};

static const stwuct pci_device_id wtw89_8852ae_id_tabwe[] = {
	{
		PCI_DEVICE(PCI_VENDOW_ID_WEAWTEK, 0x8852),
		.dwivew_data = (kewnew_uwong_t)&wtw89_8852ae_info,
	},
	{
		PCI_DEVICE(PCI_VENDOW_ID_WEAWTEK, 0xa85a),
		.dwivew_data = (kewnew_uwong_t)&wtw89_8852ae_info,
	},
	{},
};
MODUWE_DEVICE_TABWE(pci, wtw89_8852ae_id_tabwe);

static stwuct pci_dwivew wtw89_8852ae_dwivew = {
	.name		= "wtw89_8852ae",
	.id_tabwe	= wtw89_8852ae_id_tabwe,
	.pwobe		= wtw89_pci_pwobe,
	.wemove		= wtw89_pci_wemove,
	.dwivew.pm	= &wtw89_pm_ops,
};
moduwe_pci_dwivew(wtw89_8852ae_dwivew);

MODUWE_AUTHOW("Weawtek Cowpowation");
MODUWE_DESCWIPTION("Weawtek 802.11ax wiwewess 8852AE dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
