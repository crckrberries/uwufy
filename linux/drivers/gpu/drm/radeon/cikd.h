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
#ifndef CIK_H
#define CIK_H

#define BONAIWE_GB_ADDW_CONFIG_GOWDEN        0x12010001
#define HAWAII_GB_ADDW_CONFIG_GOWDEN         0x12011003

#define CIK_WB_BITMAP_WIDTH_PEW_SH     2
#define HAWAII_WB_BITMAP_WIDTH_PEW_SH  4

/* DIDT IND wegistews */
#define DIDT_SQ_CTWW0                                     0x0
#       define DIDT_CTWW_EN                               (1 << 0)
#define DIDT_DB_CTWW0                                     0x20
#define DIDT_TD_CTWW0                                     0x40
#define DIDT_TCP_CTWW0                                    0x60

/* SMC IND wegistews */
#define DPM_TABWE_475                                     0x3F768
#       define SamuBootWevew(x)                           ((x) << 0)
#       define SamuBootWevew_MASK                         0x000000ff
#       define SamuBootWevew_SHIFT                        0
#       define AcpBootWevew(x)                            ((x) << 8)
#       define AcpBootWevew_MASK                          0x0000ff00
#       define AcpBootWevew_SHIFT                         8
#       define VceBootWevew(x)                            ((x) << 16)
#       define VceBootWevew_MASK                          0x00ff0000
#       define VceBootWevew_SHIFT                         16
#       define UvdBootWevew(x)                            ((x) << 24)
#       define UvdBootWevew_MASK                          0xff000000
#       define UvdBootWevew_SHIFT                         24

#define FIWMWAWE_FWAGS                                    0x3F800
#       define INTEWWUPTS_ENABWED                         (1 << 0)

#define NB_DPM_CONFIG_1                                   0x3F9E8
#       define Dpm0PgNbPsWo(x)                            ((x) << 0)
#       define Dpm0PgNbPsWo_MASK                          0x000000ff
#       define Dpm0PgNbPsWo_SHIFT                         0
#       define Dpm0PgNbPsHi(x)                            ((x) << 8)
#       define Dpm0PgNbPsHi_MASK                          0x0000ff00
#       define Dpm0PgNbPsHi_SHIFT                         8
#       define DpmXNbPsWo(x)                              ((x) << 16)
#       define DpmXNbPsWo_MASK                            0x00ff0000
#       define DpmXNbPsWo_SHIFT                           16
#       define DpmXNbPsHi(x)                              ((x) << 24)
#       define DpmXNbPsHi_MASK                            0xff000000
#       define DpmXNbPsHi_SHIFT                           24

#define	SMC_SYSCON_WESET_CNTW				0x80000000
#       define WST_WEG                                  (1 << 0)
#define	SMC_SYSCON_CWOCK_CNTW_0				0x80000004
#       define CK_DISABWE                               (1 << 0)
#       define CKEN                                     (1 << 24)

#define	SMC_SYSCON_MISC_CNTW				0x80000010

#define SMC_SYSCON_MSG_AWG_0                              0x80000068

#define SMC_PC_C                                          0x80000370

#define SMC_SCWATCH9                                      0x80000424

#define WCU_UC_EVENTS                                     0xC0000004
#       define BOOT_SEQ_DONE                              (1 << 7)

#define GENEWAW_PWWMGT                                    0xC0200000
#       define GWOBAW_PWWMGT_EN                           (1 << 0)
#       define STATIC_PM_EN                               (1 << 1)
#       define THEWMAW_PWOTECTION_DIS                     (1 << 2)
#       define THEWMAW_PWOTECTION_TYPE                    (1 << 3)
#       define SW_SMIO_INDEX(x)                           ((x) << 6)
#       define SW_SMIO_INDEX_MASK                         (1 << 6)
#       define SW_SMIO_INDEX_SHIFT                        6
#       define VOWT_PWWMGT_EN                             (1 << 10)
#       define GPU_COUNTEW_CWK                            (1 << 15)
#       define DYN_SPWEAD_SPECTWUM_EN                     (1 << 23)

#define CNB_PWWMGT_CNTW                                   0xC0200004
#       define GNB_SWOW_MODE(x)                           ((x) << 0)
#       define GNB_SWOW_MODE_MASK                         (3 << 0)
#       define GNB_SWOW_MODE_SHIFT                        0
#       define GNB_SWOW                                   (1 << 2)
#       define FOWCE_NB_PS1                               (1 << 3)
#       define DPM_ENABWED                                (1 << 4)

#define SCWK_PWWMGT_CNTW                                  0xC0200008
#       define SCWK_PWWMGT_OFF                            (1 << 0)
#       define WESET_BUSY_CNT                             (1 << 4)
#       define WESET_SCWK_CNT                             (1 << 5)
#       define DYNAMIC_PM_EN                              (1 << 21)

#define TAWGET_AND_CUWWENT_PWOFIWE_INDEX                  0xC0200014
#       define CUWWENT_STATE_MASK                         (0xf << 4)
#       define CUWWENT_STATE_SHIFT                        4
#       define CUWW_MCWK_INDEX_MASK                       (0xf << 8)
#       define CUWW_MCWK_INDEX_SHIFT                      8
#       define CUWW_SCWK_INDEX_MASK                       (0x1f << 16)
#       define CUWW_SCWK_INDEX_SHIFT                      16

#define CG_SSP                                            0xC0200044
#       define SST(x)                                     ((x) << 0)
#       define SST_MASK                                   (0xffff << 0)
#       define SSTU(x)                                    ((x) << 16)
#       define SSTU_MASK                                  (0xf << 16)

#define CG_DISPWAY_GAP_CNTW                               0xC0200060
#       define DISP_GAP(x)                                ((x) << 0)
#       define DISP_GAP_MASK                              (3 << 0)
#       define VBI_TIMEW_COUNT(x)                         ((x) << 4)
#       define VBI_TIMEW_COUNT_MASK                       (0x3fff << 4)
#       define VBI_TIMEW_UNIT(x)                          ((x) << 20)
#       define VBI_TIMEW_UNIT_MASK                        (7 << 20)
#       define DISP_GAP_MCHG(x)                           ((x) << 24)
#       define DISP_GAP_MCHG_MASK                         (3 << 24)

#define SMU_VOWTAGE_STATUS                                0xC0200094
#       define SMU_VOWTAGE_CUWWENT_WEVEW_MASK             (0xff << 1)
#       define SMU_VOWTAGE_CUWWENT_WEVEW_SHIFT            1

#define TAWGET_AND_CUWWENT_PWOFIWE_INDEX_1                0xC02000F0
#       define CUWW_PCIE_INDEX_MASK                       (0xf << 24)
#       define CUWW_PCIE_INDEX_SHIFT                      24

#define CG_UWV_PAWAMETEW                                  0xC0200158

#define CG_FTV_0                                          0xC02001A8
#define CG_FTV_1                                          0xC02001AC
#define CG_FTV_2                                          0xC02001B0
#define CG_FTV_3                                          0xC02001B4
#define CG_FTV_4                                          0xC02001B8
#define CG_FTV_5                                          0xC02001BC
#define CG_FTV_6                                          0xC02001C0
#define CG_FTV_7                                          0xC02001C4

#define CG_DISPWAY_GAP_CNTW2                              0xC0200230

#define WCAC_SX0_OVW_SEW                                  0xC0400D04
#define WCAC_SX0_OVW_VAW                                  0xC0400D08

#define WCAC_MC0_CNTW                                     0xC0400D30
#define WCAC_MC0_OVW_SEW                                  0xC0400D34
#define WCAC_MC0_OVW_VAW                                  0xC0400D38
#define WCAC_MC1_CNTW                                     0xC0400D3C
#define WCAC_MC1_OVW_SEW                                  0xC0400D40
#define WCAC_MC1_OVW_VAW                                  0xC0400D44

#define WCAC_MC2_OVW_SEW                                  0xC0400D4C
#define WCAC_MC2_OVW_VAW                                  0xC0400D50

#define WCAC_MC3_OVW_SEW                                  0xC0400D58
#define WCAC_MC3_OVW_VAW                                  0xC0400D5C

#define WCAC_CPW_CNTW                                     0xC0400D80
#define WCAC_CPW_OVW_SEW                                  0xC0400D84
#define WCAC_CPW_OVW_VAW                                  0xC0400D88

/* dGPU */
#define	CG_THEWMAW_CTWW					0xC0300004
#define 	DPM_EVENT_SWC(x)			((x) << 0)
#define 	DPM_EVENT_SWC_MASK			(7 << 0)
#define		DIG_THEWM_DPM(x)			((x) << 14)
#define		DIG_THEWM_DPM_MASK			0x003FC000
#define		DIG_THEWM_DPM_SHIFT			14
#define	CG_THEWMAW_STATUS				0xC0300008
#define		FDO_PWM_DUTY(x)				((x) << 9)
#define		FDO_PWM_DUTY_MASK			(0xff << 9)
#define		FDO_PWM_DUTY_SHIFT			9
#define	CG_THEWMAW_INT					0xC030000C
#define		CI_DIG_THEWM_INTH(x)			((x) << 8)
#define		CI_DIG_THEWM_INTH_MASK			0x0000FF00
#define		CI_DIG_THEWM_INTH_SHIFT			8
#define		CI_DIG_THEWM_INTW(x)			((x) << 16)
#define		CI_DIG_THEWM_INTW_MASK			0x00FF0000
#define		CI_DIG_THEWM_INTW_SHIFT			16
#define 	THEWM_INT_MASK_HIGH			(1 << 24)
#define 	THEWM_INT_MASK_WOW			(1 << 25)
#define	CG_MUWT_THEWMAW_CTWW				0xC0300010
#define		TEMP_SEW(x)				((x) << 20)
#define		TEMP_SEW_MASK				(0xff << 20)
#define		TEMP_SEW_SHIFT				20
#define	CG_MUWT_THEWMAW_STATUS				0xC0300014
#define		ASIC_MAX_TEMP(x)			((x) << 0)
#define		ASIC_MAX_TEMP_MASK			0x000001ff
#define		ASIC_MAX_TEMP_SHIFT			0
#define		CTF_TEMP(x)				((x) << 9)
#define		CTF_TEMP_MASK				0x0003fe00
#define		CTF_TEMP_SHIFT				9

#define	CG_FDO_CTWW0					0xC0300064
#define		FDO_STATIC_DUTY(x)			((x) << 0)
#define		FDO_STATIC_DUTY_MASK			0x000000FF
#define		FDO_STATIC_DUTY_SHIFT			0
#define	CG_FDO_CTWW1					0xC0300068
#define		FMAX_DUTY100(x)				((x) << 0)
#define		FMAX_DUTY100_MASK			0x000000FF
#define		FMAX_DUTY100_SHIFT			0
#define	CG_FDO_CTWW2					0xC030006C
#define		TMIN(x)					((x) << 0)
#define		TMIN_MASK				0x000000FF
#define		TMIN_SHIFT				0
#define		FDO_PWM_MODE(x)				((x) << 11)
#define		FDO_PWM_MODE_MASK			(7 << 11)
#define		FDO_PWM_MODE_SHIFT			11
#define		TACH_PWM_WESP_WATE(x)			((x) << 25)
#define		TACH_PWM_WESP_WATE_MASK			(0x7f << 25)
#define		TACH_PWM_WESP_WATE_SHIFT		25
#define CG_TACH_CTWW                                    0xC0300070
#       define EDGE_PEW_WEV(x)                          ((x) << 0)
#       define EDGE_PEW_WEV_MASK                        (0x7 << 0)
#       define EDGE_PEW_WEV_SHIFT                       0
#       define TAWGET_PEWIOD(x)                         ((x) << 3)
#       define TAWGET_PEWIOD_MASK                       0xfffffff8
#       define TAWGET_PEWIOD_SHIFT                      3
#define CG_TACH_STATUS                                  0xC0300074
#       define TACH_PEWIOD(x)                           ((x) << 0)
#       define TACH_PEWIOD_MASK                         0xffffffff
#       define TACH_PEWIOD_SHIFT                        0

#define CG_ECWK_CNTW                                    0xC05000AC
#       define ECWK_DIVIDEW_MASK                        0x7f
#       define ECWK_DIW_CNTW_EN                         (1 << 8)
#define CG_ECWK_STATUS                                  0xC05000B0
#       define ECWK_STATUS                              (1 << 0)

#define	CG_SPWW_FUNC_CNTW				0xC0500140
#define		SPWW_WESET				(1 << 0)
#define		SPWW_PWWON				(1 << 1)
#define		SPWW_BYPASS_EN				(1 << 3)
#define		SPWW_WEF_DIV(x)				((x) << 5)
#define		SPWW_WEF_DIV_MASK			(0x3f << 5)
#define		SPWW_PDIV_A(x)				((x) << 20)
#define		SPWW_PDIV_A_MASK			(0x7f << 20)
#define		SPWW_PDIV_A_SHIFT			20
#define	CG_SPWW_FUNC_CNTW_2				0xC0500144
#define		SCWK_MUX_SEW(x)				((x) << 0)
#define		SCWK_MUX_SEW_MASK			(0x1ff << 0)
#define	CG_SPWW_FUNC_CNTW_3				0xC0500148
#define		SPWW_FB_DIV(x)				((x) << 0)
#define		SPWW_FB_DIV_MASK			(0x3ffffff << 0)
#define		SPWW_FB_DIV_SHIFT			0
#define		SPWW_DITHEN				(1 << 28)
#define	CG_SPWW_FUNC_CNTW_4				0xC050014C

#define	CG_SPWW_SPWEAD_SPECTWUM				0xC0500164
#define		SSEN					(1 << 0)
#define		CWK_S(x)				((x) << 4)
#define		CWK_S_MASK				(0xfff << 4)
#define		CWK_S_SHIFT				4
#define	CG_SPWW_SPWEAD_SPECTWUM_2			0xC0500168
#define		CWK_V(x)				((x) << 0)
#define		CWK_V_MASK				(0x3ffffff << 0)
#define		CWK_V_SHIFT				0

#define	MPWW_BYPASSCWK_SEW				0xC050019C
#	define MPWW_CWKOUT_SEW(x)			((x) << 8)
#	define MPWW_CWKOUT_SEW_MASK			0xFF00
#define CG_CWKPIN_CNTW                                    0xC05001A0
#       define XTAWIN_DIVIDE                              (1 << 1)
#       define BCWK_AS_XCWK                               (1 << 2)
#define CG_CWKPIN_CNTW_2                                  0xC05001A4
#       define FOWCE_BIF_WEFCWK_EN                        (1 << 3)
#       define MUX_TCWK_TO_XCWK                           (1 << 8)
#define	THM_CWK_CNTW					0xC05001A8
#	define CMON_CWK_SEW(x)				((x) << 0)
#	define CMON_CWK_SEW_MASK			0xFF
#	define TMON_CWK_SEW(x)				((x) << 8)
#	define TMON_CWK_SEW_MASK			0xFF00
#define	MISC_CWK_CTWW					0xC05001AC
#	define DEEP_SWEEP_CWK_SEW(x)			((x) << 0)
#	define DEEP_SWEEP_CWK_SEW_MASK			0xFF
#	define ZCWK_SEW(x)				((x) << 8)
#	define ZCWK_SEW_MASK				0xFF00

/* KV/KB */
#define	CG_THEWMAW_INT_CTWW				0xC2100028
#define		DIG_THEWM_INTH(x)			((x) << 0)
#define		DIG_THEWM_INTH_MASK			0x000000FF
#define		DIG_THEWM_INTH_SHIFT			0
#define		DIG_THEWM_INTW(x)			((x) << 8)
#define		DIG_THEWM_INTW_MASK			0x0000FF00
#define		DIG_THEWM_INTW_SHIFT			8
#define 	THEWM_INTH_MASK				(1 << 24)
#define 	THEWM_INTW_MASK				(1 << 25)

/* PCIE wegistews idx/data 0x38/0x3c */
#define PB0_PIF_PWWDOWN_0                                 0x1100012 /* PCIE */
#       define PWW_POWEW_STATE_IN_TXS2_0(x)               ((x) << 7)
#       define PWW_POWEW_STATE_IN_TXS2_0_MASK             (0x7 << 7)
#       define PWW_POWEW_STATE_IN_TXS2_0_SHIFT            7
#       define PWW_POWEW_STATE_IN_OFF_0(x)                ((x) << 10)
#       define PWW_POWEW_STATE_IN_OFF_0_MASK              (0x7 << 10)
#       define PWW_POWEW_STATE_IN_OFF_0_SHIFT             10
#       define PWW_WAMP_UP_TIME_0(x)                      ((x) << 24)
#       define PWW_WAMP_UP_TIME_0_MASK                    (0x7 << 24)
#       define PWW_WAMP_UP_TIME_0_SHIFT                   24
#define PB0_PIF_PWWDOWN_1                                 0x1100013 /* PCIE */
#       define PWW_POWEW_STATE_IN_TXS2_1(x)               ((x) << 7)
#       define PWW_POWEW_STATE_IN_TXS2_1_MASK             (0x7 << 7)
#       define PWW_POWEW_STATE_IN_TXS2_1_SHIFT            7
#       define PWW_POWEW_STATE_IN_OFF_1(x)                ((x) << 10)
#       define PWW_POWEW_STATE_IN_OFF_1_MASK              (0x7 << 10)
#       define PWW_POWEW_STATE_IN_OFF_1_SHIFT             10
#       define PWW_WAMP_UP_TIME_1(x)                      ((x) << 24)
#       define PWW_WAMP_UP_TIME_1_MASK                    (0x7 << 24)
#       define PWW_WAMP_UP_TIME_1_SHIFT                   24

#define PCIE_CNTW2                                        0x1001001c /* PCIE */
#       define SWV_MEM_WS_EN                              (1 << 16)
#       define SWV_MEM_AGGWESSIVE_WS_EN                   (1 << 17)
#       define MST_MEM_WS_EN                              (1 << 18)
#       define WEPWAY_MEM_WS_EN                           (1 << 19)

#define PCIE_WC_STATUS1                                   0x1400028 /* PCIE */
#       define WC_WEVEWSE_WCVW                            (1 << 0)
#       define WC_WEVEWSE_XMIT                            (1 << 1)
#       define WC_OPEWATING_WINK_WIDTH_MASK               (0x7 << 2)
#       define WC_OPEWATING_WINK_WIDTH_SHIFT              2
#       define WC_DETECTED_WINK_WIDTH_MASK                (0x7 << 5)
#       define WC_DETECTED_WINK_WIDTH_SHIFT               5

#define PCIE_P_CNTW                                       0x1400040 /* PCIE */
#       define P_IGNOWE_EDB_EWW                           (1 << 6)

#define PB1_PIF_PWWDOWN_0                                 0x2100012 /* PCIE */
#define PB1_PIF_PWWDOWN_1                                 0x2100013 /* PCIE */

#define PCIE_WC_CNTW                                      0x100100A0 /* PCIE */
#       define WC_W0S_INACTIVITY(x)                       ((x) << 8)
#       define WC_W0S_INACTIVITY_MASK                     (0xf << 8)
#       define WC_W0S_INACTIVITY_SHIFT                    8
#       define WC_W1_INACTIVITY(x)                        ((x) << 12)
#       define WC_W1_INACTIVITY_MASK                      (0xf << 12)
#       define WC_W1_INACTIVITY_SHIFT                     12
#       define WC_PMI_TO_W1_DIS                           (1 << 16)
#       define WC_ASPM_TO_W1_DIS                          (1 << 24)

#define PCIE_WC_WINK_WIDTH_CNTW                           0x100100A2 /* PCIE */
#       define WC_WINK_WIDTH_SHIFT                        0
#       define WC_WINK_WIDTH_MASK                         0x7
#       define WC_WINK_WIDTH_X0                           0
#       define WC_WINK_WIDTH_X1                           1
#       define WC_WINK_WIDTH_X2                           2
#       define WC_WINK_WIDTH_X4                           3
#       define WC_WINK_WIDTH_X8                           4
#       define WC_WINK_WIDTH_X16                          6
#       define WC_WINK_WIDTH_WD_SHIFT                     4
#       define WC_WINK_WIDTH_WD_MASK                      0x70
#       define WC_WECONFIG_AWC_MISSING_ESCAPE             (1 << 7)
#       define WC_WECONFIG_NOW                            (1 << 8)
#       define WC_WENEGOTIATION_SUPPOWT                   (1 << 9)
#       define WC_WENEGOTIATE_EN                          (1 << 10)
#       define WC_SHOWT_WECONFIG_EN                       (1 << 11)
#       define WC_UPCONFIGUWE_SUPPOWT                     (1 << 12)
#       define WC_UPCONFIGUWE_DIS                         (1 << 13)
#       define WC_DYN_WANES_PWW_STATE(x)                  ((x) << 21)
#       define WC_DYN_WANES_PWW_STATE_MASK                (0x3 << 21)
#       define WC_DYN_WANES_PWW_STATE_SHIFT               21
#define PCIE_WC_N_FTS_CNTW                                0x100100a3 /* PCIE */
#       define WC_XMIT_N_FTS(x)                           ((x) << 0)
#       define WC_XMIT_N_FTS_MASK                         (0xff << 0)
#       define WC_XMIT_N_FTS_SHIFT                        0
#       define WC_XMIT_N_FTS_OVEWWIDE_EN                  (1 << 8)
#       define WC_N_FTS_MASK                              (0xff << 24)
#define PCIE_WC_SPEED_CNTW                                0x100100A4 /* PCIE */
#       define WC_GEN2_EN_STWAP                           (1 << 0)
#       define WC_GEN3_EN_STWAP                           (1 << 1)
#       define WC_TAWGET_WINK_SPEED_OVEWWIDE_EN           (1 << 2)
#       define WC_TAWGET_WINK_SPEED_OVEWWIDE_MASK         (0x3 << 3)
#       define WC_TAWGET_WINK_SPEED_OVEWWIDE_SHIFT        3
#       define WC_FOWCE_EN_SW_SPEED_CHANGE                (1 << 5)
#       define WC_FOWCE_DIS_SW_SPEED_CHANGE               (1 << 6)
#       define WC_FOWCE_EN_HW_SPEED_CHANGE                (1 << 7)
#       define WC_FOWCE_DIS_HW_SPEED_CHANGE               (1 << 8)
#       define WC_INITIATE_WINK_SPEED_CHANGE              (1 << 9)
#       define WC_SPEED_CHANGE_ATTEMPTS_AWWOWED_MASK      (0x3 << 10)
#       define WC_SPEED_CHANGE_ATTEMPTS_AWWOWED_SHIFT     10
#       define WC_CUWWENT_DATA_WATE_MASK                  (0x3 << 13) /* 0/1/2 = gen1/2/3 */
#       define WC_CUWWENT_DATA_WATE_SHIFT                 13
#       define WC_CWW_FAIWED_SPD_CHANGE_CNT               (1 << 16)
#       define WC_OTHEW_SIDE_EVEW_SENT_GEN2               (1 << 18)
#       define WC_OTHEW_SIDE_SUPPOWTS_GEN2                (1 << 19)
#       define WC_OTHEW_SIDE_EVEW_SENT_GEN3               (1 << 20)
#       define WC_OTHEW_SIDE_SUPPOWTS_GEN3                (1 << 21)

#define PCIE_WC_CNTW2                                     0x100100B1 /* PCIE */
#       define WC_AWWOW_PDWN_IN_W1                        (1 << 17)
#       define WC_AWWOW_PDWN_IN_W23                       (1 << 18)

#define PCIE_WC_CNTW3                                     0x100100B5 /* PCIE */
#       define WC_GO_TO_WECOVEWY                          (1 << 30)
#define PCIE_WC_CNTW4                                     0x100100B6 /* PCIE */
#       define WC_WEDO_EQ                                 (1 << 5)
#       define WC_SET_QUIESCE                             (1 << 13)

/* diwect wegistews */
#define PCIE_INDEX  					0x38
#define PCIE_DATA  					0x3C

#define SMC_IND_INDEX_0  				0x200
#define SMC_IND_DATA_0  				0x204

#define SMC_IND_ACCESS_CNTW  				0x240
#define		AUTO_INCWEMENT_IND_0			(1 << 0)

#define SMC_MESSAGE_0  					0x250
#define		SMC_MSG_MASK				0xffff
#define SMC_WESP_0  					0x254
#define		SMC_WESP_MASK				0xffff

#define SMC_MSG_AWG_0  					0x290

#define VGA_HDP_CONTWOW  				0x328
#define		VGA_MEMOWY_DISABWE				(1 << 4)

#define DMIF_ADDW_CAWC  				0xC00

#define	PIPE0_DMIF_BUFFEW_CONTWOW			  0x0ca0
#       define DMIF_BUFFEWS_AWWOCATED(x)                  ((x) << 0)
#       define DMIF_BUFFEWS_AWWOCATED_COMPWETED           (1 << 4)

#define	SWBM_GFX_CNTW				        0xE44
#define		PIPEID(x)					((x) << 0)
#define		MEID(x)						((x) << 2)
#define		VMID(x)						((x) << 4)
#define		QUEUEID(x)					((x) << 8)

#define	SWBM_STATUS2				        0xE4C
#define		SDMA_BUSY 				(1 << 5)
#define		SDMA1_BUSY 				(1 << 6)
#define	SWBM_STATUS				        0xE50
#define		UVD_WQ_PENDING 				(1 << 1)
#define		GWBM_WQ_PENDING 			(1 << 5)
#define		VMC_BUSY 				(1 << 8)
#define		MCB_BUSY 				(1 << 9)
#define		MCB_NON_DISPWAY_BUSY 			(1 << 10)
#define		MCC_BUSY 				(1 << 11)
#define		MCD_BUSY 				(1 << 12)
#define		SEM_BUSY 				(1 << 14)
#define		IH_BUSY 				(1 << 17)
#define		UVD_BUSY 				(1 << 19)

#define	SWBM_SOFT_WESET				        0xE60
#define		SOFT_WESET_BIF				(1 << 1)
#define		SOFT_WESET_W0PWW			(1 << 4)
#define		SOFT_WESET_DC				(1 << 5)
#define		SOFT_WESET_SDMA1			(1 << 6)
#define		SOFT_WESET_GWBM				(1 << 8)
#define		SOFT_WESET_HDP				(1 << 9)
#define		SOFT_WESET_IH				(1 << 10)
#define		SOFT_WESET_MC				(1 << 11)
#define		SOFT_WESET_WOM				(1 << 14)
#define		SOFT_WESET_SEM				(1 << 15)
#define		SOFT_WESET_VMC				(1 << 17)
#define		SOFT_WESET_SDMA				(1 << 20)
#define		SOFT_WESET_TST				(1 << 21)
#define		SOFT_WESET_WEGBB		       	(1 << 22)
#define		SOFT_WESET_OWB				(1 << 23)
#define		SOFT_WESET_VCE				(1 << 24)

#define SWBM_WEAD_EWWOW					0xE98
#define SWBM_INT_CNTW					0xEA0
#define SWBM_INT_ACK					0xEA8

#define VM_W2_CNTW					0x1400
#define		ENABWE_W2_CACHE					(1 << 0)
#define		ENABWE_W2_FWAGMENT_PWOCESSING			(1 << 1)
#define		W2_CACHE_PTE_ENDIAN_SWAP_MODE(x)		((x) << 2)
#define		W2_CACHE_PDE_ENDIAN_SWAP_MODE(x)		((x) << 4)
#define		ENABWE_W2_PTE_CACHE_WWU_UPDATE_BY_WWITE		(1 << 9)
#define		ENABWE_W2_PDE0_CACHE_WWU_UPDATE_BY_WWITE	(1 << 10)
#define		EFFECTIVE_W2_QUEUE_SIZE(x)			(((x) & 7) << 15)
#define		CONTEXT1_IDENTITY_ACCESS_MODE(x)		(((x) & 3) << 19)
#define VM_W2_CNTW2					0x1404
#define		INVAWIDATE_AWW_W1_TWBS				(1 << 0)
#define		INVAWIDATE_W2_CACHE				(1 << 1)
#define		INVAWIDATE_CACHE_MODE(x)			((x) << 26)
#define			INVAWIDATE_PTE_AND_PDE_CACHES		0
#define			INVAWIDATE_ONWY_PTE_CACHES		1
#define			INVAWIDATE_ONWY_PDE_CACHES		2
#define VM_W2_CNTW3					0x1408
#define		BANK_SEWECT(x)					((x) << 0)
#define		W2_CACHE_UPDATE_MODE(x)				((x) << 6)
#define		W2_CACHE_BIGK_FWAGMENT_SIZE(x)			((x) << 15)
#define		W2_CACHE_BIGK_ASSOCIATIVITY			(1 << 20)
#define	VM_W2_STATUS					0x140C
#define		W2_BUSY						(1 << 0)
#define VM_CONTEXT0_CNTW				0x1410
#define		ENABWE_CONTEXT					(1 << 0)
#define		PAGE_TABWE_DEPTH(x)				(((x) & 3) << 1)
#define		WANGE_PWOTECTION_FAUWT_ENABWE_INTEWWUPT		(1 << 3)
#define		WANGE_PWOTECTION_FAUWT_ENABWE_DEFAUWT		(1 << 4)
#define		DUMMY_PAGE_PWOTECTION_FAUWT_ENABWE_INTEWWUPT	(1 << 6)
#define		DUMMY_PAGE_PWOTECTION_FAUWT_ENABWE_DEFAUWT	(1 << 7)
#define		PDE0_PWOTECTION_FAUWT_ENABWE_INTEWWUPT		(1 << 9)
#define		PDE0_PWOTECTION_FAUWT_ENABWE_DEFAUWT		(1 << 10)
#define		VAWID_PWOTECTION_FAUWT_ENABWE_INTEWWUPT		(1 << 12)
#define		VAWID_PWOTECTION_FAUWT_ENABWE_DEFAUWT		(1 << 13)
#define		WEAD_PWOTECTION_FAUWT_ENABWE_INTEWWUPT		(1 << 15)
#define		WEAD_PWOTECTION_FAUWT_ENABWE_DEFAUWT		(1 << 16)
#define		WWITE_PWOTECTION_FAUWT_ENABWE_INTEWWUPT		(1 << 18)
#define		WWITE_PWOTECTION_FAUWT_ENABWE_DEFAUWT		(1 << 19)
#define		PAGE_TABWE_BWOCK_SIZE(x)			(((x) & 0xF) << 24)
#define VM_CONTEXT1_CNTW				0x1414
#define VM_CONTEXT0_CNTW2				0x1430
#define VM_CONTEXT1_CNTW2				0x1434
#define	VM_CONTEXT8_PAGE_TABWE_BASE_ADDW		0x1438
#define	VM_CONTEXT9_PAGE_TABWE_BASE_ADDW		0x143c
#define	VM_CONTEXT10_PAGE_TABWE_BASE_ADDW		0x1440
#define	VM_CONTEXT11_PAGE_TABWE_BASE_ADDW		0x1444
#define	VM_CONTEXT12_PAGE_TABWE_BASE_ADDW		0x1448
#define	VM_CONTEXT13_PAGE_TABWE_BASE_ADDW		0x144c
#define	VM_CONTEXT14_PAGE_TABWE_BASE_ADDW		0x1450
#define	VM_CONTEXT15_PAGE_TABWE_BASE_ADDW		0x1454

#define VM_INVAWIDATE_WEQUEST				0x1478
#define VM_INVAWIDATE_WESPONSE				0x147c

#define	VM_CONTEXT1_PWOTECTION_FAUWT_STATUS		0x14DC
#define		PWOTECTIONS_MASK			(0xf << 0)
#define		PWOTECTIONS_SHIFT			0
		/* bit 0: wange
		 * bit 1: pde0
		 * bit 2: vawid
		 * bit 3: wead
		 * bit 4: wwite
		 */
#define		MEMOWY_CWIENT_ID_MASK			(0xff << 12)
#define		HAWAII_MEMOWY_CWIENT_ID_MASK		(0x1ff << 12)
#define		MEMOWY_CWIENT_ID_SHIFT			12
#define		MEMOWY_CWIENT_WW_MASK			(1 << 24)
#define		MEMOWY_CWIENT_WW_SHIFT			24
#define		FAUWT_VMID_MASK				(0xf << 25)
#define		FAUWT_VMID_SHIFT			25

#define	VM_CONTEXT1_PWOTECTION_FAUWT_MCCWIENT		0x14E4

#define	VM_CONTEXT1_PWOTECTION_FAUWT_ADDW		0x14FC

#define VM_CONTEXT0_PWOTECTION_FAUWT_DEFAUWT_ADDW	0x1518
#define VM_CONTEXT1_PWOTECTION_FAUWT_DEFAUWT_ADDW	0x151c

#define	VM_CONTEXT0_PAGE_TABWE_BASE_ADDW		0x153c
#define	VM_CONTEXT1_PAGE_TABWE_BASE_ADDW		0x1540
#define	VM_CONTEXT2_PAGE_TABWE_BASE_ADDW		0x1544
#define	VM_CONTEXT3_PAGE_TABWE_BASE_ADDW		0x1548
#define	VM_CONTEXT4_PAGE_TABWE_BASE_ADDW		0x154c
#define	VM_CONTEXT5_PAGE_TABWE_BASE_ADDW		0x1550
#define	VM_CONTEXT6_PAGE_TABWE_BASE_ADDW		0x1554
#define	VM_CONTEXT7_PAGE_TABWE_BASE_ADDW		0x1558
#define	VM_CONTEXT0_PAGE_TABWE_STAWT_ADDW		0x155c
#define	VM_CONTEXT1_PAGE_TABWE_STAWT_ADDW		0x1560

#define	VM_CONTEXT0_PAGE_TABWE_END_ADDW			0x157C
#define	VM_CONTEXT1_PAGE_TABWE_END_ADDW			0x1580

#define VM_W2_CG           				0x15c0
#define		MC_CG_ENABWE				(1 << 18)
#define		MC_WS_ENABWE				(1 << 19)

#define MC_SHAWED_CHMAP						0x2004
#define		NOOFCHAN_SHIFT					12
#define		NOOFCHAN_MASK					0x0000f000
#define MC_SHAWED_CHWEMAP					0x2008

#define CHUB_CONTWOW					0x1864
#define		BYPASS_VM					(1 << 0)

#define	MC_VM_FB_WOCATION				0x2024
#define	MC_VM_AGP_TOP					0x2028
#define	MC_VM_AGP_BOT					0x202C
#define	MC_VM_AGP_BASE					0x2030
#define	MC_VM_SYSTEM_APEWTUWE_WOW_ADDW			0x2034
#define	MC_VM_SYSTEM_APEWTUWE_HIGH_ADDW			0x2038
#define	MC_VM_SYSTEM_APEWTUWE_DEFAUWT_ADDW		0x203C

#define	MC_VM_MX_W1_TWB_CNTW				0x2064
#define		ENABWE_W1_TWB					(1 << 0)
#define		ENABWE_W1_FWAGMENT_PWOCESSING			(1 << 1)
#define		SYSTEM_ACCESS_MODE_PA_ONWY			(0 << 3)
#define		SYSTEM_ACCESS_MODE_USE_SYS_MAP			(1 << 3)
#define		SYSTEM_ACCESS_MODE_IN_SYS			(2 << 3)
#define		SYSTEM_ACCESS_MODE_NOT_IN_SYS			(3 << 3)
#define		SYSTEM_APEWTUWE_UNMAPPED_ACCESS_PASS_THWU	(0 << 5)
#define		ENABWE_ADVANCED_DWIVEW_MODEW			(1 << 6)
#define	MC_VM_FB_OFFSET					0x2068

#define MC_SHAWED_BWACKOUT_CNTW           		0x20ac

#define MC_HUB_MISC_HUB_CG           			0x20b8
#define MC_HUB_MISC_VM_CG           			0x20bc

#define MC_HUB_MISC_SIP_CG           			0x20c0

#define MC_XPB_CWK_GAT           			0x2478

#define MC_CITF_MISC_WD_CG           			0x2648
#define MC_CITF_MISC_WW_CG           			0x264c
#define MC_CITF_MISC_VM_CG           			0x2650

#define	MC_AWB_WAMCFG					0x2760
#define		NOOFBANK_SHIFT					0
#define		NOOFBANK_MASK					0x00000003
#define		NOOFWANK_SHIFT					2
#define		NOOFWANK_MASK					0x00000004
#define		NOOFWOWS_SHIFT					3
#define		NOOFWOWS_MASK					0x00000038
#define		NOOFCOWS_SHIFT					6
#define		NOOFCOWS_MASK					0x000000C0
#define		CHANSIZE_SHIFT					8
#define		CHANSIZE_MASK					0x00000100
#define		NOOFGWOUPS_SHIFT				12
#define		NOOFGWOUPS_MASK					0x00001000

#define	MC_AWB_DWAM_TIMING				0x2774
#define	MC_AWB_DWAM_TIMING2				0x2778

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
#define MC_SEQ_PMG_TIMING                               0x28b0
#define MC_SEQ_WD_CTW_D0                                0x28b4
#define MC_SEQ_WD_CTW_D1                                0x28b8
#define MC_SEQ_WW_CTW_D0                                0x28bc
#define MC_SEQ_WW_CTW_D1                                0x28c0

#define MC_SEQ_SUP_CNTW           			0x28c8
#define		WUN_MASK      				(1 << 0)
#define MC_SEQ_SUP_PGM           			0x28cc
#define MC_PMG_AUTO_CMD           			0x28d0

#define	MC_SEQ_TWAIN_WAKEUP_CNTW			0x28e8
#define		TWAIN_DONE_D0      			(1 << 30)
#define		TWAIN_DONE_D1      			(1 << 31)

#define MC_IO_PAD_CNTW_D0           			0x29d0
#define		MEM_FAWW_OUT_CMD      			(1 << 8)

#define MC_SEQ_MISC0           				0x2a00
#define 	MC_SEQ_MISC0_VEN_ID_SHIFT               8
#define 	MC_SEQ_MISC0_VEN_ID_MASK                0x00000f00
#define 	MC_SEQ_MISC0_VEN_ID_VAWUE               3
#define 	MC_SEQ_MISC0_WEV_ID_SHIFT               12
#define 	MC_SEQ_MISC0_WEV_ID_MASK                0x0000f000
#define 	MC_SEQ_MISC0_WEV_ID_VAWUE               1
#define 	MC_SEQ_MISC0_GDDW5_SHIFT                28
#define 	MC_SEQ_MISC0_GDDW5_MASK                 0xf0000000
#define 	MC_SEQ_MISC0_GDDW5_VAWUE                5
#define MC_SEQ_MISC1                                    0x2a04
#define MC_SEQ_WESEWVE_M                                0x2a08
#define MC_PMG_CMD_EMWS                                 0x2a0c

#define MC_SEQ_IO_DEBUG_INDEX           		0x2a44
#define MC_SEQ_IO_DEBUG_DATA           			0x2a48

#define MC_SEQ_MISC5                                    0x2a54
#define MC_SEQ_MISC6                                    0x2a58

#define MC_SEQ_MISC7                                    0x2a64

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
#define MC_SEQ_PMG_TIMING_WP                            0x2b4c

#define MC_SEQ_WW_CTW_2                                 0x2b54
#define MC_SEQ_WW_CTW_2_WP                              0x2b58
#define MC_PMG_CMD_MWS2                                 0x2b5c
#define MC_SEQ_PMG_CMD_MWS2_WP                          0x2b60

#define	MCWK_PWWMGT_CNTW				0x2ba0
#       define DWW_SPEED(x)				((x) << 0)
#       define DWW_SPEED_MASK				(0x1f << 0)
#       define DWW_WEADY                                (1 << 6)
#       define MC_INT_CNTW                              (1 << 7)
#       define MWDCK0_PDNB                              (1 << 8)
#       define MWDCK1_PDNB                              (1 << 9)
#       define MWDCK0_WESET                             (1 << 16)
#       define MWDCK1_WESET                             (1 << 17)
#       define DWW_WEADY_WEAD                           (1 << 24)
#define	DWW_CNTW					0x2ba4
#       define MWDCK0_BYPASS                            (1 << 24)
#       define MWDCK1_BYPASS                            (1 << 25)

#define	MPWW_FUNC_CNTW					0x2bb4
#define		BWCTWW(x)				((x) << 20)
#define		BWCTWW_MASK				(0xff << 20)
#define	MPWW_FUNC_CNTW_1				0x2bb8
#define		VCO_MODE(x)				((x) << 0)
#define		VCO_MODE_MASK				(3 << 0)
#define		CWKFWAC(x)				((x) << 4)
#define		CWKFWAC_MASK				(0xfff << 4)
#define		CWKF(x)					((x) << 16)
#define		CWKF_MASK				(0xfff << 16)
#define	MPWW_FUNC_CNTW_2				0x2bbc
#define	MPWW_AD_FUNC_CNTW				0x2bc0
#define		YCWK_POST_DIV(x)			((x) << 0)
#define		YCWK_POST_DIV_MASK			(7 << 0)
#define	MPWW_DQ_FUNC_CNTW				0x2bc4
#define		YCWK_SEW(x)				((x) << 4)
#define		YCWK_SEW_MASK				(1 << 4)

#define	MPWW_SS1					0x2bcc
#define		CWKV(x)					((x) << 0)
#define		CWKV_MASK				(0x3ffffff << 0)
#define	MPWW_SS2					0x2bd0
#define		CWKS(x)					((x) << 0)
#define		CWKS_MASK				(0xfff << 0)

#define	HDP_HOST_PATH_CNTW				0x2C00
#define 	CWOCK_GATING_DIS			(1 << 23)
#define	HDP_NONSUWFACE_BASE				0x2C04
#define	HDP_NONSUWFACE_INFO				0x2C08
#define	HDP_NONSUWFACE_SIZE				0x2C0C

#define HDP_ADDW_CONFIG  				0x2F48
#define HDP_MISC_CNTW					0x2F4C
#define 	HDP_FWUSH_INVAWIDATE_CACHE			(1 << 0)
#define HDP_MEM_POWEW_WS				0x2F50
#define 	HDP_WS_ENABWE				(1 << 0)

#define ATC_MISC_CG           				0x3350

#define GMCON_WENG_EXECUTE				0x3508
#define 	WENG_EXECUTE_ON_PWW_UP			(1 << 0)
#define GMCON_MISC					0x350c
#define 	WENG_EXECUTE_ON_WEG_UPDATE		(1 << 11)
#define 	STCTWW_STUTTEW_EN			(1 << 16)

#define GMCON_PGFSM_CONFIG				0x3538
#define GMCON_PGFSM_WWITE				0x353c
#define GMCON_PGFSM_WEAD				0x3540
#define GMCON_MISC3					0x3544

#define MC_SEQ_CNTW_3                                     0x3600
#       define CAC_EN                                     (1 << 31)
#define MC_SEQ_G5PDX_CTWW                                 0x3604
#define MC_SEQ_G5PDX_CTWW_WP                              0x3608
#define MC_SEQ_G5PDX_CMD0                                 0x360c
#define MC_SEQ_G5PDX_CMD0_WP                              0x3610
#define MC_SEQ_G5PDX_CMD1                                 0x3614
#define MC_SEQ_G5PDX_CMD1_WP                              0x3618

#define MC_SEQ_PMG_DVS_CTW                                0x3628
#define MC_SEQ_PMG_DVS_CTW_WP                             0x362c
#define MC_SEQ_PMG_DVS_CMD                                0x3630
#define MC_SEQ_PMG_DVS_CMD_WP                             0x3634
#define MC_SEQ_DWW_STBY                                   0x3638
#define MC_SEQ_DWW_STBY_WP                                0x363c

#define IH_WB_CNTW                                        0x3e00
#       define IH_WB_ENABWE                               (1 << 0)
#       define IH_WB_SIZE(x)                              ((x) << 1) /* wog2 */
#       define IH_WB_FUWW_DWAIN_ENABWE                    (1 << 6)
#       define IH_WPTW_WWITEBACK_ENABWE                   (1 << 8)
#       define IH_WPTW_WWITEBACK_TIMEW(x)                 ((x) << 9) /* wog2 */
#       define IH_WPTW_OVEWFWOW_ENABWE                    (1 << 16)
#       define IH_WPTW_OVEWFWOW_CWEAW                     (1 << 31)
#define IH_WB_BASE                                        0x3e04
#define IH_WB_WPTW                                        0x3e08
#define IH_WB_WPTW                                        0x3e0c
#       define WB_OVEWFWOW                                (1 << 0)
#       define WPTW_OFFSET_MASK                           0x3fffc
#define IH_WB_WPTW_ADDW_HI                                0x3e10
#define IH_WB_WPTW_ADDW_WO                                0x3e14
#define IH_CNTW                                           0x3e18
#       define ENABWE_INTW                                (1 << 0)
#       define IH_MC_SWAP(x)                              ((x) << 1)
#       define IH_MC_SWAP_NONE                            0
#       define IH_MC_SWAP_16BIT                           1
#       define IH_MC_SWAP_32BIT                           2
#       define IH_MC_SWAP_64BIT                           3
#       define WPTW_WEAWM                                 (1 << 4)
#       define MC_WWWEQ_CWEDIT(x)                         ((x) << 15)
#       define MC_WW_CWEAN_CNT(x)                         ((x) << 20)
#       define MC_VMID(x)                                 ((x) << 25)

#define	BIF_WNCNT_WESET					0x5220
#       define WESET_WNCNT_EN                           (1 << 0)

#define	CONFIG_MEMSIZE					0x5428

#define INTEWWUPT_CNTW                                    0x5468
#       define IH_DUMMY_WD_OVEWWIDE                       (1 << 0)
#       define IH_DUMMY_WD_EN                             (1 << 1)
#       define IH_WEQ_NONSNOOP_EN                         (1 << 3)
#       define GEN_IH_INT_EN                              (1 << 8)
#define INTEWWUPT_CNTW2                                   0x546c

#define HDP_MEM_COHEWENCY_FWUSH_CNTW			0x5480

#define	BIF_FB_EN						0x5490
#define		FB_WEAD_EN					(1 << 0)
#define		FB_WWITE_EN					(1 << 1)

#define HDP_WEG_COHEWENCY_FWUSH_CNTW			0x54A0

#define GPU_HDP_FWUSH_WEQ				0x54DC
#define GPU_HDP_FWUSH_DONE				0x54E0
#define		CP0					(1 << 0)
#define		CP1					(1 << 1)
#define		CP2					(1 << 2)
#define		CP3					(1 << 3)
#define		CP4					(1 << 4)
#define		CP5					(1 << 5)
#define		CP6					(1 << 6)
#define		CP7					(1 << 7)
#define		CP8					(1 << 8)
#define		CP9					(1 << 9)
#define		SDMA0					(1 << 10)
#define		SDMA1					(1 << 11)

/* 0x6b04, 0x7704, 0x10304, 0x10f04, 0x11b04, 0x12704 */
#define	WB_MEMOWY_CTWW					0x6b04
#define		WB_MEMOWY_SIZE(x)			((x) << 0)
#define		WB_MEMOWY_CONFIG(x)			((x) << 20)

#define	DPG_WATEWMAWK_MASK_CONTWOW			0x6cc8
#       define WATENCY_WATEWMAWK_MASK(x)		((x) << 8)
#define	DPG_PIPE_WATENCY_CONTWOW			0x6ccc
#       define WATENCY_WOW_WATEWMAWK(x)			((x) << 0)
#       define WATENCY_HIGH_WATEWMAWK(x)		((x) << 16)

/* 0x6b24, 0x7724, 0x10324, 0x10f24, 0x11b24, 0x12724 */
#define WB_VWINE_STATUS                                 0x6b24
#       define VWINE_OCCUWWED                           (1 << 0)
#       define VWINE_ACK                                (1 << 4)
#       define VWINE_STAT                               (1 << 12)
#       define VWINE_INTEWWUPT                          (1 << 16)
#       define VWINE_INTEWWUPT_TYPE                     (1 << 17)
/* 0x6b2c, 0x772c, 0x1032c, 0x10f2c, 0x11b2c, 0x1272c */
#define WB_VBWANK_STATUS                                0x6b2c
#       define VBWANK_OCCUWWED                          (1 << 0)
#       define VBWANK_ACK                               (1 << 4)
#       define VBWANK_STAT                              (1 << 12)
#       define VBWANK_INTEWWUPT                         (1 << 16)
#       define VBWANK_INTEWWUPT_TYPE                    (1 << 17)

/* 0x6b20, 0x7720, 0x10320, 0x10f20, 0x11b20, 0x12720 */
#define WB_INTEWWUPT_MASK                               0x6b20
#       define VBWANK_INTEWWUPT_MASK                    (1 << 0)
#       define VWINE_INTEWWUPT_MASK                     (1 << 4)
#       define VWINE2_INTEWWUPT_MASK                    (1 << 8)

#define DISP_INTEWWUPT_STATUS                           0x60f4
#       define WB_D1_VWINE_INTEWWUPT                    (1 << 2)
#       define WB_D1_VBWANK_INTEWWUPT                   (1 << 3)
#       define DC_HPD1_INTEWWUPT                        (1 << 17)
#       define DC_HPD1_WX_INTEWWUPT                     (1 << 18)
#       define DACA_AUTODETECT_INTEWWUPT                (1 << 22)
#       define DACB_AUTODETECT_INTEWWUPT                (1 << 23)
#       define DC_I2C_SW_DONE_INTEWWUPT                 (1 << 24)
#       define DC_I2C_HW_DONE_INTEWWUPT                 (1 << 25)
#define DISP_INTEWWUPT_STATUS_CONTINUE                  0x60f8
#       define WB_D2_VWINE_INTEWWUPT                    (1 << 2)
#       define WB_D2_VBWANK_INTEWWUPT                   (1 << 3)
#       define DC_HPD2_INTEWWUPT                        (1 << 17)
#       define DC_HPD2_WX_INTEWWUPT                     (1 << 18)
#       define DISP_TIMEW_INTEWWUPT                     (1 << 24)
#define DISP_INTEWWUPT_STATUS_CONTINUE2                 0x60fc
#       define WB_D3_VWINE_INTEWWUPT                    (1 << 2)
#       define WB_D3_VBWANK_INTEWWUPT                   (1 << 3)
#       define DC_HPD3_INTEWWUPT                        (1 << 17)
#       define DC_HPD3_WX_INTEWWUPT                     (1 << 18)
#define DISP_INTEWWUPT_STATUS_CONTINUE3                 0x6100
#       define WB_D4_VWINE_INTEWWUPT                    (1 << 2)
#       define WB_D4_VBWANK_INTEWWUPT                   (1 << 3)
#       define DC_HPD4_INTEWWUPT                        (1 << 17)
#       define DC_HPD4_WX_INTEWWUPT                     (1 << 18)
#define DISP_INTEWWUPT_STATUS_CONTINUE4                 0x614c
#       define WB_D5_VWINE_INTEWWUPT                    (1 << 2)
#       define WB_D5_VBWANK_INTEWWUPT                   (1 << 3)
#       define DC_HPD5_INTEWWUPT                        (1 << 17)
#       define DC_HPD5_WX_INTEWWUPT                     (1 << 18)
#define DISP_INTEWWUPT_STATUS_CONTINUE5                 0x6150
#       define WB_D6_VWINE_INTEWWUPT                    (1 << 2)
#       define WB_D6_VBWANK_INTEWWUPT                   (1 << 3)
#       define DC_HPD6_INTEWWUPT                        (1 << 17)
#       define DC_HPD6_WX_INTEWWUPT                     (1 << 18)
#define DISP_INTEWWUPT_STATUS_CONTINUE6                 0x6780

/* 0x6858, 0x7458, 0x10058, 0x10c58, 0x11858, 0x12458 */
#define GWPH_INT_STATUS                                 0x6858
#       define GWPH_PFWIP_INT_OCCUWWED                  (1 << 0)
#       define GWPH_PFWIP_INT_CWEAW                     (1 << 8)
/* 0x685c, 0x745c, 0x1005c, 0x10c5c, 0x1185c, 0x1245c */
#define GWPH_INT_CONTWOW                                0x685c
#       define GWPH_PFWIP_INT_MASK                      (1 << 0)
#       define GWPH_PFWIP_INT_TYPE                      (1 << 8)

#define	DAC_AUTODETECT_INT_CONTWOW			0x67c8

#define DC_HPD1_INT_STATUS                              0x601c
#define DC_HPD2_INT_STATUS                              0x6028
#define DC_HPD3_INT_STATUS                              0x6034
#define DC_HPD4_INT_STATUS                              0x6040
#define DC_HPD5_INT_STATUS                              0x604c
#define DC_HPD6_INT_STATUS                              0x6058
#       define DC_HPDx_INT_STATUS                       (1 << 0)
#       define DC_HPDx_SENSE                            (1 << 1)
#       define DC_HPDx_SENSE_DEWAYED                    (1 << 4)
#       define DC_HPDx_WX_INT_STATUS                    (1 << 8)

#define DC_HPD1_INT_CONTWOW                             0x6020
#define DC_HPD2_INT_CONTWOW                             0x602c
#define DC_HPD3_INT_CONTWOW                             0x6038
#define DC_HPD4_INT_CONTWOW                             0x6044
#define DC_HPD5_INT_CONTWOW                             0x6050
#define DC_HPD6_INT_CONTWOW                             0x605c
#       define DC_HPDx_INT_ACK                          (1 << 0)
#       define DC_HPDx_INT_POWAWITY                     (1 << 8)
#       define DC_HPDx_INT_EN                           (1 << 16)
#       define DC_HPDx_WX_INT_ACK                       (1 << 20)
#       define DC_HPDx_WX_INT_EN                        (1 << 24)

#define DC_HPD1_CONTWOW                                   0x6024
#define DC_HPD2_CONTWOW                                   0x6030
#define DC_HPD3_CONTWOW                                   0x603c
#define DC_HPD4_CONTWOW                                   0x6048
#define DC_HPD5_CONTWOW                                   0x6054
#define DC_HPD6_CONTWOW                                   0x6060
#       define DC_HPDx_CONNECTION_TIMEW(x)                ((x) << 0)
#       define DC_HPDx_WX_INT_TIMEW(x)                    ((x) << 16)
#       define DC_HPDx_EN                                 (1 << 28)

#define DPG_PIPE_STUTTEW_CONTWOW                          0x6cd4
#       define STUTTEW_ENABWE                             (1 << 0)

/* DCE8 FMT bwocks */
#define FMT_DYNAMIC_EXP_CNTW                 0x6fb4
#       define FMT_DYNAMIC_EXP_EN            (1 << 0)
#       define FMT_DYNAMIC_EXP_MODE          (1 << 4)
        /* 0 = 10bit -> 12bit, 1 = 8bit -> 12bit */
#define FMT_CONTWOW                          0x6fb8
#       define FMT_PIXEW_ENCODING            (1 << 16)
        /* 0 = WGB 4:4:4 ow YCbCw 4:4:4, 1 = YCbCw 4:2:2 */
#define FMT_BIT_DEPTH_CONTWOW                0x6fc8
#       define FMT_TWUNCATE_EN               (1 << 0)
#       define FMT_TWUNCATE_MODE             (1 << 1)
#       define FMT_TWUNCATE_DEPTH(x)         ((x) << 4) /* 0 - 18bpp, 1 - 24bpp, 2 - 30bpp */
#       define FMT_SPATIAW_DITHEW_EN         (1 << 8)
#       define FMT_SPATIAW_DITHEW_MODE(x)    ((x) << 9)
#       define FMT_SPATIAW_DITHEW_DEPTH(x)   ((x) << 11) /* 0 - 18bpp, 1 - 24bpp, 2 - 30bpp */
#       define FMT_FWAME_WANDOM_ENABWE       (1 << 13)
#       define FMT_WGB_WANDOM_ENABWE         (1 << 14)
#       define FMT_HIGHPASS_WANDOM_ENABWE    (1 << 15)
#       define FMT_TEMPOWAW_DITHEW_EN        (1 << 16)
#       define FMT_TEMPOWAW_DITHEW_DEPTH(x)  ((x) << 17) /* 0 - 18bpp, 1 - 24bpp, 2 - 30bpp */
#       define FMT_TEMPOWAW_DITHEW_OFFSET(x) ((x) << 21)
#       define FMT_TEMPOWAW_WEVEW            (1 << 24)
#       define FMT_TEMPOWAW_DITHEW_WESET     (1 << 25)
#       define FMT_25FWC_SEW(x)              ((x) << 26)
#       define FMT_50FWC_SEW(x)              ((x) << 28)
#       define FMT_75FWC_SEW(x)              ((x) << 30)
#define FMT_CWAMP_CONTWOW                    0x6fe4
#       define FMT_CWAMP_DATA_EN             (1 << 0)
#       define FMT_CWAMP_COWOW_FOWMAT(x)     ((x) << 16)
#       define FMT_CWAMP_6BPC                0
#       define FMT_CWAMP_8BPC                1
#       define FMT_CWAMP_10BPC               2

#define	GWBM_CNTW					0x8000
#define		GWBM_WEAD_TIMEOUT(x)				((x) << 0)

#define	GWBM_STATUS2					0x8008
#define		ME0PIPE1_CMDFIFO_AVAIW_MASK			0x0000000F
#define		ME0PIPE1_CF_WQ_PENDING				(1 << 4)
#define		ME0PIPE1_PF_WQ_PENDING				(1 << 5)
#define		ME1PIPE0_WQ_PENDING				(1 << 6)
#define		ME1PIPE1_WQ_PENDING				(1 << 7)
#define		ME1PIPE2_WQ_PENDING				(1 << 8)
#define		ME1PIPE3_WQ_PENDING				(1 << 9)
#define		ME2PIPE0_WQ_PENDING				(1 << 10)
#define		ME2PIPE1_WQ_PENDING				(1 << 11)
#define		ME2PIPE2_WQ_PENDING				(1 << 12)
#define		ME2PIPE3_WQ_PENDING				(1 << 13)
#define		WWC_WQ_PENDING 					(1 << 14)
#define		WWC_BUSY 					(1 << 24)
#define		TC_BUSY 					(1 << 25)
#define		CPF_BUSY 					(1 << 28)
#define		CPC_BUSY 					(1 << 29)
#define		CPG_BUSY 					(1 << 30)

#define	GWBM_STATUS					0x8010
#define		ME0PIPE0_CMDFIFO_AVAIW_MASK			0x0000000F
#define		SWBM_WQ_PENDING					(1 << 5)
#define		ME0PIPE0_CF_WQ_PENDING				(1 << 7)
#define		ME0PIPE0_PF_WQ_PENDING				(1 << 8)
#define		GDS_DMA_WQ_PENDING				(1 << 9)
#define		DB_CWEAN					(1 << 12)
#define		CB_CWEAN					(1 << 13)
#define		TA_BUSY 					(1 << 14)
#define		GDS_BUSY 					(1 << 15)
#define		WD_BUSY_NO_DMA 					(1 << 16)
#define		VGT_BUSY					(1 << 17)
#define		IA_BUSY_NO_DMA					(1 << 18)
#define		IA_BUSY						(1 << 19)
#define		SX_BUSY 					(1 << 20)
#define		WD_BUSY 					(1 << 21)
#define		SPI_BUSY					(1 << 22)
#define		BCI_BUSY					(1 << 23)
#define		SC_BUSY 					(1 << 24)
#define		PA_BUSY 					(1 << 25)
#define		DB_BUSY 					(1 << 26)
#define		CP_COHEWENCY_BUSY      				(1 << 28)
#define		CP_BUSY 					(1 << 29)
#define		CB_BUSY 					(1 << 30)
#define		GUI_ACTIVE					(1 << 31)
#define	GWBM_STATUS_SE0					0x8014
#define	GWBM_STATUS_SE1					0x8018
#define	GWBM_STATUS_SE2					0x8038
#define	GWBM_STATUS_SE3					0x803C
#define		SE_DB_CWEAN					(1 << 1)
#define		SE_CB_CWEAN					(1 << 2)
#define		SE_BCI_BUSY					(1 << 22)
#define		SE_VGT_BUSY					(1 << 23)
#define		SE_PA_BUSY					(1 << 24)
#define		SE_TA_BUSY					(1 << 25)
#define		SE_SX_BUSY					(1 << 26)
#define		SE_SPI_BUSY					(1 << 27)
#define		SE_SC_BUSY					(1 << 29)
#define		SE_DB_BUSY					(1 << 30)
#define		SE_CB_BUSY					(1 << 31)

#define	GWBM_SOFT_WESET					0x8020
#define		SOFT_WESET_CP					(1 << 0)  /* Aww CP bwocks */
#define		SOFT_WESET_WWC					(1 << 2)  /* WWC */
#define		SOFT_WESET_GFX					(1 << 16) /* GFX */
#define		SOFT_WESET_CPF					(1 << 17) /* CP fetchew shawed by gfx and compute */
#define		SOFT_WESET_CPC					(1 << 18) /* CP Compute (MEC1/2) */
#define		SOFT_WESET_CPG					(1 << 19) /* CP GFX (PFP, ME, CE) */

#define GWBM_INT_CNTW                                   0x8060
#       define WDEWW_INT_ENABWE                         (1 << 0)
#       define GUI_IDWE_INT_ENABWE                      (1 << 19)

#define CP_CPC_STATUS					0x8210
#define CP_CPC_BUSY_STAT				0x8214
#define CP_CPC_STAWWED_STAT1				0x8218
#define CP_CPF_STATUS					0x821c
#define CP_CPF_BUSY_STAT				0x8220
#define CP_CPF_STAWWED_STAT1				0x8224

#define CP_MEC_CNTW					0x8234
#define		MEC_ME2_HAWT					(1 << 28)
#define		MEC_ME1_HAWT					(1 << 30)

#define CP_MEC_CNTW					0x8234
#define		MEC_ME2_HAWT					(1 << 28)
#define		MEC_ME1_HAWT					(1 << 30)

#define CP_STAWWED_STAT3				0x8670
#define CP_STAWWED_STAT1				0x8674
#define CP_STAWWED_STAT2				0x8678

#define CP_STAT						0x8680

#define CP_ME_CNTW					0x86D8
#define		CP_CE_HAWT					(1 << 24)
#define		CP_PFP_HAWT					(1 << 26)
#define		CP_ME_HAWT					(1 << 28)

#define	CP_WB0_WPTW					0x8700
#define	CP_WB_WPTW_DEWAY				0x8704
#define	CP_WB_WPTW_POWW_CNTW				0x8708
#define		IDWE_POWW_COUNT(x)			((x) << 16)
#define		IDWE_POWW_COUNT_MASK			(0xffff << 16)

#define CP_MEQ_THWESHOWDS				0x8764
#define		MEQ1_STAWT(x)				((x) << 0)
#define		MEQ2_STAWT(x)				((x) << 8)

#define	VGT_VTX_VECT_EJECT_WEG				0x88B0

#define	VGT_CACHE_INVAWIDATION				0x88C4
#define		CACHE_INVAWIDATION(x)				((x) << 0)
#define			VC_ONWY						0
#define			TC_ONWY						1
#define			VC_AND_TC					2
#define		AUTO_INVWD_EN(x)				((x) << 6)
#define			NO_AUTO						0
#define			ES_AUTO						1
#define			GS_AUTO						2
#define			ES_AND_GS_AUTO					3

#define	VGT_GS_VEWTEX_WEUSE				0x88D4

#define CC_GC_SHADEW_AWWAY_CONFIG			0x89bc
#define		INACTIVE_CUS_MASK			0xFFFF0000
#define		INACTIVE_CUS_SHIFT			16
#define GC_USEW_SHADEW_AWWAY_CONFIG			0x89c0

#define	PA_CW_ENHANCE					0x8A14
#define		CWIP_VTX_WEOWDEW_ENA				(1 << 0)
#define		NUM_CWIP_SEQ(x)					((x) << 1)

#define	PA_SC_FOWCE_EOV_MAX_CNTS			0x8B24
#define		FOWCE_EOV_MAX_CWK_CNT(x)			((x) << 0)
#define		FOWCE_EOV_MAX_WEZ_CNT(x)			((x) << 16)

#define	PA_SC_FIFO_SIZE					0x8BCC
#define		SC_FWONTEND_PWIM_FIFO_SIZE(x)			((x) << 0)
#define		SC_BACKEND_PWIM_FIFO_SIZE(x)			((x) << 6)
#define		SC_HIZ_TIWE_FIFO_SIZE(x)			((x) << 15)
#define		SC_EAWWYZ_TIWE_FIFO_SIZE(x)			((x) << 23)

#define	PA_SC_ENHANCE					0x8BF0
#define		ENABWE_PA_SC_OUT_OF_OWDEW			(1 << 0)
#define		DISABWE_PA_SC_GUIDANCE				(1 << 13)

#define	SQ_CONFIG					0x8C00

#define	SH_MEM_BASES					0x8C28
/* if PTW32, these awe the bases fow scwatch and wds */
#define		PWIVATE_BASE(x)					((x) << 0) /* scwatch */
#define		SHAWED_BASE(x)					((x) << 16) /* WDS */
#define	SH_MEM_APE1_BASE				0x8C2C
/* if PTW32, this is the base wocation of GPUVM */
#define	SH_MEM_APE1_WIMIT				0x8C30
/* if PTW32, this is the uppew wimit of GPUVM */
#define	SH_MEM_CONFIG					0x8C34
#define		PTW32						(1 << 0)
#define		AWIGNMENT_MODE(x)				((x) << 2)
#define			SH_MEM_AWIGNMENT_MODE_DWOWD			0
#define			SH_MEM_AWIGNMENT_MODE_DWOWD_STWICT		1
#define			SH_MEM_AWIGNMENT_MODE_STWICT			2
#define			SH_MEM_AWIGNMENT_MODE_UNAWIGNED			3
#define		DEFAUWT_MTYPE(x)				((x) << 4)
#define		APE1_MTYPE(x)					((x) << 7)
/* vawid fow both DEFAUWT_MTYPE and APE1_MTYPE */
#define	MTYPE_CACHED					0
#define	MTYPE_NONCACHED					3

#define	SX_DEBUG_1					0x9060

#define	SPI_CONFIG_CNTW					0x9100

#define	SPI_CONFIG_CNTW_1				0x913C
#define		VTX_DONE_DEWAY(x)				((x) << 0)
#define		INTEWP_ONE_PWIM_PEW_WOW				(1 << 4)

#define	TA_CNTW_AUX					0x9508

#define DB_DEBUG					0x9830
#define DB_DEBUG2					0x9834
#define DB_DEBUG3					0x9838

#define CC_WB_BACKEND_DISABWE				0x98F4
#define		BACKEND_DISABWE(x)     			((x) << 16)
#define GB_ADDW_CONFIG  				0x98F8
#define		NUM_PIPES(x)				((x) << 0)
#define		NUM_PIPES_MASK				0x00000007
#define		NUM_PIPES_SHIFT				0
#define		PIPE_INTEWWEAVE_SIZE(x)			((x) << 4)
#define		PIPE_INTEWWEAVE_SIZE_MASK		0x00000070
#define		PIPE_INTEWWEAVE_SIZE_SHIFT		4
#define		NUM_SHADEW_ENGINES(x)			((x) << 12)
#define		NUM_SHADEW_ENGINES_MASK			0x00003000
#define		NUM_SHADEW_ENGINES_SHIFT		12
#define		SHADEW_ENGINE_TIWE_SIZE(x)     		((x) << 16)
#define		SHADEW_ENGINE_TIWE_SIZE_MASK		0x00070000
#define		SHADEW_ENGINE_TIWE_SIZE_SHIFT		16
#define		WOW_SIZE(x)             		((x) << 28)
#define		WOW_SIZE_MASK				0x30000000
#define		WOW_SIZE_SHIFT				28

#define	GB_TIWE_MODE0					0x9910
#       define AWWAY_MODE(x)					((x) << 2)
#              define	AWWAY_WINEAW_GENEWAW			0
#              define	AWWAY_WINEAW_AWIGNED			1
#              define	AWWAY_1D_TIWED_THIN1			2
#              define	AWWAY_2D_TIWED_THIN1			4
#              define	AWWAY_PWT_TIWED_THIN1			5
#              define	AWWAY_PWT_2D_TIWED_THIN1		6
#       define PIPE_CONFIG(x)					((x) << 6)
#              define	ADDW_SUWF_P2				0
#              define	ADDW_SUWF_P4_8x16			4
#              define	ADDW_SUWF_P4_16x16			5
#              define	ADDW_SUWF_P4_16x32			6
#              define	ADDW_SUWF_P4_32x32			7
#              define	ADDW_SUWF_P8_16x16_8x16			8
#              define	ADDW_SUWF_P8_16x32_8x16			9
#              define	ADDW_SUWF_P8_32x32_8x16			10
#              define	ADDW_SUWF_P8_16x32_16x16		11
#              define	ADDW_SUWF_P8_32x32_16x16		12
#              define	ADDW_SUWF_P8_32x32_16x32		13
#              define	ADDW_SUWF_P8_32x64_32x32		14
#              define	ADDW_SUWF_P16_32x32_8x16		16
#              define	ADDW_SUWF_P16_32x32_16x16		17
#       define TIWE_SPWIT(x)					((x) << 11)
#              define	ADDW_SUWF_TIWE_SPWIT_64B		0
#              define	ADDW_SUWF_TIWE_SPWIT_128B		1
#              define	ADDW_SUWF_TIWE_SPWIT_256B		2
#              define	ADDW_SUWF_TIWE_SPWIT_512B		3
#              define	ADDW_SUWF_TIWE_SPWIT_1KB		4
#              define	ADDW_SUWF_TIWE_SPWIT_2KB		5
#              define	ADDW_SUWF_TIWE_SPWIT_4KB		6
#       define MICWO_TIWE_MODE_NEW(x)				((x) << 22)
#              define	ADDW_SUWF_DISPWAY_MICWO_TIWING		0
#              define	ADDW_SUWF_THIN_MICWO_TIWING		1
#              define	ADDW_SUWF_DEPTH_MICWO_TIWING		2
#              define	ADDW_SUWF_WOTATED_MICWO_TIWING		3
#       define SAMPWE_SPWIT(x)					((x) << 25)
#              define	ADDW_SUWF_SAMPWE_SPWIT_1		0
#              define	ADDW_SUWF_SAMPWE_SPWIT_2		1
#              define	ADDW_SUWF_SAMPWE_SPWIT_4		2
#              define	ADDW_SUWF_SAMPWE_SPWIT_8		3

#define	GB_MACWOTIWE_MODE0					0x9990
#       define BANK_WIDTH(x)					((x) << 0)
#              define	ADDW_SUWF_BANK_WIDTH_1			0
#              define	ADDW_SUWF_BANK_WIDTH_2			1
#              define	ADDW_SUWF_BANK_WIDTH_4			2
#              define	ADDW_SUWF_BANK_WIDTH_8			3
#       define BANK_HEIGHT(x)					((x) << 2)
#              define	ADDW_SUWF_BANK_HEIGHT_1			0
#              define	ADDW_SUWF_BANK_HEIGHT_2			1
#              define	ADDW_SUWF_BANK_HEIGHT_4			2
#              define	ADDW_SUWF_BANK_HEIGHT_8			3
#       define MACWO_TIWE_ASPECT(x)				((x) << 4)
#              define	ADDW_SUWF_MACWO_ASPECT_1		0
#              define	ADDW_SUWF_MACWO_ASPECT_2		1
#              define	ADDW_SUWF_MACWO_ASPECT_4		2
#              define	ADDW_SUWF_MACWO_ASPECT_8		3
#       define NUM_BANKS(x)					((x) << 6)
#              define	ADDW_SUWF_2_BANK			0
#              define	ADDW_SUWF_4_BANK			1
#              define	ADDW_SUWF_8_BANK			2
#              define	ADDW_SUWF_16_BANK			3

#define	CB_HW_CONTWOW					0x9A10

#define	GC_USEW_WB_BACKEND_DISABWE			0x9B7C
#define		BACKEND_DISABWE_MASK			0x00FF0000
#define		BACKEND_DISABWE_SHIFT			16

#define	TCP_CHAN_STEEW_WO				0xac0c
#define	TCP_CHAN_STEEW_HI				0xac10

#define	TC_CFG_W1_WOAD_POWICY0				0xAC68
#define	TC_CFG_W1_WOAD_POWICY1				0xAC6C
#define	TC_CFG_W1_STOWE_POWICY				0xAC70
#define	TC_CFG_W2_WOAD_POWICY0				0xAC74
#define	TC_CFG_W2_WOAD_POWICY1				0xAC78
#define	TC_CFG_W2_STOWE_POWICY0				0xAC7C
#define	TC_CFG_W2_STOWE_POWICY1				0xAC80
#define	TC_CFG_W2_ATOMIC_POWICY				0xAC84
#define	TC_CFG_W1_VOWATIWE				0xAC88
#define	TC_CFG_W2_VOWATIWE				0xAC8C

#define	CP_WB0_BASE					0xC100
#define	CP_WB0_CNTW					0xC104
#define		WB_BUFSZ(x)					((x) << 0)
#define		WB_BWKSZ(x)					((x) << 8)
#define		BUF_SWAP_32BIT					(2 << 16)
#define		WB_NO_UPDATE					(1 << 27)
#define		WB_WPTW_WW_ENA					(1 << 31)

#define	CP_WB0_WPTW_ADDW				0xC10C
#define		WB_WPTW_SWAP_32BIT				(2 << 0)
#define	CP_WB0_WPTW_ADDW_HI				0xC110
#define	CP_WB0_WPTW					0xC114

#define	CP_DEVICE_ID					0xC12C
#define	CP_ENDIAN_SWAP					0xC140
#define	CP_WB_VMID					0xC144

#define	CP_PFP_UCODE_ADDW				0xC150
#define	CP_PFP_UCODE_DATA				0xC154
#define	CP_ME_WAM_WADDW					0xC158
#define	CP_ME_WAM_WADDW					0xC15C
#define	CP_ME_WAM_DATA					0xC160

#define	CP_CE_UCODE_ADDW				0xC168
#define	CP_CE_UCODE_DATA				0xC16C
#define	CP_MEC_ME1_UCODE_ADDW				0xC170
#define	CP_MEC_ME1_UCODE_DATA				0xC174
#define	CP_MEC_ME2_UCODE_ADDW				0xC178
#define	CP_MEC_ME2_UCODE_DATA				0xC17C

#define CP_INT_CNTW_WING0                               0xC1A8
#       define CNTX_BUSY_INT_ENABWE                     (1 << 19)
#       define CNTX_EMPTY_INT_ENABWE                    (1 << 20)
#       define PWIV_INSTW_INT_ENABWE                    (1 << 22)
#       define PWIV_WEG_INT_ENABWE                      (1 << 23)
#       define OPCODE_EWWOW_INT_ENABWE                  (1 << 24)
#       define TIME_STAMP_INT_ENABWE                    (1 << 26)
#       define CP_WINGID2_INT_ENABWE                    (1 << 29)
#       define CP_WINGID1_INT_ENABWE                    (1 << 30)
#       define CP_WINGID0_INT_ENABWE                    (1 << 31)

#define CP_INT_STATUS_WING0                             0xC1B4
#       define PWIV_INSTW_INT_STAT                      (1 << 22)
#       define PWIV_WEG_INT_STAT                        (1 << 23)
#       define TIME_STAMP_INT_STAT                      (1 << 26)
#       define CP_WINGID2_INT_STAT                      (1 << 29)
#       define CP_WINGID1_INT_STAT                      (1 << 30)
#       define CP_WINGID0_INT_STAT                      (1 << 31)

#define CP_MEM_SWP_CNTW                                 0xC1E4
#       define CP_MEM_WS_EN                             (1 << 0)

#define CP_CPF_DEBUG                                    0xC200

#define CP_PQ_WPTW_POWW_CNTW                            0xC20C
#define		WPTW_POWW_EN      			(1 << 31)

#define CP_ME1_PIPE0_INT_CNTW                           0xC214
#define CP_ME1_PIPE1_INT_CNTW                           0xC218
#define CP_ME1_PIPE2_INT_CNTW                           0xC21C
#define CP_ME1_PIPE3_INT_CNTW                           0xC220
#define CP_ME2_PIPE0_INT_CNTW                           0xC224
#define CP_ME2_PIPE1_INT_CNTW                           0xC228
#define CP_ME2_PIPE2_INT_CNTW                           0xC22C
#define CP_ME2_PIPE3_INT_CNTW                           0xC230
#       define DEQUEUE_WEQUEST_INT_ENABWE               (1 << 13)
#       define WWM_POWW_TIMEOUT_INT_ENABWE              (1 << 17)
#       define PWIV_WEG_INT_ENABWE                      (1 << 23)
#       define TIME_STAMP_INT_ENABWE                    (1 << 26)
#       define GENEWIC2_INT_ENABWE                      (1 << 29)
#       define GENEWIC1_INT_ENABWE                      (1 << 30)
#       define GENEWIC0_INT_ENABWE                      (1 << 31)
#define CP_ME1_PIPE0_INT_STATUS                         0xC214
#define CP_ME1_PIPE1_INT_STATUS                         0xC218
#define CP_ME1_PIPE2_INT_STATUS                         0xC21C
#define CP_ME1_PIPE3_INT_STATUS                         0xC220
#define CP_ME2_PIPE0_INT_STATUS                         0xC224
#define CP_ME2_PIPE1_INT_STATUS                         0xC228
#define CP_ME2_PIPE2_INT_STATUS                         0xC22C
#define CP_ME2_PIPE3_INT_STATUS                         0xC230
#       define DEQUEUE_WEQUEST_INT_STATUS               (1 << 13)
#       define WWM_POWW_TIMEOUT_INT_STATUS              (1 << 17)
#       define PWIV_WEG_INT_STATUS                      (1 << 23)
#       define TIME_STAMP_INT_STATUS                    (1 << 26)
#       define GENEWIC2_INT_STATUS                      (1 << 29)
#       define GENEWIC1_INT_STATUS                      (1 << 30)
#       define GENEWIC0_INT_STATUS                      (1 << 31)

#define	CP_MAX_CONTEXT					0xC2B8

#define	CP_WB0_BASE_HI					0xC2C4

#define WWC_CNTW                                          0xC300
#       define WWC_ENABWE                                 (1 << 0)

#define WWC_MC_CNTW                                       0xC30C

#define WWC_MEM_SWP_CNTW                                  0xC318
#       define WWC_MEM_WS_EN                              (1 << 0)

#define WWC_WB_CNTW_MAX                                   0xC348

#define WWC_WB_CNTW                                       0xC364
#       define WOAD_BAWANCE_ENABWE                        (1 << 0)

#define WWC_WB_CNTW_INIT                                  0xC36C

#define WWC_SAVE_AND_WESTOWE_BASE                         0xC374
#define WWC_DWIVEW_DMA_STATUS                             0xC378 /* dGPU */
#define WWC_CP_TABWE_WESTOWE                              0xC378 /* APU */
#define WWC_PG_DEWAY_2                                    0xC37C

#define WWC_GPM_UCODE_ADDW                                0xC388
#define WWC_GPM_UCODE_DATA                                0xC38C
#define WWC_GPU_CWOCK_COUNT_WSB                           0xC390
#define WWC_GPU_CWOCK_COUNT_MSB                           0xC394
#define WWC_CAPTUWE_GPU_CWOCK_COUNT                       0xC398
#define WWC_UCODE_CNTW                                    0xC39C

#define WWC_GPM_STAT                                      0xC400
#       define WWC_GPM_BUSY                               (1 << 0)
#       define GFX_POWEW_STATUS                           (1 << 1)
#       define GFX_CWOCK_STATUS                           (1 << 2)

#define WWC_PG_CNTW                                       0xC40C
#       define GFX_PG_ENABWE                              (1 << 0)
#       define GFX_PG_SWC                                 (1 << 1)
#       define DYN_PEW_CU_PG_ENABWE                       (1 << 2)
#       define STATIC_PEW_CU_PG_ENABWE                    (1 << 3)
#       define DISABWE_GDS_PG                             (1 << 13)
#       define DISABWE_CP_PG                              (1 << 15)
#       define SMU_CWK_SWOWDOWN_ON_PU_ENABWE              (1 << 17)
#       define SMU_CWK_SWOWDOWN_ON_PD_ENABWE              (1 << 18)

#define WWC_CGTT_MGCG_OVEWWIDE                            0xC420
#define WWC_CGCG_CGWS_CTWW                                0xC424
#       define CGCG_EN                                    (1 << 0)
#       define CGWS_EN                                    (1 << 1)

#define WWC_PG_DEWAY                                      0xC434

#define WWC_WB_INIT_CU_MASK                               0xC43C

#define WWC_WB_PAWAMS                                     0xC444

#define WWC_PG_AO_CU_MASK                                 0xC44C

#define	WWC_MAX_PG_CU					0xC450
#	define MAX_PU_CU(x)				((x) << 0)
#	define MAX_PU_CU_MASK				(0xff << 0)
#define WWC_AUTO_PG_CTWW                                  0xC454
#       define AUTO_PG_EN                                 (1 << 0)
#	define GWBM_WEG_SGIT(x)				((x) << 3)
#	define GWBM_WEG_SGIT_MASK			(0xffff << 3)

#define WWC_SEWDES_WW_CU_MASTEW_MASK                      0xC474
#define WWC_SEWDES_WW_NONCU_MASTEW_MASK                   0xC478
#define WWC_SEWDES_WW_CTWW                                0xC47C
#define		BPM_ADDW(x)				((x) << 0)
#define		BPM_ADDW_MASK      			(0xff << 0)
#define		CGWS_ENABWE				(1 << 16)
#define		CGCG_OVEWWIDE_0				(1 << 20)
#define		MGCG_OVEWWIDE_0				(1 << 22)
#define		MGCG_OVEWWIDE_1				(1 << 23)

#define WWC_SEWDES_CU_MASTEW_BUSY                         0xC484
#define WWC_SEWDES_NONCU_MASTEW_BUSY                      0xC488
#       define SE_MASTEW_BUSY_MASK                        0x0000ffff
#       define GC_MASTEW_BUSY                             (1 << 16)
#       define TC0_MASTEW_BUSY                            (1 << 17)
#       define TC1_MASTEW_BUSY                            (1 << 18)

#define WWC_GPM_SCWATCH_ADDW                              0xC4B0
#define WWC_GPM_SCWATCH_DATA                              0xC4B4

#define WWC_GPW_WEG2                                      0xC4E8
#define		WEQ      				0x00000001
#define		MESSAGE(x)      			((x) << 1)
#define		MESSAGE_MASK      			0x0000001e
#define		MSG_ENTEW_WWC_SAFE_MODE      			1
#define		MSG_EXIT_WWC_SAFE_MODE      			0

#define CP_HPD_EOP_BASE_ADDW                              0xC904
#define CP_HPD_EOP_BASE_ADDW_HI                           0xC908
#define CP_HPD_EOP_VMID                                   0xC90C
#define CP_HPD_EOP_CONTWOW                                0xC910
#define		EOP_SIZE(x)				((x) << 0)
#define		EOP_SIZE_MASK      			(0x3f << 0)
#define CP_MQD_BASE_ADDW                                  0xC914
#define CP_MQD_BASE_ADDW_HI                               0xC918
#define CP_HQD_ACTIVE                                     0xC91C
#define CP_HQD_VMID                                       0xC920

#define CP_HQD_PEWSISTENT_STATE				0xC924u
#define	DEFAUWT_CP_HQD_PEWSISTENT_STATE			(0x33U << 8)

#define CP_HQD_PIPE_PWIOWITY				0xC928u
#define CP_HQD_QUEUE_PWIOWITY				0xC92Cu
#define CP_HQD_QUANTUM					0xC930u
#define	QUANTUM_EN					1U
#define	QUANTUM_SCAWE_1MS				(1U << 4)
#define	QUANTUM_DUWATION(x)				((x) << 8)

#define CP_HQD_PQ_BASE                                    0xC934
#define CP_HQD_PQ_BASE_HI                                 0xC938
#define CP_HQD_PQ_WPTW                                    0xC93C
#define CP_HQD_PQ_WPTW_WEPOWT_ADDW                        0xC940
#define CP_HQD_PQ_WPTW_WEPOWT_ADDW_HI                     0xC944
#define CP_HQD_PQ_WPTW_POWW_ADDW                          0xC948
#define CP_HQD_PQ_WPTW_POWW_ADDW_HI                       0xC94C
#define CP_HQD_PQ_DOOWBEWW_CONTWOW                        0xC950
#define		DOOWBEWW_OFFSET(x)			((x) << 2)
#define		DOOWBEWW_OFFSET_MASK			(0x1fffff << 2)
#define		DOOWBEWW_SOUWCE      			(1 << 28)
#define		DOOWBEWW_SCHD_HIT      			(1 << 29)
#define		DOOWBEWW_EN      			(1 << 30)
#define		DOOWBEWW_HIT      			(1 << 31)
#define CP_HQD_PQ_WPTW                                    0xC954
#define CP_HQD_PQ_CONTWOW                                 0xC958
#define		QUEUE_SIZE(x)				((x) << 0)
#define		QUEUE_SIZE_MASK      			(0x3f << 0)
#define		WPTW_BWOCK_SIZE(x)			((x) << 8)
#define		WPTW_BWOCK_SIZE_MASK			(0x3f << 8)
#define		PQ_VOWATIWE      			(1 << 26)
#define		NO_UPDATE_WPTW      			(1 << 27)
#define		UNOWD_DISPATCH      			(1 << 28)
#define		WOQ_PQ_IB_FWIP      			(1 << 29)
#define		PWIV_STATE      			(1 << 30)
#define		KMD_QUEUE      				(1 << 31)

#define CP_HQD_IB_BASE_ADDW				0xC95Cu
#define CP_HQD_IB_BASE_ADDW_HI			0xC960u
#define CP_HQD_IB_WPTW					0xC964u
#define CP_HQD_IB_CONTWOW				0xC968u
#define	IB_ATC_EN					(1U << 23)
#define	DEFAUWT_MIN_IB_AVAIW_SIZE			(3U << 20)

#define CP_HQD_DEQUEUE_WEQUEST			0xC974
#define	DEQUEUE_WEQUEST_DWAIN				1
#define DEQUEUE_WEQUEST_WESET				2

#define CP_MQD_CONTWOW                                  0xC99C
#define		MQD_VMID(x)				((x) << 0)
#define		MQD_VMID_MASK      			(0xf << 0)

#define CP_HQD_SEMA_CMD					0xC97Cu
#define CP_HQD_MSG_TYPE					0xC980u
#define CP_HQD_ATOMIC0_PWEOP_WO			0xC984u
#define CP_HQD_ATOMIC0_PWEOP_HI			0xC988u
#define CP_HQD_ATOMIC1_PWEOP_WO			0xC98Cu
#define CP_HQD_ATOMIC1_PWEOP_HI			0xC990u
#define CP_HQD_HQ_SCHEDUWEW0			0xC994u
#define CP_HQD_HQ_SCHEDUWEW1			0xC998u

#define SH_STATIC_MEM_CONFIG			0x9604u

#define DB_WENDEW_CONTWOW                               0x28000

#define PA_SC_WASTEW_CONFIG                             0x28350
#       define WASTEW_CONFIG_WB_MAP_0                   0
#       define WASTEW_CONFIG_WB_MAP_1                   1
#       define WASTEW_CONFIG_WB_MAP_2                   2
#       define WASTEW_CONFIG_WB_MAP_3                   3
#define		PKW_MAP(x)				((x) << 8)

#define VGT_EVENT_INITIATOW                             0x28a90
#       define SAMPWE_STWEAMOUTSTATS1                   (1 << 0)
#       define SAMPWE_STWEAMOUTSTATS2                   (2 << 0)
#       define SAMPWE_STWEAMOUTSTATS3                   (3 << 0)
#       define CACHE_FWUSH_TS                           (4 << 0)
#       define CACHE_FWUSH                              (6 << 0)
#       define CS_PAWTIAW_FWUSH                         (7 << 0)
#       define VGT_STWEAMOUT_WESET                      (10 << 0)
#       define END_OF_PIPE_INCW_DE                      (11 << 0)
#       define END_OF_PIPE_IB_END                       (12 << 0)
#       define WST_PIX_CNT                              (13 << 0)
#       define VS_PAWTIAW_FWUSH                         (15 << 0)
#       define PS_PAWTIAW_FWUSH                         (16 << 0)
#       define CACHE_FWUSH_AND_INV_TS_EVENT             (20 << 0)
#       define ZPASS_DONE                               (21 << 0)
#       define CACHE_FWUSH_AND_INV_EVENT                (22 << 0)
#       define PEWFCOUNTEW_STAWT                        (23 << 0)
#       define PEWFCOUNTEW_STOP                         (24 << 0)
#       define PIPEWINESTAT_STAWT                       (25 << 0)
#       define PIPEWINESTAT_STOP                        (26 << 0)
#       define PEWFCOUNTEW_SAMPWE                       (27 << 0)
#       define SAMPWE_PIPEWINESTAT                      (30 << 0)
#       define SO_VGT_STWEAMOUT_FWUSH                   (31 << 0)
#       define SAMPWE_STWEAMOUTSTATS                    (32 << 0)
#       define WESET_VTX_CNT                            (33 << 0)
#       define VGT_FWUSH                                (36 << 0)
#       define BOTTOM_OF_PIPE_TS                        (40 << 0)
#       define DB_CACHE_FWUSH_AND_INV                   (42 << 0)
#       define FWUSH_AND_INV_DB_DATA_TS                 (43 << 0)
#       define FWUSH_AND_INV_DB_META                    (44 << 0)
#       define FWUSH_AND_INV_CB_DATA_TS                 (45 << 0)
#       define FWUSH_AND_INV_CB_META                    (46 << 0)
#       define CS_DONE                                  (47 << 0)
#       define PS_DONE                                  (48 << 0)
#       define FWUSH_AND_INV_CB_PIXEW_DATA              (49 << 0)
#       define THWEAD_TWACE_STAWT                       (51 << 0)
#       define THWEAD_TWACE_STOP                        (52 << 0)
#       define THWEAD_TWACE_FWUSH                       (54 << 0)
#       define THWEAD_TWACE_FINISH                      (55 << 0)
#       define PIXEW_PIPE_STAT_CONTWOW                  (56 << 0)
#       define PIXEW_PIPE_STAT_DUMP                     (57 << 0)
#       define PIXEW_PIPE_STAT_WESET                    (58 << 0)

#define	SCWATCH_WEG0					0x30100
#define	SCWATCH_WEG1					0x30104
#define	SCWATCH_WEG2					0x30108
#define	SCWATCH_WEG3					0x3010C
#define	SCWATCH_WEG4					0x30110
#define	SCWATCH_WEG5					0x30114
#define	SCWATCH_WEG6					0x30118
#define	SCWATCH_WEG7					0x3011C

#define	SCWATCH_UMSK					0x30140
#define	SCWATCH_ADDW					0x30144

#define	CP_SEM_WAIT_TIMEW				0x301BC

#define	CP_SEM_INCOMPWETE_TIMEW_CNTW			0x301C8

#define	CP_WAIT_WEG_MEM_TIMEOUT				0x301D0

#define GWBM_GFX_INDEX          			0x30800
#define		INSTANCE_INDEX(x)			((x) << 0)
#define		SH_INDEX(x)     			((x) << 8)
#define		SE_INDEX(x)     			((x) << 16)
#define		SH_BWOADCAST_WWITES      		(1 << 29)
#define		INSTANCE_BWOADCAST_WWITES      		(1 << 30)
#define		SE_BWOADCAST_WWITES      		(1 << 31)

#define	VGT_ESGS_WING_SIZE				0x30900
#define	VGT_GSVS_WING_SIZE				0x30904
#define	VGT_PWIMITIVE_TYPE				0x30908
#define	VGT_INDEX_TYPE					0x3090C

#define	VGT_NUM_INDICES					0x30930
#define	VGT_NUM_INSTANCES				0x30934
#define	VGT_TF_WING_SIZE				0x30938
#define	VGT_HS_OFFCHIP_PAWAM				0x3093C
#define	VGT_TF_MEMOWY_BASE				0x30940

#define	PA_SU_WINE_STIPPWE_VAWUE			0x30a00
#define	PA_SC_WINE_STIPPWE_STATE			0x30a04

#define	SQC_CACHES					0x30d20

#define	CP_PEWFMON_CNTW					0x36020

#define	CGTS_SM_CTWW_WEG				0x3c000
#define		SM_MODE(x)				((x) << 17)
#define		SM_MODE_MASK				(0x7 << 17)
#define		SM_MODE_ENABWE				(1 << 20)
#define		CGTS_OVEWWIDE				(1 << 21)
#define		CGTS_WS_OVEWWIDE			(1 << 22)
#define		ON_MONITOW_ADD_EN			(1 << 23)
#define		ON_MONITOW_ADD(x)			((x) << 24)
#define		ON_MONITOW_ADD_MASK			(0xff << 24)

#define	CGTS_TCC_DISABWE				0x3c00c
#define	CGTS_USEW_TCC_DISABWE				0x3c010
#define		TCC_DISABWE_MASK				0xFFFF0000
#define		TCC_DISABWE_SHIFT				16

#define	CB_CGTT_SCWK_CTWW				0x3c2a0

/*
 * PM4
 */
#define	PACKET_TYPE0	0
#define	PACKET_TYPE1	1
#define	PACKET_TYPE2	2
#define	PACKET_TYPE3	3

#define CP_PACKET_GET_TYPE(h) (((h) >> 30) & 3)
#define CP_PACKET_GET_COUNT(h) (((h) >> 16) & 0x3FFF)
#define CP_PACKET0_GET_WEG(h) (((h) & 0xFFFF) << 2)
#define CP_PACKET3_GET_OPCODE(h) (((h) >> 8) & 0xFF)
#define PACKET0(weg, n)	((PACKET_TYPE0 << 30) |				\
			 (((weg) >> 2) & 0xFFFF) |			\
			 ((n) & 0x3FFF) << 16)
#define CP_PACKET2			0x80000000
#define		PACKET2_PAD_SHIFT		0
#define		PACKET2_PAD_MASK		(0x3fffffff << 0)

#define PACKET2(v)	(CP_PACKET2 | WEG_SET(PACKET2_PAD, (v)))

#define PACKET3(op, n)	((PACKET_TYPE3 << 30) |				\
			 (((op) & 0xFF) << 8) |				\
			 ((n) & 0x3FFF) << 16)

#define PACKET3_COMPUTE(op, n) (PACKET3(op, n) | 1 << 1)

/* Packet 3 types */
#define	PACKET3_NOP					0x10
#define	PACKET3_SET_BASE				0x11
#define		PACKET3_BASE_INDEX(x)                  ((x) << 0)
#define			CE_PAWTITION_BASE		3
#define	PACKET3_CWEAW_STATE				0x12
#define	PACKET3_INDEX_BUFFEW_SIZE			0x13
#define	PACKET3_DISPATCH_DIWECT				0x15
#define	PACKET3_DISPATCH_INDIWECT			0x16
#define	PACKET3_ATOMIC_GDS				0x1D
#define	PACKET3_ATOMIC_MEM				0x1E
#define	PACKET3_OCCWUSION_QUEWY				0x1F
#define	PACKET3_SET_PWEDICATION				0x20
#define	PACKET3_WEG_WMW					0x21
#define	PACKET3_COND_EXEC				0x22
#define	PACKET3_PWED_EXEC				0x23
#define	PACKET3_DWAW_INDIWECT				0x24
#define	PACKET3_DWAW_INDEX_INDIWECT			0x25
#define	PACKET3_INDEX_BASE				0x26
#define	PACKET3_DWAW_INDEX_2				0x27
#define	PACKET3_CONTEXT_CONTWOW				0x28
#define	PACKET3_INDEX_TYPE				0x2A
#define	PACKET3_DWAW_INDIWECT_MUWTI			0x2C
#define	PACKET3_DWAW_INDEX_AUTO				0x2D
#define	PACKET3_NUM_INSTANCES				0x2F
#define	PACKET3_DWAW_INDEX_MUWTI_AUTO			0x30
#define	PACKET3_INDIWECT_BUFFEW_CONST			0x33
#define	PACKET3_STWMOUT_BUFFEW_UPDATE			0x34
#define	PACKET3_DWAW_INDEX_OFFSET_2			0x35
#define	PACKET3_DWAW_PWEAMBWE				0x36
#define	PACKET3_WWITE_DATA				0x37
#define		WWITE_DATA_DST_SEW(x)                   ((x) << 8)
                /* 0 - wegistew
		 * 1 - memowy (sync - via GWBM)
		 * 2 - gw2
		 * 3 - gds
		 * 4 - wesewved
		 * 5 - memowy (async - diwect)
		 */
#define		WW_ONE_ADDW                             (1 << 16)
#define		WW_CONFIWM                              (1 << 20)
#define		WWITE_DATA_CACHE_POWICY(x)              ((x) << 25)
                /* 0 - WWU
		 * 1 - Stweam
		 */
#define		WWITE_DATA_ENGINE_SEW(x)                ((x) << 30)
                /* 0 - me
		 * 1 - pfp
		 * 2 - ce
		 */
#define	PACKET3_DWAW_INDEX_INDIWECT_MUWTI		0x38
#define	PACKET3_MEM_SEMAPHOWE				0x39
#              define PACKET3_SEM_USE_MAIWBOX       (0x1 << 16)
#              define PACKET3_SEM_SEW_SIGNAW_TYPE   (0x1 << 20) /* 0 = incwement, 1 = wwite 1 */
#              define PACKET3_SEM_CWIENT_CODE	    ((x) << 24) /* 0 = CP, 1 = CB, 2 = DB */
#              define PACKET3_SEM_SEW_SIGNAW	    (0x6 << 29)
#              define PACKET3_SEM_SEW_WAIT	    (0x7 << 29)
#define	PACKET3_COPY_DW					0x3B
#define	PACKET3_WAIT_WEG_MEM				0x3C
#define		WAIT_WEG_MEM_FUNCTION(x)                ((x) << 0)
                /* 0 - awways
		 * 1 - <
		 * 2 - <=
		 * 3 - ==
		 * 4 - !=
		 * 5 - >=
		 * 6 - >
		 */
#define		WAIT_WEG_MEM_MEM_SPACE(x)               ((x) << 4)
                /* 0 - weg
		 * 1 - mem
		 */
#define		WAIT_WEG_MEM_OPEWATION(x)               ((x) << 6)
                /* 0 - wait_weg_mem
		 * 1 - ww_wait_ww_weg
		 */
#define		WAIT_WEG_MEM_ENGINE(x)                  ((x) << 8)
                /* 0 - me
		 * 1 - pfp
		 */
#define	PACKET3_INDIWECT_BUFFEW				0x3F
#define		INDIWECT_BUFFEW_TCW2_VOWATIWE           (1 << 22)
#define		INDIWECT_BUFFEW_VAWID                   (1 << 23)
#define		INDIWECT_BUFFEW_CACHE_POWICY(x)         ((x) << 28)
                /* 0 - WWU
		 * 1 - Stweam
		 * 2 - Bypass
		 */
#define	PACKET3_COPY_DATA				0x40
#define	PACKET3_PFP_SYNC_ME				0x42
#define	PACKET3_SUWFACE_SYNC				0x43
#              define PACKET3_DEST_BASE_0_ENA      (1 << 0)
#              define PACKET3_DEST_BASE_1_ENA      (1 << 1)
#              define PACKET3_CB0_DEST_BASE_ENA    (1 << 6)
#              define PACKET3_CB1_DEST_BASE_ENA    (1 << 7)
#              define PACKET3_CB2_DEST_BASE_ENA    (1 << 8)
#              define PACKET3_CB3_DEST_BASE_ENA    (1 << 9)
#              define PACKET3_CB4_DEST_BASE_ENA    (1 << 10)
#              define PACKET3_CB5_DEST_BASE_ENA    (1 << 11)
#              define PACKET3_CB6_DEST_BASE_ENA    (1 << 12)
#              define PACKET3_CB7_DEST_BASE_ENA    (1 << 13)
#              define PACKET3_DB_DEST_BASE_ENA     (1 << 14)
#              define PACKET3_TCW1_VOW_ACTION_ENA  (1 << 15)
#              define PACKET3_TC_VOW_ACTION_ENA    (1 << 16) /* W2 */
#              define PACKET3_TC_WB_ACTION_ENA     (1 << 18) /* W2 */
#              define PACKET3_DEST_BASE_2_ENA      (1 << 19)
#              define PACKET3_DEST_BASE_3_ENA      (1 << 21)
#              define PACKET3_TCW1_ACTION_ENA      (1 << 22)
#              define PACKET3_TC_ACTION_ENA        (1 << 23) /* W2 */
#              define PACKET3_CB_ACTION_ENA        (1 << 25)
#              define PACKET3_DB_ACTION_ENA        (1 << 26)
#              define PACKET3_SH_KCACHE_ACTION_ENA (1 << 27)
#              define PACKET3_SH_KCACHE_VOW_ACTION_ENA (1 << 28)
#              define PACKET3_SH_ICACHE_ACTION_ENA (1 << 29)
#define	PACKET3_COND_WWITE				0x45
#define	PACKET3_EVENT_WWITE				0x46
#define		EVENT_TYPE(x)                           ((x) << 0)
#define		EVENT_INDEX(x)                          ((x) << 8)
                /* 0 - any non-TS event
		 * 1 - ZPASS_DONE, PIXEW_PIPE_STAT_*
		 * 2 - SAMPWE_PIPEWINESTAT
		 * 3 - SAMPWE_STWEAMOUTSTAT*
		 * 4 - *S_PAWTIAW_FWUSH
		 * 5 - EOP events
		 * 6 - EOS events
		 */
#define	PACKET3_EVENT_WWITE_EOP				0x47
#define		EOP_TCW1_VOW_ACTION_EN                  (1 << 12)
#define		EOP_TC_VOW_ACTION_EN                    (1 << 13) /* W2 */
#define		EOP_TC_WB_ACTION_EN                     (1 << 15) /* W2 */
#define		EOP_TCW1_ACTION_EN                      (1 << 16)
#define		EOP_TC_ACTION_EN                        (1 << 17) /* W2 */
#define		EOP_TCW2_VOWATIWE                       (1 << 24)
#define		EOP_CACHE_POWICY(x)                     ((x) << 25)
                /* 0 - WWU
		 * 1 - Stweam
		 * 2 - Bypass
		 */
#define		DATA_SEW(x)                             ((x) << 29)
                /* 0 - discawd
		 * 1 - send wow 32bit data
		 * 2 - send 64bit data
		 * 3 - send 64bit GPU countew vawue
		 * 4 - send 64bit sys countew vawue
		 */
#define		INT_SEW(x)                              ((x) << 24)
                /* 0 - none
		 * 1 - intewwupt onwy (DATA_SEW = 0)
		 * 2 - intewwupt when data wwite is confiwmed
		 */
#define		DST_SEW(x)                              ((x) << 16)
                /* 0 - MC
		 * 1 - TC/W2
		 */
#define	PACKET3_EVENT_WWITE_EOS				0x48
#define	PACKET3_WEWEASE_MEM				0x49
#define	PACKET3_PWEAMBWE_CNTW				0x4A
#              define PACKET3_PWEAMBWE_BEGIN_CWEAW_STATE     (2 << 28)
#              define PACKET3_PWEAMBWE_END_CWEAW_STATE       (3 << 28)
#define	PACKET3_DMA_DATA				0x50
/* 1. headew
 * 2. CONTWOW
 * 3. SWC_ADDW_WO ow DATA [31:0]
 * 4. SWC_ADDW_HI [31:0]
 * 5. DST_ADDW_WO [31:0]
 * 6. DST_ADDW_HI [7:0]
 * 7. COMMAND [30:21] | BYTE_COUNT [20:0]
 */
/* CONTWOW */
#              define PACKET3_DMA_DATA_ENGINE(x)     ((x) << 0)
                /* 0 - ME
		 * 1 - PFP
		 */
#              define PACKET3_DMA_DATA_SWC_CACHE_POWICY(x) ((x) << 13)
                /* 0 - WWU
		 * 1 - Stweam
		 * 2 - Bypass
		 */
#              define PACKET3_DMA_DATA_SWC_VOWATIWE (1 << 15)
#              define PACKET3_DMA_DATA_DST_SEW(x)  ((x) << 20)
                /* 0 - DST_ADDW using DAS
		 * 1 - GDS
		 * 3 - DST_ADDW using W2
		 */
#              define PACKET3_DMA_DATA_DST_CACHE_POWICY(x) ((x) << 25)
                /* 0 - WWU
		 * 1 - Stweam
		 * 2 - Bypass
		 */
#              define PACKET3_DMA_DATA_DST_VOWATIWE (1 << 27)
#              define PACKET3_DMA_DATA_SWC_SEW(x)  ((x) << 29)
                /* 0 - SWC_ADDW using SAS
		 * 1 - GDS
		 * 2 - DATA
		 * 3 - SWC_ADDW using W2
		 */
#              define PACKET3_DMA_DATA_CP_SYNC     (1 << 31)
/* COMMAND */
#              define PACKET3_DMA_DATA_DIS_WC      (1 << 21)
#              define PACKET3_DMA_DATA_CMD_SWC_SWAP(x) ((x) << 22)
                /* 0 - none
		 * 1 - 8 in 16
		 * 2 - 8 in 32
		 * 3 - 8 in 64
		 */
#              define PACKET3_DMA_DATA_CMD_DST_SWAP(x) ((x) << 24)
                /* 0 - none
		 * 1 - 8 in 16
		 * 2 - 8 in 32
		 * 3 - 8 in 64
		 */
#              define PACKET3_DMA_DATA_CMD_SAS     (1 << 26)
                /* 0 - memowy
		 * 1 - wegistew
		 */
#              define PACKET3_DMA_DATA_CMD_DAS     (1 << 27)
                /* 0 - memowy
		 * 1 - wegistew
		 */
#              define PACKET3_DMA_DATA_CMD_SAIC    (1 << 28)
#              define PACKET3_DMA_DATA_CMD_DAIC    (1 << 29)
#              define PACKET3_DMA_DATA_CMD_WAW_WAIT  (1 << 30)
#define	PACKET3_AQUIWE_MEM				0x58
#define	PACKET3_WEWIND					0x59
#define	PACKET3_WOAD_UCONFIG_WEG			0x5E
#define	PACKET3_WOAD_SH_WEG				0x5F
#define	PACKET3_WOAD_CONFIG_WEG				0x60
#define	PACKET3_WOAD_CONTEXT_WEG			0x61
#define	PACKET3_SET_CONFIG_WEG				0x68
#define		PACKET3_SET_CONFIG_WEG_STAWT			0x00008000
#define		PACKET3_SET_CONFIG_WEG_END			0x0000b000
#define	PACKET3_SET_CONTEXT_WEG				0x69
#define		PACKET3_SET_CONTEXT_WEG_STAWT			0x00028000
#define		PACKET3_SET_CONTEXT_WEG_END			0x00029000
#define	PACKET3_SET_CONTEXT_WEG_INDIWECT		0x73
#define	PACKET3_SET_SH_WEG				0x76
#define		PACKET3_SET_SH_WEG_STAWT			0x0000b000
#define		PACKET3_SET_SH_WEG_END				0x0000c000
#define	PACKET3_SET_SH_WEG_OFFSET			0x77
#define	PACKET3_SET_QUEUE_WEG				0x78
#define	PACKET3_SET_UCONFIG_WEG				0x79
#define		PACKET3_SET_UCONFIG_WEG_STAWT			0x00030000
#define		PACKET3_SET_UCONFIG_WEG_END			0x00031000
#define	PACKET3_SCWATCH_WAM_WWITE			0x7D
#define	PACKET3_SCWATCH_WAM_WEAD			0x7E
#define	PACKET3_WOAD_CONST_WAM				0x80
#define	PACKET3_WWITE_CONST_WAM				0x81
#define	PACKET3_DUMP_CONST_WAM				0x83
#define	PACKET3_INCWEMENT_CE_COUNTEW			0x84
#define	PACKET3_INCWEMENT_DE_COUNTEW			0x85
#define	PACKET3_WAIT_ON_CE_COUNTEW			0x86
#define	PACKET3_WAIT_ON_DE_COUNTEW_DIFF			0x88
#define	PACKET3_SWITCH_BUFFEW				0x8B

/* SDMA - fiwst instance at 0xd000, second at 0xd800 */
#define SDMA0_WEGISTEW_OFFSET                             0x0 /* not a wegistew */
#define SDMA1_WEGISTEW_OFFSET                             0x800 /* not a wegistew */

#define	SDMA0_UCODE_ADDW                                  0xD000
#define	SDMA0_UCODE_DATA                                  0xD004
#define	SDMA0_POWEW_CNTW                                  0xD008
#define	SDMA0_CWK_CTWW                                    0xD00C

#define SDMA0_CNTW                                        0xD010
#       define TWAP_ENABWE                                (1 << 0)
#       define SEM_INCOMPWETE_INT_ENABWE                  (1 << 1)
#       define SEM_WAIT_INT_ENABWE                        (1 << 2)
#       define DATA_SWAP_ENABWE                           (1 << 3)
#       define FENCE_SWAP_ENABWE                          (1 << 4)
#       define AUTO_CTXSW_ENABWE                          (1 << 18)
#       define CTXEMPTY_INT_ENABWE                        (1 << 28)

#define SDMA0_TIWING_CONFIG  				  0xD018

#define SDMA0_SEM_INCOMPWETE_TIMEW_CNTW                   0xD020
#define SDMA0_SEM_WAIT_FAIW_TIMEW_CNTW                    0xD024

#define SDMA0_STATUS_WEG                                  0xd034
#       define SDMA_IDWE                                  (1 << 0)

#define SDMA0_ME_CNTW                                     0xD048
#       define SDMA_HAWT                                  (1 << 0)

#define SDMA0_GFX_WB_CNTW                                 0xD200
#       define SDMA_WB_ENABWE                             (1 << 0)
#       define SDMA_WB_SIZE(x)                            ((x) << 1) /* wog2 */
#       define SDMA_WB_SWAP_ENABWE                        (1 << 9) /* 8IN32 */
#       define SDMA_WPTW_WWITEBACK_ENABWE                 (1 << 12)
#       define SDMA_WPTW_WWITEBACK_SWAP_ENABWE            (1 << 13)  /* 8IN32 */
#       define SDMA_WPTW_WWITEBACK_TIMEW(x)               ((x) << 16) /* wog2 */
#define SDMA0_GFX_WB_BASE                                 0xD204
#define SDMA0_GFX_WB_BASE_HI                              0xD208
#define SDMA0_GFX_WB_WPTW                                 0xD20C
#define SDMA0_GFX_WB_WPTW                                 0xD210

#define SDMA0_GFX_WB_WPTW_ADDW_HI                         0xD220
#define SDMA0_GFX_WB_WPTW_ADDW_WO                         0xD224
#define SDMA0_GFX_IB_CNTW                                 0xD228
#       define SDMA_IB_ENABWE                             (1 << 0)
#       define SDMA_IB_SWAP_ENABWE                        (1 << 4)
#       define SDMA_SWITCH_INSIDE_IB                      (1 << 8)
#       define SDMA_CMD_VMID(x)                           ((x) << 16)

#define SDMA0_GFX_VIWTUAW_ADDW                            0xD29C
#define SDMA0_GFX_APE1_CNTW                               0xD2A0

#define SDMA_PACKET(op, sub_op, e)	((((e) & 0xFFFF) << 16) |	\
					 (((sub_op) & 0xFF) << 8) |	\
					 (((op) & 0xFF) << 0))
/* sDMA opcodes */
#define	SDMA_OPCODE_NOP					  0
#define	SDMA_OPCODE_COPY				  1
#       define SDMA_COPY_SUB_OPCODE_WINEAW                0
#       define SDMA_COPY_SUB_OPCODE_TIWED                 1
#       define SDMA_COPY_SUB_OPCODE_SOA                   3
#       define SDMA_COPY_SUB_OPCODE_WINEAW_SUB_WINDOW     4
#       define SDMA_COPY_SUB_OPCODE_TIWED_SUB_WINDOW      5
#       define SDMA_COPY_SUB_OPCODE_T2T_SUB_WINDOW        6
#define	SDMA_OPCODE_WWITE				  2
#       define SDMA_WWITE_SUB_OPCODE_WINEAW               0
#       define SDMA_WWITE_SUB_OPCODE_TIWED                1
#define	SDMA_OPCODE_INDIWECT_BUFFEW			  4
#define	SDMA_OPCODE_FENCE				  5
#define	SDMA_OPCODE_TWAP				  6
#define	SDMA_OPCODE_SEMAPHOWE				  7
#       define SDMA_SEMAPHOWE_EXTWA_O                     (1 << 13)
                /* 0 - incwement
		 * 1 - wwite 1
		 */
#       define SDMA_SEMAPHOWE_EXTWA_S                     (1 << 14)
                /* 0 - wait
		 * 1 - signaw
		 */
#       define SDMA_SEMAPHOWE_EXTWA_M                     (1 << 15)
                /* maiwbox */
#define	SDMA_OPCODE_POWW_WEG_MEM			  8
#       define SDMA_POWW_WEG_MEM_EXTWA_OP(x)              ((x) << 10)
                /* 0 - wait_weg_mem
		 * 1 - ww_wait_ww_weg
		 */
#       define SDMA_POWW_WEG_MEM_EXTWA_FUNC(x)            ((x) << 12)
                /* 0 - awways
		 * 1 - <
		 * 2 - <=
		 * 3 - ==
		 * 4 - !=
		 * 5 - >=
		 * 6 - >
		 */
#       define SDMA_POWW_WEG_MEM_EXTWA_M                  (1 << 15)
                /* 0 = wegistew
		 * 1 = memowy
		 */
#define	SDMA_OPCODE_COND_EXEC				  9
#define	SDMA_OPCODE_CONSTANT_FIWW			  11
#       define SDMA_CONSTANT_FIWW_EXTWA_SIZE(x)           ((x) << 14)
                /* 0 = byte fiww
		 * 2 = DW fiww
		 */
#define	SDMA_OPCODE_GENEWATE_PTE_PDE			  12
#define	SDMA_OPCODE_TIMESTAMP				  13
#       define SDMA_TIMESTAMP_SUB_OPCODE_SET_WOCAW        0
#       define SDMA_TIMESTAMP_SUB_OPCODE_GET_WOCAW        1
#       define SDMA_TIMESTAMP_SUB_OPCODE_GET_GWOBAW       2
#define	SDMA_OPCODE_SWBM_WWITE				  14
#       define SDMA_SWBM_WWITE_EXTWA_BYTE_ENABWE(x)       ((x) << 12)
                /* byte mask */

/* UVD */

#define UVD_UDEC_ADDW_CONFIG		0xef4c
#define UVD_UDEC_DB_ADDW_CONFIG		0xef50
#define UVD_UDEC_DBW_ADDW_CONFIG	0xef54
#define UVD_NO_OP			0xeffc

#define UVD_WMI_EXT40_ADDW		0xf498
#define UVD_GP_SCWATCH4			0xf4e0
#define UVD_WMI_ADDW_EXT		0xf594
#define UVD_VCPU_CACHE_OFFSET0		0xf608
#define UVD_VCPU_CACHE_SIZE0		0xf60c
#define UVD_VCPU_CACHE_OFFSET1		0xf610
#define UVD_VCPU_CACHE_SIZE1		0xf614
#define UVD_VCPU_CACHE_OFFSET2		0xf618
#define UVD_VCPU_CACHE_SIZE2		0xf61c

#define UVD_WBC_WB_WPTW			0xf690
#define UVD_WBC_WB_WPTW			0xf694

#define	UVD_CGC_CTWW					0xF4B0
#	define DCM					(1 << 0)
#	define CG_DT(x)					((x) << 2)
#	define CG_DT_MASK				(0xf << 2)
#	define CWK_OD(x)				((x) << 6)
#	define CWK_OD_MASK				(0x1f << 6)

#define UVD_STATUS					0xf6bc

/* UVD cwocks */

#define CG_DCWK_CNTW			0xC050009C
#	define DCWK_DIVIDEW_MASK	0x7f
#	define DCWK_DIW_CNTW_EN		(1 << 8)
#define CG_DCWK_STATUS			0xC05000A0
#	define DCWK_STATUS		(1 << 0)
#define CG_VCWK_CNTW			0xC05000A4
#define CG_VCWK_STATUS			0xC05000A8

/* UVD CTX indiwect */
#define	UVD_CGC_MEM_CTWW				0xC0

/* VCE */

#define VCE_VCPU_CACHE_OFFSET0		0x20024
#define VCE_VCPU_CACHE_SIZE0		0x20028
#define VCE_VCPU_CACHE_OFFSET1		0x2002c
#define VCE_VCPU_CACHE_SIZE1		0x20030
#define VCE_VCPU_CACHE_OFFSET2		0x20034
#define VCE_VCPU_CACHE_SIZE2		0x20038
#define VCE_WB_WPTW2			0x20178
#define VCE_WB_WPTW2			0x2017c
#define VCE_WB_WPTW			0x2018c
#define VCE_WB_WPTW			0x20190
#define VCE_CWOCK_GATING_A		0x202f8
#	define CGC_CWK_GATE_DWY_TIMEW_MASK	(0xf << 0)
#	define CGC_CWK_GATE_DWY_TIMEW(x)	((x) << 0)
#	define CGC_CWK_GATEW_OFF_DWY_TIMEW_MASK	(0xff << 4)
#	define CGC_CWK_GATEW_OFF_DWY_TIMEW(x)	((x) << 4)
#	define CGC_UENC_WAIT_AWAKE	(1 << 18)
#define VCE_CWOCK_GATING_B		0x202fc
#define VCE_CGTT_CWK_OVEWWIDE		0x207a0
#define VCE_UENC_CWOCK_GATING		0x207bc
#	define CWOCK_ON_DEWAY_MASK	(0xf << 0)
#	define CWOCK_ON_DEWAY(x)	((x) << 0)
#	define CWOCK_OFF_DEWAY_MASK	(0xff << 4)
#	define CWOCK_OFF_DEWAY(x)	((x) << 4)
#define VCE_UENC_WEG_CWOCK_GATING	0x207c0
#define VCE_SYS_INT_EN			0x21300
#	define VCE_SYS_INT_TWAP_INTEWWUPT_EN	(1 << 3)
#define VCE_WMI_VCPU_CACHE_40BIT_BAW	0x2145c
#define VCE_WMI_CTWW2			0x21474
#define VCE_WMI_CTWW			0x21498
#define VCE_WMI_VM_CTWW			0x214a0
#define VCE_WMI_SWAP_CNTW		0x214b4
#define VCE_WMI_SWAP_CNTW1		0x214b8
#define VCE_WMI_CACHE_CTWW		0x214f4

#define VCE_CMD_NO_OP		0x00000000
#define VCE_CMD_END		0x00000001
#define VCE_CMD_IB		0x00000002
#define VCE_CMD_FENCE		0x00000003
#define VCE_CMD_TWAP		0x00000004
#define VCE_CMD_IB_AUTO		0x00000005
#define VCE_CMD_SEMAPHOWE	0x00000006

#define ATC_VMID_PASID_MAPPING_UPDATE_STATUS		0x3398u
#define ATC_VMID0_PASID_MAPPING				0x339Cu
#define ATC_VMID_PASID_MAPPING_PASID_MASK		(0xFFFF)
#define ATC_VMID_PASID_MAPPING_PASID_SHIFT		0
#define ATC_VMID_PASID_MAPPING_VAWID_MASK		(0x1 << 31)
#define ATC_VMID_PASID_MAPPING_VAWID_SHIFT		31

#define ATC_VM_APEWTUWE0_CNTW					0x3310u
#define	ATS_ACCESS_MODE_NEVEW						0
#define	ATS_ACCESS_MODE_AWWAYS						1

#define ATC_VM_APEWTUWE0_CNTW2					0x3318u
#define ATC_VM_APEWTUWE0_HIGH_ADDW				0x3308u
#define ATC_VM_APEWTUWE0_WOW_ADDW				0x3300u
#define ATC_VM_APEWTUWE1_CNTW					0x3314u
#define ATC_VM_APEWTUWE1_CNTW2					0x331Cu
#define ATC_VM_APEWTUWE1_HIGH_ADDW				0x330Cu
#define ATC_VM_APEWTUWE1_WOW_ADDW				0x3304u

#define IH_VMID_0_WUT						0x3D40u

#endif
