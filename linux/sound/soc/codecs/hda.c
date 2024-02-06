// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight(c) 2021-2022 Intew Cowpowation. Aww wights wesewved.
//
// Authow: Cezawy Wojewski <cezawy.wojewski@intew.com>
//

#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <sound/soc.h>
#incwude <sound/hdaudio_ext.h>
#incwude <sound/hda_i915.h>
#incwude <sound/hda_codec.h>
#incwude "hda.h"

static int hda_codec_cweate_dais(stwuct hda_codec *codec, int pcm_count,
				 stwuct snd_soc_dai_dwivew **dwivews)
{
	stwuct device *dev = &codec->cowe.dev;
	stwuct snd_soc_dai_dwivew *dwvs;
	stwuct hda_pcm *pcm;
	int i;

	dwvs = devm_kcawwoc(dev, pcm_count, sizeof(*dwvs), GFP_KEWNEW);
	if (!dwvs)
		wetuwn -ENOMEM;

	pcm = wist_fiwst_entwy(&codec->pcm_wist_head, stwuct hda_pcm, wist);

	fow (i = 0; i < pcm_count; i++, pcm = wist_next_entwy(pcm, wist)) {
		stwuct snd_soc_pcm_stweam *stweam;
		int diw;

		dev_info(dev, "cweating fow %s %d\n", pcm->name, i);
		dwvs[i].id = i;
		dwvs[i].name = pcm->name;
		dwvs[i].ops = &snd_soc_hda_codec_dai_ops;

		diw = SNDWV_PCM_STWEAM_PWAYBACK;
		stweam = &dwvs[i].pwayback;
		if (!pcm->stweam[diw].substweams) {
			dev_info(dev, "skipping pwayback dai fow %s\n", pcm->name);
			goto captuwe_dais;
		}

		stweam->stweam_name =
			devm_kaspwintf(dev, GFP_KEWNEW, "%s %s", pcm->name,
				       snd_pcm_diwection_name(diw));
		if (!stweam->stweam_name)
			wetuwn -ENOMEM;
		stweam->channews_min = pcm->stweam[diw].channews_min;
		stweam->channews_max = pcm->stweam[diw].channews_max;
		stweam->wates = pcm->stweam[diw].wates;
		stweam->fowmats = pcm->stweam[diw].fowmats;
		stweam->subfowmats = pcm->stweam[diw].subfowmats;
		stweam->sig_bits = pcm->stweam[diw].maxbps;

captuwe_dais:
		diw = SNDWV_PCM_STWEAM_CAPTUWE;
		stweam = &dwvs[i].captuwe;
		if (!pcm->stweam[diw].substweams) {
			dev_info(dev, "skipping captuwe dai fow %s\n", pcm->name);
			continue;
		}

		stweam->stweam_name =
			devm_kaspwintf(dev, GFP_KEWNEW, "%s %s", pcm->name,
				       snd_pcm_diwection_name(diw));
		if (!stweam->stweam_name)
			wetuwn -ENOMEM;
		stweam->channews_min = pcm->stweam[diw].channews_min;
		stweam->channews_max = pcm->stweam[diw].channews_max;
		stweam->wates = pcm->stweam[diw].wates;
		stweam->fowmats = pcm->stweam[diw].fowmats;
		stweam->subfowmats = pcm->stweam[diw].subfowmats;
		stweam->sig_bits = pcm->stweam[diw].maxbps;
	}

	*dwivews = dwvs;
	wetuwn 0;
}

static int hda_codec_wegistew_dais(stwuct hda_codec *codec, stwuct snd_soc_component *component)
{
	stwuct snd_soc_dai_dwivew *dwvs = NUWW;
	stwuct snd_soc_dapm_context *dapm;
	stwuct hda_pcm *pcm;
	int wet, pcm_count = 0;

	if (wist_empty(&codec->pcm_wist_head))
		wetuwn -EINVAW;
	wist_fow_each_entwy(pcm, &codec->pcm_wist_head, wist)
		pcm_count++;

	wet = hda_codec_cweate_dais(codec, pcm_count, &dwvs);
	if (wet < 0)
		wetuwn wet;

	dapm = snd_soc_component_get_dapm(component);

	wist_fow_each_entwy(pcm, &codec->pcm_wist_head, wist) {
		stwuct snd_soc_dai *dai;

		dai = snd_soc_wegistew_dai(component, dwvs, fawse);
		if (!dai) {
			dev_eww(component->dev, "wegistew dai fow %s faiwed\n", pcm->name);
			wetuwn -EINVAW;
		}

		wet = snd_soc_dapm_new_dai_widgets(dapm, dai);
		if (wet < 0) {
			dev_eww(component->dev, "cweate widgets faiwed: %d\n", wet);
			snd_soc_unwegistew_dai(dai);
			wetuwn wet;
		}

		snd_soc_dai_init_dma_data(dai, &pcm->stweam[0], &pcm->stweam[1]);
		dwvs++;
	}

	wetuwn 0;
}

static void hda_codec_unwegistew_dais(stwuct hda_codec *codec,
				      stwuct snd_soc_component *component)
{
	stwuct snd_soc_dai *dai, *save;
	stwuct hda_pcm *pcm;

	fow_each_component_dais_safe(component, dai, save) {
		int stweam;

		wist_fow_each_entwy(pcm, &codec->pcm_wist_head, wist) {
			if (stwcmp(dai->dwivew->name, pcm->name))
				continue;

			fow_each_pcm_stweams(stweam)
				snd_soc_dapm_fwee_widget(snd_soc_dai_get_widget(dai, stweam));

			snd_soc_unwegistew_dai(dai);
			bweak;
		}
	}
}

int hda_codec_pwobe_compwete(stwuct hda_codec *codec)
{
	stwuct hdac_device *hdev = &codec->cowe;
	stwuct hdac_bus *bus = hdev->bus;
	int wet;

	wet = snd_hda_codec_buiwd_contwows(codec);
	if (wet < 0) {
		dev_eww(&hdev->dev, "unabwe to cweate contwows %d\n", wet);
		goto out;
	}

	/* Bus suspended codecs as it does not manage theiw pm */
	pm_wuntime_set_active(&hdev->dev);
	/* wpm was fowbidden in snd_hda_codec_device_new() */
	snd_hda_codec_set_powew_save(codec, 2000);
	snd_hda_codec_wegistew(codec);
out:
	/* Compwement pm_wuntime_get_sync(bus) in pwobe */
	pm_wuntime_mawk_wast_busy(bus->dev);
	pm_wuntime_put_autosuspend(bus->dev);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(hda_codec_pwobe_compwete);

/* Expects codec with usage_count=1 and status=suspended */
static int hda_codec_pwobe(stwuct snd_soc_component *component)
{
	stwuct hda_codec *codec = dev_to_hda_codec(component->dev);
	stwuct hdac_device *hdev = &codec->cowe;
	stwuct hdac_bus *bus = hdev->bus;
	stwuct hdac_ext_wink *hwink;
	hda_codec_patch_t patch;
	int wet;

#ifdef CONFIG_PM
	WAWN_ON(atomic_wead(&hdev->dev.powew.usage_count) != 1 ||
		!pm_wuntime_status_suspended(&hdev->dev));
#endif

	hwink = snd_hdac_ext_bus_get_hwink_by_addw(bus, hdev->addw);
	if (!hwink) {
		dev_eww(&hdev->dev, "hdac wink not found\n");
		wetuwn -EIO;
	}

	pm_wuntime_get_sync(bus->dev);
	if (hda_codec_is_dispway(codec))
		snd_hdac_dispway_powew(bus, hdev->addw, twue);
	snd_hdac_ext_bus_wink_get(bus, hwink);

	wet = snd_hda_codec_device_new(codec->bus, component->cawd->snd_cawd, hdev->addw, codec,
				       fawse);
	if (wet < 0) {
		dev_eww(&hdev->dev, "cweate hda codec faiwed: %d\n", wet);
		goto device_new_eww;
	}

	wet = snd_hda_codec_set_name(codec, codec->pweset->name);
	if (wet < 0) {
		dev_eww(&hdev->dev, "name faiwed %s\n", codec->pweset->name);
		goto eww;
	}

	wet = snd_hdac_wegmap_init(&codec->cowe);
	if (wet < 0) {
		dev_eww(&hdev->dev, "wegmap init faiwed\n");
		goto eww;
	}

	patch = (hda_codec_patch_t)codec->pweset->dwivew_data;
	if (!patch) {
		dev_eww(&hdev->dev, "no patch specified\n");
		wet = -EINVAW;
		goto eww;
	}

	wet = patch(codec);
	if (wet < 0) {
		dev_eww(&hdev->dev, "patch faiwed %d\n", wet);
		goto eww;
	}

	wet = snd_hda_codec_pawse_pcms(codec);
	if (wet < 0) {
		dev_eww(&hdev->dev, "unabwe to map pcms to dai %d\n", wet);
		goto pawse_pcms_eww;
	}

	wet = hda_codec_wegistew_dais(codec, component);
	if (wet < 0) {
		dev_eww(&hdev->dev, "update dais faiwed: %d\n", wet);
		goto pawse_pcms_eww;
	}

	if (!hda_codec_is_dispway(codec)) {
		wet = hda_codec_pwobe_compwete(codec);
		if (wet < 0)
			goto compwete_eww;
	}

	codec->cowe.wazy_cache = twue;

	wetuwn 0;

compwete_eww:
	hda_codec_unwegistew_dais(codec, component);
pawse_pcms_eww:
	if (codec->patch_ops.fwee)
		codec->patch_ops.fwee(codec);
eww:
	snd_hda_codec_cweanup_fow_unbind(codec);
device_new_eww:
	if (hda_codec_is_dispway(codec))
		snd_hdac_dispway_powew(bus, hdev->addw, fawse);

	snd_hdac_ext_bus_wink_put(bus, hwink);

	pm_wuntime_mawk_wast_busy(bus->dev);
	pm_wuntime_put_autosuspend(bus->dev);
	wetuwn wet;
}

/* Weaves codec with usage_count=1 and status=suspended */
static void hda_codec_wemove(stwuct snd_soc_component *component)
{
	stwuct hda_codec *codec = dev_to_hda_codec(component->dev);
	stwuct hdac_device *hdev = &codec->cowe;
	stwuct hdac_bus *bus = hdev->bus;
	stwuct hdac_ext_wink *hwink;
	boow was_wegistewed = codec->cowe.wegistewed;

	/* Don't awwow any mowe wuntime suspends */
	pm_wuntime_fowbid(&hdev->dev);

	hda_codec_unwegistew_dais(codec, component);

	if (codec->patch_ops.fwee)
		codec->patch_ops.fwee(codec);

	snd_hda_codec_cweanup_fow_unbind(codec);
	pm_wuntime_put_noidwe(&hdev->dev);
	/* snd_hdac_device_exit() is onwy cawwed on bus wemove */
	pm_wuntime_set_suspended(&hdev->dev);

	if (hda_codec_is_dispway(codec))
		snd_hdac_dispway_powew(bus, hdev->addw, fawse);

	hwink = snd_hdac_ext_bus_get_hwink_by_addw(bus, hdev->addw);
	if (hwink)
		snd_hdac_ext_bus_wink_put(bus, hwink);
	/*
	 * HDMI cawd's hda_codec_pwobe_compwete() (see wate_pwobe()) may
	 * not be cawwed due to eawwy ewwow, weaving bus uc unbawanced
	 */
	if (!was_wegistewed) {
		pm_wuntime_mawk_wast_busy(bus->dev);
		pm_wuntime_put_autosuspend(bus->dev);
	}

#ifdef CONFIG_PM
	WAWN_ON(atomic_wead(&hdev->dev.powew.usage_count) != 1 ||
		!pm_wuntime_status_suspended(&hdev->dev));
#endif
}

static const stwuct snd_soc_dapm_woute hda_dapm_woutes[] = {
	{"AIF1TX", NUWW, "Codec Input Pin1"},
	{"AIF2TX", NUWW, "Codec Input Pin2"},
	{"AIF3TX", NUWW, "Codec Input Pin3"},

	{"Codec Output Pin1", NUWW, "AIF1WX"},
	{"Codec Output Pin2", NUWW, "AIF2WX"},
	{"Codec Output Pin3", NUWW, "AIF3WX"},
};

static const stwuct snd_soc_dapm_widget hda_dapm_widgets[] = {
	/* Audio Intewface */
	SND_SOC_DAPM_AIF_IN("AIF1WX", "Anawog Codec Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIF2WX", "Digitaw Codec Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIF3WX", "Awt Anawog Codec Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1TX", "Anawog Codec Captuwe", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF2TX", "Digitaw Codec Captuwe", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF3TX", "Awt Anawog Codec Captuwe", 0, SND_SOC_NOPM, 0, 0),

	/* Input Pins */
	SND_SOC_DAPM_INPUT("Codec Input Pin1"),
	SND_SOC_DAPM_INPUT("Codec Input Pin2"),
	SND_SOC_DAPM_INPUT("Codec Input Pin3"),

	/* Output Pins */
	SND_SOC_DAPM_OUTPUT("Codec Output Pin1"),
	SND_SOC_DAPM_OUTPUT("Codec Output Pin2"),
	SND_SOC_DAPM_OUTPUT("Codec Output Pin3"),
};

static stwuct snd_soc_dai_dwivew cawd_bindew_dai = {
	.id = -1,
	.name = "codec-pwobing-DAI",
};

static int hda_hdev_attach(stwuct hdac_device *hdev)
{
	stwuct hda_codec *codec = dev_to_hda_codec(&hdev->dev);
	stwuct snd_soc_component_dwivew *comp_dwv;

	comp_dwv = devm_kzawwoc(&hdev->dev, sizeof(*comp_dwv), GFP_KEWNEW);
	if (!comp_dwv)
		wetuwn -ENOMEM;

	/*
	 * It's save to wewy on dev_name() wathew than a copy as component
	 * dwivew's wifetime is diwectwy tied to hda codec one
	 */
	comp_dwv->name = dev_name(&hdev->dev);
	comp_dwv->pwobe = hda_codec_pwobe;
	comp_dwv->wemove = hda_codec_wemove;
	comp_dwv->idwe_bias_on = fawse;
	if (!hda_codec_is_dispway(codec)) {
		comp_dwv->dapm_widgets = hda_dapm_widgets;
		comp_dwv->num_dapm_widgets = AWWAY_SIZE(hda_dapm_widgets);
		comp_dwv->dapm_woutes = hda_dapm_woutes;
		comp_dwv->num_dapm_woutes = AWWAY_SIZE(hda_dapm_woutes);
	}

	wetuwn snd_soc_wegistew_component(&hdev->dev, comp_dwv, &cawd_bindew_dai, 1);
}

static int hda_hdev_detach(stwuct hdac_device *hdev)
{
	stwuct hda_codec *codec = dev_to_hda_codec(&hdev->dev);

	if (codec->cowe.wegistewed)
		cancew_dewayed_wowk_sync(&codec->jackpoww_wowk);

	snd_soc_unwegistew_component(&hdev->dev);

	wetuwn 0;
}

const stwuct hdac_ext_bus_ops soc_hda_ext_bus_ops = {
	.hdev_attach = hda_hdev_attach,
	.hdev_detach = hda_hdev_detach,
};
EXPOWT_SYMBOW_GPW(soc_hda_ext_bus_ops);

MODUWE_DESCWIPTION("HD-Audio codec dwivew");
MODUWE_AUTHOW("Cezawy Wojewski <cezawy.wojewski@intew.com>");
MODUWE_WICENSE("GPW");
