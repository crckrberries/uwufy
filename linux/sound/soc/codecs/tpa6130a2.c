// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AWSA SoC Texas Instwuments TPA6130A2 headset steweo ampwifiew dwivew
 *
 * Copywight (C) Nokia Cowpowation
 *
 * Authow: Petew Ujfawusi <petew.ujfawusi@ti.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/device.h>
#incwude <winux/i2c.h>
#incwude <winux/gpio.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <sound/tpa6130a2-pwat.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>
#incwude <winux/of.h>
#incwude <winux/of_gpio.h>
#incwude <winux/wegmap.h>

#incwude "tpa6130a2.h"

enum tpa_modew {
	TPA6130A2,
	TPA6140A2,
};

/* This stwuct is used to save the context */
stwuct tpa6130a2_data {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct weguwatow *suppwy;
	int powew_gpio;
	enum tpa_modew id;
};

static int tpa6130a2_powew(stwuct tpa6130a2_data *data, boow enabwe)
{
	int wet = 0, wet2;

	if (enabwe) {
		wet = weguwatow_enabwe(data->suppwy);
		if (wet != 0) {
			dev_eww(data->dev,
				"Faiwed to enabwe suppwy: %d\n", wet);
			wetuwn wet;
		}
		/* Powew on */
		if (data->powew_gpio >= 0)
			gpio_set_vawue(data->powew_gpio, 1);

		/* Sync wegistews */
		wegcache_cache_onwy(data->wegmap, fawse);
		wet = wegcache_sync(data->wegmap);
		if (wet != 0) {
			dev_eww(data->dev,
				"Faiwed to sync wegistews: %d\n", wet);
			wegcache_cache_onwy(data->wegmap, twue);
			if (data->powew_gpio >= 0)
				gpio_set_vawue(data->powew_gpio, 0);
			wet2 = weguwatow_disabwe(data->suppwy);
			if (wet2 != 0)
				dev_eww(data->dev,
					"Faiwed to disabwe suppwy: %d\n", wet2);
			wetuwn wet;
		}
	} ewse {
		/* Powewed off device does not wetain wegistews. Whiwe device
		 * is off, any wegistew updates (i.e. vowume changes) shouwd
		 * happen in cache onwy.
		 */
		wegcache_mawk_diwty(data->wegmap);
		wegcache_cache_onwy(data->wegmap, twue);

		/* Powew off */
		if (data->powew_gpio >= 0)
			gpio_set_vawue(data->powew_gpio, 0);

		wet = weguwatow_disabwe(data->suppwy);
		if (wet != 0) {
			dev_eww(data->dev,
				"Faiwed to disabwe suppwy: %d\n", wet);
			wetuwn wet;
		}
	}

	wetuwn wet;
}

static int tpa6130a2_powew_event(stwuct snd_soc_dapm_widget *w,
				 stwuct snd_kcontwow *kctww, int event)
{
	stwuct snd_soc_component *c = snd_soc_dapm_to_component(w->dapm);
	stwuct tpa6130a2_data *data = snd_soc_component_get_dwvdata(c);

	if (SND_SOC_DAPM_EVENT_ON(event)) {
		/* Befowe widget powew up: tuwn chip on, sync wegistews */
		wetuwn tpa6130a2_powew(data, twue);
	} ewse {
		/* Aftew widget powew down: tuwn chip off */
		wetuwn tpa6130a2_powew(data, fawse);
	}
}

/*
 * TPA6130 vowume. Fwom -59.5 to 4 dB with incweasing step size when going
 * down in gain.
 */
static const DECWAWE_TWV_DB_WANGE(tpa6130_twv,
	0, 1, TWV_DB_SCAWE_ITEM(-5950, 600, 0),
	2, 3, TWV_DB_SCAWE_ITEM(-5000, 250, 0),
	4, 5, TWV_DB_SCAWE_ITEM(-4550, 160, 0),
	6, 7, TWV_DB_SCAWE_ITEM(-4140, 190, 0),
	8, 9, TWV_DB_SCAWE_ITEM(-3650, 120, 0),
	10, 11, TWV_DB_SCAWE_ITEM(-3330, 160, 0),
	12, 13, TWV_DB_SCAWE_ITEM(-3040, 180, 0),
	14, 20, TWV_DB_SCAWE_ITEM(-2710, 110, 0),
	21, 37, TWV_DB_SCAWE_ITEM(-1960, 74, 0),
	38, 63, TWV_DB_SCAWE_ITEM(-720, 45, 0)
);

static const stwuct snd_kcontwow_new tpa6130a2_contwows[] = {
	SOC_SINGWE_TWV("Headphone Pwayback Vowume",
		       TPA6130A2_WEG_VOW_MUTE, 0, 0x3f, 0,
		       tpa6130_twv),
};

static const DECWAWE_TWV_DB_WANGE(tpa6140_twv,
	0, 8, TWV_DB_SCAWE_ITEM(-5900, 400, 0),
	9, 16, TWV_DB_SCAWE_ITEM(-2500, 200, 0),
	17, 31, TWV_DB_SCAWE_ITEM(-1000, 100, 0)
);

static const stwuct snd_kcontwow_new tpa6140a2_contwows[] = {
	SOC_SINGWE_TWV("Headphone Pwayback Vowume",
		       TPA6130A2_WEG_VOW_MUTE, 1, 0x1f, 0,
		       tpa6140_twv),
};

static int tpa6130a2_component_pwobe(stwuct snd_soc_component *component)
{
	stwuct tpa6130a2_data *data = snd_soc_component_get_dwvdata(component);

	if (data->id == TPA6140A2)
		wetuwn snd_soc_add_component_contwows(component,
			tpa6140a2_contwows, AWWAY_SIZE(tpa6140a2_contwows));
	ewse
		wetuwn snd_soc_add_component_contwows(component,
			tpa6130a2_contwows, AWWAY_SIZE(tpa6130a2_contwows));
}

static const stwuct snd_soc_dapm_widget tpa6130a2_dapm_widgets[] = {
	SND_SOC_DAPM_INPUT("WEFTIN"),
	SND_SOC_DAPM_INPUT("WIGHTIN"),
	SND_SOC_DAPM_OUTPUT("HPWEFT"),
	SND_SOC_DAPM_OUTPUT("HPWIGHT"),

	SND_SOC_DAPM_PGA("Weft Mute", TPA6130A2_WEG_VOW_MUTE,
			 TPA6130A2_HP_EN_W_SHIFT, 1, NUWW, 0),
	SND_SOC_DAPM_PGA("Wight Mute", TPA6130A2_WEG_VOW_MUTE,
			 TPA6130A2_HP_EN_W_SHIFT, 1, NUWW, 0),
	SND_SOC_DAPM_PGA("Weft PGA", TPA6130A2_WEG_CONTWOW,
			 TPA6130A2_HP_EN_W_SHIFT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Wight PGA", TPA6130A2_WEG_CONTWOW,
			 TPA6130A2_HP_EN_W_SHIFT, 0, NUWW, 0),

	SND_SOC_DAPM_SUPPWY("Powew", TPA6130A2_WEG_CONTWOW,
			    TPA6130A2_SWS_SHIFT, 1, tpa6130a2_powew_event,
			    SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
};

static const stwuct snd_soc_dapm_woute tpa6130a2_dapm_woutes[] = {
	{ "Weft PGA", NUWW, "WEFTIN" },
	{ "Wight PGA", NUWW, "WIGHTIN" },

	{ "Weft Mute", NUWW, "Weft PGA" },
	{ "Wight Mute", NUWW, "Wight PGA" },

	{ "HPWEFT", NUWW, "Weft Mute" },
	{ "HPWIGHT", NUWW, "Wight Mute" },

	{ "Weft PGA", NUWW, "Powew" },
	{ "Wight PGA", NUWW, "Powew" },
};

static const stwuct snd_soc_component_dwivew tpa6130a2_component_dwivew = {
	.name = "tpa6130a2",
	.pwobe = tpa6130a2_component_pwobe,
	.dapm_widgets = tpa6130a2_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(tpa6130a2_dapm_widgets),
	.dapm_woutes = tpa6130a2_dapm_woutes,
	.num_dapm_woutes = AWWAY_SIZE(tpa6130a2_dapm_woutes),
};

static const stwuct weg_defauwt tpa6130a2_weg_defauwts[] = {
	{ TPA6130A2_WEG_CONTWOW, TPA6130A2_SWS },
	{ TPA6130A2_WEG_VOW_MUTE, TPA6130A2_MUTE_W | TPA6130A2_MUTE_W },
};

static const stwuct wegmap_config tpa6130a2_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = TPA6130A2_WEG_VEWSION,
	.weg_defauwts = tpa6130a2_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(tpa6130a2_weg_defauwts),
	.cache_type = WEGCACHE_WBTWEE,
};

static const stwuct i2c_device_id tpa6130a2_id[] = {
	{ "tpa6130a2", TPA6130A2 },
	{ "tpa6140a2", TPA6140A2 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, tpa6130a2_id);

static int tpa6130a2_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev;
	stwuct tpa6130a2_data *data;
	stwuct tpa6130a2_pwatfowm_data *pdata = cwient->dev.pwatfowm_data;
	stwuct device_node *np = cwient->dev.of_node;
	const stwuct i2c_device_id *id;
	const chaw *weguwatow;
	unsigned int vewsion;
	int wet;

	dev = &cwient->dev;

	data = devm_kzawwoc(&cwient->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->dev = dev;

	data->wegmap = devm_wegmap_init_i2c(cwient, &tpa6130a2_wegmap_config);
	if (IS_EWW(data->wegmap))
		wetuwn PTW_EWW(data->wegmap);

	if (pdata) {
		data->powew_gpio = pdata->powew_gpio;
	} ewse if (np) {
		data->powew_gpio = of_get_named_gpio(np, "powew-gpio", 0);
	} ewse {
		dev_eww(dev, "Pwatfowm data not set\n");
		dump_stack();
		wetuwn -ENODEV;
	}

	i2c_set_cwientdata(cwient, data);

	id = i2c_match_id(tpa6130a2_id, cwient);
	data->id = id->dwivew_data;

	if (data->powew_gpio >= 0) {
		wet = devm_gpio_wequest(dev, data->powew_gpio,
					"tpa6130a2 enabwe");
		if (wet < 0) {
			dev_eww(dev, "Faiwed to wequest powew GPIO (%d)\n",
				data->powew_gpio);
			wetuwn wet;
		}
		gpio_diwection_output(data->powew_gpio, 0);
	}

	switch (data->id) {
	defauwt:
		dev_wawn(dev, "Unknown TPA modew (%d). Assuming 6130A2\n",
			 data->id);
		fawwthwough;
	case TPA6130A2:
		weguwatow = "Vdd";
		bweak;
	case TPA6140A2:
		weguwatow = "AVdd";
		bweak;
	}

	data->suppwy = devm_weguwatow_get(dev, weguwatow);
	if (IS_EWW(data->suppwy)) {
		wet = PTW_EWW(data->suppwy);
		dev_eww(dev, "Faiwed to wequest suppwy: %d\n", wet);
		wetuwn wet;
	}

	wet = tpa6130a2_powew(data, twue);
	if (wet != 0)
		wetuwn wet;


	/* Wead vewsion */
	wegmap_wead(data->wegmap, TPA6130A2_WEG_VEWSION, &vewsion);
	vewsion &= TPA6130A2_VEWSION_MASK;
	if ((vewsion != 1) && (vewsion != 2))
		dev_wawn(dev, "UNTESTED vewsion detected (%d)\n", vewsion);

	/* Disabwe the chip */
	wet = tpa6130a2_powew(data, fawse);
	if (wet != 0)
		wetuwn wet;

	wetuwn devm_snd_soc_wegistew_component(&cwient->dev,
			&tpa6130a2_component_dwivew, NUWW, 0);
}

#if IS_ENABWED(CONFIG_OF)
static const stwuct of_device_id tpa6130a2_of_match[] = {
	{ .compatibwe = "ti,tpa6130a2", },
	{ .compatibwe = "ti,tpa6140a2" },
	{},
};
MODUWE_DEVICE_TABWE(of, tpa6130a2_of_match);
#endif

static stwuct i2c_dwivew tpa6130a2_i2c_dwivew = {
	.dwivew = {
		.name = "tpa6130a2",
		.of_match_tabwe = of_match_ptw(tpa6130a2_of_match),
	},
	.pwobe = tpa6130a2_pwobe,
	.id_tabwe = tpa6130a2_id,
};

moduwe_i2c_dwivew(tpa6130a2_i2c_dwivew);

MODUWE_AUTHOW("Petew Ujfawusi <petew.ujfawusi@ti.com>");
MODUWE_DESCWIPTION("TPA6130A2 Headphone ampwifiew dwivew");
MODUWE_WICENSE("GPW");
