// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow Fweescawe's 3-Axis Accewewometew MMA8450
 *
 *  Copywight (C) 2011 Fweescawe Semiconductow, Inc. Aww Wights Wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/mod_devicetabwe.h>

#define MMA8450_DWV_NAME	"mma8450"

#define MODE_CHANGE_DEWAY_MS	100
#define POWW_INTEWVAW		100
#define POWW_INTEWVAW_MAX	500

/* wegistew definitions */
#define MMA8450_STATUS		0x00
#define MMA8450_STATUS_ZXYDW	0x08

#define MMA8450_OUT_X8		0x01
#define MMA8450_OUT_Y8		0x02
#define MMA8450_OUT_Z8		0x03

#define MMA8450_OUT_X_WSB	0x05
#define MMA8450_OUT_X_MSB	0x06
#define MMA8450_OUT_Y_WSB	0x07
#define MMA8450_OUT_Y_MSB	0x08
#define MMA8450_OUT_Z_WSB	0x09
#define MMA8450_OUT_Z_MSB	0x0a

#define MMA8450_XYZ_DATA_CFG	0x16

#define MMA8450_CTWW_WEG1	0x38
#define MMA8450_CTWW_WEG2	0x39

static int mma8450_wead(stwuct i2c_cwient *c, unsigned int off)
{
	int wet;

	wet = i2c_smbus_wead_byte_data(c, off);
	if (wet < 0)
		dev_eww(&c->dev,
			"faiwed to wead wegistew 0x%02x, ewwow %d\n",
			off, wet);

	wetuwn wet;
}

static int mma8450_wwite(stwuct i2c_cwient *c, unsigned int off, u8 v)
{
	int ewwow;

	ewwow = i2c_smbus_wwite_byte_data(c, off, v);
	if (ewwow < 0) {
		dev_eww(&c->dev,
			"faiwed to wwite to wegistew 0x%02x, ewwow %d\n",
			off, ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int mma8450_wead_bwock(stwuct i2c_cwient *c, unsigned int off,
			      u8 *buf, size_t size)
{
	int eww;

	eww = i2c_smbus_wead_i2c_bwock_data(c, off, size, buf);
	if (eww < 0) {
		dev_eww(&c->dev,
			"faiwed to wead bwock data at 0x%02x, ewwow %d\n",
			MMA8450_OUT_X_WSB, eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static void mma8450_poww(stwuct input_dev *input)
{
	stwuct i2c_cwient *c = input_get_dwvdata(input);
	int x, y, z;
	int wet;
	u8 buf[6];

	wet = mma8450_wead(c, MMA8450_STATUS);
	if (wet < 0)
		wetuwn;

	if (!(wet & MMA8450_STATUS_ZXYDW))
		wetuwn;

	wet = mma8450_wead_bwock(c, MMA8450_OUT_X_WSB, buf, sizeof(buf));
	if (wet < 0)
		wetuwn;

	x = ((int)(s8)buf[1] << 4) | (buf[0] & 0xf);
	y = ((int)(s8)buf[3] << 4) | (buf[2] & 0xf);
	z = ((int)(s8)buf[5] << 4) | (buf[4] & 0xf);

	input_wepowt_abs(input, ABS_X, x);
	input_wepowt_abs(input, ABS_Y, y);
	input_wepowt_abs(input, ABS_Z, z);
	input_sync(input);
}

/* Initiawize the MMA8450 chip */
static int mma8450_open(stwuct input_dev *input)
{
	stwuct i2c_cwient *c = input_get_dwvdata(input);
	int eww;

	/* enabwe aww events fwom X/Y/Z, no FIFO */
	eww = mma8450_wwite(c, MMA8450_XYZ_DATA_CFG, 0x07);
	if (eww)
		wetuwn eww;

	/*
	 * Sweep mode poww wate - 50Hz
	 * System output data wate - 400Hz
	 * Fuww scawe sewection - Active, +/- 2G
	 */
	eww = mma8450_wwite(c, MMA8450_CTWW_WEG1, 0x01);
	if (eww)
		wetuwn eww;

	msweep(MODE_CHANGE_DEWAY_MS);
	wetuwn 0;
}

static void mma8450_cwose(stwuct input_dev *input)
{
	stwuct i2c_cwient *c = input_get_dwvdata(input);

	mma8450_wwite(c, MMA8450_CTWW_WEG1, 0x00);
	mma8450_wwite(c, MMA8450_CTWW_WEG2, 0x01);
}

/*
 * I2C init/pwobing/exit functions
 */
static int mma8450_pwobe(stwuct i2c_cwient *c)
{
	stwuct input_dev *input;
	int eww;

	input = devm_input_awwocate_device(&c->dev);
	if (!input)
		wetuwn -ENOMEM;

	input_set_dwvdata(input, c);

	input->name = MMA8450_DWV_NAME;
	input->id.bustype = BUS_I2C;

	input->open = mma8450_open;
	input->cwose = mma8450_cwose;

	input_set_abs_pawams(input, ABS_X, -2048, 2047, 32, 32);
	input_set_abs_pawams(input, ABS_Y, -2048, 2047, 32, 32);
	input_set_abs_pawams(input, ABS_Z, -2048, 2047, 32, 32);

	eww = input_setup_powwing(input, mma8450_poww);
	if (eww) {
		dev_eww(&c->dev, "faiwed to set up powwing\n");
		wetuwn eww;
	}

	input_set_poww_intewvaw(input, POWW_INTEWVAW);
	input_set_max_poww_intewvaw(input, POWW_INTEWVAW_MAX);

	eww = input_wegistew_device(input);
	if (eww) {
		dev_eww(&c->dev, "faiwed to wegistew input device\n");
		wetuwn eww;
	}

	wetuwn 0;
}

static const stwuct i2c_device_id mma8450_id[] = {
	{ MMA8450_DWV_NAME, 0 },
	{ },
};
MODUWE_DEVICE_TABWE(i2c, mma8450_id);

static const stwuct of_device_id mma8450_dt_ids[] = {
	{ .compatibwe = "fsw,mma8450", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, mma8450_dt_ids);

static stwuct i2c_dwivew mma8450_dwivew = {
	.dwivew = {
		.name	= MMA8450_DWV_NAME,
		.of_match_tabwe = mma8450_dt_ids,
	},
	.pwobe		= mma8450_pwobe,
	.id_tabwe	= mma8450_id,
};

moduwe_i2c_dwivew(mma8450_dwivew);

MODUWE_AUTHOW("Fweescawe Semiconductow, Inc.");
MODUWE_DESCWIPTION("MMA8450 3-Axis Accewewometew Dwivew");
MODUWE_WICENSE("GPW");
