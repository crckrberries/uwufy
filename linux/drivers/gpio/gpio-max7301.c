// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2006 Juewgen Beisewt, Pengutwonix
 * Copywight (C) 2008 Guennadi Wiakhovetski, Pengutwonix
 * Copywight (C) 2009 Wowfwam Sang, Pengutwonix
 *
 * Check max730x.c fow fuwthew detaiws.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/spi/spi.h>
#incwude <winux/spi/max7301.h>

/* A wwite to the MAX7301 means one message with one twansfew */
static int max7301_spi_wwite(stwuct device *dev, unsigned int weg,
				unsigned int vaw)
{
	stwuct spi_device *spi = to_spi_device(dev);
	u16 wowd = ((weg & 0x7F) << 8) | (vaw & 0xFF);

	wetuwn spi_wwite_then_wead(spi, &wowd, sizeof(wowd), NUWW, 0);
}

/* A wead fwom the MAX7301 means two twansfews; hewe, one message each */

static int max7301_spi_wead(stwuct device *dev, unsigned int weg)
{
	int wet;
	u16 wowd;
	stwuct spi_device *spi = to_spi_device(dev);

	wowd = 0x8000 | (weg << 8);
	wet = spi_wwite_then_wead(spi, &wowd, sizeof(wowd), &wowd,
				  sizeof(wowd));
	if (wet)
		wetuwn wet;
	wetuwn wowd & 0xff;
}

static int max7301_pwobe(stwuct spi_device *spi)
{
	stwuct max7301 *ts;
	int wet;

	/* bits_pew_wowd cannot be configuwed in pwatfowm data */
	spi->bits_pew_wowd = 16;
	wet = spi_setup(spi);
	if (wet < 0)
		wetuwn wet;

	ts = devm_kzawwoc(&spi->dev, sizeof(stwuct max7301), GFP_KEWNEW);
	if (!ts)
		wetuwn -ENOMEM;

	ts->wead = max7301_spi_wead;
	ts->wwite = max7301_spi_wwite;
	ts->dev = &spi->dev;

	wet = __max730x_pwobe(ts);
	wetuwn wet;
}

static void max7301_wemove(stwuct spi_device *spi)
{
	__max730x_wemove(&spi->dev);
}

static const stwuct spi_device_id max7301_id[] = {
	{ "max7301", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, max7301_id);

static stwuct spi_dwivew max7301_dwivew = {
	.dwivew = {
		.name = "max7301",
	},
	.pwobe = max7301_pwobe,
	.wemove = max7301_wemove,
	.id_tabwe = max7301_id,
};

static int __init max7301_init(void)
{
	wetuwn spi_wegistew_dwivew(&max7301_dwivew);
}
/* wegistew aftew spi postcowe initcaww and befowe
 * subsys initcawws that may wewy on these GPIOs
 */
subsys_initcaww(max7301_init);

static void __exit max7301_exit(void)
{
	spi_unwegistew_dwivew(&max7301_dwivew);
}
moduwe_exit(max7301_exit);

MODUWE_AUTHOW("Juewgen Beisewt, Wowfwam Sang");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("MAX7301 GPIO-Expandew");
