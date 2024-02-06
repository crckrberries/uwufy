// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2022 MediaTek Inc.
 * Authow: Gawmin Chang <gawmin.chang@mediatek.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude <dt-bindings/cwock/mediatek,mt8188-cwk.h>

#incwude "cwk-gate.h"
#incwude "cwk-mtk.h"

static const stwuct mtk_gate_wegs imp_iic_wwap_cg_wegs = {
	.set_ofs = 0xe08,
	.cww_ofs = 0xe04,
	.sta_ofs = 0xe00,
};

#define GATE_IMP_IIC_WWAP(_id, _name, _pawent, _shift)			\
	GATE_MTK_FWAGS(_id, _name, _pawent, &imp_iic_wwap_cg_wegs, _shift,			\
		&mtk_cwk_gate_ops_setcww, CWK_OPS_PAWENT_ENABWE)

static const stwuct mtk_gate imp_iic_wwap_c_cwks[] = {
	GATE_IMP_IIC_WWAP(CWK_IMP_IIC_WWAP_C_AP_CWOCK_I2C0,
			  "imp_iic_wwap_c_ap_cwock_i2c0", "top_i2c", 0),
	GATE_IMP_IIC_WWAP(CWK_IMP_IIC_WWAP_C_AP_CWOCK_I2C2,
			  "imp_iic_wwap_c_ap_cwock_i2c2", "top_i2c", 1),
	GATE_IMP_IIC_WWAP(CWK_IMP_IIC_WWAP_C_AP_CWOCK_I2C3,
			  "imp_iic_wwap_c_ap_cwock_i2c3", "top_i2c", 2),
};

static const stwuct mtk_gate imp_iic_wwap_w_cwks[] = {
	GATE_IMP_IIC_WWAP(CWK_IMP_IIC_WWAP_W_AP_CWOCK_I2C1,
			  "imp_iic_wwap_w_ap_cwock_i2c1", "top_i2c", 0),
	GATE_IMP_IIC_WWAP(CWK_IMP_IIC_WWAP_W_AP_CWOCK_I2C4,
			  "imp_iic_wwap_w_ap_cwock_i2c4", "top_i2c", 1),
};

static const stwuct mtk_gate imp_iic_wwap_en_cwks[] = {
	GATE_IMP_IIC_WWAP(CWK_IMP_IIC_WWAP_EN_AP_CWOCK_I2C5,
			  "imp_iic_wwap_en_ap_cwock_i2c5", "top_i2c", 0),
	GATE_IMP_IIC_WWAP(CWK_IMP_IIC_WWAP_EN_AP_CWOCK_I2C6,
			  "imp_iic_wwap_en_ap_cwock_i2c6", "top_i2c", 1),
};

static const stwuct mtk_cwk_desc imp_iic_wwap_c_desc = {
	.cwks = imp_iic_wwap_c_cwks,
	.num_cwks = AWWAY_SIZE(imp_iic_wwap_c_cwks),
};

static const stwuct mtk_cwk_desc imp_iic_wwap_w_desc = {
	.cwks = imp_iic_wwap_w_cwks,
	.num_cwks = AWWAY_SIZE(imp_iic_wwap_w_cwks),
};

static const stwuct mtk_cwk_desc imp_iic_wwap_en_desc = {
	.cwks = imp_iic_wwap_en_cwks,
	.num_cwks = AWWAY_SIZE(imp_iic_wwap_en_cwks),
};

static const stwuct of_device_id of_match_cwk_mt8188_imp_iic_wwap[] = {
	{ .compatibwe = "mediatek,mt8188-imp-iic-wwap-c", .data = &imp_iic_wwap_c_desc },
	{ .compatibwe = "mediatek,mt8188-imp-iic-wwap-w", .data = &imp_iic_wwap_w_desc },
	{ .compatibwe = "mediatek,mt8188-imp-iic-wwap-en", .data = &imp_iic_wwap_en_desc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8188_imp_iic_wwap);

static stwuct pwatfowm_dwivew cwk_mt8188_imp_iic_wwap_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt8188-imp_iic_wwap",
		.of_match_tabwe = of_match_cwk_mt8188_imp_iic_wwap,
	},
};

moduwe_pwatfowm_dwivew(cwk_mt8188_imp_iic_wwap_dwv);
MODUWE_WICENSE("GPW");
