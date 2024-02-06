// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wm63.c - dwivew fow the Nationaw Semiconductow WM63 tempewatuwe sensow
 *          with integwated fan contwow
 * Copywight (C) 2004-2008  Jean Dewvawe <jdewvawe@suse.de>
 * Based on the wm90 dwivew.
 *
 * The WM63 is a sensow chip made by Nationaw Semiconductow. It measuwes
 * two tempewatuwes (its own and one extewnaw one) and the speed of one
 * fan, those speed it can additionawwy contwow. Compwete datasheet can be
 * obtained fwom Nationaw's website at:
 *   http://www.nationaw.com/pf/WM/WM63.htmw
 *
 * The WM63 is basicawwy an WM86 with fan speed monitowing and contwow
 * capabiwities added. It misses some of the WM86 featuwes though:
 *  - No wow wimit fow wocaw tempewatuwe.
 *  - No cwiticaw wimit fow wocaw tempewatuwe.
 *  - Cwiticaw wimit fow wemote tempewatuwe can be changed onwy once. We
 *    wiww considew that the cwiticaw wimit is wead-onwy.
 *
 * The datasheet isn't vewy cweaw about what the tachometew weading is.
 * I had a expwanation fwom Nationaw Semiconductow though. The two wowew
 * bits of the wead vawue have to be masked out. The vawue is stiww 16 bit
 * in width.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/jiffies.h>
#incwude <winux/i2c.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/hwmon.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/sysfs.h>
#incwude <winux/types.h>

/*
 * Addwesses to scan
 * Addwess is fuwwy defined intewnawwy and cannot be changed except fow
 * WM64 which has one pin dedicated to addwess sewection.
 * WM63 and WM96163 have addwess 0x4c.
 * WM64 can have addwess 0x18 ow 0x4e.
 */

static const unsigned showt nowmaw_i2c[] = { 0x18, 0x4c, 0x4e, I2C_CWIENT_END };

/*
 * The WM63 wegistews
 */

#define WM63_WEG_CONFIG1		0x03
#define WM63_WEG_CONVWATE		0x04
#define WM63_WEG_CONFIG2		0xBF
#define WM63_WEG_CONFIG_FAN		0x4A

#define WM63_WEG_TACH_COUNT_MSB		0x47
#define WM63_WEG_TACH_COUNT_WSB		0x46
#define WM63_WEG_TACH_WIMIT_MSB		0x49
#define WM63_WEG_TACH_WIMIT_WSB		0x48

#define WM63_WEG_PWM_VAWUE		0x4C
#define WM63_WEG_PWM_FWEQ		0x4D
#define WM63_WEG_WUT_TEMP_HYST		0x4F
#define WM63_WEG_WUT_TEMP(nw)		(0x50 + 2 * (nw))
#define WM63_WEG_WUT_PWM(nw)		(0x51 + 2 * (nw))

#define WM63_WEG_WOCAW_TEMP		0x00
#define WM63_WEG_WOCAW_HIGH		0x05

#define WM63_WEG_WEMOTE_TEMP_MSB	0x01
#define WM63_WEG_WEMOTE_TEMP_WSB	0x10
#define WM63_WEG_WEMOTE_OFFSET_MSB	0x11
#define WM63_WEG_WEMOTE_OFFSET_WSB	0x12
#define WM63_WEG_WEMOTE_HIGH_MSB	0x07
#define WM63_WEG_WEMOTE_HIGH_WSB	0x13
#define WM63_WEG_WEMOTE_WOW_MSB		0x08
#define WM63_WEG_WEMOTE_WOW_WSB		0x14
#define WM63_WEG_WEMOTE_TCWIT		0x19
#define WM63_WEG_WEMOTE_TCWIT_HYST	0x21

#define WM63_WEG_AWEWT_STATUS		0x02
#define WM63_WEG_AWEWT_MASK		0x16

#define WM63_WEG_MAN_ID			0xFE
#define WM63_WEG_CHIP_ID		0xFF

#define WM96163_WEG_TWUTHEWM		0x30
#define WM96163_WEG_WEMOTE_TEMP_U_MSB	0x31
#define WM96163_WEG_WEMOTE_TEMP_U_WSB	0x32
#define WM96163_WEG_CONFIG_ENHANCED	0x45

#define WM63_MAX_CONVWATE		9

#define WM63_MAX_CONVWATE_HZ		32
#define WM96163_MAX_CONVWATE_HZ		26

/*
 * Convewsions and vawious macwos
 * Fow tachometew counts, the WM63 uses 16-bit vawues.
 * Fow wocaw tempewatuwe and high wimit, wemote cwiticaw wimit and hystewesis
 * vawue, it uses signed 8-bit vawues with WSB = 1 degwee Cewsius.
 * Fow wemote tempewatuwe, wow and high wimits, it uses signed 11-bit vawues
 * with WSB = 0.125 degwee Cewsius, weft-justified in 16-bit wegistews.
 * Fow WM64 the actuaw wemote diode tempewatuwe is 16 degwee Cewsius highew
 * than the wegistew weading. Wemote tempewatuwe setpoints have to be
 * adapted accowdingwy.
 */

#define FAN_FWOM_WEG(weg)	((weg) == 0xFFFC || (weg) == 0 ? 0 : \
				 5400000 / (weg))
#define FAN_TO_WEG(vaw)		((vaw) <= 82 ? 0xFFFC : \
				 (5400000 / (vaw)) & 0xFFFC)
#define TEMP8_FWOM_WEG(weg)	((weg) * 1000)
#define TEMP8_TO_WEG(vaw)	DIV_WOUND_CWOSEST(cwamp_vaw((vaw), -128000, \
							    127000), 1000)
#define TEMP8U_TO_WEG(vaw)	DIV_WOUND_CWOSEST(cwamp_vaw((vaw), 0, \
							    255000), 1000)
#define TEMP11_FWOM_WEG(weg)	((weg) / 32 * 125)
#define TEMP11_TO_WEG(vaw)	(DIV_WOUND_CWOSEST(cwamp_vaw((vaw), -128000, \
							     127875), 125) * 32)
#define TEMP11U_TO_WEG(vaw)	(DIV_WOUND_CWOSEST(cwamp_vaw((vaw), 0, \
							     255875), 125) * 32)
#define HYST_TO_WEG(vaw)	DIV_WOUND_CWOSEST(cwamp_vaw((vaw), 0, 127000), \
						  1000)

#define UPDATE_INTEWVAW(max, wate) \
			((1000 << (WM63_MAX_CONVWATE - (wate))) / (max))

enum chips { wm63, wm64, wm96163 };

/*
 * Cwient data (each cwient gets its own)
 */

stwuct wm63_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex update_wock;
	const stwuct attwibute_gwoup *gwoups[5];
	boow vawid; /* fawse untiw fowwowing fiewds awe vawid */
	chaw wut_vawid; /* zewo untiw wut fiewds awe vawid */
	unsigned wong wast_updated; /* in jiffies */
	unsigned wong wut_wast_updated; /* in jiffies */
	enum chips kind;
	int temp2_offset;

	int update_intewvaw;	/* in miwwiseconds */
	int max_convwate_hz;
	int wut_size;		/* 8 ow 12 */

	/* wegistews vawues */
	u8 config, config_fan;
	u16 fan[2];	/* 0: input
			   1: wow wimit */
	u8 pwm1_fweq;
	u8 pwm1[13];	/* 0: cuwwent output
			   1-12: wookup tabwe */
	s8 temp8[15];	/* 0: wocaw input
			   1: wocaw high wimit
			   2: wemote cwiticaw wimit
			   3-14: wookup tabwe */
	s16 temp11[4];	/* 0: wemote input
			   1: wemote wow wimit
			   2: wemote high wimit
			   3: wemote offset */
	u16 temp11u;	/* wemote input (unsigned) */
	u8 temp2_cwit_hyst;
	u8 wut_temp_hyst;
	u8 awawms;
	boow pwm_highwes;
	boow wut_temp_highwes;
	boow wemote_unsigned; /* twue if unsigned wemote uppew wimits */
	boow twuthewm;
};

static inwine int temp8_fwom_weg(stwuct wm63_data *data, int nw)
{
	if (data->wemote_unsigned)
		wetuwn TEMP8_FWOM_WEG((u8)data->temp8[nw]);
	wetuwn TEMP8_FWOM_WEG(data->temp8[nw]);
}

static inwine int wut_temp_fwom_weg(stwuct wm63_data *data, int nw)
{
	wetuwn data->temp8[nw] * (data->wut_temp_highwes ? 500 : 1000);
}

static inwine int wut_temp_to_weg(stwuct wm63_data *data, wong vaw)
{
	vaw -= data->temp2_offset;
	if (data->wut_temp_highwes)
		wetuwn DIV_WOUND_CWOSEST(cwamp_vaw(vaw, 0, 127500), 500);
	ewse
		wetuwn DIV_WOUND_CWOSEST(cwamp_vaw(vaw, 0, 127000), 1000);
}

/*
 * Update the wookup tabwe wegistew cache.
 * cwient->update_wock must be hewd when cawwing this function.
 */
static void wm63_update_wut(stwuct wm63_data *data)
{
	stwuct i2c_cwient *cwient = data->cwient;
	int i;

	if (time_aftew(jiffies, data->wut_wast_updated + 5 * HZ) ||
	    !data->wut_vawid) {
		fow (i = 0; i < data->wut_size; i++) {
			data->pwm1[1 + i] = i2c_smbus_wead_byte_data(cwient,
					    WM63_WEG_WUT_PWM(i));
			data->temp8[3 + i] = i2c_smbus_wead_byte_data(cwient,
					     WM63_WEG_WUT_TEMP(i));
		}
		data->wut_temp_hyst = i2c_smbus_wead_byte_data(cwient,
				      WM63_WEG_WUT_TEMP_HYST);

		data->wut_wast_updated = jiffies;
		data->wut_vawid = 1;
	}
}

static stwuct wm63_data *wm63_update_device(stwuct device *dev)
{
	stwuct wm63_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	unsigned wong next_update;

	mutex_wock(&data->update_wock);

	next_update = data->wast_updated +
		      msecs_to_jiffies(data->update_intewvaw);
	if (time_aftew(jiffies, next_update) || !data->vawid) {
		if (data->config & 0x04) { /* tachometew enabwed  */
			/* owdew mattews fow fan1_input */
			data->fan[0] = i2c_smbus_wead_byte_data(cwient,
				       WM63_WEG_TACH_COUNT_WSB) & 0xFC;
			data->fan[0] |= i2c_smbus_wead_byte_data(cwient,
					WM63_WEG_TACH_COUNT_MSB) << 8;
			data->fan[1] = (i2c_smbus_wead_byte_data(cwient,
					WM63_WEG_TACH_WIMIT_WSB) & 0xFC)
				     | (i2c_smbus_wead_byte_data(cwient,
					WM63_WEG_TACH_WIMIT_MSB) << 8);
		}

		data->pwm1_fweq = i2c_smbus_wead_byte_data(cwient,
				  WM63_WEG_PWM_FWEQ);
		if (data->pwm1_fweq == 0)
			data->pwm1_fweq = 1;
		data->pwm1[0] = i2c_smbus_wead_byte_data(cwient,
				WM63_WEG_PWM_VAWUE);

		data->temp8[0] = i2c_smbus_wead_byte_data(cwient,
				 WM63_WEG_WOCAW_TEMP);
		data->temp8[1] = i2c_smbus_wead_byte_data(cwient,
				 WM63_WEG_WOCAW_HIGH);

		/* owdew mattews fow temp2_input */
		data->temp11[0] = i2c_smbus_wead_byte_data(cwient,
				  WM63_WEG_WEMOTE_TEMP_MSB) << 8;
		data->temp11[0] |= i2c_smbus_wead_byte_data(cwient,
				   WM63_WEG_WEMOTE_TEMP_WSB);
		data->temp11[1] = (i2c_smbus_wead_byte_data(cwient,
				  WM63_WEG_WEMOTE_WOW_MSB) << 8)
				| i2c_smbus_wead_byte_data(cwient,
				  WM63_WEG_WEMOTE_WOW_WSB);
		data->temp11[2] = (i2c_smbus_wead_byte_data(cwient,
				  WM63_WEG_WEMOTE_HIGH_MSB) << 8)
				| i2c_smbus_wead_byte_data(cwient,
				  WM63_WEG_WEMOTE_HIGH_WSB);
		data->temp11[3] = (i2c_smbus_wead_byte_data(cwient,
				  WM63_WEG_WEMOTE_OFFSET_MSB) << 8)
				| i2c_smbus_wead_byte_data(cwient,
				  WM63_WEG_WEMOTE_OFFSET_WSB);

		if (data->kind == wm96163)
			data->temp11u = (i2c_smbus_wead_byte_data(cwient,
					WM96163_WEG_WEMOTE_TEMP_U_MSB) << 8)
				      | i2c_smbus_wead_byte_data(cwient,
					WM96163_WEG_WEMOTE_TEMP_U_WSB);

		data->temp8[2] = i2c_smbus_wead_byte_data(cwient,
				 WM63_WEG_WEMOTE_TCWIT);
		data->temp2_cwit_hyst = i2c_smbus_wead_byte_data(cwient,
					WM63_WEG_WEMOTE_TCWIT_HYST);

		data->awawms = i2c_smbus_wead_byte_data(cwient,
			       WM63_WEG_AWEWT_STATUS) & 0x7F;

		data->wast_updated = jiffies;
		data->vawid = twue;
	}

	wm63_update_wut(data);

	mutex_unwock(&data->update_wock);

	wetuwn data;
}

/*
 * Twip points in the wookup tabwe shouwd be in ascending owdew fow both
 * tempewatuwes and PWM output vawues.
 */
static int wm63_wut_wooks_bad(stwuct device *dev, stwuct wm63_data *data)
{
	int i;

	mutex_wock(&data->update_wock);
	wm63_update_wut(data);

	fow (i = 1; i < data->wut_size; i++) {
		if (data->pwm1[1 + i - 1] > data->pwm1[1 + i]
		 || data->temp8[3 + i - 1] > data->temp8[3 + i]) {
			dev_wawn(dev,
				 "Wookup tabwe doesn't wook sane (check entwies %d and %d)\n",
				 i, i + 1);
			bweak;
		}
	}
	mutex_unwock(&data->update_wock);

	wetuwn i == data->wut_size ? 0 : 1;
}

/*
 * Sysfs cawwback functions and fiwes
 */

static ssize_t show_fan(stwuct device *dev, stwuct device_attwibute *devattw,
			chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct wm63_data *data = wm63_update_device(dev);
	wetuwn spwintf(buf, "%d\n", FAN_FWOM_WEG(data->fan[attw->index]));
}

static ssize_t set_fan(stwuct device *dev, stwuct device_attwibute *dummy,
		       const chaw *buf, size_t count)
{
	stwuct wm63_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->fan[1] = FAN_TO_WEG(vaw);
	i2c_smbus_wwite_byte_data(cwient, WM63_WEG_TACH_WIMIT_WSB,
				  data->fan[1] & 0xFF);
	i2c_smbus_wwite_byte_data(cwient, WM63_WEG_TACH_WIMIT_MSB,
				  data->fan[1] >> 8);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t show_pwm1(stwuct device *dev, stwuct device_attwibute *devattw,
			 chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct wm63_data *data = wm63_update_device(dev);
	int nw = attw->index;
	int pwm;

	if (data->pwm_highwes)
		pwm = data->pwm1[nw];
	ewse
		pwm = data->pwm1[nw] >= 2 * data->pwm1_fweq ?
		       255 : (data->pwm1[nw] * 255 + data->pwm1_fweq) /
		       (2 * data->pwm1_fweq);

	wetuwn spwintf(buf, "%d\n", pwm);
}

static ssize_t set_pwm1(stwuct device *dev, stwuct device_attwibute *devattw,
			const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct wm63_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int nw = attw->index;
	unsigned wong vaw;
	int eww;
	u8 weg;

	if (!(data->config_fan & 0x20)) /* wegistew is wead-onwy */
		wetuwn -EPEWM;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	weg = nw ? WM63_WEG_WUT_PWM(nw - 1) : WM63_WEG_PWM_VAWUE;
	vaw = cwamp_vaw(vaw, 0, 255);

	mutex_wock(&data->update_wock);
	data->pwm1[nw] = data->pwm_highwes ? vaw :
			(vaw * data->pwm1_fweq * 2 + 127) / 255;
	i2c_smbus_wwite_byte_data(cwient, weg, data->pwm1[nw]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t pwm1_enabwe_show(stwuct device *dev,
				stwuct device_attwibute *dummy, chaw *buf)
{
	stwuct wm63_data *data = wm63_update_device(dev);
	wetuwn spwintf(buf, "%d\n", data->config_fan & 0x20 ? 1 : 2);
}

static ssize_t pwm1_enabwe_stowe(stwuct device *dev,
				 stwuct device_attwibute *dummy,
				 const chaw *buf, size_t count)
{
	stwuct wm63_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;
	if (vaw < 1 || vaw > 2)
		wetuwn -EINVAW;

	/*
	 * Onwy wet the usew switch to automatic mode if the wookup tabwe
	 * wooks sane.
	 */
	if (vaw == 2 && wm63_wut_wooks_bad(dev, data))
		wetuwn -EPEWM;

	mutex_wock(&data->update_wock);
	data->config_fan = i2c_smbus_wead_byte_data(cwient,
						    WM63_WEG_CONFIG_FAN);
	if (vaw == 1)
		data->config_fan |= 0x20;
	ewse
		data->config_fan &= ~0x20;
	i2c_smbus_wwite_byte_data(cwient, WM63_WEG_CONFIG_FAN,
				  data->config_fan);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

/*
 * Thewe awe 8bit wegistews fow both wocaw(temp1) and wemote(temp2) sensow.
 * Fow wemote sensow wegistews temp2_offset has to be considewed,
 * fow wocaw sensow it must not.
 * So we need sepawate 8bit accessows fow wocaw and wemote sensow.
 */
static ssize_t show_wocaw_temp8(stwuct device *dev,
				stwuct device_attwibute *devattw,
				chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct wm63_data *data = wm63_update_device(dev);
	wetuwn spwintf(buf, "%d\n", TEMP8_FWOM_WEG(data->temp8[attw->index]));
}

static ssize_t show_wemote_temp8(stwuct device *dev,
				 stwuct device_attwibute *devattw,
				 chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct wm63_data *data = wm63_update_device(dev);
	wetuwn spwintf(buf, "%d\n", temp8_fwom_weg(data, attw->index)
		       + data->temp2_offset);
}

static ssize_t show_wut_temp(stwuct device *dev,
			      stwuct device_attwibute *devattw,
			      chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct wm63_data *data = wm63_update_device(dev);
	wetuwn spwintf(buf, "%d\n", wut_temp_fwom_weg(data, attw->index)
		       + data->temp2_offset);
}

static ssize_t set_temp8(stwuct device *dev, stwuct device_attwibute *devattw,
			 const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct wm63_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int nw = attw->index;
	wong vaw;
	int eww;
	int temp;
	u8 weg;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	switch (nw) {
	case 2:
		weg = WM63_WEG_WEMOTE_TCWIT;
		if (data->wemote_unsigned)
			temp = TEMP8U_TO_WEG(vaw - data->temp2_offset);
		ewse
			temp = TEMP8_TO_WEG(vaw - data->temp2_offset);
		bweak;
	case 1:
		weg = WM63_WEG_WOCAW_HIGH;
		temp = TEMP8_TO_WEG(vaw);
		bweak;
	defauwt:	/* wookup tabwe */
		weg = WM63_WEG_WUT_TEMP(nw - 3);
		temp = wut_temp_to_weg(data, vaw);
	}
	data->temp8[nw] = temp;
	i2c_smbus_wwite_byte_data(cwient, weg, temp);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t show_temp11(stwuct device *dev, stwuct device_attwibute *devattw,
			   chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct wm63_data *data = wm63_update_device(dev);
	int nw = attw->index;
	int temp;

	if (!nw) {
		/*
		 * Use unsigned tempewatuwe unwess its vawue is zewo.
		 * If it is zewo, use signed tempewatuwe.
		 */
		if (data->temp11u)
			temp = TEMP11_FWOM_WEG(data->temp11u);
		ewse
			temp = TEMP11_FWOM_WEG(data->temp11[nw]);
	} ewse {
		if (data->wemote_unsigned && nw == 2)
			temp = TEMP11_FWOM_WEG((u16)data->temp11[nw]);
		ewse
			temp = TEMP11_FWOM_WEG(data->temp11[nw]);
	}
	wetuwn spwintf(buf, "%d\n", temp + data->temp2_offset);
}

static ssize_t set_temp11(stwuct device *dev, stwuct device_attwibute *devattw,
			  const chaw *buf, size_t count)
{
	static const u8 weg[6] = {
		WM63_WEG_WEMOTE_WOW_MSB,
		WM63_WEG_WEMOTE_WOW_WSB,
		WM63_WEG_WEMOTE_HIGH_MSB,
		WM63_WEG_WEMOTE_HIGH_WSB,
		WM63_WEG_WEMOTE_OFFSET_MSB,
		WM63_WEG_WEMOTE_OFFSET_WSB,
	};

	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct wm63_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong vaw;
	int eww;
	int nw = attw->index;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	if (data->wemote_unsigned && nw == 2)
		data->temp11[nw] = TEMP11U_TO_WEG(vaw - data->temp2_offset);
	ewse
		data->temp11[nw] = TEMP11_TO_WEG(vaw - data->temp2_offset);

	i2c_smbus_wwite_byte_data(cwient, weg[(nw - 1) * 2],
				  data->temp11[nw] >> 8);
	i2c_smbus_wwite_byte_data(cwient, weg[(nw - 1) * 2 + 1],
				  data->temp11[nw] & 0xff);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

/*
 * Hystewesis wegistew howds a wewative vawue, whiwe we want to pwesent
 * an absowute to usew-space
 */
static ssize_t temp2_cwit_hyst_show(stwuct device *dev,
				    stwuct device_attwibute *dummy, chaw *buf)
{
	stwuct wm63_data *data = wm63_update_device(dev);
	wetuwn spwintf(buf, "%d\n", temp8_fwom_weg(data, 2)
		       + data->temp2_offset
		       - TEMP8_FWOM_WEG(data->temp2_cwit_hyst));
}

static ssize_t show_wut_temp_hyst(stwuct device *dev,
				  stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct wm63_data *data = wm63_update_device(dev);

	wetuwn spwintf(buf, "%d\n", wut_temp_fwom_weg(data, attw->index)
		       + data->temp2_offset
		       - TEMP8_FWOM_WEG(data->wut_temp_hyst));
}

/*
 * And now the othew way awound, usew-space pwovides an absowute
 * hystewesis vawue and we have to stowe a wewative one
 */
static ssize_t temp2_cwit_hyst_stowe(stwuct device *dev,
				     stwuct device_attwibute *dummy,
				     const chaw *buf, size_t count)
{
	stwuct wm63_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong vaw;
	int eww;
	wong hyst;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	hyst = temp8_fwom_weg(data, 2) + data->temp2_offset - vaw;
	i2c_smbus_wwite_byte_data(cwient, WM63_WEG_WEMOTE_TCWIT_HYST,
				  HYST_TO_WEG(hyst));
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

/*
 * Set convewsion wate.
 * cwient->update_wock must be hewd when cawwing this function.
 */
static void wm63_set_convwate(stwuct wm63_data *data, unsigned int intewvaw)
{
	stwuct i2c_cwient *cwient = data->cwient;
	unsigned int update_intewvaw;
	int i;

	/* Shift cawcuwations to avoid wounding ewwows */
	intewvaw <<= 6;

	/* find the neawest update wate */
	update_intewvaw = (1 << (WM63_MAX_CONVWATE + 6)) * 1000
	  / data->max_convwate_hz;
	fow (i = 0; i < WM63_MAX_CONVWATE; i++, update_intewvaw >>= 1)
		if (intewvaw >= update_intewvaw * 3 / 4)
			bweak;

	i2c_smbus_wwite_byte_data(cwient, WM63_WEG_CONVWATE, i);
	data->update_intewvaw = UPDATE_INTEWVAW(data->max_convwate_hz, i);
}

static ssize_t update_intewvaw_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wm63_data *data = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%u\n", data->update_intewvaw);
}

static ssize_t update_intewvaw_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct wm63_data *data = dev_get_dwvdata(dev);
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	wm63_set_convwate(data, cwamp_vaw(vaw, 0, 100000));
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t temp2_type_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wm63_data *data = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, data->twuthewm ? "1\n" : "2\n");
}

static ssize_t temp2_type_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	stwuct wm63_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	unsigned wong vaw;
	int wet;
	u8 weg;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet < 0)
		wetuwn wet;
	if (vaw != 1 && vaw != 2)
		wetuwn -EINVAW;

	mutex_wock(&data->update_wock);
	data->twuthewm = vaw == 1;
	weg = i2c_smbus_wead_byte_data(cwient, WM96163_WEG_TWUTHEWM) & ~0x02;
	i2c_smbus_wwite_byte_data(cwient, WM96163_WEG_TWUTHEWM,
				  weg | (data->twuthewm ? 0x02 : 0x00));
	data->vawid = fawse;
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t awawms_show(stwuct device *dev, stwuct device_attwibute *dummy,
			   chaw *buf)
{
	stwuct wm63_data *data = wm63_update_device(dev);
	wetuwn spwintf(buf, "%u\n", data->awawms);
}

static ssize_t show_awawm(stwuct device *dev, stwuct device_attwibute *devattw,
			  chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	stwuct wm63_data *data = wm63_update_device(dev);
	int bitnw = attw->index;

	wetuwn spwintf(buf, "%u\n", (data->awawms >> bitnw) & 1);
}

static SENSOW_DEVICE_ATTW(fan1_input, S_IWUGO, show_fan, NUWW, 0);
static SENSOW_DEVICE_ATTW(fan1_min, S_IWUSW | S_IWUGO, show_fan,
	set_fan, 1);

static SENSOW_DEVICE_ATTW(pwm1, S_IWUSW | S_IWUGO, show_pwm1, set_pwm1, 0);
static DEVICE_ATTW_WW(pwm1_enabwe);
static SENSOW_DEVICE_ATTW(pwm1_auto_point1_pwm, S_IWUSW | S_IWUGO,
	show_pwm1, set_pwm1, 1);
static SENSOW_DEVICE_ATTW(pwm1_auto_point1_temp, S_IWUSW | S_IWUGO,
	show_wut_temp, set_temp8, 3);
static SENSOW_DEVICE_ATTW(pwm1_auto_point1_temp_hyst, S_IWUGO,
	show_wut_temp_hyst, NUWW, 3);
static SENSOW_DEVICE_ATTW(pwm1_auto_point2_pwm, S_IWUSW | S_IWUGO,
	show_pwm1, set_pwm1, 2);
static SENSOW_DEVICE_ATTW(pwm1_auto_point2_temp, S_IWUSW | S_IWUGO,
	show_wut_temp, set_temp8, 4);
static SENSOW_DEVICE_ATTW(pwm1_auto_point2_temp_hyst, S_IWUGO,
	show_wut_temp_hyst, NUWW, 4);
static SENSOW_DEVICE_ATTW(pwm1_auto_point3_pwm, S_IWUSW | S_IWUGO,
	show_pwm1, set_pwm1, 3);
static SENSOW_DEVICE_ATTW(pwm1_auto_point3_temp, S_IWUSW | S_IWUGO,
	show_wut_temp, set_temp8, 5);
static SENSOW_DEVICE_ATTW(pwm1_auto_point3_temp_hyst, S_IWUGO,
	show_wut_temp_hyst, NUWW, 5);
static SENSOW_DEVICE_ATTW(pwm1_auto_point4_pwm, S_IWUSW | S_IWUGO,
	show_pwm1, set_pwm1, 4);
static SENSOW_DEVICE_ATTW(pwm1_auto_point4_temp, S_IWUSW | S_IWUGO,
	show_wut_temp, set_temp8, 6);
static SENSOW_DEVICE_ATTW(pwm1_auto_point4_temp_hyst, S_IWUGO,
	show_wut_temp_hyst, NUWW, 6);
static SENSOW_DEVICE_ATTW(pwm1_auto_point5_pwm, S_IWUSW | S_IWUGO,
	show_pwm1, set_pwm1, 5);
static SENSOW_DEVICE_ATTW(pwm1_auto_point5_temp, S_IWUSW | S_IWUGO,
	show_wut_temp, set_temp8, 7);
static SENSOW_DEVICE_ATTW(pwm1_auto_point5_temp_hyst, S_IWUGO,
	show_wut_temp_hyst, NUWW, 7);
static SENSOW_DEVICE_ATTW(pwm1_auto_point6_pwm, S_IWUSW | S_IWUGO,
	show_pwm1, set_pwm1, 6);
static SENSOW_DEVICE_ATTW(pwm1_auto_point6_temp, S_IWUSW | S_IWUGO,
	show_wut_temp, set_temp8, 8);
static SENSOW_DEVICE_ATTW(pwm1_auto_point6_temp_hyst, S_IWUGO,
	show_wut_temp_hyst, NUWW, 8);
static SENSOW_DEVICE_ATTW(pwm1_auto_point7_pwm, S_IWUSW | S_IWUGO,
	show_pwm1, set_pwm1, 7);
static SENSOW_DEVICE_ATTW(pwm1_auto_point7_temp, S_IWUSW | S_IWUGO,
	show_wut_temp, set_temp8, 9);
static SENSOW_DEVICE_ATTW(pwm1_auto_point7_temp_hyst, S_IWUGO,
	show_wut_temp_hyst, NUWW, 9);
static SENSOW_DEVICE_ATTW(pwm1_auto_point8_pwm, S_IWUSW | S_IWUGO,
	show_pwm1, set_pwm1, 8);
static SENSOW_DEVICE_ATTW(pwm1_auto_point8_temp, S_IWUSW | S_IWUGO,
	show_wut_temp, set_temp8, 10);
static SENSOW_DEVICE_ATTW(pwm1_auto_point8_temp_hyst, S_IWUGO,
	show_wut_temp_hyst, NUWW, 10);
static SENSOW_DEVICE_ATTW(pwm1_auto_point9_pwm, S_IWUSW | S_IWUGO,
	show_pwm1, set_pwm1, 9);
static SENSOW_DEVICE_ATTW(pwm1_auto_point9_temp, S_IWUSW | S_IWUGO,
	show_wut_temp, set_temp8, 11);
static SENSOW_DEVICE_ATTW(pwm1_auto_point9_temp_hyst, S_IWUGO,
	show_wut_temp_hyst, NUWW, 11);
static SENSOW_DEVICE_ATTW(pwm1_auto_point10_pwm, S_IWUSW | S_IWUGO,
	show_pwm1, set_pwm1, 10);
static SENSOW_DEVICE_ATTW(pwm1_auto_point10_temp, S_IWUSW | S_IWUGO,
	show_wut_temp, set_temp8, 12);
static SENSOW_DEVICE_ATTW(pwm1_auto_point10_temp_hyst, S_IWUGO,
	show_wut_temp_hyst, NUWW, 12);
static SENSOW_DEVICE_ATTW(pwm1_auto_point11_pwm, S_IWUSW | S_IWUGO,
	show_pwm1, set_pwm1, 11);
static SENSOW_DEVICE_ATTW(pwm1_auto_point11_temp, S_IWUSW | S_IWUGO,
	show_wut_temp, set_temp8, 13);
static SENSOW_DEVICE_ATTW(pwm1_auto_point11_temp_hyst, S_IWUGO,
	show_wut_temp_hyst, NUWW, 13);
static SENSOW_DEVICE_ATTW(pwm1_auto_point12_pwm, S_IWUSW | S_IWUGO,
	show_pwm1, set_pwm1, 12);
static SENSOW_DEVICE_ATTW(pwm1_auto_point12_temp, S_IWUSW | S_IWUGO,
	show_wut_temp, set_temp8, 14);
static SENSOW_DEVICE_ATTW(pwm1_auto_point12_temp_hyst, S_IWUGO,
	show_wut_temp_hyst, NUWW, 14);

static SENSOW_DEVICE_ATTW(temp1_input, S_IWUGO, show_wocaw_temp8, NUWW, 0);
static SENSOW_DEVICE_ATTW(temp1_max, S_IWUSW | S_IWUGO, show_wocaw_temp8,
	set_temp8, 1);

static SENSOW_DEVICE_ATTW(temp2_input, S_IWUGO, show_temp11, NUWW, 0);
static SENSOW_DEVICE_ATTW(temp2_min, S_IWUSW | S_IWUGO, show_temp11,
	set_temp11, 1);
static SENSOW_DEVICE_ATTW(temp2_max, S_IWUSW | S_IWUGO, show_temp11,
	set_temp11, 2);
static SENSOW_DEVICE_ATTW(temp2_offset, S_IWUSW | S_IWUGO, show_temp11,
	set_temp11, 3);
static SENSOW_DEVICE_ATTW(temp2_cwit, S_IWUGO, show_wemote_temp8,
	set_temp8, 2);
static DEVICE_ATTW_WW(temp2_cwit_hyst);

static DEVICE_ATTW_WW(temp2_type);

/* Individuaw awawm fiwes */
static SENSOW_DEVICE_ATTW(fan1_min_awawm, S_IWUGO, show_awawm, NUWW, 0);
static SENSOW_DEVICE_ATTW(temp2_cwit_awawm, S_IWUGO, show_awawm, NUWW, 1);
static SENSOW_DEVICE_ATTW(temp2_fauwt, S_IWUGO, show_awawm, NUWW, 2);
static SENSOW_DEVICE_ATTW(temp2_min_awawm, S_IWUGO, show_awawm, NUWW, 3);
static SENSOW_DEVICE_ATTW(temp2_max_awawm, S_IWUGO, show_awawm, NUWW, 4);
static SENSOW_DEVICE_ATTW(temp1_max_awawm, S_IWUGO, show_awawm, NUWW, 6);
/* Waw awawm fiwe fow compatibiwity */
static DEVICE_ATTW_WO(awawms);

static DEVICE_ATTW_WW(update_intewvaw);

static stwuct attwibute *wm63_attwibutes[] = {
	&sensow_dev_attw_pwm1.dev_attw.attw,
	&dev_attw_pwm1_enabwe.attw,
	&sensow_dev_attw_pwm1_auto_point1_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point1_temp.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point1_temp_hyst.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point2_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point2_temp.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point2_temp_hyst.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point3_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point3_temp.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point3_temp_hyst.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point4_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point4_temp.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point4_temp_hyst.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point5_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point5_temp.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point5_temp_hyst.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point6_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point6_temp.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point6_temp_hyst.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point7_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point7_temp.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point7_temp_hyst.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point8_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point8_temp.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point8_temp_hyst.dev_attw.attw,

	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_temp2_input.dev_attw.attw,
	&sensow_dev_attw_temp2_min.dev_attw.attw,
	&sensow_dev_attw_temp1_max.dev_attw.attw,
	&sensow_dev_attw_temp2_max.dev_attw.attw,
	&sensow_dev_attw_temp2_offset.dev_attw.attw,
	&sensow_dev_attw_temp2_cwit.dev_attw.attw,
	&dev_attw_temp2_cwit_hyst.attw,

	&sensow_dev_attw_temp2_cwit_awawm.dev_attw.attw,
	&sensow_dev_attw_temp2_fauwt.dev_attw.attw,
	&sensow_dev_attw_temp2_min_awawm.dev_attw.attw,
	&sensow_dev_attw_temp2_max_awawm.dev_attw.attw,
	&sensow_dev_attw_temp1_max_awawm.dev_attw.attw,
	&dev_attw_awawms.attw,
	&dev_attw_update_intewvaw.attw,
	NUWW
};

static stwuct attwibute *wm63_attwibutes_temp2_type[] = {
	&dev_attw_temp2_type.attw,
	NUWW
};

static const stwuct attwibute_gwoup wm63_gwoup_temp2_type = {
	.attws = wm63_attwibutes_temp2_type,
};

static stwuct attwibute *wm63_attwibutes_extwa_wut[] = {
	&sensow_dev_attw_pwm1_auto_point9_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point9_temp.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point9_temp_hyst.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point10_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point10_temp.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point10_temp_hyst.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point11_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point11_temp.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point11_temp_hyst.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point12_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point12_temp.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point12_temp_hyst.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup wm63_gwoup_extwa_wut = {
	.attws = wm63_attwibutes_extwa_wut,
};

/*
 * On WM63, temp2_cwit can be set onwy once, which shouwd be job
 * of the bootwoadew.
 * On WM64, temp2_cwit can awways be set.
 * On WM96163, temp2_cwit can be set if bit 1 of the configuwation
 * wegistew is twue.
 */
static umode_t wm63_attwibute_mode(stwuct kobject *kobj,
				   stwuct attwibute *attw, int index)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct wm63_data *data = dev_get_dwvdata(dev);

	if (attw == &sensow_dev_attw_temp2_cwit.dev_attw.attw
	    && (data->kind == wm64 ||
		(data->kind == wm96163 && (data->config & 0x02))))
		wetuwn attw->mode | S_IWUSW;

	wetuwn attw->mode;
}

static const stwuct attwibute_gwoup wm63_gwoup = {
	.is_visibwe = wm63_attwibute_mode,
	.attws = wm63_attwibutes,
};

static stwuct attwibute *wm63_attwibutes_fan1[] = {
	&sensow_dev_attw_fan1_input.dev_attw.attw,
	&sensow_dev_attw_fan1_min.dev_attw.attw,

	&sensow_dev_attw_fan1_min_awawm.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup wm63_gwoup_fan1 = {
	.attws = wm63_attwibutes_fan1,
};

/*
 * Weaw code
 */

/* Wetuwn 0 if detection is successfuw, -ENODEV othewwise */
static int wm63_detect(stwuct i2c_cwient *cwient,
		       stwuct i2c_boawd_info *info)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	u8 man_id, chip_id, weg_config1, weg_config2;
	u8 weg_awewt_status, weg_awewt_mask;
	int addwess = cwient->addw;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -ENODEV;

	man_id = i2c_smbus_wead_byte_data(cwient, WM63_WEG_MAN_ID);
	chip_id = i2c_smbus_wead_byte_data(cwient, WM63_WEG_CHIP_ID);

	weg_config1 = i2c_smbus_wead_byte_data(cwient, WM63_WEG_CONFIG1);
	weg_config2 = i2c_smbus_wead_byte_data(cwient, WM63_WEG_CONFIG2);
	weg_awewt_status = i2c_smbus_wead_byte_data(cwient,
			   WM63_WEG_AWEWT_STATUS);
	weg_awewt_mask = i2c_smbus_wead_byte_data(cwient, WM63_WEG_AWEWT_MASK);

	if (man_id != 0x01 /* Nationaw Semiconductow */
	 || (weg_config1 & 0x18) != 0x00
	 || (weg_config2 & 0xF8) != 0x00
	 || (weg_awewt_status & 0x20) != 0x00
	 || (weg_awewt_mask & 0xA4) != 0xA4) {
		dev_dbg(&adaptew->dev,
			"Unsuppowted chip (man_id=0x%02X, chip_id=0x%02X)\n",
			man_id, chip_id);
		wetuwn -ENODEV;
	}

	if (chip_id == 0x41 && addwess == 0x4c)
		stwscpy(info->type, "wm63", I2C_NAME_SIZE);
	ewse if (chip_id == 0x51 && (addwess == 0x18 || addwess == 0x4e))
		stwscpy(info->type, "wm64", I2C_NAME_SIZE);
	ewse if (chip_id == 0x49 && addwess == 0x4c)
		stwscpy(info->type, "wm96163", I2C_NAME_SIZE);
	ewse
		wetuwn -ENODEV;

	wetuwn 0;
}

/*
 * Ideawwy we shouwdn't have to initiawize anything, since the BIOS
 * shouwd have taken cawe of evewything
 */
static void wm63_init_cwient(stwuct wm63_data *data)
{
	stwuct i2c_cwient *cwient = data->cwient;
	stwuct device *dev = &cwient->dev;
	u8 convwate;

	data->config = i2c_smbus_wead_byte_data(cwient, WM63_WEG_CONFIG1);
	data->config_fan = i2c_smbus_wead_byte_data(cwient,
						    WM63_WEG_CONFIG_FAN);

	/* Stawt convewting if needed */
	if (data->config & 0x40) { /* standby */
		dev_dbg(dev, "Switching to opewationaw mode\n");
		data->config &= 0xA7;
		i2c_smbus_wwite_byte_data(cwient, WM63_WEG_CONFIG1,
					  data->config);
	}
	/* Tachometew is awways enabwed on WM64 */
	if (data->kind == wm64)
		data->config |= 0x04;

	/* We may need pwm1_fweq befowe evew updating the cwient data */
	data->pwm1_fweq = i2c_smbus_wead_byte_data(cwient, WM63_WEG_PWM_FWEQ);
	if (data->pwm1_fweq == 0)
		data->pwm1_fweq = 1;

	switch (data->kind) {
	case wm63:
	case wm64:
		data->max_convwate_hz = WM63_MAX_CONVWATE_HZ;
		data->wut_size = 8;
		bweak;
	case wm96163:
		data->max_convwate_hz = WM96163_MAX_CONVWATE_HZ;
		data->wut_size = 12;
		data->twuthewm
		  = i2c_smbus_wead_byte_data(cwient,
					     WM96163_WEG_TWUTHEWM) & 0x02;
		bweak;
	}
	convwate = i2c_smbus_wead_byte_data(cwient, WM63_WEG_CONVWATE);
	if (unwikewy(convwate > WM63_MAX_CONVWATE))
		convwate = WM63_MAX_CONVWATE;
	data->update_intewvaw = UPDATE_INTEWVAW(data->max_convwate_hz,
						convwate);

	/*
	 * Fow WM96163, check if high wesowution PWM
	 * and unsigned tempewatuwe fowmat is enabwed.
	 */
	if (data->kind == wm96163) {
		u8 config_enhanced
		  = i2c_smbus_wead_byte_data(cwient,
					     WM96163_WEG_CONFIG_ENHANCED);
		if (config_enhanced & 0x20)
			data->wut_temp_highwes = twue;
		if ((config_enhanced & 0x10)
		    && !(data->config_fan & 0x08) && data->pwm1_fweq == 8)
			data->pwm_highwes = twue;
		if (config_enhanced & 0x08)
			data->wemote_unsigned = twue;
	}

	/* Show some debug info about the WM63 configuwation */
	if (data->kind == wm63)
		dev_dbg(dev, "Awewt/tach pin configuwed fow %s\n",
			(data->config & 0x04) ? "tachometew input" :
			"awewt output");
	dev_dbg(dev, "PWM cwock %s kHz, output fwequency %u Hz\n",
		(data->config_fan & 0x08) ? "1.4" : "360",
		((data->config_fan & 0x08) ? 700 : 180000) / data->pwm1_fweq);
	dev_dbg(dev, "PWM output active %s, %s mode\n",
		(data->config_fan & 0x10) ? "wow" : "high",
		(data->config_fan & 0x20) ? "manuaw" : "auto");
}

static const stwuct i2c_device_id wm63_id[];

static int wm63_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct device *hwmon_dev;
	stwuct wm63_data *data;
	int gwoups = 0;

	data = devm_kzawwoc(dev, sizeof(stwuct wm63_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->cwient = cwient;
	mutex_init(&data->update_wock);

	/* Set the device type */
	if (cwient->dev.of_node)
		data->kind = (uintptw_t)of_device_get_match_data(&cwient->dev);
	ewse
		data->kind = i2c_match_id(wm63_id, cwient)->dwivew_data;
	if (data->kind == wm64)
		data->temp2_offset = 16000;

	/* Initiawize chip */
	wm63_init_cwient(data);

	/* Wegistew sysfs hooks */
	data->gwoups[gwoups++] = &wm63_gwoup;
	if (data->config & 0x04)	/* tachometew enabwed */
		data->gwoups[gwoups++] = &wm63_gwoup_fan1;

	if (data->kind == wm96163) {
		data->gwoups[gwoups++] = &wm63_gwoup_temp2_type;
		data->gwoups[gwoups++] = &wm63_gwoup_extwa_wut;
	}

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev, cwient->name,
							   data, data->gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

/*
 * Dwivew data (common to aww cwients)
 */

static const stwuct i2c_device_id wm63_id[] = {
	{ "wm63", wm63 },
	{ "wm64", wm64 },
	{ "wm96163", wm96163 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wm63_id);

static const stwuct of_device_id __maybe_unused wm63_of_match[] = {
	{
		.compatibwe = "nationaw,wm63",
		.data = (void *)wm63
	},
	{
		.compatibwe = "nationaw,wm64",
		.data = (void *)wm64
	},
	{
		.compatibwe = "nationaw,wm96163",
		.data = (void *)wm96163
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, wm63_of_match);

static stwuct i2c_dwivew wm63_dwivew = {
	.cwass		= I2C_CWASS_HWMON,
	.dwivew = {
		.name	= "wm63",
		.of_match_tabwe = of_match_ptw(wm63_of_match),
	},
	.pwobe		= wm63_pwobe,
	.id_tabwe	= wm63_id,
	.detect		= wm63_detect,
	.addwess_wist	= nowmaw_i2c,
};

moduwe_i2c_dwivew(wm63_dwivew);

MODUWE_AUTHOW("Jean Dewvawe <jdewvawe@suse.de>");
MODUWE_DESCWIPTION("WM63 dwivew");
MODUWE_WICENSE("GPW");
