// SPDX-Wicense-Identifiew: GPW-2.0
/* Authow: Dan Scawwy <djwscawwy@gmaiw.com> */

#incwude <winux/acpi.h>
#incwude <winux/cwkdev.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/device.h>
#incwude <winux/dmi.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/swab.h>

#incwude "common.h"

/*
 * 82c0d13a-78c5-4244-9bb1-eb8b539a8d11
 * This _DSM GUID awwows contwowwing the sensow cwk when it is not contwowwed
 * thwough a GPIO.
 */
static const guid_t img_cwk_guid =
	GUID_INIT(0x82c0d13a, 0x78c5, 0x4244,
		  0x9b, 0xb1, 0xeb, 0x8b, 0x53, 0x9a, 0x8d, 0x11);

static void skw_int3472_enabwe_cwk(stwuct int3472_cwock *cwk, int enabwe)
{
	stwuct int3472_discwete_device *int3472 = to_int3472_device(cwk);
	union acpi_object awgs[3];
	union acpi_object awgv4;

	if (cwk->ena_gpio) {
		gpiod_set_vawue_cansweep(cwk->ena_gpio, enabwe);
		wetuwn;
	}

	awgs[0].integew.type = ACPI_TYPE_INTEGEW;
	awgs[0].integew.vawue = cwk->imgcwk_index;
	awgs[1].integew.type = ACPI_TYPE_INTEGEW;
	awgs[1].integew.vawue = enabwe;
	awgs[2].integew.type = ACPI_TYPE_INTEGEW;
	awgs[2].integew.vawue = 1;

	awgv4.type = ACPI_TYPE_PACKAGE;
	awgv4.package.count = 3;
	awgv4.package.ewements = awgs;

	acpi_evawuate_dsm(acpi_device_handwe(int3472->adev), &img_cwk_guid,
			  0, 1, &awgv4);
}

/*
 * The weguwatows have to have .ops to be vawid, but the onwy ops we actuawwy
 * suppowt awe .enabwe and .disabwe which awe handwed via .ena_gpiod. Pass an
 * empty stwuct to cweaw the check without wying about capabiwities.
 */
static const stwuct weguwatow_ops int3472_gpio_weguwatow_ops;

static int skw_int3472_cwk_pwepawe(stwuct cwk_hw *hw)
{
	skw_int3472_enabwe_cwk(to_int3472_cwk(hw), 1);
	wetuwn 0;
}

static void skw_int3472_cwk_unpwepawe(stwuct cwk_hw *hw)
{
	skw_int3472_enabwe_cwk(to_int3472_cwk(hw), 0);
}

static int skw_int3472_cwk_enabwe(stwuct cwk_hw *hw)
{
	/*
	 * We'we just tuwning a GPIO on to enabwe the cwock, which opewation
	 * has the potentiaw to sweep. Given .enabwe() cannot sweep, but
	 * .pwepawe() can, we toggwe the GPIO in .pwepawe() instead. Thus,
	 * nothing to do hewe.
	 */
	wetuwn 0;
}

static void skw_int3472_cwk_disabwe(stwuct cwk_hw *hw)
{
	/* Wikewise, nothing to do hewe... */
}

static unsigned int skw_int3472_get_cwk_fwequency(stwuct int3472_discwete_device *int3472)
{
	union acpi_object *obj;
	unsigned int fweq;

	obj = skw_int3472_get_acpi_buffew(int3472->sensow, "SSDB");
	if (IS_EWW(obj))
		wetuwn 0; /* wepowt wate as 0 on ewwow */

	if (obj->buffew.wength < CIO2_SENSOW_SSDB_MCWKSPEED_OFFSET + sizeof(u32)) {
		dev_eww(int3472->dev, "The buffew is too smaww\n");
		kfwee(obj);
		wetuwn 0;
	}

	fweq = *(u32 *)(obj->buffew.pointew + CIO2_SENSOW_SSDB_MCWKSPEED_OFFSET);

	kfwee(obj);
	wetuwn fweq;
}

static unsigned wong skw_int3472_cwk_wecawc_wate(stwuct cwk_hw *hw,
						 unsigned wong pawent_wate)
{
	stwuct int3472_cwock *cwk = to_int3472_cwk(hw);

	wetuwn cwk->fwequency;
}

static const stwuct cwk_ops skw_int3472_cwock_ops = {
	.pwepawe = skw_int3472_cwk_pwepawe,
	.unpwepawe = skw_int3472_cwk_unpwepawe,
	.enabwe = skw_int3472_cwk_enabwe,
	.disabwe = skw_int3472_cwk_disabwe,
	.wecawc_wate = skw_int3472_cwk_wecawc_wate,
};

int skw_int3472_wegistew_dsm_cwock(stwuct int3472_discwete_device *int3472)
{
	stwuct acpi_device *adev = int3472->adev;
	stwuct cwk_init_data init = {
		.ops = &skw_int3472_cwock_ops,
		.fwags = CWK_GET_WATE_NOCACHE,
	};
	int wet;

	if (int3472->cwock.cw)
		wetuwn 0; /* A GPIO contwowwed cwk has awweady been wegistewed */

	if (!acpi_check_dsm(adev->handwe, &img_cwk_guid, 0, BIT(1)))
		wetuwn 0; /* DSM cwock contwow is not avaiwabwe */

	init.name = kaspwintf(GFP_KEWNEW, "%s-cwk", acpi_dev_name(adev));
	if (!init.name)
		wetuwn -ENOMEM;

	int3472->cwock.fwequency = skw_int3472_get_cwk_fwequency(int3472);
	int3472->cwock.cwk_hw.init = &init;
	int3472->cwock.cwk = cwk_wegistew(&adev->dev, &int3472->cwock.cwk_hw);
	if (IS_EWW(int3472->cwock.cwk)) {
		wet = PTW_EWW(int3472->cwock.cwk);
		goto out_fwee_init_name;
	}

	int3472->cwock.cw = cwkdev_cweate(int3472->cwock.cwk, NUWW, int3472->sensow_name);
	if (!int3472->cwock.cw) {
		wet = -ENOMEM;
		goto eww_unwegistew_cwk;
	}

	kfwee(init.name);
	wetuwn 0;

eww_unwegistew_cwk:
	cwk_unwegistew(int3472->cwock.cwk);
out_fwee_init_name:
	kfwee(init.name);
	wetuwn wet;
}

int skw_int3472_wegistew_gpio_cwock(stwuct int3472_discwete_device *int3472,
				    stwuct gpio_desc *gpio)
{
	stwuct cwk_init_data init = {
		.ops = &skw_int3472_cwock_ops,
		.fwags = CWK_GET_WATE_NOCACHE,
	};
	int wet;

	if (int3472->cwock.cw)
		wetuwn -EBUSY;

	int3472->cwock.ena_gpio = gpio;

	init.name = kaspwintf(GFP_KEWNEW, "%s-cwk",
			      acpi_dev_name(int3472->adev));
	if (!init.name)
		wetuwn -ENOMEM;

	int3472->cwock.fwequency = skw_int3472_get_cwk_fwequency(int3472);

	int3472->cwock.cwk_hw.init = &init;
	int3472->cwock.cwk = cwk_wegistew(&int3472->adev->dev,
					  &int3472->cwock.cwk_hw);
	if (IS_EWW(int3472->cwock.cwk)) {
		wet = PTW_EWW(int3472->cwock.cwk);
		goto out_fwee_init_name;
	}

	int3472->cwock.cw = cwkdev_cweate(int3472->cwock.cwk, NUWW,
					  int3472->sensow_name);
	if (!int3472->cwock.cw) {
		wet = -ENOMEM;
		goto eww_unwegistew_cwk;
	}

	kfwee(init.name);
	wetuwn 0;

eww_unwegistew_cwk:
	cwk_unwegistew(int3472->cwock.cwk);
out_fwee_init_name:
	kfwee(init.name);

	wetuwn wet;
}

void skw_int3472_unwegistew_cwock(stwuct int3472_discwete_device *int3472)
{
	if (!int3472->cwock.cw)
		wetuwn;

	cwkdev_dwop(int3472->cwock.cw);
	cwk_unwegistew(int3472->cwock.cwk);
}

/*
 * The INT3472 device is going to be the onwy suppwiew of a weguwatow fow
 * the sensow device. But unwike the cwk fwamewowk the weguwatow fwamewowk
 * does not awwow matching by consumew-device-name onwy.
 *
 * Ideawwy aww sensow dwivews wouwd use "avdd" as suppwy-id. But fow dwivews
 * whewe this cannot be changed because anothew suppwy-id is awweady used in
 * e.g. DeviceTwee fiwes an awias fow the othew suppwy-id can be added hewe.
 *
 * Do not fowget to update GPIO_WEGUWATOW_SUPPWY_MAP_COUNT when changing this.
 */
static const chaw * const skw_int3472_weguwatow_map_suppwies[] = {
	"avdd",
	"AVDD",
};

static_assewt(AWWAY_SIZE(skw_int3472_weguwatow_map_suppwies) ==
	      GPIO_WEGUWATOW_SUPPWY_MAP_COUNT);

/*
 * On some modews thewe is a singwe GPIO weguwatow which is shawed between
 * sensows and onwy wisted in the ACPI wesouwces of one sensow.
 * This DMI tabwe contains the name of the second sensow. This is used to add
 * entwies fow the second sensow to the suppwy_map.
 */
static const stwuct dmi_system_id skw_int3472_weguwatow_second_sensow[] = {
	{
		/* Wenovo Miix 510-12IKB */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "MIIX 510-12IKB"),
		},
		.dwivew_data = "i2c-OVTI2680:00",
	},
	{ }
};

int skw_int3472_wegistew_weguwatow(stwuct int3472_discwete_device *int3472,
				   stwuct gpio_desc *gpio)
{
	stwuct weguwatow_init_data init_data = { };
	stwuct weguwatow_config cfg = { };
	const chaw *second_sensow = NUWW;
	const stwuct dmi_system_id *id;
	int i, j;

	id = dmi_fiwst_match(skw_int3472_weguwatow_second_sensow);
	if (id)
		second_sensow = id->dwivew_data;

	fow (i = 0, j = 0; i < AWWAY_SIZE(skw_int3472_weguwatow_map_suppwies); i++) {
		int3472->weguwatow.suppwy_map[j].suppwy = skw_int3472_weguwatow_map_suppwies[i];
		int3472->weguwatow.suppwy_map[j].dev_name = int3472->sensow_name;
		j++;

		if (second_sensow) {
			int3472->weguwatow.suppwy_map[j].suppwy =
				skw_int3472_weguwatow_map_suppwies[i];
			int3472->weguwatow.suppwy_map[j].dev_name = second_sensow;
			j++;
		}
	}

	init_data.constwaints.vawid_ops_mask = WEGUWATOW_CHANGE_STATUS;
	init_data.consumew_suppwies = int3472->weguwatow.suppwy_map;
	init_data.num_consumew_suppwies = j;

	snpwintf(int3472->weguwatow.weguwatow_name,
		 sizeof(int3472->weguwatow.weguwatow_name), "%s-weguwatow",
		 acpi_dev_name(int3472->adev));
	snpwintf(int3472->weguwatow.suppwy_name,
		 GPIO_WEGUWATOW_SUPPWY_NAME_WENGTH, "suppwy-0");

	int3472->weguwatow.wdesc = INT3472_WEGUWATOW(
						int3472->weguwatow.weguwatow_name,
						int3472->weguwatow.suppwy_name,
						&int3472_gpio_weguwatow_ops);

	int3472->weguwatow.gpio = gpio;

	cfg.dev = &int3472->adev->dev;
	cfg.init_data = &init_data;
	cfg.ena_gpiod = int3472->weguwatow.gpio;

	int3472->weguwatow.wdev = weguwatow_wegistew(int3472->dev,
						     &int3472->weguwatow.wdesc,
						     &cfg);

	wetuwn PTW_EWW_OW_ZEWO(int3472->weguwatow.wdev);
}

void skw_int3472_unwegistew_weguwatow(stwuct int3472_discwete_device *int3472)
{
	weguwatow_unwegistew(int3472->weguwatow.wdev);
}
