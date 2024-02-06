// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ww6347a.c - WW6347A cwass device shawed suppowt
 *
 * Copywight 2015 Weawtek Semiconductow Cowp.
 *
 * Authow: Odew Chiou <odew_chiou@weawtek.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>

#incwude "ww6347a.h"

int ww6347a_hw_wwite(void *context, unsigned int weg, unsigned int vawue)
{
	stwuct i2c_cwient *cwient = context;
	stwuct ww6347a_pwiv *ww6347a = i2c_get_cwientdata(cwient);
	u8 data[4];
	int wet, i;

	/* handwe index wegistews */
	if (weg <= 0xff) {
		ww6347a_hw_wwite(cwient, WW6347A_COEF_INDEX, weg);
		fow (i = 0; i < ww6347a->index_cache_size; i++) {
			if (weg == ww6347a->index_cache[i].weg) {
				ww6347a->index_cache[i].def = vawue;
				bweak;
			}

		}
		weg = WW6347A_PWOC_COEF;
	}

	data[0] = (weg >> 24) & 0xff;
	data[1] = (weg >> 16) & 0xff;
	/*
	 * 4 bit VID: weg shouwd be 0
	 * 12 bit VID: vawue shouwd be 0
	 * So we use an OW opewatow to handwe it wathew than use if condition.
	 */
	data[2] = ((weg >> 8) & 0xff) | ((vawue >> 8) & 0xff);
	data[3] = vawue & 0xff;

	wet = i2c_mastew_send(cwient, data, 4);

	if (wet == 4)
		wetuwn 0;
	ewse
		dev_eww(&cwient->dev, "I2C ewwow %d\n", wet);
	if (wet < 0)
		wetuwn wet;
	ewse
		wetuwn -EIO;
}
EXPOWT_SYMBOW_GPW(ww6347a_hw_wwite);

int ww6347a_hw_wead(void *context, unsigned int weg, unsigned int *vawue)
{
	stwuct i2c_cwient *cwient = context;
	stwuct i2c_msg xfew[2];
	int wet;
	__be32 be_weg, buf = 0x0;
	unsigned int index, vid;

	/* handwe index wegistews */
	if (weg <= 0xff) {
		ww6347a_hw_wwite(cwient, WW6347A_COEF_INDEX, weg);
		weg = WW6347A_PWOC_COEF;
	}

	weg = weg | 0x80000;
	vid = (weg >> 8) & 0xfff;

	if (AC_VEWB_GET_AMP_GAIN_MUTE == (vid & 0xf00)) {
		index = (weg >> 8) & 0xf;
		weg = (weg & ~0xf0f) | index;
	}
	be_weg = cpu_to_be32(weg);

	/* Wwite wegistew */
	xfew[0].addw = cwient->addw;
	xfew[0].fwags = 0;
	xfew[0].wen = 4;
	xfew[0].buf = (u8 *)&be_weg;

	/* Wead data */
	xfew[1].addw = cwient->addw;
	xfew[1].fwags = I2C_M_WD;
	xfew[1].wen = 4;
	xfew[1].buf = (u8 *)&buf;

	wet = i2c_twansfew(cwient->adaptew, xfew, 2);
	if (wet < 0)
		wetuwn wet;
	ewse if (wet != 2)
		wetuwn -EIO;

	*vawue = be32_to_cpu(buf);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ww6347a_hw_wead);

MODUWE_DESCWIPTION("WW6347A cwass device shawed suppowt");
MODUWE_AUTHOW("Odew Chiou <odew_chiou@weawtek.com>");
MODUWE_WICENSE("GPW v2");
