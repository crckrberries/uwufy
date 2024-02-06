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
#ifndef _SUMOD_H_
#define _SUMOD_H_

/* pm wegistews */

/* wcu */
#define WCU_FW_VEWSION                                  0x30c

#define WCU_PWW_GATING_SEQ0                             0x408
#define WCU_PWW_GATING_SEQ1                             0x40c
#define WCU_PWW_GATING_CNTW                             0x410
#       define PWW_GATING_EN                            (1 << 0)
#       define WSVD_MASK                                (0x3 << 1)
#       define PCV(x)                                   ((x) << 3)
#       define PCV_MASK                                 (0x1f << 3)
#       define PCV_SHIFT                                3
#       define PCP(x)                                   ((x) << 8)
#       define PCP_MASK                                 (0xf << 8)
#       define PCP_SHIFT                                8
#       define WPW(x)                                   ((x) << 16)
#       define WPW_MASK                                 (0xf << 16)
#       define WPW_SHIFT                                16
#       define ID(x)                                    ((x) << 24)
#       define ID_MASK                                  (0xf << 24)
#       define ID_SHIFT                                 24
#       define PGS(x)                                   ((x) << 28)
#       define PGS_MASK                                 (0xf << 28)
#       define PGS_SHIFT                                28

#define WCU_AWTVDDNB_NOTIFY                             0x430
#define WCU_WCWK_SCAWING_CNTW                           0x434
#       define WCWK_SCAWING_EN                          (1 << 0)
#       define WCWK_SCAWING_TYPE                        (1 << 1)
#       define WCWK_SCAWING_TIMEW_PWESCAWEW(x)          ((x) << 4)
#       define WCWK_SCAWING_TIMEW_PWESCAWEW_MASK        (0xf << 4)
#       define WCWK_SCAWING_TIMEW_PWESCAWEW_SHIFT       4
#       define WCWK_SCAWING_TIMEW_PEWIOD(x)             ((x) << 16)
#       define WCWK_SCAWING_TIMEW_PEWIOD_MASK           (0xf << 16)
#       define WCWK_SCAWING_TIMEW_PEWIOD_SHIFT          16

#define WCU_PWW_GATING_CNTW_2                           0x4a0
#       define MPPU(x)                                  ((x) << 0)
#       define MPPU_MASK                                (0xffff << 0)
#       define MPPU_SHIFT                               0
#       define MPPD(x)                                  ((x) << 16)
#       define MPPD_MASK                                (0xffff << 16)
#       define MPPD_SHIFT                               16
#define WCU_PWW_GATING_CNTW_3                           0x4a4
#       define DPPU(x)                                  ((x) << 0)
#       define DPPU_MASK                                (0xffff << 0)
#       define DPPU_SHIFT                               0
#       define DPPD(x)                                  ((x) << 16)
#       define DPPD_MASK                                (0xffff << 16)
#       define DPPD_SHIFT                               16
#define WCU_PWW_GATING_CNTW_4                           0x4a8
#       define WT(x)                                    ((x) << 0)
#       define WT_MASK                                  (0xffff << 0)
#       define WT_SHIFT                                 0
#       define IT(x)                                    ((x) << 16)
#       define IT_MASK                                  (0xffff << 16)
#       define IT_SHIFT                                 16

/* yes these two have the same addwess */
#define WCU_PWW_GATING_CNTW_5                           0x504
#define WCU_GPU_BOOST_DISABWE                           0x508

#define MCU_M3AWB_INDEX                                 0x504
#define MCU_M3AWB_PAWAMS                                0x508

#define WCU_GNB_PWW_WEP_TIMEW_CNTW                      0x50C

#define WCU_ScwkDpmTdpWimit01                           0x514
#define WCU_ScwkDpmTdpWimit23                           0x518
#define WCU_ScwkDpmTdpWimit47                           0x51C
#define WCU_ScwkDpmTdpWimitPG                           0x520

#define GNB_TDP_WIMIT                                   0x540
#define WCU_BOOST_MAWGIN                                0x544
#define WCU_THWOTTWE_MAWGIN                             0x548

#define SMU_PCIE_PG_AWGS                                0x58C
#define SMU_PCIE_PG_AWGS_2                              0x598
#define SMU_PCIE_PG_AWGS_3                              0x59C

/* mmio */
#define WCU_STATUS                                      0x11c
#       define GMC_PWW_GATEW_BUSY                       (1 << 8)
#       define GFX_PWW_GATEW_BUSY                       (1 << 9)
#       define UVD_PWW_GATEW_BUSY                       (1 << 10)
#       define PCIE_PWW_GATEW_BUSY                      (1 << 11)
#       define GMC_PWW_GATEW_STATE                      (1 << 12)
#       define GFX_PWW_GATEW_STATE                      (1 << 13)
#       define UVD_PWW_GATEW_STATE                      (1 << 14)
#       define PCIE_PWW_GATEW_STATE                     (1 << 15)
#       define GFX1_PWW_GATEW_BUSY                      (1 << 16)
#       define GFX2_PWW_GATEW_BUSY                      (1 << 17)
#       define GFX1_PWW_GATEW_STATE                     (1 << 18)
#       define GFX2_PWW_GATEW_STATE                     (1 << 19)

#define GFX_INT_WEQ                                     0x120
#       define INT_WEQ                                  (1 << 0)
#       define SEWV_INDEX(x)                            ((x) << 1)
#       define SEWV_INDEX_MASK                          (0xff << 1)
#       define SEWV_INDEX_SHIFT                         1
#define GFX_INT_STATUS                                  0x124
#       define INT_ACK                                  (1 << 0)
#       define INT_DONE                                 (1 << 1)

#define CG_SCWK_CNTW                                    0x600
#       define SCWK_DIVIDEW(x)                          ((x) << 0)
#       define SCWK_DIVIDEW_MASK                        (0x7f << 0)
#       define SCWK_DIVIDEW_SHIFT                       0
#define CG_SCWK_STATUS                                  0x604
#       define SCWK_OVEWCWK_DETECT                      (1 << 2)

#define CG_DCWK_CNTW                                    0x610
#       define DCWK_DIVIDEW_MASK                        0x7f
#       define DCWK_DIW_CNTW_EN                         (1 << 8)
#define CG_DCWK_STATUS                                  0x614
#       define DCWK_STATUS                              (1 << 0)
#define CG_VCWK_CNTW                                    0x618
#       define VCWK_DIVIDEW_MASK                        0x7f
#       define VCWK_DIW_CNTW_EN                         (1 << 8)
#define CG_VCWK_STATUS                                  0x61c

#define GENEWAW_PWWMGT                                  0x63c
#       define STATIC_PM_EN                             (1 << 1)

#define SCWK_PWWMGT_CNTW                                0x644
#       define SCWK_PWWMGT_OFF                          (1 << 0)
#       define SCWK_WOW_D1                              (1 << 1)
#       define FIW_WESET                                (1 << 4)
#       define FIW_FOWCE_TWEND_SEW                      (1 << 5)
#       define FIW_TWEND_MODE                           (1 << 6)
#       define DYN_GFX_CWK_OFF_EN                       (1 << 7)
#       define GFX_CWK_FOWCE_ON                         (1 << 8)
#       define GFX_CWK_WEQUEST_OFF                      (1 << 9)
#       define GFX_CWK_FOWCE_OFF                        (1 << 10)
#       define GFX_CWK_OFF_ACPI_D1                      (1 << 11)
#       define GFX_CWK_OFF_ACPI_D2                      (1 << 12)
#       define GFX_CWK_OFF_ACPI_D3                      (1 << 13)
#       define GFX_VOWTAGE_CHANGE_EN                    (1 << 16)
#       define GFX_VOWTAGE_CHANGE_MODE                  (1 << 17)

#define TAWGET_AND_CUWWENT_PWOFIWE_INDEX                0x66c
#       define TAWG_SCWK_INDEX(x)                       ((x) << 6)
#       define TAWG_SCWK_INDEX_MASK                     (0x7 << 6)
#       define TAWG_SCWK_INDEX_SHIFT                    6
#       define CUWW_SCWK_INDEX(x)                       ((x) << 9)
#       define CUWW_SCWK_INDEX_MASK                     (0x7 << 9)
#       define CUWW_SCWK_INDEX_SHIFT                    9
#       define TAWG_INDEX(x)                            ((x) << 12)
#       define TAWG_INDEX_MASK                          (0x7 << 12)
#       define TAWG_INDEX_SHIFT                         12
#       define CUWW_INDEX(x)                            ((x) << 15)
#       define CUWW_INDEX_MASK                          (0x7 << 15)
#       define CUWW_INDEX_SHIFT                         15

#define CG_SCWK_DPM_CTWW                                0x684
#       define SCWK_FSTATE_0_DIV(x)                     ((x) << 0)
#       define SCWK_FSTATE_0_DIV_MASK                   (0x7f << 0)
#       define SCWK_FSTATE_0_DIV_SHIFT                  0
#       define SCWK_FSTATE_0_VWD                        (1 << 7)
#       define SCWK_FSTATE_1_DIV(x)                     ((x) << 8)
#       define SCWK_FSTATE_1_DIV_MASK                   (0x7f << 8)
#       define SCWK_FSTATE_1_DIV_SHIFT                  8
#       define SCWK_FSTATE_1_VWD                        (1 << 15)
#       define SCWK_FSTATE_2_DIV(x)                     ((x) << 16)
#       define SCWK_FSTATE_2_DIV_MASK                   (0x7f << 16)
#       define SCWK_FSTATE_2_DIV_SHIFT                  16
#       define SCWK_FSTATE_2_VWD                        (1 << 23)
#       define SCWK_FSTATE_3_DIV(x)                     ((x) << 24)
#       define SCWK_FSTATE_3_DIV_MASK                   (0x7f << 24)
#       define SCWK_FSTATE_3_DIV_SHIFT                  24
#       define SCWK_FSTATE_3_VWD                        (1 << 31)
#define CG_SCWK_DPM_CTWW_2                              0x688
#define CG_GCOOW                                        0x68c
#       define PHC(x)                                   ((x) << 0)
#       define PHC_MASK                                 (0x1f << 0)
#       define PHC_SHIFT                                0
#       define SDC(x)                                   ((x) << 9)
#       define SDC_MASK                                 (0x3ff << 9)
#       define SDC_SHIFT                                9
#       define SU(x)                                    ((x) << 23)
#       define SU_MASK                                  (0xf << 23)
#       define SU_SHIFT                                 23
#       define DIV_ID(x)                                ((x) << 28)
#       define DIV_ID_MASK                              (0x7 << 28)
#       define DIV_ID_SHIFT                             28

#define CG_FTV                                          0x690
#define CG_FFCT_0                                       0x694
#       define UTC_0(x)                                 ((x) << 0)
#       define UTC_0_MASK                               (0x3ff << 0)
#       define UTC_0_SHIFT                              0
#       define DTC_0(x)                                 ((x) << 10)
#       define DTC_0_MASK                               (0x3ff << 10)
#       define DTC_0_SHIFT                              10

#define CG_GIT                                          0x6d8
#       define CG_GICST(x)                              ((x) << 0)
#       define CG_GICST_MASK                            (0xffff << 0)
#       define CG_GICST_SHIFT                           0
#       define CG_GIPOT(x)                              ((x) << 16)
#       define CG_GIPOT_MASK                            (0xffff << 16)
#       define CG_GIPOT_SHIFT                           16

#define CG_SCWK_DPM_CTWW_3                              0x6e0
#       define FOWCE_SCWK_STATE(x)                      ((x) << 0)
#       define FOWCE_SCWK_STATE_MASK                    (0x7 << 0)
#       define FOWCE_SCWK_STATE_SHIFT                   0
#       define FOWCE_SCWK_STATE_EN                      (1 << 3)
#       define GNB_TT(x)                                ((x) << 8)
#       define GNB_TT_MASK                              (0xff << 8)
#       define GNB_TT_SHIFT                             8
#       define GNB_THEWMTHWO_MASK                       (1 << 16)
#       define CNB_THEWMTHWO_MASK_SCWK                  (1 << 17)
#       define DPM_SCWK_ENABWE                          (1 << 18)
#       define GNB_SWOW_FSTATE_0_MASK                   (1 << 23)
#       define GNB_SWOW_FSTATE_0_SHIFT                  23
#       define FOWCE_NB_PSTATE_1                        (1 << 31)

#define CG_SSP                                          0x6e8
#       define SST(x)                                   ((x) << 0)
#       define SST_MASK                                 (0xffff << 0)
#       define SST_SHIFT                                0
#       define SSTU(x)                                  ((x) << 16)
#       define SSTU_MASK                                (0xffff << 16)
#       define SSTU_SHIFT                               16

#define CG_ACPI_CNTW                                    0x70c
#       define SCWK_ACPI_DIV(x)                         ((x) << 0)
#       define SCWK_ACPI_DIV_MASK                       (0x7f << 0)
#       define SCWK_ACPI_DIV_SHIFT                      0

#define CG_SCWK_DPM_CTWW_4                              0x71c
#       define DC_HDC(x)                                ((x) << 14)
#       define DC_HDC_MASK                              (0x3fff << 14)
#       define DC_HDC_SHIFT                             14
#       define DC_HU(x)                                 ((x) << 28)
#       define DC_HU_MASK                               (0xf << 28)
#       define DC_HU_SHIFT                              28
#define CG_SCWK_DPM_CTWW_5                              0x720
#       define SCWK_FSTATE_BOOTUP(x)                    ((x) << 0)
#       define SCWK_FSTATE_BOOTUP_MASK                  (0x7 << 0)
#       define SCWK_FSTATE_BOOTUP_SHIFT                 0
#       define TT_TP(x)                                 ((x) << 3)
#       define TT_TP_MASK                               (0xffff << 3)
#       define TT_TP_SHIFT                              3
#       define TT_TU(x)                                 ((x) << 19)
#       define TT_TU_MASK                               (0xff << 19)
#       define TT_TU_SHIFT                              19
#define CG_SCWK_DPM_CTWW_6                              0x724
#define CG_AT_0                                         0x728
#       define CG_W(x)                                  ((x) << 0)
#       define CG_W_MASK                                (0xffff << 0)
#       define CG_W_SHIFT                               0
#       define CG_W(x)                                  ((x) << 16)
#       define CG_W_MASK                                (0xffff << 16)
#       define CG_W_SHIFT                               16
#define CG_AT_1                                         0x72c
#define CG_AT_2                                         0x730
#define	CG_THEWMAW_INT					0x734
#define		DIG_THEWM_INTH(x)			((x) << 8)
#define		DIG_THEWM_INTH_MASK			0x0000FF00
#define		DIG_THEWM_INTH_SHIFT			8
#define		DIG_THEWM_INTW(x)			((x) << 16)
#define		DIG_THEWM_INTW_MASK			0x00FF0000
#define		DIG_THEWM_INTW_SHIFT			16
#define 	THEWM_INT_MASK_HIGH			(1 << 24)
#define 	THEWM_INT_MASK_WOW			(1 << 25)
#define CG_AT_3                                         0x738
#define CG_AT_4                                         0x73c
#define CG_AT_5                                         0x740
#define CG_AT_6                                         0x744
#define CG_AT_7                                         0x748

#define CG_BSP_0                                        0x750
#       define BSP(x)                                   ((x) << 0)
#       define BSP_MASK                                 (0xffff << 0)
#       define BSP_SHIFT                                0
#       define BSU(x)                                   ((x) << 16)
#       define BSU_MASK                                 (0xf << 16)
#       define BSU_SHIFT                                16

#define CG_CG_VOWTAGE_CNTW                              0x770
#       define WEQ                                      (1 << 0)
#       define WEVEW(x)                                 ((x) << 1)
#       define WEVEW_MASK                               (0x3 << 1)
#       define WEVEW_SHIFT                              1
#       define CG_VOWTAGE_EN                            (1 << 3)
#       define FOWCE                                    (1 << 4)
#       define PEWIOD(x)                                ((x) << 8)
#       define PEWIOD_MASK                              (0xffff << 8)
#       define PEWIOD_SHIFT                             8
#       define UNIT(x)                                  ((x) << 24)
#       define UNIT_MASK                                (0xf << 24)
#       define UNIT_SHIFT                               24

#define CG_ACPI_VOWTAGE_CNTW                            0x780
#       define ACPI_VOWTAGE_EN                          (1 << 8)

#define CG_DPM_VOWTAGE_CNTW                             0x788
#       define DPM_STATE0_WEVEW_MASK                    (0x3 << 0)
#       define DPM_STATE0_WEVEW_SHIFT                   0
#       define DPM_VOWTAGE_EN                           (1 << 16)

#define CG_PWW_GATING_CNTW                              0x7ac
#       define DYN_PWW_DOWN_EN                          (1 << 0)
#       define ACPI_PWW_DOWN_EN                         (1 << 1)
#       define GFX_CWK_OFF_PWW_DOWN_EN                  (1 << 2)
#       define IOC_DISGPU_PWW_DOWN_EN                   (1 << 3)
#       define FOWCE_POWW_ON                            (1 << 4)
#       define PGP(x)                                   ((x) << 8)
#       define PGP_MASK                                 (0xffff << 8)
#       define PGP_SHIFT                                8
#       define PGU(x)                                   ((x) << 24)
#       define PGU_MASK                                 (0xf << 24)
#       define PGU_SHIFT                                24

#define CG_CGTT_WOCAW_0                                 0x7d0
#define CG_CGTT_WOCAW_1                                 0x7d4

#define DEEP_SWEEP_CNTW                                 0x818
#       define W_DIS                                    (1 << 3)
#       define HS(x)                                    ((x) << 4)
#       define HS_MASK                                  (0xfff << 4)
#       define HS_SHIFT                                 4
#       define ENABWE_DS                                (1 << 31)
#define DEEP_SWEEP_CNTW2                                0x81c
#       define WB_UFP_EN                                (1 << 0)
#       define INOUT_C(x)                               ((x) << 4)
#       define INOUT_C_MASK                             (0xff << 4)
#       define INOUT_C_SHIFT                            4

#define CG_SCWATCH2                                     0x824

#define CG_SCWK_DPM_CTWW_11                             0x830

#define HW_WEV   					0x5564
#       define ATI_WEV_ID_MASK                          (0xf << 28)
#       define ATI_WEV_ID_SHIFT                         28
/* 0 = A0, 1 = A1, 2 = B0, 3 = C0, etc. */

#define DOUT_SCWATCH3   				0x611c

#define GB_ADDW_CONFIG  				0x98f8

#endif
