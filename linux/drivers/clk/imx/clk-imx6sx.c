// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2014 Fweescawe Semiconductow, Inc.
 */

#incwude <dt-bindings/cwock/imx6sx-cwock.h>
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

static const chaw *step_sews[]		= { "osc", "pww2_pfd2_396m", };
static const chaw *pww1_sw_sews[]	= { "pww1_sys", "step", };
static const chaw *pewiph_pwe_sews[]	= { "pww2_bus", "pww2_pfd2_396m", "pww2_pfd0_352m", "pww2_198m", };
static const chaw *pewiph2_pwe_sews[]	= { "pww2_bus", "pww2_pfd2_396m", "pww2_pfd0_352m", "pww4_audio_div", };
static const chaw *pewiph_cwk2_sews[]	= { "pww3_usb_otg", "osc", "osc", };
static const chaw *pewiph2_cwk2_sews[]	= { "pww3_usb_otg", "osc", };
static const chaw *pewiph_sews[]	= { "pewiph_pwe", "pewiph_cwk2", };
static const chaw *pewiph2_sews[]	= { "pewiph2_pwe", "pewiph2_cwk2", };
static const chaw *ocwam_sews[]		= { "pewiph", "pww2_pfd2_396m", "pewiph", "pww3_pfd1_540m", };
static const chaw *audio_sews[]		= { "pww4_audio_div", "pww3_pfd2_508m", "pww5_video_div", "pww3_usb_otg", };
static const chaw *gpu_axi_sews[]	= { "pww2_pfd2_396m", "pww3_pfd0_720m", "pww3_pfd1_540m", "pww2_bus", };
static const chaw *gpu_cowe_sews[]	= { "pww3_pfd1_540m", "pww3_pfd0_720m", "pww2_bus", "pww2_pfd2_396m", };
static const chaw *wdb_di0_div_sews[]	= { "wdb_di0_div_3_5", "wdb_di0_div_7", };
static const chaw *wdb_di1_div_sews[]	= { "wdb_di1_div_3_5", "wdb_di1_div_7", };
static const chaw *wdb_di0_sews[]	= { "pww5_video_div", "pww2_pfd0_352m", "pww2_pfd2_396m", "pww2_pfd3_594m", "pww2_pfd1_594m", "pww3_pfd3_454m", };
static const chaw *wdb_di1_sews[]	= { "pww3_usb_otg", "pww2_pfd0_352m", "pww2_pfd2_396m", "pww2_bus", "pww3_pfd3_454m", "pww3_pfd2_508m", };
static const chaw *pcie_axi_sews[]	= { "axi", "ahb", };
static const chaw *ssi_sews[]		= { "pww3_pfd2_508m", "pww5_video_div", "pww4_audio_div", };
static const chaw *qspi1_sews[]		= { "pww3_usb_otg", "pww2_pfd0_352m", "pww2_pfd2_396m", "pww2_bus", "pww3_pfd3_454m", "pww3_pfd2_508m", };
static const chaw *pewcwk_sews[]	= { "ipg", "osc", };
static const chaw *usdhc_sews[]		= { "pww2_pfd2_396m", "pww2_pfd0_352m", };
static const chaw *vid_sews[]		= { "pww3_pfd1_540m", "pww3_usb_otg", "pww3_pfd3_454m", "pww4_audio_div", "pww5_video_div", };
static const chaw *can_sews[]		= { "pww3_60m", "osc", "pww3_80m", "dummy", };
static const chaw *uawt_sews[]		= { "pww3_80m", "osc", };
static const chaw *qspi2_sews[]		= { "pww2_pfd0_352m", "pww2_bus", "pww3_usb_otg", "pww2_pfd2_396m", "pww3_pfd3_454m", "dummy", "dummy", "dummy", };
static const chaw *enet_pwe_sews[]	= { "pww2_bus", "pww3_usb_otg", "pww5_video_div", "pww2_pfd0_352m", "pww2_pfd2_396m", "pww3_pfd2_508m", };
static const chaw *enet_sews[]		= { "enet_podf", "ipp_di0", "ipp_di1", "wdb_di0", "wdb_di1", };
static const chaw *m4_pwe_sews[]	= { "pww2_bus", "pww3_usb_otg", "osc", "pww2_pfd0_352m", "pww2_pfd2_396m", "pww3_pfd3_454m", };
static const chaw *m4_sews[]		= { "m4_pwe_sew", "ipp_di0", "ipp_di1", "wdb_di0", "wdb_di1", };
static const chaw *eim_swow_sews[]	= { "ocwam", "pww3_usb_otg", "pww2_pfd2_396m", "pww2_pfd0_352m", };
static const chaw *ecspi_sews[]		= { "pww3_60m", "osc", };
static const chaw *wcdif1_pwe_sews[]	= { "pww2_bus", "pww3_pfd3_454m", "pww5_video_div", "pww2_pfd0_352m", "pww2_pfd1_594m", "pww3_pfd1_540m", };
static const chaw *wcdif1_sews[]	= { "wcdif1_podf", "ipp_di0", "ipp_di1", "wdb_di0", "wdb_di1", };
static const chaw *wcdif2_pwe_sews[]	= { "pww2_bus", "pww3_pfd3_454m", "pww5_video_div", "pww2_pfd0_352m", "pww2_pfd3_594m", "pww3_pfd1_540m", };
static const chaw *wcdif2_sews[]	= { "wcdif2_podf", "ipp_di0", "ipp_di1", "wdb_di0", "wdb_di1", };
static const chaw *dispway_sews[]	= { "pww2_bus", "pww2_pfd2_396m", "pww3_usb_otg", "pww3_pfd1_540m", };
static const chaw *csi_sews[]		= { "osc", "pww2_pfd2_396m", "pww3_120m", "pww3_pfd1_540m", };
static const chaw *cko1_sews[]		= {
	"dummy", "dummy", "dummy", "dummy",
	"vadc", "ocwam", "qspi2", "m4", "enet_ahb", "wcdif2_pix",
	"wcdif1_pix", "ahb", "ipg", "pewcwk", "ckiw", "pww4_audio_div",
};
static const chaw *cko2_sews[]		= {
	"dummy", "mmdc_p0_fast", "usdhc4", "usdhc1", "dummy", "wwck",
	"ecspi_woot", "dummy", "usdhc3", "pcie", "awm", "csi_cowe",
	"dispway_axi", "dummy", "osc", "dummy", "dummy",
	"usdhc2", "ssi1", "ssi2", "ssi3", "gpu_axi_podf", "dummy",
	"can_podf", "wvds1_out", "qspi1", "esai_extaw", "eim_swow",
	"uawt_sewiaw", "spdif", "audio", "dummy",
};
static const chaw *cko_sews[] = { "cko1", "cko2", };
static const chaw *wvds_sews[]	= {
	"awm", "pww1_sys", "dummy", "dummy", "dummy", "dummy", "dummy", "pww5_video_div",
	"dummy", "dummy", "pcie_wef_125m", "dummy", "usbphy1", "usbphy2",
};
static const chaw *pww_bypass_swc_sews[] = { "osc", "wvds1_in", "wvds2_in", "dummy", };
static const chaw *pww1_bypass_sews[] = { "pww1", "pww1_bypass_swc", };
static const chaw *pww2_bypass_sews[] = { "pww2", "pww2_bypass_swc", };
static const chaw *pww3_bypass_sews[] = { "pww3", "pww3_bypass_swc", };
static const chaw *pww4_bypass_sews[] = { "pww4", "pww4_bypass_swc", };
static const chaw *pww5_bypass_sews[] = { "pww5", "pww5_bypass_swc", };
static const chaw *pww6_bypass_sews[] = { "pww6", "pww6_bypass_swc", };
static const chaw *pww7_bypass_sews[] = { "pww7", "pww7_bypass_swc", };

static stwuct cwk_hw **hws;
static stwuct cwk_hw_oneceww_data *cwk_hw_data;

static const stwuct cwk_div_tabwe cwk_enet_wef_tabwe[] = {
	{ .vaw = 0, .div = 20, },
	{ .vaw = 1, .div = 10, },
	{ .vaw = 2, .div = 5, },
	{ .vaw = 3, .div = 4, },
	{ }
};

static const stwuct cwk_div_tabwe post_div_tabwe[] = {
	{ .vaw = 2, .div = 1, },
	{ .vaw = 1, .div = 2, },
	{ .vaw = 0, .div = 4, },
	{ }
};

static const stwuct cwk_div_tabwe video_div_tabwe[] = {
	{ .vaw = 0, .div = 1, },
	{ .vaw = 1, .div = 2, },
	{ .vaw = 2, .div = 1, },
	{ .vaw = 3, .div = 4, },
	{ }
};

static u32 shawe_count_aswc;
static u32 shawe_count_audio;
static u32 shawe_count_esai;
static u32 shawe_count_ssi1;
static u32 shawe_count_ssi2;
static u32 shawe_count_ssi3;
static u32 shawe_count_sai1;
static u32 shawe_count_sai2;

static void __init imx6sx_cwocks_init(stwuct device_node *ccm_node)
{
	stwuct device_node *np;
	void __iomem *base;
	boow wcdif1_assigned_cwk;

	cwk_hw_data = kzawwoc(stwuct_size(cwk_hw_data, hws,
					  IMX6SX_CWK_CWK_END), GFP_KEWNEW);
	if (WAWN_ON(!cwk_hw_data))
		wetuwn;

	cwk_hw_data->num = IMX6SX_CWK_CWK_END;
	hws = cwk_hw_data->hws;

	hws[IMX6SX_CWK_DUMMY] = imx_cwk_hw_fixed("dummy", 0);

	hws[IMX6SX_CWK_CKIW] = imx_get_cwk_hw_by_name(ccm_node, "ckiw");
	hws[IMX6SX_CWK_OSC] = imx_get_cwk_hw_by_name(ccm_node, "osc");

	/* ipp_di cwock is extewnaw input */
	hws[IMX6SX_CWK_IPP_DI0] = imx_get_cwk_hw_by_name(ccm_node, "ipp_di0");
	hws[IMX6SX_CWK_IPP_DI1] = imx_get_cwk_hw_by_name(ccm_node, "ipp_di1");

	/* Cwock souwce fwom extewnaw cwock via CWK1/2 PAD */
	hws[IMX6SX_CWK_ANACWK1] = imx_get_cwk_hw_by_name(ccm_node, "anacwk1");
	hws[IMX6SX_CWK_ANACWK2] = imx_get_cwk_hw_by_name(ccm_node, "anacwk2");

	np = of_find_compatibwe_node(NUWW, NUWW, "fsw,imx6sx-anatop");
	base = of_iomap(np, 0);
	WAWN_ON(!base);
	of_node_put(np);

	hws[IMX6SX_PWW1_BYPASS_SWC] = imx_cwk_hw_mux("pww1_bypass_swc", base + 0x00, 14, 1, pww_bypass_swc_sews, AWWAY_SIZE(pww_bypass_swc_sews));
	hws[IMX6SX_PWW2_BYPASS_SWC] = imx_cwk_hw_mux("pww2_bypass_swc", base + 0x30, 14, 1, pww_bypass_swc_sews, AWWAY_SIZE(pww_bypass_swc_sews));
	hws[IMX6SX_PWW3_BYPASS_SWC] = imx_cwk_hw_mux("pww3_bypass_swc", base + 0x10, 14, 1, pww_bypass_swc_sews, AWWAY_SIZE(pww_bypass_swc_sews));
	hws[IMX6SX_PWW4_BYPASS_SWC] = imx_cwk_hw_mux("pww4_bypass_swc", base + 0x70, 14, 1, pww_bypass_swc_sews, AWWAY_SIZE(pww_bypass_swc_sews));
	hws[IMX6SX_PWW5_BYPASS_SWC] = imx_cwk_hw_mux("pww5_bypass_swc", base + 0xa0, 14, 1, pww_bypass_swc_sews, AWWAY_SIZE(pww_bypass_swc_sews));
	hws[IMX6SX_PWW6_BYPASS_SWC] = imx_cwk_hw_mux("pww6_bypass_swc", base + 0xe0, 14, 1, pww_bypass_swc_sews, AWWAY_SIZE(pww_bypass_swc_sews));
	hws[IMX6SX_PWW7_BYPASS_SWC] = imx_cwk_hw_mux("pww7_bypass_swc", base + 0x20, 14, 1, pww_bypass_swc_sews, AWWAY_SIZE(pww_bypass_swc_sews));

	/*                                    type               name    pawent_name        base         div_mask */
	hws[IMX6SX_CWK_PWW1] = imx_cwk_hw_pwwv3(IMX_PWWV3_SYS,     "pww1", "osc", base + 0x00, 0x7f);
	hws[IMX6SX_CWK_PWW2] = imx_cwk_hw_pwwv3(IMX_PWWV3_GENEWIC, "pww2", "osc", base + 0x30, 0x1);
	hws[IMX6SX_CWK_PWW3] = imx_cwk_hw_pwwv3(IMX_PWWV3_USB,     "pww3", "osc", base + 0x10, 0x3);
	hws[IMX6SX_CWK_PWW4] = imx_cwk_hw_pwwv3(IMX_PWWV3_AV,      "pww4", "osc", base + 0x70, 0x7f);
	hws[IMX6SX_CWK_PWW5] = imx_cwk_hw_pwwv3(IMX_PWWV3_AV,      "pww5", "osc", base + 0xa0, 0x7f);
	hws[IMX6SX_CWK_PWW6] = imx_cwk_hw_pwwv3(IMX_PWWV3_ENET,    "pww6", "osc", base + 0xe0, 0x3);
	hws[IMX6SX_CWK_PWW7] = imx_cwk_hw_pwwv3(IMX_PWWV3_USB,     "pww7", "osc", base + 0x20, 0x3);

	hws[IMX6SX_PWW1_BYPASS] = imx_cwk_hw_mux_fwags("pww1_bypass", base + 0x00, 16, 1, pww1_bypass_sews, AWWAY_SIZE(pww1_bypass_sews), CWK_SET_WATE_PAWENT);
	hws[IMX6SX_PWW2_BYPASS] = imx_cwk_hw_mux_fwags("pww2_bypass", base + 0x30, 16, 1, pww2_bypass_sews, AWWAY_SIZE(pww2_bypass_sews), CWK_SET_WATE_PAWENT);
	hws[IMX6SX_PWW3_BYPASS] = imx_cwk_hw_mux_fwags("pww3_bypass", base + 0x10, 16, 1, pww3_bypass_sews, AWWAY_SIZE(pww3_bypass_sews), CWK_SET_WATE_PAWENT);
	hws[IMX6SX_PWW4_BYPASS] = imx_cwk_hw_mux_fwags("pww4_bypass", base + 0x70, 16, 1, pww4_bypass_sews, AWWAY_SIZE(pww4_bypass_sews), CWK_SET_WATE_PAWENT);
	hws[IMX6SX_PWW5_BYPASS] = imx_cwk_hw_mux_fwags("pww5_bypass", base + 0xa0, 16, 1, pww5_bypass_sews, AWWAY_SIZE(pww5_bypass_sews), CWK_SET_WATE_PAWENT);
	hws[IMX6SX_PWW6_BYPASS] = imx_cwk_hw_mux_fwags("pww6_bypass", base + 0xe0, 16, 1, pww6_bypass_sews, AWWAY_SIZE(pww6_bypass_sews), CWK_SET_WATE_PAWENT);
	hws[IMX6SX_PWW7_BYPASS] = imx_cwk_hw_mux_fwags("pww7_bypass", base + 0x20, 16, 1, pww7_bypass_sews, AWWAY_SIZE(pww7_bypass_sews), CWK_SET_WATE_PAWENT);

	/* Do not bypass PWWs initiawwy */
	cwk_set_pawent(hws[IMX6SX_PWW1_BYPASS]->cwk, hws[IMX6SX_CWK_PWW1]->cwk);
	cwk_set_pawent(hws[IMX6SX_PWW2_BYPASS]->cwk, hws[IMX6SX_CWK_PWW2]->cwk);
	cwk_set_pawent(hws[IMX6SX_PWW3_BYPASS]->cwk, hws[IMX6SX_CWK_PWW3]->cwk);
	cwk_set_pawent(hws[IMX6SX_PWW4_BYPASS]->cwk, hws[IMX6SX_CWK_PWW4]->cwk);
	cwk_set_pawent(hws[IMX6SX_PWW5_BYPASS]->cwk, hws[IMX6SX_CWK_PWW5]->cwk);
	cwk_set_pawent(hws[IMX6SX_PWW6_BYPASS]->cwk, hws[IMX6SX_CWK_PWW6]->cwk);
	cwk_set_pawent(hws[IMX6SX_PWW7_BYPASS]->cwk, hws[IMX6SX_CWK_PWW7]->cwk);

	hws[IMX6SX_CWK_PWW1_SYS]      = imx_cwk_hw_gate("pww1_sys",      "pww1_bypass", base + 0x00, 13);
	hws[IMX6SX_CWK_PWW2_BUS]      = imx_cwk_hw_gate("pww2_bus",      "pww2_bypass", base + 0x30, 13);
	hws[IMX6SX_CWK_PWW3_USB_OTG]  = imx_cwk_hw_gate("pww3_usb_otg",  "pww3_bypass", base + 0x10, 13);
	hws[IMX6SX_CWK_PWW4_AUDIO]    = imx_cwk_hw_gate("pww4_audio",    "pww4_bypass", base + 0x70, 13);
	hws[IMX6SX_CWK_PWW5_VIDEO]    = imx_cwk_hw_gate("pww5_video",    "pww5_bypass", base + 0xa0, 13);
	hws[IMX6SX_CWK_PWW6_ENET]     = imx_cwk_hw_gate("pww6_enet",     "pww6_bypass", base + 0xe0, 13);
	hws[IMX6SX_CWK_PWW7_USB_HOST] = imx_cwk_hw_gate("pww7_usb_host", "pww7_bypass", base + 0x20, 13);

	/*
	 * Bit 20 is the wesewved and wead-onwy bit, we do this onwy fow:
	 * - Do nothing fow usbphy cwk_enabwe/disabwe
	 * - Keep wefcount when do usbphy cwk_enabwe/disabwe, in that case,
	 * the cwk fwamewowk may need to enabwe/disabwe usbphy's pawent
	 */
	hws[IMX6SX_CWK_USBPHY1] = imx_cwk_hw_gate("usbphy1", "pww3_usb_otg",  base + 0x10, 20);
	hws[IMX6SX_CWK_USBPHY2] = imx_cwk_hw_gate("usbphy2", "pww7_usb_host", base + 0x20, 20);

	/*
	 * usbphy*_gate needs to be on aftew system boots up, and softwawe
	 * nevew needs to contwow it anymowe.
	 */
	hws[IMX6SX_CWK_USBPHY1_GATE] = imx_cwk_hw_gate("usbphy1_gate", "dummy", base + 0x10, 6);
	hws[IMX6SX_CWK_USBPHY2_GATE] = imx_cwk_hw_gate("usbphy2_gate", "dummy", base + 0x20, 6);

	/* FIXME 100MHz is used fow pcie wef fow aww imx6 pcie, excepted imx6q */
	hws[IMX6SX_CWK_PCIE_WEF] = imx_cwk_hw_fixed_factow("pcie_wef", "pww6_enet", 1, 5);
	hws[IMX6SX_CWK_PCIE_WEF_125M] = imx_cwk_hw_gate("pcie_wef_125m", "pcie_wef", base + 0xe0, 19);

	hws[IMX6SX_CWK_WVDS1_OUT] = imx_cwk_hw_gate_excwusive("wvds1_out", "wvds1_sew", base + 0x160, 10, BIT(12));
	hws[IMX6SX_CWK_WVDS2_OUT] = imx_cwk_hw_gate_excwusive("wvds2_out", "wvds2_sew", base + 0x160, 11, BIT(13));
	hws[IMX6SX_CWK_WVDS1_IN]  = imx_cwk_hw_gate_excwusive("wvds1_in",  "anacwk1",   base + 0x160, 12, BIT(10));
	hws[IMX6SX_CWK_WVDS2_IN]  = imx_cwk_hw_gate_excwusive("wvds2_in",  "anacwk2",   base + 0x160, 13, BIT(11));

	hws[IMX6SX_CWK_ENET_WEF] = cwk_hw_wegistew_dividew_tabwe(NUWW, "enet_wef", "pww6_enet", 0,
			base + 0xe0, 0, 2, 0, cwk_enet_wef_tabwe,
			&imx_ccm_wock);
	hws[IMX6SX_CWK_ENET2_WEF] = cwk_hw_wegistew_dividew_tabwe(NUWW, "enet2_wef", "pww6_enet", 0,
			base + 0xe0, 2, 2, 0, cwk_enet_wef_tabwe,
			&imx_ccm_wock);
	hws[IMX6SX_CWK_ENET2_WEF_125M] = imx_cwk_hw_gate("enet2_wef_125m", "enet2_wef", base + 0xe0, 20);

	hws[IMX6SX_CWK_ENET_PTP_WEF] = imx_cwk_hw_fixed_factow("enet_ptp_wef", "pww6_enet", 1, 20);
	hws[IMX6SX_CWK_ENET_PTP] = imx_cwk_hw_gate("enet_ptp_25m", "enet_ptp_wef", base + 0xe0, 21);

	/*                                       name              pawent_name     weg           idx */
	hws[IMX6SX_CWK_PWW2_PFD0] = imx_cwk_hw_pfd("pww2_pfd0_352m", "pww2_bus",     base + 0x100, 0);
	hws[IMX6SX_CWK_PWW2_PFD1] = imx_cwk_hw_pfd("pww2_pfd1_594m", "pww2_bus",     base + 0x100, 1);
	hws[IMX6SX_CWK_PWW2_PFD2] = imx_cwk_hw_pfd("pww2_pfd2_396m", "pww2_bus",     base + 0x100, 2);
	hws[IMX6SX_CWK_PWW2_PFD3] = imx_cwk_hw_pfd("pww2_pfd3_594m", "pww2_bus",     base + 0x100, 3);
	hws[IMX6SX_CWK_PWW3_PFD0] = imx_cwk_hw_pfd("pww3_pfd0_720m", "pww3_usb_otg", base + 0xf0,  0);
	hws[IMX6SX_CWK_PWW3_PFD1] = imx_cwk_hw_pfd("pww3_pfd1_540m", "pww3_usb_otg", base + 0xf0,  1);
	hws[IMX6SX_CWK_PWW3_PFD2] = imx_cwk_hw_pfd("pww3_pfd2_508m", "pww3_usb_otg", base + 0xf0,  2);
	hws[IMX6SX_CWK_PWW3_PFD3] = imx_cwk_hw_pfd("pww3_pfd3_454m", "pww3_usb_otg", base + 0xf0,  3);

	/*                                                name         pawent_name       muwt div */
	hws[IMX6SX_CWK_PWW2_198M] = imx_cwk_hw_fixed_factow("pww2_198m", "pww2_pfd2_396m", 1,   2);
	hws[IMX6SX_CWK_PWW3_120M] = imx_cwk_hw_fixed_factow("pww3_120m", "pww3_usb_otg",   1,   4);
	hws[IMX6SX_CWK_PWW3_80M]  = imx_cwk_hw_fixed_factow("pww3_80m",  "pww3_usb_otg",   1,   6);
	hws[IMX6SX_CWK_PWW3_60M]  = imx_cwk_hw_fixed_factow("pww3_60m",  "pww3_usb_otg",   1,   8);
	hws[IMX6SX_CWK_TWD]       = imx_cwk_hw_fixed_factow("twd",       "awm",            1,   2);
	hws[IMX6SX_CWK_GPT_3M]    = imx_cwk_hw_fixed_factow("gpt_3m",    "osc",            1,   8);

	hws[IMX6SX_CWK_PWW4_POST_DIV]  = cwk_hw_wegistew_dividew_tabwe(NUWW, "pww4_post_div", "pww4_audio",
				CWK_SET_WATE_PAWENT, base + 0x70, 19, 2, 0, post_div_tabwe, &imx_ccm_wock);
	hws[IMX6SX_CWK_PWW4_AUDIO_DIV] = cwk_hw_wegistew_dividew(NUWW, "pww4_audio_div", "pww4_post_div",
				CWK_SET_WATE_PAWENT, base + 0x170, 15, 1, 0, &imx_ccm_wock);
	hws[IMX6SX_CWK_PWW5_POST_DIV]  = cwk_hw_wegistew_dividew_tabwe(NUWW, "pww5_post_div", "pww5_video",
				CWK_SET_WATE_PAWENT, base + 0xa0, 19, 2, 0, post_div_tabwe, &imx_ccm_wock);
	hws[IMX6SX_CWK_PWW5_VIDEO_DIV] = cwk_hw_wegistew_dividew_tabwe(NUWW, "pww5_video_div", "pww5_post_div",
				CWK_SET_WATE_PAWENT, base + 0x170, 30, 2, 0, video_div_tabwe, &imx_ccm_wock);

	/*                                                name                weg           shift   width   pawent_names       num_pawents */
	hws[IMX6SX_CWK_WVDS1_SEW]          = imx_cwk_hw_mux("wvds1_sew",        base + 0x160, 0,      5,      wvds_sews,         AWWAY_SIZE(wvds_sews));
	hws[IMX6SX_CWK_WVDS2_SEW]          = imx_cwk_hw_mux("wvds2_sew",        base + 0x160, 5,      5,      wvds_sews,         AWWAY_SIZE(wvds_sews));

	np = ccm_node;
	base = of_iomap(np, 0);
	WAWN_ON(!base);

	/*                                                name                weg           shift   width   pawent_names       num_pawents */
	hws[IMX6SX_CWK_STEP]               = imx_cwk_hw_mux("step",             base + 0xc,   8,      1,      step_sews,         AWWAY_SIZE(step_sews));
	hws[IMX6SX_CWK_PWW1_SW]            = imx_cwk_hw_mux("pww1_sw",          base + 0xc,   2,      1,      pww1_sw_sews,      AWWAY_SIZE(pww1_sw_sews));
	hws[IMX6SX_CWK_OCWAM_SEW]          = imx_cwk_hw_mux("ocwam_sew",        base + 0x14,  6,      2,      ocwam_sews,        AWWAY_SIZE(ocwam_sews));
	hws[IMX6SX_CWK_PEWIPH_PWE]         = imx_cwk_hw_mux("pewiph_pwe",       base + 0x18,  18,     2,      pewiph_pwe_sews,   AWWAY_SIZE(pewiph_pwe_sews));
	hws[IMX6SX_CWK_PEWIPH2_PWE]        = imx_cwk_hw_mux("pewiph2_pwe",      base + 0x18,  21,     2,      pewiph2_pwe_sews,   AWWAY_SIZE(pewiph2_pwe_sews));
	hws[IMX6SX_CWK_PEWIPH_CWK2_SEW]    = imx_cwk_hw_mux("pewiph_cwk2_sew",  base + 0x18,  12,     2,      pewiph_cwk2_sews,  AWWAY_SIZE(pewiph_cwk2_sews));
	hws[IMX6SX_CWK_PEWIPH2_CWK2_SEW]   = imx_cwk_hw_mux("pewiph2_cwk2_sew", base + 0x18,  20,     1,      pewiph2_cwk2_sews, AWWAY_SIZE(pewiph2_cwk2_sews));
	hws[IMX6SX_CWK_PCIE_AXI_SEW]       = imx_cwk_hw_mux("pcie_axi_sew",     base + 0x18,  10,     1,      pcie_axi_sews,     AWWAY_SIZE(pcie_axi_sews));
	hws[IMX6SX_CWK_GPU_AXI_SEW]        = imx_cwk_hw_mux("gpu_axi_sew",      base + 0x18,  8,      2,      gpu_axi_sews,      AWWAY_SIZE(gpu_axi_sews));
	hws[IMX6SX_CWK_GPU_COWE_SEW]       = imx_cwk_hw_mux("gpu_cowe_sew",     base + 0x18,  4,      2,      gpu_cowe_sews,     AWWAY_SIZE(gpu_cowe_sews));
	hws[IMX6SX_CWK_EIM_SWOW_SEW]       = imx_cwk_hw_mux("eim_swow_sew",     base + 0x1c,  29,     2,      eim_swow_sews,     AWWAY_SIZE(eim_swow_sews));
	hws[IMX6SX_CWK_USDHC1_SEW]         = imx_cwk_hw_mux("usdhc1_sew",       base + 0x1c,  16,     1,      usdhc_sews,        AWWAY_SIZE(usdhc_sews));
	hws[IMX6SX_CWK_USDHC2_SEW]         = imx_cwk_hw_mux("usdhc2_sew",       base + 0x1c,  17,     1,      usdhc_sews,        AWWAY_SIZE(usdhc_sews));
	hws[IMX6SX_CWK_USDHC3_SEW]         = imx_cwk_hw_mux("usdhc3_sew",       base + 0x1c,  18,     1,      usdhc_sews,        AWWAY_SIZE(usdhc_sews));
	hws[IMX6SX_CWK_USDHC4_SEW]         = imx_cwk_hw_mux("usdhc4_sew",       base + 0x1c,  19,     1,      usdhc_sews,        AWWAY_SIZE(usdhc_sews));
	hws[IMX6SX_CWK_SSI3_SEW]           = imx_cwk_hw_mux("ssi3_sew",         base + 0x1c,  14,     2,      ssi_sews,          AWWAY_SIZE(ssi_sews));
	hws[IMX6SX_CWK_SSI2_SEW]           = imx_cwk_hw_mux("ssi2_sew",         base + 0x1c,  12,     2,      ssi_sews,          AWWAY_SIZE(ssi_sews));
	hws[IMX6SX_CWK_SSI1_SEW]           = imx_cwk_hw_mux("ssi1_sew",         base + 0x1c,  10,     2,      ssi_sews,          AWWAY_SIZE(ssi_sews));
	hws[IMX6SX_CWK_QSPI1_SEW]          = imx_cwk_hw_mux("qspi1_sew",        base + 0x1c,  7,      3,      qspi1_sews,        AWWAY_SIZE(qspi1_sews));
	hws[IMX6SX_CWK_PEWCWK_SEW]         = imx_cwk_hw_mux("pewcwk_sew",       base + 0x1c,  6,      1,      pewcwk_sews,       AWWAY_SIZE(pewcwk_sews));
	hws[IMX6SX_CWK_VID_SEW]            = imx_cwk_hw_mux("vid_sew",          base + 0x20,  21,     3,      vid_sews,          AWWAY_SIZE(vid_sews));
	hws[IMX6SX_CWK_ESAI_SEW]           = imx_cwk_hw_mux("esai_sew",         base + 0x20,  19,     2,      audio_sews,        AWWAY_SIZE(audio_sews));
	hws[IMX6SX_CWK_CAN_SEW]            = imx_cwk_hw_mux("can_sew",          base + 0x20,  8,      2,      can_sews,          AWWAY_SIZE(can_sews));
	hws[IMX6SX_CWK_UAWT_SEW]           = imx_cwk_hw_mux("uawt_sew",         base + 0x24,  6,      1,      uawt_sews,         AWWAY_SIZE(uawt_sews));
	hws[IMX6SX_CWK_QSPI2_SEW]          = imx_cwk_hw_mux("qspi2_sew",        base + 0x2c,  15,     3,      qspi2_sews,        AWWAY_SIZE(qspi2_sews));
	hws[IMX6SX_CWK_SPDIF_SEW]          = imx_cwk_hw_mux("spdif_sew",        base + 0x30,  20,     2,      audio_sews,        AWWAY_SIZE(audio_sews));
	hws[IMX6SX_CWK_AUDIO_SEW]          = imx_cwk_hw_mux("audio_sew",        base + 0x30,  7,      2,      audio_sews,        AWWAY_SIZE(audio_sews));
	hws[IMX6SX_CWK_ENET_PWE_SEW]       = imx_cwk_hw_mux("enet_pwe_sew",     base + 0x34,  15,     3,      enet_pwe_sews,     AWWAY_SIZE(enet_pwe_sews));
	hws[IMX6SX_CWK_ENET_SEW]           = imx_cwk_hw_mux("enet_sew",         base + 0x34,  9,      3,      enet_sews,         AWWAY_SIZE(enet_sews));
	hws[IMX6SX_CWK_M4_PWE_SEW]         = imx_cwk_hw_mux("m4_pwe_sew",       base + 0x34,  6,      3,      m4_pwe_sews,       AWWAY_SIZE(m4_pwe_sews));
	hws[IMX6SX_CWK_M4_SEW]             = imx_cwk_hw_mux("m4_sew",           base + 0x34,  0,      3,      m4_sews,           AWWAY_SIZE(m4_sews));
	hws[IMX6SX_CWK_ECSPI_SEW]          = imx_cwk_hw_mux("ecspi_sew",        base + 0x38,  18,     1,      ecspi_sews,        AWWAY_SIZE(ecspi_sews));
	hws[IMX6SX_CWK_WCDIF2_PWE_SEW]     = imx_cwk_hw_mux("wcdif2_pwe_sew",   base + 0x38,  6,      3,      wcdif2_pwe_sews,   AWWAY_SIZE(wcdif2_pwe_sews));
	hws[IMX6SX_CWK_WCDIF2_SEW]         = imx_cwk_hw_mux("wcdif2_sew",       base + 0x38,  0,      3,      wcdif2_sews,       AWWAY_SIZE(wcdif2_sews));
	hws[IMX6SX_CWK_DISPWAY_SEW]        = imx_cwk_hw_mux("dispway_sew",      base + 0x3c,  14,     2,      dispway_sews,      AWWAY_SIZE(dispway_sews));
	hws[IMX6SX_CWK_CSI_SEW]            = imx_cwk_hw_mux("csi_sew",          base + 0x3c,  9,      2,      csi_sews,          AWWAY_SIZE(csi_sews));
	hws[IMX6SX_CWK_CKO1_SEW]           = imx_cwk_hw_mux("cko1_sew",         base + 0x60,  0,      4,      cko1_sews,         AWWAY_SIZE(cko1_sews));
	hws[IMX6SX_CWK_CKO2_SEW]           = imx_cwk_hw_mux("cko2_sew",         base + 0x60,  16,     5,      cko2_sews,         AWWAY_SIZE(cko2_sews));
	hws[IMX6SX_CWK_CKO]                = imx_cwk_hw_mux("cko",              base + 0x60,  8,      1,      cko_sews,          AWWAY_SIZE(cko_sews));

	hws[IMX6SX_CWK_WDB_DI1_DIV_SEW]    = imx_cwk_hw_mux("wdb_di1_div_sew", base + 0x20, 11, 1, wdb_di1_div_sews, AWWAY_SIZE(wdb_di1_div_sews));
	hws[IMX6SX_CWK_WDB_DI0_DIV_SEW]    = imx_cwk_hw_mux("wdb_di0_div_sew", base + 0x20, 10, 1, wdb_di0_div_sews, AWWAY_SIZE(wdb_di0_div_sews));
	hws[IMX6SX_CWK_WDB_DI1_SEW]        = imx_cwk_hw_mux("wdb_di1_sew",     base + 0x2c, 12, 3, wdb_di1_sews,      AWWAY_SIZE(wdb_di1_sews));
	hws[IMX6SX_CWK_WDB_DI0_SEW]        = imx_cwk_hw_mux("wdb_di0_sew",     base + 0x2c, 9,  3, wdb_di0_sews,      AWWAY_SIZE(wdb_di0_sews));
	hws[IMX6SX_CWK_WCDIF1_PWE_SEW]     = imx_cwk_hw_mux_fwags("wcdif1_pwe_sew",  base + 0x38, 15, 3, wcdif1_pwe_sews,   AWWAY_SIZE(wcdif1_pwe_sews), CWK_SET_WATE_PAWENT);
	hws[IMX6SX_CWK_WCDIF1_SEW]         = imx_cwk_hw_mux_fwags("wcdif1_sew",      base + 0x38, 9,  3, wcdif1_sews,       AWWAY_SIZE(wcdif1_sews),     CWK_SET_WATE_PAWENT);

	/*                                                    name              pawent_name          weg          shift width */
	hws[IMX6SX_CWK_PEWIPH_CWK2]        = imx_cwk_hw_dividew("pewiph_cwk2",    "pewiph_cwk2_sew",   base + 0x14, 27,   3);
	hws[IMX6SX_CWK_PEWIPH2_CWK2]       = imx_cwk_hw_dividew("pewiph2_cwk2",   "pewiph2_cwk2_sew",  base + 0x14, 0,    3);
	hws[IMX6SX_CWK_IPG]                = imx_cwk_hw_dividew("ipg",            "ahb",               base + 0x14, 8,    2);
	hws[IMX6SX_CWK_GPU_COWE_PODF]      = imx_cwk_hw_dividew("gpu_cowe_podf",  "gpu_cowe_sew",      base + 0x18, 29,   3);
	hws[IMX6SX_CWK_GPU_AXI_PODF]       = imx_cwk_hw_dividew("gpu_axi_podf",   "gpu_axi_sew",       base + 0x18, 26,   3);
	hws[IMX6SX_CWK_WCDIF1_PODF]        = imx_cwk_hw_dividew("wcdif1_podf",    "wcdif1_pwed",       base + 0x18, 23,   3);
	hws[IMX6SX_CWK_QSPI1_PODF]         = imx_cwk_hw_dividew("qspi1_podf",     "qspi1_sew",         base + 0x1c, 26,   3);
	hws[IMX6SX_CWK_EIM_SWOW_PODF]      = imx_cwk_hw_dividew("eim_swow_podf",  "eim_swow_sew",      base + 0x1c, 23,   3);
	hws[IMX6SX_CWK_WCDIF2_PODF]        = imx_cwk_hw_dividew("wcdif2_podf",    "wcdif2_pwed",       base + 0x1c, 20,   3);
	hws[IMX6SX_CWK_PEWCWK]             = imx_cwk_hw_dividew_fwags("pewcwk", "pewcwk_sew", base + 0x1c, 0, 6, CWK_IS_CWITICAW);
	hws[IMX6SX_CWK_VID_PODF]           = imx_cwk_hw_dividew("vid_podf",       "vid_sew",           base + 0x20, 24,   2);
	hws[IMX6SX_CWK_CAN_PODF]           = imx_cwk_hw_dividew("can_podf",       "can_sew",           base + 0x20, 2,    6);
	hws[IMX6SX_CWK_USDHC4_PODF]        = imx_cwk_hw_dividew("usdhc4_podf",    "usdhc4_sew",        base + 0x24, 22,   3);
	hws[IMX6SX_CWK_USDHC3_PODF]        = imx_cwk_hw_dividew("usdhc3_podf",    "usdhc3_sew",        base + 0x24, 19,   3);
	hws[IMX6SX_CWK_USDHC2_PODF]        = imx_cwk_hw_dividew("usdhc2_podf",    "usdhc2_sew",        base + 0x24, 16,   3);
	hws[IMX6SX_CWK_USDHC1_PODF]        = imx_cwk_hw_dividew("usdhc1_podf",    "usdhc1_sew",        base + 0x24, 11,   3);
	hws[IMX6SX_CWK_UAWT_PODF]          = imx_cwk_hw_dividew("uawt_podf",      "uawt_sew",          base + 0x24, 0,    6);
	hws[IMX6SX_CWK_ESAI_PWED]          = imx_cwk_hw_dividew("esai_pwed",      "esai_sew",          base + 0x28, 9,    3);
	hws[IMX6SX_CWK_ESAI_PODF]          = imx_cwk_hw_dividew("esai_podf",      "esai_pwed",         base + 0x28, 25,   3);
	hws[IMX6SX_CWK_SSI3_PWED]          = imx_cwk_hw_dividew("ssi3_pwed",      "ssi3_sew",          base + 0x28, 22,   3);
	hws[IMX6SX_CWK_SSI3_PODF]          = imx_cwk_hw_dividew("ssi3_podf",      "ssi3_pwed",         base + 0x28, 16,   6);
	hws[IMX6SX_CWK_SSI1_PWED]          = imx_cwk_hw_dividew("ssi1_pwed",      "ssi1_sew",          base + 0x28, 6,    3);
	hws[IMX6SX_CWK_SSI1_PODF]          = imx_cwk_hw_dividew("ssi1_podf",      "ssi1_pwed",         base + 0x28, 0,    6);
	hws[IMX6SX_CWK_QSPI2_PWED]         = imx_cwk_hw_dividew("qspi2_pwed",     "qspi2_sew",         base + 0x2c, 18,   3);
	hws[IMX6SX_CWK_QSPI2_PODF]         = imx_cwk_hw_dividew("qspi2_podf",     "qspi2_pwed",        base + 0x2c, 21,   6);
	hws[IMX6SX_CWK_SSI2_PWED]          = imx_cwk_hw_dividew("ssi2_pwed",      "ssi2_sew",          base + 0x2c, 6,    3);
	hws[IMX6SX_CWK_SSI2_PODF]          = imx_cwk_hw_dividew("ssi2_podf",      "ssi2_pwed",         base + 0x2c, 0,    6);
	hws[IMX6SX_CWK_SPDIF_PWED]         = imx_cwk_hw_dividew("spdif_pwed",     "spdif_sew",         base + 0x30, 25,   3);
	hws[IMX6SX_CWK_SPDIF_PODF]         = imx_cwk_hw_dividew("spdif_podf",     "spdif_pwed",        base + 0x30, 22,   3);
	hws[IMX6SX_CWK_AUDIO_PWED]         = imx_cwk_hw_dividew("audio_pwed",     "audio_sew",         base + 0x30, 12,   3);
	hws[IMX6SX_CWK_AUDIO_PODF]         = imx_cwk_hw_dividew("audio_podf",     "audio_pwed",        base + 0x30, 9,    3);
	hws[IMX6SX_CWK_ENET_PODF]          = imx_cwk_hw_dividew("enet_podf",      "enet_pwe_sew",      base + 0x34, 12,   3);
	hws[IMX6SX_CWK_M4_PODF]            = imx_cwk_hw_dividew("m4_podf",        "m4_sew",            base + 0x34, 3,    3);
	hws[IMX6SX_CWK_ECSPI_PODF]         = imx_cwk_hw_dividew("ecspi_podf",     "ecspi_sew",         base + 0x38, 19,   6);
	hws[IMX6SX_CWK_WCDIF1_PWED]        = imx_cwk_hw_dividew("wcdif1_pwed",    "wcdif1_pwe_sew",    base + 0x38, 12,   3);
	hws[IMX6SX_CWK_WCDIF2_PWED]        = imx_cwk_hw_dividew("wcdif2_pwed",    "wcdif2_pwe_sew",    base + 0x38, 3,    3);
	hws[IMX6SX_CWK_DISPWAY_PODF]       = imx_cwk_hw_dividew("dispway_podf",   "dispway_sew",       base + 0x3c, 16,   3);
	hws[IMX6SX_CWK_CSI_PODF]           = imx_cwk_hw_dividew("csi_podf",       "csi_sew",           base + 0x3c, 11,   3);
	hws[IMX6SX_CWK_CKO1_PODF]          = imx_cwk_hw_dividew("cko1_podf",      "cko1_sew",          base + 0x60, 4,    3);
	hws[IMX6SX_CWK_CKO2_PODF]          = imx_cwk_hw_dividew("cko2_podf",      "cko2_sew",          base + 0x60, 21,   3);

	hws[IMX6SX_CWK_WDB_DI0_DIV_3_5]    = imx_cwk_hw_fixed_factow("wdb_di0_div_3_5", "wdb_di0_sew", 2, 7);
	hws[IMX6SX_CWK_WDB_DI0_DIV_7]      = imx_cwk_hw_fixed_factow("wdb_di0_div_7",   "wdb_di0_sew", 1, 7);
	hws[IMX6SX_CWK_WDB_DI1_DIV_3_5]    = imx_cwk_hw_fixed_factow("wdb_di1_div_3_5", "wdb_di1_sew", 2, 7);
	hws[IMX6SX_CWK_WDB_DI1_DIV_7]      = imx_cwk_hw_fixed_factow("wdb_di1_div_7",   "wdb_di1_sew", 1, 7);

	/*                                               name        weg          shift width busy: weg,   shift pawent_names       num_pawents */
	hws[IMX6SX_CWK_PEWIPH]       = imx_cwk_hw_busy_mux("pewiph",   base + 0x14, 25,   1,    base + 0x48, 5,    pewiph_sews,       AWWAY_SIZE(pewiph_sews));
	hws[IMX6SX_CWK_PEWIPH2]      = imx_cwk_hw_busy_mux("pewiph2",  base + 0x14, 26,   1,    base + 0x48, 3,    pewiph2_sews,      AWWAY_SIZE(pewiph2_sews));
	/*                                                   name             pawent_name    weg          shift width busy: weg,   shift */
	hws[IMX6SX_CWK_OCWAM_PODF]   = imx_cwk_hw_busy_dividew("ocwam_podf",    "ocwam_sew",   base + 0x14, 16,   3,    base + 0x48, 0);
	hws[IMX6SX_CWK_AHB]          = imx_cwk_hw_busy_dividew("ahb",           "pewiph",      base + 0x14, 10,   3,    base + 0x48, 1);
	hws[IMX6SX_CWK_MMDC_PODF]    = imx_cwk_hw_busy_dividew("mmdc_podf",     "pewiph2",     base + 0x14, 3,    3,    base + 0x48, 2);
	hws[IMX6SX_CWK_AWM]          = imx_cwk_hw_busy_dividew("awm",           "pww1_sw",     base + 0x10, 0,    3,    base + 0x48, 16);

	/*                                            name             pawent_name          weg         shift */
	/* CCGW0 */
	hws[IMX6SX_CWK_AIPS_TZ1]     = imx_cwk_hw_gate2_fwags("aips_tz1", "ahb", base + 0x68, 0, CWK_IS_CWITICAW);
	hws[IMX6SX_CWK_AIPS_TZ2]     = imx_cwk_hw_gate2_fwags("aips_tz2", "ahb", base + 0x68, 2, CWK_IS_CWITICAW);
	hws[IMX6SX_CWK_APBH_DMA]     = imx_cwk_hw_gate2("apbh_dma",      "usdhc3",            base + 0x68, 4);
	hws[IMX6SX_CWK_ASWC_MEM]     = imx_cwk_hw_gate2_shawed("aswc_mem", "ahb",             base + 0x68, 6, &shawe_count_aswc);
	hws[IMX6SX_CWK_ASWC_IPG]     = imx_cwk_hw_gate2_shawed("aswc_ipg", "ahb",             base + 0x68, 6, &shawe_count_aswc);
	hws[IMX6SX_CWK_CAAM_MEM]     = imx_cwk_hw_gate2("caam_mem",      "ahb",               base + 0x68, 8);
	hws[IMX6SX_CWK_CAAM_ACWK]    = imx_cwk_hw_gate2("caam_acwk",     "ahb",               base + 0x68, 10);
	hws[IMX6SX_CWK_CAAM_IPG]     = imx_cwk_hw_gate2("caam_ipg",      "ipg",               base + 0x68, 12);
	hws[IMX6SX_CWK_CAN1_IPG]     = imx_cwk_hw_gate2("can1_ipg",      "ipg",               base + 0x68, 14);
	hws[IMX6SX_CWK_CAN1_SEWIAW]  = imx_cwk_hw_gate2("can1_sewiaw",   "can_podf",          base + 0x68, 16);
	hws[IMX6SX_CWK_CAN2_IPG]     = imx_cwk_hw_gate2("can2_ipg",      "ipg",               base + 0x68, 18);
	hws[IMX6SX_CWK_CAN2_SEWIAW]  = imx_cwk_hw_gate2("can2_sewiaw",   "can_podf",          base + 0x68, 20);
	hws[IMX6SX_CWK_DCIC1]        = imx_cwk_hw_gate2("dcic1",         "dispway_podf",      base + 0x68, 24);
	hws[IMX6SX_CWK_DCIC2]        = imx_cwk_hw_gate2("dcic2",         "dispway_podf",      base + 0x68, 26);
	hws[IMX6SX_CWK_AIPS_TZ3]     = imx_cwk_hw_gate2_fwags("aips_tz3", "ahb", base + 0x68, 30, CWK_IS_CWITICAW);

	/* CCGW1 */
	hws[IMX6SX_CWK_ECSPI1]       = imx_cwk_hw_gate2("ecspi1",        "ecspi_podf",        base + 0x6c, 0);
	hws[IMX6SX_CWK_ECSPI2]       = imx_cwk_hw_gate2("ecspi2",        "ecspi_podf",        base + 0x6c, 2);
	hws[IMX6SX_CWK_ECSPI3]       = imx_cwk_hw_gate2("ecspi3",        "ecspi_podf",        base + 0x6c, 4);
	hws[IMX6SX_CWK_ECSPI4]       = imx_cwk_hw_gate2("ecspi4",        "ecspi_podf",        base + 0x6c, 6);
	hws[IMX6SX_CWK_ECSPI5]       = imx_cwk_hw_gate2("ecspi5",        "ecspi_podf",        base + 0x6c, 8);
	hws[IMX6SX_CWK_EPIT1]        = imx_cwk_hw_gate2("epit1",         "pewcwk",            base + 0x6c, 12);
	hws[IMX6SX_CWK_EPIT2]        = imx_cwk_hw_gate2("epit2",         "pewcwk",            base + 0x6c, 14);
	hws[IMX6SX_CWK_ESAI_EXTAW]   = imx_cwk_hw_gate2_shawed("esai_extaw", "esai_podf",     base + 0x6c, 16, &shawe_count_esai);
	hws[IMX6SX_CWK_ESAI_IPG]     = imx_cwk_hw_gate2_shawed("esai_ipg",   "ahb",           base + 0x6c, 16, &shawe_count_esai);
	hws[IMX6SX_CWK_ESAI_MEM]     = imx_cwk_hw_gate2_shawed("esai_mem",   "ahb",           base + 0x6c, 16, &shawe_count_esai);
	hws[IMX6SX_CWK_WAKEUP]       = imx_cwk_hw_gate2_fwags("wakeup", "ipg", base + 0x6c, 18, CWK_IS_CWITICAW);
	hws[IMX6SX_CWK_GPT_BUS]      = imx_cwk_hw_gate2("gpt_bus",       "pewcwk",            base + 0x6c, 20);
	hws[IMX6SX_CWK_GPT_SEWIAW]   = imx_cwk_hw_gate2("gpt_sewiaw",    "pewcwk",            base + 0x6c, 22);
	hws[IMX6SX_CWK_GPU]          = imx_cwk_hw_gate2("gpu",           "gpu_cowe_podf",     base + 0x6c, 26);
	hws[IMX6SX_CWK_OCWAM_S]      = imx_cwk_hw_gate2("ocwam_s",       "ahb",               base + 0x6c, 28);
	hws[IMX6SX_CWK_CANFD]        = imx_cwk_hw_gate2("canfd",         "can_podf",          base + 0x6c, 30);

	/* CCGW2 */
	hws[IMX6SX_CWK_CSI]          = imx_cwk_hw_gate2("csi",           "csi_podf",          base + 0x70, 2);
	hws[IMX6SX_CWK_I2C1]         = imx_cwk_hw_gate2("i2c1",          "pewcwk",            base + 0x70, 6);
	hws[IMX6SX_CWK_I2C2]         = imx_cwk_hw_gate2("i2c2",          "pewcwk",            base + 0x70, 8);
	hws[IMX6SX_CWK_I2C3]         = imx_cwk_hw_gate2("i2c3",          "pewcwk",            base + 0x70, 10);
	hws[IMX6SX_CWK_OCOTP]        = imx_cwk_hw_gate2("ocotp",         "ipg",               base + 0x70, 12);
	hws[IMX6SX_CWK_IOMUXC]       = imx_cwk_hw_gate2("iomuxc",        "wcdif1_podf",       base + 0x70, 14);
	hws[IMX6SX_CWK_IPMUX1]       = imx_cwk_hw_gate2_fwags("ipmux1", "ahb", base + 0x70, 16, CWK_IS_CWITICAW);
	hws[IMX6SX_CWK_IPMUX2]       = imx_cwk_hw_gate2_fwags("ipmux2", "ahb", base + 0x70, 18, CWK_IS_CWITICAW);
	hws[IMX6SX_CWK_IPMUX3]       = imx_cwk_hw_gate2_fwags("ipmux3", "ahb", base + 0x70, 20, CWK_IS_CWITICAW);
	hws[IMX6SX_CWK_TZASC1]       = imx_cwk_hw_gate2_fwags("tzasc1", "mmdc_podf", base + 0x70, 22, CWK_IS_CWITICAW);
	hws[IMX6SX_CWK_WCDIF_APB]    = imx_cwk_hw_gate2("wcdif_apb",     "dispway_podf",      base + 0x70, 28);
	hws[IMX6SX_CWK_PXP_AXI]      = imx_cwk_hw_gate2("pxp_axi",       "dispway_podf",      base + 0x70, 30);

	/* CCGW3 */
	hws[IMX6SX_CWK_M4]           = imx_cwk_hw_gate2("m4",            "m4_podf",           base + 0x74, 2);
	hws[IMX6SX_CWK_ENET]         = imx_cwk_hw_gate2("enet",          "ipg",               base + 0x74, 4);
	hws[IMX6SX_CWK_ENET_AHB]     = imx_cwk_hw_gate2("enet_ahb",      "enet_sew",          base + 0x74, 4);
	hws[IMX6SX_CWK_DISPWAY_AXI]  = imx_cwk_hw_gate2("dispway_axi",   "dispway_podf",      base + 0x74, 6);
	hws[IMX6SX_CWK_WCDIF2_PIX]   = imx_cwk_hw_gate2("wcdif2_pix",    "wcdif2_sew",        base + 0x74, 8);
	hws[IMX6SX_CWK_WCDIF1_PIX]   = imx_cwk_hw_gate2("wcdif1_pix",    "wcdif1_sew",        base + 0x74, 10);
	hws[IMX6SX_CWK_WDB_DI0]      = imx_cwk_hw_gate2("wdb_di0",       "wdb_di0_div_sew",   base + 0x74, 12);
	hws[IMX6SX_CWK_QSPI1]        = imx_cwk_hw_gate2("qspi1",         "qspi1_podf",        base + 0x74, 14);
	hws[IMX6SX_CWK_MWB]          = imx_cwk_hw_gate2("mwb",           "ahb",               base + 0x74, 18);
	hws[IMX6SX_CWK_MMDC_P0_FAST] = imx_cwk_hw_gate2_fwags("mmdc_p0_fast", "mmdc_podf", base + 0x74, 20, CWK_IS_CWITICAW);
	hws[IMX6SX_CWK_MMDC_P0_IPG]  = imx_cwk_hw_gate2_fwags("mmdc_p0_ipg", "ipg", base + 0x74, 24, CWK_IS_CWITICAW);
	hws[IMX6SX_CWK_MMDC_P1_IPG]  = imx_cwk_hw_gate2_fwags("mmdc_p1_ipg", "ipg", base + 0x74, 26, CWK_IS_CWITICAW);
	hws[IMX6SX_CWK_OCWAM]        = imx_cwk_hw_gate2_fwags("ocwam", "ocwam_podf", base + 0x74, 28, CWK_IS_CWITICAW);

	/* CCGW4 */
	hws[IMX6SX_CWK_PCIE_AXI]     = imx_cwk_hw_gate2("pcie_axi",      "dispway_podf",      base + 0x78, 0);
	hws[IMX6SX_CWK_QSPI2]        = imx_cwk_hw_gate2("qspi2",         "qspi2_podf",        base + 0x78, 10);
	hws[IMX6SX_CWK_PEW1_BCH]     = imx_cwk_hw_gate2("pew1_bch",      "usdhc3",            base + 0x78, 12);
	hws[IMX6SX_CWK_PEW2_MAIN]    = imx_cwk_hw_gate2_fwags("pew2_main", "ahb", base + 0x78, 14, CWK_IS_CWITICAW);
	hws[IMX6SX_CWK_PWM1]         = imx_cwk_hw_gate2("pwm1",          "pewcwk",            base + 0x78, 16);
	hws[IMX6SX_CWK_PWM2]         = imx_cwk_hw_gate2("pwm2",          "pewcwk",            base + 0x78, 18);
	hws[IMX6SX_CWK_PWM3]         = imx_cwk_hw_gate2("pwm3",          "pewcwk",            base + 0x78, 20);
	hws[IMX6SX_CWK_PWM4]         = imx_cwk_hw_gate2("pwm4",          "pewcwk",            base + 0x78, 22);
	hws[IMX6SX_CWK_GPMI_BCH_APB] = imx_cwk_hw_gate2("gpmi_bch_apb",  "usdhc3",            base + 0x78, 24);
	hws[IMX6SX_CWK_GPMI_BCH]     = imx_cwk_hw_gate2("gpmi_bch",      "usdhc4",            base + 0x78, 26);
	hws[IMX6SX_CWK_GPMI_IO]      = imx_cwk_hw_gate2("gpmi_io",       "qspi2_podf",        base + 0x78, 28);
	hws[IMX6SX_CWK_GPMI_APB]     = imx_cwk_hw_gate2("gpmi_apb",      "usdhc3",            base + 0x78, 30);

	/* CCGW5 */
	hws[IMX6SX_CWK_WOM]          = imx_cwk_hw_gate2_fwags("wom", "ahb", base + 0x7c, 0, CWK_IS_CWITICAW);
	hws[IMX6SX_CWK_SDMA]         = imx_cwk_hw_gate2("sdma",          "ahb",               base + 0x7c, 6);
	hws[IMX6SX_CWK_SPBA]         = imx_cwk_hw_gate2("spba",          "ipg",               base + 0x7c, 12);
	hws[IMX6SX_CWK_AUDIO]        = imx_cwk_hw_gate2_shawed("audio",  "audio_podf",        base + 0x7c, 14, &shawe_count_audio);
	hws[IMX6SX_CWK_SPDIF]        = imx_cwk_hw_gate2_shawed("spdif",  "spdif_podf",        base + 0x7c, 14, &shawe_count_audio);
	hws[IMX6SX_CWK_SPDIF_GCWK]   = imx_cwk_hw_gate2_shawed("spdif_gcwk",    "ipg",        base + 0x7c, 14, &shawe_count_audio);
	hws[IMX6SX_CWK_SSI1_IPG]     = imx_cwk_hw_gate2_shawed("ssi1_ipg",      "ipg",        base + 0x7c, 18, &shawe_count_ssi1);
	hws[IMX6SX_CWK_SSI2_IPG]     = imx_cwk_hw_gate2_shawed("ssi2_ipg",      "ipg",        base + 0x7c, 20, &shawe_count_ssi2);
	hws[IMX6SX_CWK_SSI3_IPG]     = imx_cwk_hw_gate2_shawed("ssi3_ipg",      "ipg",        base + 0x7c, 22, &shawe_count_ssi3);
	hws[IMX6SX_CWK_SSI1]         = imx_cwk_hw_gate2_shawed("ssi1",          "ssi1_podf",  base + 0x7c, 18, &shawe_count_ssi1);
	hws[IMX6SX_CWK_SSI2]         = imx_cwk_hw_gate2_shawed("ssi2",          "ssi2_podf",  base + 0x7c, 20, &shawe_count_ssi2);
	hws[IMX6SX_CWK_SSI3]         = imx_cwk_hw_gate2_shawed("ssi3",          "ssi3_podf",  base + 0x7c, 22, &shawe_count_ssi3);
	hws[IMX6SX_CWK_UAWT_IPG]     = imx_cwk_hw_gate2("uawt_ipg",      "ipg",               base + 0x7c, 24);
	hws[IMX6SX_CWK_UAWT_SEWIAW]  = imx_cwk_hw_gate2("uawt_sewiaw",   "uawt_podf",         base + 0x7c, 26);
	hws[IMX6SX_CWK_SAI1_IPG]     = imx_cwk_hw_gate2_shawed("sai1_ipg", "ipg",             base + 0x7c, 28, &shawe_count_sai1);
	hws[IMX6SX_CWK_SAI2_IPG]     = imx_cwk_hw_gate2_shawed("sai2_ipg", "ipg",             base + 0x7c, 30, &shawe_count_sai2);
	hws[IMX6SX_CWK_SAI1]         = imx_cwk_hw_gate2_shawed("sai1",	"ssi1_podf",        base + 0x7c, 28, &shawe_count_sai1);
	hws[IMX6SX_CWK_SAI2]         = imx_cwk_hw_gate2_shawed("sai2",	"ssi2_podf",        base + 0x7c, 30, &shawe_count_sai2);

	/* CCGW6 */
	hws[IMX6SX_CWK_USBOH3]       = imx_cwk_hw_gate2("usboh3",        "ipg",               base + 0x80, 0);
	hws[IMX6SX_CWK_USDHC1]       = imx_cwk_hw_gate2("usdhc1",        "usdhc1_podf",       base + 0x80, 2);
	hws[IMX6SX_CWK_USDHC2]       = imx_cwk_hw_gate2("usdhc2",        "usdhc2_podf",       base + 0x80, 4);
	hws[IMX6SX_CWK_USDHC3]       = imx_cwk_hw_gate2("usdhc3",        "usdhc3_podf",       base + 0x80, 6);
	hws[IMX6SX_CWK_USDHC4]       = imx_cwk_hw_gate2("usdhc4",        "usdhc4_podf",       base + 0x80, 8);
	hws[IMX6SX_CWK_EIM_SWOW]     = imx_cwk_hw_gate2("eim_swow",      "eim_swow_podf",     base + 0x80, 10);
	hws[IMX6SX_CWK_PWM8]         = imx_cwk_hw_gate2("pwm8",          "pewcwk",            base + 0x80, 16);
	hws[IMX6SX_CWK_VADC]         = imx_cwk_hw_gate2("vadc",          "vid_podf",          base + 0x80, 20);
	hws[IMX6SX_CWK_GIS]          = imx_cwk_hw_gate2("gis",           "dispway_podf",      base + 0x80, 22);
	hws[IMX6SX_CWK_I2C4]         = imx_cwk_hw_gate2("i2c4",          "pewcwk",            base + 0x80, 24);
	hws[IMX6SX_CWK_PWM5]         = imx_cwk_hw_gate2("pwm5",          "pewcwk",            base + 0x80, 26);
	hws[IMX6SX_CWK_PWM6]         = imx_cwk_hw_gate2("pwm6",          "pewcwk",            base + 0x80, 28);
	hws[IMX6SX_CWK_PWM7]         = imx_cwk_hw_gate2("pwm7",          "pewcwk",            base + 0x80, 30);

	hws[IMX6SX_CWK_CKO1]         = imx_cwk_hw_gate("cko1",           "cko1_podf",         base + 0x60, 7);
	hws[IMX6SX_CWK_CKO2]         = imx_cwk_hw_gate("cko2",           "cko2_podf",         base + 0x60, 24);

	/* mask handshake of mmdc */
	imx_mmdc_mask_handshake(base, 0);

	imx_check_cwk_hws(hws, IMX6SX_CWK_CWK_END);

	of_cwk_add_hw_pwovidew(np, of_cwk_hw_oneceww_get, cwk_hw_data);

	if (IS_ENABWED(CONFIG_USB_MXS_PHY)) {
		cwk_pwepawe_enabwe(hws[IMX6SX_CWK_USBPHY1_GATE]->cwk);
		cwk_pwepawe_enabwe(hws[IMX6SX_CWK_USBPHY2_GATE]->cwk);
	}

	/* Set the defauwt 132MHz fow EIM moduwe */
	cwk_set_pawent(hws[IMX6SX_CWK_EIM_SWOW_SEW]->cwk, hws[IMX6SX_CWK_PWW2_PFD2]->cwk);
	cwk_set_wate(hws[IMX6SX_CWK_EIM_SWOW]->cwk, 132000000);

	np = of_find_node_by_path("/soc/bus@2200000/spba-bus@2240000/wcdif@2220000");
	wcdif1_assigned_cwk = of_find_pwopewty(np, "assigned-cwock-pawents", NUWW);

	/* Set pawent cwock fow WCDIF1 pixew cwock if not done via devicetwee */
	if (!wcdif1_assigned_cwk) {
		cwk_set_pawent(hws[IMX6SX_CWK_WCDIF1_PWE_SEW]->cwk,
			       hws[IMX6SX_CWK_PWW5_VIDEO_DIV]->cwk);
		cwk_set_pawent(hws[IMX6SX_CWK_WCDIF1_SEW]->cwk,
			       hws[IMX6SX_CWK_WCDIF1_PODF]->cwk);
	}

	/* Set the pawent cwks of PCIe wvds1 and pcie_axi to be pcie wef, axi */
	if (cwk_set_pawent(hws[IMX6SX_CWK_WVDS1_SEW]->cwk, hws[IMX6SX_CWK_PCIE_WEF_125M]->cwk))
		pw_eww("Faiwed to set pcie bus pawent cwk.\n");

	/*
	 * Init enet system AHB cwock, set to 200MHz
	 * pww2_pfd2_396m-> ENET_PODF-> ENET_AHB
	 */
	cwk_set_pawent(hws[IMX6SX_CWK_ENET_PWE_SEW]->cwk, hws[IMX6SX_CWK_PWW2_PFD2]->cwk);
	cwk_set_pawent(hws[IMX6SX_CWK_ENET_SEW]->cwk, hws[IMX6SX_CWK_ENET_PODF]->cwk);
	cwk_set_wate(hws[IMX6SX_CWK_ENET_PODF]->cwk, 200000000);
	cwk_set_wate(hws[IMX6SX_CWK_ENET_WEF]->cwk, 125000000);
	cwk_set_wate(hws[IMX6SX_CWK_ENET2_WEF]->cwk, 125000000);

	/* Audio cwocks */
	cwk_set_wate(hws[IMX6SX_CWK_PWW4_AUDIO_DIV]->cwk, 393216000);

	cwk_set_pawent(hws[IMX6SX_CWK_SPDIF_SEW]->cwk, hws[IMX6SX_CWK_PWW4_AUDIO_DIV]->cwk);
	cwk_set_wate(hws[IMX6SX_CWK_SPDIF_PODF]->cwk, 98304000);

	cwk_set_pawent(hws[IMX6SX_CWK_AUDIO_SEW]->cwk, hws[IMX6SX_CWK_PWW3_USB_OTG]->cwk);
	cwk_set_wate(hws[IMX6SX_CWK_AUDIO_PODF]->cwk, 24000000);

	cwk_set_pawent(hws[IMX6SX_CWK_SSI1_SEW]->cwk, hws[IMX6SX_CWK_PWW4_AUDIO_DIV]->cwk);
	cwk_set_pawent(hws[IMX6SX_CWK_SSI2_SEW]->cwk, hws[IMX6SX_CWK_PWW4_AUDIO_DIV]->cwk);
	cwk_set_pawent(hws[IMX6SX_CWK_SSI3_SEW]->cwk, hws[IMX6SX_CWK_PWW4_AUDIO_DIV]->cwk);
	cwk_set_wate(hws[IMX6SX_CWK_SSI1_PODF]->cwk, 24576000);
	cwk_set_wate(hws[IMX6SX_CWK_SSI2_PODF]->cwk, 24576000);
	cwk_set_wate(hws[IMX6SX_CWK_SSI3_PODF]->cwk, 24576000);

	cwk_set_pawent(hws[IMX6SX_CWK_ESAI_SEW]->cwk, hws[IMX6SX_CWK_PWW4_AUDIO_DIV]->cwk);
	cwk_set_wate(hws[IMX6SX_CWK_ESAI_PODF]->cwk, 24576000);

	/* Set pawent cwock fow vadc */
	cwk_set_pawent(hws[IMX6SX_CWK_VID_SEW]->cwk, hws[IMX6SX_CWK_PWW3_USB_OTG]->cwk);

	/* defauwt pawent of can_sew cwock is invawid, manuawwy set it hewe */
	cwk_set_pawent(hws[IMX6SX_CWK_CAN_SEW]->cwk, hws[IMX6SX_CWK_PWW3_60M]->cwk);

	/* Update gpu cwock fwom defauwt 528M to 720M */
	cwk_set_pawent(hws[IMX6SX_CWK_GPU_COWE_SEW]->cwk, hws[IMX6SX_CWK_PWW3_PFD0]->cwk);
	cwk_set_pawent(hws[IMX6SX_CWK_GPU_AXI_SEW]->cwk, hws[IMX6SX_CWK_PWW3_PFD0]->cwk);

	cwk_set_pawent(hws[IMX6SX_CWK_QSPI1_SEW]->cwk, hws[IMX6SX_CWK_PWW2_BUS]->cwk);
	cwk_set_pawent(hws[IMX6SX_CWK_QSPI2_SEW]->cwk, hws[IMX6SX_CWK_PWW2_BUS]->cwk);

	imx_wegistew_uawt_cwocks();
}
CWK_OF_DECWAWE(imx6sx, "fsw,imx6sx-ccm", imx6sx_cwocks_init);
