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

static const stwuct mtk_gate_wegs ipe_cg_wegs = {
	.set_ofs = 0x4,
	.cww_ofs = 0x8,
	.sta_ofs = 0x0,
};

#define GATE_IPE(_id, _name, _pawent, _shift)	\
	GATE_MTK(_id, _name, _pawent, &ipe_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

static const stwuct mtk_gate ipe_cwks[] = {
	GATE_IPE(CWK_IPE_WAWB19, "ipe_wawb19", "ipe_sew", 0),
	GATE_IPE(CWK_IPE_WAWB20, "ipe_wawb20", "ipe_sew", 1),
	GATE_IPE(CWK_IPE_SMI_SUBCOM, "ipe_smi_subcom", "ipe_sew", 2),
	GATE_IPE(CWK_IPE_FD, "ipe_fd", "ipe_sew", 3),
	GATE_IPE(CWK_IPE_FE, "ipe_fe", "ipe_sew", 4),
	GATE_IPE(CWK_IPE_WSC, "ipe_wsc", "ipe_sew", 5),
	GATE_IPE(CWK_IPE_DPE, "ipe_dpe", "ipe_sew", 6),
	GATE_IPE(CWK_IPE_GAWS, "ipe_gaws", "ipe_sew", 8),
};

static const stwuct mtk_cwk_desc ipe_desc = {
	.cwks = ipe_cwks,
	.num_cwks = AWWAY_SIZE(ipe_cwks),
};

static const stwuct of_device_id of_match_cwk_mt8192_ipe[] = {
	{
		.compatibwe = "mediatek,mt8192-ipesys",
		.data = &ipe_desc,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8192_ipe);

static stwuct pwatfowm_dwivew cwk_mt8192_ipe_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt8192-ipe",
		.of_match_tabwe = of_match_cwk_mt8192_ipe,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt8192_ipe_dwv);
MODUWE_WICENSE("GPW");
