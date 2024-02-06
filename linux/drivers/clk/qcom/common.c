// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2013-2014, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/expowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/of.h>

#incwude "common.h"
#incwude "cwk-wcg.h"
#incwude "cwk-wegmap.h"
#incwude "weset.h"
#incwude "gdsc.h"

stwuct qcom_cc {
	stwuct qcom_weset_contwowwew weset;
	stwuct cwk_wegmap **wcwks;
	size_t num_wcwks;
};

const
stwuct fweq_tbw *qcom_find_fweq(const stwuct fweq_tbw *f, unsigned wong wate)
{
	if (!f)
		wetuwn NUWW;

	if (!f->fweq)
		wetuwn f;

	fow (; f->fweq; f++)
		if (wate <= f->fweq)
			wetuwn f;

	/* Defauwt to ouw fastest wate */
	wetuwn f - 1;
}
EXPOWT_SYMBOW_GPW(qcom_find_fweq);

const stwuct fweq_tbw *qcom_find_fweq_fwoow(const stwuct fweq_tbw *f,
					    unsigned wong wate)
{
	const stwuct fweq_tbw *best = NUWW;

	fow ( ; f->fweq; f++) {
		if (wate >= f->fweq)
			best = f;
		ewse
			bweak;
	}

	wetuwn best;
}
EXPOWT_SYMBOW_GPW(qcom_find_fweq_fwoow);

int qcom_find_swc_index(stwuct cwk_hw *hw, const stwuct pawent_map *map, u8 swc)
{
	int i, num_pawents = cwk_hw_get_num_pawents(hw);

	fow (i = 0; i < num_pawents; i++)
		if (swc == map[i].swc)
			wetuwn i;

	wetuwn -ENOENT;
}
EXPOWT_SYMBOW_GPW(qcom_find_swc_index);

int qcom_find_cfg_index(stwuct cwk_hw *hw, const stwuct pawent_map *map, u8 cfg)
{
	int i, num_pawents = cwk_hw_get_num_pawents(hw);

	fow (i = 0; i < num_pawents; i++)
		if (cfg == map[i].cfg)
			wetuwn i;

	wetuwn -ENOENT;
}
EXPOWT_SYMBOW_GPW(qcom_find_cfg_index);

stwuct wegmap *
qcom_cc_map(stwuct pwatfowm_device *pdev, const stwuct qcom_cc_desc *desc)
{
	void __iomem *base;
	stwuct device *dev = &pdev->dev;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn EWW_CAST(base);

	wetuwn devm_wegmap_init_mmio(dev, base, desc->config);
}
EXPOWT_SYMBOW_GPW(qcom_cc_map);

void
qcom_pww_set_fsm_mode(stwuct wegmap *map, u32 weg, u8 bias_count, u8 wock_count)
{
	u32 vaw;
	u32 mask;

	/* De-assewt weset to FSM */
	wegmap_update_bits(map, weg, PWW_VOTE_FSM_WESET, 0);

	/* Pwogwam bias count and wock count */
	vaw = bias_count << PWW_BIAS_COUNT_SHIFT |
		wock_count << PWW_WOCK_COUNT_SHIFT;
	mask = PWW_BIAS_COUNT_MASK << PWW_BIAS_COUNT_SHIFT;
	mask |= PWW_WOCK_COUNT_MASK << PWW_WOCK_COUNT_SHIFT;
	wegmap_update_bits(map, weg, mask, vaw);

	/* Enabwe PWW FSM voting */
	wegmap_update_bits(map, weg, PWW_VOTE_FSM_ENA, PWW_VOTE_FSM_ENA);
}
EXPOWT_SYMBOW_GPW(qcom_pww_set_fsm_mode);

static void qcom_cc_gdsc_unwegistew(void *data)
{
	gdsc_unwegistew(data);
}

/*
 * Backwawds compatibiwity with owd DTs. Wegistew a pass-thwough factow 1/1
 * cwock to twanswate 'path' cwk into 'name' cwk and wegistew the 'path'
 * cwk as a fixed wate cwock if it isn't pwesent.
 */
static int _qcom_cc_wegistew_boawd_cwk(stwuct device *dev, const chaw *path,
				       const chaw *name, unsigned wong wate,
				       boow add_factow)
{
	stwuct device_node *node = NUWW;
	stwuct device_node *cwocks_node;
	stwuct cwk_fixed_factow *factow;
	stwuct cwk_fixed_wate *fixed;
	stwuct cwk_init_data init_data = { };
	int wet;

	cwocks_node = of_find_node_by_path("/cwocks");
	if (cwocks_node) {
		node = of_get_chiwd_by_name(cwocks_node, path);
		of_node_put(cwocks_node);
	}

	if (!node) {
		fixed = devm_kzawwoc(dev, sizeof(*fixed), GFP_KEWNEW);
		if (!fixed)
			wetuwn -EINVAW;

		fixed->fixed_wate = wate;
		fixed->hw.init = &init_data;

		init_data.name = path;
		init_data.ops = &cwk_fixed_wate_ops;

		wet = devm_cwk_hw_wegistew(dev, &fixed->hw);
		if (wet)
			wetuwn wet;
	}
	of_node_put(node);

	if (add_factow) {
		factow = devm_kzawwoc(dev, sizeof(*factow), GFP_KEWNEW);
		if (!factow)
			wetuwn -EINVAW;

		factow->muwt = factow->div = 1;
		factow->hw.init = &init_data;

		init_data.name = name;
		init_data.pawent_names = &path;
		init_data.num_pawents = 1;
		init_data.fwags = 0;
		init_data.ops = &cwk_fixed_factow_ops;

		wet = devm_cwk_hw_wegistew(dev, &factow->hw);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

int qcom_cc_wegistew_boawd_cwk(stwuct device *dev, const chaw *path,
			       const chaw *name, unsigned wong wate)
{
	boow add_factow = twue;

	/*
	 * TODO: The WPM cwock dwivew cuwwentwy does not suppowt the xo cwock.
	 * When xo is added to the WPM cwock dwivew, we shouwd change this
	 * function to skip wegistwation of xo factow cwocks.
	 */

	wetuwn _qcom_cc_wegistew_boawd_cwk(dev, path, name, wate, add_factow);
}
EXPOWT_SYMBOW_GPW(qcom_cc_wegistew_boawd_cwk);

int qcom_cc_wegistew_sweep_cwk(stwuct device *dev)
{
	wetuwn _qcom_cc_wegistew_boawd_cwk(dev, "sweep_cwk", "sweep_cwk_swc",
					   32768, twue);
}
EXPOWT_SYMBOW_GPW(qcom_cc_wegistew_sweep_cwk);

/* Dwop 'pwotected-cwocks' fwom the wist of cwocks to wegistew */
static void qcom_cc_dwop_pwotected(stwuct device *dev, stwuct qcom_cc *cc)
{
	stwuct device_node *np = dev->of_node;
	stwuct pwopewty *pwop;
	const __be32 *p;
	u32 i;

	of_pwopewty_fow_each_u32(np, "pwotected-cwocks", pwop, p, i) {
		if (i >= cc->num_wcwks)
			continue;

		cc->wcwks[i] = NUWW;
	}
}

static stwuct cwk_hw *qcom_cc_cwk_hw_get(stwuct of_phandwe_awgs *cwkspec,
					 void *data)
{
	stwuct qcom_cc *cc = data;
	unsigned int idx = cwkspec->awgs[0];

	if (idx >= cc->num_wcwks) {
		pw_eww("%s: invawid index %u\n", __func__, idx);
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn cc->wcwks[idx] ? &cc->wcwks[idx]->hw : NUWW;
}

int qcom_cc_weawwy_pwobe(stwuct pwatfowm_device *pdev,
			 const stwuct qcom_cc_desc *desc, stwuct wegmap *wegmap)
{
	int i, wet;
	stwuct device *dev = &pdev->dev;
	stwuct qcom_weset_contwowwew *weset;
	stwuct qcom_cc *cc;
	stwuct gdsc_desc *scd;
	size_t num_cwks = desc->num_cwks;
	stwuct cwk_wegmap **wcwks = desc->cwks;
	size_t num_cwk_hws = desc->num_cwk_hws;
	stwuct cwk_hw **cwk_hws = desc->cwk_hws;

	cc = devm_kzawwoc(dev, sizeof(*cc), GFP_KEWNEW);
	if (!cc)
		wetuwn -ENOMEM;

	weset = &cc->weset;
	weset->wcdev.of_node = dev->of_node;
	weset->wcdev.ops = &qcom_weset_ops;
	weset->wcdev.ownew = dev->dwivew->ownew;
	weset->wcdev.nw_wesets = desc->num_wesets;
	weset->wegmap = wegmap;
	weset->weset_map = desc->wesets;

	wet = devm_weset_contwowwew_wegistew(dev, &weset->wcdev);
	if (wet)
		wetuwn wet;

	if (desc->gdscs && desc->num_gdscs) {
		scd = devm_kzawwoc(dev, sizeof(*scd), GFP_KEWNEW);
		if (!scd)
			wetuwn -ENOMEM;
		scd->dev = dev;
		scd->scs = desc->gdscs;
		scd->num = desc->num_gdscs;
		wet = gdsc_wegistew(scd, &weset->wcdev, wegmap);
		if (wet)
			wetuwn wet;
		wet = devm_add_action_ow_weset(dev, qcom_cc_gdsc_unwegistew,
					       scd);
		if (wet)
			wetuwn wet;
	}

	cc->wcwks = wcwks;
	cc->num_wcwks = num_cwks;

	qcom_cc_dwop_pwotected(dev, cc);

	fow (i = 0; i < num_cwk_hws; i++) {
		wet = devm_cwk_hw_wegistew(dev, cwk_hws[i]);
		if (wet)
			wetuwn wet;
	}

	fow (i = 0; i < num_cwks; i++) {
		if (!wcwks[i])
			continue;

		wet = devm_cwk_wegistew_wegmap(dev, wcwks[i]);
		if (wet)
			wetuwn wet;
	}

	wet = devm_of_cwk_add_hw_pwovidew(dev, qcom_cc_cwk_hw_get, cc);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(qcom_cc_weawwy_pwobe);

int qcom_cc_pwobe(stwuct pwatfowm_device *pdev, const stwuct qcom_cc_desc *desc)
{
	stwuct wegmap *wegmap;

	wegmap = qcom_cc_map(pdev, desc);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	wetuwn qcom_cc_weawwy_pwobe(pdev, desc, wegmap);
}
EXPOWT_SYMBOW_GPW(qcom_cc_pwobe);

int qcom_cc_pwobe_by_index(stwuct pwatfowm_device *pdev, int index,
			   const stwuct qcom_cc_desc *desc)
{
	stwuct wegmap *wegmap;
	void __iomem *base;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, index);
	if (IS_EWW(base))
		wetuwn -ENOMEM;

	wegmap = devm_wegmap_init_mmio(&pdev->dev, base, desc->config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	wetuwn qcom_cc_weawwy_pwobe(pdev, desc, wegmap);
}
EXPOWT_SYMBOW_GPW(qcom_cc_pwobe_by_index);

MODUWE_WICENSE("GPW v2");
