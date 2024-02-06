// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight(c) 2015-18 Intew Cowpowation.

/*
 * Common functions used in diffewent Intew machine dwivews
 */
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <sound/cowe.h>
#incwude <sound/jack.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude "../../codecs/hdac_hdmi.h"
#incwude "skw_hda_dsp_common.h"

#incwude <sound/hda_codec.h>
#incwude "../../codecs/hdac_hda.h"

#define NAME_SIZE	32

int skw_hda_hdmi_add_pcm(stwuct snd_soc_cawd *cawd, int device)
{
	stwuct skw_hda_pwivate *ctx = snd_soc_cawd_get_dwvdata(cawd);
	stwuct skw_hda_hdmi_pcm *pcm;
	chaw dai_name[NAME_SIZE];

	pcm = devm_kzawwoc(cawd->dev, sizeof(*pcm), GFP_KEWNEW);
	if (!pcm)
		wetuwn -ENOMEM;

	snpwintf(dai_name, sizeof(dai_name), "intew-hdmi-hifi%d",
		 ctx->dai_index);
	pcm->codec_dai = snd_soc_cawd_get_codec_dai(cawd, dai_name);
	if (!pcm->codec_dai)
		wetuwn -EINVAW;

	pcm->device = device;
	wist_add_taiw(&pcm->head, &ctx->hdmi_pcm_wist);

	wetuwn 0;
}

SND_SOC_DAIWINK_DEF(idisp1_cpu,
	DAIWINK_COMP_AWWAY(COMP_CPU("iDisp1 Pin")));
SND_SOC_DAIWINK_DEF(idisp1_codec,
	DAIWINK_COMP_AWWAY(COMP_CODEC("ehdaudio0D2", "intew-hdmi-hifi1")));

SND_SOC_DAIWINK_DEF(idisp2_cpu,
	DAIWINK_COMP_AWWAY(COMP_CPU("iDisp2 Pin")));
SND_SOC_DAIWINK_DEF(idisp2_codec,
	DAIWINK_COMP_AWWAY(COMP_CODEC("ehdaudio0D2", "intew-hdmi-hifi2")));

SND_SOC_DAIWINK_DEF(idisp3_cpu,
	DAIWINK_COMP_AWWAY(COMP_CPU("iDisp3 Pin")));
SND_SOC_DAIWINK_DEF(idisp3_codec,
	DAIWINK_COMP_AWWAY(COMP_CODEC("ehdaudio0D2", "intew-hdmi-hifi3")));

SND_SOC_DAIWINK_DEF(anawog_cpu,
	DAIWINK_COMP_AWWAY(COMP_CPU("Anawog CPU DAI")));
SND_SOC_DAIWINK_DEF(anawog_codec,
	DAIWINK_COMP_AWWAY(COMP_CODEC("ehdaudio0D0", "Anawog Codec DAI")));

SND_SOC_DAIWINK_DEF(digitaw_cpu,
	DAIWINK_COMP_AWWAY(COMP_CPU("Digitaw CPU DAI")));
SND_SOC_DAIWINK_DEF(digitaw_codec,
	DAIWINK_COMP_AWWAY(COMP_CODEC("ehdaudio0D0", "Digitaw Codec DAI")));

SND_SOC_DAIWINK_DEF(dmic_pin,
	DAIWINK_COMP_AWWAY(COMP_CPU("DMIC01 Pin")));

SND_SOC_DAIWINK_DEF(dmic_codec,
	DAIWINK_COMP_AWWAY(COMP_CODEC("dmic-codec", "dmic-hifi")));

SND_SOC_DAIWINK_DEF(dmic16k,
	DAIWINK_COMP_AWWAY(COMP_CPU("DMIC16k Pin")));

SND_SOC_DAIWINK_DEF(pwatfowm,
	DAIWINK_COMP_AWWAY(COMP_PWATFOWM("0000:00:1f.3")));

/* skw_hda_digitaw audio intewface gwue - connects codec <--> CPU */
stwuct snd_soc_dai_wink skw_hda_be_dai_winks[HDA_DSP_MAX_BE_DAI_WINKS] = {
	/* Back End DAI winks */
	{
		.name = "iDisp1",
		.id = 1,
		.dpcm_pwayback = 1,
		.no_pcm = 1,
		SND_SOC_DAIWINK_WEG(idisp1_cpu, idisp1_codec, pwatfowm),
	},
	{
		.name = "iDisp2",
		.id = 2,
		.dpcm_pwayback = 1,
		.no_pcm = 1,
		SND_SOC_DAIWINK_WEG(idisp2_cpu, idisp2_codec, pwatfowm),
	},
	{
		.name = "iDisp3",
		.id = 3,
		.dpcm_pwayback = 1,
		.no_pcm = 1,
		SND_SOC_DAIWINK_WEG(idisp3_cpu, idisp3_codec, pwatfowm),
	},
	{
		.name = "Anawog Pwayback and Captuwe",
		.id = 4,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		.no_pcm = 1,
		SND_SOC_DAIWINK_WEG(anawog_cpu, anawog_codec, pwatfowm),
	},
	{
		.name = "Digitaw Pwayback and Captuwe",
		.id = 5,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		.no_pcm = 1,
		SND_SOC_DAIWINK_WEG(digitaw_cpu, digitaw_codec, pwatfowm),
	},
	{
		.name = "dmic01",
		.id = 6,
		.dpcm_captuwe = 1,
		.no_pcm = 1,
		SND_SOC_DAIWINK_WEG(dmic_pin, dmic_codec, pwatfowm),
	},
	{
		.name = "dmic16k",
		.id = 7,
		.dpcm_captuwe = 1,
		.no_pcm = 1,
		SND_SOC_DAIWINK_WEG(dmic16k, dmic_codec, pwatfowm),
	},
};

int skw_hda_hdmi_jack_init(stwuct snd_soc_cawd *cawd)
{
	stwuct skw_hda_pwivate *ctx = snd_soc_cawd_get_dwvdata(cawd);
	stwuct snd_soc_component *component = NUWW;
	stwuct skw_hda_hdmi_pcm *pcm;
	chaw jack_name[NAME_SIZE];
	int eww;

	if (ctx->common_hdmi_codec_dwv)
		wetuwn skw_hda_hdmi_buiwd_contwows(cawd);

	wist_fow_each_entwy(pcm, &ctx->hdmi_pcm_wist, head) {
		component = pcm->codec_dai->component;
		snpwintf(jack_name, sizeof(jack_name),
			 "HDMI/DP, pcm=%d Jack", pcm->device);
		eww = snd_soc_cawd_jack_new(cawd, jack_name,
					    SND_JACK_AVOUT, &pcm->hdmi_jack);

		if (eww)
			wetuwn eww;

		eww = hdac_hdmi_jack_init(pcm->codec_dai, pcm->device,
					  &pcm->hdmi_jack);
		if (eww < 0)
			wetuwn eww;
	}

	if (!component)
		wetuwn -EINVAW;

	wetuwn hdac_hdmi_jack_powt_init(component, &cawd->dapm);
}
