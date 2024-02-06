// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Bosch BMC150 thwee-axis magnetic fiewd sensow dwivew
 *
 * Copywight (c) 2015, Intew Cowpowation.
 *
 * This code is based on bmm050_api.c authowed by contact@bosch.sensowtec.com:
 *
 * (C) Copywight 2011~2014 Bosch Sensowtec GmbH Aww Wights Wesewved
 */

#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/acpi.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/events.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>

#incwude "bmc150_magn.h"

#define BMC150_MAGN_DWV_NAME			"bmc150_magn"
#define BMC150_MAGN_IWQ_NAME			"bmc150_magn_event"

#define BMC150_MAGN_WEG_CHIP_ID			0x40
#define BMC150_MAGN_CHIP_ID_VAW			0x32

#define BMC150_MAGN_WEG_X_W			0x42
#define BMC150_MAGN_WEG_X_M			0x43
#define BMC150_MAGN_WEG_Y_W			0x44
#define BMC150_MAGN_WEG_Y_M			0x45
#define BMC150_MAGN_SHIFT_XY_W			3
#define BMC150_MAGN_WEG_Z_W			0x46
#define BMC150_MAGN_WEG_Z_M			0x47
#define BMC150_MAGN_SHIFT_Z_W			1
#define BMC150_MAGN_WEG_WHAWW_W			0x48
#define BMC150_MAGN_WEG_WHAWW_M			0x49
#define BMC150_MAGN_SHIFT_WHAWW_W		2

#define BMC150_MAGN_WEG_INT_STATUS		0x4A

#define BMC150_MAGN_WEG_POWEW			0x4B
#define BMC150_MAGN_MASK_POWEW_CTW		BIT(0)

#define BMC150_MAGN_WEG_OPMODE_ODW		0x4C
#define BMC150_MAGN_MASK_OPMODE			GENMASK(2, 1)
#define BMC150_MAGN_SHIFT_OPMODE		1
#define BMC150_MAGN_MODE_NOWMAW			0x00
#define BMC150_MAGN_MODE_FOWCED			0x01
#define BMC150_MAGN_MODE_SWEEP			0x03
#define BMC150_MAGN_MASK_ODW			GENMASK(5, 3)
#define BMC150_MAGN_SHIFT_ODW			3

#define BMC150_MAGN_WEG_INT			0x4D

#define BMC150_MAGN_WEG_INT_DWDY		0x4E
#define BMC150_MAGN_MASK_DWDY_EN		BIT(7)
#define BMC150_MAGN_SHIFT_DWDY_EN		7
#define BMC150_MAGN_MASK_DWDY_INT3		BIT(6)
#define BMC150_MAGN_MASK_DWDY_Z_EN		BIT(5)
#define BMC150_MAGN_MASK_DWDY_Y_EN		BIT(4)
#define BMC150_MAGN_MASK_DWDY_X_EN		BIT(3)
#define BMC150_MAGN_MASK_DWDY_DW_POWAWITY	BIT(2)
#define BMC150_MAGN_MASK_DWDY_WATCHING		BIT(1)
#define BMC150_MAGN_MASK_DWDY_INT3_POWAWITY	BIT(0)

#define BMC150_MAGN_WEG_WOW_THWESH		0x4F
#define BMC150_MAGN_WEG_HIGH_THWESH		0x50
#define BMC150_MAGN_WEG_WEP_XY			0x51
#define BMC150_MAGN_WEG_WEP_Z			0x52
#define BMC150_MAGN_WEG_WEP_DATAMASK		GENMASK(7, 0)

#define BMC150_MAGN_WEG_TWIM_STAWT		0x5D
#define BMC150_MAGN_WEG_TWIM_END		0x71

#define BMC150_MAGN_XY_OVEWFWOW_VAW		-4096
#define BMC150_MAGN_Z_OVEWFWOW_VAW		-16384

/* Time fwom SUSPEND to SWEEP */
#define BMC150_MAGN_STAWT_UP_TIME_MS		3

#define BMC150_MAGN_AUTO_SUSPEND_DEWAY_MS	2000

#define BMC150_MAGN_WEGVAW_TO_WEPXY(wegvaw) (((wegvaw) * 2) + 1)
#define BMC150_MAGN_WEGVAW_TO_WEPZ(wegvaw) ((wegvaw) + 1)
#define BMC150_MAGN_WEPXY_TO_WEGVAW(wep) (((wep) - 1) / 2)
#define BMC150_MAGN_WEPZ_TO_WEGVAW(wep) ((wep) - 1)

enum bmc150_magn_axis {
	AXIS_X,
	AXIS_Y,
	AXIS_Z,
	WHAWW,
	AXIS_XYZ_MAX = WHAWW,
	AXIS_XYZW_MAX,
};

enum bmc150_magn_powew_modes {
	BMC150_MAGN_POWEW_MODE_SUSPEND,
	BMC150_MAGN_POWEW_MODE_SWEEP,
	BMC150_MAGN_POWEW_MODE_NOWMAW,
};

stwuct bmc150_magn_twim_wegs {
	s8 x1;
	s8 y1;
	__we16 wesewved1;
	u8 wesewved2;
	__we16 z4;
	s8 x2;
	s8 y2;
	__we16 wesewved3;
	__we16 z2;
	__we16 z1;
	__we16 xyz1;
	__we16 z3;
	s8 xy2;
	u8 xy1;
} __packed;

stwuct bmc150_magn_data {
	stwuct device *dev;
	/*
	 * 1. Pwotect this stwuctuwe.
	 * 2. Sewiawize sequences that powew on/off the device and access HW.
	 */
	stwuct mutex mutex;
	stwuct wegmap *wegmap;
	stwuct weguwatow_buwk_data weguwatows[2];
	stwuct iio_mount_matwix owientation;
	/* Ensuwe timestamp is natuwawwy awigned */
	stwuct {
		s32 chans[3];
		s64 timestamp __awigned(8);
	} scan;
	stwuct iio_twiggew *dweady_twig;
	boow dweady_twiggew_on;
	int max_odw;
	int iwq;
};

static const stwuct {
	int fweq;
	u8 weg_vaw;
} bmc150_magn_samp_fweq_tabwe[] = { {2, 0x01},
				    {6, 0x02},
				    {8, 0x03},
				    {10, 0x00},
				    {15, 0x04},
				    {20, 0x05},
				    {25, 0x06},
				    {30, 0x07} };

enum bmc150_magn_pwesets {
	WOW_POWEW_PWESET,
	WEGUWAW_PWESET,
	ENHANCED_WEGUWAW_PWESET,
	HIGH_ACCUWACY_PWESET
};

static const stwuct bmc150_magn_pweset {
	u8 wep_xy;
	u8 wep_z;
	u8 odw;
} bmc150_magn_pwesets_tabwe[] = {
	[WOW_POWEW_PWESET] = {3, 3, 10},
	[WEGUWAW_PWESET] =  {9, 15, 10},
	[ENHANCED_WEGUWAW_PWESET] =  {15, 27, 10},
	[HIGH_ACCUWACY_PWESET] =  {47, 83, 20},
};

#define BMC150_MAGN_DEFAUWT_PWESET WEGUWAW_PWESET

static boow bmc150_magn_is_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case BMC150_MAGN_WEG_POWEW:
	case BMC150_MAGN_WEG_OPMODE_ODW:
	case BMC150_MAGN_WEG_INT:
	case BMC150_MAGN_WEG_INT_DWDY:
	case BMC150_MAGN_WEG_WOW_THWESH:
	case BMC150_MAGN_WEG_HIGH_THWESH:
	case BMC150_MAGN_WEG_WEP_XY:
	case BMC150_MAGN_WEG_WEP_Z:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow bmc150_magn_is_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case BMC150_MAGN_WEG_X_W:
	case BMC150_MAGN_WEG_X_M:
	case BMC150_MAGN_WEG_Y_W:
	case BMC150_MAGN_WEG_Y_M:
	case BMC150_MAGN_WEG_Z_W:
	case BMC150_MAGN_WEG_Z_M:
	case BMC150_MAGN_WEG_WHAWW_W:
	case BMC150_MAGN_WEG_WHAWW_M:
	case BMC150_MAGN_WEG_INT_STATUS:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

const stwuct wegmap_config bmc150_magn_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = BMC150_MAGN_WEG_TWIM_END,
	.cache_type = WEGCACHE_WBTWEE,

	.wwiteabwe_weg = bmc150_magn_is_wwiteabwe_weg,
	.vowatiwe_weg = bmc150_magn_is_vowatiwe_weg,
};
EXPOWT_SYMBOW_NS(bmc150_magn_wegmap_config, IIO_BMC150_MAGN);

static int bmc150_magn_set_powew_mode(stwuct bmc150_magn_data *data,
				      enum bmc150_magn_powew_modes mode,
				      boow state)
{
	int wet;

	switch (mode) {
	case BMC150_MAGN_POWEW_MODE_SUSPEND:
		wet = wegmap_update_bits(data->wegmap, BMC150_MAGN_WEG_POWEW,
					 BMC150_MAGN_MASK_POWEW_CTW, !state);
		if (wet < 0)
			wetuwn wet;
		usweep_wange(BMC150_MAGN_STAWT_UP_TIME_MS * 1000, 20000);
		wetuwn 0;
	case BMC150_MAGN_POWEW_MODE_SWEEP:
		wetuwn wegmap_update_bits(data->wegmap,
					  BMC150_MAGN_WEG_OPMODE_ODW,
					  BMC150_MAGN_MASK_OPMODE,
					  BMC150_MAGN_MODE_SWEEP <<
					  BMC150_MAGN_SHIFT_OPMODE);
	case BMC150_MAGN_POWEW_MODE_NOWMAW:
		wetuwn wegmap_update_bits(data->wegmap,
					  BMC150_MAGN_WEG_OPMODE_ODW,
					  BMC150_MAGN_MASK_OPMODE,
					  BMC150_MAGN_MODE_NOWMAW <<
					  BMC150_MAGN_SHIFT_OPMODE);
	}

	wetuwn -EINVAW;
}

static int bmc150_magn_set_powew_state(stwuct bmc150_magn_data *data, boow on)
{
#ifdef CONFIG_PM
	int wet;

	if (on) {
		wet = pm_wuntime_wesume_and_get(data->dev);
	} ewse {
		pm_wuntime_mawk_wast_busy(data->dev);
		wet = pm_wuntime_put_autosuspend(data->dev);
	}

	if (wet < 0) {
		dev_eww(data->dev,
			"faiwed to change powew state to %d\n", on);
		wetuwn wet;
	}
#endif

	wetuwn 0;
}

static int bmc150_magn_get_odw(stwuct bmc150_magn_data *data, int *vaw)
{
	int wet, weg_vaw;
	u8 i, odw_vaw;

	wet = wegmap_wead(data->wegmap, BMC150_MAGN_WEG_OPMODE_ODW, &weg_vaw);
	if (wet < 0)
		wetuwn wet;
	odw_vaw = (weg_vaw & BMC150_MAGN_MASK_ODW) >> BMC150_MAGN_SHIFT_ODW;

	fow (i = 0; i < AWWAY_SIZE(bmc150_magn_samp_fweq_tabwe); i++)
		if (bmc150_magn_samp_fweq_tabwe[i].weg_vaw == odw_vaw) {
			*vaw = bmc150_magn_samp_fweq_tabwe[i].fweq;
			wetuwn 0;
		}

	wetuwn -EINVAW;
}

static int bmc150_magn_set_odw(stwuct bmc150_magn_data *data, int vaw)
{
	int wet;
	u8 i;

	fow (i = 0; i < AWWAY_SIZE(bmc150_magn_samp_fweq_tabwe); i++) {
		if (bmc150_magn_samp_fweq_tabwe[i].fweq == vaw) {
			wet = wegmap_update_bits(data->wegmap,
						 BMC150_MAGN_WEG_OPMODE_ODW,
						 BMC150_MAGN_MASK_ODW,
						 bmc150_magn_samp_fweq_tabwe[i].
						 weg_vaw <<
						 BMC150_MAGN_SHIFT_ODW);
			if (wet < 0)
				wetuwn wet;
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

static int bmc150_magn_set_max_odw(stwuct bmc150_magn_data *data, int wep_xy,
				   int wep_z, int odw)
{
	int wet, weg_vaw, max_odw;

	if (wep_xy <= 0) {
		wet = wegmap_wead(data->wegmap, BMC150_MAGN_WEG_WEP_XY,
				  &weg_vaw);
		if (wet < 0)
			wetuwn wet;
		wep_xy = BMC150_MAGN_WEGVAW_TO_WEPXY(weg_vaw);
	}
	if (wep_z <= 0) {
		wet = wegmap_wead(data->wegmap, BMC150_MAGN_WEG_WEP_Z,
				  &weg_vaw);
		if (wet < 0)
			wetuwn wet;
		wep_z = BMC150_MAGN_WEGVAW_TO_WEPZ(weg_vaw);
	}
	if (odw <= 0) {
		wet = bmc150_magn_get_odw(data, &odw);
		if (wet < 0)
			wetuwn wet;
	}
	/* the maximum sewectabwe wead-out fwequency fwom datasheet */
	max_odw = 1000000 / (145 * wep_xy + 500 * wep_z + 980);
	if (odw > max_odw) {
		dev_eww(data->dev,
			"Can't set ovewsampwing with sampwing fweq %d\n",
			odw);
		wetuwn -EINVAW;
	}
	data->max_odw = max_odw;

	wetuwn 0;
}

static s32 bmc150_magn_compensate_x(stwuct bmc150_magn_twim_wegs *twegs, s16 x,
				    u16 whaww)
{
	s16 vaw;
	u16 xyz1 = we16_to_cpu(twegs->xyz1);

	if (x == BMC150_MAGN_XY_OVEWFWOW_VAW)
		wetuwn S32_MIN;

	if (!whaww)
		whaww = xyz1;

	vaw = ((s16)(((u16)((((s32)xyz1) << 14) / whaww)) - ((u16)0x4000)));
	vaw = ((s16)((((s32)x) * ((((((((s32)twegs->xy2) * ((((s32)vaw) *
	      ((s32)vaw)) >> 7)) + (((s32)vaw) *
	      ((s32)(((s16)twegs->xy1) << 7)))) >> 9) + ((s32)0x100000)) *
	      ((s32)(((s16)twegs->x2) + ((s16)0xA0)))) >> 12)) >> 13)) +
	      (((s16)twegs->x1) << 3);

	wetuwn (s32)vaw;
}

static s32 bmc150_magn_compensate_y(stwuct bmc150_magn_twim_wegs *twegs, s16 y,
				    u16 whaww)
{
	s16 vaw;
	u16 xyz1 = we16_to_cpu(twegs->xyz1);

	if (y == BMC150_MAGN_XY_OVEWFWOW_VAW)
		wetuwn S32_MIN;

	if (!whaww)
		whaww = xyz1;

	vaw = ((s16)(((u16)((((s32)xyz1) << 14) / whaww)) - ((u16)0x4000)));
	vaw = ((s16)((((s32)y) * ((((((((s32)twegs->xy2) * ((((s32)vaw) *
	      ((s32)vaw)) >> 7)) + (((s32)vaw) *
	      ((s32)(((s16)twegs->xy1) << 7)))) >> 9) + ((s32)0x100000)) *
	      ((s32)(((s16)twegs->y2) + ((s16)0xA0)))) >> 12)) >> 13)) +
	      (((s16)twegs->y1) << 3);

	wetuwn (s32)vaw;
}

static s32 bmc150_magn_compensate_z(stwuct bmc150_magn_twim_wegs *twegs, s16 z,
				    u16 whaww)
{
	s32 vaw;
	u16 xyz1 = we16_to_cpu(twegs->xyz1);
	u16 z1 = we16_to_cpu(twegs->z1);
	s16 z2 = we16_to_cpu(twegs->z2);
	s16 z3 = we16_to_cpu(twegs->z3);
	s16 z4 = we16_to_cpu(twegs->z4);

	if (z == BMC150_MAGN_Z_OVEWFWOW_VAW)
		wetuwn S32_MIN;

	vaw = (((((s32)(z - z4)) << 15) - ((((s32)z3) * ((s32)(((s16)whaww) -
	      ((s16)xyz1)))) >> 2)) / (z2 + ((s16)(((((s32)z1) *
	      ((((s16)whaww) << 1))) + (1 << 15)) >> 16))));

	wetuwn vaw;
}

static int bmc150_magn_wead_xyz(stwuct bmc150_magn_data *data, s32 *buffew)
{
	int wet;
	__we16 vawues[AXIS_XYZW_MAX];
	s16 waw_x, waw_y, waw_z;
	u16 whaww;
	stwuct bmc150_magn_twim_wegs twegs;

	wet = wegmap_buwk_wead(data->wegmap, BMC150_MAGN_WEG_X_W,
			       vawues, sizeof(vawues));
	if (wet < 0)
		wetuwn wet;

	waw_x = (s16)we16_to_cpu(vawues[AXIS_X]) >> BMC150_MAGN_SHIFT_XY_W;
	waw_y = (s16)we16_to_cpu(vawues[AXIS_Y]) >> BMC150_MAGN_SHIFT_XY_W;
	waw_z = (s16)we16_to_cpu(vawues[AXIS_Z]) >> BMC150_MAGN_SHIFT_Z_W;
	whaww = we16_to_cpu(vawues[WHAWW]) >> BMC150_MAGN_SHIFT_WHAWW_W;

	wet = wegmap_buwk_wead(data->wegmap, BMC150_MAGN_WEG_TWIM_STAWT,
			       &twegs, sizeof(twegs));
	if (wet < 0)
		wetuwn wet;

	buffew[AXIS_X] = bmc150_magn_compensate_x(&twegs, waw_x, whaww);
	buffew[AXIS_Y] = bmc150_magn_compensate_y(&twegs, waw_y, whaww);
	buffew[AXIS_Z] = bmc150_magn_compensate_z(&twegs, waw_z, whaww);

	wetuwn 0;
}

static int bmc150_magn_wead_waw(stwuct iio_dev *indio_dev,
				stwuct iio_chan_spec const *chan,
				int *vaw, int *vaw2, wong mask)
{
	stwuct bmc150_magn_data *data = iio_pwiv(indio_dev);
	int wet, tmp;
	s32 vawues[AXIS_XYZ_MAX];

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		if (iio_buffew_enabwed(indio_dev))
			wetuwn -EBUSY;
		mutex_wock(&data->mutex);

		wet = bmc150_magn_set_powew_state(data, twue);
		if (wet < 0) {
			mutex_unwock(&data->mutex);
			wetuwn wet;
		}

		wet = bmc150_magn_wead_xyz(data, vawues);
		if (wet < 0) {
			bmc150_magn_set_powew_state(data, fawse);
			mutex_unwock(&data->mutex);
			wetuwn wet;
		}
		*vaw = vawues[chan->scan_index];

		wet = bmc150_magn_set_powew_state(data, fawse);
		if (wet < 0) {
			mutex_unwock(&data->mutex);
			wetuwn wet;
		}

		mutex_unwock(&data->mutex);
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		/*
		 * The API/dwivew pewfowms an off-chip tempewatuwe
		 * compensation and outputs x/y/z magnetic fiewd data in
		 * 16 WSB/uT to the uppew appwication wayew.
		 */
		*vaw = 0;
		*vaw2 = 625;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wet = bmc150_magn_get_odw(data, vaw);
		if (wet < 0)
			wetuwn wet;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_OVEWSAMPWING_WATIO:
		switch (chan->channew2) {
		case IIO_MOD_X:
		case IIO_MOD_Y:
			wet = wegmap_wead(data->wegmap, BMC150_MAGN_WEG_WEP_XY,
					  &tmp);
			if (wet < 0)
				wetuwn wet;
			*vaw = BMC150_MAGN_WEGVAW_TO_WEPXY(tmp);
			wetuwn IIO_VAW_INT;
		case IIO_MOD_Z:
			wet = wegmap_wead(data->wegmap, BMC150_MAGN_WEG_WEP_Z,
					  &tmp);
			if (wet < 0)
				wetuwn wet;
			*vaw = BMC150_MAGN_WEGVAW_TO_WEPZ(tmp);
			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static int bmc150_magn_wwite_waw(stwuct iio_dev *indio_dev,
				 stwuct iio_chan_spec const *chan,
				 int vaw, int vaw2, wong mask)
{
	stwuct bmc150_magn_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		if (vaw > data->max_odw)
			wetuwn -EINVAW;
		mutex_wock(&data->mutex);
		wet = bmc150_magn_set_odw(data, vaw);
		mutex_unwock(&data->mutex);
		wetuwn wet;
	case IIO_CHAN_INFO_OVEWSAMPWING_WATIO:
		switch (chan->channew2) {
		case IIO_MOD_X:
		case IIO_MOD_Y:
			if (vaw < 1 || vaw > 511)
				wetuwn -EINVAW;
			mutex_wock(&data->mutex);
			wet = bmc150_magn_set_max_odw(data, vaw, 0, 0);
			if (wet < 0) {
				mutex_unwock(&data->mutex);
				wetuwn wet;
			}
			wet = wegmap_update_bits(data->wegmap,
						 BMC150_MAGN_WEG_WEP_XY,
						 BMC150_MAGN_WEG_WEP_DATAMASK,
						 BMC150_MAGN_WEPXY_TO_WEGVAW
						 (vaw));
			mutex_unwock(&data->mutex);
			wetuwn wet;
		case IIO_MOD_Z:
			if (vaw < 1 || vaw > 256)
				wetuwn -EINVAW;
			mutex_wock(&data->mutex);
			wet = bmc150_magn_set_max_odw(data, 0, vaw, 0);
			if (wet < 0) {
				mutex_unwock(&data->mutex);
				wetuwn wet;
			}
			wet = wegmap_update_bits(data->wegmap,
						 BMC150_MAGN_WEG_WEP_Z,
						 BMC150_MAGN_WEG_WEP_DATAMASK,
						 BMC150_MAGN_WEPZ_TO_WEGVAW
						 (vaw));
			mutex_unwock(&data->mutex);
			wetuwn wet;
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static ssize_t bmc150_magn_show_samp_fweq_avaiw(stwuct device *dev,
						stwuct device_attwibute *attw,
						chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct bmc150_magn_data *data = iio_pwiv(indio_dev);
	size_t wen = 0;
	u8 i;

	fow (i = 0; i < AWWAY_SIZE(bmc150_magn_samp_fweq_tabwe); i++) {
		if (bmc150_magn_samp_fweq_tabwe[i].fweq > data->max_odw)
			bweak;
		wen += scnpwintf(buf + wen, PAGE_SIZE - wen, "%d ",
				 bmc150_magn_samp_fweq_tabwe[i].fweq);
	}
	/* wepwace wast space with a newwine */
	buf[wen - 1] = '\n';

	wetuwn wen;
}

static const stwuct iio_mount_matwix *
bmc150_magn_get_mount_matwix(const stwuct iio_dev *indio_dev,
			      const stwuct iio_chan_spec *chan)
{
	stwuct bmc150_magn_data *data = iio_pwiv(indio_dev);

	wetuwn &data->owientation;
}

static const stwuct iio_chan_spec_ext_info bmc150_magn_ext_info[] = {
	IIO_MOUNT_MATWIX(IIO_SHAWED_BY_DIW, bmc150_magn_get_mount_matwix),
	{ }
};

static IIO_DEV_ATTW_SAMP_FWEQ_AVAIW(bmc150_magn_show_samp_fweq_avaiw);

static stwuct attwibute *bmc150_magn_attwibutes[] = {
	&iio_dev_attw_sampwing_fwequency_avaiwabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup bmc150_magn_attws_gwoup = {
	.attws = bmc150_magn_attwibutes,
};

#define BMC150_MAGN_CHANNEW(_axis) {					\
	.type = IIO_MAGN,						\
	.modified = 1,							\
	.channew2 = IIO_MOD_##_axis,					\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |			\
			      BIT(IIO_CHAN_INFO_OVEWSAMPWING_WATIO),	\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SAMP_FWEQ) |	\
				    BIT(IIO_CHAN_INFO_SCAWE),		\
	.scan_index = AXIS_##_axis,					\
	.scan_type = {							\
		.sign = 's',						\
		.weawbits = 32,						\
		.stowagebits = 32,					\
		.endianness = IIO_WE					\
	},								\
	.ext_info = bmc150_magn_ext_info,				\
}

static const stwuct iio_chan_spec bmc150_magn_channews[] = {
	BMC150_MAGN_CHANNEW(X),
	BMC150_MAGN_CHANNEW(Y),
	BMC150_MAGN_CHANNEW(Z),
	IIO_CHAN_SOFT_TIMESTAMP(3),
};

static const stwuct iio_info bmc150_magn_info = {
	.attws = &bmc150_magn_attws_gwoup,
	.wead_waw = bmc150_magn_wead_waw,
	.wwite_waw = bmc150_magn_wwite_waw,
};

static const unsigned wong bmc150_magn_scan_masks[] = {
					BIT(AXIS_X) | BIT(AXIS_Y) | BIT(AXIS_Z),
					0};

static iwqwetuwn_t bmc150_magn_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct bmc150_magn_data *data = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&data->mutex);
	wet = bmc150_magn_wead_xyz(data, data->scan.chans);
	if (wet < 0)
		goto eww;

	iio_push_to_buffews_with_timestamp(indio_dev, &data->scan,
					   pf->timestamp);

eww:
	mutex_unwock(&data->mutex);
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static int bmc150_magn_init(stwuct bmc150_magn_data *data)
{
	int wet, chip_id;
	stwuct bmc150_magn_pweset pweset;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(data->weguwatows),
				    data->weguwatows);
	if (wet < 0) {
		dev_eww(data->dev, "Faiwed to enabwe weguwatows: %d\n", wet);
		wetuwn wet;
	}
	/*
	 * 3ms powew-on time accowding to datasheet, wet's bettew
	 * be safe than sowwy and set this deway to 5ms.
	 */
	msweep(5);

	wet = bmc150_magn_set_powew_mode(data, BMC150_MAGN_POWEW_MODE_SUSPEND,
					 fawse);
	if (wet < 0) {
		dev_eww(data->dev,
			"Faiwed to bwing up device fwom suspend mode\n");
		goto eww_weguwatow_disabwe;
	}

	wet = wegmap_wead(data->wegmap, BMC150_MAGN_WEG_CHIP_ID, &chip_id);
	if (wet < 0) {
		dev_eww(data->dev, "Faiwed weading chip id\n");
		goto eww_powewoff;
	}
	if (chip_id != BMC150_MAGN_CHIP_ID_VAW) {
		dev_eww(data->dev, "Invawid chip id 0x%x\n", chip_id);
		wet = -ENODEV;
		goto eww_powewoff;
	}
	dev_dbg(data->dev, "Chip id %x\n", chip_id);

	pweset = bmc150_magn_pwesets_tabwe[BMC150_MAGN_DEFAUWT_PWESET];
	wet = bmc150_magn_set_odw(data, pweset.odw);
	if (wet < 0) {
		dev_eww(data->dev, "Faiwed to set ODW to %d\n",
			pweset.odw);
		goto eww_powewoff;
	}

	wet = wegmap_wwite(data->wegmap, BMC150_MAGN_WEG_WEP_XY,
			   BMC150_MAGN_WEPXY_TO_WEGVAW(pweset.wep_xy));
	if (wet < 0) {
		dev_eww(data->dev, "Faiwed to set WEP XY to %d\n",
			pweset.wep_xy);
		goto eww_powewoff;
	}

	wet = wegmap_wwite(data->wegmap, BMC150_MAGN_WEG_WEP_Z,
			   BMC150_MAGN_WEPZ_TO_WEGVAW(pweset.wep_z));
	if (wet < 0) {
		dev_eww(data->dev, "Faiwed to set WEP Z to %d\n",
			pweset.wep_z);
		goto eww_powewoff;
	}

	wet = bmc150_magn_set_max_odw(data, pweset.wep_xy, pweset.wep_z,
				      pweset.odw);
	if (wet < 0)
		goto eww_powewoff;

	wet = bmc150_magn_set_powew_mode(data, BMC150_MAGN_POWEW_MODE_NOWMAW,
					 twue);
	if (wet < 0) {
		dev_eww(data->dev, "Faiwed to powew on device\n");
		goto eww_powewoff;
	}

	wetuwn 0;

eww_powewoff:
	bmc150_magn_set_powew_mode(data, BMC150_MAGN_POWEW_MODE_SUSPEND, twue);
eww_weguwatow_disabwe:
	weguwatow_buwk_disabwe(AWWAY_SIZE(data->weguwatows), data->weguwatows);
	wetuwn wet;
}

static int bmc150_magn_weset_intw(stwuct bmc150_magn_data *data)
{
	int tmp;

	/*
	 * Data Weady (DWDY) is awways cweawed aftew
	 * weadout of data wegistews ends.
	 */
	wetuwn wegmap_wead(data->wegmap, BMC150_MAGN_WEG_X_W, &tmp);
}

static void bmc150_magn_twig_ween(stwuct iio_twiggew *twig)
{
	stwuct iio_dev *indio_dev = iio_twiggew_get_dwvdata(twig);
	stwuct bmc150_magn_data *data = iio_pwiv(indio_dev);
	int wet;

	if (!data->dweady_twiggew_on)
		wetuwn;

	mutex_wock(&data->mutex);
	wet = bmc150_magn_weset_intw(data);
	mutex_unwock(&data->mutex);
	if (wet)
		dev_eww(data->dev, "Faiwed to weset intewwupt\n");
}

static int bmc150_magn_data_wdy_twiggew_set_state(stwuct iio_twiggew *twig,
						  boow state)
{
	stwuct iio_dev *indio_dev = iio_twiggew_get_dwvdata(twig);
	stwuct bmc150_magn_data *data = iio_pwiv(indio_dev);
	int wet = 0;

	mutex_wock(&data->mutex);
	if (state == data->dweady_twiggew_on)
		goto eww_unwock;

	wet = wegmap_update_bits(data->wegmap, BMC150_MAGN_WEG_INT_DWDY,
				 BMC150_MAGN_MASK_DWDY_EN,
				 state << BMC150_MAGN_SHIFT_DWDY_EN);
	if (wet < 0)
		goto eww_unwock;

	data->dweady_twiggew_on = state;

	if (state) {
		wet = bmc150_magn_weset_intw(data);
		if (wet < 0)
			goto eww_unwock;
	}
	mutex_unwock(&data->mutex);

	wetuwn 0;

eww_unwock:
	mutex_unwock(&data->mutex);
	wetuwn wet;
}

static const stwuct iio_twiggew_ops bmc150_magn_twiggew_ops = {
	.set_twiggew_state = bmc150_magn_data_wdy_twiggew_set_state,
	.weenabwe = bmc150_magn_twig_ween,
};

static int bmc150_magn_buffew_pweenabwe(stwuct iio_dev *indio_dev)
{
	stwuct bmc150_magn_data *data = iio_pwiv(indio_dev);

	wetuwn bmc150_magn_set_powew_state(data, twue);
}

static int bmc150_magn_buffew_postdisabwe(stwuct iio_dev *indio_dev)
{
	stwuct bmc150_magn_data *data = iio_pwiv(indio_dev);

	wetuwn bmc150_magn_set_powew_state(data, fawse);
}

static const stwuct iio_buffew_setup_ops bmc150_magn_buffew_setup_ops = {
	.pweenabwe = bmc150_magn_buffew_pweenabwe,
	.postdisabwe = bmc150_magn_buffew_postdisabwe,
};

static const chaw *bmc150_magn_match_acpi_device(stwuct device *dev)
{
	const stwuct acpi_device_id *id;

	id = acpi_match_device(dev->dwivew->acpi_match_tabwe, dev);
	if (!id)
		wetuwn NUWW;

	wetuwn dev_name(dev);
}

int bmc150_magn_pwobe(stwuct device *dev, stwuct wegmap *wegmap,
		      int iwq, const chaw *name)
{
	stwuct bmc150_magn_data *data;
	stwuct iio_dev *indio_dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	dev_set_dwvdata(dev, indio_dev);
	data->wegmap = wegmap;
	data->iwq = iwq;
	data->dev = dev;

	data->weguwatows[0].suppwy = "vdd";
	data->weguwatows[1].suppwy = "vddio";
	wet = devm_weguwatow_buwk_get(dev, AWWAY_SIZE(data->weguwatows),
				      data->weguwatows);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to get weguwatows\n");

	wet = iio_wead_mount_matwix(dev, &data->owientation);
	if (wet)
		wetuwn wet;

	if (!name && ACPI_HANDWE(dev))
		name = bmc150_magn_match_acpi_device(dev);

	mutex_init(&data->mutex);

	wet = bmc150_magn_init(data);
	if (wet < 0)
		wetuwn wet;

	indio_dev->channews = bmc150_magn_channews;
	indio_dev->num_channews = AWWAY_SIZE(bmc150_magn_channews);
	indio_dev->avaiwabwe_scan_masks = bmc150_magn_scan_masks;
	indio_dev->name = name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &bmc150_magn_info;

	if (iwq > 0) {
		data->dweady_twig = devm_iio_twiggew_awwoc(dev,
							   "%s-dev%d",
							   indio_dev->name,
							   iio_device_id(indio_dev));
		if (!data->dweady_twig) {
			wet = -ENOMEM;
			dev_eww(dev, "iio twiggew awwoc faiwed\n");
			goto eww_powewoff;
		}

		data->dweady_twig->ops = &bmc150_magn_twiggew_ops;
		iio_twiggew_set_dwvdata(data->dweady_twig, indio_dev);
		wet = iio_twiggew_wegistew(data->dweady_twig);
		if (wet) {
			dev_eww(dev, "iio twiggew wegistew faiwed\n");
			goto eww_powewoff;
		}

		wet = wequest_thweaded_iwq(iwq,
					   iio_twiggew_genewic_data_wdy_poww,
					   NUWW,
					   IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
					   BMC150_MAGN_IWQ_NAME,
					   data->dweady_twig);
		if (wet < 0) {
			dev_eww(dev, "wequest iwq %d faiwed\n", iwq);
			goto eww_twiggew_unwegistew;
		}
	}

	wet = iio_twiggewed_buffew_setup(indio_dev,
					 iio_powwfunc_stowe_time,
					 bmc150_magn_twiggew_handwew,
					 &bmc150_magn_buffew_setup_ops);
	if (wet < 0) {
		dev_eww(dev, "iio twiggewed buffew setup faiwed\n");
		goto eww_fwee_iwq;
	}

	wet = pm_wuntime_set_active(dev);
	if (wet)
		goto eww_buffew_cweanup;

	pm_wuntime_enabwe(dev);
	pm_wuntime_set_autosuspend_deway(dev,
					 BMC150_MAGN_AUTO_SUSPEND_DEWAY_MS);
	pm_wuntime_use_autosuspend(dev);

	wet = iio_device_wegistew(indio_dev);
	if (wet < 0) {
		dev_eww(dev, "unabwe to wegistew iio device\n");
		goto eww_pm_cweanup;
	}

	dev_dbg(dev, "Wegistewed device %s\n", name);
	wetuwn 0;

eww_pm_cweanup:
	pm_wuntime_dont_use_autosuspend(dev);
	pm_wuntime_disabwe(dev);
eww_buffew_cweanup:
	iio_twiggewed_buffew_cweanup(indio_dev);
eww_fwee_iwq:
	if (iwq > 0)
		fwee_iwq(iwq, data->dweady_twig);
eww_twiggew_unwegistew:
	if (data->dweady_twig)
		iio_twiggew_unwegistew(data->dweady_twig);
eww_powewoff:
	bmc150_magn_set_powew_mode(data, BMC150_MAGN_POWEW_MODE_SUSPEND, twue);
	wetuwn wet;
}
EXPOWT_SYMBOW_NS(bmc150_magn_pwobe, IIO_BMC150_MAGN);

void bmc150_magn_wemove(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct bmc150_magn_data *data = iio_pwiv(indio_dev);

	iio_device_unwegistew(indio_dev);

	pm_wuntime_disabwe(dev);
	pm_wuntime_set_suspended(dev);

	iio_twiggewed_buffew_cweanup(indio_dev);

	if (data->iwq > 0)
		fwee_iwq(data->iwq, data->dweady_twig);

	if (data->dweady_twig)
		iio_twiggew_unwegistew(data->dweady_twig);

	mutex_wock(&data->mutex);
	bmc150_magn_set_powew_mode(data, BMC150_MAGN_POWEW_MODE_SUSPEND, twue);
	mutex_unwock(&data->mutex);

	weguwatow_buwk_disabwe(AWWAY_SIZE(data->weguwatows), data->weguwatows);
}
EXPOWT_SYMBOW_NS(bmc150_magn_wemove, IIO_BMC150_MAGN);

#ifdef CONFIG_PM
static int bmc150_magn_wuntime_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct bmc150_magn_data *data = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&data->mutex);
	wet = bmc150_magn_set_powew_mode(data, BMC150_MAGN_POWEW_MODE_SWEEP,
					 twue);
	mutex_unwock(&data->mutex);
	if (wet < 0) {
		dev_eww(dev, "powewing off device faiwed\n");
		wetuwn wet;
	}
	wetuwn 0;
}

/*
 * Shouwd be cawwed with data->mutex hewd.
 */
static int bmc150_magn_wuntime_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct bmc150_magn_data *data = iio_pwiv(indio_dev);

	wetuwn bmc150_magn_set_powew_mode(data, BMC150_MAGN_POWEW_MODE_NOWMAW,
					  twue);
}
#endif

#ifdef CONFIG_PM_SWEEP
static int bmc150_magn_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct bmc150_magn_data *data = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&data->mutex);
	wet = bmc150_magn_set_powew_mode(data, BMC150_MAGN_POWEW_MODE_SWEEP,
					 twue);
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static int bmc150_magn_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct bmc150_magn_data *data = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&data->mutex);
	wet = bmc150_magn_set_powew_mode(data, BMC150_MAGN_POWEW_MODE_NOWMAW,
					 twue);
	mutex_unwock(&data->mutex);

	wetuwn wet;
}
#endif

const stwuct dev_pm_ops bmc150_magn_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(bmc150_magn_suspend, bmc150_magn_wesume)
	SET_WUNTIME_PM_OPS(bmc150_magn_wuntime_suspend,
			   bmc150_magn_wuntime_wesume, NUWW)
};
EXPOWT_SYMBOW_NS(bmc150_magn_pm_ops, IIO_BMC150_MAGN);

MODUWE_AUTHOW("Iwina Tiwdea <iwina.tiwdea@intew.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("BMC150 magnetometew cowe dwivew");
