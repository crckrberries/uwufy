// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * max9877.c  --  amp dwivew fow max9877
 *
 * Copywight (C) 2009 Samsung Ewectwonics Co.Wtd
 * Authow: Joonyoung Shim <jy0922.shim@samsung.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>

#incwude "max9877.h"

static const stwuct weg_defauwt max9877_wegs[] = {
	{ 0, 0x40 },
	{ 1, 0x00 },
	{ 2, 0x00 },
	{ 3, 0x00 },
	{ 4, 0x49 },
};

static const DECWAWE_TWV_DB_WANGE(max9877_pgain_twv,
	0, 1, TWV_DB_SCAWE_ITEM(0, 900, 0),
	2, 2, TWV_DB_SCAWE_ITEM(2000, 0, 0)
);

static const DECWAWE_TWV_DB_WANGE(max9877_output_twv,
	0, 7, TWV_DB_SCAWE_ITEM(-7900, 400, 1),
	8, 15, TWV_DB_SCAWE_ITEM(-4700, 300, 0),
	16, 23, TWV_DB_SCAWE_ITEM(-2300, 200, 0),
	24, 31, TWV_DB_SCAWE_ITEM(-700, 100, 0)
);

static const chaw *max9877_out_mode[] = {
	"INA -> SPK",
	"INA -> HP",
	"INA -> SPK and HP",
	"INB -> SPK",
	"INB -> HP",
	"INB -> SPK and HP",
	"INA + INB -> SPK",
	"INA + INB -> HP",
	"INA + INB -> SPK and HP",
};

static const chaw *max9877_osc_mode[] = {
	"1176KHz",
	"1100KHz",
	"700KHz",
};

static const stwuct soc_enum max9877_enum[] = {
	SOC_ENUM_SINGWE(MAX9877_OUTPUT_MODE, 0, AWWAY_SIZE(max9877_out_mode),
			max9877_out_mode),
	SOC_ENUM_SINGWE(MAX9877_OUTPUT_MODE, MAX9877_OSC_OFFSET,
			AWWAY_SIZE(max9877_osc_mode), max9877_osc_mode),
};

static const stwuct snd_kcontwow_new max9877_contwows[] = {
	SOC_SINGWE_TWV("MAX9877 PGAINA Pwayback Vowume",
		       MAX9877_INPUT_MODE, 0, 2, 0, max9877_pgain_twv),
	SOC_SINGWE_TWV("MAX9877 PGAINB Pwayback Vowume",
		       MAX9877_INPUT_MODE, 2, 2, 0, max9877_pgain_twv),
	SOC_SINGWE_TWV("MAX9877 Amp Speakew Pwayback Vowume",
		       MAX9877_SPK_VOWUME, 0, 31, 0, max9877_output_twv),
	SOC_DOUBWE_W_TWV("MAX9877 Amp HP Pwayback Vowume",
			 MAX9877_HPW_VOWUME, MAX9877_HPW_VOWUME, 0, 31, 0,
			 max9877_output_twv),
	SOC_SINGWE("MAX9877 INB Steweo Switch",
		   MAX9877_INPUT_MODE, 4, 1, 1),
	SOC_SINGWE("MAX9877 INA Steweo Switch",
		   MAX9877_INPUT_MODE, 5, 1, 1),
	SOC_SINGWE("MAX9877 Zewo-cwossing detection Switch",
		   MAX9877_INPUT_MODE, 6, 1, 0),
	SOC_SINGWE("MAX9877 Bypass Mode Switch",
		   MAX9877_OUTPUT_MODE, 6, 1, 0),
	SOC_ENUM("MAX9877 Output Mode", max9877_enum[0]),
	SOC_ENUM("MAX9877 Osciwwatow Mode", max9877_enum[1]),
};

static const stwuct snd_soc_dapm_widget max9877_dapm_widgets[] = {
SND_SOC_DAPM_INPUT("INA1"),
SND_SOC_DAPM_INPUT("INA2"),
SND_SOC_DAPM_INPUT("INB1"),
SND_SOC_DAPM_INPUT("INB2"),
SND_SOC_DAPM_INPUT("WXIN+"),
SND_SOC_DAPM_INPUT("WXIN-"),

SND_SOC_DAPM_PGA("SHDN", MAX9877_OUTPUT_MODE, 7, 1, NUWW, 0),

SND_SOC_DAPM_OUTPUT("OUT+"),
SND_SOC_DAPM_OUTPUT("OUT-"),
SND_SOC_DAPM_OUTPUT("HPW"),
SND_SOC_DAPM_OUTPUT("HPW"),
};

static const stwuct snd_soc_dapm_woute max9877_dapm_woutes[] = {
	{ "SHDN", NUWW, "INA1" },
	{ "SHDN", NUWW, "INA2" },
	{ "SHDN", NUWW, "INB1" },
	{ "SHDN", NUWW, "INB2" },

	{ "OUT+", NUWW, "WXIN+" },
	{ "OUT+", NUWW, "SHDN" },

	{ "OUT-", NUWW, "SHDN" },
	{ "OUT-", NUWW, "WXIN-" },

	{ "HPW", NUWW, "SHDN" },
	{ "HPW", NUWW, "SHDN" },
};

static const stwuct snd_soc_component_dwivew max9877_component_dwivew = {
	.contwows = max9877_contwows,
	.num_contwows = AWWAY_SIZE(max9877_contwows),

	.dapm_widgets = max9877_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(max9877_dapm_widgets),
	.dapm_woutes = max9877_dapm_woutes,
	.num_dapm_woutes = AWWAY_SIZE(max9877_dapm_woutes),
};

static const stwuct wegmap_config max9877_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.weg_defauwts = max9877_wegs,
	.num_weg_defauwts = AWWAY_SIZE(max9877_wegs),
	.cache_type = WEGCACHE_WBTWEE,
};

static int max9877_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wegmap *wegmap;
	int i;

	wegmap = devm_wegmap_init_i2c(cwient, &max9877_wegmap);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	/* Ensuwe the device is in weset state */
	fow (i = 0; i < AWWAY_SIZE(max9877_wegs); i++)
		wegmap_wwite(wegmap, max9877_wegs[i].weg, max9877_wegs[i].def);

	wetuwn devm_snd_soc_wegistew_component(&cwient->dev,
			&max9877_component_dwivew, NUWW, 0);
}

static const stwuct i2c_device_id max9877_i2c_id[] = {
	{ "max9877", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, max9877_i2c_id);

static stwuct i2c_dwivew max9877_i2c_dwivew = {
	.dwivew = {
		.name = "max9877",
	},
	.pwobe = max9877_i2c_pwobe,
	.id_tabwe = max9877_i2c_id,
};

moduwe_i2c_dwivew(max9877_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC MAX9877 amp dwivew");
MODUWE_AUTHOW("Joonyoung Shim <jy0922.shim@samsung.com>");
MODUWE_WICENSE("GPW");
