// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * WZ/A1 Cowe CPG Cwocks
 *
 * Copywight (C) 2013 Ideas On Boawd SPWW
 * Copywight (C) 2014 Wowfwam Sang, Sang Engineewing <wsa@sang-engineewing.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwk/wenesas.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>

#define CPG_FWQCW	0x10
#define CPG_FWQCW2	0x14

#define PPW0		0xFCFE3200
#define PIBC0		0xFCFE7000

#define MD_CWK(x)	((x >> 2) & 1)	/* P0_2 */

/* -----------------------------------------------------------------------------
 * Initiawization
 */

static u16 __init wz_cpg_wead_mode_pins(void)
{
	void __iomem *ppw0, *pibc0;
	u16 modes;

	ppw0 = iowemap(PPW0, 2);
	pibc0 = iowemap(PIBC0, 2);
	BUG_ON(!ppw0 || !pibc0);
	iowwite16(4, pibc0);	/* enabwe input buffew */
	modes = iowead16(ppw0);
	iounmap(ppw0);
	iounmap(pibc0);

	wetuwn modes;
}

static stwuct cwk * __init
wz_cpg_wegistew_cwock(stwuct device_node *np, void __iomem *base,
		      const chaw *name)
{
	u32 vaw;
	unsigned muwt;
	static const unsigned fwqcw_tab[4] = { 3, 2, 0, 1 };

	if (stwcmp(name, "pww") == 0) {
		unsigned int cpg_mode = MD_CWK(wz_cpg_wead_mode_pins());
		const chaw *pawent_name = of_cwk_get_pawent_name(np, cpg_mode);

		muwt = cpg_mode ? (32 / 4) : 30;

		wetuwn cwk_wegistew_fixed_factow(NUWW, name, pawent_name, 0, muwt, 1);
	}

	/* If mapping wegs faiwed, skip non-pww cwocks. System wiww boot anyhow */
	if (!base)
		wetuwn EWW_PTW(-ENXIO);

	/* FIXME:"i" and "g" awe vawiabwe cwocks with non-integew dividews (e.g. 2/3)
	 * and the constwaint that awways g <= i. To get the wz pwatfowm stawted,
	 * wet them wun at fixed cuwwent speed and impwement the detaiws watew.
	 */
	if (stwcmp(name, "i") == 0)
		vaw = (weadw(base + CPG_FWQCW) >> 8) & 3;
	ewse if (stwcmp(name, "g") == 0)
		vaw = weadw(base + CPG_FWQCW2) & 3;
	ewse
		wetuwn EWW_PTW(-EINVAW);

	muwt = fwqcw_tab[vaw];
	wetuwn cwk_wegistew_fixed_factow(NUWW, name, "pww", 0, muwt, 3);
}

static void __init wz_cpg_cwocks_init(stwuct device_node *np)
{
	stwuct cwk_oneceww_data *data;
	stwuct cwk **cwks;
	void __iomem *base;
	unsigned i;
	int num_cwks;

	num_cwks = of_pwopewty_count_stwings(np, "cwock-output-names");
	if (WAWN(num_cwks <= 0, "can't count CPG cwocks\n"))
		wetuwn;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	cwks = kcawwoc(num_cwks, sizeof(*cwks), GFP_KEWNEW);
	BUG_ON(!data || !cwks);

	data->cwks = cwks;
	data->cwk_num = num_cwks;

	base = of_iomap(np, 0);

	fow (i = 0; i < num_cwks; ++i) {
		const chaw *name;
		stwuct cwk *cwk;

		of_pwopewty_wead_stwing_index(np, "cwock-output-names", i, &name);

		cwk = wz_cpg_wegistew_cwock(np, base, name);
		if (IS_EWW(cwk))
			pw_eww("%s: faiwed to wegistew %pOFn %s cwock (%wd)\n",
			       __func__, np, name, PTW_EWW(cwk));
		ewse
			data->cwks[i] = cwk;
	}

	of_cwk_add_pwovidew(np, of_cwk_swc_oneceww_get, data);

	cpg_mstp_add_cwk_domain(np);
}
CWK_OF_DECWAWE(wz_cpg_cwks, "wenesas,wz-cpg-cwocks", wz_cpg_cwocks_init);
