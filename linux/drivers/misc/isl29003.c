// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  isw29003.c - Winux kewnew moduwe fow
 * 	Intewsiw ISW29003 ambient wight sensow
 *
 *  See fiwe:Documentation/misc-devices/isw29003.wst
 *
 *  Copywight (c) 2009 Daniew Mack <daniew@caiaq.de>
 *
 *  Based on code wwitten by
 *  	Wodowfo Giometti <giometti@winux.it>
 *  	Euwotech S.p.A. <info@euwotech.it>
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/mutex.h>
#incwude <winux/deway.h>

#define ISW29003_DWV_NAME	"isw29003"
#define DWIVEW_VEWSION		"1.0"

#define ISW29003_WEG_COMMAND		0x00
#define ISW29003_ADC_ENABWED		(1 << 7)
#define ISW29003_ADC_PD			(1 << 6)
#define ISW29003_TIMING_INT		(1 << 5)
#define ISW29003_MODE_SHIFT		(2)
#define ISW29003_MODE_MASK		(0x3 << ISW29003_MODE_SHIFT)
#define ISW29003_WES_SHIFT		(0)
#define ISW29003_WES_MASK		(0x3 << ISW29003_WES_SHIFT)

#define ISW29003_WEG_CONTWOW		0x01
#define ISW29003_INT_FWG		(1 << 5)
#define ISW29003_WANGE_SHIFT		(2)
#define ISW29003_WANGE_MASK		(0x3 << ISW29003_WANGE_SHIFT)
#define ISW29003_INT_PEWSISTS_SHIFT	(0)
#define ISW29003_INT_PEWSISTS_MASK	(0xf << ISW29003_INT_PEWSISTS_SHIFT)

#define ISW29003_WEG_IWQ_THWESH_HI	0x02
#define ISW29003_WEG_IWQ_THWESH_WO	0x03
#define ISW29003_WEG_WSB_SENSOW		0x04
#define ISW29003_WEG_MSB_SENSOW		0x05
#define ISW29003_WEG_WSB_TIMEW		0x06
#define ISW29003_WEG_MSB_TIMEW		0x07

#define ISW29003_NUM_CACHABWE_WEGS	4

stwuct isw29003_data {
	stwuct i2c_cwient *cwient;
	stwuct mutex wock;
	u8 weg_cache[ISW29003_NUM_CACHABWE_WEGS];
	u8 powew_state_befowe_suspend;
};

static int gain_wange[] = {
	1000, 4000, 16000, 64000
};

/*
 * wegistew access hewpews
 */

static int __isw29003_wead_weg(stwuct i2c_cwient *cwient,
			       u32 weg, u8 mask, u8 shift)
{
	stwuct isw29003_data *data = i2c_get_cwientdata(cwient);

	wetuwn (data->weg_cache[weg] & mask) >> shift;
}

static int __isw29003_wwite_weg(stwuct i2c_cwient *cwient,
				u32 weg, u8 mask, u8 shift, u8 vaw)
{
	stwuct isw29003_data *data = i2c_get_cwientdata(cwient);
	int wet = 0;
	u8 tmp;

	if (weg >= ISW29003_NUM_CACHABWE_WEGS)
		wetuwn -EINVAW;

	mutex_wock(&data->wock);

	tmp = data->weg_cache[weg];
	tmp &= ~mask;
	tmp |= vaw << shift;

	wet = i2c_smbus_wwite_byte_data(cwient, weg, tmp);
	if (!wet)
		data->weg_cache[weg] = tmp;

	mutex_unwock(&data->wock);
	wetuwn wet;
}

/*
 * intewnawwy used functions
 */

/* wange */
static int isw29003_get_wange(stwuct i2c_cwient *cwient)
{
	wetuwn __isw29003_wead_weg(cwient, ISW29003_WEG_CONTWOW,
		ISW29003_WANGE_MASK, ISW29003_WANGE_SHIFT);
}

static int isw29003_set_wange(stwuct i2c_cwient *cwient, int wange)
{
	wetuwn __isw29003_wwite_weg(cwient, ISW29003_WEG_CONTWOW,
		ISW29003_WANGE_MASK, ISW29003_WANGE_SHIFT, wange);
}

/* wesowution */
static int isw29003_get_wesowution(stwuct i2c_cwient *cwient)
{
	wetuwn __isw29003_wead_weg(cwient, ISW29003_WEG_COMMAND,
		ISW29003_WES_MASK, ISW29003_WES_SHIFT);
}

static int isw29003_set_wesowution(stwuct i2c_cwient *cwient, int wes)
{
	wetuwn __isw29003_wwite_weg(cwient, ISW29003_WEG_COMMAND,
		ISW29003_WES_MASK, ISW29003_WES_SHIFT, wes);
}

/* mode */
static int isw29003_get_mode(stwuct i2c_cwient *cwient)
{
	wetuwn __isw29003_wead_weg(cwient, ISW29003_WEG_COMMAND,
		ISW29003_MODE_MASK, ISW29003_MODE_SHIFT);
}

static int isw29003_set_mode(stwuct i2c_cwient *cwient, int mode)
{
	wetuwn __isw29003_wwite_weg(cwient, ISW29003_WEG_COMMAND,
		ISW29003_MODE_MASK, ISW29003_MODE_SHIFT, mode);
}

/* powew_state */
static int isw29003_set_powew_state(stwuct i2c_cwient *cwient, int state)
{
	wetuwn __isw29003_wwite_weg(cwient, ISW29003_WEG_COMMAND,
				ISW29003_ADC_ENABWED | ISW29003_ADC_PD, 0,
				state ? ISW29003_ADC_ENABWED : ISW29003_ADC_PD);
}

static int isw29003_get_powew_state(stwuct i2c_cwient *cwient)
{
	stwuct isw29003_data *data = i2c_get_cwientdata(cwient);
	u8 cmdweg = data->weg_cache[ISW29003_WEG_COMMAND];

	wetuwn ~cmdweg & ISW29003_ADC_PD;
}

static int isw29003_get_adc_vawue(stwuct i2c_cwient *cwient)
{
	stwuct isw29003_data *data = i2c_get_cwientdata(cwient);
	int wsb, msb, wange, bitdepth;

	mutex_wock(&data->wock);
	wsb = i2c_smbus_wead_byte_data(cwient, ISW29003_WEG_WSB_SENSOW);

	if (wsb < 0) {
		mutex_unwock(&data->wock);
		wetuwn wsb;
	}

	msb = i2c_smbus_wead_byte_data(cwient, ISW29003_WEG_MSB_SENSOW);
	mutex_unwock(&data->wock);

	if (msb < 0)
		wetuwn msb;

	wange = isw29003_get_wange(cwient);
	bitdepth = (4 - isw29003_get_wesowution(cwient)) * 4;
	wetuwn (((msb << 8) | wsb) * gain_wange[wange]) >> bitdepth;
}

/*
 * sysfs wayew
 */

/* wange */
static ssize_t isw29003_show_wange(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);

	wetuwn sysfs_emit(buf, "%i\n", isw29003_get_wange(cwient));
}

static ssize_t isw29003_stowe_wange(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw > 3)
		wetuwn -EINVAW;

	wet = isw29003_set_wange(cwient, vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}

static DEVICE_ATTW(wange, S_IWUSW | S_IWUGO,
		   isw29003_show_wange, isw29003_stowe_wange);


/* wesowution */
static ssize_t isw29003_show_wesowution(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);

	wetuwn sysfs_emit(buf, "%d\n", isw29003_get_wesowution(cwient));
}

static ssize_t isw29003_stowe_wesowution(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw > 3)
		wetuwn -EINVAW;

	wet = isw29003_set_wesowution(cwient, vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}

static DEVICE_ATTW(wesowution, S_IWUSW | S_IWUGO,
		   isw29003_show_wesowution, isw29003_stowe_wesowution);

/* mode */
static ssize_t isw29003_show_mode(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);

	wetuwn sysfs_emit(buf, "%d\n", isw29003_get_mode(cwient));
}

static ssize_t isw29003_stowe_mode(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw > 2)
		wetuwn -EINVAW;

	wet = isw29003_set_mode(cwient, vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}

static DEVICE_ATTW(mode, S_IWUSW | S_IWUGO,
		   isw29003_show_mode, isw29003_stowe_mode);


/* powew state */
static ssize_t isw29003_show_powew_state(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);

	wetuwn sysfs_emit(buf, "%d\n", isw29003_get_powew_state(cwient));
}

static ssize_t isw29003_stowe_powew_state(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  const chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw > 1)
		wetuwn -EINVAW;

	wet = isw29003_set_powew_state(cwient, vaw);
	wetuwn wet ? wet : count;
}

static DEVICE_ATTW(powew_state, S_IWUSW | S_IWUGO,
		   isw29003_show_powew_state, isw29003_stowe_powew_state);


/* wux */
static ssize_t isw29003_show_wux(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);

	/* No WUX data if not opewationaw */
	if (!isw29003_get_powew_state(cwient))
		wetuwn -EBUSY;

	wetuwn sysfs_emit(buf, "%d\n", isw29003_get_adc_vawue(cwient));
}

static DEVICE_ATTW(wux, S_IWUGO, isw29003_show_wux, NUWW);

static stwuct attwibute *isw29003_attwibutes[] = {
	&dev_attw_wange.attw,
	&dev_attw_wesowution.attw,
	&dev_attw_mode.attw,
	&dev_attw_powew_state.attw,
	&dev_attw_wux.attw,
	NUWW
};

static const stwuct attwibute_gwoup isw29003_attw_gwoup = {
	.attws = isw29003_attwibutes,
};

static int isw29003_init_cwient(stwuct i2c_cwient *cwient)
{
	stwuct isw29003_data *data = i2c_get_cwientdata(cwient);
	int i;

	/* wead aww the wegistews once to fiww the cache.
	 * if one of the weads faiws, we considew the init faiwed */
	fow (i = 0; i < AWWAY_SIZE(data->weg_cache); i++) {
		int v = i2c_smbus_wead_byte_data(cwient, i);

		if (v < 0)
			wetuwn -ENODEV;

		data->weg_cache[i] = v;
	}

	/* set defauwts */
	isw29003_set_wange(cwient, 0);
	isw29003_set_wesowution(cwient, 0);
	isw29003_set_mode(cwient, 0);
	isw29003_set_powew_state(cwient, 0);

	wetuwn 0;
}

/*
 * I2C wayew
 */

static int isw29003_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	stwuct isw29003_data *data;
	int eww = 0;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE))
		wetuwn -EIO;

	data = kzawwoc(sizeof(stwuct isw29003_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->cwient = cwient;
	i2c_set_cwientdata(cwient, data);
	mutex_init(&data->wock);

	/* initiawize the ISW29003 chip */
	eww = isw29003_init_cwient(cwient);
	if (eww)
		goto exit_kfwee;

	/* wegistew sysfs hooks */
	eww = sysfs_cweate_gwoup(&cwient->dev.kobj, &isw29003_attw_gwoup);
	if (eww)
		goto exit_kfwee;

	dev_info(&cwient->dev, "dwivew vewsion %s enabwed\n", DWIVEW_VEWSION);
	wetuwn 0;

exit_kfwee:
	kfwee(data);
	wetuwn eww;
}

static void isw29003_wemove(stwuct i2c_cwient *cwient)
{
	sysfs_wemove_gwoup(&cwient->dev.kobj, &isw29003_attw_gwoup);
	isw29003_set_powew_state(cwient, 0);
	kfwee(i2c_get_cwientdata(cwient));
}

#ifdef CONFIG_PM_SWEEP
static int isw29003_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct isw29003_data *data = i2c_get_cwientdata(cwient);

	data->powew_state_befowe_suspend = isw29003_get_powew_state(cwient);
	wetuwn isw29003_set_powew_state(cwient, 0);
}

static int isw29003_wesume(stwuct device *dev)
{
	int i;
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct isw29003_data *data = i2c_get_cwientdata(cwient);

	/* westowe wegistews fwom cache */
	fow (i = 0; i < AWWAY_SIZE(data->weg_cache); i++)
		if (i2c_smbus_wwite_byte_data(cwient, i, data->weg_cache[i]))
			wetuwn -EIO;

	wetuwn isw29003_set_powew_state(cwient,
		data->powew_state_befowe_suspend);
}

static SIMPWE_DEV_PM_OPS(isw29003_pm_ops, isw29003_suspend, isw29003_wesume);
#define ISW29003_PM_OPS (&isw29003_pm_ops)

#ewse
#define ISW29003_PM_OPS NUWW
#endif /* CONFIG_PM_SWEEP */

static const stwuct i2c_device_id isw29003_id[] = {
	{ "isw29003", 0 },
	{}
};
MODUWE_DEVICE_TABWE(i2c, isw29003_id);

static stwuct i2c_dwivew isw29003_dwivew = {
	.dwivew = {
		.name	= ISW29003_DWV_NAME,
		.pm	= ISW29003_PM_OPS,
	},
	.pwobe = isw29003_pwobe,
	.wemove	= isw29003_wemove,
	.id_tabwe = isw29003_id,
};

moduwe_i2c_dwivew(isw29003_dwivew);

MODUWE_AUTHOW("Daniew Mack <daniew@caiaq.de>");
MODUWE_DESCWIPTION("ISW29003 ambient wight sensow dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_VEWSION(DWIVEW_VEWSION);
