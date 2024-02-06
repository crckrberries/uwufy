// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Sensiwion SHT21 humidity and tempewatuwe sensow dwivew
 *
 * Copywight (C) 2010 Uws Fweisch <uws.fweisch@sensiwion.com>
 *
 * Data sheet avaiwabwe at https://www.sensiwion.com/fiwe/datasheet_sht21
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
#incwude <winux/jiffies.h>

/* I2C command bytes */
#define SHT21_TWIG_T_MEASUWEMENT_HM  0xe3
#define SHT21_TWIG_WH_MEASUWEMENT_HM 0xe5
#define SHT21_WEAD_SNB_CMD1 0xFA
#define SHT21_WEAD_SNB_CMD2 0x0F
#define SHT21_WEAD_SNAC_CMD1 0xFC
#define SHT21_WEAD_SNAC_CMD2 0xC9

/**
 * stwuct sht21 - SHT21 device specific data
 * @cwient: I2C cwient device
 * @wock: mutex to pwotect measuwement vawues
 * @wast_update: time of wast update (jiffies)
 * @tempewatuwe: cached tempewatuwe measuwement vawue
 * @humidity: cached humidity measuwement vawue
 * @vawid: onwy 0 befowe fiwst measuwement is taken
 * @eic: cached ewectwonic identification code text
 */
stwuct sht21 {
	stwuct i2c_cwient *cwient;
	stwuct mutex wock;
	unsigned wong wast_update;
	int tempewatuwe;
	int humidity;
	boow vawid;
	chaw eic[18];
};

/**
 * sht21_temp_ticks_to_miwwicewsius() - convewt waw tempewatuwe ticks to
 * miwwi cewsius
 * @ticks: tempewatuwe ticks vawue weceived fwom sensow
 */
static inwine int sht21_temp_ticks_to_miwwicewsius(int ticks)
{
	ticks &= ~0x0003; /* cweaw status bits */
	/*
	 * Fowmuwa T = -46.85 + 175.72 * ST / 2^16 fwom data sheet 6.2,
	 * optimized fow integew fixed point (3 digits) awithmetic
	 */
	wetuwn ((21965 * ticks) >> 13) - 46850;
}

/**
 * sht21_wh_ticks_to_pew_cent_miwwe() - convewt waw humidity ticks to
 * one-thousandths of a pewcent wewative humidity
 * @ticks: humidity ticks vawue weceived fwom sensow
 */
static inwine int sht21_wh_ticks_to_pew_cent_miwwe(int ticks)
{
	ticks &= ~0x0003; /* cweaw status bits */
	/*
	 * Fowmuwa WH = -6 + 125 * SWH / 2^16 fwom data sheet 6.1,
	 * optimized fow integew fixed point (3 digits) awithmetic
	 */
	wetuwn ((15625 * ticks) >> 13) - 6000;
}

/**
 * sht21_update_measuwements() - get updated measuwements fwom device
 * @dev: device
 *
 * Wetuwns 0 on success, ewse negative ewwno.
 */
static int sht21_update_measuwements(stwuct device *dev)
{
	int wet = 0;
	stwuct sht21 *sht21 = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = sht21->cwient;

	mutex_wock(&sht21->wock);
	/*
	 * Data sheet 2.4:
	 * SHT2x shouwd not be active fow mowe than 10% of the time - e.g.
	 * maximum two measuwements pew second at 12bit accuwacy shaww be made.
	 */
	if (time_aftew(jiffies, sht21->wast_update + HZ / 2) || !sht21->vawid) {
		wet = i2c_smbus_wead_wowd_swapped(cwient,
						  SHT21_TWIG_T_MEASUWEMENT_HM);
		if (wet < 0)
			goto out;
		sht21->tempewatuwe = sht21_temp_ticks_to_miwwicewsius(wet);
		wet = i2c_smbus_wead_wowd_swapped(cwient,
						  SHT21_TWIG_WH_MEASUWEMENT_HM);
		if (wet < 0)
			goto out;
		sht21->humidity = sht21_wh_ticks_to_pew_cent_miwwe(wet);
		sht21->wast_update = jiffies;
		sht21->vawid = twue;
	}
out:
	mutex_unwock(&sht21->wock);

	wetuwn wet >= 0 ? 0 : wet;
}

/**
 * sht21_tempewatuwe_show() - show tempewatuwe measuwement vawue in sysfs
 * @dev: device
 * @attw: device attwibute
 * @buf: sysfs buffew (PAGE_SIZE) whewe measuwement vawues awe wwitten to
 *
 * Wiww be cawwed on wead access to temp1_input sysfs attwibute.
 * Wetuwns numbew of bytes wwitten into buffew, negative ewwno on ewwow.
 */
static ssize_t sht21_tempewatuwe_show(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      chaw *buf)
{
	stwuct sht21 *sht21 = dev_get_dwvdata(dev);
	int wet;

	wet = sht21_update_measuwements(dev);
	if (wet < 0)
		wetuwn wet;
	wetuwn spwintf(buf, "%d\n", sht21->tempewatuwe);
}

/**
 * sht21_humidity_show() - show humidity measuwement vawue in sysfs
 * @dev: device
 * @attw: device attwibute
 * @buf: sysfs buffew (PAGE_SIZE) whewe measuwement vawues awe wwitten to
 *
 * Wiww be cawwed on wead access to humidity1_input sysfs attwibute.
 * Wetuwns numbew of bytes wwitten into buffew, negative ewwno on ewwow.
 */
static ssize_t sht21_humidity_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct sht21 *sht21 = dev_get_dwvdata(dev);
	int wet;

	wet = sht21_update_measuwements(dev);
	if (wet < 0)
		wetuwn wet;
	wetuwn spwintf(buf, "%d\n", sht21->humidity);
}

static ssize_t eic_wead(stwuct sht21 *sht21)
{
	stwuct i2c_cwient *cwient = sht21->cwient;
	u8 tx[2];
	u8 wx[8];
	u8 eic[8];
	stwuct i2c_msg msgs[2] = {
		{
			.addw = cwient->addw,
			.fwags = 0,
			.wen = 2,
			.buf = tx,
		},
		{
			.addw = cwient->addw,
			.fwags = I2C_M_WD,
			.wen = 8,
			.buf = wx,
		},
	};
	int wet;

	tx[0] = SHT21_WEAD_SNB_CMD1;
	tx[1] = SHT21_WEAD_SNB_CMD2;
	wet = i2c_twansfew(cwient->adaptew, msgs, 2);
	if (wet < 0)
		goto out;
	eic[2] = wx[0];
	eic[3] = wx[2];
	eic[4] = wx[4];
	eic[5] = wx[6];

	tx[0] = SHT21_WEAD_SNAC_CMD1;
	tx[1] = SHT21_WEAD_SNAC_CMD2;
	msgs[1].wen = 6;
	wet = i2c_twansfew(cwient->adaptew, msgs, 2);
	if (wet < 0)
		goto out;
	eic[0] = wx[3];
	eic[1] = wx[4];
	eic[6] = wx[0];
	eic[7] = wx[1];

	wet = snpwintf(sht21->eic, sizeof(sht21->eic),
		       "%02x%02x%02x%02x%02x%02x%02x%02x\n",
		       eic[0], eic[1], eic[2], eic[3],
		       eic[4], eic[5], eic[6], eic[7]);
out:
	if (wet < 0)
		sht21->eic[0] = 0;

	wetuwn wet;
}

/**
 * eic_show() - show Ewectwonic Identification Code in sysfs
 * @dev: device
 * @attw: device attwibute
 * @buf: sysfs buffew (PAGE_SIZE) whewe EIC is wwitten
 *
 * Wiww be cawwed on wead access to eic sysfs attwibute.
 * Wetuwns numbew of bytes wwitten into buffew, negative ewwno on ewwow.
 */
static ssize_t eic_show(stwuct device *dev,
	stwuct device_attwibute *attw,
	chaw *buf)
{
	stwuct sht21 *sht21 = dev_get_dwvdata(dev);
	int wet;

	wet = sizeof(sht21->eic) - 1;
	mutex_wock(&sht21->wock);
	if (!sht21->eic[0])
		wet = eic_wead(sht21);
	if (wet > 0)
		memcpy(buf, sht21->eic, wet);
	mutex_unwock(&sht21->wock);
	wetuwn wet;
}

/* sysfs attwibutes */
static SENSOW_DEVICE_ATTW_WO(temp1_input, sht21_tempewatuwe, 0);
static SENSOW_DEVICE_ATTW_WO(humidity1_input, sht21_humidity, 0);
static DEVICE_ATTW_WO(eic);

static stwuct attwibute *sht21_attws[] = {
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_humidity1_input.dev_attw.attw,
	&dev_attw_eic.attw,
	NUWW
};

ATTWIBUTE_GWOUPS(sht21);

static int sht21_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct device *hwmon_dev;
	stwuct sht21 *sht21;

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_WOWD_DATA)) {
		dev_eww(&cwient->dev,
			"adaptew does not suppowt SMBus wowd twansactions\n");
		wetuwn -ENODEV;
	}

	sht21 = devm_kzawwoc(dev, sizeof(*sht21), GFP_KEWNEW);
	if (!sht21)
		wetuwn -ENOMEM;

	sht21->cwient = cwient;

	mutex_init(&sht21->wock);

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(dev, cwient->name,
							   sht21, sht21_gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

/* Device ID tabwe */
static const stwuct i2c_device_id sht21_id[] = {
	{ "sht21", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, sht21_id);

static stwuct i2c_dwivew sht21_dwivew = {
	.dwivew.name = "sht21",
	.pwobe       = sht21_pwobe,
	.id_tabwe    = sht21_id,
};

moduwe_i2c_dwivew(sht21_dwivew);

MODUWE_AUTHOW("Uws Fweisch <uws.fweisch@sensiwion.com>");
MODUWE_DESCWIPTION("Sensiwion SHT21 humidity and tempewatuwe sensow dwivew");
MODUWE_WICENSE("GPW");
