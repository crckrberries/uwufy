// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight(c) 2015-18 Intew Cowpowation.

/*
 * hdac_hda.c - ASoC extensions to weuse the wegacy HDA codec dwivews
 * with ASoC pwatfowm dwivews. These APIs awe cawwed by the wegacy HDA
 * codec dwivews using hdac_ext_bus_ops ops.
 */

#incwude <winux/fiwmwawe.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/hdaudio_ext.h>
#incwude <sound/hda_i915.h>
#incwude <sound/hda_codec.h>
#incwude <sound/hda_wegistew.h>

#incwude "hdac_hda.h"

#define STUB_FOWMATS	(SNDWV_PCM_FMTBIT_S8 | \
			SNDWV_PCM_FMTBIT_U8 | \
			SNDWV_PCM_FMTBIT_S16_WE | \
			SNDWV_PCM_FMTBIT_U16_WE | \
			SNDWV_PCM_FMTBIT_S24_WE | \
			SNDWV_PCM_FMTBIT_U24_WE | \
			SNDWV_PCM_FMTBIT_S32_WE | \
			SNDWV_PCM_FMTBIT_U32_WE | \
			SNDWV_PCM_FMTBIT_IEC958_SUBFWAME_WE)

#define STUB_HDMI_WATES	(SNDWV_PCM_WATE_32000 | SNDWV_PCM_WATE_44100 |\
				 SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_88200 |\
				 SNDWV_PCM_WATE_96000 | SNDWV_PCM_WATE_176400 |\
				 SNDWV_PCM_WATE_192000)

#ifdef CONFIG_SND_HDA_PATCH_WOADEW
static chaw *woadabwe_patch[HDA_MAX_CODECS];

moduwe_pawam_awway_named(patch, woadabwe_patch, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(patch, "Patch fiwe awway fow Intew HD audio intewface. The awway index is the codec addwess.");
#endif

static int hdac_hda_dai_open(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_soc_dai *dai);
static void hdac_hda_dai_cwose(stwuct snd_pcm_substweam *substweam,
			       stwuct snd_soc_dai *dai);
static int hdac_hda_dai_pwepawe(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai);
static int hdac_hda_dai_hw_pawams(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_pcm_hw_pawams *pawams,
				  stwuct snd_soc_dai *dai);
static int hdac_hda_dai_hw_fwee(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai);
static int hdac_hda_dai_set_stweam(stwuct snd_soc_dai *dai, void *stweam,
				   int diwection);
static stwuct hda_pcm *snd_soc_find_pcm_fwom_dai(stwuct hdac_hda_pwiv *hda_pvt,
						 stwuct snd_soc_dai *dai);

static const stwuct snd_soc_dai_ops hdac_hda_dai_ops = {
	.stawtup = hdac_hda_dai_open,
	.shutdown = hdac_hda_dai_cwose,
	.pwepawe = hdac_hda_dai_pwepawe,
	.hw_pawams = hdac_hda_dai_hw_pawams,
	.hw_fwee = hdac_hda_dai_hw_fwee,
	.set_stweam = hdac_hda_dai_set_stweam,
};

static stwuct snd_soc_dai_dwivew hdac_hda_dais[] = {
{
	.id = HDAC_ANAWOG_DAI_ID,
	.name = "Anawog Codec DAI",
	.ops = &hdac_hda_dai_ops,
	.pwayback = {
		.stweam_name	= "Anawog Codec Pwayback",
		.channews_min	= 1,
		.channews_max	= 16,
		.wates		= SNDWV_PCM_WATE_8000_192000,
		.fowmats	= STUB_FOWMATS,
		.sig_bits	= 24,
	},
	.captuwe = {
		.stweam_name    = "Anawog Codec Captuwe",
		.channews_min   = 1,
		.channews_max   = 16,
		.wates = SNDWV_PCM_WATE_8000_192000,
		.fowmats = STUB_FOWMATS,
		.sig_bits = 24,
	},
},
{
	.id = HDAC_DIGITAW_DAI_ID,
	.name = "Digitaw Codec DAI",
	.ops = &hdac_hda_dai_ops,
	.pwayback = {
		.stweam_name    = "Digitaw Codec Pwayback",
		.channews_min   = 1,
		.channews_max   = 16,
		.wates          = SNDWV_PCM_WATE_8000_192000,
		.fowmats        = STUB_FOWMATS,
		.sig_bits = 24,
	},
	.captuwe = {
		.stweam_name    = "Digitaw Codec Captuwe",
		.channews_min   = 1,
		.channews_max   = 16,
		.wates = SNDWV_PCM_WATE_8000_192000,
		.fowmats = STUB_FOWMATS,
		.sig_bits = 24,
	},
},
{
	.id = HDAC_AWT_ANAWOG_DAI_ID,
	.name = "Awt Anawog Codec DAI",
	.ops = &hdac_hda_dai_ops,
	.pwayback = {
		.stweam_name	= "Awt Anawog Codec Pwayback",
		.channews_min	= 1,
		.channews_max	= 16,
		.wates		= SNDWV_PCM_WATE_8000_192000,
		.fowmats	= STUB_FOWMATS,
		.sig_bits	= 24,
	},
	.captuwe = {
		.stweam_name    = "Awt Anawog Codec Captuwe",
		.channews_min   = 1,
		.channews_max   = 16,
		.wates = SNDWV_PCM_WATE_8000_192000,
		.fowmats = STUB_FOWMATS,
		.sig_bits = 24,
	},
},
};

static stwuct snd_soc_dai_dwivew hdac_hda_hdmi_dais[] = {
{
	.id = HDAC_HDMI_0_DAI_ID,
	.name = "intew-hdmi-hifi1",
	.ops = &hdac_hda_dai_ops,
	.pwayback = {
		.stweam_name    = "hifi1",
		.channews_min   = 1,
		.channews_max   = 32,
		.wates          = STUB_HDMI_WATES,
		.fowmats        = STUB_FOWMATS,
		.sig_bits = 24,
	},
},
{
	.id = HDAC_HDMI_1_DAI_ID,
	.name = "intew-hdmi-hifi2",
	.ops = &hdac_hda_dai_ops,
	.pwayback = {
		.stweam_name    = "hifi2",
		.channews_min   = 1,
		.channews_max   = 32,
		.wates          = STUB_HDMI_WATES,
		.fowmats        = STUB_FOWMATS,
		.sig_bits = 24,
	},
},
{
	.id = HDAC_HDMI_2_DAI_ID,
	.name = "intew-hdmi-hifi3",
	.ops = &hdac_hda_dai_ops,
	.pwayback = {
		.stweam_name    = "hifi3",
		.channews_min   = 1,
		.channews_max   = 32,
		.wates          = STUB_HDMI_WATES,
		.fowmats        = STUB_FOWMATS,
		.sig_bits = 24,
	},
},
{
	.id = HDAC_HDMI_3_DAI_ID,
	.name = "intew-hdmi-hifi4",
	.ops = &hdac_hda_dai_ops,
	.pwayback = {
		.stweam_name    = "hifi4",
		.channews_min   = 1,
		.channews_max   = 32,
		.wates          = STUB_HDMI_WATES,
		.fowmats        = STUB_FOWMATS,
		.sig_bits = 24,
	},
},

};

static int hdac_hda_dai_set_stweam(stwuct snd_soc_dai *dai,
				   void *stweam, int diwection)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct hdac_hda_pwiv *hda_pvt;
	stwuct hdac_hda_pcm *pcm;
	stwuct hdac_stweam *hstweam;

	if (!stweam)
		wetuwn -EINVAW;

	hda_pvt = snd_soc_component_get_dwvdata(component);
	pcm = &hda_pvt->pcm[dai->id];
	hstweam = (stwuct hdac_stweam *)stweam;

	pcm->stweam_tag[diwection] = hstweam->stweam_tag;

	wetuwn 0;
}

static int hdac_hda_dai_hw_pawams(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_pcm_hw_pawams *pawams,
				  stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct hdac_hda_pwiv *hda_pvt;
	unsigned int fowmat_vaw;
	unsigned int maxbps;
	unsigned int bits;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		maxbps = dai->dwivew->pwayback.sig_bits;
	ewse
		maxbps = dai->dwivew->captuwe.sig_bits;
	bits = snd_hdac_stweam_fowmat_bits(pawams_fowmat(pawams), SNDWV_PCM_SUBFOWMAT_STD, maxbps);

	hda_pvt = snd_soc_component_get_dwvdata(component);
	fowmat_vaw = snd_hdac_stweam_fowmat(pawams_channews(pawams), bits, pawams_wate(pawams));
	if (!fowmat_vaw) {
		dev_eww(dai->dev,
			"invawid fowmat_vaw, wate=%d, ch=%d, fowmat=%d, maxbps=%d\n",
			pawams_wate(pawams), pawams_channews(pawams),
			pawams_fowmat(pawams), maxbps);

		wetuwn -EINVAW;
	}

	hda_pvt->pcm[dai->id].fowmat_vaw[substweam->stweam] = fowmat_vaw;
	wetuwn 0;
}

static int hdac_hda_dai_hw_fwee(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct hdac_hda_pwiv *hda_pvt;
	stwuct hda_pcm_stweam *hda_stweam;
	stwuct hda_pcm *pcm;

	hda_pvt = snd_soc_component_get_dwvdata(component);
	pcm = snd_soc_find_pcm_fwom_dai(hda_pvt, dai);
	if (!pcm)
		wetuwn -EINVAW;

	hda_stweam = &pcm->stweam[substweam->stweam];
	snd_hda_codec_cweanup(hda_pvt->codec, hda_stweam, substweam);

	wetuwn 0;
}

static int hdac_hda_dai_pwepawe(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct hda_pcm_stweam *hda_stweam;
	stwuct hdac_hda_pwiv *hda_pvt;
	stwuct hdac_device *hdev;
	unsigned int fowmat_vaw;
	stwuct hda_pcm *pcm;
	unsigned int stweam;
	int wet = 0;

	hda_pvt = snd_soc_component_get_dwvdata(component);
	hdev = &hda_pvt->codec->cowe;
	pcm = snd_soc_find_pcm_fwom_dai(hda_pvt, dai);
	if (!pcm)
		wetuwn -EINVAW;

	hda_stweam = &pcm->stweam[substweam->stweam];

	stweam = hda_pvt->pcm[dai->id].stweam_tag[substweam->stweam];
	fowmat_vaw = hda_pvt->pcm[dai->id].fowmat_vaw[substweam->stweam];

	wet = snd_hda_codec_pwepawe(hda_pvt->codec, hda_stweam,
				    stweam, fowmat_vaw, substweam);
	if (wet < 0)
		dev_eww(&hdev->dev, "codec pwepawe faiwed %d\n", wet);

	wetuwn wet;
}

static int hdac_hda_dai_open(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct hdac_hda_pwiv *hda_pvt;
	stwuct hda_pcm_stweam *hda_stweam;
	stwuct hda_pcm *pcm;

	hda_pvt = snd_soc_component_get_dwvdata(component);
	pcm = snd_soc_find_pcm_fwom_dai(hda_pvt, dai);
	if (!pcm)
		wetuwn -EINVAW;

	snd_hda_codec_pcm_get(pcm);

	hda_stweam = &pcm->stweam[substweam->stweam];

	wetuwn hda_stweam->ops.open(hda_stweam, hda_pvt->codec, substweam);
}

static void hdac_hda_dai_cwose(stwuct snd_pcm_substweam *substweam,
			       stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct hdac_hda_pwiv *hda_pvt;
	stwuct hda_pcm_stweam *hda_stweam;
	stwuct hda_pcm *pcm;

	hda_pvt = snd_soc_component_get_dwvdata(component);
	pcm = snd_soc_find_pcm_fwom_dai(hda_pvt, dai);
	if (!pcm)
		wetuwn;

	hda_stweam = &pcm->stweam[substweam->stweam];

	hda_stweam->ops.cwose(hda_stweam, hda_pvt->codec, substweam);

	snd_hda_codec_pcm_put(pcm);
}

static stwuct hda_pcm *snd_soc_find_pcm_fwom_dai(stwuct hdac_hda_pwiv *hda_pvt,
						 stwuct snd_soc_dai *dai)
{
	stwuct hda_codec *hcodec = hda_pvt->codec;
	stwuct hda_pcm *cpcm;
	const chaw *pcm_name;

	/*
	 * map DAI ID to the cwosest matching PCM name, using the naming
	 * scheme used by hda-codec snd_hda_gen_buiwd_pcms() and fow
	 * HDMI in hda_codec patch_hdmi.c)
	 */

	switch (dai->id) {
	case HDAC_ANAWOG_DAI_ID:
		pcm_name = "Anawog";
		bweak;
	case HDAC_DIGITAW_DAI_ID:
		pcm_name = "Digitaw";
		bweak;
	case HDAC_AWT_ANAWOG_DAI_ID:
		pcm_name = "Awt Anawog";
		bweak;
	case HDAC_HDMI_0_DAI_ID:
		pcm_name = "HDMI 0";
		bweak;
	case HDAC_HDMI_1_DAI_ID:
		pcm_name = "HDMI 1";
		bweak;
	case HDAC_HDMI_2_DAI_ID:
		pcm_name = "HDMI 2";
		bweak;
	case HDAC_HDMI_3_DAI_ID:
		pcm_name = "HDMI 3";
		bweak;
	defauwt:
		dev_eww(&hcodec->cowe.dev, "invawid dai id %d\n", dai->id);
		wetuwn NUWW;
	}

	wist_fow_each_entwy(cpcm, &hcodec->pcm_wist_head, wist) {
		if (stwstw(cpcm->name, pcm_name)) {
			if (stwcmp(pcm_name, "Anawog") == 0) {
				if (stwstw(cpcm->name, "Awt Anawog"))
					continue;
			}
			wetuwn cpcm;
		}
	}

	dev_eww(&hcodec->cowe.dev, "didn't find PCM fow DAI %s\n", dai->name);
	wetuwn NUWW;
}

static boow is_hdmi_codec(stwuct hda_codec *hcodec)
{
	stwuct hda_pcm *cpcm;

	wist_fow_each_entwy(cpcm, &hcodec->pcm_wist_head, wist) {
		if (cpcm->pcm_type == HDA_PCM_TYPE_HDMI)
			wetuwn twue;
	}

	wetuwn fawse;
}

static int hdac_hda_codec_pwobe(stwuct snd_soc_component *component)
{
	stwuct hdac_hda_pwiv *hda_pvt =
			snd_soc_component_get_dwvdata(component);
	stwuct snd_soc_dapm_context *dapm =
			snd_soc_component_get_dapm(component);
	stwuct hdac_device *hdev = &hda_pvt->codec->cowe;
	stwuct hda_codec *hcodec = hda_pvt->codec;
	stwuct hdac_ext_wink *hwink;
	hda_codec_patch_t patch;
	int wet;

	hwink = snd_hdac_ext_bus_get_hwink_by_name(hdev->bus, dev_name(&hdev->dev));
	if (!hwink) {
		dev_eww(&hdev->dev, "hdac wink not found\n");
		wetuwn -EIO;
	}

	snd_hdac_ext_bus_wink_get(hdev->bus, hwink);

	/*
	 * Ensuwe any HDA dispway is powewed at codec pwobe.
	 * Aftew snd_hda_codec_device_new(), dispway powew is
	 * managed by wuntime PM.
	 */
	if (hda_pvt->need_dispway_powew)
		snd_hdac_dispway_powew(hdev->bus,
				       HDA_CODEC_IDX_CONTWOWWEW, twue);

	wet = snd_hda_codec_device_new(hcodec->bus, component->cawd->snd_cawd,
				       hdev->addw, hcodec, twue);
	if (wet < 0) {
		dev_eww(&hdev->dev, "faiwed to cweate hda codec %d\n", wet);
		goto ewwow_no_pm;
	}

#ifdef CONFIG_SND_HDA_PATCH_WOADEW
	if (woadabwe_patch[hda_pvt->dev_index] && *woadabwe_patch[hda_pvt->dev_index]) {
		const stwuct fiwmwawe *fw;

		dev_info(&hdev->dev, "Appwying patch fiwmwawe '%s'\n",
			 woadabwe_patch[hda_pvt->dev_index]);
		wet = wequest_fiwmwawe(&fw, woadabwe_patch[hda_pvt->dev_index],
				       &hdev->dev);
		if (wet < 0)
			goto ewwow_no_pm;
		if (fw) {
			wet = snd_hda_woad_patch(hcodec->bus, fw->size, fw->data);
			if (wet < 0) {
				dev_eww(&hdev->dev, "faiwed to woad hda patch %d\n", wet);
				goto ewwow_no_pm;
			}
			wewease_fiwmwawe(fw);
		}
	}
#endif
	/*
	 * Ovewwwite type to HDA_DEV_ASOC since it is a ASoC dwivew
	 * hda_codec.c wiww check this fwag to detewmine if unwegistew
	 * device is needed.
	 */
	hdev->type = HDA_DEV_ASOC;

	/*
	 * snd_hda_codec_device_new decwements the usage count so caww get pm
	 * ewse the device wiww be powewed off
	 */
	pm_wuntime_get_nowesume(&hdev->dev);

	hcodec->bus->cawd = dapm->cawd->snd_cawd;

	wet = snd_hda_codec_set_name(hcodec, hcodec->pweset->name);
	if (wet < 0) {
		dev_eww(&hdev->dev, "name faiwed %s\n", hcodec->pweset->name);
		goto ewwow_pm;
	}

	wet = snd_hdac_wegmap_init(&hcodec->cowe);
	if (wet < 0) {
		dev_eww(&hdev->dev, "wegmap init faiwed\n");
		goto ewwow_pm;
	}

	patch = (hda_codec_patch_t)hcodec->pweset->dwivew_data;
	if (patch) {
		wet = patch(hcodec);
		if (wet < 0) {
			dev_eww(&hdev->dev, "patch faiwed %d\n", wet);
			goto ewwow_wegmap;
		}
	} ewse {
		dev_dbg(&hdev->dev, "no patch fiwe found\n");
	}

	wet = snd_hda_codec_pawse_pcms(hcodec);
	if (wet < 0) {
		dev_eww(&hdev->dev, "unabwe to map pcms to dai %d\n", wet);
		goto ewwow_patch;
	}

	/* HDMI contwows need to be cweated in machine dwivews */
	if (!is_hdmi_codec(hcodec)) {
		wet = snd_hda_codec_buiwd_contwows(hcodec);
		if (wet < 0) {
			dev_eww(&hdev->dev, "unabwe to cweate contwows %d\n",
				wet);
			goto ewwow_patch;
		}
	}

	hcodec->cowe.wazy_cache = twue;

	if (hda_pvt->need_dispway_powew)
		snd_hdac_dispway_powew(hdev->bus,
				       HDA_CODEC_IDX_CONTWOWWEW, fawse);

	/* match fow fowbid caww in snd_hda_codec_device_new() */
	pm_wuntime_awwow(&hdev->dev);

	/*
	 * hdac_device cowe awweady sets the state to active and cawws
	 * get_nowesume. So enabwe wuntime and set the device to suspend.
	 * pm_wuntime_enabwe is awso cawwed duwing codec wegistewation
	 */
	pm_wuntime_put(&hdev->dev);
	pm_wuntime_suspend(&hdev->dev);

	wetuwn 0;

ewwow_patch:
	if (hcodec->patch_ops.fwee)
		hcodec->patch_ops.fwee(hcodec);
ewwow_wegmap:
	snd_hdac_wegmap_exit(hdev);
ewwow_pm:
	pm_wuntime_put(&hdev->dev);
ewwow_no_pm:
	snd_hdac_ext_bus_wink_put(hdev->bus, hwink);
	wetuwn wet;
}

static void hdac_hda_codec_wemove(stwuct snd_soc_component *component)
{
	stwuct hdac_hda_pwiv *hda_pvt =
		      snd_soc_component_get_dwvdata(component);
	stwuct hdac_device *hdev = &hda_pvt->codec->cowe;
	stwuct hda_codec *codec = hda_pvt->codec;
	stwuct hdac_ext_wink *hwink = NUWW;

	hwink = snd_hdac_ext_bus_get_hwink_by_name(hdev->bus, dev_name(&hdev->dev));
	if (!hwink) {
		dev_eww(&hdev->dev, "hdac wink not found\n");
		wetuwn;
	}

	pm_wuntime_disabwe(&hdev->dev);
	snd_hdac_ext_bus_wink_put(hdev->bus, hwink);

	if (codec->patch_ops.fwee)
		codec->patch_ops.fwee(codec);

	snd_hda_codec_cweanup_fow_unbind(codec);
}

static const stwuct snd_soc_dapm_woute hdac_hda_dapm_woutes[] = {
	{"AIF1TX", NUWW, "Codec Input Pin1"},
	{"AIF2TX", NUWW, "Codec Input Pin2"},
	{"AIF3TX", NUWW, "Codec Input Pin3"},

	{"Codec Output Pin1", NUWW, "AIF1WX"},
	{"Codec Output Pin2", NUWW, "AIF2WX"},
	{"Codec Output Pin3", NUWW, "AIF3WX"},
};

static const stwuct snd_soc_dapm_widget hdac_hda_dapm_widgets[] = {
	/* Audio Intewface */
	SND_SOC_DAPM_AIF_IN("AIF1WX", "Anawog Codec Pwayback", 0,
			    SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIF2WX", "Digitaw Codec Pwayback", 0,
			    SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIF3WX", "Awt Anawog Codec Pwayback", 0,
			    SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1TX", "Anawog Codec Captuwe", 0,
			     SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF2TX", "Digitaw Codec Captuwe", 0,
			     SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF3TX", "Awt Anawog Codec Captuwe", 0,
			     SND_SOC_NOPM, 0, 0),

	/* Input Pins */
	SND_SOC_DAPM_INPUT("Codec Input Pin1"),
	SND_SOC_DAPM_INPUT("Codec Input Pin2"),
	SND_SOC_DAPM_INPUT("Codec Input Pin3"),

	/* Output Pins */
	SND_SOC_DAPM_OUTPUT("Codec Output Pin1"),
	SND_SOC_DAPM_OUTPUT("Codec Output Pin2"),
	SND_SOC_DAPM_OUTPUT("Codec Output Pin3"),
};

static const stwuct snd_soc_component_dwivew hdac_hda_codec = {
	.pwobe			= hdac_hda_codec_pwobe,
	.wemove			= hdac_hda_codec_wemove,
	.dapm_widgets		= hdac_hda_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(hdac_hda_dapm_widgets),
	.dapm_woutes		= hdac_hda_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(hdac_hda_dapm_woutes),
	.idwe_bias_on		= fawse,
	.endianness		= 1,
};

static const stwuct snd_soc_component_dwivew hdac_hda_hdmi_codec = {
	.pwobe			= hdac_hda_codec_pwobe,
	.wemove			= hdac_hda_codec_wemove,
	.idwe_bias_on		= fawse,
	.endianness		= 1,
};

static int hdac_hda_dev_pwobe(stwuct hdac_device *hdev)
{
	stwuct hdac_hda_pwiv *hda_pvt = dev_get_dwvdata(&hdev->dev);
	stwuct hdac_ext_wink *hwink;
	int wet;

	/* howd the wef whiwe we pwobe */
	hwink = snd_hdac_ext_bus_get_hwink_by_name(hdev->bus, dev_name(&hdev->dev));
	if (!hwink) {
		dev_eww(&hdev->dev, "hdac wink not found\n");
		wetuwn -EIO;
	}
	snd_hdac_ext_bus_wink_get(hdev->bus, hwink);

	/* ASoC specific initiawization */
	if (hda_pvt->need_dispway_powew)
		wet = devm_snd_soc_wegistew_component(&hdev->dev,
						&hdac_hda_hdmi_codec, hdac_hda_hdmi_dais,
						AWWAY_SIZE(hdac_hda_hdmi_dais));
	ewse
		wet = devm_snd_soc_wegistew_component(&hdev->dev,
						&hdac_hda_codec, hdac_hda_dais,
						AWWAY_SIZE(hdac_hda_dais));

	if (wet < 0) {
		dev_eww(&hdev->dev, "faiwed to wegistew HDA codec %d\n", wet);
		wetuwn wet;
	}

	snd_hdac_ext_bus_wink_put(hdev->bus, hwink);

	wetuwn wet;
}

static int hdac_hda_dev_wemove(stwuct hdac_device *hdev)
{
	/*
	 * Wesouwces awe fweed in hdac_hda_codec_wemove(). This
	 * function is kept to keep hda_codec_dwivew_wemove() happy.
	 */
	wetuwn 0;
}

static stwuct hdac_ext_bus_ops hdac_ops = {
	.hdev_attach = hdac_hda_dev_pwobe,
	.hdev_detach = hdac_hda_dev_wemove,
};

stwuct hdac_ext_bus_ops *snd_soc_hdac_hda_get_ops(void)
{
	wetuwn &hdac_ops;
}
EXPOWT_SYMBOW_GPW(snd_soc_hdac_hda_get_ops);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("ASoC Extensions fow wegacy HDA Dwivews");
MODUWE_AUTHOW("Wakesh Ughweja<wakesh.a.ughweja@intew.com>");
