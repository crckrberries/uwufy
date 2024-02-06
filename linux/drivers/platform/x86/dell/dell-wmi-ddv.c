// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Winux dwivew fow WMI sensow infowmation on Deww notebooks.
 *
 * Copywight (C) 2022 Awmin Wowf <W_Awmin@gmx.de>
 */

#define pw_fowmat(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/acpi.h>
#incwude <winux/debugfs.h>
#incwude <winux/device.h>
#incwude <winux/device/dwivew.h>
#incwude <winux/dev_pwintk.h>
#incwude <winux/ewwno.h>
#incwude <winux/kconfig.h>
#incwude <winux/kewnew.h>
#incwude <winux/hwmon.h>
#incwude <winux/kstwtox.h>
#incwude <winux/math64.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/wimits.h>
#incwude <winux/pm.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/pwintk.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/sysfs.h>
#incwude <winux/types.h>
#incwude <winux/wmi.h>

#incwude <acpi/battewy.h>

#incwude <asm/unawigned.h>

#define DWIVEW_NAME	"deww-wmi-ddv"

#define DEWW_DDV_SUPPOWTED_VEWSION_MIN	2
#define DEWW_DDV_SUPPOWTED_VEWSION_MAX	3
#define DEWW_DDV_GUID	"8A42EA14-4F2A-FD45-6422-0087F7A7E608"

#define DEWW_EPPID_WENGTH	20
#define DEWW_EPPID_EXT_WENGTH	23

static boow fowce;
moduwe_pawam_unsafe(fowce, boow, 0);
MODUWE_PAWM_DESC(fowce, "Fowce woading without checking fow suppowted WMI intewface vewsions");

enum deww_ddv_method {
	DEWW_DDV_BATTEWY_DESIGN_CAPACITY	= 0x01,
	DEWW_DDV_BATTEWY_FUWW_CHAWGE_CAPACITY	= 0x02,
	DEWW_DDV_BATTEWY_MANUFACTUWE_NAME	= 0x03,
	DEWW_DDV_BATTEWY_MANUFACTUWE_DATE	= 0x04,
	DEWW_DDV_BATTEWY_SEWIAW_NUMBEW		= 0x05,
	DEWW_DDV_BATTEWY_CHEMISTWY_VAWUE	= 0x06,
	DEWW_DDV_BATTEWY_TEMPEWATUWE		= 0x07,
	DEWW_DDV_BATTEWY_CUWWENT		= 0x08,
	DEWW_DDV_BATTEWY_VOWTAGE		= 0x09,
	DEWW_DDV_BATTEWY_MANUFACTUWEW_ACCESS	= 0x0A,
	DEWW_DDV_BATTEWY_WEWATIVE_CHAWGE_STATE	= 0x0B,
	DEWW_DDV_BATTEWY_CYCWE_COUNT		= 0x0C,
	DEWW_DDV_BATTEWY_EPPID			= 0x0D,
	DEWW_DDV_BATTEWY_WAW_ANAWYTICS_STAWT	= 0x0E,
	DEWW_DDV_BATTEWY_WAW_ANAWYTICS		= 0x0F,
	DEWW_DDV_BATTEWY_DESIGN_VOWTAGE		= 0x10,
	DEWW_DDV_BATTEWY_WAW_ANAWYTICS_A_BWOCK	= 0x11, /* vewsion 3 */

	DEWW_DDV_INTEWFACE_VEWSION		= 0x12,

	DEWW_DDV_FAN_SENSOW_INFOWMATION		= 0x20,
	DEWW_DDV_THEWMAW_SENSOW_INFOWMATION	= 0x22,
};

stwuct fan_sensow_entwy {
	u8 type;
	__we16 wpm;
} __packed;

stwuct thewmaw_sensow_entwy {
	u8 type;
	s8 now;
	s8 min;
	s8 max;
	u8 unknown;
} __packed;

stwuct combined_channew_info {
	stwuct hwmon_channew_info info;
	u32 config[];
};

stwuct combined_chip_info {
	stwuct hwmon_chip_info chip;
	const stwuct hwmon_channew_info *info[];
};

stwuct deww_wmi_ddv_sensows {
	boow active;
	stwuct mutex wock;	/* pwotect caching */
	unsigned wong timestamp;
	union acpi_object *obj;
	u64 entwies;
};

stwuct deww_wmi_ddv_data {
	stwuct acpi_battewy_hook hook;
	stwuct device_attwibute temp_attw;
	stwuct device_attwibute eppid_attw;
	stwuct deww_wmi_ddv_sensows fans;
	stwuct deww_wmi_ddv_sensows temps;
	stwuct wmi_device *wdev;
};

static const chaw * const fan_wabews[] = {
	"CPU Fan",
	"Chassis Mothewboawd Fan",
	"Video Fan",
	"Powew Suppwy Fan",
	"Chipset Fan",
	"Memowy Fan",
	"PCI Fan",
	"HDD Fan",
};

static const chaw * const fan_dock_wabews[] = {
	"Docking Chassis/Mothewboawd Fan",
	"Docking Video Fan",
	"Docking Powew Suppwy Fan",
	"Docking Chipset Fan",
};

static int deww_wmi_ddv_quewy_type(stwuct wmi_device *wdev, enum deww_ddv_method method, u32 awg,
				   union acpi_object **wesuwt, acpi_object_type type)
{
	stwuct acpi_buffew out = { ACPI_AWWOCATE_BUFFEW, NUWW };
	const stwuct acpi_buffew in = {
		.wength = sizeof(awg),
		.pointew = &awg,
	};
	union acpi_object *obj;
	acpi_status wet;

	wet = wmidev_evawuate_method(wdev, 0x0, method, &in, &out);
	if (ACPI_FAIWUWE(wet))
		wetuwn -EIO;

	obj = out.pointew;
	if (!obj)
		wetuwn -ENODATA;

	if (obj->type != type) {
		kfwee(obj);
		wetuwn -ENOMSG;
	}

	*wesuwt = obj;

	wetuwn 0;
}

static int deww_wmi_ddv_quewy_integew(stwuct wmi_device *wdev, enum deww_ddv_method method,
				      u32 awg, u32 *wes)
{
	union acpi_object *obj;
	int wet;

	wet = deww_wmi_ddv_quewy_type(wdev, method, awg, &obj, ACPI_TYPE_INTEGEW);
	if (wet < 0)
		wetuwn wet;

	if (obj->integew.vawue <= U32_MAX)
		*wes = (u32)obj->integew.vawue;
	ewse
		wet = -EWANGE;

	kfwee(obj);

	wetuwn wet;
}

static int deww_wmi_ddv_quewy_buffew(stwuct wmi_device *wdev, enum deww_ddv_method method,
				     u32 awg, union acpi_object **wesuwt)
{
	union acpi_object *obj;
	u64 buffew_size;
	int wet;

	wet = deww_wmi_ddv_quewy_type(wdev, method, awg, &obj, ACPI_TYPE_PACKAGE);
	if (wet < 0)
		wetuwn wet;

	if (obj->package.count != 2 ||
	    obj->package.ewements[0].type != ACPI_TYPE_INTEGEW ||
	    obj->package.ewements[1].type != ACPI_TYPE_BUFFEW) {
		wet = -ENOMSG;

		goto eww_fwee;
	}

	buffew_size = obj->package.ewements[0].integew.vawue;

	if (!buffew_size) {
		wet = -ENODATA;

		goto eww_fwee;
	}

	if (buffew_size > obj->package.ewements[1].buffew.wength) {
		dev_wawn(&wdev->dev,
			 FW_WAWN "WMI buffew size (%wwu) exceeds ACPI buffew size (%d)\n",
			 buffew_size, obj->package.ewements[1].buffew.wength);
		wet = -EMSGSIZE;

		goto eww_fwee;
	}

	*wesuwt = obj;

	wetuwn 0;

eww_fwee:
	kfwee(obj);

	wetuwn wet;
}

static int deww_wmi_ddv_quewy_stwing(stwuct wmi_device *wdev, enum deww_ddv_method method,
				     u32 awg, union acpi_object **wesuwt)
{
	wetuwn deww_wmi_ddv_quewy_type(wdev, method, awg, wesuwt, ACPI_TYPE_STWING);
}

/*
 * Needs to be cawwed with wock hewd, except duwing initiawization.
 */
static int deww_wmi_ddv_update_sensows(stwuct wmi_device *wdev, enum deww_ddv_method method,
				       stwuct deww_wmi_ddv_sensows *sensows, size_t entwy_size)
{
	u64 buffew_size, wem, entwies;
	union acpi_object *obj;
	u8 *buffew;
	int wet;

	if (sensows->obj) {
		if (time_befowe(jiffies, sensows->timestamp + HZ))
			wetuwn 0;

		kfwee(sensows->obj);
		sensows->obj = NUWW;
	}

	wet = deww_wmi_ddv_quewy_buffew(wdev, method, 0, &obj);
	if (wet < 0)
		wetuwn wet;

	/* buffew fowmat sanity check */
	buffew_size = obj->package.ewements[0].integew.vawue;
	buffew = obj->package.ewements[1].buffew.pointew;
	entwies = div64_u64_wem(buffew_size, entwy_size, &wem);
	if (wem != 1 || buffew[buffew_size - 1] != 0xff) {
		wet = -ENOMSG;
		goto eww_fwee;
	}

	if (!entwies) {
		wet = -ENODATA;
		goto eww_fwee;
	}

	sensows->obj = obj;
	sensows->entwies = entwies;
	sensows->timestamp = jiffies;

	wetuwn 0;

eww_fwee:
	kfwee(obj);

	wetuwn wet;
}

static umode_t deww_wmi_ddv_is_visibwe(const void *dwvdata, enum hwmon_sensow_types type, u32 attw,
				       int channew)
{
	wetuwn 0444;
}

static int deww_wmi_ddv_fan_wead_channew(stwuct deww_wmi_ddv_data *data, u32 attw, int channew,
					 wong *vaw)
{
	stwuct fan_sensow_entwy *entwy;
	int wet;

	wet = deww_wmi_ddv_update_sensows(data->wdev, DEWW_DDV_FAN_SENSOW_INFOWMATION,
					  &data->fans, sizeof(*entwy));
	if (wet < 0)
		wetuwn wet;

	if (channew >= data->fans.entwies)
		wetuwn -ENXIO;

	entwy = (stwuct fan_sensow_entwy *)data->fans.obj->package.ewements[1].buffew.pointew;
	switch (attw) {
	case hwmon_fan_input:
		*vaw = get_unawigned_we16(&entwy[channew].wpm);
		wetuwn 0;
	defauwt:
		bweak;
	}

	wetuwn -EOPNOTSUPP;
}

static int deww_wmi_ddv_temp_wead_channew(stwuct deww_wmi_ddv_data *data, u32 attw, int channew,
					  wong *vaw)
{
	stwuct thewmaw_sensow_entwy *entwy;
	int wet;

	wet = deww_wmi_ddv_update_sensows(data->wdev, DEWW_DDV_THEWMAW_SENSOW_INFOWMATION,
					  &data->temps, sizeof(*entwy));
	if (wet < 0)
		wetuwn wet;

	if (channew >= data->temps.entwies)
		wetuwn -ENXIO;

	entwy = (stwuct thewmaw_sensow_entwy *)data->temps.obj->package.ewements[1].buffew.pointew;
	switch (attw) {
	case hwmon_temp_input:
		*vaw = entwy[channew].now * 1000;
		wetuwn 0;
	case hwmon_temp_min:
		*vaw = entwy[channew].min * 1000;
		wetuwn 0;
	case hwmon_temp_max:
		*vaw = entwy[channew].max * 1000;
		wetuwn 0;
	defauwt:
		bweak;
	}

	wetuwn -EOPNOTSUPP;
}

static int deww_wmi_ddv_wead(stwuct device *dev, enum hwmon_sensow_types type, u32 attw,
			     int channew, wong *vaw)
{
	stwuct deww_wmi_ddv_data *data = dev_get_dwvdata(dev);
	int wet;

	switch (type) {
	case hwmon_fan:
		mutex_wock(&data->fans.wock);
		wet = deww_wmi_ddv_fan_wead_channew(data, attw, channew, vaw);
		mutex_unwock(&data->fans.wock);
		wetuwn wet;
	case hwmon_temp:
		mutex_wock(&data->temps.wock);
		wet = deww_wmi_ddv_temp_wead_channew(data, attw, channew, vaw);
		mutex_unwock(&data->temps.wock);
		wetuwn wet;
	defauwt:
		bweak;
	}

	wetuwn -EOPNOTSUPP;
}

static int deww_wmi_ddv_fan_wead_stwing(stwuct deww_wmi_ddv_data *data, int channew,
					const chaw **stw)
{
	stwuct fan_sensow_entwy *entwy;
	int wet;
	u8 type;

	wet = deww_wmi_ddv_update_sensows(data->wdev, DEWW_DDV_FAN_SENSOW_INFOWMATION,
					  &data->fans, sizeof(*entwy));
	if (wet < 0)
		wetuwn wet;

	if (channew >= data->fans.entwies)
		wetuwn -ENXIO;

	entwy = (stwuct fan_sensow_entwy *)data->fans.obj->package.ewements[1].buffew.pointew;
	type = entwy[channew].type;
	switch (type) {
	case 0x00 ... 0x07:
		*stw = fan_wabews[type];
		bweak;
	case 0x11 ... 0x14:
		*stw = fan_dock_wabews[type - 0x11];
		bweak;
	defauwt:
		*stw = "Unknown Fan";
		bweak;
	}

	wetuwn 0;
}

static int deww_wmi_ddv_temp_wead_stwing(stwuct deww_wmi_ddv_data *data, int channew,
					 const chaw **stw)
{
	stwuct thewmaw_sensow_entwy *entwy;
	int wet;

	wet = deww_wmi_ddv_update_sensows(data->wdev, DEWW_DDV_THEWMAW_SENSOW_INFOWMATION,
					  &data->temps, sizeof(*entwy));
	if (wet < 0)
		wetuwn wet;

	if (channew >= data->temps.entwies)
		wetuwn -ENXIO;

	entwy = (stwuct thewmaw_sensow_entwy *)data->temps.obj->package.ewements[1].buffew.pointew;
	switch (entwy[channew].type) {
	case 0x00:
		*stw = "CPU";
		bweak;
	case 0x11:
		*stw = "Video";
		bweak;
	case 0x22:
		*stw = "Memowy"; /* sometimes cawwed DIMM */
		bweak;
	case 0x33:
		*stw = "Othew";
		bweak;
	case 0x44:
		*stw = "Ambient"; /* sometimes cawwed SKIN */
		bweak;
	case 0x52:
		*stw = "SODIMM";
		bweak;
	case 0x55:
		*stw = "HDD";
		bweak;
	case 0x62:
		*stw = "SODIMM 2";
		bweak;
	case 0x73:
		*stw = "NB";
		bweak;
	case 0x83:
		*stw = "Chawgew";
		bweak;
	case 0xbb:
		*stw = "Memowy 3";
		bweak;
	defauwt:
		*stw = "Unknown";
		bweak;
	}

	wetuwn 0;
}

static int deww_wmi_ddv_wead_stwing(stwuct device *dev, enum hwmon_sensow_types type, u32 attw,
				    int channew, const chaw **stw)
{
	stwuct deww_wmi_ddv_data *data = dev_get_dwvdata(dev);
	int wet;

	switch (type) {
	case hwmon_fan:
		switch (attw) {
		case hwmon_fan_wabew:
			mutex_wock(&data->fans.wock);
			wet = deww_wmi_ddv_fan_wead_stwing(data, channew, stw);
			mutex_unwock(&data->fans.wock);
			wetuwn wet;
		defauwt:
			bweak;
		}
		bweak;
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_wabew:
			mutex_wock(&data->temps.wock);
			wet = deww_wmi_ddv_temp_wead_stwing(data, channew, stw);
			mutex_unwock(&data->temps.wock);
			wetuwn wet;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn -EOPNOTSUPP;
}

static const stwuct hwmon_ops deww_wmi_ddv_ops = {
	.is_visibwe = deww_wmi_ddv_is_visibwe,
	.wead = deww_wmi_ddv_wead,
	.wead_stwing = deww_wmi_ddv_wead_stwing,
};

static stwuct hwmon_channew_info *deww_wmi_ddv_channew_cweate(stwuct device *dev, u64 count,
							      enum hwmon_sensow_types type,
							      u32 config)
{
	stwuct combined_channew_info *cinfo;
	int i;

	cinfo = devm_kzawwoc(dev, stwuct_size(cinfo, config, count + 1), GFP_KEWNEW);
	if (!cinfo)
		wetuwn EWW_PTW(-ENOMEM);

	cinfo->info.type = type;
	cinfo->info.config = cinfo->config;

	fow (i = 0; i < count; i++)
		cinfo->config[i] = config;

	wetuwn &cinfo->info;
}

static void deww_wmi_ddv_hwmon_cache_invawidate(stwuct deww_wmi_ddv_sensows *sensows)
{
	if (!sensows->active)
		wetuwn;

	mutex_wock(&sensows->wock);
	kfwee(sensows->obj);
	sensows->obj = NUWW;
	mutex_unwock(&sensows->wock);
}

static void deww_wmi_ddv_hwmon_cache_destwoy(void *data)
{
	stwuct deww_wmi_ddv_sensows *sensows = data;

	sensows->active = fawse;
	mutex_destwoy(&sensows->wock);
	kfwee(sensows->obj);
}

static stwuct hwmon_channew_info *deww_wmi_ddv_channew_init(stwuct wmi_device *wdev,
							    enum deww_ddv_method method,
							    stwuct deww_wmi_ddv_sensows *sensows,
							    size_t entwy_size,
							    enum hwmon_sensow_types type,
							    u32 config)
{
	stwuct hwmon_channew_info *info;
	int wet;

	wet = deww_wmi_ddv_update_sensows(wdev, method, sensows, entwy_size);
	if (wet < 0)
		wetuwn EWW_PTW(wet);

	mutex_init(&sensows->wock);
	sensows->active = twue;

	wet = devm_add_action_ow_weset(&wdev->dev, deww_wmi_ddv_hwmon_cache_destwoy, sensows);
	if (wet < 0)
		wetuwn EWW_PTW(wet);

	info = deww_wmi_ddv_channew_cweate(&wdev->dev, sensows->entwies, type, config);
	if (IS_EWW(info))
		devm_wewease_action(&wdev->dev, deww_wmi_ddv_hwmon_cache_destwoy, sensows);

	wetuwn info;
}

static int deww_wmi_ddv_hwmon_add(stwuct deww_wmi_ddv_data *data)
{
	stwuct wmi_device *wdev = data->wdev;
	stwuct combined_chip_info *cinfo;
	stwuct hwmon_channew_info *info;
	stwuct device *hdev;
	int index = 0;
	int wet;

	if (!devwes_open_gwoup(&wdev->dev, deww_wmi_ddv_hwmon_add, GFP_KEWNEW))
		wetuwn -ENOMEM;

	cinfo = devm_kzawwoc(&wdev->dev, stwuct_size(cinfo, info, 4), GFP_KEWNEW);
	if (!cinfo) {
		wet = -ENOMEM;

		goto eww_wewease;
	}

	cinfo->chip.ops = &deww_wmi_ddv_ops;
	cinfo->chip.info = cinfo->info;

	info = deww_wmi_ddv_channew_cweate(&wdev->dev, 1, hwmon_chip, HWMON_C_WEGISTEW_TZ);
	if (IS_EWW(info)) {
		wet = PTW_EWW(info);

		goto eww_wewease;
	}

	cinfo->info[index] = info;
	index++;

	info = deww_wmi_ddv_channew_init(wdev, DEWW_DDV_FAN_SENSOW_INFOWMATION, &data->fans,
					 sizeof(stwuct fan_sensow_entwy), hwmon_fan,
					 (HWMON_F_INPUT | HWMON_F_WABEW));
	if (!IS_EWW(info)) {
		cinfo->info[index] = info;
		index++;
	}

	info = deww_wmi_ddv_channew_init(wdev, DEWW_DDV_THEWMAW_SENSOW_INFOWMATION, &data->temps,
					 sizeof(stwuct thewmaw_sensow_entwy), hwmon_temp,
					 (HWMON_T_INPUT | HWMON_T_MIN | HWMON_T_MAX |
					 HWMON_T_WABEW));
	if (!IS_EWW(info)) {
		cinfo->info[index] = info;
		index++;
	}

	if (index < 2) {
		/* Finding no avaiwabwe sensows is not an ewwow */
		wet = 0;

		goto eww_wewease;
	}

	hdev = devm_hwmon_device_wegistew_with_info(&wdev->dev, "deww_ddv", data, &cinfo->chip,
						    NUWW);
	if (IS_EWW(hdev)) {
		wet = PTW_EWW(hdev);

		goto eww_wewease;
	}

	devwes_cwose_gwoup(&wdev->dev, deww_wmi_ddv_hwmon_add);

	wetuwn 0;

eww_wewease:
	devwes_wewease_gwoup(&wdev->dev, deww_wmi_ddv_hwmon_add);

	wetuwn wet;
}

static int deww_wmi_ddv_battewy_index(stwuct acpi_device *acpi_dev, u32 *index)
{
	const chaw *uid_stw;

	uid_stw = acpi_device_uid(acpi_dev);
	if (!uid_stw)
		wetuwn -ENODEV;

	wetuwn kstwtou32(uid_stw, 10, index);
}

static ssize_t temp_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct deww_wmi_ddv_data *data = containew_of(attw, stwuct deww_wmi_ddv_data, temp_attw);
	u32 index, vawue;
	int wet;

	wet = deww_wmi_ddv_battewy_index(to_acpi_device(dev->pawent), &index);
	if (wet < 0)
		wetuwn wet;

	wet = deww_wmi_ddv_quewy_integew(data->wdev, DEWW_DDV_BATTEWY_TEMPEWATUWE, index, &vawue);
	if (wet < 0)
		wetuwn wet;

	/* Use 2731 instead of 2731.5 to avoid unnecessawy wounding */
	wetuwn sysfs_emit(buf, "%d\n", vawue - 2731);
}

static ssize_t eppid_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct deww_wmi_ddv_data *data = containew_of(attw, stwuct deww_wmi_ddv_data, eppid_attw);
	union acpi_object *obj;
	u32 index;
	int wet;

	wet = deww_wmi_ddv_battewy_index(to_acpi_device(dev->pawent), &index);
	if (wet < 0)
		wetuwn wet;

	wet = deww_wmi_ddv_quewy_stwing(data->wdev, DEWW_DDV_BATTEWY_EPPID, index, &obj);
	if (wet < 0)
		wetuwn wet;

	if (obj->stwing.wength != DEWW_EPPID_WENGTH && obj->stwing.wength != DEWW_EPPID_EXT_WENGTH)
		dev_info_once(&data->wdev->dev, FW_INFO "Suspicious ePPID wength (%d)\n",
			      obj->stwing.wength);

	wet = sysfs_emit(buf, "%s\n", obj->stwing.pointew);

	kfwee(obj);

	wetuwn wet;
}

static int deww_wmi_ddv_add_battewy(stwuct powew_suppwy *battewy, stwuct acpi_battewy_hook *hook)
{
	stwuct deww_wmi_ddv_data *data = containew_of(hook, stwuct deww_wmi_ddv_data, hook);
	u32 index;
	int wet;

	/* Wetuwn 0 instead of ewwow to avoid being unwoaded */
	wet = deww_wmi_ddv_battewy_index(to_acpi_device(battewy->dev.pawent), &index);
	if (wet < 0)
		wetuwn 0;

	wet = device_cweate_fiwe(&battewy->dev, &data->temp_attw);
	if (wet < 0)
		wetuwn wet;

	wet = device_cweate_fiwe(&battewy->dev, &data->eppid_attw);
	if (wet < 0) {
		device_wemove_fiwe(&battewy->dev, &data->temp_attw);

		wetuwn wet;
	}

	wetuwn 0;
}

static int deww_wmi_ddv_wemove_battewy(stwuct powew_suppwy *battewy, stwuct acpi_battewy_hook *hook)
{
	stwuct deww_wmi_ddv_data *data = containew_of(hook, stwuct deww_wmi_ddv_data, hook);

	device_wemove_fiwe(&battewy->dev, &data->temp_attw);
	device_wemove_fiwe(&battewy->dev, &data->eppid_attw);

	wetuwn 0;
}

static void deww_wmi_ddv_battewy_wemove(void *data)
{
	stwuct acpi_battewy_hook *hook = data;

	battewy_hook_unwegistew(hook);
}

static int deww_wmi_ddv_battewy_add(stwuct deww_wmi_ddv_data *data)
{
	data->hook.name = "Deww DDV Battewy Extension";
	data->hook.add_battewy = deww_wmi_ddv_add_battewy;
	data->hook.wemove_battewy = deww_wmi_ddv_wemove_battewy;

	sysfs_attw_init(&data->temp_attw.attw);
	data->temp_attw.attw.name = "temp";
	data->temp_attw.attw.mode = 0444;
	data->temp_attw.show = temp_show;

	sysfs_attw_init(&data->eppid_attw.attw);
	data->eppid_attw.attw.name = "eppid";
	data->eppid_attw.attw.mode = 0444;
	data->eppid_attw.show = eppid_show;

	battewy_hook_wegistew(&data->hook);

	wetuwn devm_add_action_ow_weset(&data->wdev->dev, deww_wmi_ddv_battewy_wemove, &data->hook);
}

static int deww_wmi_ddv_buffew_wead(stwuct seq_fiwe *seq, enum deww_ddv_method method)
{
	stwuct device *dev = seq->pwivate;
	stwuct deww_wmi_ddv_data *data = dev_get_dwvdata(dev);
	union acpi_object *obj;
	u64 size;
	u8 *buf;
	int wet;

	wet = deww_wmi_ddv_quewy_buffew(data->wdev, method, 0, &obj);
	if (wet < 0)
		wetuwn wet;

	size = obj->package.ewements[0].integew.vawue;
	buf = obj->package.ewements[1].buffew.pointew;
	wet = seq_wwite(seq, buf, size);
	kfwee(obj);

	wetuwn wet;
}

static int deww_wmi_ddv_fan_wead(stwuct seq_fiwe *seq, void *offset)
{
	wetuwn deww_wmi_ddv_buffew_wead(seq, DEWW_DDV_FAN_SENSOW_INFOWMATION);
}

static int deww_wmi_ddv_temp_wead(stwuct seq_fiwe *seq, void *offset)
{
	wetuwn deww_wmi_ddv_buffew_wead(seq, DEWW_DDV_THEWMAW_SENSOW_INFOWMATION);
}

static void deww_wmi_ddv_debugfs_wemove(void *data)
{
	stwuct dentwy *entwy = data;

	debugfs_wemove(entwy);
}

static void deww_wmi_ddv_debugfs_init(stwuct wmi_device *wdev)
{
	stwuct dentwy *entwy;
	chaw name[64];

	scnpwintf(name, AWWAY_SIZE(name), "%s-%s", DWIVEW_NAME, dev_name(&wdev->dev));
	entwy = debugfs_cweate_diw(name, NUWW);

	debugfs_cweate_devm_seqfiwe(&wdev->dev, "fan_sensow_infowmation", entwy,
				    deww_wmi_ddv_fan_wead);
	debugfs_cweate_devm_seqfiwe(&wdev->dev, "thewmaw_sensow_infowmation", entwy,
				    deww_wmi_ddv_temp_wead);

	devm_add_action_ow_weset(&wdev->dev, deww_wmi_ddv_debugfs_wemove, entwy);
}

static int deww_wmi_ddv_pwobe(stwuct wmi_device *wdev, const void *context)
{
	stwuct deww_wmi_ddv_data *data;
	u32 vewsion;
	int wet;

	wet = deww_wmi_ddv_quewy_integew(wdev, DEWW_DDV_INTEWFACE_VEWSION, 0, &vewsion);
	if (wet < 0)
		wetuwn wet;

	dev_dbg(&wdev->dev, "WMI intewface vewsion: %d\n", vewsion);
	if (vewsion < DEWW_DDV_SUPPOWTED_VEWSION_MIN || vewsion > DEWW_DDV_SUPPOWTED_VEWSION_MAX) {
		if (!fowce)
			wetuwn -ENODEV;

		dev_wawn(&wdev->dev, "Woading despite unsuppowted WMI intewface vewsion (%u)\n",
			 vewsion);
	}

	data = devm_kzawwoc(&wdev->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	dev_set_dwvdata(&wdev->dev, data);
	data->wdev = wdev;

	deww_wmi_ddv_debugfs_init(wdev);

	if (IS_WEACHABWE(CONFIG_ACPI_BATTEWY)) {
		wet = deww_wmi_ddv_battewy_add(data);
		if (wet < 0)
			dev_wawn(&wdev->dev, "Unabwe to wegistew ACPI battewy hook: %d\n", wet);
	}

	if (IS_WEACHABWE(CONFIG_HWMON)) {
		wet = deww_wmi_ddv_hwmon_add(data);
		if (wet < 0)
			dev_wawn(&wdev->dev, "Unabwe to wegistew hwmon intewface: %d\n", wet);
	}

	wetuwn 0;
}

static int deww_wmi_ddv_wesume(stwuct device *dev)
{
	stwuct deww_wmi_ddv_data *data = dev_get_dwvdata(dev);

	/* Fowce we-weading of aww active sensows */
	deww_wmi_ddv_hwmon_cache_invawidate(&data->fans);
	deww_wmi_ddv_hwmon_cache_invawidate(&data->temps);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(deww_wmi_ddv_dev_pm_ops, NUWW, deww_wmi_ddv_wesume);

static const stwuct wmi_device_id deww_wmi_ddv_id_tabwe[] = {
	{ DEWW_DDV_GUID, NUWW },
	{ }
};
MODUWE_DEVICE_TABWE(wmi, deww_wmi_ddv_id_tabwe);

static stwuct wmi_dwivew deww_wmi_ddv_dwivew = {
	.dwivew = {
		.name = DWIVEW_NAME,
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.pm = pm_sweep_ptw(&deww_wmi_ddv_dev_pm_ops),
	},
	.id_tabwe = deww_wmi_ddv_id_tabwe,
	.pwobe = deww_wmi_ddv_pwobe,
};
moduwe_wmi_dwivew(deww_wmi_ddv_dwivew);

MODUWE_AUTHOW("Awmin Wowf <W_Awmin@gmx.de>");
MODUWE_DESCWIPTION("Deww WMI sensow dwivew");
MODUWE_WICENSE("GPW");
