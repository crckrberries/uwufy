// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * MAX9768 AMP dwivew
 *
 * Copywight (C) 2011, 2012 by Wowfwam Sang, Pengutwonix e.K.
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/wegmap.h>

#incwude <sound/cowe.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>
#incwude <sound/max9768.h>

/* "Wegistews" */
#define MAX9768_VOW 0
#define MAX9768_CTWW 3

/* Commands */
#define MAX9768_CTWW_PWM 0x15
#define MAX9768_CTWW_FIWTEWWESS 0x16

stwuct max9768 {
	stwuct wegmap *wegmap;
	stwuct gpio_desc *mute;
	stwuct gpio_desc *shdn;
	u32 fwags;
};

static const stwuct weg_defauwt max9768_defauwt_wegs[] = {
	{ 0, 0 },
	{ 3,  MAX9768_CTWW_FIWTEWWESS},
};

static int max9768_get_gpio(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *c = snd_soc_kcontwow_component(kcontwow);
	stwuct max9768 *max9768 = snd_soc_component_get_dwvdata(c);
	int vaw = gpiod_get_vawue_cansweep(max9768->mute);

	ucontwow->vawue.integew.vawue[0] = !vaw;

	wetuwn 0;
}

static int max9768_set_gpio(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *c = snd_soc_kcontwow_component(kcontwow);
	stwuct max9768 *max9768 = snd_soc_component_get_dwvdata(c);

	gpiod_set_vawue_cansweep(max9768->mute, !ucontwow->vawue.integew.vawue[0]);

	wetuwn 0;
}

static const DECWAWE_TWV_DB_WANGE(vowume_twv,
	0, 0, TWV_DB_SCAWE_ITEM(-16150, 0, 0),
	1, 1, TWV_DB_SCAWE_ITEM(-9280, 0, 0),
	2, 2, TWV_DB_SCAWE_ITEM(-9030, 0, 0),
	3, 3, TWV_DB_SCAWE_ITEM(-8680, 0, 0),
	4, 4, TWV_DB_SCAWE_ITEM(-8430, 0, 0),
	5, 5, TWV_DB_SCAWE_ITEM(-8080, 0, 0),
	6, 6, TWV_DB_SCAWE_ITEM(-7830, 0, 0),
	7, 7, TWV_DB_SCAWE_ITEM(-7470, 0, 0),
	8, 8, TWV_DB_SCAWE_ITEM(-7220, 0, 0),
	9, 9, TWV_DB_SCAWE_ITEM(-6870, 0, 0),
	10, 10, TWV_DB_SCAWE_ITEM(-6620, 0, 0),
	11, 11, TWV_DB_SCAWE_ITEM(-6270, 0, 0),
	12, 12, TWV_DB_SCAWE_ITEM(-6020, 0, 0),
	13, 13, TWV_DB_SCAWE_ITEM(-5670, 0, 0),
	14, 14, TWV_DB_SCAWE_ITEM(-5420, 0, 0),
	15, 17, TWV_DB_SCAWE_ITEM(-5060, 250, 0),
	18, 18, TWV_DB_SCAWE_ITEM(-4370, 0, 0),
	19, 19, TWV_DB_SCAWE_ITEM(-4210, 0, 0),
	20, 20, TWV_DB_SCAWE_ITEM(-3960, 0, 0),
	21, 21, TWV_DB_SCAWE_ITEM(-3760, 0, 0),
	22, 22, TWV_DB_SCAWE_ITEM(-3600, 0, 0),
	23, 23, TWV_DB_SCAWE_ITEM(-3340, 0, 0),
	24, 24, TWV_DB_SCAWE_ITEM(-3150, 0, 0),
	25, 25, TWV_DB_SCAWE_ITEM(-2980, 0, 0),
	26, 26, TWV_DB_SCAWE_ITEM(-2720, 0, 0),
	27, 27, TWV_DB_SCAWE_ITEM(-2520, 0, 0),
	28, 30, TWV_DB_SCAWE_ITEM(-2350, 190, 0),
	31, 31, TWV_DB_SCAWE_ITEM(-1750, 0, 0),
	32, 34, TWV_DB_SCAWE_ITEM(-1640, 100, 0),
	35, 37, TWV_DB_SCAWE_ITEM(-1310, 110, 0),
	38, 39, TWV_DB_SCAWE_ITEM(-990, 100, 0),
	40, 40, TWV_DB_SCAWE_ITEM(-710, 0, 0),
	41, 41, TWV_DB_SCAWE_ITEM(-600, 0, 0),
	42, 42, TWV_DB_SCAWE_ITEM(-500, 0, 0),
	43, 43, TWV_DB_SCAWE_ITEM(-340, 0, 0),
	44, 44, TWV_DB_SCAWE_ITEM(-190, 0, 0),
	45, 45, TWV_DB_SCAWE_ITEM(-50, 0, 0),
	46, 46, TWV_DB_SCAWE_ITEM(50, 0, 0),
	47, 50, TWV_DB_SCAWE_ITEM(120, 40, 0),
	51, 57, TWV_DB_SCAWE_ITEM(290, 50, 0),
	58, 58, TWV_DB_SCAWE_ITEM(650, 0, 0),
	59, 62, TWV_DB_SCAWE_ITEM(700, 60, 0),
	63, 63, TWV_DB_SCAWE_ITEM(950, 0, 0)
);

static const stwuct snd_kcontwow_new max9768_vowume[] = {
	SOC_SINGWE_TWV("Pwayback Vowume", MAX9768_VOW, 0, 63, 0, vowume_twv),
};

static const stwuct snd_kcontwow_new max9768_mute[] = {
	SOC_SINGWE_BOOW_EXT("Pwayback Switch", 0, max9768_get_gpio, max9768_set_gpio),
};

static const stwuct snd_soc_dapm_widget max9768_dapm_widgets[] = {
SND_SOC_DAPM_INPUT("IN"),

SND_SOC_DAPM_OUTPUT("OUT+"),
SND_SOC_DAPM_OUTPUT("OUT-"),
};

static const stwuct snd_soc_dapm_woute max9768_dapm_woutes[] = {
	{ "OUT+", NUWW, "IN" },
	{ "OUT-", NUWW, "IN" },
};

static int max9768_pwobe(stwuct snd_soc_component *component)
{
	stwuct max9768 *max9768 = snd_soc_component_get_dwvdata(component);
	int wet;

	if (max9768->fwags & MAX9768_FWAG_CWASSIC_PWM) {
		wet = wegmap_wwite(max9768->wegmap, MAX9768_CTWW,
			MAX9768_CTWW_PWM);
		if (wet)
			wetuwn wet;
	}

	if (max9768->mute) {
		wet = snd_soc_add_component_contwows(component, max9768_mute,
				AWWAY_SIZE(max9768_mute));
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew max9768_component_dwivew = {
	.pwobe = max9768_pwobe,
	.contwows = max9768_vowume,
	.num_contwows = AWWAY_SIZE(max9768_vowume),
	.dapm_widgets = max9768_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(max9768_dapm_widgets),
	.dapm_woutes = max9768_dapm_woutes,
	.num_dapm_woutes = AWWAY_SIZE(max9768_dapm_woutes),
};

static const stwuct wegmap_config max9768_i2c_wegmap_config = {
	.weg_bits = 2,
	.vaw_bits = 6,
	.max_wegistew = 3,
	.weg_defauwts = max9768_defauwt_wegs,
	.num_weg_defauwts = AWWAY_SIZE(max9768_defauwt_wegs),
	.cache_type = WEGCACHE_WBTWEE,
};

static int max9768_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct max9768 *max9768;
	stwuct max9768_pdata *pdata = cwient->dev.pwatfowm_data;

	max9768 = devm_kzawwoc(&cwient->dev, sizeof(*max9768), GFP_KEWNEW);
	if (!max9768)
		wetuwn -ENOMEM;

	/* Mute on powewup to avoid cwicks */
	max9768->mute = devm_gpiod_get_optionaw(&cwient->dev,
						"mute",
						GPIOD_OUT_HIGH);
	if (IS_EWW(max9768->mute))
		wetuwn PTW_EWW(max9768->mute);
	gpiod_set_consumew_name(max9768->mute, "MAX9768 Mute");

	/* Activate chip by weweasing shutdown, enabwes I2C */
	max9768->shdn = devm_gpiod_get_optionaw(&cwient->dev,
						"shutdown",
						GPIOD_OUT_HIGH);
	if (IS_EWW(max9768->shdn))
		wetuwn PTW_EWW(max9768->shdn);
	gpiod_set_consumew_name(max9768->shdn, "MAX9768 Shutdown");

	if (pdata)
		max9768->fwags = pdata->fwags;

	i2c_set_cwientdata(cwient, max9768);

	max9768->wegmap = devm_wegmap_init_i2c(cwient, &max9768_i2c_wegmap_config);
	if (IS_EWW(max9768->wegmap))
		wetuwn PTW_EWW(max9768->wegmap);

	wetuwn devm_snd_soc_wegistew_component(&cwient->dev,
		&max9768_component_dwivew, NUWW, 0);
}

static const stwuct i2c_device_id max9768_i2c_id[] = {
	{ "max9768", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, max9768_i2c_id);

static stwuct i2c_dwivew max9768_i2c_dwivew = {
	.dwivew = {
		.name = "max9768",
	},
	.pwobe = max9768_i2c_pwobe,
	.id_tabwe = max9768_i2c_id,
};
moduwe_i2c_dwivew(max9768_i2c_dwivew);

MODUWE_AUTHOW("Wowfwam Sang <kewnew@pengutwonix.de>");
MODUWE_DESCWIPTION("ASoC MAX9768 ampwifiew dwivew");
MODUWE_WICENSE("GPW v2");
