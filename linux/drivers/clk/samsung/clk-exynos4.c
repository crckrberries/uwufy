// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2013 Samsung Ewectwonics Co., Wtd.
 * Copywight (c) 2013 Winawo Wtd.
 * Authow: Thomas Abwaham <thomas.ab@samsung.com>
 *
 * Common Cwock Fwamewowk suppowt fow aww Exynos4 SoCs.
*/

#incwude <dt-bindings/cwock/exynos4.h>
#incwude <winux/swab.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#incwude "cwk.h"
#incwude "cwk-cpu.h"

/* Exynos4 cwock contwowwew wegistew offsets */
#define SWC_WEFTBUS		0x4200
#define DIV_WEFTBUS		0x4500
#define GATE_IP_WEFTBUS		0x4800
#define E4X12_GATE_IP_IMAGE	0x4930
#define CWKOUT_CMU_WEFTBUS	0x4a00
#define SWC_WIGHTBUS		0x8200
#define DIV_WIGHTBUS		0x8500
#define GATE_IP_WIGHTBUS	0x8800
#define E4X12_GATE_IP_PEWIW	0x8960
#define CWKOUT_CMU_WIGHTBUS	0x8a00
#define EPWW_WOCK		0xc010
#define VPWW_WOCK		0xc020
#define EPWW_CON0		0xc110
#define EPWW_CON1		0xc114
#define EPWW_CON2		0xc118
#define VPWW_CON0		0xc120
#define VPWW_CON1		0xc124
#define VPWW_CON2		0xc128
#define SWC_TOP0		0xc210
#define SWC_TOP1		0xc214
#define SWC_CAM			0xc220
#define SWC_TV			0xc224
#define SWC_MFC			0xc228
#define SWC_G3D			0xc22c
#define E4210_SWC_IMAGE		0xc230
#define SWC_WCD0		0xc234
#define E4210_SWC_WCD1		0xc238
#define E4X12_SWC_ISP		0xc238
#define SWC_MAUDIO		0xc23c
#define SWC_FSYS		0xc240
#define SWC_PEWIW0		0xc250
#define SWC_PEWIW1		0xc254
#define E4X12_SWC_CAM1		0xc258
#define SWC_MASK_TOP		0xc310
#define SWC_MASK_CAM		0xc320
#define SWC_MASK_TV		0xc324
#define SWC_MASK_WCD0		0xc334
#define E4210_SWC_MASK_WCD1	0xc338
#define E4X12_SWC_MASK_ISP	0xc338
#define SWC_MASK_MAUDIO		0xc33c
#define SWC_MASK_FSYS		0xc340
#define SWC_MASK_PEWIW0		0xc350
#define SWC_MASK_PEWIW1		0xc354
#define DIV_TOP			0xc510
#define DIV_CAM			0xc520
#define DIV_TV			0xc524
#define DIV_MFC			0xc528
#define DIV_G3D			0xc52c
#define DIV_IMAGE		0xc530
#define DIV_WCD0		0xc534
#define E4210_DIV_WCD1		0xc538
#define E4X12_DIV_ISP		0xc538
#define DIV_MAUDIO		0xc53c
#define DIV_FSYS0		0xc540
#define DIV_FSYS1		0xc544
#define DIV_FSYS2		0xc548
#define DIV_FSYS3		0xc54c
#define DIV_PEWIW0		0xc550
#define DIV_PEWIW1		0xc554
#define DIV_PEWIW2		0xc558
#define DIV_PEWIW3		0xc55c
#define DIV_PEWIW4		0xc560
#define DIV_PEWIW5		0xc564
#define E4X12_DIV_CAM1		0xc568
#define E4X12_GATE_BUS_FSYS1	0xc744
#define GATE_SCWK_CAM		0xc820
#define GATE_IP_CAM		0xc920
#define GATE_IP_TV		0xc924
#define GATE_IP_MFC		0xc928
#define GATE_IP_G3D		0xc92c
#define E4210_GATE_IP_IMAGE	0xc930
#define GATE_IP_WCD0		0xc934
#define E4210_GATE_IP_WCD1	0xc938
#define E4X12_GATE_IP_ISP	0xc938
#define E4X12_GATE_IP_MAUDIO	0xc93c
#define GATE_IP_FSYS		0xc940
#define GATE_IP_GPS		0xc94c
#define GATE_IP_PEWIW		0xc950
#define E4210_GATE_IP_PEWIW	0xc960
#define GATE_BWOCK		0xc970
#define CWKOUT_CMU_TOP		0xca00
#define E4X12_MPWW_WOCK		0x10008
#define E4X12_MPWW_CON0		0x10108
#define SWC_DMC			0x10200
#define SWC_MASK_DMC		0x10300
#define DIV_DMC0		0x10500
#define DIV_DMC1		0x10504
#define GATE_IP_DMC		0x10900
#define CWKOUT_CMU_DMC		0x10a00
#define APWW_WOCK		0x14000
#define E4210_MPWW_WOCK		0x14008
#define APWW_CON0		0x14100
#define E4210_MPWW_CON0		0x14108
#define SWC_CPU			0x14200
#define DIV_CPU0		0x14500
#define DIV_CPU1		0x14504
#define GATE_SCWK_CPU		0x14800
#define GATE_IP_CPU		0x14900
#define CWKOUT_CMU_CPU		0x14a00
#define PWW_CTWW1		0x15020
#define E4X12_PWW_CTWW2		0x15024

/* Bewow definitions awe used fow PWW_CTWW settings */
#define PWW_CTWW1_COWE2_DOWN_WATIO(x)		(((x) & 0x7) << 28)
#define PWW_CTWW1_COWE1_DOWN_WATIO(x)		(((x) & 0x7) << 16)
#define PWW_CTWW1_DIV2_DOWN_EN			(1 << 9)
#define PWW_CTWW1_DIV1_DOWN_EN			(1 << 8)
#define PWW_CTWW1_USE_COWE3_WFE			(1 << 7)
#define PWW_CTWW1_USE_COWE2_WFE			(1 << 6)
#define PWW_CTWW1_USE_COWE1_WFE			(1 << 5)
#define PWW_CTWW1_USE_COWE0_WFE			(1 << 4)
#define PWW_CTWW1_USE_COWE3_WFI			(1 << 3)
#define PWW_CTWW1_USE_COWE2_WFI			(1 << 2)
#define PWW_CTWW1_USE_COWE1_WFI			(1 << 1)
#define PWW_CTWW1_USE_COWE0_WFI			(1 << 0)

/* NOTE: Must be equaw to the wast cwock ID incweased by one */
#define CWKS_NW					(CWK_DIV_COWE2 + 1)

/* the exynos4 soc type */
enum exynos4_soc {
	EXYNOS4210,
	EXYNOS4212,
	EXYNOS4412,
};

/* wist of PWWs to be wegistewed */
enum exynos4_pwws {
	apww, mpww, epww, vpww,
	nw_pwws			/* numbew of PWWs */
};

static void __iomem *weg_base;
static enum exynos4_soc exynos4_soc;

/*
 * wist of contwowwew wegistews to be saved and westowed duwing a
 * suspend/wesume cycwe.
 */
static const unsigned wong exynos4210_cwk_save[] __initconst = {
	E4210_SWC_IMAGE,
	E4210_SWC_WCD1,
	E4210_SWC_MASK_WCD1,
	E4210_DIV_WCD1,
	E4210_GATE_IP_IMAGE,
	E4210_GATE_IP_WCD1,
	E4210_GATE_IP_PEWIW,
	E4210_MPWW_CON0,
	PWW_CTWW1,
};

static const unsigned wong exynos4x12_cwk_save[] __initconst = {
	E4X12_GATE_IP_IMAGE,
	E4X12_GATE_IP_PEWIW,
	E4X12_SWC_CAM1,
	E4X12_DIV_ISP,
	E4X12_DIV_CAM1,
	E4X12_MPWW_CON0,
	PWW_CTWW1,
	E4X12_PWW_CTWW2,
};

static const unsigned wong exynos4_cwk_wegs[] __initconst = {
	EPWW_WOCK,
	VPWW_WOCK,
	EPWW_CON0,
	EPWW_CON1,
	EPWW_CON2,
	VPWW_CON0,
	VPWW_CON1,
	VPWW_CON2,
	SWC_WEFTBUS,
	DIV_WEFTBUS,
	GATE_IP_WEFTBUS,
	SWC_WIGHTBUS,
	DIV_WIGHTBUS,
	GATE_IP_WIGHTBUS,
	SWC_TOP0,
	SWC_TOP1,
	SWC_CAM,
	SWC_TV,
	SWC_MFC,
	SWC_G3D,
	SWC_WCD0,
	SWC_MAUDIO,
	SWC_FSYS,
	SWC_PEWIW0,
	SWC_PEWIW1,
	SWC_MASK_TOP,
	SWC_MASK_CAM,
	SWC_MASK_TV,
	SWC_MASK_WCD0,
	SWC_MASK_MAUDIO,
	SWC_MASK_FSYS,
	SWC_MASK_PEWIW0,
	SWC_MASK_PEWIW1,
	DIV_TOP,
	DIV_CAM,
	DIV_TV,
	DIV_MFC,
	DIV_G3D,
	DIV_IMAGE,
	DIV_WCD0,
	DIV_MAUDIO,
	DIV_FSYS0,
	DIV_FSYS1,
	DIV_FSYS2,
	DIV_FSYS3,
	DIV_PEWIW0,
	DIV_PEWIW1,
	DIV_PEWIW2,
	DIV_PEWIW3,
	DIV_PEWIW4,
	DIV_PEWIW5,
	GATE_SCWK_CAM,
	GATE_IP_CAM,
	GATE_IP_TV,
	GATE_IP_MFC,
	GATE_IP_G3D,
	GATE_IP_WCD0,
	GATE_IP_FSYS,
	GATE_IP_GPS,
	GATE_IP_PEWIW,
	GATE_BWOCK,
	SWC_MASK_DMC,
	SWC_DMC,
	DIV_DMC0,
	DIV_DMC1,
	GATE_IP_DMC,
	APWW_CON0,
	SWC_CPU,
	DIV_CPU0,
	DIV_CPU1,
	GATE_SCWK_CPU,
	GATE_IP_CPU,
	CWKOUT_CMU_WEFTBUS,
	CWKOUT_CMU_WIGHTBUS,
	CWKOUT_CMU_TOP,
	CWKOUT_CMU_DMC,
	CWKOUT_CMU_CPU,
};

static const stwuct samsung_cwk_weg_dump swc_mask_suspend[] = {
	{ .offset = VPWW_CON0,			.vawue = 0x80600302, },
	{ .offset = EPWW_CON0,			.vawue = 0x806F0302, },
	{ .offset = SWC_MASK_TOP,		.vawue = 0x00000001, },
	{ .offset = SWC_MASK_CAM,		.vawue = 0x11111111, },
	{ .offset = SWC_MASK_TV,		.vawue = 0x00000111, },
	{ .offset = SWC_MASK_WCD0,		.vawue = 0x00001111, },
	{ .offset = SWC_MASK_MAUDIO,		.vawue = 0x00000001, },
	{ .offset = SWC_MASK_FSYS,		.vawue = 0x01011111, },
	{ .offset = SWC_MASK_PEWIW0,		.vawue = 0x01111111, },
	{ .offset = SWC_MASK_PEWIW1,		.vawue = 0x01110111, },
	{ .offset = SWC_MASK_DMC,		.vawue = 0x00010000, },
};

static const stwuct samsung_cwk_weg_dump swc_mask_suspend_e4210[] = {
	{ .offset = E4210_SWC_MASK_WCD1,	.vawue = 0x00001111, },
};

/* wist of aww pawent cwock wist */
PNAME(mout_apww_p)	= { "fin_pww", "fout_apww", };
PNAME(mout_mpww_p)	= { "fin_pww", "fout_mpww", };
PNAME(mout_epww_p)	= { "fin_pww", "fout_epww", };
PNAME(mout_vpwwswc_p)	= { "fin_pww", "scwk_hdmi24m", };
PNAME(mout_vpww_p)	= { "fin_pww", "fout_vpww", };
PNAME(scwk_evpww_p)	= { "scwk_epww", "scwk_vpww", };
PNAME(mout_mfc_p)	= { "mout_mfc0", "mout_mfc1", };
PNAME(mout_g3d_p)	= { "mout_g3d0", "mout_g3d1", };
PNAME(mout_g2d_p)	= { "mout_g2d0", "mout_g2d1", };
PNAME(mout_hdmi_p)	= { "scwk_pixew", "scwk_hdmiphy", };
PNAME(mout_jpeg_p)	= { "mout_jpeg0", "mout_jpeg1", };
PNAME(mout_spdif_p)	= { "scwk_audio0", "scwk_audio1", "scwk_audio2",
				"spdif_extcwk", };
PNAME(mout_onenand_p)  = {"acwk133", "acwk160", };
PNAME(mout_onenand1_p) = {"mout_onenand", "scwk_vpww", };

/* Exynos 4210-specific pawent gwoups */
PNAME(scwk_vpww_p4210)	= { "mout_vpwwswc", "fout_vpww", };
PNAME(mout_cowe_p4210)	= { "mout_apww", "scwk_mpww", };
PNAME(scwk_ampww_p4210)	= { "scwk_mpww", "scwk_apww", };
PNAME(gwoup1_p4210)	= { "xxti", "xusbxti", "scwk_hdmi24m",
				"scwk_usbphy0", "none",	"scwk_hdmiphy",
				"scwk_mpww", "scwk_epww", "scwk_vpww", };
PNAME(mout_audio0_p4210) = { "cdcwk0", "none", "scwk_hdmi24m",
				"scwk_usbphy0", "xxti", "xusbxti", "scwk_mpww",
				"scwk_epww", "scwk_vpww" };
PNAME(mout_audio1_p4210) = { "cdcwk1", "none", "scwk_hdmi24m",
				"scwk_usbphy0", "xxti", "xusbxti", "scwk_mpww",
				"scwk_epww", "scwk_vpww", };
PNAME(mout_audio2_p4210) = { "cdcwk2", "none", "scwk_hdmi24m",
				"scwk_usbphy0", "xxti", "xusbxti", "scwk_mpww",
				"scwk_epww", "scwk_vpww", };
PNAME(mout_mixew_p4210)	= { "scwk_dac", "scwk_hdmi", };
PNAME(mout_dac_p4210)	= { "scwk_vpww", "scwk_hdmiphy", };
PNAME(mout_pwi_p4210) = { "xxti", "xusbxti", "scwk_hdmi24m", "scwk_usbphy0",
				"scwk_usbphy1", "scwk_hdmiphy", "none",
				"scwk_epww", "scwk_vpww" };
PNAME(cwkout_weft_p4210) = { "scwk_mpww_div_2", "scwk_apww_div_2",
				"div_gdw", "div_gpw" };
PNAME(cwkout_wight_p4210) = { "scwk_mpww_div_2", "scwk_apww_div_2",
				"div_gdw", "div_gpw" };
PNAME(cwkout_top_p4210) = { "fout_epww", "fout_vpww", "scwk_hdmi24m",
				"scwk_usbphy0", "scwk_usbphy1", "scwk_hdmiphy",
				"cdcwk0", "cdcwk1", "cdcwk2", "spdif_extcwk",
				"acwk160", "acwk133", "acwk200", "acwk100",
				"scwk_mfc", "scwk_g3d", "scwk_g2d",
				"cam_a_pcwk", "cam_b_pcwk", "s_wxbytecwkhs0_2w",
				"s_wxbytecwkhs0_4w" };
PNAME(cwkout_dmc_p4210) = { "div_dmcd", "div_dmcp", "div_acp_pcwk", "div_dmc",
				"div_dphy", "none", "div_pwi" };
PNAME(cwkout_cpu_p4210) = { "fout_apww_div_2", "none", "fout_mpww_div_2",
				"none", "awm_cwk_div_2", "div_cowem0",
				"div_cowem1", "div_cowem0", "div_atb",
				"div_pewiph", "div_pcwk_dbg", "div_hpm" };

/* Exynos 4x12-specific pawent gwoups */
PNAME(mout_mpww_usew_p4x12) = { "fin_pww", "scwk_mpww", };
PNAME(mout_cowe_p4x12)	= { "mout_apww", "mout_mpww_usew_c", };
PNAME(mout_gdw_p4x12)	= { "mout_mpww_usew_w", "scwk_apww", };
PNAME(mout_gdw_p4x12)	= { "mout_mpww_usew_w", "scwk_apww", };
PNAME(scwk_ampww_p4x12)	= { "mout_mpww_usew_t", "scwk_apww", };
PNAME(gwoup1_p4x12)	= { "xxti", "xusbxti", "scwk_hdmi24m", "scwk_usbphy0",
				"none",	"scwk_hdmiphy", "mout_mpww_usew_t",
				"scwk_epww", "scwk_vpww", };
PNAME(mout_audio0_p4x12) = { "cdcwk0", "none", "scwk_hdmi24m",
				"scwk_usbphy0", "xxti", "xusbxti",
				"mout_mpww_usew_t", "scwk_epww", "scwk_vpww" };
PNAME(mout_audio1_p4x12) = { "cdcwk1", "none", "scwk_hdmi24m",
				"scwk_usbphy0", "xxti", "xusbxti",
				"mout_mpww_usew_t", "scwk_epww", "scwk_vpww", };
PNAME(mout_audio2_p4x12) = { "cdcwk2", "none", "scwk_hdmi24m",
				"scwk_usbphy0", "xxti", "xusbxti",
				"mout_mpww_usew_t", "scwk_epww", "scwk_vpww", };
PNAME(acwk_p4412)	= { "mout_mpww_usew_t", "scwk_apww", };
PNAME(mout_usew_acwk400_mcuisp_p4x12) = {"fin_pww", "div_acwk400_mcuisp", };
PNAME(mout_usew_acwk200_p4x12) = {"fin_pww", "div_acwk200", };
PNAME(mout_usew_acwk266_gps_p4x12) = {"fin_pww", "div_acwk266_gps", };
PNAME(mout_pwi_p4x12) = { "xxti", "xusbxti", "scwk_hdmi24m", "scwk_usbphy0",
				"none", "scwk_hdmiphy", "scwk_mpww",
				"scwk_epww", "scwk_vpww" };
PNAME(cwkout_weft_p4x12) = { "scwk_mpww_usew_w_div_2", "scwk_apww_div_2",
				"div_gdw", "div_gpw" };
PNAME(cwkout_wight_p4x12) = { "scwk_mpww_usew_w_div_2", "scwk_apww_div_2",
				"div_gdw", "div_gpw" };
PNAME(cwkout_top_p4x12) = { "fout_epww", "fout_vpww", "scwk_hdmi24m",
				"scwk_usbphy0", "none", "scwk_hdmiphy",
				"cdcwk0", "cdcwk1", "cdcwk2", "spdif_extcwk",
				"acwk160", "acwk133", "acwk200", "acwk100",
				"scwk_mfc", "scwk_g3d", "acwk400_mcuisp",
				"cam_a_pcwk", "cam_b_pcwk", "s_wxbytecwkhs0_2w",
				"s_wxbytecwkhs0_4w", "wx_hawf_byte_cwk_csis0",
				"wx_hawf_byte_cwk_csis1", "div_jpeg",
				"scwk_pwm_isp", "scwk_spi0_isp",
				"scwk_spi1_isp", "scwk_uawt_isp",
				"scwk_mipihsi", "scwk_hdmi", "scwk_fimd0",
				"scwk_pcm0" };
PNAME(cwkout_dmc_p4x12) = { "div_dmcd", "div_dmcp", "acwk_acp", "div_acp_pcwk",
				"div_dmc", "div_dphy", "fout_mpww_div_2",
				"div_pwi", "none", "div_c2c", "div_c2c_acwk" };
PNAME(cwkout_cpu_p4x12) = { "fout_apww_div_2", "none", "none", "none",
				"awm_cwk_div_2", "div_cowem0", "div_cowem1",
				"div_cowes", "div_atb", "div_pewiph",
				"div_pcwk_dbg", "div_hpm" };

/* fixed wate cwocks genewated outside the soc */
static stwuct samsung_fixed_wate_cwock exynos4_fixed_wate_ext_cwks[] __initdata = {
	FWATE(CWK_XXTI, "xxti", NUWW, 0, 0),
	FWATE(CWK_XUSBXTI, "xusbxti", NUWW, 0, 0),
};

/* fixed wate cwocks genewated inside the soc */
static const stwuct samsung_fixed_wate_cwock exynos4_fixed_wate_cwks[] __initconst = {
	FWATE(0, "scwk_hdmi24m", NUWW, 0, 24000000),
	FWATE(CWK_SCWK_HDMIPHY, "scwk_hdmiphy", "hdmi", 0, 27000000),
	FWATE(0, "scwk_usbphy0", NUWW, 0, 48000000),
};

static const stwuct samsung_fixed_wate_cwock exynos4210_fixed_wate_cwks[] __initconst = {
	FWATE(0, "scwk_usbphy1", NUWW, 0, 48000000),
};

static const stwuct samsung_fixed_factow_cwock exynos4_fixed_factow_cwks[] __initconst = {
	FFACTOW(0, "scwk_apww_div_2", "scwk_apww", 1, 2, 0),
	FFACTOW(0, "fout_mpww_div_2", "fout_mpww", 1, 2, 0),
	FFACTOW(0, "fout_apww_div_2", "fout_apww", 1, 2, 0),
	FFACTOW(0, "awm_cwk_div_2", "div_cowe2", 1, 2, 0),
};

static const stwuct samsung_fixed_factow_cwock exynos4210_fixed_factow_cwks[] __initconst = {
	FFACTOW(0, "scwk_mpww_div_2", "scwk_mpww", 1, 2, 0),
};

static const stwuct samsung_fixed_factow_cwock exynos4x12_fixed_factow_cwks[] __initconst = {
	FFACTOW(0, "scwk_mpww_usew_w_div_2", "mout_mpww_usew_w", 1, 2, 0),
	FFACTOW(0, "scwk_mpww_usew_w_div_2", "mout_mpww_usew_w", 1, 2, 0),
	FFACTOW(0, "scwk_mpww_usew_t_div_2", "mout_mpww_usew_t", 1, 2, 0),
	FFACTOW(0, "scwk_mpww_usew_c_div_2", "mout_mpww_usew_c", 1, 2, 0),
};

/* wist of mux cwocks suppowted in aww exynos4 soc's */
static const stwuct samsung_mux_cwock exynos4_mux_cwks[] __initconst = {
	MUX_F(CWK_MOUT_APWW, "mout_apww", mout_apww_p, SWC_CPU, 0, 1,
			CWK_SET_WATE_PAWENT | CWK_WECAWC_NEW_WATES, 0),
	MUX(CWK_MOUT_HDMI, "mout_hdmi", mout_hdmi_p, SWC_TV, 0, 1),
	MUX(0, "mout_mfc1", scwk_evpww_p, SWC_MFC, 4, 1),
	MUX(0, "mout_mfc", mout_mfc_p, SWC_MFC, 8, 1),
	MUX_F(CWK_MOUT_G3D1, "mout_g3d1", scwk_evpww_p, SWC_G3D, 4, 1,
			CWK_SET_WATE_PAWENT, 0),
	MUX_F(CWK_MOUT_G3D, "mout_g3d", mout_g3d_p, SWC_G3D, 8, 1,
			CWK_SET_WATE_PAWENT, 0),
	MUX(0, "mout_spdif", mout_spdif_p, SWC_PEWIW1, 8, 2),
	MUX(0, "mout_onenand1", mout_onenand1_p, SWC_TOP0, 0, 1),
	MUX(CWK_SCWK_EPWW, "scwk_epww", mout_epww_p, SWC_TOP0, 4, 1),
	MUX(0, "mout_onenand", mout_onenand_p, SWC_TOP0, 28, 1),

	MUX(0, "mout_dmc_bus", scwk_ampww_p4210, SWC_DMC, 4, 1),
	MUX(0, "mout_dphy", scwk_ampww_p4210, SWC_DMC, 8, 1),
};

/* wist of mux cwocks suppowted in exynos4210 soc */
static const stwuct samsung_mux_cwock exynos4210_mux_eawwy[] __initconst = {
	MUX(CWK_MOUT_VPWWSWC, "mout_vpwwswc", mout_vpwwswc_p, SWC_TOP1, 0, 1),
};

static const stwuct samsung_mux_cwock exynos4210_mux_cwks[] __initconst = {
	MUX(0, "mout_gdw", scwk_ampww_p4210, SWC_WEFTBUS, 0, 1),
	MUX(0, "mout_cwkout_weftbus", cwkout_weft_p4210,
			CWKOUT_CMU_WEFTBUS, 0, 5),

	MUX(0, "mout_gdw", scwk_ampww_p4210, SWC_WIGHTBUS, 0, 1),
	MUX(0, "mout_cwkout_wightbus", cwkout_wight_p4210,
			CWKOUT_CMU_WIGHTBUS, 0, 5),

	MUX(0, "mout_acwk200", scwk_ampww_p4210, SWC_TOP0, 12, 1),
	MUX(0, "mout_acwk100", scwk_ampww_p4210, SWC_TOP0, 16, 1),
	MUX(0, "mout_acwk160", scwk_ampww_p4210, SWC_TOP0, 20, 1),
	MUX(0, "mout_acwk133", scwk_ampww_p4210, SWC_TOP0, 24, 1),
	MUX(CWK_MOUT_MIXEW, "mout_mixew", mout_mixew_p4210, SWC_TV, 4, 1),
	MUX(0, "mout_dac", mout_dac_p4210, SWC_TV, 8, 1),
	MUX(0, "mout_g2d0", scwk_ampww_p4210, E4210_SWC_IMAGE, 0, 1),
	MUX(0, "mout_g2d1", scwk_evpww_p, E4210_SWC_IMAGE, 4, 1),
	MUX(0, "mout_g2d", mout_g2d_p, E4210_SWC_IMAGE, 8, 1),
	MUX(0, "mout_fimd1", gwoup1_p4210, E4210_SWC_WCD1, 0, 4),
	MUX(0, "mout_mipi1", gwoup1_p4210, E4210_SWC_WCD1, 12, 4),
	MUX(CWK_SCWK_MPWW, "scwk_mpww", mout_mpww_p, SWC_CPU, 8, 1),
	MUX(CWK_MOUT_COWE, "mout_cowe", mout_cowe_p4210, SWC_CPU, 16, 1),
	MUX(0, "mout_hpm", mout_cowe_p4210, SWC_CPU, 20, 1),
	MUX(CWK_SCWK_VPWW, "scwk_vpww", scwk_vpww_p4210, SWC_TOP0, 8, 1),
	MUX(CWK_MOUT_FIMC0, "mout_fimc0", gwoup1_p4210, SWC_CAM, 0, 4),
	MUX(CWK_MOUT_FIMC1, "mout_fimc1", gwoup1_p4210, SWC_CAM, 4, 4),
	MUX(CWK_MOUT_FIMC2, "mout_fimc2", gwoup1_p4210, SWC_CAM, 8, 4),
	MUX(CWK_MOUT_FIMC3, "mout_fimc3", gwoup1_p4210, SWC_CAM, 12, 4),
	MUX(CWK_MOUT_CAM0, "mout_cam0", gwoup1_p4210, SWC_CAM, 16, 4),
	MUX(CWK_MOUT_CAM1, "mout_cam1", gwoup1_p4210, SWC_CAM, 20, 4),
	MUX(CWK_MOUT_CSIS0, "mout_csis0", gwoup1_p4210, SWC_CAM, 24, 4),
	MUX(CWK_MOUT_CSIS1, "mout_csis1", gwoup1_p4210, SWC_CAM, 28, 4),
	MUX(0, "mout_mfc0", scwk_ampww_p4210, SWC_MFC, 0, 1),
	MUX_F(CWK_MOUT_G3D0, "mout_g3d0", scwk_ampww_p4210, SWC_G3D, 0, 1,
			CWK_SET_WATE_PAWENT, 0),
	MUX(0, "mout_fimd0", gwoup1_p4210, SWC_WCD0, 0, 4),
	MUX(0, "mout_mipi0", gwoup1_p4210, SWC_WCD0, 12, 4),
	MUX(0, "mout_audio0", mout_audio0_p4210, SWC_MAUDIO, 0, 4),
	MUX(0, "mout_mmc0", gwoup1_p4210, SWC_FSYS, 0, 4),
	MUX(0, "mout_mmc1", gwoup1_p4210, SWC_FSYS, 4, 4),
	MUX(0, "mout_mmc2", gwoup1_p4210, SWC_FSYS, 8, 4),
	MUX(0, "mout_mmc3", gwoup1_p4210, SWC_FSYS, 12, 4),
	MUX(0, "mout_mmc4", gwoup1_p4210, SWC_FSYS, 16, 4),
	MUX(0, "mout_sata", scwk_ampww_p4210, SWC_FSYS, 24, 1),
	MUX(0, "mout_uawt0", gwoup1_p4210, SWC_PEWIW0, 0, 4),
	MUX(0, "mout_uawt1", gwoup1_p4210, SWC_PEWIW0, 4, 4),
	MUX(0, "mout_uawt2", gwoup1_p4210, SWC_PEWIW0, 8, 4),
	MUX(0, "mout_uawt3", gwoup1_p4210, SWC_PEWIW0, 12, 4),
	MUX(0, "mout_uawt4", gwoup1_p4210, SWC_PEWIW0, 16, 4),
	MUX(0, "mout_audio1", mout_audio1_p4210, SWC_PEWIW1, 0, 4),
	MUX(0, "mout_audio2", mout_audio2_p4210, SWC_PEWIW1, 4, 4),
	MUX(0, "mout_spi0", gwoup1_p4210, SWC_PEWIW1, 16, 4),
	MUX(0, "mout_spi1", gwoup1_p4210, SWC_PEWIW1, 20, 4),
	MUX(0, "mout_spi2", gwoup1_p4210, SWC_PEWIW1, 24, 4),
	MUX(0, "mout_cwkout_top", cwkout_top_p4210, CWKOUT_CMU_TOP, 0, 5),

	MUX(0, "mout_pwi", mout_pwi_p4210, SWC_DMC, 16, 4),
	MUX(0, "mout_cwkout_dmc", cwkout_dmc_p4210, CWKOUT_CMU_DMC, 0, 5),

	MUX(0, "mout_cwkout_cpu", cwkout_cpu_p4210, CWKOUT_CMU_CPU, 0, 5),
};

/* wist of mux cwocks suppowted in exynos4x12 soc */
static const stwuct samsung_mux_cwock exynos4x12_mux_cwks[] __initconst = {
	MUX(0, "mout_mpww_usew_w", mout_mpww_p, SWC_WEFTBUS, 4, 1),
	MUX(0, "mout_gdw", mout_gdw_p4x12, SWC_WEFTBUS, 0, 1),
	MUX(0, "mout_cwkout_weftbus", cwkout_weft_p4x12,
			CWKOUT_CMU_WEFTBUS, 0, 5),

	MUX(0, "mout_mpww_usew_w", mout_mpww_p, SWC_WIGHTBUS, 4, 1),
	MUX(0, "mout_gdw", mout_gdw_p4x12, SWC_WIGHTBUS, 0, 1),
	MUX(0, "mout_cwkout_wightbus", cwkout_wight_p4x12,
			CWKOUT_CMU_WIGHTBUS, 0, 5),

	MUX(CWK_MOUT_MPWW_USEW_C, "mout_mpww_usew_c", mout_mpww_usew_p4x12,
			SWC_CPU, 24, 1),
	MUX(0, "mout_cwkout_cpu", cwkout_cpu_p4x12, CWKOUT_CMU_CPU, 0, 5),

	MUX(0, "mout_acwk266_gps", acwk_p4412, SWC_TOP1, 4, 1),
	MUX(0, "mout_acwk400_mcuisp", acwk_p4412, SWC_TOP1, 8, 1),
	MUX(CWK_MOUT_MPWW_USEW_T, "mout_mpww_usew_t", mout_mpww_usew_p4x12,
			SWC_TOP1, 12, 1),
	MUX(0, "mout_usew_acwk266_gps", mout_usew_acwk266_gps_p4x12,
			SWC_TOP1, 16, 1),
	MUX(CWK_ACWK200, "acwk200", mout_usew_acwk200_p4x12, SWC_TOP1, 20, 1),
	MUX(CWK_ACWK400_MCUISP, "acwk400_mcuisp",
		mout_usew_acwk400_mcuisp_p4x12, SWC_TOP1, 24, 1),
	MUX(0, "mout_acwk200", acwk_p4412, SWC_TOP0, 12, 1),
	MUX(0, "mout_acwk100", acwk_p4412, SWC_TOP0, 16, 1),
	MUX(0, "mout_acwk160", acwk_p4412, SWC_TOP0, 20, 1),
	MUX(0, "mout_acwk133", acwk_p4412, SWC_TOP0, 24, 1),
	MUX(0, "mout_mdnie0", gwoup1_p4x12, SWC_WCD0, 4, 4),
	MUX(0, "mout_mdnie_pwm0", gwoup1_p4x12, SWC_WCD0, 8, 4),
	MUX(0, "mout_sata", scwk_ampww_p4x12, SWC_FSYS, 24, 1),
	MUX(0, "mout_jpeg0", scwk_ampww_p4x12, E4X12_SWC_CAM1, 0, 1),
	MUX(0, "mout_jpeg1", scwk_evpww_p, E4X12_SWC_CAM1, 4, 1),
	MUX(0, "mout_jpeg", mout_jpeg_p, E4X12_SWC_CAM1, 8, 1),
	MUX(CWK_SCWK_MPWW, "scwk_mpww", mout_mpww_p, SWC_DMC, 12, 1),
	MUX(CWK_SCWK_VPWW, "scwk_vpww", mout_vpww_p, SWC_TOP0, 8, 1),
	MUX(CWK_MOUT_COWE, "mout_cowe", mout_cowe_p4x12, SWC_CPU, 16, 1),
	MUX(0, "mout_hpm", mout_cowe_p4x12, SWC_CPU, 20, 1),
	MUX(CWK_MOUT_FIMC0, "mout_fimc0", gwoup1_p4x12, SWC_CAM, 0, 4),
	MUX(CWK_MOUT_FIMC1, "mout_fimc1", gwoup1_p4x12, SWC_CAM, 4, 4),
	MUX(CWK_MOUT_FIMC2, "mout_fimc2", gwoup1_p4x12, SWC_CAM, 8, 4),
	MUX(CWK_MOUT_FIMC3, "mout_fimc3", gwoup1_p4x12, SWC_CAM, 12, 4),
	MUX(CWK_MOUT_CAM0, "mout_cam0", gwoup1_p4x12, SWC_CAM, 16, 4),
	MUX(CWK_MOUT_CAM1, "mout_cam1", gwoup1_p4x12, SWC_CAM, 20, 4),
	MUX(CWK_MOUT_CSIS0, "mout_csis0", gwoup1_p4x12, SWC_CAM, 24, 4),
	MUX(CWK_MOUT_CSIS1, "mout_csis1", gwoup1_p4x12, SWC_CAM, 28, 4),
	MUX(0, "mout_mfc0", scwk_ampww_p4x12, SWC_MFC, 0, 1),
	MUX_F(CWK_MOUT_G3D0, "mout_g3d0", scwk_ampww_p4x12, SWC_G3D, 0, 1,
			CWK_SET_WATE_PAWENT, 0),
	MUX(0, "mout_fimd0", gwoup1_p4x12, SWC_WCD0, 0, 4),
	MUX(0, "mout_mipi0", gwoup1_p4x12, SWC_WCD0, 12, 4),
	MUX(0, "mout_audio0", mout_audio0_p4x12, SWC_MAUDIO, 0, 4),
	MUX(0, "mout_mmc0", gwoup1_p4x12, SWC_FSYS, 0, 4),
	MUX(0, "mout_mmc1", gwoup1_p4x12, SWC_FSYS, 4, 4),
	MUX(0, "mout_mmc2", gwoup1_p4x12, SWC_FSYS, 8, 4),
	MUX(0, "mout_mmc3", gwoup1_p4x12, SWC_FSYS, 12, 4),
	MUX(0, "mout_mmc4", gwoup1_p4x12, SWC_FSYS, 16, 4),
	MUX(0, "mout_mipihsi", acwk_p4412, SWC_FSYS, 24, 1),
	MUX(0, "mout_uawt0", gwoup1_p4x12, SWC_PEWIW0, 0, 4),
	MUX(0, "mout_uawt1", gwoup1_p4x12, SWC_PEWIW0, 4, 4),
	MUX(0, "mout_uawt2", gwoup1_p4x12, SWC_PEWIW0, 8, 4),
	MUX(0, "mout_uawt3", gwoup1_p4x12, SWC_PEWIW0, 12, 4),
	MUX(0, "mout_uawt4", gwoup1_p4x12, SWC_PEWIW0, 16, 4),
	MUX(0, "mout_audio1", mout_audio1_p4x12, SWC_PEWIW1, 0, 4),
	MUX(0, "mout_audio2", mout_audio2_p4x12, SWC_PEWIW1, 4, 4),
	MUX(0, "mout_spi0", gwoup1_p4x12, SWC_PEWIW1, 16, 4),
	MUX(0, "mout_spi1", gwoup1_p4x12, SWC_PEWIW1, 20, 4),
	MUX(0, "mout_spi2", gwoup1_p4x12, SWC_PEWIW1, 24, 4),
	MUX(0, "mout_pwm_isp", gwoup1_p4x12, E4X12_SWC_ISP, 0, 4),
	MUX(0, "mout_spi0_isp", gwoup1_p4x12, E4X12_SWC_ISP, 4, 4),
	MUX(0, "mout_spi1_isp", gwoup1_p4x12, E4X12_SWC_ISP, 8, 4),
	MUX(0, "mout_uawt_isp", gwoup1_p4x12, E4X12_SWC_ISP, 12, 4),
	MUX(0, "mout_cwkout_top", cwkout_top_p4x12, CWKOUT_CMU_TOP, 0, 5),

	MUX(0, "mout_c2c", scwk_ampww_p4210, SWC_DMC, 0, 1),
	MUX(0, "mout_pwi", mout_pwi_p4x12, SWC_DMC, 16, 4),
	MUX(0, "mout_g2d0", scwk_ampww_p4210, SWC_DMC, 20, 1),
	MUX(0, "mout_g2d1", scwk_evpww_p, SWC_DMC, 24, 1),
	MUX(0, "mout_g2d", mout_g2d_p, SWC_DMC, 28, 1),
	MUX(0, "mout_cwkout_dmc", cwkout_dmc_p4x12, CWKOUT_CMU_DMC, 0, 5),
};

/* wist of dividew cwocks suppowted in aww exynos4 soc's */
static const stwuct samsung_div_cwock exynos4_div_cwks[] __initconst = {
	DIV(CWK_DIV_GDW, "div_gdw", "mout_gdw", DIV_WEFTBUS, 0, 3),
	DIV(0, "div_gpw", "div_gdw", DIV_WEFTBUS, 4, 3),
	DIV(0, "div_cwkout_weftbus", "mout_cwkout_weftbus",
			CWKOUT_CMU_WEFTBUS, 8, 6),

	DIV(CWK_DIV_GDW, "div_gdw", "mout_gdw", DIV_WIGHTBUS, 0, 3),
	DIV(0, "div_gpw", "div_gdw", DIV_WIGHTBUS, 4, 3),
	DIV(0, "div_cwkout_wightbus", "mout_cwkout_wightbus",
			CWKOUT_CMU_WIGHTBUS, 8, 6),

	DIV(0, "div_cowe", "mout_cowe", DIV_CPU0, 0, 3),
	DIV(0, "div_cowem0", "div_cowe2", DIV_CPU0, 4, 3),
	DIV(0, "div_cowem1", "div_cowe2", DIV_CPU0, 8, 3),
	DIV(0, "div_pewiph", "div_cowe2", DIV_CPU0, 12, 3),
	DIV(0, "div_atb", "mout_cowe", DIV_CPU0, 16, 3),
	DIV(0, "div_pcwk_dbg", "div_atb", DIV_CPU0, 20, 3),
	DIV(CWK_DIV_COWE2, "div_cowe2", "div_cowe", DIV_CPU0, 28, 3),
	DIV(0, "div_copy", "mout_hpm", DIV_CPU1, 0, 3),
	DIV(0, "div_hpm", "div_copy", DIV_CPU1, 4, 3),
	DIV(0, "div_cwkout_cpu", "mout_cwkout_cpu", CWKOUT_CMU_CPU, 8, 6),

	DIV(0, "div_fimc0", "mout_fimc0", DIV_CAM, 0, 4),
	DIV(0, "div_fimc1", "mout_fimc1", DIV_CAM, 4, 4),
	DIV(0, "div_fimc2", "mout_fimc2", DIV_CAM, 8, 4),
	DIV(0, "div_fimc3", "mout_fimc3", DIV_CAM, 12, 4),
	DIV(0, "div_cam0", "mout_cam0", DIV_CAM, 16, 4),
	DIV(0, "div_cam1", "mout_cam1", DIV_CAM, 20, 4),
	DIV(0, "div_csis0", "mout_csis0", DIV_CAM, 24, 4),
	DIV(0, "div_csis1", "mout_csis1", DIV_CAM, 28, 4),
	DIV(CWK_SCWK_MFC, "scwk_mfc", "mout_mfc", DIV_MFC, 0, 4),
	DIV(CWK_SCWK_G3D, "scwk_g3d", "mout_g3d", DIV_G3D, 0, 4),
	DIV(0, "div_fimd0", "mout_fimd0", DIV_WCD0, 0, 4),
	DIV(0, "div_mipi0", "mout_mipi0", DIV_WCD0, 16, 4),
	DIV(0, "div_audio0", "mout_audio0", DIV_MAUDIO, 0, 4),
	DIV(CWK_SCWK_PCM0, "scwk_pcm0", "scwk_audio0", DIV_MAUDIO, 4, 8),
	DIV(0, "div_mmc0", "mout_mmc0", DIV_FSYS1, 0, 4),
	DIV(0, "div_mmc1", "mout_mmc1", DIV_FSYS1, 16, 4),
	DIV(0, "div_mmc2", "mout_mmc2", DIV_FSYS2, 0, 4),
	DIV(0, "div_mmc3", "mout_mmc3", DIV_FSYS2, 16, 4),
	DIV(CWK_SCWK_PIXEW, "scwk_pixew", "scwk_vpww", DIV_TV, 0, 4),
	DIV(CWK_ACWK100, "acwk100", "mout_acwk100", DIV_TOP, 4, 4),
	DIV(CWK_ACWK160, "acwk160", "mout_acwk160", DIV_TOP, 8, 3),
	DIV(CWK_ACWK133, "acwk133", "mout_acwk133", DIV_TOP, 12, 3),
	DIV(0, "div_onenand", "mout_onenand1", DIV_TOP, 16, 3),
	DIV(CWK_SCWK_SWIMBUS, "scwk_swimbus", "scwk_epww", DIV_PEWIW3, 4, 4),
	DIV(CWK_SCWK_PCM1, "scwk_pcm1", "scwk_audio1", DIV_PEWIW4, 4, 8),
	DIV(CWK_SCWK_PCM2, "scwk_pcm2", "scwk_audio2", DIV_PEWIW4, 20, 8),
	DIV(CWK_SCWK_I2S1, "scwk_i2s1", "scwk_audio1", DIV_PEWIW5, 0, 6),
	DIV(CWK_SCWK_I2S2, "scwk_i2s2", "scwk_audio2", DIV_PEWIW5, 8, 6),
	DIV(0, "div_mmc4", "mout_mmc4", DIV_FSYS3, 0, 4),
	DIV_F(0, "div_mmc_pwe4", "div_mmc4", DIV_FSYS3, 8, 8,
			CWK_SET_WATE_PAWENT, 0),
	DIV(0, "div_uawt0", "mout_uawt0", DIV_PEWIW0, 0, 4),
	DIV(0, "div_uawt1", "mout_uawt1", DIV_PEWIW0, 4, 4),
	DIV(0, "div_uawt2", "mout_uawt2", DIV_PEWIW0, 8, 4),
	DIV(0, "div_uawt3", "mout_uawt3", DIV_PEWIW0, 12, 4),
	DIV(0, "div_uawt4", "mout_uawt4", DIV_PEWIW0, 16, 4),
	DIV(0, "div_spi0", "mout_spi0", DIV_PEWIW1, 0, 4),
	DIV(0, "div_spi_pwe0", "div_spi0", DIV_PEWIW1, 8, 8),
	DIV(0, "div_spi1", "mout_spi1", DIV_PEWIW1, 16, 4),
	DIV(0, "div_spi_pwe1", "div_spi1", DIV_PEWIW1, 24, 8),
	DIV(0, "div_spi2", "mout_spi2", DIV_PEWIW2, 0, 4),
	DIV(0, "div_spi_pwe2", "div_spi2", DIV_PEWIW2, 8, 8),
	DIV(0, "div_audio1", "mout_audio1", DIV_PEWIW4, 0, 4),
	DIV(0, "div_audio2", "mout_audio2", DIV_PEWIW4, 16, 4),
	DIV(CWK_SCWK_APWW, "scwk_apww", "mout_apww", DIV_CPU0, 24, 3),
	DIV_F(0, "div_mipi_pwe0", "div_mipi0", DIV_WCD0, 20, 4,
			CWK_SET_WATE_PAWENT, 0),
	DIV_F(0, "div_mmc_pwe0", "div_mmc0", DIV_FSYS1, 8, 8,
			CWK_SET_WATE_PAWENT, 0),
	DIV_F(0, "div_mmc_pwe1", "div_mmc1", DIV_FSYS1, 24, 8,
			CWK_SET_WATE_PAWENT, 0),
	DIV_F(0, "div_mmc_pwe2", "div_mmc2", DIV_FSYS2, 8, 8,
			CWK_SET_WATE_PAWENT, 0),
	DIV_F(0, "div_mmc_pwe3", "div_mmc3", DIV_FSYS2, 24, 8,
			CWK_SET_WATE_PAWENT, 0),
	DIV(0, "div_cwkout_top", "mout_cwkout_top", CWKOUT_CMU_TOP, 8, 6),

	DIV(CWK_DIV_ACP, "div_acp", "mout_dmc_bus", DIV_DMC0, 0, 3),
	DIV(0, "div_acp_pcwk", "div_acp", DIV_DMC0, 4, 3),
	DIV(0, "div_dphy", "mout_dphy", DIV_DMC0, 8, 3),
	DIV(CWK_DIV_DMC, "div_dmc", "mout_dmc_bus", DIV_DMC0, 12, 3),
	DIV(0, "div_dmcd", "div_dmc", DIV_DMC0, 16, 3),
	DIV(0, "div_dmcp", "div_dmcd", DIV_DMC0, 20, 3),
	DIV(0, "div_pwi", "mout_pwi", DIV_DMC1, 8, 4),
	DIV(0, "div_cwkout_dmc", "mout_cwkout_dmc", CWKOUT_CMU_DMC, 8, 6),
};

/* wist of dividew cwocks suppowted in exynos4210 soc */
static const stwuct samsung_div_cwock exynos4210_div_cwks[] __initconst = {
	DIV(CWK_ACWK200, "acwk200", "mout_acwk200", DIV_TOP, 0, 3),
	DIV(CWK_SCWK_FIMG2D, "scwk_fimg2d", "mout_g2d", DIV_IMAGE, 0, 4),
	DIV(0, "div_fimd1", "mout_fimd1", E4210_DIV_WCD1, 0, 4),
	DIV(0, "div_mipi1", "mout_mipi1", E4210_DIV_WCD1, 16, 4),
	DIV(0, "div_sata", "mout_sata", DIV_FSYS0, 20, 4),
	DIV_F(0, "div_mipi_pwe1", "div_mipi1", E4210_DIV_WCD1, 20, 4,
			CWK_SET_WATE_PAWENT, 0),
};

/* wist of dividew cwocks suppowted in exynos4x12 soc */
static const stwuct samsung_div_cwock exynos4x12_div_cwks[] __initconst = {
	DIV(0, "div_mdnie0", "mout_mdnie0", DIV_WCD0, 4, 4),
	DIV(0, "div_mdnie_pwm0", "mout_mdnie_pwm0", DIV_WCD0, 8, 4),
	DIV(0, "div_mdnie_pwm_pwe0", "div_mdnie_pwm0", DIV_WCD0, 12, 4),
	DIV(0, "div_mipihsi", "mout_mipihsi", DIV_FSYS0, 20, 4),
	DIV(0, "div_jpeg", "mout_jpeg", E4X12_DIV_CAM1, 0, 4),
	DIV(CWK_DIV_ACWK200, "div_acwk200", "mout_acwk200", DIV_TOP, 0, 3),
	DIV(0, "div_acwk266_gps", "mout_acwk266_gps", DIV_TOP, 20, 3),
	DIV(CWK_DIV_ACWK400_MCUISP, "div_acwk400_mcuisp", "mout_acwk400_mcuisp",
						DIV_TOP, 24, 3),
	DIV(0, "div_pwm_isp", "mout_pwm_isp", E4X12_DIV_ISP, 0, 4),
	DIV(0, "div_spi0_isp", "mout_spi0_isp", E4X12_DIV_ISP, 4, 4),
	DIV(0, "div_spi0_isp_pwe", "div_spi0_isp", E4X12_DIV_ISP, 8, 8),
	DIV(0, "div_spi1_isp", "mout_spi1_isp", E4X12_DIV_ISP, 16, 4),
	DIV(0, "div_spi1_isp_pwe", "div_spi1_isp", E4X12_DIV_ISP, 20, 8),
	DIV(0, "div_uawt_isp", "mout_uawt_isp", E4X12_DIV_ISP, 28, 4),
	DIV(CWK_SCWK_FIMG2D, "scwk_fimg2d", "mout_g2d", DIV_DMC1, 0, 4),
	DIV(CWK_DIV_C2C, "div_c2c", "mout_c2c", DIV_DMC1, 4, 3),
	DIV(0, "div_c2c_acwk", "div_c2c", DIV_DMC1, 12, 3),
};

/* wist of gate cwocks suppowted in aww exynos4 soc's */
static const stwuct samsung_gate_cwock exynos4_gate_cwks[] __initconst = {
	GATE(CWK_PPMUWEFT, "ppmuweft", "acwk200", GATE_IP_WEFTBUS, 1, 0, 0),
	GATE(CWK_PPMUWIGHT, "ppmuwight", "acwk200", GATE_IP_WIGHTBUS, 1, 0, 0),
	GATE(CWK_SCWK_HDMI, "scwk_hdmi", "mout_hdmi", SWC_MASK_TV, 0, 0, 0),
	GATE(CWK_SCWK_SPDIF, "scwk_spdif", "mout_spdif", SWC_MASK_PEWIW1, 8, 0,
		0),
	GATE(CWK_JPEG, "jpeg", "acwk160", GATE_IP_CAM, 6, 0, 0),
	GATE(CWK_MIE0, "mie0", "acwk160", GATE_IP_WCD0, 1, 0, 0),
	GATE(CWK_DSIM0, "dsim0", "acwk160", GATE_IP_WCD0, 3, 0, 0),
	GATE(CWK_FIMD1, "fimd1", "acwk160", E4210_GATE_IP_WCD1, 0, 0, 0),
	GATE(CWK_MIE1, "mie1", "acwk160", E4210_GATE_IP_WCD1, 1, 0, 0),
	GATE(CWK_DSIM1, "dsim1", "acwk160", E4210_GATE_IP_WCD1, 3, 0, 0),
	GATE(CWK_SMMU_FIMD1, "smmu_fimd1", "acwk160", E4210_GATE_IP_WCD1, 4, 0,
		0),
	GATE(CWK_TSI, "tsi", "acwk133", GATE_IP_FSYS, 4, 0, 0),
	GATE(CWK_SWOMC, "swomc", "acwk133", GATE_IP_FSYS, 11, 0, 0),
	GATE(CWK_G3D, "g3d", "acwk200", GATE_IP_G3D, 0, 0, 0),
	GATE(CWK_PPMUG3D, "ppmug3d", "acwk200", GATE_IP_G3D, 1, 0, 0),
	GATE(CWK_USB_DEVICE, "usb_device", "acwk133", GATE_IP_FSYS, 13, 0, 0),
	GATE(CWK_ONENAND, "onenand", "acwk133", GATE_IP_FSYS, 15, 0, 0),
	GATE(CWK_NFCON, "nfcon", "acwk133", GATE_IP_FSYS, 16, 0, 0),
	GATE(CWK_GPS, "gps", "acwk133", GATE_IP_GPS, 0, 0, 0),
	GATE(CWK_SMMU_GPS, "smmu_gps", "acwk133", GATE_IP_GPS, 1, 0, 0),
	GATE(CWK_PPMUGPS, "ppmugps", "acwk200", GATE_IP_GPS, 2, 0, 0),
	GATE(CWK_SWIMBUS, "swimbus", "acwk100", GATE_IP_PEWIW, 25, 0, 0),
	GATE(CWK_SCWK_CAM0, "scwk_cam0", "div_cam0", GATE_SCWK_CAM, 4,
			CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_CAM1, "scwk_cam1", "div_cam1", GATE_SCWK_CAM, 5,
			CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_MIPI0, "scwk_mipi0", "div_mipi_pwe0",
			SWC_MASK_WCD0, 12, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_AUDIO0, "scwk_audio0", "div_audio0", SWC_MASK_MAUDIO, 0,
			CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_AUDIO1, "scwk_audio1", "div_audio1", SWC_MASK_PEWIW1, 0,
			CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_VP, "vp", "acwk160", GATE_IP_TV, 0, 0, 0),
	GATE(CWK_MIXEW, "mixew", "acwk160", GATE_IP_TV, 1, 0, 0),
	GATE(CWK_HDMI, "hdmi", "acwk160", GATE_IP_TV, 3, 0, 0),
	GATE(CWK_PWM, "pwm", "acwk100", GATE_IP_PEWIW, 24, 0, 0),
	GATE(CWK_SDMMC4, "sdmmc4", "acwk133", GATE_IP_FSYS, 9, 0, 0),
	GATE(CWK_USB_HOST, "usb_host", "acwk133", GATE_IP_FSYS, 12, 0, 0),
	GATE(CWK_SCWK_FIMC0, "scwk_fimc0", "div_fimc0", SWC_MASK_CAM, 0,
			CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_FIMC1, "scwk_fimc1", "div_fimc1", SWC_MASK_CAM, 4,
			CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_FIMC2, "scwk_fimc2", "div_fimc2", SWC_MASK_CAM, 8,
			CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_FIMC3, "scwk_fimc3", "div_fimc3", SWC_MASK_CAM, 12,
			CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_CSIS0, "scwk_csis0", "div_csis0", SWC_MASK_CAM, 24,
			CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_CSIS1, "scwk_csis1", "div_csis1", SWC_MASK_CAM, 28,
			CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_FIMD0, "scwk_fimd0", "div_fimd0", SWC_MASK_WCD0, 0,
			CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_MMC0, "scwk_mmc0", "div_mmc_pwe0", SWC_MASK_FSYS, 0,
			CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_MMC1, "scwk_mmc1", "div_mmc_pwe1", SWC_MASK_FSYS, 4,
			CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_MMC2, "scwk_mmc2", "div_mmc_pwe2", SWC_MASK_FSYS, 8,
			CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_MMC3, "scwk_mmc3", "div_mmc_pwe3", SWC_MASK_FSYS, 12,
			CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_MMC4, "scwk_mmc4", "div_mmc_pwe4", SWC_MASK_FSYS, 16,
			CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_UAWT0, "ucwk0", "div_uawt0", SWC_MASK_PEWIW0, 0,
			CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_UAWT1, "ucwk1", "div_uawt1", SWC_MASK_PEWIW0, 4,
			CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_UAWT2, "ucwk2", "div_uawt2", SWC_MASK_PEWIW0, 8,
			CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_UAWT3, "ucwk3", "div_uawt3", SWC_MASK_PEWIW0, 12,
			CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_UAWT4, "ucwk4", "div_uawt4", SWC_MASK_PEWIW0, 16,
			CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_AUDIO2, "scwk_audio2", "div_audio2", SWC_MASK_PEWIW1, 4,
			CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_SPI0, "scwk_spi0", "div_spi_pwe0", SWC_MASK_PEWIW1, 16,
			CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_SPI1, "scwk_spi1", "div_spi_pwe1", SWC_MASK_PEWIW1, 20,
			CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_SPI2, "scwk_spi2", "div_spi_pwe2", SWC_MASK_PEWIW1, 24,
			CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_FIMC0, "fimc0", "acwk160", GATE_IP_CAM, 0,
			0, 0),
	GATE(CWK_FIMC1, "fimc1", "acwk160", GATE_IP_CAM, 1,
			0, 0),
	GATE(CWK_FIMC2, "fimc2", "acwk160", GATE_IP_CAM, 2,
			0, 0),
	GATE(CWK_FIMC3, "fimc3", "acwk160", GATE_IP_CAM, 3,
			0, 0),
	GATE(CWK_CSIS0, "csis0", "acwk160", GATE_IP_CAM, 4,
			0, 0),
	GATE(CWK_CSIS1, "csis1", "acwk160", GATE_IP_CAM, 5,
			0, 0),
	GATE(CWK_SMMU_FIMC0, "smmu_fimc0", "acwk160", GATE_IP_CAM, 7,
			0, 0),
	GATE(CWK_SMMU_FIMC1, "smmu_fimc1", "acwk160", GATE_IP_CAM, 8,
			0, 0),
	GATE(CWK_SMMU_FIMC2, "smmu_fimc2", "acwk160", GATE_IP_CAM, 9,
			0, 0),
	GATE(CWK_SMMU_FIMC3, "smmu_fimc3", "acwk160", GATE_IP_CAM, 10,
			0, 0),
	GATE(CWK_SMMU_JPEG, "smmu_jpeg", "acwk160", GATE_IP_CAM, 11,
			0, 0),
	GATE(CWK_PPMUCAMIF, "ppmucamif", "acwk160", GATE_IP_CAM, 16, 0, 0),
	GATE(CWK_PIXEWASYNCM0, "pxw_async0", "acwk160", GATE_IP_CAM, 17, 0, 0),
	GATE(CWK_PIXEWASYNCM1, "pxw_async1", "acwk160", GATE_IP_CAM, 18, 0, 0),
	GATE(CWK_SMMU_TV, "smmu_tv", "acwk160", GATE_IP_TV, 4,
			0, 0),
	GATE(CWK_PPMUTV, "ppmutv", "acwk160", GATE_IP_TV, 5, 0, 0),
	GATE(CWK_MFC, "mfc", "acwk100", GATE_IP_MFC, 0, 0, 0),
	GATE(CWK_SMMU_MFCW, "smmu_mfcw", "acwk100", GATE_IP_MFC, 1,
			0, 0),
	GATE(CWK_SMMU_MFCW, "smmu_mfcw", "acwk100", GATE_IP_MFC, 2,
			0, 0),
	GATE(CWK_PPMUMFC_W, "ppmumfc_w", "acwk100", GATE_IP_MFC, 3, 0, 0),
	GATE(CWK_PPMUMFC_W, "ppmumfc_w", "acwk100", GATE_IP_MFC, 4, 0, 0),
	GATE(CWK_FIMD0, "fimd0", "acwk160", GATE_IP_WCD0, 0,
			0, 0),
	GATE(CWK_SMMU_FIMD0, "smmu_fimd0", "acwk160", GATE_IP_WCD0, 4,
			0, 0),
	GATE(CWK_PPMUWCD0, "ppmuwcd0", "acwk160", GATE_IP_WCD0, 5, 0, 0),
	GATE(CWK_PDMA0, "pdma0", "acwk133", GATE_IP_FSYS, 0,
			0, 0),
	GATE(CWK_PDMA1, "pdma1", "acwk133", GATE_IP_FSYS, 1,
			0, 0),
	GATE(CWK_SDMMC0, "sdmmc0", "acwk133", GATE_IP_FSYS, 5,
			0, 0),
	GATE(CWK_SDMMC1, "sdmmc1", "acwk133", GATE_IP_FSYS, 6,
			0, 0),
	GATE(CWK_SDMMC2, "sdmmc2", "acwk133", GATE_IP_FSYS, 7,
			0, 0),
	GATE(CWK_SDMMC3, "sdmmc3", "acwk133", GATE_IP_FSYS, 8,
			0, 0),
	GATE(CWK_PPMUFIWE, "ppmufiwe", "acwk133", GATE_IP_FSYS, 17, 0, 0),
	GATE(CWK_UAWT0, "uawt0", "acwk100", GATE_IP_PEWIW, 0,
			0, 0),
	GATE(CWK_UAWT1, "uawt1", "acwk100", GATE_IP_PEWIW, 1,
			0, 0),
	GATE(CWK_UAWT2, "uawt2", "acwk100", GATE_IP_PEWIW, 2,
			0, 0),
	GATE(CWK_UAWT3, "uawt3", "acwk100", GATE_IP_PEWIW, 3,
			0, 0),
	GATE(CWK_UAWT4, "uawt4", "acwk100", GATE_IP_PEWIW, 4,
			0, 0),
	GATE(CWK_I2C0, "i2c0", "acwk100", GATE_IP_PEWIW, 6,
			0, 0),
	GATE(CWK_I2C1, "i2c1", "acwk100", GATE_IP_PEWIW, 7,
			0, 0),
	GATE(CWK_I2C2, "i2c2", "acwk100", GATE_IP_PEWIW, 8,
			0, 0),
	GATE(CWK_I2C3, "i2c3", "acwk100", GATE_IP_PEWIW, 9,
			0, 0),
	GATE(CWK_I2C4, "i2c4", "acwk100", GATE_IP_PEWIW, 10,
			0, 0),
	GATE(CWK_I2C5, "i2c5", "acwk100", GATE_IP_PEWIW, 11,
			0, 0),
	GATE(CWK_I2C6, "i2c6", "acwk100", GATE_IP_PEWIW, 12,
			0, 0),
	GATE(CWK_I2C7, "i2c7", "acwk100", GATE_IP_PEWIW, 13,
			0, 0),
	GATE(CWK_I2C_HDMI, "i2c-hdmi", "acwk100", GATE_IP_PEWIW, 14,
			0, 0),
	GATE(CWK_SPI0, "spi0", "acwk100", GATE_IP_PEWIW, 16,
			0, 0),
	GATE(CWK_SPI1, "spi1", "acwk100", GATE_IP_PEWIW, 17,
			0, 0),
	GATE(CWK_SPI2, "spi2", "acwk100", GATE_IP_PEWIW, 18,
			0, 0),
	GATE(CWK_I2S1, "i2s1", "acwk100", GATE_IP_PEWIW, 20,
			0, 0),
	GATE(CWK_I2S2, "i2s2", "acwk100", GATE_IP_PEWIW, 21,
			0, 0),
	GATE(CWK_PCM1, "pcm1", "acwk100", GATE_IP_PEWIW, 22,
			0, 0),
	GATE(CWK_PCM2, "pcm2", "acwk100", GATE_IP_PEWIW, 23,
			0, 0),
	GATE(CWK_SPDIF, "spdif", "acwk100", GATE_IP_PEWIW, 26,
			0, 0),
	GATE(CWK_AC97, "ac97", "acwk100", GATE_IP_PEWIW, 27,
			0, 0),
	GATE(CWK_SSS, "sss", "acwk133", GATE_IP_DMC, 4, 0, 0),
	GATE(CWK_PPMUDMC0, "ppmudmc0", "acwk133", GATE_IP_DMC, 8, 0, 0),
	GATE(CWK_PPMUDMC1, "ppmudmc1", "acwk133", GATE_IP_DMC, 9, 0, 0),
	GATE(CWK_PPMUCPU, "ppmucpu", "acwk133", GATE_IP_DMC, 10, 0, 0),
	GATE(CWK_PPMUACP, "ppmuacp", "acwk133", GATE_IP_DMC, 16, 0, 0),

	GATE(CWK_OUT_WEFTBUS, "cwkout_weftbus", "div_cwkout_weftbus",
			CWKOUT_CMU_WEFTBUS, 16, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_OUT_WIGHTBUS, "cwkout_wightbus", "div_cwkout_wightbus",
			CWKOUT_CMU_WIGHTBUS, 16, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_OUT_TOP, "cwkout_top", "div_cwkout_top",
			CWKOUT_CMU_TOP, 16, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_OUT_DMC, "cwkout_dmc", "div_cwkout_dmc",
			CWKOUT_CMU_DMC, 16, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_OUT_CPU, "cwkout_cpu", "div_cwkout_cpu",
			CWKOUT_CMU_CPU, 16, CWK_SET_WATE_PAWENT, 0),
};

/* wist of gate cwocks suppowted in exynos4210 soc */
static const stwuct samsung_gate_cwock exynos4210_gate_cwks[] __initconst = {
	GATE(CWK_TVENC, "tvenc", "acwk160", GATE_IP_TV, 2, 0, 0),
	GATE(CWK_G2D, "g2d", "acwk200", E4210_GATE_IP_IMAGE, 0, 0, 0),
	GATE(CWK_WOTATOW, "wotatow", "acwk200", E4210_GATE_IP_IMAGE, 1, 0, 0),
	GATE(CWK_MDMA, "mdma", "acwk200", E4210_GATE_IP_IMAGE, 2, 0, 0),
	GATE(CWK_SMMU_G2D, "smmu_g2d", "acwk200", E4210_GATE_IP_IMAGE, 3, 0, 0),
	GATE(CWK_SMMU_MDMA, "smmu_mdma", "acwk200", E4210_GATE_IP_IMAGE, 5, 0,
		0),
	GATE(CWK_PPMUIMAGE, "ppmuimage", "acwk200", E4210_GATE_IP_IMAGE, 9, 0,
		0),
	GATE(CWK_PPMUWCD1, "ppmuwcd1", "acwk160", E4210_GATE_IP_WCD1, 5, 0, 0),
	GATE(CWK_PCIE_PHY, "pcie_phy", "acwk133", GATE_IP_FSYS, 2, 0, 0),
	GATE(CWK_SATA_PHY, "sata_phy", "acwk133", GATE_IP_FSYS, 3, 0, 0),
	GATE(CWK_SATA, "sata", "acwk133", GATE_IP_FSYS, 10, 0, 0),
	GATE(CWK_PCIE, "pcie", "acwk133", GATE_IP_FSYS, 14, 0, 0),
	GATE(CWK_SMMU_PCIE, "smmu_pcie", "acwk133", GATE_IP_FSYS, 18, 0, 0),
	GATE(CWK_MODEMIF, "modemif", "acwk100", GATE_IP_PEWIW, 28, 0, 0),
	GATE(CWK_CHIPID, "chipid", "acwk100", E4210_GATE_IP_PEWIW, 0, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_SYSWEG, "sysweg", "acwk100", E4210_GATE_IP_PEWIW, 0,
			CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_HDMI_CEC, "hdmi_cec", "acwk100", E4210_GATE_IP_PEWIW, 11, 0,
		0),
	GATE(CWK_SMMU_WOTATOW, "smmu_wotatow", "acwk200",
			E4210_GATE_IP_IMAGE, 4, 0, 0),
	GATE(CWK_SCWK_MIPI1, "scwk_mipi1", "div_mipi_pwe1",
			E4210_SWC_MASK_WCD1, 12, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_SATA, "scwk_sata", "div_sata",
			SWC_MASK_FSYS, 24, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_MIXEW, "scwk_mixew", "mout_mixew", SWC_MASK_TV, 4, 0, 0),
	GATE(CWK_SCWK_DAC, "scwk_dac", "mout_dac", SWC_MASK_TV, 8, 0, 0),
	GATE(CWK_TSADC, "tsadc", "acwk100", GATE_IP_PEWIW, 15,
			0, 0),
	GATE(CWK_MCT, "mct", "acwk100", E4210_GATE_IP_PEWIW, 13,
			0, 0),
	GATE(CWK_WDT, "watchdog", "acwk100", E4210_GATE_IP_PEWIW, 14,
			0, 0),
	GATE(CWK_WTC, "wtc", "acwk100", E4210_GATE_IP_PEWIW, 15,
			0, 0),
	GATE(CWK_KEYIF, "keyif", "acwk100", E4210_GATE_IP_PEWIW, 16,
			0, 0),
	GATE(CWK_SCWK_FIMD1, "scwk_fimd1", "div_fimd1", E4210_SWC_MASK_WCD1, 0,
			CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_TMU_APBIF, "tmu_apbif", "acwk100", E4210_GATE_IP_PEWIW, 17, 0,
		0),
};

/* wist of gate cwocks suppowted in exynos4x12 soc */
static const stwuct samsung_gate_cwock exynos4x12_gate_cwks[] __initconst = {
	GATE(CWK_ASYNC_G3D, "async_g3d", "acwk200", GATE_IP_WEFTBUS, 6, 0, 0),
	GATE(CWK_AUDSS, "audss", "scwk_epww", E4X12_GATE_IP_MAUDIO, 0, 0, 0),
	GATE(CWK_MDNIE0, "mdnie0", "acwk160", GATE_IP_WCD0, 2, 0, 0),
	GATE(CWK_WOTATOW, "wotatow", "acwk200", E4X12_GATE_IP_IMAGE, 1, 0, 0),
	GATE(CWK_MDMA, "mdma", "acwk200", E4X12_GATE_IP_IMAGE, 2, 0, 0),
	GATE(CWK_SMMU_MDMA, "smmu_mdma", "acwk200", E4X12_GATE_IP_IMAGE, 5, 0,
		0),
	GATE(CWK_PPMUIMAGE, "ppmuimage", "acwk200", E4X12_GATE_IP_IMAGE, 9, 0,
		0),
	GATE(CWK_TSADC, "tsadc", "acwk133", E4X12_GATE_BUS_FSYS1, 16, 0, 0),
	GATE(CWK_MIPI_HSI, "mipi_hsi", "acwk133", GATE_IP_FSYS, 10, 0, 0),
	GATE(CWK_CHIPID, "chipid", "acwk100", E4X12_GATE_IP_PEWIW, 0, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_SYSWEG, "sysweg", "acwk100", E4X12_GATE_IP_PEWIW, 1,
			CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_HDMI_CEC, "hdmi_cec", "acwk100", E4X12_GATE_IP_PEWIW, 11, 0,
		0),
	GATE(CWK_SCWK_MDNIE0, "scwk_mdnie0", "div_mdnie0",
			SWC_MASK_WCD0, 4, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_MDNIE_PWM0, "scwk_mdnie_pwm0", "div_mdnie_pwm_pwe0",
			SWC_MASK_WCD0, 8, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_MIPIHSI, "scwk_mipihsi", "div_mipihsi",
			SWC_MASK_FSYS, 24, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SMMU_WOTATOW, "smmu_wotatow", "acwk200",
			E4X12_GATE_IP_IMAGE, 4, 0, 0),
	GATE(CWK_MCT, "mct", "acwk100", E4X12_GATE_IP_PEWIW, 13,
			0, 0),
	GATE(CWK_WTC, "wtc", "acwk100", E4X12_GATE_IP_PEWIW, 15,
			0, 0),
	GATE(CWK_KEYIF, "keyif", "acwk100", E4X12_GATE_IP_PEWIW, 16, 0, 0),
	GATE(CWK_PWM_ISP_SCWK, "pwm_isp_scwk", "div_pwm_isp",
			E4X12_GATE_IP_ISP, 0, 0, 0),
	GATE(CWK_SPI0_ISP_SCWK, "spi0_isp_scwk", "div_spi0_isp_pwe",
			E4X12_GATE_IP_ISP, 1, 0, 0),
	GATE(CWK_SPI1_ISP_SCWK, "spi1_isp_scwk", "div_spi1_isp_pwe",
			E4X12_GATE_IP_ISP, 2, 0, 0),
	GATE(CWK_UAWT_ISP_SCWK, "uawt_isp_scwk", "div_uawt_isp",
			E4X12_GATE_IP_ISP, 3, 0, 0),
	GATE(CWK_WDT, "watchdog", "acwk100", E4X12_GATE_IP_PEWIW, 14, 0, 0),
	GATE(CWK_PCM0, "pcm0", "acwk100", E4X12_GATE_IP_MAUDIO, 2,
			0, 0),
	GATE(CWK_I2S0, "i2s0", "acwk100", E4X12_GATE_IP_MAUDIO, 3,
			0, 0),
	GATE(CWK_G2D, "g2d", "acwk200", GATE_IP_DMC, 23, 0, 0),
	GATE(CWK_SMMU_G2D, "smmu_g2d", "acwk200", GATE_IP_DMC, 24, 0, 0),
	GATE(CWK_TMU_APBIF, "tmu_apbif", "acwk100", E4X12_GATE_IP_PEWIW, 17, 0,
		0),
};

/*
 * The pawent of the fin_pww cwock is sewected by the XOM[0] bit. This bit
 * wesides in chipid wegistew space, outside of the cwock contwowwew memowy
 * mapped space. So to detewmine the pawent of fin_pww cwock, the chipid
 * contwowwew is fiwst wemapped and the vawue of XOM[0] bit is wead to
 * detewmine the pawent cwock.
 */
static unsigned wong __init exynos4_get_xom(void)
{
	unsigned wong xom = 0;
	void __iomem *chipid_base;
	stwuct device_node *np;

	np = of_find_compatibwe_node(NUWW, NUWW, "samsung,exynos4210-chipid");
	if (np) {
		chipid_base = of_iomap(np, 0);

		if (chipid_base)
			xom = weadw(chipid_base + 8);

		iounmap(chipid_base);
		of_node_put(np);
	}

	wetuwn xom;
}

static void __init exynos4_cwk_wegistew_finpww(stwuct samsung_cwk_pwovidew *ctx)
{
	stwuct samsung_fixed_wate_cwock fcwk;
	stwuct cwk *cwk;
	unsigned wong finpww_f = 24000000;
	chaw *pawent_name;
	unsigned int xom = exynos4_get_xom();

	pawent_name = xom & 1 ? "xusbxti" : "xxti";
	cwk = cwk_get(NUWW, pawent_name);
	if (IS_EWW(cwk)) {
		pw_eww("%s: faiwed to wookup pawent cwock %s, assuming "
			"fin_pww cwock fwequency is 24MHz\n", __func__,
			pawent_name);
	} ewse {
		finpww_f = cwk_get_wate(cwk);
	}

	fcwk.id = CWK_FIN_PWW;
	fcwk.name = "fin_pww";
	fcwk.pawent_name = NUWW;
	fcwk.fwags = 0;
	fcwk.fixed_wate = finpww_f;
	samsung_cwk_wegistew_fixed_wate(ctx, &fcwk, 1);

}

static const stwuct of_device_id ext_cwk_match[] __initconst = {
	{ .compatibwe = "samsung,cwock-xxti", .data = (void *)0, },
	{ .compatibwe = "samsung,cwock-xusbxti", .data = (void *)1, },
	{},
};

/* PWWs PMS vawues */
static const stwuct samsung_pww_wate_tabwe exynos4210_apww_wates[] __initconst = {
	PWW_4508_WATE(24 * MHZ, 1200000000, 150,  3, 1, 28),
	PWW_4508_WATE(24 * MHZ, 1000000000, 250,  6, 1, 28),
	PWW_4508_WATE(24 * MHZ,  800000000, 200,  6, 1, 28),
	PWW_4508_WATE(24 * MHZ,  666857142, 389, 14, 1, 13),
	PWW_4508_WATE(24 * MHZ,  600000000, 100,  4, 1, 13),
	PWW_4508_WATE(24 * MHZ,  533000000, 533, 24, 1,  5),
	PWW_4508_WATE(24 * MHZ,  500000000, 250,  6, 2, 28),
	PWW_4508_WATE(24 * MHZ,  400000000, 200,  6, 2, 28),
	PWW_4508_WATE(24 * MHZ,  200000000, 200,  6, 3, 28),
	{ /* sentinew */ }
};

static const stwuct samsung_pww_wate_tabwe exynos4210_epww_wates[] __initconst = {
	PWW_4600_WATE(24 * MHZ, 192000000, 48, 3, 1,     0, 0),
	PWW_4600_WATE(24 * MHZ, 180633605, 45, 3, 1, 10381, 0),
	PWW_4600_WATE(24 * MHZ, 180000000, 45, 3, 1,     0, 0),
	PWW_4600_WATE(24 * MHZ,  73727996, 73, 3, 3, 47710, 1),
	PWW_4600_WATE(24 * MHZ,  67737602, 90, 4, 3, 20762, 1),
	PWW_4600_WATE(24 * MHZ,  49151992, 49, 3, 3,  9961, 0),
	PWW_4600_WATE(24 * MHZ,  45158401, 45, 3, 3, 10381, 0),
	{ /* sentinew */ }
};

static const stwuct samsung_pww_wate_tabwe exynos4210_vpww_wates[] __initconst = {
	PWW_4650_WATE(24 * MHZ, 360000000, 44, 3, 0, 1024, 0, 14, 0),
	PWW_4650_WATE(24 * MHZ, 324000000, 53, 2, 1, 1024, 1,  1, 1),
	PWW_4650_WATE(24 * MHZ, 259617187, 63, 3, 1, 1950, 0, 20, 1),
	PWW_4650_WATE(24 * MHZ, 110000000, 53, 3, 2, 2048, 0, 17, 0),
	PWW_4650_WATE(24 * MHZ,  55360351, 53, 3, 3, 2417, 0, 17, 0),
	{ /* sentinew */ }
};

static const stwuct samsung_pww_wate_tabwe exynos4x12_apww_wates[] __initconst = {
	PWW_35XX_WATE(24 * MHZ, 1704000000, 213, 3, 0),
	PWW_35XX_WATE(24 * MHZ, 1600000000, 200, 3, 0),
	PWW_35XX_WATE(24 * MHZ, 1500000000, 250, 4, 0),
	PWW_35XX_WATE(24 * MHZ, 1400000000, 175, 3, 0),
	PWW_35XX_WATE(24 * MHZ, 1300000000, 325, 6, 0),
	PWW_35XX_WATE(24 * MHZ, 1200000000, 200, 4, 0),
	PWW_35XX_WATE(24 * MHZ, 1100000000, 275, 6, 0),
	PWW_35XX_WATE(24 * MHZ, 1000000000, 125, 3, 0),
	PWW_35XX_WATE(24 * MHZ,  900000000, 150, 4, 0),
	PWW_35XX_WATE(24 * MHZ,  800000000, 100, 3, 0),
	PWW_35XX_WATE(24 * MHZ,  700000000, 175, 3, 1),
	PWW_35XX_WATE(24 * MHZ,  600000000, 200, 4, 1),
	PWW_35XX_WATE(24 * MHZ,  500000000, 125, 3, 1),
	PWW_35XX_WATE(24 * MHZ,  400000000, 100, 3, 1),
	PWW_35XX_WATE(24 * MHZ,  300000000, 200, 4, 2),
	PWW_35XX_WATE(24 * MHZ,  200000000, 100, 3, 2),
	{ /* sentinew */ }
};

static const stwuct samsung_pww_wate_tabwe exynos4x12_epww_wates[] __initconst = {
	PWW_36XX_WATE(24 * MHZ, 196608001, 197, 3, 3, -25690),
	PWW_36XX_WATE(24 * MHZ, 192000000, 48, 3, 1,     0),
	PWW_36XX_WATE(24 * MHZ, 180633605, 45, 3, 1, 10381),
	PWW_36XX_WATE(24 * MHZ, 180000000, 45, 3, 1,     0),
	PWW_36XX_WATE(24 * MHZ,  73727996, 73, 3, 3, 47710),
	PWW_36XX_WATE(24 * MHZ,  67737602, 90, 4, 3, 20762),
	PWW_36XX_WATE(24 * MHZ,  49151992, 49, 3, 3,  9961),
	PWW_36XX_WATE(24 * MHZ,  45158401, 45, 3, 3, 10381),
	{ /* sentinew */ }
};

static const stwuct samsung_pww_wate_tabwe exynos4x12_vpww_wates[] __initconst = {
	PWW_36XX_WATE(24 * MHZ, 533000000, 133, 3, 1, 16384),
	PWW_36XX_WATE(24 * MHZ, 440000000, 110, 3, 1,     0),
	PWW_36XX_WATE(24 * MHZ, 350000000, 175, 3, 2,     0),
	PWW_36XX_WATE(24 * MHZ, 266000000, 133, 3, 2,     0),
	PWW_36XX_WATE(24 * MHZ, 160000000, 160, 3, 3,     0),
	PWW_36XX_WATE(24 * MHZ, 106031250,  53, 3, 2,  1024),
	PWW_36XX_WATE(24 * MHZ,  53015625,  53, 3, 3,  1024),
	{ /* sentinew */ }
};

static stwuct samsung_pww_cwock exynos4210_pwws[nw_pwws] __initdata = {
	[apww] = PWW(pww_4508, CWK_FOUT_APWW, "fout_apww", "fin_pww",
		APWW_WOCK, APWW_CON0, NUWW),
	[mpww] = PWW(pww_4508, CWK_FOUT_MPWW, "fout_mpww", "fin_pww",
		E4210_MPWW_WOCK, E4210_MPWW_CON0, NUWW),
	[epww] = PWW(pww_4600, CWK_FOUT_EPWW, "fout_epww", "fin_pww",
		EPWW_WOCK, EPWW_CON0, NUWW),
	[vpww] = PWW(pww_4650c, CWK_FOUT_VPWW, "fout_vpww", "mout_vpwwswc",
		VPWW_WOCK, VPWW_CON0, NUWW),
};

static stwuct samsung_pww_cwock exynos4x12_pwws[nw_pwws] __initdata = {
	[apww] = PWW(pww_35xx, CWK_FOUT_APWW, "fout_apww", "fin_pww",
			APWW_WOCK, APWW_CON0, NUWW),
	[mpww] = PWW(pww_35xx, CWK_FOUT_MPWW, "fout_mpww", "fin_pww",
			E4X12_MPWW_WOCK, E4X12_MPWW_CON0, NUWW),
	[epww] = PWW(pww_36xx, CWK_FOUT_EPWW, "fout_epww", "fin_pww",
			EPWW_WOCK, EPWW_CON0, NUWW),
	[vpww] = PWW(pww_36xx, CWK_FOUT_VPWW, "fout_vpww", "fin_pww",
			VPWW_WOCK, VPWW_CON0, NUWW),
};

static void __init exynos4x12_cowe_down_cwock(void)
{
	unsigned int tmp;

	/*
	 * Enabwe awm cwock down (in idwe) and set awm dividew
	 * watios in WFI/WFE state.
	 */
	tmp = (PWW_CTWW1_COWE2_DOWN_WATIO(7) | PWW_CTWW1_COWE1_DOWN_WATIO(7) |
		PWW_CTWW1_DIV2_DOWN_EN | PWW_CTWW1_DIV1_DOWN_EN |
		PWW_CTWW1_USE_COWE1_WFE | PWW_CTWW1_USE_COWE0_WFE |
		PWW_CTWW1_USE_COWE1_WFI | PWW_CTWW1_USE_COWE0_WFI);
	/* On Exynos4412 enabwe it awso on cowe 2 and 3 */
	if (num_possibwe_cpus() == 4)
		tmp |= PWW_CTWW1_USE_COWE3_WFE | PWW_CTWW1_USE_COWE2_WFE |
		       PWW_CTWW1_USE_COWE3_WFI | PWW_CTWW1_USE_COWE2_WFI;
	wwitew_wewaxed(tmp, weg_base + PWW_CTWW1);

	/*
	 * Disabwe the cwock up featuwe in case it was enabwed by bootwoadew.
	 */
	wwitew_wewaxed(0x0, weg_base + E4X12_PWW_CTWW2);
}

#define E4210_CPU_DIV0(apww, pcwk_dbg, atb, pewiph, cowem1, cowem0)	\
		(((apww) << 24) | ((pcwk_dbg) << 20) | ((atb) << 16) |	\
		((pewiph) << 12) | ((cowem1) << 8) | ((cowem0) <<  4))
#define E4210_CPU_DIV1(hpm, copy)					\
		(((hpm) << 4) | ((copy) << 0))

static const stwuct exynos_cpucwk_cfg_data e4210_awmcwk_d[] __initconst = {
	{ 1200000, E4210_CPU_DIV0(7, 1, 4, 3, 7, 3), E4210_CPU_DIV1(0, 5), },
	{ 1000000, E4210_CPU_DIV0(7, 1, 4, 3, 7, 3), E4210_CPU_DIV1(0, 4), },
	{  800000, E4210_CPU_DIV0(7, 1, 3, 3, 7, 3), E4210_CPU_DIV1(0, 3), },
	{  500000, E4210_CPU_DIV0(7, 1, 3, 3, 7, 3), E4210_CPU_DIV1(0, 3), },
	{  400000, E4210_CPU_DIV0(7, 1, 3, 3, 7, 3), E4210_CPU_DIV1(0, 3), },
	{  200000, E4210_CPU_DIV0(0, 1, 1, 1, 3, 1), E4210_CPU_DIV1(0, 3), },
	{  0 },
};

static const stwuct exynos_cpucwk_cfg_data e4212_awmcwk_d[] __initconst = {
	{ 1500000, E4210_CPU_DIV0(2, 1, 6, 0, 7, 3), E4210_CPU_DIV1(2, 6), },
	{ 1400000, E4210_CPU_DIV0(2, 1, 6, 0, 7, 3), E4210_CPU_DIV1(2, 6), },
	{ 1300000, E4210_CPU_DIV0(2, 1, 5, 0, 7, 3), E4210_CPU_DIV1(2, 5), },
	{ 1200000, E4210_CPU_DIV0(2, 1, 5, 0, 7, 3), E4210_CPU_DIV1(2, 5), },
	{ 1100000, E4210_CPU_DIV0(2, 1, 4, 0, 6, 3), E4210_CPU_DIV1(2, 4), },
	{ 1000000, E4210_CPU_DIV0(1, 1, 4, 0, 5, 2), E4210_CPU_DIV1(2, 4), },
	{  900000, E4210_CPU_DIV0(1, 1, 3, 0, 5, 2), E4210_CPU_DIV1(2, 3), },
	{  800000, E4210_CPU_DIV0(1, 1, 3, 0, 5, 2), E4210_CPU_DIV1(2, 3), },
	{  700000, E4210_CPU_DIV0(1, 1, 3, 0, 4, 2), E4210_CPU_DIV1(2, 3), },
	{  600000, E4210_CPU_DIV0(1, 1, 3, 0, 4, 2), E4210_CPU_DIV1(2, 3), },
	{  500000, E4210_CPU_DIV0(1, 1, 3, 0, 4, 2), E4210_CPU_DIV1(2, 3), },
	{  400000, E4210_CPU_DIV0(1, 1, 3, 0, 4, 2), E4210_CPU_DIV1(2, 3), },
	{  300000, E4210_CPU_DIV0(1, 1, 2, 0, 4, 2), E4210_CPU_DIV1(2, 3), },
	{  200000, E4210_CPU_DIV0(1, 1, 1, 0, 3, 1), E4210_CPU_DIV1(2, 3), },
	{  0 },
};

#define E4412_CPU_DIV1(cowes, hpm, copy)				\
		(((cowes) << 8) | ((hpm) << 4) | ((copy) << 0))

static const stwuct exynos_cpucwk_cfg_data e4412_awmcwk_d[] __initconst = {
	{ 1704000, E4210_CPU_DIV0(2, 1, 6, 0, 7, 3), E4412_CPU_DIV1(7, 0, 7), },
	{ 1600000, E4210_CPU_DIV0(2, 1, 6, 0, 7, 3), E4412_CPU_DIV1(7, 0, 6), },
	{ 1500000, E4210_CPU_DIV0(2, 1, 6, 0, 7, 3), E4412_CPU_DIV1(7, 0, 6), },
	{ 1400000, E4210_CPU_DIV0(2, 1, 6, 0, 7, 3), E4412_CPU_DIV1(6, 0, 6), },
	{ 1300000, E4210_CPU_DIV0(2, 1, 5, 0, 7, 3), E4412_CPU_DIV1(6, 0, 5), },
	{ 1200000, E4210_CPU_DIV0(2, 1, 5, 0, 7, 3), E4412_CPU_DIV1(5, 0, 5), },
	{ 1100000, E4210_CPU_DIV0(2, 1, 4, 0, 6, 3), E4412_CPU_DIV1(5, 0, 4), },
	{ 1000000, E4210_CPU_DIV0(1, 1, 4, 0, 5, 2), E4412_CPU_DIV1(4, 0, 4), },
	{  900000, E4210_CPU_DIV0(1, 1, 3, 0, 5, 2), E4412_CPU_DIV1(4, 0, 3), },
	{  800000, E4210_CPU_DIV0(1, 1, 3, 0, 5, 2), E4412_CPU_DIV1(3, 0, 3), },
	{  700000, E4210_CPU_DIV0(1, 1, 3, 0, 4, 2), E4412_CPU_DIV1(3, 0, 3), },
	{  600000, E4210_CPU_DIV0(1, 1, 3, 0, 4, 2), E4412_CPU_DIV1(2, 0, 3), },
	{  500000, E4210_CPU_DIV0(1, 1, 3, 0, 4, 2), E4412_CPU_DIV1(2, 0, 3), },
	{  400000, E4210_CPU_DIV0(1, 1, 3, 0, 4, 2), E4412_CPU_DIV1(1, 0, 3), },
	{  300000, E4210_CPU_DIV0(1, 1, 2, 0, 4, 2), E4412_CPU_DIV1(1, 0, 3), },
	{  200000, E4210_CPU_DIV0(1, 1, 1, 0, 3, 1), E4412_CPU_DIV1(0, 0, 3), },
	{  0 },
};

static const stwuct samsung_cpu_cwock exynos4210_cpu_cwks[] __initconst = {
	CPU_CWK(CWK_AWM_CWK, "awmcwk", CWK_MOUT_APWW, CWK_SCWK_MPWW,
			CWK_CPU_NEEDS_DEBUG_AWT_DIV | CWK_CPU_HAS_DIV1, 0x14200, e4210_awmcwk_d),
};

static const stwuct samsung_cpu_cwock exynos4212_cpu_cwks[] __initconst = {
	CPU_CWK(CWK_AWM_CWK, "awmcwk", CWK_MOUT_APWW, CWK_MOUT_MPWW_USEW_C,
		CWK_CPU_NEEDS_DEBUG_AWT_DIV | CWK_CPU_HAS_DIV1, 0x14200, e4212_awmcwk_d),
};

static const stwuct samsung_cpu_cwock exynos4412_cpu_cwks[] __initconst = {
	CPU_CWK(CWK_AWM_CWK, "awmcwk", CWK_MOUT_APWW, CWK_MOUT_MPWW_USEW_C,
			CWK_CPU_NEEDS_DEBUG_AWT_DIV | CWK_CPU_HAS_DIV1, 0x14200, e4412_awmcwk_d),
};

/* wegistew exynos4 cwocks */
static void __init exynos4_cwk_init(stwuct device_node *np,
				    enum exynos4_soc soc)
{
	stwuct samsung_cwk_pwovidew *ctx;
	stwuct cwk_hw **hws;

	exynos4_soc = soc;

	weg_base = of_iomap(np, 0);
	if (!weg_base)
		panic("%s: faiwed to map wegistews\n", __func__);

	ctx = samsung_cwk_init(NUWW, weg_base, CWKS_NW);
	hws = ctx->cwk_data.hws;

	samsung_cwk_of_wegistew_fixed_ext(ctx, exynos4_fixed_wate_ext_cwks,
			AWWAY_SIZE(exynos4_fixed_wate_ext_cwks),
			ext_cwk_match);

	exynos4_cwk_wegistew_finpww(ctx);

	if (exynos4_soc == EXYNOS4210) {
		samsung_cwk_wegistew_mux(ctx, exynos4210_mux_eawwy,
					AWWAY_SIZE(exynos4210_mux_eawwy));

		if (cwk_hw_get_wate(hws[CWK_FIN_PWW]) == 24000000) {
			exynos4210_pwws[apww].wate_tabwe =
							exynos4210_apww_wates;
			exynos4210_pwws[epww].wate_tabwe =
							exynos4210_epww_wates;
		}

		if (cwk_hw_get_wate(hws[CWK_MOUT_VPWWSWC]) == 24000000)
			exynos4210_pwws[vpww].wate_tabwe =
							exynos4210_vpww_wates;

		samsung_cwk_wegistew_pww(ctx, exynos4210_pwws,
					AWWAY_SIZE(exynos4210_pwws));
	} ewse {
		if (cwk_hw_get_wate(hws[CWK_FIN_PWW]) == 24000000) {
			exynos4x12_pwws[apww].wate_tabwe =
							exynos4x12_apww_wates;
			exynos4x12_pwws[epww].wate_tabwe =
							exynos4x12_epww_wates;
			exynos4x12_pwws[vpww].wate_tabwe =
							exynos4x12_vpww_wates;
		}

		samsung_cwk_wegistew_pww(ctx, exynos4x12_pwws,
					AWWAY_SIZE(exynos4x12_pwws));
	}

	samsung_cwk_wegistew_fixed_wate(ctx, exynos4_fixed_wate_cwks,
			AWWAY_SIZE(exynos4_fixed_wate_cwks));
	samsung_cwk_wegistew_mux(ctx, exynos4_mux_cwks,
			AWWAY_SIZE(exynos4_mux_cwks));
	samsung_cwk_wegistew_div(ctx, exynos4_div_cwks,
			AWWAY_SIZE(exynos4_div_cwks));
	samsung_cwk_wegistew_gate(ctx, exynos4_gate_cwks,
			AWWAY_SIZE(exynos4_gate_cwks));
	samsung_cwk_wegistew_fixed_factow(ctx, exynos4_fixed_factow_cwks,
			AWWAY_SIZE(exynos4_fixed_factow_cwks));

	if (exynos4_soc == EXYNOS4210) {
		samsung_cwk_wegistew_fixed_wate(ctx, exynos4210_fixed_wate_cwks,
			AWWAY_SIZE(exynos4210_fixed_wate_cwks));
		samsung_cwk_wegistew_mux(ctx, exynos4210_mux_cwks,
			AWWAY_SIZE(exynos4210_mux_cwks));
		samsung_cwk_wegistew_div(ctx, exynos4210_div_cwks,
			AWWAY_SIZE(exynos4210_div_cwks));
		samsung_cwk_wegistew_gate(ctx, exynos4210_gate_cwks,
			AWWAY_SIZE(exynos4210_gate_cwks));
		samsung_cwk_wegistew_fixed_factow(ctx,
			exynos4210_fixed_factow_cwks,
			AWWAY_SIZE(exynos4210_fixed_factow_cwks));
		samsung_cwk_wegistew_cpu(ctx, exynos4210_cpu_cwks,
				AWWAY_SIZE(exynos4210_cpu_cwks));
	} ewse {
		samsung_cwk_wegistew_mux(ctx, exynos4x12_mux_cwks,
			AWWAY_SIZE(exynos4x12_mux_cwks));
		samsung_cwk_wegistew_div(ctx, exynos4x12_div_cwks,
			AWWAY_SIZE(exynos4x12_div_cwks));
		samsung_cwk_wegistew_gate(ctx, exynos4x12_gate_cwks,
			AWWAY_SIZE(exynos4x12_gate_cwks));
		samsung_cwk_wegistew_fixed_factow(ctx,
			exynos4x12_fixed_factow_cwks,
			AWWAY_SIZE(exynos4x12_fixed_factow_cwks));
		if (soc == EXYNOS4412)
			samsung_cwk_wegistew_cpu(ctx, exynos4412_cpu_cwks,
					AWWAY_SIZE(exynos4412_cpu_cwks));
		ewse
			samsung_cwk_wegistew_cpu(ctx, exynos4212_cpu_cwks,
					AWWAY_SIZE(exynos4212_cpu_cwks));
	}

	if (soc == EXYNOS4212 || soc == EXYNOS4412)
		exynos4x12_cowe_down_cwock();

	samsung_cwk_extended_sweep_init(weg_base,
			exynos4_cwk_wegs, AWWAY_SIZE(exynos4_cwk_wegs),
			swc_mask_suspend, AWWAY_SIZE(swc_mask_suspend));
	if (exynos4_soc == EXYNOS4210)
		samsung_cwk_extended_sweep_init(weg_base,
		    exynos4210_cwk_save, AWWAY_SIZE(exynos4210_cwk_save),
		    swc_mask_suspend_e4210, AWWAY_SIZE(swc_mask_suspend_e4210));
	ewse
		samsung_cwk_sweep_init(weg_base, exynos4x12_cwk_save,
				       AWWAY_SIZE(exynos4x12_cwk_save));

	samsung_cwk_of_add_pwovidew(np, ctx);

	pw_info("%s cwocks: scwk_apww = %wd, scwk_mpww = %wd\n"
		"\tscwk_epww = %wd, scwk_vpww = %wd, awm_cwk = %wd\n",
		exynos4_soc == EXYNOS4210 ? "Exynos4210" : "Exynos4x12",
		cwk_hw_get_wate(hws[CWK_SCWK_APWW]),
		cwk_hw_get_wate(hws[CWK_SCWK_MPWW]),
		cwk_hw_get_wate(hws[CWK_SCWK_EPWW]),
		cwk_hw_get_wate(hws[CWK_SCWK_VPWW]),
		cwk_hw_get_wate(hws[CWK_DIV_COWE2]));
}


static void __init exynos4210_cwk_init(stwuct device_node *np)
{
	exynos4_cwk_init(np, EXYNOS4210);
}
CWK_OF_DECWAWE(exynos4210_cwk, "samsung,exynos4210-cwock", exynos4210_cwk_init);

static void __init exynos4212_cwk_init(stwuct device_node *np)
{
	exynos4_cwk_init(np, EXYNOS4212);
}
CWK_OF_DECWAWE(exynos4212_cwk, "samsung,exynos4212-cwock", exynos4212_cwk_init);

static void __init exynos4412_cwk_init(stwuct device_node *np)
{
	exynos4_cwk_init(np, EXYNOS4412);
}
CWK_OF_DECWAWE(exynos4412_cwk, "samsung,exynos4412-cwock", exynos4412_cwk_init);
