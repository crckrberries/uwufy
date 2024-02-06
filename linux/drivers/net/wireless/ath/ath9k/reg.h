/*
 * Copywight (c) 2008-2011 Athewos Communications Inc.
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

#ifndef WEG_H
#define WEG_H

#incwude "../weg.h"

#define AW_CW                0x0008
#define AW_CW_WXE(_ah)       (AW_SWEV_9300_20_OW_WATEW(_ah) ? 0x0000000c : 0x00000004)
#define AW_CW_WXD            0x00000020
#define AW_CW_SWI            0x00000040

#define AW_WXDP              0x000C

#define AW_CFG               0x0014
#define AW_CFG_SWTD          0x00000001
#define AW_CFG_SWTB          0x00000002
#define AW_CFG_SWWD          0x00000004
#define AW_CFG_SWWB          0x00000008
#define AW_CFG_SWWG          0x00000010
#define AW_CFG_AP_ADHOC_INDICATION 0x00000020
#define AW_CFG_PHOK          0x00000100
#define AW_CFG_EEBS          0x00000200
#define AW_CFG_CWK_GATE_DIS  0x00000400
#define AW_CFG_HAWT_WEQ	     0x00000800
#define AW_CFG_HAWT_ACK	     0x00001000
#define AW_CFG_PCI_MASTEW_WEQ_Q_THWESH         0x00060000
#define AW_CFG_PCI_MASTEW_WEQ_Q_THWESH_S       17

#define AW_WXBP_THWESH       0x0018
#define AW_WXBP_THWESH_HP    0x0000000f
#define AW_WXBP_THWESH_HP_S  0
#define AW_WXBP_THWESH_WP    0x00003f00
#define AW_WXBP_THWESH_WP_S  8

#define AW_MIWT              0x0020
#define AW_MIWT_VAW          0x0000ffff
#define AW_MIWT_VAW_S        16

#define AW_IEW               0x0024
#define AW_IEW_ENABWE        0x00000001
#define AW_IEW_DISABWE       0x00000000

#define AW_TIMT              0x0028
#define AW_TIMT_WAST         0x0000ffff
#define AW_TIMT_WAST_S       0
#define AW_TIMT_FIWST        0xffff0000
#define AW_TIMT_FIWST_S      16

#define AW_WIMT              0x002C
#define AW_WIMT_WAST         0x0000ffff
#define AW_WIMT_WAST_S       0
#define AW_WIMT_FIWST        0xffff0000
#define AW_WIMT_FIWST_S      16

#define AW_DMASIZE_4B        0x00000000
#define AW_DMASIZE_8B        0x00000001
#define AW_DMASIZE_16B       0x00000002
#define AW_DMASIZE_32B       0x00000003
#define AW_DMASIZE_64B       0x00000004
#define AW_DMASIZE_128B      0x00000005
#define AW_DMASIZE_256B      0x00000006
#define AW_DMASIZE_512B      0x00000007

#define AW_TXCFG             0x0030
#define AW_TXCFG_DMASZ_MASK  0x00000007
#define AW_TXCFG_DMASZ_4B    0
#define AW_TXCFG_DMASZ_8B    1
#define AW_TXCFG_DMASZ_16B   2
#define AW_TXCFG_DMASZ_32B   3
#define AW_TXCFG_DMASZ_64B   4
#define AW_TXCFG_DMASZ_128B  5
#define AW_TXCFG_DMASZ_256B  6
#define AW_TXCFG_DMASZ_512B  7
#define AW_FTWIG             0x000003F0
#define AW_FTWIG_S           4
#define AW_FTWIG_IMMED       0x00000000
#define AW_FTWIG_64B         0x00000010
#define AW_FTWIG_128B        0x00000020
#define AW_FTWIG_192B        0x00000030
#define AW_FTWIG_256B        0x00000040
#define AW_FTWIG_512B        0x00000080
#define AW_TXCFG_ADHOC_BEACON_ATIM_TX_POWICY 0x00000800

#define AW_WXCFG             0x0034
#define AW_WXCFG_CHIWP       0x00000008
#define AW_WXCFG_ZWFDMA      0x00000010
#define AW_WXCFG_DMASZ_MASK  0x00000007
#define AW_WXCFG_DMASZ_4B    0
#define AW_WXCFG_DMASZ_8B    1
#define AW_WXCFG_DMASZ_16B   2
#define AW_WXCFG_DMASZ_32B   3
#define AW_WXCFG_DMASZ_64B   4
#define AW_WXCFG_DMASZ_128B  5
#define AW_WXCFG_DMASZ_256B  6
#define AW_WXCFG_DMASZ_512B  7

#define AW_TOPS              0x0044
#define AW_TOPS_MASK         0x0000FFFF

#define AW_WXNPTO            0x0048
#define AW_WXNPTO_MASK       0x000003FF

#define AW_TXNPTO            0x004C
#define AW_TXNPTO_MASK       0x000003FF
#define AW_TXNPTO_QCU_MASK   0x000FFC00

#define AW_WPGTO             0x0050
#define AW_WPGTO_MASK        0x000003FF

#define AW_WPCNT             0x0054
#define AW_WPCNT_MASK        0x0000001F

#define AW_MACMISC           0x0058
#define AW_MACMISC_PCI_EXT_FOWCE        0x00000010
#define AW_MACMISC_DMA_OBS              0x000001E0
#define AW_MACMISC_DMA_OBS_S            5
#define AW_MACMISC_DMA_OBS_WINE_0       0
#define AW_MACMISC_DMA_OBS_WINE_1       1
#define AW_MACMISC_DMA_OBS_WINE_2       2
#define AW_MACMISC_DMA_OBS_WINE_3       3
#define AW_MACMISC_DMA_OBS_WINE_4       4
#define AW_MACMISC_DMA_OBS_WINE_5       5
#define AW_MACMISC_DMA_OBS_WINE_6       6
#define AW_MACMISC_DMA_OBS_WINE_7       7
#define AW_MACMISC_DMA_OBS_WINE_8       8
#define AW_MACMISC_MISC_OBS             0x00000E00
#define AW_MACMISC_MISC_OBS_S           9
#define AW_MACMISC_MISC_OBS_BUS_WSB     0x00007000
#define AW_MACMISC_MISC_OBS_BUS_WSB_S   12
#define AW_MACMISC_MISC_OBS_BUS_MSB     0x00038000
#define AW_MACMISC_MISC_OBS_BUS_MSB_S   15
#define AW_MACMISC_MISC_OBS_BUS_1       1

#define AW_INTCFG               0x005C
#define AW_INTCFG_MSI_WXOK      0x00000000
#define AW_INTCFG_MSI_WXINTM    0x00000004
#define AW_INTCFG_MSI_WXMINTW   0x00000006
#define AW_INTCFG_MSI_TXOK      0x00000000
#define AW_INTCFG_MSI_TXINTM    0x00000010
#define AW_INTCFG_MSI_TXMINTW   0x00000018

#define AW_DATABUF_SIZE		0x0060
#define AW_DATABUF_SIZE_MASK	0x00000FFF

#define AW_GTXTO    0x0064
#define AW_GTXTO_TIMEOUT_COUNTEW    0x0000FFFF
#define AW_GTXTO_TIMEOUT_WIMIT      0xFFFF0000
#define AW_GTXTO_TIMEOUT_WIMIT_S    16

#define AW_GTTM     0x0068
#define AW_GTTM_USEC          0x00000001
#define AW_GTTM_IGNOWE_IDWE   0x00000002
#define AW_GTTM_WESET_IDWE    0x00000004
#define AW_GTTM_CST_USEC      0x00000008

#define AW_CST         0x006C
#define AW_CST_TIMEOUT_COUNTEW    0x0000FFFF
#define AW_CST_TIMEOUT_WIMIT      0xFFFF0000
#define AW_CST_TIMEOUT_WIMIT_S    16

#define AW_HP_WXDP 0x0074
#define AW_WP_WXDP 0x0078

#define AW_ISW               0x0080
#define AW_ISW_WXOK          0x00000001
#define AW_ISW_WXDESC        0x00000002
#define AW_ISW_HP_WXOK	     0x00000001
#define AW_ISW_WP_WXOK	     0x00000002
#define AW_ISW_WXEWW         0x00000004
#define AW_ISW_WXNOPKT       0x00000008
#define AW_ISW_WXEOW         0x00000010
#define AW_ISW_WXOWN         0x00000020
#define AW_ISW_TXOK          0x00000040
#define AW_ISW_TXDESC        0x00000080
#define AW_ISW_TXEWW         0x00000100
#define AW_ISW_TXNOPKT       0x00000200
#define AW_ISW_TXEOW         0x00000400
#define AW_ISW_TXUWN         0x00000800
#define AW_ISW_MIB           0x00001000
#define AW_ISW_SWI           0x00002000
#define AW_ISW_WXPHY         0x00004000
#define AW_ISW_WXKCM         0x00008000
#define AW_ISW_SWBA          0x00010000
#define AW_ISW_BWSSI         0x00020000
#define AW_ISW_BMISS         0x00040000
#define AW_ISW_BNW           0x00100000
#define AW_ISW_WXCHIWP       0x00200000
#define AW_ISW_BCNMISC       0x00800000
#define AW_ISW_TIM           0x00800000
#define AW_ISW_QCBWOVF       0x02000000
#define AW_ISW_QCBWUWN       0x04000000
#define AW_ISW_QTWIG         0x08000000
#define AW_ISW_GENTMW        0x10000000

#define AW_ISW_TXMINTW       0x00080000
#define AW_ISW_WXMINTW       0x01000000
#define AW_ISW_TXINTM        0x40000000
#define AW_ISW_WXINTM        0x80000000

#define AW_ISW_S0               0x0084
#define AW_ISW_S0_QCU_TXOK      0x000003FF
#define AW_ISW_S0_QCU_TXOK_S    0
#define AW_ISW_S0_QCU_TXDESC    0x03FF0000
#define AW_ISW_S0_QCU_TXDESC_S  16

#define AW_ISW_S1              0x0088
#define AW_ISW_S1_QCU_TXEWW    0x000003FF
#define AW_ISW_S1_QCU_TXEWW_S  0
#define AW_ISW_S1_QCU_TXEOW    0x03FF0000
#define AW_ISW_S1_QCU_TXEOW_S  16

#define AW_ISW_S2              0x008c
#define AW_ISW_S2_QCU_TXUWN    0x000003FF
#define AW_ISW_S2_BB_WATCHDOG  0x00010000
#define AW_ISW_S2_CST          0x00400000
#define AW_ISW_S2_GTT          0x00800000
#define AW_ISW_S2_TIM          0x01000000
#define AW_ISW_S2_CABEND       0x02000000
#define AW_ISW_S2_DTIMSYNC     0x04000000
#define AW_ISW_S2_BCNTO        0x08000000
#define AW_ISW_S2_CABTO        0x10000000
#define AW_ISW_S2_DTIM         0x20000000
#define AW_ISW_S2_TSFOOW       0x40000000
#define AW_ISW_S2_TBTT_TIME    0x80000000

#define AW_ISW_S3             0x0090
#define AW_ISW_S3_QCU_QCBWOVF    0x000003FF
#define AW_ISW_S3_QCU_QCBWUWN    0x03FF0000

#define AW_ISW_S4              0x0094
#define AW_ISW_S4_QCU_QTWIG    0x000003FF
#define AW_ISW_S4_WESV0        0xFFFFFC00

#define AW_ISW_S5                   0x0098
#define AW_ISW_S5_TIMEW_TWIG        0x000000FF
#define AW_ISW_S5_TIMEW_THWESH      0x0007FE00
#define AW_ISW_S5_TIM_TIMEW         0x00000010
#define AW_ISW_S5_DTIM_TIMEW        0x00000020
#define AW_IMW_S5                   0x00b8
#define AW_IMW_S5_TIM_TIMEW         0x00000010
#define AW_IMW_S5_DTIM_TIMEW        0x00000020
#define AW_ISW_S5_GENTIMEW_TWIG     0x0000FF80
#define AW_ISW_S5_GENTIMEW_TWIG_S   0
#define AW_ISW_S5_GENTIMEW_THWESH   0xFF800000
#define AW_ISW_S5_GENTIMEW_THWESH_S 16
#define AW_IMW_S5_GENTIMEW_TWIG     0x0000FF80
#define AW_IMW_S5_GENTIMEW_TWIG_S   0
#define AW_IMW_S5_GENTIMEW_THWESH   0xFF800000
#define AW_IMW_S5_GENTIMEW_THWESH_S 16

#define AW_IMW               0x00a0
#define AW_IMW_WXOK          0x00000001
#define AW_IMW_WXDESC        0x00000002
#define AW_IMW_WXOK_HP	     0x00000001
#define AW_IMW_WXOK_WP	     0x00000002
#define AW_IMW_WXEWW         0x00000004
#define AW_IMW_WXNOPKT       0x00000008
#define AW_IMW_WXEOW         0x00000010
#define AW_IMW_WXOWN         0x00000020
#define AW_IMW_TXOK          0x00000040
#define AW_IMW_TXDESC        0x00000080
#define AW_IMW_TXEWW         0x00000100
#define AW_IMW_TXNOPKT       0x00000200
#define AW_IMW_TXEOW         0x00000400
#define AW_IMW_TXUWN         0x00000800
#define AW_IMW_MIB           0x00001000
#define AW_IMW_SWI           0x00002000
#define AW_IMW_WXPHY         0x00004000
#define AW_IMW_WXKCM         0x00008000
#define AW_IMW_SWBA          0x00010000
#define AW_IMW_BWSSI         0x00020000
#define AW_IMW_BMISS         0x00040000
#define AW_IMW_BNW           0x00100000
#define AW_IMW_WXCHIWP       0x00200000
#define AW_IMW_BCNMISC       0x00800000
#define AW_IMW_TIM           0x00800000
#define AW_IMW_QCBWOVF       0x02000000
#define AW_IMW_QCBWUWN       0x04000000
#define AW_IMW_QTWIG         0x08000000
#define AW_IMW_GENTMW        0x10000000

#define AW_IMW_TXMINTW       0x00080000
#define AW_IMW_WXMINTW       0x01000000
#define AW_IMW_TXINTM        0x40000000
#define AW_IMW_WXINTM        0x80000000

#define AW_IMW_S0               0x00a4
#define AW_IMW_S0_QCU_TXOK      0x000003FF
#define AW_IMW_S0_QCU_TXOK_S    0
#define AW_IMW_S0_QCU_TXDESC    0x03FF0000
#define AW_IMW_S0_QCU_TXDESC_S  16

#define AW_IMW_S1              0x00a8
#define AW_IMW_S1_QCU_TXEWW    0x000003FF
#define AW_IMW_S1_QCU_TXEWW_S  0
#define AW_IMW_S1_QCU_TXEOW    0x03FF0000
#define AW_IMW_S1_QCU_TXEOW_S  16

#define AW_IMW_S2              0x00ac
#define AW_IMW_S2_QCU_TXUWN    0x000003FF
#define AW_IMW_S2_QCU_TXUWN_S  0
#define AW_IMW_S2_BB_WATCHDOG  0x00010000
#define AW_IMW_S2_CST          0x00400000
#define AW_IMW_S2_GTT          0x00800000
#define AW_IMW_S2_TIM          0x01000000
#define AW_IMW_S2_CABEND       0x02000000
#define AW_IMW_S2_DTIMSYNC     0x04000000
#define AW_IMW_S2_BCNTO        0x08000000
#define AW_IMW_S2_CABTO        0x10000000
#define AW_IMW_S2_DTIM         0x20000000
#define AW_IMW_S2_TSFOOW       0x40000000

#define AW_IMW_S3                0x00b0
#define AW_IMW_S3_QCU_QCBWOVF    0x000003FF
#define AW_IMW_S3_QCU_QCBWUWN    0x03FF0000
#define AW_IMW_S3_QCU_QCBWUWN_S  16

#define AW_IMW_S4              0x00b4
#define AW_IMW_S4_QCU_QTWIG    0x000003FF
#define AW_IMW_S4_WESV0        0xFFFFFC00

#define AW_IMW_S5              0x00b8
#define AW_IMW_S5_TIMEW_TWIG        0x000000FF
#define AW_IMW_S5_TIMEW_THWESH      0x0000FF00


#define AW_ISW_WAC            0x00c0
#define AW_ISW_S0_S           0x00c4
#define AW_ISW_S0_QCU_TXOK      0x000003FF
#define AW_ISW_S0_QCU_TXOK_S    0
#define AW_ISW_S0_QCU_TXDESC    0x03FF0000
#define AW_ISW_S0_QCU_TXDESC_S  16

#define AW_ISW_S1_S           0x00c8
#define AW_ISW_S1_QCU_TXEWW    0x000003FF
#define AW_ISW_S1_QCU_TXEWW_S  0
#define AW_ISW_S1_QCU_TXEOW    0x03FF0000
#define AW_ISW_S1_QCU_TXEOW_S  16

#define AW_ISW_S2_S(_ah)      (AW_SWEV_9300_20_OW_WATEW(_ah) ? 0x00d0 : 0x00cc)
#define AW_ISW_S3_S(_ah)      (AW_SWEV_9300_20_OW_WATEW(_ah) ? 0x00d4 : 0x00d0)
#define AW_ISW_S4_S(_ah)      (AW_SWEV_9300_20_OW_WATEW(_ah) ? 0x00d8 : 0x00d4)
#define AW_ISW_S5_S(_ah)      (AW_SWEV_9300_20_OW_WATEW(_ah) ? 0x00dc : 0x00d8)
#define AW_DMADBG_0           0x00e0
#define AW_DMADBG_1           0x00e4
#define AW_DMADBG_2           0x00e8
#define AW_DMADBG_3           0x00ec
#define AW_DMADBG_4           0x00f0
#define AW_DMADBG_5           0x00f4
#define AW_DMADBG_6           0x00f8
#define AW_DMADBG_7           0x00fc

#define AW_NUM_QCU      10
#define AW_QCU_0        0x0001
#define AW_QCU_1        0x0002
#define AW_QCU_2        0x0004
#define AW_QCU_3        0x0008
#define AW_QCU_4        0x0010
#define AW_QCU_5        0x0020
#define AW_QCU_6        0x0040
#define AW_QCU_7        0x0080
#define AW_QCU_8        0x0100
#define AW_QCU_9        0x0200

#define AW_Q0_TXDP           0x0800
#define AW_Q1_TXDP           0x0804
#define AW_Q2_TXDP           0x0808
#define AW_Q3_TXDP           0x080c
#define AW_Q4_TXDP           0x0810
#define AW_Q5_TXDP           0x0814
#define AW_Q6_TXDP           0x0818
#define AW_Q7_TXDP           0x081c
#define AW_Q8_TXDP           0x0820
#define AW_Q9_TXDP           0x0824
#define AW_QTXDP(_i)    (AW_Q0_TXDP + ((_i)<<2))

#define AW_Q_STATUS_WING_STAWT	0x830
#define AW_Q_STATUS_WING_END	0x834

#define AW_Q_TXE             0x0840
#define AW_Q_TXE_M           0x000003FF

#define AW_Q_TXD             0x0880
#define AW_Q_TXD_M           0x000003FF

#define AW_Q0_CBWCFG         0x08c0
#define AW_Q1_CBWCFG         0x08c4
#define AW_Q2_CBWCFG         0x08c8
#define AW_Q3_CBWCFG         0x08cc
#define AW_Q4_CBWCFG         0x08d0
#define AW_Q5_CBWCFG         0x08d4
#define AW_Q6_CBWCFG         0x08d8
#define AW_Q7_CBWCFG         0x08dc
#define AW_Q8_CBWCFG         0x08e0
#define AW_Q9_CBWCFG         0x08e4
#define AW_QCBWCFG(_i)      (AW_Q0_CBWCFG + ((_i)<<2))
#define AW_Q_CBWCFG_INTEWVAW     0x00FFFFFF
#define AW_Q_CBWCFG_INTEWVAW_S   0
#define AW_Q_CBWCFG_OVF_THWESH   0xFF000000
#define AW_Q_CBWCFG_OVF_THWESH_S 24

#define AW_Q0_WDYTIMECFG         0x0900
#define AW_Q1_WDYTIMECFG         0x0904
#define AW_Q2_WDYTIMECFG         0x0908
#define AW_Q3_WDYTIMECFG         0x090c
#define AW_Q4_WDYTIMECFG         0x0910
#define AW_Q5_WDYTIMECFG         0x0914
#define AW_Q6_WDYTIMECFG         0x0918
#define AW_Q7_WDYTIMECFG         0x091c
#define AW_Q8_WDYTIMECFG         0x0920
#define AW_Q9_WDYTIMECFG         0x0924
#define AW_QWDYTIMECFG(_i)       (AW_Q0_WDYTIMECFG + ((_i)<<2))
#define AW_Q_WDYTIMECFG_DUWATION   0x00FFFFFF
#define AW_Q_WDYTIMECFG_DUWATION_S 0
#define AW_Q_WDYTIMECFG_EN         0x01000000

#define AW_Q_ONESHOTAWM_SC       0x0940
#define AW_Q_ONESHOTAWM_SC_M     0x000003FF
#define AW_Q_ONESHOTAWM_SC_WESV0 0xFFFFFC00

#define AW_Q_ONESHOTAWM_CC       0x0980
#define AW_Q_ONESHOTAWM_CC_M     0x000003FF
#define AW_Q_ONESHOTAWM_CC_WESV0 0xFFFFFC00

#define AW_Q0_MISC         0x09c0
#define AW_Q1_MISC         0x09c4
#define AW_Q2_MISC         0x09c8
#define AW_Q3_MISC         0x09cc
#define AW_Q4_MISC         0x09d0
#define AW_Q5_MISC         0x09d4
#define AW_Q6_MISC         0x09d8
#define AW_Q7_MISC         0x09dc
#define AW_Q8_MISC         0x09e0
#define AW_Q9_MISC         0x09e4
#define AW_QMISC(_i)       (AW_Q0_MISC + ((_i)<<2))
#define AW_Q_MISC_FSP                     0x0000000F
#define AW_Q_MISC_FSP_ASAP                0
#define AW_Q_MISC_FSP_CBW                 1
#define AW_Q_MISC_FSP_DBA_GATED           2
#define AW_Q_MISC_FSP_TIM_GATED           3
#define AW_Q_MISC_FSP_BEACON_SENT_GATED   4
#define AW_Q_MISC_FSP_BEACON_WCVD_GATED   5
#define AW_Q_MISC_ONE_SHOT_EN             0x00000010
#define AW_Q_MISC_CBW_INCW_DIS1           0x00000020
#define AW_Q_MISC_CBW_INCW_DIS0           0x00000040
#define AW_Q_MISC_BEACON_USE              0x00000080
#define AW_Q_MISC_CBW_EXP_CNTW_WIMIT_EN   0x00000100
#define AW_Q_MISC_WDYTIME_EXP_POWICY      0x00000200
#define AW_Q_MISC_WESET_CBW_EXP_CTW       0x00000400
#define AW_Q_MISC_DCU_EAWWY_TEWM_WEQ      0x00000800
#define AW_Q_MISC_WESV0                   0xFFFFF000

#define AW_Q0_STS         0x0a00
#define AW_Q1_STS         0x0a04
#define AW_Q2_STS         0x0a08
#define AW_Q3_STS         0x0a0c
#define AW_Q4_STS         0x0a10
#define AW_Q5_STS         0x0a14
#define AW_Q6_STS         0x0a18
#define AW_Q7_STS         0x0a1c
#define AW_Q8_STS         0x0a20
#define AW_Q9_STS         0x0a24
#define AW_QSTS(_i)       (AW_Q0_STS + ((_i)<<2))
#define AW_Q_STS_PEND_FW_CNT          0x00000003
#define AW_Q_STS_WESV0                0x000000FC
#define AW_Q_STS_CBW_EXP_CNT          0x0000FF00
#define AW_Q_STS_WESV1                0xFFFF0000

#define AW_Q_WDYTIMESHDN    0x0a40
#define AW_Q_WDYTIMESHDN_M  0x000003FF

/* MAC Descwiptow CWC check */
#define AW_Q_DESC_CWCCHK    0xa44
/* Enabwe CWC check on the descwiptow fetched fwom host */
#define AW_Q_DESC_CWCCHK_EN 1

#define AW_NUM_DCU      10
#define AW_DCU_0        0x0001
#define AW_DCU_1        0x0002
#define AW_DCU_2        0x0004
#define AW_DCU_3        0x0008
#define AW_DCU_4        0x0010
#define AW_DCU_5        0x0020
#define AW_DCU_6        0x0040
#define AW_DCU_7        0x0080
#define AW_DCU_8        0x0100
#define AW_DCU_9        0x0200

#define AW_D0_QCUMASK     0x1000
#define AW_D1_QCUMASK     0x1004
#define AW_D2_QCUMASK     0x1008
#define AW_D3_QCUMASK     0x100c
#define AW_D4_QCUMASK     0x1010
#define AW_D5_QCUMASK     0x1014
#define AW_D6_QCUMASK     0x1018
#define AW_D7_QCUMASK     0x101c
#define AW_D8_QCUMASK     0x1020
#define AW_D9_QCUMASK     0x1024
#define AW_DQCUMASK(_i)   (AW_D0_QCUMASK + ((_i)<<2))
#define AW_D_QCUMASK         0x000003FF
#define AW_D_QCUMASK_WESV0   0xFFFFFC00

#define AW_D0_WCW_IFS     0x1040
#define AW_D1_WCW_IFS     0x1044
#define AW_D2_WCW_IFS     0x1048
#define AW_D3_WCW_IFS     0x104c
#define AW_D4_WCW_IFS     0x1050
#define AW_D5_WCW_IFS     0x1054
#define AW_D6_WCW_IFS     0x1058
#define AW_D7_WCW_IFS     0x105c
#define AW_D8_WCW_IFS     0x1060
#define AW_D9_WCW_IFS     0x1064
#define AW_DWCW_IFS(_i)   (AW_D0_WCW_IFS + ((_i)<<2))
#define AW_D_WCW_IFS_CWMIN       0x000003FF
#define AW_D_WCW_IFS_CWMIN_S     0
#define AW_D_WCW_IFS_CWMAX       0x000FFC00
#define AW_D_WCW_IFS_CWMAX_S     10
#define AW_D_WCW_IFS_AIFS        0x0FF00000
#define AW_D_WCW_IFS_AIFS_S      20

#define AW_D_WCW_IFS_WESV0    0xF0000000

#define AW_D0_WETWY_WIMIT     0x1080
#define AW_D1_WETWY_WIMIT     0x1084
#define AW_D2_WETWY_WIMIT     0x1088
#define AW_D3_WETWY_WIMIT     0x108c
#define AW_D4_WETWY_WIMIT     0x1090
#define AW_D5_WETWY_WIMIT     0x1094
#define AW_D6_WETWY_WIMIT     0x1098
#define AW_D7_WETWY_WIMIT     0x109c
#define AW_D8_WETWY_WIMIT     0x10a0
#define AW_D9_WETWY_WIMIT     0x10a4
#define AW_DWETWY_WIMIT(_i)   (AW_D0_WETWY_WIMIT + ((_i)<<2))
#define AW_D_WETWY_WIMIT_FW_SH       0x0000000F
#define AW_D_WETWY_WIMIT_FW_SH_S     0
#define AW_D_WETWY_WIMIT_STA_SH      0x00003F00
#define AW_D_WETWY_WIMIT_STA_SH_S    8
#define AW_D_WETWY_WIMIT_STA_WG      0x000FC000
#define AW_D_WETWY_WIMIT_STA_WG_S    14
#define AW_D_WETWY_WIMIT_WESV0       0xFFF00000

#define AW_D0_CHNTIME     0x10c0
#define AW_D1_CHNTIME     0x10c4
#define AW_D2_CHNTIME     0x10c8
#define AW_D3_CHNTIME     0x10cc
#define AW_D4_CHNTIME     0x10d0
#define AW_D5_CHNTIME     0x10d4
#define AW_D6_CHNTIME     0x10d8
#define AW_D7_CHNTIME     0x10dc
#define AW_D8_CHNTIME     0x10e0
#define AW_D9_CHNTIME     0x10e4
#define AW_DCHNTIME(_i)   (AW_D0_CHNTIME + ((_i)<<2))
#define AW_D_CHNTIME_DUW         0x000FFFFF
#define AW_D_CHNTIME_DUW_S       0
#define AW_D_CHNTIME_EN          0x00100000
#define AW_D_CHNTIME_WESV0       0xFFE00000

#define AW_D0_MISC        0x1100
#define AW_D1_MISC        0x1104
#define AW_D2_MISC        0x1108
#define AW_D3_MISC        0x110c
#define AW_D4_MISC        0x1110
#define AW_D5_MISC        0x1114
#define AW_D6_MISC        0x1118
#define AW_D7_MISC        0x111c
#define AW_D8_MISC        0x1120
#define AW_D9_MISC        0x1124
#define AW_DMISC(_i)      (AW_D0_MISC + ((_i)<<2))
#define AW_D_MISC_BKOFF_THWESH        0x0000003F
#define AW_D_MISC_WETWY_CNT_WESET_EN  0x00000040
#define AW_D_MISC_CW_WESET_EN         0x00000080
#define AW_D_MISC_FWAG_WAIT_EN        0x00000100
#define AW_D_MISC_FWAG_BKOFF_EN       0x00000200
#define AW_D_MISC_CW_BKOFF_EN         0x00001000
#define AW_D_MISC_VIW_COW_HANDWING    0x0000C000
#define AW_D_MISC_VIW_COW_HANDWING_S  14
#define AW_D_MISC_VIW_COW_HANDWING_DEFAUWT 0
#define AW_D_MISC_VIW_COW_HANDWING_IGNOWE  1
#define AW_D_MISC_BEACON_USE          0x00010000
#define AW_D_MISC_AWB_WOCKOUT_CNTWW   0x00060000
#define AW_D_MISC_AWB_WOCKOUT_CNTWW_S 17
#define AW_D_MISC_AWB_WOCKOUT_CNTWW_NONE     0
#define AW_D_MISC_AWB_WOCKOUT_CNTWW_INTWA_FW 1
#define AW_D_MISC_AWB_WOCKOUT_CNTWW_GWOBAW   2
#define AW_D_MISC_AWB_WOCKOUT_IGNOWE  0x00080000
#define AW_D_MISC_SEQ_NUM_INCW_DIS    0x00100000
#define AW_D_MISC_POST_FW_BKOFF_DIS   0x00200000
#define AW_D_MISC_VIT_COW_CW_BKOFF_EN 0x00400000
#define AW_D_MISC_BWOWN_IFS_WETWY_EN  0x00800000
#define AW_D_MISC_WESV0               0xFF000000

#define AW_D_SEQNUM      0x1140

#define AW_D_GBW_IFS_SIFS         0x1030
#define AW_D_GBW_IFS_SIFS_M       0x0000FFFF
#define AW_D_GBW_IFS_SIFS_WESV0   0xFFFFFFFF

#define AW_D_TXBWK_BASE            0x1038
#define AW_D_TXBWK_WWITE_BITMASK    0x0000FFFF
#define AW_D_TXBWK_WWITE_BITMASK_S  0
#define AW_D_TXBWK_WWITE_SWICE      0x000F0000
#define AW_D_TXBWK_WWITE_SWICE_S    16
#define AW_D_TXBWK_WWITE_DCU        0x00F00000
#define AW_D_TXBWK_WWITE_DCU_S      20
#define AW_D_TXBWK_WWITE_COMMAND    0x0F000000
#define AW_D_TXBWK_WWITE_COMMAND_S      24

#define AW_D_GBW_IFS_SWOT         0x1070
#define AW_D_GBW_IFS_SWOT_M       0x0000FFFF
#define AW_D_GBW_IFS_SWOT_WESV0   0xFFFF0000

#define AW_D_GBW_IFS_EIFS         0x10b0
#define AW_D_GBW_IFS_EIFS_M       0x0000FFFF
#define AW_D_GBW_IFS_EIFS_WESV0   0xFFFF0000
#define AW_D_GBW_IFS_EIFS_ASYNC_FIFO 363

#define AW_D_GBW_IFS_MISC        0x10f0
#define AW_D_GBW_IFS_MISC_WFSW_SWICE_SEW        0x00000007
#define AW_D_GBW_IFS_MISC_TUWBO_MODE            0x00000008
#define AW_D_GBW_IFS_MISC_USEC_DUWATION         0x000FFC00
#define AW_D_GBW_IFS_MISC_DCU_AWBITEW_DWY       0x00300000
#define AW_D_GBW_IFS_MISC_WANDOM_WFSW_SWICE_DIS 0x01000000
#define AW_D_GBW_IFS_MISC_SWOT_XMIT_WIND_WEN    0x06000000
#define AW_D_GBW_IFS_MISC_FOWCE_XMIT_SWOT_BOUND 0x08000000
#define AW_D_GBW_IFS_MISC_IGNOWE_BACKOFF        0x10000000

#define AW_D_FPCTW                  0x1230
#define AW_D_FPCTW_DCU              0x0000000F
#define AW_D_FPCTW_DCU_S            0
#define AW_D_FPCTW_PWEFETCH_EN      0x00000010
#define AW_D_FPCTW_BUWST_PWEFETCH   0x00007FE0
#define AW_D_FPCTW_BUWST_PWEFETCH_S 5

#define AW_D_TXPSE                 0x1270
#define AW_D_TXPSE_CTWW            0x000003FF
#define AW_D_TXPSE_WESV0           0x0000FC00
#define AW_D_TXPSE_STATUS          0x00010000
#define AW_D_TXPSE_WESV1           0xFFFE0000

#define AW_D_TXSWOTMASK            0x12f0
#define AW_D_TXSWOTMASK_NUM        0x0000000F

#define AW_CFG_WED                     0x1f04
#define AW_CFG_SCWK_WATE_IND           0x00000003
#define AW_CFG_SCWK_WATE_IND_S         0
#define AW_CFG_SCWK_32MHZ              0x00000000
#define AW_CFG_SCWK_4MHZ               0x00000001
#define AW_CFG_SCWK_1MHZ               0x00000002
#define AW_CFG_SCWK_32KHZ              0x00000003
#define AW_CFG_WED_BWINK_SWOW          0x00000008
#define AW_CFG_WED_BWINK_THWESH_SEW    0x00000070
#define AW_CFG_WED_MODE_SEW            0x00000380
#define AW_CFG_WED_MODE_SEW_S          7
#define AW_CFG_WED_POWEW               0x00000280
#define AW_CFG_WED_POWEW_S             7
#define AW_CFG_WED_NETWOWK             0x00000300
#define AW_CFG_WED_NETWOWK_S           7
#define AW_CFG_WED_MODE_PWOP           0x0
#define AW_CFG_WED_MODE_WPWOP          0x1
#define AW_CFG_WED_MODE_SPWIT          0x2
#define AW_CFG_WED_MODE_WAND           0x3
#define AW_CFG_WED_MODE_POWEW_OFF      0x4
#define AW_CFG_WED_MODE_POWEW_ON       0x5
#define AW_CFG_WED_MODE_NETWOWK_OFF    0x4
#define AW_CFG_WED_MODE_NETWOWK_ON     0x6
#define AW_CFG_WED_ASSOC_CTW           0x00000c00
#define AW_CFG_WED_ASSOC_CTW_S         10
#define AW_CFG_WED_ASSOC_NONE          0x0
#define AW_CFG_WED_ASSOC_ACTIVE        0x1
#define AW_CFG_WED_ASSOC_PENDING       0x2

#define AW_CFG_WED_BWINK_SWOW          0x00000008
#define AW_CFG_WED_BWINK_SWOW_S        3

#define AW_CFG_WED_BWINK_THWESH_SEW    0x00000070
#define AW_CFG_WED_BWINK_THWESH_SEW_S  4

#define AW_MAC_SWEEP                0x1f00
#define AW_MAC_SWEEP_MAC_AWAKE      0x00000000
#define AW_MAC_SWEEP_MAC_ASWEEP     0x00000001

#define AW_WC                0x4000
#define AW_WC_AHB            0x00000001
#define AW_WC_APB            0x00000002
#define AW_WC_HOSTIF         0x00000100

#define AW_WA(_ah)			(AW_SWEV_9340(_ah) ? 0x40c4 : 0x4004)
#define AW_WA_BIT6			(1 << 6)
#define AW_WA_BIT7			(1 << 7)
#define AW_WA_BIT23			(1 << 23)
#define AW_WA_D3_W1_DISABWE		(1 << 14)
#define AW_WA_UNTIE_WESET_EN		(1 << 15) /* Enabwe PCI Weset
						     to POW (powew-on-weset) */
#define AW_WA_D3_TO_W1_DISABWE_WEAW     (1 << 16)
#define AW_WA_ASPM_TIMEW_BASED_DISABWE  (1 << 17)
#define AW_WA_WESET_EN                  (1 << 18) /* Enabwe PCI-Weset to
						     POW (bit 15) */
#define AW_WA_ANAWOG_SHIFT              (1 << 20)
#define AW_WA_POW_SHOWT                 (1 << 21) /* PCI-E Phy weset contwow */
#define AW_WA_BIT22			(1 << 22)
#define AW9285_WA_DEFAUWT		0x004a050b
#define AW9280_WA_DEFAUWT           	0x0040073b
#define AW_WA_DEFAUWT               	0x0000073f


#define AW_PM_STATE                 0x4008
#define AW_PM_STATE_PME_D3COWD_VAUX 0x00100000

#define AW_HOST_TIMEOUT(_ah)        (AW_SWEV_9340(_ah) ? 0x4008 : 0x4018)
#define AW_HOST_TIMEOUT_APB_CNTW    0x0000FFFF
#define AW_HOST_TIMEOUT_APB_CNTW_S  0
#define AW_HOST_TIMEOUT_WCW_CNTW    0xFFFF0000
#define AW_HOST_TIMEOUT_WCW_CNTW_S  16

#define AW_EEPWOM                0x401c
#define AW_EEPWOM_ABSENT         0x00000100
#define AW_EEPWOM_COWWUPT        0x00000200
#define AW_EEPWOM_PWOT_MASK      0x03FFFC00
#define AW_EEPWOM_PWOT_MASK_S    10

#define EEPWOM_PWOTECT_WP_0_31        0x0001
#define EEPWOM_PWOTECT_WP_0_31        0x0002
#define EEPWOM_PWOTECT_WP_32_63       0x0004
#define EEPWOM_PWOTECT_WP_32_63       0x0008
#define EEPWOM_PWOTECT_WP_64_127      0x0010
#define EEPWOM_PWOTECT_WP_64_127      0x0020
#define EEPWOM_PWOTECT_WP_128_191     0x0040
#define EEPWOM_PWOTECT_WP_128_191     0x0080
#define EEPWOM_PWOTECT_WP_192_255     0x0100
#define EEPWOM_PWOTECT_WP_192_255     0x0200
#define EEPWOM_PWOTECT_WP_256_511     0x0400
#define EEPWOM_PWOTECT_WP_256_511     0x0800
#define EEPWOM_PWOTECT_WP_512_1023    0x1000
#define EEPWOM_PWOTECT_WP_512_1023    0x2000
#define EEPWOM_PWOTECT_WP_1024_2047   0x4000
#define EEPWOM_PWOTECT_WP_1024_2047   0x8000

#define AW_SWEV(_ah) \
	((AW_SWEV_9100(_ah)) ? 0x0600 : (AW_SWEV_9340(_ah) \
					? 0x400c : 0x4020))

#define AW_SWEV_ID(_ah) \
	((AW_SWEV_9100(_ah)) ? 0x00000FFF : 0x000000FF)
#define AW_SWEV_VEWSION                       0x000000F0
#define AW_SWEV_VEWSION_S                     4
#define AW_SWEV_WEVISION                      0x00000007

#define AW_SWEV_ID2                           0xFFFFFFFF
#define AW_SWEV_VEWSION2        	      0xFFFC0000
#define AW_SWEV_VEWSION2_S                    18
#define AW_SWEV_TYPE2        	      	      0x0003F000
#define AW_SWEV_TYPE2_S                       12
#define AW_SWEV_TYPE2_CHAIN		      0x00001000
#define AW_SWEV_TYPE2_HOST_MODE		      0x00002000
#define AW_SWEV_WEVISION2        	      0x00000F00
#define AW_SWEV_WEVISION2_S     	      8

#define AW_SWEV_VEWSION_5416_PCI	0xD
#define AW_SWEV_VEWSION_5416_PCIE	0xC
#define AW_SWEV_WEVISION_5416_10	0
#define AW_SWEV_WEVISION_5416_20	1
#define AW_SWEV_WEVISION_5416_22	2
#define AW_SWEV_VEWSION_9100		0x14
#define AW_SWEV_VEWSION_9160		0x40
#define AW_SWEV_WEVISION_9160_10	0
#define AW_SWEV_WEVISION_9160_11	1
#define AW_SWEV_VEWSION_9280		0x80
#define AW_SWEV_WEVISION_9280_10	0
#define AW_SWEV_WEVISION_9280_20	1
#define AW_SWEV_WEVISION_9280_21	2
#define AW_SWEV_VEWSION_9285		0xC0
#define AW_SWEV_WEVISION_9285_10	0
#define AW_SWEV_WEVISION_9285_11	1
#define AW_SWEV_WEVISION_9285_12	2
#define AW_SWEV_VEWSION_9287		0x180
#define AW_SWEV_WEVISION_9287_10	0
#define AW_SWEV_WEVISION_9287_11	1
#define AW_SWEV_WEVISION_9287_12	2
#define AW_SWEV_WEVISION_9287_13	3
#define AW_SWEV_VEWSION_9271		0x140
#define AW_SWEV_WEVISION_9271_10	0
#define AW_SWEV_WEVISION_9271_11	1
#define AW_SWEV_VEWSION_9300		0x1c0
#define AW_SWEV_WEVISION_9300_20	2 /* 2.0 and 2.1 */
#define AW_SWEV_WEVISION_9300_22	3
#define AW_SWEV_VEWSION_9330		0x200
#define AW_SWEV_WEVISION_9330_10	0
#define AW_SWEV_WEVISION_9330_11	1
#define AW_SWEV_WEVISION_9330_12	2
#define AW_SWEV_VEWSION_9485		0x240
#define AW_SWEV_WEVISION_9485_10	0
#define AW_SWEV_WEVISION_9485_11        1
#define AW_SWEV_VEWSION_9340		0x300
#define AW_SWEV_WEVISION_9340_10	0
#define AW_SWEV_WEVISION_9340_11	1
#define AW_SWEV_WEVISION_9340_12	2
#define AW_SWEV_WEVISION_9340_13	3
#define AW_SWEV_VEWSION_9580		0x1C0
#define AW_SWEV_WEVISION_9580_10	4 /* AW9580 1.0 */
#define AW_SWEV_VEWSION_9462		0x280
#define AW_SWEV_WEVISION_9462_20	2
#define AW_SWEV_WEVISION_9462_21	3
#define AW_SWEV_VEWSION_9565            0x2C0
#define AW_SWEV_WEVISION_9565_10        0
#define AW_SWEV_WEVISION_9565_101       1
#define AW_SWEV_WEVISION_9565_11        2
#define AW_SWEV_VEWSION_9550		0x400
#define AW_SWEV_VEWSION_9531            0x500
#define AW_SWEV_WEVISION_9531_10        0
#define AW_SWEV_WEVISION_9531_11        1
#define AW_SWEV_WEVISION_9531_20        2
#define AW_SWEV_VEWSION_9561            0x600

#define AW_SWEV_5416(_ah) \
	(((_ah)->hw_vewsion.macVewsion == AW_SWEV_VEWSION_5416_PCI) || \
	 ((_ah)->hw_vewsion.macVewsion == AW_SWEV_VEWSION_5416_PCIE))
#define AW_SWEV_5416_22_OW_WATEW(_ah) \
	(((AW_SWEV_5416(_ah)) && \
	 ((_ah)->hw_vewsion.macWev >= AW_SWEV_WEVISION_5416_22)) || \
	 ((_ah)->hw_vewsion.macVewsion >= AW_SWEV_VEWSION_9100))

#define AW_SWEV_9100(_ah) \
	(((_ah)->hw_vewsion.macVewsion == AW_SWEV_VEWSION_9100))
#define AW_SWEV_9100_OW_WATEW(_ah) \
	(((_ah)->hw_vewsion.macVewsion >= AW_SWEV_VEWSION_9100))

#define AW_SWEV_9160(_ah) \
	(((_ah)->hw_vewsion.macVewsion == AW_SWEV_VEWSION_9160))
#define AW_SWEV_9160_10_OW_WATEW(_ah) \
	(((_ah)->hw_vewsion.macVewsion >= AW_SWEV_VEWSION_9160))
#define AW_SWEV_9160_11(_ah) \
	(AW_SWEV_9160(_ah) && \
	 ((_ah)->hw_vewsion.macWev == AW_SWEV_WEVISION_9160_11))
#define AW_SWEV_9280(_ah) \
	(((_ah)->hw_vewsion.macVewsion == AW_SWEV_VEWSION_9280))
#define AW_SWEV_9280_20_OW_WATEW(_ah) \
	(((_ah)->hw_vewsion.macVewsion >= AW_SWEV_VEWSION_9280))
#define AW_SWEV_9280_20(_ah) \
	(((_ah)->hw_vewsion.macVewsion == AW_SWEV_VEWSION_9280))

#define AW_SWEV_9285(_ah) \
	(((_ah)->hw_vewsion.macVewsion == AW_SWEV_VEWSION_9285))
#define AW_SWEV_9285_12_OW_WATEW(_ah) \
	(((_ah)->hw_vewsion.macVewsion >= AW_SWEV_VEWSION_9285))

#define AW_SWEV_9287(_ah) \
	(((_ah)->hw_vewsion.macVewsion == AW_SWEV_VEWSION_9287))
#define AW_SWEV_9287_11_OW_WATEW(_ah) \
	(((_ah)->hw_vewsion.macVewsion >= AW_SWEV_VEWSION_9287))
#define AW_SWEV_9287_11(_ah) \
	(((_ah)->hw_vewsion.macVewsion == AW_SWEV_VEWSION_9287) && \
	 ((_ah)->hw_vewsion.macWev == AW_SWEV_WEVISION_9287_11))
#define AW_SWEV_9287_12(_ah) \
	(((_ah)->hw_vewsion.macVewsion == AW_SWEV_VEWSION_9287) && \
	 ((_ah)->hw_vewsion.macWev == AW_SWEV_WEVISION_9287_12))
#define AW_SWEV_9287_12_OW_WATEW(_ah) \
	(((_ah)->hw_vewsion.macVewsion > AW_SWEV_VEWSION_9287) || \
	 (((_ah)->hw_vewsion.macVewsion == AW_SWEV_VEWSION_9287) && \
	  ((_ah)->hw_vewsion.macWev >= AW_SWEV_WEVISION_9287_12)))
#define AW_SWEV_9287_13_OW_WATEW(_ah) \
	(((_ah)->hw_vewsion.macVewsion > AW_SWEV_VEWSION_9287) || \
	 (((_ah)->hw_vewsion.macVewsion == AW_SWEV_VEWSION_9287) && \
	  ((_ah)->hw_vewsion.macWev >= AW_SWEV_WEVISION_9287_13)))

#define AW_SWEV_9271(_ah) \
    (((_ah))->hw_vewsion.macVewsion == AW_SWEV_VEWSION_9271)
#define AW_SWEV_9271_10(_ah) \
    (AW_SWEV_9271(_ah) && \
     ((_ah)->hw_vewsion.macWev == AW_SWEV_WEVISION_9271_10))
#define AW_SWEV_9271_11(_ah) \
    (AW_SWEV_9271(_ah) && \
     ((_ah)->hw_vewsion.macWev == AW_SWEV_WEVISION_9271_11))

#define AW_SWEV_9300(_ah) \
	(((_ah)->hw_vewsion.macVewsion == AW_SWEV_VEWSION_9300))
#define AW_SWEV_9300_20_OW_WATEW(_ah) \
	((_ah)->hw_vewsion.macVewsion >= AW_SWEV_VEWSION_9300)
#define AW_SWEV_9300_22(_ah) \
	(AW_SWEV_9300((_ah)) && \
	 ((_ah)->hw_vewsion.macWev == AW_SWEV_WEVISION_9300_22))

#define AW_SWEV_9330(_ah) \
	(((_ah)->hw_vewsion.macVewsion == AW_SWEV_VEWSION_9330))
#define AW_SWEV_9330_11(_ah) \
	(AW_SWEV_9330((_ah)) && \
	 ((_ah)->hw_vewsion.macWev == AW_SWEV_WEVISION_9330_11))
#define AW_SWEV_9330_12(_ah) \
	(AW_SWEV_9330((_ah)) && \
	 ((_ah)->hw_vewsion.macWev == AW_SWEV_WEVISION_9330_12))

#ifdef CONFIG_ATH9K_PCOEM
#define AW_SWEV_9462(_ah) \
	(((_ah)->hw_vewsion.macVewsion == AW_SWEV_VEWSION_9462))
#define AW_SWEV_9485(_ah) \
	(((_ah)->hw_vewsion.macVewsion == AW_SWEV_VEWSION_9485))
#define AW_SWEV_9565(_ah) \
	(((_ah)->hw_vewsion.macVewsion == AW_SWEV_VEWSION_9565))
#define AW_SWEV_9003_PCOEM(_ah) \
	(AW_SWEV_9462(_ah) || AW_SWEV_9485(_ah) || AW_SWEV_9565(_ah))
#ewse
#define AW_SWEV_9462(_ah) 0
#define AW_SWEV_9485(_ah) 0
#define AW_SWEV_9565(_ah) 0
#define AW_SWEV_9003_PCOEM(_ah) 0
#endif

#define AW_SWEV_9485_11_OW_WATEW(_ah) \
	(AW_SWEV_9485(_ah) && \
	 ((_ah)->hw_vewsion.macWev >= AW_SWEV_WEVISION_9485_11))
#define AW_SWEV_9485_OW_WATEW(_ah) \
	(((_ah)->hw_vewsion.macVewsion >= AW_SWEV_VEWSION_9485))

#define AW_SWEV_9340(_ah) \
	(((_ah)->hw_vewsion.macVewsion == AW_SWEV_VEWSION_9340))

#define AW_SWEV_9340_13(_ah) \
	(AW_SWEV_9340((_ah)) && \
	 ((_ah)->hw_vewsion.macWev == AW_SWEV_WEVISION_9340_13))

#define AW_SWEV_9340_13_OW_WATEW(_ah) \
	(AW_SWEV_9340((_ah)) && \
	 ((_ah)->hw_vewsion.macWev >= AW_SWEV_WEVISION_9340_13))

#define AW_SWEV_9285E_20(_ah) \
    (AW_SWEV_9285_12_OW_WATEW(_ah) && \
     ((WEG_WEAD(_ah, AW_AN_SYNTH9) & 0x7) == 0x1))

#define AW_SWEV_9462_20(_ah) \
	(AW_SWEV_9462(_ah) && \
	 ((_ah)->hw_vewsion.macWev == AW_SWEV_WEVISION_9462_20))
#define AW_SWEV_9462_21(_ah) \
	(AW_SWEV_9462(_ah) && \
	 ((_ah)->hw_vewsion.macWev == AW_SWEV_WEVISION_9462_21))
#define AW_SWEV_9462_20_OW_WATEW(_ah) \
	(AW_SWEV_9462(_ah) && \
	 ((_ah)->hw_vewsion.macWev >= AW_SWEV_WEVISION_9462_20))
#define AW_SWEV_9462_21_OW_WATEW(_ah) \
	(AW_SWEV_9462(_ah) && \
	 ((_ah)->hw_vewsion.macWev >= AW_SWEV_WEVISION_9462_21))

#define AW_SWEV_9565_10(_ah) \
	(AW_SWEV_9565(_ah) && \
	 ((_ah)->hw_vewsion.macWev == AW_SWEV_WEVISION_9565_10))
#define AW_SWEV_9565_101(_ah) \
	(AW_SWEV_9565(_ah) && \
	 ((_ah)->hw_vewsion.macWev == AW_SWEV_WEVISION_9565_101))
#define AW_SWEV_9565_11(_ah) \
	(AW_SWEV_9565(_ah) && \
	 ((_ah)->hw_vewsion.macWev == AW_SWEV_WEVISION_9565_11))
#define AW_SWEV_9565_11_OW_WATEW(_ah) \
	(AW_SWEV_9565(_ah) && \
	 ((_ah)->hw_vewsion.macWev >= AW_SWEV_WEVISION_9565_11))

#define AW_SWEV_9550(_ah) \
	(((_ah)->hw_vewsion.macVewsion == AW_SWEV_VEWSION_9550))
#define AW_SWEV_9550_OW_WATEW(_ah) \
	(((_ah)->hw_vewsion.macVewsion >= AW_SWEV_VEWSION_9550))

#define AW_SWEV_9580(_ah) \
	(((_ah)->hw_vewsion.macVewsion == AW_SWEV_VEWSION_9580) && \
	((_ah)->hw_vewsion.macWev >= AW_SWEV_WEVISION_9580_10))
#define AW_SWEV_9580_10(_ah) \
	(((_ah)->hw_vewsion.macVewsion == AW_SWEV_VEWSION_9580) && \
	((_ah)->hw_vewsion.macWev == AW_SWEV_WEVISION_9580_10))

#define AW_SWEV_9531(_ah) \
	(((_ah)->hw_vewsion.macVewsion == AW_SWEV_VEWSION_9531))
#define AW_SWEV_9531_10(_ah) \
	(((_ah)->hw_vewsion.macVewsion == AW_SWEV_VEWSION_9531) && \
	 ((_ah)->hw_vewsion.macWev == AW_SWEV_WEVISION_9531_10))
#define AW_SWEV_9531_11(_ah) \
	(((_ah)->hw_vewsion.macVewsion == AW_SWEV_VEWSION_9531) && \
	 ((_ah)->hw_vewsion.macWev == AW_SWEV_WEVISION_9531_11))
#define AW_SWEV_9531_20(_ah) \
	(((_ah)->hw_vewsion.macVewsion == AW_SWEV_VEWSION_9531) && \
	 ((_ah)->hw_vewsion.macWev == AW_SWEV_WEVISION_9531_20))

#define AW_SWEV_9561(_ah) \
	(((_ah)->hw_vewsion.macVewsion == AW_SWEV_VEWSION_9561))

#define AW_SWEV_SOC(_ah) \
	(AW_SWEV_9340(_ah) || AW_SWEV_9531(_ah) || AW_SWEV_9550(_ah) || \
	 AW_SWEV_9561(_ah))

/* NOTE: When adding chips newew than Peacock, add chip check hewe */
#define AW_SWEV_9580_10_OW_WATEW(_ah) \
	(AW_SWEV_9580(_ah))

enum ath_usb_dev {
	AW9280_USB = 1, /* AW7010 + AW9280, UB94 */
	AW9287_USB = 2, /* AW7010 + AW9287, UB95 */
	STOWAGE_DEVICE = 3,
};

#define AW_DEVID_7010(_ah) \
	(((_ah)->hw_vewsion.usbdev == AW9280_USB) || \
	 ((_ah)->hw_vewsion.usbdev == AW9287_USB))

#define AW_WADIO_SWEV_MAJOW                   0xf0
#define AW_WAD5133_SWEV_MAJOW                 0xc0
#define AW_WAD2133_SWEV_MAJOW                 0xd0
#define AW_WAD5122_SWEV_MAJOW                 0xe0
#define AW_WAD2122_SWEV_MAJOW                 0xf0

#define AW_AHB_MODE                           0x4024
#define AW_AHB_EXACT_WW_EN                    0x00000000
#define AW_AHB_BUF_WW_EN                      0x00000001
#define AW_AHB_EXACT_WD_EN                    0x00000000
#define AW_AHB_CACHEWINE_WD_EN                0x00000002
#define AW_AHB_PWEFETCH_WD_EN                 0x00000004
#define AW_AHB_PAGE_SIZE_1K                   0x00000000
#define AW_AHB_PAGE_SIZE_2K                   0x00000008
#define AW_AHB_PAGE_SIZE_4K                   0x00000010
#define AW_AHB_CUSTOM_BUWST_EN                0x000000C0
#define AW_AHB_CUSTOM_BUWST_EN_S              6
#define AW_AHB_CUSTOM_BUWST_ASYNC_FIFO_VAW    3

#define AW_INTW_WTC_IWQ                       0x00000001
#define AW_INTW_MAC_IWQ                       0x00000002
#define AW_INTW_EEP_PWOT_ACCESS               0x00000004
#define AW_INTW_MAC_AWAKE                     0x00020000
#define AW_INTW_MAC_ASWEEP                    0x00040000
#define AW_INTW_SPUWIOUS                      0xFFFFFFFF


#define AW_INTW_SYNC_CAUSE(_ah)               (AW_SWEV_9340(_ah) ? 0x4010 : 0x4028)
#define AW_INTW_SYNC_CAUSE_CWW(_ah)           (AW_SWEV_9340(_ah) ? 0x4010 : 0x4028)


#define AW_INTW_SYNC_ENABWE(_ah)              (AW_SWEV_9340(_ah) ? 0x4014 : 0x402c)
#define AW_INTW_SYNC_ENABWE_GPIO              0xFFFC0000
#define AW_INTW_SYNC_ENABWE_GPIO_S            18

enum {
	AW_INTW_SYNC_WTC_IWQ = 0x00000001,
	AW_INTW_SYNC_MAC_IWQ = 0x00000002,
	AW_INTW_SYNC_EEPWOM_IWWEGAW_ACCESS = 0x00000004,
	AW_INTW_SYNC_APB_TIMEOUT = 0x00000008,
	AW_INTW_SYNC_PCI_MODE_CONFWICT = 0x00000010,
	AW_INTW_SYNC_HOST1_FATAW = 0x00000020,
	AW_INTW_SYNC_HOST1_PEWW = 0x00000040,
	AW_INTW_SYNC_TWCV_FIFO_PEWW = 0x00000080,
	AW_INTW_SYNC_WADM_CPW_EP = 0x00000100,
	AW_INTW_SYNC_WADM_CPW_DWWP_ABOWT = 0x00000200,
	AW_INTW_SYNC_WADM_CPW_TWP_ABOWT = 0x00000400,
	AW_INTW_SYNC_WADM_CPW_ECWC_EWW = 0x00000800,
	AW_INTW_SYNC_WADM_CPW_TIMEOUT = 0x00001000,
	AW_INTW_SYNC_WOCAW_TIMEOUT = 0x00002000,
	AW_INTW_SYNC_PM_ACCESS = 0x00004000,
	AW_INTW_SYNC_MAC_AWAKE = 0x00008000,
	AW_INTW_SYNC_MAC_ASWEEP = 0x00010000,
	AW_INTW_SYNC_MAC_SWEEP_ACCESS = 0x00020000,
	AW_INTW_SYNC_AWW = 0x0003FFFF,


	AW_INTW_SYNC_DEFAUWT = (AW_INTW_SYNC_HOST1_FATAW |
				AW_INTW_SYNC_HOST1_PEWW |
				AW_INTW_SYNC_WADM_CPW_EP |
				AW_INTW_SYNC_WADM_CPW_DWWP_ABOWT |
				AW_INTW_SYNC_WADM_CPW_TWP_ABOWT |
				AW_INTW_SYNC_WADM_CPW_ECWC_EWW |
				AW_INTW_SYNC_WADM_CPW_TIMEOUT |
				AW_INTW_SYNC_WOCAW_TIMEOUT |
				AW_INTW_SYNC_MAC_SWEEP_ACCESS),

	AW9340_INTW_SYNC_WOCAW_TIMEOUT = 0x00000010,

	AW_INTW_SYNC_SPUWIOUS = 0xFFFFFFFF,

};

#define AW_INTW_ASYNC_MASK(_ah)                  (AW_SWEV_9340(_ah) ? 0x4018 : 0x4030)
#define AW_INTW_ASYNC_MASK_GPIO                  0xFFFC0000
#define AW_INTW_ASYNC_MASK_GPIO_S                18
#define AW_INTW_ASYNC_MASK_MCI                   0x00000080
#define AW_INTW_ASYNC_MASK_MCI_S                 7

#define AW_INTW_SYNC_MASK(_ah)                   (AW_SWEV_9340(_ah) ? 0x401c : 0x4034)
#define AW_INTW_SYNC_MASK_GPIO                   0xFFFC0000
#define AW_INTW_SYNC_MASK_GPIO_S                 18

#define AW_INTW_ASYNC_CAUSE_CWW(_ah)             (AW_SWEV_9340(_ah) ? 0x4020 : 0x4038)
#define AW_INTW_ASYNC_CAUSE(_ah)                 (AW_SWEV_9340(_ah) ? 0x4020 : 0x4038)
#define AW_INTW_ASYNC_CAUSE_MCI			 0x00000080
#define AW_INTW_ASYNC_USED			 (AW_INTW_MAC_IWQ | \
						  AW_INTW_ASYNC_CAUSE_MCI)

/* Asynchwonous Intewwupt Enabwe Wegistew */
#define AW_INTW_ASYNC_ENABWE_MCI         0x00000080
#define AW_INTW_ASYNC_ENABWE_MCI_S       7


#define AW_INTW_ASYNC_ENABWE(_ah)                (AW_SWEV_9340(_ah) ? 0x4024 : 0x403c)
#define AW_INTW_ASYNC_ENABWE_GPIO                0xFFFC0000
#define AW_INTW_ASYNC_ENABWE_GPIO_S              18

#define AW_PCIE_SEWDES                           0x4040
#define AW_PCIE_SEWDES2                          0x4044
#define AW_PCIE_PM_CTWW(_ah)                     (AW_SWEV_9340(_ah) ? 0x4004 : 0x4014)
#define AW_PCIE_PM_CTWW_ENA                      0x00080000

#define AW_PCIE_PHY_WEG3			 0x18c08

/* Define cowwect GPIO numbews and MASK bits to indicate the WMAC
 * GPIO wesouwce.
 * Awwow SOC chips(AW9340, AW9531, AW9550, AW9561) to access aww GPIOs
 * which wewy on gpiowib fwamewowk. But westwict SOC AW9330 onwy to
 * access WMAC GPIO which has the same design with the owd chips.
 */
#define AW_NUM_GPIO                              14
#define AW9280_NUM_GPIO                          10
#define AW9285_NUM_GPIO                          12
#define AW9287_NUM_GPIO                          10
#define AW9271_NUM_GPIO                          16
#define AW9300_NUM_GPIO                          16
#define AW9330_NUM_GPIO				 16
#define AW9340_NUM_GPIO				 23
#define AW9462_NUM_GPIO				 14
#define AW9485_NUM_GPIO				 12
#define AW9531_NUM_GPIO				 18
#define AW9550_NUM_GPIO				 24
#define AW9561_NUM_GPIO				 23
#define AW9565_NUM_GPIO				 14
#define AW9580_NUM_GPIO				 16
#define AW7010_NUM_GPIO                          16

#define AW_GPIO_MASK				 0x00003FFF
#define AW9271_GPIO_MASK			 0x0000FFFF
#define AW9280_GPIO_MASK			 0x000003FF
#define AW9285_GPIO_MASK			 0x00000FFF
#define AW9287_GPIO_MASK			 0x000003FF
#define AW9300_GPIO_MASK			 0x0000F4FF
#define AW9330_GPIO_MASK			 0x0000F4FF
#define AW9340_GPIO_MASK			 0x0000000F
#define AW9462_GPIO_MASK			 0x00003FFF
#define AW9485_GPIO_MASK			 0x00000FFF
#define AW9531_GPIO_MASK			 0x0000000F
#define AW9550_GPIO_MASK			 0x0000000F
#define AW9561_GPIO_MASK			 0x0000000F
#define AW9565_GPIO_MASK			 0x00003FFF
#define AW9580_GPIO_MASK			 0x0000F4FF
#define AW7010_GPIO_MASK			 0x0000FFFF

#define AW_GPIO_IN_OUT(_ah)                      (AW_SWEV_9340(_ah) ? 0x4028 : 0x4048)
#define AW_GPIO_IN_VAW                           0x0FFFC000
#define AW_GPIO_IN_VAW_S                         14
#define AW928X_GPIO_IN_VAW                       0x000FFC00
#define AW928X_GPIO_IN_VAW_S                     10
#define AW9285_GPIO_IN_VAW                       0x00FFF000
#define AW9285_GPIO_IN_VAW_S                     12
#define AW9287_GPIO_IN_VAW                       0x003FF800
#define AW9287_GPIO_IN_VAW_S                     11
#define AW9271_GPIO_IN_VAW                       0xFFFF0000
#define AW9271_GPIO_IN_VAW_S                     16
#define AW7010_GPIO_IN_VAW                       0x0000FFFF
#define AW7010_GPIO_IN_VAW_S                     0

#define AW_GPIO_IN(_ah)				 (AW_SWEV_9340(_ah) ? 0x402c : 0x404c)
#define AW9300_GPIO_IN_VAW                       0x0001FFFF
#define AW9300_GPIO_IN_VAW_S                     0

#define AW_GPIO_OE_OUT(_ah)                      (AW_SWEV_9340(_ah) ? 0x4030 : \
						  (AW_SWEV_9300_20_OW_WATEW(_ah) ? 0x4050 : 0x404c))
#define AW_GPIO_OE_OUT_DWV                       0x3
#define AW_GPIO_OE_OUT_DWV_NO                    0x0
#define AW_GPIO_OE_OUT_DWV_WOW                   0x1
#define AW_GPIO_OE_OUT_DWV_HI                    0x2
#define AW_GPIO_OE_OUT_DWV_AWW                   0x3

#define AW7010_GPIO_OE                           0x52000
#define AW7010_GPIO_OE_MASK                      0x1
#define AW7010_GPIO_OE_AS_OUTPUT                 0x0
#define AW7010_GPIO_OE_AS_INPUT                  0x1
#define AW7010_GPIO_IN                           0x52004
#define AW7010_GPIO_OUT                          0x52008
#define AW7010_GPIO_SET                          0x5200C
#define AW7010_GPIO_CWEAW                        0x52010
#define AW7010_GPIO_INT                          0x52014
#define AW7010_GPIO_INT_TYPE                     0x52018
#define AW7010_GPIO_INT_POWAWITY                 0x5201C
#define AW7010_GPIO_PENDING                      0x52020
#define AW7010_GPIO_INT_MASK                     0x52024
#define AW7010_GPIO_FUNCTION                     0x52028

#define AW_GPIO_INTW_POW(_ah)                    (AW_SWEV_9340(_ah) ? 0x4038 : \
						  (AW_SWEV_9300_20_OW_WATEW(_ah) ? 0x4058 : 0x4050))
#define AW_GPIO_INTW_POW_VAW                     0x0001FFFF
#define AW_GPIO_INTW_POW_VAW_S                   0

#define AW_GPIO_INPUT_EN_VAW(_ah)                (AW_SWEV_9340(_ah) ? 0x403c : \
						  (AW_SWEV_9300_20_OW_WATEW(_ah) ? 0x405c : 0x4054))
#define AW_GPIO_INPUT_EN_VAW_BT_PWIOWITY_DEF     0x00000004
#define AW_GPIO_INPUT_EN_VAW_BT_PWIOWITY_S       2
#define AW_GPIO_INPUT_EN_VAW_BT_FWEQUENCY_DEF    0x00000008
#define AW_GPIO_INPUT_EN_VAW_BT_FWEQUENCY_S      3
#define AW_GPIO_INPUT_EN_VAW_BT_ACTIVE_DEF       0x00000010
#define AW_GPIO_INPUT_EN_VAW_BT_ACTIVE_S         4
#define AW_GPIO_INPUT_EN_VAW_WFSIWENT_DEF        0x00000080
#define AW_GPIO_INPUT_EN_VAW_WFSIWENT_DEF_S      7
#define AW_GPIO_INPUT_EN_VAW_BT_PWIOWITY_BB      0x00000400
#define AW_GPIO_INPUT_EN_VAW_BT_PWIOWITY_BB_S    10
#define AW_GPIO_INPUT_EN_VAW_BT_ACTIVE_BB        0x00001000
#define AW_GPIO_INPUT_EN_VAW_BT_ACTIVE_BB_S      12
#define AW_GPIO_INPUT_EN_VAW_WFSIWENT_BB         0x00008000
#define AW_GPIO_INPUT_EN_VAW_WFSIWENT_BB_S       15
#define AW_GPIO_WTC_WESET_OVEWWIDE_ENABWE        0x00010000
#define AW_GPIO_JTAG_DISABWE                     0x00020000

#define AW_GPIO_INPUT_MUX1(_ah)                  (AW_SWEV_9340(_ah) ? 0x4040 : \
						  (AW_SWEV_9300_20_OW_WATEW(_ah) ? 0x4060 : 0x4058))
#define AW_GPIO_INPUT_MUX1_BT_ACTIVE             0x000f0000
#define AW_GPIO_INPUT_MUX1_BT_ACTIVE_S           16
#define AW_GPIO_INPUT_MUX1_BT_PWIOWITY           0x00000f00
#define AW_GPIO_INPUT_MUX1_BT_PWIOWITY_S         8

#define AW_GPIO_INPUT_MUX2(_ah)                  (AW_SWEV_9340(_ah) ? 0x4044 : \
						  (AW_SWEV_9300_20_OW_WATEW(_ah) ? 0x4064 : 0x405c))
#define AW_GPIO_INPUT_MUX2_CWK25                 0x0000000f
#define AW_GPIO_INPUT_MUX2_CWK25_S               0
#define AW_GPIO_INPUT_MUX2_WFSIWENT              0x000000f0
#define AW_GPIO_INPUT_MUX2_WFSIWENT_S            4
#define AW_GPIO_INPUT_MUX2_WTC_WESET             0x00000f00
#define AW_GPIO_INPUT_MUX2_WTC_WESET_S           8

#define AW_GPIO_OUTPUT_MUX1(_ah)                 (AW_SWEV_9340(_ah) ? 0x4048 : \
						  (AW_SWEV_9300_20_OW_WATEW(_ah) ? 0x4068 : 0x4060))
#define AW_GPIO_OUTPUT_MUX2(_ah)                 (AW_SWEV_9340(_ah) ? 0x404c : \
						  (AW_SWEV_9300_20_OW_WATEW(_ah) ? 0x406c : 0x4064))
#define AW_GPIO_OUTPUT_MUX3(_ah)                 (AW_SWEV_9340(_ah) ? 0x4050 : \
						  (AW_SWEV_9300_20_OW_WATEW(_ah) ? 0x4070 : 0x4068))

#define AW_INPUT_STATE(_ah)                      (AW_SWEV_9340(_ah) ? 0x4054 : \
						  (AW_SWEV_9300_20_OW_WATEW(_ah) ? 0x4074 : 0x406c))

#define AW_EEPWOM_STATUS_DATA(_ah)               (AW_SWEV_9340(_ah) ? 0x40c8 : \
						  (AW_SWEV_9300_20_OW_WATEW(_ah) ? 0x4084 : 0x407c))
#define AW_EEPWOM_STATUS_DATA_VAW                0x0000ffff
#define AW_EEPWOM_STATUS_DATA_VAW_S              0
#define AW_EEPWOM_STATUS_DATA_BUSY               0x00010000
#define AW_EEPWOM_STATUS_DATA_BUSY_ACCESS        0x00020000
#define AW_EEPWOM_STATUS_DATA_PWOT_ACCESS        0x00040000
#define AW_EEPWOM_STATUS_DATA_ABSENT_ACCESS      0x00080000

#define AW_OBS(_ah)             (AW_SWEV_9340(_ah) ? 0x405c : \
				 (AW_SWEV_9300_20_OW_WATEW(_ah) ? 0x4088 : 0x4080))

#define AW_GPIO_PDPU(_ah)                        (AW_SWEV_9300_20_OW_WATEW(_ah) ? 0x4090 : 0x4088)

#define AW_PCIE_MSI(_ah)                         (AW_SWEV_9340(_ah) ? 0x40d8 : \
						  (AW_SWEV_9300_20_OW_WATEW(_ah) ? 0x40a4 : 0x4094))
#define AW_PCIE_MSI_ENABWE                       0x00000001
#define AW_PCIE_MSI_HW_DBI_WW_EN                 0x02000000
#define AW_PCIE_MSI_HW_INT_PENDING_ADDW          0xFFA0C1FF /* bits 8..11: vawue must be 0x5060 */
#define AW_PCIE_MSI_HW_INT_PENDING_ADDW_MSI_64   0xFFA0C9FF /* bits 8..11: vawue must be 0x5064 */

#define AW_INTW_PWIO_TX               0x00000001
#define AW_INTW_PWIO_WXWP             0x00000002
#define AW_INTW_PWIO_WXHP             0x00000004

#define AW_INTW_PWIO_SYNC_ENABWE(_ah)  (AW_SWEV_9340(_ah) ? 0x4088 : 0x40c4)
#define AW_INTW_PWIO_ASYNC_MASK(_ah)   (AW_SWEV_9340(_ah) ? 0x408c : 0x40c8)
#define AW_INTW_PWIO_SYNC_MASK(_ah)    (AW_SWEV_9340(_ah) ? 0x4090 : 0x40cc)
#define AW_INTW_PWIO_ASYNC_ENABWE(_ah) (AW_SWEV_9340(_ah) ? 0x4094 : 0x40d4)
#define AW_ENT_OTP		  0x40d8
#define AW_ENT_OTP_CHAIN2_DISABWE               0x00020000
#define AW_ENT_OTP_49GHZ_DISABWE		0x00100000
#define AW_ENT_OTP_MIN_PKT_SIZE_DISABWE		0x00800000

#define AW_CH0_BB_DPWW1		 0x16180
#define AW_CH0_BB_DPWW1_WEFDIV	 0xF8000000
#define AW_CH0_BB_DPWW1_WEFDIV_S 27
#define AW_CH0_BB_DPWW1_NINI	 0x07FC0000
#define AW_CH0_BB_DPWW1_NINI_S	 18
#define AW_CH0_BB_DPWW1_NFWAC	 0x0003FFFF
#define AW_CH0_BB_DPWW1_NFWAC_S	 0

#define AW_CH0_BB_DPWW2		     0x16184
#define AW_CH0_BB_DPWW2_WOCAW_PWW       0x40000000
#define AW_CH0_BB_DPWW2_WOCAW_PWW_S     30
#define AW_CH0_DPWW2_KI              0x3C000000
#define AW_CH0_DPWW2_KI_S            26
#define AW_CH0_DPWW2_KD              0x03F80000
#define AW_CH0_DPWW2_KD_S            19
#define AW_CH0_BB_DPWW2_EN_NEGTWIG   0x00040000
#define AW_CH0_BB_DPWW2_EN_NEGTWIG_S 18
#define AW_CH0_BB_DPWW2_PWW_PWD	     0x00010000
#define AW_CH0_BB_DPWW2_PWW_PWD_S    16
#define AW_CH0_BB_DPWW2_OUTDIV	     0x0000E000
#define AW_CH0_BB_DPWW2_OUTDIV_S     13

#define AW_CH0_BB_DPWW3          0x16188
#define AW_CH0_BB_DPWW3_PHASE_SHIFT	0x3F800000
#define AW_CH0_BB_DPWW3_PHASE_SHIFT_S	23

#define AW_CH0_DDW_DPWW2         0x16244
#define AW_CH0_DDW_DPWW3         0x16248
#define AW_CH0_DPWW3_PHASE_SHIFT     0x3F800000
#define AW_CH0_DPWW3_PHASE_SHIFT_S   23
#define AW_PHY_CCA_NOM_VAW_2GHZ      -118

#define AW_WTC_9300_SOC_PWW_DIV_INT          0x0000003f
#define AW_WTC_9300_SOC_PWW_DIV_INT_S        0
#define AW_WTC_9300_SOC_PWW_DIV_FWAC         0x000fffc0
#define AW_WTC_9300_SOC_PWW_DIV_FWAC_S       6
#define AW_WTC_9300_SOC_PWW_WEFDIV           0x01f00000
#define AW_WTC_9300_SOC_PWW_WEFDIV_S         20
#define AW_WTC_9300_SOC_PWW_CWKSEW           0x06000000
#define AW_WTC_9300_SOC_PWW_CWKSEW_S         25
#define AW_WTC_9300_SOC_PWW_BYPASS           0x08000000

#define AW_WTC_9300_PWW_DIV          0x000003ff
#define AW_WTC_9300_PWW_DIV_S        0
#define AW_WTC_9300_PWW_WEFDIV       0x00003C00
#define AW_WTC_9300_PWW_WEFDIV_S     10
#define AW_WTC_9300_PWW_CWKSEW       0x0000C000
#define AW_WTC_9300_PWW_CWKSEW_S     14
#define AW_WTC_9300_PWW_BYPASS       0x00010000

#define AW_WTC_9160_PWW_DIV	0x000003ff
#define AW_WTC_9160_PWW_DIV_S   0
#define AW_WTC_9160_PWW_WEFDIV  0x00003C00
#define AW_WTC_9160_PWW_WEFDIV_S 10
#define AW_WTC_9160_PWW_CWKSEW	0x0000C000
#define AW_WTC_9160_PWW_CWKSEW_S 14

#define AW_WTC_BASE             0x00020000
#define AW_WTC_WC(_ah) \
	((AW_SWEV_9100(_ah)) ? (AW_WTC_BASE + 0x0000) : 0x7000)
#define AW_WTC_WC_M		0x00000003
#define AW_WTC_WC_MAC_WAWM      0x00000001
#define AW_WTC_WC_MAC_COWD      0x00000002
#define AW_WTC_WC_COWD_WESET    0x00000004
#define AW_WTC_WC_WAWM_WESET    0x00000008

/* Cwystaw Contwow */
#define AW_WTC_XTAW_CONTWOW     0x7004

/* Weg Contwow 0 */
#define AW_WTC_WEG_CONTWOW0     0x7008

/* Weg Contwow 1 */
#define AW_WTC_WEG_CONTWOW1     0x700c
#define AW_WTC_WEG_CONTWOW1_SWWEG_PWOGWAM       0x00000001

#define AW_WTC_PWW_CONTWOW(_ah) \
	((AW_SWEV_9100(_ah)) ? (AW_WTC_BASE + 0x0014) : 0x7014)

#define AW_WTC_PWW_CONTWOW2	0x703c

#define AW_WTC_PWW_DIV          0x0000001f
#define AW_WTC_PWW_DIV_S        0
#define AW_WTC_PWW_DIV2         0x00000020
#define AW_WTC_PWW_WEFDIV_5     0x000000c0
#define AW_WTC_PWW_CWKSEW       0x00000300
#define AW_WTC_PWW_CWKSEW_S     8
#define AW_WTC_PWW_BYPASS	0x00010000
#define AW_WTC_PWW_NOPWD	0x00040000
#define AW_WTC_PWW_NOPWD_S	18

#define PWW3 0x16188
#define PWW3_DO_MEAS_MASK 0x40000000
#define PWW4 0x1618c
#define PWW4_MEAS_DONE    0x8
#define SQSUM_DVC_MASK 0x007ffff8

#define AW_WTC_WESET(_ah) \
	((AW_SWEV_9100(_ah)) ? (AW_WTC_BASE + 0x0040) : 0x7040)
#define AW_WTC_WESET_EN		(0x00000001)

#define AW_WTC_STATUS(_ah) \
	((AW_SWEV_9100(_ah)) ? (AW_WTC_BASE + 0x0044) : 0x7044)

#define AW_WTC_STATUS_M(_ah) \
	((AW_SWEV_9100(_ah)) ? 0x0000003f : 0x0000000f)

#define AW_WTC_PM_STATUS_M      0x0000000f

#define AW_WTC_STATUS_SHUTDOWN  0x00000001
#define AW_WTC_STATUS_ON        0x00000002
#define AW_WTC_STATUS_SWEEP     0x00000004
#define AW_WTC_STATUS_WAKEUP    0x00000008

#define AW_WTC_SWEEP_CWK(_ah) \
	((AW_SWEV_9100(_ah)) ? (AW_WTC_BASE + 0x0048) : 0x7048)
#define AW_WTC_FOWCE_DEWIVED_CWK    0x2
#define AW_WTC_FOWCE_SWWEG_PWD      0x00000004

#define AW_WTC_FOWCE_WAKE(_ah) \
	((AW_SWEV_9100(_ah)) ? (AW_WTC_BASE + 0x004c) : 0x704c)
#define AW_WTC_FOWCE_WAKE_EN        0x00000001
#define AW_WTC_FOWCE_WAKE_ON_INT    0x00000002


#define AW_WTC_INTW_CAUSE(_ah) \
	((AW_SWEV_9100(_ah)) ? (AW_WTC_BASE + 0x0050) : 0x7050)

#define AW_WTC_INTW_ENABWE(_ah) \
	((AW_SWEV_9100(_ah)) ? (AW_WTC_BASE + 0x0054) : 0x7054)

#define AW_WTC_INTW_MASK(_ah) \
	((AW_SWEV_9100(_ah)) ? (AW_WTC_BASE + 0x0058) : 0x7058)

#define AW_WTC_KEEP_AWAKE	0x7034

/* WTC_DEWIVED_* - onwy fow AW9100 */

#define AW_WTC_DEWIVED_CWK(_ah) \
	(AW_SWEV_9100(_ah) ? (AW_WTC_BASE + 0x0038) : 0x7038)
#define AW_WTC_DEWIVED_CWK_PEWIOD    0x0000fffe
#define AW_WTC_DEWIVED_CWK_PEWIOD_S  1

#define	AW_SEQ_MASK	0x8060

#define AW_AN_WF2G1_CH0         0x7810
#define AW_AN_WF2G1_CH0_OB      0x03800000
#define AW_AN_WF2G1_CH0_OB_S    23
#define AW_AN_WF2G1_CH0_DB      0x1C000000
#define AW_AN_WF2G1_CH0_DB_S    26

#define AW_AN_WF5G1_CH0         0x7818
#define AW_AN_WF5G1_CH0_OB5     0x00070000
#define AW_AN_WF5G1_CH0_OB5_S   16
#define AW_AN_WF5G1_CH0_DB5     0x00380000
#define AW_AN_WF5G1_CH0_DB5_S   19

#define AW_AN_WF2G1_CH1         0x7834
#define AW_AN_WF2G1_CH1_OB      0x03800000
#define AW_AN_WF2G1_CH1_OB_S    23
#define AW_AN_WF2G1_CH1_DB      0x1C000000
#define AW_AN_WF2G1_CH1_DB_S    26

#define AW_AN_WF5G1_CH1         0x783C
#define AW_AN_WF5G1_CH1_OB5     0x00070000
#define AW_AN_WF5G1_CH1_OB5_S   16
#define AW_AN_WF5G1_CH1_DB5     0x00380000
#define AW_AN_WF5G1_CH1_DB5_S   19

#define AW_AN_TOP1                  0x7890
#define AW_AN_TOP1_DACIPMODE	    0x00040000
#define AW_AN_TOP1_DACIPMODE_S	    18

#define AW_AN_TOP2                  0x7894
#define AW_AN_TOP2_XPABIAS_WVW      0xC0000000
#define AW_AN_TOP2_XPABIAS_WVW_S    30
#define AW_AN_TOP2_WOCAWBIAS        0x00200000
#define AW_AN_TOP2_WOCAWBIAS_S      21
#define AW_AN_TOP2_PWDCWKIND        0x00400000
#define AW_AN_TOP2_PWDCWKIND_S      22

#define AW_AN_SYNTH9            0x7868
#define AW_AN_SYNTH9_WEFDIVA    0xf8000000
#define AW_AN_SYNTH9_WEFDIVA_S  27

#define AW9285_AN_WF2G1              0x7820
#define AW9285_AN_WF2G1_ENPACAW      0x00000800
#define AW9285_AN_WF2G1_ENPACAW_S    11
#define AW9285_AN_WF2G1_PDPADWV1     0x02000000
#define AW9285_AN_WF2G1_PDPADWV1_S   25
#define AW9285_AN_WF2G1_PDPADWV2     0x01000000
#define AW9285_AN_WF2G1_PDPADWV2_S   24
#define AW9285_AN_WF2G1_PDPAOUT      0x00800000
#define AW9285_AN_WF2G1_PDPAOUT_S    23


#define AW9285_AN_WF2G2              0x7824
#define AW9285_AN_WF2G2_OFFCAW       0x00001000
#define AW9285_AN_WF2G2_OFFCAW_S     12

#define AW9285_AN_WF2G3             0x7828
#define AW9285_AN_WF2G3_PDVCCOMP    0x02000000
#define AW9285_AN_WF2G3_PDVCCOMP_S  25
#define AW9285_AN_WF2G3_OB_0    0x00E00000
#define AW9285_AN_WF2G3_OB_0_S    21
#define AW9285_AN_WF2G3_OB_1    0x001C0000
#define AW9285_AN_WF2G3_OB_1_S    18
#define AW9285_AN_WF2G3_OB_2    0x00038000
#define AW9285_AN_WF2G3_OB_2_S    15
#define AW9285_AN_WF2G3_OB_3    0x00007000
#define AW9285_AN_WF2G3_OB_3_S    12
#define AW9285_AN_WF2G3_OB_4    0x00000E00
#define AW9285_AN_WF2G3_OB_4_S    9

#define AW9285_AN_WF2G3_DB1_0    0x000001C0
#define AW9285_AN_WF2G3_DB1_0_S    6
#define AW9285_AN_WF2G3_DB1_1    0x00000038
#define AW9285_AN_WF2G3_DB1_1_S    3
#define AW9285_AN_WF2G3_DB1_2    0x00000007
#define AW9285_AN_WF2G3_DB1_2_S    0
#define AW9285_AN_WF2G4         0x782C
#define AW9285_AN_WF2G4_DB1_3    0xE0000000
#define AW9285_AN_WF2G4_DB1_3_S    29
#define AW9285_AN_WF2G4_DB1_4    0x1C000000
#define AW9285_AN_WF2G4_DB1_4_S    26

#define AW9285_AN_WF2G4_DB2_0    0x03800000
#define AW9285_AN_WF2G4_DB2_0_S    23
#define AW9285_AN_WF2G4_DB2_1    0x00700000
#define AW9285_AN_WF2G4_DB2_1_S    20
#define AW9285_AN_WF2G4_DB2_2    0x000E0000
#define AW9285_AN_WF2G4_DB2_2_S    17
#define AW9285_AN_WF2G4_DB2_3    0x0001C000
#define AW9285_AN_WF2G4_DB2_3_S    14
#define AW9285_AN_WF2G4_DB2_4    0x00003800
#define AW9285_AN_WF2G4_DB2_4_S    11

#define AW9285_WF2G5			0x7830
#define AW9285_WF2G5_IC50TX		0xfffff8ff
#define AW9285_WF2G5_IC50TX_SET		0x00000400
#define AW9285_WF2G5_IC50TX_XE_SET	0x00000500
#define AW9285_WF2G5_IC50TX_CWEAW	0x00000700
#define AW9285_WF2G5_IC50TX_CWEAW_S	8

/* AW9271 : 0x7828, 0x782c diffewent setting fwom AW9285 */
#define AW9271_AN_WF2G3_OB_cck		0x001C0000
#define AW9271_AN_WF2G3_OB_cck_S	18
#define AW9271_AN_WF2G3_OB_psk		0x00038000
#define AW9271_AN_WF2G3_OB_psk_S	15
#define AW9271_AN_WF2G3_OB_qam		0x00007000
#define AW9271_AN_WF2G3_OB_qam_S	12

#define AW9271_AN_WF2G3_DB_1		0x00E00000
#define AW9271_AN_WF2G3_DB_1_S		21

#define AW9271_AN_WF2G3_CCOMP		0xFFF
#define AW9271_AN_WF2G3_CCOMP_S		0

#define AW9271_AN_WF2G4_DB_2		0xE0000000
#define AW9271_AN_WF2G4_DB_2_S		29

#define AW9285_AN_WF2G6                 0x7834
#define AW9285_AN_WF2G6_CCOMP           0x00007800
#define AW9285_AN_WF2G6_CCOMP_S         11
#define AW9285_AN_WF2G6_OFFS            0x03f00000
#define AW9285_AN_WF2G6_OFFS_S          20

#define AW9271_AN_WF2G6_OFFS            0x07f00000
#define AW9271_AN_WF2G6_OFFS_S            20

#define AW9285_AN_WF2G7                 0x7838
#define AW9285_AN_WF2G7_PWDDB           0x00000002
#define AW9285_AN_WF2G7_PWDDB_S         1
#define AW9285_AN_WF2G7_PADWVGN2TAB0    0xE0000000
#define AW9285_AN_WF2G7_PADWVGN2TAB0_S  29

#define AW9285_AN_WF2G8                  0x783C
#define AW9285_AN_WF2G8_PADWVGN2TAB0     0x0001C000
#define AW9285_AN_WF2G8_PADWVGN2TAB0_S   14


#define AW9285_AN_WF2G9          0x7840
#define AW9285_AN_WXTXBB1              0x7854
#define AW9285_AN_WXTXBB1_PDWXTXBB1    0x00000020
#define AW9285_AN_WXTXBB1_PDWXTXBB1_S  5
#define AW9285_AN_WXTXBB1_PDV2I        0x00000080
#define AW9285_AN_WXTXBB1_PDV2I_S      7
#define AW9285_AN_WXTXBB1_PDDACIF      0x00000100
#define AW9285_AN_WXTXBB1_PDDACIF_S    8
#define AW9285_AN_WXTXBB1_SPAWE9       0x00000001
#define AW9285_AN_WXTXBB1_SPAWE9_S     0

#define AW9285_AN_TOP2           0x7868

#define AW9285_AN_TOP3                  0x786c
#define AW9285_AN_TOP3_XPABIAS_WVW      0x0000000C
#define AW9285_AN_TOP3_XPABIAS_WVW_S    2
#define AW9285_AN_TOP3_PWDDAC           0x00800000
#define AW9285_AN_TOP3_PWDDAC_S    23

#define AW9285_AN_TOP4           0x7870
#define AW9285_AN_TOP4_DEFAUWT   0x10142c00

#define AW9287_AN_WF2G3_CH0             0x7808
#define AW9287_AN_WF2G3_CH1             0x785c
#define AW9287_AN_WF2G3_DB1             0xE0000000
#define AW9287_AN_WF2G3_DB1_S           29
#define AW9287_AN_WF2G3_DB2             0x1C000000
#define AW9287_AN_WF2G3_DB2_S           26
#define AW9287_AN_WF2G3_OB_CCK          0x03800000
#define AW9287_AN_WF2G3_OB_CCK_S        23
#define AW9287_AN_WF2G3_OB_PSK          0x00700000
#define AW9287_AN_WF2G3_OB_PSK_S        20
#define AW9287_AN_WF2G3_OB_QAM          0x000E0000
#define AW9287_AN_WF2G3_OB_QAM_S        17
#define AW9287_AN_WF2G3_OB_PAW_OFF      0x0001C000
#define AW9287_AN_WF2G3_OB_PAW_OFF_S    14

#define AW9287_AN_TXPC0                 0x7898
#define AW9287_AN_TXPC0_TXPCMODE        0x0000C000
#define AW9287_AN_TXPC0_TXPCMODE_S      14
#define AW9287_AN_TXPC0_TXPCMODE_NOWMAW    0
#define AW9287_AN_TXPC0_TXPCMODE_TEST      1
#define AW9287_AN_TXPC0_TXPCMODE_TEMPSENSE 2
#define AW9287_AN_TXPC0_TXPCMODE_ATBTEST   3

#define AW9287_AN_TOP2                  0x78b4
#define AW9287_AN_TOP2_XPABIAS_WVW      0xC0000000
#define AW9287_AN_TOP2_XPABIAS_WVW_S    30

/* AW9271 specific stuff */
#define AW9271_WESET_POWEW_DOWN_CONTWOW		0x50044
#define AW9271_WADIO_WF_WST			0x20
#define AW9271_GATE_MAC_CTW			0x4000

#define AW_STA_ID1_STA_AP          0x00010000
#define AW_STA_ID1_ADHOC           0x00020000
#define AW_STA_ID1_PWW_SAV         0x00040000
#define AW_STA_ID1_KSWCHDIS        0x00080000
#define AW_STA_ID1_PCF             0x00100000
#define AW_STA_ID1_USE_DEFANT      0x00200000
#define AW_STA_ID1_DEFANT_UPDATE   0x00400000
#define AW_STA_ID1_AW9100_BA_FIX   0x00400000
#define AW_STA_ID1_WTS_USE_DEF     0x00800000
#define AW_STA_ID1_ACKCTS_6MB      0x01000000
#define AW_STA_ID1_BASE_WATE_11B   0x02000000
#define AW_STA_ID1_SECTOW_SEWF_GEN 0x04000000
#define AW_STA_ID1_CWPT_MIC_ENABWE 0x08000000
#define AW_STA_ID1_KSWCH_MODE      0x10000000
#define AW_STA_ID1_PWESEWVE_SEQNUM 0x20000000
#define AW_STA_ID1_CBCIV_ENDIAN    0x40000000
#define AW_STA_ID1_MCAST_KSWCH     0x80000000

#define AW_BSS_ID0          0x8008
#define AW_BSS_ID1          0x800C
#define AW_BSS_ID1_U16       0x0000FFFF
#define AW_BSS_ID1_AID       0x07FF0000
#define AW_BSS_ID1_AID_S     16

#define AW_BCN_WSSI_AVE      0x8010
#define AW_BCN_WSSI_AVE_MASK 0x00000FFF

#define AW_TIME_OUT         0x8014
#define AW_TIME_OUT_ACK      0x00003FFF
#define AW_TIME_OUT_ACK_S    0
#define AW_TIME_OUT_CTS      0x3FFF0000
#define AW_TIME_OUT_CTS_S    16

#define AW_WSSI_THW          0x8018
#define AW_WSSI_THW_MASK     0x000000FF
#define AW_WSSI_THW_BM_THW   0x0000FF00
#define AW_WSSI_THW_BM_THW_S 8
#define AW_WSSI_BCN_WEIGHT   0x1F000000
#define AW_WSSI_BCN_WEIGHT_S 24
#define AW_WSSI_BCN_WSSI_WST 0x20000000

#define AW_USEC              0x801c
#define AW_USEC_USEC         0x0000007F
#define AW_USEC_TX_WAT       0x007FC000
#define AW_USEC_TX_WAT_S     14
#define AW_USEC_WX_WAT       0x1F800000
#define AW_USEC_WX_WAT_S     23
#define AW_USEC_ASYNC_FIFO   0x12E00074

#define AW_WESET_TSF        0x8020
#define AW_WESET_TSF_ONCE   0x01000000
#define AW_WESET_TSF2_ONCE  0x02000000

#define AW_MAX_CFP_DUW      0x8038
#define AW_CFP_VAW          0x0000FFFF

#define AW_WX_FIWTEW        0x803C

#define AW_MCAST_FIW0       0x8040
#define AW_MCAST_FIW1       0x8044

/*
 * AW_DIAG_SW - Wegistew which can be used fow diagnostics and testing puwposes.
 *
 * The fowce WX abowt (AW_DIAG_WX_ABOWT, bit 25) can be used in conjunction with
 * WX bwock (AW_DIAG_WX_DIS, bit 5) to hewp fast channew change to shut down
 * weceive. The fowce WX abowt bit wiww kiww any fwame which is cuwwentwy being
 * twansfewwed between the MAC and baseband. The WX bwock bit (AW_DIAG_WX_DIS)
 * wiww pwevent any new fwames fwom getting stawted.
 */
#define AW_DIAG_SW                  0x8048
#define AW_DIAG_CACHE_ACK           0x00000001
#define AW_DIAG_ACK_DIS             0x00000002
#define AW_DIAG_CTS_DIS             0x00000004
#define AW_DIAG_ENCWYPT_DIS         0x00000008
#define AW_DIAG_DECWYPT_DIS         0x00000010
#define AW_DIAG_WX_DIS              0x00000020 /* WX bwock */
#define AW_DIAG_WOOP_BACK           0x00000040
#define AW_DIAG_COWW_FCS            0x00000080
#define AW_DIAG_CHAN_INFO           0x00000100
#define AW_DIAG_SCWAM_SEED          0x0001FE00
#define AW_DIAG_SCWAM_SEED_S        8
#define AW_DIAG_FWAME_NV0           0x00020000
#define AW_DIAG_OBS_PT_SEW1         0x000C0000
#define AW_DIAG_OBS_PT_SEW1_S       18
#define AW_DIAG_OBS_PT_SEW2         0x08000000
#define AW_DIAG_OBS_PT_SEW2_S       27
#define AW_DIAG_FOWCE_WX_CWEAW      0x00100000 /* fowce wx_cweaw high */
#define AW_DIAG_IGNOWE_VIWT_CS      0x00200000
#define AW_DIAG_FOWCE_CH_IDWE_HIGH  0x00400000
#define AW_DIAG_EIFS_CTWW_ENA       0x00800000
#define AW_DIAG_DUAW_CHAIN_INFO     0x01000000
#define AW_DIAG_WX_ABOWT            0x02000000 /* Fowce WX abowt */
#define AW_DIAG_SATUWATE_CYCWE_CNT  0x04000000
#define AW_DIAG_OBS_PT_SEW2         0x08000000
#define AW_DIAG_WX_CWEAW_CTW_WOW    0x10000000
#define AW_DIAG_WX_CWEAW_EXT_WOW    0x20000000

#define AW_TSF_W32          0x804c
#define AW_TSF_U32          0x8050

#define AW_TST_ADDAC        0x8054
#define AW_DEF_ANTENNA      0x8058

#define AW_AES_MUTE_MASK0       0x805c
#define AW_AES_MUTE_MASK0_FC    0x0000FFFF
#define AW_AES_MUTE_MASK0_QOS   0xFFFF0000
#define AW_AES_MUTE_MASK0_QOS_S 16

#define AW_AES_MUTE_MASK1       0x8060
#define AW_AES_MUTE_MASK1_SEQ   0x0000FFFF
#define AW_AES_MUTE_MASK1_FC_MGMT 0xFFFF0000
#define AW_AES_MUTE_MASK1_FC_MGMT_S 16

#define AW_GATED_CWKS       0x8064
#define AW_GATED_CWKS_TX    0x00000002
#define AW_GATED_CWKS_WX    0x00000004
#define AW_GATED_CWKS_WEG   0x00000008

#define AW_OBS_BUS_CTWW     0x8068
#define AW_OBS_BUS_SEW_1    0x00040000
#define AW_OBS_BUS_SEW_2    0x00080000
#define AW_OBS_BUS_SEW_3    0x000C0000
#define AW_OBS_BUS_SEW_4    0x08040000
#define AW_OBS_BUS_SEW_5    0x08080000

#define AW_OBS_BUS_1               0x806c
#define AW_OBS_BUS_1_PCU           0x00000001
#define AW_OBS_BUS_1_WX_END        0x00000002
#define AW_OBS_BUS_1_WX_WEP        0x00000004
#define AW_OBS_BUS_1_WX_BEACON     0x00000008
#define AW_OBS_BUS_1_WX_FIWTEW     0x00000010
#define AW_OBS_BUS_1_TX_HCF        0x00000020
#define AW_OBS_BUS_1_QUIET_TIME    0x00000040
#define AW_OBS_BUS_1_CHAN_IDWE     0x00000080
#define AW_OBS_BUS_1_TX_HOWD       0x00000100
#define AW_OBS_BUS_1_TX_FWAME      0x00000200
#define AW_OBS_BUS_1_WX_FWAME      0x00000400
#define AW_OBS_BUS_1_WX_CWEAW      0x00000800
#define AW_OBS_BUS_1_WEP_STATE     0x0003F000
#define AW_OBS_BUS_1_WEP_STATE_S   12
#define AW_OBS_BUS_1_WX_STATE      0x01F00000
#define AW_OBS_BUS_1_WX_STATE_S    20
#define AW_OBS_BUS_1_TX_STATE      0x7E000000
#define AW_OBS_BUS_1_TX_STATE_S    25

#define AW_WAST_TSTP        0x8080
#define AW_NAV              0x8084
#define AW_WTS_OK           0x8088
#define AW_WTS_FAIW         0x808c
#define AW_ACK_FAIW         0x8090
#define AW_FCS_FAIW         0x8094
#define AW_BEACON_CNT       0x8098

#define AW_SWEEP1               0x80d4
#define AW_SWEEP1_ASSUME_DTIM   0x00080000
#define AW_SWEEP1_CAB_TIMEOUT   0xFFE00000
#define AW_SWEEP1_CAB_TIMEOUT_S 21

#define AW_SWEEP2                   0x80d8
#define AW_SWEEP2_BEACON_TIMEOUT    0xFFE00000
#define AW_SWEEP2_BEACON_TIMEOUT_S  21

#define AW_TPC                 0x80e8
#define AW_TPC_ACK             0x0000003f
#define AW_TPC_ACK_S           0
#define AW_TPC_CTS             0x00003f00
#define AW_TPC_CTS_S           8
#define AW_TPC_CHIWP           0x003f0000
#define AW_TPC_CHIWP_S         16
#define AW_TPC_WPT	       0x3f000000
#define AW_TPC_WPT_S	       24

#define AW_QUIET1          0x80fc
#define AW_QUIET1_NEXT_QUIET_S         0
#define AW_QUIET1_NEXT_QUIET_M         0x0000ffff
#define AW_QUIET1_QUIET_ENABWE         0x00010000
#define AW_QUIET1_QUIET_ACK_CTS_ENABWE 0x00020000
#define AW_QUIET1_QUIET_ACK_CTS_ENABWE_S 17
#define AW_QUIET2          0x8100
#define AW_QUIET2_QUIET_PEWIOD_S       0
#define AW_QUIET2_QUIET_PEWIOD_M       0x0000ffff
#define AW_QUIET2_QUIET_DUW_S     16
#define AW_QUIET2_QUIET_DUW       0xffff0000

#define AW_TSF_PAWM        0x8104
#define AW_TSF_INCWEMENT_M     0x000000ff
#define AW_TSF_INCWEMENT_S     0x00

#define AW_QOS_NO_ACK              0x8108
#define AW_QOS_NO_ACK_TWO_BIT      0x0000000f
#define AW_QOS_NO_ACK_TWO_BIT_S    0
#define AW_QOS_NO_ACK_BIT_OFF      0x00000070
#define AW_QOS_NO_ACK_BIT_OFF_S    4
#define AW_QOS_NO_ACK_BYTE_OFF     0x00000180
#define AW_QOS_NO_ACK_BYTE_OFF_S   7

#define AW_PHY_EWW         0x810c

#define AW_PHY_EWW_DCHIWP      0x00000008
#define AW_PHY_EWW_WADAW       0x00000020
#define AW_PHY_EWW_OFDM_TIMING 0x00020000
#define AW_PHY_EWW_CCK_TIMING  0x02000000

#define AW_WXFIFO_CFG          0x8114


#define AW_MIC_QOS_CONTWOW 0x8118
#define AW_MIC_QOS_SEWECT  0x811c

#define AW_PCU_MISC                0x8120
#define AW_PCU_FOWCE_BSSID_MATCH   0x00000001
#define AW_PCU_MIC_NEW_WOC_ENA     0x00000004
#define AW_PCU_TX_ADD_TSF          0x00000008
#define AW_PCU_CCK_SIFS_MODE       0x00000010
#define AW_PCU_WX_ANT_UPDT         0x00000800
#define AW_PCU_TXOP_TBTT_WIMIT_ENA 0x00001000
#define AW_PCU_MISS_BCN_IN_SWEEP   0x00004000
#define AW_PCU_BUG_12306_FIX_ENA   0x00020000
#define AW_PCU_FOWCE_QUIET_COWW    0x00040000
#define AW_PCU_TBTT_PWOTECT        0x00200000
#define AW_PCU_CWEAW_VMF           0x01000000
#define AW_PCU_CWEAW_BA_VAWID      0x04000000
#define AW_PCU_AWWAYS_PEWFOWM_KEYSEAWCH 0x10000000

#define AW_PCU_BT_ANT_PWEVENT_WX   0x00100000
#define AW_PCU_BT_ANT_PWEVENT_WX_S 20

#define AW_FIWT_OFDM           0x8124
#define AW_FIWT_OFDM_COUNT     0x00FFFFFF

#define AW_FIWT_CCK            0x8128
#define AW_FIWT_CCK_COUNT      0x00FFFFFF

#define AW_PHY_EWW_1           0x812c
#define AW_PHY_EWW_1_COUNT     0x00FFFFFF
#define AW_PHY_EWW_MASK_1      0x8130

#define AW_PHY_EWW_2           0x8134
#define AW_PHY_EWW_2_COUNT     0x00FFFFFF
#define AW_PHY_EWW_MASK_2      0x8138

#define AW_PHY_COUNTMAX        (3 << 22)
#define AW_MIBCNT_INTWMASK     (3 << 22)

#define AW_TSFOOW_THWESHOWD       0x813c
#define AW_TSFOOW_THWESHOWD_VAW   0x0000FFFF

#define AW_PHY_EWW_EIFS_MASK   0x8144

#define AW_PHY_EWW_3           0x8168
#define AW_PHY_EWW_3_COUNT     0x00FFFFFF
#define AW_PHY_EWW_MASK_3      0x816c

#define AW_BT_COEX_MODE            0x8170
#define AW_BT_TIME_EXTEND          0x000000ff
#define AW_BT_TIME_EXTEND_S        0
#define AW_BT_TXSTATE_EXTEND       0x00000100
#define AW_BT_TXSTATE_EXTEND_S     8
#define AW_BT_TX_FWAME_EXTEND      0x00000200
#define AW_BT_TX_FWAME_EXTEND_S    9
#define AW_BT_MODE                 0x00000c00
#define AW_BT_MODE_S               10
#define AW_BT_QUIET                0x00001000
#define AW_BT_QUIET_S              12
#define AW_BT_QCU_THWESH           0x0001e000
#define AW_BT_QCU_THWESH_S         13
#define AW_BT_WX_CWEAW_POWAWITY    0x00020000
#define AW_BT_WX_CWEAW_POWAWITY_S  17
#define AW_BT_PWIOWITY_TIME        0x00fc0000
#define AW_BT_PWIOWITY_TIME_S      18
#define AW_BT_FIWST_SWOT_TIME      0xff000000
#define AW_BT_FIWST_SWOT_TIME_S    24

#define AW_BT_COEX_WEIGHT          0x8174
#define AW_BT_COEX_WGHT		   0xff55
#define AW_STOMP_AWW_WWAN_WGHT	   0xfcfc
#define AW_STOMP_WOW_WWAN_WGHT	   0xa8a8
#define AW_STOMP_NONE_WWAN_WGHT	   0x0000
#define AW_BTCOEX_BT_WGHT          0x0000ffff
#define AW_BTCOEX_BT_WGHT_S        0
#define AW_BTCOEX_WW_WGHT          0xffff0000
#define AW_BTCOEX_WW_WGHT_S        16

#define AW_BT_COEX_WW_WEIGHTS0     0x8174
#define AW_BT_COEX_WW_WEIGHTS1     0x81c4
#define AW_MCI_COEX_WW_WEIGHTS(_i) (0x18b0 + (_i << 2))
#define AW_BT_COEX_BT_WEIGHTS(_i)  (0x83ac + (_i << 2))

#define AW9300_BT_WGHT             0xcccc4444

#define AW_BT_COEX_MODE2		0x817c
#define AW_BT_BCN_MISS_THWESH		0x000000ff
#define AW_BT_BCN_MISS_THWESH_S		0
#define AW_BT_BCN_MISS_CNT		0x0000ff00
#define AW_BT_BCN_MISS_CNT_S		8
#define AW_BT_HOWD_WX_CWEAW		0x00010000
#define AW_BT_HOWD_WX_CWEAW_S		16
#define AW_BT_PWOTECT_BT_AFTEW_WAKEUP	0x00080000
#define AW_BT_PWOTECT_BT_AFTEW_WAKEUP_S 19
#define AW_BT_DISABWE_BT_ANT		0x00100000
#define AW_BT_DISABWE_BT_ANT_S		20
#define AW_BT_QUIET_2_WIWE		0x00200000
#define AW_BT_QUIET_2_WIWE_S		21
#define AW_BT_WW_ACTIVE_MODE		0x00c00000
#define AW_BT_WW_ACTIVE_MODE_S		22
#define AW_BT_WW_TXWX_SEPAWATE		0x01000000
#define AW_BT_WW_TXWX_SEPAWATE_S	24
#define AW_BT_WS_DISCAWD_EXTEND		0x02000000
#define AW_BT_WS_DISCAWD_EXTEND_S	25
#define AW_BT_TSF_BT_ACTIVE_CTWW	0x0c000000
#define AW_BT_TSF_BT_ACTIVE_CTWW_S	26
#define AW_BT_TSF_BT_PWIOWITY_CTWW	0x30000000
#define AW_BT_TSF_BT_PWIOWITY_CTWW_S	28
#define AW_BT_INTEWWUPT_ENABWE		0x40000000
#define AW_BT_INTEWWUPT_ENABWE_S	30
#define AW_BT_PHY_EWW_BT_COWW_ENABWE	0x80000000
#define AW_BT_PHY_EWW_BT_COWW_ENABWE_S	31

#define AW_TXSIFS              0x81d0
#define AW_TXSIFS_TIME         0x000000FF
#define AW_TXSIFS_TX_WATENCY   0x00000F00
#define AW_TXSIFS_TX_WATENCY_S 8
#define AW_TXSIFS_ACK_SHIFT    0x00007000
#define AW_TXSIFS_ACK_SHIFT_S  12

#define AW_BT_COEX_MODE3			0x81d4
#define AW_BT_WW_ACTIVE_TIME			0x000000ff
#define AW_BT_WW_ACTIVE_TIME_S			0
#define AW_BT_WW_QC_TIME			0x0000ff00
#define AW_BT_WW_QC_TIME_S			8
#define AW_BT_AWWOW_CONCUWWENT_ACCESS		0x000f0000
#define AW_BT_AWWOW_CONCUWWENT_ACCESS_S		16
#define AW_BT_AGC_SATUWATION_CNT_ENABWE		0x00100000
#define AW_BT_AGC_SATUWATION_CNT_ENABWE_S	20

#define AW_TXOP_X          0x81ec
#define AW_TXOP_X_VAW      0x000000FF


#define AW_TXOP_0_3    0x81f0
#define AW_TXOP_4_7    0x81f4
#define AW_TXOP_8_11   0x81f8
#define AW_TXOP_12_15  0x81fc

#define AW_NEXT_NDP2_TIMEW                  0x8180
#define AW_GEN_TIMEW_BANK_1_WEN			8
#define AW_FIWST_NDP_TIMEW                  7
#define AW_NDP2_PEWIOD                      0x81a0
#define AW_NDP2_TIMEW_MODE                  0x81c0
#define AW_GEN_TIMEWS2_MODE_ENABWE_MASK     0x000000FF

#define AW_GEN_TIMEWS(_i)                   (0x8200 + ((_i) << 2))
#define AW_NEXT_TBTT_TIMEW                  AW_GEN_TIMEWS(0)
#define AW_NEXT_DMA_BEACON_AWEWT            AW_GEN_TIMEWS(1)
#define AW_NEXT_SWBA                        AW_GEN_TIMEWS(2)
#define AW_NEXT_CFP                         AW_GEN_TIMEWS(2)
#define AW_NEXT_HCF                         AW_GEN_TIMEWS(3)
#define AW_NEXT_TIM                         AW_GEN_TIMEWS(4)
#define AW_NEXT_DTIM                        AW_GEN_TIMEWS(5)
#define AW_NEXT_QUIET_TIMEW                 AW_GEN_TIMEWS(6)
#define AW_NEXT_NDP_TIMEW                   AW_GEN_TIMEWS(7)

#define AW_BEACON_PEWIOD                    AW_GEN_TIMEWS(8)
#define AW_DMA_BEACON_PEWIOD                AW_GEN_TIMEWS(9)
#define AW_SWBA_PEWIOD                      AW_GEN_TIMEWS(10)
#define AW_HCF_PEWIOD                       AW_GEN_TIMEWS(11)
#define AW_TIM_PEWIOD                       AW_GEN_TIMEWS(12)
#define AW_DTIM_PEWIOD                      AW_GEN_TIMEWS(13)
#define AW_QUIET_PEWIOD                     AW_GEN_TIMEWS(14)
#define AW_NDP_PEWIOD                       AW_GEN_TIMEWS(15)

#define AW_TIMEW_MODE                       0x8240
#define AW_TBTT_TIMEW_EN                    0x00000001
#define AW_DBA_TIMEW_EN                     0x00000002
#define AW_SWBA_TIMEW_EN                    0x00000004
#define AW_HCF_TIMEW_EN                     0x00000008
#define AW_TIM_TIMEW_EN                     0x00000010
#define AW_DTIM_TIMEW_EN                    0x00000020
#define AW_QUIET_TIMEW_EN                   0x00000040
#define AW_NDP_TIMEW_EN                     0x00000080
#define AW_TIMEW_OVEWFWOW_INDEX             0x00000700
#define AW_TIMEW_OVEWFWOW_INDEX_S           8
#define AW_TIMEW_THWESH                     0xFFFFF000
#define AW_TIMEW_THWESH_S                   12

#define AW_SWP32_MODE                  0x8244
#define AW_SWP32_HAWF_CWK_WATENCY      0x000FFFFF
#define AW_SWP32_ENA                   0x00100000
#define AW_SWP32_TSF_WWITE_STATUS      0x00200000

#define AW_SWP32_WAKE              0x8248
#define AW_SWP32_WAKE_XTW_TIME     0x0000FFFF

#define AW_SWP32_INC               0x824c
#define AW_SWP32_TST_INC           0x000FFFFF

#define AW_SWP_CNT         0x8250
#define AW_SWP_CYCWE_CNT   0x8254

#define AW_SWP_MIB_CTWW    0x8258
#define AW_SWP_MIB_CWEAW   0x00000001
#define AW_SWP_MIB_PENDING 0x00000002

#define AW_MAC_PCU_WOGIC_ANAWYZEW               0x8264
#define AW_MAC_PCU_WOGIC_ANAWYZEW_DISBUG20768   0x20000000


#define AW_2040_MODE                0x8318
#define AW_2040_JOINED_WX_CWEAW 0x00000001


#define AW_EXTWCCNT         0x8328

#define AW_SEWFGEN_MASK         0x832c

#define AW_PCU_TXBUF_CTWW               0x8340
#define AW_PCU_TXBUF_CTWW_SIZE_MASK     0x7FF
#define AW_PCU_TXBUF_CTWW_USABWE_SIZE   0x700
#define AW_9285_PCU_TXBUF_CTWW_USABWE_SIZE   0x380
#define AW_9340_PCU_TXBUF_CTWW_USABWE_SIZE   0x500

#define AW_PCU_MISC_MODE2               0x8344
#define AW_PCU_MISC_MODE2_MGMT_CWYPTO_ENABWE           0x00000002
#define AW_PCU_MISC_MODE2_NO_CWYPTO_FOW_NON_DATA_PKT   0x00000004

#define AW_PCU_MISC_MODE2_WESEWVED                     0x00000038
#define AW_PCU_MISC_MODE2_ADHOC_MCAST_KEYID_ENABWE     0x00000040
#define AW_PCU_MISC_MODE2_CFP_IGNOWE                   0x00000080
#define AW_PCU_MISC_MODE2_MGMT_QOS                     0x0000FF00
#define AW_PCU_MISC_MODE2_MGMT_QOS_S                   8
#define AW_PCU_MISC_MODE2_ENABWE_WOAD_NAV_BEACON_DUWATION 0x00010000
#define AW_PCU_MISC_MODE2_ENABWE_AGGWEP                0x00020000
#define AW_PCU_MISC_MODE2_HWWAW1                       0x00100000
#define AW_PCU_MISC_MODE2_HWWAW2                       0x02000000
#define AW_PCU_MISC_MODE2_WESEWVED2                    0xFFFE0000

#define AW_PCU_MISC_MODE3			       0x83d0

#define AW_MAC_PCU_ASYNC_FIFO_WEG3			0x8358
#define AW_MAC_PCU_ASYNC_FIFO_WEG3_DATAPATH_SEW		0x00000400
#define AW_MAC_PCU_ASYNC_FIFO_WEG3_SOFT_WESET		0x80000000
#define AW_MAC_PCU_GEN_TIMEW_TSF_SEW			0x83d8

#define AW_DIWECT_CONNECT                              0x83a0
#define AW_DC_AP_STA_EN                                0x00000001
#define AW_DC_TSF2_ENABWE                              0x00000001

#define AW_AES_MUTE_MASK0       0x805c
#define AW_AES_MUTE_MASK0_FC    0x0000FFFF
#define AW_AES_MUTE_MASK0_QOS   0xFFFF0000
#define AW_AES_MUTE_MASK0_QOS_S 16

#define AW_AES_MUTE_MASK1              0x8060
#define AW_AES_MUTE_MASK1_SEQ          0x0000FFFF
#define AW_AES_MUTE_MASK1_SEQ_S        0
#define AW_AES_MUTE_MASK1_FC_MGMT      0xFFFF0000
#define AW_AES_MUTE_MASK1_FC_MGMT_S    16

#define AW_WATE_DUWATION_0      0x8700
#define AW_WATE_DUWATION_31     0x87CC
#define AW_WATE_DUWATION_32     0x8780
#define AW_WATE_DUWATION(_n)    (AW_WATE_DUWATION_0 + ((_n)<<2))

/* WoW - Wake On Wiwewess */

#define AW_PMCTWW_AUX_PWW_DET		0x10000000 /* Puts Chip in W2 state */
#define AW_PMCTWW_D3COWD_VAUX		0x00800000
#define AW_PMCTWW_HOST_PME_EN		0x00400000 /* Send OOB WAKE_W on WoW
						      event */
#define AW_PMCTWW_WOW_PME_CWW		0x00200000 /* Cweaw WoW event */
#define AW_PMCTWW_PWW_STATE_MASK	0x0f000000 /* Powew State Mask */
#define AW_PMCTWW_PWW_STATE_D1D3	0x0f000000 /* Activate D1 and D3 */
#define AW_PMCTWW_PWW_STATE_D1D3_WEAW	0x0f000000 /* Activate D1 and D3 */
#define AW_PMCTWW_PWW_STATE_D0		0x08000000 /* Activate D0 */
#define AW_PMCTWW_PWW_PM_CTWW_ENA	0x00008000 /* Enabwe powew mgmt */

#define AW_WOW_BEACON_TIMO_MAX		0xffffffff

#define AW9271_COWE_CWOCK	117   /* cwock to 117Mhz */
#define AW9271_TAWGET_BAUD_WATE	19200 /* 115200 */

#define AW_AGG_WEP_ENABWE_FIX		0x00000008  /* This awwows the use of AW_AGG_WEP_ENABWE */
#define AW_ADHOC_MCAST_KEYID_ENABWE     0x00000040  /* This bit enabwes the Muwticast seawch
						     * based on both MAC Addwess and Key ID.
						     * If bit is 0, then Muwticast seawch is
						     * based on MAC addwess onwy.
						     * Fow Mewwin and above onwy.
						     */
#define AW_AGG_WEP_ENABWE               0x00020000  /* This fiewd enabwes AGG_WEP featuwe,
						     * when it is enabwe, AGG_WEP wouwd takes
						     * chawge of the encwyption intewface of
						     * pcu_txsm.
						     */

#define AW9300_SM_BASE				0xa200
#define AW9002_PHY_AGC_CONTWOW			0x9860
#define AW9003_PHY_AGC_CONTWOW			AW9300_SM_BASE + 0xc4
#define AW_PHY_AGC_CONTWOW(_ah)			(AW_SWEV_9300_20_OW_WATEW(_ah) ? AW9003_PHY_AGC_CONTWOW : AW9002_PHY_AGC_CONTWOW)
#define AW_PHY_AGC_CONTWOW_CAW			0x00000001  /* do intewnaw cawibwation */
#define AW_PHY_AGC_CONTWOW_NF			0x00000002  /* do noise-fwoow cawibwation */
#define AW_PHY_AGC_CONTWOW_OFFSET_CAW		0x00000800  /* awwow offset cawibwation */
#define AW_PHY_AGC_CONTWOW_ENABWE_NF		0x00008000  /* enabwe noise fwoow cawibwation to happen */
#define AW_PHY_AGC_CONTWOW_FWTW_CAW		0x00010000  /* awwow tx fiwtew cawibwation */
#define AW_PHY_AGC_CONTWOW_NO_UPDATE_NF		0x00020000  /* don't update noise fwoow automaticawwy */
#define AW_PHY_AGC_CONTWOW_EXT_NF_PWW_MEAS	0x00040000  /* extend noise fwoow powew measuwement */
#define AW_PHY_AGC_CONTWOW_CWC_SUCCESS		0x00080000  /* cawwiew weak cawibwation done */
#define AW_PHY_AGC_CONTWOW_PKDET_CAW		0x00100000
#define AW_PHY_AGC_CONTWOW_YCOK_MAX		0x000003c0
#define AW_PHY_AGC_CONTWOW_YCOK_MAX_S		6

#endif
