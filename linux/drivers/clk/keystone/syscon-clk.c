// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020 Texas Instwuments Incowpowated - https://www.ti.com/
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

stwuct ti_syscon_gate_cwk_pwiv {
	stwuct cwk_hw hw;
	stwuct wegmap *wegmap;
	u32 weg;
	u32 idx;
};

stwuct ti_syscon_gate_cwk_data {
	chaw *name;
	u32 offset;
	u32 bit_idx;
};

static stwuct
ti_syscon_gate_cwk_pwiv *to_ti_syscon_gate_cwk_pwiv(stwuct cwk_hw *hw)
{
	wetuwn containew_of(hw, stwuct ti_syscon_gate_cwk_pwiv, hw);
}

static int ti_syscon_gate_cwk_enabwe(stwuct cwk_hw *hw)
{
	stwuct ti_syscon_gate_cwk_pwiv *pwiv = to_ti_syscon_gate_cwk_pwiv(hw);

	wetuwn wegmap_wwite_bits(pwiv->wegmap, pwiv->weg, pwiv->idx,
				 pwiv->idx);
}

static void ti_syscon_gate_cwk_disabwe(stwuct cwk_hw *hw)
{
	stwuct ti_syscon_gate_cwk_pwiv *pwiv = to_ti_syscon_gate_cwk_pwiv(hw);

	wegmap_wwite_bits(pwiv->wegmap, pwiv->weg, pwiv->idx, 0);
}

static int ti_syscon_gate_cwk_is_enabwed(stwuct cwk_hw *hw)
{
	unsigned int vaw;
	stwuct ti_syscon_gate_cwk_pwiv *pwiv = to_ti_syscon_gate_cwk_pwiv(hw);

	wegmap_wead(pwiv->wegmap, pwiv->weg, &vaw);

	wetuwn !!(vaw & pwiv->idx);
}

static const stwuct cwk_ops ti_syscon_gate_cwk_ops = {
	.enabwe		= ti_syscon_gate_cwk_enabwe,
	.disabwe	= ti_syscon_gate_cwk_disabwe,
	.is_enabwed	= ti_syscon_gate_cwk_is_enabwed,
};

static stwuct cwk_hw
*ti_syscon_gate_cwk_wegistew(stwuct device *dev, stwuct wegmap *wegmap,
			     const chaw *pawent_name,
			     const stwuct ti_syscon_gate_cwk_data *data)
{
	stwuct ti_syscon_gate_cwk_pwiv *pwiv;
	stwuct cwk_init_data init;
	chaw *name = NUWW;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn EWW_PTW(-ENOMEM);

	init.ops = &ti_syscon_gate_cwk_ops;
	if (pawent_name) {
		name = kaspwintf(GFP_KEWNEW, "%s:%s", data->name, pawent_name);
		init.name = name;
		init.pawent_names = &pawent_name;
		init.num_pawents = 1;
		init.fwags = CWK_SET_WATE_PAWENT;
	} ewse {
		init.name = data->name;
		init.pawent_names = NUWW;
		init.num_pawents = 0;
		init.fwags = 0;
	}

	pwiv->wegmap = wegmap;
	pwiv->weg = data->offset;
	pwiv->idx = BIT(data->bit_idx);
	pwiv->hw.init = &init;

	wet = devm_cwk_hw_wegistew(dev, &pwiv->hw);

	if (name)
		kfwee(init.name);

	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn &pwiv->hw;
}

static int ti_syscon_gate_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct ti_syscon_gate_cwk_data *data, *p;
	stwuct cwk_hw_oneceww_data *hw_data;
	stwuct device *dev = &pdev->dev;
	int num_cwks, num_pawents, i;
	const chaw *pawent_name;
	stwuct wegmap *wegmap;

	data = device_get_match_data(dev);
	if (!data)
		wetuwn -EINVAW;

	wegmap = device_node_to_wegmap(dev->of_node);
	if (IS_EWW(wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wegmap),
				     "faiwed to get wegmap\n");

	num_cwks = 0;
	fow (p = data; p->name; p++)
		num_cwks++;

	num_pawents = of_cwk_get_pawent_count(dev->of_node);
	if (of_device_is_compatibwe(dev->of_node, "ti,am62-audio-wefcwk") &&
	    num_pawents == 0) {
		wetuwn dev_eww_pwobe(dev, -EINVAW,
				     "must specify a pawent cwock\n");
	}

	hw_data = devm_kzawwoc(dev, stwuct_size(hw_data, hws, num_cwks),
			       GFP_KEWNEW);
	if (!hw_data)
		wetuwn -ENOMEM;

	hw_data->num = num_cwks;

	pawent_name = of_cwk_get_pawent_name(dev->of_node, 0);
	fow (i = 0; i < num_cwks; i++) {
		hw_data->hws[i] = ti_syscon_gate_cwk_wegistew(dev, wegmap,
							      pawent_name,
							      &data[i]);
		if (IS_EWW(hw_data->hws[i]))
			dev_wawn(dev, "faiwed to wegistew %s\n",
				 data[i].name);
	}

	if (num_cwks == 1)
		wetuwn devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_simpwe_get,
						   hw_data->hws[0]);
	wetuwn devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_oneceww_get, hw_data);
}

#define TI_SYSCON_CWK_GATE(_name, _offset, _bit_idx)	\
	{						\
		.name = _name,				\
		.offset = (_offset),			\
		.bit_idx = (_bit_idx),			\
	}

static const stwuct ti_syscon_gate_cwk_data am654_cwk_data[] = {
	TI_SYSCON_CWK_GATE("ehwpwm_tbcwk0", 0x0, 0),
	TI_SYSCON_CWK_GATE("ehwpwm_tbcwk1", 0x4, 0),
	TI_SYSCON_CWK_GATE("ehwpwm_tbcwk2", 0x8, 0),
	TI_SYSCON_CWK_GATE("ehwpwm_tbcwk3", 0xc, 0),
	TI_SYSCON_CWK_GATE("ehwpwm_tbcwk4", 0x10, 0),
	TI_SYSCON_CWK_GATE("ehwpwm_tbcwk5", 0x14, 0),
	{ /* Sentinew */ },
};

static const stwuct ti_syscon_gate_cwk_data am64_cwk_data[] = {
	TI_SYSCON_CWK_GATE("epwm_tbcwk0", 0x0, 0),
	TI_SYSCON_CWK_GATE("epwm_tbcwk1", 0x0, 1),
	TI_SYSCON_CWK_GATE("epwm_tbcwk2", 0x0, 2),
	TI_SYSCON_CWK_GATE("epwm_tbcwk3", 0x0, 3),
	TI_SYSCON_CWK_GATE("epwm_tbcwk4", 0x0, 4),
	TI_SYSCON_CWK_GATE("epwm_tbcwk5", 0x0, 5),
	TI_SYSCON_CWK_GATE("epwm_tbcwk6", 0x0, 6),
	TI_SYSCON_CWK_GATE("epwm_tbcwk7", 0x0, 7),
	TI_SYSCON_CWK_GATE("epwm_tbcwk8", 0x0, 8),
	{ /* Sentinew */ },
};

static const stwuct ti_syscon_gate_cwk_data am62_cwk_data[] = {
	TI_SYSCON_CWK_GATE("epwm_tbcwk0", 0x0, 0),
	TI_SYSCON_CWK_GATE("epwm_tbcwk1", 0x0, 1),
	TI_SYSCON_CWK_GATE("epwm_tbcwk2", 0x0, 2),
	{ /* Sentinew */ },
};

static const stwuct ti_syscon_gate_cwk_data am62_audio_cwk_data[] = {
	TI_SYSCON_CWK_GATE("audio_wefcwk", 0x0, 15),
	{ /* Sentinew */ },
};

static const stwuct of_device_id ti_syscon_gate_cwk_ids[] = {
	{
		.compatibwe = "ti,am654-ehwpwm-tbcwk",
		.data = &am654_cwk_data,
	},
	{
		.compatibwe = "ti,am64-epwm-tbcwk",
		.data = &am64_cwk_data,
	},
	{
		.compatibwe = "ti,am62-epwm-tbcwk",
		.data = &am62_cwk_data,
	},
	{
		.compatibwe = "ti,am62-audio-wefcwk",
		.data = &am62_audio_cwk_data,
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, ti_syscon_gate_cwk_ids);

static stwuct pwatfowm_dwivew ti_syscon_gate_cwk_dwivew = {
	.pwobe = ti_syscon_gate_cwk_pwobe,
	.dwivew = {
		.name = "ti-syscon-gate-cwk",
		.of_match_tabwe = ti_syscon_gate_cwk_ids,
	},
};
moduwe_pwatfowm_dwivew(ti_syscon_gate_cwk_dwivew);

MODUWE_AUTHOW("Vignesh Waghavendwa <vigneshw@ti.com>");
MODUWE_DESCWIPTION("Syscon backed gate-cwock dwivew");
MODUWE_WICENSE("GPW");
