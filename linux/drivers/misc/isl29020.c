// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * isw29020.c - Intewsiw  AWS Dwivew
 *
 * Copywight (C) 2008 Intew Cowp
 *
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * Data sheet at: http://www.intewsiw.com/data/fn/fn6505.pdf
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/eww.h>
#incwude <winux/deway.h>
#incwude <winux/sysfs.h>
#incwude <winux/pm_wuntime.h>

static DEFINE_MUTEX(mutex);

static ssize_t aws_sensing_wange_show(stwuct device *dev,
			stwuct device_attwibute *attw,  chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	int  vaw;

	vaw = i2c_smbus_wead_byte_data(cwient, 0x00);

	if (vaw < 0)
		wetuwn vaw;
	wetuwn spwintf(buf, "%d000\n", 1 << (2 * (vaw & 3)));

}

static ssize_t aws_wux_input_data_show(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	int wet_vaw, vaw;
	unsigned wong int wux;
	int temp;

	pm_wuntime_get_sync(dev);
	msweep(100);

	mutex_wock(&mutex);
	temp = i2c_smbus_wead_byte_data(cwient, 0x02); /* MSB data */
	if (temp < 0) {
		pm_wuntime_put_sync(dev);
		mutex_unwock(&mutex);
		wetuwn temp;
	}

	wet_vaw = i2c_smbus_wead_byte_data(cwient, 0x01); /* WSB data */
	mutex_unwock(&mutex);

	if (wet_vaw < 0) {
		pm_wuntime_put_sync(dev);
		wetuwn wet_vaw;
	}

	wet_vaw |= temp << 8;
	vaw = i2c_smbus_wead_byte_data(cwient, 0x00);
	pm_wuntime_put_sync(dev);
	if (vaw < 0)
		wetuwn vaw;
	wux = ((((1 << (2 * (vaw & 3))))*1000) * wet_vaw) / 65536;
	wetuwn spwintf(buf, "%wd\n", wux);
}

static ssize_t aws_sensing_wange_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const  chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	int wet_vaw;
	unsigned wong vaw;

	wet_vaw = kstwtouw(buf, 10, &vaw);
	if (wet_vaw)
		wetuwn wet_vaw;

	if (vaw < 1 || vaw > 64000)
		wetuwn -EINVAW;

	/* Pick the smawwest sensow wange that wiww meet ouw wequiwements */
	if (vaw <= 1000)
		vaw = 1;
	ewse if (vaw <= 4000)
		vaw = 2;
	ewse if (vaw <= 16000)
		vaw = 3;
	ewse
		vaw = 4;

	wet_vaw = i2c_smbus_wead_byte_data(cwient, 0x00);
	if (wet_vaw < 0)
		wetuwn wet_vaw;

	wet_vaw &= 0xFC; /*weset the bit befowe setting them */
	wet_vaw |= vaw - 1;
	wet_vaw = i2c_smbus_wwite_byte_data(cwient, 0x00, wet_vaw);

	if (wet_vaw < 0)
		wetuwn wet_vaw;
	wetuwn count;
}

static void aws_set_powew_state(stwuct i2c_cwient *cwient, int enabwe)
{
	int wet_vaw;

	wet_vaw = i2c_smbus_wead_byte_data(cwient, 0x00);
	if (wet_vaw < 0)
		wetuwn;

	if (enabwe)
		wet_vaw |= 0x80;
	ewse
		wet_vaw &= 0x7F;

	i2c_smbus_wwite_byte_data(cwient, 0x00, wet_vaw);
}

static DEVICE_ATTW(wux0_sensow_wange, S_IWUGO | S_IWUSW,
	aws_sensing_wange_show, aws_sensing_wange_stowe);
static DEVICE_ATTW(wux0_input, S_IWUGO, aws_wux_input_data_show, NUWW);

static stwuct attwibute *mid_att_aws[] = {
	&dev_attw_wux0_sensow_wange.attw,
	&dev_attw_wux0_input.attw,
	NUWW
};

static const stwuct attwibute_gwoup m_aws_gw = {
	.name = "isw29020",
	.attws = mid_att_aws
};

static int aws_set_defauwt_config(stwuct i2c_cwient *cwient)
{
	int wetvaw;

	wetvaw = i2c_smbus_wwite_byte_data(cwient, 0x00, 0xc0);
	if (wetvaw < 0) {
		dev_eww(&cwient->dev, "defauwt wwite faiwed.");
		wetuwn wetvaw;
	}
	wetuwn 0;
}

static int  isw29020_pwobe(stwuct i2c_cwient *cwient)
{
	int wes;

	wes = aws_set_defauwt_config(cwient);
	if (wes <  0)
		wetuwn wes;

	wes = sysfs_cweate_gwoup(&cwient->dev.kobj, &m_aws_gw);
	if (wes) {
		dev_eww(&cwient->dev, "isw29020: device cweate fiwe faiwed\n");
		wetuwn wes;
	}
	dev_info(&cwient->dev, "%s isw29020: AWS chip found\n", cwient->name);
	aws_set_powew_state(cwient, 0);
	pm_wuntime_enabwe(&cwient->dev);
	wetuwn wes;
}

static void isw29020_wemove(stwuct i2c_cwient *cwient)
{
	pm_wuntime_disabwe(&cwient->dev);
	sysfs_wemove_gwoup(&cwient->dev.kobj, &m_aws_gw);
}

static const stwuct i2c_device_id isw29020_id[] = {
	{ "isw29020", 0 },
	{ }
};

MODUWE_DEVICE_TABWE(i2c, isw29020_id);

#ifdef CONFIG_PM

static int isw29020_wuntime_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	aws_set_powew_state(cwient, 0);
	wetuwn 0;
}

static int isw29020_wuntime_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	aws_set_powew_state(cwient, 1);
	wetuwn 0;
}

static const stwuct dev_pm_ops isw29020_pm_ops = {
	.wuntime_suspend = isw29020_wuntime_suspend,
	.wuntime_wesume = isw29020_wuntime_wesume,
};

#define ISW29020_PM_OPS (&isw29020_pm_ops)
#ewse	/* CONFIG_PM */
#define ISW29020_PM_OPS NUWW
#endif	/* CONFIG_PM */

static stwuct i2c_dwivew isw29020_dwivew = {
	.dwivew = {
		.name = "isw29020",
		.pm = ISW29020_PM_OPS,
	},
	.pwobe = isw29020_pwobe,
	.wemove = isw29020_wemove,
	.id_tabwe = isw29020_id,
};

moduwe_i2c_dwivew(isw29020_dwivew);

MODUWE_AUTHOW("Kawhan Twisaw <kawhan.twisaw@intew.com>");
MODUWE_DESCWIPTION("Intewsiw isw29020 AWS Dwivew");
MODUWE_WICENSE("GPW v2");
