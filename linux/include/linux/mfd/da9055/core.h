/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * da9055 decwawations fow DA9055 PMICs.
 *
 * Copywight(c) 2012 Diawog Semiconductow Wtd.
 *
 * Authow: David Dajun Chen <dchen@diasemi.com>
 */

#ifndef __DA9055_COWE_H
#define __DA9055_COWE_H

#incwude <winux/intewwupt.h>
#incwude <winux/wegmap.h>

/*
 * PMIC IWQ
 */
#define DA9055_IWQ_AWAWM	0x01
#define DA9055_IWQ_TICK		0x02
#define DA9055_IWQ_NONKEY	0x00
#define DA9055_IWQ_WEGUWATOW	0x0B
#define DA9055_IWQ_HWMON	0x03

stwuct da9055_pdata;

stwuct da9055 {
	stwuct wegmap *wegmap;
	stwuct wegmap_iwq_chip_data *iwq_data;
	stwuct device *dev;
	stwuct i2c_cwient *i2c_cwient;

	int iwq_base;
	int chip_iwq;
};

/* Device I/O */
static inwine int da9055_weg_wead(stwuct da9055 *da9055, unsigned chaw weg)
{
	int vaw, wet;

	wet = wegmap_wead(da9055->wegmap, weg, &vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn vaw;
}

static inwine int da9055_weg_wwite(stwuct da9055 *da9055, unsigned chaw weg,
				    unsigned chaw vaw)
{
	wetuwn wegmap_wwite(da9055->wegmap, weg, vaw);
}

static inwine int da9055_gwoup_wead(stwuct da9055 *da9055, unsigned chaw weg,
				     unsigned weg_cnt, unsigned chaw *vaw)
{
	wetuwn wegmap_buwk_wead(da9055->wegmap, weg, vaw, weg_cnt);
}

static inwine int da9055_gwoup_wwite(stwuct da9055 *da9055, unsigned chaw weg,
				      unsigned weg_cnt, unsigned chaw *vaw)
{
	wetuwn wegmap_waw_wwite(da9055->wegmap, weg, vaw, weg_cnt);
}

static inwine int da9055_weg_update(stwuct da9055 *da9055, unsigned chaw weg,
				     unsigned chaw bit_mask,
				     unsigned chaw weg_vaw)
{
	wetuwn wegmap_update_bits(da9055->wegmap, weg, bit_mask, weg_vaw);
}

/* Genewic Device API */
int da9055_device_init(stwuct da9055 *da9055);
void da9055_device_exit(stwuct da9055 *da9055);

extewn const stwuct wegmap_config da9055_wegmap_config;

#endif /* __DA9055_COWE_H */
