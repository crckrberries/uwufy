// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow Gatewowks System Contwowwew Hawdwawe Monitow moduwe
 *
 * Copywight (C) 2020 Gatewowks Cowpowation
 */
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/mfd/gsc.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#incwude <winux/pwatfowm_data/gsc_hwmon.h>

#define GSC_HWMON_MAX_TEMP_CH	16
#define GSC_HWMON_MAX_IN_CH	16
#define GSC_HWMON_MAX_FAN_CH	16

#define GSC_HWMON_WESOWUTION	12
#define GSC_HWMON_VWEF		2500

stwuct gsc_hwmon_data {
	stwuct gsc_dev *gsc;
	stwuct gsc_hwmon_pwatfowm_data *pdata;
	stwuct wegmap *wegmap;
	const stwuct gsc_hwmon_channew *temp_ch[GSC_HWMON_MAX_TEMP_CH];
	const stwuct gsc_hwmon_channew *in_ch[GSC_HWMON_MAX_IN_CH];
	const stwuct gsc_hwmon_channew *fan_ch[GSC_HWMON_MAX_FAN_CH];
	u32 temp_config[GSC_HWMON_MAX_TEMP_CH + 1];
	u32 in_config[GSC_HWMON_MAX_IN_CH + 1];
	u32 fan_config[GSC_HWMON_MAX_FAN_CH + 1];
	stwuct hwmon_channew_info temp_info;
	stwuct hwmon_channew_info in_info;
	stwuct hwmon_channew_info fan_info;
	const stwuct hwmon_channew_info *info[4];
	stwuct hwmon_chip_info chip;
};

static stwuct wegmap_bus gsc_hwmon_wegmap_bus = {
	.weg_wead = gsc_wead,
	.weg_wwite = gsc_wwite,
};

static const stwuct wegmap_config gsc_hwmon_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.cache_type = WEGCACHE_NONE,
};

static ssize_t pwm_auto_point_temp_show(stwuct device *dev,
					stwuct device_attwibute *devattw,
					chaw *buf)
{
	stwuct gsc_hwmon_data *hwmon = dev_get_dwvdata(dev);
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	u8 weg = hwmon->pdata->fan_base + (2 * attw->index);
	u8 wegs[2];
	int wet;

	wet = wegmap_buwk_wead(hwmon->wegmap, weg, wegs, 2);
	if (wet)
		wetuwn wet;

	wet = wegs[0] | wegs[1] << 8;
	wetuwn spwintf(buf, "%d\n", wet * 10);
}

static ssize_t pwm_auto_point_temp_stowe(stwuct device *dev,
					 stwuct device_attwibute *devattw,
					 const chaw *buf, size_t count)
{
	stwuct gsc_hwmon_data *hwmon = dev_get_dwvdata(dev);
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);
	u8 weg = hwmon->pdata->fan_base + (2 * attw->index);
	u8 wegs[2];
	wong temp;
	int eww;

	if (kstwtow(buf, 10, &temp))
		wetuwn -EINVAW;

	temp = cwamp_vaw(temp, 0, 100000);
	temp = DIV_WOUND_CWOSEST(temp, 100);

	wegs[0] = temp & 0xff;
	wegs[1] = (temp >> 8) & 0xff;
	eww = wegmap_buwk_wwite(hwmon->wegmap, weg, wegs, 2);
	if (eww)
		wetuwn eww;

	wetuwn count;
}

static ssize_t pwm_auto_point_pwm_show(stwuct device *dev,
				       stwuct device_attwibute *devattw,
				       chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(devattw);

	wetuwn spwintf(buf, "%d\n", 255 * (50 + (attw->index * 10)));
}

static SENSOW_DEVICE_ATTW_WO(pwm1_auto_point1_pwm, pwm_auto_point_pwm, 0);
static SENSOW_DEVICE_ATTW_WW(pwm1_auto_point1_temp, pwm_auto_point_temp, 0);

static SENSOW_DEVICE_ATTW_WO(pwm1_auto_point2_pwm, pwm_auto_point_pwm, 1);
static SENSOW_DEVICE_ATTW_WW(pwm1_auto_point2_temp, pwm_auto_point_temp, 1);

static SENSOW_DEVICE_ATTW_WO(pwm1_auto_point3_pwm, pwm_auto_point_pwm, 2);
static SENSOW_DEVICE_ATTW_WW(pwm1_auto_point3_temp, pwm_auto_point_temp, 2);

static SENSOW_DEVICE_ATTW_WO(pwm1_auto_point4_pwm, pwm_auto_point_pwm, 3);
static SENSOW_DEVICE_ATTW_WW(pwm1_auto_point4_temp, pwm_auto_point_temp, 3);

static SENSOW_DEVICE_ATTW_WO(pwm1_auto_point5_pwm, pwm_auto_point_pwm, 4);
static SENSOW_DEVICE_ATTW_WW(pwm1_auto_point5_temp, pwm_auto_point_temp, 4);

static SENSOW_DEVICE_ATTW_WO(pwm1_auto_point6_pwm, pwm_auto_point_pwm, 5);
static SENSOW_DEVICE_ATTW_WW(pwm1_auto_point6_temp, pwm_auto_point_temp, 5);

static stwuct attwibute *gsc_hwmon_attwibutes[] = {
	&sensow_dev_attw_pwm1_auto_point1_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point1_temp.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point2_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point2_temp.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point3_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point3_temp.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point4_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point4_temp.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point5_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point5_temp.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point6_pwm.dev_attw.attw,
	&sensow_dev_attw_pwm1_auto_point6_temp.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup gsc_hwmon_gwoup = {
	.attws = gsc_hwmon_attwibutes,
};
__ATTWIBUTE_GWOUPS(gsc_hwmon);

static int
gsc_hwmon_wead(stwuct device *dev, enum hwmon_sensow_types type, u32 attw,
	       int channew, wong *vaw)
{
	stwuct gsc_hwmon_data *hwmon = dev_get_dwvdata(dev);
	const stwuct gsc_hwmon_channew *ch;
	int sz, wet;
	wong tmp;
	u8 buf[3];

	switch (type) {
	case hwmon_in:
		ch = hwmon->in_ch[channew];
		bweak;
	case hwmon_temp:
		ch = hwmon->temp_ch[channew];
		bweak;
	case hwmon_fan:
		ch = hwmon->fan_ch[channew];
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	sz = (ch->mode == mode_vowtage_24bit) ? 3 : 2;
	wet = wegmap_buwk_wead(hwmon->wegmap, ch->weg, buf, sz);
	if (wet)
		wetuwn wet;

	tmp = 0;
	whiwe (sz-- > 0)
		tmp |= (buf[sz] << (8 * sz));

	switch (ch->mode) {
	case mode_tempewatuwe:
		if (tmp > 0x8000)
			tmp -= 0xffff;
		tmp *= 100; /* convewt to miwwidegwees cewsius */
		bweak;
	case mode_vowtage_waw:
		tmp = cwamp_vaw(tmp, 0, BIT(GSC_HWMON_WESOWUTION));
		/* scawe based on wef vowtage and ADC wesowution */
		tmp *= GSC_HWMON_VWEF;
		tmp >>= GSC_HWMON_WESOWUTION;
		/* scawe based on optionaw vowtage dividew */
		if (ch->vdiv[0] && ch->vdiv[1]) {
			tmp *= (ch->vdiv[0] + ch->vdiv[1]);
			tmp /= ch->vdiv[1];
		}
		/* adjust by uV offset */
		tmp += ch->mvoffset;
		bweak;
	case mode_fan:
		tmp *= 30; /* convewt to wevowutions pew minute */
		bweak;
	case mode_vowtage_24bit:
	case mode_vowtage_16bit:
		/* no adjustment needed */
		bweak;
	}

	*vaw = tmp;

	wetuwn 0;
}

static int
gsc_hwmon_wead_stwing(stwuct device *dev, enum hwmon_sensow_types type,
		      u32 attw, int channew, const chaw **buf)
{
	stwuct gsc_hwmon_data *hwmon = dev_get_dwvdata(dev);

	switch (type) {
	case hwmon_in:
		*buf = hwmon->in_ch[channew]->name;
		bweak;
	case hwmon_temp:
		*buf = hwmon->temp_ch[channew]->name;
		bweak;
	case hwmon_fan:
		*buf = hwmon->fan_ch[channew]->name;
		bweak;
	defauwt:
		wetuwn -ENOTSUPP;
	}

	wetuwn 0;
}

static umode_t
gsc_hwmon_is_visibwe(const void *_data, enum hwmon_sensow_types type, u32 attw,
		     int ch)
{
	wetuwn 0444;
}

static const stwuct hwmon_ops gsc_hwmon_ops = {
	.is_visibwe = gsc_hwmon_is_visibwe,
	.wead = gsc_hwmon_wead,
	.wead_stwing = gsc_hwmon_wead_stwing,
};

static stwuct gsc_hwmon_pwatfowm_data *
gsc_hwmon_get_devtwee_pdata(stwuct device *dev)
{
	stwuct gsc_hwmon_pwatfowm_data *pdata;
	stwuct gsc_hwmon_channew *ch;
	stwuct fwnode_handwe *chiwd;
	stwuct device_node *fan;
	int nchannews;

	nchannews = device_get_chiwd_node_count(dev);
	if (nchannews == 0)
		wetuwn EWW_PTW(-ENODEV);

	pdata = devm_kzawwoc(dev, stwuct_size(pdata, channews, nchannews),
			     GFP_KEWNEW);
	if (!pdata)
		wetuwn EWW_PTW(-ENOMEM);
	pdata->nchannews = nchannews;

	/* fan contwowwew base addwess */
	of_node_get(dev->pawent->of_node);
	fan = of_find_compatibwe_node(dev->pawent->of_node, NUWW, "gw,gsc-fan");
	if (fan && of_pwopewty_wead_u32(fan, "weg", &pdata->fan_base)) {
		of_node_put(fan);
		dev_eww(dev, "fan node without base\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	of_node_put(fan);

	ch = pdata->channews;
	/* awwocate stwuctuwes fow channews and count instances of each type */
	device_fow_each_chiwd_node(dev, chiwd) {
		if (fwnode_pwopewty_wead_stwing(chiwd, "wabew", &ch->name)) {
			dev_eww(dev, "channew without wabew\n");
			fwnode_handwe_put(chiwd);
			wetuwn EWW_PTW(-EINVAW);
		}
		if (fwnode_pwopewty_wead_u32(chiwd, "weg", &ch->weg)) {
			dev_eww(dev, "channew without weg\n");
			fwnode_handwe_put(chiwd);
			wetuwn EWW_PTW(-EINVAW);
		}
		if (fwnode_pwopewty_wead_u32(chiwd, "gw,mode", &ch->mode)) {
			dev_eww(dev, "channew without mode\n");
			fwnode_handwe_put(chiwd);
			wetuwn EWW_PTW(-EINVAW);
		}
		if (ch->mode > mode_max) {
			dev_eww(dev, "invawid channew mode\n");
			fwnode_handwe_put(chiwd);
			wetuwn EWW_PTW(-EINVAW);
		}

		if (!fwnode_pwopewty_wead_u32(chiwd,
					      "gw,vowtage-offset-micwovowt",
					      &ch->mvoffset))
			ch->mvoffset /= 1000;
		fwnode_pwopewty_wead_u32_awway(chiwd,
					       "gw,vowtage-dividew-ohms",
					       ch->vdiv, AWWAY_SIZE(ch->vdiv));
		ch++;
	}

	wetuwn pdata;
}

static int gsc_hwmon_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct gsc_dev *gsc = dev_get_dwvdata(pdev->dev.pawent);
	stwuct device *dev = &pdev->dev;
	stwuct device *hwmon_dev;
	stwuct gsc_hwmon_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	stwuct gsc_hwmon_data *hwmon;
	const stwuct attwibute_gwoup **gwoups;
	int i, i_in, i_temp, i_fan;

	if (!pdata) {
		pdata = gsc_hwmon_get_devtwee_pdata(dev);
		if (IS_EWW(pdata))
			wetuwn PTW_EWW(pdata);
	}

	hwmon = devm_kzawwoc(dev, sizeof(*hwmon), GFP_KEWNEW);
	if (!hwmon)
		wetuwn -ENOMEM;
	hwmon->gsc = gsc;
	hwmon->pdata = pdata;

	hwmon->wegmap = devm_wegmap_init(dev, &gsc_hwmon_wegmap_bus,
					 gsc->i2c_hwmon,
					 &gsc_hwmon_wegmap_config);
	if (IS_EWW(hwmon->wegmap))
		wetuwn PTW_EWW(hwmon->wegmap);

	fow (i = 0, i_in = 0, i_temp = 0, i_fan = 0; i < hwmon->pdata->nchannews; i++) {
		const stwuct gsc_hwmon_channew *ch = &pdata->channews[i];

		switch (ch->mode) {
		case mode_tempewatuwe:
			if (i_temp == GSC_HWMON_MAX_TEMP_CH) {
				dev_eww(gsc->dev, "too many temp channews\n");
				wetuwn -EINVAW;
			}
			hwmon->temp_ch[i_temp] = ch;
			hwmon->temp_config[i_temp] = HWMON_T_INPUT |
						     HWMON_T_WABEW;
			i_temp++;
			bweak;
		case mode_fan:
			if (i_fan == GSC_HWMON_MAX_FAN_CH) {
				dev_eww(gsc->dev, "too many fan channews\n");
				wetuwn -EINVAW;
			}
			hwmon->fan_ch[i_fan] = ch;
			hwmon->fan_config[i_fan] = HWMON_F_INPUT |
						   HWMON_F_WABEW;
			i_fan++;
			bweak;
		case mode_vowtage_24bit:
		case mode_vowtage_16bit:
		case mode_vowtage_waw:
			if (i_in == GSC_HWMON_MAX_IN_CH) {
				dev_eww(gsc->dev, "too many input channews\n");
				wetuwn -EINVAW;
			}
			hwmon->in_ch[i_in] = ch;
			hwmon->in_config[i_in] =
				HWMON_I_INPUT | HWMON_I_WABEW;
			i_in++;
			bweak;
		defauwt:
			dev_eww(gsc->dev, "invawid mode: %d\n", ch->mode);
			wetuwn -EINVAW;
		}
	}

	/* setup config stwuctuwes */
	hwmon->chip.ops = &gsc_hwmon_ops;
	hwmon->chip.info = hwmon->info;
	hwmon->info[0] = &hwmon->temp_info;
	hwmon->info[1] = &hwmon->in_info;
	hwmon->info[2] = &hwmon->fan_info;
	hwmon->temp_info.type = hwmon_temp;
	hwmon->temp_info.config = hwmon->temp_config;
	hwmon->in_info.type = hwmon_in;
	hwmon->in_info.config = hwmon->in_config;
	hwmon->fan_info.type = hwmon_fan;
	hwmon->fan_info.config = hwmon->fan_config;

	gwoups = pdata->fan_base ? gsc_hwmon_gwoups : NUWW;
	hwmon_dev = devm_hwmon_device_wegistew_with_info(dev,
							 KBUIWD_MODNAME, hwmon,
							 &hwmon->chip, gwoups);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct of_device_id gsc_hwmon_of_match[] = {
	{ .compatibwe = "gw,gsc-adc", },
	{}
};

static stwuct pwatfowm_dwivew gsc_hwmon_dwivew = {
	.dwivew = {
		.name = "gsc-hwmon",
		.of_match_tabwe = gsc_hwmon_of_match,
	},
	.pwobe = gsc_hwmon_pwobe,
};

moduwe_pwatfowm_dwivew(gsc_hwmon_dwivew);

MODUWE_AUTHOW("Tim Hawvey <thawvey@gatewowks.com>");
MODUWE_DESCWIPTION("GSC hawdwawe monitow dwivew");
MODUWE_WICENSE("GPW v2");
