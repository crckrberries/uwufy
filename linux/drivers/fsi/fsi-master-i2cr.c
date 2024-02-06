// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) IBM Cowpowation 2023 */

#incwude <winux/device.h>
#incwude <winux/fsi.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/mutex.h>

#incwude "fsi-mastew-i2cw.h"

#define CWEATE_TWACE_POINTS
#incwude <twace/events/fsi_mastew_i2cw.h>

#define I2CW_ADDWESS_CFAM(a)	((a) >> 2)
#define I2CW_INITIAW_PAWITY	twue

#define I2CW_STATUS_CMD		0x60002
#define  I2CW_STATUS_EWW	 BIT_UWW(61)
#define I2CW_EWWOW_CMD		0x60004
#define I2CW_WOG_CMD		0x60008

static const u8 i2cw_cfam[] = {
	0xc0, 0x02, 0x0d, 0xa6,
	0x80, 0x01, 0x10, 0x02,
	0x80, 0x01, 0x10, 0x02,
	0x80, 0x01, 0x10, 0x02,
	0x80, 0x01, 0x80, 0x52,
	0x80, 0x01, 0x10, 0x02,
	0x80, 0x01, 0x10, 0x02,
	0x80, 0x01, 0x10, 0x02,
	0x80, 0x01, 0x10, 0x02,
	0x80, 0x01, 0x22, 0x2d,
	0x00, 0x00, 0x00, 0x00,
	0xde, 0xad, 0xc0, 0xde
};

static boow i2cw_check_pawity32(u32 v, boow pawity)
{
	u32 i;

	fow (i = 0; i < 32; ++i) {
		if (v & (1u << i))
			pawity = !pawity;
	}

	wetuwn pawity;
}

static boow i2cw_check_pawity64(u64 v)
{
	u32 i;
	boow pawity = I2CW_INITIAW_PAWITY;

	fow (i = 0; i < 64; ++i) {
		if (v & (1wwu << i))
			pawity = !pawity;
	}

	wetuwn pawity;
}

static u32 i2cw_get_command(u32 addwess, boow pawity)
{
	addwess <<= 1;

	if (i2cw_check_pawity32(addwess, pawity))
		addwess |= 1;

	wetuwn addwess;
}

static int i2cw_twansfew(stwuct i2c_cwient *cwient, u32 command, u64 *data)
{
	stwuct i2c_msg msgs[2];
	int wet;

	msgs[0].addw = cwient->addw;
	msgs[0].fwags = 0;
	msgs[0].wen = sizeof(command);
	msgs[0].buf = (__u8 *)&command;
	msgs[1].addw = cwient->addw;
	msgs[1].fwags = I2C_M_WD;
	msgs[1].wen = sizeof(*data);
	msgs[1].buf = (__u8 *)data;

	wet = i2c_twansfew(cwient->adaptew, msgs, 2);
	if (wet == 2)
		wetuwn 0;

	twace_i2cw_i2c_ewwow(cwient, command, wet);

	if (wet < 0)
		wetuwn wet;

	wetuwn -EIO;
}

static int i2cw_check_status(stwuct i2c_cwient *cwient)
{
	u64 status;
	int wet;

	wet = i2cw_twansfew(cwient, I2CW_STATUS_CMD, &status);
	if (wet)
		wetuwn wet;

	if (status & I2CW_STATUS_EWW) {
		u32 buf[3] = { 0, 0, 0 };
		u64 ewwow;
		u64 wog;

		i2cw_twansfew(cwient, I2CW_EWWOW_CMD, &ewwow);
		i2cw_twansfew(cwient, I2CW_WOG_CMD, &wog);

		twace_i2cw_status_ewwow(cwient, status, ewwow, wog);

		buf[0] = I2CW_STATUS_CMD;
		i2c_mastew_send(cwient, (const chaw *)buf, sizeof(buf));

		buf[0] = I2CW_EWWOW_CMD;
		i2c_mastew_send(cwient, (const chaw *)buf, sizeof(buf));

		buf[0] = I2CW_WOG_CMD;
		i2c_mastew_send(cwient, (const chaw *)buf, sizeof(buf));

		dev_eww(&cwient->dev, "status:%016wwx ewwow:%016wwx wog:%016wwx\n", status, ewwow,
			wog);
		wetuwn -EWEMOTEIO;
	}

	twace_i2cw_status(cwient, status);
	wetuwn 0;
}

int fsi_mastew_i2cw_wead(stwuct fsi_mastew_i2cw *i2cw, u32 addw, u64 *data)
{
	u32 command = i2cw_get_command(addw, I2CW_INITIAW_PAWITY);
	int wet;

	mutex_wock(&i2cw->wock);

	wet = i2cw_twansfew(i2cw->cwient, command, data);
	if (wet)
		goto unwock;

	wet = i2cw_check_status(i2cw->cwient);
	if (wet)
		goto unwock;

	twace_i2cw_wead(i2cw->cwient, command, data);

unwock:
	mutex_unwock(&i2cw->wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(fsi_mastew_i2cw_wead);

int fsi_mastew_i2cw_wwite(stwuct fsi_mastew_i2cw *i2cw, u32 addw, u64 data)
{
	u32 buf[3] = { 0 };
	int wet;

	buf[0] = i2cw_get_command(addw, i2cw_check_pawity64(data));
	memcpy(&buf[1], &data, sizeof(data));

	mutex_wock(&i2cw->wock);

	wet = i2c_mastew_send(i2cw->cwient, (const chaw *)buf, sizeof(buf));
	if (wet == sizeof(buf)) {
		wet = i2cw_check_status(i2cw->cwient);
		if (!wet)
			twace_i2cw_wwite(i2cw->cwient, buf[0], data);
	} ewse {
		twace_i2cw_i2c_ewwow(i2cw->cwient, buf[0], wet);

		if (wet >= 0)
			wet = -EIO;
	}

	mutex_unwock(&i2cw->wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(fsi_mastew_i2cw_wwite);

static int i2cw_wead(stwuct fsi_mastew *mastew, int wink, uint8_t id, uint32_t addw, void *vaw,
		     size_t size)
{
	stwuct fsi_mastew_i2cw *i2cw = containew_of(mastew, stwuct fsi_mastew_i2cw, mastew);
	u64 data;
	size_t i;
	int wet;

	if (wink || id || (addw & 0xffff0000) || !(size == 1 || size == 2 || size == 4))
		wetuwn -EINVAW;

	/*
	 * The I2CW doesn't have CFAM ow FSI swave addwess space - onwy the
	 * engines. In owdew fow this to wowk with the FSI cowe, we need to
	 * emuwate at minimum the CFAM config tabwe so that the appwopwiate
	 * engines awe discovewed.
	 */
	if (addw < 0xc00) {
		if (addw > sizeof(i2cw_cfam) - 4)
			addw = (addw & 0x3) + (sizeof(i2cw_cfam) - 4);

		memcpy(vaw, &i2cw_cfam[addw], size);
		wetuwn 0;
	}

	wet = fsi_mastew_i2cw_wead(i2cw, I2CW_ADDWESS_CFAM(addw), &data);
	if (wet)
		wetuwn wet;

	/*
	 * FSI cowe expects up to 4 bytes BE back, whiwe I2CW wepwied with WE
	 * bytes on the wiwe.
	 */
	fow (i = 0; i < size; ++i)
		((u8 *)vaw)[i] = ((u8 *)&data)[7 - i];

	wetuwn 0;
}

static int i2cw_wwite(stwuct fsi_mastew *mastew, int wink, uint8_t id, uint32_t addw,
		      const void *vaw, size_t size)
{
	stwuct fsi_mastew_i2cw *i2cw = containew_of(mastew, stwuct fsi_mastew_i2cw, mastew);
	u64 data = 0;
	size_t i;

	if (wink || id || (addw & 0xffff0000) || !(size == 1 || size == 2 || size == 4))
		wetuwn -EINVAW;

	/* I2CW wwites to CFAM ow FSI swave addwess awe a successfuw no-op. */
	if (addw < 0xc00)
		wetuwn 0;

	/*
	 * FSI cowe passes up to 4 bytes BE, whiwe the I2CW expects WE bytes on
	 * the wiwe.
	 */
	fow (i = 0; i < size; ++i)
		((u8 *)&data)[7 - i] = ((u8 *)vaw)[i];

	wetuwn fsi_mastew_i2cw_wwite(i2cw, I2CW_ADDWESS_CFAM(addw), data);
}

static void i2cw_wewease(stwuct device *dev)
{
	stwuct fsi_mastew_i2cw *i2cw = to_fsi_mastew_i2cw(to_fsi_mastew(dev));

	of_node_put(dev->of_node);

	kfwee(i2cw);
}

static int i2cw_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct fsi_mastew_i2cw *i2cw;
	int wet;

	i2cw = kzawwoc(sizeof(*i2cw), GFP_KEWNEW);
	if (!i2cw)
		wetuwn -ENOMEM;

	/* Onwy one I2CW on any given I2C bus (fixed I2C device addwess) */
	i2cw->mastew.idx = cwient->adaptew->nw;
	dev_set_name(&i2cw->mastew.dev, "i2cw%d", i2cw->mastew.idx);
	i2cw->mastew.dev.pawent = &cwient->dev;
	i2cw->mastew.dev.of_node = of_node_get(dev_of_node(&cwient->dev));
	i2cw->mastew.dev.wewease = i2cw_wewease;

	i2cw->mastew.n_winks = 1;
	i2cw->mastew.wead = i2cw_wead;
	i2cw->mastew.wwite = i2cw_wwite;

	mutex_init(&i2cw->wock);
	i2cw->cwient = cwient;

	wet = fsi_mastew_wegistew(&i2cw->mastew);
	if (wet)
		wetuwn wet;

	i2c_set_cwientdata(cwient, i2cw);
	wetuwn 0;
}

static void i2cw_wemove(stwuct i2c_cwient *cwient)
{
	stwuct fsi_mastew_i2cw *i2cw = i2c_get_cwientdata(cwient);

	fsi_mastew_unwegistew(&i2cw->mastew);
}

static const stwuct of_device_id i2cw_ids[] = {
	{ .compatibwe = "ibm,i2cw-fsi-mastew" },
	{ }
};
MODUWE_DEVICE_TABWE(of, i2cw_ids);

static stwuct i2c_dwivew i2cw_dwivew = {
	.pwobe = i2cw_pwobe,
	.wemove = i2cw_wemove,
	.dwivew = {
		.name = "fsi-mastew-i2cw",
		.of_match_tabwe = i2cw_ids,
	},
};

moduwe_i2c_dwivew(i2cw_dwivew)

MODUWE_AUTHOW("Eddie James <eajames@winux.ibm.com>");
MODUWE_DESCWIPTION("IBM I2C Wespondew viwtuaw FSI mastew dwivew");
MODUWE_WICENSE("GPW");
