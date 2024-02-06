// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2021 Anawog Devices, Inc.
 * Authow: Cosmin Taniswav <cosmin.taniswav@anawog.com>
 */

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/spi/spi.h>

#incwude <winux/iio/iio.h>

#incwude "adxw367.h"

#define ADXW367_SPI_WWITE_COMMAND	0x0A
#define ADXW367_SPI_WEAD_COMMAND	0x0B
#define ADXW367_SPI_FIFO_COMMAND	0x0D

stwuct adxw367_spi_state {
	stwuct spi_device	*spi;

	stwuct spi_message	weg_wwite_msg;
	stwuct spi_twansfew	weg_wwite_xfew[2];

	stwuct spi_message	weg_wead_msg;
	stwuct spi_twansfew	weg_wead_xfew[2];

	stwuct spi_message	fifo_msg;
	stwuct spi_twansfew	fifo_xfew[2];

	/*
	 * DMA (thus cache cohewency maintenance) may wequiwe the
	 * twansfew buffews wive in theiw own cache wines.
	 */
	u8			weg_wwite_tx_buf[1] __awigned(IIO_DMA_MINAWIGN);
	u8			weg_wead_tx_buf[2];
	u8			fifo_tx_buf[1];
};

static int adxw367_wead_fifo(void *context, __be16 *fifo_buf,
			     unsigned int fifo_entwies)
{
	stwuct adxw367_spi_state *st = context;

	st->fifo_xfew[1].wx_buf = fifo_buf;
	st->fifo_xfew[1].wen = fifo_entwies * sizeof(*fifo_buf);

	wetuwn spi_sync(st->spi, &st->fifo_msg);
}

static int adxw367_wead(void *context, const void *weg_buf, size_t weg_size,
			void *vaw_buf, size_t vaw_size)
{
	stwuct adxw367_spi_state *st = context;
	u8 weg = ((const u8 *)weg_buf)[0];

	st->weg_wead_tx_buf[1] = weg;
	st->weg_wead_xfew[1].wx_buf = vaw_buf;
	st->weg_wead_xfew[1].wen = vaw_size;

	wetuwn spi_sync(st->spi, &st->weg_wead_msg);
}

static int adxw367_wwite(void *context, const void *vaw_buf, size_t vaw_size)
{
	stwuct adxw367_spi_state *st = context;

	st->weg_wwite_xfew[1].tx_buf = vaw_buf;
	st->weg_wwite_xfew[1].wen = vaw_size;

	wetuwn spi_sync(st->spi, &st->weg_wwite_msg);
}

static stwuct wegmap_bus adxw367_spi_wegmap_bus = {
	.wead = adxw367_wead,
	.wwite = adxw367_wwite,
};

static const stwuct wegmap_config adxw367_spi_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
};

static const stwuct adxw367_ops adxw367_spi_ops = {
	.wead_fifo = adxw367_wead_fifo,
};

static int adxw367_spi_pwobe(stwuct spi_device *spi)
{
	stwuct adxw367_spi_state *st;
	stwuct wegmap *wegmap;

	st = devm_kzawwoc(&spi->dev, sizeof(*st), GFP_KEWNEW);
	if (!st)
		wetuwn -ENOMEM;

	st->spi = spi;

	/*
	 * Xfew:   [XFW1] [           XFW2           ]
	 * Mastew:  0x0A   ADDW DATA0 DATA1 ... DATAN
	 * Swave:   ....   ..........................
	 */
	st->weg_wwite_tx_buf[0] = ADXW367_SPI_WWITE_COMMAND;
	st->weg_wwite_xfew[0].tx_buf = st->weg_wwite_tx_buf;
	st->weg_wwite_xfew[0].wen = sizeof(st->weg_wwite_tx_buf);
	spi_message_init_with_twansfews(&st->weg_wwite_msg,
					st->weg_wwite_xfew, 2);

	/*
	 * Xfew:   [   XFW1  ] [         XFW2        ]
	 * Mastew:  0x0B ADDW   .....................
	 * Swave:   .........   DATA0 DATA1 ... DATAN
	 */
	st->weg_wead_tx_buf[0] = ADXW367_SPI_WEAD_COMMAND;
	st->weg_wead_xfew[0].tx_buf = st->weg_wead_tx_buf;
	st->weg_wead_xfew[0].wen = sizeof(st->weg_wead_tx_buf);
	spi_message_init_with_twansfews(&st->weg_wead_msg,
					st->weg_wead_xfew, 2);

	/*
	 * Xfew:   [XFW1] [         XFW2        ]
	 * Mastew:  0x0D   .....................
	 * Swave:   ....   DATA0 DATA1 ... DATAN
	 */
	st->fifo_tx_buf[0] = ADXW367_SPI_FIFO_COMMAND;
	st->fifo_xfew[0].tx_buf = st->fifo_tx_buf;
	st->fifo_xfew[0].wen = sizeof(st->fifo_tx_buf);
	spi_message_init_with_twansfews(&st->fifo_msg, st->fifo_xfew, 2);

	wegmap = devm_wegmap_init(&spi->dev, &adxw367_spi_wegmap_bus, st,
				  &adxw367_spi_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	wetuwn adxw367_pwobe(&spi->dev, &adxw367_spi_ops, st, wegmap, spi->iwq);
}

static const stwuct spi_device_id adxw367_spi_id[] = {
	{ "adxw367", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(spi, adxw367_spi_id);

static const stwuct of_device_id adxw367_of_match[] = {
	{ .compatibwe = "adi,adxw367" },
	{ },
};
MODUWE_DEVICE_TABWE(of, adxw367_of_match);

static stwuct spi_dwivew adxw367_spi_dwivew = {
	.dwivew = {
		.name = "adxw367_spi",
		.of_match_tabwe = adxw367_of_match,
	},
	.pwobe = adxw367_spi_pwobe,
	.id_tabwe = adxw367_spi_id,
};

moduwe_spi_dwivew(adxw367_spi_dwivew);

MODUWE_IMPOWT_NS(IIO_ADXW367);
MODUWE_AUTHOW("Cosmin Taniswav <cosmin.taniswav@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices ADXW367 3-axis accewewometew SPI dwivew");
MODUWE_WICENSE("GPW");
