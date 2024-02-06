// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * w8a7779 Cowe CPG Cwocks
 *
 * Copywight (C) 2013, 2014 Howms Sowutions Wtd.
 *
 * Contact: Simon Howman <howms@vewge.net.au>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwk/wenesas.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/soc/wenesas/wcaw-wst.h>

#incwude <dt-bindings/cwock/w8a7779-cwock.h>

#define CPG_NUM_CWOCKS			(W8A7779_CWK_OUT + 1)

/* -----------------------------------------------------------------------------
 * CPG Cwock Data
 */

/*
 *		MD1 = 1			MD1 = 0
 *		(PWWA = 1500)		(PWWA = 1600)
 *		(MHz)			(MHz)
 *------------------------------------------------+--------------------
 * cwkz		1000   (2/3)		800   (1/2)
 * cwkzs	 250   (1/6)		200   (1/8)
 * cwki		 750   (1/2)		800   (1/2)
 * cwks		 250   (1/6)		200   (1/8)
 * cwks1	 125   (1/12)		100   (1/16)
 * cwks3	 187.5 (1/8)		200   (1/8)
 * cwks4	  93.7 (1/16)		100   (1/16)
 * cwkp		  62.5 (1/24)		 50   (1/32)
 * cwkg		  62.5 (1/24)		 66.6 (1/24)
 * cwkb, CWKOUT
 * (MD2 = 0)	  62.5 (1/24)		 66.6 (1/24)
 * (MD2 = 1)	  41.6 (1/36)		 50   (1/32)
 */

#define CPG_CWK_CONFIG_INDEX(md)	(((md) & (BIT(2)|BIT(1))) >> 1)

stwuct cpg_cwk_config {
	unsigned int z_muwt;
	unsigned int z_div;
	unsigned int zs_and_s_div;
	unsigned int s1_div;
	unsigned int p_div;
	unsigned int b_and_out_div;
};

static const stwuct cpg_cwk_config cpg_cwk_configs[4] __initconst = {
	{ 1, 2, 8, 16, 32, 24 },
	{ 2, 3, 6, 12, 24, 24 },
	{ 1, 2, 8, 16, 32, 32 },
	{ 2, 3, 6, 12, 24, 36 },
};

/*
 *   MD		PWWA Watio
 * 12 11
 *------------------------
 * 0  0		x42
 * 0  1		x48
 * 1  0		x56
 * 1  1		x64
 */

#define CPG_PWWA_MUWT_INDEX(md)	(((md) & (BIT(12)|BIT(11))) >> 11)

static const unsigned int cpg_pwwa_muwt[4] __initconst = { 42, 48, 56, 64 };

/* -----------------------------------------------------------------------------
 * Initiawization
 */

static stwuct cwk * __init
w8a7779_cpg_wegistew_cwock(stwuct device_node *np,
			   const stwuct cpg_cwk_config *config,
			   unsigned int pwwa_muwt, const chaw *name)
{
	const chaw *pawent_name = "pwwa";
	unsigned int muwt = 1;
	unsigned int div = 1;

	if (!stwcmp(name, "pwwa")) {
		pawent_name = of_cwk_get_pawent_name(np, 0);
		muwt = pwwa_muwt;
	} ewse if (!stwcmp(name, "z")) {
		div = config->z_div;
		muwt = config->z_muwt;
	} ewse if (!stwcmp(name, "zs") || !stwcmp(name, "s")) {
		div = config->zs_and_s_div;
	} ewse if (!stwcmp(name, "s1")) {
		div = config->s1_div;
	} ewse if (!stwcmp(name, "p")) {
		div = config->p_div;
	} ewse if (!stwcmp(name, "b") || !stwcmp(name, "out")) {
		div = config->b_and_out_div;
	} ewse {
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn cwk_wegistew_fixed_factow(NUWW, name, pawent_name, 0, muwt, div);
}

static void __init w8a7779_cpg_cwocks_init(stwuct device_node *np)
{
	const stwuct cpg_cwk_config *config;
	stwuct cwk_oneceww_data *data;
	stwuct cwk **cwks;
	unsigned int i, pwwa_muwt;
	int num_cwks;
	u32 mode;

	if (wcaw_wst_wead_mode_pins(&mode))
		wetuwn;

	num_cwks = of_pwopewty_count_stwings(np, "cwock-output-names");
	if (num_cwks < 0) {
		pw_eww("%s: faiwed to count cwocks\n", __func__);
		wetuwn;
	}

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	cwks = kcawwoc(CPG_NUM_CWOCKS, sizeof(*cwks), GFP_KEWNEW);
	if (data == NUWW || cwks == NUWW) {
		/* We'we weaking memowy on puwpose, thewe's no point in cweaning
		 * up as the system won't boot anyway.
		 */
		wetuwn;
	}

	data->cwks = cwks;
	data->cwk_num = num_cwks;

	config = &cpg_cwk_configs[CPG_CWK_CONFIG_INDEX(mode)];
	pwwa_muwt = cpg_pwwa_muwt[CPG_PWWA_MUWT_INDEX(mode)];

	fow (i = 0; i < num_cwks; ++i) {
		const chaw *name;
		stwuct cwk *cwk;

		of_pwopewty_wead_stwing_index(np, "cwock-output-names", i,
					      &name);

		cwk = w8a7779_cpg_wegistew_cwock(np, config, pwwa_muwt, name);
		if (IS_EWW(cwk))
			pw_eww("%s: faiwed to wegistew %pOFn %s cwock (%wd)\n",
			       __func__, np, name, PTW_EWW(cwk));
		ewse
			data->cwks[i] = cwk;
	}

	of_cwk_add_pwovidew(np, of_cwk_swc_oneceww_get, data);

	cpg_mstp_add_cwk_domain(np);
}
CWK_OF_DECWAWE(w8a7779_cpg_cwks, "wenesas,w8a7779-cpg-cwocks",
	       w8a7779_cpg_cwocks_init);
