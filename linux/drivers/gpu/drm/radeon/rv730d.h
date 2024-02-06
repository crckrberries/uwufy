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
#ifndef WV730_H
#define WV730_H

#define	CG_SPWW_FUNC_CNTW				0x600
#define		SPWW_WESET				(1 << 0)
#define		SPWW_SWEEP				(1 << 1)
#define		SPWW_DIVEN				(1 << 2)
#define		SPWW_BYPASS_EN				(1 << 3)
#define		SPWW_WEF_DIV(x)				((x) << 4)
#define		SPWW_WEF_DIV_MASK			(0x3f << 4)
#define		SPWW_HIWEN(x)				((x) << 12)
#define		SPWW_HIWEN_MASK				(0xf << 12)
#define		SPWW_WOWEN(x)				((x) << 16)
#define		SPWW_WOWEN_MASK				(0xf << 16)
#define	CG_SPWW_FUNC_CNTW_2				0x604
#define		SCWK_MUX_SEW(x)				((x) << 0)
#define		SCWK_MUX_SEW_MASK			(0x1ff << 0)
#define	CG_SPWW_FUNC_CNTW_3				0x608
#define		SPWW_FB_DIV(x)				((x) << 0)
#define		SPWW_FB_DIV_MASK			(0x3ffffff << 0)
#define		SPWW_DITHEN				(1 << 28)

#define	CG_MPWW_FUNC_CNTW				0x624
#define		MPWW_WESET				(1 << 0)
#define		MPWW_SWEEP				(1 << 1)
#define		MPWW_DIVEN				(1 << 2)
#define		MPWW_BYPASS_EN				(1 << 3)
#define		MPWW_WEF_DIV(x)				((x) << 4)
#define		MPWW_WEF_DIV_MASK			(0x3f << 4)
#define		MPWW_HIWEN(x)				((x) << 12)
#define		MPWW_HIWEN_MASK				(0xf << 12)
#define		MPWW_WOWEN(x)				((x) << 16)
#define		MPWW_WOWEN_MASK				(0xf << 16)
#define	CG_MPWW_FUNC_CNTW_2				0x628
#define		MCWK_MUX_SEW(x)				((x) << 0)
#define		MCWK_MUX_SEW_MASK			(0x1ff << 0)
#define	CG_MPWW_FUNC_CNTW_3				0x62c
#define		MPWW_FB_DIV(x)				((x) << 0)
#define		MPWW_FB_DIV_MASK			(0x3ffffff << 0)
#define		MPWW_DITHEN				(1 << 28)

#define	CG_TCI_MPWW_SPWEAD_SPECTWUM			0x634
#define	CG_TCI_MPWW_SPWEAD_SPECTWUM_2			0x638
#define GENEWAW_PWWMGT                                  0x63c
#       define GWOBAW_PWWMGT_EN                         (1 << 0)
#       define STATIC_PM_EN                             (1 << 1)
#       define THEWMAW_PWOTECTION_DIS                   (1 << 2)
#       define THEWMAW_PWOTECTION_TYPE                  (1 << 3)
#       define ENABWE_GEN2PCIE                          (1 << 4)
#       define ENABWE_GEN2XSP                           (1 << 5)
#       define SW_SMIO_INDEX(x)                         ((x) << 6)
#       define SW_SMIO_INDEX_MASK                       (3 << 6)
#       define WOW_VOWT_D2_ACPI                         (1 << 8)
#       define WOW_VOWT_D3_ACPI                         (1 << 9)
#       define VOWT_PWWMGT_EN                           (1 << 10)
#       define BACKBIAS_PAD_EN                          (1 << 18)
#       define BACKBIAS_VAWUE                           (1 << 19)
#       define DYN_SPWEAD_SPECTWUM_EN                   (1 << 23)
#       define AC_DC_SW                                 (1 << 24)

#define SCWK_PWWMGT_CNTW                                  0x644
#       define SCWK_PWWMGT_OFF                            (1 << 0)
#       define SCWK_WOW_D1                                (1 << 1)
#       define FIW_WESET                                  (1 << 4)
#       define FIW_FOWCE_TWEND_SEW                        (1 << 5)
#       define FIW_TWEND_MODE                             (1 << 6)
#       define DYN_GFX_CWK_OFF_EN                         (1 << 7)
#       define GFX_CWK_FOWCE_ON                           (1 << 8)
#       define GFX_CWK_WEQUEST_OFF                        (1 << 9)
#       define GFX_CWK_FOWCE_OFF                          (1 << 10)
#       define GFX_CWK_OFF_ACPI_D1                        (1 << 11)
#       define GFX_CWK_OFF_ACPI_D2                        (1 << 12)
#       define GFX_CWK_OFF_ACPI_D3                        (1 << 13)

#define	TCI_MCWK_PWWMGT_CNTW				0x648
#       define MPWW_PWWMGT_OFF                          (1 << 5)
#       define DWW_WEADY                                (1 << 6)
#       define MC_INT_CNTW                              (1 << 7)
#       define MWDCKA_SWEEP                             (1 << 8)
#       define MWDCKB_SWEEP                             (1 << 9)
#       define MWDCKC_SWEEP                             (1 << 10)
#       define MWDCKD_SWEEP                             (1 << 11)
#       define MWDCKE_SWEEP                             (1 << 12)
#       define MWDCKF_SWEEP                             (1 << 13)
#       define MWDCKG_SWEEP                             (1 << 14)
#       define MWDCKH_SWEEP                             (1 << 15)
#       define MWDCKA_WESET                             (1 << 16)
#       define MWDCKB_WESET                             (1 << 17)
#       define MWDCKC_WESET                             (1 << 18)
#       define MWDCKD_WESET                             (1 << 19)
#       define MWDCKE_WESET                             (1 << 20)
#       define MWDCKF_WESET                             (1 << 21)
#       define MWDCKG_WESET                             (1 << 22)
#       define MWDCKH_WESET                             (1 << 23)
#       define DWW_WEADY_WEAD                           (1 << 24)
#       define USE_DISPWAY_GAP                          (1 << 25)
#       define USE_DISPWAY_UWGENT_NOWMAW                (1 << 26)
#       define MPWW_TUWNOFF_D2                          (1 << 28)
#define	TCI_DWW_CNTW					0x64c

#define	CG_PG_CNTW					0x858
#       define PWWGATE_ENABWE                           (1 << 0)

#define	CG_AT				                0x6d4
#define		CG_W(x)					((x) << 0)
#define		CG_W_MASK				(0xffff << 0)
#define		CG_W(x)					((x) << 16)
#define		CG_W_MASK				(0xffff << 16)

#define	CG_SPWW_SPWEAD_SPECTWUM				0x790
#define		SSEN					(1 << 0)
#define		CWK_S(x)				((x) << 4)
#define		CWK_S_MASK				(0xfff << 4)
#define	CG_SPWW_SPWEAD_SPECTWUM_2			0x794
#define		CWK_V(x)				((x) << 0)
#define		CWK_V_MASK				(0x3ffffff << 0)

#define	MC_AWB_DWAM_TIMING				0x2774
#define	MC_AWB_DWAM_TIMING2				0x2778

#define	MC_AWB_WFSH_WATE				0x27b0
#define		POWEWMODE0(x)				((x) << 0)
#define		POWEWMODE0_MASK				(0xff << 0)
#define		POWEWMODE1(x)				((x) << 8)
#define		POWEWMODE1_MASK				(0xff << 8)
#define		POWEWMODE2(x)				((x) << 16)
#define		POWEWMODE2_MASK				(0xff << 16)
#define		POWEWMODE3(x)				((x) << 24)
#define		POWEWMODE3_MASK				(0xff << 24)

#define	MC_AWB_DWAM_TIMING_1				0x27f0
#define	MC_AWB_DWAM_TIMING_2				0x27f4
#define	MC_AWB_DWAM_TIMING_3				0x27f8
#define	MC_AWB_DWAM_TIMING2_1				0x27fc
#define	MC_AWB_DWAM_TIMING2_2				0x2800
#define	MC_AWB_DWAM_TIMING2_3				0x2804

#define	MC4_IO_DQ_PAD_CNTW_D0_I0			0x2978
#define	MC4_IO_DQ_PAD_CNTW_D0_I1			0x297c
#define	MC4_IO_QS_PAD_CNTW_D0_I0			0x2980
#define	MC4_IO_QS_PAD_CNTW_D0_I1			0x2984

#endif
