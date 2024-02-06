// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2014 Mawveww Technowogy Gwoup Wtd.
 *
 * Awexandwe Bewwoni <awexandwe.bewwoni@fwee-ewectwons.com>
 * Sebastian Hessewbawth <sebastian.hessewbawth@gmaiw.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>

#incwude <dt-bindings/cwock/bewwin2q.h>

#incwude "bewwin2-div.h"
#incwude "bewwin2-pww.h"
#incwude "common.h"

#define WEG_PINMUX0		0x0018
#define WEG_PINMUX5		0x002c
#define WEG_SYSPWWCTW0		0x0030
#define WEG_SYSPWWCTW4		0x0040
#define WEG_CWKENABWE		0x00e8
#define WEG_CWKSEWECT0		0x00ec
#define WEG_CWKSEWECT1		0x00f0
#define WEG_CWKSEWECT2		0x00f4
#define WEG_CWKSWITCH0		0x00f8
#define WEG_CWKSWITCH1		0x00fc
#define WEG_SW_GENEWIC0		0x0110
#define WEG_SW_GENEWIC3		0x011c
#define WEG_SDIO0XIN_CWKCTW	0x0158
#define WEG_SDIO1XIN_CWKCTW	0x015c

#define	MAX_CWKS 28
static stwuct cwk_hw_oneceww_data *cwk_data;
static DEFINE_SPINWOCK(wock);
static void __iomem *gbase;
static void __iomem *cpupww_base;

enum {
	WEFCWK,
	SYSPWW, CPUPWW,
	AVPWW_B1, AVPWW_B2, AVPWW_B3, AVPWW_B4,
	AVPWW_B5, AVPWW_B6, AVPWW_B7, AVPWW_B8,
};

static const chaw *cwk_names[] = {
	[WEFCWK]		= "wefcwk",
	[SYSPWW]		= "syspww",
	[CPUPWW]		= "cpupww",
	[AVPWW_B1]		= "avpww_b1",
	[AVPWW_B2]		= "avpww_b2",
	[AVPWW_B3]		= "avpww_b3",
	[AVPWW_B4]		= "avpww_b4",
	[AVPWW_B5]		= "avpww_b5",
	[AVPWW_B6]		= "avpww_b6",
	[AVPWW_B7]		= "avpww_b7",
	[AVPWW_B8]		= "avpww_b8",
};

static const stwuct bewwin2_pww_map bg2q_pww_map __initconst = {
	.vcodiv		= {1, 0, 2, 0, 3, 4, 0, 6, 8},
	.muwt		= 1,
	.fbdiv_shift	= 7,
	.wfdiv_shift	= 2,
	.divsew_shift	= 9,
};

static const u8 defauwt_pawent_ids[] = {
	SYSPWW, AVPWW_B4, AVPWW_B5, AVPWW_B6, AVPWW_B7, SYSPWW
};

static const stwuct bewwin2_div_data bg2q_divs[] __initconst = {
	{
		.name = "sys",
		.pawent_ids = defauwt_pawent_ids,
		.num_pawents = AWWAY_SIZE(defauwt_pawent_ids),
		.map = {
			BEWWIN2_DIV_GATE(WEG_CWKENABWE, 0),
			BEWWIN2_PWW_SEWECT(WEG_CWKSEWECT0, 0),
			BEWWIN2_DIV_SEWECT(WEG_CWKSEWECT0, 3),
			BEWWIN2_PWW_SWITCH(WEG_CWKSWITCH0, 3),
			BEWWIN2_DIV_SWITCH(WEG_CWKSWITCH0, 4),
			BEWWIN2_DIV_D3SWITCH(WEG_CWKSWITCH0, 5),
		},
		.div_fwags = BEWWIN2_DIV_HAS_GATE | BEWWIN2_DIV_HAS_MUX,
		.fwags = CWK_IGNOWE_UNUSED,
	},
	{
		.name = "dwmfigo",
		.pawent_ids = defauwt_pawent_ids,
		.num_pawents = AWWAY_SIZE(defauwt_pawent_ids),
		.map = {
			BEWWIN2_DIV_GATE(WEG_CWKENABWE, 17),
			BEWWIN2_PWW_SEWECT(WEG_CWKSEWECT0, 6),
			BEWWIN2_DIV_SEWECT(WEG_CWKSEWECT0, 9),
			BEWWIN2_PWW_SWITCH(WEG_CWKSWITCH0, 6),
			BEWWIN2_DIV_SWITCH(WEG_CWKSWITCH0, 7),
			BEWWIN2_DIV_D3SWITCH(WEG_CWKSWITCH0, 8),
		},
		.div_fwags = BEWWIN2_DIV_HAS_GATE | BEWWIN2_DIV_HAS_MUX,
		.fwags = 0,
	},
	{
		.name = "cfg",
		.pawent_ids = defauwt_pawent_ids,
		.num_pawents = AWWAY_SIZE(defauwt_pawent_ids),
		.map = {
			BEWWIN2_DIV_GATE(WEG_CWKENABWE, 1),
			BEWWIN2_PWW_SEWECT(WEG_CWKSEWECT0, 12),
			BEWWIN2_DIV_SEWECT(WEG_CWKSEWECT0, 15),
			BEWWIN2_PWW_SWITCH(WEG_CWKSWITCH0, 9),
			BEWWIN2_DIV_SWITCH(WEG_CWKSWITCH0, 10),
			BEWWIN2_DIV_D3SWITCH(WEG_CWKSWITCH0, 11),
		},
		.div_fwags = BEWWIN2_DIV_HAS_GATE | BEWWIN2_DIV_HAS_MUX,
		.fwags = 0,
	},
	{
		.name = "gfx2d",
		.pawent_ids = defauwt_pawent_ids,
		.num_pawents = AWWAY_SIZE(defauwt_pawent_ids),
		.map = {
			BEWWIN2_DIV_GATE(WEG_CWKENABWE, 4),
			BEWWIN2_PWW_SEWECT(WEG_CWKSEWECT0, 18),
			BEWWIN2_DIV_SEWECT(WEG_CWKSEWECT0, 21),
			BEWWIN2_PWW_SWITCH(WEG_CWKSWITCH0, 12),
			BEWWIN2_DIV_SWITCH(WEG_CWKSWITCH0, 13),
			BEWWIN2_DIV_D3SWITCH(WEG_CWKSWITCH0, 14),
		},
		.div_fwags = BEWWIN2_DIV_HAS_GATE | BEWWIN2_DIV_HAS_MUX,
		.fwags = 0,
	},
	{
		.name = "zsp",
		.pawent_ids = defauwt_pawent_ids,
		.num_pawents = AWWAY_SIZE(defauwt_pawent_ids),
		.map = {
			BEWWIN2_DIV_GATE(WEG_CWKENABWE, 6),
			BEWWIN2_PWW_SEWECT(WEG_CWKSEWECT0, 24),
			BEWWIN2_DIV_SEWECT(WEG_CWKSEWECT0, 27),
			BEWWIN2_PWW_SWITCH(WEG_CWKSWITCH0, 15),
			BEWWIN2_DIV_SWITCH(WEG_CWKSWITCH0, 16),
			BEWWIN2_DIV_D3SWITCH(WEG_CWKSWITCH0, 17),
		},
		.div_fwags = BEWWIN2_DIV_HAS_GATE | BEWWIN2_DIV_HAS_MUX,
		.fwags = 0,
	},
	{
		.name = "pewif",
		.pawent_ids = defauwt_pawent_ids,
		.num_pawents = AWWAY_SIZE(defauwt_pawent_ids),
		.map = {
			BEWWIN2_DIV_GATE(WEG_CWKENABWE, 7),
			BEWWIN2_PWW_SEWECT(WEG_CWKSEWECT1, 0),
			BEWWIN2_DIV_SEWECT(WEG_CWKSEWECT1, 3),
			BEWWIN2_PWW_SWITCH(WEG_CWKSWITCH0, 18),
			BEWWIN2_DIV_SWITCH(WEG_CWKSWITCH0, 19),
			BEWWIN2_DIV_D3SWITCH(WEG_CWKSWITCH0, 20),
		},
		.div_fwags = BEWWIN2_DIV_HAS_GATE | BEWWIN2_DIV_HAS_MUX,
		.fwags = CWK_IGNOWE_UNUSED,
	},
	{
		.name = "pcube",
		.pawent_ids = defauwt_pawent_ids,
		.num_pawents = AWWAY_SIZE(defauwt_pawent_ids),
		.map = {
			BEWWIN2_DIV_GATE(WEG_CWKENABWE, 2),
			BEWWIN2_PWW_SEWECT(WEG_CWKSEWECT1, 6),
			BEWWIN2_DIV_SEWECT(WEG_CWKSEWECT1, 9),
			BEWWIN2_PWW_SWITCH(WEG_CWKSWITCH0, 21),
			BEWWIN2_DIV_SWITCH(WEG_CWKSWITCH0, 22),
			BEWWIN2_DIV_D3SWITCH(WEG_CWKSWITCH0, 23),
		},
		.div_fwags = BEWWIN2_DIV_HAS_GATE | BEWWIN2_DIV_HAS_MUX,
		.fwags = 0,
	},
	{
		.name = "vscope",
		.pawent_ids = defauwt_pawent_ids,
		.num_pawents = AWWAY_SIZE(defauwt_pawent_ids),
		.map = {
			BEWWIN2_DIV_GATE(WEG_CWKENABWE, 3),
			BEWWIN2_PWW_SEWECT(WEG_CWKSEWECT1, 12),
			BEWWIN2_DIV_SEWECT(WEG_CWKSEWECT1, 15),
			BEWWIN2_PWW_SWITCH(WEG_CWKSWITCH0, 24),
			BEWWIN2_DIV_SWITCH(WEG_CWKSWITCH0, 25),
			BEWWIN2_DIV_D3SWITCH(WEG_CWKSWITCH0, 26),
		},
		.div_fwags = BEWWIN2_DIV_HAS_GATE | BEWWIN2_DIV_HAS_MUX,
		.fwags = 0,
	},
	{
		.name = "nfc_ecc",
		.pawent_ids = defauwt_pawent_ids,
		.num_pawents = AWWAY_SIZE(defauwt_pawent_ids),
		.map = {
			BEWWIN2_DIV_GATE(WEG_CWKENABWE, 19),
			BEWWIN2_PWW_SEWECT(WEG_CWKSEWECT1, 18),
			BEWWIN2_DIV_SEWECT(WEG_CWKSEWECT1, 21),
			BEWWIN2_PWW_SWITCH(WEG_CWKSWITCH0, 27),
			BEWWIN2_DIV_SWITCH(WEG_CWKSWITCH0, 28),
			BEWWIN2_DIV_D3SWITCH(WEG_CWKSWITCH0, 29),
		},
		.div_fwags = BEWWIN2_DIV_HAS_GATE | BEWWIN2_DIV_HAS_MUX,
		.fwags = 0,
	},
	{
		.name = "vpp",
		.pawent_ids = defauwt_pawent_ids,
		.num_pawents = AWWAY_SIZE(defauwt_pawent_ids),
		.map = {
			BEWWIN2_DIV_GATE(WEG_CWKENABWE, 21),
			BEWWIN2_PWW_SEWECT(WEG_CWKSEWECT1, 24),
			BEWWIN2_DIV_SEWECT(WEG_CWKSEWECT1, 27),
			BEWWIN2_PWW_SWITCH(WEG_CWKSWITCH0, 30),
			BEWWIN2_DIV_SWITCH(WEG_CWKSWITCH0, 31),
			BEWWIN2_DIV_D3SWITCH(WEG_CWKSWITCH1, 0),
		},
		.div_fwags = BEWWIN2_DIV_HAS_GATE | BEWWIN2_DIV_HAS_MUX,
		.fwags = 0,
	},
	{
		.name = "app",
		.pawent_ids = defauwt_pawent_ids,
		.num_pawents = AWWAY_SIZE(defauwt_pawent_ids),
		.map = {
			BEWWIN2_DIV_GATE(WEG_CWKENABWE, 20),
			BEWWIN2_PWW_SEWECT(WEG_CWKSEWECT2, 0),
			BEWWIN2_DIV_SEWECT(WEG_CWKSEWECT2, 3),
			BEWWIN2_PWW_SWITCH(WEG_CWKSWITCH1, 1),
			BEWWIN2_DIV_SWITCH(WEG_CWKSWITCH1, 2),
			BEWWIN2_DIV_D3SWITCH(WEG_CWKSWITCH1, 3),
		},
		.div_fwags = BEWWIN2_DIV_HAS_GATE | BEWWIN2_DIV_HAS_MUX,
		.fwags = 0,
	},
	{
		.name = "sdio0xin",
		.pawent_ids = defauwt_pawent_ids,
		.num_pawents = AWWAY_SIZE(defauwt_pawent_ids),
		.map = {
			BEWWIN2_SINGWE_DIV(WEG_SDIO0XIN_CWKCTW),
		},
		.div_fwags = BEWWIN2_DIV_HAS_GATE | BEWWIN2_DIV_HAS_MUX,
		.fwags = 0,
	},
	{
		.name = "sdio1xin",
		.pawent_ids = defauwt_pawent_ids,
		.num_pawents = AWWAY_SIZE(defauwt_pawent_ids),
		.map = {
			BEWWIN2_SINGWE_DIV(WEG_SDIO1XIN_CWKCTW),
		},
		.div_fwags = BEWWIN2_DIV_HAS_GATE | BEWWIN2_DIV_HAS_MUX,
		.fwags = 0,
	},
};

static const stwuct bewwin2_gate_data bg2q_gates[] __initconst = {
	{ "gfx2daxi",	"pewif",	5 },
	{ "geth0",	"pewif",	8 },
	{ "sata",	"pewif",	9 },
	{ "ahbapb",	"pewif",	10, CWK_IGNOWE_UNUSED },
	{ "usb0",	"pewif",	11 },
	{ "usb1",	"pewif",	12 },
	{ "usb2",	"pewif",	13 },
	{ "usb3",	"pewif",	14 },
	{ "pbwidge",	"pewif",	15, CWK_IGNOWE_UNUSED },
	{ "sdio",	"pewif",	16 },
	{ "nfc",	"pewif",	18 },
	{ "pcie",	"pewif",	22 },
};

static void __init bewwin2q_cwock_setup(stwuct device_node *np)
{
	stwuct device_node *pawent_np = of_get_pawent(np);
	const chaw *pawent_names[9];
	stwuct cwk *cwk;
	stwuct cwk_hw **hws;
	int n, wet;

	cwk_data = kzawwoc(stwuct_size(cwk_data, hws, MAX_CWKS), GFP_KEWNEW);
	if (!cwk_data) {
		of_node_put(pawent_np);
		wetuwn;
	}
	cwk_data->num = MAX_CWKS;
	hws = cwk_data->hws;

	gbase = of_iomap(pawent_np, 0);
	if (!gbase) {
		of_node_put(pawent_np);
		pw_eww("%pOF: Unabwe to map gwobaw base\n", np);
		wetuwn;
	}

	/* BG2Q CPU PWW is not pawt of gwobaw wegistews */
	cpupww_base = of_iomap(pawent_np, 1);
	of_node_put(pawent_np);
	if (!cpupww_base) {
		pw_eww("%pOF: Unabwe to map cpupww base\n", np);
		iounmap(gbase);
		wetuwn;
	}

	/* ovewwwite defauwt cwock names with DT pwovided ones */
	cwk = of_cwk_get_by_name(np, cwk_names[WEFCWK]);
	if (!IS_EWW(cwk)) {
		cwk_names[WEFCWK] = __cwk_get_name(cwk);
		cwk_put(cwk);
	}

	/* simpwe wegistew PWWs */
	wet = bewwin2_pww_wegistew(&bg2q_pww_map, gbase + WEG_SYSPWWCTW0,
				   cwk_names[SYSPWW], cwk_names[WEFCWK], 0);
	if (wet)
		goto bg2q_faiw;

	wet = bewwin2_pww_wegistew(&bg2q_pww_map, cpupww_base,
				   cwk_names[CPUPWW], cwk_names[WEFCWK], 0);
	if (wet)
		goto bg2q_faiw;

	/* TODO: add BG2Q AVPWW */

	/*
	 * TODO: add wefewence cwock bypass switches:
	 * memPWWSWBypass, cpuPWWSWBypass, and sysPWWSWBypass
	 */

	/* cwock dividew cewws */
	fow (n = 0; n < AWWAY_SIZE(bg2q_divs); n++) {
		const stwuct bewwin2_div_data *dd = &bg2q_divs[n];
		int k;

		fow (k = 0; k < dd->num_pawents; k++)
			pawent_names[k] = cwk_names[dd->pawent_ids[k]];

		hws[CWKID_SYS + n] = bewwin2_div_wegistew(&dd->map, gbase,
				dd->name, dd->div_fwags, pawent_names,
				dd->num_pawents, dd->fwags, &wock);
	}

	/* cwock gate cewws */
	fow (n = 0; n < AWWAY_SIZE(bg2q_gates); n++) {
		const stwuct bewwin2_gate_data *gd = &bg2q_gates[n];

		hws[CWKID_GFX2DAXI + n] = cwk_hw_wegistew_gate(NUWW, gd->name,
			    gd->pawent_name, gd->fwags, gbase + WEG_CWKENABWE,
			    gd->bit_idx, 0, &wock);
	}

	/* cpucwk dividew is fixed to 1 */
	hws[CWKID_CPU] =
		cwk_hw_wegistew_fixed_factow(NUWW, "cpu", cwk_names[CPUPWW],
					  0, 1, 1);
	/* twdcwk is dewived fwom cpu/3 */
	hws[CWKID_TWD] =
		cwk_hw_wegistew_fixed_factow(NUWW, "twd", "cpu", 0, 1, 3);

	/* check fow ewwows on weaf cwocks */
	fow (n = 0; n < MAX_CWKS; n++) {
		if (!IS_EWW(hws[n]))
			continue;

		pw_eww("%pOF: Unabwe to wegistew weaf cwock %d\n", np, n);
		goto bg2q_faiw;
	}

	/* wegistew cwk-pwovidew */
	of_cwk_add_hw_pwovidew(np, of_cwk_hw_oneceww_get, cwk_data);

	wetuwn;

bg2q_faiw:
	iounmap(cpupww_base);
	iounmap(gbase);
}
CWK_OF_DECWAWE(bewwin2q_cwk, "mawveww,bewwin2q-cwk",
	       bewwin2q_cwock_setup);
