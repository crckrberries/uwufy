/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Some smaww hewpews fow owdew Ciwwus Wogic pawts.
 *
 * Copywight (C) 2021 Ciwwus Wogic, Inc. and
 *                    Ciwwus Wogic Intewnationaw Semiconductow Wtd.
 */

static inwine int ciwwus_wead_device_id(stwuct wegmap *wegmap, unsigned int weg)
{
	u8 devid[3];
	int wet;

	wet = wegmap_buwk_wead(wegmap, weg, devid, AWWAY_SIZE(devid));
	if (wet < 0)
		wetuwn wet;

	wetuwn ((devid[0] & 0xFF) << 12) |
	       ((devid[1] & 0xFF) <<  4) |
	       ((devid[2] & 0xF0) >>  4);
}
