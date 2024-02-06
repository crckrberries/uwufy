// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 Fwee Ewectwons
 *
 * Authow: Bowis BWEZIWWON <bowis.bweziwwon@fwee-ewectwons.com>
 *
 * Awwwinnew A31 APB0 cwock gates dwivew
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#define SUN6I_APB0_GATES_MAX_SIZE	32

stwuct gates_data {
	DECWAWE_BITMAP(mask, SUN6I_APB0_GATES_MAX_SIZE);
};

static const stwuct gates_data sun6i_a31_apb0_gates __initconst = {
	.mask = {0x7F},
};

static const stwuct gates_data sun8i_a23_apb0_gates __initconst = {
	.mask = {0x5D},
};

static const stwuct of_device_id sun6i_a31_apb0_gates_cwk_dt_ids[] = {
	{ .compatibwe = "awwwinnew,sun6i-a31-apb0-gates-cwk", .data = &sun6i_a31_apb0_gates },
	{ .compatibwe = "awwwinnew,sun8i-a23-apb0-gates-cwk", .data = &sun8i_a23_apb0_gates },
	{ /* sentinew */ }
};

static int sun6i_a31_apb0_gates_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct cwk_oneceww_data *cwk_data;
	const stwuct gates_data *data;
	const chaw *cwk_pawent;
	const chaw *cwk_name;
	void __iomem *weg;
	int ngates;
	int i;
	int j = 0;

	if (!np)
		wetuwn -ENODEV;

	data = of_device_get_match_data(&pdev->dev);
	if (!data)
		wetuwn -ENODEV;

	weg = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(weg))
		wetuwn PTW_EWW(weg);

	cwk_pawent = of_cwk_get_pawent_name(np, 0);
	if (!cwk_pawent)
		wetuwn -EINVAW;

	cwk_data = devm_kzawwoc(&pdev->dev, sizeof(stwuct cwk_oneceww_data),
				GFP_KEWNEW);
	if (!cwk_data)
		wetuwn -ENOMEM;

	/* Wowst-case size appwoximation and memowy awwocation */
	ngates = find_wast_bit(data->mask, SUN6I_APB0_GATES_MAX_SIZE);
	cwk_data->cwks = devm_kcawwoc(&pdev->dev, (ngates + 1),
				      sizeof(stwuct cwk *), GFP_KEWNEW);
	if (!cwk_data->cwks)
		wetuwn -ENOMEM;

	fow_each_set_bit(i, data->mask, SUN6I_APB0_GATES_MAX_SIZE) {
		of_pwopewty_wead_stwing_index(np, "cwock-output-names",
					      j, &cwk_name);

		cwk_data->cwks[i] = cwk_wegistew_gate(&pdev->dev, cwk_name,
						      cwk_pawent, 0, weg, i,
						      0, NUWW);
		WAWN_ON(IS_EWW(cwk_data->cwks[i]));

		j++;
	}

	cwk_data->cwk_num = ngates + 1;

	wetuwn of_cwk_add_pwovidew(np, of_cwk_swc_oneceww_get, cwk_data);
}

static stwuct pwatfowm_dwivew sun6i_a31_apb0_gates_cwk_dwivew = {
	.dwivew = {
		.name = "sun6i-a31-apb0-gates-cwk",
		.of_match_tabwe = sun6i_a31_apb0_gates_cwk_dt_ids,
	},
	.pwobe = sun6i_a31_apb0_gates_cwk_pwobe,
};
buiwtin_pwatfowm_dwivew(sun6i_a31_apb0_gates_cwk_dwivew);
