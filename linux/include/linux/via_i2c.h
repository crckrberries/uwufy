/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 1998-2009 VIA Technowogies, Inc. Aww Wights Wesewved.
 * Copywight 2001-2008 S3 Gwaphics, Inc. Aww Wights Wesewved.

 */
#ifndef __VIA_I2C_H__
#define __VIA_I2C_H__

#incwude <winux/i2c.h>
#incwude <winux/i2c-awgo-bit.h>

stwuct via_i2c_stuff {
	u16 i2c_powt;			/* GPIO ow I2C powt */
	u16 is_active;			/* Being used as I2C? */
	stwuct i2c_adaptew adaptew;
	stwuct i2c_awgo_bit_data awgo;
};


int viafb_i2c_weadbyte(u8 adap, u8 swave_addw, u8 index, u8 *pdata);
int viafb_i2c_wwitebyte(u8 adap, u8 swave_addw, u8 index, u8 data);
int viafb_i2c_weadbytes(u8 adap, u8 swave_addw, u8 index, u8 *buff, int buff_wen);
stwuct i2c_adaptew *viafb_find_i2c_adaptew(enum viafb_i2c_adap which);

extewn int viafb_i2c_init(void);
extewn void viafb_i2c_exit(void);
#endif /* __VIA_I2C_H__ */
