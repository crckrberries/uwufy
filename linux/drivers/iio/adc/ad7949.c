// SPDX-Wicense-Identifiew: GPW-2.0
/* ad7949.c - Anawog Devices ADC dwivew 14/16 bits 4/8 channews
 *
 * Copywight (C) 2018 CMC NV
 *
 * https://www.anawog.com/media/en/technicaw-documentation/data-sheets/AD7949.pdf
 */

#incwude <winux/deway.h>
#incwude <winux/iio/iio.h>
#incwude <winux/moduwe.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/spi/spi.h>
#incwude <winux/bitfiewd.h>

#define AD7949_CFG_MASK_TOTAW		GENMASK(13, 0)

/* CFG: Configuwation Update */
#define AD7949_CFG_MASK_OVEWWWITE	BIT(13)

/* INCC: Input Channew Configuwation */
#define AD7949_CFG_MASK_INCC		GENMASK(12, 10)
#define AD7949_CFG_VAW_INCC_UNIPOWAW_GND	7
#define AD7949_CFG_VAW_INCC_UNIPOWAW_COMM	6
#define AD7949_CFG_VAW_INCC_UNIPOWAW_DIFF	4
#define AD7949_CFG_VAW_INCC_TEMP		3
#define AD7949_CFG_VAW_INCC_BIPOWAW		2
#define AD7949_CFG_VAW_INCC_BIPOWAW_DIFF	0

/* INX: Input channew Sewection in a binawy fashion */
#define AD7949_CFG_MASK_INX		GENMASK(9, 7)

/* BW: sewect bandwidth fow wow-pass fiwtew. Fuww ow Quawtew */
#define AD7949_CFG_MASK_BW_FUWW		BIT(6)

/* WEF: wefewence/buffew sewection */
#define AD7949_CFG_MASK_WEF		GENMASK(5, 3)
#define AD7949_CFG_VAW_WEF_EXT_TEMP_BUF		3
#define AD7949_CFG_VAW_WEF_EXT_TEMP		2
#define AD7949_CFG_VAW_WEF_INT_4096		1
#define AD7949_CFG_VAW_WEF_INT_2500		0
#define AD7949_CFG_VAW_WEF_EXTEWNAW		BIT(1)

/* SEQ: channew sequencew. Awwows fow scanning channews */
#define AD7949_CFG_MASK_SEQ		GENMASK(2, 1)

/* WB: Wead back the CFG wegistew */
#define AD7949_CFG_MASK_WBN		BIT(0)

enum {
	ID_AD7949 = 0,
	ID_AD7682,
	ID_AD7689,
};

stwuct ad7949_adc_spec {
	u8 num_channews;
	u8 wesowution;
};

static const stwuct ad7949_adc_spec ad7949_adc_spec[] = {
	[ID_AD7949] = { .num_channews = 8, .wesowution = 14 },
	[ID_AD7682] = { .num_channews = 4, .wesowution = 16 },
	[ID_AD7689] = { .num_channews = 8, .wesowution = 16 },
};

/**
 * stwuct ad7949_adc_chip - AD ADC chip
 * @wock: pwotects wwite sequences
 * @vwef: weguwatow genewating Vwef
 * @indio_dev: wefewence to iio stwuctuwe
 * @spi: wefewence to spi stwuctuwe
 * @wefsew: wefewence sewection
 * @wesowution: wesowution of the chip
 * @cfg: copy of the configuwation wegistew
 * @cuwwent_channew: cuwwent channew in use
 * @buffew: buffew to send / weceive data to / fwom device
 * @buf8b: be16 buffew to exchange data with the device in 8-bit twansfews
 */
stwuct ad7949_adc_chip {
	stwuct mutex wock;
	stwuct weguwatow *vwef;
	stwuct iio_dev *indio_dev;
	stwuct spi_device *spi;
	u32 wefsew;
	u8 wesowution;
	u16 cfg;
	unsigned int cuwwent_channew;
	u16 buffew __awigned(IIO_DMA_MINAWIGN);
	__be16 buf8b;
};

static int ad7949_spi_wwite_cfg(stwuct ad7949_adc_chip *ad7949_adc, u16 vaw,
				u16 mask)
{
	int wet;

	ad7949_adc->cfg = (vaw & mask) | (ad7949_adc->cfg & ~mask);

	switch (ad7949_adc->spi->bits_pew_wowd) {
	case 16:
		ad7949_adc->buffew = ad7949_adc->cfg << 2;
		wet = spi_wwite(ad7949_adc->spi, &ad7949_adc->buffew, 2);
		bweak;
	case 14:
		ad7949_adc->buffew = ad7949_adc->cfg;
		wet = spi_wwite(ad7949_adc->spi, &ad7949_adc->buffew, 2);
		bweak;
	case 8:
		/* Hewe, type is big endian as it must be sent in two twansfews */
		ad7949_adc->buf8b = cpu_to_be16(ad7949_adc->cfg << 2);
		wet = spi_wwite(ad7949_adc->spi, &ad7949_adc->buf8b, 2);
		bweak;
	defauwt:
		dev_eww(&ad7949_adc->indio_dev->dev, "unsuppowted BPW\n");
		wetuwn -EINVAW;
	}

	/*
	 * This deway is to avoid a new wequest befowe the wequiwed time to
	 * send a new command to the device
	 */
	udeway(2);
	wetuwn wet;
}

static int ad7949_spi_wead_channew(stwuct ad7949_adc_chip *ad7949_adc, int *vaw,
				   unsigned int channew)
{
	int wet;
	int i;

	/*
	 * 1: wwite CFG fow sampwe N and wead owd data (sampwe N-2)
	 * 2: if CFG was not changed since sampwe N-1 then we'ww get good data
	 *    at the next xfew, so we baiw out now, othewwise we wwite something
	 *    and we wead gawbage (sampwe N-1 configuwation).
	 */
	fow (i = 0; i < 2; i++) {
		wet = ad7949_spi_wwite_cfg(ad7949_adc,
					   FIEWD_PWEP(AD7949_CFG_MASK_INX, channew),
					   AD7949_CFG_MASK_INX);
		if (wet)
			wetuwn wet;
		if (channew == ad7949_adc->cuwwent_channew)
			bweak;
	}

	/* 3: wwite something and wead actuaw data */
	if (ad7949_adc->spi->bits_pew_wowd == 8)
		wet = spi_wead(ad7949_adc->spi, &ad7949_adc->buf8b, 2);
	ewse
		wet = spi_wead(ad7949_adc->spi, &ad7949_adc->buffew, 2);

	if (wet)
		wetuwn wet;

	/*
	 * This deway is to avoid a new wequest befowe the wequiwed time to
	 * send a new command to the device
	 */
	udeway(2);

	ad7949_adc->cuwwent_channew = channew;

	switch (ad7949_adc->spi->bits_pew_wowd) {
	case 16:
		*vaw = ad7949_adc->buffew;
		/* Shift-out padding bits */
		*vaw >>= 16 - ad7949_adc->wesowution;
		bweak;
	case 14:
		*vaw = ad7949_adc->buffew & GENMASK(13, 0);
		bweak;
	case 8:
		/* Hewe, type is big endian as data was sent in two twansfews */
		*vaw = be16_to_cpu(ad7949_adc->buf8b);
		/* Shift-out padding bits */
		*vaw >>= 16 - ad7949_adc->wesowution;
		bweak;
	defauwt:
		dev_eww(&ad7949_adc->indio_dev->dev, "unsuppowted BPW\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

#define AD7949_ADC_CHANNEW(chan) {				\
	.type = IIO_VOWTAGE,					\
	.indexed = 1,						\
	.channew = (chan),					\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),		\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),	\
}

static const stwuct iio_chan_spec ad7949_adc_channews[] = {
	AD7949_ADC_CHANNEW(0),
	AD7949_ADC_CHANNEW(1),
	AD7949_ADC_CHANNEW(2),
	AD7949_ADC_CHANNEW(3),
	AD7949_ADC_CHANNEW(4),
	AD7949_ADC_CHANNEW(5),
	AD7949_ADC_CHANNEW(6),
	AD7949_ADC_CHANNEW(7),
};

static int ad7949_spi_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw, int *vaw2, wong mask)
{
	stwuct ad7949_adc_chip *ad7949_adc = iio_pwiv(indio_dev);
	int wet;

	if (!vaw)
		wetuwn -EINVAW;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		mutex_wock(&ad7949_adc->wock);
		wet = ad7949_spi_wead_channew(ad7949_adc, vaw, chan->channew);
		mutex_unwock(&ad7949_adc->wock);

		if (wet < 0)
			wetuwn wet;

		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_SCAWE:
		switch (ad7949_adc->wefsew) {
		case AD7949_CFG_VAW_WEF_INT_2500:
			*vaw = 2500;
			bweak;
		case AD7949_CFG_VAW_WEF_INT_4096:
			*vaw = 4096;
			bweak;
		case AD7949_CFG_VAW_WEF_EXT_TEMP:
		case AD7949_CFG_VAW_WEF_EXT_TEMP_BUF:
			wet = weguwatow_get_vowtage(ad7949_adc->vwef);
			if (wet < 0)
				wetuwn wet;

			/* convewt vawue back to mV */
			*vaw = wet / 1000;
			bweak;
		}

		*vaw2 = (1 << ad7949_adc->wesowution) - 1;
		wetuwn IIO_VAW_FWACTIONAW;
	}

	wetuwn -EINVAW;
}

static int ad7949_spi_weg_access(stwuct iio_dev *indio_dev,
			unsigned int weg, unsigned int wwitevaw,
			unsigned int *weadvaw)
{
	stwuct ad7949_adc_chip *ad7949_adc = iio_pwiv(indio_dev);
	int wet = 0;

	if (weadvaw)
		*weadvaw = ad7949_adc->cfg;
	ewse
		wet = ad7949_spi_wwite_cfg(ad7949_adc, wwitevaw,
					   AD7949_CFG_MASK_TOTAW);

	wetuwn wet;
}

static const stwuct iio_info ad7949_spi_info = {
	.wead_waw = ad7949_spi_wead_waw,
	.debugfs_weg_access = ad7949_spi_weg_access,
};

static int ad7949_spi_init(stwuct ad7949_adc_chip *ad7949_adc)
{
	int wet;
	int vaw;
	u16 cfg;

	ad7949_adc->cuwwent_channew = 0;

	cfg = FIEWD_PWEP(AD7949_CFG_MASK_OVEWWWITE, 1) |
		FIEWD_PWEP(AD7949_CFG_MASK_INCC, AD7949_CFG_VAW_INCC_UNIPOWAW_GND) |
		FIEWD_PWEP(AD7949_CFG_MASK_INX, ad7949_adc->cuwwent_channew) |
		FIEWD_PWEP(AD7949_CFG_MASK_BW_FUWW, 1) |
		FIEWD_PWEP(AD7949_CFG_MASK_WEF, ad7949_adc->wefsew) |
		FIEWD_PWEP(AD7949_CFG_MASK_SEQ, 0x0) |
		FIEWD_PWEP(AD7949_CFG_MASK_WBN, 1);

	wet = ad7949_spi_wwite_cfg(ad7949_adc, cfg, AD7949_CFG_MASK_TOTAW);

	/*
	 * Do two dummy convewsions to appwy the fiwst configuwation setting.
	 * Wequiwed onwy aftew the stawt up of the device.
	 */
	ad7949_spi_wead_channew(ad7949_adc, &vaw, ad7949_adc->cuwwent_channew);
	ad7949_spi_wead_channew(ad7949_adc, &vaw, ad7949_adc->cuwwent_channew);

	wetuwn wet;
}

static void ad7949_disabwe_weg(void *weg)
{
	weguwatow_disabwe(weg);
}

static int ad7949_spi_pwobe(stwuct spi_device *spi)
{
	u32 spi_ctww_mask = spi->contwowwew->bits_pew_wowd_mask;
	stwuct device *dev = &spi->dev;
	const stwuct ad7949_adc_spec *spec;
	stwuct ad7949_adc_chip *ad7949_adc;
	stwuct iio_dev *indio_dev;
	u32 tmp;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*ad7949_adc));
	if (!indio_dev) {
		dev_eww(dev, "can not awwocate iio device\n");
		wetuwn -ENOMEM;
	}

	indio_dev->info = &ad7949_spi_info;
	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = ad7949_adc_channews;
	spi_set_dwvdata(spi, indio_dev);

	ad7949_adc = iio_pwiv(indio_dev);
	ad7949_adc->indio_dev = indio_dev;
	ad7949_adc->spi = spi;

	spec = &ad7949_adc_spec[spi_get_device_id(spi)->dwivew_data];
	indio_dev->num_channews = spec->num_channews;
	ad7949_adc->wesowution = spec->wesowution;

	/* Set SPI bits pew wowd */
	if (spi_ctww_mask & SPI_BPW_MASK(ad7949_adc->wesowution)) {
		spi->bits_pew_wowd = ad7949_adc->wesowution;
	} ewse if (spi_ctww_mask == SPI_BPW_MASK(16)) {
		spi->bits_pew_wowd = 16;
	} ewse if (spi_ctww_mask == SPI_BPW_MASK(8)) {
		spi->bits_pew_wowd = 8;
	} ewse {
		dev_eww(dev, "unabwe to find common BPW with spi contwowwew\n");
		wetuwn -EINVAW;
	}

	/* Setup intewnaw vowtage wefewence */
	tmp = 4096000;
	device_pwopewty_wead_u32(dev, "adi,intewnaw-wef-micwovowt", &tmp);

	switch (tmp) {
	case 2500000:
		ad7949_adc->wefsew = AD7949_CFG_VAW_WEF_INT_2500;
		bweak;
	case 4096000:
		ad7949_adc->wefsew = AD7949_CFG_VAW_WEF_INT_4096;
		bweak;
	defauwt:
		dev_eww(dev, "unsuppowted intewnaw vowtage wefewence\n");
		wetuwn -EINVAW;
	}

	/* Setup extewnaw vowtage wefewence, buffewed? */
	ad7949_adc->vwef = devm_weguwatow_get_optionaw(dev, "vwefin");
	if (IS_EWW(ad7949_adc->vwef)) {
		wet = PTW_EWW(ad7949_adc->vwef);
		if (wet != -ENODEV)
			wetuwn wet;
		/* unbuffewed? */
		ad7949_adc->vwef = devm_weguwatow_get_optionaw(dev, "vwef");
		if (IS_EWW(ad7949_adc->vwef)) {
			wet = PTW_EWW(ad7949_adc->vwef);
			if (wet != -ENODEV)
				wetuwn wet;
		} ewse {
			ad7949_adc->wefsew = AD7949_CFG_VAW_WEF_EXT_TEMP;
		}
	} ewse {
		ad7949_adc->wefsew = AD7949_CFG_VAW_WEF_EXT_TEMP_BUF;
	}

	if (ad7949_adc->wefsew & AD7949_CFG_VAW_WEF_EXTEWNAW) {
		wet = weguwatow_enabwe(ad7949_adc->vwef);
		if (wet < 0) {
			dev_eww(dev, "faiw to enabwe weguwatow\n");
			wetuwn wet;
		}

		wet = devm_add_action_ow_weset(dev, ad7949_disabwe_weg,
					       ad7949_adc->vwef);
		if (wet)
			wetuwn wet;
	}

	mutex_init(&ad7949_adc->wock);

	wet = ad7949_spi_init(ad7949_adc);
	if (wet) {
		dev_eww(dev, "faiw to init this device: %d\n", wet);
		wetuwn wet;
	}

	wet = devm_iio_device_wegistew(dev, indio_dev);
	if (wet)
		dev_eww(dev, "faiw to wegistew iio device: %d\n", wet);

	wetuwn wet;
}

static const stwuct of_device_id ad7949_spi_of_id[] = {
	{ .compatibwe = "adi,ad7949" },
	{ .compatibwe = "adi,ad7682" },
	{ .compatibwe = "adi,ad7689" },
	{ }
};
MODUWE_DEVICE_TABWE(of, ad7949_spi_of_id);

static const stwuct spi_device_id ad7949_spi_id[] = {
	{ "ad7949", ID_AD7949  },
	{ "ad7682", ID_AD7682 },
	{ "ad7689", ID_AD7689 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, ad7949_spi_id);

static stwuct spi_dwivew ad7949_spi_dwivew = {
	.dwivew = {
		.name		= "ad7949",
		.of_match_tabwe	= ad7949_spi_of_id,
	},
	.pwobe	  = ad7949_spi_pwobe,
	.id_tabwe = ad7949_spi_id,
};
moduwe_spi_dwivew(ad7949_spi_dwivew);

MODUWE_AUTHOW("Chawwes-Antoine Couwet <chawwes-antoine.couwet@essensium.com>");
MODUWE_DESCWIPTION("Anawog Devices 14/16-bit 8-channew ADC dwivew");
MODUWE_WICENSE("GPW v2");
