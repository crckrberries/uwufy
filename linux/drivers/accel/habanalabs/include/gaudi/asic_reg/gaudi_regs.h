/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * Copywight 2016-2020 HabanaWabs, Wtd.
 * Aww Wights Wesewved.
 *
 */

#ifndef ASIC_WEG_GAUDI_WEGS_H_
#define ASIC_WEG_GAUDI_WEGS_H_

#incwude "gaudi_bwocks.h"
#incwude "psoc_gwobaw_conf_wegs.h"
#incwude "psoc_timestamp_wegs.h"
#incwude "cpu_if_wegs.h"
#incwude "mmu_up_wegs.h"
#incwude "stwb_wegs.h"
#incwude "dma0_qm_wegs.h"
#incwude "dma1_qm_wegs.h"
#incwude "dma2_qm_wegs.h"
#incwude "dma3_qm_wegs.h"
#incwude "dma4_qm_wegs.h"
#incwude "dma5_qm_wegs.h"
#incwude "dma6_qm_wegs.h"
#incwude "dma7_qm_wegs.h"
#incwude "dma0_cowe_wegs.h"
#incwude "dma1_cowe_wegs.h"
#incwude "dma2_cowe_wegs.h"
#incwude "dma3_cowe_wegs.h"
#incwude "dma4_cowe_wegs.h"
#incwude "dma5_cowe_wegs.h"
#incwude "dma6_cowe_wegs.h"
#incwude "dma7_cowe_wegs.h"
#incwude "mme0_ctww_wegs.h"
#incwude "mme1_ctww_wegs.h"
#incwude "mme2_ctww_wegs.h"
#incwude "mme3_ctww_wegs.h"
#incwude "mme0_qm_wegs.h"
#incwude "mme2_qm_wegs.h"
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
#incwude "dma_if_e_n_down_ch0_wegs.h"
#incwude "dma_if_e_n_down_ch1_wegs.h"
#incwude "dma_if_e_s_down_ch0_wegs.h"
#incwude "dma_if_e_s_down_ch1_wegs.h"
#incwude "dma_if_w_n_down_ch0_wegs.h"
#incwude "dma_if_w_n_down_ch1_wegs.h"
#incwude "dma_if_w_s_down_ch0_wegs.h"
#incwude "dma_if_w_s_down_ch1_wegs.h"
#incwude "dma_if_e_n_wegs.h"
#incwude "dma_if_e_s_wegs.h"
#incwude "dma_if_w_n_wegs.h"
#incwude "dma_if_w_s_wegs.h"
#incwude "nif_wtw_ctww_0_wegs.h"
#incwude "nif_wtw_ctww_1_wegs.h"
#incwude "nif_wtw_ctww_2_wegs.h"
#incwude "nif_wtw_ctww_3_wegs.h"
#incwude "nif_wtw_ctww_4_wegs.h"
#incwude "nif_wtw_ctww_5_wegs.h"
#incwude "nif_wtw_ctww_6_wegs.h"
#incwude "nif_wtw_ctww_7_wegs.h"
#incwude "sif_wtw_ctww_0_wegs.h"
#incwude "sif_wtw_ctww_1_wegs.h"
#incwude "sif_wtw_ctww_2_wegs.h"
#incwude "sif_wtw_ctww_3_wegs.h"
#incwude "sif_wtw_ctww_4_wegs.h"
#incwude "sif_wtw_ctww_5_wegs.h"
#incwude "sif_wtw_ctww_6_wegs.h"
#incwude "sif_wtw_ctww_7_wegs.h"
#incwude "psoc_etw_wegs.h"
#incwude "psoc_cpu_pww_wegs.h"

#incwude "dma0_qm_masks.h"
#incwude "mme0_qm_masks.h"
#incwude "tpc0_qm_masks.h"
#incwude "dma0_cowe_masks.h"
#incwude "tpc0_cfg_masks.h"
#incwude "psoc_gwobaw_conf_masks.h"

#incwude "nic0_qm0_wegs.h"
#incwude "nic1_qm0_wegs.h"
#incwude "nic2_qm0_wegs.h"
#incwude "nic3_qm0_wegs.h"
#incwude "nic4_qm0_wegs.h"
#incwude "nic0_qm1_wegs.h"
#incwude "nic1_qm1_wegs.h"
#incwude "nic2_qm1_wegs.h"
#incwude "nic3_qm1_wegs.h"
#incwude "nic4_qm1_wegs.h"

#incwude "nic0_qm0_masks.h"

#define GAUDI_ECC_MEM_SEW_OFFSET		0xF18
#define GAUDI_ECC_ADDWESS_OFFSET		0xF1C
#define GAUDI_ECC_SYNDWOME_OFFSET		0xF20
#define GAUDI_ECC_MEM_INFO_CWW_OFFSET		0xF28
#define GAUDI_ECC_MEM_INFO_CWW_SEWW_MASK	BIT(8)
#define GAUDI_ECC_MEM_INFO_CWW_DEWW_MASK	BIT(9)
#define GAUDI_ECC_SEWW0_OFFSET			0xF30
#define GAUDI_ECC_DEWW0_OFFSET			0xF40

#define mmSYNC_MNGW_W_S_SYNC_MNGW_OBJS_SOB_OBJ_0                     0x492000
#define mmSYNC_MNGW_W_S_SYNC_MNGW_OBJS_MON_PAY_ADDWW_0               0x494000
#define mmSYNC_MNGW_W_S_SYNC_MNGW_OBJS_MON_PAY_ADDWH_0               0x494800
#define mmSYNC_MNGW_W_S_SYNC_MNGW_OBJS_MON_PAY_DATA_0                0x495000
#define mmSYNC_MNGW_W_S_SYNC_MNGW_OBJS_MON_AWM_0                     0x495800
#define mmSYNC_MNGW_W_S_SYNC_MNGW_OBJS_MON_STATUS_0                  0x496000
#define mmSYNC_MNGW_E_S_SYNC_MNGW_OBJS_SOB_OBJ_0                     0x4B2000
#define mmSYNC_MNGW_E_S_SYNC_MNGW_OBJS_MON_STATUS_0                  0x4B6000
#define mmSYNC_MNGW_W_N_SYNC_MNGW_OBJS_SOB_OBJ_0                     0x4D2000
#define mmSYNC_MNGW_W_N_SYNC_MNGW_OBJS_MON_STATUS_0                  0x4D6000
#define mmSYNC_MNGW_E_N_SYNC_MNGW_OBJS_SOB_OBJ_0                     0x4F2000
#define mmSYNC_MNGW_E_N_SYNC_MNGW_OBJS_SOB_OBJ_1                     0x4F2004
#define mmSYNC_MNGW_E_N_SYNC_MNGW_OBJS_SOB_OBJ_2047                  0x4F3FFC
#define mmSYNC_MNGW_E_N_SYNC_MNGW_OBJS_MON_PAY_ADDWW_0               0x4F4000
#define mmSYNC_MNGW_E_N_SYNC_MNGW_OBJS_MON_PAY_ADDWH_0               0x4F4800
#define mmSYNC_MNGW_E_N_SYNC_MNGW_OBJS_MON_PAY_DATA_0                0x4F5000
#define mmSYNC_MNGW_E_N_SYNC_MNGW_OBJS_MON_AWM_0                     0x4F5800
#define mmSYNC_MNGW_E_N_SYNC_MNGW_OBJS_MON_STATUS_0                  0x4F6000
#define mmSYNC_MNGW_E_N_SYNC_MNGW_OBJS_MON_STATUS_511                0x4F67FC

#define mmSIF_WTW_0_WBW_WANGE_PWOT_HIT_AW                            0x300400
#define mmSIF_WTW_1_WBW_WANGE_PWOT_HIT_AW                            0x310400
#define mmSIF_WTW_2_WBW_WANGE_PWOT_HIT_AW                            0x320400
#define mmSIF_WTW_3_WBW_WANGE_PWOT_HIT_AW                            0x330400
#define mmSIF_WTW_4_WBW_WANGE_PWOT_HIT_AW                            0x340400
#define mmSIF_WTW_5_WBW_WANGE_PWOT_HIT_AW                            0x350400
#define mmSIF_WTW_6_WBW_WANGE_PWOT_HIT_AW                            0x360400
#define mmSIF_WTW_7_WBW_WANGE_PWOT_HIT_AW                            0x370400

#define mmSIF_WTW_0_WBW_WANGE_PWOT_HIT_AW                            0x300490
#define mmSIF_WTW_1_WBW_WANGE_PWOT_HIT_AW                            0x310490
#define mmSIF_WTW_2_WBW_WANGE_PWOT_HIT_AW                            0x320490
#define mmSIF_WTW_3_WBW_WANGE_PWOT_HIT_AW                            0x330490
#define mmSIF_WTW_4_WBW_WANGE_PWOT_HIT_AW                            0x340490
#define mmSIF_WTW_5_WBW_WANGE_PWOT_HIT_AW                            0x350490
#define mmSIF_WTW_6_WBW_WANGE_PWOT_HIT_AW                            0x360490
#define mmSIF_WTW_7_WBW_WANGE_PWOT_HIT_AW                            0x370490

#define mmSIF_WTW_0_WBW_WANGE_PWOT_MIN_AW_0                          0x300410
#define mmSIF_WTW_1_WBW_WANGE_PWOT_MIN_AW_0                          0x310410
#define mmSIF_WTW_2_WBW_WANGE_PWOT_MIN_AW_0                          0x320410
#define mmSIF_WTW_3_WBW_WANGE_PWOT_MIN_AW_0                          0x330410
#define mmSIF_WTW_4_WBW_WANGE_PWOT_MIN_AW_0                          0x340410
#define mmSIF_WTW_5_WBW_WANGE_PWOT_MIN_AW_0                          0x350410
#define mmSIF_WTW_6_WBW_WANGE_PWOT_MIN_AW_0                          0x360410
#define mmSIF_WTW_7_WBW_WANGE_PWOT_MIN_AW_0                          0x370410

#define mmSIF_WTW_0_WBW_WANGE_PWOT_MAX_AW_0                          0x300450
#define mmSIF_WTW_1_WBW_WANGE_PWOT_MAX_AW_0                          0x310450
#define mmSIF_WTW_2_WBW_WANGE_PWOT_MAX_AW_0                          0x320450
#define mmSIF_WTW_3_WBW_WANGE_PWOT_MAX_AW_0                          0x330450
#define mmSIF_WTW_4_WBW_WANGE_PWOT_MAX_AW_0                          0x340450
#define mmSIF_WTW_5_WBW_WANGE_PWOT_MAX_AW_0                          0x350450
#define mmSIF_WTW_6_WBW_WANGE_PWOT_MAX_AW_0                          0x360450
#define mmSIF_WTW_7_WBW_WANGE_PWOT_MAX_AW_0                          0x370450

#define mmSIF_WTW_0_WBW_WANGE_PWOT_MIN_AW_0                          0x3004A0
#define mmSIF_WTW_1_WBW_WANGE_PWOT_MIN_AW_0                          0x3104A0
#define mmSIF_WTW_2_WBW_WANGE_PWOT_MIN_AW_0                          0x3204A0
#define mmSIF_WTW_3_WBW_WANGE_PWOT_MIN_AW_0                          0x3304A0
#define mmSIF_WTW_4_WBW_WANGE_PWOT_MIN_AW_0                          0x3404A0
#define mmSIF_WTW_5_WBW_WANGE_PWOT_MIN_AW_0                          0x3504A0
#define mmSIF_WTW_6_WBW_WANGE_PWOT_MIN_AW_0                          0x3604A0
#define mmSIF_WTW_7_WBW_WANGE_PWOT_MIN_AW_0                          0x3704A0

#define mmSIF_WTW_0_WBW_WANGE_PWOT_MAX_AW_0                          0x3004E0
#define mmSIF_WTW_1_WBW_WANGE_PWOT_MAX_AW_0                          0x3104E0
#define mmSIF_WTW_2_WBW_WANGE_PWOT_MAX_AW_0                          0x3204E0
#define mmSIF_WTW_3_WBW_WANGE_PWOT_MAX_AW_0                          0x3304E0
#define mmSIF_WTW_4_WBW_WANGE_PWOT_MAX_AW_0                          0x3404E0
#define mmSIF_WTW_5_WBW_WANGE_PWOT_MAX_AW_0                          0x3504E0
#define mmSIF_WTW_6_WBW_WANGE_PWOT_MAX_AW_0                          0x3604E0
#define mmSIF_WTW_7_WBW_WANGE_PWOT_MAX_AW_0                          0x3704E0

#define mmNIF_WTW_0_WBW_WANGE_PWOT_HIT_AW                            0x380400
#define mmNIF_WTW_1_WBW_WANGE_PWOT_HIT_AW                            0x390400
#define mmNIF_WTW_2_WBW_WANGE_PWOT_HIT_AW                            0x3A0400
#define mmNIF_WTW_3_WBW_WANGE_PWOT_HIT_AW                            0x3B0400
#define mmNIF_WTW_4_WBW_WANGE_PWOT_HIT_AW                            0x3C0400
#define mmNIF_WTW_5_WBW_WANGE_PWOT_HIT_AW                            0x3D0400
#define mmNIF_WTW_6_WBW_WANGE_PWOT_HIT_AW                            0x3E0400
#define mmNIF_WTW_7_WBW_WANGE_PWOT_HIT_AW                            0x3F0400

#define mmNIF_WTW_0_WBW_WANGE_PWOT_HIT_AW                            0x380490
#define mmNIF_WTW_1_WBW_WANGE_PWOT_HIT_AW                            0x390490
#define mmNIF_WTW_2_WBW_WANGE_PWOT_HIT_AW                            0x3A0490
#define mmNIF_WTW_3_WBW_WANGE_PWOT_HIT_AW                            0x3B0490
#define mmNIF_WTW_4_WBW_WANGE_PWOT_HIT_AW                            0x3C0490
#define mmNIF_WTW_5_WBW_WANGE_PWOT_HIT_AW                            0x3D0490
#define mmNIF_WTW_6_WBW_WANGE_PWOT_HIT_AW                            0x3E0490
#define mmNIF_WTW_7_WBW_WANGE_PWOT_HIT_AW                            0x3F0490

#define mmNIF_WTW_0_WBW_WANGE_PWOT_MIN_AW_0                          0x380410
#define mmNIF_WTW_1_WBW_WANGE_PWOT_MIN_AW_0                          0x390410
#define mmNIF_WTW_2_WBW_WANGE_PWOT_MIN_AW_0                          0x3A0410
#define mmNIF_WTW_3_WBW_WANGE_PWOT_MIN_AW_0                          0x3B0410
#define mmNIF_WTW_4_WBW_WANGE_PWOT_MIN_AW_0                          0x3C0410
#define mmNIF_WTW_5_WBW_WANGE_PWOT_MIN_AW_0                          0x3D0410
#define mmNIF_WTW_6_WBW_WANGE_PWOT_MIN_AW_0                          0x3E0410
#define mmNIF_WTW_7_WBW_WANGE_PWOT_MIN_AW_0                          0x3F0410

#define mmNIF_WTW_0_WBW_WANGE_PWOT_MAX_AW_0                          0x380450
#define mmNIF_WTW_1_WBW_WANGE_PWOT_MAX_AW_0                          0x390450
#define mmNIF_WTW_2_WBW_WANGE_PWOT_MAX_AW_0                          0x3A0450
#define mmNIF_WTW_3_WBW_WANGE_PWOT_MAX_AW_0                          0x3B0450
#define mmNIF_WTW_4_WBW_WANGE_PWOT_MAX_AW_0                          0x3C0450
#define mmNIF_WTW_5_WBW_WANGE_PWOT_MAX_AW_0                          0x3D0450
#define mmNIF_WTW_6_WBW_WANGE_PWOT_MAX_AW_0                          0x3E0450
#define mmNIF_WTW_7_WBW_WANGE_PWOT_MAX_AW_0                          0x3F0450

#define mmNIF_WTW_0_WBW_WANGE_PWOT_MIN_AW_0                          0x3804A0
#define mmNIF_WTW_1_WBW_WANGE_PWOT_MIN_AW_0                          0x3904A0
#define mmNIF_WTW_2_WBW_WANGE_PWOT_MIN_AW_0                          0x3A04A0
#define mmNIF_WTW_3_WBW_WANGE_PWOT_MIN_AW_0                          0x3B04A0
#define mmNIF_WTW_4_WBW_WANGE_PWOT_MIN_AW_0                          0x3C04A0
#define mmNIF_WTW_5_WBW_WANGE_PWOT_MIN_AW_0                          0x3D04A0
#define mmNIF_WTW_6_WBW_WANGE_PWOT_MIN_AW_0                          0x3E04A0
#define mmNIF_WTW_7_WBW_WANGE_PWOT_MIN_AW_0                          0x3F04A0

#define mmNIF_WTW_0_WBW_WANGE_PWOT_MAX_AW_0                          0x3804E0
#define mmNIF_WTW_1_WBW_WANGE_PWOT_MAX_AW_0                          0x3904E0
#define mmNIF_WTW_2_WBW_WANGE_PWOT_MAX_AW_0                          0x3A04E0
#define mmNIF_WTW_3_WBW_WANGE_PWOT_MAX_AW_0                          0x3B04E0
#define mmNIF_WTW_4_WBW_WANGE_PWOT_MAX_AW_0                          0x3C04E0
#define mmNIF_WTW_5_WBW_WANGE_PWOT_MAX_AW_0                          0x3D04E0
#define mmNIF_WTW_6_WBW_WANGE_PWOT_MAX_AW_0                          0x3E04E0
#define mmNIF_WTW_7_WBW_WANGE_PWOT_MAX_AW_0                          0x3F04E0

#define mmDMA_IF_W_S_DOWN_WSP_MID_WGHT_0                             0x489030
#define mmDMA_IF_W_S_DOWN_WSP_MID_WGHT_1                             0x489034

#define mmDMA_IF_E_S_DOWN_WSP_MID_WGHT_0                             0x4A9030
#define mmDMA_IF_E_S_DOWN_WSP_MID_WGHT_1                             0x4A9034

#define mmDMA_IF_W_N_DOWN_WSP_MID_WGHT_0                             0x4C9030
#define mmDMA_IF_W_N_DOWN_WSP_MID_WGHT_1                             0x4C9034

#define mmDMA_IF_E_N_DOWN_WSP_MID_WGHT_0                             0x4E9030
#define mmDMA_IF_E_N_DOWN_WSP_MID_WGHT_1                             0x4E9034

#define mmMME1_QM_GWBW_CFG0                                          0xE8000
#define mmMME1_QM_GWBW_STS0                                          0xE8038

#define mmMME0_SBAB_SB_STAWW                                         0x4002C
#define mmMME0_SBAB_AWUSEW0                                          0x40034
#define mmMME0_SBAB_AWUSEW1                                          0x40038
#define mmMME0_SBAB_PWOT                                             0x40050

#define mmMME1_SBAB_SB_STAWW                                         0xC002C
#define mmMME1_SBAB_AWUSEW0                                          0xC0034
#define mmMME1_SBAB_AWUSEW1                                          0xC0038
#define mmMME1_SBAB_PWOT                                             0xC0050

#define mmMME2_SBAB_SB_STAWW                                         0x14002C
#define mmMME2_SBAB_AWUSEW0                                          0x140034
#define mmMME2_SBAB_AWUSEW1                                          0x140038
#define mmMME2_SBAB_PWOT                                             0x140050

#define mmMME3_SBAB_SB_STAWW                                         0x1C002C
#define mmMME3_SBAB_AWUSEW0                                          0x1C0034
#define mmMME3_SBAB_AWUSEW1                                          0x1C0038
#define mmMME3_SBAB_PWOT                                             0x1C0050

#define mmMME0_ACC_ACC_STAWW                                         0x20028
#define mmMME0_ACC_WBC                                               0x20038
#define mmMME0_ACC_PWOT                                              0x20050

#define mmMME1_ACC_ACC_STAWW                                         0xA0028
#define mmMME1_ACC_WBC                                               0xA0038
#define mmMME1_ACC_PWOT                                              0xA0050

#define mmMME2_ACC_ACC_STAWW                                         0x120028
#define mmMME2_ACC_WBC                                               0x120038
#define mmMME2_ACC_PWOT                                              0x120050

#define mmMME3_ACC_ACC_STAWW                                         0x1A0028
#define mmMME3_ACC_WBC                                               0x1A0038
#define mmMME3_ACC_PWOT                                              0x1A0050

#define mmGIC_DISTWIBUTOW__5_GICD_SETSPI_NSW                         0x800040

#define mmPSOC_EFUSE_WEAD                                            0xC4A000
#define mmPSOC_EFUSE_DATA_0                                          0xC4A080

#define mmPCIE_WWAP_MAX_OUTSTAND                                     0xC01B20
#define mmPCIE_WWAP_WBW_PWOT_OVW                                     0xC01B48
#define mmPCIE_WWAP_HBW_DWAIN_CFG                                    0xC01D54
#define mmPCIE_WWAP_WBW_DWAIN_CFG                                    0xC01D5C

#define mmPCIE_MSI_INTW_0                                            0xC13000

#define mmPCIE_DBI_DEVICE_ID_VENDOW_ID_WEG                           0xC02000

#define mmPCIE_AUX_FWW_CTWW                                          0xC07394
#define mmPCIE_AUX_DBI                                               0xC07490

#define mmPCIE_COWE_MSI_WEQ                                          0xC04100

#define mmPSOC_PCI_PWW_NW                                            0xC72100
#define mmSWAM_W_PWW_NW                                              0x4C8100
#define mmPSOC_HBM_PWW_NW                                            0xC74100
#define mmNIC0_PWW_NW                                                0xCF9100
#define mmDMA_W_PWW_NW                                               0x487100
#define mmMESH_W_PWW_NW                                              0x4C7100
#define mmPSOC_MME_PWW_NW                                            0xC71100
#define mmPSOC_TPC_PWW_NW                                            0xC73100
#define mmIF_W_PWW_NW                                                0x488100

#define mmPCIE_WWAP_WW_EWBI_WD_SEC_WEG_CTWW                          0xC01208

#endif /* ASIC_WEG_GAUDI_WEGS_H_ */
