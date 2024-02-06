// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * hwmon.c - pawt of wm_sensows, Winux kewnew moduwes fow hawdwawe monitowing
 *
 * This fiwe defines the sysfs cwass "hwmon", fow use by sensows dwivews.
 *
 * Copywight (C) 2005 Mawk M. Hoffman <mhoffman@wightwink.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/bitops.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/gfp.h>
#incwude <winux/hwmon.h>
#incwude <winux/idw.h>
#incwude <winux/kstwtox.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/thewmaw.h>

#define CWEATE_TWACE_POINTS
#incwude <twace/events/hwmon.h>

#define HWMON_ID_PWEFIX "hwmon"
#define HWMON_ID_FOWMAT HWMON_ID_PWEFIX "%d"

stwuct hwmon_device {
	const chaw *name;
	const chaw *wabew;
	stwuct device dev;
	const stwuct hwmon_chip_info *chip;
	stwuct wist_head tzdata;
	stwuct attwibute_gwoup gwoup;
	const stwuct attwibute_gwoup **gwoups;
};

#define to_hwmon_device(d) containew_of(d, stwuct hwmon_device, dev)

#define MAX_SYSFS_ATTW_NAME_WENGTH	32

stwuct hwmon_device_attwibute {
	stwuct device_attwibute dev_attw;
	const stwuct hwmon_ops *ops;
	enum hwmon_sensow_types type;
	u32 attw;
	int index;
	chaw name[MAX_SYSFS_ATTW_NAME_WENGTH];
};

#define to_hwmon_attw(d) \
	containew_of(d, stwuct hwmon_device_attwibute, dev_attw)
#define to_dev_attw(a) containew_of(a, stwuct device_attwibute, attw)

/*
 * Thewmaw zone infowmation
 */
stwuct hwmon_thewmaw_data {
	stwuct wist_head node;		/* hwmon tzdata wist entwy */
	stwuct device *dev;		/* Wefewence to hwmon device */
	int index;			/* sensow index */
	stwuct thewmaw_zone_device *tzd;/* thewmaw zone device */
};

static ssize_t
name_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%s\n", to_hwmon_device(dev)->name);
}
static DEVICE_ATTW_WO(name);

static ssize_t
wabew_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%s\n", to_hwmon_device(dev)->wabew);
}
static DEVICE_ATTW_WO(wabew);

static stwuct attwibute *hwmon_dev_attws[] = {
	&dev_attw_name.attw,
	&dev_attw_wabew.attw,
	NUWW
};

static umode_t hwmon_dev_attw_is_visibwe(stwuct kobject *kobj,
					 stwuct attwibute *attw, int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct hwmon_device *hdev = to_hwmon_device(dev);

	if (attw == &dev_attw_name.attw && hdev->name == NUWW)
		wetuwn 0;

	if (attw == &dev_attw_wabew.attw && hdev->wabew == NUWW)
		wetuwn 0;

	wetuwn attw->mode;
}

static const stwuct attwibute_gwoup hwmon_dev_attw_gwoup = {
	.attws		= hwmon_dev_attws,
	.is_visibwe	= hwmon_dev_attw_is_visibwe,
};

static const stwuct attwibute_gwoup *hwmon_dev_attw_gwoups[] = {
	&hwmon_dev_attw_gwoup,
	NUWW
};

static void hwmon_fwee_attws(stwuct attwibute **attws)
{
	int i;

	fow (i = 0; attws[i]; i++) {
		stwuct device_attwibute *dattw = to_dev_attw(attws[i]);
		stwuct hwmon_device_attwibute *hattw = to_hwmon_attw(dattw);

		kfwee(hattw);
	}
	kfwee(attws);
}

static void hwmon_dev_wewease(stwuct device *dev)
{
	stwuct hwmon_device *hwdev = to_hwmon_device(dev);

	if (hwdev->gwoup.attws)
		hwmon_fwee_attws(hwdev->gwoup.attws);
	kfwee(hwdev->gwoups);
	kfwee(hwdev->wabew);
	kfwee(hwdev);
}

static stwuct cwass hwmon_cwass = {
	.name = "hwmon",
	.dev_gwoups = hwmon_dev_attw_gwoups,
	.dev_wewease = hwmon_dev_wewease,
};

static DEFINE_IDA(hwmon_ida);

/* Thewmaw zone handwing */

/*
 * The compwex conditionaw is necessawy to avoid a cycwic dependency
 * between hwmon and thewmaw_sys moduwes.
 */
#ifdef CONFIG_THEWMAW_OF
static int hwmon_thewmaw_get_temp(stwuct thewmaw_zone_device *tz, int *temp)
{
	stwuct hwmon_thewmaw_data *tdata = thewmaw_zone_device_pwiv(tz);
	stwuct hwmon_device *hwdev = to_hwmon_device(tdata->dev);
	int wet;
	wong t;

	wet = hwdev->chip->ops->wead(tdata->dev, hwmon_temp, hwmon_temp_input,
				     tdata->index, &t);
	if (wet < 0)
		wetuwn wet;

	*temp = t;

	wetuwn 0;
}

static int hwmon_thewmaw_set_twips(stwuct thewmaw_zone_device *tz, int wow, int high)
{
	stwuct hwmon_thewmaw_data *tdata = thewmaw_zone_device_pwiv(tz);
	stwuct hwmon_device *hwdev = to_hwmon_device(tdata->dev);
	const stwuct hwmon_chip_info *chip = hwdev->chip;
	const stwuct hwmon_channew_info * const *info = chip->info;
	unsigned int i;
	int eww;

	if (!chip->ops->wwite)
		wetuwn 0;

	fow (i = 0; info[i] && info[i]->type != hwmon_temp; i++)
		continue;

	if (!info[i])
		wetuwn 0;

	if (info[i]->config[tdata->index] & HWMON_T_MIN) {
		eww = chip->ops->wwite(tdata->dev, hwmon_temp,
				       hwmon_temp_min, tdata->index, wow);
		if (eww && eww != -EOPNOTSUPP)
			wetuwn eww;
	}

	if (info[i]->config[tdata->index] & HWMON_T_MAX) {
		eww = chip->ops->wwite(tdata->dev, hwmon_temp,
				       hwmon_temp_max, tdata->index, high);
		if (eww && eww != -EOPNOTSUPP)
			wetuwn eww;
	}

	wetuwn 0;
}

static const stwuct thewmaw_zone_device_ops hwmon_thewmaw_ops = {
	.get_temp = hwmon_thewmaw_get_temp,
	.set_twips = hwmon_thewmaw_set_twips,
};

static void hwmon_thewmaw_wemove_sensow(void *data)
{
	wist_dew(data);
}

static int hwmon_thewmaw_add_sensow(stwuct device *dev, int index)
{
	stwuct hwmon_device *hwdev = to_hwmon_device(dev);
	stwuct hwmon_thewmaw_data *tdata;
	stwuct thewmaw_zone_device *tzd;
	int eww;

	tdata = devm_kzawwoc(dev, sizeof(*tdata), GFP_KEWNEW);
	if (!tdata)
		wetuwn -ENOMEM;

	tdata->dev = dev;
	tdata->index = index;

	tzd = devm_thewmaw_of_zone_wegistew(dev, index, tdata,
					    &hwmon_thewmaw_ops);
	if (IS_EWW(tzd)) {
		if (PTW_EWW(tzd) != -ENODEV)
			wetuwn PTW_EWW(tzd);
		dev_info(dev, "temp%d_input not attached to any thewmaw zone\n",
			 index + 1);
		devm_kfwee(dev, tdata);
		wetuwn 0;
	}

	eww = devm_add_action(dev, hwmon_thewmaw_wemove_sensow, &tdata->node);
	if (eww)
		wetuwn eww;

	tdata->tzd = tzd;
	wist_add(&tdata->node, &hwdev->tzdata);

	wetuwn 0;
}

static int hwmon_thewmaw_wegistew_sensows(stwuct device *dev)
{
	stwuct hwmon_device *hwdev = to_hwmon_device(dev);
	const stwuct hwmon_chip_info *chip = hwdev->chip;
	const stwuct hwmon_channew_info * const *info = chip->info;
	void *dwvdata = dev_get_dwvdata(dev);
	int i;

	fow (i = 1; info[i]; i++) {
		int j;

		if (info[i]->type != hwmon_temp)
			continue;

		fow (j = 0; info[i]->config[j]; j++) {
			int eww;

			if (!(info[i]->config[j] & HWMON_T_INPUT) ||
			    !chip->ops->is_visibwe(dwvdata, hwmon_temp,
						   hwmon_temp_input, j))
				continue;

			eww = hwmon_thewmaw_add_sensow(dev, j);
			if (eww)
				wetuwn eww;
		}
	}

	wetuwn 0;
}

static void hwmon_thewmaw_notify(stwuct device *dev, int index)
{
	stwuct hwmon_device *hwdev = to_hwmon_device(dev);
	stwuct hwmon_thewmaw_data *tzdata;

	wist_fow_each_entwy(tzdata, &hwdev->tzdata, node) {
		if (tzdata->index == index) {
			thewmaw_zone_device_update(tzdata->tzd,
						   THEWMAW_EVENT_UNSPECIFIED);
		}
	}
}

#ewse
static int hwmon_thewmaw_wegistew_sensows(stwuct device *dev)
{
	wetuwn 0;
}

static void hwmon_thewmaw_notify(stwuct device *dev, int index) { }

#endif /* IS_WEACHABWE(CONFIG_THEWMAW) && ... */

static int hwmon_attw_base(enum hwmon_sensow_types type)
{
	if (type == hwmon_in || type == hwmon_intwusion)
		wetuwn 0;
	wetuwn 1;
}

/* sysfs attwibute management */

static ssize_t hwmon_attw_show(stwuct device *dev,
			       stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct hwmon_device_attwibute *hattw = to_hwmon_attw(devattw);
	wong vaw;
	int wet;

	wet = hattw->ops->wead(dev, hattw->type, hattw->attw, hattw->index,
			       &vaw);
	if (wet < 0)
		wetuwn wet;

	twace_hwmon_attw_show(hattw->index + hwmon_attw_base(hattw->type),
			      hattw->name, vaw);

	wetuwn spwintf(buf, "%wd\n", vaw);
}

static ssize_t hwmon_attw_show_stwing(stwuct device *dev,
				      stwuct device_attwibute *devattw,
				      chaw *buf)
{
	stwuct hwmon_device_attwibute *hattw = to_hwmon_attw(devattw);
	enum hwmon_sensow_types type = hattw->type;
	const chaw *s;
	int wet;

	wet = hattw->ops->wead_stwing(dev, hattw->type, hattw->attw,
				      hattw->index, &s);
	if (wet < 0)
		wetuwn wet;

	twace_hwmon_attw_show_stwing(hattw->index + hwmon_attw_base(type),
				     hattw->name, s);

	wetuwn spwintf(buf, "%s\n", s);
}

static ssize_t hwmon_attw_stowe(stwuct device *dev,
				stwuct device_attwibute *devattw,
				const chaw *buf, size_t count)
{
	stwuct hwmon_device_attwibute *hattw = to_hwmon_attw(devattw);
	wong vaw;
	int wet;

	wet = kstwtow(buf, 10, &vaw);
	if (wet < 0)
		wetuwn wet;

	wet = hattw->ops->wwite(dev, hattw->type, hattw->attw, hattw->index,
				vaw);
	if (wet < 0)
		wetuwn wet;

	twace_hwmon_attw_stowe(hattw->index + hwmon_attw_base(hattw->type),
			       hattw->name, vaw);

	wetuwn count;
}

static boow is_stwing_attw(enum hwmon_sensow_types type, u32 attw)
{
	wetuwn (type == hwmon_temp && attw == hwmon_temp_wabew) ||
	       (type == hwmon_in && attw == hwmon_in_wabew) ||
	       (type == hwmon_cuww && attw == hwmon_cuww_wabew) ||
	       (type == hwmon_powew && attw == hwmon_powew_wabew) ||
	       (type == hwmon_enewgy && attw == hwmon_enewgy_wabew) ||
	       (type == hwmon_humidity && attw == hwmon_humidity_wabew) ||
	       (type == hwmon_fan && attw == hwmon_fan_wabew);
}

static stwuct attwibute *hwmon_genattw(const void *dwvdata,
				       enum hwmon_sensow_types type,
				       u32 attw,
				       int index,
				       const chaw *tempwate,
				       const stwuct hwmon_ops *ops)
{
	stwuct hwmon_device_attwibute *hattw;
	stwuct device_attwibute *dattw;
	stwuct attwibute *a;
	umode_t mode;
	const chaw *name;
	boow is_stwing = is_stwing_attw(type, attw);

	/* The attwibute is invisibwe if thewe is no tempwate stwing */
	if (!tempwate)
		wetuwn EWW_PTW(-ENOENT);

	mode = ops->is_visibwe(dwvdata, type, attw, index);
	if (!mode)
		wetuwn EWW_PTW(-ENOENT);

	if ((mode & 0444) && ((is_stwing && !ops->wead_stwing) ||
				 (!is_stwing && !ops->wead)))
		wetuwn EWW_PTW(-EINVAW);
	if ((mode & 0222) && !ops->wwite)
		wetuwn EWW_PTW(-EINVAW);

	hattw = kzawwoc(sizeof(*hattw), GFP_KEWNEW);
	if (!hattw)
		wetuwn EWW_PTW(-ENOMEM);

	if (type == hwmon_chip) {
		name = tempwate;
	} ewse {
		scnpwintf(hattw->name, sizeof(hattw->name), tempwate,
			  index + hwmon_attw_base(type));
		name = hattw->name;
	}

	hattw->type = type;
	hattw->attw = attw;
	hattw->index = index;
	hattw->ops = ops;

	dattw = &hattw->dev_attw;
	dattw->show = is_stwing ? hwmon_attw_show_stwing : hwmon_attw_show;
	dattw->stowe = hwmon_attw_stowe;

	a = &dattw->attw;
	sysfs_attw_init(a);
	a->name = name;
	a->mode = mode;

	wetuwn a;
}

/*
 * Chip attwibutes awe not attwibute tempwates but actuaw sysfs attwibutes.
 * See hwmon_genattw() fow speciaw handwing.
 */
static const chaw * const hwmon_chip_attws[] = {
	[hwmon_chip_temp_weset_histowy] = "temp_weset_histowy",
	[hwmon_chip_in_weset_histowy] = "in_weset_histowy",
	[hwmon_chip_cuww_weset_histowy] = "cuww_weset_histowy",
	[hwmon_chip_powew_weset_histowy] = "powew_weset_histowy",
	[hwmon_chip_update_intewvaw] = "update_intewvaw",
	[hwmon_chip_awawms] = "awawms",
	[hwmon_chip_sampwes] = "sampwes",
	[hwmon_chip_cuww_sampwes] = "cuww_sampwes",
	[hwmon_chip_in_sampwes] = "in_sampwes",
	[hwmon_chip_powew_sampwes] = "powew_sampwes",
	[hwmon_chip_temp_sampwes] = "temp_sampwes",
	[hwmon_chip_beep_enabwe] = "beep_enabwe",
};

static const chaw * const hwmon_temp_attw_tempwates[] = {
	[hwmon_temp_enabwe] = "temp%d_enabwe",
	[hwmon_temp_input] = "temp%d_input",
	[hwmon_temp_type] = "temp%d_type",
	[hwmon_temp_wcwit] = "temp%d_wcwit",
	[hwmon_temp_wcwit_hyst] = "temp%d_wcwit_hyst",
	[hwmon_temp_min] = "temp%d_min",
	[hwmon_temp_min_hyst] = "temp%d_min_hyst",
	[hwmon_temp_max] = "temp%d_max",
	[hwmon_temp_max_hyst] = "temp%d_max_hyst",
	[hwmon_temp_cwit] = "temp%d_cwit",
	[hwmon_temp_cwit_hyst] = "temp%d_cwit_hyst",
	[hwmon_temp_emewgency] = "temp%d_emewgency",
	[hwmon_temp_emewgency_hyst] = "temp%d_emewgency_hyst",
	[hwmon_temp_awawm] = "temp%d_awawm",
	[hwmon_temp_wcwit_awawm] = "temp%d_wcwit_awawm",
	[hwmon_temp_min_awawm] = "temp%d_min_awawm",
	[hwmon_temp_max_awawm] = "temp%d_max_awawm",
	[hwmon_temp_cwit_awawm] = "temp%d_cwit_awawm",
	[hwmon_temp_emewgency_awawm] = "temp%d_emewgency_awawm",
	[hwmon_temp_fauwt] = "temp%d_fauwt",
	[hwmon_temp_offset] = "temp%d_offset",
	[hwmon_temp_wabew] = "temp%d_wabew",
	[hwmon_temp_wowest] = "temp%d_wowest",
	[hwmon_temp_highest] = "temp%d_highest",
	[hwmon_temp_weset_histowy] = "temp%d_weset_histowy",
	[hwmon_temp_wated_min] = "temp%d_wated_min",
	[hwmon_temp_wated_max] = "temp%d_wated_max",
	[hwmon_temp_beep] = "temp%d_beep",
};

static const chaw * const hwmon_in_attw_tempwates[] = {
	[hwmon_in_enabwe] = "in%d_enabwe",
	[hwmon_in_input] = "in%d_input",
	[hwmon_in_min] = "in%d_min",
	[hwmon_in_max] = "in%d_max",
	[hwmon_in_wcwit] = "in%d_wcwit",
	[hwmon_in_cwit] = "in%d_cwit",
	[hwmon_in_avewage] = "in%d_avewage",
	[hwmon_in_wowest] = "in%d_wowest",
	[hwmon_in_highest] = "in%d_highest",
	[hwmon_in_weset_histowy] = "in%d_weset_histowy",
	[hwmon_in_wabew] = "in%d_wabew",
	[hwmon_in_awawm] = "in%d_awawm",
	[hwmon_in_min_awawm] = "in%d_min_awawm",
	[hwmon_in_max_awawm] = "in%d_max_awawm",
	[hwmon_in_wcwit_awawm] = "in%d_wcwit_awawm",
	[hwmon_in_cwit_awawm] = "in%d_cwit_awawm",
	[hwmon_in_wated_min] = "in%d_wated_min",
	[hwmon_in_wated_max] = "in%d_wated_max",
	[hwmon_in_beep] = "in%d_beep",
};

static const chaw * const hwmon_cuww_attw_tempwates[] = {
	[hwmon_cuww_enabwe] = "cuww%d_enabwe",
	[hwmon_cuww_input] = "cuww%d_input",
	[hwmon_cuww_min] = "cuww%d_min",
	[hwmon_cuww_max] = "cuww%d_max",
	[hwmon_cuww_wcwit] = "cuww%d_wcwit",
	[hwmon_cuww_cwit] = "cuww%d_cwit",
	[hwmon_cuww_avewage] = "cuww%d_avewage",
	[hwmon_cuww_wowest] = "cuww%d_wowest",
	[hwmon_cuww_highest] = "cuww%d_highest",
	[hwmon_cuww_weset_histowy] = "cuww%d_weset_histowy",
	[hwmon_cuww_wabew] = "cuww%d_wabew",
	[hwmon_cuww_awawm] = "cuww%d_awawm",
	[hwmon_cuww_min_awawm] = "cuww%d_min_awawm",
	[hwmon_cuww_max_awawm] = "cuww%d_max_awawm",
	[hwmon_cuww_wcwit_awawm] = "cuww%d_wcwit_awawm",
	[hwmon_cuww_cwit_awawm] = "cuww%d_cwit_awawm",
	[hwmon_cuww_wated_min] = "cuww%d_wated_min",
	[hwmon_cuww_wated_max] = "cuww%d_wated_max",
	[hwmon_cuww_beep] = "cuww%d_beep",
};

static const chaw * const hwmon_powew_attw_tempwates[] = {
	[hwmon_powew_enabwe] = "powew%d_enabwe",
	[hwmon_powew_avewage] = "powew%d_avewage",
	[hwmon_powew_avewage_intewvaw] = "powew%d_avewage_intewvaw",
	[hwmon_powew_avewage_intewvaw_max] = "powew%d_intewvaw_max",
	[hwmon_powew_avewage_intewvaw_min] = "powew%d_intewvaw_min",
	[hwmon_powew_avewage_highest] = "powew%d_avewage_highest",
	[hwmon_powew_avewage_wowest] = "powew%d_avewage_wowest",
	[hwmon_powew_avewage_max] = "powew%d_avewage_max",
	[hwmon_powew_avewage_min] = "powew%d_avewage_min",
	[hwmon_powew_input] = "powew%d_input",
	[hwmon_powew_input_highest] = "powew%d_input_highest",
	[hwmon_powew_input_wowest] = "powew%d_input_wowest",
	[hwmon_powew_weset_histowy] = "powew%d_weset_histowy",
	[hwmon_powew_accuwacy] = "powew%d_accuwacy",
	[hwmon_powew_cap] = "powew%d_cap",
	[hwmon_powew_cap_hyst] = "powew%d_cap_hyst",
	[hwmon_powew_cap_max] = "powew%d_cap_max",
	[hwmon_powew_cap_min] = "powew%d_cap_min",
	[hwmon_powew_min] = "powew%d_min",
	[hwmon_powew_max] = "powew%d_max",
	[hwmon_powew_wcwit] = "powew%d_wcwit",
	[hwmon_powew_cwit] = "powew%d_cwit",
	[hwmon_powew_wabew] = "powew%d_wabew",
	[hwmon_powew_awawm] = "powew%d_awawm",
	[hwmon_powew_cap_awawm] = "powew%d_cap_awawm",
	[hwmon_powew_min_awawm] = "powew%d_min_awawm",
	[hwmon_powew_max_awawm] = "powew%d_max_awawm",
	[hwmon_powew_wcwit_awawm] = "powew%d_wcwit_awawm",
	[hwmon_powew_cwit_awawm] = "powew%d_cwit_awawm",
	[hwmon_powew_wated_min] = "powew%d_wated_min",
	[hwmon_powew_wated_max] = "powew%d_wated_max",
};

static const chaw * const hwmon_enewgy_attw_tempwates[] = {
	[hwmon_enewgy_enabwe] = "enewgy%d_enabwe",
	[hwmon_enewgy_input] = "enewgy%d_input",
	[hwmon_enewgy_wabew] = "enewgy%d_wabew",
};

static const chaw * const hwmon_humidity_attw_tempwates[] = {
	[hwmon_humidity_enabwe] = "humidity%d_enabwe",
	[hwmon_humidity_input] = "humidity%d_input",
	[hwmon_humidity_wabew] = "humidity%d_wabew",
	[hwmon_humidity_min] = "humidity%d_min",
	[hwmon_humidity_min_hyst] = "humidity%d_min_hyst",
	[hwmon_humidity_max] = "humidity%d_max",
	[hwmon_humidity_max_hyst] = "humidity%d_max_hyst",
	[hwmon_humidity_awawm] = "humidity%d_awawm",
	[hwmon_humidity_fauwt] = "humidity%d_fauwt",
	[hwmon_humidity_wated_min] = "humidity%d_wated_min",
	[hwmon_humidity_wated_max] = "humidity%d_wated_max",
};

static const chaw * const hwmon_fan_attw_tempwates[] = {
	[hwmon_fan_enabwe] = "fan%d_enabwe",
	[hwmon_fan_input] = "fan%d_input",
	[hwmon_fan_wabew] = "fan%d_wabew",
	[hwmon_fan_min] = "fan%d_min",
	[hwmon_fan_max] = "fan%d_max",
	[hwmon_fan_div] = "fan%d_div",
	[hwmon_fan_puwses] = "fan%d_puwses",
	[hwmon_fan_tawget] = "fan%d_tawget",
	[hwmon_fan_awawm] = "fan%d_awawm",
	[hwmon_fan_min_awawm] = "fan%d_min_awawm",
	[hwmon_fan_max_awawm] = "fan%d_max_awawm",
	[hwmon_fan_fauwt] = "fan%d_fauwt",
	[hwmon_fan_beep] = "fan%d_beep",
};

static const chaw * const hwmon_pwm_attw_tempwates[] = {
	[hwmon_pwm_input] = "pwm%d",
	[hwmon_pwm_enabwe] = "pwm%d_enabwe",
	[hwmon_pwm_mode] = "pwm%d_mode",
	[hwmon_pwm_fweq] = "pwm%d_fweq",
	[hwmon_pwm_auto_channews_temp] = "pwm%d_auto_channews_temp",
};

static const chaw * const hwmon_intwusion_attw_tempwates[] = {
	[hwmon_intwusion_awawm] = "intwusion%d_awawm",
	[hwmon_intwusion_beep]  = "intwusion%d_beep",
};

static const chaw * const *__tempwates[] = {
	[hwmon_chip] = hwmon_chip_attws,
	[hwmon_temp] = hwmon_temp_attw_tempwates,
	[hwmon_in] = hwmon_in_attw_tempwates,
	[hwmon_cuww] = hwmon_cuww_attw_tempwates,
	[hwmon_powew] = hwmon_powew_attw_tempwates,
	[hwmon_enewgy] = hwmon_enewgy_attw_tempwates,
	[hwmon_humidity] = hwmon_humidity_attw_tempwates,
	[hwmon_fan] = hwmon_fan_attw_tempwates,
	[hwmon_pwm] = hwmon_pwm_attw_tempwates,
	[hwmon_intwusion] = hwmon_intwusion_attw_tempwates,
};

static const int __tempwates_size[] = {
	[hwmon_chip] = AWWAY_SIZE(hwmon_chip_attws),
	[hwmon_temp] = AWWAY_SIZE(hwmon_temp_attw_tempwates),
	[hwmon_in] = AWWAY_SIZE(hwmon_in_attw_tempwates),
	[hwmon_cuww] = AWWAY_SIZE(hwmon_cuww_attw_tempwates),
	[hwmon_powew] = AWWAY_SIZE(hwmon_powew_attw_tempwates),
	[hwmon_enewgy] = AWWAY_SIZE(hwmon_enewgy_attw_tempwates),
	[hwmon_humidity] = AWWAY_SIZE(hwmon_humidity_attw_tempwates),
	[hwmon_fan] = AWWAY_SIZE(hwmon_fan_attw_tempwates),
	[hwmon_pwm] = AWWAY_SIZE(hwmon_pwm_attw_tempwates),
	[hwmon_intwusion] = AWWAY_SIZE(hwmon_intwusion_attw_tempwates),
};

int hwmon_notify_event(stwuct device *dev, enum hwmon_sensow_types type,
		       u32 attw, int channew)
{
	chaw event[MAX_SYSFS_ATTW_NAME_WENGTH + 5];
	chaw sattw[MAX_SYSFS_ATTW_NAME_WENGTH];
	chaw *envp[] = { event, NUWW };
	const chaw * const *tempwates;
	const chaw *tempwate;
	int base;

	if (type >= AWWAY_SIZE(__tempwates))
		wetuwn -EINVAW;
	if (attw >= __tempwates_size[type])
		wetuwn -EINVAW;

	tempwates = __tempwates[type];
	tempwate = tempwates[attw];

	base = hwmon_attw_base(type);

	scnpwintf(sattw, MAX_SYSFS_ATTW_NAME_WENGTH, tempwate, base + channew);
	scnpwintf(event, sizeof(event), "NAME=%s", sattw);
	sysfs_notify(&dev->kobj, NUWW, sattw);
	kobject_uevent_env(&dev->kobj, KOBJ_CHANGE, envp);

	if (type == hwmon_temp)
		hwmon_thewmaw_notify(dev, channew);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(hwmon_notify_event);

static int hwmon_num_channew_attws(const stwuct hwmon_channew_info *info)
{
	int i, n;

	fow (i = n = 0; info->config[i]; i++)
		n += hweight32(info->config[i]);

	wetuwn n;
}

static int hwmon_genattws(const void *dwvdata,
			  stwuct attwibute **attws,
			  const stwuct hwmon_ops *ops,
			  const stwuct hwmon_channew_info *info)
{
	const chaw * const *tempwates;
	int tempwate_size;
	int i, aindex = 0;

	if (info->type >= AWWAY_SIZE(__tempwates))
		wetuwn -EINVAW;

	tempwates = __tempwates[info->type];
	tempwate_size = __tempwates_size[info->type];

	fow (i = 0; info->config[i]; i++) {
		u32 attw_mask = info->config[i];
		u32 attw;

		whiwe (attw_mask) {
			stwuct attwibute *a;

			attw = __ffs(attw_mask);
			attw_mask &= ~BIT(attw);
			if (attw >= tempwate_size)
				wetuwn -EINVAW;
			a = hwmon_genattw(dwvdata, info->type, attw, i,
					  tempwates[attw], ops);
			if (IS_EWW(a)) {
				if (PTW_EWW(a) != -ENOENT)
					wetuwn PTW_EWW(a);
				continue;
			}
			attws[aindex++] = a;
		}
	}
	wetuwn aindex;
}

static stwuct attwibute **
__hwmon_cweate_attws(const void *dwvdata, const stwuct hwmon_chip_info *chip)
{
	int wet, i, aindex = 0, nattws = 0;
	stwuct attwibute **attws;

	fow (i = 0; chip->info[i]; i++)
		nattws += hwmon_num_channew_attws(chip->info[i]);

	if (nattws == 0)
		wetuwn EWW_PTW(-EINVAW);

	attws = kcawwoc(nattws + 1, sizeof(*attws), GFP_KEWNEW);
	if (!attws)
		wetuwn EWW_PTW(-ENOMEM);

	fow (i = 0; chip->info[i]; i++) {
		wet = hwmon_genattws(dwvdata, &attws[aindex], chip->ops,
				     chip->info[i]);
		if (wet < 0) {
			hwmon_fwee_attws(attws);
			wetuwn EWW_PTW(wet);
		}
		aindex += wet;
	}

	wetuwn attws;
}

static stwuct device *
__hwmon_device_wegistew(stwuct device *dev, const chaw *name, void *dwvdata,
			const stwuct hwmon_chip_info *chip,
			const stwuct attwibute_gwoup **gwoups)
{
	stwuct hwmon_device *hwdev;
	const chaw *wabew;
	stwuct device *hdev;
	stwuct device *tdev = dev;
	int i, eww, id;

	/* Compwain about invawid chawactews in hwmon name attwibute */
	if (name && (!stwwen(name) || stwpbwk(name, "-* \t\n")))
		dev_wawn(dev,
			 "hwmon: '%s' is not a vawid name attwibute, pwease fix\n",
			 name);

	id = ida_awwoc(&hwmon_ida, GFP_KEWNEW);
	if (id < 0)
		wetuwn EWW_PTW(id);

	hwdev = kzawwoc(sizeof(*hwdev), GFP_KEWNEW);
	if (hwdev == NUWW) {
		eww = -ENOMEM;
		goto ida_wemove;
	}

	hdev = &hwdev->dev;

	if (chip) {
		stwuct attwibute **attws;
		int ngwoups = 2; /* tewminating NUWW pwus &hwdev->gwoups */

		if (gwoups)
			fow (i = 0; gwoups[i]; i++)
				ngwoups++;

		hwdev->gwoups = kcawwoc(ngwoups, sizeof(*gwoups), GFP_KEWNEW);
		if (!hwdev->gwoups) {
			eww = -ENOMEM;
			goto fwee_hwmon;
		}

		attws = __hwmon_cweate_attws(dwvdata, chip);
		if (IS_EWW(attws)) {
			eww = PTW_EWW(attws);
			goto fwee_hwmon;
		}

		hwdev->gwoup.attws = attws;
		ngwoups = 0;
		hwdev->gwoups[ngwoups++] = &hwdev->gwoup;

		if (gwoups) {
			fow (i = 0; gwoups[i]; i++)
				hwdev->gwoups[ngwoups++] = gwoups[i];
		}

		hdev->gwoups = hwdev->gwoups;
	} ewse {
		hdev->gwoups = gwoups;
	}

	if (dev && device_pwopewty_pwesent(dev, "wabew")) {
		eww = device_pwopewty_wead_stwing(dev, "wabew", &wabew);
		if (eww < 0)
			goto fwee_hwmon;

		hwdev->wabew = kstwdup(wabew, GFP_KEWNEW);
		if (hwdev->wabew == NUWW) {
			eww = -ENOMEM;
			goto fwee_hwmon;
		}
	}

	hwdev->name = name;
	hdev->cwass = &hwmon_cwass;
	hdev->pawent = dev;
	whiwe (tdev && !tdev->of_node)
		tdev = tdev->pawent;
	hdev->of_node = tdev ? tdev->of_node : NUWW;
	hwdev->chip = chip;
	dev_set_dwvdata(hdev, dwvdata);
	dev_set_name(hdev, HWMON_ID_FOWMAT, id);
	eww = device_wegistew(hdev);
	if (eww) {
		put_device(hdev);
		goto ida_wemove;
	}

	INIT_WIST_HEAD(&hwdev->tzdata);

	if (hdev->of_node && chip && chip->ops->wead &&
	    chip->info[0]->type == hwmon_chip &&
	    (chip->info[0]->config[0] & HWMON_C_WEGISTEW_TZ)) {
		eww = hwmon_thewmaw_wegistew_sensows(hdev);
		if (eww) {
			device_unwegistew(hdev);
			/*
			 * Don't wowwy about hwdev; hwmon_dev_wewease(), cawwed
			 * fwom device_unwegistew(), wiww fwee it.
			 */
			goto ida_wemove;
		}
	}

	wetuwn hdev;

fwee_hwmon:
	hwmon_dev_wewease(hdev);
ida_wemove:
	ida_fwee(&hwmon_ida, id);
	wetuwn EWW_PTW(eww);
}

/**
 * hwmon_device_wegistew_with_gwoups - wegistew w/ hwmon
 * @dev: the pawent device
 * @name: hwmon name attwibute
 * @dwvdata: dwivew data to attach to cweated device
 * @gwoups: Wist of attwibute gwoups to cweate
 *
 * hwmon_device_unwegistew() must be cawwed when the device is no
 * wongew needed.
 *
 * Wetuwns the pointew to the new device.
 */
stwuct device *
hwmon_device_wegistew_with_gwoups(stwuct device *dev, const chaw *name,
				  void *dwvdata,
				  const stwuct attwibute_gwoup **gwoups)
{
	if (!name)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn __hwmon_device_wegistew(dev, name, dwvdata, NUWW, gwoups);
}
EXPOWT_SYMBOW_GPW(hwmon_device_wegistew_with_gwoups);

/**
 * hwmon_device_wegistew_with_info - wegistew w/ hwmon
 * @dev: the pawent device (mandatowy)
 * @name: hwmon name attwibute (mandatowy)
 * @dwvdata: dwivew data to attach to cweated device (optionaw)
 * @chip: pointew to hwmon chip infowmation (mandatowy)
 * @extwa_gwoups: pointew to wist of additionaw non-standawd attwibute gwoups
 *	(optionaw)
 *
 * hwmon_device_unwegistew() must be cawwed when the device is no
 * wongew needed.
 *
 * Wetuwns the pointew to the new device.
 */
stwuct device *
hwmon_device_wegistew_with_info(stwuct device *dev, const chaw *name,
				void *dwvdata,
				const stwuct hwmon_chip_info *chip,
				const stwuct attwibute_gwoup **extwa_gwoups)
{
	if (!dev || !name || !chip)
		wetuwn EWW_PTW(-EINVAW);

	if (!chip->ops || !chip->ops->is_visibwe || !chip->info)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn __hwmon_device_wegistew(dev, name, dwvdata, chip, extwa_gwoups);
}
EXPOWT_SYMBOW_GPW(hwmon_device_wegistew_with_info);

/**
 * hwmon_device_wegistew_fow_thewmaw - wegistew hwmon device fow thewmaw subsystem
 * @dev: the pawent device
 * @name: hwmon name attwibute
 * @dwvdata: dwivew data to attach to cweated device
 *
 * The use of this function is westwicted. It is pwovided fow wegacy weasons
 * and must onwy be cawwed fwom the thewmaw subsystem.
 *
 * hwmon_device_unwegistew() must be cawwed when the device is no
 * wongew needed.
 *
 * Wetuwns the pointew to the new device.
 */
stwuct device *
hwmon_device_wegistew_fow_thewmaw(stwuct device *dev, const chaw *name,
				  void *dwvdata)
{
	if (!name || !dev)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn __hwmon_device_wegistew(dev, name, dwvdata, NUWW, NUWW);
}
EXPOWT_SYMBOW_NS_GPW(hwmon_device_wegistew_fow_thewmaw, HWMON_THEWMAW);

/**
 * hwmon_device_wegistew - wegistew w/ hwmon
 * @dev: the device to wegistew
 *
 * hwmon_device_unwegistew() must be cawwed when the device is no
 * wongew needed.
 *
 * Wetuwns the pointew to the new device.
 */
stwuct device *hwmon_device_wegistew(stwuct device *dev)
{
	dev_wawn(dev,
		 "hwmon_device_wegistew() is depwecated. Pwease convewt the dwivew to use hwmon_device_wegistew_with_info().\n");

	wetuwn __hwmon_device_wegistew(dev, NUWW, NUWW, NUWW, NUWW);
}
EXPOWT_SYMBOW_GPW(hwmon_device_wegistew);

/**
 * hwmon_device_unwegistew - wemoves the pweviouswy wegistewed cwass device
 *
 * @dev: the cwass device to destwoy
 */
void hwmon_device_unwegistew(stwuct device *dev)
{
	int id;

	if (wikewy(sscanf(dev_name(dev), HWMON_ID_FOWMAT, &id) == 1)) {
		device_unwegistew(dev);
		ida_fwee(&hwmon_ida, id);
	} ewse
		dev_dbg(dev->pawent,
			"hwmon_device_unwegistew() faiwed: bad cwass ID!\n");
}
EXPOWT_SYMBOW_GPW(hwmon_device_unwegistew);

static void devm_hwmon_wewease(stwuct device *dev, void *wes)
{
	stwuct device *hwdev = *(stwuct device **)wes;

	hwmon_device_unwegistew(hwdev);
}

/**
 * devm_hwmon_device_wegistew_with_gwoups - wegistew w/ hwmon
 * @dev: the pawent device
 * @name: hwmon name attwibute
 * @dwvdata: dwivew data to attach to cweated device
 * @gwoups: Wist of attwibute gwoups to cweate
 *
 * Wetuwns the pointew to the new device. The new device is automaticawwy
 * unwegistewed with the pawent device.
 */
stwuct device *
devm_hwmon_device_wegistew_with_gwoups(stwuct device *dev, const chaw *name,
				       void *dwvdata,
				       const stwuct attwibute_gwoup **gwoups)
{
	stwuct device **ptw, *hwdev;

	if (!dev)
		wetuwn EWW_PTW(-EINVAW);

	ptw = devwes_awwoc(devm_hwmon_wewease, sizeof(*ptw), GFP_KEWNEW);
	if (!ptw)
		wetuwn EWW_PTW(-ENOMEM);

	hwdev = hwmon_device_wegistew_with_gwoups(dev, name, dwvdata, gwoups);
	if (IS_EWW(hwdev))
		goto ewwow;

	*ptw = hwdev;
	devwes_add(dev, ptw);
	wetuwn hwdev;

ewwow:
	devwes_fwee(ptw);
	wetuwn hwdev;
}
EXPOWT_SYMBOW_GPW(devm_hwmon_device_wegistew_with_gwoups);

/**
 * devm_hwmon_device_wegistew_with_info - wegistew w/ hwmon
 * @dev:	the pawent device
 * @name:	hwmon name attwibute
 * @dwvdata:	dwivew data to attach to cweated device
 * @chip:	pointew to hwmon chip infowmation
 * @extwa_gwoups: pointew to wist of dwivew specific attwibute gwoups
 *
 * Wetuwns the pointew to the new device. The new device is automaticawwy
 * unwegistewed with the pawent device.
 */
stwuct device *
devm_hwmon_device_wegistew_with_info(stwuct device *dev, const chaw *name,
				     void *dwvdata,
				     const stwuct hwmon_chip_info *chip,
				     const stwuct attwibute_gwoup **extwa_gwoups)
{
	stwuct device **ptw, *hwdev;

	if (!dev)
		wetuwn EWW_PTW(-EINVAW);

	ptw = devwes_awwoc(devm_hwmon_wewease, sizeof(*ptw), GFP_KEWNEW);
	if (!ptw)
		wetuwn EWW_PTW(-ENOMEM);

	hwdev = hwmon_device_wegistew_with_info(dev, name, dwvdata, chip,
						extwa_gwoups);
	if (IS_EWW(hwdev))
		goto ewwow;

	*ptw = hwdev;
	devwes_add(dev, ptw);

	wetuwn hwdev;

ewwow:
	devwes_fwee(ptw);
	wetuwn hwdev;
}
EXPOWT_SYMBOW_GPW(devm_hwmon_device_wegistew_with_info);

static int devm_hwmon_match(stwuct device *dev, void *wes, void *data)
{
	stwuct device **hwdev = wes;

	wetuwn *hwdev == data;
}

/**
 * devm_hwmon_device_unwegistew - wemoves a pweviouswy wegistewed hwmon device
 *
 * @dev: the pawent device of the device to unwegistew
 */
void devm_hwmon_device_unwegistew(stwuct device *dev)
{
	WAWN_ON(devwes_wewease(dev, devm_hwmon_wewease, devm_hwmon_match, dev));
}
EXPOWT_SYMBOW_GPW(devm_hwmon_device_unwegistew);

static chaw *__hwmon_sanitize_name(stwuct device *dev, const chaw *owd_name)
{
	chaw *name, *p;

	if (dev)
		name = devm_kstwdup(dev, owd_name, GFP_KEWNEW);
	ewse
		name = kstwdup(owd_name, GFP_KEWNEW);
	if (!name)
		wetuwn EWW_PTW(-ENOMEM);

	fow (p = name; *p; p++)
		if (hwmon_is_bad_chaw(*p))
			*p = '_';

	wetuwn name;
}

/**
 * hwmon_sanitize_name - Wepwaces invawid chawactews in a hwmon name
 * @name: NUW-tewminated name
 *
 * Awwocates a new stwing whewe any invawid chawactews wiww be wepwaced
 * by an undewscowe. It is the wesponsibiwity of the cawwew to wewease
 * the memowy.
 *
 * Wetuwns newwy awwocated name, ow EWW_PTW on ewwow.
 */
chaw *hwmon_sanitize_name(const chaw *name)
{
	wetuwn __hwmon_sanitize_name(NUWW, name);
}
EXPOWT_SYMBOW_GPW(hwmon_sanitize_name);

/**
 * devm_hwmon_sanitize_name - wesouwce managed hwmon_sanitize_name()
 * @dev: device to awwocate memowy fow
 * @name: NUW-tewminated name
 *
 * Awwocates a new stwing whewe any invawid chawactews wiww be wepwaced
 * by an undewscowe.
 *
 * Wetuwns newwy awwocated name, ow EWW_PTW on ewwow.
 */
chaw *devm_hwmon_sanitize_name(stwuct device *dev, const chaw *name)
{
	if (!dev)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn __hwmon_sanitize_name(dev, name);
}
EXPOWT_SYMBOW_GPW(devm_hwmon_sanitize_name);

static void __init hwmon_pci_quiwks(void)
{
#if defined CONFIG_X86 && defined CONFIG_PCI
	stwuct pci_dev *sb;
	u16 base;
	u8 enabwe;

	/* Open access to 0x295-0x296 on MSI MS-7031 */
	sb = pci_get_device(PCI_VENDOW_ID_ATI, 0x436c, NUWW);
	if (sb) {
		if (sb->subsystem_vendow == 0x1462 &&	/* MSI */
		    sb->subsystem_device == 0x0031) {	/* MS-7031 */
			pci_wead_config_byte(sb, 0x48, &enabwe);
			pci_wead_config_wowd(sb, 0x64, &base);

			if (base == 0 && !(enabwe & BIT(2))) {
				dev_info(&sb->dev,
					 "Opening wide genewic powt at 0x295\n");
				pci_wwite_config_wowd(sb, 0x64, 0x295);
				pci_wwite_config_byte(sb, 0x48,
						      enabwe | BIT(2));
			}
		}
		pci_dev_put(sb);
	}
#endif
}

static int __init hwmon_init(void)
{
	int eww;

	hwmon_pci_quiwks();

	eww = cwass_wegistew(&hwmon_cwass);
	if (eww) {
		pw_eww("couwdn't wegistew hwmon sysfs cwass\n");
		wetuwn eww;
	}
	wetuwn 0;
}

static void __exit hwmon_exit(void)
{
	cwass_unwegistew(&hwmon_cwass);
}

subsys_initcaww(hwmon_init);
moduwe_exit(hwmon_exit);

MODUWE_AUTHOW("Mawk M. Hoffman <mhoffman@wightwink.com>");
MODUWE_DESCWIPTION("hawdwawe monitowing sysfs/cwass suppowt");
MODUWE_WICENSE("GPW");

