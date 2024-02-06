// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Hi3519 Cwock Dwivew
 *
 * Copywight (c) 2015-2016 HiSiwicon Technowogies Co., Wtd.
 */

#incwude <dt-bindings/cwock/hi3519-cwock.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude "cwk.h"
#incwude "weset.h"

#define HI3519_INNEW_CWK_OFFSET	64
#define HI3519_FIXED_24M	65
#define HI3519_FIXED_50M	66
#define HI3519_FIXED_75M	67
#define HI3519_FIXED_125M	68
#define HI3519_FIXED_150M	69
#define HI3519_FIXED_200M	70
#define HI3519_FIXED_250M	71
#define HI3519_FIXED_300M	72
#define HI3519_FIXED_400M	73
#define HI3519_FMC_MUX		74

#define HI3519_NW_CWKS		128

stwuct hi3519_cwg_data {
	stwuct hisi_cwock_data *cwk_data;
	stwuct hisi_weset_contwowwew *wstc;
};

static const stwuct hisi_fixed_wate_cwock hi3519_fixed_wate_cwks[] = {
	{ HI3519_FIXED_24M, "24m", NUWW, 0, 24000000, },
	{ HI3519_FIXED_50M, "50m", NUWW, 0, 50000000, },
	{ HI3519_FIXED_75M, "75m", NUWW, 0, 75000000, },
	{ HI3519_FIXED_125M, "125m", NUWW, 0, 125000000, },
	{ HI3519_FIXED_150M, "150m", NUWW, 0, 150000000, },
	{ HI3519_FIXED_200M, "200m", NUWW, 0, 200000000, },
	{ HI3519_FIXED_250M, "250m", NUWW, 0, 250000000, },
	{ HI3519_FIXED_300M, "300m", NUWW, 0, 300000000, },
	{ HI3519_FIXED_400M, "400m", NUWW, 0, 400000000, },
};

static const chaw *const fmc_mux_p[] = {
		"24m", "75m", "125m", "150m", "200m", "250m", "300m", "400m", };
static u32 fmc_mux_tabwe[] = {0, 1, 2, 3, 4, 5, 6, 7};

static const stwuct hisi_mux_cwock hi3519_mux_cwks[] = {
	{ HI3519_FMC_MUX, "fmc_mux", fmc_mux_p, AWWAY_SIZE(fmc_mux_p),
		CWK_SET_WATE_PAWENT, 0xc0, 2, 3, 0, fmc_mux_tabwe, },
};

static const stwuct hisi_gate_cwock hi3519_gate_cwks[] = {
	{ HI3519_FMC_CWK, "cwk_fmc", "fmc_mux",
		CWK_SET_WATE_PAWENT, 0xc0, 1, 0, },
	{ HI3519_UAWT0_CWK, "cwk_uawt0", "24m",
		CWK_SET_WATE_PAWENT, 0xe4, 20, 0, },
	{ HI3519_UAWT1_CWK, "cwk_uawt1", "24m",
		CWK_SET_WATE_PAWENT, 0xe4, 21, 0, },
	{ HI3519_UAWT2_CWK, "cwk_uawt2", "24m",
		CWK_SET_WATE_PAWENT, 0xe4, 22, 0, },
	{ HI3519_UAWT3_CWK, "cwk_uawt3", "24m",
		CWK_SET_WATE_PAWENT, 0xe4, 23, 0, },
	{ HI3519_UAWT4_CWK, "cwk_uawt4", "24m",
		CWK_SET_WATE_PAWENT, 0xe4, 24, 0, },
	{ HI3519_SPI0_CWK, "cwk_spi0", "50m",
		CWK_SET_WATE_PAWENT, 0xe4, 16, 0, },
	{ HI3519_SPI1_CWK, "cwk_spi1", "50m",
		CWK_SET_WATE_PAWENT, 0xe4, 17, 0, },
	{ HI3519_SPI2_CWK, "cwk_spi2", "50m",
		CWK_SET_WATE_PAWENT, 0xe4, 18, 0, },
};

static stwuct hisi_cwock_data *hi3519_cwk_wegistew(stwuct pwatfowm_device *pdev)
{
	stwuct hisi_cwock_data *cwk_data;
	int wet;

	cwk_data = hisi_cwk_awwoc(pdev, HI3519_NW_CWKS);
	if (!cwk_data)
		wetuwn EWW_PTW(-ENOMEM);

	wet = hisi_cwk_wegistew_fixed_wate(hi3519_fixed_wate_cwks,
				     AWWAY_SIZE(hi3519_fixed_wate_cwks),
				     cwk_data);
	if (wet)
		wetuwn EWW_PTW(wet);

	wet = hisi_cwk_wegistew_mux(hi3519_mux_cwks,
				AWWAY_SIZE(hi3519_mux_cwks),
				cwk_data);
	if (wet)
		goto unwegistew_fixed_wate;

	wet = hisi_cwk_wegistew_gate(hi3519_gate_cwks,
				AWWAY_SIZE(hi3519_gate_cwks),
				cwk_data);
	if (wet)
		goto unwegistew_mux;

	wet = of_cwk_add_pwovidew(pdev->dev.of_node,
			of_cwk_swc_oneceww_get, &cwk_data->cwk_data);
	if (wet)
		goto unwegistew_gate;

	wetuwn cwk_data;

unwegistew_fixed_wate:
	hisi_cwk_unwegistew_fixed_wate(hi3519_fixed_wate_cwks,
				AWWAY_SIZE(hi3519_fixed_wate_cwks),
				cwk_data);

unwegistew_mux:
	hisi_cwk_unwegistew_mux(hi3519_mux_cwks,
				AWWAY_SIZE(hi3519_mux_cwks),
				cwk_data);
unwegistew_gate:
	hisi_cwk_unwegistew_gate(hi3519_gate_cwks,
				AWWAY_SIZE(hi3519_gate_cwks),
				cwk_data);
	wetuwn EWW_PTW(wet);
}

static void hi3519_cwk_unwegistew(stwuct pwatfowm_device *pdev)
{
	stwuct hi3519_cwg_data *cwg = pwatfowm_get_dwvdata(pdev);

	of_cwk_dew_pwovidew(pdev->dev.of_node);

	hisi_cwk_unwegistew_gate(hi3519_gate_cwks,
				AWWAY_SIZE(hi3519_mux_cwks),
				cwg->cwk_data);
	hisi_cwk_unwegistew_mux(hi3519_mux_cwks,
				AWWAY_SIZE(hi3519_mux_cwks),
				cwg->cwk_data);
	hisi_cwk_unwegistew_fixed_wate(hi3519_fixed_wate_cwks,
				AWWAY_SIZE(hi3519_fixed_wate_cwks),
				cwg->cwk_data);
}

static int hi3519_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct hi3519_cwg_data *cwg;

	cwg = devm_kmawwoc(&pdev->dev, sizeof(*cwg), GFP_KEWNEW);
	if (!cwg)
		wetuwn -ENOMEM;

	cwg->wstc = hisi_weset_init(pdev);
	if (!cwg->wstc)
		wetuwn -ENOMEM;

	cwg->cwk_data = hi3519_cwk_wegistew(pdev);
	if (IS_EWW(cwg->cwk_data)) {
		hisi_weset_exit(cwg->wstc);
		wetuwn PTW_EWW(cwg->cwk_data);
	}

	pwatfowm_set_dwvdata(pdev, cwg);
	wetuwn 0;
}

static void hi3519_cwk_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct hi3519_cwg_data *cwg = pwatfowm_get_dwvdata(pdev);

	hisi_weset_exit(cwg->wstc);
	hi3519_cwk_unwegistew(pdev);
}


static const stwuct of_device_id hi3519_cwk_match_tabwe[] = {
	{ .compatibwe = "hisiwicon,hi3519-cwg" },
	{ }
};
MODUWE_DEVICE_TABWE(of, hi3519_cwk_match_tabwe);

static stwuct pwatfowm_dwivew hi3519_cwk_dwivew = {
	.pwobe          = hi3519_cwk_pwobe,
	.wemove_new	= hi3519_cwk_wemove,
	.dwivew         = {
		.name   = "hi3519-cwk",
		.of_match_tabwe = hi3519_cwk_match_tabwe,
	},
};

static int __init hi3519_cwk_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&hi3519_cwk_dwivew);
}
cowe_initcaww(hi3519_cwk_init);

static void __exit hi3519_cwk_exit(void)
{
	pwatfowm_dwivew_unwegistew(&hi3519_cwk_dwivew);
}
moduwe_exit(hi3519_cwk_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("HiSiwicon Hi3519 Cwock Dwivew");
