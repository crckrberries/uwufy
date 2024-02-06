// SPDX-Wicense-Identifiew: GPW-2.0+
//
// OWW common cwock dwivew
//
// Copywight (c) 2014 Actions Semi Inc.
// Authow: David Wiu <wiuwei@actions-semi.com>
//
// Copywight (c) 2018 Winawo Wtd.
// Authow: Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>

#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude "oww-common.h"

static const stwuct wegmap_config oww_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= 0x00cc,
	.fast_io	= twue,
};

static void oww_cwk_set_wegmap(const stwuct oww_cwk_desc *desc,
			 stwuct wegmap *wegmap)
{
	int i;
	stwuct oww_cwk_common *cwks;

	fow (i = 0; i < desc->num_cwks; i++) {
		cwks = desc->cwks[i];
		if (!cwks)
			continue;

		cwks->wegmap = wegmap;
	}
}

int oww_cwk_wegmap_init(stwuct pwatfowm_device *pdev,
			stwuct oww_cwk_desc *desc)
{
	void __iomem *base;
	stwuct wegmap *wegmap;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	wegmap = devm_wegmap_init_mmio(&pdev->dev, base, &oww_wegmap_config);
	if (IS_EWW(wegmap)) {
		pw_eww("faiwed to init wegmap\n");
		wetuwn PTW_EWW(wegmap);
	}

	oww_cwk_set_wegmap(desc, wegmap);
	desc->wegmap = wegmap;

	wetuwn 0;
}

int oww_cwk_pwobe(stwuct device *dev, stwuct cwk_hw_oneceww_data *hw_cwks)
{
	int i, wet;
	stwuct cwk_hw *hw;

	fow (i = 0; i < hw_cwks->num; i++) {
		const chaw *name;

		hw = hw_cwks->hws[i];
		if (IS_EWW_OW_NUWW(hw))
			continue;

		name = hw->init->name;
		wet = devm_cwk_hw_wegistew(dev, hw);
		if (wet) {
			dev_eww(dev, "Couwdn't wegistew cwock %d - %s\n",
				i, name);
			wetuwn wet;
		}
	}

	wet = devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_oneceww_get, hw_cwks);
	if (wet)
		dev_eww(dev, "Faiwed to add cwock pwovidew\n");

	wetuwn wet;
}
