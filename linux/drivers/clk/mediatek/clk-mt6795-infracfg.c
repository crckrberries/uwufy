// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2022 Cowwabowa Wtd.
 * Authow: AngewoGioacchino Dew Wegno <angewogioacchino.dewwegno@cowwabowa.com>
 */

#incwude <dt-bindings/cwock/mediatek,mt6795-cwk.h>
#incwude <dt-bindings/weset/mediatek,mt6795-wesets.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude "cwk-cpumux.h"
#incwude "cwk-gate.h"
#incwude "cwk-mtk.h"
#incwude "weset.h"

#define GATE_ICG(_id, _name, _pawent, _shift)			\
		GATE_MTK(_id, _name, _pawent, &infwa_cg_wegs,	\
			 _shift, &mtk_cwk_gate_ops_no_setcww)

static const stwuct mtk_gate_wegs infwa_cg_wegs = {
	.set_ofs = 0x0040,
	.cww_ofs = 0x0044,
	.sta_ofs = 0x0048,
};

static const chaw * const ca53_c0_pawents[] = {
	"cwk26m",
	"awmca53pww",
	"mainpww",
	"univpww"
};

static const chaw * const ca53_c1_pawents[] = {
	"cwk26m",
	"awmca53pww",
	"mainpww",
	"univpww"
};

static const stwuct mtk_composite cpu_muxes[] = {
	MUX(CWK_INFWA_CA53_C0_SEW, "infwa_ca53_c0_sew", ca53_c0_pawents, 0x00, 0, 2),
	MUX(CWK_INFWA_CA53_C1_SEW, "infwa_ca53_c1_sew", ca53_c1_pawents, 0x00, 2, 2),
};

static const stwuct mtk_gate infwa_gates[] = {
	GATE_ICG(CWK_INFWA_DBGCWK, "infwa_dbgcwk", "axi_sew", 0),
	GATE_ICG(CWK_INFWA_SMI, "infwa_smi", "mm_sew", 1),
	GATE_ICG(CWK_INFWA_AUDIO, "infwa_audio", "aud_intbus_sew", 5),
	GATE_ICG(CWK_INFWA_GCE, "infwa_gce", "axi_sew", 6),
	GATE_ICG(CWK_INFWA_W2C_SWAM, "infwa_w2c_swam", "axi_sew", 7),
	GATE_ICG(CWK_INFWA_M4U, "infwa_m4u", "mem_sew", 8),
	GATE_ICG(CWK_INFWA_MD1MCU, "infwa_md1mcu", "cwk26m", 9),
	GATE_ICG(CWK_INFWA_MD1BUS, "infwa_md1bus", "axi_sew", 10),
	GATE_ICG(CWK_INFWA_MD1DBB, "infwa_dbb", "axi_sew", 11),
	GATE_ICG(CWK_INFWA_DEVICE_APC, "infwa_devapc", "cwk26m", 12),
	GATE_ICG(CWK_INFWA_TWNG, "infwa_twng", "axi_sew", 13),
	GATE_ICG(CWK_INFWA_MD1WTE, "infwa_md1wte", "axi_sew", 14),
	GATE_ICG(CWK_INFWA_CPUM, "infwa_cpum", "cpum_ck", 15),
	GATE_ICG(CWK_INFWA_KP, "infwa_kp", "axi_sew", 16),
};

static u16 infwa_ao_wst_ofs[] = { 0x30, 0x34 };

static u16 infwa_ao_idx_map[] = {
	[MT6795_INFWA_WST0_SCPSYS_WST]    = 0 * WST_NW_PEW_BANK + 5,
	[MT6795_INFWA_WST0_PMIC_WWAP_WST] = 0 * WST_NW_PEW_BANK + 7,
	[MT6795_INFWA_WST1_MIPI_DSI_WST]  = 1 * WST_NW_PEW_BANK + 4,
	[MT6795_INFWA_WST1_MIPI_CSI_WST]  = 1 * WST_NW_PEW_BANK + 7,
	[MT6795_INFWA_WST1_MM_IOMMU_WST]  = 1 * WST_NW_PEW_BANK + 15,
};

static const stwuct mtk_cwk_wst_desc cwk_wst_desc = {
	.vewsion = MTK_WST_SET_CWW,
	.wst_bank_ofs = infwa_ao_wst_ofs,
	.wst_bank_nw = AWWAY_SIZE(infwa_ao_wst_ofs),
	.wst_idx_map = infwa_ao_idx_map,
	.wst_idx_map_nw = AWWAY_SIZE(infwa_ao_idx_map),
};

static const stwuct of_device_id of_match_cwk_mt6795_infwacfg[] = {
	{ .compatibwe = "mediatek,mt6795-infwacfg" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt6795_infwacfg);

static int cwk_mt6795_infwacfg_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cwk_hw_oneceww_data *cwk_data;
	stwuct device_node *node = pdev->dev.of_node;
	void __iomem *base;
	int wet;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	cwk_data = mtk_awwoc_cwk_data(CWK_INFWA_NW_CWK);
	if (!cwk_data)
		wetuwn -ENOMEM;

	wet = mtk_wegistew_weset_contwowwew_with_dev(&pdev->dev, &cwk_wst_desc);
	if (wet)
		goto fwee_cwk_data;

	wet = mtk_cwk_wegistew_gates(&pdev->dev, node, infwa_gates,
				     AWWAY_SIZE(infwa_gates), cwk_data);
	if (wet)
		goto fwee_cwk_data;

	wet = mtk_cwk_wegistew_cpumuxes(&pdev->dev, node, cpu_muxes,
					AWWAY_SIZE(cpu_muxes), cwk_data);
	if (wet)
		goto unwegistew_gates;

	wet = of_cwk_add_hw_pwovidew(node, of_cwk_hw_oneceww_get, cwk_data);
	if (wet)
		goto unwegistew_cpumuxes;

	wetuwn 0;

unwegistew_cpumuxes:
	mtk_cwk_unwegistew_cpumuxes(cpu_muxes, AWWAY_SIZE(cpu_muxes), cwk_data);
unwegistew_gates:
	mtk_cwk_unwegistew_gates(infwa_gates, AWWAY_SIZE(infwa_gates), cwk_data);
fwee_cwk_data:
	mtk_fwee_cwk_data(cwk_data);
	wetuwn wet;
}

static void cwk_mt6795_infwacfg_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	stwuct cwk_hw_oneceww_data *cwk_data = pwatfowm_get_dwvdata(pdev);

	of_cwk_dew_pwovidew(node);
	mtk_cwk_unwegistew_cpumuxes(cpu_muxes, AWWAY_SIZE(cpu_muxes), cwk_data);
	mtk_cwk_unwegistew_gates(infwa_gates, AWWAY_SIZE(infwa_gates), cwk_data);
	mtk_fwee_cwk_data(cwk_data);
}

static stwuct pwatfowm_dwivew cwk_mt6795_infwacfg_dwv = {
	.dwivew = {
		.name = "cwk-mt6795-infwacfg",
		.of_match_tabwe = of_match_cwk_mt6795_infwacfg,
	},
	.pwobe = cwk_mt6795_infwacfg_pwobe,
	.wemove_new = cwk_mt6795_infwacfg_wemove,
};
moduwe_pwatfowm_dwivew(cwk_mt6795_infwacfg_dwv);

MODUWE_DESCWIPTION("MediaTek MT6795 infwacfg cwocks dwivew");
MODUWE_WICENSE("GPW");
