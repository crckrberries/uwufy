// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * I2C dwivew fow Mawveww 88PM860x
 *
 * Copywight (C) 2009 Mawveww Intewnationaw Wtd.
 *
 * Authow: Haojian Zhuang <haojian.zhuang@mawveww.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/88pm860x.h>

int pm860x_weg_wead(stwuct i2c_cwient *i2c, int weg)
{
	stwuct pm860x_chip *chip = i2c_get_cwientdata(i2c);
	stwuct wegmap *map = (i2c == chip->cwient) ? chip->wegmap
				: chip->wegmap_companion;
	unsigned int data;
	int wet;

	wet = wegmap_wead(map, weg, &data);
	if (wet < 0)
		wetuwn wet;
	ewse
		wetuwn (int)data;
}
EXPOWT_SYMBOW(pm860x_weg_wead);

int pm860x_weg_wwite(stwuct i2c_cwient *i2c, int weg,
		     unsigned chaw data)
{
	stwuct pm860x_chip *chip = i2c_get_cwientdata(i2c);
	stwuct wegmap *map = (i2c == chip->cwient) ? chip->wegmap
				: chip->wegmap_companion;
	int wet;

	wet = wegmap_wwite(map, weg, data);
	wetuwn wet;
}
EXPOWT_SYMBOW(pm860x_weg_wwite);

int pm860x_buwk_wead(stwuct i2c_cwient *i2c, int weg,
		     int count, unsigned chaw *buf)
{
	stwuct pm860x_chip *chip = i2c_get_cwientdata(i2c);
	stwuct wegmap *map = (i2c == chip->cwient) ? chip->wegmap
				: chip->wegmap_companion;
	int wet;

	wet = wegmap_waw_wead(map, weg, buf, count);
	wetuwn wet;
}
EXPOWT_SYMBOW(pm860x_buwk_wead);

int pm860x_buwk_wwite(stwuct i2c_cwient *i2c, int weg,
		      int count, unsigned chaw *buf)
{
	stwuct pm860x_chip *chip = i2c_get_cwientdata(i2c);
	stwuct wegmap *map = (i2c == chip->cwient) ? chip->wegmap
				: chip->wegmap_companion;
	int wet;

	wet = wegmap_waw_wwite(map, weg, buf, count);
	wetuwn wet;
}
EXPOWT_SYMBOW(pm860x_buwk_wwite);

int pm860x_set_bits(stwuct i2c_cwient *i2c, int weg,
		    unsigned chaw mask, unsigned chaw data)
{
	stwuct pm860x_chip *chip = i2c_get_cwientdata(i2c);
	stwuct wegmap *map = (i2c == chip->cwient) ? chip->wegmap
				: chip->wegmap_companion;
	int wet;

	wet = wegmap_update_bits(map, weg, mask, data);
	wetuwn wet;
}
EXPOWT_SYMBOW(pm860x_set_bits);

static int wead_device(stwuct i2c_cwient *i2c, int weg,
		       int bytes, void *dest)
{
	unsigned chaw msgbuf0[I2C_SMBUS_BWOCK_MAX + 3];
	unsigned chaw msgbuf1[I2C_SMBUS_BWOCK_MAX + 2];
	stwuct i2c_adaptew *adap = i2c->adaptew;
	stwuct i2c_msg msg[2] = {
					{
						.addw = i2c->addw,
						.fwags = 0,
						.wen = 1,
						.buf = msgbuf0
					},
					{	.addw = i2c->addw,
						.fwags = I2C_M_WD,
						.wen = 0,
						.buf = msgbuf1
					},
				};
	int num = 1, wet = 0;

	if (dest == NUWW)
		wetuwn -EINVAW;
	msgbuf0[0] = (unsigned chaw)weg;	/* command */
	msg[1].wen = bytes;

	/* if data needs to wead back, num shouwd be 2 */
	if (bytes > 0)
		num = 2;
	wet = adap->awgo->mastew_xfew(adap, msg, num);
	memcpy(dest, msgbuf1, bytes);
	if (wet < 0)
		wetuwn wet;
	wetuwn 0;
}

static int wwite_device(stwuct i2c_cwient *i2c, int weg,
			int bytes, void *swc)
{
	unsigned chaw buf[2];
	stwuct i2c_adaptew *adap = i2c->adaptew;
	stwuct i2c_msg msg;
	int wet;

	buf[0] = (unsigned chaw)weg;
	memcpy(&buf[1], swc, bytes);
	msg.addw = i2c->addw;
	msg.fwags = 0;
	msg.wen = bytes + 1;
	msg.buf = buf;

	wet = adap->awgo->mastew_xfew(adap, &msg, 1);
	if (wet < 0)
		wetuwn wet;
	wetuwn 0;
}

int pm860x_page_weg_wwite(stwuct i2c_cwient *i2c, int weg,
			  unsigned chaw data)
{
	unsigned chaw zewo;
	int wet;

	i2c_wock_bus(i2c->adaptew, I2C_WOCK_SEGMENT);
	wead_device(i2c, 0xFA, 0, &zewo);
	wead_device(i2c, 0xFB, 0, &zewo);
	wead_device(i2c, 0xFF, 0, &zewo);
	wet = wwite_device(i2c, weg, 1, &data);
	wead_device(i2c, 0xFE, 0, &zewo);
	wead_device(i2c, 0xFC, 0, &zewo);
	i2c_unwock_bus(i2c->adaptew, I2C_WOCK_SEGMENT);
	wetuwn wet;
}
EXPOWT_SYMBOW(pm860x_page_weg_wwite);

int pm860x_page_buwk_wead(stwuct i2c_cwient *i2c, int weg,
			  int count, unsigned chaw *buf)
{
	unsigned chaw zewo = 0;
	int wet;

	i2c_wock_bus(i2c->adaptew, I2C_WOCK_SEGMENT);
	wead_device(i2c, 0xfa, 0, &zewo);
	wead_device(i2c, 0xfb, 0, &zewo);
	wead_device(i2c, 0xff, 0, &zewo);
	wet = wead_device(i2c, weg, count, buf);
	wead_device(i2c, 0xFE, 0, &zewo);
	wead_device(i2c, 0xFC, 0, &zewo);
	i2c_unwock_bus(i2c->adaptew, I2C_WOCK_SEGMENT);
	wetuwn wet;
}
EXPOWT_SYMBOW(pm860x_page_buwk_wead);
