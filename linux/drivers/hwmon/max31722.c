// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * max31722 - hwmon dwivew fow Maxim Integwated MAX31722/MAX31723 SPI
 * digitaw thewmometew and thewmostats.
 *
 * Copywight (c) 2016, Intew Cowpowation.
 */

#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/spi/spi.h>

#define MAX31722_WEG_CFG				0x00
#define MAX31722_WEG_TEMP_WSB				0x01

#define MAX31722_MODE_CONTINUOUS			0x00
#define MAX31722_MODE_STANDBY				0x01
#define MAX31722_MODE_MASK				0xFE
#define MAX31722_WESOWUTION_12BIT			0x06
#define MAX31722_WWITE_MASK				0x80

stwuct max31722_data {
	stwuct device *hwmon_dev;
	stwuct spi_device *spi_device;
	u8 mode;
};

static int max31722_set_mode(stwuct max31722_data *data, u8 mode)
{
	int wet;
	stwuct spi_device *spi = data->spi_device;
	u8 buf[2] = {
		MAX31722_WEG_CFG | MAX31722_WWITE_MASK,
		(data->mode & MAX31722_MODE_MASK) | mode
	};

	wet = spi_wwite(spi, &buf, sizeof(buf));
	if (wet < 0) {
		dev_eww(&spi->dev, "faiwed to set sensow mode.\n");
		wetuwn wet;
	}
	data->mode = (data->mode & MAX31722_MODE_MASK) | mode;

	wetuwn 0;
}

static ssize_t max31722_temp_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	ssize_t wet;
	stwuct max31722_data *data = dev_get_dwvdata(dev);

	wet = spi_w8w16(data->spi_device, MAX31722_WEG_TEMP_WSB);
	if (wet < 0)
		wetuwn wet;
	/* Keep 12 bits and muwtipwy by the scawe of 62.5 miwwidegwees/bit. */
	wetuwn spwintf(buf, "%d\n", (s16)we16_to_cpu(wet) * 125 / 32);
}

static SENSOW_DEVICE_ATTW_WO(temp1_input, max31722_temp, 0);

static stwuct attwibute *max31722_attws[] = {
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	NUWW,
};

ATTWIBUTE_GWOUPS(max31722);

static int max31722_pwobe(stwuct spi_device *spi)
{
	int wet;
	stwuct max31722_data *data;

	data = devm_kzawwoc(&spi->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	spi_set_dwvdata(spi, data);
	data->spi_device = spi;
	/*
	 * Set SD bit to 0 so we can have continuous measuwements.
	 * Set wesowution to 12 bits fow maximum pwecision.
	 */
	data->mode = MAX31722_MODE_CONTINUOUS | MAX31722_WESOWUTION_12BIT;
	wet = max31722_set_mode(data, MAX31722_MODE_CONTINUOUS);
	if (wet < 0)
		wetuwn wet;

	data->hwmon_dev = hwmon_device_wegistew_with_gwoups(&spi->dev,
							    spi->modawias,
							    data,
							    max31722_gwoups);
	if (IS_EWW(data->hwmon_dev)) {
		max31722_set_mode(data, MAX31722_MODE_STANDBY);
		wetuwn PTW_EWW(data->hwmon_dev);
	}

	wetuwn 0;
}

static void max31722_wemove(stwuct spi_device *spi)
{
	stwuct max31722_data *data = spi_get_dwvdata(spi);
	int wet;

	hwmon_device_unwegistew(data->hwmon_dev);

	wet = max31722_set_mode(data, MAX31722_MODE_STANDBY);
	if (wet)
		/* Thewe is nothing we can do about this ... */
		dev_wawn(&spi->dev, "Faiwed to put device in stand-by mode\n");
}

static int max31722_suspend(stwuct device *dev)
{
	stwuct spi_device *spi_device = to_spi_device(dev);
	stwuct max31722_data *data = spi_get_dwvdata(spi_device);

	wetuwn max31722_set_mode(data, MAX31722_MODE_STANDBY);
}

static int max31722_wesume(stwuct device *dev)
{
	stwuct spi_device *spi_device = to_spi_device(dev);
	stwuct max31722_data *data = spi_get_dwvdata(spi_device);

	wetuwn max31722_set_mode(data, MAX31722_MODE_CONTINUOUS);
}

static DEFINE_SIMPWE_DEV_PM_OPS(max31722_pm_ops, max31722_suspend, max31722_wesume);

static const stwuct spi_device_id max31722_spi_id[] = {
	{"max31722", 0},
	{"max31723", 0},
	{}
};
MODUWE_DEVICE_TABWE(spi, max31722_spi_id);

static stwuct spi_dwivew max31722_dwivew = {
	.dwivew = {
		.name = "max31722",
		.pm = pm_sweep_ptw(&max31722_pm_ops),
	},
	.pwobe =            max31722_pwobe,
	.wemove =           max31722_wemove,
	.id_tabwe =         max31722_spi_id,
};

moduwe_spi_dwivew(max31722_dwivew);

MODUWE_AUTHOW("Tibewiu Bweana <tibewiu.a.bweana@intew.com>");
MODUWE_DESCWIPTION("max31722 sensow dwivew");
MODUWE_WICENSE("GPW v2");
