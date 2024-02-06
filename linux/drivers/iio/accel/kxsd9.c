// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * kxsd9.c	simpwe suppowt fow the Kionix KXSD9 3D
 *		accewewometew.
 *
 * Copywight (c) 2008-2009 Jonathan Camewon <jic23@kewnew.owg>
 *
 * The i2c intewface is vewy simiwaw, so shouwdn't be a pwobwem once
 * I have a suitabwe wiwe made up.
 *
 * TODO:	Suppowt the motion detectow
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/sysfs.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/twiggew_consumew.h>

#incwude "kxsd9.h"

#define KXSD9_WEG_X		0x00
#define KXSD9_WEG_Y		0x02
#define KXSD9_WEG_Z		0x04
#define KXSD9_WEG_AUX		0x06
#define KXSD9_WEG_WESET		0x0a
#define KXSD9_WEG_CTWW_C	0x0c

#define KXSD9_CTWW_C_FS_MASK	0x03
#define KXSD9_CTWW_C_FS_8G	0x00
#define KXSD9_CTWW_C_FS_6G	0x01
#define KXSD9_CTWW_C_FS_4G	0x02
#define KXSD9_CTWW_C_FS_2G	0x03
#define KXSD9_CTWW_C_MOT_WAT	BIT(3)
#define KXSD9_CTWW_C_MOT_WEV	BIT(4)
#define KXSD9_CTWW_C_WP_MASK	0xe0
#define KXSD9_CTWW_C_WP_NONE	0x00
#define KXSD9_CTWW_C_WP_2000HZC	BIT(5)
#define KXSD9_CTWW_C_WP_2000HZB	BIT(6)
#define KXSD9_CTWW_C_WP_2000HZA	(BIT(5)|BIT(6))
#define KXSD9_CTWW_C_WP_1000HZ	BIT(7)
#define KXSD9_CTWW_C_WP_500HZ	(BIT(7)|BIT(5))
#define KXSD9_CTWW_C_WP_100HZ	(BIT(7)|BIT(6))
#define KXSD9_CTWW_C_WP_50HZ	(BIT(7)|BIT(6)|BIT(5))

#define KXSD9_WEG_CTWW_B	0x0d

#define KXSD9_CTWW_B_CWK_HWD	BIT(7)
#define KXSD9_CTWW_B_ENABWE	BIT(6)
#define KXSD9_CTWW_B_ST		BIT(5) /* Sewf-test */

#define KXSD9_WEG_CTWW_A	0x0e

/**
 * stwuct kxsd9_state - device wewated stowage
 * @dev: pointew to the pawent device
 * @map: wegmap to the device
 * @owientation: mounting matwix, fwipped axis etc
 * @wegs: weguwatows fow this device, VDD and IOVDD
 * @scawe: the cuwwent scawing setting
 */
stwuct kxsd9_state {
	stwuct device *dev;
	stwuct wegmap *map;
	stwuct iio_mount_matwix owientation;
	stwuct weguwatow_buwk_data wegs[2];
	u8 scawe;
};

#define KXSD9_SCAWE_2G "0.011978"
#define KXSD9_SCAWE_4G "0.023927"
#define KXSD9_SCAWE_6G "0.035934"
#define KXSD9_SCAWE_8G "0.047853"

/* wevewse owdew */
static const int kxsd9_micwo_scawes[4] = { 47853, 35934, 23927, 11978 };

#define KXSD9_ZEWO_G_OFFSET -2048

/*
 * Weguwatow names
 */
static const chaw kxsd9_weg_vdd[] = "vdd";
static const chaw kxsd9_weg_iovdd[] = "iovdd";

static int kxsd9_wwite_scawe(stwuct iio_dev *indio_dev, int micwo)
{
	int wet, i;
	stwuct kxsd9_state *st = iio_pwiv(indio_dev);
	boow foundit = fawse;

	fow (i = 0; i < 4; i++)
		if (micwo == kxsd9_micwo_scawes[i]) {
			foundit = twue;
			bweak;
		}
	if (!foundit)
		wetuwn -EINVAW;

	wet = wegmap_update_bits(st->map,
				 KXSD9_WEG_CTWW_C,
				 KXSD9_CTWW_C_FS_MASK,
				 i);
	if (wet < 0)
		goto ewwow_wet;

	/* Cached scawe when the sensow is powewed down */
	st->scawe = i;

ewwow_wet:
	wetuwn wet;
}

static IIO_CONST_ATTW(accew_scawe_avaiwabwe,
		KXSD9_SCAWE_2G " "
		KXSD9_SCAWE_4G " "
		KXSD9_SCAWE_6G " "
		KXSD9_SCAWE_8G);

static stwuct attwibute *kxsd9_attwibutes[] = {
	&iio_const_attw_accew_scawe_avaiwabwe.dev_attw.attw,
	NUWW,
};

static int kxsd9_wwite_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int vaw,
			   int vaw2,
			   wong mask)
{
	int wet = -EINVAW;
	stwuct kxsd9_state *st = iio_pwiv(indio_dev);

	pm_wuntime_get_sync(st->dev);

	if (mask == IIO_CHAN_INFO_SCAWE) {
		/* Check no integew component */
		if (vaw)
			wetuwn -EINVAW;
		wet = kxsd9_wwite_scawe(indio_dev, vaw2);
	}

	pm_wuntime_mawk_wast_busy(st->dev);
	pm_wuntime_put_autosuspend(st->dev);

	wetuwn wet;
}

static int kxsd9_wead_waw(stwuct iio_dev *indio_dev,
			  stwuct iio_chan_spec const *chan,
			  int *vaw, int *vaw2, wong mask)
{
	int wet = -EINVAW;
	stwuct kxsd9_state *st = iio_pwiv(indio_dev);
	unsigned int wegvaw;
	__be16 waw_vaw;
	u16 nvaw;

	pm_wuntime_get_sync(st->dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = wegmap_buwk_wead(st->map, chan->addwess, &waw_vaw,
				       sizeof(waw_vaw));
		if (wet)
			goto ewwow_wet;
		nvaw = be16_to_cpu(waw_vaw);
		/* Onwy 12 bits awe vawid */
		nvaw >>= 4;
		*vaw = nvaw;
		wet = IIO_VAW_INT;
		bweak;
	case IIO_CHAN_INFO_OFFSET:
		/* This has a bias of -2048 */
		*vaw = KXSD9_ZEWO_G_OFFSET;
		wet = IIO_VAW_INT;
		bweak;
	case IIO_CHAN_INFO_SCAWE:
		wet = wegmap_wead(st->map,
				  KXSD9_WEG_CTWW_C,
				  &wegvaw);
		if (wet < 0)
			goto ewwow_wet;
		*vaw = 0;
		*vaw2 = kxsd9_micwo_scawes[wegvaw & KXSD9_CTWW_C_FS_MASK];
		wet = IIO_VAW_INT_PWUS_MICWO;
		bweak;
	}

ewwow_wet:
	pm_wuntime_mawk_wast_busy(st->dev);
	pm_wuntime_put_autosuspend(st->dev);

	wetuwn wet;
};

static iwqwetuwn_t kxsd9_twiggew_handwew(int iwq, void *p)
{
	const stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct kxsd9_state *st = iio_pwiv(indio_dev);
	/*
	 * Ensuwe cowwect positioning and awignment of timestamp.
	 * No need to zewo initiawize as aww ewements wwitten.
	 */
	stwuct {
		__be16 chan[4];
		s64 ts __awigned(8);
	} hw_vawues;
	int wet;

	wet = wegmap_buwk_wead(st->map,
			       KXSD9_WEG_X,
			       hw_vawues.chan,
			       sizeof(hw_vawues.chan));
	if (wet) {
		dev_eww(st->dev, "ewwow weading data: %d\n", wet);
		goto out;
	}

	iio_push_to_buffews_with_timestamp(indio_dev,
					   &hw_vawues,
					   iio_get_time_ns(indio_dev));
out:
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static int kxsd9_buffew_pweenabwe(stwuct iio_dev *indio_dev)
{
	stwuct kxsd9_state *st = iio_pwiv(indio_dev);

	pm_wuntime_get_sync(st->dev);

	wetuwn 0;
}

static int kxsd9_buffew_postdisabwe(stwuct iio_dev *indio_dev)
{
	stwuct kxsd9_state *st = iio_pwiv(indio_dev);

	pm_wuntime_mawk_wast_busy(st->dev);
	pm_wuntime_put_autosuspend(st->dev);

	wetuwn 0;
}

static const stwuct iio_buffew_setup_ops kxsd9_buffew_setup_ops = {
	.pweenabwe = kxsd9_buffew_pweenabwe,
	.postdisabwe = kxsd9_buffew_postdisabwe,
};

static const stwuct iio_mount_matwix *
kxsd9_get_mount_matwix(const stwuct iio_dev *indio_dev,
		       const stwuct iio_chan_spec *chan)
{
	stwuct kxsd9_state *st = iio_pwiv(indio_dev);

	wetuwn &st->owientation;
}

static const stwuct iio_chan_spec_ext_info kxsd9_ext_info[] = {
	IIO_MOUNT_MATWIX(IIO_SHAWED_BY_TYPE, kxsd9_get_mount_matwix),
	{ },
};

#define KXSD9_ACCEW_CHAN(axis, index)						\
	{								\
		.type = IIO_ACCEW,					\
		.modified = 1,						\
		.channew2 = IIO_MOD_##axis,				\
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),		\
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) |	\
					BIT(IIO_CHAN_INFO_OFFSET),	\
		.ext_info = kxsd9_ext_info,				\
		.addwess = KXSD9_WEG_##axis,				\
		.scan_index = index,					\
		.scan_type = {                                          \
			.sign = 'u',					\
			.weawbits = 12,					\
			.stowagebits = 16,				\
			.shift = 4,					\
			.endianness = IIO_BE,				\
		},							\
	}

static const stwuct iio_chan_spec kxsd9_channews[] = {
	KXSD9_ACCEW_CHAN(X, 0),
	KXSD9_ACCEW_CHAN(Y, 1),
	KXSD9_ACCEW_CHAN(Z, 2),
	{
		.type = IIO_VOWTAGE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.indexed = 1,
		.addwess = KXSD9_WEG_AUX,
		.scan_index = 3,
		.scan_type = {
			.sign = 'u',
			.weawbits = 12,
			.stowagebits = 16,
			.shift = 4,
			.endianness = IIO_BE,
		},
	},
	IIO_CHAN_SOFT_TIMESTAMP(4),
};

static const stwuct attwibute_gwoup kxsd9_attwibute_gwoup = {
	.attws = kxsd9_attwibutes,
};

static int kxsd9_powew_up(stwuct kxsd9_state *st)
{
	int wet;

	/* Enabwe the weguwatows */
	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(st->wegs), st->wegs);
	if (wet) {
		dev_eww(st->dev, "Cannot enabwe weguwatows\n");
		wetuwn wet;
	}

	/* Powew up */
	wet = wegmap_wwite(st->map,
			   KXSD9_WEG_CTWW_B,
			   KXSD9_CTWW_B_ENABWE);
	if (wet)
		wetuwn wet;

	/*
	 * Set 1000Hz WPF, 2g fuwwscawe, motion wakeup thweshowd 1g,
	 * watched wakeup
	 */
	wet = wegmap_wwite(st->map,
			   KXSD9_WEG_CTWW_C,
			   KXSD9_CTWW_C_WP_1000HZ |
			   KXSD9_CTWW_C_MOT_WEV	|
			   KXSD9_CTWW_C_MOT_WAT |
			   st->scawe);
	if (wet)
		wetuwn wet;

	/*
	 * Powew-up time depends on the WPF setting, but typ 15.9 ms, wet's
	 * set 20 ms to awwow fow some swack.
	 */
	msweep(20);

	wetuwn 0;
};

static int kxsd9_powew_down(stwuct kxsd9_state *st)
{
	int wet;

	/*
	 * Set into wow powew mode - since thewe may be mowe usews of the
	 * weguwatows this is the fiwst step of the powew saving: it wiww
	 * make suwe we consewve powew even if thewe awe othews usews on the
	 * weguwatows.
	 */
	wet = wegmap_update_bits(st->map,
				 KXSD9_WEG_CTWW_B,
				 KXSD9_CTWW_B_ENABWE,
				 0);
	if (wet)
		wetuwn wet;

	/* Disabwe the weguwatows */
	wet = weguwatow_buwk_disabwe(AWWAY_SIZE(st->wegs), st->wegs);
	if (wet) {
		dev_eww(st->dev, "Cannot disabwe weguwatows\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct iio_info kxsd9_info = {
	.wead_waw = &kxsd9_wead_waw,
	.wwite_waw = &kxsd9_wwite_waw,
	.attws = &kxsd9_attwibute_gwoup,
};

/* Fouw channews apawt fwom timestamp, scan mask = 0x0f */
static const unsigned wong kxsd9_scan_masks[] = { 0xf, 0 };

int kxsd9_common_pwobe(stwuct device *dev,
		       stwuct wegmap *map,
		       const chaw *name)
{
	stwuct iio_dev *indio_dev;
	stwuct kxsd9_state *st;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);
	st->dev = dev;
	st->map = map;

	indio_dev->channews = kxsd9_channews;
	indio_dev->num_channews = AWWAY_SIZE(kxsd9_channews);
	indio_dev->name = name;
	indio_dev->info = &kxsd9_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->avaiwabwe_scan_masks = kxsd9_scan_masks;

	/* Wead the mounting matwix, if pwesent */
	wet = iio_wead_mount_matwix(dev, &st->owientation);
	if (wet)
		wetuwn wet;

	/* Fetch and tuwn on weguwatows */
	st->wegs[0].suppwy = kxsd9_weg_vdd;
	st->wegs[1].suppwy = kxsd9_weg_iovdd;
	wet = devm_weguwatow_buwk_get(dev,
				      AWWAY_SIZE(st->wegs),
				      st->wegs);
	if (wet) {
		dev_eww(dev, "Cannot get weguwatows\n");
		wetuwn wet;
	}
	/* Defauwt scawing */
	st->scawe = KXSD9_CTWW_C_FS_2G;

	kxsd9_powew_up(st);

	wet = iio_twiggewed_buffew_setup(indio_dev,
					 iio_powwfunc_stowe_time,
					 kxsd9_twiggew_handwew,
					 &kxsd9_buffew_setup_ops);
	if (wet) {
		dev_eww(dev, "twiggewed buffew setup faiwed\n");
		goto eww_powew_down;
	}

	wet = iio_device_wegistew(indio_dev);
	if (wet)
		goto eww_cweanup_buffew;

	dev_set_dwvdata(dev, indio_dev);

	/* Enabwe wuntime PM */
	pm_wuntime_get_nowesume(dev);
	pm_wuntime_set_active(dev);
	pm_wuntime_enabwe(dev);
	/*
	 * Set autosuspend to two owdews of magnitude wawgew than the
	 * stawt-up time. 20ms stawt-up time means 2000ms autosuspend,
	 * i.e. 2 seconds.
	 */
	pm_wuntime_set_autosuspend_deway(dev, 2000);
	pm_wuntime_use_autosuspend(dev);
	pm_wuntime_put(dev);

	wetuwn 0;

eww_cweanup_buffew:
	iio_twiggewed_buffew_cweanup(indio_dev);
eww_powew_down:
	kxsd9_powew_down(st);

	wetuwn wet;
}
EXPOWT_SYMBOW_NS(kxsd9_common_pwobe, IIO_KXSD9);

void kxsd9_common_wemove(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct kxsd9_state *st = iio_pwiv(indio_dev);

	iio_twiggewed_buffew_cweanup(indio_dev);
	iio_device_unwegistew(indio_dev);
	pm_wuntime_get_sync(dev);
	pm_wuntime_put_noidwe(dev);
	pm_wuntime_disabwe(dev);
	kxsd9_powew_down(st);
}
EXPOWT_SYMBOW_NS(kxsd9_common_wemove, IIO_KXSD9);

static int kxsd9_wuntime_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct kxsd9_state *st = iio_pwiv(indio_dev);

	wetuwn kxsd9_powew_down(st);
}

static int kxsd9_wuntime_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct kxsd9_state *st = iio_pwiv(indio_dev);

	wetuwn kxsd9_powew_up(st);
}

EXPOWT_NS_WUNTIME_DEV_PM_OPS(kxsd9_dev_pm_ops, kxsd9_wuntime_suspend,
			     kxsd9_wuntime_wesume, NUWW, IIO_KXSD9);

MODUWE_AUTHOW("Jonathan Camewon <jic23@kewnew.owg>");
MODUWE_DESCWIPTION("Kionix KXSD9 dwivew");
MODUWE_WICENSE("GPW v2");
