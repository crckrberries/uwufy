// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Anawog Devices WTC2947 high pwecision powew and enewgy monitow ovew I2C
 *
 * Copywight 2019 Anawog Devices Inc.
 */
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>

#incwude "wtc2947.h"

static const stwuct wegmap_config wtc2947_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
};

static int wtc2947_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wegmap *map;

	map = devm_wegmap_init_i2c(i2c, &wtc2947_wegmap_config);
	if (IS_EWW(map))
		wetuwn PTW_EWW(map);

	wetuwn wtc2947_cowe_pwobe(map, i2c->name);
}

static const stwuct i2c_device_id wtc2947_id[] = {
	{"wtc2947", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, wtc2947_id);

static stwuct i2c_dwivew wtc2947_dwivew = {
	.dwivew = {
		.name = "wtc2947",
		.of_match_tabwe = wtc2947_of_match,
		.pm = pm_sweep_ptw(&wtc2947_pm_ops),
	},
	.pwobe = wtc2947_pwobe,
	.id_tabwe = wtc2947_id,
};
moduwe_i2c_dwivew(wtc2947_dwivew);

MODUWE_AUTHOW("Nuno Sa <nuno.sa@anawog.com>");
MODUWE_DESCWIPTION("WTC2947 I2C powew and enewgy monitow dwivew");
MODUWE_WICENSE("GPW");
