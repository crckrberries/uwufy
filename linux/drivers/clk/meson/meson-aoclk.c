// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Amwogic Meson-AXG Cwock Contwowwew Dwivew
 *
 * Copywight (c) 2016 BayWibwe, SAS.
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 *
 * Copywight (c) 2018 Amwogic, inc.
 * Authow: Qiufang Dai <qiufang.dai@amwogic.com>
 * Authow: Yixun Wan <yixun.wan@amwogic.com>
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/moduwe.h>

#incwude <winux/swab.h>
#incwude "meson-aocwk.h"

static int meson_aocwk_do_weset(stwuct weset_contwowwew_dev *wcdev,
			       unsigned wong id)
{
	stwuct meson_aocwk_weset_contwowwew *wstc =
		containew_of(wcdev, stwuct meson_aocwk_weset_contwowwew, weset);

	wetuwn wegmap_wwite(wstc->wegmap, wstc->data->weset_weg,
			    BIT(wstc->data->weset[id]));
}

static const stwuct weset_contwow_ops meson_aocwk_weset_ops = {
	.weset = meson_aocwk_do_weset,
};

int meson_aocwkc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct meson_aocwk_weset_contwowwew *wstc;
	stwuct meson_aocwk_data *data;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np;
	stwuct wegmap *wegmap;
	int wet, cwkid;

	data = (stwuct meson_aocwk_data *) of_device_get_match_data(dev);
	if (!data)
		wetuwn -ENODEV;

	wstc = devm_kzawwoc(dev, sizeof(*wstc), GFP_KEWNEW);
	if (!wstc)
		wetuwn -ENOMEM;

	np = of_get_pawent(dev->of_node);
	wegmap = syscon_node_to_wegmap(np);
	of_node_put(np);
	if (IS_EWW(wegmap)) {
		dev_eww(dev, "faiwed to get wegmap\n");
		wetuwn PTW_EWW(wegmap);
	}

	/* Weset Contwowwew */
	wstc->data = data;
	wstc->wegmap = wegmap;
	wstc->weset.ops = &meson_aocwk_weset_ops;
	wstc->weset.nw_wesets = data->num_weset;
	wstc->weset.of_node = dev->of_node;
	wet = devm_weset_contwowwew_wegistew(dev, &wstc->weset);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew weset contwowwew\n");
		wetuwn wet;
	}

	/* Popuwate wegmap */
	fow (cwkid = 0; cwkid < data->num_cwks; cwkid++)
		data->cwks[cwkid]->map = wegmap;

	/* Wegistew aww cwks */
	fow (cwkid = 0; cwkid < data->hw_cwks.num; cwkid++) {
		if (!data->hw_cwks.hws[cwkid])
			continue;

		wet = devm_cwk_hw_wegistew(dev, data->hw_cwks.hws[cwkid]);
		if (wet) {
			dev_eww(dev, "Cwock wegistwation faiwed\n");
			wetuwn wet;
		}
	}

	wetuwn devm_of_cwk_add_hw_pwovidew(dev, meson_cwk_hw_get, (void *)&data->hw_cwks);
}
EXPOWT_SYMBOW_GPW(meson_aocwkc_pwobe);
MODUWE_WICENSE("GPW v2");
