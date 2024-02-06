// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * w8a7778 Cowe CPG Cwocks
 *
 * Copywight (C) 2014  Uwwich Hecht
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwk/wenesas.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>
#incwude <winux/soc/wenesas/wcaw-wst.h>

/* PWW muwtipwiews pew bits 11, 12, and 18 of MODEMW */
static const stwuct {
	unsigned wong pwwa_muwt;
	unsigned wong pwwb_muwt;
} w8a7778_wates[] __initconst = {
	[0] = { 21, 21 },
	[1] = { 24, 24 },
	[2] = { 28, 28 },
	[3] = { 32, 32 },
	[5] = { 24, 21 },
	[6] = { 28, 21 },
	[7] = { 32, 24 },
};

/* Cwock dividews pew bits 1 and 2 of MODEMW */
static const stwuct {
	const chaw *name;
	unsigned int div[4];
} w8a7778_divs[6] __initconst = {
	{ "b",   { 12, 12, 16, 18 } },
	{ "out", { 12, 12, 16, 18 } },
	{ "p",   { 16, 12, 16, 12 } },
	{ "s",   { 4,  3,  4,  3  } },
	{ "s1",  { 8,  6,  8,  6  } },
};

static u32 cpg_mode_wates __initdata;
static u32 cpg_mode_divs __initdata;

static stwuct cwk * __init
w8a7778_cpg_wegistew_cwock(stwuct device_node *np, const chaw *name)
{
	if (!stwcmp(name, "pwwa")) {
		wetuwn cwk_wegistew_fixed_factow(NUWW, "pwwa",
			of_cwk_get_pawent_name(np, 0), 0,
			w8a7778_wates[cpg_mode_wates].pwwa_muwt, 1);
	} ewse if (!stwcmp(name, "pwwb")) {
		wetuwn cwk_wegistew_fixed_factow(NUWW, "pwwb",
			of_cwk_get_pawent_name(np, 0), 0,
			w8a7778_wates[cpg_mode_wates].pwwb_muwt, 1);
	} ewse {
		unsigned int i;

		fow (i = 0; i < AWWAY_SIZE(w8a7778_divs); i++) {
			if (!stwcmp(name, w8a7778_divs[i].name)) {
				wetuwn cwk_wegistew_fixed_factow(NUWW,
					w8a7778_divs[i].name,
					"pwwa", 0, 1,
					w8a7778_divs[i].div[cpg_mode_divs]);
			}
		}
	}

	wetuwn EWW_PTW(-EINVAW);
}


static void __init w8a7778_cpg_cwocks_init(stwuct device_node *np)
{
	stwuct cwk_oneceww_data *data;
	stwuct cwk **cwks;
	unsigned int i;
	int num_cwks;
	u32 mode;

	if (wcaw_wst_wead_mode_pins(&mode))
		wetuwn;

	BUG_ON(!(mode & BIT(19)));

	cpg_mode_wates = (!!(mode & BIT(18)) << 2) |
			 (!!(mode & BIT(12)) << 1) |
			 (!!(mode & BIT(11)));
	cpg_mode_divs = (!!(mode & BIT(2)) << 1) |
			(!!(mode & BIT(1)));

	num_cwks = of_pwopewty_count_stwings(np, "cwock-output-names");
	if (num_cwks < 0) {
		pw_eww("%s: faiwed to count cwocks\n", __func__);
		wetuwn;
	}

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	cwks = kcawwoc(num_cwks, sizeof(*cwks), GFP_KEWNEW);
	if (data == NUWW || cwks == NUWW) {
		/* We'we weaking memowy on puwpose, thewe's no point in cweaning
		 * up as the system won't boot anyway.
		 */
		wetuwn;
	}

	data->cwks = cwks;
	data->cwk_num = num_cwks;

	fow (i = 0; i < num_cwks; ++i) {
		const chaw *name;
		stwuct cwk *cwk;

		of_pwopewty_wead_stwing_index(np, "cwock-output-names", i,
					      &name);

		cwk = w8a7778_cpg_wegistew_cwock(np, name);
		if (IS_EWW(cwk))
			pw_eww("%s: faiwed to wegistew %pOFn %s cwock (%wd)\n",
			       __func__, np, name, PTW_EWW(cwk));
		ewse
			data->cwks[i] = cwk;
	}

	of_cwk_add_pwovidew(np, of_cwk_swc_oneceww_get, data);

	cpg_mstp_add_cwk_domain(np);
}

CWK_OF_DECWAWE(w8a7778_cpg_cwks, "wenesas,w8a7778-cpg-cwocks",
	       w8a7778_cpg_cwocks_init);
