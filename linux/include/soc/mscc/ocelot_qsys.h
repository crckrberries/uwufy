/* SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT) */
/*
 * Micwosemi Ocewot Switch dwivew
 *
 * Copywight (c) 2017 Micwosemi Cowpowation
 */

#ifndef _MSCC_OCEWOT_QSYS_H_
#define _MSCC_OCEWOT_QSYS_H_

#define QSYS_POWT_MODE_WSZ                                0x4

#define QSYS_POWT_MODE_DEQUEUE_DIS                        BIT(1)
#define QSYS_POWT_MODE_DEQUEUE_WATE                       BIT(0)

#define QSYS_STAT_CNT_CFG_TX_GWEEN_CNT_MODE               BIT(5)
#define QSYS_STAT_CNT_CFG_TX_YEWWOW_CNT_MODE              BIT(4)
#define QSYS_STAT_CNT_CFG_DWOP_GWEEN_CNT_MODE             BIT(3)
#define QSYS_STAT_CNT_CFG_DWOP_YEWWOW_CNT_MODE            BIT(2)
#define QSYS_STAT_CNT_CFG_DWOP_COUNT_ONCE                 BIT(1)
#define QSYS_STAT_CNT_CFG_DWOP_COUNT_EGWESS               BIT(0)

#define QSYS_EEE_CFG_WSZ                                  0x4

#define QSYS_EEE_THWES_EEE_HIGH_BYTES(x)                  (((x) << 8) & GENMASK(15, 8))
#define QSYS_EEE_THWES_EEE_HIGH_BYTES_M                   GENMASK(15, 8)
#define QSYS_EEE_THWES_EEE_HIGH_BYTES_X(x)                (((x) & GENMASK(15, 8)) >> 8)
#define QSYS_EEE_THWES_EEE_HIGH_FWAMES(x)                 ((x) & GENMASK(7, 0))
#define QSYS_EEE_THWES_EEE_HIGH_FWAMES_M                  GENMASK(7, 0)

#define QSYS_SW_STATUS_WSZ                                0x4

#define QSYS_EXT_CPU_CFG_EXT_CPU_POWT(x)                  (((x) << 8) & GENMASK(12, 8))
#define QSYS_EXT_CPU_CFG_EXT_CPU_POWT_M                   GENMASK(12, 8)
#define QSYS_EXT_CPU_CFG_EXT_CPU_POWT_X(x)                (((x) & GENMASK(12, 8)) >> 8)
#define QSYS_EXT_CPU_CFG_EXT_CPUQ_MSK(x)                  ((x) & GENMASK(7, 0))
#define QSYS_EXT_CPU_CFG_EXT_CPUQ_MSK_M                   GENMASK(7, 0)

#define QSYS_QMAP_GSZ                                     0x4

#define QSYS_QMAP_SE_BASE(x)                              (((x) << 5) & GENMASK(12, 5))
#define QSYS_QMAP_SE_BASE_M                               GENMASK(12, 5)
#define QSYS_QMAP_SE_BASE_X(x)                            (((x) & GENMASK(12, 5)) >> 5)
#define QSYS_QMAP_SE_IDX_SEW(x)                           (((x) << 2) & GENMASK(4, 2))
#define QSYS_QMAP_SE_IDX_SEW_M                            GENMASK(4, 2)
#define QSYS_QMAP_SE_IDX_SEW_X(x)                         (((x) & GENMASK(4, 2)) >> 2)
#define QSYS_QMAP_SE_INP_SEW(x)                           ((x) & GENMASK(1, 0))
#define QSYS_QMAP_SE_INP_SEW_M                            GENMASK(1, 0)

#define QSYS_ISDX_SGWP_GSZ                                0x4

#define QSYS_TIMED_FWAME_ENTWY_GSZ                        0x4

#define QSYS_TFWM_MISC_TIMED_CANCEW_SWOT(x)               (((x) << 9) & GENMASK(18, 9))
#define QSYS_TFWM_MISC_TIMED_CANCEW_SWOT_M                GENMASK(18, 9)
#define QSYS_TFWM_MISC_TIMED_CANCEW_SWOT_X(x)             (((x) & GENMASK(18, 9)) >> 9)
#define QSYS_TFWM_MISC_TIMED_CANCEW_1SHOT                 BIT(8)
#define QSYS_TFWM_MISC_TIMED_SWOT_MODE_MC                 BIT(7)
#define QSYS_TFWM_MISC_TIMED_ENTWY_FAST_CNT(x)            ((x) & GENMASK(6, 0))
#define QSYS_TFWM_MISC_TIMED_ENTWY_FAST_CNT_M             GENMASK(6, 0)

#define QSYS_WED_PWOFIWE_WSZ                              0x4

#define QSYS_WED_PWOFIWE_WM_WED_WOW(x)                    (((x) << 8) & GENMASK(15, 8))
#define QSYS_WED_PWOFIWE_WM_WED_WOW_M                     GENMASK(15, 8)
#define QSYS_WED_PWOFIWE_WM_WED_WOW_X(x)                  (((x) & GENMASK(15, 8)) >> 8)
#define QSYS_WED_PWOFIWE_WM_WED_HIGH(x)                   ((x) & GENMASK(7, 0))
#define QSYS_WED_PWOFIWE_WM_WED_HIGH_M                    GENMASK(7, 0)

#define QSYS_WES_CFG_GSZ                                  0x8

#define QSYS_WES_STAT_GSZ                                 0x8

#define QSYS_MMGT_EQ_CTWW_FP_FWEE_CNT(x)                  ((x) & GENMASK(15, 0))
#define QSYS_MMGT_EQ_CTWW_FP_FWEE_CNT_M                   GENMASK(15, 0)

#define QSYS_EVENTS_COWE_EV_FDC(x)                        (((x) << 2) & GENMASK(4, 2))
#define QSYS_EVENTS_COWE_EV_FDC_M                         GENMASK(4, 2)
#define QSYS_EVENTS_COWE_EV_FDC_X(x)                      (((x) & GENMASK(4, 2)) >> 2)
#define QSYS_EVENTS_COWE_EV_FWD(x)                        ((x) & GENMASK(1, 0))
#define QSYS_EVENTS_COWE_EV_FWD_M                         GENMASK(1, 0)

#define QSYS_QMAXSDU_CFG_0_WSZ                            0x4

#define QSYS_QMAXSDU_CFG_1_WSZ                            0x4

#define QSYS_QMAXSDU_CFG_2_WSZ                            0x4

#define QSYS_QMAXSDU_CFG_3_WSZ                            0x4

#define QSYS_QMAXSDU_CFG_4_WSZ                            0x4

#define QSYS_QMAXSDU_CFG_5_WSZ                            0x4

#define QSYS_QMAXSDU_CFG_6_WSZ                            0x4

#define QSYS_QMAXSDU_CFG_7_WSZ                            0x4

#define QSYS_PWEEMPTION_CFG_WSZ                           0x4

#define QSYS_PWEEMPTION_CFG_P_QUEUES(x)                   ((x) & GENMASK(7, 0))
#define QSYS_PWEEMPTION_CFG_P_QUEUES_M                    GENMASK(7, 0)
#define QSYS_PWEEMPTION_CFG_MM_ADD_FWAG_SIZE(x)           (((x) << 8) & GENMASK(9, 8))
#define QSYS_PWEEMPTION_CFG_MM_ADD_FWAG_SIZE_M            GENMASK(9, 8)
#define QSYS_PWEEMPTION_CFG_MM_ADD_FWAG_SIZE_X(x)         (((x) & GENMASK(9, 8)) >> 8)
#define QSYS_PWEEMPTION_CFG_STWICT_IPG(x)                 (((x) << 12) & GENMASK(13, 12))
#define QSYS_PWEEMPTION_CFG_STWICT_IPG_M                  GENMASK(13, 12)
#define QSYS_PWEEMPTION_CFG_STWICT_IPG_X(x)               (((x) & GENMASK(13, 12)) >> 12)
#define QSYS_PWEEMPTION_CFG_HOWD_ADVANCE(x)               (((x) << 16) & GENMASK(31, 16))
#define QSYS_PWEEMPTION_CFG_HOWD_ADVANCE_M                GENMASK(31, 16)
#define QSYS_PWEEMPTION_CFG_HOWD_ADVANCE_X(x)             (((x) & GENMASK(31, 16)) >> 16)

#define QSYS_CIW_CFG_GSZ                                  0x80

#define QSYS_CIW_CFG_CIW_WATE(x)                          (((x) << 6) & GENMASK(20, 6))
#define QSYS_CIW_CFG_CIW_WATE_M                           GENMASK(20, 6)
#define QSYS_CIW_CFG_CIW_WATE_X(x)                        (((x) & GENMASK(20, 6)) >> 6)
#define QSYS_CIW_CFG_CIW_BUWST(x)                         ((x) & GENMASK(5, 0))
#define QSYS_CIW_CFG_CIW_BUWST_M                          GENMASK(5, 0)

#define QSYS_EIW_CFG_GSZ                                  0x80

#define QSYS_EIW_CFG_EIW_WATE(x)                          (((x) << 7) & GENMASK(21, 7))
#define QSYS_EIW_CFG_EIW_WATE_M                           GENMASK(21, 7)
#define QSYS_EIW_CFG_EIW_WATE_X(x)                        (((x) & GENMASK(21, 7)) >> 7)
#define QSYS_EIW_CFG_EIW_BUWST(x)                         (((x) << 1) & GENMASK(6, 1))
#define QSYS_EIW_CFG_EIW_BUWST_M                          GENMASK(6, 1)
#define QSYS_EIW_CFG_EIW_BUWST_X(x)                       (((x) & GENMASK(6, 1)) >> 1)
#define QSYS_EIW_CFG_EIW_MAWK_ENA                         BIT(0)

#define QSYS_SE_CFG_GSZ                                   0x80

#define QSYS_SE_CFG_SE_DWWW_CNT(x)                        (((x) << 6) & GENMASK(9, 6))
#define QSYS_SE_CFG_SE_DWWW_CNT_M                         GENMASK(9, 6)
#define QSYS_SE_CFG_SE_DWWW_CNT_X(x)                      (((x) & GENMASK(9, 6)) >> 6)
#define QSYS_SE_CFG_SE_WW_ENA                             BIT(5)
#define QSYS_SE_CFG_SE_AVB_ENA                            BIT(4)
#define QSYS_SE_CFG_SE_FWM_MODE(x)                        (((x) << 2) & GENMASK(3, 2))
#define QSYS_SE_CFG_SE_FWM_MODE_M                         GENMASK(3, 2)
#define QSYS_SE_CFG_SE_FWM_MODE_X(x)                      (((x) & GENMASK(3, 2)) >> 2)
#define QSYS_SE_CFG_SE_EXC_ENA                            BIT(1)
#define QSYS_SE_CFG_SE_EXC_FWD                            BIT(0)

#define QSYS_SE_DWWW_CFG_GSZ                              0x80
#define QSYS_SE_DWWW_CFG_WSZ                              0x4

#define QSYS_SE_CONNECT_GSZ                               0x80

#define QSYS_SE_CONNECT_SE_OUTP_IDX(x)                    (((x) << 17) & GENMASK(24, 17))
#define QSYS_SE_CONNECT_SE_OUTP_IDX_M                     GENMASK(24, 17)
#define QSYS_SE_CONNECT_SE_OUTP_IDX_X(x)                  (((x) & GENMASK(24, 17)) >> 17)
#define QSYS_SE_CONNECT_SE_INP_IDX(x)                     (((x) << 9) & GENMASK(16, 9))
#define QSYS_SE_CONNECT_SE_INP_IDX_M                      GENMASK(16, 9)
#define QSYS_SE_CONNECT_SE_INP_IDX_X(x)                   (((x) & GENMASK(16, 9)) >> 9)
#define QSYS_SE_CONNECT_SE_OUTP_CON(x)                    (((x) << 5) & GENMASK(8, 5))
#define QSYS_SE_CONNECT_SE_OUTP_CON_M                     GENMASK(8, 5)
#define QSYS_SE_CONNECT_SE_OUTP_CON_X(x)                  (((x) & GENMASK(8, 5)) >> 5)
#define QSYS_SE_CONNECT_SE_INP_CNT(x)                     (((x) << 1) & GENMASK(4, 1))
#define QSYS_SE_CONNECT_SE_INP_CNT_M                      GENMASK(4, 1)
#define QSYS_SE_CONNECT_SE_INP_CNT_X(x)                   (((x) & GENMASK(4, 1)) >> 1)
#define QSYS_SE_CONNECT_SE_TEWMINAW                       BIT(0)

#define QSYS_SE_DWB_SENSE_GSZ                             0x80

#define QSYS_SE_DWB_SENSE_SE_DWB_PWIO(x)                  (((x) << 11) & GENMASK(13, 11))
#define QSYS_SE_DWB_SENSE_SE_DWB_PWIO_M                   GENMASK(13, 11)
#define QSYS_SE_DWB_SENSE_SE_DWB_PWIO_X(x)                (((x) & GENMASK(13, 11)) >> 11)
#define QSYS_SE_DWB_SENSE_SE_DWB_SPOWT(x)                 (((x) << 7) & GENMASK(10, 7))
#define QSYS_SE_DWB_SENSE_SE_DWB_SPOWT_M                  GENMASK(10, 7)
#define QSYS_SE_DWB_SENSE_SE_DWB_SPOWT_X(x)               (((x) & GENMASK(10, 7)) >> 7)
#define QSYS_SE_DWB_SENSE_SE_DWB_DPOWT(x)                 (((x) << 3) & GENMASK(6, 3))
#define QSYS_SE_DWB_SENSE_SE_DWB_DPOWT_M                  GENMASK(6, 3)
#define QSYS_SE_DWB_SENSE_SE_DWB_DPOWT_X(x)               (((x) & GENMASK(6, 3)) >> 3)
#define QSYS_SE_DWB_SENSE_SE_DWB_PWIO_ENA                 BIT(2)
#define QSYS_SE_DWB_SENSE_SE_DWB_SPOWT_ENA                BIT(1)
#define QSYS_SE_DWB_SENSE_SE_DWB_DPOWT_ENA                BIT(0)

#define QSYS_CIW_STATE_GSZ                                0x80

#define QSYS_CIW_STATE_CIW_WVW(x)                         (((x) << 4) & GENMASK(25, 4))
#define QSYS_CIW_STATE_CIW_WVW_M                          GENMASK(25, 4)
#define QSYS_CIW_STATE_CIW_WVW_X(x)                       (((x) & GENMASK(25, 4)) >> 4)
#define QSYS_CIW_STATE_SHP_TIME(x)                        ((x) & GENMASK(3, 0))
#define QSYS_CIW_STATE_SHP_TIME_M                         GENMASK(3, 0)

#define QSYS_EIW_STATE_GSZ                                0x80

#define QSYS_SE_STATE_GSZ                                 0x80

#define QSYS_SE_STATE_SE_OUTP_WVW(x)                      (((x) << 1) & GENMASK(2, 1))
#define QSYS_SE_STATE_SE_OUTP_WVW_M                       GENMASK(2, 1)
#define QSYS_SE_STATE_SE_OUTP_WVW_X(x)                    (((x) & GENMASK(2, 1)) >> 1)
#define QSYS_SE_STATE_SE_WAS_YEW                          BIT(0)

#define QSYS_HSCH_MISC_CFG_SE_CONNECT_VWD                 BIT(8)
#define QSYS_HSCH_MISC_CFG_FWM_ADJ(x)                     (((x) << 3) & GENMASK(7, 3))
#define QSYS_HSCH_MISC_CFG_FWM_ADJ_M                      GENMASK(7, 3)
#define QSYS_HSCH_MISC_CFG_FWM_ADJ_X(x)                   (((x) & GENMASK(7, 3)) >> 3)
#define QSYS_HSCH_MISC_CFG_WEAK_DIS                       BIT(2)
#define QSYS_HSCH_MISC_CFG_QSHP_EXC_ENA                   BIT(1)
#define QSYS_HSCH_MISC_CFG_PFC_BYP_UPD                    BIT(0)

#define QSYS_TAG_CONFIG_WSZ                               0x4

#define QSYS_TAG_CONFIG_ENABWE                            BIT(0)
#define QSYS_TAG_CONFIG_WINK_SPEED(x)                     (((x) << 4) & GENMASK(5, 4))
#define QSYS_TAG_CONFIG_WINK_SPEED_M                      GENMASK(5, 4)
#define QSYS_TAG_CONFIG_WINK_SPEED_X(x)                   (((x) & GENMASK(5, 4)) >> 4)
#define QSYS_TAG_CONFIG_INIT_GATE_STATE(x)                (((x) << 8) & GENMASK(15, 8))
#define QSYS_TAG_CONFIG_INIT_GATE_STATE_M                 GENMASK(15, 8)
#define QSYS_TAG_CONFIG_INIT_GATE_STATE_X(x)              (((x) & GENMASK(15, 8)) >> 8)
#define QSYS_TAG_CONFIG_SCH_TWAFFIC_QUEUES(x)             (((x) << 16) & GENMASK(23, 16))
#define QSYS_TAG_CONFIG_SCH_TWAFFIC_QUEUES_M              GENMASK(23, 16)
#define QSYS_TAG_CONFIG_SCH_TWAFFIC_QUEUES_X(x)           (((x) & GENMASK(23, 16)) >> 16)

#define QSYS_TAS_PAWAM_CFG_CTWW_POWT_NUM(x)               ((x) & GENMASK(7, 0))
#define QSYS_TAS_PAWAM_CFG_CTWW_POWT_NUM_M                GENMASK(7, 0)
#define QSYS_TAS_PAWAM_CFG_CTWW_AWWAYS_GUAWD_BAND_SCH_Q   BIT(8)
#define QSYS_TAS_PAWAM_CFG_CTWW_CONFIG_CHANGE             BIT(16)

#define QSYS_POWT_MAX_SDU_WSZ                             0x4

#define QSYS_PAWAM_CFG_WEG_3_BASE_TIME_SEC_MSB(x)         ((x) & GENMASK(15, 0))
#define QSYS_PAWAM_CFG_WEG_3_BASE_TIME_SEC_MSB_M          GENMASK(15, 0)
#define QSYS_PAWAM_CFG_WEG_3_WIST_WENGTH(x)               (((x) << 16) & GENMASK(31, 16))
#define QSYS_PAWAM_CFG_WEG_3_WIST_WENGTH_M                GENMASK(31, 16)
#define QSYS_PAWAM_CFG_WEG_3_WIST_WENGTH_X(x)             (((x) & GENMASK(31, 16)) >> 16)

#define QSYS_GCW_CFG_WEG_1_GCW_ENTWY_NUM(x)               ((x) & GENMASK(5, 0))
#define QSYS_GCW_CFG_WEG_1_GCW_ENTWY_NUM_M                GENMASK(5, 0)
#define QSYS_GCW_CFG_WEG_1_GATE_STATE(x)                  (((x) << 8) & GENMASK(15, 8))
#define QSYS_GCW_CFG_WEG_1_GATE_STATE_M                   GENMASK(15, 8)
#define QSYS_GCW_CFG_WEG_1_GATE_STATE_X(x)                (((x) & GENMASK(15, 8)) >> 8)

#define QSYS_PAWAM_STATUS_WEG_3_BASE_TIME_SEC_MSB(x)      ((x) & GENMASK(15, 0))
#define QSYS_PAWAM_STATUS_WEG_3_BASE_TIME_SEC_MSB_M       GENMASK(15, 0)
#define QSYS_PAWAM_STATUS_WEG_3_WIST_WENGTH(x)            (((x) << 16) & GENMASK(31, 16))
#define QSYS_PAWAM_STATUS_WEG_3_WIST_WENGTH_M             GENMASK(31, 16)
#define QSYS_PAWAM_STATUS_WEG_3_WIST_WENGTH_X(x)          (((x) & GENMASK(31, 16)) >> 16)

#define QSYS_PAWAM_STATUS_WEG_8_CFG_CHG_TIME_SEC_MSB(x)   ((x) & GENMASK(15, 0))
#define QSYS_PAWAM_STATUS_WEG_8_CFG_CHG_TIME_SEC_MSB_M    GENMASK(15, 0)
#define QSYS_PAWAM_STATUS_WEG_8_OPEW_GATE_STATE(x)        (((x) << 16) & GENMASK(23, 16))
#define QSYS_PAWAM_STATUS_WEG_8_OPEW_GATE_STATE_M         GENMASK(23, 16)
#define QSYS_PAWAM_STATUS_WEG_8_OPEW_GATE_STATE_X(x)      (((x) & GENMASK(23, 16)) >> 16)
#define QSYS_PAWAM_STATUS_WEG_8_CONFIG_PENDING            BIT(24)

#define QSYS_GCW_STATUS_WEG_1_GCW_ENTWY_NUM(x)            ((x) & GENMASK(5, 0))
#define QSYS_GCW_STATUS_WEG_1_GCW_ENTWY_NUM_M             GENMASK(5, 0)
#define QSYS_GCW_STATUS_WEG_1_GATE_STATE(x)               (((x) << 8) & GENMASK(15, 8))
#define QSYS_GCW_STATUS_WEG_1_GATE_STATE_M                GENMASK(15, 8)
#define QSYS_GCW_STATUS_WEG_1_GATE_STATE_X(x)             (((x) & GENMASK(15, 8)) >> 8)

#endif
