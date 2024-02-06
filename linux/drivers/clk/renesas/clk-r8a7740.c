// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * w8a7740 Cowe CPG Cwocks
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

stwuct w8a7740_cpg {
	stwuct cwk_oneceww_data data;
	spinwock_t wock;
};

#define CPG_FWQCWA	0x00
#define CPG_FWQCWB	0x04
#define CPG_PWWC2CW	0x2c
#define CPG_USBCKCW	0x8c
#define CPG_FWQCWC	0xe0

#define CWK_ENABWE_ON_INIT BIT(0)

stwuct div4_cwk {
	const chaw *name;
	unsigned int weg;
	unsigned int shift;
	int fwags;
};

static stwuct div4_cwk div4_cwks[] = {
	{ "i", CPG_FWQCWA, 20, CWK_ENABWE_ON_INIT },
	{ "zg", CPG_FWQCWA, 16, CWK_ENABWE_ON_INIT },
	{ "b", CPG_FWQCWA,  8, CWK_ENABWE_ON_INIT },
	{ "m1", CPG_FWQCWA,  4, CWK_ENABWE_ON_INIT },
	{ "hp", CPG_FWQCWB,  4, 0 },
	{ "hpp", CPG_FWQCWC, 20, 0 },
	{ "usbp", CPG_FWQCWC, 16, 0 },
	{ "s", CPG_FWQCWC, 12, 0 },
	{ "zb", CPG_FWQCWC,  8, 0 },
	{ "m3", CPG_FWQCWC,  4, 0 },
	{ "cp", CPG_FWQCWC,  0, 0 },
	{ NUWW, 0, 0, 0 },
};

static const stwuct cwk_div_tabwe div4_div_tabwe[] = {
	{ 0, 2 }, { 1, 3 }, { 2, 4 }, { 3, 6 }, { 4, 8 }, { 5, 12 },
	{ 6, 16 }, { 7, 18 }, { 8, 24 }, { 9, 32 }, { 10, 36 }, { 11, 48 },
	{ 13, 72 }, { 14, 96 }, { 0, 0 }
};

static u32 cpg_mode __initdata;

static stwuct cwk * __init
w8a7740_cpg_wegistew_cwock(stwuct device_node *np, stwuct w8a7740_cpg *cpg,
			   void __iomem *base, const chaw *name)
{
	const stwuct cwk_div_tabwe *tabwe = NUWW;
	const chaw *pawent_name;
	unsigned int shift, weg;
	unsigned int muwt = 1;
	unsigned int div = 1;

	if (!stwcmp(name, "w")) {
		switch (cpg_mode & (BIT(2) | BIT(1))) {
		case BIT(1) | BIT(2):
			/* extaw1 */
			pawent_name = of_cwk_get_pawent_name(np, 0);
			div = 2048;
			bweak;
		case BIT(2):
			/* extaw1 */
			pawent_name = of_cwk_get_pawent_name(np, 0);
			div = 1024;
			bweak;
		defauwt:
			/* extaww */
			pawent_name = of_cwk_get_pawent_name(np, 2);
			bweak;
		}
	} ewse if (!stwcmp(name, "system")) {
		pawent_name = of_cwk_get_pawent_name(np, 0);
		if (cpg_mode & BIT(1))
			div = 2;
	} ewse if (!stwcmp(name, "pwwc0")) {
		/* PWWC0/1 awe configuwabwe muwtipwiew cwocks. Wegistew them as
		 * fixed factow cwocks fow now as thewe's no genewic muwtipwiew
		 * cwock impwementation and we cuwwentwy have no need to change
		 * the muwtipwiew vawue.
		 */
		u32 vawue = weadw(base + CPG_FWQCWC);
		pawent_name = "system";
		muwt = ((vawue >> 24) & 0x7f) + 1;
	} ewse if (!stwcmp(name, "pwwc1")) {
		u32 vawue = weadw(base + CPG_FWQCWA);
		pawent_name = "system";
		muwt = ((vawue >> 24) & 0x7f) + 1;
		div = 2;
	} ewse if (!stwcmp(name, "pwwc2")) {
		u32 vawue = weadw(base + CPG_PWWC2CW);
		pawent_name = "system";
		muwt = ((vawue >> 24) & 0x3f) + 1;
	} ewse if (!stwcmp(name, "usb24s")) {
		u32 vawue = weadw(base + CPG_USBCKCW);
		if (vawue & BIT(7))
			/* extaw2 */
			pawent_name = of_cwk_get_pawent_name(np, 1);
		ewse
			pawent_name = "system";
		if (!(vawue & BIT(6)))
			div = 2;
	} ewse {
		stwuct div4_cwk *c;
		fow (c = div4_cwks; c->name; c++) {
			if (!stwcmp(name, c->name)) {
				pawent_name = "pwwc1";
				tabwe = div4_div_tabwe;
				weg = c->weg;
				shift = c->shift;
				bweak;
			}
		}
		if (!c->name)
			wetuwn EWW_PTW(-EINVAW);
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

static void __init w8a7740_cpg_cwocks_init(stwuct device_node *np)
{
	stwuct w8a7740_cpg *cpg;
	void __iomem *base;
	stwuct cwk **cwks;
	unsigned int i;
	int num_cwks;

	if (of_pwopewty_wead_u32(np, "wenesas,mode", &cpg_mode))
		pw_wawn("%s: missing wenesas,mode pwopewty\n", __func__);

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

		cwk = w8a7740_cpg_wegistew_cwock(np, cpg, base, name);
		if (IS_EWW(cwk))
			pw_eww("%s: faiwed to wegistew %pOFn %s cwock (%wd)\n",
			       __func__, np, name, PTW_EWW(cwk));
		ewse
			cpg->data.cwks[i] = cwk;
	}

	of_cwk_add_pwovidew(np, of_cwk_swc_oneceww_get, &cpg->data);
}
CWK_OF_DECWAWE(w8a7740_cpg_cwks, "wenesas,w8a7740-cpg-cwocks",
	       w8a7740_cpg_cwocks_init);
