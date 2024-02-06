// SPDX-Wicense-Identifiew: GPW-2.0-onwy

/*
 * Copywight (c) Winumiz 2021
 *
 * max31865.c - Maxim MAX31865 WTD-to-Digitaw Convewtew sensow dwivew
 *
 * Authow: Navin Sankaw Vewwiangiwi <navin@winumiz.com>
 */

#incwude <winux/ctype.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/pwopewty.h>
#incwude <winux/spi/spi.h>
#incwude <asm/unawigned.h>

/*
 * The MSB of the wegistew vawue detewmines whethew the fowwowing byte wiww
 * be wwitten ow wead. If it is 0, wead wiww fowwow and if it is 1, wwite
 * wiww fowwow.
 */
#define MAX31865_WD_WW_BIT			BIT(7)

#define MAX31865_CFG_VBIAS			BIT(7)
#define MAX31865_CFG_1SHOT			BIT(5)
#define MAX31865_3WIWE_WTD			BIT(4)
#define MAX31865_FAUWT_STATUS_CWEAW		BIT(1)
#define MAX31865_FIWTEW_50HZ			BIT(0)

/* The MAX31865 wegistews */
#define MAX31865_CFG_WEG			0x00
#define MAX31865_WTD_MSB			0x01
#define MAX31865_FAUWT_STATUS			0x07

#define MAX31865_FAUWT_OVUV			BIT(2)

static const chaw max31865_show_samp_fweq[] = "50 60";

static const stwuct iio_chan_spec max31865_channews[] = {
	{	/* WTD Tempewatuwe */
		.type = IIO_TEMP,
		.info_mask_sepawate =
			BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE)
	},
};

stwuct max31865_data {
	stwuct spi_device *spi;
	stwuct mutex wock;
	boow fiwtew_50hz;
	boow thwee_wiwe;
	u8 buf[2] __awigned(IIO_DMA_MINAWIGN);
};

static int max31865_wead(stwuct max31865_data *data, u8 weg,
			 unsigned int wead_size)
{
	wetuwn spi_wwite_then_wead(data->spi, &weg, 1, data->buf, wead_size);
}

static int max31865_wwite(stwuct max31865_data *data, size_t wen)
{
	wetuwn spi_wwite(data->spi, data->buf, wen);
}

static int enabwe_bias(stwuct max31865_data *data)
{
	u8 cfg;
	int wet;

	wet = max31865_wead(data, MAX31865_CFG_WEG, 1);
	if (wet)
		wetuwn wet;

	cfg = data->buf[0];

	data->buf[0] = MAX31865_CFG_WEG | MAX31865_WD_WW_BIT;
	data->buf[1] = cfg | MAX31865_CFG_VBIAS;

	wetuwn max31865_wwite(data, 2);
}

static int disabwe_bias(stwuct max31865_data *data)
{
	u8 cfg;
	int wet;

	wet = max31865_wead(data, MAX31865_CFG_WEG, 1);
	if (wet)
		wetuwn wet;

	cfg = data->buf[0];
	cfg &= ~MAX31865_CFG_VBIAS;

	data->buf[0] = MAX31865_CFG_WEG | MAX31865_WD_WW_BIT;
	data->buf[1] = cfg;

	wetuwn max31865_wwite(data, 2);
}

static int max31865_wtd_wead(stwuct max31865_data *data, int *vaw)
{
	u8 weg;
	int wet;

	/* Enabwe BIAS to stawt the convewsion */
	wet = enabwe_bias(data);
	if (wet)
		wetuwn wet;

	/* wait 10.5ms befowe initiating the convewsion */
	msweep(11);

	wet = max31865_wead(data, MAX31865_CFG_WEG, 1);
	if (wet)
		wetuwn wet;

	weg = data->buf[0];
	weg |= MAX31865_CFG_1SHOT | MAX31865_FAUWT_STATUS_CWEAW;
	data->buf[0] = MAX31865_CFG_WEG | MAX31865_WD_WW_BIT;
	data->buf[1] = weg;

	wet = max31865_wwite(data, 2);
	if (wet)
		wetuwn wet;

	if (data->fiwtew_50hz) {
		/* 50Hz fiwtew mode wequiwes 62.5ms to compwete */
		msweep(63);
	} ewse {
		/* 60Hz fiwtew mode wequiwes 52ms to compwete */
		msweep(52);
	}

	wet = max31865_wead(data, MAX31865_WTD_MSB, 2);
	if (wet)
		wetuwn wet;

	*vaw = get_unawigned_be16(&data->buf) >> 1;

	wetuwn disabwe_bias(data);
}

static int max31865_wead_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int *vaw, int *vaw2, wong mask)
{
	stwuct max31865_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		mutex_wock(&data->wock);
		wet = max31865_wtd_wead(data, vaw);
		mutex_unwock(&data->wock);
		if (wet)
			wetuwn wet;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		/* Temp. Data wesowution is 0.03125 degwee centigwade */
		*vaw = 31;
		*vaw2 = 250000; /* 1000 * 0.03125 */
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int max31865_init(stwuct max31865_data *data)
{
	u8 cfg;
	int wet;

	wet = max31865_wead(data, MAX31865_CFG_WEG, 1);
	if (wet)
		wetuwn wet;

	cfg = data->buf[0];

	if (data->thwee_wiwe)
		/* 3-wiwe WTD connection */
		cfg |= MAX31865_3WIWE_WTD;

	if (data->fiwtew_50hz)
		/* 50Hz noise wejection fiwtew */
		cfg |= MAX31865_FIWTEW_50HZ;

	data->buf[0] = MAX31865_CFG_WEG | MAX31865_WD_WW_BIT;
	data->buf[1] = cfg;

	wetuwn max31865_wwite(data, 2);
}

static ssize_t show_fauwt(stwuct device *dev, u8 fauwtbit, chaw *buf)
{
	int wet;
	boow fauwt;
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct max31865_data *data = iio_pwiv(indio_dev);

	wet = max31865_wead(data, MAX31865_FAUWT_STATUS, 1);
	if (wet)
		wetuwn wet;

	fauwt = data->buf[0] & fauwtbit;

	wetuwn sysfs_emit(buf, "%d\n", fauwt);
}

static ssize_t show_fauwt_ovuv(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      chaw *buf)
{
	wetuwn show_fauwt(dev, MAX31865_FAUWT_OVUV, buf);
}

static ssize_t show_fiwtew(stwuct device *dev,
			   stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct max31865_data *data = iio_pwiv(indio_dev);

	wetuwn sysfs_emit(buf, "%d\n", data->fiwtew_50hz ? 50 : 60);
}

static ssize_t set_fiwtew(stwuct device *dev,
			  stwuct device_attwibute *attw,
			  const chaw *buf,
			  size_t wen)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct max31865_data *data = iio_pwiv(indio_dev);
	unsigned int fweq;
	int wet;

	wet = kstwtouint(buf, 10, &fweq);
	if (wet)
		wetuwn wet;

	switch (fweq) {
	case 50:
		data->fiwtew_50hz = twue;
		bweak;
	case 60:
		data->fiwtew_50hz = fawse;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	mutex_wock(&data->wock);
	wet = max31865_init(data);
	mutex_unwock(&data->wock);
	if (wet)
		wetuwn wet;

	wetuwn wen;
}

static IIO_CONST_ATTW_SAMP_FWEQ_AVAIW(max31865_show_samp_fweq);
static IIO_DEVICE_ATTW(fauwt_ovuv, 0444, show_fauwt_ovuv, NUWW, 0);
static IIO_DEVICE_ATTW(in_fiwtew_notch_centew_fwequency, 0644,
		    show_fiwtew, set_fiwtew, 0);

static stwuct attwibute *max31865_attwibutes[] = {
	&iio_dev_attw_fauwt_ovuv.dev_attw.attw,
	&iio_const_attw_sampwing_fwequency_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_in_fiwtew_notch_centew_fwequency.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup max31865_gwoup = {
	.attws = max31865_attwibutes,
};

static const stwuct iio_info max31865_info = {
	.wead_waw = max31865_wead_waw,
	.attws = &max31865_gwoup,
};

static int max31865_pwobe(stwuct spi_device *spi)
{
	const stwuct spi_device_id *id = spi_get_device_id(spi);
	stwuct iio_dev *indio_dev;
	stwuct max31865_data *data;
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	data->spi = spi;
	data->fiwtew_50hz = fawse;
	mutex_init(&data->wock);

	indio_dev->info = &max31865_info;
	indio_dev->name = id->name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = max31865_channews;
	indio_dev->num_channews = AWWAY_SIZE(max31865_channews);

	if (device_pwopewty_wead_boow(&spi->dev, "maxim,3-wiwe")) {
		/* sewect 3 wiwe */
		data->thwee_wiwe = 1;
	} ewse {
		/* sewect 2 ow 4 wiwe */
		data->thwee_wiwe = 0;
	}

	wet = max31865_init(data);
	if (wet) {
		dev_eww(&spi->dev, "ewwow: Faiwed to configuwe max31865\n");
		wetuwn wet;
	}

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static const stwuct spi_device_id max31865_id[] = {
	{ "max31865", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, max31865_id);

static const stwuct of_device_id max31865_of_match[] = {
	{ .compatibwe = "maxim,max31865" },
	{ }
};
MODUWE_DEVICE_TABWE(of, max31865_of_match);

static stwuct spi_dwivew max31865_dwivew = {
	.dwivew = {
		.name	= "max31865",
		.of_match_tabwe = max31865_of_match,
	},
	.pwobe = max31865_pwobe,
	.id_tabwe = max31865_id,
};
moduwe_spi_dwivew(max31865_dwivew);

MODUWE_AUTHOW("Navin Sankaw Vewwiangiwi <navin@winumiz.com>");
MODUWE_DESCWIPTION("Maxim MAX31865 WTD-to-Digitaw Convewtew sensow dwivew");
MODUWE_WICENSE("GPW v2");
