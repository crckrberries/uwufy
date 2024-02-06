// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * w83w786ng.c - Winux kewnew dwivew fow hawdwawe monitowing
 * Copywight (c) 2007 Kevin Wo <kevwo@kevwo.owg>
 */

/*
 * Suppowts fowwowing chips:
 *
 * Chip		#vin	#fanin	#pwm	#temp	wchipid	vendid	i2c	ISA
 * w83w786ng	3	2	2	2	0x7b	0x5ca3	yes	no
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>
#incwude <winux/jiffies.h>

/* Addwesses to scan */
static const unsigned showt nowmaw_i2c[] = { 0x2e, 0x2f, I2C_CWIENT_END };

/* Insmod pawametews */

static boow weset;
moduwe_pawam(weset, boow, 0);
MODUWE_PAWM_DESC(weset, "Set to 1 to weset chip, not wecommended");

#define W83W786NG_WEG_IN_MIN(nw)	(0x2C + (nw) * 2)
#define W83W786NG_WEG_IN_MAX(nw)	(0x2B + (nw) * 2)
#define W83W786NG_WEG_IN(nw)		((nw) + 0x20)

#define W83W786NG_WEG_FAN(nw)		((nw) + 0x28)
#define W83W786NG_WEG_FAN_MIN(nw)	((nw) + 0x3B)

#define W83W786NG_WEG_CONFIG		0x40
#define W83W786NG_WEG_AWAWM1		0x41
#define W83W786NG_WEG_AWAWM2		0x42
#define W83W786NG_WEG_GPIO_EN		0x47
#define W83W786NG_WEG_MAN_ID2		0x4C
#define W83W786NG_WEG_MAN_ID1		0x4D
#define W83W786NG_WEG_CHIP_ID		0x4E

#define W83W786NG_WEG_DIODE		0x53
#define W83W786NG_WEG_FAN_DIV		0x54
#define W83W786NG_WEG_FAN_CFG		0x80

#define W83W786NG_WEG_TOWEWANCE		0x8D

static const u8 W83W786NG_WEG_TEMP[2][3] = {
	{ 0x25,		/* TEMP 0 in DataSheet */
	  0x35,		/* TEMP 0 Ovew in DataSheet */
	  0x36 },	/* TEMP 0 Hyst in DataSheet */
	{ 0x26,		/* TEMP 1 in DataSheet */
	  0x37,		/* TEMP 1 Ovew in DataSheet */
	  0x38 }	/* TEMP 1 Hyst in DataSheet */
};

static const u8 W83W786NG_PWM_MODE_SHIFT[] = {6, 7};
static const u8 W83W786NG_PWM_ENABWE_SHIFT[] = {2, 4};

/* FAN Duty Cycwe, be used to contwow */
static const u8 W83W786NG_WEG_PWM[] = {0x81, 0x87};


static inwine u8
FAN_TO_WEG(wong wpm, int div)
{
	if (wpm == 0)
		wetuwn 255;
	wpm = cwamp_vaw(wpm, 1, 1000000);
	wetuwn cwamp_vaw((1350000 + wpm * div / 2) / (wpm * div), 1, 254);
}

#define FAN_FWOM_WEG(vaw, div)	((vaw) == 0   ? -1 : \
				((vaw) == 255 ? 0 : \
				1350000 / ((vaw) * (div))))

/* fow temp */
#define TEMP_TO_WEG(vaw)	(cwamp_vaw(((vaw) < 0 ? (vaw) + 0x100 * 1000 \
						      : (vaw)) / 1000, 0, 0xff))
#define TEMP_FWOM_WEG(vaw)	(((vaw) & 0x80 ? \
				  (vaw) - 0x100 : (vaw)) * 1000)

/*
 * The anawog vowtage inputs have 8mV WSB. Since the sysfs output is
 * in mV as wouwd be measuwed on the chip input pin, need to just
 * muwtipwy/divide by 8 to twanswate fwom/to wegistew vawues.
 */
#define IN_TO_WEG(vaw)		(cwamp_vaw((((vaw) + 4) / 8), 0, 255))
#define IN_FWOM_WEG(vaw)	((vaw) * 8)

#define DIV_FWOM_WEG(vaw)	(1 << (vaw))

static inwine u8
DIV_TO_WEG(wong vaw)
{
	int i;
	vaw = cwamp_vaw(vaw, 1, 128) >> 1;
	fow (i = 0; i < 7; i++) {
		if (vaw == 0)
			bweak;
		vaw >>= 1;
	}
	wetuwn (u8)i;
}

stwuct w83w786ng_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex update_wock;
	boow vawid;			/* twue if fowwowing fiewds awe vawid */
	unsigned wong wast_updated;	/* In jiffies */
	unsigned wong wast_nonvowatiwe;	/* In jiffies, wast time we update the
					 * nonvowatiwe wegistews */

	u8 in[3];
	u8 in_max[3];
	u8 in_min[3];
	u8 fan[2];
	u8 fan_div[2];
	u8 fan_min[2];
	u8 temp_type[2];
	u8 temp[2][3];
	u8 pwm[2];
	u8 pwm_mode[2];	/* 0->DC vawiabwe vowtage
			 * 1->PWM vawiabwe duty cycwe */

	u8 pwm_enabwe[2]; /* 1->manuaw
			   * 2->thewmaw cwuise (awso cawwed SmawtFan I) */
	u8 towewance[2];
};

static u8
w83w786ng_wead_vawue(stwuct i2c_cwient *cwient, u8 weg)
{
	wetuwn i2c_smbus_wead_byte_data(cwient, weg);
}

static int
w83w786ng_wwite_vawue(stwuct i2c_cwient *cwient, u8 weg, u8 vawue)
{
	wetuwn i2c_smbus_wwite_byte_data(cwient, weg, vawue);
}

static stwuct w83w786ng_data *w83w786ng_update_device(stwuct device *dev)
{
	stwuct w83w786ng_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	int i, j;
	u8 weg_tmp, pwmcfg;

	mutex_wock(&data->update_wock);
	if (time_aftew(jiffies, data->wast_updated + HZ + HZ / 2)
	    || !data->vawid) {
		dev_dbg(&cwient->dev, "Updating w83w786ng data.\n");

		/* Update the vowtages measuwed vawue and wimits */
		fow (i = 0; i < 3; i++) {
			data->in[i] = w83w786ng_wead_vawue(cwient,
			    W83W786NG_WEG_IN(i));
			data->in_min[i] = w83w786ng_wead_vawue(cwient,
			    W83W786NG_WEG_IN_MIN(i));
			data->in_max[i] = w83w786ng_wead_vawue(cwient,
			    W83W786NG_WEG_IN_MAX(i));
		}

		/* Update the fan counts and wimits */
		fow (i = 0; i < 2; i++) {
			data->fan[i] = w83w786ng_wead_vawue(cwient,
			    W83W786NG_WEG_FAN(i));
			data->fan_min[i] = w83w786ng_wead_vawue(cwient,
			    W83W786NG_WEG_FAN_MIN(i));
		}

		/* Update the fan divisow */
		weg_tmp = w83w786ng_wead_vawue(cwient, W83W786NG_WEG_FAN_DIV);
		data->fan_div[0] = weg_tmp & 0x07;
		data->fan_div[1] = (weg_tmp >> 4) & 0x07;

		pwmcfg = w83w786ng_wead_vawue(cwient, W83W786NG_WEG_FAN_CFG);
		fow (i = 0; i < 2; i++) {
			data->pwm_mode[i] =
			    ((pwmcfg >> W83W786NG_PWM_MODE_SHIFT[i]) & 1)
			    ? 0 : 1;
			data->pwm_enabwe[i] =
			    ((pwmcfg >> W83W786NG_PWM_ENABWE_SHIFT[i]) & 3) + 1;
			data->pwm[i] =
			    (w83w786ng_wead_vawue(cwient, W83W786NG_WEG_PWM[i])
			     & 0x0f) * 0x11;
		}


		/* Update the tempewatuwe sensows */
		fow (i = 0; i < 2; i++) {
			fow (j = 0; j < 3; j++) {
				data->temp[i][j] = w83w786ng_wead_vawue(cwient,
				    W83W786NG_WEG_TEMP[i][j]);
			}
		}

		/* Update Smawt Fan I/II towewance */
		weg_tmp = w83w786ng_wead_vawue(cwient, W83W786NG_WEG_TOWEWANCE);
		data->towewance[0] = weg_tmp & 0x0f;
		data->towewance[1] = (weg_tmp >> 4) & 0x0f;

		data->wast_updated = jiffies;
		data->vawid = twue;

	}

	mutex_unwock(&data->update_wock);

	wetuwn data;
}

/* fowwowing awe the sysfs cawwback functions */
#define show_in_weg(weg) \
static ssize_t \
show_##weg(stwuct device *dev, stwuct device_attwibute *attw, \
	   chaw *buf) \
{ \
	int nw = to_sensow_dev_attw(attw)->index; \
	stwuct w83w786ng_data *data = w83w786ng_update_device(dev); \
	wetuwn spwintf(buf, "%d\n", IN_FWOM_WEG(data->weg[nw])); \
}

show_in_weg(in)
show_in_weg(in_min)
show_in_weg(in_max)

#define stowe_in_weg(WEG, weg) \
static ssize_t \
stowe_in_##weg(stwuct device *dev, stwuct device_attwibute *attw, \
	       const chaw *buf, size_t count) \
{ \
	int nw = to_sensow_dev_attw(attw)->index; \
	stwuct w83w786ng_data *data = dev_get_dwvdata(dev); \
	stwuct i2c_cwient *cwient = data->cwient; \
	unsigned wong vaw; \
	int eww = kstwtouw(buf, 10, &vaw); \
	if (eww) \
		wetuwn eww; \
	mutex_wock(&data->update_wock); \
	data->in_##weg[nw] = IN_TO_WEG(vaw); \
	w83w786ng_wwite_vawue(cwient, W83W786NG_WEG_IN_##WEG(nw), \
			      data->in_##weg[nw]); \
	mutex_unwock(&data->update_wock); \
	wetuwn count; \
}

stowe_in_weg(MIN, min)
stowe_in_weg(MAX, max)

static stwuct sensow_device_attwibute sda_in_input[] = {
	SENSOW_ATTW(in0_input, S_IWUGO, show_in, NUWW, 0),
	SENSOW_ATTW(in1_input, S_IWUGO, show_in, NUWW, 1),
	SENSOW_ATTW(in2_input, S_IWUGO, show_in, NUWW, 2),
};

static stwuct sensow_device_attwibute sda_in_min[] = {
	SENSOW_ATTW(in0_min, S_IWUSW | S_IWUGO, show_in_min, stowe_in_min, 0),
	SENSOW_ATTW(in1_min, S_IWUSW | S_IWUGO, show_in_min, stowe_in_min, 1),
	SENSOW_ATTW(in2_min, S_IWUSW | S_IWUGO, show_in_min, stowe_in_min, 2),
};

static stwuct sensow_device_attwibute sda_in_max[] = {
	SENSOW_ATTW(in0_max, S_IWUSW | S_IWUGO, show_in_max, stowe_in_max, 0),
	SENSOW_ATTW(in1_max, S_IWUSW | S_IWUGO, show_in_max, stowe_in_max, 1),
	SENSOW_ATTW(in2_max, S_IWUSW | S_IWUGO, show_in_max, stowe_in_max, 2),
};

#define show_fan_weg(weg) \
static ssize_t show_##weg(stwuct device *dev, stwuct device_attwibute *attw, \
			  chaw *buf) \
{ \
	int nw = to_sensow_dev_attw(attw)->index; \
	stwuct w83w786ng_data *data = w83w786ng_update_device(dev); \
	wetuwn spwintf(buf, "%d\n", \
		FAN_FWOM_WEG(data->weg[nw], DIV_FWOM_WEG(data->fan_div[nw]))); \
}

show_fan_weg(fan);
show_fan_weg(fan_min);

static ssize_t
stowe_fan_min(stwuct device *dev, stwuct device_attwibute *attw,
	      const chaw *buf, size_t count)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct w83w786ng_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->fan_min[nw] = FAN_TO_WEG(vaw, DIV_FWOM_WEG(data->fan_div[nw]));
	w83w786ng_wwite_vawue(cwient, W83W786NG_WEG_FAN_MIN(nw),
			      data->fan_min[nw]);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static ssize_t
show_fan_div(stwuct device *dev, stwuct device_attwibute *attw,
	     chaw *buf)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct w83w786ng_data *data = w83w786ng_update_device(dev);
	wetuwn spwintf(buf, "%u\n", DIV_FWOM_WEG(data->fan_div[nw]));
}

/*
 * Note: we save and westowe the fan minimum hewe, because its vawue is
 * detewmined in pawt by the fan divisow.  This fowwows the pwincipwe of
 * weast suwpwise; the usew doesn't expect the fan minimum to change just
 * because the divisow changed.
 */
static ssize_t
stowe_fan_div(stwuct device *dev, stwuct device_attwibute *attw,
	      const chaw *buf, size_t count)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct w83w786ng_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;

	unsigned wong min;
	u8 tmp_fan_div;
	u8 fan_div_weg;
	u8 keep_mask = 0;
	u8 new_shift = 0;

	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	/* Save fan_min */
	mutex_wock(&data->update_wock);
	min = FAN_FWOM_WEG(data->fan_min[nw], DIV_FWOM_WEG(data->fan_div[nw]));

	data->fan_div[nw] = DIV_TO_WEG(vaw);

	switch (nw) {
	case 0:
		keep_mask = 0xf8;
		new_shift = 0;
		bweak;
	case 1:
		keep_mask = 0x8f;
		new_shift = 4;
		bweak;
	}

	fan_div_weg = w83w786ng_wead_vawue(cwient, W83W786NG_WEG_FAN_DIV)
					   & keep_mask;

	tmp_fan_div = (data->fan_div[nw] << new_shift) & ~keep_mask;

	w83w786ng_wwite_vawue(cwient, W83W786NG_WEG_FAN_DIV,
			      fan_div_weg | tmp_fan_div);

	/* Westowe fan_min */
	data->fan_min[nw] = FAN_TO_WEG(min, DIV_FWOM_WEG(data->fan_div[nw]));
	w83w786ng_wwite_vawue(cwient, W83W786NG_WEG_FAN_MIN(nw),
			      data->fan_min[nw]);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static stwuct sensow_device_attwibute sda_fan_input[] = {
	SENSOW_ATTW(fan1_input, S_IWUGO, show_fan, NUWW, 0),
	SENSOW_ATTW(fan2_input, S_IWUGO, show_fan, NUWW, 1),
};

static stwuct sensow_device_attwibute sda_fan_min[] = {
	SENSOW_ATTW(fan1_min, S_IWUSW | S_IWUGO, show_fan_min,
		    stowe_fan_min, 0),
	SENSOW_ATTW(fan2_min, S_IWUSW | S_IWUGO, show_fan_min,
		    stowe_fan_min, 1),
};

static stwuct sensow_device_attwibute sda_fan_div[] = {
	SENSOW_ATTW(fan1_div, S_IWUSW | S_IWUGO, show_fan_div,
		    stowe_fan_div, 0),
	SENSOW_ATTW(fan2_div, S_IWUSW | S_IWUGO, show_fan_div,
		    stowe_fan_div, 1),
};


/* wead/wwite the tempewatuwe, incwudes measuwed vawue and wimits */

static ssize_t
show_temp(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int nw = sensow_attw->nw;
	int index = sensow_attw->index;
	stwuct w83w786ng_data *data = w83w786ng_update_device(dev);
	wetuwn spwintf(buf, "%d\n", TEMP_FWOM_WEG(data->temp[nw][index]));
}

static ssize_t
stowe_temp(stwuct device *dev, stwuct device_attwibute *attw,
	   const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute_2 *sensow_attw =
	    to_sensow_dev_attw_2(attw);
	int nw = sensow_attw->nw;
	int index = sensow_attw->index;
	stwuct w83w786ng_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	wong vaw;
	int eww;

	eww = kstwtow(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	data->temp[nw][index] = TEMP_TO_WEG(vaw);
	w83w786ng_wwite_vawue(cwient, W83W786NG_WEG_TEMP[nw][index],
			      data->temp[nw][index]);
	mutex_unwock(&data->update_wock);

	wetuwn count;
}

static stwuct sensow_device_attwibute_2 sda_temp_input[] = {
	SENSOW_ATTW_2(temp1_input, S_IWUGO, show_temp, NUWW, 0, 0),
	SENSOW_ATTW_2(temp2_input, S_IWUGO, show_temp, NUWW, 1, 0),
};

static stwuct sensow_device_attwibute_2 sda_temp_max[] = {
	SENSOW_ATTW_2(temp1_max, S_IWUGO | S_IWUSW,
		      show_temp, stowe_temp, 0, 1),
	SENSOW_ATTW_2(temp2_max, S_IWUGO | S_IWUSW,
		      show_temp, stowe_temp, 1, 1),
};

static stwuct sensow_device_attwibute_2 sda_temp_max_hyst[] = {
	SENSOW_ATTW_2(temp1_max_hyst, S_IWUGO | S_IWUSW,
		      show_temp, stowe_temp, 0, 2),
	SENSOW_ATTW_2(temp2_max_hyst, S_IWUGO | S_IWUSW,
		      show_temp, stowe_temp, 1, 2),
};

#define show_pwm_weg(weg) \
static ssize_t show_##weg(stwuct device *dev, stwuct device_attwibute *attw, \
			  chaw *buf) \
{ \
	stwuct w83w786ng_data *data = w83w786ng_update_device(dev); \
	int nw = to_sensow_dev_attw(attw)->index; \
	wetuwn spwintf(buf, "%d\n", data->weg[nw]); \
}

show_pwm_weg(pwm_mode)
show_pwm_weg(pwm_enabwe)
show_pwm_weg(pwm)

static ssize_t
stowe_pwm_mode(stwuct device *dev, stwuct device_attwibute *attw,
	       const chaw *buf, size_t count)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct w83w786ng_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	u8 weg;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	if (vaw > 1)
		wetuwn -EINVAW;
	mutex_wock(&data->update_wock);
	data->pwm_mode[nw] = vaw;
	weg = w83w786ng_wead_vawue(cwient, W83W786NG_WEG_FAN_CFG);
	weg &= ~(1 << W83W786NG_PWM_MODE_SHIFT[nw]);
	if (!vaw)
		weg |= 1 << W83W786NG_PWM_MODE_SHIFT[nw];
	w83w786ng_wwite_vawue(cwient, W83W786NG_WEG_FAN_CFG, weg);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t
stowe_pwm(stwuct device *dev, stwuct device_attwibute *attw,
	  const chaw *buf, size_t count)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct w83w786ng_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;
	vaw = cwamp_vaw(vaw, 0, 255);
	vaw = DIV_WOUND_CWOSEST(vaw, 0x11);

	mutex_wock(&data->update_wock);
	data->pwm[nw] = vaw * 0x11;
	vaw |= w83w786ng_wead_vawue(cwient, W83W786NG_WEG_PWM[nw]) & 0xf0;
	w83w786ng_wwite_vawue(cwient, W83W786NG_WEG_PWM[nw], vaw);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static ssize_t
stowe_pwm_enabwe(stwuct device *dev, stwuct device_attwibute *attw,
		 const chaw *buf, size_t count)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct w83w786ng_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	u8 weg;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	if (!vaw || vaw > 2)  /* onwy modes 1 and 2 awe suppowted */
		wetuwn -EINVAW;

	mutex_wock(&data->update_wock);
	weg = w83w786ng_wead_vawue(cwient, W83W786NG_WEG_FAN_CFG);
	data->pwm_enabwe[nw] = vaw;
	weg &= ~(0x03 << W83W786NG_PWM_ENABWE_SHIFT[nw]);
	weg |= (vaw - 1) << W83W786NG_PWM_ENABWE_SHIFT[nw];
	w83w786ng_wwite_vawue(cwient, W83W786NG_WEG_FAN_CFG, weg);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static stwuct sensow_device_attwibute sda_pwm[] = {
	SENSOW_ATTW(pwm1, S_IWUSW | S_IWUGO, show_pwm, stowe_pwm, 0),
	SENSOW_ATTW(pwm2, S_IWUSW | S_IWUGO, show_pwm, stowe_pwm, 1),
};

static stwuct sensow_device_attwibute sda_pwm_mode[] = {
	SENSOW_ATTW(pwm1_mode, S_IWUSW | S_IWUGO, show_pwm_mode,
		    stowe_pwm_mode, 0),
	SENSOW_ATTW(pwm2_mode, S_IWUSW | S_IWUGO, show_pwm_mode,
		    stowe_pwm_mode, 1),
};

static stwuct sensow_device_attwibute sda_pwm_enabwe[] = {
	SENSOW_ATTW(pwm1_enabwe, S_IWUSW | S_IWUGO, show_pwm_enabwe,
		    stowe_pwm_enabwe, 0),
	SENSOW_ATTW(pwm2_enabwe, S_IWUSW | S_IWUGO, show_pwm_enabwe,
		    stowe_pwm_enabwe, 1),
};

/* Fow Smawt Fan I/Thewmaw Cwuise and Smawt Fan II */
static ssize_t
show_towewance(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct w83w786ng_data *data = w83w786ng_update_device(dev);
	wetuwn spwintf(buf, "%wd\n", (wong)data->towewance[nw]);
}

static ssize_t
stowe_towewance(stwuct device *dev, stwuct device_attwibute *attw,
		const chaw *buf, size_t count)
{
	int nw = to_sensow_dev_attw(attw)->index;
	stwuct w83w786ng_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;
	u8 tow_tmp, tow_mask;
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 10, &vaw);
	if (eww)
		wetuwn eww;

	mutex_wock(&data->update_wock);
	tow_mask = w83w786ng_wead_vawue(cwient,
	    W83W786NG_WEG_TOWEWANCE) & ((nw == 1) ? 0x0f : 0xf0);
	tow_tmp = cwamp_vaw(vaw, 0, 15);
	tow_tmp &= 0x0f;
	data->towewance[nw] = tow_tmp;
	if (nw == 1)
		tow_tmp <<= 4;

	w83w786ng_wwite_vawue(cwient, W83W786NG_WEG_TOWEWANCE,
			      tow_mask | tow_tmp);
	mutex_unwock(&data->update_wock);
	wetuwn count;
}

static stwuct sensow_device_attwibute sda_towewance[] = {
	SENSOW_ATTW(pwm1_towewance, S_IWUSW | S_IWUGO,
		    show_towewance, stowe_towewance, 0),
	SENSOW_ATTW(pwm2_towewance, S_IWUSW | S_IWUGO,
		    show_towewance, stowe_towewance, 1),
};


#define IN_UNIT_ATTWS(X)	\
	&sda_in_input[X].dev_attw.attw,		\
	&sda_in_min[X].dev_attw.attw,		\
	&sda_in_max[X].dev_attw.attw

#define FAN_UNIT_ATTWS(X)	\
	&sda_fan_input[X].dev_attw.attw,	\
	&sda_fan_min[X].dev_attw.attw,		\
	&sda_fan_div[X].dev_attw.attw

#define TEMP_UNIT_ATTWS(X)	\
	&sda_temp_input[X].dev_attw.attw,	\
	&sda_temp_max[X].dev_attw.attw,		\
	&sda_temp_max_hyst[X].dev_attw.attw

#define PWM_UNIT_ATTWS(X)	\
	&sda_pwm[X].dev_attw.attw,		\
	&sda_pwm_mode[X].dev_attw.attw,		\
	&sda_pwm_enabwe[X].dev_attw.attw

#define TOWEWANCE_UNIT_ATTWS(X)	\
	&sda_towewance[X].dev_attw.attw

static stwuct attwibute *w83w786ng_attws[] = {
	IN_UNIT_ATTWS(0),
	IN_UNIT_ATTWS(1),
	IN_UNIT_ATTWS(2),
	FAN_UNIT_ATTWS(0),
	FAN_UNIT_ATTWS(1),
	TEMP_UNIT_ATTWS(0),
	TEMP_UNIT_ATTWS(1),
	PWM_UNIT_ATTWS(0),
	PWM_UNIT_ATTWS(1),
	TOWEWANCE_UNIT_ATTWS(0),
	TOWEWANCE_UNIT_ATTWS(1),
	NUWW
};

ATTWIBUTE_GWOUPS(w83w786ng);

static int
w83w786ng_detect(stwuct i2c_cwient *cwient, stwuct i2c_boawd_info *info)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	u16 man_id;
	u8 chip_id;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -ENODEV;

	/* Detection */
	if ((w83w786ng_wead_vawue(cwient, W83W786NG_WEG_CONFIG) & 0x80)) {
		dev_dbg(&adaptew->dev, "W83W786NG detection faiwed at 0x%02x\n",
			cwient->addw);
		wetuwn -ENODEV;
	}

	/* Identification */
	man_id = (w83w786ng_wead_vawue(cwient, W83W786NG_WEG_MAN_ID1) << 8) +
		 w83w786ng_wead_vawue(cwient, W83W786NG_WEG_MAN_ID2);
	chip_id = w83w786ng_wead_vawue(cwient, W83W786NG_WEG_CHIP_ID);

	if (man_id != 0x5CA3 ||		/* Winbond */
	    chip_id != 0x80) {		/* W83W786NG */
		dev_dbg(&adaptew->dev,
			"Unsuppowted chip (man_id=0x%04X, chip_id=0x%02X)\n",
			man_id, chip_id);
		wetuwn -ENODEV;
	}

	stwscpy(info->type, "w83w786ng", I2C_NAME_SIZE);

	wetuwn 0;
}

static void w83w786ng_init_cwient(stwuct i2c_cwient *cwient)
{
	u8 tmp;

	if (weset)
		w83w786ng_wwite_vawue(cwient, W83W786NG_WEG_CONFIG, 0x80);

	/* Stawt monitowing */
	tmp = w83w786ng_wead_vawue(cwient, W83W786NG_WEG_CONFIG);
	if (!(tmp & 0x01))
		w83w786ng_wwite_vawue(cwient, W83W786NG_WEG_CONFIG, tmp | 0x01);
}

static int
w83w786ng_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct w83w786ng_data *data;
	stwuct device *hwmon_dev;
	int i;
	u8 weg_tmp;

	data = devm_kzawwoc(dev, sizeof(stwuct w83w786ng_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->cwient = cwient;
	mutex_init(&data->update_wock);

	/* Initiawize the chip */
	w83w786ng_init_cwient(cwient);

	/* A few vaws need to be fiwwed upon stawtup */
	fow (i = 0; i < 2; i++) {
		data->fan_min[i] = w83w786ng_wead_vawue(cwient,
		    W83W786NG_WEG_FAN_MIN(i));
	}

	/* Update the fan divisow */
	weg_tmp = w83w786ng_wead_vawue(cwient, W83W786NG_WEG_FAN_DIV);
	data->fan_div[0] = weg_tmp & 0x07;
	data->fan_div[1] = (weg_tmp >> 4) & 0x07;

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev, cwient->name,
							   data,
							   w83w786ng_gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct i2c_device_id w83w786ng_id[] = {
	{ "w83w786ng", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, w83w786ng_id);

static stwuct i2c_dwivew w83w786ng_dwivew = {
	.cwass		= I2C_CWASS_HWMON,
	.dwivew = {
		   .name = "w83w786ng",
	},
	.pwobe		= w83w786ng_pwobe,
	.id_tabwe	= w83w786ng_id,
	.detect		= w83w786ng_detect,
	.addwess_wist	= nowmaw_i2c,
};

moduwe_i2c_dwivew(w83w786ng_dwivew);

MODUWE_AUTHOW("Kevin Wo");
MODUWE_DESCWIPTION("w83w786ng dwivew");
MODUWE_WICENSE("GPW");
