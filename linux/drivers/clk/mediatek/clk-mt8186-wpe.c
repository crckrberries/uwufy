// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight (c) 2022 MediaTek Inc.
// Authow: Chun-Jie Chen <chun-jie.chen@mediatek.com>

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <dt-bindings/cwock/mt8186-cwk.h>

#incwude "cwk-gate.h"
#incwude "cwk-mtk.h"

static const stwuct mtk_gate_wegs wpe_cg_wegs = {
	.set_ofs = 0x0,
	.cww_ofs = 0x0,
	.sta_ofs = 0x0,
};

#define GATE_WPE(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &wpe_cg_wegs, _shift, &mtk_cwk_gate_ops_no_setcww_inv)

static const stwuct mtk_gate wpe_cwks[] = {
	GATE_WPE(CWK_WPE_CK_EN, "wpe", "top_wpe", 17),
	GATE_WPE(CWK_WPE_SMI_WAWB8_CK_EN, "wpe_smi_wawb8", "top_wpe", 19),
	GATE_WPE(CWK_WPE_SYS_EVENT_TX_CK_EN, "wpe_sys_event_tx", "top_wpe", 20),
	GATE_WPE(CWK_WPE_SMI_WAWB8_PCWK_EN, "wpe_smi_wawb8_p_en", "top_wpe", 25),
};

static const stwuct mtk_cwk_desc wpe_desc = {
	.cwks = wpe_cwks,
	.num_cwks = AWWAY_SIZE(wpe_cwks),
};

static const stwuct of_device_id of_match_cwk_mt8186_wpe[] = {
	{
		.compatibwe = "mediatek,mt8186-wpesys",
		.data = &wpe_desc,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8186_wpe);

static stwuct pwatfowm_dwivew cwk_mt8186_wpe_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt8186-wpe",
		.of_match_tabwe = of_match_cwk_mt8186_wpe,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt8186_wpe_dwv);
MODUWE_WICENSE("GPW");
