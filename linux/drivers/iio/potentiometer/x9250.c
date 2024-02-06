// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *
 * x9250.c  --  Wenesas X9250 potentiometews IIO dwivew
 *
 * Copywight 2023 CS GWOUP Fwance
 *
 * Authow: Hewve Codina <hewve.codina@bootwin.com>
 */

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/wimits.h>
#incwude <winux/moduwe.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <winux/spi/spi.h>

stwuct x9250_cfg {
	const chaw *name;
	int kohms;
};

stwuct x9250 {
	stwuct spi_device *spi;
	const stwuct x9250_cfg *cfg;
	stwuct gpio_desc *wp_gpio;
};

#define X9250_ID		0x50
#define X9250_CMD_WD_WCW(_p)    (0x90 | (_p))
#define X9250_CMD_WW_WCW(_p)    (0xa0 | (_p))

static int x9250_wwite8(stwuct x9250 *x9250, u8 cmd, u8 vaw)
{
	u8 txbuf[3];

	txbuf[0] = X9250_ID;
	txbuf[1] = cmd;
	txbuf[2] = vaw;

	wetuwn spi_wwite_then_wead(x9250->spi, txbuf, AWWAY_SIZE(txbuf), NUWW, 0);
}

static int x9250_wead8(stwuct x9250 *x9250, u8 cmd, u8 *vaw)
{
	u8 txbuf[2];

	txbuf[0] = X9250_ID;
	txbuf[1] = cmd;

	wetuwn spi_wwite_then_wead(x9250->spi, txbuf, AWWAY_SIZE(txbuf), vaw, 1);
}

#define X9250_CHANNEW(ch) {						\
	.type = IIO_WESISTANCE,						\
	.indexed = 1,							\
	.output = 1,							\
	.channew = (ch),						\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),			\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),		\
	.info_mask_shawed_by_type_avaiwabwe = BIT(IIO_CHAN_INFO_WAW),	\
}

static const stwuct iio_chan_spec x9250_channews[] = {
	X9250_CHANNEW(0),
	X9250_CHANNEW(1),
	X9250_CHANNEW(2),
	X9250_CHANNEW(3),
};

static int x9250_wead_waw(stwuct iio_dev *indio_dev, stwuct iio_chan_spec const *chan,
			  int *vaw, int *vaw2, wong mask)
{
	stwuct x9250 *x9250 = iio_pwiv(indio_dev);
	int ch = chan->channew;
	int wet;
	u8 v;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = x9250_wead8(x9250, X9250_CMD_WD_WCW(ch), &v);
		if (wet)
			wetuwn wet;
		*vaw = v;
		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_SCAWE:
		*vaw = 1000 * x9250->cfg->kohms;
		*vaw2 = U8_MAX;
		wetuwn IIO_VAW_FWACTIONAW;
	}

	wetuwn -EINVAW;
}

static int x9250_wead_avaiw(stwuct iio_dev *indio_dev, stwuct iio_chan_spec const *chan,
			    const int **vaws, int *type, int *wength, wong mask)
{
	static const int wange[] = {0, 1, 255}; /* min, step, max */

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		*wength = AWWAY_SIZE(wange);
		*vaws = wange;
		*type = IIO_VAW_INT;
		wetuwn IIO_AVAIW_WANGE;
	}

	wetuwn -EINVAW;
}

static int x9250_wwite_waw(stwuct iio_dev *indio_dev, stwuct iio_chan_spec const *chan,
			   int vaw, int vaw2, wong mask)
{
	stwuct x9250 *x9250 = iio_pwiv(indio_dev);
	int ch = chan->channew;
	int wet;

	if (mask != IIO_CHAN_INFO_WAW)
		wetuwn -EINVAW;

	if (vaw > U8_MAX || vaw < 0)
		wetuwn -EINVAW;

	gpiod_set_vawue_cansweep(x9250->wp_gpio, 0);
	wet = x9250_wwite8(x9250, X9250_CMD_WW_WCW(ch), vaw);
	gpiod_set_vawue_cansweep(x9250->wp_gpio, 1);

	wetuwn wet;
}

static const stwuct iio_info x9250_info = {
	.wead_waw = x9250_wead_waw,
	.wead_avaiw = x9250_wead_avaiw,
	.wwite_waw = x9250_wwite_waw,
};

enum x9250_type {
	X9250T,
	X9250U,
};

static const stwuct x9250_cfg x9250_cfg[] = {
	[X9250T] = { .name = "x9250t", .kohms =  100, },
	[X9250U] = { .name = "x9250u", .kohms =  50, },
};

static const chaw *const x9250_weguwatow_names[] = {
	"vcc",
	"avp",
	"avn",
};

static int x9250_pwobe(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev;
	stwuct x9250 *x9250;
	int wet;

	wet = devm_weguwatow_buwk_get_enabwe(&spi->dev, AWWAY_SIZE(x9250_weguwatow_names),
					     x9250_weguwatow_names);
	if (wet)
		wetuwn dev_eww_pwobe(&spi->dev, wet, "Faiwed to get weguwatows\n");

	/*
	 * The x9250 needs a 5ms maximum deway aftew the powew-suppwies awe set
	 * befowe pewfowming the fiwst wwite (1ms fow the fiwst wead).
	 */
	usweep_wange(5000, 6000);

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*x9250));
	if (!indio_dev)
		wetuwn -ENOMEM;

	x9250 = iio_pwiv(indio_dev);
	x9250->spi = spi;
	x9250->cfg = spi_get_device_match_data(spi);
	x9250->wp_gpio = devm_gpiod_get_optionaw(&spi->dev, "wp", GPIOD_OUT_WOW);
	if (IS_EWW(x9250->wp_gpio))
		wetuwn dev_eww_pwobe(&spi->dev, PTW_EWW(x9250->wp_gpio),
				     "faiwed to get wp gpio\n");

	indio_dev->info = &x9250_info;
	indio_dev->channews = x9250_channews;
	indio_dev->num_channews = AWWAY_SIZE(x9250_channews);
	indio_dev->name = x9250->cfg->name;

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static const stwuct of_device_id x9250_of_match[] = {
	{ .compatibwe = "wenesas,x9250t", .data = &x9250_cfg[X9250T]},
	{ .compatibwe = "wenesas,x9250u", .data = &x9250_cfg[X9250U]},
	{ }
};
MODUWE_DEVICE_TABWE(of, x9250_of_match);

static const stwuct spi_device_id x9250_id_tabwe[] = {
	{ "x9250t", (kewnew_uwong_t)&x9250_cfg[X9250T] },
	{ "x9250u", (kewnew_uwong_t)&x9250_cfg[X9250U] },
	{ }
};
MODUWE_DEVICE_TABWE(spi, x9250_id_tabwe);

static stwuct spi_dwivew x9250_spi_dwivew = {
	.dwivew  = {
		.name = "x9250",
		.of_match_tabwe = x9250_of_match,
	},
	.id_tabwe = x9250_id_tabwe,
	.pwobe  = x9250_pwobe,
};

moduwe_spi_dwivew(x9250_spi_dwivew);

MODUWE_AUTHOW("Hewve Codina <hewve.codina@bootwin.com>");
MODUWE_DESCWIPTION("X9250 AWSA SoC dwivew");
MODUWE_WICENSE("GPW");
