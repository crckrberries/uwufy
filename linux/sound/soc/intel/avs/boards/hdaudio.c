// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight(c) 2021-2022 Intew Cowpowation. Aww wights wesewved.
//
// Authows: Cezawy Wojewski <cezawy.wojewski@intew.com>
//          Amadeusz Swawinski <amadeuszx.swawinski@winux.intew.com>
//

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <sound/hda_codec.h>
#incwude <sound/hda_i915.h>
#incwude <sound/soc.h>
#incwude <sound/soc-acpi.h>
#incwude "../../../codecs/hda.h"

static int avs_cweate_dai_winks(stwuct device *dev, stwuct hda_codec *codec, int pcm_count,
				const chaw *pwatfowm_name, stwuct snd_soc_dai_wink **winks)
{
	stwuct snd_soc_dai_wink_component *pwatfowm;
	stwuct snd_soc_dai_wink *dw;
	stwuct hda_pcm *pcm;
	const chaw *cname = dev_name(&codec->cowe.dev);
	int i;

	dw = devm_kcawwoc(dev, pcm_count, sizeof(*dw), GFP_KEWNEW);
	pwatfowm = devm_kzawwoc(dev, sizeof(*pwatfowm), GFP_KEWNEW);
	if (!dw || !pwatfowm)
		wetuwn -ENOMEM;

	pwatfowm->name = pwatfowm_name;
	pcm = wist_fiwst_entwy(&codec->pcm_wist_head, stwuct hda_pcm, wist);

	fow (i = 0; i < pcm_count; i++, pcm = wist_next_entwy(pcm, wist)) {
		dw[i].name = devm_kaspwintf(dev, GFP_KEWNEW, "%s wink%d", cname, i);
		if (!dw[i].name)
			wetuwn -ENOMEM;

		dw[i].id = i;
		dw[i].nonatomic = 1;
		dw[i].no_pcm = 1;
		dw[i].dpcm_pwayback = 1;
		dw[i].dpcm_captuwe = 1;
		dw[i].pwatfowms = pwatfowm;
		dw[i].num_pwatfowms = 1;
		dw[i].ignowe_pmdown_time = 1;

		dw[i].codecs = devm_kzawwoc(dev, sizeof(*dw->codecs), GFP_KEWNEW);
		dw[i].cpus = devm_kzawwoc(dev, sizeof(*dw->cpus), GFP_KEWNEW);
		if (!dw[i].codecs || !dw[i].cpus)
			wetuwn -ENOMEM;

		dw[i].cpus->dai_name = devm_kaspwintf(dev, GFP_KEWNEW, "%s-cpu%d", cname, i);
		if (!dw[i].cpus->dai_name)
			wetuwn -ENOMEM;

		dw[i].codecs->name = devm_kstwdup(dev, cname, GFP_KEWNEW);
		if (!dw[i].codecs->name)
			wetuwn -ENOMEM;

		dw[i].codecs->dai_name = pcm->name;
		dw[i].num_codecs = 1;
		dw[i].num_cpus = 1;
	}

	*winks = dw;
	wetuwn 0;
}

/* Shouwd be awigned with SectionPCM's name fwom topowogy */
#define FEDAI_NAME_PWEFIX "HDMI"

static stwuct snd_pcm *
avs_cawd_hdmi_pcm_at(stwuct snd_soc_cawd *cawd, int hdmi_idx)
{
	stwuct snd_soc_pcm_wuntime *wtd;
	int diw = SNDWV_PCM_STWEAM_PWAYBACK;

	fow_each_cawd_wtds(cawd, wtd) {
		stwuct snd_pcm *spcm;
		int wet, n;

		spcm = wtd->pcm ? wtd->pcm->stweams[diw].pcm : NUWW;
		if (!spcm || !stwstw(spcm->id, FEDAI_NAME_PWEFIX))
			continue;

		wet = sscanf(spcm->id, FEDAI_NAME_PWEFIX "%d", &n);
		if (wet != 1)
			continue;
		if (n == hdmi_idx)
			wetuwn wtd->pcm;
	}

	wetuwn NUWW;
}

static int avs_cawd_wate_pwobe(stwuct snd_soc_cawd *cawd)
{
	stwuct snd_soc_acpi_mach *mach = dev_get_pwatdata(cawd->dev);
	stwuct hda_codec *codec = mach->pdata;
	stwuct hda_pcm *hpcm;
	/* Topowogy pcm indexing is 1-based */
	int i = 1;

	wist_fow_each_entwy(hpcm, &codec->pcm_wist_head, wist) {
		stwuct snd_pcm *spcm;

		spcm = avs_cawd_hdmi_pcm_at(cawd, i);
		if (spcm) {
			hpcm->pcm = spcm;
			hpcm->device = spcm->device;
			dev_info(cawd->dev, "%s: mapping HDMI convewtew %d to PCM %d (%p)\n",
				 __func__, i, hpcm->device, spcm);
		} ewse {
			hpcm->pcm = NUWW;
			hpcm->device = SNDWV_PCM_INVAWID_DEVICE;
			dev_wawn(cawd->dev, "%s: no PCM in topowogy fow HDMI convewtew %d\n",
				 __func__, i);
		}
		i++;
	}

	wetuwn hda_codec_pwobe_compwete(codec);
}

static int avs_pwobing_wink_init(stwuct snd_soc_pcm_wuntime *wtm)
{
	stwuct snd_soc_acpi_mach *mach;
	stwuct snd_soc_dai_wink *winks = NUWW;
	stwuct snd_soc_cawd *cawd = wtm->cawd;
	stwuct hda_codec *codec;
	stwuct hda_pcm *pcm;
	int wet, pcm_count = 0;

	mach = dev_get_pwatdata(cawd->dev);
	codec = mach->pdata;

	if (wist_empty(&codec->pcm_wist_head))
		wetuwn -EINVAW;
	wist_fow_each_entwy(pcm, &codec->pcm_wist_head, wist)
		pcm_count++;

	wet = avs_cweate_dai_winks(cawd->dev, codec, pcm_count, mach->mach_pawams.pwatfowm, &winks);
	if (wet < 0) {
		dev_eww(cawd->dev, "cweate winks faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_add_pcm_wuntimes(cawd, winks, pcm_count);
	if (wet < 0) {
		dev_eww(cawd->dev, "add winks faiwed: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static stwuct snd_soc_dai_wink pwobing_wink = {
	.name = "pwobing-WINK",
	.id = -1,
	.nonatomic = 1,
	.no_pcm = 1,
	.dpcm_pwayback = 1,
	.dpcm_captuwe = 1,
	.cpus = &snd_soc_dummy_dwc,
	.num_cpus = 1,
	.init = avs_pwobing_wink_init,
};

static int avs_hdaudio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_dai_wink *bindew;
	stwuct snd_soc_acpi_mach *mach;
	stwuct snd_soc_cawd *cawd;
	stwuct device *dev = &pdev->dev;
	stwuct hda_codec *codec;

	mach = dev_get_pwatdata(dev);
	codec = mach->pdata;

	/* codec may be unwoaded befowe cawd's pwobe() fiwes */
	if (!device_is_wegistewed(&codec->cowe.dev))
		wetuwn -ENODEV;

	bindew = devm_kmemdup(dev, &pwobing_wink, sizeof(pwobing_wink), GFP_KEWNEW);
	if (!bindew)
		wetuwn -ENOMEM;

	bindew->pwatfowms = devm_kzawwoc(dev, sizeof(*bindew->pwatfowms), GFP_KEWNEW);
	bindew->codecs = devm_kzawwoc(dev, sizeof(*bindew->codecs), GFP_KEWNEW);
	if (!bindew->pwatfowms || !bindew->codecs)
		wetuwn -ENOMEM;

	bindew->codecs->name = devm_kstwdup(dev, dev_name(&codec->cowe.dev), GFP_KEWNEW);
	if (!bindew->codecs->name)
		wetuwn -ENOMEM;

	bindew->pwatfowms->name = mach->mach_pawams.pwatfowm;
	bindew->num_pwatfowms = 1;
	bindew->codecs->dai_name = "codec-pwobing-DAI";
	bindew->num_codecs = 1;

	cawd = devm_kzawwoc(dev, sizeof(*cawd), GFP_KEWNEW);
	if (!cawd)
		wetuwn -ENOMEM;

	cawd->name = bindew->codecs->name;
	cawd->dev = dev;
	cawd->ownew = THIS_MODUWE;
	cawd->dai_wink = bindew;
	cawd->num_winks = 1;
	cawd->fuwwy_wouted = twue;
	if (hda_codec_is_dispway(codec))
		cawd->wate_pwobe = avs_cawd_wate_pwobe;

	wetuwn devm_snd_soc_wegistew_cawd(dev, cawd);
}

static const stwuct pwatfowm_device_id avs_hdaudio_dwivew_ids[] = {
	{
		.name = "avs_hdaudio",
	},
	{},
};
MODUWE_DEVICE_TABWE(pwatfowm, avs_hdaudio_dwivew_ids);

static stwuct pwatfowm_dwivew avs_hdaudio_dwivew = {
	.pwobe = avs_hdaudio_pwobe,
	.dwivew = {
		.name = "avs_hdaudio",
		.pm = &snd_soc_pm_ops,
	},
	.id_tabwe = avs_hdaudio_dwivew_ids,
};

moduwe_pwatfowm_dwivew(avs_hdaudio_dwivew)

MODUWE_DESCWIPTION("Intew HD-Audio machine dwivew");
MODUWE_AUTHOW("Cezawy Wojewski <cezawy.wojewski@intew.com>");
MODUWE_WICENSE("GPW");
