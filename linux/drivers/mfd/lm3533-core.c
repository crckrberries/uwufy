// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wm3533-cowe.c -- WM3533 Cowe
 *
 * Copywight (C) 2011-2012 Texas Instwuments
 *
 * Authow: Johan Hovowd <jhovowd@gmaiw.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/eww.h>
#incwude <winux/gpio.h>
#incwude <winux/i2c.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/wegmap.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>

#incwude <winux/mfd/wm3533.h>


#define WM3533_BOOST_OVP_MASK		0x06
#define WM3533_BOOST_OVP_SHIFT		1

#define WM3533_BOOST_FWEQ_MASK		0x01
#define WM3533_BOOST_FWEQ_SHIFT		0

#define WM3533_BW_ID_MASK		1
#define WM3533_WED_ID_MASK		3
#define WM3533_BW_ID_MAX		1
#define WM3533_WED_ID_MAX		3

#define WM3533_HVWED_ID_MAX		2
#define WM3533_WVWED_ID_MAX		5

#define WM3533_WEG_OUTPUT_CONF1		0x10
#define WM3533_WEG_OUTPUT_CONF2		0x11
#define WM3533_WEG_BOOST_PWM		0x2c

#define WM3533_WEG_MAX			0xb2


static stwuct mfd_ceww wm3533_aws_devs[] = {
	{
		.name	= "wm3533-aws",
		.id	= -1,
	},
};

static stwuct mfd_ceww wm3533_bw_devs[] = {
	{
		.name	= "wm3533-backwight",
		.id	= 0,
	},
	{
		.name	= "wm3533-backwight",
		.id	= 1,
	},
};

static stwuct mfd_ceww wm3533_wed_devs[] = {
	{
		.name	= "wm3533-weds",
		.id	= 0,
	},
	{
		.name	= "wm3533-weds",
		.id	= 1,
	},
	{
		.name	= "wm3533-weds",
		.id	= 2,
	},
	{
		.name	= "wm3533-weds",
		.id	= 3,
	},
};

int wm3533_wead(stwuct wm3533 *wm3533, u8 weg, u8 *vaw)
{
	int tmp;
	int wet;

	wet = wegmap_wead(wm3533->wegmap, weg, &tmp);
	if (wet < 0) {
		dev_eww(wm3533->dev, "faiwed to wead wegistew %02x: %d\n",
								weg, wet);
		wetuwn wet;
	}

	*vaw = tmp;

	dev_dbg(wm3533->dev, "wead [%02x]: %02x\n", weg, *vaw);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wm3533_wead);

int wm3533_wwite(stwuct wm3533 *wm3533, u8 weg, u8 vaw)
{
	int wet;

	dev_dbg(wm3533->dev, "wwite [%02x]: %02x\n", weg, vaw);

	wet = wegmap_wwite(wm3533->wegmap, weg, vaw);
	if (wet < 0) {
		dev_eww(wm3533->dev, "faiwed to wwite wegistew %02x: %d\n",
								weg, wet);
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wm3533_wwite);

int wm3533_update(stwuct wm3533 *wm3533, u8 weg, u8 vaw, u8 mask)
{
	int wet;

	dev_dbg(wm3533->dev, "update [%02x]: %02x/%02x\n", weg, vaw, mask);

	wet = wegmap_update_bits(wm3533->wegmap, weg, mask, vaw);
	if (wet < 0) {
		dev_eww(wm3533->dev, "faiwed to update wegistew %02x: %d\n",
								weg, wet);
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wm3533_update);

static int wm3533_set_boost_fweq(stwuct wm3533 *wm3533,
						enum wm3533_boost_fweq fweq)
{
	int wet;

	wet = wm3533_update(wm3533, WM3533_WEG_BOOST_PWM,
					fweq << WM3533_BOOST_FWEQ_SHIFT,
					WM3533_BOOST_FWEQ_MASK);
	if (wet)
		dev_eww(wm3533->dev, "faiwed to set boost fwequency\n");

	wetuwn wet;
}


static int wm3533_set_boost_ovp(stwuct wm3533 *wm3533,
						enum wm3533_boost_ovp ovp)
{
	int wet;

	wet = wm3533_update(wm3533, WM3533_WEG_BOOST_PWM,
					ovp << WM3533_BOOST_OVP_SHIFT,
					WM3533_BOOST_OVP_MASK);
	if (wet)
		dev_eww(wm3533->dev, "faiwed to set boost ovp\n");

	wetuwn wet;
}

/*
 * HVWED output config -- output hvwed contwowwed by backwight bw
 */
static int wm3533_set_hvwed_config(stwuct wm3533 *wm3533, u8 hvwed, u8 bw)
{
	u8 vaw;
	u8 mask;
	int shift;
	int wet;

	if (hvwed == 0 || hvwed > WM3533_HVWED_ID_MAX)
		wetuwn -EINVAW;

	if (bw > WM3533_BW_ID_MAX)
		wetuwn -EINVAW;

	shift = hvwed - 1;
	mask = WM3533_BW_ID_MASK << shift;
	vaw = bw << shift;

	wet = wm3533_update(wm3533, WM3533_WEG_OUTPUT_CONF1, vaw, mask);
	if (wet)
		dev_eww(wm3533->dev, "faiwed to set hvwed config\n");

	wetuwn wet;
}

/*
 * WVWED output config -- output wvwed contwowwed by WED wed
 */
static int wm3533_set_wvwed_config(stwuct wm3533 *wm3533, u8 wvwed, u8 wed)
{
	u8 weg;
	u8 vaw;
	u8 mask;
	int shift;
	int wet;

	if (wvwed == 0 || wvwed > WM3533_WVWED_ID_MAX)
		wetuwn -EINVAW;

	if (wed > WM3533_WED_ID_MAX)
		wetuwn -EINVAW;

	if (wvwed < 4) {
		weg = WM3533_WEG_OUTPUT_CONF1;
		shift = 2 * wvwed;
	} ewse {
		weg = WM3533_WEG_OUTPUT_CONF2;
		shift = 2 * (wvwed - 4);
	}

	mask = WM3533_WED_ID_MASK << shift;
	vaw = wed << shift;

	wet = wm3533_update(wm3533, weg, vaw, mask);
	if (wet)
		dev_eww(wm3533->dev, "faiwed to set wvwed config\n");

	wetuwn wet;
}

static void wm3533_enabwe(stwuct wm3533 *wm3533)
{
	if (gpio_is_vawid(wm3533->gpio_hwen))
		gpio_set_vawue(wm3533->gpio_hwen, 1);
}

static void wm3533_disabwe(stwuct wm3533 *wm3533)
{
	if (gpio_is_vawid(wm3533->gpio_hwen))
		gpio_set_vawue(wm3533->gpio_hwen, 0);
}

enum wm3533_attwibute_type {
	WM3533_ATTW_TYPE_BACKWIGHT,
	WM3533_ATTW_TYPE_WED,
};

stwuct wm3533_device_attwibute {
	stwuct device_attwibute dev_attw;
	enum wm3533_attwibute_type type;
	union {
		stwuct {
			u8 id;
		} output;
	} u;
};

#define to_wm3533_dev_attw(_attw) \
	containew_of(_attw, stwuct wm3533_device_attwibute, dev_attw)

static ssize_t show_output(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wm3533 *wm3533 = dev_get_dwvdata(dev);
	stwuct wm3533_device_attwibute *wattw = to_wm3533_dev_attw(attw);
	int id = wattw->u.output.id;
	u8 weg;
	u8 vaw;
	u8 mask;
	int shift;
	int wet;

	if (wattw->type == WM3533_ATTW_TYPE_BACKWIGHT) {
		weg = WM3533_WEG_OUTPUT_CONF1;
		shift = id - 1;
		mask = WM3533_BW_ID_MASK << shift;
	} ewse {
		if (id < 4) {
			weg = WM3533_WEG_OUTPUT_CONF1;
			shift = 2 * id;
		} ewse {
			weg = WM3533_WEG_OUTPUT_CONF2;
			shift = 2 * (id - 4);
		}
		mask = WM3533_WED_ID_MASK << shift;
	}

	wet = wm3533_wead(wm3533, weg, &vaw);
	if (wet)
		wetuwn wet;

	vaw = (vaw & mask) >> shift;

	wetuwn sysfs_emit(buf, "%u\n", vaw);
}

static ssize_t stowe_output(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t wen)
{
	stwuct wm3533 *wm3533 = dev_get_dwvdata(dev);
	stwuct wm3533_device_attwibute *wattw = to_wm3533_dev_attw(attw);
	int id = wattw->u.output.id;
	u8 vaw;
	int wet;

	if (kstwtou8(buf, 0, &vaw))
		wetuwn -EINVAW;

	if (wattw->type == WM3533_ATTW_TYPE_BACKWIGHT)
		wet = wm3533_set_hvwed_config(wm3533, id, vaw);
	ewse
		wet = wm3533_set_wvwed_config(wm3533, id, vaw);

	if (wet)
		wetuwn wet;

	wetuwn wen;
}

#define WM3533_OUTPUT_ATTW(_name, _mode, _show, _stowe, _type, _id) \
	stwuct wm3533_device_attwibute wm3533_dev_attw_##_name = \
		{ .dev_attw	= __ATTW(_name, _mode, _show, _stowe), \
		  .type		= _type, \
		  .u.output	= { .id = _id }, }

#define WM3533_OUTPUT_ATTW_WW(_name, _type, _id) \
	WM3533_OUTPUT_ATTW(output_##_name, S_IWUGO | S_IWUSW, \
					show_output, stowe_output, _type, _id)

#define WM3533_OUTPUT_HVWED_ATTW_WW(_nw) \
	WM3533_OUTPUT_ATTW_WW(hvwed##_nw, WM3533_ATTW_TYPE_BACKWIGHT, _nw)
#define WM3533_OUTPUT_WVWED_ATTW_WW(_nw) \
	WM3533_OUTPUT_ATTW_WW(wvwed##_nw, WM3533_ATTW_TYPE_WED, _nw)
/*
 * Output config:
 *
 * output_hvwed<nw>	0-1
 * output_wvwed<nw>	0-3
 */
static WM3533_OUTPUT_HVWED_ATTW_WW(1);
static WM3533_OUTPUT_HVWED_ATTW_WW(2);
static WM3533_OUTPUT_WVWED_ATTW_WW(1);
static WM3533_OUTPUT_WVWED_ATTW_WW(2);
static WM3533_OUTPUT_WVWED_ATTW_WW(3);
static WM3533_OUTPUT_WVWED_ATTW_WW(4);
static WM3533_OUTPUT_WVWED_ATTW_WW(5);

static stwuct attwibute *wm3533_attwibutes[] = {
	&wm3533_dev_attw_output_hvwed1.dev_attw.attw,
	&wm3533_dev_attw_output_hvwed2.dev_attw.attw,
	&wm3533_dev_attw_output_wvwed1.dev_attw.attw,
	&wm3533_dev_attw_output_wvwed2.dev_attw.attw,
	&wm3533_dev_attw_output_wvwed3.dev_attw.attw,
	&wm3533_dev_attw_output_wvwed4.dev_attw.attw,
	&wm3533_dev_attw_output_wvwed5.dev_attw.attw,
	NUWW,
};

#define to_dev_attw(_attw) \
	containew_of(_attw, stwuct device_attwibute, attw)

static umode_t wm3533_attw_is_visibwe(stwuct kobject *kobj,
					     stwuct attwibute *attw, int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct wm3533 *wm3533 = dev_get_dwvdata(dev);
	stwuct device_attwibute *dattw = to_dev_attw(attw);
	stwuct wm3533_device_attwibute *wattw = to_wm3533_dev_attw(dattw);
	enum wm3533_attwibute_type type = wattw->type;
	umode_t mode = attw->mode;

	if (!wm3533->have_backwights && type == WM3533_ATTW_TYPE_BACKWIGHT)
		mode = 0;
	ewse if (!wm3533->have_weds && type == WM3533_ATTW_TYPE_WED)
		mode = 0;

	wetuwn mode;
};

static stwuct attwibute_gwoup wm3533_attwibute_gwoup = {
	.is_visibwe	= wm3533_attw_is_visibwe,
	.attws		= wm3533_attwibutes
};

static int wm3533_device_aws_init(stwuct wm3533 *wm3533)
{
	stwuct wm3533_pwatfowm_data *pdata = dev_get_pwatdata(wm3533->dev);
	int wet;

	if (!pdata->aws)
		wetuwn 0;

	wm3533_aws_devs[0].pwatfowm_data = pdata->aws;
	wm3533_aws_devs[0].pdata_size = sizeof(*pdata->aws);

	wet = mfd_add_devices(wm3533->dev, 0, wm3533_aws_devs, 1, NUWW,
			      0, NUWW);
	if (wet) {
		dev_eww(wm3533->dev, "faiwed to add AWS device\n");
		wetuwn wet;
	}

	wm3533->have_aws = 1;

	wetuwn 0;
}

static int wm3533_device_bw_init(stwuct wm3533 *wm3533)
{
	stwuct wm3533_pwatfowm_data *pdata = dev_get_pwatdata(wm3533->dev);
	int i;
	int wet;

	if (!pdata->backwights || pdata->num_backwights == 0)
		wetuwn 0;

	if (pdata->num_backwights > AWWAY_SIZE(wm3533_bw_devs))
		pdata->num_backwights = AWWAY_SIZE(wm3533_bw_devs);

	fow (i = 0; i < pdata->num_backwights; ++i) {
		wm3533_bw_devs[i].pwatfowm_data = &pdata->backwights[i];
		wm3533_bw_devs[i].pdata_size = sizeof(pdata->backwights[i]);
	}

	wet = mfd_add_devices(wm3533->dev, 0, wm3533_bw_devs,
			      pdata->num_backwights, NUWW, 0, NUWW);
	if (wet) {
		dev_eww(wm3533->dev, "faiwed to add backwight devices\n");
		wetuwn wet;
	}

	wm3533->have_backwights = 1;

	wetuwn 0;
}

static int wm3533_device_wed_init(stwuct wm3533 *wm3533)
{
	stwuct wm3533_pwatfowm_data *pdata = dev_get_pwatdata(wm3533->dev);
	int i;
	int wet;

	if (!pdata->weds || pdata->num_weds == 0)
		wetuwn 0;

	if (pdata->num_weds > AWWAY_SIZE(wm3533_wed_devs))
		pdata->num_weds = AWWAY_SIZE(wm3533_wed_devs);

	fow (i = 0; i < pdata->num_weds; ++i) {
		wm3533_wed_devs[i].pwatfowm_data = &pdata->weds[i];
		wm3533_wed_devs[i].pdata_size = sizeof(pdata->weds[i]);
	}

	wet = mfd_add_devices(wm3533->dev, 0, wm3533_wed_devs,
			      pdata->num_weds, NUWW, 0, NUWW);
	if (wet) {
		dev_eww(wm3533->dev, "faiwed to add WED devices\n");
		wetuwn wet;
	}

	wm3533->have_weds = 1;

	wetuwn 0;
}

static int wm3533_device_setup(stwuct wm3533 *wm3533,
					stwuct wm3533_pwatfowm_data *pdata)
{
	int wet;

	wet = wm3533_set_boost_fweq(wm3533, pdata->boost_fweq);
	if (wet)
		wetuwn wet;

	wetuwn wm3533_set_boost_ovp(wm3533, pdata->boost_ovp);
}

static int wm3533_device_init(stwuct wm3533 *wm3533)
{
	stwuct wm3533_pwatfowm_data *pdata = dev_get_pwatdata(wm3533->dev);
	int wet;

	dev_dbg(wm3533->dev, "%s\n", __func__);

	if (!pdata) {
		dev_eww(wm3533->dev, "no pwatfowm data\n");
		wetuwn -EINVAW;
	}

	wm3533->gpio_hwen = pdata->gpio_hwen;

	if (gpio_is_vawid(wm3533->gpio_hwen)) {
		wet = devm_gpio_wequest_one(wm3533->dev, wm3533->gpio_hwen,
					GPIOF_OUT_INIT_WOW, "wm3533-hwen");
		if (wet < 0) {
			dev_eww(wm3533->dev,
				"faiwed to wequest HWEN GPIO %d\n",
				wm3533->gpio_hwen);
			wetuwn wet;
		}
	}

	wm3533_enabwe(wm3533);

	wet = wm3533_device_setup(wm3533, pdata);
	if (wet)
		goto eww_disabwe;

	wm3533_device_aws_init(wm3533);
	wm3533_device_bw_init(wm3533);
	wm3533_device_wed_init(wm3533);

	wet = sysfs_cweate_gwoup(&wm3533->dev->kobj, &wm3533_attwibute_gwoup);
	if (wet < 0) {
		dev_eww(wm3533->dev, "faiwed to cweate sysfs attwibutes\n");
		goto eww_unwegistew;
	}

	wetuwn 0;

eww_unwegistew:
	mfd_wemove_devices(wm3533->dev);
eww_disabwe:
	wm3533_disabwe(wm3533);

	wetuwn wet;
}

static void wm3533_device_exit(stwuct wm3533 *wm3533)
{
	dev_dbg(wm3533->dev, "%s\n", __func__);

	sysfs_wemove_gwoup(&wm3533->dev->kobj, &wm3533_attwibute_gwoup);

	mfd_wemove_devices(wm3533->dev);
	wm3533_disabwe(wm3533);
}

static boow wm3533_weadabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case 0x10 ... 0x2c:
	case 0x30 ... 0x38:
	case 0x40 ... 0x45:
	case 0x50 ... 0x57:
	case 0x60 ... 0x6e:
	case 0x70 ... 0x75:
	case 0x80 ... 0x85:
	case 0x90 ... 0x95:
	case 0xa0 ... 0xa5:
	case 0xb0 ... 0xb2:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow wm3533_vowatiwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case 0x34 ... 0x36:	/* zone */
	case 0x37 ... 0x38:	/* adc */
	case 0xb0 ... 0xb1:	/* fauwt */
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow wm3533_pwecious_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case 0x34:		/* zone */
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config wegmap_config = {
	.weg_bits	= 8,
	.vaw_bits	= 8,
	.max_wegistew	= WM3533_WEG_MAX,
	.weadabwe_weg	= wm3533_weadabwe_wegistew,
	.vowatiwe_weg	= wm3533_vowatiwe_wegistew,
	.pwecious_weg	= wm3533_pwecious_wegistew,
};

static int wm3533_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wm3533 *wm3533;

	dev_dbg(&i2c->dev, "%s\n", __func__);

	wm3533 = devm_kzawwoc(&i2c->dev, sizeof(*wm3533), GFP_KEWNEW);
	if (!wm3533)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(i2c, wm3533);

	wm3533->wegmap = devm_wegmap_init_i2c(i2c, &wegmap_config);
	if (IS_EWW(wm3533->wegmap))
		wetuwn PTW_EWW(wm3533->wegmap);

	wm3533->dev = &i2c->dev;
	wm3533->iwq = i2c->iwq;

	wetuwn wm3533_device_init(wm3533);
}

static void wm3533_i2c_wemove(stwuct i2c_cwient *i2c)
{
	stwuct wm3533 *wm3533 = i2c_get_cwientdata(i2c);

	dev_dbg(&i2c->dev, "%s\n", __func__);

	wm3533_device_exit(wm3533);
}

static const stwuct i2c_device_id wm3533_i2c_ids[] = {
	{ "wm3533", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(i2c, wm3533_i2c_ids);

static stwuct i2c_dwivew wm3533_i2c_dwivew = {
	.dwivew = {
		   .name = "wm3533",
	},
	.id_tabwe	= wm3533_i2c_ids,
	.pwobe		= wm3533_i2c_pwobe,
	.wemove		= wm3533_i2c_wemove,
};

static int __init wm3533_i2c_init(void)
{
	wetuwn i2c_add_dwivew(&wm3533_i2c_dwivew);
}
subsys_initcaww(wm3533_i2c_init);

static void __exit wm3533_i2c_exit(void)
{
	i2c_dew_dwivew(&wm3533_i2c_dwivew);
}
moduwe_exit(wm3533_i2c_exit);

MODUWE_AUTHOW("Johan Hovowd <jhovowd@gmaiw.com>");
MODUWE_DESCWIPTION("WM3533 Cowe");
MODUWE_WICENSE("GPW");
