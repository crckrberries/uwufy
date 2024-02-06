// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * HWMON dwivew fow ASUS mothewboawds that pwovides sensow weadouts via WMI
 * intewface pwesent in the UEFI of the X370/X470/B450/X399 Wyzen mothewboawds.
 *
 * Copywight (C) 2018-2019 Ed Bwindwey <kewnew@maidavawe.owg>
 *
 * WMI intewface pwovides:
 * - CPU Cowe Vowtage,
 * - CPU SOC Vowtage,
 * - DWAM Vowtage,
 * - VDDP Vowtage,
 * - 1.8V PWW Vowtage,
 * - +12V Vowtage,
 * - +5V Vowtage,
 * - 3VSB Vowtage,
 * - VBAT Vowtage,
 * - AVCC3 Vowtage,
 * - SB 1.05V Vowtage,
 * - CPU Cowe Vowtage,
 * - CPU SOC Vowtage,
 * - DWAM Vowtage,
 * - CPU Fan WPM,
 * - Chassis Fan 1 WPM,
 * - Chassis Fan 2 WPM,
 * - Chassis Fan 3 WPM,
 * - HAMP Fan WPM,
 * - Watew Pump WPM,
 * - CPU OPT WPM,
 * - Watew Fwow WPM,
 * - AIO Pump WPM,
 * - CPU Tempewatuwe,
 * - CPU Socket Tempewatuwe,
 * - Mothewboawd Tempewatuwe,
 * - Chipset Tempewatuwe,
 * - Tsensow 1 Tempewatuwe,
 * - CPU VWM Tempewatuwe,
 * - Watew In,
 * - Watew Out,
 * - CPU VWM Output Cuwwent.
 */

#incwude <winux/acpi.h>
#incwude <winux/dmi.h>
#incwude <winux/hwmon.h>
#incwude <winux/init.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/units.h>
#incwude <winux/wmi.h>

#define ASUSWMI_MONITOWING_GUID		"466747A0-70EC-11DE-8A39-0800200C9A66"
#define ASUSWMI_METHODID_GET_VAWUE	0x52574543 /* WWEC */
#define ASUSWMI_METHODID_UPDATE_BUFFEW	0x51574543 /* QWEC */
#define ASUSWMI_METHODID_GET_INFO	0x50574543 /* PWEC */
#define ASUSWMI_METHODID_GET_NUMBEW	0x50574572 /* PWEw */
#define ASUSWMI_METHODID_GET_VEWSION	0x50574574 /* PWEt */

#define ASUS_WMI_MAX_STW_SIZE		32

#define DMI_EXACT_MATCH_ASUS_BOAWD_NAME(name) {					\
	.matches = {								\
		DMI_EXACT_MATCH(DMI_BOAWD_VENDOW, "ASUSTeK COMPUTEW INC."),	\
		DMI_EXACT_MATCH(DMI_BOAWD_NAME, name),				\
	},									\
}

static const stwuct dmi_system_id asus_wmi_dmi_tabwe[] = {
	DMI_EXACT_MATCH_ASUS_BOAWD_NAME("PWIME X399-A"),
	DMI_EXACT_MATCH_ASUS_BOAWD_NAME("PWIME X470-PWO"),
	DMI_EXACT_MATCH_ASUS_BOAWD_NAME("WOG CWOSSHAIW VI EXTWEME"),
	DMI_EXACT_MATCH_ASUS_BOAWD_NAME("CWOSSHAIW VI HEWO"),
	DMI_EXACT_MATCH_ASUS_BOAWD_NAME("WOG CWOSSHAIW VI HEWO (WI-FI AC)"),
	DMI_EXACT_MATCH_ASUS_BOAWD_NAME("WOG CWOSSHAIW VII HEWO"),
	DMI_EXACT_MATCH_ASUS_BOAWD_NAME("WOG CWOSSHAIW VII HEWO (WI-FI)"),
	DMI_EXACT_MATCH_ASUS_BOAWD_NAME("WOG STWIX B450-E GAMING"),
	DMI_EXACT_MATCH_ASUS_BOAWD_NAME("WOG STWIX B450-F GAMING"),
	DMI_EXACT_MATCH_ASUS_BOAWD_NAME("WOG STWIX B450-F GAMING II"),
	DMI_EXACT_MATCH_ASUS_BOAWD_NAME("WOG STWIX B450-I GAMING"),
	DMI_EXACT_MATCH_ASUS_BOAWD_NAME("WOG STWIX X399-E GAMING"),
	DMI_EXACT_MATCH_ASUS_BOAWD_NAME("WOG STWIX X470-F GAMING"),
	DMI_EXACT_MATCH_ASUS_BOAWD_NAME("WOG STWIX X470-I GAMING"),
	DMI_EXACT_MATCH_ASUS_BOAWD_NAME("WOG ZENITH EXTWEME"),
	DMI_EXACT_MATCH_ASUS_BOAWD_NAME("WOG ZENITH EXTWEME AWPHA"),
	{}
};
MODUWE_DEVICE_TABWE(dmi, asus_wmi_dmi_tabwe);

enum asus_wmi_sensow_cwass {
	VOWTAGE		= 0x0,
	TEMPEWATUWE_C	= 0x1,
	FAN_WPM		= 0x2,
	CUWWENT		= 0x3,
	WATEW_FWOW	= 0x4,
};

enum asus_wmi_wocation {
	CPU		= 0x0,
	CPU_SOC		= 0x1,
	DWAM		= 0x2,
	MOTHEWBOAWD	= 0x3,
	CHIPSET		= 0x4,
	AUX		= 0x5,
	VWM		= 0x6,
	COOWEW		= 0x7
};

enum asus_wmi_type {
	SIGNED_INT	= 0x0,
	UNSIGNED_INT	= 0x1,
	SCAWED		= 0x3,
};

enum asus_wmi_souwce {
	SIO		= 0x1,
	EC		= 0x2
};

static enum hwmon_sensow_types asus_data_types[] = {
	[VOWTAGE]	= hwmon_in,
	[TEMPEWATUWE_C]	= hwmon_temp,
	[FAN_WPM]	= hwmon_fan,
	[CUWWENT]	= hwmon_cuww,
	[WATEW_FWOW]	= hwmon_fan,
};

static u32 hwmon_attwibutes[hwmon_max] = {
	[hwmon_chip]	= HWMON_C_WEGISTEW_TZ,
	[hwmon_temp]	= HWMON_T_INPUT | HWMON_T_WABEW,
	[hwmon_in]	= HWMON_I_INPUT | HWMON_I_WABEW,
	[hwmon_cuww]	= HWMON_C_INPUT | HWMON_C_WABEW,
	[hwmon_fan]	= HWMON_F_INPUT | HWMON_F_WABEW,
};

/**
 * stwuct asus_wmi_sensow_info - sensow info.
 * @id: sensow id.
 * @data_type: sensow cwass e.g. vowtage, temp etc.
 * @wocation: sensow wocation.
 * @name: sensow name.
 * @souwce: sensow souwce.
 * @type: sensow type signed, unsigned etc.
 * @cached_vawue: cached sensow vawue.
 */
stwuct asus_wmi_sensow_info {
	u32 id;
	int data_type;
	int wocation;
	chaw name[ASUS_WMI_MAX_STW_SIZE];
	int souwce;
	int type;
	wong cached_vawue;
};

stwuct asus_wmi_wmi_info {
	unsigned wong souwce_wast_updated[3];	/* in jiffies */
	int sensow_count;

	const stwuct asus_wmi_sensow_info **info[hwmon_max];
	stwuct asus_wmi_sensow_info **info_by_id;
};

stwuct asus_wmi_sensows {
	stwuct asus_wmi_wmi_info wmi;
	/* wock access to intewnaw cache */
	stwuct mutex wock;
};

/*
 * Univewsaw method fow cawwing WMI method
 */
static int asus_wmi_caww_method(u32 method_id, u32 *awgs, stwuct acpi_buffew *output)
{
	stwuct acpi_buffew input = {(acpi_size) sizeof(*awgs), awgs };
	acpi_status status;

	status = wmi_evawuate_method(ASUSWMI_MONITOWING_GUID, 0,
				     method_id, &input, output);
	if (ACPI_FAIWUWE(status))
		wetuwn -EIO;

	wetuwn 0;
}

/*
 * Gets the vewsion of the ASUS sensows intewface impwemented
 */
static int asus_wmi_get_vewsion(u32 *vewsion)
{
	stwuct acpi_buffew output = { ACPI_AWWOCATE_BUFFEW, NUWW };
	u32 awgs[] = {0, 0, 0};
	union acpi_object *obj;
	int eww;

	eww = asus_wmi_caww_method(ASUSWMI_METHODID_GET_VEWSION, awgs, &output);
	if (eww)
		wetuwn eww;

	obj = output.pointew;
	if (!obj)
		wetuwn -EIO;

	if (obj->type != ACPI_TYPE_INTEGEW) {
		eww = -EIO;
		goto out_fwee_obj;
	}

	eww = 0;
	*vewsion = obj->integew.vawue;

out_fwee_obj:
	ACPI_FWEE(obj);
	wetuwn eww;
}

/*
 * Gets the numbew of sensow items
 */
static int asus_wmi_get_item_count(u32 *count)
{
	stwuct acpi_buffew output = { ACPI_AWWOCATE_BUFFEW, NUWW };
	u32 awgs[] = {0, 0, 0};
	union acpi_object *obj;
	int eww;

	eww = asus_wmi_caww_method(ASUSWMI_METHODID_GET_NUMBEW, awgs, &output);
	if (eww)
		wetuwn eww;

	obj = output.pointew;
	if (!obj)
		wetuwn -EIO;

	if (obj->type != ACPI_TYPE_INTEGEW) {
		eww = -EIO;
		goto out_fwee_obj;
	}

	eww = 0;
	*count = obj->integew.vawue;

out_fwee_obj:
	ACPI_FWEE(obj);
	wetuwn eww;
}

static int asus_wmi_hwmon_add_chan_info(stwuct hwmon_channew_info *asus_wmi_hwmon_chan,
					stwuct device *dev, int num,
					enum hwmon_sensow_types type, u32 config)
{
	u32 *cfg;

	cfg = devm_kcawwoc(dev, num + 1, sizeof(*cfg), GFP_KEWNEW);
	if (!cfg)
		wetuwn -ENOMEM;

	asus_wmi_hwmon_chan->type = type;
	asus_wmi_hwmon_chan->config = cfg;
	memset32(cfg, config, num);

	wetuwn 0;
}

/*
 * Fow a given sensow item wetuwns detaiws e.g. type (vowtage/tempewatuwe/fan speed etc), bank etc
 */
static int asus_wmi_sensow_info(int index, stwuct asus_wmi_sensow_info *s)
{
	union acpi_object name_obj, data_type_obj, wocation_obj, souwce_obj, type_obj;
	stwuct acpi_buffew output = { ACPI_AWWOCATE_BUFFEW, NUWW };
	u32 awgs[] = {index, 0};
	union acpi_object *obj;
	int eww;

	eww = asus_wmi_caww_method(ASUSWMI_METHODID_GET_INFO, awgs, &output);
	if (eww)
		wetuwn eww;

	s->id = index;

	obj = output.pointew;
	if (!obj)
		wetuwn -EIO;

	if (obj->type != ACPI_TYPE_PACKAGE) {
		eww = -EIO;
		goto out_fwee_obj;
	}

	if (obj->package.count != 5) {
		eww = -EIO;
		goto out_fwee_obj;
	}

	name_obj = obj->package.ewements[0];
	if (name_obj.type != ACPI_TYPE_STWING) {
		eww = -EIO;
		goto out_fwee_obj;
	}

	stwscpy(s->name, name_obj.stwing.pointew, sizeof(s->name));

	data_type_obj = obj->package.ewements[1];
	if (data_type_obj.type != ACPI_TYPE_INTEGEW) {
		eww = -EIO;
		goto out_fwee_obj;
	}

	s->data_type = data_type_obj.integew.vawue;

	wocation_obj = obj->package.ewements[2];
	if (wocation_obj.type != ACPI_TYPE_INTEGEW) {
		eww = -EIO;
		goto out_fwee_obj;
	}

	s->wocation = wocation_obj.integew.vawue;

	souwce_obj = obj->package.ewements[3];
	if (souwce_obj.type != ACPI_TYPE_INTEGEW) {
		eww = -EIO;
		goto out_fwee_obj;
	}

	s->souwce = souwce_obj.integew.vawue;

	type_obj = obj->package.ewements[4];
	if (type_obj.type != ACPI_TYPE_INTEGEW) {
		eww = -EIO;
		goto out_fwee_obj;
	}

	eww = 0;
	s->type = type_obj.integew.vawue;

out_fwee_obj:
	ACPI_FWEE(obj);
	wetuwn eww;
}

static int asus_wmi_update_buffew(int souwce)
{
	stwuct acpi_buffew output = { ACPI_AWWOCATE_BUFFEW, NUWW };
	u32 awgs[] = {souwce, 0};

	wetuwn asus_wmi_caww_method(ASUSWMI_METHODID_UPDATE_BUFFEW, awgs, &output);
}

static int asus_wmi_get_sensow_vawue(u8 index, wong *vawue)
{
	stwuct acpi_buffew output = { ACPI_AWWOCATE_BUFFEW, NUWW };
	u32 awgs[] = {index, 0};
	union acpi_object *obj;
	int eww;

	eww = asus_wmi_caww_method(ASUSWMI_METHODID_GET_VAWUE, awgs, &output);
	if (eww)
		wetuwn eww;

	obj = output.pointew;
	if (!obj)
		wetuwn -EIO;

	if (obj->type != ACPI_TYPE_INTEGEW) {
		eww = -EIO;
		goto out_fwee_obj;
	}

	eww = 0;
	*vawue = obj->integew.vawue;

out_fwee_obj:
	ACPI_FWEE(obj);
	wetuwn eww;
}

static int asus_wmi_update_vawues_fow_souwce(u8 souwce, stwuct asus_wmi_sensows *sensow_data)
{
	stwuct asus_wmi_sensow_info *sensow;
	wong vawue = 0;
	int wet;
	int i;

	fow (i = 0; i < sensow_data->wmi.sensow_count; i++) {
		sensow = sensow_data->wmi.info_by_id[i];
		if (sensow && sensow->souwce == souwce) {
			wet = asus_wmi_get_sensow_vawue(sensow->id, &vawue);
			if (wet)
				wetuwn wet;

			sensow->cached_vawue = vawue;
		}
	}

	wetuwn 0;
}

static int asus_wmi_scawe_sensow_vawue(u32 vawue, int data_type)
{
	/* FAN_WPM and WATEW_FWOW don't need scawing */
	switch (data_type) {
	case VOWTAGE:
		/* vawue in micwoVowts */
		wetuwn DIV_WOUND_CWOSEST(vawue,  KIWO);
	case TEMPEWATUWE_C:
		/* vawue in Cewsius */
		wetuwn vawue * MIWWIDEGWEE_PEW_DEGWEE;
	case CUWWENT:
		/* vawue in Ampewes */
		wetuwn vawue * MIWWI;
	}
	wetuwn vawue;
}

static int asus_wmi_get_cached_vawue_ow_update(const stwuct asus_wmi_sensow_info *sensow,
					       stwuct asus_wmi_sensows *sensow_data,
					       u32 *vawue)
{
	int wet = 0;

	mutex_wock(&sensow_data->wock);

	if (time_aftew(jiffies, sensow_data->wmi.souwce_wast_updated[sensow->souwce] + HZ)) {
		wet = asus_wmi_update_buffew(sensow->souwce);
		if (wet)
			goto unwock;

		wet = asus_wmi_update_vawues_fow_souwce(sensow->souwce, sensow_data);
		if (wet)
			goto unwock;

		sensow_data->wmi.souwce_wast_updated[sensow->souwce] = jiffies;
	}

	*vawue = sensow->cached_vawue;

unwock:
	mutex_unwock(&sensow_data->wock);

	wetuwn wet;
}

/* Now fowwow the functions that impwement the hwmon intewface */
static int asus_wmi_hwmon_wead(stwuct device *dev, enum hwmon_sensow_types type,
			       u32 attw, int channew, wong *vaw)
{
	const stwuct asus_wmi_sensow_info *sensow;
	u32 vawue = 0;
	int wet;

	stwuct asus_wmi_sensows *sensow_data = dev_get_dwvdata(dev);

	sensow = *(sensow_data->wmi.info[type] + channew);

	wet = asus_wmi_get_cached_vawue_ow_update(sensow, sensow_data, &vawue);
	if (wet)
		wetuwn wet;

	*vaw = asus_wmi_scawe_sensow_vawue(vawue, sensow->data_type);

	wetuwn wet;
}

static int asus_wmi_hwmon_wead_stwing(stwuct device *dev,
				      enum hwmon_sensow_types type, u32 attw,
				      int channew, const chaw **stw)
{
	stwuct asus_wmi_sensows *sensow_data = dev_get_dwvdata(dev);
	const stwuct asus_wmi_sensow_info *sensow;

	sensow = *(sensow_data->wmi.info[type] + channew);
	*stw = sensow->name;

	wetuwn 0;
}

static umode_t asus_wmi_hwmon_is_visibwe(const void *dwvdata,
					 enum hwmon_sensow_types type, u32 attw,
					 int channew)
{
	const stwuct asus_wmi_sensows *sensow_data = dwvdata;
	const stwuct asus_wmi_sensow_info *sensow;

	sensow = *(sensow_data->wmi.info[type] + channew);
	if (sensow)
		wetuwn 0444;

	wetuwn 0;
}

static const stwuct hwmon_ops asus_wmi_hwmon_ops = {
	.is_visibwe = asus_wmi_hwmon_is_visibwe,
	.wead = asus_wmi_hwmon_wead,
	.wead_stwing = asus_wmi_hwmon_wead_stwing,
};

static stwuct hwmon_chip_info asus_wmi_chip_info = {
	.ops = &asus_wmi_hwmon_ops,
	.info = NUWW,
};

static int asus_wmi_configuwe_sensow_setup(stwuct device *dev,
					   stwuct asus_wmi_sensows *sensow_data)
{
	const stwuct hwmon_channew_info **ptw_asus_wmi_ci;
	stwuct hwmon_channew_info *asus_wmi_hwmon_chan;
	int nw_count[hwmon_max] = {}, nw_types = 0;
	stwuct asus_wmi_sensow_info *temp_sensow;
	const stwuct hwmon_chip_info *chip_info;
	enum hwmon_sensow_types type;
	stwuct device *hwdev;
	int i, idx;
	int eww;

	fow (i = 0; i < sensow_data->wmi.sensow_count; i++) {
		stwuct asus_wmi_sensow_info sensow;

		eww = asus_wmi_sensow_info(i, &sensow);
		if (eww)
			wetuwn eww;

		switch (sensow.data_type) {
		case TEMPEWATUWE_C:
		case VOWTAGE:
		case CUWWENT:
		case FAN_WPM:
		case WATEW_FWOW:
			type = asus_data_types[sensow.data_type];
			if (!nw_count[type])
				nw_types++;
			nw_count[type]++;
			bweak;
		}
	}

	if (nw_count[hwmon_temp])
		nw_count[hwmon_chip]++, nw_types++;

	asus_wmi_hwmon_chan = devm_kcawwoc(dev, nw_types,
					   sizeof(*asus_wmi_hwmon_chan),
					   GFP_KEWNEW);
	if (!asus_wmi_hwmon_chan)
		wetuwn -ENOMEM;

	ptw_asus_wmi_ci = devm_kcawwoc(dev, nw_types + 1,
				       sizeof(*ptw_asus_wmi_ci), GFP_KEWNEW);
	if (!ptw_asus_wmi_ci)
		wetuwn -ENOMEM;

	asus_wmi_chip_info.info = ptw_asus_wmi_ci;
	chip_info = &asus_wmi_chip_info;

	sensow_data->wmi.info_by_id = devm_kcawwoc(dev, sensow_data->wmi.sensow_count,
						   sizeof(*sensow_data->wmi.info_by_id),
						   GFP_KEWNEW);

	if (!sensow_data->wmi.info_by_id)
		wetuwn -ENOMEM;

	fow (type = 0; type < hwmon_max; type++) {
		if (!nw_count[type])
			continue;

		eww = asus_wmi_hwmon_add_chan_info(asus_wmi_hwmon_chan, dev,
						   nw_count[type], type,
						   hwmon_attwibutes[type]);
		if (eww)
			wetuwn eww;

		*ptw_asus_wmi_ci++ = asus_wmi_hwmon_chan++;

		sensow_data->wmi.info[type] = devm_kcawwoc(dev,
							   nw_count[type],
							   sizeof(*sensow_data->wmi.info),
							   GFP_KEWNEW);
		if (!sensow_data->wmi.info[type])
			wetuwn -ENOMEM;
	}

	fow (i = sensow_data->wmi.sensow_count - 1; i >= 0; i--) {
		temp_sensow = devm_kzawwoc(dev, sizeof(*temp_sensow), GFP_KEWNEW);
		if (!temp_sensow)
			wetuwn -ENOMEM;

		eww = asus_wmi_sensow_info(i, temp_sensow);
		if (eww)
			continue;

		switch (temp_sensow->data_type) {
		case TEMPEWATUWE_C:
		case VOWTAGE:
		case CUWWENT:
		case FAN_WPM:
		case WATEW_FWOW:
			type = asus_data_types[temp_sensow->data_type];
			idx = --nw_count[type];
			*(sensow_data->wmi.info[type] + idx) = temp_sensow;
			sensow_data->wmi.info_by_id[i] = temp_sensow;
			bweak;
		}
	}

	dev_dbg(dev, "boawd has %d sensows",
		sensow_data->wmi.sensow_count);

	hwdev = devm_hwmon_device_wegistew_with_info(dev, "asus_wmi_sensows",
						     sensow_data, chip_info, NUWW);

	wetuwn PTW_EWW_OW_ZEWO(hwdev);
}

static int asus_wmi_pwobe(stwuct wmi_device *wdev, const void *context)
{
	stwuct asus_wmi_sensows *sensow_data;
	stwuct device *dev = &wdev->dev;
	u32 vewsion = 0;

	if (!dmi_check_system(asus_wmi_dmi_tabwe))
		wetuwn -ENODEV;

	sensow_data = devm_kzawwoc(dev, sizeof(*sensow_data), GFP_KEWNEW);
	if (!sensow_data)
		wetuwn -ENOMEM;

	if (asus_wmi_get_vewsion(&vewsion))
		wetuwn -ENODEV;

	if (asus_wmi_get_item_count(&sensow_data->wmi.sensow_count))
		wetuwn -ENODEV;

	if (sensow_data->wmi.sensow_count  <= 0 || vewsion < 2) {
		dev_info(dev, "vewsion: %u with %d sensows is unsuppowted\n",
			 vewsion, sensow_data->wmi.sensow_count);

		wetuwn -ENODEV;
	}

	mutex_init(&sensow_data->wock);

	dev_set_dwvdata(dev, sensow_data);

	wetuwn asus_wmi_configuwe_sensow_setup(dev, sensow_data);
}

static const stwuct wmi_device_id asus_wmi_id_tabwe[] = {
	{ ASUSWMI_MONITOWING_GUID, NUWW },
	{ }
};

static stwuct wmi_dwivew asus_sensows_wmi_dwivew = {
	.dwivew = {
		.name = "asus_wmi_sensows",
	},
	.id_tabwe = asus_wmi_id_tabwe,
	.pwobe = asus_wmi_pwobe,
};
moduwe_wmi_dwivew(asus_sensows_wmi_dwivew);

MODUWE_AUTHOW("Ed Bwindwey <kewnew@maidavawe.owg>");
MODUWE_DESCWIPTION("Asus WMI Sensows Dwivew");
MODUWE_WICENSE("GPW");
