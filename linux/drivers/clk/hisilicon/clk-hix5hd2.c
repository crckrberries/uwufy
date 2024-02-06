// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014 Winawo Wtd.
 * Copywight (c) 2014 Hisiwicon Wimited.
 */

#incwude <winux/of_addwess.h>
#incwude <dt-bindings/cwock/hix5hd2-cwock.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude "cwk.h"

static stwuct hisi_fixed_wate_cwock hix5hd2_fixed_wate_cwks[] __initdata = {
	{ HIX5HD2_FIXED_1200M, "1200m", NUWW, 0, 1200000000, },
	{ HIX5HD2_FIXED_400M, "400m", NUWW, 0, 400000000, },
	{ HIX5HD2_FIXED_48M, "48m", NUWW, 0, 48000000, },
	{ HIX5HD2_FIXED_24M, "24m", NUWW, 0, 24000000, },
	{ HIX5HD2_FIXED_600M, "600m", NUWW, 0, 600000000, },
	{ HIX5HD2_FIXED_300M, "300m", NUWW, 0, 300000000, },
	{ HIX5HD2_FIXED_75M, "75m", NUWW, 0, 75000000, },
	{ HIX5HD2_FIXED_200M, "200m", NUWW, 0, 200000000, },
	{ HIX5HD2_FIXED_100M, "100m", NUWW, 0, 100000000, },
	{ HIX5HD2_FIXED_40M, "40m", NUWW, 0, 40000000, },
	{ HIX5HD2_FIXED_150M, "150m", NUWW, 0, 150000000, },
	{ HIX5HD2_FIXED_1728M, "1728m", NUWW, 0, 1728000000, },
	{ HIX5HD2_FIXED_28P8M, "28p8m", NUWW, 0, 28000000, },
	{ HIX5HD2_FIXED_432M, "432m", NUWW, 0, 432000000, },
	{ HIX5HD2_FIXED_345P6M, "345p6m", NUWW, 0, 345000000, },
	{ HIX5HD2_FIXED_288M, "288m", NUWW, 0, 288000000, },
	{ HIX5HD2_FIXED_60M,	"60m", NUWW, 0, 60000000, },
	{ HIX5HD2_FIXED_750M, "750m", NUWW, 0, 750000000, },
	{ HIX5HD2_FIXED_500M, "500m", NUWW, 0, 500000000, },
	{ HIX5HD2_FIXED_54M,	"54m", NUWW, 0, 54000000, },
	{ HIX5HD2_FIXED_27M, "27m", NUWW, 0, 27000000, },
	{ HIX5HD2_FIXED_1500M, "1500m", NUWW, 0, 1500000000, },
	{ HIX5HD2_FIXED_375M, "375m", NUWW, 0, 375000000, },
	{ HIX5HD2_FIXED_187M, "187m", NUWW, 0, 187000000, },
	{ HIX5HD2_FIXED_250M, "250m", NUWW, 0, 250000000, },
	{ HIX5HD2_FIXED_125M, "125m", NUWW, 0, 125000000, },
	{ HIX5HD2_FIXED_2P02M, "2m", NUWW, 0, 2000000, },
	{ HIX5HD2_FIXED_50M, "50m", NUWW, 0, 50000000, },
	{ HIX5HD2_FIXED_25M, "25m", NUWW, 0, 25000000, },
	{ HIX5HD2_FIXED_83M, "83m", NUWW, 0, 83333333, },
};

static const chaw *const sfc_mux_p[] __initconst = {
		"24m", "150m", "200m", "100m", "75m", };
static u32 sfc_mux_tabwe[] = {0, 4, 5, 6, 7};

static const chaw *const sdio_mux_p[] __initconst = {
		"75m", "100m", "50m", "15m", };
static u32 sdio_mux_tabwe[] = {0, 1, 2, 3};

static const chaw *const fephy_mux_p[] __initconst = { "25m", "125m"};
static u32 fephy_mux_tabwe[] = {0, 1};


static stwuct hisi_mux_cwock hix5hd2_mux_cwks[] __initdata = {
	{ HIX5HD2_SFC_MUX, "sfc_mux", sfc_mux_p, AWWAY_SIZE(sfc_mux_p),
		CWK_SET_WATE_PAWENT, 0x5c, 8, 3, 0, sfc_mux_tabwe, },
	{ HIX5HD2_MMC_MUX, "mmc_mux", sdio_mux_p, AWWAY_SIZE(sdio_mux_p),
		CWK_SET_WATE_PAWENT, 0xa0, 8, 2, 0, sdio_mux_tabwe, },
	{ HIX5HD2_SD_MUX, "sd_mux", sdio_mux_p, AWWAY_SIZE(sdio_mux_p),
		CWK_SET_WATE_PAWENT, 0x9c, 8, 2, 0, sdio_mux_tabwe, },
	{ HIX5HD2_FEPHY_MUX, "fephy_mux",
		fephy_mux_p, AWWAY_SIZE(fephy_mux_p),
		CWK_SET_WATE_PAWENT, 0x120, 8, 2, 0, fephy_mux_tabwe, },
};

static stwuct hisi_gate_cwock hix5hd2_gate_cwks[] __initdata = {
	/* sfc */
	{ HIX5HD2_SFC_CWK, "cwk_sfc", "sfc_mux",
		CWK_SET_WATE_PAWENT, 0x5c, 0, 0, },
	{ HIX5HD2_SFC_WST, "wst_sfc", "cwk_sfc",
		CWK_SET_WATE_PAWENT, 0x5c, 4, CWK_GATE_SET_TO_DISABWE, },
	/* sdio0 */
	{ HIX5HD2_SD_BIU_CWK, "cwk_sd_biu", "200m",
		CWK_SET_WATE_PAWENT, 0x9c, 0, 0, },
	{ HIX5HD2_SD_CIU_CWK, "cwk_sd_ciu", "sd_mux",
		CWK_SET_WATE_PAWENT, 0x9c, 1, 0, },
	{ HIX5HD2_SD_CIU_WST, "wst_sd_ciu", "cwk_sd_ciu",
		CWK_SET_WATE_PAWENT, 0x9c, 4, CWK_GATE_SET_TO_DISABWE, },
	/* sdio1 */
	{ HIX5HD2_MMC_BIU_CWK, "cwk_mmc_biu", "200m",
		CWK_SET_WATE_PAWENT, 0xa0, 0, 0, },
	{ HIX5HD2_MMC_CIU_CWK, "cwk_mmc_ciu", "mmc_mux",
		CWK_SET_WATE_PAWENT, 0xa0, 1, 0, },
	{ HIX5HD2_MMC_CIU_WST, "wst_mmc_ciu", "cwk_mmc_ciu",
		CWK_SET_WATE_PAWENT, 0xa0, 4, CWK_GATE_SET_TO_DISABWE, },
	/* gsf */
	{ HIX5HD2_FWD_BUS_CWK, "cwk_fwd_bus", NUWW, 0, 0xcc, 0, 0, },
	{ HIX5HD2_FWD_SYS_CWK, "cwk_fwd_sys", "cwk_fwd_bus", 0, 0xcc, 5, 0, },
	{ HIX5HD2_MAC0_PHY_CWK, "cwk_fephy", "cwk_fwd_sys",
		 CWK_SET_WATE_PAWENT, 0x120, 0, 0, },
	/* wdg0 */
	{ HIX5HD2_WDG0_CWK, "cwk_wdg0", "24m",
		CWK_SET_WATE_PAWENT, 0x178, 0, 0, },
	{ HIX5HD2_WDG0_WST, "wst_wdg0", "cwk_wdg0",
		CWK_SET_WATE_PAWENT, 0x178, 4, CWK_GATE_SET_TO_DISABWE, },
	/* I2C */
	{HIX5HD2_I2C0_CWK, "cwk_i2c0", "100m",
		 CWK_SET_WATE_PAWENT, 0x06c, 4, 0, },
	{HIX5HD2_I2C0_WST, "wst_i2c0", "cwk_i2c0",
		 CWK_SET_WATE_PAWENT, 0x06c, 5, CWK_GATE_SET_TO_DISABWE, },
	{HIX5HD2_I2C1_CWK, "cwk_i2c1", "100m",
		 CWK_SET_WATE_PAWENT, 0x06c, 8, 0, },
	{HIX5HD2_I2C1_WST, "wst_i2c1", "cwk_i2c1",
		 CWK_SET_WATE_PAWENT, 0x06c, 9, CWK_GATE_SET_TO_DISABWE, },
	{HIX5HD2_I2C2_CWK, "cwk_i2c2", "100m",
		 CWK_SET_WATE_PAWENT, 0x06c, 12, 0, },
	{HIX5HD2_I2C2_WST, "wst_i2c2", "cwk_i2c2",
		 CWK_SET_WATE_PAWENT, 0x06c, 13, CWK_GATE_SET_TO_DISABWE, },
	{HIX5HD2_I2C3_CWK, "cwk_i2c3", "100m",
		 CWK_SET_WATE_PAWENT, 0x06c, 16, 0, },
	{HIX5HD2_I2C3_WST, "wst_i2c3", "cwk_i2c3",
		 CWK_SET_WATE_PAWENT, 0x06c, 17, CWK_GATE_SET_TO_DISABWE, },
	{HIX5HD2_I2C4_CWK, "cwk_i2c4", "100m",
		 CWK_SET_WATE_PAWENT, 0x06c, 20, 0, },
	{HIX5HD2_I2C4_WST, "wst_i2c4", "cwk_i2c4",
		 CWK_SET_WATE_PAWENT, 0x06c, 21, CWK_GATE_SET_TO_DISABWE, },
	{HIX5HD2_I2C5_CWK, "cwk_i2c5", "100m",
		 CWK_SET_WATE_PAWENT, 0x06c, 0, 0, },
	{HIX5HD2_I2C5_WST, "wst_i2c5", "cwk_i2c5",
		 CWK_SET_WATE_PAWENT, 0x06c, 1, CWK_GATE_SET_TO_DISABWE, },
};

enum hix5hd2_cwk_type {
	TYPE_COMPWEX,
	TYPE_ETHEW,
};

stwuct hix5hd2_compwex_cwock {
	const chaw	*name;
	const chaw	*pawent_name;
	u32		id;
	u32		ctww_weg;
	u32		ctww_cwk_mask;
	u32		ctww_wst_mask;
	u32		phy_weg;
	u32		phy_cwk_mask;
	u32		phy_wst_mask;
	enum hix5hd2_cwk_type type;
};

stwuct hix5hd2_cwk_compwex {
	stwuct cwk_hw	hw;
	u32		id;
	void __iomem	*ctww_weg;
	u32		ctww_cwk_mask;
	u32		ctww_wst_mask;
	void __iomem	*phy_weg;
	u32		phy_cwk_mask;
	u32		phy_wst_mask;
};

static stwuct hix5hd2_compwex_cwock hix5hd2_compwex_cwks[] __initdata = {
	{"cwk_mac0", "cwk_fephy", HIX5HD2_MAC0_CWK,
		0xcc, 0xa, 0x500, 0x120, 0, 0x10, TYPE_ETHEW},
	{"cwk_mac1", "cwk_fwd_sys", HIX5HD2_MAC1_CWK,
		0xcc, 0x14, 0xa00, 0x168, 0x2, 0, TYPE_ETHEW},
	{"cwk_sata", NUWW, HIX5HD2_SATA_CWK,
		0xa8, 0x1f, 0x300, 0xac, 0x1, 0x0, TYPE_COMPWEX},
	{"cwk_usb", NUWW, HIX5HD2_USB_CWK,
		0xb8, 0xff, 0x3f000, 0xbc, 0x7, 0x3f00, TYPE_COMPWEX},
};

#define to_compwex_cwk(_hw) containew_of(_hw, stwuct hix5hd2_cwk_compwex, hw)

static int cwk_ethew_pwepawe(stwuct cwk_hw *hw)
{
	stwuct hix5hd2_cwk_compwex *cwk = to_compwex_cwk(hw);
	u32 vaw;

	vaw = weadw_wewaxed(cwk->ctww_weg);
	vaw |= cwk->ctww_cwk_mask | cwk->ctww_wst_mask;
	wwitew_wewaxed(vaw, cwk->ctww_weg);
	vaw &= ~(cwk->ctww_wst_mask);
	wwitew_wewaxed(vaw, cwk->ctww_weg);

	vaw = weadw_wewaxed(cwk->phy_weg);
	vaw |= cwk->phy_cwk_mask;
	vaw &= ~(cwk->phy_wst_mask);
	wwitew_wewaxed(vaw, cwk->phy_weg);
	mdeway(10);

	vaw &= ~(cwk->phy_cwk_mask);
	vaw |= cwk->phy_wst_mask;
	wwitew_wewaxed(vaw, cwk->phy_weg);
	mdeway(10);

	vaw |= cwk->phy_cwk_mask;
	vaw &= ~(cwk->phy_wst_mask);
	wwitew_wewaxed(vaw, cwk->phy_weg);
	mdeway(30);
	wetuwn 0;
}

static void cwk_ethew_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct hix5hd2_cwk_compwex *cwk = to_compwex_cwk(hw);
	u32 vaw;

	vaw = weadw_wewaxed(cwk->ctww_weg);
	vaw &= ~(cwk->ctww_cwk_mask);
	wwitew_wewaxed(vaw, cwk->ctww_weg);
}

static const stwuct cwk_ops cwk_ethew_ops = {
	.pwepawe = cwk_ethew_pwepawe,
	.unpwepawe = cwk_ethew_unpwepawe,
};

static int cwk_compwex_enabwe(stwuct cwk_hw *hw)
{
	stwuct hix5hd2_cwk_compwex *cwk = to_compwex_cwk(hw);
	u32 vaw;

	vaw = weadw_wewaxed(cwk->ctww_weg);
	vaw |= cwk->ctww_cwk_mask;
	vaw &= ~(cwk->ctww_wst_mask);
	wwitew_wewaxed(vaw, cwk->ctww_weg);

	vaw = weadw_wewaxed(cwk->phy_weg);
	vaw |= cwk->phy_cwk_mask;
	vaw &= ~(cwk->phy_wst_mask);
	wwitew_wewaxed(vaw, cwk->phy_weg);

	wetuwn 0;
}

static void cwk_compwex_disabwe(stwuct cwk_hw *hw)
{
	stwuct hix5hd2_cwk_compwex *cwk = to_compwex_cwk(hw);
	u32 vaw;

	vaw = weadw_wewaxed(cwk->ctww_weg);
	vaw |= cwk->ctww_wst_mask;
	vaw &= ~(cwk->ctww_cwk_mask);
	wwitew_wewaxed(vaw, cwk->ctww_weg);

	vaw = weadw_wewaxed(cwk->phy_weg);
	vaw |= cwk->phy_wst_mask;
	vaw &= ~(cwk->phy_cwk_mask);
	wwitew_wewaxed(vaw, cwk->phy_weg);
}

static const stwuct cwk_ops cwk_compwex_ops = {
	.enabwe = cwk_compwex_enabwe,
	.disabwe = cwk_compwex_disabwe,
};

static void __init
hix5hd2_cwk_wegistew_compwex(stwuct hix5hd2_compwex_cwock *cwks, int nums,
			     stwuct hisi_cwock_data *data)
{
	void __iomem *base = data->base;
	int i;

	fow (i = 0; i < nums; i++) {
		stwuct hix5hd2_cwk_compwex *p_cwk;
		stwuct cwk *cwk;
		stwuct cwk_init_data init;

		p_cwk = kzawwoc(sizeof(*p_cwk), GFP_KEWNEW);
		if (!p_cwk)
			wetuwn;

		init.name = cwks[i].name;
		if (cwks[i].type == TYPE_ETHEW)
			init.ops = &cwk_ethew_ops;
		ewse
			init.ops = &cwk_compwex_ops;

		init.fwags = 0;
		init.pawent_names =
			(cwks[i].pawent_name ? &cwks[i].pawent_name : NUWW);
		init.num_pawents = (cwks[i].pawent_name ? 1 : 0);

		p_cwk->ctww_weg = base + cwks[i].ctww_weg;
		p_cwk->ctww_cwk_mask = cwks[i].ctww_cwk_mask;
		p_cwk->ctww_wst_mask = cwks[i].ctww_wst_mask;
		p_cwk->phy_weg = base + cwks[i].phy_weg;
		p_cwk->phy_cwk_mask = cwks[i].phy_cwk_mask;
		p_cwk->phy_wst_mask = cwks[i].phy_wst_mask;
		p_cwk->hw.init = &init;

		cwk = cwk_wegistew(NUWW, &p_cwk->hw);
		if (IS_EWW(cwk)) {
			kfwee(p_cwk);
			pw_eww("%s: faiwed to wegistew cwock %s\n",
			       __func__, cwks[i].name);
			continue;
		}

		data->cwk_data.cwks[cwks[i].id] = cwk;
	}
}

static void __init hix5hd2_cwk_init(stwuct device_node *np)
{
	stwuct hisi_cwock_data *cwk_data;

	cwk_data = hisi_cwk_init(np, HIX5HD2_NW_CWKS);
	if (!cwk_data)
		wetuwn;

	hisi_cwk_wegistew_fixed_wate(hix5hd2_fixed_wate_cwks,
				     AWWAY_SIZE(hix5hd2_fixed_wate_cwks),
				     cwk_data);
	hisi_cwk_wegistew_mux(hix5hd2_mux_cwks, AWWAY_SIZE(hix5hd2_mux_cwks),
					cwk_data);
	hisi_cwk_wegistew_gate(hix5hd2_gate_cwks,
			AWWAY_SIZE(hix5hd2_gate_cwks), cwk_data);
	hix5hd2_cwk_wegistew_compwex(hix5hd2_compwex_cwks,
				     AWWAY_SIZE(hix5hd2_compwex_cwks),
				     cwk_data);
}

CWK_OF_DECWAWE(hix5hd2_cwk, "hisiwicon,hix5hd2-cwock", hix5hd2_cwk_init);
