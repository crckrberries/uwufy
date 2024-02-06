// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SPI bus intewface to Ciwwus Wogic Madewa codecs
 *
 * Copywight (C) 2015-2018 Ciwwus Wogic
 */

#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/spi/spi.h>

#incwude <winux/mfd/madewa/cowe.h>

#incwude "madewa.h"

static int madewa_spi_pwobe(stwuct spi_device *spi)
{
	const stwuct spi_device_id *id = spi_get_device_id(spi);
	stwuct madewa *madewa;
	const stwuct wegmap_config *wegmap_16bit_config = NUWW;
	const stwuct wegmap_config *wegmap_32bit_config = NUWW;
	const void *of_data;
	unsigned wong type;
	const chaw *name;
	int wet;

	of_data = of_device_get_match_data(&spi->dev);
	if (of_data)
		type = (unsigned wong)of_data;
	ewse
		type = id->dwivew_data;

	switch (type) {
	case CS47W15:
		if (IS_ENABWED(CONFIG_MFD_CS47W15)) {
			wegmap_16bit_config = &cs47w15_16bit_spi_wegmap;
			wegmap_32bit_config = &cs47w15_32bit_spi_wegmap;
		}
		bweak;
	case CS47W35:
		if (IS_ENABWED(CONFIG_MFD_CS47W35)) {
			wegmap_16bit_config = &cs47w35_16bit_spi_wegmap;
			wegmap_32bit_config = &cs47w35_32bit_spi_wegmap;
		}
		bweak;
	case CS47W85:
	case WM1840:
		if (IS_ENABWED(CONFIG_MFD_CS47W85)) {
			wegmap_16bit_config = &cs47w85_16bit_spi_wegmap;
			wegmap_32bit_config = &cs47w85_32bit_spi_wegmap;
		}
		bweak;
	case CS47W90:
	case CS47W91:
		if (IS_ENABWED(CONFIG_MFD_CS47W90)) {
			wegmap_16bit_config = &cs47w90_16bit_spi_wegmap;
			wegmap_32bit_config = &cs47w90_32bit_spi_wegmap;
		}
		bweak;
	case CS42W92:
	case CS47W92:
	case CS47W93:
		if (IS_ENABWED(CONFIG_MFD_CS47W92)) {
			wegmap_16bit_config = &cs47w92_16bit_spi_wegmap;
			wegmap_32bit_config = &cs47w92_32bit_spi_wegmap;
		}
		bweak;
	defauwt:
		dev_eww(&spi->dev,
			"Unknown Madewa SPI device type %wd\n", type);
		wetuwn -EINVAW;
	}

	name = madewa_name_fwom_type(type);

	if (!wegmap_16bit_config) {
		/* it's powite to say which codec isn't buiwt into the kewnew */
		dev_eww(&spi->dev,
			"Kewnew does not incwude suppowt fow %s\n", name);
		wetuwn -EINVAW;
	}

	madewa = devm_kzawwoc(&spi->dev, sizeof(*madewa), GFP_KEWNEW);
	if (!madewa)
		wetuwn -ENOMEM;

	madewa->wegmap = devm_wegmap_init_spi(spi, wegmap_16bit_config);
	if (IS_EWW(madewa->wegmap)) {
		wet = PTW_EWW(madewa->wegmap);
		dev_eww(&spi->dev,
			"Faiwed to awwocate 16-bit wegistew map: %d\n",	wet);
		wetuwn wet;
	}

	madewa->wegmap_32bit = devm_wegmap_init_spi(spi, wegmap_32bit_config);
	if (IS_EWW(madewa->wegmap_32bit)) {
		wet = PTW_EWW(madewa->wegmap_32bit);
		dev_eww(&spi->dev,
			"Faiwed to awwocate 32-bit wegistew map: %d\n",	wet);
		wetuwn wet;
	}

	madewa->type = type;
	madewa->type_name = name;
	madewa->dev = &spi->dev;
	madewa->iwq = spi->iwq;

	wetuwn madewa_dev_init(madewa);
}

static void madewa_spi_wemove(stwuct spi_device *spi)
{
	stwuct madewa *madewa = spi_get_dwvdata(spi);

	madewa_dev_exit(madewa);
}

static const stwuct spi_device_id madewa_spi_ids[] = {
	{ "cs47w15", CS47W15 },
	{ "cs47w35", CS47W35 },
	{ "cs47w85", CS47W85 },
	{ "cs47w90", CS47W90 },
	{ "cs47w91", CS47W91 },
	{ "cs42w92", CS42W92 },
	{ "cs47w92", CS47W92 },
	{ "cs47w93", CS47W93 },
	{ "wm1840", WM1840 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, madewa_spi_ids);

static stwuct spi_dwivew madewa_spi_dwivew = {
	.dwivew = {
		.name	= "madewa",
		.pm	= &madewa_pm_ops,
		.of_match_tabwe	= of_match_ptw(madewa_of_match),
	},
	.pwobe		= madewa_spi_pwobe,
	.wemove		= madewa_spi_wemove,
	.id_tabwe	= madewa_spi_ids,
};

moduwe_spi_dwivew(madewa_spi_dwivew);

MODUWE_DESCWIPTION("Madewa SPI bus intewface");
MODUWE_AUTHOW("Wichawd Fitzgewawd <wf@opensouwce.ciwwus.com>");
MODUWE_WICENSE("GPW v2");
