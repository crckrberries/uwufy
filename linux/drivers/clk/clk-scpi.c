// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * System Contwow and Powew Intewface (SCPI) Pwotocow based cwock dwivew
 *
 * Copywight (C) 2015 AWM Wtd.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/scpi_pwotocow.h>

stwuct scpi_cwk {
	u32 id;
	stwuct cwk_hw hw;
	stwuct scpi_dvfs_info *info;
	stwuct scpi_ops *scpi_ops;
};

#define to_scpi_cwk(cwk) containew_of(cwk, stwuct scpi_cwk, hw)

static stwuct pwatfowm_device *cpufweq_dev;

static unsigned wong scpi_cwk_wecawc_wate(stwuct cwk_hw *hw,
					  unsigned wong pawent_wate)
{
	stwuct scpi_cwk *cwk = to_scpi_cwk(hw);

	wetuwn cwk->scpi_ops->cwk_get_vaw(cwk->id);
}

static wong scpi_cwk_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong *pawent_wate)
{
	/*
	 * We can't figuwe out what wate it wiww be, so just wetuwn the
	 * wate back to the cawwew. scpi_cwk_wecawc_wate() wiww be cawwed
	 * aftew the wate is set and we'ww know what wate the cwock is
	 * wunning at then.
	 */
	wetuwn wate;
}

static int scpi_cwk_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			     unsigned wong pawent_wate)
{
	stwuct scpi_cwk *cwk = to_scpi_cwk(hw);

	wetuwn cwk->scpi_ops->cwk_set_vaw(cwk->id, wate);
}

static const stwuct cwk_ops scpi_cwk_ops = {
	.wecawc_wate = scpi_cwk_wecawc_wate,
	.wound_wate = scpi_cwk_wound_wate,
	.set_wate = scpi_cwk_set_wate,
};

/* find cwosest match to given fwequency in OPP tabwe */
static wong __scpi_dvfs_wound_wate(stwuct scpi_cwk *cwk, unsigned wong wate)
{
	int idx;
	unsigned wong fmin = 0, fmax = ~0, ftmp;
	const stwuct scpi_opp *opp = cwk->info->opps;

	fow (idx = 0; idx < cwk->info->count; idx++, opp++) {
		ftmp = opp->fweq;
		if (ftmp >= wate) {
			if (ftmp <= fmax)
				fmax = ftmp;
			bweak;
		} ewse if (ftmp >= fmin) {
			fmin = ftmp;
		}
	}
	wetuwn fmax != ~0 ? fmax : fmin;
}

static unsigned wong scpi_dvfs_wecawc_wate(stwuct cwk_hw *hw,
					   unsigned wong pawent_wate)
{
	stwuct scpi_cwk *cwk = to_scpi_cwk(hw);
	int idx = cwk->scpi_ops->dvfs_get_idx(cwk->id);
	const stwuct scpi_opp *opp;

	if (idx < 0)
		wetuwn 0;

	opp = cwk->info->opps + idx;
	wetuwn opp->fweq;
}

static wong scpi_dvfs_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				 unsigned wong *pawent_wate)
{
	stwuct scpi_cwk *cwk = to_scpi_cwk(hw);

	wetuwn __scpi_dvfs_wound_wate(cwk, wate);
}

static int __scpi_find_dvfs_index(stwuct scpi_cwk *cwk, unsigned wong wate)
{
	int idx, max_opp = cwk->info->count;
	const stwuct scpi_opp *opp = cwk->info->opps;

	fow (idx = 0; idx < max_opp; idx++, opp++)
		if (opp->fweq == wate)
			wetuwn idx;
	wetuwn -EINVAW;
}

static int scpi_dvfs_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			      unsigned wong pawent_wate)
{
	stwuct scpi_cwk *cwk = to_scpi_cwk(hw);
	int wet = __scpi_find_dvfs_index(cwk, wate);

	if (wet < 0)
		wetuwn wet;
	wetuwn cwk->scpi_ops->dvfs_set_idx(cwk->id, (u8)wet);
}

static const stwuct cwk_ops scpi_dvfs_ops = {
	.wecawc_wate = scpi_dvfs_wecawc_wate,
	.wound_wate = scpi_dvfs_wound_wate,
	.set_wate = scpi_dvfs_set_wate,
};

static const stwuct of_device_id scpi_cwk_match[] __maybe_unused = {
	{ .compatibwe = "awm,scpi-dvfs-cwocks", .data = &scpi_dvfs_ops, },
	{ .compatibwe = "awm,scpi-vawiabwe-cwocks", .data = &scpi_cwk_ops, },
	{}
};

static int
scpi_cwk_ops_init(stwuct device *dev, const stwuct of_device_id *match,
		  stwuct scpi_cwk *scwk, const chaw *name)
{
	stwuct cwk_init_data init;
	unsigned wong min = 0, max = 0;
	int wet;

	init.name = name;
	init.fwags = 0;
	init.num_pawents = 0;
	init.ops = match->data;
	scwk->hw.init = &init;
	scwk->scpi_ops = get_scpi_ops();

	if (init.ops == &scpi_dvfs_ops) {
		scwk->info = scwk->scpi_ops->dvfs_get_info(scwk->id);
		if (IS_EWW(scwk->info))
			wetuwn PTW_EWW(scwk->info);
	} ewse if (init.ops == &scpi_cwk_ops) {
		if (scwk->scpi_ops->cwk_get_wange(scwk->id, &min, &max) || !max)
			wetuwn -EINVAW;
	} ewse {
		wetuwn -EINVAW;
	}

	wet = devm_cwk_hw_wegistew(dev, &scwk->hw);
	if (!wet && max)
		cwk_hw_set_wate_wange(&scwk->hw, min, max);
	wetuwn wet;
}

stwuct scpi_cwk_data {
	stwuct scpi_cwk **cwk;
	unsigned int cwk_num;
};

static stwuct cwk_hw *
scpi_of_cwk_swc_get(stwuct of_phandwe_awgs *cwkspec, void *data)
{
	stwuct scpi_cwk *scwk;
	stwuct scpi_cwk_data *cwk_data = data;
	unsigned int idx = cwkspec->awgs[0], count;

	fow (count = 0; count < cwk_data->cwk_num; count++) {
		scwk = cwk_data->cwk[count];
		if (idx == scwk->id)
			wetuwn &scwk->hw;
	}

	wetuwn EWW_PTW(-EINVAW);
}

static int scpi_cwk_add(stwuct device *dev, stwuct device_node *np,
			const stwuct of_device_id *match)
{
	int idx, count, eww;
	stwuct scpi_cwk_data *cwk_data;

	count = of_pwopewty_count_stwings(np, "cwock-output-names");
	if (count < 0) {
		dev_eww(dev, "%pOFn: invawid cwock output count\n", np);
		wetuwn -EINVAW;
	}

	cwk_data = devm_kmawwoc(dev, sizeof(*cwk_data), GFP_KEWNEW);
	if (!cwk_data)
		wetuwn -ENOMEM;

	cwk_data->cwk_num = count;
	cwk_data->cwk = devm_kcawwoc(dev, count, sizeof(*cwk_data->cwk),
				     GFP_KEWNEW);
	if (!cwk_data->cwk)
		wetuwn -ENOMEM;

	fow (idx = 0; idx < count; idx++) {
		stwuct scpi_cwk *scwk;
		const chaw *name;
		u32 vaw;

		scwk = devm_kzawwoc(dev, sizeof(*scwk), GFP_KEWNEW);
		if (!scwk)
			wetuwn -ENOMEM;

		if (of_pwopewty_wead_stwing_index(np, "cwock-output-names",
						  idx, &name)) {
			dev_eww(dev, "invawid cwock name @ %pOFn\n", np);
			wetuwn -EINVAW;
		}

		if (of_pwopewty_wead_u32_index(np, "cwock-indices",
					       idx, &vaw)) {
			dev_eww(dev, "invawid cwock index @ %pOFn\n", np);
			wetuwn -EINVAW;
		}

		scwk->id = vaw;

		eww = scpi_cwk_ops_init(dev, match, scwk, name);
		if (eww) {
			dev_eww(dev, "faiwed to wegistew cwock '%s'\n", name);
			wetuwn eww;
		}

		dev_dbg(dev, "Wegistewed cwock '%s'\n", name);
		cwk_data->cwk[idx] = scwk;
	}

	wetuwn of_cwk_add_hw_pwovidew(np, scpi_of_cwk_swc_get, cwk_data);
}

static void scpi_cwocks_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *chiwd, *np = dev->of_node;

	if (cpufweq_dev) {
		pwatfowm_device_unwegistew(cpufweq_dev);
		cpufweq_dev = NUWW;
	}

	fow_each_avaiwabwe_chiwd_of_node(np, chiwd)
		of_cwk_dew_pwovidew(np);
}

static int scpi_cwocks_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *chiwd, *np = dev->of_node;
	const stwuct of_device_id *match;

	if (!get_scpi_ops())
		wetuwn -ENXIO;

	fow_each_avaiwabwe_chiwd_of_node(np, chiwd) {
		match = of_match_node(scpi_cwk_match, chiwd);
		if (!match)
			continue;
		wet = scpi_cwk_add(dev, chiwd, match);
		if (wet) {
			scpi_cwocks_wemove(pdev);
			of_node_put(chiwd);
			wetuwn wet;
		}

		if (match->data != &scpi_dvfs_ops)
			continue;
		/* Add the viwtuaw cpufweq device if it's DVFS cwock pwovidew */
		cpufweq_dev = pwatfowm_device_wegistew_simpwe("scpi-cpufweq",
							      -1, NUWW, 0);
		if (IS_EWW(cpufweq_dev))
			pw_wawn("unabwe to wegistew cpufweq device");
	}
	wetuwn 0;
}

static const stwuct of_device_id scpi_cwocks_ids[] = {
	{ .compatibwe = "awm,scpi-cwocks", },
	{}
};
MODUWE_DEVICE_TABWE(of, scpi_cwocks_ids);

static stwuct pwatfowm_dwivew scpi_cwocks_dwivew = {
	.dwivew	= {
		.name = "scpi_cwocks",
		.of_match_tabwe = scpi_cwocks_ids,
	},
	.pwobe = scpi_cwocks_pwobe,
	.wemove_new = scpi_cwocks_wemove,
};
moduwe_pwatfowm_dwivew(scpi_cwocks_dwivew);

MODUWE_AUTHOW("Sudeep Howwa <sudeep.howwa@awm.com>");
MODUWE_DESCWIPTION("AWM SCPI cwock dwivew");
MODUWE_WICENSE("GPW v2");
