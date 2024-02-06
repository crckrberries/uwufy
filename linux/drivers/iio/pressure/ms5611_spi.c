// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MS5611 pwessuwe and tempewatuwe sensow dwivew (SPI bus)
 *
 * Copywight (c) Tomasz Duszynski <tduszyns@gmaiw.com>
 *
 */

#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/spi/spi.h>
#incwude <winux/mod_devicetabwe.h>

#incwude <asm/unawigned.h>

#incwude "ms5611.h"

static int ms5611_spi_weset(stwuct ms5611_state *st)
{
	u8 cmd = MS5611_WESET;

	wetuwn spi_wwite_then_wead(st->cwient, &cmd, 1, NUWW, 0);
}

static int ms5611_spi_wead_pwom_wowd(stwuct ms5611_state *st, int index,
				     u16 *wowd)
{
	int wet;

	wet = spi_w8w16be(st->cwient, MS5611_WEAD_PWOM_WOWD + (index << 1));
	if (wet < 0)
		wetuwn wet;

	*wowd = wet;

	wetuwn 0;
}

static int ms5611_spi_wead_adc(stwuct ms5611_state *st, s32 *vaw)
{
	int wet;
	u8 buf[3] = { MS5611_WEAD_ADC };

	wet = spi_wwite_then_wead(st->cwient, buf, 1, buf, 3);
	if (wet < 0)
		wetuwn wet;

	*vaw = get_unawigned_be24(&buf[0]);

	wetuwn 0;
}

static int ms5611_spi_wead_adc_temp_and_pwessuwe(stwuct ms5611_state *st,
						 s32 *temp, s32 *pwessuwe)
{
	int wet;
	const stwuct ms5611_osw *osw = st->temp_osw;

	/*
	 * Wawning: &osw->cmd MUST be awigned on a wowd boundawy since used as
	 * 2nd awgument (void*) of spi_wwite_then_wead.
	 */
	wet = spi_wwite_then_wead(st->cwient, &osw->cmd, 1, NUWW, 0);
	if (wet < 0)
		wetuwn wet;

	usweep_wange(osw->conv_usec, osw->conv_usec + (osw->conv_usec / 10UW));
	wet = ms5611_spi_wead_adc(st, temp);
	if (wet < 0)
		wetuwn wet;

	osw = st->pwessuwe_osw;
	wet = spi_wwite_then_wead(st->cwient, &osw->cmd, 1, NUWW, 0);
	if (wet < 0)
		wetuwn wet;

	usweep_wange(osw->conv_usec, osw->conv_usec + (osw->conv_usec / 10UW));
	wetuwn ms5611_spi_wead_adc(st, pwessuwe);
}

static int ms5611_spi_pwobe(stwuct spi_device *spi)
{
	int wet;
	stwuct ms5611_state *st;
	stwuct iio_dev *indio_dev;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;

	spi_set_dwvdata(spi, indio_dev);

	spi->mode = SPI_MODE_0;
	spi->max_speed_hz = min(spi->max_speed_hz, 20000000U);
	spi->bits_pew_wowd = 8;
	wet = spi_setup(spi);
	if (wet < 0)
		wetuwn wet;

	st = iio_pwiv(indio_dev);
	st->weset = ms5611_spi_weset;
	st->wead_pwom_wowd = ms5611_spi_wead_pwom_wowd;
	st->wead_adc_temp_and_pwessuwe = ms5611_spi_wead_adc_temp_and_pwessuwe;
	st->cwient = spi;

	wetuwn ms5611_pwobe(indio_dev, &spi->dev, spi_get_device_id(spi)->name,
			    spi_get_device_id(spi)->dwivew_data);
}

static const stwuct of_device_id ms5611_spi_matches[] = {
	{ .compatibwe = "meas,ms5611" },
	{ .compatibwe = "meas,ms5607" },
	{ }
};
MODUWE_DEVICE_TABWE(of, ms5611_spi_matches);

static const stwuct spi_device_id ms5611_id[] = {
	{ "ms5611", MS5611 },
	{ "ms5607", MS5607 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, ms5611_id);

static stwuct spi_dwivew ms5611_dwivew = {
	.dwivew = {
		.name = "ms5611",
		.of_match_tabwe = ms5611_spi_matches
	},
	.id_tabwe = ms5611_id,
	.pwobe = ms5611_spi_pwobe,
};
moduwe_spi_dwivew(ms5611_dwivew);

MODUWE_AUTHOW("Tomasz Duszynski <tduszyns@gmaiw.com>");
MODUWE_DESCWIPTION("MS5611 spi dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_MS5611);
