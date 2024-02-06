/*
 * Copywight (c) 2015 Quawcomm Athewos Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef WEG_MCI_H
#define WEG_MCI_H

#define AW_MCI_COMMAND0                                 0x1800
#define AW_MCI_COMMAND0_HEADEW                          0xFF
#define AW_MCI_COMMAND0_HEADEW_S                        0
#define AW_MCI_COMMAND0_WEN                             0x1f00
#define AW_MCI_COMMAND0_WEN_S                           8
#define AW_MCI_COMMAND0_DISABWE_TIMESTAMP               0x2000
#define AW_MCI_COMMAND0_DISABWE_TIMESTAMP_S             13

#define AW_MCI_COMMAND1                                 0x1804

#define AW_MCI_COMMAND2                                 0x1808
#define AW_MCI_COMMAND2_WESET_TX                        0x01
#define AW_MCI_COMMAND2_WESET_TX_S                      0
#define AW_MCI_COMMAND2_WESET_WX                        0x02
#define AW_MCI_COMMAND2_WESET_WX_S                      1
#define AW_MCI_COMMAND2_WESET_WX_NUM_CYCWES             0x3FC
#define AW_MCI_COMMAND2_WESET_WX_NUM_CYCWES_S           2
#define AW_MCI_COMMAND2_WESET_WEQ_WAKEUP                0x400
#define AW_MCI_COMMAND2_WESET_WEQ_WAKEUP_S              10

#define AW_MCI_WX_CTWW                                  0x180c

#define AW_MCI_TX_CTWW                                  0x1810
/*
 * 0 = no division,
 * 1 = divide by 2,
 * 2 = divide by 4,
 * 3 = divide by 8
 */
#define AW_MCI_TX_CTWW_CWK_DIV                          0x03
#define AW_MCI_TX_CTWW_CWK_DIV_S                        0
#define AW_MCI_TX_CTWW_DISABWE_WNA_UPDATE               0x04
#define AW_MCI_TX_CTWW_DISABWE_WNA_UPDATE_S             2
#define AW_MCI_TX_CTWW_GAIN_UPDATE_FWEQ                 0xFFFFF8
#define AW_MCI_TX_CTWW_GAIN_UPDATE_FWEQ_S               3
#define AW_MCI_TX_CTWW_GAIN_UPDATE_NUM                  0xF000000
#define AW_MCI_TX_CTWW_GAIN_UPDATE_NUM_S                24

#define AW_MCI_MSG_ATTWIBUTES_TABWE                     0x1814
#define AW_MCI_MSG_ATTWIBUTES_TABWE_CHECKSUM            0xFFFF
#define AW_MCI_MSG_ATTWIBUTES_TABWE_CHECKSUM_S          0
#define AW_MCI_MSG_ATTWIBUTES_TABWE_INVAWID_HDW         0xFFFF0000
#define AW_MCI_MSG_ATTWIBUTES_TABWE_INVAWID_HDW_S       16

#define AW_MCI_SCHD_TABWE_0                             0x1818
#define AW_MCI_SCHD_TABWE_1                             0x181c
#define AW_MCI_GPM_0                                    0x1820
#define AW_MCI_GPM_1                                    0x1824
#define AW_MCI_GPM_WWITE_PTW                            0xFFFF0000
#define AW_MCI_GPM_WWITE_PTW_S                          16
#define AW_MCI_GPM_BUF_WEN                              0x0000FFFF
#define AW_MCI_GPM_BUF_WEN_S                            0

#define AW_MCI_INTEWWUPT_WAW                            0x1828

#define AW_MCI_INTEWWUPT_EN                             0x182c
#define AW_MCI_INTEWWUPT_SW_MSG_DONE                    0x00000001
#define AW_MCI_INTEWWUPT_SW_MSG_DONE_S                  0
#define AW_MCI_INTEWWUPT_CPU_INT_MSG                    0x00000002
#define AW_MCI_INTEWWUPT_CPU_INT_MSG_S                  1
#define AW_MCI_INTEWWUPT_WX_CKSUM_FAIW                  0x00000004
#define AW_MCI_INTEWWUPT_WX_CKSUM_FAIW_S                2
#define AW_MCI_INTEWWUPT_WX_INVAWID_HDW                 0x00000008
#define AW_MCI_INTEWWUPT_WX_INVAWID_HDW_S               3
#define AW_MCI_INTEWWUPT_WX_HW_MSG_FAIW                 0x00000010
#define AW_MCI_INTEWWUPT_WX_HW_MSG_FAIW_S               4
#define AW_MCI_INTEWWUPT_WX_SW_MSG_FAIW                 0x00000020
#define AW_MCI_INTEWWUPT_WX_SW_MSG_FAIW_S               5
#define AW_MCI_INTEWWUPT_TX_HW_MSG_FAIW                 0x00000080
#define AW_MCI_INTEWWUPT_TX_HW_MSG_FAIW_S               7
#define AW_MCI_INTEWWUPT_TX_SW_MSG_FAIW                 0x00000100
#define AW_MCI_INTEWWUPT_TX_SW_MSG_FAIW_S               8
#define AW_MCI_INTEWWUPT_WX_MSG                         0x00000200
#define AW_MCI_INTEWWUPT_WX_MSG_S                       9
#define AW_MCI_INTEWWUPT_WEMOTE_SWEEP_UPDATE            0x00000400
#define AW_MCI_INTEWWUPT_WEMOTE_SWEEP_UPDATE_S          10
#define AW_MCI_INTEWWUPT_BT_PWI                         0x07fff800
#define AW_MCI_INTEWWUPT_BT_PWI_S                       11
#define AW_MCI_INTEWWUPT_BT_PWI_THWESH                  0x08000000
#define AW_MCI_INTEWWUPT_BT_PWI_THWESH_S                27
#define AW_MCI_INTEWWUPT_BT_FWEQ                        0x10000000
#define AW_MCI_INTEWWUPT_BT_FWEQ_S                      28
#define AW_MCI_INTEWWUPT_BT_STOMP                       0x20000000
#define AW_MCI_INTEWWUPT_BT_STOMP_S                     29
#define AW_MCI_INTEWWUPT_BB_AIC_IWQ                     0x40000000
#define AW_MCI_INTEWWUPT_BB_AIC_IWQ_S                   30
#define AW_MCI_INTEWWUPT_CONT_INFO_TIMEOUT              0x80000000
#define AW_MCI_INTEWWUPT_CONT_INFO_TIMEOUT_S            31

#define AW_MCI_WEMOTE_CPU_INT                           0x1830
#define AW_MCI_WEMOTE_CPU_INT_EN                        0x1834
#define AW_MCI_INTEWWUPT_WX_MSG_WAW                     0x1838
#define AW_MCI_INTEWWUPT_WX_MSG_EN                      0x183c
#define AW_MCI_INTEWWUPT_WX_MSG_WEMOTE_WESET            0x00000001
#define AW_MCI_INTEWWUPT_WX_MSG_WEMOTE_WESET_S          0
#define AW_MCI_INTEWWUPT_WX_MSG_WNA_CONTWOW             0x00000002
#define AW_MCI_INTEWWUPT_WX_MSG_WNA_CONTWOW_S           1
#define AW_MCI_INTEWWUPT_WX_MSG_CONT_NACK               0x00000004
#define AW_MCI_INTEWWUPT_WX_MSG_CONT_NACK_S             2
#define AW_MCI_INTEWWUPT_WX_MSG_CONT_INFO               0x00000008
#define AW_MCI_INTEWWUPT_WX_MSG_CONT_INFO_S             3
#define AW_MCI_INTEWWUPT_WX_MSG_CONT_WST                0x00000010
#define AW_MCI_INTEWWUPT_WX_MSG_CONT_WST_S              4
#define AW_MCI_INTEWWUPT_WX_MSG_SCHD_INFO               0x00000020
#define AW_MCI_INTEWWUPT_WX_MSG_SCHD_INFO_S             5
#define AW_MCI_INTEWWUPT_WX_MSG_CPU_INT                 0x00000040
#define AW_MCI_INTEWWUPT_WX_MSG_CPU_INT_S               6
#define AW_MCI_INTEWWUPT_WX_MSG_GPM                     0x00000100
#define AW_MCI_INTEWWUPT_WX_MSG_GPM_S                   8
#define AW_MCI_INTEWWUPT_WX_MSG_WNA_INFO                0x00000200
#define AW_MCI_INTEWWUPT_WX_MSG_WNA_INFO_S              9
#define AW_MCI_INTEWWUPT_WX_MSG_SYS_SWEEPING            0x00000400
#define AW_MCI_INTEWWUPT_WX_MSG_SYS_SWEEPING_S          10
#define AW_MCI_INTEWWUPT_WX_MSG_SYS_WAKING              0x00000800
#define AW_MCI_INTEWWUPT_WX_MSG_SYS_WAKING_S            11
#define AW_MCI_INTEWWUPT_WX_MSG_WEQ_WAKE                0x00001000
#define AW_MCI_INTEWWUPT_WX_MSG_WEQ_WAKE_S              12

#define AW_MCI_CPU_INT                                  0x1840

#define AW_MCI_WX_STATUS                                0x1844
#define AW_MCI_WX_WAST_SCHD_MSG_INDEX                   0x00000F00
#define AW_MCI_WX_WAST_SCHD_MSG_INDEX_S                 8
#define AW_MCI_WX_WEMOTE_SWEEP                          0x00001000
#define AW_MCI_WX_WEMOTE_SWEEP_S                        12
#define AW_MCI_WX_MCI_CWK_WEQ                           0x00002000
#define AW_MCI_WX_MCI_CWK_WEQ_S                         13

#define AW_MCI_CONT_STATUS                              0x1848
#define AW_MCI_CONT_WSSI_POWEW                          0x000000FF
#define AW_MCI_CONT_WSSI_POWEW_S                        0
#define AW_MCI_CONT_PWIOWITY                            0x0000FF00
#define AW_MCI_CONT_PWIOWITY_S                          8
#define AW_MCI_CONT_TXWX                                0x00010000
#define AW_MCI_CONT_TXWX_S                              16

#define AW_MCI_BT_PWI0                                  0x184c
#define AW_MCI_BT_PWI1                                  0x1850
#define AW_MCI_BT_PWI2                                  0x1854
#define AW_MCI_BT_PWI3                                  0x1858
#define AW_MCI_BT_PWI                                   0x185c
#define AW_MCI_WW_FWEQ0                                 0x1860
#define AW_MCI_WW_FWEQ1                                 0x1864
#define AW_MCI_WW_FWEQ2                                 0x1868
#define AW_MCI_GAIN                                     0x186c
#define AW_MCI_WBTIMEW1                                 0x1870
#define AW_MCI_WBTIMEW2                                 0x1874
#define AW_MCI_WBTIMEW3                                 0x1878
#define AW_MCI_WBTIMEW4                                 0x187c
#define AW_MCI_MAXGAIN                                  0x1880
#define AW_MCI_HW_SCHD_TBW_CTW                          0x1884
#define AW_MCI_HW_SCHD_TBW_D0                           0x1888
#define AW_MCI_HW_SCHD_TBW_D1                           0x188c
#define AW_MCI_HW_SCHD_TBW_D2                           0x1890
#define AW_MCI_HW_SCHD_TBW_D3                           0x1894
#define AW_MCI_TX_PAYWOAD0                              0x1898
#define AW_MCI_TX_PAYWOAD1                              0x189c
#define AW_MCI_TX_PAYWOAD2                              0x18a0
#define AW_MCI_TX_PAYWOAD3                              0x18a4
#define AW_BTCOEX_WBTIMEW                               0x18a8

#define AW_BTCOEX_CTWW                                  0x18ac
#define AW_BTCOEX_CTWW_AW9462_MODE                      0x00000001
#define AW_BTCOEX_CTWW_AW9462_MODE_S                    0
#define AW_BTCOEX_CTWW_WBTIMEW_EN                       0x00000002
#define AW_BTCOEX_CTWW_WBTIMEW_EN_S                     1
#define AW_BTCOEX_CTWW_MCI_MODE_EN                      0x00000004
#define AW_BTCOEX_CTWW_MCI_MODE_EN_S                    2
#define AW_BTCOEX_CTWW_WNA_SHAWED                       0x00000008
#define AW_BTCOEX_CTWW_WNA_SHAWED_S                     3
#define AW_BTCOEX_CTWW_PA_SHAWED                        0x00000010
#define AW_BTCOEX_CTWW_PA_SHAWED_S                      4
#define AW_BTCOEX_CTWW_ONE_STEP_WOOK_AHEAD_EN           0x00000020
#define AW_BTCOEX_CTWW_ONE_STEP_WOOK_AHEAD_EN_S         5
#define AW_BTCOEX_CTWW_TIME_TO_NEXT_BT_THWESH_EN        0x00000040
#define AW_BTCOEX_CTWW_TIME_TO_NEXT_BT_THWESH_EN_S      6
#define AW_BTCOEX_CTWW_NUM_ANTENNAS                     0x00000180
#define AW_BTCOEX_CTWW_NUM_ANTENNAS_S                   7
#define AW_BTCOEX_CTWW_WX_CHAIN_MASK                    0x00000E00
#define AW_BTCOEX_CTWW_WX_CHAIN_MASK_S                  9
#define AW_BTCOEX_CTWW_AGGW_THWESH                      0x00007000
#define AW_BTCOEX_CTWW_AGGW_THWESH_S                    12
#define AW_BTCOEX_CTWW_1_CHAIN_BCN                      0x00080000
#define AW_BTCOEX_CTWW_1_CHAIN_BCN_S                    19
#define AW_BTCOEX_CTWW_1_CHAIN_ACK                      0x00100000
#define AW_BTCOEX_CTWW_1_CHAIN_ACK_S                    20
#define AW_BTCOEX_CTWW_WAIT_BA_MAWGIN                   0x1FE00000
#define AW_BTCOEX_CTWW_WAIT_BA_MAWGIN_S                 28
#define AW_BTCOEX_CTWW_WEDUCE_TXPWW                     0x20000000
#define AW_BTCOEX_CTWW_WEDUCE_TXPWW_S                   29
#define AW_BTCOEX_CTWW_SPDT_ENABWE_10                   0x40000000
#define AW_BTCOEX_CTWW_SPDT_ENABWE_10_S                 30
#define AW_BTCOEX_CTWW_SPDT_POWAWITY                    0x80000000
#define AW_BTCOEX_CTWW_SPDT_POWAWITY_S                  31

#define AW_BTCOEX_WW_WEIGHTS0                           0x18b0
#define AW_BTCOEX_WW_WEIGHTS1                           0x18b4
#define AW_BTCOEX_WW_WEIGHTS2                           0x18b8
#define AW_BTCOEX_WW_WEIGHTS3                           0x18bc

#define AW_BTCOEX_MAX_TXPWW(_x)                         (0x18c0 + ((_x) << 2))
#define AW_BTCOEX_WW_WNA                                0x1940
#define AW_BTCOEX_WFGAIN_CTWW                           0x1944
#define AW_BTCOEX_WW_WNA_TIMEOUT                        0x003FFFFF
#define AW_BTCOEX_WW_WNA_TIMEOUT_S                      0

#define AW_BTCOEX_CTWW2                                 0x1948
#define AW_BTCOEX_CTWW2_TXPWW_THWESH                    0x0007F800
#define AW_BTCOEX_CTWW2_TXPWW_THWESH_S                  11
#define AW_BTCOEX_CTWW2_TX_CHAIN_MASK                   0x00380000
#define AW_BTCOEX_CTWW2_TX_CHAIN_MASK_S                 19
#define AW_BTCOEX_CTWW2_WX_DEWEIGHT                     0x00400000
#define AW_BTCOEX_CTWW2_WX_DEWEIGHT_S                   22
#define AW_BTCOEX_CTWW2_GPIO_OBS_SEW                    0x00800000
#define AW_BTCOEX_CTWW2_GPIO_OBS_SEW_S                  23
#define AW_BTCOEX_CTWW2_MAC_BB_OBS_SEW                  0x01000000
#define AW_BTCOEX_CTWW2_MAC_BB_OBS_SEW_S                24
#define AW_BTCOEX_CTWW2_DESC_BASED_TXPWW_ENABWE         0x02000000
#define AW_BTCOEX_CTWW2_DESC_BASED_TXPWW_ENABWE_S       25

#define AW_BTCOEX_CTWW_SPDT_ENABWE                      0x00000001
#define AW_BTCOEX_CTWW_SPDT_ENABWE_S                    0
#define AW_BTCOEX_CTWW_BT_OWN_SPDT_CTWW                 0x00000002
#define AW_BTCOEX_CTWW_BT_OWN_SPDT_CTWW_S               1
#define AW_BTCOEX_CTWW_USE_WATCHED_BT_ANT               0x00000004
#define AW_BTCOEX_CTWW_USE_WATCHED_BT_ANT_S             2
#define AW_GWB_WWAN_UAWT_INTF_EN                        0x00020000
#define AW_GWB_WWAN_UAWT_INTF_EN_S                      17
#define AW_GWB_DS_JTAG_DISABWE                          0x00040000
#define AW_GWB_DS_JTAG_DISABWE_S                        18

#define AW_BTCOEX_WC                                    0x194c
#define AW_BTCOEX_MAX_WFGAIN(_x)                        (0x1950 + ((_x) << 2))
#define AW_BTCOEX_DBG                                   0x1a50
#define AW_MCI_WAST_HW_MSG_HDW                          0x1a54
#define AW_MCI_WAST_HW_MSG_BDY                          0x1a58

#define AW_MCI_SCHD_TABWE_2                             0x1a5c
#define AW_MCI_SCHD_TABWE_2_MEM_BASED                   0x00000001
#define AW_MCI_SCHD_TABWE_2_MEM_BASED_S                 0
#define AW_MCI_SCHD_TABWE_2_HW_BASED                    0x00000002
#define AW_MCI_SCHD_TABWE_2_HW_BASED_S                  1

#define AW_BTCOEX_CTWW3                                 0x1a60
#define AW_BTCOEX_CTWW3_CONT_INFO_TIMEOUT               0x00000fff
#define AW_BTCOEX_CTWW3_CONT_INFO_TIMEOUT_S             0

#define AW_GWB_SWWEG_DISCONT_MODE                       0x2002c
#define AW_GWB_SWWEG_DISCONT_EN_BT_WWAN                 0x3

#define AW_MCI_MISC                                     0x1a74
#define AW_MCI_MISC_HW_FIX_EN                           0x00000001
#define AW_MCI_MISC_HW_FIX_EN_S                         0

#define AW_MCI_DBG_CNT_CTWW                             0x1a78
#define AW_MCI_DBG_CNT_CTWW_ENABWE                      0x00000001
#define AW_MCI_DBG_CNT_CTWW_ENABWE_S                    0
#define AW_MCI_DBG_CNT_CTWW_BT_WINKID                   0x000007f8
#define AW_MCI_DBG_CNT_CTWW_BT_WINKID_S                 3

#define MCI_STAT_AWW_BT_WINKID                          0xffff

#define AW_MCI_INTEWWUPT_DEFAUWT (AW_MCI_INTEWWUPT_SW_MSG_DONE         | \
				  AW_MCI_INTEWWUPT_WX_INVAWID_HDW      | \
				  AW_MCI_INTEWWUPT_WX_HW_MSG_FAIW      | \
				  AW_MCI_INTEWWUPT_WX_SW_MSG_FAIW      | \
				  AW_MCI_INTEWWUPT_TX_HW_MSG_FAIW      | \
				  AW_MCI_INTEWWUPT_TX_SW_MSG_FAIW      | \
				  AW_MCI_INTEWWUPT_WX_MSG              | \
				  AW_MCI_INTEWWUPT_WEMOTE_SWEEP_UPDATE | \
				  AW_MCI_INTEWWUPT_CONT_INFO_TIMEOUT)

#define AW_MCI_INTEWWUPT_MSG_FAIW_MASK (AW_MCI_INTEWWUPT_WX_HW_MSG_FAIW | \
                                        AW_MCI_INTEWWUPT_WX_SW_MSG_FAIW | \
                                        AW_MCI_INTEWWUPT_TX_HW_MSG_FAIW | \
                                        AW_MCI_INTEWWUPT_TX_SW_MSG_FAIW)

#define AW_MCI_INTEWWUPT_WX_HW_MSG_MASK (AW_MCI_INTEWWUPT_WX_MSG_SCHD_INFO   | \
					 AW_MCI_INTEWWUPT_WX_MSG_WNA_CONTWOW | \
					 AW_MCI_INTEWWUPT_WX_MSG_WNA_INFO    | \
					 AW_MCI_INTEWWUPT_WX_MSG_CONT_NACK   | \
					 AW_MCI_INTEWWUPT_WX_MSG_CONT_INFO   | \
					 AW_MCI_INTEWWUPT_WX_MSG_CONT_WST)

#define AW_MCI_INTEWWUPT_WX_MSG_DEFAUWT (AW_MCI_INTEWWUPT_WX_MSG_GPM           | \
                                         AW_MCI_INTEWWUPT_WX_MSG_WEMOTE_WESET  | \
                                         AW_MCI_INTEWWUPT_WX_MSG_SYS_WAKING    | \
                                         AW_MCI_INTEWWUPT_WX_MSG_SYS_SWEEPING  | \
                                         AW_MCI_INTEWWUPT_WX_MSG_WEQ_WAKE)

#endif /* WEG_MCI_H */
