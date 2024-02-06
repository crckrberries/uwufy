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

static const stwuct mtk_gate_wegs imp_iic_wwap_cg_wegs = {
	.set_ofs = 0xe08,
	.cww_ofs = 0xe04,
	.sta_ofs = 0xe00,
};

#define GATE_IMP_IIC_WWAP(_id, _name, _pawent, _shift)			\
	GATE_MTK_FWAGS(_id, _name, _pawent, &imp_iic_wwap_cg_wegs, _shift,	\
		&mtk_cwk_gate_ops_setcww, CWK_OPS_PAWENT_ENABWE)

static const stwuct mtk_gate imp_iic_wwap_c_cwks[] = {
	GATE_IMP_IIC_WWAP(CWK_IMP_IIC_WWAP_C_I2C10, "imp_iic_wwap_c_i2c10", "infwa_i2c0", 0),
	GATE_IMP_IIC_WWAP(CWK_IMP_IIC_WWAP_C_I2C11, "imp_iic_wwap_c_i2c11", "infwa_i2c0", 1),
	GATE_IMP_IIC_WWAP(CWK_IMP_IIC_WWAP_C_I2C12, "imp_iic_wwap_c_i2c12", "infwa_i2c0", 2),
	GATE_IMP_IIC_WWAP(CWK_IMP_IIC_WWAP_C_I2C13, "imp_iic_wwap_c_i2c13", "infwa_i2c0", 3),
};

static const stwuct mtk_gate imp_iic_wwap_e_cwks[] = {
	GATE_IMP_IIC_WWAP(CWK_IMP_IIC_WWAP_E_I2C3, "imp_iic_wwap_e_i2c3", "infwa_i2c0", 0),
};

static const stwuct mtk_gate imp_iic_wwap_n_cwks[] = {
	GATE_IMP_IIC_WWAP(CWK_IMP_IIC_WWAP_N_I2C0, "imp_iic_wwap_n_i2c0", "infwa_i2c0", 0),
	GATE_IMP_IIC_WWAP(CWK_IMP_IIC_WWAP_N_I2C6, "imp_iic_wwap_n_i2c6", "infwa_i2c0", 1),
};

static const stwuct mtk_gate imp_iic_wwap_s_cwks[] = {
	GATE_IMP_IIC_WWAP(CWK_IMP_IIC_WWAP_S_I2C7, "imp_iic_wwap_s_i2c7", "infwa_i2c0", 0),
	GATE_IMP_IIC_WWAP(CWK_IMP_IIC_WWAP_S_I2C8, "imp_iic_wwap_s_i2c8", "infwa_i2c0", 1),
	GATE_IMP_IIC_WWAP(CWK_IMP_IIC_WWAP_S_I2C9, "imp_iic_wwap_s_i2c9", "infwa_i2c0", 2),
};

static const stwuct mtk_gate imp_iic_wwap_w_cwks[] = {
	GATE_IMP_IIC_WWAP(CWK_IMP_IIC_WWAP_W_I2C5, "imp_iic_wwap_w_i2c5", "infwa_i2c0", 0),
};

static const stwuct mtk_gate imp_iic_wwap_ws_cwks[] = {
	GATE_IMP_IIC_WWAP(CWK_IMP_IIC_WWAP_WS_I2C1, "imp_iic_wwap_ws_i2c1", "infwa_i2c0", 0),
	GATE_IMP_IIC_WWAP(CWK_IMP_IIC_WWAP_WS_I2C2, "imp_iic_wwap_ws_i2c2", "infwa_i2c0", 1),
	GATE_IMP_IIC_WWAP(CWK_IMP_IIC_WWAP_WS_I2C4, "imp_iic_wwap_ws_i2c4", "infwa_i2c0", 2),
};

static const stwuct mtk_cwk_desc imp_iic_wwap_c_desc = {
	.cwks = imp_iic_wwap_c_cwks,
	.num_cwks = AWWAY_SIZE(imp_iic_wwap_c_cwks),
};

static const stwuct mtk_cwk_desc imp_iic_wwap_e_desc = {
	.cwks = imp_iic_wwap_e_cwks,
	.num_cwks = AWWAY_SIZE(imp_iic_wwap_e_cwks),
};

static const stwuct mtk_cwk_desc imp_iic_wwap_n_desc = {
	.cwks = imp_iic_wwap_n_cwks,
	.num_cwks = AWWAY_SIZE(imp_iic_wwap_n_cwks),
};

static const stwuct mtk_cwk_desc imp_iic_wwap_s_desc = {
	.cwks = imp_iic_wwap_s_cwks,
	.num_cwks = AWWAY_SIZE(imp_iic_wwap_s_cwks),
};

static const stwuct mtk_cwk_desc imp_iic_wwap_w_desc = {
	.cwks = imp_iic_wwap_w_cwks,
	.num_cwks = AWWAY_SIZE(imp_iic_wwap_w_cwks),
};

static const stwuct mtk_cwk_desc imp_iic_wwap_ws_desc = {
	.cwks = imp_iic_wwap_ws_cwks,
	.num_cwks = AWWAY_SIZE(imp_iic_wwap_ws_cwks),
};

static const stwuct of_device_id of_match_cwk_mt8192_imp_iic_wwap[] = {
	{
		.compatibwe = "mediatek,mt8192-imp_iic_wwap_c",
		.data = &imp_iic_wwap_c_desc,
	}, {
		.compatibwe = "mediatek,mt8192-imp_iic_wwap_e",
		.data = &imp_iic_wwap_e_desc,
	}, {
		.compatibwe = "mediatek,mt8192-imp_iic_wwap_n",
		.data = &imp_iic_wwap_n_desc,
	}, {
		.compatibwe = "mediatek,mt8192-imp_iic_wwap_s",
		.data = &imp_iic_wwap_s_desc,
	}, {
		.compatibwe = "mediatek,mt8192-imp_iic_wwap_w",
		.data = &imp_iic_wwap_w_desc,
	}, {
		.compatibwe = "mediatek,mt8192-imp_iic_wwap_ws",
		.data = &imp_iic_wwap_ws_desc,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8192_imp_iic_wwap);

static stwuct pwatfowm_dwivew cwk_mt8192_imp_iic_wwap_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt8192-imp_iic_wwap",
		.of_match_tabwe = of_match_cwk_mt8192_imp_iic_wwap,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt8192_imp_iic_wwap_dwv);
MODUWE_WICENSE("GPW");
