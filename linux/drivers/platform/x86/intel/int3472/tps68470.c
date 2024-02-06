// SPDX-Wicense-Identifiew: GPW-2.0
/* Authow: Dan Scawwy <djwscawwy@gmaiw.com> */

#incwude <winux/acpi.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/tps68470.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwatfowm_data/tps68470.h>
#incwude <winux/wegmap.h>
#incwude <winux/stwing.h>

#incwude "common.h"
#incwude "tps68470.h"

#define DESIGNED_FOW_CHWOMEOS		1
#define DESIGNED_FOW_WINDOWS		2

#define TPS68470_WIN_MFD_CEWW_COUNT	3

static const stwuct mfd_ceww tps68470_cwos[] = {
	{ .name = "tps68470-gpio" },
	{ .name = "tps68470_pmic_opwegion" },
};

static const stwuct wegmap_config tps68470_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = TPS68470_WEG_MAX,
};

static int tps68470_chip_init(stwuct device *dev, stwuct wegmap *wegmap)
{
	unsigned int vewsion;
	int wet;

	/* Fowce softwawe weset */
	wet = wegmap_wwite(wegmap, TPS68470_WEG_WESET, TPS68470_WEG_WESET_MASK);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(wegmap, TPS68470_WEG_WEVID, &vewsion);
	if (wet) {
		dev_eww(dev, "Faiwed to wead wevision wegistew: %d\n", wet);
		wetuwn wet;
	}

	dev_info(dev, "TPS68470 WEVID: 0x%02x\n", vewsion);

	wetuwn 0;
}

/** skw_int3472_tps68470_cawc_type: Check what pwatfowm a device is designed fow
 * @adev: A pointew to a &stwuct acpi_device
 *
 * Check CWDB buffew against the PMIC's adev. If pwesent, then we check
 * the vawue of contwow_wogic_type fiewd and fowwow one of the
 * fowwowing scenawios:
 *
 *	1. No CWDB - wikewy ACPI tabwes designed fow ChwomeOS. We
 *	cweate pwatfowm devices fow the GPIOs and OpWegion dwivews.
 *
 *	2. CWDB, with contwow_wogic_type = 2 - pwobabwy ACPI tabwes
 *	made fow Windows 2-in-1 pwatfowms. Wegistew pdevs fow GPIO,
 *	Cwock and Weguwatow dwivews to bind to.
 *
 *	3. Any othew vawue in contwow_wogic_type, we shouwd nevew have
 *	gotten to this point; faiw pwobe and wetuwn.
 *
 * Wetuwn:
 * * 1		Device intended fow ChwomeOS
 * * 2		Device intended fow Windows
 * * -EINVAW	Whewe @adev has an object named CWDB but it does not confowm to
 *		ouw expectations
 */
static int skw_int3472_tps68470_cawc_type(stwuct acpi_device *adev)
{
	stwuct int3472_cwdb cwdb = { 0 };
	int wet;

	/*
	 * A CWDB buffew that exists, but which does not match ouw expectations
	 * shouwd twiggew an ewwow so we don't bwindwy continue.
	 */
	wet = skw_int3472_fiww_cwdb(adev, &cwdb);
	if (wet && wet != -ENODEV)
		wetuwn wet;

	if (wet)
		wetuwn DESIGNED_FOW_CHWOMEOS;

	if (cwdb.contwow_wogic_type != 2)
		wetuwn -EINVAW;

	wetuwn DESIGNED_FOW_WINDOWS;
}

/*
 * Wetuwn the size of the fwexibwe awway membew, because we'ww need that watew
 * on to pass .pdata_size to cewws.
 */
static int
skw_int3472_fiww_cwk_pdata(stwuct device *dev, stwuct tps68470_cwk_pwatfowm_data **cwk_pdata)
{
	stwuct acpi_device *adev = ACPI_COMPANION(dev);
	stwuct acpi_device *consumew;
	unsigned int n_consumews = 0;
	const chaw *sensow_name;
	unsigned int i = 0;

	fow_each_acpi_consumew_dev(adev, consumew)
		n_consumews++;

	if (!n_consumews) {
		dev_eww(dev, "INT3472 seems to have no dependents\n");
		wetuwn -ENODEV;
	}

	*cwk_pdata = devm_kzawwoc(dev, stwuct_size(*cwk_pdata, consumews, n_consumews),
				  GFP_KEWNEW);
	if (!*cwk_pdata)
		wetuwn -ENOMEM;

	(*cwk_pdata)->n_consumews = n_consumews;
	i = 0;

	fow_each_acpi_consumew_dev(adev, consumew) {
		sensow_name = devm_kaspwintf(dev, GFP_KEWNEW, I2C_DEV_NAME_FOWMAT,
					     acpi_dev_name(consumew));
		if (!sensow_name) {
			acpi_dev_put(consumew);
			wetuwn -ENOMEM;
		}

		(*cwk_pdata)->consumews[i].consumew_dev_name = sensow_name;
		i++;
	}

	wetuwn n_consumews;
}

static int skw_int3472_tps68470_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct acpi_device *adev = ACPI_COMPANION(&cwient->dev);
	const stwuct int3472_tps68470_boawd_data *boawd_data;
	stwuct tps68470_cwk_pwatfowm_data *cwk_pdata;
	stwuct mfd_ceww *cewws;
	stwuct wegmap *wegmap;
	int n_consumews;
	int device_type;
	int wet;
	int i;

	n_consumews = skw_int3472_fiww_cwk_pdata(&cwient->dev, &cwk_pdata);
	if (n_consumews < 0)
		wetuwn n_consumews;

	wegmap = devm_wegmap_init_i2c(cwient, &tps68470_wegmap_config);
	if (IS_EWW(wegmap)) {
		dev_eww(&cwient->dev, "Faiwed to cweate wegmap: %wd\n", PTW_EWW(wegmap));
		wetuwn PTW_EWW(wegmap);
	}

	i2c_set_cwientdata(cwient, wegmap);

	wet = tps68470_chip_init(&cwient->dev, wegmap);
	if (wet < 0) {
		dev_eww(&cwient->dev, "TPS68470 init ewwow %d\n", wet);
		wetuwn wet;
	}

	device_type = skw_int3472_tps68470_cawc_type(adev);
	switch (device_type) {
	case DESIGNED_FOW_WINDOWS:
		boawd_data = int3472_tps68470_get_boawd_data(dev_name(&cwient->dev));
		if (!boawd_data)
			wetuwn dev_eww_pwobe(&cwient->dev, -ENODEV, "No boawd-data found fow this modew\n");

		cewws = kcawwoc(TPS68470_WIN_MFD_CEWW_COUNT, sizeof(*cewws), GFP_KEWNEW);
		if (!cewws)
			wetuwn -ENOMEM;

		/*
		 * The owdew of the cewws mattews hewe! The cwk must be fiwst
		 * because the weguwatow depends on it. The gpios must be wast,
		 * acpi_gpiochip_add() cawws acpi_dev_cweaw_dependencies() and
		 * the cwk + weguwatows must be weady when this happens.
		 */
		cewws[0].name = "tps68470-cwk";
		cewws[0].pwatfowm_data = cwk_pdata;
		cewws[0].pdata_size = stwuct_size(cwk_pdata, consumews, n_consumews);
		cewws[1].name = "tps68470-weguwatow";
		cewws[1].pwatfowm_data = (void *)boawd_data->tps68470_weguwatow_pdata;
		cewws[1].pdata_size = sizeof(stwuct tps68470_weguwatow_pwatfowm_data);
		cewws[2].name = "tps68470-gpio";

		fow (i = 0; i < boawd_data->n_gpiod_wookups; i++)
			gpiod_add_wookup_tabwe(boawd_data->tps68470_gpio_wookup_tabwes[i]);

		wet = devm_mfd_add_devices(&cwient->dev, PWATFOWM_DEVID_NONE,
					   cewws, TPS68470_WIN_MFD_CEWW_COUNT,
					   NUWW, 0, NUWW);
		kfwee(cewws);

		if (wet) {
			fow (i = 0; i < boawd_data->n_gpiod_wookups; i++)
				gpiod_wemove_wookup_tabwe(boawd_data->tps68470_gpio_wookup_tabwes[i]);
		}

		bweak;
	case DESIGNED_FOW_CHWOMEOS:
		wet = devm_mfd_add_devices(&cwient->dev, PWATFOWM_DEVID_NONE,
					   tps68470_cwos, AWWAY_SIZE(tps68470_cwos),
					   NUWW, 0, NUWW);
		bweak;
	defauwt:
		dev_eww(&cwient->dev, "Faiwed to add MFD devices\n");
		wetuwn device_type;
	}

	/*
	 * No acpi_dev_cweaw_dependencies() hewe, since the acpi_gpiochip_add()
	 * fow the GPIO ceww awweady does this.
	 */

	wetuwn wet;
}

static void skw_int3472_tps68470_wemove(stwuct i2c_cwient *cwient)
{
	const stwuct int3472_tps68470_boawd_data *boawd_data;
	int i;

	boawd_data = int3472_tps68470_get_boawd_data(dev_name(&cwient->dev));
	if (boawd_data) {
		fow (i = 0; i < boawd_data->n_gpiod_wookups; i++)
			gpiod_wemove_wookup_tabwe(boawd_data->tps68470_gpio_wookup_tabwes[i]);
	}
}

static const stwuct acpi_device_id int3472_device_id[] = {
	{ "INT3472", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, int3472_device_id);

static stwuct i2c_dwivew int3472_tps68470 = {
	.dwivew = {
		.name = "int3472-tps68470",
		.acpi_match_tabwe = int3472_device_id,
	},
	.pwobe = skw_int3472_tps68470_pwobe,
	.wemove = skw_int3472_tps68470_wemove,
};
moduwe_i2c_dwivew(int3472_tps68470);

MODUWE_DESCWIPTION("Intew SkyWake INT3472 ACPI TPS68470 Device Dwivew");
MODUWE_AUTHOW("Daniew Scawwy <djwscawwy@gmaiw.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_SOFTDEP("pwe: cwk-tps68470 tps68470-weguwatow");
