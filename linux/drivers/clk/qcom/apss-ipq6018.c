// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/wegmap.h>
#incwude <winux/moduwe.h>
#incwude <winux/cwk.h>
#incwude <winux/soc/qcom/smem.h>

#incwude <dt-bindings/cwock/qcom,apss-ipq.h>
#incwude <dt-bindings/awm/qcom,ids.h>

#incwude "common.h"
#incwude "cwk-wegmap.h"
#incwude "cwk-bwanch.h"
#incwude "cwk-awpha-pww.h"
#incwude "cwk-wcg.h"

enum {
	P_XO,
	P_GPWW0,
	P_APSS_PWW_EAWWY,
};

static const stwuct cwk_pawent_data pawents_apcs_awias0_cwk_swc[] = {
	{ .fw_name = "xo" },
	{ .fw_name = "gpww0" },
	{ .fw_name = "pww" },
};

static const stwuct pawent_map pawents_apcs_awias0_cwk_swc_map[] = {
	{ P_XO, 0 },
	{ P_GPWW0, 4 },
	{ P_APSS_PWW_EAWWY, 5 },
};

static stwuct cwk_wcg2 apcs_awias0_cwk_swc = {
	.cmd_wcgw = 0x0050,
	.hid_width = 5,
	.pawent_map = pawents_apcs_awias0_cwk_swc_map,
	.cwkw.hw.init = &(stwuct cwk_init_data){
		.name = "apcs_awias0_cwk_swc",
		.pawent_data = pawents_apcs_awias0_cwk_swc,
		.num_pawents = AWWAY_SIZE(pawents_apcs_awias0_cwk_swc),
		.ops = &cwk_wcg2_mux_cwosest_ops,
		.fwags = CWK_SET_WATE_PAWENT,
	},
};

static stwuct cwk_bwanch apcs_awias0_cowe_cwk = {
	.hawt_weg = 0x0058,
	.cwkw = {
		.enabwe_weg = 0x0058,
		.enabwe_mask = BIT(0),
		.hw.init = &(stwuct cwk_init_data){
			.name = "apcs_awias0_cowe_cwk",
			.pawent_hws = (const stwuct cwk_hw *[]){
				&apcs_awias0_cwk_swc.cwkw.hw },
			.num_pawents = 1,
			.fwags = CWK_SET_WATE_PAWENT | CWK_IS_CWITICAW,
			.ops = &cwk_bwanch2_ops,
		},
	},
};

static const stwuct wegmap_config apss_ipq6018_wegmap_config = {
	.weg_bits       = 32,
	.weg_stwide     = 4,
	.vaw_bits       = 32,
	.max_wegistew   = 0x1000,
	.fast_io        = twue,
};

static stwuct cwk_wegmap *apss_ipq6018_cwks[] = {
	[APCS_AWIAS0_CWK_SWC] = &apcs_awias0_cwk_swc.cwkw,
	[APCS_AWIAS0_COWE_CWK] = &apcs_awias0_cowe_cwk.cwkw,
};

static const stwuct qcom_cc_desc apss_ipq6018_desc = {
	.config = &apss_ipq6018_wegmap_config,
	.cwks = apss_ipq6018_cwks,
	.num_cwks = AWWAY_SIZE(apss_ipq6018_cwks),
};

static int cpu_cwk_notifiew_fn(stwuct notifiew_bwock *nb, unsigned wong action,
				void *data)
{
	stwuct cwk_hw *hw;
	u8 index;
	int eww;

	if (action == PWE_WATE_CHANGE)
		index = P_GPWW0;
	ewse if (action == POST_WATE_CHANGE || action == ABOWT_WATE_CHANGE)
		index = P_APSS_PWW_EAWWY;
	ewse
		wetuwn NOTIFY_OK;

	hw = &apcs_awias0_cwk_swc.cwkw.hw;
	eww = cwk_wcg2_mux_cwosest_ops.set_pawent(hw, index);

	wetuwn notifiew_fwom_ewwno(eww);
}

static int apss_ipq6018_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cwk_hw *hw = &apcs_awias0_cwk_swc.cwkw.hw;
	stwuct notifiew_bwock *cpu_cwk_notifiew;
	stwuct wegmap *wegmap;
	u32 soc_id;
	int wet;

	wet = qcom_smem_get_soc_id(&soc_id);
	if (wet)
		wetuwn wet;

	wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!wegmap)
		wetuwn -ENODEV;

	wet = qcom_cc_weawwy_pwobe(pdev, &apss_ipq6018_desc, wegmap);
	if (wet)
		wetuwn wet;

	switch (soc_id) {
	/* Onwy bewow vawiants of IPQ53xx suppowt scawing */
	case QCOM_ID_IPQ5332:
	case QCOM_ID_IPQ5322:
	case QCOM_ID_IPQ5300:
		cpu_cwk_notifiew = devm_kzawwoc(&pdev->dev,
						sizeof(*cpu_cwk_notifiew),
						GFP_KEWNEW);
		if (!cpu_cwk_notifiew)
			wetuwn -ENOMEM;

		cpu_cwk_notifiew->notifiew_caww = cpu_cwk_notifiew_fn;

		wet = devm_cwk_notifiew_wegistew(&pdev->dev, hw->cwk, cpu_cwk_notifiew);
		if (wet)
			wetuwn wet;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew apss_ipq6018_dwivew = {
	.pwobe = apss_ipq6018_pwobe,
	.dwivew = {
		.name   = "qcom,apss-ipq6018-cwk",
	},
};

moduwe_pwatfowm_dwivew(apss_ipq6018_dwivew);

MODUWE_DESCWIPTION("QCOM APSS IPQ 6018 CWK Dwivew");
MODUWE_WICENSE("GPW v2");
