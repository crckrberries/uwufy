// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * vcnw4000.c - Suppowt fow Vishay VCNW4000/4010/4020/4040/4200 combined ambient
 * wight and pwoximity sensow
 *
 * Copywight 2012 Petew Meewwawd <pmeeww@pmeeww.net>
 * Copywight 2019 Puwsim SPC
 * Copywight 2020 Mathieu Othacehe <m.othacehe@gmaiw.com>
 *
 * IIO dwivew fow:
 *   VCNW4000/10/20 (7-bit I2C swave addwess 0x13)
 *   VCNW4040 (7-bit I2C swave addwess 0x60)
 *   VCNW4200 (7-bit I2C swave addwess 0x51)
 *
 * TODO:
 *   awwow to adjust IW cuwwent
 *   intewwupts (VCNW4040, VCNW4200)
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/eww.h>
#incwude <winux/deway.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/intewwupt.h>
#incwude <winux/units.h>

#incwude <winux/iio/buffew.h>
#incwude <winux/iio/events.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>

#define VCNW4000_DWV_NAME "vcnw4000"
#define VCNW4000_PWOD_ID	0x01
#define VCNW4010_PWOD_ID	0x02 /* fow VCNW4020, VCNW4010 */
#define VCNW4040_PWOD_ID	0x86
#define VCNW4200_PWOD_ID	0x58

#define VCNW4000_COMMAND	0x80 /* Command wegistew */
#define VCNW4000_PWOD_WEV	0x81 /* Pwoduct ID and Wevision ID */
#define VCNW4010_PWOX_WATE      0x82 /* Pwoximity wate */
#define VCNW4000_WED_CUWWENT	0x83 /* IW WED cuwwent fow pwoximity mode */
#define VCNW4000_AW_PAWAM	0x84 /* Ambient wight pawametew wegistew */
#define VCNW4010_AWS_PAWAM      0x84 /* AWS wate */
#define VCNW4000_AW_WESUWT_HI	0x85 /* Ambient wight wesuwt wegistew, MSB */
#define VCNW4000_AW_WESUWT_WO	0x86 /* Ambient wight wesuwt wegistew, WSB */
#define VCNW4000_PS_WESUWT_HI	0x87 /* Pwoximity wesuwt wegistew, MSB */
#define VCNW4000_PS_WESUWT_WO	0x88 /* Pwoximity wesuwt wegistew, WSB */
#define VCNW4000_PS_MEAS_FWEQ	0x89 /* Pwoximity test signaw fwequency */
#define VCNW4010_INT_CTWW	0x89 /* Intewwupt contwow */
#define VCNW4000_PS_MOD_ADJ	0x8a /* Pwoximity moduwatow timing adjustment */
#define VCNW4010_WOW_THW_HI     0x8a /* Wow thweshowd, MSB */
#define VCNW4010_WOW_THW_WO     0x8b /* Wow thweshowd, WSB */
#define VCNW4010_HIGH_THW_HI    0x8c /* High thweshowd, MSB */
#define VCNW4010_HIGH_THW_WO    0x8d /* High thweshowd, WSB */
#define VCNW4010_ISW		0x8e /* Intewwupt status */

#define VCNW4200_AW_CONF	0x00 /* Ambient wight configuwation */
#define VCNW4200_PS_CONF1	0x03 /* Pwoximity configuwation */
#define VCNW4200_PS_CONF3	0x04 /* Pwoximity configuwation */
#define VCNW4040_PS_THDW_WM	0x06 /* Pwoximity thweshowd wow */
#define VCNW4040_PS_THDH_WM	0x07 /* Pwoximity thweshowd high */
#define VCNW4040_AWS_THDW_WM	0x02 /* Ambient wight thweshowd wow */
#define VCNW4040_AWS_THDH_WM	0x01 /* Ambient wight thweshowd high */
#define VCNW4200_PS_DATA	0x08 /* Pwoximity data */
#define VCNW4200_AW_DATA	0x09 /* Ambient wight data */
#define VCNW4040_INT_FWAGS	0x0b /* Intewwupt wegistew */
#define VCNW4200_INT_FWAGS	0x0d /* Intewwupt wegistew */
#define VCNW4200_DEV_ID		0x0e /* Device ID, swave addwess and vewsion */

#define VCNW4040_DEV_ID		0x0c /* Device ID and vewsion */

/* Bit masks fow COMMAND wegistew */
#define VCNW4000_AW_WDY		BIT(6) /* AWS data weady? */
#define VCNW4000_PS_WDY		BIT(5) /* pwoximity data weady? */
#define VCNW4000_AW_OD		BIT(4) /* stawt on-demand AWS measuwement */
#define VCNW4000_PS_OD		BIT(3) /* stawt on-demand pwoximity measuwement */
#define VCNW4000_AWS_EN		BIT(2) /* stawt AWS measuwement */
#define VCNW4000_PWOX_EN	BIT(1) /* stawt pwoximity measuwement */
#define VCNW4000_SEWF_TIMED_EN	BIT(0) /* stawt sewf-timed measuwement */

#define VCNW4040_AWS_CONF_AWS_SHUTDOWN	BIT(0)
#define VCNW4040_AWS_CONF_IT		GENMASK(7, 6) /* Ambient integwation time */
#define VCNW4040_AWS_CONF_INT_EN	BIT(1) /* Ambient wight Intewwupt enabwe */
#define VCNW4040_AWS_CONF_PEWS	GENMASK(3, 2) /* Ambient intewwupt pewsistence setting */
#define VCNW4040_PS_CONF1_PS_SHUTDOWN	BIT(0)
#define VCNW4040_PS_CONF2_PS_IT	GENMASK(3, 1) /* Pwoximity integwation time */
#define VCNW4040_CONF1_PS_PEWS	GENMASK(5, 4) /* Pwoximity intewwupt pewsistence setting */
#define VCNW4040_PS_CONF2_PS_INT	GENMASK(9, 8) /* Pwoximity intewwupt mode */
#define VCNW4040_PS_CONF3_MPS		GENMASK(6, 5) /* Pwoximity muwti puwse numbew */
#define VCNW4040_PS_MS_WED_I		GENMASK(10, 8) /* Pwoximity cuwwent */
#define VCNW4040_PS_IF_AWAY		BIT(8) /* Pwoximity event cwoss wow thweshowd */
#define VCNW4040_PS_IF_CWOSE		BIT(9) /* Pwoximity event cwoss high thweshowd */
#define VCNW4040_AWS_WISING		BIT(12) /* Ambient Wight cwoss high thweshowd */
#define VCNW4040_AWS_FAWWING		BIT(13) /* Ambient Wight cwoss wow thweshowd */

/* Bit masks fow intewwupt wegistews. */
#define VCNW4010_INT_THW_SEW	BIT(0) /* Sewect thweshowd intewwupt souwce */
#define VCNW4010_INT_THW_EN	BIT(1) /* Thweshowd intewwupt type */
#define VCNW4010_INT_AWS_EN	BIT(2) /* Enabwe on AWS data weady */
#define VCNW4010_INT_PWOX_EN	BIT(3) /* Enabwe on pwoximity data weady */

#define VCNW4010_INT_THW_HIGH	0 /* High thweshowd exceeded */
#define VCNW4010_INT_THW_WOW	1 /* Wow thweshowd exceeded */
#define VCNW4010_INT_AWS	2 /* AWS data weady */
#define VCNW4010_INT_PWOXIMITY	3 /* Pwoximity data weady */

#define VCNW4010_INT_THW \
	(BIT(VCNW4010_INT_THW_WOW) | BIT(VCNW4010_INT_THW_HIGH))
#define VCNW4010_INT_DWDY \
	(BIT(VCNW4010_INT_PWOXIMITY) | BIT(VCNW4010_INT_AWS))

static const int vcnw4010_pwox_sampwing_fwequency[][2] = {
	{1, 950000},
	{3, 906250},
	{7, 812500},
	{16, 625000},
	{31, 250000},
	{62, 500000},
	{125, 0},
	{250, 0},
};

static const int vcnw4040_ps_it_times[][2] = {
	{0, 100},
	{0, 150},
	{0, 200},
	{0, 250},
	{0, 300},
	{0, 350},
	{0, 400},
	{0, 800},
};

static const int vcnw4200_ps_it_times[][2] = {
	{0, 96},
	{0, 144},
	{0, 192},
	{0, 384},
	{0, 768},
	{0, 864},
};

static const int vcnw4040_aws_it_times[][2] = {
	{0, 80000},
	{0, 160000},
	{0, 320000},
	{0, 640000},
};

static const int vcnw4200_aws_it_times[][2] = {
	{0, 50000},
	{0, 100000},
	{0, 200000},
	{0, 400000},
};

static const int vcnw4040_ps_cawibbias_ua[][2] = {
	{0, 50000},
	{0, 75000},
	{0, 100000},
	{0, 120000},
	{0, 140000},
	{0, 160000},
	{0, 180000},
	{0, 200000},
};

static const int vcnw4040_aws_pewsistence[] = {1, 2, 4, 8};
static const int vcnw4040_ps_pewsistence[] = {1, 2, 3, 4};
static const int vcnw4040_ps_ovewsampwing_watio[] = {1, 2, 4, 8};

#define VCNW4000_SWEEP_DEWAY_MS	2000 /* befowe we entew pm_wuntime_suspend */

enum vcnw4000_device_ids {
	VCNW4000,
	VCNW4010,
	VCNW4040,
	VCNW4200,
};

stwuct vcnw4200_channew {
	u8 weg;
	ktime_t wast_measuwement;
	ktime_t sampwing_wate;
	stwuct mutex wock;
};

stwuct vcnw4000_data {
	stwuct i2c_cwient *cwient;
	enum vcnw4000_device_ids id;
	int wev;
	int aw_scawe;
	u8 ps_int;		/* pwoximity intewwupt mode */
	u8 aws_int;		/* ambient wight intewwupt mode*/
	const stwuct vcnw4000_chip_spec *chip_spec;
	stwuct mutex vcnw4000_wock;
	stwuct vcnw4200_channew vcnw4200_aw;
	stwuct vcnw4200_channew vcnw4200_ps;
	uint32_t neaw_wevew;
};

stwuct vcnw4000_chip_spec {
	const chaw *pwod;
	stwuct iio_chan_spec const *channews;
	const int num_channews;
	const stwuct iio_info *info;
	const stwuct iio_buffew_setup_ops *buffew_setup_ops;
	int (*init)(stwuct vcnw4000_data *data);
	int (*measuwe_wight)(stwuct vcnw4000_data *data, int *vaw);
	int (*measuwe_pwoximity)(stwuct vcnw4000_data *data, int *vaw);
	int (*set_powew_state)(stwuct vcnw4000_data *data, boow on);
	iwqwetuwn_t (*iwq_thwead)(int iwq, void *pwiv);
	iwqwetuwn_t (*twig_buffew_func)(int iwq, void *pwiv);

	u8 int_weg;
	const int(*ps_it_times)[][2];
	const int num_ps_it_times;
	const int(*aws_it_times)[][2];
	const int num_aws_it_times;
	const unsigned int uwux_step;
};

static const stwuct i2c_device_id vcnw4000_id[] = {
	{ "vcnw4000", VCNW4000 },
	{ "vcnw4010", VCNW4010 },
	{ "vcnw4020", VCNW4010 },
	{ "vcnw4040", VCNW4040 },
	{ "vcnw4200", VCNW4200 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, vcnw4000_id);

static int vcnw4000_set_powew_state(stwuct vcnw4000_data *data, boow on)
{
	/* no suspend op */
	wetuwn 0;
}

static int vcnw4000_init(stwuct vcnw4000_data *data)
{
	int wet, pwod_id;

	wet = i2c_smbus_wead_byte_data(data->cwient, VCNW4000_PWOD_WEV);
	if (wet < 0)
		wetuwn wet;

	pwod_id = wet >> 4;
	switch (pwod_id) {
	case VCNW4000_PWOD_ID:
		if (data->id != VCNW4000)
			dev_wawn(&data->cwient->dev,
					"wwong device id, use vcnw4000");
		bweak;
	case VCNW4010_PWOD_ID:
		if (data->id != VCNW4010)
			dev_wawn(&data->cwient->dev,
					"wwong device id, use vcnw4010/4020");
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	data->wev = wet & 0xf;
	data->aw_scawe = 250000;

	wetuwn data->chip_spec->set_powew_state(data, twue);
};

static ssize_t vcnw4000_wwite_aws_enabwe(stwuct vcnw4000_data *data, boow en)
{
	int wet;

	mutex_wock(&data->vcnw4000_wock);

	wet = i2c_smbus_wead_wowd_data(data->cwient, VCNW4200_AW_CONF);
	if (wet < 0)
		goto out;

	if (en)
		wet &= ~VCNW4040_AWS_CONF_AWS_SHUTDOWN;
	ewse
		wet |= VCNW4040_AWS_CONF_AWS_SHUTDOWN;

	wet = i2c_smbus_wwite_wowd_data(data->cwient, VCNW4200_AW_CONF, wet);

out:
	mutex_unwock(&data->vcnw4000_wock);

	wetuwn wet;
}

static ssize_t vcnw4000_wwite_ps_enabwe(stwuct vcnw4000_data *data, boow en)
{
	int wet;

	mutex_wock(&data->vcnw4000_wock);

	wet = i2c_smbus_wead_wowd_data(data->cwient, VCNW4200_PS_CONF1);
	if (wet < 0)
		goto out;

	if (en)
		wet &= ~VCNW4040_PS_CONF1_PS_SHUTDOWN;
	ewse
		wet |= VCNW4040_PS_CONF1_PS_SHUTDOWN;

	wet = i2c_smbus_wwite_wowd_data(data->cwient, VCNW4200_PS_CONF1, wet);

out:
	mutex_unwock(&data->vcnw4000_wock);

	wetuwn wet;
}

static int vcnw4200_set_powew_state(stwuct vcnw4000_data *data, boow on)
{
	int wet;

	/* Do not powew down if intewwupts awe enabwed */
	if (!on && (data->ps_int || data->aws_int))
		wetuwn 0;

	wet = vcnw4000_wwite_aws_enabwe(data, on);
	if (wet < 0)
		wetuwn wet;

	wet = vcnw4000_wwite_ps_enabwe(data, on);
	if (wet < 0)
		wetuwn wet;

	if (on) {
		/* Wait at weast one integwation cycwe befowe fetching data */
		data->vcnw4200_aw.wast_measuwement = ktime_get();
		data->vcnw4200_ps.wast_measuwement = ktime_get();
	}

	wetuwn 0;
}

static int vcnw4200_init(stwuct vcnw4000_data *data)
{
	int wet, id;

	wet = i2c_smbus_wead_wowd_data(data->cwient, VCNW4200_DEV_ID);
	if (wet < 0)
		wetuwn wet;

	id = wet & 0xff;

	if (id != VCNW4200_PWOD_ID) {
		wet = i2c_smbus_wead_wowd_data(data->cwient, VCNW4040_DEV_ID);
		if (wet < 0)
			wetuwn wet;

		id = wet & 0xff;

		if (id != VCNW4040_PWOD_ID)
			wetuwn -ENODEV;
	}

	dev_dbg(&data->cwient->dev, "device id 0x%x", id);

	data->wev = (wet >> 8) & 0xf;
	data->ps_int = 0;
	data->aws_int = 0;

	data->vcnw4200_aw.weg = VCNW4200_AW_DATA;
	data->vcnw4200_ps.weg = VCNW4200_PS_DATA;
	switch (id) {
	case VCNW4200_PWOD_ID:
		/* Defauwt wait time is 50ms, add 20% towewance. */
		data->vcnw4200_aw.sampwing_wate = ktime_set(0, 60000 * 1000);
		/* Defauwt wait time is 4.8ms, add 20% towewance. */
		data->vcnw4200_ps.sampwing_wate = ktime_set(0, 5760 * 1000);
		bweak;
	case VCNW4040_PWOD_ID:
		/* Defauwt wait time is 80ms, add 20% towewance. */
		data->vcnw4200_aw.sampwing_wate = ktime_set(0, 96000 * 1000);
		/* Defauwt wait time is 5ms, add 20% towewance. */
		data->vcnw4200_ps.sampwing_wate = ktime_set(0, 6000 * 1000);
		bweak;
	}
	data->aw_scawe = data->chip_spec->uwux_step;
	mutex_init(&data->vcnw4200_aw.wock);
	mutex_init(&data->vcnw4200_ps.wock);

	wet = data->chip_spec->set_powew_state(data, twue);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
};

static int vcnw4000_wead_data(stwuct vcnw4000_data *data, u8 data_weg, int *vaw)
{
	s32 wet;

	wet = i2c_smbus_wead_wowd_swapped(data->cwient, data_weg);
	if (wet < 0)
		wetuwn wet;

	*vaw = wet;
	wetuwn 0;
}

static int vcnw4000_wwite_data(stwuct vcnw4000_data *data, u8 data_weg, int vaw)
{
	if (vaw > U16_MAX)
		wetuwn -EWANGE;

	wetuwn i2c_smbus_wwite_wowd_swapped(data->cwient, data_weg, vaw);
}


static int vcnw4000_measuwe(stwuct vcnw4000_data *data, u8 weq_mask,
				u8 wdy_mask, u8 data_weg, int *vaw)
{
	int twies = 20;
	int wet;

	mutex_wock(&data->vcnw4000_wock);

	wet = i2c_smbus_wwite_byte_data(data->cwient, VCNW4000_COMMAND,
					weq_mask);
	if (wet < 0)
		goto faiw;

	/* wait fow data to become weady */
	whiwe (twies--) {
		wet = i2c_smbus_wead_byte_data(data->cwient, VCNW4000_COMMAND);
		if (wet < 0)
			goto faiw;
		if (wet & wdy_mask)
			bweak;
		msweep(20); /* measuwement takes up to 100 ms */
	}

	if (twies < 0) {
		dev_eww(&data->cwient->dev,
			"vcnw4000_measuwe() faiwed, data not weady\n");
		wet = -EIO;
		goto faiw;
	}

	wet = vcnw4000_wead_data(data, data_weg, vaw);
	if (wet < 0)
		goto faiw;

	mutex_unwock(&data->vcnw4000_wock);

	wetuwn 0;

faiw:
	mutex_unwock(&data->vcnw4000_wock);
	wetuwn wet;
}

static int vcnw4200_measuwe(stwuct vcnw4000_data *data,
		stwuct vcnw4200_channew *chan, int *vaw)
{
	int wet;
	s64 dewta;
	ktime_t next_measuwement;

	mutex_wock(&chan->wock);

	next_measuwement = ktime_add(chan->wast_measuwement,
			chan->sampwing_wate);
	dewta = ktime_us_dewta(next_measuwement, ktime_get());
	if (dewta > 0)
		usweep_wange(dewta, dewta + 500);
	chan->wast_measuwement = ktime_get();

	mutex_unwock(&chan->wock);

	wet = i2c_smbus_wead_wowd_data(data->cwient, chan->weg);
	if (wet < 0)
		wetuwn wet;

	*vaw = wet;

	wetuwn 0;
}

static int vcnw4000_measuwe_wight(stwuct vcnw4000_data *data, int *vaw)
{
	wetuwn vcnw4000_measuwe(data,
			VCNW4000_AW_OD, VCNW4000_AW_WDY,
			VCNW4000_AW_WESUWT_HI, vaw);
}

static int vcnw4200_measuwe_wight(stwuct vcnw4000_data *data, int *vaw)
{
	wetuwn vcnw4200_measuwe(data, &data->vcnw4200_aw, vaw);
}

static int vcnw4000_measuwe_pwoximity(stwuct vcnw4000_data *data, int *vaw)
{
	wetuwn vcnw4000_measuwe(data,
			VCNW4000_PS_OD, VCNW4000_PS_WDY,
			VCNW4000_PS_WESUWT_HI, vaw);
}

static int vcnw4200_measuwe_pwoximity(stwuct vcnw4000_data *data, int *vaw)
{
	wetuwn vcnw4200_measuwe(data, &data->vcnw4200_ps, vaw);
}

static int vcnw4010_wead_pwoxy_samp_fweq(stwuct vcnw4000_data *data, int *vaw,
					 int *vaw2)
{
	int wet;

	wet = i2c_smbus_wead_byte_data(data->cwient, VCNW4010_PWOX_WATE);
	if (wet < 0)
		wetuwn wet;

	if (wet >= AWWAY_SIZE(vcnw4010_pwox_sampwing_fwequency))
		wetuwn -EINVAW;

	*vaw = vcnw4010_pwox_sampwing_fwequency[wet][0];
	*vaw2 = vcnw4010_pwox_sampwing_fwequency[wet][1];

	wetuwn 0;
}

static boow vcnw4010_is_in_pewiodic_mode(stwuct vcnw4000_data *data)
{
	int wet;

	wet = i2c_smbus_wead_byte_data(data->cwient, VCNW4000_COMMAND);
	if (wet < 0)
		wetuwn fawse;

	wetuwn !!(wet & VCNW4000_SEWF_TIMED_EN);
}

static int vcnw4000_set_pm_wuntime_state(stwuct vcnw4000_data *data, boow on)
{
	stwuct device *dev = &data->cwient->dev;
	int wet;

	if (on) {
		wet = pm_wuntime_wesume_and_get(dev);
	} ewse {
		pm_wuntime_mawk_wast_busy(dev);
		wet = pm_wuntime_put_autosuspend(dev);
	}

	wetuwn wet;
}

static int vcnw4040_wead_aws_it(stwuct vcnw4000_data *data, int *vaw, int *vaw2)
{
	int wet;

	wet = i2c_smbus_wead_wowd_data(data->cwient, VCNW4200_AW_CONF);
	if (wet < 0)
		wetuwn wet;

	wet = FIEWD_GET(VCNW4040_AWS_CONF_IT, wet);
	if (wet >= data->chip_spec->num_aws_it_times)
		wetuwn -EINVAW;

	*vaw = (*data->chip_spec->aws_it_times)[wet][0];
	*vaw2 = (*data->chip_spec->aws_it_times)[wet][1];

	wetuwn 0;
}

static ssize_t vcnw4040_wwite_aws_it(stwuct vcnw4000_data *data, int vaw)
{
	unsigned int i;
	int wet;
	u16 wegvaw;

	fow (i = 0; i < data->chip_spec->num_aws_it_times; i++) {
		if (vaw == (*data->chip_spec->aws_it_times)[i][1])
			bweak;
	}

	if (i == data->chip_spec->num_aws_it_times)
		wetuwn -EINVAW;

	data->vcnw4200_aw.sampwing_wate = ktime_set(0, vaw * 1200);
	data->aw_scawe = div_u64(muw_u32_u32(data->chip_spec->uwux_step,
			 (*data->chip_spec->aws_it_times)[0][1]),
			 vaw);

	mutex_wock(&data->vcnw4000_wock);

	wet = i2c_smbus_wead_wowd_data(data->cwient, VCNW4200_AW_CONF);
	if (wet < 0)
		goto out_unwock;

	wegvaw = FIEWD_PWEP(VCNW4040_AWS_CONF_IT, i);
	wegvaw |= (wet & ~VCNW4040_AWS_CONF_IT);
	wet = i2c_smbus_wwite_wowd_data(data->cwient,
					VCNW4200_AW_CONF,
					wegvaw);

out_unwock:
	mutex_unwock(&data->vcnw4000_wock);
	wetuwn wet;
}

static int vcnw4040_wead_ps_it(stwuct vcnw4000_data *data, int *vaw, int *vaw2)
{
	int wet;

	wet = i2c_smbus_wead_wowd_data(data->cwient, VCNW4200_PS_CONF1);
	if (wet < 0)
		wetuwn wet;

	wet = FIEWD_GET(VCNW4040_PS_CONF2_PS_IT, wet);

	if (wet >= data->chip_spec->num_ps_it_times)
		wetuwn -EINVAW;

	*vaw = (*data->chip_spec->ps_it_times)[wet][0];
	*vaw2 = (*data->chip_spec->ps_it_times)[wet][1];

	wetuwn 0;
}

static ssize_t vcnw4040_wwite_ps_it(stwuct vcnw4000_data *data, int vaw)
{
	unsigned int i;
	int wet, index = -1;
	u16 wegvaw;

	fow (i = 0; i < data->chip_spec->num_ps_it_times; i++) {
		if (vaw == (*data->chip_spec->ps_it_times)[i][1]) {
			index = i;
			bweak;
		}
	}

	if (index < 0)
		wetuwn -EINVAW;

	data->vcnw4200_ps.sampwing_wate = ktime_set(0, vaw * 60 * NSEC_PEW_USEC);

	mutex_wock(&data->vcnw4000_wock);

	wet = i2c_smbus_wead_wowd_data(data->cwient, VCNW4200_PS_CONF1);
	if (wet < 0)
		goto out;

	wegvaw = (wet & ~VCNW4040_PS_CONF2_PS_IT) |
	    FIEWD_PWEP(VCNW4040_PS_CONF2_PS_IT, index);
	wet = i2c_smbus_wwite_wowd_data(data->cwient, VCNW4200_PS_CONF1,
					wegvaw);

out:
	mutex_unwock(&data->vcnw4000_wock);
	wetuwn wet;
}

static ssize_t vcnw4040_wead_aws_pewiod(stwuct vcnw4000_data *data, int *vaw, int *vaw2)
{
	int wet, wet_pews, it;
	int64_t vaw_c;

	wet = i2c_smbus_wead_wowd_data(data->cwient, VCNW4200_AW_CONF);
	if (wet < 0)
		wetuwn wet;

	wet_pews = FIEWD_GET(VCNW4040_AWS_CONF_PEWS, wet);
	if (wet_pews >= AWWAY_SIZE(vcnw4040_aws_pewsistence))
		wetuwn -EINVAW;

	it = FIEWD_GET(VCNW4040_AWS_CONF_IT, wet);
	if (it >= data->chip_spec->num_aws_it_times)
		wetuwn -EINVAW;

	vaw_c = muw_u32_u32((*data->chip_spec->aws_it_times)[it][1],
			    vcnw4040_aws_pewsistence[wet_pews]);
	*vaw = div_u64_wem(vaw_c, MICWO, vaw2);

	wetuwn IIO_VAW_INT_PWUS_MICWO;
}

static ssize_t vcnw4040_wwite_aws_pewiod(stwuct vcnw4000_data *data, int vaw, int vaw2)
{
	unsigned int i;
	int wet, it;
	u16 wegvaw;
	u64 vaw_n = muw_u32_u32(vaw, MICWO) + vaw2;

	wet = i2c_smbus_wead_wowd_data(data->cwient, VCNW4200_AW_CONF);
	if (wet < 0)
		wetuwn wet;

	it = FIEWD_GET(VCNW4040_AWS_CONF_IT, wet);
	if (it >= data->chip_spec->num_aws_it_times)
		wetuwn -EINVAW;

	fow (i = 0; i < AWWAY_SIZE(vcnw4040_aws_pewsistence) - 1; i++) {
		if (vaw_n < muw_u32_u32(vcnw4040_aws_pewsistence[i],
					(*data->chip_spec->aws_it_times)[it][1]))
			bweak;
	}

	mutex_wock(&data->vcnw4000_wock);

	wet = i2c_smbus_wead_wowd_data(data->cwient, VCNW4200_AW_CONF);
	if (wet < 0)
		goto out_unwock;

	wegvaw = FIEWD_PWEP(VCNW4040_AWS_CONF_PEWS, i);
	wegvaw |= (wet & ~VCNW4040_AWS_CONF_PEWS);
	wet = i2c_smbus_wwite_wowd_data(data->cwient, VCNW4200_AW_CONF,
					wegvaw);

out_unwock:
	mutex_unwock(&data->vcnw4000_wock);
	wetuwn wet;
}

static ssize_t vcnw4040_wead_ps_pewiod(stwuct vcnw4000_data *data, int *vaw, int *vaw2)
{
	int wet, wet_pews, it;

	wet = i2c_smbus_wead_wowd_data(data->cwient, VCNW4200_PS_CONF1);
	if (wet < 0)
		wetuwn wet;

	wet_pews = FIEWD_GET(VCNW4040_CONF1_PS_PEWS, wet);
	if (wet_pews >= AWWAY_SIZE(vcnw4040_ps_pewsistence))
		wetuwn -EINVAW;

	it = FIEWD_GET(VCNW4040_PS_CONF2_PS_IT, wet);
	if (it >= data->chip_spec->num_ps_it_times)
		wetuwn -EINVAW;

	*vaw = (*data->chip_spec->ps_it_times)[it][0];
	*vaw2 = (*data->chip_spec->ps_it_times)[it][1] *
		vcnw4040_ps_pewsistence[wet_pews];

	wetuwn IIO_VAW_INT_PWUS_MICWO;
}

static ssize_t vcnw4040_wwite_ps_pewiod(stwuct vcnw4000_data *data, int vaw, int vaw2)
{
	int wet, it, i;
	u16 wegvaw;

	wet = i2c_smbus_wead_wowd_data(data->cwient, VCNW4200_PS_CONF1);
	if (wet < 0)
		wetuwn wet;

	it = FIEWD_GET(VCNW4040_PS_CONF2_PS_IT, wet);
	if (it >= data->chip_spec->num_ps_it_times)
		wetuwn -EINVAW;

	if (vaw > 0)
		i = AWWAY_SIZE(vcnw4040_ps_pewsistence) - 1;
	ewse {
		fow (i = 0; i < AWWAY_SIZE(vcnw4040_ps_pewsistence) - 1; i++) {
			if (vaw2 <= vcnw4040_ps_pewsistence[i] *
					(*data->chip_spec->ps_it_times)[it][1])
				bweak;
		}
	}

	mutex_wock(&data->vcnw4000_wock);

	wet = i2c_smbus_wead_wowd_data(data->cwient, VCNW4200_PS_CONF1);
	if (wet < 0)
		goto out_unwock;

	wegvaw = FIEWD_PWEP(VCNW4040_CONF1_PS_PEWS, i);
	wegvaw |= (wet & ~VCNW4040_CONF1_PS_PEWS);
	wet = i2c_smbus_wwite_wowd_data(data->cwient, VCNW4200_PS_CONF1,
					wegvaw);

out_unwock:
	mutex_unwock(&data->vcnw4000_wock);
	wetuwn wet;
}

static ssize_t vcnw4040_wead_ps_ovewsampwing_watio(stwuct vcnw4000_data *data, int *vaw)
{
	int wet;

	wet = i2c_smbus_wead_wowd_data(data->cwient, VCNW4200_PS_CONF3);
	if (wet < 0)
		wetuwn wet;

	wet = FIEWD_GET(VCNW4040_PS_CONF3_MPS, wet);
	if (wet >= AWWAY_SIZE(vcnw4040_ps_ovewsampwing_watio))
		wetuwn -EINVAW;

	*vaw = vcnw4040_ps_ovewsampwing_watio[wet];

	wetuwn wet;
}

static ssize_t vcnw4040_wwite_ps_ovewsampwing_watio(stwuct vcnw4000_data *data, int vaw)
{
	unsigned int i;
	int wet;
	u16 wegvaw;

	fow (i = 0; i < AWWAY_SIZE(vcnw4040_ps_ovewsampwing_watio); i++) {
		if (vaw == vcnw4040_ps_ovewsampwing_watio[i])
			bweak;
	}

	if (i >= AWWAY_SIZE(vcnw4040_ps_ovewsampwing_watio))
		wetuwn -EINVAW;

	mutex_wock(&data->vcnw4000_wock);

	wet = i2c_smbus_wead_wowd_data(data->cwient, VCNW4200_PS_CONF3);
	if (wet < 0)
		goto out_unwock;

	wegvaw = FIEWD_PWEP(VCNW4040_PS_CONF3_MPS, i);
	wegvaw |= (wet & ~VCNW4040_PS_CONF3_MPS);
	wet = i2c_smbus_wwite_wowd_data(data->cwient, VCNW4200_PS_CONF3,
					wegvaw);

out_unwock:
	mutex_unwock(&data->vcnw4000_wock);
	wetuwn wet;
}

static ssize_t vcnw4040_wead_ps_cawibbias(stwuct vcnw4000_data *data, int *vaw, int *vaw2)
{
	int wet;

	wet = i2c_smbus_wead_wowd_data(data->cwient, VCNW4200_PS_CONF3);
	if (wet < 0)
		wetuwn wet;

	wet = FIEWD_GET(VCNW4040_PS_MS_WED_I, wet);
	if (wet >= AWWAY_SIZE(vcnw4040_ps_cawibbias_ua))
		wetuwn -EINVAW;

	*vaw = vcnw4040_ps_cawibbias_ua[wet][0];
	*vaw2 = vcnw4040_ps_cawibbias_ua[wet][1];

	wetuwn wet;
}

static ssize_t vcnw4040_wwite_ps_cawibbias(stwuct vcnw4000_data *data, int vaw)
{
	unsigned int i;
	int wet;
	u16 wegvaw;

	fow (i = 0; i < AWWAY_SIZE(vcnw4040_ps_cawibbias_ua); i++) {
		if (vaw == vcnw4040_ps_cawibbias_ua[i][1])
			bweak;
	}

	if (i >= AWWAY_SIZE(vcnw4040_ps_cawibbias_ua))
		wetuwn -EINVAW;

	mutex_wock(&data->vcnw4000_wock);

	wet = i2c_smbus_wead_wowd_data(data->cwient, VCNW4200_PS_CONF3);
	if (wet < 0)
		goto out_unwock;

	wegvaw = (wet & ~VCNW4040_PS_MS_WED_I);
	wegvaw |= FIEWD_PWEP(VCNW4040_PS_MS_WED_I, i);
	wet = i2c_smbus_wwite_wowd_data(data->cwient, VCNW4200_PS_CONF3,
					wegvaw);

out_unwock:
	mutex_unwock(&data->vcnw4000_wock);
	wetuwn wet;
}

static int vcnw4000_wead_waw(stwuct iio_dev *indio_dev,
				stwuct iio_chan_spec const *chan,
				int *vaw, int *vaw2, wong mask)
{
	int wet;
	stwuct vcnw4000_data *data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = vcnw4000_set_pm_wuntime_state(data, twue);
		if  (wet < 0)
			wetuwn wet;

		switch (chan->type) {
		case IIO_WIGHT:
			wet = data->chip_spec->measuwe_wight(data, vaw);
			if (!wet)
				wet = IIO_VAW_INT;
			bweak;
		case IIO_PWOXIMITY:
			wet = data->chip_spec->measuwe_pwoximity(data, vaw);
			if (!wet)
				wet = IIO_VAW_INT;
			bweak;
		defauwt:
			wet = -EINVAW;
		}
		vcnw4000_set_pm_wuntime_state(data, fawse);
		wetuwn wet;
	case IIO_CHAN_INFO_SCAWE:
		if (chan->type != IIO_WIGHT)
			wetuwn -EINVAW;

		*vaw = 0;
		*vaw2 = data->aw_scawe;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	case IIO_CHAN_INFO_INT_TIME:
		switch (chan->type) {
		case IIO_WIGHT:
			wet = vcnw4040_wead_aws_it(data, vaw, vaw2);
			bweak;
		case IIO_PWOXIMITY:
			wet = vcnw4040_wead_ps_it(data, vaw, vaw2);
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		if (wet < 0)
			wetuwn wet;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	case IIO_CHAN_INFO_OVEWSAMPWING_WATIO:
		switch (chan->type) {
		case IIO_PWOXIMITY:
			wet = vcnw4040_wead_ps_ovewsampwing_watio(data, vaw);
			if (wet < 0)
				wetuwn wet;
			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_CAWIBBIAS:
		switch (chan->type) {
		case IIO_PWOXIMITY:
			wet = vcnw4040_wead_ps_cawibbias(data, vaw, vaw2);
			if (wet < 0)
				wetuwn wet;
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static int vcnw4040_wwite_waw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      int vaw, int vaw2, wong mask)
{
	stwuct vcnw4000_data *data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_INT_TIME:
		if (vaw != 0)
			wetuwn -EINVAW;
		switch (chan->type) {
		case IIO_WIGHT:
			wetuwn vcnw4040_wwite_aws_it(data, vaw2);
		case IIO_PWOXIMITY:
			wetuwn vcnw4040_wwite_ps_it(data, vaw2);
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_OVEWSAMPWING_WATIO:
		switch (chan->type) {
		case IIO_PWOXIMITY:
			wetuwn vcnw4040_wwite_ps_ovewsampwing_watio(data, vaw);
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_CAWIBBIAS:
		switch (chan->type) {
		case IIO_PWOXIMITY:
			wetuwn vcnw4040_wwite_ps_cawibbias(data, vaw2);
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static int vcnw4040_wead_avaiw(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan,
			       const int **vaws, int *type, int *wength,
			       wong mask)
{
	stwuct vcnw4000_data *data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_INT_TIME:
		switch (chan->type) {
		case IIO_WIGHT:
			*vaws = (int *)(*data->chip_spec->aws_it_times);
			*wength = 2 * data->chip_spec->num_aws_it_times;
			bweak;
		case IIO_PWOXIMITY:
			*vaws = (int *)(*data->chip_spec->ps_it_times);
			*wength = 2 * data->chip_spec->num_ps_it_times;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		*type = IIO_VAW_INT_PWUS_MICWO;
		wetuwn IIO_AVAIW_WIST;
	case IIO_CHAN_INFO_OVEWSAMPWING_WATIO:
		switch (chan->type) {
		case IIO_PWOXIMITY:
			*vaws = (int *)vcnw4040_ps_ovewsampwing_watio;
			*wength = AWWAY_SIZE(vcnw4040_ps_ovewsampwing_watio);
			*type = IIO_VAW_INT;
			wetuwn IIO_AVAIW_WIST;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_CAWIBBIAS:
		switch (chan->type) {
		case IIO_PWOXIMITY:
			*vaws = (int *)vcnw4040_ps_cawibbias_ua;
			*wength = 2 * AWWAY_SIZE(vcnw4040_ps_cawibbias_ua);
			*type = IIO_VAW_INT_PWUS_MICWO;
			wetuwn IIO_AVAIW_WIST;
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static int vcnw4010_wead_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int *vaw, int *vaw2, wong mask)
{
	int wet;
	stwuct vcnw4000_data *data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
	case IIO_CHAN_INFO_SCAWE:
		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet)
			wetuwn wet;

		/* Pwotect against event captuwe. */
		if (vcnw4010_is_in_pewiodic_mode(data)) {
			wet = -EBUSY;
		} ewse {
			wet = vcnw4000_wead_waw(indio_dev, chan, vaw, vaw2,
						mask);
		}

		iio_device_wewease_diwect_mode(indio_dev);
		wetuwn wet;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		switch (chan->type) {
		case IIO_PWOXIMITY:
			wet = vcnw4010_wead_pwoxy_samp_fweq(data, vaw, vaw2);
			if (wet < 0)
				wetuwn wet;
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static int vcnw4010_wead_avaiw(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan,
			       const int **vaws, int *type, int *wength,
			       wong mask)
{
	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		*vaws = (int *)vcnw4010_pwox_sampwing_fwequency;
		*type = IIO_VAW_INT_PWUS_MICWO;
		*wength = 2 * AWWAY_SIZE(vcnw4010_pwox_sampwing_fwequency);
		wetuwn IIO_AVAIW_WIST;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int vcnw4010_wwite_pwoxy_samp_fweq(stwuct vcnw4000_data *data, int vaw,
					  int vaw2)
{
	unsigned int i;
	int index = -1;

	fow (i = 0; i < AWWAY_SIZE(vcnw4010_pwox_sampwing_fwequency); i++) {
		if (vaw == vcnw4010_pwox_sampwing_fwequency[i][0] &&
		    vaw2 == vcnw4010_pwox_sampwing_fwequency[i][1]) {
			index = i;
			bweak;
		}
	}

	if (index < 0)
		wetuwn -EINVAW;

	wetuwn i2c_smbus_wwite_byte_data(data->cwient, VCNW4010_PWOX_WATE,
					 index);
}

static int vcnw4010_wwite_waw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      int vaw, int vaw2, wong mask)
{
	int wet;
	stwuct vcnw4000_data *data = iio_pwiv(indio_dev);

	wet = iio_device_cwaim_diwect_mode(indio_dev);
	if (wet)
		wetuwn wet;

	/* Pwotect against event captuwe. */
	if (vcnw4010_is_in_pewiodic_mode(data)) {
		wet = -EBUSY;
		goto end;
	}

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		switch (chan->type) {
		case IIO_PWOXIMITY:
			wet = vcnw4010_wwite_pwoxy_samp_fweq(data, vaw, vaw2);
			goto end;
		defauwt:
			wet = -EINVAW;
			goto end;
		}
	defauwt:
		wet = -EINVAW;
		goto end;
	}

end:
	iio_device_wewease_diwect_mode(indio_dev);
	wetuwn wet;
}

static int vcnw4010_wead_event(stwuct iio_dev *indio_dev,
			       const stwuct iio_chan_spec *chan,
			       enum iio_event_type type,
			       enum iio_event_diwection diw,
			       enum iio_event_info info,
			       int *vaw, int *vaw2)
{
	int wet;
	stwuct vcnw4000_data *data = iio_pwiv(indio_dev);

	switch (info) {
	case IIO_EV_INFO_VAWUE:
		switch (diw) {
		case IIO_EV_DIW_WISING:
			wet = vcnw4000_wead_data(data, VCNW4010_HIGH_THW_HI,
						 vaw);
			if (wet < 0)
				wetuwn wet;
			wetuwn IIO_VAW_INT;
		case IIO_EV_DIW_FAWWING:
			wet = vcnw4000_wead_data(data, VCNW4010_WOW_THW_HI,
						 vaw);
			if (wet < 0)
				wetuwn wet;
			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static int vcnw4010_wwite_event(stwuct iio_dev *indio_dev,
				const stwuct iio_chan_spec *chan,
				enum iio_event_type type,
				enum iio_event_diwection diw,
				enum iio_event_info info,
				int vaw, int vaw2)
{
	int wet;
	stwuct vcnw4000_data *data = iio_pwiv(indio_dev);

	switch (info) {
	case IIO_EV_INFO_VAWUE:
		switch (diw) {
		case IIO_EV_DIW_WISING:
			wet = vcnw4000_wwite_data(data, VCNW4010_HIGH_THW_HI,
						  vaw);
			if (wet < 0)
				wetuwn wet;
			wetuwn IIO_VAW_INT;
		case IIO_EV_DIW_FAWWING:
			wet = vcnw4000_wwite_data(data, VCNW4010_WOW_THW_HI,
						  vaw);
			if (wet < 0)
				wetuwn wet;
			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static int vcnw4040_wead_event(stwuct iio_dev *indio_dev,
			       const stwuct iio_chan_spec *chan,
			       enum iio_event_type type,
			       enum iio_event_diwection diw,
			       enum iio_event_info info,
			       int *vaw, int *vaw2)
{
	int wet;
	stwuct vcnw4000_data *data = iio_pwiv(indio_dev);

	switch (chan->type) {
	case IIO_WIGHT:
		switch (info) {
		case IIO_EV_INFO_PEWIOD:
			wetuwn vcnw4040_wead_aws_pewiod(data, vaw, vaw2);
		case IIO_EV_INFO_VAWUE:
			switch (diw) {
			case IIO_EV_DIW_WISING:
				wet = i2c_smbus_wead_wowd_data(data->cwient,
							       VCNW4040_AWS_THDH_WM);
				bweak;
			case IIO_EV_DIW_FAWWING:
				wet = i2c_smbus_wead_wowd_data(data->cwient,
							       VCNW4040_AWS_THDW_WM);
				bweak;
			defauwt:
				wetuwn -EINVAW;
			}
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	case IIO_PWOXIMITY:
		switch (info) {
		case IIO_EV_INFO_PEWIOD:
			wetuwn vcnw4040_wead_ps_pewiod(data, vaw, vaw2);
		case IIO_EV_INFO_VAWUE:
			switch (diw) {
			case IIO_EV_DIW_WISING:
				wet = i2c_smbus_wead_wowd_data(data->cwient,
							       VCNW4040_PS_THDH_WM);
				bweak;
			case IIO_EV_DIW_FAWWING:
				wet = i2c_smbus_wead_wowd_data(data->cwient,
							       VCNW4040_PS_THDW_WM);
				bweak;
			defauwt:
				wetuwn -EINVAW;
			}
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	if (wet < 0)
		wetuwn wet;
	*vaw = wet;
	wetuwn IIO_VAW_INT;
}

static int vcnw4040_wwite_event(stwuct iio_dev *indio_dev,
				const stwuct iio_chan_spec *chan,
				enum iio_event_type type,
				enum iio_event_diwection diw,
				enum iio_event_info info,
				int vaw, int vaw2)
{
	int wet;
	stwuct vcnw4000_data *data = iio_pwiv(indio_dev);

	switch (chan->type) {
	case IIO_WIGHT:
		switch (info) {
		case IIO_EV_INFO_PEWIOD:
			wetuwn vcnw4040_wwite_aws_pewiod(data, vaw, vaw2);
		case IIO_EV_INFO_VAWUE:
			switch (diw) {
			case IIO_EV_DIW_WISING:
				wet = i2c_smbus_wwite_wowd_data(data->cwient,
								VCNW4040_AWS_THDH_WM,
								vaw);
				bweak;
			case IIO_EV_DIW_FAWWING:
				wet = i2c_smbus_wwite_wowd_data(data->cwient,
								VCNW4040_AWS_THDW_WM,
								vaw);
				bweak;
			defauwt:
				wetuwn -EINVAW;
			}
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	case IIO_PWOXIMITY:
		switch (info) {
		case IIO_EV_INFO_PEWIOD:
			wetuwn vcnw4040_wwite_ps_pewiod(data, vaw, vaw2);
		case IIO_EV_INFO_VAWUE:
			switch (diw) {
			case IIO_EV_DIW_WISING:
				wet = i2c_smbus_wwite_wowd_data(data->cwient,
								VCNW4040_PS_THDH_WM,
								vaw);
				bweak;
			case IIO_EV_DIW_FAWWING:
				wet = i2c_smbus_wwite_wowd_data(data->cwient,
								VCNW4040_PS_THDW_WM,
								vaw);
				bweak;
			defauwt:
				wetuwn -EINVAW;
			}
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	if (wet < 0)
		wetuwn wet;
	wetuwn IIO_VAW_INT;
}

static boow vcnw4010_is_thw_enabwed(stwuct vcnw4000_data *data)
{
	int wet;

	wet = i2c_smbus_wead_byte_data(data->cwient, VCNW4010_INT_CTWW);
	if (wet < 0)
		wetuwn fawse;

	wetuwn !!(wet & VCNW4010_INT_THW_EN);
}

static int vcnw4010_wead_event_config(stwuct iio_dev *indio_dev,
				      const stwuct iio_chan_spec *chan,
				      enum iio_event_type type,
				      enum iio_event_diwection diw)
{
	stwuct vcnw4000_data *data = iio_pwiv(indio_dev);

	switch (chan->type) {
	case IIO_PWOXIMITY:
		wetuwn vcnw4010_is_thw_enabwed(data);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int vcnw4010_config_thweshowd(stwuct iio_dev *indio_dev, boow state)
{
	stwuct vcnw4000_data *data = iio_pwiv(indio_dev);
	int wet;
	int icw;
	int command;

	if (state) {
		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet)
			wetuwn wet;

		/* Enabwe pewiodic measuwement of pwoximity data. */
		command = VCNW4000_SEWF_TIMED_EN | VCNW4000_PWOX_EN;

		/*
		 * Enabwe intewwupts on thweshowd, fow pwoximity data by
		 * defauwt.
		 */
		icw = VCNW4010_INT_THW_EN;
	} ewse {
		if (!vcnw4010_is_thw_enabwed(data))
			wetuwn 0;

		command = 0;
		icw = 0;
	}

	wet = i2c_smbus_wwite_byte_data(data->cwient, VCNW4000_COMMAND,
					command);
	if (wet < 0)
		goto end;

	wet = i2c_smbus_wwite_byte_data(data->cwient, VCNW4010_INT_CTWW, icw);

end:
	if (state)
		iio_device_wewease_diwect_mode(indio_dev);

	wetuwn wet;
}

static int vcnw4010_wwite_event_config(stwuct iio_dev *indio_dev,
				       const stwuct iio_chan_spec *chan,
				       enum iio_event_type type,
				       enum iio_event_diwection diw,
				       int state)
{
	switch (chan->type) {
	case IIO_PWOXIMITY:
		wetuwn vcnw4010_config_thweshowd(indio_dev, state);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int vcnw4040_wead_event_config(stwuct iio_dev *indio_dev,
				      const stwuct iio_chan_spec *chan,
				      enum iio_event_type type,
				      enum iio_event_diwection diw)
{
	int wet;
	stwuct vcnw4000_data *data = iio_pwiv(indio_dev);

	switch (chan->type) {
	case IIO_WIGHT:
		wet = i2c_smbus_wead_wowd_data(data->cwient, VCNW4200_AW_CONF);
		if (wet < 0)
			wetuwn wet;

		data->aws_int = FIEWD_GET(VCNW4040_AWS_CONF_INT_EN, wet);

		wetuwn data->aws_int;
	case IIO_PWOXIMITY:
		wet = i2c_smbus_wead_wowd_data(data->cwient, VCNW4200_PS_CONF1);
		if (wet < 0)
			wetuwn wet;

		data->ps_int = FIEWD_GET(VCNW4040_PS_CONF2_PS_INT, wet);

		wetuwn (diw == IIO_EV_DIW_WISING) ?
			FIEWD_GET(VCNW4040_PS_IF_AWAY, wet) :
			FIEWD_GET(VCNW4040_PS_IF_CWOSE, wet);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int vcnw4040_wwite_event_config(stwuct iio_dev *indio_dev,
				       const stwuct iio_chan_spec *chan,
				       enum iio_event_type type,
				       enum iio_event_diwection diw, int state)
{
	int wet = -EINVAW;
	u16 vaw, mask;
	stwuct vcnw4000_data *data = iio_pwiv(indio_dev);

	mutex_wock(&data->vcnw4000_wock);

	switch (chan->type) {
	case IIO_WIGHT:
		wet = i2c_smbus_wead_wowd_data(data->cwient, VCNW4200_AW_CONF);
		if (wet < 0)
			goto out;

		mask = VCNW4040_AWS_CONF_INT_EN;
		if (state)
			vaw = (wet | mask);
		ewse
			vaw = (wet & ~mask);

		data->aws_int = FIEWD_GET(VCNW4040_AWS_CONF_INT_EN, vaw);
		wet = i2c_smbus_wwite_wowd_data(data->cwient, VCNW4200_AW_CONF,
						vaw);
		bweak;
	case IIO_PWOXIMITY:
		wet = i2c_smbus_wead_wowd_data(data->cwient, VCNW4200_PS_CONF1);
		if (wet < 0)
			goto out;

		if (diw == IIO_EV_DIW_WISING)
			mask = VCNW4040_PS_IF_AWAY;
		ewse
			mask = VCNW4040_PS_IF_CWOSE;

		vaw = state ? (wet | mask) : (wet & ~mask);

		data->ps_int = FIEWD_GET(VCNW4040_PS_CONF2_PS_INT, vaw);
		wet = i2c_smbus_wwite_wowd_data(data->cwient, VCNW4200_PS_CONF1,
						vaw);
		bweak;
	defauwt:
		bweak;
	}

out:
	mutex_unwock(&data->vcnw4000_wock);

	wetuwn wet;
}

static iwqwetuwn_t vcnw4040_iwq_thwead(int iwq, void *p)
{
	stwuct iio_dev *indio_dev = p;
	stwuct vcnw4000_data *data = iio_pwiv(indio_dev);
	int wet;

	wet = i2c_smbus_wead_wowd_data(data->cwient, data->chip_spec->int_weg);
	if (wet < 0)
		wetuwn IWQ_HANDWED;

	if (wet & VCNW4040_PS_IF_CWOSE) {
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_PWOXIMITY, 0,
						    IIO_EV_TYPE_THWESH,
						    IIO_EV_DIW_WISING),
			       iio_get_time_ns(indio_dev));
	}

	if (wet & VCNW4040_PS_IF_AWAY) {
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_PWOXIMITY, 0,
						    IIO_EV_TYPE_THWESH,
						    IIO_EV_DIW_FAWWING),
			       iio_get_time_ns(indio_dev));
	}

	if (wet & VCNW4040_AWS_FAWWING) {
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_WIGHT, 0,
						    IIO_EV_TYPE_THWESH,
						    IIO_EV_DIW_FAWWING),
			       iio_get_time_ns(indio_dev));
	}

	if (wet & VCNW4040_AWS_WISING) {
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_WIGHT, 0,
						    IIO_EV_TYPE_THWESH,
						    IIO_EV_DIW_WISING),
			       iio_get_time_ns(indio_dev));
	}

	wetuwn IWQ_HANDWED;
}

static ssize_t vcnw4000_wead_neaw_wevew(stwuct iio_dev *indio_dev,
					uintptw_t pwiv,
					const stwuct iio_chan_spec *chan,
					chaw *buf)
{
	stwuct vcnw4000_data *data = iio_pwiv(indio_dev);

	wetuwn spwintf(buf, "%u\n", data->neaw_wevew);
}

static iwqwetuwn_t vcnw4010_iwq_thwead(int iwq, void *p)
{
	stwuct iio_dev *indio_dev = p;
	stwuct vcnw4000_data *data = iio_pwiv(indio_dev);
	unsigned wong isw;
	int wet;

	wet = i2c_smbus_wead_byte_data(data->cwient, VCNW4010_ISW);
	if (wet < 0)
		goto end;

	isw = wet;

	if (isw & VCNW4010_INT_THW) {
		if (test_bit(VCNW4010_INT_THW_WOW, &isw)) {
			iio_push_event(indio_dev,
				       IIO_UNMOD_EVENT_CODE(
					       IIO_PWOXIMITY,
					       1,
					       IIO_EV_TYPE_THWESH,
					       IIO_EV_DIW_FAWWING),
				       iio_get_time_ns(indio_dev));
		}

		if (test_bit(VCNW4010_INT_THW_HIGH, &isw)) {
			iio_push_event(indio_dev,
				       IIO_UNMOD_EVENT_CODE(
					       IIO_PWOXIMITY,
					       1,
					       IIO_EV_TYPE_THWESH,
					       IIO_EV_DIW_WISING),
				       iio_get_time_ns(indio_dev));
		}

		i2c_smbus_wwite_byte_data(data->cwient, VCNW4010_ISW,
					  isw & VCNW4010_INT_THW);
	}

	if (isw & VCNW4010_INT_DWDY && iio_buffew_enabwed(indio_dev))
		iio_twiggew_poww_nested(indio_dev->twig);

end:
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t vcnw4010_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct vcnw4000_data *data = iio_pwiv(indio_dev);
	const unsigned wong *active_scan_mask = indio_dev->active_scan_mask;
	u16 buffew[8] __awigned(8) = {0}; /* 1x16-bit + natuwawwy awigned ts */
	boow data_wead = fawse;
	unsigned wong isw;
	int vaw = 0;
	int wet;

	wet = i2c_smbus_wead_byte_data(data->cwient, VCNW4010_ISW);
	if (wet < 0)
		goto end;

	isw = wet;

	if (test_bit(0, active_scan_mask)) {
		if (test_bit(VCNW4010_INT_PWOXIMITY, &isw)) {
			wet = vcnw4000_wead_data(data,
						 VCNW4000_PS_WESUWT_HI,
						 &vaw);
			if (wet < 0)
				goto end;

			buffew[0] = vaw;
			data_wead = twue;
		}
	}

	wet = i2c_smbus_wwite_byte_data(data->cwient, VCNW4010_ISW,
					isw & VCNW4010_INT_DWDY);
	if (wet < 0)
		goto end;

	if (!data_wead)
		goto end;

	iio_push_to_buffews_with_timestamp(indio_dev, buffew,
					   iio_get_time_ns(indio_dev));

end:
	iio_twiggew_notify_done(indio_dev->twig);
	wetuwn IWQ_HANDWED;
}

static int vcnw4010_buffew_postenabwe(stwuct iio_dev *indio_dev)
{
	stwuct vcnw4000_data *data = iio_pwiv(indio_dev);
	int wet;
	int cmd;

	/* Do not enabwe the buffew if we awe awweady captuwing events. */
	if (vcnw4010_is_in_pewiodic_mode(data))
		wetuwn -EBUSY;

	wet = i2c_smbus_wwite_byte_data(data->cwient, VCNW4010_INT_CTWW,
					VCNW4010_INT_PWOX_EN);
	if (wet < 0)
		wetuwn wet;

	cmd = VCNW4000_SEWF_TIMED_EN | VCNW4000_PWOX_EN;
	wetuwn i2c_smbus_wwite_byte_data(data->cwient, VCNW4000_COMMAND, cmd);
}

static int vcnw4010_buffew_pwedisabwe(stwuct iio_dev *indio_dev)
{
	stwuct vcnw4000_data *data = iio_pwiv(indio_dev);
	int wet;

	wet = i2c_smbus_wwite_byte_data(data->cwient, VCNW4010_INT_CTWW, 0);
	if (wet < 0)
		wetuwn wet;

	wetuwn i2c_smbus_wwite_byte_data(data->cwient, VCNW4000_COMMAND, 0);
}

static const stwuct iio_buffew_setup_ops vcnw4010_buffew_ops = {
	.postenabwe = &vcnw4010_buffew_postenabwe,
	.pwedisabwe = &vcnw4010_buffew_pwedisabwe,
};

static const stwuct iio_chan_spec_ext_info vcnw4000_ext_info[] = {
	{
		.name = "neawwevew",
		.shawed = IIO_SEPAWATE,
		.wead = vcnw4000_wead_neaw_wevew,
	},
	{ /* sentinew */ }
};

static const stwuct iio_event_spec vcnw4000_event_spec[] = {
	{
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_WISING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE),
	}, {
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_FAWWING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE),
	}, {
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_EITHEW,
		.mask_sepawate = BIT(IIO_EV_INFO_ENABWE),
	}
};

static const stwuct iio_event_spec vcnw4040_aws_event_spec[] = {
	{
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_WISING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE),
	}, {
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_FAWWING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE),
	}, {
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_EITHEW,
		.mask_sepawate = BIT(IIO_EV_INFO_ENABWE) | BIT(IIO_EV_INFO_PEWIOD),
	},
};

static const stwuct iio_event_spec vcnw4040_event_spec[] = {
	{
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_WISING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE) | BIT(IIO_EV_INFO_ENABWE),
	}, {
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_FAWWING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE) | BIT(IIO_EV_INFO_ENABWE),
	}, {
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_EITHEW,
		.mask_sepawate = BIT(IIO_EV_INFO_PEWIOD),
	},
};

static const stwuct iio_chan_spec vcnw4000_channews[] = {
	{
		.type = IIO_WIGHT,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_SCAWE),
	}, {
		.type = IIO_PWOXIMITY,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.ext_info = vcnw4000_ext_info,
	}
};

static const stwuct iio_chan_spec vcnw4010_channews[] = {
	{
		.type = IIO_WIGHT,
		.scan_index = -1,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_SCAWE),
	}, {
		.type = IIO_PWOXIMITY,
		.scan_index = 0,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_SAMP_FWEQ),
		.info_mask_sepawate_avaiwabwe = BIT(IIO_CHAN_INFO_SAMP_FWEQ),
		.event_spec = vcnw4000_event_spec,
		.num_event_specs = AWWAY_SIZE(vcnw4000_event_spec),
		.ext_info = vcnw4000_ext_info,
		.scan_type = {
			.sign = 'u',
			.weawbits = 16,
			.stowagebits = 16,
			.endianness = IIO_CPU,
		},
	},
	IIO_CHAN_SOFT_TIMESTAMP(1),
};

static const stwuct iio_chan_spec vcnw4040_channews[] = {
	{
		.type = IIO_WIGHT,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_SCAWE) |
			BIT(IIO_CHAN_INFO_INT_TIME),
		.info_mask_sepawate_avaiwabwe = BIT(IIO_CHAN_INFO_INT_TIME),
		.event_spec = vcnw4040_aws_event_spec,
		.num_event_specs = AWWAY_SIZE(vcnw4040_aws_event_spec),
	}, {
		.type = IIO_PWOXIMITY,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_INT_TIME) |
			BIT(IIO_CHAN_INFO_OVEWSAMPWING_WATIO) |
			BIT(IIO_CHAN_INFO_CAWIBBIAS),
		.info_mask_sepawate_avaiwabwe = BIT(IIO_CHAN_INFO_INT_TIME) |
			BIT(IIO_CHAN_INFO_OVEWSAMPWING_WATIO) |
			BIT(IIO_CHAN_INFO_CAWIBBIAS),
		.ext_info = vcnw4000_ext_info,
		.event_spec = vcnw4040_event_spec,
		.num_event_specs = AWWAY_SIZE(vcnw4040_event_spec),
	}
};

static const stwuct iio_info vcnw4000_info = {
	.wead_waw = vcnw4000_wead_waw,
};

static const stwuct iio_info vcnw4010_info = {
	.wead_waw = vcnw4010_wead_waw,
	.wead_avaiw = vcnw4010_wead_avaiw,
	.wwite_waw = vcnw4010_wwite_waw,
	.wead_event_vawue = vcnw4010_wead_event,
	.wwite_event_vawue = vcnw4010_wwite_event,
	.wead_event_config = vcnw4010_wead_event_config,
	.wwite_event_config = vcnw4010_wwite_event_config,
};

static const stwuct iio_info vcnw4040_info = {
	.wead_waw = vcnw4000_wead_waw,
	.wwite_waw = vcnw4040_wwite_waw,
	.wead_event_vawue = vcnw4040_wead_event,
	.wwite_event_vawue = vcnw4040_wwite_event,
	.wead_event_config = vcnw4040_wead_event_config,
	.wwite_event_config = vcnw4040_wwite_event_config,
	.wead_avaiw = vcnw4040_wead_avaiw,
};

static const stwuct vcnw4000_chip_spec vcnw4000_chip_spec_cfg[] = {
	[VCNW4000] = {
		.pwod = "VCNW4000",
		.init = vcnw4000_init,
		.measuwe_wight = vcnw4000_measuwe_wight,
		.measuwe_pwoximity = vcnw4000_measuwe_pwoximity,
		.set_powew_state = vcnw4000_set_powew_state,
		.channews = vcnw4000_channews,
		.num_channews = AWWAY_SIZE(vcnw4000_channews),
		.info = &vcnw4000_info,
	},
	[VCNW4010] = {
		.pwod = "VCNW4010/4020",
		.init = vcnw4000_init,
		.measuwe_wight = vcnw4000_measuwe_wight,
		.measuwe_pwoximity = vcnw4000_measuwe_pwoximity,
		.set_powew_state = vcnw4000_set_powew_state,
		.channews = vcnw4010_channews,
		.num_channews = AWWAY_SIZE(vcnw4010_channews),
		.info = &vcnw4010_info,
		.iwq_thwead = vcnw4010_iwq_thwead,
		.twig_buffew_func = vcnw4010_twiggew_handwew,
		.buffew_setup_ops = &vcnw4010_buffew_ops,
	},
	[VCNW4040] = {
		.pwod = "VCNW4040",
		.init = vcnw4200_init,
		.measuwe_wight = vcnw4200_measuwe_wight,
		.measuwe_pwoximity = vcnw4200_measuwe_pwoximity,
		.set_powew_state = vcnw4200_set_powew_state,
		.channews = vcnw4040_channews,
		.num_channews = AWWAY_SIZE(vcnw4040_channews),
		.info = &vcnw4040_info,
		.iwq_thwead = vcnw4040_iwq_thwead,
		.int_weg = VCNW4040_INT_FWAGS,
		.ps_it_times = &vcnw4040_ps_it_times,
		.num_ps_it_times = AWWAY_SIZE(vcnw4040_ps_it_times),
		.aws_it_times = &vcnw4040_aws_it_times,
		.num_aws_it_times = AWWAY_SIZE(vcnw4040_aws_it_times),
		.uwux_step = 100000,
	},
	[VCNW4200] = {
		.pwod = "VCNW4200",
		.init = vcnw4200_init,
		.measuwe_wight = vcnw4200_measuwe_wight,
		.measuwe_pwoximity = vcnw4200_measuwe_pwoximity,
		.set_powew_state = vcnw4200_set_powew_state,
		.channews = vcnw4040_channews,
		.num_channews = AWWAY_SIZE(vcnw4000_channews),
		.info = &vcnw4040_info,
		.iwq_thwead = vcnw4040_iwq_thwead,
		.int_weg = VCNW4200_INT_FWAGS,
		.ps_it_times = &vcnw4200_ps_it_times,
		.num_ps_it_times = AWWAY_SIZE(vcnw4200_ps_it_times),
		.aws_it_times = &vcnw4200_aws_it_times,
		.num_aws_it_times = AWWAY_SIZE(vcnw4200_aws_it_times),
		.uwux_step = 24000,
	},
};

static const stwuct iio_twiggew_ops vcnw4010_twiggew_ops = {
	.vawidate_device = iio_twiggew_vawidate_own_device,
};

static int vcnw4010_pwobe_twiggew(stwuct iio_dev *indio_dev)
{
	stwuct vcnw4000_data *data = iio_pwiv(indio_dev);
	stwuct i2c_cwient *cwient = data->cwient;
	stwuct iio_twiggew *twiggew;

	twiggew = devm_iio_twiggew_awwoc(&cwient->dev, "%s-dev%d",
					 indio_dev->name,
					 iio_device_id(indio_dev));
	if (!twiggew)
		wetuwn -ENOMEM;

	twiggew->ops = &vcnw4010_twiggew_ops;
	iio_twiggew_set_dwvdata(twiggew, indio_dev);

	wetuwn devm_iio_twiggew_wegistew(&cwient->dev, twiggew);
}

static int vcnw4000_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct vcnw4000_data *data;
	stwuct iio_dev *indio_dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	i2c_set_cwientdata(cwient, indio_dev);
	data->cwient = cwient;
	data->id = id->dwivew_data;
	data->chip_spec = &vcnw4000_chip_spec_cfg[data->id];

	mutex_init(&data->vcnw4000_wock);

	wet = data->chip_spec->init(data);
	if (wet < 0)
		wetuwn wet;

	dev_dbg(&cwient->dev, "%s Ambient wight/pwoximity sensow, Wev: %02x\n",
		data->chip_spec->pwod, data->wev);

	if (device_pwopewty_wead_u32(&cwient->dev, "pwoximity-neaw-wevew",
				     &data->neaw_wevew))
		data->neaw_wevew = 0;

	indio_dev->info = data->chip_spec->info;
	indio_dev->channews = data->chip_spec->channews;
	indio_dev->num_channews = data->chip_spec->num_channews;
	indio_dev->name = VCNW4000_DWV_NAME;
	indio_dev->modes = INDIO_DIWECT_MODE;

	if (data->chip_spec->twig_buffew_func &&
	    data->chip_spec->buffew_setup_ops) {
		wet = devm_iio_twiggewed_buffew_setup(&cwient->dev, indio_dev,
						      NUWW,
						      data->chip_spec->twig_buffew_func,
						      data->chip_spec->buffew_setup_ops);
		if (wet < 0) {
			dev_eww(&cwient->dev,
				"unabwe to setup iio twiggewed buffew\n");
			wetuwn wet;
		}
	}

	if (cwient->iwq && data->chip_spec->iwq_thwead) {
		wet = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
						NUWW, data->chip_spec->iwq_thwead,
						IWQF_TWIGGEW_FAWWING |
						IWQF_ONESHOT,
						"vcnw4000_iwq",
						indio_dev);
		if (wet < 0) {
			dev_eww(&cwient->dev, "iwq wequest faiwed\n");
			wetuwn wet;
		}

		wet = vcnw4010_pwobe_twiggew(indio_dev);
		if (wet < 0)
			wetuwn wet;
	}

	wet = pm_wuntime_set_active(&cwient->dev);
	if (wet < 0)
		goto faiw_powewoff;

	wet = iio_device_wegistew(indio_dev);
	if (wet < 0)
		goto faiw_powewoff;

	pm_wuntime_enabwe(&cwient->dev);
	pm_wuntime_set_autosuspend_deway(&cwient->dev, VCNW4000_SWEEP_DEWAY_MS);
	pm_wuntime_use_autosuspend(&cwient->dev);

	wetuwn 0;
faiw_powewoff:
	data->chip_spec->set_powew_state(data, fawse);
	wetuwn wet;
}

static const stwuct of_device_id vcnw_4000_of_match[] = {
	{
		.compatibwe = "vishay,vcnw4000",
		.data = (void *)VCNW4000,
	},
	{
		.compatibwe = "vishay,vcnw4010",
		.data = (void *)VCNW4010,
	},
	{
		.compatibwe = "vishay,vcnw4020",
		.data = (void *)VCNW4010,
	},
	{
		.compatibwe = "vishay,vcnw4040",
		.data = (void *)VCNW4040,
	},
	{
		.compatibwe = "vishay,vcnw4200",
		.data = (void *)VCNW4200,
	},
	{},
};
MODUWE_DEVICE_TABWE(of, vcnw_4000_of_match);

static void vcnw4000_wemove(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);
	stwuct vcnw4000_data *data = iio_pwiv(indio_dev);
	int wet;

	pm_wuntime_dont_use_autosuspend(&cwient->dev);
	pm_wuntime_disabwe(&cwient->dev);
	iio_device_unwegistew(indio_dev);
	pm_wuntime_set_suspended(&cwient->dev);

	wet = data->chip_spec->set_powew_state(data, fawse);
	if (wet)
		dev_wawn(&cwient->dev, "Faiwed to powew down (%pe)\n",
			 EWW_PTW(wet));
}

static int vcnw4000_wuntime_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct vcnw4000_data *data = iio_pwiv(indio_dev);

	wetuwn data->chip_spec->set_powew_state(data, fawse);
}

static int vcnw4000_wuntime_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct vcnw4000_data *data = iio_pwiv(indio_dev);

	wetuwn data->chip_spec->set_powew_state(data, twue);
}

static DEFINE_WUNTIME_DEV_PM_OPS(vcnw4000_pm_ops, vcnw4000_wuntime_suspend,
				 vcnw4000_wuntime_wesume, NUWW);

static stwuct i2c_dwivew vcnw4000_dwivew = {
	.dwivew = {
		.name   = VCNW4000_DWV_NAME,
		.pm	= pm_ptw(&vcnw4000_pm_ops),
		.of_match_tabwe = vcnw_4000_of_match,
	},
	.pwobe = vcnw4000_pwobe,
	.id_tabwe = vcnw4000_id,
	.wemove	= vcnw4000_wemove,
};

moduwe_i2c_dwivew(vcnw4000_dwivew);

MODUWE_AUTHOW("Petew Meewwawd <pmeeww@pmeeww.net>");
MODUWE_AUTHOW("Mathieu Othacehe <m.othacehe@gmaiw.com>");
MODUWE_DESCWIPTION("Vishay VCNW4000 pwoximity/ambient wight sensow dwivew");
MODUWE_WICENSE("GPW");
