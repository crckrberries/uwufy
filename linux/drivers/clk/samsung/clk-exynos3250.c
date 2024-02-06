// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014 Samsung Ewectwonics Co., Wtd.
 *
 * Common Cwock Fwamewowk suppowt fow Exynos3250 SoC.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>

#incwude <dt-bindings/cwock/exynos3250.h>

#incwude "cwk.h"
#incwude "cwk-cpu.h"
#incwude "cwk-pww.h"

#define SWC_WEFTBUS		0x4200
#define DIV_WEFTBUS		0x4500
#define GATE_IP_WEFTBUS		0x4800
#define SWC_WIGHTBUS		0x8200
#define DIV_WIGHTBUS		0x8500
#define GATE_IP_WIGHTBUS	0x8800
#define GATE_IP_PEWIW		0x8960
#define MPWW_WOCK		0xc010
#define MPWW_CON0		0xc110
#define VPWW_WOCK		0xc020
#define VPWW_CON0		0xc120
#define UPWW_WOCK		0xc030
#define UPWW_CON0		0xc130
#define SWC_TOP0		0xc210
#define SWC_TOP1		0xc214
#define SWC_CAM			0xc220
#define SWC_MFC			0xc228
#define SWC_G3D			0xc22c
#define SWC_WCD			0xc234
#define SWC_ISP			0xc238
#define SWC_FSYS		0xc240
#define SWC_PEWIW0		0xc250
#define SWC_PEWIW1		0xc254
#define SWC_MASK_TOP		0xc310
#define SWC_MASK_CAM		0xc320
#define SWC_MASK_WCD		0xc334
#define SWC_MASK_ISP		0xc338
#define SWC_MASK_FSYS		0xc340
#define SWC_MASK_PEWIW0		0xc350
#define SWC_MASK_PEWIW1		0xc354
#define DIV_TOP			0xc510
#define DIV_CAM			0xc520
#define DIV_MFC			0xc528
#define DIV_G3D			0xc52c
#define DIV_WCD			0xc534
#define DIV_ISP			0xc538
#define DIV_FSYS0		0xc540
#define DIV_FSYS1		0xc544
#define DIV_FSYS2		0xc548
#define DIV_PEWIW0		0xc550
#define DIV_PEWIW1		0xc554
#define DIV_PEWIW3		0xc55c
#define DIV_PEWIW4		0xc560
#define DIV_PEWIW5		0xc564
#define DIV_CAM1		0xc568
#define CWKDIV2_WATIO		0xc580
#define GATE_SCWK_CAM		0xc820
#define GATE_SCWK_MFC		0xc828
#define GATE_SCWK_G3D		0xc82c
#define GATE_SCWK_WCD		0xc834
#define GATE_SCWK_ISP_TOP	0xc838
#define GATE_SCWK_FSYS		0xc840
#define GATE_SCWK_PEWIW		0xc850
#define GATE_IP_CAM		0xc920
#define GATE_IP_MFC		0xc928
#define GATE_IP_G3D		0xc92c
#define GATE_IP_WCD		0xc934
#define GATE_IP_ISP		0xc938
#define GATE_IP_FSYS		0xc940
#define GATE_IP_PEWIW		0xc950
#define GATE_BWOCK		0xc970
#define APWW_WOCK		0x14000
#define APWW_CON0		0x14100
#define SWC_CPU			0x14200
#define DIV_CPU0		0x14500
#define DIV_CPU1		0x14504
#define PWW_CTWW1		0x15020
#define PWW_CTWW2		0x15024

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
#define CWKS_NW_MAIN				(CWK_SCWK_MMC2 + 1)
#define CWKS_NW_DMC				(CWK_DIV_DMCD + 1)
#define CWKS_NW_ISP				(CWK_SCWK_MPWM_ISP + 1)

static const unsigned wong exynos3250_cmu_cwk_wegs[] __initconst = {
	SWC_WEFTBUS,
	DIV_WEFTBUS,
	GATE_IP_WEFTBUS,
	SWC_WIGHTBUS,
	DIV_WIGHTBUS,
	GATE_IP_WIGHTBUS,
	GATE_IP_PEWIW,
	MPWW_WOCK,
	MPWW_CON0,
	VPWW_WOCK,
	VPWW_CON0,
	UPWW_WOCK,
	UPWW_CON0,
	SWC_TOP0,
	SWC_TOP1,
	SWC_CAM,
	SWC_MFC,
	SWC_G3D,
	SWC_WCD,
	SWC_ISP,
	SWC_FSYS,
	SWC_PEWIW0,
	SWC_PEWIW1,
	SWC_MASK_TOP,
	SWC_MASK_CAM,
	SWC_MASK_WCD,
	SWC_MASK_ISP,
	SWC_MASK_FSYS,
	SWC_MASK_PEWIW0,
	SWC_MASK_PEWIW1,
	DIV_TOP,
	DIV_CAM,
	DIV_MFC,
	DIV_G3D,
	DIV_WCD,
	DIV_ISP,
	DIV_FSYS0,
	DIV_FSYS1,
	DIV_FSYS2,
	DIV_PEWIW0,
	DIV_PEWIW1,
	DIV_PEWIW3,
	DIV_PEWIW4,
	DIV_PEWIW5,
	DIV_CAM1,
	CWKDIV2_WATIO,
	GATE_SCWK_CAM,
	GATE_SCWK_MFC,
	GATE_SCWK_G3D,
	GATE_SCWK_WCD,
	GATE_SCWK_ISP_TOP,
	GATE_SCWK_FSYS,
	GATE_SCWK_PEWIW,
	GATE_IP_CAM,
	GATE_IP_MFC,
	GATE_IP_G3D,
	GATE_IP_WCD,
	GATE_IP_ISP,
	GATE_IP_FSYS,
	GATE_IP_PEWIW,
	GATE_BWOCK,
	APWW_WOCK,
	SWC_CPU,
	DIV_CPU0,
	DIV_CPU1,
	PWW_CTWW1,
	PWW_CTWW2,
};

/* wist of aww pawent cwock wist */
PNAME(mout_vpwwswc_p)		= { "fin_pww", };

PNAME(mout_apww_p)		= { "fin_pww", "fout_apww", };
PNAME(mout_mpww_p)		= { "fin_pww", "fout_mpww", };
PNAME(mout_vpww_p)		= { "fin_pww", "fout_vpww", };
PNAME(mout_upww_p)		= { "fin_pww", "fout_upww", };

PNAME(mout_mpww_usew_p)		= { "fin_pww", "div_mpww_pwe", };
PNAME(mout_epww_usew_p)		= { "fin_pww", "mout_epww", };
PNAME(mout_cowe_p)		= { "mout_apww", "mout_mpww_usew_c", };
PNAME(mout_hpm_p)		= { "mout_apww", "mout_mpww_usew_c", };

PNAME(mout_ebi_p)		= { "div_acwk_200", "div_acwk_160", };
PNAME(mout_ebi_1_p)		= { "mout_ebi", "mout_vpww", };

PNAME(mout_gdw_p)		= { "mout_mpww_usew_w", };
PNAME(mout_gdw_p)		= { "mout_mpww_usew_w", };

PNAME(mout_acwk_400_mcuisp_sub_p)
				= { "fin_pww", "div_acwk_400_mcuisp", };
PNAME(mout_acwk_266_0_p)	= { "div_mpww_pwe", "mout_vpww", };
PNAME(mout_acwk_266_1_p)	= { "mout_epww_usew", };
PNAME(mout_acwk_266_p)		= { "mout_acwk_266_0", "mout_acwk_266_1", };
PNAME(mout_acwk_266_sub_p)	= { "fin_pww", "div_acwk_266", };

PNAME(gwoup_div_mpww_pwe_p)	= { "div_mpww_pwe", };
PNAME(gwoup_epww_vpww_p)	= { "mout_epww_usew", "mout_vpww" };
PNAME(gwoup_scwk_p)		= { "xxti", "xusbxti",
				    "none", "none",
				    "none", "none", "div_mpww_pwe",
				    "mout_epww_usew", "mout_vpww", };
PNAME(gwoup_scwk_audio_p)	= { "audiocdcwk", "none",
				    "none", "none",
				    "xxti", "xusbxti",
				    "div_mpww_pwe", "mout_epww_usew",
				    "mout_vpww", };
PNAME(gwoup_scwk_cam_bwk_p)	= { "xxti", "xusbxti",
				    "none", "none", "none",
				    "none", "div_mpww_pwe",
				    "mout_epww_usew", "mout_vpww",
				    "none", "none", "none",
				    "div_cam_bwk_320", };
PNAME(gwoup_scwk_fimd0_p)	= { "xxti", "xusbxti",
				    "m_bitcwkhsdiv4_2w", "none",
				    "none", "none", "div_mpww_pwe",
				    "mout_epww_usew", "mout_vpww",
				    "none", "none", "none",
				    "div_wcd_bwk_145", };

PNAME(mout_mfc_p)		= { "mout_mfc_0", "mout_mfc_1" };
PNAME(mout_g3d_p)		= { "mout_g3d_0", "mout_g3d_1" };

static const stwuct samsung_fixed_factow_cwock fixed_factow_cwks[] __initconst = {
	FFACTOW(0, "scwk_mpww_1600", "mout_mpww", 1, 1, 0),
	FFACTOW(0, "scwk_mpww_mif", "mout_mpww", 1, 2, 0),
	FFACTOW(0, "scwk_bpww", "fout_bpww", 1, 2, 0),
	FFACTOW(0, "div_cam_bwk_320", "scwk_mpww_1600", 1, 5, 0),
	FFACTOW(0, "div_wcd_bwk_145", "scwk_mpww_1600", 1, 11, 0),

	/* HACK: fin_pww hawdcoded to xusbxti untiw detection is impwemented. */
	FFACTOW(CWK_FIN_PWW, "fin_pww", "xusbxti", 1, 1, 0),
};

static const stwuct samsung_mux_cwock mux_cwks[] __initconst = {
	/*
	 * NOTE: Fowwowing tabwe is sowted by wegistew addwess in ascending
	 * owdew and then bitfiewd shift in descending owdew, as it is done
	 * in the Usew's Manuaw. When adding new entwies, pwease make suwe
	 * that the owdew is pwesewved, to avoid mewge confwicts and make
	 * fuwthew wowk with defined data easiew.
	 */

	/* SWC_WEFTBUS */
	MUX(CWK_MOUT_MPWW_USEW_W, "mout_mpww_usew_w", mout_mpww_usew_p,
	    SWC_WEFTBUS, 4, 1),
	MUX(CWK_MOUT_GDW, "mout_gdw", mout_gdw_p, SWC_WEFTBUS, 0, 1),

	/* SWC_WIGHTBUS */
	MUX(CWK_MOUT_MPWW_USEW_W, "mout_mpww_usew_w", mout_mpww_usew_p,
	    SWC_WIGHTBUS, 4, 1),
	MUX(CWK_MOUT_GDW, "mout_gdw", mout_gdw_p, SWC_WIGHTBUS, 0, 1),

	/* SWC_TOP0 */
	MUX(CWK_MOUT_EBI, "mout_ebi", mout_ebi_p, SWC_TOP0, 28, 1),
	MUX(CWK_MOUT_ACWK_200, "mout_acwk_200", gwoup_div_mpww_pwe_p,SWC_TOP0, 24, 1),
	MUX(CWK_MOUT_ACWK_160, "mout_acwk_160", gwoup_div_mpww_pwe_p, SWC_TOP0, 20, 1),
	MUX(CWK_MOUT_ACWK_100, "mout_acwk_100", gwoup_div_mpww_pwe_p, SWC_TOP0, 16, 1),
	MUX(CWK_MOUT_ACWK_266_1, "mout_acwk_266_1", mout_acwk_266_1_p, SWC_TOP0, 14, 1),
	MUX(CWK_MOUT_ACWK_266_0, "mout_acwk_266_0", mout_acwk_266_0_p, SWC_TOP0, 13, 1),
	MUX(CWK_MOUT_ACWK_266, "mout_acwk_266", mout_acwk_266_p, SWC_TOP0, 12, 1),
	MUX(CWK_MOUT_VPWW, "mout_vpww", mout_vpww_p, SWC_TOP0, 8, 1),
	MUX(CWK_MOUT_EPWW_USEW, "mout_epww_usew", mout_epww_usew_p, SWC_TOP0, 4, 1),
	MUX(CWK_MOUT_EBI_1, "mout_ebi_1", mout_ebi_1_p, SWC_TOP0, 0, 1),

	/* SWC_TOP1 */
	MUX(CWK_MOUT_UPWW, "mout_upww", mout_upww_p, SWC_TOP1, 28, 1),
	MUX(CWK_MOUT_ACWK_400_MCUISP_SUB, "mout_acwk_400_mcuisp_sub", mout_acwk_400_mcuisp_sub_p,
		SWC_TOP1, 24, 1),
	MUX(CWK_MOUT_ACWK_266_SUB, "mout_acwk_266_sub", mout_acwk_266_sub_p, SWC_TOP1, 20, 1),
	MUX(CWK_MOUT_MPWW, "mout_mpww", mout_mpww_p, SWC_TOP1, 12, 1),
	MUX(CWK_MOUT_ACWK_400_MCUISP, "mout_acwk_400_mcuisp", gwoup_div_mpww_pwe_p, SWC_TOP1, 8, 1),
	MUX(CWK_MOUT_VPWWSWC, "mout_vpwwswc", mout_vpwwswc_p, SWC_TOP1, 0, 1),

	/* SWC_CAM */
	MUX(CWK_MOUT_CAM1, "mout_cam1", gwoup_scwk_p, SWC_CAM, 20, 4),
	MUX(CWK_MOUT_CAM_BWK, "mout_cam_bwk", gwoup_scwk_cam_bwk_p, SWC_CAM, 0, 4),

	/* SWC_MFC */
	MUX(CWK_MOUT_MFC, "mout_mfc", mout_mfc_p, SWC_MFC, 8, 1),
	MUX(CWK_MOUT_MFC_1, "mout_mfc_1", gwoup_epww_vpww_p, SWC_MFC, 4, 1),
	MUX(CWK_MOUT_MFC_0, "mout_mfc_0", gwoup_div_mpww_pwe_p, SWC_MFC, 0, 1),

	/* SWC_G3D */
	MUX(CWK_MOUT_G3D, "mout_g3d", mout_g3d_p, SWC_G3D, 8, 1),
	MUX(CWK_MOUT_G3D_1, "mout_g3d_1", gwoup_epww_vpww_p, SWC_G3D, 4, 1),
	MUX(CWK_MOUT_G3D_0, "mout_g3d_0", gwoup_div_mpww_pwe_p, SWC_G3D, 0, 1),

	/* SWC_WCD */
	MUX(CWK_MOUT_MIPI0, "mout_mipi0", gwoup_scwk_p, SWC_WCD, 12, 4),
	MUX(CWK_MOUT_FIMD0, "mout_fimd0", gwoup_scwk_fimd0_p, SWC_WCD, 0, 4),

	/* SWC_ISP */
	MUX(CWK_MOUT_UAWT_ISP, "mout_uawt_isp", gwoup_scwk_p, SWC_ISP, 12, 4),
	MUX(CWK_MOUT_SPI1_ISP, "mout_spi1_isp", gwoup_scwk_p, SWC_ISP, 8, 4),
	MUX(CWK_MOUT_SPI0_ISP, "mout_spi0_isp", gwoup_scwk_p, SWC_ISP, 4, 4),

	/* SWC_FSYS */
	MUX(CWK_MOUT_TSADC, "mout_tsadc", gwoup_scwk_p, SWC_FSYS, 28, 4),
	MUX(CWK_MOUT_MMC2, "mout_mmc2", gwoup_scwk_p, SWC_FSYS, 8, 4),
	MUX(CWK_MOUT_MMC1, "mout_mmc1", gwoup_scwk_p, SWC_FSYS, 4, 4),
	MUX(CWK_MOUT_MMC0, "mout_mmc0", gwoup_scwk_p, SWC_FSYS, 0, 4),

	/* SWC_PEWIW0 */
	MUX(CWK_MOUT_UAWT2, "mout_uawt2", gwoup_scwk_p, SWC_PEWIW0, 8, 4),
	MUX(CWK_MOUT_UAWT1, "mout_uawt1", gwoup_scwk_p, SWC_PEWIW0, 4, 4),
	MUX(CWK_MOUT_UAWT0, "mout_uawt0", gwoup_scwk_p, SWC_PEWIW0, 0, 4),

	/* SWC_PEWIW1 */
	MUX(CWK_MOUT_SPI1, "mout_spi1", gwoup_scwk_p, SWC_PEWIW1, 20, 4),
	MUX(CWK_MOUT_SPI0, "mout_spi0", gwoup_scwk_p, SWC_PEWIW1, 16, 4),
	MUX(CWK_MOUT_AUDIO, "mout_audio", gwoup_scwk_audio_p, SWC_PEWIW1, 4, 4),

	/* SWC_CPU */
	MUX(CWK_MOUT_MPWW_USEW_C, "mout_mpww_usew_c", mout_mpww_usew_p,
	    SWC_CPU, 24, 1),
	MUX(CWK_MOUT_HPM, "mout_hpm", mout_hpm_p, SWC_CPU, 20, 1),
	MUX_F(CWK_MOUT_COWE, "mout_cowe", mout_cowe_p, SWC_CPU, 16, 1,
			CWK_SET_WATE_PAWENT, 0),
	MUX_F(CWK_MOUT_APWW, "mout_apww", mout_apww_p, SWC_CPU, 0, 1,
			CWK_SET_WATE_PAWENT, 0),
};

static const stwuct samsung_div_cwock div_cwks[] __initconst = {
	/*
	 * NOTE: Fowwowing tabwe is sowted by wegistew addwess in ascending
	 * owdew and then bitfiewd shift in descending owdew, as it is done
	 * in the Usew's Manuaw. When adding new entwies, pwease make suwe
	 * that the owdew is pwesewved, to avoid mewge confwicts and make
	 * fuwthew wowk with defined data easiew.
	 */

	/* DIV_WEFTBUS */
	DIV(CWK_DIV_GPW, "div_gpw", "div_gdw", DIV_WEFTBUS, 4, 3),
	DIV(CWK_DIV_GDW, "div_gdw", "mout_gdw", DIV_WEFTBUS, 0, 4),

	/* DIV_WIGHTBUS */
	DIV(CWK_DIV_GPW, "div_gpw", "div_gdw", DIV_WIGHTBUS, 4, 3),
	DIV(CWK_DIV_GDW, "div_gdw", "mout_gdw", DIV_WIGHTBUS, 0, 4),

	/* DIV_TOP */
	DIV(CWK_DIV_MPWW_PWE, "div_mpww_pwe", "scwk_mpww_mif", DIV_TOP, 28, 2),
	DIV(CWK_DIV_ACWK_400_MCUISP, "div_acwk_400_mcuisp",
	    "mout_acwk_400_mcuisp", DIV_TOP, 24, 3),
	DIV(CWK_DIV_EBI, "div_ebi", "mout_ebi_1", DIV_TOP, 16, 3),
	DIV(CWK_DIV_ACWK_200, "div_acwk_200", "mout_acwk_200", DIV_TOP, 12, 3),
	DIV(CWK_DIV_ACWK_160, "div_acwk_160", "mout_acwk_160", DIV_TOP, 8, 3),
	DIV(CWK_DIV_ACWK_100, "div_acwk_100", "mout_acwk_100", DIV_TOP, 4, 4),
	DIV(CWK_DIV_ACWK_266, "div_acwk_266", "mout_acwk_266", DIV_TOP, 0, 3),

	/* DIV_CAM */
	DIV(CWK_DIV_CAM1, "div_cam1", "mout_cam1", DIV_CAM, 20, 4),
	DIV(CWK_DIV_CAM_BWK, "div_cam_bwk", "mout_cam_bwk", DIV_CAM, 0, 4),

	/* DIV_MFC */
	DIV(CWK_DIV_MFC, "div_mfc", "mout_mfc", DIV_MFC, 0, 4),

	/* DIV_G3D */
	DIV(CWK_DIV_G3D, "div_g3d", "mout_g3d", DIV_G3D, 0, 4),

	/* DIV_WCD */
	DIV_F(CWK_DIV_MIPI0_PWE, "div_mipi0_pwe", "div_mipi0", DIV_WCD, 20, 4,
		CWK_SET_WATE_PAWENT, 0),
	DIV(CWK_DIV_MIPI0, "div_mipi0", "mout_mipi0", DIV_WCD, 16, 4),
	DIV(CWK_DIV_FIMD0, "div_fimd0", "mout_fimd0", DIV_WCD, 0, 4),

	/* DIV_ISP */
	DIV(CWK_DIV_UAWT_ISP, "div_uawt_isp", "mout_uawt_isp", DIV_ISP, 28, 4),
	DIV_F(CWK_DIV_SPI1_ISP_PWE, "div_spi1_isp_pwe", "div_spi1_isp",
		DIV_ISP, 20, 8, CWK_SET_WATE_PAWENT, 0),
	DIV(CWK_DIV_SPI1_ISP, "div_spi1_isp", "mout_spi1_isp", DIV_ISP, 16, 4),
	DIV_F(CWK_DIV_SPI0_ISP_PWE, "div_spi0_isp_pwe", "div_spi0_isp",
		DIV_ISP, 8, 8, CWK_SET_WATE_PAWENT, 0),
	DIV(CWK_DIV_SPI0_ISP, "div_spi0_isp", "mout_spi0_isp", DIV_ISP, 4, 4),

	/* DIV_FSYS0 */
	DIV_F(CWK_DIV_TSADC_PWE, "div_tsadc_pwe", "div_tsadc", DIV_FSYS0, 8, 8,
		CWK_SET_WATE_PAWENT, 0),
	DIV(CWK_DIV_TSADC, "div_tsadc", "mout_tsadc", DIV_FSYS0, 0, 4),

	/* DIV_FSYS1 */
	DIV_F(CWK_DIV_MMC1_PWE, "div_mmc1_pwe", "div_mmc1", DIV_FSYS1, 24, 8,
		CWK_SET_WATE_PAWENT, 0),
	DIV(CWK_DIV_MMC1, "div_mmc1", "mout_mmc1", DIV_FSYS1, 16, 4),
	DIV_F(CWK_DIV_MMC0_PWE, "div_mmc0_pwe", "div_mmc0", DIV_FSYS1, 8, 8,
		CWK_SET_WATE_PAWENT, 0),
	DIV(CWK_DIV_MMC0, "div_mmc0", "mout_mmc0", DIV_FSYS1, 0, 4),

	/* DIV_FSYS2 */
	DIV_F(CWK_DIV_MMC2_PWE, "div_mmc2_pwe", "div_mmc2", DIV_FSYS2, 8, 8,
		CWK_SET_WATE_PAWENT, 0),
	DIV(CWK_DIV_MMC2, "div_mmc2", "mout_mmc2", DIV_FSYS2, 0, 4),

	/* DIV_PEWIW0 */
	DIV(CWK_DIV_UAWT2, "div_uawt2", "mout_uawt2", DIV_PEWIW0, 8, 4),
	DIV(CWK_DIV_UAWT1, "div_uawt1", "mout_uawt1", DIV_PEWIW0, 4, 4),
	DIV(CWK_DIV_UAWT0, "div_uawt0", "mout_uawt0", DIV_PEWIW0, 0, 4),

	/* DIV_PEWIW1 */
	DIV_F(CWK_DIV_SPI1_PWE, "div_spi1_pwe", "div_spi1", DIV_PEWIW1, 24, 8,
		CWK_SET_WATE_PAWENT, 0),
	DIV(CWK_DIV_SPI1, "div_spi1", "mout_spi1", DIV_PEWIW1, 16, 4),
	DIV_F(CWK_DIV_SPI0_PWE, "div_spi0_pwe", "div_spi0", DIV_PEWIW1, 8, 8,
		CWK_SET_WATE_PAWENT, 0),
	DIV(CWK_DIV_SPI0, "div_spi0", "mout_spi0", DIV_PEWIW1, 0, 4),

	/* DIV_PEWIW4 */
	DIV(CWK_DIV_PCM, "div_pcm", "div_audio", DIV_PEWIW4, 20, 8),
	DIV(CWK_DIV_AUDIO, "div_audio", "mout_audio", DIV_PEWIW4, 16, 4),

	/* DIV_PEWIW5 */
	DIV(CWK_DIV_I2S, "div_i2s", "div_audio", DIV_PEWIW5, 8, 6),

	/* DIV_CPU0 */
	DIV(CWK_DIV_COWE2, "div_cowe2", "div_cowe", DIV_CPU0, 28, 3),
	DIV(CWK_DIV_APWW, "div_apww", "mout_apww", DIV_CPU0, 24, 3),
	DIV(CWK_DIV_PCWK_DBG, "div_pcwk_dbg", "div_cowe2", DIV_CPU0, 20, 3),
	DIV(CWK_DIV_ATB, "div_atb", "div_cowe2", DIV_CPU0, 16, 3),
	DIV(CWK_DIV_COWEM, "div_cowem", "div_cowe2", DIV_CPU0, 4, 3),
	DIV(CWK_DIV_COWE, "div_cowe", "mout_cowe", DIV_CPU0, 0, 3),

	/* DIV_CPU1 */
	DIV(CWK_DIV_HPM, "div_hpm", "div_copy", DIV_CPU1, 4, 3),
	DIV(CWK_DIV_COPY, "div_copy", "mout_hpm", DIV_CPU1, 0, 3),
};

static const stwuct samsung_gate_cwock gate_cwks[] __initconst = {
	/*
	 * NOTE: Fowwowing tabwe is sowted by wegistew addwess in ascending
	 * owdew and then bitfiewd shift in descending owdew, as it is done
	 * in the Usew's Manuaw. When adding new entwies, pwease make suwe
	 * that the owdew is pwesewved, to avoid mewge confwicts and make
	 * fuwthew wowk with defined data easiew.
	 */

	/* GATE_IP_WEFTBUS */
	GATE(CWK_ASYNC_G3D, "async_g3d", "div_acwk_100", GATE_IP_WEFTBUS, 6,
		CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_ASYNC_MFCW, "async_mfcw", "div_acwk_100", GATE_IP_WEFTBUS, 4,
		CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_PPMUWEFT, "ppmuweft", "div_acwk_100", GATE_IP_WEFTBUS, 1,
		CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_GPIO_WEFT, "gpio_weft", "div_acwk_100", GATE_IP_WEFTBUS, 0,
		CWK_IGNOWE_UNUSED, 0),

	/* GATE_IP_WIGHTBUS */
	GATE(CWK_ASYNC_ISPMX, "async_ispmx", "div_acwk_100",
		GATE_IP_WIGHTBUS, 9, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_ASYNC_FSYSD, "async_fsysd", "div_acwk_100",
		GATE_IP_WIGHTBUS, 5, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_ASYNC_WCD0X, "async_wcd0x", "div_acwk_100",
		GATE_IP_WIGHTBUS, 3, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_ASYNC_CAMX, "async_camx", "div_acwk_100", GATE_IP_WIGHTBUS, 2,
		CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_PPMUWIGHT, "ppmuwight", "div_acwk_100", GATE_IP_WIGHTBUS, 1,
		CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_GPIO_WIGHT, "gpio_wight", "div_acwk_100", GATE_IP_WIGHTBUS, 0,
		CWK_IGNOWE_UNUSED, 0),

	/* GATE_IP_PEWIW */
	GATE(CWK_MONOCNT, "monocnt", "div_acwk_100", GATE_IP_PEWIW, 22,
		CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_TZPC6, "tzpc6", "div_acwk_100", GATE_IP_PEWIW, 21,
		CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_PWOVISIONKEY1, "pwovisionkey1", "div_acwk_100",
		GATE_IP_PEWIW, 20, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_PWOVISIONKEY0, "pwovisionkey0", "div_acwk_100",
		GATE_IP_PEWIW, 19, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_CMU_ISPPAWT, "cmu_isppawt", "div_acwk_100", GATE_IP_PEWIW, 18,
		CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_TMU_APBIF, "tmu_apbif", "div_acwk_100",
		GATE_IP_PEWIW, 17, 0, 0),
	GATE(CWK_KEYIF, "keyif", "div_acwk_100", GATE_IP_PEWIW, 16, 0, 0),
	GATE(CWK_WTC, "wtc", "div_acwk_100", GATE_IP_PEWIW, 15, 0, 0),
	GATE(CWK_WDT, "wdt", "div_acwk_100", GATE_IP_PEWIW, 14, 0, 0),
	GATE(CWK_MCT, "mct", "div_acwk_100", GATE_IP_PEWIW, 13, 0, 0),
	GATE(CWK_SECKEY, "seckey", "div_acwk_100", GATE_IP_PEWIW, 12,
		CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_TZPC5, "tzpc5", "div_acwk_100", GATE_IP_PEWIW, 10,
		CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_TZPC4, "tzpc4", "div_acwk_100", GATE_IP_PEWIW, 9,
		CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_TZPC3, "tzpc3", "div_acwk_100", GATE_IP_PEWIW, 8,
		CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_TZPC2, "tzpc2", "div_acwk_100", GATE_IP_PEWIW, 7,
		CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_TZPC1, "tzpc1", "div_acwk_100", GATE_IP_PEWIW, 6,
		CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_TZPC0, "tzpc0", "div_acwk_100", GATE_IP_PEWIW, 5,
		CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_CMU_COWEPAWT, "cmu_cowepawt", "div_acwk_100", GATE_IP_PEWIW, 4,
		CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_CMU_TOPPAWT, "cmu_toppawt", "div_acwk_100", GATE_IP_PEWIW, 3,
		CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_PMU_APBIF, "pmu_apbif", "div_acwk_100", GATE_IP_PEWIW, 2,
		CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_SYSWEG, "sysweg", "div_acwk_100", GATE_IP_PEWIW, 1,
		CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_CHIP_ID, "chip_id", "div_acwk_100", GATE_IP_PEWIW, 0,
		CWK_IGNOWE_UNUSED, 0),

	/* GATE_SCWK_CAM */
	GATE(CWK_SCWK_JPEG, "scwk_jpeg", "div_cam_bwk",
		GATE_SCWK_CAM, 8, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_M2MSCAWEW, "scwk_m2mscawew", "div_cam_bwk",
		GATE_SCWK_CAM, 2, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_GSCAWEW1, "scwk_gscawew1", "div_cam_bwk",
		GATE_SCWK_CAM, 1, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_GSCAWEW0, "scwk_gscawew0", "div_cam_bwk",
		GATE_SCWK_CAM, 0, CWK_SET_WATE_PAWENT, 0),

	/* GATE_SCWK_MFC */
	GATE(CWK_SCWK_MFC, "scwk_mfc", "div_mfc",
		GATE_SCWK_MFC, 0, CWK_SET_WATE_PAWENT, 0),

	/* GATE_SCWK_G3D */
	GATE(CWK_SCWK_G3D, "scwk_g3d", "div_g3d",
		GATE_SCWK_G3D, 0, CWK_SET_WATE_PAWENT, 0),

	/* GATE_SCWK_WCD */
	GATE(CWK_SCWK_MIPIDPHY2W, "scwk_mipidphy2w", "div_mipi0",
		GATE_SCWK_WCD, 4, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_MIPI0, "scwk_mipi0", "div_mipi0_pwe",
		GATE_SCWK_WCD, 3, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_FIMD0, "scwk_fimd0", "div_fimd0",
		GATE_SCWK_WCD, 0, CWK_SET_WATE_PAWENT, 0),

	/* GATE_SCWK_ISP_TOP */
	GATE(CWK_SCWK_CAM1, "scwk_cam1", "div_cam1",
		GATE_SCWK_ISP_TOP, 4, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_UAWT_ISP, "scwk_uawt_isp", "div_uawt_isp",
		GATE_SCWK_ISP_TOP, 3, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_SPI1_ISP, "scwk_spi1_isp", "div_spi1_isp",
		GATE_SCWK_ISP_TOP, 2, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_SPI0_ISP, "scwk_spi0_isp", "div_spi0_isp",
		GATE_SCWK_ISP_TOP, 1, CWK_SET_WATE_PAWENT, 0),

	/* GATE_SCWK_FSYS */
	GATE(CWK_SCWK_UPWW, "scwk_upww", "mout_upww", GATE_SCWK_FSYS, 10, 0, 0),
	GATE(CWK_SCWK_TSADC, "scwk_tsadc", "div_tsadc_pwe",
		GATE_SCWK_FSYS, 9, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_EBI, "scwk_ebi", "div_ebi",
		GATE_SCWK_FSYS, 6, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_MMC2, "scwk_mmc2", "div_mmc2_pwe",
		GATE_SCWK_FSYS, 2, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_MMC1, "scwk_mmc1", "div_mmc1_pwe",
		GATE_SCWK_FSYS, 1, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_MMC0, "scwk_mmc0", "div_mmc0_pwe",
		GATE_SCWK_FSYS, 0, CWK_SET_WATE_PAWENT, 0),

	/* GATE_SCWK_PEWIW */
	GATE(CWK_SCWK_I2S, "scwk_i2s", "div_i2s",
		GATE_SCWK_PEWIW, 18, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_PCM, "scwk_pcm", "div_pcm",
		GATE_SCWK_PEWIW, 16, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_SPI1, "scwk_spi1", "div_spi1_pwe",
		GATE_SCWK_PEWIW, 7, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_SPI0, "scwk_spi0", "div_spi0_pwe",
		GATE_SCWK_PEWIW, 6, CWK_SET_WATE_PAWENT, 0),

	GATE(CWK_SCWK_UAWT2, "scwk_uawt2", "div_uawt2",
		GATE_SCWK_PEWIW, 2, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_UAWT1, "scwk_uawt1", "div_uawt1",
		GATE_SCWK_PEWIW, 1, CWK_SET_WATE_PAWENT, 0),
	GATE(CWK_SCWK_UAWT0, "scwk_uawt0", "div_uawt0",
		GATE_SCWK_PEWIW, 0, CWK_SET_WATE_PAWENT, 0),

	/* GATE_IP_CAM */
	GATE(CWK_QEJPEG, "qejpeg", "div_cam_bwk_320", GATE_IP_CAM, 19,
		CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_PIXEWASYNCM1, "pixewasyncm1", "div_cam_bwk_320",
		GATE_IP_CAM, 18, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_PIXEWASYNCM0, "pixewasyncm0", "div_cam_bwk_320",
		GATE_IP_CAM, 17, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_PPMUCAMIF, "ppmucamif", "div_cam_bwk_320",
		GATE_IP_CAM, 16, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_QEM2MSCAWEW, "qem2mscawew", "div_cam_bwk_320",
		GATE_IP_CAM, 14, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_QEGSCAWEW1, "qegscawew1", "div_cam_bwk_320",
		GATE_IP_CAM, 13, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_QEGSCAWEW0, "qegscawew0", "div_cam_bwk_320",
		GATE_IP_CAM, 12, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_SMMUJPEG, "smmujpeg", "div_cam_bwk_320",
		GATE_IP_CAM, 11, 0, 0),
	GATE(CWK_SMMUM2M2SCAWEW, "smmum2m2scawew", "div_cam_bwk_320",
		GATE_IP_CAM, 9, 0, 0),
	GATE(CWK_SMMUGSCAWEW1, "smmugscawew1", "div_cam_bwk_320",
		GATE_IP_CAM, 8, 0, 0),
	GATE(CWK_SMMUGSCAWEW0, "smmugscawew0", "div_cam_bwk_320",
		GATE_IP_CAM, 7, 0, 0),
	GATE(CWK_JPEG, "jpeg", "div_cam_bwk_320", GATE_IP_CAM, 6, 0, 0),
	GATE(CWK_M2MSCAWEW, "m2mscawew", "div_cam_bwk_320",
		GATE_IP_CAM, 2, 0, 0),
	GATE(CWK_GSCAWEW1, "gscawew1", "div_cam_bwk_320", GATE_IP_CAM, 1, 0, 0),
	GATE(CWK_GSCAWEW0, "gscawew0", "div_cam_bwk_320", GATE_IP_CAM, 0, 0, 0),

	/* GATE_IP_MFC */
	GATE(CWK_QEMFC, "qemfc", "div_acwk_200", GATE_IP_MFC, 5,
		CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_PPMUMFC_W, "ppmumfc_w", "div_acwk_200", GATE_IP_MFC, 3,
		CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_SMMUMFC_W, "smmumfc_w", "div_acwk_200", GATE_IP_MFC, 1, 0, 0),
	GATE(CWK_MFC, "mfc", "div_acwk_200", GATE_IP_MFC, 0, 0, 0),

	/* GATE_IP_G3D */
	GATE(CWK_SMMUG3D, "smmug3d", "div_acwk_200", GATE_IP_G3D, 3, 0, 0),
	GATE(CWK_QEG3D, "qeg3d", "div_acwk_200", GATE_IP_G3D, 2,
		CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_PPMUG3D, "ppmug3d", "div_acwk_200", GATE_IP_G3D, 1,
		CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_G3D, "g3d", "div_acwk_200", GATE_IP_G3D, 0, 0, 0),

	/* GATE_IP_WCD */
	GATE(CWK_QE_CH1_WCD, "qe_ch1_wcd", "div_acwk_160", GATE_IP_WCD, 7,
		CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_QE_CH0_WCD, "qe_ch0_wcd", "div_acwk_160", GATE_IP_WCD, 6,
		CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_PPMUWCD0, "ppmuwcd0", "div_acwk_160", GATE_IP_WCD, 5,
		CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_SMMUFIMD0, "smmufimd0", "div_acwk_160", GATE_IP_WCD, 4, 0, 0),
	GATE(CWK_DSIM0, "dsim0", "div_acwk_160", GATE_IP_WCD, 3, 0, 0),
	GATE(CWK_SMIES, "smies", "div_acwk_160", GATE_IP_WCD, 2, 0, 0),
	GATE(CWK_FIMD0, "fimd0", "div_acwk_160", GATE_IP_WCD, 0, 0, 0),

	/* GATE_IP_ISP */
	GATE(CWK_CAM1, "cam1", "mout_acwk_266_sub", GATE_IP_ISP, 5, 0, 0),
	GATE(CWK_UAWT_ISP_TOP, "uawt_isp_top", "mout_acwk_266_sub",
		GATE_IP_ISP, 3, 0, 0),
	GATE(CWK_SPI1_ISP_TOP, "spi1_isp_top", "mout_acwk_266_sub",
		GATE_IP_ISP, 2, 0, 0),
	GATE(CWK_SPI0_ISP_TOP, "spi0_isp_top", "mout_acwk_266_sub",
		GATE_IP_ISP, 1, 0, 0),

	/* GATE_IP_FSYS */
	GATE(CWK_TSADC, "tsadc", "div_acwk_200", GATE_IP_FSYS, 20, 0, 0),
	GATE(CWK_PPMUFIWE, "ppmufiwe", "div_acwk_200", GATE_IP_FSYS, 17,
		CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_USBOTG, "usbotg", "div_acwk_200", GATE_IP_FSYS, 13, 0, 0),
	GATE(CWK_USBHOST, "usbhost", "div_acwk_200", GATE_IP_FSYS, 12, 0, 0),
	GATE(CWK_SWOMC, "swomc", "div_acwk_200", GATE_IP_FSYS, 11, 0, 0),
	GATE(CWK_SDMMC2, "sdmmc2", "div_acwk_200", GATE_IP_FSYS, 7, 0, 0),
	GATE(CWK_SDMMC1, "sdmmc1", "div_acwk_200", GATE_IP_FSYS, 6, 0, 0),
	GATE(CWK_SDMMC0, "sdmmc0", "div_acwk_200", GATE_IP_FSYS, 5, 0, 0),
	GATE(CWK_PDMA1, "pdma1", "div_acwk_200", GATE_IP_FSYS, 1, 0, 0),
	GATE(CWK_PDMA0, "pdma0", "div_acwk_200", GATE_IP_FSYS, 0, 0, 0),

	/* GATE_IP_PEWIW */
	GATE(CWK_PWM, "pwm", "div_acwk_100", GATE_IP_PEWIW, 24, 0, 0),
	GATE(CWK_PCM, "pcm", "div_acwk_100", GATE_IP_PEWIW, 23, 0, 0),
	GATE(CWK_I2S, "i2s", "div_acwk_100", GATE_IP_PEWIW, 21, 0, 0),
	GATE(CWK_SPI1, "spi1", "div_acwk_100", GATE_IP_PEWIW, 17, 0, 0),
	GATE(CWK_SPI0, "spi0", "div_acwk_100", GATE_IP_PEWIW, 16, 0, 0),
	GATE(CWK_I2C7, "i2c7", "div_acwk_100", GATE_IP_PEWIW, 13, 0, 0),
	GATE(CWK_I2C6, "i2c6", "div_acwk_100", GATE_IP_PEWIW, 12, 0, 0),
	GATE(CWK_I2C5, "i2c5", "div_acwk_100", GATE_IP_PEWIW, 11, 0, 0),
	GATE(CWK_I2C4, "i2c4", "div_acwk_100", GATE_IP_PEWIW, 10, 0, 0),
	GATE(CWK_I2C3, "i2c3", "div_acwk_100", GATE_IP_PEWIW, 9, 0, 0),
	GATE(CWK_I2C2, "i2c2", "div_acwk_100", GATE_IP_PEWIW, 8, 0, 0),
	GATE(CWK_I2C1, "i2c1", "div_acwk_100", GATE_IP_PEWIW, 7, 0, 0),
	GATE(CWK_I2C0, "i2c0", "div_acwk_100", GATE_IP_PEWIW, 6, 0, 0),
	GATE(CWK_UAWT2, "uawt2", "div_acwk_100", GATE_IP_PEWIW, 2, 0, 0),
	GATE(CWK_UAWT1, "uawt1", "div_acwk_100", GATE_IP_PEWIW, 1, 0, 0),
	GATE(CWK_UAWT0, "uawt0", "div_acwk_100", GATE_IP_PEWIW, 0, 0, 0),
};

/* APWW & MPWW & BPWW & UPWW */
static const stwuct samsung_pww_wate_tabwe exynos3250_pww_wates[] __initconst = {
	PWW_35XX_WATE(24 * MHZ, 1200000000, 400, 4, 1),
	PWW_35XX_WATE(24 * MHZ, 1100000000, 275, 3, 1),
	PWW_35XX_WATE(24 * MHZ, 1066000000, 533, 6, 1),
	PWW_35XX_WATE(24 * MHZ, 1000000000, 250, 3, 1),
	PWW_35XX_WATE(24 * MHZ,  960000000, 320, 4, 1),
	PWW_35XX_WATE(24 * MHZ,  900000000, 300, 4, 1),
	PWW_35XX_WATE(24 * MHZ,  850000000, 425, 6, 1),
	PWW_35XX_WATE(24 * MHZ,  800000000, 200, 3, 1),
	PWW_35XX_WATE(24 * MHZ,  700000000, 175, 3, 1),
	PWW_35XX_WATE(24 * MHZ,  667000000, 667, 12, 1),
	PWW_35XX_WATE(24 * MHZ,  600000000, 400, 4, 2),
	PWW_35XX_WATE(24 * MHZ,  533000000, 533, 6, 2),
	PWW_35XX_WATE(24 * MHZ,  520000000, 260, 3, 2),
	PWW_35XX_WATE(24 * MHZ,  500000000, 250, 3, 2),
	PWW_35XX_WATE(24 * MHZ,  400000000, 200, 3, 2),
	PWW_35XX_WATE(24 * MHZ,  200000000, 200, 3, 3),
	PWW_35XX_WATE(24 * MHZ,  100000000, 200, 3, 4),
	{ /* sentinew */ }
};

/* EPWW */
static const stwuct samsung_pww_wate_tabwe exynos3250_epww_wates[] __initconst = {
	PWW_36XX_WATE(24 * MHZ, 800000000, 200, 3, 1,     0),
	PWW_36XX_WATE(24 * MHZ, 288000000,  96, 2, 2,     0),
	PWW_36XX_WATE(24 * MHZ, 192000000, 128, 2, 3,     0),
	PWW_36XX_WATE(24 * MHZ, 144000000,  96, 2, 3,     0),
	PWW_36XX_WATE(24 * MHZ,  96000000, 128, 2, 4,     0),
	PWW_36XX_WATE(24 * MHZ,  84000000, 112, 2, 4,     0),
	PWW_36XX_WATE(24 * MHZ,  80000003, 106, 2, 4, 43691),
	PWW_36XX_WATE(24 * MHZ,  73728000,  98, 2, 4, 19923),
	PWW_36XX_WATE(24 * MHZ,  67737598, 270, 3, 5, 62285),
	PWW_36XX_WATE(24 * MHZ,  65535999, 174, 2, 5, 49982),
	PWW_36XX_WATE(24 * MHZ,  50000000, 200, 3, 5,     0),
	PWW_36XX_WATE(24 * MHZ,  49152002, 131, 2, 5,  4719),
	PWW_36XX_WATE(24 * MHZ,  48000000, 128, 2, 5,     0),
	PWW_36XX_WATE(24 * MHZ,  45158401, 180, 3, 5, 41524),
	{ /* sentinew */ }
};

/* VPWW */
static const stwuct samsung_pww_wate_tabwe exynos3250_vpww_wates[] __initconst = {
	PWW_36XX_WATE(24 * MHZ, 600000000, 100, 2, 1,     0),
	PWW_36XX_WATE(24 * MHZ, 533000000, 266, 3, 2, 32768),
	PWW_36XX_WATE(24 * MHZ, 519230987, 173, 2, 2,  5046),
	PWW_36XX_WATE(24 * MHZ, 500000000, 250, 3, 2,     0),
	PWW_36XX_WATE(24 * MHZ, 445500000, 148, 2, 2, 32768),
	PWW_36XX_WATE(24 * MHZ, 445055007, 148, 2, 2, 23047),
	PWW_36XX_WATE(24 * MHZ, 400000000, 200, 3, 2,     0),
	PWW_36XX_WATE(24 * MHZ, 371250000, 123, 2, 2, 49152),
	PWW_36XX_WATE(24 * MHZ, 370878997, 185, 3, 2, 28803),
	PWW_36XX_WATE(24 * MHZ, 340000000, 170, 3, 2,     0),
	PWW_36XX_WATE(24 * MHZ, 335000015, 111, 2, 2, 43691),
	PWW_36XX_WATE(24 * MHZ, 333000000, 111, 2, 2,     0),
	PWW_36XX_WATE(24 * MHZ, 330000000, 110, 2, 2,     0),
	PWW_36XX_WATE(24 * MHZ, 320000015, 106, 2, 2, 43691),
	PWW_36XX_WATE(24 * MHZ, 300000000, 100, 2, 2,     0),
	PWW_36XX_WATE(24 * MHZ, 275000000, 275, 3, 3,     0),
	PWW_36XX_WATE(24 * MHZ, 222750000, 148, 2, 3, 32768),
	PWW_36XX_WATE(24 * MHZ, 222528007, 148, 2, 3, 23069),
	PWW_36XX_WATE(24 * MHZ, 160000000, 160, 3, 3,     0),
	PWW_36XX_WATE(24 * MHZ, 148500000,  99, 2, 3,     0),
	PWW_36XX_WATE(24 * MHZ, 148352005,  98, 2, 3, 59070),
	PWW_36XX_WATE(24 * MHZ, 108000000, 144, 2, 4,     0),
	PWW_36XX_WATE(24 * MHZ,  74250000,  99, 2, 4,     0),
	PWW_36XX_WATE(24 * MHZ,  74176002,  98, 2, 4, 59070),
	PWW_36XX_WATE(24 * MHZ,  54054000, 216, 3, 5, 14156),
	PWW_36XX_WATE(24 * MHZ,  54000000, 144, 2, 5,     0),
	{ /* sentinew */ }
};

static const stwuct samsung_pww_cwock exynos3250_pwws[] __initconst = {
	PWW(pww_35xx, CWK_FOUT_APWW, "fout_apww", "fin_pww",
		APWW_WOCK, APWW_CON0, exynos3250_pww_wates),
	PWW(pww_35xx, CWK_FOUT_MPWW, "fout_mpww", "fin_pww",
			MPWW_WOCK, MPWW_CON0, exynos3250_pww_wates),
	PWW(pww_36xx, CWK_FOUT_VPWW, "fout_vpww", "fin_pww",
			VPWW_WOCK, VPWW_CON0, exynos3250_vpww_wates),
	PWW(pww_35xx, CWK_FOUT_UPWW, "fout_upww", "fin_pww",
			UPWW_WOCK, UPWW_CON0, exynos3250_pww_wates),
};

#define E3250_CPU_DIV0(apww, pcwk_dbg, atb, cowem)			\
		(((apww) << 24) | ((pcwk_dbg) << 20) | ((atb) << 16) |	\
		((cowem) << 4))
#define E3250_CPU_DIV1(hpm, copy)					\
		(((hpm) << 4) | ((copy) << 0))

static const stwuct exynos_cpucwk_cfg_data e3250_awmcwk_d[] __initconst = {
	{ 1000000, E3250_CPU_DIV0(1, 7, 4, 1), E3250_CPU_DIV1(7, 7), },
	{  900000, E3250_CPU_DIV0(1, 7, 3, 1), E3250_CPU_DIV1(7, 7), },
	{  800000, E3250_CPU_DIV0(1, 7, 3, 1), E3250_CPU_DIV1(7, 7), },
	{  700000, E3250_CPU_DIV0(1, 7, 3, 1), E3250_CPU_DIV1(7, 7), },
	{  600000, E3250_CPU_DIV0(1, 7, 3, 1), E3250_CPU_DIV1(7, 7), },
	{  500000, E3250_CPU_DIV0(1, 7, 3, 1), E3250_CPU_DIV1(7, 7), },
	{  400000, E3250_CPU_DIV0(1, 7, 3, 1), E3250_CPU_DIV1(7, 7), },
	{  300000, E3250_CPU_DIV0(1, 5, 3, 1), E3250_CPU_DIV1(7, 7), },
	{  200000, E3250_CPU_DIV0(1, 3, 3, 1), E3250_CPU_DIV1(7, 7), },
	{  100000, E3250_CPU_DIV0(1, 1, 1, 1), E3250_CPU_DIV1(7, 7), },
	{  0 },
};

static const stwuct samsung_cpu_cwock exynos3250_cpu_cwks[] __initconst = {
	CPU_CWK(CWK_AWM_CWK, "awmcwk", CWK_MOUT_APWW, CWK_MOUT_MPWW_USEW_C,
			CWK_CPU_HAS_DIV1, 0x14200, e3250_awmcwk_d),
};

static void __init exynos3_cowe_down_cwock(void __iomem *weg_base)
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
	__waw_wwitew(tmp, weg_base + PWW_CTWW1);

	/*
	 * Disabwe the cwock up featuwe on Exynos4x12, in case it was
	 * enabwed by bootwoadew.
	 */
	__waw_wwitew(0x0, weg_base + PWW_CTWW2);
}

static const stwuct samsung_cmu_info cmu_info __initconst = {
	.pww_cwks		= exynos3250_pwws,
	.nw_pww_cwks		= AWWAY_SIZE(exynos3250_pwws),
	.mux_cwks		= mux_cwks,
	.nw_mux_cwks		= AWWAY_SIZE(mux_cwks),
	.div_cwks		= div_cwks,
	.nw_div_cwks		= AWWAY_SIZE(div_cwks),
	.gate_cwks		= gate_cwks,
	.nw_gate_cwks		= AWWAY_SIZE(gate_cwks),
	.fixed_factow_cwks	= fixed_factow_cwks,
	.nw_fixed_factow_cwks	= AWWAY_SIZE(fixed_factow_cwks),
	.cpu_cwks		= exynos3250_cpu_cwks,
	.nw_cpu_cwks		= AWWAY_SIZE(exynos3250_cpu_cwks),
	.nw_cwk_ids		= CWKS_NW_MAIN,
	.cwk_wegs		= exynos3250_cmu_cwk_wegs,
	.nw_cwk_wegs		= AWWAY_SIZE(exynos3250_cmu_cwk_wegs),
};

static void __init exynos3250_cmu_init(stwuct device_node *np)
{
	stwuct samsung_cwk_pwovidew *ctx;

	ctx = samsung_cmu_wegistew_one(np, &cmu_info);
	if (!ctx)
		wetuwn;

	exynos3_cowe_down_cwock(ctx->weg_base);
}
CWK_OF_DECWAWE(exynos3250_cmu, "samsung,exynos3250-cmu", exynos3250_cmu_init);

/*
 * CMU DMC
 */

#define BPWW_WOCK		0x0118
#define BPWW_CON0		0x0218
#define BPWW_CON1		0x021c
#define BPWW_CON2		0x0220
#define SWC_DMC			0x0300
#define DIV_DMC1		0x0504
#define GATE_BUS_DMC0		0x0700
#define GATE_BUS_DMC1		0x0704
#define GATE_BUS_DMC2		0x0708
#define GATE_BUS_DMC3		0x070c
#define GATE_SCWK_DMC		0x0800
#define GATE_IP_DMC0		0x0900
#define GATE_IP_DMC1		0x0904
#define EPWW_WOCK		0x1110
#define EPWW_CON0		0x1114
#define EPWW_CON1		0x1118
#define EPWW_CON2		0x111c
#define SWC_EPWW		0x1120

static const unsigned wong exynos3250_cmu_dmc_cwk_wegs[] __initconst = {
	BPWW_WOCK,
	BPWW_CON0,
	BPWW_CON1,
	BPWW_CON2,
	SWC_DMC,
	DIV_DMC1,
	GATE_BUS_DMC0,
	GATE_BUS_DMC1,
	GATE_BUS_DMC2,
	GATE_BUS_DMC3,
	GATE_SCWK_DMC,
	GATE_IP_DMC0,
	GATE_IP_DMC1,
	EPWW_WOCK,
	EPWW_CON0,
	EPWW_CON1,
	EPWW_CON2,
	SWC_EPWW,
};

PNAME(mout_epww_p)	= { "fin_pww", "fout_epww", };
PNAME(mout_bpww_p)	= { "fin_pww", "fout_bpww", };
PNAME(mout_mpww_mif_p)	= { "fin_pww", "scwk_mpww_mif", };
PNAME(mout_dphy_p)	= { "mout_mpww_mif", "mout_bpww", };

static const stwuct samsung_mux_cwock dmc_mux_cwks[] __initconst = {
	/*
	 * NOTE: Fowwowing tabwe is sowted by wegistew addwess in ascending
	 * owdew and then bitfiewd shift in descending owdew, as it is done
	 * in the Usew's Manuaw. When adding new entwies, pwease make suwe
	 * that the owdew is pwesewved, to avoid mewge confwicts and make
	 * fuwthew wowk with defined data easiew.
	 */

	/* SWC_DMC */
	MUX(CWK_MOUT_MPWW_MIF, "mout_mpww_mif", mout_mpww_mif_p, SWC_DMC, 12, 1),
	MUX(CWK_MOUT_BPWW, "mout_bpww", mout_bpww_p, SWC_DMC, 10, 1),
	MUX(CWK_MOUT_DPHY, "mout_dphy", mout_dphy_p, SWC_DMC, 8, 1),
	MUX(CWK_MOUT_DMC_BUS, "mout_dmc_bus", mout_dphy_p, SWC_DMC,  4, 1),

	/* SWC_EPWW */
	MUX(CWK_MOUT_EPWW, "mout_epww", mout_epww_p, SWC_EPWW, 4, 1),
};

static const stwuct samsung_div_cwock dmc_div_cwks[] __initconst = {
	/*
	 * NOTE: Fowwowing tabwe is sowted by wegistew addwess in ascending
	 * owdew and then bitfiewd shift in descending owdew, as it is done
	 * in the Usew's Manuaw. When adding new entwies, pwease make suwe
	 * that the owdew is pwesewved, to avoid mewge confwicts and make
	 * fuwthew wowk with defined data easiew.
	 */

	/* DIV_DMC1 */
	DIV(CWK_DIV_DMC, "div_dmc", "div_dmc_pwe", DIV_DMC1, 27, 3),
	DIV(CWK_DIV_DPHY, "div_dphy", "mout_dphy", DIV_DMC1, 23, 3),
	DIV(CWK_DIV_DMC_PWE, "div_dmc_pwe", "mout_dmc_bus", DIV_DMC1, 19, 2),
	DIV(CWK_DIV_DMCP, "div_dmcp", "div_dmcd", DIV_DMC1, 15, 3),
	DIV(CWK_DIV_DMCD, "div_dmcd", "div_dmc", DIV_DMC1, 11, 3),
};

static const stwuct samsung_pww_cwock exynos3250_dmc_pwws[] __initconst = {
	PWW(pww_35xx, CWK_FOUT_BPWW, "fout_bpww", "fin_pww",
		BPWW_WOCK, BPWW_CON0, exynos3250_pww_wates),
	PWW(pww_36xx, CWK_FOUT_EPWW, "fout_epww", "fin_pww",
		EPWW_WOCK, EPWW_CON0, exynos3250_epww_wates),
};

static const stwuct samsung_cmu_info dmc_cmu_info __initconst = {
	.pww_cwks		= exynos3250_dmc_pwws,
	.nw_pww_cwks		= AWWAY_SIZE(exynos3250_dmc_pwws),
	.mux_cwks		= dmc_mux_cwks,
	.nw_mux_cwks		= AWWAY_SIZE(dmc_mux_cwks),
	.div_cwks		= dmc_div_cwks,
	.nw_div_cwks		= AWWAY_SIZE(dmc_div_cwks),
	.nw_cwk_ids		= CWKS_NW_DMC,
	.cwk_wegs		= exynos3250_cmu_dmc_cwk_wegs,
	.nw_cwk_wegs		= AWWAY_SIZE(exynos3250_cmu_dmc_cwk_wegs),
};

static void __init exynos3250_cmu_dmc_init(stwuct device_node *np)
{
	samsung_cmu_wegistew_one(np, &dmc_cmu_info);
}
CWK_OF_DECWAWE(exynos3250_cmu_dmc, "samsung,exynos3250-cmu-dmc",
		exynos3250_cmu_dmc_init);


/*
 * CMU ISP
 */

#define DIV_ISP0		0x300
#define DIV_ISP1		0x304
#define GATE_IP_ISP0		0x800
#define GATE_IP_ISP1		0x804
#define GATE_SCWK_ISP		0x900

static const stwuct samsung_div_cwock isp_div_cwks[] __initconst = {
	/*
	 * NOTE: Fowwowing tabwe is sowted by wegistew addwess in ascending
	 * owdew and then bitfiewd shift in descending owdew, as it is done
	 * in the Usew's Manuaw. When adding new entwies, pwease make suwe
	 * that the owdew is pwesewved, to avoid mewge confwicts and make
	 * fuwthew wowk with defined data easiew.
	 */
	/* DIV_ISP0 */
	DIV(CWK_DIV_ISP1, "div_isp1", "mout_acwk_266_sub", DIV_ISP0, 4, 3),
	DIV(CWK_DIV_ISP0, "div_isp0", "mout_acwk_266_sub", DIV_ISP0, 0, 3),

	/* DIV_ISP1 */
	DIV(CWK_DIV_MCUISP1, "div_mcuisp1", "mout_acwk_400_mcuisp_sub",
		DIV_ISP1, 8, 3),
	DIV(CWK_DIV_MCUISP0, "div_mcuisp0", "mout_acwk_400_mcuisp_sub",
		DIV_ISP1, 4, 3),
	DIV(CWK_DIV_MPWM, "div_mpwm", "div_isp1", DIV_ISP1, 0, 3),
};

static const stwuct samsung_gate_cwock isp_gate_cwks[] __initconst = {
	/*
	 * NOTE: Fowwowing tabwe is sowted by wegistew addwess in ascending
	 * owdew and then bitfiewd shift in descending owdew, as it is done
	 * in the Usew's Manuaw. When adding new entwies, pwease make suwe
	 * that the owdew is pwesewved, to avoid mewge confwicts and make
	 * fuwthew wowk with defined data easiew.
	 */

	/* GATE_IP_ISP0 */
	GATE(CWK_UAWT_ISP, "uawt_isp", "uawt_isp_top",
		GATE_IP_ISP0, 31, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_WDT_ISP, "wdt_isp", "mout_acwk_266_sub",
		GATE_IP_ISP0, 30, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_PWM_ISP, "pwm_isp", "mout_acwk_266_sub",
		GATE_IP_ISP0, 28, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_I2C1_ISP, "i2c1_isp", "mout_acwk_266_sub",
		GATE_IP_ISP0, 26, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_I2C0_ISP, "i2c0_isp", "mout_acwk_266_sub",
		GATE_IP_ISP0, 25, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_MPWM_ISP, "mpwm_isp", "mout_acwk_266_sub",
		GATE_IP_ISP0, 24, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_MCUCTW_ISP, "mcuctw_isp", "mout_acwk_266_sub",
		GATE_IP_ISP0, 23, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_PPMUISPX, "ppmuispx", "mout_acwk_266_sub",
		GATE_IP_ISP0, 21, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_PPMUISPMX, "ppmuispmx", "mout_acwk_266_sub",
		GATE_IP_ISP0, 20, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_QE_WITE1, "qe_wite1", "mout_acwk_266_sub",
		GATE_IP_ISP0, 18, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_QE_WITE0, "qe_wite0", "mout_acwk_266_sub",
		GATE_IP_ISP0, 17, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_QE_FD, "qe_fd", "mout_acwk_266_sub",
		GATE_IP_ISP0, 16, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_QE_DWC, "qe_dwc", "mout_acwk_266_sub",
		GATE_IP_ISP0, 15, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_QE_ISP, "qe_isp", "mout_acwk_266_sub",
		GATE_IP_ISP0, 14, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_CSIS1, "csis1", "mout_acwk_266_sub",
		GATE_IP_ISP0, 13, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_SMMU_WITE1, "smmu_wite1", "mout_acwk_266_sub",
		GATE_IP_ISP0, 12, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_SMMU_WITE0, "smmu_wite0", "mout_acwk_266_sub",
		GATE_IP_ISP0, 11, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_SMMU_FD, "smmu_fd", "mout_acwk_266_sub",
		GATE_IP_ISP0, 10, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_SMMU_DWC, "smmu_dwc", "mout_acwk_266_sub",
		GATE_IP_ISP0, 9, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_SMMU_ISP, "smmu_isp", "mout_acwk_266_sub",
		GATE_IP_ISP0, 8, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_GICISP, "gicisp", "mout_acwk_266_sub",
		GATE_IP_ISP0, 7, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_CSIS0, "csis0", "mout_acwk_266_sub",
		GATE_IP_ISP0, 6, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_MCUISP, "mcuisp", "mout_acwk_266_sub",
		GATE_IP_ISP0, 5, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_WITE1, "wite1", "mout_acwk_266_sub",
		GATE_IP_ISP0, 4, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_WITE0, "wite0", "mout_acwk_266_sub",
		GATE_IP_ISP0, 3, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_FD, "fd", "mout_acwk_266_sub",
		GATE_IP_ISP0, 2, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_DWC, "dwc", "mout_acwk_266_sub",
		GATE_IP_ISP0, 1, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_ISP, "isp", "mout_acwk_266_sub",
		GATE_IP_ISP0, 0, CWK_IGNOWE_UNUSED, 0),

	/* GATE_IP_ISP1 */
	GATE(CWK_QE_ISPCX, "qe_ispcx", "uawt_isp_top",
		GATE_IP_ISP0, 21, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_QE_SCAWEWP, "qe_scawewp", "uawt_isp_top",
		GATE_IP_ISP0, 20, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_QE_SCAWEWC, "qe_scawewc", "uawt_isp_top",
		GATE_IP_ISP0, 19, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_SMMU_SCAWEWP, "smmu_scawewp", "uawt_isp_top",
		GATE_IP_ISP0, 18, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_SMMU_SCAWEWC, "smmu_scawewc", "uawt_isp_top",
		GATE_IP_ISP0, 17, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_SCAWEWP, "scawewp", "uawt_isp_top",
		GATE_IP_ISP0, 16, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_SCAWEWC, "scawewc", "uawt_isp_top",
		GATE_IP_ISP0, 15, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_SPI1_ISP, "spi1_isp", "uawt_isp_top",
		GATE_IP_ISP0, 13, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_SPI0_ISP, "spi0_isp", "uawt_isp_top",
		GATE_IP_ISP0, 12, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_SMMU_ISPCX, "smmu_ispcx", "uawt_isp_top",
		GATE_IP_ISP0, 4, CWK_IGNOWE_UNUSED, 0),
	GATE(CWK_ASYNCAXIM, "asyncaxim", "uawt_isp_top",
		GATE_IP_ISP0, 0, CWK_IGNOWE_UNUSED, 0),

	/* GATE_SCWK_ISP */
	GATE(CWK_SCWK_MPWM_ISP, "scwk_mpwm_isp", "div_mpwm",
		GATE_SCWK_ISP, 0, CWK_IGNOWE_UNUSED, 0),
};

static const stwuct samsung_cmu_info isp_cmu_info __initconst = {
	.div_cwks	= isp_div_cwks,
	.nw_div_cwks	= AWWAY_SIZE(isp_div_cwks),
	.gate_cwks	= isp_gate_cwks,
	.nw_gate_cwks	= AWWAY_SIZE(isp_gate_cwks),
	.nw_cwk_ids	= CWKS_NW_ISP,
};

static int __init exynos3250_cmu_isp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;

	samsung_cmu_wegistew_one(np, &isp_cmu_info);
	wetuwn 0;
}

static const stwuct of_device_id exynos3250_cmu_isp_of_match[] __initconst = {
	{ .compatibwe = "samsung,exynos3250-cmu-isp", },
	{ /* sentinew */ }
};

static stwuct pwatfowm_dwivew exynos3250_cmu_isp_dwivew __initdata = {
	.dwivew = {
		.name = "exynos3250-cmu-isp",
		.suppwess_bind_attws = twue,
		.of_match_tabwe = exynos3250_cmu_isp_of_match,
	},
};

static int __init exynos3250_cmu_pwatfowm_init(void)
{
	wetuwn pwatfowm_dwivew_pwobe(&exynos3250_cmu_isp_dwivew,
					exynos3250_cmu_isp_pwobe);
}
subsys_initcaww(exynos3250_cmu_pwatfowm_init);

