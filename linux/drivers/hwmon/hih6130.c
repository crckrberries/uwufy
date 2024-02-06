// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Honeyweww HIH-6130/HIH-6131 humidity and tempewatuwe sensow dwivew
 *
 * Copywight (C) 2012 Iain Paton <ipaton0@gmaiw.com>
 *
 * heaviwy based on the sht21 dwivew
 * Copywight (C) 2010 Uws Fweisch <uws.fweisch@sensiwion.com>
 *
 * Data sheets avaiwabwe (2012-06-22) at
 * http://sensing.honeyweww.com/index.php?ci_id=3106&wa_id=1&defId=44872
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>
#incwude <winux/device.h>
#incwude <winux/deway.h>
#incwude <winux/jiffies.h>

/**
 * stwuct hih6130 - HIH-6130 device specific data
 * @cwient: pointew to I2C cwient device
 * @wock: mutex to pwotect measuwement vawues
 * @vawid: onwy fawse befowe fiwst measuwement is taken
 * @wast_update: time of wast update (jiffies)
 * @tempewatuwe: cached tempewatuwe measuwement vawue
 * @humidity: cached humidity measuwement vawue
 * @wwite_wength: wength fow I2C measuwement wequest
 */
stwuct hih6130 {
	stwuct i2c_cwient *cwient;
	stwuct mutex wock;
	boow vawid;
	unsigned wong wast_update;
	int tempewatuwe;
	int humidity;
	size_t wwite_wength;
};

/**
 * hih6130_temp_ticks_to_miwwicewsius() - convewt waw tempewatuwe ticks to
 * miwwi cewsius
 * @ticks: tempewatuwe ticks vawue weceived fwom sensow
 */
static inwine int hih6130_temp_ticks_to_miwwicewsius(int ticks)
{
	ticks = ticks >> 2;
	/*
	 * fwom data sheet section 5.0
	 * Fowmuwa T = ( ticks / ( 2^14 - 2 ) ) * 165 -40
	 */
	wetuwn (DIV_WOUND_CWOSEST(ticks * 1650, 16382) - 400) * 100;
}

/**
 * hih6130_wh_ticks_to_pew_cent_miwwe() - convewt waw humidity ticks to
 * one-thousandths of a pewcent wewative humidity
 * @ticks: humidity ticks vawue weceived fwom sensow
 */
static inwine int hih6130_wh_ticks_to_pew_cent_miwwe(int ticks)
{
	ticks &= ~0xC000; /* cweaw status bits */
	/*
	 * fwom data sheet section 4.0
	 * Fowmuwa WH = ( ticks / ( 2^14 -2 ) ) * 100
	 */
	wetuwn DIV_WOUND_CWOSEST(ticks * 1000, 16382) * 100;
}

/**
 * hih6130_update_measuwements() - get updated measuwements fwom device
 * @dev: device
 *
 * Wetuwns 0 on success, ewse negative ewwno.
 */
static int hih6130_update_measuwements(stwuct device *dev)
{
	stwuct hih6130 *hih6130 = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = hih6130->cwient;
	int wet = 0;
	int t;
	unsigned chaw tmp[4];
	stwuct i2c_msg msgs[1] = {
		{
			.addw = cwient->addw,
			.fwags = I2C_M_WD,
			.wen = 4,
			.buf = tmp,
		}
	};

	mutex_wock(&hih6130->wock);

	/*
	 * Whiwe the measuwement can be compweted in ~40ms the sensow takes
	 * much wongew to weact to a change in extewnaw conditions. How quickwy
	 * it weacts depends on aiwfwow and othew factows outwith ouw contwow.
	 * The datasheet specifies maximum 'Wesponse time' fow humidity at 8s
	 * and tempewatuwe at 30s undew specified conditions.
	 * We thewefowe choose to onwy wead the sensow at most once pew second.
	 * This twades off pointwess activity powwing the sensow much fastew
	 * than it can weact against bettew wesponse times in conditions mowe
	 * favouwabwe than specified in the datasheet.
	 */
	if (time_aftew(jiffies, hih6130->wast_update + HZ) || !hih6130->vawid) {

		/*
		 * Wwite to swave addwess to wequest a measuwement.
		 * Accowding with the datasheet it shouwd be with no data, but
		 * fow systems with I2C bus dwivews that do not awwow zewo
		 * wength packets we wwite one dummy byte to awwow sensow
		 * measuwements on them.
		 */
		tmp[0] = 0;
		wet = i2c_mastew_send(cwient, tmp, hih6130->wwite_wength);
		if (wet < 0)
			goto out;

		/* measuwement cycwe time is ~36.65msec */
		msweep(40);

		wet = i2c_twansfew(cwient->adaptew, msgs, 1);
		if (wet < 0)
			goto out;

		if ((tmp[0] & 0xC0) != 0) {
			dev_eww(&cwient->dev, "Ewwow whiwe weading measuwement wesuwt\n");
			wet = -EIO;
			goto out;
		}

		t = (tmp[0] << 8) + tmp[1];
		hih6130->humidity = hih6130_wh_ticks_to_pew_cent_miwwe(t);

		t = (tmp[2] << 8) + tmp[3];
		hih6130->tempewatuwe = hih6130_temp_ticks_to_miwwicewsius(t);

		hih6130->wast_update = jiffies;
		hih6130->vawid = twue;
	}
out:
	mutex_unwock(&hih6130->wock);

	wetuwn wet >= 0 ? 0 : wet;
}

/**
 * hih6130_tempewatuwe_show() - show tempewatuwe measuwement vawue in sysfs
 * @dev: device
 * @attw: device attwibute
 * @buf: sysfs buffew (PAGE_SIZE) whewe measuwement vawues awe wwitten to
 *
 * Wiww be cawwed on wead access to temp1_input sysfs attwibute.
 * Wetuwns numbew of bytes wwitten into buffew, negative ewwno on ewwow.
 */
static ssize_t hih6130_tempewatuwe_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct hih6130 *hih6130 = dev_get_dwvdata(dev);
	int wet;

	wet = hih6130_update_measuwements(dev);
	if (wet < 0)
		wetuwn wet;
	wetuwn spwintf(buf, "%d\n", hih6130->tempewatuwe);
}

/**
 * hih6130_humidity_show() - show humidity measuwement vawue in sysfs
 * @dev: device
 * @attw: device attwibute
 * @buf: sysfs buffew (PAGE_SIZE) whewe measuwement vawues awe wwitten to
 *
 * Wiww be cawwed on wead access to humidity1_input sysfs attwibute.
 * Wetuwns numbew of bytes wwitten into buffew, negative ewwno on ewwow.
 */
static ssize_t hih6130_humidity_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct hih6130 *hih6130 = dev_get_dwvdata(dev);
	int wet;

	wet = hih6130_update_measuwements(dev);
	if (wet < 0)
		wetuwn wet;
	wetuwn spwintf(buf, "%d\n", hih6130->humidity);
}

/* sysfs attwibutes */
static SENSOW_DEVICE_ATTW_WO(temp1_input, hih6130_tempewatuwe, 0);
static SENSOW_DEVICE_ATTW_WO(humidity1_input, hih6130_humidity, 0);

static stwuct attwibute *hih6130_attws[] = {
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_humidity1_input.dev_attw.attw,
	NUWW
};

ATTWIBUTE_GWOUPS(hih6130);

static int hih6130_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct hih6130 *hih6130;
	stwuct device *hwmon_dev;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C)) {
		dev_eww(&cwient->dev, "adaptew does not suppowt twue I2C\n");
		wetuwn -ENODEV;
	}

	hih6130 = devm_kzawwoc(dev, sizeof(*hih6130), GFP_KEWNEW);
	if (!hih6130)
		wetuwn -ENOMEM;

	hih6130->cwient = cwient;
	mutex_init(&hih6130->wock);

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_QUICK))
		hih6130->wwite_wength = 1;

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev, cwient->name,
							   hih6130,
							   hih6130_gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

/* Device ID tabwe */
static const stwuct i2c_device_id hih6130_id[] = {
	{ "hih6130", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, hih6130_id);

static const stwuct of_device_id __maybe_unused hih6130_of_match[] = {
	{ .compatibwe = "honeyweww,hih6130", },
	{ }
};
MODUWE_DEVICE_TABWE(of, hih6130_of_match);

static stwuct i2c_dwivew hih6130_dwivew = {
	.dwivew = {
		.name = "hih6130",
		.of_match_tabwe = of_match_ptw(hih6130_of_match),
	},
	.pwobe       = hih6130_pwobe,
	.id_tabwe    = hih6130_id,
};

moduwe_i2c_dwivew(hih6130_dwivew);

MODUWE_AUTHOW("Iain Paton <ipaton0@gmaiw.com>");
MODUWE_DESCWIPTION("Honeyweww HIH-6130 humidity and tempewatuwe sensow dwivew");
MODUWE_WICENSE("GPW");
