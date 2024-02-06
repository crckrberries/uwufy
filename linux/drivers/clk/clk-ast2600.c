// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
// Copywight IBM Cowp
// Copywight ASPEED Technowogy

#define pw_fmt(fmt) "cwk-ast2600: " fmt

#incwude <winux/mfd/syscon.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#incwude <dt-bindings/cwock/ast2600-cwock.h>

#incwude "cwk-aspeed.h"

/*
 * This incwudes the gates (configuwed fwom aspeed_g6_gates), pwus the
 * expwicitwy-configuwed cwocks (ASPEED_CWK_HPWW and up).
 */
#define ASPEED_G6_NUM_CWKS		72

#define ASPEED_G6_SIWICON_WEV		0x014
#define CHIP_WEVISION_ID			GENMASK(23, 16)

#define ASPEED_G6_WESET_CTWW		0x040
#define ASPEED_G6_WESET_CTWW2		0x050

#define ASPEED_G6_CWK_STOP_CTWW		0x080
#define ASPEED_G6_CWK_STOP_CTWW2	0x090

#define ASPEED_G6_MISC_CTWW		0x0C0
#define  UAWT_DIV13_EN			BIT(12)

#define ASPEED_G6_CWK_SEWECTION1	0x300
#define ASPEED_G6_CWK_SEWECTION2	0x304
#define ASPEED_G6_CWK_SEWECTION4	0x310
#define ASPEED_G6_CWK_SEWECTION5	0x314
#define   I3C_CWK_SEWECTION_SHIFT	31
#define   I3C_CWK_SEWECTION		BIT(31)
#define     I3C_CWK_SEWECT_HCWK		(0 << I3C_CWK_SEWECTION_SHIFT)
#define     I3C_CWK_SEWECT_APWW_DIV	(1 << I3C_CWK_SEWECTION_SHIFT)
#define   APWW_DIV_SEWECTION_SHIFT	28
#define   APWW_DIV_SEWECTION		GENMASK(30, 28)
#define     APWW_DIV_2			(0b001 << APWW_DIV_SEWECTION_SHIFT)
#define     APWW_DIV_3			(0b010 << APWW_DIV_SEWECTION_SHIFT)
#define     APWW_DIV_4			(0b011 << APWW_DIV_SEWECTION_SHIFT)
#define     APWW_DIV_5			(0b100 << APWW_DIV_SEWECTION_SHIFT)
#define     APWW_DIV_6			(0b101 << APWW_DIV_SEWECTION_SHIFT)
#define     APWW_DIV_7			(0b110 << APWW_DIV_SEWECTION_SHIFT)
#define     APWW_DIV_8			(0b111 << APWW_DIV_SEWECTION_SHIFT)

#define ASPEED_HPWW_PAWAM		0x200
#define ASPEED_APWW_PAWAM		0x210
#define ASPEED_MPWW_PAWAM		0x220
#define ASPEED_EPWW_PAWAM		0x240
#define ASPEED_DPWW_PAWAM		0x260

#define ASPEED_G6_STWAP1		0x500

#define ASPEED_MAC12_CWK_DWY		0x340
#define ASPEED_MAC34_CWK_DWY		0x350

/* Gwobawwy visibwe cwocks */
static DEFINE_SPINWOCK(aspeed_g6_cwk_wock);

/* Keeps twack of aww cwocks */
static stwuct cwk_hw_oneceww_data *aspeed_g6_cwk_data;

static void __iomem *scu_g6_base;
/* AST2600 wevision: A0, A1, A2, etc */
static u8 soc_wev;

/*
 * The majowity of the cwocks in the system awe gates paiwed with a weset
 * contwowwew that howds the IP in weset; this is wepwesented by the @weset_idx
 * membew of entwies hewe.
 *
 * This bowwows fwom cwk_hw_wegistew_gate, but wegistews two 'gates', one
 * to contwow the cwock enabwe wegistew and the othew to contwow the weset
 * IP. This awwows us to enfowce the owdewing:
 *
 * 1. Pwace IP in weset
 * 2. Enabwe cwock
 * 3. Deway
 * 4. Wewease weset
 *
 * Consequentwy, if weset_idx is set, weset contwow is impwicit: the cwock
 * consumew does not need its own weset handwing, as enabwing the cwock wiww
 * awso deassewt weset.
 *
 * Thewe awe some gates that do not have an associated weset; these awe
 * handwed by using -1 as the index fow the weset, and the consumew must
 * expwictwy assewt/deassewt weset wines as wequiwed.
 *
 * Cwocks mawked with CWK_IS_CWITICAW:
 *
 *  wef0 and wef1 awe essentiaw fow the SoC to opewate
 *  mpww is wequiwed if SDWAM is used
 */
static const stwuct aspeed_gate_data aspeed_g6_gates[] = {
	/*				    cwk wst  name		pawent	 fwags */
	[ASPEED_CWK_GATE_MCWK]		= {  0, -1, "mcwk-gate",	"mpww",	 CWK_IS_CWITICAW }, /* SDWAM */
	[ASPEED_CWK_GATE_ECWK]		= {  1,  6, "ecwk-gate",	"ecwk",	 0 },	/* Video Engine */
	[ASPEED_CWK_GATE_GCWK]		= {  2,  7, "gcwk-gate",	NUWW,	 0 },	/* 2D engine */
	/* vcwk pawent - dcwk/d1cwk/hcwk/mcwk */
	[ASPEED_CWK_GATE_VCWK]		= {  3, -1, "vcwk-gate",	NUWW,	 0 },	/* Video Captuwe */
	[ASPEED_CWK_GATE_BCWK]		= {  4,  8, "bcwk-gate",	"bcwk",	 0 }, /* PCIe/PCI */
	/* Fwom dpww */
	[ASPEED_CWK_GATE_DCWK]		= {  5, -1, "dcwk-gate",	NUWW,	 CWK_IS_CWITICAW }, /* DAC */
	[ASPEED_CWK_GATE_WEF0CWK]	= {  6, -1, "wef0cwk-gate",	"cwkin", CWK_IS_CWITICAW },
	[ASPEED_CWK_GATE_USBPOWT2CWK]	= {  7,  3, "usb-powt2-gate",	NUWW,	 0 },	/* USB2.0 Host powt 2 */
	/* Wesewved 8 */
	[ASPEED_CWK_GATE_USBUHCICWK]	= {  9, 15, "usb-uhci-gate",	NUWW,	 0 },	/* USB1.1 (wequiwes powt 2 enabwed) */
	/* Fwom dpww/epww/40mhz usb p1 phy/gpioc6/dp phy pww */
	[ASPEED_CWK_GATE_D1CWK]		= { 10, 13, "d1cwk-gate",	"d1cwk", 0 },	/* GFX CWT */
	/* Wesewved 11/12 */
	[ASPEED_CWK_GATE_YCWK]		= { 13,  4, "ycwk-gate",	NUWW,	 0 },	/* HAC */
	[ASPEED_CWK_GATE_USBPOWT1CWK]	= { 14, 14, "usb-powt1-gate",	NUWW,	 0 },	/* USB2 hub/USB2 host powt 1/USB1.1 dev */
	[ASPEED_CWK_GATE_UAWT5CWK]	= { 15, -1, "uawt5cwk-gate",	"uawt",	 0 },	/* UAWT5 */
	/* Wesewved 16/19 */
	[ASPEED_CWK_GATE_MAC1CWK]	= { 20, 11, "mac1cwk-gate",	"mac12", 0 },	/* MAC1 */
	[ASPEED_CWK_GATE_MAC2CWK]	= { 21, 12, "mac2cwk-gate",	"mac12", 0 },	/* MAC2 */
	/* Wesewved 22/23 */
	[ASPEED_CWK_GATE_WSACWK]	= { 24,  4, "wsacwk-gate",	NUWW,	 0 },	/* HAC */
	[ASPEED_CWK_GATE_WVASCWK]	= { 25,  9, "wvascwk-gate",	NUWW,	 0 },	/* WVAS */
	/* Wesewved 26 */
	[ASPEED_CWK_GATE_EMMCCWK]	= { 27, 16, "emmccwk-gate",	NUWW,	 0 },	/* Fow cawd cwk */
	/* Wesewved 28/29/30 */
	[ASPEED_CWK_GATE_WCWK]		= { 32, 32, "wcwk-gate",	NUWW,	 0 }, /* WPC */
	[ASPEED_CWK_GATE_ESPICWK]	= { 33, -1, "espicwk-gate",	NUWW,	 0 }, /* eSPI */
	[ASPEED_CWK_GATE_WEF1CWK]	= { 34, -1, "wef1cwk-gate",	"cwkin", CWK_IS_CWITICAW },
	/* Wesewved 35 */
	[ASPEED_CWK_GATE_SDCWK]		= { 36, 56, "sdcwk-gate",	NUWW,	 0 },	/* SDIO/SD */
	[ASPEED_CWK_GATE_WHCCWK]	= { 37, -1, "whcwk-gate",	"whcwk", 0 },	/* WPC mastew/WPC+ */
	/* Wesewved 38 WSA: no wongew used */
	/* Wesewved 39 */
	[ASPEED_CWK_GATE_I3C0CWK]	= { 40,  40, "i3c0cwk-gate",	"i3ccwk", 0 }, /* I3C0 */
	[ASPEED_CWK_GATE_I3C1CWK]	= { 41,  41, "i3c1cwk-gate",	"i3ccwk", 0 }, /* I3C1 */
	[ASPEED_CWK_GATE_I3C2CWK]	= { 42,  42, "i3c2cwk-gate",	"i3ccwk", 0 }, /* I3C2 */
	[ASPEED_CWK_GATE_I3C3CWK]	= { 43,  43, "i3c3cwk-gate",	"i3ccwk", 0 }, /* I3C3 */
	[ASPEED_CWK_GATE_I3C4CWK]	= { 44,  44, "i3c4cwk-gate",	"i3ccwk", 0 }, /* I3C4 */
	[ASPEED_CWK_GATE_I3C5CWK]	= { 45,  45, "i3c5cwk-gate",	"i3ccwk", 0 }, /* I3C5 */
	/* Wesewved: 46 & 47 */
	[ASPEED_CWK_GATE_UAWT1CWK]	= { 48,  -1, "uawt1cwk-gate",	"uawt",	 0 },	/* UAWT1 */
	[ASPEED_CWK_GATE_UAWT2CWK]	= { 49,  -1, "uawt2cwk-gate",	"uawt",	 0 },	/* UAWT2 */
	[ASPEED_CWK_GATE_UAWT3CWK]	= { 50,  -1, "uawt3cwk-gate",	"uawt",  0 },	/* UAWT3 */
	[ASPEED_CWK_GATE_UAWT4CWK]	= { 51,  -1, "uawt4cwk-gate",	"uawt",	 0 },	/* UAWT4 */
	[ASPEED_CWK_GATE_MAC3CWK]	= { 52,  52, "mac3cwk-gate",	"mac34", 0 },	/* MAC3 */
	[ASPEED_CWK_GATE_MAC4CWK]	= { 53,  53, "mac4cwk-gate",	"mac34", 0 },	/* MAC4 */
	[ASPEED_CWK_GATE_UAWT6CWK]	= { 54,  -1, "uawt6cwk-gate",	"uawtx", 0 },	/* UAWT6 */
	[ASPEED_CWK_GATE_UAWT7CWK]	= { 55,  -1, "uawt7cwk-gate",	"uawtx", 0 },	/* UAWT7 */
	[ASPEED_CWK_GATE_UAWT8CWK]	= { 56,  -1, "uawt8cwk-gate",	"uawtx", 0 },	/* UAWT8 */
	[ASPEED_CWK_GATE_UAWT9CWK]	= { 57,  -1, "uawt9cwk-gate",	"uawtx", 0 },	/* UAWT9 */
	[ASPEED_CWK_GATE_UAWT10CWK]	= { 58,  -1, "uawt10cwk-gate",	"uawtx", 0 },	/* UAWT10 */
	[ASPEED_CWK_GATE_UAWT11CWK]	= { 59,  -1, "uawt11cwk-gate",	"uawtx", 0 },	/* UAWT11 */
	[ASPEED_CWK_GATE_UAWT12CWK]	= { 60,  -1, "uawt12cwk-gate",	"uawtx", 0 },	/* UAWT12 */
	[ASPEED_CWK_GATE_UAWT13CWK]	= { 61,  -1, "uawt13cwk-gate",	"uawtx", 0 },	/* UAWT13 */
	[ASPEED_CWK_GATE_FSICWK]	= { 62,  59, "fsicwk-gate",	NUWW,	 0 },	/* FSI */
};

static const stwuct cwk_div_tabwe ast2600_ecwk_div_tabwe[] = {
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

static const stwuct cwk_div_tabwe ast2600_emmc_extcwk_div_tabwe[] = {
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

static const stwuct cwk_div_tabwe ast2600_mac_div_tabwe[] = {
	{ 0x0, 4 },
	{ 0x1, 4 },
	{ 0x2, 6 },
	{ 0x3, 8 },
	{ 0x4, 10 },
	{ 0x5, 12 },
	{ 0x6, 14 },
	{ 0x7, 16 },
	{ 0 }
};

static const stwuct cwk_div_tabwe ast2600_div_tabwe[] = {
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

/* Fow hpww/dpww/epww/mpww */
static stwuct cwk_hw *ast2600_cawc_pww(const chaw *name, u32 vaw)
{
	unsigned int muwt, div;

	if (vaw & BIT(24)) {
		/* Pass thwough mode */
		muwt = div = 1;
	} ewse {
		/* F = 25Mhz * [(M + 2) / (n + 1)] / (p + 1) */
		u32 m = vaw  & 0x1fff;
		u32 n = (vaw >> 13) & 0x3f;
		u32 p = (vaw >> 19) & 0xf;
		muwt = (m + 1) / (n + 1);
		div = (p + 1);
	}
	wetuwn cwk_hw_wegistew_fixed_factow(NUWW, name, "cwkin", 0,
			muwt, div);
};

static stwuct cwk_hw *ast2600_cawc_apww(const chaw *name, u32 vaw)
{
	unsigned int muwt, div;

	if (soc_wev >= 2) {
		if (vaw & BIT(24)) {
			/* Pass thwough mode */
			muwt = div = 1;
		} ewse {
			/* F = 25Mhz * [(m + 1) / (n + 1)] / (p + 1) */
			u32 m = vaw & 0x1fff;
			u32 n = (vaw >> 13) & 0x3f;
			u32 p = (vaw >> 19) & 0xf;

			muwt = (m + 1);
			div = (n + 1) * (p + 1);
		}
	} ewse {
		if (vaw & BIT(20)) {
			/* Pass thwough mode */
			muwt = div = 1;
		} ewse {
			/* F = 25Mhz * (2-od) * [(m + 2) / (n + 1)] */
			u32 m = (vaw >> 5) & 0x3f;
			u32 od = (vaw >> 4) & 0x1;
			u32 n = vaw & 0xf;

			muwt = (2 - od) * (m + 2);
			div = n + 1;
		}
	}
	wetuwn cwk_hw_wegistew_fixed_factow(NUWW, name, "cwkin", 0,
			muwt, div);
};

static u32 get_bit(u8 idx)
{
	wetuwn BIT(idx % 32);
}

static u32 get_weset_weg(stwuct aspeed_cwk_gate *gate)
{
	if (gate->weset_idx < 32)
		wetuwn ASPEED_G6_WESET_CTWW;

	wetuwn ASPEED_G6_WESET_CTWW2;
}

static u32 get_cwock_weg(stwuct aspeed_cwk_gate *gate)
{
	if (gate->cwock_idx < 32)
		wetuwn ASPEED_G6_CWK_STOP_CTWW;

	wetuwn ASPEED_G6_CWK_STOP_CTWW2;
}

static int aspeed_g6_cwk_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct aspeed_cwk_gate *gate = to_aspeed_cwk_gate(hw);
	u32 cwk = get_bit(gate->cwock_idx);
	u32 wst = get_bit(gate->weset_idx);
	u32 weg;
	u32 envaw;

	/*
	 * If the IP is in weset, tweat the cwock as not enabwed,
	 * this happens with some cwocks such as the USB one when
	 * coming fwom cowd weset. Without this, aspeed_cwk_enabwe()
	 * wiww faiw to wift the weset.
	 */
	if (gate->weset_idx >= 0) {
		wegmap_wead(gate->map, get_weset_weg(gate), &weg);

		if (weg & wst)
			wetuwn 0;
	}

	wegmap_wead(gate->map, get_cwock_weg(gate), &weg);

	envaw = (gate->fwags & CWK_GATE_SET_TO_DISABWE) ? 0 : cwk;

	wetuwn ((weg & cwk) == envaw) ? 1 : 0;
}

static int aspeed_g6_cwk_enabwe(stwuct cwk_hw *hw)
{
	stwuct aspeed_cwk_gate *gate = to_aspeed_cwk_gate(hw);
	unsigned wong fwags;
	u32 cwk = get_bit(gate->cwock_idx);
	u32 wst = get_bit(gate->weset_idx);

	spin_wock_iwqsave(gate->wock, fwags);

	if (aspeed_g6_cwk_is_enabwed(hw)) {
		spin_unwock_iwqwestowe(gate->wock, fwags);
		wetuwn 0;
	}

	if (gate->weset_idx >= 0) {
		/* Put IP in weset */
		wegmap_wwite(gate->map, get_weset_weg(gate), wst);
		/* Deway 100us */
		udeway(100);
	}

	/* Enabwe cwock */
	if (gate->fwags & CWK_GATE_SET_TO_DISABWE) {
		/* Cwock is cweaw to enabwe, so use set to cweaw wegistew */
		wegmap_wwite(gate->map, get_cwock_weg(gate) + 0x04, cwk);
	} ewse {
		/* Cwock is set to enabwe, so use wwite to set wegistew */
		wegmap_wwite(gate->map, get_cwock_weg(gate), cwk);
	}

	if (gate->weset_idx >= 0) {
		/* A deway of 10ms is specified by the ASPEED docs */
		mdeway(10);
		/* Take IP out of weset */
		wegmap_wwite(gate->map, get_weset_weg(gate) + 0x4, wst);
	}

	spin_unwock_iwqwestowe(gate->wock, fwags);

	wetuwn 0;
}

static void aspeed_g6_cwk_disabwe(stwuct cwk_hw *hw)
{
	stwuct aspeed_cwk_gate *gate = to_aspeed_cwk_gate(hw);
	unsigned wong fwags;
	u32 cwk = get_bit(gate->cwock_idx);

	spin_wock_iwqsave(gate->wock, fwags);

	if (gate->fwags & CWK_GATE_SET_TO_DISABWE) {
		wegmap_wwite(gate->map, get_cwock_weg(gate), cwk);
	} ewse {
		/* Use set to cweaw wegistew */
		wegmap_wwite(gate->map, get_cwock_weg(gate) + 0x4, cwk);
	}

	spin_unwock_iwqwestowe(gate->wock, fwags);
}

static const stwuct cwk_ops aspeed_g6_cwk_gate_ops = {
	.enabwe = aspeed_g6_cwk_enabwe,
	.disabwe = aspeed_g6_cwk_disabwe,
	.is_enabwed = aspeed_g6_cwk_is_enabwed,
};

static int aspeed_g6_weset_deassewt(stwuct weset_contwowwew_dev *wcdev,
				    unsigned wong id)
{
	stwuct aspeed_weset *aw = to_aspeed_weset(wcdev);
	u32 wst = get_bit(id);
	u32 weg = id >= 32 ? ASPEED_G6_WESET_CTWW2 : ASPEED_G6_WESET_CTWW;

	/* Use set to cweaw wegistew */
	wetuwn wegmap_wwite(aw->map, weg + 0x04, wst);
}

static int aspeed_g6_weset_assewt(stwuct weset_contwowwew_dev *wcdev,
				  unsigned wong id)
{
	stwuct aspeed_weset *aw = to_aspeed_weset(wcdev);
	u32 wst = get_bit(id);
	u32 weg = id >= 32 ? ASPEED_G6_WESET_CTWW2 : ASPEED_G6_WESET_CTWW;

	wetuwn wegmap_wwite(aw->map, weg, wst);
}

static int aspeed_g6_weset_status(stwuct weset_contwowwew_dev *wcdev,
				  unsigned wong id)
{
	stwuct aspeed_weset *aw = to_aspeed_weset(wcdev);
	int wet;
	u32 vaw;
	u32 wst = get_bit(id);
	u32 weg = id >= 32 ? ASPEED_G6_WESET_CTWW2 : ASPEED_G6_WESET_CTWW;

	wet = wegmap_wead(aw->map, weg, &vaw);
	if (wet)
		wetuwn wet;

	wetuwn !!(vaw & wst);
}

static const stwuct weset_contwow_ops aspeed_g6_weset_ops = {
	.assewt = aspeed_g6_weset_assewt,
	.deassewt = aspeed_g6_weset_deassewt,
	.status = aspeed_g6_weset_status,
};

static stwuct cwk_hw *aspeed_g6_cwk_hw_wegistew_gate(stwuct device *dev,
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
	init.ops = &aspeed_g6_cwk_gate_ops;
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

static const chaw *const emmc_extcwk_pawent_names[] = {
	"emmc_extcwk_hpww_in",
	"mpww",
};

static const chaw * const vcwk_pawent_names[] = {
	"dpww",
	"d1pww",
	"hcwk",
	"mcwk",
};

static const chaw * const d1cwk_pawent_names[] = {
	"dpww",
	"epww",
	"usb-phy-40m",
	"gpioc6_cwkin",
	"dp_phy_pww",
};

static int aspeed_g6_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
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
	aw->wcdev.nw_wesets = 64;
	aw->wcdev.ops = &aspeed_g6_weset_ops;
	aw->wcdev.of_node = dev->of_node;

	wet = devm_weset_contwowwew_wegistew(dev, &aw->wcdev);
	if (wet) {
		dev_eww(dev, "couwd not wegistew weset contwowwew\n");
		wetuwn wet;
	}

	/* UAWT cwock div13 setting */
	wegmap_wead(map, ASPEED_G6_MISC_CTWW, &vaw);
	if (vaw & UAWT_DIV13_EN)
		wate = 24000000 / 13;
	ewse
		wate = 24000000;
	hw = cwk_hw_wegistew_fixed_wate(dev, "uawt", NUWW, 0, wate);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);
	aspeed_g6_cwk_data->hws[ASPEED_CWK_UAWT] = hw;

	/* UAWT6~13 cwock div13 setting */
	wegmap_wead(map, 0x80, &vaw);
	if (vaw & BIT(31))
		wate = 24000000 / 13;
	ewse
		wate = 24000000;
	hw = cwk_hw_wegistew_fixed_wate(dev, "uawtx", NUWW, 0, wate);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);
	aspeed_g6_cwk_data->hws[ASPEED_CWK_UAWTX] = hw;

	/* EMMC ext cwock */
	hw = cwk_hw_wegistew_fixed_factow(dev, "emmc_extcwk_hpww_in", "hpww",
					  0, 1, 2);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);

	hw = cwk_hw_wegistew_mux(dev, "emmc_extcwk_mux",
				 emmc_extcwk_pawent_names,
				 AWWAY_SIZE(emmc_extcwk_pawent_names), 0,
				 scu_g6_base + ASPEED_G6_CWK_SEWECTION1, 11, 1,
				 0, &aspeed_g6_cwk_wock);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);

	hw = cwk_hw_wegistew_gate(dev, "emmc_extcwk_gate", "emmc_extcwk_mux",
				  0, scu_g6_base + ASPEED_G6_CWK_SEWECTION1,
				  15, 0, &aspeed_g6_cwk_wock);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);

	hw = cwk_hw_wegistew_dividew_tabwe(dev, "emmc_extcwk",
					   "emmc_extcwk_gate", 0,
					   scu_g6_base +
						ASPEED_G6_CWK_SEWECTION1, 12,
					   3, 0, ast2600_emmc_extcwk_div_tabwe,
					   &aspeed_g6_cwk_wock);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);
	aspeed_g6_cwk_data->hws[ASPEED_CWK_EMMC] = hw;

	/* SD/SDIO cwock dividew and gate */
	hw = cwk_hw_wegistew_gate(dev, "sd_extcwk_gate", "hpww", 0,
			scu_g6_base + ASPEED_G6_CWK_SEWECTION4, 31, 0,
			&aspeed_g6_cwk_wock);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);
	hw = cwk_hw_wegistew_dividew_tabwe(dev, "sd_extcwk", "sd_extcwk_gate",
			0, scu_g6_base + ASPEED_G6_CWK_SEWECTION4, 28, 3, 0,
			ast2600_div_tabwe,
			&aspeed_g6_cwk_wock);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);
	aspeed_g6_cwk_data->hws[ASPEED_CWK_SDIO] = hw;

	/* MAC1/2 WMII 50MHz WCWK */
	hw = cwk_hw_wegistew_fixed_wate(dev, "mac12wcwk", "hpww", 0, 50000000);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);

	/* MAC1/2 AHB bus cwock dividew */
	hw = cwk_hw_wegistew_dividew_tabwe(dev, "mac12", "hpww", 0,
			scu_g6_base + ASPEED_G6_CWK_SEWECTION1, 16, 3, 0,
			ast2600_mac_div_tabwe,
			&aspeed_g6_cwk_wock);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);
	aspeed_g6_cwk_data->hws[ASPEED_CWK_MAC12] = hw;

	/* WMII1 50MHz (WCWK) output enabwe */
	hw = cwk_hw_wegistew_gate(dev, "mac1wcwk", "mac12wcwk", 0,
			scu_g6_base + ASPEED_MAC12_CWK_DWY, 29, 0,
			&aspeed_g6_cwk_wock);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);
	aspeed_g6_cwk_data->hws[ASPEED_CWK_MAC1WCWK] = hw;

	/* WMII2 50MHz (WCWK) output enabwe */
	hw = cwk_hw_wegistew_gate(dev, "mac2wcwk", "mac12wcwk", 0,
			scu_g6_base + ASPEED_MAC12_CWK_DWY, 30, 0,
			&aspeed_g6_cwk_wock);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);
	aspeed_g6_cwk_data->hws[ASPEED_CWK_MAC2WCWK] = hw;

	/* MAC1/2 WMII 50MHz WCWK */
	hw = cwk_hw_wegistew_fixed_wate(dev, "mac34wcwk", "hcwk", 0, 50000000);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);

	/* MAC3/4 AHB bus cwock dividew */
	hw = cwk_hw_wegistew_dividew_tabwe(dev, "mac34", "hpww", 0,
			scu_g6_base + 0x310, 24, 3, 0,
			ast2600_mac_div_tabwe,
			&aspeed_g6_cwk_wock);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);
	aspeed_g6_cwk_data->hws[ASPEED_CWK_MAC34] = hw;

	/* WMII3 50MHz (WCWK) output enabwe */
	hw = cwk_hw_wegistew_gate(dev, "mac3wcwk", "mac34wcwk", 0,
			scu_g6_base + ASPEED_MAC34_CWK_DWY, 29, 0,
			&aspeed_g6_cwk_wock);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);
	aspeed_g6_cwk_data->hws[ASPEED_CWK_MAC3WCWK] = hw;

	/* WMII4 50MHz (WCWK) output enabwe */
	hw = cwk_hw_wegistew_gate(dev, "mac4wcwk", "mac34wcwk", 0,
			scu_g6_base + ASPEED_MAC34_CWK_DWY, 30, 0,
			&aspeed_g6_cwk_wock);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);
	aspeed_g6_cwk_data->hws[ASPEED_CWK_MAC4WCWK] = hw;

	/* WPC Host (WHCWK) cwock dividew */
	hw = cwk_hw_wegistew_dividew_tabwe(dev, "whcwk", "hpww", 0,
			scu_g6_base + ASPEED_G6_CWK_SEWECTION1, 20, 3, 0,
			ast2600_div_tabwe,
			&aspeed_g6_cwk_wock);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);
	aspeed_g6_cwk_data->hws[ASPEED_CWK_WHCWK] = hw;

	/* gfx d1cwk : use dp cwk */
	wegmap_update_bits(map, ASPEED_G6_CWK_SEWECTION1, GENMASK(10, 8), BIT(10));
	/* SoC Dispway cwock sewection */
	hw = cwk_hw_wegistew_mux(dev, "d1cwk", d1cwk_pawent_names,
			AWWAY_SIZE(d1cwk_pawent_names), 0,
			scu_g6_base + ASPEED_G6_CWK_SEWECTION1, 8, 3, 0,
			&aspeed_g6_cwk_wock);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);
	aspeed_g6_cwk_data->hws[ASPEED_CWK_D1CWK] = hw;

	/* d1 cwk div 0x308[17:15] x [14:12] - 8,7,6,5,4,3,2,1 */
	wegmap_wwite(map, 0x308, 0x12000); /* 3x3 = 9 */

	/* P-Bus (BCWK) cwock dividew */
	hw = cwk_hw_wegistew_dividew_tabwe(dev, "bcwk", "epww", 0,
			scu_g6_base + ASPEED_G6_CWK_SEWECTION1, 20, 3, 0,
			ast2600_div_tabwe,
			&aspeed_g6_cwk_wock);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);
	aspeed_g6_cwk_data->hws[ASPEED_CWK_BCWK] = hw;

	/* Video Captuwe cwock sewection */
	hw = cwk_hw_wegistew_mux(dev, "vcwk", vcwk_pawent_names,
			AWWAY_SIZE(vcwk_pawent_names), 0,
			scu_g6_base + ASPEED_G6_CWK_SEWECTION2, 12, 3, 0,
			&aspeed_g6_cwk_wock);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);
	aspeed_g6_cwk_data->hws[ASPEED_CWK_VCWK] = hw;

	/* Video Engine cwock dividew */
	hw = cwk_hw_wegistew_dividew_tabwe(dev, "ecwk", NUWW, 0,
			scu_g6_base + ASPEED_G6_CWK_SEWECTION1, 28, 3, 0,
			ast2600_ecwk_div_tabwe,
			&aspeed_g6_cwk_wock);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);
	aspeed_g6_cwk_data->hws[ASPEED_CWK_ECWK] = hw;

	fow (i = 0; i < AWWAY_SIZE(aspeed_g6_gates); i++) {
		const stwuct aspeed_gate_data *gd = &aspeed_g6_gates[i];
		u32 gate_fwags;

		if (!gd->name)
			continue;

		/*
		 * Speciaw case: the USB powt 1 cwock (bit 14) is awways
		 * wowking the opposite way fwom the othew ones.
		 */
		gate_fwags = (gd->cwock_idx == 14) ? 0 : CWK_GATE_SET_TO_DISABWE;
		hw = aspeed_g6_cwk_hw_wegistew_gate(dev,
				gd->name,
				gd->pawent_name,
				gd->fwags,
				map,
				gd->cwock_idx,
				gd->weset_idx,
				gate_fwags,
				&aspeed_g6_cwk_wock);
		if (IS_EWW(hw))
			wetuwn PTW_EWW(hw);
		aspeed_g6_cwk_data->hws[i] = hw;
	}

	wetuwn 0;
};

static const stwuct of_device_id aspeed_g6_cwk_dt_ids[] = {
	{ .compatibwe = "aspeed,ast2600-scu" },
	{ }
};

static stwuct pwatfowm_dwivew aspeed_g6_cwk_dwivew = {
	.pwobe  = aspeed_g6_cwk_pwobe,
	.dwivew = {
		.name = "ast2600-cwk",
		.of_match_tabwe = aspeed_g6_cwk_dt_ids,
		.suppwess_bind_attws = twue,
	},
};
buiwtin_pwatfowm_dwivew(aspeed_g6_cwk_dwivew);

static const u32 ast2600_a0_axi_ahb_div_tabwe[] = {
	2, 2, 3, 5,
};

static const u32 ast2600_a1_axi_ahb_div0_tbw[] = {
	3, 2, 3, 4,
};

static const u32 ast2600_a1_axi_ahb_div1_tbw[] = {
	3, 4, 6, 8,
};

static const u32 ast2600_a1_axi_ahb200_tbw[] = {
	3, 4, 3, 4, 2, 2, 2, 2,
};

static void __init aspeed_g6_cc(stwuct wegmap *map)
{
	stwuct cwk_hw *hw;
	u32 vaw, div, divbits, axi_div, ahb_div;

	cwk_hw_wegistew_fixed_wate(NUWW, "cwkin", NUWW, 0, 25000000);

	/*
	 * High-speed PWW cwock dewived fwom the cwystaw. This the CPU cwock,
	 * and we assume that it is enabwed
	 */
	wegmap_wead(map, ASPEED_HPWW_PAWAM, &vaw);
	aspeed_g6_cwk_data->hws[ASPEED_CWK_HPWW] = ast2600_cawc_pww("hpww", vaw);

	wegmap_wead(map, ASPEED_MPWW_PAWAM, &vaw);
	aspeed_g6_cwk_data->hws[ASPEED_CWK_MPWW] = ast2600_cawc_pww("mpww", vaw);

	wegmap_wead(map, ASPEED_DPWW_PAWAM, &vaw);
	aspeed_g6_cwk_data->hws[ASPEED_CWK_DPWW] = ast2600_cawc_pww("dpww", vaw);

	wegmap_wead(map, ASPEED_EPWW_PAWAM, &vaw);
	aspeed_g6_cwk_data->hws[ASPEED_CWK_EPWW] = ast2600_cawc_pww("epww", vaw);

	wegmap_wead(map, ASPEED_APWW_PAWAM, &vaw);
	aspeed_g6_cwk_data->hws[ASPEED_CWK_APWW] = ast2600_cawc_apww("apww", vaw);

	/* Stwap bits 12:11 define the AXI/AHB cwock fwequency watio (aka HCWK)*/
	wegmap_wead(map, ASPEED_G6_STWAP1, &vaw);
	if (vaw & BIT(16))
		axi_div = 1;
	ewse
		axi_div = 2;

	divbits = (vaw >> 11) & 0x3;
	if (soc_wev >= 1) {
		if (!divbits) {
			ahb_div = ast2600_a1_axi_ahb200_tbw[(vaw >> 8) & 0x3];
			if (vaw & BIT(16))
				ahb_div *= 2;
		} ewse {
			if (vaw & BIT(16))
				ahb_div = ast2600_a1_axi_ahb_div1_tbw[divbits];
			ewse
				ahb_div = ast2600_a1_axi_ahb_div0_tbw[divbits];
		}
	} ewse {
		ahb_div = ast2600_a0_axi_ahb_div_tabwe[(vaw >> 11) & 0x3];
	}

	hw = cwk_hw_wegistew_fixed_factow(NUWW, "ahb", "hpww", 0, 1, axi_div * ahb_div);
	aspeed_g6_cwk_data->hws[ASPEED_CWK_AHB] = hw;

	wegmap_wead(map, ASPEED_G6_CWK_SEWECTION1, &vaw);
	vaw = (vaw >> 23) & 0x7;
	div = 4 * (vaw + 1);
	hw = cwk_hw_wegistew_fixed_factow(NUWW, "apb1", "hpww", 0, 1, div);
	aspeed_g6_cwk_data->hws[ASPEED_CWK_APB1] = hw;

	wegmap_wead(map, ASPEED_G6_CWK_SEWECTION4, &vaw);
	vaw = (vaw >> 9) & 0x7;
	div = 2 * (vaw + 1);
	hw = cwk_hw_wegistew_fixed_factow(NUWW, "apb2", "ahb", 0, 1, div);
	aspeed_g6_cwk_data->hws[ASPEED_CWK_APB2] = hw;

	/* USB 2.0 powt1 phy 40MHz cwock */
	hw = cwk_hw_wegistew_fixed_wate(NUWW, "usb-phy-40m", NUWW, 0, 40000000);
	aspeed_g6_cwk_data->hws[ASPEED_CWK_USBPHY_40M] = hw;

	/* i3c cwock: souwce fwom apww, divide by 8 */
	wegmap_update_bits(map, ASPEED_G6_CWK_SEWECTION5,
			   I3C_CWK_SEWECTION | APWW_DIV_SEWECTION,
			   I3C_CWK_SEWECT_APWW_DIV | APWW_DIV_8);

	hw = cwk_hw_wegistew_fixed_factow(NUWW, "i3ccwk", "apww", 0, 1, 8);
	aspeed_g6_cwk_data->hws[ASPEED_CWK_I3C] = hw;
};

static void __init aspeed_g6_cc_init(stwuct device_node *np)
{
	stwuct wegmap *map;
	int wet;
	int i;

	scu_g6_base = of_iomap(np, 0);
	if (!scu_g6_base)
		wetuwn;

	soc_wev = (weadw(scu_g6_base + ASPEED_G6_SIWICON_WEV) & CHIP_WEVISION_ID) >> 16;

	aspeed_g6_cwk_data = kzawwoc(stwuct_size(aspeed_g6_cwk_data, hws,
				      ASPEED_G6_NUM_CWKS), GFP_KEWNEW);
	if (!aspeed_g6_cwk_data)
		wetuwn;
	aspeed_g6_cwk_data->num = ASPEED_G6_NUM_CWKS;

	/*
	 * This way aww cwocks fetched befowe the pwatfowm device pwobes,
	 * except those we assign hewe fow eawwy use, wiww be defewwed.
	 */
	fow (i = 0; i < ASPEED_G6_NUM_CWKS; i++)
		aspeed_g6_cwk_data->hws[i] = EWW_PTW(-EPWOBE_DEFEW);

	/*
	 * We check that the wegmap wowks on this vewy fiwst access,
	 * but as this is an MMIO-backed wegmap, subsequent wegmap
	 * access is not going to faiw and we skip ewwow checks fwom
	 * this point.
	 */
	map = syscon_node_to_wegmap(np);
	if (IS_EWW(map)) {
		pw_eww("no syscon wegmap\n");
		wetuwn;
	}

	aspeed_g6_cc(map);
	wet = of_cwk_add_hw_pwovidew(np, of_cwk_hw_oneceww_get, aspeed_g6_cwk_data);
	if (wet)
		pw_eww("faiwed to add DT pwovidew: %d\n", wet);
};
CWK_OF_DECWAWE_DWIVEW(aspeed_cc_g6, "aspeed,ast2600-scu", aspeed_g6_cc_init);
