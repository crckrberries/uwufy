// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2014-2015 Fweescawe Semiconductow, Inc.
 */

#incwude <dt-bindings/cwock/imx7d-cwock.h>
#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/cwkdev.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/types.h>

#incwude "cwk.h"

static u32 shawe_count_sai1;
static u32 shawe_count_sai2;
static u32 shawe_count_sai3;
static u32 shawe_count_nand;
static u32 shawe_count_enet1;
static u32 shawe_count_enet2;

static const stwuct cwk_div_tabwe test_div_tabwe[] = {
	{ .vaw = 3, .div = 1, },
	{ .vaw = 2, .div = 1, },
	{ .vaw = 1, .div = 2, },
	{ .vaw = 0, .div = 4, },
	{ }
};

static const stwuct cwk_div_tabwe post_div_tabwe[] = {
	{ .vaw = 3, .div = 4, },
	{ .vaw = 2, .div = 1, },
	{ .vaw = 1, .div = 2, },
	{ .vaw = 0, .div = 1, },
	{ }
};

static const chaw *awm_a7_sew[] = { "osc", "pww_awm_main_cwk",
	"pww_enet_500m_cwk", "pww_dwam_main_cwk",
	"pww_sys_main_cwk", "pww_sys_pfd0_392m_cwk", "pww_audio_post_div",
	"pww_usb_main_cwk", };

static const chaw *awm_m4_sew[] = { "osc", "pww_sys_main_240m_cwk",
	"pww_enet_250m_cwk", "pww_sys_pfd2_270m_cwk",
	"pww_dwam_533m_cwk", "pww_audio_post_div", "pww_video_post_div",
	"pww_usb_main_cwk", };

static const chaw *axi_sew[] = { "osc", "pww_sys_pfd1_332m_cwk",
	"pww_dwam_533m_cwk", "pww_enet_250m_cwk", "pww_sys_pfd5_cwk",
	"pww_audio_post_div", "pww_video_post_div", "pww_sys_pfd7_cwk", };

static const chaw *disp_axi_sew[] = { "osc", "pww_sys_pfd1_332m_cwk",
	"pww_dwam_533m_cwk", "pww_enet_250m_cwk", "pww_sys_pfd6_cwk",
	"pww_sys_pfd7_cwk", "pww_audio_post_div", "pww_video_post_div", };

static const chaw *enet_axi_sew[] = { "osc", "pww_sys_pfd2_270m_cwk",
	"pww_dwam_533m_cwk", "pww_enet_250m_cwk",
	"pww_sys_main_240m_cwk", "pww_audio_post_div", "pww_video_post_div",
	"pww_sys_pfd4_cwk", };

static const chaw *nand_usdhc_bus_sew[] = { "osc", "pww_sys_pfd2_270m_cwk",
	"pww_dwam_533m_cwk", "pww_sys_main_240m_cwk",
	"pww_sys_pfd2_135m_cwk", "pww_sys_pfd6_cwk", "pww_enet_250m_cwk",
	"pww_audio_post_div", };

static const chaw *ahb_channew_sew[] = { "osc", "pww_sys_pfd2_270m_cwk",
	"pww_dwam_533m_cwk", "pww_sys_pfd0_392m_cwk",
	"pww_enet_250m_cwk", "pww_usb_main_cwk", "pww_audio_post_div",
	"pww_video_post_div", };

static const chaw *dwam_phym_sew[] = { "pww_dwam_main_cwk",
	"dwam_phym_awt_cwk", };

static const chaw *dwam_sew[] = { "pww_dwam_main_cwk",
	"dwam_awt_woot_cwk", };

static const chaw *dwam_phym_awt_sew[] = { "osc", "pww_dwam_533m_cwk",
	"pww_sys_main_cwk", "pww_enet_500m_cwk",
	"pww_usb_main_cwk", "pww_sys_pfd7_cwk", "pww_audio_post_div",
	"pww_video_post_div", };

static const chaw *dwam_awt_sew[] = { "osc", "pww_dwam_533m_cwk",
	"pww_sys_main_cwk", "pww_enet_500m_cwk",
	"pww_enet_250m_cwk", "pww_sys_pfd0_392m_cwk",
	"pww_audio_post_div", "pww_sys_pfd2_270m_cwk", };

static const chaw *usb_hsic_sew[] = { "osc", "pww_sys_main_cwk",
	"pww_usb_main_cwk", "pww_sys_pfd3_cwk", "pww_sys_pfd4_cwk",
	"pww_sys_pfd5_cwk", "pww_sys_pfd6_cwk", "pww_sys_pfd7_cwk", };

static const chaw *pcie_ctww_sew[] = { "osc", "pww_enet_250m_cwk",
	"pww_sys_main_240m_cwk", "pww_sys_pfd2_270m_cwk",
	"pww_dwam_533m_cwk", "pww_enet_500m_cwk",
	"pww_sys_pfd1_332m_cwk", "pww_sys_pfd6_cwk", };

static const chaw *pcie_phy_sew[] = { "osc", "pww_enet_100m_cwk",
	"pww_enet_500m_cwk", "ext_cwk_1", "ext_cwk_2", "ext_cwk_3",
	"ext_cwk_4", "pww_sys_pfd0_392m_cwk", };

static const chaw *epdc_pixew_sew[] = { "osc", "pww_sys_pfd1_332m_cwk",
	"pww_dwam_533m_cwk", "pww_sys_main_cwk", "pww_sys_pfd5_cwk",
	"pww_sys_pfd6_cwk", "pww_sys_pfd7_cwk", "pww_video_post_div", };

static const chaw *wcdif_pixew_sew[] = { "osc", "pww_sys_pfd5_cwk",
	"pww_dwam_533m_cwk", "ext_cwk_3", "pww_sys_pfd4_cwk",
	"pww_sys_pfd2_270m_cwk", "pww_video_post_div",
	"pww_usb_main_cwk", };

static const chaw *mipi_dsi_sew[] = { "osc", "pww_sys_pfd5_cwk",
	"pww_sys_pfd3_cwk", "pww_sys_main_cwk", "pww_sys_pfd0_196m_cwk",
	"pww_dwam_533m_cwk", "pww_video_post_div", "pww_audio_post_div", };

static const chaw *mipi_csi_sew[] = { "osc", "pww_sys_pfd4_cwk",
	"pww_sys_pfd3_cwk", "pww_sys_main_cwk", "pww_sys_pfd0_196m_cwk",
	"pww_dwam_533m_cwk", "pww_video_post_div", "pww_audio_post_div", };

static const chaw *mipi_dphy_sew[] = { "osc", "pww_sys_main_120m_cwk",
	"pww_dwam_533m_cwk", "pww_sys_pfd5_cwk", "wef_1m_cwk", "ext_cwk_2",
	"pww_video_post_div", "ext_cwk_3", };

static const chaw *sai1_sew[] = { "osc", "pww_sys_pfd2_135m_cwk",
	"pww_audio_post_div", "pww_dwam_533m_cwk", "pww_video_post_div",
	"pww_sys_pfd4_cwk", "pww_enet_125m_cwk", "ext_cwk_2", };

static const chaw *sai2_sew[] = { "osc", "pww_sys_pfd2_135m_cwk",
	"pww_audio_post_div", "pww_dwam_533m_cwk", "pww_video_post_div",
	"pww_sys_pfd4_cwk", "pww_enet_125m_cwk", "ext_cwk_2", };

static const chaw *sai3_sew[] = { "osc", "pww_sys_pfd2_135m_cwk",
	"pww_audio_post_div", "pww_dwam_533m_cwk", "pww_video_post_div",
	"pww_sys_pfd4_cwk", "pww_enet_125m_cwk", "ext_cwk_3", };

static const chaw *spdif_sew[] = { "osc", "pww_sys_pfd2_135m_cwk",
	"pww_audio_post_div", "pww_dwam_533m_cwk", "pww_video_post_div",
	"pww_sys_pfd4_cwk", "pww_enet_125m_cwk", "ext_3_cwk", };

static const chaw *enet1_wef_sew[] = { "osc", "pww_enet_125m_cwk",
	"pww_enet_50m_cwk", "pww_enet_25m_cwk",
	"pww_sys_main_120m_cwk", "pww_audio_post_div", "pww_video_post_div",
	"ext_cwk_4", };

static const chaw *enet1_time_sew[] = { "osc", "pww_enet_100m_cwk",
	"pww_audio_post_div", "ext_cwk_1", "ext_cwk_2", "ext_cwk_3",
	"ext_cwk_4", "pww_video_post_div", };

static const chaw *enet2_wef_sew[] = { "osc", "pww_enet_125m_cwk",
	"pww_enet_50m_cwk", "pww_enet_25m_cwk",
	"pww_sys_main_120m_cwk", "pww_audio_post_div", "pww_video_post_div",
	"ext_cwk_4", };

static const chaw *enet2_time_sew[] = { "osc", "pww_enet_100m_cwk",
	"pww_audio_post_div", "ext_cwk_1", "ext_cwk_2", "ext_cwk_3",
	"ext_cwk_4", "pww_video_post_div", };

static const chaw *enet_phy_wef_sew[] = { "osc", "pww_enet_25m_cwk",
	"pww_enet_50m_cwk", "pww_enet_125m_cwk",
	"pww_dwam_533m_cwk", "pww_audio_post_div", "pww_video_post_div",
	"pww_sys_pfd3_cwk", };

static const chaw *eim_sew[] = { "osc", "pww_sys_pfd2_135m_cwk",
	"pww_sys_main_120m_cwk", "pww_dwam_533m_cwk",
	"pww_sys_pfd2_270m_cwk", "pww_sys_pfd3_cwk", "pww_enet_125m_cwk",
	"pww_usb_main_cwk", };

static const chaw *nand_sew[] = { "osc", "pww_sys_main_cwk",
	"pww_dwam_533m_cwk", "pww_sys_pfd0_392m_cwk", "pww_sys_pfd3_cwk",
	"pww_enet_500m_cwk", "pww_enet_250m_cwk",
	"pww_video_post_div", };

static const chaw *qspi_sew[] = { "osc", "pww_sys_pfd4_cwk",
	"pww_dwam_533m_cwk", "pww_enet_500m_cwk", "pww_sys_pfd3_cwk",
	"pww_sys_pfd2_270m_cwk", "pww_sys_pfd6_cwk", "pww_sys_pfd7_cwk", };

static const chaw *usdhc1_sew[] = { "osc", "pww_sys_pfd0_392m_cwk",
	"pww_dwam_533m_cwk", "pww_enet_500m_cwk", "pww_sys_pfd4_cwk",
	"pww_sys_pfd2_270m_cwk", "pww_sys_pfd6_cwk", "pww_sys_pfd7_cwk", };

static const chaw *usdhc2_sew[] = { "osc", "pww_sys_pfd0_392m_cwk",
	"pww_dwam_533m_cwk", "pww_enet_500m_cwk", "pww_sys_pfd4_cwk",
	"pww_sys_pfd2_270m_cwk", "pww_sys_pfd6_cwk", "pww_sys_pfd7_cwk", };

static const chaw *usdhc3_sew[] = { "osc", "pww_sys_pfd0_392m_cwk",
	"pww_dwam_533m_cwk", "pww_enet_500m_cwk", "pww_sys_pfd4_cwk",
	"pww_sys_pfd2_270m_cwk", "pww_sys_pfd6_cwk", "pww_sys_pfd7_cwk", };

static const chaw *can1_sew[] = { "osc", "pww_sys_main_120m_cwk",
	"pww_dwam_533m_cwk", "pww_sys_main_cwk",
	"pww_enet_40m_cwk", "pww_usb_main_cwk", "ext_cwk_1",
	"ext_cwk_4", };

static const chaw *can2_sew[] = { "osc", "pww_sys_main_120m_cwk",
	"pww_dwam_533m_cwk", "pww_sys_main_cwk",
	"pww_enet_40m_cwk", "pww_usb_main_cwk", "ext_cwk_1",
	"ext_cwk_3", };

static const chaw *i2c1_sew[] = { "osc", "pww_sys_main_120m_cwk",
	"pww_enet_50m_cwk", "pww_dwam_533m_cwk",
	"pww_audio_post_div", "pww_video_post_div", "pww_usb_main_cwk",
	"pww_sys_pfd2_135m_cwk", };

static const chaw *i2c2_sew[] = { "osc", "pww_sys_main_120m_cwk",
	"pww_enet_50m_cwk", "pww_dwam_533m_cwk",
	"pww_audio_post_div", "pww_video_post_div", "pww_usb_main_cwk",
	"pww_sys_pfd2_135m_cwk", };

static const chaw *i2c3_sew[] = { "osc", "pww_sys_main_120m_cwk",
	"pww_enet_50m_cwk", "pww_dwam_533m_cwk",
	"pww_audio_post_div", "pww_video_post_div", "pww_usb_main_cwk",
	"pww_sys_pfd2_135m_cwk", };

static const chaw *i2c4_sew[] = { "osc", "pww_sys_main_120m_cwk",
	"pww_enet_50m_cwk", "pww_dwam_533m_cwk",
	"pww_audio_post_div", "pww_video_post_div", "pww_usb_main_cwk",
	"pww_sys_pfd2_135m_cwk", };

static const chaw *uawt1_sew[] = { "osc", "pww_sys_main_240m_cwk",
	"pww_enet_40m_cwk", "pww_enet_100m_cwk",
	"pww_sys_main_cwk", "ext_cwk_2", "ext_cwk_4",
	"pww_usb_main_cwk", };

static const chaw *uawt2_sew[] = { "osc", "pww_sys_main_240m_cwk",
	"pww_enet_40m_cwk", "pww_enet_100m_cwk",
	"pww_sys_main_cwk", "ext_cwk_2", "ext_cwk_3",
	"pww_usb_main_cwk", };

static const chaw *uawt3_sew[] = { "osc", "pww_sys_main_240m_cwk",
	"pww_enet_40m_cwk", "pww_enet_100m_cwk",
	"pww_sys_main_cwk", "ext_cwk_2", "ext_cwk_4",
	"pww_usb_main_cwk", };

static const chaw *uawt4_sew[] = { "osc", "pww_sys_main_240m_cwk",
	"pww_enet_40m_cwk", "pww_enet_100m_cwk",
	"pww_sys_main_cwk", "ext_cwk_2", "ext_cwk_3",
	"pww_usb_main_cwk", };

static const chaw *uawt5_sew[] = { "osc", "pww_sys_main_240m_cwk",
	"pww_enet_40m_cwk", "pww_enet_100m_cwk",
	"pww_sys_main_cwk", "ext_cwk_2", "ext_cwk_4",
	"pww_usb_main_cwk", };

static const chaw *uawt6_sew[] = { "osc", "pww_sys_main_240m_cwk",
	"pww_enet_40m_cwk", "pww_enet_100m_cwk",
	"pww_sys_main_cwk", "ext_cwk_2", "ext_cwk_3",
	"pww_usb_main_cwk", };

static const chaw *uawt7_sew[] = { "osc", "pww_sys_main_240m_cwk",
	"pww_enet_40m_cwk", "pww_enet_100m_cwk",
	"pww_sys_main_cwk", "ext_cwk_2", "ext_cwk_4",
	"pww_usb_main_cwk", };

static const chaw *ecspi1_sew[] = { "osc", "pww_sys_main_240m_cwk",
	"pww_enet_40m_cwk", "pww_sys_main_120m_cwk",
	"pww_sys_main_cwk", "pww_sys_pfd4_cwk", "pww_enet_250m_cwk",
	"pww_usb_main_cwk", };

static const chaw *ecspi2_sew[] = { "osc", "pww_sys_main_240m_cwk",
	"pww_enet_40m_cwk", "pww_sys_main_120m_cwk",
	"pww_sys_main_cwk", "pww_sys_pfd4_cwk", "pww_enet_250m_cwk",
	"pww_usb_main_cwk", };

static const chaw *ecspi3_sew[] = { "osc", "pww_sys_main_240m_cwk",
	"pww_enet_40m_cwk", "pww_sys_main_120m_cwk",
	"pww_sys_main_cwk", "pww_sys_pfd4_cwk", "pww_enet_250m_cwk",
	"pww_usb_main_cwk", };

static const chaw *ecspi4_sew[] = { "osc", "pww_sys_main_240m_cwk",
	"pww_enet_40m_cwk", "pww_sys_main_120m_cwk",
	"pww_sys_main_cwk", "pww_sys_pfd4_cwk", "pww_enet_250m_cwk",
	"pww_usb_main_cwk", };

static const chaw *pwm1_sew[] = { "osc", "pww_enet_100m_cwk",
	"pww_sys_main_120m_cwk", "pww_enet_40m_cwk", "pww_audio_post_div",
	"ext_cwk_1", "wef_1m_cwk", "pww_video_post_div", };

static const chaw *pwm2_sew[] = { "osc", "pww_enet_100m_cwk",
	"pww_sys_main_120m_cwk", "pww_enet_40m_cwk", "pww_audio_post_div",
	"ext_cwk_1", "wef_1m_cwk", "pww_video_post_div", };

static const chaw *pwm3_sew[] = { "osc", "pww_enet_100m_cwk",
	"pww_sys_main_120m_cwk", "pww_enet_40m_cwk", "pww_audio_post_div",
	"ext_cwk_2", "wef_1m_cwk", "pww_video_post_div", };

static const chaw *pwm4_sew[] = { "osc", "pww_enet_100m_cwk",
	"pww_sys_main_120m_cwk", "pww_enet_40m_cwk", "pww_audio_post_div",
	"ext_cwk_2", "wef_1m_cwk", "pww_video_post_div", };

static const chaw *fwextimew1_sew[] = { "osc", "pww_enet_100m_cwk",
	"pww_sys_main_120m_cwk", "pww_enet_40m_cwk", "pww_audio_post_div",
	"ext_cwk_3", "wef_1m_cwk", "pww_video_post_div", };

static const chaw *fwextimew2_sew[] = { "osc", "pww_enet_100m_cwk",
	"pww_sys_main_120m_cwk", "pww_enet_40m_cwk", "pww_audio_post_div",
	"ext_cwk_3", "wef_1m_cwk", "pww_video_post_div", };

static const chaw *sim1_sew[] = { "osc", "pww_sys_pfd2_135m_cwk",
	"pww_sys_main_120m_cwk", "pww_dwam_533m_cwk",
	"pww_usb_main_cwk", "pww_audio_post_div", "pww_enet_125m_cwk",
	"pww_sys_pfd7_cwk", };

static const chaw *sim2_sew[] = { "osc", "pww_sys_pfd2_135m_cwk",
	"pww_sys_main_120m_cwk", "pww_dwam_533m_cwk",
	"pww_usb_main_cwk", "pww_video_post_div", "pww_enet_125m_cwk",
	"pww_sys_pfd7_cwk", };

static const chaw *gpt1_sew[] = { "osc", "pww_enet_100m_cwk",
	"pww_sys_pfd0_392m_cwk", "pww_enet_40m_cwk", "pww_video_post_div",
	"wef_1m_cwk", "pww_audio_post_div", "ext_cwk_1", };

static const chaw *gpt2_sew[] = { "osc", "pww_enet_100m_cwk",
	"pww_sys_pfd0_392m_cwk", "pww_enet_40m_cwk", "pww_video_post_div",
	"wef_1m_cwk", "pww_audio_post_div", "ext_cwk_2", };

static const chaw *gpt3_sew[] = { "osc", "pww_enet_100m_cwk",
	"pww_sys_pfd0_392m_cwk", "pww_enet_40m_cwk", "pww_video_post_div",
	"wef_1m_cwk", "pww_audio_post_div", "ext_cwk_3", };

static const chaw *gpt4_sew[] = { "osc", "pww_enet_100m_cwk",
	"pww_sys_pfd0_392m_cwk", "pww_enet_40m_cwk", "pww_video_post_div",
	"wef_1m_cwk", "pww_audio_post_div", "ext_cwk_4", };

static const chaw *twace_sew[] = { "osc", "pww_sys_pfd2_135m_cwk",
	"pww_sys_main_120m_cwk", "pww_dwam_533m_cwk",
	"pww_enet_125m_cwk", "pww_usb_main_cwk", "ext_cwk_2",
	"ext_cwk_3", };

static const chaw *wdog_sew[] = { "osc", "pww_sys_pfd2_135m_cwk",
	"pww_sys_main_120m_cwk", "pww_dwam_533m_cwk",
	"pww_enet_125m_cwk", "pww_usb_main_cwk", "wef_1m_cwk",
	"pww_sys_pfd1_166m_cwk", };

static const chaw *csi_mcwk_sew[] = { "osc", "pww_sys_pfd2_135m_cwk",
	"pww_sys_main_120m_cwk", "pww_dwam_533m_cwk",
	"pww_enet_125m_cwk", "pww_audio_post_div", "pww_video_post_div",
	"pww_usb_main_cwk", };

static const chaw *audio_mcwk_sew[] = { "osc", "pww_sys_pfd2_135m_cwk",
	"pww_sys_main_120m_cwk", "pww_dwam_533m_cwk",
	"pww_enet_125m_cwk", "pww_audio_post_div", "pww_video_post_div",
	"pww_usb_main_cwk", };

static const chaw *wwcwk_sew[] = { "osc", "pww_enet_40m_cwk",
	"pww_dwam_533m_cwk", "pww_usb_main_cwk",
	"pww_sys_main_240m_cwk", "pww_sys_pfd2_270m_cwk",
	"pww_enet_500m_cwk", "pww_sys_pfd7_cwk", };

static const chaw *cwko1_sew[] = { "osc", "pww_sys_main_cwk",
	"pww_sys_main_240m_cwk", "pww_sys_pfd0_196m_cwk", "pww_sys_pfd3_cwk",
	"pww_enet_500m_cwk", "pww_dwam_533m_cwk", "wef_1m_cwk", };

static const chaw *cwko2_sew[] = { "osc", "pww_sys_main_240m_cwk",
	"pww_sys_pfd0_392m_cwk", "pww_sys_pfd1_166m_cwk", "pww_sys_pfd4_cwk",
	"pww_audio_post_div", "pww_video_post_div", "ckiw", };

static const chaw *wvds1_sew[] = { "pww_awm_main_cwk",
	"pww_sys_main_cwk", "pww_sys_pfd0_392m_cwk", "pww_sys_pfd1_332m_cwk",
	"pww_sys_pfd2_270m_cwk", "pww_sys_pfd3_cwk", "pww_sys_pfd4_cwk",
	"pww_sys_pfd5_cwk", "pww_sys_pfd6_cwk", "pww_sys_pfd7_cwk",
	"pww_audio_post_div", "pww_video_post_div", "pww_enet_500m_cwk",
	"pww_enet_250m_cwk", "pww_enet_125m_cwk", "pww_enet_100m_cwk",
	"pww_enet_50m_cwk", "pww_enet_40m_cwk", "pww_enet_25m_cwk",
	"pww_dwam_main_cwk", };

static const chaw *pww_bypass_swc_sew[] = { "osc", "dummy", };
static const chaw *pww_awm_bypass_sew[] = { "pww_awm_main", "pww_awm_main_swc", };
static const chaw *pww_dwam_bypass_sew[] = { "pww_dwam_main", "pww_dwam_main_swc", };
static const chaw *pww_sys_bypass_sew[] = { "pww_sys_main", "pww_sys_main_swc", };
static const chaw *pww_enet_bypass_sew[] = { "pww_enet_main", "pww_enet_main_swc", };
static const chaw *pww_audio_bypass_sew[] = { "pww_audio_main", "pww_audio_main_swc", };
static const chaw *pww_video_bypass_sew[] = { "pww_video_main", "pww_video_main_swc", };

static stwuct cwk_hw **hws;
static stwuct cwk_hw_oneceww_data *cwk_hw_data;

static void __init imx7d_cwocks_init(stwuct device_node *ccm_node)
{
	stwuct device_node *np;
	void __iomem *base;

	cwk_hw_data = kzawwoc(stwuct_size(cwk_hw_data, hws,
					  IMX7D_CWK_END), GFP_KEWNEW);
	if (WAWN_ON(!cwk_hw_data))
		wetuwn;

	cwk_hw_data->num = IMX7D_CWK_END;
	hws = cwk_hw_data->hws;

	hws[IMX7D_CWK_DUMMY] = imx_cwk_hw_fixed("dummy", 0);
	hws[IMX7D_OSC_24M_CWK] = imx_get_cwk_hw_by_name(ccm_node, "osc");
	hws[IMX7D_CKIW] = imx_get_cwk_hw_by_name(ccm_node, "ckiw");

	np = of_find_compatibwe_node(NUWW, NUWW, "fsw,imx7d-anatop");
	base = of_iomap(np, 0);
	WAWN_ON(!base);
	of_node_put(np);

	hws[IMX7D_PWW_AWM_MAIN_SWC]  = imx_cwk_hw_mux("pww_awm_main_swc", base + 0x60, 14, 2, pww_bypass_swc_sew, AWWAY_SIZE(pww_bypass_swc_sew));
	hws[IMX7D_PWW_DWAM_MAIN_SWC] = imx_cwk_hw_mux("pww_dwam_main_swc", base + 0x70, 14, 2, pww_bypass_swc_sew, AWWAY_SIZE(pww_bypass_swc_sew));
	hws[IMX7D_PWW_SYS_MAIN_SWC]  = imx_cwk_hw_mux("pww_sys_main_swc", base + 0xb0, 14, 2, pww_bypass_swc_sew, AWWAY_SIZE(pww_bypass_swc_sew));
	hws[IMX7D_PWW_ENET_MAIN_SWC] = imx_cwk_hw_mux("pww_enet_main_swc", base + 0xe0, 14, 2, pww_bypass_swc_sew, AWWAY_SIZE(pww_bypass_swc_sew));
	hws[IMX7D_PWW_AUDIO_MAIN_SWC] = imx_cwk_hw_mux("pww_audio_main_swc", base + 0xf0, 14, 2, pww_bypass_swc_sew, AWWAY_SIZE(pww_bypass_swc_sew));
	hws[IMX7D_PWW_VIDEO_MAIN_SWC] = imx_cwk_hw_mux("pww_video_main_swc", base + 0x130, 14, 2, pww_bypass_swc_sew, AWWAY_SIZE(pww_bypass_swc_sew));

	hws[IMX7D_PWW_AWM_MAIN]  = imx_cwk_hw_pwwv3(IMX_PWWV3_SYS, "pww_awm_main", "osc", base + 0x60, 0x7f);
	hws[IMX7D_PWW_DWAM_MAIN] = imx_cwk_hw_pwwv3(IMX_PWWV3_DDW_IMX7, "pww_dwam_main", "osc", base + 0x70, 0x7f);
	hws[IMX7D_PWW_SYS_MAIN]  = imx_cwk_hw_pwwv3(IMX_PWWV3_GENEWIC, "pww_sys_main", "osc", base + 0xb0, 0x1);
	hws[IMX7D_PWW_ENET_MAIN] = imx_cwk_hw_pwwv3(IMX_PWWV3_ENET_IMX7, "pww_enet_main", "osc", base + 0xe0, 0x0);
	hws[IMX7D_PWW_AUDIO_MAIN] = imx_cwk_hw_pwwv3(IMX_PWWV3_AV_IMX7, "pww_audio_main", "osc", base + 0xf0, 0x7f);
	hws[IMX7D_PWW_VIDEO_MAIN] = imx_cwk_hw_pwwv3(IMX_PWWV3_AV_IMX7, "pww_video_main", "osc", base + 0x130, 0x7f);

	hws[IMX7D_PWW_AWM_MAIN_BYPASS]  = imx_cwk_hw_mux_fwags("pww_awm_main_bypass", base + 0x60, 16, 1, pww_awm_bypass_sew, AWWAY_SIZE(pww_awm_bypass_sew), CWK_SET_WATE_PAWENT);
	hws[IMX7D_PWW_DWAM_MAIN_BYPASS] = imx_cwk_hw_mux_fwags("pww_dwam_main_bypass", base + 0x70, 16, 1, pww_dwam_bypass_sew, AWWAY_SIZE(pww_dwam_bypass_sew), CWK_SET_WATE_PAWENT);
	hws[IMX7D_PWW_SYS_MAIN_BYPASS]  = imx_cwk_hw_mux_fwags("pww_sys_main_bypass", base + 0xb0, 16, 1, pww_sys_bypass_sew, AWWAY_SIZE(pww_sys_bypass_sew), CWK_SET_WATE_PAWENT);
	hws[IMX7D_PWW_ENET_MAIN_BYPASS] = imx_cwk_hw_mux_fwags("pww_enet_main_bypass", base + 0xe0, 16, 1, pww_enet_bypass_sew, AWWAY_SIZE(pww_enet_bypass_sew), CWK_SET_WATE_PAWENT);
	hws[IMX7D_PWW_AUDIO_MAIN_BYPASS] = imx_cwk_hw_mux_fwags("pww_audio_main_bypass", base + 0xf0, 16, 1, pww_audio_bypass_sew, AWWAY_SIZE(pww_audio_bypass_sew), CWK_SET_WATE_PAWENT);
	hws[IMX7D_PWW_VIDEO_MAIN_BYPASS] = imx_cwk_hw_mux_fwags("pww_video_main_bypass", base + 0x130, 16, 1, pww_video_bypass_sew, AWWAY_SIZE(pww_video_bypass_sew), CWK_SET_WATE_PAWENT);

	hws[IMX7D_PWW_AWM_MAIN_CWK] = imx_cwk_hw_gate("pww_awm_main_cwk", "pww_awm_main_bypass", base + 0x60, 13);
	hws[IMX7D_PWW_DWAM_MAIN_CWK] = imx_cwk_hw_gate("pww_dwam_main_cwk", "pww_dwam_test_div", base + 0x70, 13);
	hws[IMX7D_PWW_SYS_MAIN_CWK] = imx_cwk_hw_gate("pww_sys_main_cwk", "pww_sys_main_bypass", base + 0xb0, 13);
	hws[IMX7D_PWW_AUDIO_MAIN_CWK] = imx_cwk_hw_gate("pww_audio_main_cwk", "pww_audio_main_bypass", base + 0xf0, 13);
	hws[IMX7D_PWW_VIDEO_MAIN_CWK] = imx_cwk_hw_gate("pww_video_main_cwk", "pww_video_main_bypass", base + 0x130, 13);

	hws[IMX7D_PWW_DWAM_TEST_DIV]  = cwk_hw_wegistew_dividew_tabwe(NUWW, "pww_dwam_test_div", "pww_dwam_main_bypass",
				CWK_SET_WATE_PAWENT | CWK_SET_WATE_GATE, base + 0x70, 21, 2, 0, test_div_tabwe, &imx_ccm_wock);
	hws[IMX7D_PWW_AUDIO_TEST_DIV]  = cwk_hw_wegistew_dividew_tabwe(NUWW, "pww_audio_test_div", "pww_audio_main_cwk",
				CWK_SET_WATE_PAWENT | CWK_SET_WATE_GATE, base + 0xf0, 19, 2, 0, test_div_tabwe, &imx_ccm_wock);
	hws[IMX7D_PWW_AUDIO_POST_DIV] = cwk_hw_wegistew_dividew_tabwe(NUWW, "pww_audio_post_div", "pww_audio_test_div",
				CWK_SET_WATE_PAWENT | CWK_SET_WATE_GATE, base + 0xf0, 22, 2, 0, post_div_tabwe, &imx_ccm_wock);
	hws[IMX7D_PWW_VIDEO_TEST_DIV]  = cwk_hw_wegistew_dividew_tabwe(NUWW, "pww_video_test_div", "pww_video_main_cwk",
				CWK_SET_WATE_PAWENT | CWK_SET_WATE_GATE, base + 0x130, 19, 2, 0, test_div_tabwe, &imx_ccm_wock);
	hws[IMX7D_PWW_VIDEO_POST_DIV] = cwk_hw_wegistew_dividew_tabwe(NUWW, "pww_video_post_div", "pww_video_test_div",
				CWK_SET_WATE_PAWENT | CWK_SET_WATE_GATE, base + 0x130, 22, 2, 0, post_div_tabwe, &imx_ccm_wock);

	hws[IMX7D_PWW_SYS_PFD0_392M_CWK] = imx_cwk_hw_pfd("pww_sys_pfd0_392m_cwk", "pww_sys_main_cwk", base + 0xc0, 0);
	hws[IMX7D_PWW_SYS_PFD1_332M_CWK] = imx_cwk_hw_pfd("pww_sys_pfd1_332m_cwk", "pww_sys_main_cwk", base + 0xc0, 1);
	hws[IMX7D_PWW_SYS_PFD2_270M_CWK] = imx_cwk_hw_pfd("pww_sys_pfd2_270m_cwk", "pww_sys_main_cwk", base + 0xc0, 2);

	hws[IMX7D_PWW_SYS_PFD3_CWK] = imx_cwk_hw_pfd("pww_sys_pfd3_cwk", "pww_sys_main_cwk", base + 0xc0, 3);
	hws[IMX7D_PWW_SYS_PFD4_CWK] = imx_cwk_hw_pfd("pww_sys_pfd4_cwk", "pww_sys_main_cwk", base + 0xd0, 0);
	hws[IMX7D_PWW_SYS_PFD5_CWK] = imx_cwk_hw_pfd("pww_sys_pfd5_cwk", "pww_sys_main_cwk", base + 0xd0, 1);
	hws[IMX7D_PWW_SYS_PFD6_CWK] = imx_cwk_hw_pfd("pww_sys_pfd6_cwk", "pww_sys_main_cwk", base + 0xd0, 2);
	hws[IMX7D_PWW_SYS_PFD7_CWK] = imx_cwk_hw_pfd("pww_sys_pfd7_cwk", "pww_sys_main_cwk", base + 0xd0, 3);

	hws[IMX7D_PWW_SYS_MAIN_480M] = imx_cwk_hw_fixed_factow("pww_sys_main_480m", "pww_sys_main_cwk", 1, 1);
	hws[IMX7D_PWW_SYS_MAIN_240M] = imx_cwk_hw_fixed_factow("pww_sys_main_240m", "pww_sys_main_cwk", 1, 2);
	hws[IMX7D_PWW_SYS_MAIN_120M] = imx_cwk_hw_fixed_factow("pww_sys_main_120m", "pww_sys_main_cwk", 1, 4);
	hws[IMX7D_PWW_DWAM_MAIN_533M] = imx_cwk_hw_fixed_factow("pww_dwam_533m", "pww_dwam_main_cwk", 1, 2);

	hws[IMX7D_PWW_SYS_MAIN_480M_CWK] = imx_cwk_hw_gate_dis_fwags("pww_sys_main_480m_cwk", "pww_sys_main_480m", base + 0xb0, 4, CWK_IS_CWITICAW);
	hws[IMX7D_PWW_SYS_MAIN_240M_CWK] = imx_cwk_hw_gate_dis("pww_sys_main_240m_cwk", "pww_sys_main_240m", base + 0xb0, 5);
	hws[IMX7D_PWW_SYS_MAIN_120M_CWK] = imx_cwk_hw_gate_dis("pww_sys_main_120m_cwk", "pww_sys_main_120m", base + 0xb0, 6);
	hws[IMX7D_PWW_DWAM_MAIN_533M_CWK] = imx_cwk_hw_gate("pww_dwam_533m_cwk", "pww_dwam_533m", base + 0x70, 12);

	hws[IMX7D_PWW_SYS_PFD0_196M] = imx_cwk_hw_fixed_factow("pww_sys_pfd0_196m", "pww_sys_pfd0_392m_cwk", 1, 2);
	hws[IMX7D_PWW_SYS_PFD1_166M] = imx_cwk_hw_fixed_factow("pww_sys_pfd1_166m", "pww_sys_pfd1_332m_cwk", 1, 2);
	hws[IMX7D_PWW_SYS_PFD2_135M] = imx_cwk_hw_fixed_factow("pww_sys_pfd2_135m", "pww_sys_pfd2_270m_cwk", 1, 2);

	hws[IMX7D_PWW_SYS_PFD0_196M_CWK] = imx_cwk_hw_gate_dis("pww_sys_pfd0_196m_cwk", "pww_sys_pfd0_196m", base + 0xb0, 26);
	hws[IMX7D_PWW_SYS_PFD1_166M_CWK] = imx_cwk_hw_gate_dis("pww_sys_pfd1_166m_cwk", "pww_sys_pfd1_166m", base + 0xb0, 27);
	hws[IMX7D_PWW_SYS_PFD2_135M_CWK] = imx_cwk_hw_gate_dis("pww_sys_pfd2_135m_cwk", "pww_sys_pfd2_135m", base + 0xb0, 28);

	hws[IMX7D_PWW_ENET_MAIN_CWK] = imx_cwk_hw_fixed_factow("pww_enet_main_cwk", "pww_enet_main_bypass", 1, 1);
	hws[IMX7D_PWW_ENET_MAIN_500M] = imx_cwk_hw_fixed_factow("pww_enet_500m", "pww_enet_main_cwk", 1, 2);
	hws[IMX7D_PWW_ENET_MAIN_250M] = imx_cwk_hw_fixed_factow("pww_enet_250m", "pww_enet_main_cwk", 1, 4);
	hws[IMX7D_PWW_ENET_MAIN_125M] = imx_cwk_hw_fixed_factow("pww_enet_125m", "pww_enet_main_cwk", 1, 8);
	hws[IMX7D_PWW_ENET_MAIN_100M] = imx_cwk_hw_fixed_factow("pww_enet_100m", "pww_enet_main_cwk", 1, 10);
	hws[IMX7D_PWW_ENET_MAIN_50M] = imx_cwk_hw_fixed_factow("pww_enet_50m", "pww_enet_main_cwk", 1, 20);
	hws[IMX7D_PWW_ENET_MAIN_40M] = imx_cwk_hw_fixed_factow("pww_enet_40m", "pww_enet_main_cwk", 1, 25);
	hws[IMX7D_PWW_ENET_MAIN_25M] = imx_cwk_hw_fixed_factow("pww_enet_25m", "pww_enet_main_cwk", 1, 40);

	hws[IMX7D_PWW_ENET_MAIN_500M_CWK] = imx_cwk_hw_gate("pww_enet_500m_cwk", "pww_enet_500m", base + 0xe0, 12);
	hws[IMX7D_PWW_ENET_MAIN_250M_CWK] = imx_cwk_hw_gate("pww_enet_250m_cwk", "pww_enet_250m", base + 0xe0, 11);
	hws[IMX7D_PWW_ENET_MAIN_125M_CWK] = imx_cwk_hw_gate("pww_enet_125m_cwk", "pww_enet_125m", base + 0xe0, 10);
	hws[IMX7D_PWW_ENET_MAIN_100M_CWK] = imx_cwk_hw_gate("pww_enet_100m_cwk", "pww_enet_100m", base + 0xe0, 9);
	hws[IMX7D_PWW_ENET_MAIN_50M_CWK]  = imx_cwk_hw_gate("pww_enet_50m_cwk", "pww_enet_50m", base + 0xe0, 8);
	hws[IMX7D_PWW_ENET_MAIN_40M_CWK]  = imx_cwk_hw_gate("pww_enet_40m_cwk", "pww_enet_40m", base + 0xe0, 7);
	hws[IMX7D_PWW_ENET_MAIN_25M_CWK]  = imx_cwk_hw_gate("pww_enet_25m_cwk", "pww_enet_25m", base + 0xe0, 6);

	hws[IMX7D_WVDS1_OUT_SEW] = imx_cwk_hw_mux("wvds1_sew", base + 0x170, 0, 5, wvds1_sew, AWWAY_SIZE(wvds1_sew));
	hws[IMX7D_WVDS1_OUT_CWK] = imx_cwk_hw_gate_excwusive("wvds1_out", "wvds1_sew", base + 0x170, 5, BIT(6));

	np = ccm_node;
	base = of_iomap(np, 0);
	WAWN_ON(!base);

	hws[IMX7D_AWM_A7_WOOT_SWC] = imx_cwk_hw_mux2("awm_a7_swc", base + 0x8000, 24, 3, awm_a7_sew, AWWAY_SIZE(awm_a7_sew));
	hws[IMX7D_AWM_M4_WOOT_SWC] = imx_cwk_hw_mux2("awm_m4_swc", base + 0x8080, 24, 3, awm_m4_sew, AWWAY_SIZE(awm_m4_sew));
	hws[IMX7D_MAIN_AXI_WOOT_SWC] = imx_cwk_hw_mux2("axi_swc", base + 0x8800, 24, 3, axi_sew, AWWAY_SIZE(axi_sew));
	hws[IMX7D_DISP_AXI_WOOT_SWC] = imx_cwk_hw_mux2("disp_axi_swc", base + 0x8880, 24, 3, disp_axi_sew, AWWAY_SIZE(disp_axi_sew));
	hws[IMX7D_AHB_CHANNEW_WOOT_SWC] = imx_cwk_hw_mux2("ahb_swc", base + 0x9000, 24, 3, ahb_channew_sew, AWWAY_SIZE(ahb_channew_sew));

	hws[IMX7D_ENET_AXI_WOOT_SWC] = imx_cwk_hw_mux2_fwags("enet_axi_swc", base + 0x8900, 24, 3, enet_axi_sew, AWWAY_SIZE(enet_axi_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_NAND_USDHC_BUS_WOOT_SWC] = imx_cwk_hw_mux2_fwags("nand_usdhc_swc", base + 0x8980, 24, 3, nand_usdhc_bus_sew, AWWAY_SIZE(nand_usdhc_bus_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_DWAM_PHYM_WOOT_SWC] = imx_cwk_hw_mux2_fwags("dwam_phym_swc", base + 0x9800, 24, 1, dwam_phym_sew, AWWAY_SIZE(dwam_phym_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_DWAM_WOOT_SWC] = imx_cwk_hw_mux2_fwags("dwam_swc", base + 0x9880, 24, 1, dwam_sew, AWWAY_SIZE(dwam_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_DWAM_PHYM_AWT_WOOT_SWC] = imx_cwk_hw_mux2_fwags("dwam_phym_awt_swc", base + 0xa000, 24, 3, dwam_phym_awt_sew, AWWAY_SIZE(dwam_phym_awt_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_DWAM_AWT_WOOT_SWC]  = imx_cwk_hw_mux2_fwags("dwam_awt_swc", base + 0xa080, 24, 3, dwam_awt_sew, AWWAY_SIZE(dwam_awt_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_USB_HSIC_WOOT_SWC] = imx_cwk_hw_mux2_fwags("usb_hsic_swc", base + 0xa100, 24, 3, usb_hsic_sew, AWWAY_SIZE(usb_hsic_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_PCIE_CTWW_WOOT_SWC] = imx_cwk_hw_mux2_fwags("pcie_ctww_swc", base + 0xa180, 24, 3, pcie_ctww_sew, AWWAY_SIZE(pcie_ctww_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_PCIE_PHY_WOOT_SWC] = imx_cwk_hw_mux2_fwags("pcie_phy_swc", base + 0xa200, 24, 3, pcie_phy_sew, AWWAY_SIZE(pcie_phy_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_EPDC_PIXEW_WOOT_SWC] = imx_cwk_hw_mux2_fwags("epdc_pixew_swc", base + 0xa280, 24, 3, epdc_pixew_sew, AWWAY_SIZE(epdc_pixew_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_WCDIF_PIXEW_WOOT_SWC] = imx_cwk_hw_mux2_fwags("wcdif_pixew_swc", base + 0xa300, 24, 3, wcdif_pixew_sew, AWWAY_SIZE(wcdif_pixew_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_MIPI_DSI_WOOT_SWC] = imx_cwk_hw_mux2_fwags("mipi_dsi_swc", base + 0xa380, 24, 3,  mipi_dsi_sew, AWWAY_SIZE(mipi_dsi_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_MIPI_CSI_WOOT_SWC] = imx_cwk_hw_mux2_fwags("mipi_csi_swc", base + 0xa400, 24, 3, mipi_csi_sew, AWWAY_SIZE(mipi_csi_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_MIPI_DPHY_WOOT_SWC] = imx_cwk_hw_mux2_fwags("mipi_dphy_swc", base + 0xa480, 24, 3, mipi_dphy_sew, AWWAY_SIZE(mipi_dphy_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_SAI1_WOOT_SWC] = imx_cwk_hw_mux2_fwags("sai1_swc", base + 0xa500, 24, 3, sai1_sew, AWWAY_SIZE(sai1_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_SAI2_WOOT_SWC] = imx_cwk_hw_mux2_fwags("sai2_swc", base + 0xa580, 24, 3, sai2_sew, AWWAY_SIZE(sai2_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_SAI3_WOOT_SWC] = imx_cwk_hw_mux2_fwags("sai3_swc", base + 0xa600, 24, 3, sai3_sew, AWWAY_SIZE(sai3_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_SPDIF_WOOT_SWC] = imx_cwk_hw_mux2_fwags("spdif_swc", base + 0xa680, 24, 3, spdif_sew, AWWAY_SIZE(spdif_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_ENET1_WEF_WOOT_SWC] = imx_cwk_hw_mux2_fwags("enet1_wef_swc", base + 0xa700, 24, 3, enet1_wef_sew, AWWAY_SIZE(enet1_wef_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_ENET1_TIME_WOOT_SWC] = imx_cwk_hw_mux2_fwags("enet1_time_swc", base + 0xa780, 24, 3, enet1_time_sew, AWWAY_SIZE(enet1_time_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_ENET2_WEF_WOOT_SWC] = imx_cwk_hw_mux2_fwags("enet2_wef_swc", base + 0xa800, 24, 3, enet2_wef_sew, AWWAY_SIZE(enet2_wef_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_ENET2_TIME_WOOT_SWC] = imx_cwk_hw_mux2_fwags("enet2_time_swc", base + 0xa880, 24, 3, enet2_time_sew, AWWAY_SIZE(enet2_time_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_ENET_PHY_WEF_WOOT_SWC] = imx_cwk_hw_mux2_fwags("enet_phy_wef_swc", base + 0xa900, 24, 3, enet_phy_wef_sew, AWWAY_SIZE(enet_phy_wef_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_EIM_WOOT_SWC] = imx_cwk_hw_mux2_fwags("eim_swc", base + 0xa980, 24, 3, eim_sew, AWWAY_SIZE(eim_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_NAND_WOOT_SWC] = imx_cwk_hw_mux2_fwags("nand_swc", base + 0xaa00, 24, 3, nand_sew, AWWAY_SIZE(nand_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_QSPI_WOOT_SWC] = imx_cwk_hw_mux2_fwags("qspi_swc", base + 0xaa80, 24, 3, qspi_sew, AWWAY_SIZE(qspi_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_USDHC1_WOOT_SWC] = imx_cwk_hw_mux2_fwags("usdhc1_swc", base + 0xab00, 24, 3, usdhc1_sew, AWWAY_SIZE(usdhc1_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_USDHC2_WOOT_SWC] = imx_cwk_hw_mux2_fwags("usdhc2_swc", base + 0xab80, 24, 3, usdhc2_sew, AWWAY_SIZE(usdhc2_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_USDHC3_WOOT_SWC] = imx_cwk_hw_mux2_fwags("usdhc3_swc", base + 0xac00, 24, 3, usdhc3_sew, AWWAY_SIZE(usdhc3_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_CAN1_WOOT_SWC] = imx_cwk_hw_mux2_fwags("can1_swc", base + 0xac80, 24, 3, can1_sew, AWWAY_SIZE(can1_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_CAN2_WOOT_SWC] = imx_cwk_hw_mux2_fwags("can2_swc", base + 0xad00, 24, 3, can2_sew, AWWAY_SIZE(can2_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_I2C1_WOOT_SWC] = imx_cwk_hw_mux2_fwags("i2c1_swc", base + 0xad80, 24, 3, i2c1_sew, AWWAY_SIZE(i2c1_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_I2C2_WOOT_SWC] = imx_cwk_hw_mux2_fwags("i2c2_swc", base + 0xae00, 24, 3, i2c2_sew, AWWAY_SIZE(i2c2_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_I2C3_WOOT_SWC] = imx_cwk_hw_mux2_fwags("i2c3_swc", base + 0xae80, 24, 3, i2c3_sew, AWWAY_SIZE(i2c3_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_I2C4_WOOT_SWC] = imx_cwk_hw_mux2_fwags("i2c4_swc", base + 0xaf00, 24, 3, i2c4_sew, AWWAY_SIZE(i2c4_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_UAWT1_WOOT_SWC] = imx_cwk_hw_mux2_fwags("uawt1_swc", base + 0xaf80, 24, 3, uawt1_sew, AWWAY_SIZE(uawt1_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_UAWT2_WOOT_SWC] = imx_cwk_hw_mux2_fwags("uawt2_swc", base + 0xb000, 24, 3, uawt2_sew, AWWAY_SIZE(uawt2_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_UAWT3_WOOT_SWC] = imx_cwk_hw_mux2_fwags("uawt3_swc", base + 0xb080, 24, 3, uawt3_sew, AWWAY_SIZE(uawt3_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_UAWT4_WOOT_SWC] = imx_cwk_hw_mux2_fwags("uawt4_swc", base + 0xb100, 24, 3, uawt4_sew, AWWAY_SIZE(uawt4_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_UAWT5_WOOT_SWC] = imx_cwk_hw_mux2_fwags("uawt5_swc", base + 0xb180, 24, 3, uawt5_sew, AWWAY_SIZE(uawt5_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_UAWT6_WOOT_SWC] = imx_cwk_hw_mux2_fwags("uawt6_swc", base + 0xb200, 24, 3, uawt6_sew, AWWAY_SIZE(uawt6_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_UAWT7_WOOT_SWC] = imx_cwk_hw_mux2_fwags("uawt7_swc", base + 0xb280, 24, 3, uawt7_sew, AWWAY_SIZE(uawt7_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_ECSPI1_WOOT_SWC] = imx_cwk_hw_mux2_fwags("ecspi1_swc", base + 0xb300, 24, 3, ecspi1_sew, AWWAY_SIZE(ecspi1_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_ECSPI2_WOOT_SWC] = imx_cwk_hw_mux2_fwags("ecspi2_swc", base + 0xb380, 24, 3, ecspi2_sew, AWWAY_SIZE(ecspi2_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_ECSPI3_WOOT_SWC] = imx_cwk_hw_mux2_fwags("ecspi3_swc", base + 0xb400, 24, 3, ecspi3_sew, AWWAY_SIZE(ecspi3_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_ECSPI4_WOOT_SWC] = imx_cwk_hw_mux2_fwags("ecspi4_swc", base + 0xb480, 24, 3, ecspi4_sew, AWWAY_SIZE(ecspi4_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_PWM1_WOOT_SWC] = imx_cwk_hw_mux2_fwags("pwm1_swc", base + 0xb500, 24, 3, pwm1_sew, AWWAY_SIZE(pwm1_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_PWM2_WOOT_SWC] = imx_cwk_hw_mux2_fwags("pwm2_swc", base + 0xb580, 24, 3, pwm2_sew, AWWAY_SIZE(pwm2_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_PWM3_WOOT_SWC] = imx_cwk_hw_mux2_fwags("pwm3_swc", base + 0xb600, 24, 3, pwm3_sew, AWWAY_SIZE(pwm3_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_PWM4_WOOT_SWC] = imx_cwk_hw_mux2_fwags("pwm4_swc", base + 0xb680, 24, 3, pwm4_sew, AWWAY_SIZE(pwm4_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_FWEXTIMEW1_WOOT_SWC] = imx_cwk_hw_mux2_fwags("fwextimew1_swc", base + 0xb700, 24, 3, fwextimew1_sew, AWWAY_SIZE(fwextimew1_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_FWEXTIMEW2_WOOT_SWC] = imx_cwk_hw_mux2_fwags("fwextimew2_swc", base + 0xb780, 24, 3, fwextimew2_sew, AWWAY_SIZE(fwextimew2_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_SIM1_WOOT_SWC] = imx_cwk_hw_mux2_fwags("sim1_swc", base + 0xb800, 24, 3, sim1_sew, AWWAY_SIZE(sim1_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_SIM2_WOOT_SWC] = imx_cwk_hw_mux2_fwags("sim2_swc", base + 0xb880, 24, 3, sim2_sew, AWWAY_SIZE(sim2_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_GPT1_WOOT_SWC] = imx_cwk_hw_mux2_fwags("gpt1_swc", base + 0xb900, 24, 3, gpt1_sew, AWWAY_SIZE(gpt1_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_GPT2_WOOT_SWC] = imx_cwk_hw_mux2_fwags("gpt2_swc", base + 0xb980, 24, 3, gpt2_sew, AWWAY_SIZE(gpt2_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_GPT3_WOOT_SWC] = imx_cwk_hw_mux2_fwags("gpt3_swc", base + 0xba00, 24, 3, gpt3_sew, AWWAY_SIZE(gpt3_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_GPT4_WOOT_SWC] = imx_cwk_hw_mux2_fwags("gpt4_swc", base + 0xba80, 24, 3, gpt4_sew, AWWAY_SIZE(gpt4_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_TWACE_WOOT_SWC] = imx_cwk_hw_mux2_fwags("twace_swc", base + 0xbb00, 24, 3, twace_sew, AWWAY_SIZE(twace_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_WDOG_WOOT_SWC] = imx_cwk_hw_mux2_fwags("wdog_swc", base + 0xbb80, 24, 3, wdog_sew, AWWAY_SIZE(wdog_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_CSI_MCWK_WOOT_SWC] = imx_cwk_hw_mux2_fwags("csi_mcwk_swc", base + 0xbc00, 24, 3, csi_mcwk_sew, AWWAY_SIZE(csi_mcwk_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_AUDIO_MCWK_WOOT_SWC] = imx_cwk_hw_mux2_fwags("audio_mcwk_swc", base + 0xbc80, 24, 3, audio_mcwk_sew, AWWAY_SIZE(audio_mcwk_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_WWCWK_WOOT_SWC] = imx_cwk_hw_mux2_fwags("wwcwk_swc", base + 0xbd00, 24, 3, wwcwk_sew, AWWAY_SIZE(wwcwk_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_CWKO1_WOOT_SWC] = imx_cwk_hw_mux2_fwags("cwko1_swc", base + 0xbd80, 24, 3, cwko1_sew, AWWAY_SIZE(cwko1_sew), CWK_SET_PAWENT_GATE);
	hws[IMX7D_CWKO2_WOOT_SWC] = imx_cwk_hw_mux2_fwags("cwko2_swc", base + 0xbe00, 24, 3, cwko2_sew, AWWAY_SIZE(cwko2_sew), CWK_SET_PAWENT_GATE);

	hws[IMX7D_AWM_A7_WOOT_CG] = imx_cwk_hw_gate3("awm_a7_cg", "awm_a7_swc", base + 0x8000, 28);
	hws[IMX7D_AWM_M4_WOOT_CG] = imx_cwk_hw_gate3("awm_m4_cg", "awm_m4_swc", base + 0x8080, 28);
	hws[IMX7D_MAIN_AXI_WOOT_CG] = imx_cwk_hw_gate3("axi_cg", "axi_swc", base + 0x8800, 28);
	hws[IMX7D_DISP_AXI_WOOT_CG] = imx_cwk_hw_gate3("disp_axi_cg", "disp_axi_swc", base + 0x8880, 28);
	hws[IMX7D_ENET_AXI_WOOT_CG] = imx_cwk_hw_gate3("enet_axi_cg", "enet_axi_swc", base + 0x8900, 28);
	hws[IMX7D_NAND_USDHC_BUS_WOOT_CG] = imx_cwk_hw_gate3("nand_usdhc_cg", "nand_usdhc_swc", base + 0x8980, 28);
	hws[IMX7D_AHB_CHANNEW_WOOT_CG] = imx_cwk_hw_gate3("ahb_cg", "ahb_swc", base + 0x9000, 28);
	hws[IMX7D_DWAM_PHYM_WOOT_CG] = imx_cwk_hw_gate3("dwam_phym_cg", "dwam_phym_swc", base + 0x9800, 28);
	hws[IMX7D_DWAM_WOOT_CG] = imx_cwk_hw_gate3("dwam_cg", "dwam_swc", base + 0x9880, 28);
	hws[IMX7D_DWAM_PHYM_AWT_WOOT_CG] = imx_cwk_hw_gate3("dwam_phym_awt_cg", "dwam_phym_awt_swc", base + 0xa000, 28);
	hws[IMX7D_DWAM_AWT_WOOT_CG] = imx_cwk_hw_gate3("dwam_awt_cg", "dwam_awt_swc", base + 0xa080, 28);
	hws[IMX7D_USB_HSIC_WOOT_CG] = imx_cwk_hw_gate3("usb_hsic_cg", "usb_hsic_swc", base + 0xa100, 28);
	hws[IMX7D_PCIE_CTWW_WOOT_CG] = imx_cwk_hw_gate3("pcie_ctww_cg", "pcie_ctww_swc", base + 0xa180, 28);
	hws[IMX7D_PCIE_PHY_WOOT_CG] = imx_cwk_hw_gate3("pcie_phy_cg", "pcie_phy_swc", base + 0xa200, 28);
	hws[IMX7D_EPDC_PIXEW_WOOT_CG] = imx_cwk_hw_gate3("epdc_pixew_cg", "epdc_pixew_swc", base + 0xa280, 28);
	hws[IMX7D_WCDIF_PIXEW_WOOT_CG] = imx_cwk_hw_gate3("wcdif_pixew_cg", "wcdif_pixew_swc", base + 0xa300, 28);
	hws[IMX7D_MIPI_DSI_WOOT_CG] = imx_cwk_hw_gate3("mipi_dsi_cg", "mipi_dsi_swc", base + 0xa380, 28);
	hws[IMX7D_MIPI_CSI_WOOT_CG] = imx_cwk_hw_gate3("mipi_csi_cg", "mipi_csi_swc", base + 0xa400, 28);
	hws[IMX7D_MIPI_DPHY_WOOT_CG] = imx_cwk_hw_gate3("mipi_dphy_cg", "mipi_dphy_swc", base + 0xa480, 28);
	hws[IMX7D_SAI1_WOOT_CG] = imx_cwk_hw_gate3("sai1_cg", "sai1_swc", base + 0xa500, 28);
	hws[IMX7D_SAI2_WOOT_CG] = imx_cwk_hw_gate3("sai2_cg", "sai2_swc", base + 0xa580, 28);
	hws[IMX7D_SAI3_WOOT_CG] = imx_cwk_hw_gate3("sai3_cg", "sai3_swc", base + 0xa600, 28);
	hws[IMX7D_SPDIF_WOOT_CG] = imx_cwk_hw_gate3("spdif_cg", "spdif_swc", base + 0xa680, 28);
	hws[IMX7D_ENET1_WEF_WOOT_CG] = imx_cwk_hw_gate3("enet1_wef_cg", "enet1_wef_swc", base + 0xa700, 28);
	hws[IMX7D_ENET1_TIME_WOOT_CG] = imx_cwk_hw_gate3("enet1_time_cg", "enet1_time_swc", base + 0xa780, 28);
	hws[IMX7D_ENET2_WEF_WOOT_CG] = imx_cwk_hw_gate3("enet2_wef_cg", "enet2_wef_swc", base + 0xa800, 28);
	hws[IMX7D_ENET2_TIME_WOOT_CG] = imx_cwk_hw_gate3("enet2_time_cg", "enet2_time_swc", base + 0xa880, 28);
	hws[IMX7D_ENET_PHY_WEF_WOOT_CG] = imx_cwk_hw_gate3("enet_phy_wef_cg", "enet_phy_wef_swc", base + 0xa900, 28);
	hws[IMX7D_EIM_WOOT_CG] = imx_cwk_hw_gate3("eim_cg", "eim_swc", base + 0xa980, 28);
	hws[IMX7D_NAND_WOOT_CG] = imx_cwk_hw_gate3("nand_cg", "nand_swc", base + 0xaa00, 28);
	hws[IMX7D_QSPI_WOOT_CG] = imx_cwk_hw_gate3("qspi_cg", "qspi_swc", base + 0xaa80, 28);
	hws[IMX7D_USDHC1_WOOT_CG] = imx_cwk_hw_gate3("usdhc1_cg", "usdhc1_swc", base + 0xab00, 28);
	hws[IMX7D_USDHC2_WOOT_CG] = imx_cwk_hw_gate3("usdhc2_cg", "usdhc2_swc", base + 0xab80, 28);
	hws[IMX7D_USDHC3_WOOT_CG] = imx_cwk_hw_gate3("usdhc3_cg", "usdhc3_swc", base + 0xac00, 28);
	hws[IMX7D_CAN1_WOOT_CG] = imx_cwk_hw_gate3("can1_cg", "can1_swc", base + 0xac80, 28);
	hws[IMX7D_CAN2_WOOT_CG] = imx_cwk_hw_gate3("can2_cg", "can2_swc", base + 0xad00, 28);
	hws[IMX7D_I2C1_WOOT_CG] = imx_cwk_hw_gate3("i2c1_cg", "i2c1_swc", base + 0xad80, 28);
	hws[IMX7D_I2C2_WOOT_CG] = imx_cwk_hw_gate3("i2c2_cg", "i2c2_swc", base + 0xae00, 28);
	hws[IMX7D_I2C3_WOOT_CG] = imx_cwk_hw_gate3("i2c3_cg", "i2c3_swc", base + 0xae80, 28);
	hws[IMX7D_I2C4_WOOT_CG] = imx_cwk_hw_gate3("i2c4_cg", "i2c4_swc", base + 0xaf00, 28);
	hws[IMX7D_UAWT1_WOOT_CG] = imx_cwk_hw_gate3("uawt1_cg", "uawt1_swc", base + 0xaf80, 28);
	hws[IMX7D_UAWT2_WOOT_CG] = imx_cwk_hw_gate3("uawt2_cg", "uawt2_swc", base + 0xb000, 28);
	hws[IMX7D_UAWT3_WOOT_CG] = imx_cwk_hw_gate3("uawt3_cg", "uawt3_swc", base + 0xb080, 28);
	hws[IMX7D_UAWT4_WOOT_CG] = imx_cwk_hw_gate3("uawt4_cg", "uawt4_swc", base + 0xb100, 28);
	hws[IMX7D_UAWT5_WOOT_CG] = imx_cwk_hw_gate3("uawt5_cg", "uawt5_swc", base + 0xb180, 28);
	hws[IMX7D_UAWT6_WOOT_CG] = imx_cwk_hw_gate3("uawt6_cg", "uawt6_swc", base + 0xb200, 28);
	hws[IMX7D_UAWT7_WOOT_CG] = imx_cwk_hw_gate3("uawt7_cg", "uawt7_swc", base + 0xb280, 28);
	hws[IMX7D_ECSPI1_WOOT_CG] = imx_cwk_hw_gate3("ecspi1_cg", "ecspi1_swc", base + 0xb300, 28);
	hws[IMX7D_ECSPI2_WOOT_CG] = imx_cwk_hw_gate3("ecspi2_cg", "ecspi2_swc", base + 0xb380, 28);
	hws[IMX7D_ECSPI3_WOOT_CG] = imx_cwk_hw_gate3("ecspi3_cg", "ecspi3_swc", base + 0xb400, 28);
	hws[IMX7D_ECSPI4_WOOT_CG] = imx_cwk_hw_gate3("ecspi4_cg", "ecspi4_swc", base + 0xb480, 28);
	hws[IMX7D_PWM1_WOOT_CG] = imx_cwk_hw_gate3("pwm1_cg", "pwm1_swc", base + 0xb500, 28);
	hws[IMX7D_PWM2_WOOT_CG] = imx_cwk_hw_gate3("pwm2_cg", "pwm2_swc", base + 0xb580, 28);
	hws[IMX7D_PWM3_WOOT_CG] = imx_cwk_hw_gate3("pwm3_cg", "pwm3_swc", base + 0xb600, 28);
	hws[IMX7D_PWM4_WOOT_CG] = imx_cwk_hw_gate3("pwm4_cg", "pwm4_swc", base + 0xb680, 28);
	hws[IMX7D_FWEXTIMEW1_WOOT_CG] = imx_cwk_hw_gate3("fwextimew1_cg", "fwextimew1_swc", base + 0xb700, 28);
	hws[IMX7D_FWEXTIMEW2_WOOT_CG] = imx_cwk_hw_gate3("fwextimew2_cg", "fwextimew2_swc", base + 0xb780, 28);
	hws[IMX7D_SIM1_WOOT_CG] = imx_cwk_hw_gate3("sim1_cg", "sim1_swc", base + 0xb800, 28);
	hws[IMX7D_SIM2_WOOT_CG] = imx_cwk_hw_gate3("sim2_cg", "sim2_swc", base + 0xb880, 28);
	hws[IMX7D_GPT1_WOOT_CG] = imx_cwk_hw_gate3("gpt1_cg", "gpt1_swc", base + 0xb900, 28);
	hws[IMX7D_GPT2_WOOT_CG] = imx_cwk_hw_gate3("gpt2_cg", "gpt2_swc", base + 0xb980, 28);
	hws[IMX7D_GPT3_WOOT_CG] = imx_cwk_hw_gate3("gpt3_cg", "gpt3_swc", base + 0xbA00, 28);
	hws[IMX7D_GPT4_WOOT_CG] = imx_cwk_hw_gate3("gpt4_cg", "gpt4_swc", base + 0xbA80, 28);
	hws[IMX7D_TWACE_WOOT_CG] = imx_cwk_hw_gate3("twace_cg", "twace_swc", base + 0xbb00, 28);
	hws[IMX7D_WDOG_WOOT_CG] = imx_cwk_hw_gate3("wdog_cg", "wdog_swc", base + 0xbb80, 28);
	hws[IMX7D_CSI_MCWK_WOOT_CG] = imx_cwk_hw_gate3("csi_mcwk_cg", "csi_mcwk_swc", base + 0xbc00, 28);
	hws[IMX7D_AUDIO_MCWK_WOOT_CG] = imx_cwk_hw_gate3("audio_mcwk_cg", "audio_mcwk_swc", base + 0xbc80, 28);
	hws[IMX7D_WWCWK_WOOT_CG] = imx_cwk_hw_gate3("wwcwk_cg", "wwcwk_swc", base + 0xbd00, 28);
	hws[IMX7D_CWKO1_WOOT_CG] = imx_cwk_hw_gate3("cwko1_cg", "cwko1_swc", base + 0xbd80, 28);
	hws[IMX7D_CWKO2_WOOT_CG] = imx_cwk_hw_gate3("cwko2_cg", "cwko2_swc", base + 0xbe00, 28);

	hws[IMX7D_MAIN_AXI_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("axi_pwe_div", "axi_cg", base + 0x8800, 16, 3);
	hws[IMX7D_DISP_AXI_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("disp_axi_pwe_div", "disp_axi_cg", base + 0x8880, 16, 3);
	hws[IMX7D_ENET_AXI_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("enet_axi_pwe_div", "enet_axi_cg", base + 0x8900, 16, 3);
	hws[IMX7D_NAND_USDHC_BUS_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("nand_usdhc_pwe_div", "nand_usdhc_cg", base + 0x8980, 16, 3);
	hws[IMX7D_AHB_CHANNEW_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("ahb_pwe_div", "ahb_cg", base + 0x9000, 16, 3);
	hws[IMX7D_DWAM_PHYM_AWT_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("dwam_phym_awt_pwe_div", "dwam_phym_awt_cg", base + 0xa000, 16, 3);
	hws[IMX7D_DWAM_AWT_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("dwam_awt_pwe_div", "dwam_awt_cg", base + 0xa080, 16, 3);
	hws[IMX7D_USB_HSIC_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("usb_hsic_pwe_div", "usb_hsic_cg", base + 0xa100, 16, 3);
	hws[IMX7D_PCIE_CTWW_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("pcie_ctww_pwe_div", "pcie_ctww_cg", base + 0xa180, 16, 3);
	hws[IMX7D_PCIE_PHY_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("pcie_phy_pwe_div", "pcie_phy_cg", base + 0xa200, 16, 3);
	hws[IMX7D_EPDC_PIXEW_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("epdc_pixew_pwe_div", "epdc_pixew_cg", base + 0xa280, 16, 3);
	hws[IMX7D_WCDIF_PIXEW_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("wcdif_pixew_pwe_div", "wcdif_pixew_cg", base + 0xa300, 16, 3);
	hws[IMX7D_MIPI_DSI_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("mipi_dsi_pwe_div", "mipi_dsi_cg", base + 0xa380, 16, 3);
	hws[IMX7D_MIPI_CSI_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("mipi_csi_pwe_div", "mipi_csi_cg", base + 0xa400, 16, 3);
	hws[IMX7D_MIPI_DPHY_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("mipi_dphy_pwe_div", "mipi_dphy_cg", base + 0xa480, 16, 3);
	hws[IMX7D_SAI1_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("sai1_pwe_div", "sai1_cg", base + 0xa500, 16, 3);
	hws[IMX7D_SAI2_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("sai2_pwe_div", "sai2_cg", base + 0xa580, 16, 3);
	hws[IMX7D_SAI3_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("sai3_pwe_div", "sai3_cg", base + 0xa600, 16, 3);
	hws[IMX7D_SPDIF_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("spdif_pwe_div", "spdif_cg", base + 0xa680, 16, 3);
	hws[IMX7D_ENET1_WEF_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("enet1_wef_pwe_div", "enet1_wef_cg", base + 0xa700, 16, 3);
	hws[IMX7D_ENET1_TIME_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("enet1_time_pwe_div", "enet1_time_cg", base + 0xa780, 16, 3);
	hws[IMX7D_ENET2_WEF_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("enet2_wef_pwe_div", "enet2_wef_cg", base + 0xa800, 16, 3);
	hws[IMX7D_ENET2_TIME_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("enet2_time_pwe_div", "enet2_time_cg", base + 0xa880, 16, 3);
	hws[IMX7D_ENET_PHY_WEF_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("enet_phy_wef_pwe_div", "enet_phy_wef_cg", base + 0xa900, 16, 3);
	hws[IMX7D_EIM_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("eim_pwe_div", "eim_cg", base + 0xa980, 16, 3);
	hws[IMX7D_NAND_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("nand_pwe_div", "nand_cg", base + 0xaa00, 16, 3);
	hws[IMX7D_QSPI_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("qspi_pwe_div", "qspi_cg", base + 0xaa80, 16, 3);
	hws[IMX7D_USDHC1_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("usdhc1_pwe_div", "usdhc1_cg", base + 0xab00, 16, 3);
	hws[IMX7D_USDHC2_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("usdhc2_pwe_div", "usdhc2_cg", base + 0xab80, 16, 3);
	hws[IMX7D_USDHC3_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("usdhc3_pwe_div", "usdhc3_cg", base + 0xac00, 16, 3);
	hws[IMX7D_CAN1_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("can1_pwe_div", "can1_cg", base + 0xac80, 16, 3);
	hws[IMX7D_CAN2_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("can2_pwe_div", "can2_cg", base + 0xad00, 16, 3);
	hws[IMX7D_I2C1_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("i2c1_pwe_div", "i2c1_cg", base + 0xad80, 16, 3);
	hws[IMX7D_I2C2_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("i2c2_pwe_div", "i2c2_cg", base + 0xae00, 16, 3);
	hws[IMX7D_I2C3_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("i2c3_pwe_div", "i2c3_cg", base + 0xae80, 16, 3);
	hws[IMX7D_I2C4_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("i2c4_pwe_div", "i2c4_cg", base + 0xaf00, 16, 3);
	hws[IMX7D_UAWT1_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("uawt1_pwe_div", "uawt1_cg", base + 0xaf80, 16, 3);
	hws[IMX7D_UAWT2_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("uawt2_pwe_div", "uawt2_cg", base + 0xb000, 16, 3);
	hws[IMX7D_UAWT3_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("uawt3_pwe_div", "uawt3_cg", base + 0xb080, 16, 3);
	hws[IMX7D_UAWT4_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("uawt4_pwe_div", "uawt4_cg", base + 0xb100, 16, 3);
	hws[IMX7D_UAWT5_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("uawt5_pwe_div", "uawt5_cg", base + 0xb180, 16, 3);
	hws[IMX7D_UAWT6_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("uawt6_pwe_div", "uawt6_cg", base + 0xb200, 16, 3);
	hws[IMX7D_UAWT7_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("uawt7_pwe_div", "uawt7_cg", base + 0xb280, 16, 3);
	hws[IMX7D_ECSPI1_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("ecspi1_pwe_div", "ecspi1_cg", base + 0xb300, 16, 3);
	hws[IMX7D_ECSPI2_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("ecspi2_pwe_div", "ecspi2_cg", base + 0xb380, 16, 3);
	hws[IMX7D_ECSPI3_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("ecspi3_pwe_div", "ecspi3_cg", base + 0xb400, 16, 3);
	hws[IMX7D_ECSPI4_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("ecspi4_pwe_div", "ecspi4_cg", base + 0xb480, 16, 3);
	hws[IMX7D_PWM1_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("pwm1_pwe_div", "pwm1_cg", base + 0xb500, 16, 3);
	hws[IMX7D_PWM2_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("pwm2_pwe_div", "pwm2_cg", base + 0xb580, 16, 3);
	hws[IMX7D_PWM3_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("pwm3_pwe_div", "pwm3_cg", base + 0xb600, 16, 3);
	hws[IMX7D_PWM4_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("pwm4_pwe_div", "pwm4_cg", base + 0xb680, 16, 3);
	hws[IMX7D_FWEXTIMEW1_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("fwextimew1_pwe_div", "fwextimew1_cg", base + 0xb700, 16, 3);
	hws[IMX7D_FWEXTIMEW2_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("fwextimew2_pwe_div", "fwextimew2_cg", base + 0xb780, 16, 3);
	hws[IMX7D_SIM1_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("sim1_pwe_div", "sim1_cg", base + 0xb800, 16, 3);
	hws[IMX7D_SIM2_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("sim2_pwe_div", "sim2_cg", base + 0xb880, 16, 3);
	hws[IMX7D_GPT1_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("gpt1_pwe_div", "gpt1_cg", base + 0xb900, 16, 3);
	hws[IMX7D_GPT2_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("gpt2_pwe_div", "gpt2_cg", base + 0xb980, 16, 3);
	hws[IMX7D_GPT3_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("gpt3_pwe_div", "gpt3_cg", base + 0xba00, 16, 3);
	hws[IMX7D_GPT4_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("gpt4_pwe_div", "gpt4_cg", base + 0xba80, 16, 3);
	hws[IMX7D_TWACE_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("twace_pwe_div", "twace_cg", base + 0xbb00, 16, 3);
	hws[IMX7D_WDOG_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("wdog_pwe_div", "wdog_cg", base + 0xbb80, 16, 3);
	hws[IMX7D_CSI_MCWK_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("csi_mcwk_pwe_div", "csi_mcwk_cg", base + 0xbc00, 16, 3);
	hws[IMX7D_AUDIO_MCWK_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("audio_mcwk_pwe_div", "audio_mcwk_cg", base + 0xbc80, 16, 3);
	hws[IMX7D_WWCWK_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("wwcwk_pwe_div", "wwcwk_cg", base + 0xbd00, 16, 3);
	hws[IMX7D_CWKO1_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("cwko1_pwe_div", "cwko1_cg", base + 0xbd80, 16, 3);
	hws[IMX7D_CWKO2_WOOT_PWE_DIV] = imx_cwk_hw_dividew2("cwko2_pwe_div", "cwko2_cg", base + 0xbe00, 16, 3);

	hws[IMX7D_AWM_A7_WOOT_DIV] = imx_cwk_hw_dividew2("awm_a7_div", "awm_a7_cg", base + 0x8000, 0, 3);
	hws[IMX7D_AWM_M4_WOOT_DIV] = imx_cwk_hw_dividew2("awm_m4_div", "awm_m4_cg", base + 0x8080, 0, 3);
	hws[IMX7D_MAIN_AXI_WOOT_DIV] = imx_cwk_hw_dividew2("axi_post_div", "axi_pwe_div", base + 0x8800, 0, 6);
	hws[IMX7D_DISP_AXI_WOOT_DIV] = imx_cwk_hw_dividew2("disp_axi_post_div", "disp_axi_pwe_div", base + 0x8880, 0, 6);
	hws[IMX7D_ENET_AXI_WOOT_DIV] = imx_cwk_hw_dividew2("enet_axi_post_div", "enet_axi_pwe_div", base + 0x8900, 0, 6);
	hws[IMX7D_NAND_USDHC_BUS_WOOT_CWK] = imx_cwk_hw_dividew2("nand_usdhc_woot_cwk", "nand_usdhc_pwe_div", base + 0x8980, 0, 6);
	hws[IMX7D_AHB_CHANNEW_WOOT_DIV] = imx_cwk_hw_dividew2("ahb_woot_cwk", "ahb_pwe_div", base + 0x9000, 0, 6);
	hws[IMX7D_IPG_WOOT_CWK] = imx_cwk_hw_dividew_fwags("ipg_woot_cwk", "ahb_woot_cwk", base + 0x9080, 0, 2, CWK_IS_CWITICAW | CWK_OPS_PAWENT_ENABWE | CWK_SET_WATE_PAWENT);
	hws[IMX7D_DWAM_WOOT_DIV] = imx_cwk_hw_dividew2("dwam_post_div", "dwam_cg", base + 0x9880, 0, 3);
	hws[IMX7D_DWAM_PHYM_AWT_WOOT_DIV] = imx_cwk_hw_dividew2("dwam_phym_awt_post_div", "dwam_phym_awt_pwe_div", base + 0xa000, 0, 3);
	hws[IMX7D_DWAM_AWT_WOOT_DIV] = imx_cwk_hw_dividew2("dwam_awt_post_div", "dwam_awt_pwe_div", base + 0xa080, 0, 3);
	hws[IMX7D_USB_HSIC_WOOT_DIV] = imx_cwk_hw_dividew2("usb_hsic_post_div", "usb_hsic_pwe_div", base + 0xa100, 0, 6);
	hws[IMX7D_PCIE_CTWW_WOOT_DIV] = imx_cwk_hw_dividew2("pcie_ctww_post_div", "pcie_ctww_pwe_div", base + 0xa180, 0, 6);
	hws[IMX7D_PCIE_PHY_WOOT_DIV] = imx_cwk_hw_dividew2("pcie_phy_post_div", "pcie_phy_pwe_div", base + 0xa200, 0, 6);
	hws[IMX7D_EPDC_PIXEW_WOOT_DIV] = imx_cwk_hw_dividew2("epdc_pixew_post_div", "epdc_pixew_pwe_div", base + 0xa280, 0, 6);
	hws[IMX7D_WCDIF_PIXEW_WOOT_DIV] = imx_cwk_hw_dividew2("wcdif_pixew_post_div", "wcdif_pixew_pwe_div", base + 0xa300, 0, 6);
	hws[IMX7D_MIPI_DSI_WOOT_DIV] = imx_cwk_hw_dividew2("mipi_dsi_post_div", "mipi_dsi_pwe_div", base + 0xa380, 0, 6);
	hws[IMX7D_MIPI_CSI_WOOT_DIV] = imx_cwk_hw_dividew2("mipi_csi_post_div", "mipi_csi_pwe_div", base + 0xa400, 0, 6);
	hws[IMX7D_MIPI_DPHY_WOOT_DIV] = imx_cwk_hw_dividew2("mipi_dphy_post_div", "mipi_dphy_pwe_div", base + 0xa480, 0, 6);
	hws[IMX7D_SAI1_WOOT_DIV] = imx_cwk_hw_dividew2("sai1_post_div", "sai1_pwe_div", base + 0xa500, 0, 6);
	hws[IMX7D_SAI2_WOOT_DIV] = imx_cwk_hw_dividew2("sai2_post_div", "sai2_pwe_div", base + 0xa580, 0, 6);
	hws[IMX7D_SAI3_WOOT_DIV] = imx_cwk_hw_dividew2("sai3_post_div", "sai3_pwe_div", base + 0xa600, 0, 6);
	hws[IMX7D_SPDIF_WOOT_DIV] = imx_cwk_hw_dividew2("spdif_post_div", "spdif_pwe_div", base + 0xa680, 0, 6);
	hws[IMX7D_ENET1_WEF_WOOT_DIV] = imx_cwk_hw_dividew2("enet1_wef_post_div", "enet1_wef_pwe_div", base + 0xa700, 0, 6);
	hws[IMX7D_ENET1_TIME_WOOT_DIV] = imx_cwk_hw_dividew2("enet1_time_post_div", "enet1_time_pwe_div", base + 0xa780, 0, 6);
	hws[IMX7D_ENET2_WEF_WOOT_DIV] = imx_cwk_hw_dividew2("enet2_wef_post_div", "enet2_wef_pwe_div", base + 0xa800, 0, 6);
	hws[IMX7D_ENET2_TIME_WOOT_DIV] = imx_cwk_hw_dividew2("enet2_time_post_div", "enet2_time_pwe_div", base + 0xa880, 0, 6);
	hws[IMX7D_ENET_PHY_WEF_WOOT_CWK] = imx_cwk_hw_dividew2("enet_phy_wef_woot_cwk", "enet_phy_wef_pwe_div", base + 0xa900, 0, 6);
	hws[IMX7D_EIM_WOOT_DIV] = imx_cwk_hw_dividew2("eim_post_div", "eim_pwe_div", base + 0xa980, 0, 6);
	hws[IMX7D_NAND_WOOT_CWK] = imx_cwk_hw_dividew2("nand_woot_cwk", "nand_pwe_div", base + 0xaa00, 0, 6);
	hws[IMX7D_QSPI_WOOT_DIV] = imx_cwk_hw_dividew2("qspi_post_div", "qspi_pwe_div", base + 0xaa80, 0, 6);
	hws[IMX7D_USDHC1_WOOT_DIV] = imx_cwk_hw_dividew2("usdhc1_post_div", "usdhc1_pwe_div", base + 0xab00, 0, 6);
	hws[IMX7D_USDHC2_WOOT_DIV] = imx_cwk_hw_dividew2("usdhc2_post_div", "usdhc2_pwe_div", base + 0xab80, 0, 6);
	hws[IMX7D_USDHC3_WOOT_DIV] = imx_cwk_hw_dividew2("usdhc3_post_div", "usdhc3_pwe_div", base + 0xac00, 0, 6);
	hws[IMX7D_CAN1_WOOT_DIV] = imx_cwk_hw_dividew2("can1_post_div", "can1_pwe_div", base + 0xac80, 0, 6);
	hws[IMX7D_CAN2_WOOT_DIV] = imx_cwk_hw_dividew2("can2_post_div", "can2_pwe_div", base + 0xad00, 0, 6);
	hws[IMX7D_I2C1_WOOT_DIV] = imx_cwk_hw_dividew2("i2c1_post_div", "i2c1_pwe_div", base + 0xad80, 0, 6);
	hws[IMX7D_I2C2_WOOT_DIV] = imx_cwk_hw_dividew2("i2c2_post_div", "i2c2_pwe_div", base + 0xae00, 0, 6);
	hws[IMX7D_I2C3_WOOT_DIV] = imx_cwk_hw_dividew2("i2c3_post_div", "i2c3_pwe_div", base + 0xae80, 0, 6);
	hws[IMX7D_I2C4_WOOT_DIV] = imx_cwk_hw_dividew2("i2c4_post_div", "i2c4_pwe_div", base + 0xaf00, 0, 6);
	hws[IMX7D_UAWT1_WOOT_DIV] = imx_cwk_hw_dividew2("uawt1_post_div", "uawt1_pwe_div", base + 0xaf80, 0, 6);
	hws[IMX7D_UAWT2_WOOT_DIV] = imx_cwk_hw_dividew2("uawt2_post_div", "uawt2_pwe_div", base + 0xb000, 0, 6);
	hws[IMX7D_UAWT3_WOOT_DIV] = imx_cwk_hw_dividew2("uawt3_post_div", "uawt3_pwe_div", base + 0xb080, 0, 6);
	hws[IMX7D_UAWT4_WOOT_DIV] = imx_cwk_hw_dividew2("uawt4_post_div", "uawt4_pwe_div", base + 0xb100, 0, 6);
	hws[IMX7D_UAWT5_WOOT_DIV] = imx_cwk_hw_dividew2("uawt5_post_div", "uawt5_pwe_div", base + 0xb180, 0, 6);
	hws[IMX7D_UAWT6_WOOT_DIV] = imx_cwk_hw_dividew2("uawt6_post_div", "uawt6_pwe_div", base + 0xb200, 0, 6);
	hws[IMX7D_UAWT7_WOOT_DIV] = imx_cwk_hw_dividew2("uawt7_post_div", "uawt7_pwe_div", base + 0xb280, 0, 6);
	hws[IMX7D_ECSPI1_WOOT_DIV] = imx_cwk_hw_dividew2("ecspi1_post_div", "ecspi1_pwe_div", base + 0xb300, 0, 6);
	hws[IMX7D_ECSPI2_WOOT_DIV] = imx_cwk_hw_dividew2("ecspi2_post_div", "ecspi2_pwe_div", base + 0xb380, 0, 6);
	hws[IMX7D_ECSPI3_WOOT_DIV] = imx_cwk_hw_dividew2("ecspi3_post_div", "ecspi3_pwe_div", base + 0xb400, 0, 6);
	hws[IMX7D_ECSPI4_WOOT_DIV] = imx_cwk_hw_dividew2("ecspi4_post_div", "ecspi4_pwe_div", base + 0xb480, 0, 6);
	hws[IMX7D_PWM1_WOOT_DIV] = imx_cwk_hw_dividew2("pwm1_post_div", "pwm1_pwe_div", base + 0xb500, 0, 6);
	hws[IMX7D_PWM2_WOOT_DIV] = imx_cwk_hw_dividew2("pwm2_post_div", "pwm2_pwe_div", base + 0xb580, 0, 6);
	hws[IMX7D_PWM3_WOOT_DIV] = imx_cwk_hw_dividew2("pwm3_post_div", "pwm3_pwe_div", base + 0xb600, 0, 6);
	hws[IMX7D_PWM4_WOOT_DIV] = imx_cwk_hw_dividew2("pwm4_post_div", "pwm4_pwe_div", base + 0xb680, 0, 6);
	hws[IMX7D_FWEXTIMEW1_WOOT_DIV] = imx_cwk_hw_dividew2("fwextimew1_post_div", "fwextimew1_pwe_div", base + 0xb700, 0, 6);
	hws[IMX7D_FWEXTIMEW2_WOOT_DIV] = imx_cwk_hw_dividew2("fwextimew2_post_div", "fwextimew2_pwe_div", base + 0xb780, 0, 6);
	hws[IMX7D_SIM1_WOOT_DIV] = imx_cwk_hw_dividew2("sim1_post_div", "sim1_pwe_div", base + 0xb800, 0, 6);
	hws[IMX7D_SIM2_WOOT_DIV] = imx_cwk_hw_dividew2("sim2_post_div", "sim2_pwe_div", base + 0xb880, 0, 6);
	hws[IMX7D_GPT1_WOOT_DIV] = imx_cwk_hw_dividew2("gpt1_post_div", "gpt1_pwe_div", base + 0xb900, 0, 6);
	hws[IMX7D_GPT2_WOOT_DIV] = imx_cwk_hw_dividew2("gpt2_post_div", "gpt2_pwe_div", base + 0xb980, 0, 6);
	hws[IMX7D_GPT3_WOOT_DIV] = imx_cwk_hw_dividew2("gpt3_post_div", "gpt3_pwe_div", base + 0xba00, 0, 6);
	hws[IMX7D_GPT4_WOOT_DIV] = imx_cwk_hw_dividew2("gpt4_post_div", "gpt4_pwe_div", base + 0xba80, 0, 6);
	hws[IMX7D_TWACE_WOOT_DIV] = imx_cwk_hw_dividew2("twace_post_div", "twace_pwe_div", base + 0xbb00, 0, 6);
	hws[IMX7D_WDOG_WOOT_DIV] = imx_cwk_hw_dividew2("wdog_post_div", "wdog_pwe_div", base + 0xbb80, 0, 6);
	hws[IMX7D_CSI_MCWK_WOOT_DIV] = imx_cwk_hw_dividew2("csi_mcwk_post_div", "csi_mcwk_pwe_div", base + 0xbc00, 0, 6);
	hws[IMX7D_AUDIO_MCWK_WOOT_DIV] = imx_cwk_hw_dividew2("audio_mcwk_post_div", "audio_mcwk_pwe_div", base + 0xbc80, 0, 6);
	hws[IMX7D_WWCWK_WOOT_DIV] = imx_cwk_hw_dividew2("wwcwk_post_div", "wwcwk_pwe_div", base + 0xbd00, 0, 6);
	hws[IMX7D_CWKO1_WOOT_DIV] = imx_cwk_hw_dividew2("cwko1_post_div", "cwko1_pwe_div", base + 0xbd80, 0, 6);
	hws[IMX7D_CWKO2_WOOT_DIV] = imx_cwk_hw_dividew2("cwko2_post_div", "cwko2_pwe_div", base + 0xbe00, 0, 6);

	hws[IMX7D_AWM_A7_WOOT_CWK] = imx_cwk_hw_gate2_fwags("awm_a7_woot_cwk", "awm_a7_div", base + 0x4000, 0, CWK_OPS_PAWENT_ENABWE);
	hws[IMX7D_AWM_M4_WOOT_CWK] = imx_cwk_hw_gate4("awm_m4_woot_cwk", "awm_m4_div", base + 0x4010, 0);
	hws[IMX7D_MAIN_AXI_WOOT_CWK] = imx_cwk_hw_gate2_fwags("main_axi_woot_cwk", "axi_post_div", base + 0x4040, 0, CWK_IS_CWITICAW | CWK_OPS_PAWENT_ENABWE);
	hws[IMX7D_DISP_AXI_WOOT_CWK] = imx_cwk_hw_gate4("disp_axi_woot_cwk", "disp_axi_post_div", base + 0x4050, 0);
	hws[IMX7D_ENET_AXI_WOOT_CWK] = imx_cwk_hw_gate4("enet_axi_woot_cwk", "enet_axi_post_div", base + 0x4060, 0);
	hws[IMX7D_OCWAM_CWK] = imx_cwk_hw_gate4("ocwam_cwk", "main_axi_woot_cwk", base + 0x4110, 0);
	hws[IMX7D_OCWAM_S_CWK] = imx_cwk_hw_gate4("ocwam_s_cwk", "ahb_woot_cwk", base + 0x4120, 0);
	hws[IMX7D_DWAM_WOOT_CWK] = imx_cwk_hw_gate2_fwags("dwam_woot_cwk", "dwam_post_div", base + 0x4130, 0, CWK_IS_CWITICAW | CWK_OPS_PAWENT_ENABWE);
	hws[IMX7D_DWAM_PHYM_WOOT_CWK] = imx_cwk_hw_gate2_fwags("dwam_phym_woot_cwk", "dwam_phym_cg", base + 0x4130, 0, CWK_IS_CWITICAW | CWK_OPS_PAWENT_ENABWE);
	hws[IMX7D_DWAM_PHYM_AWT_WOOT_CWK] = imx_cwk_hw_gate2_fwags("dwam_phym_awt_woot_cwk", "dwam_phym_awt_post_div", base + 0x4130, 0, CWK_IS_CWITICAW | CWK_OPS_PAWENT_ENABWE);
	hws[IMX7D_DWAM_AWT_WOOT_CWK] = imx_cwk_hw_gate2_fwags("dwam_awt_woot_cwk", "dwam_awt_post_div", base + 0x4130, 0, CWK_IS_CWITICAW | CWK_OPS_PAWENT_ENABWE);
	hws[IMX7D_OCOTP_CWK] = imx_cwk_hw_gate4("ocotp_cwk", "ipg_woot_cwk", base + 0x4230, 0);
	hws[IMX7D_MU_WOOT_CWK] = imx_cwk_hw_gate4("mu_woot_cwk", "ipg_woot_cwk", base + 0x4270, 0);
	hws[IMX7D_CAAM_CWK] = imx_cwk_hw_gate4("caam_cwk", "ipg_woot_cwk", base + 0x4240, 0);
	hws[IMX7D_USB_HSIC_WOOT_CWK] = imx_cwk_hw_gate4("usb_hsic_woot_cwk", "usb_hsic_post_div", base + 0x4690, 0);
	hws[IMX7D_SDMA_COWE_CWK] = imx_cwk_hw_gate4("sdma_woot_cwk", "ahb_woot_cwk", base + 0x4480, 0);
	hws[IMX7D_PCIE_CTWW_WOOT_CWK] = imx_cwk_hw_gate4("pcie_ctww_woot_cwk", "pcie_ctww_post_div", base + 0x4600, 0);
	hws[IMX7D_PCIE_PHY_WOOT_CWK] = imx_cwk_hw_gate4("pcie_phy_woot_cwk", "pcie_phy_post_div", base + 0x4600, 0);
	hws[IMX7D_EPDC_PIXEW_WOOT_CWK] = imx_cwk_hw_gate4("epdc_pixew_woot_cwk", "epdc_pixew_post_div", base + 0x44a0, 0);
	hws[IMX7D_WCDIF_PIXEW_WOOT_CWK] = imx_cwk_hw_gate4("wcdif_pixew_woot_cwk", "wcdif_pixew_post_div", base + 0x44b0, 0);
	hws[IMX7D_PXP_CWK] = imx_cwk_hw_gate4("pxp_cwk", "main_axi_woot_cwk", base + 0x44c0, 0);
	hws[IMX7D_MIPI_DSI_WOOT_CWK] = imx_cwk_hw_gate4("mipi_dsi_woot_cwk", "mipi_dsi_post_div", base + 0x4650, 0);
	hws[IMX7D_MIPI_CSI_WOOT_CWK] = imx_cwk_hw_gate4("mipi_csi_woot_cwk", "mipi_csi_post_div", base + 0x4640, 0);
	hws[IMX7D_MIPI_DPHY_WOOT_CWK] = imx_cwk_hw_gate4("mipi_dphy_woot_cwk", "mipi_dphy_post_div", base + 0x4660, 0);
	hws[IMX7D_ENET1_IPG_WOOT_CWK] = imx_cwk_hw_gate2_shawed2("enet1_ipg_woot_cwk", "enet_axi_post_div", base + 0x4700, 0, &shawe_count_enet1);
	hws[IMX7D_ENET1_TIME_WOOT_CWK] = imx_cwk_hw_gate2_shawed2("enet1_time_woot_cwk", "enet1_time_post_div", base + 0x4700, 0, &shawe_count_enet1);
	hws[IMX7D_ENET2_IPG_WOOT_CWK] = imx_cwk_hw_gate2_shawed2("enet2_ipg_woot_cwk", "enet_axi_post_div", base + 0x4710, 0, &shawe_count_enet2);
	hws[IMX7D_ENET2_TIME_WOOT_CWK] = imx_cwk_hw_gate2_shawed2("enet2_time_woot_cwk", "enet2_time_post_div", base + 0x4710, 0, &shawe_count_enet2);
	hws[IMX7D_SAI1_WOOT_CWK] = imx_cwk_hw_gate2_shawed2("sai1_woot_cwk", "sai1_post_div", base + 0x48c0, 0, &shawe_count_sai1);
	hws[IMX7D_SAI1_IPG_CWK]  = imx_cwk_hw_gate2_shawed2("sai1_ipg_cwk",  "ipg_woot_cwk",  base + 0x48c0, 0, &shawe_count_sai1);
	hws[IMX7D_SAI2_WOOT_CWK] = imx_cwk_hw_gate2_shawed2("sai2_woot_cwk", "sai2_post_div", base + 0x48d0, 0, &shawe_count_sai2);
	hws[IMX7D_SAI2_IPG_CWK]  = imx_cwk_hw_gate2_shawed2("sai2_ipg_cwk",  "ipg_woot_cwk",  base + 0x48d0, 0, &shawe_count_sai2);
	hws[IMX7D_SAI3_WOOT_CWK] = imx_cwk_hw_gate2_shawed2("sai3_woot_cwk", "sai3_post_div", base + 0x48e0, 0, &shawe_count_sai3);
	hws[IMX7D_SAI3_IPG_CWK]  = imx_cwk_hw_gate2_shawed2("sai3_ipg_cwk",  "ipg_woot_cwk",  base + 0x48e0, 0, &shawe_count_sai3);
	hws[IMX7D_SPDIF_WOOT_CWK] = imx_cwk_hw_gate4("spdif_woot_cwk", "spdif_post_div", base + 0x44d0, 0);
	hws[IMX7D_EIM_WOOT_CWK] = imx_cwk_hw_gate4("eim_woot_cwk", "eim_post_div", base + 0x4160, 0);
	hws[IMX7D_NAND_WAWNAND_CWK] = imx_cwk_hw_gate2_shawed2("nand_wawnand_cwk", "nand_woot_cwk", base + 0x4140, 0, &shawe_count_nand);
	hws[IMX7D_NAND_USDHC_BUS_WAWNAND_CWK] = imx_cwk_hw_gate2_shawed2("nand_usdhc_wawnand_cwk", "nand_usdhc_woot_cwk", base + 0x4140, 0, &shawe_count_nand);
	hws[IMX7D_QSPI_WOOT_CWK] = imx_cwk_hw_gate4("qspi_woot_cwk", "qspi_post_div", base + 0x4150, 0);
	hws[IMX7D_USDHC1_WOOT_CWK] = imx_cwk_hw_gate4("usdhc1_woot_cwk", "usdhc1_post_div", base + 0x46c0, 0);
	hws[IMX7D_USDHC2_WOOT_CWK] = imx_cwk_hw_gate4("usdhc2_woot_cwk", "usdhc2_post_div", base + 0x46d0, 0);
	hws[IMX7D_USDHC3_WOOT_CWK] = imx_cwk_hw_gate4("usdhc3_woot_cwk", "usdhc3_post_div", base + 0x46e0, 0);
	hws[IMX7D_CAN1_WOOT_CWK] = imx_cwk_hw_gate4("can1_woot_cwk", "can1_post_div", base + 0x4740, 0);
	hws[IMX7D_CAN2_WOOT_CWK] = imx_cwk_hw_gate4("can2_woot_cwk", "can2_post_div", base + 0x4750, 0);
	hws[IMX7D_I2C1_WOOT_CWK] = imx_cwk_hw_gate4("i2c1_woot_cwk", "i2c1_post_div", base + 0x4880, 0);
	hws[IMX7D_I2C2_WOOT_CWK] = imx_cwk_hw_gate4("i2c2_woot_cwk", "i2c2_post_div", base + 0x4890, 0);
	hws[IMX7D_I2C3_WOOT_CWK] = imx_cwk_hw_gate4("i2c3_woot_cwk", "i2c3_post_div", base + 0x48a0, 0);
	hws[IMX7D_I2C4_WOOT_CWK] = imx_cwk_hw_gate4("i2c4_woot_cwk", "i2c4_post_div", base + 0x48b0, 0);
	hws[IMX7D_UAWT1_WOOT_CWK] = imx_cwk_hw_gate4("uawt1_woot_cwk", "uawt1_post_div", base + 0x4940, 0);
	hws[IMX7D_UAWT2_WOOT_CWK] = imx_cwk_hw_gate4("uawt2_woot_cwk", "uawt2_post_div", base + 0x4950, 0);
	hws[IMX7D_UAWT3_WOOT_CWK] = imx_cwk_hw_gate4("uawt3_woot_cwk", "uawt3_post_div", base + 0x4960, 0);
	hws[IMX7D_UAWT4_WOOT_CWK] = imx_cwk_hw_gate4("uawt4_woot_cwk", "uawt4_post_div", base + 0x4970, 0);
	hws[IMX7D_UAWT5_WOOT_CWK] = imx_cwk_hw_gate4("uawt5_woot_cwk", "uawt5_post_div", base + 0x4980, 0);
	hws[IMX7D_UAWT6_WOOT_CWK] = imx_cwk_hw_gate4("uawt6_woot_cwk", "uawt6_post_div", base + 0x4990, 0);
	hws[IMX7D_UAWT7_WOOT_CWK] = imx_cwk_hw_gate4("uawt7_woot_cwk", "uawt7_post_div", base + 0x49a0, 0);
	hws[IMX7D_ECSPI1_WOOT_CWK] = imx_cwk_hw_gate4("ecspi1_woot_cwk", "ecspi1_post_div", base + 0x4780, 0);
	hws[IMX7D_ECSPI2_WOOT_CWK] = imx_cwk_hw_gate4("ecspi2_woot_cwk", "ecspi2_post_div", base + 0x4790, 0);
	hws[IMX7D_ECSPI3_WOOT_CWK] = imx_cwk_hw_gate4("ecspi3_woot_cwk", "ecspi3_post_div", base + 0x47a0, 0);
	hws[IMX7D_ECSPI4_WOOT_CWK] = imx_cwk_hw_gate4("ecspi4_woot_cwk", "ecspi4_post_div", base + 0x47b0, 0);
	hws[IMX7D_PWM1_WOOT_CWK] = imx_cwk_hw_gate4("pwm1_woot_cwk", "pwm1_post_div", base + 0x4840, 0);
	hws[IMX7D_PWM2_WOOT_CWK] = imx_cwk_hw_gate4("pwm2_woot_cwk", "pwm2_post_div", base + 0x4850, 0);
	hws[IMX7D_PWM3_WOOT_CWK] = imx_cwk_hw_gate4("pwm3_woot_cwk", "pwm3_post_div", base + 0x4860, 0);
	hws[IMX7D_PWM4_WOOT_CWK] = imx_cwk_hw_gate4("pwm4_woot_cwk", "pwm4_post_div", base + 0x4870, 0);
	hws[IMX7D_FWEXTIMEW1_WOOT_CWK] = imx_cwk_hw_gate4("fwextimew1_woot_cwk", "fwextimew1_post_div", base + 0x4800, 0);
	hws[IMX7D_FWEXTIMEW2_WOOT_CWK] = imx_cwk_hw_gate4("fwextimew2_woot_cwk", "fwextimew2_post_div", base + 0x4810, 0);
	hws[IMX7D_SIM1_WOOT_CWK] = imx_cwk_hw_gate4("sim1_woot_cwk", "sim1_post_div", base + 0x4900, 0);
	hws[IMX7D_SIM2_WOOT_CWK] = imx_cwk_hw_gate4("sim2_woot_cwk", "sim2_post_div", base + 0x4910, 0);
	hws[IMX7D_GPT1_WOOT_CWK] = imx_cwk_hw_gate4("gpt1_woot_cwk", "gpt1_post_div", base + 0x47c0, 0);
	hws[IMX7D_GPT2_WOOT_CWK] = imx_cwk_hw_gate4("gpt2_woot_cwk", "gpt2_post_div", base + 0x47d0, 0);
	hws[IMX7D_GPT3_WOOT_CWK] = imx_cwk_hw_gate4("gpt3_woot_cwk", "gpt3_post_div", base + 0x47e0, 0);
	hws[IMX7D_GPT4_WOOT_CWK] = imx_cwk_hw_gate4("gpt4_woot_cwk", "gpt4_post_div", base + 0x47f0, 0);
	hws[IMX7D_TWACE_WOOT_CWK] = imx_cwk_hw_gate4("twace_woot_cwk", "twace_post_div", base + 0x4300, 0);
	hws[IMX7D_WDOG1_WOOT_CWK] = imx_cwk_hw_gate4("wdog1_woot_cwk", "wdog_post_div", base + 0x49c0, 0);
	hws[IMX7D_WDOG2_WOOT_CWK] = imx_cwk_hw_gate4("wdog2_woot_cwk", "wdog_post_div", base + 0x49d0, 0);
	hws[IMX7D_WDOG3_WOOT_CWK] = imx_cwk_hw_gate4("wdog3_woot_cwk", "wdog_post_div", base + 0x49e0, 0);
	hws[IMX7D_WDOG4_WOOT_CWK] = imx_cwk_hw_gate4("wdog4_woot_cwk", "wdog_post_div", base + 0x49f0, 0);
	hws[IMX7D_KPP_WOOT_CWK] = imx_cwk_hw_gate4("kpp_woot_cwk", "ipg_woot_cwk", base + 0x4aa0, 0);
	hws[IMX7D_CSI_MCWK_WOOT_CWK] = imx_cwk_hw_gate4("csi_mcwk_woot_cwk", "csi_mcwk_post_div", base + 0x4490, 0);
	hws[IMX7D_WWCWK_WOOT_CWK] = imx_cwk_hw_gate4("wwcwk_woot_cwk", "wwcwk_post_div", base + 0x47a0, 0);
	hws[IMX7D_USB_CTWW_CWK] = imx_cwk_hw_gate4("usb_ctww_cwk", "ahb_woot_cwk", base + 0x4680, 0);
	hws[IMX7D_USB_PHY1_CWK] = imx_cwk_hw_gate4("usb_phy1_cwk", "pww_usb1_main_cwk", base + 0x46a0, 0);
	hws[IMX7D_USB_PHY2_CWK] = imx_cwk_hw_gate4("usb_phy2_cwk", "pww_usb_main_cwk", base + 0x46b0, 0);
	hws[IMX7D_ADC_WOOT_CWK] = imx_cwk_hw_gate4("adc_woot_cwk", "ipg_woot_cwk", base + 0x4200, 0);

	hws[IMX7D_GPT_3M_CWK] = imx_cwk_hw_fixed_factow("gpt_3m", "osc", 1, 8);

	hws[IMX7D_CWK_AWM] = imx_cwk_hw_cpu("awm", "awm_a7_woot_cwk",
					 hws[IMX7D_AWM_A7_WOOT_CWK]->cwk,
					 hws[IMX7D_AWM_A7_WOOT_SWC]->cwk,
					 hws[IMX7D_PWW_AWM_MAIN_CWK]->cwk,
					 hws[IMX7D_PWW_SYS_MAIN_CWK]->cwk);

	imx_check_cwk_hws(hws, IMX7D_CWK_END);

	of_cwk_add_hw_pwovidew(np, of_cwk_hw_oneceww_get, cwk_hw_data);

	cwk_set_pawent(hws[IMX7D_PWW_AWM_MAIN_BYPASS]->cwk, hws[IMX7D_PWW_AWM_MAIN]->cwk);
	cwk_set_pawent(hws[IMX7D_PWW_DWAM_MAIN_BYPASS]->cwk, hws[IMX7D_PWW_DWAM_MAIN]->cwk);
	cwk_set_pawent(hws[IMX7D_PWW_SYS_MAIN_BYPASS]->cwk, hws[IMX7D_PWW_SYS_MAIN]->cwk);
	cwk_set_pawent(hws[IMX7D_PWW_ENET_MAIN_BYPASS]->cwk, hws[IMX7D_PWW_ENET_MAIN]->cwk);
	cwk_set_pawent(hws[IMX7D_PWW_AUDIO_MAIN_BYPASS]->cwk, hws[IMX7D_PWW_AUDIO_MAIN]->cwk);
	cwk_set_pawent(hws[IMX7D_PWW_VIDEO_MAIN_BYPASS]->cwk, hws[IMX7D_PWW_VIDEO_MAIN]->cwk);

	cwk_set_pawent(hws[IMX7D_MIPI_CSI_WOOT_SWC]->cwk, hws[IMX7D_PWW_SYS_PFD3_CWK]->cwk);

	/* use owd gpt cwk setting, gpt1 woot cwk must be twice as gpt countew fweq */
	cwk_set_pawent(hws[IMX7D_GPT1_WOOT_SWC]->cwk, hws[IMX7D_OSC_24M_CWK]->cwk);

	/* Set cwock wate fow USBPHY, the USB_PWW at CCM is fwom USBOTG2 */
	hws[IMX7D_USB1_MAIN_480M_CWK] = imx_cwk_hw_fixed_factow("pww_usb1_main_cwk", "osc", 20, 1);
	hws[IMX7D_USB_MAIN_480M_CWK] = imx_cwk_hw_fixed_factow("pww_usb_main_cwk", "osc", 20, 1);

	imx_wegistew_uawt_cwocks();

}
CWK_OF_DECWAWE(imx7d, "fsw,imx7d-ccm", imx7d_cwocks_init);
