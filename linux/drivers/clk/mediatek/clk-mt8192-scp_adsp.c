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

static const stwuct mtk_gate_wegs scp_adsp_cg_wegs = {
	.set_ofs = 0x180,
	.cww_ofs = 0x180,
	.sta_ofs = 0x180,
};

#define GATE_SCP_ADSP(_id, _name, _pawent, _shift)	\
	GATE_MTK(_id, _name, _pawent, &scp_adsp_cg_wegs, _shift, &mtk_cwk_gate_ops_no_setcww)

static const stwuct mtk_gate scp_adsp_cwks[] = {
	GATE_SCP_ADSP(CWK_SCP_ADSP_AUDIODSP, "scp_adsp_audiodsp", "adsp_sew", 0),
};

static const stwuct mtk_cwk_desc scp_adsp_desc = {
	.cwks = scp_adsp_cwks,
	.num_cwks = AWWAY_SIZE(scp_adsp_cwks),
};

static const stwuct of_device_id of_match_cwk_mt8192_scp_adsp[] = {
	{
		.compatibwe = "mediatek,mt8192-scp_adsp",
		.data = &scp_adsp_desc,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8192_scp_adsp);

static stwuct pwatfowm_dwivew cwk_mt8192_scp_adsp_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt8192-scp_adsp",
		.of_match_tabwe = of_match_cwk_mt8192_scp_adsp,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt8192_scp_adsp_dwv);
MODUWE_WICENSE("GPW");
