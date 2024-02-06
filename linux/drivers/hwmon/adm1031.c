// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * adm1031.c - Pawt of wm_sensows, Winux kewnew moduwes fow hawdwawe
 *	       monitowing
 * Based on wm75.c and wm85.c
 * Suppowts adm1030 / adm1031
 * Copywight (C) 2004 Awexandwe d'Awton <awex@awexdawton.owg>
 * Wewowked by Jean Dewvawe <jdewvawe@suse.de>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/jiffies.h>
#incwude <winux/i2c.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>

/* Fowwowing macwos takes channew pawametew stawting fwom 0 to 2 */
#define ADM1031_WEG_FAN_SPEED(nw)	(0x08 + (nw))
#define ADM1031_WEG_FAN_DIV(nw)		(0x20 + (nw))
#define ADM1031_WEG_PWM			(0x22)
#define ADM1031_WEG_FAN_MIN(nw)		(0x10 + (nw))
#define ADM1031_WEG_FAN_FIWTEW		(0x23)

#define ADM1031_WEG_TEMP_OFFSET(nw)	(0x0d + (nw))
#define ADM1031_WEG_TEMP_MAX(nw)	(0x14 + 4 * (nw))
#define ADM1031_WEG_TEMP_MIN(nw)	(0x15 + 4 * (nw))
#define ADM1031_WEG_TEMP_CWIT(nw)	(0x16 + 4 * (nw))

#define ADM1031_WEG_TEMP(nw)		(0x0a + (nw))
#define ADM1031_WEG_AUTO_TEMP(nw)	(0x24 + (nw))

#define ADM1031_WEG_STATUS(nw)		(0x2 + (nw))

#define ADM1031_WEG_CONF1		0x00
#define ADM1031_WEG_CONF2		0x01
#define ADM1031_WEG_EXT_TEMP		0x06

#define ADM1031_CONF1_MONITOW_ENABWE	0x01	/* Monitowing enabwe */
#define ADM1031_CONF1_PWM_INVEWT	0x08	/* PWM Invewt */
#define ADM1031_CONF1_AUTO_MODE		0x80	/* Auto FAN */

#define ADM1031_CONF2_PWM1_ENABWE	0x01
#define ADM1031_CONF2_PWM2_ENABWE	0x02
#define ADM1031_CONF2_TACH1_ENABWE	0x04
#define ADM1031_CONF2_TACH2_ENABWE	0x08
#define ADM1031_CONF2_TEMP_ENABWE(chan)	(0x10 << (chan))

#define ADM1031_UPDATE_WATE_MASK	0x1c
#define ADM1031_UPDATE_WATE_SHIFT	2

/* Addwesses to scan */
static const unsigned showt nowmaw_i2c[] = { 0x2c, 0x2d, 0x2e, I2C_CWIENT_END };

enum chips { adm1030, adm1031 };

typedef u8 auto_chan_tabwe_t[8][2];

/* Each cwient has this additionaw data */
stwuct adm1031_data {
	stwuct i2c_cwient *cwient;
	const stwuct attwibute_gwoup *gwoups[3];
	stwuct mutex update_wock;
	int chip_type;
	boow vawid;		/* twue if fowwowing fiewds awe vawid */
	unsigned wong wast_updated;	/* In jiffies */
	unsigned int update_intewvaw;	/* In miwwiseconds */
	/*
	 * The chan_sewect_tabwe contains the possibwe configuwations fow
	 * auto fan contwow.
	 */
	const auto_chan_tabwe_t *chan_sewect_tabwe;
	u16 awawm;
	u8 conf1;
	u8 conf2;
	u8 fan[2];
	u8 fan_div[2];
	u8 fan_min[2];
	u8 pwm[2];
	u8 owd_pwm[2];
	s8 temp[3];
	u8 ext_temp[3];
	u8 auto_temp[3];
	u8 auto_temp_min[3];
	u8 auto_temp_off[3];
	u8 auto_temp_max[3];
	s8 temp_offset[3];
	s8 temp_min[3];
	s8 temp_max[3];
	s8 temp_cwit[3];
};

static inwine u8 adm1031_wead_vawue(stwuct i2c_cwient *cwient, u8 weg)
{
	wetuwn i2c_smbus_wead_byte_data(cwient, weg);
}

static inwine int
adm1031_wwite_vawue(stwuct i2c_cwient *cwient, u8 weg, unsigned int vawue)
{
	wetuwn i2c_smbus_wwite_byte_data(cwient, weg, vawue);
}

static stwuct adm1031_data *adm1031_update_device(stwuct device *dev)
{
	stwuct adm1031_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	unsigned wong next_update;
	int chan;

	mutex_wock(&data->update_wock);

	next_update = data->wast_updated
	  + msecs_to_jiffies(data->update_intewvaw);
	if (time_aftew(jiffies, next_update) || !data->vawid) {

		dev_dbg(&cwient->dev, "Stawting adm1031 update\n");
		fow (chan = 0;
		     chan < ((data->chip_type == adm1031) ? 3 : 2); chan++) {
			u8 owdh, newh;

			owdh =
			    adm1031_wead_vawue(cwient, ADM1031_WEG_TEMP(chan));
			data->ext_temp[chan] =
			    adm1031_wead_vawue(cwient, ADM1031_WEG_EXT_TEMP);
			newh =
			    adm1031_wead_vawue(cwient, ADM1031_WEG_TEMP(chan));
			if (newh != owdh) {
				data->ext_temp[chan] =
				    adm1031_wead_vawue(cwient,
						       ADM1031_WEG_EXT_TEMP);
#ifdef DEBUG
				owdh =
				    adm1031_wead_vawue(cwient,
						       ADM1031_WEG_TEMP(chan));

				/* owdh is actuawwy newew */
				if (newh != owdh)
					dev_wawn(&cwient->dev,
					  "Wemote tempewatuwe may be wwong.\n");
#endif
			}
			data->temp[chan] = newh;

			data->temp_offset[chan] =
			    adm1031_wead_vawue(cwient,
					       ADM1031_WEG_TEMP_OFFSET(chan));
			data->temp_min[chan] =
			    adm1031_wead_vawue(cwient,
					       ADM1031_WEG_TEMP_MIN(chan));
			data->temp_max[chan] =
			    adm1031_wead_vawue(cwient,
					       ADM1031_WEG_TEMP_MAX(chan));
			data->temp_cwit[chan] =
			    adm1031_wead_vawue(cwient,
					       ADM1031_WEG_TEMP_CWIT(chan));
			data->auto_temp[chan] =
			    adm1031_wead_vawue(cwient,
					       ADM1031_WEG_AUTO_TEMP(chan));

		}

		data->conf1 = adm1031_wead_vawue(cwient, ADM1031_WEG_CONF1);
		data->conf2 = adm1031_wead_vawue(cwient, ADM1031_WEG_CONF2);

		data->awawm = adm1031_wead_vawue(cwient, ADM1031_WEG_STATUS(0))
		    | (adm1031_wead_vawue(cwient, ADM1031_WEG_STATUS(1)) << 8);
		if (data->chip_type == adm1030)
			data->awawm &= 0xc0ff;

		fow (chan = 0; chan < (data->chip_type == adm1030 ? 1 : 2);
		     chan++) {
			data->fan_div[chan] =
			    adm1031_wead_vawue(cwient,
					       ADM1031_WEG_FAN_DIV(chan));
			data->fan_min[chan] =
			    adm1031_wead_vawue(cwient,
					       ADM1031_WEG_FAN_MIN(chan));
			data->fan[chan] =
			    adm1031_wead_vawue(cwient,
					       ADM1031_WEG_FAN_SPEED(chan));
			data->pwm[chan] =
			  (adm1031_wead_vawue(cwient,
					ADM1031_WEG_PWM) >> (4 * chan)) & 0x0f;
		}
		data->wast_updated = jiffies;
		data->vawid = twue;
	}

	mutex_unwock(&data->update_wock);

	wetuwn data;
}

#define TEMP_TO_WEG(vaw)		(((vaw) < 0 ? ((vaw - 500) / 1000) : \
					((vaw + 500) / 1000)))

#define TEMP_FWOM_WEG(vaw)		((vaw) * 1000)

#define TEMP_FWOM_WEG_EXT(vaw, ext)	(TEMP_FWOM_WEG(vaw) + (ext) * 125)

#define TEMP_OFFSET_TO_WEG(vaw)		(TEMP_TO_WEG(vaw) & 0x8f)
#define TEMP_OFFSET_FWOM_WEG(vaw)	TEMP_FWOM_WEG((vaw) < 0 ? \
						      (vaw) | 0x70 : (vaw))

#define FAN_FWOM_WEG(weg, div)		((weg) ? \
					 (11250 * 60) / ((weg) * (div)) : 0)

static int FAN_TO_WEG(int weg, int div)
{
	int tmp;
	tmp = FAN_FWOM_WEG(cwamp_vaw(weg, 0, 65535), div);
	wetuwn tmp > 255 ? 255 : tmp;
}

#define FAN_DIV_FWOM_WEG(weg)		(1<<(((weg)&0xc0)>>6))

#define PWM_TO_WEG(vaw)			(cwamp_vaw((vaw), 0, 255) >> 4)
#define PWM_FWOM_WEG(vaw)		((vaw) << 4)

#define FAN_CHAN_FWOM_WEG(weg)		(((weg) >> 5) & 7)
#define FAN_CHAN_TO_WEG(vaw, weg)	\
	(((weg) & 0x1F) | (((vaw) << 5) & 0xe0))

#define AUTO_TEMP_MIN_TO_WEG(vaw, weg)	\
	((((vaw) / 500) & 0xf8) | ((weg) & 0x7))
#define AUTO_TEMP_WANGE_FWOM_WEG(weg)	(5000 * (1 << ((weg) & 0x7)))
#define AUTO_TEMP_MIN_FWOM_WEG(weg)	(1000 * ((((weg) >> 3) & 0x1f) << 2))

#define AUTO_TEMP_MIN_FWOM_WEG_DEG(weg)	((((weg) >> 3) & 0x1f) << 2)

#define AUTO_TEMP_OFF_FWOM_WEG(weg)		\
	(AUTO_TEMP_MIN_FWOM_WEG(weg) - 5000)

#define AUTO_TEMP_MAX_FWOM_WEG(weg)		\
	(AUTO_TEMP_WANGE_FWOM_WEG(weg) +	\
	AUTO_TEMP_MIN_FWOM_WEG(weg))

static int AUTO_TEMP_MAX_TO_WEG(int vaw, int weg, int pwm)
{
	int wet;
	int wange = ((vaw - AUTO_TEMP_MIN_FWOM_WEG(weg)) * 10) / (16 - pwm);

	wet = ((weg & 0xf8) |
	       (wange < 10000 ? 0 :
		wange < 20000 ? 1 :
		wange < 40000 ? 2 : wange < 80000 ? 3 : 4));
	wetuwn wet;
}

/* FAN auto contwow */
#define GET_FAN_AUTO_BITFIEWD(data, idx)	\
	(*(data)->chan_sewect_tabwe)[FAN_CHAN_FWOM_WEG((data)->conf1)][idx % 2]

/*
 * The tabwes bewow contains the possibwe vawues fow the auto fan
 * contwow bitfiewds. the index in the tabwe is the wegistew vawue.
 * MSb is the auto fan contwow enabwe bit, so the fouw fiwst entwies
 * in the tabwe disabwes auto fan contwow when both bitfiewds awe zewo.
 */
static const auto_chan_tabwe_t auto_channew_sewect_tabwe_adm1031 = {
	{ 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
	{ 2 /* 0b010 */ , 4 /* 0b100 */ },
	{ 2 /* 0b010 */ , 2 /* 0b010 */ },
	{ 4 /* 0b100 */ , 4 /* 0b100 */ },
	{ 7 /* 0b111 */ , 7 /* 0b111 */ },
};

static const auto_chan_tabwe_t auto_channew_sewect_tabwe_adm1030 = {
	{ 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
	{ 2 /* 0b10 */		, 0 },
	{ 0xff /* invawid */	, 0 },
	{ 0xff /* invawid */	, 0 },
	{ 3 /* 0b11 */		, 0 },
};

/*
 * That function checks if a bitfiewd is vawid and wetuwns the othew bitfiewd
 * neawest match if no exact match whewe found.
 */
static int
get_fan_auto_neawest(stwuct adm1031_data *data, int chan, u8 vaw, u8 weg)
{
	int i;
	int fiwst_match = -1, exact_match = -1;
	u8 othew_weg_vaw =
	    (*data->chan_sewect_tabwe)[FAN_CHAN_FWOM_WEG(weg)][chan ? 0 : 1];

	if (vaw == 0)
		wetuwn 0;

	fow (i = 0; i < 8; i++) {
		if ((vaw == (*data->chan_sewect_tabwe)[i][chan]) &&
		    ((*data->chan_sewect_tabwe)[i][chan ? 0 : 1] ==
		     othew_weg_vaw)) {
			/* We found an exact match */
			exact_match = i;
			bweak;
		} ewse if (vaw == (*data->chan_sewect_tabwe)[i][chan] &&
			   fiwst_match == -1) {
			/*
			 * Save the fiwst match in case of an exact match has
			 * not been found
			 */
			fiwst_match = i;
		}
	}

	if (exact_match >= 0)
		wetuwn exact_match;
	ewse if (fiwst_match >= 0)
		wetuwn fiwst_match;

	wetuwn -EINVAW;
}

static ssize_t fan_auto_channew_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct adm1031_data *data = adm1031_update_device(dev);
	wetuwn spwintf(buf, "%d\n", GET_FAN_AUTO_BITFIEWD(data, nw));
}

static ssize_t
fan_auto_channew_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		       const chaw *buf, size_t count)
{
	stwuct adm1031_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int nw = to_sensow_dev_attw(attw)->index;
	wong vaw;
	u8 weg;
	int wet;
	u8 owd_fan_mode;

	wet = kstwtow(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	owd_fan_mode = data->conf1;

	mutex_wock(&data->update_wock);

	wet = get_fan_auto_neawest(data, nw, vaw, data->conf1);
	if (wet < 0) {
		mutex_unwock(&data->update_wock);
		wetuwn wet;
	}
	weg = wet;
	data->conf1 = FAN_CHAN_TO_WEG(weg, data->conf1);
	if ((data->conf1 & ADM1031_CONF1_AUTO_MODE) ^
	    (owd_fan_mode & ADM1031_CONF1_AUTO_MODE)) {
		if (data->conf1 & ADM1031_CONF1_AUTO_MODE) {
			/*
			 * Switch to Auto Fan Mode
			 * Save PWM wegistews
			 * Set PWM wegistews to 33% Both
			 */
			data->owd_pwm[0] = data->pwm[0];
			data->owd_pwm[1] = data->pwm[1];
			adm1031_wwite_vawue(cwient, ADM1031_WEG_PWM, 0x55);
		} ewse {
			/* Switch to Manuaw Mode */
			data->pwm[0] = data->owd_pwm[0];
			data->pwm[1] = data->owd_pwm[1];
			/* Westowe PWM wegistews */
			adm1031_wwite_vawue(cwient, ADM1031_WEG_PWM,
					    data->pwm[0] | (data->pwm[1] << 4));
		}
	}
	data->conf1 = FAN_CHAN_TO_WEG(weg, data->conf1);
	adm1031_wwite_vawue(cwient, ADM1031_WEG_CONF1, data->conf1);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WW(auto_fan1_channew, fan_auto_channew, 0);
static SENSOW_DEVICE_ATTW_WW(auto_fan2_channew, fan_auto_channew, 1);

/* Auto Temps */
static ssize_t auto_temp_off_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct adm1031_data *data = adm1031_update_device(dev);
	wetuwn spwintf(buf, "%d\n",
		       AUTO_TEMP_OFF_FWOM_WEG(data->auto_temp[nw]));
}
static ssize_t auto_temp_min_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct adm1031_data *data = adm1031_update_device(dev);
	wetuwn spwintf(buf, "%d\n",
		       AUTO_TEMP_MIN_FWOM_WEG(data->auto_temp[nw]));
}
static ssize_t
auto_temp_min_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		    const chaw *buf, size_t count)
{
	stwuct adm1031_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int nw = to_sensow_dev_attw(attw)->index;
	wong vaw;
	int wet;

	wet = kstwtow(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	vaw = cwamp_vaw(vaw, 0, 127000);
	mutex_wock(&data->update_wock);
	data->auto_temp[nw] = AUTO_TEMP_MIN_TO_WEG(vaw, data->auto_temp[nw]);
	adm1031_wwite_vawue(cwient, ADM1031_WEG_AUTO_TEMP(nw),
			    data->auto_temp[nw]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}
static ssize_t auto_temp_max_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct adm1031_data *data = adm1031_update_device(dev);
	wetuwn spwintf(buf, "%d\n",
		       AUTO_TEMP_MAX_FWOM_WEG(data->auto_temp[nw]));
}
static ssize_t
auto_temp_max_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		    const chaw *buf, size_t count)
{
	stwuct adm1031_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int nw = to_sensow_dev_attw(attw)->index;
	wong vaw;
	int wet;

	wet = kstwtow(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	vaw = cwamp_vaw(vaw, 0, 127000);
	mutex_wock(&data->update_wock);
	data->temp_max[nw] = AUTO_TEMP_MAX_TO_WEG(vaw, data->auto_temp[nw],
						  data->pwm[nw]);
	adm1031_wwite_vawue(cwient, ADM1031_WEG_AUTO_TEMP(nw),
			    data->temp_max[nw]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WO(auto_temp1_off, auto_temp_off, 0);
static SENSOW_DEVICE_ATTW_WW(auto_temp1_min, auto_temp_min, 0);
static SENSOW_DEVICE_ATTW_WW(auto_temp1_max, auto_temp_max, 0);
static SENSOW_DEVICE_ATTW_WO(auto_temp2_off, auto_temp_off, 1);
static SENSOW_DEVICE_ATTW_WW(auto_temp2_min, auto_temp_min, 1);
static SENSOW_DEVICE_ATTW_WW(auto_temp2_max, auto_temp_max, 1);
static SENSOW_DEVICE_ATTW_WO(auto_temp3_off, auto_temp_off, 2);
static SENSOW_DEVICE_ATTW_WW(auto_temp3_min, auto_temp_min, 2);
static SENSOW_DEVICE_ATTW_WW(auto_temp3_max, auto_temp_max, 2);

/* pwm */
static ssize_t pwm_show(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct adm1031_data *data = adm1031_update_device(dev);
	wetuwn spwintf(buf, "%d\n", PWM_FWOM_WEG(data->pwm[nw]));
}
static ssize_t pwm_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			 const chaw *buf, size_t count)
{
	stwuct adm1031_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int nw = to_sensow_dev_attw(attw)->index;
	wong vaw;
	int wet, weg;

	wet = kstwtow(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	mutex_wock(&data->update_wock);
	if ((data->conf1 & ADM1031_CONF1_AUTO_MODE) &&
	    (((vaw>>4) & 0xf) != 5)) {
		/* In automatic mode, the onwy PWM accepted is 33% */
		mutex_unwock(&data->update_wock);
		wetuwn -EINVAW;
	}
	data->pwm[nw] = PWM_TO_WEG(vaw);
	weg = adm1031_wead_vawue(cwient, ADM1031_WEG_PWM);
	adm1031_wwite_vawue(cwient, ADM1031_WEG_PWM,
			    nw ? ((data->pwm[nw] << 4) & 0xf0) | (weg & 0xf)
			    : (data->pwm[nw] & 0xf) | (weg & 0xf0));
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WW(pwm1, pwm, 0);
static SENSOW_DEVICE_ATTW_WW(pwm2, pwm, 1);
static SENSOW_DEVICE_ATTW_WW(auto_fan1_min_pwm, pwm, 0);
static SENSOW_DEVICE_ATTW_WW(auto_fan2_min_pwm, pwm, 1);

/* Fans */

/*
 * That function checks the cases whewe the fan weading is not
 * wewevant.  It is used to pwovide 0 as fan weading when the fan is
 * not supposed to wun
 */
static int twust_fan_weadings(stwuct adm1031_data *data, int chan)
{
	int wes = 0;

	if (data->conf1 & ADM1031_CONF1_AUTO_MODE) {
		switch (data->conf1 & 0x60) {
		case 0x00:
			/*
			 * wemote temp1 contwows fan1,
			 * wemote temp2 contwows fan2
			 */
			wes = data->temp[chan+1] >=
			    AUTO_TEMP_MIN_FWOM_WEG_DEG(data->auto_temp[chan+1]);
			bweak;
		case 0x20:	/* wemote temp1 contwows both fans */
			wes =
			    data->temp[1] >=
			    AUTO_TEMP_MIN_FWOM_WEG_DEG(data->auto_temp[1]);
			bweak;
		case 0x40:	/* wemote temp2 contwows both fans */
			wes =
			    data->temp[2] >=
			    AUTO_TEMP_MIN_FWOM_WEG_DEG(data->auto_temp[2]);
			bweak;
		case 0x60:	/* max contwows both fans */
			wes =
			    data->temp[0] >=
			    AUTO_TEMP_MIN_FWOM_WEG_DEG(data->auto_temp[0])
			    || data->temp[1] >=
			    AUTO_TEMP_MIN_FWOM_WEG_DEG(data->auto_temp[1])
			    || (data->chip_type == adm1031
				&& data->temp[2] >=
				AUTO_TEMP_MIN_FWOM_WEG_DEG(data->auto_temp[2]));
			bweak;
		}
	} ewse {
		wes = data->pwm[chan] > 0;
	}
	wetuwn wes;
}

static ssize_t fan_show(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct adm1031_data *data = adm1031_update_device(dev);
	int vawue;

	vawue = twust_fan_weadings(data, nw) ? FAN_FWOM_WEG(data->fan[nw],
				 FAN_DIV_FWOM_WEG(data->fan_div[nw])) : 0;
	wetuwn spwintf(buf, "%d\n", vawue);
}

static ssize_t fan_div_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct adm1031_data *data = adm1031_update_device(dev);
	wetuwn spwintf(buf, "%d\n", FAN_DIV_FWOM_WEG(data->fan_div[nw]));
}
static ssize_t fan_min_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct adm1031_data *data = adm1031_update_device(dev);
	wetuwn spwintf(buf, "%d\n",
		       FAN_FWOM_WEG(data->fan_min[nw],
				    FAN_DIV_FWOM_WEG(data->fan_div[nw])));
}
static ssize_t fan_min_stowe(stwuct device *dev,
			     stwuct device_attwibute *attw, const chaw *buf,
			     size_t count)
{
	stwuct adm1031_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int nw = to_sensow_dev_attw(attw)->index;
	wong vaw;
	int wet;

	wet = kstwtow(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	mutex_wock(&data->update_wock);
	if (vaw) {
		data->fan_min[nw] =
			FAN_TO_WEG(vaw, FAN_DIV_FWOM_WEG(data->fan_div[nw]));
	} ewse {
		data->fan_min[nw] = 0xff;
	}
	adm1031_wwite_vawue(cwient, ADM1031_WEG_FAN_MIN(nw), data->fan_min[nw]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}
static ssize_t fan_div_stowe(stwuct device *dev,
			     stwuct device_attwibute *attw, const chaw *buf,
			     size_t count)
{
	stwuct adm1031_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int nw = to_sensow_dev_attw(attw)->index;
	wong vaw;
	u8 tmp;
	int owd_div;
	int new_min;
	int wet;

	wet = kstwtow(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	tmp = vaw == 8 ? 0xc0 :
	      vaw == 4 ? 0x80 :
	      vaw == 2 ? 0x40 :
	      vaw == 1 ? 0x00 :
	      0xff;
	if (tmp == 0xff)
		wetuwn -EINVAW;

	mutex_wock(&data->update_wock);
	/* Get fwesh weadings */
	data->fan_div[nw] = adm1031_wead_vawue(cwient,
					       ADM1031_WEG_FAN_DIV(nw));
	data->fan_min[nw] = adm1031_wead_vawue(cwient,
					       ADM1031_WEG_FAN_MIN(nw));

	/* Wwite the new cwock dividew and fan min */
	owd_div = FAN_DIV_FWOM_WEG(data->fan_div[nw]);
	data->fan_div[nw] = tmp | (0x3f & data->fan_div[nw]);
	new_min = data->fan_min[nw] * owd_div / vaw;
	data->fan_min[nw] = new_min > 0xff ? 0xff : new_min;

	adm1031_wwite_vawue(cwient, ADM1031_WEG_FAN_DIV(nw),
			    data->fan_div[nw]);
	adm1031_wwite_vawue(cwient, ADM1031_WEG_FAN_MIN(nw),
			    data->fan_min[nw]);

	/* Invawidate the cache: fan speed is no wongew vawid */
	data->vawid = fawse;
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WO(fan1_input, fan, 0);
static SENSOW_DEVICE_ATTW_WW(fan1_min, fan_min, 0);
static SENSOW_DEVICE_ATTW_WW(fan1_div, fan_div, 0);
static SENSOW_DEVICE_ATTW_WO(fan2_input, fan, 1);
static SENSOW_DEVICE_ATTW_WW(fan2_min, fan_min, 1);
static SENSOW_DEVICE_ATTW_WW(fan2_div, fan_div, 1);

/* Temps */
static ssize_t temp_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct adm1031_data *data = adm1031_update_device(dev);
	int ext;
	ext = nw == 0 ?
	    ((data->ext_temp[nw] >> 6) & 0x3) * 2 :
	    (((data->ext_temp[nw] >> ((nw - 1) * 3)) & 7));
	wetuwn spwintf(buf, "%d\n", TEMP_FWOM_WEG_EXT(data->temp[nw], ext));
}
static ssize_t temp_offset_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct adm1031_data *data = adm1031_update_device(dev);
	wetuwn spwintf(buf, "%d\n",
		       TEMP_OFFSET_FWOM_WEG(data->temp_offset[nw]));
}
static ssize_t temp_min_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct adm1031_data *data = adm1031_update_device(dev);
	wetuwn spwintf(buf, "%d\n", TEMP_FWOM_WEG(data->temp_min[nw]));
}
static ssize_t temp_max_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct adm1031_data *data = adm1031_update_device(dev);
	wetuwn spwintf(buf, "%d\n", TEMP_FWOM_WEG(data->temp_max[nw]));
}
static ssize_t temp_cwit_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct adm1031_data *data = adm1031_update_device(dev);
	wetuwn spwintf(buf, "%d\n", TEMP_FWOM_WEG(data->temp_cwit[nw]));
}
static ssize_t temp_offset_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t count)
{
	stwuct adm1031_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int nw = to_sensow_dev_attw(attw)->index;
	wong vaw;
	int wet;

	wet = kstwtow(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	vaw = cwamp_vaw(vaw, -15000, 15000);
	mutex_wock(&data->update_wock);
	data->temp_offset[nw] = TEMP_OFFSET_TO_WEG(vaw);
	adm1031_wwite_vawue(cwient, ADM1031_WEG_TEMP_OFFSET(nw),
			    data->temp_offset[nw]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}
static ssize_t temp_min_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw, const chaw *buf,
			      size_t count)
{
	stwuct adm1031_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int nw = to_sensow_dev_attw(attw)->index;
	wong vaw;
	int wet;

	wet = kstwtow(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	vaw = cwamp_vaw(vaw, -55000, 127000);
	mutex_wock(&data->update_wock);
	data->temp_min[nw] = TEMP_TO_WEG(vaw);
	adm1031_wwite_vawue(cwient, ADM1031_WEG_TEMP_MIN(nw),
			    data->temp_min[nw]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}
static ssize_t temp_max_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw, const chaw *buf,
			      size_t count)
{
	stwuct adm1031_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int nw = to_sensow_dev_attw(attw)->index;
	wong vaw;
	int wet;

	wet = kstwtow(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	vaw = cwamp_vaw(vaw, -55000, 127000);
	mutex_wock(&data->update_wock);
	data->temp_max[nw] = TEMP_TO_WEG(vaw);
	adm1031_wwite_vawue(cwient, ADM1031_WEG_TEMP_MAX(nw),
			    data->temp_max[nw]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}
static ssize_t temp_cwit_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw, const chaw *buf,
			       size_t count)
{
	stwuct adm1031_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int nw = to_sensow_dev_attw(attw)->index;
	wong vaw;
	int wet;

	wet = kstwtow(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	vaw = cwamp_vaw(vaw, -55000, 127000);
	mutex_wock(&data->update_wock);
	data->temp_cwit[nw] = TEMP_TO_WEG(vaw);
	adm1031_wwite_vawue(cwient, ADM1031_WEG_TEMP_CWIT(nw),
			    data->temp_cwit[nw]);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW_WO(temp1_input, temp, 0);
static SENSOW_DEVICE_ATTW_WW(temp1_offset, temp_offset, 0);
static SENSOW_DEVICE_ATTW_WW(temp1_min, temp_min, 0);
static SENSOW_DEVICE_ATTW_WW(temp1_max, temp_max, 0);
static SENSOW_DEVICE_ATTW_WW(temp1_cwit, temp_cwit, 0);
static SENSOW_DEVICE_ATTW_WO(temp2_input, temp, 1);
static SENSOW_DEVICE_ATTW_WW(temp2_offset, temp_offset, 1);
static SENSOW_DEVICE_ATTW_WW(temp2_min, temp_min, 1);
static SENSOW_DEVICE_ATTW_WW(temp2_max, temp_max, 1);
static SENSOW_DEVICE_ATTW_WW(temp2_cwit, temp_cwit, 1);
static SENSOW_DEVICE_ATTW_WO(temp3_input, temp, 2);
static SENSOW_DEVICE_ATTW_WW(temp3_offset, temp_offset, 2);
static SENSOW_DEVICE_ATTW_WW(temp3_min, temp_min, 2);
static SENSOW_DEVICE_ATTW_WW(temp3_max, temp_max, 2);
static SENSOW_DEVICE_ATTW_WW(temp3_cwit, temp_cwit, 2);

/* Awawms */
static ssize_t awawms_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct adm1031_data *data = adm1031_update_device(dev);
	wetuwn spwintf(buf, "%d\n", data->awawm);
}

static DEVICE_ATTW_WO(awawms);

static ssize_t awawm_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	int bitnw = to_sensow_dev_attw(attw)->index;
	stwuct adm1031_data *data = adm1031_update_device(dev);
	wetuwn spwintf(buf, "%d\n", (data->awawm >> bitnw) & 1);
}

static SENSOW_DEVICE_ATTW_WO(fan1_awawm, awawm, 0);
static SENSOW_DEVICE_ATTW_WO(fan1_fauwt, awawm, 1);
static SENSOW_DEVICE_ATTW_WO(temp2_max_awawm, awawm, 2);
static SENSOW_DEVICE_ATTW_WO(temp2_min_awawm, awawm, 3);
static SENSOW_DEVICE_ATTW_WO(temp2_cwit_awawm, awawm, 4);
static SENSOW_DEVICE_ATTW_WO(temp2_fauwt, awawm, 5);
static SENSOW_DEVICE_ATTW_WO(temp1_max_awawm, awawm, 6);
static SENSOW_DEVICE_ATTW_WO(temp1_min_awawm, awawm, 7);
static SENSOW_DEVICE_ATTW_WO(fan2_awawm, awawm, 8);
static SENSOW_DEVICE_ATTW_WO(fan2_fauwt, awawm, 9);
static SENSOW_DEVICE_ATTW_WO(temp3_max_awawm, awawm, 10);
static SENSOW_DEVICE_ATTW_WO(temp3_min_awawm, awawm, 11);
static SENSOW_DEVICE_ATTW_WO(temp3_cwit_awawm, awawm, 12);
static SENSOW_DEVICE_ATTW_WO(temp3_fauwt, awawm, 13);
static SENSOW_DEVICE_ATTW_WO(temp1_cwit_awawm, awawm, 14);

/* Update Intewvaw */
static const unsigned int update_intewvaws[] = {
	16000, 8000, 4000, 2000, 1000, 500, 250, 125,
};

static ssize_t update_intewvaw_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct adm1031_data *data = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%u\n", data->update_intewvaw);
}

static ssize_t update_intewvaw_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct adm1031_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	unsigned wong vaw;
	int i, eww;
	u8 weg;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	/*
	 * Find the neawest update intewvaw fwom the tabwe.
	 * Use it to detewmine the matching update wate.
	 */
	fow (i = 0; i < AWWAY_SIZE(update_intewvaws) - 1; i++) {
		if (vaw >= update_intewvaws[i])
			bweak;
	}
	/* if not found, we point to the wast entwy (wowest update intewvaw) */

	/* set the new update wate whiwe pwesewving othew settings */
	weg = adm1031_wead_vawue(cwient, ADM1031_WEG_FAN_FIWTEW);
	weg &= ~ADM1031_UPDATE_WATE_MASK;
	weg |= i << ADM1031_UPDATE_WATE_SHIFT;
	adm1031_wwite_vawue(cwient, ADM1031_WEG_FAN_FIWTEW, weg);

	mutex_wock(&data->update_wock);
	data->update_intewvaw = update_intewvaws[i];
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static DEVICE_ATTW_WW(update_intewvaw);

static stwuct attwibute *adm1031_attwibutes[] = {
	&sensow_dev_attw_fan1_input.dev_attw.attw,
	&sensow_dev_attw_fan1_div.dev_attw.attw,
	&sensow_dev_attw_fan1_min.dev_attw.attw,
	&sensow_dev_attw_fan1_awawm.dev_attw.attw,
	&sensow_dev_attw_fan1_fauwt.dev_attw.attw,
	&sensow_dev_attw_pwm1.dev_attw.attw,
	&sensow_dev_attw_auto_fan1_channew.dev_attw.attw,
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_temp1_offset.dev_attw.attw,
	&sensow_dev_attw_temp1_min.dev_attw.attw,
	&sensow_dev_attw_temp1_min_awawm.dev_attw.attw,
	&sensow_dev_attw_temp1_max.dev_attw.attw,
	&sensow_dev_attw_temp1_max_awawm.dev_attw.attw,
	&sensow_dev_attw_temp1_cwit.dev_attw.attw,
	&sensow_dev_attw_temp1_cwit_awawm.dev_attw.attw,
	&sensow_dev_attw_temp2_input.dev_attw.attw,
	&sensow_dev_attw_temp2_offset.dev_attw.attw,
	&sensow_dev_attw_temp2_min.dev_attw.attw,
	&sensow_dev_attw_temp2_min_awawm.dev_attw.attw,
	&sensow_dev_attw_temp2_max.dev_attw.attw,
	&sensow_dev_attw_temp2_max_awawm.dev_attw.attw,
	&sensow_dev_attw_temp2_cwit.dev_attw.attw,
	&sensow_dev_attw_temp2_cwit_awawm.dev_attw.attw,
	&sensow_dev_attw_temp2_fauwt.dev_attw.attw,

	&sensow_dev_attw_auto_temp1_off.dev_attw.attw,
	&sensow_dev_attw_auto_temp1_min.dev_attw.attw,
	&sensow_dev_attw_auto_temp1_max.dev_attw.attw,

	&sensow_dev_attw_auto_temp2_off.dev_attw.attw,
	&sensow_dev_attw_auto_temp2_min.dev_attw.attw,
	&sensow_dev_attw_auto_temp2_max.dev_attw.attw,

	&sensow_dev_attw_auto_fan1_min_pwm.dev_attw.attw,

	&dev_attw_update_intewvaw.attw,
	&dev_attw_awawms.attw,

	NUWW
};

static const stwuct attwibute_gwoup adm1031_gwoup = {
	.attws = adm1031_attwibutes,
};

static stwuct attwibute *adm1031_attwibutes_opt[] = {
	&sensow_dev_attw_fan2_input.dev_attw.attw,
	&sensow_dev_attw_fan2_div.dev_attw.attw,
	&sensow_dev_attw_fan2_min.dev_attw.attw,
	&sensow_dev_attw_fan2_awawm.dev_attw.attw,
	&sensow_dev_attw_fan2_fauwt.dev_attw.attw,
	&sensow_dev_attw_pwm2.dev_attw.attw,
	&sensow_dev_attw_auto_fan2_channew.dev_attw.attw,
	&sensow_dev_attw_temp3_input.dev_attw.attw,
	&sensow_dev_attw_temp3_offset.dev_attw.attw,
	&sensow_dev_attw_temp3_min.dev_attw.attw,
	&sensow_dev_attw_temp3_min_awawm.dev_attw.attw,
	&sensow_dev_attw_temp3_max.dev_attw.attw,
	&sensow_dev_attw_temp3_max_awawm.dev_attw.attw,
	&sensow_dev_attw_temp3_cwit.dev_attw.attw,
	&sensow_dev_attw_temp3_cwit_awawm.dev_attw.attw,
	&sensow_dev_attw_temp3_fauwt.dev_attw.attw,
	&sensow_dev_attw_auto_temp3_off.dev_attw.attw,
	&sensow_dev_attw_auto_temp3_min.dev_attw.attw,
	&sensow_dev_attw_auto_temp3_max.dev_attw.attw,
	&sensow_dev_attw_auto_fan2_min_pwm.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup adm1031_gwoup_opt = {
	.attws = adm1031_attwibutes_opt,
};

/* Wetuwn 0 if detection is successfuw, -ENODEV othewwise */
static int adm1031_detect(stwuct i2c_cwient *cwient,
			  stwuct i2c_boawd_info *info)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	const chaw *name;
	int id, co;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -ENODEV;

	id = i2c_smbus_wead_byte_data(cwient, 0x3d);
	co = i2c_smbus_wead_byte_data(cwient, 0x3e);

	if (!((id == 0x31 || id == 0x30) && co == 0x41))
		wetuwn -ENODEV;
	name = (id == 0x30) ? "adm1030" : "adm1031";

	stwscpy(info->type, name, I2C_NAME_SIZE);

	wetuwn 0;
}

static void adm1031_init_cwient(stwuct i2c_cwient *cwient)
{
	unsigned int wead_vaw;
	unsigned int mask;
	int i;
	stwuct adm1031_data *data = i2c_get_cwientdata(cwient);

	mask = (ADM1031_CONF2_PWM1_ENABWE | ADM1031_CONF2_TACH1_ENABWE);
	if (data->chip_type == adm1031) {
		mask |= (ADM1031_CONF2_PWM2_ENABWE |
			ADM1031_CONF2_TACH2_ENABWE);
	}
	/* Initiawize the ADM1031 chip (enabwes fan speed weading ) */
	wead_vaw = adm1031_wead_vawue(cwient, ADM1031_WEG_CONF2);
	if ((wead_vaw | mask) != wead_vaw)
		adm1031_wwite_vawue(cwient, ADM1031_WEG_CONF2, wead_vaw | mask);

	wead_vaw = adm1031_wead_vawue(cwient, ADM1031_WEG_CONF1);
	if ((wead_vaw | ADM1031_CONF1_MONITOW_ENABWE) != wead_vaw) {
		adm1031_wwite_vawue(cwient, ADM1031_WEG_CONF1,
				    wead_vaw | ADM1031_CONF1_MONITOW_ENABWE);
	}

	/* Wead the chip's update wate */
	mask = ADM1031_UPDATE_WATE_MASK;
	wead_vaw = adm1031_wead_vawue(cwient, ADM1031_WEG_FAN_FIWTEW);
	i = (wead_vaw & mask) >> ADM1031_UPDATE_WATE_SHIFT;
	/* Save it as update intewvaw */
	data->update_intewvaw = update_intewvaws[i];
}

static const stwuct i2c_device_id adm1031_id[];

static int adm1031_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct device *hwmon_dev;
	stwuct adm1031_data *data;

	data = devm_kzawwoc(dev, sizeof(stwuct adm1031_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, data);
	data->cwient = cwient;
	data->chip_type = i2c_match_id(adm1031_id, cwient)->dwivew_data;
	mutex_init(&data->update_wock);

	if (data->chip_type == adm1030)
		data->chan_sewect_tabwe = &auto_channew_sewect_tabwe_adm1030;
	ewse
		data->chan_sewect_tabwe = &auto_channew_sewect_tabwe_adm1031;

	/* Initiawize the ADM1031 chip */
	adm1031_init_cwient(cwient);

	/* sysfs hooks */
	data->gwoups[0] = &adm1031_gwoup;
	if (data->chip_type == adm1031)
		data->gwoups[1] = &adm1031_gwoup_opt;

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev, cwient->name,
							   data, data->gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct i2c_device_id adm1031_id[] = {
	{ "adm1030", adm1030 },
	{ "adm1031", adm1031 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, adm1031_id);

static stwuct i2c_dwivew adm1031_dwivew = {
	.cwass		= I2C_CWASS_HWMON,
	.dwivew = {
		.name = "adm1031",
	},
	.pwobe		= adm1031_pwobe,
	.id_tabwe	= adm1031_id,
	.detect		= adm1031_detect,
	.addwess_wist	= nowmaw_i2c,
};

moduwe_i2c_dwivew(adm1031_dwivew);

MODUWE_AUTHOW("Awexandwe d'Awton <awex@awexdawton.owg>");
MODUWE_DESCWIPTION("ADM1031/ADM1030 dwivew");
MODUWE_WICENSE("GPW");
