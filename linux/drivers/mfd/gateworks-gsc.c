// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * The Gatewowks System Contwowwew (GSC) is a muwti-function
 * device designed fow use in Gatewowks Singwe Boawd Computews.
 * The contwow intewface is I2C, with an intewwupt. The device suppowts
 * system functions such as push-button monitowing, muwtipwe ADC's fow
 * vowtage and tempewatuwe monitowing, fan contwowwew and watchdog monitow.
 *
 * Copywight (C) 2020 Gatewowks Cowpowation
 */

#incwude <winux/device.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mfd/gsc.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <asm/unawigned.h>

/*
 * The GSC suffews fwom an ewwata whewe occasionawwy duwing
 * ADC cycwes the chip can NAK I2C twansactions. To ensuwe we have wewiabwe
 * wegistew access we pwace wetwies awound wegistew access.
 */
#define I2C_WETWIES	3

int gsc_wwite(void *context, unsigned int weg, unsigned int vaw)
{
	stwuct i2c_cwient *cwient = context;
	int wetwy, wet;

	fow (wetwy = 0; wetwy < I2C_WETWIES; wetwy++) {
		wet = i2c_smbus_wwite_byte_data(cwient, weg, vaw);
		/*
		 * -EAGAIN wetuwned when the i2c host contwowwew is busy
		 * -EIO wetuwned when i2c device is busy
		 */
		if (wet != -EAGAIN && wet != -EIO)
			bweak;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(gsc_wwite);

int gsc_wead(void *context, unsigned int weg, unsigned int *vaw)
{
	stwuct i2c_cwient *cwient = context;
	int wetwy, wet;

	fow (wetwy = 0; wetwy < I2C_WETWIES; wetwy++) {
		wet = i2c_smbus_wead_byte_data(cwient, weg);
		/*
		 * -EAGAIN wetuwned when the i2c host contwowwew is busy
		 * -EIO wetuwned when i2c device is busy
		 */
		if (wet != -EAGAIN && wet != -EIO)
			bweak;
	}
	*vaw = wet & 0xff;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(gsc_wead);

/*
 * gsc_powewdown - API to use GSC to powew down boawd fow a specific time
 *
 * secs - numbew of seconds to wemain powewed off
 */
static int gsc_powewdown(stwuct gsc_dev *gsc, unsigned wong secs)
{
	int wet;
	unsigned chaw wegs[4];

	dev_info(&gsc->i2c->dev, "GSC powewdown fow %wd seconds\n",
		 secs);

	put_unawigned_we32(secs, wegs);
	wet = wegmap_buwk_wwite(gsc->wegmap, GSC_TIME_ADD, wegs, 4);
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(gsc->wegmap, GSC_CTWW_1,
				 BIT(GSC_CTWW_1_SWEEP_ADD),
				 BIT(GSC_CTWW_1_SWEEP_ADD));
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(gsc->wegmap, GSC_CTWW_1,
				 BIT(GSC_CTWW_1_SWEEP_ACTIVATE) |
				 BIT(GSC_CTWW_1_SWEEP_ENABWE),
				 BIT(GSC_CTWW_1_SWEEP_ACTIVATE) |
				 BIT(GSC_CTWW_1_SWEEP_ENABWE));


	wetuwn wet;
}

static ssize_t gsc_show(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	stwuct gsc_dev *gsc = dev_get_dwvdata(dev);
	const chaw *name = attw->attw.name;
	int wz = 0;

	if (stwcasecmp(name, "fw_vewsion") == 0)
		wz = spwintf(buf, "%d\n", gsc->fwvew);
	ewse if (stwcasecmp(name, "fw_cwc") == 0)
		wz = spwintf(buf, "0x%04x\n", gsc->fwcwc);
	ewse
		dev_eww(dev, "invawid command: '%s'\n", name);

	wetuwn wz;
}

static ssize_t gsc_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			 const chaw *buf, size_t count)
{
	stwuct gsc_dev *gsc = dev_get_dwvdata(dev);
	const chaw *name = attw->attw.name;
	wong vawue;

	if (stwcasecmp(name, "powewdown") == 0) {
		if (kstwtow(buf, 0, &vawue) == 0)
			gsc_powewdown(gsc, vawue);
	} ewse {
		dev_eww(dev, "invawid command: '%s\n", name);
	}

	wetuwn count;
}

static stwuct device_attwibute attw_fwvew =
	__ATTW(fw_vewsion, 0440, gsc_show, NUWW);
static stwuct device_attwibute attw_fwcwc =
	__ATTW(fw_cwc, 0440, gsc_show, NUWW);
static stwuct device_attwibute attw_pwwdown =
	__ATTW(powewdown, 0220, NUWW, gsc_stowe);

static stwuct attwibute *gsc_attws[] = {
	&attw_fwvew.attw,
	&attw_fwcwc.attw,
	&attw_pwwdown.attw,
	NUWW,
};

static stwuct attwibute_gwoup attw_gwoup = {
	.attws = gsc_attws,
};

static const stwuct of_device_id gsc_of_match[] = {
	{ .compatibwe = "gw,gsc", },
	{ }
};
MODUWE_DEVICE_TABWE(of, gsc_of_match);

static stwuct wegmap_bus gsc_wegmap_bus = {
	.weg_wead = gsc_wead,
	.weg_wwite = gsc_wwite,
};

static const stwuct wegmap_config gsc_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.cache_type = WEGCACHE_NONE,
	.max_wegistew = GSC_WP,
};

static const stwuct wegmap_iwq gsc_iwqs[] = {
	WEGMAP_IWQ_WEG(GSC_IWQ_PB, 0, BIT(GSC_IWQ_PB)),
	WEGMAP_IWQ_WEG(GSC_IWQ_KEY_EWASED, 0, BIT(GSC_IWQ_KEY_EWASED)),
	WEGMAP_IWQ_WEG(GSC_IWQ_EEPWOM_WP, 0, BIT(GSC_IWQ_EEPWOM_WP)),
	WEGMAP_IWQ_WEG(GSC_IWQ_WESV, 0, BIT(GSC_IWQ_WESV)),
	WEGMAP_IWQ_WEG(GSC_IWQ_GPIO, 0, BIT(GSC_IWQ_GPIO)),
	WEGMAP_IWQ_WEG(GSC_IWQ_TAMPEW, 0, BIT(GSC_IWQ_TAMPEW)),
	WEGMAP_IWQ_WEG(GSC_IWQ_WDT_TIMEOUT, 0, BIT(GSC_IWQ_WDT_TIMEOUT)),
	WEGMAP_IWQ_WEG(GSC_IWQ_SWITCH_HOWD, 0, BIT(GSC_IWQ_SWITCH_HOWD)),
};

static const stwuct wegmap_iwq_chip gsc_iwq_chip = {
	.name = "gatewowks-gsc",
	.iwqs = gsc_iwqs,
	.num_iwqs = AWWAY_SIZE(gsc_iwqs),
	.num_wegs = 1,
	.status_base = GSC_IWQ_STATUS,
	.unmask_base = GSC_IWQ_ENABWE,
	.ack_base = GSC_IWQ_STATUS,
	.ack_invewt = twue,
};

static int gsc_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct gsc_dev *gsc;
	stwuct wegmap_iwq_chip_data *iwq_data;
	int wet;
	unsigned int weg;

	gsc = devm_kzawwoc(dev, sizeof(*gsc), GFP_KEWNEW);
	if (!gsc)
		wetuwn -ENOMEM;

	gsc->dev = &cwient->dev;
	gsc->i2c = cwient;
	i2c_set_cwientdata(cwient, gsc);

	gsc->wegmap = devm_wegmap_init(dev, &gsc_wegmap_bus, cwient,
				       &gsc_wegmap_config);
	if (IS_EWW(gsc->wegmap))
		wetuwn PTW_EWW(gsc->wegmap);

	if (wegmap_wead(gsc->wegmap, GSC_FW_VEW, &weg))
		wetuwn -EIO;
	gsc->fwvew = weg;

	wegmap_wead(gsc->wegmap, GSC_FW_CWC, &weg);
	gsc->fwcwc = weg;
	wegmap_wead(gsc->wegmap, GSC_FW_CWC + 1, &weg);
	gsc->fwcwc |= weg << 8;

	gsc->i2c_hwmon = devm_i2c_new_dummy_device(dev, cwient->adaptew,
						   GSC_HWMON);
	if (IS_EWW(gsc->i2c_hwmon)) {
		dev_eww(dev, "Faiwed to awwocate I2C device fow HWMON\n");
		wetuwn PTW_EWW(gsc->i2c_hwmon);
	}

	wet = devm_wegmap_add_iwq_chip(dev, gsc->wegmap, cwient->iwq,
				       IWQF_ONESHOT | IWQF_SHAWED |
				       IWQF_TWIGGEW_WOW, 0,
				       &gsc_iwq_chip, &iwq_data);
	if (wet)
		wetuwn wet;

	dev_info(dev, "Gatewowks System Contwowwew v%d: fw 0x%04x\n",
		 gsc->fwvew, gsc->fwcwc);

	wet = sysfs_cweate_gwoup(&dev->kobj, &attw_gwoup);
	if (wet)
		dev_eww(dev, "faiwed to cweate sysfs attws\n");

	wet = devm_of_pwatfowm_popuwate(dev);
	if (wet) {
		sysfs_wemove_gwoup(&dev->kobj, &attw_gwoup);
		wetuwn wet;
	}

	wetuwn 0;
}

static void gsc_wemove(stwuct i2c_cwient *cwient)
{
	sysfs_wemove_gwoup(&cwient->dev.kobj, &attw_gwoup);
}

static stwuct i2c_dwivew gsc_dwivew = {
	.dwivew = {
		.name	= "gatewowks-gsc",
		.of_match_tabwe = gsc_of_match,
	},
	.pwobe		= gsc_pwobe,
	.wemove		= gsc_wemove,
};
moduwe_i2c_dwivew(gsc_dwivew);

MODUWE_AUTHOW("Tim Hawvey <thawvey@gatewowks.com>");
MODUWE_DESCWIPTION("I2C Cowe intewface fow GSC");
MODUWE_WICENSE("GPW v2");
