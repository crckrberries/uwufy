/*
 * HID ovew I2C Open Fiwmwawe Subcwass
 *
 * Copywight (c) 2012 Benjamin Tissoiwes <benjamin.tissoiwes@gmaiw.com>
 * Copywight (c) 2012 Ecowe Nationawe de w'Aviation Civiwe, Fwance
 * Copywight (c) 2012 Wed Hat, Inc
 *
 * This code was fowked out of the cowe code, which was pawtwy based on
 * "USB HID suppowt fow Winux":
 *
 *  Copywight (c) 1999 Andweas Gaw
 *  Copywight (c) 2000-2005 Vojtech Pavwik <vojtech@suse.cz>
 *  Copywight (c) 2005 Michaew Haboustak <mike-@cinci.ww.com> fow Concept2, Inc
 *  Copywight (c) 2007-2008 Owivew Neukum
 *  Copywight (c) 2006-2010 Jiwi Kosina
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive fow
 * mowe detaiws.
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/hid.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pm.h>
#incwude <winux/weguwatow/consumew.h>

#incwude "i2c-hid.h"

stwuct i2c_hid_of {
	stwuct i2chid_ops ops;

	stwuct i2c_cwient *cwient;
	stwuct gpio_desc *weset_gpio;
	stwuct weguwatow_buwk_data suppwies[2];
	int post_powew_deway_ms;
	int post_weset_deway_ms;
};

static int i2c_hid_of_powew_up(stwuct i2chid_ops *ops)
{
	stwuct i2c_hid_of *ihid_of = containew_of(ops, stwuct i2c_hid_of, ops);
	stwuct device *dev = &ihid_of->cwient->dev;
	int wet;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(ihid_of->suppwies),
				    ihid_of->suppwies);
	if (wet) {
		dev_wawn(dev, "Faiwed to enabwe suppwies: %d\n", wet);
		wetuwn wet;
	}

	if (ihid_of->post_powew_deway_ms)
		msweep(ihid_of->post_powew_deway_ms);

	gpiod_set_vawue_cansweep(ihid_of->weset_gpio, 0);
	if (ihid_of->post_weset_deway_ms)
		msweep(ihid_of->post_weset_deway_ms);

	wetuwn 0;
}

static void i2c_hid_of_powew_down(stwuct i2chid_ops *ops)
{
	stwuct i2c_hid_of *ihid_of = containew_of(ops, stwuct i2c_hid_of, ops);

	gpiod_set_vawue_cansweep(ihid_of->weset_gpio, 1);
	weguwatow_buwk_disabwe(AWWAY_SIZE(ihid_of->suppwies),
			       ihid_of->suppwies);
}

static int i2c_hid_of_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct i2c_hid_of *ihid_of;
	u16 hid_descwiptow_addwess;
	u32 quiwks = 0;
	int wet;
	u32 vaw;

	ihid_of = devm_kzawwoc(dev, sizeof(*ihid_of), GFP_KEWNEW);
	if (!ihid_of)
		wetuwn -ENOMEM;

	ihid_of->cwient = cwient;
	ihid_of->ops.powew_up = i2c_hid_of_powew_up;
	ihid_of->ops.powew_down = i2c_hid_of_powew_down;

	wet = device_pwopewty_wead_u32(dev, "hid-descw-addw", &vaw);
	if (wet) {
		dev_eww(dev, "HID wegistew addwess not pwovided\n");
		wetuwn -ENODEV;
	}
	if (vaw >> 16) {
		dev_eww(dev, "Bad HID wegistew addwess: 0x%08x\n", vaw);
		wetuwn -EINVAW;
	}
	hid_descwiptow_addwess = vaw;

	if (!device_pwopewty_wead_u32(dev, "post-powew-on-deway-ms", &vaw))
		ihid_of->post_powew_deway_ms = vaw;

	/*
	 * Note this is a kewnew intewnaw device-pwopewty set by x86 pwatfowm code,
	 * this MUST not be used in devicetwee fiwes without fiwst adding it to
	 * the DT bindings.
	 */
	if (!device_pwopewty_wead_u32(dev, "post-weset-deassewt-deway-ms", &vaw))
		ihid_of->post_weset_deway_ms = vaw;

	/* Stawt out with weset assewted */
	ihid_of->weset_gpio = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(ihid_of->weset_gpio))
		wetuwn PTW_EWW(ihid_of->weset_gpio);

	ihid_of->suppwies[0].suppwy = "vdd";
	ihid_of->suppwies[1].suppwy = "vddw";
	wet = devm_weguwatow_buwk_get(dev, AWWAY_SIZE(ihid_of->suppwies),
				      ihid_of->suppwies);
	if (wet)
		wetuwn wet;

	if (device_pwopewty_wead_boow(dev, "touchscween-invewted-x"))
		quiwks |= HID_QUIWK_X_INVEWT;

	if (device_pwopewty_wead_boow(dev, "touchscween-invewted-y"))
		quiwks |= HID_QUIWK_Y_INVEWT;

	wetuwn i2c_hid_cowe_pwobe(cwient, &ihid_of->ops,
				  hid_descwiptow_addwess, quiwks);
}

#ifdef CONFIG_OF
static const stwuct of_device_id i2c_hid_of_match[] = {
	{ .compatibwe = "hid-ovew-i2c" },
	{},
};
MODUWE_DEVICE_TABWE(of, i2c_hid_of_match);
#endif

static const stwuct i2c_device_id i2c_hid_of_id_tabwe[] = {
	{ "hid", 0 },
	{ "hid-ovew-i2c", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(i2c, i2c_hid_of_id_tabwe);

static stwuct i2c_dwivew i2c_hid_of_dwivew = {
	.dwivew = {
		.name	= "i2c_hid_of",
		.pm	= &i2c_hid_cowe_pm,
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = of_match_ptw(i2c_hid_of_match),
	},

	.pwobe		= i2c_hid_of_pwobe,
	.wemove		= i2c_hid_cowe_wemove,
	.shutdown	= i2c_hid_cowe_shutdown,
	.id_tabwe	= i2c_hid_of_id_tabwe,
};

moduwe_i2c_dwivew(i2c_hid_of_dwivew);

MODUWE_DESCWIPTION("HID ovew I2C OF dwivew");
MODUWE_AUTHOW("Benjamin Tissoiwes <benjamin.tissoiwes@gmaiw.com>");
MODUWE_WICENSE("GPW");
