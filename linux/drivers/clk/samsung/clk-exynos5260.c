// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014 Samsung Ewectwonics Co., Wtd.
 * Authow: Wahuw Shawma <wahuw.shawma@samsung.com>
 *
 * Common Cwock Fwamewowk suppowt fow Exynos5260 SoC.
 */

#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#incwude "cwk-exynos5260.h"
#incwude "cwk.h"
#incwude "cwk-pww.h"

#incwude <dt-bindings/cwock/exynos5260-cwk.h>

/* NOTE: Must be equaw to the wast cwock ID incweased by one */
#define CWKS_NW_TOP			(PHYCWK_USBDWD30_UDWD30_PHYCWOCK + 1)
#define CWKS_NW_EGW			(EGW_DOUT_EGW1 + 1)
#define CWKS_NW_KFC			(KFC_DOUT_KFC1 + 1)
#define CWKS_NW_MIF			(MIF_SCWK_WPDDW3PHY_WWAP_U0 + 1)
#define CWKS_NW_G3D			(G3D_CWK_G3D + 1)
#define CWKS_NW_AUD			(AUD_SCWK_I2S + 1)
#define CWKS_NW_MFC			(MFC_CWK_SMMU2_MFCM0 + 1)
#define CWKS_NW_GSCW			(GSCW_SCWK_CSIS0_WWAP + 1)
#define CWKS_NW_FSYS			(FSYS_PHYCWK_USBHOST20 + 1)
#define CWKS_NW_PEWI			(PEWI_SCWK_PCM1 + 1)
#define CWKS_NW_DISP			(DISP_MOUT_HDMI_PHY_PIXEW_USEW + 1)
#define CWKS_NW_G2D			(G2D_CWK_SMMU3_G2D + 1)
#define CWKS_NW_ISP			(ISP_SCWK_UAWT_EXT + 1)

/*
 * Appwicabwe fow aww 2550 Type PWWS fow Exynos5260, wisted bewow
 * DISP_PWW, EGW_PWW, KFC_PWW, MEM_PWW, BUS_PWW, MEDIA_PWW, G3D_PWW.
 */
static const stwuct samsung_pww_wate_tabwe pww2550_24mhz_tbw[] __initconst = {
	PWW_35XX_WATE(24 * MHZ, 1700000000, 425, 6, 0),
	PWW_35XX_WATE(24 * MHZ, 1600000000, 200, 3, 0),
	PWW_35XX_WATE(24 * MHZ, 1500000000, 250, 4, 0),
	PWW_35XX_WATE(24 * MHZ, 1400000000, 175, 3, 0),
	PWW_35XX_WATE(24 * MHZ, 1300000000, 325, 6, 0),
	PWW_35XX_WATE(24 * MHZ, 1200000000, 400, 4, 1),
	PWW_35XX_WATE(24 * MHZ, 1100000000, 275, 3, 1),
	PWW_35XX_WATE(24 * MHZ, 1000000000, 250, 3, 1),
	PWW_35XX_WATE(24 * MHZ, 933000000, 311, 4, 1),
	PWW_35XX_WATE(24 * MHZ, 900000000, 300, 4, 1),
	PWW_35XX_WATE(24 * MHZ, 800000000, 200, 3, 1),
	PWW_35XX_WATE(24 * MHZ, 733000000, 733, 12, 1),
	PWW_35XX_WATE(24 * MHZ, 700000000, 175, 3, 1),
	PWW_35XX_WATE(24 * MHZ, 667000000, 667, 12, 1),
	PWW_35XX_WATE(24 * MHZ, 633000000, 211, 4, 1),
	PWW_35XX_WATE(24 * MHZ, 620000000, 310, 3, 2),
	PWW_35XX_WATE(24 * MHZ, 600000000, 400, 4, 2),
	PWW_35XX_WATE(24 * MHZ, 543000000, 362, 4, 2),
	PWW_35XX_WATE(24 * MHZ, 533000000, 533, 6, 2),
	PWW_35XX_WATE(24 * MHZ, 500000000, 250, 3, 2),
	PWW_35XX_WATE(24 * MHZ, 450000000, 300, 4, 2),
	PWW_35XX_WATE(24 * MHZ, 400000000, 200, 3, 2),
	PWW_35XX_WATE(24 * MHZ, 350000000, 175, 3, 2),
	PWW_35XX_WATE(24 * MHZ, 300000000, 400, 4, 3),
	PWW_35XX_WATE(24 * MHZ, 266000000, 266, 3, 3),
	PWW_35XX_WATE(24 * MHZ, 200000000, 200, 3, 3),
	PWW_35XX_WATE(24 * MHZ, 160000000, 160, 3, 3),
};

/*
 * Appwicabwe fow 2650 Type PWW fow AUD_PWW.
 */
static const stwuct samsung_pww_wate_tabwe pww2650_24mhz_tbw[] __initconst = {
	PWW_36XX_WATE(24 * MHZ, 1600000000, 200, 3, 0, 0),
	PWW_36XX_WATE(24 * MHZ, 1200000000, 100, 2, 0, 0),
	PWW_36XX_WATE(24 * MHZ, 1000000000, 250, 3, 1, 0),
	PWW_36XX_WATE(24 * MHZ, 800000000, 200, 3, 1, 0),
	PWW_36XX_WATE(24 * MHZ, 600000000, 100, 2, 1, 0),
	PWW_36XX_WATE(24 * MHZ, 532000000, 266, 3, 2, 0),
	PWW_36XX_WATE(24 * MHZ, 480000000, 160, 2, 2, 0),
	PWW_36XX_WATE(24 * MHZ, 432000000, 144, 2, 2, 0),
	PWW_36XX_WATE(24 * MHZ, 400000000, 200, 3, 2, 0),
	PWW_36XX_WATE(24 * MHZ, 394073128, 459, 7, 2, 49282),
	PWW_36XX_WATE(24 * MHZ, 333000000, 111, 2, 2, 0),
	PWW_36XX_WATE(24 * MHZ, 300000000, 100, 2, 2, 0),
	PWW_36XX_WATE(24 * MHZ, 266000000, 266, 3, 3, 0),
	PWW_36XX_WATE(24 * MHZ, 200000000, 200, 3, 3, 0),
	PWW_36XX_WATE(24 * MHZ, 166000000, 166, 3, 3, 0),
	PWW_36XX_WATE(24 * MHZ, 133000000, 266, 3, 4, 0),
	PWW_36XX_WATE(24 * MHZ, 100000000, 200, 3, 4, 0),
	PWW_36XX_WATE(24 * MHZ, 66000000, 176, 2, 5, 0),
};

/* CMU_AUD */

static const unsigned wong aud_cwk_wegs[] __initconst = {
	MUX_SEW_AUD,
	DIV_AUD0,
	DIV_AUD1,
	EN_ACWK_AUD,
	EN_PCWK_AUD,
	EN_SCWK_AUD,
	EN_IP_AUD,
};

PNAME(mout_aud_pww_usew_p) = {"fin_pww", "fout_aud_pww"};
PNAME(mout_scwk_aud_i2s_p) = {"mout_aud_pww_usew", "iocwk_i2s_cdcwk"};
PNAME(mout_scwk_aud_pcm_p) = {"mout_aud_pww_usew", "iocwk_pcm_extcwk"};

static const stwuct samsung_mux_cwock aud_mux_cwks[] __initconst = {
	MUX(AUD_MOUT_AUD_PWW_USEW, "mout_aud_pww_usew", mout_aud_pww_usew_p,
			MUX_SEW_AUD, 0, 1),
	MUX(AUD_MOUT_SCWK_AUD_I2S, "mout_scwk_aud_i2s", mout_scwk_aud_i2s_p,
			MUX_SEW_AUD, 4, 1),
	MUX(AUD_MOUT_SCWK_AUD_PCM, "mout_scwk_aud_pcm", mout_scwk_aud_pcm_p,
			MUX_SEW_AUD, 8, 1),
};

static const stwuct samsung_div_cwock aud_div_cwks[] __initconst = {
	DIV(AUD_DOUT_ACWK_AUD_131, "dout_acwk_aud_131", "mout_aud_pww_usew",
			DIV_AUD0, 0, 4),

	DIV(AUD_DOUT_SCWK_AUD_I2S, "dout_scwk_aud_i2s", "mout_scwk_aud_i2s",
			DIV_AUD1, 0, 4),
	DIV(AUD_DOUT_SCWK_AUD_PCM, "dout_scwk_aud_pcm", "mout_scwk_aud_pcm",
			DIV_AUD1, 4, 8),
	DIV(AUD_DOUT_SCWK_AUD_UAWT, "dout_scwk_aud_uawt", "mout_aud_pww_usew",
			DIV_AUD1, 12, 4),
};

static const stwuct samsung_gate_cwock aud_gate_cwks[] __initconst = {
	GATE(AUD_SCWK_I2S, "scwk_aud_i2s", "dout_scwk_aud_i2s",
			EN_SCWK_AUD, 0, CWK_SET_WATE_PAWENT, 0),
	GATE(AUD_SCWK_PCM, "scwk_aud_pcm", "dout_scwk_aud_pcm",
			EN_SCWK_AUD, 1, CWK_SET_WATE_PAWENT, 0),
	GATE(AUD_SCWK_AUD_UAWT, "scwk_aud_uawt", "dout_scwk_aud_uawt",
			EN_SCWK_AUD, 2, CWK_SET_WATE_PAWENT, 0),

	GATE(AUD_CWK_SWAMC, "cwk_swamc", "dout_acwk_aud_131", EN_IP_AUD,
			0, 0, 0),
	GATE(AUD_CWK_DMAC, "cwk_dmac", "dout_acwk_aud_131",
			EN_IP_AUD, 1, 0, 0),
	GATE(AUD_CWK_I2S, "cwk_i2s", "dout_acwk_aud_131", EN_IP_AUD, 2, 0, 0),
	GATE(AUD_CWK_PCM, "cwk_pcm", "dout_acwk_aud_131", EN_IP_AUD, 3, 0, 0),
	GATE(AUD_CWK_AUD_UAWT, "cwk_aud_uawt", "dout_acwk_aud_131",
			EN_IP_AUD, 4, 0, 0),
};

static const stwuct samsung_cmu_info aud_cmu __initconst = {
	.mux_cwks	= aud_mux_cwks,
	.nw_mux_cwks	= AWWAY_SIZE(aud_mux_cwks),
	.div_cwks	= aud_div_cwks,
	.nw_div_cwks	= AWWAY_SIZE(aud_div_cwks),
	.gate_cwks	= aud_gate_cwks,
	.nw_gate_cwks	= AWWAY_SIZE(aud_gate_cwks),
	.nw_cwk_ids	= CWKS_NW_AUD,
	.cwk_wegs	= aud_cwk_wegs,
	.nw_cwk_wegs	= AWWAY_SIZE(aud_cwk_wegs),
};

static void __init exynos5260_cwk_aud_init(stwuct device_node *np)
{
	samsung_cmu_wegistew_one(np, &aud_cmu);
}

CWK_OF_DECWAWE(exynos5260_cwk_aud, "samsung,exynos5260-cwock-aud",
		exynos5260_cwk_aud_init);


/* CMU_DISP */

static const unsigned wong disp_cwk_wegs[] __initconst = {
	MUX_SEW_DISP0,
	MUX_SEW_DISP1,
	MUX_SEW_DISP2,
	MUX_SEW_DISP3,
	MUX_SEW_DISP4,
	DIV_DISP,
	EN_ACWK_DISP,
	EN_PCWK_DISP,
	EN_SCWK_DISP0,
	EN_SCWK_DISP1,
	EN_IP_DISP,
	EN_IP_DISP_BUS,
};

PNAME(mout_phycwk_dptx_phy_ch3_txd_cwk_usew_p) = {"fin_pww",
			"phycwk_dptx_phy_ch3_txd_cwk"};
PNAME(mout_phycwk_dptx_phy_ch2_txd_cwk_usew_p) = {"fin_pww",
			"phycwk_dptx_phy_ch2_txd_cwk"};
PNAME(mout_phycwk_dptx_phy_ch1_txd_cwk_usew_p) = {"fin_pww",
			"phycwk_dptx_phy_ch1_txd_cwk"};
PNAME(mout_phycwk_dptx_phy_ch0_txd_cwk_usew_p) = {"fin_pww",
			"phycwk_dptx_phy_ch0_txd_cwk"};
PNAME(mout_acwk_disp_222_usew_p) = {"fin_pww", "dout_acwk_disp_222"};
PNAME(mout_scwk_disp_pixew_usew_p) = {"fin_pww", "dout_scwk_disp_pixew"};
PNAME(mout_acwk_disp_333_usew_p) = {"fin_pww", "dout_acwk_disp_333"};
PNAME(mout_phycwk_hdmi_phy_tmds_cwko_usew_p) = {"fin_pww",
			"phycwk_hdmi_phy_tmds_cwko"};
PNAME(mout_phycwk_hdmi_phy_wef_cwko_usew_p) = {"fin_pww",
			"phycwk_hdmi_phy_wef_cwko"};
PNAME(mout_phycwk_hdmi_phy_pixew_cwko_usew_p) = {"fin_pww",
			"phycwk_hdmi_phy_pixew_cwko"};
PNAME(mout_phycwk_hdmi_wink_o_tmds_cwkhi_usew_p) = {"fin_pww",
			"phycwk_hdmi_wink_o_tmds_cwkhi"};
PNAME(mout_phycwk_mipi_dphy_4w_m_txbyte_cwkhs_p) = {"fin_pww",
			"phycwk_mipi_dphy_4w_m_txbyte_cwkhs"};
PNAME(mout_phycwk_dptx_phy_o_wef_cwk_24m_usew_p) = {"fin_pww",
			"phycwk_dptx_phy_o_wef_cwk_24m"};
PNAME(mout_phycwk_dptx_phy_cwk_div2_usew_p) = {"fin_pww",
			"phycwk_dptx_phy_cwk_div2"};
PNAME(mout_scwk_hdmi_pixew_p) = {"mout_scwk_disp_pixew_usew",
			"mout_acwk_disp_222_usew"};
PNAME(mout_phycwk_mipi_dphy_4wmwxcwk_esc0_usew_p) = {"fin_pww",
			"phycwk_mipi_dphy_4w_m_wxcwkesc0"};
PNAME(mout_scwk_hdmi_spdif_p) = {"fin_pww", "iocwk_spdif_extcwk",
			"dout_acwk_pewi_aud", "phycwk_hdmi_phy_wef_cko"};

static const stwuct samsung_mux_cwock disp_mux_cwks[] __initconst = {
	MUX(DISP_MOUT_ACWK_DISP_333_USEW, "mout_acwk_disp_333_usew",
			mout_acwk_disp_333_usew_p,
			MUX_SEW_DISP0, 0, 1),
	MUX(DISP_MOUT_SCWK_DISP_PIXEW_USEW, "mout_scwk_disp_pixew_usew",
			mout_scwk_disp_pixew_usew_p,
			MUX_SEW_DISP0, 4, 1),
	MUX(DISP_MOUT_ACWK_DISP_222_USEW, "mout_acwk_disp_222_usew",
			mout_acwk_disp_222_usew_p,
			MUX_SEW_DISP0, 8, 1),
	MUX(DISP_MOUT_PHYCWK_DPTX_PHY_CH0_TXD_CWK_USEW,
			"mout_phycwk_dptx_phy_ch0_txd_cwk_usew",
			mout_phycwk_dptx_phy_ch0_txd_cwk_usew_p,
			MUX_SEW_DISP0, 16, 1),
	MUX(DISP_MOUT_PHYCWK_DPTX_PHY_CH1_TXD_CWK_USEW,
			"mout_phycwk_dptx_phy_ch1_txd_cwk_usew",
			mout_phycwk_dptx_phy_ch1_txd_cwk_usew_p,
			MUX_SEW_DISP0, 20, 1),
	MUX(DISP_MOUT_PHYCWK_DPTX_PHY_CH2_TXD_CWK_USEW,
			"mout_phycwk_dptx_phy_ch2_txd_cwk_usew",
			mout_phycwk_dptx_phy_ch2_txd_cwk_usew_p,
			MUX_SEW_DISP0, 24, 1),
	MUX(DISP_MOUT_PHYCWK_DPTX_PHY_CH3_TXD_CWK_USEW,
			"mout_phycwk_dptx_phy_ch3_txd_cwk_usew",
			mout_phycwk_dptx_phy_ch3_txd_cwk_usew_p,
			MUX_SEW_DISP0, 28, 1),

	MUX(DISP_MOUT_PHYCWK_DPTX_PHY_CWK_DIV2_USEW,
			"mout_phycwk_dptx_phy_cwk_div2_usew",
			mout_phycwk_dptx_phy_cwk_div2_usew_p,
			MUX_SEW_DISP1, 0, 1),
	MUX(DISP_MOUT_PHYCWK_DPTX_PHY_O_WEF_CWK_24M_USEW,
			"mout_phycwk_dptx_phy_o_wef_cwk_24m_usew",
			mout_phycwk_dptx_phy_o_wef_cwk_24m_usew_p,
			MUX_SEW_DISP1, 4, 1),
	MUX(DISP_MOUT_PHYCWK_MIPI_DPHY_4W_M_TXBYTE_CWKHS,
			"mout_phycwk_mipi_dphy_4w_m_txbyte_cwkhs",
			mout_phycwk_mipi_dphy_4w_m_txbyte_cwkhs_p,
			MUX_SEW_DISP1, 8, 1),
	MUX(DISP_MOUT_PHYCWK_HDMI_WINK_O_TMDS_CWKHI_USEW,
			"mout_phycwk_hdmi_wink_o_tmds_cwkhi_usew",
			mout_phycwk_hdmi_wink_o_tmds_cwkhi_usew_p,
			MUX_SEW_DISP1, 16, 1),
	MUX(DISP_MOUT_HDMI_PHY_PIXEW,
			"mout_phycwk_hdmi_phy_pixew_cwko_usew",
			mout_phycwk_hdmi_phy_pixew_cwko_usew_p,
			MUX_SEW_DISP1, 20, 1),
	MUX(DISP_MOUT_PHYCWK_HDMI_PHY_WEF_CWKO_USEW,
			"mout_phycwk_hdmi_phy_wef_cwko_usew",
			mout_phycwk_hdmi_phy_wef_cwko_usew_p,
			MUX_SEW_DISP1, 24, 1),
	MUX(DISP_MOUT_PHYCWK_HDMI_PHY_TMDS_CWKO_USEW,
			"mout_phycwk_hdmi_phy_tmds_cwko_usew",
			mout_phycwk_hdmi_phy_tmds_cwko_usew_p,
			MUX_SEW_DISP1, 28, 1),

	MUX(DISP_MOUT_PHYCWK_MIPI_DPHY_4WMWXCWK_ESC0_USEW,
			"mout_phycwk_mipi_dphy_4wmwxcwk_esc0_usew",
			mout_phycwk_mipi_dphy_4wmwxcwk_esc0_usew_p,
			MUX_SEW_DISP2, 0, 1),
	MUX(DISP_MOUT_SCWK_HDMI_PIXEW, "mout_scwk_hdmi_pixew",
			mout_scwk_hdmi_pixew_p,
			MUX_SEW_DISP2, 4, 1),

	MUX(DISP_MOUT_SCWK_HDMI_SPDIF, "mout_scwk_hdmi_spdif",
			mout_scwk_hdmi_spdif_p,
			MUX_SEW_DISP4, 4, 2),
};

static const stwuct samsung_div_cwock disp_div_cwks[] __initconst = {
	DIV(DISP_DOUT_PCWK_DISP_111, "dout_pcwk_disp_111",
			"mout_acwk_disp_222_usew",
			DIV_DISP, 8, 4),
	DIV(DISP_DOUT_SCWK_FIMD1_EXTCWKPWW, "dout_scwk_fimd1_extcwkpww",
			"mout_scwk_disp_pixew_usew",
			DIV_DISP, 12, 4),
	DIV(DISP_DOUT_SCWK_HDMI_PHY_PIXEW_CWKI,
			"dout_scwk_hdmi_phy_pixew_cwki",
			"mout_scwk_hdmi_pixew",
			DIV_DISP, 16, 4),
};

static const stwuct samsung_gate_cwock disp_gate_cwks[] __initconst = {
	GATE(DISP_MOUT_HDMI_PHY_PIXEW_USEW, "scwk_hdmi_wink_i_pixew",
			"mout_phycwk_hdmi_phy_pixew_cwko_usew",
			EN_SCWK_DISP0, 26, CWK_SET_WATE_PAWENT, 0),
	GATE(DISP_SCWK_PIXEW, "scwk_hdmi_phy_pixew_cwki",
			"dout_scwk_hdmi_phy_pixew_cwki",
			EN_SCWK_DISP0, 29, CWK_SET_WATE_PAWENT, 0),

	GATE(DISP_CWK_DP, "cwk_dptx_wink", "mout_acwk_disp_222_usew",
			EN_IP_DISP, 4, 0, 0),
	GATE(DISP_CWK_DPPHY, "cwk_dptx_phy", "mout_acwk_disp_222_usew",
			EN_IP_DISP, 5, 0, 0),
	GATE(DISP_CWK_DSIM1, "cwk_dsim1", "mout_acwk_disp_222_usew",
			EN_IP_DISP, 6, 0, 0),
	GATE(DISP_CWK_FIMD1, "cwk_fimd1", "mout_acwk_disp_222_usew",
			EN_IP_DISP, 7, 0, 0),
	GATE(DISP_CWK_HDMI, "cwk_hdmi", "mout_acwk_disp_222_usew",
			EN_IP_DISP, 8, 0, 0),
	GATE(DISP_CWK_HDMIPHY, "cwk_hdmiphy", "mout_acwk_disp_222_usew",
			EN_IP_DISP, 9, 0, 0),
	GATE(DISP_CWK_MIPIPHY, "cwk_mipi_dphy", "mout_acwk_disp_222_usew",
			EN_IP_DISP, 10, 0, 0),
	GATE(DISP_CWK_MIXEW, "cwk_mixew", "mout_acwk_disp_222_usew",
			EN_IP_DISP, 11, 0, 0),
	GATE(DISP_CWK_PIXEW_DISP, "cwk_pixew_disp", "mout_acwk_disp_222_usew",
			EN_IP_DISP, 12, CWK_IGNOWE_UNUSED, 0),
	GATE(DISP_CWK_PIXEW_MIXEW, "cwk_pixew_mixew", "mout_acwk_disp_222_usew",
			EN_IP_DISP, 13, CWK_IGNOWE_UNUSED, 0),
	GATE(DISP_CWK_SMMU_FIMD1M0, "cwk_smmu3_fimd1m0",
			"mout_acwk_disp_222_usew",
			EN_IP_DISP, 22, 0, 0),
	GATE(DISP_CWK_SMMU_FIMD1M1, "cwk_smmu3_fimd1m1",
			"mout_acwk_disp_222_usew",
			EN_IP_DISP, 23, 0, 0),
	GATE(DISP_CWK_SMMU_TV, "cwk_smmu3_tv", "mout_acwk_disp_222_usew",
			EN_IP_DISP, 25, 0, 0),
};

static const stwuct samsung_cmu_info disp_cmu __initconst = {
	.mux_cwks	= disp_mux_cwks,
	.nw_mux_cwks	= AWWAY_SIZE(disp_mux_cwks),
	.div_cwks	= disp_div_cwks,
	.nw_div_cwks	= AWWAY_SIZE(disp_div_cwks),
	.gate_cwks	= disp_gate_cwks,
	.nw_gate_cwks	= AWWAY_SIZE(disp_gate_cwks),
	.nw_cwk_ids	= CWKS_NW_DISP,
	.cwk_wegs	= disp_cwk_wegs,
	.nw_cwk_wegs	= AWWAY_SIZE(disp_cwk_wegs),
};

static void __init exynos5260_cwk_disp_init(stwuct device_node *np)
{
	samsung_cmu_wegistew_one(np, &disp_cmu);
}

CWK_OF_DECWAWE(exynos5260_cwk_disp, "samsung,exynos5260-cwock-disp",
		exynos5260_cwk_disp_init);


/* CMU_EGW */

static const unsigned wong egw_cwk_wegs[] __initconst = {
	EGW_PWW_WOCK,
	EGW_PWW_CON0,
	EGW_PWW_CON1,
	EGW_PWW_FWEQ_DET,
	MUX_SEW_EGW,
	MUX_ENABWE_EGW,
	DIV_EGW,
	DIV_EGW_PWW_FDET,
	EN_ACWK_EGW,
	EN_PCWK_EGW,
	EN_SCWK_EGW,
};

PNAME(mout_egw_b_p) = {"mout_egw_pww", "dout_bus_pww"};
PNAME(mout_egw_pww_p) = {"fin_pww", "fout_egw_pww"};

static const stwuct samsung_mux_cwock egw_mux_cwks[] __initconst = {
	MUX(EGW_MOUT_EGW_PWW, "mout_egw_pww", mout_egw_pww_p,
			MUX_SEW_EGW, 4, 1),
	MUX(EGW_MOUT_EGW_B, "mout_egw_b", mout_egw_b_p, MUX_SEW_EGW, 16, 1),
};

static const stwuct samsung_div_cwock egw_div_cwks[] __initconst = {
	DIV(EGW_DOUT_EGW1, "dout_egw1", "mout_egw_b", DIV_EGW, 0, 3),
	DIV(EGW_DOUT_EGW2, "dout_egw2", "dout_egw1", DIV_EGW, 4, 3),
	DIV(EGW_DOUT_ACWK_EGW, "dout_acwk_egw", "dout_egw2", DIV_EGW, 8, 3),
	DIV(EGW_DOUT_PCWK_EGW, "dout_pcwk_egw", "dout_egw_atcwk",
			DIV_EGW, 12, 3),
	DIV(EGW_DOUT_EGW_ATCWK, "dout_egw_atcwk", "dout_egw2", DIV_EGW, 16, 3),
	DIV(EGW_DOUT_EGW_PCWK_DBG, "dout_egw_pcwk_dbg", "dout_egw_atcwk",
			DIV_EGW, 20, 3),
	DIV(EGW_DOUT_EGW_PWW, "dout_egw_pww", "mout_egw_b", DIV_EGW, 24, 3),
};

static const stwuct samsung_pww_cwock egw_pww_cwks[] __initconst = {
	PWW(pww_2550xx, EGW_FOUT_EGW_PWW, "fout_egw_pww", "fin_pww",
		EGW_PWW_WOCK, EGW_PWW_CON0,
		pww2550_24mhz_tbw),
};

static const stwuct samsung_cmu_info egw_cmu __initconst = {
	.pww_cwks	= egw_pww_cwks,
	.nw_pww_cwks	= AWWAY_SIZE(egw_pww_cwks),
	.mux_cwks	= egw_mux_cwks,
	.nw_mux_cwks	= AWWAY_SIZE(egw_mux_cwks),
	.div_cwks	= egw_div_cwks,
	.nw_div_cwks	= AWWAY_SIZE(egw_div_cwks),
	.nw_cwk_ids	= CWKS_NW_EGW,
	.cwk_wegs	= egw_cwk_wegs,
	.nw_cwk_wegs	= AWWAY_SIZE(egw_cwk_wegs),
};

static void __init exynos5260_cwk_egw_init(stwuct device_node *np)
{
	samsung_cmu_wegistew_one(np, &egw_cmu);
}

CWK_OF_DECWAWE(exynos5260_cwk_egw, "samsung,exynos5260-cwock-egw",
		exynos5260_cwk_egw_init);


/* CMU_FSYS */

static const unsigned wong fsys_cwk_wegs[] __initconst = {
	MUX_SEW_FSYS0,
	MUX_SEW_FSYS1,
	EN_ACWK_FSYS,
	EN_ACWK_FSYS_SECUWE_WTIC,
	EN_ACWK_FSYS_SECUWE_SMMU_WTIC,
	EN_SCWK_FSYS,
	EN_IP_FSYS,
	EN_IP_FSYS_SECUWE_WTIC,
	EN_IP_FSYS_SECUWE_SMMU_WTIC,
};

PNAME(mout_phycwk_usbhost20_phycwk_usew_p) = {"fin_pww",
			"phycwk_usbhost20_phy_phycwock"};
PNAME(mout_phycwk_usbhost20_fweecwk_usew_p) = {"fin_pww",
			"phycwk_usbhost20_phy_fweecwk"};
PNAME(mout_phycwk_usbhost20_cwk48mohci_usew_p) = {"fin_pww",
			"phycwk_usbhost20_phy_cwk48mohci"};
PNAME(mout_phycwk_usbdwd30_pipe_pcwk_usew_p) = {"fin_pww",
			"phycwk_usbdwd30_udwd30_pipe_pcwk"};
PNAME(mout_phycwk_usbdwd30_phycwock_usew_p) = {"fin_pww",
			"phycwk_usbdwd30_udwd30_phycwock"};

static const stwuct samsung_mux_cwock fsys_mux_cwks[] __initconst = {
	MUX(FSYS_MOUT_PHYCWK_USBDWD30_PHYCWOCK_USEW,
			"mout_phycwk_usbdwd30_phycwock_usew",
			mout_phycwk_usbdwd30_phycwock_usew_p,
			MUX_SEW_FSYS1, 0, 1),
	MUX(FSYS_MOUT_PHYCWK_USBDWD30_PIPE_PCWK_USEW,
			"mout_phycwk_usbdwd30_pipe_pcwk_usew",
			mout_phycwk_usbdwd30_pipe_pcwk_usew_p,
			MUX_SEW_FSYS1, 4, 1),
	MUX(FSYS_MOUT_PHYCWK_USBHOST20_CWK48MOHCI_USEW,
			"mout_phycwk_usbhost20_cwk48mohci_usew",
			mout_phycwk_usbhost20_cwk48mohci_usew_p,
			MUX_SEW_FSYS1, 8, 1),
	MUX(FSYS_MOUT_PHYCWK_USBHOST20_FWEECWK_USEW,
			"mout_phycwk_usbhost20_fweecwk_usew",
			mout_phycwk_usbhost20_fweecwk_usew_p,
			MUX_SEW_FSYS1, 12, 1),
	MUX(FSYS_MOUT_PHYCWK_USBHOST20_PHYCWK_USEW,
			"mout_phycwk_usbhost20_phycwk_usew",
			mout_phycwk_usbhost20_phycwk_usew_p,
			MUX_SEW_FSYS1, 16, 1),
};

static const stwuct samsung_gate_cwock fsys_gate_cwks[] __initconst = {
	GATE(FSYS_PHYCWK_USBHOST20, "phycwk_usbhost20_phycwock",
			"mout_phycwk_usbdwd30_phycwock_usew",
			EN_SCWK_FSYS, 1, 0, 0),
	GATE(FSYS_PHYCWK_USBDWD30, "phycwk_usbdwd30_udwd30_phycwock_g",
			"mout_phycwk_usbdwd30_phycwock_usew",
			EN_SCWK_FSYS, 7, 0, 0),

	GATE(FSYS_CWK_MMC0, "cwk_mmc0", "dout_acwk_fsys_200",
			EN_IP_FSYS, 6, 0, 0),
	GATE(FSYS_CWK_MMC1, "cwk_mmc1", "dout_acwk_fsys_200",
			EN_IP_FSYS, 7, 0, 0),
	GATE(FSYS_CWK_MMC2, "cwk_mmc2", "dout_acwk_fsys_200",
			EN_IP_FSYS, 8, 0, 0),
	GATE(FSYS_CWK_PDMA, "cwk_pdma", "dout_acwk_fsys_200",
			EN_IP_FSYS, 9, 0, 0),
	GATE(FSYS_CWK_SWOMC, "cwk_swomc", "dout_acwk_fsys_200",
			EN_IP_FSYS, 13, 0, 0),
	GATE(FSYS_CWK_USBDWD30, "cwk_usbdwd30", "dout_acwk_fsys_200",
			EN_IP_FSYS, 14, 0, 0),
	GATE(FSYS_CWK_USBHOST20, "cwk_usbhost20", "dout_acwk_fsys_200",
			EN_IP_FSYS, 15, 0, 0),
	GATE(FSYS_CWK_USBWINK, "cwk_usbwink", "dout_acwk_fsys_200",
			EN_IP_FSYS, 18, 0, 0),
	GATE(FSYS_CWK_TSI, "cwk_tsi", "dout_acwk_fsys_200",
			EN_IP_FSYS, 20, 0, 0),

	GATE(FSYS_CWK_WTIC, "cwk_wtic", "dout_acwk_fsys_200",
			EN_IP_FSYS_SECUWE_WTIC, 11, 0, 0),
	GATE(FSYS_CWK_SMMU_WTIC, "cwk_smmu_wtic", "dout_acwk_fsys_200",
			EN_IP_FSYS_SECUWE_SMMU_WTIC, 12, 0, 0),
};

static const stwuct samsung_cmu_info fsys_cmu __initconst = {
	.mux_cwks	= fsys_mux_cwks,
	.nw_mux_cwks	= AWWAY_SIZE(fsys_mux_cwks),
	.gate_cwks	= fsys_gate_cwks,
	.nw_gate_cwks	= AWWAY_SIZE(fsys_gate_cwks),
	.nw_cwk_ids	= CWKS_NW_FSYS,
	.cwk_wegs	= fsys_cwk_wegs,
	.nw_cwk_wegs	= AWWAY_SIZE(fsys_cwk_wegs),
};

static void __init exynos5260_cwk_fsys_init(stwuct device_node *np)
{
	samsung_cmu_wegistew_one(np, &fsys_cmu);
}

CWK_OF_DECWAWE(exynos5260_cwk_fsys, "samsung,exynos5260-cwock-fsys",
		exynos5260_cwk_fsys_init);


/* CMU_G2D */

static const unsigned wong g2d_cwk_wegs[] __initconst = {
	MUX_SEW_G2D,
	MUX_STAT_G2D,
	DIV_G2D,
	EN_ACWK_G2D,
	EN_ACWK_G2D_SECUWE_SSS,
	EN_ACWK_G2D_SECUWE_SWIM_SSS,
	EN_ACWK_G2D_SECUWE_SMMU_SWIM_SSS,
	EN_ACWK_G2D_SECUWE_SMMU_SSS,
	EN_ACWK_G2D_SECUWE_SMMU_MDMA,
	EN_ACWK_G2D_SECUWE_SMMU_G2D,
	EN_PCWK_G2D,
	EN_PCWK_G2D_SECUWE_SMMU_SWIM_SSS,
	EN_PCWK_G2D_SECUWE_SMMU_SSS,
	EN_PCWK_G2D_SECUWE_SMMU_MDMA,
	EN_PCWK_G2D_SECUWE_SMMU_G2D,
	EN_IP_G2D,
	EN_IP_G2D_SECUWE_SSS,
	EN_IP_G2D_SECUWE_SWIM_SSS,
	EN_IP_G2D_SECUWE_SMMU_SWIM_SSS,
	EN_IP_G2D_SECUWE_SMMU_SSS,
	EN_IP_G2D_SECUWE_SMMU_MDMA,
	EN_IP_G2D_SECUWE_SMMU_G2D,
};

PNAME(mout_acwk_g2d_333_usew_p) = {"fin_pww", "dout_acwk_g2d_333"};

static const stwuct samsung_mux_cwock g2d_mux_cwks[] __initconst = {
	MUX(G2D_MOUT_ACWK_G2D_333_USEW, "mout_acwk_g2d_333_usew",
			mout_acwk_g2d_333_usew_p,
			MUX_SEW_G2D, 0, 1),
};

static const stwuct samsung_div_cwock g2d_div_cwks[] __initconst = {
	DIV(G2D_DOUT_PCWK_G2D_83, "dout_pcwk_g2d_83", "mout_acwk_g2d_333_usew",
			DIV_G2D, 0, 3),
};

static const stwuct samsung_gate_cwock g2d_gate_cwks[] __initconst = {
	GATE(G2D_CWK_G2D, "cwk_g2d", "mout_acwk_g2d_333_usew",
			EN_IP_G2D, 4, 0, 0),
	GATE(G2D_CWK_JPEG, "cwk_jpeg", "mout_acwk_g2d_333_usew",
			EN_IP_G2D, 5, 0, 0),
	GATE(G2D_CWK_MDMA, "cwk_mdma", "mout_acwk_g2d_333_usew",
			EN_IP_G2D, 6, 0, 0),
	GATE(G2D_CWK_SMMU3_JPEG, "cwk_smmu3_jpeg", "mout_acwk_g2d_333_usew",
			EN_IP_G2D, 16, 0, 0),

	GATE(G2D_CWK_SSS, "cwk_sss", "mout_acwk_g2d_333_usew",
			EN_IP_G2D_SECUWE_SSS, 17, 0, 0),

	GATE(G2D_CWK_SWIM_SSS, "cwk_swim_sss", "mout_acwk_g2d_333_usew",
			EN_IP_G2D_SECUWE_SWIM_SSS, 11, 0, 0),

	GATE(G2D_CWK_SMMU_SWIM_SSS, "cwk_smmu_swim_sss",
			"mout_acwk_g2d_333_usew",
			EN_IP_G2D_SECUWE_SMMU_SWIM_SSS, 13, 0, 0),

	GATE(G2D_CWK_SMMU_SSS, "cwk_smmu_sss", "mout_acwk_g2d_333_usew",
			EN_IP_G2D_SECUWE_SMMU_SSS, 14, 0, 0),

	GATE(G2D_CWK_SMMU_MDMA, "cwk_smmu_mdma", "mout_acwk_g2d_333_usew",
			EN_IP_G2D_SECUWE_SMMU_MDMA, 12, 0, 0),

	GATE(G2D_CWK_SMMU3_G2D, "cwk_smmu3_g2d", "mout_acwk_g2d_333_usew",
			EN_IP_G2D_SECUWE_SMMU_G2D, 15, 0, 0),
};

static const stwuct samsung_cmu_info g2d_cmu __initconst = {
	.mux_cwks	= g2d_mux_cwks,
	.nw_mux_cwks	= AWWAY_SIZE(g2d_mux_cwks),
	.div_cwks	= g2d_div_cwks,
	.nw_div_cwks	= AWWAY_SIZE(g2d_div_cwks),
	.gate_cwks	= g2d_gate_cwks,
	.nw_gate_cwks	= AWWAY_SIZE(g2d_gate_cwks),
	.nw_cwk_ids	= CWKS_NW_G2D,
	.cwk_wegs	= g2d_cwk_wegs,
	.nw_cwk_wegs	= AWWAY_SIZE(g2d_cwk_wegs),
};

static void __init exynos5260_cwk_g2d_init(stwuct device_node *np)
{
	samsung_cmu_wegistew_one(np, &g2d_cmu);
}

CWK_OF_DECWAWE(exynos5260_cwk_g2d, "samsung,exynos5260-cwock-g2d",
		exynos5260_cwk_g2d_init);


/* CMU_G3D */

static const unsigned wong g3d_cwk_wegs[] __initconst = {
	G3D_PWW_WOCK,
	G3D_PWW_CON0,
	G3D_PWW_CON1,
	G3D_PWW_FDET,
	MUX_SEW_G3D,
	DIV_G3D,
	DIV_G3D_PWW_FDET,
	EN_ACWK_G3D,
	EN_PCWK_G3D,
	EN_SCWK_G3D,
	EN_IP_G3D,
};

PNAME(mout_g3d_pww_p) = {"fin_pww", "fout_g3d_pww"};

static const stwuct samsung_mux_cwock g3d_mux_cwks[] __initconst = {
	MUX(G3D_MOUT_G3D_PWW, "mout_g3d_pww", mout_g3d_pww_p,
			MUX_SEW_G3D, 0, 1),
};

static const stwuct samsung_div_cwock g3d_div_cwks[] __initconst = {
	DIV(G3D_DOUT_PCWK_G3D, "dout_pcwk_g3d", "dout_acwk_g3d", DIV_G3D, 0, 3),
	DIV(G3D_DOUT_ACWK_G3D, "dout_acwk_g3d", "mout_g3d_pww", DIV_G3D, 4, 3),
};

static const stwuct samsung_gate_cwock g3d_gate_cwks[] __initconst = {
	GATE(G3D_CWK_G3D, "cwk_g3d", "dout_acwk_g3d", EN_IP_G3D, 2, 0, 0),
	GATE(G3D_CWK_G3D_HPM, "cwk_g3d_hpm", "dout_acwk_g3d",
			EN_IP_G3D, 3, 0, 0),
};

static const stwuct samsung_pww_cwock g3d_pww_cwks[] __initconst = {
	PWW(pww_2550, G3D_FOUT_G3D_PWW, "fout_g3d_pww", "fin_pww",
		G3D_PWW_WOCK, G3D_PWW_CON0,
		pww2550_24mhz_tbw),
};

static const stwuct samsung_cmu_info g3d_cmu __initconst = {
	.pww_cwks	= g3d_pww_cwks,
	.nw_pww_cwks	= AWWAY_SIZE(g3d_pww_cwks),
	.mux_cwks	= g3d_mux_cwks,
	.nw_mux_cwks	= AWWAY_SIZE(g3d_mux_cwks),
	.div_cwks	= g3d_div_cwks,
	.nw_div_cwks	= AWWAY_SIZE(g3d_div_cwks),
	.gate_cwks	= g3d_gate_cwks,
	.nw_gate_cwks	= AWWAY_SIZE(g3d_gate_cwks),
	.nw_cwk_ids	= CWKS_NW_G3D,
	.cwk_wegs	= g3d_cwk_wegs,
	.nw_cwk_wegs	= AWWAY_SIZE(g3d_cwk_wegs),
};

static void __init exynos5260_cwk_g3d_init(stwuct device_node *np)
{
	samsung_cmu_wegistew_one(np, &g3d_cmu);
}

CWK_OF_DECWAWE(exynos5260_cwk_g3d, "samsung,exynos5260-cwock-g3d",
		exynos5260_cwk_g3d_init);


/* CMU_GSCW */

static const unsigned wong gscw_cwk_wegs[] __initconst = {
	MUX_SEW_GSCW,
	DIV_GSCW,
	EN_ACWK_GSCW,
	EN_ACWK_GSCW_FIMC,
	EN_ACWK_GSCW_SECUWE_SMMU_GSCW0,
	EN_ACWK_GSCW_SECUWE_SMMU_GSCW1,
	EN_ACWK_GSCW_SECUWE_SMMU_MSCW0,
	EN_ACWK_GSCW_SECUWE_SMMU_MSCW1,
	EN_PCWK_GSCW,
	EN_PCWK_GSCW_FIMC,
	EN_PCWK_GSCW_SECUWE_SMMU_GSCW0,
	EN_PCWK_GSCW_SECUWE_SMMU_GSCW1,
	EN_PCWK_GSCW_SECUWE_SMMU_MSCW0,
	EN_PCWK_GSCW_SECUWE_SMMU_MSCW1,
	EN_SCWK_GSCW,
	EN_SCWK_GSCW_FIMC,
	EN_IP_GSCW,
	EN_IP_GSCW_FIMC,
	EN_IP_GSCW_SECUWE_SMMU_GSCW0,
	EN_IP_GSCW_SECUWE_SMMU_GSCW1,
	EN_IP_GSCW_SECUWE_SMMU_MSCW0,
	EN_IP_GSCW_SECUWE_SMMU_MSCW1,
};

PNAME(mout_acwk_gscw_333_usew_p) = {"fin_pww", "dout_acwk_gscw_333"};
PNAME(mout_acwk_m2m_400_usew_p) = {"fin_pww", "dout_acwk_gscw_400"};
PNAME(mout_acwk_gscw_fimc_usew_p) = {"fin_pww", "dout_acwk_gscw_400"};
PNAME(mout_acwk_csis_p) = {"dout_acwk_csis_200", "mout_acwk_gscw_fimc_usew"};

static const stwuct samsung_mux_cwock gscw_mux_cwks[] __initconst = {
	MUX(GSCW_MOUT_ACWK_GSCW_333_USEW, "mout_acwk_gscw_333_usew",
			mout_acwk_gscw_333_usew_p,
			MUX_SEW_GSCW, 0, 1),
	MUX(GSCW_MOUT_ACWK_M2M_400_USEW, "mout_acwk_m2m_400_usew",
			mout_acwk_m2m_400_usew_p,
			MUX_SEW_GSCW, 4, 1),
	MUX(GSCW_MOUT_ACWK_GSCW_FIMC_USEW, "mout_acwk_gscw_fimc_usew",
			mout_acwk_gscw_fimc_usew_p,
			MUX_SEW_GSCW, 8, 1),
	MUX(GSCW_MOUT_ACWK_CSIS, "mout_acwk_csis", mout_acwk_csis_p,
			MUX_SEW_GSCW, 24, 1),
};

static const stwuct samsung_div_cwock gscw_div_cwks[] __initconst = {
	DIV(GSCW_DOUT_PCWK_M2M_100, "dout_pcwk_m2m_100",
			"mout_acwk_m2m_400_usew",
			DIV_GSCW, 0, 3),
	DIV(GSCW_DOUT_ACWK_CSIS_200, "dout_acwk_csis_200",
			"mout_acwk_m2m_400_usew",
			DIV_GSCW, 4, 3),
};

static const stwuct samsung_gate_cwock gscw_gate_cwks[] __initconst = {
	GATE(GSCW_SCWK_CSIS0_WWAP, "scwk_csis0_wwap", "dout_acwk_csis_200",
			EN_SCWK_GSCW_FIMC, 0, CWK_SET_WATE_PAWENT, 0),
	GATE(GSCW_SCWK_CSIS1_WWAP, "scwk_csis1_wwap", "dout_acwk_csis_200",
			EN_SCWK_GSCW_FIMC, 1, CWK_SET_WATE_PAWENT, 0),

	GATE(GSCW_CWK_GSCW0, "cwk_gscw0", "mout_acwk_gscw_333_usew",
			EN_IP_GSCW, 2, 0, 0),
	GATE(GSCW_CWK_GSCW1, "cwk_gscw1", "mout_acwk_gscw_333_usew",
			EN_IP_GSCW, 3, 0, 0),
	GATE(GSCW_CWK_MSCW0, "cwk_mscw0", "mout_acwk_gscw_333_usew",
			EN_IP_GSCW, 4, 0, 0),
	GATE(GSCW_CWK_MSCW1, "cwk_mscw1", "mout_acwk_gscw_333_usew",
			EN_IP_GSCW, 5, 0, 0),
	GATE(GSCW_CWK_PIXEW_GSCW0, "cwk_pixew_gscw0",
			"mout_acwk_gscw_333_usew",
			EN_IP_GSCW, 8, 0, 0),
	GATE(GSCW_CWK_PIXEW_GSCW1, "cwk_pixew_gscw1",
			"mout_acwk_gscw_333_usew",
			EN_IP_GSCW, 9, 0, 0),

	GATE(GSCW_CWK_SMMU3_WITE_A, "cwk_smmu3_wite_a",
			"mout_acwk_gscw_fimc_usew",
			EN_IP_GSCW_FIMC, 5, 0, 0),
	GATE(GSCW_CWK_SMMU3_WITE_B, "cwk_smmu3_wite_b",
			"mout_acwk_gscw_fimc_usew",
			EN_IP_GSCW_FIMC, 6, 0, 0),
	GATE(GSCW_CWK_SMMU3_WITE_D, "cwk_smmu3_wite_d",
			"mout_acwk_gscw_fimc_usew",
			EN_IP_GSCW_FIMC, 7, 0, 0),
	GATE(GSCW_CWK_CSIS0, "cwk_csis0", "mout_acwk_gscw_fimc_usew",
			EN_IP_GSCW_FIMC, 8, 0, 0),
	GATE(GSCW_CWK_CSIS1, "cwk_csis1", "mout_acwk_gscw_fimc_usew",
			EN_IP_GSCW_FIMC, 9, 0, 0),
	GATE(GSCW_CWK_FIMC_WITE_A, "cwk_fimc_wite_a",
			"mout_acwk_gscw_fimc_usew",
			EN_IP_GSCW_FIMC, 10, 0, 0),
	GATE(GSCW_CWK_FIMC_WITE_B, "cwk_fimc_wite_b",
			"mout_acwk_gscw_fimc_usew",
			EN_IP_GSCW_FIMC, 11, 0, 0),
	GATE(GSCW_CWK_FIMC_WITE_D, "cwk_fimc_wite_d",
			"mout_acwk_gscw_fimc_usew",
			EN_IP_GSCW_FIMC, 12, 0, 0),

	GATE(GSCW_CWK_SMMU3_GSCW0, "cwk_smmu3_gscw0",
			"mout_acwk_gscw_333_usew",
			EN_IP_GSCW_SECUWE_SMMU_GSCW0, 17, 0, 0),
	GATE(GSCW_CWK_SMMU3_GSCW1, "cwk_smmu3_gscw1", "mout_acwk_gscw_333_usew",
			EN_IP_GSCW_SECUWE_SMMU_GSCW1, 18, 0, 0),
	GATE(GSCW_CWK_SMMU3_MSCW0, "cwk_smmu3_mscw0",
			"mout_acwk_m2m_400_usew",
			EN_IP_GSCW_SECUWE_SMMU_MSCW0, 19, 0, 0),
	GATE(GSCW_CWK_SMMU3_MSCW1, "cwk_smmu3_mscw1",
			"mout_acwk_m2m_400_usew",
			EN_IP_GSCW_SECUWE_SMMU_MSCW1, 20, 0, 0),
};

static const stwuct samsung_cmu_info gscw_cmu __initconst = {
	.mux_cwks	= gscw_mux_cwks,
	.nw_mux_cwks	= AWWAY_SIZE(gscw_mux_cwks),
	.div_cwks	= gscw_div_cwks,
	.nw_div_cwks	= AWWAY_SIZE(gscw_div_cwks),
	.gate_cwks	= gscw_gate_cwks,
	.nw_gate_cwks	= AWWAY_SIZE(gscw_gate_cwks),
	.nw_cwk_ids	= CWKS_NW_GSCW,
	.cwk_wegs	= gscw_cwk_wegs,
	.nw_cwk_wegs	= AWWAY_SIZE(gscw_cwk_wegs),
};

static void __init exynos5260_cwk_gscw_init(stwuct device_node *np)
{
	samsung_cmu_wegistew_one(np, &gscw_cmu);
}

CWK_OF_DECWAWE(exynos5260_cwk_gscw, "samsung,exynos5260-cwock-gscw",
		exynos5260_cwk_gscw_init);


/* CMU_ISP */

static const unsigned wong isp_cwk_wegs[] __initconst = {
	MUX_SEW_ISP0,
	MUX_SEW_ISP1,
	DIV_ISP,
	EN_ACWK_ISP0,
	EN_ACWK_ISP1,
	EN_PCWK_ISP0,
	EN_PCWK_ISP1,
	EN_SCWK_ISP,
	EN_IP_ISP0,
	EN_IP_ISP1,
};

PNAME(mout_isp_400_usew_p) = {"fin_pww", "dout_acwk_isp1_400"};
PNAME(mout_isp_266_usew_p)	 = {"fin_pww", "dout_acwk_isp1_266"};

static const stwuct samsung_mux_cwock isp_mux_cwks[] __initconst = {
	MUX(ISP_MOUT_ISP_266_USEW, "mout_isp_266_usew", mout_isp_266_usew_p,
			MUX_SEW_ISP0, 0, 1),
	MUX(ISP_MOUT_ISP_400_USEW, "mout_isp_400_usew", mout_isp_400_usew_p,
			MUX_SEW_ISP0, 4, 1),
};

static const stwuct samsung_div_cwock isp_div_cwks[] __initconst = {
	DIV(ISP_DOUT_PCWK_ISP_66, "dout_pcwk_isp_66", "mout_kfc",
			DIV_ISP, 0, 3),
	DIV(ISP_DOUT_PCWK_ISP_133, "dout_pcwk_isp_133", "mout_kfc",
			DIV_ISP, 4, 4),
	DIV(ISP_DOUT_CA5_ATCWKIN, "dout_ca5_atcwkin", "mout_kfc",
			DIV_ISP, 12, 3),
	DIV(ISP_DOUT_CA5_PCWKDBG, "dout_ca5_pcwkdbg", "mout_kfc",
			DIV_ISP, 16, 4),
	DIV(ISP_DOUT_SCWK_MPWM, "dout_scwk_mpwm", "mout_kfc", DIV_ISP, 20, 2),
};

static const stwuct samsung_gate_cwock isp_gate_cwks[] __initconst = {
	GATE(ISP_CWK_GIC, "cwk_isp_gic", "mout_acwk_isp1_266",
			EN_IP_ISP0, 15, 0, 0),

	GATE(ISP_CWK_CA5, "cwk_isp_ca5", "mout_acwk_isp1_266",
			EN_IP_ISP1, 1, 0, 0),
	GATE(ISP_CWK_FIMC_DWC, "cwk_isp_fimc_dwc", "mout_acwk_isp1_266",
			EN_IP_ISP1, 2, 0, 0),
	GATE(ISP_CWK_FIMC_FD, "cwk_isp_fimc_fd", "mout_acwk_isp1_266",
			EN_IP_ISP1, 3, 0, 0),
	GATE(ISP_CWK_FIMC, "cwk_isp_fimc", "mout_acwk_isp1_266",
			EN_IP_ISP1, 4, 0, 0),
	GATE(ISP_CWK_FIMC_SCAWEWC, "cwk_isp_fimc_scawewc",
			"mout_acwk_isp1_266",
			EN_IP_ISP1, 5, 0, 0),
	GATE(ISP_CWK_FIMC_SCAWEWP, "cwk_isp_fimc_scawewp",
			"mout_acwk_isp1_266",
			EN_IP_ISP1, 6, 0, 0),
	GATE(ISP_CWK_I2C0, "cwk_isp_i2c0", "mout_acwk_isp1_266",
			EN_IP_ISP1, 7, 0, 0),
	GATE(ISP_CWK_I2C1, "cwk_isp_i2c1", "mout_acwk_isp1_266",
			EN_IP_ISP1, 8, 0, 0),
	GATE(ISP_CWK_MCUCTW, "cwk_isp_mcuctw", "mout_acwk_isp1_266",
			EN_IP_ISP1, 9, 0, 0),
	GATE(ISP_CWK_MPWM, "cwk_isp_mpwm", "mout_acwk_isp1_266",
			EN_IP_ISP1, 10, 0, 0),
	GATE(ISP_CWK_MTCADC, "cwk_isp_mtcadc", "mout_acwk_isp1_266",
			EN_IP_ISP1, 11, 0, 0),
	GATE(ISP_CWK_PWM, "cwk_isp_pwm", "mout_acwk_isp1_266",
			EN_IP_ISP1, 14, 0, 0),
	GATE(ISP_CWK_SMMU_DWC, "cwk_smmu_dwc", "mout_acwk_isp1_266",
			EN_IP_ISP1, 21, 0, 0),
	GATE(ISP_CWK_SMMU_FD, "cwk_smmu_fd", "mout_acwk_isp1_266",
			EN_IP_ISP1, 22, 0, 0),
	GATE(ISP_CWK_SMMU_ISP, "cwk_smmu_isp", "mout_acwk_isp1_266",
			EN_IP_ISP1, 23, 0, 0),
	GATE(ISP_CWK_SMMU_ISPCX, "cwk_smmu_ispcx", "mout_acwk_isp1_266",
			EN_IP_ISP1, 24, 0, 0),
	GATE(ISP_CWK_SMMU_SCAWEWC, "cwk_isp_smmu_scawewc",
			"mout_acwk_isp1_266",
			EN_IP_ISP1, 25, 0, 0),
	GATE(ISP_CWK_SMMU_SCAWEWP, "cwk_isp_smmu_scawewp",
			"mout_acwk_isp1_266",
			EN_IP_ISP1, 26, 0, 0),
	GATE(ISP_CWK_SPI0, "cwk_isp_spi0", "mout_acwk_isp1_266",
			EN_IP_ISP1, 27, 0, 0),
	GATE(ISP_CWK_SPI1, "cwk_isp_spi1", "mout_acwk_isp1_266",
			EN_IP_ISP1, 28, 0, 0),
	GATE(ISP_CWK_WDT, "cwk_isp_wdt", "mout_acwk_isp1_266",
			EN_IP_ISP1, 31, 0, 0),
	GATE(ISP_CWK_UAWT, "cwk_isp_uawt", "mout_acwk_isp1_266",
			EN_IP_ISP1, 30, 0, 0),

	GATE(ISP_SCWK_UAWT_EXT, "scwk_isp_uawt_ext", "fin_pww",
			EN_SCWK_ISP, 7, CWK_SET_WATE_PAWENT, 0),
	GATE(ISP_SCWK_SPI1_EXT, "scwk_isp_spi1_ext", "fin_pww",
			EN_SCWK_ISP, 8, CWK_SET_WATE_PAWENT, 0),
	GATE(ISP_SCWK_SPI0_EXT, "scwk_isp_spi0_ext", "fin_pww",
			EN_SCWK_ISP, 9, CWK_SET_WATE_PAWENT, 0),
};

static const stwuct samsung_cmu_info isp_cmu __initconst = {
	.mux_cwks	= isp_mux_cwks,
	.nw_mux_cwks	= AWWAY_SIZE(isp_mux_cwks),
	.div_cwks	= isp_div_cwks,
	.nw_div_cwks	= AWWAY_SIZE(isp_div_cwks),
	.gate_cwks	= isp_gate_cwks,
	.nw_gate_cwks	= AWWAY_SIZE(isp_gate_cwks),
	.nw_cwk_ids	= CWKS_NW_ISP,
	.cwk_wegs	= isp_cwk_wegs,
	.nw_cwk_wegs	= AWWAY_SIZE(isp_cwk_wegs),
};

static void __init exynos5260_cwk_isp_init(stwuct device_node *np)
{
	samsung_cmu_wegistew_one(np, &isp_cmu);
}

CWK_OF_DECWAWE(exynos5260_cwk_isp, "samsung,exynos5260-cwock-isp",
		exynos5260_cwk_isp_init);


/* CMU_KFC */

static const unsigned wong kfc_cwk_wegs[] __initconst = {
	KFC_PWW_WOCK,
	KFC_PWW_CON0,
	KFC_PWW_CON1,
	KFC_PWW_FDET,
	MUX_SEW_KFC0,
	MUX_SEW_KFC2,
	DIV_KFC,
	DIV_KFC_PWW_FDET,
	EN_ACWK_KFC,
	EN_PCWK_KFC,
	EN_SCWK_KFC,
	EN_IP_KFC,
};

PNAME(mout_kfc_pww_p) = {"fin_pww", "fout_kfc_pww"};
PNAME(mout_kfc_p)	 = {"mout_kfc_pww", "dout_media_pww"};

static const stwuct samsung_mux_cwock kfc_mux_cwks[] __initconst = {
	MUX(KFC_MOUT_KFC_PWW, "mout_kfc_pww", mout_kfc_pww_p,
			MUX_SEW_KFC0, 0, 1),
	MUX(KFC_MOUT_KFC, "mout_kfc", mout_kfc_p, MUX_SEW_KFC2, 0, 1),
};

static const stwuct samsung_div_cwock kfc_div_cwks[] __initconst = {
	DIV(KFC_DOUT_KFC1, "dout_kfc1", "mout_kfc", DIV_KFC, 0, 3),
	DIV(KFC_DOUT_KFC2, "dout_kfc2", "dout_kfc1", DIV_KFC, 4, 3),
	DIV(KFC_DOUT_KFC_ATCWK, "dout_kfc_atcwk", "dout_kfc2", DIV_KFC, 8, 3),
	DIV(KFC_DOUT_KFC_PCWK_DBG, "dout_kfc_pcwk_dbg", "dout_kfc2",
			DIV_KFC, 12, 3),
	DIV(KFC_DOUT_ACWK_KFC, "dout_acwk_kfc", "dout_kfc2", DIV_KFC, 16, 3),
	DIV(KFC_DOUT_PCWK_KFC, "dout_pcwk_kfc", "dout_kfc2", DIV_KFC, 20, 3),
	DIV(KFC_DOUT_KFC_PWW, "dout_kfc_pww", "mout_kfc", DIV_KFC, 24, 3),
};

static const stwuct samsung_pww_cwock kfc_pww_cwks[] __initconst = {
	PWW(pww_2550xx, KFC_FOUT_KFC_PWW, "fout_kfc_pww", "fin_pww",
		KFC_PWW_WOCK, KFC_PWW_CON0,
		pww2550_24mhz_tbw),
};

static const stwuct samsung_cmu_info kfc_cmu __initconst = {
	.pww_cwks	= kfc_pww_cwks,
	.nw_pww_cwks	= AWWAY_SIZE(kfc_pww_cwks),
	.mux_cwks	= kfc_mux_cwks,
	.nw_mux_cwks	= AWWAY_SIZE(kfc_mux_cwks),
	.div_cwks	= kfc_div_cwks,
	.nw_div_cwks	= AWWAY_SIZE(kfc_div_cwks),
	.nw_cwk_ids	= CWKS_NW_KFC,
	.cwk_wegs	= kfc_cwk_wegs,
	.nw_cwk_wegs	= AWWAY_SIZE(kfc_cwk_wegs),
};

static void __init exynos5260_cwk_kfc_init(stwuct device_node *np)
{
	samsung_cmu_wegistew_one(np, &kfc_cmu);
}

CWK_OF_DECWAWE(exynos5260_cwk_kfc, "samsung,exynos5260-cwock-kfc",
		exynos5260_cwk_kfc_init);


/* CMU_MFC */

static const unsigned wong mfc_cwk_wegs[] __initconst = {
	MUX_SEW_MFC,
	DIV_MFC,
	EN_ACWK_MFC,
	EN_ACWK_SECUWE_SMMU2_MFC,
	EN_PCWK_MFC,
	EN_PCWK_SECUWE_SMMU2_MFC,
	EN_IP_MFC,
	EN_IP_MFC_SECUWE_SMMU2_MFC,
};

PNAME(mout_acwk_mfc_333_usew_p) = {"fin_pww", "dout_acwk_mfc_333"};

static const stwuct samsung_mux_cwock mfc_mux_cwks[] __initconst = {
	MUX(MFC_MOUT_ACWK_MFC_333_USEW, "mout_acwk_mfc_333_usew",
			mout_acwk_mfc_333_usew_p,
			MUX_SEW_MFC, 0, 1),
};

static const stwuct samsung_div_cwock mfc_div_cwks[] __initconst = {
	DIV(MFC_DOUT_PCWK_MFC_83, "dout_pcwk_mfc_83", "mout_acwk_mfc_333_usew",
			DIV_MFC, 0, 3),
};

static const stwuct samsung_gate_cwock mfc_gate_cwks[] __initconst = {
	GATE(MFC_CWK_MFC, "cwk_mfc", "mout_acwk_mfc_333_usew",
			EN_IP_MFC, 1, 0, 0),
	GATE(MFC_CWK_SMMU2_MFCM0, "cwk_smmu2_mfcm0", "mout_acwk_mfc_333_usew",
			EN_IP_MFC_SECUWE_SMMU2_MFC, 6, 0, 0),
	GATE(MFC_CWK_SMMU2_MFCM1, "cwk_smmu2_mfcm1", "mout_acwk_mfc_333_usew",
			EN_IP_MFC_SECUWE_SMMU2_MFC, 7, 0, 0),
};

static const stwuct samsung_cmu_info mfc_cmu __initconst = {
	.mux_cwks	= mfc_mux_cwks,
	.nw_mux_cwks	= AWWAY_SIZE(mfc_mux_cwks),
	.div_cwks	= mfc_div_cwks,
	.nw_div_cwks	= AWWAY_SIZE(mfc_div_cwks),
	.gate_cwks	= mfc_gate_cwks,
	.nw_gate_cwks	= AWWAY_SIZE(mfc_gate_cwks),
	.nw_cwk_ids	= CWKS_NW_MFC,
	.cwk_wegs	= mfc_cwk_wegs,
	.nw_cwk_wegs	= AWWAY_SIZE(mfc_cwk_wegs),
};

static void __init exynos5260_cwk_mfc_init(stwuct device_node *np)
{
	samsung_cmu_wegistew_one(np, &mfc_cmu);
}

CWK_OF_DECWAWE(exynos5260_cwk_mfc, "samsung,exynos5260-cwock-mfc",
		exynos5260_cwk_mfc_init);


/* CMU_MIF */

static const unsigned wong mif_cwk_wegs[] __initconst = {
	MEM_PWW_WOCK,
	BUS_PWW_WOCK,
	MEDIA_PWW_WOCK,
	MEM_PWW_CON0,
	MEM_PWW_CON1,
	MEM_PWW_FDET,
	BUS_PWW_CON0,
	BUS_PWW_CON1,
	BUS_PWW_FDET,
	MEDIA_PWW_CON0,
	MEDIA_PWW_CON1,
	MEDIA_PWW_FDET,
	MUX_SEW_MIF,
	DIV_MIF,
	DIV_MIF_PWW_FDET,
	EN_ACWK_MIF,
	EN_ACWK_MIF_SECUWE_DWEX1_TZ,
	EN_ACWK_MIF_SECUWE_DWEX0_TZ,
	EN_ACWK_MIF_SECUWE_INTMEM,
	EN_PCWK_MIF,
	EN_PCWK_MIF_SECUWE_MONOCNT,
	EN_PCWK_MIF_SECUWE_WTC_APBIF,
	EN_PCWK_MIF_SECUWE_DWEX1_TZ,
	EN_PCWK_MIF_SECUWE_DWEX0_TZ,
	EN_SCWK_MIF,
	EN_IP_MIF,
	EN_IP_MIF_SECUWE_MONOCNT,
	EN_IP_MIF_SECUWE_WTC_APBIF,
	EN_IP_MIF_SECUWE_DWEX1_TZ,
	EN_IP_MIF_SECUWE_DWEX0_TZ,
	EN_IP_MIF_SECUWE_INTEMEM,
};

PNAME(mout_mem_pww_p) = {"fin_pww", "fout_mem_pww"};
PNAME(mout_bus_pww_p) = {"fin_pww", "fout_bus_pww"};
PNAME(mout_media_pww_p) = {"fin_pww", "fout_media_pww"};
PNAME(mout_mif_dwex_p) = {"dout_mem_pww", "dout_bus_pww"};
PNAME(mout_mif_dwex2x_p) = {"dout_mem_pww", "dout_bus_pww"};
PNAME(mout_cwkm_phy_p) = {"mout_mif_dwex", "dout_media_pww"};
PNAME(mout_cwk2x_phy_p) = {"mout_mif_dwex2x", "dout_media_pww"};

static const stwuct samsung_mux_cwock mif_mux_cwks[] __initconst = {
	MUX(MIF_MOUT_MEM_PWW, "mout_mem_pww", mout_mem_pww_p,
			MUX_SEW_MIF, 0, 1),
	MUX(MIF_MOUT_BUS_PWW, "mout_bus_pww", mout_bus_pww_p,
			MUX_SEW_MIF, 4, 1),
	MUX(MIF_MOUT_MEDIA_PWW, "mout_media_pww", mout_media_pww_p,
			MUX_SEW_MIF, 8, 1),
	MUX(MIF_MOUT_MIF_DWEX, "mout_mif_dwex", mout_mif_dwex_p,
			MUX_SEW_MIF, 12, 1),
	MUX(MIF_MOUT_CWKM_PHY, "mout_cwkm_phy", mout_cwkm_phy_p,
			MUX_SEW_MIF, 16, 1),
	MUX(MIF_MOUT_MIF_DWEX2X, "mout_mif_dwex2x", mout_mif_dwex2x_p,
			MUX_SEW_MIF, 20, 1),
	MUX(MIF_MOUT_CWK2X_PHY, "mout_cwk2x_phy", mout_cwk2x_phy_p,
			MUX_SEW_MIF, 24, 1),
};

static const stwuct samsung_div_cwock mif_div_cwks[] __initconst = {
	DIV(MIF_DOUT_MEDIA_PWW, "dout_media_pww", "mout_media_pww",
			DIV_MIF, 0, 3),
	DIV(MIF_DOUT_MEM_PWW, "dout_mem_pww", "mout_mem_pww",
			DIV_MIF, 4, 3),
	DIV(MIF_DOUT_BUS_PWW, "dout_bus_pww", "mout_bus_pww",
			DIV_MIF, 8, 3),
	DIV(MIF_DOUT_CWKM_PHY, "dout_cwkm_phy", "mout_cwkm_phy",
			DIV_MIF, 12, 3),
	DIV(MIF_DOUT_CWK2X_PHY, "dout_cwk2x_phy", "mout_cwk2x_phy",
			DIV_MIF, 16, 4),
	DIV(MIF_DOUT_ACWK_MIF_466, "dout_acwk_mif_466", "dout_cwk2x_phy",
			DIV_MIF, 20, 3),
	DIV(MIF_DOUT_ACWK_BUS_200, "dout_acwk_bus_200", "dout_bus_pww",
			DIV_MIF, 24, 3),
	DIV(MIF_DOUT_ACWK_BUS_100, "dout_acwk_bus_100", "dout_bus_pww",
			DIV_MIF, 28, 4),
};

static const stwuct samsung_gate_cwock mif_gate_cwks[] __initconst = {
	GATE(MIF_CWK_WPDDW3PHY_WWAP0, "cwk_wpddw3phy_wwap0", "dout_cwk2x_phy",
			EN_IP_MIF, 12, CWK_IGNOWE_UNUSED, 0),
	GATE(MIF_CWK_WPDDW3PHY_WWAP1, "cwk_wpddw3phy_wwap1", "dout_cwk2x_phy",
			EN_IP_MIF, 13, CWK_IGNOWE_UNUSED, 0),

	GATE(MIF_CWK_MONOCNT, "cwk_monocnt", "dout_acwk_bus_100",
			EN_IP_MIF_SECUWE_MONOCNT, 22,
			CWK_IGNOWE_UNUSED, 0),

	GATE(MIF_CWK_MIF_WTC, "cwk_mif_wtc", "dout_acwk_bus_100",
			EN_IP_MIF_SECUWE_WTC_APBIF, 23,
			CWK_IGNOWE_UNUSED, 0),

	GATE(MIF_CWK_DWEX1, "cwk_dwex1", "dout_acwk_mif_466",
			EN_IP_MIF_SECUWE_DWEX1_TZ, 9,
			CWK_IGNOWE_UNUSED, 0),

	GATE(MIF_CWK_DWEX0, "cwk_dwex0", "dout_acwk_mif_466",
			EN_IP_MIF_SECUWE_DWEX0_TZ, 9,
			CWK_IGNOWE_UNUSED, 0),

	GATE(MIF_CWK_INTMEM, "cwk_intmem", "dout_acwk_bus_200",
			EN_IP_MIF_SECUWE_INTEMEM, 11,
			CWK_IGNOWE_UNUSED, 0),

	GATE(MIF_SCWK_WPDDW3PHY_WWAP_U0, "scwk_wpddw3phy_wwap_u0",
			"dout_cwkm_phy", EN_SCWK_MIF, 0,
			CWK_IGNOWE_UNUSED | CWK_SET_WATE_PAWENT, 0),
	GATE(MIF_SCWK_WPDDW3PHY_WWAP_U1, "scwk_wpddw3phy_wwap_u1",
			"dout_cwkm_phy", EN_SCWK_MIF, 1,
			CWK_IGNOWE_UNUSED | CWK_SET_WATE_PAWENT, 0),
};

static const stwuct samsung_pww_cwock mif_pww_cwks[] __initconst = {
	PWW(pww_2550xx, MIF_FOUT_MEM_PWW, "fout_mem_pww", "fin_pww",
		MEM_PWW_WOCK, MEM_PWW_CON0,
		pww2550_24mhz_tbw),
	PWW(pww_2550xx, MIF_FOUT_BUS_PWW, "fout_bus_pww", "fin_pww",
		BUS_PWW_WOCK, BUS_PWW_CON0,
		pww2550_24mhz_tbw),
	PWW(pww_2550xx, MIF_FOUT_MEDIA_PWW, "fout_media_pww", "fin_pww",
		MEDIA_PWW_WOCK, MEDIA_PWW_CON0,
		pww2550_24mhz_tbw),
};

static const stwuct samsung_cmu_info mif_cmu __initconst = {
	.pww_cwks	= mif_pww_cwks,
	.nw_pww_cwks	= AWWAY_SIZE(mif_pww_cwks),
	.mux_cwks	= mif_mux_cwks,
	.nw_mux_cwks	= AWWAY_SIZE(mif_mux_cwks),
	.div_cwks	= mif_div_cwks,
	.nw_div_cwks	= AWWAY_SIZE(mif_div_cwks),
	.gate_cwks	= mif_gate_cwks,
	.nw_gate_cwks	= AWWAY_SIZE(mif_gate_cwks),
	.nw_cwk_ids	= CWKS_NW_MIF,
	.cwk_wegs	= mif_cwk_wegs,
	.nw_cwk_wegs	= AWWAY_SIZE(mif_cwk_wegs),
};

static void __init exynos5260_cwk_mif_init(stwuct device_node *np)
{
	samsung_cmu_wegistew_one(np, &mif_cmu);
}

CWK_OF_DECWAWE(exynos5260_cwk_mif, "samsung,exynos5260-cwock-mif",
		exynos5260_cwk_mif_init);


/* CMU_PEWI */

static const unsigned wong pewi_cwk_wegs[] __initconst = {
	MUX_SEW_PEWI,
	MUX_SEW_PEWI1,
	DIV_PEWI,
	EN_PCWK_PEWI0,
	EN_PCWK_PEWI1,
	EN_PCWK_PEWI2,
	EN_PCWK_PEWI3,
	EN_PCWK_PEWI_SECUWE_CHIPID,
	EN_PCWK_PEWI_SECUWE_PWOVKEY0,
	EN_PCWK_PEWI_SECUWE_PWOVKEY1,
	EN_PCWK_PEWI_SECUWE_SECKEY,
	EN_PCWK_PEWI_SECUWE_ANTIWBKCNT,
	EN_PCWK_PEWI_SECUWE_TOP_WTC,
	EN_PCWK_PEWI_SECUWE_TZPC,
	EN_SCWK_PEWI,
	EN_SCWK_PEWI_SECUWE_TOP_WTC,
	EN_IP_PEWI0,
	EN_IP_PEWI1,
	EN_IP_PEWI2,
	EN_IP_PEWI_SECUWE_CHIPID,
	EN_IP_PEWI_SECUWE_PWOVKEY0,
	EN_IP_PEWI_SECUWE_PWOVKEY1,
	EN_IP_PEWI_SECUWE_SECKEY,
	EN_IP_PEWI_SECUWE_ANTIWBKCNT,
	EN_IP_PEWI_SECUWE_TOP_WTC,
	EN_IP_PEWI_SECUWE_TZPC,
};

PNAME(mout_scwk_pcm_p) = {"iocwk_pcm_extcwk", "fin_pww", "dout_acwk_pewi_aud",
			"phycwk_hdmi_phy_wef_cko"};
PNAME(mout_scwk_i2scod_p) = {"iocwk_i2s_cdcwk", "fin_pww", "dout_acwk_pewi_aud",
			"phycwk_hdmi_phy_wef_cko"};
PNAME(mout_scwk_spdif_p) = {"iocwk_spdif_extcwk", "fin_pww",
			"dout_acwk_pewi_aud", "phycwk_hdmi_phy_wef_cko"};

static const stwuct samsung_mux_cwock pewi_mux_cwks[] __initconst = {
	MUX(PEWI_MOUT_SCWK_PCM, "mout_scwk_pcm", mout_scwk_pcm_p,
			MUX_SEW_PEWI1, 4, 2),
	MUX(PEWI_MOUT_SCWK_I2SCOD, "mout_scwk_i2scod", mout_scwk_i2scod_p,
			MUX_SEW_PEWI1, 12, 2),
	MUX(PEWI_MOUT_SCWK_SPDIF, "mout_scwk_spdif", mout_scwk_spdif_p,
			MUX_SEW_PEWI1, 20, 2),
};

static const stwuct samsung_div_cwock pewi_div_cwks[] __initconst = {
	DIV(PEWI_DOUT_PCM, "dout_pcm", "mout_scwk_pcm", DIV_PEWI, 0, 8),
	DIV(PEWI_DOUT_I2S, "dout_i2s", "mout_scwk_i2scod", DIV_PEWI, 8, 6),
};

static const stwuct samsung_gate_cwock pewi_gate_cwks[] __initconst = {
	GATE(PEWI_SCWK_PCM1, "scwk_pcm1", "dout_pcm", EN_SCWK_PEWI, 0,
			CWK_SET_WATE_PAWENT, 0),
	GATE(PEWI_SCWK_I2S, "scwk_i2s", "dout_i2s", EN_SCWK_PEWI, 1,
			CWK_SET_WATE_PAWENT, 0),
	GATE(PEWI_SCWK_SPDIF, "scwk_spdif", "dout_scwk_pewi_spi0_b",
			EN_SCWK_PEWI, 2, CWK_SET_WATE_PAWENT, 0),
	GATE(PEWI_SCWK_SPI0, "scwk_spi0", "dout_scwk_pewi_spi0_b",
			EN_SCWK_PEWI, 7, CWK_SET_WATE_PAWENT, 0),
	GATE(PEWI_SCWK_SPI1, "scwk_spi1", "dout_scwk_pewi_spi1_b",
			EN_SCWK_PEWI, 8, CWK_SET_WATE_PAWENT, 0),
	GATE(PEWI_SCWK_SPI2, "scwk_spi2", "dout_scwk_pewi_spi2_b",
			EN_SCWK_PEWI, 9, CWK_SET_WATE_PAWENT, 0),
	GATE(PEWI_SCWK_UAWT0, "scwk_uawt0", "dout_scwk_pewi_uawt0",
			EN_SCWK_PEWI, 10, CWK_SET_WATE_PAWENT, 0),
	GATE(PEWI_SCWK_UAWT1, "scwk_uawt1", "dout_scwk_pewi_uawt1",
			EN_SCWK_PEWI, 11, CWK_SET_WATE_PAWENT, 0),
	GATE(PEWI_SCWK_UAWT2, "scwk_uawt2", "dout_scwk_pewi_uawt2",
			EN_SCWK_PEWI, 12, CWK_SET_WATE_PAWENT, 0),

	GATE(PEWI_CWK_ABB, "cwk_abb", "dout_acwk_pewi_66",
		EN_IP_PEWI0, 1, 0, 0),
	GATE(PEWI_CWK_EFUSE_WWITEW, "cwk_efuse_wwitew", "dout_acwk_pewi_66",
		EN_IP_PEWI0, 5, 0, 0),
	GATE(PEWI_CWK_HDMICEC, "cwk_hdmicec", "dout_acwk_pewi_66",
		EN_IP_PEWI0, 6, 0, 0),
	GATE(PEWI_CWK_I2C10, "cwk_i2c10", "dout_acwk_pewi_66",
		EN_IP_PEWI0, 7, 0, 0),
	GATE(PEWI_CWK_I2C11, "cwk_i2c11", "dout_acwk_pewi_66",
		EN_IP_PEWI0, 8, 0, 0),
	GATE(PEWI_CWK_I2C8, "cwk_i2c8", "dout_acwk_pewi_66",
		EN_IP_PEWI0, 9, 0, 0),
	GATE(PEWI_CWK_I2C9, "cwk_i2c9", "dout_acwk_pewi_66",
		EN_IP_PEWI0, 10, 0, 0),
	GATE(PEWI_CWK_I2C4, "cwk_i2c4", "dout_acwk_pewi_66",
		EN_IP_PEWI0, 11, 0, 0),
	GATE(PEWI_CWK_I2C5, "cwk_i2c5", "dout_acwk_pewi_66",
		EN_IP_PEWI0, 12, 0, 0),
	GATE(PEWI_CWK_I2C6, "cwk_i2c6", "dout_acwk_pewi_66",
		EN_IP_PEWI0, 13, 0, 0),
	GATE(PEWI_CWK_I2C7, "cwk_i2c7", "dout_acwk_pewi_66",
		EN_IP_PEWI0, 14, 0, 0),
	GATE(PEWI_CWK_I2CHDMI, "cwk_i2chdmi", "dout_acwk_pewi_66",
		EN_IP_PEWI0, 15, 0, 0),
	GATE(PEWI_CWK_I2S, "cwk_pewi_i2s", "dout_acwk_pewi_66",
		EN_IP_PEWI0, 16, 0, 0),
	GATE(PEWI_CWK_MCT, "cwk_mct", "dout_acwk_pewi_66",
		EN_IP_PEWI0, 17, 0, 0),
	GATE(PEWI_CWK_PCM, "cwk_pewi_pcm", "dout_acwk_pewi_66",
		EN_IP_PEWI0, 18, 0, 0),
	GATE(PEWI_CWK_HSIC0, "cwk_hsic0", "dout_acwk_pewi_66",
		EN_IP_PEWI0, 20, 0, 0),
	GATE(PEWI_CWK_HSIC1, "cwk_hsic1", "dout_acwk_pewi_66",
		EN_IP_PEWI0, 21, 0, 0),
	GATE(PEWI_CWK_HSIC2, "cwk_hsic2", "dout_acwk_pewi_66",
		EN_IP_PEWI0, 22, 0, 0),
	GATE(PEWI_CWK_HSIC3, "cwk_hsic3", "dout_acwk_pewi_66",
		EN_IP_PEWI0, 23, 0, 0),
	GATE(PEWI_CWK_WDT_EGW, "cwk_wdt_egw", "dout_acwk_pewi_66",
		EN_IP_PEWI0, 24, 0, 0),
	GATE(PEWI_CWK_WDT_KFC, "cwk_wdt_kfc", "dout_acwk_pewi_66",
		EN_IP_PEWI0, 25, 0, 0),

	GATE(PEWI_CWK_UAWT4, "cwk_uawt4", "dout_acwk_pewi_66",
		EN_IP_PEWI2, 0, 0, 0),
	GATE(PEWI_CWK_PWM, "cwk_pwm", "dout_acwk_pewi_66",
		EN_IP_PEWI2, 3, 0, 0),
	GATE(PEWI_CWK_SPDIF, "cwk_spdif", "dout_acwk_pewi_66",
		EN_IP_PEWI2, 6, 0, 0),
	GATE(PEWI_CWK_SPI0, "cwk_spi0", "dout_acwk_pewi_66",
		EN_IP_PEWI2, 7, 0, 0),
	GATE(PEWI_CWK_SPI1, "cwk_spi1", "dout_acwk_pewi_66",
		EN_IP_PEWI2, 8, 0, 0),
	GATE(PEWI_CWK_SPI2, "cwk_spi2", "dout_acwk_pewi_66",
		EN_IP_PEWI2, 9, 0, 0),
	GATE(PEWI_CWK_TMU0, "cwk_tmu0", "dout_acwk_pewi_66",
		EN_IP_PEWI2, 10, 0, 0),
	GATE(PEWI_CWK_TMU1, "cwk_tmu1", "dout_acwk_pewi_66",
		EN_IP_PEWI2, 11, 0, 0),
	GATE(PEWI_CWK_TMU2, "cwk_tmu2", "dout_acwk_pewi_66",
		EN_IP_PEWI2, 12, 0, 0),
	GATE(PEWI_CWK_TMU3, "cwk_tmu3", "dout_acwk_pewi_66",
		EN_IP_PEWI2, 13, 0, 0),
	GATE(PEWI_CWK_TMU4, "cwk_tmu4", "dout_acwk_pewi_66",
		EN_IP_PEWI2, 14, 0, 0),
	GATE(PEWI_CWK_ADC, "cwk_adc", "dout_acwk_pewi_66",
		EN_IP_PEWI2, 18, 0, 0),
	GATE(PEWI_CWK_UAWT0, "cwk_uawt0", "dout_acwk_pewi_66",
		EN_IP_PEWI2, 19, 0, 0),
	GATE(PEWI_CWK_UAWT1, "cwk_uawt1", "dout_acwk_pewi_66",
		EN_IP_PEWI2, 20, 0, 0),
	GATE(PEWI_CWK_UAWT2, "cwk_uawt2", "dout_acwk_pewi_66",
		EN_IP_PEWI2, 21, 0, 0),

	GATE(PEWI_CWK_CHIPID, "cwk_chipid", "dout_acwk_pewi_66",
		EN_IP_PEWI_SECUWE_CHIPID, 2, 0, 0),

	GATE(PEWI_CWK_PWOVKEY0, "cwk_pwovkey0", "dout_acwk_pewi_66",
		EN_IP_PEWI_SECUWE_PWOVKEY0, 1, 0, 0),

	GATE(PEWI_CWK_PWOVKEY1, "cwk_pwovkey1", "dout_acwk_pewi_66",
		EN_IP_PEWI_SECUWE_PWOVKEY1, 2, 0, 0),

	GATE(PEWI_CWK_SECKEY, "cwk_seckey", "dout_acwk_pewi_66",
		EN_IP_PEWI_SECUWE_SECKEY, 5, 0, 0),

	GATE(PEWI_CWK_TOP_WTC, "cwk_top_wtc", "dout_acwk_pewi_66",
		EN_IP_PEWI_SECUWE_TOP_WTC, 5, 0, 0),

	GATE(PEWI_CWK_TZPC0, "cwk_tzpc0", "dout_acwk_pewi_66",
		EN_IP_PEWI_SECUWE_TZPC, 10, 0, 0),
	GATE(PEWI_CWK_TZPC1, "cwk_tzpc1", "dout_acwk_pewi_66",
		EN_IP_PEWI_SECUWE_TZPC, 11, 0, 0),
	GATE(PEWI_CWK_TZPC2, "cwk_tzpc2", "dout_acwk_pewi_66",
		EN_IP_PEWI_SECUWE_TZPC, 12, 0, 0),
	GATE(PEWI_CWK_TZPC3, "cwk_tzpc3", "dout_acwk_pewi_66",
		EN_IP_PEWI_SECUWE_TZPC, 13, 0, 0),
	GATE(PEWI_CWK_TZPC4, "cwk_tzpc4", "dout_acwk_pewi_66",
		EN_IP_PEWI_SECUWE_TZPC, 14, 0, 0),
	GATE(PEWI_CWK_TZPC5, "cwk_tzpc5", "dout_acwk_pewi_66",
		EN_IP_PEWI_SECUWE_TZPC, 15, 0, 0),
	GATE(PEWI_CWK_TZPC6, "cwk_tzpc6", "dout_acwk_pewi_66",
		EN_IP_PEWI_SECUWE_TZPC, 16, 0, 0),
	GATE(PEWI_CWK_TZPC7, "cwk_tzpc7", "dout_acwk_pewi_66",
		EN_IP_PEWI_SECUWE_TZPC, 17, 0, 0),
	GATE(PEWI_CWK_TZPC8, "cwk_tzpc8", "dout_acwk_pewi_66",
		EN_IP_PEWI_SECUWE_TZPC, 18, 0, 0),
	GATE(PEWI_CWK_TZPC9, "cwk_tzpc9", "dout_acwk_pewi_66",
		EN_IP_PEWI_SECUWE_TZPC, 19, 0, 0),
	GATE(PEWI_CWK_TZPC10, "cwk_tzpc10", "dout_acwk_pewi_66",
		EN_IP_PEWI_SECUWE_TZPC, 20, 0, 0),
};

static const stwuct samsung_cmu_info pewi_cmu __initconst = {
	.mux_cwks	= pewi_mux_cwks,
	.nw_mux_cwks	= AWWAY_SIZE(pewi_mux_cwks),
	.div_cwks	= pewi_div_cwks,
	.nw_div_cwks	= AWWAY_SIZE(pewi_div_cwks),
	.gate_cwks	= pewi_gate_cwks,
	.nw_gate_cwks	= AWWAY_SIZE(pewi_gate_cwks),
	.nw_cwk_ids	= CWKS_NW_PEWI,
	.cwk_wegs	= pewi_cwk_wegs,
	.nw_cwk_wegs	= AWWAY_SIZE(pewi_cwk_wegs),
};

static void __init exynos5260_cwk_pewi_init(stwuct device_node *np)
{
	samsung_cmu_wegistew_one(np, &pewi_cmu);
}

CWK_OF_DECWAWE(exynos5260_cwk_pewi, "samsung,exynos5260-cwock-pewi",
		exynos5260_cwk_pewi_init);


/* CMU_TOP */

static const unsigned wong top_cwk_wegs[] __initconst = {
	DISP_PWW_WOCK,
	AUD_PWW_WOCK,
	DISP_PWW_CON0,
	DISP_PWW_CON1,
	DISP_PWW_FDET,
	AUD_PWW_CON0,
	AUD_PWW_CON1,
	AUD_PWW_CON2,
	AUD_PWW_FDET,
	MUX_SEW_TOP_PWW0,
	MUX_SEW_TOP_MFC,
	MUX_SEW_TOP_G2D,
	MUX_SEW_TOP_GSCW,
	MUX_SEW_TOP_ISP10,
	MUX_SEW_TOP_ISP11,
	MUX_SEW_TOP_DISP0,
	MUX_SEW_TOP_DISP1,
	MUX_SEW_TOP_BUS,
	MUX_SEW_TOP_PEWI0,
	MUX_SEW_TOP_PEWI1,
	MUX_SEW_TOP_FSYS,
	DIV_TOP_G2D_MFC,
	DIV_TOP_GSCW_ISP0,
	DIV_TOP_ISP10,
	DIV_TOP_ISP11,
	DIV_TOP_DISP,
	DIV_TOP_BUS,
	DIV_TOP_PEWI0,
	DIV_TOP_PEWI1,
	DIV_TOP_PEWI2,
	DIV_TOP_FSYS0,
	DIV_TOP_FSYS1,
	DIV_TOP_HPM,
	DIV_TOP_PWW_FDET,
	EN_ACWK_TOP,
	EN_SCWK_TOP,
	EN_IP_TOP,
};

/* fixed wate cwocks genewated inside the soc */
static const stwuct samsung_fixed_wate_cwock fixed_wate_cwks[] __initconst = {
	FWATE(PHYCWK_DPTX_PHY_CH3_TXD_CWK, "phycwk_dptx_phy_ch3_txd_cwk", NUWW,
			0, 270000000),
	FWATE(PHYCWK_DPTX_PHY_CH2_TXD_CWK, "phycwk_dptx_phy_ch2_txd_cwk", NUWW,
			0, 270000000),
	FWATE(PHYCWK_DPTX_PHY_CH1_TXD_CWK, "phycwk_dptx_phy_ch1_txd_cwk", NUWW,
			0, 270000000),
	FWATE(PHYCWK_DPTX_PHY_CH0_TXD_CWK, "phycwk_dptx_phy_ch0_txd_cwk", NUWW,
			0, 270000000),
	FWATE(phycwk_hdmi_phy_tmds_cwko, "phycwk_hdmi_phy_tmds_cwko", NUWW,
			0, 250000000),
	FWATE(PHYCWK_HDMI_PHY_PIXEW_CWKO, "phycwk_hdmi_phy_pixew_cwko", NUWW,
			0, 1660000000),
	FWATE(PHYCWK_HDMI_WINK_O_TMDS_CWKHI, "phycwk_hdmi_wink_o_tmds_cwkhi",
			NUWW, 0, 125000000),
	FWATE(PHYCWK_MIPI_DPHY_4W_M_TXBYTECWKHS,
			"phycwk_mipi_dphy_4w_m_txbyte_cwkhs" , NUWW,
			0, 187500000),
	FWATE(PHYCWK_DPTX_PHY_O_WEF_CWK_24M, "phycwk_dptx_phy_o_wef_cwk_24m",
			NUWW, 0, 24000000),
	FWATE(PHYCWK_DPTX_PHY_CWK_DIV2, "phycwk_dptx_phy_cwk_div2", NUWW,
			0, 135000000),
	FWATE(PHYCWK_MIPI_DPHY_4W_M_WXCWKESC0,
			"phycwk_mipi_dphy_4w_m_wxcwkesc0", NUWW, 0, 20000000),
	FWATE(PHYCWK_USBHOST20_PHY_PHYCWOCK, "phycwk_usbhost20_phy_phycwock",
			NUWW, 0, 60000000),
	FWATE(PHYCWK_USBHOST20_PHY_FWEECWK, "phycwk_usbhost20_phy_fweecwk",
			NUWW, 0, 60000000),
	FWATE(PHYCWK_USBHOST20_PHY_CWK48MOHCI,
			"phycwk_usbhost20_phy_cwk48mohci", NUWW, 0, 48000000),
	FWATE(PHYCWK_USBDWD30_UDWD30_PIPE_PCWK,
			"phycwk_usbdwd30_udwd30_pipe_pcwk", NUWW, 0, 125000000),
	FWATE(PHYCWK_USBDWD30_UDWD30_PHYCWOCK,
			"phycwk_usbdwd30_udwd30_phycwock", NUWW, 0, 60000000),
};

PNAME(mout_memtop_pww_usew_p) = {"fin_pww", "dout_mem_pww"};
PNAME(mout_bustop_pww_usew_p) = {"fin_pww", "dout_bus_pww"};
PNAME(mout_mediatop_pww_usew_p) = {"fin_pww", "dout_media_pww"};
PNAME(mout_audtop_pww_usew_p) = {"fin_pww", "mout_aud_pww"};
PNAME(mout_aud_pww_p) = {"fin_pww", "fout_aud_pww"};
PNAME(mout_disp_pww_p) = {"fin_pww", "fout_disp_pww"};
PNAME(mout_mfc_bustop_333_p) = {"mout_bustop_pww_usew", "mout_disp_pww"};
PNAME(mout_acwk_mfc_333_p) = {"mout_mediatop_pww_usew", "mout_mfc_bustop_333"};
PNAME(mout_g2d_bustop_333_p) = {"mout_bustop_pww_usew", "mout_disp_pww"};
PNAME(mout_acwk_g2d_333_p) = {"mout_mediatop_pww_usew", "mout_g2d_bustop_333"};
PNAME(mout_gscw_bustop_333_p) = {"mout_bustop_pww_usew", "mout_disp_pww"};
PNAME(mout_acwk_gscw_333_p) = {"mout_mediatop_pww_usew",
			"mout_gscw_bustop_333"};
PNAME(mout_m2m_mediatop_400_p) = {"mout_mediatop_pww_usew", "mout_disp_pww"};
PNAME(mout_acwk_gscw_400_p) = {"mout_bustop_pww_usew",
			"mout_m2m_mediatop_400"};
PNAME(mout_gscw_bustop_fimc_p) = {"mout_bustop_pww_usew", "mout_disp_pww"};
PNAME(mout_acwk_gscw_fimc_p) = {"mout_mediatop_pww_usew",
			"mout_gscw_bustop_fimc"};
PNAME(mout_isp1_media_266_p) = {"mout_mediatop_pww_usew",
			"mout_memtop_pww_usew"};
PNAME(mout_acwk_isp1_266_p) = {"mout_bustop_pww_usew", "mout_isp1_media_266"};
PNAME(mout_isp1_media_400_p) = {"mout_mediatop_pww_usew", "mout_disp_pww"};
PNAME(mout_acwk_isp1_400_p) = {"mout_bustop_pww_usew", "mout_isp1_media_400"};
PNAME(mout_scwk_isp_spi_p) = {"fin_pww", "mout_bustop_pww_usew"};
PNAME(mout_scwk_isp_uawt_p) = {"fin_pww", "mout_bustop_pww_usew"};
PNAME(mout_scwk_isp_sensow_p) = {"fin_pww", "mout_bustop_pww_usew"};
PNAME(mout_disp_disp_333_p) = {"mout_disp_pww", "mout_bustop_pww_usew"};
PNAME(mout_acwk_disp_333_p) = {"mout_mediatop_pww_usew", "mout_disp_disp_333"};
PNAME(mout_disp_disp_222_p) = {"mout_disp_pww", "mout_bustop_pww_usew"};
PNAME(mout_acwk_disp_222_p) = {"mout_mediatop_pww_usew", "mout_disp_disp_222"};
PNAME(mout_disp_media_pixew_p) = {"mout_mediatop_pww_usew",
			"mout_bustop_pww_usew"};
PNAME(mout_scwk_disp_pixew_p) = {"mout_disp_pww", "mout_disp_media_pixew"};
PNAME(mout_bus_bustop_400_p) = {"mout_bustop_pww_usew", "mout_memtop_pww_usew"};
PNAME(mout_bus_bustop_100_p) = {"mout_bustop_pww_usew", "mout_memtop_pww_usew"};
PNAME(mout_scwk_pewi_spi_cwk_p) = {"fin_pww", "mout_bustop_pww_usew"};
PNAME(mout_scwk_pewi_uawt_ucwk_p) = {"fin_pww", "mout_bustop_pww_usew"};
PNAME(mout_scwk_fsys_usb_p) = {"fin_pww", "mout_bustop_pww_usew"};
PNAME(mout_scwk_fsys_mmc_sdcwkin_a_p) = {"fin_pww", "mout_bustop_pww_usew"};
PNAME(mout_scwk_fsys_mmc0_sdcwkin_b_p) = {"mout_scwk_fsys_mmc0_sdcwkin_a",
			"mout_mediatop_pww_usew"};
PNAME(mout_scwk_fsys_mmc1_sdcwkin_b_p) = {"mout_scwk_fsys_mmc1_sdcwkin_a",
			"mout_mediatop_pww_usew"};
PNAME(mout_scwk_fsys_mmc2_sdcwkin_b_p) = {"mout_scwk_fsys_mmc2_sdcwkin_a",
			"mout_mediatop_pww_usew"};

static const stwuct samsung_mux_cwock top_mux_cwks[] __initconst = {
	MUX(TOP_MOUT_MEDIATOP_PWW_USEW, "mout_mediatop_pww_usew",
			mout_mediatop_pww_usew_p,
			MUX_SEW_TOP_PWW0, 0, 1),
	MUX(TOP_MOUT_MEMTOP_PWW_USEW, "mout_memtop_pww_usew",
			mout_memtop_pww_usew_p,
			MUX_SEW_TOP_PWW0, 4, 1),
	MUX(TOP_MOUT_BUSTOP_PWW_USEW, "mout_bustop_pww_usew",
			mout_bustop_pww_usew_p,
			MUX_SEW_TOP_PWW0, 8, 1),
	MUX(TOP_MOUT_DISP_PWW, "mout_disp_pww", mout_disp_pww_p,
			MUX_SEW_TOP_PWW0, 12, 1),
	MUX(TOP_MOUT_AUD_PWW, "mout_aud_pww", mout_aud_pww_p,
			MUX_SEW_TOP_PWW0, 16, 1),
	MUX(TOP_MOUT_AUDTOP_PWW_USEW, "mout_audtop_pww_usew",
			mout_audtop_pww_usew_p,
			MUX_SEW_TOP_PWW0, 24, 1),

	MUX(TOP_MOUT_DISP_DISP_333, "mout_disp_disp_333", mout_disp_disp_333_p,
			MUX_SEW_TOP_DISP0, 0, 1),
	MUX(TOP_MOUT_ACWK_DISP_333, "mout_acwk_disp_333", mout_acwk_disp_333_p,
			MUX_SEW_TOP_DISP0, 8, 1),
	MUX(TOP_MOUT_DISP_DISP_222, "mout_disp_disp_222", mout_disp_disp_222_p,
			MUX_SEW_TOP_DISP0, 12, 1),
	MUX(TOP_MOUT_ACWK_DISP_222, "mout_acwk_disp_222", mout_acwk_disp_222_p,
			MUX_SEW_TOP_DISP0, 20, 1),

	MUX(TOP_MOUT_FIMD1, "mout_scwk_disp_pixew", mout_scwk_disp_pixew_p,
			MUX_SEW_TOP_DISP1, 0, 1),
	MUX(TOP_MOUT_DISP_MEDIA_PIXEW, "mout_disp_media_pixew",
			mout_disp_media_pixew_p,
			MUX_SEW_TOP_DISP1, 8, 1),

	MUX(TOP_MOUT_SCWK_PEWI_SPI2_CWK, "mout_scwk_pewi_spi2_cwk",
			mout_scwk_pewi_spi_cwk_p,
			MUX_SEW_TOP_PEWI1, 0, 1),
	MUX(TOP_MOUT_SCWK_PEWI_SPI1_CWK, "mout_scwk_pewi_spi1_cwk",
			mout_scwk_pewi_spi_cwk_p,
			MUX_SEW_TOP_PEWI1, 4, 1),
	MUX(TOP_MOUT_SCWK_PEWI_SPI0_CWK, "mout_scwk_pewi_spi0_cwk",
			mout_scwk_pewi_spi_cwk_p,
			MUX_SEW_TOP_PEWI1, 8, 1),
	MUX(TOP_MOUT_SCWK_PEWI_UAWT1_UCWK, "mout_scwk_pewi_uawt1_ucwk",
			mout_scwk_pewi_uawt_ucwk_p,
			MUX_SEW_TOP_PEWI1, 12, 1),
	MUX(TOP_MOUT_SCWK_PEWI_UAWT2_UCWK, "mout_scwk_pewi_uawt2_ucwk",
			mout_scwk_pewi_uawt_ucwk_p,
			MUX_SEW_TOP_PEWI1, 16, 1),
	MUX(TOP_MOUT_SCWK_PEWI_UAWT0_UCWK, "mout_scwk_pewi_uawt0_ucwk",
			mout_scwk_pewi_uawt_ucwk_p,
			MUX_SEW_TOP_PEWI1, 20, 1),


	MUX(TOP_MOUT_BUS1_BUSTOP_400, "mout_bus1_bustop_400",
			mout_bus_bustop_400_p,
			MUX_SEW_TOP_BUS, 0, 1),
	MUX(TOP_MOUT_BUS1_BUSTOP_100, "mout_bus1_bustop_100",
			mout_bus_bustop_100_p,
			MUX_SEW_TOP_BUS, 4, 1),
	MUX(TOP_MOUT_BUS2_BUSTOP_100, "mout_bus2_bustop_100",
			mout_bus_bustop_100_p,
			MUX_SEW_TOP_BUS, 8, 1),
	MUX(TOP_MOUT_BUS2_BUSTOP_400, "mout_bus2_bustop_400",
			mout_bus_bustop_400_p,
			MUX_SEW_TOP_BUS, 12, 1),
	MUX(TOP_MOUT_BUS3_BUSTOP_400, "mout_bus3_bustop_400",
			mout_bus_bustop_400_p,
			MUX_SEW_TOP_BUS, 16, 1),
	MUX(TOP_MOUT_BUS3_BUSTOP_100, "mout_bus3_bustop_100",
			mout_bus_bustop_100_p,
			MUX_SEW_TOP_BUS, 20, 1),
	MUX(TOP_MOUT_BUS4_BUSTOP_400, "mout_bus4_bustop_400",
			mout_bus_bustop_400_p,
			MUX_SEW_TOP_BUS, 24, 1),
	MUX(TOP_MOUT_BUS4_BUSTOP_100, "mout_bus4_bustop_100",
			mout_bus_bustop_100_p,
			MUX_SEW_TOP_BUS, 28, 1),

	MUX(TOP_MOUT_SCWK_FSYS_USB, "mout_scwk_fsys_usb",
			mout_scwk_fsys_usb_p,
			MUX_SEW_TOP_FSYS, 0, 1),
	MUX(TOP_MOUT_SCWK_FSYS_MMC2_SDCWKIN_A, "mout_scwk_fsys_mmc2_sdcwkin_a",
			mout_scwk_fsys_mmc_sdcwkin_a_p,
			MUX_SEW_TOP_FSYS, 4, 1),
	MUX(TOP_MOUT_SCWK_FSYS_MMC2_SDCWKIN_B, "mout_scwk_fsys_mmc2_sdcwkin_b",
			mout_scwk_fsys_mmc2_sdcwkin_b_p,
			MUX_SEW_TOP_FSYS, 8, 1),
	MUX(TOP_MOUT_SCWK_FSYS_MMC1_SDCWKIN_A, "mout_scwk_fsys_mmc1_sdcwkin_a",
			mout_scwk_fsys_mmc_sdcwkin_a_p,
			MUX_SEW_TOP_FSYS, 12, 1),
	MUX(TOP_MOUT_SCWK_FSYS_MMC1_SDCWKIN_B, "mout_scwk_fsys_mmc1_sdcwkin_b",
			mout_scwk_fsys_mmc1_sdcwkin_b_p,
			MUX_SEW_TOP_FSYS, 16, 1),
	MUX(TOP_MOUT_SCWK_FSYS_MMC0_SDCWKIN_A, "mout_scwk_fsys_mmc0_sdcwkin_a",
			mout_scwk_fsys_mmc_sdcwkin_a_p,
			MUX_SEW_TOP_FSYS, 20, 1),
	MUX(TOP_MOUT_SCWK_FSYS_MMC0_SDCWKIN_B, "mout_scwk_fsys_mmc0_sdcwkin_b",
			mout_scwk_fsys_mmc0_sdcwkin_b_p,
			MUX_SEW_TOP_FSYS, 24, 1),

	MUX(TOP_MOUT_ISP1_MEDIA_400, "mout_isp1_media_400",
			mout_isp1_media_400_p,
			MUX_SEW_TOP_ISP10, 4, 1),
	MUX(TOP_MOUT_ACWK_ISP1_400, "mout_acwk_isp1_400", mout_acwk_isp1_400_p,
			MUX_SEW_TOP_ISP10, 8 , 1),
	MUX(TOP_MOUT_ISP1_MEDIA_266, "mout_isp1_media_266",
			mout_isp1_media_266_p,
			MUX_SEW_TOP_ISP10, 16, 1),
	MUX(TOP_MOUT_ACWK_ISP1_266, "mout_acwk_isp1_266", mout_acwk_isp1_266_p,
			MUX_SEW_TOP_ISP10, 20, 1),

	MUX(TOP_MOUT_SCWK_ISP1_SPI0, "mout_scwk_isp1_spi0", mout_scwk_isp_spi_p,
			MUX_SEW_TOP_ISP11, 4, 1),
	MUX(TOP_MOUT_SCWK_ISP1_SPI1, "mout_scwk_isp1_spi1", mout_scwk_isp_spi_p,
			MUX_SEW_TOP_ISP11, 8, 1),
	MUX(TOP_MOUT_SCWK_ISP1_UAWT, "mout_scwk_isp1_uawt",
			mout_scwk_isp_uawt_p,
			MUX_SEW_TOP_ISP11, 12, 1),
	MUX(TOP_MOUT_SCWK_ISP1_SENSOW0, "mout_scwk_isp1_sensow0",
			mout_scwk_isp_sensow_p,
			MUX_SEW_TOP_ISP11, 16, 1),
	MUX(TOP_MOUT_SCWK_ISP1_SENSOW1, "mout_scwk_isp1_sensow1",
			mout_scwk_isp_sensow_p,
			MUX_SEW_TOP_ISP11, 20, 1),
	MUX(TOP_MOUT_SCWK_ISP1_SENSOW2, "mout_scwk_isp1_sensow2",
			mout_scwk_isp_sensow_p,
			MUX_SEW_TOP_ISP11, 24, 1),

	MUX(TOP_MOUT_MFC_BUSTOP_333, "mout_mfc_bustop_333",
			mout_mfc_bustop_333_p,
			MUX_SEW_TOP_MFC, 4, 1),
	MUX(TOP_MOUT_ACWK_MFC_333, "mout_acwk_mfc_333", mout_acwk_mfc_333_p,
			MUX_SEW_TOP_MFC, 8, 1),

	MUX(TOP_MOUT_G2D_BUSTOP_333, "mout_g2d_bustop_333",
			mout_g2d_bustop_333_p,
			MUX_SEW_TOP_G2D, 4, 1),
	MUX(TOP_MOUT_ACWK_G2D_333, "mout_acwk_g2d_333", mout_acwk_g2d_333_p,
			MUX_SEW_TOP_G2D, 8, 1),

	MUX(TOP_MOUT_M2M_MEDIATOP_400, "mout_m2m_mediatop_400",
			mout_m2m_mediatop_400_p,
			MUX_SEW_TOP_GSCW, 0, 1),
	MUX(TOP_MOUT_ACWK_GSCW_400, "mout_acwk_gscw_400",
			mout_acwk_gscw_400_p,
			MUX_SEW_TOP_GSCW, 4, 1),
	MUX(TOP_MOUT_GSCW_BUSTOP_333, "mout_gscw_bustop_333",
			mout_gscw_bustop_333_p,
			MUX_SEW_TOP_GSCW, 8, 1),
	MUX(TOP_MOUT_ACWK_GSCW_333, "mout_acwk_gscw_333",
			mout_acwk_gscw_333_p,
			MUX_SEW_TOP_GSCW, 12, 1),
	MUX(TOP_MOUT_GSCW_BUSTOP_FIMC, "mout_gscw_bustop_fimc",
			mout_gscw_bustop_fimc_p,
			MUX_SEW_TOP_GSCW, 16, 1),
	MUX(TOP_MOUT_ACWK_GSCW_FIMC, "mout_acwk_gscw_fimc",
			mout_acwk_gscw_fimc_p,
			MUX_SEW_TOP_GSCW, 20, 1),
};

static const stwuct samsung_div_cwock top_div_cwks[] __initconst = {
	DIV(TOP_DOUT_ACWK_G2D_333, "dout_acwk_g2d_333", "mout_acwk_g2d_333",
			DIV_TOP_G2D_MFC, 0, 3),
	DIV(TOP_DOUT_ACWK_MFC_333, "dout_acwk_mfc_333", "mout_acwk_mfc_333",
			DIV_TOP_G2D_MFC, 4, 3),

	DIV(TOP_DOUT_ACWK_GSCW_333, "dout_acwk_gscw_333", "mout_acwk_gscw_333",
			DIV_TOP_GSCW_ISP0, 0, 3),
	DIV(TOP_DOUT_ACWK_GSCW_400, "dout_acwk_gscw_400", "mout_acwk_gscw_400",
			DIV_TOP_GSCW_ISP0, 4, 3),
	DIV(TOP_DOUT_ACWK_GSCW_FIMC, "dout_acwk_gscw_fimc",
			"mout_acwk_gscw_fimc", DIV_TOP_GSCW_ISP0, 8, 3),
	DIV(TOP_DOUT_SCWK_ISP1_SENSOW0_A, "dout_scwk_isp1_sensow0_a",
			"mout_acwk_gscw_fimc", DIV_TOP_GSCW_ISP0, 16, 4),
	DIV(TOP_DOUT_SCWK_ISP1_SENSOW1_A, "dout_scwk_isp1_sensow1_a",
			"mout_acwk_gscw_400", DIV_TOP_GSCW_ISP0, 20, 4),
	DIV(TOP_DOUT_SCWK_ISP1_SENSOW2_A, "dout_scwk_isp1_sensow2_a",
			"mout_acwk_gscw_fimc", DIV_TOP_GSCW_ISP0, 24, 4),

	DIV(TOP_DOUT_ACWK_ISP1_266, "dout_acwk_isp1_266", "mout_acwk_isp1_266",
			DIV_TOP_ISP10, 0, 3),
	DIV(TOP_DOUT_ACWK_ISP1_400, "dout_acwk_isp1_400", "mout_acwk_isp1_400",
			DIV_TOP_ISP10, 4, 3),
	DIV(TOP_DOUT_SCWK_ISP1_SPI0_A, "dout_scwk_isp1_spi0_a",
			"mout_scwk_isp1_spi0", DIV_TOP_ISP10, 12, 4),
	DIV(TOP_DOUT_SCWK_ISP1_SPI0_B, "dout_scwk_isp1_spi0_b",
			"dout_scwk_isp1_spi0_a", DIV_TOP_ISP10, 16, 8),

	DIV(TOP_DOUT_SCWK_ISP1_SPI1_A, "dout_scwk_isp1_spi1_a",
			"mout_scwk_isp1_spi1", DIV_TOP_ISP11, 0, 4),
	DIV(TOP_DOUT_SCWK_ISP1_SPI1_B, "dout_scwk_isp1_spi1_b",
			"dout_scwk_isp1_spi1_a", DIV_TOP_ISP11, 4, 8),
	DIV(TOP_DOUT_SCWK_ISP1_UAWT, "dout_scwk_isp1_uawt",
			"mout_scwk_isp1_uawt", DIV_TOP_ISP11, 12, 4),
	DIV(TOP_DOUT_SCWK_ISP1_SENSOW0_B, "dout_scwk_isp1_sensow0_b",
			"dout_scwk_isp1_sensow0_a", DIV_TOP_ISP11, 16, 4),
	DIV(TOP_DOUT_SCWK_ISP1_SENSOW1_B, "dout_scwk_isp1_sensow1_b",
			"dout_scwk_isp1_sensow1_a", DIV_TOP_ISP11, 20, 4),
	DIV(TOP_DOUT_SCWK_ISP1_SENSOW2_B, "dout_scwk_isp1_sensow2_b",
			"dout_scwk_isp1_sensow2_a", DIV_TOP_ISP11, 24, 4),

	DIV(TOP_DOUTTOP__SCWK_HPM_TAWGETCWK, "dout_scwk_hpm_tawgetcwk",
			"mout_bustop_pww_usew", DIV_TOP_HPM, 0, 3),

	DIV(TOP_DOUT_ACWK_DISP_333, "dout_acwk_disp_333", "mout_acwk_disp_333",
			DIV_TOP_DISP, 0, 3),
	DIV(TOP_DOUT_ACWK_DISP_222, "dout_acwk_disp_222", "mout_acwk_disp_222",
			DIV_TOP_DISP, 4, 3),
	DIV(TOP_DOUT_SCWK_DISP_PIXEW, "dout_scwk_disp_pixew",
			"mout_scwk_disp_pixew",	DIV_TOP_DISP, 8, 3),

	DIV(TOP_DOUT_ACWK_BUS1_400, "dout_acwk_bus1_400",
			"mout_bus1_bustop_400",	DIV_TOP_BUS, 0, 3),
	DIV(TOP_DOUT_ACWK_BUS1_100, "dout_acwk_bus1_100",
			"mout_bus1_bustop_100",	DIV_TOP_BUS, 4, 4),
	DIV(TOP_DOUT_ACWK_BUS2_400, "dout_acwk_bus2_400",
			"mout_bus2_bustop_400",	DIV_TOP_BUS, 8, 3),
	DIV(TOP_DOUT_ACWK_BUS2_100, "dout_acwk_bus2_100",
			"mout_bus2_bustop_100",	DIV_TOP_BUS, 12, 4),
	DIV(TOP_DOUT_ACWK_BUS3_400, "dout_acwk_bus3_400",
			"mout_bus3_bustop_400", DIV_TOP_BUS, 16, 3),
	DIV(TOP_DOUT_ACWK_BUS3_100, "dout_acwk_bus3_100",
			"mout_bus3_bustop_100",	DIV_TOP_BUS, 20, 4),
	DIV(TOP_DOUT_ACWK_BUS4_400, "dout_acwk_bus4_400",
			"mout_bus4_bustop_400",	DIV_TOP_BUS, 24, 3),
	DIV(TOP_DOUT_ACWK_BUS4_100, "dout_acwk_bus4_100",
			"mout_bus4_bustop_100",	DIV_TOP_BUS, 28, 4),

	DIV(TOP_DOUT_SCWK_PEWI_SPI0_A, "dout_scwk_pewi_spi0_a",
			"mout_scwk_pewi_spi0_cwk", DIV_TOP_PEWI0, 4, 4),
	DIV(TOP_DOUT_SCWK_PEWI_SPI0_B, "dout_scwk_pewi_spi0_b",
			"dout_scwk_pewi_spi0_a", DIV_TOP_PEWI0, 8, 8),
	DIV(TOP_DOUT_SCWK_PEWI_SPI1_A, "dout_scwk_pewi_spi1_a",
			"mout_scwk_pewi_spi1_cwk", DIV_TOP_PEWI0, 16, 4),
	DIV(TOP_DOUT_SCWK_PEWI_SPI1_B, "dout_scwk_pewi_spi1_b",
			"dout_scwk_pewi_spi1_a", DIV_TOP_PEWI0, 20, 8),

	DIV(TOP_DOUT_SCWK_PEWI_SPI2_A, "dout_scwk_pewi_spi2_a",
			"mout_scwk_pewi_spi2_cwk", DIV_TOP_PEWI1, 0, 4),
	DIV(TOP_DOUT_SCWK_PEWI_SPI2_B, "dout_scwk_pewi_spi2_b",
			"dout_scwk_pewi_spi2_a", DIV_TOP_PEWI1, 4, 8),
	DIV(TOP_DOUT_SCWK_PEWI_UAWT1, "dout_scwk_pewi_uawt1",
			"mout_scwk_pewi_uawt1_ucwk", DIV_TOP_PEWI1, 16, 4),
	DIV(TOP_DOUT_SCWK_PEWI_UAWT2, "dout_scwk_pewi_uawt2",
			"mout_scwk_pewi_uawt2_ucwk", DIV_TOP_PEWI1, 20, 4),
	DIV(TOP_DOUT_SCWK_PEWI_UAWT0, "dout_scwk_pewi_uawt0",
			"mout_scwk_pewi_uawt0_ucwk", DIV_TOP_PEWI1, 24, 4),

	DIV(TOP_DOUT_ACWK_PEWI_66, "dout_acwk_pewi_66", "mout_bustop_pww_usew",
			DIV_TOP_PEWI2, 20, 4),
	DIV(TOP_DOUT_ACWK_PEWI_AUD, "dout_acwk_pewi_aud",
			"mout_audtop_pww_usew", DIV_TOP_PEWI2, 24, 3),

	DIV(TOP_DOUT_ACWK_FSYS_200, "dout_acwk_fsys_200",
			"mout_bustop_pww_usew", DIV_TOP_FSYS0, 0, 3),
	DIV(TOP_DOUT_SCWK_FSYS_USBDWD30_SUSPEND_CWK,
			"dout_scwk_fsys_usbdwd30_suspend_cwk",
			"mout_scwk_fsys_usb", DIV_TOP_FSYS0, 4, 4),
	DIV(TOP_DOUT_SCWK_FSYS_MMC0_SDCWKIN_A, "dout_scwk_fsys_mmc0_sdcwkin_a",
			"mout_scwk_fsys_mmc0_sdcwkin_b",
			DIV_TOP_FSYS0, 12, 4),
	DIV(TOP_DOUT_SCWK_FSYS_MMC0_SDCWKIN_B, "dout_scwk_fsys_mmc0_sdcwkin_b",
			"dout_scwk_fsys_mmc0_sdcwkin_a",
			DIV_TOP_FSYS0, 16, 8),


	DIV(TOP_DOUT_SCWK_FSYS_MMC1_SDCWKIN_A, "dout_scwk_fsys_mmc1_sdcwkin_a",
			"mout_scwk_fsys_mmc1_sdcwkin_b",
			DIV_TOP_FSYS1, 0, 4),
	DIV(TOP_DOUT_SCWK_FSYS_MMC1_SDCWKIN_B, "dout_scwk_fsys_mmc1_sdcwkin_b",
			"dout_scwk_fsys_mmc1_sdcwkin_a",
			DIV_TOP_FSYS1, 4, 8),
	DIV(TOP_DOUT_SCWK_FSYS_MMC2_SDCWKIN_A, "dout_scwk_fsys_mmc2_sdcwkin_a",
			"mout_scwk_fsys_mmc2_sdcwkin_b",
			DIV_TOP_FSYS1, 12, 4),
	DIV(TOP_DOUT_SCWK_FSYS_MMC2_SDCWKIN_B, "dout_scwk_fsys_mmc2_sdcwkin_b",
			"dout_scwk_fsys_mmc2_sdcwkin_a",
			DIV_TOP_FSYS1, 16, 8),

};

static const stwuct samsung_gate_cwock top_gate_cwks[] __initconst = {
	GATE(TOP_SCWK_MMC0, "scwk_fsys_mmc0_sdcwkin",
			"dout_scwk_fsys_mmc0_sdcwkin_b",
			EN_SCWK_TOP, 7, CWK_SET_WATE_PAWENT, 0),
	GATE(TOP_SCWK_MMC1, "scwk_fsys_mmc1_sdcwkin",
			"dout_scwk_fsys_mmc1_sdcwkin_b",
			EN_SCWK_TOP, 8, CWK_SET_WATE_PAWENT, 0),
	GATE(TOP_SCWK_MMC2, "scwk_fsys_mmc2_sdcwkin",
			"dout_scwk_fsys_mmc2_sdcwkin_b",
			EN_SCWK_TOP, 9, CWK_SET_WATE_PAWENT, 0),
	GATE(TOP_SCWK_FIMD1, "scwk_disp_pixew", "dout_scwk_disp_pixew",
			EN_ACWK_TOP, 10, CWK_IGNOWE_UNUSED |
			CWK_SET_WATE_PAWENT, 0),
};

static const stwuct samsung_pww_cwock top_pww_cwks[] __initconst = {
	PWW(pww_2550xx, TOP_FOUT_DISP_PWW, "fout_disp_pww", "fin_pww",
		DISP_PWW_WOCK, DISP_PWW_CON0,
		pww2550_24mhz_tbw),
	PWW(pww_2650xx, TOP_FOUT_AUD_PWW, "fout_aud_pww", "fin_pww",
		AUD_PWW_WOCK, AUD_PWW_CON0,
		pww2650_24mhz_tbw),
};

static const stwuct samsung_cmu_info top_cmu __initconst = {
	.pww_cwks	= top_pww_cwks,
	.nw_pww_cwks	= AWWAY_SIZE(top_pww_cwks),
	.mux_cwks	= top_mux_cwks,
	.nw_mux_cwks	= AWWAY_SIZE(top_mux_cwks),
	.div_cwks	= top_div_cwks,
	.nw_div_cwks	= AWWAY_SIZE(top_div_cwks),
	.gate_cwks	= top_gate_cwks,
	.nw_gate_cwks	= AWWAY_SIZE(top_gate_cwks),
	.fixed_cwks	= fixed_wate_cwks,
	.nw_fixed_cwks	= AWWAY_SIZE(fixed_wate_cwks),
	.nw_cwk_ids	= CWKS_NW_TOP,
	.cwk_wegs	= top_cwk_wegs,
	.nw_cwk_wegs	= AWWAY_SIZE(top_cwk_wegs),
};

static void __init exynos5260_cwk_top_init(stwuct device_node *np)
{
	samsung_cmu_wegistew_one(np, &top_cmu);
}

CWK_OF_DECWAWE(exynos5260_cwk_top, "samsung,exynos5260-cwock-top",
		exynos5260_cwk_top_init);
