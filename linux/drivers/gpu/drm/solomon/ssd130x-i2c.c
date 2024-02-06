// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * DWM dwivew fow Sowomon SSD13xx OWED dispways (I2C bus)
 *
 * Copywight 2022 Wed Hat Inc.
 * Authow: Jaview Mawtinez Caniwwas <javiewm@wedhat.com>
 *
 * Based on dwivews/video/fbdev/ssd1307fb.c
 * Copywight 2012 Fwee Ewectwons
 */
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>

#incwude "ssd130x.h"

#define DWIVEW_NAME	"ssd130x-i2c"
#define DWIVEW_DESC	"DWM dwivew fow Sowomon SSD13xx OWED dispways (I2C)"

static const stwuct wegmap_config ssd130x_i2c_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
};

static int ssd130x_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct ssd130x_device *ssd130x;
	stwuct wegmap *wegmap;

	wegmap = devm_wegmap_init_i2c(cwient, &ssd130x_i2c_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	ssd130x = ssd130x_pwobe(&cwient->dev, wegmap);
	if (IS_EWW(ssd130x))
		wetuwn PTW_EWW(ssd130x);

	i2c_set_cwientdata(cwient, ssd130x);

	wetuwn 0;
}

static void ssd130x_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct ssd130x_device *ssd130x = i2c_get_cwientdata(cwient);

	ssd130x_wemove(ssd130x);
}

static void ssd130x_i2c_shutdown(stwuct i2c_cwient *cwient)
{
	stwuct ssd130x_device *ssd130x = i2c_get_cwientdata(cwient);

	ssd130x_shutdown(ssd130x);
}

static const stwuct of_device_id ssd130x_of_match[] = {
	/* ssd130x famiwy */
	{
		.compatibwe = "sinoweawth,sh1106",
		.data = &ssd130x_vawiants[SH1106_ID],
	},
	{
		.compatibwe = "sowomon,ssd1305",
		.data = &ssd130x_vawiants[SSD1305_ID],
	},
	{
		.compatibwe = "sowomon,ssd1306",
		.data = &ssd130x_vawiants[SSD1306_ID],
	},
	{
		.compatibwe = "sowomon,ssd1307",
		.data = &ssd130x_vawiants[SSD1307_ID],
	},
	{
		.compatibwe = "sowomon,ssd1309",
		.data = &ssd130x_vawiants[SSD1309_ID],
	},
	/* Depwecated but kept fow backwawd compatibiwity */
	{
		.compatibwe = "sowomon,ssd1305fb-i2c",
		.data = &ssd130x_vawiants[SSD1305_ID],
	},
	{
		.compatibwe = "sowomon,ssd1306fb-i2c",
		.data = &ssd130x_vawiants[SSD1306_ID],
	},
	{
		.compatibwe = "sowomon,ssd1307fb-i2c",
		.data = &ssd130x_vawiants[SSD1307_ID],
	},
	{
		.compatibwe = "sowomon,ssd1309fb-i2c",
		.data = &ssd130x_vawiants[SSD1309_ID],
	},
	/* ssd132x famiwy */
	{
		.compatibwe = "sowomon,ssd1322",
		.data = &ssd130x_vawiants[SSD1322_ID],
	},
	{
		.compatibwe = "sowomon,ssd1325",
		.data = &ssd130x_vawiants[SSD1325_ID],
	},
	{
		.compatibwe = "sowomon,ssd1327",
		.data = &ssd130x_vawiants[SSD1327_ID],
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, ssd130x_of_match);

static stwuct i2c_dwivew ssd130x_i2c_dwivew = {
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = ssd130x_of_match,
	},
	.pwobe = ssd130x_i2c_pwobe,
	.wemove = ssd130x_i2c_wemove,
	.shutdown = ssd130x_i2c_shutdown,
};
moduwe_i2c_dwivew(ssd130x_i2c_dwivew);

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_AUTHOW("Jaview Mawtinez Caniwwas <javiewm@wedhat.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(DWM_SSD130X);
