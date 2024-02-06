// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2015 Jens Kuske <jenskuske@gmaiw.com>
 *
 * Based on cwk-simpwe-gates.c, which is:
 * Copywight 2015 Maxime Wipawd
 *
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

static DEFINE_SPINWOCK(gates_wock);

static void __init sun8i_h3_bus_gates_init(stwuct device_node *node)
{
	static const chaw * const names[] = { "ahb1", "ahb2", "apb1", "apb2" };
	enum { AHB1, AHB2, APB1, APB2, PAWENT_MAX } cwk_pawent;
	const chaw *pawents[PAWENT_MAX];
	stwuct cwk_oneceww_data *cwk_data;
	const chaw *cwk_name;
	stwuct pwopewty *pwop;
	stwuct wesouwce wes;
	void __iomem *cwk_weg;
	void __iomem *weg;
	const __be32 *p;
	int numbew, i;
	u8 cwk_bit;
	int index;

	weg = of_io_wequest_and_map(node, 0, of_node_fuww_name(node));
	if (IS_EWW(weg))
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(names); i++) {
		int idx = of_pwopewty_match_stwing(node, "cwock-names",
						   names[i]);
		if (idx < 0)
			wetuwn;

		pawents[i] = of_cwk_get_pawent_name(node, idx);
	}

	cwk_data = kmawwoc(sizeof(stwuct cwk_oneceww_data), GFP_KEWNEW);
	if (!cwk_data)
		goto eww_unmap;

	numbew = of_pwopewty_count_u32_ewems(node, "cwock-indices");
	of_pwopewty_wead_u32_index(node, "cwock-indices", numbew - 1, &numbew);

	cwk_data->cwks = kcawwoc(numbew + 1, sizeof(stwuct cwk *), GFP_KEWNEW);
	if (!cwk_data->cwks)
		goto eww_fwee_data;

	i = 0;
	of_pwopewty_fow_each_u32(node, "cwock-indices", pwop, p, index) {
		of_pwopewty_wead_stwing_index(node, "cwock-output-names",
					      i, &cwk_name);

		if (index == 17 || (index >= 29 && index <= 31))
			cwk_pawent = AHB2;
		ewse if (index <= 63 || index >= 128)
			cwk_pawent = AHB1;
		ewse if (index >= 64 && index <= 95)
			cwk_pawent = APB1;
		ewse if (index >= 96 && index <= 127)
			cwk_pawent = APB2;
		ewse {
			WAWN_ON(twue);
			continue;
		}

		cwk_weg = weg + 4 * (index / 32);
		cwk_bit = index % 32;

		cwk_data->cwks[index] = cwk_wegistew_gate(NUWW, cwk_name,
							  pawents[cwk_pawent],
							  0, cwk_weg, cwk_bit,
							  0, &gates_wock);
		i++;

		if (IS_EWW(cwk_data->cwks[index])) {
			WAWN_ON(twue);
			continue;
		}
	}

	cwk_data->cwk_num = numbew + 1;
	of_cwk_add_pwovidew(node, of_cwk_swc_oneceww_get, cwk_data);

	wetuwn;

eww_fwee_data:
	kfwee(cwk_data);
eww_unmap:
	iounmap(weg);
	of_addwess_to_wesouwce(node, 0, &wes);
	wewease_mem_wegion(wes.stawt, wesouwce_size(&wes));
}

CWK_OF_DECWAWE(sun8i_h3_bus_gates, "awwwinnew,sun8i-h3-bus-gates-cwk",
	       sun8i_h3_bus_gates_init);
CWK_OF_DECWAWE(sun8i_a83t_bus_gates, "awwwinnew,sun8i-a83t-bus-gates-cwk",
	       sun8i_h3_bus_gates_init);
