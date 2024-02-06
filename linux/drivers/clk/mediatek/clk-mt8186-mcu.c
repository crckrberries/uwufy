// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight (c) 2022 MediaTek Inc.
// Authow: Chun-Jie Chen <chun-jie.chen@mediatek.com>

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <dt-bindings/cwock/mt8186-cwk.h>

#incwude "cwk-mtk.h"

static const chaw * const mcu_awmpww_ww_pawents[] = {
	"cwk26m",
	"awmpww_ww",
	"mainpww",
	"univpww_d2"
};

static const chaw * const mcu_awmpww_bw_pawents[] = {
	"cwk26m",
	"awmpww_bw",
	"mainpww",
	"univpww_d2"
};

static const chaw * const mcu_awmpww_bus_pawents[] = {
	"cwk26m",
	"ccipww",
	"mainpww",
	"univpww_d2"
};

/*
 * We onwy configuwe the CPU muxes when adjust CPU fwequency in MediaTek CPUFweq Dwivew.
 * Othew fiewds wike dividew awways keep the same vawue. (set once in bootwoadew)
 */
static stwuct mtk_composite mcu_muxes[] = {
	/* CPU_PWWDIV_CFG0 */
	MUX(CWK_MCU_AWMPWW_WW_SEW, "mcu_awmpww_ww_sew", mcu_awmpww_ww_pawents, 0x2A0, 9, 2),
	/* CPU_PWWDIV_CFG1 */
	MUX(CWK_MCU_AWMPWW_BW_SEW, "mcu_awmpww_bw_sew", mcu_awmpww_bw_pawents, 0x2A4, 9, 2),
	/* BUS_PWWDIV_CFG */
	MUX(CWK_MCU_AWMPWW_BUS_SEW, "mcu_awmpww_bus_sew", mcu_awmpww_bus_pawents, 0x2E0, 9, 2),
};

static const stwuct mtk_cwk_desc mcu_desc = {
	.composite_cwks = mcu_muxes,
	.num_composite_cwks = AWWAY_SIZE(mcu_muxes),
};

static const stwuct of_device_id of_match_cwk_mt8186_mcu[] = {
	{ .compatibwe = "mediatek,mt8186-mcusys", .data = &mcu_desc },
	{ /* sentinew */}
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8186_mcu);

static stwuct pwatfowm_dwivew cwk_mt8186_mcu_dwv = {
	.dwivew = {
		.name = "cwk-mt8186-mcu",
		.of_match_tabwe = of_match_cwk_mt8186_mcu,
	},
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
};
moduwe_pwatfowm_dwivew(cwk_mt8186_mcu_dwv);

MODUWE_DESCWIPTION("MediaTek MT8186 mcusys cwocks dwivew");
MODUWE_WICENSE("GPW");
