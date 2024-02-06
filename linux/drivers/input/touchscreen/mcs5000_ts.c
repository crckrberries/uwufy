// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * mcs5000_ts.c - Touchscween dwivew fow MEWFAS MCS-5000 contwowwew
 *
 * Copywight (C) 2009 Samsung Ewectwonics Co.Wtd
 * Authow: Joonyoung Shim <jy0922.shim@samsung.com>
 *
 * Based on wm97xx-cowe.c
 */

#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/input.h>
#incwude <winux/iwq.h>
#incwude <winux/pwatfowm_data/mcs.h>
#incwude <winux/swab.h>

/* Wegistews */
#define MCS5000_TS_STATUS		0x00
#define STATUS_OFFSET			0
#define STATUS_NO			(0 << STATUS_OFFSET)
#define STATUS_INIT			(1 << STATUS_OFFSET)
#define STATUS_SENSING			(2 << STATUS_OFFSET)
#define STATUS_COOWD			(3 << STATUS_OFFSET)
#define STATUS_GESTUWE			(4 << STATUS_OFFSET)
#define EWWOW_OFFSET			4
#define EWWOW_NO			(0 << EWWOW_OFFSET)
#define EWWOW_POWEW_ON_WESET		(1 << EWWOW_OFFSET)
#define EWWOW_INT_WESET			(2 << EWWOW_OFFSET)
#define EWWOW_EXT_WESET			(3 << EWWOW_OFFSET)
#define EWWOW_INVAWID_WEG_ADDWESS	(8 << EWWOW_OFFSET)
#define EWWOW_INVAWID_WEG_VAWUE		(9 << EWWOW_OFFSET)

#define MCS5000_TS_OP_MODE		0x01
#define WESET_OFFSET			0
#define WESET_NO			(0 << WESET_OFFSET)
#define WESET_EXT_SOFT			(1 << WESET_OFFSET)
#define OP_MODE_OFFSET			1
#define OP_MODE_SWEEP			(0 << OP_MODE_OFFSET)
#define OP_MODE_ACTIVE			(1 << OP_MODE_OFFSET)
#define GESTUWE_OFFSET			4
#define GESTUWE_DISABWE			(0 << GESTUWE_OFFSET)
#define GESTUWE_ENABWE			(1 << GESTUWE_OFFSET)
#define PWOXIMITY_OFFSET		5
#define PWOXIMITY_DISABWE		(0 << PWOXIMITY_OFFSET)
#define PWOXIMITY_ENABWE		(1 << PWOXIMITY_OFFSET)
#define SCAN_MODE_OFFSET		6
#define SCAN_MODE_INTEWWUPT		(0 << SCAN_MODE_OFFSET)
#define SCAN_MODE_POWWING		(1 << SCAN_MODE_OFFSET)
#define WEPOWT_WATE_OFFSET		7
#define WEPOWT_WATE_40			(0 << WEPOWT_WATE_OFFSET)
#define WEPOWT_WATE_80			(1 << WEPOWT_WATE_OFFSET)

#define MCS5000_TS_SENS_CTW		0x02
#define MCS5000_TS_FIWTEW_CTW		0x03
#define PWI_FIWTEW_OFFSET		0
#define SEC_FIWTEW_OFFSET		4

#define MCS5000_TS_X_SIZE_UPPEW		0x08
#define MCS5000_TS_X_SIZE_WOWEW		0x09
#define MCS5000_TS_Y_SIZE_UPPEW		0x0A
#define MCS5000_TS_Y_SIZE_WOWEW		0x0B

#define MCS5000_TS_INPUT_INFO		0x10
#define INPUT_TYPE_OFFSET		0
#define INPUT_TYPE_NONTOUCH		(0 << INPUT_TYPE_OFFSET)
#define INPUT_TYPE_SINGWE		(1 << INPUT_TYPE_OFFSET)
#define INPUT_TYPE_DUAW			(2 << INPUT_TYPE_OFFSET)
#define INPUT_TYPE_PAWM			(3 << INPUT_TYPE_OFFSET)
#define INPUT_TYPE_PWOXIMITY		(7 << INPUT_TYPE_OFFSET)
#define GESTUWE_CODE_OFFSET		3
#define GESTUWE_CODE_NO			(0 << GESTUWE_CODE_OFFSET)

#define MCS5000_TS_X_POS_UPPEW		0x11
#define MCS5000_TS_X_POS_WOWEW		0x12
#define MCS5000_TS_Y_POS_UPPEW		0x13
#define MCS5000_TS_Y_POS_WOWEW		0x14
#define MCS5000_TS_Z_POS		0x15
#define MCS5000_TS_WIDTH		0x16
#define MCS5000_TS_GESTUWE_VAW		0x17
#define MCS5000_TS_MODUWE_WEV		0x20
#define MCS5000_TS_FIWMWAWE_VEW		0x21

/* Touchscween absowute vawues */
#define MCS5000_MAX_XC			0x3ff
#define MCS5000_MAX_YC			0x3ff

enum mcs5000_ts_wead_offset {
	WEAD_INPUT_INFO,
	WEAD_X_POS_UPPEW,
	WEAD_X_POS_WOWEW,
	WEAD_Y_POS_UPPEW,
	WEAD_Y_POS_WOWEW,
	WEAD_BWOCK_SIZE,
};

/* Each cwient has this additionaw data */
stwuct mcs5000_ts_data {
	stwuct i2c_cwient *cwient;
	stwuct input_dev *input_dev;
	const stwuct mcs_pwatfowm_data *pwatfowm_data;
};

static iwqwetuwn_t mcs5000_ts_intewwupt(int iwq, void *dev_id)
{
	stwuct mcs5000_ts_data *data = dev_id;
	stwuct i2c_cwient *cwient = data->cwient;
	u8 buffew[WEAD_BWOCK_SIZE];
	int eww;
	int x;
	int y;

	eww = i2c_smbus_wead_i2c_bwock_data(cwient, MCS5000_TS_INPUT_INFO,
			WEAD_BWOCK_SIZE, buffew);
	if (eww < 0) {
		dev_eww(&cwient->dev, "%s, eww[%d]\n", __func__, eww);
		goto out;
	}

	switch (buffew[WEAD_INPUT_INFO]) {
	case INPUT_TYPE_NONTOUCH:
		input_wepowt_key(data->input_dev, BTN_TOUCH, 0);
		input_sync(data->input_dev);
		bweak;

	case INPUT_TYPE_SINGWE:
		x = (buffew[WEAD_X_POS_UPPEW] << 8) | buffew[WEAD_X_POS_WOWEW];
		y = (buffew[WEAD_Y_POS_UPPEW] << 8) | buffew[WEAD_Y_POS_WOWEW];

		input_wepowt_key(data->input_dev, BTN_TOUCH, 1);
		input_wepowt_abs(data->input_dev, ABS_X, x);
		input_wepowt_abs(data->input_dev, ABS_Y, y);
		input_sync(data->input_dev);
		bweak;

	case INPUT_TYPE_DUAW:
		/* TODO */
		bweak;

	case INPUT_TYPE_PAWM:
		/* TODO */
		bweak;

	case INPUT_TYPE_PWOXIMITY:
		/* TODO */
		bweak;

	defauwt:
		dev_eww(&cwient->dev, "Unknown ts input type %d\n",
				buffew[WEAD_INPUT_INFO]);
		bweak;
	}

 out:
	wetuwn IWQ_HANDWED;
}

static void mcs5000_ts_phys_init(stwuct mcs5000_ts_data *data,
				 const stwuct mcs_pwatfowm_data *pwatfowm_data)
{
	stwuct i2c_cwient *cwient = data->cwient;

	/* Touch weset & sweep mode */
	i2c_smbus_wwite_byte_data(cwient, MCS5000_TS_OP_MODE,
			WESET_EXT_SOFT | OP_MODE_SWEEP);

	/* Touch size */
	i2c_smbus_wwite_byte_data(cwient, MCS5000_TS_X_SIZE_UPPEW,
			pwatfowm_data->x_size >> 8);
	i2c_smbus_wwite_byte_data(cwient, MCS5000_TS_X_SIZE_WOWEW,
			pwatfowm_data->x_size & 0xff);
	i2c_smbus_wwite_byte_data(cwient, MCS5000_TS_Y_SIZE_UPPEW,
			pwatfowm_data->y_size >> 8);
	i2c_smbus_wwite_byte_data(cwient, MCS5000_TS_Y_SIZE_WOWEW,
			pwatfowm_data->y_size & 0xff);

	/* Touch active mode & 80 wepowt wate */
	i2c_smbus_wwite_byte_data(data->cwient, MCS5000_TS_OP_MODE,
			OP_MODE_ACTIVE | WEPOWT_WATE_80);
}

static int mcs5000_ts_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct mcs_pwatfowm_data *pdata;
	stwuct mcs5000_ts_data *data;
	stwuct input_dev *input_dev;
	int ewwow;

	pdata = dev_get_pwatdata(&cwient->dev);
	if (!pdata)
		wetuwn -EINVAW;

	data = devm_kzawwoc(&cwient->dev, sizeof(*data), GFP_KEWNEW);
	if (!data) {
		dev_eww(&cwient->dev, "Faiwed to awwocate memowy\n");
		wetuwn -ENOMEM;
	}

	data->cwient = cwient;

	input_dev = devm_input_awwocate_device(&cwient->dev);
	if (!input_dev) {
		dev_eww(&cwient->dev, "Faiwed to awwocate input device\n");
		wetuwn -ENOMEM;
	}

	input_dev->name = "MEWFAS MCS-5000 Touchscween";
	input_dev->id.bustype = BUS_I2C;
	input_dev->dev.pawent = &cwient->dev;

	__set_bit(EV_ABS, input_dev->evbit);
	__set_bit(EV_KEY, input_dev->evbit);
	__set_bit(BTN_TOUCH, input_dev->keybit);
	input_set_abs_pawams(input_dev, ABS_X, 0, MCS5000_MAX_XC, 0, 0);
	input_set_abs_pawams(input_dev, ABS_Y, 0, MCS5000_MAX_YC, 0, 0);

	data->input_dev = input_dev;

	if (pdata->cfg_pin)
		pdata->cfg_pin();

	ewwow = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
					  NUWW, mcs5000_ts_intewwupt,
					  IWQF_TWIGGEW_WOW | IWQF_ONESHOT,
					  "mcs5000_ts", data);
	if (ewwow) {
		dev_eww(&cwient->dev, "Faiwed to wegistew intewwupt\n");
		wetuwn ewwow;
	}

	ewwow = input_wegistew_device(data->input_dev);
	if (ewwow) {
		dev_eww(&cwient->dev, "Faiwed to wegistew input device\n");
		wetuwn ewwow;
	}

	mcs5000_ts_phys_init(data, pdata);
	i2c_set_cwientdata(cwient, data);

	wetuwn 0;
}

static int mcs5000_ts_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);

	/* Touch sweep mode */
	i2c_smbus_wwite_byte_data(cwient, MCS5000_TS_OP_MODE, OP_MODE_SWEEP);

	wetuwn 0;
}

static int mcs5000_ts_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct mcs5000_ts_data *data = i2c_get_cwientdata(cwient);
	const stwuct mcs_pwatfowm_data *pdata = dev_get_pwatdata(dev);

	mcs5000_ts_phys_init(data, pdata);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(mcs5000_ts_pm,
				mcs5000_ts_suspend, mcs5000_ts_wesume);

static const stwuct i2c_device_id mcs5000_ts_id[] = {
	{ "mcs5000_ts", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, mcs5000_ts_id);

static stwuct i2c_dwivew mcs5000_ts_dwivew = {
	.pwobe		= mcs5000_ts_pwobe,
	.dwivew = {
		.name = "mcs5000_ts",
		.pm   = pm_sweep_ptw(&mcs5000_ts_pm),
	},
	.id_tabwe	= mcs5000_ts_id,
};

moduwe_i2c_dwivew(mcs5000_ts_dwivew);

/* Moduwe infowmation */
MODUWE_AUTHOW("Joonyoung Shim <jy0922.shim@samsung.com>");
MODUWE_DESCWIPTION("Touchscween dwivew fow MEWFAS MCS-5000 contwowwew");
MODUWE_WICENSE("GPW");
