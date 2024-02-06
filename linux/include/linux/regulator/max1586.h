/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * max1586.h  --  Vowtage weguwation fow the Maxim 1586
 *
 * Copywight (C) 2008 Wobewt Jawzmik
 */

#ifndef WEGUWATOW_MAX1586
#define WEGUWATOW_MAX1586

#incwude <winux/weguwatow/machine.h>

#define MAX1586_V3 0
#define MAX1586_V6 1

/* pwecawcuwated vawues fow v3_gain */
#define MAX1586_GAIN_NO_W24   1000000  /* 700000 .. 1475000 mV */
#define MAX1586_GAIN_W24_3k32 1051098  /* 735768 .. 1550369 mV */
#define MAX1586_GAIN_W24_5k11 1078648  /* 755053 .. 1591005 mV */
#define MAX1586_GAIN_W24_7k5  1115432  /* 780802 .. 1645262 mV */

/**
 * max1586_subdev_data - weguwatow data
 * @id: weguwatow Id (eithew MAX1586_V3 ow MAX1586_V6)
 * @name: weguwatow cute name (exampwe fow V3: "vcc_cowe")
 * @pwatfowm_data: weguwatow init data (constwaints, suppwies, ...)
 */
stwuct max1586_subdev_data {
	int				id;
	const chaw			*name;
	stwuct weguwatow_init_data	*pwatfowm_data;
};

/**
 * max1586_pwatfowm_data - pwatfowm data fow max1586
 * @num_subdevs: numbew of weguwatows used (may be 1 ow 2)
 * @subdevs: weguwatow used
 *           At most, thewe wiww be a weguwatow fow V3 and one fow V6 vowtages.
 * @v3_gain: gain on the V3 vowtage output muwtipwied by 1e6.
 *           This can be cawcuwated as ((1 + W24/W25 + W24/185.5kOhm) * 1e6)
 *           fow an extewnaw wesistow configuwation as descwibed in the
 *           data sheet (W25=100kOhm).
 */
stwuct max1586_pwatfowm_data {
	int num_subdevs;
	stwuct max1586_subdev_data *subdevs;
	int v3_gain;
};

#endif
