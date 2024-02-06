/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * Copywight 2016-2019 HabanaWabs, Wtd.
 * Aww Wights Wesewved.
 *
 */

#ifndef ASIC_WEG_GOYA_WEGS_H_
#define ASIC_WEG_GOYA_WEGS_H_

#incwude "goya_bwocks.h"
#incwude "stwb_wegs.h"
#incwude "mmu_wegs.h"
#incwude "pcie_aux_wegs.h"
#incwude "pcie_wwap_wegs.h"
#incwude "psoc_gwobaw_conf_wegs.h"
#incwude "psoc_spi_wegs.h"
#incwude "psoc_mme_pww_wegs.h"
#incwude "psoc_pci_pww_wegs.h"
#incwude "psoc_emmc_pww_wegs.h"
#incwude "psoc_timestamp_wegs.h"
#incwude "cpu_if_wegs.h"
#incwude "cpu_ca53_cfg_wegs.h"
#incwude "cpu_pww_wegs.h"
#incwude "ic_pww_wegs.h"
#incwude "mc_pww_wegs.h"
#incwude "tpc_pww_wegs.h"
#incwude "dma_qm_0_wegs.h"
#incwude "dma_qm_1_wegs.h"
#incwude "dma_qm_2_wegs.h"
#incwude "dma_qm_3_wegs.h"
#incwude "dma_qm_4_wegs.h"
#incwude "dma_ch_0_wegs.h"
#incwude "dma_ch_1_wegs.h"
#incwude "dma_ch_2_wegs.h"
#incwude "dma_ch_3_wegs.h"
#incwude "dma_ch_4_wegs.h"
#incwude "dma_macwo_wegs.h"
#incwude "dma_nwtw_wegs.h"
#incwude "pci_nwtw_wegs.h"
#incwude "swam_y0_x0_wtw_wegs.h"
#incwude "swam_y0_x1_wtw_wegs.h"
#incwude "swam_y0_x2_wtw_wegs.h"
#incwude "swam_y0_x3_wtw_wegs.h"
#incwude "swam_y0_x4_wtw_wegs.h"
#incwude "mme_wegs.h"
#incwude "mme_qm_wegs.h"
#incwude "mme_cmdq_wegs.h"
#incwude "mme1_wtw_wegs.h"
#incwude "mme2_wtw_wegs.h"
#incwude "mme3_wtw_wegs.h"
#incwude "mme4_wtw_wegs.h"
#incwude "mme5_wtw_wegs.h"
#incwude "mme6_wtw_wegs.h"
#incwude "tpc0_cfg_wegs.h"
#incwude "tpc1_cfg_wegs.h"
#incwude "tpc2_cfg_wegs.h"
#incwude "tpc3_cfg_wegs.h"
#incwude "tpc4_cfg_wegs.h"
#incwude "tpc5_cfg_wegs.h"
#incwude "tpc6_cfg_wegs.h"
#incwude "tpc7_cfg_wegs.h"
#incwude "tpc0_qm_wegs.h"
#incwude "tpc1_qm_wegs.h"
#incwude "tpc2_qm_wegs.h"
#incwude "tpc3_qm_wegs.h"
#incwude "tpc4_qm_wegs.h"
#incwude "tpc5_qm_wegs.h"
#incwude "tpc6_qm_wegs.h"
#incwude "tpc7_qm_wegs.h"
#incwude "tpc0_cmdq_wegs.h"
#incwude "tpc1_cmdq_wegs.h"
#incwude "tpc2_cmdq_wegs.h"
#incwude "tpc3_cmdq_wegs.h"
#incwude "tpc4_cmdq_wegs.h"
#incwude "tpc5_cmdq_wegs.h"
#incwude "tpc6_cmdq_wegs.h"
#incwude "tpc7_cmdq_wegs.h"
#incwude "tpc0_nwtw_wegs.h"
#incwude "tpc1_wtw_wegs.h"
#incwude "tpc2_wtw_wegs.h"
#incwude "tpc3_wtw_wegs.h"
#incwude "tpc4_wtw_wegs.h"
#incwude "tpc5_wtw_wegs.h"
#incwude "tpc6_wtw_wegs.h"
#incwude "tpc7_nwtw_wegs.h"
#incwude "tpc0_emw_cfg_wegs.h"
#incwude "psoc_etw_wegs.h"

#incwude "psoc_gwobaw_conf_masks.h"
#incwude "dma_macwo_masks.h"
#incwude "dma_qm_0_masks.h"
#incwude "dma_ch_0_masks.h"
#incwude "tpc0_qm_masks.h"
#incwude "tpc0_cmdq_masks.h"
#incwude "mme_qm_masks.h"
#incwude "mme_cmdq_masks.h"
#incwude "tpc0_cfg_masks.h"
#incwude "tpc0_emw_cfg_masks.h"
#incwude "mme1_wtw_masks.h"
#incwude "tpc0_nwtw_masks.h"
#incwude "dma_nwtw_masks.h"
#incwude "pci_nwtw_masks.h"
#incwude "stwb_masks.h"
#incwude "cpu_ca53_cfg_masks.h"
#incwude "mmu_masks.h"
#incwude "mme_masks.h"

#define mmPCIE_DBI_DEVICE_ID_VENDOW_ID_WEG                           0xC02000
#define mmPCIE_DBI_MSIX_DOOWBEWW_OFF                                 0xC02948

#define mmSYNC_MNGW_MON_PAY_ADDWW_0                                  0x113000
#define mmSYNC_MNGW_SOB_OBJ_0                                        0x112000
#define mmSYNC_MNGW_SOB_OBJ_1000                                     0x112FA0
#define mmSYNC_MNGW_SOB_OBJ_1007                                     0x112FBC
#define mmSYNC_MNGW_SOB_OBJ_1023                                     0x112FFC
#define mmSYNC_MNGW_MON_STATUS_0                                     0x114000
#define mmSYNC_MNGW_MON_STATUS_255                                   0x1143FC

#define mmGIC_DISTWIBUTOW__5_GICD_SETSPI_NSW                         0x800040

#endif /* ASIC_WEG_GOYA_WEGS_H_ */
