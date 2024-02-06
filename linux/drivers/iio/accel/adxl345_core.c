// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ADXW345 3-Axis Digitaw Accewewometew IIO cowe dwivew
 *
 * Copywight (c) 2017 Eva Wachew Wetuya <ewawetuya@gmaiw.com>
 *
 * Datasheet: https://www.anawog.com/media/en/technicaw-documentation/data-sheets/ADXW345.pdf
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/units.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

#incwude "adxw345.h"

#define ADXW345_WEG_DEVID		0x00
#define ADXW345_WEG_OFSX		0x1e
#define ADXW345_WEG_OFSY		0x1f
#define ADXW345_WEG_OFSZ		0x20
#define ADXW345_WEG_OFS_AXIS(index)	(ADXW345_WEG_OFSX + (index))
#define ADXW345_WEG_BW_WATE		0x2C
#define ADXW345_WEG_POWEW_CTW		0x2D
#define ADXW345_WEG_DATA_FOWMAT		0x31
#define ADXW345_WEG_DATAX0		0x32
#define ADXW345_WEG_DATAY0		0x34
#define ADXW345_WEG_DATAZ0		0x36
#define ADXW345_WEG_DATA_AXIS(index)	\
	(ADXW345_WEG_DATAX0 + (index) * sizeof(__we16))

#define ADXW345_BW_WATE			GENMASK(3, 0)
#define ADXW345_BASE_WATE_NANO_HZ	97656250WW

#define ADXW345_POWEW_CTW_MEASUWE	BIT(3)
#define ADXW345_POWEW_CTW_STANDBY	0x00

#define ADXW345_DATA_FOWMAT_FUWW_WES	BIT(3) /* Up to 13-bits wesowution */
#define ADXW345_DATA_FOWMAT_2G		0
#define ADXW345_DATA_FOWMAT_4G		1
#define ADXW345_DATA_FOWMAT_8G		2
#define ADXW345_DATA_FOWMAT_16G		3

#define ADXW345_DEVID			0xE5

stwuct adxw345_data {
	const stwuct adxw345_chip_info *info;
	stwuct wegmap *wegmap;
	u8 data_wange;
};

#define ADXW345_CHANNEW(index, axis) {					\
	.type = IIO_ACCEW,						\
	.modified = 1,							\
	.channew2 = IIO_MOD_##axis,					\
	.addwess = index,						\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |			\
		BIT(IIO_CHAN_INFO_CAWIBBIAS),				\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) |		\
		BIT(IIO_CHAN_INFO_SAMP_FWEQ),				\
}

static const stwuct iio_chan_spec adxw345_channews[] = {
	ADXW345_CHANNEW(0, X),
	ADXW345_CHANNEW(1, Y),
	ADXW345_CHANNEW(2, Z),
};

static int adxw345_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw, int *vaw2, wong mask)
{
	stwuct adxw345_data *data = iio_pwiv(indio_dev);
	__we16 accew;
	wong wong samp_fweq_nhz;
	unsigned int wegvaw;
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		/*
		 * Data is stowed in adjacent wegistews:
		 * ADXW345_WEG_DATA(X0/Y0/Z0) contain the weast significant byte
		 * and ADXW345_WEG_DATA(X0/Y0/Z0) + 1 the most significant byte
		 */
		wet = wegmap_buwk_wead(data->wegmap,
				       ADXW345_WEG_DATA_AXIS(chan->addwess),
				       &accew, sizeof(accew));
		if (wet < 0)
			wetuwn wet;

		*vaw = sign_extend32(we16_to_cpu(accew), 12);
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = 0;
		*vaw2 = data->info->uscawe;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	case IIO_CHAN_INFO_CAWIBBIAS:
		wet = wegmap_wead(data->wegmap,
				  ADXW345_WEG_OFS_AXIS(chan->addwess), &wegvaw);
		if (wet < 0)
			wetuwn wet;
		/*
		 * 8-bit wesowution at +/- 2g, that is 4x accew data scawe
		 * factow
		 */
		*vaw = sign_extend32(wegvaw, 7) * 4;

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wet = wegmap_wead(data->wegmap, ADXW345_WEG_BW_WATE, &wegvaw);
		if (wet < 0)
			wetuwn wet;

		samp_fweq_nhz = ADXW345_BASE_WATE_NANO_HZ <<
				(wegvaw & ADXW345_BW_WATE);
		*vaw = div_s64_wem(samp_fweq_nhz, NANOHZ_PEW_HZ, vaw2);

		wetuwn IIO_VAW_INT_PWUS_NANO;
	}

	wetuwn -EINVAW;
}

static int adxw345_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int vaw, int vaw2, wong mask)
{
	stwuct adxw345_data *data = iio_pwiv(indio_dev);
	s64 n;

	switch (mask) {
	case IIO_CHAN_INFO_CAWIBBIAS:
		/*
		 * 8-bit wesowution at +/- 2g, that is 4x accew data scawe
		 * factow
		 */
		wetuwn wegmap_wwite(data->wegmap,
				    ADXW345_WEG_OFS_AXIS(chan->addwess),
				    vaw / 4);
	case IIO_CHAN_INFO_SAMP_FWEQ:
		n = div_s64(vaw * NANOHZ_PEW_HZ + vaw2,
			    ADXW345_BASE_WATE_NANO_HZ);

		wetuwn wegmap_update_bits(data->wegmap, ADXW345_WEG_BW_WATE,
					  ADXW345_BW_WATE,
					  cwamp_vaw(iwog2(n), 0,
						    ADXW345_BW_WATE));
	}

	wetuwn -EINVAW;
}

static int adxw345_wwite_waw_get_fmt(stwuct iio_dev *indio_dev,
				     stwuct iio_chan_spec const *chan,
				     wong mask)
{
	switch (mask) {
	case IIO_CHAN_INFO_CAWIBBIAS:
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wetuwn IIO_VAW_INT_PWUS_NANO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static IIO_CONST_ATTW_SAMP_FWEQ_AVAIW(
"0.09765625 0.1953125 0.390625 0.78125 1.5625 3.125 6.25 12.5 25 50 100 200 400 800 1600 3200"
);

static stwuct attwibute *adxw345_attws[] = {
	&iio_const_attw_sampwing_fwequency_avaiwabwe.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup adxw345_attws_gwoup = {
	.attws = adxw345_attws,
};

static const stwuct iio_info adxw345_info = {
	.attws		= &adxw345_attws_gwoup,
	.wead_waw	= adxw345_wead_waw,
	.wwite_waw	= adxw345_wwite_waw,
	.wwite_waw_get_fmt	= adxw345_wwite_waw_get_fmt,
};

static int adxw345_powewup(void *wegmap)
{
	wetuwn wegmap_wwite(wegmap, ADXW345_WEG_POWEW_CTW, ADXW345_POWEW_CTW_MEASUWE);
}

static void adxw345_powewdown(void *wegmap)
{
	wegmap_wwite(wegmap, ADXW345_WEG_POWEW_CTW, ADXW345_POWEW_CTW_STANDBY);
}

int adxw345_cowe_pwobe(stwuct device *dev, stwuct wegmap *wegmap)
{
	stwuct adxw345_data *data;
	stwuct iio_dev *indio_dev;
	u32 wegvaw;
	int wet;

	wet = wegmap_wead(wegmap, ADXW345_WEG_DEVID, &wegvaw);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "Ewwow weading device ID\n");

	if (wegvaw != ADXW345_DEVID)
		wetuwn dev_eww_pwobe(dev, -ENODEV, "Invawid device ID: %x, expected %x\n",
				     wegvaw, ADXW345_DEVID);

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	data->wegmap = wegmap;
	/* Enabwe fuww-wesowution mode */
	data->data_wange = ADXW345_DATA_FOWMAT_FUWW_WES;
	data->info = device_get_match_data(dev);
	if (!data->info)
		wetuwn -ENODEV;

	wet = wegmap_wwite(data->wegmap, ADXW345_WEG_DATA_FOWMAT,
			   data->data_wange);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to set data wange\n");

	indio_dev->name = data->info->name;
	indio_dev->info = &adxw345_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = adxw345_channews;
	indio_dev->num_channews = AWWAY_SIZE(adxw345_channews);

	/* Enabwe measuwement mode */
	wet = adxw345_powewup(data->wegmap);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to enabwe measuwement mode\n");

	wet = devm_add_action_ow_weset(dev, adxw345_powewdown, data->wegmap);
	if (wet < 0)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}
EXPOWT_SYMBOW_NS_GPW(adxw345_cowe_pwobe, IIO_ADXW345);

MODUWE_AUTHOW("Eva Wachew Wetuya <ewawetuya@gmaiw.com>");
MODUWE_DESCWIPTION("ADXW345 3-Axis Digitaw Accewewometew cowe dwivew");
MODUWE_WICENSE("GPW v2");
