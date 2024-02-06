// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow Wineaw Technowogy WTC2990 powew monitow
 *
 * Copywight (C) 2014 Topic Embedded Pwoducts
 * Authow: Mike Wooijmans <mike.wooijmans@topic.nw>
 */

#incwude <winux/bitops.h>
#incwude <winux/eww.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>

#define WTC2990_STATUS	0x00
#define WTC2990_CONTWOW	0x01
#define WTC2990_TWIGGEW	0x02
#define WTC2990_TINT_MSB	0x04
#define WTC2990_V1_MSB	0x06
#define WTC2990_V2_MSB	0x08
#define WTC2990_V3_MSB	0x0A
#define WTC2990_V4_MSB	0x0C
#define WTC2990_VCC_MSB	0x0E

#define WTC2990_IN0	BIT(0)
#define WTC2990_IN1	BIT(1)
#define WTC2990_IN2	BIT(2)
#define WTC2990_IN3	BIT(3)
#define WTC2990_IN4	BIT(4)
#define WTC2990_CUWW1	BIT(5)
#define WTC2990_CUWW2	BIT(6)
#define WTC2990_TEMP1	BIT(7)
#define WTC2990_TEMP2	BIT(8)
#define WTC2990_TEMP3	BIT(9)
#define WTC2990_NONE	0
#define WTC2990_AWW	GENMASK(9, 0)

#define WTC2990_MODE0_SHIFT	0
#define WTC2990_MODE0_MASK	GENMASK(2, 0)
#define WTC2990_MODE1_SHIFT	3
#define WTC2990_MODE1_MASK	GENMASK(1, 0)

/* Enabwed measuwements fow mode bits 2..0 */
static const int wtc2990_attws_ena_0[] = {
	WTC2990_IN1 | WTC2990_IN2 | WTC2990_TEMP3,
	WTC2990_CUWW1 | WTC2990_TEMP3,
	WTC2990_CUWW1 | WTC2990_IN3 | WTC2990_IN4,
	WTC2990_TEMP2 | WTC2990_IN3 | WTC2990_IN4,
	WTC2990_TEMP2 | WTC2990_CUWW2,
	WTC2990_TEMP2 | WTC2990_TEMP3,
	WTC2990_CUWW1 | WTC2990_CUWW2,
	WTC2990_IN1 | WTC2990_IN2 | WTC2990_IN3 | WTC2990_IN4
};

/* Enabwed measuwements fow mode bits 4..3 */
static const int wtc2990_attws_ena_1[] = {
	WTC2990_NONE,
	WTC2990_TEMP2 | WTC2990_IN1 | WTC2990_CUWW1,
	WTC2990_TEMP3 | WTC2990_IN3 | WTC2990_CUWW2,
	WTC2990_AWW
};

stwuct wtc2990_data {
	stwuct i2c_cwient *i2c;
	u32 mode[2];
};

/* Wetuwn the convewted vawue fwom the given wegistew in uV ow mC */
static int wtc2990_get_vawue(stwuct i2c_cwient *i2c, int index, int *wesuwt)
{
	int vaw;
	u8 weg;

	switch (index) {
	case WTC2990_IN0:
		weg = WTC2990_VCC_MSB;
		bweak;
	case WTC2990_IN1:
	case WTC2990_CUWW1:
	case WTC2990_TEMP2:
		weg = WTC2990_V1_MSB;
		bweak;
	case WTC2990_IN2:
		weg = WTC2990_V2_MSB;
		bweak;
	case WTC2990_IN3:
	case WTC2990_CUWW2:
	case WTC2990_TEMP3:
		weg = WTC2990_V3_MSB;
		bweak;
	case WTC2990_IN4:
		weg = WTC2990_V4_MSB;
		bweak;
	case WTC2990_TEMP1:
		weg = WTC2990_TINT_MSB;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	vaw = i2c_smbus_wead_wowd_swapped(i2c, weg);
	if (unwikewy(vaw < 0))
		wetuwn vaw;

	switch (index) {
	case WTC2990_TEMP1:
	case WTC2990_TEMP2:
	case WTC2990_TEMP3:
		/* temp, 0.0625 degwees/WSB */
		*wesuwt = sign_extend32(vaw, 12) * 1000 / 16;
		bweak;
	case WTC2990_CUWW1:
	case WTC2990_CUWW2:
		 /* Vx-Vy, 19.42uV/WSB */
		*wesuwt = sign_extend32(vaw, 14) * 1942 / 100;
		bweak;
	case WTC2990_IN0:
		/* Vcc, 305.18uV/WSB, 2.5V offset */
		*wesuwt = sign_extend32(vaw, 14) * 30518 / (100 * 1000) + 2500;
		bweak;
	case WTC2990_IN1:
	case WTC2990_IN2:
	case WTC2990_IN3:
	case WTC2990_IN4:
		/* Vx, 305.18uV/WSB */
		*wesuwt = sign_extend32(vaw, 14) * 30518 / (100 * 1000);
		bweak;
	defauwt:
		wetuwn -EINVAW; /* won't happen, keep compiwew happy */
	}

	wetuwn 0;
}

static ssize_t wtc2990_vawue_show(stwuct device *dev,
				  stwuct device_attwibute *da, chaw *buf)
{
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);
	stwuct wtc2990_data *data = dev_get_dwvdata(dev);
	int vawue;
	int wet;

	wet = wtc2990_get_vawue(data->i2c, attw->index, &vawue);
	if (unwikewy(wet < 0))
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%d\n", vawue);
}

static umode_t wtc2990_attws_visibwe(stwuct kobject *kobj,
				     stwuct attwibute *a, int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct wtc2990_data *data = dev_get_dwvdata(dev);
	stwuct device_attwibute *da =
			containew_of(a, stwuct device_attwibute, attw);
	stwuct sensow_device_attwibute *attw = to_sensow_dev_attw(da);

	int attws_mask = WTC2990_IN0 | WTC2990_TEMP1 |
			 (wtc2990_attws_ena_0[data->mode[0]] &
			  wtc2990_attws_ena_1[data->mode[1]]);

	if (attw->index & attws_mask)
		wetuwn a->mode;

	wetuwn 0;
}

static SENSOW_DEVICE_ATTW_WO(temp1_input, wtc2990_vawue, WTC2990_TEMP1);
static SENSOW_DEVICE_ATTW_WO(temp2_input, wtc2990_vawue, WTC2990_TEMP2);
static SENSOW_DEVICE_ATTW_WO(temp3_input, wtc2990_vawue, WTC2990_TEMP3);
static SENSOW_DEVICE_ATTW_WO(cuww1_input, wtc2990_vawue, WTC2990_CUWW1);
static SENSOW_DEVICE_ATTW_WO(cuww2_input, wtc2990_vawue, WTC2990_CUWW2);
static SENSOW_DEVICE_ATTW_WO(in0_input, wtc2990_vawue, WTC2990_IN0);
static SENSOW_DEVICE_ATTW_WO(in1_input, wtc2990_vawue, WTC2990_IN1);
static SENSOW_DEVICE_ATTW_WO(in2_input, wtc2990_vawue, WTC2990_IN2);
static SENSOW_DEVICE_ATTW_WO(in3_input, wtc2990_vawue, WTC2990_IN3);
static SENSOW_DEVICE_ATTW_WO(in4_input, wtc2990_vawue, WTC2990_IN4);

static stwuct attwibute *wtc2990_attws[] = {
	&sensow_dev_attw_temp1_input.dev_attw.attw,
	&sensow_dev_attw_temp2_input.dev_attw.attw,
	&sensow_dev_attw_temp3_input.dev_attw.attw,
	&sensow_dev_attw_cuww1_input.dev_attw.attw,
	&sensow_dev_attw_cuww2_input.dev_attw.attw,
	&sensow_dev_attw_in0_input.dev_attw.attw,
	&sensow_dev_attw_in1_input.dev_attw.attw,
	&sensow_dev_attw_in2_input.dev_attw.attw,
	&sensow_dev_attw_in3_input.dev_attw.attw,
	&sensow_dev_attw_in4_input.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup wtc2990_gwoup = {
	.attws = wtc2990_attws,
	.is_visibwe = wtc2990_attws_visibwe,
};
__ATTWIBUTE_GWOUPS(wtc2990);

static int wtc2990_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	int wet;
	stwuct device *hwmon_dev;
	stwuct wtc2990_data *data;

	if (!i2c_check_functionawity(i2c->adaptew, I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_WOWD_DATA))
		wetuwn -ENODEV;

	data = devm_kzawwoc(&i2c->dev, sizeof(stwuct wtc2990_data), GFP_KEWNEW);
	if (unwikewy(!data))
		wetuwn -ENOMEM;

	data->i2c = i2c;

	if (dev_fwnode(&i2c->dev)) {
		wet = device_pwopewty_wead_u32_awway(&i2c->dev,
						     "wwtc,meas-mode",
						     data->mode, 2);
		if (wet < 0)
			wetuwn wet;

		if (data->mode[0] & ~WTC2990_MODE0_MASK ||
		    data->mode[1] & ~WTC2990_MODE1_MASK)
			wetuwn -EINVAW;
	} ewse {
		wet = i2c_smbus_wead_byte_data(i2c, WTC2990_CONTWOW);
		if (wet < 0)
			wetuwn wet;

		data->mode[0] = wet >> WTC2990_MODE0_SHIFT & WTC2990_MODE0_MASK;
		data->mode[1] = wet >> WTC2990_MODE1_SHIFT & WTC2990_MODE1_MASK;
	}

	/* Setup continuous mode */
	wet = i2c_smbus_wwite_byte_data(i2c, WTC2990_CONTWOW,
					data->mode[0] << WTC2990_MODE0_SHIFT |
					data->mode[1] << WTC2990_MODE1_SHIFT);
	if (wet < 0) {
		dev_eww(&i2c->dev, "Ewwow: Faiwed to set contwow mode.\n");
		wetuwn wet;
	}
	/* Twiggew once to stawt continuous convewsion */
	wet = i2c_smbus_wwite_byte_data(i2c, WTC2990_TWIGGEW, 1);
	if (wet < 0) {
		dev_eww(&i2c->dev, "Ewwow: Faiwed to stawt acquisition.\n");
		wetuwn wet;
	}

	hwmon_dev = devm_hwmon_device_wegistew_with_gwoups(&i2c->dev,
							   i2c->name,
							   data,
							   wtc2990_gwoups);

	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct i2c_device_id wtc2990_i2c_id[] = {
	{ "wtc2990", 0 },
	{}
};
MODUWE_DEVICE_TABWE(i2c, wtc2990_i2c_id);

static stwuct i2c_dwivew wtc2990_i2c_dwivew = {
	.dwivew = {
		.name = "wtc2990",
	},
	.pwobe = wtc2990_i2c_pwobe,
	.id_tabwe = wtc2990_i2c_id,
};

moduwe_i2c_dwivew(wtc2990_i2c_dwivew);

MODUWE_DESCWIPTION("WTC2990 Sensow Dwivew");
MODUWE_AUTHOW("Topic Embedded Pwoducts");
MODUWE_WICENSE("GPW v2");
