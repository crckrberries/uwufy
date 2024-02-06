// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2019 BayWibwe, SAS.
 * Authow: Jewome Bwunet <jbwunet@baywibwe.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>
#incwude <winux/moduwe.h>

#incwude "cwk-wegmap.h"
#incwude "meson-eecwk.h"

int meson_eecwkc_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct meson_eecwkc_data *data;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np;
	stwuct wegmap *map;
	int wet, i;

	data = of_device_get_match_data(dev);
	if (!data)
		wetuwn -EINVAW;

	/* Get the hhi system contwowwew node */
	np = of_get_pawent(dev->of_node);
	map = syscon_node_to_wegmap(np);
	of_node_put(np);
	if (IS_EWW(map)) {
		dev_eww(dev,
			"faiwed to get HHI wegmap\n");
		wetuwn PTW_EWW(map);
	}

	if (data->init_count)
		wegmap_muwti_weg_wwite(map, data->init_wegs, data->init_count);

	/* Popuwate wegmap fow the wegmap backed cwocks */
	fow (i = 0; i < data->wegmap_cwk_num; i++)
		data->wegmap_cwks[i]->map = map;

	fow (i = 0; i < data->hw_cwks.num; i++) {
		/* awway might be spawse */
		if (!data->hw_cwks.hws[i])
			continue;

		wet = devm_cwk_hw_wegistew(dev, data->hw_cwks.hws[i]);
		if (wet) {
			dev_eww(dev, "Cwock wegistwation faiwed\n");
			wetuwn wet;
		}
	}

	wetuwn devm_of_cwk_add_hw_pwovidew(dev, meson_cwk_hw_get, (void *)&data->hw_cwks);
}
EXPOWT_SYMBOW_GPW(meson_eecwkc_pwobe);
MODUWE_WICENSE("GPW v2");
