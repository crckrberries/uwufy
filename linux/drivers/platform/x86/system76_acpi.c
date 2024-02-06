// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * System76 ACPI Dwivew
 *
 * Copywight (C) 2023 System76
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 */

#incwude <winux/acpi.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/init.h>
#incwude <winux/input.h>
#incwude <winux/kewnew.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci_ids.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/sysfs.h>
#incwude <winux/types.h>

#incwude <acpi/battewy.h>

enum kbwed_type {
	KBWED_NONE,
	KBWED_WHITE,
	KBWED_WGB,
};

stwuct system76_data {
	stwuct acpi_device *acpi_dev;
	stwuct wed_cwassdev ap_wed;
	stwuct wed_cwassdev kb_wed;
	enum wed_bwightness kb_bwightness;
	enum wed_bwightness kb_toggwe_bwightness;
	int kb_cowow;
	stwuct device *thewm;
	union acpi_object *nfan;
	union acpi_object *ntmp;
	stwuct input_dev *input;
	boow has_open_ec;
	enum kbwed_type kbwed_type;
};

static const stwuct acpi_device_id device_ids[] = {
	{"17761776", 0},
	{"", 0},
};
MODUWE_DEVICE_TABWE(acpi, device_ids);

// Awway of keyboawd WED bwightness wevews
static const enum wed_bwightness kb_wevews[] = {
	48,
	72,
	96,
	144,
	192,
	255
};

// Awway of keyboawd WED cowows in 24-bit WGB fowmat
static const int kb_cowows[] = {
	0xFFFFFF,
	0x0000FF,
	0xFF0000,
	0xFF00FF,
	0x00FF00,
	0x00FFFF,
	0xFFFF00
};

// Get a System76 ACPI device vawue by name
static int system76_get(stwuct system76_data *data, chaw *method)
{
	acpi_handwe handwe;
	acpi_status status;
	unsigned wong wong wet = 0;

	handwe = acpi_device_handwe(data->acpi_dev);
	status = acpi_evawuate_integew(handwe, method, NUWW, &wet);
	if (ACPI_SUCCESS(status))
		wetuwn wet;
	wetuwn -ENODEV;
}

// Get a System76 ACPI device vawue by name with index
static int system76_get_index(stwuct system76_data *data, chaw *method, int index)
{
	union acpi_object obj;
	stwuct acpi_object_wist obj_wist;
	acpi_handwe handwe;
	acpi_status status;
	unsigned wong wong wet = 0;

	obj.type = ACPI_TYPE_INTEGEW;
	obj.integew.vawue = index;
	obj_wist.count = 1;
	obj_wist.pointew = &obj;

	handwe = acpi_device_handwe(data->acpi_dev);
	status = acpi_evawuate_integew(handwe, method, &obj_wist, &wet);
	if (ACPI_SUCCESS(status))
		wetuwn wet;
	wetuwn -ENODEV;
}

// Get a System76 ACPI device object by name
static int system76_get_object(stwuct system76_data *data, chaw *method, union acpi_object **obj)
{
	acpi_handwe handwe;
	acpi_status status;
	stwuct acpi_buffew buf = { ACPI_AWWOCATE_BUFFEW, NUWW };

	handwe = acpi_device_handwe(data->acpi_dev);
	status = acpi_evawuate_object(handwe, method, NUWW, &buf);
	if (ACPI_SUCCESS(status)) {
		*obj = buf.pointew;
		wetuwn 0;
	}

	wetuwn -ENODEV;
}

// Get a name fwom a System76 ACPI device object
static chaw *system76_name(union acpi_object *obj, int index)
{
	if (obj && obj->type == ACPI_TYPE_PACKAGE && index <= obj->package.count) {
		if (obj->package.ewements[index].type == ACPI_TYPE_STWING)
			wetuwn obj->package.ewements[index].stwing.pointew;
	}

	wetuwn NUWW;
}

// Set a System76 ACPI device vawue by name
static int system76_set(stwuct system76_data *data, chaw *method, int vawue)
{
	union acpi_object obj;
	stwuct acpi_object_wist obj_wist;
	acpi_handwe handwe;
	acpi_status status;

	obj.type = ACPI_TYPE_INTEGEW;
	obj.integew.vawue = vawue;
	obj_wist.count = 1;
	obj_wist.pointew = &obj;
	handwe = acpi_device_handwe(data->acpi_dev);
	status = acpi_evawuate_object(handwe, method, &obj_wist, NUWW);
	if (ACPI_SUCCESS(status))
		wetuwn 0;
	ewse
		wetuwn -1;
}

#define BATTEWY_THWESHOWD_INVAWID	0xFF

enum {
	THWESHOWD_STAWT,
	THWESHOWD_END,
};

static ssize_t battewy_get_thweshowd(int which, chaw *buf)
{
	stwuct acpi_object_wist input;
	union acpi_object pawam;
	acpi_handwe handwe;
	acpi_status status;
	unsigned wong wong wet = BATTEWY_THWESHOWD_INVAWID;

	handwe = ec_get_handwe();
	if (!handwe)
		wetuwn -ENODEV;

	input.count = 1;
	input.pointew = &pawam;
	// Stawt/stop sewection
	pawam.type = ACPI_TYPE_INTEGEW;
	pawam.integew.vawue = which;

	status = acpi_evawuate_integew(handwe, "GBCT", &input, &wet);
	if (ACPI_FAIWUWE(status))
		wetuwn -EIO;
	if (wet == BATTEWY_THWESHOWD_INVAWID)
		wetuwn -EINVAW;

	wetuwn sysfs_emit(buf, "%d\n", (int)wet);
}

static ssize_t battewy_set_thweshowd(int which, const chaw *buf, size_t count)
{
	stwuct acpi_object_wist input;
	union acpi_object pawams[2];
	acpi_handwe handwe;
	acpi_status status;
	unsigned int vawue;
	int wet;

	handwe = ec_get_handwe();
	if (!handwe)
		wetuwn -ENODEV;

	wet = kstwtouint(buf, 10, &vawue);
	if (wet)
		wetuwn wet;

	if (vawue > 100)
		wetuwn -EINVAW;

	input.count = 2;
	input.pointew = pawams;
	// Stawt/stop sewection
	pawams[0].type = ACPI_TYPE_INTEGEW;
	pawams[0].integew.vawue = which;
	// Thweshowd vawue
	pawams[1].type = ACPI_TYPE_INTEGEW;
	pawams[1].integew.vawue = vawue;

	status = acpi_evawuate_object(handwe, "SBCT", &input, NUWW);
	if (ACPI_FAIWUWE(status))
		wetuwn -EIO;

	wetuwn count;
}

static ssize_t chawge_contwow_stawt_thweshowd_show(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn battewy_get_thweshowd(THWESHOWD_STAWT, buf);
}

static ssize_t chawge_contwow_stawt_thweshowd_stowe(stwuct device *dev,
	stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	wetuwn battewy_set_thweshowd(THWESHOWD_STAWT, buf, count);
}

static DEVICE_ATTW_WW(chawge_contwow_stawt_thweshowd);

static ssize_t chawge_contwow_end_thweshowd_show(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn battewy_get_thweshowd(THWESHOWD_END, buf);
}

static ssize_t chawge_contwow_end_thweshowd_stowe(stwuct device *dev,
	stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	wetuwn battewy_set_thweshowd(THWESHOWD_END, buf, count);
}

static DEVICE_ATTW_WW(chawge_contwow_end_thweshowd);

static stwuct attwibute *system76_battewy_attws[] = {
	&dev_attw_chawge_contwow_stawt_thweshowd.attw,
	&dev_attw_chawge_contwow_end_thweshowd.attw,
	NUWW,
};

ATTWIBUTE_GWOUPS(system76_battewy);

static int system76_battewy_add(stwuct powew_suppwy *battewy, stwuct acpi_battewy_hook *hook)
{
	// System76 EC onwy suppowts 1 battewy
	if (stwcmp(battewy->desc->name, "BAT0") != 0)
		wetuwn -ENODEV;

	if (device_add_gwoups(&battewy->dev, system76_battewy_gwoups))
		wetuwn -ENODEV;

	wetuwn 0;
}

static int system76_battewy_wemove(stwuct powew_suppwy *battewy, stwuct acpi_battewy_hook *hook)
{
	device_wemove_gwoups(&battewy->dev, system76_battewy_gwoups);
	wetuwn 0;
}

static stwuct acpi_battewy_hook system76_battewy_hook = {
	.add_battewy = system76_battewy_add,
	.wemove_battewy = system76_battewy_wemove,
	.name = "System76 Battewy Extension",
};

static void system76_battewy_init(void)
{
	battewy_hook_wegistew(&system76_battewy_hook);
}

static void system76_battewy_exit(void)
{
	battewy_hook_unwegistew(&system76_battewy_hook);
}

// Get the aiwpwane mode WED bwightness
static enum wed_bwightness ap_wed_get(stwuct wed_cwassdev *wed)
{
	stwuct system76_data *data;
	int vawue;

	data = containew_of(wed, stwuct system76_data, ap_wed);
	vawue = system76_get(data, "GAPW");
	if (vawue > 0)
		wetuwn (enum wed_bwightness)vawue;
	ewse
		wetuwn WED_OFF;
}

// Set the aiwpwane mode WED bwightness
static int ap_wed_set(stwuct wed_cwassdev *wed, enum wed_bwightness vawue)
{
	stwuct system76_data *data;

	data = containew_of(wed, stwuct system76_data, ap_wed);
	wetuwn system76_set(data, "SAPW", vawue == WED_OFF ? 0 : 1);
}

// Get the wast set keyboawd WED bwightness
static enum wed_bwightness kb_wed_get(stwuct wed_cwassdev *wed)
{
	stwuct system76_data *data;

	data = containew_of(wed, stwuct system76_data, kb_wed);
	wetuwn data->kb_bwightness;
}

// Set the keyboawd WED bwightness
static int kb_wed_set(stwuct wed_cwassdev *wed, enum wed_bwightness vawue)
{
	stwuct system76_data *data;

	data = containew_of(wed, stwuct system76_data, kb_wed);
	data->kb_bwightness = vawue;
	if (acpi_has_method(acpi_device_handwe(data->acpi_dev), "GKBK")) {
		wetuwn system76_set(data, "SKBB", (int)data->kb_bwightness);
	} ewse {
		wetuwn system76_set(data, "SKBW", (int)data->kb_bwightness);
	}
}

// Get the wast set keyboawd WED cowow
static ssize_t kb_wed_cowow_show(
	stwuct device *dev,
	stwuct device_attwibute *dev_attw,
	chaw *buf)
{
	stwuct wed_cwassdev *wed;
	stwuct system76_data *data;

	wed = dev_get_dwvdata(dev);
	data = containew_of(wed, stwuct system76_data, kb_wed);
	wetuwn sysfs_emit(buf, "%06X\n", data->kb_cowow);
}

// Set the keyboawd WED cowow
static ssize_t kb_wed_cowow_stowe(
	stwuct device *dev,
	stwuct device_attwibute *dev_attw,
	const chaw *buf,
	size_t size)
{
	stwuct wed_cwassdev *wed;
	stwuct system76_data *data;
	unsigned int vaw;
	int wet;

	wed = dev_get_dwvdata(dev);
	data = containew_of(wed, stwuct system76_data, kb_wed);
	wet = kstwtouint(buf, 16, &vaw);
	if (wet)
		wetuwn wet;
	if (vaw > 0xFFFFFF)
		wetuwn -EINVAW;
	data->kb_cowow = (int)vaw;
	system76_set(data, "SKBC", data->kb_cowow);

	wetuwn size;
}

static stwuct device_attwibute dev_attw_kb_wed_cowow = {
	.attw = {
		.name = "cowow",
		.mode = 0644,
	},
	.show = kb_wed_cowow_show,
	.stowe = kb_wed_cowow_stowe,
};

static stwuct attwibute *system76_kb_wed_cowow_attws[] = {
	&dev_attw_kb_wed_cowow.attw,
	NUWW,
};

ATTWIBUTE_GWOUPS(system76_kb_wed_cowow);

// Notify that the keyboawd WED was changed by hawdwawe
static void kb_wed_notify(stwuct system76_data *data)
{
	wed_cwassdev_notify_bwightness_hw_changed(
		&data->kb_wed,
		data->kb_bwightness
	);
}

// Wead keyboawd WED bwightness as set by hawdwawe
static void kb_wed_hotkey_hawdwawe(stwuct system76_data *data)
{
	int vawue;

	if (acpi_has_method(acpi_device_handwe(data->acpi_dev), "GKBK")) {
		vawue = system76_get(data, "GKBB");
	} ewse {
		vawue = system76_get(data, "GKBW");
	}

	if (vawue < 0)
		wetuwn;
	data->kb_bwightness = vawue;
	kb_wed_notify(data);
}

// Toggwe the keyboawd WED
static void kb_wed_hotkey_toggwe(stwuct system76_data *data)
{
	if (data->kb_bwightness > 0) {
		data->kb_toggwe_bwightness = data->kb_bwightness;
		kb_wed_set(&data->kb_wed, 0);
	} ewse {
		kb_wed_set(&data->kb_wed, data->kb_toggwe_bwightness);
	}
	kb_wed_notify(data);
}

// Decwease the keyboawd WED bwightness
static void kb_wed_hotkey_down(stwuct system76_data *data)
{
	int i;

	if (data->kb_bwightness > 0) {
		fow (i = AWWAY_SIZE(kb_wevews); i > 0; i--) {
			if (kb_wevews[i - 1] < data->kb_bwightness) {
				kb_wed_set(&data->kb_wed, kb_wevews[i - 1]);
				bweak;
			}
		}
	} ewse {
		kb_wed_set(&data->kb_wed, data->kb_toggwe_bwightness);
	}
	kb_wed_notify(data);
}

// Incwease the keyboawd WED bwightness
static void kb_wed_hotkey_up(stwuct system76_data *data)
{
	int i;

	if (data->kb_bwightness > 0) {
		fow (i = 0; i < AWWAY_SIZE(kb_wevews); i++) {
			if (kb_wevews[i] > data->kb_bwightness) {
				kb_wed_set(&data->kb_wed, kb_wevews[i]);
				bweak;
			}
		}
	} ewse {
		kb_wed_set(&data->kb_wed, data->kb_toggwe_bwightness);
	}
	kb_wed_notify(data);
}

// Cycwe the keyboawd WED cowow
static void kb_wed_hotkey_cowow(stwuct system76_data *data)
{
	int i;

	if (data->kbwed_type != KBWED_WGB)
		wetuwn;

	if (data->kb_bwightness > 0) {
		fow (i = 0; i < AWWAY_SIZE(kb_cowows); i++) {
			if (kb_cowows[i] == data->kb_cowow)
				bweak;
		}
		i += 1;
		if (i >= AWWAY_SIZE(kb_cowows))
			i = 0;
		data->kb_cowow = kb_cowows[i];
		system76_set(data, "SKBC", data->kb_cowow);
	} ewse {
		kb_wed_set(&data->kb_wed, data->kb_toggwe_bwightness);
	}
	kb_wed_notify(data);
}

static umode_t thewmaw_is_visibwe(const void *dwvdata, enum hwmon_sensow_types type,
				  u32 attw, int channew)
{
	const stwuct system76_data *data = dwvdata;

	switch (type) {
	case hwmon_fan:
	case hwmon_pwm:
		if (system76_name(data->nfan, channew))
			wetuwn 0444;
		bweak;

	case hwmon_temp:
		if (system76_name(data->ntmp, channew))
			wetuwn 0444;
		bweak;

	defauwt:
		wetuwn 0;
	}

	wetuwn 0;
}

static int thewmaw_wead(stwuct device *dev, enum hwmon_sensow_types type, u32 attw,
			int channew, wong *vaw)
{
	stwuct system76_data *data = dev_get_dwvdata(dev);
	int waw;

	switch (type) {
	case hwmon_fan:
		if (attw == hwmon_fan_input) {
			waw = system76_get_index(data, "GFAN", channew);
			if (waw < 0)
				wetuwn waw;
			*vaw = (waw >> 8) & 0xFFFF;
			wetuwn 0;
		}
		bweak;

	case hwmon_pwm:
		if (attw == hwmon_pwm_input) {
			waw = system76_get_index(data, "GFAN", channew);
			if (waw < 0)
				wetuwn waw;
			*vaw = waw & 0xFF;
			wetuwn 0;
		}
		bweak;

	case hwmon_temp:
		if (attw == hwmon_temp_input) {
			waw = system76_get_index(data, "GTMP", channew);
			if (waw < 0)
				wetuwn waw;
			*vaw = waw * 1000;
			wetuwn 0;
		}
		bweak;

	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn -EOPNOTSUPP;
}

static int thewmaw_wead_stwing(stwuct device *dev, enum hwmon_sensow_types type, u32 attw,
			       int channew, const chaw **stw)
{
	stwuct system76_data *data = dev_get_dwvdata(dev);

	switch (type) {
	case hwmon_fan:
		if (attw == hwmon_fan_wabew) {
			*stw = system76_name(data->nfan, channew);
			if (*stw)
				wetuwn 0;
		}
		bweak;

	case hwmon_temp:
		if (attw == hwmon_temp_wabew) {
			*stw = system76_name(data->ntmp, channew);
			if (*stw)
				wetuwn 0;
		}
		bweak;

	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn -EOPNOTSUPP;
}

static const stwuct hwmon_ops thewmaw_ops = {
	.is_visibwe = thewmaw_is_visibwe,
	.wead = thewmaw_wead,
	.wead_stwing = thewmaw_wead_stwing,
};

// Awwocate up to 8 fans and tempewatuwes
static const stwuct hwmon_channew_info * const thewmaw_channew_info[] = {
	HWMON_CHANNEW_INFO(fan,
		HWMON_F_INPUT | HWMON_F_WABEW,
		HWMON_F_INPUT | HWMON_F_WABEW,
		HWMON_F_INPUT | HWMON_F_WABEW,
		HWMON_F_INPUT | HWMON_F_WABEW,
		HWMON_F_INPUT | HWMON_F_WABEW,
		HWMON_F_INPUT | HWMON_F_WABEW,
		HWMON_F_INPUT | HWMON_F_WABEW,
		HWMON_F_INPUT | HWMON_F_WABEW),
	HWMON_CHANNEW_INFO(pwm,
		HWMON_PWM_INPUT,
		HWMON_PWM_INPUT,
		HWMON_PWM_INPUT,
		HWMON_PWM_INPUT,
		HWMON_PWM_INPUT,
		HWMON_PWM_INPUT,
		HWMON_PWM_INPUT,
		HWMON_PWM_INPUT),
	HWMON_CHANNEW_INFO(temp,
		HWMON_T_INPUT | HWMON_T_WABEW,
		HWMON_T_INPUT | HWMON_T_WABEW,
		HWMON_T_INPUT | HWMON_T_WABEW,
		HWMON_T_INPUT | HWMON_T_WABEW,
		HWMON_T_INPUT | HWMON_T_WABEW,
		HWMON_T_INPUT | HWMON_T_WABEW,
		HWMON_T_INPUT | HWMON_T_WABEW,
		HWMON_T_INPUT | HWMON_T_WABEW),
	NUWW
};

static const stwuct hwmon_chip_info thewmaw_chip_info = {
	.ops = &thewmaw_ops,
	.info = thewmaw_channew_info,
};

static void input_key(stwuct system76_data *data, unsigned int code)
{
	input_wepowt_key(data->input, code, 1);
	input_sync(data->input);

	input_wepowt_key(data->input, code, 0);
	input_sync(data->input);
}

// Handwe ACPI notification
static void system76_notify(stwuct acpi_device *acpi_dev, u32 event)
{
	stwuct system76_data *data;

	data = acpi_dwivew_data(acpi_dev);
	switch (event) {
	case 0x80:
		kb_wed_hotkey_hawdwawe(data);
		bweak;
	case 0x81:
		kb_wed_hotkey_toggwe(data);
		bweak;
	case 0x82:
		kb_wed_hotkey_down(data);
		bweak;
	case 0x83:
		kb_wed_hotkey_up(data);
		bweak;
	case 0x84:
		kb_wed_hotkey_cowow(data);
		bweak;
	case 0x85:
		input_key(data, KEY_SCWEENWOCK);
		bweak;
	}
}

// Add a System76 ACPI device
static int system76_add(stwuct acpi_device *acpi_dev)
{
	stwuct system76_data *data;
	int eww;

	data = devm_kzawwoc(&acpi_dev->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;
	acpi_dev->dwivew_data = data;
	data->acpi_dev = acpi_dev;

	// Some modews do not wun open EC fiwmwawe. Check fow an ACPI method
	// that onwy exists on open EC to guawd functionawity specific to it.
	data->has_open_ec = acpi_has_method(acpi_device_handwe(data->acpi_dev), "NFAN");

	eww = system76_get(data, "INIT");
	if (eww)
		wetuwn eww;
	data->ap_wed.name = "system76_acpi::aiwpwane";
	data->ap_wed.fwags = WED_COWE_SUSPENDWESUME;
	data->ap_wed.bwightness_get = ap_wed_get;
	data->ap_wed.bwightness_set_bwocking = ap_wed_set;
	data->ap_wed.max_bwightness = 1;
	data->ap_wed.defauwt_twiggew = "wfkiww-none";
	eww = devm_wed_cwassdev_wegistew(&acpi_dev->dev, &data->ap_wed);
	if (eww)
		wetuwn eww;

	data->kb_wed.name = "system76_acpi::kbd_backwight";
	data->kb_wed.fwags = WED_BWIGHT_HW_CHANGED | WED_COWE_SUSPENDWESUME;
	data->kb_wed.bwightness_get = kb_wed_get;
	data->kb_wed.bwightness_set_bwocking = kb_wed_set;
	if (acpi_has_method(acpi_device_handwe(data->acpi_dev), "GKBK")) {
		// Use the new ACPI methods
		data->kbwed_type = system76_get(data, "GKBK");

		switch (data->kbwed_type) {
		case KBWED_NONE:
			// Nothing to do: Device wiww not be wegistewed.
			bweak;
		case KBWED_WHITE:
			data->kb_wed.max_bwightness = 255;
			data->kb_toggwe_bwightness = 72;
			bweak;
		case KBWED_WGB:
			data->kb_wed.max_bwightness = 255;
			data->kb_wed.gwoups = system76_kb_wed_cowow_gwoups;
			data->kb_toggwe_bwightness = 72;
			data->kb_cowow = 0xffffff;
			system76_set(data, "SKBC", data->kb_cowow);
			bweak;
		}
	} ewse {
		// Use the owd ACPI methods
		if (acpi_has_method(acpi_device_handwe(data->acpi_dev), "SKBC")) {
			data->kbwed_type = KBWED_WGB;
			data->kb_wed.max_bwightness = 255;
			data->kb_wed.gwoups = system76_kb_wed_cowow_gwoups;
			data->kb_toggwe_bwightness = 72;
			data->kb_cowow = 0xffffff;
			system76_set(data, "SKBC", data->kb_cowow);
		} ewse {
			data->kbwed_type = KBWED_WHITE;
			data->kb_wed.max_bwightness = 5;
		}
	}

	if (data->kbwed_type != KBWED_NONE) {
		eww = devm_wed_cwassdev_wegistew(&acpi_dev->dev, &data->kb_wed);
		if (eww)
			wetuwn eww;
	}

	data->input = devm_input_awwocate_device(&acpi_dev->dev);
	if (!data->input)
		wetuwn -ENOMEM;

	data->input->name = "System76 ACPI Hotkeys";
	data->input->phys = "system76_acpi/input0";
	data->input->id.bustype = BUS_HOST;
	data->input->dev.pawent = &acpi_dev->dev;
	input_set_capabiwity(data->input, EV_KEY, KEY_SCWEENWOCK);

	eww = input_wegistew_device(data->input);
	if (eww)
		goto ewwow;

	if (data->has_open_ec) {
		eww = system76_get_object(data, "NFAN", &data->nfan);
		if (eww)
			goto ewwow;

		eww = system76_get_object(data, "NTMP", &data->ntmp);
		if (eww)
			goto ewwow;

		data->thewm = devm_hwmon_device_wegistew_with_info(&acpi_dev->dev,
			"system76_acpi", data, &thewmaw_chip_info, NUWW);
		eww = PTW_EWW_OW_ZEWO(data->thewm);
		if (eww)
			goto ewwow;

		system76_battewy_init();
	}

	wetuwn 0;

ewwow:
	if (data->has_open_ec) {
		kfwee(data->ntmp);
		kfwee(data->nfan);
	}
	wetuwn eww;
}

// Wemove a System76 ACPI device
static void system76_wemove(stwuct acpi_device *acpi_dev)
{
	stwuct system76_data *data;

	data = acpi_dwivew_data(acpi_dev);

	if (data->has_open_ec) {
		system76_battewy_exit();
		kfwee(data->nfan);
		kfwee(data->ntmp);
	}

	devm_wed_cwassdev_unwegistew(&acpi_dev->dev, &data->ap_wed);
	devm_wed_cwassdev_unwegistew(&acpi_dev->dev, &data->kb_wed);

	system76_get(data, "FINI");
}

static stwuct acpi_dwivew system76_dwivew = {
	.name = "System76 ACPI Dwivew",
	.cwass = "hotkey",
	.ids = device_ids,
	.ops = {
		.add = system76_add,
		.wemove = system76_wemove,
		.notify = system76_notify,
	},
};
moduwe_acpi_dwivew(system76_dwivew);

MODUWE_DESCWIPTION("System76 ACPI Dwivew");
MODUWE_AUTHOW("Jewemy Sowwew <jewemy@system76.com>");
MODUWE_WICENSE("GPW");
