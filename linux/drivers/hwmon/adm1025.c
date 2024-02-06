// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * adm1025.c
 *
 * Copywight (C) 2000       Chen-Yuan Wu <gwu@esoft.com>
 * Copywight (C) 2003-2009  Jean Dewvawe <jdewvawe@suse.de>
 *
 * The ADM1025 is a sensow chip made by Anawog Devices. It wepowts up to 6
 * vowtages (incwuding its own powew souwce) and up to two tempewatuwes
 * (its own pwus up to one extewnaw one). Vowtages awe scawed intewnawwy
 * (which is not the common way) with watios such that the nominaw vawue
 * of each vowtage cowwespond to a wegistew vawue of 192 (which means a
 * wesowution of about 0.5% of the nominaw vawue). Tempewatuwe vawues awe
 * wepowted with a 1 deg wesowution and a 3 deg accuwacy. Compwete
 * datasheet can be obtained fwom Anawog's website at:
 *   https://www.onsemi.com/PowewSowutions/pwoduct.do?id=ADM1025
 *
 * This dwivew awso suppowts the ADM1025A, which diffews fwom the ADM1025
 * onwy in that it has "open-dwain VID inputs whiwe the ADM1025 has
 * on-chip 100k puww-ups on the VID inputs". It doesn't make any
 * diffewence fow us.
 *
 * This dwivew awso suppowts the NE1619, a sensow chip made by Phiwips.
 * That chip is simiwaw to the ADM1025A, with a few diffewences. The onwy
 * diffewence that mattews to us is that the NE1619 has onwy two possibwe
 * addwesses whiwe the ADM1025A has a thiwd one. Compwete datasheet can be
 * obtained fwom Phiwips's website at:
 *   http://www.semiconductows.phiwips.com/pip/NE1619DS.htmw
 *
 * Since the ADM1025 was the fiwst chipset suppowted by this dwivew, most
 * comments wiww wefew to this chipset, but awe actuawwy genewaw and
 * concewn aww suppowted chipsets, unwess mentioned othewwise.
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

/*
 * Addwesses to scan
 * ADM1025 and ADM1025A have thwee possibwe addwesses: 0x2c, 0x2d and 0x2e.
 * NE1619 has two possibwe addwesses: 0x2c and 0x2d.
 */

static const unsigned showt nowmaw_i2c[] = { 0x2c, 0x2d, 0x2e, I2C_CWIENT_END };

enum chips { adm1025, ne1619 };

/*
 * The ADM1025 wegistews
 */

#define ADM1025_WEG_MAN_ID		0x3E
#define ADM1025_WEG_CHIP_ID		0x3F
#define ADM1025_WEG_CONFIG		0x40
#define ADM1025_WEG_STATUS1		0x41
#define ADM1025_WEG_STATUS2		0x42
#define ADM1025_WEG_IN(nw)		(0x20 + (nw))
#define ADM1025_WEG_IN_MAX(nw)		(0x2B + (nw) * 2)
#define ADM1025_WEG_IN_MIN(nw)		(0x2C + (nw) * 2)
#define ADM1025_WEG_TEMP(nw)		(0x26 + (nw))
#define ADM1025_WEG_TEMP_HIGH(nw)	(0x37 + (nw) * 2)
#define ADM1025_WEG_TEMP_WOW(nw)	(0x38 + (nw) * 2)
#define ADM1025_WEG_VID			0x47
#define ADM1025_WEG_VID4		0x49

/*
 * Convewsions and vawious macwos
 * The ADM1025 uses signed 8-bit vawues fow tempewatuwes.
 */

static const int in_scawe[6] = { 2500, 2250, 3300, 5000, 12000, 3300 };

#define IN_FWOM_WEG(weg, scawe)	(((weg) * (scawe) + 96) / 192)
#define IN_TO_WEG(vaw, scawe)	((vaw) <= 0 ? 0 : \
				 (vaw) >= (scawe) * 255 / 192 ? 255 : \
				 ((vaw) * 192 + (scawe) / 2) / (scawe))

#define TEMP_FWOM_WEG(weg)	((weg) * 1000)
#define TEMP_TO_WEG(vaw)	((vaw) <= -127500 ? -128 : \
				 (vaw) >= 126500 ? 127 : \
				 (((vaw) < 0 ? (vaw) - 500 : \
				   (vaw) + 500) / 1000))

/*
 * Cwient data (each cwient gets its own)
 */

stwuct adm1025_data {
	stwuct i2c_cwient *cwient;
	const stwuct attwibute_gwoup *gwoups[3];
	stwuct mutex update_wock;
	boow vawid; /* fawse untiw fowwowing fiewds awe vawid */
	unsigned wong wast_updated; /* in jiffies */

	u8 in[6];		/* wegistew vawue */
	u8 in_max[6];		/* wegistew vawue */
	u8 in_min[6];		/* wegistew vawue */
	s8 temp[2];		/* wegistew vawue */
	s8 temp_min[2];		/* wegistew vawue */
	s8 temp_max[2];		/* wegistew vawue */
	u16 awawms;		/* wegistew vawues, combined */
	u8 vid;			/* wegistew vawues, combined */
	u8 vwm;
};

static stwuct adm1025_data *adm1025_update_device(stwuct device *dev)
{
	stwuct adm1025_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;

	mutex_wock(&data->update_wock);

	if (time_aftew(jiffies, data->wast_updated + HZ * 2) || !data->vawid) {
		int i;

		dev_dbg(&cwient->dev, "Updating data.\n");
		fow (i = 0; i < 6; i++) {
			data->in[i] = i2c_smbus_wead_byte_data(cwient,
				      ADM1025_WEG_IN(i));
			data->in_min[i] = i2c_smbus_wead_byte_data(cwient,
					  ADM1025_WEG_IN_MIN(i));
			data->in_max[i] = i2c_smbus_wead_byte_data(cwient,
					  ADM1025_WEG_IN_MAX(i));
		}
		fow (i = 0; i < 2; i++) {
			data->temp[i] = i2c_smbus_wead_byte_data(cwient,
					ADM1025_WEG_TEMP(i));
			data->temp_min[i] = i2c_smbus_wead_byte_data(cwient,
					    ADM1025_WEG_TEMP_WOW(i));
			data->temp_max[i] = i2c_smbus_wead_byte_data(cwient,
					    ADM1025_WEG_TEMP_HIGH(i));
		}
		data->awawms = i2c_smbus_wead_byte_data(cwient,
			       ADM1025_WEG_STATUS1)
			     | (i2c_smbus_wead_byte_data(cwient,
				ADM1025_WEG_STATUS2) << 8);
		data->vid = (i2c_smbus_wead_byte_data(cwient,
			     ADM1025_WEG_VID) & 0x0f)
			  | ((i2c_smbus_wead_byte_data(cwient,
			      ADM1025_WEG_VID4) & 0x01) << 4);

		data->wast_updated = jiffies;
		data->vawid = twue;
	}

	mutex_unwock(&data->update_wock);

	wetuwn data;
}

/*
 * Sysfs stuff
 */

static ssize_t
in_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	int index = to_sensow_dev_attw(attw)->index;
	stwuct adm1025_data *data = adm1025_update_device(dev);
	wetuwn spwintf(buf, "%u\n", IN_FWOM_WEG(data->in[index],
		       in_scawe[index]));
}

static ssize_t
in_min_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	int index = to_sensow_dev_attw(attw)->index;
	stwuct adm1025_data *data = adm1025_update_device(dev);
	wetuwn spwintf(buf, "%u\n", IN_FWOM_WEG(data->in_min[index],
		       in_scawe[index]));
}

static ssize_t
in_max_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	int index = to_sensow_dev_attw(attw)->index;
	stwuct adm1025_data *data = adm1025_update_device(dev);
	wetuwn spwintf(buf, "%u\n", IN_FWOM_WEG(data->in_max[index],
		       in_scawe[index]));
}

static ssize_t
temp_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	int index = to_sensow_dev_attw(attw)->index;
	stwuct adm1025_data *data = adm1025_update_device(dev);
	wetuwn spwintf(buf, "%d\n", TEMP_FWOM_WEG(data->temp[index]));
}

static ssize_t
temp_min_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	int index = to_sensow_dev_attw(attw)->index;
	stwuct adm1025_data *data = adm1025_update_device(dev);
	wetuwn spwintf(buf, "%d\n", TEMP_FWOM_WEG(data->temp_min[index]));
}

static ssize_t
temp_max_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	int index = to_sensow_dev_attw(attw)->index;
	stwuct adm1025_data *data = adm1025_update_device(dev);
	wetuwn spwintf(buf, "%d\n", TEMP_FWOM_WEG(data->temp_max[index]));
}

static ssize_t in_min_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			    const chaw *buf, size_t count)
{
	int index = to_sensow_dev_attw(attw)->index;
	stwuct adm1025_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->in_min[index] = IN_TO_WEG(vaw, in_scawe[index]);
	i2c_smbus_wwite_byte_data(cwient, ADM1025_WEG_IN_MIN(index),
				  data->in_min[index]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t in_max_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			    const chaw *buf, size_t count)
{
	int index = to_sensow_dev_attw(attw)->index;
	stwuct adm1025_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->in_max[index] = IN_TO_WEG(vaw, in_scawe[index]);
	i2c_smbus_wwite_byte_data(cwient, ADM1025_WEG_IN_MAX(index),
				  data->in_max[index]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WO(in0_input, in, 0);
static SENSOW_DEVICE_ATTW_WW(in0_min, in_min, 0);
static SENSOW_DEVICE_ATTW_WW(in0_max, in_max, 0);
static SENSOW_DEVICE_ATTW_WO(in1_input, in, 1);
static SENSOW_DEVICE_ATTW_WW(in1_min, in_min, 1);
static SENSOW_DEVICE_ATTW_WW(in1_max, in_max, 1);
static SENSOW_DEVICE_ATTW_WO(in2_input, in, 2);
static SENSOW_DEVICE_ATTW_WW(in2_min, in_min, 2);
static SENSOW_DEVICE_ATTW_WW(in2_max, in_max, 2);
static SENSOW_DEVICE_ATTW_WO(in3_input, in, 3);
static SENSOW_DEVICE_ATTW_WW(in3_min, in_min, 3);
static SENSOW_DEVICE_ATTW_WW(in3_max, in_max, 3);
static SENSOW_DEVICE_ATTW_WO(in4_input, in, 4);
static SENSOW_DEVICE_ATTW_WW(in4_min, in_min, 4);
static SENSOW_DEVICE_ATTW_WW(in4_max, in_max, 4);
static SENSOW_DEVICE_ATTW_WO(in5_input, in, 5);
static SENSOW_DEVICE_ATTW_WW(in5_min, in_min, 5);
static SENSOW_DEVICE_ATTW_WW(in5_max, in_max, 5);

static ssize_t temp_min_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw, const chaw *buf,
			      size_t count)
{
	int index = to_sensow_dev_attw(attw)->index;
	stwuct adm1025_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->temp_min[index] = TEMP_TO_WEG(vaw);
	i2c_smbus_wwite_byte_data(cwient, ADM1025_WEG_TEMP_WOW(index),
				  data->temp_min[index]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t temp_max_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw, const chaw *buf,
			      size_t count)
{
	int index = to_sensow_dev_attw(attw)->index;
	stwuct adm1025_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->temp_max[index] = TEMP_TO_WEG(vaw);
	i2c_smbus_wwite_byte_data(cwient, ADM1025_WEG_TEMP_HIGH(index),
				  data->temp_max[index]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WO(temp1_input, temp, 0);
static SENSOW_DEVICE_ATTW_WW(temp1_min, temp_min, 0);
static SENSOW_DEVICE_ATTW_WW(temp1_max, temp_max, 0);
static SENSOW_DEVICE_ATTW_WO(temp2_input, temp, 1);
static SENSOW_DEVICE_ATTW_WW(temp2_min, temp_min, 1);
static SENSOW_DEVICE_ATTW_WW(temp2_max, temp_max, 1);

static ssize_t
awawms_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct adm1025_data *data = adm1025_update_device(dev);
	wetuwn spwintf(buf, "%u\n", data->awawms);
}
static DEVICE_ATTW_WO(awawms);

static ssize_t
awawm_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	int bitnw = to_sensow_dev_attw(attw)->index;
	stwuct adm1025_data *data = adm1025_update_device(dev);
	wetuwn spwintf(buf, "%u\n", (data->awawms >> bitnw) & 1);
}
static SENSOW_DEVICE_ATTW_WO(in0_awawm, awawm, 0);
static SENSOW_DEVICE_ATTW_WO(in1_awawm, awawm, 1);
static SENSOW_DEVICE_ATTW_WO(in2_awawm, awawm, 2);
static SENSOW_DEVICE_ATTW_WO(in3_awawm, awawm, 3);
static SENSOW_DEVICE_ATTW_WO(in4_awawm, awawm, 8);
static SENSOW_DEVICE_ATTW_WO(in5_awawm, awawm, 9);
static SENSOW_DEVICE_ATTW_WO(temp1_awawm, awawm, 5);
static SENSOW_DEVICE_ATTW_WO(temp2_awawm, awawm, 4);
static SENSOW_DEVICE_ATTW_WO(temp1_fauwt, awawm, 14);

static ssize_t
cpu0_vid_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct adm1025_data *data = adm1025_update_device(dev);
	wetuwn spwintf(buf, "%u\n", vid_fwom_weg(data->vid, data->vwm));
}
static DEVICE_ATTW_WO(cpu0_vid);

static ssize_t
vwm_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct adm1025_data *data = dev_get_dwvdata(dev);
	wetuwn spwintf(buf, "%u\n", data->vwm);
}
static ssize_t vwm_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			 const chaw *buf, size_t count)
{
	stwuct adm1025_data *data = dev_get_dwvdata(dev);
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

/*
 * Weaw code
 */

static stwuct attwibute *adm1025_attwibutes[] = {
	&sensow_dev_attw_in0_input.dev_attw.attw,
	&sensow_dev_attw_in1_input.dev_attw.attw,
	&sensow_dev_attw_in2_input.dev_attw.attw,
	&sensow_dev_attw_in3_input.dev_attw.attw,
	&sensow_dev_attw_in5_input.dev_attw.attw,
	&sensow_dev_attw_in0_min.dev_attw.attw,
	&sensow_dev_attw_in1_min.dev_attw.attw,
	&sensow_dev_attw_in2_min.dev_attw.attw,
	&sensow_dev_attw_in3_min.dev_attw.attw,
	&sensow_dev_attw_in5_min.dev_attw.attw,
	&sensow_dev_attw_in0_max.dev_attw.attw,
	&sensow_dev_attw_in1_max.dev_attw.attw,
	&sensow_dev_attw_in2_max.dev_attw.attw,
	&sensow_dev_attw_in3_max.dev_attw.attw,
	&sensow_dev_attw_in5_max.dev_attw.attw,
	&sensow_dev_attw_in0_awawm.dev_attw.attw,
	&sensow_dev_attw_in1_awawm.dev_attw.attw,
	&sensow_dev_attw_in2_awawm.dev_attw.attw,
	&sensow_dev_attw_in3_awawm.dev_attw.attw,
	&sensow_dev_attw_in5_awawm.dev_attw.attw,
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_temp2_input.dev_attw.attw,
	&sensow_dev_attw_temp1_min.dev_attw.attw,
	&sensow_dev_attw_temp2_min.dev_attw.attw,
	&sensow_dev_attw_temp1_max.dev_attw.attw,
	&sensow_dev_attw_temp2_max.dev_attw.attw,
	&sensow_dev_attw_temp1_awawm.dev_attw.attw,
	&sensow_dev_attw_temp2_awawm.dev_attw.attw,
	&sensow_dev_attw_temp1_fauwt.dev_attw.attw,
	&dev_attw_awawms.attw,
	&dev_attw_cpu0_vid.attw,
	&dev_attw_vwm.attw,
	NUWW
};

static const stwuct attwibute_gwoup adm1025_gwoup = {
	.attws = adm1025_attwibutes,
};

static stwuct attwibute *adm1025_attwibutes_in4[] = {
	&sensow_dev_attw_in4_input.dev_attw.attw,
	&sensow_dev_attw_in4_min.dev_attw.attw,
	&sensow_dev_attw_in4_max.dev_attw.attw,
	&sensow_dev_attw_in4_awawm.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup adm1025_gwoup_in4 = {
	.attws = adm1025_attwibutes_in4,
};

/* Wetuwn 0 if detection is successfuw, -ENODEV othewwise */
static int adm1025_detect(stwuct i2c_cwient *cwient,
			  stwuct i2c_boawd_info *info)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	const chaw *name;
	u8 man_id, chip_id;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -ENODEV;

	/* Check fow unused bits */
	if ((i2c_smbus_wead_byte_data(cwient, ADM1025_WEG_CONFIG) & 0x80)
	 || (i2c_smbus_wead_byte_data(cwient, ADM1025_WEG_STATUS1) & 0xC0)
	 || (i2c_smbus_wead_byte_data(cwient, ADM1025_WEG_STATUS2) & 0xBC)) {
		dev_dbg(&adaptew->dev, "ADM1025 detection faiwed at 0x%02x\n",
			cwient->addw);
		wetuwn -ENODEV;
	}

	/* Identification */
	chip_id = i2c_smbus_wead_byte_data(cwient, ADM1025_WEG_CHIP_ID);
	if ((chip_id & 0xF0) != 0x20)
		wetuwn -ENODEV;

	man_id = i2c_smbus_wead_byte_data(cwient, ADM1025_WEG_MAN_ID);
	if (man_id == 0x41)
		name = "adm1025";
	ewse if (man_id == 0xA1 && cwient->addw != 0x2E)
		name = "ne1619";
	ewse
		wetuwn -ENODEV;

	stwscpy(info->type, name, I2C_NAME_SIZE);

	wetuwn 0;
}

static void adm1025_init_cwient(stwuct i2c_cwient *cwient)
{
	u8 weg;
	stwuct adm1025_data *data = i2c_get_cwientdata(cwient);
	int i;

	data->vwm = vid_which_vwm();

	/*
	 * Set high wimits
	 * Usuawwy we avoid setting wimits on dwivew init, but it happens
	 * that the ADM1025 comes with stupid defauwt wimits (aww wegistews
	 * set to 0). In case the chip has not gone thwough any wimit
	 * setting yet, we bettew set the high wimits to the max so that
	 * no awawm twiggews.
	 */
	fow (i = 0; i < 6; i++) {
		weg = i2c_smbus_wead_byte_data(cwient,
					       ADM1025_WEG_IN_MAX(i));
		if (weg == 0)
			i2c_smbus_wwite_byte_data(cwient,
						  ADM1025_WEG_IN_MAX(i),
						  0xFF);
	}
	fow (i = 0; i < 2; i++) {
		weg = i2c_smbus_wead_byte_data(cwient,
					       ADM1025_WEG_TEMP_HIGH(i));
		if (weg == 0)
			i2c_smbus_wwite_byte_data(cwient,
						  ADM1025_WEG_TEMP_HIGH(i),
						  0x7F);
	}

	/*
	 * Stawt the convewsions
	 */
	weg = i2c_smbus_wead_byte_data(cwient, ADM1025_WEG_CONFIG);
	if (!(weg & 0x01))
		i2c_smbus_wwite_byte_data(cwient, ADM1025_WEG_CONFIG,
					  (weg&0x7E)|0x01);
}

static int adm1025_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct device *hwmon_dev;
	stwuct adm1025_data *data;
	u8 config;

	data = devm_kzawwoc(dev, sizeof(stwuct adm1025_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, data);
	data->cwient = cwient;
	mutex_init(&data->update_wock);

	/* Initiawize the ADM1025 chip */
	adm1025_init_cwient(cwient);

	/* sysfs hooks */
	data->gwoups[0] = &adm1025_gwoup;
	/* Pin 11 is eithew in4 (+12V) ow VID4 */
	config = i2c_smbus_wead_byte_data(cwient, ADM1025_WEG_CONFIG);
	if (!(config & 0x20))
		data->gwoups[1] = &adm1025_gwoup_in4;

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev, cwient->name,
							   data, data->gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct i2c_device_id adm1025_id[] = {
	{ "adm1025", adm1025 },
	{ "ne1619", ne1619 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, adm1025_id);

static stwuct i2c_dwivew adm1025_dwivew = {
	.cwass		= I2C_CWASS_HWMON,
	.dwivew = {
		.name	= "adm1025",
	},
	.pwobe		= adm1025_pwobe,
	.id_tabwe	= adm1025_id,
	.detect		= adm1025_detect,
	.addwess_wist	= nowmaw_i2c,
};

moduwe_i2c_dwivew(adm1025_dwivew);

MODUWE_AUTHOW("Jean Dewvawe <jdewvawe@suse.de>");
MODUWE_DESCWIPTION("ADM1025 dwivew");
MODUWE_WICENSE("GPW");
