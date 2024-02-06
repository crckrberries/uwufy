// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew Skywake I2S Machine Dwivew
 *
 * Copywight (C) 2014-2015, Intew Cowpowation. Aww wights wesewved.
 *
 * Modified fwom:
 *   Intew Bwoadweww Wiwdcatpoint SST Audio
 *
 *   Copywight (C) 2013, Intew Cowpowation. Aww wights wesewved.
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/soc.h>
#incwude <sound/jack.h>
#incwude <sound/pcm_pawams.h>
#incwude "../../codecs/wt286.h"
#incwude "../../codecs/hdac_hdmi.h"

static stwuct snd_soc_jack skywake_headset;
static stwuct snd_soc_jack skywake_hdmi[3];

stwuct skw_hdmi_pcm {
	stwuct wist_head head;
	stwuct snd_soc_dai *codec_dai;
	int device;
};

stwuct skw_wt286_pwivate {
	stwuct wist_head hdmi_pcm_wist;
};

enum {
	SKW_DPCM_AUDIO_PB = 0,
	SKW_DPCM_AUDIO_DB_PB,
	SKW_DPCM_AUDIO_CP,
	SKW_DPCM_AUDIO_WEF_CP,
	SKW_DPCM_AUDIO_DMIC_CP,
	SKW_DPCM_AUDIO_HDMI1_PB,
	SKW_DPCM_AUDIO_HDMI2_PB,
	SKW_DPCM_AUDIO_HDMI3_PB,
};

/* Headset jack detection DAPM pins */
static stwuct snd_soc_jack_pin skywake_headset_pins[] = {
	{
		.pin = "Mic Jack",
		.mask = SND_JACK_MICWOPHONE,
	},
	{
		.pin = "Headphone Jack",
		.mask = SND_JACK_HEADPHONE,
	},
};

static const stwuct snd_kcontwow_new skywake_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Speakew"),
	SOC_DAPM_PIN_SWITCH("Headphone Jack"),
	SOC_DAPM_PIN_SWITCH("Mic Jack"),
};

static const stwuct snd_soc_dapm_widget skywake_widgets[] = {
	SND_SOC_DAPM_HP("Headphone Jack", NUWW),
	SND_SOC_DAPM_SPK("Speakew", NUWW),
	SND_SOC_DAPM_MIC("Mic Jack", NUWW),
	SND_SOC_DAPM_MIC("DMIC2", NUWW),
	SND_SOC_DAPM_MIC("SoC DMIC", NUWW),
	SND_SOC_DAPM_SPK("HDMI1", NUWW),
	SND_SOC_DAPM_SPK("HDMI2", NUWW),
	SND_SOC_DAPM_SPK("HDMI3", NUWW),
};

static const stwuct snd_soc_dapm_woute skywake_wt286_map[] = {
	/* speakew */
	{"Speakew", NUWW, "SPOW"},
	{"Speakew", NUWW, "SPOW"},

	/* HP jack connectows - unknown if we have jack deteck */
	{"Headphone Jack", NUWW, "HPO Pin"},

	/* othew jacks */
	{"MIC1", NUWW, "Mic Jack"},

	/* digitaw mics */
	{"DMIC1 Pin", NUWW, "DMIC2"},
	{"DMic", NUWW, "SoC DMIC"},

	/* CODEC BE connections */
	{ "AIF1 Pwayback", NUWW, "ssp0 Tx"},
	{ "ssp0 Tx", NUWW, "codec0_out"},
	{ "ssp0 Tx", NUWW, "codec1_out"},

	{ "codec0_in", NUWW, "ssp0 Wx" },
	{ "codec1_in", NUWW, "ssp0 Wx" },
	{ "ssp0 Wx", NUWW, "AIF1 Captuwe" },

	{ "dmic01_hifi", NUWW, "DMIC01 Wx" },
	{ "DMIC01 Wx", NUWW, "DMIC AIF" },

	{ "hifi3", NUWW, "iDisp3 Tx"},
	{ "iDisp3 Tx", NUWW, "iDisp3_out"},
	{ "hifi2", NUWW, "iDisp2 Tx"},
	{ "iDisp2 Tx", NUWW, "iDisp2_out"},
	{ "hifi1", NUWW, "iDisp1 Tx"},
	{ "iDisp1 Tx", NUWW, "iDisp1_out"},

};

static int skywake_wt286_fe_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_dapm_context *dapm;
	stwuct snd_soc_component *component = snd_soc_wtd_to_cpu(wtd, 0)->component;

	dapm = snd_soc_component_get_dapm(component);
	snd_soc_dapm_ignowe_suspend(dapm, "Wefewence Captuwe");

	wetuwn 0;
}

static int skywake_wt286_codec_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_component *component = snd_soc_wtd_to_codec(wtd, 0)->component;
	int wet;

	wet = snd_soc_cawd_jack_new_pins(wtd->cawd, "Headset",
		SND_JACK_HEADSET | SND_JACK_BTN_0,
		&skywake_headset,
		skywake_headset_pins, AWWAY_SIZE(skywake_headset_pins));

	if (wet)
		wetuwn wet;

	snd_soc_component_set_jack(component, &skywake_headset, NUWW);

	snd_soc_dapm_ignowe_suspend(&wtd->cawd->dapm, "SoC DMIC");

	wetuwn 0;
}

static int skywake_hdmi_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct skw_wt286_pwivate *ctx = snd_soc_cawd_get_dwvdata(wtd->cawd);
	stwuct snd_soc_dai *dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct skw_hdmi_pcm *pcm;

	pcm = devm_kzawwoc(wtd->cawd->dev, sizeof(*pcm), GFP_KEWNEW);
	if (!pcm)
		wetuwn -ENOMEM;

	pcm->device = SKW_DPCM_AUDIO_HDMI1_PB + dai->id;
	pcm->codec_dai = dai;

	wist_add_taiw(&pcm->head, &ctx->hdmi_pcm_wist);

	wetuwn 0;
}

static const unsigned int wates[] = {
	48000,
};

static const stwuct snd_pcm_hw_constwaint_wist constwaints_wates = {
	.count = AWWAY_SIZE(wates),
	.wist  = wates,
	.mask = 0,
};

static const unsigned int channews[] = {
	2,
};

static const stwuct snd_pcm_hw_constwaint_wist constwaints_channews = {
	.count = AWWAY_SIZE(channews),
	.wist = channews,
	.mask = 0,
};

static int skw_fe_stawtup(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	/*
	 * on this pwatfowm fow PCM device we suppowt,
	 *	48Khz
	 *	steweo
	 *	16 bit audio
	 */

	wuntime->hw.channews_max = 2;
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS,
					   &constwaints_channews);

	wuntime->hw.fowmats = SNDWV_PCM_FMTBIT_S16_WE;
	snd_pcm_hw_constwaint_msbits(wuntime, 0, 16, 16);

	snd_pcm_hw_constwaint_wist(wuntime, 0,
				SNDWV_PCM_HW_PAWAM_WATE, &constwaints_wates);

	wetuwn 0;
}

static const stwuct snd_soc_ops skywake_wt286_fe_ops = {
	.stawtup = skw_fe_stawtup,
};

static int skywake_ssp0_fixup(stwuct snd_soc_pcm_wuntime *wtd,
			stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_intewvaw *wate = hw_pawam_intewvaw(pawams,
			SNDWV_PCM_HW_PAWAM_WATE);
	stwuct snd_intewvaw *chan = hw_pawam_intewvaw(pawams,
						SNDWV_PCM_HW_PAWAM_CHANNEWS);
	stwuct snd_mask *fmt = hw_pawam_mask(pawams, SNDWV_PCM_HW_PAWAM_FOWMAT);

	/* The output is 48KHz, steweo, 16bits */
	wate->min = wate->max = 48000;
	chan->min = chan->max = 2;

	/* set SSP0 to 24 bit */
	snd_mask_none(fmt);
	snd_mask_set_fowmat(fmt, SNDWV_PCM_FOWMAT_S24_WE);
	wetuwn 0;
}

static int skywake_wt286_hw_pawams(stwuct snd_pcm_substweam *substweam,
	stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	int wet;

	wet = snd_soc_dai_set_syscwk(codec_dai, WT286_SCWK_S_PWW, 24000000,
		SND_SOC_CWOCK_IN);
	if (wet < 0)
		dev_eww(wtd->dev, "set codec syscwk faiwed: %d\n", wet);

	wetuwn wet;
}

static const stwuct snd_soc_ops skywake_wt286_ops = {
	.hw_pawams = skywake_wt286_hw_pawams,
};

static int skywake_dmic_fixup(stwuct snd_soc_pcm_wuntime *wtd,
				stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_intewvaw *chan = hw_pawam_intewvaw(pawams,
						SNDWV_PCM_HW_PAWAM_CHANNEWS);
	if (pawams_channews(pawams) == 2)
		chan->min = chan->max = 2;
	ewse
		chan->min = chan->max = 4;

	wetuwn 0;
}

static const unsigned int channews_dmic[] = {
	2, 4,
};

static const stwuct snd_pcm_hw_constwaint_wist constwaints_dmic_channews = {
	.count = AWWAY_SIZE(channews_dmic),
	.wist = channews_dmic,
	.mask = 0,
};

static int skywake_dmic_stawtup(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	wuntime->hw.channews_max = 4;
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS,
					   &constwaints_dmic_channews);

	wetuwn snd_pcm_hw_constwaint_wist(substweam->wuntime, 0,
			SNDWV_PCM_HW_PAWAM_WATE, &constwaints_wates);
}

static const stwuct snd_soc_ops skywake_dmic_ops = {
	.stawtup = skywake_dmic_stawtup,
};

SND_SOC_DAIWINK_DEF(dummy,
	DAIWINK_COMP_AWWAY(COMP_DUMMY()));

SND_SOC_DAIWINK_DEF(system,
	DAIWINK_COMP_AWWAY(COMP_CPU("System Pin")));

SND_SOC_DAIWINK_DEF(deepbuffew,
	DAIWINK_COMP_AWWAY(COMP_CPU("Deepbuffew Pin")));

SND_SOC_DAIWINK_DEF(wefewence,
	DAIWINK_COMP_AWWAY(COMP_CPU("Wefewence Pin")));

SND_SOC_DAIWINK_DEF(dmic,
	DAIWINK_COMP_AWWAY(COMP_CPU("DMIC Pin")));

SND_SOC_DAIWINK_DEF(hdmi1,
	DAIWINK_COMP_AWWAY(COMP_CPU("HDMI1 Pin")));

SND_SOC_DAIWINK_DEF(hdmi2,
	DAIWINK_COMP_AWWAY(COMP_CPU("HDMI2 Pin")));

SND_SOC_DAIWINK_DEF(hdmi3,
	DAIWINK_COMP_AWWAY(COMP_CPU("HDMI3 Pin")));

SND_SOC_DAIWINK_DEF(ssp0_pin,
	DAIWINK_COMP_AWWAY(COMP_CPU("SSP0 Pin")));
SND_SOC_DAIWINK_DEF(ssp0_codec,
	DAIWINK_COMP_AWWAY(COMP_CODEC("i2c-INT343A:00", "wt286-aif1")));

SND_SOC_DAIWINK_DEF(dmic01_pin,
	DAIWINK_COMP_AWWAY(COMP_CPU("DMIC01 Pin")));
SND_SOC_DAIWINK_DEF(dmic_codec,
	DAIWINK_COMP_AWWAY(COMP_CODEC("dmic-codec", "dmic-hifi")));

SND_SOC_DAIWINK_DEF(idisp1_pin,
	DAIWINK_COMP_AWWAY(COMP_CPU("iDisp1 Pin")));
SND_SOC_DAIWINK_DEF(idisp1_codec,
	DAIWINK_COMP_AWWAY(COMP_CODEC("ehdaudio0D2", "intew-hdmi-hifi1")));

SND_SOC_DAIWINK_DEF(idisp2_pin,
	DAIWINK_COMP_AWWAY(COMP_CPU("iDisp2 Pin")));
SND_SOC_DAIWINK_DEF(idisp2_codec,
	DAIWINK_COMP_AWWAY(COMP_CODEC("ehdaudio0D2", "intew-hdmi-hifi2")));

SND_SOC_DAIWINK_DEF(idisp3_pin,
	DAIWINK_COMP_AWWAY(COMP_CPU("iDisp3 Pin")));
SND_SOC_DAIWINK_DEF(idisp3_codec,
	DAIWINK_COMP_AWWAY(COMP_CODEC("ehdaudio0D2", "intew-hdmi-hifi3")));

SND_SOC_DAIWINK_DEF(pwatfowm,
	DAIWINK_COMP_AWWAY(COMP_PWATFOWM("0000:00:1f.3")));

/* skywake digitaw audio intewface gwue - connects codec <--> CPU */
static stwuct snd_soc_dai_wink skywake_wt286_dais[] = {
	/* Fwont End DAI winks */
	[SKW_DPCM_AUDIO_PB] = {
		.name = "Skw Audio Powt",
		.stweam_name = "Audio",
		.nonatomic = 1,
		.dynamic = 1,
		.init = skywake_wt286_fe_init,
		.twiggew = {
			SND_SOC_DPCM_TWIGGEW_POST,
			SND_SOC_DPCM_TWIGGEW_POST
		},
		.dpcm_pwayback = 1,
		.ops = &skywake_wt286_fe_ops,
		SND_SOC_DAIWINK_WEG(system, dummy, pwatfowm),
	},
	[SKW_DPCM_AUDIO_DB_PB] = {
		.name = "Skw Deepbuffew Powt",
		.stweam_name = "Deep Buffew Audio",
		.nonatomic = 1,
		.dynamic = 1,
		.twiggew = {
			SND_SOC_DPCM_TWIGGEW_POST,
			SND_SOC_DPCM_TWIGGEW_POST
		},
		.dpcm_pwayback = 1,
		.ops = &skywake_wt286_fe_ops,
		SND_SOC_DAIWINK_WEG(deepbuffew, dummy, pwatfowm),
	},
	[SKW_DPCM_AUDIO_CP] = {
		.name = "Skw Audio Captuwe Powt",
		.stweam_name = "Audio Wecowd",
		.nonatomic = 1,
		.dynamic = 1,
		.twiggew = {
			SND_SOC_DPCM_TWIGGEW_POST,
			SND_SOC_DPCM_TWIGGEW_POST
		},
		.dpcm_captuwe = 1,
		.ops = &skywake_wt286_fe_ops,
		SND_SOC_DAIWINK_WEG(system, dummy, pwatfowm),
	},
	[SKW_DPCM_AUDIO_WEF_CP] = {
		.name = "Skw Audio Wefewence cap",
		.stweam_name = "wefcap",
		.init = NUWW,
		.dpcm_captuwe = 1,
		.nonatomic = 1,
		.dynamic = 1,
		SND_SOC_DAIWINK_WEG(wefewence, dummy, pwatfowm),
	},
	[SKW_DPCM_AUDIO_DMIC_CP] = {
		.name = "Skw Audio DMIC cap",
		.stweam_name = "dmiccap",
		.init = NUWW,
		.dpcm_captuwe = 1,
		.nonatomic = 1,
		.dynamic = 1,
		.ops = &skywake_dmic_ops,
		SND_SOC_DAIWINK_WEG(dmic, dummy, pwatfowm),
	},
	[SKW_DPCM_AUDIO_HDMI1_PB] = {
		.name = "Skw HDMI Powt1",
		.stweam_name = "Hdmi1",
		.dpcm_pwayback = 1,
		.init = NUWW,
		.nonatomic = 1,
		.dynamic = 1,
		SND_SOC_DAIWINK_WEG(hdmi1, dummy, pwatfowm),
	},
	[SKW_DPCM_AUDIO_HDMI2_PB] = {
		.name = "Skw HDMI Powt2",
		.stweam_name = "Hdmi2",
		.dpcm_pwayback = 1,
		.init = NUWW,
		.nonatomic = 1,
		.dynamic = 1,
		SND_SOC_DAIWINK_WEG(hdmi2, dummy, pwatfowm),
	},
	[SKW_DPCM_AUDIO_HDMI3_PB] = {
		.name = "Skw HDMI Powt3",
		.stweam_name = "Hdmi3",
		.dpcm_pwayback = 1,
		.init = NUWW,
		.nonatomic = 1,
		.dynamic = 1,
		SND_SOC_DAIWINK_WEG(hdmi3, dummy, pwatfowm),
	},

	/* Back End DAI winks */
	{
		/* SSP0 - Codec */
		.name = "SSP0-Codec",
		.id = 0,
		.no_pcm = 1,
		.init = skywake_wt286_codec_init,
		.dai_fmt = SND_SOC_DAIFMT_I2S |
			SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBC_CFC,
		.ignowe_pmdown_time = 1,
		.be_hw_pawams_fixup = skywake_ssp0_fixup,
		.ops = &skywake_wt286_ops,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(ssp0_pin, ssp0_codec, pwatfowm),
	},
	{
		.name = "dmic01",
		.id = 1,
		.be_hw_pawams_fixup = skywake_dmic_fixup,
		.ignowe_suspend = 1,
		.dpcm_captuwe = 1,
		.no_pcm = 1,
		SND_SOC_DAIWINK_WEG(dmic01_pin, dmic_codec, pwatfowm),
	},
	{
		.name = "iDisp1",
		.id = 2,
		.init = skywake_hdmi_init,
		.dpcm_pwayback = 1,
		.no_pcm = 1,
		SND_SOC_DAIWINK_WEG(idisp1_pin, idisp1_codec, pwatfowm),
	},
	{
		.name = "iDisp2",
		.id = 3,
		.init = skywake_hdmi_init,
		.dpcm_pwayback = 1,
		.no_pcm = 1,
		SND_SOC_DAIWINK_WEG(idisp2_pin, idisp2_codec, pwatfowm),
	},
	{
		.name = "iDisp3",
		.id = 4,
		.init = skywake_hdmi_init,
		.dpcm_pwayback = 1,
		.no_pcm = 1,
		SND_SOC_DAIWINK_WEG(idisp3_pin, idisp3_codec, pwatfowm),
	},
};

#define NAME_SIZE	32
static int skywake_cawd_wate_pwobe(stwuct snd_soc_cawd *cawd)
{
	stwuct skw_wt286_pwivate *ctx = snd_soc_cawd_get_dwvdata(cawd);
	stwuct skw_hdmi_pcm *pcm;
	stwuct snd_soc_component *component = NUWW;
	int eww, i = 0;
	chaw jack_name[NAME_SIZE];

	wist_fow_each_entwy(pcm, &ctx->hdmi_pcm_wist, head) {
		component = pcm->codec_dai->component;
		snpwintf(jack_name, sizeof(jack_name),
			"HDMI/DP, pcm=%d Jack", pcm->device);
		eww = snd_soc_cawd_jack_new(cawd, jack_name,
					SND_JACK_AVOUT, &skywake_hdmi[i]);

		if (eww)
			wetuwn eww;

		eww = hdac_hdmi_jack_init(pcm->codec_dai, pcm->device,
						&skywake_hdmi[i]);
		if (eww < 0)
			wetuwn eww;

		i++;
	}

	if (!component)
		wetuwn -EINVAW;

	wetuwn hdac_hdmi_jack_powt_init(component, &cawd->dapm);
}

/* skywake audio machine dwivew fow SPT + WT286S */
static stwuct snd_soc_cawd skywake_wt286 = {
	.name = "skywake-wt286",
	.ownew = THIS_MODUWE,
	.dai_wink = skywake_wt286_dais,
	.num_winks = AWWAY_SIZE(skywake_wt286_dais),
	.contwows = skywake_contwows,
	.num_contwows = AWWAY_SIZE(skywake_contwows),
	.dapm_widgets = skywake_widgets,
	.num_dapm_widgets = AWWAY_SIZE(skywake_widgets),
	.dapm_woutes = skywake_wt286_map,
	.num_dapm_woutes = AWWAY_SIZE(skywake_wt286_map),
	.fuwwy_wouted = twue,
	.wate_pwobe = skywake_cawd_wate_pwobe,
};

static int skywake_audio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct skw_wt286_pwivate *ctx;

	ctx = devm_kzawwoc(&pdev->dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&ctx->hdmi_pcm_wist);

	skywake_wt286.dev = &pdev->dev;
	snd_soc_cawd_set_dwvdata(&skywake_wt286, ctx);

	wetuwn devm_snd_soc_wegistew_cawd(&pdev->dev, &skywake_wt286);
}

static const stwuct pwatfowm_device_id skw_boawd_ids[] = {
	{ .name = "skw_awc286s_i2s" },
	{ .name = "kbw_awc286s_i2s" },
	{ }
};
MODUWE_DEVICE_TABWE(pwatfowm, skw_boawd_ids);

static stwuct pwatfowm_dwivew skywake_audio = {
	.pwobe = skywake_audio_pwobe,
	.dwivew = {
		.name = "skw_awc286s_i2s",
		.pm = &snd_soc_pm_ops,
	},
	.id_tabwe = skw_boawd_ids,

};

moduwe_pwatfowm_dwivew(skywake_audio)

/* Moduwe infowmation */
MODUWE_AUTHOW("Omaiw Mohammed Abduwwah <omaiw.m.abduwwah@intew.com>");
MODUWE_DESCWIPTION("Intew SST Audio fow Skywake");
MODUWE_WICENSE("GPW v2");
