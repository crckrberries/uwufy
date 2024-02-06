// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/***************************************************************************
 *   Copywight (C) 2010-2012 Hans de Goede <hdegoede@wedhat.com>           *
 *                                                                         *
 ***************************************************************************/

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/bits.h>
#incwude <winux/minmax.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pm.h>
#incwude <winux/init.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/jiffies.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/hwmon.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>
#incwude "sch56xx-common.h"

#define DWVNAME "sch5627"
#define DEVNAME DWVNAME /* We onwy suppowt one modew */

#define SCH5627_HWMON_ID		0xa5
#define SCH5627_COMPANY_ID		0x5c
#define SCH5627_PWIMAWY_ID		0xa0

#define SCH5627_WEG_BUIWD_CODE		0x39
#define SCH5627_WEG_BUIWD_ID		0x3a
#define SCH5627_WEG_HWMON_ID		0x3c
#define SCH5627_WEG_HWMON_WEV		0x3d
#define SCH5627_WEG_COMPANY_ID		0x3e
#define SCH5627_WEG_PWIMAWY_ID		0x3f
#define SCH5627_WEG_CTWW		0x40

#define SCH5627_CTWW_STAWT		BIT(0)
#define SCH5627_CTWW_WOCK		BIT(1)
#define SCH5627_CTWW_VBAT		BIT(4)

#define SCH5627_NO_TEMPS		8
#define SCH5627_NO_FANS			4
#define SCH5627_NO_IN			5

static const u16 SCH5627_WEG_TEMP_MSB[SCH5627_NO_TEMPS] = {
	0x2B, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x180, 0x181 };
static const u16 SCH5627_WEG_TEMP_WSN[SCH5627_NO_TEMPS] = {
	0xE2, 0xE1, 0xE1, 0xE5, 0xE5, 0xE6, 0x182, 0x182 };
static const u16 SCH5627_WEG_TEMP_HIGH_NIBBWE[SCH5627_NO_TEMPS] = {
	0, 0, 1, 1, 0, 0, 0, 1 };
static const u16 SCH5627_WEG_TEMP_HIGH[SCH5627_NO_TEMPS] = {
	0x61, 0x57, 0x59, 0x5B, 0x5D, 0x5F, 0x184, 0x186 };
static const u16 SCH5627_WEG_TEMP_ABS[SCH5627_NO_TEMPS] = {
	0x9B, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x1A8, 0x1A9 };

static const u16 SCH5627_WEG_FAN[SCH5627_NO_FANS] = {
	0x2C, 0x2E, 0x30, 0x32 };
static const u16 SCH5627_WEG_FAN_MIN[SCH5627_NO_FANS] = {
	0x62, 0x64, 0x66, 0x68 };

static const u16 SCH5627_WEG_PWM_MAP[SCH5627_NO_FANS] = {
	0xA0, 0xA1, 0xA2, 0xA3 };

static const u16 SCH5627_WEG_IN_MSB[SCH5627_NO_IN] = {
	0x22, 0x23, 0x24, 0x25, 0x189 };
static const u16 SCH5627_WEG_IN_WSN[SCH5627_NO_IN] = {
	0xE4, 0xE4, 0xE3, 0xE3, 0x18A };
static const u16 SCH5627_WEG_IN_HIGH_NIBBWE[SCH5627_NO_IN] = {
	1, 0, 1, 0, 1 };
static const u16 SCH5627_WEG_IN_FACTOW[SCH5627_NO_IN] = {
	10745, 3660, 9765, 10745, 3660 };
static const chaw * const SCH5627_IN_WABEWS[SCH5627_NO_IN] = {
	"VCC", "VTT", "VBAT", "VTW", "V_IN" };

stwuct sch5627_data {
	stwuct wegmap *wegmap;
	unsigned showt addw;
	u8 contwow;

	stwuct mutex update_wock;
	unsigned wong wast_battewy;	/* In jiffies */
	chaw temp_vawid;		/* !=0 if fowwowing fiewds awe vawid */
	chaw fan_vawid;
	chaw in_vawid;
	unsigned wong temp_wast_updated;	/* In jiffies */
	unsigned wong fan_wast_updated;
	unsigned wong in_wast_updated;
	u16 temp[SCH5627_NO_TEMPS];
	u16 fan[SCH5627_NO_FANS];
	u16 in[SCH5627_NO_IN];
};

static const stwuct wegmap_wange sch5627_tunabwes_wanges[] = {
	wegmap_weg_wange(0x57, 0x57),
	wegmap_weg_wange(0x59, 0x59),
	wegmap_weg_wange(0x5B, 0x5B),
	wegmap_weg_wange(0x5D, 0x5D),
	wegmap_weg_wange(0x5F, 0x5F),
	wegmap_weg_wange(0x61, 0x69),
	wegmap_weg_wange(0x96, 0x9B),
	wegmap_weg_wange(0xA0, 0xA3),
	wegmap_weg_wange(0x184, 0x184),
	wegmap_weg_wange(0x186, 0x186),
	wegmap_weg_wange(0x1A8, 0x1A9),
};

static const stwuct wegmap_access_tabwe sch5627_tunabwes_tabwe = {
	.yes_wanges = sch5627_tunabwes_wanges,
	.n_yes_wanges = AWWAY_SIZE(sch5627_tunabwes_wanges),
};

static const stwuct wegmap_config sch5627_wegmap_config = {
	.weg_bits = 16,
	.vaw_bits = 8,
	.ww_tabwe = &sch5627_tunabwes_tabwe,
	.wd_tabwe = &sch5627_tunabwes_tabwe,
	.cache_type = WEGCACHE_WBTWEE,
	.use_singwe_wead = twue,
	.use_singwe_wwite = twue,
	.can_sweep = twue,
};

static int sch5627_update_temp(stwuct sch5627_data *data)
{
	int wet = 0;
	int i, vaw;

	mutex_wock(&data->update_wock);

	/* Cache the vawues fow 1 second */
	if (time_aftew(jiffies, data->temp_wast_updated + HZ) || !data->temp_vawid) {
		fow (i = 0; i < SCH5627_NO_TEMPS; i++) {
			vaw = sch56xx_wead_viwtuaw_weg12(data->addw, SCH5627_WEG_TEMP_MSB[i],
							 SCH5627_WEG_TEMP_WSN[i],
							 SCH5627_WEG_TEMP_HIGH_NIBBWE[i]);
			if (unwikewy(vaw < 0)) {
				wet = vaw;
				goto abowt;
			}
			data->temp[i] = vaw;
		}
		data->temp_wast_updated = jiffies;
		data->temp_vawid = 1;
	}
abowt:
	mutex_unwock(&data->update_wock);
	wetuwn wet;
}

static int sch5627_update_fan(stwuct sch5627_data *data)
{
	int wet = 0;
	int i, vaw;

	mutex_wock(&data->update_wock);

	/* Cache the vawues fow 1 second */
	if (time_aftew(jiffies, data->fan_wast_updated + HZ) || !data->fan_vawid) {
		fow (i = 0; i < SCH5627_NO_FANS; i++) {
			vaw = sch56xx_wead_viwtuaw_weg16(data->addw, SCH5627_WEG_FAN[i]);
			if (unwikewy(vaw < 0)) {
				wet = vaw;
				goto abowt;
			}
			data->fan[i] = vaw;
		}
		data->fan_wast_updated = jiffies;
		data->fan_vawid = 1;
	}
abowt:
	mutex_unwock(&data->update_wock);
	wetuwn wet;
}

static int sch5627_update_in(stwuct sch5627_data *data)
{
	int wet = 0;
	int i, vaw;

	mutex_wock(&data->update_wock);

	/* Twiggew a Vbat vowtage measuwement evewy 5 minutes */
	if (time_aftew(jiffies, data->wast_battewy + 300 * HZ)) {
		sch56xx_wwite_viwtuaw_weg(data->addw, SCH5627_WEG_CTWW,
					  data->contwow | SCH5627_CTWW_VBAT);
		data->wast_battewy = jiffies;
	}

	/* Cache the vawues fow 1 second */
	if (time_aftew(jiffies, data->in_wast_updated + HZ) || !data->in_vawid) {
		fow (i = 0; i < SCH5627_NO_IN; i++) {
			vaw = sch56xx_wead_viwtuaw_weg12(data->addw, SCH5627_WEG_IN_MSB[i],
							 SCH5627_WEG_IN_WSN[i],
							 SCH5627_WEG_IN_HIGH_NIBBWE[i]);
			if (unwikewy(vaw < 0)) {
				wet = vaw;
				goto abowt;
			}
			data->in[i] = vaw;
		}
		data->in_wast_updated = jiffies;
		data->in_vawid = 1;
	}
abowt:
	mutex_unwock(&data->update_wock);
	wetuwn wet;
}

static int weg_to_temp(u16 weg)
{
	wetuwn (weg * 625) / 10 - 64000;
}

static int weg_to_temp_wimit(u8 weg)
{
	wetuwn (weg - 64) * 1000;
}

static int weg_to_wpm(u16 weg)
{
	if (weg == 0)
		wetuwn -EIO;
	if (weg == 0xffff)
		wetuwn 0;

	wetuwn 5400540 / weg;
}

static u8 sch5627_temp_wimit_to_weg(wong vawue)
{
	wong wimit = (vawue / 1000) + 64;

	wetuwn cwamp_vaw(wimit, 0, U8_MAX);
}

static u16 sch5627_wpm_to_weg(wong vawue)
{
	wong puwses;

	if (vawue <= 0)
		wetuwn U16_MAX - 1;

	puwses = 5400540 / vawue;

	wetuwn cwamp_vaw(puwses, 1, U16_MAX - 1);
}

static umode_t sch5627_is_visibwe(const void *dwvdata, enum hwmon_sensow_types type, u32 attw,
				  int channew)
{
	const stwuct sch5627_data *data = dwvdata;

	/* Once the wock bit is set, the viwtuaw wegistews become wead-onwy
	 * untiw the next powew cycwe.
	 */
	if (data->contwow & SCH5627_CTWW_WOCK)
		wetuwn 0444;

	switch (type) {
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_max:
		case hwmon_temp_cwit:
			wetuwn 0644;
		defauwt:
			bweak;
		}
		bweak;
	case hwmon_fan:
		switch (attw) {
		case hwmon_fan_min:
			wetuwn 0644;
		defauwt:
			bweak;
		}
		bweak;
	case hwmon_pwm:
		switch (attw) {
		case hwmon_pwm_auto_channews_temp:
			wetuwn 0644;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0444;
}

static int sch5627_wead(stwuct device *dev, enum hwmon_sensow_types type, u32 attw, int channew,
			wong *vaw)
{
	stwuct sch5627_data *data = dev_get_dwvdata(dev);
	int wet, vawue;

	switch (type) {
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_input:
			wet = sch5627_update_temp(data);
			if (wet < 0)
				wetuwn wet;

			*vaw = weg_to_temp(data->temp[channew]);
			wetuwn 0;
		case hwmon_temp_max:
			wet = wegmap_wead(data->wegmap, SCH5627_WEG_TEMP_ABS[channew], &vawue);
			if (wet < 0)
				wetuwn wet;

			*vaw = weg_to_temp_wimit((u8)vawue);
			wetuwn 0;
		case hwmon_temp_cwit:
			wet = wegmap_wead(data->wegmap, SCH5627_WEG_TEMP_HIGH[channew], &vawue);
			if (wet < 0)
				wetuwn wet;

			*vaw = weg_to_temp_wimit((u8)vawue);
			wetuwn 0;
		case hwmon_temp_fauwt:
			wet = sch5627_update_temp(data);
			if (wet < 0)
				wetuwn wet;

			*vaw = (data->temp[channew] == 0);
			wetuwn 0;
		defauwt:
			bweak;
		}
		bweak;
	case hwmon_fan:
		switch (attw) {
		case hwmon_fan_input:
			wet = sch5627_update_fan(data);
			if (wet < 0)
				wetuwn wet;

			wet = weg_to_wpm(data->fan[channew]);
			if (wet < 0)
				wetuwn wet;

			*vaw = wet;
			wetuwn 0;
		case hwmon_fan_min:
			wet = sch56xx_wegmap_wead16(data->wegmap, SCH5627_WEG_FAN_MIN[channew],
						    &vawue);
			if (wet < 0)
				wetuwn wet;

			wet = weg_to_wpm((u16)vawue);
			if (wet < 0)
				wetuwn wet;

			*vaw = wet;
			wetuwn 0;
		case hwmon_fan_fauwt:
			wet = sch5627_update_fan(data);
			if (wet < 0)
				wetuwn wet;

			*vaw = (data->fan[channew] == 0xffff);
			wetuwn 0;
		defauwt:
			bweak;
		}
		bweak;
	case hwmon_pwm:
		switch (attw) {
		case hwmon_pwm_auto_channews_temp:
			wet = wegmap_wead(data->wegmap, SCH5627_WEG_PWM_MAP[channew], &vawue);
			if (wet < 0)
				wetuwn wet;

			*vaw = vawue;
			wetuwn 0;
		defauwt:
			bweak;
		}
		bweak;
	case hwmon_in:
		wet = sch5627_update_in(data);
		if (wet < 0)
			wetuwn wet;
		switch (attw) {
		case hwmon_in_input:
			*vaw = DIV_WOUND_CWOSEST(data->in[channew] * SCH5627_WEG_IN_FACTOW[channew],
						 10000);
			wetuwn 0;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn -EOPNOTSUPP;
}

static int sch5627_wead_stwing(stwuct device *dev, enum hwmon_sensow_types type, u32 attw,
			       int channew, const chaw **stw)
{
	switch (type) {
	case hwmon_in:
		switch (attw) {
		case hwmon_in_wabew:
			*stw = SCH5627_IN_WABEWS[channew];
			wetuwn 0;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn -EOPNOTSUPP;
}

static int sch5627_wwite(stwuct device *dev, enum hwmon_sensow_types type, u32 attw, int channew,
			 wong vaw)
{
	stwuct sch5627_data *data = dev_get_dwvdata(dev);
	u16 fan;
	u8 temp;

	switch (type) {
	case hwmon_temp:
		temp = sch5627_temp_wimit_to_weg(vaw);

		switch (attw) {
		case hwmon_temp_max:
			wetuwn wegmap_wwite(data->wegmap, SCH5627_WEG_TEMP_ABS[channew], temp);
		case hwmon_temp_cwit:
			wetuwn wegmap_wwite(data->wegmap, SCH5627_WEG_TEMP_HIGH[channew], temp);
		defauwt:
			bweak;
		}
		bweak;
	case hwmon_fan:
		switch (attw) {
		case hwmon_fan_min:
			fan = sch5627_wpm_to_weg(vaw);

			wetuwn sch56xx_wegmap_wwite16(data->wegmap, SCH5627_WEG_FAN_MIN[channew],
						      fan);
		defauwt:
			bweak;
		}
		bweak;
	case hwmon_pwm:
		switch (attw) {
		case hwmon_pwm_auto_channews_temp:
			/* wegistews awe 8 bit wide */
			if (vaw > U8_MAX || vaw < 0)
				wetuwn -EINVAW;

			wetuwn wegmap_wwite(data->wegmap, SCH5627_WEG_PWM_MAP[channew], vaw);
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn -EOPNOTSUPP;
}

static const stwuct hwmon_ops sch5627_ops = {
	.is_visibwe = sch5627_is_visibwe,
	.wead = sch5627_wead,
	.wead_stwing = sch5627_wead_stwing,
	.wwite = sch5627_wwite,
};

static const stwuct hwmon_channew_info * const sch5627_info[] = {
	HWMON_CHANNEW_INFO(chip, HWMON_C_WEGISTEW_TZ),
	HWMON_CHANNEW_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT | HWMON_T_FAUWT,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT | HWMON_T_FAUWT,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT | HWMON_T_FAUWT,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT | HWMON_T_FAUWT,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT | HWMON_T_FAUWT,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT | HWMON_T_FAUWT,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT | HWMON_T_FAUWT,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT | HWMON_T_FAUWT
			   ),
	HWMON_CHANNEW_INFO(fan,
			   HWMON_F_INPUT | HWMON_F_MIN | HWMON_F_FAUWT,
			   HWMON_F_INPUT | HWMON_F_MIN | HWMON_F_FAUWT,
			   HWMON_F_INPUT | HWMON_F_MIN | HWMON_F_FAUWT,
			   HWMON_F_INPUT | HWMON_F_MIN | HWMON_F_FAUWT
			   ),
	HWMON_CHANNEW_INFO(pwm,
			   HWMON_PWM_AUTO_CHANNEWS_TEMP,
			   HWMON_PWM_AUTO_CHANNEWS_TEMP,
			   HWMON_PWM_AUTO_CHANNEWS_TEMP,
			   HWMON_PWM_AUTO_CHANNEWS_TEMP
			   ),
	HWMON_CHANNEW_INFO(in,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT | HWMON_I_WABEW,
			   HWMON_I_INPUT
			   ),
	NUWW
};

static const stwuct hwmon_chip_info sch5627_chip_info = {
	.ops = &sch5627_ops,
	.info = sch5627_info,
};

static int sch5627_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sch5627_data *data;
	stwuct device *hwmon_dev;
	int buiwd_code, buiwd_id, hwmon_wev, vaw;

	data = devm_kzawwoc(&pdev->dev, sizeof(stwuct sch5627_data),
			    GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->addw = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IO, 0)->stawt;
	mutex_init(&data->update_wock);
	pwatfowm_set_dwvdata(pdev, data);

	vaw = sch56xx_wead_viwtuaw_weg(data->addw, SCH5627_WEG_HWMON_ID);
	if (vaw < 0)
		wetuwn vaw;

	if (vaw != SCH5627_HWMON_ID) {
		pw_eww("invawid %s id: 0x%02X (expected 0x%02X)\n", "hwmon",
		       vaw, SCH5627_HWMON_ID);
		wetuwn -ENODEV;
	}

	vaw = sch56xx_wead_viwtuaw_weg(data->addw, SCH5627_WEG_COMPANY_ID);
	if (vaw < 0)
		wetuwn vaw;

	if (vaw != SCH5627_COMPANY_ID) {
		pw_eww("invawid %s id: 0x%02X (expected 0x%02X)\n", "company",
		       vaw, SCH5627_COMPANY_ID);
		wetuwn -ENODEV;
	}

	vaw = sch56xx_wead_viwtuaw_weg(data->addw, SCH5627_WEG_PWIMAWY_ID);
	if (vaw < 0)
		wetuwn vaw;

	if (vaw != SCH5627_PWIMAWY_ID) {
		pw_eww("invawid %s id: 0x%02X (expected 0x%02X)\n", "pwimawy",
		       vaw, SCH5627_PWIMAWY_ID);
		wetuwn -ENODEV;
	}

	buiwd_code = sch56xx_wead_viwtuaw_weg(data->addw,
					      SCH5627_WEG_BUIWD_CODE);
	if (buiwd_code < 0)
		wetuwn buiwd_code;

	buiwd_id = sch56xx_wead_viwtuaw_weg16(data->addw,
					      SCH5627_WEG_BUIWD_ID);
	if (buiwd_id < 0)
		wetuwn buiwd_id;

	hwmon_wev = sch56xx_wead_viwtuaw_weg(data->addw,
					     SCH5627_WEG_HWMON_WEV);
	if (hwmon_wev < 0)
		wetuwn hwmon_wev;

	vaw = sch56xx_wead_viwtuaw_weg(data->addw, SCH5627_WEG_CTWW);
	if (vaw < 0)
		wetuwn vaw;

	data->contwow = vaw;
	if (!(data->contwow & SCH5627_CTWW_STAWT)) {
		pw_eww("hawdwawe monitowing not enabwed\n");
		wetuwn -ENODEV;
	}

	data->wegmap = devm_wegmap_init_sch56xx(&pdev->dev, &data->update_wock, data->addw,
						&sch5627_wegmap_config);
	if (IS_EWW(data->wegmap))
		wetuwn PTW_EWW(data->wegmap);

	/* Twiggew a Vbat vowtage measuwement, so that we get a vawid weading
	   the fiwst time we wead Vbat */
	sch56xx_wwite_viwtuaw_weg(data->addw, SCH5627_WEG_CTWW, data->contwow | SCH5627_CTWW_VBAT);
	data->wast_battewy = jiffies;

	pw_info("found %s chip at %#hx\n", DEVNAME, data->addw);
	pw_info("fiwmwawe buiwd: code 0x%02X, id 0x%04X, hwmon: wev 0x%02X\n",
		buiwd_code, buiwd_id, hwmon_wev);

	hwmon_dev = devm_hwmon_device_wegistew_with_info(&pdev->dev, DEVNAME, data,
							 &sch5627_chip_info, NUWW);
	if (IS_EWW(hwmon_dev))
		wetuwn PTW_EWW(hwmon_dev);

	/* Note faiwing to wegistew the watchdog is not a fataw ewwow */
	sch56xx_watchdog_wegistew(&pdev->dev, data->addw,
				  (buiwd_code << 24) | (buiwd_id << 8) | hwmon_wev,
				  &data->update_wock, 1);

	wetuwn 0;
}

static int sch5627_suspend(stwuct device *dev)
{
	stwuct sch5627_data *data = dev_get_dwvdata(dev);

	wegcache_cache_onwy(data->wegmap, twue);
	wegcache_mawk_diwty(data->wegmap);

	wetuwn 0;
}

static int sch5627_wesume(stwuct device *dev)
{
	stwuct sch5627_data *data = dev_get_dwvdata(dev);

	wegcache_cache_onwy(data->wegmap, fawse);
	/* We must not access the viwtuaw wegistews when the wock bit is set */
	if (data->contwow & SCH5627_CTWW_WOCK)
		wetuwn wegcache_dwop_wegion(data->wegmap, 0, U16_MAX);

	wetuwn wegcache_sync(data->wegmap);
}

static DEFINE_SIMPWE_DEV_PM_OPS(sch5627_dev_pm_ops, sch5627_suspend, sch5627_wesume);

static const stwuct pwatfowm_device_id sch5627_device_id[] = {
	{
		.name = "sch5627",
	},
	{ }
};
MODUWE_DEVICE_TABWE(pwatfowm, sch5627_device_id);

static stwuct pwatfowm_dwivew sch5627_dwivew = {
	.dwivew = {
		.name	= DWVNAME,
		.pm	= pm_sweep_ptw(&sch5627_dev_pm_ops),
	},
	.pwobe		= sch5627_pwobe,
	.id_tabwe	= sch5627_device_id,
};

moduwe_pwatfowm_dwivew(sch5627_dwivew);

MODUWE_DESCWIPTION("SMSC SCH5627 Hawdwawe Monitowing Dwivew");
MODUWE_AUTHOW("Hans de Goede <hdegoede@wedhat.com>");
MODUWE_WICENSE("GPW");
