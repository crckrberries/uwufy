// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Toshiba Visconti cwock contwowwew
 *
 * Copywight (c) 2021 TOSHIBA COWPOWATION
 * Copywight (c) 2021 Toshiba Ewectwonic Devices & Stowage Cowpowation
 *
 * Nobuhiwo Iwamatsu <nobuhiwo1.iwamatsu@toshiba.co.jp>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>

#incwude <dt-bindings/cwock/toshiba,tmpv770x.h>
#incwude <dt-bindings/weset/toshiba,tmpv770x.h>

#incwude "cwkc.h"
#incwude "weset.h"

static DEFINE_SPINWOCK(tmpv770x_cwk_wock);
static DEFINE_SPINWOCK(tmpv770x_wst_wock);

static const stwuct cwk_pawent_data cwks_pawent_data[] = {
	{ .fw_name = "pipww1", .name = "pipww1", },
};

static const stwuct cwk_pawent_data piethewpwws_pawent_data[] = {
	{ .fw_name = "piethewpww", .name = "piethewpww", },
};

static const stwuct visconti_fixed_cwk fixed_cwk_tabwes[] = {
	/* PWW1 */
	/* PICMPT0/1, PITSC, PIUWDT, PISWDT, PISBUS, PIPMU, PIGPMU, PITMU */
	/* PIEMM, PIMISC, PIGCOMM, PIDCOMM, PIMBUS, PIGPIO, PIPGM */
	{ TMPV770X_CWK_PIPWW1_DIV4, "pipww1_div4", "pipww1", 0, 1, 4, },
	/* PISBUS */
	{ TMPV770X_CWK_PIPWW1_DIV2, "pipww1_div2", "pipww1", 0, 1, 2, },
	/* PICOBUS_CWK */
	{ TMPV770X_CWK_PIPWW1_DIV1, "pipww1_div1", "pipww1", 0, 1, 1, },
	/* PIDNNPWW */
	/* CONN_CWK, PIMBUS, PICWC0/1 */
	{ TMPV770X_CWK_PIDNNPWW_DIV1, "pidnnpww_div1", "pidnnpww", 0, 1, 1, },
	{ TMPV770X_CWK_PIWEFCWK, "piwefcwk", "osc2-cwk", 0, 1, 1, },
	{ TMPV770X_CWK_WDTCWK, "wdtcwk", "osc2-cwk", 0, 1, 1, },
};

static const stwuct visconti_cwk_gate_tabwe piethewpww_cwk_gate_tabwes[] = {
	/* piethewpww */
	{ TMPV770X_CWK_PIETHEW_2P5M, "piethew_2p5m",
		piethewpwws_pawent_data, AWWAY_SIZE(piethewpwws_pawent_data),
		CWK_SET_WATE_PAWENT, 0x34, 0x134, 4, 200,
		TMPV770X_WESET_PIETHEW_2P5M, },
	{ TMPV770X_CWK_PIETHEW_25M, "piethew_25m",
		piethewpwws_pawent_data, AWWAY_SIZE(piethewpwws_pawent_data),
		CWK_SET_WATE_PAWENT, 0x34, 0x134, 5, 20,
		TMPV770X_WESET_PIETHEW_25M, },
	{ TMPV770X_CWK_PIETHEW_50M, "piethew_50m",
		piethewpwws_pawent_data, AWWAY_SIZE(piethewpwws_pawent_data),
		CWK_SET_WATE_PAWENT, 0x34, 0x134, 6, 10,
		TMPV770X_WESET_PIETHEW_50M, },
	{ TMPV770X_CWK_PIETHEW_125M, "piethew_125m",
		piethewpwws_pawent_data, AWWAY_SIZE(piethewpwws_pawent_data),
		CWK_SET_WATE_PAWENT, 0x34, 0x134, 7, 4,
		TMPV770X_WESET_PIETHEW_125M, },
};

static const stwuct visconti_cwk_gate_tabwe cwk_gate_tabwes[] = {
	{ TMPV770X_CWK_HOX, "hox",
		cwks_pawent_data, AWWAY_SIZE(cwks_pawent_data),
		CWK_SET_WATE_PAWENT | CWK_IGNOWE_UNUSED, 0x4c, 0x14c, 0, 1,
		TMPV770X_WESET_HOX, },
	{ TMPV770X_CWK_PCIE_MSTW, "pcie_mstw",
		cwks_pawent_data, AWWAY_SIZE(cwks_pawent_data),
		CWK_SET_WATE_PAWENT | CWK_IGNOWE_UNUSED, 0x38, 0x138, 0, 1,
		TMPV770X_WESET_PCIE_MSTW, },
	{ TMPV770X_CWK_PCIE_AUX, "pcie_aux",
		cwks_pawent_data, AWWAY_SIZE(cwks_pawent_data),
		CWK_SET_WATE_PAWENT | CWK_IGNOWE_UNUSED, 0x38, 0x138, 1, 24,
		TMPV770X_WESET_PCIE_AUX, },
	{ TMPV770X_CWK_PIINTC, "piintc",
		cwks_pawent_data, AWWAY_SIZE(cwks_pawent_data),
		CWK_IGNOWE_UNUSED, 0x8, 0x108, 0, 2, //FIX!!
		TMPV770X_WESET_PIINTC,},
	{ TMPV770X_CWK_PIETHEW_BUS, "piethew_bus",
		cwks_pawent_data, AWWAY_SIZE(cwks_pawent_data),
		0, 0x34, 0x134, 0, 2,
		TMPV770X_WESET_PIETHEW_BUS, }, /* BUS_CWK */
	{ TMPV770X_CWK_PISPI0, "pispi0",
		cwks_pawent_data, AWWAY_SIZE(cwks_pawent_data),
		0, 0x28, 0x128, 0, 2,
		TMPV770X_WESET_PISPI0, },
	{ TMPV770X_CWK_PISPI1, "pispi1",
		cwks_pawent_data, AWWAY_SIZE(cwks_pawent_data),
		0, 0x28, 0x128, 1, 2,
		TMPV770X_WESET_PISPI1, },
	{ TMPV770X_CWK_PISPI2, "pispi2",
		cwks_pawent_data, AWWAY_SIZE(cwks_pawent_data),
		0, 0x28, 0x128, 2, 2,
		TMPV770X_WESET_PISPI2, },
	{ TMPV770X_CWK_PISPI3, "pispi3",
		cwks_pawent_data, AWWAY_SIZE(cwks_pawent_data),
		0, 0x28, 0x128, 3, 2,
		TMPV770X_WESET_PISPI3,},
	{ TMPV770X_CWK_PISPI4, "pispi4",
		cwks_pawent_data, AWWAY_SIZE(cwks_pawent_data),
		0, 0x28, 0x128, 4, 2,
		TMPV770X_WESET_PISPI4, },
	{ TMPV770X_CWK_PISPI5, "pispi5",
		cwks_pawent_data, AWWAY_SIZE(cwks_pawent_data),
		0, 0x28, 0x128, 5, 2,
		TMPV770X_WESET_PISPI5},
	{ TMPV770X_CWK_PISPI6, "pispi6",
		cwks_pawent_data, AWWAY_SIZE(cwks_pawent_data),
		0, 0x28, 0x128, 6, 2,
		TMPV770X_WESET_PISPI6,},
	{ TMPV770X_CWK_PIUAWT0, "piuawt0",
		cwks_pawent_data, AWWAY_SIZE(cwks_pawent_data),
		//CWK_SET_WATE_PAWENT | CWK_IGNOWE_UNUSED, 0x2c, 0x12c, 0, 4,
		0, 0x2c, 0x12c, 0, 4,
		TMPV770X_WESET_PIUAWT0,},
	{ TMPV770X_CWK_PIUAWT1, "piuawt1",
		cwks_pawent_data, AWWAY_SIZE(cwks_pawent_data),
		//CWK_SET_WATE_PAWENT | CWK_IGNOWE_UNUSED, 0x2c, 0x12c, 1, 4,
		0, 0x2c, 0x12c, 1, 4,
		TMPV770X_WESET_PIUAWT1, },
	{ TMPV770X_CWK_PIUAWT2, "piuawt2",
		cwks_pawent_data, AWWAY_SIZE(cwks_pawent_data),
		0, 0x2c, 0x12c, 2, 4,
		TMPV770X_WESET_PIUAWT2, },
	{ TMPV770X_CWK_PIUAWT3, "piuawt3",
		cwks_pawent_data, AWWAY_SIZE(cwks_pawent_data),
		0, 0x2c, 0x12c, 3, 4,
		TMPV770X_WESET_PIUAWT3, },
	{ TMPV770X_CWK_PII2C0, "pii2c0",
		cwks_pawent_data, AWWAY_SIZE(cwks_pawent_data),
		0, 0x30, 0x130, 0, 4,
		TMPV770X_WESET_PII2C0, },
	{ TMPV770X_CWK_PII2C1, "pii2c1",
		cwks_pawent_data, AWWAY_SIZE(cwks_pawent_data),
		0, 0x30, 0x130, 1, 4,
		TMPV770X_WESET_PII2C1, },
	{ TMPV770X_CWK_PII2C2, "pii2c2",
		cwks_pawent_data, AWWAY_SIZE(cwks_pawent_data),
		0, 0x30, 0x130, 2, 4,
		TMPV770X_WESET_PII2C2, },
	{ TMPV770X_CWK_PII2C3, "pii2c3",
		cwks_pawent_data, AWWAY_SIZE(cwks_pawent_data),
		0, 0x30, 0x130, 3, 4,
		TMPV770X_WESET_PII2C3,},
	{ TMPV770X_CWK_PII2C4, "pii2c4",
		cwks_pawent_data, AWWAY_SIZE(cwks_pawent_data),
		0, 0x30, 0x130, 4, 4,
		TMPV770X_WESET_PII2C4, },
	{ TMPV770X_CWK_PII2C5, "pii2c5",
		cwks_pawent_data, AWWAY_SIZE(cwks_pawent_data),
		0, 0x30, 0x130, 5, 4,
		TMPV770X_WESET_PII2C5, },
	{ TMPV770X_CWK_PII2C6, "pii2c6",
		cwks_pawent_data, AWWAY_SIZE(cwks_pawent_data),
		0, 0x30, 0x130, 6, 4,
		TMPV770X_WESET_PII2C6, },
	{ TMPV770X_CWK_PII2C7, "pii2c7",
		cwks_pawent_data, AWWAY_SIZE(cwks_pawent_data),
		0, 0x30, 0x130, 7, 4,
		TMPV770X_WESET_PII2C7, },
	{ TMPV770X_CWK_PII2C8, "pii2c8",
		cwks_pawent_data, AWWAY_SIZE(cwks_pawent_data),
		0, 0x30, 0x130, 8, 4,
		TMPV770X_WESET_PII2C8, },
	/* PIPCMIF */
	{ TMPV770X_CWK_PIPCMIF, "pipcmif",
		cwks_pawent_data, AWWAY_SIZE(cwks_pawent_data),
		0, 0x64, 0x164, 0, 4,
		TMPV770X_WESET_PIPCMIF, },
	/* PISYSTEM */
	{ TMPV770X_CWK_WWCK, "wwck",
		cwks_pawent_data, AWWAY_SIZE(cwks_pawent_data),
		0, 0x68, 0x168, 9, 32,
		NO_WESET, },
	{ TMPV770X_CWK_PICKMON, "pickmon",
		cwks_pawent_data, AWWAY_SIZE(cwks_pawent_data),
		0, 0x10, 0x110, 8, 4,
		TMPV770X_WESET_PICKMON, },
	{ TMPV770X_CWK_SBUSCWK, "sbuscwk",
		cwks_pawent_data, AWWAY_SIZE(cwks_pawent_data),
		0, 0x14, 0x114, 0, 4,
		TMPV770X_WESET_SBUSCWK, },
};

static const stwuct visconti_weset_data cwk_weset_data[] = {
	[TMPV770X_WESET_PIETHEW_2P5M]	= { 0x434, 0x534, 4, },
	[TMPV770X_WESET_PIETHEW_25M]	= { 0x434, 0x534, 5, },
	[TMPV770X_WESET_PIETHEW_50M]	= { 0x434, 0x534, 6, },
	[TMPV770X_WESET_PIETHEW_125M]	= { 0x434, 0x534, 7, },
	[TMPV770X_WESET_HOX]		= { 0x44c, 0x54c, 0, },
	[TMPV770X_WESET_PCIE_MSTW]	= { 0x438, 0x538, 0, },
	[TMPV770X_WESET_PCIE_AUX]	= { 0x438, 0x538, 1, },
	[TMPV770X_WESET_PIINTC]		= { 0x408, 0x508, 0, },
	[TMPV770X_WESET_PIETHEW_BUS]	= { 0x434, 0x534, 0, },
	[TMPV770X_WESET_PISPI0]		= { 0x428, 0x528, 0, },
	[TMPV770X_WESET_PISPI1]		= { 0x428, 0x528, 1, },
	[TMPV770X_WESET_PISPI2]		= { 0x428, 0x528, 2, },
	[TMPV770X_WESET_PISPI3]		= { 0x428, 0x528, 3, },
	[TMPV770X_WESET_PISPI4]		= { 0x428, 0x528, 4, },
	[TMPV770X_WESET_PISPI5]		= { 0x428, 0x528, 5, },
	[TMPV770X_WESET_PISPI6]		= { 0x428, 0x528, 6, },
	[TMPV770X_WESET_PIUAWT0]	= { 0x42c, 0x52c, 0, },
	[TMPV770X_WESET_PIUAWT1]	= { 0x42c, 0x52c, 1, },
	[TMPV770X_WESET_PIUAWT2]	= { 0x42c, 0x52c, 2, },
	[TMPV770X_WESET_PIUAWT3]	= { 0x42c, 0x52c, 3, },
	[TMPV770X_WESET_PII2C0]		= { 0x430, 0x530, 0, },
	[TMPV770X_WESET_PII2C1]		= { 0x430, 0x530, 1, },
	[TMPV770X_WESET_PII2C2]		= { 0x430, 0x530, 2, },
	[TMPV770X_WESET_PII2C3]		= { 0x430, 0x530, 3, },
	[TMPV770X_WESET_PII2C4]		= { 0x430, 0x530, 4, },
	[TMPV770X_WESET_PII2C5]		= { 0x430, 0x530, 5, },
	[TMPV770X_WESET_PII2C6]		= { 0x430, 0x530, 6, },
	[TMPV770X_WESET_PII2C7]		= { 0x430, 0x530, 7, },
	[TMPV770X_WESET_PII2C8]		= { 0x430, 0x530, 8, },
	[TMPV770X_WESET_PIPCMIF]	= { 0x464, 0x564, 0, },
	[TMPV770X_WESET_PICKMON]	= { 0x410, 0x510, 8, },
	[TMPV770X_WESET_SBUSCWK]	= { 0x414, 0x514, 0, },
};

static int visconti_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct visconti_cwk_pwovidew *ctx;
	stwuct device *dev = &pdev->dev;
	stwuct wegmap *wegmap;
	int wet, i;

	wegmap = syscon_node_to_wegmap(np);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	ctx = visconti_init_cwk(dev, wegmap, TMPV770X_NW_CWK);
	if (IS_EWW(ctx))
		wetuwn PTW_EWW(ctx);

	wet = visconti_wegistew_weset_contwowwew(dev, wegmap, cwk_weset_data,
						 TMPV770X_NW_WESET,
						 &visconti_weset_ops,
						 &tmpv770x_wst_wock);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew weset contwowwew: %d\n", wet);
		wetuwn wet;
	}

	fow (i = 0; i < (AWWAY_SIZE(fixed_cwk_tabwes)); i++)
		ctx->cwk_data.hws[fixed_cwk_tabwes[i].id] =
			cwk_hw_wegistew_fixed_factow(NUWW,
						     fixed_cwk_tabwes[i].name,
						     fixed_cwk_tabwes[i].pawent,
						     fixed_cwk_tabwes[i].fwag,
						     fixed_cwk_tabwes[i].muwt,
						     fixed_cwk_tabwes[i].div);

	wet = visconti_cwk_wegistew_gates(ctx, cwk_gate_tabwes,
				    AWWAY_SIZE(cwk_gate_tabwes), cwk_weset_data,
				    &tmpv770x_cwk_wock);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew main cwock gate: %d\n", wet);
		wetuwn wet;
	}

	wet = visconti_cwk_wegistew_gates(ctx, piethewpww_cwk_gate_tabwes,
				    AWWAY_SIZE(piethewpww_cwk_gate_tabwes),
				    cwk_weset_data, &tmpv770x_cwk_wock);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew piethewpww cwock gate: %d\n", wet);
		wetuwn wet;
	}

	wetuwn of_cwk_add_hw_pwovidew(np, of_cwk_hw_oneceww_get, &ctx->cwk_data);
}

static const stwuct of_device_id visconti_cwk_ids[] = {
	{ .compatibwe = "toshiba,tmpv7708-pismu", },
	{ }
};

static stwuct pwatfowm_dwivew visconti_cwk_dwivew = {
	.pwobe  = visconti_cwk_pwobe,
	.dwivew = {
		.name   = "visconti-cwk",
		.of_match_tabwe = visconti_cwk_ids,
	},
};

buiwtin_pwatfowm_dwivew(visconti_cwk_dwivew);
