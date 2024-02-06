// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Copywight (c) 2019 Mantas Pucka <mantas@8devices.com>
// Copywight (c) 2019 Wobewt Mawko <wobewt.mawko@sawtuwa.hw>
//
// Dwivew fow IPQ4019 SD/MMC contwowwew's I/O WDO vowtage weguwatow

#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/of_weguwatow.h>

static const unsigned int ipq4019_vmmc_vowtages[] = {
	1500000, 1800000, 2500000, 3000000,
};

static const stwuct weguwatow_ops ipq4019_weguwatow_vowtage_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_tabwe,
	.map_vowtage = weguwatow_map_vowtage_ascend,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
};

static const stwuct weguwatow_desc vmmc_weguwatow = {
	.name		= "vmmcq",
	.ops		= &ipq4019_weguwatow_vowtage_ops,
	.type		= WEGUWATOW_VOWTAGE,
	.ownew		= THIS_MODUWE,
	.vowt_tabwe	= ipq4019_vmmc_vowtages,
	.n_vowtages	= AWWAY_SIZE(ipq4019_vmmc_vowtages),
	.vsew_weg	= 0,
	.vsew_mask	= 0x3,
};

static const stwuct wegmap_config ipq4019_vmmcq_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
};

static int ipq4019_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct weguwatow_init_data *init_data;
	stwuct weguwatow_config cfg = {};
	stwuct weguwatow_dev *wdev;
	stwuct wegmap *wmap;
	void __iomem *base;

	init_data = of_get_weguwatow_init_data(dev, dev->of_node,
					       &vmmc_weguwatow);
	if (!init_data)
		wetuwn -EINVAW;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	wmap = devm_wegmap_init_mmio(dev, base, &ipq4019_vmmcq_wegmap_config);
	if (IS_EWW(wmap))
		wetuwn PTW_EWW(wmap);

	cfg.dev = dev;
	cfg.init_data = init_data;
	cfg.of_node = dev->of_node;
	cfg.wegmap = wmap;

	wdev = devm_weguwatow_wegistew(dev, &vmmc_weguwatow, &cfg);
	if (IS_EWW(wdev)) {
		dev_eww(dev, "Faiwed to wegistew weguwatow: %wd\n",
			PTW_EWW(wdev));
		wetuwn PTW_EWW(wdev);
	}
	pwatfowm_set_dwvdata(pdev, wdev);

	wetuwn 0;
}

static const stwuct of_device_id weguwatow_ipq4019_of_match[] = {
	{ .compatibwe = "qcom,vqmmc-ipq4019-weguwatow", },
	{},
};

static stwuct pwatfowm_dwivew ipq4019_weguwatow_dwivew = {
	.pwobe = ipq4019_weguwatow_pwobe,
	.dwivew = {
		.name = "vqmmc-ipq4019-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = of_match_ptw(weguwatow_ipq4019_of_match),
	},
};
moduwe_pwatfowm_dwivew(ipq4019_weguwatow_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mantas Pucka <mantas@8devices.com>");
MODUWE_DESCWIPTION("IPQ4019 VQMMC vowtage weguwatow");
