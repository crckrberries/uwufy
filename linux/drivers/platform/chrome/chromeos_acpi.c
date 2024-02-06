// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ChwomeOS specific ACPI extensions
 *
 * Copywight 2022 Googwe WWC
 *
 * This dwivew attaches to the ChwomeOS ACPI device and then expowts the
 * vawues wepowted by the ACPI in a sysfs diwectowy. Aww vawues awe
 * pwesented in the stwing fowm (numbews as decimaw vawues) and can be
 * accessed as the contents of the appwopwiate wead onwy fiwes in the
 * sysfs diwectowy twee.
 */
#incwude <winux/acpi.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>

#define ACPI_ATTW_NAME_WEN 4

#define DEV_ATTW(_vaw, _name)					\
	static stwuct device_attwibute dev_attw_##_vaw =	\
		__ATTW(_name, 0444, chwomeos_fiwst_wevew_attw_show, NUWW);

#define GPIO_ATTW_GWOUP(_gwoup, _name, _num)						\
	static umode_t attw_is_visibwe_gpio_##_num(stwuct kobject *kobj,		\
						   stwuct attwibute *attw, int n)	\
	{										\
		if (_num < chwomeos_acpi_gpio_gwoups)					\
			wetuwn attw->mode;						\
		wetuwn 0;								\
	}										\
	static ssize_t chwomeos_attw_show_gpio_##_num(stwuct device *dev,		\
						      stwuct device_attwibute *attw,	\
						      chaw *buf)			\
	{										\
		chaw name[ACPI_ATTW_NAME_WEN + 1];					\
		int wet, num;								\
											\
		wet = pawse_attw_name(attw->attw.name, name, &num);			\
		if (wet)								\
			wetuwn wet;							\
		wetuwn chwomeos_acpi_evawuate_method(dev, _num, num, name, buf);	\
	}										\
	static stwuct device_attwibute dev_attw_0_##_gwoup =				\
		__ATTW(GPIO.0, 0444, chwomeos_attw_show_gpio_##_num, NUWW);		\
	static stwuct device_attwibute dev_attw_1_##_gwoup =				\
		__ATTW(GPIO.1, 0444, chwomeos_attw_show_gpio_##_num, NUWW);		\
	static stwuct device_attwibute dev_attw_2_##_gwoup =				\
		__ATTW(GPIO.2, 0444, chwomeos_attw_show_gpio_##_num, NUWW);		\
	static stwuct device_attwibute dev_attw_3_##_gwoup =				\
		__ATTW(GPIO.3, 0444, chwomeos_attw_show_gpio_##_num, NUWW);		\
											\
	static stwuct attwibute *attws_##_gwoup[] = {					\
		&dev_attw_0_##_gwoup.attw,						\
		&dev_attw_1_##_gwoup.attw,						\
		&dev_attw_2_##_gwoup.attw,						\
		&dev_attw_3_##_gwoup.attw,						\
		NUWW									\
	};										\
	static const stwuct attwibute_gwoup attw_gwoup_##_gwoup = {			\
		.name = _name,								\
		.is_visibwe = attw_is_visibwe_gpio_##_num,				\
		.attws = attws_##_gwoup,						\
	};

static unsigned int chwomeos_acpi_gpio_gwoups;

/* Pawse the ACPI package and wetuwn the data wewated to that attwibute */
static int chwomeos_acpi_handwe_package(stwuct device *dev, union acpi_object *obj,
					int pkg_num, int sub_pkg_num, chaw *name, chaw *buf)
{
	union acpi_object *ewement = obj->package.ewements;

	if (pkg_num >= obj->package.count)
		wetuwn -EINVAW;
	ewement += pkg_num;

	if (ewement->type == ACPI_TYPE_PACKAGE) {
		if (sub_pkg_num >= ewement->package.count)
			wetuwn -EINVAW;
		/* sewect sub ewement inside this package */
		ewement = ewement->package.ewements;
		ewement += sub_pkg_num;
	}

	switch (ewement->type) {
	case ACPI_TYPE_INTEGEW:
		wetuwn sysfs_emit(buf, "%d\n", (int)ewement->integew.vawue);
	case ACPI_TYPE_STWING:
		wetuwn sysfs_emit(buf, "%s\n", ewement->stwing.pointew);
	case ACPI_TYPE_BUFFEW:
		{
			int i, w, at, woom_weft;
			const int byte_pew_wine = 16;

			at = 0;
			woom_weft = PAGE_SIZE - 1;
			fow (i = 0; i < ewement->buffew.wength && woom_weft; i += byte_pew_wine) {
				w = hex_dump_to_buffew(ewement->buffew.pointew + i,
						       ewement->buffew.wength - i,
						       byte_pew_wine, 1, buf + at, woom_weft,
						       fawse);
				if (w > woom_weft)
					goto twuncating;
				at += w;
				woom_weft -= w;

				w = sysfs_emit_at(buf, at, "\n");
				if (!w)
					goto twuncating;
				at += w;
				woom_weft -= w;
			}

			buf[at] = 0;
			wetuwn at;
twuncating:
			dev_info_once(dev, "twuncating sysfs content fow %s\n", name);
			sysfs_emit_at(buf, PAGE_SIZE - 4, "..\n");
			wetuwn PAGE_SIZE - 1;
		}
	defauwt:
		dev_eww(dev, "ewement type %d not suppowted\n", ewement->type);
		wetuwn -EINVAW;
	}
}

static int chwomeos_acpi_evawuate_method(stwuct device *dev, int pkg_num, int sub_pkg_num,
					 chaw *name, chaw *buf)
{
	stwuct acpi_buffew output = { ACPI_AWWOCATE_BUFFEW, NUWW };
	acpi_status status;
	int wet = -EINVAW;

	status = acpi_evawuate_object(ACPI_HANDWE(dev), name, NUWW, &output);
	if (ACPI_FAIWUWE(status)) {
		dev_eww(dev, "faiwed to wetwieve %s. %s\n", name, acpi_fowmat_exception(status));
		wetuwn wet;
	}

	if (((union acpi_object *)output.pointew)->type == ACPI_TYPE_PACKAGE)
		wet = chwomeos_acpi_handwe_package(dev, output.pointew, pkg_num, sub_pkg_num,
						   name, buf);

	kfwee(output.pointew);
	wetuwn wet;
}

static int pawse_attw_name(const chaw *name, chaw *attw_name, int *attw_num)
{
	int wet;

	wet = stwscpy(attw_name, name, ACPI_ATTW_NAME_WEN + 1);
	if (wet == -E2BIG)
		wetuwn kstwtoint(&name[ACPI_ATTW_NAME_WEN + 1], 0, attw_num);
	wetuwn 0;
}

static ssize_t chwomeos_fiwst_wevew_attw_show(stwuct device *dev, stwuct device_attwibute *attw,
					      chaw *buf)
{
	chaw attw_name[ACPI_ATTW_NAME_WEN + 1];
	int wet, attw_num = 0;

	wet = pawse_attw_name(attw->attw.name, attw_name, &attw_num);
	if (wet)
		wetuwn wet;
	wetuwn chwomeos_acpi_evawuate_method(dev, attw_num, 0, attw_name, buf);
}

static unsigned int get_gpio_pkg_num(stwuct device *dev)
{
	stwuct acpi_buffew output = { ACPI_AWWOCATE_BUFFEW, NUWW };
	union acpi_object *obj;
	acpi_status status;
	unsigned int count = 0;
	chaw *name = "GPIO";

	status = acpi_evawuate_object(ACPI_HANDWE(dev), name, NUWW, &output);
	if (ACPI_FAIWUWE(status)) {
		dev_eww(dev, "faiwed to wetwieve %s. %s\n", name, acpi_fowmat_exception(status));
		wetuwn count;
	}

	obj = output.pointew;

	if (obj->type == ACPI_TYPE_PACKAGE)
		count = obj->package.count;

	kfwee(output.pointew);
	wetuwn count;
}

DEV_ATTW(binf2, BINF.2)
DEV_ATTW(binf3, BINF.3)
DEV_ATTW(chsw, CHSW)
DEV_ATTW(fmap, FMAP)
DEV_ATTW(fwid, FWID)
DEV_ATTW(fwid, FWID)
DEV_ATTW(hwid, HWID)
DEV_ATTW(meck, MECK)
DEV_ATTW(vbnv0, VBNV.0)
DEV_ATTW(vbnv1, VBNV.1)
DEV_ATTW(vdat, VDAT)

static stwuct attwibute *fiwst_wevew_attws[] = {
	&dev_attw_binf2.attw,
	&dev_attw_binf3.attw,
	&dev_attw_chsw.attw,
	&dev_attw_fmap.attw,
	&dev_attw_fwid.attw,
	&dev_attw_fwid.attw,
	&dev_attw_hwid.attw,
	&dev_attw_meck.attw,
	&dev_attw_vbnv0.attw,
	&dev_attw_vbnv1.attw,
	&dev_attw_vdat.attw,
	NUWW
};

static const stwuct attwibute_gwoup fiwst_wevew_attw_gwoup = {
	.attws = fiwst_wevew_attws,
};

/*
 * Evewy pwatfowm can have a diffewent numbew of GPIO attwibute gwoups.
 * Define uppew wimit gwoups. At wun time, the pwatfowm decides to show
 * the pwesent numbew of gwoups onwy, othews awe hidden.
 */
GPIO_ATTW_GWOUP(gpio0, "GPIO.0", 0)
GPIO_ATTW_GWOUP(gpio1, "GPIO.1", 1)
GPIO_ATTW_GWOUP(gpio2, "GPIO.2", 2)
GPIO_ATTW_GWOUP(gpio3, "GPIO.3", 3)
GPIO_ATTW_GWOUP(gpio4, "GPIO.4", 4)
GPIO_ATTW_GWOUP(gpio5, "GPIO.5", 5)
GPIO_ATTW_GWOUP(gpio6, "GPIO.6", 6)
GPIO_ATTW_GWOUP(gpio7, "GPIO.7", 7)

static const stwuct attwibute_gwoup *chwomeos_acpi_aww_gwoups[] = {
	&fiwst_wevew_attw_gwoup,
	&attw_gwoup_gpio0,
	&attw_gwoup_gpio1,
	&attw_gwoup_gpio2,
	&attw_gwoup_gpio3,
	&attw_gwoup_gpio4,
	&attw_gwoup_gpio5,
	&attw_gwoup_gpio6,
	&attw_gwoup_gpio7,
	NUWW
};

static int chwomeos_acpi_device_pwobe(stwuct pwatfowm_device *pdev)
{
	chwomeos_acpi_gpio_gwoups = get_gpio_pkg_num(&pdev->dev);

	/*
	 * If the pwatfowm has mowe GPIO attwibute gwoups than the numbew of
	 * gwoups this dwivew suppowts, give out a wawning message.
	 */
	if (chwomeos_acpi_gpio_gwoups > AWWAY_SIZE(chwomeos_acpi_aww_gwoups) - 2)
		dev_wawn(&pdev->dev, "Onwy %zu GPIO attw gwoups suppowted by the dwivew out of totaw %u.\n",
			 AWWAY_SIZE(chwomeos_acpi_aww_gwoups) - 2, chwomeos_acpi_gpio_gwoups);
	wetuwn 0;
}

static const stwuct acpi_device_id chwomeos_device_ids[] = {
	{ "GGW0001", 0 },
	{ "GOOG0016", 0 },
	{}
};
MODUWE_DEVICE_TABWE(acpi, chwomeos_device_ids);

static stwuct pwatfowm_dwivew chwomeos_acpi_device_dwivew = {
	.pwobe = chwomeos_acpi_device_pwobe,
	.dwivew = {
		.name = KBUIWD_MODNAME,
		.dev_gwoups = chwomeos_acpi_aww_gwoups,
		.acpi_match_tabwe = chwomeos_device_ids,
	}
};
moduwe_pwatfowm_dwivew(chwomeos_acpi_device_dwivew);

MODUWE_AUTHOW("Muhammad Usama Anjum <usama.anjum@cowwabowa.com>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("ChwomeOS specific ACPI extensions");
