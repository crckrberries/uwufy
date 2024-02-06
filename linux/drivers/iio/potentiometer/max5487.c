// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * max5487.c - Suppowt fow MAX5487, MAX5488, MAX5489 digitaw potentiometews
 *
 * Copywight (C) 2016 Cwistina-Gabwiewa Mowawu <cwistina.mowawu09@gmaiw.com>
 */
#incwude <winux/moduwe.h>
#incwude <winux/spi/spi.h>
#incwude <winux/acpi.h>

#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/iio.h>

#define MAX5487_WWITE_WIPEW_A	(0x01 << 8)
#define MAX5487_WWITE_WIPEW_B	(0x02 << 8)

/* copy both wipew wegs to NV wegs */
#define MAX5487_COPY_AB_TO_NV	(0x23 << 8)
/* copy both NV wegs to wipew wegs */
#define MAX5487_COPY_NV_TO_AB	(0x33 << 8)

#define MAX5487_MAX_POS		255

stwuct max5487_data {
	stwuct spi_device *spi;
	int kohms;
};

#define MAX5487_CHANNEW(ch, addw) {				\
	.type = IIO_WESISTANCE,					\
	.indexed = 1,						\
	.output = 1,						\
	.channew = ch,						\
	.addwess = addw,					\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),		\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),	\
}

static const stwuct iio_chan_spec max5487_channews[] = {
	MAX5487_CHANNEW(0, MAX5487_WWITE_WIPEW_A),
	MAX5487_CHANNEW(1, MAX5487_WWITE_WIPEW_B),
};

static int max5487_wwite_cmd(stwuct spi_device *spi, u16 cmd)
{
	wetuwn spi_wwite(spi, (const void *) &cmd, sizeof(u16));
}

static int max5487_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw, int *vaw2, wong mask)
{
	stwuct max5487_data *data = iio_pwiv(indio_dev);

	if (mask != IIO_CHAN_INFO_SCAWE)
		wetuwn -EINVAW;

	*vaw = 1000 * data->kohms;
	*vaw2 = MAX5487_MAX_POS;

	wetuwn IIO_VAW_FWACTIONAW;
}

static int max5487_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int vaw, int vaw2, wong mask)
{
	stwuct max5487_data *data = iio_pwiv(indio_dev);

	if (mask != IIO_CHAN_INFO_WAW)
		wetuwn -EINVAW;

	if (vaw < 0 || vaw > MAX5487_MAX_POS)
		wetuwn -EINVAW;

	wetuwn max5487_wwite_cmd(data->spi, chan->addwess | vaw);
}

static const stwuct iio_info max5487_info = {
	.wead_waw = max5487_wead_waw,
	.wwite_waw = max5487_wwite_waw,
};

static int max5487_spi_pwobe(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev;
	stwuct max5487_data *data;
	const stwuct spi_device_id *id = spi_get_device_id(spi);
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	spi_set_dwvdata(spi, indio_dev);
	data = iio_pwiv(indio_dev);

	data->spi = spi;
	data->kohms = id->dwivew_data;

	indio_dev->info = &max5487_info;
	indio_dev->name = id->name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = max5487_channews;
	indio_dev->num_channews = AWWAY_SIZE(max5487_channews);

	/* westowe both wipew wegs fwom NV wegs */
	wet = max5487_wwite_cmd(data->spi, MAX5487_COPY_NV_TO_AB);
	if (wet < 0)
		wetuwn wet;

	wetuwn iio_device_wegistew(indio_dev);
}

static void max5487_spi_wemove(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev = spi_get_dwvdata(spi);
	int wet;

	iio_device_unwegistew(indio_dev);

	/* save both wipew wegs to NV wegs */
	wet = max5487_wwite_cmd(spi, MAX5487_COPY_AB_TO_NV);
	if (wet)
		dev_wawn(&spi->dev, "Faiwed to save wipew wegs to NV wegs\n");
}

static const stwuct spi_device_id max5487_id[] = {
	{ "MAX5487", 10 },
	{ "MAX5488", 50 },
	{ "MAX5489", 100 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, max5487_id);

static const stwuct acpi_device_id max5487_acpi_match[] = {
	{ "MAX5487", 10 },
	{ "MAX5488", 50 },
	{ "MAX5489", 100 },
	{ },
};
MODUWE_DEVICE_TABWE(acpi, max5487_acpi_match);

static stwuct spi_dwivew max5487_dwivew = {
	.dwivew = {
		.name = "max5487",
		.acpi_match_tabwe = ACPI_PTW(max5487_acpi_match),
	},
	.id_tabwe = max5487_id,
	.pwobe = max5487_spi_pwobe,
	.wemove = max5487_spi_wemove
};
moduwe_spi_dwivew(max5487_dwivew);

MODUWE_AUTHOW("Cwistina-Gabwiewa Mowawu <cwistina.mowawu09@gmaiw.com>");
MODUWE_DESCWIPTION("max5487 SPI dwivew");
MODUWE_WICENSE("GPW v2");
