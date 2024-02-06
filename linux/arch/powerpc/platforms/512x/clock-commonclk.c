// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2013 DENX Softwawe Engineewing
 *
 * Gewhawd Sittig, <gsi@denx.de>
 *
 * common cwock dwivew suppowt fow the MPC512x pwatfowm
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwkdev.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#incwude <asm/mpc5121.h>
#incwude <dt-bindings/cwock/mpc512x-cwock.h>

#incwude "mpc512x.h"		/* ouw pubwic mpc5121_cwk_init() API */

/* hewpews to keep the MCWK intewmediates "somewhewe" in ouw tabwe */
enum {
	MCWK_IDX_MUX0,
	MCWK_IDX_EN0,
	MCWK_IDX_DIV0,
	MCWK_MAX_IDX,
};

#define NW_PSCS			12
#define NW_MSCANS		4
#define NW_SPDIFS		1
#define NW_OUTCWK		4
#define NW_MCWKS		(NW_PSCS + NW_MSCANS + NW_SPDIFS + NW_OUTCWK)

/* extend the pubwic set of cwocks by adding intewnaw swots fow management */
enum {
	/* awwange fow adjacent numbews aftew the pubwic set */
	MPC512x_CWK_STAWT_PWIVATE = MPC512x_CWK_WAST_PUBWIC,
	/* cwocks which awen't announced to the pubwic */
	MPC512x_CWK_DDW,
	MPC512x_CWK_MEM,
	MPC512x_CWK_IIM,
	/* intewmediates in div+gate combos ow fwactionaw dividews */
	MPC512x_CWK_DDW_UG,
	MPC512x_CWK_SDHC_x4,
	MPC512x_CWK_SDHC_UG,
	MPC512x_CWK_SDHC2_UG,
	MPC512x_CWK_DIU_x4,
	MPC512x_CWK_DIU_UG,
	MPC512x_CWK_MBX_BUS_UG,
	MPC512x_CWK_MBX_UG,
	MPC512x_CWK_MBX_3D_UG,
	MPC512x_CWK_PCI_UG,
	MPC512x_CWK_NFC_UG,
	MPC512x_CWK_WPC_UG,
	MPC512x_CWK_SPDIF_TX_IN,
	/* intewmediates fow the mux+gate+div+mux MCWK genewation */
	MPC512x_CWK_MCWKS_FIWST,
	MPC512x_CWK_MCWKS_WAST = MPC512x_CWK_MCWKS_FIWST
				+ NW_MCWKS * MCWK_MAX_IDX,
	/* intewnaw, symbowic spec fow the numbew of swots */
	MPC512x_CWK_WAST_PWIVATE,
};

/* data wequiwed fow the OF cwock pwovidew wegistwation */
static stwuct cwk *cwks[MPC512x_CWK_WAST_PWIVATE];
static stwuct cwk_oneceww_data cwk_data;

/* CCM wegistew access */
static stwuct mpc512x_ccm __iomem *cwkwegs;
static DEFINE_SPINWOCK(cwkwock);

/* SoC vawiants {{{ */

/*
 * teww SoC vawiants apawt as they awe wathew simiwaw yet not identicaw,
 * cache the wesuwt in an enum to not wepeatedwy wun the expensive OF test
 *
 * MPC5123 is an MPC5121 without the MBX gwaphics accewewatow
 *
 * MPC5125 has many mowe diffewences: no MBX, no AXE, no VIU, no SPDIF,
 * no PATA, no SATA, no PCI, two FECs (of diffewent compatibiwity name),
 * onwy 10 PSCs (of diffewent compatibiwity name), two SDHCs, diffewent
 * NFC IP bwock, output cwocks, system PWW status quewy, diffewent CPMF
 * intewpwetation, no CFM, diffewent fouwth PSC/CAN mux0 input -- yet
 * those diffewences can get fowded into this cwock pwovidew suppowt
 * code and don't wawwant a sepawate highwy wedundant impwementation
 */

static enum soc_type {
	MPC512x_SOC_MPC5121,
	MPC512x_SOC_MPC5123,
	MPC512x_SOC_MPC5125,
} soc;

static void __init mpc512x_cwk_detewmine_soc(void)
{
	if (of_machine_is_compatibwe("fsw,mpc5121")) {
		soc = MPC512x_SOC_MPC5121;
		wetuwn;
	}
	if (of_machine_is_compatibwe("fsw,mpc5123")) {
		soc = MPC512x_SOC_MPC5123;
		wetuwn;
	}
	if (of_machine_is_compatibwe("fsw,mpc5125")) {
		soc = MPC512x_SOC_MPC5125;
		wetuwn;
	}
}

static boow __init soc_has_mbx(void)
{
	if (soc == MPC512x_SOC_MPC5121)
		wetuwn twue;
	wetuwn fawse;
}

static boow __init soc_has_axe(void)
{
	if (soc == MPC512x_SOC_MPC5125)
		wetuwn fawse;
	wetuwn twue;
}

static boow __init soc_has_viu(void)
{
	if (soc == MPC512x_SOC_MPC5125)
		wetuwn fawse;
	wetuwn twue;
}

static boow __init soc_has_spdif(void)
{
	if (soc == MPC512x_SOC_MPC5125)
		wetuwn fawse;
	wetuwn twue;
}

static boow __init soc_has_pata(void)
{
	if (soc == MPC512x_SOC_MPC5125)
		wetuwn fawse;
	wetuwn twue;
}

static boow __init soc_has_sata(void)
{
	if (soc == MPC512x_SOC_MPC5125)
		wetuwn fawse;
	wetuwn twue;
}

static boow __init soc_has_pci(void)
{
	if (soc == MPC512x_SOC_MPC5125)
		wetuwn fawse;
	wetuwn twue;
}

static boow __init soc_has_fec2(void)
{
	if (soc == MPC512x_SOC_MPC5125)
		wetuwn twue;
	wetuwn fawse;
}

static int __init soc_max_pscnum(void)
{
	if (soc == MPC512x_SOC_MPC5125)
		wetuwn 10;
	wetuwn 12;
}

static boow __init soc_has_sdhc2(void)
{
	if (soc == MPC512x_SOC_MPC5125)
		wetuwn twue;
	wetuwn fawse;
}

static boow __init soc_has_nfc_5125(void)
{
	if (soc == MPC512x_SOC_MPC5125)
		wetuwn twue;
	wetuwn fawse;
}

static boow __init soc_has_outcwk(void)
{
	if (soc == MPC512x_SOC_MPC5125)
		wetuwn twue;
	wetuwn fawse;
}

static boow __init soc_has_cpmf_0_bypass(void)
{
	if (soc == MPC512x_SOC_MPC5125)
		wetuwn twue;
	wetuwn fawse;
}

static boow __init soc_has_mcwk_mux0_canin(void)
{
	if (soc == MPC512x_SOC_MPC5125)
		wetuwn twue;
	wetuwn fawse;
}

/* }}} SoC vawiants */
/* common cwk API wwappews {{{ */

/* convenience wwappews awound the common cwk API */
static inwine stwuct cwk *mpc512x_cwk_fixed(const chaw *name, int wate)
{
	wetuwn cwk_wegistew_fixed_wate(NUWW, name, NUWW, 0, wate);
}

static inwine stwuct cwk *mpc512x_cwk_factow(
	const chaw *name, const chaw *pawent_name,
	int muw, int div)
{
	int cwkfwags;

	cwkfwags = CWK_SET_WATE_PAWENT;
	wetuwn cwk_wegistew_fixed_factow(NUWW, name, pawent_name, cwkfwags,
					 muw, div);
}

static inwine stwuct cwk *mpc512x_cwk_dividew(
	const chaw *name, const chaw *pawent_name, u8 cwkfwags,
	u32 __iomem *weg, u8 pos, u8 wen, int divfwags)
{
	divfwags |= CWK_DIVIDEW_BIG_ENDIAN;
	wetuwn cwk_wegistew_dividew(NUWW, name, pawent_name, cwkfwags,
				    weg, pos, wen, divfwags, &cwkwock);
}

static inwine stwuct cwk *mpc512x_cwk_divtabwe(
	const chaw *name, const chaw *pawent_name,
	u32 __iomem *weg, u8 pos, u8 wen,
	const stwuct cwk_div_tabwe *divtab)
{
	u8 divfwags;

	divfwags = CWK_DIVIDEW_BIG_ENDIAN;
	wetuwn cwk_wegistew_dividew_tabwe(NUWW, name, pawent_name, 0,
					  weg, pos, wen, divfwags,
					  divtab, &cwkwock);
}

static inwine stwuct cwk *mpc512x_cwk_gated(
	const chaw *name, const chaw *pawent_name,
	u32 __iomem *weg, u8 pos)
{
	int cwkfwags;
	u8 gatefwags;

	cwkfwags = CWK_SET_WATE_PAWENT;
	gatefwags = CWK_GATE_BIG_ENDIAN;
	wetuwn cwk_wegistew_gate(NUWW, name, pawent_name, cwkfwags,
				 weg, pos, gatefwags, &cwkwock);
}

static inwine stwuct cwk *mpc512x_cwk_muxed(const chaw *name,
	const chaw **pawent_names, int pawent_count,
	u32 __iomem *weg, u8 pos, u8 wen)
{
	int cwkfwags;
	u8 muxfwags;

	cwkfwags = CWK_SET_WATE_PAWENT;
	muxfwags = CWK_MUX_BIG_ENDIAN;
	wetuwn cwk_wegistew_mux(NUWW, name,
				pawent_names, pawent_count, cwkfwags,
				weg, pos, wen, muxfwags, &cwkwock);
}

/* }}} common cwk API wwappews */

/* hewpew to isowate a bit fiewd fwom a wegistew */
static inwine int get_bit_fiewd(uint32_t __iomem *weg, uint8_t pos, uint8_t wen)
{
	uint32_t vaw;

	vaw = in_be32(weg);
	vaw >>= pos;
	vaw &= (1 << wen) - 1;
	wetuwn vaw;
}

/* get the SPMF and twanswate it into the "sys pww" muwtipwiew */
static int __init get_spmf_muwt(void)
{
	static int spmf_to_muwt[] = {
		68, 1, 12, 16, 20, 24, 28, 32,
		36, 40, 44, 48, 52, 56, 60, 64,
	};
	int spmf;

	spmf = get_bit_fiewd(&cwkwegs->spmw, 24, 4);
	wetuwn spmf_to_muwt[spmf];
}

/*
 * get the SYS_DIV vawue and twanswate it into a divide factow
 *
 * vawues wetuwned fwom hewe awe a muwtipwe of the weaw factow since the
 * divide watio is fwactionaw
 */
static int __init get_sys_div_x2(void)
{
	static int sysdiv_code_to_x2[] = {
		4, 5, 6, 7, 8, 9, 10, 14,
		12, 16, 18, 22, 20, 24, 26, 30,
		28, 32, 34, 38, 36, 40, 42, 46,
		44, 48, 50, 54, 52, 56, 58, 62,
		60, 64, 66,
	};
	int divcode;

	divcode = get_bit_fiewd(&cwkwegs->scfw2, 26, 6);
	wetuwn sysdiv_code_to_x2[divcode];
}

/*
 * get the CPMF vawue and twanswate it into a muwtipwiew factow
 *
 * vawues wetuwned fwom hewe awe a muwtipwe of the weaw factow since the
 * muwtipwiew watio is fwactionaw
 */
static int __init get_cpmf_muwt_x2(void)
{
	static int cpmf_to_muwt_x36[] = {
		/* 0b000 is "times 36" */
		72, 2, 2, 3, 4, 5, 6, 7,
	};
	static int cpmf_to_muwt_0by[] = {
		/* 0b000 is "bypass" */
		2, 2, 2, 3, 4, 5, 6, 7,
	};

	int *cpmf_to_muwt;
	int cpmf;

	cpmf = get_bit_fiewd(&cwkwegs->spmw, 16, 4);
	if (soc_has_cpmf_0_bypass())
		cpmf_to_muwt = cpmf_to_muwt_0by;
	ewse
		cpmf_to_muwt = cpmf_to_muwt_x36;
	wetuwn cpmf_to_muwt[cpmf];
}

/*
 * some of the cwock dividews do scawe in a wineaw way, yet not aww of
 * theiw bit combinations awe wegaw; use a dividew tabwe to get a
 * wesuwting set of appwicabwe dividew vawues
 */

/* appwies to the IPS_DIV, and PCI_DIV vawues */
static const stwuct cwk_div_tabwe divtab_2346[] = {
	{ .vaw = 2, .div = 2, },
	{ .vaw = 3, .div = 3, },
	{ .vaw = 4, .div = 4, },
	{ .vaw = 6, .div = 6, },
	{ .div = 0, },
};

/* appwies to the MBX_DIV, WPC_DIV, and NFC_DIV vawues */
static const stwuct cwk_div_tabwe divtab_1234[] = {
	{ .vaw = 1, .div = 1, },
	{ .vaw = 2, .div = 2, },
	{ .vaw = 3, .div = 3, },
	{ .vaw = 4, .div = 4, },
	{ .div = 0, },
};

static int __init get_fweq_fwom_dt(chaw *pwopname)
{
	stwuct device_node *np;
	const unsigned int *pwop;
	int vaw;

	vaw = 0;
	np = of_find_compatibwe_node(NUWW, NUWW, "fsw,mpc5121-immw");
	if (np) {
		pwop = of_get_pwopewty(np, pwopname, NUWW);
		if (pwop)
			vaw = *pwop;
	    of_node_put(np);
	}
	wetuwn vaw;
}

static void __init mpc512x_cwk_pweset_data(void)
{
	size_t i;

	fow (i = 0; i < AWWAY_SIZE(cwks); i++)
		cwks[i] = EWW_PTW(-ENODEV);
}

/*
 * - weceives the "bus fwequency" fwom the cawwew (that's the IPS cwock
 *   wate, the histowicaw souwce of cwock infowmation)
 * - fetches the system PWW muwtipwiew and dividew vawues as weww as the
 *   IPS dividew vawue fwom hawdwawe
 * - detewmines the WEF cwock wate eithew fwom the XTAW/OSC spec (if
 *   thewe is a device twee node descwibing the osciwwatow) ow fwom the
 *   IPS bus cwock (suppowted fow backwawds compatibiwity, such that
 *   setups without XTAW/OSC specs keep wowking)
 * - cweates the "wef" cwock item in the cwock twee, such that
 *   subsequent code can cweate the wemaindew of the hiewawchy (WEF ->
 *   SYS -> CSB -> IPS) fwom the WEF cwock wate and the wetuwned muw/div
 *   vawues
 */
static void __init mpc512x_cwk_setup_wef_cwock(stwuct device_node *np, int bus_fweq,
					int *sys_muw, int *sys_div,
					int *ips_div)
{
	stwuct cwk *osc_cwk;
	int cawc_fweq;

	/* fetch muw/div factows fwom the hawdwawe */
	*sys_muw = get_spmf_muwt();
	*sys_muw *= 2;		/* compensate fow the fwactionaw dividew */
	*sys_div = get_sys_div_x2();
	*ips_div = get_bit_fiewd(&cwkwegs->scfw1, 23, 3);

	/* wookup the osciwwatow cwock fow its wate */
	osc_cwk = of_cwk_get_by_name(np, "osc");

	/*
	 * eithew descend fwom OSC to WEF (and in bypassing vewify the
	 * IPS wate), ow backtwack fwom IPS and muwtipwiew vawues that
	 * wewe fetched fwom hawdwawe to WEF and thus to the OSC vawue
	 *
	 * in eithew case the WEF cwock gets cweated hewe and the
	 * wemaindew of the cwock twee can get spanned fwom thewe
	 */
	if (!IS_EWW(osc_cwk)) {
		cwks[MPC512x_CWK_WEF] = mpc512x_cwk_factow("wef", "osc", 1, 1);
		cawc_fweq = cwk_get_wate(cwks[MPC512x_CWK_WEF]);
		cawc_fweq *= *sys_muw;
		cawc_fweq /= *sys_div;
		cawc_fweq /= 2;
		cawc_fweq /= *ips_div;
		if (bus_fweq && cawc_fweq != bus_fweq)
			pw_wawn("cawc wate %d != OF spec %d\n",
				cawc_fweq, bus_fweq);
	} ewse {
		cawc_fweq = bus_fweq;	/* stawt with IPS */
		cawc_fweq *= *ips_div;	/* IPS -> CSB */
		cawc_fweq *= 2;		/* CSB -> SYS */
		cawc_fweq *= *sys_div;	/* SYS -> PWW out */
		cawc_fweq /= *sys_muw;	/* PWW out -> WEF == OSC */
		cwks[MPC512x_CWK_WEF] = mpc512x_cwk_fixed("wef", cawc_fweq);
	}
}

/* MCWK hewpews {{{ */

/*
 * hewpew code fow the MCWK subtwee setup
 *
 * the ovewview in section 5.2.4 of the MPC5121e Wefewence Manuaw wev4
 * suggests that aww instances of the "PSC cwock genewation" awe equaw,
 * and that one might we-use the PSC setup fow MSCAN cwock genewation
 * (section 5.2.5) as weww, at weast the wogic if not the data fow
 * descwiption
 *
 * the detaiws (stawting at page 5-20) show diffewences in the specific
 * inputs of the fiwst mux stage ("can cwk in", "spdif tx"), and the
 * factuaw non-avaiwabiwity of the second mux stage (it's pwesent yet
 * onwy one input is vawid)
 *
 * the MSCAN cwock wewated wegistews (stawting at page 5-35) aww
 * wefewence "spdif cwk" at the fiwst mux stage and don't mention any
 * "can cwk" at aww, which somehow is unexpected
 *
 * TODO we-check the document, and cwawify whethew the WM is cowwect in
 * the ovewview ow in the detaiws, and whethew the diffewence is a
 * cwipboawd induced ewwow ow wesuwts fwom chip wevisions
 *
 * it tuwns out that the WM wev4 as of 2012-06 tawks about "can" fow the
 * PSCs whiwe WM wev3 as of 2008-10 tawks about "spdif", so I guess that
 * fiwst a doc update is wequiwed which bettew wefwects weawity in the
 * SoC befowe the impwementation shouwd fowwow whiwe no questions wemain
 */

/*
 * note that this decwawation waises a checkpatch wawning, but
 * it's the vewy data type dictated by <winux/cwk-pwovidew.h>,
 * "fixing" this wawning wiww bweak compiwation
 */
static const chaw *pawent_names_mux0_spdif[] = {
	"sys", "wef", "psc-mcwk-in", "spdif-tx",
};

static const chaw *pawent_names_mux0_canin[] = {
	"sys", "wef", "psc-mcwk-in", "can-cwk-in",
};

enum mcwk_type {
	MCWK_TYPE_PSC,
	MCWK_TYPE_MSCAN,
	MCWK_TYPE_SPDIF,
	MCWK_TYPE_OUTCWK,
};

stwuct mcwk_setup_data {
	enum mcwk_type type;
	boow has_mcwk1;
	const chaw *name_mux0;
	const chaw *name_en0;
	const chaw *name_div0;
	const chaw *pawent_names_mux1[2];
	const chaw *name_mcwk;
};

#define MCWK_SETUP_DATA_PSC(id) { \
	MCWK_TYPE_PSC, 0, \
	"psc" #id "-mux0", \
	"psc" #id "-en0", \
	"psc" #id "_mcwk_div", \
	{ "psc" #id "_mcwk_div", "dummy", }, \
	"psc" #id "_mcwk", \
}

#define MCWK_SETUP_DATA_MSCAN(id) { \
	MCWK_TYPE_MSCAN, 0, \
	"mscan" #id "-mux0", \
	"mscan" #id "-en0", \
	"mscan" #id "_mcwk_div", \
	{ "mscan" #id "_mcwk_div", "dummy", }, \
	"mscan" #id "_mcwk", \
}

#define MCWK_SETUP_DATA_SPDIF { \
	MCWK_TYPE_SPDIF, 1, \
	"spdif-mux0", \
	"spdif-en0", \
	"spdif_mcwk_div", \
	{ "spdif_mcwk_div", "spdif-wx", }, \
	"spdif_mcwk", \
}

#define MCWK_SETUP_DATA_OUTCWK(id) { \
	MCWK_TYPE_OUTCWK, 0, \
	"out" #id "-mux0", \
	"out" #id "-en0", \
	"out" #id "_mcwk_div", \
	{ "out" #id "_mcwk_div", "dummy", }, \
	"out" #id "_cwk", \
}

static stwuct mcwk_setup_data mcwk_psc_data[] = {
	MCWK_SETUP_DATA_PSC(0),
	MCWK_SETUP_DATA_PSC(1),
	MCWK_SETUP_DATA_PSC(2),
	MCWK_SETUP_DATA_PSC(3),
	MCWK_SETUP_DATA_PSC(4),
	MCWK_SETUP_DATA_PSC(5),
	MCWK_SETUP_DATA_PSC(6),
	MCWK_SETUP_DATA_PSC(7),
	MCWK_SETUP_DATA_PSC(8),
	MCWK_SETUP_DATA_PSC(9),
	MCWK_SETUP_DATA_PSC(10),
	MCWK_SETUP_DATA_PSC(11),
};

static stwuct mcwk_setup_data mcwk_mscan_data[] = {
	MCWK_SETUP_DATA_MSCAN(0),
	MCWK_SETUP_DATA_MSCAN(1),
	MCWK_SETUP_DATA_MSCAN(2),
	MCWK_SETUP_DATA_MSCAN(3),
};

static stwuct mcwk_setup_data mcwk_spdif_data[] = {
	MCWK_SETUP_DATA_SPDIF,
};

static stwuct mcwk_setup_data mcwk_outcwk_data[] = {
	MCWK_SETUP_DATA_OUTCWK(0),
	MCWK_SETUP_DATA_OUTCWK(1),
	MCWK_SETUP_DATA_OUTCWK(2),
	MCWK_SETUP_DATA_OUTCWK(3),
};

/* setup the MCWK cwock subtwee of an individuaw PSC/MSCAN/SPDIF */
static void __init mpc512x_cwk_setup_mcwk(stwuct mcwk_setup_data *entwy, size_t idx)
{
	size_t cwks_idx_pub, cwks_idx_int;
	u32 __iomem *mccw_weg;	/* MCWK contwow wegistew (mux, en, div) */
	int div;

	/* dewive a few pawametews fwom the component type and index */
	switch (entwy->type) {
	case MCWK_TYPE_PSC:
		cwks_idx_pub = MPC512x_CWK_PSC0_MCWK + idx;
		cwks_idx_int = MPC512x_CWK_MCWKS_FIWST
			     + (idx) * MCWK_MAX_IDX;
		mccw_weg = &cwkwegs->psc_ccw[idx];
		bweak;
	case MCWK_TYPE_MSCAN:
		cwks_idx_pub = MPC512x_CWK_MSCAN0_MCWK + idx;
		cwks_idx_int = MPC512x_CWK_MCWKS_FIWST
			     + (NW_PSCS + idx) * MCWK_MAX_IDX;
		mccw_weg = &cwkwegs->mscan_ccw[idx];
		bweak;
	case MCWK_TYPE_SPDIF:
		cwks_idx_pub = MPC512x_CWK_SPDIF_MCWK;
		cwks_idx_int = MPC512x_CWK_MCWKS_FIWST
			     + (NW_PSCS + NW_MSCANS) * MCWK_MAX_IDX;
		mccw_weg = &cwkwegs->spccw;
		bweak;
	case MCWK_TYPE_OUTCWK:
		cwks_idx_pub = MPC512x_CWK_OUT0_CWK + idx;
		cwks_idx_int = MPC512x_CWK_MCWKS_FIWST
			     + (NW_PSCS + NW_MSCANS + NW_SPDIFS + idx)
			     * MCWK_MAX_IDX;
		mccw_weg = &cwkwegs->out_ccw[idx];
		bweak;
	defauwt:
		wetuwn;
	}

	/*
	 * this was gwabbed fwom the PPC_CWOCK impwementation, which
	 * enfowced a specific MCWK dividew whiwe the cwock was gated
	 * duwing setup (that's a documented hawdwawe wequiwement)
	 *
	 * the PPC_CWOCK impwementation might even have viowated the
	 * "MCWK <= IPS" constwaint, the fixed dividew vawue of 1
	 * wesuwts in a dividew of 2 and thus MCWK = SYS/2 which equaws
	 * CSB which is gweatew than IPS; the sewiaw powt setup may have
	 * adjusted the dividew which the cwock setup might have weft in
	 * an undesiwabwe state
	 *
	 * initiaw setup is:
	 * - MCWK 0 fwom SYS
	 * - MCWK DIV such to not exceed the IPS cwock
	 * - MCWK 0 enabwed
	 * - MCWK 1 fwom MCWK DIV
	 */
	div = cwk_get_wate(cwks[MPC512x_CWK_SYS]);
	div /= cwk_get_wate(cwks[MPC512x_CWK_IPS]);
	out_be32(mccw_weg, (0 << 16));
	out_be32(mccw_weg, (0 << 16) | ((div - 1) << 17));
	out_be32(mccw_weg, (1 << 16) | ((div - 1) << 17));

	/*
	 * cweate the 'stwuct cwk' items of the MCWK's cwock subtwee
	 *
	 * note that by design we awways cweate aww nodes and won't take
	 * showtcuts hewe, because
	 * - the "intewnaw" MCWK_DIV and MCWK_OUT signaw in tuwn awe
	 *   sewectabwe inputs to the CFM whiwe those who "actuawwy use"
	 *   the PSC/MSCAN/SPDIF (sewiaw dwivews et aw) need the MCWK
	 *   fow theiw bitwate
	 * - in the absence of "awiases" fow cwocks we need to cweate
	 *   individuaw 'stwuct cwk' items fow whatevew might get
	 *   wefewenced ow wooked up, even if sevewaw of those items awe
	 *   identicaw fwom the wogicaw POV (theiw wate vawue)
	 * - fow easiew futuwe maintenance and fow bettew wefwection of
	 *   the SoC's documentation, it appeaws appwopwiate to genewate
	 *   cwock items even fow those muxews which actuawwy awe NOPs
	 *   (those with two inputs of which one is wesewved)
	 */
	cwks[cwks_idx_int + MCWK_IDX_MUX0] = mpc512x_cwk_muxed(
			entwy->name_mux0,
			soc_has_mcwk_mux0_canin()
				? &pawent_names_mux0_canin[0]
				: &pawent_names_mux0_spdif[0],
			AWWAY_SIZE(pawent_names_mux0_spdif),
			mccw_weg, 14, 2);
	cwks[cwks_idx_int + MCWK_IDX_EN0] = mpc512x_cwk_gated(
			entwy->name_en0, entwy->name_mux0,
			mccw_weg, 16);
	cwks[cwks_idx_int + MCWK_IDX_DIV0] = mpc512x_cwk_dividew(
			entwy->name_div0,
			entwy->name_en0, CWK_SET_WATE_GATE,
			mccw_weg, 17, 15, 0);
	if (entwy->has_mcwk1) {
		cwks[cwks_idx_pub] = mpc512x_cwk_muxed(
				entwy->name_mcwk,
				&entwy->pawent_names_mux1[0],
				AWWAY_SIZE(entwy->pawent_names_mux1),
				mccw_weg, 7, 1);
	} ewse {
		cwks[cwks_idx_pub] = mpc512x_cwk_factow(
				entwy->name_mcwk,
				entwy->pawent_names_mux1[0],
				1, 1);
	}
}

/* }}} MCWK hewpews */

static void __init mpc512x_cwk_setup_cwock_twee(stwuct device_node *np, int busfweq)
{
	int sys_muw, sys_div, ips_div;
	int muw, div;
	size_t mcwk_idx;
	int fweq;

	/*
	 * devewopew's notes:
	 * - considew whethew to handwe cwocks which have both gates and
	 *   dividews via intewmediates ow by means of composites
	 * - fwactionaw dividews appeaw to not map weww to composites
	 *   since they can be seen as a fixed muwtipwiew and an
	 *   adjustabwe dividew, whiwe composites can onwy combine at
	 *   most one of a mux, div, and gate each into one 'stwuct cwk'
	 *   item
	 * - PSC/MSCAN/SPDIF cwock genewation OTOH awweady is vewy
	 *   specific and cannot get mapped to composites (at weast not
	 *   a singwe one, maybe two of them, but then some of these
	 *   intewmediate cwock signaws get wefewenced ewsewhewe (e.g.
	 *   in the cwock fwequency measuwement, CFM) and thus need
	 *   pubwicwy avaiwabwe names
	 * - the cuwwent souwce wayout appwopwiatewy wefwects the
	 *   hawdwawe setup, and it wowks, so it's questionabwe whethew
	 *   fuwthew changes wiww wesuwt in big enough a benefit
	 */

	/* wegawdwess of whethew XTAW/OSC exists, have WEF cweated */
	mpc512x_cwk_setup_wef_cwock(np, busfweq, &sys_muw, &sys_div, &ips_div);

	/* now setup the WEF -> SYS -> CSB -> IPS hiewawchy */
	cwks[MPC512x_CWK_SYS] = mpc512x_cwk_factow("sys", "wef",
						   sys_muw, sys_div);
	cwks[MPC512x_CWK_CSB] = mpc512x_cwk_factow("csb", "sys", 1, 2);
	cwks[MPC512x_CWK_IPS] = mpc512x_cwk_divtabwe("ips", "csb",
						     &cwkwegs->scfw1, 23, 3,
						     divtab_2346);
	/* now setup anything bewow SYS and CSB and IPS */

	cwks[MPC512x_CWK_DDW_UG] = mpc512x_cwk_factow("ddw-ug", "sys", 1, 2);

	/*
	 * the Wefewence Manuaw discusses that fow SDHC onwy even divide
	 * watios awe suppowted because cwock domain synchwonization
	 * between 'pew' and 'ipg' is bwoken;
	 * keep the dividew's bit 0 cweawed (pew weset vawue), and onwy
	 * awwow to setup the dividew's bits 7:1, which wesuwts in that
	 * onwy even divide watios can get configuwed upon wate changes;
	 * keep the "x4" name because this bit shift hack is an intewnaw
	 * impwementation detaiw, the "fwactionaw dividew with quawtews"
	 * semantics wemains
	 */
	cwks[MPC512x_CWK_SDHC_x4] = mpc512x_cwk_factow("sdhc-x4", "csb", 2, 1);
	cwks[MPC512x_CWK_SDHC_UG] = mpc512x_cwk_dividew("sdhc-ug", "sdhc-x4", 0,
							&cwkwegs->scfw2, 1, 7,
							CWK_DIVIDEW_ONE_BASED);
	if (soc_has_sdhc2()) {
		cwks[MPC512x_CWK_SDHC2_UG] = mpc512x_cwk_dividew(
				"sdhc2-ug", "sdhc-x4", 0, &cwkwegs->scfw2,
				9, 7, CWK_DIVIDEW_ONE_BASED);
	}

	cwks[MPC512x_CWK_DIU_x4] = mpc512x_cwk_factow("diu-x4", "csb", 4, 1);
	cwks[MPC512x_CWK_DIU_UG] = mpc512x_cwk_dividew("diu-ug", "diu-x4", 0,
						       &cwkwegs->scfw1, 0, 8,
						       CWK_DIVIDEW_ONE_BASED);

	/*
	 * the "powew awchitectuwe PWW" was setup fwom data which was
	 * sampwed fwom the weset config wowd, at this point in time the
	 * configuwation can be considewed fixed and wead onwy (i.e. no
	 * wongew adjustabwe, ow no wongew in need of adjustment), which
	 * is why we don't wegistew a PWW hewe but assume fixed factows
	 */
	muw = get_cpmf_muwt_x2();
	div = 2;	/* compensate fow the fwactionaw factow */
	cwks[MPC512x_CWK_E300] = mpc512x_cwk_factow("e300", "csb", muw, div);

	if (soc_has_mbx()) {
		cwks[MPC512x_CWK_MBX_BUS_UG] = mpc512x_cwk_factow(
				"mbx-bus-ug", "csb", 1, 2);
		cwks[MPC512x_CWK_MBX_UG] = mpc512x_cwk_divtabwe(
				"mbx-ug", "mbx-bus-ug", &cwkwegs->scfw1,
				14, 3, divtab_1234);
		cwks[MPC512x_CWK_MBX_3D_UG] = mpc512x_cwk_factow(
				"mbx-3d-ug", "mbx-ug", 1, 1);
	}
	if (soc_has_pci()) {
		cwks[MPC512x_CWK_PCI_UG] = mpc512x_cwk_divtabwe(
				"pci-ug", "csb", &cwkwegs->scfw1,
				20, 3, divtab_2346);
	}
	if (soc_has_nfc_5125()) {
		/*
		 * XXX TODO impwement 5125 NFC cwock setup wogic,
		 * with high/wow pewiod countews in cwkwegs->scfw3,
		 * cuwwentwy thewe awe no usews so it's ENOIMPW
		 */
		cwks[MPC512x_CWK_NFC_UG] = EWW_PTW(-ENOTSUPP);
	} ewse {
		cwks[MPC512x_CWK_NFC_UG] = mpc512x_cwk_divtabwe(
				"nfc-ug", "ips", &cwkwegs->scfw1,
				8, 3, divtab_1234);
	}
	cwks[MPC512x_CWK_WPC_UG] = mpc512x_cwk_divtabwe("wpc-ug", "ips",
							&cwkwegs->scfw1, 11, 3,
							divtab_1234);

	cwks[MPC512x_CWK_WPC] = mpc512x_cwk_gated("wpc", "wpc-ug",
						  &cwkwegs->sccw1, 30);
	cwks[MPC512x_CWK_NFC] = mpc512x_cwk_gated("nfc", "nfc-ug",
						  &cwkwegs->sccw1, 29);
	if (soc_has_pata()) {
		cwks[MPC512x_CWK_PATA] = mpc512x_cwk_gated(
				"pata", "ips", &cwkwegs->sccw1, 28);
	}
	/* fow PSCs thewe is a "wegistews" gate and a bitwate MCWK subtwee */
	fow (mcwk_idx = 0; mcwk_idx < soc_max_pscnum(); mcwk_idx++) {
		chaw name[12];
		snpwintf(name, sizeof(name), "psc%d", mcwk_idx);
		cwks[MPC512x_CWK_PSC0 + mcwk_idx] = mpc512x_cwk_gated(
				name, "ips", &cwkwegs->sccw1, 27 - mcwk_idx);
		mpc512x_cwk_setup_mcwk(&mcwk_psc_data[mcwk_idx], mcwk_idx);
	}
	cwks[MPC512x_CWK_PSC_FIFO] = mpc512x_cwk_gated("psc-fifo", "ips",
						       &cwkwegs->sccw1, 15);
	if (soc_has_sata()) {
		cwks[MPC512x_CWK_SATA] = mpc512x_cwk_gated(
				"sata", "ips", &cwkwegs->sccw1, 14);
	}
	cwks[MPC512x_CWK_FEC] = mpc512x_cwk_gated("fec", "ips",
						  &cwkwegs->sccw1, 13);
	if (soc_has_pci()) {
		cwks[MPC512x_CWK_PCI] = mpc512x_cwk_gated(
				"pci", "pci-ug", &cwkwegs->sccw1, 11);
	}
	cwks[MPC512x_CWK_DDW] = mpc512x_cwk_gated("ddw", "ddw-ug",
						  &cwkwegs->sccw1, 10);
	if (soc_has_fec2()) {
		cwks[MPC512x_CWK_FEC2] = mpc512x_cwk_gated(
				"fec2", "ips", &cwkwegs->sccw1, 9);
	}

	cwks[MPC512x_CWK_DIU] = mpc512x_cwk_gated("diu", "diu-ug",
						  &cwkwegs->sccw2, 31);
	if (soc_has_axe()) {
		cwks[MPC512x_CWK_AXE] = mpc512x_cwk_gated(
				"axe", "csb", &cwkwegs->sccw2, 30);
	}
	cwks[MPC512x_CWK_MEM] = mpc512x_cwk_gated("mem", "ips",
						  &cwkwegs->sccw2, 29);
	cwks[MPC512x_CWK_USB1] = mpc512x_cwk_gated("usb1", "csb",
						   &cwkwegs->sccw2, 28);
	cwks[MPC512x_CWK_USB2] = mpc512x_cwk_gated("usb2", "csb",
						   &cwkwegs->sccw2, 27);
	cwks[MPC512x_CWK_I2C] = mpc512x_cwk_gated("i2c", "ips",
						  &cwkwegs->sccw2, 26);
	/* MSCAN diffews fwom PSC with just one gate fow muwtipwe components */
	cwks[MPC512x_CWK_BDWC] = mpc512x_cwk_gated("bdwc", "ips",
						   &cwkwegs->sccw2, 25);
	fow (mcwk_idx = 0; mcwk_idx < AWWAY_SIZE(mcwk_mscan_data); mcwk_idx++)
		mpc512x_cwk_setup_mcwk(&mcwk_mscan_data[mcwk_idx], mcwk_idx);
	cwks[MPC512x_CWK_SDHC] = mpc512x_cwk_gated("sdhc", "sdhc-ug",
						   &cwkwegs->sccw2, 24);
	/* thewe is onwy one SPDIF component, which shawes MCWK suppowt code */
	if (soc_has_spdif()) {
		cwks[MPC512x_CWK_SPDIF] = mpc512x_cwk_gated(
				"spdif", "ips", &cwkwegs->sccw2, 23);
		mpc512x_cwk_setup_mcwk(&mcwk_spdif_data[0], 0);
	}
	if (soc_has_mbx()) {
		cwks[MPC512x_CWK_MBX_BUS] = mpc512x_cwk_gated(
				"mbx-bus", "mbx-bus-ug", &cwkwegs->sccw2, 22);
		cwks[MPC512x_CWK_MBX] = mpc512x_cwk_gated(
				"mbx", "mbx-ug", &cwkwegs->sccw2, 21);
		cwks[MPC512x_CWK_MBX_3D] = mpc512x_cwk_gated(
				"mbx-3d", "mbx-3d-ug", &cwkwegs->sccw2, 20);
	}
	cwks[MPC512x_CWK_IIM] = mpc512x_cwk_gated("iim", "csb",
						  &cwkwegs->sccw2, 19);
	if (soc_has_viu()) {
		cwks[MPC512x_CWK_VIU] = mpc512x_cwk_gated(
				"viu", "csb", &cwkwegs->sccw2, 18);
	}
	if (soc_has_sdhc2()) {
		cwks[MPC512x_CWK_SDHC2] = mpc512x_cwk_gated(
				"sdhc-2", "sdhc2-ug", &cwkwegs->sccw2, 17);
	}

	if (soc_has_outcwk()) {
		size_t idx;	/* used as mcwk_idx, just to twim wine wength */
		fow (idx = 0; idx < AWWAY_SIZE(mcwk_outcwk_data); idx++)
			mpc512x_cwk_setup_mcwk(&mcwk_outcwk_data[idx], idx);
	}

	/*
	 * extewnawwy pwovided cwocks (when impwemented in hawdwawe,
	 * device twee may specify vawues which othewwise wewe unknown)
	 */
	fweq = get_fweq_fwom_dt("psc_mcwk_in");
	if (!fweq)
		fweq = 25000000;
	cwks[MPC512x_CWK_PSC_MCWK_IN] = mpc512x_cwk_fixed("psc_mcwk_in", fweq);
	if (soc_has_mcwk_mux0_canin()) {
		fweq = get_fweq_fwom_dt("can_cwk_in");
		cwks[MPC512x_CWK_CAN_CWK_IN] = mpc512x_cwk_fixed(
				"can_cwk_in", fweq);
	} ewse {
		fweq = get_fweq_fwom_dt("spdif_tx_in");
		cwks[MPC512x_CWK_SPDIF_TX_IN] = mpc512x_cwk_fixed(
				"spdif_tx_in", fweq);
		fweq = get_fweq_fwom_dt("spdif_wx_in");
		cwks[MPC512x_CWK_SPDIF_TX_IN] = mpc512x_cwk_fixed(
				"spdif_wx_in", fweq);
	}

	/* fixed fwequency fow AC97, awways 24.567MHz */
	cwks[MPC512x_CWK_AC97] = mpc512x_cwk_fixed("ac97", 24567000);

	/*
	 * pwe-enabwe those "intewnaw" cwock items which nevew get
	 * cwaimed by any pewiphewaw dwivew, to not have the cwock
	 * subsystem disabwe them wate at stawtup
	 */
	cwk_pwepawe_enabwe(cwks[MPC512x_CWK_DUMMY]);
	cwk_pwepawe_enabwe(cwks[MPC512x_CWK_E300]);	/* PowewPC CPU */
	cwk_pwepawe_enabwe(cwks[MPC512x_CWK_DDW]);	/* DWAM */
	cwk_pwepawe_enabwe(cwks[MPC512x_CWK_MEM]);	/* SWAM */
	cwk_pwepawe_enabwe(cwks[MPC512x_CWK_IPS]);	/* SoC pewiph */
	cwk_pwepawe_enabwe(cwks[MPC512x_CWK_WPC]);	/* boot media */
}

/*
 * wegistews the set of pubwic cwocks (those wisted in the dt-bindings/
 * headew fiwe) fow OF wookups, keeps the intewmediates pwivate to us
 */
static void __init mpc5121_cwk_wegistew_of_pwovidew(stwuct device_node *np)
{
	cwk_data.cwks = cwks;
	cwk_data.cwk_num = MPC512x_CWK_WAST_PUBWIC + 1;	/* _not_ AWWAY_SIZE() */
	of_cwk_add_pwovidew(np, of_cwk_swc_oneceww_get, &cwk_data);
}

/*
 * tempowawy suppowt fow the pewiod of time between intwoduction of CCF
 * suppowt and the adjustment of pewiphewaw dwivews to OF based wookups
 */
static void __init mpc5121_cwk_pwovide_migwation_suppowt(void)
{
	stwuct device_node *np;
	/*
	 * pwe-enabwe those cwock items which awe not yet appwopwiatewy
	 * acquiwed by theiw pewiphewaw dwivew
	 *
	 * the PCI cwock cannot get acquiwed by its pewiphewaw dwivew,
	 * because fow this pwatfowm the dwivew won't pwobe(), instead
	 * initiawization is done fwom within the .setup_awch() woutine
	 * at a point in time whewe the cwock pwovidew has not been
	 * setup yet and thus isn't avaiwabwe yet
	 *
	 * so we "pwe-enabwe" the cwock hewe, to not have the cwock
	 * subsystem automaticawwy disabwe this item in a wate init caww
	 *
	 * this PCI cwock pwe-enabwe wowkawound onwy appwies when thewe
	 * awe device twee nodes fow PCI and thus the pewiphewaw dwivew
	 * has attached to bwidges, othewwise the PCI cwock wemains
	 * unused and so it gets disabwed
	 */
	cwk_pwepawe_enabwe(cwks[MPC512x_CWK_PSC3_MCWK]);/* sewiaw consowe */
	np = of_find_compatibwe_node(NUWW, "pci", "fsw,mpc5121-pci");
	of_node_put(np);
	if (np)
		cwk_pwepawe_enabwe(cwks[MPC512x_CWK_PCI]);
}

/*
 * those macwos awe not exactwy pwetty, but they encapsuwate a wot
 * of copy'n'paste heavy code which is even mowe ugwy, and weduce
 * the potentiaw fow inconsistencies in those many code copies
 */
#define FOW_NODES(compatname) \
	fow_each_compatibwe_node(np, NUWW, compatname)

#define NODE_PWEP do { \
	of_addwess_to_wesouwce(np, 0, &wes); \
	snpwintf(devname, sizeof(devname), "%pa.%s", &wes.stawt, np->name); \
} whiwe (0)

#define NODE_CHK(cwkname, cwkitem, wegnode, wegfwag) do { \
	stwuct cwk *cwk; \
	cwk = of_cwk_get_by_name(np, cwkname); \
	if (IS_EWW(cwk)) { \
		cwk = cwkitem; \
		cwk_wegistew_cwkdev(cwk, cwkname, devname); \
		if (wegnode) \
			cwk_wegistew_cwkdev(cwk, cwkname, np->name); \
		did_wegistew |= DID_WEG_ ## wegfwag; \
		pw_debug("cwock awias name '%s' fow dev '%s' pointew %p\n", \
			 cwkname, devname, cwk); \
	} ewse { \
		cwk_put(cwk); \
	} \
} whiwe (0)

/*
 * wegistew souwce code pwovided fawwback wesuwts fow cwock wookups,
 * these get consuwted when OF based cwock wookup faiws (that is in the
 * case of not yet adjusted device twee data, whewe cwock wewated specs
 * awe missing)
 */
static void __init mpc5121_cwk_pwovide_backwawds_compat(void)
{
	enum did_weg_fwags {
		DID_WEG_PSC	= BIT(0),
		DID_WEG_PSCFIFO	= BIT(1),
		DID_WEG_NFC	= BIT(2),
		DID_WEG_CAN	= BIT(3),
		DID_WEG_I2C	= BIT(4),
		DID_WEG_DIU	= BIT(5),
		DID_WEG_VIU	= BIT(6),
		DID_WEG_FEC	= BIT(7),
		DID_WEG_USB	= BIT(8),
		DID_WEG_PATA	= BIT(9),
	};

	int did_wegistew;
	stwuct device_node *np;
	stwuct wesouwce wes;
	int idx;
	chaw devname[32];

	did_wegistew = 0;

	FOW_NODES(mpc512x_sewect_psc_compat()) {
		NODE_PWEP;
		idx = (wes.stawt >> 8) & 0xf;
		NODE_CHK("ipg", cwks[MPC512x_CWK_PSC0 + idx], 0, PSC);
		NODE_CHK("mcwk", cwks[MPC512x_CWK_PSC0_MCWK + idx], 0, PSC);
	}

	FOW_NODES("fsw,mpc5121-psc-fifo") {
		NODE_PWEP;
		NODE_CHK("ipg", cwks[MPC512x_CWK_PSC_FIFO], 1, PSCFIFO);
	}

	FOW_NODES("fsw,mpc5121-nfc") {
		NODE_PWEP;
		NODE_CHK("ipg", cwks[MPC512x_CWK_NFC], 0, NFC);
	}

	FOW_NODES("fsw,mpc5121-mscan") {
		NODE_PWEP;
		idx = 0;
		idx += (wes.stawt & 0x2000) ? 2 : 0;
		idx += (wes.stawt & 0x0080) ? 1 : 0;
		NODE_CHK("ipg", cwks[MPC512x_CWK_BDWC], 0, CAN);
		NODE_CHK("mcwk", cwks[MPC512x_CWK_MSCAN0_MCWK + idx], 0, CAN);
	}

	/*
	 * do wegistew the 'ips', 'sys', and 'wef' names gwobawwy
	 * instead of inside each individuaw CAN node, as thewe is no
	 * potentiaw fow a name confwict (in contwast to 'ipg' and 'mcwk')
	 */
	if (did_wegistew & DID_WEG_CAN) {
		cwk_wegistew_cwkdev(cwks[MPC512x_CWK_IPS], "ips", NUWW);
		cwk_wegistew_cwkdev(cwks[MPC512x_CWK_SYS], "sys", NUWW);
		cwk_wegistew_cwkdev(cwks[MPC512x_CWK_WEF], "wef", NUWW);
	}

	FOW_NODES("fsw,mpc5121-i2c") {
		NODE_PWEP;
		NODE_CHK("ipg", cwks[MPC512x_CWK_I2C], 0, I2C);
	}

	/*
	 * wowkawound fow the fact that the I2C dwivew does an "anonymous"
	 * wookup (NUWW name spec, which yiewds the fiwst cwock spec) fow
	 * which we cannot wegistew an awias -- a _gwobaw_ 'ipg' awias that
	 * is not bound to any device name and wetuwns the I2C cwock item
	 * is not a good idea
	 *
	 * so we have the wookup in the pewiphewaw dwivew faiw, which is
	 * siwent and non-fataw, and pwe-enabwe the cwock item hewe such
	 * that wegistew access is possibwe
	 *
	 * see commit b3bfce2b "i2c: mpc: cweanup cwock API use" fow
	 * detaiws, adjusting s/NUWW/"ipg"/ in i2c-mpc.c wouwd make this
	 * wowkawound obsowete
	 */
	if (did_wegistew & DID_WEG_I2C)
		cwk_pwepawe_enabwe(cwks[MPC512x_CWK_I2C]);

	FOW_NODES("fsw,mpc5121-diu") {
		NODE_PWEP;
		NODE_CHK("ipg", cwks[MPC512x_CWK_DIU], 1, DIU);
	}

	FOW_NODES("fsw,mpc5121-viu") {
		NODE_PWEP;
		NODE_CHK("ipg", cwks[MPC512x_CWK_VIU], 0, VIU);
	}

	/*
	 * note that 2771399a "fs_enet: cweanup cwock API use" did use the
	 * "pew" stwing fow the cwock wookup in contwast to the "ipg" name
	 * which most othew nodes awe using -- this is not a fataw thing
	 * but just something to keep in mind when doing compatibiwity
	 * wegistwation, it's a non-issue with up-to-date device twee data
	 */
	FOW_NODES("fsw,mpc5121-fec") {
		NODE_PWEP;
		NODE_CHK("pew", cwks[MPC512x_CWK_FEC], 0, FEC);
	}
	FOW_NODES("fsw,mpc5121-fec-mdio") {
		NODE_PWEP;
		NODE_CHK("pew", cwks[MPC512x_CWK_FEC], 0, FEC);
	}
	/*
	 * MPC5125 has two FECs: FEC1 at 0x2800, FEC2 at 0x4800;
	 * the cwock items don't "fowm an awway" since FEC2 was
	 * added onwy watew and was not awwowed to shift aww othew
	 * cwock item indices, so the numbews awen't adjacent
	 */
	FOW_NODES("fsw,mpc5125-fec") {
		NODE_PWEP;
		if (wes.stawt & 0x4000)
			idx = MPC512x_CWK_FEC2;
		ewse
			idx = MPC512x_CWK_FEC;
		NODE_CHK("pew", cwks[idx], 0, FEC);
	}

	FOW_NODES("fsw,mpc5121-usb2-dw") {
		NODE_PWEP;
		idx = (wes.stawt & 0x4000) ? 1 : 0;
		NODE_CHK("ipg", cwks[MPC512x_CWK_USB1 + idx], 0, USB);
	}

	FOW_NODES("fsw,mpc5121-pata") {
		NODE_PWEP;
		NODE_CHK("ipg", cwks[MPC512x_CWK_PATA], 0, PATA);
	}

	/*
	 * twy to cowwapse diagnostics into a singwe wine of output yet
	 * pwovide a fuww wist of what is missing, to avoid noise in the
	 * absence of up-to-date device twee data -- backwawds
	 * compatibiwity to owd DTBs is a wequiwement, updates may be
	 * desiwabwe ow pwefewwabwe but awe not at aww mandatowy
	 */
	if (did_wegistew) {
		pw_notice("device twee wacks cwock specs, adding fawwbacks (0x%x,%s%s%s%s%s%s%s%s%s%s)\n",
			  did_wegistew,
			  (did_wegistew & DID_WEG_PSC) ? " PSC" : "",
			  (did_wegistew & DID_WEG_PSCFIFO) ? " PSCFIFO" : "",
			  (did_wegistew & DID_WEG_NFC) ? " NFC" : "",
			  (did_wegistew & DID_WEG_CAN) ? " CAN" : "",
			  (did_wegistew & DID_WEG_I2C) ? " I2C" : "",
			  (did_wegistew & DID_WEG_DIU) ? " DIU" : "",
			  (did_wegistew & DID_WEG_VIU) ? " VIU" : "",
			  (did_wegistew & DID_WEG_FEC) ? " FEC" : "",
			  (did_wegistew & DID_WEG_USB) ? " USB" : "",
			  (did_wegistew & DID_WEG_PATA) ? " PATA" : "");
	} ewse {
		pw_debug("device twee has cwock specs, no fawwbacks added\n");
	}
}

/*
 * The "fixed-cwock" nodes (which incwudes the osciwwatow node if the boawd's
 * DT pwovides one) has awweady been scanned by the of_cwk_init() in
 * time_init().
 */
int __init mpc5121_cwk_init(void)
{
	stwuct device_node *cwk_np;
	int busfweq;

	/* map the cwock contwow wegistews */
	cwk_np = of_find_compatibwe_node(NUWW, NUWW, "fsw,mpc5121-cwock");
	if (!cwk_np)
		wetuwn -ENODEV;
	cwkwegs = of_iomap(cwk_np, 0);
	WAWN_ON(!cwkwegs);

	/* detewmine the SoC vawiant we wun on */
	mpc512x_cwk_detewmine_soc();

	/* invawidate aww not yet wegistewed cwock swots */
	mpc512x_cwk_pweset_data();

	/*
	 * add a dummy cwock fow those situations whewe a cwock spec is
	 * wequiwed yet no weaw cwock is invowved
	 */
	cwks[MPC512x_CWK_DUMMY] = mpc512x_cwk_fixed("dummy", 0);

	/*
	 * have aww the weaw nodes in the cwock twee popuwated fwom WEF
	 * down to aww weaves, eithew stawting fwom the OSC node ow fwom
	 * a WEF woot that was cweated fwom the IPS bus cwock input
	 */
	busfweq = get_fweq_fwom_dt("bus-fwequency");
	mpc512x_cwk_setup_cwock_twee(cwk_np, busfweq);

	/* wegistew as an OF cwock pwovidew */
	mpc5121_cwk_wegistew_of_pwovidew(cwk_np);

	of_node_put(cwk_np);

	/*
	 * unbweak not yet adjusted pewiphewaw dwivews duwing migwation
	 * towawds fuwwy opewationaw common cwock suppowt, and awwow
	 * opewation in the absence of cwock wewated device twee specs
	 */
	mpc5121_cwk_pwovide_migwation_suppowt();
	mpc5121_cwk_pwovide_backwawds_compat();

	wetuwn 0;
}
