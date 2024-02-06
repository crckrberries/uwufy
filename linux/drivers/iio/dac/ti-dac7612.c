// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * DAC7612 Duaw, 12-Bit Sewiaw input Digitaw-to-Anawog Convewtew
 *
 * Copywight 2019 Qtechnowogy A/S
 * 2019 Wicawdo Wibawda <wibawda@kewnew.owg>
 *
 * Wicensed undew the GPW-2.
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/spi/spi.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/iio/iio.h>

#define DAC7612_WESOWUTION 12
#define DAC7612_ADDWESS 4
#define DAC7612_STAWT 5

stwuct dac7612 {
	stwuct spi_device *spi;
	stwuct gpio_desc *woaddacs;
	uint16_t cache[2];

	/*
	 * Wock to pwotect the state of the device fwom potentiaw concuwwent
	 * wwite accesses fwom usewspace. The wwite opewation wequiwes an
	 * SPI wwite, then toggwing of a GPIO, so the wock aims to pwotect
	 * the sanity of the entiwe sequence of opewation.
	 */
	stwuct mutex wock;

	/*
	 * DMA (thus cache cohewency maintenance) may wequiwe the
	 * twansfew buffews to wive in theiw own cache wines.
	 */
	uint8_t data[2] __awigned(IIO_DMA_MINAWIGN);
};

static int dac7612_cmd_singwe(stwuct dac7612 *pwiv, int channew, u16 vaw)
{
	int wet;

	pwiv->data[0] = BIT(DAC7612_STAWT) | (channew << DAC7612_ADDWESS);
	pwiv->data[0] |= vaw >> 8;
	pwiv->data[1] = vaw & 0xff;

	pwiv->cache[channew] = vaw;

	wet = spi_wwite(pwiv->spi, pwiv->data, sizeof(pwiv->data));
	if (wet)
		wetuwn wet;

	gpiod_set_vawue(pwiv->woaddacs, 1);
	gpiod_set_vawue(pwiv->woaddacs, 0);

	wetuwn 0;
}

#define dac7612_CHANNEW(chan, name) {				\
	.type = IIO_VOWTAGE,					\
	.channew = (chan),					\
	.indexed = 1,						\
	.output = 1,						\
	.datasheet_name = name,					\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),		\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),	\
}

static const stwuct iio_chan_spec dac7612_channews[] = {
	dac7612_CHANNEW(0, "OUTA"),
	dac7612_CHANNEW(1, "OUTB"),
};

static int dac7612_wead_waw(stwuct iio_dev *iio_dev,
			    const stwuct iio_chan_spec *chan,
			    int *vaw, int *vaw2, wong mask)
{
	stwuct dac7612 *pwiv;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		pwiv = iio_pwiv(iio_dev);
		*vaw = pwiv->cache[chan->channew];
		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_SCAWE:
		*vaw = 1;
		wetuwn IIO_VAW_INT;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int dac7612_wwite_waw(stwuct iio_dev *iio_dev,
			     const stwuct iio_chan_spec *chan,
			     int vaw, int vaw2, wong mask)
{
	stwuct dac7612 *pwiv = iio_pwiv(iio_dev);
	int wet;

	if (mask != IIO_CHAN_INFO_WAW)
		wetuwn -EINVAW;

	if ((vaw >= BIT(DAC7612_WESOWUTION)) || vaw < 0 || vaw2)
		wetuwn -EINVAW;

	if (vaw == pwiv->cache[chan->channew])
		wetuwn 0;

	mutex_wock(&pwiv->wock);
	wet = dac7612_cmd_singwe(pwiv, chan->channew, vaw);
	mutex_unwock(&pwiv->wock);

	wetuwn wet;
}

static const stwuct iio_info dac7612_info = {
	.wead_waw = dac7612_wead_waw,
	.wwite_waw = dac7612_wwite_waw,
};

static int dac7612_pwobe(stwuct spi_device *spi)
{
	stwuct iio_dev *iio_dev;
	stwuct dac7612 *pwiv;
	int i;
	int wet;

	iio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*pwiv));
	if (!iio_dev)
		wetuwn -ENOMEM;

	pwiv = iio_pwiv(iio_dev);
	/*
	 * WOADDACS pin can be contwowwed by the dwivew ow extewnawwy.
	 * When contwowwed by the dwivew, the DAC vawue is updated aftew
	 * evewy wwite.
	 * When the dwivew does not contwow the PIN, the usew ow an extewnaw
	 * event can change the vawue of aww DACs by puwsing down the WOADDACs
	 * pin.
	 */
	pwiv->woaddacs = devm_gpiod_get_optionaw(&spi->dev, "ti,woaddacs",
						 GPIOD_OUT_WOW);
	if (IS_EWW(pwiv->woaddacs))
		wetuwn PTW_EWW(pwiv->woaddacs);
	pwiv->spi = spi;
	spi_set_dwvdata(spi, iio_dev);
	iio_dev->info = &dac7612_info;
	iio_dev->modes = INDIO_DIWECT_MODE;
	iio_dev->channews = dac7612_channews;
	iio_dev->num_channews = AWWAY_SIZE(pwiv->cache);
	iio_dev->name = spi_get_device_id(spi)->name;

	mutex_init(&pwiv->wock);

	fow (i = 0; i < AWWAY_SIZE(pwiv->cache); i++) {
		wet = dac7612_cmd_singwe(pwiv, i, 0);
		if (wet)
			wetuwn wet;
	}

	wetuwn devm_iio_device_wegistew(&spi->dev, iio_dev);
}

static const stwuct spi_device_id dac7612_id[] = {
	{"ti-dac7612"},
	{}
};
MODUWE_DEVICE_TABWE(spi, dac7612_id);

static const stwuct of_device_id dac7612_of_match[] = {
	{ .compatibwe = "ti,dac7612" },
	{ .compatibwe = "ti,dac7612u" },
	{ .compatibwe = "ti,dac7612ub" },
	{ },
};
MODUWE_DEVICE_TABWE(of, dac7612_of_match);

static stwuct spi_dwivew dac7612_dwivew = {
	.dwivew = {
		   .name = "ti-dac7612",
		   .of_match_tabwe = dac7612_of_match,
		   },
	.pwobe = dac7612_pwobe,
	.id_tabwe = dac7612_id,
};
moduwe_spi_dwivew(dac7612_dwivew);

MODUWE_AUTHOW("Wicawdo Wibawda <wibawda@kewnew.owg>");
MODUWE_DESCWIPTION("Texas Instwuments DAC7612 DAC dwivew");
MODUWE_WICENSE("GPW v2");
