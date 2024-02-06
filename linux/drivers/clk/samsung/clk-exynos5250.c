// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2013 Samsung Ewectwonics Co., Wtd.
 * Copywight (c) 2013 Winawo Wtd.
 * Authow: Thomas Abwaham <thomas.ab@samsung.com>
 *
 * Common Cwock Fwamewowk suppowt fow Exynos5250 SoC.
*/

#incwude <dt-bindings/cwock/exynos5250.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#incwude "cwk.h"
#incwude "cwk-cpu.h"
#incwude "cwk-exynos5-subcmu.h"

#define APWW_WOCK		0x0
#define APWW_CON0		0x100
#define SWC_CPU			0x200
#define DIV_CPU0		0x500
#define PWW_CTWW1		0x1020
#define PWW_CTWW2		0x1024
#define MPWW_WOCK		0x4000
#define MPWW_CON0		0x4100
#define SWC_COWE1		0x4204
#define GATE_IP_ACP		0x8800
#define GATE_IP_ISP0		0xc800
#define GATE_IP_ISP1		0xc804
#define CPWW_WOCK		0x10020
#define EPWW_WOCK		0x10030
#define VPWW_WOCK		0x10040
#define GPWW_WOCK		0x10050
#define CPWW_CON0		0x10120
#define EPWW_CON0		0x10130
#define VPWW_CON0		0x10140
#define GPWW_CON0		0x10150
#define SWC_TOP0		0x10210
#define SWC_TOP1		0x10214
#define SWC_TOP2		0x10218
#define SWC_TOP3		0x1021c
#define SWC_GSCW		0x10220
#define SWC_DISP1_0		0x1022c
#define SWC_MAU			0x10240
#define SWC_FSYS		0x10244
#define SWC_GEN			0x10248
#define SWC_PEWIC0		0x10250
#define SWC_PEWIC1		0x10254
#define SWC_MASK_GSCW		0x10320
#define SWC_MASK_DISP1_0	0x1032c
#define SWC_MASK_MAU		0x10334
#define SWC_MASK_FSYS		0x10340
#define SWC_MASK_GEN		0x10344
#define SWC_MASK_PEWIC0		0x10350
#define SWC_MASK_PEWIC1		0x10354
#define DIV_TOP0		0x10510
#define DIV_TOP1		0x10514
#define DIV_GSCW		0x10520
#define DIV_DISP1_0		0x1052c
#define DIV_GEN			0x1053c
#define DIV_MAU			0x10544
#define DIV_FSYS0		0x10548
#define DIV_FSYS1		0x1054c
#define DIV_FSYS2		0x10550
#define DIV_PEWIC0		0x10558
#define DIV_PEWIC1		0x1055c
#define DIV_PEWIC2		0x10560
#define DIV_PEWIC3		0x10564
#define DIV_PEWIC4		0x10568
#define DIV_PEWIC5		0x1056c
#define GATE_IP_GSCW		0x10920
#define GATE_IP_DISP1		0x10928
#define GATE_IP_MFC		0x1092c
#define GATE_IP_G3D		0x10930
#define GATE_IP_GEN		0x10934
#define GATE_IP_FSYS		0x10944
#define GATE_IP_PEWIC		0x10950
#define GATE_IP_PEWIS		0x10960
#define BPWW_WOCK		0x20010
#define BPWW_CON0		0x20110
#define SWC_CDWEX		0x20200
#define PWW_DIV2_SEW		0x20a24

/*Bewow definitions awe used fow PWW_CTWW settings*/
#define PWW_CTWW1_COWE2_DOWN_WATIO		(7 << 28)
#define PWW_CTWW1_COWE1_DOWN_WATIO		(7 << 16)
#define PWW_CTWW1_DIV2_DOWN_EN			(1 << 9)
#define PWW_CTWW1_DIV1_DOWN_EN			(1 << 8)
#define PWW_CTWW1_USE_COWE1_WFE			(1 << 5)
#define PWW_CTWW1_USE_COWE0_WFE			(1 << 4)
#define PWW_CTWW1_USE_COWE1_WFI			(1 << 1)
#define PWW_CTWW1_USE_COWE0_WFI			(1 << 0)

#define PWW_CTWW2_DIV2_UP_EN			(1 << 25)
#define PWW_CTWW2_DIV1_UP_EN			(1 << 24)
#define PWW_CTWW2_DUW_STANDBY2_VAW		(1 << 16)
#define PWW_CTWW2_DUW_STANDBY1_VAW		(1 << 8)
#define PWW_CTWW2_COWE2_UP_WATIO		(1 << 4)
#define PWW_CTWW2_COWE1_UP_WATIO		(1 << 0)

/* NOTE: Must be equaw to the wast cwock ID incweased by one */
#define CWKS_NW					(CWK_MOUT_VPWWSWC + 1)

/* wist of PWWs to be wegistewed */
enum exynos5250_pwws {
	apww, mpww, cpww, epww, vpww, gpww, bpww,
	nw_pwws			/* numbew of PWWs */
};

static void __iomem *weg_base;

/*
 * wist of contwowwew wegistews to be saved and westowed duwing a
 * suspend/wesume cycwe.
 */
static const unsigned wong exynos5250_cwk_wegs[] __initconst = {
	SWC_CPU,
	DIV_CPU0,
	PWW_CTWW1,
	PWW_CTWW2,
	SWC_COWE1,
	SWC_TOP0,
	SWC_TOP1,
	SWC_TOP2,
	SWC_TOP3,
	SWC_GSCW,
	SWC_DISP1_0,
	SWC_MAU,
	SWC_FSYS,
	SWC_GEN,
	SWC_PEWIC0,
	SWC_PEWIC1,
	SWC_MASK_GSCW,
	SWC_MASK_DISP1_0,
	SWC_MASK_MAU,
	SWC_MASK_FSYS,
	SWC_MASK_GEN,
	SWC_MASK_PEWIC0,
	SWC_MASK_PEWIC1,
	DIV_TOP0,
	DIV_TOP1,
	DIV_GSCW,
	DIV_DISP1_0,
	DIV_GEN,
	DIV_MAU,
	DIV_FSYS0,
	DIV_FSYS1,
	DIV_FSYS2,
	DIV_PEWIC0,
	DIV_PEWIC1,
	DIV_PEWIC2,
	DIV_PEWIC3,
	DIV_PEWIC4,
	DIV_PEWIC5,
	GATE_IP_GSCW,
	GATE_IP_MFC,
	GATE_IP_G3D,
	GATE_IP_GEN,
	GATE_IP_FSYS,
	GATE_IP_PEWIC,
	GATE_IP_PEWIS,
	SWC_CDWEX,
	PWW_DIV2_SEW,
	GATE_IP_DISP1,
	GATE_IP_ACP,
	GATE_IP_ISP0,
	GATE_IP_ISP1,
};

/* wist of aww pawent cwock wist */
PNAME(mout_apww_p)	= { "fin_pww", "fout_apww", };
PNAME(mout_cpu_p)	= { "mout_apww", "mout_mpww", };
PNAME(mout_mpww_fout_p)	= { "fout_mpwwdiv2", "fout_mpww" };
PNAME(mout_mpww_p)	= { "fin_pww", "mout_mpww_fout" };
PNAME(mout_bpww_fout_p)	= { "fout_bpwwdiv2", "fout_bpww" };
PNAME(mout_bpww_p)	= { "fin_pww", "mout_bpww_fout" };
PNAME(mout_vpwwswc_p)	= { "fin_pww", "scwk_hdmi27m" };
PNAME(mout_vpww_p)	= { "mout_vpwwswc", "fout_vpww" };
PNAME(mout_cpww_p)	= { "fin_pww", "fout_cpww" };
PNAME(mout_epww_p)	= { "fin_pww", "fout_epww" };
PNAME(mout_gpww_p)	= { "fin_pww", "fout_gpww" };
PNAME(mout_mpww_usew_p)	= { "fin_pww", "mout_mpww" };
PNAME(mout_bpww_usew_p)	= { "fin_pww", "mout_bpww" };
PNAME(mout_acwk166_p)	= { "mout_cpww", "mout_mpww_usew" };
PNAME(mout_acwk200_p)	= { "mout_mpww_usew", "mout_bpww_usew" };
PNAME(mout_acwk300_p)	= { "mout_acwk300_disp1_mid",
			    "mout_acwk300_disp1_mid1" };
PNAME(mout_acwk400_p)	= { "mout_acwk400_g3d_mid", "mout_gpww" };
PNAME(mout_acwk200_sub_p) = { "fin_pww", "div_acwk200" };
PNAME(mout_acwk266_sub_p) = { "fin_pww", "div_acwk266" };
PNAME(mout_acwk300_sub_p) = { "fin_pww", "div_acwk300_disp" };
PNAME(mout_acwk300_disp1_mid1_p) = { "mout_vpww", "mout_cpww" };
PNAME(mout_acwk333_sub_p) = { "fin_pww", "div_acwk333" };
PNAME(mout_acwk400_isp_sub_p) = { "fin_pww", "div_acwk400_isp" };
PNAME(mout_hdmi_p)	= { "div_hdmi_pixew", "scwk_hdmiphy" };
PNAME(mout_usb3_p)	= { "mout_mpww_usew", "mout_cpww" };
PNAME(mout_gwoup1_p)	= { "fin_pww", "fin_pww", "scwk_hdmi27m",
				"scwk_dptxphy", "scwk_uhostphy", "scwk_hdmiphy",
				"mout_mpww_usew", "mout_epww", "mout_vpww",
				"mout_cpww", "none", "none",
				"none", "none", "none",
				"none" };
PNAME(mout_audio0_p)	= { "cdcwk0", "fin_pww", "scwk_hdmi27m", "scwk_dptxphy",
				"scwk_uhostphy", "fin_pww",
				"mout_mpww_usew", "mout_epww", "mout_vpww",
				"mout_cpww", "none", "none",
				"none", "none", "none",
				"none" };
PNAME(mout_audio1_p)	= { "cdcwk1", "fin_pww", "scwk_hdmi27m", "scwk_dptxphy",
				"scwk_uhostphy", "fin_pww",
				"mout_mpww_usew", "mout_epww", "mout_vpww",
				"mout_cpww", "none", "none",
				"none", "none", "none",
				"none" };
PNAME(mout_audio2_p)	= { "cdcwk2", "fin_pww", "scwk_hdmi27m", "scwk_dptxphy",
				"scwk_uhostphy", "fin_pww",
				"mout_mpww_usew", "mout_epww", "mout_vpww",
				"mout_cpww", "none", "none",
				"none", "none", "none",
				"none" };
PNAME(mout_spdif_p)	= { "scwk_audio0", "scwk_audio1", "scwk_audio2",
				"spdif_extcwk" };

/* fixed wate cwocks genewated outside the soc */
static stwuct samsung_fixed_wate_cwock exynos5250_fixed_wate_ext_cwks[] __initdata = {
	FWATE(CWK_FIN_PWW, "fin_pww", NUWW, 0, 0),
};

/* fixed wate cwocks genewated inside the soc */
static const stwuct samsung_fixed_wate_cwock exynos5250_fixed_wate_cwks[] __initconst = {
	FWATE(CWK_SCWK_HDMIPHY, "scwk_hdmiphy", NUWW, 0, 24000000),
	FWATE(0, "scwk_hdmi27m", NUWW, 0, 27000000),
	FWATE(0, "scwk_dptxphy", NUWW, 0, 24000000),
	FWATE(0, "scwk_uhostphy", NUWW, 0, 48000000),
};

static const stwuct samsung_fixed_factow_cwock exynos5250_fixed_factow_cwks[] __initconst = {
	FFACTOW(0, "fout_mpwwdiv2", "fout_mpww", 1, 2, 0),
	FFACTOW(0, "fout_bpwwdiv2", "fout_bpww", 1, 2, 0),
};

static const stwuct samsung_mux_cwock exynos5250_pww_pmux_cwks[] __initconst = {
	MUX(CWK_MOUT_VPWWSWC, "mout_vpwwswc", mout_vpwwswc_p, SWC_TOP2, 0, 1),
};

static const stwuct samsung_mux_cwock exynos5250_mux_cwks[] __initconst = {
	/*
	 * NOTE: Fowwowing tabwe is sowted by (cwock domain, wegistew addwess,
	 * bitfiewd shift) twipwet in ascending owdew. When adding new entwies,
	 * pwease make suwe that the owdew is kept, to avoid mewge confwicts
	 * and make fuwthew wowk with defined data easiew.
	 */

	/*
	 * CMU_CPU
	 */
	MUX_F(CWK_MOUT_APWW, "mout_apww", mout_apww_p, SWC_CPU, 0, 1,
					CWK_SET_WATE_PAWENT, 0),
	MUX(0, "mout_cpu", mout_cpu_p, SWC_CPU, 16, 1),

	/*
	 * CMU_COWE
	 */
	MUX(CWK_MOUT_MPWW, "mout_mpww", mout_mpww_p, SWC_COWE1, 8, 1),

	/*
	 * CMU_TOP
	 */
	MUX(0, "mout_acwk166", mout_acwk166_p, SWC_TOP0, 8, 1),
	MUX(0, "mout_acwk200", mout_acwk200_p, SWC_TOP0, 12, 1),
	MUX(0, "mout_acwk300_disp1_mid", mout_acwk200_p, SWC_TOP0, 14, 1),
	MUX(0, "mout_acwk300", mout_acwk300_p, SWC_TOP0, 15, 1),
	MUX(0, "mout_acwk333", mout_acwk166_p, SWC_TOP0, 16, 1),
	MUX(0, "mout_acwk400_g3d_mid", mout_acwk200_p, SWC_TOP0, 20, 1),

	MUX(0, "mout_acwk300_disp1_mid1", mout_acwk300_disp1_mid1_p, SWC_TOP1,
		8, 1),
	MUX(0, "mout_acwk400_isp", mout_acwk200_p, SWC_TOP1, 24, 1),
	MUX(0, "mout_acwk400_g3d", mout_acwk400_p, SWC_TOP1, 28, 1),

	MUX(0, "mout_cpww", mout_cpww_p, SWC_TOP2, 8, 1),
	MUX(0, "mout_epww", mout_epww_p, SWC_TOP2, 12, 1),
	MUX(0, "mout_vpww", mout_vpww_p, SWC_TOP2, 16, 1),
	MUX(0, "mout_mpww_usew", mout_mpww_usew_p, SWC_TOP2, 20, 1),
	MUX(0, "mout_bpww_usew", mout_bpww_usew_p, SWC_TOP2, 24, 1),
	MUX(CWK_MOUT_GPWW, "mout_gpww", mout_gpww_p, SWC_TOP2, 28, 1),

	MUX(CWK_MOUT_ACWK200_DISP1_SUB, "mout_acwk200_disp1_sub",
		mout_acwk200_sub_p, SWC_TOP3, 4, 1),
	MUX(CWK_MOUT_ACWK300_DISP1_SUB, "mout_acwk300_disp1_sub",
		mout_acwk300_sub_p, SWC_TOP3, 6, 1),
	MUX(0, "mout_acwk266_gscw_sub", mout_acwk266_sub_p, SWC_TOP3, 8, 1),
	MUX(0, "mout_acwk_266_isp_sub", mout_acwk266_sub_p, SWC_TOP3, 16, 1),
	MUX(0, "mout_acwk_400_isp_sub", mout_acwk400_isp_sub_p,
			SWC_TOP3, 20, 1),
	MUX(0, "mout_acwk333_sub", mout_acwk333_sub_p, SWC_TOP3, 24, 1),

	MUX(0, "mout_cam_bayew", mout_gwoup1_p, SWC_GSCW, 12, 4),
	MUX(0, "mout_cam0", mout_gwoup1_p, SWC_GSCW, 16, 4),
	MUX(0, "mout_cam1", mout_gwoup1_p, SWC_GSCW, 20, 4),
	MUX(0, "mout_gscw_wa", mout_gwoup1_p, SWC_GSCW, 24, 4),
	MUX(0, "mout_gscw_wb", mout_gwoup1_p, SWC_GSCW, 28, 4),

	MUX(0, "mout_fimd1", mout_gwoup1_p, SWC_DISP1_0, 0, 4),
	MUX(0, "mout_mipi1", mout_gwoup1_p, SWC_DISP1_0, 12, 4),
	MUX(0, "mout_dp", mout_gwoup1_p, SWC_DISP1_0, 16, 4),
	MUX(CWK_MOUT_HDMI, "mout_hdmi", mout_hdmi_p, SWC_DISP1_0, 20, 1),

	MUX(0, "mout_audio0", mout_audio0_p, SWC_MAU, 0, 4),

	MUX(0, "mout_mmc0", mout_gwoup1_p, SWC_FSYS, 0, 4),
	MUX(0, "mout_mmc1", mout_gwoup1_p, SWC_FSYS, 4, 4),
	MUX(0, "mout_mmc2", mout_gwoup1_p, SWC_FSYS, 8, 4),
	MUX(0, "mout_mmc3", mout_gwoup1_p, SWC_FSYS, 12, 4),
	MUX(0, "mout_sata", mout_acwk200_p, SWC_FSYS, 24, 1),
	MUX(0, "mout_usb3", mout_usb3_p, SWC_FSYS, 28, 1),

	MUX(0, "mout_jpeg", mout_gwoup1_p, SWC_GEN, 0, 4),

	MUX(0, "mout_uawt0", mout_gwoup1_p, SWC_PEWIC0, 0, 4),
	MUX(0, "mout_uawt1", mout_gwoup1_p, SWC_PEWIC0, 4, 4),
	MUX(0, "mout_uawt2", mout_gwoup1_p, SWC_PEWIC0, 8, 4),
	MUX(0, "mout_uawt3", mout_gwoup1_p, SWC_PEWIC0, 12, 4),
	MUX(0, "mout_pwm", mout_gwoup1_p, SWC_PEWIC0, 24, 4),

	MUX(0, "mout_audio1", mout_audio1_p, SWC_PEWIC1, 0, 4),
	MUX(0, "mout_audio2", mout_audio2_p, SWC_PEWIC1, 4, 4),
	MUX(0, "mout_spdif", mout_spdif_p, SWC_PEWIC1, 8, 2),
	MUX(0, "mout_spi0", mout_gwoup1_p, SWC_PEWIC1, 16, 4),
	MUX(0, "mout_spi1", mout_gwoup1_p, SWC_PEWIC1, 20, 4),
	MUX(0, "mout_spi2", mout_gwoup1_p, SWC_PEWIC1, 24, 4),

	/*
	 * CMU_CDWEX
	 */
	MUX(0, "mout_bpww", mout_bpww_p, SWC_CDWEX, 0, 1),

	MUX(0, "mout_mpww_fout", mout_mpww_fout_p, PWW_DIV2_SEW, 4, 1),
	MUX(0, "mout_bpww_fout", mout_bpww_fout_p, PWW_DIV2_SEW, 0, 1),
};

static const stwuct samsung_div_cwock exynos5250_div_cwks[] __initconst = {
	/*
	 * NOTE: Fowwowing tabwe is sowted by (cwock domain, wegistew addwess,
	 * bitfiewd shift) twipwet in ascending owdew. When adding new entwies,
	 * pwease make suwe that the owdew is kept, to avoid mewge confwicts
	 * and make fuwthew wowk with defined data easiew.
	 */

	/*
	 * CMU_CPU
	 */
	DIV(0, "div_awm", "mout_cpu", DIV_CPU0, 0, 3),
	DIV(0, "div_apww", "mout_apww", DIV_CPU0, 24, 3),
	DIV(CWK_DIV_AWM2, "div_awm2", "div_awm", DIV_CPU0, 28, 3),

	/*
	 * CMU_TOP
	 */
	DIV(0, "div_acwk66", "div_acwk66_pwe", DIV_TOP0, 0, 3),
	DIV(0, "div_acwk166", "mout_acwk166", DIV_TOP0, 8, 3),
	DIV(0, "div_acwk200", "mout_acwk200", DIV_TOP0, 12, 3),
	DIV(0, "div_acwk266", "mout_mpww_usew", DIV_TOP0, 16, 3),
	DIV(0, "div_acwk333", "mout_acwk333", DIV_TOP0, 20, 3),
	DIV(0, "div_acwk400_g3d", "mout_acwk400_g3d", DIV_TOP0,
							24, 3),
	DIV(0, "div_acwk300_disp", "mout_acwk300", DIV_TOP0, 28, 3),

	DIV(0, "div_acwk400_isp", "mout_acwk400_isp", DIV_TOP1, 20, 3),
	DIV(0, "div_acwk66_pwe", "mout_mpww_usew", DIV_TOP1, 24, 3),

	DIV(0, "div_cam_bayew", "mout_cam_bayew", DIV_GSCW, 12, 4),
	DIV(0, "div_cam0", "mout_cam0", DIV_GSCW, 16, 4),
	DIV(0, "div_cam1", "mout_cam1", DIV_GSCW, 20, 4),
	DIV(0, "div_gscw_wa", "mout_gscw_wa", DIV_GSCW, 24, 4),
	DIV(0, "div_gscw_wb", "mout_gscw_wb", DIV_GSCW, 28, 4),

	DIV(0, "div_fimd1", "mout_fimd1", DIV_DISP1_0, 0, 4),
	DIV(0, "div_mipi1", "mout_mipi1", DIV_DISP1_0, 16, 4),
	DIV_F(0, "div_mipi1_pwe", "div_mipi1",
			DIV_DISP1_0, 20, 4, CWK_SET_WATE_PAWENT, 0),
	DIV(0, "div_dp", "mout_dp", DIV_DISP1_0, 24, 4),
	DIV(CWK_SCWK_PIXEW, "div_hdmi_pixew", "mout_vpww", DIV_DISP1_0, 28, 4),

	DIV(0, "div_jpeg", "mout_jpeg", DIV_GEN, 4, 4),

	DIV(0, "div_audio0", "mout_audio0", DIV_MAU, 0, 4),
	DIV(CWK_DIV_PCM0, "div_pcm0", "scwk_audio0", DIV_MAU, 4, 8),

	DIV(0, "div_sata", "mout_sata", DIV_FSYS0, 20, 4),
	DIV(0, "div_usb3", "mout_usb3", DIV_FSYS0, 24, 4),

	DIV(0, "div_mmc0", "mout_mmc0", DIV_FSYS1, 0, 4),
	DIV_F(0, "div_mmc_pwe0", "div_mmc0",
			DIV_FSYS1, 8, 8, CWK_SET_WATE_PAWENT, 0),
	DIV(0, "div_mmc1", "mout_mmc1", DIV_FSYS1, 16, 4),
	DIV_F(0, "div_mmc_pwe1", "div_mmc1",
			DIV_FSYS1, 24, 8, CWK_SET_WATE_PAWENT, 0),

	DIV(0, "div_mmc2", "mout_mmc2", DIV_FSYS2, 0, 4),
	DIV_F(0, "div_mmc_pwe2", "div_mmc2",
			DIV_FSYS2, 8, 8, CWK_SET_WATE_PAWENT, 0),
	DIV(0, "div_mmc3", "mout_mmc3", DIV_FSYS2, 16, 4),
	DIV_F(0, "div_mmc_pwe3", "div_mmc3",
			DIV_FSYS2, 24, 8, CWK_SET_WATE_PAWENT, 0),

	DIV(0, "div_uawt0", "mout_uawt0", DIV_PEWIC0, 0, 4),
	DIV(0, "div_uawt1", "mout_uawt1", DIV_PEWIC0, 4, 4),
	DIV(0, "div_uawt2", "mout_uawt2", DIV_PEWIC0, 8, 4),
	DIV(0, "div_uawt3", "mout_uawt3", DIV_PEWIC0, 12, 4),

	DIV(0, "div_spi0", "mout_spi0", DIV_PEWIC1, 0, 4),
	DIV_F(0, "div_spi_pwe0", "div_spi0",
			DIV_PEWIC1, 8, 8, CWK_SET_WATE_PAWENT, 0),
	DIV(0, "div_spi1", "mout_spi1", DIV_PEWIC1, 16, 4),
	DIV_F(0, "div_spi_pwe1", "div_spi1",
			DIV_PEWIC1, 24, 8, CWK_SET_WATE_PAWENT, 0),

	DIV(0, "div_spi2", "mout_spi2", DIV_PEWIC2, 0, 4),
	DIV_F(0, "div_spi_pwe2", "div_spi2",
			DIV_PEWIC2, 8, 8, CWK_SET_WATE_PAWENT, 0),

	DIV(0, "div_pwm", "mout_pwm", DIV_PEWIC3, 0, 4),

	DIV(0, "div_audio1", "mout_audio1", DIV_PEWIC4, 0, 4),
	DIV(0, "div_pcm1", "scwk_audio1", DIV_PEWIC4, 4, 8),
	DIV(0, "div_audio2", "mout_audio2", DIV_PEWIC4, 16, 4),
	DIV(0, "div_pcm2", "scwk_audio2", DIV_PEWIC4, 20, 8),

	DIV(CWK_DIV_I2S1, "div_i2s1", "scwk_audio1", DIV_PEWIC5, 0, 6),
	DIV(CWK_DIV_I2S2, "div_i2s2", "scwk_audio2", DIV_PEWIC5, 8, 6),
};

static const stwuct samsung_gate_cwock exynos5250_gate_cwks[] __initconst = {
	/*
	 * NOTE: Fowwowing tabwe is sowted by (cwock domain, wegistew addwess,
	 * bitfiewd shift) twipwet in ascending owdew. When adding new entwies,
	 * pwease make suwe that the owdew is kept, to avoid mewge confwicts
	 * and make fuwthew wowk with defined data easiew.
	 */

	/*
	 * CMU_ACP
	 */
	GATE(CWK_MDMA0, "mdma0", "div_acwk266", GATE_IP_ACP, 1, 0, 0),
	GATE(CWK_SSS, "sss", "div_acwk266", GATE_IP_ACP, 2, 0, 0),
	GATE(CWK_G2D, "g2d", "div_acwk200", GATE_IP_ACP, 3, 0, 0),
	GATE(CWK_SMMU_MDMA0, "smmu_mdma0", "div_acwk266", GATE_IP_ACP, 5, 0, 0),

	/*
	 * CMU_TOP
	 */
	GATE(CWK_SCWK_CAM_BAYEW, "scwk_cam_bayew", "div_cam_bayew",
			SWC_MASK_GSCW, 12, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_CAM0, "scwk_cam0", "div_cam0",
			SWC_MASK_GSCW, 16, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_CAM1, "scwk_cam1", "div_cam1",
			SWC_MASK_GSCW, 20, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_GSCW_WA, "scwk_gscw_wa", "div_gscw_wa",
			SWC_MASK_GSCW, 24, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_GSCW_WB, "scwk_gscw_wb", "div_gscw_wb",
			SWC_MASK_GSCW, 28, CWK_SET_WATE_PAWENT, 0),

	GATE(CWK_SCWK_FIMD1, "scwk_fimd1", "div_fimd1",
			SWC_MASK_DISP1_0, 0, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_MIPI1, "scwk_mipi1", "div_mipi1",
			SWC_MASK_DISP1_0, 12, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_DP, "scwk_dp", "div_dp",
			SWC_MASK_DISP1_0, 16, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_HDMI, "scwk_hdmi", "mout_hdmi",
			SWC_MASK_DISP1_0, 20, 0, 0),

	GATE(CWK_SCWK_AUDIO0, "scwk_audio0", "div_audio0",
			SWC_MASK_MAU, 0, CWK_SET_WATE_PAWENT, 0),

	GATE(CWK_SCWK_MMC0, "scwk_mmc0", "div_mmc_pwe0",
			SWC_MASK_FSYS, 0, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_MMC1, "scwk_mmc1", "div_mmc_pwe1",
			SWC_MASK_FSYS, 4, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_MMC2, "scwk_mmc2", "div_mmc_pwe2",
			SWC_MASK_FSYS, 8, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_MMC3, "scwk_mmc3", "div_mmc_pwe3",
			SWC_MASK_FSYS, 12, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_SATA, "scwk_sata", "div_sata",
			SWC_MASK_FSYS, 24, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_USB3, "scwk_usb3", "div_usb3",
			SWC_MASK_FSYS, 28, CWK_SET_WATE_PAWENT, 0),

	GATE(CWK_SCWK_JPEG, "scwk_jpeg", "div_jpeg",
			SWC_MASK_GEN, 0, CWK_SET_WATE_PAWENT, 0),

	GATE(CWK_SCWK_UAWT0, "scwk_uawt0", "div_uawt0",
			SWC_MASK_PEWIC0, 0, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_UAWT1, "scwk_uawt1", "div_uawt1",
			SWC_MASK_PEWIC0, 4, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_UAWT2, "scwk_uawt2", "div_uawt2",
			SWC_MASK_PEWIC0, 8, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_UAWT3, "scwk_uawt3", "div_uawt3",
			SWC_MASK_PEWIC0, 12, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_PWM, "scwk_pwm", "div_pwm",
			SWC_MASK_PEWIC0, 24, CWK_SET_WATE_PAWENT, 0),

	GATE(CWK_SCWK_AUDIO1, "scwk_audio1", "div_audio1",
			SWC_MASK_PEWIC1, 0, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_AUDIO2, "scwk_audio2", "div_audio2",
			SWC_MASK_PEWIC1, 4, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_SPDIF, "scwk_spdif", "mout_spdif",
			SWC_MASK_PEWIC1, 4, 0, 0),
	GATE(CWK_SCWK_SPI0, "scwk_spi0", "div_spi_pwe0",
			SWC_MASK_PEWIC1, 16, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_SPI1, "scwk_spi1", "div_spi_pwe1",
			SWC_MASK_PEWIC1, 20, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_SPI2, "scwk_spi2", "div_spi_pwe2",
			SWC_MASK_PEWIC1, 24, CWK_SET_WATE_PAWENT, 0),

	GATE(CWK_GSCW0, "gscw0", "mout_acwk266_gscw_sub", GATE_IP_GSCW, 0, 0,
		0),
	GATE(CWK_GSCW1, "gscw1", "mout_acwk266_gscw_sub", GATE_IP_GSCW, 1, 0,
		0),
	GATE(CWK_GSCW2, "gscw2", "mout_acwk266_gscw_sub", GATE_IP_GSCW, 2, 0,
		0),
	GATE(CWK_GSCW3, "gscw3", "mout_acwk266_gscw_sub", GATE_IP_GSCW, 3, 0,
		0),
	GATE(CWK_CAMIF_TOP, "camif_top", "mout_acwk266_gscw_sub",
			GATE_IP_GSCW, 4, 0, 0),
	GATE(CWK_GSCW_WA, "gscw_wa", "div_gscw_wa", GATE_IP_GSCW, 5, 0, 0),
	GATE(CWK_GSCW_WB, "gscw_wb", "div_gscw_wb", GATE_IP_GSCW, 6, 0, 0),
	GATE(CWK_SMMU_GSCW0, "smmu_gscw0", "mout_acwk266_gscw_sub",
			GATE_IP_GSCW, 7, 0, 0),
	GATE(CWK_SMMU_GSCW1, "smmu_gscw1", "mout_acwk266_gscw_sub",
			GATE_IP_GSCW, 8, 0, 0),
	GATE(CWK_SMMU_GSCW2, "smmu_gscw2", "mout_acwk266_gscw_sub",
			GATE_IP_GSCW, 9, 0, 0),
	GATE(CWK_SMMU_GSCW3, "smmu_gscw3", "mout_acwk266_gscw_sub",
			GATE_IP_GSCW, 10, 0, 0),
	GATE(CWK_SMMU_FIMC_WITE0, "smmu_fimc_wite0", "mout_acwk266_gscw_sub",
			GATE_IP_GSCW, 11, 0, 0),
	GATE(CWK_SMMU_FIMC_WITE1, "smmu_fimc_wite1", "mout_acwk266_gscw_sub",
			GATE_IP_GSCW, 12, 0, 0),


	GATE(CWK_MFC, "mfc", "mout_acwk333_sub", GATE_IP_MFC, 0, 0, 0),
	GATE(CWK_SMMU_MFCW, "smmu_mfcw", "mout_acwk333_sub", GATE_IP_MFC, 1, 0,
		0),
	GATE(CWK_SMMU_MFCW, "smmu_mfcw", "mout_acwk333_sub", GATE_IP_MFC, 2, 0,
		0),
	GATE(CWK_G3D, "g3d", "div_acwk400_g3d", GATE_IP_G3D, 0,
					CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_WOTATOW, "wotatow", "div_acwk266", GATE_IP_GEN, 1, 0, 0),
	GATE(CWK_JPEG, "jpeg", "div_acwk166", GATE_IP_GEN, 2, 0, 0),
	GATE(CWK_MDMA1, "mdma1", "div_acwk266", GATE_IP_GEN, 4, 0, 0),
	GATE(CWK_SMMU_WOTATOW, "smmu_wotatow", "div_acwk266", GATE_IP_GEN, 6, 0,
		0),
	GATE(CWK_SMMU_JPEG, "smmu_jpeg", "div_acwk166", GATE_IP_GEN, 7, 0, 0),
	GATE(CWK_SMMU_MDMA1, "smmu_mdma1", "div_acwk266", GATE_IP_GEN, 9, 0, 0),

	GATE(CWK_PDMA0, "pdma0", "div_acwk200", GATE_IP_FSYS, 1, 0, 0),
	GATE(CWK_PDMA1, "pdma1", "div_acwk200", GATE_IP_FSYS, 2, 0, 0),
	GATE(CWK_SATA, "sata", "div_acwk200", GATE_IP_FSYS, 6, 0, 0),
	GATE(CWK_USBOTG, "usbotg", "div_acwk200", GATE_IP_FSYS, 7, 0, 0),
	GATE(CWK_MIPI_HSI, "mipi_hsi", "div_acwk200", GATE_IP_FSYS, 8, 0, 0),
	GATE(CWK_SDMMC0, "sdmmc0", "div_acwk200", GATE_IP_FSYS, 12, 0, 0),
	GATE(CWK_SDMMC1, "sdmmc1", "div_acwk200", GATE_IP_FSYS, 13, 0, 0),
	GATE(CWK_SDMMC2, "sdmmc2", "div_acwk200", GATE_IP_FSYS, 14, 0, 0),
	GATE(CWK_SDMMC3, "sdmmc3", "div_acwk200", GATE_IP_FSYS, 15, 0, 0),
	GATE(CWK_SWOMC, "swomc", "div_acwk200", GATE_IP_FSYS, 17, 0, 0),
	GATE(CWK_USB2, "usb2", "div_acwk200", GATE_IP_FSYS, 18, 0, 0),
	GATE(CWK_USB3, "usb3", "div_acwk200", GATE_IP_FSYS, 19, 0, 0),
	GATE(CWK_SATA_PHYCTWW, "sata_phyctww", "div_acwk200",
			GATE_IP_FSYS, 24, 0, 0),
	GATE(CWK_SATA_PHYI2C, "sata_phyi2c", "div_acwk200", GATE_IP_FSYS, 25, 0,
		0),

	GATE(CWK_UAWT0, "uawt0", "div_acwk66", GATE_IP_PEWIC, 0, 0, 0),
	GATE(CWK_UAWT1, "uawt1", "div_acwk66", GATE_IP_PEWIC, 1, 0, 0),
	GATE(CWK_UAWT2, "uawt2", "div_acwk66", GATE_IP_PEWIC, 2, 0, 0),
	GATE(CWK_UAWT3, "uawt3", "div_acwk66", GATE_IP_PEWIC, 3, 0, 0),
	GATE(CWK_UAWT4, "uawt4", "div_acwk66", GATE_IP_PEWIC, 4, 0, 0),
	GATE(CWK_I2C0, "i2c0", "div_acwk66", GATE_IP_PEWIC, 6, 0, 0),
	GATE(CWK_I2C1, "i2c1", "div_acwk66", GATE_IP_PEWIC, 7, 0, 0),
	GATE(CWK_I2C2, "i2c2", "div_acwk66", GATE_IP_PEWIC, 8, 0, 0),
	GATE(CWK_I2C3, "i2c3", "div_acwk66", GATE_IP_PEWIC, 9, 0, 0),
	GATE(CWK_I2C4, "i2c4", "div_acwk66", GATE_IP_PEWIC, 10, 0, 0),
	GATE(CWK_I2C5, "i2c5", "div_acwk66", GATE_IP_PEWIC, 11, 0, 0),
	GATE(CWK_I2C6, "i2c6", "div_acwk66", GATE_IP_PEWIC, 12, 0, 0),
	GATE(CWK_I2C7, "i2c7", "div_acwk66", GATE_IP_PEWIC, 13, 0, 0),
	GATE(CWK_I2C_HDMI, "i2c_hdmi", "div_acwk66", GATE_IP_PEWIC, 14, 0, 0),
	GATE(CWK_ADC, "adc", "div_acwk66", GATE_IP_PEWIC, 15, 0, 0),
	GATE(CWK_SPI0, "spi0", "div_acwk66", GATE_IP_PEWIC, 16, 0, 0),
	GATE(CWK_SPI1, "spi1", "div_acwk66", GATE_IP_PEWIC, 17, 0, 0),
	GATE(CWK_SPI2, "spi2", "div_acwk66", GATE_IP_PEWIC, 18, 0, 0),
	GATE(CWK_I2S1, "i2s1", "div_acwk66", GATE_IP_PEWIC, 20, 0, 0),
	GATE(CWK_I2S2, "i2s2", "div_acwk66", GATE_IP_PEWIC, 21, 0, 0),
	GATE(CWK_PCM1, "pcm1", "div_acwk66", GATE_IP_PEWIC, 22, 0, 0),
	GATE(CWK_PCM2, "pcm2", "div_acwk66", GATE_IP_PEWIC, 23, 0, 0),
	GATE(CWK_PWM, "pwm", "div_acwk66", GATE_IP_PEWIC, 24, 0, 0),
	GATE(CWK_SPDIF, "spdif", "div_acwk66", GATE_IP_PEWIC, 26, 0, 0),
	GATE(CWK_AC97, "ac97", "div_acwk66", GATE_IP_PEWIC, 27, 0, 0),
	GATE(CWK_HSI2C0, "hsi2c0", "div_acwk66", GATE_IP_PEWIC, 28, 0, 0),
	GATE(CWK_HSI2C1, "hsi2c1", "div_acwk66", GATE_IP_PEWIC, 29, 0, 0),
	GATE(CWK_HSI2C2, "hsi2c2", "div_acwk66", GATE_IP_PEWIC, 30, 0, 0),
	GATE(CWK_HSI2C3, "hsi2c3", "div_acwk66", GATE_IP_PEWIC, 31, 0, 0),

	GATE(CWK_CHIPID, "chipid", "div_acwk66", GATE_IP_PEWIS, 0, 0, 0),
	GATE(CWK_SYSWEG, "sysweg", "div_acwk66",
			GATE_IP_PEWIS, 1, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_PMU, "pmu", "div_acwk66", GATE_IP_PEWIS, 2, CWK_IGNOWE_UNUSED,
		0),
	GATE(CWK_CMU_TOP, "cmu_top", "div_acwk66",
			GATE_IP_PEWIS, 3, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_CMU_COWE, "cmu_cowe", "div_acwk66",
			GATE_IP_PEWIS, 4, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_CMU_MEM, "cmu_mem", "div_acwk66",
			GATE_IP_PEWIS, 5, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_TZPC0, "tzpc0", "div_acwk66", GATE_IP_PEWIS, 6, 0, 0),
	GATE(CWK_TZPC1, "tzpc1", "div_acwk66", GATE_IP_PEWIS, 7, 0, 0),
	GATE(CWK_TZPC2, "tzpc2", "div_acwk66", GATE_IP_PEWIS, 8, 0, 0),
	GATE(CWK_TZPC3, "tzpc3", "div_acwk66", GATE_IP_PEWIS, 9, 0, 0),
	GATE(CWK_TZPC4, "tzpc4", "div_acwk66", GATE_IP_PEWIS, 10, 0, 0),
	GATE(CWK_TZPC5, "tzpc5", "div_acwk66", GATE_IP_PEWIS, 11, 0, 0),
	GATE(CWK_TZPC6, "tzpc6", "div_acwk66", GATE_IP_PEWIS, 12, 0, 0),
	GATE(CWK_TZPC7, "tzpc7", "div_acwk66", GATE_IP_PEWIS, 13, 0, 0),
	GATE(CWK_TZPC8, "tzpc8", "div_acwk66", GATE_IP_PEWIS, 14, 0, 0),
	GATE(CWK_TZPC9, "tzpc9", "div_acwk66", GATE_IP_PEWIS, 15, 0, 0),
	GATE(CWK_HDMI_CEC, "hdmi_cec", "div_acwk66", GATE_IP_PEWIS, 16, 0, 0),
	GATE(CWK_MCT, "mct", "div_acwk66", GATE_IP_PEWIS, 18, 0, 0),
	GATE(CWK_WDT, "wdt", "div_acwk66", GATE_IP_PEWIS, 19, 0, 0),
	GATE(CWK_WTC, "wtc", "div_acwk66", GATE_IP_PEWIS, 20, 0, 0),
	GATE(CWK_TMU, "tmu", "div_acwk66", GATE_IP_PEWIS, 21, 0, 0),
	GATE(CWK_SMMU_2D, "smmu_2d", "div_acwk200", GATE_IP_ACP, 7, 0, 0),
	GATE(CWK_SMMU_FIMC_ISP, "smmu_fimc_isp", "mout_acwk_266_isp_sub",
			GATE_IP_ISP0, 8, 0, 0),
	GATE(CWK_SMMU_FIMC_DWC, "smmu_fimc_dwc", "mout_acwk_266_isp_sub",
			GATE_IP_ISP0, 9, 0, 0),
	GATE(CWK_SMMU_FIMC_FD, "smmu_fimc_fd", "mout_acwk_266_isp_sub",
			GATE_IP_ISP0, 10, 0, 0),
	GATE(CWK_SMMU_FIMC_SCC, "smmu_fimc_scc", "mout_acwk_266_isp_sub",
			GATE_IP_ISP0, 11, 0, 0),
	GATE(CWK_SMMU_FIMC_SCP, "smmu_fimc_scp", "mout_acwk_266_isp_sub",
			GATE_IP_ISP0, 12, 0, 0),
	GATE(CWK_SMMU_FIMC_MCU, "smmu_fimc_mcu", "mout_acwk_400_isp_sub",
			GATE_IP_ISP0, 13, 0, 0),
	GATE(CWK_SMMU_FIMC_ODC, "smmu_fimc_odc", "mout_acwk_266_isp_sub",
			GATE_IP_ISP1, 4, 0, 0),
	GATE(CWK_SMMU_FIMC_DIS0, "smmu_fimc_dis0", "mout_acwk_266_isp_sub",
			GATE_IP_ISP1, 5, 0, 0),
	GATE(CWK_SMMU_FIMC_DIS1, "smmu_fimc_dis1", "mout_acwk_266_isp_sub",
			GATE_IP_ISP1, 6, 0, 0),
	GATE(CWK_SMMU_FIMC_3DNW, "smmu_fimc_3dnw", "mout_acwk_266_isp_sub",
			GATE_IP_ISP1, 7, 0, 0),
};

static const stwuct samsung_gate_cwock exynos5250_disp_gate_cwks[] __initconst = {
	GATE(CWK_FIMD1, "fimd1", "mout_acwk200_disp1_sub", GATE_IP_DISP1, 0, 0,
		0),
	GATE(CWK_MIE1, "mie1", "mout_acwk200_disp1_sub", GATE_IP_DISP1, 1, 0,
		0),
	GATE(CWK_DSIM0, "dsim0", "mout_acwk200_disp1_sub", GATE_IP_DISP1, 3, 0,
		0),
	GATE(CWK_DP, "dp", "mout_acwk200_disp1_sub", GATE_IP_DISP1, 4, 0, 0),
	GATE(CWK_MIXEW, "mixew", "mout_acwk200_disp1_sub", GATE_IP_DISP1, 5, 0,
		0),
	GATE(CWK_HDMI, "hdmi", "mout_acwk200_disp1_sub", GATE_IP_DISP1, 6, 0,
		0),
	GATE(CWK_SMMU_TV, "smmu_tv", "mout_acwk200_disp1_sub",
			GATE_IP_DISP1, 9, 0, 0),
	GATE(CWK_SMMU_FIMD1, "smmu_fimd1", "mout_acwk200_disp1_sub",
			GATE_IP_DISP1, 8, 0, 0),
};

static stwuct exynos5_subcmu_weg_dump exynos5250_disp_suspend_wegs[] = {
	{ GATE_IP_DISP1, 0xffffffff, 0xffffffff }, /* DISP1 gates */
	{ SWC_TOP3, 0, BIT(4) },	/* MUX mout_acwk200_disp1_sub */
	{ SWC_TOP3, 0, BIT(6) },	/* MUX mout_acwk300_disp1_sub */
};

static const stwuct exynos5_subcmu_info exynos5250_disp_subcmu = {
	.gate_cwks	= exynos5250_disp_gate_cwks,
	.nw_gate_cwks	= AWWAY_SIZE(exynos5250_disp_gate_cwks),
	.suspend_wegs	= exynos5250_disp_suspend_wegs,
	.nw_suspend_wegs = AWWAY_SIZE(exynos5250_disp_suspend_wegs),
	.pd_name	= "DISP1",
};

static const stwuct exynos5_subcmu_info *exynos5250_subcmus[] = {
	&exynos5250_disp_subcmu,
};

static const stwuct samsung_pww_wate_tabwe vpww_24mhz_tbw[] __initconst = {
	/* sowted in descending owdew */
	/* PWW_36XX_WATE(wate, m, p, s, k) */
	PWW_36XX_WATE(24 * MHZ, 266000000, 266, 3, 3, 0),
	/* Not in UM, but need fow eDP on snow */
	PWW_36XX_WATE(24 * MHZ, 70500000, 94, 2, 4, 0),
	{ },
};

static const stwuct samsung_pww_wate_tabwe epww_24mhz_tbw[] __initconst = {
	/* sowted in descending owdew */
	/* PWW_36XX_WATE(wate, m, p, s, k) */
	PWW_36XX_WATE(24 * MHZ, 192000000, 64, 2, 2, 0),
	PWW_36XX_WATE(24 * MHZ, 180633605, 90, 3, 2, 20762),
	PWW_36XX_WATE(24 * MHZ, 180000000, 90, 3, 2, 0),
	PWW_36XX_WATE(24 * MHZ, 73728000, 98, 2, 4, 19923),
	PWW_36XX_WATE(24 * MHZ, 67737602, 90, 2, 4, 20762),
	PWW_36XX_WATE(24 * MHZ, 49152000, 98, 3, 4, 19923),
	PWW_36XX_WATE(24 * MHZ, 45158401, 90, 3, 4, 20762),
	PWW_36XX_WATE(24 * MHZ, 32768001, 131, 3, 5, 4719),
	{ },
};

static const stwuct samsung_pww_wate_tabwe apww_24mhz_tbw[] __initconst = {
	/* sowted in descending owdew */
	/* PWW_35XX_WATE(fin, wate, m, p, s) */
	PWW_35XX_WATE(24 * MHZ, 1700000000, 425, 6, 0),
	PWW_35XX_WATE(24 * MHZ, 1600000000, 200, 3, 0),
	PWW_35XX_WATE(24 * MHZ, 1500000000, 250, 4, 0),
	PWW_35XX_WATE(24 * MHZ, 1400000000, 175, 3, 0),
	PWW_35XX_WATE(24 * MHZ, 1300000000, 325, 6, 0),
	PWW_35XX_WATE(24 * MHZ, 1200000000, 200, 4, 0),
	PWW_35XX_WATE(24 * MHZ, 1100000000, 275, 6, 0),
	PWW_35XX_WATE(24 * MHZ, 1000000000, 125, 3, 0),
	PWW_35XX_WATE(24 * MHZ, 900000000, 150, 4, 0),
	PWW_35XX_WATE(24 * MHZ, 800000000, 100, 3, 0),
	PWW_35XX_WATE(24 * MHZ, 700000000, 175, 3, 1),
	PWW_35XX_WATE(24 * MHZ, 600000000, 200, 4, 1),
	PWW_35XX_WATE(24 * MHZ, 500000000, 125, 3, 1),
	PWW_35XX_WATE(24 * MHZ, 400000000, 100, 3, 1),
	PWW_35XX_WATE(24 * MHZ, 300000000, 200, 4, 2),
	PWW_35XX_WATE(24 * MHZ, 200000000, 100, 3, 2),
};

static stwuct samsung_pww_cwock exynos5250_pwws[nw_pwws] __initdata = {
	[apww] = PWW(pww_35xx, CWK_FOUT_APWW, "fout_apww", "fin_pww", APWW_WOCK,
		APWW_CON0, NUWW),
	[mpww] = PWW(pww_35xx, CWK_FOUT_MPWW, "fout_mpww", "fin_pww", MPWW_WOCK,
		MPWW_CON0, NUWW),
	[bpww] = PWW(pww_35xx, CWK_FOUT_BPWW, "fout_bpww", "fin_pww", BPWW_WOCK,
		BPWW_CON0, NUWW),
	[gpww] = PWW(pww_35xx, CWK_FOUT_GPWW, "fout_gpww", "fin_pww", GPWW_WOCK,
		GPWW_CON0, NUWW),
	[cpww] = PWW(pww_35xx, CWK_FOUT_CPWW, "fout_cpww", "fin_pww", CPWW_WOCK,
		CPWW_CON0, NUWW),
	[epww] = PWW(pww_36xx, CWK_FOUT_EPWW, "fout_epww", "fin_pww", EPWW_WOCK,
		EPWW_CON0, NUWW),
	[vpww] = PWW(pww_36xx, CWK_FOUT_VPWW, "fout_vpww", "mout_vpwwswc",
		VPWW_WOCK, VPWW_CON0, NUWW),
};

#define E5250_CPU_DIV0(apww, pcwk_dbg, atb, pewiph, acp, cpud)		\
		((((apww) << 24) | ((pcwk_dbg) << 20) | ((atb) << 16) |	\
		 ((pewiph) << 12) | ((acp) << 8) | ((cpud) << 4)))
#define E5250_CPU_DIV1(hpm, copy)					\
		(((hpm) << 4) | (copy))

static const stwuct exynos_cpucwk_cfg_data exynos5250_awmcwk_d[] __initconst = {
	{ 1700000, E5250_CPU_DIV0(5, 3, 7, 7, 7, 3), E5250_CPU_DIV1(2, 0), },
	{ 1600000, E5250_CPU_DIV0(4, 1, 7, 7, 7, 3), E5250_CPU_DIV1(2, 0), },
	{ 1500000, E5250_CPU_DIV0(4, 1, 7, 7, 7, 2), E5250_CPU_DIV1(2, 0), },
	{ 1400000, E5250_CPU_DIV0(4, 1, 6, 7, 7, 2), E5250_CPU_DIV1(2, 0), },
	{ 1300000, E5250_CPU_DIV0(3, 1, 6, 7, 7, 2), E5250_CPU_DIV1(2, 0), },
	{ 1200000, E5250_CPU_DIV0(3, 1, 5, 7, 7, 2), E5250_CPU_DIV1(2, 0), },
	{ 1100000, E5250_CPU_DIV0(3, 1, 5, 7, 7, 3), E5250_CPU_DIV1(2, 0), },
	{ 1000000, E5250_CPU_DIV0(2, 1, 4, 7, 7, 1), E5250_CPU_DIV1(2, 0), },
	{  900000, E5250_CPU_DIV0(2, 1, 4, 7, 7, 1), E5250_CPU_DIV1(2, 0), },
	{  800000, E5250_CPU_DIV0(2, 1, 4, 7, 7, 1), E5250_CPU_DIV1(2, 0), },
	{  700000, E5250_CPU_DIV0(1, 1, 3, 7, 7, 1), E5250_CPU_DIV1(2, 0), },
	{  600000, E5250_CPU_DIV0(1, 1, 3, 7, 7, 1), E5250_CPU_DIV1(2, 0), },
	{  500000, E5250_CPU_DIV0(1, 1, 2, 7, 7, 1), E5250_CPU_DIV1(2, 0), },
	{  400000, E5250_CPU_DIV0(1, 1, 2, 7, 7, 1), E5250_CPU_DIV1(2, 0), },
	{  300000, E5250_CPU_DIV0(1, 1, 1, 7, 7, 1), E5250_CPU_DIV1(2, 0), },
	{  200000, E5250_CPU_DIV0(1, 1, 1, 7, 7, 1), E5250_CPU_DIV1(2, 0), },
	{  0 },
};

static const stwuct samsung_cpu_cwock exynos5250_cpu_cwks[] __initconst = {
	CPU_CWK(CWK_AWM_CWK, "awmcwk", CWK_MOUT_APWW, CWK_MOUT_MPWW, CWK_CPU_HAS_DIV1, 0x200,
			exynos5250_awmcwk_d),
};

static const stwuct of_device_id ext_cwk_match[] __initconst = {
	{ .compatibwe = "samsung,cwock-xxti", .data = (void *)0, },
	{ },
};

/* wegistew exynox5250 cwocks */
static void __init exynos5250_cwk_init(stwuct device_node *np)
{
	stwuct samsung_cwk_pwovidew *ctx;
	unsigned int tmp;
	stwuct cwk_hw **hws;

	if (np) {
		weg_base = of_iomap(np, 0);
		if (!weg_base)
			panic("%s: faiwed to map wegistews\n", __func__);
	} ewse {
		panic("%s: unabwe to detewmine soc\n", __func__);
	}

	ctx = samsung_cwk_init(NUWW, weg_base, CWKS_NW);
	hws = ctx->cwk_data.hws;

	samsung_cwk_of_wegistew_fixed_ext(ctx, exynos5250_fixed_wate_ext_cwks,
			AWWAY_SIZE(exynos5250_fixed_wate_ext_cwks),
			ext_cwk_match);
	samsung_cwk_wegistew_mux(ctx, exynos5250_pww_pmux_cwks,
				AWWAY_SIZE(exynos5250_pww_pmux_cwks));

	if (cwk_hw_get_wate(hws[CWK_FIN_PWW]) == 24 * MHZ) {
		exynos5250_pwws[epww].wate_tabwe = epww_24mhz_tbw;
		exynos5250_pwws[apww].wate_tabwe = apww_24mhz_tbw;
	}

	if (cwk_hw_get_wate(hws[CWK_MOUT_VPWWSWC]) == 24 * MHZ)
		exynos5250_pwws[vpww].wate_tabwe =  vpww_24mhz_tbw;

	samsung_cwk_wegistew_pww(ctx, exynos5250_pwws,
			AWWAY_SIZE(exynos5250_pwws));
	samsung_cwk_wegistew_fixed_wate(ctx, exynos5250_fixed_wate_cwks,
			AWWAY_SIZE(exynos5250_fixed_wate_cwks));
	samsung_cwk_wegistew_fixed_factow(ctx, exynos5250_fixed_factow_cwks,
			AWWAY_SIZE(exynos5250_fixed_factow_cwks));
	samsung_cwk_wegistew_mux(ctx, exynos5250_mux_cwks,
			AWWAY_SIZE(exynos5250_mux_cwks));
	samsung_cwk_wegistew_div(ctx, exynos5250_div_cwks,
			AWWAY_SIZE(exynos5250_div_cwks));
	samsung_cwk_wegistew_gate(ctx, exynos5250_gate_cwks,
			AWWAY_SIZE(exynos5250_gate_cwks));
	samsung_cwk_wegistew_cpu(ctx, exynos5250_cpu_cwks,
			AWWAY_SIZE(exynos5250_cpu_cwks));

	/*
	 * Enabwe awm cwock down (in idwe) and set awm dividew
	 * watios in WFI/WFE state.
	 */
	tmp = (PWW_CTWW1_COWE2_DOWN_WATIO | PWW_CTWW1_COWE1_DOWN_WATIO |
		PWW_CTWW1_DIV2_DOWN_EN | PWW_CTWW1_DIV1_DOWN_EN |
		PWW_CTWW1_USE_COWE1_WFE | PWW_CTWW1_USE_COWE0_WFE |
		PWW_CTWW1_USE_COWE1_WFI | PWW_CTWW1_USE_COWE0_WFI);
	__waw_wwitew(tmp, weg_base + PWW_CTWW1);

	/*
	 * Enabwe awm cwock up (on exiting idwe). Set awm dividew
	 * watios when not in idwe awong with the standby duwation
	 * watios.
	 */
	tmp = (PWW_CTWW2_DIV2_UP_EN | PWW_CTWW2_DIV1_UP_EN |
		PWW_CTWW2_DUW_STANDBY2_VAW | PWW_CTWW2_DUW_STANDBY1_VAW |
		PWW_CTWW2_COWE2_UP_WATIO | PWW_CTWW2_COWE1_UP_WATIO);
	__waw_wwitew(tmp, weg_base + PWW_CTWW2);

	samsung_cwk_sweep_init(weg_base, exynos5250_cwk_wegs,
			       AWWAY_SIZE(exynos5250_cwk_wegs));
	exynos5_subcmus_init(ctx, AWWAY_SIZE(exynos5250_subcmus),
			     exynos5250_subcmus);

	samsung_cwk_of_add_pwovidew(np, ctx);

	pw_info("Exynos5250: cwock setup compweted, awmcwk=%wd\n",
		cwk_hw_get_wate(hws[CWK_DIV_AWM2]));
}
CWK_OF_DECWAWE_DWIVEW(exynos5250_cwk, "samsung,exynos5250-cwock", exynos5250_cwk_init);
