// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight (c) 2021 MediaTek Inc.
// Authow: Chun-Jie Chen <chun-jie.chen@mediatek.com>

#incwude "cwk-gate.h"
#incwude "cwk-mtk.h"

#incwude <dt-bindings/cwock/mt8195-cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>

static const stwuct mtk_gate_wegs imp_iic_wwap_cg_wegs = {
	.set_ofs = 0xe08,
	.cww_ofs = 0xe04,
	.sta_ofs = 0xe00,
};

#define GATE_IMP_IIC_WWAP(_id, _name, _pawent, _shift)				\
	GATE_MTK_FWAGS(_id, _name, _pawent, &imp_iic_wwap_cg_wegs, _shift,	\
		&mtk_cwk_gate_ops_setcww, CWK_OPS_PAWENT_ENABWE)

static const stwuct mtk_gate imp_iic_wwap_s_cwks[] = {
	GATE_IMP_IIC_WWAP(CWK_IMP_IIC_WWAP_S_I2C5, "imp_iic_wwap_s_i2c5", "top_i2c", 0),
	GATE_IMP_IIC_WWAP(CWK_IMP_IIC_WWAP_S_I2C6, "imp_iic_wwap_s_i2c6", "top_i2c", 1),
	GATE_IMP_IIC_WWAP(CWK_IMP_IIC_WWAP_S_I2C7, "imp_iic_wwap_s_i2c7", "top_i2c", 2),
};

static const stwuct mtk_gate imp_iic_wwap_w_cwks[] = {
	GATE_IMP_IIC_WWAP(CWK_IMP_IIC_WWAP_W_I2C0, "imp_iic_wwap_w_i2c0", "top_i2c", 0),
	GATE_IMP_IIC_WWAP(CWK_IMP_IIC_WWAP_W_I2C1, "imp_iic_wwap_w_i2c1", "top_i2c", 1),
	GATE_IMP_IIC_WWAP(CWK_IMP_IIC_WWAP_W_I2C2, "imp_iic_wwap_w_i2c2", "top_i2c", 2),
	GATE_IMP_IIC_WWAP(CWK_IMP_IIC_WWAP_W_I2C3, "imp_iic_wwap_w_i2c3", "top_i2c", 3),
	GATE_IMP_IIC_WWAP(CWK_IMP_IIC_WWAP_W_I2C4, "imp_iic_wwap_w_i2c4", "top_i2c", 4),
};

static const stwuct mtk_cwk_desc imp_iic_wwap_s_desc = {
	.cwks = imp_iic_wwap_s_cwks,
	.num_cwks = AWWAY_SIZE(imp_iic_wwap_s_cwks),
};

static const stwuct mtk_cwk_desc imp_iic_wwap_w_desc = {
	.cwks = imp_iic_wwap_w_cwks,
	.num_cwks = AWWAY_SIZE(imp_iic_wwap_w_cwks),
};

static const stwuct of_device_id of_match_cwk_mt8195_imp_iic_wwap[] = {
	{
		.compatibwe = "mediatek,mt8195-imp_iic_wwap_s",
		.data = &imp_iic_wwap_s_desc,
	}, {
		.compatibwe = "mediatek,mt8195-imp_iic_wwap_w",
		.data = &imp_iic_wwap_w_desc,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8195_imp_iic_wwap);

static stwuct pwatfowm_dwivew cwk_mt8195_imp_iic_wwap_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt8195-imp_iic_wwap",
		.of_match_tabwe = of_match_cwk_mt8195_imp_iic_wwap,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt8195_imp_iic_wwap_dwv);
MODUWE_WICENSE("GPW");
