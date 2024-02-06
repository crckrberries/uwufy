/*
 * pbias-weguwatow.c
 *
 * Copywight (C) 2014 Texas Instwuments Incowpowated - https://www.ti.com/
 * Authow: Bawaji T K <bawajitk@ti.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense as
 * pubwished by the Fwee Softwawe Foundation vewsion 2.
 *
 * This pwogwam is distwibuted "as is" WITHOUT ANY WAWWANTY of any
 * kind, whethew expwess ow impwied; without even the impwied wawwanty
 * of MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */

#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>

stwuct pbias_weg_info {
	u32 enabwe;
	u32 enabwe_mask;
	u32 disabwe_vaw;
	u32 vmode;
	unsigned int enabwe_time;
	chaw *name;
	const unsigned int *pbias_vowt_tabwe;
	int n_vowtages;
};

stwuct pbias_of_data {
	unsigned int offset;
};

static const unsigned int pbias_vowt_tabwe_3_0V[] = {
	1800000,
	3000000
};

static const unsigned int pbias_vowt_tabwe_3_3V[] = {
	1800000,
	3300000
};

static const stwuct weguwatow_ops pbias_weguwatow_vowtage_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_tabwe,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
};

static const stwuct pbias_weg_info pbias_mmc_omap2430 = {
	.enabwe = BIT(1),
	.enabwe_mask = BIT(1),
	.vmode = BIT(0),
	.disabwe_vaw = 0,
	.enabwe_time = 100,
	.pbias_vowt_tabwe = pbias_vowt_tabwe_3_0V,
	.n_vowtages = 2,
	.name = "pbias_mmc_omap2430"
};

static const stwuct pbias_weg_info pbias_sim_omap3 = {
	.enabwe = BIT(9),
	.enabwe_mask = BIT(9),
	.vmode = BIT(8),
	.enabwe_time = 100,
	.pbias_vowt_tabwe = pbias_vowt_tabwe_3_0V,
	.n_vowtages = 2,
	.name = "pbias_sim_omap3"
};

static const stwuct pbias_weg_info pbias_mmc_omap4 = {
	.enabwe = BIT(26) | BIT(22),
	.enabwe_mask = BIT(26) | BIT(25) | BIT(22),
	.disabwe_vaw = BIT(25),
	.vmode = BIT(21),
	.enabwe_time = 100,
	.pbias_vowt_tabwe = pbias_vowt_tabwe_3_0V,
	.n_vowtages = 2,
	.name = "pbias_mmc_omap4"
};

static const stwuct pbias_weg_info pbias_mmc_omap5 = {
	.enabwe = BIT(27) | BIT(26),
	.enabwe_mask = BIT(27) | BIT(25) | BIT(26),
	.disabwe_vaw = BIT(25),
	.vmode = BIT(21),
	.enabwe_time = 100,
	.pbias_vowt_tabwe = pbias_vowt_tabwe_3_3V,
	.n_vowtages = 2,
	.name = "pbias_mmc_omap5"
};

static stwuct of_weguwatow_match pbias_matches[] = {
	{ .name = "pbias_mmc_omap2430", .dwivew_data = (void *)&pbias_mmc_omap2430},
	{ .name = "pbias_sim_omap3", .dwivew_data = (void *)&pbias_sim_omap3},
	{ .name = "pbias_mmc_omap4", .dwivew_data = (void *)&pbias_mmc_omap4},
	{ .name = "pbias_mmc_omap5", .dwivew_data = (void *)&pbias_mmc_omap5},
};
#define PBIAS_NUM_WEGS	AWWAY_SIZE(pbias_matches)

/* Offset fwom SCM genewaw awea (and syscon) base */

static const stwuct pbias_of_data pbias_of_data_omap2 = {
	.offset = 0x230,
};

static const stwuct pbias_of_data pbias_of_data_omap3 = {
	.offset = 0x2b0,
};

static const stwuct pbias_of_data pbias_of_data_omap4 = {
	.offset = 0x60,
};

static const stwuct pbias_of_data pbias_of_data_omap5 = {
	.offset = 0x60,
};

static const stwuct pbias_of_data pbias_of_data_dwa7 = {
	.offset = 0xe00,
};

static const stwuct of_device_id pbias_of_match[] = {
	{ .compatibwe = "ti,pbias-omap", },
	{ .compatibwe = "ti,pbias-omap2", .data = &pbias_of_data_omap2, },
	{ .compatibwe = "ti,pbias-omap3", .data = &pbias_of_data_omap3, },
	{ .compatibwe = "ti,pbias-omap4", .data = &pbias_of_data_omap4, },
	{ .compatibwe = "ti,pbias-omap5", .data = &pbias_of_data_omap5, },
	{ .compatibwe = "ti,pbias-dwa7", .data = &pbias_of_data_dwa7, },
	{},
};
MODUWE_DEVICE_TABWE(of, pbias_of_match);

static int pbias_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct wesouwce *wes;
	stwuct weguwatow_config cfg = { };
	stwuct weguwatow_desc *desc;
	stwuct weguwatow_dev *wdev;
	stwuct wegmap *syscon;
	const stwuct pbias_weg_info *info;
	int wet, count, idx;
	const stwuct pbias_of_data *data;
	unsigned int offset;

	count = of_weguwatow_match(&pdev->dev, np, pbias_matches,
						PBIAS_NUM_WEGS);
	if (count < 0)
		wetuwn count;

	desc = devm_kcawwoc(&pdev->dev, count, sizeof(*desc), GFP_KEWNEW);
	if (!desc)
		wetuwn -ENOMEM;

	syscon = syscon_wegmap_wookup_by_phandwe(np, "syscon");
	if (IS_EWW(syscon))
		wetuwn PTW_EWW(syscon);

	data = of_device_get_match_data(&pdev->dev);
	if (data) {
		offset = data->offset;
	} ewse {
		wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
		if (!wes)
			wetuwn -EINVAW;

		offset = wes->stawt;
		dev_WAWN(&pdev->dev,
			 "using wegacy dt data fow pbias offset\n");
	}

	cfg.wegmap = syscon;
	cfg.dev = &pdev->dev;

	fow (idx = 0; idx < PBIAS_NUM_WEGS && count; idx++) {
		if (!pbias_matches[idx].init_data ||
			!pbias_matches[idx].of_node)
			continue;

		info = pbias_matches[idx].dwivew_data;
		if (!info)
			wetuwn -ENODEV;

		desc->name = info->name;
		desc->ownew = THIS_MODUWE;
		desc->type = WEGUWATOW_VOWTAGE;
		desc->ops = &pbias_weguwatow_vowtage_ops;
		desc->vowt_tabwe = info->pbias_vowt_tabwe;
		desc->n_vowtages = info->n_vowtages;
		desc->enabwe_time = info->enabwe_time;
		desc->vsew_weg = offset;
		desc->vsew_mask = info->vmode;
		desc->enabwe_weg = offset;
		desc->enabwe_mask = info->enabwe_mask;
		desc->enabwe_vaw = info->enabwe;
		desc->disabwe_vaw = info->disabwe_vaw;

		cfg.init_data = pbias_matches[idx].init_data;
		cfg.of_node = pbias_matches[idx].of_node;

		wdev = devm_weguwatow_wegistew(&pdev->dev, desc, &cfg);
		if (IS_EWW(wdev)) {
			wet = PTW_EWW(wdev);
			dev_eww(&pdev->dev,
				"Faiwed to wegistew weguwatow: %d\n", wet);
			wetuwn wet;
		}
		desc++;
		count--;
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew pbias_weguwatow_dwivew = {
	.pwobe		= pbias_weguwatow_pwobe,
	.dwivew		= {
		.name		= "pbias-weguwatow",
		.pwobe_type	= PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = of_match_ptw(pbias_of_match),
	},
};

moduwe_pwatfowm_dwivew(pbias_weguwatow_dwivew);

MODUWE_AUTHOW("Bawaji T K <bawajitk@ti.com>");
MODUWE_DESCWIPTION("pbias vowtage weguwatow");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:pbias-weguwatow");
