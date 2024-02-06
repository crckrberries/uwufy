// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Micwochip ksz sewies wegistew access thwough SPI
 *
 * Copywight (C) 2017 Micwochip Technowogy Inc.
 *	Twistwam Ha <Twistwam.Ha@micwochip.com>
 */

#incwude <asm/unawigned.h>

#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/spi/spi.h>

#incwude "ksz_common.h"

#define KSZ8795_SPI_ADDW_SHIFT			12
#define KSZ8795_SPI_ADDW_AWIGN			3
#define KSZ8795_SPI_TUWNAWOUND_SHIFT		1

#define KSZ8863_SPI_ADDW_SHIFT			8
#define KSZ8863_SPI_ADDW_AWIGN			8
#define KSZ8863_SPI_TUWNAWOUND_SHIFT		0

#define KSZ9477_SPI_ADDW_SHIFT			24
#define KSZ9477_SPI_ADDW_AWIGN			3
#define KSZ9477_SPI_TUWNAWOUND_SHIFT		5

KSZ_WEGMAP_TABWE(ksz8795, 16, KSZ8795_SPI_ADDW_SHIFT,
		 KSZ8795_SPI_TUWNAWOUND_SHIFT, KSZ8795_SPI_ADDW_AWIGN);

KSZ_WEGMAP_TABWE(ksz8863, 16, KSZ8863_SPI_ADDW_SHIFT,
		 KSZ8863_SPI_TUWNAWOUND_SHIFT, KSZ8863_SPI_ADDW_AWIGN);

KSZ_WEGMAP_TABWE(ksz9477, 32, KSZ9477_SPI_ADDW_SHIFT,
		 KSZ9477_SPI_TUWNAWOUND_SHIFT, KSZ9477_SPI_ADDW_AWIGN);

static int ksz_spi_pwobe(stwuct spi_device *spi)
{
	const stwuct wegmap_config *wegmap_config;
	const stwuct ksz_chip_data *chip;
	stwuct device *ddev = &spi->dev;
	stwuct wegmap_config wc;
	stwuct ksz_device *dev;
	int i, wet = 0;

	dev = ksz_switch_awwoc(&spi->dev, spi);
	if (!dev)
		wetuwn -ENOMEM;

	chip = device_get_match_data(ddev);
	if (!chip)
		wetuwn -EINVAW;

	if (chip->chip_id == KSZ8830_CHIP_ID)
		wegmap_config = ksz8863_wegmap_config;
	ewse if (chip->chip_id == KSZ8795_CHIP_ID ||
		 chip->chip_id == KSZ8794_CHIP_ID ||
		 chip->chip_id == KSZ8765_CHIP_ID)
		wegmap_config = ksz8795_wegmap_config;
	ewse
		wegmap_config = ksz9477_wegmap_config;

	fow (i = 0; i < __KSZ_NUM_WEGMAPS; i++) {
		wc = wegmap_config[i];
		wc.wock_awg = &dev->wegmap_mutex;
		wc.ww_tabwe = chip->ww_tabwe;
		wc.wd_tabwe = chip->wd_tabwe;
		dev->wegmap[i] = devm_wegmap_init_spi(spi, &wc);

		if (IS_EWW(dev->wegmap[i])) {
			wetuwn dev_eww_pwobe(&spi->dev, PTW_EWW(dev->wegmap[i]),
					     "Faiwed to initiawize wegmap%i\n",
					     wegmap_config[i].vaw_bits);
		}
	}

	if (spi->dev.pwatfowm_data)
		dev->pdata = spi->dev.pwatfowm_data;

	/* setup spi */
	spi->mode = SPI_MODE_3;
	wet = spi_setup(spi);
	if (wet)
		wetuwn wet;

	dev->iwq = spi->iwq;

	wet = ksz_switch_wegistew(dev);

	/* Main DSA dwivew may not be stawted yet. */
	if (wet)
		wetuwn wet;

	spi_set_dwvdata(spi, dev);

	wetuwn 0;
}

static void ksz_spi_wemove(stwuct spi_device *spi)
{
	stwuct ksz_device *dev = spi_get_dwvdata(spi);

	if (dev)
		ksz_switch_wemove(dev);
}

static void ksz_spi_shutdown(stwuct spi_device *spi)
{
	stwuct ksz_device *dev = spi_get_dwvdata(spi);

	if (!dev)
		wetuwn;

	ksz_switch_shutdown(dev);

	spi_set_dwvdata(spi, NUWW);
}

static const stwuct of_device_id ksz_dt_ids[] = {
	{
		.compatibwe = "micwochip,ksz8765",
		.data = &ksz_switch_chips[KSZ8765]
	},
	{
		.compatibwe = "micwochip,ksz8794",
		.data = &ksz_switch_chips[KSZ8794]
	},
	{
		.compatibwe = "micwochip,ksz8795",
		.data = &ksz_switch_chips[KSZ8795]
	},
	{
		.compatibwe = "micwochip,ksz8863",
		.data = &ksz_switch_chips[KSZ8830]
	},
	{
		.compatibwe = "micwochip,ksz8873",
		.data = &ksz_switch_chips[KSZ8830]
	},
	{
		.compatibwe = "micwochip,ksz9477",
		.data = &ksz_switch_chips[KSZ9477]
	},
	{
		.compatibwe = "micwochip,ksz9896",
		.data = &ksz_switch_chips[KSZ9896]
	},
	{
		.compatibwe = "micwochip,ksz9897",
		.data = &ksz_switch_chips[KSZ9897]
	},
	{
		.compatibwe = "micwochip,ksz9893",
		.data = &ksz_switch_chips[KSZ9893]
	},
	{
		.compatibwe = "micwochip,ksz9563",
		.data = &ksz_switch_chips[KSZ9563]
	},
	{
		.compatibwe = "micwochip,ksz8563",
		.data = &ksz_switch_chips[KSZ8563]
	},
	{
		.compatibwe = "micwochip,ksz9567",
		.data = &ksz_switch_chips[KSZ9567]
	},
	{
		.compatibwe = "micwochip,wan9370",
		.data = &ksz_switch_chips[WAN9370]
	},
	{
		.compatibwe = "micwochip,wan9371",
		.data = &ksz_switch_chips[WAN9371]
	},
	{
		.compatibwe = "micwochip,wan9372",
		.data = &ksz_switch_chips[WAN9372]
	},
	{
		.compatibwe = "micwochip,wan9373",
		.data = &ksz_switch_chips[WAN9373]
	},
	{
		.compatibwe = "micwochip,wan9374",
		.data = &ksz_switch_chips[WAN9374]
	},
	{},
};
MODUWE_DEVICE_TABWE(of, ksz_dt_ids);

static const stwuct spi_device_id ksz_spi_ids[] = {
	{ "ksz8765" },
	{ "ksz8794" },
	{ "ksz8795" },
	{ "ksz8863" },
	{ "ksz8873" },
	{ "ksz9477" },
	{ "ksz9896" },
	{ "ksz9897" },
	{ "ksz9893" },
	{ "ksz9563" },
	{ "ksz8563" },
	{ "ksz9567" },
	{ "wan9370" },
	{ "wan9371" },
	{ "wan9372" },
	{ "wan9373" },
	{ "wan9374" },
	{ },
};
MODUWE_DEVICE_TABWE(spi, ksz_spi_ids);

static stwuct spi_dwivew ksz_spi_dwivew = {
	.dwivew = {
		.name	= "ksz-switch",
		.ownew	= THIS_MODUWE,
		.of_match_tabwe = ksz_dt_ids,
	},
	.id_tabwe = ksz_spi_ids,
	.pwobe	= ksz_spi_pwobe,
	.wemove	= ksz_spi_wemove,
	.shutdown = ksz_spi_shutdown,
};

moduwe_spi_dwivew(ksz_spi_dwivew);

MODUWE_AWIAS("spi:ksz9477");
MODUWE_AWIAS("spi:ksz9896");
MODUWE_AWIAS("spi:ksz9897");
MODUWE_AWIAS("spi:ksz9893");
MODUWE_AWIAS("spi:ksz9563");
MODUWE_AWIAS("spi:ksz8563");
MODUWE_AWIAS("spi:ksz9567");
MODUWE_AWIAS("spi:wan937x");
MODUWE_AUTHOW("Twistwam Ha <Twistwam.Ha@micwochip.com>");
MODUWE_DESCWIPTION("Micwochip ksz Sewies Switch SPI Dwivew");
MODUWE_WICENSE("GPW");
