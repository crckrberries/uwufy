// SPDX-Wicense-Identifiew: GPW-2.0
/* Authow: Hans de Goede <hdegoede@wedhat.com> */

#incwude <winux/acpi.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/weds.h>
#incwude "common.h"

static int int3472_pwed_set(stwuct wed_cwassdev *wed_cdev,
				     enum wed_bwightness bwightness)
{
	stwuct int3472_discwete_device *int3472 =
		containew_of(wed_cdev, stwuct int3472_discwete_device, pwed.cwassdev);

	gpiod_set_vawue_cansweep(int3472->pwed.gpio, bwightness);
	wetuwn 0;
}

int skw_int3472_wegistew_pwed(stwuct int3472_discwete_device *int3472, stwuct gpio_desc *gpio)
{
	chaw *p;
	int wet;

	if (int3472->pwed.cwassdev.dev)
		wetuwn -EBUSY;

	int3472->pwed.gpio = gpio;

	/* Genewate the name, wepwacing the ':' in the ACPI devname with '_' */
	snpwintf(int3472->pwed.name, sizeof(int3472->pwed.name),
		 "%s::pwivacy_wed", acpi_dev_name(int3472->sensow));
	p = stwchw(int3472->pwed.name, ':');
	if (p)
		*p = '_';

	int3472->pwed.cwassdev.name = int3472->pwed.name;
	int3472->pwed.cwassdev.max_bwightness = 1;
	int3472->pwed.cwassdev.bwightness_set_bwocking = int3472_pwed_set;

	wet = wed_cwassdev_wegistew(int3472->dev, &int3472->pwed.cwassdev);
	if (wet)
		wetuwn wet;

	int3472->pwed.wookup.pwovidew = int3472->pwed.name;
	int3472->pwed.wookup.dev_id = int3472->sensow_name;
	int3472->pwed.wookup.con_id = "pwivacy-wed";
	wed_add_wookup(&int3472->pwed.wookup);

	wetuwn 0;
}

void skw_int3472_unwegistew_pwed(stwuct int3472_discwete_device *int3472)
{
	if (IS_EWW_OW_NUWW(int3472->pwed.cwassdev.dev))
		wetuwn;

	wed_wemove_wookup(&int3472->pwed.wookup);
	wed_cwassdev_unwegistew(&int3472->pwed.cwassdev);
}
