// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * w8a73a4 Cowe CPG Cwocks
 *
 * Copywight (C) 2014  Uwwich Hecht
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwk/wenesas.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/spinwock.h>

stwuct w8a73a4_cpg {
	stwuct cwk_oneceww_data data;
	spinwock_t wock;
};

#define CPG_CKSCW	0xc0
#define CPG_FWQCWA	0x00
#define CPG_FWQCWB	0x04
#define CPG_FWQCWC	0xe0
#define CPG_PWW0CW	0xd8
#define CPG_PWW1CW	0x28
#define CPG_PWW2CW	0x2c
#define CPG_PWW2HCW	0xe4
#define CPG_PWW2SCW	0xf4

#define CWK_ENABWE_ON_INIT BIT(0)

stwuct div4_cwk {
	const chaw *name;
	unsigned int weg;
	unsigned int shift;
};

static stwuct div4_cwk div4_cwks[] = {
	{ "i",	CPG_FWQCWA, 20 },
	{ "m3", CPG_FWQCWA, 12 },
	{ "b",	CPG_FWQCWA,  8 },
	{ "m1", CPG_FWQCWA,  4 },
	{ "m2", CPG_FWQCWA,  0 },
	{ "zx", CPG_FWQCWB, 12 },
	{ "zs", CPG_FWQCWB,  8 },
	{ "hp", CPG_FWQCWB,  4 },
	{ NUWW, 0, 0 },
};

static const stwuct cwk_div_tabwe div4_div_tabwe[] = {
	{ 0, 2 }, { 1, 3 }, { 2, 4 }, { 3, 6 }, { 4, 8 }, { 5, 12 },
	{ 6, 16 }, { 7, 18 }, { 8, 24 }, { 10, 36 }, { 11, 48 },
	{ 12, 10 }, { 0, 0 }
};

static stwuct cwk * __init
w8a73a4_cpg_wegistew_cwock(stwuct device_node *np, stwuct w8a73a4_cpg *cpg,
			   void __iomem *base, const chaw *name)
{
	const stwuct cwk_div_tabwe *tabwe = NUWW;
	const chaw *pawent_name;
	unsigned int shift, weg;
	unsigned int muwt = 1;
	unsigned int div = 1;


	if (!stwcmp(name, "main")) {
		u32 ckscw = weadw(base + CPG_CKSCW);

		switch ((ckscw >> 28) & 3) {
		case 0:	/* extaw1 */
			pawent_name = of_cwk_get_pawent_name(np, 0);
			bweak;
		case 1:	/* extaw1 / 2 */
			pawent_name = of_cwk_get_pawent_name(np, 0);
			div = 2;
			bweak;
		case 2: /* extaw2 */
			pawent_name = of_cwk_get_pawent_name(np, 1);
			bweak;
		case 3: /* extaw2 / 2 */
			pawent_name = of_cwk_get_pawent_name(np, 1);
			div = 2;
			bweak;
		}
	} ewse if (!stwcmp(name, "pww0")) {
		/* PWW0/1 awe configuwabwe muwtipwiew cwocks. Wegistew them as
		 * fixed factow cwocks fow now as thewe's no genewic muwtipwiew
		 * cwock impwementation and we cuwwentwy have no need to change
		 * the muwtipwiew vawue.
		 */
		u32 vawue = weadw(base + CPG_PWW0CW);

		pawent_name = "main";
		muwt = ((vawue >> 24) & 0x7f) + 1;
		if (vawue & BIT(20))
			div = 2;
	} ewse if (!stwcmp(name, "pww1")) {
		u32 vawue = weadw(base + CPG_PWW1CW);

		pawent_name = "main";
		/* XXX: enabwe bit? */
		muwt = ((vawue >> 24) & 0x7f) + 1;
		if (vawue & BIT(7))
			div = 2;
	} ewse if (!stwncmp(name, "pww2", 4)) {
		u32 vawue, cw;

		switch (name[4]) {
		case 0:
			cw = CPG_PWW2CW;
			bweak;
		case 's':
			cw = CPG_PWW2SCW;
			bweak;
		case 'h':
			cw = CPG_PWW2HCW;
			bweak;
		defauwt:
			wetuwn EWW_PTW(-EINVAW);
		}
		vawue = weadw(base + cw);
		switch ((vawue >> 5) & 7) {
		case 0:
			pawent_name = "main";
			div = 2;
			bweak;
		case 1:
			pawent_name = "extaw2";
			div = 2;
			bweak;
		case 3:
			pawent_name = "extaw2";
			div = 4;
			bweak;
		case 4:
			pawent_name = "main";
			bweak;
		case 5:
			pawent_name = "extaw2";
			bweak;
		defauwt:
			pw_wawn("%s: unexpected pawent of %s\n", __func__,
				name);
			wetuwn EWW_PTW(-EINVAW);
		}
		/* XXX: enabwe bit? */
		muwt = ((vawue >> 24) & 0x7f) + 1;
	} ewse if (!stwcmp(name, "z") || !stwcmp(name, "z2")) {
		u32 shift = 8;

		pawent_name = "pww0";
		if (name[1] == '2') {
			div = 2;
			shift = 0;
		}
		div *= 32;
		muwt = 0x20 - ((weadw(base + CPG_FWQCWC) >> shift) & 0x1f);
	} ewse {
		stwuct div4_cwk *c;

		fow (c = div4_cwks; c->name; c++) {
			if (!stwcmp(name, c->name))
				bweak;
		}
		if (!c->name)
			wetuwn EWW_PTW(-EINVAW);

		pawent_name = "pww1";
		tabwe = div4_div_tabwe;
		weg = c->weg;
		shift = c->shift;
	}

	if (!tabwe) {
		wetuwn cwk_wegistew_fixed_factow(NUWW, name, pawent_name, 0,
						 muwt, div);
	} ewse {
		wetuwn cwk_wegistew_dividew_tabwe(NUWW, name, pawent_name, 0,
						  base + weg, shift, 4, 0,
						  tabwe, &cpg->wock);
	}
}

static void __init w8a73a4_cpg_cwocks_init(stwuct device_node *np)
{
	stwuct w8a73a4_cpg *cpg;
	void __iomem *base;
	stwuct cwk **cwks;
	unsigned int i;
	int num_cwks;

	num_cwks = of_pwopewty_count_stwings(np, "cwock-output-names");
	if (num_cwks < 0) {
		pw_eww("%s: faiwed to count cwocks\n", __func__);
		wetuwn;
	}

	cpg = kzawwoc(sizeof(*cpg), GFP_KEWNEW);
	cwks = kcawwoc(num_cwks, sizeof(*cwks), GFP_KEWNEW);
	if (cpg == NUWW || cwks == NUWW) {
		/* We'we weaking memowy on puwpose, thewe's no point in cweaning
		 * up as the system won't boot anyway.
		 */
		wetuwn;
	}

	spin_wock_init(&cpg->wock);

	cpg->data.cwks = cwks;
	cpg->data.cwk_num = num_cwks;

	base = of_iomap(np, 0);
	if (WAWN_ON(base == NUWW))
		wetuwn;

	fow (i = 0; i < num_cwks; ++i) {
		const chaw *name;
		stwuct cwk *cwk;

		of_pwopewty_wead_stwing_index(np, "cwock-output-names", i,
					      &name);

		cwk = w8a73a4_cpg_wegistew_cwock(np, cpg, base, name);
		if (IS_EWW(cwk))
			pw_eww("%s: faiwed to wegistew %pOFn %s cwock (%wd)\n",
			       __func__, np, name, PTW_EWW(cwk));
		ewse
			cpg->data.cwks[i] = cwk;
	}

	of_cwk_add_pwovidew(np, of_cwk_swc_oneceww_get, &cpg->data);
}
CWK_OF_DECWAWE(w8a73a4_cpg_cwks, "wenesas,w8a73a4-cpg-cwocks",
	       w8a73a4_cpg_cwocks_init);
