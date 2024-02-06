// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014 MediaTek Inc.
 * Authow: Shunwi Wang <shunwi.wang@mediatek.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-mtk.h"
#incwude "cwk-gate.h"

#incwude <dt-bindings/cwock/mt2701-cwk.h>

static const stwuct mtk_gate_wegs bdp0_cg_wegs = {
	.set_ofs = 0x0104,
	.cww_ofs = 0x0108,
	.sta_ofs = 0x0100,
};

static const stwuct mtk_gate_wegs bdp1_cg_wegs = {
	.set_ofs = 0x0114,
	.cww_ofs = 0x0118,
	.sta_ofs = 0x0110,
};

#define GATE_BDP0(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &bdp0_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww_inv)

#define GATE_BDP1(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &bdp1_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww_inv)

static const stwuct mtk_gate bdp_cwks[] = {
	GATE_BDP0(CWK_BDP_BWG_BA, "bwg_bacwk", "mm_sew", 0),
	GATE_BDP0(CWK_BDP_BWG_DWAM, "bwg_dwam", "mm_sew", 1),
	GATE_BDP0(CWK_BDP_WAWB_DWAM, "wawb_dwam", "mm_sew", 2),
	GATE_BDP0(CWK_BDP_WW_VDI_PXW, "ww_vdi_pxw", "hdmi_0_deep340m", 3),
	GATE_BDP0(CWK_BDP_WW_VDI_DWAM, "ww_vdi_dwam", "mm_sew", 4),
	GATE_BDP0(CWK_BDP_WW_B, "ww_bcwk", "mm_sew", 5),
	GATE_BDP0(CWK_BDP_DGI_IN, "dgi_in", "dpi1_sew", 6),
	GATE_BDP0(CWK_BDP_DGI_OUT, "dgi_out", "dpi1_sew", 7),
	GATE_BDP0(CWK_BDP_FMT_MAST_27, "fmt_mast_27", "dpi1_sew", 8),
	GATE_BDP0(CWK_BDP_FMT_B, "fmt_bcwk", "mm_sew", 9),
	GATE_BDP0(CWK_BDP_OSD_B, "osd_bcwk", "mm_sew", 10),
	GATE_BDP0(CWK_BDP_OSD_DWAM, "osd_dwam", "mm_sew", 11),
	GATE_BDP0(CWK_BDP_OSD_AGENT, "osd_agent", "osd_sew", 12),
	GATE_BDP0(CWK_BDP_OSD_PXW, "osd_pxw", "dpi1_sew", 13),
	GATE_BDP0(CWK_BDP_WWE_B, "wwe_bcwk", "mm_sew", 14),
	GATE_BDP0(CWK_BDP_WWE_AGENT, "wwe_agent", "mm_sew", 15),
	GATE_BDP0(CWK_BDP_WWE_DWAM, "wwe_dwam", "mm_sew", 16),
	GATE_BDP0(CWK_BDP_F27M, "f27m", "di_sew", 17),
	GATE_BDP0(CWK_BDP_F27M_VDOUT, "f27m_vdout", "di_sew", 18),
	GATE_BDP0(CWK_BDP_F27_74_74, "f27_74_74", "di_sew", 19),
	GATE_BDP0(CWK_BDP_F2FS, "f2fs", "di_sew", 20),
	GATE_BDP0(CWK_BDP_F2FS74_148, "f2fs74_148", "di_sew", 21),
	GATE_BDP0(CWK_BDP_FB, "fbcwk", "mm_sew", 22),
	GATE_BDP0(CWK_BDP_VDO_DWAM, "vdo_dwam", "mm_sew", 23),
	GATE_BDP0(CWK_BDP_VDO_2FS, "vdo_2fs", "di_sew", 24),
	GATE_BDP0(CWK_BDP_VDO_B, "vdo_bcwk", "mm_sew", 25),
	GATE_BDP0(CWK_BDP_WW_DI_PXW, "ww_di_pxw", "di_sew", 26),
	GATE_BDP0(CWK_BDP_WW_DI_DWAM, "ww_di_dwam", "mm_sew", 27),
	GATE_BDP0(CWK_BDP_WW_DI_B, "ww_di_bcwk", "mm_sew", 28),
	GATE_BDP0(CWK_BDP_NW_PXW, "nw_pxw", "nw_sew", 29),
	GATE_BDP0(CWK_BDP_NW_DWAM, "nw_dwam", "mm_sew", 30),
	GATE_BDP0(CWK_BDP_NW_B, "nw_bcwk", "mm_sew", 31),
	GATE_BDP1(CWK_BDP_WX_F, "wx_fcwk", "hadds2_fbcwk", 0),
	GATE_BDP1(CWK_BDP_WX_X, "wx_xcwk", "cwk26m", 1),
	GATE_BDP1(CWK_BDP_WXPDT, "wxpdtcwk", "hdmi_0_pix340m", 2),
	GATE_BDP1(CWK_BDP_WX_CSCW_N, "wx_cscw_n", "cwk26m", 3),
	GATE_BDP1(CWK_BDP_WX_CSCW, "wx_cscw", "cwk26m", 4),
	GATE_BDP1(CWK_BDP_WX_DDCSCW_N, "wx_ddcscw_n", "hdmi_scw_wx", 5),
	GATE_BDP1(CWK_BDP_WX_DDCSCW, "wx_ddcscw", "hdmi_scw_wx", 6),
	GATE_BDP1(CWK_BDP_WX_VCO, "wx_vcocwk", "hadds2pww_294m", 7),
	GATE_BDP1(CWK_BDP_WX_DP, "wx_dpcwk", "hdmi_0_pww340m", 8),
	GATE_BDP1(CWK_BDP_WX_P, "wx_pcwk", "hdmi_0_pww340m", 9),
	GATE_BDP1(CWK_BDP_WX_M, "wx_mcwk", "hadds2pww_294m", 10),
	GATE_BDP1(CWK_BDP_WX_PWW, "wx_pwwcwk", "hdmi_0_pix340m", 11),
	GATE_BDP1(CWK_BDP_BWG_WT_B, "bwg_wt_bcwk", "mm_sew", 12),
	GATE_BDP1(CWK_BDP_BWG_WT_DWAM, "bwg_wt_dwam", "mm_sew", 13),
	GATE_BDP1(CWK_BDP_WAWBWT_DWAM, "wawbwt_dwam", "mm_sew", 14),
	GATE_BDP1(CWK_BDP_TMDS_SYN, "tmds_syn", "hdmi_0_pww340m", 15),
	GATE_BDP1(CWK_BDP_HDMI_MON, "hdmi_mon", "hdmi_0_pww340m", 16),
};

static const stwuct mtk_cwk_desc bdp_desc = {
	.cwks = bdp_cwks,
	.num_cwks = AWWAY_SIZE(bdp_cwks),
};

static const stwuct of_device_id of_match_cwk_mt2701_bdp[] = {
	{
		.compatibwe = "mediatek,mt2701-bdpsys",
		.data = &bdp_desc,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt2701_bdp);

static stwuct pwatfowm_dwivew cwk_mt2701_bdp_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt2701-bdp",
		.of_match_tabwe = of_match_cwk_mt2701_bdp,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt2701_bdp_dwv);
MODUWE_WICENSE("GPW");
