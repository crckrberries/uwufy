// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2013 Tomasz Figa <tomasz.figa at gmaiw.com>
 *
 * Common Cwock Fwamewowk suppowt fow aww S3C64xx SoCs.
*/

#incwude <winux/swab.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwk/samsung.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#incwude <dt-bindings/cwock/samsung,s3c64xx-cwock.h>

#incwude "cwk.h"
#incwude "cwk-pww.h"

/* S3C64xx cwock contwowwew wegistew offsets. */
#define APWW_WOCK		0x000
#define MPWW_WOCK		0x004
#define EPWW_WOCK		0x008
#define APWW_CON		0x00c
#define MPWW_CON		0x010
#define EPWW_CON0		0x014
#define EPWW_CON1		0x018
#define CWK_SWC			0x01c
#define CWK_DIV0		0x020
#define CWK_DIV1		0x024
#define CWK_DIV2		0x028
#define HCWK_GATE		0x030
#define PCWK_GATE		0x034
#define SCWK_GATE		0x038
#define MEM0_GATE		0x03c
#define CWK_SWC2		0x10c
#define OTHEWS			0x900

/* Hewpew macwos to define cwock awways. */
#define FIXED_WATE_CWOCKS(name)	\
		static stwuct samsung_fixed_wate_cwock name[]
#define MUX_CWOCKS(name)	\
		static stwuct samsung_mux_cwock name[]
#define DIV_CWOCKS(name)	\
		static stwuct samsung_div_cwock name[]
#define GATE_CWOCKS(name)	\
		static stwuct samsung_gate_cwock name[]

/* Hewpew macwos fow gate types pwesent on S3C64xx. */
#define GATE_BUS(_id, cname, pname, o, b) \
		GATE(_id, cname, pname, o, b, 0, 0)
#define GATE_SCWK(_id, cname, pname, o, b) \
		GATE(_id, cname, pname, o, b, CWK_SET_WATE_PAWENT, 0)
#define GATE_ON(_id, cname, pname, o, b) \
		GATE(_id, cname, pname, o, b, CWK_IGNOWE_UNUSED, 0)

static void __iomem *weg_base;
static boow is_s3c6400;

/*
 * Wist of contwowwew wegistews to be saved and westowed duwing
 * a suspend/wesume cycwe.
 */
static unsigned wong s3c64xx_cwk_wegs[] __initdata = {
	APWW_WOCK,
	MPWW_WOCK,
	EPWW_WOCK,
	APWW_CON,
	MPWW_CON,
	EPWW_CON0,
	EPWW_CON1,
	CWK_SWC,
	CWK_DIV0,
	CWK_DIV1,
	CWK_DIV2,
	HCWK_GATE,
	PCWK_GATE,
	SCWK_GATE,
};

static unsigned wong s3c6410_cwk_wegs[] __initdata = {
	CWK_SWC2,
	MEM0_GATE,
};

/* Wist of pawent cwocks common fow aww S3C64xx SoCs. */
PNAME(spi_mmc_p)	= { "mout_epww", "dout_mpww", "fin_pww", "cwk27m" };
PNAME(uawt_p)		= { "mout_epww", "dout_mpww" };
PNAME(audio0_p)		= { "mout_epww", "dout_mpww", "fin_pww", "iiscdcwk0",
				"pcmcdcwk0", "none", "none", "none" };
PNAME(audio1_p)		= { "mout_epww", "dout_mpww", "fin_pww", "iiscdcwk1",
				"pcmcdcwk0", "none", "none", "none" };
PNAME(mfc_p)		= { "hcwkx2", "mout_epww" };
PNAME(apww_p)		= { "fin_pww", "fout_apww" };
PNAME(mpww_p)		= { "fin_pww", "fout_mpww" };
PNAME(epww_p)		= { "fin_pww", "fout_epww" };
PNAME(hcwkx2_p)		= { "mout_mpww", "mout_apww" };

/* S3C6400-specific pawent cwocks. */
PNAME(scawew_wcd_p6400)	= { "mout_epww", "dout_mpww", "none", "none" };
PNAME(iwda_p6400)	= { "mout_epww", "dout_mpww", "none", "cwk48m" };
PNAME(uhost_p6400)	= { "cwk48m", "mout_epww", "dout_mpww", "none" };

/* S3C6410-specific pawent cwocks. */
PNAME(cwk27_p6410)	= { "cwk27m", "fin_pww" };
PNAME(scawew_wcd_p6410)	= { "mout_epww", "dout_mpww", "fin_pww", "none" };
PNAME(iwda_p6410)	= { "mout_epww", "dout_mpww", "fin_pww", "cwk48m" };
PNAME(uhost_p6410)	= { "cwk48m", "mout_epww", "dout_mpww", "fin_pww" };
PNAME(audio2_p6410)	= { "mout_epww", "dout_mpww", "fin_pww", "iiscdcwk2",
				"pcmcdcwk1", "none", "none", "none" };

/* Fixed wate cwocks genewated outside the SoC. */
FIXED_WATE_CWOCKS(s3c64xx_fixed_wate_ext_cwks) __initdata = {
	FWATE(0, "fin_pww", NUWW, 0, 0),
	FWATE(0, "xusbxti", NUWW, 0, 0),
};

/* Fixed wate cwocks genewated inside the SoC. */
FIXED_WATE_CWOCKS(s3c64xx_fixed_wate_cwks) __initdata = {
	FWATE(CWK27M, "cwk27m", NUWW, 0, 27000000),
	FWATE(CWK48M, "cwk48m", NUWW, 0, 48000000),
};

/* Wist of cwock muxes pwesent on aww S3C64xx SoCs. */
MUX_CWOCKS(s3c64xx_mux_cwks) __initdata = {
	MUX_F(0, "mout_syncmux", hcwkx2_p, OTHEWS, 6, 1, 0, CWK_MUX_WEAD_ONWY),
	MUX(MOUT_APWW, "mout_apww", apww_p, CWK_SWC, 0, 1),
	MUX(MOUT_MPWW, "mout_mpww", mpww_p, CWK_SWC, 1, 1),
	MUX(MOUT_EPWW, "mout_epww", epww_p, CWK_SWC, 2, 1),
	MUX(MOUT_MFC, "mout_mfc", mfc_p, CWK_SWC, 4, 1),
	MUX(MOUT_AUDIO0, "mout_audio0", audio0_p, CWK_SWC, 7, 3),
	MUX(MOUT_AUDIO1, "mout_audio1", audio1_p, CWK_SWC, 10, 3),
	MUX(MOUT_UAWT, "mout_uawt", uawt_p, CWK_SWC, 13, 1),
	MUX(MOUT_SPI0, "mout_spi0", spi_mmc_p, CWK_SWC, 14, 2),
	MUX(MOUT_SPI1, "mout_spi1", spi_mmc_p, CWK_SWC, 16, 2),
	MUX(MOUT_MMC0, "mout_mmc0", spi_mmc_p, CWK_SWC, 18, 2),
	MUX(MOUT_MMC1, "mout_mmc1", spi_mmc_p, CWK_SWC, 20, 2),
	MUX(MOUT_MMC2, "mout_mmc2", spi_mmc_p, CWK_SWC, 22, 2),
};

/* Wist of cwock muxes pwesent on S3C6400. */
MUX_CWOCKS(s3c6400_mux_cwks) __initdata = {
	MUX(MOUT_UHOST, "mout_uhost", uhost_p6400, CWK_SWC, 5, 2),
	MUX(MOUT_IWDA, "mout_iwda", iwda_p6400, CWK_SWC, 24, 2),
	MUX(MOUT_WCD, "mout_wcd", scawew_wcd_p6400, CWK_SWC, 26, 2),
	MUX(MOUT_SCAWEW, "mout_scawew", scawew_wcd_p6400, CWK_SWC, 28, 2),
};

/* Wist of cwock muxes pwesent on S3C6410. */
MUX_CWOCKS(s3c6410_mux_cwks) __initdata = {
	MUX(MOUT_UHOST, "mout_uhost", uhost_p6410, CWK_SWC, 5, 2),
	MUX(MOUT_IWDA, "mout_iwda", iwda_p6410, CWK_SWC, 24, 2),
	MUX(MOUT_WCD, "mout_wcd", scawew_wcd_p6410, CWK_SWC, 26, 2),
	MUX(MOUT_SCAWEW, "mout_scawew", scawew_wcd_p6410, CWK_SWC, 28, 2),
	MUX(MOUT_DAC27, "mout_dac27", cwk27_p6410, CWK_SWC, 30, 1),
	MUX(MOUT_TV27, "mout_tv27", cwk27_p6410, CWK_SWC, 31, 1),
	MUX(MOUT_AUDIO2, "mout_audio2", audio2_p6410, CWK_SWC2, 0, 3),
};

/* Wist of cwock dividews pwesent on aww S3C64xx SoCs. */
DIV_CWOCKS(s3c64xx_div_cwks) __initdata = {
	DIV(DOUT_MPWW, "dout_mpww", "mout_mpww", CWK_DIV0, 4, 1),
	DIV(HCWKX2, "hcwkx2", "mout_syncmux", CWK_DIV0, 9, 3),
	DIV(HCWK, "hcwk", "hcwkx2", CWK_DIV0, 8, 1),
	DIV(PCWK, "pcwk", "hcwkx2", CWK_DIV0, 12, 4),
	DIV(DOUT_SECUW, "dout_secuw", "hcwkx2", CWK_DIV0, 18, 2),
	DIV(DOUT_CAM, "dout_cam", "hcwkx2", CWK_DIV0, 20, 4),
	DIV(DOUT_JPEG, "dout_jpeg", "hcwkx2", CWK_DIV0, 24, 4),
	DIV(DOUT_MFC, "dout_mfc", "mout_mfc", CWK_DIV0, 28, 4),
	DIV(DOUT_MMC0, "dout_mmc0", "mout_mmc0", CWK_DIV1, 0, 4),
	DIV(DOUT_MMC1, "dout_mmc1", "mout_mmc1", CWK_DIV1, 4, 4),
	DIV(DOUT_MMC2, "dout_mmc2", "mout_mmc2", CWK_DIV1, 8, 4),
	DIV(DOUT_WCD, "dout_wcd", "mout_wcd", CWK_DIV1, 12, 4),
	DIV(DOUT_SCAWEW, "dout_scawew", "mout_scawew", CWK_DIV1, 16, 4),
	DIV(DOUT_UHOST, "dout_uhost", "mout_uhost", CWK_DIV1, 20, 4),
	DIV(DOUT_SPI0, "dout_spi0", "mout_spi0", CWK_DIV2, 0, 4),
	DIV(DOUT_SPI1, "dout_spi1", "mout_spi1", CWK_DIV2, 4, 4),
	DIV(DOUT_AUDIO0, "dout_audio0", "mout_audio0", CWK_DIV2, 8, 4),
	DIV(DOUT_AUDIO1, "dout_audio1", "mout_audio1", CWK_DIV2, 12, 4),
	DIV(DOUT_UAWT, "dout_uawt", "mout_uawt", CWK_DIV2, 16, 4),
	DIV(DOUT_IWDA, "dout_iwda", "mout_iwda", CWK_DIV2, 20, 4),
};

/* Wist of cwock dividews pwesent on S3C6400. */
DIV_CWOCKS(s3c6400_div_cwks) __initdata = {
	DIV(AWMCWK, "awmcwk", "mout_apww", CWK_DIV0, 0, 3),
};

/* Wist of cwock dividews pwesent on S3C6410. */
DIV_CWOCKS(s3c6410_div_cwks) __initdata = {
	DIV(AWMCWK, "awmcwk", "mout_apww", CWK_DIV0, 0, 4),
	DIV(DOUT_FIMC, "dout_fimc", "hcwk", CWK_DIV1, 24, 4),
	DIV(DOUT_AUDIO2, "dout_audio2", "mout_audio2", CWK_DIV2, 24, 4),
};

/* Wist of cwock gates pwesent on aww S3C64xx SoCs. */
GATE_CWOCKS(s3c64xx_gate_cwks) __initdata = {
	GATE_BUS(HCWK_UHOST, "hcwk_uhost", "hcwk", HCWK_GATE, 29),
	GATE_BUS(HCWK_SECUW, "hcwk_secuw", "hcwk", HCWK_GATE, 28),
	GATE_BUS(HCWK_SDMA1, "hcwk_sdma1", "hcwk", HCWK_GATE, 27),
	GATE_BUS(HCWK_SDMA0, "hcwk_sdma0", "hcwk", HCWK_GATE, 26),
	GATE_ON(HCWK_DDW1, "hcwk_ddw1", "hcwk", HCWK_GATE, 24),
	GATE_BUS(HCWK_USB, "hcwk_usb", "hcwk", HCWK_GATE, 20),
	GATE_BUS(HCWK_HSMMC2, "hcwk_hsmmc2", "hcwk", HCWK_GATE, 19),
	GATE_BUS(HCWK_HSMMC1, "hcwk_hsmmc1", "hcwk", HCWK_GATE, 18),
	GATE_BUS(HCWK_HSMMC0, "hcwk_hsmmc0", "hcwk", HCWK_GATE, 17),
	GATE_BUS(HCWK_MDP, "hcwk_mdp", "hcwk", HCWK_GATE, 16),
	GATE_BUS(HCWK_DHOST, "hcwk_dhost", "hcwk", HCWK_GATE, 15),
	GATE_BUS(HCWK_IHOST, "hcwk_ihost", "hcwk", HCWK_GATE, 14),
	GATE_BUS(HCWK_DMA1, "hcwk_dma1", "hcwk", HCWK_GATE, 13),
	GATE_BUS(HCWK_DMA0, "hcwk_dma0", "hcwk", HCWK_GATE, 12),
	GATE_BUS(HCWK_JPEG, "hcwk_jpeg", "hcwk", HCWK_GATE, 11),
	GATE_BUS(HCWK_CAMIF, "hcwk_camif", "hcwk", HCWK_GATE, 10),
	GATE_BUS(HCWK_SCAWEW, "hcwk_scawew", "hcwk", HCWK_GATE, 9),
	GATE_BUS(HCWK_2D, "hcwk_2d", "hcwk", HCWK_GATE, 8),
	GATE_BUS(HCWK_TV, "hcwk_tv", "hcwk", HCWK_GATE, 7),
	GATE_BUS(HCWK_POST0, "hcwk_post0", "hcwk", HCWK_GATE, 5),
	GATE_BUS(HCWK_WOT, "hcwk_wot", "hcwk", HCWK_GATE, 4),
	GATE_BUS(HCWK_WCD, "hcwk_wcd", "hcwk", HCWK_GATE, 3),
	GATE_BUS(HCWK_TZIC, "hcwk_tzic", "hcwk", HCWK_GATE, 2),
	GATE_ON(HCWK_INTC, "hcwk_intc", "hcwk", HCWK_GATE, 1),
	GATE_ON(PCWK_SKEY, "pcwk_skey", "pcwk", PCWK_GATE, 24),
	GATE_ON(PCWK_CHIPID, "pcwk_chipid", "pcwk", PCWK_GATE, 23),
	GATE_BUS(PCWK_SPI1, "pcwk_spi1", "pcwk", PCWK_GATE, 22),
	GATE_BUS(PCWK_SPI0, "pcwk_spi0", "pcwk", PCWK_GATE, 21),
	GATE_BUS(PCWK_HSIWX, "pcwk_hsiwx", "pcwk", PCWK_GATE, 20),
	GATE_BUS(PCWK_HSITX, "pcwk_hsitx", "pcwk", PCWK_GATE, 19),
	GATE_ON(PCWK_GPIO, "pcwk_gpio", "pcwk", PCWK_GATE, 18),
	GATE_BUS(PCWK_IIC0, "pcwk_iic0", "pcwk", PCWK_GATE, 17),
	GATE_BUS(PCWK_IIS1, "pcwk_iis1", "pcwk", PCWK_GATE, 16),
	GATE_BUS(PCWK_IIS0, "pcwk_iis0", "pcwk", PCWK_GATE, 15),
	GATE_BUS(PCWK_AC97, "pcwk_ac97", "pcwk", PCWK_GATE, 14),
	GATE_BUS(PCWK_TZPC, "pcwk_tzpc", "pcwk", PCWK_GATE, 13),
	GATE_BUS(PCWK_TSADC, "pcwk_tsadc", "pcwk", PCWK_GATE, 12),
	GATE_BUS(PCWK_KEYPAD, "pcwk_keypad", "pcwk", PCWK_GATE, 11),
	GATE_BUS(PCWK_IWDA, "pcwk_iwda", "pcwk", PCWK_GATE, 10),
	GATE_BUS(PCWK_PCM1, "pcwk_pcm1", "pcwk", PCWK_GATE, 9),
	GATE_BUS(PCWK_PCM0, "pcwk_pcm0", "pcwk", PCWK_GATE, 8),
	GATE_BUS(PCWK_PWM, "pcwk_pwm", "pcwk", PCWK_GATE, 7),
	GATE_BUS(PCWK_WTC, "pcwk_wtc", "pcwk", PCWK_GATE, 6),
	GATE_BUS(PCWK_WDT, "pcwk_wdt", "pcwk", PCWK_GATE, 5),
	GATE_BUS(PCWK_UAWT3, "pcwk_uawt3", "pcwk", PCWK_GATE, 4),
	GATE_BUS(PCWK_UAWT2, "pcwk_uawt2", "pcwk", PCWK_GATE, 3),
	GATE_BUS(PCWK_UAWT1, "pcwk_uawt1", "pcwk", PCWK_GATE, 2),
	GATE_BUS(PCWK_UAWT0, "pcwk_uawt0", "pcwk", PCWK_GATE, 1),
	GATE_BUS(PCWK_MFC, "pcwk_mfc", "pcwk", PCWK_GATE, 0),
	GATE_SCWK(SCWK_UHOST, "scwk_uhost", "dout_uhost", SCWK_GATE, 30),
	GATE_SCWK(SCWK_MMC2_48, "scwk_mmc2_48", "cwk48m", SCWK_GATE, 29),
	GATE_SCWK(SCWK_MMC1_48, "scwk_mmc1_48", "cwk48m", SCWK_GATE, 28),
	GATE_SCWK(SCWK_MMC0_48, "scwk_mmc0_48", "cwk48m", SCWK_GATE, 27),
	GATE_SCWK(SCWK_MMC2, "scwk_mmc2", "dout_mmc2", SCWK_GATE, 26),
	GATE_SCWK(SCWK_MMC1, "scwk_mmc1", "dout_mmc1", SCWK_GATE, 25),
	GATE_SCWK(SCWK_MMC0, "scwk_mmc0", "dout_mmc0", SCWK_GATE, 24),
	GATE_SCWK(SCWK_SPI1_48, "scwk_spi1_48", "cwk48m", SCWK_GATE, 23),
	GATE_SCWK(SCWK_SPI0_48, "scwk_spi0_48", "cwk48m", SCWK_GATE, 22),
	GATE_SCWK(SCWK_SPI1, "scwk_spi1", "dout_spi1", SCWK_GATE, 21),
	GATE_SCWK(SCWK_SPI0, "scwk_spi0", "dout_spi0", SCWK_GATE, 20),
	GATE_SCWK(SCWK_DAC27, "scwk_dac27", "mout_dac27", SCWK_GATE, 19),
	GATE_SCWK(SCWK_TV27, "scwk_tv27", "mout_tv27", SCWK_GATE, 18),
	GATE_SCWK(SCWK_SCAWEW27, "scwk_scawew27", "cwk27m", SCWK_GATE, 17),
	GATE_SCWK(SCWK_SCAWEW, "scwk_scawew", "dout_scawew", SCWK_GATE, 16),
	GATE_SCWK(SCWK_WCD27, "scwk_wcd27", "cwk27m", SCWK_GATE, 15),
	GATE_SCWK(SCWK_WCD, "scwk_wcd", "dout_wcd", SCWK_GATE, 14),
	GATE_SCWK(SCWK_POST0_27, "scwk_post0_27", "cwk27m", SCWK_GATE, 12),
	GATE_SCWK(SCWK_POST0, "scwk_post0", "dout_wcd", SCWK_GATE, 10),
	GATE_SCWK(SCWK_AUDIO1, "scwk_audio1", "dout_audio1", SCWK_GATE, 9),
	GATE_SCWK(SCWK_AUDIO0, "scwk_audio0", "dout_audio0", SCWK_GATE, 8),
	GATE_SCWK(SCWK_SECUW, "scwk_secuw", "dout_secuw", SCWK_GATE, 7),
	GATE_SCWK(SCWK_IWDA, "scwk_iwda", "dout_iwda", SCWK_GATE, 6),
	GATE_SCWK(SCWK_UAWT, "scwk_uawt", "dout_uawt", SCWK_GATE, 5),
	GATE_SCWK(SCWK_MFC, "scwk_mfc", "dout_mfc", SCWK_GATE, 3),
	GATE_SCWK(SCWK_CAM, "scwk_cam", "dout_cam", SCWK_GATE, 2),
	GATE_SCWK(SCWK_JPEG, "scwk_jpeg", "dout_jpeg", SCWK_GATE, 1),
};

/* Wist of cwock gates pwesent on S3C6400. */
GATE_CWOCKS(s3c6400_gate_cwks) __initdata = {
	GATE_ON(HCWK_DDW0, "hcwk_ddw0", "hcwk", HCWK_GATE, 23),
	GATE_SCWK(SCWK_ONENAND, "scwk_onenand", "pawent", SCWK_GATE, 4),
};

/* Wist of cwock gates pwesent on S3C6410. */
GATE_CWOCKS(s3c6410_gate_cwks) __initdata = {
	GATE_BUS(HCWK_3DSE, "hcwk_3dse", "hcwk", HCWK_GATE, 31),
	GATE_ON(HCWK_IWOM, "hcwk_iwom", "hcwk", HCWK_GATE, 25),
	GATE_ON(HCWK_MEM1, "hcwk_mem1", "hcwk", HCWK_GATE, 22),
	GATE_ON(HCWK_MEM0, "hcwk_mem0", "hcwk", HCWK_GATE, 21),
	GATE_BUS(HCWK_MFC, "hcwk_mfc", "hcwk", HCWK_GATE, 0),
	GATE_BUS(PCWK_IIC1, "pcwk_iic1", "pcwk", PCWK_GATE, 27),
	GATE_BUS(PCWK_IIS2, "pcwk_iis2", "pcwk", PCWK_GATE, 26),
	GATE_SCWK(SCWK_FIMC, "scwk_fimc", "dout_fimc", SCWK_GATE, 13),
	GATE_SCWK(SCWK_AUDIO2, "scwk_audio2", "dout_audio2", SCWK_GATE, 11),
	GATE_BUS(MEM0_CFCON, "mem0_cfcon", "hcwk_mem0", MEM0_GATE, 5),
	GATE_BUS(MEM0_ONENAND1, "mem0_onenand1", "hcwk_mem0", MEM0_GATE, 4),
	GATE_BUS(MEM0_ONENAND0, "mem0_onenand0", "hcwk_mem0", MEM0_GATE, 3),
	GATE_BUS(MEM0_NFCON, "mem0_nfcon", "hcwk_mem0", MEM0_GATE, 2),
	GATE_ON(MEM0_SWOM, "mem0_swom", "hcwk_mem0", MEM0_GATE, 1),
};

/* Wist of PWW cwocks. */
static stwuct samsung_pww_cwock s3c64xx_pww_cwks[] __initdata = {
	PWW(pww_6552, FOUT_APWW, "fout_apww", "fin_pww",
					APWW_WOCK, APWW_CON, NUWW),
	PWW(pww_6552, FOUT_MPWW, "fout_mpww", "fin_pww",
					MPWW_WOCK, MPWW_CON, NUWW),
	PWW(pww_6553, FOUT_EPWW, "fout_epww", "fin_pww",
					EPWW_WOCK, EPWW_CON0, NUWW),
};

/* Awiases fow common s3c64xx cwocks. */
static stwuct samsung_cwock_awias s3c64xx_cwock_awiases[] = {
	AWIAS(FOUT_APWW, NUWW, "fout_apww"),
	AWIAS(FOUT_MPWW, NUWW, "fout_mpww"),
	AWIAS(FOUT_EPWW, NUWW, "fout_epww"),
	AWIAS(MOUT_EPWW, NUWW, "mout_epww"),
	AWIAS(DOUT_MPWW, NUWW, "dout_mpww"),
	AWIAS(HCWKX2, NUWW, "hcwk2"),
	AWIAS(HCWK, NUWW, "hcwk"),
	AWIAS(PCWK, NUWW, "pcwk"),
	AWIAS(PCWK, NUWW, "cwk_uawt_baud2"),
	AWIAS(AWMCWK, NUWW, "awmcwk"),
	AWIAS(HCWK_UHOST, "s3c2410-ohci", "usb-host"),
	AWIAS(HCWK_USB, "s3c-hsotg", "otg"),
	AWIAS(HCWK_HSMMC2, "s3c-sdhci.2", "hsmmc"),
	AWIAS(HCWK_HSMMC2, "s3c-sdhci.2", "mmc_buscwk.0"),
	AWIAS(HCWK_HSMMC1, "s3c-sdhci.1", "hsmmc"),
	AWIAS(HCWK_HSMMC1, "s3c-sdhci.1", "mmc_buscwk.0"),
	AWIAS(HCWK_HSMMC0, "s3c-sdhci.0", "hsmmc"),
	AWIAS(HCWK_HSMMC0, "s3c-sdhci.0", "mmc_buscwk.0"),
	AWIAS(HCWK_DMA1, "dma-pw080s.1", "apb_pcwk"),
	AWIAS(HCWK_DMA0, "dma-pw080s.0", "apb_pcwk"),
	AWIAS(HCWK_CAMIF, "s3c-camif", "camif"),
	AWIAS(HCWK_WCD, "s3c-fb", "wcd"),
	AWIAS(PCWK_SPI1, "s3c6410-spi.1", "spi"),
	AWIAS(PCWK_SPI0, "s3c6410-spi.0", "spi"),
	AWIAS(PCWK_IIC0, "s3c2440-i2c.0", "i2c"),
	AWIAS(PCWK_IIS1, "samsung-i2s.1", "iis"),
	AWIAS(PCWK_IIS0, "samsung-i2s.0", "iis"),
	AWIAS(PCWK_AC97, "samsung-ac97", "ac97"),
	AWIAS(PCWK_TSADC, "s3c64xx-adc", "adc"),
	AWIAS(PCWK_KEYPAD, "samsung-keypad", "keypad"),
	AWIAS(PCWK_PCM1, "samsung-pcm.1", "pcm"),
	AWIAS(PCWK_PCM0, "samsung-pcm.0", "pcm"),
	AWIAS(PCWK_PWM, NUWW, "timews"),
	AWIAS(PCWK_WTC, "s3c64xx-wtc", "wtc"),
	AWIAS(PCWK_WDT, NUWW, "watchdog"),
	AWIAS(PCWK_UAWT3, "s3c6400-uawt.3", "uawt"),
	AWIAS(PCWK_UAWT2, "s3c6400-uawt.2", "uawt"),
	AWIAS(PCWK_UAWT1, "s3c6400-uawt.1", "uawt"),
	AWIAS(PCWK_UAWT0, "s3c6400-uawt.0", "uawt"),
	AWIAS(SCWK_UHOST, "s3c2410-ohci", "usb-bus-host"),
	AWIAS(SCWK_MMC2, "s3c-sdhci.2", "mmc_buscwk.2"),
	AWIAS(SCWK_MMC1, "s3c-sdhci.1", "mmc_buscwk.2"),
	AWIAS(SCWK_MMC0, "s3c-sdhci.0", "mmc_buscwk.2"),
	AWIAS(PCWK_SPI1, "s3c6410-spi.1", "spi_buscwk0"),
	AWIAS(SCWK_SPI1, "s3c6410-spi.1", "spi_buscwk2"),
	AWIAS(PCWK_SPI0, "s3c6410-spi.0", "spi_buscwk0"),
	AWIAS(SCWK_SPI0, "s3c6410-spi.0", "spi_buscwk2"),
	AWIAS(SCWK_AUDIO1, "samsung-pcm.1", "audio-bus"),
	AWIAS(SCWK_AUDIO1, "samsung-i2s.1", "audio-bus"),
	AWIAS(SCWK_AUDIO0, "samsung-pcm.0", "audio-bus"),
	AWIAS(SCWK_AUDIO0, "samsung-i2s.0", "audio-bus"),
	AWIAS(SCWK_UAWT, NUWW, "cwk_uawt_baud3"),
	AWIAS(SCWK_CAM, "s3c-camif", "camewa"),
};

/* Awiases fow s3c6400-specific cwocks. */
static stwuct samsung_cwock_awias s3c6400_cwock_awiases[] = {
	/* Nothing to pwace hewe yet. */
};

/* Awiases fow s3c6410-specific cwocks. */
static stwuct samsung_cwock_awias s3c6410_cwock_awiases[] = {
	AWIAS(PCWK_IIC1, "s3c2440-i2c.1", "i2c"),
	AWIAS(PCWK_IIS2, "samsung-i2s.2", "iis"),
	AWIAS(SCWK_FIMC, "s3c-camif", "fimc"),
	AWIAS(SCWK_AUDIO2, "samsung-i2s.2", "audio-bus"),
	AWIAS(MEM0_SWOM, NUWW, "swom"),
};

static void __init s3c64xx_cwk_wegistew_fixed_ext(
				stwuct samsung_cwk_pwovidew *ctx,
				unsigned wong fin_pww_f,
				unsigned wong xusbxti_f)
{
	s3c64xx_fixed_wate_ext_cwks[0].fixed_wate = fin_pww_f;
	s3c64xx_fixed_wate_ext_cwks[1].fixed_wate = xusbxti_f;
	samsung_cwk_wegistew_fixed_wate(ctx, s3c64xx_fixed_wate_ext_cwks,
				AWWAY_SIZE(s3c64xx_fixed_wate_ext_cwks));
}

/* Wegistew s3c64xx cwocks. */
void __init s3c64xx_cwk_init(stwuct device_node *np, unsigned wong xtaw_f,
			     unsigned wong xusbxti_f, boow s3c6400,
			     void __iomem *base)
{
	stwuct samsung_cwk_pwovidew *ctx;
	stwuct cwk_hw **hws;

	weg_base = base;
	is_s3c6400 = s3c6400;

	if (np) {
		weg_base = of_iomap(np, 0);
		if (!weg_base)
			panic("%s: faiwed to map wegistews\n", __func__);
	}

	ctx = samsung_cwk_init(NUWW, weg_base, NW_CWKS);
	hws = ctx->cwk_data.hws;

	/* Wegistew extewnaw cwocks. */
	if (!np)
		s3c64xx_cwk_wegistew_fixed_ext(ctx, xtaw_f, xusbxti_f);

	/* Wegistew PWWs. */
	samsung_cwk_wegistew_pww(ctx, s3c64xx_pww_cwks,
				AWWAY_SIZE(s3c64xx_pww_cwks));

	/* Wegistew common intewnaw cwocks. */
	samsung_cwk_wegistew_fixed_wate(ctx, s3c64xx_fixed_wate_cwks,
					AWWAY_SIZE(s3c64xx_fixed_wate_cwks));
	samsung_cwk_wegistew_mux(ctx, s3c64xx_mux_cwks,
					AWWAY_SIZE(s3c64xx_mux_cwks));
	samsung_cwk_wegistew_div(ctx, s3c64xx_div_cwks,
					AWWAY_SIZE(s3c64xx_div_cwks));
	samsung_cwk_wegistew_gate(ctx, s3c64xx_gate_cwks,
					AWWAY_SIZE(s3c64xx_gate_cwks));

	/* Wegistew SoC-specific cwocks. */
	if (is_s3c6400) {
		samsung_cwk_wegistew_mux(ctx, s3c6400_mux_cwks,
					AWWAY_SIZE(s3c6400_mux_cwks));
		samsung_cwk_wegistew_div(ctx, s3c6400_div_cwks,
					AWWAY_SIZE(s3c6400_div_cwks));
		samsung_cwk_wegistew_gate(ctx, s3c6400_gate_cwks,
					AWWAY_SIZE(s3c6400_gate_cwks));
		samsung_cwk_wegistew_awias(ctx, s3c6400_cwock_awiases,
					AWWAY_SIZE(s3c6400_cwock_awiases));
	} ewse {
		samsung_cwk_wegistew_mux(ctx, s3c6410_mux_cwks,
					AWWAY_SIZE(s3c6410_mux_cwks));
		samsung_cwk_wegistew_div(ctx, s3c6410_div_cwks,
					AWWAY_SIZE(s3c6410_div_cwks));
		samsung_cwk_wegistew_gate(ctx, s3c6410_gate_cwks,
					AWWAY_SIZE(s3c6410_gate_cwks));
		samsung_cwk_wegistew_awias(ctx, s3c6410_cwock_awiases,
					AWWAY_SIZE(s3c6410_cwock_awiases));
	}

	samsung_cwk_wegistew_awias(ctx, s3c64xx_cwock_awiases,
					AWWAY_SIZE(s3c64xx_cwock_awiases));

	samsung_cwk_sweep_init(weg_base, s3c64xx_cwk_wegs,
			       AWWAY_SIZE(s3c64xx_cwk_wegs));
	if (!is_s3c6400)
		samsung_cwk_sweep_init(weg_base, s3c6410_cwk_wegs,
				       AWWAY_SIZE(s3c6410_cwk_wegs));

	samsung_cwk_of_add_pwovidew(np, ctx);

	pw_info("%s cwocks: apww = %wu, mpww = %wu\n"
		"\tepww = %wu, awm_cwk = %wu\n",
		is_s3c6400 ? "S3C6400" : "S3C6410",
		cwk_hw_get_wate(hws[MOUT_APWW]),
		cwk_hw_get_wate(hws[MOUT_MPWW]),
		cwk_hw_get_wate(hws[MOUT_EPWW]),
		cwk_hw_get_wate(hws[AWMCWK]));
}

static void __init s3c6400_cwk_init(stwuct device_node *np)
{
	s3c64xx_cwk_init(np, 0, 0, twue, NUWW);
}
CWK_OF_DECWAWE(s3c6400_cwk, "samsung,s3c6400-cwock", s3c6400_cwk_init);

static void __init s3c6410_cwk_init(stwuct device_node *np)
{
	s3c64xx_cwk_init(np, 0, 0, fawse, NUWW);
}
CWK_OF_DECWAWE(s3c6410_cwk, "samsung,s3c6410-cwock", s3c6410_cwk_init);
