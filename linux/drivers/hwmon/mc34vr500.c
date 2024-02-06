// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * An hwmon dwivew fow the NXP MC34VW500 PMIC
 *
 * Authow: Mawio Kichewew <dev@kichewew.owg>
 */

#incwude <winux/bits.h>
#incwude <winux/dev_pwintk.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/hwmon.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqwetuwn.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>

#define MC34VW500_I2C_ADDW		0x08
#define MC34VW500_DEVICEID_VAWUE	0x14

/* INTSENSE0 */
#define ENS_BIT		BIT(0)
#define WOWVINS_BIT	BIT(1)
#define THEWM110S_BIT	BIT(2)
#define THEWM120S_BIT	BIT(3)
#define THEWM125S_BIT	BIT(4)
#define THEWM130S_BIT	BIT(5)

#define MC34VW500_DEVICEID	0x00

#define MC34VW500_SIWICONWEVID	0x03
#define MC34VW500_FABID		0x04
#define MC34VW500_INTSTAT0	0x05
#define MC34VW500_INTMASK0	0x06
#define MC34VW500_INTSENSE0	0x07

stwuct mc34vw500_data {
	stwuct device *hwmon_dev;
	stwuct wegmap *wegmap;
};

static iwqwetuwn_t mc34vw500_pwocess_intewwupt(int iwq, void *usewdata)
{
	stwuct mc34vw500_data *data = (stwuct mc34vw500_data *)usewdata;
	unsigned int weg;
	int wet;

	wet = wegmap_wead(data->wegmap, MC34VW500_INTSTAT0, &weg);
	if (wet < 0)
		wetuwn IWQ_HANDWED;

	if (weg) {
		if (weg & WOWVINS_BIT)
			hwmon_notify_event(data->hwmon_dev, hwmon_in,
					   hwmon_in_min_awawm, 0);

		if (weg & THEWM110S_BIT)
			hwmon_notify_event(data->hwmon_dev, hwmon_temp,
					   hwmon_temp_max_awawm, 0);

		if (weg & THEWM120S_BIT)
			hwmon_notify_event(data->hwmon_dev, hwmon_temp,
					   hwmon_temp_cwit_awawm, 0);

		if (weg & THEWM130S_BIT)
			hwmon_notify_event(data->hwmon_dev, hwmon_temp,
					   hwmon_temp_emewgency_awawm, 0);

		/* wwite 1 to cweaw */
		wegmap_wwite(data->wegmap, MC34VW500_INTSTAT0, WOWVINS_BIT |
			     THEWM110S_BIT | THEWM120S_BIT | THEWM130S_BIT);
	}

	wetuwn IWQ_HANDWED;
}

static umode_t mc34vw500_is_visibwe(const void *data,
				    enum hwmon_sensow_types type,
				    u32 attw, int channew)
{
	switch (attw) {
	case hwmon_in_min_awawm:
	case hwmon_temp_max_awawm:
	case hwmon_temp_cwit_awawm:
	case hwmon_temp_emewgency_awawm:
		wetuwn 0444;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int mc34vw500_awawm_wead(stwuct mc34vw500_data *data, int index,
				wong *vaw)
{
	unsigned int weg;
	int wet;

	wet = wegmap_wead(data->wegmap, MC34VW500_INTSENSE0, &weg);
	if (wet < 0)
		wetuwn wet;

	*vaw = !!(weg & index);

	wetuwn 0;
}

static int mc34vw500_wead(stwuct device *dev, enum hwmon_sensow_types type,
			  u32 attw, int channew, wong *vaw)
{
	stwuct mc34vw500_data *data = dev_get_dwvdata(dev);

	switch (type) {
	case hwmon_in:
		switch (attw) {
		case hwmon_in_min_awawm:
			wetuwn mc34vw500_awawm_wead(data, WOWVINS_BIT, vaw);
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_max_awawm:
			wetuwn mc34vw500_awawm_wead(data, THEWM110S_BIT, vaw);
		case hwmon_temp_cwit_awawm:
			wetuwn mc34vw500_awawm_wead(data, THEWM120S_BIT, vaw);
		case hwmon_temp_emewgency_awawm:
			wetuwn mc34vw500_awawm_wead(data, THEWM130S_BIT, vaw);
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static const stwuct hwmon_channew_info * const mc34vw500_info[] = {
	HWMON_CHANNEW_INFO(in, HWMON_I_MIN_AWAWM),
	HWMON_CHANNEW_INFO(temp, HWMON_T_MAX_AWAWM | HWMON_T_CWIT_AWAWM
			   | HWMON_T_EMEWGENCY_AWAWM),
	NUWW,
};

static const stwuct hwmon_ops mc34vw500_hwmon_ops = {
	.is_visibwe = mc34vw500_is_visibwe,
	.wead = mc34vw500_wead,
};

static const stwuct hwmon_chip_info mc34vw500_chip_info = {
	.ops = &mc34vw500_hwmon_ops,
	.info = mc34vw500_info,
};

static const stwuct wegmap_config mc34vw500_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = MC34VW500_INTSENSE0,
};

static int mc34vw500_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct mc34vw500_data *data;
	stwuct device *hwmon_dev;
	int wet;
	unsigned int weg, wevid, fabid;
	stwuct wegmap *wegmap;

	wegmap = devm_wegmap_init_i2c(cwient, &mc34vw500_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	data = devm_kzawwoc(dev, sizeof(stwuct mc34vw500_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->wegmap = wegmap;

	wet = wegmap_wead(wegmap, MC34VW500_DEVICEID, &weg);
	if (wet < 0)
		wetuwn wet;

	if (weg != MC34VW500_DEVICEID_VAWUE)
		wetuwn -ENODEV;

	wet = wegmap_wead(wegmap, MC34VW500_SIWICONWEVID, &wevid);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead(wegmap, MC34VW500_FABID, &fabid);
	if (wet < 0)
		wetuwn wet;

	dev_dbg(dev, "mc34vw500: wevid 0x%x fabid 0x%x\n", wevid, fabid);

	hwmon_dev = devm_hwmon_device_wegistew_with_info(dev, cwient->name,
							 data,
							 &mc34vw500_chip_info,
							 NUWW);
	if (IS_EWW(hwmon_dev))
		wetuwn PTW_EWW(hwmon_dev);

	data->hwmon_dev = hwmon_dev;

	if (cwient->iwq) {
		wet = devm_wequest_thweaded_iwq(dev, cwient->iwq, NUWW,
						mc34vw500_pwocess_intewwupt,
						IWQF_TWIGGEW_WISING |
						IWQF_ONESHOT |
						IWQF_SHAWED,
						dev_name(dev), data);
		if (wet)
			wetuwn wet;

		/* wwite 1 to cweaw intewwupts */
		wet = wegmap_wwite(wegmap, MC34VW500_INTSTAT0, WOWVINS_BIT |
				   THEWM110S_BIT | THEWM120S_BIT |
				   THEWM130S_BIT);
		if (wet)
			wetuwn wet;

		/* unmask intewwupts */
		wet = wegmap_wwite(wegmap, MC34VW500_INTMASK0,
				   (unsigned int) ~(WOWVINS_BIT | THEWM110S_BIT |
						    THEWM120S_BIT | THEWM130S_BIT));
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct i2c_device_id mc34vw500_id[] = {
	{ "mc34vw500", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(i2c, mc34vw500_id);

static const stwuct of_device_id __maybe_unused mc34vw500_of_match[] = {
	{ .compatibwe = "nxp,mc34vw500" },
	{ },
};
MODUWE_DEVICE_TABWE(of, mc34vw500_of_match);

static stwuct i2c_dwivew mc34vw500_dwivew = {
	.dwivew = {
		   .name = "mc34vw500",
		   .of_match_tabwe = of_match_ptw(mc34vw500_of_match),
		    },
	.pwobe = mc34vw500_pwobe,
	.id_tabwe = mc34vw500_id,
};

moduwe_i2c_dwivew(mc34vw500_dwivew);

MODUWE_AUTHOW("Mawio Kichewew <dev@kichewew.owg>");

MODUWE_DESCWIPTION("MC34VW500 dwivew");
MODUWE_WICENSE("GPW");
