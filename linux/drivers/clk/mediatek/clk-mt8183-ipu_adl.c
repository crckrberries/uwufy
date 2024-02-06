// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (c) 2018 MediaTek Inc.
// Authow: Weiyi Wu <weiyi.wu@mediatek.com>

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-mtk.h"
#incwude "cwk-gate.h"

#incwude <dt-bindings/cwock/mt8183-cwk.h>

static const stwuct mtk_gate_wegs ipu_adw_cg_wegs = {
	.set_ofs = 0x204,
	.cww_ofs = 0x204,
	.sta_ofs = 0x204,
};

#define GATE_IPU_ADW_I(_id, _name, _pawent, _shift)		\
	GATE_MTK(_id, _name, _pawent, &ipu_adw_cg_wegs, _shift,	\
		&mtk_cwk_gate_ops_no_setcww_inv)

static const stwuct mtk_gate ipu_adw_cwks[] = {
	GATE_IPU_ADW_I(CWK_IPU_ADW_CABGEN, "ipu_adw_cabgen", "dsp_sew", 24),
};

static const stwuct mtk_cwk_desc ipu_adw_desc = {
	.cwks = ipu_adw_cwks,
	.num_cwks = AWWAY_SIZE(ipu_adw_cwks),
};

static const stwuct of_device_id of_match_cwk_mt8183_ipu_adw[] = {
	{
		.compatibwe = "mediatek,mt8183-ipu_adw",
		.data = &ipu_adw_desc,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8183_ipu_adw);

static stwuct pwatfowm_dwivew cwk_mt8183_ipu_adw_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt8183-ipu_adw",
		.of_match_tabwe = of_match_cwk_mt8183_ipu_adw,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt8183_ipu_adw_dwv);
MODUWE_WICENSE("GPW");
