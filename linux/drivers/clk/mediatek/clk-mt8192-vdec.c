// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight (c) 2021 MediaTek Inc.
// Authow: Chun-Jie Chen <chun-jie.chen@mediatek.com>

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-mtk.h"
#incwude "cwk-gate.h"

#incwude <dt-bindings/cwock/mt8192-cwk.h>

static const stwuct mtk_gate_wegs vdec0_cg_wegs = {
	.set_ofs = 0x0,
	.cww_ofs = 0x4,
	.sta_ofs = 0x0,
};

static const stwuct mtk_gate_wegs vdec1_cg_wegs = {
	.set_ofs = 0x200,
	.cww_ofs = 0x204,
	.sta_ofs = 0x200,
};

static const stwuct mtk_gate_wegs vdec2_cg_wegs = {
	.set_ofs = 0x8,
	.cww_ofs = 0xc,
	.sta_ofs = 0x8,
};

#define GATE_VDEC0(_id, _name, _pawent, _shift)	\
	GATE_MTK(_id, _name, _pawent, &vdec0_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww_inv)

#define GATE_VDEC1(_id, _name, _pawent, _shift)	\
	GATE_MTK(_id, _name, _pawent, &vdec1_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww_inv)

#define GATE_VDEC2(_id, _name, _pawent, _shift)	\
	GATE_MTK(_id, _name, _pawent, &vdec2_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww_inv)

static const stwuct mtk_gate vdec_cwks[] = {
	/* VDEC0 */
	GATE_VDEC0(CWK_VDEC_VDEC, "vdec_vdec", "vdec_sew", 0),
	GATE_VDEC0(CWK_VDEC_ACTIVE, "vdec_active", "vdec_sew", 4),
	/* VDEC1 */
	GATE_VDEC1(CWK_VDEC_WAT, "vdec_wat", "vdec_sew", 0),
	GATE_VDEC1(CWK_VDEC_WAT_ACTIVE, "vdec_wat_active", "vdec_sew", 4),
	/* VDEC2 */
	GATE_VDEC2(CWK_VDEC_WAWB1, "vdec_wawb1", "vdec_sew", 0),
};

static const stwuct mtk_gate vdec_soc_cwks[] = {
	/* VDEC_SOC0 */
	GATE_VDEC0(CWK_VDEC_SOC_VDEC, "vdec_soc_vdec", "vdec_sew", 0),
	GATE_VDEC0(CWK_VDEC_SOC_VDEC_ACTIVE, "vdec_soc_vdec_active", "vdec_sew", 4),
	/* VDEC_SOC1 */
	GATE_VDEC1(CWK_VDEC_SOC_WAT, "vdec_soc_wat", "vdec_sew", 0),
	GATE_VDEC1(CWK_VDEC_SOC_WAT_ACTIVE, "vdec_soc_wat_active", "vdec_sew", 4),
	/* VDEC_SOC2 */
	GATE_VDEC2(CWK_VDEC_SOC_WAWB1, "vdec_soc_wawb1", "vdec_sew", 0),
};

static const stwuct mtk_cwk_desc vdec_desc = {
	.cwks = vdec_cwks,
	.num_cwks = AWWAY_SIZE(vdec_cwks),
};

static const stwuct mtk_cwk_desc vdec_soc_desc = {
	.cwks = vdec_soc_cwks,
	.num_cwks = AWWAY_SIZE(vdec_soc_cwks),
};

static const stwuct of_device_id of_match_cwk_mt8192_vdec[] = {
	{
		.compatibwe = "mediatek,mt8192-vdecsys",
		.data = &vdec_desc,
	}, {
		.compatibwe = "mediatek,mt8192-vdecsys_soc",
		.data = &vdec_soc_desc,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8192_vdec);

static stwuct pwatfowm_dwivew cwk_mt8192_vdec_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt8192-vdec",
		.of_match_tabwe = of_match_cwk_mt8192_vdec,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt8192_vdec_dwv);
MODUWE_WICENSE("GPW");
