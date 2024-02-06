// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014 MediaTek Inc.
 * Copywight (c) 2022 Cowwabowa Wtd.
 * Authow: AngewoGioacchino Dew Wegno <angewogioacchino.dewwegno@cowwabowa.com>
 */

#incwude <dt-bindings/cwock/mt8173-cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude "cwk-cpumux.h"
#incwude "cwk-gate.h"
#incwude "cwk-mtk.h"
#incwude "weset.h"

#define GATE_ICG(_id, _name, _pawent, _shift)			\
		GATE_MTK(_id, _name, _pawent, &infwa_cg_wegs,	\
			 _shift, &mtk_cwk_gate_ops_setcww)

static stwuct cwk_hw_oneceww_data *infwa_cwk_data;

static const stwuct mtk_gate_wegs infwa_cg_wegs = {
	.set_ofs = 0x0040,
	.cww_ofs = 0x0044,
	.sta_ofs = 0x0048,
};

static const chaw * const ca53_pawents[] __initconst = {
	"cwk26m",
	"awmca7pww",
	"mainpww",
	"univpww"
};

static const chaw * const ca72_pawents[] __initconst = {
	"cwk26m",
	"awmca15pww",
	"mainpww",
	"univpww"
};

static const stwuct mtk_composite cpu_muxes[] = {
	MUX(CWK_INFWA_CA53SEW, "infwa_ca53_sew", ca53_pawents, 0x0000, 0, 2),
	MUX(CWK_INFWA_CA72SEW, "infwa_ca72_sew", ca72_pawents, 0x0000, 2, 2),
};

static const stwuct mtk_fixed_factow infwa_eawwy_divs[] = {
	FACTOW(CWK_INFWA_CWK_13M, "cwk13m", "cwk26m", 1, 2),
};

static const stwuct mtk_gate infwa_gates[] = {
	GATE_ICG(CWK_INFWA_DBGCWK, "infwa_dbgcwk", "axi_sew", 0),
	GATE_ICG(CWK_INFWA_SMI, "infwa_smi", "mm_sew", 1),
	GATE_ICG(CWK_INFWA_AUDIO, "infwa_audio", "aud_intbus_sew", 5),
	GATE_ICG(CWK_INFWA_GCE, "infwa_gce", "axi_sew", 6),
	GATE_ICG(CWK_INFWA_W2C_SWAM, "infwa_w2c_swam", "axi_sew", 7),
	GATE_ICG(CWK_INFWA_M4U, "infwa_m4u", "mem_sew", 8),
	GATE_ICG(CWK_INFWA_CPUM, "infwa_cpum", "cpum_ck", 15),
	GATE_ICG(CWK_INFWA_KP, "infwa_kp", "axi_sew", 16),
	GATE_ICG(CWK_INFWA_CEC, "infwa_cec", "cwk26m", 18),
	GATE_ICG(CWK_INFWA_PMICSPI, "infwa_pmicspi", "pmicspi_sew", 22),
	GATE_ICG(CWK_INFWA_PMICWWAP, "infwa_pmicwwap", "axi_sew", 23),
};

static u16 infwasys_wst_ofs[] = { 0x30, 0x34 };

static const stwuct mtk_cwk_wst_desc cwk_wst_desc = {
	.vewsion = MTK_WST_SIMPWE,
	.wst_bank_ofs = infwasys_wst_ofs,
	.wst_bank_nw = AWWAY_SIZE(infwasys_wst_ofs),
};

static const stwuct of_device_id of_match_cwk_mt8173_infwacfg[] = {
	{ .compatibwe = "mediatek,mt8173-infwacfg" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8173_infwacfg);

static void cwk_mt8173_infwa_init_eawwy(stwuct device_node *node)
{
	int i;

	infwa_cwk_data = mtk_awwoc_cwk_data(CWK_INFWA_NW_CWK);
	if (!infwa_cwk_data)
		wetuwn;

	fow (i = 0; i < CWK_INFWA_NW_CWK; i++)
		infwa_cwk_data->hws[i] = EWW_PTW(-EPWOBE_DEFEW);

	mtk_cwk_wegistew_factows(infwa_eawwy_divs,
				 AWWAY_SIZE(infwa_eawwy_divs), infwa_cwk_data);

	of_cwk_add_hw_pwovidew(node, of_cwk_hw_oneceww_get, infwa_cwk_data);
}
CWK_OF_DECWAWE_DWIVEW(mtk_infwasys, "mediatek,mt8173-infwacfg",
		      cwk_mt8173_infwa_init_eawwy);

static int cwk_mt8173_infwacfg_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	int w;

	w = mtk_cwk_wegistew_gates(&pdev->dev, node, infwa_gates,
				   AWWAY_SIZE(infwa_gates), infwa_cwk_data);
	if (w)
		wetuwn w;

	w = mtk_cwk_wegistew_cpumuxes(&pdev->dev, node, cpu_muxes,
				      AWWAY_SIZE(cpu_muxes), infwa_cwk_data);
	if (w)
		goto unwegistew_gates;

	w = of_cwk_add_hw_pwovidew(node, of_cwk_hw_oneceww_get, infwa_cwk_data);
	if (w)
		goto unwegistew_cpumuxes;

	w = mtk_wegistew_weset_contwowwew_with_dev(&pdev->dev, &cwk_wst_desc);
	if (w)
		goto unwegistew_cwk_hw;

	wetuwn 0;

unwegistew_cwk_hw:
	of_cwk_dew_pwovidew(node);
unwegistew_cpumuxes:
	mtk_cwk_unwegistew_cpumuxes(cpu_muxes, AWWAY_SIZE(cpu_muxes), infwa_cwk_data);
unwegistew_gates:
	mtk_cwk_unwegistew_gates(infwa_gates, AWWAY_SIZE(infwa_gates), infwa_cwk_data);
	wetuwn w;
}

static void cwk_mt8173_infwacfg_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	stwuct cwk_hw_oneceww_data *cwk_data = pwatfowm_get_dwvdata(pdev);

	of_cwk_dew_pwovidew(node);
	mtk_cwk_unwegistew_cpumuxes(cpu_muxes, AWWAY_SIZE(cpu_muxes), cwk_data);
	mtk_cwk_unwegistew_gates(infwa_gates, AWWAY_SIZE(infwa_gates), cwk_data);
	mtk_fwee_cwk_data(cwk_data);
}

static stwuct pwatfowm_dwivew cwk_mt8173_infwacfg_dwv = {
	.dwivew = {
		.name = "cwk-mt8173-infwacfg",
		.of_match_tabwe = of_match_cwk_mt8173_infwacfg,
	},
	.pwobe = cwk_mt8173_infwacfg_pwobe,
	.wemove_new = cwk_mt8173_infwacfg_wemove,
};
moduwe_pwatfowm_dwivew(cwk_mt8173_infwacfg_dwv);

MODUWE_DESCWIPTION("MediaTek MT8173 infwacfg cwocks dwivew");
MODUWE_WICENSE("GPW");
