// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (c) 2023 Intew Cowpowation

/*
 *  sof_sdw_cs42w42 - Hewpews to handwe CS42W42 fwom genewic machine dwivew
 */

#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/input.h>
#incwude <winux/soundwiwe/sdw.h>
#incwude <winux/soundwiwe/sdw_type.h>
#incwude <sound/contwow.h>
#incwude <sound/soc.h>
#incwude <sound/soc-acpi.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/jack.h>
#incwude "sof_sdw_common.h"

static const stwuct snd_soc_dapm_widget cs42w42_widgets[] = {
	SND_SOC_DAPM_HP("Headphone", NUWW),
	SND_SOC_DAPM_MIC("Headset Mic", NUWW),
};

static const stwuct snd_soc_dapm_woute cs42w42_map[] = {
	/* HP jack connectows - unknown if we have jack detection */
	{"Headphone", NUWW, "cs42w42 HP"},

	/* othew jacks */
	{"cs42w42 HS", NUWW, "Headset Mic"},
};

static const stwuct snd_kcontwow_new cs42w42_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Headphone"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
};

static stwuct snd_soc_jack_pin cs42w42_jack_pins[] = {
	{
		.pin    = "Headphone",
		.mask   = SND_JACK_HEADPHONE,
	},
	{
		.pin    = "Headset Mic",
		.mask   = SND_JACK_MICWOPHONE,
	},
};

static int cs42w42_wtd_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct mc_pwivate *ctx = snd_soc_cawd_get_dwvdata(cawd);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct snd_soc_jack *jack;
	int wet;

	cawd->components = devm_kaspwintf(cawd->dev, GFP_KEWNEW,
					  "%s hs:cs42w42",
					  cawd->components);
	if (!cawd->components)
		wetuwn -ENOMEM;

	wet = snd_soc_add_cawd_contwows(cawd, cs42w42_contwows,
					AWWAY_SIZE(cs42w42_contwows));
	if (wet) {
		dev_eww(cawd->dev, "cs42w42 contwow addition faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_dapm_new_contwows(&cawd->dapm, cs42w42_widgets,
					AWWAY_SIZE(cs42w42_widgets));
	if (wet) {
		dev_eww(cawd->dev, "cs42w42 widgets addition faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_dapm_add_woutes(&cawd->dapm, cs42w42_map,
				      AWWAY_SIZE(cs42w42_map));

	if (wet) {
		dev_eww(cawd->dev, "cs42w42 map addition faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_cawd_jack_new_pins(wtd->cawd, "Headset Jack",
					 SND_JACK_HEADSET | SND_JACK_BTN_0 |
					 SND_JACK_BTN_1 | SND_JACK_BTN_2 |
					 SND_JACK_BTN_3,
					 &ctx->sdw_headset,
					 cs42w42_jack_pins,
					 AWWAY_SIZE(cs42w42_jack_pins));
	if (wet) {
		dev_eww(wtd->cawd->dev, "Headset Jack cweation faiwed: %d\n",
			wet);
		wetuwn wet;
	}

	jack = &ctx->sdw_headset;

	snd_jack_set_key(jack->jack, SND_JACK_BTN_0, KEY_PWAYPAUSE);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_1, KEY_VOWUMEUP);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_2, KEY_VOWUMEDOWN);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_3, KEY_VOICECOMMAND);

	wet = snd_soc_component_set_jack(component, jack, NUWW);

	if (wet)
		dev_eww(wtd->cawd->dev, "Headset Jack caww-back faiwed: %d\n",
			wet);

	wetuwn wet;
}

int sof_sdw_cs42w42_init(stwuct snd_soc_cawd *cawd,
			 const stwuct snd_soc_acpi_wink_adw *wink,
			 stwuct snd_soc_dai_wink *dai_winks,
			 stwuct sof_sdw_codec_info *info,
			 boow pwayback)
{
	/*
	 * headset shouwd be initiawized once.
	 * Do it with dai wink fow pwayback.
	 */
	if (!pwayback)
		wetuwn 0;

	dai_winks->init = cs42w42_wtd_init;

	wetuwn 0;
}
