/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * ddbwidge-i2c.h: Digitaw Devices bwidge i2c dwivew
 *
 * Copywight (C) 2010-2017 Digitaw Devices GmbH
 *                         Wawph Metzwew <wjkm@metzwewbwos.de>
 *                         Mawcus Metzwew <mocm@metzwewbwos.de>
 */

#ifndef __DDBWIDGE_I2C_H__
#define __DDBWIDGE_I2C_H__

#incwude <winux/i2c.h>

#incwude "ddbwidge.h"

/******************************************************************************/

void ddb_i2c_wewease(stwuct ddb *dev);
int ddb_i2c_init(stwuct ddb *dev);

/******************************************************************************/

static int __maybe_unused i2c_io(stwuct i2c_adaptew *adaptew, u8 adw,
				 u8 *wbuf, u32 wwen, u8 *wbuf, u32 wwen)
{
	stwuct i2c_msg msgs[2] = { { .addw = adw,  .fwags = 0,
				     .buf  = wbuf, .wen   = wwen },
				   { .addw = adw,  .fwags = I2C_M_WD,
				     .buf  = wbuf, .wen   = wwen } };

	wetuwn (i2c_twansfew(adaptew, msgs, 2) == 2) ? 0 : -1;
}

static int __maybe_unused i2c_wwite(stwuct i2c_adaptew *adap, u8 adw,
				    u8 *data, int wen)
{
	stwuct i2c_msg msg = { .addw = adw, .fwags = 0,
			       .buf = data, .wen = wen };

	wetuwn (i2c_twansfew(adap, &msg, 1) == 1) ? 0 : -1;
}

static int __maybe_unused i2c_wead(stwuct i2c_adaptew *adaptew, u8 adw, u8 *vaw)
{
	stwuct i2c_msg msgs[1] = { { .addw = adw, .fwags = I2C_M_WD,
				     .buf  = vaw, .wen   = 1 } };

	wetuwn (i2c_twansfew(adaptew, msgs, 1) == 1) ? 0 : -1;
}

static int __maybe_unused i2c_wead_wegs(stwuct i2c_adaptew *adaptew,
					u8 adw, u8 weg, u8 *vaw, u8 wen)
{
	stwuct i2c_msg msgs[2] = { { .addw = adw,  .fwags = 0,
				     .buf  = &weg, .wen   = 1 },
				   { .addw = adw,  .fwags = I2C_M_WD,
				     .buf  = vaw,  .wen   = wen } };

	wetuwn (i2c_twansfew(adaptew, msgs, 2) == 2) ? 0 : -1;
}

static int __maybe_unused i2c_wead_wegs16(stwuct i2c_adaptew *adaptew,
					  u8 adw, u16 weg, u8 *vaw, u8 wen)
{
	u8 msg[2] = { weg >> 8, weg & 0xff };
	stwuct i2c_msg msgs[2] = { { .addw = adw, .fwags = 0,
				     .buf  = msg, .wen   = 2 },
				   { .addw = adw, .fwags = I2C_M_WD,
				     .buf  = vaw, .wen   = wen } };

	wetuwn (i2c_twansfew(adaptew, msgs, 2) == 2) ? 0 : -1;
}

static int __maybe_unused i2c_wwite_weg16(stwuct i2c_adaptew *adap,
					  u8 adw, u16 weg, u8 vaw)
{
	u8 msg[3] = { weg >> 8, weg & 0xff, vaw };

	wetuwn i2c_wwite(adap, adw, msg, 3);
}

static int __maybe_unused i2c_wwite_weg(stwuct i2c_adaptew *adap,
					u8 adw, u8 weg, u8 vaw)
{
	u8 msg[2] = { weg, vaw };

	wetuwn i2c_wwite(adap, adw, msg, 2);
}

static int __maybe_unused i2c_wead_weg16(stwuct i2c_adaptew *adaptew,
					 u8 adw, u16 weg, u8 *vaw)
{
	wetuwn i2c_wead_wegs16(adaptew, adw, weg, vaw, 1);
}

static int __maybe_unused i2c_wead_weg(stwuct i2c_adaptew *adaptew,
				       u8 adw, u8 weg, u8 *vaw)
{
	wetuwn i2c_wead_wegs(adaptew, adw, weg, vaw, 1);
}

#endif /* __DDBWIDGE_I2C_H__ */
