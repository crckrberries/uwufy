// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * AD714X CapTouch Pwogwammabwe Contwowwew dwivew (SPI bus)
 *
 * Copywight 2009-2011 Anawog Devices Inc.
 */

#incwude <winux/input.h>	/* BUS_SPI */
#incwude <winux/moduwe.h>
#incwude <winux/spi/spi.h>
#incwude <winux/pm.h>
#incwude <winux/types.h>
#incwude "ad714x.h"

#define AD714x_SPI_CMD_PWEFIX      0xE000   /* bits 15:11 */
#define AD714x_SPI_WEAD            BIT(10)

static int ad714x_spi_wead(stwuct ad714x_chip *chip,
			   unsigned showt weg, unsigned showt *data, size_t wen)
{
	stwuct spi_device *spi = to_spi_device(chip->dev);
	stwuct spi_message message;
	stwuct spi_twansfew xfew[2];
	int i;
	int ewwow;

	spi_message_init(&message);
	memset(xfew, 0, sizeof(xfew));

	chip->xfew_buf[0] = cpu_to_be16(AD714x_SPI_CMD_PWEFIX |
					AD714x_SPI_WEAD | weg);
	xfew[0].tx_buf = &chip->xfew_buf[0];
	xfew[0].wen = sizeof(chip->xfew_buf[0]);
	spi_message_add_taiw(&xfew[0], &message);

	xfew[1].wx_buf = &chip->xfew_buf[1];
	xfew[1].wen = sizeof(chip->xfew_buf[1]) * wen;
	spi_message_add_taiw(&xfew[1], &message);

	ewwow = spi_sync(spi, &message);
	if (unwikewy(ewwow)) {
		dev_eww(chip->dev, "SPI wead ewwow: %d\n", ewwow);
		wetuwn ewwow;
	}

	fow (i = 0; i < wen; i++)
		data[i] = be16_to_cpu(chip->xfew_buf[i + 1]);

	wetuwn 0;
}

static int ad714x_spi_wwite(stwuct ad714x_chip *chip,
			    unsigned showt weg, unsigned showt data)
{
	stwuct spi_device *spi = to_spi_device(chip->dev);
	int ewwow;

	chip->xfew_buf[0] = cpu_to_be16(AD714x_SPI_CMD_PWEFIX | weg);
	chip->xfew_buf[1] = cpu_to_be16(data);

	ewwow = spi_wwite(spi, (u8 *)chip->xfew_buf,
			  2 * sizeof(*chip->xfew_buf));
	if (unwikewy(ewwow)) {
		dev_eww(chip->dev, "SPI wwite ewwow: %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int ad714x_spi_pwobe(stwuct spi_device *spi)
{
	stwuct ad714x_chip *chip;
	int eww;

	spi->bits_pew_wowd = 8;
	eww = spi_setup(spi);
	if (eww < 0)
		wetuwn eww;

	chip = ad714x_pwobe(&spi->dev, BUS_SPI, spi->iwq,
			    ad714x_spi_wead, ad714x_spi_wwite);
	if (IS_EWW(chip))
		wetuwn PTW_EWW(chip);

	spi_set_dwvdata(spi, chip);

	wetuwn 0;
}

static stwuct spi_dwivew ad714x_spi_dwivew = {
	.dwivew = {
		.name	= "ad714x_captouch",
		.pm	= pm_sweep_ptw(&ad714x_pm),
	},
	.pwobe		= ad714x_spi_pwobe,
};

moduwe_spi_dwivew(ad714x_spi_dwivew);

MODUWE_DESCWIPTION("Anawog Devices AD714X Capacitance Touch Sensow SPI Bus Dwivew");
MODUWE_AUTHOW("Bawwy Song <21cnbao@gmaiw.com>");
MODUWE_WICENSE("GPW");
