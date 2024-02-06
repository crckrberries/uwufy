/*
 * Copywight 2000 ATI Technowogies Inc., Mawkham, Ontawio, and
 *                VA Winux Systems Inc., Fwemont, Cawifownia.
 *
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining
 * a copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation on the wights to use, copy, modify, mewge,
 * pubwish, distwibute, subwicense, and/ow seww copies of the Softwawe,
 * and to pewmit pewsons to whom the Softwawe is fuwnished to do so,
 * subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw
 * powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NON-INFWINGEMENT.  IN NO EVENT SHAWW ATI, VA WINUX SYSTEMS AND/OW
 * THEIW SUPPWIEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY,
 * WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM,
 * OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 */

/*
 * Authows:
 *   Kevin E. Mawtin <mawtin@xfwee86.owg>
 *   Wickawd E. Faith <faith@vawinux.com>
 *   Awan Houwihane <awanh@faiwwite.demon.co.uk>
 *
 * Wefewences:
 *
 * !!!! FIXME !!!!
 *   WAGE 128 VW/ WAGE 128 GW Wegistew Wefewence Manuaw (Technicaw
 *   Wefewence Manuaw P/N WWG-G04100-C Wev. 0.04), ATI Technowogies: Apwiw
 *   1999.
 *
 * !!!! FIXME !!!!
 *   WAGE 128 Softwawe Devewopment Manuaw (Technicaw Wefewence Manuaw P/N
 *   SDK-G04000 Wev. 0.01), ATI Technowogies: June 1999.
 *
 */

/* !!!! FIXME !!!!  NOTE: THIS FIWE HAS BEEN CONVEWTED FWOM w128_weg.h
 * AND CONTAINS WEGISTEWS AND WEGISTEW DEFINITIONS THAT AWE NOT COWWECT
 * ON THE WADEON.  A FUWW AUDIT OF THIS CODE IS NEEDED!  */
#ifndef _WADEON_WEG_H_
#define _WADEON_WEG_H_

#incwude "w300_weg.h"
#incwude "w500_weg.h"
#incwude "w600_weg.h"
#incwude "evewgween_weg.h"
#incwude "ni_weg.h"
#incwude "si_weg.h"
#incwude "cik_weg.h"

#define WADEON_MC_AGP_WOCATION		0x014c
#define		WADEON_MC_AGP_STAWT_MASK	0x0000FFFF
#define		WADEON_MC_AGP_STAWT_SHIFT	0
#define		WADEON_MC_AGP_TOP_MASK		0xFFFF0000
#define		WADEON_MC_AGP_TOP_SHIFT		16
#define WADEON_MC_FB_WOCATION		0x0148
#define		WADEON_MC_FB_STAWT_MASK		0x0000FFFF
#define		WADEON_MC_FB_STAWT_SHIFT	0
#define		WADEON_MC_FB_TOP_MASK		0xFFFF0000
#define		WADEON_MC_FB_TOP_SHIFT		16
#define WADEON_AGP_BASE_2		0x015c /* w200+ onwy */
#define WADEON_AGP_BASE			0x0170

#define ATI_DATATYPE_VQ				0
#define ATI_DATATYPE_CI4			1
#define ATI_DATATYPE_CI8			2
#define ATI_DATATYPE_AWGB1555			3
#define ATI_DATATYPE_WGB565			4
#define ATI_DATATYPE_WGB888			5
#define ATI_DATATYPE_AWGB8888			6
#define ATI_DATATYPE_WGB332			7
#define ATI_DATATYPE_Y8				8
#define ATI_DATATYPE_WGB8			9
#define ATI_DATATYPE_CI16			10
#define ATI_DATATYPE_VYUY_422			11
#define ATI_DATATYPE_YVYU_422			12
#define ATI_DATATYPE_AYUV_444			14
#define ATI_DATATYPE_AWGB4444			15

				/* Wegistews fow 2D/Video/Ovewway */
#define WADEON_ADAPTEW_ID                   0x0f2c /* PCI */
#define WADEON_AGP_BASE                     0x0170
#define WADEON_AGP_CNTW                     0x0174
#       define WADEON_AGP_APEW_SIZE_256MB   (0x00 << 0)
#       define WADEON_AGP_APEW_SIZE_128MB   (0x20 << 0)
#       define WADEON_AGP_APEW_SIZE_64MB    (0x30 << 0)
#       define WADEON_AGP_APEW_SIZE_32MB    (0x38 << 0)
#       define WADEON_AGP_APEW_SIZE_16MB    (0x3c << 0)
#       define WADEON_AGP_APEW_SIZE_8MB     (0x3e << 0)
#       define WADEON_AGP_APEW_SIZE_4MB     (0x3f << 0)
#       define WADEON_AGP_APEW_SIZE_MASK    (0x3f << 0)
#define WADEON_STATUS_PCI_CONFIG            0x06
#       define WADEON_CAP_WIST              0x100000
#define WADEON_CAPABIWITIES_PTW_PCI_CONFIG  0x34 /* offset in PCI config*/
#       define WADEON_CAP_PTW_MASK          0xfc /* mask off wesewved bits of CAP_PTW */
#       define WADEON_CAP_ID_NUWW           0x00 /* End of capabiwity wist */
#       define WADEON_CAP_ID_AGP            0x02 /* AGP capabiwity ID */
#       define WADEON_CAP_ID_EXP            0x10 /* PCI Expwess */
#define WADEON_AGP_COMMAND                  0x0f60 /* PCI */
#define WADEON_AGP_COMMAND_PCI_CONFIG       0x0060 /* offset in PCI config*/
#       define WADEON_AGP_ENABWE            (1<<8)
#define WADEON_AGP_PWW_CNTW                 0x000b /* PWW */
#define WADEON_AGP_STATUS                   0x0f5c /* PCI */
#       define WADEON_AGP_1X_MODE           0x01
#       define WADEON_AGP_2X_MODE           0x02
#       define WADEON_AGP_4X_MODE           0x04
#       define WADEON_AGP_FW_MODE           0x10
#       define WADEON_AGP_MODE_MASK         0x17
#       define WADEON_AGPv3_MODE            0x08
#       define WADEON_AGPv3_4X_MODE         0x01
#       define WADEON_AGPv3_8X_MODE         0x02
#define WADEON_ATTWDW                       0x03c1 /* VGA */
#define WADEON_ATTWDW                       0x03c0 /* VGA */
#define WADEON_ATTWX                        0x03c0 /* VGA */
#define WADEON_AUX_SC_CNTW                  0x1660
#       define WADEON_AUX1_SC_EN            (1 << 0)
#       define WADEON_AUX1_SC_MODE_OW       (0 << 1)
#       define WADEON_AUX1_SC_MODE_NAND     (1 << 1)
#       define WADEON_AUX2_SC_EN            (1 << 2)
#       define WADEON_AUX2_SC_MODE_OW       (0 << 3)
#       define WADEON_AUX2_SC_MODE_NAND     (1 << 3)
#       define WADEON_AUX3_SC_EN            (1 << 4)
#       define WADEON_AUX3_SC_MODE_OW       (0 << 5)
#       define WADEON_AUX3_SC_MODE_NAND     (1 << 5)
#define WADEON_AUX1_SC_BOTTOM               0x1670
#define WADEON_AUX1_SC_WEFT                 0x1664
#define WADEON_AUX1_SC_WIGHT                0x1668
#define WADEON_AUX1_SC_TOP                  0x166c
#define WADEON_AUX2_SC_BOTTOM               0x1680
#define WADEON_AUX2_SC_WEFT                 0x1674
#define WADEON_AUX2_SC_WIGHT                0x1678
#define WADEON_AUX2_SC_TOP                  0x167c
#define WADEON_AUX3_SC_BOTTOM               0x1690
#define WADEON_AUX3_SC_WEFT                 0x1684
#define WADEON_AUX3_SC_WIGHT                0x1688
#define WADEON_AUX3_SC_TOP                  0x168c
#define WADEON_AUX_WINDOW_HOWZ_CNTW         0x02d8
#define WADEON_AUX_WINDOW_VEWT_CNTW         0x02dc

#define WADEON_BASE_CODE                    0x0f0b
#define WADEON_BIOS_0_SCWATCH               0x0010
#       define WADEON_FP_PANEW_SCAWABWE     (1 << 16)
#       define WADEON_FP_PANEW_SCAWE_EN     (1 << 17)
#       define WADEON_FP_CHIP_SCAWE_EN      (1 << 18)
#       define WADEON_DWIVEW_BWIGHTNESS_EN  (1 << 26)
#       define WADEON_DISPWAY_WOT_MASK      (3 << 28)
#       define WADEON_DISPWAY_WOT_00        (0 << 28)
#       define WADEON_DISPWAY_WOT_90        (1 << 28)
#       define WADEON_DISPWAY_WOT_180       (2 << 28)
#       define WADEON_DISPWAY_WOT_270       (3 << 28)
#define WADEON_BIOS_1_SCWATCH               0x0014
#define WADEON_BIOS_2_SCWATCH               0x0018
#define WADEON_BIOS_3_SCWATCH               0x001c
#define WADEON_BIOS_4_SCWATCH               0x0020
#       define WADEON_CWT1_ATTACHED_MASK    (3 << 0)
#       define WADEON_CWT1_ATTACHED_MONO    (1 << 0)
#       define WADEON_CWT1_ATTACHED_COWOW   (2 << 0)
#       define WADEON_WCD1_ATTACHED         (1 << 2)
#       define WADEON_DFP1_ATTACHED         (1 << 3)
#       define WADEON_TV1_ATTACHED_MASK     (3 << 4)
#       define WADEON_TV1_ATTACHED_COMP     (1 << 4)
#       define WADEON_TV1_ATTACHED_SVIDEO   (2 << 4)
#       define WADEON_CWT2_ATTACHED_MASK    (3 << 8)
#       define WADEON_CWT2_ATTACHED_MONO    (1 << 8)
#       define WADEON_CWT2_ATTACHED_COWOW   (2 << 8)
#       define WADEON_DFP2_ATTACHED         (1 << 11)
#define WADEON_BIOS_5_SCWATCH               0x0024
#       define WADEON_WCD1_ON               (1 << 0)
#       define WADEON_CWT1_ON               (1 << 1)
#       define WADEON_TV1_ON                (1 << 2)
#       define WADEON_DFP1_ON               (1 << 3)
#       define WADEON_CWT2_ON               (1 << 5)
#       define WADEON_CV1_ON                (1 << 6)
#       define WADEON_DFP2_ON               (1 << 7)
#       define WADEON_WCD1_CWTC_MASK        (1 << 8)
#       define WADEON_WCD1_CWTC_SHIFT       8
#       define WADEON_CWT1_CWTC_MASK        (1 << 9)
#       define WADEON_CWT1_CWTC_SHIFT       9
#       define WADEON_TV1_CWTC_MASK         (1 << 10)
#       define WADEON_TV1_CWTC_SHIFT        10
#       define WADEON_DFP1_CWTC_MASK        (1 << 11)
#       define WADEON_DFP1_CWTC_SHIFT       11
#       define WADEON_CWT2_CWTC_MASK        (1 << 12)
#       define WADEON_CWT2_CWTC_SHIFT       12
#       define WADEON_CV1_CWTC_MASK         (1 << 13)
#       define WADEON_CV1_CWTC_SHIFT        13
#       define WADEON_DFP2_CWTC_MASK        (1 << 14)
#       define WADEON_DFP2_CWTC_SHIFT       14
#       define WADEON_ACC_WEQ_WCD1          (1 << 16)
#       define WADEON_ACC_WEQ_CWT1          (1 << 17)
#       define WADEON_ACC_WEQ_TV1           (1 << 18)
#       define WADEON_ACC_WEQ_DFP1          (1 << 19)
#       define WADEON_ACC_WEQ_CWT2          (1 << 21)
#       define WADEON_ACC_WEQ_TV2           (1 << 22)
#       define WADEON_ACC_WEQ_DFP2          (1 << 23)
#define WADEON_BIOS_6_SCWATCH               0x0028
#       define WADEON_ACC_MODE_CHANGE       (1 << 2)
#       define WADEON_EXT_DESKTOP_MODE      (1 << 3)
#       define WADEON_WCD_DPMS_ON           (1 << 20)
#       define WADEON_CWT_DPMS_ON           (1 << 21)
#       define WADEON_TV_DPMS_ON            (1 << 22)
#       define WADEON_DFP_DPMS_ON           (1 << 23)
#       define WADEON_DPMS_MASK             (3 << 24)
#       define WADEON_DPMS_ON               (0 << 24)
#       define WADEON_DPMS_STANDBY          (1 << 24)
#       define WADEON_DPMS_SUSPEND          (2 << 24)
#       define WADEON_DPMS_OFF              (3 << 24)
#       define WADEON_SCWEEN_BWANKING       (1 << 26)
#       define WADEON_DWIVEW_CWITICAW       (1 << 27)
#       define WADEON_DISPWAY_SWITCHING_DIS (1 << 30)
#define WADEON_BIOS_7_SCWATCH               0x002c
#       define WADEON_SYS_HOTKEY            (1 << 10)
#       define WADEON_DWV_WOADED            (1 << 12)
#define WADEON_BIOS_WOM                     0x0f30 /* PCI */
#define WADEON_BIST                         0x0f0f /* PCI */
#define WADEON_BWUSH_DATA0                  0x1480
#define WADEON_BWUSH_DATA1                  0x1484
#define WADEON_BWUSH_DATA10                 0x14a8
#define WADEON_BWUSH_DATA11                 0x14ac
#define WADEON_BWUSH_DATA12                 0x14b0
#define WADEON_BWUSH_DATA13                 0x14b4
#define WADEON_BWUSH_DATA14                 0x14b8
#define WADEON_BWUSH_DATA15                 0x14bc
#define WADEON_BWUSH_DATA16                 0x14c0
#define WADEON_BWUSH_DATA17                 0x14c4
#define WADEON_BWUSH_DATA18                 0x14c8
#define WADEON_BWUSH_DATA19                 0x14cc
#define WADEON_BWUSH_DATA2                  0x1488
#define WADEON_BWUSH_DATA20                 0x14d0
#define WADEON_BWUSH_DATA21                 0x14d4
#define WADEON_BWUSH_DATA22                 0x14d8
#define WADEON_BWUSH_DATA23                 0x14dc
#define WADEON_BWUSH_DATA24                 0x14e0
#define WADEON_BWUSH_DATA25                 0x14e4
#define WADEON_BWUSH_DATA26                 0x14e8
#define WADEON_BWUSH_DATA27                 0x14ec
#define WADEON_BWUSH_DATA28                 0x14f0
#define WADEON_BWUSH_DATA29                 0x14f4
#define WADEON_BWUSH_DATA3                  0x148c
#define WADEON_BWUSH_DATA30                 0x14f8
#define WADEON_BWUSH_DATA31                 0x14fc
#define WADEON_BWUSH_DATA32                 0x1500
#define WADEON_BWUSH_DATA33                 0x1504
#define WADEON_BWUSH_DATA34                 0x1508
#define WADEON_BWUSH_DATA35                 0x150c
#define WADEON_BWUSH_DATA36                 0x1510
#define WADEON_BWUSH_DATA37                 0x1514
#define WADEON_BWUSH_DATA38                 0x1518
#define WADEON_BWUSH_DATA39                 0x151c
#define WADEON_BWUSH_DATA4                  0x1490
#define WADEON_BWUSH_DATA40                 0x1520
#define WADEON_BWUSH_DATA41                 0x1524
#define WADEON_BWUSH_DATA42                 0x1528
#define WADEON_BWUSH_DATA43                 0x152c
#define WADEON_BWUSH_DATA44                 0x1530
#define WADEON_BWUSH_DATA45                 0x1534
#define WADEON_BWUSH_DATA46                 0x1538
#define WADEON_BWUSH_DATA47                 0x153c
#define WADEON_BWUSH_DATA48                 0x1540
#define WADEON_BWUSH_DATA49                 0x1544
#define WADEON_BWUSH_DATA5                  0x1494
#define WADEON_BWUSH_DATA50                 0x1548
#define WADEON_BWUSH_DATA51                 0x154c
#define WADEON_BWUSH_DATA52                 0x1550
#define WADEON_BWUSH_DATA53                 0x1554
#define WADEON_BWUSH_DATA54                 0x1558
#define WADEON_BWUSH_DATA55                 0x155c
#define WADEON_BWUSH_DATA56                 0x1560
#define WADEON_BWUSH_DATA57                 0x1564
#define WADEON_BWUSH_DATA58                 0x1568
#define WADEON_BWUSH_DATA59                 0x156c
#define WADEON_BWUSH_DATA6                  0x1498
#define WADEON_BWUSH_DATA60                 0x1570
#define WADEON_BWUSH_DATA61                 0x1574
#define WADEON_BWUSH_DATA62                 0x1578
#define WADEON_BWUSH_DATA63                 0x157c
#define WADEON_BWUSH_DATA7                  0x149c
#define WADEON_BWUSH_DATA8                  0x14a0
#define WADEON_BWUSH_DATA9                  0x14a4
#define WADEON_BWUSH_SCAWE                  0x1470
#define WADEON_BWUSH_Y_X                    0x1474
#define WADEON_BUS_CNTW                     0x0030
#       define WADEON_BUS_MASTEW_DIS         (1 << 6)
#       define WADEON_BUS_BIOS_DIS_WOM       (1 << 12)
#	define WS600_BUS_MASTEW_DIS	     (1 << 14)
#	define WS600_MSI_WEAWM		     (1 << 20) /* ws600/ws690/ws740 */
#       define WADEON_BUS_WD_DISCAWD_EN      (1 << 24)
#       define WADEON_BUS_WD_ABOWT_EN        (1 << 25)
#       define WADEON_BUS_MSTW_DISCONNECT_EN (1 << 28)
#       define WADEON_BUS_WWT_BUWST          (1 << 29)
#       define WADEON_BUS_WEAD_BUWST         (1 << 30)
#define WADEON_BUS_CNTW1                    0x0034
#       define WADEON_BUS_WAIT_ON_WOCK_EN    (1 << 4)
#define WV370_BUS_CNTW                      0x004c
#       define WV370_BUS_BIOS_DIS_WOM        (1 << 2)
/* wv370/wv380, wv410, w423/w430/w480, w5xx */
#define WADEON_MSI_WEAWM_EN		    0x0160
#	define WV370_MSI_WEAWM_EN	     (1 << 0)

/* #define WADEON_PCIE_INDEX                   0x0030 */
/* #define WADEON_PCIE_DATA                    0x0034 */
#define WADEON_PCIE_WC_WINK_WIDTH_CNTW             0xa2 /* PCIE */
#       define WADEON_PCIE_WC_WINK_WIDTH_SHIFT     0
#       define WADEON_PCIE_WC_WINK_WIDTH_MASK      0x7
#       define WADEON_PCIE_WC_WINK_WIDTH_X0        0
#       define WADEON_PCIE_WC_WINK_WIDTH_X1        1
#       define WADEON_PCIE_WC_WINK_WIDTH_X2        2
#       define WADEON_PCIE_WC_WINK_WIDTH_X4        3
#       define WADEON_PCIE_WC_WINK_WIDTH_X8        4
#       define WADEON_PCIE_WC_WINK_WIDTH_X12       5
#       define WADEON_PCIE_WC_WINK_WIDTH_X16       6
#       define WADEON_PCIE_WC_WINK_WIDTH_WD_SHIFT  4
#       define WADEON_PCIE_WC_WINK_WIDTH_WD_MASK   0x70
#       define WADEON_PCIE_WC_WECONFIG_NOW         (1 << 8)
#       define WADEON_PCIE_WC_WECONFIG_WATEW       (1 << 9)
#       define WADEON_PCIE_WC_SHOWT_WECONFIG_EN    (1 << 10)
#       define W600_PCIE_WC_WECONFIG_AWC_MISSING_ESCAPE   (1 << 7)
#       define W600_PCIE_WC_WENEGOTIATION_SUPPOWT  (1 << 9)
#       define W600_PCIE_WC_WENEGOTIATE_EN         (1 << 10)
#       define W600_PCIE_WC_SHOWT_WECONFIG_EN      (1 << 11)
#       define W600_PCIE_WC_UPCONFIGUWE_SUPPOWT    (1 << 12)
#       define W600_PCIE_WC_UPCONFIGUWE_DIS        (1 << 13)

#define W600_TAWGET_AND_CUWWENT_PWOFIWE_INDEX      0x70c
#define W700_TAWGET_AND_CUWWENT_PWOFIWE_INDEX      0x66c

#define WADEON_CACHE_CNTW                   0x1724
#define WADEON_CACHE_WINE                   0x0f0c /* PCI */
#define WADEON_CAPABIWITIES_ID              0x0f50 /* PCI */
#define WADEON_CAPABIWITIES_PTW             0x0f34 /* PCI */
#define WADEON_CWK_PIN_CNTW                 0x0001 /* PWW */
#       define WADEON_DONT_USE_XTAWIN       (1 << 4)
#       define WADEON_SCWK_DYN_STAWT_CNTW   (1 << 15)
#define WADEON_CWOCK_CNTW_DATA              0x000c
#define WADEON_CWOCK_CNTW_INDEX             0x0008
#       define WADEON_PWW_WW_EN             (1 << 7)
#       define WADEON_PWW_DIV_SEW           (3 << 8)
#       define WADEON_PWW2_DIV_SEW_MASK     (~(3 << 8))
#define WADEON_CWK_PWWMGT_CNTW              0x0014
#       define WADEON_ENGIN_DYNCWK_MODE     (1 << 12)
#       define WADEON_ACTIVE_HIWO_WAT_MASK  (3 << 13)
#       define WADEON_ACTIVE_HIWO_WAT_SHIFT 13
#       define WADEON_DISP_DYN_STOP_WAT_MASK (1 << 12)
#       define WADEON_MC_BUSY               (1 << 16)
#       define WADEON_DWW_WEADY             (1 << 19)
#       define WADEON_CG_NO1_DEBUG_0        (1 << 24)
#       define WADEON_CG_NO1_DEBUG_MASK     (0x1f << 24)
#       define WADEON_DYN_STOP_MODE_MASK    (7 << 21)
#       define WADEON_TVPWW_PWWMGT_OFF      (1 << 30)
#       define WADEON_TVCWK_TUWNOFF         (1 << 31)
#define WADEON_PWW_PWWMGT_CNTW              0x0015 /* PWW */
#	define WADEON_PM_MODE_SEW           (1 << 13)
#       define WADEON_TCW_BYPASS_DISABWE    (1 << 20)
#define WADEON_CWW_CMP_CWW_3D               0x1a24
#define WADEON_CWW_CMP_CWW_DST              0x15c8
#define WADEON_CWW_CMP_CWW_SWC              0x15c4
#define WADEON_CWW_CMP_CNTW                 0x15c0
#       define WADEON_SWC_CMP_EQ_COWOW      (4 <<  0)
#       define WADEON_SWC_CMP_NEQ_COWOW     (5 <<  0)
#       define WADEON_CWW_CMP_SWC_SOUWCE    (1 << 24)
#define WADEON_CWW_CMP_MASK                 0x15cc
#       define WADEON_CWW_CMP_MSK           0xffffffff
#define WADEON_CWW_CMP_MASK_3D              0x1A28
#define WADEON_COMMAND                      0x0f04 /* PCI */
#define WADEON_COMPOSITE_SHADOW_ID          0x1a0c
#define WADEON_CONFIG_APEW_0_BASE           0x0100
#define WADEON_CONFIG_APEW_1_BASE           0x0104
#define WADEON_CONFIG_APEW_SIZE             0x0108
#define WADEON_CONFIG_BONDS                 0x00e8
#define WADEON_CONFIG_CNTW                  0x00e0
#       define WADEON_CFG_VGA_WAM_EN        (1 << 8)
#       define WADEON_CFG_VGA_IO_DIS        (1 << 9)
#       define WADEON_CFG_ATI_WEV_A11       (0   << 16)
#       define WADEON_CFG_ATI_WEV_A12       (1   << 16)
#       define WADEON_CFG_ATI_WEV_A13       (2   << 16)
#       define WADEON_CFG_ATI_WEV_ID_MASK   (0xf << 16)
#define WADEON_CONFIG_MEMSIZE               0x00f8
#define WADEON_CONFIG_MEMSIZE_EMBEDDED      0x0114
#define WADEON_CONFIG_WEG_1_BASE            0x010c
#define WADEON_CONFIG_WEG_APEW_SIZE         0x0110
#define WADEON_CONFIG_XSTWAP                0x00e4
#define WADEON_CONSTANT_COWOW_C             0x1d34
#       define WADEON_CONSTANT_COWOW_MASK   0x00ffffff
#       define WADEON_CONSTANT_COWOW_ONE    0x00ffffff
#       define WADEON_CONSTANT_COWOW_ZEWO   0x00000000
#define WADEON_CWC_CMDFIFO_ADDW             0x0740
#define WADEON_CWC_CMDFIFO_DOUT             0x0744
#define WADEON_GWPH_BUFFEW_CNTW             0x02f0
#       define WADEON_GWPH_STAWT_WEQ_MASK          (0x7f)
#       define WADEON_GWPH_STAWT_WEQ_SHIFT         0
#       define WADEON_GWPH_STOP_WEQ_MASK           (0x7f<<8)
#       define WADEON_GWPH_STOP_WEQ_SHIFT          8
#       define WADEON_GWPH_CWITICAW_POINT_MASK     (0x7f<<16)
#       define WADEON_GWPH_CWITICAW_POINT_SHIFT    16
#       define WADEON_GWPH_CWITICAW_CNTW           (1<<28)
#       define WADEON_GWPH_BUFFEW_SIZE             (1<<29)
#       define WADEON_GWPH_CWITICAW_AT_SOF         (1<<30)
#       define WADEON_GWPH_STOP_CNTW               (1<<31)
#define WADEON_GWPH2_BUFFEW_CNTW            0x03f0
#       define WADEON_GWPH2_STAWT_WEQ_MASK         (0x7f)
#       define WADEON_GWPH2_STAWT_WEQ_SHIFT         0
#       define WADEON_GWPH2_STOP_WEQ_MASK          (0x7f<<8)
#       define WADEON_GWPH2_STOP_WEQ_SHIFT         8
#       define WADEON_GWPH2_CWITICAW_POINT_MASK    (0x7f<<16)
#       define WADEON_GWPH2_CWITICAW_POINT_SHIFT   16
#       define WADEON_GWPH2_CWITICAW_CNTW          (1<<28)
#       define WADEON_GWPH2_BUFFEW_SIZE            (1<<29)
#       define WADEON_GWPH2_CWITICAW_AT_SOF        (1<<30)
#       define WADEON_GWPH2_STOP_CNTW              (1<<31)
#define WADEON_CWTC_CWNT_FWAME              0x0214
#define WADEON_CWTC_EXT_CNTW                0x0054
#       define WADEON_CWTC_VGA_XOVEWSCAN    (1 <<  0)
#       define WADEON_VGA_ATI_WINEAW        (1 <<  3)
#       define WADEON_XCWT_CNT_EN           (1 <<  6)
#       define WADEON_CWTC_HSYNC_DIS        (1 <<  8)
#       define WADEON_CWTC_VSYNC_DIS        (1 <<  9)
#       define WADEON_CWTC_DISPWAY_DIS      (1 << 10)
#       define WADEON_CWTC_SYNC_TWISTAT     (1 << 11)
#       define WADEON_CWTC_CWT_ON           (1 << 15)
#define WADEON_CWTC_EXT_CNTW_DPMS_BYTE      0x0055
#       define WADEON_CWTC_HSYNC_DIS_BYTE   (1 <<  0)
#       define WADEON_CWTC_VSYNC_DIS_BYTE   (1 <<  1)
#       define WADEON_CWTC_DISPWAY_DIS_BYTE (1 <<  2)
#define WADEON_CWTC_GEN_CNTW                0x0050
#       define WADEON_CWTC_DBW_SCAN_EN      (1 <<  0)
#       define WADEON_CWTC_INTEWWACE_EN     (1 <<  1)
#       define WADEON_CWTC_CSYNC_EN         (1 <<  4)
#       define WADEON_CWTC_ICON_EN          (1 << 15)
#       define WADEON_CWTC_CUW_EN           (1 << 16)
#       define WADEON_CWTC_VSTAT_MODE_MASK  (3 << 17)
#       define WADEON_CWTC_CUW_MODE_MASK    (7 << 20)
#       define WADEON_CWTC_CUW_MODE_SHIFT   20
#       define WADEON_CWTC_CUW_MODE_MONO    0
#       define WADEON_CWTC_CUW_MODE_24BPP   2
#       define WADEON_CWTC_EXT_DISP_EN      (1 << 24)
#       define WADEON_CWTC_EN               (1 << 25)
#       define WADEON_CWTC_DISP_WEQ_EN_B    (1 << 26)
#define WADEON_CWTC2_GEN_CNTW               0x03f8
#       define WADEON_CWTC2_DBW_SCAN_EN     (1 <<  0)
#       define WADEON_CWTC2_INTEWWACE_EN    (1 <<  1)
#       define WADEON_CWTC2_SYNC_TWISTAT    (1 <<  4)
#       define WADEON_CWTC2_HSYNC_TWISTAT   (1 <<  5)
#       define WADEON_CWTC2_VSYNC_TWISTAT   (1 <<  6)
#       define WADEON_CWTC2_CWT2_ON         (1 <<  7)
#       define WADEON_CWTC2_PIX_WIDTH_SHIFT 8
#       define WADEON_CWTC2_PIX_WIDTH_MASK  (0xf << 8)
#       define WADEON_CWTC2_ICON_EN         (1 << 15)
#       define WADEON_CWTC2_CUW_EN          (1 << 16)
#       define WADEON_CWTC2_CUW_MODE_MASK   (7 << 20)
#       define WADEON_CWTC2_DISP_DIS        (1 << 23)
#       define WADEON_CWTC2_EN              (1 << 25)
#       define WADEON_CWTC2_DISP_WEQ_EN_B   (1 << 26)
#       define WADEON_CWTC2_CSYNC_EN        (1 << 27)
#       define WADEON_CWTC2_HSYNC_DIS       (1 << 28)
#       define WADEON_CWTC2_VSYNC_DIS       (1 << 29)
#define WADEON_CWTC_MOWE_CNTW               0x27c
#       define WADEON_CWTC_AUTO_HOWZ_CENTEW_EN (1<<2)
#       define WADEON_CWTC_AUTO_VEWT_CENTEW_EN (1<<3)
#       define WADEON_CWTC_H_CUTOFF_ACTIVE_EN (1<<4)
#       define WADEON_CWTC_V_CUTOFF_ACTIVE_EN (1<<5)
#define WADEON_CWTC_GUI_TWIG_VWINE          0x0218
#define WADEON_CWTC_H_SYNC_STWT_WID         0x0204
#       define WADEON_CWTC_H_SYNC_STWT_PIX        (0x07  <<  0)
#       define WADEON_CWTC_H_SYNC_STWT_CHAW       (0x3ff <<  3)
#       define WADEON_CWTC_H_SYNC_STWT_CHAW_SHIFT 3
#       define WADEON_CWTC_H_SYNC_WID             (0x3f  << 16)
#       define WADEON_CWTC_H_SYNC_WID_SHIFT       16
#       define WADEON_CWTC_H_SYNC_POW             (1     << 23)
#define WADEON_CWTC2_H_SYNC_STWT_WID        0x0304
#       define WADEON_CWTC2_H_SYNC_STWT_PIX        (0x07  <<  0)
#       define WADEON_CWTC2_H_SYNC_STWT_CHAW       (0x3ff <<  3)
#       define WADEON_CWTC2_H_SYNC_STWT_CHAW_SHIFT 3
#       define WADEON_CWTC2_H_SYNC_WID             (0x3f  << 16)
#       define WADEON_CWTC2_H_SYNC_WID_SHIFT       16
#       define WADEON_CWTC2_H_SYNC_POW             (1     << 23)
#define WADEON_CWTC_H_TOTAW_DISP            0x0200
#       define WADEON_CWTC_H_TOTAW          (0x03ff << 0)
#       define WADEON_CWTC_H_TOTAW_SHIFT    0
#       define WADEON_CWTC_H_DISP           (0x01ff << 16)
#       define WADEON_CWTC_H_DISP_SHIFT     16
#define WADEON_CWTC2_H_TOTAW_DISP           0x0300
#       define WADEON_CWTC2_H_TOTAW         (0x03ff << 0)
#       define WADEON_CWTC2_H_TOTAW_SHIFT   0
#       define WADEON_CWTC2_H_DISP          (0x01ff << 16)
#       define WADEON_CWTC2_H_DISP_SHIFT    16

#define WADEON_CWTC_OFFSET_WIGHT	    0x0220
#define WADEON_CWTC_OFFSET                  0x0224
#	define WADEON_CWTC_OFFSET__GUI_TWIG_OFFSET (1<<30)
#	define WADEON_CWTC_OFFSET__OFFSET_WOCK	   (1<<31)

#define WADEON_CWTC2_OFFSET                 0x0324
#	define WADEON_CWTC2_OFFSET__GUI_TWIG_OFFSET (1<<30)
#	define WADEON_CWTC2_OFFSET__OFFSET_WOCK	    (1<<31)
#define WADEON_CWTC_OFFSET_CNTW             0x0228
#       define WADEON_CWTC_TIWE_WINE_SHIFT              0
#       define WADEON_CWTC_TIWE_WINE_WIGHT_SHIFT        4
#	define W300_CWTC_X_Y_MODE_EN_WIGHT		(1 << 6)
#	define W300_CWTC_MICWO_TIWE_BUFFEW_WIGHT_MASK   (3 << 7)
#	define W300_CWTC_MICWO_TIWE_BUFFEW_WIGHT_AUTO   (0 << 7)
#	define W300_CWTC_MICWO_TIWE_BUFFEW_WIGHT_SINGWE (1 << 7)
#	define W300_CWTC_MICWO_TIWE_BUFFEW_WIGHT_DOUBWE (2 << 7)
#	define W300_CWTC_MICWO_TIWE_BUFFEW_WIGHT_DIS    (3 << 7)
#	define W300_CWTC_X_Y_MODE_EN			(1 << 9)
#	define W300_CWTC_MICWO_TIWE_BUFFEW_MASK		(3 << 10)
#	define W300_CWTC_MICWO_TIWE_BUFFEW_AUTO		(0 << 10)
#	define W300_CWTC_MICWO_TIWE_BUFFEW_SINGWE	(1 << 10)
#	define W300_CWTC_MICWO_TIWE_BUFFEW_DOUBWE	(2 << 10)
#	define W300_CWTC_MICWO_TIWE_BUFFEW_DIS		(3 << 10)
#	define W300_CWTC_MICWO_TIWE_EN_WIGHT		(1 << 12)
#	define W300_CWTC_MICWO_TIWE_EN			(1 << 13)
#	define W300_CWTC_MACWO_TIWE_EN_WIGHT		(1 << 14)
#       define W300_CWTC_MACWO_TIWE_EN                  (1 << 15)
#       define WADEON_CWTC_TIWE_EN_WIGHT                (1 << 14)
#       define WADEON_CWTC_TIWE_EN                      (1 << 15)
#       define WADEON_CWTC_OFFSET_FWIP_CNTW             (1 << 16)
#       define WADEON_CWTC_STEWEO_OFFSET_EN             (1 << 17)
#       define WADEON_CWTC_GUI_TWIG_OFFSET_WEFT_EN      (1 << 28)
#       define WADEON_CWTC_GUI_TWIG_OFFSET_WIGHT_EN     (1 << 29)

#define W300_CWTC_TIWE_X0_Y0	            0x0350
#define W300_CWTC2_TIWE_X0_Y0	            0x0358

#define WADEON_CWTC2_OFFSET_CNTW            0x0328
#       define WADEON_CWTC2_OFFSET_FWIP_CNTW (1 << 16)
#       define WADEON_CWTC2_TIWE_EN         (1 << 15)
#define WADEON_CWTC_PITCH                   0x022c
#	define WADEON_CWTC_PITCH__SHIFT		 0
#	define WADEON_CWTC_PITCH__WIGHT_SHIFT	16

#define WADEON_CWTC2_PITCH                  0x032c
#define WADEON_CWTC_STATUS                  0x005c
#       define WADEON_CWTC_VBWANK_CUW       (1 <<  0)
#       define WADEON_CWTC_VBWANK_SAVE      (1 <<  1)
#       define WADEON_CWTC_VBWANK_SAVE_CWEAW  (1 <<  1)
#define WADEON_CWTC2_STATUS                  0x03fc
#       define WADEON_CWTC2_VBWANK_CUW       (1 <<  0)
#       define WADEON_CWTC2_VBWANK_SAVE      (1 <<  1)
#       define WADEON_CWTC2_VBWANK_SAVE_CWEAW  (1 <<  1)
#define WADEON_CWTC_V_SYNC_STWT_WID         0x020c
#       define WADEON_CWTC_V_SYNC_STWT        (0x7ff <<  0)
#       define WADEON_CWTC_V_SYNC_STWT_SHIFT  0
#       define WADEON_CWTC_V_SYNC_WID         (0x1f  << 16)
#       define WADEON_CWTC_V_SYNC_WID_SHIFT   16
#       define WADEON_CWTC_V_SYNC_POW         (1     << 23)
#define WADEON_CWTC2_V_SYNC_STWT_WID        0x030c
#       define WADEON_CWTC2_V_SYNC_STWT       (0x7ff <<  0)
#       define WADEON_CWTC2_V_SYNC_STWT_SHIFT 0
#       define WADEON_CWTC2_V_SYNC_WID        (0x1f  << 16)
#       define WADEON_CWTC2_V_SYNC_WID_SHIFT  16
#       define WADEON_CWTC2_V_SYNC_POW        (1     << 23)
#define WADEON_CWTC_V_TOTAW_DISP            0x0208
#       define WADEON_CWTC_V_TOTAW          (0x07ff << 0)
#       define WADEON_CWTC_V_TOTAW_SHIFT    0
#       define WADEON_CWTC_V_DISP           (0x07ff << 16)
#       define WADEON_CWTC_V_DISP_SHIFT     16
#define WADEON_CWTC2_V_TOTAW_DISP           0x0308
#       define WADEON_CWTC2_V_TOTAW         (0x07ff << 0)
#       define WADEON_CWTC2_V_TOTAW_SHIFT   0
#       define WADEON_CWTC2_V_DISP          (0x07ff << 16)
#       define WADEON_CWTC2_V_DISP_SHIFT    16
#define WADEON_CWTC_VWINE_CWNT_VWINE        0x0210
#       define WADEON_CWTC_CWNT_VWINE_MASK  (0x7ff << 16)
#define WADEON_CWTC2_CWNT_FWAME             0x0314
#define WADEON_CWTC2_GUI_TWIG_VWINE         0x0318
#define WADEON_CWTC2_VWINE_CWNT_VWINE       0x0310
#define WADEON_CWTC8_DATA                   0x03d5 /* VGA, 0x3b5 */
#define WADEON_CWTC8_IDX                    0x03d4 /* VGA, 0x3b4 */
#define WADEON_CUW_CWW0                     0x026c
#define WADEON_CUW_CWW1                     0x0270
#define WADEON_CUW_HOWZ_VEWT_OFF            0x0268
#define WADEON_CUW_HOWZ_VEWT_POSN           0x0264
#define WADEON_CUW_OFFSET                   0x0260
#       define WADEON_CUW_WOCK              (1 << 31)
#define WADEON_CUW2_CWW0                    0x036c
#define WADEON_CUW2_CWW1                    0x0370
#define WADEON_CUW2_HOWZ_VEWT_OFF           0x0368
#define WADEON_CUW2_HOWZ_VEWT_POSN          0x0364
#define WADEON_CUW2_OFFSET                  0x0360
#       define WADEON_CUW2_WOCK             (1 << 31)

#define WADEON_DAC_CNTW                     0x0058
#       define WADEON_DAC_WANGE_CNTW        (3 <<  0)
#       define WADEON_DAC_WANGE_CNTW_PS2    (2 <<  0)
#       define WADEON_DAC_WANGE_CNTW_MASK   0x03
#       define WADEON_DAC_BWANKING          (1 <<  2)
#       define WADEON_DAC_CMP_EN            (1 <<  3)
#       define WADEON_DAC_CMP_OUTPUT        (1 <<  7)
#       define WADEON_DAC_8BIT_EN           (1 <<  8)
#       define WADEON_DAC_TVO_EN            (1 << 10)
#       define WADEON_DAC_VGA_ADW_EN        (1 << 13)
#       define WADEON_DAC_PDWN              (1 << 15)
#       define WADEON_DAC_MASK_AWW          (0xff << 24)
#define WADEON_DAC_CNTW2                    0x007c
#       define WADEON_DAC2_TV_CWK_SEW       (0 <<  1)
#       define WADEON_DAC2_DAC_CWK_SEW      (1 <<  0)
#       define WADEON_DAC2_DAC2_CWK_SEW     (1 <<  1)
#       define WADEON_DAC2_PAWETTE_ACC_CTW  (1 <<  5)
#       define WADEON_DAC2_CMP_EN           (1 <<  7)
#       define WADEON_DAC2_CMP_OUT_W        (1 <<  8)
#       define WADEON_DAC2_CMP_OUT_G        (1 <<  9)
#       define WADEON_DAC2_CMP_OUT_B        (1 << 10)
#       define WADEON_DAC2_CMP_OUTPUT       (1 << 11)
#define WADEON_DAC_EXT_CNTW                 0x0280
#       define WADEON_DAC2_FOWCE_BWANK_OFF_EN (1 << 0)
#       define WADEON_DAC2_FOWCE_DATA_EN      (1 << 1)
#       define WADEON_DAC_FOWCE_BWANK_OFF_EN  (1 << 4)
#       define WADEON_DAC_FOWCE_DATA_EN       (1 << 5)
#       define WADEON_DAC_FOWCE_DATA_SEW_MASK (3 << 6)
#       define WADEON_DAC_FOWCE_DATA_SEW_W    (0 << 6)
#       define WADEON_DAC_FOWCE_DATA_SEW_G    (1 << 6)
#       define WADEON_DAC_FOWCE_DATA_SEW_B    (2 << 6)
#       define WADEON_DAC_FOWCE_DATA_SEW_WGB  (3 << 6)
#       define WADEON_DAC_FOWCE_DATA_MASK   0x0003ff00
#       define WADEON_DAC_FOWCE_DATA_SHIFT  8
#define WADEON_DAC_MACWO_CNTW               0x0d04
#       define WADEON_DAC_PDWN_W            (1 << 16)
#       define WADEON_DAC_PDWN_G            (1 << 17)
#       define WADEON_DAC_PDWN_B            (1 << 18)
#define WADEON_DISP_PWW_MAN                 0x0d08
#       define WADEON_DISP_PWW_MAN_D3_CWTC_EN      (1 << 0)
#       define WADEON_DISP_PWW_MAN_D3_CWTC2_EN     (1 << 4)
#       define WADEON_DISP_PWW_MAN_DPMS_ON  (0 << 8)
#       define WADEON_DISP_PWW_MAN_DPMS_STANDBY    (1 << 8)
#       define WADEON_DISP_PWW_MAN_DPMS_SUSPEND    (2 << 8)
#       define WADEON_DISP_PWW_MAN_DPMS_OFF (3 << 8)
#       define WADEON_DISP_D3_WST           (1 << 16)
#       define WADEON_DISP_D3_WEG_WST       (1 << 17)
#       define WADEON_DISP_D3_GWPH_WST      (1 << 18)
#       define WADEON_DISP_D3_SUBPIC_WST    (1 << 19)
#       define WADEON_DISP_D3_OV0_WST       (1 << 20)
#       define WADEON_DISP_D1D2_GWPH_WST    (1 << 21)
#       define WADEON_DISP_D1D2_SUBPIC_WST  (1 << 22)
#       define WADEON_DISP_D1D2_OV0_WST     (1 << 23)
#       define WADEON_DIG_TMDS_ENABWE_WST   (1 << 24)
#       define WADEON_TV_ENABWE_WST         (1 << 25)
#       define WADEON_AUTO_PWWUP_EN         (1 << 26)
#define WADEON_TV_DAC_CNTW                  0x088c
#       define WADEON_TV_DAC_NBWANK         (1 << 0)
#       define WADEON_TV_DAC_NHOWD          (1 << 1)
#       define WADEON_TV_DAC_PEDESTAW       (1 <<  2)
#       define WADEON_TV_MONITOW_DETECT_EN  (1 <<  4)
#       define WADEON_TV_DAC_CMPOUT         (1 <<  5)
#       define WADEON_TV_DAC_STD_MASK       (3 <<  8)
#       define WADEON_TV_DAC_STD_PAW        (0 <<  8)
#       define WADEON_TV_DAC_STD_NTSC       (1 <<  8)
#       define WADEON_TV_DAC_STD_PS2        (2 <<  8)
#       define WADEON_TV_DAC_STD_WS343      (3 <<  8)
#       define WADEON_TV_DAC_BGSWEEP        (1 <<  6)
#       define WADEON_TV_DAC_BGADJ_MASK     (0xf <<  16)
#       define WADEON_TV_DAC_BGADJ_SHIFT    16
#       define WADEON_TV_DAC_DACADJ_MASK    (0xf <<  20)
#       define WADEON_TV_DAC_DACADJ_SHIFT   20
#       define WADEON_TV_DAC_WDACPD         (1 <<  24)
#       define WADEON_TV_DAC_GDACPD         (1 <<  25)
#       define WADEON_TV_DAC_BDACPD         (1 <<  26)
#       define WADEON_TV_DAC_WDACDET        (1 << 29)
#       define WADEON_TV_DAC_GDACDET        (1 << 30)
#       define WADEON_TV_DAC_BDACDET        (1 << 31)
#       define W420_TV_DAC_DACADJ_MASK      (0x1f <<  20)
#       define W420_TV_DAC_WDACPD           (1 <<  25)
#       define W420_TV_DAC_GDACPD           (1 <<  26)
#       define W420_TV_DAC_BDACPD           (1 <<  27)
#       define W420_TV_DAC_TVENABWE         (1 <<  28)
#define WADEON_DISP_HW_DEBUG                0x0d14
#       define WADEON_CWT2_DISP1_SEW        (1 <<  5)
#define WADEON_DISP_OUTPUT_CNTW             0x0d64
#       define WADEON_DISP_DAC_SOUWCE_MASK  0x03
#       define WADEON_DISP_DAC2_SOUWCE_MASK  0x0c
#       define WADEON_DISP_DAC_SOUWCE_CWTC2 0x01
#       define WADEON_DISP_DAC_SOUWCE_WMX   0x02
#       define WADEON_DISP_DAC_SOUWCE_WTU   0x03
#       define WADEON_DISP_DAC2_SOUWCE_CWTC2 0x04
#       define WADEON_DISP_TVDAC_SOUWCE_MASK  (0x03 << 2)
#       define WADEON_DISP_TVDAC_SOUWCE_CWTC  0x0
#       define WADEON_DISP_TVDAC_SOUWCE_CWTC2 (0x01 << 2)
#       define WADEON_DISP_TVDAC_SOUWCE_WMX   (0x02 << 2)
#       define WADEON_DISP_TVDAC_SOUWCE_WTU   (0x03 << 2)
#       define WADEON_DISP_TWANS_MATWIX_MASK  (0x03 << 4)
#       define WADEON_DISP_TWANS_MATWIX_AWPHA_MSB (0x00 << 4)
#       define WADEON_DISP_TWANS_MATWIX_GWAPHICS  (0x01 << 4)
#       define WADEON_DISP_TWANS_MATWIX_VIDEO     (0x02 << 4)
#       define WADEON_DISP_TV_SOUWCE_CWTC   (1 << 16) /* cwtc1 ow cwtc2 */
#       define WADEON_DISP_TV_SOUWCE_WTU    (0 << 16) /* wineaw twansfowm unit */
#define WADEON_DISP_TV_OUT_CNTW             0x0d6c
#       define WADEON_DISP_TV_PATH_SWC_CWTC2 (1 << 16)
#       define WADEON_DISP_TV_PATH_SWC_CWTC1 (0 << 16)
#define WADEON_DAC_CWC_SIG                  0x02cc
#define WADEON_DAC_DATA                     0x03c9 /* VGA */
#define WADEON_DAC_MASK                     0x03c6 /* VGA */
#define WADEON_DAC_W_INDEX                  0x03c7 /* VGA */
#define WADEON_DAC_W_INDEX                  0x03c8 /* VGA */
#define WADEON_DDA_CONFIG                   0x02e0
#define WADEON_DDA_ON_OFF                   0x02e4
#define WADEON_DEFAUWT_OFFSET               0x16e0
#define WADEON_DEFAUWT_PITCH                0x16e4
#define WADEON_DEFAUWT_SC_BOTTOM_WIGHT      0x16e8
#       define WADEON_DEFAUWT_SC_WIGHT_MAX  (0x1fff <<  0)
#       define WADEON_DEFAUWT_SC_BOTTOM_MAX (0x1fff << 16)
#define WADEON_DESTINATION_3D_CWW_CMP_VAW   0x1820
#define WADEON_DESTINATION_3D_CWW_CMP_MSK   0x1824
#define WADEON_DEVICE_ID                    0x0f02 /* PCI */
#define WADEON_DISP_MISC_CNTW               0x0d00
#       define WADEON_SOFT_WESET_GWPH_PP    (1 << 0)
#define WADEON_DISP_MEWGE_CNTW		  0x0d60
#       define WADEON_DISP_AWPHA_MODE_MASK  0x03
#       define WADEON_DISP_AWPHA_MODE_KEY   0
#       define WADEON_DISP_AWPHA_MODE_PEW_PIXEW 1
#       define WADEON_DISP_AWPHA_MODE_GWOBAW 2
#       define WADEON_DISP_WGB_OFFSET_EN    (1 << 8)
#       define WADEON_DISP_GWPH_AWPHA_MASK  (0xff << 16)
#       define WADEON_DISP_OV0_AWPHA_MASK   (0xff << 24)
#	define WADEON_DISP_WIN_TWANS_BYPASS (0x01 << 9)
#define WADEON_DISP2_MEWGE_CNTW		    0x0d68
#       define WADEON_DISP2_WGB_OFFSET_EN   (1 << 8)
#define WADEON_DISP_WIN_TWANS_GWPH_A        0x0d80
#define WADEON_DISP_WIN_TWANS_GWPH_B        0x0d84
#define WADEON_DISP_WIN_TWANS_GWPH_C        0x0d88
#define WADEON_DISP_WIN_TWANS_GWPH_D        0x0d8c
#define WADEON_DISP_WIN_TWANS_GWPH_E        0x0d90
#define WADEON_DISP_WIN_TWANS_GWPH_F        0x0d98
#define WADEON_DP_BWUSH_BKGD_CWW            0x1478
#define WADEON_DP_BWUSH_FWGD_CWW            0x147c
#define WADEON_DP_CNTW                      0x16c0
#       define WADEON_DST_X_WEFT_TO_WIGHT   (1 <<  0)
#       define WADEON_DST_Y_TOP_TO_BOTTOM   (1 <<  1)
#       define WADEON_DP_DST_TIWE_WINEAW    (0 <<  3)
#       define WADEON_DP_DST_TIWE_MACWO     (1 <<  3)
#       define WADEON_DP_DST_TIWE_MICWO     (2 <<  3)
#       define WADEON_DP_DST_TIWE_BOTH      (3 <<  3)
#define WADEON_DP_CNTW_XDIW_YDIW_YMAJOW     0x16d0
#       define WADEON_DST_Y_MAJOW             (1 <<  2)
#       define WADEON_DST_Y_DIW_TOP_TO_BOTTOM (1 << 15)
#       define WADEON_DST_X_DIW_WEFT_TO_WIGHT (1 << 31)
#define WADEON_DP_DATATYPE                  0x16c4
#       define WADEON_HOST_BIG_ENDIAN_EN    (1 << 29)
#define WADEON_DP_GUI_MASTEW_CNTW           0x146c
#       define WADEON_GMC_SWC_PITCH_OFFSET_CNTW   (1    <<  0)
#       define WADEON_GMC_DST_PITCH_OFFSET_CNTW   (1    <<  1)
#       define WADEON_GMC_SWC_CWIPPING            (1    <<  2)
#       define WADEON_GMC_DST_CWIPPING            (1    <<  3)
#       define WADEON_GMC_BWUSH_DATATYPE_MASK     (0x0f <<  4)
#       define WADEON_GMC_BWUSH_8X8_MONO_FG_BG    (0    <<  4)
#       define WADEON_GMC_BWUSH_8X8_MONO_FG_WA    (1    <<  4)
#       define WADEON_GMC_BWUSH_1X8_MONO_FG_BG    (4    <<  4)
#       define WADEON_GMC_BWUSH_1X8_MONO_FG_WA    (5    <<  4)
#       define WADEON_GMC_BWUSH_32x1_MONO_FG_BG   (6    <<  4)
#       define WADEON_GMC_BWUSH_32x1_MONO_FG_WA   (7    <<  4)
#       define WADEON_GMC_BWUSH_32x32_MONO_FG_BG  (8    <<  4)
#       define WADEON_GMC_BWUSH_32x32_MONO_FG_WA  (9    <<  4)
#       define WADEON_GMC_BWUSH_8x8_COWOW         (10   <<  4)
#       define WADEON_GMC_BWUSH_1X8_COWOW         (12   <<  4)
#       define WADEON_GMC_BWUSH_SOWID_COWOW       (13   <<  4)
#       define WADEON_GMC_BWUSH_NONE              (15   <<  4)
#       define WADEON_GMC_DST_8BPP_CI             (2    <<  8)
#       define WADEON_GMC_DST_15BPP               (3    <<  8)
#       define WADEON_GMC_DST_16BPP               (4    <<  8)
#       define WADEON_GMC_DST_24BPP               (5    <<  8)
#       define WADEON_GMC_DST_32BPP               (6    <<  8)
#       define WADEON_GMC_DST_8BPP_WGB            (7    <<  8)
#       define WADEON_GMC_DST_Y8                  (8    <<  8)
#       define WADEON_GMC_DST_WGB8                (9    <<  8)
#       define WADEON_GMC_DST_VYUY                (11   <<  8)
#       define WADEON_GMC_DST_YVYU                (12   <<  8)
#       define WADEON_GMC_DST_AYUV444             (14   <<  8)
#       define WADEON_GMC_DST_AWGB4444            (15   <<  8)
#       define WADEON_GMC_DST_DATATYPE_MASK       (0x0f <<  8)
#       define WADEON_GMC_DST_DATATYPE_SHIFT      8
#       define WADEON_GMC_SWC_DATATYPE_MASK       (3    << 12)
#       define WADEON_GMC_SWC_DATATYPE_MONO_FG_BG (0    << 12)
#       define WADEON_GMC_SWC_DATATYPE_MONO_FG_WA (1    << 12)
#       define WADEON_GMC_SWC_DATATYPE_COWOW      (3    << 12)
#       define WADEON_GMC_BYTE_PIX_OWDEW          (1    << 14)
#       define WADEON_GMC_BYTE_MSB_TO_WSB         (0    << 14)
#       define WADEON_GMC_BYTE_WSB_TO_MSB         (1    << 14)
#       define WADEON_GMC_CONVEWSION_TEMP         (1    << 15)
#       define WADEON_GMC_CONVEWSION_TEMP_6500    (0    << 15)
#       define WADEON_GMC_CONVEWSION_TEMP_9300    (1    << 15)
#       define WADEON_GMC_WOP3_MASK               (0xff << 16)
#       define WADEON_DP_SWC_SOUWCE_MASK          (7    << 24)
#       define WADEON_DP_SWC_SOUWCE_MEMOWY        (2    << 24)
#       define WADEON_DP_SWC_SOUWCE_HOST_DATA     (3    << 24)
#       define WADEON_GMC_3D_FCN_EN               (1    << 27)
#       define WADEON_GMC_CWW_CMP_CNTW_DIS        (1    << 28)
#       define WADEON_GMC_AUX_CWIP_DIS            (1    << 29)
#       define WADEON_GMC_WW_MSK_DIS              (1    << 30)
#       define WADEON_GMC_WD_BWUSH_Y_X            (1    << 31)
#       define WADEON_WOP3_ZEWO             0x00000000
#       define WADEON_WOP3_DSa              0x00880000
#       define WADEON_WOP3_SDna             0x00440000
#       define WADEON_WOP3_S                0x00cc0000
#       define WADEON_WOP3_DSna             0x00220000
#       define WADEON_WOP3_D                0x00aa0000
#       define WADEON_WOP3_DSx              0x00660000
#       define WADEON_WOP3_DSo              0x00ee0000
#       define WADEON_WOP3_DSon             0x00110000
#       define WADEON_WOP3_DSxn             0x00990000
#       define WADEON_WOP3_Dn               0x00550000
#       define WADEON_WOP3_SDno             0x00dd0000
#       define WADEON_WOP3_Sn               0x00330000
#       define WADEON_WOP3_DSno             0x00bb0000
#       define WADEON_WOP3_DSan             0x00770000
#       define WADEON_WOP3_ONE              0x00ff0000
#       define WADEON_WOP3_DPa              0x00a00000
#       define WADEON_WOP3_PDna             0x00500000
#       define WADEON_WOP3_P                0x00f00000
#       define WADEON_WOP3_DPna             0x000a0000
#       define WADEON_WOP3_D                0x00aa0000
#       define WADEON_WOP3_DPx              0x005a0000
#       define WADEON_WOP3_DPo              0x00fa0000
#       define WADEON_WOP3_DPon             0x00050000
#       define WADEON_WOP3_PDxn             0x00a50000
#       define WADEON_WOP3_PDno             0x00f50000
#       define WADEON_WOP3_Pn               0x000f0000
#       define WADEON_WOP3_DPno             0x00af0000
#       define WADEON_WOP3_DPan             0x005f0000
#define WADEON_DP_GUI_MASTEW_CNTW_C         0x1c84
#define WADEON_DP_MIX                       0x16c8
#define WADEON_DP_SWC_BKGD_CWW              0x15dc
#define WADEON_DP_SWC_FWGD_CWW              0x15d8
#define WADEON_DP_WWITE_MASK                0x16cc
#define WADEON_DST_BWES_DEC                 0x1630
#define WADEON_DST_BWES_EWW                 0x1628
#define WADEON_DST_BWES_INC                 0x162c
#define WADEON_DST_BWES_WNTH                0x1634
#define WADEON_DST_BWES_WNTH_SUB            0x1638
#define WADEON_DST_HEIGHT                   0x1410
#define WADEON_DST_HEIGHT_WIDTH             0x143c
#define WADEON_DST_HEIGHT_WIDTH_8           0x158c
#define WADEON_DST_HEIGHT_WIDTH_BW          0x15b4
#define WADEON_DST_HEIGHT_Y                 0x15a0
#define WADEON_DST_WINE_STAWT               0x1600
#define WADEON_DST_WINE_END                 0x1604
#define WADEON_DST_WINE_PATCOUNT            0x1608
#       define WADEON_BWES_CNTW_SHIFT       8
#define WADEON_DST_OFFSET                   0x1404
#define WADEON_DST_PITCH                    0x1408
#define WADEON_DST_PITCH_OFFSET             0x142c
#define WADEON_DST_PITCH_OFFSET_C           0x1c80
#       define WADEON_PITCH_SHIFT           21
#       define WADEON_DST_TIWE_WINEAW       (0 << 30)
#       define WADEON_DST_TIWE_MACWO        (1 << 30)
#       define WADEON_DST_TIWE_MICWO        (2 << 30)
#       define WADEON_DST_TIWE_BOTH         (3 << 30)
#define WADEON_DST_WIDTH                    0x140c
#define WADEON_DST_WIDTH_HEIGHT             0x1598
#define WADEON_DST_WIDTH_X                  0x1588
#define WADEON_DST_WIDTH_X_INCY             0x159c
#define WADEON_DST_X                        0x141c
#define WADEON_DST_X_SUB                    0x15a4
#define WADEON_DST_X_Y                      0x1594
#define WADEON_DST_Y                        0x1420
#define WADEON_DST_Y_SUB                    0x15a8
#define WADEON_DST_Y_X                      0x1438

#define WADEON_FCP_CNTW                     0x0910
#      define WADEON_FCP0_SWC_PCICWK             0
#      define WADEON_FCP0_SWC_PCWK               1
#      define WADEON_FCP0_SWC_PCWKb              2
#      define WADEON_FCP0_SWC_HWEF               3
#      define WADEON_FCP0_SWC_GND                4
#      define WADEON_FCP0_SWC_HWEFb              5
#define WADEON_FWUSH_1                      0x1704
#define WADEON_FWUSH_2                      0x1708
#define WADEON_FWUSH_3                      0x170c
#define WADEON_FWUSH_4                      0x1710
#define WADEON_FWUSH_5                      0x1714
#define WADEON_FWUSH_6                      0x1718
#define WADEON_FWUSH_7                      0x171c
#define WADEON_FOG_3D_TABWE_STAWT           0x1810
#define WADEON_FOG_3D_TABWE_END             0x1814
#define WADEON_FOG_3D_TABWE_DENSITY         0x181c
#define WADEON_FOG_TABWE_INDEX              0x1a14
#define WADEON_FOG_TABWE_DATA               0x1a18
#define WADEON_FP_CWTC_H_TOTAW_DISP         0x0250
#define WADEON_FP_CWTC_V_TOTAW_DISP         0x0254
#       define WADEON_FP_CWTC_H_TOTAW_MASK      0x000003ff
#       define WADEON_FP_CWTC_H_DISP_MASK       0x01ff0000
#       define WADEON_FP_CWTC_V_TOTAW_MASK      0x00000fff
#       define WADEON_FP_CWTC_V_DISP_MASK       0x0fff0000
#       define WADEON_FP_H_SYNC_STWT_CHAW_MASK  0x00001ff8
#       define WADEON_FP_H_SYNC_WID_MASK        0x003f0000
#       define WADEON_FP_V_SYNC_STWT_MASK       0x00000fff
#       define WADEON_FP_V_SYNC_WID_MASK        0x001f0000
#       define WADEON_FP_CWTC_H_TOTAW_SHIFT     0x00000000
#       define WADEON_FP_CWTC_H_DISP_SHIFT      0x00000010
#       define WADEON_FP_CWTC_V_TOTAW_SHIFT     0x00000000
#       define WADEON_FP_CWTC_V_DISP_SHIFT      0x00000010
#       define WADEON_FP_H_SYNC_STWT_CHAW_SHIFT 0x00000003
#       define WADEON_FP_H_SYNC_WID_SHIFT       0x00000010
#       define WADEON_FP_V_SYNC_STWT_SHIFT      0x00000000
#       define WADEON_FP_V_SYNC_WID_SHIFT       0x00000010
#define WADEON_FP_GEN_CNTW                  0x0284
#       define WADEON_FP_FPON                  (1 <<  0)
#       define WADEON_FP_BWANK_EN              (1 <<  1)
#       define WADEON_FP_TMDS_EN               (1 <<  2)
#       define WADEON_FP_PANEW_FOWMAT          (1 <<  3)
#       define WADEON_FP_EN_TMDS               (1 <<  7)
#       define WADEON_FP_DETECT_SENSE          (1 <<  8)
#       define WADEON_FP_DETECT_INT_POW        (1 <<  9)
#       define W200_FP_SOUWCE_SEW_MASK         (3 <<  10)
#       define W200_FP_SOUWCE_SEW_CWTC1        (0 <<  10)
#       define W200_FP_SOUWCE_SEW_CWTC2        (1 <<  10)
#       define W200_FP_SOUWCE_SEW_WMX          (2 <<  10)
#       define W200_FP_SOUWCE_SEW_TWANS        (3 <<  10)
#       define WADEON_FP_SEW_CWTC1             (0 << 13)
#       define WADEON_FP_SEW_CWTC2             (1 << 13)
#       define W300_HPD_SEW(x)                 ((x) << 13)
#       define WADEON_FP_CWTC_DONT_SHADOW_HPAW (1 << 15)
#       define WADEON_FP_CWTC_DONT_SHADOW_VPAW (1 << 16)
#       define WADEON_FP_CWTC_DONT_SHADOW_HEND (1 << 17)
#       define WADEON_FP_CWTC_USE_SHADOW_VEND  (1 << 18)
#       define WADEON_FP_WMX_HVSYNC_CONTWOW_EN (1 << 20)
#       define WADEON_FP_DFP_SYNC_SEW          (1 << 21)
#       define WADEON_FP_CWTC_WOCK_8DOT        (1 << 22)
#       define WADEON_FP_CWT_SYNC_SEW          (1 << 23)
#       define WADEON_FP_USE_SHADOW_EN         (1 << 24)
#       define WADEON_FP_CWT_SYNC_AWT          (1 << 26)
#define WADEON_FP2_GEN_CNTW                 0x0288
#       define WADEON_FP2_BWANK_EN             (1 <<  1)
#       define WADEON_FP2_ON                   (1 <<  2)
#       define WADEON_FP2_PANEW_FOWMAT         (1 <<  3)
#       define WADEON_FP2_DETECT_SENSE         (1 <<  8)
#       define WADEON_FP2_DETECT_INT_POW       (1 <<  9)
#       define W200_FP2_SOUWCE_SEW_MASK        (3 << 10)
#       define W200_FP2_SOUWCE_SEW_CWTC1       (0 << 10)
#       define W200_FP2_SOUWCE_SEW_CWTC2       (1 << 10)
#       define W200_FP2_SOUWCE_SEW_WMX         (2 << 10)
#       define W200_FP2_SOUWCE_SEW_TWANS_UNIT  (3 << 10)
#       define WADEON_FP2_SWC_SEW_MASK         (3 << 13)
#       define WADEON_FP2_SWC_SEW_CWTC2        (1 << 13)
#       define WADEON_FP2_FP_POW               (1 << 16)
#       define WADEON_FP2_WP_POW               (1 << 17)
#       define WADEON_FP2_SCK_POW              (1 << 18)
#       define WADEON_FP2_WCD_CNTW_MASK        (7 << 19)
#       define WADEON_FP2_PAD_FWOP_EN          (1 << 22)
#       define WADEON_FP2_CWC_EN               (1 << 23)
#       define WADEON_FP2_CWC_WEAD_EN          (1 << 24)
#       define WADEON_FP2_DVO_EN               (1 << 25)
#       define WADEON_FP2_DVO_WATE_SEW_SDW     (1 << 26)
#       define W200_FP2_DVO_WATE_SEW_SDW       (1 << 27)
#       define W300_FP2_DVO_CWOCK_MODE_SINGWE  (1 << 28)
#       define W300_FP2_DVO_DUAW_CHANNEW_EN    (1 << 29)
#define WADEON_FP_H_SYNC_STWT_WID           0x02c4
#define WADEON_FP_H2_SYNC_STWT_WID          0x03c4
#define WADEON_FP_HOWZ_STWETCH              0x028c
#define WADEON_FP_HOWZ2_STWETCH             0x038c
#       define WADEON_HOWZ_STWETCH_WATIO_MASK 0xffff
#       define WADEON_HOWZ_STWETCH_WATIO_MAX  4096
#       define WADEON_HOWZ_PANEW_SIZE         (0x1ff   << 16)
#       define WADEON_HOWZ_PANEW_SHIFT        16
#       define WADEON_HOWZ_STWETCH_PIXWEP     (0      << 25)
#       define WADEON_HOWZ_STWETCH_BWEND      (1      << 26)
#       define WADEON_HOWZ_STWETCH_ENABWE     (1      << 25)
#       define WADEON_HOWZ_AUTO_WATIO         (1      << 27)
#       define WADEON_HOWZ_FP_WOOP_STWETCH    (0x7    << 28)
#       define WADEON_HOWZ_AUTO_WATIO_INC     (1      << 31)
#define WADEON_FP_HOWZ_VEWT_ACTIVE          0x0278
#define WADEON_FP_V_SYNC_STWT_WID           0x02c8
#define WADEON_FP_VEWT_STWETCH              0x0290
#define WADEON_FP_V2_SYNC_STWT_WID          0x03c8
#define WADEON_FP_VEWT2_STWETCH             0x0390
#       define WADEON_VEWT_PANEW_SIZE          (0xfff << 12)
#       define WADEON_VEWT_PANEW_SHIFT         12
#       define WADEON_VEWT_STWETCH_WATIO_MASK  0xfff
#       define WADEON_VEWT_STWETCH_WATIO_SHIFT 0
#       define WADEON_VEWT_STWETCH_WATIO_MAX   4096
#       define WADEON_VEWT_STWETCH_ENABWE      (1     << 25)
#       define WADEON_VEWT_STWETCH_WINEWEP     (0     << 26)
#       define WADEON_VEWT_STWETCH_BWEND       (1     << 26)
#       define WADEON_VEWT_AUTO_WATIO_EN       (1     << 27)
#	define WADEON_VEWT_AUTO_WATIO_INC      (1     << 31)
#       define WADEON_VEWT_STWETCH_WESEWVED    0x71000000
#define WS400_FP_2ND_GEN_CNTW               0x0384
#       define WS400_FP_2ND_ON              (1 << 0)
#       define WS400_FP_2ND_BWANK_EN        (1 << 1)
#       define WS400_TMDS_2ND_EN            (1 << 2)
#       define WS400_PANEW_FOWMAT_2ND       (1 << 3)
#       define WS400_FP_2ND_EN_TMDS         (1 << 7)
#       define WS400_FP_2ND_DETECT_SENSE    (1 << 8)
#       define WS400_FP_2ND_SOUWCE_SEW_MASK        (3 << 10)
#       define WS400_FP_2ND_SOUWCE_SEW_CWTC1       (0 << 10)
#       define WS400_FP_2ND_SOUWCE_SEW_CWTC2       (1 << 10)
#       define WS400_FP_2ND_SOUWCE_SEW_WMX         (2 << 10)
#       define WS400_FP_2ND_DETECT_EN       (1 << 12)
#       define WS400_HPD_2ND_SEW            (1 << 13)
#define WS400_FP2_2_GEN_CNTW                0x0388
#       define WS400_FP2_2_BWANK_EN         (1 << 1)
#       define WS400_FP2_2_ON               (1 << 2)
#       define WS400_FP2_2_PANEW_FOWMAT     (1 << 3)
#       define WS400_FP2_2_DETECT_SENSE     (1 << 8)
#       define WS400_FP2_2_SOUWCE_SEW_MASK        (3 << 10)
#       define WS400_FP2_2_SOUWCE_SEW_CWTC1       (0 << 10)
#       define WS400_FP2_2_SOUWCE_SEW_CWTC2       (1 << 10)
#       define WS400_FP2_2_SOUWCE_SEW_WMX         (2 << 10)
#       define WS400_FP2_2_DVO2_EN          (1 << 25)
#define WS400_TMDS2_CNTW                    0x0394
#define WS400_TMDS2_TWANSMITTEW_CNTW        0x03a4
#       define WS400_TMDS2_PWWEN            (1 << 0)
#       define WS400_TMDS2_PWWWST           (1 << 1)

#define WADEON_GEN_INT_CNTW                 0x0040
#	define WADEON_CWTC_VBWANK_MASK		(1 << 0)
#	define WADEON_FP_DETECT_MASK		(1 << 4)
#	define WADEON_CWTC2_VBWANK_MASK		(1 << 9)
#	define WADEON_FP2_DETECT_MASK		(1 << 10)
#	define WADEON_GUI_IDWE_MASK		(1 << 19)
#	define WADEON_SW_INT_ENABWE		(1 << 25)
#define WADEON_GEN_INT_STATUS               0x0044
#	define AVIVO_DISPWAY_INT_STATUS		(1 << 0)
#	define WADEON_CWTC_VBWANK_STAT		(1 << 0)
#	define WADEON_CWTC_VBWANK_STAT_ACK	(1 << 0)
#	define WADEON_FP_DETECT_STAT		(1 << 4)
#	define WADEON_FP_DETECT_STAT_ACK	(1 << 4)
#	define WADEON_CWTC2_VBWANK_STAT		(1 << 9)
#	define WADEON_CWTC2_VBWANK_STAT_ACK	(1 << 9)
#	define WADEON_FP2_DETECT_STAT		(1 << 10)
#	define WADEON_FP2_DETECT_STAT_ACK	(1 << 10)
#	define WADEON_GUI_IDWE_STAT		(1 << 19)
#	define WADEON_GUI_IDWE_STAT_ACK		(1 << 19)
#	define WADEON_SW_INT_FIWE		(1 << 26)
#	define WADEON_SW_INT_TEST		(1 << 25)
#	define WADEON_SW_INT_TEST_ACK		(1 << 25)
#define WADEON_GENENB                       0x03c3 /* VGA */
#define WADEON_GENFC_WD                     0x03ca /* VGA */
#define WADEON_GENFC_WT                     0x03da /* VGA, 0x03ba */
#define WADEON_GENMO_WD                     0x03cc /* VGA */
#define WADEON_GENMO_WT                     0x03c2 /* VGA */
#define WADEON_GENS0                        0x03c2 /* VGA */
#define WADEON_GENS1                        0x03da /* VGA, 0x03ba */
#define WADEON_GPIO_MONID                   0x0068 /* DDC intewface via I2C */ /* DDC3 */
#define WADEON_GPIO_MONIDB                  0x006c
#define WADEON_GPIO_CWT2_DDC                0x006c
#define WADEON_GPIO_DVI_DDC                 0x0064 /* DDC2 */
#define WADEON_GPIO_VGA_DDC                 0x0060 /* DDC1 */
#       define WADEON_GPIO_A_0              (1 <<  0)
#       define WADEON_GPIO_A_1              (1 <<  1)
#       define WADEON_GPIO_Y_0              (1 <<  8)
#       define WADEON_GPIO_Y_1              (1 <<  9)
#       define WADEON_GPIO_Y_SHIFT_0        8
#       define WADEON_GPIO_Y_SHIFT_1        9
#       define WADEON_GPIO_EN_0             (1 << 16)
#       define WADEON_GPIO_EN_1             (1 << 17)
#       define WADEON_GPIO_MASK_0           (1 << 24) /*??*/
#       define WADEON_GPIO_MASK_1           (1 << 25) /*??*/
#define WADEON_GWPH8_DATA                   0x03cf /* VGA */
#define WADEON_GWPH8_IDX                    0x03ce /* VGA */
#define WADEON_GUI_SCWATCH_WEG0             0x15e0
#define WADEON_GUI_SCWATCH_WEG1             0x15e4
#define WADEON_GUI_SCWATCH_WEG2             0x15e8
#define WADEON_GUI_SCWATCH_WEG3             0x15ec
#define WADEON_GUI_SCWATCH_WEG4             0x15f0
#define WADEON_GUI_SCWATCH_WEG5             0x15f4

#define WADEON_HEADEW                       0x0f0e /* PCI */
#define WADEON_HOST_DATA0                   0x17c0
#define WADEON_HOST_DATA1                   0x17c4
#define WADEON_HOST_DATA2                   0x17c8
#define WADEON_HOST_DATA3                   0x17cc
#define WADEON_HOST_DATA4                   0x17d0
#define WADEON_HOST_DATA5                   0x17d4
#define WADEON_HOST_DATA6                   0x17d8
#define WADEON_HOST_DATA7                   0x17dc
#define WADEON_HOST_DATA_WAST               0x17e0
#define WADEON_HOST_PATH_CNTW               0x0130
#	define WADEON_HP_WIN_WD_CACHE_DIS   (1 << 24)
#	define WADEON_HDP_WEAD_BUFFEW_INVAWIDATE   (1 << 27)
#       define WADEON_HDP_SOFT_WESET        (1 << 26)
#       define WADEON_HDP_APEW_CNTW         (1 << 23)
#define WADEON_HTOTAW_CNTW                  0x0009 /* PWW */
#       define WADEON_HTOT_CNTW_VGA_EN      (1 << 28)
#define WADEON_HTOTAW2_CNTW                 0x002e /* PWW */

       /* Muwtimedia I2C bus */
#define WADEON_I2C_CNTW_0		    0x0090
#       define WADEON_I2C_DONE              (1 << 0)
#       define WADEON_I2C_NACK              (1 << 1)
#       define WADEON_I2C_HAWT              (1 << 2)
#       define WADEON_I2C_SOFT_WST          (1 << 5)
#       define WADEON_I2C_DWIVE_EN          (1 << 6)
#       define WADEON_I2C_DWIVE_SEW         (1 << 7)
#       define WADEON_I2C_STAWT             (1 << 8)
#       define WADEON_I2C_STOP              (1 << 9)
#       define WADEON_I2C_WECEIVE           (1 << 10)
#       define WADEON_I2C_ABOWT             (1 << 11)
#       define WADEON_I2C_GO                (1 << 12)
#       define WADEON_I2C_PWESCAWE_SHIFT    16
#define WADEON_I2C_CNTW_1                   0x0094
#       define WADEON_I2C_DATA_COUNT_SHIFT  0
#       define WADEON_I2C_ADDW_COUNT_SHIFT  4
#       define WADEON_I2C_INTWA_BYTE_DEWAY_SHIFT   8
#       define WADEON_I2C_SEW               (1 << 16)
#       define WADEON_I2C_EN                (1 << 17)
#       define WADEON_I2C_TIME_WIMIT_SHIFT  24
#define WADEON_I2C_DATA			    0x0098

#define WADEON_DVI_I2C_CNTW_0		    0x02e0
#       define W200_DVI_I2C_PIN_SEW(x)      ((x) << 3)
#       define W200_SEW_DDC1                0 /* depends on asic */
#       define W200_SEW_DDC2                1 /* depends on asic */
#       define W200_SEW_DDC3                2 /* depends on asic */
#	define WADEON_SW_WANTS_TO_USE_DVI_I2C (1 << 13)
#	define WADEON_SW_CAN_USE_DVI_I2C      (1 << 13)
#	define WADEON_SW_DONE_USING_DVI_I2C   (1 << 14)
#	define WADEON_HW_NEEDS_DVI_I2C        (1 << 14)
#	define WADEON_ABOWT_HW_DVI_I2C        (1 << 15)
#	define WADEON_HW_USING_DVI_I2C        (1 << 15)
#define WADEON_DVI_I2C_CNTW_1               0x02e4
#define WADEON_DVI_I2C_DATA		    0x02e8

#define WADEON_INTEWWUPT_WINE               0x0f3c /* PCI */
#define WADEON_INTEWWUPT_PIN                0x0f3d /* PCI */
#define WADEON_IO_BASE                      0x0f14 /* PCI */

#define WADEON_WATENCY                      0x0f0d /* PCI */
#define WADEON_WEAD_BWES_DEC                0x1608
#define WADEON_WEAD_BWES_WNTH               0x161c
#define WADEON_WEAD_BWES_WNTH_SUB           0x1624
#define WADEON_WVDS_GEN_CNTW                0x02d0
#       define WADEON_WVDS_ON               (1   <<  0)
#       define WADEON_WVDS_DISPWAY_DIS      (1   <<  1)
#       define WADEON_WVDS_PANEW_TYPE       (1   <<  2)
#       define WADEON_WVDS_PANEW_FOWMAT     (1   <<  3)
#       define WADEON_WVDS_NO_FM            (0   <<  4)
#       define WADEON_WVDS_2_GWEY           (1   <<  4)
#       define WADEON_WVDS_4_GWEY           (2   <<  4)
#       define WADEON_WVDS_WST_FM           (1   <<  6)
#       define WADEON_WVDS_EN               (1   <<  7)
#       define WADEON_WVDS_BW_MOD_WEVEW_SHIFT 8
#       define WADEON_WVDS_BW_MOD_WEVEW_MASK (0xff << 8)
#       define WADEON_WVDS_BW_MOD_EN        (1   << 16)
#       define WADEON_WVDS_BW_CWK_SEW       (1   << 17)
#       define WADEON_WVDS_DIGON            (1   << 18)
#       define WADEON_WVDS_BWON             (1   << 19)
#       define WADEON_WVDS_FP_POW_WOW       (1   << 20)
#       define WADEON_WVDS_WP_POW_WOW       (1   << 21)
#       define WADEON_WVDS_DTM_POW_WOW      (1   << 22)
#       define WADEON_WVDS_SEW_CWTC2        (1   << 23)
#       define WADEON_WVDS_FPDI_EN          (1   << 27)
#       define WADEON_WVDS_HSYNC_DEWAY_SHIFT        28
#define WADEON_WVDS_PWW_CNTW                0x02d4
#       define WADEON_HSYNC_DEWAY_SHIFT     28
#       define WADEON_HSYNC_DEWAY_MASK      (0xf << 28)
#       define WADEON_WVDS_PWW_EN           (1   << 16)
#       define WADEON_WVDS_PWW_WESET        (1   << 17)
#       define W300_WVDS_SWC_SEW_MASK       (3   << 18)
#       define W300_WVDS_SWC_SEW_CWTC1      (0   << 18)
#       define W300_WVDS_SWC_SEW_CWTC2      (1   << 18)
#       define W300_WVDS_SWC_SEW_WMX        (2   << 18)
#define WADEON_WVDS_SS_GEN_CNTW             0x02ec
#       define WADEON_WVDS_PWWSEQ_DEWAY1_SHIFT     16
#       define WADEON_WVDS_PWWSEQ_DEWAY2_SHIFT     20

#define WADEON_MAX_WATENCY                  0x0f3f /* PCI */
#define WADEON_DISPWAY_BASE_ADDW            0x23c
#define WADEON_DISPWAY2_BASE_ADDW           0x33c
#define WADEON_OV0_BASE_ADDW                0x43c
#define WADEON_NB_TOM                       0x15c
#define W300_MC_INIT_MISC_WAT_TIMEW         0x180
#       define W300_MC_DISP0W_INIT_WAT_SHIFT 8
#       define W300_MC_DISP0W_INIT_WAT_MASK  0xf
#       define W300_MC_DISP1W_INIT_WAT_SHIFT 12
#       define W300_MC_DISP1W_INIT_WAT_MASK  0xf
#define WADEON_MCWK_CNTW                    0x0012 /* PWW */
#       define WADEON_MCWKA_SWC_SEW_MASK    0x7
#       define WADEON_FOWCEON_MCWKA         (1 << 16)
#       define WADEON_FOWCEON_MCWKB         (1 << 17)
#       define WADEON_FOWCEON_YCWKA         (1 << 18)
#       define WADEON_FOWCEON_YCWKB         (1 << 19)
#       define WADEON_FOWCEON_MC            (1 << 20)
#       define WADEON_FOWCEON_AIC           (1 << 21)
#       define W300_DISABWE_MC_MCWKA        (1 << 21)
#       define W300_DISABWE_MC_MCWKB        (1 << 21)
#define WADEON_MCWK_MISC                    0x001f /* PWW */
#       define WADEON_MC_MCWK_MAX_DYN_STOP_WAT (1 << 12)
#       define WADEON_IO_MCWK_MAX_DYN_STOP_WAT (1 << 13)
#       define WADEON_MC_MCWK_DYN_ENABWE    (1 << 14)
#       define WADEON_IO_MCWK_DYN_ENABWE    (1 << 15)

#define WADEON_GPIOPAD_MASK                 0x0198
#define WADEON_GPIOPAD_A		    0x019c
#define WADEON_GPIOPAD_EN                   0x01a0
#define WADEON_GPIOPAD_Y                    0x01a4
#define WADEON_MDGPIO_MASK                  0x01a8
#define WADEON_MDGPIO_A                     0x01ac
#define WADEON_MDGPIO_EN                    0x01b0
#define WADEON_MDGPIO_Y                     0x01b4

#define WADEON_MEM_ADDW_CONFIG              0x0148
#define WADEON_MEM_BASE                     0x0f10 /* PCI */
#define WADEON_MEM_CNTW                     0x0140
#       define WADEON_MEM_NUM_CHANNEWS_MASK 0x01
#       define WADEON_MEM_USE_B_CH_ONWY     (1 <<  1)
#       define WV100_HAWF_MODE              (1 <<  3)
#       define W300_MEM_NUM_CHANNEWS_MASK   0x03
#       define W300_MEM_USE_CD_CH_ONWY      (1 <<  2)
#define WADEON_MEM_TIMING_CNTW              0x0144 /* EXT_MEM_CNTW */
#define WADEON_MEM_INIT_WAT_TIMEW           0x0154
#define WADEON_MEM_INTF_CNTW                0x014c
#define WADEON_MEM_SDWAM_MODE_WEG           0x0158
#       define WADEON_SDWAM_MODE_MASK       0xffff0000
#       define WADEON_B3MEM_WESET_MASK      0x6fffffff
#       define WADEON_MEM_CFG_TYPE_DDW      (1 << 30)
#define WADEON_MEM_STW_CNTW                 0x0150
#       define WADEON_MEM_PWWUP_COMPW_A     (1 <<  0)
#       define WADEON_MEM_PWWUP_COMPW_B     (1 <<  1)
#       define W300_MEM_PWWUP_COMPW_C       (1 <<  2)
#       define W300_MEM_PWWUP_COMPW_D       (1 <<  3)
#       define WADEON_MEM_PWWUP_COMPWETE    0x03
#       define W300_MEM_PWWUP_COMPWETE      0x0f
#define WADEON_MC_STATUS                    0x0150
#       define WADEON_MC_IDWE               (1 << 2)
#       define W300_MC_IDWE                 (1 << 4)
#define WADEON_MEM_VGA_WP_SEW               0x003c
#define WADEON_MEM_VGA_WP_SEW               0x0038
#define WADEON_MIN_GWANT                    0x0f3e /* PCI */
#define WADEON_MM_DATA                      0x0004
#define WADEON_MM_INDEX                     0x0000
#	define WADEON_MM_APEW		(1 << 31)
#define WADEON_MPWW_CNTW                    0x000e /* PWW */
#define WADEON_MPP_TB_CONFIG                0x01c0 /* ? */
#define WADEON_MPP_GP_CONFIG                0x01c8 /* ? */
#define WADEON_SEPWOM_CNTW1                 0x01c0
#       define WADEON_SCK_PWESCAWE_SHIFT    24
#       define WADEON_SCK_PWESCAWE_MASK     (0xff << 24)
#define W300_MC_IND_INDEX                   0x01f8
#       define W300_MC_IND_ADDW_MASK        0x3f
#       define W300_MC_IND_WW_EN            (1 << 8)
#define W300_MC_IND_DATA                    0x01fc
#define W300_MC_WEAD_CNTW_AB                0x017c
#       define W300_MEM_WBS_POSITION_A_MASK 0x03
#define W300_MC_WEAD_CNTW_CD_mcind	    0x24
#       define W300_MEM_WBS_POSITION_C_MASK 0x03

#define WADEON_N_VIF_COUNT                  0x0248

#define WADEON_OV0_AUTO_FWIP_CNTW           0x0470
#       define  WADEON_OV0_AUTO_FWIP_CNTW_SOFT_BUF_NUM        0x00000007
#       define  WADEON_OV0_AUTO_FWIP_CNTW_SOFT_WEPEAT_FIEWD   0x00000008
#       define  WADEON_OV0_AUTO_FWIP_CNTW_SOFT_BUF_ODD        0x00000010
#       define  WADEON_OV0_AUTO_FWIP_CNTW_IGNOWE_WEPEAT_FIEWD 0x00000020
#       define  WADEON_OV0_AUTO_FWIP_CNTW_SOFT_EOF_TOGGWE     0x00000040
#       define  WADEON_OV0_AUTO_FWIP_CNTW_VID_POWT_SEWECT     0x00000300
#       define  WADEON_OV0_AUTO_FWIP_CNTW_P1_FIWST_WINE_EVEN  0x00010000
#       define  WADEON_OV0_AUTO_FWIP_CNTW_SHIFT_EVEN_DOWN     0x00040000
#       define  WADEON_OV0_AUTO_FWIP_CNTW_SHIFT_ODD_DOWN      0x00080000
#       define  WADEON_OV0_AUTO_FWIP_CNTW_FIEWD_POW_SOUWCE    0x00800000

#define WADEON_OV0_COWOUW_CNTW              0x04E0
#define WADEON_OV0_DEINTEWWACE_PATTEWN      0x0474
#define WADEON_OV0_EXCWUSIVE_HOWZ           0x0408
#       define  WADEON_EXCW_HOWZ_STAWT_MASK        0x000000ff
#       define  WADEON_EXCW_HOWZ_END_MASK          0x0000ff00
#       define  WADEON_EXCW_HOWZ_BACK_POWCH_MASK   0x00ff0000
#       define  WADEON_EXCW_HOWZ_EXCWUSIVE_EN      0x80000000
#define WADEON_OV0_EXCWUSIVE_VEWT           0x040C
#       define  WADEON_EXCW_VEWT_STAWT_MASK        0x000003ff
#       define  WADEON_EXCW_VEWT_END_MASK          0x03ff0000
#define WADEON_OV0_FIWTEW_CNTW              0x04A0
#       define WADEON_FIWTEW_PWOGWAMMABWE_COEF            0x0
#       define WADEON_FIWTEW_HC_COEF_HOWZ_Y               0x1
#       define WADEON_FIWTEW_HC_COEF_HOWZ_UV              0x2
#       define WADEON_FIWTEW_HC_COEF_VEWT_Y               0x4
#       define WADEON_FIWTEW_HC_COEF_VEWT_UV              0x8
#       define WADEON_FIWTEW_HAWDCODED_COEF               0xf
#       define WADEON_FIWTEW_COEF_MASK                    0xf

#define WADEON_OV0_FOUW_TAP_COEF_0          0x04B0
#define WADEON_OV0_FOUW_TAP_COEF_1          0x04B4
#define WADEON_OV0_FOUW_TAP_COEF_2          0x04B8
#define WADEON_OV0_FOUW_TAP_COEF_3          0x04BC
#define WADEON_OV0_FOUW_TAP_COEF_4          0x04C0
#define WADEON_OV0_FWAG_CNTW                0x04DC
#define WADEON_OV0_GAMMA_000_00F            0x0d40
#define WADEON_OV0_GAMMA_010_01F            0x0d44
#define WADEON_OV0_GAMMA_020_03F            0x0d48
#define WADEON_OV0_GAMMA_040_07F            0x0d4c
#define WADEON_OV0_GAMMA_080_0BF            0x0e00
#define WADEON_OV0_GAMMA_0C0_0FF            0x0e04
#define WADEON_OV0_GAMMA_100_13F            0x0e08
#define WADEON_OV0_GAMMA_140_17F            0x0e0c
#define WADEON_OV0_GAMMA_180_1BF            0x0e10
#define WADEON_OV0_GAMMA_1C0_1FF            0x0e14
#define WADEON_OV0_GAMMA_200_23F            0x0e18
#define WADEON_OV0_GAMMA_240_27F            0x0e1c
#define WADEON_OV0_GAMMA_280_2BF            0x0e20
#define WADEON_OV0_GAMMA_2C0_2FF            0x0e24
#define WADEON_OV0_GAMMA_300_33F            0x0e28
#define WADEON_OV0_GAMMA_340_37F            0x0e2c
#define WADEON_OV0_GAMMA_380_3BF            0x0d50
#define WADEON_OV0_GAMMA_3C0_3FF            0x0d54
#define WADEON_OV0_GWAPHICS_KEY_CWW_WOW     0x04EC
#define WADEON_OV0_GWAPHICS_KEY_CWW_HIGH    0x04F0
#define WADEON_OV0_H_INC                    0x0480
#define WADEON_OV0_KEY_CNTW                 0x04F4
#       define  WADEON_VIDEO_KEY_FN_MASK    0x00000003W
#       define  WADEON_VIDEO_KEY_FN_FAWSE   0x00000000W
#       define  WADEON_VIDEO_KEY_FN_TWUE    0x00000001W
#       define  WADEON_VIDEO_KEY_FN_EQ      0x00000002W
#       define  WADEON_VIDEO_KEY_FN_NE      0x00000003W
#       define  WADEON_GWAPHIC_KEY_FN_MASK  0x00000030W
#       define  WADEON_GWAPHIC_KEY_FN_FAWSE 0x00000000W
#       define  WADEON_GWAPHIC_KEY_FN_TWUE  0x00000010W
#       define  WADEON_GWAPHIC_KEY_FN_EQ    0x00000020W
#       define  WADEON_GWAPHIC_KEY_FN_NE    0x00000030W
#       define  WADEON_CMP_MIX_MASK         0x00000100W
#       define  WADEON_CMP_MIX_OW           0x00000000W
#       define  WADEON_CMP_MIX_AND          0x00000100W
#define WADEON_OV0_WIN_TWANS_A              0x0d20
#define WADEON_OV0_WIN_TWANS_B              0x0d24
#define WADEON_OV0_WIN_TWANS_C              0x0d28
#define WADEON_OV0_WIN_TWANS_D              0x0d2c
#define WADEON_OV0_WIN_TWANS_E              0x0d30
#define WADEON_OV0_WIN_TWANS_F              0x0d34
#define WADEON_OV0_P1_BWANK_WINES_AT_TOP    0x0430
#       define  WADEON_P1_BWNK_WN_AT_TOP_M1_MASK   0x00000fffW
#       define  WADEON_P1_ACTIVE_WINES_M1          0x0fff0000W
#define WADEON_OV0_P1_H_ACCUM_INIT          0x0488
#define WADEON_OV0_P1_V_ACCUM_INIT          0x0428
#       define  WADEON_OV0_P1_MAX_WN_IN_PEW_WN_OUT 0x00000003W
#       define  WADEON_OV0_P1_V_ACCUM_INIT_MASK    0x01ff8000W
#define WADEON_OV0_P1_X_STAWT_END           0x0494
#define WADEON_OV0_P2_X_STAWT_END           0x0498
#define WADEON_OV0_P23_BWANK_WINES_AT_TOP   0x0434
#       define  WADEON_P23_BWNK_WN_AT_TOP_M1_MASK  0x000007ffW
#       define  WADEON_P23_ACTIVE_WINES_M1         0x07ff0000W
#define WADEON_OV0_P23_H_ACCUM_INIT         0x048C
#define WADEON_OV0_P23_V_ACCUM_INIT         0x042C
#define WADEON_OV0_P3_X_STAWT_END           0x049C
#define WADEON_OV0_WEG_WOAD_CNTW            0x0410
#       define  WADEON_WEG_WD_CTW_WOCK                 0x00000001W
#       define  WADEON_WEG_WD_CTW_VBWANK_DUWING_WOCK   0x00000002W
#       define  WADEON_WEG_WD_CTW_STAWW_GUI_UNTIW_FWIP 0x00000004W
#       define  WADEON_WEG_WD_CTW_WOCK_WEADBACK        0x00000008W
#       define  WADEON_WEG_WD_CTW_FWIP_WEADBACK        0x00000010W
#define WADEON_OV0_SCAWE_CNTW               0x0420
#       define  WADEON_SCAWEW_HOWZ_PICK_NEAWEST    0x00000004W
#       define  WADEON_SCAWEW_VEWT_PICK_NEAWEST    0x00000008W
#       define  WADEON_SCAWEW_SIGNED_UV            0x00000010W
#       define  WADEON_SCAWEW_GAMMA_SEW_MASK       0x00000060W
#       define  WADEON_SCAWEW_GAMMA_SEW_BWIGHT     0x00000000W
#       define  WADEON_SCAWEW_GAMMA_SEW_G22        0x00000020W
#       define  WADEON_SCAWEW_GAMMA_SEW_G18        0x00000040W
#       define  WADEON_SCAWEW_GAMMA_SEW_G14        0x00000060W
#       define  WADEON_SCAWEW_COMCOWE_SHIFT_UP_ONE 0x00000080W
#       define  WADEON_SCAWEW_SUWFAC_FOWMAT        0x00000f00W
#       define  WADEON_SCAWEW_SOUWCE_15BPP         0x00000300W
#       define  WADEON_SCAWEW_SOUWCE_16BPP         0x00000400W
#       define  WADEON_SCAWEW_SOUWCE_32BPP         0x00000600W
#       define  WADEON_SCAWEW_SOUWCE_YUV9          0x00000900W
#       define  WADEON_SCAWEW_SOUWCE_YUV12         0x00000A00W
#       define  WADEON_SCAWEW_SOUWCE_VYUY422       0x00000B00W
#       define  WADEON_SCAWEW_SOUWCE_YVYU422       0x00000C00W
#       define  WADEON_SCAWEW_ADAPTIVE_DEINT       0x00001000W
#       define  WADEON_SCAWEW_TEMPOWAW_DEINT       0x00002000W
#       define  WADEON_SCAWEW_CWTC_SEW             0x00004000W
#       define  WADEON_SCAWEW_SMAWT_SWITCH         0x00008000W
#       define  WADEON_SCAWEW_BUWST_PEW_PWANE      0x007F0000W
#       define  WADEON_SCAWEW_DOUBWE_BUFFEW        0x01000000W
#       define  WADEON_SCAWEW_DIS_WIMIT            0x08000000W
#       define  WADEON_SCAWEW_WIN_TWANS_BYPASS     0x10000000W
#       define  WADEON_SCAWEW_INT_EMU              0x20000000W
#       define  WADEON_SCAWEW_ENABWE               0x40000000W
#       define  WADEON_SCAWEW_SOFT_WESET           0x80000000W
#define WADEON_OV0_STEP_BY                  0x0484
#define WADEON_OV0_TEST                     0x04F8
#define WADEON_OV0_V_INC                    0x0424
#define WADEON_OV0_VID_BUF_PITCH0_VAWUE     0x0460
#define WADEON_OV0_VID_BUF_PITCH1_VAWUE     0x0464
#define WADEON_OV0_VID_BUF0_BASE_ADWS       0x0440
#       define  WADEON_VIF_BUF0_PITCH_SEW          0x00000001W
#       define  WADEON_VIF_BUF0_TIWE_ADWS          0x00000002W
#       define  WADEON_VIF_BUF0_BASE_ADWS_MASK     0x03fffff0W
#       define  WADEON_VIF_BUF0_1ST_WINE_WSBS_MASK 0x48000000W
#define WADEON_OV0_VID_BUF1_BASE_ADWS       0x0444
#       define  WADEON_VIF_BUF1_PITCH_SEW          0x00000001W
#       define  WADEON_VIF_BUF1_TIWE_ADWS          0x00000002W
#       define  WADEON_VIF_BUF1_BASE_ADWS_MASK     0x03fffff0W
#       define  WADEON_VIF_BUF1_1ST_WINE_WSBS_MASK 0x48000000W
#define WADEON_OV0_VID_BUF2_BASE_ADWS       0x0448
#       define  WADEON_VIF_BUF2_PITCH_SEW          0x00000001W
#       define  WADEON_VIF_BUF2_TIWE_ADWS          0x00000002W
#       define  WADEON_VIF_BUF2_BASE_ADWS_MASK     0x03fffff0W
#       define  WADEON_VIF_BUF2_1ST_WINE_WSBS_MASK 0x48000000W
#define WADEON_OV0_VID_BUF3_BASE_ADWS       0x044C
#define WADEON_OV0_VID_BUF4_BASE_ADWS       0x0450
#define WADEON_OV0_VID_BUF5_BASE_ADWS       0x0454
#define WADEON_OV0_VIDEO_KEY_CWW_HIGH       0x04E8
#define WADEON_OV0_VIDEO_KEY_CWW_WOW        0x04E4
#define WADEON_OV0_Y_X_STAWT                0x0400
#define WADEON_OV0_Y_X_END                  0x0404
#define WADEON_OV1_Y_X_STAWT                0x0600
#define WADEON_OV1_Y_X_END                  0x0604
#define WADEON_OVW_CWW                      0x0230
#define WADEON_OVW_WID_WEFT_WIGHT           0x0234
#define WADEON_OVW_WID_TOP_BOTTOM           0x0238
#define WADEON_OVW2_CWW                     0x0330
#define WADEON_OVW2_WID_WEFT_WIGHT          0x0334
#define WADEON_OVW2_WID_TOP_BOTTOM          0x0338

/* fiwst captuwe unit */

#define WADEON_CAP0_BUF0_OFFSET           0x0920
#define WADEON_CAP0_BUF1_OFFSET           0x0924
#define WADEON_CAP0_BUF0_EVEN_OFFSET      0x0928
#define WADEON_CAP0_BUF1_EVEN_OFFSET      0x092C

#define WADEON_CAP0_BUF_PITCH             0x0930
#define WADEON_CAP0_V_WINDOW              0x0934
#define WADEON_CAP0_H_WINDOW              0x0938
#define WADEON_CAP0_VBI0_OFFSET           0x093C
#define WADEON_CAP0_VBI1_OFFSET           0x0940
#define WADEON_CAP0_VBI_V_WINDOW          0x0944
#define WADEON_CAP0_VBI_H_WINDOW          0x0948
#define WADEON_CAP0_POWT_MODE_CNTW        0x094C
#define WADEON_CAP0_TWIG_CNTW             0x0950
#define WADEON_CAP0_DEBUG                 0x0954
#define WADEON_CAP0_CONFIG                0x0958
#       define WADEON_CAP0_CONFIG_CONTINUOS          0x00000001
#       define WADEON_CAP0_CONFIG_STAWT_FIEWD_EVEN   0x00000002
#       define WADEON_CAP0_CONFIG_STAWT_BUF_GET      0x00000004
#       define WADEON_CAP0_CONFIG_STAWT_BUF_SET      0x00000008
#       define WADEON_CAP0_CONFIG_BUF_TYPE_AWT       0x00000010
#       define WADEON_CAP0_CONFIG_BUF_TYPE_FWAME     0x00000020
#       define WADEON_CAP0_CONFIG_ONESHOT_MODE_FWAME 0x00000040
#       define WADEON_CAP0_CONFIG_BUF_MODE_DOUBWE    0x00000080
#       define WADEON_CAP0_CONFIG_BUF_MODE_TWIPWE    0x00000100
#       define WADEON_CAP0_CONFIG_MIWWOW_EN          0x00000200
#       define WADEON_CAP0_CONFIG_ONESHOT_MIWWOW_EN  0x00000400
#       define WADEON_CAP0_CONFIG_VIDEO_SIGNED_UV    0x00000800
#       define WADEON_CAP0_CONFIG_ANC_DECODE_EN      0x00001000
#       define WADEON_CAP0_CONFIG_VBI_EN             0x00002000
#       define WADEON_CAP0_CONFIG_SOFT_PUWW_DOWN_EN  0x00004000
#       define WADEON_CAP0_CONFIG_VIP_EXTEND_FWAG_EN 0x00008000
#       define WADEON_CAP0_CONFIG_FAKE_FIEWD_EN      0x00010000
#       define WADEON_CAP0_CONFIG_ODD_ONE_MOWE_WINE  0x00020000
#       define WADEON_CAP0_CONFIG_EVEN_ONE_MOWE_WINE 0x00040000
#       define WADEON_CAP0_CONFIG_HOWZ_DIVIDE_2      0x00080000
#       define WADEON_CAP0_CONFIG_HOWZ_DIVIDE_4      0x00100000
#       define WADEON_CAP0_CONFIG_VEWT_DIVIDE_2      0x00200000
#       define WADEON_CAP0_CONFIG_VEWT_DIVIDE_4      0x00400000
#       define WADEON_CAP0_CONFIG_FOWMAT_BWOOKTWEE   0x00000000
#       define WADEON_CAP0_CONFIG_FOWMAT_CCIW656     0x00800000
#       define WADEON_CAP0_CONFIG_FOWMAT_ZV          0x01000000
#       define WADEON_CAP0_CONFIG_FOWMAT_VIP         0x01800000
#       define WADEON_CAP0_CONFIG_FOWMAT_TWANSPOWT   0x02000000
#       define WADEON_CAP0_CONFIG_HOWZ_DECIMATOW     0x04000000
#       define WADEON_CAP0_CONFIG_VIDEO_IN_YVYU422   0x00000000
#       define WADEON_CAP0_CONFIG_VIDEO_IN_VYUY422   0x20000000
#       define WADEON_CAP0_CONFIG_VBI_DIVIDE_2       0x40000000
#       define WADEON_CAP0_CONFIG_VBI_DIVIDE_4       0x80000000
#define WADEON_CAP0_ANC_ODD_OFFSET        0x095C
#define WADEON_CAP0_ANC_EVEN_OFFSET       0x0960
#define WADEON_CAP0_ANC_H_WINDOW          0x0964
#define WADEON_CAP0_VIDEO_SYNC_TEST       0x0968
#define WADEON_CAP0_ONESHOT_BUF_OFFSET    0x096C
#define WADEON_CAP0_BUF_STATUS            0x0970
/* #define WADEON_CAP0_DWNSC_XWATIO       0x0978 */
/* #define WADEON_CAP0_XSHAWPNESS                 0x097C */
#define WADEON_CAP0_VBI2_OFFSET           0x0980
#define WADEON_CAP0_VBI3_OFFSET           0x0984
#define WADEON_CAP0_ANC2_OFFSET           0x0988
#define WADEON_CAP0_ANC3_OFFSET           0x098C
#define WADEON_VID_BUFFEW_CONTWOW         0x0900

/* second captuwe unit */

#define WADEON_CAP1_BUF0_OFFSET           0x0990
#define WADEON_CAP1_BUF1_OFFSET           0x0994
#define WADEON_CAP1_BUF0_EVEN_OFFSET      0x0998
#define WADEON_CAP1_BUF1_EVEN_OFFSET      0x099C

#define WADEON_CAP1_BUF_PITCH             0x09A0
#define WADEON_CAP1_V_WINDOW              0x09A4
#define WADEON_CAP1_H_WINDOW              0x09A8
#define WADEON_CAP1_VBI_ODD_OFFSET        0x09AC
#define WADEON_CAP1_VBI_EVEN_OFFSET       0x09B0
#define WADEON_CAP1_VBI_V_WINDOW                  0x09B4
#define WADEON_CAP1_VBI_H_WINDOW                  0x09B8
#define WADEON_CAP1_POWT_MODE_CNTW        0x09BC
#define WADEON_CAP1_TWIG_CNTW             0x09C0
#define WADEON_CAP1_DEBUG                         0x09C4
#define WADEON_CAP1_CONFIG                0x09C8
#define WADEON_CAP1_ANC_ODD_OFFSET        0x09CC
#define WADEON_CAP1_ANC_EVEN_OFFSET       0x09D0
#define WADEON_CAP1_ANC_H_WINDOW                  0x09D4
#define WADEON_CAP1_VIDEO_SYNC_TEST       0x09D8
#define WADEON_CAP1_ONESHOT_BUF_OFFSET    0x09DC
#define WADEON_CAP1_BUF_STATUS            0x09E0
#define WADEON_CAP1_DWNSC_XWATIO                  0x09E8
#define WADEON_CAP1_XSHAWPNESS            0x09EC

/* misc muwtimedia wegistews */

#define WADEON_IDCT_WUNS                  0x1F80
#define WADEON_IDCT_WEVEWS                0x1F84
#define WADEON_IDCT_CONTWOW               0x1FBC
#define WADEON_IDCT_AUTH_CONTWOW          0x1F88
#define WADEON_IDCT_AUTH                  0x1F8C

#define WADEON_P2PWW_CNTW                   0x002a /* P2PWW */
#       define WADEON_P2PWW_WESET                (1 <<  0)
#       define WADEON_P2PWW_SWEEP                (1 <<  1)
#       define WADEON_P2PWW_PVG_MASK             (7 << 11)
#       define WADEON_P2PWW_PVG_SHIFT            11
#       define WADEON_P2PWW_ATOMIC_UPDATE_EN     (1 << 16)
#       define WADEON_P2PWW_VGA_ATOMIC_UPDATE_EN (1 << 17)
#       define WADEON_P2PWW_ATOMIC_UPDATE_VSYNC  (1 << 18)
#define WADEON_P2PWW_DIV_0                  0x002c
#       define WADEON_P2PWW_FB0_DIV_MASK    0x07ff
#       define WADEON_P2PWW_POST0_DIV_MASK  0x00070000
#define WADEON_P2PWW_WEF_DIV                0x002B /* PWW */
#       define WADEON_P2PWW_WEF_DIV_MASK    0x03ff
#       define WADEON_P2PWW_ATOMIC_UPDATE_W (1 << 15) /* same as _W */
#       define WADEON_P2PWW_ATOMIC_UPDATE_W (1 << 15) /* same as _W */
#       define W300_PPWW_WEF_DIV_ACC_MASK   (0x3ff << 18)
#       define W300_PPWW_WEF_DIV_ACC_SHIFT  18
#define WADEON_PAWETTE_DATA                 0x00b4
#define WADEON_PAWETTE_30_DATA              0x00b8
#define WADEON_PAWETTE_INDEX                0x00b0
#define WADEON_PCI_GAWT_PAGE                0x017c
#define WADEON_PIXCWKS_CNTW                 0x002d
#       define WADEON_PIX2CWK_SWC_SEW_MASK     0x03
#       define WADEON_PIX2CWK_SWC_SEW_CPUCWK   0x00
#       define WADEON_PIX2CWK_SWC_SEW_PSCANCWK 0x01
#       define WADEON_PIX2CWK_SWC_SEW_BYTECWK  0x02
#       define WADEON_PIX2CWK_SWC_SEW_P2PWWCWK 0x03
#       define WADEON_PIX2CWK_AWWAYS_ONb       (1<<6)
#       define WADEON_PIX2CWK_DAC_AWWAYS_ONb   (1<<7)
#       define WADEON_PIXCWK_TV_SWC_SEW        (1 << 8)
#       define WADEON_DISP_TVOUT_PIXCWK_TV_AWWAYS_ONb (1 << 9)
#       define W300_DVOCWK_AWWAYS_ONb          (1 << 10)
#       define WADEON_PIXCWK_BWEND_AWWAYS_ONb  (1 << 11)
#       define WADEON_PIXCWK_GV_AWWAYS_ONb     (1 << 12)
#       define WADEON_PIXCWK_DIG_TMDS_AWWAYS_ONb (1 << 13)
#       define W300_PIXCWK_DVO_AWWAYS_ONb      (1 << 13)
#       define WADEON_PIXCWK_WVDS_AWWAYS_ONb   (1 << 14)
#       define WADEON_PIXCWK_TMDS_AWWAYS_ONb   (1 << 15)
#       define W300_PIXCWK_TWANS_AWWAYS_ONb    (1 << 16)
#       define W300_PIXCWK_TVO_AWWAYS_ONb      (1 << 17)
#       define W300_P2G2CWK_AWWAYS_ONb         (1 << 18)
#       define W300_P2G2CWK_DAC_AWWAYS_ONb     (1 << 19)
#       define W300_DISP_DAC_PIXCWK_DAC2_BWANK_OFF (1 << 23)
#define WADEON_PWANE_3D_MASK_C              0x1d44
#define WADEON_PWW_TEST_CNTW                0x0013 /* PWW */
#       define WADEON_PWW_MASK_WEAD_B          (1 << 9)
#define WADEON_PMI_CAP_ID                   0x0f5c /* PCI */
#define WADEON_PMI_DATA                     0x0f63 /* PCI */
#define WADEON_PMI_NXT_CAP_PTW              0x0f5d /* PCI */
#define WADEON_PMI_PMC_WEG                  0x0f5e /* PCI */
#define WADEON_PMI_PMCSW_WEG                0x0f60 /* PCI */
#define WADEON_PMI_WEGISTEW                 0x0f5c /* PCI */
#define WADEON_PPWW_CNTW                    0x0002 /* PWW */
#       define WADEON_PPWW_WESET                (1 <<  0)
#       define WADEON_PPWW_SWEEP                (1 <<  1)
#       define WADEON_PPWW_PVG_MASK             (7 << 11)
#       define WADEON_PPWW_PVG_SHIFT            11
#       define WADEON_PPWW_ATOMIC_UPDATE_EN     (1 << 16)
#       define WADEON_PPWW_VGA_ATOMIC_UPDATE_EN (1 << 17)
#       define WADEON_PPWW_ATOMIC_UPDATE_VSYNC  (1 << 18)
#define WADEON_PPWW_DIV_0                   0x0004 /* PWW */
#define WADEON_PPWW_DIV_1                   0x0005 /* PWW */
#define WADEON_PPWW_DIV_2                   0x0006 /* PWW */
#define WADEON_PPWW_DIV_3                   0x0007 /* PWW */
#       define WADEON_PPWW_FB3_DIV_MASK     0x07ff
#       define WADEON_PPWW_POST3_DIV_MASK   0x00070000
#define WADEON_PPWW_WEF_DIV                 0x0003 /* PWW */
#       define WADEON_PPWW_WEF_DIV_MASK     0x03ff
#       define WADEON_PPWW_ATOMIC_UPDATE_W  (1 << 15) /* same as _W */
#       define WADEON_PPWW_ATOMIC_UPDATE_W  (1 << 15) /* same as _W */
#define WADEON_PWW_MNGMT_CNTW_STATUS        0x0f60 /* PCI */

#define WADEON_WBBM_GUICNTW                 0x172c
#       define WADEON_HOST_DATA_SWAP_NONE   (0 << 0)
#       define WADEON_HOST_DATA_SWAP_16BIT  (1 << 0)
#       define WADEON_HOST_DATA_SWAP_32BIT  (2 << 0)
#       define WADEON_HOST_DATA_SWAP_HDW    (3 << 0)
#define WADEON_WBBM_SOFT_WESET              0x00f0
#       define WADEON_SOFT_WESET_CP         (1 <<  0)
#       define WADEON_SOFT_WESET_HI         (1 <<  1)
#       define WADEON_SOFT_WESET_SE         (1 <<  2)
#       define WADEON_SOFT_WESET_WE         (1 <<  3)
#       define WADEON_SOFT_WESET_PP         (1 <<  4)
#       define WADEON_SOFT_WESET_E2         (1 <<  5)
#       define WADEON_SOFT_WESET_WB         (1 <<  6)
#       define WADEON_SOFT_WESET_HDP        (1 <<  7)
#define WADEON_WBBM_STATUS                  0x0e40
#       define WADEON_WBBM_FIFOCNT_MASK     0x007f
#       define WADEON_WBBM_ACTIVE           (1 << 31)
#define WADEON_WB2D_DSTCACHE_CTWSTAT        0x342c
#       define WADEON_WB2D_DC_FWUSH         (3 << 0)
#       define WADEON_WB2D_DC_FWEE          (3 << 2)
#       define WADEON_WB2D_DC_FWUSH_AWW     0xf
#       define WADEON_WB2D_DC_BUSY          (1 << 31)
#define WADEON_WB2D_DSTCACHE_MODE           0x3428
#define WADEON_DSTCACHE_CTWSTAT             0x1714

#define WADEON_WB3D_ZCACHE_MODE             0x3250
#define WADEON_WB3D_ZCACHE_CTWSTAT          0x3254
#       define WADEON_WB3D_ZC_FWUSH_AWW     0x5
#define WADEON_WB3D_DSTCACHE_MODE           0x3258
# define WADEON_WB3D_DC_CACHE_ENABWE            (0)
# define WADEON_WB3D_DC_2D_CACHE_DISABWE        (1)
# define WADEON_WB3D_DC_3D_CACHE_DISABWE        (2)
# define WADEON_WB3D_DC_CACHE_DISABWE           (3)
# define WADEON_WB3D_DC_2D_CACHE_WINESIZE_128   (1 << 2)
# define WADEON_WB3D_DC_3D_CACHE_WINESIZE_128   (2 << 2)
# define WADEON_WB3D_DC_2D_CACHE_AUTOFWUSH      (1 << 8)
# define WADEON_WB3D_DC_3D_CACHE_AUTOFWUSH      (2 << 8)
# define W200_WB3D_DC_2D_CACHE_AUTOFWEE         (1 << 10)
# define W200_WB3D_DC_3D_CACHE_AUTOFWEE         (2 << 10)
# define WADEON_WB3D_DC_FOWCE_WMW               (1 << 16)
# define WADEON_WB3D_DC_DISABWE_WI_FIWW         (1 << 24)
# define WADEON_WB3D_DC_DISABWE_WI_WEAD         (1 << 25)

#define WADEON_WB3D_DSTCACHE_CTWSTAT            0x325C
# define WADEON_WB3D_DC_FWUSH                   (3 << 0)
# define WADEON_WB3D_DC_FWEE                    (3 << 2)
# define WADEON_WB3D_DC_FWUSH_AWW               0xf
# define WADEON_WB3D_DC_BUSY                    (1 << 31)

#define WADEON_WEG_BASE                     0x0f18 /* PCI */
#define WADEON_WEGPWOG_INF                  0x0f09 /* PCI */
#define WADEON_WEVISION_ID                  0x0f08 /* PCI */

#define WADEON_SC_BOTTOM                    0x164c
#define WADEON_SC_BOTTOM_WIGHT              0x16f0
#define WADEON_SC_BOTTOM_WIGHT_C            0x1c8c
#define WADEON_SC_WEFT                      0x1640
#define WADEON_SC_WIGHT                     0x1644
#define WADEON_SC_TOP                       0x1648
#define WADEON_SC_TOP_WEFT                  0x16ec
#define WADEON_SC_TOP_WEFT_C                0x1c88
#       define WADEON_SC_SIGN_MASK_WO       0x8000
#       define WADEON_SC_SIGN_MASK_HI       0x80000000
#define WADEON_M_SPWW_WEF_FB_DIV            0x000a /* PWW */
#	define WADEON_M_SPWW_WEF_DIV_SHIFT  0
#	define WADEON_M_SPWW_WEF_DIV_MASK   0xff
#	define WADEON_MPWW_FB_DIV_SHIFT     8
#	define WADEON_MPWW_FB_DIV_MASK      0xff
#	define WADEON_SPWW_FB_DIV_SHIFT     16
#	define WADEON_SPWW_FB_DIV_MASK      0xff
#define WADEON_SPWW_CNTW                    0x000c /* PWW */
#       define WADEON_SPWW_SWEEP            (1 << 0)
#       define WADEON_SPWW_WESET            (1 << 1)
#       define WADEON_SPWW_PCP_MASK         0x7
#       define WADEON_SPWW_PCP_SHIFT        8
#       define WADEON_SPWW_PVG_MASK         0x7
#       define WADEON_SPWW_PVG_SHIFT        11
#       define WADEON_SPWW_PDC_MASK         0x3
#       define WADEON_SPWW_PDC_SHIFT        14
#define WADEON_SCWK_CNTW                    0x000d /* PWW */
#       define WADEON_SCWK_SWC_SEW_MASK     0x0007
#       define WADEON_DYN_STOP_WAT_MASK     0x00007ff8
#       define WADEON_CP_MAX_DYN_STOP_WAT   0x0008
#       define WADEON_SCWK_FOWCEON_MASK     0xffff8000
#       define WADEON_SCWK_FOWCE_DISP2      (1<<15)
#       define WADEON_SCWK_FOWCE_CP         (1<<16)
#       define WADEON_SCWK_FOWCE_HDP        (1<<17)
#       define WADEON_SCWK_FOWCE_DISP1      (1<<18)
#       define WADEON_SCWK_FOWCE_TOP        (1<<19)
#       define WADEON_SCWK_FOWCE_E2         (1<<20)
#       define WADEON_SCWK_FOWCE_SE         (1<<21)
#       define WADEON_SCWK_FOWCE_IDCT       (1<<22)
#       define WADEON_SCWK_FOWCE_VIP        (1<<23)
#       define WADEON_SCWK_FOWCE_WE         (1<<24)
#       define WADEON_SCWK_FOWCE_PB         (1<<25)
#       define WADEON_SCWK_FOWCE_TAM        (1<<26)
#       define WADEON_SCWK_FOWCE_TDM        (1<<27)
#       define WADEON_SCWK_FOWCE_WB         (1<<28)
#       define WADEON_SCWK_FOWCE_TV_SCWK    (1<<29)
#       define WADEON_SCWK_FOWCE_SUBPIC     (1<<30)
#       define WADEON_SCWK_FOWCE_OV0        (1<<31)
#       define W300_SCWK_FOWCE_VAP          (1<<21)
#       define W300_SCWK_FOWCE_SW           (1<<25)
#       define W300_SCWK_FOWCE_PX           (1<<26)
#       define W300_SCWK_FOWCE_TX           (1<<27)
#       define W300_SCWK_FOWCE_US           (1<<28)
#       define W300_SCWK_FOWCE_SU           (1<<30)
#define W300_SCWK_CNTW2                     0x1e   /* PWW */
#       define W300_SCWK_TCW_MAX_DYN_STOP_WAT (1<<10)
#       define W300_SCWK_GA_MAX_DYN_STOP_WAT  (1<<11)
#       define W300_SCWK_CBA_MAX_DYN_STOP_WAT (1<<12)
#       define W300_SCWK_FOWCE_TCW          (1<<13)
#       define W300_SCWK_FOWCE_CBA          (1<<14)
#       define W300_SCWK_FOWCE_GA           (1<<15)
#define WADEON_SCWK_MOWE_CNTW               0x0035 /* PWW */
#       define WADEON_SCWK_MOWE_MAX_DYN_STOP_WAT 0x0007
#       define WADEON_SCWK_MOWE_FOWCEON     0x0700
#define WADEON_SDWAM_MODE_WEG               0x0158
#define WADEON_SEQ8_DATA                    0x03c5 /* VGA */
#define WADEON_SEQ8_IDX                     0x03c4 /* VGA */
#define WADEON_SNAPSHOT_F_COUNT             0x0244
#define WADEON_SNAPSHOT_VH_COUNTS           0x0240
#define WADEON_SNAPSHOT_VIF_COUNT           0x024c
#define WADEON_SWC_OFFSET                   0x15ac
#define WADEON_SWC_PITCH                    0x15b0
#define WADEON_SWC_PITCH_OFFSET             0x1428
#define WADEON_SWC_SC_BOTTOM                0x165c
#define WADEON_SWC_SC_BOTTOM_WIGHT          0x16f4
#define WADEON_SWC_SC_WIGHT                 0x1654
#define WADEON_SWC_X                        0x1414
#define WADEON_SWC_X_Y                      0x1590
#define WADEON_SWC_Y                        0x1418
#define WADEON_SWC_Y_X                      0x1434
#define WADEON_STATUS                       0x0f06 /* PCI */
#define WADEON_SUBPIC_CNTW                  0x0540 /* ? */
#define WADEON_SUB_CWASS                    0x0f0a /* PCI */
#define WADEON_SUWFACE_CNTW                 0x0b00
#       define WADEON_SUWF_TWANSWATION_DIS  (1 << 8)
#       define WADEON_NONSUWF_AP0_SWP_16BPP (1 << 20)
#       define WADEON_NONSUWF_AP0_SWP_32BPP (1 << 21)
#       define WADEON_NONSUWF_AP1_SWP_16BPP (1 << 22)
#       define WADEON_NONSUWF_AP1_SWP_32BPP (1 << 23)
#define WADEON_SUWFACE0_INFO                0x0b0c
#       define WADEON_SUWF_TIWE_COWOW_MACWO (0 << 16)
#       define WADEON_SUWF_TIWE_COWOW_BOTH  (1 << 16)
#       define WADEON_SUWF_TIWE_DEPTH_32BPP (2 << 16)
#       define WADEON_SUWF_TIWE_DEPTH_16BPP (3 << 16)
#       define W200_SUWF_TIWE_NONE          (0 << 16)
#       define W200_SUWF_TIWE_COWOW_MACWO   (1 << 16)
#       define W200_SUWF_TIWE_COWOW_MICWO   (2 << 16)
#       define W200_SUWF_TIWE_COWOW_BOTH    (3 << 16)
#       define W200_SUWF_TIWE_DEPTH_32BPP   (4 << 16)
#       define W200_SUWF_TIWE_DEPTH_16BPP   (5 << 16)
#       define W300_SUWF_TIWE_NONE          (0 << 16)
#       define W300_SUWF_TIWE_COWOW_MACWO   (1 << 16)
#       define W300_SUWF_TIWE_DEPTH_32BPP   (2 << 16)
#       define WADEON_SUWF_AP0_SWP_16BPP    (1 << 20)
#       define WADEON_SUWF_AP0_SWP_32BPP    (1 << 21)
#       define WADEON_SUWF_AP1_SWP_16BPP    (1 << 22)
#       define WADEON_SUWF_AP1_SWP_32BPP    (1 << 23)
#define WADEON_SUWFACE0_WOWEW_BOUND         0x0b04
#define WADEON_SUWFACE0_UPPEW_BOUND         0x0b08
#define WADEON_SUWFACE1_INFO                0x0b1c
#define WADEON_SUWFACE1_WOWEW_BOUND         0x0b14
#define WADEON_SUWFACE1_UPPEW_BOUND         0x0b18
#define WADEON_SUWFACE2_INFO                0x0b2c
#define WADEON_SUWFACE2_WOWEW_BOUND         0x0b24
#define WADEON_SUWFACE2_UPPEW_BOUND         0x0b28
#define WADEON_SUWFACE3_INFO                0x0b3c
#define WADEON_SUWFACE3_WOWEW_BOUND         0x0b34
#define WADEON_SUWFACE3_UPPEW_BOUND         0x0b38
#define WADEON_SUWFACE4_INFO                0x0b4c
#define WADEON_SUWFACE4_WOWEW_BOUND         0x0b44
#define WADEON_SUWFACE4_UPPEW_BOUND         0x0b48
#define WADEON_SUWFACE5_INFO                0x0b5c
#define WADEON_SUWFACE5_WOWEW_BOUND         0x0b54
#define WADEON_SUWFACE5_UPPEW_BOUND         0x0b58
#define WADEON_SUWFACE6_INFO                0x0b6c
#define WADEON_SUWFACE6_WOWEW_BOUND         0x0b64
#define WADEON_SUWFACE6_UPPEW_BOUND         0x0b68
#define WADEON_SUWFACE7_INFO                0x0b7c
#define WADEON_SUWFACE7_WOWEW_BOUND         0x0b74
#define WADEON_SUWFACE7_UPPEW_BOUND         0x0b78
#define WADEON_SW_SEMAPHOWE                 0x013c

#define WADEON_TEST_DEBUG_CNTW              0x0120
#define WADEON_TEST_DEBUG_CNTW__TEST_DEBUG_OUT_EN 0x00000001

#define WADEON_TEST_DEBUG_MUX               0x0124
#define WADEON_TEST_DEBUG_OUT               0x012c
#define WADEON_TMDS_PWW_CNTW                0x02a8
#define WADEON_TMDS_TWANSMITTEW_CNTW        0x02a4
#       define WADEON_TMDS_TWANSMITTEW_PWWEN  1
#       define WADEON_TMDS_TWANSMITTEW_PWWWST 2
#define WADEON_TWAIW_BWES_DEC               0x1614
#define WADEON_TWAIW_BWES_EWW               0x160c
#define WADEON_TWAIW_BWES_INC               0x1610
#define WADEON_TWAIW_X                      0x1618
#define WADEON_TWAIW_X_SUB                  0x1620

#define WADEON_VCWK_ECP_CNTW                0x0008 /* PWW */
#       define WADEON_VCWK_SWC_SEW_MASK     0x03
#       define WADEON_VCWK_SWC_SEW_CPUCWK   0x00
#       define WADEON_VCWK_SWC_SEW_PSCANCWK 0x01
#       define WADEON_VCWK_SWC_SEW_BYTECWK  0x02
#       define WADEON_VCWK_SWC_SEW_PPWWCWK  0x03
#       define WADEON_PIXCWK_AWWAYS_ONb     (1<<6)
#       define WADEON_PIXCWK_DAC_AWWAYS_ONb (1<<7)
#       define W300_DISP_DAC_PIXCWK_DAC_BWANK_OFF (1<<23)

#define WADEON_VENDOW_ID                    0x0f00 /* PCI */
#define WADEON_VGA_DDA_CONFIG               0x02e8
#define WADEON_VGA_DDA_ON_OFF               0x02ec
#define WADEON_VID_BUFFEW_CONTWOW           0x0900
#define WADEON_VIDEOMUX_CNTW                0x0190

/* VIP bus */
#define WADEON_VIPH_CH0_DATA                0x0c00
#define WADEON_VIPH_CH1_DATA                0x0c04
#define WADEON_VIPH_CH2_DATA                0x0c08
#define WADEON_VIPH_CH3_DATA                0x0c0c
#define WADEON_VIPH_CH0_ADDW                0x0c10
#define WADEON_VIPH_CH1_ADDW                0x0c14
#define WADEON_VIPH_CH2_ADDW                0x0c18
#define WADEON_VIPH_CH3_ADDW                0x0c1c
#define WADEON_VIPH_CH0_SBCNT               0x0c20
#define WADEON_VIPH_CH1_SBCNT               0x0c24
#define WADEON_VIPH_CH2_SBCNT               0x0c28
#define WADEON_VIPH_CH3_SBCNT               0x0c2c
#define WADEON_VIPH_CH0_ABCNT               0x0c30
#define WADEON_VIPH_CH1_ABCNT               0x0c34
#define WADEON_VIPH_CH2_ABCNT               0x0c38
#define WADEON_VIPH_CH3_ABCNT               0x0c3c
#define WADEON_VIPH_CONTWOW                 0x0c40
#       define WADEON_VIP_BUSY 0
#       define WADEON_VIP_IDWE 1
#       define WADEON_VIP_WESET 2
#       define WADEON_VIPH_EN               (1 << 21)
#define WADEON_VIPH_DV_WAT                  0x0c44
#define WADEON_VIPH_BM_CHUNK                0x0c48
#define WADEON_VIPH_DV_INT                  0x0c4c
#define WADEON_VIPH_TIMEOUT_STAT            0x0c50
#define WADEON_VIPH_TIMEOUT_STAT__VIPH_WEG_STAT 0x00000010
#define WADEON_VIPH_TIMEOUT_STAT__VIPH_WEG_AK   0x00000010
#define WADEON_VIPH_TIMEOUT_STAT__VIPH_WEGW_DIS 0x01000000

#define WADEON_VIPH_WEG_DATA                0x0084
#define WADEON_VIPH_WEG_ADDW                0x0080


#define WADEON_WAIT_UNTIW                   0x1720
#       define WADEON_WAIT_CWTC_PFWIP       (1 << 0)
#       define WADEON_WAIT_WE_CWTC_VWINE    (1 << 1)
#       define WADEON_WAIT_FE_CWTC_VWINE    (1 << 2)
#       define WADEON_WAIT_CWTC_VWINE       (1 << 3)
#       define WADEON_WAIT_DMA_VID_IDWE     (1 << 8)
#       define WADEON_WAIT_DMA_GUI_IDWE     (1 << 9)
#       define WADEON_WAIT_CMDFIFO          (1 << 10) /* wait fow CMDFIFO_ENTWIES */
#       define WADEON_WAIT_OV0_FWIP         (1 << 11)
#       define WADEON_WAIT_AGP_FWUSH        (1 << 13)
#       define WADEON_WAIT_2D_IDWE          (1 << 14)
#       define WADEON_WAIT_3D_IDWE          (1 << 15)
#       define WADEON_WAIT_2D_IDWECWEAN     (1 << 16)
#       define WADEON_WAIT_3D_IDWECWEAN     (1 << 17)
#       define WADEON_WAIT_HOST_IDWECWEAN   (1 << 18)
#       define WADEON_CMDFIFO_ENTWIES_SHIFT 10
#       define WADEON_CMDFIFO_ENTWIES_MASK  0x7f
#       define WADEON_WAIT_VAP_IDWE         (1 << 28)
#       define WADEON_WAIT_BOTH_CWTC_PFWIP  (1 << 30)
#       define WADEON_ENG_DISPWAY_SEWECT_CWTC0    (0 << 31)
#       define WADEON_ENG_DISPWAY_SEWECT_CWTC1    (1 << 31)

#define WADEON_X_MPWW_WEF_FB_DIV            0x000a /* PWW */
#define WADEON_XCWK_CNTW                    0x000d /* PWW */
#define WADEON_XDWW_CNTW                    0x000c /* PWW */
#define WADEON_XPWW_CNTW                    0x000b /* PWW */



				/* Wegistews fow 3D/TCW */
#define WADEON_PP_BOWDEW_COWOW_0            0x1d40
#define WADEON_PP_BOWDEW_COWOW_1            0x1d44
#define WADEON_PP_BOWDEW_COWOW_2            0x1d48
#define WADEON_PP_CNTW                      0x1c38
#       define WADEON_STIPPWE_ENABWE        (1 <<  0)
#       define WADEON_SCISSOW_ENABWE        (1 <<  1)
#       define WADEON_PATTEWN_ENABWE        (1 <<  2)
#       define WADEON_SHADOW_ENABWE         (1 <<  3)
#       define WADEON_TEX_ENABWE_MASK       (0xf << 4)
#       define WADEON_TEX_0_ENABWE          (1 <<  4)
#       define WADEON_TEX_1_ENABWE          (1 <<  5)
#       define WADEON_TEX_2_ENABWE          (1 <<  6)
#       define WADEON_TEX_3_ENABWE          (1 <<  7)
#       define WADEON_TEX_BWEND_ENABWE_MASK (0xf << 12)
#       define WADEON_TEX_BWEND_0_ENABWE    (1 << 12)
#       define WADEON_TEX_BWEND_1_ENABWE    (1 << 13)
#       define WADEON_TEX_BWEND_2_ENABWE    (1 << 14)
#       define WADEON_TEX_BWEND_3_ENABWE    (1 << 15)
#       define WADEON_PWANAW_YUV_ENABWE     (1 << 20)
#       define WADEON_SPECUWAW_ENABWE       (1 << 21)
#       define WADEON_FOG_ENABWE            (1 << 22)
#       define WADEON_AWPHA_TEST_ENABWE     (1 << 23)
#       define WADEON_ANTI_AWIAS_NONE       (0 << 24)
#       define WADEON_ANTI_AWIAS_WINE       (1 << 24)
#       define WADEON_ANTI_AWIAS_POWY       (2 << 24)
#       define WADEON_ANTI_AWIAS_WINE_POWY  (3 << 24)
#       define WADEON_BUMP_MAP_ENABWE       (1 << 26)
#       define WADEON_BUMPED_MAP_T0         (0 << 27)
#       define WADEON_BUMPED_MAP_T1         (1 << 27)
#       define WADEON_BUMPED_MAP_T2         (2 << 27)
#       define WADEON_TEX_3D_ENABWE_0       (1 << 29)
#       define WADEON_TEX_3D_ENABWE_1       (1 << 30)
#       define WADEON_MC_ENABWE             (1 << 31)
#define WADEON_PP_FOG_COWOW                 0x1c18
#       define WADEON_FOG_COWOW_MASK        0x00ffffff
#       define WADEON_FOG_VEWTEX            (0 << 24)
#       define WADEON_FOG_TABWE             (1 << 24)
#       define WADEON_FOG_USE_DEPTH         (0 << 25)
#       define WADEON_FOG_USE_DIFFUSE_AWPHA (2 << 25)
#       define WADEON_FOG_USE_SPEC_AWPHA    (3 << 25)
#define WADEON_PP_WUM_MATWIX                0x1d00
#define WADEON_PP_MISC                      0x1c14
#       define WADEON_WEF_AWPHA_MASK        0x000000ff
#       define WADEON_AWPHA_TEST_FAIW       (0 << 8)
#       define WADEON_AWPHA_TEST_WESS       (1 << 8)
#       define WADEON_AWPHA_TEST_WEQUAW     (2 << 8)
#       define WADEON_AWPHA_TEST_EQUAW      (3 << 8)
#       define WADEON_AWPHA_TEST_GEQUAW     (4 << 8)
#       define WADEON_AWPHA_TEST_GWEATEW    (5 << 8)
#       define WADEON_AWPHA_TEST_NEQUAW     (6 << 8)
#       define WADEON_AWPHA_TEST_PASS       (7 << 8)
#       define WADEON_AWPHA_TEST_OP_MASK    (7 << 8)
#       define WADEON_CHWOMA_FUNC_FAIW      (0 << 16)
#       define WADEON_CHWOMA_FUNC_PASS      (1 << 16)
#       define WADEON_CHWOMA_FUNC_NEQUAW    (2 << 16)
#       define WADEON_CHWOMA_FUNC_EQUAW     (3 << 16)
#       define WADEON_CHWOMA_KEY_NEAWEST    (0 << 18)
#       define WADEON_CHWOMA_KEY_ZEWO       (1 << 18)
#       define WADEON_SHADOW_ID_AUTO_INC    (1 << 20)
#       define WADEON_SHADOW_FUNC_EQUAW     (0 << 21)
#       define WADEON_SHADOW_FUNC_NEQUAW    (1 << 21)
#       define WADEON_SHADOW_PASS_1         (0 << 22)
#       define WADEON_SHADOW_PASS_2         (1 << 22)
#       define WADEON_WIGHT_HAND_CUBE_D3D   (0 << 24)
#       define WADEON_WIGHT_HAND_CUBE_OGW   (1 << 24)
#define WADEON_PP_WOT_MATWIX_0              0x1d58
#define WADEON_PP_WOT_MATWIX_1              0x1d5c
#define WADEON_PP_TXFIWTEW_0                0x1c54
#define WADEON_PP_TXFIWTEW_1                0x1c6c
#define WADEON_PP_TXFIWTEW_2                0x1c84
#       define WADEON_MAG_FIWTEW_NEAWEST                   (0  <<  0)
#       define WADEON_MAG_FIWTEW_WINEAW                    (1  <<  0)
#       define WADEON_MAG_FIWTEW_MASK                      (1  <<  0)
#       define WADEON_MIN_FIWTEW_NEAWEST                   (0  <<  1)
#       define WADEON_MIN_FIWTEW_WINEAW                    (1  <<  1)
#       define WADEON_MIN_FIWTEW_NEAWEST_MIP_NEAWEST       (2  <<  1)
#       define WADEON_MIN_FIWTEW_NEAWEST_MIP_WINEAW        (3  <<  1)
#       define WADEON_MIN_FIWTEW_WINEAW_MIP_NEAWEST        (6  <<  1)
#       define WADEON_MIN_FIWTEW_WINEAW_MIP_WINEAW         (7  <<  1)
#       define WADEON_MIN_FIWTEW_ANISO_NEAWEST             (8  <<  1)
#       define WADEON_MIN_FIWTEW_ANISO_WINEAW              (9  <<  1)
#       define WADEON_MIN_FIWTEW_ANISO_NEAWEST_MIP_NEAWEST (10 <<  1)
#       define WADEON_MIN_FIWTEW_ANISO_NEAWEST_MIP_WINEAW  (11 <<  1)
#       define WADEON_MIN_FIWTEW_MASK                      (15 <<  1)
#       define WADEON_MAX_ANISO_1_TO_1                     (0  <<  5)
#       define WADEON_MAX_ANISO_2_TO_1                     (1  <<  5)
#       define WADEON_MAX_ANISO_4_TO_1                     (2  <<  5)
#       define WADEON_MAX_ANISO_8_TO_1                     (3  <<  5)
#       define WADEON_MAX_ANISO_16_TO_1                    (4  <<  5)
#       define WADEON_MAX_ANISO_MASK                       (7  <<  5)
#       define WADEON_WOD_BIAS_MASK                        (0xff <<  8)
#       define WADEON_WOD_BIAS_SHIFT                       8
#       define WADEON_MAX_MIP_WEVEW_MASK                   (0x0f << 16)
#       define WADEON_MAX_MIP_WEVEW_SHIFT                  16
#       define WADEON_YUV_TO_WGB                           (1  << 20)
#       define WADEON_YUV_TEMPEWATUWE_COOW                 (0  << 21)
#       define WADEON_YUV_TEMPEWATUWE_HOT                  (1  << 21)
#       define WADEON_YUV_TEMPEWATUWE_MASK                 (1  << 21)
#       define WADEON_WWAPEN_S                             (1  << 22)
#       define WADEON_CWAMP_S_WWAP                         (0  << 23)
#       define WADEON_CWAMP_S_MIWWOW                       (1  << 23)
#       define WADEON_CWAMP_S_CWAMP_WAST                   (2  << 23)
#       define WADEON_CWAMP_S_MIWWOW_CWAMP_WAST            (3  << 23)
#       define WADEON_CWAMP_S_CWAMP_BOWDEW                 (4  << 23)
#       define WADEON_CWAMP_S_MIWWOW_CWAMP_BOWDEW          (5  << 23)
#       define WADEON_CWAMP_S_CWAMP_GW                     (6  << 23)
#       define WADEON_CWAMP_S_MIWWOW_CWAMP_GW              (7  << 23)
#       define WADEON_CWAMP_S_MASK                         (7  << 23)
#       define WADEON_WWAPEN_T                             (1  << 26)
#       define WADEON_CWAMP_T_WWAP                         (0  << 27)
#       define WADEON_CWAMP_T_MIWWOW                       (1  << 27)
#       define WADEON_CWAMP_T_CWAMP_WAST                   (2  << 27)
#       define WADEON_CWAMP_T_MIWWOW_CWAMP_WAST            (3  << 27)
#       define WADEON_CWAMP_T_CWAMP_BOWDEW                 (4  << 27)
#       define WADEON_CWAMP_T_MIWWOW_CWAMP_BOWDEW          (5  << 27)
#       define WADEON_CWAMP_T_CWAMP_GW                     (6  << 27)
#       define WADEON_CWAMP_T_MIWWOW_CWAMP_GW              (7  << 27)
#       define WADEON_CWAMP_T_MASK                         (7  << 27)
#       define WADEON_BOWDEW_MODE_OGW                      (0  << 31)
#       define WADEON_BOWDEW_MODE_D3D                      (1  << 31)
#define WADEON_PP_TXFOWMAT_0                0x1c58
#define WADEON_PP_TXFOWMAT_1                0x1c70
#define WADEON_PP_TXFOWMAT_2                0x1c88
#       define WADEON_TXFOWMAT_I8                 (0  <<  0)
#       define WADEON_TXFOWMAT_AI88               (1  <<  0)
#       define WADEON_TXFOWMAT_WGB332             (2  <<  0)
#       define WADEON_TXFOWMAT_AWGB1555           (3  <<  0)
#       define WADEON_TXFOWMAT_WGB565             (4  <<  0)
#       define WADEON_TXFOWMAT_AWGB4444           (5  <<  0)
#       define WADEON_TXFOWMAT_AWGB8888           (6  <<  0)
#       define WADEON_TXFOWMAT_WGBA8888           (7  <<  0)
#       define WADEON_TXFOWMAT_Y8                 (8  <<  0)
#       define WADEON_TXFOWMAT_VYUY422            (10 <<  0)
#       define WADEON_TXFOWMAT_YVYU422            (11 <<  0)
#       define WADEON_TXFOWMAT_DXT1               (12 <<  0)
#       define WADEON_TXFOWMAT_DXT23              (14 <<  0)
#       define WADEON_TXFOWMAT_DXT45              (15 <<  0)
#	define WADEON_TXFOWMAT_SHADOW16           (16 <<  0)
#	define WADEON_TXFOWMAT_SHADOW32           (17 <<  0)
#       define WADEON_TXFOWMAT_DUDV88             (18 <<  0)
#       define WADEON_TXFOWMAT_WDUDV655           (19 <<  0)
#       define WADEON_TXFOWMAT_WDUDUV8888         (20 <<  0)
#       define WADEON_TXFOWMAT_FOWMAT_MASK        (31 <<  0)
#       define WADEON_TXFOWMAT_FOWMAT_SHIFT       0
#       define WADEON_TXFOWMAT_APPWE_YUV_MODE     (1  <<  5)
#       define WADEON_TXFOWMAT_AWPHA_IN_MAP       (1  <<  6)
#       define WADEON_TXFOWMAT_NON_POWEW2         (1  <<  7)
#       define WADEON_TXFOWMAT_WIDTH_MASK         (15 <<  8)
#       define WADEON_TXFOWMAT_WIDTH_SHIFT        8
#       define WADEON_TXFOWMAT_HEIGHT_MASK        (15 << 12)
#       define WADEON_TXFOWMAT_HEIGHT_SHIFT       12
#       define WADEON_TXFOWMAT_F5_WIDTH_MASK      (15 << 16)
#       define WADEON_TXFOWMAT_F5_WIDTH_SHIFT     16
#       define WADEON_TXFOWMAT_F5_HEIGHT_MASK     (15 << 20)
#       define WADEON_TXFOWMAT_F5_HEIGHT_SHIFT    20
#       define WADEON_TXFOWMAT_ST_WOUTE_STQ0      (0  << 24)
#       define WADEON_TXFOWMAT_ST_WOUTE_MASK      (3  << 24)
#       define WADEON_TXFOWMAT_ST_WOUTE_STQ1      (1  << 24)
#       define WADEON_TXFOWMAT_ST_WOUTE_STQ2      (2  << 24)
#       define WADEON_TXFOWMAT_ENDIAN_NO_SWAP     (0  << 26)
#       define WADEON_TXFOWMAT_ENDIAN_16BPP_SWAP  (1  << 26)
#       define WADEON_TXFOWMAT_ENDIAN_32BPP_SWAP  (2  << 26)
#       define WADEON_TXFOWMAT_ENDIAN_HAWFDW_SWAP (3  << 26)
#       define WADEON_TXFOWMAT_AWPHA_MASK_ENABWE  (1  << 28)
#       define WADEON_TXFOWMAT_CHWOMA_KEY_ENABWE  (1  << 29)
#       define WADEON_TXFOWMAT_CUBIC_MAP_ENABWE   (1  << 30)
#       define WADEON_TXFOWMAT_PEWSPECTIVE_ENABWE (1  << 31)
#define WADEON_PP_CUBIC_FACES_0             0x1d24
#define WADEON_PP_CUBIC_FACES_1             0x1d28
#define WADEON_PP_CUBIC_FACES_2             0x1d2c
#       define WADEON_FACE_WIDTH_1_SHIFT          0
#       define WADEON_FACE_HEIGHT_1_SHIFT         4
#       define WADEON_FACE_WIDTH_1_MASK           (0xf << 0)
#       define WADEON_FACE_HEIGHT_1_MASK          (0xf << 4)
#       define WADEON_FACE_WIDTH_2_SHIFT          8
#       define WADEON_FACE_HEIGHT_2_SHIFT         12
#       define WADEON_FACE_WIDTH_2_MASK           (0xf << 8)
#       define WADEON_FACE_HEIGHT_2_MASK          (0xf << 12)
#       define WADEON_FACE_WIDTH_3_SHIFT          16
#       define WADEON_FACE_HEIGHT_3_SHIFT         20
#       define WADEON_FACE_WIDTH_3_MASK           (0xf << 16)
#       define WADEON_FACE_HEIGHT_3_MASK          (0xf << 20)
#       define WADEON_FACE_WIDTH_4_SHIFT          24
#       define WADEON_FACE_HEIGHT_4_SHIFT         28
#       define WADEON_FACE_WIDTH_4_MASK           (0xf << 24)
#       define WADEON_FACE_HEIGHT_4_MASK          (0xf << 28)

#define WADEON_PP_TXOFFSET_0                0x1c5c
#define WADEON_PP_TXOFFSET_1                0x1c74
#define WADEON_PP_TXOFFSET_2                0x1c8c
#       define WADEON_TXO_ENDIAN_NO_SWAP     (0 << 0)
#       define WADEON_TXO_ENDIAN_BYTE_SWAP   (1 << 0)
#       define WADEON_TXO_ENDIAN_WOWD_SWAP   (2 << 0)
#       define WADEON_TXO_ENDIAN_HAWFDW_SWAP (3 << 0)
#       define WADEON_TXO_MACWO_WINEAW       (0 << 2)
#       define WADEON_TXO_MACWO_TIWE         (1 << 2)
#       define WADEON_TXO_MICWO_WINEAW       (0 << 3)
#       define WADEON_TXO_MICWO_TIWE_X2      (1 << 3)
#       define WADEON_TXO_MICWO_TIWE_OPT     (2 << 3)
#       define WADEON_TXO_OFFSET_MASK        0xffffffe0
#       define WADEON_TXO_OFFSET_SHIFT       5

#define WADEON_PP_CUBIC_OFFSET_T0_0         0x1dd0  /* bits [31:5] */
#define WADEON_PP_CUBIC_OFFSET_T0_1         0x1dd4
#define WADEON_PP_CUBIC_OFFSET_T0_2         0x1dd8
#define WADEON_PP_CUBIC_OFFSET_T0_3         0x1ddc
#define WADEON_PP_CUBIC_OFFSET_T0_4         0x1de0
#define WADEON_PP_CUBIC_OFFSET_T1_0         0x1e00
#define WADEON_PP_CUBIC_OFFSET_T1_1         0x1e04
#define WADEON_PP_CUBIC_OFFSET_T1_2         0x1e08
#define WADEON_PP_CUBIC_OFFSET_T1_3         0x1e0c
#define WADEON_PP_CUBIC_OFFSET_T1_4         0x1e10
#define WADEON_PP_CUBIC_OFFSET_T2_0         0x1e14
#define WADEON_PP_CUBIC_OFFSET_T2_1         0x1e18
#define WADEON_PP_CUBIC_OFFSET_T2_2         0x1e1c
#define WADEON_PP_CUBIC_OFFSET_T2_3         0x1e20
#define WADEON_PP_CUBIC_OFFSET_T2_4         0x1e24

#define WADEON_PP_TEX_SIZE_0                0x1d04  /* NPOT */
#define WADEON_PP_TEX_SIZE_1                0x1d0c
#define WADEON_PP_TEX_SIZE_2                0x1d14
#       define WADEON_TEX_USIZE_MASK        (0x7ff << 0)
#       define WADEON_TEX_USIZE_SHIFT       0
#       define WADEON_TEX_VSIZE_MASK        (0x7ff << 16)
#       define WADEON_TEX_VSIZE_SHIFT       16
#       define WADEON_SIGNED_WGB_MASK       (1 << 30)
#       define WADEON_SIGNED_WGB_SHIFT      30
#       define WADEON_SIGNED_AWPHA_MASK     (1 << 31)
#       define WADEON_SIGNED_AWPHA_SHIFT    31
#define WADEON_PP_TEX_PITCH_0               0x1d08  /* NPOT */
#define WADEON_PP_TEX_PITCH_1               0x1d10  /* NPOT */
#define WADEON_PP_TEX_PITCH_2               0x1d18  /* NPOT */
/* note: bits 13-5: 32 byte awigned stwide of textuwe map */

#define WADEON_PP_TXCBWEND_0                0x1c60
#define WADEON_PP_TXCBWEND_1                0x1c78
#define WADEON_PP_TXCBWEND_2                0x1c90
#       define WADEON_COWOW_AWG_A_SHIFT          0
#       define WADEON_COWOW_AWG_A_MASK           (0x1f << 0)
#       define WADEON_COWOW_AWG_A_ZEWO           (0    << 0)
#       define WADEON_COWOW_AWG_A_CUWWENT_COWOW  (2    << 0)
#       define WADEON_COWOW_AWG_A_CUWWENT_AWPHA  (3    << 0)
#       define WADEON_COWOW_AWG_A_DIFFUSE_COWOW  (4    << 0)
#       define WADEON_COWOW_AWG_A_DIFFUSE_AWPHA  (5    << 0)
#       define WADEON_COWOW_AWG_A_SPECUWAW_COWOW (6    << 0)
#       define WADEON_COWOW_AWG_A_SPECUWAW_AWPHA (7    << 0)
#       define WADEON_COWOW_AWG_A_TFACTOW_COWOW  (8    << 0)
#       define WADEON_COWOW_AWG_A_TFACTOW_AWPHA  (9    << 0)
#       define WADEON_COWOW_AWG_A_T0_COWOW       (10   << 0)
#       define WADEON_COWOW_AWG_A_T0_AWPHA       (11   << 0)
#       define WADEON_COWOW_AWG_A_T1_COWOW       (12   << 0)
#       define WADEON_COWOW_AWG_A_T1_AWPHA       (13   << 0)
#       define WADEON_COWOW_AWG_A_T2_COWOW       (14   << 0)
#       define WADEON_COWOW_AWG_A_T2_AWPHA       (15   << 0)
#       define WADEON_COWOW_AWG_A_T3_COWOW       (16   << 0)
#       define WADEON_COWOW_AWG_A_T3_AWPHA       (17   << 0)
#       define WADEON_COWOW_AWG_B_SHIFT          5
#       define WADEON_COWOW_AWG_B_MASK           (0x1f << 5)
#       define WADEON_COWOW_AWG_B_ZEWO           (0    << 5)
#       define WADEON_COWOW_AWG_B_CUWWENT_COWOW  (2    << 5)
#       define WADEON_COWOW_AWG_B_CUWWENT_AWPHA  (3    << 5)
#       define WADEON_COWOW_AWG_B_DIFFUSE_COWOW  (4    << 5)
#       define WADEON_COWOW_AWG_B_DIFFUSE_AWPHA  (5    << 5)
#       define WADEON_COWOW_AWG_B_SPECUWAW_COWOW (6    << 5)
#       define WADEON_COWOW_AWG_B_SPECUWAW_AWPHA (7    << 5)
#       define WADEON_COWOW_AWG_B_TFACTOW_COWOW  (8    << 5)
#       define WADEON_COWOW_AWG_B_TFACTOW_AWPHA  (9    << 5)
#       define WADEON_COWOW_AWG_B_T0_COWOW       (10   << 5)
#       define WADEON_COWOW_AWG_B_T0_AWPHA       (11   << 5)
#       define WADEON_COWOW_AWG_B_T1_COWOW       (12   << 5)
#       define WADEON_COWOW_AWG_B_T1_AWPHA       (13   << 5)
#       define WADEON_COWOW_AWG_B_T2_COWOW       (14   << 5)
#       define WADEON_COWOW_AWG_B_T2_AWPHA       (15   << 5)
#       define WADEON_COWOW_AWG_B_T3_COWOW       (16   << 5)
#       define WADEON_COWOW_AWG_B_T3_AWPHA       (17   << 5)
#       define WADEON_COWOW_AWG_C_SHIFT          10
#       define WADEON_COWOW_AWG_C_MASK           (0x1f << 10)
#       define WADEON_COWOW_AWG_C_ZEWO           (0    << 10)
#       define WADEON_COWOW_AWG_C_CUWWENT_COWOW  (2    << 10)
#       define WADEON_COWOW_AWG_C_CUWWENT_AWPHA  (3    << 10)
#       define WADEON_COWOW_AWG_C_DIFFUSE_COWOW  (4    << 10)
#       define WADEON_COWOW_AWG_C_DIFFUSE_AWPHA  (5    << 10)
#       define WADEON_COWOW_AWG_C_SPECUWAW_COWOW (6    << 10)
#       define WADEON_COWOW_AWG_C_SPECUWAW_AWPHA (7    << 10)
#       define WADEON_COWOW_AWG_C_TFACTOW_COWOW  (8    << 10)
#       define WADEON_COWOW_AWG_C_TFACTOW_AWPHA  (9    << 10)
#       define WADEON_COWOW_AWG_C_T0_COWOW       (10   << 10)
#       define WADEON_COWOW_AWG_C_T0_AWPHA       (11   << 10)
#       define WADEON_COWOW_AWG_C_T1_COWOW       (12   << 10)
#       define WADEON_COWOW_AWG_C_T1_AWPHA       (13   << 10)
#       define WADEON_COWOW_AWG_C_T2_COWOW       (14   << 10)
#       define WADEON_COWOW_AWG_C_T2_AWPHA       (15   << 10)
#       define WADEON_COWOW_AWG_C_T3_COWOW       (16   << 10)
#       define WADEON_COWOW_AWG_C_T3_AWPHA       (17   << 10)
#       define WADEON_COMP_AWG_A                 (1 << 15)
#       define WADEON_COMP_AWG_A_SHIFT           15
#       define WADEON_COMP_AWG_B                 (1 << 16)
#       define WADEON_COMP_AWG_B_SHIFT           16
#       define WADEON_COMP_AWG_C                 (1 << 17)
#       define WADEON_COMP_AWG_C_SHIFT           17
#       define WADEON_BWEND_CTW_MASK             (7 << 18)
#       define WADEON_BWEND_CTW_ADD              (0 << 18)
#       define WADEON_BWEND_CTW_SUBTWACT         (1 << 18)
#       define WADEON_BWEND_CTW_ADDSIGNED        (2 << 18)
#       define WADEON_BWEND_CTW_BWEND            (3 << 18)
#       define WADEON_BWEND_CTW_DOT3             (4 << 18)
#       define WADEON_SCAWE_SHIFT                21
#       define WADEON_SCAWE_MASK                 (3 << 21)
#       define WADEON_SCAWE_1X                   (0 << 21)
#       define WADEON_SCAWE_2X                   (1 << 21)
#       define WADEON_SCAWE_4X                   (2 << 21)
#       define WADEON_CWAMP_TX                   (1 << 23)
#       define WADEON_T0_EQ_TCUW                 (1 << 24)
#       define WADEON_T1_EQ_TCUW                 (1 << 25)
#       define WADEON_T2_EQ_TCUW                 (1 << 26)
#       define WADEON_T3_EQ_TCUW                 (1 << 27)
#       define WADEON_COWOW_AWG_MASK             0x1f
#       define WADEON_COMP_AWG_SHIFT             15
#define WADEON_PP_TXABWEND_0                0x1c64
#define WADEON_PP_TXABWEND_1                0x1c7c
#define WADEON_PP_TXABWEND_2                0x1c94
#       define WADEON_AWPHA_AWG_A_SHIFT          0
#       define WADEON_AWPHA_AWG_A_MASK           (0xf << 0)
#       define WADEON_AWPHA_AWG_A_ZEWO           (0   << 0)
#       define WADEON_AWPHA_AWG_A_CUWWENT_AWPHA  (1   << 0)
#       define WADEON_AWPHA_AWG_A_DIFFUSE_AWPHA  (2   << 0)
#       define WADEON_AWPHA_AWG_A_SPECUWAW_AWPHA (3   << 0)
#       define WADEON_AWPHA_AWG_A_TFACTOW_AWPHA  (4   << 0)
#       define WADEON_AWPHA_AWG_A_T0_AWPHA       (5   << 0)
#       define WADEON_AWPHA_AWG_A_T1_AWPHA       (6   << 0)
#       define WADEON_AWPHA_AWG_A_T2_AWPHA       (7   << 0)
#       define WADEON_AWPHA_AWG_A_T3_AWPHA       (8   << 0)
#       define WADEON_AWPHA_AWG_B_SHIFT          4
#       define WADEON_AWPHA_AWG_B_MASK           (0xf << 4)
#       define WADEON_AWPHA_AWG_B_ZEWO           (0   << 4)
#       define WADEON_AWPHA_AWG_B_CUWWENT_AWPHA  (1   << 4)
#       define WADEON_AWPHA_AWG_B_DIFFUSE_AWPHA  (2   << 4)
#       define WADEON_AWPHA_AWG_B_SPECUWAW_AWPHA (3   << 4)
#       define WADEON_AWPHA_AWG_B_TFACTOW_AWPHA  (4   << 4)
#       define WADEON_AWPHA_AWG_B_T0_AWPHA       (5   << 4)
#       define WADEON_AWPHA_AWG_B_T1_AWPHA       (6   << 4)
#       define WADEON_AWPHA_AWG_B_T2_AWPHA       (7   << 4)
#       define WADEON_AWPHA_AWG_B_T3_AWPHA       (8   << 4)
#       define WADEON_AWPHA_AWG_C_SHIFT          8
#       define WADEON_AWPHA_AWG_C_MASK           (0xf << 8)
#       define WADEON_AWPHA_AWG_C_ZEWO           (0   << 8)
#       define WADEON_AWPHA_AWG_C_CUWWENT_AWPHA  (1   << 8)
#       define WADEON_AWPHA_AWG_C_DIFFUSE_AWPHA  (2   << 8)
#       define WADEON_AWPHA_AWG_C_SPECUWAW_AWPHA (3   << 8)
#       define WADEON_AWPHA_AWG_C_TFACTOW_AWPHA  (4   << 8)
#       define WADEON_AWPHA_AWG_C_T0_AWPHA       (5   << 8)
#       define WADEON_AWPHA_AWG_C_T1_AWPHA       (6   << 8)
#       define WADEON_AWPHA_AWG_C_T2_AWPHA       (7   << 8)
#       define WADEON_AWPHA_AWG_C_T3_AWPHA       (8   << 8)
#       define WADEON_DOT_AWPHA_DONT_WEPWICATE   (1   << 9)
#       define WADEON_AWPHA_AWG_MASK             0xf

#define WADEON_PP_TFACTOW_0                 0x1c68
#define WADEON_PP_TFACTOW_1                 0x1c80
#define WADEON_PP_TFACTOW_2                 0x1c98

#define WADEON_WB3D_BWENDCNTW               0x1c20
#       define WADEON_COMB_FCN_MASK                    (3  << 12)
#       define WADEON_COMB_FCN_ADD_CWAMP               (0  << 12)
#       define WADEON_COMB_FCN_ADD_NOCWAMP             (1  << 12)
#       define WADEON_COMB_FCN_SUB_CWAMP               (2  << 12)
#       define WADEON_COMB_FCN_SUB_NOCWAMP             (3  << 12)
#       define WADEON_SWC_BWEND_GW_ZEWO                (32 << 16)
#       define WADEON_SWC_BWEND_GW_ONE                 (33 << 16)
#       define WADEON_SWC_BWEND_GW_SWC_COWOW           (34 << 16)
#       define WADEON_SWC_BWEND_GW_ONE_MINUS_SWC_COWOW (35 << 16)
#       define WADEON_SWC_BWEND_GW_DST_COWOW           (36 << 16)
#       define WADEON_SWC_BWEND_GW_ONE_MINUS_DST_COWOW (37 << 16)
#       define WADEON_SWC_BWEND_GW_SWC_AWPHA           (38 << 16)
#       define WADEON_SWC_BWEND_GW_ONE_MINUS_SWC_AWPHA (39 << 16)
#       define WADEON_SWC_BWEND_GW_DST_AWPHA           (40 << 16)
#       define WADEON_SWC_BWEND_GW_ONE_MINUS_DST_AWPHA (41 << 16)
#       define WADEON_SWC_BWEND_GW_SWC_AWPHA_SATUWATE  (42 << 16)
#       define WADEON_SWC_BWEND_MASK                   (63 << 16)
#       define WADEON_DST_BWEND_GW_ZEWO                (32 << 24)
#       define WADEON_DST_BWEND_GW_ONE                 (33 << 24)
#       define WADEON_DST_BWEND_GW_SWC_COWOW           (34 << 24)
#       define WADEON_DST_BWEND_GW_ONE_MINUS_SWC_COWOW (35 << 24)
#       define WADEON_DST_BWEND_GW_DST_COWOW           (36 << 24)
#       define WADEON_DST_BWEND_GW_ONE_MINUS_DST_COWOW (37 << 24)
#       define WADEON_DST_BWEND_GW_SWC_AWPHA           (38 << 24)
#       define WADEON_DST_BWEND_GW_ONE_MINUS_SWC_AWPHA (39 << 24)
#       define WADEON_DST_BWEND_GW_DST_AWPHA           (40 << 24)
#       define WADEON_DST_BWEND_GW_ONE_MINUS_DST_AWPHA (41 << 24)
#       define WADEON_DST_BWEND_MASK                   (63 << 24)
#define WADEON_WB3D_CNTW                    0x1c3c
#       define WADEON_AWPHA_BWEND_ENABWE       (1  <<  0)
#       define WADEON_PWANE_MASK_ENABWE        (1  <<  1)
#       define WADEON_DITHEW_ENABWE            (1  <<  2)
#       define WADEON_WOUND_ENABWE             (1  <<  3)
#       define WADEON_SCAWE_DITHEW_ENABWE      (1  <<  4)
#       define WADEON_DITHEW_INIT              (1  <<  5)
#       define WADEON_WOP_ENABWE               (1  <<  6)
#       define WADEON_STENCIW_ENABWE           (1  <<  7)
#       define WADEON_Z_ENABWE                 (1  <<  8)
#       define WADEON_DEPTHXY_OFFSET_ENABWE    (1  <<  9)
#       define WADEON_WB3D_COWOW_FOWMAT_SHIFT  10

#       define WADEON_COWOW_FOWMAT_AWGB1555    3
#       define WADEON_COWOW_FOWMAT_WGB565      4
#       define WADEON_COWOW_FOWMAT_AWGB8888    6
#       define WADEON_COWOW_FOWMAT_WGB332      7
#       define WADEON_COWOW_FOWMAT_Y8          8
#       define WADEON_COWOW_FOWMAT_WGB8        9
#       define WADEON_COWOW_FOWMAT_YUV422_VYUY 11
#       define WADEON_COWOW_FOWMAT_YUV422_YVYU 12
#       define WADEON_COWOW_FOWMAT_aYUV444     14
#       define WADEON_COWOW_FOWMAT_AWGB4444    15

#       define WADEON_CWWCMP_FWIP_ENABWE       (1  << 14)
#define WADEON_WB3D_COWOWOFFSET             0x1c40
#       define WADEON_COWOWOFFSET_MASK      0xfffffff0
#define WADEON_WB3D_COWOWPITCH              0x1c48
#       define WADEON_COWOWPITCH_MASK         0x000001ff8
#       define WADEON_COWOW_TIWE_ENABWE       (1 << 16)
#       define WADEON_COWOW_MICWOTIWE_ENABWE  (1 << 17)
#       define WADEON_COWOW_ENDIAN_NO_SWAP    (0 << 18)
#       define WADEON_COWOW_ENDIAN_WOWD_SWAP  (1 << 18)
#       define WADEON_COWOW_ENDIAN_DWOWD_SWAP (2 << 18)
#define WADEON_WB3D_DEPTHOFFSET             0x1c24
#define WADEON_WB3D_DEPTHPITCH              0x1c28
#       define WADEON_DEPTHPITCH_MASK         0x00001ff8
#       define WADEON_DEPTH_ENDIAN_NO_SWAP    (0 << 18)
#       define WADEON_DEPTH_ENDIAN_WOWD_SWAP  (1 << 18)
#       define WADEON_DEPTH_ENDIAN_DWOWD_SWAP (2 << 18)
#define WADEON_WB3D_PWANEMASK               0x1d84
#define WADEON_WB3D_WOPCNTW                 0x1d80
#       define WADEON_WOP_MASK              (15 << 8)
#       define WADEON_WOP_CWEAW             (0  << 8)
#       define WADEON_WOP_NOW               (1  << 8)
#       define WADEON_WOP_AND_INVEWTED      (2  << 8)
#       define WADEON_WOP_COPY_INVEWTED     (3  << 8)
#       define WADEON_WOP_AND_WEVEWSE       (4  << 8)
#       define WADEON_WOP_INVEWT            (5  << 8)
#       define WADEON_WOP_XOW               (6  << 8)
#       define WADEON_WOP_NAND              (7  << 8)
#       define WADEON_WOP_AND               (8  << 8)
#       define WADEON_WOP_EQUIV             (9  << 8)
#       define WADEON_WOP_NOOP              (10 << 8)
#       define WADEON_WOP_OW_INVEWTED       (11 << 8)
#       define WADEON_WOP_COPY              (12 << 8)
#       define WADEON_WOP_OW_WEVEWSE        (13 << 8)
#       define WADEON_WOP_OW                (14 << 8)
#       define WADEON_WOP_SET               (15 << 8)
#define WADEON_WB3D_STENCIWWEFMASK          0x1d7c
#       define WADEON_STENCIW_WEF_SHIFT       0
#       define WADEON_STENCIW_WEF_MASK        (0xff << 0)
#       define WADEON_STENCIW_MASK_SHIFT      16
#       define WADEON_STENCIW_VAWUE_MASK      (0xff << 16)
#       define WADEON_STENCIW_WWITEMASK_SHIFT 24
#       define WADEON_STENCIW_WWITE_MASK      (0xff << 24)
#define WADEON_WB3D_ZSTENCIWCNTW            0x1c2c
#       define WADEON_DEPTH_FOWMAT_MASK          (0xf << 0)
#       define WADEON_DEPTH_FOWMAT_16BIT_INT_Z   (0  <<  0)
#       define WADEON_DEPTH_FOWMAT_24BIT_INT_Z   (2  <<  0)
#       define WADEON_DEPTH_FOWMAT_24BIT_FWOAT_Z (3  <<  0)
#       define WADEON_DEPTH_FOWMAT_32BIT_INT_Z   (4  <<  0)
#       define WADEON_DEPTH_FOWMAT_32BIT_FWOAT_Z (5  <<  0)
#       define WADEON_DEPTH_FOWMAT_16BIT_FWOAT_W (7  <<  0)
#       define WADEON_DEPTH_FOWMAT_24BIT_FWOAT_W (9  <<  0)
#       define WADEON_DEPTH_FOWMAT_32BIT_FWOAT_W (11 <<  0)
#       define WADEON_Z_TEST_NEVEW               (0  <<  4)
#       define WADEON_Z_TEST_WESS                (1  <<  4)
#       define WADEON_Z_TEST_WEQUAW              (2  <<  4)
#       define WADEON_Z_TEST_EQUAW               (3  <<  4)
#       define WADEON_Z_TEST_GEQUAW              (4  <<  4)
#       define WADEON_Z_TEST_GWEATEW             (5  <<  4)
#       define WADEON_Z_TEST_NEQUAW              (6  <<  4)
#       define WADEON_Z_TEST_AWWAYS              (7  <<  4)
#       define WADEON_Z_TEST_MASK                (7  <<  4)
#       define WADEON_STENCIW_TEST_NEVEW         (0  << 12)
#       define WADEON_STENCIW_TEST_WESS          (1  << 12)
#       define WADEON_STENCIW_TEST_WEQUAW        (2  << 12)
#       define WADEON_STENCIW_TEST_EQUAW         (3  << 12)
#       define WADEON_STENCIW_TEST_GEQUAW        (4  << 12)
#       define WADEON_STENCIW_TEST_GWEATEW       (5  << 12)
#       define WADEON_STENCIW_TEST_NEQUAW        (6  << 12)
#       define WADEON_STENCIW_TEST_AWWAYS        (7  << 12)
#       define WADEON_STENCIW_TEST_MASK          (0x7 << 12)
#       define WADEON_STENCIW_FAIW_KEEP          (0  << 16)
#       define WADEON_STENCIW_FAIW_ZEWO          (1  << 16)
#       define WADEON_STENCIW_FAIW_WEPWACE       (2  << 16)
#       define WADEON_STENCIW_FAIW_INC           (3  << 16)
#       define WADEON_STENCIW_FAIW_DEC           (4  << 16)
#       define WADEON_STENCIW_FAIW_INVEWT        (5  << 16)
#       define WADEON_STENCIW_FAIW_MASK          (0x7 << 16)
#       define WADEON_STENCIW_ZPASS_KEEP         (0  << 20)
#       define WADEON_STENCIW_ZPASS_ZEWO         (1  << 20)
#       define WADEON_STENCIW_ZPASS_WEPWACE      (2  << 20)
#       define WADEON_STENCIW_ZPASS_INC          (3  << 20)
#       define WADEON_STENCIW_ZPASS_DEC          (4  << 20)
#       define WADEON_STENCIW_ZPASS_INVEWT       (5  << 20)
#       define WADEON_STENCIW_ZPASS_MASK         (0x7 << 20)
#       define WADEON_STENCIW_ZFAIW_KEEP         (0  << 24)
#       define WADEON_STENCIW_ZFAIW_ZEWO         (1  << 24)
#       define WADEON_STENCIW_ZFAIW_WEPWACE      (2  << 24)
#       define WADEON_STENCIW_ZFAIW_INC          (3  << 24)
#       define WADEON_STENCIW_ZFAIW_DEC          (4  << 24)
#       define WADEON_STENCIW_ZFAIW_INVEWT       (5  << 24)
#       define WADEON_STENCIW_ZFAIW_MASK         (0x7 << 24)
#       define WADEON_Z_COMPWESSION_ENABWE       (1  << 28)
#       define WADEON_FOWCE_Z_DIWTY              (1  << 29)
#       define WADEON_Z_WWITE_ENABWE             (1  << 30)
#define WADEON_WE_WINE_PATTEWN              0x1cd0
#       define WADEON_WINE_PATTEWN_MASK             0x0000ffff
#       define WADEON_WINE_WEPEAT_COUNT_SHIFT       16
#       define WADEON_WINE_PATTEWN_STAWT_SHIFT      24
#       define WADEON_WINE_PATTEWN_WITTWE_BIT_OWDEW (0 << 28)
#       define WADEON_WINE_PATTEWN_BIG_BIT_OWDEW    (1 << 28)
#       define WADEON_WINE_PATTEWN_AUTO_WESET       (1 << 29)
#define WADEON_WE_WINE_STATE                0x1cd4
#       define WADEON_WINE_CUWWENT_PTW_SHIFT   0
#       define WADEON_WINE_CUWWENT_COUNT_SHIFT 8
#define WADEON_WE_MISC                      0x26c4
#       define WADEON_STIPPWE_COOWD_MASK       0x1f
#       define WADEON_STIPPWE_X_OFFSET_SHIFT   0
#       define WADEON_STIPPWE_X_OFFSET_MASK    (0x1f << 0)
#       define WADEON_STIPPWE_Y_OFFSET_SHIFT   8
#       define WADEON_STIPPWE_Y_OFFSET_MASK    (0x1f << 8)
#       define WADEON_STIPPWE_WITTWE_BIT_OWDEW (0 << 16)
#       define WADEON_STIPPWE_BIG_BIT_OWDEW    (1 << 16)
#define WADEON_WE_SOWID_COWOW               0x1c1c
#define WADEON_WE_TOP_WEFT                  0x26c0
#       define WADEON_WE_WEFT_SHIFT         0
#       define WADEON_WE_TOP_SHIFT          16
#define WADEON_WE_WIDTH_HEIGHT              0x1c44
#       define WADEON_WE_WIDTH_SHIFT        0
#       define WADEON_WE_HEIGHT_SHIFT       16

#define WADEON_WB3D_ZPASS_DATA 0x3290
#define WADEON_WB3D_ZPASS_ADDW 0x3294

#define WADEON_SE_CNTW                      0x1c4c
#       define WADEON_FFACE_CUWW_CW          (0 <<  0)
#       define WADEON_FFACE_CUWW_CCW         (1 <<  0)
#       define WADEON_FFACE_CUWW_DIW_MASK    (1 <<  0)
#       define WADEON_BFACE_CUWW             (0 <<  1)
#       define WADEON_BFACE_SOWID            (3 <<  1)
#       define WADEON_FFACE_CUWW             (0 <<  3)
#       define WADEON_FFACE_SOWID            (3 <<  3)
#       define WADEON_FFACE_CUWW_MASK        (3 <<  3)
#       define WADEON_BADVTX_CUWW_DISABWE    (1 <<  5)
#       define WADEON_FWAT_SHADE_VTX_0       (0 <<  6)
#       define WADEON_FWAT_SHADE_VTX_1       (1 <<  6)
#       define WADEON_FWAT_SHADE_VTX_2       (2 <<  6)
#       define WADEON_FWAT_SHADE_VTX_WAST    (3 <<  6)
#       define WADEON_DIFFUSE_SHADE_SOWID    (0 <<  8)
#       define WADEON_DIFFUSE_SHADE_FWAT     (1 <<  8)
#       define WADEON_DIFFUSE_SHADE_GOUWAUD  (2 <<  8)
#       define WADEON_DIFFUSE_SHADE_MASK     (3 <<  8)
#       define WADEON_AWPHA_SHADE_SOWID      (0 << 10)
#       define WADEON_AWPHA_SHADE_FWAT       (1 << 10)
#       define WADEON_AWPHA_SHADE_GOUWAUD    (2 << 10)
#       define WADEON_AWPHA_SHADE_MASK       (3 << 10)
#       define WADEON_SPECUWAW_SHADE_SOWID   (0 << 12)
#       define WADEON_SPECUWAW_SHADE_FWAT    (1 << 12)
#       define WADEON_SPECUWAW_SHADE_GOUWAUD (2 << 12)
#       define WADEON_SPECUWAW_SHADE_MASK    (3 << 12)
#       define WADEON_FOG_SHADE_SOWID        (0 << 14)
#       define WADEON_FOG_SHADE_FWAT         (1 << 14)
#       define WADEON_FOG_SHADE_GOUWAUD      (2 << 14)
#       define WADEON_FOG_SHADE_MASK         (3 << 14)
#       define WADEON_ZBIAS_ENABWE_POINT     (1 << 16)
#       define WADEON_ZBIAS_ENABWE_WINE      (1 << 17)
#       define WADEON_ZBIAS_ENABWE_TWI       (1 << 18)
#       define WADEON_WIDEWINE_ENABWE        (1 << 20)
#       define WADEON_VPOWT_XY_XFOWM_ENABWE  (1 << 24)
#       define WADEON_VPOWT_Z_XFOWM_ENABWE   (1 << 25)
#       define WADEON_VTX_PIX_CENTEW_D3D     (0 << 27)
#       define WADEON_VTX_PIX_CENTEW_OGW     (1 << 27)
#       define WADEON_WOUND_MODE_TWUNC       (0 << 28)
#       define WADEON_WOUND_MODE_WOUND       (1 << 28)
#       define WADEON_WOUND_MODE_WOUND_EVEN  (2 << 28)
#       define WADEON_WOUND_MODE_WOUND_ODD   (3 << 28)
#       define WADEON_WOUND_PWEC_16TH_PIX    (0 << 30)
#       define WADEON_WOUND_PWEC_8TH_PIX     (1 << 30)
#       define WADEON_WOUND_PWEC_4TH_PIX     (2 << 30)
#       define WADEON_WOUND_PWEC_HAWF_PIX    (3 << 30)
#define W200_WE_CNTW				0x1c50
#       define W200_STIPPWE_ENABWE		0x1
#       define W200_SCISSOW_ENABWE		0x2
#       define W200_PATTEWN_ENABWE		0x4
#       define W200_PEWSPECTIVE_ENABWE		0x8
#       define W200_POINT_SMOOTH		0x20
#       define W200_VTX_STQ0_D3D		0x00010000
#       define W200_VTX_STQ1_D3D		0x00040000
#       define W200_VTX_STQ2_D3D		0x00100000
#       define W200_VTX_STQ3_D3D		0x00400000
#       define W200_VTX_STQ4_D3D		0x01000000
#       define W200_VTX_STQ5_D3D		0x04000000
#define WADEON_SE_CNTW_STATUS               0x2140
#       define WADEON_VC_NO_SWAP            (0 << 0)
#       define WADEON_VC_16BIT_SWAP         (1 << 0)
#       define WADEON_VC_32BIT_SWAP         (2 << 0)
#       define WADEON_VC_HAWF_DWOWD_SWAP    (3 << 0)
#       define WADEON_TCW_BYPASS            (1 << 8)
#define WADEON_SE_COOWD_FMT                 0x1c50
#       define WADEON_VTX_XY_PWE_MUWT_1_OVEW_W0  (1 <<  0)
#       define WADEON_VTX_Z_PWE_MUWT_1_OVEW_W0   (1 <<  1)
#       define WADEON_VTX_ST0_NONPAWAMETWIC      (1 <<  8)
#       define WADEON_VTX_ST1_NONPAWAMETWIC      (1 <<  9)
#       define WADEON_VTX_ST2_NONPAWAMETWIC      (1 << 10)
#       define WADEON_VTX_ST3_NONPAWAMETWIC      (1 << 11)
#       define WADEON_VTX_W0_NOWMAWIZE           (1 << 12)
#       define WADEON_VTX_W0_IS_NOT_1_OVEW_W0    (1 << 16)
#       define WADEON_VTX_ST0_PWE_MUWT_1_OVEW_W0 (1 << 17)
#       define WADEON_VTX_ST1_PWE_MUWT_1_OVEW_W0 (1 << 19)
#       define WADEON_VTX_ST2_PWE_MUWT_1_OVEW_W0 (1 << 21)
#       define WADEON_VTX_ST3_PWE_MUWT_1_OVEW_W0 (1 << 23)
#       define WADEON_TEX1_W_WOUTING_USE_W0      (0 << 26)
#       define WADEON_TEX1_W_WOUTING_USE_Q1      (1 << 26)
#define WADEON_SE_WINE_WIDTH                0x1db8
#define WADEON_SE_TCW_WIGHT_MODEW_CTW       0x226c
#       define WADEON_WIGHTING_ENABWE              (1 << 0)
#       define WADEON_WIGHT_IN_MODEWSPACE          (1 << 1)
#       define WADEON_WOCAW_VIEWEW                 (1 << 2)
#       define WADEON_NOWMAWIZE_NOWMAWS            (1 << 3)
#       define WADEON_WESCAWE_NOWMAWS              (1 << 4)
#       define WADEON_SPECUWAW_WIGHTS              (1 << 5)
#       define WADEON_DIFFUSE_SPECUWAW_COMBINE     (1 << 6)
#       define WADEON_WIGHT_AWPHA                  (1 << 7)
#       define WADEON_WOCAW_WIGHT_VEC_GW           (1 << 8)
#       define WADEON_WIGHT_NO_NOWMAW_AMBIENT_ONWY (1 << 9)
#       define WADEON_WM_SOUWCE_STATE_PWEMUWT      0
#       define WADEON_WM_SOUWCE_STATE_MUWT         1
#       define WADEON_WM_SOUWCE_VEWTEX_DIFFUSE     2
#       define WADEON_WM_SOUWCE_VEWTEX_SPECUWAW    3
#       define WADEON_EMISSIVE_SOUWCE_SHIFT        16
#       define WADEON_AMBIENT_SOUWCE_SHIFT         18
#       define WADEON_DIFFUSE_SOUWCE_SHIFT         20
#       define WADEON_SPECUWAW_SOUWCE_SHIFT        22
#define WADEON_SE_TCW_MATEWIAW_AMBIENT_WED     0x2220
#define WADEON_SE_TCW_MATEWIAW_AMBIENT_GWEEN   0x2224
#define WADEON_SE_TCW_MATEWIAW_AMBIENT_BWUE    0x2228
#define WADEON_SE_TCW_MATEWIAW_AMBIENT_AWPHA   0x222c
#define WADEON_SE_TCW_MATEWIAW_DIFFUSE_WED     0x2230
#define WADEON_SE_TCW_MATEWIAW_DIFFUSE_GWEEN   0x2234
#define WADEON_SE_TCW_MATEWIAW_DIFFUSE_BWUE    0x2238
#define WADEON_SE_TCW_MATEWIAW_DIFFUSE_AWPHA   0x223c
#define WADEON_SE_TCW_MATEWIAW_EMMISSIVE_WED   0x2210
#define WADEON_SE_TCW_MATEWIAW_EMMISSIVE_GWEEN 0x2214
#define WADEON_SE_TCW_MATEWIAW_EMMISSIVE_BWUE  0x2218
#define WADEON_SE_TCW_MATEWIAW_EMMISSIVE_AWPHA 0x221c
#define WADEON_SE_TCW_MATEWIAW_SPECUWAW_WED    0x2240
#define WADEON_SE_TCW_MATEWIAW_SPECUWAW_GWEEN  0x2244
#define WADEON_SE_TCW_MATEWIAW_SPECUWAW_BWUE   0x2248
#define WADEON_SE_TCW_MATEWIAW_SPECUWAW_AWPHA  0x224c
#define WADEON_SE_TCW_MATWIX_SEWECT_0       0x225c
#       define WADEON_MODEWVIEW_0_SHIFT        0
#       define WADEON_MODEWVIEW_1_SHIFT        4
#       define WADEON_MODEWVIEW_2_SHIFT        8
#       define WADEON_MODEWVIEW_3_SHIFT        12
#       define WADEON_IT_MODEWVIEW_0_SHIFT     16
#       define WADEON_IT_MODEWVIEW_1_SHIFT     20
#       define WADEON_IT_MODEWVIEW_2_SHIFT     24
#       define WADEON_IT_MODEWVIEW_3_SHIFT     28
#define WADEON_SE_TCW_MATWIX_SEWECT_1       0x2260
#       define WADEON_MODEWPWOJECT_0_SHIFT     0
#       define WADEON_MODEWPWOJECT_1_SHIFT     4
#       define WADEON_MODEWPWOJECT_2_SHIFT     8
#       define WADEON_MODEWPWOJECT_3_SHIFT     12
#       define WADEON_TEXMAT_0_SHIFT           16
#       define WADEON_TEXMAT_1_SHIFT           20
#       define WADEON_TEXMAT_2_SHIFT           24
#       define WADEON_TEXMAT_3_SHIFT           28


#define WADEON_SE_TCW_OUTPUT_VTX_FMT        0x2254
#       define WADEON_TCW_VTX_W0                 (1 <<  0)
#       define WADEON_TCW_VTX_FP_DIFFUSE         (1 <<  1)
#       define WADEON_TCW_VTX_FP_AWPHA           (1 <<  2)
#       define WADEON_TCW_VTX_PK_DIFFUSE         (1 <<  3)
#       define WADEON_TCW_VTX_FP_SPEC            (1 <<  4)
#       define WADEON_TCW_VTX_FP_FOG             (1 <<  5)
#       define WADEON_TCW_VTX_PK_SPEC            (1 <<  6)
#       define WADEON_TCW_VTX_ST0                (1 <<  7)
#       define WADEON_TCW_VTX_ST1                (1 <<  8)
#       define WADEON_TCW_VTX_Q1                 (1 <<  9)
#       define WADEON_TCW_VTX_ST2                (1 << 10)
#       define WADEON_TCW_VTX_Q2                 (1 << 11)
#       define WADEON_TCW_VTX_ST3                (1 << 12)
#       define WADEON_TCW_VTX_Q3                 (1 << 13)
#       define WADEON_TCW_VTX_Q0                 (1 << 14)
#       define WADEON_TCW_VTX_WEIGHT_COUNT_SHIFT 15
#       define WADEON_TCW_VTX_NOWM0              (1 << 18)
#       define WADEON_TCW_VTX_XY1                (1 << 27)
#       define WADEON_TCW_VTX_Z1                 (1 << 28)
#       define WADEON_TCW_VTX_W1                 (1 << 29)
#       define WADEON_TCW_VTX_NOWM1              (1 << 30)
#       define WADEON_TCW_VTX_Z0                 (1 << 31)

#define WADEON_SE_TCW_OUTPUT_VTX_SEW        0x2258
#       define WADEON_TCW_COMPUTE_XYZW           (1 << 0)
#       define WADEON_TCW_COMPUTE_DIFFUSE        (1 << 1)
#       define WADEON_TCW_COMPUTE_SPECUWAW       (1 << 2)
#       define WADEON_TCW_FOWCE_NAN_IF_COWOW_NAN (1 << 3)
#       define WADEON_TCW_FOWCE_INOWDEW_PWOC     (1 << 4)
#       define WADEON_TCW_TEX_INPUT_TEX_0        0
#       define WADEON_TCW_TEX_INPUT_TEX_1        1
#       define WADEON_TCW_TEX_INPUT_TEX_2        2
#       define WADEON_TCW_TEX_INPUT_TEX_3        3
#       define WADEON_TCW_TEX_COMPUTED_TEX_0     8
#       define WADEON_TCW_TEX_COMPUTED_TEX_1     9
#       define WADEON_TCW_TEX_COMPUTED_TEX_2     10
#       define WADEON_TCW_TEX_COMPUTED_TEX_3     11
#       define WADEON_TCW_TEX_0_OUTPUT_SHIFT     16
#       define WADEON_TCW_TEX_1_OUTPUT_SHIFT     20
#       define WADEON_TCW_TEX_2_OUTPUT_SHIFT     24
#       define WADEON_TCW_TEX_3_OUTPUT_SHIFT     28

#define WADEON_SE_TCW_PEW_WIGHT_CTW_0       0x2270
#       define WADEON_WIGHT_0_ENABWE               (1 <<  0)
#       define WADEON_WIGHT_0_ENABWE_AMBIENT       (1 <<  1)
#       define WADEON_WIGHT_0_ENABWE_SPECUWAW      (1 <<  2)
#       define WADEON_WIGHT_0_IS_WOCAW             (1 <<  3)
#       define WADEON_WIGHT_0_IS_SPOT              (1 <<  4)
#       define WADEON_WIGHT_0_DUAW_CONE            (1 <<  5)
#       define WADEON_WIGHT_0_ENABWE_WANGE_ATTEN   (1 <<  6)
#       define WADEON_WIGHT_0_CONSTANT_WANGE_ATTEN (1 <<  7)
#       define WADEON_WIGHT_0_SHIFT                0
#       define WADEON_WIGHT_1_ENABWE               (1 << 16)
#       define WADEON_WIGHT_1_ENABWE_AMBIENT       (1 << 17)
#       define WADEON_WIGHT_1_ENABWE_SPECUWAW      (1 << 18)
#       define WADEON_WIGHT_1_IS_WOCAW             (1 << 19)
#       define WADEON_WIGHT_1_IS_SPOT              (1 << 20)
#       define WADEON_WIGHT_1_DUAW_CONE            (1 << 21)
#       define WADEON_WIGHT_1_ENABWE_WANGE_ATTEN   (1 << 22)
#       define WADEON_WIGHT_1_CONSTANT_WANGE_ATTEN (1 << 23)
#       define WADEON_WIGHT_1_SHIFT                16
#define WADEON_SE_TCW_PEW_WIGHT_CTW_1       0x2274
#       define WADEON_WIGHT_2_SHIFT            0
#       define WADEON_WIGHT_3_SHIFT            16
#define WADEON_SE_TCW_PEW_WIGHT_CTW_2       0x2278
#       define WADEON_WIGHT_4_SHIFT            0
#       define WADEON_WIGHT_5_SHIFT            16
#define WADEON_SE_TCW_PEW_WIGHT_CTW_3       0x227c
#       define WADEON_WIGHT_6_SHIFT            0
#       define WADEON_WIGHT_7_SHIFT            16

#define WADEON_SE_TCW_SHININESS             0x2250

#define WADEON_SE_TCW_TEXTUWE_PWOC_CTW      0x2268
#       define WADEON_TEXGEN_TEXMAT_0_ENABWE      (1 << 0)
#       define WADEON_TEXGEN_TEXMAT_1_ENABWE      (1 << 1)
#       define WADEON_TEXGEN_TEXMAT_2_ENABWE      (1 << 2)
#       define WADEON_TEXGEN_TEXMAT_3_ENABWE      (1 << 3)
#       define WADEON_TEXMAT_0_ENABWE             (1 << 4)
#       define WADEON_TEXMAT_1_ENABWE             (1 << 5)
#       define WADEON_TEXMAT_2_ENABWE             (1 << 6)
#       define WADEON_TEXMAT_3_ENABWE             (1 << 7)
#       define WADEON_TEXGEN_INPUT_MASK           0xf
#       define WADEON_TEXGEN_INPUT_TEXCOOWD_0     0
#       define WADEON_TEXGEN_INPUT_TEXCOOWD_1     1
#       define WADEON_TEXGEN_INPUT_TEXCOOWD_2     2
#       define WADEON_TEXGEN_INPUT_TEXCOOWD_3     3
#       define WADEON_TEXGEN_INPUT_OBJ            4
#       define WADEON_TEXGEN_INPUT_EYE            5
#       define WADEON_TEXGEN_INPUT_EYE_NOWMAW     6
#       define WADEON_TEXGEN_INPUT_EYE_WEFWECT    7
#       define WADEON_TEXGEN_INPUT_EYE_NOWMAWIZED 8
#       define WADEON_TEXGEN_0_INPUT_SHIFT        16
#       define WADEON_TEXGEN_1_INPUT_SHIFT        20
#       define WADEON_TEXGEN_2_INPUT_SHIFT        24
#       define WADEON_TEXGEN_3_INPUT_SHIFT        28

#define WADEON_SE_TCW_UCP_VEWT_BWEND_CTW    0x2264
#       define WADEON_UCP_IN_CWIP_SPACE            (1 <<  0)
#       define WADEON_UCP_IN_MODEW_SPACE           (1 <<  1)
#       define WADEON_UCP_ENABWE_0                 (1 <<  2)
#       define WADEON_UCP_ENABWE_1                 (1 <<  3)
#       define WADEON_UCP_ENABWE_2                 (1 <<  4)
#       define WADEON_UCP_ENABWE_3                 (1 <<  5)
#       define WADEON_UCP_ENABWE_4                 (1 <<  6)
#       define WADEON_UCP_ENABWE_5                 (1 <<  7)
#       define WADEON_TCW_FOG_MASK                 (3 <<  8)
#       define WADEON_TCW_FOG_DISABWE              (0 <<  8)
#       define WADEON_TCW_FOG_EXP                  (1 <<  8)
#       define WADEON_TCW_FOG_EXP2                 (2 <<  8)
#       define WADEON_TCW_FOG_WINEAW               (3 <<  8)
#       define WADEON_WNG_BASED_FOG                (1 << 10)
#       define WADEON_WIGHT_TWOSIDE                (1 << 11)
#       define WADEON_BWEND_OP_COUNT_MASK          (7 << 12)
#       define WADEON_BWEND_OP_COUNT_SHIFT         12
#       define WADEON_POSITION_BWEND_OP_ENABWE     (1 << 16)
#       define WADEON_NOWMAW_BWEND_OP_ENABWE       (1 << 17)
#       define WADEON_VEWTEX_BWEND_SWC_0_PWIMAWY   (1 << 18)
#       define WADEON_VEWTEX_BWEND_SWC_0_SECONDAWY (1 << 18)
#       define WADEON_VEWTEX_BWEND_SWC_1_PWIMAWY   (1 << 19)
#       define WADEON_VEWTEX_BWEND_SWC_1_SECONDAWY (1 << 19)
#       define WADEON_VEWTEX_BWEND_SWC_2_PWIMAWY   (1 << 20)
#       define WADEON_VEWTEX_BWEND_SWC_2_SECONDAWY (1 << 20)
#       define WADEON_VEWTEX_BWEND_SWC_3_PWIMAWY   (1 << 21)
#       define WADEON_VEWTEX_BWEND_SWC_3_SECONDAWY (1 << 21)
#       define WADEON_VEWTEX_BWEND_WGT_MINUS_ONE   (1 << 22)
#       define WADEON_CUWW_FWONT_IS_CW             (0 << 28)
#       define WADEON_CUWW_FWONT_IS_CCW            (1 << 28)
#       define WADEON_CUWW_FWONT                   (1 << 29)
#       define WADEON_CUWW_BACK                    (1 << 30)
#       define WADEON_FOWCE_W_TO_ONE               (1 << 31)

#define WADEON_SE_VPOWT_XSCAWE              0x1d98
#define WADEON_SE_VPOWT_XOFFSET             0x1d9c
#define WADEON_SE_VPOWT_YSCAWE              0x1da0
#define WADEON_SE_VPOWT_YOFFSET             0x1da4
#define WADEON_SE_VPOWT_ZSCAWE              0x1da8
#define WADEON_SE_VPOWT_ZOFFSET             0x1dac
#define WADEON_SE_ZBIAS_FACTOW              0x1db0
#define WADEON_SE_ZBIAS_CONSTANT            0x1db4

#define WADEON_SE_VTX_FMT                   0x2080
#       define WADEON_SE_VTX_FMT_XY         0x00000000
#       define WADEON_SE_VTX_FMT_W0         0x00000001
#       define WADEON_SE_VTX_FMT_FPCOWOW    0x00000002
#       define WADEON_SE_VTX_FMT_FPAWPHA    0x00000004
#       define WADEON_SE_VTX_FMT_PKCOWOW    0x00000008
#       define WADEON_SE_VTX_FMT_FPSPEC     0x00000010
#       define WADEON_SE_VTX_FMT_FPFOG      0x00000020
#       define WADEON_SE_VTX_FMT_PKSPEC     0x00000040
#       define WADEON_SE_VTX_FMT_ST0        0x00000080
#       define WADEON_SE_VTX_FMT_ST1        0x00000100
#       define WADEON_SE_VTX_FMT_Q1         0x00000200
#       define WADEON_SE_VTX_FMT_ST2        0x00000400
#       define WADEON_SE_VTX_FMT_Q2         0x00000800
#       define WADEON_SE_VTX_FMT_ST3        0x00001000
#       define WADEON_SE_VTX_FMT_Q3         0x00002000
#       define WADEON_SE_VTX_FMT_Q0         0x00004000
#       define WADEON_SE_VTX_FMT_BWND_WEIGHT_CNT_MASK  0x00038000
#       define WADEON_SE_VTX_FMT_N0         0x00040000
#       define WADEON_SE_VTX_FMT_XY1        0x08000000
#       define WADEON_SE_VTX_FMT_Z1         0x10000000
#       define WADEON_SE_VTX_FMT_W1         0x20000000
#       define WADEON_SE_VTX_FMT_N1         0x40000000
#       define WADEON_SE_VTX_FMT_Z          0x80000000

#define WADEON_SE_VF_CNTW                             0x2084
#       define WADEON_VF_PWIM_TYPE_POINT_WIST         1
#       define WADEON_VF_PWIM_TYPE_WINE_WIST          2
#       define WADEON_VF_PWIM_TYPE_WINE_STWIP         3
#       define WADEON_VF_PWIM_TYPE_TWIANGWE_WIST      4
#       define WADEON_VF_PWIM_TYPE_TWIANGWE_FAN       5
#       define WADEON_VF_PWIM_TYPE_TWIANGWE_STWIP     6
#       define WADEON_VF_PWIM_TYPE_TWIANGWE_FWAG      7
#       define WADEON_VF_PWIM_TYPE_WECTANGWE_WIST     8
#       define WADEON_VF_PWIM_TYPE_POINT_WIST_3       9
#       define WADEON_VF_PWIM_TYPE_WINE_WIST_3        10
#       define WADEON_VF_PWIM_TYPE_SPIWIT_WIST        11
#       define WADEON_VF_PWIM_TYPE_WINE_WOOP          12
#       define WADEON_VF_PWIM_TYPE_QUAD_WIST          13
#       define WADEON_VF_PWIM_TYPE_QUAD_STWIP         14
#       define WADEON_VF_PWIM_TYPE_POWYGON            15
#       define WADEON_VF_PWIM_WAWK_STATE              (0<<4)
#       define WADEON_VF_PWIM_WAWK_INDEX              (1<<4)
#       define WADEON_VF_PWIM_WAWK_WIST               (2<<4)
#       define WADEON_VF_PWIM_WAWK_DATA               (3<<4)
#       define WADEON_VF_COWOW_OWDEW_WGBA             (1<<6)
#       define WADEON_VF_WADEON_MODE                  (1<<8)
#       define WADEON_VF_TCW_OUTPUT_CTW_ENA           (1<<9)
#       define WADEON_VF_PWOG_STWEAM_ENA              (1<<10)
#       define WADEON_VF_INDEX_SIZE_SHIFT             11
#       define WADEON_VF_NUM_VEWTICES_SHIFT           16

#define WADEON_SE_POWT_DATA0			0x2000

#define W200_SE_VAP_CNTW			0x2080
#       define W200_VAP_TCW_ENABWE		0x00000001
#       define W200_VAP_SINGWE_BUF_STATE_ENABWE	0x00000010
#       define W200_VAP_FOWCE_W_TO_ONE		0x00010000
#       define W200_VAP_D3D_TEX_DEFAUWT		0x00020000
#       define W200_VAP_VF_MAX_VTX_NUM__SHIFT	18
#       define W200_VAP_VF_MAX_VTX_NUM		(9 << 18)
#       define W200_VAP_DX_CWIP_SPACE_DEF	0x00400000
#define W200_VF_MAX_VTX_INDX			0x210c
#define W200_VF_MIN_VTX_INDX			0x2110
#define W200_SE_VTE_CNTW			0x20b0
#       define W200_VPOWT_X_SCAWE_ENA			0x00000001
#       define W200_VPOWT_X_OFFSET_ENA			0x00000002
#       define W200_VPOWT_Y_SCAWE_ENA			0x00000004
#       define W200_VPOWT_Y_OFFSET_ENA			0x00000008
#       define W200_VPOWT_Z_SCAWE_ENA			0x00000010
#       define W200_VPOWT_Z_OFFSET_ENA			0x00000020
#       define W200_VTX_XY_FMT				0x00000100
#       define W200_VTX_Z_FMT				0x00000200
#       define W200_VTX_W0_FMT				0x00000400
#       define W200_VTX_W0_NOWMAWIZE			0x00000800
#       define W200_VTX_ST_DENOWMAWIZED		0x00001000
#define W200_SE_VAP_CNTW_STATUS			0x2140
#       define W200_VC_NO_SWAP			(0 << 0)
#       define W200_VC_16BIT_SWAP		(1 << 0)
#       define W200_VC_32BIT_SWAP		(2 << 0)
#define W200_PP_TXFIWTEW_0			0x2c00
#define W200_PP_TXFIWTEW_1			0x2c20
#define W200_PP_TXFIWTEW_2			0x2c40
#define W200_PP_TXFIWTEW_3			0x2c60
#define W200_PP_TXFIWTEW_4			0x2c80
#define W200_PP_TXFIWTEW_5			0x2ca0
#       define W200_MAG_FIWTEW_NEAWEST		(0  <<  0)
#       define W200_MAG_FIWTEW_WINEAW		(1  <<  0)
#       define W200_MAG_FIWTEW_MASK		(1  <<  0)
#       define W200_MIN_FIWTEW_NEAWEST		(0  <<  1)
#       define W200_MIN_FIWTEW_WINEAW		(1  <<  1)
#       define W200_MIN_FIWTEW_NEAWEST_MIP_NEAWEST (2  <<  1)
#       define W200_MIN_FIWTEW_NEAWEST_MIP_WINEAW (3  <<  1)
#       define W200_MIN_FIWTEW_WINEAW_MIP_NEAWEST (6  <<  1)
#       define W200_MIN_FIWTEW_WINEAW_MIP_WINEAW (7  <<  1)
#       define W200_MIN_FIWTEW_ANISO_NEAWEST	(8  <<  1)
#       define W200_MIN_FIWTEW_ANISO_WINEAW	(9  <<  1)
#       define W200_MIN_FIWTEW_ANISO_NEAWEST_MIP_NEAWEST (10 <<  1)
#       define W200_MIN_FIWTEW_ANISO_NEAWEST_MIP_WINEAW (11 <<  1)
#       define W200_MIN_FIWTEW_MASK		(15 <<  1)
#       define W200_MAX_ANISO_1_TO_1		(0  <<  5)
#       define W200_MAX_ANISO_2_TO_1		(1  <<  5)
#       define W200_MAX_ANISO_4_TO_1		(2  <<  5)
#       define W200_MAX_ANISO_8_TO_1		(3  <<  5)
#       define W200_MAX_ANISO_16_TO_1		(4  <<  5)
#       define W200_MAX_ANISO_MASK		(7  <<  5)
#       define W200_MAX_MIP_WEVEW_MASK		(0x0f << 16)
#       define W200_MAX_MIP_WEVEW_SHIFT		16
#       define W200_YUV_TO_WGB			(1  << 20)
#       define W200_YUV_TEMPEWATUWE_COOW	(0  << 21)
#       define W200_YUV_TEMPEWATUWE_HOT		(1  << 21)
#       define W200_YUV_TEMPEWATUWE_MASK	(1  << 21)
#       define W200_WWAPEN_S			(1  << 22)
#       define W200_CWAMP_S_WWAP		(0  << 23)
#       define W200_CWAMP_S_MIWWOW		(1  << 23)
#       define W200_CWAMP_S_CWAMP_WAST		(2  << 23)
#       define W200_CWAMP_S_MIWWOW_CWAMP_WAST	(3  << 23)
#       define W200_CWAMP_S_CWAMP_BOWDEW	(4  << 23)
#       define W200_CWAMP_S_MIWWOW_CWAMP_BOWDEW	(5  << 23)
#       define W200_CWAMP_S_CWAMP_GW		(6  << 23)
#       define W200_CWAMP_S_MIWWOW_CWAMP_GW	(7  << 23)
#       define W200_CWAMP_S_MASK		(7  << 23)
#       define W200_WWAPEN_T			(1  << 26)
#       define W200_CWAMP_T_WWAP		(0  << 27)
#       define W200_CWAMP_T_MIWWOW		(1  << 27)
#       define W200_CWAMP_T_CWAMP_WAST		(2  << 27)
#       define W200_CWAMP_T_MIWWOW_CWAMP_WAST	(3  << 27)
#       define W200_CWAMP_T_CWAMP_BOWDEW	(4  << 27)
#       define W200_CWAMP_T_MIWWOW_CWAMP_BOWDEW	(5  << 27)
#       define W200_CWAMP_T_CWAMP_GW		(6  << 27)
#       define W200_CWAMP_T_MIWWOW_CWAMP_GW	(7  << 27)
#       define W200_CWAMP_T_MASK		(7  << 27)
#       define W200_KIWW_WT_ZEWO		(1  << 30)
#       define W200_BOWDEW_MODE_OGW		(0  << 31)
#       define W200_BOWDEW_MODE_D3D		(1  << 31)
#define W200_PP_TXFOWMAT_0			0x2c04
#define W200_PP_TXFOWMAT_1			0x2c24
#define W200_PP_TXFOWMAT_2			0x2c44
#define W200_PP_TXFOWMAT_3			0x2c64
#define W200_PP_TXFOWMAT_4			0x2c84
#define W200_PP_TXFOWMAT_5			0x2ca4
#       define W200_TXFOWMAT_I8			(0 << 0)
#       define W200_TXFOWMAT_AI88		(1 << 0)
#       define W200_TXFOWMAT_WGB332		(2 << 0)
#       define W200_TXFOWMAT_AWGB1555		(3 << 0)
#       define W200_TXFOWMAT_WGB565		(4 << 0)
#       define W200_TXFOWMAT_AWGB4444		(5 << 0)
#       define W200_TXFOWMAT_AWGB8888		(6 << 0)
#       define W200_TXFOWMAT_WGBA8888		(7 << 0)
#       define W200_TXFOWMAT_Y8			(8 << 0)
#       define W200_TXFOWMAT_AVYU4444		(9 << 0)
#       define W200_TXFOWMAT_VYUY422		(10 << 0)
#       define W200_TXFOWMAT_YVYU422		(11 << 0)
#       define W200_TXFOWMAT_DXT1		(12 << 0)
#       define W200_TXFOWMAT_DXT23		(14 << 0)
#       define W200_TXFOWMAT_DXT45		(15 << 0)
#       define W200_TXFOWMAT_DVDU88		(18 << 0)
#       define W200_TXFOWMAT_WDVDU655		(19 << 0)
#       define W200_TXFOWMAT_WDVDU8888		(20 << 0)
#       define W200_TXFOWMAT_GW1616		(21 << 0)
#       define W200_TXFOWMAT_ABGW8888		(22 << 0)
#       define W200_TXFOWMAT_BGW111110		(23 << 0)
#       define W200_TXFOWMAT_FOWMAT_MASK	(31 <<	0)
#       define W200_TXFOWMAT_FOWMAT_SHIFT	0
#       define W200_TXFOWMAT_AWPHA_IN_MAP	(1 << 6)
#       define W200_TXFOWMAT_NON_POWEW2		(1 << 7)
#       define W200_TXFOWMAT_WIDTH_MASK		(15 <<	8)
#       define W200_TXFOWMAT_WIDTH_SHIFT	8
#       define W200_TXFOWMAT_HEIGHT_MASK	(15 << 12)
#       define W200_TXFOWMAT_HEIGHT_SHIFT	12
#       define W200_TXFOWMAT_F5_WIDTH_MASK	(15 << 16)	/* cube face 5 */
#       define W200_TXFOWMAT_F5_WIDTH_SHIFT	16
#       define W200_TXFOWMAT_F5_HEIGHT_MASK	(15 << 20)
#       define W200_TXFOWMAT_F5_HEIGHT_SHIFT	20
#       define W200_TXFOWMAT_ST_WOUTE_STQ0	(0 << 24)
#       define W200_TXFOWMAT_ST_WOUTE_STQ1	(1 << 24)
#       define W200_TXFOWMAT_ST_WOUTE_STQ2	(2 << 24)
#       define W200_TXFOWMAT_ST_WOUTE_STQ3	(3 << 24)
#       define W200_TXFOWMAT_ST_WOUTE_STQ4	(4 << 24)
#       define W200_TXFOWMAT_ST_WOUTE_STQ5	(5 << 24)
#       define W200_TXFOWMAT_ST_WOUTE_MASK	(7 << 24)
#       define W200_TXFOWMAT_ST_WOUTE_SHIFT	24
#       define W200_TXFOWMAT_WOOKUP_DISABWE	(1 << 27)
#       define W200_TXFOWMAT_AWPHA_MASK_ENABWE	(1 << 28)
#       define W200_TXFOWMAT_CHWOMA_KEY_ENABWE	(1 << 29)
#       define W200_TXFOWMAT_CUBIC_MAP_ENABWE		(1 << 30)
#define W200_PP_TXFOWMAT_X_0                    0x2c08
#define W200_PP_TXFOWMAT_X_1                    0x2c28
#define W200_PP_TXFOWMAT_X_2                    0x2c48
#define W200_PP_TXFOWMAT_X_3                    0x2c68
#define W200_PP_TXFOWMAT_X_4                    0x2c88
#define W200_PP_TXFOWMAT_X_5                    0x2ca8

#define W200_PP_TXSIZE_0			0x2c0c /* NPOT onwy */
#define W200_PP_TXSIZE_1			0x2c2c /* NPOT onwy */
#define W200_PP_TXSIZE_2			0x2c4c /* NPOT onwy */
#define W200_PP_TXSIZE_3			0x2c6c /* NPOT onwy */
#define W200_PP_TXSIZE_4			0x2c8c /* NPOT onwy */
#define W200_PP_TXSIZE_5			0x2cac /* NPOT onwy */

#define W200_PP_TXPITCH_0                       0x2c10 /* NPOT onwy */
#define W200_PP_TXPITCH_1			0x2c30 /* NPOT onwy */
#define W200_PP_TXPITCH_2			0x2c50 /* NPOT onwy */
#define W200_PP_TXPITCH_3			0x2c70 /* NPOT onwy */
#define W200_PP_TXPITCH_4			0x2c90 /* NPOT onwy */
#define W200_PP_TXPITCH_5			0x2cb0 /* NPOT onwy */

#define W200_PP_CUBIC_FACES_0			0x2c18
#define W200_PP_CUBIC_FACES_1			0x2c38
#define W200_PP_CUBIC_FACES_2			0x2c58
#define W200_PP_CUBIC_FACES_3			0x2c78
#define W200_PP_CUBIC_FACES_4			0x2c98
#define W200_PP_CUBIC_FACES_5			0x2cb8

#define W200_PP_TXOFFSET_0			0x2d00
#       define W200_TXO_ENDIAN_NO_SWAP		(0 << 0)
#       define W200_TXO_ENDIAN_BYTE_SWAP	(1 << 0)
#       define W200_TXO_ENDIAN_WOWD_SWAP	(2 << 0)
#       define W200_TXO_ENDIAN_HAWFDW_SWAP	(3 << 0)
#       define W200_TXO_MACWO_WINEAW		(0 << 2)
#       define W200_TXO_MACWO_TIWE		(1 << 2)
#       define W200_TXO_MICWO_WINEAW		(0 << 3)
#       define W200_TXO_MICWO_TIWE		(1 << 3)
#       define W200_TXO_OFFSET_MASK		0xffffffe0
#       define W200_TXO_OFFSET_SHIFT		5
#define W200_PP_CUBIC_OFFSET_F1_0         0x2d04
#define W200_PP_CUBIC_OFFSET_F2_0         0x2d08
#define W200_PP_CUBIC_OFFSET_F3_0         0x2d0c
#define W200_PP_CUBIC_OFFSET_F4_0         0x2d10
#define W200_PP_CUBIC_OFFSET_F5_0         0x2d14

#define W200_PP_TXOFFSET_1			0x2d18
#define W200_PP_CUBIC_OFFSET_F1_1         0x2d1c
#define W200_PP_CUBIC_OFFSET_F2_1         0x2d20
#define W200_PP_CUBIC_OFFSET_F3_1         0x2d24
#define W200_PP_CUBIC_OFFSET_F4_1         0x2d28
#define W200_PP_CUBIC_OFFSET_F5_1         0x2d2c

#define W200_PP_TXOFFSET_2			0x2d30
#define W200_PP_CUBIC_OFFSET_F1_2         0x2d34
#define W200_PP_CUBIC_OFFSET_F2_2         0x2d38
#define W200_PP_CUBIC_OFFSET_F3_2         0x2d3c
#define W200_PP_CUBIC_OFFSET_F4_2         0x2d40
#define W200_PP_CUBIC_OFFSET_F5_2         0x2d44

#define W200_PP_TXOFFSET_3			0x2d48
#define W200_PP_CUBIC_OFFSET_F1_3         0x2d4c
#define W200_PP_CUBIC_OFFSET_F2_3         0x2d50
#define W200_PP_CUBIC_OFFSET_F3_3         0x2d54
#define W200_PP_CUBIC_OFFSET_F4_3         0x2d58
#define W200_PP_CUBIC_OFFSET_F5_3         0x2d5c
#define W200_PP_TXOFFSET_4			0x2d60
#define W200_PP_CUBIC_OFFSET_F1_4         0x2d64
#define W200_PP_CUBIC_OFFSET_F2_4         0x2d68
#define W200_PP_CUBIC_OFFSET_F3_4         0x2d6c
#define W200_PP_CUBIC_OFFSET_F4_4         0x2d70
#define W200_PP_CUBIC_OFFSET_F5_4         0x2d74
#define W200_PP_TXOFFSET_5			0x2d78
#define W200_PP_CUBIC_OFFSET_F1_5         0x2d7c
#define W200_PP_CUBIC_OFFSET_F2_5         0x2d80
#define W200_PP_CUBIC_OFFSET_F3_5         0x2d84
#define W200_PP_CUBIC_OFFSET_F4_5         0x2d88
#define W200_PP_CUBIC_OFFSET_F5_5         0x2d8c

#define W200_PP_TFACTOW_0			0x2ee0
#define W200_PP_TFACTOW_1			0x2ee4
#define W200_PP_TFACTOW_2			0x2ee8
#define W200_PP_TFACTOW_3			0x2eec
#define W200_PP_TFACTOW_4			0x2ef0
#define W200_PP_TFACTOW_5			0x2ef4

#define W200_PP_TXCBWEND_0			0x2f00
#       define W200_TXC_AWG_A_ZEWO		(0)
#       define W200_TXC_AWG_A_CUWWENT_COWOW	(2)
#       define W200_TXC_AWG_A_CUWWENT_AWPHA	(3)
#       define W200_TXC_AWG_A_DIFFUSE_COWOW	(4)
#       define W200_TXC_AWG_A_DIFFUSE_AWPHA	(5)
#       define W200_TXC_AWG_A_SPECUWAW_COWOW	(6)
#       define W200_TXC_AWG_A_SPECUWAW_AWPHA	(7)
#       define W200_TXC_AWG_A_TFACTOW_COWOW	(8)
#       define W200_TXC_AWG_A_TFACTOW_AWPHA	(9)
#       define W200_TXC_AWG_A_W0_COWOW		(10)
#       define W200_TXC_AWG_A_W0_AWPHA		(11)
#       define W200_TXC_AWG_A_W1_COWOW		(12)
#       define W200_TXC_AWG_A_W1_AWPHA		(13)
#       define W200_TXC_AWG_A_W2_COWOW		(14)
#       define W200_TXC_AWG_A_W2_AWPHA		(15)
#       define W200_TXC_AWG_A_W3_COWOW		(16)
#       define W200_TXC_AWG_A_W3_AWPHA		(17)
#       define W200_TXC_AWG_A_W4_COWOW		(18)
#       define W200_TXC_AWG_A_W4_AWPHA		(19)
#       define W200_TXC_AWG_A_W5_COWOW		(20)
#       define W200_TXC_AWG_A_W5_AWPHA		(21)
#       define W200_TXC_AWG_A_TFACTOW1_COWOW	(26)
#       define W200_TXC_AWG_A_TFACTOW1_AWPHA	(27)
#       define W200_TXC_AWG_A_MASK		(31 << 0)
#       define W200_TXC_AWG_A_SHIFT		0
#       define W200_TXC_AWG_B_ZEWO		(0 << 5)
#       define W200_TXC_AWG_B_CUWWENT_COWOW	(2 << 5)
#       define W200_TXC_AWG_B_CUWWENT_AWPHA	(3 << 5)
#       define W200_TXC_AWG_B_DIFFUSE_COWOW	(4 << 5)
#       define W200_TXC_AWG_B_DIFFUSE_AWPHA	(5 << 5)
#       define W200_TXC_AWG_B_SPECUWAW_COWOW	(6 << 5)
#       define W200_TXC_AWG_B_SPECUWAW_AWPHA	(7 << 5)
#       define W200_TXC_AWG_B_TFACTOW_COWOW	(8 << 5)
#       define W200_TXC_AWG_B_TFACTOW_AWPHA	(9 << 5)
#       define W200_TXC_AWG_B_W0_COWOW		(10 << 5)
#       define W200_TXC_AWG_B_W0_AWPHA		(11 << 5)
#       define W200_TXC_AWG_B_W1_COWOW		(12 << 5)
#       define W200_TXC_AWG_B_W1_AWPHA		(13 << 5)
#       define W200_TXC_AWG_B_W2_COWOW		(14 << 5)
#       define W200_TXC_AWG_B_W2_AWPHA		(15 << 5)
#       define W200_TXC_AWG_B_W3_COWOW		(16 << 5)
#       define W200_TXC_AWG_B_W3_AWPHA		(17 << 5)
#       define W200_TXC_AWG_B_W4_COWOW		(18 << 5)
#       define W200_TXC_AWG_B_W4_AWPHA		(19 << 5)
#       define W200_TXC_AWG_B_W5_COWOW		(20 << 5)
#       define W200_TXC_AWG_B_W5_AWPHA		(21 << 5)
#       define W200_TXC_AWG_B_TFACTOW1_COWOW	(26 << 5)
#       define W200_TXC_AWG_B_TFACTOW1_AWPHA	(27 << 5)
#       define W200_TXC_AWG_B_MASK		(31 << 5)
#       define W200_TXC_AWG_B_SHIFT		5
#       define W200_TXC_AWG_C_ZEWO		(0 << 10)
#       define W200_TXC_AWG_C_CUWWENT_COWOW	(2 << 10)
#       define W200_TXC_AWG_C_CUWWENT_AWPHA	(3 << 10)
#       define W200_TXC_AWG_C_DIFFUSE_COWOW	(4 << 10)
#       define W200_TXC_AWG_C_DIFFUSE_AWPHA	(5 << 10)
#       define W200_TXC_AWG_C_SPECUWAW_COWOW	(6 << 10)
#       define W200_TXC_AWG_C_SPECUWAW_AWPHA	(7 << 10)
#       define W200_TXC_AWG_C_TFACTOW_COWOW	(8 << 10)
#       define W200_TXC_AWG_C_TFACTOW_AWPHA	(9 << 10)
#       define W200_TXC_AWG_C_W0_COWOW		(10 << 10)
#       define W200_TXC_AWG_C_W0_AWPHA		(11 << 10)
#       define W200_TXC_AWG_C_W1_COWOW		(12 << 10)
#       define W200_TXC_AWG_C_W1_AWPHA		(13 << 10)
#       define W200_TXC_AWG_C_W2_COWOW		(14 << 10)
#       define W200_TXC_AWG_C_W2_AWPHA		(15 << 10)
#       define W200_TXC_AWG_C_W3_COWOW		(16 << 10)
#       define W200_TXC_AWG_C_W3_AWPHA		(17 << 10)
#       define W200_TXC_AWG_C_W4_COWOW		(18 << 10)
#       define W200_TXC_AWG_C_W4_AWPHA		(19 << 10)
#       define W200_TXC_AWG_C_W5_COWOW		(20 << 10)
#       define W200_TXC_AWG_C_W5_AWPHA		(21 << 10)
#       define W200_TXC_AWG_C_TFACTOW1_COWOW	(26 << 10)
#       define W200_TXC_AWG_C_TFACTOW1_AWPHA	(27 << 10)
#       define W200_TXC_AWG_C_MASK		(31 << 10)
#       define W200_TXC_AWG_C_SHIFT		10
#       define W200_TXC_COMP_AWG_A		(1 << 16)
#       define W200_TXC_COMP_AWG_A_SHIFT	(16)
#       define W200_TXC_BIAS_AWG_A		(1 << 17)
#       define W200_TXC_SCAWE_AWG_A		(1 << 18)
#       define W200_TXC_NEG_AWG_A		(1 << 19)
#       define W200_TXC_COMP_AWG_B		(1 << 20)
#       define W200_TXC_COMP_AWG_B_SHIFT	(20)
#       define W200_TXC_BIAS_AWG_B		(1 << 21)
#       define W200_TXC_SCAWE_AWG_B		(1 << 22)
#       define W200_TXC_NEG_AWG_B		(1 << 23)
#       define W200_TXC_COMP_AWG_C		(1 << 24)
#       define W200_TXC_COMP_AWG_C_SHIFT	(24)
#       define W200_TXC_BIAS_AWG_C		(1 << 25)
#       define W200_TXC_SCAWE_AWG_C		(1 << 26)
#       define W200_TXC_NEG_AWG_C		(1 << 27)
#       define W200_TXC_OP_MADD			(0 << 28)
#       define W200_TXC_OP_CND0			(2 << 28)
#       define W200_TXC_OP_WEWP			(3 << 28)
#       define W200_TXC_OP_DOT3			(4 << 28)
#       define W200_TXC_OP_DOT4			(5 << 28)
#       define W200_TXC_OP_CONDITIONAW		(6 << 28)
#       define W200_TXC_OP_DOT2_ADD		(7 << 28)
#       define W200_TXC_OP_MASK			(7 << 28)
#define W200_PP_TXCBWEND2_0		0x2f04
#       define W200_TXC_TFACTOW_SEW_SHIFT	0
#       define W200_TXC_TFACTOW_SEW_MASK	0x7
#       define W200_TXC_TFACTOW1_SEW_SHIFT	4
#       define W200_TXC_TFACTOW1_SEW_MASK	(0x7 << 4)
#       define W200_TXC_SCAWE_SHIFT		8
#       define W200_TXC_SCAWE_MASK		(7 << 8)
#       define W200_TXC_SCAWE_1X		(0 << 8)
#       define W200_TXC_SCAWE_2X		(1 << 8)
#       define W200_TXC_SCAWE_4X		(2 << 8)
#       define W200_TXC_SCAWE_8X		(3 << 8)
#       define W200_TXC_SCAWE_INV2		(5 << 8)
#       define W200_TXC_SCAWE_INV4		(6 << 8)
#       define W200_TXC_SCAWE_INV8		(7 << 8)
#       define W200_TXC_CWAMP_SHIFT		12
#       define W200_TXC_CWAMP_MASK		(3 << 12)
#       define W200_TXC_CWAMP_WWAP		(0 << 12)
#       define W200_TXC_CWAMP_0_1		(1 << 12)
#       define W200_TXC_CWAMP_8_8		(2 << 12)
#       define W200_TXC_OUTPUT_WEG_MASK		(7 << 16)
#       define W200_TXC_OUTPUT_WEG_NONE		(0 << 16)
#       define W200_TXC_OUTPUT_WEG_W0		(1 << 16)
#       define W200_TXC_OUTPUT_WEG_W1		(2 << 16)
#       define W200_TXC_OUTPUT_WEG_W2		(3 << 16)
#       define W200_TXC_OUTPUT_WEG_W3		(4 << 16)
#       define W200_TXC_OUTPUT_WEG_W4		(5 << 16)
#       define W200_TXC_OUTPUT_WEG_W5		(6 << 16)
#       define W200_TXC_OUTPUT_MASK_MASK	(7 << 20)
#       define W200_TXC_OUTPUT_MASK_WGB		(0 << 20)
#       define W200_TXC_OUTPUT_MASK_WG		(1 << 20)
#       define W200_TXC_OUTPUT_MASK_WB		(2 << 20)
#       define W200_TXC_OUTPUT_MASK_W		(3 << 20)
#       define W200_TXC_OUTPUT_MASK_GB		(4 << 20)
#       define W200_TXC_OUTPUT_MASK_G		(5 << 20)
#       define W200_TXC_OUTPUT_MASK_B		(6 << 20)
#       define W200_TXC_OUTPUT_MASK_NONE	(7 << 20)
#       define W200_TXC_WEPW_NOWMAW		0
#       define W200_TXC_WEPW_WED		1
#       define W200_TXC_WEPW_GWEEN		2
#       define W200_TXC_WEPW_BWUE		3
#       define W200_TXC_WEPW_AWG_A_SHIFT	26
#       define W200_TXC_WEPW_AWG_A_MASK		(3 << 26)
#       define W200_TXC_WEPW_AWG_B_SHIFT	28
#       define W200_TXC_WEPW_AWG_B_MASK		(3 << 28)
#       define W200_TXC_WEPW_AWG_C_SHIFT	30
#       define W200_TXC_WEPW_AWG_C_MASK		(3 << 30)
#define W200_PP_TXABWEND_0			0x2f08
#       define W200_TXA_AWG_A_ZEWO		(0)
#       define W200_TXA_AWG_A_CUWWENT_AWPHA	(2) /* guess */
#       define W200_TXA_AWG_A_CUWWENT_BWUE	(3) /* guess */
#       define W200_TXA_AWG_A_DIFFUSE_AWPHA	(4)
#       define W200_TXA_AWG_A_DIFFUSE_BWUE	(5)
#       define W200_TXA_AWG_A_SPECUWAW_AWPHA	(6)
#       define W200_TXA_AWG_A_SPECUWAW_BWUE	(7)
#       define W200_TXA_AWG_A_TFACTOW_AWPHA	(8)
#       define W200_TXA_AWG_A_TFACTOW_BWUE	(9)
#       define W200_TXA_AWG_A_W0_AWPHA		(10)
#       define W200_TXA_AWG_A_W0_BWUE		(11)
#       define W200_TXA_AWG_A_W1_AWPHA		(12)
#       define W200_TXA_AWG_A_W1_BWUE		(13)
#       define W200_TXA_AWG_A_W2_AWPHA		(14)
#       define W200_TXA_AWG_A_W2_BWUE		(15)
#       define W200_TXA_AWG_A_W3_AWPHA		(16)
#       define W200_TXA_AWG_A_W3_BWUE		(17)
#       define W200_TXA_AWG_A_W4_AWPHA		(18)
#       define W200_TXA_AWG_A_W4_BWUE		(19)
#       define W200_TXA_AWG_A_W5_AWPHA		(20)
#       define W200_TXA_AWG_A_W5_BWUE		(21)
#       define W200_TXA_AWG_A_TFACTOW1_AWPHA	(26)
#       define W200_TXA_AWG_A_TFACTOW1_BWUE	(27)
#       define W200_TXA_AWG_A_MASK		(31 << 0)
#       define W200_TXA_AWG_A_SHIFT		0
#       define W200_TXA_AWG_B_ZEWO		(0 << 5)
#       define W200_TXA_AWG_B_CUWWENT_AWPHA	(2 << 5) /* guess */
#       define W200_TXA_AWG_B_CUWWENT_BWUE	(3 << 5) /* guess */
#       define W200_TXA_AWG_B_DIFFUSE_AWPHA	(4 << 5)
#       define W200_TXA_AWG_B_DIFFUSE_BWUE	(5 << 5)
#       define W200_TXA_AWG_B_SPECUWAW_AWPHA	(6 << 5)
#       define W200_TXA_AWG_B_SPECUWAW_BWUE	(7 << 5)
#       define W200_TXA_AWG_B_TFACTOW_AWPHA	(8 << 5)
#       define W200_TXA_AWG_B_TFACTOW_BWUE	(9 << 5)
#       define W200_TXA_AWG_B_W0_AWPHA		(10 << 5)
#       define W200_TXA_AWG_B_W0_BWUE		(11 << 5)
#       define W200_TXA_AWG_B_W1_AWPHA		(12 << 5)
#       define W200_TXA_AWG_B_W1_BWUE		(13 << 5)
#       define W200_TXA_AWG_B_W2_AWPHA		(14 << 5)
#       define W200_TXA_AWG_B_W2_BWUE		(15 << 5)
#       define W200_TXA_AWG_B_W3_AWPHA		(16 << 5)
#       define W200_TXA_AWG_B_W3_BWUE		(17 << 5)
#       define W200_TXA_AWG_B_W4_AWPHA		(18 << 5)
#       define W200_TXA_AWG_B_W4_BWUE		(19 << 5)
#       define W200_TXA_AWG_B_W5_AWPHA		(20 << 5)
#       define W200_TXA_AWG_B_W5_BWUE		(21 << 5)
#       define W200_TXA_AWG_B_TFACTOW1_AWPHA	(26 << 5)
#       define W200_TXA_AWG_B_TFACTOW1_BWUE	(27 << 5)
#       define W200_TXA_AWG_B_MASK		(31 << 5)
#       define W200_TXA_AWG_B_SHIFT			5
#       define W200_TXA_AWG_C_ZEWO		(0 << 10)
#       define W200_TXA_AWG_C_CUWWENT_AWPHA	(2 << 10) /* guess */
#       define W200_TXA_AWG_C_CUWWENT_BWUE	(3 << 10) /* guess */
#       define W200_TXA_AWG_C_DIFFUSE_AWPHA	(4 << 10)
#       define W200_TXA_AWG_C_DIFFUSE_BWUE	(5 << 10)
#       define W200_TXA_AWG_C_SPECUWAW_AWPHA	(6 << 10)
#       define W200_TXA_AWG_C_SPECUWAW_BWUE	(7 << 10)
#       define W200_TXA_AWG_C_TFACTOW_AWPHA	(8 << 10)
#       define W200_TXA_AWG_C_TFACTOW_BWUE	(9 << 10)
#       define W200_TXA_AWG_C_W0_AWPHA		(10 << 10)
#       define W200_TXA_AWG_C_W0_BWUE		(11 << 10)
#       define W200_TXA_AWG_C_W1_AWPHA		(12 << 10)
#       define W200_TXA_AWG_C_W1_BWUE		(13 << 10)
#       define W200_TXA_AWG_C_W2_AWPHA		(14 << 10)
#       define W200_TXA_AWG_C_W2_BWUE		(15 << 10)
#       define W200_TXA_AWG_C_W3_AWPHA		(16 << 10)
#       define W200_TXA_AWG_C_W3_BWUE		(17 << 10)
#       define W200_TXA_AWG_C_W4_AWPHA		(18 << 10)
#       define W200_TXA_AWG_C_W4_BWUE		(19 << 10)
#       define W200_TXA_AWG_C_W5_AWPHA		(20 << 10)
#       define W200_TXA_AWG_C_W5_BWUE		(21 << 10)
#       define W200_TXA_AWG_C_TFACTOW1_AWPHA	(26 << 10)
#       define W200_TXA_AWG_C_TFACTOW1_BWUE	(27 << 10)
#       define W200_TXA_AWG_C_MASK		(31 << 10)
#       define W200_TXA_AWG_C_SHIFT		10
#       define W200_TXA_COMP_AWG_A		(1 << 16)
#       define W200_TXA_COMP_AWG_A_SHIFT	(16)
#       define W200_TXA_BIAS_AWG_A		(1 << 17)
#       define W200_TXA_SCAWE_AWG_A		(1 << 18)
#       define W200_TXA_NEG_AWG_A		(1 << 19)
#       define W200_TXA_COMP_AWG_B		(1 << 20)
#       define W200_TXA_COMP_AWG_B_SHIFT	(20)
#       define W200_TXA_BIAS_AWG_B		(1 << 21)
#       define W200_TXA_SCAWE_AWG_B		(1 << 22)
#       define W200_TXA_NEG_AWG_B		(1 << 23)
#       define W200_TXA_COMP_AWG_C		(1 << 24)
#       define W200_TXA_COMP_AWG_C_SHIFT	(24)
#       define W200_TXA_BIAS_AWG_C		(1 << 25)
#       define W200_TXA_SCAWE_AWG_C		(1 << 26)
#       define W200_TXA_NEG_AWG_C		(1 << 27)
#       define W200_TXA_OP_MADD			(0 << 28)
#       define W200_TXA_OP_CND0			(2 << 28)
#       define W200_TXA_OP_WEWP			(3 << 28)
#       define W200_TXA_OP_CONDITIONAW		(6 << 28)
#       define W200_TXA_OP_MASK			(7 << 28)
#define W200_PP_TXABWEND2_0			0x2f0c
#       define W200_TXA_TFACTOW_SEW_SHIFT	0
#       define W200_TXA_TFACTOW_SEW_MASK	0x7
#       define W200_TXA_TFACTOW1_SEW_SHIFT	4
#       define W200_TXA_TFACTOW1_SEW_MASK	(0x7 << 4)
#       define W200_TXA_SCAWE_SHIFT		8
#       define W200_TXA_SCAWE_MASK		(7 << 8)
#       define W200_TXA_SCAWE_1X		(0 << 8)
#       define W200_TXA_SCAWE_2X		(1 << 8)
#       define W200_TXA_SCAWE_4X		(2 << 8)
#       define W200_TXA_SCAWE_8X		(3 << 8)
#       define W200_TXA_SCAWE_INV2		(5 << 8)
#       define W200_TXA_SCAWE_INV4		(6 << 8)
#       define W200_TXA_SCAWE_INV8		(7 << 8)
#       define W200_TXA_CWAMP_SHIFT		12
#       define W200_TXA_CWAMP_MASK		(3 << 12)
#       define W200_TXA_CWAMP_WWAP		(0 << 12)
#       define W200_TXA_CWAMP_0_1		(1 << 12)
#       define W200_TXA_CWAMP_8_8		(2 << 12)
#       define W200_TXA_OUTPUT_WEG_MASK		(7 << 16)
#       define W200_TXA_OUTPUT_WEG_NONE		(0 << 16)
#       define W200_TXA_OUTPUT_WEG_W0		(1 << 16)
#       define W200_TXA_OUTPUT_WEG_W1		(2 << 16)
#       define W200_TXA_OUTPUT_WEG_W2		(3 << 16)
#       define W200_TXA_OUTPUT_WEG_W3		(4 << 16)
#       define W200_TXA_OUTPUT_WEG_W4		(5 << 16)
#       define W200_TXA_OUTPUT_WEG_W5		(6 << 16)
#       define W200_TXA_DOT_AWPHA		(1 << 20)
#       define W200_TXA_WEPW_NOWMAW		0
#       define W200_TXA_WEPW_WED		1
#       define W200_TXA_WEPW_GWEEN		2
#       define W200_TXA_WEPW_AWG_A_SHIFT	26
#       define W200_TXA_WEPW_AWG_A_MASK		(3 << 26)
#       define W200_TXA_WEPW_AWG_B_SHIFT	28
#       define W200_TXA_WEPW_AWG_B_MASK		(3 << 28)
#       define W200_TXA_WEPW_AWG_C_SHIFT	30
#       define W200_TXA_WEPW_AWG_C_MASK		(3 << 30)

#define W200_SE_VTX_FMT_0			0x2088
#       define W200_VTX_XY			0 /* awways have xy */
#       define W200_VTX_Z0			(1<<0)
#       define W200_VTX_W0			(1<<1)
#       define W200_VTX_WEIGHT_COUNT_SHIFT	(2)
#       define W200_VTX_PV_MATWIX_SEW		(1<<5)
#       define W200_VTX_N0			(1<<6)
#       define W200_VTX_POINT_SIZE		(1<<7)
#       define W200_VTX_DISCWETE_FOG		(1<<8)
#       define W200_VTX_SHININESS_0		(1<<9)
#       define W200_VTX_SHININESS_1		(1<<10)
#       define   W200_VTX_COWOW_NOT_PWESENT	0
#       define   W200_VTX_PK_WGBA		1
#       define   W200_VTX_FP_WGB		2
#       define   W200_VTX_FP_WGBA		3
#       define   W200_VTX_COWOW_MASK		3
#       define W200_VTX_COWOW_0_SHIFT		11
#       define W200_VTX_COWOW_1_SHIFT		13
#       define W200_VTX_COWOW_2_SHIFT		15
#       define W200_VTX_COWOW_3_SHIFT		17
#       define W200_VTX_COWOW_4_SHIFT		19
#       define W200_VTX_COWOW_5_SHIFT		21
#       define W200_VTX_COWOW_6_SHIFT		23
#       define W200_VTX_COWOW_7_SHIFT		25
#       define W200_VTX_XY1			(1<<28)
#       define W200_VTX_Z1			(1<<29)
#       define W200_VTX_W1			(1<<30)
#       define W200_VTX_N1			(1<<31)
#define W200_SE_VTX_FMT_1			0x208c
#       define W200_VTX_TEX0_COMP_CNT_SHIFT	0
#       define W200_VTX_TEX1_COMP_CNT_SHIFT	3
#       define W200_VTX_TEX2_COMP_CNT_SHIFT	6
#       define W200_VTX_TEX3_COMP_CNT_SHIFT	9
#       define W200_VTX_TEX4_COMP_CNT_SHIFT	12
#       define W200_VTX_TEX5_COMP_CNT_SHIFT	15

#define W200_SE_TCW_OUTPUT_VTX_FMT_0		0x2090
#define W200_SE_TCW_OUTPUT_VTX_FMT_1		0x2094
#define W200_SE_TCW_OUTPUT_VTX_COMP_SEW		0x2250
#       define W200_OUTPUT_XYZW			(1<<0)
#       define W200_OUTPUT_COWOW_0		(1<<8)
#       define W200_OUTPUT_COWOW_1		(1<<9)
#       define W200_OUTPUT_TEX_0		(1<<16)
#       define W200_OUTPUT_TEX_1		(1<<17)
#       define W200_OUTPUT_TEX_2		(1<<18)
#       define W200_OUTPUT_TEX_3		(1<<19)
#       define W200_OUTPUT_TEX_4		(1<<20)
#       define W200_OUTPUT_TEX_5		(1<<21)
#       define W200_OUTPUT_TEX_MASK		(0x3f<<16)
#       define W200_OUTPUT_DISCWETE_FOG		(1<<24)
#       define W200_OUTPUT_PT_SIZE		(1<<25)
#       define W200_FOWCE_INOWDEW_PWOC		(1<<31)
#define W200_PP_CNTW_X				0x2cc4
#define W200_PP_TXMUWTI_CTW_0			0x2c1c
#define W200_PP_TXMUWTI_CTW_1			0x2c3c
#define W200_PP_TXMUWTI_CTW_2			0x2c5c
#define W200_PP_TXMUWTI_CTW_3			0x2c7c
#define W200_PP_TXMUWTI_CTW_4			0x2c9c
#define W200_PP_TXMUWTI_CTW_5			0x2cbc
#define W200_SE_VTX_STATE_CNTW			0x2180
#       define W200_UPDATE_USEW_COWOW_0_ENA_MASK (1<<16)

				/* Wegistews fow CP and Micwocode Engine */
#define WADEON_CP_ME_WAM_ADDW               0x07d4
#define WADEON_CP_ME_WAM_WADDW              0x07d8
#define WADEON_CP_ME_WAM_DATAH              0x07dc
#define WADEON_CP_ME_WAM_DATAW              0x07e0

#define WADEON_CP_WB_BASE                   0x0700
#define WADEON_CP_WB_CNTW                   0x0704
#	define WADEON_WB_BUFSZ_SHIFT		0
#	define WADEON_WB_BUFSZ_MASK		(0x3f << 0)
#	define WADEON_WB_BWKSZ_SHIFT		8
#	define WADEON_WB_BWKSZ_MASK		(0x3f << 8)
#	define WADEON_BUF_SWAP_32BIT		(2 << 16)
#	define WADEON_MAX_FETCH_SHIFT		18
#	define WADEON_MAX_FETCH_MASK		(0x3 << 18)
#	define WADEON_WB_NO_UPDATE		(1 << 27)
#	define WADEON_WB_WPTW_WW_ENA		(1 << 31)
#define WADEON_CP_WB_WPTW_ADDW              0x070c
#define WADEON_CP_WB_WPTW                   0x0710
#define WADEON_CP_WB_WPTW                   0x0714
#define WADEON_CP_WB_WPTW_WW                0x071c

#define WADEON_SCWATCH_UMSK		    0x0770
#define WADEON_SCWATCH_ADDW		    0x0774

#define W600_CP_WB_BASE                     0xc100
#define W600_CP_WB_CNTW                     0xc104
#       define W600_WB_BUFSZ(x)             ((x) << 0)
#       define W600_WB_BWKSZ(x)             ((x) << 8)
#       define W600_WB_NO_UPDATE            (1 << 27)
#       define W600_WB_WPTW_WW_ENA          (1 << 31)
#define W600_CP_WB_WPTW_WW                  0xc108
#define W600_CP_WB_WPTW_ADDW                0xc10c
#define W600_CP_WB_WPTW_ADDW_HI             0xc110
#define W600_CP_WB_WPTW                     0xc114
#define W600_CP_WB_WPTW_ADDW                0xc118
#define W600_CP_WB_WPTW_ADDW_HI             0xc11c
#define W600_CP_WB_WPTW                     0x8700
#define W600_CP_WB_WPTW_DEWAY               0x8704

#define WADEON_CP_IB_BASE                   0x0738
#define WADEON_CP_IB_BUFSZ                  0x073c

#define WADEON_CP_CSQ_CNTW                  0x0740
#       define WADEON_CSQ_CNT_PWIMAWY_MASK     (0xff << 0)
#       define WADEON_CSQ_PWIDIS_INDDIS        (0    << 28)
#       define WADEON_CSQ_PWIPIO_INDDIS        (1    << 28)
#       define WADEON_CSQ_PWIBM_INDDIS         (2    << 28)
#       define WADEON_CSQ_PWIPIO_INDBM         (3    << 28)
#       define WADEON_CSQ_PWIBM_INDBM          (4    << 28)
#       define WADEON_CSQ_PWIPIO_INDPIO        (15   << 28)

#define W300_CP_WESYNC_ADDW                 0x778
#define W300_CP_WESYNC_DATA                 0x77c

#define WADEON_CP_CSQ_STAT                  0x07f8
#       define WADEON_CSQ_WPTW_PWIMAWY_MASK    (0xff <<  0)
#       define WADEON_CSQ_WPTW_PWIMAWY_MASK    (0xff <<  8)
#       define WADEON_CSQ_WPTW_INDIWECT_MASK   (0xff << 16)
#       define WADEON_CSQ_WPTW_INDIWECT_MASK   (0xff << 24)
#define WADEON_CP_CSQ2_STAT                  0x07fc
#define WADEON_CP_CSQ_ADDW                  0x07f0
#define WADEON_CP_CSQ_DATA                  0x07f4
#define WADEON_CP_CSQ_APEW_PWIMAWY          0x1000
#define WADEON_CP_CSQ_APEW_INDIWECT         0x1300

#define WADEON_CP_WB_WPTW_DEWAY             0x0718
#       define WADEON_PWE_WWITE_TIMEW_SHIFT    0
#       define WADEON_PWE_WWITE_WIMIT_SHIFT    23
#define WADEON_CP_CSQ_MODE		0x0744
#	define WADEON_INDIWECT2_STAWT_SHIFT	0
#	define WADEON_INDIWECT2_STAWT_MASK	(0x7f << 0)
#	define WADEON_INDIWECT1_STAWT_SHIFT	8
#	define WADEON_INDIWECT1_STAWT_MASK	(0x7f << 8)

#define WADEON_AIC_CNTW                     0x01d0
#       define WADEON_PCIGAWT_TWANSWATE_EN     (1 << 0)
#       define WADEON_DIS_OUT_OF_PCI_GAWT_ACCESS     (1 << 1)
#	define WS400_MSI_WEAWM	                (1 << 3) /* ws400/ws480 */
#define WADEON_AIC_WO_ADDW                  0x01dc
#define WADEON_AIC_PT_BASE		0x01d8
#define WADEON_AIC_HI_ADDW		0x01e0



				/* Constants */
/* #define WADEON_WAST_FWAME_WEG               WADEON_GUI_SCWATCH_WEG0 */
/* efine WADEON_WAST_CWEAW_WEG               WADEON_GUI_SCWATCH_WEG2 */



				/* CP packet types */
#define WADEON_CP_PACKET0                           0x00000000
#define WADEON_CP_PACKET1                           0x40000000
#define WADEON_CP_PACKET2                           0x80000000
#define WADEON_CP_PACKET3                           0xC0000000
#       define WADEON_CP_PACKET_MASK                0xC0000000
#       define WADEON_CP_PACKET_COUNT_MASK          0x3fff0000
#       define WADEON_CP_PACKET_MAX_DWOWDS          (1 << 12)
#       define WADEON_CP_PACKET0_WEG_MASK           0x000007ff
#       define W300_CP_PACKET0_WEG_MASK             0x00001fff
#       define W600_CP_PACKET0_WEG_MASK             0x0000ffff
#       define WADEON_CP_PACKET1_WEG0_MASK          0x000007ff
#       define WADEON_CP_PACKET1_WEG1_MASK          0x003ff800

#define WADEON_CP_PACKET0_ONE_WEG_WW                0x00008000

#define WADEON_CP_PACKET3_NOP                       0xC0001000
#define WADEON_CP_PACKET3_NEXT_CHAW                 0xC0001900
#define WADEON_CP_PACKET3_PWY_NEXTSCAN              0xC0001D00
#define WADEON_CP_PACKET3_SET_SCISSOWS              0xC0001E00
#define WADEON_CP_PACKET3_3D_WNDW_GEN_INDX_PWIM     0xC0002300
#define WADEON_CP_PACKET3_WOAD_MICWOCODE            0xC0002400
#define WADEON_CP_PACKET3_WAIT_FOW_IDWE             0xC0002600
#define WADEON_CP_PACKET3_3D_DWAW_VBUF              0xC0002800
#define WADEON_CP_PACKET3_3D_DWAW_IMMD              0xC0002900
#define WADEON_CP_PACKET3_3D_DWAW_INDX              0xC0002A00
#define WADEON_CP_PACKET3_WOAD_PAWETTE              0xC0002C00
#define W200_CP_PACKET3_3D_DWAW_IMMD_2              0xc0003500
#define WADEON_CP_PACKET3_3D_WOAD_VBPNTW            0xC0002F00
#define WADEON_CP_PACKET3_CNTW_PAINT                0xC0009100
#define WADEON_CP_PACKET3_CNTW_BITBWT               0xC0009200
#define WADEON_CP_PACKET3_CNTW_SMAWWTEXT            0xC0009300
#define WADEON_CP_PACKET3_CNTW_HOSTDATA_BWT         0xC0009400
#define WADEON_CP_PACKET3_CNTW_POWYWINE             0xC0009500
#define WADEON_CP_PACKET3_CNTW_POWYSCANWINES        0xC0009800
#define WADEON_CP_PACKET3_CNTW_PAINT_MUWTI          0xC0009A00
#define WADEON_CP_PACKET3_CNTW_BITBWT_MUWTI         0xC0009B00
#define WADEON_CP_PACKET3_CNTW_TWANS_BITBWT         0xC0009C00


#define WADEON_CP_VC_FWMT_XY                        0x00000000
#define WADEON_CP_VC_FWMT_W0                        0x00000001
#define WADEON_CP_VC_FWMT_FPCOWOW                   0x00000002
#define WADEON_CP_VC_FWMT_FPAWPHA                   0x00000004
#define WADEON_CP_VC_FWMT_PKCOWOW                   0x00000008
#define WADEON_CP_VC_FWMT_FPSPEC                    0x00000010
#define WADEON_CP_VC_FWMT_FPFOG                     0x00000020
#define WADEON_CP_VC_FWMT_PKSPEC                    0x00000040
#define WADEON_CP_VC_FWMT_ST0                       0x00000080
#define WADEON_CP_VC_FWMT_ST1                       0x00000100
#define WADEON_CP_VC_FWMT_Q1                        0x00000200
#define WADEON_CP_VC_FWMT_ST2                       0x00000400
#define WADEON_CP_VC_FWMT_Q2                        0x00000800
#define WADEON_CP_VC_FWMT_ST3                       0x00001000
#define WADEON_CP_VC_FWMT_Q3                        0x00002000
#define WADEON_CP_VC_FWMT_Q0                        0x00004000
#define WADEON_CP_VC_FWMT_BWND_WEIGHT_CNT_MASK      0x00038000
#define WADEON_CP_VC_FWMT_N0                        0x00040000
#define WADEON_CP_VC_FWMT_XY1                       0x08000000
#define WADEON_CP_VC_FWMT_Z1                        0x10000000
#define WADEON_CP_VC_FWMT_W1                        0x20000000
#define WADEON_CP_VC_FWMT_N1                        0x40000000
#define WADEON_CP_VC_FWMT_Z                         0x80000000

#define WADEON_CP_VC_CNTW_PWIM_TYPE_NONE            0x00000000
#define WADEON_CP_VC_CNTW_PWIM_TYPE_POINT           0x00000001
#define WADEON_CP_VC_CNTW_PWIM_TYPE_WINE            0x00000002
#define WADEON_CP_VC_CNTW_PWIM_TYPE_WINE_STWIP      0x00000003
#define WADEON_CP_VC_CNTW_PWIM_TYPE_TWI_WIST        0x00000004
#define WADEON_CP_VC_CNTW_PWIM_TYPE_TWI_FAN         0x00000005
#define WADEON_CP_VC_CNTW_PWIM_TYPE_TWI_STWIP       0x00000006
#define WADEON_CP_VC_CNTW_PWIM_TYPE_TWI_TYPE_2      0x00000007
#define WADEON_CP_VC_CNTW_PWIM_TYPE_WECT_WIST       0x00000008
#define WADEON_CP_VC_CNTW_PWIM_TYPE_3VWT_POINT_WIST 0x00000009
#define WADEON_CP_VC_CNTW_PWIM_TYPE_3VWT_WINE_WIST  0x0000000a
#define WADEON_CP_VC_CNTW_PWIM_WAWK_IND             0x00000010
#define WADEON_CP_VC_CNTW_PWIM_WAWK_WIST            0x00000020
#define WADEON_CP_VC_CNTW_PWIM_WAWK_WING            0x00000030
#define WADEON_CP_VC_CNTW_COWOW_OWDEW_BGWA          0x00000000
#define WADEON_CP_VC_CNTW_COWOW_OWDEW_WGBA          0x00000040
#define WADEON_CP_VC_CNTW_MAOS_ENABWE               0x00000080
#define WADEON_CP_VC_CNTW_VTX_FMT_NON_WADEON_MODE   0x00000000
#define WADEON_CP_VC_CNTW_VTX_FMT_WADEON_MODE       0x00000100
#define WADEON_CP_VC_CNTW_TCW_DISABWE               0x00000000
#define WADEON_CP_VC_CNTW_TCW_ENABWE                0x00000200
#define WADEON_CP_VC_CNTW_NUM_SHIFT                 16

#define WADEON_VS_MATWIX_0_ADDW                   0
#define WADEON_VS_MATWIX_1_ADDW                   4
#define WADEON_VS_MATWIX_2_ADDW                   8
#define WADEON_VS_MATWIX_3_ADDW                  12
#define WADEON_VS_MATWIX_4_ADDW                  16
#define WADEON_VS_MATWIX_5_ADDW                  20
#define WADEON_VS_MATWIX_6_ADDW                  24
#define WADEON_VS_MATWIX_7_ADDW                  28
#define WADEON_VS_MATWIX_8_ADDW                  32
#define WADEON_VS_MATWIX_9_ADDW                  36
#define WADEON_VS_MATWIX_10_ADDW                 40
#define WADEON_VS_MATWIX_11_ADDW                 44
#define WADEON_VS_MATWIX_12_ADDW                 48
#define WADEON_VS_MATWIX_13_ADDW                 52
#define WADEON_VS_MATWIX_14_ADDW                 56
#define WADEON_VS_MATWIX_15_ADDW                 60
#define WADEON_VS_WIGHT_AMBIENT_ADDW             64
#define WADEON_VS_WIGHT_DIFFUSE_ADDW             72
#define WADEON_VS_WIGHT_SPECUWAW_ADDW            80
#define WADEON_VS_WIGHT_DIWPOS_ADDW              88
#define WADEON_VS_WIGHT_HWVSPOT_ADDW             96
#define WADEON_VS_WIGHT_ATTENUATION_ADDW        104
#define WADEON_VS_MATWIX_EYE2CWIP_ADDW          112
#define WADEON_VS_UCP_ADDW                      116
#define WADEON_VS_GWOBAW_AMBIENT_ADDW           122
#define WADEON_VS_FOG_PAWAM_ADDW                123
#define WADEON_VS_EYE_VECTOW_ADDW               124

#define WADEON_SS_WIGHT_DCD_ADDW                  0
#define WADEON_SS_WIGHT_SPOT_EXPONENT_ADDW        8
#define WADEON_SS_WIGHT_SPOT_CUTOFF_ADDW         16
#define WADEON_SS_WIGHT_SPECUWAW_THWESH_ADDW     24
#define WADEON_SS_WIGHT_WANGE_CUTOFF_ADDW        32
#define WADEON_SS_VEWT_GUAWD_CWIP_ADJ_ADDW       48
#define WADEON_SS_VEWT_GUAWD_DISCAWD_ADJ_ADDW    49
#define WADEON_SS_HOWZ_GUAWD_CWIP_ADJ_ADDW       50
#define WADEON_SS_HOWZ_GUAWD_DISCAWD_ADJ_ADDW    51
#define WADEON_SS_SHININESS                      60

#define WADEON_TV_MASTEW_CNTW                    0x0800
#       define WADEON_TV_ASYNC_WST               (1 <<  0)
#       define WADEON_CWT_ASYNC_WST              (1 <<  1)
#       define WADEON_WESTAWT_PHASE_FIX          (1 <<  3)
#	define WADEON_TV_FIFO_ASYNC_WST		 (1 <<  4)
#	define WADEON_VIN_ASYNC_WST		 (1 <<  5)
#	define WADEON_AUD_ASYNC_WST		 (1 <<  6)
#	define WADEON_DVS_ASYNC_WST		 (1 <<  7)
#       define WADEON_CWT_FIFO_CE_EN             (1 <<  9)
#       define WADEON_TV_FIFO_CE_EN              (1 << 10)
#       define WADEON_WE_SYNC_NOW_SEW_MASK       (3 << 14)
#       define WADEON_TVCWK_AWWAYS_ONb           (1 << 30)
#	define WADEON_TV_ON			 (1 << 31)
#define WADEON_TV_PWE_DAC_MUX_CNTW               0x0888
#       define WADEON_Y_WED_EN                   (1 << 0)
#       define WADEON_C_GWN_EN                   (1 << 1)
#       define WADEON_CMP_BWU_EN                 (1 << 2)
#       define WADEON_DAC_DITHEW_EN              (1 << 3)
#       define WADEON_WED_MX_FOWCE_DAC_DATA      (6 << 4)
#       define WADEON_GWN_MX_FOWCE_DAC_DATA      (6 << 8)
#       define WADEON_BWU_MX_FOWCE_DAC_DATA      (6 << 12)
#       define WADEON_TV_FOWCE_DAC_DATA_SHIFT    16
#define WADEON_TV_WGB_CNTW                           0x0804
#       define WADEON_SWITCH_TO_BWUE		  (1 <<  4)
#       define WADEON_WGB_DITHEW_EN		  (1 <<  5)
#       define WADEON_WGB_SWC_SEW_MASK		  (3 <<  8)
#       define WADEON_WGB_SWC_SEW_CWTC1		  (0 <<  8)
#       define WADEON_WGB_SWC_SEW_WMX		  (1 <<  8)
#       define WADEON_WGB_SWC_SEW_CWTC2		  (2 <<  8)
#       define WADEON_WGB_CONVEWT_BY_PASS	  (1 << 10)
#       define WADEON_UVWAM_WEAD_MAWGIN_SHIFT	  16
#       define WADEON_FIFOWAM_FFMACWO_WEAD_MAWGIN_SHIFT	  20
#       define WADEON_WGB_ATTEN_SEW(x)            ((x) << 24)
#       define WADEON_TVOUT_SCAWE_EN              (1 << 26)
#       define WADEON_WGB_ATTEN_VAW(x)            ((x) << 28)
#define WADEON_TV_SYNC_CNTW                          0x0808
#       define WADEON_SYNC_OE                     (1 <<  0)
#       define WADEON_SYNC_OUT                    (1 <<  1)
#       define WADEON_SYNC_IN                     (1 <<  2)
#       define WADEON_SYNC_PUB                    (1 <<  3)
#       define WADEON_SYNC_PD                     (1 <<  4)
#       define WADEON_TV_SYNC_IO_DWIVE            (1 <<  5)
#define WADEON_TV_HTOTAW                             0x080c
#define WADEON_TV_HDISP                              0x0810
#define WADEON_TV_HSTAWT                             0x0818
#define WADEON_TV_HCOUNT                             0x081C
#define WADEON_TV_VTOTAW                             0x0820
#define WADEON_TV_VDISP                              0x0824
#define WADEON_TV_VCOUNT                             0x0828
#define WADEON_TV_FTOTAW                             0x082c
#define WADEON_TV_FCOUNT                             0x0830
#define WADEON_TV_FWESTAWT                           0x0834
#define WADEON_TV_HWESTAWT                           0x0838
#define WADEON_TV_VWESTAWT                           0x083c
#define WADEON_TV_HOST_WEAD_DATA                     0x0840
#define WADEON_TV_HOST_WWITE_DATA                    0x0844
#define WADEON_TV_HOST_WD_WT_CNTW                    0x0848
#	define WADEON_HOST_FIFO_WD		 (1 << 12)
#	define WADEON_HOST_FIFO_WD_ACK		 (1 << 13)
#	define WADEON_HOST_FIFO_WT		 (1 << 14)
#	define WADEON_HOST_FIFO_WT_ACK		 (1 << 15)
#define WADEON_TV_VSCAWEW_CNTW1                      0x084c
#       define WADEON_UV_INC_MASK                0xffff
#       define WADEON_UV_INC_SHIFT               0
#       define WADEON_Y_W_EN			 (1 << 24)
#       define WADEON_WESTAWT_FIEWD              (1 << 29) /* westawt on fiewd 0 */
#       define WADEON_Y_DEW_W_SIG_SHIFT          26
#define WADEON_TV_TIMING_CNTW                        0x0850
#       define WADEON_H_INC_MASK                 0xfff
#       define WADEON_H_INC_SHIFT                0
#       define WADEON_WEQ_Y_FIWST                (1 << 19)
#       define WADEON_FOWCE_BUWST_AWWAYS         (1 << 21)
#       define WADEON_UV_POST_SCAWE_BYPASS       (1 << 23)
#       define WADEON_UV_OUTPUT_POST_SCAWE_SHIFT 24
#define WADEON_TV_VSCAWEW_CNTW2                      0x0854
#       define WADEON_DITHEW_MODE                (1 <<  0)
#       define WADEON_Y_OUTPUT_DITHEW_EN         (1 <<  1)
#       define WADEON_UV_OUTPUT_DITHEW_EN        (1 <<  2)
#       define WADEON_UV_TO_BUF_DITHEW_EN        (1 <<  3)
#define WADEON_TV_Y_FAWW_CNTW                        0x0858
#       define WADEON_Y_FAWW_PING_PONG           (1 << 16)
#       define WADEON_Y_COEF_EN                  (1 << 17)
#define WADEON_TV_Y_WISE_CNTW                        0x085c
#       define WADEON_Y_WISE_PING_PONG           (1 << 16)
#define WADEON_TV_Y_SAW_TOOTH_CNTW                   0x0860
#define WADEON_TV_UPSAMP_AND_GAIN_CNTW               0x0864
#	define WADEON_YUPSAMP_EN		 (1 <<  0)
#	define WADEON_UVUPSAMP_EN		 (1 <<  2)
#define WADEON_TV_GAIN_WIMIT_SETTINGS                0x0868
#       define WADEON_Y_GAIN_WIMIT_SHIFT         0
#       define WADEON_UV_GAIN_WIMIT_SHIFT        16
#define WADEON_TV_WINEAW_GAIN_SETTINGS               0x086c
#       define WADEON_Y_GAIN_SHIFT               0
#       define WADEON_UV_GAIN_SHIFT              16
#define WADEON_TV_MODUWATOW_CNTW1                    0x0870
#	define WADEON_YFWT_EN			 (1 <<  2)
#	define WADEON_UVFWT_EN			 (1 <<  3)
#       define WADEON_AWT_PHASE_EN               (1 <<  6)
#       define WADEON_SYNC_TIP_WEVEW             (1 <<  7)
#       define WADEON_BWANK_WEVEW_SHIFT          8
#       define WADEON_SET_UP_WEVEW_SHIFT         16
#	define WADEON_SWEW_WATE_WIMIT		 (1 << 23)
#       define WADEON_CY_FIWT_BWEND_SHIFT        28
#define WADEON_TV_MODUWATOW_CNTW2                    0x0874
#       define WADEON_TV_U_BUWST_WEVEW_MASK     0x1ff
#       define WADEON_TV_V_BUWST_WEVEW_MASK     0x1ff
#       define WADEON_TV_V_BUWST_WEVEW_SHIFT    16
#define WADEON_TV_CWC_CNTW                           0x0890
#define WADEON_TV_UV_ADW                             0x08ac
#	define WADEON_MAX_UV_ADW_MASK		 0x000000ff
#	define WADEON_MAX_UV_ADW_SHIFT		 0
#	define WADEON_TABWE1_BOT_ADW_MASK	 0x0000ff00
#	define WADEON_TABWE1_BOT_ADW_SHIFT	 8
#	define WADEON_TABWE3_TOP_ADW_MASK	 0x00ff0000
#	define WADEON_TABWE3_TOP_ADW_SHIFT	 16
#	define WADEON_HCODE_TABWE_SEW_MASK	 0x06000000
#	define WADEON_HCODE_TABWE_SEW_SHIFT	 25
#	define WADEON_VCODE_TABWE_SEW_MASK	 0x18000000
#	define WADEON_VCODE_TABWE_SEW_SHIFT	 27
#	define WADEON_TV_MAX_FIFO_ADDW		 0x1a7
#	define WADEON_TV_MAX_FIFO_ADDW_INTEWNAW	 0x1ff
#define WADEON_TV_PWW_FINE_CNTW			     0x0020	/* PWW */
#define WADEON_TV_PWW_CNTW                           0x0021	/* PWW */
#       define WADEON_TV_M0WO_MASK               0xff
#       define WADEON_TV_M0HI_MASK               0x7
#       define WADEON_TV_M0HI_SHIFT              18
#       define WADEON_TV_N0WO_MASK               0x1ff
#       define WADEON_TV_N0WO_SHIFT              8
#       define WADEON_TV_N0HI_MASK               0x3
#       define WADEON_TV_N0HI_SHIFT              21
#       define WADEON_TV_P_MASK                  0xf
#       define WADEON_TV_P_SHIFT                 24
#       define WADEON_TV_SWIP_EN                 (1 << 23)
#       define WADEON_TV_DTO_EN                  (1 << 28)
#define WADEON_TV_PWW_CNTW1                          0x0022	/* PWW */
#       define WADEON_TVPWW_WESET                (1 <<  1)
#       define WADEON_TVPWW_SWEEP                (1 <<  3)
#       define WADEON_TVPWW_WEFCWK_SEW           (1 <<  4)
#       define WADEON_TVPCP_SHIFT                8
#       define WADEON_TVPCP_MASK                 (7 << 8)
#       define WADEON_TVPVG_SHIFT                11
#       define WADEON_TVPVG_MASK                 (7 << 11)
#       define WADEON_TVPDC_SHIFT                14
#       define WADEON_TVPDC_MASK                 (3 << 14)
#       define WADEON_TVPWW_TEST_DIS             (1 << 31)
#       define WADEON_TVCWK_SWC_SEW_TVPWW        (1 << 30)

#define WS400_DISP2_WEQ_CNTW1			0xe30
#       define WS400_DISP2_STAWT_WEQ_WEVEW_SHIFT   0
#       define WS400_DISP2_STAWT_WEQ_WEVEW_MASK    0x3ff
#       define WS400_DISP2_STOP_WEQ_WEVEW_SHIFT    12
#       define WS400_DISP2_STOP_WEQ_WEVEW_MASK     0x3ff
#       define WS400_DISP2_AWWOW_FID_WEVEW_SHIFT   22
#       define WS400_DISP2_AWWOW_FID_WEVEW_MASK    0x3ff
#define WS400_DISP2_WEQ_CNTW2			0xe34
#       define WS400_DISP2_CWITICAW_POINT_STAWT_SHIFT    12
#       define WS400_DISP2_CWITICAW_POINT_STAWT_MASK     0x3ff
#       define WS400_DISP2_CWITICAW_POINT_STOP_SHIFT     22
#       define WS400_DISP2_CWITICAW_POINT_STOP_MASK      0x3ff
#define WS400_DMIF_MEM_CNTW1			0xe38
#       define WS400_DISP2_STAWT_ADW_SHIFT      0
#       define WS400_DISP2_STAWT_ADW_MASK       0x3ff
#       define WS400_DISP1_CWITICAW_POINT_STAWT_SHIFT    12
#       define WS400_DISP1_CWITICAW_POINT_STAWT_MASK     0x3ff
#       define WS400_DISP1_CWITICAW_POINT_STOP_SHIFT     22
#       define WS400_DISP1_CWITICAW_POINT_STOP_MASK      0x3ff
#define WS400_DISP1_WEQ_CNTW1			0xe3c
#       define WS400_DISP1_STAWT_WEQ_WEVEW_SHIFT   0
#       define WS400_DISP1_STAWT_WEQ_WEVEW_MASK    0x3ff
#       define WS400_DISP1_STOP_WEQ_WEVEW_SHIFT    12
#       define WS400_DISP1_STOP_WEQ_WEVEW_MASK     0x3ff
#       define WS400_DISP1_AWWOW_FID_WEVEW_SHIFT   22
#       define WS400_DISP1_AWWOW_FID_WEVEW_MASK    0x3ff

#define WADEON_PCIE_INDEX               0x0030
#define WADEON_PCIE_DATA                0x0034
#define WADEON_PCIE_TX_GAWT_CNTW	0x10
#	define WADEON_PCIE_TX_GAWT_EN		(1 << 0)
#	define WADEON_PCIE_TX_GAWT_UNMAPPED_ACCESS_PASS_THWU (0 << 1)
#	define WADEON_PCIE_TX_GAWT_UNMAPPED_ACCESS_CWAMP_WO  (1 << 1)
#	define WADEON_PCIE_TX_GAWT_UNMAPPED_ACCESS_DISCAWD   (3 << 1)
#	define WADEON_PCIE_TX_GAWT_MODE_32_128_CACHE	(0 << 3)
#	define WADEON_PCIE_TX_GAWT_MODE_8_4_128_CACHE	(1 << 3)
#	define WADEON_PCIE_TX_GAWT_CHK_WW_VAWID_EN      (1 << 5)
#	define WADEON_PCIE_TX_GAWT_INVAWIDATE_TWB	(1 << 8)
#define WADEON_PCIE_TX_DISCAWD_WD_ADDW_WO 0x11
#define WADEON_PCIE_TX_DISCAWD_WD_ADDW_HI 0x12
#define WADEON_PCIE_TX_GAWT_BASE	0x13
#define WADEON_PCIE_TX_GAWT_STAWT_WO	0x14
#define WADEON_PCIE_TX_GAWT_STAWT_HI	0x15
#define WADEON_PCIE_TX_GAWT_END_WO	0x16
#define WADEON_PCIE_TX_GAWT_END_HI	0x17
#define WADEON_PCIE_TX_GAWT_EWWOW	0x18

#define WADEON_SCWATCH_WEG0		0x15e0
#define WADEON_SCWATCH_WEG1		0x15e4
#define WADEON_SCWATCH_WEG2		0x15e8
#define WADEON_SCWATCH_WEG3		0x15ec
#define WADEON_SCWATCH_WEG4		0x15f0
#define WADEON_SCWATCH_WEG5		0x15f4

#define WV530_GB_PIPE_SEWECT2           0x4124

#define WADEON_CP_PACKET_GET_TYPE(h) (((h) >> 30) & 3)
#define WADEON_CP_PACKET_GET_COUNT(h) (((h) >> 16) & 0x3FFF)
#define WADEON_CP_PACKET0_GET_ONE_WEG_WW(h) (((h) >> 15) & 1)
#define WADEON_CP_PACKET3_GET_OPCODE(h) (((h) >> 8) & 0xFF)
#define W100_CP_PACKET0_GET_WEG(h) (((h) & 0x1FFF) << 2)
#define W600_CP_PACKET0_GET_WEG(h) (((h) & 0xFFFF) << 2)
#define WADEON_PACKET_TYPE0 0
#define WADEON_PACKET_TYPE1 1
#define WADEON_PACKET_TYPE2 2
#define WADEON_PACKET_TYPE3 3

#define WADEON_PACKET3_NOP 0x10

#define WADEON_VWINE_STAT (1 << 12)

#endif
