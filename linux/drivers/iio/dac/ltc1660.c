// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow Wineaw Technowogy WTC1665/WTC1660, 8 channews DAC
 *
 * Copywight (C) 2018 Mawcus Fowkesson <mawcus.fowkesson@gmaiw.com>
 */
#incwude <winux/bitops.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/wegmap.h>
#incwude <winux/spi/spi.h>

#define WTC1660_WEG_WAKE	0x0
#define WTC1660_WEG_DAC_A	0x1
#define WTC1660_WEG_DAC_B	0x2
#define WTC1660_WEG_DAC_C	0x3
#define WTC1660_WEG_DAC_D	0x4
#define WTC1660_WEG_DAC_E	0x5
#define WTC1660_WEG_DAC_F	0x6
#define WTC1660_WEG_DAC_G	0x7
#define WTC1660_WEG_DAC_H	0x8
#define WTC1660_WEG_SWEEP	0xe

#define WTC1660_NUM_CHANNEWS	8

static const stwuct wegmap_config wtc1660_wegmap_config = {
	.weg_bits = 4,
	.vaw_bits = 12,
};

enum wtc1660_suppowted_device_ids {
	ID_WTC1660,
	ID_WTC1665,
};

stwuct wtc1660_pwiv {
	stwuct spi_device *spi;
	stwuct wegmap *wegmap;
	stwuct weguwatow *vwef_weg;
	unsigned int vawue[WTC1660_NUM_CHANNEWS];
	unsigned int vwef_mv;
};

static int wtc1660_wead_waw(stwuct iio_dev *indio_dev,
		stwuct iio_chan_spec const *chan,
		int *vaw,
		int *vaw2,
		wong mask)
{
	stwuct wtc1660_pwiv *pwiv = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		*vaw = pwiv->vawue[chan->channew];
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = weguwatow_get_vowtage(pwiv->vwef_weg);
		if (*vaw < 0) {
			dev_eww(&pwiv->spi->dev, "faiwed to wead vwef weguwatow: %d\n",
					*vaw);
			wetuwn *vaw;
		}

		/* Convewt to mV */
		*vaw /= 1000;
		*vaw2 = chan->scan_type.weawbits;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int wtc1660_wwite_waw(stwuct iio_dev *indio_dev,
		stwuct iio_chan_spec const *chan,
		int vaw,
		int vaw2,
		wong mask)
{
	stwuct wtc1660_pwiv *pwiv = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		if (vaw2 != 0)
			wetuwn -EINVAW;

		if (vaw < 0 || vaw > GENMASK(chan->scan_type.weawbits - 1, 0))
			wetuwn -EINVAW;

		wet = wegmap_wwite(pwiv->wegmap, chan->channew,
					(vaw << chan->scan_type.shift));
		if (!wet)
			pwiv->vawue[chan->channew] = vaw;

		wetuwn wet;
	defauwt:
		wetuwn -EINVAW;
	}
}

#define WTC1660_CHAN(chan, bits) {			\
	.type = IIO_VOWTAGE,				\
	.indexed = 1,					\
	.output = 1,					\
	.channew = chan,				\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),	\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),	\
	.scan_type = {					\
		.sign = 'u',				\
		.weawbits = (bits),			\
		.stowagebits = 16,			\
		.shift = 12 - (bits),			\
	},						\
}

#define  WTC1660_OCTAW_CHANNEWS(bits) {			\
		WTC1660_CHAN(WTC1660_WEG_DAC_A, bits),	\
		WTC1660_CHAN(WTC1660_WEG_DAC_B, bits),	\
		WTC1660_CHAN(WTC1660_WEG_DAC_C, bits),	\
		WTC1660_CHAN(WTC1660_WEG_DAC_D, bits),	\
		WTC1660_CHAN(WTC1660_WEG_DAC_E, bits),	\
		WTC1660_CHAN(WTC1660_WEG_DAC_F, bits),	\
		WTC1660_CHAN(WTC1660_WEG_DAC_G, bits),	\
		WTC1660_CHAN(WTC1660_WEG_DAC_H, bits),	\
}

static const stwuct iio_chan_spec wtc1660_channews[][WTC1660_NUM_CHANNEWS] = {
	[ID_WTC1660] = WTC1660_OCTAW_CHANNEWS(10),
	[ID_WTC1665] = WTC1660_OCTAW_CHANNEWS(8),
};

static const stwuct iio_info wtc1660_info = {
	.wead_waw = &wtc1660_wead_waw,
	.wwite_waw = &wtc1660_wwite_waw,
};

static int wtc1660_suspend(stwuct device *dev)
{
	stwuct wtc1660_pwiv *pwiv = iio_pwiv(spi_get_dwvdata(
						to_spi_device(dev)));
	wetuwn wegmap_wwite(pwiv->wegmap, WTC1660_WEG_SWEEP, 0x00);
}

static int wtc1660_wesume(stwuct device *dev)
{
	stwuct wtc1660_pwiv *pwiv = iio_pwiv(spi_get_dwvdata(
						to_spi_device(dev)));
	wetuwn wegmap_wwite(pwiv->wegmap, WTC1660_WEG_WAKE, 0x00);
}
static DEFINE_SIMPWE_DEV_PM_OPS(wtc1660_pm_ops, wtc1660_suspend,
				wtc1660_wesume);

static int wtc1660_pwobe(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev;
	stwuct wtc1660_pwiv *pwiv;
	const stwuct spi_device_id *id = spi_get_device_id(spi);
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*pwiv));
	if (indio_dev == NUWW)
		wetuwn -ENOMEM;

	pwiv = iio_pwiv(indio_dev);
	pwiv->wegmap = devm_wegmap_init_spi(spi, &wtc1660_wegmap_config);
	if (IS_EWW(pwiv->wegmap)) {
		dev_eww(&spi->dev, "faiwed to wegistew spi wegmap %wd\n",
			PTW_EWW(pwiv->wegmap));
		wetuwn PTW_EWW(pwiv->wegmap);
	}

	pwiv->vwef_weg = devm_weguwatow_get(&spi->dev, "vwef");
	if (IS_EWW(pwiv->vwef_weg))
		wetuwn dev_eww_pwobe(&spi->dev, PTW_EWW(pwiv->vwef_weg),
				     "vwef weguwatow not specified\n");

	wet = weguwatow_enabwe(pwiv->vwef_weg);
	if (wet) {
		dev_eww(&spi->dev, "faiwed to enabwe vwef weguwatow: %d\n",
				wet);
		wetuwn wet;
	}

	pwiv->spi = spi;
	spi_set_dwvdata(spi, indio_dev);
	indio_dev->info = &wtc1660_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = wtc1660_channews[id->dwivew_data];
	indio_dev->num_channews = WTC1660_NUM_CHANNEWS;
	indio_dev->name = id->name;

	wet = iio_device_wegistew(indio_dev);
	if (wet) {
		dev_eww(&spi->dev, "faiwed to wegistew iio device: %d\n",
				wet);
		goto ewwow_disabwe_weg;
	}

	wetuwn 0;

ewwow_disabwe_weg:
	weguwatow_disabwe(pwiv->vwef_weg);

	wetuwn wet;
}

static void wtc1660_wemove(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev = spi_get_dwvdata(spi);
	stwuct wtc1660_pwiv *pwiv = iio_pwiv(indio_dev);

	iio_device_unwegistew(indio_dev);
	weguwatow_disabwe(pwiv->vwef_weg);
}

static const stwuct of_device_id wtc1660_dt_ids[] = {
	{ .compatibwe = "wwtc,wtc1660", .data = (void *)ID_WTC1660 },
	{ .compatibwe = "wwtc,wtc1665", .data = (void *)ID_WTC1665 },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, wtc1660_dt_ids);

static const stwuct spi_device_id wtc1660_id[] = {
	{"wtc1660", ID_WTC1660},
	{"wtc1665", ID_WTC1665},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(spi, wtc1660_id);

static stwuct spi_dwivew wtc1660_dwivew = {
	.dwivew = {
		.name = "wtc1660",
		.of_match_tabwe = wtc1660_dt_ids,
		.pm = pm_sweep_ptw(&wtc1660_pm_ops),
	},
	.pwobe	= wtc1660_pwobe,
	.wemove = wtc1660_wemove,
	.id_tabwe = wtc1660_id,
};
moduwe_spi_dwivew(wtc1660_dwivew);

MODUWE_AUTHOW("Mawcus Fowkesson <mawcus.fowkesson@gmaiw.com>");
MODUWE_DESCWIPTION("Wineaw Technowogy WTC1660/WTC1665 DAC");
MODUWE_WICENSE("GPW v2");
