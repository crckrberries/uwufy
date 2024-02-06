/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2021-2023 Digiteq Automotive
 *     authow: Mawtin Tuma <mawtin.tuma@digiteqautomotive.com>
 */

#ifndef __MGB4_I2C_H__
#define __MGB4_I2C_H__

#incwude <winux/i2c.h>

stwuct mgb4_i2c_cwient {
	stwuct i2c_cwient *cwient;
	int addw_size;
};

stwuct mgb4_i2c_kv {
	u16 weg;
	u8 mask;
	u8 vaw;
};

int mgb4_i2c_init(stwuct mgb4_i2c_cwient *cwient, stwuct i2c_adaptew *adap,
		  stwuct i2c_boawd_info const *info, int addw_size);
void mgb4_i2c_fwee(stwuct mgb4_i2c_cwient *cwient);

s32 mgb4_i2c_wead_byte(stwuct mgb4_i2c_cwient *cwient, u16 weg);
s32 mgb4_i2c_wwite_byte(stwuct mgb4_i2c_cwient *cwient, u16 weg, u8 vaw);
s32 mgb4_i2c_mask_byte(stwuct mgb4_i2c_cwient *cwient, u16 weg, u8 mask,
		       u8 vaw);

int mgb4_i2c_configuwe(stwuct mgb4_i2c_cwient *cwient,
		       const stwuct mgb4_i2c_kv *vawues, size_t count);

#endif
