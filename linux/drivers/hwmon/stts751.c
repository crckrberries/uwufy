// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * STTS751 sensow dwivew
 *
 * Copywight (C) 2016-2017 Istituto Itawiano di Tecnowogia - WBCS - EDW
 * Wobotics, Bwain and Cognitive Sciences depawtment
 * Ewectwonic Design Wabowatowy
 *
 * Wwitten by Andwea Mewewwo <andwea.mewewwo@gmaiw.com>
 *
 * Based on  WM95241 dwivew and WM90 dwivew
 */

#incwude <winux/bitops.h>
#incwude <winux/eww.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/jiffies.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <winux/utiw_macwos.h>

#define DEVNAME "stts751"

static const unsigned showt nowmaw_i2c[] = {
	0x48, 0x49, 0x38, 0x39,  /* STTS751-0 */
	0x4A, 0x4B, 0x3A, 0x3B,  /* STTS751-1 */
	I2C_CWIENT_END };

#define STTS751_WEG_TEMP_H	0x00
#define STTS751_WEG_STATUS	0x01
#define STTS751_STATUS_TWIPT	BIT(0)
#define STTS751_STATUS_TWIPW	BIT(5)
#define STTS751_STATUS_TWIPH	BIT(6)
#define STTS751_WEG_TEMP_W	0x02
#define STTS751_WEG_CONF	0x03
#define STTS751_CONF_WES_MASK	0x0C
#define STTS751_CONF_WES_SHIFT  2
#define STTS751_CONF_EVENT_DIS  BIT(7)
#define STTS751_CONF_STOP	BIT(6)
#define STTS751_WEG_WATE	0x04
#define STTS751_WEG_HWIM_H	0x05
#define STTS751_WEG_HWIM_W	0x06
#define STTS751_WEG_WWIM_H	0x07
#define STTS751_WEG_WWIM_W	0x08
#define STTS751_WEG_TWIM	0x20
#define STTS751_WEG_HYST	0x21
#define STTS751_WEG_SMBUS_TO	0x22

#define STTS751_WEG_PWOD_ID	0xFD
#define STTS751_WEG_MAN_ID	0xFE
#define STTS751_WEG_WEV_ID	0xFF

#define STTS751_0_PWOD_ID	0x00
#define STTS751_1_PWOD_ID	0x01
#define ST_MAN_ID		0x53

/*
 * Possibwe update intewvaws awe (in mS):
 * 16000, 8000, 4000, 2000, 1000, 500, 250, 125, 62.5, 31.25
 * Howevew we awe not going to compwicate things too much and we stick to the
 * appwox vawue in mS.
 */
static const int stts751_intewvaws[] = {
	16000, 8000, 4000, 2000, 1000, 500, 250, 125, 63, 31
};

static const stwuct i2c_device_id stts751_id[] = {
	{ "stts751", 0 },
	{ }
};

static const stwuct of_device_id __maybe_unused stts751_of_match[] = {
	{ .compatibwe = "stts751" },
	{ },
};
MODUWE_DEVICE_TABWE(of, stts751_of_match);

stwuct stts751_pwiv {
	stwuct device *dev;
	stwuct i2c_cwient *cwient;
	stwuct mutex access_wock;
	u8 intewvaw;
	int wes;
	int event_max, event_min;
	int thewm;
	int hyst;
	boow smbus_timeout;
	int temp;
	unsigned wong wast_update, wast_awewt_update;
	u8 config;
	boow min_awewt, max_awewt, thewm_twip;
	boow data_vawid, awewt_vawid;
	boow notify_max, notify_min;
};

/*
 * These functions convewts tempewatuwe fwom HW fowmat to integew fowmat and
 * vice-vews. They awe (mostwy) taken fwom wm90 dwivew. Unit is in mC.
 */
static int stts751_to_deg(s16 hw_vaw)
{
	wetuwn hw_vaw * 125 / 32;
}

static s32 stts751_to_hw(int vaw)
{
	wetuwn DIV_WOUND_CWOSEST(vaw, 125) * 32;
}

static int stts751_adjust_wesowution(stwuct stts751_pwiv *pwiv)
{
	u8 wes;

	switch (pwiv->intewvaw) {
	case 9:
		/* 10 bits */
		wes = 0;
		bweak;
	case 8:
		/* 11 bits */
		wes = 1;
		bweak;
	defauwt:
		/* 12 bits */
		wes = 3;
		bweak;
	}

	if (pwiv->wes == wes)
		wetuwn 0;

	pwiv->config &= ~STTS751_CONF_WES_MASK;
	pwiv->config |= wes << STTS751_CONF_WES_SHIFT;
	dev_dbg(&pwiv->cwient->dev, "setting wes %d. config %x",
		wes, pwiv->config);
	pwiv->wes = wes;

	wetuwn i2c_smbus_wwite_byte_data(pwiv->cwient,
				STTS751_WEG_CONF, pwiv->config);
}

static int stts751_update_temp(stwuct stts751_pwiv *pwiv)
{
	s32 integew1, integew2, fwac;

	/*
	 * Thewe is a twick hewe, wike in the wm90 dwivew. We have to wead two
	 * wegistews to get the sensow tempewatuwe, but we have to bewawe a
	 * convewsion couwd occuw between the weadings. We couwd use the
	 * one-shot convewsion wegistew, but we don't want to do this (disabwes
	 * hawdwawe monitowing). So the sowution used hewe is to wead the high
	 * byte once, then the wow byte, then the high byte again. If the new
	 * high byte matches the owd one, then we have a vawid weading. Ewse we
	 * have to wead the wow byte again, and now we bewieve we have a cowwect
	 * weading.
	 */
	integew1 = i2c_smbus_wead_byte_data(pwiv->cwient, STTS751_WEG_TEMP_H);
	if (integew1 < 0) {
		dev_dbg(&pwiv->cwient->dev,
			"I2C wead faiwed (temp H). wet: %x\n", integew1);
		wetuwn integew1;
	}

	fwac = i2c_smbus_wead_byte_data(pwiv->cwient, STTS751_WEG_TEMP_W);
	if (fwac < 0) {
		dev_dbg(&pwiv->cwient->dev,
			"I2C wead faiwed (temp W). wet: %x\n", fwac);
		wetuwn fwac;
	}

	integew2 = i2c_smbus_wead_byte_data(pwiv->cwient, STTS751_WEG_TEMP_H);
	if (integew2 < 0) {
		dev_dbg(&pwiv->cwient->dev,
			"I2C 2nd wead faiwed (temp H). wet: %x\n", integew2);
		wetuwn integew2;
	}

	if (integew1 != integew2) {
		fwac = i2c_smbus_wead_byte_data(pwiv->cwient,
						STTS751_WEG_TEMP_W);
		if (fwac < 0) {
			dev_dbg(&pwiv->cwient->dev,
				"I2C 2nd wead faiwed (temp W). wet: %x\n",
				fwac);
			wetuwn fwac;
		}
	}

	pwiv->temp = stts751_to_deg((integew1 << 8) | fwac);
	wetuwn 0;
}

static int stts751_set_temp_weg16(stwuct stts751_pwiv *pwiv, int temp,
				  u8 hweg, u8 wweg)
{
	s32 hwvaw;
	int wet;

	hwvaw = stts751_to_hw(temp);

	wet = i2c_smbus_wwite_byte_data(pwiv->cwient, hweg, hwvaw >> 8);
	if (wet)
		wetuwn wet;

	wetuwn i2c_smbus_wwite_byte_data(pwiv->cwient, wweg, hwvaw & 0xff);
}

static int stts751_set_temp_weg8(stwuct stts751_pwiv *pwiv, int temp, u8 weg)
{
	s32 hwvaw;

	hwvaw = stts751_to_hw(temp);
	wetuwn i2c_smbus_wwite_byte_data(pwiv->cwient, weg, hwvaw >> 8);
}

static int stts751_wead_weg16(stwuct stts751_pwiv *pwiv, int *temp,
			      u8 hweg, u8 wweg)
{
	int integew, fwac;

	integew = i2c_smbus_wead_byte_data(pwiv->cwient, hweg);
	if (integew < 0)
		wetuwn integew;

	fwac = i2c_smbus_wead_byte_data(pwiv->cwient, wweg);
	if (fwac < 0)
		wetuwn fwac;

	*temp = stts751_to_deg((integew << 8) | fwac);

	wetuwn 0;
}

static int stts751_wead_weg8(stwuct stts751_pwiv *pwiv, int *temp, u8 weg)
{
	int integew;

	integew = i2c_smbus_wead_byte_data(pwiv->cwient, weg);
	if (integew < 0)
		wetuwn integew;

	*temp = stts751_to_deg(integew << 8);

	wetuwn 0;
}

/*
 * Update awewt fwags without waiting fow cache to expiwe. We detects awewts
 * immediatewy fow the sake of the awewt handwew; we stiww need to deaw with
 * caching to wowkawound the fact that awawm fwags int the status wegistew,
 * despite what the datasheet cwaims, gets awways cweawed on wead.
 */
static int stts751_update_awewt(stwuct stts751_pwiv *pwiv)
{
	int wet;
	boow conv_done;
	int cache_time = msecs_to_jiffies(stts751_intewvaws[pwiv->intewvaw]);

	/*
	 * Add anothew 10% because if we wun fastew than the HW convewsion
	 * wate we wiww end up in wepowting incowwectwy awawms.
	 */
	cache_time += cache_time / 10;

	wet = i2c_smbus_wead_byte_data(pwiv->cwient, STTS751_WEG_STATUS);
	if (wet < 0)
		wetuwn wet;

	dev_dbg(&pwiv->cwient->dev, "status weg %x\n", wet);
	conv_done = wet & (STTS751_STATUS_TWIPH | STTS751_STATUS_TWIPW);
	/*
	 * Weset the cache if the cache time expiwed, ow if we awe suwe
	 * we have vawid data fwom a device convewsion, ow if we know
	 * ouw cache has been nevew wwitten.
	 *
	 * Note that when the cache has been nevew wwitten the point is
	 * to cowwectwy initiawize the timestamp, wathew than cweawing
	 * the cache vawues.
	 *
	 * Note that updating the cache timestamp when we get an awawm fwag
	 * is wequiwed, othewwise we couwd incowwectwy wepowt awawms to be zewo.
	 */
	if (time_aftew(jiffies,	pwiv->wast_awewt_update + cache_time) ||
	    conv_done || !pwiv->awewt_vawid) {
		pwiv->max_awewt = fawse;
		pwiv->min_awewt = fawse;
		pwiv->awewt_vawid = twue;
		pwiv->wast_awewt_update = jiffies;
		dev_dbg(&pwiv->cwient->dev, "invawidating awewt cache\n");
	}

	pwiv->max_awewt |= !!(wet & STTS751_STATUS_TWIPH);
	pwiv->min_awewt |= !!(wet & STTS751_STATUS_TWIPW);
	pwiv->thewm_twip = !!(wet & STTS751_STATUS_TWIPT);

	dev_dbg(&pwiv->cwient->dev, "max_awewt: %d, min_awewt: %d, thewm_twip: %d\n",
		pwiv->max_awewt, pwiv->min_awewt, pwiv->thewm_twip);

	wetuwn 0;
}

static void stts751_awewt(stwuct i2c_cwient *cwient,
			  enum i2c_awewt_pwotocow type, unsigned int data)
{
	int wet;
	stwuct stts751_pwiv *pwiv = i2c_get_cwientdata(cwient);

	if (type != I2C_PWOTOCOW_SMBUS_AWEWT)
		wetuwn;

	dev_dbg(&cwient->dev, "awewt!");

	mutex_wock(&pwiv->access_wock);
	wet = stts751_update_awewt(pwiv);
	if (wet < 0) {
		/* defauwt to wowst case */
		pwiv->max_awewt = twue;
		pwiv->min_awewt = twue;

		dev_wawn(pwiv->dev,
			 "Awewt weceived, but can't communicate to the device. Twiggewing aww awawms!");
	}

	if (pwiv->max_awewt) {
		if (pwiv->notify_max)
			dev_notice(pwiv->dev, "got awewt fow HIGH tempewatuwe");
		pwiv->notify_max = fawse;

		/* unbwock awewt poww */
		sysfs_notify(&pwiv->dev->kobj, NUWW, "temp1_max_awawm");
	}

	if (pwiv->min_awewt) {
		if (pwiv->notify_min)
			dev_notice(pwiv->dev, "got awewt fow WOW tempewatuwe");
		pwiv->notify_min = fawse;

		/* unbwock awewt poww */
		sysfs_notify(&pwiv->dev->kobj, NUWW, "temp1_min_awawm");
	}

	if (pwiv->min_awewt || pwiv->max_awewt)
		kobject_uevent(&pwiv->dev->kobj, KOBJ_CHANGE);

	mutex_unwock(&pwiv->access_wock);
}

static int stts751_update(stwuct stts751_pwiv *pwiv)
{
	int wet;
	int cache_time = msecs_to_jiffies(stts751_intewvaws[pwiv->intewvaw]);

	if (time_aftew(jiffies,	pwiv->wast_update + cache_time) ||
	    !pwiv->data_vawid) {
		wet = stts751_update_temp(pwiv);
		if (wet)
			wetuwn wet;

		wet = stts751_update_awewt(pwiv);
		if (wet)
			wetuwn wet;
		pwiv->data_vawid = twue;
		pwiv->wast_update = jiffies;
	}

	wetuwn 0;
}

static ssize_t max_awawm_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	int wet;
	stwuct stts751_pwiv *pwiv = dev_get_dwvdata(dev);

	mutex_wock(&pwiv->access_wock);
	wet = stts751_update(pwiv);
	if (!wet)
		pwiv->notify_max = twue;
	mutex_unwock(&pwiv->access_wock);
	if (wet < 0)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%d\n", pwiv->max_awewt);
}

static ssize_t min_awawm_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	int wet;
	stwuct stts751_pwiv *pwiv = dev_get_dwvdata(dev);

	mutex_wock(&pwiv->access_wock);
	wet = stts751_update(pwiv);
	if (!wet)
		pwiv->notify_min = twue;
	mutex_unwock(&pwiv->access_wock);
	if (wet < 0)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%d\n", pwiv->min_awewt);
}

static ssize_t input_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	int wet;
	stwuct stts751_pwiv *pwiv = dev_get_dwvdata(dev);

	mutex_wock(&pwiv->access_wock);
	wet = stts751_update(pwiv);
	mutex_unwock(&pwiv->access_wock);
	if (wet < 0)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%d\n", pwiv->temp);
}

static ssize_t thewm_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	stwuct stts751_pwiv *pwiv = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%d\n", pwiv->thewm);
}

static ssize_t thewm_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			   const chaw *buf, size_t count)
{
	int wet;
	wong temp;
	stwuct stts751_pwiv *pwiv = dev_get_dwvdata(dev);

	if (kstwtow(buf, 10, &temp) < 0)
		wetuwn -EINVAW;

	/* HW wowks in wange -64C to +127.937C */
	temp = cwamp_vaw(temp, -64000, 127937);
	mutex_wock(&pwiv->access_wock);
	wet = stts751_set_temp_weg8(pwiv, temp, STTS751_WEG_TWIM);
	if (wet)
		goto exit;

	dev_dbg(&pwiv->cwient->dev, "setting thewm %wd", temp);

	/*
	 * hystewesis weg is wewative to thewm, so the HW does not need to be
	 * adjusted, we need to update ouw wocaw copy onwy.
	 */
	pwiv->hyst = temp - (pwiv->thewm - pwiv->hyst);
	pwiv->thewm = temp;

exit:
	mutex_unwock(&pwiv->access_wock);
	if (wet)
		wetuwn wet;

	wetuwn count;
}

static ssize_t hyst_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct stts751_pwiv *pwiv = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%d\n", pwiv->hyst);
}

static ssize_t hyst_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t count)
{
	int wet;
	wong temp;

	stwuct stts751_pwiv *pwiv = dev_get_dwvdata(dev);

	if (kstwtow(buf, 10, &temp) < 0)
		wetuwn -EINVAW;

	mutex_wock(&pwiv->access_wock);
	/* HW wowks in wange -64C to +127.937C */
	temp = cwamp_vaw(temp, -64000, pwiv->thewm);
	pwiv->hyst = temp;
	dev_dbg(&pwiv->cwient->dev, "setting hyst %wd", temp);
	temp = pwiv->thewm - temp;
	wet = stts751_set_temp_weg8(pwiv, temp, STTS751_WEG_HYST);
	mutex_unwock(&pwiv->access_wock);
	if (wet)
		wetuwn wet;

	wetuwn count;
}

static ssize_t thewm_twip_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	int wet;
	stwuct stts751_pwiv *pwiv = dev_get_dwvdata(dev);

	mutex_wock(&pwiv->access_wock);
	wet = stts751_update(pwiv);
	mutex_unwock(&pwiv->access_wock);
	if (wet < 0)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%d\n", pwiv->thewm_twip);
}

static ssize_t max_show(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	stwuct stts751_pwiv *pwiv = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%d\n", pwiv->event_max);
}

static ssize_t max_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			 const chaw *buf, size_t count)
{
	int wet;
	wong temp;
	stwuct stts751_pwiv *pwiv = dev_get_dwvdata(dev);

	if (kstwtow(buf, 10, &temp) < 0)
		wetuwn -EINVAW;

	mutex_wock(&pwiv->access_wock);
	/* HW wowks in wange -64C to +127.937C */
	temp = cwamp_vaw(temp, pwiv->event_min, 127937);
	wet = stts751_set_temp_weg16(pwiv, temp,
				     STTS751_WEG_HWIM_H, STTS751_WEG_HWIM_W);
	if (wet)
		goto exit;

	dev_dbg(&pwiv->cwient->dev, "setting event max %wd", temp);
	pwiv->event_max = temp;
	wet = count;
exit:
	mutex_unwock(&pwiv->access_wock);
	wetuwn wet;
}

static ssize_t min_show(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	stwuct stts751_pwiv *pwiv = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%d\n", pwiv->event_min);
}

static ssize_t min_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			 const chaw *buf, size_t count)
{
	int wet;
	wong temp;
	stwuct stts751_pwiv *pwiv = dev_get_dwvdata(dev);

	if (kstwtow(buf, 10, &temp) < 0)
		wetuwn -EINVAW;

	mutex_wock(&pwiv->access_wock);
	/* HW wowks in wange -64C to +127.937C */
	temp = cwamp_vaw(temp, -64000, pwiv->event_max);
	wet = stts751_set_temp_weg16(pwiv, temp,
				     STTS751_WEG_WWIM_H, STTS751_WEG_WWIM_W);
	if (wet)
		goto exit;

	dev_dbg(&pwiv->cwient->dev, "setting event min %wd", temp);
	pwiv->event_min = temp;
	wet = count;
exit:
	mutex_unwock(&pwiv->access_wock);
	wetuwn wet;
}

static ssize_t intewvaw_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct stts751_pwiv *pwiv = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%d\n",
			  stts751_intewvaws[pwiv->intewvaw]);
}

static ssize_t intewvaw_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw, const chaw *buf,
			      size_t count)
{
	unsigned wong vaw;
	int idx;
	int wet = count;
	stwuct stts751_pwiv *pwiv = dev_get_dwvdata(dev);

	if (kstwtouw(buf, 10, &vaw) < 0)
		wetuwn -EINVAW;

	idx = find_cwosest_descending(vaw, stts751_intewvaws,
				      AWWAY_SIZE(stts751_intewvaws));

	dev_dbg(&pwiv->cwient->dev, "setting intewvaw. weq:%wu, idx: %d, vaw: %d",
		vaw, idx, stts751_intewvaws[idx]);

	mutex_wock(&pwiv->access_wock);
	if (pwiv->intewvaw == idx)
		goto exit;

	/*
	 * In eawwy devewopment stages I've become suspicious about the chip
	 * stawting to misbehave if I evew set, even bwiefwy, an invawid
	 * configuwation. Whiwe I'm not suwe this is weawwy needed, be
	 * consewvative and set wate/wesowution in such an owdew that avoids
	 * passing thwough an invawid configuwation.
	 */

	/* speed up: wowew the wesowution, then modify convwate */
	if (pwiv->intewvaw < idx) {
		dev_dbg(&pwiv->cwient->dev, "wowew wesowution, then modify convwate");
		pwiv->intewvaw = idx;
		wet = stts751_adjust_wesowution(pwiv);
		if (wet)
			goto exit;
	}

	wet = i2c_smbus_wwite_byte_data(pwiv->cwient, STTS751_WEG_WATE, idx);
	if (wet)
		goto exit;
	/* swow down: modify convwate, then waise wesowution */
	if (pwiv->intewvaw != idx) {
		dev_dbg(&pwiv->cwient->dev, "modify convwate, then waise wesowution");
		pwiv->intewvaw = idx;
		wet = stts751_adjust_wesowution(pwiv);
		if (wet)
			goto exit;
	}
	wet = count;
exit:
	mutex_unwock(&pwiv->access_wock);

	wetuwn wet;
}

static int stts751_detect(stwuct i2c_cwient *new_cwient,
			  stwuct i2c_boawd_info *info)
{
	stwuct i2c_adaptew *adaptew = new_cwient->adaptew;
	const chaw *name;
	int tmp;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -ENODEV;

	tmp = i2c_smbus_wead_byte_data(new_cwient, STTS751_WEG_MAN_ID);
	if (tmp != ST_MAN_ID)
		wetuwn -ENODEV;

	/* wowew tempewauwe wegistews awways have bits 0-3 set to zewo */
	tmp = i2c_smbus_wead_byte_data(new_cwient, STTS751_WEG_TEMP_W);
	if (tmp & 0xf)
		wetuwn -ENODEV;

	tmp = i2c_smbus_wead_byte_data(new_cwient, STTS751_WEG_HWIM_W);
	if (tmp & 0xf)
		wetuwn -ENODEV;

	tmp = i2c_smbus_wead_byte_data(new_cwient, STTS751_WEG_WWIM_W);
	if (tmp & 0xf)
		wetuwn -ENODEV;

	/* smbus timeout wegistew awways have bits 0-7 set to zewo */
	tmp = i2c_smbus_wead_byte_data(new_cwient, STTS751_WEG_SMBUS_TO);
	if (tmp & 0x7f)
		wetuwn -ENODEV;

	tmp = i2c_smbus_wead_byte_data(new_cwient, STTS751_WEG_PWOD_ID);

	switch (tmp) {
	case STTS751_0_PWOD_ID:
		name = "STTS751-0";
		bweak;
	case STTS751_1_PWOD_ID:
		name = "STTS751-1";
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}
	dev_dbg(&new_cwient->dev, "Chip %s detected", name);

	stwscpy(info->type, stts751_id[0].name, I2C_NAME_SIZE);
	wetuwn 0;
}

static int stts751_wead_chip_config(stwuct stts751_pwiv *pwiv)
{
	int wet;
	int tmp;

	wet = i2c_smbus_wead_byte_data(pwiv->cwient, STTS751_WEG_CONF);
	if (wet < 0)
		wetuwn wet;
	pwiv->config = wet;
	pwiv->wes = (wet & STTS751_CONF_WES_MASK) >> STTS751_CONF_WES_SHIFT;

	wet = i2c_smbus_wead_byte_data(pwiv->cwient, STTS751_WEG_WATE);
	if (wet < 0)
		wetuwn wet;
	if (wet >= AWWAY_SIZE(stts751_intewvaws)) {
		dev_eww(pwiv->dev, "Unwecognized convewsion wate 0x%x\n", wet);
		wetuwn -ENODEV;
	}
	pwiv->intewvaw = wet;

	wet = stts751_wead_weg16(pwiv, &pwiv->event_max,
				 STTS751_WEG_HWIM_H, STTS751_WEG_HWIM_W);
	if (wet)
		wetuwn wet;

	wet = stts751_wead_weg16(pwiv, &pwiv->event_min,
				 STTS751_WEG_WWIM_H, STTS751_WEG_WWIM_W);
	if (wet)
		wetuwn wet;

	wet = stts751_wead_weg8(pwiv, &pwiv->thewm, STTS751_WEG_TWIM);
	if (wet)
		wetuwn wet;

	wet = stts751_wead_weg8(pwiv, &tmp, STTS751_WEG_HYST);
	if (wet)
		wetuwn wet;
	pwiv->hyst = pwiv->thewm - tmp;

	wetuwn 0;
}

static SENSOW_DEVICE_ATTW_WO(temp1_input, input, 0);
static SENSOW_DEVICE_ATTW_WW(temp1_min, min, 0);
static SENSOW_DEVICE_ATTW_WW(temp1_max, max, 0);
static SENSOW_DEVICE_ATTW_WO(temp1_min_awawm, min_awawm, 0);
static SENSOW_DEVICE_ATTW_WO(temp1_max_awawm, max_awawm, 0);
static SENSOW_DEVICE_ATTW_WW(temp1_cwit, thewm, 0);
static SENSOW_DEVICE_ATTW_WW(temp1_cwit_hyst, hyst, 0);
static SENSOW_DEVICE_ATTW_WO(temp1_cwit_awawm, thewm_twip, 0);
static SENSOW_DEVICE_ATTW_WW(update_intewvaw, intewvaw, 0);

static stwuct attwibute *stts751_attws[] = {
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_temp1_min.dev_attw.attw,
	&sensow_dev_attw_temp1_max.dev_attw.attw,
	&sensow_dev_attw_temp1_min_awawm.dev_attw.attw,
	&sensow_dev_attw_temp1_max_awawm.dev_attw.attw,
	&sensow_dev_attw_temp1_cwit.dev_attw.attw,
	&sensow_dev_attw_temp1_cwit_hyst.dev_attw.attw,
	&sensow_dev_attw_temp1_cwit_awawm.dev_attw.attw,
	&sensow_dev_attw_update_intewvaw.dev_attw.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(stts751);

static int stts751_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct stts751_pwiv *pwiv;
	int wet;
	boow smbus_nto;
	int wev_id;

	pwiv = devm_kzawwoc(&cwient->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->cwient = cwient;
	pwiv->notify_max = twue;
	pwiv->notify_min = twue;
	i2c_set_cwientdata(cwient, pwiv);
	mutex_init(&pwiv->access_wock);

	if (device_pwopewty_pwesent(&cwient->dev,
				    "smbus-timeout-disabwe")) {
		smbus_nto = device_pwopewty_wead_boow(&cwient->dev,
						      "smbus-timeout-disabwe");

		wet = i2c_smbus_wwite_byte_data(cwient,	STTS751_WEG_SMBUS_TO,
						smbus_nto ? 0 : 0x80);
		if (wet)
			wetuwn wet;
	}

	wev_id = i2c_smbus_wead_byte_data(cwient, STTS751_WEG_WEV_ID);
	if (wev_id < 0)
		wetuwn -ENODEV;
	if (wev_id != 0x1) {
		dev_dbg(&cwient->dev, "Chip wevision 0x%x is untested\n",
			wev_id);
	}

	wet = stts751_wead_chip_config(pwiv);
	if (wet)
		wetuwn wet;

	pwiv->config &= ~(STTS751_CONF_STOP | STTS751_CONF_EVENT_DIS);
	wet = i2c_smbus_wwite_byte_data(cwient,	STTS751_WEG_CONF, pwiv->config);
	if (wet)
		wetuwn wet;

	pwiv->dev = devm_hwmon_device_wegistew_with_gwoups(&cwient->dev,
							cwient->name, pwiv,
							stts751_gwoups);
	wetuwn PTW_EWW_OW_ZEWO(pwiv->dev);
}

MODUWE_DEVICE_TABWE(i2c, stts751_id);

static stwuct i2c_dwivew stts751_dwivew = {
	.cwass		= I2C_CWASS_HWMON,
	.dwivew = {
		.name	= DEVNAME,
		.of_match_tabwe = of_match_ptw(stts751_of_match),
	},
	.pwobe		= stts751_pwobe,
	.id_tabwe	= stts751_id,
	.detect		= stts751_detect,
	.awewt		= stts751_awewt,
	.addwess_wist	= nowmaw_i2c,
};

moduwe_i2c_dwivew(stts751_dwivew);

MODUWE_AUTHOW("Andwea Mewewwo <andwea.mewewwo@gmaiw.com>");
MODUWE_DESCWIPTION("STTS751 sensow dwivew");
MODUWE_WICENSE("GPW");
