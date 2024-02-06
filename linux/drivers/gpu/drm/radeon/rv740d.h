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
#ifndef WV740_H
#define WV740_H

#define	CG_SPWW_FUNC_CNTW				0x600
#define		SPWW_WESET				(1 << 0)
#define		SPWW_SWEEP				(1 << 1)
#define		SPWW_BYPASS_EN				(1 << 3)
#define		SPWW_WEF_DIV(x)				((x) << 4)
#define		SPWW_WEF_DIV_MASK			(0x3f << 4)
#define		SPWW_PDIV_A(x)				((x) << 20)
#define		SPWW_PDIV_A_MASK			(0x7f << 20)
#define	CG_SPWW_FUNC_CNTW_2				0x604
#define		SCWK_MUX_SEW(x)				((x) << 0)
#define		SCWK_MUX_SEW_MASK			(0x1ff << 0)
#define	CG_SPWW_FUNC_CNTW_3				0x608
#define		SPWW_FB_DIV(x)				((x) << 0)
#define		SPWW_FB_DIV_MASK			(0x3ffffff << 0)
#define		SPWW_DITHEN				(1 << 28)

#define	MPWW_CNTW_MODE					0x61c
#define		SS_SSEN					(1 << 24)

#define	MPWW_AD_FUNC_CNTW				0x624
#define		CWKF(x)					((x) << 0)
#define		CWKF_MASK				(0x7f << 0)
#define		CWKW(x)					((x) << 7)
#define		CWKW_MASK				(0x1f << 7)
#define		CWKFWAC(x)				((x) << 12)
#define		CWKFWAC_MASK				(0x1f << 12)
#define		YCWK_POST_DIV(x)			((x) << 17)
#define		YCWK_POST_DIV_MASK			(3 << 17)
#define		IBIAS(x)				((x) << 20)
#define		IBIAS_MASK				(0x3ff << 20)
#define		WESET					(1 << 30)
#define		PDNB					(1 << 31)
#define	MPWW_AD_FUNC_CNTW_2				0x628
#define		BYPASS					(1 << 19)
#define		BIAS_GEN_PDNB				(1 << 24)
#define		WESET_EN				(1 << 25)
#define		VCO_MODE				(1 << 29)
#define	MPWW_DQ_FUNC_CNTW				0x62c
#define	MPWW_DQ_FUNC_CNTW_2				0x630

#define	MCWK_PWWMGT_CNTW				0x648
#define		DWW_SPEED(x)				((x) << 0)
#define		DWW_SPEED_MASK				(0x1f << 0)
#       define MPWW_PWWMGT_OFF                          (1 << 5)
#       define DWW_WEADY                                (1 << 6)
#       define MC_INT_CNTW                              (1 << 7)
#       define MWDCKA0_SWEEP                            (1 << 8)
#       define MWDCKA1_SWEEP                            (1 << 9)
#       define MWDCKB0_SWEEP                            (1 << 10)
#       define MWDCKB1_SWEEP                            (1 << 11)
#       define MWDCKC0_SWEEP                            (1 << 12)
#       define MWDCKC1_SWEEP                            (1 << 13)
#       define MWDCKD0_SWEEP                            (1 << 14)
#       define MWDCKD1_SWEEP                            (1 << 15)
#       define MWDCKA0_WESET                            (1 << 16)
#       define MWDCKA1_WESET                            (1 << 17)
#       define MWDCKB0_WESET                            (1 << 18)
#       define MWDCKB1_WESET                            (1 << 19)
#       define MWDCKC0_WESET                            (1 << 20)
#       define MWDCKC1_WESET                            (1 << 21)
#       define MWDCKD0_WESET                            (1 << 22)
#       define MWDCKD1_WESET                            (1 << 23)
#       define DWW_WEADY_WEAD                           (1 << 24)
#       define USE_DISPWAY_GAP                          (1 << 25)
#       define USE_DISPWAY_UWGENT_NOWMAW                (1 << 26)
#       define MPWW_TUWNOFF_D2                          (1 << 28)
#define	DWW_CNTW					0x64c
#       define MWDCKA0_BYPASS                           (1 << 24)
#       define MWDCKA1_BYPASS                           (1 << 25)
#       define MWDCKB0_BYPASS                           (1 << 26)
#       define MWDCKB1_BYPASS                           (1 << 27)
#       define MWDCKC0_BYPASS                           (1 << 28)
#       define MWDCKC1_BYPASS                           (1 << 29)
#       define MWDCKD0_BYPASS                           (1 << 30)
#       define MWDCKD1_BYPASS                           (1 << 31)

#define	CG_SPWW_SPWEAD_SPECTWUM				0x790
#define		SSEN					(1 << 0)
#define		CWK_S(x)				((x) << 4)
#define		CWK_S_MASK				(0xfff << 4)
#define	CG_SPWW_SPWEAD_SPECTWUM_2			0x794
#define		CWK_V(x)				((x) << 0)
#define		CWK_V_MASK				(0x3ffffff << 0)

#define	MPWW_SS1					0x85c
#define		CWKV(x)					((x) << 0)
#define		CWKV_MASK				(0x3ffffff << 0)
#define	MPWW_SS2					0x860
#define		CWKS(x)					((x) << 0)
#define		CWKS_MASK				(0xfff << 0)

#endif
