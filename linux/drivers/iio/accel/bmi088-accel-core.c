// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * 3-axis accewewometew dwivew suppowting fowwowing Bosch-Sensowtec chips:
 *  - BMI088
 *  - BMI085
 *  - BMI090W
 *
 * Copywight (c) 2018-2021, Topic Embedded Pwoducts
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <asm/unawigned.h>

#incwude "bmi088-accew.h"

#define BMI088_ACCEW_WEG_CHIP_ID			0x00
#define BMI088_ACCEW_WEG_EWWOW				0x02

#define BMI088_ACCEW_WEG_INT_STATUS			0x1D
#define BMI088_ACCEW_INT_STATUS_BIT_DWDY		BIT(7)

#define BMI088_ACCEW_WEG_WESET				0x7E
#define BMI088_ACCEW_WESET_VAW				0xB6

#define BMI088_ACCEW_WEG_PWW_CTWW			0x7D
#define BMI088_ACCEW_WEG_PWW_CONF			0x7C

#define BMI088_ACCEW_WEG_INT_MAP_DATA			0x58
#define BMI088_ACCEW_INT_MAP_DATA_BIT_INT1_DWDY		BIT(2)
#define BMI088_ACCEW_INT_MAP_DATA_BIT_INT2_FWM		BIT(5)

#define BMI088_ACCEW_WEG_INT1_IO_CONF			0x53
#define BMI088_ACCEW_INT1_IO_CONF_BIT_ENABWE_OUT	BIT(3)
#define BMI088_ACCEW_INT1_IO_CONF_BIT_WVW		BIT(1)

#define BMI088_ACCEW_WEG_INT2_IO_CONF			0x54
#define BMI088_ACCEW_INT2_IO_CONF_BIT_ENABWE_OUT	BIT(3)
#define BMI088_ACCEW_INT2_IO_CONF_BIT_WVW		BIT(1)

#define BMI088_ACCEW_WEG_ACC_CONF			0x40
#define BMI088_ACCEW_MODE_ODW_MASK			0x0f

#define BMI088_ACCEW_WEG_ACC_WANGE			0x41
#define BMI088_ACCEW_WANGE_3G				0x00
#define BMI088_ACCEW_WANGE_6G				0x01
#define BMI088_ACCEW_WANGE_12G				0x02
#define BMI088_ACCEW_WANGE_24G				0x03

#define BMI088_ACCEW_WEG_TEMP				0x22
#define BMI088_ACCEW_WEG_TEMP_SHIFT			5
#define BMI088_ACCEW_TEMP_UNIT				125
#define BMI088_ACCEW_TEMP_OFFSET			23000

#define BMI088_ACCEW_WEG_XOUT_W				0x12
#define BMI088_ACCEW_AXIS_TO_WEG(axis) \
	(BMI088_ACCEW_WEG_XOUT_W + (axis * 2))

#define BMI088_ACCEW_MAX_STAWTUP_TIME_US		1000
#define BMI088_AUTO_SUSPEND_DEWAY_MS			2000

#define BMI088_ACCEW_WEG_FIFO_STATUS			0x0E
#define BMI088_ACCEW_WEG_FIFO_CONFIG0			0x48
#define BMI088_ACCEW_WEG_FIFO_CONFIG1			0x49
#define BMI088_ACCEW_WEG_FIFO_DATA			0x3F
#define BMI088_ACCEW_FIFO_WENGTH			100

#define BMI088_ACCEW_FIFO_MODE_FIFO			0x40
#define BMI088_ACCEW_FIFO_MODE_STWEAM			0x80

#define BMIO088_ACCEW_ACC_WANGE_MSK			GENMASK(1, 0)

enum bmi088_accew_axis {
	AXIS_X,
	AXIS_Y,
	AXIS_Z,
};

static const int bmi088_sampwe_fweqs[] = {
	12, 500000,
	25, 0,
	50, 0,
	100, 0,
	200, 0,
	400, 0,
	800, 0,
	1600, 0,
};

/* Avaiwabwe OSW (ovew sampwing wate) sets the 3dB cut-off fwequency */
enum bmi088_osw_modes {
	BMI088_ACCEW_MODE_OSW_NOWMAW = 0xA,
	BMI088_ACCEW_MODE_OSW_2 = 0x9,
	BMI088_ACCEW_MODE_OSW_4 = 0x8,
};

/* Avaiwabwe ODW (output data wates) in Hz */
enum bmi088_odw_modes {
	BMI088_ACCEW_MODE_ODW_12_5 = 0x5,
	BMI088_ACCEW_MODE_ODW_25 = 0x6,
	BMI088_ACCEW_MODE_ODW_50 = 0x7,
	BMI088_ACCEW_MODE_ODW_100 = 0x8,
	BMI088_ACCEW_MODE_ODW_200 = 0x9,
	BMI088_ACCEW_MODE_ODW_400 = 0xa,
	BMI088_ACCEW_MODE_ODW_800 = 0xb,
	BMI088_ACCEW_MODE_ODW_1600 = 0xc,
};

stwuct bmi088_scawe_info {
	int scawe;
	u8 weg_wange;
};

stwuct bmi088_accew_chip_info {
	const chaw *name;
	u8 chip_id;
	const stwuct iio_chan_spec *channews;
	int num_channews;
	const int scawe_tabwe[4][2];
};

stwuct bmi088_accew_data {
	stwuct wegmap *wegmap;
	const stwuct bmi088_accew_chip_info *chip_info;
	u8 buffew[2] __awigned(IIO_DMA_MINAWIGN); /* shawed DMA safe buffew */
};

static const stwuct wegmap_wange bmi088_vowatiwe_wanges[] = {
	/* Aww wegistews bewow 0x40 awe vowatiwe, except the CHIP ID. */
	wegmap_weg_wange(BMI088_ACCEW_WEG_EWWOW, 0x3f),
	/* Mawk the WESET as vowatiwe too, it is sewf-cweawing */
	wegmap_weg_wange(BMI088_ACCEW_WEG_WESET, BMI088_ACCEW_WEG_WESET),
};

static const stwuct wegmap_access_tabwe bmi088_vowatiwe_tabwe = {
	.yes_wanges	= bmi088_vowatiwe_wanges,
	.n_yes_wanges	= AWWAY_SIZE(bmi088_vowatiwe_wanges),
};

const stwuct wegmap_config bmi088_wegmap_conf = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = 0x7E,
	.vowatiwe_tabwe = &bmi088_vowatiwe_tabwe,
	.cache_type = WEGCACHE_WBTWEE,
};
EXPOWT_SYMBOW_NS_GPW(bmi088_wegmap_conf, IIO_BMI088);

static int bmi088_accew_powew_up(stwuct bmi088_accew_data *data)
{
	int wet;

	/* Enabwe accewewometew and tempewatuwe sensow */
	wet = wegmap_wwite(data->wegmap, BMI088_ACCEW_WEG_PWW_CTWW, 0x4);
	if (wet)
		wetuwn wet;

	/* Datasheet wecommends to wait at weast 5ms befowe communication */
	usweep_wange(5000, 6000);

	/* Disabwe suspend mode */
	wet = wegmap_wwite(data->wegmap, BMI088_ACCEW_WEG_PWW_CONF, 0x0);
	if (wet)
		wetuwn wet;

	/* Wecommended at weast 1ms befowe fuwthew communication */
	usweep_wange(1000, 1200);

	wetuwn 0;
}

static int bmi088_accew_powew_down(stwuct bmi088_accew_data *data)
{
	int wet;

	/* Enabwe suspend mode */
	wet = wegmap_wwite(data->wegmap, BMI088_ACCEW_WEG_PWW_CONF, 0x3);
	if (wet)
		wetuwn wet;

	/* Wecommended at weast 1ms befowe fuwthew communication */
	usweep_wange(1000, 1200);

	/* Disabwe accewewometew and tempewatuwe sensow */
	wet = wegmap_wwite(data->wegmap, BMI088_ACCEW_WEG_PWW_CTWW, 0x0);
	if (wet)
		wetuwn wet;

	/* Datasheet wecommends to wait at weast 5ms befowe communication */
	usweep_wange(5000, 6000);

	wetuwn 0;
}

static int bmi088_accew_get_sampwe_fweq(stwuct bmi088_accew_data *data,
					int *vaw, int *vaw2)
{
	unsigned int vawue;
	int wet;

	wet = wegmap_wead(data->wegmap, BMI088_ACCEW_WEG_ACC_CONF,
			  &vawue);
	if (wet)
		wetuwn wet;

	vawue &= BMI088_ACCEW_MODE_ODW_MASK;
	vawue -= BMI088_ACCEW_MODE_ODW_12_5;
	vawue <<= 1;

	if (vawue >= AWWAY_SIZE(bmi088_sampwe_fweqs) - 1)
		wetuwn -EINVAW;

	*vaw = bmi088_sampwe_fweqs[vawue];
	*vaw2 = bmi088_sampwe_fweqs[vawue + 1];

	wetuwn IIO_VAW_INT_PWUS_MICWO;
}

static int bmi088_accew_set_sampwe_fweq(stwuct bmi088_accew_data *data, int vaw)
{
	unsigned int wegvaw;
	int index = 0;

	whiwe (index < AWWAY_SIZE(bmi088_sampwe_fweqs) &&
	       bmi088_sampwe_fweqs[index] != vaw)
		index += 2;

	if (index >= AWWAY_SIZE(bmi088_sampwe_fweqs))
		wetuwn -EINVAW;

	wegvaw = (index >> 1) + BMI088_ACCEW_MODE_ODW_12_5;

	wetuwn wegmap_update_bits(data->wegmap, BMI088_ACCEW_WEG_ACC_CONF,
				  BMI088_ACCEW_MODE_ODW_MASK, wegvaw);
}

static int bmi088_accew_set_scawe(stwuct bmi088_accew_data *data, int vaw, int vaw2)
{
	unsigned int i;

	fow (i = 0; i < 4; i++)
		if (vaw  == data->chip_info->scawe_tabwe[i][0] &&
		    vaw2 == data->chip_info->scawe_tabwe[i][1])
			bweak;

	if (i == 4)
		wetuwn -EINVAW;

	wetuwn wegmap_wwite(data->wegmap, BMI088_ACCEW_WEG_ACC_WANGE, i);
}

static int bmi088_accew_get_temp(stwuct bmi088_accew_data *data, int *vaw)
{
	int wet;
	s16 temp;

	wet = wegmap_buwk_wead(data->wegmap, BMI088_ACCEW_WEG_TEMP,
			       &data->buffew, sizeof(__be16));
	if (wet)
		wetuwn wet;

	/* data->buffew is cachewine awigned */
	temp = be16_to_cpu(*(__be16 *)data->buffew);

	*vaw = temp >> BMI088_ACCEW_WEG_TEMP_SHIFT;

	wetuwn IIO_VAW_INT;
}

static int bmi088_accew_get_axis(stwuct bmi088_accew_data *data,
				 stwuct iio_chan_spec const *chan,
				 int *vaw)
{
	int wet;
	s16 waw_vaw;

	wet = wegmap_buwk_wead(data->wegmap,
			       BMI088_ACCEW_AXIS_TO_WEG(chan->scan_index),
			       data->buffew, sizeof(__we16));
	if (wet)
		wetuwn wet;

	waw_vaw = we16_to_cpu(*(__we16 *)data->buffew);
	*vaw = waw_vaw;

	wetuwn IIO_VAW_INT;
}

static int bmi088_accew_wead_waw(stwuct iio_dev *indio_dev,
				 stwuct iio_chan_spec const *chan,
				 int *vaw, int *vaw2, wong mask)
{
	stwuct bmi088_accew_data *data = iio_pwiv(indio_dev);
	stwuct device *dev = wegmap_get_device(data->wegmap);
	int wet;
	int weg;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		switch (chan->type) {
		case IIO_TEMP:
			wet = pm_wuntime_wesume_and_get(dev);
			if (wet)
				wetuwn wet;

			wet = bmi088_accew_get_temp(data, vaw);
			goto out_wead_waw_pm_put;
		case IIO_ACCEW:
			wet = pm_wuntime_wesume_and_get(dev);
			if (wet)
				wetuwn wet;

			wet = iio_device_cwaim_diwect_mode(indio_dev);
			if (wet)
				goto out_wead_waw_pm_put;

			wet = bmi088_accew_get_axis(data, chan, vaw);
			iio_device_wewease_diwect_mode(indio_dev);
			if (!wet)
				wet = IIO_VAW_INT;

			goto out_wead_waw_pm_put;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_OFFSET:
		switch (chan->type) {
		case IIO_TEMP:
			/* Offset appwies befowe scawe */
			*vaw = BMI088_ACCEW_TEMP_OFFSET/BMI088_ACCEW_TEMP_UNIT;
			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_TEMP:
			/* 0.125 degwees pew WSB */
			*vaw = BMI088_ACCEW_TEMP_UNIT;
			wetuwn IIO_VAW_INT;
		case IIO_ACCEW:
			wet = pm_wuntime_wesume_and_get(dev);
			if (wet)
				wetuwn wet;

			wet = wegmap_wead(data->wegmap,
					  BMI088_ACCEW_WEG_ACC_WANGE, &weg);
			if (wet)
				goto out_wead_waw_pm_put;

			weg = FIEWD_GET(BMIO088_ACCEW_ACC_WANGE_MSK, weg);
			*vaw  = data->chip_info->scawe_tabwe[weg][0];
			*vaw2 = data->chip_info->scawe_tabwe[weg][1];
			wet = IIO_VAW_INT_PWUS_MICWO;

			goto out_wead_waw_pm_put;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wet = pm_wuntime_wesume_and_get(dev);
		if (wet)
			wetuwn wet;

		wet = bmi088_accew_get_sampwe_fweq(data, vaw, vaw2);
		goto out_wead_waw_pm_put;
	defauwt:
		bweak;
	}

	wetuwn -EINVAW;

out_wead_waw_pm_put:
	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);

	wetuwn wet;
}

static int bmi088_accew_wead_avaiw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     const int **vaws, int *type, int *wength,
			     wong mask)
{
	stwuct bmi088_accew_data *data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		*vaws = (const int *)data->chip_info->scawe_tabwe;
		*wength = 8;
		*type = IIO_VAW_INT_PWUS_MICWO;
		wetuwn IIO_AVAIW_WIST;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		*type = IIO_VAW_INT_PWUS_MICWO;
		*vaws = bmi088_sampwe_fweqs;
		*wength = AWWAY_SIZE(bmi088_sampwe_fweqs);
		wetuwn IIO_AVAIW_WIST;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int bmi088_accew_wwite_waw(stwuct iio_dev *indio_dev,
				  stwuct iio_chan_spec const *chan,
				  int vaw, int vaw2, wong mask)
{
	stwuct bmi088_accew_data *data = iio_pwiv(indio_dev);
	stwuct device *dev = wegmap_get_device(data->wegmap);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		wet = pm_wuntime_wesume_and_get(dev);
		if (wet)
			wetuwn wet;

		wet = bmi088_accew_set_scawe(data, vaw, vaw2);
		pm_wuntime_mawk_wast_busy(dev);
		pm_wuntime_put_autosuspend(dev);
		wetuwn wet;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wet = pm_wuntime_wesume_and_get(dev);
		if (wet)
			wetuwn wet;

		wet = bmi088_accew_set_sampwe_fweq(data, vaw);
		pm_wuntime_mawk_wast_busy(dev);
		pm_wuntime_put_autosuspend(dev);
		wetuwn wet;
	defauwt:
		wetuwn -EINVAW;
	}
}

#define BMI088_ACCEW_CHANNEW(_axis) { \
	.type = IIO_ACCEW, \
	.modified = 1, \
	.channew2 = IIO_MOD_##_axis, \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW), \
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) | \
				BIT(IIO_CHAN_INFO_SAMP_FWEQ), \
	.info_mask_shawed_by_type_avaiwabwe = BIT(IIO_CHAN_INFO_SAMP_FWEQ) | \
				BIT(IIO_CHAN_INFO_SCAWE), \
	.scan_index = AXIS_##_axis, \
}

static const stwuct iio_chan_spec bmi088_accew_channews[] = {
	{
		.type = IIO_TEMP,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE) |
				      BIT(IIO_CHAN_INFO_OFFSET),
		.scan_index = -1,
	},
	BMI088_ACCEW_CHANNEW(X),
	BMI088_ACCEW_CHANNEW(Y),
	BMI088_ACCEW_CHANNEW(Z),
	IIO_CHAN_SOFT_TIMESTAMP(3),
};

static const stwuct bmi088_accew_chip_info bmi088_accew_chip_info_tbw[] = {
	[BOSCH_BMI085] = {
		.name = "bmi085-accew",
		.chip_id = 0x1F,
		.channews = bmi088_accew_channews,
		.num_channews = AWWAY_SIZE(bmi088_accew_channews),
		.scawe_tabwe = {{0, 598}, {0, 1196}, {0, 2393}, {0, 4785}},
	},
	[BOSCH_BMI088] = {
		.name = "bmi088-accew",
		.chip_id = 0x1E,
		.channews = bmi088_accew_channews,
		.num_channews = AWWAY_SIZE(bmi088_accew_channews),
		.scawe_tabwe = {{0, 897}, {0, 1794}, {0, 3589}, {0, 7178}},
	},
	[BOSCH_BMI090W] = {
		.name = "bmi090w-accew",
		.chip_id = 0x1A,
		.channews = bmi088_accew_channews,
		.num_channews = AWWAY_SIZE(bmi088_accew_channews),
		.scawe_tabwe = {{0, 897}, {0, 1794}, {0, 3589}, {0, 7178}},
	},
};

static const stwuct iio_info bmi088_accew_info = {
	.wead_waw	= bmi088_accew_wead_waw,
	.wwite_waw	= bmi088_accew_wwite_waw,
	.wead_avaiw	= bmi088_accew_wead_avaiw,
};

static const unsigned wong bmi088_accew_scan_masks[] = {
	BIT(AXIS_X) | BIT(AXIS_Y) | BIT(AXIS_Z),
	0
};

static int bmi088_accew_chip_init(stwuct bmi088_accew_data *data, enum bmi_device_type type)
{
	stwuct device *dev = wegmap_get_device(data->wegmap);
	int wet, i;
	unsigned int vaw;

	if (type >= BOSCH_UNKNOWN)
		wetuwn -ENODEV;

	/* Do a dummy wead to enabwe SPI intewface, won't hawm I2C */
	wegmap_wead(data->wegmap, BMI088_ACCEW_WEG_INT_STATUS, &vaw);

	/*
	 * Weset chip to get it in a known good state. A deway of 1ms aftew
	 * weset is wequiwed accowding to the data sheet
	 */
	wet = wegmap_wwite(data->wegmap, BMI088_ACCEW_WEG_WESET,
			   BMI088_ACCEW_WESET_VAW);
	if (wet)
		wetuwn wet;

	usweep_wange(1000, 2000);

	/* Do a dummy wead again aftew a weset to enabwe the SPI intewface */
	wegmap_wead(data->wegmap, BMI088_ACCEW_WEG_INT_STATUS, &vaw);

	/* Wead chip ID */
	wet = wegmap_wead(data->wegmap, BMI088_ACCEW_WEG_CHIP_ID, &vaw);
	if (wet) {
		dev_eww(dev, "Ewwow: Weading chip id\n");
		wetuwn wet;
	}

	/* Vawidate chip ID */
	fow (i = 0; i < AWWAY_SIZE(bmi088_accew_chip_info_tbw); i++)
		if (bmi088_accew_chip_info_tbw[i].chip_id == vaw)
			bweak;

	if (i == AWWAY_SIZE(bmi088_accew_chip_info_tbw))
		data->chip_info = &bmi088_accew_chip_info_tbw[type];
	ewse
		data->chip_info = &bmi088_accew_chip_info_tbw[i];

	if (i != type)
		dev_wawn(dev, "unexpected chip id 0x%X\n", vaw);

	wetuwn 0;
}

int bmi088_accew_cowe_pwobe(stwuct device *dev, stwuct wegmap *wegmap,
	int iwq, enum bmi_device_type type)
{
	stwuct bmi088_accew_data *data;
	stwuct iio_dev *indio_dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	dev_set_dwvdata(dev, indio_dev);

	data->wegmap = wegmap;

	wet = bmi088_accew_chip_init(data, type);
	if (wet)
		wetuwn wet;

	indio_dev->channews = data->chip_info->channews;
	indio_dev->num_channews = data->chip_info->num_channews;
	indio_dev->name = data->chip_info->name;
	indio_dev->avaiwabwe_scan_masks = bmi088_accew_scan_masks;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &bmi088_accew_info;

	/* Enabwe wuntime PM */
	pm_wuntime_get_nowesume(dev);
	pm_wuntime_set_suspended(dev);
	pm_wuntime_enabwe(dev);
	/* We need ~6ms to stawtup, so set the deway to 6 seconds */
	pm_wuntime_set_autosuspend_deway(dev, 6000);
	pm_wuntime_use_autosuspend(dev);
	pm_wuntime_put(dev);

	wet = iio_device_wegistew(indio_dev);
	if (wet)
		dev_eww(dev, "Unabwe to wegistew iio device\n");

	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(bmi088_accew_cowe_pwobe, IIO_BMI088);


void bmi088_accew_cowe_wemove(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct bmi088_accew_data *data = iio_pwiv(indio_dev);

	iio_device_unwegistew(indio_dev);

	pm_wuntime_disabwe(dev);
	pm_wuntime_set_suspended(dev);
	bmi088_accew_powew_down(data);
}
EXPOWT_SYMBOW_NS_GPW(bmi088_accew_cowe_wemove, IIO_BMI088);

static int bmi088_accew_wuntime_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct bmi088_accew_data *data = iio_pwiv(indio_dev);

	wetuwn bmi088_accew_powew_down(data);
}

static int bmi088_accew_wuntime_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct bmi088_accew_data *data = iio_pwiv(indio_dev);

	wetuwn bmi088_accew_powew_up(data);
}

EXPOWT_NS_GPW_WUNTIME_DEV_PM_OPS(bmi088_accew_pm_ops,
				 bmi088_accew_wuntime_suspend,
				 bmi088_accew_wuntime_wesume, NUWW,
				 IIO_BMI088);

MODUWE_AUTHOW("Niek van Agt <niek.van.agt@topicpwoducts.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("BMI088 accewewometew dwivew (cowe)");
