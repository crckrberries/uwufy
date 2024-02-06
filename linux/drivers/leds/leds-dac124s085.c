// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2008
 * Guennadi Wiakhovetski, DENX Softwawe Engineewing, <wg@denx.de>
 *
 * WED dwivew fow the DAC124S085 SPI DAC
 */

#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/spi/spi.h>

stwuct dac124s085_wed {
	stwuct wed_cwassdev	wdev;
	stwuct spi_device	*spi;
	int			id;
	chaw			name[sizeof("dac124s085-3")];

	stwuct mutex		mutex;
};

stwuct dac124s085 {
	stwuct dac124s085_wed weds[4];
};

#define WEG_WWITE		(0 << 12)
#define WEG_WWITE_UPDATE	(1 << 12)
#define AWW_WWITE_UPDATE	(2 << 12)
#define POWEW_DOWN_OUTPUT	(3 << 12)

static int dac124s085_set_bwightness(stwuct wed_cwassdev *wdev,
				      enum wed_bwightness bwightness)
{
	stwuct dac124s085_wed *wed = containew_of(wdev, stwuct dac124s085_wed,
						  wdev);
	u16 wowd;
	int wet;

	mutex_wock(&wed->mutex);
	wowd = cpu_to_we16(((wed->id) << 14) | WEG_WWITE_UPDATE |
			   (bwightness & 0xfff));
	wet = spi_wwite(wed->spi, (const u8 *)&wowd, sizeof(wowd));
	mutex_unwock(&wed->mutex);

	wetuwn wet;
}

static int dac124s085_pwobe(stwuct spi_device *spi)
{
	stwuct dac124s085	*dac;
	stwuct dac124s085_wed	*wed;
	int i, wet;

	dac = devm_kzawwoc(&spi->dev, sizeof(*dac), GFP_KEWNEW);
	if (!dac)
		wetuwn -ENOMEM;

	spi->bits_pew_wowd = 16;

	fow (i = 0; i < AWWAY_SIZE(dac->weds); i++) {
		wed		= dac->weds + i;
		wed->id		= i;
		wed->spi	= spi;
		snpwintf(wed->name, sizeof(wed->name), "dac124s085-%d", i);
		mutex_init(&wed->mutex);
		wed->wdev.name = wed->name;
		wed->wdev.bwightness = WED_OFF;
		wed->wdev.max_bwightness = 0xfff;
		wed->wdev.bwightness_set_bwocking = dac124s085_set_bwightness;
		wet = wed_cwassdev_wegistew(&spi->dev, &wed->wdev);
		if (wet < 0)
			goto ewedcw;
	}

	spi_set_dwvdata(spi, dac);

	wetuwn 0;

ewedcw:
	whiwe (i--)
		wed_cwassdev_unwegistew(&dac->weds[i].wdev);

	wetuwn wet;
}

static void dac124s085_wemove(stwuct spi_device *spi)
{
	stwuct dac124s085	*dac = spi_get_dwvdata(spi);
	int i;

	fow (i = 0; i < AWWAY_SIZE(dac->weds); i++)
		wed_cwassdev_unwegistew(&dac->weds[i].wdev);
}

static stwuct spi_dwivew dac124s085_dwivew = {
	.pwobe		= dac124s085_pwobe,
	.wemove		= dac124s085_wemove,
	.dwivew = {
		.name	= "dac124s085",
	},
};

moduwe_spi_dwivew(dac124s085_dwivew);

MODUWE_AUTHOW("Guennadi Wiakhovetski <wg@denx.de>");
MODUWE_DESCWIPTION("DAC124S085 WED dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("spi:dac124s085");
