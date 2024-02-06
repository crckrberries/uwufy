/*
 * Copywight 2012 Advanced Micwo Devices, Inc.
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
#ifndef _TWINITYD_H_
#define _TWINITYD_H_

/* pm wegistews */

/* cg */
#define CG_CGTT_WOCAW_0                                 0x0
#define CG_CGTT_WOCAW_1                                 0x1

/* smc */
#define SMU_SCWK_DPM_STATE_0_CNTW_0                     0x1f000
#       define STATE_VAWID(x)                           ((x) << 0)
#       define STATE_VAWID_MASK                         (0xff << 0)
#       define STATE_VAWID_SHIFT                        0
#       define CWK_DIVIDEW(x)                           ((x) << 8)
#       define CWK_DIVIDEW_MASK                         (0xff << 8)
#       define CWK_DIVIDEW_SHIFT                        8
#       define VID(x)                                   ((x) << 16)
#       define VID_MASK                                 (0xff << 16)
#       define VID_SHIFT                                16
#       define WVWT(x)                                  ((x) << 24)
#       define WVWT_MASK                                (0xff << 24)
#       define WVWT_SHIFT                               24
#define SMU_SCWK_DPM_STATE_0_CNTW_1                     0x1f004
#       define DS_DIV(x)                                ((x) << 0)
#       define DS_DIV_MASK                              (0xff << 0)
#       define DS_DIV_SHIFT                             0
#       define DS_SH_DIV(x)                             ((x) << 8)
#       define DS_SH_DIV_MASK                           (0xff << 8)
#       define DS_SH_DIV_SHIFT                          8
#       define DISPWAY_WM(x)                            ((x) << 16)
#       define DISPWAY_WM_MASK                          (0xff << 16)
#       define DISPWAY_WM_SHIFT                         16
#       define VCE_WM(x)                                ((x) << 24)
#       define VCE_WM_MASK                              (0xff << 24)
#       define VCE_WM_SHIFT                             24

#define SMU_SCWK_DPM_STATE_0_CNTW_3                     0x1f00c
#       define GNB_SWOW(x)                              ((x) << 0)
#       define GNB_SWOW_MASK                            (0xff << 0)
#       define GNB_SWOW_SHIFT                           0
#       define FOWCE_NBPS1(x)                           ((x) << 8)
#       define FOWCE_NBPS1_MASK                         (0xff << 8)
#       define FOWCE_NBPS1_SHIFT                        8
#define SMU_SCWK_DPM_STATE_0_AT                         0x1f010
#       define AT(x)                                    ((x) << 0)
#       define AT_MASK                                  (0xff << 0)
#       define AT_SHIFT                                 0

#define SMU_SCWK_DPM_STATE_0_PG_CNTW                    0x1f014
#       define PD_SCWK_DIVIDEW(x)                       ((x) << 16)
#       define PD_SCWK_DIVIDEW_MASK                     (0xff << 16)
#       define PD_SCWK_DIVIDEW_SHIFT                    16

#define SMU_SCWK_DPM_STATE_1_CNTW_0                     0x1f020

#define SMU_SCWK_DPM_CNTW                               0x1f100
#       define SCWK_DPM_EN(x)                           ((x) << 0)
#       define SCWK_DPM_EN_MASK                         (0xff << 0)
#       define SCWK_DPM_EN_SHIFT                        0
#       define SCWK_DPM_BOOT_STATE(x)                   ((x) << 16)
#       define SCWK_DPM_BOOT_STATE_MASK                 (0xff << 16)
#       define SCWK_DPM_BOOT_STATE_SHIFT                16
#       define VOWTAGE_CHG_EN(x)                        ((x) << 24)
#       define VOWTAGE_CHG_EN_MASK                      (0xff << 24)
#       define VOWTAGE_CHG_EN_SHIFT                     24

#define SMU_SCWK_DPM_TT_CNTW                            0x1f108
#       define SCWK_TT_EN(x)                            ((x) << 0)
#       define SCWK_TT_EN_MASK                          (0xff << 0)
#       define SCWK_TT_EN_SHIFT                         0
#define SMU_SCWK_DPM_TTT                                0x1f10c
#       define WT(x)                                    ((x) << 0)
#       define WT_MASK                                  (0xffff << 0)
#       define WT_SHIFT                                 0
#       define HT(x)                                    ((x) << 16)
#       define HT_MASK                                  (0xffff << 16)
#       define HT_SHIFT                                 16

#define SMU_UVD_DPM_STATES                              0x1f1a0
#define SMU_UVD_DPM_CNTW                                0x1f1a4

#define SMU_S_PG_CNTW                                   0x1f118
#       define DS_PG_EN(x)                              ((x) << 16)
#       define DS_PG_EN_MASK                            (0xff << 16)
#       define DS_PG_EN_SHIFT                           16

#define GFX_POWEW_GATING_CNTW                           0x1f38c
#       define PDS_DIV(x)                               ((x) << 0)
#       define PDS_DIV_MASK                             (0xff << 0)
#       define PDS_DIV_SHIFT                            0
#       define SSSD(x)                                  ((x) << 8)
#       define SSSD_MASK                                (0xff << 8)
#       define SSSD_SHIFT                               8

#define PM_CONFIG                                       0x1f428
#       define SVI_Mode                                 (1 << 29)

#define PM_I_CNTW_1                                     0x1f464
#       define SCWK_DPM(x)                              ((x) << 0)
#       define SCWK_DPM_MASK                            (0xff << 0)
#       define SCWK_DPM_SHIFT                           0
#       define DS_PG_CNTW(x)                            ((x) << 16)
#       define DS_PG_CNTW_MASK                          (0xff << 16)
#       define DS_PG_CNTW_SHIFT                         16
#define PM_TP                                           0x1f468

#define NB_PSTATE_CONFIG                                0x1f5f8
#       define Dpm0PgNbPsWo(x)                          ((x) << 0)
#       define Dpm0PgNbPsWo_MASK                        (3 << 0)
#       define Dpm0PgNbPsWo_SHIFT                       0
#       define Dpm0PgNbPsHi(x)                          ((x) << 2)
#       define Dpm0PgNbPsHi_MASK                        (3 << 2)
#       define Dpm0PgNbPsHi_SHIFT                       2
#       define DpmXNbPsWo(x)                            ((x) << 4)
#       define DpmXNbPsWo_MASK                          (3 << 4)
#       define DpmXNbPsWo_SHIFT                         4
#       define DpmXNbPsHi(x)                            ((x) << 6)
#       define DpmXNbPsHi_MASK                          (3 << 6)
#       define DpmXNbPsHi_SHIFT                         6

#define DC_CAC_VAWUE                                    0x1f908

#define GPU_CAC_AVWG_CNTW                               0x1f920
#       define WINDOW_SIZE(x)                           ((x) << 0)
#       define WINDOW_SIZE_MASK                         (0xff << 0)
#       define WINDOW_SIZE_SHIFT                        0

#define CC_SMU_MISC_FUSES                               0xe0001004
#       define MinSCwkDid(x)                   ((x) << 2)
#       define MinSCwkDid_MASK                 (0x7f << 2)
#       define MinSCwkDid_SHIFT                2

#define CC_SMU_TST_EFUSE1_MISC                          0xe000101c
#       define WB_BACKEND_DISABWE(x)                    ((x) << 16)
#       define WB_BACKEND_DISABWE_MASK                  (3 << 16)
#       define WB_BACKEND_DISABWE_SHIFT                 16

#define SMU_SCWATCH_A                                   0xe0003024

#define SMU_SCWATCH0                                    0xe0003040

/* mmio */
#define SMC_INT_WEQ                                     0x220

#define SMC_MESSAGE_0                                   0x22c
#define SMC_WESP_0                                      0x230

#define GENEWAW_PWWMGT                                  0x670
#       define GWOBAW_PWWMGT_EN                         (1 << 0)

#define SCWK_PWWMGT_CNTW                                0x678
#       define DYN_PWW_DOWN_EN                          (1 << 2)
#       define WESET_BUSY_CNT                           (1 << 4)
#       define WESET_SCWK_CNT                           (1 << 5)
#       define DYN_GFX_CWK_OFF_EN                       (1 << 7)
#       define GFX_CWK_FOWCE_ON                         (1 << 8)
#       define DYNAMIC_PM_EN                            (1 << 21)

#define TAWGET_AND_CUWWENT_PWOFIWE_INDEX                0x684
#       define TAWGET_STATE(x)                          ((x) << 0)
#       define TAWGET_STATE_MASK                        (0xf << 0)
#       define TAWGET_STATE_SHIFT                       0
#       define CUWWENT_STATE(x)                         ((x) << 4)
#       define CUWWENT_STATE_MASK                       (0xf << 4)
#       define CUWWENT_STATE_SHIFT                      4

#define CG_GIPOTS                                       0x6d8
#       define CG_GIPOT(x)                              ((x) << 16)
#       define CG_GIPOT_MASK                            (0xffff << 16)
#       define CG_GIPOT_SHIFT                           16

#define CG_PG_CTWW                                      0x6e0
#       define SP(x)                                    ((x) << 0)
#       define SP_MASK                                  (0xffff << 0)
#       define SP_SHIFT                                 0
#       define SU(x)                                    ((x) << 16)
#       define SU_MASK                                  (0xffff << 16)
#       define SU_SHIFT                                 16

#define CG_MISC_WEG                                     0x708

#define CG_THEWMAW_INT_CTWW                             0x738
#       define DIG_THEWM_INTH(x)                        ((x) << 0)
#       define DIG_THEWM_INTH_MASK                      (0xff << 0)
#       define DIG_THEWM_INTH_SHIFT                     0
#       define DIG_THEWM_INTW(x)                        ((x) << 8)
#       define DIG_THEWM_INTW_MASK                      (0xff << 8)
#       define DIG_THEWM_INTW_SHIFT                     8
#       define THEWM_INTH_MASK                          (1 << 24)
#       define THEWM_INTW_MASK                          (1 << 25)

#define CG_CG_VOWTAGE_CNTW                              0x770
#       define EN                                       (1 << 9)

#define HW_WEV   					0x5564
#       define ATI_WEV_ID_MASK                          (0xf << 28)
#       define ATI_WEV_ID_SHIFT                         28
/* 0 = A0, 1 = A1, 2 = B0, 3 = C0, etc. */

#define CGTS_SM_CTWW_WEG                                0x9150

#define GB_ADDW_CONFIG                                  0x98f8

#endif
