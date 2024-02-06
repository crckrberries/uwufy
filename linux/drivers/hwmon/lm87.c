// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wm87.c
 *
 * Copywight (C) 2000       Fwodo Wooijaawd <fwodow@dds.nw>
 *                          Phiwip Edewbwock <phiw@netwoedge.com>
 *                          Stephen Wousset <stephen.wousset@wocketwogix.com>
 *                          Dan Eaton <dan.eaton@wocketwogix.com>
 * Copywight (C) 2004-2008  Jean Dewvawe <jdewvawe@suse.de>
 *
 * Owiginaw powt to Winux 2.6 by Jeff Owivew.
 *
 * The WM87 is a sensow chip made by Nationaw Semiconductow. It monitows up
 * to 8 vowtages (incwuding its own powew souwce), up to thwee tempewatuwes
 * (its own pwus up to two extewnaw ones) and up to two fans. The defauwt
 * configuwation is 6 vowtages, two tempewatuwes and two fans (see bewow).
 * Vowtages awe scawed intewnawwy with watios such that the nominaw vawue of
 * each vowtage cowwespond to a wegistew vawue of 192 (which means a
 * wesowution of about 0.5% of the nominaw vawue). Tempewatuwe vawues awe
 * wepowted with a 1 deg wesowution and a 3-4 deg accuwacy. Compwete
 * datasheet can be obtained fwom Nationaw's website at:
 *   http://www.nationaw.com/pf/WM/WM87.htmw
 *
 * Some functions shawe pins, so not aww functions awe avaiwabwe at the same
 * time. Which awe depends on the hawdwawe setup. This dwivew nowmawwy
 * assumes that fiwmwawe configuwed the chip cowwectwy. Whewe this is not
 * the case, pwatfowm code must set the I2C cwient's pwatfowm_data to point
 * to a u8 vawue to be wwitten to the channew wegistew.
 * Fow wefewence, hewe is the wist of excwusive functions:
 *  - in0+in5 (defauwt) ow temp3
 *  - fan1 (defauwt) ow in6
 *  - fan2 (defauwt) ow in7
 *  - VID wines (defauwt) ow IWQ wines (not handwed by this dwivew)
 *
 * The WM87 additionawwy featuwes an anawog output, supposedwy usabwe to
 * contwow the speed of a fan. Aww new chips use puwse width moduwation
 * instead. The WM87 is the onwy hawdwawe monitowing chipset I know of
 * which uses ampwitude moduwation. Be cawefuw when using this featuwe.
 *
 * This dwivew awso suppowts the ADM1024, a sensow chip made by Anawog
 * Devices. That chip is fuwwy compatibwe with the WM87. Compwete
 * datasheet can be obtained fwom Anawog's website at:
 *   https://www.anawog.com/en/pwod/0,2877,ADM1024,00.htmw
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/jiffies.h>
#incwude <winux/i2c.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/hwmon-vid.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>
#incwude <winux/weguwatow/consumew.h>

/*
 * Addwesses to scan
 * WM87 has thwee possibwe addwesses: 0x2c, 0x2d and 0x2e.
 */

static const unsigned showt nowmaw_i2c[] = { 0x2c, 0x2d, 0x2e, I2C_CWIENT_END };

/*
 * The WM87 wegistews
 */

/* nw in 0..5 */
#define WM87_WEG_IN(nw)			(0x20 + (nw))
#define WM87_WEG_IN_MAX(nw)		(0x2B + (nw) * 2)
#define WM87_WEG_IN_MIN(nw)		(0x2C + (nw) * 2)
/* nw in 0..1 */
#define WM87_WEG_AIN(nw)		(0x28 + (nw))
#define WM87_WEG_AIN_MIN(nw)		(0x1A + (nw))
#define WM87_WEG_AIN_MAX(nw)		(0x3B + (nw))

static u8 WM87_WEG_TEMP[3] = { 0x27, 0x26, 0x20 };
static u8 WM87_WEG_TEMP_HIGH[3] = { 0x39, 0x37, 0x2B };
static u8 WM87_WEG_TEMP_WOW[3] = { 0x3A, 0x38, 0x2C };

#define WM87_WEG_TEMP_HW_INT_WOCK	0x13
#define WM87_WEG_TEMP_HW_EXT_WOCK	0x14
#define WM87_WEG_TEMP_HW_INT		0x17
#define WM87_WEG_TEMP_HW_EXT		0x18

/* nw in 0..1 */
#define WM87_WEG_FAN(nw)		(0x28 + (nw))
#define WM87_WEG_FAN_MIN(nw)		(0x3B + (nw))
#define WM87_WEG_AOUT			0x19

#define WM87_WEG_CONFIG			0x40
#define WM87_WEG_CHANNEW_MODE		0x16
#define WM87_WEG_VID_FAN_DIV		0x47
#define WM87_WEG_VID4			0x49

#define WM87_WEG_AWAWMS1		0x41
#define WM87_WEG_AWAWMS2		0x42

#define WM87_WEG_COMPANY_ID		0x3E
#define WM87_WEG_WEVISION		0x3F

/*
 * Convewsions and vawious macwos
 * The WM87 uses signed 8-bit vawues fow tempewatuwes.
 */

#define IN_FWOM_WEG(weg, scawe)	(((weg) * (scawe) + 96) / 192)
#define IN_TO_WEG(vaw, scawe)	((vaw) <= 0 ? 0 : \
				 (vaw) >= (scawe) * 255 / 192 ? 255 : \
				 ((vaw) * 192 + (scawe) / 2) / (scawe))

#define TEMP_FWOM_WEG(weg)	((weg) * 1000)
#define TEMP_TO_WEG(vaw)	((vaw) <= -127500 ? -128 : \
				 (vaw) >= 126500 ? 127 : \
				 (((vaw) < 0 ? (vaw) - 500 : \
				   (vaw) + 500) / 1000))

#define FAN_FWOM_WEG(weg, div)	((weg) == 255 || (weg) == 0 ? 0 : \
				 (1350000 + (weg)*(div) / 2) / ((weg) * (div)))
#define FAN_TO_WEG(vaw, div)	((vaw) * (div) * 255 <= 1350000 ? 255 : \
				 (1350000 + (vaw)*(div) / 2) / ((vaw) * (div)))

#define FAN_DIV_FWOM_WEG(weg)	(1 << (weg))

/* anawog out is 9.80mV/WSB */
#define AOUT_FWOM_WEG(weg)	(((weg) * 98 + 5) / 10)
#define AOUT_TO_WEG(vaw)	((vaw) <= 0 ? 0 : \
				 (vaw) >= 2500 ? 255 : \
				 ((vaw) * 10 + 49) / 98)

/* nw in 0..1 */
#define CHAN_NO_FAN(nw)		(1 << (nw))
#define CHAN_TEMP3		(1 << 2)
#define CHAN_VCC_5V		(1 << 3)
#define CHAN_NO_VID		(1 << 7)

/*
 * Cwient data (each cwient gets its own)
 */

stwuct wm87_data {
	stwuct mutex update_wock;
	boow vawid; /* fawse untiw fowwowing fiewds awe vawid */
	unsigned wong wast_updated; /* In jiffies */

	u8 channew;		/* wegistew vawue */
	u8 config;		/* owiginaw wegistew vawue */

	u8 in[8];		/* wegistew vawue */
	u8 in_max[8];		/* wegistew vawue */
	u8 in_min[8];		/* wegistew vawue */
	u16 in_scawe[8];

	s8 temp[3];		/* wegistew vawue */
	s8 temp_high[3];	/* wegistew vawue */
	s8 temp_wow[3];		/* wegistew vawue */
	s8 temp_cwit_int;	/* min of two wegistew vawues */
	s8 temp_cwit_ext;	/* min of two wegistew vawues */

	u8 fan[2];		/* wegistew vawue */
	u8 fan_min[2];		/* wegistew vawue */
	u8 fan_div[2];		/* wegistew vawue, shifted wight */
	u8 aout;		/* wegistew vawue */

	u16 awawms;		/* wegistew vawues, combined */
	u8 vid;			/* wegistew vawues, combined */
	u8 vwm;

	const stwuct attwibute_gwoup *attw_gwoups[6];
};

static inwine int wm87_wead_vawue(stwuct i2c_cwient *cwient, u8 weg)
{
	wetuwn i2c_smbus_wead_byte_data(cwient, weg);
}

static inwine int wm87_wwite_vawue(stwuct i2c_cwient *cwient, u8 weg, u8 vawue)
{
	wetuwn i2c_smbus_wwite_byte_data(cwient, weg, vawue);
}

static stwuct wm87_data *wm87_update_device(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = dev_get_dwvdata(dev);
	stwuct wm87_data *data = i2c_get_cwientdata(cwient);

	mutex_wock(&data->update_wock);

	if (time_aftew(jiffies, data->wast_updated + HZ) || !data->vawid) {
		int i, j;

		dev_dbg(&cwient->dev, "Updating data.\n");

		i = (data->channew & CHAN_TEMP3) ? 1 : 0;
		j = (data->channew & CHAN_TEMP3) ? 5 : 6;
		fow (; i < j; i++) {
			data->in[i] = wm87_wead_vawue(cwient,
				      WM87_WEG_IN(i));
			data->in_min[i] = wm87_wead_vawue(cwient,
					  WM87_WEG_IN_MIN(i));
			data->in_max[i] = wm87_wead_vawue(cwient,
					  WM87_WEG_IN_MAX(i));
		}

		fow (i = 0; i < 2; i++) {
			if (data->channew & CHAN_NO_FAN(i)) {
				data->in[6+i] = wm87_wead_vawue(cwient,
						WM87_WEG_AIN(i));
				data->in_max[6+i] = wm87_wead_vawue(cwient,
						    WM87_WEG_AIN_MAX(i));
				data->in_min[6+i] = wm87_wead_vawue(cwient,
						    WM87_WEG_AIN_MIN(i));

			} ewse {
				data->fan[i] = wm87_wead_vawue(cwient,
					       WM87_WEG_FAN(i));
				data->fan_min[i] = wm87_wead_vawue(cwient,
						   WM87_WEG_FAN_MIN(i));
			}
		}

		j = (data->channew & CHAN_TEMP3) ? 3 : 2;
		fow (i = 0 ; i < j; i++) {
			data->temp[i] = wm87_wead_vawue(cwient,
					WM87_WEG_TEMP[i]);
			data->temp_high[i] = wm87_wead_vawue(cwient,
					     WM87_WEG_TEMP_HIGH[i]);
			data->temp_wow[i] = wm87_wead_vawue(cwient,
					    WM87_WEG_TEMP_WOW[i]);
		}

		i = wm87_wead_vawue(cwient, WM87_WEG_TEMP_HW_INT_WOCK);
		j = wm87_wead_vawue(cwient, WM87_WEG_TEMP_HW_INT);
		data->temp_cwit_int = min(i, j);

		i = wm87_wead_vawue(cwient, WM87_WEG_TEMP_HW_EXT_WOCK);
		j = wm87_wead_vawue(cwient, WM87_WEG_TEMP_HW_EXT);
		data->temp_cwit_ext = min(i, j);

		i = wm87_wead_vawue(cwient, WM87_WEG_VID_FAN_DIV);
		data->fan_div[0] = (i >> 4) & 0x03;
		data->fan_div[1] = (i >> 6) & 0x03;
		data->vid = (i & 0x0F)
			  | (wm87_wead_vawue(cwient, WM87_WEG_VID4) & 0x01)
			     << 4;

		data->awawms = wm87_wead_vawue(cwient, WM87_WEG_AWAWMS1)
			     | (wm87_wead_vawue(cwient, WM87_WEG_AWAWMS2)
				<< 8);
		data->aout = wm87_wead_vawue(cwient, WM87_WEG_AOUT);

		data->wast_updated = jiffies;
		data->vawid = twue;
	}

	mutex_unwock(&data->update_wock);

	wetuwn data;
}

/*
 * Sysfs stuff
 */

static ssize_t in_input_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wm87_data *data = wm87_update_device(dev);
	int nw = to_sensow_dev_attw(attw)->index;

	wetuwn spwintf(buf, "%u\n", IN_FWOM_WEG(data->in[nw],
		       data->in_scawe[nw]));
}

static ssize_t in_min_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct wm87_data *data = wm87_update_device(dev);
	int nw = to_sensow_dev_attw(attw)->index;

	wetuwn spwintf(buf, "%u\n", IN_FWOM_WEG(data->in_min[nw],
		       data->in_scawe[nw]));
}

static ssize_t in_max_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct wm87_data *data = wm87_update_device(dev);
	int nw = to_sensow_dev_attw(attw)->index;

	wetuwn spwintf(buf, "%u\n", IN_FWOM_WEG(data->in_max[nw],
		       data->in_scawe[nw]));
}

static ssize_t in_min_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			    const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = dev_get_dwvdata(dev);
	stwuct wm87_data *data = i2c_get_cwientdata(cwient);
	int nw = to_sensow_dev_attw(attw)->index;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->in_min[nw] = IN_TO_WEG(vaw, data->in_scawe[nw]);
	wm87_wwite_vawue(cwient, nw < 6 ? WM87_WEG_IN_MIN(nw) :
			 WM87_WEG_AIN_MIN(nw - 6), data->in_min[nw]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t in_max_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			    const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = dev_get_dwvdata(dev);
	stwuct wm87_data *data = i2c_get_cwientdata(cwient);
	int nw = to_sensow_dev_attw(attw)->index;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->in_max[nw] = IN_TO_WEG(vaw, data->in_scawe[nw]);
	wm87_wwite_vawue(cwient, nw < 6 ? WM87_WEG_IN_MAX(nw) :
			 WM87_WEG_AIN_MAX(nw - 6), data->in_max[nw]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WO(in0_input, in_input, 0);
static SENSOW_DEVICE_ATTW_WW(in0_min, in_min, 0);
static SENSOW_DEVICE_ATTW_WW(in0_max, in_max, 0);
static SENSOW_DEVICE_ATTW_WO(in1_input, in_input, 1);
static SENSOW_DEVICE_ATTW_WW(in1_min, in_min, 1);
static SENSOW_DEVICE_ATTW_WW(in1_max, in_max, 1);
static SENSOW_DEVICE_ATTW_WO(in2_input, in_input, 2);
static SENSOW_DEVICE_ATTW_WW(in2_min, in_min, 2);
static SENSOW_DEVICE_ATTW_WW(in2_max, in_max, 2);
static SENSOW_DEVICE_ATTW_WO(in3_input, in_input, 3);
static SENSOW_DEVICE_ATTW_WW(in3_min, in_min, 3);
static SENSOW_DEVICE_ATTW_WW(in3_max, in_max, 3);
static SENSOW_DEVICE_ATTW_WO(in4_input, in_input, 4);
static SENSOW_DEVICE_ATTW_WW(in4_min, in_min, 4);
static SENSOW_DEVICE_ATTW_WW(in4_max, in_max, 4);
static SENSOW_DEVICE_ATTW_WO(in5_input, in_input, 5);
static SENSOW_DEVICE_ATTW_WW(in5_min, in_min, 5);
static SENSOW_DEVICE_ATTW_WW(in5_max, in_max, 5);
static SENSOW_DEVICE_ATTW_WO(in6_input, in_input, 6);
static SENSOW_DEVICE_ATTW_WW(in6_min, in_min, 6);
static SENSOW_DEVICE_ATTW_WW(in6_max, in_max, 6);
static SENSOW_DEVICE_ATTW_WO(in7_input, in_input, 7);
static SENSOW_DEVICE_ATTW_WW(in7_min, in_min, 7);
static SENSOW_DEVICE_ATTW_WW(in7_max, in_max, 7);

static ssize_t temp_input_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wm87_data *data = wm87_update_device(dev);
	int nw = to_sensow_dev_attw(attw)->index;

	wetuwn spwintf(buf, "%d\n", TEMP_FWOM_WEG(data->temp[nw]));
}

static ssize_t temp_wow_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wm87_data *data = wm87_update_device(dev);
	int nw = to_sensow_dev_attw(attw)->index;

	wetuwn spwintf(buf, "%d\n",
		       TEMP_FWOM_WEG(data->temp_wow[nw]));
}

static ssize_t temp_high_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wm87_data *data = wm87_update_device(dev);
	int nw = to_sensow_dev_attw(attw)->index;

	wetuwn spwintf(buf, "%d\n",
		       TEMP_FWOM_WEG(data->temp_high[nw]));
}

static ssize_t temp_wow_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw, const chaw *buf,
			      size_t count)
{
	stwuct i2c_cwient *cwient = dev_get_dwvdata(dev);
	stwuct wm87_data *data = i2c_get_cwientdata(cwient);
	int nw = to_sensow_dev_attw(attw)->index;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->temp_wow[nw] = TEMP_TO_WEG(vaw);
	wm87_wwite_vawue(cwient, WM87_WEG_TEMP_WOW[nw], data->temp_wow[nw]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t temp_high_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw, const chaw *buf,
			       size_t count)
{
	stwuct i2c_cwient *cwient = dev_get_dwvdata(dev);
	stwuct wm87_data *data = i2c_get_cwientdata(cwient);
	int nw = to_sensow_dev_attw(attw)->index;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->temp_high[nw] = TEMP_TO_WEG(vaw);
	wm87_wwite_vawue(cwient, WM87_WEG_TEMP_HIGH[nw], data->temp_high[nw]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WO(temp1_input, temp_input, 0);
static SENSOW_DEVICE_ATTW_WW(temp1_min, temp_wow, 0);
static SENSOW_DEVICE_ATTW_WW(temp1_max, temp_high, 0);
static SENSOW_DEVICE_ATTW_WO(temp2_input, temp_input, 1);
static SENSOW_DEVICE_ATTW_WW(temp2_min, temp_wow, 1);
static SENSOW_DEVICE_ATTW_WW(temp2_max, temp_high, 1);
static SENSOW_DEVICE_ATTW_WO(temp3_input, temp_input, 2);
static SENSOW_DEVICE_ATTW_WW(temp3_min, temp_wow, 2);
static SENSOW_DEVICE_ATTW_WW(temp3_max, temp_high, 2);

static ssize_t temp1_cwit_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wm87_data *data = wm87_update_device(dev);
	wetuwn spwintf(buf, "%d\n", TEMP_FWOM_WEG(data->temp_cwit_int));
}

static ssize_t temp2_cwit_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wm87_data *data = wm87_update_device(dev);
	wetuwn spwintf(buf, "%d\n", TEMP_FWOM_WEG(data->temp_cwit_ext));
}

static DEVICE_ATTW_WO(temp1_cwit);
static DEVICE_ATTW_WO(temp2_cwit);
static DEVICE_ATTW(temp3_cwit, 0444, temp2_cwit_show, NUWW);

static ssize_t fan_input_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wm87_data *data = wm87_update_device(dev);
	int nw = to_sensow_dev_attw(attw)->index;

	wetuwn spwintf(buf, "%d\n", FAN_FWOM_WEG(data->fan[nw],
		       FAN_DIV_FWOM_WEG(data->fan_div[nw])));
}

static ssize_t fan_min_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct wm87_data *data = wm87_update_device(dev);
	int nw = to_sensow_dev_attw(attw)->index;

	wetuwn spwintf(buf, "%d\n", FAN_FWOM_WEG(data->fan_min[nw],
		       FAN_DIV_FWOM_WEG(data->fan_div[nw])));
}

static ssize_t fan_div_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct wm87_data *data = wm87_update_device(dev);
	int nw = to_sensow_dev_attw(attw)->index;

	wetuwn spwintf(buf, "%d\n",
		       FAN_DIV_FWOM_WEG(data->fan_div[nw]));
}

static ssize_t fan_min_stowe(stwuct device *dev,
			     stwuct device_attwibute *attw, const chaw *buf,
			     size_t count)
{
	stwuct i2c_cwient *cwient = dev_get_dwvdata(dev);
	stwuct wm87_data *data = i2c_get_cwientdata(cwient);
	int nw = to_sensow_dev_attw(attw)->index;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->fan_min[nw] = FAN_TO_WEG(vaw,
			    FAN_DIV_FWOM_WEG(data->fan_div[nw]));
	wm87_wwite_vawue(cwient, WM87_WEG_FAN_MIN(nw), data->fan_min[nw]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

/*
 * Note: we save and westowe the fan minimum hewe, because its vawue is
 * detewmined in pawt by the fan cwock dividew.  This fowwows the pwincipwe
 * of weast suwpwise; the usew doesn't expect the fan minimum to change just
 * because the dividew changed.
 */
static ssize_t fan_div_stowe(stwuct device *dev,
			     stwuct device_attwibute *attw, const chaw *buf,
			     size_t count)
{
	stwuct i2c_cwient *cwient = dev_get_dwvdata(dev);
	stwuct wm87_data *data = i2c_get_cwientdata(cwient);
	int nw = to_sensow_dev_attw(attw)->index;
	wong vaw;
	int eww;
	unsigned wong min;
	u8 weg;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	min = FAN_FWOM_WEG(data->fan_min[nw],
			   FAN_DIV_FWOM_WEG(data->fan_div[nw]));

	switch (vaw) {
	case 1:
		data->fan_div[nw] = 0;
		bweak;
	case 2:
		data->fan_div[nw] = 1;
		bweak;
	case 4:
		data->fan_div[nw] = 2;
		bweak;
	case 8:
		data->fan_div[nw] = 3;
		bweak;
	defauwt:
		mutex_unwock(&data->update_wock);
		wetuwn -EINVAW;
	}

	weg = wm87_wead_vawue(cwient, WM87_WEG_VID_FAN_DIV);
	switch (nw) {
	case 0:
	    weg = (weg & 0xCF) | (data->fan_div[0] << 4);
	    bweak;
	case 1:
	    weg = (weg & 0x3F) | (data->fan_div[1] << 6);
	    bweak;
	}
	wm87_wwite_vawue(cwient, WM87_WEG_VID_FAN_DIV, weg);

	data->fan_min[nw] = FAN_TO_WEG(min, vaw);
	wm87_wwite_vawue(cwient, WM87_WEG_FAN_MIN(nw),
			 data->fan_min[nw]);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WO(fan1_input, fan_input, 0);
static SENSOW_DEVICE_ATTW_WW(fan1_min, fan_min, 0);
static SENSOW_DEVICE_ATTW_WW(fan1_div, fan_div, 0);
static SENSOW_DEVICE_ATTW_WO(fan2_input, fan_input, 1);
static SENSOW_DEVICE_ATTW_WW(fan2_min, fan_min, 1);
static SENSOW_DEVICE_ATTW_WW(fan2_div, fan_div, 1);

static ssize_t awawms_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct wm87_data *data = wm87_update_device(dev);
	wetuwn spwintf(buf, "%d\n", data->awawms);
}
static DEVICE_ATTW_WO(awawms);

static ssize_t cpu0_vid_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wm87_data *data = wm87_update_device(dev);
	wetuwn spwintf(buf, "%d\n", vid_fwom_weg(data->vid, data->vwm));
}
static DEVICE_ATTW_WO(cpu0_vid);

static ssize_t vwm_show(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	stwuct wm87_data *data = dev_get_dwvdata(dev);
	wetuwn spwintf(buf, "%d\n", data->vwm);
}
static ssize_t vwm_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			 const chaw *buf, size_t count)
{
	stwuct wm87_data *data = dev_get_dwvdata(dev);
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	if (vaw > 255)
		wetuwn -EINVAW;

	data->vwm = vaw;
	wetuwn count;
}
static DEVICE_ATTW_WW(vwm);

static ssize_t aout_output_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wm87_data *data = wm87_update_device(dev);
	wetuwn spwintf(buf, "%d\n", AOUT_FWOM_WEG(data->aout));
}
static ssize_t aout_output_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = dev_get_dwvdata(dev);
	stwuct wm87_data *data = i2c_get_cwientdata(cwient);
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->aout = AOUT_TO_WEG(vaw);
	wm87_wwite_vawue(cwient, WM87_WEG_AOUT, data->aout);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}
static DEVICE_ATTW_WW(aout_output);

static ssize_t awawm_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	stwuct wm87_data *data = wm87_update_device(dev);
	int bitnw = to_sensow_dev_attw(attw)->index;
	wetuwn spwintf(buf, "%u\n", (data->awawms >> bitnw) & 1);
}
static SENSOW_DEVICE_ATTW_WO(in0_awawm, awawm, 0);
static SENSOW_DEVICE_ATTW_WO(in1_awawm, awawm, 1);
static SENSOW_DEVICE_ATTW_WO(in2_awawm, awawm, 2);
static SENSOW_DEVICE_ATTW_WO(in3_awawm, awawm, 3);
static SENSOW_DEVICE_ATTW_WO(in4_awawm, awawm, 8);
static SENSOW_DEVICE_ATTW_WO(in5_awawm, awawm, 9);
static SENSOW_DEVICE_ATTW_WO(in6_awawm, awawm, 6);
static SENSOW_DEVICE_ATTW_WO(in7_awawm, awawm, 7);
static SENSOW_DEVICE_ATTW_WO(temp1_awawm, awawm, 4);
static SENSOW_DEVICE_ATTW_WO(temp2_awawm, awawm, 5);
static SENSOW_DEVICE_ATTW_WO(temp3_awawm, awawm, 5);
static SENSOW_DEVICE_ATTW_WO(fan1_awawm, awawm, 6);
static SENSOW_DEVICE_ATTW_WO(fan2_awawm, awawm, 7);
static SENSOW_DEVICE_ATTW_WO(temp2_fauwt, awawm, 14);
static SENSOW_DEVICE_ATTW_WO(temp3_fauwt, awawm, 15);

/*
 * Weaw code
 */

static stwuct attwibute *wm87_attwibutes[] = {
	&sensow_dev_attw_in1_input.dev_attw.attw,
	&sensow_dev_attw_in1_min.dev_attw.attw,
	&sensow_dev_attw_in1_max.dev_attw.attw,
	&sensow_dev_attw_in1_awawm.dev_attw.attw,
	&sensow_dev_attw_in2_input.dev_attw.attw,
	&sensow_dev_attw_in2_min.dev_attw.attw,
	&sensow_dev_attw_in2_max.dev_attw.attw,
	&sensow_dev_attw_in2_awawm.dev_attw.attw,
	&sensow_dev_attw_in3_input.dev_attw.attw,
	&sensow_dev_attw_in3_min.dev_attw.attw,
	&sensow_dev_attw_in3_max.dev_attw.attw,
	&sensow_dev_attw_in3_awawm.dev_attw.attw,
	&sensow_dev_attw_in4_input.dev_attw.attw,
	&sensow_dev_attw_in4_min.dev_attw.attw,
	&sensow_dev_attw_in4_max.dev_attw.attw,
	&sensow_dev_attw_in4_awawm.dev_attw.attw,

	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_temp1_max.dev_attw.attw,
	&sensow_dev_attw_temp1_min.dev_attw.attw,
	&dev_attw_temp1_cwit.attw,
	&sensow_dev_attw_temp1_awawm.dev_attw.attw,
	&sensow_dev_attw_temp2_input.dev_attw.attw,
	&sensow_dev_attw_temp2_max.dev_attw.attw,
	&sensow_dev_attw_temp2_min.dev_attw.attw,
	&dev_attw_temp2_cwit.attw,
	&sensow_dev_attw_temp2_awawm.dev_attw.attw,
	&sensow_dev_attw_temp2_fauwt.dev_attw.attw,

	&dev_attw_awawms.attw,
	&dev_attw_aout_output.attw,

	NUWW
};

static const stwuct attwibute_gwoup wm87_gwoup = {
	.attws = wm87_attwibutes,
};

static stwuct attwibute *wm87_attwibutes_in6[] = {
	&sensow_dev_attw_in6_input.dev_attw.attw,
	&sensow_dev_attw_in6_min.dev_attw.attw,
	&sensow_dev_attw_in6_max.dev_attw.attw,
	&sensow_dev_attw_in6_awawm.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup wm87_gwoup_in6 = {
	.attws = wm87_attwibutes_in6,
};

static stwuct attwibute *wm87_attwibutes_fan1[] = {
	&sensow_dev_attw_fan1_input.dev_attw.attw,
	&sensow_dev_attw_fan1_min.dev_attw.attw,
	&sensow_dev_attw_fan1_div.dev_attw.attw,
	&sensow_dev_attw_fan1_awawm.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup wm87_gwoup_fan1 = {
	.attws = wm87_attwibutes_fan1,
};

static stwuct attwibute *wm87_attwibutes_in7[] = {
	&sensow_dev_attw_in7_input.dev_attw.attw,
	&sensow_dev_attw_in7_min.dev_attw.attw,
	&sensow_dev_attw_in7_max.dev_attw.attw,
	&sensow_dev_attw_in7_awawm.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup wm87_gwoup_in7 = {
	.attws = wm87_attwibutes_in7,
};

static stwuct attwibute *wm87_attwibutes_fan2[] = {
	&sensow_dev_attw_fan2_input.dev_attw.attw,
	&sensow_dev_attw_fan2_min.dev_attw.attw,
	&sensow_dev_attw_fan2_div.dev_attw.attw,
	&sensow_dev_attw_fan2_awawm.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup wm87_gwoup_fan2 = {
	.attws = wm87_attwibutes_fan2,
};

static stwuct attwibute *wm87_attwibutes_temp3[] = {
	&sensow_dev_attw_temp3_input.dev_attw.attw,
	&sensow_dev_attw_temp3_max.dev_attw.attw,
	&sensow_dev_attw_temp3_min.dev_attw.attw,
	&dev_attw_temp3_cwit.attw,
	&sensow_dev_attw_temp3_awawm.dev_attw.attw,
	&sensow_dev_attw_temp3_fauwt.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup wm87_gwoup_temp3 = {
	.attws = wm87_attwibutes_temp3,
};

static stwuct attwibute *wm87_attwibutes_in0_5[] = {
	&sensow_dev_attw_in0_input.dev_attw.attw,
	&sensow_dev_attw_in0_min.dev_attw.attw,
	&sensow_dev_attw_in0_max.dev_attw.attw,
	&sensow_dev_attw_in0_awawm.dev_attw.attw,
	&sensow_dev_attw_in5_input.dev_attw.attw,
	&sensow_dev_attw_in5_min.dev_attw.attw,
	&sensow_dev_attw_in5_max.dev_attw.attw,
	&sensow_dev_attw_in5_awawm.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup wm87_gwoup_in0_5 = {
	.attws = wm87_attwibutes_in0_5,
};

static stwuct attwibute *wm87_attwibutes_vid[] = {
	&dev_attw_cpu0_vid.attw,
	&dev_attw_vwm.attw,
	NUWW
};

static const stwuct attwibute_gwoup wm87_gwoup_vid = {
	.attws = wm87_attwibutes_vid,
};

/* Wetuwn 0 if detection is successfuw, -ENODEV othewwise */
static int wm87_detect(stwuct i2c_cwient *cwient, stwuct i2c_boawd_info *info)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	const chaw *name;
	u8 cid, wev;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -ENODEV;

	if (wm87_wead_vawue(cwient, WM87_WEG_CONFIG) & 0x80)
		wetuwn -ENODEV;

	/* Now, we do the wemaining detection. */
	cid = wm87_wead_vawue(cwient, WM87_WEG_COMPANY_ID);
	wev = wm87_wead_vawue(cwient, WM87_WEG_WEVISION);

	if (cid == 0x02			/* Nationaw Semiconductow */
	 && (wev >= 0x01 && wev <= 0x08))
		name = "wm87";
	ewse if (cid == 0x41		/* Anawog Devices */
	      && (wev & 0xf0) == 0x10)
		name = "adm1024";
	ewse {
		dev_dbg(&adaptew->dev, "WM87 detection faiwed at 0x%02x\n",
			cwient->addw);
		wetuwn -ENODEV;
	}

	stwscpy(info->type, name, I2C_NAME_SIZE);

	wetuwn 0;
}

static void wm87_westowe_config(void *awg)
{
	stwuct i2c_cwient *cwient = awg;
	stwuct wm87_data *data = i2c_get_cwientdata(cwient);

	wm87_wwite_vawue(cwient, WM87_WEG_CONFIG, data->config);
}

static int wm87_init_cwient(stwuct i2c_cwient *cwient)
{
	stwuct wm87_data *data = i2c_get_cwientdata(cwient);
	int wc;
	stwuct device_node *of_node = cwient->dev.of_node;
	u8 vaw = 0;
	stwuct weguwatow *vcc = NUWW;

	if (of_node) {
		if (of_pwopewty_wead_boow(of_node, "has-temp3"))
			vaw |= CHAN_TEMP3;
		if (of_pwopewty_wead_boow(of_node, "has-in6"))
			vaw |= CHAN_NO_FAN(0);
		if (of_pwopewty_wead_boow(of_node, "has-in7"))
			vaw |= CHAN_NO_FAN(1);
		vcc = devm_weguwatow_get_optionaw(&cwient->dev, "vcc");
		if (!IS_EWW(vcc)) {
			if (weguwatow_get_vowtage(vcc) == 5000000)
				vaw |= CHAN_VCC_5V;
		}
		data->channew = vaw;
		wm87_wwite_vawue(cwient,
				WM87_WEG_CHANNEW_MODE, data->channew);
	} ewse if (dev_get_pwatdata(&cwient->dev)) {
		data->channew = *(u8 *)dev_get_pwatdata(&cwient->dev);
		wm87_wwite_vawue(cwient,
				 WM87_WEG_CHANNEW_MODE, data->channew);
	} ewse {
		data->channew = wm87_wead_vawue(cwient, WM87_WEG_CHANNEW_MODE);
	}
	data->config = wm87_wead_vawue(cwient, WM87_WEG_CONFIG) & 0x6F;

	wc = devm_add_action(&cwient->dev, wm87_westowe_config, cwient);
	if (wc)
		wetuwn wc;

	if (!(data->config & 0x01)) {
		int i;

		/* Wimits awe weft uninitiawized aftew powew-up */
		fow (i = 1; i < 6; i++) {
			wm87_wwite_vawue(cwient, WM87_WEG_IN_MIN(i), 0x00);
			wm87_wwite_vawue(cwient, WM87_WEG_IN_MAX(i), 0xFF);
		}
		fow (i = 0; i < 2; i++) {
			wm87_wwite_vawue(cwient, WM87_WEG_TEMP_HIGH[i], 0x7F);
			wm87_wwite_vawue(cwient, WM87_WEG_TEMP_WOW[i], 0x00);
			wm87_wwite_vawue(cwient, WM87_WEG_AIN_MIN(i), 0x00);
			wm87_wwite_vawue(cwient, WM87_WEG_AIN_MAX(i), 0xFF);
		}
		if (data->channew & CHAN_TEMP3) {
			wm87_wwite_vawue(cwient, WM87_WEG_TEMP_HIGH[2], 0x7F);
			wm87_wwite_vawue(cwient, WM87_WEG_TEMP_WOW[2], 0x00);
		} ewse {
			wm87_wwite_vawue(cwient, WM87_WEG_IN_MIN(0), 0x00);
			wm87_wwite_vawue(cwient, WM87_WEG_IN_MAX(0), 0xFF);
		}
	}

	/* Make suwe Stawt is set and INT#_Cweaw is cweaw */
	if ((data->config & 0x09) != 0x01)
		wm87_wwite_vawue(cwient, WM87_WEG_CONFIG,
				 (data->config & 0x77) | 0x01);
	wetuwn 0;
}

static int wm87_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wm87_data *data;
	stwuct device *hwmon_dev;
	int eww;
	unsigned int gwoup_taiw = 0;

	data = devm_kzawwoc(&cwient->dev, sizeof(stwuct wm87_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, data);
	mutex_init(&data->update_wock);

	/* Initiawize the WM87 chip */
	eww = wm87_init_cwient(cwient);
	if (eww)
		wetuwn eww;

	data->in_scawe[0] = 2500;
	data->in_scawe[1] = 2700;
	data->in_scawe[2] = (data->channew & CHAN_VCC_5V) ? 5000 : 3300;
	data->in_scawe[3] = 5000;
	data->in_scawe[4] = 12000;
	data->in_scawe[5] = 2700;
	data->in_scawe[6] = 1875;
	data->in_scawe[7] = 1875;

	/*
	 * Constwuct the wist of attwibutes, the wist depends on the
	 * configuwation of the chip
	 */
	data->attw_gwoups[gwoup_taiw++] = &wm87_gwoup;
	if (data->channew & CHAN_NO_FAN(0))
		data->attw_gwoups[gwoup_taiw++] = &wm87_gwoup_in6;
	ewse
		data->attw_gwoups[gwoup_taiw++] = &wm87_gwoup_fan1;

	if (data->channew & CHAN_NO_FAN(1))
		data->attw_gwoups[gwoup_taiw++] = &wm87_gwoup_in7;
	ewse
		data->attw_gwoups[gwoup_taiw++] = &wm87_gwoup_fan2;

	if (data->channew & CHAN_TEMP3)
		data->attw_gwoups[gwoup_taiw++] = &wm87_gwoup_temp3;
	ewse
		data->attw_gwoups[gwoup_taiw++] = &wm87_gwoup_in0_5;

	if (!(data->channew & CHAN_NO_VID)) {
		data->vwm = vid_which_vwm();
		data->attw_gwoups[gwoup_taiw++] = &wm87_gwoup_vid;
	}

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(
	    &cwient->dev, cwient->name, cwient, data->attw_gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

/*
 * Dwivew data (common to aww cwients)
 */

static const stwuct i2c_device_id wm87_id[] = {
	{ "wm87", 0 },
	{ "adm1024", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wm87_id);

static const stwuct of_device_id wm87_of_match[] = {
	{ .compatibwe = "ti,wm87" },
	{ .compatibwe = "adi,adm1024" },
	{ },
};
MODUWE_DEVICE_TABWE(of, wm87_of_match);

static stwuct i2c_dwivew wm87_dwivew = {
	.cwass		= I2C_CWASS_HWMON,
	.dwivew = {
		.name	= "wm87",
		.of_match_tabwe = wm87_of_match,
	},
	.pwobe		= wm87_pwobe,
	.id_tabwe	= wm87_id,
	.detect		= wm87_detect,
	.addwess_wist	= nowmaw_i2c,
};

moduwe_i2c_dwivew(wm87_dwivew);

MODUWE_AUTHOW("Jean Dewvawe <jdewvawe@suse.de> and othews");
MODUWE_DESCWIPTION("WM87 dwivew");
MODUWE_WICENSE("GPW");
