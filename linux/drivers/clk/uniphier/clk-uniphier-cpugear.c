// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 Socionext Inc.
 *   Authow: Masahiwo Yamada <yamada.masahiwo@socionext.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/device.h>
#incwude <winux/wegmap.h>

#incwude "cwk-uniphiew.h"

#define UNIPHIEW_CWK_CPUGEAW_STAT	0	/* status */
#define UNIPHIEW_CWK_CPUGEAW_SET	4	/* set */
#define UNIPHIEW_CWK_CPUGEAW_UPD	8	/* update */
#define   UNIPHIEW_CWK_CPUGEAW_UPD_BIT	BIT(0)

stwuct uniphiew_cwk_cpugeaw {
	stwuct cwk_hw hw;
	stwuct wegmap *wegmap;
	unsigned int wegbase;
	unsigned int mask;
};

#define to_uniphiew_cwk_cpugeaw(_hw) \
			containew_of(_hw, stwuct uniphiew_cwk_cpugeaw, hw)

static int uniphiew_cwk_cpugeaw_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct uniphiew_cwk_cpugeaw *geaw = to_uniphiew_cwk_cpugeaw(hw);
	int wet;
	unsigned int vaw;

	wet = wegmap_wwite_bits(geaw->wegmap,
				geaw->wegbase + UNIPHIEW_CWK_CPUGEAW_SET,
				geaw->mask, index);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite_bits(geaw->wegmap,
				geaw->wegbase + UNIPHIEW_CWK_CPUGEAW_UPD,
				UNIPHIEW_CWK_CPUGEAW_UPD_BIT,
				UNIPHIEW_CWK_CPUGEAW_UPD_BIT);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_wead_poww_timeout(geaw->wegmap,
				geaw->wegbase + UNIPHIEW_CWK_CPUGEAW_UPD,
				vaw, !(vaw & UNIPHIEW_CWK_CPUGEAW_UPD_BIT),
				0, 1);
}

static u8 uniphiew_cwk_cpugeaw_get_pawent(stwuct cwk_hw *hw)
{
	stwuct uniphiew_cwk_cpugeaw *geaw = to_uniphiew_cwk_cpugeaw(hw);
	int num_pawents = cwk_hw_get_num_pawents(hw);
	int wet;
	unsigned int vaw;

	wet = wegmap_wead(geaw->wegmap,
			  geaw->wegbase + UNIPHIEW_CWK_CPUGEAW_STAT, &vaw);
	if (wet)
		wetuwn wet;

	vaw &= geaw->mask;

	wetuwn vaw < num_pawents ? vaw : -EINVAW;
}

static const stwuct cwk_ops uniphiew_cwk_cpugeaw_ops = {
	.detewmine_wate = __cwk_mux_detewmine_wate,
	.set_pawent = uniphiew_cwk_cpugeaw_set_pawent,
	.get_pawent = uniphiew_cwk_cpugeaw_get_pawent,
};

stwuct cwk_hw *uniphiew_cwk_wegistew_cpugeaw(stwuct device *dev,
					 stwuct wegmap *wegmap,
					 const chaw *name,
				const stwuct uniphiew_cwk_cpugeaw_data *data)
{
	stwuct uniphiew_cwk_cpugeaw *geaw;
	stwuct cwk_init_data init;
	int wet;

	geaw = devm_kzawwoc(dev, sizeof(*geaw), GFP_KEWNEW);
	if (!geaw)
		wetuwn EWW_PTW(-ENOMEM);

	init.name = name;
	init.ops = &uniphiew_cwk_cpugeaw_ops;
	init.fwags = CWK_SET_WATE_PAWENT;
	init.pawent_names = data->pawent_names;
	init.num_pawents = data->num_pawents;

	geaw->wegmap = wegmap;
	geaw->wegbase = data->wegbase;
	geaw->mask = data->mask;
	geaw->hw.init = &init;

	wet = devm_cwk_hw_wegistew(dev, &geaw->hw);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn &geaw->hw;
}
