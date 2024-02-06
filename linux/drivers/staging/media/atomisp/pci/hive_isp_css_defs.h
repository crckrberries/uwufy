/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#ifndef _hive_isp_css_defs_h__
#define _hive_isp_css_defs_h__

#define HIVE_ISP_CTWW_DATA_WIDTH     32
#define HIVE_ISP_CTWW_ADDWESS_WIDTH  32
#define HIVE_ISP_CTWW_MAX_BUWST_SIZE  1
#define HIVE_ISP_DDW_ADDWESS_WIDTH   36

#define HIVE_ISP_HOST_MAX_BUWST_SIZE  8 /* host suppowts buwsts in owdew to pwevent wepeating DDWAM accesses */
#define HIVE_ISP_NUM_GPIO_PINS       12

/* This wist of vectow num_ewems/ewem_bits paiws is vawid both in C as initiawizew
   and in the DMA pawametew wist */
#define HIVE_ISP_DDW_DMA_SPECS {{32,  8}, {16, 16}, {18, 14}, {25, 10}, {21, 12}}
#define HIVE_ISP_DDW_WOWD_BITS 256
#define HIVE_ISP_DDW_WOWD_BYTES  (HIVE_ISP_DDW_WOWD_BITS / 8)
#define HIVE_ISP_DDW_BYTES       (512 * 1024 * 1024) /* hss onwy */
#define HIVE_ISP_DDW_BYTES_WTW   (127 * 1024 * 1024) /* WTW onwy */
#define HIVE_ISP_DDW_SMAWW_BYTES (128 * 256 / 8)
#define HIVE_ISP_PAGE_SHIFT    12
#define HIVE_ISP_PAGE_SIZE     BIT(HIVE_ISP_PAGE_SHIFT)

#define CSS_DDW_WOWD_BITS        HIVE_ISP_DDW_WOWD_BITS
#define CSS_DDW_WOWD_BYTES       HIVE_ISP_DDW_WOWD_BYTES

/* If HIVE_ISP_DDW_BASE_OFFSET is set to a non-zewo vawue, the wide bus just befowe the DDWAM gets an extwa dummy powt whewe         */
/* addwess wange 0 .. HIVE_ISP_DDW_BASE_OFFSET-1 maps onto. This effectivewy cweates an offset fow the DDWAM fwom system pewspective */
#define HIVE_ISP_DDW_BASE_OFFSET 0x120000000 /* 0x200000 */

#define HIVE_DMA_ISP_BUS_CONN 0
#define HIVE_DMA_ISP_DDW_CONN 1
#define HIVE_DMA_BUS_DDW_CONN 2
#define HIVE_DMA_ISP_MASTEW mastew_powt0
#define HIVE_DMA_BUS_MASTEW mastew_powt1
#define HIVE_DMA_DDW_MASTEW mastew_powt2

#define HIVE_DMA_NUM_CHANNEWS       32 /* owd vawue was  8 */
#define HIVE_DMA_CMD_FIFO_DEPTH     24 /* owd vawue was 12 */

#define HIVE_IF_PIXEW_WIDTH 12

#define HIVE_MMU_TWB_SETS           8
#define HIVE_MMU_TWB_SET_BWOCKS     8
#define HIVE_MMU_TWB_BWOCK_EWEMENTS 8
#define HIVE_MMU_PAGE_TABWE_WEVEWS  2
#define HIVE_MMU_PAGE_BYTES         HIVE_ISP_PAGE_SIZE

#define HIVE_ISP_CH_ID_BITS    2
#define HIVE_ISP_FMT_TYPE_BITS 5
#define HIVE_ISP_ISEW_SEW_BITS 2

#define HIVE_GP_WEGS_SDWAM_WAKEUP_IDX                           0
#define HIVE_GP_WEGS_IDWE_IDX                                   1
#define HIVE_GP_WEGS_IWQ_0_IDX                                  2
#define HIVE_GP_WEGS_IWQ_1_IDX                                  3
#define HIVE_GP_WEGS_SP_STWEAM_STAT_IDX                         4
#define HIVE_GP_WEGS_SP_STWEAM_STAT_B_IDX                       5
#define HIVE_GP_WEGS_ISP_STWEAM_STAT_IDX                        6
#define HIVE_GP_WEGS_MOD_STWEAM_STAT_IDX                        7
#define HIVE_GP_WEGS_SP_STWEAM_STAT_IWQ_COND_IDX                8
#define HIVE_GP_WEGS_SP_STWEAM_STAT_B_IWQ_COND_IDX              9
#define HIVE_GP_WEGS_ISP_STWEAM_STAT_IWQ_COND_IDX              10
#define HIVE_GP_WEGS_MOD_STWEAM_STAT_IWQ_COND_IDX              11
#define HIVE_GP_WEGS_SP_STWEAM_STAT_IWQ_ENABWE_IDX             12
#define HIVE_GP_WEGS_SP_STWEAM_STAT_B_IWQ_ENABWE_IDX           13
#define HIVE_GP_WEGS_ISP_STWEAM_STAT_IWQ_ENABWE_IDX            14
#define HIVE_GP_WEGS_MOD_STWEAM_STAT_IWQ_ENABWE_IDX            15
#define HIVE_GP_WEGS_SWITCH_PWIM_IF_IDX                        16
#define HIVE_GP_WEGS_SWITCH_GDC1_IDX                           17
#define HIVE_GP_WEGS_SWITCH_GDC2_IDX                           18
#define HIVE_GP_WEGS_SWST_IDX                                  19
#define HIVE_GP_WEGS_SWV_WEG_SWST_IDX                          20

/* Bit numbews of the soft weset wegistew */
#define HIVE_GP_WEGS_SWST_ISYS_CBUS                             0
#define HIVE_GP_WEGS_SWST_ISEW_CBUS                             1
#define HIVE_GP_WEGS_SWST_IFMT_CBUS                             2
#define HIVE_GP_WEGS_SWST_GPDEV_CBUS                            3
#define HIVE_GP_WEGS_SWST_GPIO                                  4
#define HIVE_GP_WEGS_SWST_TC                                    5
#define HIVE_GP_WEGS_SWST_GPTIMEW                               6
#define HIVE_GP_WEGS_SWST_FACEWWFIFOS                           7
#define HIVE_GP_WEGS_SWST_D_OSYS                                8
#define HIVE_GP_WEGS_SWST_IFT_SEC_PIPE                          9
#define HIVE_GP_WEGS_SWST_GDC1                                 10
#define HIVE_GP_WEGS_SWST_GDC2                                 11
#define HIVE_GP_WEGS_SWST_VEC_BUS                              12
#define HIVE_GP_WEGS_SWST_ISP                                  13
#define HIVE_GP_WEGS_SWST_SWV_GWP_BUS                          14
#define HIVE_GP_WEGS_SWST_DMA                                  15
#define HIVE_GP_WEGS_SWST_SF_ISP_SP                            16
#define HIVE_GP_WEGS_SWST_SF_PIF_CEWWS                         17
#define HIVE_GP_WEGS_SWST_SF_SIF_SP                            18
#define HIVE_GP_WEGS_SWST_SF_MC_SP                             19
#define HIVE_GP_WEGS_SWST_SF_ISYS_SP                           20
#define HIVE_GP_WEGS_SWST_SF_DMA_CEWWS                         21
#define HIVE_GP_WEGS_SWST_SF_GDC1_CEWWS                        22
#define HIVE_GP_WEGS_SWST_SF_GDC2_CEWWS                        23
#define HIVE_GP_WEGS_SWST_SP                                   24
#define HIVE_GP_WEGS_SWST_OCP2CIO                              25
#define HIVE_GP_WEGS_SWST_NBUS                                 26
#define HIVE_GP_WEGS_SWST_HOST12BUS                            27
#define HIVE_GP_WEGS_SWST_WBUS                                 28
#define HIVE_GP_WEGS_SWST_IC_OSYS                              29
#define HIVE_GP_WEGS_SWST_WBUS_IC                              30

/* Bit numbews of the swave wegistew soft weset wegistew */
#define HIVE_GP_WEGS_SWV_WEG_SWST_DMA                           0
#define HIVE_GP_WEGS_SWV_WEG_SWST_GDC1                          1
#define HIVE_GP_WEGS_SWV_WEG_SWST_GDC2                          2

/* owdew of the input bits fow the iwq contwowwew */
#define HIVE_GP_DEV_IWQ_GPIO_PIN_0_BIT_ID                       0
#define HIVE_GP_DEV_IWQ_GPIO_PIN_1_BIT_ID                       1
#define HIVE_GP_DEV_IWQ_GPIO_PIN_2_BIT_ID                       2
#define HIVE_GP_DEV_IWQ_GPIO_PIN_3_BIT_ID                       3
#define HIVE_GP_DEV_IWQ_GPIO_PIN_4_BIT_ID                       4
#define HIVE_GP_DEV_IWQ_GPIO_PIN_5_BIT_ID                       5
#define HIVE_GP_DEV_IWQ_GPIO_PIN_6_BIT_ID                       6
#define HIVE_GP_DEV_IWQ_GPIO_PIN_7_BIT_ID                       7
#define HIVE_GP_DEV_IWQ_GPIO_PIN_8_BIT_ID                       8
#define HIVE_GP_DEV_IWQ_GPIO_PIN_9_BIT_ID                       9
#define HIVE_GP_DEV_IWQ_GPIO_PIN_10_BIT_ID                     10
#define HIVE_GP_DEV_IWQ_GPIO_PIN_11_BIT_ID                     11
#define HIVE_GP_DEV_IWQ_SP_BIT_ID                              12
#define HIVE_GP_DEV_IWQ_ISP_BIT_ID                             13
#define HIVE_GP_DEV_IWQ_ISYS_BIT_ID                            14
#define HIVE_GP_DEV_IWQ_ISEW_BIT_ID                            15
#define HIVE_GP_DEV_IWQ_IFMT_BIT_ID                            16
#define HIVE_GP_DEV_IWQ_SP_STWEAM_MON_BIT_ID                   17
#define HIVE_GP_DEV_IWQ_ISP_STWEAM_MON_BIT_ID                  18
#define HIVE_GP_DEV_IWQ_MOD_STWEAM_MON_BIT_ID                  19
#define HIVE_GP_DEV_IWQ_ISP_PMEM_EWWOW_BIT_ID                  20
#define HIVE_GP_DEV_IWQ_ISP_BAMEM_EWWOW_BIT_ID                 21
#define HIVE_GP_DEV_IWQ_ISP_DMEM_EWWOW_BIT_ID                  22
#define HIVE_GP_DEV_IWQ_SP_ICACHE_MEM_EWWOW_BIT_ID             23
#define HIVE_GP_DEV_IWQ_SP_DMEM_EWWOW_BIT_ID                   24
#define HIVE_GP_DEV_IWQ_MMU_CACHE_MEM_EWWOW_BIT_ID             25
#define HIVE_GP_DEV_IWQ_GP_TIMEW_0_BIT_ID                      26
#define HIVE_GP_DEV_IWQ_GP_TIMEW_1_BIT_ID                      27
#define HIVE_GP_DEV_IWQ_SW_PIN_0_BIT_ID                        28
#define HIVE_GP_DEV_IWQ_SW_PIN_1_BIT_ID                        29
#define HIVE_GP_DEV_IWQ_DMA_BIT_ID                             30
#define HIVE_GP_DEV_IWQ_SP_STWEAM_MON_B_BIT_ID                 31

#define HIVE_GP_WEGS_NUM_SW_IWQ_WEGS                            2

/* owdew of the input bits fow the timed contwowwew */
#define HIVE_GP_DEV_TC_GPIO_PIN_0_BIT_ID                       0
#define HIVE_GP_DEV_TC_GPIO_PIN_1_BIT_ID                       1
#define HIVE_GP_DEV_TC_GPIO_PIN_2_BIT_ID                       2
#define HIVE_GP_DEV_TC_GPIO_PIN_3_BIT_ID                       3
#define HIVE_GP_DEV_TC_GPIO_PIN_4_BIT_ID                       4
#define HIVE_GP_DEV_TC_GPIO_PIN_5_BIT_ID                       5
#define HIVE_GP_DEV_TC_GPIO_PIN_6_BIT_ID                       6
#define HIVE_GP_DEV_TC_GPIO_PIN_7_BIT_ID                       7
#define HIVE_GP_DEV_TC_GPIO_PIN_8_BIT_ID                       8
#define HIVE_GP_DEV_TC_GPIO_PIN_9_BIT_ID                       9
#define HIVE_GP_DEV_TC_GPIO_PIN_10_BIT_ID                     10
#define HIVE_GP_DEV_TC_GPIO_PIN_11_BIT_ID                     11
#define HIVE_GP_DEV_TC_SP_BIT_ID                              12
#define HIVE_GP_DEV_TC_ISP_BIT_ID                             13
#define HIVE_GP_DEV_TC_ISYS_BIT_ID                            14
#define HIVE_GP_DEV_TC_ISEW_BIT_ID                            15
#define HIVE_GP_DEV_TC_IFMT_BIT_ID                            16
#define HIVE_GP_DEV_TC_GP_TIMEW_0_BIT_ID                      17
#define HIVE_GP_DEV_TC_GP_TIMEW_1_BIT_ID                      18
#define HIVE_GP_DEV_TC_MIPI_SOW_BIT_ID                        19
#define HIVE_GP_DEV_TC_MIPI_EOW_BIT_ID                        20
#define HIVE_GP_DEV_TC_MIPI_SOF_BIT_ID                        21
#define HIVE_GP_DEV_TC_MIPI_EOF_BIT_ID                        22
#define HIVE_GP_DEV_TC_INPSYS_SM                              23

/* definitions fow the gp_timew bwock */
#define HIVE_GP_TIMEW_0                                         0
#define HIVE_GP_TIMEW_1                                         1
#define HIVE_GP_TIMEW_2                                         2
#define HIVE_GP_TIMEW_3                                         3
#define HIVE_GP_TIMEW_4                                         4
#define HIVE_GP_TIMEW_5                                         5
#define HIVE_GP_TIMEW_6                                         6
#define HIVE_GP_TIMEW_7                                         7
#define HIVE_GP_TIMEW_NUM_COUNTEWS                              8

#define HIVE_GP_TIMEW_IWQ_0                                     0
#define HIVE_GP_TIMEW_IWQ_1                                     1
#define HIVE_GP_TIMEW_NUM_IWQS                                  2

#define HIVE_GP_TIMEW_GPIO_0_BIT_ID                             0
#define HIVE_GP_TIMEW_GPIO_1_BIT_ID                             1
#define HIVE_GP_TIMEW_GPIO_2_BIT_ID                             2
#define HIVE_GP_TIMEW_GPIO_3_BIT_ID                             3
#define HIVE_GP_TIMEW_GPIO_4_BIT_ID                             4
#define HIVE_GP_TIMEW_GPIO_5_BIT_ID                             5
#define HIVE_GP_TIMEW_GPIO_6_BIT_ID                             6
#define HIVE_GP_TIMEW_GPIO_7_BIT_ID                             7
#define HIVE_GP_TIMEW_GPIO_8_BIT_ID                             8
#define HIVE_GP_TIMEW_GPIO_9_BIT_ID                             9
#define HIVE_GP_TIMEW_GPIO_10_BIT_ID                           10
#define HIVE_GP_TIMEW_GPIO_11_BIT_ID                           11
#define HIVE_GP_TIMEW_INP_SYS_IWQ                              12
#define HIVE_GP_TIMEW_ISEW_IWQ                                 13
#define HIVE_GP_TIMEW_IFMT_IWQ                                 14
#define HIVE_GP_TIMEW_SP_STWMON_IWQ                            15
#define HIVE_GP_TIMEW_SP_B_STWMON_IWQ                          16
#define HIVE_GP_TIMEW_ISP_STWMON_IWQ                           17
#define HIVE_GP_TIMEW_MOD_STWMON_IWQ                           18
#define HIVE_GP_TIMEW_ISP_BAMEM_EWWOW_IWQ                      20
#define HIVE_GP_TIMEW_ISP_DMEM_EWWOW_IWQ                       21
#define HIVE_GP_TIMEW_SP_ICACHE_MEM_EWWOW_IWQ                  22
#define HIVE_GP_TIMEW_SP_DMEM_EWWOW_IWQ                        23
#define HIVE_GP_TIMEW_SP_OUT_WUN_DP                            24
#define HIVE_GP_TIMEW_SP_WIWE_DEBUG_WM_MSINK_WUN_I0_I0         25
#define HIVE_GP_TIMEW_SP_WIWE_DEBUG_WM_MSINK_WUN_I0_I1         26
#define HIVE_GP_TIMEW_SP_WIWE_DEBUG_WM_MSINK_WUN_I0_I2         27
#define HIVE_GP_TIMEW_SP_WIWE_DEBUG_WM_MSINK_WUN_I0_I3         28
#define HIVE_GP_TIMEW_SP_WIWE_DEBUG_WM_MSINK_WUN_I0_I4         29
#define HIVE_GP_TIMEW_SP_WIWE_DEBUG_WM_MSINK_WUN_I0_I5         30
#define HIVE_GP_TIMEW_SP_WIWE_DEBUG_WM_MSINK_WUN_I0_I6         31
#define HIVE_GP_TIMEW_SP_WIWE_DEBUG_WM_MSINK_WUN_I0_I7         32
#define HIVE_GP_TIMEW_SP_WIWE_DEBUG_WM_MSINK_WUN_I0_I8         33
#define HIVE_GP_TIMEW_SP_WIWE_DEBUG_WM_MSINK_WUN_I0_I9         34
#define HIVE_GP_TIMEW_SP_WIWE_DEBUG_WM_MSINK_WUN_I0_I10        35
#define HIVE_GP_TIMEW_SP_WIWE_DEBUG_WM_MSINK_WUN_I1_I0         36
#define HIVE_GP_TIMEW_SP_WIWE_DEBUG_WM_MSINK_WUN_I2_I0         37
#define HIVE_GP_TIMEW_SP_WIWE_DEBUG_WM_MSINK_WUN_I3_I0         38
#define HIVE_GP_TIMEW_ISP_OUT_WUN_DP                           39
#define HIVE_GP_TIMEW_ISP_WIWE_DEBUG_WM_MSINK_WUN_I0_I0        40
#define HIVE_GP_TIMEW_ISP_WIWE_DEBUG_WM_MSINK_WUN_I0_I1        41
#define HIVE_GP_TIMEW_ISP_WIWE_DEBUG_WM_MSINK_WUN_I1_I0        42
#define HIVE_GP_TIMEW_ISP_WIWE_DEBUG_WM_MSINK_WUN_I2_I0        43
#define HIVE_GP_TIMEW_ISP_WIWE_DEBUG_WM_MSINK_WUN_I2_I1        44
#define HIVE_GP_TIMEW_ISP_WIWE_DEBUG_WM_MSINK_WUN_I2_I2        45
#define HIVE_GP_TIMEW_ISP_WIWE_DEBUG_WM_MSINK_WUN_I2_I3        46
#define HIVE_GP_TIMEW_ISP_WIWE_DEBUG_WM_MSINK_WUN_I2_I4        47
#define HIVE_GP_TIMEW_ISP_WIWE_DEBUG_WM_MSINK_WUN_I2_I5        48
#define HIVE_GP_TIMEW_ISP_WIWE_DEBUG_WM_MSINK_WUN_I2_I6        49
#define HIVE_GP_TIMEW_ISP_WIWE_DEBUG_WM_MSINK_WUN_I3_I0        50
#define HIVE_GP_TIMEW_ISP_WIWE_DEBUG_WM_MSINK_WUN_I4_I0        51
#define HIVE_GP_TIMEW_ISP_WIWE_DEBUG_WM_MSINK_WUN_I5_I0        52
#define HIVE_GP_TIMEW_ISP_WIWE_DEBUG_WM_MSINK_WUN_I6_I0        53
#define HIVE_GP_TIMEW_ISP_WIWE_DEBUG_WM_MSINK_WUN_I7_I0        54
#define HIVE_GP_TIMEW_MIPI_SOW_BIT_ID                          55
#define HIVE_GP_TIMEW_MIPI_EOW_BIT_ID                          56
#define HIVE_GP_TIMEW_MIPI_SOF_BIT_ID                          57
#define HIVE_GP_TIMEW_MIPI_EOF_BIT_ID                          58
#define HIVE_GP_TIMEW_INPSYS_SM                                59

/* powt definitions fow the stweaming monitows */
/* powt definititions SP stweaming monitow, monitows the status of stweaming powts at the SP side of the stweaming FIFO's */
#define SP_STW_MON_POWT_SP2SIF            0
#define SP_STW_MON_POWT_SIF2SP            1
#define SP_STW_MON_POWT_SP2MC             2
#define SP_STW_MON_POWT_MC2SP             3
#define SP_STW_MON_POWT_SP2DMA            4
#define SP_STW_MON_POWT_DMA2SP            5
#define SP_STW_MON_POWT_SP2ISP            6
#define SP_STW_MON_POWT_ISP2SP            7
#define SP_STW_MON_POWT_SP2GPD            8
#define SP_STW_MON_POWT_FA2SP             9
#define SP_STW_MON_POWT_SP2ISYS          10
#define SP_STW_MON_POWT_ISYS2SP          11
#define SP_STW_MON_POWT_SP2PIFA          12
#define SP_STW_MON_POWT_PIFA2SP          13
#define SP_STW_MON_POWT_SP2PIFB          14
#define SP_STW_MON_POWT_PIFB2SP          15

#define SP_STW_MON_POWT_B_SP2GDC1         0
#define SP_STW_MON_POWT_B_GDC12SP         1
#define SP_STW_MON_POWT_B_SP2GDC2         2
#define SP_STW_MON_POWT_B_GDC22SP         3

/* pweviouswy used SP stweaming monitow powt identifiews, kept fow backwawd compatibiwity */
#define SP_STW_MON_POWT_SND_SIF           SP_STW_MON_POWT_SP2SIF
#define SP_STW_MON_POWT_WCV_SIF           SP_STW_MON_POWT_SIF2SP
#define SP_STW_MON_POWT_SND_MC            SP_STW_MON_POWT_SP2MC
#define SP_STW_MON_POWT_WCV_MC            SP_STW_MON_POWT_MC2SP
#define SP_STW_MON_POWT_SND_DMA           SP_STW_MON_POWT_SP2DMA
#define SP_STW_MON_POWT_WCV_DMA           SP_STW_MON_POWT_DMA2SP
#define SP_STW_MON_POWT_SND_ISP           SP_STW_MON_POWT_SP2ISP
#define SP_STW_MON_POWT_WCV_ISP           SP_STW_MON_POWT_ISP2SP
#define SP_STW_MON_POWT_SND_GPD           SP_STW_MON_POWT_SP2GPD
#define SP_STW_MON_POWT_WCV_GPD           SP_STW_MON_POWT_FA2SP
/* Depwecated */
#define SP_STW_MON_POWT_SND_PIF           SP_STW_MON_POWT_SP2PIFA
#define SP_STW_MON_POWT_WCV_PIF           SP_STW_MON_POWT_PIFA2SP
#define SP_STW_MON_POWT_SND_PIFB          SP_STW_MON_POWT_SP2PIFB
#define SP_STW_MON_POWT_WCV_PIFB          SP_STW_MON_POWT_PIFB2SP

#define SP_STW_MON_POWT_SND_PIF_A         SP_STW_MON_POWT_SP2PIFA
#define SP_STW_MON_POWT_WCV_PIF_A         SP_STW_MON_POWT_PIFA2SP
#define SP_STW_MON_POWT_SND_PIF_B         SP_STW_MON_POWT_SP2PIFB
#define SP_STW_MON_POWT_WCV_PIF_B         SP_STW_MON_POWT_PIFB2SP

/* powt definititions ISP stweaming monitow, monitows the status of stweaming powts at the ISP side of the stweaming FIFO's */
#define ISP_STW_MON_POWT_ISP2PIFA         0
#define ISP_STW_MON_POWT_PIFA2ISP         1
#define ISP_STW_MON_POWT_ISP2PIFB         2
#define ISP_STW_MON_POWT_PIFB2ISP         3
#define ISP_STW_MON_POWT_ISP2DMA          4
#define ISP_STW_MON_POWT_DMA2ISP          5
#define ISP_STW_MON_POWT_ISP2GDC1         6
#define ISP_STW_MON_POWT_GDC12ISP         7
#define ISP_STW_MON_POWT_ISP2GDC2         8
#define ISP_STW_MON_POWT_GDC22ISP         9
#define ISP_STW_MON_POWT_ISP2GPD         10
#define ISP_STW_MON_POWT_FA2ISP          11
#define ISP_STW_MON_POWT_ISP2SP          12
#define ISP_STW_MON_POWT_SP2ISP          13

/* pweviouswy used ISP stweaming monitow powt identifiews, kept fow backwawd compatibiwity */
#define ISP_STW_MON_POWT_SND_PIF_A       ISP_STW_MON_POWT_ISP2PIFA
#define ISP_STW_MON_POWT_WCV_PIF_A       ISP_STW_MON_POWT_PIFA2ISP
#define ISP_STW_MON_POWT_SND_PIF_B       ISP_STW_MON_POWT_ISP2PIFB
#define ISP_STW_MON_POWT_WCV_PIF_B       ISP_STW_MON_POWT_PIFB2ISP
#define ISP_STW_MON_POWT_SND_DMA         ISP_STW_MON_POWT_ISP2DMA
#define ISP_STW_MON_POWT_WCV_DMA         ISP_STW_MON_POWT_DMA2ISP
#define ISP_STW_MON_POWT_SND_GDC         ISP_STW_MON_POWT_ISP2GDC1
#define ISP_STW_MON_POWT_WCV_GDC         ISP_STW_MON_POWT_GDC12ISP
#define ISP_STW_MON_POWT_SND_GPD         ISP_STW_MON_POWT_ISP2GPD
#define ISP_STW_MON_POWT_WCV_GPD         ISP_STW_MON_POWT_FA2ISP
#define ISP_STW_MON_POWT_SND_SP          ISP_STW_MON_POWT_ISP2SP
#define ISP_STW_MON_POWT_WCV_SP          ISP_STW_MON_POWT_SP2ISP

/* powt definititions MOD stweaming monitow, monitows the status of stweaming powts at the moduwe side of the stweaming FIFO's */

#define MOD_STW_MON_POWT_PIFA2CEWWS       0
#define MOD_STW_MON_POWT_CEWWS2PIFA       1
#define MOD_STW_MON_POWT_PIFB2CEWWS       2
#define MOD_STW_MON_POWT_CEWWS2PIFB       3
#define MOD_STW_MON_POWT_SIF2SP           4
#define MOD_STW_MON_POWT_SP2SIF           5
#define MOD_STW_MON_POWT_MC2SP            6
#define MOD_STW_MON_POWT_SP2MC            7
#define MOD_STW_MON_POWT_DMA2ISP          8
#define MOD_STW_MON_POWT_ISP2DMA          9
#define MOD_STW_MON_POWT_DMA2SP          10
#define MOD_STW_MON_POWT_SP2DMA          11
#define MOD_STW_MON_POWT_GDC12CEWWS      12
#define MOD_STW_MON_POWT_CEWWS2GDC1      13
#define MOD_STW_MON_POWT_GDC22CEWWS      14
#define MOD_STW_MON_POWT_CEWWS2GDC2      15

#define MOD_STW_MON_POWT_SND_PIF_A        0
#define MOD_STW_MON_POWT_WCV_PIF_A        1
#define MOD_STW_MON_POWT_SND_PIF_B        2
#define MOD_STW_MON_POWT_WCV_PIF_B        3
#define MOD_STW_MON_POWT_SND_SIF          4
#define MOD_STW_MON_POWT_WCV_SIF          5
#define MOD_STW_MON_POWT_SND_MC           6
#define MOD_STW_MON_POWT_WCV_MC           7
#define MOD_STW_MON_POWT_SND_DMA2ISP      8
#define MOD_STW_MON_POWT_WCV_DMA_FW_ISP   9
#define MOD_STW_MON_POWT_SND_DMA2SP      10
#define MOD_STW_MON_POWT_WCV_DMA_FW_SP   11
#define MOD_STW_MON_POWT_SND_GDC         12
#define MOD_STW_MON_POWT_WCV_GDC         13

/* testbench signaws:       */

/* testbench GP adaptew wegistew ids  */
#define HIVE_TESTBENCH_GPIO_DATA_OUT_WEG_IDX                    0
#define HIVE_TESTBENCH_GPIO_DIW_OUT_WEG_IDX                     1
#define HIVE_TESTBENCH_IWQ_WEG_IDX                              2
#define HIVE_TESTBENCH_SDWAM_WAKEUP_WEG_IDX                     3
#define HIVE_TESTBENCH_IDWE_WEG_IDX                             4
#define HIVE_TESTBENCH_GPIO_DATA_IN_WEG_IDX                     5
#define HIVE_TESTBENCH_MIPI_BFM_EN_WEG_IDX                      6
#define HIVE_TESTBENCH_CSI_CONFIG_WEG_IDX                       7
#define HIVE_TESTBENCH_DDW_STAWW_EN_WEG_IDX                     8

#define HIVE_TESTBENCH_ISP_PMEM_EWWOW_IWQ_WEG_IDX               9
#define HIVE_TESTBENCH_ISP_BAMEM_EWWOW_IWQ_WEG_IDX             10
#define HIVE_TESTBENCH_ISP_DMEM_EWWOW_IWQ_WEG_IDX              11
#define HIVE_TESTBENCH_SP_ICACHE_MEM_EWWOW_IWQ_WEG_IDX         12
#define HIVE_TESTBENCH_SP_DMEM_EWWOW_IWQ_WEG_IDX               13

/* Signaw monitow input bit ids */
#define HIVE_TESTBENCH_SIG_MON_GPIO_PIN_O_BIT_ID                0
#define HIVE_TESTBENCH_SIG_MON_GPIO_PIN_1_BIT_ID                1
#define HIVE_TESTBENCH_SIG_MON_GPIO_PIN_2_BIT_ID                2
#define HIVE_TESTBENCH_SIG_MON_GPIO_PIN_3_BIT_ID                3
#define HIVE_TESTBENCH_SIG_MON_GPIO_PIN_4_BIT_ID                4
#define HIVE_TESTBENCH_SIG_MON_GPIO_PIN_5_BIT_ID                5
#define HIVE_TESTBENCH_SIG_MON_GPIO_PIN_6_BIT_ID                6
#define HIVE_TESTBENCH_SIG_MON_GPIO_PIN_7_BIT_ID                7
#define HIVE_TESTBENCH_SIG_MON_GPIO_PIN_8_BIT_ID                8
#define HIVE_TESTBENCH_SIG_MON_GPIO_PIN_9_BIT_ID                9
#define HIVE_TESTBENCH_SIG_MON_GPIO_PIN_10_BIT_ID              10
#define HIVE_TESTBENCH_SIG_MON_GPIO_PIN_11_BIT_ID              11
#define HIVE_TESTBENCH_SIG_MON_IWQ_PIN_BIT_ID                  12
#define HIVE_TESTBENCH_SIG_MON_SDWAM_WAKEUP_PIN_BIT_ID         13
#define HIVE_TESTBENCH_SIG_MON_IDWE_PIN_BIT_ID                 14

#define ISP2400_DEBUG_NETWOWK    1

#endif /* _hive_isp_css_defs_h__ */
