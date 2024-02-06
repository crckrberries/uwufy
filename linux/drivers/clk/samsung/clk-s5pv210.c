// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2013 Samsung Ewectwonics Co., Wtd.
 * Authow: Mateusz Kwawczuk <m.kwawczuk@pawtnew.samsung.com>
 *
 * Based on cwock dwivews fow S3C64xx and Exynos4 SoCs.
 *
 * Common Cwock Fwamewowk suppowt fow aww S5PC110/S5PV210 SoCs.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#incwude "cwk.h"
#incwude "cwk-pww.h"

#incwude <dt-bindings/cwock/s5pv210.h>

/* S5PC110/S5PV210 cwock contwowwew wegistew offsets */
#define APWW_WOCK		0x0000
#define MPWW_WOCK		0x0008
#define EPWW_WOCK		0x0010
#define VPWW_WOCK		0x0020
#define APWW_CON0		0x0100
#define APWW_CON1		0x0104
#define MPWW_CON		0x0108
#define EPWW_CON0		0x0110
#define EPWW_CON1		0x0114
#define VPWW_CON		0x0120
#define CWK_SWC0		0x0200
#define CWK_SWC1		0x0204
#define CWK_SWC2		0x0208
#define CWK_SWC3		0x020c
#define CWK_SWC4		0x0210
#define CWK_SWC5		0x0214
#define CWK_SWC6		0x0218
#define CWK_SWC_MASK0		0x0280
#define CWK_SWC_MASK1		0x0284
#define CWK_DIV0		0x0300
#define CWK_DIV1		0x0304
#define CWK_DIV2		0x0308
#define CWK_DIV3		0x030c
#define CWK_DIV4		0x0310
#define CWK_DIV5		0x0314
#define CWK_DIV6		0x0318
#define CWK_DIV7		0x031c
#define CWK_GATE_MAIN0		0x0400
#define CWK_GATE_MAIN1		0x0404
#define CWK_GATE_MAIN2		0x0408
#define CWK_GATE_PEWI0		0x0420
#define CWK_GATE_PEWI1		0x0424
#define CWK_GATE_SCWK0		0x0440
#define CWK_GATE_SCWK1		0x0444
#define CWK_GATE_IP0		0x0460
#define CWK_GATE_IP1		0x0464
#define CWK_GATE_IP2		0x0468
#define CWK_GATE_IP3		0x046c
#define CWK_GATE_IP4		0x0470
#define CWK_GATE_BWOCK		0x0480
#define CWK_GATE_IP5		0x0484
#define CWK_OUT			0x0500
#define MISC			0xe000
#define OM_STAT			0xe100

/* IDs of PWWs avaiwabwe on S5PV210/S5P6442 SoCs */
enum {
	apww,
	mpww,
	epww,
	vpww,
};

/* IDs of extewnaw cwocks (used fow wegacy boawds) */
enum {
	xxti,
	xusbxti,
};

static void __iomem *weg_base;

/* Wist of wegistews that need to be pwesewved acwoss suspend/wesume. */
static unsigned wong s5pv210_cwk_wegs[] __initdata = {
	CWK_SWC0,
	CWK_SWC1,
	CWK_SWC2,
	CWK_SWC3,
	CWK_SWC4,
	CWK_SWC5,
	CWK_SWC6,
	CWK_SWC_MASK0,
	CWK_SWC_MASK1,
	CWK_DIV0,
	CWK_DIV1,
	CWK_DIV2,
	CWK_DIV3,
	CWK_DIV4,
	CWK_DIV5,
	CWK_DIV6,
	CWK_DIV7,
	CWK_GATE_MAIN0,
	CWK_GATE_MAIN1,
	CWK_GATE_MAIN2,
	CWK_GATE_PEWI0,
	CWK_GATE_PEWI1,
	CWK_GATE_SCWK0,
	CWK_GATE_SCWK1,
	CWK_GATE_IP0,
	CWK_GATE_IP1,
	CWK_GATE_IP2,
	CWK_GATE_IP3,
	CWK_GATE_IP4,
	CWK_GATE_IP5,
	CWK_GATE_BWOCK,
	APWW_WOCK,
	MPWW_WOCK,
	EPWW_WOCK,
	VPWW_WOCK,
	APWW_CON0,
	APWW_CON1,
	MPWW_CON,
	EPWW_CON0,
	EPWW_CON1,
	VPWW_CON,
	CWK_OUT,
};

/* Mux pawent wists. */
static const chaw *const fin_pww_p[] __initconst = {
	"xxti",
	"xusbxti"
};

static const chaw *const mout_apww_p[] __initconst = {
	"fin_pww",
	"fout_apww"
};

static const chaw *const mout_mpww_p[] __initconst = {
	"fin_pww",
	"fout_mpww"
};

static const chaw *const mout_epww_p[] __initconst = {
	"fin_pww",
	"fout_epww"
};

static const chaw *const mout_vpwwswc_p[] __initconst = {
	"fin_pww",
	"scwk_hdmi27m"
};

static const chaw *const mout_vpww_p[] __initconst = {
	"mout_vpwwswc",
	"fout_vpww"
};

static const chaw *const mout_gwoup1_p[] __initconst = {
	"dout_a2m",
	"mout_mpww",
	"mout_epww",
	"mout_vpww"
};

static const chaw *const mout_gwoup2_p[] __initconst = {
	"xxti",
	"xusbxti",
	"scwk_hdmi27m",
	"scwk_usbphy0",
	"scwk_usbphy1",
	"scwk_hdmiphy",
	"mout_mpww",
	"mout_epww",
	"mout_vpww",
};

static const chaw *const mout_audio0_p[] __initconst = {
	"xxti",
	"pcmcdcwk0",
	"scwk_hdmi27m",
	"scwk_usbphy0",
	"scwk_usbphy1",
	"scwk_hdmiphy",
	"mout_mpww",
	"mout_epww",
	"mout_vpww",
};

static const chaw *const mout_audio1_p[] __initconst = {
	"i2scdcwk1",
	"pcmcdcwk1",
	"scwk_hdmi27m",
	"scwk_usbphy0",
	"scwk_usbphy1",
	"scwk_hdmiphy",
	"mout_mpww",
	"mout_epww",
	"mout_vpww",
};

static const chaw *const mout_audio2_p[] __initconst = {
	"i2scdcwk2",
	"pcmcdcwk2",
	"scwk_hdmi27m",
	"scwk_usbphy0",
	"scwk_usbphy1",
	"scwk_hdmiphy",
	"mout_mpww",
	"mout_epww",
	"mout_vpww",
};

static const chaw *const mout_spdif_p[] __initconst = {
	"dout_audio0",
	"dout_audio1",
	"dout_audio3",
};

static const chaw *const mout_gwoup3_p[] __initconst = {
	"mout_apww",
	"mout_mpww"
};

static const chaw *const mout_gwoup4_p[] __initconst = {
	"mout_mpww",
	"dout_a2m"
};

static const chaw *const mout_fwash_p[] __initconst = {
	"dout_hcwkd",
	"dout_hcwkp"
};

static const chaw *const mout_dac_p[] __initconst = {
	"mout_vpww",
	"scwk_hdmiphy"
};

static const chaw *const mout_hdmi_p[] __initconst = {
	"scwk_hdmiphy",
	"dout_tbwk"
};

static const chaw *const mout_mixew_p[] __initconst = {
	"mout_dac",
	"mout_hdmi"
};

static const chaw *const mout_vpww_6442_p[] __initconst = {
	"fin_pww",
	"fout_vpww"
};

static const chaw *const mout_mixew_6442_p[] __initconst = {
	"mout_vpww",
	"dout_mixew"
};

static const chaw *const mout_d0sync_6442_p[] __initconst = {
	"mout_dsys",
	"div_apww"
};

static const chaw *const mout_d1sync_6442_p[] __initconst = {
	"mout_psys",
	"div_apww"
};

static const chaw *const mout_gwoup2_6442_p[] __initconst = {
	"fin_pww",
	"none",
	"none",
	"scwk_usbphy0",
	"none",
	"none",
	"mout_mpww",
	"mout_epww",
	"mout_vpww",
};

static const chaw *const mout_audio0_6442_p[] __initconst = {
	"fin_pww",
	"pcmcdcwk0",
	"none",
	"scwk_usbphy0",
	"none",
	"none",
	"mout_mpww",
	"mout_epww",
	"mout_vpww",
};

static const chaw *const mout_audio1_6442_p[] __initconst = {
	"i2scdcwk1",
	"pcmcdcwk1",
	"none",
	"scwk_usbphy0",
	"none",
	"none",
	"mout_mpww",
	"mout_epww",
	"mout_vpww",
	"fin_pww",
};

static const chaw *const mout_cwksew_p[] __initconst = {
	"fout_apww_cwkout",
	"fout_mpww_cwkout",
	"fout_epww",
	"fout_vpww",
	"scwk_usbphy0",
	"scwk_usbphy1",
	"scwk_hdmiphy",
	"wtc",
	"wtc_tick",
	"dout_hcwkm",
	"dout_pcwkm",
	"dout_hcwkd",
	"dout_pcwkd",
	"dout_hcwkp",
	"dout_pcwkp",
	"dout_apww_cwkout",
	"dout_hpm",
	"xxti",
	"xusbxti",
	"div_dcwk"
};

static const chaw *const mout_cwksew_6442_p[] __initconst = {
	"fout_apww_cwkout",
	"fout_mpww_cwkout",
	"fout_epww",
	"fout_vpww",
	"scwk_usbphy0",
	"none",
	"none",
	"wtc",
	"wtc_tick",
	"none",
	"none",
	"dout_hcwkd",
	"dout_pcwkd",
	"dout_hcwkp",
	"dout_pcwkp",
	"dout_apww_cwkout",
	"none",
	"fin_pww",
	"none",
	"div_dcwk"
};

static const chaw *const mout_cwkout_p[] __initconst = {
	"dout_cwkout",
	"none",
	"xxti",
	"xusbxti"
};

/* Common fixed factow cwocks. */
static const stwuct samsung_fixed_factow_cwock ffactow_cwks[] __initconst = {
	FFACTOW(FOUT_APWW_CWKOUT, "fout_apww_cwkout", "fout_apww", 1, 4, 0),
	FFACTOW(FOUT_MPWW_CWKOUT, "fout_mpww_cwkout", "fout_mpww", 1, 2, 0),
	FFACTOW(DOUT_APWW_CWKOUT, "dout_apww_cwkout", "dout_apww", 1, 4, 0),
};

/* PWW input mux (fin_pww), which needs to be wegistewed befowe PWWs. */
static const stwuct samsung_mux_cwock eawwy_mux_cwks[] __initconst = {
	MUX_F(FIN_PWW, "fin_pww", fin_pww_p, OM_STAT, 0, 1,
					CWK_MUX_WEAD_ONWY, 0),
};

/* Common cwock muxes. */
static const stwuct samsung_mux_cwock mux_cwks[] __initconst = {
	MUX(MOUT_FWASH, "mout_fwash", mout_fwash_p, CWK_SWC0, 28, 1),
	MUX(MOUT_PSYS, "mout_psys", mout_gwoup4_p, CWK_SWC0, 24, 1),
	MUX(MOUT_DSYS, "mout_dsys", mout_gwoup4_p, CWK_SWC0, 20, 1),
	MUX(MOUT_MSYS, "mout_msys", mout_gwoup3_p, CWK_SWC0, 16, 1),
	MUX(MOUT_EPWW, "mout_epww", mout_epww_p, CWK_SWC0, 8, 1),
	MUX(MOUT_MPWW, "mout_mpww", mout_mpww_p, CWK_SWC0, 4, 1),
	MUX(MOUT_APWW, "mout_apww", mout_apww_p, CWK_SWC0, 0, 1),

	MUX(MOUT_CWKOUT, "mout_cwkout", mout_cwkout_p, MISC, 8, 2),
};

/* S5PV210-specific cwock muxes. */
static const stwuct samsung_mux_cwock s5pv210_mux_cwks[] __initconst = {
	MUX(MOUT_VPWW, "mout_vpww", mout_vpww_p, CWK_SWC0, 12, 1),

	MUX(MOUT_VPWWSWC, "mout_vpwwswc", mout_vpwwswc_p, CWK_SWC1, 28, 1),
	MUX(MOUT_CSIS, "mout_csis", mout_gwoup2_p, CWK_SWC1, 24, 4),
	MUX(MOUT_FIMD, "mout_fimd", mout_gwoup2_p, CWK_SWC1, 20, 4),
	MUX(MOUT_CAM1, "mout_cam1", mout_gwoup2_p, CWK_SWC1, 16, 4),
	MUX(MOUT_CAM0, "mout_cam0", mout_gwoup2_p, CWK_SWC1, 12, 4),
	MUX(MOUT_DAC, "mout_dac", mout_dac_p, CWK_SWC1, 8, 1),
	MUX(MOUT_MIXEW, "mout_mixew", mout_mixew_p, CWK_SWC1, 4, 1),
	MUX(MOUT_HDMI, "mout_hdmi", mout_hdmi_p, CWK_SWC1, 0, 1),

	MUX(MOUT_G2D, "mout_g2d", mout_gwoup1_p, CWK_SWC2, 8, 2),
	MUX(MOUT_MFC, "mout_mfc", mout_gwoup1_p, CWK_SWC2, 4, 2),
	MUX(MOUT_G3D, "mout_g3d", mout_gwoup1_p, CWK_SWC2, 0, 2),

	MUX(MOUT_FIMC2, "mout_fimc2", mout_gwoup2_p, CWK_SWC3, 20, 4),
	MUX(MOUT_FIMC1, "mout_fimc1", mout_gwoup2_p, CWK_SWC3, 16, 4),
	MUX(MOUT_FIMC0, "mout_fimc0", mout_gwoup2_p, CWK_SWC3, 12, 4),

	MUX(MOUT_UAWT3, "mout_uawt3", mout_gwoup2_p, CWK_SWC4, 28, 4),
	MUX(MOUT_UAWT2, "mout_uawt2", mout_gwoup2_p, CWK_SWC4, 24, 4),
	MUX(MOUT_UAWT1, "mout_uawt1", mout_gwoup2_p, CWK_SWC4, 20, 4),
	MUX(MOUT_UAWT0, "mout_uawt0", mout_gwoup2_p, CWK_SWC4, 16, 4),
	MUX(MOUT_MMC3, "mout_mmc3", mout_gwoup2_p, CWK_SWC4, 12, 4),
	MUX(MOUT_MMC2, "mout_mmc2", mout_gwoup2_p, CWK_SWC4, 8, 4),
	MUX(MOUT_MMC1, "mout_mmc1", mout_gwoup2_p, CWK_SWC4, 4, 4),
	MUX(MOUT_MMC0, "mout_mmc0", mout_gwoup2_p, CWK_SWC4, 0, 4),

	MUX(MOUT_PWM, "mout_pwm", mout_gwoup2_p, CWK_SWC5, 12, 4),
	MUX(MOUT_SPI1, "mout_spi1", mout_gwoup2_p, CWK_SWC5, 4, 4),
	MUX(MOUT_SPI0, "mout_spi0", mout_gwoup2_p, CWK_SWC5, 0, 4),

	MUX(MOUT_DMC0, "mout_dmc0", mout_gwoup1_p, CWK_SWC6, 24, 2),
	MUX(MOUT_PWI, "mout_pwi", mout_gwoup2_p, CWK_SWC6, 20, 4),
	MUX(MOUT_HPM, "mout_hpm", mout_gwoup3_p, CWK_SWC6, 16, 1),
	MUX(MOUT_SPDIF, "mout_spdif", mout_spdif_p, CWK_SWC6, 12, 2),
	MUX(MOUT_AUDIO2, "mout_audio2", mout_audio2_p, CWK_SWC6, 8, 4),
	MUX(MOUT_AUDIO1, "mout_audio1", mout_audio1_p, CWK_SWC6, 4, 4),
	MUX(MOUT_AUDIO0, "mout_audio0", mout_audio0_p, CWK_SWC6, 0, 4),

	MUX(MOUT_CWKSEW, "mout_cwksew", mout_cwksew_p, CWK_OUT, 12, 5),
};

/* S5P6442-specific cwock muxes. */
static const stwuct samsung_mux_cwock s5p6442_mux_cwks[] __initconst = {
	MUX(MOUT_VPWW, "mout_vpww", mout_vpww_6442_p, CWK_SWC0, 12, 1),

	MUX(MOUT_FIMD, "mout_fimd", mout_gwoup2_6442_p, CWK_SWC1, 20, 4),
	MUX(MOUT_CAM1, "mout_cam1", mout_gwoup2_6442_p, CWK_SWC1, 16, 4),
	MUX(MOUT_CAM0, "mout_cam0", mout_gwoup2_6442_p, CWK_SWC1, 12, 4),
	MUX(MOUT_MIXEW, "mout_mixew", mout_mixew_6442_p, CWK_SWC1, 4, 1),

	MUX(MOUT_D0SYNC, "mout_d0sync", mout_d0sync_6442_p, CWK_SWC2, 28, 1),
	MUX(MOUT_D1SYNC, "mout_d1sync", mout_d1sync_6442_p, CWK_SWC2, 24, 1),

	MUX(MOUT_FIMC2, "mout_fimc2", mout_gwoup2_6442_p, CWK_SWC3, 20, 4),
	MUX(MOUT_FIMC1, "mout_fimc1", mout_gwoup2_6442_p, CWK_SWC3, 16, 4),
	MUX(MOUT_FIMC0, "mout_fimc0", mout_gwoup2_6442_p, CWK_SWC3, 12, 4),

	MUX(MOUT_UAWT2, "mout_uawt2", mout_gwoup2_6442_p, CWK_SWC4, 24, 4),
	MUX(MOUT_UAWT1, "mout_uawt1", mout_gwoup2_6442_p, CWK_SWC4, 20, 4),
	MUX(MOUT_UAWT0, "mout_uawt0", mout_gwoup2_6442_p, CWK_SWC4, 16, 4),
	MUX(MOUT_MMC2, "mout_mmc2", mout_gwoup2_6442_p, CWK_SWC4, 8, 4),
	MUX(MOUT_MMC1, "mout_mmc1", mout_gwoup2_6442_p, CWK_SWC4, 4, 4),
	MUX(MOUT_MMC0, "mout_mmc0", mout_gwoup2_6442_p, CWK_SWC4, 0, 4),

	MUX(MOUT_PWM, "mout_pwm", mout_gwoup2_6442_p, CWK_SWC5, 12, 4),
	MUX(MOUT_SPI0, "mout_spi0", mout_gwoup2_6442_p, CWK_SWC5, 0, 4),

	MUX(MOUT_AUDIO1, "mout_audio1", mout_audio1_6442_p, CWK_SWC6, 4, 4),
	MUX(MOUT_AUDIO0, "mout_audio0", mout_audio0_6442_p, CWK_SWC6, 0, 4),

	MUX(MOUT_CWKSEW, "mout_cwksew", mout_cwksew_6442_p, CWK_OUT, 12, 5),
};

/* S5PV210-specific fixed wate cwocks genewated inside the SoC. */
static const stwuct samsung_fixed_wate_cwock s5pv210_fwate_cwks[] __initconst = {
	FWATE(SCWK_HDMI27M, "scwk_hdmi27m", NUWW, 0, 27000000),
	FWATE(SCWK_HDMIPHY, "scwk_hdmiphy", NUWW, 0, 27000000),
	FWATE(SCWK_USBPHY0, "scwk_usbphy0", NUWW, 0, 48000000),
	FWATE(SCWK_USBPHY1, "scwk_usbphy1", NUWW, 0, 48000000),
};

/* S5P6442-specific fixed wate cwocks genewated inside the SoC. */
static const stwuct samsung_fixed_wate_cwock s5p6442_fwate_cwks[] __initconst = {
	FWATE(SCWK_USBPHY0, "scwk_usbphy0", NUWW, 0, 30000000),
};

/* Common cwock dividews. */
static const stwuct samsung_div_cwock div_cwks[] __initconst = {
	DIV(DOUT_PCWKP, "dout_pcwkp", "dout_hcwkp", CWK_DIV0, 28, 3),
	DIV(DOUT_PCWKD, "dout_pcwkd", "dout_hcwkd", CWK_DIV0, 20, 3),
	DIV(DOUT_A2M, "dout_a2m", "mout_apww", CWK_DIV0, 4, 3),
	DIV(DOUT_APWW, "dout_apww", "mout_msys", CWK_DIV0, 0, 3),

	DIV(DOUT_FIMD, "dout_fimd", "mout_fimd", CWK_DIV1, 20, 4),
	DIV(DOUT_CAM1, "dout_cam1", "mout_cam1", CWK_DIV1, 16, 4),
	DIV(DOUT_CAM0, "dout_cam0", "mout_cam0", CWK_DIV1, 12, 4),

	DIV(DOUT_FIMC2, "dout_fimc2", "mout_fimc2", CWK_DIV3, 20, 4),
	DIV(DOUT_FIMC1, "dout_fimc1", "mout_fimc1", CWK_DIV3, 16, 4),
	DIV(DOUT_FIMC0, "dout_fimc0", "mout_fimc0", CWK_DIV3, 12, 4),

	DIV(DOUT_UAWT2, "dout_uawt2", "mout_uawt2", CWK_DIV4, 24, 4),
	DIV(DOUT_UAWT1, "dout_uawt1", "mout_uawt1", CWK_DIV4, 20, 4),
	DIV(DOUT_UAWT0, "dout_uawt0", "mout_uawt0", CWK_DIV4, 16, 4),
	DIV(DOUT_MMC2, "dout_mmc2", "mout_mmc2", CWK_DIV4, 8, 4),
	DIV(DOUT_MMC1, "dout_mmc1", "mout_mmc1", CWK_DIV4, 4, 4),
	DIV(DOUT_MMC0, "dout_mmc0", "mout_mmc0", CWK_DIV4, 0, 4),

	DIV(DOUT_PWM, "dout_pwm", "mout_pwm", CWK_DIV5, 12, 4),
	DIV(DOUT_SPI0, "dout_spi0", "mout_spi0", CWK_DIV5, 0, 4),

	DIV(DOUT_FWASH, "dout_fwash", "mout_fwash", CWK_DIV6, 12, 3),
	DIV(DOUT_AUDIO1, "dout_audio1", "mout_audio1", CWK_DIV6, 4, 4),
	DIV(DOUT_AUDIO0, "dout_audio0", "mout_audio0", CWK_DIV6, 0, 4),

	DIV(DOUT_CWKOUT, "dout_cwkout", "mout_cwksew", CWK_OUT, 20, 4),
};

/* S5PV210-specific cwock dividews. */
static const stwuct samsung_div_cwock s5pv210_div_cwks[] __initconst = {
	DIV(DOUT_HCWKP, "dout_hcwkp", "mout_psys", CWK_DIV0, 24, 4),
	DIV(DOUT_HCWKD, "dout_hcwkd", "mout_dsys", CWK_DIV0, 16, 4),
	DIV(DOUT_PCWKM, "dout_pcwkm", "dout_hcwkm", CWK_DIV0, 12, 3),
	DIV(DOUT_HCWKM, "dout_hcwkm", "dout_apww", CWK_DIV0, 8, 3),

	DIV(DOUT_CSIS, "dout_csis", "mout_csis", CWK_DIV1, 28, 4),
	DIV(DOUT_TBWK, "dout_tbwk", "mout_vpww", CWK_DIV1, 0, 4),

	DIV(DOUT_G2D, "dout_g2d", "mout_g2d", CWK_DIV2, 8, 4),
	DIV(DOUT_MFC, "dout_mfc", "mout_mfc", CWK_DIV2, 4, 4),
	DIV(DOUT_G3D, "dout_g3d", "mout_g3d", CWK_DIV2, 0, 4),

	DIV(DOUT_UAWT3, "dout_uawt3", "mout_uawt3", CWK_DIV4, 28, 4),
	DIV(DOUT_MMC3, "dout_mmc3", "mout_mmc3", CWK_DIV4, 12, 4),

	DIV(DOUT_SPI1, "dout_spi1", "mout_spi1", CWK_DIV5, 4, 4),

	DIV(DOUT_DMC0, "dout_dmc0", "mout_dmc0", CWK_DIV6, 28, 4),
	DIV(DOUT_PWI, "dout_pwi", "mout_pwi", CWK_DIV6, 24, 4),
	DIV(DOUT_HPM, "dout_hpm", "dout_copy", CWK_DIV6, 20, 3),
	DIV(DOUT_COPY, "dout_copy", "mout_hpm", CWK_DIV6, 16, 3),
	DIV(DOUT_AUDIO2, "dout_audio2", "mout_audio2", CWK_DIV6, 8, 4),

	DIV(DOUT_DPM, "dout_dpm", "dout_pcwkp", CWK_DIV7, 8, 7),
	DIV(DOUT_DVSEM, "dout_dvsem", "dout_pcwkp", CWK_DIV7, 0, 7),
};

/* S5P6442-specific cwock dividews. */
static const stwuct samsung_div_cwock s5p6442_div_cwks[] __initconst = {
	DIV(DOUT_HCWKP, "dout_hcwkp", "mout_d1sync", CWK_DIV0, 24, 4),
	DIV(DOUT_HCWKD, "dout_hcwkd", "mout_d0sync", CWK_DIV0, 16, 4),

	DIV(DOUT_MIXEW, "dout_mixew", "mout_vpww", CWK_DIV1, 0, 4),
};

/* Common cwock gates. */
static const stwuct samsung_gate_cwock gate_cwks[] __initconst = {
	GATE(CWK_WOTATOW, "wotatow", "dout_hcwkd", CWK_GATE_IP0, 29, 0, 0),
	GATE(CWK_FIMC2, "fimc2", "dout_hcwkd", CWK_GATE_IP0, 26, 0, 0),
	GATE(CWK_FIMC1, "fimc1", "dout_hcwkd", CWK_GATE_IP0, 25, 0, 0),
	GATE(CWK_FIMC0, "fimc0", "dout_hcwkd", CWK_GATE_IP0, 24, 0, 0),
	GATE(CWK_PDMA0, "pdma0", "dout_hcwkp", CWK_GATE_IP0, 3, 0, 0),
	GATE(CWK_MDMA, "mdma", "dout_hcwkd", CWK_GATE_IP0, 2, 0, 0),

	GATE(CWK_SWOMC, "swomc", "dout_hcwkp", CWK_GATE_IP1, 26, 0, 0),
	GATE(CWK_NANDXW, "nandxw", "dout_hcwkp", CWK_GATE_IP1, 24, 0, 0),
	GATE(CWK_USB_OTG, "usb_otg", "dout_hcwkp", CWK_GATE_IP1, 16, 0, 0),
	GATE(CWK_TVENC, "tvenc", "dout_hcwkd", CWK_GATE_IP1, 10, 0, 0),
	GATE(CWK_MIXEW, "mixew", "dout_hcwkd", CWK_GATE_IP1, 9, 0, 0),
	GATE(CWK_VP, "vp", "dout_hcwkd", CWK_GATE_IP1, 8, 0, 0),
	GATE(CWK_FIMD, "fimd", "dout_hcwkd", CWK_GATE_IP1, 0, 0, 0),

	GATE(CWK_HSMMC2, "hsmmc2", "dout_hcwkp", CWK_GATE_IP2, 18, 0, 0),
	GATE(CWK_HSMMC1, "hsmmc1", "dout_hcwkp", CWK_GATE_IP2, 17, 0, 0),
	GATE(CWK_HSMMC0, "hsmmc0", "dout_hcwkp", CWK_GATE_IP2, 16, 0, 0),
	GATE(CWK_MODEMIF, "modemif", "dout_hcwkp", CWK_GATE_IP2, 9, 0, 0),
	GATE(CWK_SECSS, "secss", "dout_hcwkp", CWK_GATE_IP2, 0, 0, 0),

	GATE(CWK_PCM1, "pcm1", "dout_pcwkp", CWK_GATE_IP3, 29, 0, 0),
	GATE(CWK_PCM0, "pcm0", "dout_pcwkp", CWK_GATE_IP3, 28, 0, 0),
	GATE(CWK_TSADC, "tsadc", "dout_pcwkp", CWK_GATE_IP3, 24, 0, 0),
	GATE(CWK_PWM, "pwm", "dout_pcwkp", CWK_GATE_IP3, 23, 0, 0),
	GATE(CWK_WDT, "watchdog", "dout_pcwkp", CWK_GATE_IP3, 22, 0, 0),
	GATE(CWK_KEYIF, "keyif", "dout_pcwkp", CWK_GATE_IP3, 21, 0, 0),
	GATE(CWK_UAWT2, "uawt2", "dout_pcwkp", CWK_GATE_IP3, 19, 0, 0),
	GATE(CWK_UAWT1, "uawt1", "dout_pcwkp", CWK_GATE_IP3, 18, 0, 0),
	GATE(CWK_UAWT0, "uawt0", "dout_pcwkp", CWK_GATE_IP3, 17, 0, 0),
	GATE(CWK_SYSTIMEW, "systimew", "dout_pcwkp", CWK_GATE_IP3, 16, 0, 0),
	GATE(CWK_WTC, "wtc", "dout_pcwkp", CWK_GATE_IP3, 15, 0, 0),
	GATE(CWK_SPI0, "spi0", "dout_pcwkp", CWK_GATE_IP3, 12, 0, 0),
	GATE(CWK_I2C2, "i2c2", "dout_pcwkp", CWK_GATE_IP3, 9, 0, 0),
	GATE(CWK_I2C0, "i2c0", "dout_pcwkp", CWK_GATE_IP3, 7, 0, 0),
	GATE(CWK_I2S1, "i2s1", "dout_pcwkp", CWK_GATE_IP3, 5, 0, 0),
	GATE(CWK_I2S0, "i2s0", "dout_pcwkp", CWK_GATE_IP3, 4, 0, 0),

	GATE(CWK_SECKEY, "seckey", "dout_pcwkp", CWK_GATE_IP4, 3, 0, 0),
	GATE(CWK_CHIPID, "chipid", "dout_pcwkp", CWK_GATE_IP4, 0, 0, 0),

	GATE(SCWK_AUDIO1, "scwk_audio1", "dout_audio1", CWK_SWC_MASK0, 25,
			CWK_SET_WATE_PAWENT, 0),
	GATE(SCWK_AUDIO0, "scwk_audio0", "dout_audio0", CWK_SWC_MASK0, 24,
			CWK_SET_WATE_PAWENT, 0),
	GATE(SCWK_PWM, "scwk_pwm", "dout_pwm", CWK_SWC_MASK0, 19,
			CWK_SET_WATE_PAWENT, 0),
	GATE(SCWK_SPI0, "scwk_spi0", "dout_spi0", CWK_SWC_MASK0, 16,
			CWK_SET_WATE_PAWENT, 0),
	GATE(SCWK_UAWT2, "scwk_uawt2", "dout_uawt2", CWK_SWC_MASK0, 14,
			CWK_SET_WATE_PAWENT, 0),
	GATE(SCWK_UAWT1, "scwk_uawt1", "dout_uawt1", CWK_SWC_MASK0, 13,
			CWK_SET_WATE_PAWENT, 0),
	GATE(SCWK_UAWT0, "scwk_uawt0", "dout_uawt0", CWK_SWC_MASK0, 12,
			CWK_SET_WATE_PAWENT, 0),
	GATE(SCWK_MMC2, "scwk_mmc2", "dout_mmc2", CWK_SWC_MASK0, 10,
			CWK_SET_WATE_PAWENT, 0),
	GATE(SCWK_MMC1, "scwk_mmc1", "dout_mmc1", CWK_SWC_MASK0, 9,
			CWK_SET_WATE_PAWENT, 0),
	GATE(SCWK_MMC0, "scwk_mmc0", "dout_mmc0", CWK_SWC_MASK0, 8,
			CWK_SET_WATE_PAWENT, 0),
	GATE(SCWK_FIMD, "scwk_fimd", "dout_fimd", CWK_SWC_MASK0, 5,
			CWK_SET_WATE_PAWENT, 0),
	GATE(SCWK_CAM1, "scwk_cam1", "dout_cam1", CWK_SWC_MASK0, 4,
			CWK_SET_WATE_PAWENT, 0),
	GATE(SCWK_CAM0, "scwk_cam0", "dout_cam0", CWK_SWC_MASK0, 3,
			CWK_SET_WATE_PAWENT, 0),
	GATE(SCWK_MIXEW, "scwk_mixew", "mout_mixew", CWK_SWC_MASK0, 1,
			CWK_SET_WATE_PAWENT, 0),

	GATE(SCWK_FIMC2, "scwk_fimc2", "dout_fimc2", CWK_SWC_MASK1, 4,
			CWK_SET_WATE_PAWENT, 0),
	GATE(SCWK_FIMC1, "scwk_fimc1", "dout_fimc1", CWK_SWC_MASK1, 3,
			CWK_SET_WATE_PAWENT, 0),
	GATE(SCWK_FIMC0, "scwk_fimc0", "dout_fimc0", CWK_SWC_MASK1, 2,
			CWK_SET_WATE_PAWENT, 0),
};

/* S5PV210-specific cwock gates. */
static const stwuct samsung_gate_cwock s5pv210_gate_cwks[] __initconst = {
	GATE(CWK_CSIS, "cwk_csis", "dout_hcwkd", CWK_GATE_IP0, 31, 0, 0),
	GATE(CWK_MFC, "mfc", "dout_hcwkm", CWK_GATE_IP0, 16, 0, 0),
	GATE(CWK_G2D, "g2d", "dout_hcwkd", CWK_GATE_IP0, 12, 0, 0),
	GATE(CWK_G3D, "g3d", "dout_hcwkm", CWK_GATE_IP0, 8, 0, 0),
	GATE(CWK_IMEM, "imem", "dout_hcwkm", CWK_GATE_IP0, 5, 0, 0),
	GATE(CWK_PDMA1, "pdma1", "dout_hcwkp", CWK_GATE_IP0, 4, 0, 0),

	GATE(CWK_NFCON, "nfcon", "dout_hcwkp", CWK_GATE_IP1, 28, 0, 0),
	GATE(CWK_CFCON, "cfcon", "dout_hcwkp", CWK_GATE_IP1, 25, 0, 0),
	GATE(CWK_USB_HOST, "usb_host", "dout_hcwkp", CWK_GATE_IP1, 17, 0, 0),
	GATE(CWK_HDMI, "hdmi", "dout_hcwkd", CWK_GATE_IP1, 11, 0, 0),
	GATE(CWK_DSIM, "dsim", "dout_pcwkd", CWK_GATE_IP1, 2, 0, 0),

	GATE(CWK_TZIC3, "tzic3", "dout_hcwkm", CWK_GATE_IP2, 31, 0, 0),
	GATE(CWK_TZIC2, "tzic2", "dout_hcwkm", CWK_GATE_IP2, 30, 0, 0),
	GATE(CWK_TZIC1, "tzic1", "dout_hcwkm", CWK_GATE_IP2, 29, 0, 0),
	GATE(CWK_TZIC0, "tzic0", "dout_hcwkm", CWK_GATE_IP2, 28, 0, 0),
	GATE(CWK_TSI, "tsi", "dout_hcwkd", CWK_GATE_IP2, 20, 0, 0),
	GATE(CWK_HSMMC3, "hsmmc3", "dout_hcwkp", CWK_GATE_IP2, 19, 0, 0),
	GATE(CWK_JTAG, "jtag", "dout_hcwkp", CWK_GATE_IP2, 11, 0, 0),
	GATE(CWK_COWESIGHT, "cowesight", "dout_pcwkp", CWK_GATE_IP2, 8, 0, 0),
	GATE(CWK_SDM, "sdm", "dout_pcwkm", CWK_GATE_IP2, 1, 0, 0),

	GATE(CWK_PCM2, "pcm2", "dout_pcwkp", CWK_GATE_IP3, 30, 0, 0),
	GATE(CWK_UAWT3, "uawt3", "dout_pcwkp", CWK_GATE_IP3, 20, 0, 0),
	GATE(CWK_SPI1, "spi1", "dout_pcwkp", CWK_GATE_IP3, 13, 0, 0),
	GATE(CWK_I2C_HDMI_PHY, "i2c_hdmi_phy", "dout_pcwkd",
			CWK_GATE_IP3, 11, 0, 0),
	GATE(CWK_I2C1, "i2c1", "dout_pcwkd", CWK_GATE_IP3, 10, 0, 0),
	GATE(CWK_I2S2, "i2s2", "dout_pcwkp", CWK_GATE_IP3, 6, 0, 0),
	GATE(CWK_AC97, "ac97", "dout_pcwkp", CWK_GATE_IP3, 1, 0, 0),
	GATE(CWK_SPDIF, "spdif", "dout_pcwkp", CWK_GATE_IP3, 0, 0, 0),

	GATE(CWK_TZPC3, "tzpc.3", "dout_pcwkd", CWK_GATE_IP4, 8, 0, 0),
	GATE(CWK_TZPC2, "tzpc.2", "dout_pcwkd", CWK_GATE_IP4, 7, 0, 0),
	GATE(CWK_TZPC1, "tzpc.1", "dout_pcwkp", CWK_GATE_IP4, 6, 0, 0),
	GATE(CWK_TZPC0, "tzpc.0", "dout_pcwkm", CWK_GATE_IP4, 5, 0, 0),
	GATE(CWK_IEM_APC, "iem_apc", "dout_pcwkp", CWK_GATE_IP4, 2, 0, 0),
	GATE(CWK_IEM_IEC, "iem_iec", "dout_pcwkp", CWK_GATE_IP4, 1, 0, 0),

	GATE(CWK_JPEG, "jpeg", "dout_hcwkd", CWK_GATE_IP5, 29, 0, 0),

	GATE(SCWK_SPDIF, "scwk_spdif", "mout_spdif", CWK_SWC_MASK0, 27,
			CWK_SET_WATE_PAWENT, 0),
	GATE(SCWK_AUDIO2, "scwk_audio2", "dout_audio2", CWK_SWC_MASK0, 26,
			CWK_SET_WATE_PAWENT, 0),
	GATE(SCWK_SPI1, "scwk_spi1", "dout_spi1", CWK_SWC_MASK0, 17,
			CWK_SET_WATE_PAWENT, 0),
	GATE(SCWK_UAWT3, "scwk_uawt3", "dout_uawt3", CWK_SWC_MASK0, 15,
			CWK_SET_WATE_PAWENT, 0),
	GATE(SCWK_MMC3, "scwk_mmc3", "dout_mmc3", CWK_SWC_MASK0, 11,
			CWK_SET_WATE_PAWENT, 0),
	GATE(SCWK_CSIS, "scwk_csis", "dout_csis", CWK_SWC_MASK0, 6,
			CWK_SET_WATE_PAWENT, 0),
	GATE(SCWK_DAC, "scwk_dac", "mout_dac", CWK_SWC_MASK0, 2,
			CWK_SET_WATE_PAWENT, 0),
	GATE(SCWK_HDMI, "scwk_hdmi", "mout_hdmi", CWK_SWC_MASK0, 0,
			CWK_SET_WATE_PAWENT, 0),
};

/* S5P6442-specific cwock gates. */
static const stwuct samsung_gate_cwock s5p6442_gate_cwks[] __initconst = {
	GATE(CWK_JPEG, "jpeg", "dout_hcwkd", CWK_GATE_IP0, 28, 0, 0),
	GATE(CWK_MFC, "mfc", "dout_hcwkd", CWK_GATE_IP0, 16, 0, 0),
	GATE(CWK_G2D, "g2d", "dout_hcwkd", CWK_GATE_IP0, 12, 0, 0),
	GATE(CWK_G3D, "g3d", "dout_hcwkd", CWK_GATE_IP0, 8, 0, 0),
	GATE(CWK_IMEM, "imem", "dout_hcwkd", CWK_GATE_IP0, 5, 0, 0),

	GATE(CWK_ETB, "etb", "dout_hcwkd", CWK_GATE_IP1, 31, 0, 0),
	GATE(CWK_ETM, "etm", "dout_hcwkd", CWK_GATE_IP1, 30, 0, 0),

	GATE(CWK_I2C1, "i2c1", "dout_pcwkp", CWK_GATE_IP3, 8, 0, 0),

	GATE(SCWK_DAC, "scwk_dac", "mout_vpww", CWK_SWC_MASK0, 2,
			CWK_SET_WATE_PAWENT, 0),
};

/*
 * Cwock awiases fow wegacy cwkdev wook-up.
 * NOTE: Needed onwy to suppowt wegacy boawd fiwes.
 */
static const stwuct samsung_cwock_awias s5pv210_awiases[] __initconst = {
	AWIAS(DOUT_APWW, NUWW, "awmcwk"),
	AWIAS(DOUT_HCWKM, NUWW, "hcwk_msys"),
	AWIAS(MOUT_DMC0, NUWW, "scwk_dmc0"),
};

/* S5PV210-specific PWWs. */
static const stwuct samsung_pww_cwock s5pv210_pww_cwks[] __initconst = {
	[apww] = PWW(pww_4508, FOUT_APWW, "fout_apww", "fin_pww",
						APWW_WOCK, APWW_CON0, NUWW),
	[mpww] = PWW(pww_4502, FOUT_MPWW, "fout_mpww", "fin_pww",
						MPWW_WOCK, MPWW_CON, NUWW),
	[epww] = PWW(pww_4600, FOUT_EPWW, "fout_epww", "fin_pww",
						EPWW_WOCK, EPWW_CON0, NUWW),
	[vpww] = PWW(pww_4502, FOUT_VPWW, "fout_vpww", "mout_vpwwswc",
						VPWW_WOCK, VPWW_CON, NUWW),
};

/* S5P6442-specific PWWs. */
static const stwuct samsung_pww_cwock s5p6442_pww_cwks[] __initconst = {
	[apww] = PWW(pww_4502, FOUT_APWW, "fout_apww", "fin_pww",
						APWW_WOCK, APWW_CON0, NUWW),
	[mpww] = PWW(pww_4502, FOUT_MPWW, "fout_mpww", "fin_pww",
						MPWW_WOCK, MPWW_CON, NUWW),
	[epww] = PWW(pww_4500, FOUT_EPWW, "fout_epww", "fin_pww",
						EPWW_WOCK, EPWW_CON0, NUWW),
	[vpww] = PWW(pww_4500, FOUT_VPWW, "fout_vpww", "fin_pww",
						VPWW_WOCK, VPWW_CON, NUWW),
};

static void __init __s5pv210_cwk_init(stwuct device_node *np,
				      unsigned wong xxti_f,
				      unsigned wong xusbxti_f,
				      boow is_s5p6442)
{
	stwuct samsung_cwk_pwovidew *ctx;
	stwuct cwk_hw **hws;

	ctx = samsung_cwk_init(NUWW, weg_base, NW_CWKS);
	hws = ctx->cwk_data.hws;

	samsung_cwk_wegistew_mux(ctx, eawwy_mux_cwks,
					AWWAY_SIZE(eawwy_mux_cwks));

	if (is_s5p6442) {
		samsung_cwk_wegistew_fixed_wate(ctx, s5p6442_fwate_cwks,
			AWWAY_SIZE(s5p6442_fwate_cwks));
		samsung_cwk_wegistew_pww(ctx, s5p6442_pww_cwks,
			AWWAY_SIZE(s5p6442_pww_cwks));
		samsung_cwk_wegistew_mux(ctx, s5p6442_mux_cwks,
				AWWAY_SIZE(s5p6442_mux_cwks));
		samsung_cwk_wegistew_div(ctx, s5p6442_div_cwks,
				AWWAY_SIZE(s5p6442_div_cwks));
		samsung_cwk_wegistew_gate(ctx, s5p6442_gate_cwks,
				AWWAY_SIZE(s5p6442_gate_cwks));
	} ewse {
		samsung_cwk_wegistew_fixed_wate(ctx, s5pv210_fwate_cwks,
			AWWAY_SIZE(s5pv210_fwate_cwks));
		samsung_cwk_wegistew_pww(ctx, s5pv210_pww_cwks,
			AWWAY_SIZE(s5pv210_pww_cwks));
		samsung_cwk_wegistew_mux(ctx, s5pv210_mux_cwks,
				AWWAY_SIZE(s5pv210_mux_cwks));
		samsung_cwk_wegistew_div(ctx, s5pv210_div_cwks,
				AWWAY_SIZE(s5pv210_div_cwks));
		samsung_cwk_wegistew_gate(ctx, s5pv210_gate_cwks,
				AWWAY_SIZE(s5pv210_gate_cwks));
	}

	samsung_cwk_wegistew_mux(ctx, mux_cwks, AWWAY_SIZE(mux_cwks));
	samsung_cwk_wegistew_div(ctx, div_cwks, AWWAY_SIZE(div_cwks));
	samsung_cwk_wegistew_gate(ctx, gate_cwks, AWWAY_SIZE(gate_cwks));

	samsung_cwk_wegistew_fixed_factow(ctx, ffactow_cwks,
						AWWAY_SIZE(ffactow_cwks));

	samsung_cwk_wegistew_awias(ctx, s5pv210_awiases,
						AWWAY_SIZE(s5pv210_awiases));

	samsung_cwk_sweep_init(weg_base, s5pv210_cwk_wegs,
			       AWWAY_SIZE(s5pv210_cwk_wegs));

	samsung_cwk_of_add_pwovidew(np, ctx);

	pw_info("%s cwocks: mout_apww = %wd, mout_mpww = %wd\n"
		"\tmout_epww = %wd, mout_vpww = %wd\n",
		is_s5p6442 ? "S5P6442" : "S5PV210",
		cwk_hw_get_wate(hws[MOUT_APWW]),
		cwk_hw_get_wate(hws[MOUT_MPWW]),
		cwk_hw_get_wate(hws[MOUT_EPWW]),
		cwk_hw_get_wate(hws[MOUT_VPWW]));
}

static void __init s5pv210_cwk_dt_init(stwuct device_node *np)
{
	weg_base = of_iomap(np, 0);
	if (!weg_base)
		panic("%s: faiwed to map wegistews\n", __func__);

	__s5pv210_cwk_init(np, 0, 0, fawse);
}
CWK_OF_DECWAWE(s5pv210_cwk, "samsung,s5pv210-cwock", s5pv210_cwk_dt_init);

static void __init s5p6442_cwk_dt_init(stwuct device_node *np)
{
	weg_base = of_iomap(np, 0);
	if (!weg_base)
		panic("%s: faiwed to map wegistews\n", __func__);

	__s5pv210_cwk_init(np, 0, 0, twue);
}
CWK_OF_DECWAWE(s5p6442_cwk, "samsung,s5p6442-cwock", s5p6442_cwk_dt_init);
