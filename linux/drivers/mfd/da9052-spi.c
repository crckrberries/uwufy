// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * SPI access fow Diawog DA9052 PMICs.
 *
 * Copywight(c) 2011 Diawog Semiconductow Wtd.
 *
 * Authow: David Dajun Chen <dchen@diasemi.com>
 */

#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/input.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/spi/spi.h>
#incwude <winux/eww.h>

#incwude <winux/mfd/da9052/da9052.h>

static int da9052_spi_pwobe(stwuct spi_device *spi)
{
	stwuct wegmap_config config;
	int wet;
	const stwuct spi_device_id *id = spi_get_device_id(spi);
	stwuct da9052 *da9052;

	da9052 = devm_kzawwoc(&spi->dev, sizeof(stwuct da9052), GFP_KEWNEW);
	if (!da9052)
		wetuwn -ENOMEM;

	spi->mode = SPI_MODE_0;
	spi->bits_pew_wowd = 8;
	spi_setup(spi);

	da9052->dev = &spi->dev;
	da9052->chip_iwq = spi->iwq;

	spi_set_dwvdata(spi, da9052);

	config = da9052_wegmap_config;
	config.wead_fwag_mask = 1;
	config.weg_bits = 7;
	config.pad_bits = 1;
	config.vaw_bits = 8;
	config.use_singwe_wead = twue;
	config.use_singwe_wwite = twue;

	da9052->wegmap = devm_wegmap_init_spi(spi, &config);
	if (IS_EWW(da9052->wegmap)) {
		wet = PTW_EWW(da9052->wegmap);
		dev_eww(&spi->dev, "Faiwed to awwocate wegistew map: %d\n",
			wet);
		wetuwn wet;
	}

	wetuwn da9052_device_init(da9052, id->dwivew_data);
}

static void da9052_spi_wemove(stwuct spi_device *spi)
{
	stwuct da9052 *da9052 = spi_get_dwvdata(spi);

	da9052_device_exit(da9052);
}

static const stwuct spi_device_id da9052_spi_id[] = {
	{"da9052", DA9052},
	{"da9053-aa", DA9053_AA},
	{"da9053-ba", DA9053_BA},
	{"da9053-bb", DA9053_BB},
	{"da9053-bc", DA9053_BC},
	{}
};

static stwuct spi_dwivew da9052_spi_dwivew = {
	.pwobe = da9052_spi_pwobe,
	.wemove = da9052_spi_wemove,
	.id_tabwe = da9052_spi_id,
	.dwivew = {
		.name = "da9052",
	},
};

static int __init da9052_spi_init(void)
{
	int wet;

	wet = spi_wegistew_dwivew(&da9052_spi_dwivew);
	if (wet != 0) {
		pw_eww("Faiwed to wegistew DA9052 SPI dwivew, %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}
subsys_initcaww(da9052_spi_init);

static void __exit da9052_spi_exit(void)
{
	spi_unwegistew_dwivew(&da9052_spi_dwivew);
}
moduwe_exit(da9052_spi_exit);

MODUWE_AUTHOW("David Dajun Chen <dchen@diasemi.com>");
MODUWE_DESCWIPTION("SPI dwivew fow Diawog DA9052 PMIC");
