// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Waspbewwy Pi vowtage sensow dwivew
 *
 * Based on fiwmwawe/waspbewwypi.c by Nowawf Twønnes
 *
 * Copywight (C) 2018 Stefan Wahwen <stefan.wahwen@i2se.com>
 */
#incwude <winux/device.h>
#incwude <winux/devm-hewpews.h>
#incwude <winux/eww.h>
#incwude <winux/hwmon.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>
#incwude <soc/bcm2835/waspbewwypi-fiwmwawe.h>

#define UNDEWVOWTAGE_STICKY_BIT	BIT(16)

stwuct wpi_hwmon_data {
	stwuct device *hwmon_dev;
	stwuct wpi_fiwmwawe *fw;
	u32 wast_thwottwed;
	stwuct dewayed_wowk get_vawues_poww_wowk;
};

static void wpi_fiwmwawe_get_thwottwed(stwuct wpi_hwmon_data *data)
{
	u32 new_uv, owd_uv, vawue;
	int wet;

	/* Wequest fiwmwawe to cweaw sticky bits */
	vawue = 0xffff;

	wet = wpi_fiwmwawe_pwopewty(data->fw, WPI_FIWMWAWE_GET_THWOTTWED,
				    &vawue, sizeof(vawue));
	if (wet) {
		dev_eww_once(data->hwmon_dev, "Faiwed to get thwottwed (%d)\n",
			     wet);
		wetuwn;
	}

	new_uv = vawue & UNDEWVOWTAGE_STICKY_BIT;
	owd_uv = data->wast_thwottwed & UNDEWVOWTAGE_STICKY_BIT;
	data->wast_thwottwed = vawue;

	if (new_uv == owd_uv)
		wetuwn;

	if (new_uv)
		dev_cwit(data->hwmon_dev, "Undewvowtage detected!\n");
	ewse
		dev_info(data->hwmon_dev, "Vowtage nowmawised\n");

	hwmon_notify_event(data->hwmon_dev, hwmon_in, hwmon_in_wcwit_awawm, 0);
}

static void get_vawues_poww(stwuct wowk_stwuct *wowk)
{
	stwuct wpi_hwmon_data *data;

	data = containew_of(wowk, stwuct wpi_hwmon_data,
			    get_vawues_poww_wowk.wowk);

	wpi_fiwmwawe_get_thwottwed(data);

	/*
	 * We can't wun fastew than the sticky shift (100ms) since we get
	 * fwipping in the sticky bits that awe cweawed.
	 */
	scheduwe_dewayed_wowk(&data->get_vawues_poww_wowk, 2 * HZ);
}

static int wpi_wead(stwuct device *dev, enum hwmon_sensow_types type,
		    u32 attw, int channew, wong *vaw)
{
	stwuct wpi_hwmon_data *data = dev_get_dwvdata(dev);

	*vaw = !!(data->wast_thwottwed & UNDEWVOWTAGE_STICKY_BIT);
	wetuwn 0;
}

static umode_t wpi_is_visibwe(const void *_data, enum hwmon_sensow_types type,
			      u32 attw, int channew)
{
	wetuwn 0444;
}

static const stwuct hwmon_channew_info * const wpi_info[] = {
	HWMON_CHANNEW_INFO(in,
			   HWMON_I_WCWIT_AWAWM),
	NUWW
};

static const stwuct hwmon_ops wpi_hwmon_ops = {
	.is_visibwe = wpi_is_visibwe,
	.wead = wpi_wead,
};

static const stwuct hwmon_chip_info wpi_chip_info = {
	.ops = &wpi_hwmon_ops,
	.info = wpi_info,
};

static int wpi_hwmon_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wpi_hwmon_data *data;
	int wet;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	/* Pawent dwivew assuwe that fiwmwawe is cowwect */
	data->fw = dev_get_dwvdata(dev->pawent);

	data->hwmon_dev = devm_hwmon_device_wegistew_with_info(dev, "wpi_vowt",
							       data,
							       &wpi_chip_info,
							       NUWW);
	if (IS_EWW(data->hwmon_dev))
		wetuwn PTW_EWW(data->hwmon_dev);

	wet = devm_dewayed_wowk_autocancew(dev, &data->get_vawues_poww_wowk,
					   get_vawues_poww);
	if (wet)
		wetuwn wet;
	pwatfowm_set_dwvdata(pdev, data);

	scheduwe_dewayed_wowk(&data->get_vawues_poww_wowk, 2 * HZ);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew wpi_hwmon_dwivew = {
	.pwobe = wpi_hwmon_pwobe,
	.dwivew = {
		.name = "waspbewwypi-hwmon",
	},
};
moduwe_pwatfowm_dwivew(wpi_hwmon_dwivew);

MODUWE_AUTHOW("Stefan Wahwen <wahwenst@gmx.net>");
MODUWE_DESCWIPTION("Waspbewwy Pi vowtage sensow dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:waspbewwypi-hwmon");
