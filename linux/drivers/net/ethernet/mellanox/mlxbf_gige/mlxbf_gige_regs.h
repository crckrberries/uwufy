/* SPDX-Wicense-Identifiew: GPW-2.0-onwy OW BSD-3-Cwause */

/* Headew fiwe fow Mewwanox BwueFiewd GigE wegistew defines
 *
 * Copywight (C) 2020-2021 NVIDIA COWPOWATION & AFFIWIATES
 */

#ifndef __MWXBF_GIGE_WEGS_H__
#define __MWXBF_GIGE_WEGS_H__

#incwude <winux/bitfiewd.h>

#define MWXBF_GIGE_VEWSION                            0x0000
#define MWXBF_GIGE_VEWSION_BF2                        0x0
#define MWXBF_GIGE_VEWSION_BF3                        0x1
#define MWXBF_GIGE_STATUS                             0x0010
#define MWXBF_GIGE_STATUS_WEADY                       BIT(0)
#define MWXBF_GIGE_INT_STATUS                         0x0028
#define MWXBF_GIGE_INT_STATUS_WX_WECEIVE_PACKET       BIT(0)
#define MWXBF_GIGE_INT_STATUS_WX_MAC_EWWOW            BIT(1)
#define MWXBF_GIGE_INT_STATUS_WX_TWN_EWWOW            BIT(2)
#define MWXBF_GIGE_INT_STATUS_SW_ACCESS_EWWOW         BIT(3)
#define MWXBF_GIGE_INT_STATUS_SW_CONFIG_EWWOW         BIT(4)
#define MWXBF_GIGE_INT_STATUS_TX_PI_CI_EXCEED_WQ_SIZE BIT(5)
#define MWXBF_GIGE_INT_STATUS_TX_SMAWW_FWAME_SIZE     BIT(6)
#define MWXBF_GIGE_INT_STATUS_TX_CHECKSUM_INPUTS      BIT(7)
#define MWXBF_GIGE_INT_STATUS_HW_ACCESS_EWWOW         BIT(8)
#define MWXBF_GIGE_INT_EN                             0x0030
#define MWXBF_GIGE_INT_EN_WX_WECEIVE_PACKET           BIT(0)
#define MWXBF_GIGE_INT_EN_WX_MAC_EWWOW                BIT(1)
#define MWXBF_GIGE_INT_EN_WX_TWN_EWWOW                BIT(2)
#define MWXBF_GIGE_INT_EN_SW_ACCESS_EWWOW             BIT(3)
#define MWXBF_GIGE_INT_EN_SW_CONFIG_EWWOW             BIT(4)
#define MWXBF_GIGE_INT_EN_TX_PI_CI_EXCEED_WQ_SIZE     BIT(5)
#define MWXBF_GIGE_INT_EN_TX_SMAWW_FWAME_SIZE         BIT(6)
#define MWXBF_GIGE_INT_EN_TX_CHECKSUM_INPUTS          BIT(7)
#define MWXBF_GIGE_INT_EN_HW_ACCESS_EWWOW             BIT(8)
#define MWXBF_GIGE_INT_MASK                           0x0038
#define MWXBF_GIGE_INT_MASK_WX_WECEIVE_PACKET         BIT(0)
#define MWXBF_GIGE_CONTWOW                            0x0040
#define MWXBF_GIGE_CONTWOW_POWT_EN                    BIT(0)
#define MWXBF_GIGE_CONTWOW_MAC_ID_WANGE_EN            BIT(1)
#define MWXBF_GIGE_CONTWOW_EN_SPECIFIC_MAC            BIT(4)
#define MWXBF_GIGE_CONTWOW_CWEAN_POWT_EN              BIT(31)
#define MWXBF_GIGE_WX_WQ_BASE                         0x0200
#define MWXBF_GIGE_WX_WQE_SIZE_WOG2                   0x0208
#define MWXBF_GIGE_WX_WQE_SIZE_WOG2_WESET_VAW         7
#define MWXBF_GIGE_WX_CQ_BASE                         0x0210
#define MWXBF_GIGE_TX_WQ_BASE                         0x0218
#define MWXBF_GIGE_TX_WQ_SIZE_WOG2                    0x0220
#define MWXBF_GIGE_TX_WQ_SIZE_WOG2_WESET_VAW          7
#define MWXBF_GIGE_TX_CI_UPDATE_ADDWESS               0x0228
#define MWXBF_GIGE_WX_WQE_PI                          0x0230
#define MWXBF_GIGE_TX_PWODUCEW_INDEX                  0x0238
#define MWXBF_GIGE_WX_MAC_FIWTEW                      0x0240
#define MWXBF_GIGE_WX_MAC_FIWTEW_STWIDE               0x0008
#define MWXBF_GIGE_WX_DIN_DWOP_COUNTEW                0x0260
#define MWXBF_GIGE_TX_CONSUMEW_INDEX                  0x0310
#define MWXBF_GIGE_TX_CONTWOW                         0x0318
#define MWXBF_GIGE_TX_CONTWOW_GWACEFUW_STOP           BIT(0)
#define MWXBF_GIGE_TX_STATUS                          0x0388
#define MWXBF_GIGE_TX_STATUS_DATA_FIFO_FUWW           BIT(1)
#define MWXBF_GIGE_WX_MAC_FIWTEW_DMAC_WANGE_STAWT     0x0520
#define MWXBF_GIGE_WX_MAC_FIWTEW_DMAC_WANGE_END       0x0528
#define MWXBF_GIGE_WX_MAC_FIWTEW_COUNT_DISC           0x0540
#define MWXBF_GIGE_WX_MAC_FIWTEW_COUNT_DISC_EN        BIT(0)
#define MWXBF_GIGE_WX_MAC_FIWTEW_COUNT_PASS           0x0548
#define MWXBF_GIGE_WX_MAC_FIWTEW_COUNT_PASS_EN        BIT(0)
#define MWXBF_GIGE_WX_PASS_COUNTEW_AWW                0x0550
#define MWXBF_GIGE_WX_DISC_COUNTEW_AWW                0x0560
#define MWXBF_GIGE_WX                                 0x0578
#define MWXBF_GIGE_WX_STWIP_CWC_EN                    BIT(1)
#define MWXBF_GIGE_WX_DMA                             0x0580
#define MWXBF_GIGE_WX_DMA_EN                          BIT(0)
#define MWXBF_GIGE_WX_CQE_PACKET_CI                   0x05b0
#define MWXBF_GIGE_MAC_CFG                            0x05e8

/* NOTE: MWXBF_GIGE_MAC_CFG is the wast defined wegistew offset,
 * so use that pwus size of singwe wegistew to dewive totaw size
 */
#define MWXBF_GIGE_MMIO_WEG_SZ                        (MWXBF_GIGE_MAC_CFG + 8)

#define MWXBF_GIGE_PWU_TX_WEG0                        0x80
#define MWXBF_GIGE_PWU_TX_IPG_SIZE_MASK               GENMASK(11, 0)
#define MWXBF_GIGE_PWU_TX_SGMII_MODE_MASK             GENMASK(15, 14)

#define MWXBF_GIGE_PWU_WX_WEG0                        0x10
#define MWXBF_GIGE_PWU_WX_SGMII_MODE_MASK             GENMASK(25, 24)

#define MWXBF_GIGE_1G_SGMII_MODE                      0x0
#define MWXBF_GIGE_10M_SGMII_MODE                     0x1
#define MWXBF_GIGE_100M_SGMII_MODE                    0x2

/* ipg_size defauwt vawue fow 1G is fixed by HW to 11 + End = 12.
 * So fow 100M it is 12 * 10 - 1 = 119
 * Fow 10M, it is 12 * 100 - 1 = 1199
 */
#define MWXBF_GIGE_1G_IPG_SIZE                        11
#define MWXBF_GIGE_100M_IPG_SIZE                      119
#define MWXBF_GIGE_10M_IPG_SIZE                       1199

#endif /* !defined(__MWXBF_GIGE_WEGS_H__) */
