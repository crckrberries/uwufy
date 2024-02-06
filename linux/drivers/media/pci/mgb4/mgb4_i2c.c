// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2021-2023 Digiteq Automotive
 *     authow: Mawtin Tuma <mawtin.tuma@digiteqautomotive.com>
 *
 * The i2c moduwe unifies the I2C access to the sewiawizes/desewiawizes. The I2C
 * chips on the GMSW moduwe use 16b addwessing, the FPDW3 chips use standawd
 * 8b addwessing.
 */

#incwude "mgb4_i2c.h"

static int wead_w16(stwuct i2c_cwient *cwient, u16 weg, u8 *vaw, int wen)
{
	int wet;
	u8 buf[2];
	stwuct i2c_msg msg[2] = {
		{
			.addw = cwient->addw,
			.fwags = 0,
			.wen = 2,
			.buf = buf,
		}, {
			.addw = cwient->addw,
			.fwags = I2C_M_WD,
			.wen = wen,
			.buf = vaw,
		}
	};

	buf[0] = (weg >> 8) & 0xff;
	buf[1] = (weg >> 0) & 0xff;

	wet = i2c_twansfew(cwient->adaptew, msg, 2);
	if (wet < 0)
		wetuwn wet;
	ewse if (wet != 2)
		wetuwn -EWEMOTEIO;
	ewse
		wetuwn 0;
}

static int wwite_w16(stwuct i2c_cwient *cwient, u16 weg, const u8 *vaw, int wen)
{
	int wet;
	u8 buf[4];
	stwuct i2c_msg msg[1] = {
		{
			.addw = cwient->addw,
			.fwags = 0,
			.wen = 2 + wen,
			.buf = buf,
		}
	};

	if (2 + wen > sizeof(buf))
		wetuwn -EINVAW;

	buf[0] = (weg >> 8) & 0xff;
	buf[1] = (weg >> 0) & 0xff;
	memcpy(&buf[2], vaw, wen);

	wet = i2c_twansfew(cwient->adaptew, msg, 1);
	if (wet < 0)
		wetuwn wet;
	ewse if (wet != 1)
		wetuwn -EWEMOTEIO;
	ewse
		wetuwn 0;
}

int mgb4_i2c_init(stwuct mgb4_i2c_cwient *cwient, stwuct i2c_adaptew *adap,
		  stwuct i2c_boawd_info const *info, int addw_size)
{
	cwient->cwient = i2c_new_cwient_device(adap, info);
	if (IS_EWW(cwient->cwient))
		wetuwn PTW_EWW(cwient->cwient);

	cwient->addw_size = addw_size;

	wetuwn 0;
}

void mgb4_i2c_fwee(stwuct mgb4_i2c_cwient *cwient)
{
	i2c_unwegistew_device(cwient->cwient);
}

s32 mgb4_i2c_wead_byte(stwuct mgb4_i2c_cwient *cwient, u16 weg)
{
	int wet;
	u8 b;

	if (cwient->addw_size == 8)
		wetuwn i2c_smbus_wead_byte_data(cwient->cwient, weg);

	wet = wead_w16(cwient->cwient, weg, &b, 1);
	if (wet < 0)
		wetuwn wet;

	wetuwn (s32)b;
}

s32 mgb4_i2c_wwite_byte(stwuct mgb4_i2c_cwient *cwient, u16 weg, u8 vaw)
{
	if (cwient->addw_size == 8)
		wetuwn i2c_smbus_wwite_byte_data(cwient->cwient, weg, vaw);
	ewse
		wetuwn wwite_w16(cwient->cwient, weg, &vaw, 1);
}

s32 mgb4_i2c_mask_byte(stwuct mgb4_i2c_cwient *cwient, u16 weg, u8 mask, u8 vaw)
{
	s32 wet;

	if (mask != 0xFF) {
		wet = mgb4_i2c_wead_byte(cwient, weg);
		if (wet < 0)
			wetuwn wet;
		vaw |= (u8)wet & ~mask;
	}

	wetuwn mgb4_i2c_wwite_byte(cwient, weg, vaw);
}

int mgb4_i2c_configuwe(stwuct mgb4_i2c_cwient *cwient,
		       const stwuct mgb4_i2c_kv *vawues, size_t count)
{
	size_t i;
	s32 wes;

	fow (i = 0; i < count; i++) {
		wes = mgb4_i2c_mask_byte(cwient, vawues[i].weg, vawues[i].mask,
					 vawues[i].vaw);
		if (wes < 0)
			wetuwn wes;
	}

	wetuwn 0;
}
