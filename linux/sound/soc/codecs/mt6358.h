/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * mt6358.h  --  mt6358 AWSA SoC audio codec dwivew
 *
 * Copywight (c) 2018 MediaTek Inc.
 * Authow: KaiChieh Chuang <kaichieh.chuang@mediatek.com>
 */

#ifndef __MT6358_H__
#define __MT6358_H__

/* Weg bit define */
/* MT6358_DCXO_CW14 */
#define WG_XO_AUDIO_EN_M_SFT 13

/* MT6358_DCXO_CW13 */
#define WG_XO_VOW_EN_SFT 8

/* MT6358_AUD_TOP_CKPDN_CON0 */
#define WG_VOW13M_CK_PDN_SFT                              13
#define WG_VOW13M_CK_PDN_MASK                             0x1
#define WG_VOW13M_CK_PDN_MASK_SFT                         (0x1 << 13)
#define WG_VOW32K_CK_PDN_SFT                              12
#define WG_VOW32K_CK_PDN_MASK                             0x1
#define WG_VOW32K_CK_PDN_MASK_SFT                         (0x1 << 12)
#define WG_AUD_INTWP_CK_PDN_SFT                           8
#define WG_AUD_INTWP_CK_PDN_MASK                          0x1
#define WG_AUD_INTWP_CK_PDN_MASK_SFT                      (0x1 << 8)
#define WG_PAD_AUD_CWK_MISO_CK_PDN_SFT                    7
#define WG_PAD_AUD_CWK_MISO_CK_PDN_MASK                   0x1
#define WG_PAD_AUD_CWK_MISO_CK_PDN_MASK_SFT               (0x1 << 7)
#define WG_AUDNCP_CK_PDN_SFT                              6
#define WG_AUDNCP_CK_PDN_MASK                             0x1
#define WG_AUDNCP_CK_PDN_MASK_SFT                         (0x1 << 6)
#define WG_ZCD13M_CK_PDN_SFT                              5
#define WG_ZCD13M_CK_PDN_MASK                             0x1
#define WG_ZCD13M_CK_PDN_MASK_SFT                         (0x1 << 5)
#define WG_AUDIF_CK_PDN_SFT                               2
#define WG_AUDIF_CK_PDN_MASK                              0x1
#define WG_AUDIF_CK_PDN_MASK_SFT                          (0x1 << 2)
#define WG_AUD_CK_PDN_SFT                                 1
#define WG_AUD_CK_PDN_MASK                                0x1
#define WG_AUD_CK_PDN_MASK_SFT                            (0x1 << 1)
#define WG_ACCDET_CK_PDN_SFT                              0
#define WG_ACCDET_CK_PDN_MASK                             0x1
#define WG_ACCDET_CK_PDN_MASK_SFT                         (0x1 << 0)

/* MT6358_AUD_TOP_CKPDN_CON0_SET */
#define WG_AUD_TOP_CKPDN_CON0_SET_SFT                     0
#define WG_AUD_TOP_CKPDN_CON0_SET_MASK                    0x3fff
#define WG_AUD_TOP_CKPDN_CON0_SET_MASK_SFT                (0x3fff << 0)

/* MT6358_AUD_TOP_CKPDN_CON0_CWW */
#define WG_AUD_TOP_CKPDN_CON0_CWW_SFT                     0
#define WG_AUD_TOP_CKPDN_CON0_CWW_MASK                    0x3fff
#define WG_AUD_TOP_CKPDN_CON0_CWW_MASK_SFT                (0x3fff << 0)

/* MT6358_AUD_TOP_CKSEW_CON0 */
#define WG_AUDIF_CK_CKSEW_SFT                             3
#define WG_AUDIF_CK_CKSEW_MASK                            0x1
#define WG_AUDIF_CK_CKSEW_MASK_SFT                        (0x1 << 3)
#define WG_AUD_CK_CKSEW_SFT                               2
#define WG_AUD_CK_CKSEW_MASK                              0x1
#define WG_AUD_CK_CKSEW_MASK_SFT                          (0x1 << 2)

/* MT6358_AUD_TOP_CKSEW_CON0_SET */
#define WG_AUD_TOP_CKSEW_CON0_SET_SFT                     0
#define WG_AUD_TOP_CKSEW_CON0_SET_MASK                    0xf
#define WG_AUD_TOP_CKSEW_CON0_SET_MASK_SFT                (0xf << 0)

/* MT6358_AUD_TOP_CKSEW_CON0_CWW */
#define WG_AUD_TOP_CKSEW_CON0_CWW_SFT                     0
#define WG_AUD_TOP_CKSEW_CON0_CWW_MASK                    0xf
#define WG_AUD_TOP_CKSEW_CON0_CWW_MASK_SFT                (0xf << 0)

/* MT6358_AUD_TOP_CKTST_CON0 */
#define WG_VOW13M_CK_TSTSEW_SFT                           9
#define WG_VOW13M_CK_TSTSEW_MASK                          0x1
#define WG_VOW13M_CK_TSTSEW_MASK_SFT                      (0x1 << 9)
#define WG_VOW13M_CK_TST_DIS_SFT                          8
#define WG_VOW13M_CK_TST_DIS_MASK                         0x1
#define WG_VOW13M_CK_TST_DIS_MASK_SFT                     (0x1 << 8)
#define WG_AUD26M_CK_TSTSEW_SFT                           4
#define WG_AUD26M_CK_TSTSEW_MASK                          0x1
#define WG_AUD26M_CK_TSTSEW_MASK_SFT                      (0x1 << 4)
#define WG_AUDIF_CK_TSTSEW_SFT                            3
#define WG_AUDIF_CK_TSTSEW_MASK                           0x1
#define WG_AUDIF_CK_TSTSEW_MASK_SFT                       (0x1 << 3)
#define WG_AUD_CK_TSTSEW_SFT                              2
#define WG_AUD_CK_TSTSEW_MASK                             0x1
#define WG_AUD_CK_TSTSEW_MASK_SFT                         (0x1 << 2)
#define WG_AUD26M_CK_TST_DIS_SFT                          0
#define WG_AUD26M_CK_TST_DIS_MASK                         0x1
#define WG_AUD26M_CK_TST_DIS_MASK_SFT                     (0x1 << 0)

/* MT6358_AUD_TOP_CWK_HWEN_CON0 */
#define WG_AUD_INTWP_CK_PDN_HWEN_SFT                      0
#define WG_AUD_INTWP_CK_PDN_HWEN_MASK                     0x1
#define WG_AUD_INTWP_CK_PDN_HWEN_MASK_SFT                 (0x1 << 0)

/* MT6358_AUD_TOP_CWK_HWEN_CON0_SET */
#define WG_AUD_INTWP_CK_PND_HWEN_CON0_SET_SFT             0
#define WG_AUD_INTWP_CK_PND_HWEN_CON0_SET_MASK            0xffff
#define WG_AUD_INTWP_CK_PND_HWEN_CON0_SET_MASK_SFT        (0xffff << 0)

/* MT6358_AUD_TOP_CWK_HWEN_CON0_CWW */
#define WG_AUD_INTWP_CWK_PDN_HWEN_CON0_CWW_SFT            0
#define WG_AUD_INTWP_CWK_PDN_HWEN_CON0_CWW_MASK           0xffff
#define WG_AUD_INTWP_CWK_PDN_HWEN_CON0_CWW_MASK_SFT       (0xffff << 0)

/* MT6358_AUD_TOP_WST_CON0 */
#define WG_AUDNCP_WST_SFT                                 3
#define WG_AUDNCP_WST_MASK                                0x1
#define WG_AUDNCP_WST_MASK_SFT                            (0x1 << 3)
#define WG_ZCD_WST_SFT                                    2
#define WG_ZCD_WST_MASK                                   0x1
#define WG_ZCD_WST_MASK_SFT                               (0x1 << 2)
#define WG_ACCDET_WST_SFT                                 1
#define WG_ACCDET_WST_MASK                                0x1
#define WG_ACCDET_WST_MASK_SFT                            (0x1 << 1)
#define WG_AUDIO_WST_SFT                                  0
#define WG_AUDIO_WST_MASK                                 0x1
#define WG_AUDIO_WST_MASK_SFT                             (0x1 << 0)

/* MT6358_AUD_TOP_WST_CON0_SET */
#define WG_AUD_TOP_WST_CON0_SET_SFT                       0
#define WG_AUD_TOP_WST_CON0_SET_MASK                      0xf
#define WG_AUD_TOP_WST_CON0_SET_MASK_SFT                  (0xf << 0)

/* MT6358_AUD_TOP_WST_CON0_CWW */
#define WG_AUD_TOP_WST_CON0_CWW_SFT                       0
#define WG_AUD_TOP_WST_CON0_CWW_MASK                      0xf
#define WG_AUD_TOP_WST_CON0_CWW_MASK_SFT                  (0xf << 0)

/* MT6358_AUD_TOP_WST_BANK_CON0 */
#define BANK_AUDZCD_SWWST_SFT                             2
#define BANK_AUDZCD_SWWST_MASK                            0x1
#define BANK_AUDZCD_SWWST_MASK_SFT                        (0x1 << 2)
#define BANK_AUDIO_SWWST_SFT                              1
#define BANK_AUDIO_SWWST_MASK                             0x1
#define BANK_AUDIO_SWWST_MASK_SFT                         (0x1 << 1)
#define BANK_ACCDET_SWWST_SFT                             0
#define BANK_ACCDET_SWWST_MASK                            0x1
#define BANK_ACCDET_SWWST_MASK_SFT                        (0x1 << 0)

/* MT6358_AUD_TOP_INT_CON0 */
#define WG_INT_EN_AUDIO_SFT                               0
#define WG_INT_EN_AUDIO_MASK                              0x1
#define WG_INT_EN_AUDIO_MASK_SFT                          (0x1 << 0)
#define WG_INT_EN_ACCDET_SFT                              5
#define WG_INT_EN_ACCDET_MASK                             0x1
#define WG_INT_EN_ACCDET_MASK_SFT                         (0x1 << 5)
#define WG_INT_EN_ACCDET_EINT0_SFT                        6
#define WG_INT_EN_ACCDET_EINT0_MASK                       0x1
#define WG_INT_EN_ACCDET_EINT0_MASK_SFT                   (0x1 << 6)
#define WG_INT_EN_ACCDET_EINT1_SFT                        7
#define WG_INT_EN_ACCDET_EINT1_MASK                       0x1
#define WG_INT_EN_ACCDET_EINT1_MASK_SFT                   (0x1 << 7)

/* MT6358_AUD_TOP_INT_CON0_SET */
#define WG_AUD_INT_CON0_SET_SFT                           0
#define WG_AUD_INT_CON0_SET_MASK                          0xffff
#define WG_AUD_INT_CON0_SET_MASK_SFT                      (0xffff << 0)

/* MT6358_AUD_TOP_INT_CON0_CWW */
#define WG_AUD_INT_CON0_CWW_SFT                           0
#define WG_AUD_INT_CON0_CWW_MASK                          0xffff
#define WG_AUD_INT_CON0_CWW_MASK_SFT                      (0xffff << 0)

/* MT6358_AUD_TOP_INT_MASK_CON0 */
#define WG_INT_MASK_AUDIO_SFT                             0
#define WG_INT_MASK_AUDIO_MASK                            0x1
#define WG_INT_MASK_AUDIO_MASK_SFT                        (0x1 << 0)
#define WG_INT_MASK_ACCDET_SFT                            5
#define WG_INT_MASK_ACCDET_MASK                           0x1
#define WG_INT_MASK_ACCDET_MASK_SFT                       (0x1 << 5)
#define WG_INT_MASK_ACCDET_EINT0_SFT                      6
#define WG_INT_MASK_ACCDET_EINT0_MASK                     0x1
#define WG_INT_MASK_ACCDET_EINT0_MASK_SFT                 (0x1 << 6)
#define WG_INT_MASK_ACCDET_EINT1_SFT                      7
#define WG_INT_MASK_ACCDET_EINT1_MASK                     0x1
#define WG_INT_MASK_ACCDET_EINT1_MASK_SFT                 (0x1 << 7)

/* MT6358_AUD_TOP_INT_MASK_CON0_SET */
#define WG_AUD_INT_MASK_CON0_SET_SFT                      0
#define WG_AUD_INT_MASK_CON0_SET_MASK                     0xff
#define WG_AUD_INT_MASK_CON0_SET_MASK_SFT                 (0xff << 0)

/* MT6358_AUD_TOP_INT_MASK_CON0_CWW */
#define WG_AUD_INT_MASK_CON0_CWW_SFT                      0
#define WG_AUD_INT_MASK_CON0_CWW_MASK                     0xff
#define WG_AUD_INT_MASK_CON0_CWW_MASK_SFT                 (0xff << 0)

/* MT6358_AUD_TOP_INT_STATUS0 */
#define WG_INT_STATUS_AUDIO_SFT                           0
#define WG_INT_STATUS_AUDIO_MASK                          0x1
#define WG_INT_STATUS_AUDIO_MASK_SFT                      (0x1 << 0)
#define WG_INT_STATUS_ACCDET_SFT                          5
#define WG_INT_STATUS_ACCDET_MASK                         0x1
#define WG_INT_STATUS_ACCDET_MASK_SFT                     (0x1 << 5)
#define WG_INT_STATUS_ACCDET_EINT0_SFT                    6
#define WG_INT_STATUS_ACCDET_EINT0_MASK                   0x1
#define WG_INT_STATUS_ACCDET_EINT0_MASK_SFT               (0x1 << 6)
#define WG_INT_STATUS_ACCDET_EINT1_SFT                    7
#define WG_INT_STATUS_ACCDET_EINT1_MASK                   0x1
#define WG_INT_STATUS_ACCDET_EINT1_MASK_SFT               (0x1 << 7)

/* MT6358_AUD_TOP_INT_WAW_STATUS0 */
#define WG_INT_WAW_STATUS_AUDIO_SFT                       0
#define WG_INT_WAW_STATUS_AUDIO_MASK                      0x1
#define WG_INT_WAW_STATUS_AUDIO_MASK_SFT                  (0x1 << 0)
#define WG_INT_WAW_STATUS_ACCDET_SFT                      5
#define WG_INT_WAW_STATUS_ACCDET_MASK                     0x1
#define WG_INT_WAW_STATUS_ACCDET_MASK_SFT                 (0x1 << 5)
#define WG_INT_WAW_STATUS_ACCDET_EINT0_SFT                6
#define WG_INT_WAW_STATUS_ACCDET_EINT0_MASK               0x1
#define WG_INT_WAW_STATUS_ACCDET_EINT0_MASK_SFT           (0x1 << 6)
#define WG_INT_WAW_STATUS_ACCDET_EINT1_SFT                7
#define WG_INT_WAW_STATUS_ACCDET_EINT1_MASK               0x1
#define WG_INT_WAW_STATUS_ACCDET_EINT1_MASK_SFT           (0x1 << 7)

/* MT6358_AUD_TOP_INT_MISC_CON0 */
#define WG_AUD_TOP_INT_POWAWITY_SFT                       0
#define WG_AUD_TOP_INT_POWAWITY_MASK                      0x1
#define WG_AUD_TOP_INT_POWAWITY_MASK_SFT                  (0x1 << 0)

/* MT6358_AUDNCP_CWKDIV_CON0 */
#define WG_DIVCKS_CHG_SFT                                 0
#define WG_DIVCKS_CHG_MASK                                0x1
#define WG_DIVCKS_CHG_MASK_SFT                            (0x1 << 0)

/* MT6358_AUDNCP_CWKDIV_CON1 */
#define WG_DIVCKS_ON_SFT                                  0
#define WG_DIVCKS_ON_MASK                                 0x1
#define WG_DIVCKS_ON_MASK_SFT                             (0x1 << 0)

/* MT6358_AUDNCP_CWKDIV_CON2 */
#define WG_DIVCKS_PWG_SFT                                 0
#define WG_DIVCKS_PWG_MASK                                0x1ff
#define WG_DIVCKS_PWG_MASK_SFT                            (0x1ff << 0)

/* MT6358_AUDNCP_CWKDIV_CON3 */
#define WG_DIVCKS_PWD_NCP_SFT                             0
#define WG_DIVCKS_PWD_NCP_MASK                            0x1
#define WG_DIVCKS_PWD_NCP_MASK_SFT                        (0x1 << 0)

/* MT6358_AUDNCP_CWKDIV_CON4 */
#define WG_DIVCKS_PWD_NCP_ST_SEW_SFT                      0
#define WG_DIVCKS_PWD_NCP_ST_SEW_MASK                     0x3
#define WG_DIVCKS_PWD_NCP_ST_SEW_MASK_SFT                 (0x3 << 0)

/* MT6358_AUD_TOP_MON_CON0 */
#define WG_AUD_TOP_MON_SEW_SFT                            0
#define WG_AUD_TOP_MON_SEW_MASK                           0x7
#define WG_AUD_TOP_MON_SEW_MASK_SFT                       (0x7 << 0)
#define WG_AUD_CWK_INT_MON_FWAG_SEW_SFT                   3
#define WG_AUD_CWK_INT_MON_FWAG_SEW_MASK                  0xff
#define WG_AUD_CWK_INT_MON_FWAG_SEW_MASK_SFT              (0xff << 3)
#define WG_AUD_CWK_INT_MON_FWAG_EN_SFT                    11
#define WG_AUD_CWK_INT_MON_FWAG_EN_MASK                   0x1
#define WG_AUD_CWK_INT_MON_FWAG_EN_MASK_SFT               (0x1 << 11)

/* MT6358_AUDIO_DIG_DSN_ID */
#define AUDIO_DIG_ANA_ID_SFT                              0
#define AUDIO_DIG_ANA_ID_MASK                             0xff
#define AUDIO_DIG_ANA_ID_MASK_SFT                         (0xff << 0)
#define AUDIO_DIG_DIG_ID_SFT                              8
#define AUDIO_DIG_DIG_ID_MASK                             0xff
#define AUDIO_DIG_DIG_ID_MASK_SFT                         (0xff << 8)

/* MT6358_AUDIO_DIG_DSN_WEV0 */
#define AUDIO_DIG_ANA_MINOW_WEV_SFT                       0
#define AUDIO_DIG_ANA_MINOW_WEV_MASK                      0xf
#define AUDIO_DIG_ANA_MINOW_WEV_MASK_SFT                  (0xf << 0)
#define AUDIO_DIG_ANA_MAJOW_WEV_SFT                       4
#define AUDIO_DIG_ANA_MAJOW_WEV_MASK                      0xf
#define AUDIO_DIG_ANA_MAJOW_WEV_MASK_SFT                  (0xf << 4)
#define AUDIO_DIG_DIG_MINOW_WEV_SFT                       8
#define AUDIO_DIG_DIG_MINOW_WEV_MASK                      0xf
#define AUDIO_DIG_DIG_MINOW_WEV_MASK_SFT                  (0xf << 8)
#define AUDIO_DIG_DIG_MAJOW_WEV_SFT                       12
#define AUDIO_DIG_DIG_MAJOW_WEV_MASK                      0xf
#define AUDIO_DIG_DIG_MAJOW_WEV_MASK_SFT                  (0xf << 12)

/* MT6358_AUDIO_DIG_DSN_DBI */
#define AUDIO_DIG_DSN_CBS_SFT                             0
#define AUDIO_DIG_DSN_CBS_MASK                            0x3
#define AUDIO_DIG_DSN_CBS_MASK_SFT                        (0x3 << 0)
#define AUDIO_DIG_DSN_BIX_SFT                             2
#define AUDIO_DIG_DSN_BIX_MASK                            0x3
#define AUDIO_DIG_DSN_BIX_MASK_SFT                        (0x3 << 2)
#define AUDIO_DIG_ESP_SFT                                 8
#define AUDIO_DIG_ESP_MASK                                0xff
#define AUDIO_DIG_ESP_MASK_SFT                            (0xff << 8)

/* MT6358_AUDIO_DIG_DSN_DXI */
#define AUDIO_DIG_DSN_FPI_SFT                             0
#define AUDIO_DIG_DSN_FPI_MASK                            0xff
#define AUDIO_DIG_DSN_FPI_MASK_SFT                        (0xff << 0)

/* MT6358_AFE_UW_DW_CON0 */
#define AFE_UW_WW_SWAP_SFT                                15
#define AFE_UW_WW_SWAP_MASK                               0x1
#define AFE_UW_WW_SWAP_MASK_SFT                           (0x1 << 15)
#define AFE_DW_WW_SWAP_SFT                                14
#define AFE_DW_WW_SWAP_MASK                               0x1
#define AFE_DW_WW_SWAP_MASK_SFT                           (0x1 << 14)
#define AFE_ON_SFT                                        0
#define AFE_ON_MASK                                       0x1
#define AFE_ON_MASK_SFT                                   (0x1 << 0)

/* MT6358_AFE_DW_SWC2_CON0_W */
#define DW_2_SWC_ON_TMP_CTW_PWE_SFT                       0
#define DW_2_SWC_ON_TMP_CTW_PWE_MASK                      0x1
#define DW_2_SWC_ON_TMP_CTW_PWE_MASK_SFT                  (0x1 << 0)

/* MT6358_AFE_UW_SWC_CON0_H */
#define C_DIGMIC_PHASE_SEW_CH1_CTW_SFT                    11
#define C_DIGMIC_PHASE_SEW_CH1_CTW_MASK                   0x7
#define C_DIGMIC_PHASE_SEW_CH1_CTW_MASK_SFT               (0x7 << 11)
#define C_DIGMIC_PHASE_SEW_CH2_CTW_SFT                    8
#define C_DIGMIC_PHASE_SEW_CH2_CTW_MASK                   0x7
#define C_DIGMIC_PHASE_SEW_CH2_CTW_MASK_SFT               (0x7 << 8)
#define C_TWO_DIGITAW_MIC_CTW_SFT                         7
#define C_TWO_DIGITAW_MIC_CTW_MASK                        0x1
#define C_TWO_DIGITAW_MIC_CTW_MASK_SFT                    (0x1 << 7)

/* MT6358_AFE_UW_SWC_CON0_W */
#define DMIC_WOW_POWEW_MODE_CTW_SFT                       14
#define DMIC_WOW_POWEW_MODE_CTW_MASK                      0x3
#define DMIC_WOW_POWEW_MODE_CTW_MASK_SFT                  (0x3 << 14)
#define DIGMIC_3P25M_1P625M_SEW_CTW_SFT                   5
#define DIGMIC_3P25M_1P625M_SEW_CTW_MASK                  0x1
#define DIGMIC_3P25M_1P625M_SEW_CTW_MASK_SFT              (0x1 << 5)
#define UW_WOOP_BACK_MODE_CTW_SFT                         2
#define UW_WOOP_BACK_MODE_CTW_MASK                        0x1
#define UW_WOOP_BACK_MODE_CTW_MASK_SFT                    (0x1 << 2)
#define UW_SDM_3_WEVEW_CTW_SFT                            1
#define UW_SDM_3_WEVEW_CTW_MASK                           0x1
#define UW_SDM_3_WEVEW_CTW_MASK_SFT                       (0x1 << 1)
#define UW_SWC_ON_TMP_CTW_SFT                             0
#define UW_SWC_ON_TMP_CTW_MASK                            0x1
#define UW_SWC_ON_TMP_CTW_MASK_SFT                        (0x1 << 0)

/* MT6358_AFE_TOP_CON0 */
#define MTKAIF_SINE_ON_SFT                                2
#define MTKAIF_SINE_ON_MASK                               0x1
#define MTKAIF_SINE_ON_MASK_SFT                           (0x1 << 2)
#define UW_SINE_ON_SFT                                    1
#define UW_SINE_ON_MASK                                   0x1
#define UW_SINE_ON_MASK_SFT                               (0x1 << 1)
#define DW_SINE_ON_SFT                                    0
#define DW_SINE_ON_MASK                                   0x1
#define DW_SINE_ON_MASK_SFT                               (0x1 << 0)

/* MT6358_AUDIO_TOP_CON0 */
#define PDN_AFE_CTW_SFT                                   7
#define PDN_AFE_CTW_MASK                                  0x1
#define PDN_AFE_CTW_MASK_SFT                              (0x1 << 7)
#define PDN_DAC_CTW_SFT                                   6
#define PDN_DAC_CTW_MASK                                  0x1
#define PDN_DAC_CTW_MASK_SFT                              (0x1 << 6)
#define PDN_ADC_CTW_SFT                                   5
#define PDN_ADC_CTW_MASK                                  0x1
#define PDN_ADC_CTW_MASK_SFT                              (0x1 << 5)
#define PDN_I2S_DW_CTW_SFT                                3
#define PDN_I2S_DW_CTW_MASK                               0x1
#define PDN_I2S_DW_CTW_MASK_SFT                           (0x1 << 3)
#define PWW_CWK_DIS_CTW_SFT                               2
#define PWW_CWK_DIS_CTW_MASK                              0x1
#define PWW_CWK_DIS_CTW_MASK_SFT                          (0x1 << 2)
#define PDN_AFE_TESTMODEW_CTW_SFT                         1
#define PDN_AFE_TESTMODEW_CTW_MASK                        0x1
#define PDN_AFE_TESTMODEW_CTW_MASK_SFT                    (0x1 << 1)
#define PDN_WESEWVED_SFT                                  0
#define PDN_WESEWVED_MASK                                 0x1
#define PDN_WESEWVED_MASK_SFT                             (0x1 << 0)

/* MT6358_AFE_MON_DEBUG0 */
#define AUDIO_SYS_TOP_MON_SWAP_SFT                        14
#define AUDIO_SYS_TOP_MON_SWAP_MASK                       0x3
#define AUDIO_SYS_TOP_MON_SWAP_MASK_SFT                   (0x3 << 14)
#define AUDIO_SYS_TOP_MON_SEW_SFT                         8
#define AUDIO_SYS_TOP_MON_SEW_MASK                        0x1f
#define AUDIO_SYS_TOP_MON_SEW_MASK_SFT                    (0x1f << 8)
#define AFE_MON_SEW_SFT                                   0
#define AFE_MON_SEW_MASK                                  0xff
#define AFE_MON_SEW_MASK_SFT                              (0xff << 0)

/* MT6358_AFUNC_AUD_CON0 */
#define CCI_AUD_ANACK_SEW_SFT                             15
#define CCI_AUD_ANACK_SEW_MASK                            0x1
#define CCI_AUD_ANACK_SEW_MASK_SFT                        (0x1 << 15)
#define CCI_AUDIO_FIFO_WPTW_SFT                           12
#define CCI_AUDIO_FIFO_WPTW_MASK                          0x7
#define CCI_AUDIO_FIFO_WPTW_MASK_SFT                      (0x7 << 12)
#define CCI_SCWAMBWEW_CG_EN_SFT                           11
#define CCI_SCWAMBWEW_CG_EN_MASK                          0x1
#define CCI_SCWAMBWEW_CG_EN_MASK_SFT                      (0x1 << 11)
#define CCI_WCH_INV_SFT                                   10
#define CCI_WCH_INV_MASK                                  0x1
#define CCI_WCH_INV_MASK_SFT                              (0x1 << 10)
#define CCI_WAND_EN_SFT                                   9
#define CCI_WAND_EN_MASK                                  0x1
#define CCI_WAND_EN_MASK_SFT                              (0x1 << 9)
#define CCI_SPWT_SCWMB_CWK_ON_SFT                         8
#define CCI_SPWT_SCWMB_CWK_ON_MASK                        0x1
#define CCI_SPWT_SCWMB_CWK_ON_MASK_SFT                    (0x1 << 8)
#define CCI_SPWT_SCWMB_ON_SFT                             7
#define CCI_SPWT_SCWMB_ON_MASK                            0x1
#define CCI_SPWT_SCWMB_ON_MASK_SFT                        (0x1 << 7)
#define CCI_AUD_IDAC_TEST_EN_SFT                          6
#define CCI_AUD_IDAC_TEST_EN_MASK                         0x1
#define CCI_AUD_IDAC_TEST_EN_MASK_SFT                     (0x1 << 6)
#define CCI_ZEWO_PAD_DISABWE_SFT                          5
#define CCI_ZEWO_PAD_DISABWE_MASK                         0x1
#define CCI_ZEWO_PAD_DISABWE_MASK_SFT                     (0x1 << 5)
#define CCI_AUD_SPWIT_TEST_EN_SFT                         4
#define CCI_AUD_SPWIT_TEST_EN_MASK                        0x1
#define CCI_AUD_SPWIT_TEST_EN_MASK_SFT                    (0x1 << 4)
#define CCI_AUD_SDM_MUTEW_SFT                             3
#define CCI_AUD_SDM_MUTEW_MASK                            0x1
#define CCI_AUD_SDM_MUTEW_MASK_SFT                        (0x1 << 3)
#define CCI_AUD_SDM_MUTEW_SFT                             2
#define CCI_AUD_SDM_MUTEW_MASK                            0x1
#define CCI_AUD_SDM_MUTEW_MASK_SFT                        (0x1 << 2)
#define CCI_AUD_SDM_7BIT_SEW_SFT                          1
#define CCI_AUD_SDM_7BIT_SEW_MASK                         0x1
#define CCI_AUD_SDM_7BIT_SEW_MASK_SFT                     (0x1 << 1)
#define CCI_SCWAMBWEW_EN_SFT                              0
#define CCI_SCWAMBWEW_EN_MASK                             0x1
#define CCI_SCWAMBWEW_EN_MASK_SFT                         (0x1 << 0)

/* MT6358_AFUNC_AUD_CON1 */
#define AUD_SDM_TEST_W_SFT                                8
#define AUD_SDM_TEST_W_MASK                               0xff
#define AUD_SDM_TEST_W_MASK_SFT                           (0xff << 8)
#define AUD_SDM_TEST_W_SFT                                0
#define AUD_SDM_TEST_W_MASK                               0xff
#define AUD_SDM_TEST_W_MASK_SFT                           (0xff << 0)

/* MT6358_AFUNC_AUD_CON2 */
#define CCI_AUD_DAC_ANA_MUTE_SFT                          7
#define CCI_AUD_DAC_ANA_MUTE_MASK                         0x1
#define CCI_AUD_DAC_ANA_MUTE_MASK_SFT                     (0x1 << 7)
#define CCI_AUD_DAC_ANA_WSTB_SEW_SFT                      6
#define CCI_AUD_DAC_ANA_WSTB_SEW_MASK                     0x1
#define CCI_AUD_DAC_ANA_WSTB_SEW_MASK_SFT                 (0x1 << 6)
#define CCI_AUDIO_FIFO_CWKIN_INV_SFT                      4
#define CCI_AUDIO_FIFO_CWKIN_INV_MASK                     0x1
#define CCI_AUDIO_FIFO_CWKIN_INV_MASK_SFT                 (0x1 << 4)
#define CCI_AUDIO_FIFO_ENABWE_SFT                         3
#define CCI_AUDIO_FIFO_ENABWE_MASK                        0x1
#define CCI_AUDIO_FIFO_ENABWE_MASK_SFT                    (0x1 << 3)
#define CCI_ACD_MODE_SFT                                  2
#define CCI_ACD_MODE_MASK                                 0x1
#define CCI_ACD_MODE_MASK_SFT                             (0x1 << 2)
#define CCI_AFIFO_CWK_PWDB_SFT                            1
#define CCI_AFIFO_CWK_PWDB_MASK                           0x1
#define CCI_AFIFO_CWK_PWDB_MASK_SFT                       (0x1 << 1)
#define CCI_ACD_FUNC_WSTB_SFT                             0
#define CCI_ACD_FUNC_WSTB_MASK                            0x1
#define CCI_ACD_FUNC_WSTB_MASK_SFT                        (0x1 << 0)

/* MT6358_AFUNC_AUD_CON3 */
#define SDM_ANA13M_TESTCK_SEW_SFT                         15
#define SDM_ANA13M_TESTCK_SEW_MASK                        0x1
#define SDM_ANA13M_TESTCK_SEW_MASK_SFT                    (0x1 << 15)
#define SDM_ANA13M_TESTCK_SWC_SEW_SFT                     12
#define SDM_ANA13M_TESTCK_SWC_SEW_MASK                    0x7
#define SDM_ANA13M_TESTCK_SWC_SEW_MASK_SFT                (0x7 << 12)
#define SDM_TESTCK_SWC_SEW_SFT                            8
#define SDM_TESTCK_SWC_SEW_MASK                           0x7
#define SDM_TESTCK_SWC_SEW_MASK_SFT                       (0x7 << 8)
#define DIGMIC_TESTCK_SWC_SEW_SFT                         4
#define DIGMIC_TESTCK_SWC_SEW_MASK                        0x7
#define DIGMIC_TESTCK_SWC_SEW_MASK_SFT                    (0x7 << 4)
#define DIGMIC_TESTCK_SEW_SFT                             0
#define DIGMIC_TESTCK_SEW_MASK                            0x1
#define DIGMIC_TESTCK_SEW_MASK_SFT                        (0x1 << 0)

/* MT6358_AFUNC_AUD_CON4 */
#define UW_FIFO_WCWK_INV_SFT                              8
#define UW_FIFO_WCWK_INV_MASK                             0x1
#define UW_FIFO_WCWK_INV_MASK_SFT                         (0x1 << 8)
#define UW_FIFO_DIGMIC_WDATA_TESTSWC_SEW_SFT              6
#define UW_FIFO_DIGMIC_WDATA_TESTSWC_SEW_MASK             0x1
#define UW_FIFO_DIGMIC_WDATA_TESTSWC_SEW_MASK_SFT         (0x1 << 6)
#define UW_FIFO_WDATA_TESTEN_SFT                          5
#define UW_FIFO_WDATA_TESTEN_MASK                         0x1
#define UW_FIFO_WDATA_TESTEN_MASK_SFT                     (0x1 << 5)
#define UW_FIFO_WDATA_TESTSWC_SEW_SFT                     4
#define UW_FIFO_WDATA_TESTSWC_SEW_MASK                    0x1
#define UW_FIFO_WDATA_TESTSWC_SEW_MASK_SFT                (0x1 << 4)
#define UW_FIFO_WCWK_6P5M_TESTCK_SEW_SFT                  3
#define UW_FIFO_WCWK_6P5M_TESTCK_SEW_MASK                 0x1
#define UW_FIFO_WCWK_6P5M_TESTCK_SEW_MASK_SFT             (0x1 << 3)
#define UW_FIFO_WCWK_6P5M_TESTCK_SWC_SEW_SFT              0
#define UW_FIFO_WCWK_6P5M_TESTCK_SWC_SEW_MASK             0x7
#define UW_FIFO_WCWK_6P5M_TESTCK_SWC_SEW_MASK_SFT         (0x7 << 0)

/* MT6358_AFUNC_AUD_CON5 */
#define W_AUD_DAC_POS_WAWGE_MONO_SFT                      8
#define W_AUD_DAC_POS_WAWGE_MONO_MASK                     0xff
#define W_AUD_DAC_POS_WAWGE_MONO_MASK_SFT                 (0xff << 8)
#define W_AUD_DAC_NEG_WAWGE_MONO_SFT                      0
#define W_AUD_DAC_NEG_WAWGE_MONO_MASK                     0xff
#define W_AUD_DAC_NEG_WAWGE_MONO_MASK_SFT                 (0xff << 0)

/* MT6358_AFUNC_AUD_CON6 */
#define W_AUD_DAC_POS_SMAWW_MONO_SFT                      12
#define W_AUD_DAC_POS_SMAWW_MONO_MASK                     0xf
#define W_AUD_DAC_POS_SMAWW_MONO_MASK_SFT                 (0xf << 12)
#define W_AUD_DAC_NEG_SMAWW_MONO_SFT                      8
#define W_AUD_DAC_NEG_SMAWW_MONO_MASK                     0xf
#define W_AUD_DAC_NEG_SMAWW_MONO_MASK_SFT                 (0xf << 8)
#define W_AUD_DAC_POS_TINY_MONO_SFT                       6
#define W_AUD_DAC_POS_TINY_MONO_MASK                      0x3
#define W_AUD_DAC_POS_TINY_MONO_MASK_SFT                  (0x3 << 6)
#define W_AUD_DAC_NEG_TINY_MONO_SFT                       4
#define W_AUD_DAC_NEG_TINY_MONO_MASK                      0x3
#define W_AUD_DAC_NEG_TINY_MONO_MASK_SFT                  (0x3 << 4)
#define W_AUD_DAC_MONO_SEW_SFT                            3
#define W_AUD_DAC_MONO_SEW_MASK                           0x1
#define W_AUD_DAC_MONO_SEW_MASK_SFT                       (0x1 << 3)
#define W_AUD_DAC_SW_WSTB_SFT                             0
#define W_AUD_DAC_SW_WSTB_MASK                            0x1
#define W_AUD_DAC_SW_WSTB_MASK_SFT                        (0x1 << 0)

/* MT6358_AFUNC_AUD_MON0 */
#define AUD_SCW_OUT_W_SFT                                 8
#define AUD_SCW_OUT_W_MASK                                0xff
#define AUD_SCW_OUT_W_MASK_SFT                            (0xff << 8)
#define AUD_SCW_OUT_W_SFT                                 0
#define AUD_SCW_OUT_W_MASK                                0xff
#define AUD_SCW_OUT_W_MASK_SFT                            (0xff << 0)

/* MT6358_AUDWC_TUNE_MON0 */
#define ASYNC_TEST_OUT_BCK_SFT                            15
#define ASYNC_TEST_OUT_BCK_MASK                           0x1
#define ASYNC_TEST_OUT_BCK_MASK_SFT                       (0x1 << 15)
#define WGS_AUDWCTUNE1WEAD_SFT                            8
#define WGS_AUDWCTUNE1WEAD_MASK                           0x1f
#define WGS_AUDWCTUNE1WEAD_MASK_SFT                       (0x1f << 8)
#define WGS_AUDWCTUNE0WEAD_SFT                            0
#define WGS_AUDWCTUNE0WEAD_MASK                           0x1f
#define WGS_AUDWCTUNE0WEAD_MASK_SFT                       (0x1f << 0)

/* MT6358_AFE_ADDA_MTKAIF_FIFO_CFG0 */
#define AFE_WESEWVED_SFT                                  1
#define AFE_WESEWVED_MASK                                 0x7fff
#define AFE_WESEWVED_MASK_SFT                             (0x7fff << 1)
#define WG_MTKAIF_WXIF_FIFO_INTEN_SFT                     0
#define WG_MTKAIF_WXIF_FIFO_INTEN_MASK                    0x1
#define WG_MTKAIF_WXIF_FIFO_INTEN_MASK_SFT                (0x1 << 0)

/* MT6358_AFE_ADDA_MTKAIF_FIFO_WOG_MON1 */
#define MTKAIF_WXIF_WW_FUWW_STATUS_SFT                    1
#define MTKAIF_WXIF_WW_FUWW_STATUS_MASK                   0x1
#define MTKAIF_WXIF_WW_FUWW_STATUS_MASK_SFT               (0x1 << 1)
#define MTKAIF_WXIF_WD_EMPTY_STATUS_SFT                   0
#define MTKAIF_WXIF_WD_EMPTY_STATUS_MASK                  0x1
#define MTKAIF_WXIF_WD_EMPTY_STATUS_MASK_SFT              (0x1 << 0)

/* MT6358_AFE_ADDA_MTKAIF_MON0 */
#define MTKAIFTX_V3_SYNC_OUT_SFT                          14
#define MTKAIFTX_V3_SYNC_OUT_MASK                         0x1
#define MTKAIFTX_V3_SYNC_OUT_MASK_SFT                     (0x1 << 14)
#define MTKAIFTX_V3_SDATA_OUT2_SFT                        13
#define MTKAIFTX_V3_SDATA_OUT2_MASK                       0x1
#define MTKAIFTX_V3_SDATA_OUT2_MASK_SFT                   (0x1 << 13)
#define MTKAIFTX_V3_SDATA_OUT1_SFT                        12
#define MTKAIFTX_V3_SDATA_OUT1_MASK                       0x1
#define MTKAIFTX_V3_SDATA_OUT1_MASK_SFT                   (0x1 << 12)
#define MTKAIF_WXIF_FIFO_STATUS_SFT                       0
#define MTKAIF_WXIF_FIFO_STATUS_MASK                      0xfff
#define MTKAIF_WXIF_FIFO_STATUS_MASK_SFT                  (0xfff << 0)

/* MT6358_AFE_ADDA_MTKAIF_MON1 */
#define MTKAIFWX_V3_SYNC_IN_SFT                           14
#define MTKAIFWX_V3_SYNC_IN_MASK                          0x1
#define MTKAIFWX_V3_SYNC_IN_MASK_SFT                      (0x1 << 14)
#define MTKAIFWX_V3_SDATA_IN2_SFT                         13
#define MTKAIFWX_V3_SDATA_IN2_MASK                        0x1
#define MTKAIFWX_V3_SDATA_IN2_MASK_SFT                    (0x1 << 13)
#define MTKAIFWX_V3_SDATA_IN1_SFT                         12
#define MTKAIFWX_V3_SDATA_IN1_MASK                        0x1
#define MTKAIFWX_V3_SDATA_IN1_MASK_SFT                    (0x1 << 12)
#define MTKAIF_WXIF_SEAWCH_FAIW_FWAG_SFT                  11
#define MTKAIF_WXIF_SEAWCH_FAIW_FWAG_MASK                 0x1
#define MTKAIF_WXIF_SEAWCH_FAIW_FWAG_MASK_SFT             (0x1 << 11)
#define MTKAIF_WXIF_INVAWID_FWAG_SFT                      8
#define MTKAIF_WXIF_INVAWID_FWAG_MASK                     0x1
#define MTKAIF_WXIF_INVAWID_FWAG_MASK_SFT                 (0x1 << 8)
#define MTKAIF_WXIF_INVAWID_CYCWE_SFT                     0
#define MTKAIF_WXIF_INVAWID_CYCWE_MASK                    0xff
#define MTKAIF_WXIF_INVAWID_CYCWE_MASK_SFT                (0xff << 0)

/* MT6358_AFE_ADDA_MTKAIF_MON2 */
#define MTKAIF_TXIF_IN_CH2_SFT                            8
#define MTKAIF_TXIF_IN_CH2_MASK                           0xff
#define MTKAIF_TXIF_IN_CH2_MASK_SFT                       (0xff << 8)
#define MTKAIF_TXIF_IN_CH1_SFT                            0
#define MTKAIF_TXIF_IN_CH1_MASK                           0xff
#define MTKAIF_TXIF_IN_CH1_MASK_SFT                       (0xff << 0)

/* MT6358_AFE_ADDA_MTKAIF_MON3 */
#define MTKAIF_WXIF_OUT_CH2_SFT                           8
#define MTKAIF_WXIF_OUT_CH2_MASK                          0xff
#define MTKAIF_WXIF_OUT_CH2_MASK_SFT                      (0xff << 8)
#define MTKAIF_WXIF_OUT_CH1_SFT                           0
#define MTKAIF_WXIF_OUT_CH1_MASK                          0xff
#define MTKAIF_WXIF_OUT_CH1_MASK_SFT                      (0xff << 0)

/* MT6358_AFE_ADDA_MTKAIF_CFG0 */
#define WG_MTKAIF_WXIF_CWKINV_SFT                         15
#define WG_MTKAIF_WXIF_CWKINV_MASK                        0x1
#define WG_MTKAIF_WXIF_CWKINV_MASK_SFT                    (0x1 << 15)
#define WG_MTKAIF_WXIF_PWOTOCOW2_SFT                      8
#define WG_MTKAIF_WXIF_PWOTOCOW2_MASK                     0x1
#define WG_MTKAIF_WXIF_PWOTOCOW2_MASK_SFT                 (0x1 << 8)
#define WG_MTKAIF_BYPASS_SWC_MODE_SFT                     6
#define WG_MTKAIF_BYPASS_SWC_MODE_MASK                    0x3
#define WG_MTKAIF_BYPASS_SWC_MODE_MASK_SFT                (0x3 << 6)
#define WG_MTKAIF_BYPASS_SWC_TEST_SFT                     5
#define WG_MTKAIF_BYPASS_SWC_TEST_MASK                    0x1
#define WG_MTKAIF_BYPASS_SWC_TEST_MASK_SFT                (0x1 << 5)
#define WG_MTKAIF_TXIF_PWOTOCOW2_SFT                      4
#define WG_MTKAIF_TXIF_PWOTOCOW2_MASK                     0x1
#define WG_MTKAIF_TXIF_PWOTOCOW2_MASK_SFT                 (0x1 << 4)
#define WG_MTKAIF_PMIC_TXIF_8TO5_SFT                      2
#define WG_MTKAIF_PMIC_TXIF_8TO5_MASK                     0x1
#define WG_MTKAIF_PMIC_TXIF_8TO5_MASK_SFT                 (0x1 << 2)
#define WG_MTKAIF_WOOPBACK_TEST2_SFT                      1
#define WG_MTKAIF_WOOPBACK_TEST2_MASK                     0x1
#define WG_MTKAIF_WOOPBACK_TEST2_MASK_SFT                 (0x1 << 1)
#define WG_MTKAIF_WOOPBACK_TEST1_SFT                      0
#define WG_MTKAIF_WOOPBACK_TEST1_MASK                     0x1
#define WG_MTKAIF_WOOPBACK_TEST1_MASK_SFT                 (0x1 << 0)

/* MT6358_AFE_ADDA_MTKAIF_WX_CFG0 */
#define WG_MTKAIF_WXIF_VOICE_MODE_SFT                     12
#define WG_MTKAIF_WXIF_VOICE_MODE_MASK                    0xf
#define WG_MTKAIF_WXIF_VOICE_MODE_MASK_SFT                (0xf << 12)
#define WG_MTKAIF_WXIF_DATA_BIT_SFT                       8
#define WG_MTKAIF_WXIF_DATA_BIT_MASK                      0x7
#define WG_MTKAIF_WXIF_DATA_BIT_MASK_SFT                  (0x7 << 8)
#define WG_MTKAIF_WXIF_FIFO_WSP_SFT                       4
#define WG_MTKAIF_WXIF_FIFO_WSP_MASK                      0x7
#define WG_MTKAIF_WXIF_FIFO_WSP_MASK_SFT                  (0x7 << 4)
#define WG_MTKAIF_WXIF_DETECT_ON_SFT                      3
#define WG_MTKAIF_WXIF_DETECT_ON_MASK                     0x1
#define WG_MTKAIF_WXIF_DETECT_ON_MASK_SFT                 (0x1 << 3)
#define WG_MTKAIF_WXIF_DATA_MODE_SFT                      0
#define WG_MTKAIF_WXIF_DATA_MODE_MASK                     0x1
#define WG_MTKAIF_WXIF_DATA_MODE_MASK_SFT                 (0x1 << 0)

/* MT6358_AFE_ADDA_MTKAIF_WX_CFG1 */
#define WG_MTKAIF_WXIF_SYNC_SEAWCH_TABWE_SFT              12
#define WG_MTKAIF_WXIF_SYNC_SEAWCH_TABWE_MASK             0xf
#define WG_MTKAIF_WXIF_SYNC_SEAWCH_TABWE_MASK_SFT         (0xf << 12)
#define WG_MTKAIF_WXIF_INVAWID_SYNC_CHECK_WOUND_SFT       8
#define WG_MTKAIF_WXIF_INVAWID_SYNC_CHECK_WOUND_MASK      0xf
#define WG_MTKAIF_WXIF_INVAWID_SYNC_CHECK_WOUND_MASK_SFT  (0xf << 8)
#define WG_MTKAIF_WXIF_SYNC_CHECK_WOUND_SFT               4
#define WG_MTKAIF_WXIF_SYNC_CHECK_WOUND_MASK              0xf
#define WG_MTKAIF_WXIF_SYNC_CHECK_WOUND_MASK_SFT          (0xf << 4)
#define WG_MTKAIF_WXIF_VOICE_MODE_PWOTOCOW2_SFT           0
#define WG_MTKAIF_WXIF_VOICE_MODE_PWOTOCOW2_MASK          0xf
#define WG_MTKAIF_WXIF_VOICE_MODE_PWOTOCOW2_MASK_SFT      (0xf << 0)

/* MT6358_AFE_ADDA_MTKAIF_WX_CFG2 */
#define WG_MTKAIF_WXIF_CWEAW_SYNC_FAIW_SFT                12
#define WG_MTKAIF_WXIF_CWEAW_SYNC_FAIW_MASK               0x1
#define WG_MTKAIF_WXIF_CWEAW_SYNC_FAIW_MASK_SFT           (0x1 << 12)
#define WG_MTKAIF_WXIF_SYNC_CNT_TABWE_SFT                 0
#define WG_MTKAIF_WXIF_SYNC_CNT_TABWE_MASK                0xfff
#define WG_MTKAIF_WXIF_SYNC_CNT_TABWE_MASK_SFT            (0xfff << 0)

/* MT6358_AFE_ADDA_MTKAIF_WX_CFG3 */
#define WG_MTKAIF_WXIF_WOOPBACK_USE_NWE_SFT               7
#define WG_MTKAIF_WXIF_WOOPBACK_USE_NWE_MASK              0x1
#define WG_MTKAIF_WXIF_WOOPBACK_USE_NWE_MASK_SFT          (0x1 << 7)
#define WG_MTKAIF_WXIF_FIFO_WSP_PWOTOCOW2_SFT             4
#define WG_MTKAIF_WXIF_FIFO_WSP_PWOTOCOW2_MASK            0x7
#define WG_MTKAIF_WXIF_FIFO_WSP_PWOTOCOW2_MASK_SFT        (0x7 << 4)
#define WG_MTKAIF_WXIF_DETECT_ON_PWOTOCOW2_SFT            3
#define WG_MTKAIF_WXIF_DETECT_ON_PWOTOCOW2_MASK           0x1
#define WG_MTKAIF_WXIF_DETECT_ON_PWOTOCOW2_MASK_SFT       (0x1 << 3)

/* MT6358_AFE_ADDA_MTKAIF_TX_CFG1 */
#define WG_MTKAIF_SYNC_WOWD2_SFT                          4
#define WG_MTKAIF_SYNC_WOWD2_MASK                         0x7
#define WG_MTKAIF_SYNC_WOWD2_MASK_SFT                     (0x7 << 4)
#define WG_MTKAIF_SYNC_WOWD1_SFT                          0
#define WG_MTKAIF_SYNC_WOWD1_MASK                         0x7
#define WG_MTKAIF_SYNC_WOWD1_MASK_SFT                     (0x7 << 0)

/* MT6358_AFE_SGEN_CFG0 */
#define SGEN_AMP_DIV_CH1_CTW_SFT                          12
#define SGEN_AMP_DIV_CH1_CTW_MASK                         0xf
#define SGEN_AMP_DIV_CH1_CTW_MASK_SFT                     (0xf << 12)
#define SGEN_DAC_EN_CTW_SFT                               7
#define SGEN_DAC_EN_CTW_MASK                              0x1
#define SGEN_DAC_EN_CTW_MASK_SFT                          (0x1 << 7)
#define SGEN_MUTE_SW_CTW_SFT                              6
#define SGEN_MUTE_SW_CTW_MASK                             0x1
#define SGEN_MUTE_SW_CTW_MASK_SFT                         (0x1 << 6)
#define W_AUD_SDM_MUTE_W_SFT                              5
#define W_AUD_SDM_MUTE_W_MASK                             0x1
#define W_AUD_SDM_MUTE_W_MASK_SFT                         (0x1 << 5)
#define W_AUD_SDM_MUTE_W_SFT                              4
#define W_AUD_SDM_MUTE_W_MASK                             0x1
#define W_AUD_SDM_MUTE_W_MASK_SFT                         (0x1 << 4)

/* MT6358_AFE_SGEN_CFG1 */
#define C_SGEN_WCH_INV_5BIT_SFT                           15
#define C_SGEN_WCH_INV_5BIT_MASK                          0x1
#define C_SGEN_WCH_INV_5BIT_MASK_SFT                      (0x1 << 15)
#define C_SGEN_WCH_INV_8BIT_SFT                           14
#define C_SGEN_WCH_INV_8BIT_MASK                          0x1
#define C_SGEN_WCH_INV_8BIT_MASK_SFT                      (0x1 << 14)
#define SGEN_FWEQ_DIV_CH1_CTW_SFT                         0
#define SGEN_FWEQ_DIV_CH1_CTW_MASK                        0x1f
#define SGEN_FWEQ_DIV_CH1_CTW_MASK_SFT                    (0x1f << 0)

/* MT6358_AFE_ADC_ASYNC_FIFO_CFG */
#define WG_UW_ASYNC_FIFO_SOFT_WST_EN_SFT                  5
#define WG_UW_ASYNC_FIFO_SOFT_WST_EN_MASK                 0x1
#define WG_UW_ASYNC_FIFO_SOFT_WST_EN_MASK_SFT             (0x1 << 5)
#define WG_UW_ASYNC_FIFO_SOFT_WST_SFT                     4
#define WG_UW_ASYNC_FIFO_SOFT_WST_MASK                    0x1
#define WG_UW_ASYNC_FIFO_SOFT_WST_MASK_SFT                (0x1 << 4)
#define WG_AMIC_UW_ADC_CWK_SEW_SFT                        1
#define WG_AMIC_UW_ADC_CWK_SEW_MASK                       0x1
#define WG_AMIC_UW_ADC_CWK_SEW_MASK_SFT                   (0x1 << 1)

/* MT6358_AFE_DCCWK_CFG0 */
#define DCCWK_DIV_SFT                                     5
#define DCCWK_DIV_MASK                                    0x7ff
#define DCCWK_DIV_MASK_SFT                                (0x7ff << 5)
#define DCCWK_INV_SFT                                     4
#define DCCWK_INV_MASK                                    0x1
#define DCCWK_INV_MASK_SFT                                (0x1 << 4)
#define DCCWK_PDN_SFT                                     1
#define DCCWK_PDN_MASK                                    0x1
#define DCCWK_PDN_MASK_SFT                                (0x1 << 1)
#define DCCWK_GEN_ON_SFT                                  0
#define DCCWK_GEN_ON_MASK                                 0x1
#define DCCWK_GEN_ON_MASK_SFT                             (0x1 << 0)

/* MT6358_AFE_DCCWK_CFG1 */
#define WESYNC_SWC_SEW_SFT                                10
#define WESYNC_SWC_SEW_MASK                               0x3
#define WESYNC_SWC_SEW_MASK_SFT                           (0x3 << 10)
#define WESYNC_SWC_CK_INV_SFT                             9
#define WESYNC_SWC_CK_INV_MASK                            0x1
#define WESYNC_SWC_CK_INV_MASK_SFT                        (0x1 << 9)
#define DCCWK_WESYNC_BYPASS_SFT                           8
#define DCCWK_WESYNC_BYPASS_MASK                          0x1
#define DCCWK_WESYNC_BYPASS_MASK_SFT                      (0x1 << 8)
#define DCCWK_PHASE_SEW_SFT                               4
#define DCCWK_PHASE_SEW_MASK                              0xf
#define DCCWK_PHASE_SEW_MASK_SFT                          (0xf << 4)

/* MT6358_AUDIO_DIG_CFG */
#define WG_AUD_PAD_TOP_DAT_MISO2_WOOPBACK_SFT             15
#define WG_AUD_PAD_TOP_DAT_MISO2_WOOPBACK_MASK            0x1
#define WG_AUD_PAD_TOP_DAT_MISO2_WOOPBACK_MASK_SFT        (0x1 << 15)
#define WG_AUD_PAD_TOP_PHASE_MODE2_SFT                    8
#define WG_AUD_PAD_TOP_PHASE_MODE2_MASK                   0x7f
#define WG_AUD_PAD_TOP_PHASE_MODE2_MASK_SFT               (0x7f << 8)
#define WG_AUD_PAD_TOP_DAT_MISO_WOOPBACK_SFT              7
#define WG_AUD_PAD_TOP_DAT_MISO_WOOPBACK_MASK             0x1
#define WG_AUD_PAD_TOP_DAT_MISO_WOOPBACK_MASK_SFT         (0x1 << 7)
#define WG_AUD_PAD_TOP_PHASE_MODE_SFT                     0
#define WG_AUD_PAD_TOP_PHASE_MODE_MASK                    0x7f
#define WG_AUD_PAD_TOP_PHASE_MODE_MASK_SFT                (0x7f << 0)

/* MT6358_AFE_AUD_PAD_TOP */
#define WG_AUD_PAD_TOP_TX_FIFO_WSP_SFT                    12
#define WG_AUD_PAD_TOP_TX_FIFO_WSP_MASK                   0x7
#define WG_AUD_PAD_TOP_TX_FIFO_WSP_MASK_SFT               (0x7 << 12)
#define WG_AUD_PAD_TOP_MTKAIF_CWK_PWOTOCOW2_SFT           11
#define WG_AUD_PAD_TOP_MTKAIF_CWK_PWOTOCOW2_MASK          0x1
#define WG_AUD_PAD_TOP_MTKAIF_CWK_PWOTOCOW2_MASK_SFT      (0x1 << 11)
#define WG_AUD_PAD_TOP_TX_FIFO_ON_SFT                     8
#define WG_AUD_PAD_TOP_TX_FIFO_ON_MASK                    0x1
#define WG_AUD_PAD_TOP_TX_FIFO_ON_MASK_SFT                (0x1 << 8)

/* MT6358_AFE_AUD_PAD_TOP_MON */
#define ADDA_AUD_PAD_TOP_MON_SFT                          0
#define ADDA_AUD_PAD_TOP_MON_MASK                         0xffff
#define ADDA_AUD_PAD_TOP_MON_MASK_SFT                     (0xffff << 0)

/* MT6358_AFE_AUD_PAD_TOP_MON1 */
#define ADDA_AUD_PAD_TOP_MON1_SFT                         0
#define ADDA_AUD_PAD_TOP_MON1_MASK                        0xffff
#define ADDA_AUD_PAD_TOP_MON1_MASK_SFT                    (0xffff << 0)

/* MT6358_AFE_DW_NWE_CFG */
#define NWE_WCH_HPGAIN_SEW_SFT                            10
#define NWE_WCH_HPGAIN_SEW_MASK                           0x1
#define NWE_WCH_HPGAIN_SEW_MASK_SFT                       (0x1 << 10)
#define NWE_WCH_CH_SEW_SFT                                9
#define NWE_WCH_CH_SEW_MASK                               0x1
#define NWE_WCH_CH_SEW_MASK_SFT                           (0x1 << 9)
#define NWE_WCH_ON_SFT                                    8
#define NWE_WCH_ON_MASK                                   0x1
#define NWE_WCH_ON_MASK_SFT                               (0x1 << 8)
#define NWE_WCH_HPGAIN_SEW_SFT                            2
#define NWE_WCH_HPGAIN_SEW_MASK                           0x1
#define NWE_WCH_HPGAIN_SEW_MASK_SFT                       (0x1 << 2)
#define NWE_WCH_CH_SEW_SFT                                1
#define NWE_WCH_CH_SEW_MASK                               0x1
#define NWE_WCH_CH_SEW_MASK_SFT                           (0x1 << 1)
#define NWE_WCH_ON_SFT                                    0
#define NWE_WCH_ON_MASK                                   0x1
#define NWE_WCH_ON_MASK_SFT                               (0x1 << 0)

/* MT6358_AFE_DW_NWE_MON */
#define NWE_MONITOW_SFT                                   0
#define NWE_MONITOW_MASK                                  0x3fff
#define NWE_MONITOW_MASK_SFT                              (0x3fff << 0)

/* MT6358_AFE_CG_EN_MON */
#define CK_CG_EN_MON_SFT                                  0
#define CK_CG_EN_MON_MASK                                 0x3f
#define CK_CG_EN_MON_MASK_SFT                             (0x3f << 0)

/* MT6358_AFE_VOW_TOP */
#define PDN_VOW_SFT                                       15
#define PDN_VOW_MASK                                      0x1
#define PDN_VOW_MASK_SFT                                  (0x1 << 15)
#define VOW_1P6M_800K_SEW_SFT                             14
#define VOW_1P6M_800K_SEW_MASK                            0x1
#define VOW_1P6M_800K_SEW_MASK_SFT                        (0x1 << 14)
#define VOW_DIGMIC_ON_SFT                                 13
#define VOW_DIGMIC_ON_MASK                                0x1
#define VOW_DIGMIC_ON_MASK_SFT                            (0x1 << 13)
#define VOW_CK_DIV_WST_SFT                                12
#define VOW_CK_DIV_WST_MASK                               0x1
#define VOW_CK_DIV_WST_MASK_SFT                           (0x1 << 12)
#define VOW_ON_SFT                                        11
#define VOW_ON_MASK                                       0x1
#define VOW_ON_MASK_SFT                                   (0x1 << 11)
#define VOW_DIGMIC_CK_PHASE_SEW_SFT                       8
#define VOW_DIGMIC_CK_PHASE_SEW_MASK                      0x7
#define VOW_DIGMIC_CK_PHASE_SEW_MASK_SFT                  (0x7 << 8)
#define MAIN_DMIC_CK_VOW_SEW_SFT                          7
#define MAIN_DMIC_CK_VOW_SEW_MASK                         0x1
#define MAIN_DMIC_CK_VOW_SEW_MASK_SFT                     (0x1 << 7)
#define VOW_SDM_3_WEVEW_SFT                               6
#define VOW_SDM_3_WEVEW_MASK                              0x1
#define VOW_SDM_3_WEVEW_MASK_SFT                          (0x1 << 6)
#define VOW_WOOP_BACK_MODE_SFT                            5
#define VOW_WOOP_BACK_MODE_MASK                           0x1
#define VOW_WOOP_BACK_MODE_MASK_SFT                       (0x1 << 5)
#define VOW_INTW_SOUWCE_SEW_SFT                           4
#define VOW_INTW_SOUWCE_SEW_MASK                          0x1
#define VOW_INTW_SOUWCE_SEW_MASK_SFT                      (0x1 << 4)
#define VOW_INTW_CWW_SFT                                  3
#define VOW_INTW_CWW_MASK                                 0x1
#define VOW_INTW_CWW_MASK_SFT                             (0x1 << 3)
#define S_N_VAWUE_WST_SFT                                 2
#define S_N_VAWUE_WST_MASK                                0x1
#define S_N_VAWUE_WST_MASK_SFT                            (0x1 << 2)
#define SAMPWE_BASE_MODE_SFT                              1
#define SAMPWE_BASE_MODE_MASK                             0x1
#define SAMPWE_BASE_MODE_MASK_SFT                         (0x1 << 1)
#define VOW_INTW_FWAG_SFT                                 0
#define VOW_INTW_FWAG_MASK                                0x1
#define VOW_INTW_FWAG_MASK_SFT                            (0x1 << 0)

/* MT6358_AFE_VOW_CFG0 */
#define AMPWEF_SFT                                        0
#define AMPWEF_MASK                                       0xffff
#define AMPWEF_MASK_SFT                                   (0xffff << 0)

/* MT6358_AFE_VOW_CFG1 */
#define TIMEWINI_SFT                                      0
#define TIMEWINI_MASK                                     0xffff
#define TIMEWINI_MASK_SFT                                 (0xffff << 0)

/* MT6358_AFE_VOW_CFG2 */
#define B_DEFAUWT_SFT                                     12
#define B_DEFAUWT_MASK                                    0x7
#define B_DEFAUWT_MASK_SFT                                (0x7 << 12)
#define A_DEFAUWT_SFT                                     8
#define A_DEFAUWT_MASK                                    0x7
#define A_DEFAUWT_MASK_SFT                                (0x7 << 8)
#define B_INI_SFT                                         4
#define B_INI_MASK                                        0x7
#define B_INI_MASK_SFT                                    (0x7 << 4)
#define A_INI_SFT                                         0
#define A_INI_MASK                                        0x7
#define A_INI_MASK_SFT                                    (0x7 << 0)

/* MT6358_AFE_VOW_CFG3 */
#define K_BETA_WISE_SFT                                   12
#define K_BETA_WISE_MASK                                  0xf
#define K_BETA_WISE_MASK_SFT                              (0xf << 12)
#define K_BETA_FAWW_SFT                                   8
#define K_BETA_FAWW_MASK                                  0xf
#define K_BETA_FAWW_MASK_SFT                              (0xf << 8)
#define K_AWPHA_WISE_SFT                                  4
#define K_AWPHA_WISE_MASK                                 0xf
#define K_AWPHA_WISE_MASK_SFT                             (0xf << 4)
#define K_AWPHA_FAWW_SFT                                  0
#define K_AWPHA_FAWW_MASK                                 0xf
#define K_AWPHA_FAWW_MASK_SFT                             (0xf << 0)

/* MT6358_AFE_VOW_CFG4 */
#define VOW_TXIF_SCK_INV_SFT                              15
#define VOW_TXIF_SCK_INV_MASK                             0x1
#define VOW_TXIF_SCK_INV_MASK_SFT                         (0x1 << 15)
#define VOW_ADC_TESTCK_SWC_SEW_SFT                        12
#define VOW_ADC_TESTCK_SWC_SEW_MASK                       0x7
#define VOW_ADC_TESTCK_SWC_SEW_MASK_SFT                   (0x7 << 12)
#define VOW_ADC_TESTCK_SEW_SFT                            11
#define VOW_ADC_TESTCK_SEW_MASK                           0x1
#define VOW_ADC_TESTCK_SEW_MASK_SFT                       (0x1 << 11)
#define VOW_ADC_CWK_INV_SFT                               10
#define VOW_ADC_CWK_INV_MASK                              0x1
#define VOW_ADC_CWK_INV_MASK_SFT                          (0x1 << 10)
#define VOW_TXIF_MONO_SFT                                 9
#define VOW_TXIF_MONO_MASK                                0x1
#define VOW_TXIF_MONO_MASK_SFT                            (0x1 << 9)
#define VOW_TXIF_SCK_DIV_SFT                              4
#define VOW_TXIF_SCK_DIV_MASK                             0x1f
#define VOW_TXIF_SCK_DIV_MASK_SFT                         (0x1f << 4)
#define K_GAMMA_SFT                                       0
#define K_GAMMA_MASK                                      0xf
#define K_GAMMA_MASK_SFT                                  (0xf << 0)

/* MT6358_AFE_VOW_CFG5 */
#define N_MIN_SFT                                         0
#define N_MIN_MASK                                        0xffff
#define N_MIN_MASK_SFT                                    (0xffff << 0)

/* MT6358_AFE_VOW_CFG6 */
#define WG_WINDOW_SIZE_SEW_SFT                            12
#define WG_WINDOW_SIZE_SEW_MASK                           0x1
#define WG_WINDOW_SIZE_SEW_MASK_SFT                       (0x1 << 12)
#define WG_FWW_BYPASS_SFT                                 11
#define WG_FWW_BYPASS_MASK                                0x1
#define WG_FWW_BYPASS_MASK_SFT                            (0x1 << 11)
#define WG_FWW_WATIO_SFT                                  8
#define WG_FWW_WATIO_MASK                                 0x7
#define WG_FWW_WATIO_MASK_SFT                             (0x7 << 8)
#define WG_BUCK_DVFS_DONE_SW_CTW_SFT                      7
#define WG_BUCK_DVFS_DONE_SW_CTW_MASK                     0x1
#define WG_BUCK_DVFS_DONE_SW_CTW_MASK_SFT                 (0x1 << 7)
#define WG_BUCK_DVFS_DONE_HW_MODE_SFT                     6
#define WG_BUCK_DVFS_DONE_HW_MODE_MASK                    0x1
#define WG_BUCK_DVFS_DONE_HW_MODE_MASK_SFT                (0x1 << 6)
#define WG_BUCK_DVFS_HW_CNT_THW_SFT                       0
#define WG_BUCK_DVFS_HW_CNT_THW_MASK                      0x3f
#define WG_BUCK_DVFS_HW_CNT_THW_MASK_SFT                  (0x3f << 0)

/* MT6358_AFE_VOW_MON0 */
#define VOW_DOWNCNT_SFT                                   0
#define VOW_DOWNCNT_MASK                                  0xffff
#define VOW_DOWNCNT_MASK_SFT                              (0xffff << 0)

/* MT6358_AFE_VOW_MON1 */
#define K_TMP_MON_SFT                                     10
#define K_TMP_MON_MASK                                    0xf
#define K_TMP_MON_MASK_SFT                                (0xf << 10)
#define SWT_COUNTEW_MON_SFT                               7
#define SWT_COUNTEW_MON_MASK                              0x7
#define SWT_COUNTEW_MON_MASK_SFT                          (0x7 << 7)
#define VOW_B_SFT                                         4
#define VOW_B_MASK                                        0x7
#define VOW_B_MASK_SFT                                    (0x7 << 4)
#define VOW_A_SFT                                         1
#define VOW_A_MASK                                        0x7
#define VOW_A_MASK_SFT                                    (0x7 << 1)
#define SECOND_CNT_STAWT_SFT                              0
#define SECOND_CNT_STAWT_MASK                             0x1
#define SECOND_CNT_STAWT_MASK_SFT                         (0x1 << 0)

/* MT6358_AFE_VOW_MON2 */
#define VOW_S_W_SFT                                       0
#define VOW_S_W_MASK                                      0xffff
#define VOW_S_W_MASK_SFT                                  (0xffff << 0)

/* MT6358_AFE_VOW_MON3 */
#define VOW_S_H_SFT                                       0
#define VOW_S_H_MASK                                      0xffff
#define VOW_S_H_MASK_SFT                                  (0xffff << 0)

/* MT6358_AFE_VOW_MON4 */
#define VOW_N_W_SFT                                       0
#define VOW_N_W_MASK                                      0xffff
#define VOW_N_W_MASK_SFT                                  (0xffff << 0)

/* MT6358_AFE_VOW_MON5 */
#define VOW_N_H_SFT                                       0
#define VOW_N_H_MASK                                      0xffff
#define VOW_N_H_MASK_SFT                                  (0xffff << 0)

/* MT6358_AFE_VOW_SN_INI_CFG */
#define VOW_SN_INI_CFG_EN_SFT                             15
#define VOW_SN_INI_CFG_EN_MASK                            0x1
#define VOW_SN_INI_CFG_EN_MASK_SFT                        (0x1 << 15)
#define VOW_SN_INI_CFG_VAW_SFT                            0
#define VOW_SN_INI_CFG_VAW_MASK                           0x7fff
#define VOW_SN_INI_CFG_VAW_MASK_SFT                       (0x7fff << 0)

/* MT6358_AFE_VOW_TGEN_CFG0 */
#define VOW_TGEN_EN_SFT                                   15
#define VOW_TGEN_EN_MASK                                  0x1
#define VOW_TGEN_EN_MASK_SFT                              (0x1 << 15)
#define VOW_TGEN_MUTE_SW_SFT                              14
#define VOW_TGEN_MUTE_SW_MASK                             0x1
#define VOW_TGEN_MUTE_SW_MASK_SFT                         (0x1 << 14)
#define VOW_TGEN_FWEQ_DIV_SFT                             0
#define VOW_TGEN_FWEQ_DIV_MASK                            0x3fff
#define VOW_TGEN_FWEQ_DIV_MASK_SFT                        (0x3fff << 0)

/* MT6358_AFE_VOW_POSDIV_CFG0 */
#define BUCK_DVFS_DONE_SFT                                15
#define BUCK_DVFS_DONE_MASK                               0x1
#define BUCK_DVFS_DONE_MASK_SFT                           (0x1 << 15)
#define VOW_32K_MODE_SFT                                  13
#define VOW_32K_MODE_MASK                                 0x1
#define VOW_32K_MODE_MASK_SFT                             (0x1 << 13)
#define WG_BUCK_CWK_DIV_SFT                               8
#define WG_BUCK_CWK_DIV_MASK                              0x1f
#define WG_BUCK_CWK_DIV_MASK_SFT                          (0x1f << 8)
#define WG_A1P6M_EN_SEW_SFT                               7
#define WG_A1P6M_EN_SEW_MASK                              0x1
#define WG_A1P6M_EN_SEW_MASK_SFT                          (0x1 << 7)
#define VOW_CWK_SEW_SFT                                   6
#define VOW_CWK_SEW_MASK                                  0x1
#define VOW_CWK_SEW_MASK_SFT                              (0x1 << 6)
#define VOW_INTW_SW_MODE_SFT                              5
#define VOW_INTW_SW_MODE_MASK                             0x1
#define VOW_INTW_SW_MODE_MASK_SFT                         (0x1 << 5)
#define VOW_INTW_SW_VAW_SFT                               4
#define VOW_INTW_SW_VAW_MASK                              0x1
#define VOW_INTW_SW_VAW_MASK_SFT                          (0x1 << 4)
#define VOW_CIC_MODE_SEW_SFT                              2
#define VOW_CIC_MODE_SEW_MASK                             0x3
#define VOW_CIC_MODE_SEW_MASK_SFT                         (0x3 << 2)
#define WG_VOW_POSDIV_SFT                                 0
#define WG_VOW_POSDIV_MASK                                0x3
#define WG_VOW_POSDIV_MASK_SFT                            (0x3 << 0)

/* MT6358_AFE_VOW_HPF_CFG0 */
#define VOW_HPF_DC_TEST_SFT                               12
#define VOW_HPF_DC_TEST_MASK                              0xf
#define VOW_HPF_DC_TEST_MASK_SFT                          (0xf << 12)
#define VOW_IWQ_WATCH_SNW_EN_SFT                          10
#define VOW_IWQ_WATCH_SNW_EN_MASK                         0x1
#define VOW_IWQ_WATCH_SNW_EN_MASK_SFT                     (0x1 << 10)
#define VOW_DMICCWK_PDN_SFT                               9
#define VOW_DMICCWK_PDN_MASK                              0x1
#define VOW_DMICCWK_PDN_MASK_SFT                          (0x1 << 9)
#define VOW_POSDIVCWK_PDN_SFT                             8
#define VOW_POSDIVCWK_PDN_MASK                            0x1
#define VOW_POSDIVCWK_PDN_MASK_SFT                        (0x1 << 8)
#define WG_BASEWINE_AWPHA_OWDEW_SFT                       4
#define WG_BASEWINE_AWPHA_OWDEW_MASK                      0xf
#define WG_BASEWINE_AWPHA_OWDEW_MASK_SFT                  (0xf << 4)
#define WG_MTKAIF_HPF_BYPASS_SFT                          2
#define WG_MTKAIF_HPF_BYPASS_MASK                         0x1
#define WG_MTKAIF_HPF_BYPASS_MASK_SFT                     (0x1 << 2)
#define WG_SNWDET_HPF_BYPASS_SFT                          1
#define WG_SNWDET_HPF_BYPASS_MASK                         0x1
#define WG_SNWDET_HPF_BYPASS_MASK_SFT                     (0x1 << 1)
#define WG_HPF_ON_SFT                                     0
#define WG_HPF_ON_MASK                                    0x1
#define WG_HPF_ON_MASK_SFT                                (0x1 << 0)

/* MT6358_AFE_VOW_PEWIODIC_CFG0 */
#define WG_PEWIODIC_EN_SFT                                15
#define WG_PEWIODIC_EN_MASK                               0x1
#define WG_PEWIODIC_EN_MASK_SFT                           (0x1 << 15)
#define WG_PEWIODIC_CNT_CWW_SFT                           14
#define WG_PEWIODIC_CNT_CWW_MASK                          0x1
#define WG_PEWIODIC_CNT_CWW_MASK_SFT                      (0x1 << 14)
#define WG_PEWIODIC_CNT_PEWIOD_SFT                        0
#define WG_PEWIODIC_CNT_PEWIOD_MASK                       0x3fff
#define WG_PEWIODIC_CNT_PEWIOD_MASK_SFT                   (0x3fff << 0)

/* MT6358_AFE_VOW_PEWIODIC_CFG1 */
#define WG_PEWIODIC_CNT_SET_SFT                           15
#define WG_PEWIODIC_CNT_SET_MASK                          0x1
#define WG_PEWIODIC_CNT_SET_MASK_SFT                      (0x1 << 15)
#define WG_PEWIODIC_CNT_PAUSE_SFT                         14
#define WG_PEWIODIC_CNT_PAUSE_MASK                        0x1
#define WG_PEWIODIC_CNT_PAUSE_MASK_SFT                    (0x1 << 14)
#define WG_PEWIODIC_CNT_SET_VAWUE_SFT                     0
#define WG_PEWIODIC_CNT_SET_VAWUE_MASK                    0x3fff
#define WG_PEWIODIC_CNT_SET_VAWUE_MASK_SFT                (0x3fff << 0)

/* MT6358_AFE_VOW_PEWIODIC_CFG2 */
#define AUDPWEAMPWON_PEWIODIC_MODE_SFT                    15
#define AUDPWEAMPWON_PEWIODIC_MODE_MASK                   0x1
#define AUDPWEAMPWON_PEWIODIC_MODE_MASK_SFT               (0x1 << 15)
#define AUDPWEAMPWON_PEWIODIC_INVEWSE_SFT                 14
#define AUDPWEAMPWON_PEWIODIC_INVEWSE_MASK                0x1
#define AUDPWEAMPWON_PEWIODIC_INVEWSE_MASK_SFT            (0x1 << 14)
#define AUDPWEAMPWON_PEWIODIC_ON_CYCWE_SFT                0
#define AUDPWEAMPWON_PEWIODIC_ON_CYCWE_MASK               0x3fff
#define AUDPWEAMPWON_PEWIODIC_ON_CYCWE_MASK_SFT           (0x3fff << 0)

/* MT6358_AFE_VOW_PEWIODIC_CFG3 */
#define AUDPWEAMPWDCPWECHAWGE_PEWIODIC_MODE_SFT           15
#define AUDPWEAMPWDCPWECHAWGE_PEWIODIC_MODE_MASK          0x1
#define AUDPWEAMPWDCPWECHAWGE_PEWIODIC_MODE_MASK_SFT      (0x1 << 15)
#define AUDPWEAMPWDCPWECHAWGE_PEWIODIC_INVEWSE_SFT        14
#define AUDPWEAMPWDCPWECHAWGE_PEWIODIC_INVEWSE_MASK       0x1
#define AUDPWEAMPWDCPWECHAWGE_PEWIODIC_INVEWSE_MASK_SFT   (0x1 << 14)
#define AUDPWEAMPWDCPWECHAWGE_PEWIODIC_ON_CYCWE_SFT       0
#define AUDPWEAMPWDCPWECHAWGE_PEWIODIC_ON_CYCWE_MASK      0x3fff
#define AUDPWEAMPWDCPWECHAWGE_PEWIODIC_ON_CYCWE_MASK_SFT  (0x3fff << 0)

/* MT6358_AFE_VOW_PEWIODIC_CFG4 */
#define AUDADCWPWWUP_PEWIODIC_MODE_SFT                    15
#define AUDADCWPWWUP_PEWIODIC_MODE_MASK                   0x1
#define AUDADCWPWWUP_PEWIODIC_MODE_MASK_SFT               (0x1 << 15)
#define AUDADCWPWWUP_PEWIODIC_INVEWSE_SFT                 14
#define AUDADCWPWWUP_PEWIODIC_INVEWSE_MASK                0x1
#define AUDADCWPWWUP_PEWIODIC_INVEWSE_MASK_SFT            (0x1 << 14)
#define AUDADCWPWWUP_PEWIODIC_ON_CYCWE_SFT                0
#define AUDADCWPWWUP_PEWIODIC_ON_CYCWE_MASK               0x3fff
#define AUDADCWPWWUP_PEWIODIC_ON_CYCWE_MASK_SFT           (0x3fff << 0)

/* MT6358_AFE_VOW_PEWIODIC_CFG5 */
#define AUDGWBVOWWPWEN_PEWIODIC_MODE_SFT                  15
#define AUDGWBVOWWPWEN_PEWIODIC_MODE_MASK                 0x1
#define AUDGWBVOWWPWEN_PEWIODIC_MODE_MASK_SFT             (0x1 << 15)
#define AUDGWBVOWWPWEN_PEWIODIC_INVEWSE_SFT               14
#define AUDGWBVOWWPWEN_PEWIODIC_INVEWSE_MASK              0x1
#define AUDGWBVOWWPWEN_PEWIODIC_INVEWSE_MASK_SFT          (0x1 << 14)
#define AUDGWBVOWWPWEN_PEWIODIC_ON_CYCWE_SFT              0
#define AUDGWBVOWWPWEN_PEWIODIC_ON_CYCWE_MASK             0x3fff
#define AUDGWBVOWWPWEN_PEWIODIC_ON_CYCWE_MASK_SFT         (0x3fff << 0)

/* MT6358_AFE_VOW_PEWIODIC_CFG6 */
#define AUDDIGMICEN_PEWIODIC_MODE_SFT                     15
#define AUDDIGMICEN_PEWIODIC_MODE_MASK                    0x1
#define AUDDIGMICEN_PEWIODIC_MODE_MASK_SFT                (0x1 << 15)
#define AUDDIGMICEN_PEWIODIC_INVEWSE_SFT                  14
#define AUDDIGMICEN_PEWIODIC_INVEWSE_MASK                 0x1
#define AUDDIGMICEN_PEWIODIC_INVEWSE_MASK_SFT             (0x1 << 14)
#define AUDDIGMICEN_PEWIODIC_ON_CYCWE_SFT                 0
#define AUDDIGMICEN_PEWIODIC_ON_CYCWE_MASK                0x3fff
#define AUDDIGMICEN_PEWIODIC_ON_CYCWE_MASK_SFT            (0x3fff << 0)

/* MT6358_AFE_VOW_PEWIODIC_CFG7 */
#define AUDPWDBMICBIAS0_PEWIODIC_MODE_SFT                 15
#define AUDPWDBMICBIAS0_PEWIODIC_MODE_MASK                0x1
#define AUDPWDBMICBIAS0_PEWIODIC_MODE_MASK_SFT            (0x1 << 15)
#define AUDPWDBMICBIAS0_PEWIODIC_INVEWSE_SFT              14
#define AUDPWDBMICBIAS0_PEWIODIC_INVEWSE_MASK             0x1
#define AUDPWDBMICBIAS0_PEWIODIC_INVEWSE_MASK_SFT         (0x1 << 14)
#define AUDPWDBMICBIAS0_PEWIODIC_ON_CYCWE_SFT             0
#define AUDPWDBMICBIAS0_PEWIODIC_ON_CYCWE_MASK            0x3fff
#define AUDPWDBMICBIAS0_PEWIODIC_ON_CYCWE_MASK_SFT        (0x3fff << 0)

/* MT6358_AFE_VOW_PEWIODIC_CFG8 */
#define AUDPWDBMICBIAS1_PEWIODIC_MODE_SFT                 15
#define AUDPWDBMICBIAS1_PEWIODIC_MODE_MASK                0x1
#define AUDPWDBMICBIAS1_PEWIODIC_MODE_MASK_SFT            (0x1 << 15)
#define AUDPWDBMICBIAS1_PEWIODIC_INVEWSE_SFT              14
#define AUDPWDBMICBIAS1_PEWIODIC_INVEWSE_MASK             0x1
#define AUDPWDBMICBIAS1_PEWIODIC_INVEWSE_MASK_SFT         (0x1 << 14)
#define AUDPWDBMICBIAS1_PEWIODIC_ON_CYCWE_SFT             0
#define AUDPWDBMICBIAS1_PEWIODIC_ON_CYCWE_MASK            0x3fff
#define AUDPWDBMICBIAS1_PEWIODIC_ON_CYCWE_MASK_SFT        (0x3fff << 0)

/* MT6358_AFE_VOW_PEWIODIC_CFG9 */
#define XO_VOW_CK_EN_PEWIODIC_MODE_SFT                    15
#define XO_VOW_CK_EN_PEWIODIC_MODE_MASK                   0x1
#define XO_VOW_CK_EN_PEWIODIC_MODE_MASK_SFT               (0x1 << 15)
#define XO_VOW_CK_EN_PEWIODIC_INVEWSE_SFT                 14
#define XO_VOW_CK_EN_PEWIODIC_INVEWSE_MASK                0x1
#define XO_VOW_CK_EN_PEWIODIC_INVEWSE_MASK_SFT            (0x1 << 14)
#define XO_VOW_CK_EN_PEWIODIC_ON_CYCWE_SFT                0
#define XO_VOW_CK_EN_PEWIODIC_ON_CYCWE_MASK               0x3fff
#define XO_VOW_CK_EN_PEWIODIC_ON_CYCWE_MASK_SFT           (0x3fff << 0)

/* MT6358_AFE_VOW_PEWIODIC_CFG10 */
#define AUDGWB_PWWDN_PEWIODIC_MODE_SFT                    15
#define AUDGWB_PWWDN_PEWIODIC_MODE_MASK                   0x1
#define AUDGWB_PWWDN_PEWIODIC_MODE_MASK_SFT               (0x1 << 15)
#define AUDGWB_PWWDN_PEWIODIC_INVEWSE_SFT                 14
#define AUDGWB_PWWDN_PEWIODIC_INVEWSE_MASK                0x1
#define AUDGWB_PWWDN_PEWIODIC_INVEWSE_MASK_SFT            (0x1 << 14)
#define AUDGWB_PWWDN_PEWIODIC_ON_CYCWE_SFT                0
#define AUDGWB_PWWDN_PEWIODIC_ON_CYCWE_MASK               0x3fff
#define AUDGWB_PWWDN_PEWIODIC_ON_CYCWE_MASK_SFT           (0x3fff << 0)

/* MT6358_AFE_VOW_PEWIODIC_CFG11 */
#define VOW_ON_PEWIODIC_MODE_SFT                          15
#define VOW_ON_PEWIODIC_MODE_MASK                         0x1
#define VOW_ON_PEWIODIC_MODE_MASK_SFT                     (0x1 << 15)
#define VOW_ON_PEWIODIC_INVEWSE_SFT                       14
#define VOW_ON_PEWIODIC_INVEWSE_MASK                      0x1
#define VOW_ON_PEWIODIC_INVEWSE_MASK_SFT                  (0x1 << 14)
#define VOW_ON_PEWIODIC_ON_CYCWE_SFT                      0
#define VOW_ON_PEWIODIC_ON_CYCWE_MASK                     0x3fff
#define VOW_ON_PEWIODIC_ON_CYCWE_MASK_SFT                 (0x3fff << 0)

/* MT6358_AFE_VOW_PEWIODIC_CFG12 */
#define DMIC_ON_PEWIODIC_MODE_SFT                         15
#define DMIC_ON_PEWIODIC_MODE_MASK                        0x1
#define DMIC_ON_PEWIODIC_MODE_MASK_SFT                    (0x1 << 15)
#define DMIC_ON_PEWIODIC_INVEWSE_SFT                      14
#define DMIC_ON_PEWIODIC_INVEWSE_MASK                     0x1
#define DMIC_ON_PEWIODIC_INVEWSE_MASK_SFT                 (0x1 << 14)
#define DMIC_ON_PEWIODIC_ON_CYCWE_SFT                     0
#define DMIC_ON_PEWIODIC_ON_CYCWE_MASK                    0x3fff
#define DMIC_ON_PEWIODIC_ON_CYCWE_MASK_SFT                (0x3fff << 0)

/* MT6358_AFE_VOW_PEWIODIC_CFG13 */
#define PDN_VOW_F32K_CK_SFT                               15
#define PDN_VOW_F32K_CK_MASK                              0x1
#define PDN_VOW_F32K_CK_MASK_SFT                          (0x1 << 15)
#define AUDPWEAMPWON_PEWIODIC_OFF_CYCWE_SFT               0
#define AUDPWEAMPWON_PEWIODIC_OFF_CYCWE_MASK              0x3fff
#define AUDPWEAMPWON_PEWIODIC_OFF_CYCWE_MASK_SFT          (0x3fff << 0)

/* MT6358_AFE_VOW_PEWIODIC_CFG14 */
#define VOW_SNWDET_PEWIODIC_CFG_SFT                       15
#define VOW_SNWDET_PEWIODIC_CFG_MASK                      0x1
#define VOW_SNWDET_PEWIODIC_CFG_MASK_SFT                  (0x1 << 15)
#define AUDPWEAMPWDCPWECHAWGE_PEWIODIC_OFF_CYCWE_SFT      0
#define AUDPWEAMPWDCPWECHAWGE_PEWIODIC_OFF_CYCWE_MASK     0x3fff
#define AUDPWEAMPWDCPWECHAWGE_PEWIODIC_OFF_CYCWE_MASK_SFT (0x3fff << 0)

/* MT6358_AFE_VOW_PEWIODIC_CFG15 */
#define AUDADCWPWWUP_PEWIODIC_OFF_CYCWE_SFT               0
#define AUDADCWPWWUP_PEWIODIC_OFF_CYCWE_MASK              0x3fff
#define AUDADCWPWWUP_PEWIODIC_OFF_CYCWE_MASK_SFT          (0x3fff << 0)

/* MT6358_AFE_VOW_PEWIODIC_CFG16 */
#define AUDGWBVOWWPWEN_PEWIODIC_OFF_CYCWE_SFT             0
#define AUDGWBVOWWPWEN_PEWIODIC_OFF_CYCWE_MASK            0x3fff
#define AUDGWBVOWWPWEN_PEWIODIC_OFF_CYCWE_MASK_SFT        (0x3fff << 0)

/* MT6358_AFE_VOW_PEWIODIC_CFG17 */
#define AUDDIGMICEN_PEWIODIC_OFF_CYCWE_SFT                0
#define AUDDIGMICEN_PEWIODIC_OFF_CYCWE_MASK               0x3fff
#define AUDDIGMICEN_PEWIODIC_OFF_CYCWE_MASK_SFT           (0x3fff << 0)

/* MT6358_AFE_VOW_PEWIODIC_CFG18 */
#define AUDPWDBMICBIAS0_PEWIODIC_OFF_CYCWE_SFT            0
#define AUDPWDBMICBIAS0_PEWIODIC_OFF_CYCWE_MASK           0x3fff
#define AUDPWDBMICBIAS0_PEWIODIC_OFF_CYCWE_MASK_SFT       (0x3fff << 0)

/* MT6358_AFE_VOW_PEWIODIC_CFG19 */
#define AUDPWDBMICBIAS1_PEWIODIC_OFF_CYCWE_SFT            0
#define AUDPWDBMICBIAS1_PEWIODIC_OFF_CYCWE_MASK           0x3fff
#define AUDPWDBMICBIAS1_PEWIODIC_OFF_CYCWE_MASK_SFT       (0x3fff << 0)

/* MT6358_AFE_VOW_PEWIODIC_CFG20 */
#define CWKSQ_EN_VOW_PEWIODIC_MODE_SFT                    15
#define CWKSQ_EN_VOW_PEWIODIC_MODE_MASK                   0x1
#define CWKSQ_EN_VOW_PEWIODIC_MODE_MASK_SFT               (0x1 << 15)
#define XO_VOW_CK_EN_PEWIODIC_OFF_CYCWE_SFT               0
#define XO_VOW_CK_EN_PEWIODIC_OFF_CYCWE_MASK              0x3fff
#define XO_VOW_CK_EN_PEWIODIC_OFF_CYCWE_MASK_SFT          (0x3fff << 0)

/* MT6358_AFE_VOW_PEWIODIC_CFG21 */
#define AUDGWB_PWWDN_PEWIODIC_OFF_CYCWE_SFT               0
#define AUDGWB_PWWDN_PEWIODIC_OFF_CYCWE_MASK              0x3fff
#define AUDGWB_PWWDN_PEWIODIC_OFF_CYCWE_MASK_SFT          (0x3fff << 0)

/* MT6358_AFE_VOW_PEWIODIC_CFG22 */
#define VOW_ON_PEWIODIC_OFF_CYCWE_SFT                     0
#define VOW_ON_PEWIODIC_OFF_CYCWE_MASK                    0x3fff
#define VOW_ON_PEWIODIC_OFF_CYCWE_MASK_SFT                (0x3fff << 0)

/* MT6358_AFE_VOW_PEWIODIC_CFG23 */
#define DMIC_ON_PEWIODIC_OFF_CYCWE_SFT                    0
#define DMIC_ON_PEWIODIC_OFF_CYCWE_MASK                   0x3fff
#define DMIC_ON_PEWIODIC_OFF_CYCWE_MASK_SFT               (0x3fff << 0)

/* MT6358_AFE_VOW_PEWIODIC_MON0 */
#define VOW_PEWIODIC_MON_SFT                              0
#define VOW_PEWIODIC_MON_MASK                             0xffff
#define VOW_PEWIODIC_MON_MASK_SFT                         (0xffff << 0)

/* MT6358_AFE_VOW_PEWIODIC_MON1 */
#define VOW_PEWIODIC_COUNT_MON_SFT                        0
#define VOW_PEWIODIC_COUNT_MON_MASK                       0xffff
#define VOW_PEWIODIC_COUNT_MON_MASK_SFT                   (0xffff << 0)

/* MT6358_AUDENC_DSN_ID */
#define AUDENC_ANA_ID_SFT                                 0
#define AUDENC_ANA_ID_MASK                                0xff
#define AUDENC_ANA_ID_MASK_SFT                            (0xff << 0)
#define AUDENC_DIG_ID_SFT                                 8
#define AUDENC_DIG_ID_MASK                                0xff
#define AUDENC_DIG_ID_MASK_SFT                            (0xff << 8)

/* MT6358_AUDENC_DSN_WEV0 */
#define AUDENC_ANA_MINOW_WEV_SFT                          0
#define AUDENC_ANA_MINOW_WEV_MASK                         0xf
#define AUDENC_ANA_MINOW_WEV_MASK_SFT                     (0xf << 0)
#define AUDENC_ANA_MAJOW_WEV_SFT                          4
#define AUDENC_ANA_MAJOW_WEV_MASK                         0xf
#define AUDENC_ANA_MAJOW_WEV_MASK_SFT                     (0xf << 4)
#define AUDENC_DIG_MINOW_WEV_SFT                          8
#define AUDENC_DIG_MINOW_WEV_MASK                         0xf
#define AUDENC_DIG_MINOW_WEV_MASK_SFT                     (0xf << 8)
#define AUDENC_DIG_MAJOW_WEV_SFT                          12
#define AUDENC_DIG_MAJOW_WEV_MASK                         0xf
#define AUDENC_DIG_MAJOW_WEV_MASK_SFT                     (0xf << 12)

/* MT6358_AUDENC_DSN_DBI */
#define AUDENC_DSN_CBS_SFT                                0
#define AUDENC_DSN_CBS_MASK                               0x3
#define AUDENC_DSN_CBS_MASK_SFT                           (0x3 << 0)
#define AUDENC_DSN_BIX_SFT                                2
#define AUDENC_DSN_BIX_MASK                               0x3
#define AUDENC_DSN_BIX_MASK_SFT                           (0x3 << 2)
#define AUDENC_DSN_ESP_SFT                                8
#define AUDENC_DSN_ESP_MASK                               0xff
#define AUDENC_DSN_ESP_MASK_SFT                           (0xff << 8)

/* MT6358_AUDENC_DSN_FPI */
#define AUDENC_DSN_FPI_SFT                                0
#define AUDENC_DSN_FPI_MASK                               0xff
#define AUDENC_DSN_FPI_MASK_SFT                           (0xff << 0)

/* MT6358_AUDENC_ANA_CON0 */
#define WG_AUDPWEAMPWON_SFT                               0
#define WG_AUDPWEAMPWON_MASK                              0x1
#define WG_AUDPWEAMPWON_MASK_SFT                          (0x1 << 0)
#define WG_AUDPWEAMPWDCCEN_SFT                            1
#define WG_AUDPWEAMPWDCCEN_MASK                           0x1
#define WG_AUDPWEAMPWDCCEN_MASK_SFT                       (0x1 << 1)
#define WG_AUDPWEAMPWDCPWECHAWGE_SFT                      2
#define WG_AUDPWEAMPWDCPWECHAWGE_MASK                     0x1
#define WG_AUDPWEAMPWDCPWECHAWGE_MASK_SFT                 (0x1 << 2)
#define WG_AUDPWEAMPWPGATEST_SFT                          3
#define WG_AUDPWEAMPWPGATEST_MASK                         0x1
#define WG_AUDPWEAMPWPGATEST_MASK_SFT                     (0x1 << 3)
#define WG_AUDPWEAMPWVSCAWE_SFT                           4
#define WG_AUDPWEAMPWVSCAWE_MASK                          0x3
#define WG_AUDPWEAMPWVSCAWE_MASK_SFT                      (0x3 << 4)
#define WG_AUDPWEAMPWINPUTSEW_SFT                         6
#define WG_AUDPWEAMPWINPUTSEW_MASK                        0x3
#define WG_AUDPWEAMPWINPUTSEW_MASK_SFT                    (0x3 << 6)
#define WG_AUDPWEAMPWGAIN_SFT                             8
#define WG_AUDPWEAMPWGAIN_MASK                            0x7
#define WG_AUDPWEAMPWGAIN_MASK_SFT                        (0x7 << 8)
#define WG_AUDADCWPWWUP_SFT                               12
#define WG_AUDADCWPWWUP_MASK                              0x1
#define WG_AUDADCWPWWUP_MASK_SFT                          (0x1 << 12)
#define WG_AUDADCWINPUTSEW_SFT                            13
#define WG_AUDADCWINPUTSEW_MASK                           0x3
#define WG_AUDADCWINPUTSEW_MASK_SFT                       (0x3 << 13)

/* MT6358_AUDENC_ANA_CON1 */
#define WG_AUDPWEAMPWON_SFT                               0
#define WG_AUDPWEAMPWON_MASK                              0x1
#define WG_AUDPWEAMPWON_MASK_SFT                          (0x1 << 0)
#define WG_AUDPWEAMPWDCCEN_SFT                            1
#define WG_AUDPWEAMPWDCCEN_MASK                           0x1
#define WG_AUDPWEAMPWDCCEN_MASK_SFT                       (0x1 << 1)
#define WG_AUDPWEAMPWDCPWECHAWGE_SFT                      2
#define WG_AUDPWEAMPWDCPWECHAWGE_MASK                     0x1
#define WG_AUDPWEAMPWDCPWECHAWGE_MASK_SFT                 (0x1 << 2)
#define WG_AUDPWEAMPWPGATEST_SFT                          3
#define WG_AUDPWEAMPWPGATEST_MASK                         0x1
#define WG_AUDPWEAMPWPGATEST_MASK_SFT                     (0x1 << 3)
#define WG_AUDPWEAMPWVSCAWE_SFT                           4
#define WG_AUDPWEAMPWVSCAWE_MASK                          0x3
#define WG_AUDPWEAMPWVSCAWE_MASK_SFT                      (0x3 << 4)
#define WG_AUDPWEAMPWINPUTSEW_SFT                         6
#define WG_AUDPWEAMPWINPUTSEW_MASK                        0x3
#define WG_AUDPWEAMPWINPUTSEW_MASK_SFT                    (0x3 << 6)
#define WG_AUDPWEAMPWGAIN_SFT                             8
#define WG_AUDPWEAMPWGAIN_MASK                            0x7
#define WG_AUDPWEAMPWGAIN_MASK_SFT                        (0x7 << 8)
#define WG_AUDIO_VOW_EN_SFT                               11
#define WG_AUDIO_VOW_EN_MASK                              0x1
#define WG_AUDIO_VOW_EN_MASK_SFT                          (0x1 << 11)
#define WG_AUDADCWPWWUP_SFT                               12
#define WG_AUDADCWPWWUP_MASK                              0x1
#define WG_AUDADCWPWWUP_MASK_SFT                          (0x1 << 12)
#define WG_AUDADCWINPUTSEW_SFT                            13
#define WG_AUDADCWINPUTSEW_MASK                           0x3
#define WG_AUDADCWINPUTSEW_MASK_SFT                       (0x3 << 13)
#define WG_CWKSQ_EN_VOW_SFT                               15
#define WG_CWKSQ_EN_VOW_MASK                              0x1
#define WG_CWKSQ_EN_VOW_MASK_SFT                          (0x1 << 15)

/* MT6358_AUDENC_ANA_CON2 */
#define WG_AUDUWHAWFBIAS_SFT                              0
#define WG_AUDUWHAWFBIAS_MASK                             0x1
#define WG_AUDUWHAWFBIAS_MASK_SFT                         (0x1 << 0)
#define WG_AUDGWBVOWWPWEN_SFT                             1
#define WG_AUDGWBVOWWPWEN_MASK                            0x1
#define WG_AUDGWBVOWWPWEN_MASK_SFT                        (0x1 << 1)
#define WG_AUDPWEAMPWPEN_SFT                              2
#define WG_AUDPWEAMPWPEN_MASK                             0x1
#define WG_AUDPWEAMPWPEN_MASK_SFT                         (0x1 << 2)
#define WG_AUDADC1STSTAGEWPEN_SFT                         3
#define WG_AUDADC1STSTAGEWPEN_MASK                        0x1
#define WG_AUDADC1STSTAGEWPEN_MASK_SFT                    (0x1 << 3)
#define WG_AUDADC2NDSTAGEWPEN_SFT                         4
#define WG_AUDADC2NDSTAGEWPEN_MASK                        0x1
#define WG_AUDADC2NDSTAGEWPEN_MASK_SFT                    (0x1 << 4)
#define WG_AUDADCFWASHWPEN_SFT                            5
#define WG_AUDADCFWASHWPEN_MASK                           0x1
#define WG_AUDADCFWASHWPEN_MASK_SFT                       (0x1 << 5)
#define WG_AUDPWEAMPIDDTEST_SFT                           6
#define WG_AUDPWEAMPIDDTEST_MASK                          0x3
#define WG_AUDPWEAMPIDDTEST_MASK_SFT                      (0x3 << 6)
#define WG_AUDADC1STSTAGEIDDTEST_SFT                      8
#define WG_AUDADC1STSTAGEIDDTEST_MASK                     0x3
#define WG_AUDADC1STSTAGEIDDTEST_MASK_SFT                 (0x3 << 8)
#define WG_AUDADC2NDSTAGEIDDTEST_SFT                      10
#define WG_AUDADC2NDSTAGEIDDTEST_MASK                     0x3
#define WG_AUDADC2NDSTAGEIDDTEST_MASK_SFT                 (0x3 << 10)
#define WG_AUDADCWEFBUFIDDTEST_SFT                        12
#define WG_AUDADCWEFBUFIDDTEST_MASK                       0x3
#define WG_AUDADCWEFBUFIDDTEST_MASK_SFT                   (0x3 << 12)
#define WG_AUDADCFWASHIDDTEST_SFT                         14
#define WG_AUDADCFWASHIDDTEST_MASK                        0x3
#define WG_AUDADCFWASHIDDTEST_MASK_SFT                    (0x3 << 14)

/* MT6358_AUDENC_ANA_CON3 */
#define WG_AUDADCDAC0P25FS_SFT                            0
#define WG_AUDADCDAC0P25FS_MASK                           0x1
#define WG_AUDADCDAC0P25FS_MASK_SFT                       (0x1 << 0)
#define WG_AUDADCCWKSEW_SFT                               1
#define WG_AUDADCCWKSEW_MASK                              0x1
#define WG_AUDADCCWKSEW_MASK_SFT                          (0x1 << 1)
#define WG_AUDADCCWKSOUWCE_SFT                            2
#define WG_AUDADCCWKSOUWCE_MASK                           0x3
#define WG_AUDADCCWKSOUWCE_MASK_SFT                       (0x3 << 2)
#define WG_AUDPWEAMPAAFEN_SFT                             8
#define WG_AUDPWEAMPAAFEN_MASK                            0x1
#define WG_AUDPWEAMPAAFEN_MASK_SFT                        (0x1 << 8)
#define WG_DCCVCMBUFWPMODSEW_SFT                          9
#define WG_DCCVCMBUFWPMODSEW_MASK                         0x1
#define WG_DCCVCMBUFWPMODSEW_MASK_SFT                     (0x1 << 9)
#define WG_DCCVCMBUFWPSWEN_SFT                            10
#define WG_DCCVCMBUFWPSWEN_MASK                           0x1
#define WG_DCCVCMBUFWPSWEN_MASK_SFT                       (0x1 << 10)
#define WG_CMSTBENH_SFT                                   11
#define WG_CMSTBENH_MASK                                  0x1
#define WG_CMSTBENH_MASK_SFT                              (0x1 << 11)
#define WG_PGABODYSW_SFT                                  12
#define WG_PGABODYSW_MASK                                 0x1
#define WG_PGABODYSW_MASK_SFT                             (0x1 << 12)

/* MT6358_AUDENC_ANA_CON4 */
#define WG_AUDADC1STSTAGESDENB_SFT                        0
#define WG_AUDADC1STSTAGESDENB_MASK                       0x1
#define WG_AUDADC1STSTAGESDENB_MASK_SFT                   (0x1 << 0)
#define WG_AUDADC2NDSTAGEWESET_SFT                        1
#define WG_AUDADC2NDSTAGEWESET_MASK                       0x1
#define WG_AUDADC2NDSTAGEWESET_MASK_SFT                   (0x1 << 1)
#define WG_AUDADC3WDSTAGEWESET_SFT                        2
#define WG_AUDADC3WDSTAGEWESET_MASK                       0x1
#define WG_AUDADC3WDSTAGEWESET_MASK_SFT                   (0x1 << 2)
#define WG_AUDADCFSWESET_SFT                              3
#define WG_AUDADCFSWESET_MASK                             0x1
#define WG_AUDADCFSWESET_MASK_SFT                         (0x1 << 3)
#define WG_AUDADCWIDECM_SFT                               4
#define WG_AUDADCWIDECM_MASK                              0x1
#define WG_AUDADCWIDECM_MASK_SFT                          (0x1 << 4)
#define WG_AUDADCNOPATEST_SFT                             5
#define WG_AUDADCNOPATEST_MASK                            0x1
#define WG_AUDADCNOPATEST_MASK_SFT                        (0x1 << 5)
#define WG_AUDADCBYPASS_SFT                               6
#define WG_AUDADCBYPASS_MASK                              0x1
#define WG_AUDADCBYPASS_MASK_SFT                          (0x1 << 6)
#define WG_AUDADCFFBYPASS_SFT                             7
#define WG_AUDADCFFBYPASS_MASK                            0x1
#define WG_AUDADCFFBYPASS_MASK_SFT                        (0x1 << 7)
#define WG_AUDADCDACFBCUWWENT_SFT                         8
#define WG_AUDADCDACFBCUWWENT_MASK                        0x1
#define WG_AUDADCDACFBCUWWENT_MASK_SFT                    (0x1 << 8)
#define WG_AUDADCDACIDDTEST_SFT                           9
#define WG_AUDADCDACIDDTEST_MASK                          0x3
#define WG_AUDADCDACIDDTEST_MASK_SFT                      (0x3 << 9)
#define WG_AUDADCDACNWZ_SFT                               11
#define WG_AUDADCDACNWZ_MASK                              0x1
#define WG_AUDADCDACNWZ_MASK_SFT                          (0x1 << 11)
#define WG_AUDADCNODEM_SFT                                12
#define WG_AUDADCNODEM_MASK                               0x1
#define WG_AUDADCNODEM_MASK_SFT                           (0x1 << 12)
#define WG_AUDADCDACTEST_SFT                              13
#define WG_AUDADCDACTEST_MASK                             0x1
#define WG_AUDADCDACTEST_MASK_SFT                         (0x1 << 13)

/* MT6358_AUDENC_ANA_CON5 */
#define WG_AUDWCTUNEW_SFT                                 0
#define WG_AUDWCTUNEW_MASK                                0x1f
#define WG_AUDWCTUNEW_MASK_SFT                            (0x1f << 0)
#define WG_AUDWCTUNEWSEW_SFT                              5
#define WG_AUDWCTUNEWSEW_MASK                             0x1
#define WG_AUDWCTUNEWSEW_MASK_SFT                         (0x1 << 5)
#define WG_AUDWCTUNEW_SFT                                 8
#define WG_AUDWCTUNEW_MASK                                0x1f
#define WG_AUDWCTUNEW_MASK_SFT                            (0x1f << 8)
#define WG_AUDWCTUNEWSEW_SFT                              13
#define WG_AUDWCTUNEWSEW_MASK                             0x1
#define WG_AUDWCTUNEWSEW_MASK_SFT                         (0x1 << 13)

/* MT6358_AUDENC_ANA_CON6 */
#define WG_CWKSQ_EN_SFT                                   0
#define WG_CWKSQ_EN_MASK                                  0x1
#define WG_CWKSQ_EN_MASK_SFT                              (0x1 << 0)
#define WG_CWKSQ_IN_SEW_TEST_SFT                          1
#define WG_CWKSQ_IN_SEW_TEST_MASK                         0x1
#define WG_CWKSQ_IN_SEW_TEST_MASK_SFT                     (0x1 << 1)
#define WG_CM_WEFGENSEW_SFT                               2
#define WG_CM_WEFGENSEW_MASK                              0x1
#define WG_CM_WEFGENSEW_MASK_SFT                          (0x1 << 2)
#define WG_AUDSPAWE_SFT                                   4
#define WG_AUDSPAWE_MASK                                  0xf
#define WG_AUDSPAWE_MASK_SFT                              (0xf << 4)
#define WG_AUDENCSPAWE_SFT                                8
#define WG_AUDENCSPAWE_MASK                               0x3f
#define WG_AUDENCSPAWE_MASK_SFT                           (0x3f << 8)

/* MT6358_AUDENC_ANA_CON7 */
#define WG_AUDENCSPAWE2_SFT                               0
#define WG_AUDENCSPAWE2_MASK                              0xff
#define WG_AUDENCSPAWE2_MASK_SFT                          (0xff << 0)

/* MT6358_AUDENC_ANA_CON8 */
#define WG_AUDDIGMICEN_SFT                                0
#define WG_AUDDIGMICEN_MASK                               0x1
#define WG_AUDDIGMICEN_MASK_SFT                           (0x1 << 0)
#define WG_AUDDIGMICBIAS_SFT                              1
#define WG_AUDDIGMICBIAS_MASK                             0x3
#define WG_AUDDIGMICBIAS_MASK_SFT                         (0x3 << 1)
#define WG_DMICHPCWKEN_SFT                                3
#define WG_DMICHPCWKEN_MASK                               0x1
#define WG_DMICHPCWKEN_MASK_SFT                           (0x1 << 3)
#define WG_AUDDIGMICPDUTY_SFT                             4
#define WG_AUDDIGMICPDUTY_MASK                            0x3
#define WG_AUDDIGMICPDUTY_MASK_SFT                        (0x3 << 4)
#define WG_AUDDIGMICNDUTY_SFT                             6
#define WG_AUDDIGMICNDUTY_MASK                            0x3
#define WG_AUDDIGMICNDUTY_MASK_SFT                        (0x3 << 6)
#define WG_DMICMONEN_SFT                                  8
#define WG_DMICMONEN_MASK                                 0x1
#define WG_DMICMONEN_MASK_SFT                             (0x1 << 8)
#define WG_DMICMONSEW_SFT                                 9
#define WG_DMICMONSEW_MASK                                0x7
#define WG_DMICMONSEW_MASK_SFT                            (0x7 << 9)
#define WG_AUDSPAWEVMIC_SFT                               12
#define WG_AUDSPAWEVMIC_MASK                              0xf
#define WG_AUDSPAWEVMIC_MASK_SFT                          (0xf << 12)

/* MT6358_AUDENC_ANA_CON9 */
#define WG_AUDPWDBMICBIAS0_SFT                            0
#define WG_AUDPWDBMICBIAS0_MASK                           0x1
#define WG_AUDPWDBMICBIAS0_MASK_SFT                       (0x1 << 0)
#define WG_AUDMICBIAS0BYPASSEN_SFT                        1
#define WG_AUDMICBIAS0BYPASSEN_MASK                       0x1
#define WG_AUDMICBIAS0BYPASSEN_MASK_SFT                   (0x1 << 1)
#define WG_AUDMICBIAS0WOWPEN_SFT                          2
#define WG_AUDMICBIAS0WOWPEN_MASK                         0x1
#define WG_AUDMICBIAS0WOWPEN_MASK_SFT                     (0x1 << 2)
#define WG_AUDMICBIAS0VWEF_SFT                            4
#define WG_AUDMICBIAS0VWEF_MASK                           0x7
#define WG_AUDMICBIAS0VWEF_MASK_SFT                       (0x7 << 4)
#define WG_AUDMICBIAS0DCSW0P1EN_SFT                       8
#define WG_AUDMICBIAS0DCSW0P1EN_MASK                      0x1
#define WG_AUDMICBIAS0DCSW0P1EN_MASK_SFT                  (0x1 << 8)
#define WG_AUDMICBIAS0DCSW0P2EN_SFT                       9
#define WG_AUDMICBIAS0DCSW0P2EN_MASK                      0x1
#define WG_AUDMICBIAS0DCSW0P2EN_MASK_SFT                  (0x1 << 9)
#define WG_AUDMICBIAS0DCSW0NEN_SFT                        10
#define WG_AUDMICBIAS0DCSW0NEN_MASK                       0x1
#define WG_AUDMICBIAS0DCSW0NEN_MASK_SFT                   (0x1 << 10)
#define WG_AUDMICBIAS0DCSW2P1EN_SFT                       12
#define WG_AUDMICBIAS0DCSW2P1EN_MASK                      0x1
#define WG_AUDMICBIAS0DCSW2P1EN_MASK_SFT                  (0x1 << 12)
#define WG_AUDMICBIAS0DCSW2P2EN_SFT                       13
#define WG_AUDMICBIAS0DCSW2P2EN_MASK                      0x1
#define WG_AUDMICBIAS0DCSW2P2EN_MASK_SFT                  (0x1 << 13)
#define WG_AUDMICBIAS0DCSW2NEN_SFT                        14
#define WG_AUDMICBIAS0DCSW2NEN_MASK                       0x1
#define WG_AUDMICBIAS0DCSW2NEN_MASK_SFT                   (0x1 << 14)

/* MT6358_AUDENC_ANA_CON10 */
#define WG_AUDPWDBMICBIAS1_SFT                            0
#define WG_AUDPWDBMICBIAS1_MASK                           0x1
#define WG_AUDPWDBMICBIAS1_MASK_SFT                       (0x1 << 0)
#define WG_AUDMICBIAS1BYPASSEN_SFT                        1
#define WG_AUDMICBIAS1BYPASSEN_MASK                       0x1
#define WG_AUDMICBIAS1BYPASSEN_MASK_SFT                   (0x1 << 1)
#define WG_AUDMICBIAS1WOWPEN_SFT                          2
#define WG_AUDMICBIAS1WOWPEN_MASK                         0x1
#define WG_AUDMICBIAS1WOWPEN_MASK_SFT                     (0x1 << 2)
#define WG_AUDMICBIAS1VWEF_SFT                            4
#define WG_AUDMICBIAS1VWEF_MASK                           0x7
#define WG_AUDMICBIAS1VWEF_MASK_SFT                       (0x7 << 4)
#define WG_AUDMICBIAS1DCSW1PEN_SFT                        8
#define WG_AUDMICBIAS1DCSW1PEN_MASK                       0x1
#define WG_AUDMICBIAS1DCSW1PEN_MASK_SFT                   (0x1 << 8)
#define WG_AUDMICBIAS1DCSW1NEN_SFT                        9
#define WG_AUDMICBIAS1DCSW1NEN_MASK                       0x1
#define WG_AUDMICBIAS1DCSW1NEN_MASK_SFT                   (0x1 << 9)
#define WG_BANDGAPGEN_SFT                                 12
#define WG_BANDGAPGEN_MASK                                0x1
#define WG_BANDGAPGEN_MASK_SFT                            (0x1 << 12)
#define WG_MTEST_EN_SFT                                   13
#define WG_MTEST_EN_MASK                                  0x1
#define WG_MTEST_EN_MASK_SFT                              (0x1 << 13)
#define WG_MTEST_SEW_SFT                                  14
#define WG_MTEST_SEW_MASK                                 0x1
#define WG_MTEST_SEW_MASK_SFT                             (0x1 << 14)
#define WG_MTEST_CUWWENT_SFT                              15
#define WG_MTEST_CUWWENT_MASK                             0x1
#define WG_MTEST_CUWWENT_MASK_SFT                         (0x1 << 15)

/* MT6358_AUDENC_ANA_CON11 */
#define WG_AUDACCDETMICBIAS0PUWWWOW_SFT                   0
#define WG_AUDACCDETMICBIAS0PUWWWOW_MASK                  0x1
#define WG_AUDACCDETMICBIAS0PUWWWOW_MASK_SFT              (0x1 << 0)
#define WG_AUDACCDETMICBIAS1PUWWWOW_SFT                   1
#define WG_AUDACCDETMICBIAS1PUWWWOW_MASK                  0x1
#define WG_AUDACCDETMICBIAS1PUWWWOW_MASK_SFT              (0x1 << 1)
#define WG_AUDACCDETVIN1PUWWWOW_SFT                       2
#define WG_AUDACCDETVIN1PUWWWOW_MASK                      0x1
#define WG_AUDACCDETVIN1PUWWWOW_MASK_SFT                  (0x1 << 2)
#define WG_AUDACCDETVTHACAW_SFT                           4
#define WG_AUDACCDETVTHACAW_MASK                          0x1
#define WG_AUDACCDETVTHACAW_MASK_SFT                      (0x1 << 4)
#define WG_AUDACCDETVTHBCAW_SFT                           5
#define WG_AUDACCDETVTHBCAW_MASK                          0x1
#define WG_AUDACCDETVTHBCAW_MASK_SFT                      (0x1 << 5)
#define WG_AUDACCDETTVDET_SFT                             6
#define WG_AUDACCDETTVDET_MASK                            0x1
#define WG_AUDACCDETTVDET_MASK_SFT                        (0x1 << 6)
#define WG_ACCDETSEW_SFT                                  7
#define WG_ACCDETSEW_MASK                                 0x1
#define WG_ACCDETSEW_MASK_SFT                             (0x1 << 7)
#define WG_SWBUFMODSEW_SFT                                8
#define WG_SWBUFMODSEW_MASK                               0x1
#define WG_SWBUFMODSEW_MASK_SFT                           (0x1 << 8)
#define WG_SWBUFSWEN_SFT                                  9
#define WG_SWBUFSWEN_MASK                                 0x1
#define WG_SWBUFSWEN_MASK_SFT                             (0x1 << 9)
#define WG_EINTCOMPVTH_SFT                                10
#define WG_EINTCOMPVTH_MASK                               0x1
#define WG_EINTCOMPVTH_MASK_SFT                           (0x1 << 10)
#define WG_EINTCONFIGACCDET_SFT                           11
#define WG_EINTCONFIGACCDET_MASK                          0x1
#define WG_EINTCONFIGACCDET_MASK_SFT                      (0x1 << 11)
#define WG_EINTHIWENB_SFT                                 12
#define WG_EINTHIWENB_MASK                                0x1
#define WG_EINTHIWENB_MASK_SFT                            (0x1 << 12)
#define WG_ACCDET2AUXWESBYPASS_SFT                        13
#define WG_ACCDET2AUXWESBYPASS_MASK                       0x1
#define WG_ACCDET2AUXWESBYPASS_MASK_SFT                   (0x1 << 13)
#define WG_ACCDET2AUXBUFFEWBYPASS_SFT                     14
#define WG_ACCDET2AUXBUFFEWBYPASS_MASK                    0x1
#define WG_ACCDET2AUXBUFFEWBYPASS_MASK_SFT                (0x1 << 14)
#define WG_ACCDET2AUXSWEN_SFT                             15
#define WG_ACCDET2AUXSWEN_MASK                            0x1
#define WG_ACCDET2AUXSWEN_MASK_SFT                        (0x1 << 15)

/* MT6358_AUDENC_ANA_CON12 */
#define WGS_AUDWCTUNEWWEAD_SFT                            0
#define WGS_AUDWCTUNEWWEAD_MASK                           0x1f
#define WGS_AUDWCTUNEWWEAD_MASK_SFT                       (0x1f << 0)
#define WGS_AUDWCTUNEWWEAD_SFT                            8
#define WGS_AUDWCTUNEWWEAD_MASK                           0x1f
#define WGS_AUDWCTUNEWWEAD_MASK_SFT                       (0x1f << 8)

/* MT6358_AUDDEC_DSN_ID */
#define AUDDEC_ANA_ID_SFT                                 0
#define AUDDEC_ANA_ID_MASK                                0xff
#define AUDDEC_ANA_ID_MASK_SFT                            (0xff << 0)
#define AUDDEC_DIG_ID_SFT                                 8
#define AUDDEC_DIG_ID_MASK                                0xff
#define AUDDEC_DIG_ID_MASK_SFT                            (0xff << 8)

/* MT6358_AUDDEC_DSN_WEV0 */
#define AUDDEC_ANA_MINOW_WEV_SFT                          0
#define AUDDEC_ANA_MINOW_WEV_MASK                         0xf
#define AUDDEC_ANA_MINOW_WEV_MASK_SFT                     (0xf << 0)
#define AUDDEC_ANA_MAJOW_WEV_SFT                          4
#define AUDDEC_ANA_MAJOW_WEV_MASK                         0xf
#define AUDDEC_ANA_MAJOW_WEV_MASK_SFT                     (0xf << 4)
#define AUDDEC_DIG_MINOW_WEV_SFT                          8
#define AUDDEC_DIG_MINOW_WEV_MASK                         0xf
#define AUDDEC_DIG_MINOW_WEV_MASK_SFT                     (0xf << 8)
#define AUDDEC_DIG_MAJOW_WEV_SFT                          12
#define AUDDEC_DIG_MAJOW_WEV_MASK                         0xf
#define AUDDEC_DIG_MAJOW_WEV_MASK_SFT                     (0xf << 12)

/* MT6358_AUDDEC_DSN_DBI */
#define AUDDEC_DSN_CBS_SFT                                0
#define AUDDEC_DSN_CBS_MASK                               0x3
#define AUDDEC_DSN_CBS_MASK_SFT                           (0x3 << 0)
#define AUDDEC_DSN_BIX_SFT                                2
#define AUDDEC_DSN_BIX_MASK                               0x3
#define AUDDEC_DSN_BIX_MASK_SFT                           (0x3 << 2)
#define AUDDEC_DSN_ESP_SFT                                8
#define AUDDEC_DSN_ESP_MASK                               0xff
#define AUDDEC_DSN_ESP_MASK_SFT                           (0xff << 8)

/* MT6358_AUDDEC_DSN_FPI */
#define AUDDEC_DSN_FPI_SFT                                0
#define AUDDEC_DSN_FPI_MASK                               0xff
#define AUDDEC_DSN_FPI_MASK_SFT                           (0xff << 0)

/* MT6358_AUDDEC_ANA_CON0 */
#define WG_AUDDACWPWWUP_VAUDP15_SFT                       0
#define WG_AUDDACWPWWUP_VAUDP15_MASK                      0x1
#define WG_AUDDACWPWWUP_VAUDP15_MASK_SFT                  (0x1 << 0)
#define WG_AUDDACWPWWUP_VAUDP15_SFT                       1
#define WG_AUDDACWPWWUP_VAUDP15_MASK                      0x1
#define WG_AUDDACWPWWUP_VAUDP15_MASK_SFT                  (0x1 << 1)
#define WG_AUD_DAC_PWW_UP_VA28_SFT                        2
#define WG_AUD_DAC_PWW_UP_VA28_MASK                       0x1
#define WG_AUD_DAC_PWW_UP_VA28_MASK_SFT                   (0x1 << 2)
#define WG_AUD_DAC_PWW_UP_VA28_SFT                        3
#define WG_AUD_DAC_PWW_UP_VA28_MASK                       0x1
#define WG_AUD_DAC_PWW_UP_VA28_MASK_SFT                   (0x1 << 3)
#define WG_AUDHPWPWWUP_VAUDP15_SFT                        4
#define WG_AUDHPWPWWUP_VAUDP15_MASK                       0x1
#define WG_AUDHPWPWWUP_VAUDP15_MASK_SFT                   (0x1 << 4)
#define WG_AUDHPWPWWUP_VAUDP15_SFT                        5
#define WG_AUDHPWPWWUP_VAUDP15_MASK                       0x1
#define WG_AUDHPWPWWUP_VAUDP15_MASK_SFT                   (0x1 << 5)
#define WG_AUDHPWPWWUP_IBIAS_VAUDP15_SFT                  6
#define WG_AUDHPWPWWUP_IBIAS_VAUDP15_MASK                 0x1
#define WG_AUDHPWPWWUP_IBIAS_VAUDP15_MASK_SFT             (0x1 << 6)
#define WG_AUDHPWPWWUP_IBIAS_VAUDP15_SFT                  7
#define WG_AUDHPWPWWUP_IBIAS_VAUDP15_MASK                 0x1
#define WG_AUDHPWPWWUP_IBIAS_VAUDP15_MASK_SFT             (0x1 << 7)
#define WG_AUDHPWMUXINPUTSEW_VAUDP15_SFT                  8
#define WG_AUDHPWMUXINPUTSEW_VAUDP15_MASK                 0x3
#define WG_AUDHPWMUXINPUTSEW_VAUDP15_MASK_SFT             (0x3 << 8)
#define WG_AUDHPWMUXINPUTSEW_VAUDP15_SFT                  10
#define WG_AUDHPWMUXINPUTSEW_VAUDP15_MASK                 0x3
#define WG_AUDHPWMUXINPUTSEW_VAUDP15_MASK_SFT             (0x3 << 10)
#define WG_AUDHPWSCDISABWE_VAUDP15_SFT                    12
#define WG_AUDHPWSCDISABWE_VAUDP15_MASK                   0x1
#define WG_AUDHPWSCDISABWE_VAUDP15_MASK_SFT               (0x1 << 12)
#define WG_AUDHPWSCDISABWE_VAUDP15_SFT                    13
#define WG_AUDHPWSCDISABWE_VAUDP15_MASK                   0x1
#define WG_AUDHPWSCDISABWE_VAUDP15_MASK_SFT               (0x1 << 13)
#define WG_AUDHPWBSCCUWWENT_VAUDP15_SFT                   14
#define WG_AUDHPWBSCCUWWENT_VAUDP15_MASK                  0x1
#define WG_AUDHPWBSCCUWWENT_VAUDP15_MASK_SFT              (0x1 << 14)
#define WG_AUDHPWBSCCUWWENT_VAUDP15_SFT                   15
#define WG_AUDHPWBSCCUWWENT_VAUDP15_MASK                  0x1
#define WG_AUDHPWBSCCUWWENT_VAUDP15_MASK_SFT              (0x1 << 15)

/* MT6358_AUDDEC_ANA_CON1 */
#define WG_AUDHPWOUTPWWUP_VAUDP15_SFT                     0
#define WG_AUDHPWOUTPWWUP_VAUDP15_MASK                    0x1
#define WG_AUDHPWOUTPWWUP_VAUDP15_MASK_SFT                (0x1 << 0)
#define WG_AUDHPWOUTPWWUP_VAUDP15_SFT                     1
#define WG_AUDHPWOUTPWWUP_VAUDP15_MASK                    0x1
#define WG_AUDHPWOUTPWWUP_VAUDP15_MASK_SFT                (0x1 << 1)
#define WG_AUDHPWOUTAUXPWWUP_VAUDP15_SFT                  2
#define WG_AUDHPWOUTAUXPWWUP_VAUDP15_MASK                 0x1
#define WG_AUDHPWOUTAUXPWWUP_VAUDP15_MASK_SFT             (0x1 << 2)
#define WG_AUDHPWOUTAUXPWWUP_VAUDP15_SFT                  3
#define WG_AUDHPWOUTAUXPWWUP_VAUDP15_MASK                 0x1
#define WG_AUDHPWOUTAUXPWWUP_VAUDP15_MASK_SFT             (0x1 << 3)
#define WG_HPWAUXFBWSW_EN_VAUDP15_SFT                     4
#define WG_HPWAUXFBWSW_EN_VAUDP15_MASK                    0x1
#define WG_HPWAUXFBWSW_EN_VAUDP15_MASK_SFT                (0x1 << 4)
#define WG_HPWAUXFBWSW_EN_VAUDP15_SFT                     5
#define WG_HPWAUXFBWSW_EN_VAUDP15_MASK                    0x1
#define WG_HPWAUXFBWSW_EN_VAUDP15_MASK_SFT                (0x1 << 5)
#define WG_HPWSHOWT2HPWAUX_EN_VAUDP15_SFT                 6
#define WG_HPWSHOWT2HPWAUX_EN_VAUDP15_MASK                0x1
#define WG_HPWSHOWT2HPWAUX_EN_VAUDP15_MASK_SFT            (0x1 << 6)
#define WG_HPWSHOWT2HPWAUX_EN_VAUDP15_SFT                 7
#define WG_HPWSHOWT2HPWAUX_EN_VAUDP15_MASK                0x1
#define WG_HPWSHOWT2HPWAUX_EN_VAUDP15_MASK_SFT            (0x1 << 7)
#define WG_HPWOUTSTGCTWW_VAUDP15_SFT                      8
#define WG_HPWOUTSTGCTWW_VAUDP15_MASK                     0x7
#define WG_HPWOUTSTGCTWW_VAUDP15_MASK_SFT                 (0x7 << 8)
#define WG_HPWOUTSTGCTWW_VAUDP15_SFT                      11
#define WG_HPWOUTSTGCTWW_VAUDP15_MASK                     0x7
#define WG_HPWOUTSTGCTWW_VAUDP15_MASK_SFT                 (0x7 << 11)

/* MT6358_AUDDEC_ANA_CON2 */
#define WG_HPWOUTPUTSTBENH_VAUDP15_SFT                    0
#define WG_HPWOUTPUTSTBENH_VAUDP15_MASK                   0x7
#define WG_HPWOUTPUTSTBENH_VAUDP15_MASK_SFT               (0x7 << 0)
#define WG_HPWOUTPUTSTBENH_VAUDP15_SFT                    4
#define WG_HPWOUTPUTSTBENH_VAUDP15_MASK                   0x7
#define WG_HPWOUTPUTSTBENH_VAUDP15_MASK_SFT               (0x7 << 4)
#define WG_AUDHPSTAWTUP_VAUDP15_SFT                       13
#define WG_AUDHPSTAWTUP_VAUDP15_MASK                      0x1
#define WG_AUDHPSTAWTUP_VAUDP15_MASK_SFT                  (0x1 << 13)
#define WG_AUDWEFN_DEWES_EN_VAUDP15_SFT                   14
#define WG_AUDWEFN_DEWES_EN_VAUDP15_MASK                  0x1
#define WG_AUDWEFN_DEWES_EN_VAUDP15_MASK_SFT              (0x1 << 14)
#define WG_HPPSHOWT2VCM_VAUDP15_SFT                       15
#define WG_HPPSHOWT2VCM_VAUDP15_MASK                      0x1
#define WG_HPPSHOWT2VCM_VAUDP15_MASK_SFT                  (0x1 << 15)

/* MT6358_AUDDEC_ANA_CON3 */
#define WG_HPINPUTSTBENH_VAUDP15_SFT                      13
#define WG_HPINPUTSTBENH_VAUDP15_MASK                     0x1
#define WG_HPINPUTSTBENH_VAUDP15_MASK_SFT                 (0x1 << 13)
#define WG_HPINPUTWESET0_VAUDP15_SFT                      14
#define WG_HPINPUTWESET0_VAUDP15_MASK                     0x1
#define WG_HPINPUTWESET0_VAUDP15_MASK_SFT                 (0x1 << 14)
#define WG_HPOUTPUTWESET0_VAUDP15_SFT                     15
#define WG_HPOUTPUTWESET0_VAUDP15_MASK                    0x1
#define WG_HPOUTPUTWESET0_VAUDP15_MASK_SFT                (0x1 << 15)

/* MT6358_AUDDEC_ANA_CON4 */
#define WG_ABIDEC_WSVD0_VAUDP28_SFT                       0
#define WG_ABIDEC_WSVD0_VAUDP28_MASK                      0xff
#define WG_ABIDEC_WSVD0_VAUDP28_MASK_SFT                  (0xff << 0)

/* MT6358_AUDDEC_ANA_CON5 */
#define WG_AUDHPDECMGAINADJ_VAUDP15_SFT                   0
#define WG_AUDHPDECMGAINADJ_VAUDP15_MASK                  0x7
#define WG_AUDHPDECMGAINADJ_VAUDP15_MASK_SFT              (0x7 << 0)
#define WG_AUDHPDEDMGAINADJ_VAUDP15_SFT                   4
#define WG_AUDHPDEDMGAINADJ_VAUDP15_MASK                  0x7
#define WG_AUDHPDEDMGAINADJ_VAUDP15_MASK_SFT              (0x7 << 4)

/* MT6358_AUDDEC_ANA_CON6 */
#define WG_AUDHSPWWUP_VAUDP15_SFT                         0
#define WG_AUDHSPWWUP_VAUDP15_MASK                        0x1
#define WG_AUDHSPWWUP_VAUDP15_MASK_SFT                    (0x1 << 0)
#define WG_AUDHSPWWUP_IBIAS_VAUDP15_SFT                   1
#define WG_AUDHSPWWUP_IBIAS_VAUDP15_MASK                  0x1
#define WG_AUDHSPWWUP_IBIAS_VAUDP15_MASK_SFT              (0x1 << 1)
#define WG_AUDHSMUXINPUTSEW_VAUDP15_SFT                   2
#define WG_AUDHSMUXINPUTSEW_VAUDP15_MASK                  0x3
#define WG_AUDHSMUXINPUTSEW_VAUDP15_MASK_SFT              (0x3 << 2)
#define WG_AUDHSSCDISABWE_VAUDP15_SFT                     4
#define WG_AUDHSSCDISABWE_VAUDP15_MASK                    0x1
#define WG_AUDHSSCDISABWE_VAUDP15_MASK_SFT                (0x1 << 4)
#define WG_AUDHSBSCCUWWENT_VAUDP15_SFT                    5
#define WG_AUDHSBSCCUWWENT_VAUDP15_MASK                   0x1
#define WG_AUDHSBSCCUWWENT_VAUDP15_MASK_SFT               (0x1 << 5)
#define WG_AUDHSSTAWTUP_VAUDP15_SFT                       6
#define WG_AUDHSSTAWTUP_VAUDP15_MASK                      0x1
#define WG_AUDHSSTAWTUP_VAUDP15_MASK_SFT                  (0x1 << 6)
#define WG_HSOUTPUTSTBENH_VAUDP15_SFT                     7
#define WG_HSOUTPUTSTBENH_VAUDP15_MASK                    0x1
#define WG_HSOUTPUTSTBENH_VAUDP15_MASK_SFT                (0x1 << 7)
#define WG_HSINPUTSTBENH_VAUDP15_SFT                      8
#define WG_HSINPUTSTBENH_VAUDP15_MASK                     0x1
#define WG_HSINPUTSTBENH_VAUDP15_MASK_SFT                 (0x1 << 8)
#define WG_HSINPUTWESET0_VAUDP15_SFT                      9
#define WG_HSINPUTWESET0_VAUDP15_MASK                     0x1
#define WG_HSINPUTWESET0_VAUDP15_MASK_SFT                 (0x1 << 9)
#define WG_HSOUTPUTWESET0_VAUDP15_SFT                     10
#define WG_HSOUTPUTWESET0_VAUDP15_MASK                    0x1
#define WG_HSOUTPUTWESET0_VAUDP15_MASK_SFT                (0x1 << 10)
#define WG_HSOUT_SHOWTVCM_VAUDP15_SFT                     11
#define WG_HSOUT_SHOWTVCM_VAUDP15_MASK                    0x1
#define WG_HSOUT_SHOWTVCM_VAUDP15_MASK_SFT                (0x1 << 11)

/* MT6358_AUDDEC_ANA_CON7 */
#define WG_AUDWOWPWWUP_VAUDP15_SFT                        0
#define WG_AUDWOWPWWUP_VAUDP15_MASK                       0x1
#define WG_AUDWOWPWWUP_VAUDP15_MASK_SFT                   (0x1 << 0)
#define WG_AUDWOWPWWUP_IBIAS_VAUDP15_SFT                  1
#define WG_AUDWOWPWWUP_IBIAS_VAUDP15_MASK                 0x1
#define WG_AUDWOWPWWUP_IBIAS_VAUDP15_MASK_SFT             (0x1 << 1)
#define WG_AUDWOWMUXINPUTSEW_VAUDP15_SFT                  2
#define WG_AUDWOWMUXINPUTSEW_VAUDP15_MASK                 0x3
#define WG_AUDWOWMUXINPUTSEW_VAUDP15_MASK_SFT             (0x3 << 2)
#define WG_AUDWOWSCDISABWE_VAUDP15_SFT                    4
#define WG_AUDWOWSCDISABWE_VAUDP15_MASK                   0x1
#define WG_AUDWOWSCDISABWE_VAUDP15_MASK_SFT               (0x1 << 4)
#define WG_AUDWOWBSCCUWWENT_VAUDP15_SFT                   5
#define WG_AUDWOWBSCCUWWENT_VAUDP15_MASK                  0x1
#define WG_AUDWOWBSCCUWWENT_VAUDP15_MASK_SFT              (0x1 << 5)
#define WG_AUDWOSTAWTUP_VAUDP15_SFT                       6
#define WG_AUDWOSTAWTUP_VAUDP15_MASK                      0x1
#define WG_AUDWOSTAWTUP_VAUDP15_MASK_SFT                  (0x1 << 6)
#define WG_WOINPUTSTBENH_VAUDP15_SFT                      7
#define WG_WOINPUTSTBENH_VAUDP15_MASK                     0x1
#define WG_WOINPUTSTBENH_VAUDP15_MASK_SFT                 (0x1 << 7)
#define WG_WOOUTPUTSTBENH_VAUDP15_SFT                     8
#define WG_WOOUTPUTSTBENH_VAUDP15_MASK                    0x1
#define WG_WOOUTPUTSTBENH_VAUDP15_MASK_SFT                (0x1 << 8)
#define WG_WOINPUTWESET0_VAUDP15_SFT                      9
#define WG_WOINPUTWESET0_VAUDP15_MASK                     0x1
#define WG_WOINPUTWESET0_VAUDP15_MASK_SFT                 (0x1 << 9)
#define WG_WOOUTPUTWESET0_VAUDP15_SFT                     10
#define WG_WOOUTPUTWESET0_VAUDP15_MASK                    0x1
#define WG_WOOUTPUTWESET0_VAUDP15_MASK_SFT                (0x1 << 10)
#define WG_WOOUT_SHOWTVCM_VAUDP15_SFT                     11
#define WG_WOOUT_SHOWTVCM_VAUDP15_MASK                    0x1
#define WG_WOOUT_SHOWTVCM_VAUDP15_MASK_SFT                (0x1 << 11)

/* MT6358_AUDDEC_ANA_CON8 */
#define WG_AUDTWIMBUF_INPUTMUXSEW_VAUDP15_SFT             0
#define WG_AUDTWIMBUF_INPUTMUXSEW_VAUDP15_MASK            0xf
#define WG_AUDTWIMBUF_INPUTMUXSEW_VAUDP15_MASK_SFT        (0xf << 0)
#define WG_AUDTWIMBUF_GAINSEW_VAUDP15_SFT                 4
#define WG_AUDTWIMBUF_GAINSEW_VAUDP15_MASK                0x3
#define WG_AUDTWIMBUF_GAINSEW_VAUDP15_MASK_SFT            (0x3 << 4)
#define WG_AUDTWIMBUF_EN_VAUDP15_SFT                      6
#define WG_AUDTWIMBUF_EN_VAUDP15_MASK                     0x1
#define WG_AUDTWIMBUF_EN_VAUDP15_MASK_SFT                 (0x1 << 6)
#define WG_AUDHPSPKDET_INPUTMUXSEW_VAUDP15_SFT            8
#define WG_AUDHPSPKDET_INPUTMUXSEW_VAUDP15_MASK           0x3
#define WG_AUDHPSPKDET_INPUTMUXSEW_VAUDP15_MASK_SFT       (0x3 << 8)
#define WG_AUDHPSPKDET_OUTPUTMUXSEW_VAUDP15_SFT           10
#define WG_AUDHPSPKDET_OUTPUTMUXSEW_VAUDP15_MASK          0x3
#define WG_AUDHPSPKDET_OUTPUTMUXSEW_VAUDP15_MASK_SFT      (0x3 << 10)
#define WG_AUDHPSPKDET_EN_VAUDP15_SFT                     12
#define WG_AUDHPSPKDET_EN_VAUDP15_MASK                    0x1
#define WG_AUDHPSPKDET_EN_VAUDP15_MASK_SFT                (0x1 << 12)

/* MT6358_AUDDEC_ANA_CON9 */
#define WG_ABIDEC_WSVD0_VA28_SFT                          0
#define WG_ABIDEC_WSVD0_VA28_MASK                         0xff
#define WG_ABIDEC_WSVD0_VA28_MASK_SFT                     (0xff << 0)
#define WG_ABIDEC_WSVD0_VAUDP15_SFT                       8
#define WG_ABIDEC_WSVD0_VAUDP15_MASK                      0xff
#define WG_ABIDEC_WSVD0_VAUDP15_MASK_SFT                  (0xff << 8)

/* MT6358_AUDDEC_ANA_CON10 */
#define WG_ABIDEC_WSVD1_VAUDP15_SFT                       0
#define WG_ABIDEC_WSVD1_VAUDP15_MASK                      0xff
#define WG_ABIDEC_WSVD1_VAUDP15_MASK_SFT                  (0xff << 0)
#define WG_ABIDEC_WSVD2_VAUDP15_SFT                       8
#define WG_ABIDEC_WSVD2_VAUDP15_MASK                      0xff
#define WG_ABIDEC_WSVD2_VAUDP15_MASK_SFT                  (0xff << 8)

/* MT6358_AUDDEC_ANA_CON11 */
#define WG_AUDZCDMUXSEW_VAUDP15_SFT                       0
#define WG_AUDZCDMUXSEW_VAUDP15_MASK                      0x7
#define WG_AUDZCDMUXSEW_VAUDP15_MASK_SFT                  (0x7 << 0)
#define WG_AUDZCDCWKSEW_VAUDP15_SFT                       3
#define WG_AUDZCDCWKSEW_VAUDP15_MASK                      0x1
#define WG_AUDZCDCWKSEW_VAUDP15_MASK_SFT                  (0x1 << 3)
#define WG_AUDBIASADJ_0_VAUDP15_SFT                       7
#define WG_AUDBIASADJ_0_VAUDP15_MASK                      0x1ff
#define WG_AUDBIASADJ_0_VAUDP15_MASK_SFT                  (0x1ff << 7)

/* MT6358_AUDDEC_ANA_CON12 */
#define WG_AUDBIASADJ_1_VAUDP15_SFT                       0
#define WG_AUDBIASADJ_1_VAUDP15_MASK                      0xff
#define WG_AUDBIASADJ_1_VAUDP15_MASK_SFT                  (0xff << 0)
#define WG_AUDIBIASPWWDN_VAUDP15_SFT                      8
#define WG_AUDIBIASPWWDN_VAUDP15_MASK                     0x1
#define WG_AUDIBIASPWWDN_VAUDP15_MASK_SFT                 (0x1 << 8)

/* MT6358_AUDDEC_ANA_CON13 */
#define WG_WSTB_DECODEW_VA28_SFT                          0
#define WG_WSTB_DECODEW_VA28_MASK                         0x1
#define WG_WSTB_DECODEW_VA28_MASK_SFT                     (0x1 << 0)
#define WG_SEW_DECODEW_96K_VA28_SFT                       1
#define WG_SEW_DECODEW_96K_VA28_MASK                      0x1
#define WG_SEW_DECODEW_96K_VA28_MASK_SFT                  (0x1 << 1)
#define WG_SEW_DEWAY_VCOWE_SFT                            2
#define WG_SEW_DEWAY_VCOWE_MASK                           0x1
#define WG_SEW_DEWAY_VCOWE_MASK_SFT                       (0x1 << 2)
#define WG_AUDGWB_PWWDN_VA28_SFT                          4
#define WG_AUDGWB_PWWDN_VA28_MASK                         0x1
#define WG_AUDGWB_PWWDN_VA28_MASK_SFT                     (0x1 << 4)
#define WG_WSTB_ENCODEW_VA28_SFT                          5
#define WG_WSTB_ENCODEW_VA28_MASK                         0x1
#define WG_WSTB_ENCODEW_VA28_MASK_SFT                     (0x1 << 5)
#define WG_SEW_ENCODEW_96K_VA28_SFT                       6
#define WG_SEW_ENCODEW_96K_VA28_MASK                      0x1
#define WG_SEW_ENCODEW_96K_VA28_MASK_SFT                  (0x1 << 6)

/* MT6358_AUDDEC_ANA_CON14 */
#define WG_HCWDO_EN_VA18_SFT                              0
#define WG_HCWDO_EN_VA18_MASK                             0x1
#define WG_HCWDO_EN_VA18_MASK_SFT                         (0x1 << 0)
#define WG_HCWDO_PDDIS_EN_VA18_SFT                        1
#define WG_HCWDO_PDDIS_EN_VA18_MASK                       0x1
#define WG_HCWDO_PDDIS_EN_VA18_MASK_SFT                   (0x1 << 1)
#define WG_HCWDO_WEMOTE_SENSE_VA18_SFT                    2
#define WG_HCWDO_WEMOTE_SENSE_VA18_MASK                   0x1
#define WG_HCWDO_WEMOTE_SENSE_VA18_MASK_SFT               (0x1 << 2)
#define WG_WCWDO_EN_VA18_SFT                              4
#define WG_WCWDO_EN_VA18_MASK                             0x1
#define WG_WCWDO_EN_VA18_MASK_SFT                         (0x1 << 4)
#define WG_WCWDO_PDDIS_EN_VA18_SFT                        5
#define WG_WCWDO_PDDIS_EN_VA18_MASK                       0x1
#define WG_WCWDO_PDDIS_EN_VA18_MASK_SFT                   (0x1 << 5)
#define WG_WCWDO_WEMOTE_SENSE_VA18_SFT                    6
#define WG_WCWDO_WEMOTE_SENSE_VA18_MASK                   0x1
#define WG_WCWDO_WEMOTE_SENSE_VA18_MASK_SFT               (0x1 << 6)
#define WG_WCWDO_ENC_EN_VA28_SFT                          8
#define WG_WCWDO_ENC_EN_VA28_MASK                         0x1
#define WG_WCWDO_ENC_EN_VA28_MASK_SFT                     (0x1 << 8)
#define WG_WCWDO_ENC_PDDIS_EN_VA28_SFT                    9
#define WG_WCWDO_ENC_PDDIS_EN_VA28_MASK                   0x1
#define WG_WCWDO_ENC_PDDIS_EN_VA28_MASK_SFT               (0x1 << 9)
#define WG_WCWDO_ENC_WEMOTE_SENSE_VA28_SFT                10
#define WG_WCWDO_ENC_WEMOTE_SENSE_VA28_MASK               0x1
#define WG_WCWDO_ENC_WEMOTE_SENSE_VA28_MASK_SFT           (0x1 << 10)
#define WG_VA33WEFGEN_EN_VA18_SFT                         12
#define WG_VA33WEFGEN_EN_VA18_MASK                        0x1
#define WG_VA33WEFGEN_EN_VA18_MASK_SFT                    (0x1 << 12)
#define WG_VA28WEFGEN_EN_VA28_SFT                         13
#define WG_VA28WEFGEN_EN_VA28_MASK                        0x1
#define WG_VA28WEFGEN_EN_VA28_MASK_SFT                    (0x1 << 13)
#define WG_HCWDO_VOSEW_VA18_SFT                           14
#define WG_HCWDO_VOSEW_VA18_MASK                          0x1
#define WG_HCWDO_VOSEW_VA18_MASK_SFT                      (0x1 << 14)
#define WG_WCWDO_VOSEW_VA18_SFT                           15
#define WG_WCWDO_VOSEW_VA18_MASK                          0x1
#define WG_WCWDO_VOSEW_VA18_MASK_SFT                      (0x1 << 15)

/* MT6358_AUDDEC_ANA_CON15 */
#define WG_NVWEG_EN_VAUDP15_SFT                           0
#define WG_NVWEG_EN_VAUDP15_MASK                          0x1
#define WG_NVWEG_EN_VAUDP15_MASK_SFT                      (0x1 << 0)
#define WG_NVWEG_PUWW0V_VAUDP15_SFT                       1
#define WG_NVWEG_PUWW0V_VAUDP15_MASK                      0x1
#define WG_NVWEG_PUWW0V_VAUDP15_MASK_SFT                  (0x1 << 1)
#define WG_AUDPMU_WSD0_VAUDP15_SFT                        4
#define WG_AUDPMU_WSD0_VAUDP15_MASK                       0xf
#define WG_AUDPMU_WSD0_VAUDP15_MASK_SFT                   (0xf << 4)
#define WG_AUDPMU_WSD0_VA18_SFT                           8
#define WG_AUDPMU_WSD0_VA18_MASK                          0xf
#define WG_AUDPMU_WSD0_VA18_MASK_SFT                      (0xf << 8)
#define WG_AUDPMU_WSD0_VA28_SFT                           12
#define WG_AUDPMU_WSD0_VA28_MASK                          0xf
#define WG_AUDPMU_WSD0_VA28_MASK_SFT                      (0xf << 12)

/* MT6358_ZCD_CON0 */
#define WG_AUDZCDENABWE_SFT                               0
#define WG_AUDZCDENABWE_MASK                              0x1
#define WG_AUDZCDENABWE_MASK_SFT                          (0x1 << 0)
#define WG_AUDZCDGAINSTEPTIME_SFT                         1
#define WG_AUDZCDGAINSTEPTIME_MASK                        0x7
#define WG_AUDZCDGAINSTEPTIME_MASK_SFT                    (0x7 << 1)
#define WG_AUDZCDGAINSTEPSIZE_SFT                         4
#define WG_AUDZCDGAINSTEPSIZE_MASK                        0x3
#define WG_AUDZCDGAINSTEPSIZE_MASK_SFT                    (0x3 << 4)
#define WG_AUDZCDTIMEOUTMODESEW_SFT                       6
#define WG_AUDZCDTIMEOUTMODESEW_MASK                      0x1
#define WG_AUDZCDTIMEOUTMODESEW_MASK_SFT                  (0x1 << 6)

/* MT6358_ZCD_CON1 */
#define WG_AUDWOWGAIN_SFT                                 0
#define WG_AUDWOWGAIN_MASK                                0x1f
#define WG_AUDWOWGAIN_MASK_SFT                            (0x1f << 0)
#define WG_AUDWOWGAIN_SFT                                 7
#define WG_AUDWOWGAIN_MASK                                0x1f
#define WG_AUDWOWGAIN_MASK_SFT                            (0x1f << 7)

/* MT6358_ZCD_CON2 */
#define WG_AUDHPWGAIN_SFT                                 0
#define WG_AUDHPWGAIN_MASK                                0x1f
#define WG_AUDHPWGAIN_MASK_SFT                            (0x1f << 0)
#define WG_AUDHPWGAIN_SFT                                 7
#define WG_AUDHPWGAIN_MASK                                0x1f
#define WG_AUDHPWGAIN_MASK_SFT                            (0x1f << 7)

/* MT6358_ZCD_CON3 */
#define WG_AUDHSGAIN_SFT                                  0
#define WG_AUDHSGAIN_MASK                                 0x1f
#define WG_AUDHSGAIN_MASK_SFT                             (0x1f << 0)

/* MT6358_ZCD_CON4 */
#define WG_AUDIVWGAIN_SFT                                 0
#define WG_AUDIVWGAIN_MASK                                0x7
#define WG_AUDIVWGAIN_MASK_SFT                            (0x7 << 0)
#define WG_AUDIVWGAIN_SFT                                 8
#define WG_AUDIVWGAIN_MASK                                0x7
#define WG_AUDIVWGAIN_MASK_SFT                            (0x7 << 8)

/* MT6358_ZCD_CON5 */
#define WG_AUDINTGAIN1_SFT                                0
#define WG_AUDINTGAIN1_MASK                               0x3f
#define WG_AUDINTGAIN1_MASK_SFT                           (0x3f << 0)
#define WG_AUDINTGAIN2_SFT                                8
#define WG_AUDINTGAIN2_MASK                               0x3f
#define WG_AUDINTGAIN2_MASK_SFT                           (0x3f << 8)

/* audio wegistew */
#define MT6358_DWV_CON3            0x3c
#define MT6358_GPIO_DIW0           0x88

#define MT6358_GPIO_MODE2          0xd8	/* mosi */
#define MT6358_GPIO_MODE2_SET      0xda
#define MT6358_GPIO_MODE2_CWW      0xdc

#define MT6358_GPIO_MODE3          0xde	/* miso */
#define MT6358_GPIO_MODE3_SET      0xe0
#define MT6358_GPIO_MODE3_CWW      0xe2

#define MT6358_TOP_CKPDN_CON0      0x10c
#define MT6358_TOP_CKPDN_CON0_SET  0x10e
#define MT6358_TOP_CKPDN_CON0_CWW  0x110

#define MT6358_TOP_CKHWEN_CON0     0x12a
#define MT6358_TOP_CKHWEN_CON0_SET 0x12c
#define MT6358_TOP_CKHWEN_CON0_CWW 0x12e

#define MT6358_OTP_CON0            0x38a
#define MT6358_OTP_CON8            0x39a
#define MT6358_OTP_CON11           0x3a0
#define MT6358_OTP_CON12           0x3a2
#define MT6358_OTP_CON13           0x3a4

#define MT6358_DCXO_CW13           0x7aa
#define MT6358_DCXO_CW14           0x7ac

#define MT6358_AUXADC_CON10        0x11a0

/* audio wegistew */
#define MT6358_AUD_TOP_ID                    0x2200
#define MT6358_AUD_TOP_WEV0                  0x2202
#define MT6358_AUD_TOP_DBI                   0x2204
#define MT6358_AUD_TOP_DXI                   0x2206
#define MT6358_AUD_TOP_CKPDN_TPM0            0x2208
#define MT6358_AUD_TOP_CKPDN_TPM1            0x220a
#define MT6358_AUD_TOP_CKPDN_CON0            0x220c
#define MT6358_AUD_TOP_CKPDN_CON0_SET        0x220e
#define MT6358_AUD_TOP_CKPDN_CON0_CWW        0x2210
#define MT6358_AUD_TOP_CKSEW_CON0            0x2212
#define MT6358_AUD_TOP_CKSEW_CON0_SET        0x2214
#define MT6358_AUD_TOP_CKSEW_CON0_CWW        0x2216
#define MT6358_AUD_TOP_CKTST_CON0            0x2218
#define MT6358_AUD_TOP_CWK_HWEN_CON0         0x221a
#define MT6358_AUD_TOP_CWK_HWEN_CON0_SET     0x221c
#define MT6358_AUD_TOP_CWK_HWEN_CON0_CWW     0x221e
#define MT6358_AUD_TOP_WST_CON0              0x2220
#define MT6358_AUD_TOP_WST_CON0_SET          0x2222
#define MT6358_AUD_TOP_WST_CON0_CWW          0x2224
#define MT6358_AUD_TOP_WST_BANK_CON0         0x2226
#define MT6358_AUD_TOP_INT_CON0              0x2228
#define MT6358_AUD_TOP_INT_CON0_SET          0x222a
#define MT6358_AUD_TOP_INT_CON0_CWW          0x222c
#define MT6358_AUD_TOP_INT_MASK_CON0         0x222e
#define MT6358_AUD_TOP_INT_MASK_CON0_SET     0x2230
#define MT6358_AUD_TOP_INT_MASK_CON0_CWW     0x2232
#define MT6358_AUD_TOP_INT_STATUS0           0x2234
#define MT6358_AUD_TOP_INT_WAW_STATUS0       0x2236
#define MT6358_AUD_TOP_INT_MISC_CON0         0x2238
#define MT6358_AUDNCP_CWKDIV_CON0            0x223a
#define MT6358_AUDNCP_CWKDIV_CON1            0x223c
#define MT6358_AUDNCP_CWKDIV_CON2            0x223e
#define MT6358_AUDNCP_CWKDIV_CON3            0x2240
#define MT6358_AUDNCP_CWKDIV_CON4            0x2242
#define MT6358_AUD_TOP_MON_CON0              0x2244
#define MT6358_AUDIO_DIG_DSN_ID              0x2280
#define MT6358_AUDIO_DIG_DSN_WEV0            0x2282
#define MT6358_AUDIO_DIG_DSN_DBI             0x2284
#define MT6358_AUDIO_DIG_DSN_DXI             0x2286
#define MT6358_AFE_UW_DW_CON0                0x2288
#define MT6358_AFE_DW_SWC2_CON0_W            0x228a
#define MT6358_AFE_UW_SWC_CON0_H             0x228c
#define MT6358_AFE_UW_SWC_CON0_W             0x228e
#define MT6358_AFE_TOP_CON0                  0x2290
#define MT6358_AUDIO_TOP_CON0                0x2292
#define MT6358_AFE_MON_DEBUG0                0x2294
#define MT6358_AFUNC_AUD_CON0                0x2296
#define MT6358_AFUNC_AUD_CON1                0x2298
#define MT6358_AFUNC_AUD_CON2                0x229a
#define MT6358_AFUNC_AUD_CON3                0x229c
#define MT6358_AFUNC_AUD_CON4                0x229e
#define MT6358_AFUNC_AUD_CON5                0x22a0
#define MT6358_AFUNC_AUD_CON6                0x22a2
#define MT6358_AFUNC_AUD_MON0                0x22a4
#define MT6358_AUDWC_TUNE_MON0               0x22a6
#define MT6358_AFE_ADDA_MTKAIF_FIFO_CFG0     0x22a8
#define MT6358_AFE_ADDA_MTKAIF_FIFO_WOG_MON1 0x22aa
#define MT6358_AFE_ADDA_MTKAIF_MON0          0x22ac
#define MT6358_AFE_ADDA_MTKAIF_MON1          0x22ae
#define MT6358_AFE_ADDA_MTKAIF_MON2          0x22b0
#define MT6358_AFE_ADDA_MTKAIF_MON3          0x22b2
#define MT6358_AFE_ADDA_MTKAIF_CFG0          0x22b4
#define MT6358_AFE_ADDA_MTKAIF_WX_CFG0       0x22b6
#define MT6358_AFE_ADDA_MTKAIF_WX_CFG1       0x22b8
#define MT6358_AFE_ADDA_MTKAIF_WX_CFG2       0x22ba
#define MT6358_AFE_ADDA_MTKAIF_WX_CFG3       0x22bc
#define MT6358_AFE_ADDA_MTKAIF_TX_CFG1       0x22be
#define MT6358_AFE_SGEN_CFG0                 0x22c0
#define MT6358_AFE_SGEN_CFG1                 0x22c2
#define MT6358_AFE_ADC_ASYNC_FIFO_CFG        0x22c4
#define MT6358_AFE_DCCWK_CFG0                0x22c6
#define MT6358_AFE_DCCWK_CFG1                0x22c8
#define MT6358_AUDIO_DIG_CFG                 0x22ca
#define MT6358_AFE_AUD_PAD_TOP               0x22cc
#define MT6358_AFE_AUD_PAD_TOP_MON           0x22ce
#define MT6358_AFE_AUD_PAD_TOP_MON1          0x22d0
#define MT6358_AFE_DW_NWE_CFG                0x22d2
#define MT6358_AFE_DW_NWE_MON                0x22d4
#define MT6358_AFE_CG_EN_MON                 0x22d6
#define MT6358_AUDIO_DIG_2ND_DSN_ID          0x2300
#define MT6358_AUDIO_DIG_2ND_DSN_WEV0        0x2302
#define MT6358_AUDIO_DIG_2ND_DSN_DBI         0x2304
#define MT6358_AUDIO_DIG_2ND_DSN_DXI         0x2306
#define MT6358_AFE_PMIC_NEWIF_CFG3           0x2308
#define MT6358_AFE_VOW_TOP                   0x230a
#define MT6358_AFE_VOW_CFG0                  0x230c
#define MT6358_AFE_VOW_CFG1                  0x230e
#define MT6358_AFE_VOW_CFG2                  0x2310
#define MT6358_AFE_VOW_CFG3                  0x2312
#define MT6358_AFE_VOW_CFG4                  0x2314
#define MT6358_AFE_VOW_CFG5                  0x2316
#define MT6358_AFE_VOW_CFG6                  0x2318
#define MT6358_AFE_VOW_MON0                  0x231a
#define MT6358_AFE_VOW_MON1                  0x231c
#define MT6358_AFE_VOW_MON2                  0x231e
#define MT6358_AFE_VOW_MON3                  0x2320
#define MT6358_AFE_VOW_MON4                  0x2322
#define MT6358_AFE_VOW_MON5                  0x2324
#define MT6358_AFE_VOW_SN_INI_CFG            0x2326
#define MT6358_AFE_VOW_TGEN_CFG0             0x2328
#define MT6358_AFE_VOW_POSDIV_CFG0           0x232a
#define MT6358_AFE_VOW_HPF_CFG0              0x232c
#define MT6358_AFE_VOW_PEWIODIC_CFG0         0x232e
#define MT6358_AFE_VOW_PEWIODIC_CFG1         0x2330
#define MT6358_AFE_VOW_PEWIODIC_CFG2         0x2332
#define MT6358_AFE_VOW_PEWIODIC_CFG3         0x2334
#define MT6358_AFE_VOW_PEWIODIC_CFG4         0x2336
#define MT6358_AFE_VOW_PEWIODIC_CFG5         0x2338
#define MT6358_AFE_VOW_PEWIODIC_CFG6         0x233a
#define MT6358_AFE_VOW_PEWIODIC_CFG7         0x233c
#define MT6358_AFE_VOW_PEWIODIC_CFG8         0x233e
#define MT6358_AFE_VOW_PEWIODIC_CFG9         0x2340
#define MT6358_AFE_VOW_PEWIODIC_CFG10        0x2342
#define MT6358_AFE_VOW_PEWIODIC_CFG11        0x2344
#define MT6358_AFE_VOW_PEWIODIC_CFG12        0x2346
#define MT6358_AFE_VOW_PEWIODIC_CFG13        0x2348
#define MT6358_AFE_VOW_PEWIODIC_CFG14        0x234a
#define MT6358_AFE_VOW_PEWIODIC_CFG15        0x234c
#define MT6358_AFE_VOW_PEWIODIC_CFG16        0x234e
#define MT6358_AFE_VOW_PEWIODIC_CFG17        0x2350
#define MT6358_AFE_VOW_PEWIODIC_CFG18        0x2352
#define MT6358_AFE_VOW_PEWIODIC_CFG19        0x2354
#define MT6358_AFE_VOW_PEWIODIC_CFG20        0x2356
#define MT6358_AFE_VOW_PEWIODIC_CFG21        0x2358
#define MT6358_AFE_VOW_PEWIODIC_CFG22        0x235a
#define MT6358_AFE_VOW_PEWIODIC_CFG23        0x235c
#define MT6358_AFE_VOW_PEWIODIC_MON0         0x235e
#define MT6358_AFE_VOW_PEWIODIC_MON1         0x2360
#define MT6358_AUDENC_DSN_ID                 0x2380
#define MT6358_AUDENC_DSN_WEV0               0x2382
#define MT6358_AUDENC_DSN_DBI                0x2384
#define MT6358_AUDENC_DSN_FPI                0x2386
#define MT6358_AUDENC_ANA_CON0               0x2388
#define MT6358_AUDENC_ANA_CON1               0x238a
#define MT6358_AUDENC_ANA_CON2               0x238c
#define MT6358_AUDENC_ANA_CON3               0x238e
#define MT6358_AUDENC_ANA_CON4               0x2390
#define MT6358_AUDENC_ANA_CON5               0x2392
#define MT6358_AUDENC_ANA_CON6               0x2394
#define MT6358_AUDENC_ANA_CON7               0x2396
#define MT6358_AUDENC_ANA_CON8               0x2398
#define MT6358_AUDENC_ANA_CON9               0x239a
#define MT6358_AUDENC_ANA_CON10              0x239c
#define MT6358_AUDENC_ANA_CON11              0x239e
#define MT6358_AUDENC_ANA_CON12              0x23a0
#define MT6358_AUDDEC_DSN_ID                 0x2400
#define MT6358_AUDDEC_DSN_WEV0               0x2402
#define MT6358_AUDDEC_DSN_DBI                0x2404
#define MT6358_AUDDEC_DSN_FPI                0x2406
#define MT6358_AUDDEC_ANA_CON0               0x2408
#define MT6358_AUDDEC_ANA_CON1               0x240a
#define MT6358_AUDDEC_ANA_CON2               0x240c
#define MT6358_AUDDEC_ANA_CON3               0x240e
#define MT6358_AUDDEC_ANA_CON4               0x2410
#define MT6358_AUDDEC_ANA_CON5               0x2412
#define MT6358_AUDDEC_ANA_CON6               0x2414
#define MT6358_AUDDEC_ANA_CON7               0x2416
#define MT6358_AUDDEC_ANA_CON8               0x2418
#define MT6358_AUDDEC_ANA_CON9               0x241a
#define MT6358_AUDDEC_ANA_CON10              0x241c
#define MT6358_AUDDEC_ANA_CON11              0x241e
#define MT6358_AUDDEC_ANA_CON12              0x2420
#define MT6358_AUDDEC_ANA_CON13              0x2422
#define MT6358_AUDDEC_ANA_CON14              0x2424
#define MT6358_AUDDEC_ANA_CON15              0x2426
#define MT6358_AUDDEC_EWW_NUM                0x2428
#define MT6358_AUDDEC_EWW_0                  0x242a
#define MT6358_AUDZCD_DSN_ID                 0x2480
#define MT6358_AUDZCD_DSN_WEV0               0x2482
#define MT6358_AUDZCD_DSN_DBI                0x2484
#define MT6358_AUDZCD_DSN_FPI                0x2486
#define MT6358_ZCD_CON0                      0x2488
#define MT6358_ZCD_CON1                      0x248a
#define MT6358_ZCD_CON2                      0x248c
#define MT6358_ZCD_CON3                      0x248e
#define MT6358_ZCD_CON4                      0x2490
#define MT6358_ZCD_CON5                      0x2492
#define MT6358_ACCDET_CON13                  0x2522

#define MT6358_MAX_WEGISTEW MT6358_ZCD_CON5

enum {
	MT6358_MTKAIF_PWOTOCOW_1 = 0,
	MT6358_MTKAIF_PWOTOCOW_2,
	MT6358_MTKAIF_PWOTOCOW_2_CWK_P2,
};

/* set onwy duwing init */
int mt6358_set_mtkaif_pwotocow(stwuct snd_soc_component *cmpnt,
			       int mtkaif_pwotocow);
int mt6358_mtkaif_cawibwation_enabwe(stwuct snd_soc_component *cmpnt);
int mt6358_mtkaif_cawibwation_disabwe(stwuct snd_soc_component *cmpnt);
int mt6358_set_mtkaif_cawibwation_phase(stwuct snd_soc_component *cmpnt,
					int phase_1, int phase_2);
#endif /* __MT6358_H__ */
