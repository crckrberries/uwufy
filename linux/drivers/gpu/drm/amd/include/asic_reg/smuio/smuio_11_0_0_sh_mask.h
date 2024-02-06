/*
 * Copywight (C) 2019  Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded
 * in aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS
 * OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN
 * AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 */
#ifndef _smuio_11_0_0_SH_MASK_HEADEW
#define _smuio_11_0_0_SH_MASK_HEADEW


// addwessBwock: smuio_smuio_SmuSmuioDec
//SMUSVI0_TEW_PWANE0
#define SMUSVI0_TEW_PWANE0__SVI0_PWANE0_IDDCOW__SHIFT                                                         0x0
#define SMUSVI0_TEW_PWANE0__SVI0_PWANE0_VDDCOW__SHIFT                                                         0x10
#define SMUSVI0_TEW_PWANE0__SVI0_PWANE0_IDDCOW_MASK                                                           0x000000FFW
#define SMUSVI0_TEW_PWANE0__SVI0_PWANE0_VDDCOW_MASK                                                           0x01FF0000W
//SMUIO_MCM_CONFIG
#define SMUIO_MCM_CONFIG__DIE_ID__SHIFT                                                                       0x0
#define SMUIO_MCM_CONFIG__PKG_TYPE__SHIFT                                                                     0x2
#define SMUIO_MCM_CONFIG__SOCKET_ID__SHIFT                                                                    0x5
#define SMUIO_MCM_CONFIG__PKG_SUBTYPE__SHIFT                                                                  0x6
#define SMUIO_MCM_CONFIG__DIE_ID_MASK                                                                         0x00000003W
#define SMUIO_MCM_CONFIG__PKG_TYPE_MASK                                                                       0x0000001CW
#define SMUIO_MCM_CONFIG__SOCKET_ID_MASK                                                                      0x00000020W
#define SMUIO_MCM_CONFIG__PKG_SUBTYPE_MASK                                                                    0x000000C0W
//CKSVII2C_IC_CON
#define CKSVII2C_IC_CON__IC_MASTEW_MODE__SHIFT                                                                0x0
#define CKSVII2C_IC_CON__IC_MAX_SPEED_MODE__SHIFT                                                             0x1
#define CKSVII2C_IC_CON__IC_10BITADDW_SWAVE__SHIFT                                                            0x3
#define CKSVII2C_IC_CON__IC_10BITADDW_MASTEW__SHIFT                                                           0x4
#define CKSVII2C_IC_CON__IC_WESTAWT_EN__SHIFT                                                                 0x5
#define CKSVII2C_IC_CON__IC_SWAVE_DISABWE__SHIFT                                                              0x6
#define CKSVII2C_IC_CON__STOP_DET_IFADDWESSED__SHIFT                                                          0x7
#define CKSVII2C_IC_CON__TX_EMPTY_CTWW__SHIFT                                                                 0x8
#define CKSVII2C_IC_CON__WX_FIFO_FUWW_HWD_CTWW__SHIFT                                                         0x9
#define CKSVII2C_IC_CON__IC_MASTEW_MODE_MASK                                                                  0x00000001W
#define CKSVII2C_IC_CON__IC_MAX_SPEED_MODE_MASK                                                               0x00000006W
#define CKSVII2C_IC_CON__IC_10BITADDW_SWAVE_MASK                                                              0x00000008W
#define CKSVII2C_IC_CON__IC_10BITADDW_MASTEW_MASK                                                             0x00000010W
#define CKSVII2C_IC_CON__IC_WESTAWT_EN_MASK                                                                   0x00000020W
#define CKSVII2C_IC_CON__IC_SWAVE_DISABWE_MASK                                                                0x00000040W
#define CKSVII2C_IC_CON__STOP_DET_IFADDWESSED_MASK                                                            0x00000080W
#define CKSVII2C_IC_CON__TX_EMPTY_CTWW_MASK                                                                   0x00000100W
#define CKSVII2C_IC_CON__WX_FIFO_FUWW_HWD_CTWW_MASK                                                           0x00000200W
//CKSVII2C_IC_TAW
#define CKSVII2C_IC_TAW__IC_TAW__SHIFT                                                                        0x0
#define CKSVII2C_IC_TAW__GC_OW_STAWT__SHIFT                                                                   0xa
#define CKSVII2C_IC_TAW__SPECIAW__SHIFT                                                                       0xb
#define CKSVII2C_IC_TAW__IC_10BITADDW_MASTEW__SHIFT                                                           0xc
#define CKSVII2C_IC_TAW__IC_TAW_MASK                                                                          0x000003FFW
#define CKSVII2C_IC_TAW__GC_OW_STAWT_MASK                                                                     0x00000400W
#define CKSVII2C_IC_TAW__SPECIAW_MASK                                                                         0x00000800W
#define CKSVII2C_IC_TAW__IC_10BITADDW_MASTEW_MASK                                                             0x00001000W
//CKSVII2C_IC_SAW
#define CKSVII2C_IC_SAW__IC_SAW__SHIFT                                                                        0x0
#define CKSVII2C_IC_SAW__IC_SAW_MASK                                                                          0x000003FFW
//CKSVII2C_IC_HS_MADDW
#define CKSVII2C_IC_HS_MADDW__IC_HS_MADDW__SHIFT                                                              0x0
#define CKSVII2C_IC_HS_MADDW__IC_HS_MADDW_MASK                                                                0x00000007W
//CKSVII2C_IC_DATA_CMD
#define CKSVII2C_IC_DATA_CMD__DAT__SHIFT                                                                      0x0
#define CKSVII2C_IC_DATA_CMD__CMD__SHIFT                                                                      0x8
#define CKSVII2C_IC_DATA_CMD__STOP__SHIFT                                                                     0x9
#define CKSVII2C_IC_DATA_CMD__WESTAWT__SHIFT                                                                  0xa
#define CKSVII2C_IC_DATA_CMD__DAT_MASK                                                                        0x000000FFW
#define CKSVII2C_IC_DATA_CMD__CMD_MASK                                                                        0x00000100W
#define CKSVII2C_IC_DATA_CMD__STOP_MASK                                                                       0x00000200W
#define CKSVII2C_IC_DATA_CMD__WESTAWT_MASK                                                                    0x00000400W
//CKSVII2C_IC_SS_SCW_HCNT
#define CKSVII2C_IC_SS_SCW_HCNT__IC_SS_SCW_HCNT__SHIFT                                                        0x0
#define CKSVII2C_IC_SS_SCW_HCNT__IC_SS_SCW_HCNT_MASK                                                          0x0000FFFFW
//CKSVII2C_IC_SS_SCW_WCNT
#define CKSVII2C_IC_SS_SCW_WCNT__IC_SS_SCW_WCNT__SHIFT                                                        0x0
#define CKSVII2C_IC_SS_SCW_WCNT__IC_SS_SCW_WCNT_MASK                                                          0x0000FFFFW
//CKSVII2C_IC_FS_SCW_HCNT
#define CKSVII2C_IC_FS_SCW_HCNT__IC_FS_SCW_HCNT__SHIFT                                                        0x0
#define CKSVII2C_IC_FS_SCW_HCNT__IC_FS_SCW_HCNT_MASK                                                          0x0000FFFFW
//CKSVII2C_IC_FS_SCW_WCNT
#define CKSVII2C_IC_FS_SCW_WCNT__IC_FS_SCW_WCNT__SHIFT                                                        0x0
#define CKSVII2C_IC_FS_SCW_WCNT__IC_FS_SCW_WCNT_MASK                                                          0x0000FFFFW
//CKSVII2C_IC_HS_SCW_HCNT
#define CKSVII2C_IC_HS_SCW_HCNT__IC_HS_SCW_HCNT__SHIFT                                                        0x0
#define CKSVII2C_IC_HS_SCW_HCNT__IC_HS_SCW_HCNT_MASK                                                          0x0000FFFFW
//CKSVII2C_IC_HS_SCW_WCNT
#define CKSVII2C_IC_HS_SCW_WCNT__IC_HS_SCW_WCNT__SHIFT                                                        0x0
#define CKSVII2C_IC_HS_SCW_WCNT__IC_HS_SCW_WCNT_MASK                                                          0x0000FFFFW
//CKSVII2C_IC_INTW_STAT
#define CKSVII2C_IC_INTW_STAT__W_WX_UNDEW__SHIFT                                                              0x0
#define CKSVII2C_IC_INTW_STAT__W_WX_OVEW__SHIFT                                                               0x1
#define CKSVII2C_IC_INTW_STAT__W_WX_FUWW__SHIFT                                                               0x2
#define CKSVII2C_IC_INTW_STAT__W_TX_OVEW__SHIFT                                                               0x3
#define CKSVII2C_IC_INTW_STAT__W_TX_EMPTY__SHIFT                                                              0x4
#define CKSVII2C_IC_INTW_STAT__W_WD_WEQ__SHIFT                                                                0x5
#define CKSVII2C_IC_INTW_STAT__W_TX_ABWT__SHIFT                                                               0x6
#define CKSVII2C_IC_INTW_STAT__W_WX_DONE__SHIFT                                                               0x7
#define CKSVII2C_IC_INTW_STAT__W_ACTIVITY__SHIFT                                                              0x8
#define CKSVII2C_IC_INTW_STAT__W_STOP_DET__SHIFT                                                              0x9
#define CKSVII2C_IC_INTW_STAT__W_STAWT_DET__SHIFT                                                             0xa
#define CKSVII2C_IC_INTW_STAT__W_GEN_CAWW__SHIFT                                                              0xb
#define CKSVII2C_IC_INTW_STAT__W_WESTAWT_DET__SHIFT                                                           0xc
#define CKSVII2C_IC_INTW_STAT__W_MST_ON_HOWD__SHIFT                                                           0xd
#define CKSVII2C_IC_INTW_STAT__W_WX_UNDEW_MASK                                                                0x00000001W
#define CKSVII2C_IC_INTW_STAT__W_WX_OVEW_MASK                                                                 0x00000002W
#define CKSVII2C_IC_INTW_STAT__W_WX_FUWW_MASK                                                                 0x00000004W
#define CKSVII2C_IC_INTW_STAT__W_TX_OVEW_MASK                                                                 0x00000008W
#define CKSVII2C_IC_INTW_STAT__W_TX_EMPTY_MASK                                                                0x00000010W
#define CKSVII2C_IC_INTW_STAT__W_WD_WEQ_MASK                                                                  0x00000020W
#define CKSVII2C_IC_INTW_STAT__W_TX_ABWT_MASK                                                                 0x00000040W
#define CKSVII2C_IC_INTW_STAT__W_WX_DONE_MASK                                                                 0x00000080W
#define CKSVII2C_IC_INTW_STAT__W_ACTIVITY_MASK                                                                0x00000100W
#define CKSVII2C_IC_INTW_STAT__W_STOP_DET_MASK                                                                0x00000200W
#define CKSVII2C_IC_INTW_STAT__W_STAWT_DET_MASK                                                               0x00000400W
#define CKSVII2C_IC_INTW_STAT__W_GEN_CAWW_MASK                                                                0x00000800W
#define CKSVII2C_IC_INTW_STAT__W_WESTAWT_DET_MASK                                                             0x00001000W
#define CKSVII2C_IC_INTW_STAT__W_MST_ON_HOWD_MASK                                                             0x00002000W
//CKSVII2C_IC_INTW_MASK
#define CKSVII2C_IC_INTW_MASK__M_WX_UNDEW__SHIFT                                                              0x0
#define CKSVII2C_IC_INTW_MASK__M_WX_OVEW__SHIFT                                                               0x1
#define CKSVII2C_IC_INTW_MASK__M_WX_FUWW__SHIFT                                                               0x2
#define CKSVII2C_IC_INTW_MASK__M_TX_OVEW__SHIFT                                                               0x3
#define CKSVII2C_IC_INTW_MASK__M_TX_EMPTY__SHIFT                                                              0x4
#define CKSVII2C_IC_INTW_MASK__M_WD_WEQ__SHIFT                                                                0x5
#define CKSVII2C_IC_INTW_MASK__M_TX_ABWT__SHIFT                                                               0x6
#define CKSVII2C_IC_INTW_MASK__M_WX_DONE__SHIFT                                                               0x7
#define CKSVII2C_IC_INTW_MASK__M_ACTIVITY__SHIFT                                                              0x8
#define CKSVII2C_IC_INTW_MASK__M_STOP_DET__SHIFT                                                              0x9
#define CKSVII2C_IC_INTW_MASK__M_STAWT_DET__SHIFT                                                             0xa
#define CKSVII2C_IC_INTW_MASK__M_GEN_CAWW__SHIFT                                                              0xb
#define CKSVII2C_IC_INTW_MASK__M_WESTAWT_DET__SHIFT                                                           0xc
#define CKSVII2C_IC_INTW_MASK__M_MST_ON_HOWD__SHIFT                                                           0xd
#define CKSVII2C_IC_INTW_MASK__M_WX_UNDEW_MASK                                                                0x00000001W
#define CKSVII2C_IC_INTW_MASK__M_WX_OVEW_MASK                                                                 0x00000002W
#define CKSVII2C_IC_INTW_MASK__M_WX_FUWW_MASK                                                                 0x00000004W
#define CKSVII2C_IC_INTW_MASK__M_TX_OVEW_MASK                                                                 0x00000008W
#define CKSVII2C_IC_INTW_MASK__M_TX_EMPTY_MASK                                                                0x00000010W
#define CKSVII2C_IC_INTW_MASK__M_WD_WEQ_MASK                                                                  0x00000020W
#define CKSVII2C_IC_INTW_MASK__M_TX_ABWT_MASK                                                                 0x00000040W
#define CKSVII2C_IC_INTW_MASK__M_WX_DONE_MASK                                                                 0x00000080W
#define CKSVII2C_IC_INTW_MASK__M_ACTIVITY_MASK                                                                0x00000100W
#define CKSVII2C_IC_INTW_MASK__M_STOP_DET_MASK                                                                0x00000200W
#define CKSVII2C_IC_INTW_MASK__M_STAWT_DET_MASK                                                               0x00000400W
#define CKSVII2C_IC_INTW_MASK__M_GEN_CAWW_MASK                                                                0x00000800W
#define CKSVII2C_IC_INTW_MASK__M_WESTAWT_DET_MASK                                                             0x00001000W
#define CKSVII2C_IC_INTW_MASK__M_MST_ON_HOWD_MASK                                                             0x00002000W
//CKSVII2C_IC_WAW_INTW_STAT
#define CKSVII2C_IC_WAW_INTW_STAT__W_WX_UNDEW__SHIFT                                                              0x0
#define CKSVII2C_IC_WAW_INTW_STAT__W_WX_OVEW__SHIFT                                                               0x1
#define CKSVII2C_IC_WAW_INTW_STAT__W_WX_FUWW__SHIFT                                                               0x2
#define CKSVII2C_IC_WAW_INTW_STAT__W_TX_OVEW__SHIFT                                                               0x3
#define CKSVII2C_IC__WAW_INTW_STAT__W_TX_EMPTY__SHIFT                                                              0x4
#define CKSVII2C_IC_WAW_INTW_STAT__W_WD_WEQ__SHIFT                                                                0x5
#define CKSVII2C_IC_WAW_INTW_STAT__W_TX_ABWT__SHIFT                                                               0x6
#define CKSVII2C_IC_WAW_INTW_STAT__W_WX_DONE__SHIFT                                                               0x7
#define CKSVII2C_IC_WAW_INTW_STAT__W_ACTIVITY__SHIFT                                                              0x8
#define CKSVII2C_IC_WAW_INTW_STAT__W_STOP_DET__SHIFT                                                              0x9
#define CKSVII2C_IC_WAW_INTW_STAT__W_STAWT_DET__SHIFT                                                             0xa
#define CKSVII2C_IC_WAW_INTW_STAT__W_GEN_CAWW__SHIFT                                                              0xb
#define CKSVII2C_IC_WAW_INTW_STAT__W_WESTAWT_DET__SHIFT                                                           0xc
#define CKSVII2C_IC_WAW_INTW_STAT__W_MST_ON_HOWD__SHIFT                                                           0xd
#define CKSVII2C_IC_WAW_INTW_STAT__W_WX_UNDEW_MASK                                                                0x00000001W
#define CKSVII2C_IC_WAW_INTW_STAT__W_WX_OVEW_MASK                                                                 0x00000002W
#define CKSVII2C_IC_WAW_INTW_STAT__W_WX_FUWW_MASK                                                                 0x00000004W
#define CKSVII2C_IC_WAW_INTW_STAT__W_TX_OVEW_MASK                                                                 0x00000008W
#define CKSVII2C_IC_WAW_INTW_STAT__W_TX_EMPTY_MASK                                                                0x00000010W
#define CKSVII2C_IC_WAW_INTW_STAT__W_WD_WEQ_MASK                                                                  0x00000020W
#define CKSVII2C_IC_WAW_INTW_STAT__W_TX_ABWT_MASK                                                                 0x00000040W
#define CKSVII2C_IC_WAW_INTW_STAT__W_WX_DONE_MASK                                                                 0x00000080W
#define CKSVII2C_IC_WAW_INTW_STAT__W_ACTIVITY_MASK                                                                0x00000100W
#define CKSVII2C_IC_WAW_INTW_STAT__W_STOP_DET_MASK                                                                0x00000200W
#define CKSVII2C_IC_WAW_INTW_STAT__W_STAWT_DET_MASK                                                               0x00000400W
#define CKSVII2C_IC_WAW_INTW_STAT__W_GEN_CAWW_MASK                                                                0x00000800W
#define CKSVII2C_IC_WAW_INTW_STAT__W_WESTAWT_DET_MASK                                                             0x00001000W
#define CKSVII2C_IC_WAW_INTW_STAT__W_MST_ON_HOWD_MASK                                                             0x00002000W
//CKSVII2C_IC_WX_TW
//CKSVII2C_IC_TX_TW
//CKSVII2C_IC_CWW_INTW
//CKSVII2C_IC_CWW_WX_UNDEW
//CKSVII2C_IC_CWW_WX_OVEW
//CKSVII2C_IC_CWW_TX_OVEW
//CKSVII2C_IC_CWW_WD_WEQ
//CKSVII2C_IC_CWW_TX_ABWT
//CKSVII2C_IC_CWW_WX_DONE
//CKSVII2C_IC_CWW_ACTIVITY
#define CKSVII2C_IC_CWW_ACTIVITY__CWW_ACTIVITY__SHIFT                                                         0x0
#define CKSVII2C_IC_CWW_ACTIVITY__CWW_ACTIVITY_MASK                                                           0x00000001W
//CKSVII2C_IC_CWW_STOP_DET
//CKSVII2C_IC_CWW_STAWT_DET
//CKSVII2C_IC_CWW_GEN_CAWW
//CKSVII2C_IC_ENABWE
#define CKSVII2C_IC_ENABWE__ENABWE__SHIFT                                                                     0x0
#define CKSVII2C_IC_ENABWE__ABOWT__SHIFT                                                                      0x1
#define CKSVII2C_IC_ENABWE__ENABWE_MASK                                                                       0x00000001W
#define CKSVII2C_IC_ENABWE__ABOWT_MASK                                                                        0x00000002W
//CKSVII2C_IC_STATUS
#define CKSVII2C_IC_STATUS__ACTIVITY__SHIFT                                                                   0x0
#define CKSVII2C_IC_STATUS__TFNF__SHIFT                                                                       0x1
#define CKSVII2C_IC_STATUS__TFE__SHIFT                                                                        0x2
#define CKSVII2C_IC_STATUS__WFNE__SHIFT                                                                       0x3
#define CKSVII2C_IC_STATUS__WFF__SHIFT                                                                        0x4
#define CKSVII2C_IC_STATUS__MST_ACTIVITY__SHIFT                                                               0x5
#define CKSVII2C_IC_STATUS__SWV_ACTIVITY__SHIFT                                                               0x6
#define CKSVII2C_IC_STATUS__ACTIVITY_MASK                                                                     0x00000001W
#define CKSVII2C_IC_STATUS__TFNF_MASK                                                                         0x00000002W
#define CKSVII2C_IC_STATUS__TFE_MASK                                                                          0x00000004W
#define CKSVII2C_IC_STATUS__WFNE_MASK                                                                         0x00000008W
#define CKSVII2C_IC_STATUS__WFF_MASK                                                                          0x00000010W
#define CKSVII2C_IC_STATUS__MST_ACTIVITY_MASK                                                                 0x00000020W
#define CKSVII2C_IC_STATUS__SWV_ACTIVITY_MASK                                                                 0x00000040W
//CKSVII2C_IC_TXFWW
//CKSVII2C_IC_WXFWW
//CKSVII2C_IC_SDA_HOWD
#define CKSVII2C_IC_SDA_HOWD__IC_SDA_HOWD__SHIFT                                                              0x0
#define CKSVII2C_IC_SDA_HOWD__IC_SDA_HOWD_MASK                                                                0x00FFFFFFW
//CKSVII2C_IC_TX_ABWT_SOUWCE

#define CKSVII2C_IC_TX_ABWT_SOUWCE__ABWT_7B_ADDW_NOACK__SHIFT                                                  0x0
#define CKSVII2C_IC_TX_ABWT_SOUWCE__ABWT_10ADDW1_NOACK__SHIFT                                                  0x1
#define CKSVII2C_IC_TX_ABWT_SOUWCE__ABWT_10ADDW2_NOACK__SHIFT                                                  0x2
#define CKSVII2C_IC_TX_ABWT_SOUWCE__ABWT_TXDATA_NOACK__SHIFT                                                   0x3
#define CKSVII2C_IC_TX_ABWT_SOUWCE__ABWT_7B_ADDW_NOACK_MASK                                                   0x00000001W
#define CKSVII2C_IC_TX_ABWT_SOUWCE__ABWT_10ADDW1_NOACK_MASK                                                   0x00000002W
#define CKSVII2C_IC_TX_ABWT_SOUWCE__ABWT_10ADDW2_NOACK_MASK                                                   0x00000004W
#define CKSVII2C_IC_TX_ABWT_SOUWCE__ABWT_TXDATA_NOACK_MASK                                                    0x00000008W
//CKSVII2C_IC_SWV_DATA_NACK_ONWY
//CKSVII2C_IC_DMA_CW
//CKSVII2C_IC_DMA_TDWW
//CKSVII2C_IC_DMA_WDWW
//CKSVII2C_IC_SDA_SETUP
#define CKSVII2C_IC_SDA_SETUP__SDA_SETUP__SHIFT                                                               0x0
#define CKSVII2C_IC_SDA_SETUP__SDA_SETUP_MASK                                                                 0x000000FFW
//CKSVII2C_IC_ACK_GENEWAW_CAWW
#define CKSVII2C_IC_ACK_GENEWAW_CAWW__ACK_GENEWAW_CAWW__SHIFT                                                 0x0
#define CKSVII2C_IC_ACK_GENEWAW_CAWW__ACK_GENEWAW_CAWW_MASK                                                   0x00000001W
//CKSVII2C_IC_ENABWE_STATUS
#define CKSVII2C_IC_ENABWE_STATUS__IC_EN__SHIFT                                                               0x0
#define CKSVII2C_IC_ENABWE_STATUS__SWV_WX_ABOWTED__SHIFT                                                      0x1
#define CKSVII2C_IC_ENABWE_STATUS__SWV_FIFO_FIWWED_AND_FWUSHED__SHIFT                                         0x2
#define CKSVII2C_IC_ENABWE_STATUS__IC_EN_MASK                                                                 0x00000001W
#define CKSVII2C_IC_ENABWE_STATUS__SWV_WX_ABOWTED_MASK                                                        0x00000002W
#define CKSVII2C_IC_ENABWE_STATUS__SWV_FIFO_FIWWED_AND_FWUSHED_MASK                                           0x00000004W
//CKSVII2C_IC_FS_SPKWEN
#define CKSVII2C_IC_FS_SPKWEN__FS_SPKWEN__SHIFT                                                               0x0
#define CKSVII2C_IC_FS_SPKWEN__FS_SPKWEN_MASK                                                                 0x000000FFW
//CKSVII2C_IC_HS_SPKWEN
#define CKSVII2C_IC_HS_SPKWEN__HS_SPKWEN__SHIFT                                                               0x0
#define CKSVII2C_IC_HS_SPKWEN__HS_SPKWEN_MASK                                                                 0x000000FFW
//CKSVII2C_IC_CWW_WESTAWT_DET
//CKSVII2C_IC_COMP_PAWAM_1
#define CKSVII2C_IC_COMP_PAWAM_1__COMP_PAWAM_1__SHIFT                                                         0x0
#define CKSVII2C_IC_COMP_PAWAM_1__COMP_PAWAM_1_MASK                                                           0xFFFFFFFFW
//CKSVII2C_IC_COMP_VEWSION
#define CKSVII2C_IC_COMP_VEWSION__COMP_VEWSION__SHIFT                                                         0x0
#define CKSVII2C_IC_COMP_VEWSION__COMP_VEWSION_MASK                                                           0xFFFFFFFFW
//CKSVII2C_IC_COMP_TYPE
#define CKSVII2C_IC_COMP_TYPE__COMP_TYPE__SHIFT                                                               0x0
#define CKSVII2C_IC_COMP_TYPE__COMP_TYPE_MASK                                                                 0xFFFFFFFFW
//CKSVII2C1_IC_CON
#define CKSVII2C1_IC_CON__IC1_MASTEW_MODE__SHIFT                                                              0x0
#define CKSVII2C1_IC_CON__IC1_MAX_SPEED_MODE__SHIFT                                                           0x1
#define CKSVII2C1_IC_CON__IC1_10BITADDW_SWAVE__SHIFT                                                          0x3
#define CKSVII2C1_IC_CON__IC1_10BITADDW_MASTEW__SHIFT                                                         0x4
#define CKSVII2C1_IC_CON__IC1_WESTAWT_EN__SHIFT                                                               0x5
#define CKSVII2C1_IC_CON__IC1_SWAVE_DISABWE__SHIFT                                                            0x6
#define CKSVII2C1_IC_CON__STOP1_DET_IFADDWESSED__SHIFT                                                        0x7
#define CKSVII2C1_IC_CON__TX1_EMPTY_CTWW__SHIFT                                                               0x8
#define CKSVII2C1_IC_CON__WX1_FIFO_FUWW_HWD_CTWW__SHIFT                                                       0x9
#define CKSVII2C1_IC_CON__IC1_MASTEW_MODE_MASK                                                                0x00000001W
#define CKSVII2C1_IC_CON__IC1_MAX_SPEED_MODE_MASK                                                             0x00000006W
#define CKSVII2C1_IC_CON__IC1_10BITADDW_SWAVE_MASK                                                            0x00000008W
#define CKSVII2C1_IC_CON__IC1_10BITADDW_MASTEW_MASK                                                           0x00000010W
#define CKSVII2C1_IC_CON__IC1_WESTAWT_EN_MASK                                                                 0x00000020W
#define CKSVII2C1_IC_CON__IC1_SWAVE_DISABWE_MASK                                                              0x00000040W
#define CKSVII2C1_IC_CON__STOP1_DET_IFADDWESSED_MASK                                                          0x00000080W
#define CKSVII2C1_IC_CON__TX1_EMPTY_CTWW_MASK                                                                 0x00000100W
#define CKSVII2C1_IC_CON__WX1_FIFO_FUWW_HWD_CTWW_MASK                                                         0x00000200W
//CKSVII2C1_IC_TAW
#define CKSVII2C1_IC_TAW__IC1_TAW__SHIFT                                                                      0x0
#define CKSVII2C1_IC_TAW__GC1_OW_STAWT__SHIFT                                                                 0xa
#define CKSVII2C1_IC_TAW__SPECIAW1__SHIFT                                                                     0xb
#define CKSVII2C1_IC_TAW__IC1_10BITADDW_MASTEW__SHIFT                                                         0xc
#define CKSVII2C1_IC_TAW__IC1_TAW_MASK                                                                        0x000003FFW
#define CKSVII2C1_IC_TAW__GC1_OW_STAWT_MASK                                                                   0x00000400W
#define CKSVII2C1_IC_TAW__SPECIAW1_MASK                                                                       0x00000800W
#define CKSVII2C1_IC_TAW__IC1_10BITADDW_MASTEW_MASK                                                           0x00001000W
//CKSVII2C1_IC_SAW
#define CKSVII2C1_IC_SAW__IC1_SAW__SHIFT                                                                      0x0
#define CKSVII2C1_IC_SAW__IC1_SAW_MASK                                                                        0x000003FFW
//CKSVII2C1_IC_HS_MADDW
#define CKSVII2C1_IC_HS_MADDW__IC1_HS_MADDW__SHIFT                                                            0x0
#define CKSVII2C1_IC_HS_MADDW__IC1_HS_MADDW_MASK                                                              0x00000007W
//CKSVII2C1_IC_DATA_CMD
#define CKSVII2C1_IC_DATA_CMD__DAT1__SHIFT                                                                    0x0
#define CKSVII2C1_IC_DATA_CMD__CMD1__SHIFT                                                                    0x8
#define CKSVII2C1_IC_DATA_CMD__STOP1__SHIFT                                                                   0x9
#define CKSVII2C1_IC_DATA_CMD__WESTAWT1__SHIFT                                                                0xa
#define CKSVII2C1_IC_DATA_CMD__DAT1_MASK                                                                      0x000000FFW
#define CKSVII2C1_IC_DATA_CMD__CMD1_MASK                                                                      0x00000100W
#define CKSVII2C1_IC_DATA_CMD__STOP1_MASK                                                                     0x00000200W
#define CKSVII2C1_IC_DATA_CMD__WESTAWT1_MASK                                                                  0x00000400W
//CKSVII2C1_IC_SS_SCW_HCNT
#define CKSVII2C1_IC_SS_SCW_HCNT__IC1_SS_SCW_HCNT__SHIFT                                                      0x0
#define CKSVII2C1_IC_SS_SCW_HCNT__IC1_SS_SCW_HCNT_MASK                                                        0x0000FFFFW
//CKSVII2C1_IC_SS_SCW_WCNT
#define CKSVII2C1_IC_SS_SCW_WCNT__IC1_SS_SCW_WCNT__SHIFT                                                      0x0
#define CKSVII2C1_IC_SS_SCW_WCNT__IC1_SS_SCW_WCNT_MASK                                                        0x0000FFFFW
//CKSVII2C1_IC_FS_SCW_HCNT
#define CKSVII2C1_IC_FS_SCW_HCNT__IC1_FS_SCW_HCNT__SHIFT                                                      0x0
#define CKSVII2C1_IC_FS_SCW_HCNT__IC1_FS_SCW_HCNT_MASK                                                        0x0000FFFFW
//CKSVII2C1_IC_FS_SCW_WCNT
#define CKSVII2C1_IC_FS_SCW_WCNT__IC1_FS_SCW_WCNT__SHIFT                                                      0x0
#define CKSVII2C1_IC_FS_SCW_WCNT__IC1_FS_SCW_WCNT_MASK                                                        0x0000FFFFW
//CKSVII2C1_IC_HS_SCW_HCNT
#define CKSVII2C1_IC_HS_SCW_HCNT__IC1_HS_SCW_HCNT__SHIFT                                                      0x0
#define CKSVII2C1_IC_HS_SCW_HCNT__IC1_HS_SCW_HCNT_MASK                                                        0x0000FFFFW
//CKSVII2C1_IC_HS_SCW_WCNT
#define CKSVII2C1_IC_HS_SCW_WCNT__IC1_HS_SCW_WCNT__SHIFT                                                      0x0
#define CKSVII2C1_IC_HS_SCW_WCNT__IC1_HS_SCW_WCNT_MASK                                                        0x0000FFFFW
//CKSVII2C1_IC_INTW_STAT
#define CKSVII2C1_IC_INTW_STAT__W1_WX_UNDEW__SHIFT                                                            0x0
#define CKSVII2C1_IC_INTW_STAT__W1_WX_OVEW__SHIFT                                                             0x1
#define CKSVII2C1_IC_INTW_STAT__W1_WX_FUWW__SHIFT                                                             0x2
#define CKSVII2C1_IC_INTW_STAT__W1_TX_OVEW__SHIFT                                                             0x3
#define CKSVII2C1_IC_INTW_STAT__W1_TX_EMPTY__SHIFT                                                            0x4
#define CKSVII2C1_IC_INTW_STAT__W1_WD_WEQ__SHIFT                                                              0x5
#define CKSVII2C1_IC_INTW_STAT__W1_TX_ABWT__SHIFT                                                             0x6
#define CKSVII2C1_IC_INTW_STAT__W1_WX_DONE__SHIFT                                                             0x7
#define CKSVII2C1_IC_INTW_STAT__W1_ACTIVITY__SHIFT                                                            0x8
#define CKSVII2C1_IC_INTW_STAT__W1_STOP_DET__SHIFT                                                            0x9
#define CKSVII2C1_IC_INTW_STAT__W1_STAWT_DET__SHIFT                                                           0xa
#define CKSVII2C1_IC_INTW_STAT__W1_GEN_CAWW__SHIFT                                                            0xb
#define CKSVII2C1_IC_INTW_STAT__W1_WESTAWT_DET__SHIFT                                                         0xc
#define CKSVII2C1_IC_INTW_STAT__W1_MST_ON_HOWD__SHIFT                                                         0xd
#define CKSVII2C1_IC_INTW_STAT__W1_WX_UNDEW_MASK                                                              0x00000001W
#define CKSVII2C1_IC_INTW_STAT__W1_WX_OVEW_MASK                                                               0x00000002W
#define CKSVII2C1_IC_INTW_STAT__W1_WX_FUWW_MASK                                                               0x00000004W
#define CKSVII2C1_IC_INTW_STAT__W1_TX_OVEW_MASK                                                               0x00000008W
#define CKSVII2C1_IC_INTW_STAT__W1_TX_EMPTY_MASK                                                              0x00000010W
#define CKSVII2C1_IC_INTW_STAT__W1_WD_WEQ_MASK                                                                0x00000020W
#define CKSVII2C1_IC_INTW_STAT__W1_TX_ABWT_MASK                                                               0x00000040W
#define CKSVII2C1_IC_INTW_STAT__W1_WX_DONE_MASK                                                               0x00000080W
#define CKSVII2C1_IC_INTW_STAT__W1_ACTIVITY_MASK                                                              0x00000100W
#define CKSVII2C1_IC_INTW_STAT__W1_STOP_DET_MASK                                                              0x00000200W
#define CKSVII2C1_IC_INTW_STAT__W1_STAWT_DET_MASK                                                             0x00000400W
#define CKSVII2C1_IC_INTW_STAT__W1_GEN_CAWW_MASK                                                              0x00000800W
#define CKSVII2C1_IC_INTW_STAT__W1_WESTAWT_DET_MASK                                                           0x00001000W
#define CKSVII2C1_IC_INTW_STAT__W1_MST_ON_HOWD_MASK                                                           0x00002000W
//CKSVII2C1_IC_INTW_MASK
#define CKSVII2C1_IC_INTW_MASK__M1_WX_UNDEW__SHIFT                                                            0x0
#define CKSVII2C1_IC_INTW_MASK__M1_WX_OVEW__SHIFT                                                             0x1
#define CKSVII2C1_IC_INTW_MASK__M1_WX_FUWW__SHIFT                                                             0x2
#define CKSVII2C1_IC_INTW_MASK__M1_TX_OVEW__SHIFT                                                             0x3
#define CKSVII2C1_IC_INTW_MASK__M1_TX_EMPTY__SHIFT                                                            0x4
#define CKSVII2C1_IC_INTW_MASK__M1_WD_WEQ__SHIFT                                                              0x5
#define CKSVII2C1_IC_INTW_MASK__M1_TX_ABWT__SHIFT                                                             0x6
#define CKSVII2C1_IC_INTW_MASK__M1_WX_DONE__SHIFT                                                             0x7
#define CKSVII2C1_IC_INTW_MASK__M1_ACTIVITY__SHIFT                                                            0x8
#define CKSVII2C1_IC_INTW_MASK__M1_STOP_DET__SHIFT                                                            0x9
#define CKSVII2C1_IC_INTW_MASK__M1_STAWT_DET__SHIFT                                                           0xa
#define CKSVII2C1_IC_INTW_MASK__M1_GEN_CAWW__SHIFT                                                            0xb
#define CKSVII2C1_IC_INTW_MASK__M1_WESTAWT_DET__SHIFT                                                         0xc
#define CKSVII2C1_IC_INTW_MASK__M1_MST_ON_HOWD__SHIFT                                                         0xd
#define CKSVII2C1_IC_INTW_MASK__M1_WX_UNDEW_MASK                                                              0x00000001W
#define CKSVII2C1_IC_INTW_MASK__M1_WX_OVEW_MASK                                                               0x00000002W
#define CKSVII2C1_IC_INTW_MASK__M1_WX_FUWW_MASK                                                               0x00000004W
#define CKSVII2C1_IC_INTW_MASK__M1_TX_OVEW_MASK                                                               0x00000008W
#define CKSVII2C1_IC_INTW_MASK__M1_TX_EMPTY_MASK                                                              0x00000010W
#define CKSVII2C1_IC_INTW_MASK__M1_WD_WEQ_MASK                                                                0x00000020W
#define CKSVII2C1_IC_INTW_MASK__M1_TX_ABWT_MASK                                                               0x00000040W
#define CKSVII2C1_IC_INTW_MASK__M1_WX_DONE_MASK                                                               0x00000080W
#define CKSVII2C1_IC_INTW_MASK__M1_ACTIVITY_MASK                                                              0x00000100W
#define CKSVII2C1_IC_INTW_MASK__M1_STOP_DET_MASK                                                              0x00000200W
#define CKSVII2C1_IC_INTW_MASK__M1_STAWT_DET_MASK                                                             0x00000400W
#define CKSVII2C1_IC_INTW_MASK__M1_GEN_CAWW_MASK                                                              0x00000800W
#define CKSVII2C1_IC_INTW_MASK__M1_WESTAWT_DET_MASK                                                           0x00001000W
#define CKSVII2C1_IC_INTW_MASK__M1_MST_ON_HOWD_MASK                                                           0x00002000W
//CKSVII2C1_IC_WAW_INTW_STAT
//CKSVII2C1_IC_WX_TW
//CKSVII2C1_IC_TX_TW
//CKSVII2C1_IC_CWW_INTW
//CKSVII2C1_IC_CWW_WX_UNDEW
//CKSVII2C1_IC_CWW_WX_OVEW
//CKSVII2C1_IC_CWW_TX_OVEW
//CKSVII2C1_IC_CWW_WD_WEQ
//CKSVII2C1_IC_CWW_TX_ABWT
//CKSVII2C1_IC_CWW_WX_DONE
//CKSVII2C1_IC_CWW_ACTIVITY
//CKSVII2C1_IC_CWW_STOP_DET
//CKSVII2C1_IC_CWW_STAWT_DET
//CKSVII2C1_IC_CWW_GEN_CAWW
//CKSVII2C1_IC_ENABWE
#define CKSVII2C1_IC_ENABWE__ENABWE1__SHIFT                                                                   0x0
#define CKSVII2C1_IC_ENABWE__ABOWT1__SHIFT                                                                    0x1
#define CKSVII2C1_IC_ENABWE__ENABWE1_MASK                                                                     0x00000001W
#define CKSVII2C1_IC_ENABWE__ABOWT1_MASK                                                                      0x00000002W
//CKSVII2C1_IC_STATUS
#define CKSVII2C1_IC_STATUS__ACTIVITY1__SHIFT                                                                 0x0
#define CKSVII2C1_IC_STATUS__TFNF1__SHIFT                                                                     0x1
#define CKSVII2C1_IC_STATUS__TFE1__SHIFT                                                                      0x2
#define CKSVII2C1_IC_STATUS__WFNE1__SHIFT                                                                     0x3
#define CKSVII2C1_IC_STATUS__WFF1__SHIFT                                                                      0x4
#define CKSVII2C1_IC_STATUS__MST1_ACTIVITY__SHIFT                                                             0x5
#define CKSVII2C1_IC_STATUS__SWV1_ACTIVITY__SHIFT                                                             0x6
#define CKSVII2C1_IC_STATUS__ACTIVITY1_MASK                                                                   0x00000001W
#define CKSVII2C1_IC_STATUS__TFNF1_MASK                                                                       0x00000002W
#define CKSVII2C1_IC_STATUS__TFE1_MASK                                                                        0x00000004W
#define CKSVII2C1_IC_STATUS__WFNE1_MASK                                                                       0x00000008W
#define CKSVII2C1_IC_STATUS__WFF1_MASK                                                                        0x00000010W
#define CKSVII2C1_IC_STATUS__MST1_ACTIVITY_MASK                                                               0x00000020W
#define CKSVII2C1_IC_STATUS__SWV1_ACTIVITY_MASK                                                               0x00000040W
//CKSVII2C1_IC_TXFWW
//CKSVII2C1_IC_WXFWW
//CKSVII2C1_IC_SDA_HOWD
#define CKSVII2C1_IC_SDA_HOWD__IC1_SDA_HOWD__SHIFT                                                            0x0
#define CKSVII2C1_IC_SDA_HOWD__IC1_SDA_HOWD_MASK                                                              0x00FFFFFFW
//CKSVII2C1_IC_TX_ABWT_SOUWCE
//CKSVII2C1_IC_SWV_DATA_NACK_ONWY
//CKSVII2C1_IC_DMA_CW
//CKSVII2C1_IC_DMA_TDWW
//CKSVII2C1_IC_DMA_WDWW
//CKSVII2C1_IC_SDA_SETUP
#define CKSVII2C1_IC_SDA_SETUP__SDA1_SETUP__SHIFT                                                             0x0
#define CKSVII2C1_IC_SDA_SETUP__SDA1_SETUP_MASK                                                               0x000000FFW
//CKSVII2C1_IC_ACK_GENEWAW_CAWW
#define CKSVII2C1_IC_ACK_GENEWAW_CAWW__ACK1_GENEWAW_CAWW__SHIFT                                               0x0
#define CKSVII2C1_IC_ACK_GENEWAW_CAWW__ACK1_GENEWAW_CAWW_MASK                                                 0x00000001W
//CKSVII2C1_IC_ENABWE_STATUS
#define CKSVII2C1_IC_ENABWE_STATUS__IC1_EN__SHIFT                                                             0x0
#define CKSVII2C1_IC_ENABWE_STATUS__SWV1_WX_ABOWTED__SHIFT                                                    0x1
#define CKSVII2C1_IC_ENABWE_STATUS__SWV1_FIFO_FIWWED_AND_FWUSHED__SHIFT                                       0x2
#define CKSVII2C1_IC_ENABWE_STATUS__IC1_EN_MASK                                                               0x00000001W
#define CKSVII2C1_IC_ENABWE_STATUS__SWV1_WX_ABOWTED_MASK                                                      0x00000002W
#define CKSVII2C1_IC_ENABWE_STATUS__SWV1_FIFO_FIWWED_AND_FWUSHED_MASK                                         0x00000004W
//SMUIO_MP_WESET_INTW
#define SMUIO_MP_WESET_INTW__SMUIO_MP_WESET_INTW__SHIFT                                                       0x0
#define SMUIO_MP_WESET_INTW__SMUIO_MP_WESET_INTW_MASK                                                         0x00000001W
//SMUIO_SOC_HAWT
#define SMUIO_SOC_HAWT__WDT_FOWCE_PWWOK_EN__SHIFT                                                             0x2
#define SMUIO_SOC_HAWT__WDT_FOWCE_WESETn_EN__SHIFT                                                            0x3
#define SMUIO_SOC_HAWT__WDT_FOWCE_PWWOK_EN_MASK                                                               0x00000004W
#define SMUIO_SOC_HAWT__WDT_FOWCE_WESETn_EN_MASK                                                              0x00000008W
//SMUIO_PWWMGT
#define SMUIO_PWWMGT__i2c_cwk_gate_en__SHIFT                                                                  0x0
#define SMUIO_PWWMGT__i2c1_cwk_gate_en__SHIFT                                                                 0x4
#define SMUIO_PWWMGT__i2c_cwk_gate_en_MASK                                                                    0x00000001W
#define SMUIO_PWWMGT__i2c1_cwk_gate_en_MASK                                                                   0x00000010W
//WOM_CNTW
#define WOM_CNTW__CWOCK_GATING_EN__SHIFT                                                                      0x0
#define WOM_CNTW__SPI_TIMING_WEWAX__SHIFT                                                                     0x14
#define WOM_CNTW__SPI_TIMING_WEWAX_OVEWWIDE__SHIFT                                                            0x15
#define WOM_CNTW__SPI_FAST_MODE__SHIFT                                                                        0x16
#define WOM_CNTW__SPI_FAST_MODE_OVEWWIDE__SHIFT                                                               0x17
#define WOM_CNTW__SCK_PWESCAWE_WEFCWK__SHIFT                                                                  0x18
#define WOM_CNTW__SCK_PWESCAWE_WEFCWK_OVEWWIDE__SHIFT                                                         0x1c
#define WOM_CNTW__CWOCK_GATING_EN_MASK                                                                        0x00000001W
#define WOM_CNTW__SPI_TIMING_WEWAX_MASK                                                                       0x00100000W
#define WOM_CNTW__SPI_TIMING_WEWAX_OVEWWIDE_MASK                                                              0x00200000W
#define WOM_CNTW__SPI_FAST_MODE_MASK                                                                          0x00400000W
#define WOM_CNTW__SPI_FAST_MODE_OVEWWIDE_MASK                                                                 0x00800000W
#define WOM_CNTW__SCK_PWESCAWE_WEFCWK_MASK                                                                    0x0F000000W
#define WOM_CNTW__SCK_PWESCAWE_WEFCWK_OVEWWIDE_MASK                                                           0x10000000W
//PAGE_MIWWOW_CNTW
#define PAGE_MIWWOW_CNTW__PAGE_MIWWOW_BASE_ADDW__SHIFT                                                        0x0
#define PAGE_MIWWOW_CNTW__PAGE_MIWWOW_INVAWIDATE__SHIFT                                                       0x18
#define PAGE_MIWWOW_CNTW__PAGE_MIWWOW_ENABWE__SHIFT                                                           0x19
#define PAGE_MIWWOW_CNTW__PAGE_MIWWOW_USAGE__SHIFT                                                            0x1a
#define PAGE_MIWWOW_CNTW__PAGE_MIWWOW_BASE_ADDW_MASK                                                          0x00FFFFFFW
#define PAGE_MIWWOW_CNTW__PAGE_MIWWOW_INVAWIDATE_MASK                                                         0x01000000W
#define PAGE_MIWWOW_CNTW__PAGE_MIWWOW_ENABWE_MASK                                                             0x02000000W
#define PAGE_MIWWOW_CNTW__PAGE_MIWWOW_USAGE_MASK                                                              0x0C000000W
//WOM_STATUS
#define WOM_STATUS__WOM_BUSY__SHIFT                                                                           0x0
#define WOM_STATUS__WOM_BUSY_MASK                                                                             0x00000001W
//CGTT_WOM_CWK_CTWW0
#define CGTT_WOM_CWK_CTWW0__ON_DEWAY__SHIFT                                                                   0x0
#define CGTT_WOM_CWK_CTWW0__OFF_HYSTEWESIS__SHIFT                                                             0x4
#define CGTT_WOM_CWK_CTWW0__SOFT_OVEWWIDE1__SHIFT                                                             0x1e
#define CGTT_WOM_CWK_CTWW0__SOFT_OVEWWIDE0__SHIFT                                                             0x1f
#define CGTT_WOM_CWK_CTWW0__ON_DEWAY_MASK                                                                     0x0000000FW
#define CGTT_WOM_CWK_CTWW0__OFF_HYSTEWESIS_MASK                                                               0x00000FF0W
#define CGTT_WOM_CWK_CTWW0__SOFT_OVEWWIDE1_MASK                                                               0x40000000W
#define CGTT_WOM_CWK_CTWW0__SOFT_OVEWWIDE0_MASK                                                               0x80000000W
//WOM_INDEX
#define WOM_INDEX__WOM_INDEX__SHIFT                                                                           0x0
#define WOM_INDEX__WOM_INDEX_MASK                                                                             0x00FFFFFFW
//WOM_DATA
#define WOM_DATA__WOM_DATA__SHIFT                                                                             0x0
#define WOM_DATA__WOM_DATA_MASK                                                                               0xFFFFFFFFW
//WOM_STAWT
#define WOM_STAWT__WOM_STAWT__SHIFT                                                                           0x0
#define WOM_STAWT__WOM_STAWT_MASK                                                                             0x00FFFFFFW
//WOM_SW_CNTW
#define WOM_SW_CNTW__DATA_SIZE__SHIFT                                                                         0x0
#define WOM_SW_CNTW__COMMAND_SIZE__SHIFT                                                                      0x10
#define WOM_SW_CNTW__WOM_SW_WETUWN_DATA_ENABWE__SHIFT                                                         0x12
#define WOM_SW_CNTW__DATA_SIZE_MASK                                                                           0x0000FFFFW
#define WOM_SW_CNTW__COMMAND_SIZE_MASK                                                                        0x00030000W
#define WOM_SW_CNTW__WOM_SW_WETUWN_DATA_ENABWE_MASK                                                           0x00040000W
//WOM_SW_STATUS
#define WOM_SW_STATUS__WOM_SW_DONE__SHIFT                                                                     0x0
#define WOM_SW_STATUS__WOM_SW_DONE_MASK                                                                       0x00000001W
//WOM_SW_COMMAND
#define WOM_SW_COMMAND__WOM_SW_INSTWUCTION__SHIFT                                                             0x0
#define WOM_SW_COMMAND__WOM_SW_ADDWESS__SHIFT                                                                 0x8
#define WOM_SW_COMMAND__WOM_SW_INSTWUCTION_MASK                                                               0x000000FFW
#define WOM_SW_COMMAND__WOM_SW_ADDWESS_MASK                                                                   0xFFFFFF00W
//WOM_SW_DATA_1
#define WOM_SW_DATA_1__WOM_SW_DATA__SHIFT                                                                     0x0
#define WOM_SW_DATA_1__WOM_SW_DATA_MASK                                                                       0xFFFFFFFFW
//WOM_SW_DATA_2
#define WOM_SW_DATA_2__WOM_SW_DATA__SHIFT                                                                     0x0
#define WOM_SW_DATA_2__WOM_SW_DATA_MASK                                                                       0xFFFFFFFFW
//WOM_SW_DATA_3
#define WOM_SW_DATA_3__WOM_SW_DATA__SHIFT                                                                     0x0
#define WOM_SW_DATA_3__WOM_SW_DATA_MASK                                                                       0xFFFFFFFFW
//WOM_SW_DATA_4
#define WOM_SW_DATA_4__WOM_SW_DATA__SHIFT                                                                     0x0
#define WOM_SW_DATA_4__WOM_SW_DATA_MASK                                                                       0xFFFFFFFFW
//WOM_SW_DATA_5
#define WOM_SW_DATA_5__WOM_SW_DATA__SHIFT                                                                     0x0
#define WOM_SW_DATA_5__WOM_SW_DATA_MASK                                                                       0xFFFFFFFFW
//WOM_SW_DATA_6
#define WOM_SW_DATA_6__WOM_SW_DATA__SHIFT                                                                     0x0
#define WOM_SW_DATA_6__WOM_SW_DATA_MASK                                                                       0xFFFFFFFFW
//WOM_SW_DATA_7
#define WOM_SW_DATA_7__WOM_SW_DATA__SHIFT                                                                     0x0
#define WOM_SW_DATA_7__WOM_SW_DATA_MASK                                                                       0xFFFFFFFFW
//WOM_SW_DATA_8
#define WOM_SW_DATA_8__WOM_SW_DATA__SHIFT                                                                     0x0
#define WOM_SW_DATA_8__WOM_SW_DATA_MASK                                                                       0xFFFFFFFFW
//WOM_SW_DATA_9
#define WOM_SW_DATA_9__WOM_SW_DATA__SHIFT                                                                     0x0
#define WOM_SW_DATA_9__WOM_SW_DATA_MASK                                                                       0xFFFFFFFFW
//WOM_SW_DATA_10
#define WOM_SW_DATA_10__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_10__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_11
#define WOM_SW_DATA_11__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_11__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_12
#define WOM_SW_DATA_12__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_12__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_13
#define WOM_SW_DATA_13__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_13__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_14
#define WOM_SW_DATA_14__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_14__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_15
#define WOM_SW_DATA_15__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_15__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_16
#define WOM_SW_DATA_16__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_16__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_17
#define WOM_SW_DATA_17__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_17__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_18
#define WOM_SW_DATA_18__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_18__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_19
#define WOM_SW_DATA_19__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_19__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_20
#define WOM_SW_DATA_20__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_20__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_21
#define WOM_SW_DATA_21__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_21__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_22
#define WOM_SW_DATA_22__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_22__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_23
#define WOM_SW_DATA_23__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_23__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_24
#define WOM_SW_DATA_24__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_24__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_25
#define WOM_SW_DATA_25__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_25__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_26
#define WOM_SW_DATA_26__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_26__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_27
#define WOM_SW_DATA_27__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_27__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_28
#define WOM_SW_DATA_28__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_28__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_29
#define WOM_SW_DATA_29__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_29__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_30
#define WOM_SW_DATA_30__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_30__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_31
#define WOM_SW_DATA_31__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_31__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_32
#define WOM_SW_DATA_32__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_32__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_33
#define WOM_SW_DATA_33__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_33__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_34
#define WOM_SW_DATA_34__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_34__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_35
#define WOM_SW_DATA_35__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_35__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_36
#define WOM_SW_DATA_36__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_36__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_37
#define WOM_SW_DATA_37__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_37__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_38
#define WOM_SW_DATA_38__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_38__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_39
#define WOM_SW_DATA_39__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_39__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_40
#define WOM_SW_DATA_40__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_40__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_41
#define WOM_SW_DATA_41__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_41__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_42
#define WOM_SW_DATA_42__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_42__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_43
#define WOM_SW_DATA_43__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_43__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_44
#define WOM_SW_DATA_44__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_44__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_45
#define WOM_SW_DATA_45__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_45__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_46
#define WOM_SW_DATA_46__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_46__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_47
#define WOM_SW_DATA_47__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_47__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_48
#define WOM_SW_DATA_48__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_48__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_49
#define WOM_SW_DATA_49__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_49__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_50
#define WOM_SW_DATA_50__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_50__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_51
#define WOM_SW_DATA_51__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_51__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_52
#define WOM_SW_DATA_52__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_52__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_53
#define WOM_SW_DATA_53__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_53__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_54
#define WOM_SW_DATA_54__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_54__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_55
#define WOM_SW_DATA_55__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_55__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_56
#define WOM_SW_DATA_56__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_56__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_57
#define WOM_SW_DATA_57__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_57__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_58
#define WOM_SW_DATA_58__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_58__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_59
#define WOM_SW_DATA_59__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_59__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_60
#define WOM_SW_DATA_60__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_60__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_61
#define WOM_SW_DATA_61__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_61__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_62
#define WOM_SW_DATA_62__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_62__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_63
#define WOM_SW_DATA_63__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_63__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//WOM_SW_DATA_64
#define WOM_SW_DATA_64__WOM_SW_DATA__SHIFT                                                                    0x0
#define WOM_SW_DATA_64__WOM_SW_DATA_MASK                                                                      0xFFFFFFFFW
//SMU_GPIOPAD_SW_INT_STAT
#define SMU_GPIOPAD_SW_INT_STAT__SW_INT_STAT__SHIFT                                                           0x0
#define SMU_GPIOPAD_SW_INT_STAT__SW_INT_STAT_MASK                                                             0x00000001W
//SMU_GPIOPAD_MASK
#define SMU_GPIOPAD_MASK__GPIO_MASK__SHIFT                                                                    0x0
#define SMU_GPIOPAD_MASK__GPIO_MASK_MASK                                                                      0x7FFFFFFFW
//SMU_GPIOPAD_A
#define SMU_GPIOPAD_A__GPIO_A__SHIFT                                                                          0x0
#define SMU_GPIOPAD_A__GPIO_A_MASK                                                                            0x7FFFFFFFW
//SMU_GPIOPAD_TXIMPSEW
#define SMU_GPIOPAD_TXIMPSEW__GPIO_TXIMPSEW__SHIFT                                                            0x0
#define SMU_GPIOPAD_TXIMPSEW__GPIO_TXIMPSEW_MASK                                                              0x7FFFFFFFW
//SMU_GPIOPAD_EN
#define SMU_GPIOPAD_EN__GPIO_EN__SHIFT                                                                        0x0
#define SMU_GPIOPAD_EN__GPIO_EN_MASK                                                                          0x7FFFFFFFW
//SMU_GPIOPAD_Y
#define SMU_GPIOPAD_Y__GPIO_Y__SHIFT                                                                          0x0
#define SMU_GPIOPAD_Y__GPIO_Y_MASK                                                                            0x7FFFFFFFW
//SMU_GPIOPAD_WXEN
#define SMU_GPIOPAD_WXEN__GPIO_WXEN__SHIFT                                                                    0x0
#define SMU_GPIOPAD_WXEN__GPIO_WXEN_MASK                                                                      0x7FFFFFFFW
//SMU_GPIOPAD_WCVW_SEW0
#define SMU_GPIOPAD_WCVW_SEW0__GPIO_WCVW_SEW0__SHIFT                                                          0x0
#define SMU_GPIOPAD_WCVW_SEW0__GPIO_WCVW_SEW0_MASK                                                            0x7FFFFFFFW
//SMU_GPIOPAD_WCVW_SEW1
#define SMU_GPIOPAD_WCVW_SEW1__GPIO_WCVW_SEW1__SHIFT                                                          0x0
#define SMU_GPIOPAD_WCVW_SEW1__GPIO_WCVW_SEW1_MASK                                                            0x7FFFFFFFW
//SMU_GPIOPAD_PU_EN
#define SMU_GPIOPAD_PU_EN__GPIO_PU_EN__SHIFT                                                                  0x0
#define SMU_GPIOPAD_PU_EN__GPIO_PU_EN_MASK                                                                    0x7FFFFFFFW
//SMU_GPIOPAD_PD_EN
#define SMU_GPIOPAD_PD_EN__GPIO_PD_EN__SHIFT                                                                  0x0
#define SMU_GPIOPAD_PD_EN__GPIO_PD_EN_MASK                                                                    0x7FFFFFFFW
//SMU_GPIOPAD_PINSTWAPS
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_0__SHIFT                                                         0x0
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_1__SHIFT                                                         0x1
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_2__SHIFT                                                         0x2
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_3__SHIFT                                                         0x3
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_4__SHIFT                                                         0x4
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_5__SHIFT                                                         0x5
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_6__SHIFT                                                         0x6
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_7__SHIFT                                                         0x7
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_8__SHIFT                                                         0x8
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_9__SHIFT                                                         0x9
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_10__SHIFT                                                        0xa
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_11__SHIFT                                                        0xb
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_12__SHIFT                                                        0xc
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_13__SHIFT                                                        0xd
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_14__SHIFT                                                        0xe
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_15__SHIFT                                                        0xf
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_16__SHIFT                                                        0x10
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_17__SHIFT                                                        0x11
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_18__SHIFT                                                        0x12
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_19__SHIFT                                                        0x13
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_20__SHIFT                                                        0x14
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_21__SHIFT                                                        0x15
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_22__SHIFT                                                        0x16
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_23__SHIFT                                                        0x17
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_24__SHIFT                                                        0x18
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_25__SHIFT                                                        0x19
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_26__SHIFT                                                        0x1a
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_27__SHIFT                                                        0x1b
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_28__SHIFT                                                        0x1c
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_29__SHIFT                                                        0x1d
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_30__SHIFT                                                        0x1e
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_0_MASK                                                           0x00000001W
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_1_MASK                                                           0x00000002W
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_2_MASK                                                           0x00000004W
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_3_MASK                                                           0x00000008W
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_4_MASK                                                           0x00000010W
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_5_MASK                                                           0x00000020W
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_6_MASK                                                           0x00000040W
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_7_MASK                                                           0x00000080W
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_8_MASK                                                           0x00000100W
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_9_MASK                                                           0x00000200W
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_10_MASK                                                          0x00000400W
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_11_MASK                                                          0x00000800W
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_12_MASK                                                          0x00001000W
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_13_MASK                                                          0x00002000W
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_14_MASK                                                          0x00004000W
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_15_MASK                                                          0x00008000W
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_16_MASK                                                          0x00010000W
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_17_MASK                                                          0x00020000W
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_18_MASK                                                          0x00040000W
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_19_MASK                                                          0x00080000W
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_20_MASK                                                          0x00100000W
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_21_MASK                                                          0x00200000W
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_22_MASK                                                          0x00400000W
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_23_MASK                                                          0x00800000W
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_24_MASK                                                          0x01000000W
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_25_MASK                                                          0x02000000W
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_26_MASK                                                          0x04000000W
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_27_MASK                                                          0x08000000W
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_28_MASK                                                          0x10000000W
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_29_MASK                                                          0x20000000W
#define SMU_GPIOPAD_PINSTWAPS__GPIO_PINSTWAP_30_MASK                                                          0x40000000W
//DFT_PINSTWAPS
#define DFT_PINSTWAPS__DFT_PINSTWAPS__SHIFT                                                                   0x0
#define DFT_PINSTWAPS__DFT_PINSTWAPS_MASK                                                                     0x000000FFW
//SMU_GPIOPAD_INT_STAT_EN
#define SMU_GPIOPAD_INT_STAT_EN__GPIO_INT_STAT_EN__SHIFT                                                      0x0
#define SMU_GPIOPAD_INT_STAT_EN__SW_INITIATED_INT_STAT_EN__SHIFT                                              0x1f
#define SMU_GPIOPAD_INT_STAT_EN__GPIO_INT_STAT_EN_MASK                                                        0x1FFFFFFFW
#define SMU_GPIOPAD_INT_STAT_EN__SW_INITIATED_INT_STAT_EN_MASK                                                0x80000000W
//SMU_GPIOPAD_INT_STAT
#define SMU_GPIOPAD_INT_STAT__GPIO_INT_STAT__SHIFT                                                            0x0
#define SMU_GPIOPAD_INT_STAT__SW_INITIATED_INT_STAT__SHIFT                                                    0x1f
#define SMU_GPIOPAD_INT_STAT__GPIO_INT_STAT_MASK                                                              0x1FFFFFFFW
#define SMU_GPIOPAD_INT_STAT__SW_INITIATED_INT_STAT_MASK                                                      0x80000000W
//SMU_GPIOPAD_INT_STAT_AK
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_0__SHIFT                                                    0x0
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_1__SHIFT                                                    0x1
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_2__SHIFT                                                    0x2
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_3__SHIFT                                                    0x3
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_4__SHIFT                                                    0x4
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_5__SHIFT                                                    0x5
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_6__SHIFT                                                    0x6
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_7__SHIFT                                                    0x7
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_8__SHIFT                                                    0x8
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_9__SHIFT                                                    0x9
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_10__SHIFT                                                   0xa
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_11__SHIFT                                                   0xb
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_12__SHIFT                                                   0xc
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_13__SHIFT                                                   0xd
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_14__SHIFT                                                   0xe
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_15__SHIFT                                                   0xf
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_16__SHIFT                                                   0x10
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_17__SHIFT                                                   0x11
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_18__SHIFT                                                   0x12
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_19__SHIFT                                                   0x13
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_20__SHIFT                                                   0x14
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_21__SHIFT                                                   0x15
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_22__SHIFT                                                   0x16
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_23__SHIFT                                                   0x17
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_24__SHIFT                                                   0x18
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_25__SHIFT                                                   0x19
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_26__SHIFT                                                   0x1a
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_27__SHIFT                                                   0x1b
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_28__SHIFT                                                   0x1c
#define SMU_GPIOPAD_INT_STAT_AK__SW_INITIATED_INT_STAT_AK__SHIFT                                              0x1f
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_0_MASK                                                      0x00000001W
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_1_MASK                                                      0x00000002W
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_2_MASK                                                      0x00000004W
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_3_MASK                                                      0x00000008W
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_4_MASK                                                      0x00000010W
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_5_MASK                                                      0x00000020W
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_6_MASK                                                      0x00000040W
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_7_MASK                                                      0x00000080W
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_8_MASK                                                      0x00000100W
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_9_MASK                                                      0x00000200W
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_10_MASK                                                     0x00000400W
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_11_MASK                                                     0x00000800W
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_12_MASK                                                     0x00001000W
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_13_MASK                                                     0x00002000W
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_14_MASK                                                     0x00004000W
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_15_MASK                                                     0x00008000W
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_16_MASK                                                     0x00010000W
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_17_MASK                                                     0x00020000W
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_18_MASK                                                     0x00040000W
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_19_MASK                                                     0x00080000W
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_20_MASK                                                     0x00100000W
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_21_MASK                                                     0x00200000W
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_22_MASK                                                     0x00400000W
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_23_MASK                                                     0x00800000W
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_24_MASK                                                     0x01000000W
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_25_MASK                                                     0x02000000W
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_26_MASK                                                     0x04000000W
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_27_MASK                                                     0x08000000W
#define SMU_GPIOPAD_INT_STAT_AK__GPIO_INT_STAT_AK_28_MASK                                                     0x10000000W
#define SMU_GPIOPAD_INT_STAT_AK__SW_INITIATED_INT_STAT_AK_MASK                                                0x80000000W
//SMU_GPIOPAD_INT_EN
#define SMU_GPIOPAD_INT_EN__GPIO_INT_EN__SHIFT                                                                0x0
#define SMU_GPIOPAD_INT_EN__SW_INITIATED_INT_EN__SHIFT                                                        0x1f
#define SMU_GPIOPAD_INT_EN__GPIO_INT_EN_MASK                                                                  0x1FFFFFFFW
#define SMU_GPIOPAD_INT_EN__SW_INITIATED_INT_EN_MASK                                                          0x80000000W
//SMU_GPIOPAD_INT_TYPE
#define SMU_GPIOPAD_INT_TYPE__GPIO_INT_TYPE__SHIFT                                                            0x0
#define SMU_GPIOPAD_INT_TYPE__SW_INITIATED_INT_TYPE__SHIFT                                                    0x1f
#define SMU_GPIOPAD_INT_TYPE__GPIO_INT_TYPE_MASK                                                              0x1FFFFFFFW
#define SMU_GPIOPAD_INT_TYPE__SW_INITIATED_INT_TYPE_MASK                                                      0x80000000W
//SMU_GPIOPAD_INT_POWAWITY
#define SMU_GPIOPAD_INT_POWAWITY__GPIO_INT_POWAWITY__SHIFT                                                    0x0
#define SMU_GPIOPAD_INT_POWAWITY__SW_INITIATED_INT_POWAWITY__SHIFT                                            0x1f
#define SMU_GPIOPAD_INT_POWAWITY__GPIO_INT_POWAWITY_MASK                                                      0x1FFFFFFFW
#define SMU_GPIOPAD_INT_POWAWITY__SW_INITIATED_INT_POWAWITY_MASK                                              0x80000000W
//WOM_CC_BIF_PINSTWAP
#define WOM_CC_BIF_PINSTWAP__BIOS_WOM_EN__SHIFT                                                               0x0
#define WOM_CC_BIF_PINSTWAP__BIF_MEM_AP_SIZE__SHIFT                                                           0x1
#define WOM_CC_BIF_PINSTWAP__WOM_CONFIG__SHIFT                                                                0x4
#define WOM_CC_BIF_PINSTWAP__BIF_GEN3_DIS_A__SHIFT                                                            0x7
#define WOM_CC_BIF_PINSTWAP__BIF_CWK_PM_EN__SHIFT                                                             0x8
#define WOM_CC_BIF_PINSTWAP__BIF_VGA_DIS__SHIFT                                                               0x9
#define WOM_CC_BIF_PINSTWAP__BIF_WC_TX_SWING__SHIFT                                                           0xa
#define WOM_CC_BIF_PINSTWAP__BIOS_WOM_EN_MASK                                                                 0x00000001W
#define WOM_CC_BIF_PINSTWAP__BIF_MEM_AP_SIZE_MASK                                                             0x0000000EW
#define WOM_CC_BIF_PINSTWAP__WOM_CONFIG_MASK                                                                  0x00000070W
#define WOM_CC_BIF_PINSTWAP__BIF_GEN3_DIS_A_MASK                                                              0x00000080W
#define WOM_CC_BIF_PINSTWAP__BIF_CWK_PM_EN_MASK                                                               0x00000100W
#define WOM_CC_BIF_PINSTWAP__BIF_VGA_DIS_MASK                                                                 0x00000200W
#define WOM_CC_BIF_PINSTWAP__BIF_WC_TX_SWING_MASK                                                             0x00000400W
//IO_SMUIO_PINSTWAP
#define IO_SMUIO_PINSTWAP__AUD_POWT_CONN__SHIFT                                                               0x0
#define IO_SMUIO_PINSTWAP__AUD__SHIFT                                                                         0x3
#define IO_SMUIO_PINSTWAP__BOAWD_CONFIG__SHIFT                                                                0x5
#define IO_SMUIO_PINSTWAP__SMBUS_ADDW__SHIFT                                                                  0x8
#define IO_SMUIO_PINSTWAP__AUD_POWT_CONN_MASK                                                                 0x00000007W
#define IO_SMUIO_PINSTWAP__AUD_MASK                                                                           0x00000018W
#define IO_SMUIO_PINSTWAP__BOAWD_CONFIG_MASK                                                                  0x000000E0W
#define IO_SMUIO_PINSTWAP__SMBUS_ADDW_MASK                                                                    0x00000100W
//SMUIO_PCC_CONTWOW
#define SMUIO_PCC_CONTWOW__PCC_POWAWITY__SHIFT                                                                0x0
#define SMUIO_PCC_CONTWOW__PCC_POWAWITY_MASK                                                                  0x00000001W
//SMUIO_PCC_GPIO_SEWECT
#define SMUIO_PCC_GPIO_SEWECT__GPIO__SHIFT                                                                    0x0
#define SMUIO_PCC_GPIO_SEWECT__GPIO_MASK                                                                      0xFFFFFFFFW
//SMUIO_GPIO_INT0_SEWECT
#define SMUIO_GPIO_INT0_SEWECT__GPIO_INT0_SEWECT__SHIFT                                                       0x0
#define SMUIO_GPIO_INT0_SEWECT__GPIO_INT0_SEWECT_MASK                                                         0xFFFFFFFFW
//SMUIO_GPIO_INT1_SEWECT
#define SMUIO_GPIO_INT1_SEWECT__GPIO_INT1_SEWECT__SHIFT                                                       0x0
#define SMUIO_GPIO_INT1_SEWECT__GPIO_INT1_SEWECT_MASK                                                         0xFFFFFFFFW
//SMUIO_GPIO_INT2_SEWECT
#define SMUIO_GPIO_INT2_SEWECT__GPIO_INT2_SEWECT__SHIFT                                                       0x0
#define SMUIO_GPIO_INT2_SEWECT__GPIO_INT2_SEWECT_MASK                                                         0xFFFFFFFFW
//SMUIO_GPIO_INT3_SEWECT
#define SMUIO_GPIO_INT3_SEWECT__GPIO_INT3_SEWECT__SHIFT                                                       0x0
#define SMUIO_GPIO_INT3_SEWECT__GPIO_INT3_SEWECT_MASK                                                         0xFFFFFFFFW
//SMU_GPIOPAD_MP_INT0_STAT
#define SMU_GPIOPAD_MP_INT0_STAT__GPIO_MP_INT0_STAT__SHIFT                                                    0x0
#define SMU_GPIOPAD_MP_INT0_STAT__GPIO_MP_INT0_STAT_MASK                                                      0x1FFFFFFFW
//SMU_GPIOPAD_MP_INT1_STAT
#define SMU_GPIOPAD_MP_INT1_STAT__GPIO_MP_INT1_STAT__SHIFT                                                    0x0
#define SMU_GPIOPAD_MP_INT1_STAT__GPIO_MP_INT1_STAT_MASK                                                      0x1FFFFFFFW
//SMU_GPIOPAD_MP_INT2_STAT
#define SMU_GPIOPAD_MP_INT2_STAT__GPIO_MP_INT2_STAT__SHIFT                                                    0x0
#define SMU_GPIOPAD_MP_INT2_STAT__GPIO_MP_INT2_STAT_MASK                                                      0x1FFFFFFFW
//SMU_GPIOPAD_MP_INT3_STAT
#define SMU_GPIOPAD_MP_INT3_STAT__GPIO_MP_INT3_STAT__SHIFT                                                    0x0
#define SMU_GPIOPAD_MP_INT3_STAT__GPIO_MP_INT3_STAT_MASK                                                      0x1FFFFFFFW
//SMIO_INDEX
#define SMIO_INDEX__SW_SMIO_INDEX__SHIFT                                                                      0x0
#define SMIO_INDEX__SW_SMIO_INDEX_MASK                                                                        0x00000001W
//S0_VID_SMIO_CNTW
#define S0_VID_SMIO_CNTW__S0_SMIO_VAWUES__SHIFT                                                               0x0
#define S0_VID_SMIO_CNTW__S0_SMIO_VAWUES_MASK                                                                 0xFFFFFFFFW
//S1_VID_SMIO_CNTW
#define S1_VID_SMIO_CNTW__S1_SMIO_VAWUES__SHIFT                                                               0x0
#define S1_VID_SMIO_CNTW__S1_SMIO_VAWUES_MASK                                                                 0xFFFFFFFFW
//OPEN_DWAIN_SEWECT
#define OPEN_DWAIN_SEWECT__OPEN_DWAIN_SEWECT__SHIFT                                                           0x0
#define OPEN_DWAIN_SEWECT__WESEWVED__SHIFT                                                                    0x1f
#define OPEN_DWAIN_SEWECT__OPEN_DWAIN_SEWECT_MASK                                                             0x7FFFFFFFW
#define OPEN_DWAIN_SEWECT__WESEWVED_MASK                                                                      0x80000000W
//SMIO_ENABWE
#define SMIO_ENABWE__SMIO_ENABWE__SHIFT                                                                       0x0
#define SMIO_ENABWE__SMIO_ENABWE_MASK                                                                         0xFFFFFFFFW
//SMU_GPIOPAD_S0
#define SMU_GPIOPAD_S0__GPIO_S0__SHIFT                                                                        0x0
#define SMU_GPIOPAD_S0__GPIO_S0_MASK                                                                          0x7FFFFFFFW
//SMU_GPIOPAD_S1
#define SMU_GPIOPAD_S1__GPIO_S1__SHIFT                                                                        0x0
#define SMU_GPIOPAD_S1__GPIO_S1_MASK                                                                          0x7FFFFFFFW
//SMU_GPIOPAD_SCW_EN
#define SMU_GPIOPAD_SCW_EN__GPIO_SCW_EN__SHIFT                                                                0x0
#define SMU_GPIOPAD_SCW_EN__GPIO_SCW_EN_MASK                                                                  0x7FFFFFFFW
//SMU_GPIOPAD_SDA_EN
#define SMU_GPIOPAD_SDA_EN__GPIO_SDA_EN__SHIFT                                                                0x0
#define SMU_GPIOPAD_SDA_EN__GPIO_SDA_EN_MASK                                                                  0x7FFFFFFFW
//SMU_GPIOPAD_SCHMEN
#define SMU_GPIOPAD_SCHMEN__GPIO_SCHMEN__SHIFT                                                                0x0
#define SMU_GPIOPAD_SCHMEN__GPIO_SCHMEN_MASK                                                                  0x7FFFFFFFW


// addwessBwock: smuio_smuio_pww_SmuSmuioDec
//IP_DISCOVEWY_VEWSION
#define IP_DISCOVEWY_VEWSION__IP_DISCOVEWY_VEWSION__SHIFT                                                     0x0
#define IP_DISCOVEWY_VEWSION__IP_DISCOVEWY_VEWSION_MASK                                                       0xFFFFFFFFW
//SOC_GAP_PWWOK
#define SOC_GAP_PWWOK__soc_gap_pwwok__SHIFT                                                                   0x0
#define SOC_GAP_PWWOK__soc_gap_pwwok_MASK                                                                     0x00000001W
//GFX_GAP_PWWOK
#define GFX_GAP_PWWOK__gfx_gap_pwwok__SHIFT                                                                   0x0
#define GFX_GAP_PWWOK__gfx_gap_pwwok_MASK                                                                     0x00000001W
//PWWOK_WEFCWK_GAP_CYCWES
#define PWWOK_WEFCWK_GAP_CYCWES__Pwwok_PweAssewtion_cwkgap_cycwes__SHIFT                                      0x0
#define PWWOK_WEFCWK_GAP_CYCWES__Pwwok_PostAssewtion_cwkgap_cycwes__SHIFT                                     0x8
#define PWWOK_WEFCWK_GAP_CYCWES__Pwwok_PweAssewtion_cwkgap_cycwes_MASK                                        0x000000FFW
#define PWWOK_WEFCWK_GAP_CYCWES__Pwwok_PostAssewtion_cwkgap_cycwes_MASK                                       0x0000FF00W
//GOWDEN_TSC_INCWEMENT_UPPEW
#define GOWDEN_TSC_INCWEMENT_UPPEW__GowdenTscIncwementUppew__SHIFT                                            0x0
#define GOWDEN_TSC_INCWEMENT_UPPEW__GowdenTscIncwementUppew_MASK                                              0x00FFFFFFW
//GOWDEN_TSC_INCWEMENT_WOWEW
#define GOWDEN_TSC_INCWEMENT_WOWEW__GowdenTscIncwementWowew__SHIFT                                            0x0
#define GOWDEN_TSC_INCWEMENT_WOWEW__GowdenTscIncwementWowew_MASK                                              0xFFFFFFFFW
//GOWDEN_TSC_COUNT_UPPEW
#define GOWDEN_TSC_COUNT_UPPEW__GowdenTscCountUppew__SHIFT                                                    0x0
#define GOWDEN_TSC_COUNT_UPPEW__GowdenTscCountUppew_MASK                                                      0x00FFFFFFW
//GOWDEN_TSC_COUNT_WOWEW
#define GOWDEN_TSC_COUNT_WOWEW__GowdenTscCountWowew__SHIFT                                                    0x0
#define GOWDEN_TSC_COUNT_WOWEW__GowdenTscCountWowew_MASK                                                      0xFFFFFFFFW
//SOC_GOWDEN_TSC_SHADOW_UPPEW
#define SOC_GOWDEN_TSC_SHADOW_UPPEW__SOCGowdenTscShadowUppew__SHIFT                                           0x0
#define SOC_GOWDEN_TSC_SHADOW_UPPEW__SOCGowdenTscShadowUppew_MASK                                             0x00FFFFFFW
//SOC_GOWDEN_TSC_SHADOW_WOWEW
#define SOC_GOWDEN_TSC_SHADOW_WOWEW__SOCGowdenTscShadowWowew__SHIFT                                           0x0
#define SOC_GOWDEN_TSC_SHADOW_WOWEW__SOCGowdenTscShadowWowew_MASK                                             0xFFFFFFFFW
//GFX_GOWDEN_TSC_SHADOW_UPPEW
#define GFX_GOWDEN_TSC_SHADOW_UPPEW__GFXGowdenTscShadowUppew__SHIFT                                           0x0
#define GFX_GOWDEN_TSC_SHADOW_UPPEW__GFXGowdenTscShadowUppew_MASK                                             0x00FFFFFFW
//GFX_GOWDEN_TSC_SHADOW_WOWEW
#define GFX_GOWDEN_TSC_SHADOW_WOWEW__GFXGowdenTscShadowWowew__SHIFT                                           0x0
#define GFX_GOWDEN_TSC_SHADOW_WOWEW__GFXGowdenTscShadowWowew_MASK                                             0xFFFFFFFFW
//PWW_VIWT_WESET_WEQ
#define PWW_VIWT_WESET_WEQ__VF_FWW__SHIFT                                                                     0x0
#define PWW_VIWT_WESET_WEQ__PF_FWW__SHIFT                                                                     0x1f
#define PWW_VIWT_WESET_WEQ__VF_FWW_MASK                                                                       0x7FFFFFFFW
#define PWW_VIWT_WESET_WEQ__PF_FWW_MASK                                                                       0x80000000W
//SCWATCH_WEGISTEW0
#define SCWATCH_WEGISTEW0__ScwatchPad0__SHIFT                                                                 0x0
#define SCWATCH_WEGISTEW0__ScwatchPad0_MASK                                                                   0xFFFFFFFFW
//SCWATCH_WEGISTEW1
#define SCWATCH_WEGISTEW1__ScwatchPad1__SHIFT                                                                 0x0
#define SCWATCH_WEGISTEW1__ScwatchPad1_MASK                                                                   0xFFFFFFFFW
//SCWATCH_WEGISTEW2
#define SCWATCH_WEGISTEW2__ScwatchPad2__SHIFT                                                                 0x0
#define SCWATCH_WEGISTEW2__ScwatchPad2_MASK                                                                   0xFFFFFFFFW
//SCWATCH_WEGISTEW3
#define SCWATCH_WEGISTEW3__ScwatchPad3__SHIFT                                                                 0x0
#define SCWATCH_WEGISTEW3__ScwatchPad3_MASK                                                                   0xFFFFFFFFW
//SCWATCH_WEGISTEW4
#define SCWATCH_WEGISTEW4__ScwatchPad4__SHIFT                                                                 0x0
#define SCWATCH_WEGISTEW4__ScwatchPad4_MASK                                                                   0xFFFFFFFFW
//SCWATCH_WEGISTEW5
#define SCWATCH_WEGISTEW5__ScwatchPad5__SHIFT                                                                 0x0
#define SCWATCH_WEGISTEW5__ScwatchPad5_MASK                                                                   0xFFFFFFFFW
//SCWATCH_WEGISTEW6
#define SCWATCH_WEGISTEW6__ScwatchPad6__SHIFT                                                                 0x0
#define SCWATCH_WEGISTEW6__ScwatchPad6_MASK                                                                   0xFFFFFFFFW
//SCWATCH_WEGISTEW7
#define SCWATCH_WEGISTEW7__ScwatchPad7__SHIFT                                                                 0x0
#define SCWATCH_WEGISTEW7__ScwatchPad7_MASK                                                                   0xFFFFFFFFW
//PWW_DISP_TIMEW_CONTWOW
#define PWW_DISP_TIMEW_CONTWOW__DISP_TIMEW_INT_COUNT__SHIFT                                                   0x0
#define PWW_DISP_TIMEW_CONTWOW__DISP_TIMEW_INT_ENABWE__SHIFT                                                  0x19
#define PWW_DISP_TIMEW_CONTWOW__DISP_TIMEW_INT_DISABWE__SHIFT                                                 0x1a
#define PWW_DISP_TIMEW_CONTWOW__DISP_TIMEW_INT_MASK__SHIFT                                                    0x1b
#define PWW_DISP_TIMEW_CONTWOW__DISP_TIMEW_INT_STAT_AK__SHIFT                                                 0x1c
#define PWW_DISP_TIMEW_CONTWOW__DISP_TIMEW_INT_TYPE__SHIFT                                                    0x1d
#define PWW_DISP_TIMEW_CONTWOW__DISP_TIMEW_INT_MODE__SHIFT                                                    0x1e
#define PWW_DISP_TIMEW_CONTWOW__DISP_TIMEW_INT_COUNT_MASK                                                     0x01FFFFFFW
#define PWW_DISP_TIMEW_CONTWOW__DISP_TIMEW_INT_ENABWE_MASK                                                    0x02000000W
#define PWW_DISP_TIMEW_CONTWOW__DISP_TIMEW_INT_DISABWE_MASK                                                   0x04000000W
#define PWW_DISP_TIMEW_CONTWOW__DISP_TIMEW_INT_MASK_MASK                                                      0x08000000W
#define PWW_DISP_TIMEW_CONTWOW__DISP_TIMEW_INT_STAT_AK_MASK                                                   0x10000000W
#define PWW_DISP_TIMEW_CONTWOW__DISP_TIMEW_INT_TYPE_MASK                                                      0x20000000W
#define PWW_DISP_TIMEW_CONTWOW__DISP_TIMEW_INT_MODE_MASK                                                      0x40000000W
//PWW_DISP_TIMEW2_CONTWOW
#define PWW_DISP_TIMEW2_CONTWOW__DISP_TIMEW_INT_COUNT__SHIFT                                                  0x0
#define PWW_DISP_TIMEW2_CONTWOW__DISP_TIMEW_INT_ENABWE__SHIFT                                                 0x19
#define PWW_DISP_TIMEW2_CONTWOW__DISP_TIMEW_INT_DISABWE__SHIFT                                                0x1a
#define PWW_DISP_TIMEW2_CONTWOW__DISP_TIMEW_INT_MASK__SHIFT                                                   0x1b
#define PWW_DISP_TIMEW2_CONTWOW__DISP_TIMEW_INT_STAT_AK__SHIFT                                                0x1c
#define PWW_DISP_TIMEW2_CONTWOW__DISP_TIMEW_INT_TYPE__SHIFT                                                   0x1d
#define PWW_DISP_TIMEW2_CONTWOW__DISP_TIMEW_INT_MODE__SHIFT                                                   0x1e
#define PWW_DISP_TIMEW2_CONTWOW__DISP_TIMEW_INT_COUNT_MASK                                                    0x01FFFFFFW
#define PWW_DISP_TIMEW2_CONTWOW__DISP_TIMEW_INT_ENABWE_MASK                                                   0x02000000W
#define PWW_DISP_TIMEW2_CONTWOW__DISP_TIMEW_INT_DISABWE_MASK                                                  0x04000000W
#define PWW_DISP_TIMEW2_CONTWOW__DISP_TIMEW_INT_MASK_MASK                                                     0x08000000W
#define PWW_DISP_TIMEW2_CONTWOW__DISP_TIMEW_INT_STAT_AK_MASK                                                  0x10000000W
#define PWW_DISP_TIMEW2_CONTWOW__DISP_TIMEW_INT_TYPE_MASK                                                     0x20000000W
#define PWW_DISP_TIMEW2_CONTWOW__DISP_TIMEW_INT_MODE_MASK                                                     0x40000000W
//PWW_DISP_TIMEW_GWOBAW_CONTWOW
#define PWW_DISP_TIMEW_GWOBAW_CONTWOW__DISP_TIMEW_PUWSE_WIDTH__SHIFT                                          0x0
#define PWW_DISP_TIMEW_GWOBAW_CONTWOW__DISP_TIMEW_PUWSE_EN__SHIFT                                             0xa
#define PWW_DISP_TIMEW_GWOBAW_CONTWOW__DISP_TIMEW_PUWSE_WIDTH_MASK                                            0x000003FFW
#define PWW_DISP_TIMEW_GWOBAW_CONTWOW__DISP_TIMEW_PUWSE_EN_MASK                                               0x00000400W
//PWW_IH_CONTWOW
#define PWW_IH_CONTWOW__MAX_CWEDIT__SHIFT                                                                     0x0
#define PWW_IH_CONTWOW__DISP_TIMEW_TWIGGEW_MASK__SHIFT                                                        0x5
#define PWW_IH_CONTWOW__DISP_TIMEW2_TWIGGEW_MASK__SHIFT                                                       0x6
#define PWW_IH_CONTWOW__MAX_CWEDIT_MASK                                                                       0x0000001FW
#define PWW_IH_CONTWOW__DISP_TIMEW_TWIGGEW_MASK_MASK                                                          0x00000020W
#define PWW_IH_CONTWOW__DISP_TIMEW2_TWIGGEW_MASK_MASK                                                         0x00000040W

#endif
