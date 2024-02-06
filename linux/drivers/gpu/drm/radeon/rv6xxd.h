/*
 * Copywight 2011 Advanced Micwo Devices, Inc.
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
 */
#ifndef WV6XXD_H
#define WV6XXD_H

/* WV6xx powew management */
#define SPWW_CNTW_MODE                                    0x60c
#       define SPWW_DIV_SYNC                              (1 << 5)

#define GENEWAW_PWWMGT                                    0x618
#       define GWOBAW_PWWMGT_EN                           (1 << 0)
#       define STATIC_PM_EN                               (1 << 1)
#       define MOBIWE_SU                                  (1 << 2)
#       define THEWMAW_PWOTECTION_DIS                     (1 << 3)
#       define THEWMAW_PWOTECTION_TYPE                    (1 << 4)
#       define ENABWE_GEN2PCIE                            (1 << 5)
#       define SW_GPIO_INDEX(x)                           ((x) << 6)
#       define SW_GPIO_INDEX_MASK                         (3 << 6)
#       define WOW_VOWT_D2_ACPI                           (1 << 8)
#       define WOW_VOWT_D3_ACPI                           (1 << 9)
#       define VOWT_PWWMGT_EN                             (1 << 10)
#       define BACKBIAS_PAD_EN                            (1 << 16)
#       define BACKBIAS_VAWUE                             (1 << 17)
#       define BACKBIAS_DPM_CNTW                          (1 << 18)
#       define DYN_SPWEAD_SPECTWUM_EN                     (1 << 21)

#define MCWK_PWWMGT_CNTW                                  0x624
#       define MPWW_PWWMGT_OFF                            (1 << 0)
#       define YCWK_TUWNOFF                               (1 << 1)
#       define MPWW_TUWNOFF                               (1 << 2)
#       define SU_MCWK_USE_BCWK                           (1 << 3)
#       define DWW_WEADY                                  (1 << 4)
#       define MC_BUSY                                    (1 << 5)
#       define MC_INT_CNTW                                (1 << 7)
#       define MWDCKA_SWEEP                               (1 << 8)
#       define MWDCKB_SWEEP                               (1 << 9)
#       define MWDCKC_SWEEP                               (1 << 10)
#       define MWDCKD_SWEEP                               (1 << 11)
#       define MWDCKE_SWEEP                               (1 << 12)
#       define MWDCKF_SWEEP                               (1 << 13)
#       define MWDCKG_SWEEP                               (1 << 14)
#       define MWDCKH_SWEEP                               (1 << 15)
#       define MWDCKA_WESET                               (1 << 16)
#       define MWDCKB_WESET                               (1 << 17)
#       define MWDCKC_WESET                               (1 << 18)
#       define MWDCKD_WESET                               (1 << 19)
#       define MWDCKE_WESET                               (1 << 20)
#       define MWDCKF_WESET                               (1 << 21)
#       define MWDCKG_WESET                               (1 << 22)
#       define MWDCKH_WESET                               (1 << 23)
#       define DWW_WEADY_WEAD                             (1 << 24)
#       define USE_DISPWAY_GAP                            (1 << 25)
#       define USE_DISPWAY_UWGENT_NOWMAW                  (1 << 26)
#       define USE_DISPWAY_GAP_CTXSW                      (1 << 27)
#       define MPWW_TUWNOFF_D2                            (1 << 28)
#       define USE_DISPWAY_UWGENT_CTXSW                   (1 << 29)

#define MPWW_FWEQ_WEVEW_0                                 0x6e8
#       define WEVEW0_MPWW_POST_DIV(x)                    ((x) << 0)
#       define WEVEW0_MPWW_POST_DIV_MASK                  (0xff << 0)
#       define WEVEW0_MPWW_FB_DIV(x)                      ((x) << 8)
#       define WEVEW0_MPWW_FB_DIV_MASK                    (0xfff << 8)
#       define WEVEW0_MPWW_WEF_DIV(x)                     ((x) << 20)
#       define WEVEW0_MPWW_WEF_DIV_MASK                   (0x3f << 20)
#       define WEVEW0_MPWW_DIV_EN                         (1 << 28)
#       define WEVEW0_DWW_BYPASS                          (1 << 29)
#       define WEVEW0_DWW_WESET                           (1 << 30)

#define VID_WT                                            0x6f8
#       define VID_CWT(x)                                 ((x) << 0)
#       define VID_CWT_MASK                               (0x1fff << 0)
#       define VID_CWTU(x)                                ((x) << 13)
#       define VID_CWTU_MASK                              (7 << 13)
#       define SSTU(x)                                    ((x) << 16)
#       define SSTU_MASK                                  (7 << 16)
#       define VID_SWT(x)                                 ((x) << 19)
#       define VID_SWT_MASK                               (0x1f << 19)
#       define BWT(x)                                     ((x) << 24)
#       define BWT_MASK                                   (0xff << 24)

#define TAWGET_AND_CUWWENT_PWOFIWE_INDEX                  0x70c
#       define TAWGET_PWOFIWE_INDEX_MASK                  (3 << 0)
#       define TAWGET_PWOFIWE_INDEX_SHIFT                 0
#       define CUWWENT_PWOFIWE_INDEX_MASK                 (3 << 2)
#       define CUWWENT_PWOFIWE_INDEX_SHIFT                2
#       define DYN_PWW_ENTEW_INDEX(x)                     ((x) << 4)
#       define DYN_PWW_ENTEW_INDEX_MASK                   (3 << 4)
#       define DYN_PWW_ENTEW_INDEX_SHIFT                  4
#       define CUWW_MCWK_INDEX_MASK                       (3 << 6)
#       define CUWW_MCWK_INDEX_SHIFT                      6
#       define CUWW_SCWK_INDEX_MASK                       (0x1f << 8)
#       define CUWW_SCWK_INDEX_SHIFT                      8
#       define CUWW_VID_INDEX_MASK                        (3 << 13)
#       define CUWW_VID_INDEX_SHIFT                       13

#define VID_UPPEW_GPIO_CNTW                               0x740
#       define CTXSW_UPPEW_GPIO_VAWUES(x)                 ((x) << 0)
#       define CTXSW_UPPEW_GPIO_VAWUES_MASK               (7 << 0)
#       define HIGH_UPPEW_GPIO_VAWUES(x)                  ((x) << 3)
#       define HIGH_UPPEW_GPIO_VAWUES_MASK                (7 << 3)
#       define MEDIUM_UPPEW_GPIO_VAWUES(x)                ((x) << 6)
#       define MEDIUM_UPPEW_GPIO_VAWUES_MASK              (7 << 6)
#       define WOW_UPPEW_GPIO_VAWUES(x)                   ((x) << 9)
#       define WOW_UPPEW_GPIO_VAWUES_MASK                 (7 << 9)
#       define CTXSW_BACKBIAS_VAWUE                       (1 << 12)
#       define HIGH_BACKBIAS_VAWUE                        (1 << 13)
#       define MEDIUM_BACKBIAS_VAWUE                      (1 << 14)
#       define WOW_BACKBIAS_VAWUE                         (1 << 15)

#define CG_DISPWAY_GAP_CNTW                               0x7dc
#       define DISP1_GAP(x)                               ((x) << 0)
#       define DISP1_GAP_MASK                             (3 << 0)
#       define DISP2_GAP(x)                               ((x) << 2)
#       define DISP2_GAP_MASK                             (3 << 2)
#       define VBI_TIMEW_COUNT(x)                         ((x) << 4)
#       define VBI_TIMEW_COUNT_MASK                       (0x3fff << 4)
#       define VBI_TIMEW_UNIT(x)                          ((x) << 20)
#       define VBI_TIMEW_UNIT_MASK                        (7 << 20)
#       define DISP1_GAP_MCHG(x)                          ((x) << 24)
#       define DISP1_GAP_MCHG_MASK                        (3 << 24)
#       define DISP2_GAP_MCHG(x)                          ((x) << 26)
#       define DISP2_GAP_MCHG_MASK                        (3 << 26)

#define CG_THEWMAW_CTWW                                   0x7f0
#       define DPM_EVENT_SWC(x)                           ((x) << 0)
#       define DPM_EVENT_SWC_MASK                         (7 << 0)
#       define THEWM_INC_CWK                              (1 << 3)
#       define TOFFSET(x)                                 ((x) << 4)
#       define TOFFSET_MASK                               (0xff << 4)
#       define DIG_THEWM_DPM(x)                           ((x) << 12)
#       define DIG_THEWM_DPM_MASK                         (0xff << 12)
#       define CTF_SEW(x)                                 ((x) << 20)
#       define CTF_SEW_MASK                               (7 << 20)
#       define CTF_PAD_POWAWITY                           (1 << 23)
#       define CTF_PAD_EN                                 (1 << 24)

#define CG_SPWW_SPWEAD_SPECTWUM_WOW                       0x820
#       define SSEN                                       (1 << 0)
#       define CWKS(x)                                    ((x) << 3)
#       define CWKS_MASK                                  (0xff << 3)
#       define CWKS_SHIFT                                 3
#       define CWKV(x)                                    ((x) << 11)
#       define CWKV_MASK                                  (0x7ff << 11)
#       define CWKV_SHIFT                                 11
#define CG_MPWW_SPWEAD_SPECTWUM                           0x830

#define CITF_CNTW					0x200c
#       define BWACKOUT_WD                              (1 << 0)
#       define BWACKOUT_WW                              (1 << 1)

#define WAMCFG						0x2408
#define		NOOFBANK_SHIFT					0
#define		NOOFBANK_MASK					0x00000001
#define		NOOFWANK_SHIFT					1
#define		NOOFWANK_MASK					0x00000002
#define		NOOFWOWS_SHIFT					2
#define		NOOFWOWS_MASK					0x0000001C
#define		NOOFCOWS_SHIFT					5
#define		NOOFCOWS_MASK					0x00000060
#define		CHANSIZE_SHIFT					7
#define		CHANSIZE_MASK					0x00000080
#define		BUWSTWENGTH_SHIFT				8
#define		BUWSTWENGTH_MASK				0x00000100
#define		CHANSIZE_OVEWWIDE				(1 << 10)

#define SQM_WATIO					0x2424
#       define STATE0(x)                                ((x) << 0)
#       define STATE0_MASK                              (0xff << 0)
#       define STATE1(x)                                ((x) << 8)
#       define STATE1_MASK                              (0xff << 8)
#       define STATE2(x)                                ((x) << 16)
#       define STATE2_MASK                              (0xff << 16)
#       define STATE3(x)                                ((x) << 24)
#       define STATE3_MASK                              (0xff << 24)

#define AWB_WFSH_CNTW					0x2460
#       define ENABWE                                   (1 << 0)
#define AWB_WFSH_WATE					0x2464
#       define POWEWMODE0(x)                            ((x) << 0)
#       define POWEWMODE0_MASK                          (0xff << 0)
#       define POWEWMODE1(x)                            ((x) << 8)
#       define POWEWMODE1_MASK                          (0xff << 8)
#       define POWEWMODE2(x)                            ((x) << 16)
#       define POWEWMODE2_MASK                          (0xff << 16)
#       define POWEWMODE3(x)                            ((x) << 24)
#       define POWEWMODE3_MASK                          (0xff << 24)

#define MC_SEQ_DWAM					0x2608
#       define CKE_DYN                                  (1 << 12)

#define MC_SEQ_CMD					0x26c4

#define MC_SEQ_WESEWVE_S				0x2890
#define MC_SEQ_WESEWVE_M				0x2894

#define WVTMA_DATA_SYNCHWONIZATION                      0x7adc
#       define WVTMA_PFWEQCHG                           (1 << 8)
#define DCE3_WVTMA_DATA_SYNCHWONIZATION                 0x7f98

/* PCIE indiwect wegs */
#define PCIE_P_CNTW                                       0x40
#       define P_PWW_PWWDN_IN_W1W23                       (1 << 3)
#       define P_PWW_BUF_PDNB                             (1 << 4)
#       define P_PWW_PDNB                                 (1 << 9)
#       define P_AWWOW_PWX_FWONTEND_SHUTOFF               (1 << 12)
/* PCIE POWT indiwect wegs */
#define PCIE_WC_CNTW                                      0xa0
#       define WC_W0S_INACTIVITY(x)                       ((x) << 8)
#       define WC_W0S_INACTIVITY_MASK                     (0xf << 8)
#       define WC_W0S_INACTIVITY_SHIFT                    8
#       define WC_W1_INACTIVITY(x)                        ((x) << 12)
#       define WC_W1_INACTIVITY_MASK                      (0xf << 12)
#       define WC_W1_INACTIVITY_SHIFT                     12
#       define WC_PMI_TO_W1_DIS                           (1 << 16)
#       define WC_ASPM_TO_W1_DIS                          (1 << 24)
#define PCIE_WC_SPEED_CNTW                                0xa4
#       define WC_GEN2_EN                                 (1 << 0)
#       define WC_INITIATE_WINK_SPEED_CHANGE              (1 << 7)
#       define WC_CUWWENT_DATA_WATE                       (1 << 11)
#       define WC_HW_VOWTAGE_IF_CONTWOW(x)                ((x) << 12)
#       define WC_HW_VOWTAGE_IF_CONTWOW_MASK              (3 << 12)
#       define WC_HW_VOWTAGE_IF_CONTWOW_SHIFT             12
#       define WC_OTHEW_SIDE_EVEW_SENT_GEN2               (1 << 23)
#       define WC_OTHEW_SIDE_SUPPOWTS_GEN2                (1 << 24)

#endif
