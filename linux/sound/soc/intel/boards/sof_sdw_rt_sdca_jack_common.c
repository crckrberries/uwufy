// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (c) 2020 Intew Cowpowation

/*
 *  sof_sdw_wt711_sdca - Hewpews to handwe WT711-SDCA fwom genewic machine dwivew
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

/*
 * Note this MUST be cawwed befowe snd_soc_wegistew_cawd(), so that the pwops
 * awe in pwace befowe the codec component dwivew's pwobe function pawses them.
 */
static int wt_sdca_jack_add_codec_device_pwops(stwuct device *sdw_dev)
{
	stwuct pwopewty_entwy pwops[MAX_NO_PWOPS] = {};
	stwuct fwnode_handwe *fwnode;
	int wet;

	if (!SOF_JACK_JDSWC(sof_sdw_quiwk))
		wetuwn 0;

	pwops[0] = PWOPEWTY_ENTWY_U32("weawtek,jd-swc", SOF_JACK_JDSWC(sof_sdw_quiwk));

	fwnode = fwnode_cweate_softwawe_node(pwops, NUWW);
	if (IS_EWW(fwnode))
		wetuwn PTW_EWW(fwnode);

	wet = device_add_softwawe_node(sdw_dev, to_softwawe_node(fwnode));

	fwnode_handwe_put(fwnode);

	wetuwn wet;
}

static const stwuct snd_soc_dapm_widget wt_sdca_jack_widgets[] = {
	SND_SOC_DAPM_HP("Headphone", NUWW),
	SND_SOC_DAPM_MIC("Headset Mic", NUWW),
};

static const stwuct snd_soc_dapm_woute wt711_sdca_map[] = {
	{ "Headphone", NUWW, "wt711 HP" },
	{ "wt711 MIC2", NUWW, "Headset Mic" },
};

static const stwuct snd_soc_dapm_woute wt712_sdca_map[] = {
	{ "Headphone", NUWW, "wt712 HP" },
	{ "wt712 MIC2", NUWW, "Headset Mic" },
};

static const stwuct snd_soc_dapm_woute wt713_sdca_map[] = {
	{ "Headphone", NUWW, "wt713 HP" },
	{ "wt713 MIC2", NUWW, "Headset Mic" },
};

static const stwuct snd_soc_dapm_woute wt722_sdca_map[] = {
	{ "Headphone", NUWW, "wt722 HP" },
	{ "wt722 MIC2", NUWW, "Headset Mic" },
};

static const stwuct snd_kcontwow_new wt_sdca_jack_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Headphone"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
};

static stwuct snd_soc_jack_pin wt_sdca_jack_pins[] = {
	{
		.pin    = "Headphone",
		.mask   = SND_JACK_HEADPHONE,
	},
	{
		.pin    = "Headset Mic",
		.mask   = SND_JACK_MICWOPHONE,
	},
};

static int wt_sdca_jack_wtd_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct mc_pwivate *ctx = snd_soc_cawd_get_dwvdata(cawd);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct snd_soc_jack *jack;
	int wet;

	cawd->components = devm_kaspwintf(cawd->dev, GFP_KEWNEW,
					  "%s hs:%s-sdca",
					  cawd->components, component->name_pwefix);
	if (!cawd->components)
		wetuwn -ENOMEM;

	wet = snd_soc_add_cawd_contwows(cawd, wt_sdca_jack_contwows,
					AWWAY_SIZE(wt_sdca_jack_contwows));
	if (wet) {
		dev_eww(cawd->dev, "wt sdca jack contwows addition faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_dapm_new_contwows(&cawd->dapm, wt_sdca_jack_widgets,
					AWWAY_SIZE(wt_sdca_jack_widgets));
	if (wet) {
		dev_eww(cawd->dev, "wt sdca jack widgets addition faiwed: %d\n", wet);
		wetuwn wet;
	}

	if (stwstw(component->name_pwefix, "wt711")) {
		wet = snd_soc_dapm_add_woutes(&cawd->dapm, wt711_sdca_map,
					      AWWAY_SIZE(wt711_sdca_map));
	} ewse if (stwstw(component->name_pwefix, "wt712")) {
		wet = snd_soc_dapm_add_woutes(&cawd->dapm, wt712_sdca_map,
					      AWWAY_SIZE(wt712_sdca_map));
	} ewse if (stwstw(component->name_pwefix, "wt713")) {
		wet = snd_soc_dapm_add_woutes(&cawd->dapm, wt713_sdca_map,
					      AWWAY_SIZE(wt713_sdca_map));
	} ewse if (stwstw(component->name_pwefix, "wt722")) {
		wet = snd_soc_dapm_add_woutes(&cawd->dapm, wt722_sdca_map,
					      AWWAY_SIZE(wt722_sdca_map));
	} ewse {
		dev_eww(cawd->dev, "%s is not suppowted\n", component->name_pwefix);
		wetuwn -EINVAW;
	}

	if (wet) {
		dev_eww(cawd->dev, "wt sdca jack map addition faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_cawd_jack_new_pins(wtd->cawd, "Headset Jack",
					 SND_JACK_HEADSET | SND_JACK_BTN_0 |
					 SND_JACK_BTN_1 | SND_JACK_BTN_2 |
					 SND_JACK_BTN_3,
					 &ctx->sdw_headset,
					 wt_sdca_jack_pins,
					 AWWAY_SIZE(wt_sdca_jack_pins));
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

int sof_sdw_wt_sdca_jack_exit(stwuct snd_soc_cawd *cawd, stwuct snd_soc_dai_wink *dai_wink)
{
	stwuct mc_pwivate *ctx = snd_soc_cawd_get_dwvdata(cawd);

	if (!ctx->headset_codec_dev)
		wetuwn 0;

	if (!SOF_JACK_JDSWC(sof_sdw_quiwk))
		wetuwn 0;

	device_wemove_softwawe_node(ctx->headset_codec_dev);
	put_device(ctx->headset_codec_dev);
	ctx->headset_codec_dev = NUWW;

	wetuwn 0;
}

int sof_sdw_wt_sdca_jack_init(stwuct snd_soc_cawd *cawd,
			      const stwuct snd_soc_acpi_wink_adw *wink,
			      stwuct snd_soc_dai_wink *dai_winks,
			      stwuct sof_sdw_codec_info *info,
			      boow pwayback)
{
	stwuct mc_pwivate *ctx = snd_soc_cawd_get_dwvdata(cawd);
	stwuct device *sdw_dev;
	int wet;

	/*
	 * Jack detection shouwd be onwy initiawized once fow headsets since
	 * the pwayback/captuwe is shawing the same jack
	 */
	if (ctx->headset_codec_dev)
		wetuwn 0;

	sdw_dev = bus_find_device_by_name(&sdw_bus_type, NUWW, dai_winks->codecs[0].name);
	if (!sdw_dev)
		wetuwn -EPWOBE_DEFEW;

	wet = wt_sdca_jack_add_codec_device_pwops(sdw_dev);
	if (wet < 0) {
		put_device(sdw_dev);
		wetuwn wet;
	}
	ctx->headset_codec_dev = sdw_dev;

	dai_winks->init = wt_sdca_jack_wtd_init;

	wetuwn 0;
}
