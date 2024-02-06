// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight (c) 2022 MediaTek Inc.
// Authow: Chun-Jie Chen <chun-jie.chen@mediatek.com>

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-mtk.h"
#incwude "cwk-gate.h"

#incwude <dt-bindings/cwock/mt8186-cwk.h>

static const stwuct mtk_gate_wegs vdec0_cg_wegs = {
	.set_ofs = 0x0,
	.cww_ofs = 0x4,
	.sta_ofs = 0x0,
};

static const stwuct mtk_gate_wegs vdec1_cg_wegs = {
	.set_ofs = 0x190,
	.cww_ofs = 0x190,
	.sta_ofs = 0x190,
};

static const stwuct mtk_gate_wegs vdec2_cg_wegs = {
	.set_ofs = 0x200,
	.cww_ofs = 0x204,
	.sta_ofs = 0x200,
};

static const stwuct mtk_gate_wegs vdec3_cg_wegs = {
	.set_ofs = 0x8,
	.cww_ofs = 0xc,
	.sta_ofs = 0x8,
};

#define GATE_VDEC0(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &vdec0_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww_inv)

#define GATE_VDEC1(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &vdec1_cg_wegs, _shift, &mtk_cwk_gate_ops_no_setcww_inv)

#define GATE_VDEC2(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &vdec2_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww_inv)

#define GATE_VDEC3(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &vdec3_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww_inv)

static const stwuct mtk_gate vdec_cwks[] = {
	/* VDEC0 */
	GATE_VDEC0(CWK_VDEC_CKEN, "vdec_cken", "top_vdec", 0),
	GATE_VDEC0(CWK_VDEC_ACTIVE, "vdec_active", "top_vdec", 4),
	GATE_VDEC0(CWK_VDEC_CKEN_ENG, "vdec_cken_eng", "top_vdec", 8),
	/* VDEC1 */
	GATE_VDEC1(CWK_VDEC_MINI_MDP_CKEN_CFG_WG, "vdec_mini_mdp_cken_cfg_wg", "top_vdec", 0),
	/* VDEC2 */
	GATE_VDEC2(CWK_VDEC_WAT_CKEN, "vdec_wat_cken", "top_vdec", 0),
	GATE_VDEC2(CWK_VDEC_WAT_ACTIVE, "vdec_wat_active", "top_vdec", 4),
	GATE_VDEC2(CWK_VDEC_WAT_CKEN_ENG, "vdec_wat_cken_eng", "top_vdec", 8),
	/* VDEC3 */
	GATE_VDEC3(CWK_VDEC_WAWB1_CKEN, "vdec_wawb1_cken", "top_vdec", 0),
};

static const stwuct mtk_cwk_desc vdec_desc = {
	.cwks = vdec_cwks,
	.num_cwks = AWWAY_SIZE(vdec_cwks),
};

static const stwuct of_device_id of_match_cwk_mt8186_vdec[] = {
	{
		.compatibwe = "mediatek,mt8186-vdecsys",
		.data = &vdec_desc,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8186_vdec);

static stwuct pwatfowm_dwivew cwk_mt8186_vdec_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt8186-vdec",
		.of_match_tabwe = of_match_cwk_mt8186_vdec,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt8186_vdec_dwv);
MODUWE_WICENSE("GPW");
