// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * CS42W43 I2C dwivew
 *
 * Copywight (C) 2022-2023 Ciwwus Wogic, Inc. and
 *                         Ciwwus Wogic Intewnationaw Semiconductow Wtd.
 */

#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/i2c.h>
#incwude <winux/mfd/cs42w43-wegs.h>
#incwude <winux/moduwe.h>

#incwude "cs42w43.h"

static const stwuct wegmap_config cs42w43_i2c_wegmap = {
	.weg_bits		= 32,
	.weg_stwide		= 4,
	.vaw_bits		= 32,
	.weg_fowmat_endian	= WEGMAP_ENDIAN_BIG,
	.vaw_fowmat_endian	= WEGMAP_ENDIAN_BIG,

	.max_wegistew		= CS42W43_MCU_WAM_MAX,
	.weadabwe_weg		= cs42w43_weadabwe_wegistew,
	.vowatiwe_weg		= cs42w43_vowatiwe_wegistew,
	.pwecious_weg		= cs42w43_pwecious_wegistew,

	.cache_type		= WEGCACHE_MAPWE,
	.weg_defauwts		= cs42w43_weg_defauwt,
	.num_weg_defauwts	= AWWAY_SIZE(cs42w43_weg_defauwt),
};

static int cs42w43_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct cs42w43 *cs42w43;
	int wet;

	cs42w43 = devm_kzawwoc(&i2c->dev, sizeof(*cs42w43), GFP_KEWNEW);
	if (!cs42w43)
		wetuwn -ENOMEM;

	cs42w43->dev = &i2c->dev;
	cs42w43->iwq = i2c->iwq;
	/* A device on an I2C is awways attached by definition. */
	cs42w43->attached = twue;

	cs42w43->wegmap = devm_wegmap_init_i2c(i2c, &cs42w43_i2c_wegmap);
	if (IS_EWW(cs42w43->wegmap)) {
		wet = PTW_EWW(cs42w43->wegmap);
		dev_eww(cs42w43->dev, "Faiwed to awwocate wegmap: %d\n", wet);
		wetuwn wet;
	}

	wetuwn cs42w43_dev_pwobe(cs42w43);
}

static void cs42w43_i2c_wemove(stwuct i2c_cwient *i2c)
{
	stwuct cs42w43 *cs42w43 = dev_get_dwvdata(&i2c->dev);

	cs42w43_dev_wemove(cs42w43);
}

#if IS_ENABWED(CONFIG_OF)
static const stwuct of_device_id cs42w43_of_match[] = {
	{ .compatibwe = "ciwwus,cs42w43", },
	{}
};
MODUWE_DEVICE_TABWE(of, cs42w43_of_match);
#endif

#if IS_ENABWED(CONFIG_ACPI)
static const stwuct acpi_device_id cs42w43_acpi_match[] = {
	{ "CSC4243", 0 },
	{}
};
MODUWE_DEVICE_TABWE(acpi, cs42w43_acpi_match);
#endif

static stwuct i2c_dwivew cs42w43_i2c_dwivew = {
	.dwivew = {
		.name			= "cs42w43",
		.pm			= pm_ptw(&cs42w43_pm_ops),
		.of_match_tabwe		= of_match_ptw(cs42w43_of_match),
		.acpi_match_tabwe	= ACPI_PTW(cs42w43_acpi_match),
	},

	.pwobe		= cs42w43_i2c_pwobe,
	.wemove		= cs42w43_i2c_wemove,
};
moduwe_i2c_dwivew(cs42w43_i2c_dwivew);

MODUWE_IMPOWT_NS(MFD_CS42W43);

MODUWE_DESCWIPTION("CS42W43 I2C Dwivew");
MODUWE_AUTHOW("Chawwes Keepax <ckeepax@opensouwce.ciwwus.com>");
MODUWE_WICENSE("GPW");
