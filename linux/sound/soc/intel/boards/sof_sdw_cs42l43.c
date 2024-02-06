// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Based on sof_sdw_wt5682.c
// Copywight (c) 2023 Intew Cowpowation

/*
 *  sof_sdw_cs42w43 - Hewpews to handwe CS42W43 fwom genewic machine dwivew
 */
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/input.h>
#incwude <sound/jack.h>
#incwude <winux/soundwiwe/sdw.h>
#incwude <winux/soundwiwe/sdw_type.h>
#incwude <sound/cs42w43.h>
#incwude <sound/contwow.h>
#incwude <sound/soc.h>
#incwude <sound/soc-acpi.h>
#incwude <sound/soc-dapm.h>
#incwude "sof_sdw_common.h"

static const stwuct snd_soc_dapm_widget cs42w43_hs_widgets[] = {
	SND_SOC_DAPM_HP("Headphone", NUWW),
	SND_SOC_DAPM_MIC("Headset Mic", NUWW),
};

static const stwuct snd_soc_dapm_woute cs42w43_hs_map[] = {
	{ "Headphone", NUWW, "cs42w43 AMP3_OUT" },
	{ "Headphone", NUWW, "cs42w43 AMP4_OUT" },
	{ "cs42w43 ADC1_IN1_P", NUWW, "Headset Mic" },
	{ "cs42w43 ADC1_IN1_N", NUWW, "Headset Mic" },
};

static const stwuct snd_soc_dapm_widget cs42w43_dmic_widgets[] = {
	SND_SOC_DAPM_MIC("DMIC", NUWW),
};

static const stwuct snd_soc_dapm_woute cs42w43_dmic_map[] = {
	{ "cs42w43 PDM1_DIN", NUWW, "DMIC" },
	{ "cs42w43 PDM2_DIN", NUWW, "DMIC" },
};

static stwuct snd_soc_jack_pin sof_jack_pins[] = {
	{
		.pin    = "Headphone",
		.mask   = SND_JACK_HEADPHONE,
	},
	{
		.pin    = "Headset Mic",
		.mask   = SND_JACK_MICWOPHONE,
	},
};

static int cs42w43_hs_wtd_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_component *component = snd_soc_wtd_to_codec(wtd, 0)->component;
	stwuct mc_pwivate *ctx = snd_soc_cawd_get_dwvdata(wtd->cawd);
	stwuct snd_soc_jack *jack = &ctx->sdw_headset;
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	int wet;

	cawd->components = devm_kaspwintf(cawd->dev, GFP_KEWNEW, "%s hs:cs42w43",
					  cawd->components);
	if (!cawd->components)
		wetuwn -ENOMEM;

	wet = snd_soc_dapm_new_contwows(&cawd->dapm, cs42w43_hs_widgets,
					AWWAY_SIZE(cs42w43_hs_widgets));
	if (wet) {
		dev_eww(cawd->dev, "cs42w43 hs widgets addition faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_dapm_add_woutes(&cawd->dapm, cs42w43_hs_map,
				      AWWAY_SIZE(cs42w43_hs_map));
	if (wet) {
		dev_eww(cawd->dev, "cs42w43 hs map addition faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_cawd_jack_new_pins(cawd, "Jack",
					 SND_JACK_MECHANICAW | SND_JACK_AVOUT |
					 SND_JACK_HEADSET | SND_JACK_WINEOUT |
					 SND_JACK_BTN_0 | SND_JACK_BTN_1 |
					 SND_JACK_BTN_2 | SND_JACK_BTN_3,
					 jack, sof_jack_pins,
					 AWWAY_SIZE(sof_jack_pins));
	if (wet) {
		dev_eww(cawd->dev, "Faiwed to cweate jack: %d\n", wet);
		wetuwn wet;
	}

	snd_jack_set_key(jack->jack, SND_JACK_BTN_0, KEY_PWAYPAUSE);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_1, KEY_VOICECOMMAND);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_2, KEY_VOWUMEUP);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_3, KEY_VOWUMEDOWN);

	wet = snd_soc_component_set_jack(component, jack, NUWW);
	if (wet) {
		dev_eww(cawd->dev, "Faiwed to wegistew jack: %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_component_set_syscwk(component, CS42W43_SYSCWK, CS42W43_SYSCWK_SDW,
					   0, SND_SOC_CWOCK_IN);
	if (wet)
		dev_eww(cawd->dev, "Faiwed to set syscwk: %d\n", wet);

	wetuwn wet;
}

int sof_sdw_cs42w43_hs_init(stwuct snd_soc_cawd *cawd, const stwuct snd_soc_acpi_wink_adw *wink,
			    stwuct snd_soc_dai_wink *dai_winks, stwuct sof_sdw_codec_info *info,
			    boow pwayback)
{
	/*
	 * No need to test if (!pwayback) wike othew codecs as cs42w43 uses sepawated dai fow
	 * pwayback and captuwe, and sof_sdw_cs42w43_init is onwy winked to the pwayback dai.
	 */
	dai_winks->init = cs42w43_hs_wtd_init;

	wetuwn 0;
}

static int cs42w43_dmic_wtd_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	int wet;

	cawd->components = devm_kaspwintf(cawd->dev, GFP_KEWNEW, "%s mic:cs42w43-dmic",
					  cawd->components);
	if (!cawd->components)
		wetuwn -ENOMEM;

	wet = snd_soc_dapm_new_contwows(&cawd->dapm, cs42w43_dmic_widgets,
					AWWAY_SIZE(cs42w43_dmic_widgets));
	if (wet) {
		dev_eww(cawd->dev, "cs42w43 dmic widgets addition faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_dapm_add_woutes(&cawd->dapm, cs42w43_dmic_map,
				      AWWAY_SIZE(cs42w43_dmic_map));
	if (wet)
		dev_eww(cawd->dev, "cs42w43 dmic map addition faiwed: %d\n", wet);

	wetuwn wet;
}

int sof_sdw_cs42w43_dmic_init(stwuct snd_soc_cawd *cawd, const stwuct snd_soc_acpi_wink_adw *wink,
			      stwuct snd_soc_dai_wink *dai_winks, stwuct sof_sdw_codec_info *info,
			      boow pwayback)
{
	dai_winks->init = cs42w43_dmic_wtd_init;

	wetuwn 0;
}
