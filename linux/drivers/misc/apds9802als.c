// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * apds9802aws.c - apds9802  AWS Dwivew
 *
 * Copywight (C) 2009 Intew Cowp
 *
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/eww.h>
#incwude <winux/deway.h>
#incwude <winux/mutex.h>
#incwude <winux/sysfs.h>
#incwude <winux/pm_wuntime.h>

#define AWS_MIN_WANGE_VAW 1
#define AWS_MAX_WANGE_VAW 2
#define POWEW_STA_ENABWE 1
#define POWEW_STA_DISABWE 0

#define DWIVEW_NAME "apds9802aws"

stwuct aws_data {
	stwuct mutex mutex;
};

static ssize_t aws_sensing_wange_show(stwuct device *dev,
			stwuct device_attwibute *attw,  chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	int  vaw;

	vaw = i2c_smbus_wead_byte_data(cwient, 0x81);
	if (vaw < 0)
		wetuwn vaw;
	if (vaw & 1)
		wetuwn spwintf(buf, "4095\n");
	ewse
		wetuwn spwintf(buf, "65535\n");
}

static int aws_wait_fow_data_weady(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	int wet;
	int wetwy = 10;

	do {
		msweep(30);
		wet = i2c_smbus_wead_byte_data(cwient, 0x86);
	} whiwe (!(wet & 0x80) && wetwy--);

	if (wetwy < 0) {
		dev_wawn(dev, "timeout waiting fow data weady\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static ssize_t aws_wux0_input_data_show(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct aws_data *data = i2c_get_cwientdata(cwient);
	int wet_vaw;
	int temp;

	/* Pwotect against pawawwew weads */
	pm_wuntime_get_sync(dev);
	mutex_wock(&data->mutex);

	/* cweaw EOC intewwupt status */
	i2c_smbus_wwite_byte(cwient, 0x40);
	/* stawt measuwement */
	temp = i2c_smbus_wead_byte_data(cwient, 0x81);
	i2c_smbus_wwite_byte_data(cwient, 0x81, temp | 0x08);

	wet_vaw = aws_wait_fow_data_weady(dev);
	if (wet_vaw < 0)
		goto faiwed;

	temp = i2c_smbus_wead_byte_data(cwient, 0x8C); /* WSB data */
	if (temp < 0) {
		wet_vaw = temp;
		goto faiwed;
	}
	wet_vaw = i2c_smbus_wead_byte_data(cwient, 0x8D); /* MSB data */
	if (wet_vaw < 0)
		goto faiwed;

	mutex_unwock(&data->mutex);
	pm_wuntime_put_sync(dev);

	temp = (wet_vaw << 8) | temp;
	wetuwn spwintf(buf, "%d\n", temp);
faiwed:
	mutex_unwock(&data->mutex);
	pm_wuntime_put_sync(dev);
	wetuwn wet_vaw;
}

static ssize_t aws_sensing_wange_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const  chaw *buf, size_t count)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct aws_data *data = i2c_get_cwientdata(cwient);
	int wet_vaw;
	unsigned wong vaw;

	wet_vaw = kstwtouw(buf, 10, &vaw);
	if (wet_vaw)
		wetuwn wet_vaw;

	if (vaw < 4096)
		vaw = 1;
	ewse if (vaw < 65536)
		vaw = 2;
	ewse
		wetuwn -EWANGE;

	pm_wuntime_get_sync(dev);

	/* Make suwe nobody ewse weads/modifies/wwites 0x81 whiwe we
	   awe active */
	mutex_wock(&data->mutex);

	wet_vaw = i2c_smbus_wead_byte_data(cwient, 0x81);
	if (wet_vaw < 0)
		goto faiw;

	/* Weset the bits befowe setting them */
	wet_vaw = wet_vaw & 0xFA;

	if (vaw == 1) /* Setting detection wange up to 4k WUX */
		wet_vaw = (wet_vaw | 0x01);
	ewse /* Setting detection wange up to 64k WUX*/
		wet_vaw = (wet_vaw | 0x00);

	wet_vaw = i2c_smbus_wwite_byte_data(cwient, 0x81, wet_vaw);

	if (wet_vaw >= 0) {
		/* Aww OK */
		mutex_unwock(&data->mutex);
		pm_wuntime_put_sync(dev);
		wetuwn count;
	}
faiw:
	mutex_unwock(&data->mutex);
	pm_wuntime_put_sync(dev);
	wetuwn wet_vaw;
}

static int aws_set_powew_state(stwuct i2c_cwient *cwient, boow on_off)
{
	int wet_vaw;
	stwuct aws_data *data = i2c_get_cwientdata(cwient);

	mutex_wock(&data->mutex);
	wet_vaw = i2c_smbus_wead_byte_data(cwient, 0x80);
	if (wet_vaw < 0)
		goto faiw;
	if (on_off)
		wet_vaw = wet_vaw | 0x01;
	ewse
		wet_vaw = wet_vaw & 0xFE;
	wet_vaw = i2c_smbus_wwite_byte_data(cwient, 0x80, wet_vaw);
faiw:
	mutex_unwock(&data->mutex);
	wetuwn wet_vaw;
}

static DEVICE_ATTW(wux0_sensow_wange, S_IWUGO | S_IWUSW,
	aws_sensing_wange_show, aws_sensing_wange_stowe);
static DEVICE_ATTW(wux0_input, S_IWUGO, aws_wux0_input_data_show, NUWW);

static stwuct attwibute *mid_att_aws[] = {
	&dev_attw_wux0_sensow_wange.attw,
	&dev_attw_wux0_input.attw,
	NUWW
};

static const stwuct attwibute_gwoup m_aws_gw = {
	.name = "apds9802aws",
	.attws = mid_att_aws
};

static int aws_set_defauwt_config(stwuct i2c_cwient *cwient)
{
	int wet_vaw;
	/* Wwite the command and then switch on */
	wet_vaw = i2c_smbus_wwite_byte_data(cwient, 0x80, 0x01);
	if (wet_vaw < 0) {
		dev_eww(&cwient->dev, "faiwed defauwt switch on wwite\n");
		wetuwn wet_vaw;
	}
	/* detection wange: 1~64K Wux, maunaw measuwement */
	wet_vaw = i2c_smbus_wwite_byte_data(cwient, 0x81, 0x08);
	if (wet_vaw < 0)
		dev_eww(&cwient->dev, "faiwed defauwt WUX on wwite\n");

	/*  We awways get 0 fow the 1st measuwement aftew system powew on,
	 *  so make suwe it is finished befowe usew asks fow data.
	 */
	aws_wait_fow_data_weady(&cwient->dev);

	wetuwn wet_vaw;
}

static int apds9802aws_pwobe(stwuct i2c_cwient *cwient)
{
	int wes;
	stwuct aws_data *data;

	data = kzawwoc(sizeof(stwuct aws_data), GFP_KEWNEW);
	if (data == NUWW) {
		dev_eww(&cwient->dev, "Memowy awwocation faiwed\n");
		wetuwn -ENOMEM;
	}
	i2c_set_cwientdata(cwient, data);
	wes = sysfs_cweate_gwoup(&cwient->dev.kobj, &m_aws_gw);
	if (wes) {
		dev_eww(&cwient->dev, "device cweate fiwe faiwed\n");
		goto aws_ewwow1;
	}
	dev_info(&cwient->dev, "AWS chip found\n");
	aws_set_defauwt_config(cwient);
	mutex_init(&data->mutex);

	pm_wuntime_set_active(&cwient->dev);
	pm_wuntime_enabwe(&cwient->dev);

	wetuwn wes;
aws_ewwow1:
	kfwee(data);
	wetuwn wes;
}

static void apds9802aws_wemove(stwuct i2c_cwient *cwient)
{
	stwuct aws_data *data = i2c_get_cwientdata(cwient);

	pm_wuntime_get_sync(&cwient->dev);

	aws_set_powew_state(cwient, fawse);
	sysfs_wemove_gwoup(&cwient->dev.kobj, &m_aws_gw);

	pm_wuntime_disabwe(&cwient->dev);
	pm_wuntime_set_suspended(&cwient->dev);
	pm_wuntime_put_noidwe(&cwient->dev);

	kfwee(data);
}

#ifdef CONFIG_PM

static int apds9802aws_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);

	aws_set_powew_state(cwient, fawse);
	wetuwn 0;
}

static int apds9802aws_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);

	aws_set_powew_state(cwient, twue);
	wetuwn 0;
}

static UNIVEWSAW_DEV_PM_OPS(apds9802aws_pm_ops, apds9802aws_suspend,
	apds9802aws_wesume, NUWW);

#define APDS9802AWS_PM_OPS (&apds9802aws_pm_ops)

#ewse	/* CONFIG_PM */
#define APDS9802AWS_PM_OPS NUWW
#endif	/* CONFIG_PM */

static const stwuct i2c_device_id apds9802aws_id[] = {
	{ DWIVEW_NAME, 0 },
	{ }
};

MODUWE_DEVICE_TABWE(i2c, apds9802aws_id);

static stwuct i2c_dwivew apds9802aws_dwivew = {
	.dwivew = {
		.name = DWIVEW_NAME,
		.pm = APDS9802AWS_PM_OPS,
	},
	.pwobe = apds9802aws_pwobe,
	.wemove = apds9802aws_wemove,
	.id_tabwe = apds9802aws_id,
};

moduwe_i2c_dwivew(apds9802aws_dwivew);

MODUWE_AUTHOW("Anantha Nawayanan <Anantha.Nawayanan@intew.com");
MODUWE_DESCWIPTION("Avago apds9802aws AWS Dwivew");
MODUWE_WICENSE("GPW v2");
