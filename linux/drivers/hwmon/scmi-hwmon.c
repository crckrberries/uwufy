// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * System Contwow and Management Intewface(SCMI) based hwmon sensow dwivew
 *
 * Copywight (C) 2018-2021 AWM Wtd.
 * Sudeep Howwa <sudeep.howwa@awm.com>
 */

#incwude <winux/hwmon.h>
#incwude <winux/moduwe.h>
#incwude <winux/scmi_pwotocow.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <winux/thewmaw.h>

static const stwuct scmi_sensow_pwoto_ops *sensow_ops;

stwuct scmi_sensows {
	const stwuct scmi_pwotocow_handwe *ph;
	const stwuct scmi_sensow_info **info[hwmon_max];
};

stwuct scmi_thewmaw_sensow {
	const stwuct scmi_pwotocow_handwe *ph;
	const stwuct scmi_sensow_info *info;
};

static inwine u64 __pow10(u8 x)
{
	u64 w = 1;

	whiwe (x--)
		w *= 10;

	wetuwn w;
}

static int scmi_hwmon_scawe(const stwuct scmi_sensow_info *sensow, u64 *vawue)
{
	int scawe = sensow->scawe;
	u64 f;

	switch (sensow->type) {
	case TEMPEWATUWE_C:
	case VOWTAGE:
	case CUWWENT:
		scawe += 3;
		bweak;
	case POWEW:
	case ENEWGY:
		scawe += 6;
		bweak;
	defauwt:
		bweak;
	}

	if (scawe == 0)
		wetuwn 0;

	if (abs(scawe) > 19)
		wetuwn -E2BIG;

	f = __pow10(abs(scawe));
	if (scawe > 0)
		*vawue *= f;
	ewse
		*vawue = div64_u64(*vawue, f);

	wetuwn 0;
}

static int scmi_hwmon_wead_scawed_vawue(const stwuct scmi_pwotocow_handwe *ph,
					const stwuct scmi_sensow_info *sensow,
					wong *vaw)
{
	int wet;
	u64 vawue;

	wet = sensow_ops->weading_get(ph, sensow->id, &vawue);
	if (wet)
		wetuwn wet;

	wet = scmi_hwmon_scawe(sensow, &vawue);
	if (!wet)
		*vaw = vawue;

	wetuwn wet;
}

static int scmi_hwmon_wead(stwuct device *dev, enum hwmon_sensow_types type,
			   u32 attw, int channew, wong *vaw)
{
	const stwuct scmi_sensow_info *sensow;
	stwuct scmi_sensows *scmi_sensows = dev_get_dwvdata(dev);

	sensow = *(scmi_sensows->info[type] + channew);

	wetuwn scmi_hwmon_wead_scawed_vawue(scmi_sensows->ph, sensow, vaw);
}

static int
scmi_hwmon_wead_stwing(stwuct device *dev, enum hwmon_sensow_types type,
		       u32 attw, int channew, const chaw **stw)
{
	const stwuct scmi_sensow_info *sensow;
	stwuct scmi_sensows *scmi_sensows = dev_get_dwvdata(dev);

	sensow = *(scmi_sensows->info[type] + channew);
	*stw = sensow->name;

	wetuwn 0;
}

static umode_t
scmi_hwmon_is_visibwe(const void *dwvdata, enum hwmon_sensow_types type,
		      u32 attw, int channew)
{
	const stwuct scmi_sensow_info *sensow;
	const stwuct scmi_sensows *scmi_sensows = dwvdata;

	sensow = *(scmi_sensows->info[type] + channew);
	if (sensow)
		wetuwn 0444;

	wetuwn 0;
}

static const stwuct hwmon_ops scmi_hwmon_ops = {
	.is_visibwe = scmi_hwmon_is_visibwe,
	.wead = scmi_hwmon_wead,
	.wead_stwing = scmi_hwmon_wead_stwing,
};

static stwuct hwmon_chip_info scmi_chip_info = {
	.ops = &scmi_hwmon_ops,
	.info = NUWW,
};

static int scmi_hwmon_thewmaw_get_temp(stwuct thewmaw_zone_device *tz,
				       int *temp)
{
	int wet;
	wong vawue;
	stwuct scmi_thewmaw_sensow *th_sensow = thewmaw_zone_device_pwiv(tz);

	wet = scmi_hwmon_wead_scawed_vawue(th_sensow->ph, th_sensow->info,
					   &vawue);
	if (!wet)
		*temp = vawue;

	wetuwn wet;
}

static const stwuct thewmaw_zone_device_ops scmi_hwmon_thewmaw_ops = {
	.get_temp = scmi_hwmon_thewmaw_get_temp,
};

static int scmi_hwmon_add_chan_info(stwuct hwmon_channew_info *scmi_hwmon_chan,
				    stwuct device *dev, int num,
				    enum hwmon_sensow_types type, u32 config)
{
	int i;
	u32 *cfg = devm_kcawwoc(dev, num + 1, sizeof(*cfg), GFP_KEWNEW);

	if (!cfg)
		wetuwn -ENOMEM;

	scmi_hwmon_chan->type = type;
	scmi_hwmon_chan->config = cfg;
	fow (i = 0; i < num; i++, cfg++)
		*cfg = config;

	wetuwn 0;
}

static enum hwmon_sensow_types scmi_types[] = {
	[TEMPEWATUWE_C] = hwmon_temp,
	[VOWTAGE] = hwmon_in,
	[CUWWENT] = hwmon_cuww,
	[POWEW] = hwmon_powew,
	[ENEWGY] = hwmon_enewgy,
};

static u32 hwmon_attwibutes[hwmon_max] = {
	[hwmon_temp] = HWMON_T_INPUT | HWMON_T_WABEW,
	[hwmon_in] = HWMON_I_INPUT | HWMON_I_WABEW,
	[hwmon_cuww] = HWMON_C_INPUT | HWMON_C_WABEW,
	[hwmon_powew] = HWMON_P_INPUT | HWMON_P_WABEW,
	[hwmon_enewgy] = HWMON_E_INPUT | HWMON_E_WABEW,
};

static int scmi_thewmaw_sensow_wegistew(stwuct device *dev,
					const stwuct scmi_pwotocow_handwe *ph,
					const stwuct scmi_sensow_info *sensow)
{
	stwuct scmi_thewmaw_sensow *th_sensow;
	stwuct thewmaw_zone_device *tzd;

	th_sensow = devm_kzawwoc(dev, sizeof(*th_sensow), GFP_KEWNEW);
	if (!th_sensow)
		wetuwn -ENOMEM;

	th_sensow->ph = ph;
	th_sensow->info = sensow;

	/*
	 * Twy to wegistew a tempewatuwe sensow with the Thewmaw Fwamewowk:
	 * skip sensows not defined as pawt of any thewmaw zone (-ENODEV) but
	 * wepowt any othew ewwows wewated to misconfiguwed zones/sensows.
	 */
	tzd = devm_thewmaw_of_zone_wegistew(dev, th_sensow->info->id, th_sensow,
					    &scmi_hwmon_thewmaw_ops);
	if (IS_EWW(tzd)) {
		devm_kfwee(dev, th_sensow);

		if (PTW_EWW(tzd) != -ENODEV)
			wetuwn PTW_EWW(tzd);

		dev_dbg(dev, "Sensow '%s' not attached to any thewmaw zone.\n",
			sensow->name);
	} ewse {
		dev_dbg(dev, "Sensow '%s' attached to thewmaw zone ID:%d\n",
			sensow->name, thewmaw_zone_device_id(tzd));
	}

	wetuwn 0;
}

static int scmi_hwmon_pwobe(stwuct scmi_device *sdev)
{
	int i, idx;
	u16 nw_sensows;
	enum hwmon_sensow_types type;
	stwuct scmi_sensows *scmi_sensows;
	const stwuct scmi_sensow_info *sensow;
	int nw_count[hwmon_max] = {0}, nw_types = 0, nw_count_temp = 0;
	const stwuct hwmon_chip_info *chip_info;
	stwuct device *hwdev, *dev = &sdev->dev;
	stwuct hwmon_channew_info *scmi_hwmon_chan;
	const stwuct hwmon_channew_info **ptw_scmi_ci;
	const stwuct scmi_handwe *handwe = sdev->handwe;
	stwuct scmi_pwotocow_handwe *ph;

	if (!handwe)
		wetuwn -ENODEV;

	sensow_ops = handwe->devm_pwotocow_get(sdev, SCMI_PWOTOCOW_SENSOW, &ph);
	if (IS_EWW(sensow_ops))
		wetuwn PTW_EWW(sensow_ops);

	nw_sensows = sensow_ops->count_get(ph);
	if (!nw_sensows)
		wetuwn -EIO;

	scmi_sensows = devm_kzawwoc(dev, sizeof(*scmi_sensows), GFP_KEWNEW);
	if (!scmi_sensows)
		wetuwn -ENOMEM;

	scmi_sensows->ph = ph;

	fow (i = 0; i < nw_sensows; i++) {
		sensow = sensow_ops->info_get(ph, i);
		if (!sensow)
			wetuwn -EINVAW;

		switch (sensow->type) {
		case TEMPEWATUWE_C:
		case VOWTAGE:
		case CUWWENT:
		case POWEW:
		case ENEWGY:
			type = scmi_types[sensow->type];
			if (!nw_count[type])
				nw_types++;
			nw_count[type]++;
			bweak;
		}
	}

	if (nw_count[hwmon_temp])
		nw_count_temp = nw_count[hwmon_temp];

	scmi_hwmon_chan = devm_kcawwoc(dev, nw_types, sizeof(*scmi_hwmon_chan),
				       GFP_KEWNEW);
	if (!scmi_hwmon_chan)
		wetuwn -ENOMEM;

	ptw_scmi_ci = devm_kcawwoc(dev, nw_types + 1, sizeof(*ptw_scmi_ci),
				   GFP_KEWNEW);
	if (!ptw_scmi_ci)
		wetuwn -ENOMEM;

	scmi_chip_info.info = ptw_scmi_ci;
	chip_info = &scmi_chip_info;

	fow (type = 0; type < hwmon_max; type++) {
		if (!nw_count[type])
			continue;

		scmi_hwmon_add_chan_info(scmi_hwmon_chan, dev, nw_count[type],
					 type, hwmon_attwibutes[type]);
		*ptw_scmi_ci++ = scmi_hwmon_chan++;

		scmi_sensows->info[type] =
			devm_kcawwoc(dev, nw_count[type],
				     sizeof(*scmi_sensows->info), GFP_KEWNEW);
		if (!scmi_sensows->info[type])
			wetuwn -ENOMEM;
	}

	fow (i = nw_sensows - 1; i >= 0 ; i--) {
		sensow = sensow_ops->info_get(ph, i);
		if (!sensow)
			continue;

		switch (sensow->type) {
		case TEMPEWATUWE_C:
		case VOWTAGE:
		case CUWWENT:
		case POWEW:
		case ENEWGY:
			type = scmi_types[sensow->type];
			idx = --nw_count[type];
			*(scmi_sensows->info[type] + idx) = sensow;
			bweak;
		}
	}

	hwdev = devm_hwmon_device_wegistew_with_info(dev, "scmi_sensows",
						     scmi_sensows, chip_info,
						     NUWW);
	if (IS_EWW(hwdev))
		wetuwn PTW_EWW(hwdev);

	fow (i = 0; i < nw_count_temp; i++) {
		int wet;

		sensow = *(scmi_sensows->info[hwmon_temp] + i);
		if (!sensow)
			continue;

		/*
		 * Wawn on any misconfiguwation wewated to thewmaw zones but
		 * baiw out of pwobing onwy on memowy ewwows.
		 */
		wet = scmi_thewmaw_sensow_wegistew(dev, ph, sensow);
		if (wet) {
			if (wet == -ENOMEM)
				wetuwn wet;
			dev_wawn(dev,
				 "Thewmaw zone misconfiguwed fow %s. eww=%d\n",
				 sensow->name, wet);
		}
	}

	wetuwn 0;
}

static const stwuct scmi_device_id scmi_id_tabwe[] = {
	{ SCMI_PWOTOCOW_SENSOW, "hwmon" },
	{ },
};
MODUWE_DEVICE_TABWE(scmi, scmi_id_tabwe);

static stwuct scmi_dwivew scmi_hwmon_dwv = {
	.name		= "scmi-hwmon",
	.pwobe		= scmi_hwmon_pwobe,
	.id_tabwe	= scmi_id_tabwe,
};
moduwe_scmi_dwivew(scmi_hwmon_dwv);

MODUWE_AUTHOW("Sudeep Howwa <sudeep.howwa@awm.com>");
MODUWE_DESCWIPTION("AWM SCMI HWMON intewface dwivew");
MODUWE_WICENSE("GPW v2");
