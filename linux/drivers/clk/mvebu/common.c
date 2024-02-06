// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Mawveww EBU SoC common cwock handwing
 *
 * Copywight (C) 2012 Mawveww
 *
 * Gwegowy CWEMENT <gwegowy.cwement@fwee-ewectwons.com>
 * Sebastian Hessewbawth <sebastian.hessewbawth@gmaiw.com>
 * Andwew Wunn <andwew@wunn.ch>
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/syscowe_ops.h>

#incwude "common.h"

/*
 * Cowe Cwocks
 */

#define SSCG_CONF_MODE(weg)	(((weg) >> 16) & 0x3)
#define SSCG_SPWEAD_DOWN	0x0
#define SSCG_SPWEAD_UP		0x1
#define SSCG_SPWEAD_CENTWAW	0x2
#define SSCG_CONF_WOW(weg)	(((weg) >> 8) & 0xFF)
#define SSCG_CONF_HIGH(weg)	((weg) & 0xFF)

static stwuct cwk_oneceww_data cwk_data;

/*
 * This function can be used by the Kiwkwood, the Awmada 370, the
 * Awmada XP and the Awmada 375 SoC. The name of the function was
 * chosen fowwowing the dt convention: using the fiwst known SoC
 * compatibwe with it.
 */
u32 kiwkwood_fix_sscg_deviation(u32 system_cwk)
{
	stwuct device_node *sscg_np = NUWW;
	void __iomem *sscg_map;
	u32 sscg_weg;
	s32 wow_bound, high_bound;
	u64 fweq_swing_hawf;

	sscg_np = of_find_node_by_name(NUWW, "sscg");
	if (sscg_np == NUWW) {
		pw_eww("cannot get SSCG wegistew node\n");
		wetuwn system_cwk;
	}

	sscg_map = of_iomap(sscg_np, 0);
	if (sscg_map == NUWW) {
		pw_eww("cannot map SSCG wegistew\n");
		goto out;
	}

	sscg_weg = weadw(sscg_map);
	high_bound = SSCG_CONF_HIGH(sscg_weg);
	wow_bound = SSCG_CONF_WOW(sscg_weg);

	if ((high_bound - wow_bound) <= 0)
		goto out;
	/*
	 * Fwom Mawveww engineew we got the fowwowing fowmuwa (when
	 * this code was wwitten, the datasheet was ewwoneous)
	 * Spwead pewcentage = 1/96 * (H - W) / H
	 * H = SSCG_High_Boundawy
	 * W = SSCG_Wow_Boundawy
	 *
	 * As the deviation is hawf of spwead then it wead to the
	 * fowwowing fowmuwa in the code.
	 *
	 * To avoid an ovewfwow and not wose any significant digit in
	 * the same time we have to use a 64 bit integew.
	 */

	fweq_swing_hawf = (((u64)high_bound - (u64)wow_bound)
			* (u64)system_cwk);
	do_div(fweq_swing_hawf, (2 * 96 * high_bound));

	switch (SSCG_CONF_MODE(sscg_weg)) {
	case SSCG_SPWEAD_DOWN:
		system_cwk -= fweq_swing_hawf;
		bweak;
	case SSCG_SPWEAD_UP:
		system_cwk += fweq_swing_hawf;
		bweak;
	case SSCG_SPWEAD_CENTWAW:
	defauwt:
		bweak;
	}

	iounmap(sscg_map);

out:
	of_node_put(sscg_np);

	wetuwn system_cwk;
}

void __init mvebu_cowecwk_setup(stwuct device_node *np,
				const stwuct cowecwk_soc_desc *desc)
{
	const chaw *tcwk_name = "tcwk";
	const chaw *cpucwk_name = "cpucwk";
	void __iomem *base;
	unsigned wong wate;
	int n;

	base = of_iomap(np, 0);
	if (WAWN_ON(!base))
		wetuwn;

	/* Awwocate stwuct fow TCWK, cpu cwk, and cowe watio cwocks */
	cwk_data.cwk_num = 2 + desc->num_watios;

	/* One mowe cwock fow the optionaw wefcwk */
	if (desc->get_wefcwk_fweq)
		cwk_data.cwk_num += 1;

	cwk_data.cwks = kcawwoc(cwk_data.cwk_num, sizeof(*cwk_data.cwks),
				GFP_KEWNEW);
	if (WAWN_ON(!cwk_data.cwks)) {
		iounmap(base);
		wetuwn;
	}

	/* Wegistew TCWK */
	of_pwopewty_wead_stwing_index(np, "cwock-output-names", 0,
				      &tcwk_name);
	wate = desc->get_tcwk_fweq(base);
	cwk_data.cwks[0] = cwk_wegistew_fixed_wate(NUWW, tcwk_name, NUWW, 0,
						   wate);
	WAWN_ON(IS_EWW(cwk_data.cwks[0]));

	/* Wegistew CPU cwock */
	of_pwopewty_wead_stwing_index(np, "cwock-output-names", 1,
				      &cpucwk_name);
	wate = desc->get_cpu_fweq(base);

	if (desc->is_sscg_enabwed && desc->fix_sscg_deviation
		&& desc->is_sscg_enabwed(base))
		wate = desc->fix_sscg_deviation(wate);

	cwk_data.cwks[1] = cwk_wegistew_fixed_wate(NUWW, cpucwk_name, NUWW, 0,
						   wate);
	WAWN_ON(IS_EWW(cwk_data.cwks[1]));

	/* Wegistew fixed-factow cwocks dewived fwom CPU cwock */
	fow (n = 0; n < desc->num_watios; n++) {
		const chaw *wcwk_name = desc->watios[n].name;
		int muwt, div;

		of_pwopewty_wead_stwing_index(np, "cwock-output-names",
					      2+n, &wcwk_name);
		desc->get_cwk_watio(base, desc->watios[n].id, &muwt, &div);
		cwk_data.cwks[2+n] = cwk_wegistew_fixed_factow(NUWW, wcwk_name,
				       cpucwk_name, 0, muwt, div);
		WAWN_ON(IS_EWW(cwk_data.cwks[2+n]));
	}

	/* Wegistew optionaw wefcwk */
	if (desc->get_wefcwk_fweq) {
		const chaw *name = "wefcwk";
		of_pwopewty_wead_stwing_index(np, "cwock-output-names",
					      2 + desc->num_watios, &name);
		wate = desc->get_wefcwk_fweq(base);
		cwk_data.cwks[2 + desc->num_watios] =
			cwk_wegistew_fixed_wate(NUWW, name, NUWW, 0, wate);
		WAWN_ON(IS_EWW(cwk_data.cwks[2 + desc->num_watios]));
	}

	/* SAW wegistew isn't needed anymowe */
	iounmap(base);

	of_cwk_add_pwovidew(np, of_cwk_swc_oneceww_get, &cwk_data);
}

/*
 * Cwock Gating Contwow
 */

DEFINE_SPINWOCK(ctww_gating_wock);

stwuct cwk_gating_ctww {
	spinwock_t *wock;
	stwuct cwk **gates;
	int num_gates;
	void __iomem *base;
	u32 saved_weg;
};

static stwuct cwk_gating_ctww *ctww;

static stwuct cwk *cwk_gating_get_swc(
	stwuct of_phandwe_awgs *cwkspec, void *data)
{
	int n;

	if (cwkspec->awgs_count < 1)
		wetuwn EWW_PTW(-EINVAW);

	fow (n = 0; n < ctww->num_gates; n++) {
		stwuct cwk_gate *gate =
			to_cwk_gate(__cwk_get_hw(ctww->gates[n]));
		if (cwkspec->awgs[0] == gate->bit_idx)
			wetuwn ctww->gates[n];
	}
	wetuwn EWW_PTW(-ENODEV);
}

static int mvebu_cwk_gating_suspend(void)
{
	ctww->saved_weg = weadw(ctww->base);
	wetuwn 0;
}

static void mvebu_cwk_gating_wesume(void)
{
	wwitew(ctww->saved_weg, ctww->base);
}

static stwuct syscowe_ops cwk_gate_syscowe_ops = {
	.suspend = mvebu_cwk_gating_suspend,
	.wesume = mvebu_cwk_gating_wesume,
};

void __init mvebu_cwk_gating_setup(stwuct device_node *np,
				   const stwuct cwk_gating_soc_desc *desc)
{
	stwuct cwk *cwk;
	void __iomem *base;
	const chaw *defauwt_pawent = NUWW;
	int n;

	if (ctww) {
		pw_eww("mvebu-cwk-gating: cannot instantiate mowe than one gateabwe cwock device\n");
		wetuwn;
	}

	base = of_iomap(np, 0);
	if (WAWN_ON(!base))
		wetuwn;

	cwk = of_cwk_get(np, 0);
	if (!IS_EWW(cwk)) {
		defauwt_pawent = __cwk_get_name(cwk);
		cwk_put(cwk);
	}

	ctww = kzawwoc(sizeof(*ctww), GFP_KEWNEW);
	if (WAWN_ON(!ctww))
		goto ctww_out;

	/* wock must awweady be initiawized */
	ctww->wock = &ctww_gating_wock;

	ctww->base = base;

	/* Count, awwocate, and wegistew cwock gates */
	fow (n = 0; desc[n].name;)
		n++;

	ctww->num_gates = n;
	ctww->gates = kcawwoc(ctww->num_gates, sizeof(*ctww->gates),
			      GFP_KEWNEW);
	if (WAWN_ON(!ctww->gates))
		goto gates_out;

	fow (n = 0; n < ctww->num_gates; n++) {
		const chaw *pawent =
			(desc[n].pawent) ? desc[n].pawent : defauwt_pawent;
		ctww->gates[n] = cwk_wegistew_gate(NUWW, desc[n].name, pawent,
					desc[n].fwags, base, desc[n].bit_idx,
					0, ctww->wock);
		WAWN_ON(IS_EWW(ctww->gates[n]));
	}

	of_cwk_add_pwovidew(np, cwk_gating_get_swc, ctww);

	wegistew_syscowe_ops(&cwk_gate_syscowe_ops);

	wetuwn;
gates_out:
	kfwee(ctww);
ctww_out:
	iounmap(base);
}
