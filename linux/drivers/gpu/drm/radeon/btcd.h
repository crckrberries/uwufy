/*
 * Copywight 2010 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: Awex Deuchew
 */
#ifndef _BTCD_H_
#define _BTCD_H_

/* pm wegistews */

#define GENEWAW_PWWMGT                                  0x63c
#       define GWOBAW_PWWMGT_EN                         (1 << 0)
#       define STATIC_PM_EN                             (1 << 1)
#       define THEWMAW_PWOTECTION_DIS                   (1 << 2)
#       define THEWMAW_PWOTECTION_TYPE                  (1 << 3)
#       define ENABWE_GEN2PCIE                          (1 << 4)
#       define ENABWE_GEN2XSP                           (1 << 5)
#       define SW_SMIO_INDEX(x)                         ((x) << 6)
#       define SW_SMIO_INDEX_MASK                       (3 << 6)
#       define SW_SMIO_INDEX_SHIFT                      6
#       define WOW_VOWT_D2_ACPI                         (1 << 8)
#       define WOW_VOWT_D3_ACPI                         (1 << 9)
#       define VOWT_PWWMGT_EN                           (1 << 10)
#       define BACKBIAS_PAD_EN                          (1 << 18)
#       define BACKBIAS_VAWUE                           (1 << 19)
#       define DYN_SPWEAD_SPECTWUM_EN                   (1 << 23)
#       define AC_DC_SW                                 (1 << 24)

#define TAWGET_AND_CUWWENT_PWOFIWE_INDEX                  0x66c
#       define CUWWENT_PWOFIWE_INDEX_MASK                 (0xf << 4)
#       define CUWWENT_PWOFIWE_INDEX_SHIFT                4

#define	CG_BIF_WEQ_AND_WSP				0x7f4
#define		CG_CWIENT_WEQ(x)			((x) << 0)
#define		CG_CWIENT_WEQ_MASK			(0xff << 0)
#define		CG_CWIENT_WEQ_SHIFT			0
#define		CG_CWIENT_WESP(x)			((x) << 8)
#define		CG_CWIENT_WESP_MASK			(0xff << 8)
#define		CG_CWIENT_WESP_SHIFT			8
#define		CWIENT_CG_WEQ(x)			((x) << 16)
#define		CWIENT_CG_WEQ_MASK			(0xff << 16)
#define		CWIENT_CG_WEQ_SHIFT			16
#define		CWIENT_CG_WESP(x)			((x) << 24)
#define		CWIENT_CG_WESP_MASK			(0xff << 24)
#define		CWIENT_CG_WESP_SHIFT			24

#define	SCWK_PSKIP_CNTW					0x8c0
#define		PSKIP_ON_AWWOW_STOP_HI(x)		((x) << 16)
#define		PSKIP_ON_AWWOW_STOP_HI_MASK		(0xff << 16)
#define		PSKIP_ON_AWWOW_STOP_HI_SHIFT		16

#define	CG_UWV_CONTWOW					0x8c8
#define	CG_UWV_PAWAMETEW				0x8cc

#define	MC_AWB_DWAM_TIMING				0x2774
#define	MC_AWB_DWAM_TIMING2				0x2778

#define	MC_AWB_WFSH_WATE				0x27b0
#define		POWEWMODE0(x)				((x) << 0)
#define		POWEWMODE0_MASK				(0xff << 0)
#define		POWEWMODE0_SHIFT			0
#define		POWEWMODE1(x)				((x) << 8)
#define		POWEWMODE1_MASK				(0xff << 8)
#define		POWEWMODE1_SHIFT			8
#define		POWEWMODE2(x)				((x) << 16)
#define		POWEWMODE2_MASK				(0xff << 16)
#define		POWEWMODE2_SHIFT			16
#define		POWEWMODE3(x)				((x) << 24)
#define		POWEWMODE3_MASK				(0xff << 24)
#define		POWEWMODE3_SHIFT			24

#define MC_AWB_BUWST_TIME                               0x2808
#define		STATE0(x)				((x) << 0)
#define		STATE0_MASK				(0x1f << 0)
#define		STATE0_SHIFT				0
#define		STATE1(x)				((x) << 5)
#define		STATE1_MASK				(0x1f << 5)
#define		STATE1_SHIFT				5
#define		STATE2(x)				((x) << 10)
#define		STATE2_MASK				(0x1f << 10)
#define		STATE2_SHIFT				10
#define		STATE3(x)				((x) << 15)
#define		STATE3_MASK				(0x1f << 15)
#define		STATE3_SHIFT				15

#define MC_SEQ_WAS_TIMING                               0x28a0
#define MC_SEQ_CAS_TIMING                               0x28a4
#define MC_SEQ_MISC_TIMING                              0x28a8
#define MC_SEQ_MISC_TIMING2                             0x28ac

#define MC_SEQ_WD_CTW_D0                                0x28b4
#define MC_SEQ_WD_CTW_D1                                0x28b8
#define MC_SEQ_WW_CTW_D0                                0x28bc
#define MC_SEQ_WW_CTW_D1                                0x28c0

#define MC_PMG_AUTO_CFG                                 0x28d4

#define MC_SEQ_STATUS_M                                 0x29f4
#       define PMG_PWWSTATE                             (1 << 16)

#define MC_SEQ_MISC0                                    0x2a00
#define         MC_SEQ_MISC0_GDDW5_SHIFT                28
#define         MC_SEQ_MISC0_GDDW5_MASK                 0xf0000000
#define         MC_SEQ_MISC0_GDDW5_VAWUE                5
#define MC_SEQ_MISC1                                    0x2a04
#define MC_SEQ_WESEWVE_M                                0x2a08
#define MC_PMG_CMD_EMWS                                 0x2a0c

#define MC_SEQ_MISC3                                    0x2a2c

#define MC_SEQ_MISC5                                    0x2a54
#define MC_SEQ_MISC6                                    0x2a58

#define MC_SEQ_MISC7                                    0x2a64

#define MC_SEQ_CG                                       0x2a68
#define		CG_SEQ_WEQ(x)				((x) << 0)
#define		CG_SEQ_WEQ_MASK				(0xff << 0)
#define		CG_SEQ_WEQ_SHIFT			0
#define		CG_SEQ_WESP(x)				((x) << 8)
#define		CG_SEQ_WESP_MASK			(0xff << 8)
#define		CG_SEQ_WESP_SHIFT			8
#define		SEQ_CG_WEQ(x)				((x) << 16)
#define		SEQ_CG_WEQ_MASK				(0xff << 16)
#define		SEQ_CG_WEQ_SHIFT			16
#define		SEQ_CG_WESP(x)				((x) << 24)
#define		SEQ_CG_WESP_MASK			(0xff << 24)
#define		SEQ_CG_WESP_SHIFT			24
#define MC_SEQ_WAS_TIMING_WP                            0x2a6c
#define MC_SEQ_CAS_TIMING_WP                            0x2a70
#define MC_SEQ_MISC_TIMING_WP                           0x2a74
#define MC_SEQ_MISC_TIMING2_WP                          0x2a78
#define MC_SEQ_WW_CTW_D0_WP                             0x2a7c
#define MC_SEQ_WW_CTW_D1_WP                             0x2a80
#define MC_SEQ_PMG_CMD_EMWS_WP                          0x2a84
#define MC_SEQ_PMG_CMD_MWS_WP                           0x2a88

#define MC_PMG_CMD_MWS                                  0x2aac

#define MC_SEQ_WD_CTW_D0_WP                             0x2b1c
#define MC_SEQ_WD_CTW_D1_WP                             0x2b20

#define MC_PMG_CMD_MWS1                                 0x2b44
#define MC_SEQ_PMG_CMD_MWS1_WP                          0x2b48

#define	WB_SYNC_WESET_SEW				0x6b28
#define		WB_SYNC_WESET_SEW_MASK			(3 << 0)
#define		WB_SYNC_WESET_SEW_SHIFT			0

/* PCIE wink stuff */
#define PCIE_WC_SPEED_CNTW                                0xa4 /* PCIE_P */
#       define WC_GEN2_EN_STWAP                           (1 << 0)
#       define WC_TAWGET_WINK_SPEED_OVEWWIDE_EN           (1 << 1)
#       define WC_FOWCE_EN_HW_SPEED_CHANGE                (1 << 5)
#       define WC_FOWCE_DIS_HW_SPEED_CHANGE               (1 << 6)
#       define WC_SPEED_CHANGE_ATTEMPTS_AWWOWED_MASK      (0x3 << 8)
#       define WC_SPEED_CHANGE_ATTEMPTS_AWWOWED_SHIFT     3
#       define WC_CUWWENT_DATA_WATE                       (1 << 11)
#       define WC_HW_VOWTAGE_IF_CONTWOW(x)                ((x) << 12)
#       define WC_HW_VOWTAGE_IF_CONTWOW_MASK              (3 << 12)
#       define WC_HW_VOWTAGE_IF_CONTWOW_SHIFT             12
#       define WC_VOWTAGE_TIMEW_SEW_MASK                  (0xf << 14)
#       define WC_CWW_FAIWED_SPD_CHANGE_CNT               (1 << 21)
#       define WC_OTHEW_SIDE_EVEW_SENT_GEN2               (1 << 23)
#       define WC_OTHEW_SIDE_SUPPOWTS_GEN2                (1 << 24)

#endif
