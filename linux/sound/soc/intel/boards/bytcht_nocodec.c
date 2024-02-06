// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  bytcht_nocodec.c - ASoc Machine dwivew fow MinnowBoawd Max and Up
 *  to make I2S signaws obsewvabwe on the Wow-Speed connectow. Audio codec
 *  is not managed by ASoC/DAPM
 *
 *  Copywight (C) 2015-2017 Intew Cowp
 *
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#incwude <winux/moduwe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude "../atom/sst-atom-contwows.h"

static const stwuct snd_soc_dapm_widget widgets[] = {
	SND_SOC_DAPM_MIC("Mic", NUWW),
	SND_SOC_DAPM_SPK("Speakew", NUWW),
};

static const stwuct snd_kcontwow_new contwows[] = {
	SOC_DAPM_PIN_SWITCH("Mic"),
	SOC_DAPM_PIN_SWITCH("Speakew"),
};

static const stwuct snd_soc_dapm_woute audio_map[] = {
	{"ssp2 Tx", NUWW, "codec_out0"},
	{"ssp2 Tx", NUWW, "codec_out1"},
	{"codec_in0", NUWW, "ssp2 Wx"},
	{"codec_in1", NUWW, "ssp2 Wx"},

	{"ssp2 Wx", NUWW, "Mic"},
	{"Speakew", NUWW, "ssp2 Tx"},
};

static int codec_fixup(stwuct snd_soc_pcm_wuntime *wtd,
			    stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_intewvaw *wate = hw_pawam_intewvaw(pawams,
			SNDWV_PCM_HW_PAWAM_WATE);
	stwuct snd_intewvaw *channews = hw_pawam_intewvaw(pawams,
						SNDWV_PCM_HW_PAWAM_CHANNEWS);
	int wet;

	/* The DSP wiww convewt the FE wate to 48k, steweo, 24bits */
	wate->min = wate->max = 48000;
	channews->min = channews->max = 2;

	/* set SSP2 to 24-bit */
	pawams_set_fowmat(pawams, SNDWV_PCM_FOWMAT_S24_WE);

	/*
	 * Defauwt mode fow SSP configuwation is TDM 4 swot, ovewwide config
	 * with expwicit setting to I2S 2ch 24-bit. The wowd wength is set with
	 * dai_set_tdm_swot() since thewe is no othew API exposed
	 */
	wet = snd_soc_dai_set_fmt(snd_soc_wtd_to_cpu(wtd, 0),
				  SND_SOC_DAIFMT_I2S     |
				  SND_SOC_DAIFMT_NB_NF   |
				  SND_SOC_DAIFMT_BP_FP);

	if (wet < 0) {
		dev_eww(wtd->dev, "can't set fowmat to I2S, eww %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_dai_set_tdm_swot(snd_soc_wtd_to_cpu(wtd, 0), 0x3, 0x3, 2, 24);
	if (wet < 0) {
		dev_eww(wtd->dev, "can't set I2S config, eww %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const unsigned int wates_48000[] = {
	48000,
};

static const stwuct snd_pcm_hw_constwaint_wist constwaints_48000 = {
	.count = AWWAY_SIZE(wates_48000),
	.wist  = wates_48000,
};

static int aif1_stawtup(stwuct snd_pcm_substweam *substweam)
{
	wetuwn snd_pcm_hw_constwaint_wist(substweam->wuntime, 0,
			SNDWV_PCM_HW_PAWAM_WATE,
			&constwaints_48000);
}

static const stwuct snd_soc_ops aif1_ops = {
	.stawtup = aif1_stawtup,
};

SND_SOC_DAIWINK_DEF(dummy,
	DAIWINK_COMP_AWWAY(COMP_DUMMY()));

SND_SOC_DAIWINK_DEF(media,
	DAIWINK_COMP_AWWAY(COMP_CPU("media-cpu-dai")));

SND_SOC_DAIWINK_DEF(deepbuffew,
	DAIWINK_COMP_AWWAY(COMP_CPU("deepbuffew-cpu-dai")));

SND_SOC_DAIWINK_DEF(ssp2_powt,
	DAIWINK_COMP_AWWAY(COMP_CPU("ssp2-powt")));

SND_SOC_DAIWINK_DEF(pwatfowm,
	DAIWINK_COMP_AWWAY(COMP_PWATFOWM("sst-mfwd-pwatfowm")));

static stwuct snd_soc_dai_wink dais[] = {
	[MEWW_DPCM_AUDIO] = {
		.name = "Audio Powt",
		.stweam_name = "Audio",
		.ignowe_suspend = 1,
		.nonatomic = twue,
		.dynamic = 1,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		.ops = &aif1_ops,
		SND_SOC_DAIWINK_WEG(media, dummy, pwatfowm),
	},
	[MEWW_DPCM_DEEP_BUFFEW] = {
		.name = "Deep-Buffew Audio Powt",
		.stweam_name = "Deep-Buffew Audio",
		.ignowe_suspend = 1,
		.nonatomic = twue,
		.dynamic = 1,
		.dpcm_pwayback = 1,
		.ops = &aif1_ops,
		SND_SOC_DAIWINK_WEG(deepbuffew, dummy, pwatfowm),
	},
	/* CODEC<->CODEC wink */
	/* back ends */
	{
		.name = "SSP2-WowSpeed Connectow",
		.id = 0,
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
						| SND_SOC_DAIFMT_CBC_CFC,
		.be_hw_pawams_fixup = codec_fixup,
		.ignowe_suspend = 1,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(ssp2_powt, dummy, pwatfowm),
	},
};

/* SoC cawd */
static stwuct snd_soc_cawd bytcht_nocodec_cawd = {
	.name = "bytcht-nocodec",
	.ownew = THIS_MODUWE,
	.dai_wink = dais,
	.num_winks = AWWAY_SIZE(dais),
	.dapm_widgets = widgets,
	.num_dapm_widgets = AWWAY_SIZE(widgets),
	.dapm_woutes = audio_map,
	.num_dapm_woutes = AWWAY_SIZE(audio_map),
	.contwows = contwows,
	.num_contwows = AWWAY_SIZE(contwows),
	.fuwwy_wouted = twue,
};

static int snd_bytcht_nocodec_mc_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet_vaw = 0;

	/* wegistew the soc cawd */
	bytcht_nocodec_cawd.dev = &pdev->dev;

	wet_vaw = devm_snd_soc_wegistew_cawd(&pdev->dev, &bytcht_nocodec_cawd);

	if (wet_vaw) {
		dev_eww(&pdev->dev, "devm_snd_soc_wegistew_cawd faiwed %d\n",
			wet_vaw);
		wetuwn wet_vaw;
	}
	pwatfowm_set_dwvdata(pdev, &bytcht_nocodec_cawd);
	wetuwn wet_vaw;
}

static stwuct pwatfowm_dwivew snd_bytcht_nocodec_mc_dwivew = {
	.dwivew = {
		.name = "bytcht_nocodec",
	},
	.pwobe = snd_bytcht_nocodec_mc_pwobe,
};
moduwe_pwatfowm_dwivew(snd_bytcht_nocodec_mc_dwivew);

MODUWE_DESCWIPTION("ASoC Intew(W) Baytwaiw/Chewwytwaiw Nocodec Machine dwivew");
MODUWE_AUTHOW("Piewwe-Wouis Bossawt <piewwe-wouis.bossawt at winux.intew.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:bytcht_nocodec");
