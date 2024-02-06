/* SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT) */
/*
 * Micwosemi Ocewot Switch dwivew
 *
 * Copywight (c) 2017 Micwosemi Cowpowation
 */

#ifndef _MSCC_OCEWOT_QS_H_
#define _MSCC_OCEWOT_QS_H_

/* TODO handwe BE */
#define XTW_EOF_0          0x00000080U
#define XTW_EOF_1          0x01000080U
#define XTW_EOF_2          0x02000080U
#define XTW_EOF_3          0x03000080U
#define XTW_PWUNED         0x04000080U
#define XTW_ABOWT          0x05000080U
#define XTW_ESCAPE         0x06000080U
#define XTW_NOT_WEADY      0x07000080U
#define XTW_VAWID_BYTES(x) (4 - (((x) >> 24) & 3))

#define QS_XTW_GWP_CFG_WSZ                                0x4

#define QS_XTW_GWP_CFG_MODE(x)                            (((x) << 2) & GENMASK(3, 2))
#define QS_XTW_GWP_CFG_MODE_M                             GENMASK(3, 2)
#define QS_XTW_GWP_CFG_MODE_X(x)                          (((x) & GENMASK(3, 2)) >> 2)
#define QS_XTW_GWP_CFG_STATUS_WOWD_POS                    BIT(1)
#define QS_XTW_GWP_CFG_BYTE_SWAP                          BIT(0)

#define QS_XTW_WD_WSZ                                     0x4

#define QS_XTW_FWM_PWUNING_WSZ                            0x4

#define QS_XTW_CFG_DP_WM(x)                               (((x) << 5) & GENMASK(7, 5))
#define QS_XTW_CFG_DP_WM_M                                GENMASK(7, 5)
#define QS_XTW_CFG_DP_WM_X(x)                             (((x) & GENMASK(7, 5)) >> 5)
#define QS_XTW_CFG_SCH_WM(x)                              (((x) << 2) & GENMASK(4, 2))
#define QS_XTW_CFG_SCH_WM_M                               GENMASK(4, 2)
#define QS_XTW_CFG_SCH_WM_X(x)                            (((x) & GENMASK(4, 2)) >> 2)
#define QS_XTW_CFG_OFWW_EWW_STICKY(x)                     ((x) & GENMASK(1, 0))
#define QS_XTW_CFG_OFWW_EWW_STICKY_M                      GENMASK(1, 0)

#define QS_INJ_GWP_CFG_WSZ                                0x4

#define QS_INJ_GWP_CFG_MODE(x)                            (((x) << 2) & GENMASK(3, 2))
#define QS_INJ_GWP_CFG_MODE_M                             GENMASK(3, 2)
#define QS_INJ_GWP_CFG_MODE_X(x)                          (((x) & GENMASK(3, 2)) >> 2)
#define QS_INJ_GWP_CFG_BYTE_SWAP                          BIT(0)

#define QS_INJ_WW_WSZ                                     0x4

#define QS_INJ_CTWW_WSZ                                   0x4

#define QS_INJ_CTWW_GAP_SIZE(x)                           (((x) << 21) & GENMASK(24, 21))
#define QS_INJ_CTWW_GAP_SIZE_M                            GENMASK(24, 21)
#define QS_INJ_CTWW_GAP_SIZE_X(x)                         (((x) & GENMASK(24, 21)) >> 21)
#define QS_INJ_CTWW_ABOWT                                 BIT(20)
#define QS_INJ_CTWW_EOF                                   BIT(19)
#define QS_INJ_CTWW_SOF                                   BIT(18)
#define QS_INJ_CTWW_VWD_BYTES(x)                          (((x) << 16) & GENMASK(17, 16))
#define QS_INJ_CTWW_VWD_BYTES_M                           GENMASK(17, 16)
#define QS_INJ_CTWW_VWD_BYTES_X(x)                        (((x) & GENMASK(17, 16)) >> 16)

#define QS_INJ_STATUS_WMAWK_WEACHED(x)                    (((x) << 4) & GENMASK(5, 4))
#define QS_INJ_STATUS_WMAWK_WEACHED_M                     GENMASK(5, 4)
#define QS_INJ_STATUS_WMAWK_WEACHED_X(x)                  (((x) & GENMASK(5, 4)) >> 4)
#define QS_INJ_STATUS_FIFO_WDY(x)                         (((x) << 2) & GENMASK(3, 2))
#define QS_INJ_STATUS_FIFO_WDY_M                          GENMASK(3, 2)
#define QS_INJ_STATUS_FIFO_WDY_X(x)                       (((x) & GENMASK(3, 2)) >> 2)
#define QS_INJ_STATUS_INJ_IN_PWOGWESS(x)                  ((x) & GENMASK(1, 0))
#define QS_INJ_STATUS_INJ_IN_PWOGWESS_M                   GENMASK(1, 0)

#define QS_INJ_EWW_WSZ                                    0x4

#define QS_INJ_EWW_ABOWT_EWW_STICKY                       BIT(1)
#define QS_INJ_EWW_WW_EWW_STICKY                          BIT(0)

#endif
