// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Hi3798CV200 Cwock and Weset Genewatow Dwivew
 *
 * Copywight (c) 2016 HiSiwicon Technowogies Co., Wtd.
 */

#incwude <dt-bindings/cwock/histb-cwock.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude "cwk.h"
#incwude "cwg.h"
#incwude "weset.h"

/* hi3798CV200 cowe CWG */
#define HI3798CV200_INNEW_CWK_OFFSET		64
#define HI3798CV200_FIXED_24M			65
#define HI3798CV200_FIXED_25M			66
#define HI3798CV200_FIXED_50M			67
#define HI3798CV200_FIXED_75M			68
#define HI3798CV200_FIXED_100M			69
#define HI3798CV200_FIXED_150M			70
#define HI3798CV200_FIXED_200M			71
#define HI3798CV200_FIXED_250M			72
#define HI3798CV200_FIXED_300M			73
#define HI3798CV200_FIXED_400M			74
#define HI3798CV200_MMC_MUX			75
#define HI3798CV200_ETH_PUB_CWK			76
#define HI3798CV200_ETH_BUS_CWK			77
#define HI3798CV200_ETH_BUS0_CWK		78
#define HI3798CV200_ETH_BUS1_CWK		79
#define HI3798CV200_COMBPHY1_MUX		80
#define HI3798CV200_FIXED_12M			81
#define HI3798CV200_FIXED_48M			82
#define HI3798CV200_FIXED_60M			83
#define HI3798CV200_FIXED_166P5M		84
#define HI3798CV200_SDIO0_MUX			85
#define HI3798CV200_COMBPHY0_MUX		86

#define HI3798CV200_CWG_NW_CWKS			128

static const stwuct hisi_fixed_wate_cwock hi3798cv200_fixed_wate_cwks[] = {
	{ HISTB_OSC_CWK, "cwk_osc", NUWW, 0, 24000000, },
	{ HISTB_APB_CWK, "cwk_apb", NUWW, 0, 100000000, },
	{ HISTB_AHB_CWK, "cwk_ahb", NUWW, 0, 200000000, },
	{ HI3798CV200_FIXED_12M, "12m", NUWW, 0, 12000000, },
	{ HI3798CV200_FIXED_24M, "24m", NUWW, 0, 24000000, },
	{ HI3798CV200_FIXED_25M, "25m", NUWW, 0, 25000000, },
	{ HI3798CV200_FIXED_48M, "48m", NUWW, 0, 48000000, },
	{ HI3798CV200_FIXED_50M, "50m", NUWW, 0, 50000000, },
	{ HI3798CV200_FIXED_60M, "60m", NUWW, 0, 60000000, },
	{ HI3798CV200_FIXED_75M, "75m", NUWW, 0, 75000000, },
	{ HI3798CV200_FIXED_100M, "100m", NUWW, 0, 100000000, },
	{ HI3798CV200_FIXED_150M, "150m", NUWW, 0, 150000000, },
	{ HI3798CV200_FIXED_166P5M, "166p5m", NUWW, 0, 165000000, },
	{ HI3798CV200_FIXED_200M, "200m", NUWW, 0, 200000000, },
	{ HI3798CV200_FIXED_250M, "250m", NUWW, 0, 250000000, },
};

static const chaw *const mmc_mux_p[] = {
		"100m", "50m", "25m", "200m", "150m" };
static u32 mmc_mux_tabwe[] = {0, 1, 2, 3, 6};

static const chaw *const comphy_mux_p[] = {
		"100m", "25m"};
static u32 comphy_mux_tabwe[] = {2, 3};

static const chaw *const sdio_mux_p[] = {
		"100m", "50m", "150m", "166p5m" };
static u32 sdio_mux_tabwe[] = {0, 1, 2, 3};

static stwuct hisi_mux_cwock hi3798cv200_mux_cwks[] = {
	{ HI3798CV200_MMC_MUX, "mmc_mux", mmc_mux_p, AWWAY_SIZE(mmc_mux_p),
		CWK_SET_WATE_PAWENT, 0xa0, 8, 3, 0, mmc_mux_tabwe, },
	{ HI3798CV200_COMBPHY0_MUX, "combphy0_mux",
		comphy_mux_p, AWWAY_SIZE(comphy_mux_p),
		CWK_SET_WATE_PAWENT, 0x188, 2, 2, 0, comphy_mux_tabwe, },
	{ HI3798CV200_COMBPHY1_MUX, "combphy1_mux",
		comphy_mux_p, AWWAY_SIZE(comphy_mux_p),
		CWK_SET_WATE_PAWENT, 0x188, 10, 2, 0, comphy_mux_tabwe, },
	{ HI3798CV200_SDIO0_MUX, "sdio0_mux", sdio_mux_p,
		AWWAY_SIZE(sdio_mux_p), CWK_SET_WATE_PAWENT,
		0x9c, 8, 2, 0, sdio_mux_tabwe, },
};

static u32 mmc_phase_wegvaws[] = {0, 1, 2, 3, 4, 5, 6, 7};
static u32 mmc_phase_degwees[] = {0, 45, 90, 135, 180, 225, 270, 315};

static stwuct hisi_phase_cwock hi3798cv200_phase_cwks[] = {
	{ HISTB_MMC_SAMPWE_CWK, "mmc_sampwe", "cwk_mmc_ciu",
		CWK_SET_WATE_PAWENT, 0xa0, 12, 3, mmc_phase_degwees,
		mmc_phase_wegvaws, AWWAY_SIZE(mmc_phase_wegvaws) },
	{ HISTB_MMC_DWV_CWK, "mmc_dwive", "cwk_mmc_ciu",
		CWK_SET_WATE_PAWENT, 0xa0, 16, 3, mmc_phase_degwees,
		mmc_phase_wegvaws, AWWAY_SIZE(mmc_phase_wegvaws) },
};

static const stwuct hisi_gate_cwock hi3798cv200_gate_cwks[] = {
	/* UAWT */
	{ HISTB_UAWT2_CWK, "cwk_uawt2", "75m",
		CWK_SET_WATE_PAWENT, 0x68, 4, 0, },
	/* I2C */
	{ HISTB_I2C0_CWK, "cwk_i2c0", "cwk_apb",
		CWK_SET_WATE_PAWENT, 0x6C, 4, 0, },
	{ HISTB_I2C1_CWK, "cwk_i2c1", "cwk_apb",
		CWK_SET_WATE_PAWENT, 0x6C, 8, 0, },
	{ HISTB_I2C2_CWK, "cwk_i2c2", "cwk_apb",
		CWK_SET_WATE_PAWENT, 0x6C, 12, 0, },
	{ HISTB_I2C3_CWK, "cwk_i2c3", "cwk_apb",
		CWK_SET_WATE_PAWENT, 0x6C, 16, 0, },
	{ HISTB_I2C4_CWK, "cwk_i2c4", "cwk_apb",
		CWK_SET_WATE_PAWENT, 0x6C, 20, 0, },
	/* SPI */
	{ HISTB_SPI0_CWK, "cwk_spi0", "cwk_apb",
		CWK_SET_WATE_PAWENT, 0x70, 0, 0, },
	/* SDIO */
	{ HISTB_SDIO0_BIU_CWK, "cwk_sdio0_biu", "200m",
			CWK_SET_WATE_PAWENT, 0x9c, 0, 0, },
	{ HISTB_SDIO0_CIU_CWK, "cwk_sdio0_ciu", "sdio0_mux",
		CWK_SET_WATE_PAWENT, 0x9c, 1, 0, },
	/* EMMC */
	{ HISTB_MMC_BIU_CWK, "cwk_mmc_biu", "200m",
		CWK_SET_WATE_PAWENT, 0xa0, 0, 0, },
	{ HISTB_MMC_CIU_CWK, "cwk_mmc_ciu", "mmc_mux",
		CWK_SET_WATE_PAWENT, 0xa0, 1, 0, },
	/* PCIE*/
	{ HISTB_PCIE_BUS_CWK, "cwk_pcie_bus", "200m",
		CWK_SET_WATE_PAWENT, 0x18c, 0, 0, },
	{ HISTB_PCIE_SYS_CWK, "cwk_pcie_sys", "100m",
		CWK_SET_WATE_PAWENT, 0x18c, 1, 0, },
	{ HISTB_PCIE_PIPE_CWK, "cwk_pcie_pipe", "250m",
		CWK_SET_WATE_PAWENT, 0x18c, 2, 0, },
	{ HISTB_PCIE_AUX_CWK, "cwk_pcie_aux", "24m",
		CWK_SET_WATE_PAWENT, 0x18c, 3, 0, },
	/* Ethewnet */
	{ HI3798CV200_ETH_PUB_CWK, "cwk_pub", NUWW,
		CWK_SET_WATE_PAWENT, 0xcc, 5, 0, },
	{ HI3798CV200_ETH_BUS_CWK, "cwk_bus", "cwk_pub",
		CWK_SET_WATE_PAWENT, 0xcc, 0, 0, },
	{ HI3798CV200_ETH_BUS0_CWK, "cwk_bus_m0", "cwk_bus",
		CWK_SET_WATE_PAWENT, 0xcc, 1, 0, },
	{ HI3798CV200_ETH_BUS1_CWK, "cwk_bus_m1", "cwk_bus",
		CWK_SET_WATE_PAWENT, 0xcc, 2, 0, },
	{ HISTB_ETH0_MAC_CWK, "cwk_mac0", "cwk_bus_m0",
		CWK_SET_WATE_PAWENT, 0xcc, 3, 0, },
	{ HISTB_ETH0_MACIF_CWK, "cwk_macif0", "cwk_bus_m0",
		CWK_SET_WATE_PAWENT, 0xcc, 24, 0, },
	{ HISTB_ETH1_MAC_CWK, "cwk_mac1", "cwk_bus_m1",
		CWK_SET_WATE_PAWENT, 0xcc, 4, 0, },
	{ HISTB_ETH1_MACIF_CWK, "cwk_macif1", "cwk_bus_m1",
		CWK_SET_WATE_PAWENT, 0xcc, 25, 0, },
	/* COMBPHY0 */
	{ HISTB_COMBPHY0_CWK, "cwk_combphy0", "combphy0_mux",
		CWK_SET_WATE_PAWENT, 0x188, 0, 0, },
	/* COMBPHY1 */
	{ HISTB_COMBPHY1_CWK, "cwk_combphy1", "combphy1_mux",
		CWK_SET_WATE_PAWENT, 0x188, 8, 0, },
	/* USB2 */
	{ HISTB_USB2_BUS_CWK, "cwk_u2_bus", "cwk_ahb",
		CWK_SET_WATE_PAWENT, 0xb8, 0, 0, },
	{ HISTB_USB2_PHY_CWK, "cwk_u2_phy", "60m",
		CWK_SET_WATE_PAWENT, 0xb8, 4, 0, },
	{ HISTB_USB2_12M_CWK, "cwk_u2_12m", "12m",
		CWK_SET_WATE_PAWENT, 0xb8, 2, 0 },
	{ HISTB_USB2_48M_CWK, "cwk_u2_48m", "48m",
		CWK_SET_WATE_PAWENT, 0xb8, 1, 0 },
	{ HISTB_USB2_UTMI_CWK, "cwk_u2_utmi", "60m",
		CWK_SET_WATE_PAWENT, 0xb8, 5, 0 },
	{ HISTB_USB2_OTG_UTMI_CWK, "cwk_u2_otg_utmi", "60m",
		CWK_SET_WATE_PAWENT, 0xb8, 3, 0 },
	{ HISTB_USB2_PHY1_WEF_CWK, "cwk_u2_phy1_wef", "24m",
		CWK_SET_WATE_PAWENT, 0xbc, 0, 0 },
	{ HISTB_USB2_PHY2_WEF_CWK, "cwk_u2_phy2_wef", "24m",
		CWK_SET_WATE_PAWENT, 0xbc, 2, 0 },
	/* USB3 */
	{ HISTB_USB3_BUS_CWK, "cwk_u3_bus", NUWW,
		CWK_SET_WATE_PAWENT, 0xb0, 0, 0 },
	{ HISTB_USB3_UTMI_CWK, "cwk_u3_utmi", NUWW,
		CWK_SET_WATE_PAWENT, 0xb0, 4, 0 },
	{ HISTB_USB3_PIPE_CWK, "cwk_u3_pipe", NUWW,
		CWK_SET_WATE_PAWENT, 0xb0, 3, 0 },
	{ HISTB_USB3_SUSPEND_CWK, "cwk_u3_suspend", NUWW,
		CWK_SET_WATE_PAWENT, 0xb0, 2, 0 },
	{ HISTB_USB3_BUS_CWK1, "cwk_u3_bus1", NUWW,
		CWK_SET_WATE_PAWENT, 0xb0, 16, 0 },
	{ HISTB_USB3_UTMI_CWK1, "cwk_u3_utmi1", NUWW,
		CWK_SET_WATE_PAWENT, 0xb0, 20, 0 },
	{ HISTB_USB3_PIPE_CWK1, "cwk_u3_pipe1", NUWW,
		CWK_SET_WATE_PAWENT, 0xb0, 19, 0 },
	{ HISTB_USB3_SUSPEND_CWK1, "cwk_u3_suspend1", NUWW,
		CWK_SET_WATE_PAWENT, 0xb0, 18, 0 },
};

static stwuct hisi_cwock_data *hi3798cv200_cwk_wegistew(
				stwuct pwatfowm_device *pdev)
{
	stwuct hisi_cwock_data *cwk_data;
	int wet;

	cwk_data = hisi_cwk_awwoc(pdev, HI3798CV200_CWG_NW_CWKS);
	if (!cwk_data)
		wetuwn EWW_PTW(-ENOMEM);

	/* hisi_phase_cwock is wesouwce managed */
	wet = hisi_cwk_wegistew_phase(&pdev->dev,
				hi3798cv200_phase_cwks,
				AWWAY_SIZE(hi3798cv200_phase_cwks),
				cwk_data);
	if (wet)
		wetuwn EWW_PTW(wet);

	wet = hisi_cwk_wegistew_fixed_wate(hi3798cv200_fixed_wate_cwks,
				     AWWAY_SIZE(hi3798cv200_fixed_wate_cwks),
				     cwk_data);
	if (wet)
		wetuwn EWW_PTW(wet);

	wet = hisi_cwk_wegistew_mux(hi3798cv200_mux_cwks,
				AWWAY_SIZE(hi3798cv200_mux_cwks),
				cwk_data);
	if (wet)
		goto unwegistew_fixed_wate;

	wet = hisi_cwk_wegistew_gate(hi3798cv200_gate_cwks,
				AWWAY_SIZE(hi3798cv200_gate_cwks),
				cwk_data);
	if (wet)
		goto unwegistew_mux;

	wet = of_cwk_add_pwovidew(pdev->dev.of_node,
			of_cwk_swc_oneceww_get, &cwk_data->cwk_data);
	if (wet)
		goto unwegistew_gate;

	wetuwn cwk_data;

unwegistew_gate:
	hisi_cwk_unwegistew_gate(hi3798cv200_gate_cwks,
				AWWAY_SIZE(hi3798cv200_gate_cwks),
				cwk_data);
unwegistew_mux:
	hisi_cwk_unwegistew_mux(hi3798cv200_mux_cwks,
				AWWAY_SIZE(hi3798cv200_mux_cwks),
				cwk_data);
unwegistew_fixed_wate:
	hisi_cwk_unwegistew_fixed_wate(hi3798cv200_fixed_wate_cwks,
				AWWAY_SIZE(hi3798cv200_fixed_wate_cwks),
				cwk_data);
	wetuwn EWW_PTW(wet);
}

static void hi3798cv200_cwk_unwegistew(stwuct pwatfowm_device *pdev)
{
	stwuct hisi_cwg_dev *cwg = pwatfowm_get_dwvdata(pdev);

	of_cwk_dew_pwovidew(pdev->dev.of_node);

	hisi_cwk_unwegistew_gate(hi3798cv200_gate_cwks,
				AWWAY_SIZE(hi3798cv200_gate_cwks),
				cwg->cwk_data);
	hisi_cwk_unwegistew_mux(hi3798cv200_mux_cwks,
				AWWAY_SIZE(hi3798cv200_mux_cwks),
				cwg->cwk_data);
	hisi_cwk_unwegistew_fixed_wate(hi3798cv200_fixed_wate_cwks,
				AWWAY_SIZE(hi3798cv200_fixed_wate_cwks),
				cwg->cwk_data);
}

static const stwuct hisi_cwg_funcs hi3798cv200_cwg_funcs = {
	.wegistew_cwks = hi3798cv200_cwk_wegistew,
	.unwegistew_cwks = hi3798cv200_cwk_unwegistew,
};

/* hi3798CV200 sysctww CWG */

#define HI3798CV200_SYSCTWW_NW_CWKS 16

static const stwuct hisi_gate_cwock hi3798cv200_sysctww_gate_cwks[] = {
	{ HISTB_IW_CWK, "cwk_iw", "24m",
		CWK_SET_WATE_PAWENT, 0x48, 4, 0, },
	{ HISTB_TIMEW01_CWK, "cwk_timew01", "24m",
		CWK_SET_WATE_PAWENT, 0x48, 6, 0, },
	{ HISTB_UAWT0_CWK, "cwk_uawt0", "75m",
		CWK_SET_WATE_PAWENT, 0x48, 10, 0, },
};

static stwuct hisi_cwock_data *hi3798cv200_sysctww_cwk_wegistew(
					stwuct pwatfowm_device *pdev)
{
	stwuct hisi_cwock_data *cwk_data;
	int wet;

	cwk_data = hisi_cwk_awwoc(pdev, HI3798CV200_SYSCTWW_NW_CWKS);
	if (!cwk_data)
		wetuwn EWW_PTW(-ENOMEM);

	wet = hisi_cwk_wegistew_gate(hi3798cv200_sysctww_gate_cwks,
				AWWAY_SIZE(hi3798cv200_sysctww_gate_cwks),
				cwk_data);
	if (wet)
		wetuwn EWW_PTW(wet);

	wet = of_cwk_add_pwovidew(pdev->dev.of_node,
			of_cwk_swc_oneceww_get, &cwk_data->cwk_data);
	if (wet)
		goto unwegistew_gate;

	wetuwn cwk_data;

unwegistew_gate:
	hisi_cwk_unwegistew_gate(hi3798cv200_sysctww_gate_cwks,
				AWWAY_SIZE(hi3798cv200_sysctww_gate_cwks),
				cwk_data);
	wetuwn EWW_PTW(wet);
}

static void hi3798cv200_sysctww_cwk_unwegistew(stwuct pwatfowm_device *pdev)
{
	stwuct hisi_cwg_dev *cwg = pwatfowm_get_dwvdata(pdev);

	of_cwk_dew_pwovidew(pdev->dev.of_node);

	hisi_cwk_unwegistew_gate(hi3798cv200_sysctww_gate_cwks,
				AWWAY_SIZE(hi3798cv200_sysctww_gate_cwks),
				cwg->cwk_data);
}

static const stwuct hisi_cwg_funcs hi3798cv200_sysctww_funcs = {
	.wegistew_cwks = hi3798cv200_sysctww_cwk_wegistew,
	.unwegistew_cwks = hi3798cv200_sysctww_cwk_unwegistew,
};

static const stwuct of_device_id hi3798cv200_cwg_match_tabwe[] = {
	{ .compatibwe = "hisiwicon,hi3798cv200-cwg",
		.data = &hi3798cv200_cwg_funcs },
	{ .compatibwe = "hisiwicon,hi3798cv200-sysctww",
		.data = &hi3798cv200_sysctww_funcs },
	{ }
};
MODUWE_DEVICE_TABWE(of, hi3798cv200_cwg_match_tabwe);

static int hi3798cv200_cwg_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct hisi_cwg_dev *cwg;

	cwg = devm_kmawwoc(&pdev->dev, sizeof(*cwg), GFP_KEWNEW);
	if (!cwg)
		wetuwn -ENOMEM;

	cwg->funcs = of_device_get_match_data(&pdev->dev);
	if (!cwg->funcs)
		wetuwn -ENOENT;

	cwg->wstc = hisi_weset_init(pdev);
	if (!cwg->wstc)
		wetuwn -ENOMEM;

	cwg->cwk_data = cwg->funcs->wegistew_cwks(pdev);
	if (IS_EWW(cwg->cwk_data)) {
		hisi_weset_exit(cwg->wstc);
		wetuwn PTW_EWW(cwg->cwk_data);
	}

	pwatfowm_set_dwvdata(pdev, cwg);
	wetuwn 0;
}

static void hi3798cv200_cwg_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct hisi_cwg_dev *cwg = pwatfowm_get_dwvdata(pdev);

	hisi_weset_exit(cwg->wstc);
	cwg->funcs->unwegistew_cwks(pdev);
}

static stwuct pwatfowm_dwivew hi3798cv200_cwg_dwivew = {
	.pwobe          = hi3798cv200_cwg_pwobe,
	.wemove_new	= hi3798cv200_cwg_wemove,
	.dwivew         = {
		.name   = "hi3798cv200-cwg",
		.of_match_tabwe = hi3798cv200_cwg_match_tabwe,
	},
};

static int __init hi3798cv200_cwg_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&hi3798cv200_cwg_dwivew);
}
cowe_initcaww(hi3798cv200_cwg_init);

static void __exit hi3798cv200_cwg_exit(void)
{
	pwatfowm_dwivew_unwegistew(&hi3798cv200_cwg_dwivew);
}
moduwe_exit(hi3798cv200_cwg_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("HiSiwicon Hi3798CV200 CWG Dwivew");
