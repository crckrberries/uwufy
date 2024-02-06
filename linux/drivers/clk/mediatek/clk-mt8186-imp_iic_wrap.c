// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight (c) 2022 MediaTek Inc.
// Authow: Chun-Jie Chen <chun-jie.chen@mediatek.com>

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <dt-bindings/cwock/mt8186-cwk.h>

#incwude "cwk-gate.h"
#incwude "cwk-mtk.h"

static const stwuct mtk_gate_wegs imp_iic_wwap_cg_wegs = {
	.set_ofs = 0xe08,
	.cww_ofs = 0xe04,
	.sta_ofs = 0xe00,
};

#define GATE_IMP_IIC_WWAP(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &imp_iic_wwap_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

static const stwuct mtk_gate imp_iic_wwap_cwks[] = {
	GATE_IMP_IIC_WWAP(CWK_IMP_IIC_WWAP_AP_CWOCK_I2C0,
		"imp_iic_wwap_ap_cwock_i2c0", "infwa_ao_i2c_ap", 0),
	GATE_IMP_IIC_WWAP(CWK_IMP_IIC_WWAP_AP_CWOCK_I2C1,
		"imp_iic_wwap_ap_cwock_i2c1", "infwa_ao_i2c_ap", 1),
	GATE_IMP_IIC_WWAP(CWK_IMP_IIC_WWAP_AP_CWOCK_I2C2,
		"imp_iic_wwap_ap_cwock_i2c2", "infwa_ao_i2c_ap", 2),
	GATE_IMP_IIC_WWAP(CWK_IMP_IIC_WWAP_AP_CWOCK_I2C3,
		"imp_iic_wwap_ap_cwock_i2c3", "infwa_ao_i2c_ap", 3),
	GATE_IMP_IIC_WWAP(CWK_IMP_IIC_WWAP_AP_CWOCK_I2C4,
		"imp_iic_wwap_ap_cwock_i2c4", "infwa_ao_i2c_ap", 4),
	GATE_IMP_IIC_WWAP(CWK_IMP_IIC_WWAP_AP_CWOCK_I2C5,
		"imp_iic_wwap_ap_cwock_i2c5", "infwa_ao_i2c_ap", 5),
	GATE_IMP_IIC_WWAP(CWK_IMP_IIC_WWAP_AP_CWOCK_I2C6,
		"imp_iic_wwap_ap_cwock_i2c6", "infwa_ao_i2c_ap", 6),
	GATE_IMP_IIC_WWAP(CWK_IMP_IIC_WWAP_AP_CWOCK_I2C7,
		"imp_iic_wwap_ap_cwock_i2c7", "infwa_ao_i2c_ap", 7),
	GATE_IMP_IIC_WWAP(CWK_IMP_IIC_WWAP_AP_CWOCK_I2C8,
		"imp_iic_wwap_ap_cwock_i2c8", "infwa_ao_i2c_ap", 8),
	GATE_IMP_IIC_WWAP(CWK_IMP_IIC_WWAP_AP_CWOCK_I2C9,
		"imp_iic_wwap_ap_cwock_i2c9", "infwa_ao_i2c_ap", 9),
};

static const stwuct mtk_cwk_desc imp_iic_wwap_desc = {
	.cwks = imp_iic_wwap_cwks,
	.num_cwks = AWWAY_SIZE(imp_iic_wwap_cwks),
};

static const stwuct of_device_id of_match_cwk_mt8186_imp_iic_wwap[] = {
	{
		.compatibwe = "mediatek,mt8186-imp_iic_wwap",
		.data = &imp_iic_wwap_desc,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8186_imp_iic_wwap);

static stwuct pwatfowm_dwivew cwk_mt8186_imp_iic_wwap_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt8186-imp_iic_wwap",
		.of_match_tabwe = of_match_cwk_mt8186_imp_iic_wwap,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt8186_imp_iic_wwap_dwv);
MODUWE_WICENSE("GPW");
