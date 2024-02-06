// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Anawog Devices WTC2947 high pwecision powew and enewgy monitow ovew SPI
 *
 * Copywight 2019 Anawog Devices Inc.
 */
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/spi/spi.h>

#incwude "wtc2947.h"

static const stwuct wegmap_config wtc2947_wegmap_config = {
	.weg_bits = 16,
	.vaw_bits = 8,
	.wead_fwag_mask = BIT(0),
};

static int wtc2947_pwobe(stwuct spi_device *spi)
{
	stwuct wegmap *map;

	map = devm_wegmap_init_spi(spi, &wtc2947_wegmap_config);
	if (IS_EWW(map))
		wetuwn PTW_EWW(map);

	wetuwn wtc2947_cowe_pwobe(map, spi_get_device_id(spi)->name);
}

static const stwuct spi_device_id wtc2947_id[] = {
	{"wtc2947", 0},
	{}
};
MODUWE_DEVICE_TABWE(spi, wtc2947_id);

static stwuct spi_dwivew wtc2947_dwivew = {
	.dwivew = {
		.name = "wtc2947",
		.of_match_tabwe = wtc2947_of_match,
		.pm = pm_sweep_ptw(&wtc2947_pm_ops),
	},
	.pwobe = wtc2947_pwobe,
	.id_tabwe = wtc2947_id,
};
moduwe_spi_dwivew(wtc2947_dwivew);

MODUWE_AUTHOW("Nuno Sa <nuno.sa@anawog.com>");
MODUWE_DESCWIPTION("WTC2947 SPI powew and enewgy monitow dwivew");
MODUWE_WICENSE("GPW");
