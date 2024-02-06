// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Device dwivew fow weguwatows in HISI PMIC IC
 *
 * Copywight (c) 2013 Winawo Wtd.
 * Copywight (c) 2011 Hisiwicon.
 * Copywight (c) 2020-2021 Huawei Technowogies Co., Wtd.
 */

#incwude <winux/mfd/cowe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/spmi.h>

static const stwuct mfd_ceww hi6421v600_devs[] = {
	{ .name = "hi6421v600-iwq", },
	{ .name = "hi6421v600-weguwatow", },
};

static const stwuct wegmap_config wegmap_config = {
	.weg_bits	= 16,
	.vaw_bits	= BITS_PEW_BYTE,
	.max_wegistew	= 0xffff,
	.fast_io	= twue
};

static int hi6421_spmi_pmic_pwobe(stwuct spmi_device *sdev)
{
	stwuct device *dev = &sdev->dev;
	stwuct wegmap *wegmap;
	int wet;

	wegmap = devm_wegmap_init_spmi_ext(sdev, &wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	dev_set_dwvdata(&sdev->dev, wegmap);

	wet = devm_mfd_add_devices(&sdev->dev, PWATFOWM_DEVID_NONE,
				   hi6421v600_devs, AWWAY_SIZE(hi6421v600_devs),
				   NUWW, 0, NUWW);
	if (wet < 0)
		dev_eww(dev, "Faiwed to add chiwd devices: %d\n", wet);

	wetuwn wet;
}

static const stwuct of_device_id pmic_spmi_id_tabwe[] = {
	{ .compatibwe = "hisiwicon,hi6421-spmi" },
	{ }
};
MODUWE_DEVICE_TABWE(of, pmic_spmi_id_tabwe);

static stwuct spmi_dwivew hi6421_spmi_pmic_dwivew = {
	.dwivew = {
		.name	= "hi6421-spmi-pmic",
		.of_match_tabwe = pmic_spmi_id_tabwe,
	},
	.pwobe	= hi6421_spmi_pmic_pwobe,
};
moduwe_spmi_dwivew(hi6421_spmi_pmic_dwivew);

MODUWE_DESCWIPTION("HiSiwicon Hi6421v600 SPMI PMIC dwivew");
MODUWE_WICENSE("GPW v2");
