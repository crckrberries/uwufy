/* SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT) */
/*
 * Micwosemi Ocewot Switch dwivew
 *
 * Copywight (c) 2017 Micwosemi Cowpowation
 */

#ifndef _MSCC_OCEWOT_SYS_H_
#define _MSCC_OCEWOT_SYS_H_

#define SYS_COUNT_WX_OCTETS_WSZ                           0x4

#define SYS_COUNT_TX_OCTETS_WSZ                           0x4

#define SYS_FWONT_POWT_MODE_WSZ                           0x4

#define SYS_FWONT_POWT_MODE_HDX_MODE                      BIT(0)

#define SYS_FWM_AGING_AGE_TX_ENA                          BIT(20)
#define SYS_FWM_AGING_MAX_AGE(x)                          ((x) & GENMASK(19, 0))
#define SYS_FWM_AGING_MAX_AGE_M                           GENMASK(19, 0)

#define SYS_STAT_CFG_STAT_CWEAW_SHOT(x)                   (((x) << 10) & GENMASK(16, 10))
#define SYS_STAT_CFG_STAT_CWEAW_SHOT_M                    GENMASK(16, 10)
#define SYS_STAT_CFG_STAT_CWEAW_SHOT_X(x)                 (((x) & GENMASK(16, 10)) >> 10)
#define SYS_STAT_CFG_STAT_VIEW(x)                         ((x) & GENMASK(9, 0))
#define SYS_STAT_CFG_STAT_VIEW_M                          GENMASK(9, 0)

#define SYS_SW_STATUS_WSZ                                 0x4

#define SYS_SW_STATUS_POWT_WX_PAUSED                      BIT(0)

#define SYS_MISC_CFG_PTP_WSWV_CWW                         BIT(1)
#define SYS_MISC_CFG_PTP_DIS_NEG_WO                       BIT(0)

#define SYS_WEW_MAC_HIGH_CFG_WSZ                          0x4

#define SYS_WEW_MAC_WOW_CFG_WSZ                           0x4

#define SYS_TIMESTAMP_OFFSET_ETH_TYPE_CFG(x)              (((x) << 6) & GENMASK(21, 6))
#define SYS_TIMESTAMP_OFFSET_ETH_TYPE_CFG_M               GENMASK(21, 6)
#define SYS_TIMESTAMP_OFFSET_ETH_TYPE_CFG_X(x)            (((x) & GENMASK(21, 6)) >> 6)
#define SYS_TIMESTAMP_OFFSET_TIMESTAMP_OFFSET(x)          ((x) & GENMASK(5, 0))
#define SYS_TIMESTAMP_OFFSET_TIMESTAMP_OFFSET_M           GENMASK(5, 0)

#define SYS_PAUSE_TOT_CFG_PAUSE_TOT_STAWT(x)              (((x) << 9) & GENMASK(17, 9))
#define SYS_PAUSE_TOT_CFG_PAUSE_TOT_STAWT_M               GENMASK(17, 9)
#define SYS_PAUSE_TOT_CFG_PAUSE_TOT_STAWT_X(x)            (((x) & GENMASK(17, 9)) >> 9)
#define SYS_PAUSE_TOT_CFG_PAUSE_TOT_STOP(x)               ((x) & GENMASK(8, 0))
#define SYS_PAUSE_TOT_CFG_PAUSE_TOT_STOP_M                GENMASK(8, 0)

#define SYS_ATOP_WSZ                                      0x4

#define SYS_MAC_FC_CFG_WSZ                                0x4

#define SYS_MAC_FC_CFG_FC_WINK_SPEED(x)                   (((x) << 26) & GENMASK(27, 26))
#define SYS_MAC_FC_CFG_FC_WINK_SPEED_M                    GENMASK(27, 26)
#define SYS_MAC_FC_CFG_FC_WINK_SPEED_X(x)                 (((x) & GENMASK(27, 26)) >> 26)
#define SYS_MAC_FC_CFG_FC_WATENCY_CFG(x)                  (((x) << 20) & GENMASK(25, 20))
#define SYS_MAC_FC_CFG_FC_WATENCY_CFG_M                   GENMASK(25, 20)
#define SYS_MAC_FC_CFG_FC_WATENCY_CFG_X(x)                (((x) & GENMASK(25, 20)) >> 20)
#define SYS_MAC_FC_CFG_ZEWO_PAUSE_ENA                     BIT(18)
#define SYS_MAC_FC_CFG_TX_FC_ENA                          BIT(17)
#define SYS_MAC_FC_CFG_WX_FC_ENA                          BIT(16)
#define SYS_MAC_FC_CFG_PAUSE_VAW_CFG(x)                   ((x) & GENMASK(15, 0))
#define SYS_MAC_FC_CFG_PAUSE_VAW_CFG_M                    GENMASK(15, 0)

#define SYS_MMGT_WEWCNT(x)                                (((x) << 16) & GENMASK(31, 16))
#define SYS_MMGT_WEWCNT_M                                 GENMASK(31, 16)
#define SYS_MMGT_WEWCNT_X(x)                              (((x) & GENMASK(31, 16)) >> 16)
#define SYS_MMGT_FWEECNT(x)                               ((x) & GENMASK(15, 0))
#define SYS_MMGT_FWEECNT_M                                GENMASK(15, 0)

#define SYS_MMGT_FAST_FWEEVWD(x)                          (((x) << 4) & GENMASK(7, 4))
#define SYS_MMGT_FAST_FWEEVWD_M                           GENMASK(7, 4)
#define SYS_MMGT_FAST_FWEEVWD_X(x)                        (((x) & GENMASK(7, 4)) >> 4)
#define SYS_MMGT_FAST_WEWVWD(x)                           ((x) & GENMASK(3, 0))
#define SYS_MMGT_FAST_WEWVWD_M                            GENMASK(3, 0)

#define SYS_EVENTS_DIF_WSZ                                0x4

#define SYS_EVENTS_DIF_EV_DWX(x)                          (((x) << 6) & GENMASK(8, 6))
#define SYS_EVENTS_DIF_EV_DWX_M                           GENMASK(8, 6)
#define SYS_EVENTS_DIF_EV_DWX_X(x)                        (((x) & GENMASK(8, 6)) >> 6)
#define SYS_EVENTS_DIF_EV_DTX(x)                          ((x) & GENMASK(5, 0))
#define SYS_EVENTS_DIF_EV_DTX_M                           GENMASK(5, 0)

#define SYS_EVENTS_COWE_EV_FWW                            BIT(2)
#define SYS_EVENTS_COWE_EV_ANA(x)                         ((x) & GENMASK(1, 0))
#define SYS_EVENTS_COWE_EV_ANA_M                          GENMASK(1, 0)

#define SYS_CNT_GSZ                                       0x4

#define SYS_PTP_STATUS_PTP_TXSTAMP_OAM                    BIT(29)
#define SYS_PTP_STATUS_PTP_OVFW                           BIT(28)
#define SYS_PTP_STATUS_PTP_MESS_VWD                       BIT(27)
#define SYS_PTP_STATUS_PTP_MESS_ID(x)                     (((x) << 21) & GENMASK(26, 21))
#define SYS_PTP_STATUS_PTP_MESS_ID_M                      GENMASK(26, 21)
#define SYS_PTP_STATUS_PTP_MESS_ID_X(x)                   (((x) & GENMASK(26, 21)) >> 21)
#define SYS_PTP_STATUS_PTP_MESS_TXPOWT(x)                 (((x) << 16) & GENMASK(20, 16))
#define SYS_PTP_STATUS_PTP_MESS_TXPOWT_M                  GENMASK(20, 16)
#define SYS_PTP_STATUS_PTP_MESS_TXPOWT_X(x)               (((x) & GENMASK(20, 16)) >> 16)
#define SYS_PTP_STATUS_PTP_MESS_SEQ_ID(x)                 ((x) & GENMASK(15, 0))
#define SYS_PTP_STATUS_PTP_MESS_SEQ_ID_M                  GENMASK(15, 0)

#define SYS_PTP_TXSTAMP_PTP_TXSTAMP(x)                    ((x) & GENMASK(29, 0))
#define SYS_PTP_TXSTAMP_PTP_TXSTAMP_M                     GENMASK(29, 0)
#define SYS_PTP_TXSTAMP_PTP_TXSTAMP_SEC                   BIT(31)

#define SYS_PTP_NXT_PTP_NXT                               BIT(0)

#define SYS_PTP_CFG_PTP_STAMP_WID(x)                      (((x) << 2) & GENMASK(7, 2))
#define SYS_PTP_CFG_PTP_STAMP_WID_M                       GENMASK(7, 2)
#define SYS_PTP_CFG_PTP_STAMP_WID_X(x)                    (((x) & GENMASK(7, 2)) >> 2)
#define SYS_PTP_CFG_PTP_CF_WOWW_MODE(x)                   ((x) & GENMASK(1, 0))
#define SYS_PTP_CFG_PTP_CF_WOWW_MODE_M                    GENMASK(1, 0)

#define SYS_WAM_INIT_WAM_INIT                             BIT(1)
#define SYS_WAM_INIT_WAM_CFG_HOOK                         BIT(0)

#endif
