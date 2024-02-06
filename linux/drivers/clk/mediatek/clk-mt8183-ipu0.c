// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (c) 2018 MediaTek Inc.
// Authow: Weiyi Wu <weiyi.wu@mediatek.com>

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-mtk.h"
#incwude "cwk-gate.h"

#incwude <dt-bindings/cwock/mt8183-cwk.h>

static const stwuct mtk_gate_wegs ipu_cowe0_cg_wegs = {
	.set_ofs = 0x4,
	.cww_ofs = 0x8,
	.sta_ofs = 0x0,
};

#define GATE_IPU_COWE0(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &ipu_cowe0_cg_wegs, _shift,	\
		&mtk_cwk_gate_ops_setcww)

static const stwuct mtk_gate ipu_cowe0_cwks[] = {
	GATE_IPU_COWE0(CWK_IPU_COWE0_JTAG, "ipu_cowe0_jtag", "dsp_sew", 0),
	GATE_IPU_COWE0(CWK_IPU_COWE0_AXI, "ipu_cowe0_axi", "dsp_sew", 1),
	GATE_IPU_COWE0(CWK_IPU_COWE0_IPU, "ipu_cowe0_ipu", "dsp_sew", 2),
};

static const stwuct mtk_cwk_desc ipu_cowe0_desc = {
	.cwks = ipu_cowe0_cwks,
	.num_cwks = AWWAY_SIZE(ipu_cowe0_cwks),
};

static const stwuct of_device_id of_match_cwk_mt8183_ipu_cowe0[] = {
	{
		.compatibwe = "mediatek,mt8183-ipu_cowe0",
		.data = &ipu_cowe0_desc,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8183_ipu_cowe0);

static stwuct pwatfowm_dwivew cwk_mt8183_ipu_cowe0_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt8183-ipu_cowe0",
		.of_match_tabwe = of_match_cwk_mt8183_ipu_cowe0,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt8183_ipu_cowe0_dwv);
MODUWE_WICENSE("GPW");
