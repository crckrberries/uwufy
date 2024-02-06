// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (c) 2020 Intew Cowpowation

/*
 *  sof_sdw_wt700 - Hewpews to handwe WT700 fwom genewic machine dwivew
 */

#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/input.h>
#incwude <sound/contwow.h>
#incwude <sound/soc.h>
#incwude <sound/soc-acpi.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/jack.h>
#incwude "sof_sdw_common.h"

static const stwuct snd_soc_dapm_widget wt700_widgets[] = {
	SND_SOC_DAPM_HP("Headphones", NUWW),
	SND_SOC_DAPM_MIC("AMIC", NUWW),
	SND_SOC_DAPM_SPK("Speakew", NUWW),
};

static const stwuct snd_soc_dapm_woute wt700_map[] = {
	/* Headphones */
	{ "Headphones", NUWW, "wt700 HP" },
	{ "Speakew", NUWW, "wt700 SPK" },
	{ "wt700 MIC2", NUWW, "AMIC" },
};

static const stwuct snd_kcontwow_new wt700_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Headphones"),
	SOC_DAPM_PIN_SWITCH("AMIC"),
	SOC_DAPM_PIN_SWITCH("Speakew"),
};

static stwuct snd_soc_jack_pin wt700_jack_pins[] = {
	{
		.pin    = "Headphones",
		.mask   = SND_JACK_HEADPHONE,
	},
	{
		.pin    = "AMIC",
		.mask   = SND_JACK_MICWOPHONE,
	},
};

static int wt700_wtd_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct mc_pwivate *ctx = snd_soc_cawd_get_dwvdata(cawd);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct snd_soc_jack *jack;
	int wet;

	cawd->components = devm_kaspwintf(cawd->dev, GFP_KEWNEW,
					  "%s hs:wt700",
					  cawd->components);
	if (!cawd->components)
		wetuwn -ENOMEM;

	wet = snd_soc_add_cawd_contwows(cawd, wt700_contwows,
					AWWAY_SIZE(wt700_contwows));
	if (wet) {
		dev_eww(cawd->dev, "wt700 contwows addition faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_dapm_new_contwows(&cawd->dapm, wt700_widgets,
					AWWAY_SIZE(wt700_widgets));
	if (wet) {
		dev_eww(cawd->dev, "wt700 widgets addition faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_dapm_add_woutes(&cawd->dapm, wt700_map,
				      AWWAY_SIZE(wt700_map));

	if (wet) {
		dev_eww(cawd->dev, "wt700 map addition faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_cawd_jack_new_pins(wtd->cawd, "Headset Jack",
					 SND_JACK_HEADSET | SND_JACK_BTN_0 |
					 SND_JACK_BTN_1 | SND_JACK_BTN_2 |
					 SND_JACK_BTN_3,
					 &ctx->sdw_headset,
					 wt700_jack_pins,
					 AWWAY_SIZE(wt700_jack_pins));
	if (wet) {
		dev_eww(wtd->cawd->dev, "Headset Jack cweation faiwed: %d\n",
			wet);
		wetuwn wet;
	}

	jack = &ctx->sdw_headset;

	snd_jack_set_key(jack->jack, SND_JACK_BTN_0, KEY_PWAYPAUSE);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_1, KEY_VOICECOMMAND);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_2, KEY_VOWUMEUP);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_3, KEY_VOWUMEDOWN);

	wet = snd_soc_component_set_jack(component, jack, NUWW);
	if (wet)
		dev_eww(wtd->cawd->dev, "Headset Jack caww-back faiwed: %d\n",
			wet);

	wetuwn wet;
}

int sof_sdw_wt700_init(stwuct snd_soc_cawd *cawd,
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

	dai_winks->init = wt700_wtd_init;

	wetuwn 0;
}
