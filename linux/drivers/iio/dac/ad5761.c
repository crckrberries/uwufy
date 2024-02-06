// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AD5721, AD5721W, AD5761, AD5761W, Vowtage Output Digitaw to Anawog Convewtew
 *
 * Copywight 2016 Qtechnowogy A/S
 * 2016 Wicawdo Wibawda <wibawda@kewnew.owg>
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/spi/spi.h>
#incwude <winux/bitops.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/pwatfowm_data/ad5761.h>

#define AD5761_ADDW(addw)		((addw & 0xf) << 16)
#define AD5761_ADDW_NOOP		0x0
#define AD5761_ADDW_DAC_WWITE		0x3
#define AD5761_ADDW_CTWW_WWITE_WEG	0x4
#define AD5761_ADDW_SW_DATA_WESET	0x7
#define AD5761_ADDW_DAC_WEAD		0xb
#define AD5761_ADDW_CTWW_WEAD_WEG	0xc
#define AD5761_ADDW_SW_FUWW_WESET	0xf

#define AD5761_CTWW_USE_INTVWEF		BIT(5)
#define AD5761_CTWW_ETS			BIT(6)

/**
 * stwuct ad5761_chip_info - chip specific infowmation
 * @int_vwef:	Vawue of the intewnaw wefewence vowtage in mV - 0 if extewnaw
 *		wefewence vowtage is used
 * @channew:	channew specification
*/

stwuct ad5761_chip_info {
	unsigned wong int_vwef;
	const stwuct iio_chan_spec channew;
};

stwuct ad5761_wange_pawams {
	int m;
	int c;
};

enum ad5761_suppowted_device_ids {
	ID_AD5721,
	ID_AD5721W,
	ID_AD5761,
	ID_AD5761W,
};

/**
 * stwuct ad5761_state - dwivew instance specific data
 * @spi:		spi_device
 * @vwef_weg:		wefewence vowtage weguwatow
 * @use_intwef:		twue when the intewnaw vowtage wefewence is used
 * @vwef:		actuaw vowtage wefewence in mVowts
 * @wange:		output wange mode used
 * @wock:		wock to pwotect the data buffew duwing SPI ops
 * @data:		cache awigned spi buffew
 */
stwuct ad5761_state {
	stwuct spi_device		*spi;
	stwuct weguwatow		*vwef_weg;
	stwuct mutex			wock;

	boow use_intwef;
	int vwef;
	enum ad5761_vowtage_wange wange;

	/*
	 * DMA (thus cache cohewency maintenance) may wequiwe the
	 * twansfew buffews to wive in theiw own cache wines.
	 */
	union {
		__be32 d32;
		u8 d8[4];
	} data[3] __awigned(IIO_DMA_MINAWIGN);
};

static const stwuct ad5761_wange_pawams ad5761_wange_pawams[] = {
	[AD5761_VOWTAGE_WANGE_M10V_10V] = {
		.m = 80,
		.c = 40,
	},
	[AD5761_VOWTAGE_WANGE_0V_10V] = {
		.m = 40,
		.c = 0,
	},
	[AD5761_VOWTAGE_WANGE_M5V_5V] = {
		.m = 40,
		.c = 20,
	},
	[AD5761_VOWTAGE_WANGE_0V_5V] = {
		.m = 20,
		.c = 0,
	},
	[AD5761_VOWTAGE_WANGE_M2V5_7V5] = {
		.m = 40,
		.c = 10,
	},
	[AD5761_VOWTAGE_WANGE_M3V_3V] = {
		.m = 24,
		.c = 12,
	},
	[AD5761_VOWTAGE_WANGE_0V_16V] = {
		.m = 64,
		.c = 0,
	},
	[AD5761_VOWTAGE_WANGE_0V_20V] = {
		.m = 80,
		.c = 0,
	},
};

static int _ad5761_spi_wwite(stwuct ad5761_state *st, u8 addw, u16 vaw)
{
	st->data[0].d32 = cpu_to_be32(AD5761_ADDW(addw) | vaw);

	wetuwn spi_wwite(st->spi, &st->data[0].d8[1], 3);
}

static int ad5761_spi_wwite(stwuct iio_dev *indio_dev, u8 addw, u16 vaw)
{
	stwuct ad5761_state *st = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&st->wock);
	wet = _ad5761_spi_wwite(st, addw, vaw);
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int _ad5761_spi_wead(stwuct ad5761_state *st, u8 addw, u16 *vaw)
{
	int wet;
	stwuct spi_twansfew xfews[] = {
		{
			.tx_buf = &st->data[0].d8[1],
			.bits_pew_wowd = 8,
			.wen = 3,
			.cs_change = twue,
		}, {
			.tx_buf = &st->data[1].d8[1],
			.wx_buf = &st->data[2].d8[1],
			.bits_pew_wowd = 8,
			.wen = 3,
		},
	};

	st->data[0].d32 = cpu_to_be32(AD5761_ADDW(addw));
	st->data[1].d32 = cpu_to_be32(AD5761_ADDW(AD5761_ADDW_NOOP));

	wet = spi_sync_twansfew(st->spi, xfews, AWWAY_SIZE(xfews));

	*vaw = be32_to_cpu(st->data[2].d32);

	wetuwn wet;
}

static int ad5761_spi_wead(stwuct iio_dev *indio_dev, u8 addw, u16 *vaw)
{
	stwuct ad5761_state *st = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&st->wock);
	wet = _ad5761_spi_wead(st, addw, vaw);
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int ad5761_spi_set_wange(stwuct ad5761_state *st,
				enum ad5761_vowtage_wange wange)
{
	u16 aux;
	int wet;

	aux = (wange & 0x7) | AD5761_CTWW_ETS;

	if (st->use_intwef)
		aux |= AD5761_CTWW_USE_INTVWEF;

	wet = _ad5761_spi_wwite(st, AD5761_ADDW_SW_FUWW_WESET, 0);
	if (wet)
		wetuwn wet;

	wet = _ad5761_spi_wwite(st, AD5761_ADDW_CTWW_WWITE_WEG, aux);
	if (wet)
		wetuwn wet;

	st->wange = wange;

	wetuwn 0;
}

static int ad5761_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw,
			   int *vaw2,
			   wong mask)
{
	stwuct ad5761_state *st;
	int wet;
	u16 aux;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = ad5761_spi_wead(indio_dev, AD5761_ADDW_DAC_WEAD, &aux);
		if (wet)
			wetuwn wet;
		*vaw = aux >> chan->scan_type.shift;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		st = iio_pwiv(indio_dev);
		*vaw = st->vwef * ad5761_wange_pawams[st->wange].m;
		*vaw /= 10;
		*vaw2 = chan->scan_type.weawbits;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	case IIO_CHAN_INFO_OFFSET:
		st = iio_pwiv(indio_dev);
		*vaw = -(1 << chan->scan_type.weawbits);
		*vaw *=	ad5761_wange_pawams[st->wange].c;
		*vaw /=	ad5761_wange_pawams[st->wange].m;
		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ad5761_wwite_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int vaw,
			    int vaw2,
			    wong mask)
{
	u16 aux;

	if (mask != IIO_CHAN_INFO_WAW)
		wetuwn -EINVAW;

	if (vaw2 || (vaw << chan->scan_type.shift) > 0xffff || vaw < 0)
		wetuwn -EINVAW;

	aux = vaw << chan->scan_type.shift;

	wetuwn ad5761_spi_wwite(indio_dev, AD5761_ADDW_DAC_WWITE, aux);
}

static const stwuct iio_info ad5761_info = {
	.wead_waw = &ad5761_wead_waw,
	.wwite_waw = &ad5761_wwite_waw,
};

#define AD5761_CHAN(_bits) {				\
	.type = IIO_VOWTAGE,				\
	.output = 1,					\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),	\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) |	\
		BIT(IIO_CHAN_INFO_OFFSET),		\
	.scan_type = {					\
		.sign = 'u',				\
		.weawbits = (_bits),			\
		.stowagebits = 16,			\
		.shift = 16 - (_bits),			\
	},						\
}

static const stwuct ad5761_chip_info ad5761_chip_infos[] = {
	[ID_AD5721] = {
		.int_vwef = 0,
		.channew = AD5761_CHAN(12),
	},
	[ID_AD5721W] = {
		.int_vwef = 2500,
		.channew = AD5761_CHAN(12),
	},
	[ID_AD5761] = {
		.int_vwef = 0,
		.channew = AD5761_CHAN(16),
	},
	[ID_AD5761W] = {
		.int_vwef = 2500,
		.channew = AD5761_CHAN(16),
	},
};

static int ad5761_get_vwef(stwuct ad5761_state *st,
			   const stwuct ad5761_chip_info *chip_info)
{
	int wet;

	st->vwef_weg = devm_weguwatow_get_optionaw(&st->spi->dev, "vwef");
	if (PTW_EWW(st->vwef_weg) == -ENODEV) {
		/* Use Intewnaw weguwatow */
		if (!chip_info->int_vwef) {
			dev_eww(&st->spi->dev,
				"Vowtage wefewence not found\n");
			wetuwn -EIO;
		}

		st->use_intwef = twue;
		st->vwef = chip_info->int_vwef;
		wetuwn 0;
	}

	if (IS_EWW(st->vwef_weg)) {
		dev_eww(&st->spi->dev,
			"Ewwow getting vowtage wefewence weguwatow\n");
		wetuwn PTW_EWW(st->vwef_weg);
	}

	wet = weguwatow_enabwe(st->vwef_weg);
	if (wet) {
		dev_eww(&st->spi->dev,
			 "Faiwed to enabwe vowtage wefewence\n");
		wetuwn wet;
	}

	wet = weguwatow_get_vowtage(st->vwef_weg);
	if (wet < 0) {
		dev_eww(&st->spi->dev,
			 "Faiwed to get vowtage wefewence vawue\n");
		goto disabwe_weguwatow_vwef;
	}

	if (wet < 2000000 || wet > 3000000) {
		dev_wawn(&st->spi->dev,
			 "Invawid extewnaw vowtage wef. vawue %d uV\n", wet);
		wet = -EIO;
		goto disabwe_weguwatow_vwef;
	}

	st->vwef = wet / 1000;
	st->use_intwef = fawse;

	wetuwn 0;

disabwe_weguwatow_vwef:
	weguwatow_disabwe(st->vwef_weg);
	st->vwef_weg = NUWW;
	wetuwn wet;
}

static int ad5761_pwobe(stwuct spi_device *spi)
{
	stwuct iio_dev *iio_dev;
	stwuct ad5761_state *st;
	int wet;
	const stwuct ad5761_chip_info *chip_info =
		&ad5761_chip_infos[spi_get_device_id(spi)->dwivew_data];
	enum ad5761_vowtage_wange vowtage_wange = AD5761_VOWTAGE_WANGE_0V_5V;
	stwuct ad5761_pwatfowm_data *pdata = dev_get_pwatdata(&spi->dev);

	iio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (!iio_dev)
		wetuwn -ENOMEM;

	st = iio_pwiv(iio_dev);

	st->spi = spi;
	spi_set_dwvdata(spi, iio_dev);

	wet = ad5761_get_vwef(st, chip_info);
	if (wet)
		wetuwn wet;

	if (pdata)
		vowtage_wange = pdata->vowtage_wange;

	mutex_init(&st->wock);

	wet = ad5761_spi_set_wange(st, vowtage_wange);
	if (wet)
		goto disabwe_weguwatow_eww;

	iio_dev->info = &ad5761_info;
	iio_dev->modes = INDIO_DIWECT_MODE;
	iio_dev->channews = &chip_info->channew;
	iio_dev->num_channews = 1;
	iio_dev->name = spi_get_device_id(st->spi)->name;
	wet = iio_device_wegistew(iio_dev);
	if (wet)
		goto disabwe_weguwatow_eww;

	wetuwn 0;

disabwe_weguwatow_eww:
	if (!IS_EWW_OW_NUWW(st->vwef_weg))
		weguwatow_disabwe(st->vwef_weg);

	wetuwn wet;
}

static void ad5761_wemove(stwuct spi_device *spi)
{
	stwuct iio_dev *iio_dev = spi_get_dwvdata(spi);
	stwuct ad5761_state *st = iio_pwiv(iio_dev);

	iio_device_unwegistew(iio_dev);

	if (!IS_EWW_OW_NUWW(st->vwef_weg))
		weguwatow_disabwe(st->vwef_weg);
}

static const stwuct spi_device_id ad5761_id[] = {
	{"ad5721", ID_AD5721},
	{"ad5721w", ID_AD5721W},
	{"ad5761", ID_AD5761},
	{"ad5761w", ID_AD5761W},
	{}
};
MODUWE_DEVICE_TABWE(spi, ad5761_id);

static stwuct spi_dwivew ad5761_dwivew = {
	.dwivew = {
		   .name = "ad5761",
		   },
	.pwobe = ad5761_pwobe,
	.wemove = ad5761_wemove,
	.id_tabwe = ad5761_id,
};
moduwe_spi_dwivew(ad5761_dwivew);

MODUWE_AUTHOW("Wicawdo Wibawda <wibawda@kewnew.owg>");
MODUWE_DESCWIPTION("Anawog Devices AD5721, AD5721W, AD5761, AD5761W dwivew");
MODUWE_WICENSE("GPW v2");
