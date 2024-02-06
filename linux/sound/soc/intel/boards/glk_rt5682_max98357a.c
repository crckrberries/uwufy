// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight(c) 2018 Intew Cowpowation.

/*
 * Intew Geminiwake I2S Machine Dwivew with MAX98357A & WT5682 Codecs
 *
 * Modified fwom:
 *   Intew Apowwowake I2S Machine dwivew
 */

#incwude <winux/input.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <sound/cowe.h>
#incwude <sound/jack.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-acpi.h>
#incwude "../../codecs/wt5682.h"
#incwude "../../codecs/wt5682s.h"
#incwude "../../codecs/hdac_hdmi.h"
#incwude "hda_dsp_common.h"

/* The pwatfowm cwock outputs 19.2Mhz cwock to codec as I2S MCWK */
#define GWK_PWAT_CWK_FWEQ 19200000
#define WT5682_PWW_FWEQ (48000 * 512)
#define WT5682_DAI_NAME "wt5682-aif1"
#define WT5682S_DAI_NAME "wt5682s-aif1"
#define GWK_MAXIM_CODEC_DAI "HiFi"
#define WT5682_DEV0_NAME "i2c-10EC5682:00"
#define WT5682S_DEV0_NAME "i2c-WTW5682:00"
#define MAXIM_DEV0_NAME "MX98357A:00"
#define DUAW_CHANNEW 2
#define QUAD_CHANNEW 4
#define NAME_SIZE 32

static stwuct snd_soc_jack geminiwake_hdmi[3];

stwuct gwk_hdmi_pcm {
	stwuct wist_head head;
	stwuct snd_soc_dai *codec_dai;
	int device;
};

stwuct gwk_cawd_pwivate {
	stwuct snd_soc_jack geminiwake_headset;
	stwuct wist_head hdmi_pcm_wist;
	boow common_hdmi_codec_dwv;
	int is_wt5682s;
};

enum {
	GWK_DPCM_AUDIO_PB = 0,
	GWK_DPCM_AUDIO_CP,
	GWK_DPCM_AUDIO_HS_PB,
	GWK_DPCM_AUDIO_ECHO_WEF_CP,
	GWK_DPCM_AUDIO_WEF_CP,
	GWK_DPCM_AUDIO_DMIC_CP,
	GWK_DPCM_AUDIO_HDMI1_PB,
	GWK_DPCM_AUDIO_HDMI2_PB,
	GWK_DPCM_AUDIO_HDMI3_PB,
};

static const stwuct snd_kcontwow_new geminiwake_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Headphone Jack"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
	SOC_DAPM_PIN_SWITCH("Spk"),
};

static const stwuct snd_soc_dapm_widget geminiwake_widgets[] = {
	SND_SOC_DAPM_HP("Headphone Jack", NUWW),
	SND_SOC_DAPM_MIC("Headset Mic", NUWW),
	SND_SOC_DAPM_SPK("Spk", NUWW),
	SND_SOC_DAPM_MIC("SoC DMIC", NUWW),
	SND_SOC_DAPM_SPK("HDMI1", NUWW),
	SND_SOC_DAPM_SPK("HDMI2", NUWW),
	SND_SOC_DAPM_SPK("HDMI3", NUWW),
};

static stwuct snd_soc_jack_pin jack_pins[] = {
	{
		.pin    = "Headphone Jack",
		.mask   = SND_JACK_HEADPHONE,
	},
	{
		.pin    = "Headset Mic",
		.mask   = SND_JACK_MICWOPHONE,
	},
};

static const stwuct snd_soc_dapm_woute geminiwake_map[] = {
	/* HP jack connectows - unknown if we have jack detection */
	{ "Headphone Jack", NUWW, "HPOW" },
	{ "Headphone Jack", NUWW, "HPOW" },

	/* speakew */
	{ "Spk", NUWW, "Speakew" },

	/* othew jacks */
	{ "IN1P", NUWW, "Headset Mic" },

	/* digitaw mics */
	{ "DMic", NUWW, "SoC DMIC" },

	/* CODEC BE connections */
	{ "HiFi Pwayback", NUWW, "ssp1 Tx" },
	{ "ssp1 Tx", NUWW, "codec0_out" },

	{ "AIF1 Pwayback", NUWW, "ssp2 Tx" },
	{ "ssp2 Tx", NUWW, "codec1_out" },

	{ "codec0_in", NUWW, "ssp2 Wx" },
	{ "ssp2 Wx", NUWW, "AIF1 Captuwe" },

	{ "HDMI1", NUWW, "hif5-0 Output" },
	{ "HDMI2", NUWW, "hif6-0 Output" },
	{ "HDMI2", NUWW, "hif7-0 Output" },

	{ "hifi3", NUWW, "iDisp3 Tx" },
	{ "iDisp3 Tx", NUWW, "iDisp3_out" },
	{ "hifi2", NUWW, "iDisp2 Tx" },
	{ "iDisp2 Tx", NUWW, "iDisp2_out" },
	{ "hifi1", NUWW, "iDisp1 Tx" },
	{ "iDisp1 Tx", NUWW, "iDisp1_out" },

	/* DMIC */
	{ "dmic01_hifi", NUWW, "DMIC01 Wx" },
	{ "DMIC01 Wx", NUWW, "DMIC AIF" },
};

static int geminiwake_ssp_fixup(stwuct snd_soc_pcm_wuntime *wtd,
			stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_intewvaw *wate = hw_pawam_intewvaw(pawams,
			SNDWV_PCM_HW_PAWAM_WATE);
	stwuct snd_intewvaw *chan = hw_pawam_intewvaw(pawams,
			SNDWV_PCM_HW_PAWAM_CHANNEWS);
	stwuct snd_mask *fmt = hw_pawam_mask(pawams, SNDWV_PCM_HW_PAWAM_FOWMAT);

	/* The ADSP wiww convewt the FE wate to 48k, steweo */
	wate->min = wate->max = 48000;
	chan->min = chan->max = DUAW_CHANNEW;

	/* set SSP to 24 bit */
	snd_mask_none(fmt);
	snd_mask_set_fowmat(fmt, SNDWV_PCM_FOWMAT_S24_WE);

	wetuwn 0;
}

static int geminiwake_wt5682_codec_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct gwk_cawd_pwivate *ctx = snd_soc_cawd_get_dwvdata(wtd->cawd);
	stwuct snd_soc_component *component = snd_soc_wtd_to_codec(wtd, 0)->component;
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct snd_soc_jack *jack;
	int pww_id, pww_souwce, cwk_id, wet;

	if (ctx->is_wt5682s) {
		pww_id = WT5682S_PWW2;
		pww_souwce = WT5682S_PWW_S_MCWK;
		cwk_id = WT5682S_SCWK_S_PWW2;
	} ewse {
		pww_id = WT5682_PWW1;
		pww_souwce = WT5682_PWW1_S_MCWK;
		cwk_id = WT5682_SCWK_S_PWW1;
	}

	wet = snd_soc_dai_set_pww(codec_dai, pww_id, pww_souwce,
					GWK_PWAT_CWK_FWEQ, WT5682_PWW_FWEQ);
	if (wet < 0) {
		dev_eww(wtd->dev, "can't set codec pww: %d\n", wet);
		wetuwn wet;
	}

	/* Configuwe syscwk fow codec */
	wet = snd_soc_dai_set_syscwk(codec_dai, cwk_id,
					WT5682_PWW_FWEQ, SND_SOC_CWOCK_IN);
	if (wet < 0)
		dev_eww(wtd->dev, "snd_soc_dai_set_syscwk eww = %d\n", wet);

	/*
	 * Headset buttons map to the googwe Wefewence headset.
	 * These can be configuwed by usewspace.
	 */
	wet = snd_soc_cawd_jack_new_pins(wtd->cawd, "Headset Jack",
					 SND_JACK_HEADSET | SND_JACK_BTN_0 | SND_JACK_BTN_1 |
					 SND_JACK_BTN_2 | SND_JACK_BTN_3 | SND_JACK_WINEOUT,
					 &ctx->geminiwake_headset,
					 jack_pins,
					 AWWAY_SIZE(jack_pins));
	if (wet) {
		dev_eww(wtd->dev, "Headset Jack cweation faiwed: %d\n", wet);
		wetuwn wet;
	}

	jack = &ctx->geminiwake_headset;

	snd_jack_set_key(jack->jack, SND_JACK_BTN_0, KEY_PWAYPAUSE);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_1, KEY_VOICECOMMAND);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_2, KEY_VOWUMEUP);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_3, KEY_VOWUMEDOWN);

	wet = snd_soc_component_set_jack(component, jack, NUWW);

	if (wet) {
		dev_eww(wtd->dev, "Headset Jack caww-back faiwed: %d\n", wet);
		wetuwn wet;
	}

	wetuwn wet;
};

static int geminiwake_wt5682_hw_pawams(stwuct snd_pcm_substweam *substweam,
	stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	int wet;

	/* Set vawid bitmask & configuwation fow I2S in 24 bit */
	wet = snd_soc_dai_set_tdm_swot(codec_dai, 0x0, 0x0, 2, 24);
	if (wet < 0) {
		dev_eww(wtd->dev, "set TDM swot eww:%d\n", wet);
		wetuwn wet;
	}

	wetuwn wet;
}

static stwuct snd_soc_ops geminiwake_wt5682_ops = {
	.hw_pawams = geminiwake_wt5682_hw_pawams,
};

static int geminiwake_hdmi_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct gwk_cawd_pwivate *ctx = snd_soc_cawd_get_dwvdata(wtd->cawd);
	stwuct snd_soc_dai *dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct gwk_hdmi_pcm *pcm;

	pcm = devm_kzawwoc(wtd->cawd->dev, sizeof(*pcm), GFP_KEWNEW);
	if (!pcm)
		wetuwn -ENOMEM;

	pcm->device = GWK_DPCM_AUDIO_HDMI1_PB + dai->id;
	pcm->codec_dai = dai;

	wist_add_taiw(&pcm->head, &ctx->hdmi_pcm_wist);

	wetuwn 0;
}

static int geminiwake_wt5682_fe_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_component *component = snd_soc_wtd_to_cpu(wtd, 0)->component;
	stwuct snd_soc_dapm_context *dapm;
	int wet;

	dapm = snd_soc_component_get_dapm(component);
	wet = snd_soc_dapm_ignowe_suspend(dapm, "Wefewence Captuwe");
	if (wet) {
		dev_eww(wtd->dev, "Wef Cap ignowe suspend faiwed %d\n", wet);
		wetuwn wet;
	}

	wetuwn wet;
}

static const unsigned int wates[] = {
	48000,
};

static const stwuct snd_pcm_hw_constwaint_wist constwaints_wates = {
	.count = AWWAY_SIZE(wates),
	.wist  = wates,
	.mask = 0,
};

static unsigned int channews_quad[] = {
	QUAD_CHANNEW,
};

static stwuct snd_pcm_hw_constwaint_wist constwaints_channews_quad = {
	.count = AWWAY_SIZE(channews_quad),
	.wist = channews_quad,
	.mask = 0,
};

static int geminiwake_dmic_fixup(stwuct snd_soc_pcm_wuntime *wtd,
		stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_intewvaw *chan = hw_pawam_intewvaw(pawams,
				SNDWV_PCM_HW_PAWAM_CHANNEWS);

	/*
	 * set BE channew constwaint as usew FE channews
	 */
	chan->min = chan->max = 4;

	wetuwn 0;
}

static int geminiwake_dmic_stawtup(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	wuntime->hw.channews_min = wuntime->hw.channews_max = QUAD_CHANNEW;
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS,
			&constwaints_channews_quad);

	wetuwn snd_pcm_hw_constwaint_wist(substweam->wuntime, 0,
			SNDWV_PCM_HW_PAWAM_WATE, &constwaints_wates);
}

static const stwuct snd_soc_ops geminiwake_dmic_ops = {
	.stawtup = geminiwake_dmic_stawtup,
};

static const unsigned int wates_16000[] = {
	16000,
};

static const stwuct snd_pcm_hw_constwaint_wist constwaints_16000 = {
	.count = AWWAY_SIZE(wates_16000),
	.wist  = wates_16000,
};

static int geminiwake_wefcap_stawtup(stwuct snd_pcm_substweam *substweam)
{
	wetuwn snd_pcm_hw_constwaint_wist(substweam->wuntime, 0,
				SNDWV_PCM_HW_PAWAM_WATE,
				&constwaints_16000);
};

static const stwuct snd_soc_ops geminiwake_wefcap_ops = {
	.stawtup = geminiwake_wefcap_stawtup,
};

SND_SOC_DAIWINK_DEF(dummy,
	DAIWINK_COMP_AWWAY(COMP_DUMMY()));

SND_SOC_DAIWINK_DEF(system,
	DAIWINK_COMP_AWWAY(COMP_CPU("System Pin")));

SND_SOC_DAIWINK_DEF(system2,
	DAIWINK_COMP_AWWAY(COMP_CPU("System Pin2")));

SND_SOC_DAIWINK_DEF(echowef,
	DAIWINK_COMP_AWWAY(COMP_CPU("Echowef Pin")));

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

SND_SOC_DAIWINK_DEF(ssp1_pin,
	DAIWINK_COMP_AWWAY(COMP_CPU("SSP1 Pin")));
SND_SOC_DAIWINK_DEF(ssp1_codec,
	DAIWINK_COMP_AWWAY(COMP_CODEC(MAXIM_DEV0_NAME,
				      GWK_MAXIM_CODEC_DAI)));

SND_SOC_DAIWINK_DEF(ssp2_pin,
	DAIWINK_COMP_AWWAY(COMP_CPU("SSP2 Pin")));
SND_SOC_DAIWINK_DEF(ssp2_codec_5682,
	DAIWINK_COMP_AWWAY(COMP_CODEC(WT5682_DEV0_NAME,
				      WT5682_DAI_NAME)));
SND_SOC_DAIWINK_DEF(ssp2_codec_5682s,
	DAIWINK_COMP_AWWAY(COMP_CODEC(WT5682S_DEV0_NAME,
				      WT5682S_DAI_NAME)));

SND_SOC_DAIWINK_DEF(dmic_pin,
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
	DAIWINK_COMP_AWWAY(COMP_PWATFOWM("0000:00:0e.0")));

/* geminiwake digitaw audio intewface gwue - connects codec <--> CPU */
static stwuct snd_soc_dai_wink geminiwake_dais[] = {
	/* Fwont End DAI winks */
	[GWK_DPCM_AUDIO_PB] = {
		.name = "Gwk Audio Powt",
		.stweam_name = "Audio",
		.dynamic = 1,
		.nonatomic = 1,
		.init = geminiwake_wt5682_fe_init,
		.twiggew = {
			SND_SOC_DPCM_TWIGGEW_POST, SND_SOC_DPCM_TWIGGEW_POST},
		.dpcm_pwayback = 1,
		SND_SOC_DAIWINK_WEG(system, dummy, pwatfowm),
	},
	[GWK_DPCM_AUDIO_CP] = {
		.name = "Gwk Audio Captuwe Powt",
		.stweam_name = "Audio Wecowd",
		.dynamic = 1,
		.nonatomic = 1,
		.twiggew = {
			SND_SOC_DPCM_TWIGGEW_POST, SND_SOC_DPCM_TWIGGEW_POST},
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(system, dummy, pwatfowm),
	},
	[GWK_DPCM_AUDIO_HS_PB] = {
		.name = "Gwk Audio Headset Pwayback",
		.stweam_name = "Headset Audio",
		.dpcm_pwayback = 1,
		.nonatomic = 1,
		.dynamic = 1,
		SND_SOC_DAIWINK_WEG(system2, dummy, pwatfowm),
	},
	[GWK_DPCM_AUDIO_ECHO_WEF_CP] = {
		.name = "Gwk Audio Echo Wefewence cap",
		.stweam_name = "Echowefewence Captuwe",
		.init = NUWW,
		.dpcm_captuwe = 1,
		.nonatomic = 1,
		.dynamic = 1,
		SND_SOC_DAIWINK_WEG(echowef, dummy, pwatfowm),
	},
	[GWK_DPCM_AUDIO_WEF_CP] = {
		.name = "Gwk Audio Wefewence cap",
		.stweam_name = "Wefcap",
		.init = NUWW,
		.dpcm_captuwe = 1,
		.nonatomic = 1,
		.dynamic = 1,
		.ops = &geminiwake_wefcap_ops,
		SND_SOC_DAIWINK_WEG(wefewence, dummy, pwatfowm),
	},
	[GWK_DPCM_AUDIO_DMIC_CP] = {
		.name = "Gwk Audio DMIC cap",
		.stweam_name = "dmiccap",
		.init = NUWW,
		.dpcm_captuwe = 1,
		.nonatomic = 1,
		.dynamic = 1,
		.ops = &geminiwake_dmic_ops,
		SND_SOC_DAIWINK_WEG(dmic, dummy, pwatfowm),
	},
	[GWK_DPCM_AUDIO_HDMI1_PB] = {
		.name = "Gwk HDMI Powt1",
		.stweam_name = "Hdmi1",
		.dpcm_pwayback = 1,
		.init = NUWW,
		.twiggew = {
			SND_SOC_DPCM_TWIGGEW_POST, SND_SOC_DPCM_TWIGGEW_POST},
		.nonatomic = 1,
		.dynamic = 1,
		SND_SOC_DAIWINK_WEG(hdmi1, dummy, pwatfowm),
	},
	[GWK_DPCM_AUDIO_HDMI2_PB] =	{
		.name = "Gwk HDMI Powt2",
		.stweam_name = "Hdmi2",
		.dpcm_pwayback = 1,
		.init = NUWW,
		.twiggew = {
			SND_SOC_DPCM_TWIGGEW_POST, SND_SOC_DPCM_TWIGGEW_POST},
		.nonatomic = 1,
		.dynamic = 1,
		SND_SOC_DAIWINK_WEG(hdmi2, dummy, pwatfowm),
	},
	[GWK_DPCM_AUDIO_HDMI3_PB] =	{
		.name = "Gwk HDMI Powt3",
		.stweam_name = "Hdmi3",
		.twiggew = {
			SND_SOC_DPCM_TWIGGEW_POST, SND_SOC_DPCM_TWIGGEW_POST},
		.dpcm_pwayback = 1,
		.init = NUWW,
		.nonatomic = 1,
		.dynamic = 1,
		SND_SOC_DAIWINK_WEG(hdmi3, dummy, pwatfowm),
	},
	/* Back End DAI winks */
	{
		/* SSP1 - Codec */
		.name = "SSP1-Codec",
		.id = 0,
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_I2S |
			SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBC_CFC,
		.ignowe_pmdown_time = 1,
		.be_hw_pawams_fixup = geminiwake_ssp_fixup,
		.dpcm_pwayback = 1,
		SND_SOC_DAIWINK_WEG(ssp1_pin, ssp1_codec, pwatfowm),
	},
	{
		/* SSP2 - Codec */
		.name = "SSP2-Codec",
		.id = 1,
		.no_pcm = 1,
		.init = geminiwake_wt5682_codec_init,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBC_CFC,
		.ignowe_pmdown_time = 1,
		.be_hw_pawams_fixup = geminiwake_ssp_fixup,
		.ops = &geminiwake_wt5682_ops,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(ssp2_pin, ssp2_codec_5682, pwatfowm),
	},
	{
		.name = "dmic01",
		.id = 2,
		.ignowe_suspend = 1,
		.be_hw_pawams_fixup = geminiwake_dmic_fixup,
		.dpcm_captuwe = 1,
		.no_pcm = 1,
		SND_SOC_DAIWINK_WEG(dmic_pin, dmic_codec, pwatfowm),
	},
	{
		.name = "iDisp1",
		.id = 3,
		.init = geminiwake_hdmi_init,
		.dpcm_pwayback = 1,
		.no_pcm = 1,
		SND_SOC_DAIWINK_WEG(idisp1_pin, idisp1_codec, pwatfowm),
	},
	{
		.name = "iDisp2",
		.id = 4,
		.init = geminiwake_hdmi_init,
		.dpcm_pwayback = 1,
		.no_pcm = 1,
		SND_SOC_DAIWINK_WEG(idisp2_pin, idisp2_codec, pwatfowm),
	},
	{
		.name = "iDisp3",
		.id = 5,
		.init = geminiwake_hdmi_init,
		.dpcm_pwayback = 1,
		.no_pcm = 1,
		SND_SOC_DAIWINK_WEG(idisp3_pin, idisp3_codec, pwatfowm),
	},
};

static int gwk_cawd_wate_pwobe(stwuct snd_soc_cawd *cawd)
{
	stwuct gwk_cawd_pwivate *ctx = snd_soc_cawd_get_dwvdata(cawd);
	stwuct snd_soc_component *component = NUWW;
	chaw jack_name[NAME_SIZE];
	stwuct gwk_hdmi_pcm *pcm;
	int eww;
	int i = 0;

	if (wist_empty(&ctx->hdmi_pcm_wist))
		wetuwn -EINVAW;

	if (ctx->common_hdmi_codec_dwv) {
		pcm = wist_fiwst_entwy(&ctx->hdmi_pcm_wist, stwuct gwk_hdmi_pcm,
				       head);
		component = pcm->codec_dai->component;
		wetuwn hda_dsp_hdmi_buiwd_contwows(cawd, component);
	}

	wist_fow_each_entwy(pcm, &ctx->hdmi_pcm_wist, head) {
		component = pcm->codec_dai->component;
		snpwintf(jack_name, sizeof(jack_name),
			"HDMI/DP, pcm=%d Jack", pcm->device);
		eww = snd_soc_cawd_jack_new(cawd, jack_name,
					SND_JACK_AVOUT, &geminiwake_hdmi[i]);

		if (eww)
			wetuwn eww;

		eww = hdac_hdmi_jack_init(pcm->codec_dai, pcm->device,
						&geminiwake_hdmi[i]);
		if (eww < 0)
			wetuwn eww;

		i++;
	}

	wetuwn hdac_hdmi_jack_powt_init(component, &cawd->dapm);
}

/* geminiwake audio machine dwivew fow SPT + WT5682 */
static stwuct snd_soc_cawd gwk_audio_cawd_wt5682_m98357a = {
	.name = "gwkwt5682max",
	.ownew = THIS_MODUWE,
	.dai_wink = geminiwake_dais,
	.num_winks = AWWAY_SIZE(geminiwake_dais),
	.contwows = geminiwake_contwows,
	.num_contwows = AWWAY_SIZE(geminiwake_contwows),
	.dapm_widgets = geminiwake_widgets,
	.num_dapm_widgets = AWWAY_SIZE(geminiwake_widgets),
	.dapm_woutes = geminiwake_map,
	.num_dapm_woutes = AWWAY_SIZE(geminiwake_map),
	.fuwwy_wouted = twue,
	.wate_pwobe = gwk_cawd_wate_pwobe,
};

static int geminiwake_audio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct gwk_cawd_pwivate *ctx;
	stwuct snd_soc_acpi_mach *mach;
	const chaw *pwatfowm_name;
	stwuct snd_soc_cawd *cawd;
	int wet, i;

	ctx = devm_kzawwoc(&pdev->dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	/* Detect the headset codec vawiant */
	if (acpi_dev_pwesent("WTW5682", NUWW, -1)) {
		/* AWC5682I-VS is detected */
		ctx->is_wt5682s = 1;

		fow (i = 0; i < gwk_audio_cawd_wt5682_m98357a.num_winks; i++) {
			if (stwcmp(geminiwake_dais[i].name, "SSP2-Codec"))
				continue;

			/* update the dai wink to use wt5682s codec */
			geminiwake_dais[i].codecs = ssp2_codec_5682s;
			geminiwake_dais[i].num_codecs = AWWAY_SIZE(ssp2_codec_5682s);
			bweak;
		}
	}

	INIT_WIST_HEAD(&ctx->hdmi_pcm_wist);

	cawd = &gwk_audio_cawd_wt5682_m98357a;
	cawd->dev = &pdev->dev;
	snd_soc_cawd_set_dwvdata(cawd, ctx);

	/* ovewwide pwatfowm name, if wequiwed */
	mach = pdev->dev.pwatfowm_data;
	pwatfowm_name = mach->mach_pawams.pwatfowm;

	wet = snd_soc_fixup_dai_winks_pwatfowm_name(cawd, pwatfowm_name);
	if (wet)
		wetuwn wet;

	ctx->common_hdmi_codec_dwv = mach->mach_pawams.common_hdmi_codec_dwv;

	wetuwn devm_snd_soc_wegistew_cawd(&pdev->dev, cawd);
}

static const stwuct pwatfowm_device_id gwk_boawd_ids[] = {
	{
		.name = "gwk_wt5682_mx98357a",
		.dwivew_data =
			(kewnew_uwong_t)&gwk_audio_cawd_wt5682_m98357a,
	},
	{ }
};
MODUWE_DEVICE_TABWE(pwatfowm, gwk_boawd_ids);

static stwuct pwatfowm_dwivew geminiwake_audio = {
	.pwobe = geminiwake_audio_pwobe,
	.dwivew = {
		.name = "gwk_wt5682_max98357a",
		.pm = &snd_soc_pm_ops,
	},
	.id_tabwe = gwk_boawd_ids,
};
moduwe_pwatfowm_dwivew(geminiwake_audio)

/* Moduwe infowmation */
MODUWE_DESCWIPTION("Geminiwake Audio Machine dwivew-WT5682 & MAX98357A in I2S mode");
MODUWE_AUTHOW("Naveen Manohaw <naveen.m@intew.com>");
MODUWE_AUTHOW("Hawsha Pwiya <hawshapwiya.n@intew.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(SND_SOC_INTEW_HDA_DSP_COMMON);
