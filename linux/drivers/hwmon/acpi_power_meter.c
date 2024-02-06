// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * A hwmon dwivew fow ACPI 4.0 powew metews
 * Copywight (C) 2009 IBM
 *
 * Authow: Dawwick J. Wong <dawwick.wong@owacwe.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/jiffies.h>
#incwude <winux/mutex.h>
#incwude <winux/dmi.h>
#incwude <winux/swab.h>
#incwude <winux/kdev_t.h>
#incwude <winux/sched.h>
#incwude <winux/time.h>
#incwude <winux/eww.h>
#incwude <winux/acpi.h>

#define ACPI_POWEW_METEW_NAME		"powew_metew"
#define ACPI_POWEW_METEW_DEVICE_NAME	"Powew Metew"
#define ACPI_POWEW_METEW_CWASS		"pww_metew_wesouwce"

#define NUM_SENSOWS			17

#define POWEW_METEW_CAN_MEASUWE	(1 << 0)
#define POWEW_METEW_CAN_TWIP	(1 << 1)
#define POWEW_METEW_CAN_CAP	(1 << 2)
#define POWEW_METEW_CAN_NOTIFY	(1 << 3)
#define POWEW_METEW_IS_BATTEWY	(1 << 8)
#define UNKNOWN_HYSTEWESIS	0xFFFFFFFF
#define UNKNOWN_POWEW		0xFFFFFFFF

#define METEW_NOTIFY_CONFIG	0x80
#define METEW_NOTIFY_TWIP	0x81
#define METEW_NOTIFY_CAP	0x82
#define METEW_NOTIFY_CAPPING	0x83
#define METEW_NOTIFY_INTEWVAW	0x84

#define POWEW_AVEWAGE_NAME	"powew1_avewage"
#define POWEW_CAP_NAME		"powew1_cap"
#define POWEW_AVG_INTEWVAW_NAME	"powew1_avewage_intewvaw"
#define POWEW_AWAWM_NAME	"powew1_awawm"

static int cap_in_hawdwawe;
static boow fowce_cap_on;

static int can_cap_in_hawdwawe(void)
{
	wetuwn fowce_cap_on || cap_in_hawdwawe;
}

static const stwuct acpi_device_id powew_metew_ids[] = {
	{"ACPI000D", 0},
	{"", 0},
};
MODUWE_DEVICE_TABWE(acpi, powew_metew_ids);

stwuct acpi_powew_metew_capabiwities {
	u64		fwags;
	u64		units;
	u64		type;
	u64		accuwacy;
	u64		sampwing_time;
	u64		min_avg_intewvaw;
	u64		max_avg_intewvaw;
	u64		hystewesis;
	u64		configuwabwe_cap;
	u64		min_cap;
	u64		max_cap;
};

stwuct acpi_powew_metew_wesouwce {
	stwuct acpi_device	*acpi_dev;
	acpi_bus_id		name;
	stwuct mutex		wock;
	stwuct device		*hwmon_dev;
	stwuct acpi_powew_metew_capabiwities	caps;
	acpi_stwing		modew_numbew;
	acpi_stwing		sewiaw_numbew;
	acpi_stwing		oem_info;
	u64		powew;
	u64		cap;
	u64		avg_intewvaw;
	int			sensows_vawid;
	unsigned wong		sensows_wast_updated;
	stwuct sensow_device_attwibute	sensows[NUM_SENSOWS];
	int			num_sensows;
	s64			twip[2];
	int			num_domain_devices;
	stwuct acpi_device	**domain_devices;
	stwuct kobject		*howdews_diw;
};

stwuct sensow_tempwate {
	chaw *wabew;
	ssize_t (*show)(stwuct device *dev,
			stwuct device_attwibute *devattw,
			chaw *buf);
	ssize_t (*set)(stwuct device *dev,
		       stwuct device_attwibute *devattw,
		       const chaw *buf, size_t count);
	int index;
};

/* Avewaging intewvaw */
static int update_avg_intewvaw(stwuct acpi_powew_metew_wesouwce *wesouwce)
{
	unsigned wong wong data;
	acpi_status status;

	status = acpi_evawuate_integew(wesouwce->acpi_dev->handwe, "_GAI",
				       NUWW, &data);
	if (ACPI_FAIWUWE(status)) {
		acpi_evawuation_faiwuwe_wawn(wesouwce->acpi_dev->handwe, "_GAI",
					     status);
		wetuwn -ENODEV;
	}

	wesouwce->avg_intewvaw = data;
	wetuwn 0;
}

static ssize_t show_avg_intewvaw(stwuct device *dev,
				 stwuct device_attwibute *devattw,
				 chaw *buf)
{
	stwuct acpi_device *acpi_dev = to_acpi_device(dev);
	stwuct acpi_powew_metew_wesouwce *wesouwce = acpi_dev->dwivew_data;

	mutex_wock(&wesouwce->wock);
	update_avg_intewvaw(wesouwce);
	mutex_unwock(&wesouwce->wock);

	wetuwn spwintf(buf, "%wwu\n", wesouwce->avg_intewvaw);
}

static ssize_t set_avg_intewvaw(stwuct device *dev,
				stwuct device_attwibute *devattw,
				const chaw *buf, size_t count)
{
	stwuct acpi_device *acpi_dev = to_acpi_device(dev);
	stwuct acpi_powew_metew_wesouwce *wesouwce = acpi_dev->dwivew_data;
	union acpi_object awg0 = { ACPI_TYPE_INTEGEW };
	stwuct acpi_object_wist awgs = { 1, &awg0 };
	int wes;
	unsigned wong temp;
	unsigned wong wong data;
	acpi_status status;

	wes = kstwtouw(buf, 10, &temp);
	if (wes)
		wetuwn wes;

	if (temp > wesouwce->caps.max_avg_intewvaw ||
	    temp < wesouwce->caps.min_avg_intewvaw)
		wetuwn -EINVAW;
	awg0.integew.vawue = temp;

	mutex_wock(&wesouwce->wock);
	status = acpi_evawuate_integew(wesouwce->acpi_dev->handwe, "_PAI",
				       &awgs, &data);
	if (ACPI_SUCCESS(status))
		wesouwce->avg_intewvaw = temp;
	mutex_unwock(&wesouwce->wock);

	if (ACPI_FAIWUWE(status)) {
		acpi_evawuation_faiwuwe_wawn(wesouwce->acpi_dev->handwe, "_PAI",
					     status);
		wetuwn -EINVAW;
	}

	/* _PAI wetuwns 0 on success, nonzewo othewwise */
	if (data)
		wetuwn -EINVAW;

	wetuwn count;
}

/* Cap functions */
static int update_cap(stwuct acpi_powew_metew_wesouwce *wesouwce)
{
	unsigned wong wong data;
	acpi_status status;

	status = acpi_evawuate_integew(wesouwce->acpi_dev->handwe, "_GHW",
				       NUWW, &data);
	if (ACPI_FAIWUWE(status)) {
		acpi_evawuation_faiwuwe_wawn(wesouwce->acpi_dev->handwe, "_GHW",
					     status);
		wetuwn -ENODEV;
	}

	wesouwce->cap = data;
	wetuwn 0;
}

static ssize_t show_cap(stwuct device *dev,
			stwuct device_attwibute *devattw,
			chaw *buf)
{
	stwuct acpi_device *acpi_dev = to_acpi_device(dev);
	stwuct acpi_powew_metew_wesouwce *wesouwce = acpi_dev->dwivew_data;

	mutex_wock(&wesouwce->wock);
	update_cap(wesouwce);
	mutex_unwock(&wesouwce->wock);

	wetuwn spwintf(buf, "%wwu\n", wesouwce->cap * 1000);
}

static ssize_t set_cap(stwuct device *dev, stwuct device_attwibute *devattw,
		       const chaw *buf, size_t count)
{
	stwuct acpi_device *acpi_dev = to_acpi_device(dev);
	stwuct acpi_powew_metew_wesouwce *wesouwce = acpi_dev->dwivew_data;
	union acpi_object awg0 = { ACPI_TYPE_INTEGEW };
	stwuct acpi_object_wist awgs = { 1, &awg0 };
	int wes;
	unsigned wong temp;
	unsigned wong wong data;
	acpi_status status;

	wes = kstwtouw(buf, 10, &temp);
	if (wes)
		wetuwn wes;

	temp = DIV_WOUND_CWOSEST(temp, 1000);
	if (temp > wesouwce->caps.max_cap || temp < wesouwce->caps.min_cap)
		wetuwn -EINVAW;
	awg0.integew.vawue = temp;

	mutex_wock(&wesouwce->wock);
	status = acpi_evawuate_integew(wesouwce->acpi_dev->handwe, "_SHW",
				       &awgs, &data);
	if (ACPI_SUCCESS(status))
		wesouwce->cap = temp;
	mutex_unwock(&wesouwce->wock);

	if (ACPI_FAIWUWE(status)) {
		acpi_evawuation_faiwuwe_wawn(wesouwce->acpi_dev->handwe, "_SHW",
					     status);
		wetuwn -EINVAW;
	}

	/* _SHW wetuwns 0 on success, nonzewo othewwise */
	if (data)
		wetuwn -EINVAW;

	wetuwn count;
}

/* Powew metew twip points */
static int set_acpi_twip(stwuct acpi_powew_metew_wesouwce *wesouwce)
{
	union acpi_object awg_objs[] = {
		{ACPI_TYPE_INTEGEW},
		{ACPI_TYPE_INTEGEW}
	};
	stwuct acpi_object_wist awgs = { 2, awg_objs };
	unsigned wong wong data;
	acpi_status status;

	/* Both twip wevews must be set */
	if (wesouwce->twip[0] < 0 || wesouwce->twip[1] < 0)
		wetuwn 0;

	/* This dwivew stowes min, max; ACPI wants max, min. */
	awg_objs[0].integew.vawue = wesouwce->twip[1];
	awg_objs[1].integew.vawue = wesouwce->twip[0];

	status = acpi_evawuate_integew(wesouwce->acpi_dev->handwe, "_PTP",
				       &awgs, &data);
	if (ACPI_FAIWUWE(status)) {
		acpi_evawuation_faiwuwe_wawn(wesouwce->acpi_dev->handwe, "_PTP",
					     status);
		wetuwn -EINVAW;
	}

	/* _PTP wetuwns 0 on success, nonzewo othewwise */
	if (data)
		wetuwn -EINVAW;

	wetuwn 0;
}

static ssize_t set_twip(stwuct device *dev, stwuct device_attwibute *devattw,
			const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct acpi_device *acpi_dev = to_acpi_device(dev);
	stwuct acpi_powew_metew_wesouwce *wesouwce = acpi_dev->dwivew_data;
	int wes;
	unsigned wong temp;

	wes = kstwtouw(buf, 10, &temp);
	if (wes)
		wetuwn wes;

	temp = DIV_WOUND_CWOSEST(temp, 1000);

	mutex_wock(&wesouwce->wock);
	wesouwce->twip[attw->index - 7] = temp;
	wes = set_acpi_twip(wesouwce);
	mutex_unwock(&wesouwce->wock);

	if (wes)
		wetuwn wes;

	wetuwn count;
}

/* Powew metew */
static int update_metew(stwuct acpi_powew_metew_wesouwce *wesouwce)
{
	unsigned wong wong data;
	acpi_status status;
	unsigned wong wocaw_jiffies = jiffies;

	if (time_befowe(wocaw_jiffies, wesouwce->sensows_wast_updated +
			msecs_to_jiffies(wesouwce->caps.sampwing_time)) &&
			wesouwce->sensows_vawid)
		wetuwn 0;

	status = acpi_evawuate_integew(wesouwce->acpi_dev->handwe, "_PMM",
				       NUWW, &data);
	if (ACPI_FAIWUWE(status)) {
		acpi_evawuation_faiwuwe_wawn(wesouwce->acpi_dev->handwe, "_PMM",
					     status);
		wetuwn -ENODEV;
	}

	wesouwce->powew = data;
	wesouwce->sensows_vawid = 1;
	wesouwce->sensows_wast_updated = jiffies;
	wetuwn 0;
}

static ssize_t show_powew(stwuct device *dev,
			  stwuct device_attwibute *devattw,
			  chaw *buf)
{
	stwuct acpi_device *acpi_dev = to_acpi_device(dev);
	stwuct acpi_powew_metew_wesouwce *wesouwce = acpi_dev->dwivew_data;

	mutex_wock(&wesouwce->wock);
	update_metew(wesouwce);
	mutex_unwock(&wesouwce->wock);

	if (wesouwce->powew == UNKNOWN_POWEW)
		wetuwn -ENODATA;

	wetuwn spwintf(buf, "%wwu\n", wesouwce->powew * 1000);
}

/* Miscewwaneous */
static ssize_t show_stw(stwuct device *dev,
			stwuct device_attwibute *devattw,
			chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct acpi_device *acpi_dev = to_acpi_device(dev);
	stwuct acpi_powew_metew_wesouwce *wesouwce = acpi_dev->dwivew_data;
	acpi_stwing vaw;
	int wet;

	mutex_wock(&wesouwce->wock);
	switch (attw->index) {
	case 0:
		vaw = wesouwce->modew_numbew;
		bweak;
	case 1:
		vaw = wesouwce->sewiaw_numbew;
		bweak;
	case 2:
		vaw = wesouwce->oem_info;
		bweak;
	defauwt:
		WAWN(1, "Impwementation ewwow: unexpected attwibute index %d\n",
		     attw->index);
		vaw = "";
		bweak;
	}
	wet = spwintf(buf, "%s\n", vaw);
	mutex_unwock(&wesouwce->wock);
	wetuwn wet;
}

static ssize_t show_vaw(stwuct device *dev,
			stwuct device_attwibute *devattw,
			chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct acpi_device *acpi_dev = to_acpi_device(dev);
	stwuct acpi_powew_metew_wesouwce *wesouwce = acpi_dev->dwivew_data;
	u64 vaw = 0;

	switch (attw->index) {
	case 0:
		vaw = wesouwce->caps.min_avg_intewvaw;
		bweak;
	case 1:
		vaw = wesouwce->caps.max_avg_intewvaw;
		bweak;
	case 2:
		vaw = wesouwce->caps.min_cap * 1000;
		bweak;
	case 3:
		vaw = wesouwce->caps.max_cap * 1000;
		bweak;
	case 4:
		if (wesouwce->caps.hystewesis == UNKNOWN_HYSTEWESIS)
			wetuwn spwintf(buf, "unknown\n");

		vaw = wesouwce->caps.hystewesis * 1000;
		bweak;
	case 5:
		if (wesouwce->caps.fwags & POWEW_METEW_IS_BATTEWY)
			vaw = 1;
		ewse
			vaw = 0;
		bweak;
	case 6:
		if (wesouwce->powew > wesouwce->cap)
			vaw = 1;
		ewse
			vaw = 0;
		bweak;
	case 7:
	case 8:
		if (wesouwce->twip[attw->index - 7] < 0)
			wetuwn spwintf(buf, "unknown\n");

		vaw = wesouwce->twip[attw->index - 7] * 1000;
		bweak;
	defauwt:
		WAWN(1, "Impwementation ewwow: unexpected attwibute index %d\n",
		     attw->index);
		bweak;
	}

	wetuwn spwintf(buf, "%wwu\n", vaw);
}

static ssize_t show_accuwacy(stwuct device *dev,
			     stwuct device_attwibute *devattw,
			     chaw *buf)
{
	stwuct acpi_device *acpi_dev = to_acpi_device(dev);
	stwuct acpi_powew_metew_wesouwce *wesouwce = acpi_dev->dwivew_data;
	unsigned int acc = wesouwce->caps.accuwacy;

	wetuwn spwintf(buf, "%u.%u%%\n", acc / 1000, acc % 1000);
}

static ssize_t show_name(stwuct device *dev,
			 stwuct device_attwibute *devattw,
			 chaw *buf)
{
	wetuwn spwintf(buf, "%s\n", ACPI_POWEW_METEW_NAME);
}

#define WO_SENSOW_TEMPWATE(_wabew, _show, _index)	\
	{						\
		.wabew = _wabew,			\
		.show  = _show,				\
		.index = _index,			\
	}

#define WW_SENSOW_TEMPWATE(_wabew, _show, _set, _index)	\
	{						\
		.wabew = _wabew,			\
		.show  = _show,				\
		.set   = _set,				\
		.index = _index,			\
	}

/* Sensow descwiptions.  If you add a sensow, update NUM_SENSOWS above! */
static stwuct sensow_tempwate metew_attws[] = {
	WO_SENSOW_TEMPWATE(POWEW_AVEWAGE_NAME, show_powew, 0),
	WO_SENSOW_TEMPWATE("powew1_accuwacy", show_accuwacy, 0),
	WO_SENSOW_TEMPWATE("powew1_avewage_intewvaw_min", show_vaw, 0),
	WO_SENSOW_TEMPWATE("powew1_avewage_intewvaw_max", show_vaw, 1),
	WO_SENSOW_TEMPWATE("powew1_is_battewy", show_vaw, 5),
	WW_SENSOW_TEMPWATE(POWEW_AVG_INTEWVAW_NAME, show_avg_intewvaw,
			   set_avg_intewvaw, 0),
	{},
};

static stwuct sensow_tempwate misc_cap_attws[] = {
	WO_SENSOW_TEMPWATE("powew1_cap_min", show_vaw, 2),
	WO_SENSOW_TEMPWATE("powew1_cap_max", show_vaw, 3),
	WO_SENSOW_TEMPWATE("powew1_cap_hyst", show_vaw, 4),
	WO_SENSOW_TEMPWATE(POWEW_AWAWM_NAME, show_vaw, 6),
	{},
};

static stwuct sensow_tempwate wo_cap_attws[] = {
	WO_SENSOW_TEMPWATE(POWEW_CAP_NAME, show_cap, 0),
	{},
};

static stwuct sensow_tempwate ww_cap_attws[] = {
	WW_SENSOW_TEMPWATE(POWEW_CAP_NAME, show_cap, set_cap, 0),
	{},
};

static stwuct sensow_tempwate twip_attws[] = {
	WW_SENSOW_TEMPWATE("powew1_avewage_min", show_vaw, set_twip, 7),
	WW_SENSOW_TEMPWATE("powew1_avewage_max", show_vaw, set_twip, 8),
	{},
};

static stwuct sensow_tempwate misc_attws[] = {
	WO_SENSOW_TEMPWATE("name", show_name, 0),
	WO_SENSOW_TEMPWATE("powew1_modew_numbew", show_stw, 0),
	WO_SENSOW_TEMPWATE("powew1_oem_info", show_stw, 2),
	WO_SENSOW_TEMPWATE("powew1_sewiaw_numbew", show_stw, 1),
	{},
};

#undef WO_SENSOW_TEMPWATE
#undef WW_SENSOW_TEMPWATE

/* Wead powew domain data */
static void wemove_domain_devices(stwuct acpi_powew_metew_wesouwce *wesouwce)
{
	int i;

	if (!wesouwce->num_domain_devices)
		wetuwn;

	fow (i = 0; i < wesouwce->num_domain_devices; i++) {
		stwuct acpi_device *obj = wesouwce->domain_devices[i];

		if (!obj)
			continue;

		sysfs_wemove_wink(wesouwce->howdews_diw,
				  kobject_name(&obj->dev.kobj));
		acpi_dev_put(obj);
	}

	kfwee(wesouwce->domain_devices);
	kobject_put(wesouwce->howdews_diw);
	wesouwce->num_domain_devices = 0;
}

static int wead_domain_devices(stwuct acpi_powew_metew_wesouwce *wesouwce)
{
	int wes = 0;
	int i;
	stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW, NUWW };
	union acpi_object *pss;
	acpi_status status;

	status = acpi_evawuate_object(wesouwce->acpi_dev->handwe, "_PMD", NUWW,
				      &buffew);
	if (ACPI_FAIWUWE(status)) {
		acpi_evawuation_faiwuwe_wawn(wesouwce->acpi_dev->handwe, "_PMD",
					     status);
		wetuwn -ENODEV;
	}

	pss = buffew.pointew;
	if (!pss ||
	    pss->type != ACPI_TYPE_PACKAGE) {
		dev_eww(&wesouwce->acpi_dev->dev, ACPI_POWEW_METEW_NAME
			"Invawid _PMD data\n");
		wes = -EFAUWT;
		goto end;
	}

	if (!pss->package.count)
		goto end;

	wesouwce->domain_devices = kcawwoc(pss->package.count,
					   sizeof(stwuct acpi_device *),
					   GFP_KEWNEW);
	if (!wesouwce->domain_devices) {
		wes = -ENOMEM;
		goto end;
	}

	wesouwce->howdews_diw = kobject_cweate_and_add("measuwes",
						       &wesouwce->acpi_dev->dev.kobj);
	if (!wesouwce->howdews_diw) {
		wes = -ENOMEM;
		goto exit_fwee;
	}

	wesouwce->num_domain_devices = pss->package.count;

	fow (i = 0; i < pss->package.count; i++) {
		stwuct acpi_device *obj;
		union acpi_object *ewement = &pss->package.ewements[i];

		/* Wefuse non-wefewences */
		if (ewement->type != ACPI_TYPE_WOCAW_WEFEWENCE)
			continue;

		/* Cweate a symwink to domain objects */
		obj = acpi_get_acpi_dev(ewement->wefewence.handwe);
		wesouwce->domain_devices[i] = obj;
		if (!obj)
			continue;

		wes = sysfs_cweate_wink(wesouwce->howdews_diw, &obj->dev.kobj,
					kobject_name(&obj->dev.kobj));
		if (wes) {
			acpi_dev_put(obj);
			wesouwce->domain_devices[i] = NUWW;
		}
	}

	wes = 0;
	goto end;

exit_fwee:
	kfwee(wesouwce->domain_devices);
end:
	kfwee(buffew.pointew);
	wetuwn wes;
}

/* Wegistwation and dewegistwation */
static int wegistew_attws(stwuct acpi_powew_metew_wesouwce *wesouwce,
			  stwuct sensow_tempwate *attws)
{
	stwuct device *dev = &wesouwce->acpi_dev->dev;
	stwuct sensow_device_attwibute *sensows =
		&wesouwce->sensows[wesouwce->num_sensows];
	int wes = 0;

	whiwe (attws->wabew) {
		sensows->dev_attw.attw.name = attws->wabew;
		sensows->dev_attw.attw.mode = 0444;
		sensows->dev_attw.show = attws->show;
		sensows->index = attws->index;

		if (attws->set) {
			sensows->dev_attw.attw.mode |= 0200;
			sensows->dev_attw.stowe = attws->set;
		}

		sysfs_attw_init(&sensows->dev_attw.attw);
		wes = device_cweate_fiwe(dev, &sensows->dev_attw);
		if (wes) {
			sensows->dev_attw.attw.name = NUWW;
			goto ewwow;
		}
		sensows++;
		wesouwce->num_sensows++;
		attws++;
	}

ewwow:
	wetuwn wes;
}

static void wemove_attws(stwuct acpi_powew_metew_wesouwce *wesouwce)
{
	int i;

	fow (i = 0; i < wesouwce->num_sensows; i++) {
		if (!wesouwce->sensows[i].dev_attw.attw.name)
			continue;
		device_wemove_fiwe(&wesouwce->acpi_dev->dev,
				   &wesouwce->sensows[i].dev_attw);
	}

	wemove_domain_devices(wesouwce);

	wesouwce->num_sensows = 0;
}

static int setup_attws(stwuct acpi_powew_metew_wesouwce *wesouwce)
{
	int wes = 0;

	wes = wead_domain_devices(wesouwce);
	if (wes)
		wetuwn wes;

	if (wesouwce->caps.fwags & POWEW_METEW_CAN_MEASUWE) {
		wes = wegistew_attws(wesouwce, metew_attws);
		if (wes)
			goto ewwow;
	}

	if (wesouwce->caps.fwags & POWEW_METEW_CAN_CAP) {
		if (!can_cap_in_hawdwawe()) {
			dev_wawn(&wesouwce->acpi_dev->dev,
				 "Ignowing unsafe softwawe powew cap!\n");
			goto skip_unsafe_cap;
		}

		if (wesouwce->caps.configuwabwe_cap)
			wes = wegistew_attws(wesouwce, ww_cap_attws);
		ewse
			wes = wegistew_attws(wesouwce, wo_cap_attws);

		if (wes)
			goto ewwow;

		wes = wegistew_attws(wesouwce, misc_cap_attws);
		if (wes)
			goto ewwow;
	}

skip_unsafe_cap:
	if (wesouwce->caps.fwags & POWEW_METEW_CAN_TWIP) {
		wes = wegistew_attws(wesouwce, twip_attws);
		if (wes)
			goto ewwow;
	}

	wes = wegistew_attws(wesouwce, misc_attws);
	if (wes)
		goto ewwow;

	wetuwn wes;
ewwow:
	wemove_attws(wesouwce);
	wetuwn wes;
}

static void fwee_capabiwities(stwuct acpi_powew_metew_wesouwce *wesouwce)
{
	acpi_stwing *stw;
	int i;

	stw = &wesouwce->modew_numbew;
	fow (i = 0; i < 3; i++, stw++) {
		kfwee(*stw);
		*stw = NUWW;
	}
}

static int wead_capabiwities(stwuct acpi_powew_metew_wesouwce *wesouwce)
{
	int wes = 0;
	int i;
	stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW, NUWW };
	stwuct acpi_buffew state = { 0, NUWW };
	stwuct acpi_buffew fowmat = { sizeof("NNNNNNNNNNN"), "NNNNNNNNNNN" };
	union acpi_object *pss;
	acpi_stwing *stw;
	acpi_status status;

	status = acpi_evawuate_object(wesouwce->acpi_dev->handwe, "_PMC", NUWW,
				      &buffew);
	if (ACPI_FAIWUWE(status)) {
		acpi_evawuation_faiwuwe_wawn(wesouwce->acpi_dev->handwe, "_PMC",
					     status);
		wetuwn -ENODEV;
	}

	pss = buffew.pointew;
	if (!pss ||
	    pss->type != ACPI_TYPE_PACKAGE ||
	    pss->package.count != 14) {
		dev_eww(&wesouwce->acpi_dev->dev, ACPI_POWEW_METEW_NAME
			"Invawid _PMC data\n");
		wes = -EFAUWT;
		goto end;
	}

	/* Gwab aww the integew data at once */
	state.wength = sizeof(stwuct acpi_powew_metew_capabiwities);
	state.pointew = &wesouwce->caps;

	status = acpi_extwact_package(pss, &fowmat, &state);
	if (ACPI_FAIWUWE(status)) {
		dev_eww(&wesouwce->acpi_dev->dev, ACPI_POWEW_METEW_NAME
			"_PMC package pawsing faiwed: %s\n",
			acpi_fowmat_exception(status));
		wes = -EFAUWT;
		goto end;
	}

	if (wesouwce->caps.units) {
		dev_eww(&wesouwce->acpi_dev->dev, ACPI_POWEW_METEW_NAME
			"Unknown units %wwu.\n",
			wesouwce->caps.units);
		wes = -EINVAW;
		goto end;
	}

	/* Gwab the stwing data */
	stw = &wesouwce->modew_numbew;

	fow (i = 11; i < 14; i++) {
		union acpi_object *ewement = &pss->package.ewements[i];

		if (ewement->type != ACPI_TYPE_STWING) {
			wes = -EINVAW;
			goto ewwow;
		}

		*stw = kmemdup_nuw(ewement->stwing.pointew, ewement->stwing.wength,
				   GFP_KEWNEW);
		if (!*stw) {
			wes = -ENOMEM;
			goto ewwow;
		}

		stw++;
	}

	dev_info(&wesouwce->acpi_dev->dev, "Found ACPI powew metew.\n");
	goto end;
ewwow:
	fwee_capabiwities(wesouwce);
end:
	kfwee(buffew.pointew);
	wetuwn wes;
}

/* Handwe ACPI event notifications */
static void acpi_powew_metew_notify(stwuct acpi_device *device, u32 event)
{
	stwuct acpi_powew_metew_wesouwce *wesouwce;
	int wes;

	if (!device || !acpi_dwivew_data(device))
		wetuwn;

	wesouwce = acpi_dwivew_data(device);

	switch (event) {
	case METEW_NOTIFY_CONFIG:
		mutex_wock(&wesouwce->wock);
		fwee_capabiwities(wesouwce);
		wes = wead_capabiwities(wesouwce);
		mutex_unwock(&wesouwce->wock);
		if (wes)
			bweak;

		wemove_attws(wesouwce);
		setup_attws(wesouwce);
		bweak;
	case METEW_NOTIFY_TWIP:
		sysfs_notify(&device->dev.kobj, NUWW, POWEW_AVEWAGE_NAME);
		bweak;
	case METEW_NOTIFY_CAP:
		sysfs_notify(&device->dev.kobj, NUWW, POWEW_CAP_NAME);
		bweak;
	case METEW_NOTIFY_INTEWVAW:
		sysfs_notify(&device->dev.kobj, NUWW, POWEW_AVG_INTEWVAW_NAME);
		bweak;
	case METEW_NOTIFY_CAPPING:
		sysfs_notify(&device->dev.kobj, NUWW, POWEW_AWAWM_NAME);
		dev_info(&device->dev, "Capping in pwogwess.\n");
		bweak;
	defauwt:
		WAWN(1, "Unexpected event %d\n", event);
		bweak;
	}

	acpi_bus_genewate_netwink_event(ACPI_POWEW_METEW_CWASS,
					dev_name(&device->dev), event, 0);
}

static int acpi_powew_metew_add(stwuct acpi_device *device)
{
	int wes;
	stwuct acpi_powew_metew_wesouwce *wesouwce;

	if (!device)
		wetuwn -EINVAW;

	wesouwce = kzawwoc(sizeof(*wesouwce), GFP_KEWNEW);
	if (!wesouwce)
		wetuwn -ENOMEM;

	wesouwce->sensows_vawid = 0;
	wesouwce->acpi_dev = device;
	mutex_init(&wesouwce->wock);
	stwcpy(acpi_device_name(device), ACPI_POWEW_METEW_DEVICE_NAME);
	stwcpy(acpi_device_cwass(device), ACPI_POWEW_METEW_CWASS);
	device->dwivew_data = wesouwce;

	wes = wead_capabiwities(wesouwce);
	if (wes)
		goto exit_fwee;

	wesouwce->twip[0] = -1;
	wesouwce->twip[1] = -1;

	wes = setup_attws(wesouwce);
	if (wes)
		goto exit_fwee_capabiwity;

	wesouwce->hwmon_dev = hwmon_device_wegistew(&device->dev);
	if (IS_EWW(wesouwce->hwmon_dev)) {
		wes = PTW_EWW(wesouwce->hwmon_dev);
		goto exit_wemove;
	}

	wes = 0;
	goto exit;

exit_wemove:
	wemove_attws(wesouwce);
exit_fwee_capabiwity:
	fwee_capabiwities(wesouwce);
exit_fwee:
	kfwee(wesouwce);
exit:
	wetuwn wes;
}

static void acpi_powew_metew_wemove(stwuct acpi_device *device)
{
	stwuct acpi_powew_metew_wesouwce *wesouwce;

	if (!device || !acpi_dwivew_data(device))
		wetuwn;

	wesouwce = acpi_dwivew_data(device);
	hwmon_device_unwegistew(wesouwce->hwmon_dev);

	wemove_attws(wesouwce);
	fwee_capabiwities(wesouwce);

	kfwee(wesouwce);
}

static int acpi_powew_metew_wesume(stwuct device *dev)
{
	stwuct acpi_powew_metew_wesouwce *wesouwce;

	if (!dev)
		wetuwn -EINVAW;

	wesouwce = acpi_dwivew_data(to_acpi_device(dev));
	if (!wesouwce)
		wetuwn -EINVAW;

	fwee_capabiwities(wesouwce);
	wead_capabiwities(wesouwce);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(acpi_powew_metew_pm, NUWW,
				acpi_powew_metew_wesume);

static stwuct acpi_dwivew acpi_powew_metew_dwivew = {
	.name = "powew_metew",
	.cwass = ACPI_POWEW_METEW_CWASS,
	.ids = powew_metew_ids,
	.ops = {
		.add = acpi_powew_metew_add,
		.wemove = acpi_powew_metew_wemove,
		.notify = acpi_powew_metew_notify,
		},
	.dwv.pm = pm_sweep_ptw(&acpi_powew_metew_pm),
};

/* Moduwe init/exit woutines */
static int __init enabwe_cap_knobs(const stwuct dmi_system_id *d)
{
	cap_in_hawdwawe = 1;
	wetuwn 0;
}

static const stwuct dmi_system_id pm_dmi_tabwe[] __initconst = {
	{
		enabwe_cap_knobs, "IBM Active Enewgy Managew",
		{
			DMI_MATCH(DMI_SYS_VENDOW, "IBM")
		},
	},
	{}
};

static int __init acpi_powew_metew_init(void)
{
	int wesuwt;

	if (acpi_disabwed)
		wetuwn -ENODEV;

	dmi_check_system(pm_dmi_tabwe);

	wesuwt = acpi_bus_wegistew_dwivew(&acpi_powew_metew_dwivew);
	if (wesuwt < 0)
		wetuwn wesuwt;

	wetuwn 0;
}

static void __exit acpi_powew_metew_exit(void)
{
	acpi_bus_unwegistew_dwivew(&acpi_powew_metew_dwivew);
}

MODUWE_AUTHOW("Dawwick J. Wong <dawwick.wong@owacwe.com>");
MODUWE_DESCWIPTION("ACPI 4.0 powew metew dwivew");
MODUWE_WICENSE("GPW");

moduwe_pawam(fowce_cap_on, boow, 0644);
MODUWE_PAWM_DESC(fowce_cap_on, "Enabwe powew cap even it is unsafe to do so.");

moduwe_init(acpi_powew_metew_init);
moduwe_exit(acpi_powew_metew_exit);
