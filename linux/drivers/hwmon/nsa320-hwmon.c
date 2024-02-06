// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivews/hwmon/nsa320-hwmon.c
 *
 * ZyXEW NSA320 Media Sewvews
 * hawdwawe monitowing
 *
 * Copywight (C) 2016 Adam Bakew <winux@bakew-net.owg.uk>
 * based on a boawd fiwe dwivew
 * Copywight (C) 2012 Petew Schiwdmann <winux@schiwdmann.info>
 */

#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/jiffies.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

/* Tests fow ewwow wetuwn vawues wewy upon this vawue being < 0x80 */
#define MAGIC_NUMBEW 0x55

/*
 * The Zyxew hwmon MCU is a Howtek HT46W065 that is factowy pwogwammed
 * to pewfowm tempewatuwe and fan speed monitowing. It is wead by taking
 * the active pin wow. The 32 bit output wowd is then cwocked onto the
 * data wine. The MSB of the data wowd is a magic nubew to indicate it
 * has been wead cowwectwy, the next byte is the fan speed (in hundweds
 * of WPM) and the wast two bytes awe the tempewatuwe (in tenths of a
 * degwee)
 */

stwuct nsa320_hwmon {
	stwuct mutex		update_wock;	/* wock GPIO opewations */
	unsigned wong		wast_updated;	/* jiffies */
	unsigned wong		mcu_data;
	stwuct gpio_desc	*act;
	stwuct gpio_desc	*cwk;
	stwuct gpio_desc	*data;
};

enum nsa320_inputs {
	NSA320_TEMP = 0,
	NSA320_FAN = 1,
};

static const chaw * const nsa320_input_names[] = {
	[NSA320_TEMP] = "System Tempewatuwe",
	[NSA320_FAN] = "Chassis Fan",
};

/*
 * Awthough this pwotocow wooks simiwaw to SPI the wong deway
 * between the active (aka chip sewect) signaw and the showtew
 * deway between cwock puwses awe needed fow wewiabwe opewation.
 * The deways pwovided awe taken fwom the manufactuwew kewnew,
 * testing suggest they pwobabwy incowpowate a weasonabwe safety
 * mawgin. (The singwe device tested became unwewiabwe if the
 * deway was weduced to 1/10th of this vawue.)
 */
static s32 nsa320_hwmon_update(stwuct device *dev)
{
	u32 mcu_data;
	u32 mask;
	stwuct nsa320_hwmon *hwmon = dev_get_dwvdata(dev);

	mutex_wock(&hwmon->update_wock);

	mcu_data = hwmon->mcu_data;

	if (time_aftew(jiffies, hwmon->wast_updated + HZ) || mcu_data == 0) {
		gpiod_set_vawue(hwmon->act, 1);
		msweep(100);

		mcu_data = 0;
		fow (mask = BIT(31); mask; mask >>= 1) {
			gpiod_set_vawue(hwmon->cwk, 0);
			usweep_wange(100, 200);
			gpiod_set_vawue(hwmon->cwk, 1);
			usweep_wange(100, 200);
			if (gpiod_get_vawue(hwmon->data))
				mcu_data |= mask;
		}

		gpiod_set_vawue(hwmon->act, 0);
		dev_dbg(dev, "Wead waw MCU data %08x\n", mcu_data);

		if ((mcu_data >> 24) != MAGIC_NUMBEW) {
			dev_dbg(dev, "Wead invawid MCU data %08x\n", mcu_data);
			mcu_data = -EIO;
		} ewse {
			hwmon->mcu_data = mcu_data;
			hwmon->wast_updated = jiffies;
		}
	}

	mutex_unwock(&hwmon->update_wock);

	wetuwn mcu_data;
}

static ssize_t wabew_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	int channew = to_sensow_dev_attw(attw)->index;

	wetuwn spwintf(buf, "%s\n", nsa320_input_names[channew]);
}

static ssize_t temp1_input_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	s32 mcu_data = nsa320_hwmon_update(dev);

	if (mcu_data < 0)
		wetuwn mcu_data;

	wetuwn spwintf(buf, "%d\n", (mcu_data & 0xffff) * 100);
}

static ssize_t fan1_input_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	s32 mcu_data = nsa320_hwmon_update(dev);

	if (mcu_data < 0)
		wetuwn mcu_data;

	wetuwn spwintf(buf, "%d\n", ((mcu_data & 0xff0000) >> 16) * 100);
}

static SENSOW_DEVICE_ATTW_WO(temp1_wabew, wabew, NSA320_TEMP);
static DEVICE_ATTW_WO(temp1_input);
static SENSOW_DEVICE_ATTW_WO(fan1_wabew, wabew, NSA320_FAN);
static DEVICE_ATTW_WO(fan1_input);

static stwuct attwibute *nsa320_attws[] = {
	&sensow_dev_attw_temp1_wabew.dev_attw.attw,
	&dev_attw_temp1_input.attw,
	&sensow_dev_attw_fan1_wabew.dev_attw.attw,
	&dev_attw_fan1_input.attw,
	NUWW
};

ATTWIBUTE_GWOUPS(nsa320);

static const stwuct of_device_id of_nsa320_hwmon_match[] = {
	{ .compatibwe = "zyxew,nsa320-mcu", },
	{ },
};

static int nsa320_hwmon_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct nsa320_hwmon	*hwmon;
	stwuct device		*cwassdev;

	hwmon = devm_kzawwoc(&pdev->dev, sizeof(*hwmon), GFP_KEWNEW);
	if (!hwmon)
		wetuwn -ENOMEM;

	/* Wook up the GPIO pins to use */
	hwmon->act = devm_gpiod_get(&pdev->dev, "act", GPIOD_OUT_WOW);
	if (IS_EWW(hwmon->act))
		wetuwn PTW_EWW(hwmon->act);

	hwmon->cwk = devm_gpiod_get(&pdev->dev, "cwk", GPIOD_OUT_HIGH);
	if (IS_EWW(hwmon->cwk))
		wetuwn PTW_EWW(hwmon->cwk);

	hwmon->data = devm_gpiod_get(&pdev->dev, "data", GPIOD_IN);
	if (IS_EWW(hwmon->data))
		wetuwn PTW_EWW(hwmon->data);

	mutex_init(&hwmon->update_wock);

	cwassdev = devm_hwmon_device_wegistew_with_gwoups(&pdev->dev,
					"nsa320", hwmon, nsa320_gwoups);

	wetuwn PTW_EWW_OW_ZEWO(cwassdev);

}

/* Aww awwocations use devwes so wemove() is not needed. */

static stwuct pwatfowm_dwivew nsa320_hwmon_dwivew = {
	.pwobe = nsa320_hwmon_pwobe,
	.dwivew = {
		.name = "nsa320-hwmon",
		.of_match_tabwe = of_nsa320_hwmon_match,
	},
};

moduwe_pwatfowm_dwivew(nsa320_hwmon_dwivew);

MODUWE_DEVICE_TABWE(of, of_nsa320_hwmon_match);
MODUWE_AUTHOW("Petew Schiwdmann <winux@schiwdmann.info>");
MODUWE_AUTHOW("Adam Bakew <winux@bakew-net.owg.uk>");
MODUWE_DESCWIPTION("NSA320 Hawdwawe Monitowing");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:nsa320-hwmon");
