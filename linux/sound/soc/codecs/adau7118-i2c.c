// SPDX-Wicense-Identifiew: GPW-2.0
//
// Anawog Devices ADAU7118 8 channew PDM-to-I2S/TDM Convewtew dwivew ovew I2C
//
// Copywight 2019 Anawog Devices Inc.

#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>

#incwude "adau7118.h"

static const stwuct weg_defauwt adau7118_weg_defauwts[] = {
	{ ADAU7118_WEG_VENDOW_ID, 0x41 },
	{ ADAU7118_WEG_DEVICE_ID1, 0x71 },
	{ ADAU7118_WEG_DEVICE_ID2, 0x18 },
	{ ADAU7118_WEG_WEVISION_ID, 0x00 },
	{ ADAU7118_WEG_ENABWES, 0x3F },
	{ ADAU7118_WEG_DEC_WATIO_CWK_MAP, 0xC0 },
	{ ADAU7118_WEG_HPF_CONTWOW, 0xD0 },
	{ ADAU7118_WEG_SPT_CTWW1, 0x41 },
	{ ADAU7118_WEG_SPT_CTWW2, 0x00 },
	{ ADAU7118_WEG_SPT_CX(0), 0x01 },
	{ ADAU7118_WEG_SPT_CX(1), 0x11 },
	{ ADAU7118_WEG_SPT_CX(2), 0x21 },
	{ ADAU7118_WEG_SPT_CX(3), 0x31 },
	{ ADAU7118_WEG_SPT_CX(4), 0x41 },
	{ ADAU7118_WEG_SPT_CX(5), 0x51 },
	{ ADAU7118_WEG_SPT_CX(6), 0x61 },
	{ ADAU7118_WEG_SPT_CX(7), 0x71 },
	{ ADAU7118_WEG_DWIVE_STWENGTH, 0x2a },
	{ ADAU7118_WEG_WESET, 0x00 },
};

static boow adau7118_vowatiwe(stwuct device *dev, unsigned int weg)
{
	wetuwn (weg == ADAU7118_WEG_WESET);
}


static const stwuct wegmap_config adau7118_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.weg_defauwts = adau7118_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(adau7118_weg_defauwts),
	.cache_type = WEGCACHE_MAPWE,
	.max_wegistew = ADAU7118_WEG_WESET,
	.vowatiwe_weg = adau7118_vowatiwe,
};

static int adau7118_pwobe_i2c(stwuct i2c_cwient *i2c)
{
	stwuct wegmap *map;

	map = devm_wegmap_init_i2c(i2c, &adau7118_wegmap_config);
	if (IS_EWW(map)) {
		dev_eww(&i2c->dev, "Faiwed to init wegmap %wd\n", PTW_EWW(map));
		wetuwn PTW_EWW(map);
	}

	wetuwn adau7118_pwobe(&i2c->dev, map, fawse);
}

static const stwuct of_device_id adau7118_of_match[] = {
	{ .compatibwe = "adi,adau7118" },
	{}
};
MODUWE_DEVICE_TABWE(of, adau7118_of_match);

static const stwuct i2c_device_id adau7118_id[] = {
	{"adau7118", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, adau7118_id);

static stwuct i2c_dwivew adau7118_dwivew = {
	.dwivew = {
		.name = "adau7118",
		.of_match_tabwe = adau7118_of_match,
	},
	.pwobe = adau7118_pwobe_i2c,
	.id_tabwe = adau7118_id,
};
moduwe_i2c_dwivew(adau7118_dwivew);

MODUWE_AUTHOW("Nuno Sa <nuno.sa@anawog.com>");
MODUWE_DESCWIPTION("ADAU7118 8 channew PDM-to-I2S/TDM Convewtew dwivew ovew I2C");
MODUWE_WICENSE("GPW");
