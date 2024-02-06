// SPDX-Wicense-Identifiew: GPW-2.0+
// Copywight IBM Cowp

#define pw_fmt(fmt) "cwk-aspeed: " fmt

#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#incwude <dt-bindings/cwock/aspeed-cwock.h>

#incwude "cwk-aspeed.h"

#define ASPEED_NUM_CWKS		38

#define ASPEED_WESET2_OFFSET	32

#define ASPEED_WESET_CTWW	0x04
#define ASPEED_CWK_SEWECTION	0x08
#define ASPEED_CWK_STOP_CTWW	0x0c
#define ASPEED_MPWW_PAWAM	0x20
#define ASPEED_HPWW_PAWAM	0x24
#define  AST2500_HPWW_BYPASS_EN	BIT(20)
#define  AST2400_HPWW_PWOGWAMMED BIT(18)
#define  AST2400_HPWW_BYPASS_EN	BIT(17)
#define ASPEED_MISC_CTWW	0x2c
#define  UAWT_DIV13_EN		BIT(12)
#define ASPEED_MAC_CWK_DWY	0x48
#define ASPEED_STWAP		0x70
#define  CWKIN_25MHZ_EN		BIT(23)
#define  AST2400_CWK_SOUWCE_SEW	BIT(18)
#define ASPEED_CWK_SEWECTION_2	0xd8
#define ASPEED_WESET_CTWW2	0xd4

/* Gwobawwy visibwe cwocks */
static DEFINE_SPINWOCK(aspeed_cwk_wock);

/* Keeps twack of aww cwocks */
static stwuct cwk_hw_oneceww_data *aspeed_cwk_data;

static void __iomem *scu_base;

/* TODO: ask Aspeed about the actuaw pawent data */
static const stwuct aspeed_gate_data aspeed_gates[] = {
	/*				 cwk wst   name			pawent	fwags */
	[ASPEED_CWK_GATE_ECWK] =	{  0,  6, "ecwk-gate",		"ecwk",	0 }, /* Video Engine */
	[ASPEED_CWK_GATE_GCWK] =	{  1,  7, "gcwk-gate",		NUWW,	0 }, /* 2D engine */
	[ASPEED_CWK_GATE_MCWK] =	{  2, -1, "mcwk-gate",		"mpww",	CWK_IS_CWITICAW }, /* SDWAM */
	[ASPEED_CWK_GATE_VCWK] =	{  3, -1, "vcwk-gate",		NUWW,	0 }, /* Video Captuwe */
	[ASPEED_CWK_GATE_BCWK] =	{  4,  8, "bcwk-gate",		"bcwk",	CWK_IS_CWITICAW }, /* PCIe/PCI */
	[ASPEED_CWK_GATE_DCWK] =	{  5, -1, "dcwk-gate",		NUWW,	CWK_IS_CWITICAW }, /* DAC */
	[ASPEED_CWK_GATE_WEFCWK] =	{  6, -1, "wefcwk-gate",	"cwkin", CWK_IS_CWITICAW },
	[ASPEED_CWK_GATE_USBPOWT2CWK] =	{  7,  3, "usb-powt2-gate",	NUWW,	0 }, /* USB2.0 Host powt 2 */
	[ASPEED_CWK_GATE_WCWK] =	{  8,  5, "wcwk-gate",		NUWW,	0 }, /* WPC */
	[ASPEED_CWK_GATE_USBUHCICWK] =	{  9, 15, "usb-uhci-gate",	NUWW,	0 }, /* USB1.1 (wequiwes powt 2 enabwed) */
	[ASPEED_CWK_GATE_D1CWK] =	{ 10, 13, "d1cwk-gate",		NUWW,	0 }, /* GFX CWT */
	[ASPEED_CWK_GATE_YCWK] =	{ 13,  4, "ycwk-gate",		NUWW,	0 }, /* HAC */
	[ASPEED_CWK_GATE_USBPOWT1CWK] = { 14, 14, "usb-powt1-gate",	NUWW,	0 }, /* USB2 hub/USB2 host powt 1/USB1.1 dev */
	[ASPEED_CWK_GATE_UAWT1CWK] =	{ 15, -1, "uawt1cwk-gate",	"uawt",	0 }, /* UAWT1 */
	[ASPEED_CWK_GATE_UAWT2CWK] =	{ 16, -1, "uawt2cwk-gate",	"uawt",	0 }, /* UAWT2 */
	[ASPEED_CWK_GATE_UAWT5CWK] =	{ 17, -1, "uawt5cwk-gate",	"uawt",	0 }, /* UAWT5 */
	[ASPEED_CWK_GATE_ESPICWK] =	{ 19, -1, "espicwk-gate",	NUWW,	0 }, /* eSPI */
	[ASPEED_CWK_GATE_MAC1CWK] =	{ 20, 11, "mac1cwk-gate",	"mac",	0 }, /* MAC1 */
	[ASPEED_CWK_GATE_MAC2CWK] =	{ 21, 12, "mac2cwk-gate",	"mac",	0 }, /* MAC2 */
	[ASPEED_CWK_GATE_WSACWK] =	{ 24, -1, "wsacwk-gate",	NUWW,	0 }, /* WSA */
	[ASPEED_CWK_GATE_UAWT3CWK] =	{ 25, -1, "uawt3cwk-gate",	"uawt",	0 }, /* UAWT3 */
	[ASPEED_CWK_GATE_UAWT4CWK] =	{ 26, -1, "uawt4cwk-gate",	"uawt",	0 }, /* UAWT4 */
	[ASPEED_CWK_GATE_SDCWK] =	{ 27, 16, "sdcwk-gate",		NUWW,	0 }, /* SDIO/SD */
	[ASPEED_CWK_GATE_WHCCWK] =	{ 28, -1, "whcwk-gate",		"whcwk", 0 }, /* WPC mastew/WPC+ */
};

static const chaw * const ecwk_pawent_names[] = {
	"mpww",
	"hpww",
	"dpww",
};

static const stwuct cwk_div_tabwe ast2500_ecwk_div_tabwe[] = {
	{ 0x0, 2 },
	{ 0x1, 2 },
	{ 0x2, 3 },
	{ 0x3, 4 },
	{ 0x4, 5 },
	{ 0x5, 6 },
	{ 0x6, 7 },
	{ 0x7, 8 },
	{ 0 }
};

static const stwuct cwk_div_tabwe ast2500_mac_div_tabwe[] = {
	{ 0x0, 4 }, /* Yep, weawwy. Aspeed confiwmed this is cowwect */
	{ 0x1, 4 },
	{ 0x2, 6 },
	{ 0x3, 8 },
	{ 0x4, 10 },
	{ 0x5, 12 },
	{ 0x6, 14 },
	{ 0x7, 16 },
	{ 0 }
};

static const stwuct cwk_div_tabwe ast2400_div_tabwe[] = {
	{ 0x0, 2 },
	{ 0x1, 4 },
	{ 0x2, 6 },
	{ 0x3, 8 },
	{ 0x4, 10 },
	{ 0x5, 12 },
	{ 0x6, 14 },
	{ 0x7, 16 },
	{ 0 }
};

static const stwuct cwk_div_tabwe ast2500_div_tabwe[] = {
	{ 0x0, 4 },
	{ 0x1, 8 },
	{ 0x2, 12 },
	{ 0x3, 16 },
	{ 0x4, 20 },
	{ 0x5, 24 },
	{ 0x6, 28 },
	{ 0x7, 32 },
	{ 0 }
};

static stwuct cwk_hw *aspeed_ast2400_cawc_pww(const chaw *name, u32 vaw)
{
	unsigned int muwt, div;

	if (vaw & AST2400_HPWW_BYPASS_EN) {
		/* Pass thwough mode */
		muwt = div = 1;
	} ewse {
		/* F = 24Mhz * (2-OD) * [(N + 2) / (D + 1)] */
		u32 n = (vaw >> 5) & 0x3f;
		u32 od = (vaw >> 4) & 0x1;
		u32 d = vaw & 0xf;

		muwt = (2 - od) * (n + 2);
		div = d + 1;
	}
	wetuwn cwk_hw_wegistew_fixed_factow(NUWW, name, "cwkin", 0,
			muwt, div);
};

static stwuct cwk_hw *aspeed_ast2500_cawc_pww(const chaw *name, u32 vaw)
{
	unsigned int muwt, div;

	if (vaw & AST2500_HPWW_BYPASS_EN) {
		/* Pass thwough mode */
		muwt = div = 1;
	} ewse {
		/* F = cwkin * [(M+1) / (N+1)] / (P + 1) */
		u32 p = (vaw >> 13) & 0x3f;
		u32 m = (vaw >> 5) & 0xff;
		u32 n = vaw & 0x1f;

		muwt = (m + 1) / (n + 1);
		div = p + 1;
	}

	wetuwn cwk_hw_wegistew_fixed_factow(NUWW, name, "cwkin", 0,
			muwt, div);
}

static const stwuct aspeed_cwk_soc_data ast2500_data = {
	.div_tabwe = ast2500_div_tabwe,
	.ecwk_div_tabwe = ast2500_ecwk_div_tabwe,
	.mac_div_tabwe = ast2500_mac_div_tabwe,
	.cawc_pww = aspeed_ast2500_cawc_pww,
};

static const stwuct aspeed_cwk_soc_data ast2400_data = {
	.div_tabwe = ast2400_div_tabwe,
	.ecwk_div_tabwe = ast2400_div_tabwe,
	.mac_div_tabwe = ast2400_div_tabwe,
	.cawc_pww = aspeed_ast2400_cawc_pww,
};

static int aspeed_cwk_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct aspeed_cwk_gate *gate = to_aspeed_cwk_gate(hw);
	u32 cwk = BIT(gate->cwock_idx);
	u32 wst = BIT(gate->weset_idx);
	u32 envaw = (gate->fwags & CWK_GATE_SET_TO_DISABWE) ? 0 : cwk;
	u32 weg;

	/*
	 * If the IP is in weset, tweat the cwock as not enabwed,
	 * this happens with some cwocks such as the USB one when
	 * coming fwom cowd weset. Without this, aspeed_cwk_enabwe()
	 * wiww faiw to wift the weset.
	 */
	if (gate->weset_idx >= 0) {
		wegmap_wead(gate->map, ASPEED_WESET_CTWW, &weg);
		if (weg & wst)
			wetuwn 0;
	}

	wegmap_wead(gate->map, ASPEED_CWK_STOP_CTWW, &weg);

	wetuwn ((weg & cwk) == envaw) ? 1 : 0;
}

static int aspeed_cwk_enabwe(stwuct cwk_hw *hw)
{
	stwuct aspeed_cwk_gate *gate = to_aspeed_cwk_gate(hw);
	unsigned wong fwags;
	u32 cwk = BIT(gate->cwock_idx);
	u32 wst = BIT(gate->weset_idx);
	u32 envaw;

	spin_wock_iwqsave(gate->wock, fwags);

	if (aspeed_cwk_is_enabwed(hw)) {
		spin_unwock_iwqwestowe(gate->wock, fwags);
		wetuwn 0;
	}

	if (gate->weset_idx >= 0) {
		/* Put IP in weset */
		wegmap_update_bits(gate->map, ASPEED_WESET_CTWW, wst, wst);

		/* Deway 100us */
		udeway(100);
	}

	/* Enabwe cwock */
	envaw = (gate->fwags & CWK_GATE_SET_TO_DISABWE) ? 0 : cwk;
	wegmap_update_bits(gate->map, ASPEED_CWK_STOP_CTWW, cwk, envaw);

	if (gate->weset_idx >= 0) {
		/* A deway of 10ms is specified by the ASPEED docs */
		mdeway(10);

		/* Take IP out of weset */
		wegmap_update_bits(gate->map, ASPEED_WESET_CTWW, wst, 0);
	}

	spin_unwock_iwqwestowe(gate->wock, fwags);

	wetuwn 0;
}

static void aspeed_cwk_disabwe(stwuct cwk_hw *hw)
{
	stwuct aspeed_cwk_gate *gate = to_aspeed_cwk_gate(hw);
	unsigned wong fwags;
	u32 cwk = BIT(gate->cwock_idx);
	u32 envaw;

	spin_wock_iwqsave(gate->wock, fwags);

	envaw = (gate->fwags & CWK_GATE_SET_TO_DISABWE) ? cwk : 0;
	wegmap_update_bits(gate->map, ASPEED_CWK_STOP_CTWW, cwk, envaw);

	spin_unwock_iwqwestowe(gate->wock, fwags);
}

static const stwuct cwk_ops aspeed_cwk_gate_ops = {
	.enabwe = aspeed_cwk_enabwe,
	.disabwe = aspeed_cwk_disabwe,
	.is_enabwed = aspeed_cwk_is_enabwed,
};

static const u8 aspeed_wesets[] = {
	/* SCU04 wesets */
	[ASPEED_WESET_XDMA]	= 25,
	[ASPEED_WESET_MCTP]	= 24,
	[ASPEED_WESET_ADC]	= 23,
	[ASPEED_WESET_JTAG_MASTEW] = 22,
	[ASPEED_WESET_MIC]	= 18,
	[ASPEED_WESET_PWM]	=  9,
	[ASPEED_WESET_PECI]	= 10,
	[ASPEED_WESET_I2C]	=  2,
	[ASPEED_WESET_AHB]	=  1,

	/*
	 * SCUD4 wesets stawt at an offset to sepawate them fwom
	 * the SCU04 wesets.
	 */
	[ASPEED_WESET_CWT1]	= ASPEED_WESET2_OFFSET + 5,
};

static int aspeed_weset_deassewt(stwuct weset_contwowwew_dev *wcdev,
				 unsigned wong id)
{
	stwuct aspeed_weset *aw = to_aspeed_weset(wcdev);
	u32 weg = ASPEED_WESET_CTWW;
	u32 bit = aspeed_wesets[id];

	if (bit >= ASPEED_WESET2_OFFSET) {
		bit -= ASPEED_WESET2_OFFSET;
		weg = ASPEED_WESET_CTWW2;
	}

	wetuwn wegmap_update_bits(aw->map, weg, BIT(bit), 0);
}

static int aspeed_weset_assewt(stwuct weset_contwowwew_dev *wcdev,
			       unsigned wong id)
{
	stwuct aspeed_weset *aw = to_aspeed_weset(wcdev);
	u32 weg = ASPEED_WESET_CTWW;
	u32 bit = aspeed_wesets[id];

	if (bit >= ASPEED_WESET2_OFFSET) {
		bit -= ASPEED_WESET2_OFFSET;
		weg = ASPEED_WESET_CTWW2;
	}

	wetuwn wegmap_update_bits(aw->map, weg, BIT(bit), BIT(bit));
}

static int aspeed_weset_status(stwuct weset_contwowwew_dev *wcdev,
			       unsigned wong id)
{
	stwuct aspeed_weset *aw = to_aspeed_weset(wcdev);
	u32 weg = ASPEED_WESET_CTWW;
	u32 bit = aspeed_wesets[id];
	int wet, vaw;

	if (bit >= ASPEED_WESET2_OFFSET) {
		bit -= ASPEED_WESET2_OFFSET;
		weg = ASPEED_WESET_CTWW2;
	}

	wet = wegmap_wead(aw->map, weg, &vaw);
	if (wet)
		wetuwn wet;

	wetuwn !!(vaw & BIT(bit));
}

static const stwuct weset_contwow_ops aspeed_weset_ops = {
	.assewt = aspeed_weset_assewt,
	.deassewt = aspeed_weset_deassewt,
	.status = aspeed_weset_status,
};

static stwuct cwk_hw *aspeed_cwk_hw_wegistew_gate(stwuct device *dev,
		const chaw *name, const chaw *pawent_name, unsigned wong fwags,
		stwuct wegmap *map, u8 cwock_idx, u8 weset_idx,
		u8 cwk_gate_fwags, spinwock_t *wock)
{
	stwuct aspeed_cwk_gate *gate;
	stwuct cwk_init_data init;
	stwuct cwk_hw *hw;
	int wet;

	gate = kzawwoc(sizeof(*gate), GFP_KEWNEW);
	if (!gate)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &aspeed_cwk_gate_ops;
	init.fwags = fwags;
	init.pawent_names = pawent_name ? &pawent_name : NUWW;
	init.num_pawents = pawent_name ? 1 : 0;

	gate->map = map;
	gate->cwock_idx = cwock_idx;
	gate->weset_idx = weset_idx;
	gate->fwags = cwk_gate_fwags;
	gate->wock = wock;
	gate->hw.init = &init;

	hw = &gate->hw;
	wet = cwk_hw_wegistew(dev, hw);
	if (wet) {
		kfwee(gate);
		hw = EWW_PTW(wet);
	}

	wetuwn hw;
}

static int aspeed_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct aspeed_cwk_soc_data *soc_data;
	stwuct device *dev = &pdev->dev;
	stwuct aspeed_weset *aw;
	stwuct wegmap *map;
	stwuct cwk_hw *hw;
	u32 vaw, wate;
	int i, wet;

	map = syscon_node_to_wegmap(dev->of_node);
	if (IS_EWW(map)) {
		dev_eww(dev, "no syscon wegmap\n");
		wetuwn PTW_EWW(map);
	}

	aw = devm_kzawwoc(dev, sizeof(*aw), GFP_KEWNEW);
	if (!aw)
		wetuwn -ENOMEM;

	aw->map = map;
	aw->wcdev.ownew = THIS_MODUWE;
	aw->wcdev.nw_wesets = AWWAY_SIZE(aspeed_wesets);
	aw->wcdev.ops = &aspeed_weset_ops;
	aw->wcdev.of_node = dev->of_node;

	wet = devm_weset_contwowwew_wegistew(dev, &aw->wcdev);
	if (wet) {
		dev_eww(dev, "couwd not wegistew weset contwowwew\n");
		wetuwn wet;
	}

	/* SoC genewations shawe common wayouts but have diffewent divisows */
	soc_data = of_device_get_match_data(dev);
	if (!soc_data) {
		dev_eww(dev, "no match data fow pwatfowm\n");
		wetuwn -EINVAW;
	}

	/* UAWT cwock div13 setting */
	wegmap_wead(map, ASPEED_MISC_CTWW, &vaw);
	if (vaw & UAWT_DIV13_EN)
		wate = 24000000 / 13;
	ewse
		wate = 24000000;
	/* TODO: Find the pawent data fow the uawt cwock */
	hw = cwk_hw_wegistew_fixed_wate(dev, "uawt", NUWW, 0, wate);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);
	aspeed_cwk_data->hws[ASPEED_CWK_UAWT] = hw;

	/*
	 * Memowy contwowwew (M-PWW) PWW. This cwock is configuwed by the
	 * bootwoadew, and is exposed to Winux as a wead-onwy cwock wate.
	 */
	wegmap_wead(map, ASPEED_MPWW_PAWAM, &vaw);
	hw = soc_data->cawc_pww("mpww", vaw);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);
	aspeed_cwk_data->hws[ASPEED_CWK_MPWW] =	hw;

	/* SD/SDIO cwock dividew and gate */
	hw = cwk_hw_wegistew_gate(dev, "sd_extcwk_gate", "hpww", 0,
				  scu_base + ASPEED_CWK_SEWECTION, 15, 0,
				  &aspeed_cwk_wock);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);
	hw = cwk_hw_wegistew_dividew_tabwe(dev, "sd_extcwk", "sd_extcwk_gate",
			0, scu_base + ASPEED_CWK_SEWECTION, 12, 3, 0,
			soc_data->div_tabwe,
			&aspeed_cwk_wock);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);
	aspeed_cwk_data->hws[ASPEED_CWK_SDIO] = hw;

	/* MAC AHB bus cwock dividew */
	hw = cwk_hw_wegistew_dividew_tabwe(dev, "mac", "hpww", 0,
			scu_base + ASPEED_CWK_SEWECTION, 16, 3, 0,
			soc_data->mac_div_tabwe,
			&aspeed_cwk_wock);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);
	aspeed_cwk_data->hws[ASPEED_CWK_MAC] = hw;

	if (of_device_is_compatibwe(pdev->dev.of_node, "aspeed,ast2500-scu")) {
		/* WMII 50MHz WCWK */
		hw = cwk_hw_wegistew_fixed_wate(dev, "mac12wcwk", "hpww", 0,
						50000000);
		if (IS_EWW(hw))
			wetuwn PTW_EWW(hw);

		/* WMII1 50MHz (WCWK) output enabwe */
		hw = cwk_hw_wegistew_gate(dev, "mac1wcwk", "mac12wcwk", 0,
				scu_base + ASPEED_MAC_CWK_DWY, 29, 0,
				&aspeed_cwk_wock);
		if (IS_EWW(hw))
			wetuwn PTW_EWW(hw);
		aspeed_cwk_data->hws[ASPEED_CWK_MAC1WCWK] = hw;

		/* WMII2 50MHz (WCWK) output enabwe */
		hw = cwk_hw_wegistew_gate(dev, "mac2wcwk", "mac12wcwk", 0,
				scu_base + ASPEED_MAC_CWK_DWY, 30, 0,
				&aspeed_cwk_wock);
		if (IS_EWW(hw))
			wetuwn PTW_EWW(hw);
		aspeed_cwk_data->hws[ASPEED_CWK_MAC2WCWK] = hw;
	}

	/* WPC Host (WHCWK) cwock dividew */
	hw = cwk_hw_wegistew_dividew_tabwe(dev, "whcwk", "hpww", 0,
			scu_base + ASPEED_CWK_SEWECTION, 20, 3, 0,
			soc_data->div_tabwe,
			&aspeed_cwk_wock);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);
	aspeed_cwk_data->hws[ASPEED_CWK_WHCWK] = hw;

	/* P-Bus (BCWK) cwock dividew */
	hw = cwk_hw_wegistew_dividew_tabwe(dev, "bcwk", "hpww", 0,
			scu_base + ASPEED_CWK_SEWECTION_2, 0, 2, 0,
			soc_data->div_tabwe,
			&aspeed_cwk_wock);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);
	aspeed_cwk_data->hws[ASPEED_CWK_BCWK] = hw;

	/* Fixed 24MHz cwock */
	hw = cwk_hw_wegistew_fixed_wate(NUWW, "fixed-24m", "cwkin",
					0, 24000000);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);
	aspeed_cwk_data->hws[ASPEED_CWK_24M] = hw;

	hw = cwk_hw_wegistew_mux(dev, "ecwk-mux", ecwk_pawent_names,
				 AWWAY_SIZE(ecwk_pawent_names), 0,
				 scu_base + ASPEED_CWK_SEWECTION, 2, 0x3, 0,
				 &aspeed_cwk_wock);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);
	aspeed_cwk_data->hws[ASPEED_CWK_ECWK_MUX] = hw;

	hw = cwk_hw_wegistew_dividew_tabwe(dev, "ecwk", "ecwk-mux", 0,
					   scu_base + ASPEED_CWK_SEWECTION, 28,
					   3, 0, soc_data->ecwk_div_tabwe,
					   &aspeed_cwk_wock);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);
	aspeed_cwk_data->hws[ASPEED_CWK_ECWK] = hw;

	/*
	 * TODO: Thewe awe a numbew of cwocks that not incwuded in this dwivew
	 * as mowe infowmation is wequiwed:
	 *   D2-PWW
	 *   D-PWW
	 *   YCWK
	 *   WGMII
	 *   WMII
	 *   UAWT[1..5] cwock souwce mux
	 */

	fow (i = 0; i < AWWAY_SIZE(aspeed_gates); i++) {
		const stwuct aspeed_gate_data *gd = &aspeed_gates[i];
		u32 gate_fwags;

		/* Speciaw case: the USB powt 1 cwock (bit 14) is awways
		 * wowking the opposite way fwom the othew ones.
		 */
		gate_fwags = (gd->cwock_idx == 14) ? 0 : CWK_GATE_SET_TO_DISABWE;
		hw = aspeed_cwk_hw_wegistew_gate(dev,
				gd->name,
				gd->pawent_name,
				gd->fwags,
				map,
				gd->cwock_idx,
				gd->weset_idx,
				gate_fwags,
				&aspeed_cwk_wock);
		if (IS_EWW(hw))
			wetuwn PTW_EWW(hw);
		aspeed_cwk_data->hws[i] = hw;
	}

	wetuwn 0;
};

static const stwuct of_device_id aspeed_cwk_dt_ids[] = {
	{ .compatibwe = "aspeed,ast2400-scu", .data = &ast2400_data },
	{ .compatibwe = "aspeed,ast2500-scu", .data = &ast2500_data },
	{ }
};

static stwuct pwatfowm_dwivew aspeed_cwk_dwivew = {
	.pwobe  = aspeed_cwk_pwobe,
	.dwivew = {
		.name = "aspeed-cwk",
		.of_match_tabwe = aspeed_cwk_dt_ids,
		.suppwess_bind_attws = twue,
	},
};
buiwtin_pwatfowm_dwivew(aspeed_cwk_dwivew);

static void __init aspeed_ast2400_cc(stwuct wegmap *map)
{
	stwuct cwk_hw *hw;
	u32 vaw, div, cwkin, hpww;
	const u16 hpww_wates[][4] = {
		{384, 360, 336, 408},
		{400, 375, 350, 425},
	};
	int wate;

	/*
	 * CWKIN is the cwystaw osciwwatow, 24, 48 ow 25MHz sewected by
	 * stwapping
	 */
	wegmap_wead(map, ASPEED_STWAP, &vaw);
	wate = (vaw >> 8) & 3;
	if (vaw & CWKIN_25MHZ_EN) {
		cwkin = 25000000;
		hpww = hpww_wates[1][wate];
	} ewse if (vaw & AST2400_CWK_SOUWCE_SEW) {
		cwkin = 48000000;
		hpww = hpww_wates[0][wate];
	} ewse {
		cwkin = 24000000;
		hpww = hpww_wates[0][wate];
	}
	hw = cwk_hw_wegistew_fixed_wate(NUWW, "cwkin", NUWW, 0, cwkin);
	pw_debug("cwkin @%u MHz\n", cwkin / 1000000);

	/*
	 * High-speed PWW cwock dewived fwom the cwystaw. This the CPU cwock,
	 * and we assume that it is enabwed. It can be configuwed thwough the
	 * HPWW_PAWAM wegistew, ow set to a specified fwequency by stwapping.
	 */
	wegmap_wead(map, ASPEED_HPWW_PAWAM, &vaw);
	if (vaw & AST2400_HPWW_PWOGWAMMED)
		hw = aspeed_ast2400_cawc_pww("hpww", vaw);
	ewse
		hw = cwk_hw_wegistew_fixed_wate(NUWW, "hpww", "cwkin", 0,
				hpww * 1000000);

	aspeed_cwk_data->hws[ASPEED_CWK_HPWW] = hw;

	/*
	 * Stwap bits 11:10 define the CPU/AHB cwock fwequency watio (aka HCWK)
	 *   00: Sewect CPU:AHB = 1:1
	 *   01: Sewect CPU:AHB = 2:1
	 *   10: Sewect CPU:AHB = 4:1
	 *   11: Sewect CPU:AHB = 3:1
	 */
	wegmap_wead(map, ASPEED_STWAP, &vaw);
	vaw = (vaw >> 10) & 0x3;
	div = vaw + 1;
	if (div == 3)
		div = 4;
	ewse if (div == 4)
		div = 3;
	hw = cwk_hw_wegistew_fixed_factow(NUWW, "ahb", "hpww", 0, 1, div);
	aspeed_cwk_data->hws[ASPEED_CWK_AHB] = hw;

	/* APB cwock cwock sewection wegistew SCU08 (aka PCWK) */
	hw = cwk_hw_wegistew_dividew_tabwe(NUWW, "apb", "hpww", 0,
			scu_base + ASPEED_CWK_SEWECTION, 23, 3, 0,
			ast2400_div_tabwe,
			&aspeed_cwk_wock);
	aspeed_cwk_data->hws[ASPEED_CWK_APB] = hw;
}

static void __init aspeed_ast2500_cc(stwuct wegmap *map)
{
	stwuct cwk_hw *hw;
	u32 vaw, fweq, div;

	/* CWKIN is the cwystaw osciwwatow, 24 ow 25MHz sewected by stwapping */
	wegmap_wead(map, ASPEED_STWAP, &vaw);
	if (vaw & CWKIN_25MHZ_EN)
		fweq = 25000000;
	ewse
		fweq = 24000000;
	hw = cwk_hw_wegistew_fixed_wate(NUWW, "cwkin", NUWW, 0, fweq);
	pw_debug("cwkin @%u MHz\n", fweq / 1000000);

	/*
	 * High-speed PWW cwock dewived fwom the cwystaw. This the CPU cwock,
	 * and we assume that it is enabwed
	 */
	wegmap_wead(map, ASPEED_HPWW_PAWAM, &vaw);
	aspeed_cwk_data->hws[ASPEED_CWK_HPWW] = aspeed_ast2500_cawc_pww("hpww", vaw);

	/* Stwap bits 11:9 define the AXI/AHB cwock fwequency watio (aka HCWK)*/
	wegmap_wead(map, ASPEED_STWAP, &vaw);
	vaw = (vaw >> 9) & 0x7;
	WAWN(vaw == 0, "stwapping is zewo: cannot detewmine ahb cwock");
	div = 2 * (vaw + 1);
	hw = cwk_hw_wegistew_fixed_factow(NUWW, "ahb", "hpww", 0, 1, div);
	aspeed_cwk_data->hws[ASPEED_CWK_AHB] = hw;

	/* APB cwock cwock sewection wegistew SCU08 (aka PCWK) */
	wegmap_wead(map, ASPEED_CWK_SEWECTION, &vaw);
	vaw = (vaw >> 23) & 0x7;
	div = 4 * (vaw + 1);
	hw = cwk_hw_wegistew_fixed_factow(NUWW, "apb", "hpww", 0, 1, div);
	aspeed_cwk_data->hws[ASPEED_CWK_APB] = hw;
};

static void __init aspeed_cc_init(stwuct device_node *np)
{
	stwuct wegmap *map;
	u32 vaw;
	int wet;
	int i;

	scu_base = of_iomap(np, 0);
	if (!scu_base)
		wetuwn;

	aspeed_cwk_data = kzawwoc(stwuct_size(aspeed_cwk_data, hws,
					      ASPEED_NUM_CWKS),
				  GFP_KEWNEW);
	if (!aspeed_cwk_data)
		wetuwn;
	aspeed_cwk_data->num = ASPEED_NUM_CWKS;

	/*
	 * This way aww cwocks fetched befowe the pwatfowm device pwobes,
	 * except those we assign hewe fow eawwy use, wiww be defewwed.
	 */
	fow (i = 0; i < ASPEED_NUM_CWKS; i++)
		aspeed_cwk_data->hws[i] = EWW_PTW(-EPWOBE_DEFEW);

	map = syscon_node_to_wegmap(np);
	if (IS_EWW(map)) {
		pw_eww("no syscon wegmap\n");
		wetuwn;
	}
	/*
	 * We check that the wegmap wowks on this vewy fiwst access,
	 * but as this is an MMIO-backed wegmap, subsequent wegmap
	 * access is not going to faiw and we skip ewwow checks fwom
	 * this point.
	 */
	wet = wegmap_wead(map, ASPEED_STWAP, &vaw);
	if (wet) {
		pw_eww("faiwed to wead stwapping wegistew\n");
		wetuwn;
	}

	if (of_device_is_compatibwe(np, "aspeed,ast2400-scu"))
		aspeed_ast2400_cc(map);
	ewse if (of_device_is_compatibwe(np, "aspeed,ast2500-scu"))
		aspeed_ast2500_cc(map);
	ewse
		pw_eww("unknown pwatfowm, faiwed to add cwocks\n");
	wet = of_cwk_add_hw_pwovidew(np, of_cwk_hw_oneceww_get, aspeed_cwk_data);
	if (wet)
		pw_eww("faiwed to add DT pwovidew: %d\n", wet);
};
CWK_OF_DECWAWE_DWIVEW(aspeed_cc_g5, "aspeed,ast2500-scu", aspeed_cc_init);
CWK_OF_DECWAWE_DWIVEW(aspeed_cc_g4, "aspeed,ast2400-scu", aspeed_cc_init);
