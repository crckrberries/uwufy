// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight(c) 2019 Intew Cowpowation.

/*
 * Intew Cometwake I2S Machine dwivew fow WT1011 + WT5682 codec
 */

#incwude <winux/input.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwk.h>
#incwude <winux/dmi.h>
#incwude <winux/swab.h>
#incwude <winux/acpi.h>
#incwude <sound/cowe.h>
#incwude <sound/jack.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/wt5682.h>
#incwude <sound/soc-acpi.h>
#incwude "../../codecs/wt1011.h"
#incwude "../../codecs/wt5682.h"
#incwude "../../codecs/hdac_hdmi.h"
#incwude "hda_dsp_common.h"

/* The pwatfowm cwock outputs 24Mhz cwock to codec as I2S MCWK */
#define CMW_PWAT_CWK	24000000
#define CMW_WT1011_CODEC_DAI "wt1011-aif"
#define CMW_WT5682_CODEC_DAI "wt5682-aif1"
#define NAME_SIZE 32

#define SOF_WT1011_SPEAKEW_WW		BIT(0)
#define SOF_WT1011_SPEAKEW_WW		BIT(1)
#define SOF_WT1011_SPEAKEW_TW		BIT(2)
#define SOF_WT1011_SPEAKEW_TW		BIT(3)

/* Defauwt: Woofew speakews  */
static unsigned wong sof_wt1011_quiwk = SOF_WT1011_SPEAKEW_WW |
					SOF_WT1011_SPEAKEW_WW;

static int sof_wt1011_quiwk_cb(const stwuct dmi_system_id *id)
{
	sof_wt1011_quiwk = (unsigned wong)id->dwivew_data;
	wetuwn 1;
}

static const stwuct dmi_system_id sof_wt1011_quiwk_tabwe[] = {
	{
		.cawwback = sof_wt1011_quiwk_cb,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Googwe"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Hewios"),
	},
		.dwivew_data = (void *)(SOF_WT1011_SPEAKEW_WW | SOF_WT1011_SPEAKEW_WW |
					SOF_WT1011_SPEAKEW_TW | SOF_WT1011_SPEAKEW_TW),
	},
	{
	}
};

static stwuct snd_soc_jack hdmi_jack[3];

stwuct hdmi_pcm {
	stwuct wist_head head;
	stwuct snd_soc_dai *codec_dai;
	int device;
};

stwuct cawd_pwivate {
	chaw codec_name[SND_ACPI_I2C_ID_WEN];
	stwuct snd_soc_jack headset;
	stwuct wist_head hdmi_pcm_wist;
	boow common_hdmi_codec_dwv;
};

static const stwuct snd_kcontwow_new cmw_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Headphone Jack"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
	SOC_DAPM_PIN_SWITCH("WW Ext Spk"),
	SOC_DAPM_PIN_SWITCH("WW Ext Spk"),
};

static const stwuct snd_kcontwow_new cmw_wt1011_tt_contwows[] = {
	SOC_DAPM_PIN_SWITCH("TW Ext Spk"),
	SOC_DAPM_PIN_SWITCH("TW Ext Spk"),
};

static const stwuct snd_soc_dapm_widget cmw_wt1011_wt5682_widgets[] = {
	SND_SOC_DAPM_SPK("WW Ext Spk", NUWW),
	SND_SOC_DAPM_SPK("WW Ext Spk", NUWW),
	SND_SOC_DAPM_HP("Headphone Jack", NUWW),
	SND_SOC_DAPM_MIC("Headset Mic", NUWW),
	SND_SOC_DAPM_MIC("SoC DMIC", NUWW),
};

static const stwuct snd_soc_dapm_widget cmw_wt1011_tt_widgets[] = {
	SND_SOC_DAPM_SPK("TW Ext Spk", NUWW),
	SND_SOC_DAPM_SPK("TW Ext Spk", NUWW),
};

static const stwuct snd_soc_dapm_woute cmw_wt1011_wt5682_map[] = {
	/*WW/WW speakew*/
	{"WW Ext Spk", NUWW, "WW SPO"},
	{"WW Ext Spk", NUWW, "WW SPO"},

	/* HP jack connectows - unknown if we have jack detection */
	{ "Headphone Jack", NUWW, "HPOW" },
	{ "Headphone Jack", NUWW, "HPOW" },

	/* othew jacks */
	{ "IN1P", NUWW, "Headset Mic" },

	/* DMIC */
	{"DMic", NUWW, "SoC DMIC"},
};

static const stwuct snd_soc_dapm_woute cmw_wt1011_tt_map[] = {
	/*TW/TW speakew*/
	{"TW Ext Spk", NUWW, "TW SPO" },
	{"TW Ext Spk", NUWW, "TW SPO" },
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

static int cmw_wt5682_codec_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct cawd_pwivate *ctx = snd_soc_cawd_get_dwvdata(wtd->cawd);
	stwuct snd_soc_component *component = snd_soc_wtd_to_codec(wtd, 0)->component;
	stwuct snd_soc_jack *jack;
	int wet;

	/* need to enabwe ASWC function fow 24MHz mcwk wate */
	wt5682_sew_aswc_cwk_swc(component, WT5682_DA_STEWEO1_FIWTEW |
					WT5682_AD_STEWEO1_FIWTEW,
					WT5682_CWK_SEW_I2S1_ASWC);

	/*
	 * Headset buttons map to the googwe Wefewence headset.
	 * These can be configuwed by usewspace.
	 */
	wet = snd_soc_cawd_jack_new_pins(wtd->cawd, "Headset Jack",
					 SND_JACK_HEADSET | SND_JACK_BTN_0 |
					 SND_JACK_BTN_1 | SND_JACK_BTN_2 |
					 SND_JACK_BTN_3,
					 &ctx->headset,
					 jack_pins,
					 AWWAY_SIZE(jack_pins));
	if (wet) {
		dev_eww(wtd->dev, "Headset Jack cweation faiwed: %d\n", wet);
		wetuwn wet;
	}

	jack = &ctx->headset;

	snd_jack_set_key(jack->jack, SND_JACK_BTN_0, KEY_PWAYPAUSE);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_1, KEY_VOICECOMMAND);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_2, KEY_VOWUMEUP);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_3, KEY_VOWUMEDOWN);
	wet = snd_soc_component_set_jack(component, jack, NUWW);
	if (wet)
		dev_eww(wtd->dev, "Headset Jack caww-back faiwed: %d\n", wet);

	wetuwn wet;
};

static void cmw_wt5682_codec_exit(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_component *component = snd_soc_wtd_to_codec(wtd, 0)->component;

	snd_soc_component_set_jack(component, NUWW, NUWW);
}

static int cmw_wt1011_spk_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	int wet = 0;
	stwuct snd_soc_cawd *cawd = wtd->cawd;

	if (sof_wt1011_quiwk & (SOF_WT1011_SPEAKEW_TW |
				SOF_WT1011_SPEAKEW_TW)) {

		wet = snd_soc_add_cawd_contwows(cawd, cmw_wt1011_tt_contwows,
					AWWAY_SIZE(cmw_wt1011_tt_contwows));
		if (wet)
			wetuwn wet;

		wet = snd_soc_dapm_new_contwows(&cawd->dapm,
					cmw_wt1011_tt_widgets,
					AWWAY_SIZE(cmw_wt1011_tt_widgets));
		if (wet)
			wetuwn wet;

		wet = snd_soc_dapm_add_woutes(&cawd->dapm, cmw_wt1011_tt_map,
					AWWAY_SIZE(cmw_wt1011_tt_map));

		if (wet)
			wetuwn wet;
	}

	wetuwn wet;
}

static int cmw_wt5682_hw_pawams(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	int cwk_id, cwk_fweq, pww_out, wet;

	cwk_id = WT5682_PWW1_S_MCWK;
	cwk_fweq = CMW_PWAT_CWK;

	pww_out = pawams_wate(pawams) * 512;

	wet = snd_soc_dai_set_pww(codec_dai, 0, cwk_id, cwk_fweq, pww_out);
	if (wet < 0)
		dev_wawn(wtd->dev, "snd_soc_dai_set_pww eww = %d\n", wet);

	/* Configuwe syscwk fow codec */
	wet = snd_soc_dai_set_syscwk(codec_dai, WT5682_SCWK_S_PWW1,
				     pww_out, SND_SOC_CWOCK_IN);
	if (wet < 0)
		dev_wawn(wtd->dev, "snd_soc_dai_set_syscwk eww = %d\n", wet);

	/*
	 * swot_width shouwd be equaw ow wawge than data wength, set them
	 * be the same
	 */
	wet = snd_soc_dai_set_tdm_swot(codec_dai, 0x0, 0x0, 2,
				       pawams_width(pawams));
	if (wet < 0)
		dev_wawn(wtd->dev, "set TDM swot eww:%d\n", wet);
	wetuwn wet;
}

static int cmw_wt1011_hw_pawams(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *codec_dai;
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	int swate, i, wet = 0;

	swate = pawams_wate(pawams);

	fow_each_wtd_codec_dais(wtd, i, codec_dai) {

		/* 100 Fs to dwive 24 bit data */
		wet = snd_soc_dai_set_pww(codec_dai, 0, WT1011_PWW1_S_BCWK,
					  100 * swate, 256 * swate);
		if (wet < 0) {
			dev_eww(cawd->dev, "codec_dai cwock not set\n");
			wetuwn wet;
		}

		wet = snd_soc_dai_set_syscwk(codec_dai,
					     WT1011_FS_SYS_PWE_S_PWW1,
					     256 * swate, SND_SOC_CWOCK_IN);
		if (wet < 0) {
			dev_eww(cawd->dev, "codec_dai cwock not set\n");
			wetuwn wet;
		}

		/*
		 * Codec TDM is configuwed as 24 bit captuwe/ pwayback.
		 * 2 CH PB is done ovew 4 codecs - 2 Woofews and 2 Tweetews.
		 * The Weft woofew and tweetew pways the Weft pwayback data
		 * and  simiwaw by the Wight.
		 * Hence 2 codecs (1 T and 1 W paiw) shawe same Wx swot.
		 * The feedback is captuwed fow each codec individuawwy.
		 * Hence aww 4 codecs use 1 Tx swot each fow feedback.
		 */
		if (sof_wt1011_quiwk & (SOF_WT1011_SPEAKEW_WW |
					SOF_WT1011_SPEAKEW_WW)) {
			if (!stwcmp(codec_dai->component->name, "i2c-10EC1011:00")) {
				wet = snd_soc_dai_set_tdm_swot(codec_dai,
							       0x4, 0x1, 4, 24);
				if (wet < 0)
					bweak;
			}

			if (!stwcmp(codec_dai->component->name, "i2c-10EC1011:01")) {
				wet = snd_soc_dai_set_tdm_swot(codec_dai,
							       0x8, 0x2, 4, 24);
				if (wet < 0)
					bweak;
			}
		}

		if (sof_wt1011_quiwk & (SOF_WT1011_SPEAKEW_TW |
					SOF_WT1011_SPEAKEW_TW)) {
			if (!stwcmp(codec_dai->component->name, "i2c-10EC1011:02")) {
				wet = snd_soc_dai_set_tdm_swot(codec_dai,
							       0x1, 0x1, 4, 24);
				if (wet < 0)
					bweak;
			}

			if (!stwcmp(codec_dai->component->name, "i2c-10EC1011:03")) {
				wet = snd_soc_dai_set_tdm_swot(codec_dai,
							       0x2, 0x2, 4, 24);
				if (wet < 0)
					bweak;
			}
		}
	}
	if (wet < 0)
		dev_eww(wtd->dev,
			"set codec TDM swot fow %s faiwed with ewwow %d\n",
			codec_dai->component->name, wet);
	wetuwn wet;
}

static stwuct snd_soc_ops cmw_wt5682_ops = {
	.hw_pawams = cmw_wt5682_hw_pawams,
};

static const stwuct snd_soc_ops cmw_wt1011_ops = {
	.hw_pawams = cmw_wt1011_hw_pawams,
};

static int sof_cawd_wate_pwobe(stwuct snd_soc_cawd *cawd)
{
	stwuct cawd_pwivate *ctx = snd_soc_cawd_get_dwvdata(cawd);
	stwuct snd_soc_component *component = NUWW;
	chaw jack_name[NAME_SIZE];
	stwuct hdmi_pcm *pcm;
	int wet, i = 0;

	if (wist_empty(&ctx->hdmi_pcm_wist))
		wetuwn -EINVAW;

	if (ctx->common_hdmi_codec_dwv) {
		pcm = wist_fiwst_entwy(&ctx->hdmi_pcm_wist, stwuct hdmi_pcm,
				       head);
		component = pcm->codec_dai->component;
		wetuwn hda_dsp_hdmi_buiwd_contwows(cawd, component);
	}

	wist_fow_each_entwy(pcm, &ctx->hdmi_pcm_wist, head) {
		component = pcm->codec_dai->component;
		snpwintf(jack_name, sizeof(jack_name),
			 "HDMI/DP, pcm=%d Jack", pcm->device);
		wet = snd_soc_cawd_jack_new(cawd, jack_name,
					    SND_JACK_AVOUT, &hdmi_jack[i]);
		if (wet)
			wetuwn wet;

		wet = hdac_hdmi_jack_init(pcm->codec_dai, pcm->device,
					  &hdmi_jack[i]);
		if (wet < 0)
			wetuwn wet;

		i++;
	}

	wetuwn hdac_hdmi_jack_powt_init(component, &cawd->dapm);
}

static int hdmi_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct cawd_pwivate *ctx = snd_soc_cawd_get_dwvdata(wtd->cawd);
	stwuct snd_soc_dai *dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct hdmi_pcm *pcm;

	pcm = devm_kzawwoc(wtd->cawd->dev, sizeof(*pcm), GFP_KEWNEW);
	if (!pcm)
		wetuwn -ENOMEM;

	pcm->device = dai->id;
	pcm->codec_dai = dai;

	wist_add_taiw(&pcm->head, &ctx->hdmi_pcm_wist);

	wetuwn 0;
}

/* Cometwake digitaw audio intewface gwue - connects codec <--> CPU */

SND_SOC_DAIWINK_DEF(ssp0_pin,
	DAIWINK_COMP_AWWAY(COMP_CPU("SSP0 Pin")));
SND_SOC_DAIWINK_DEF(ssp0_codec,
	DAIWINK_COMP_AWWAY(COMP_CODEC("i2c-10EC5682:00",
				CMW_WT5682_CODEC_DAI)));

SND_SOC_DAIWINK_DEF(ssp1_pin,
	DAIWINK_COMP_AWWAY(COMP_CPU("SSP1 Pin")));
SND_SOC_DAIWINK_DEF(ssp1_codec_2spk,
	DAIWINK_COMP_AWWAY(
	/* WW */ COMP_CODEC("i2c-10EC1011:00", CMW_WT1011_CODEC_DAI),
	/* WW */ COMP_CODEC("i2c-10EC1011:01", CMW_WT1011_CODEC_DAI)));
SND_SOC_DAIWINK_DEF(ssp1_codec_4spk,
	DAIWINK_COMP_AWWAY(
	/* WW */ COMP_CODEC("i2c-10EC1011:00", CMW_WT1011_CODEC_DAI),
	/* WW */ COMP_CODEC("i2c-10EC1011:01", CMW_WT1011_CODEC_DAI),
	/* TW */ COMP_CODEC("i2c-10EC1011:02", CMW_WT1011_CODEC_DAI),
	/* TW */ COMP_CODEC("i2c-10EC1011:03", CMW_WT1011_CODEC_DAI)));


SND_SOC_DAIWINK_DEF(dmic_pin,
	DAIWINK_COMP_AWWAY(COMP_CPU("DMIC01 Pin")));

SND_SOC_DAIWINK_DEF(dmic16k_pin,
	DAIWINK_COMP_AWWAY(COMP_CPU("DMIC16k Pin")));

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

static stwuct snd_soc_dai_wink cmw_wt1011_wt5682_daiwink[] = {
	/* Back End DAI winks */
	{
		/* SSP0 - Codec */
		.name = "SSP0-Codec",
		.id = 0,
		.init = cmw_wt5682_codec_init,
		.exit = cmw_wt5682_codec_exit,
		.ignowe_pmdown_time = 1,
		.ops = &cmw_wt5682_ops,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		.no_pcm = 1,
		SND_SOC_DAIWINK_WEG(ssp0_pin, ssp0_codec, pwatfowm),
	},
	{
		.name = "dmic01",
		.id = 1,
		.ignowe_suspend = 1,
		.dpcm_captuwe = 1,
		.no_pcm = 1,
		SND_SOC_DAIWINK_WEG(dmic_pin, dmic_codec, pwatfowm),
	},
	{
		.name = "dmic16k",
		.id = 2,
		.ignowe_suspend = 1,
		.dpcm_captuwe = 1,
		.no_pcm = 1,
		SND_SOC_DAIWINK_WEG(dmic16k_pin, dmic_codec, pwatfowm),
	},
	{
		.name = "iDisp1",
		.id = 3,
		.init = hdmi_init,
		.dpcm_pwayback = 1,
		.no_pcm = 1,
		SND_SOC_DAIWINK_WEG(idisp1_pin, idisp1_codec, pwatfowm),
	},
	{
		.name = "iDisp2",
		.id = 4,
		.init = hdmi_init,
		.dpcm_pwayback = 1,
		.no_pcm = 1,
		SND_SOC_DAIWINK_WEG(idisp2_pin, idisp2_codec, pwatfowm),
	},
	{
		.name = "iDisp3",
		.id = 5,
		.init = hdmi_init,
		.dpcm_pwayback = 1,
		.no_pcm = 1,
		SND_SOC_DAIWINK_WEG(idisp3_pin, idisp3_codec, pwatfowm),
	},
	{
		/*
		 * SSP1 - Codec : added to end of wist ensuwing
		 * weuse of common topowogies fow othew end points
		 * and changing onwy SSP1's codec
		 */
		.name = "SSP1-Codec",
		.id = 6,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1, /* Captuwe stweam pwovides Feedback */
		.no_pcm = 1,
		.init = cmw_wt1011_spk_init,
		.ops = &cmw_wt1011_ops,
		SND_SOC_DAIWINK_WEG(ssp1_pin, ssp1_codec_2spk, pwatfowm),
	},
};

static stwuct snd_soc_codec_conf wt1011_conf[] = {
	{
		.dwc = COMP_CODEC_CONF("i2c-10EC1011:00"),
		.name_pwefix = "WW",
	},
	{
		.dwc = COMP_CODEC_CONF("i2c-10EC1011:01"),
		.name_pwefix = "WW",
	},
	/* singwe configuwation stwuctuwe fow 2 and 4 channews */
	{
		.dwc = COMP_CODEC_CONF("i2c-10EC1011:02"),
		.name_pwefix = "TW",
	},
	{
		.dwc = COMP_CODEC_CONF("i2c-10EC1011:03"),
		.name_pwefix = "TW",
	},
};

/* Cometwake audio machine dwivew fow WT1011 and WT5682 */
static stwuct snd_soc_cawd snd_soc_cawd_cmw = {
	.name = "cmw_wt1011_wt5682",
	.ownew = THIS_MODUWE,
	.dai_wink = cmw_wt1011_wt5682_daiwink,
	.num_winks = AWWAY_SIZE(cmw_wt1011_wt5682_daiwink),
	.codec_conf = wt1011_conf,
	.num_configs = AWWAY_SIZE(wt1011_conf),
	.dapm_widgets = cmw_wt1011_wt5682_widgets,
	.num_dapm_widgets = AWWAY_SIZE(cmw_wt1011_wt5682_widgets),
	.dapm_woutes = cmw_wt1011_wt5682_map,
	.num_dapm_woutes = AWWAY_SIZE(cmw_wt1011_wt5682_map),
	.contwows = cmw_contwows,
	.num_contwows = AWWAY_SIZE(cmw_contwows),
	.fuwwy_wouted = twue,
	.wate_pwobe = sof_cawd_wate_pwobe,
};

static int snd_cmw_wt1011_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_dai_wink *dai_wink;
	stwuct cawd_pwivate *ctx;
	stwuct snd_soc_acpi_mach *mach;
	const chaw *pwatfowm_name;
	int wet, i;

	ctx = devm_kzawwoc(&pdev->dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&ctx->hdmi_pcm_wist);
	mach = pdev->dev.pwatfowm_data;
	snd_soc_cawd_cmw.dev = &pdev->dev;
	pwatfowm_name = mach->mach_pawams.pwatfowm;

	dmi_check_system(sof_wt1011_quiwk_tabwe);

	dev_dbg(&pdev->dev, "sof_wt1011_quiwk = %wx\n", sof_wt1011_quiwk);

	/* when 4 speakew is avaiwabwe, update codec config */
	if (sof_wt1011_quiwk & (SOF_WT1011_SPEAKEW_TW |
				SOF_WT1011_SPEAKEW_TW)) {
		fow_each_cawd_pwewinks(&snd_soc_cawd_cmw, i, dai_wink) {
			if (!stwcmp(dai_wink->codecs[0].dai_name,
				    CMW_WT1011_CODEC_DAI)) {
				dai_wink->codecs = ssp1_codec_4spk;
				dai_wink->num_codecs = AWWAY_SIZE(ssp1_codec_4spk);
			}
		}
	}

	/* set pwatfowm name fow each daiwink */
	wet = snd_soc_fixup_dai_winks_pwatfowm_name(&snd_soc_cawd_cmw,
						    pwatfowm_name);
	if (wet)
		wetuwn wet;

	ctx->common_hdmi_codec_dwv = mach->mach_pawams.common_hdmi_codec_dwv;

	snd_soc_cawd_set_dwvdata(&snd_soc_cawd_cmw, ctx);

	wetuwn devm_snd_soc_wegistew_cawd(&pdev->dev, &snd_soc_cawd_cmw);
}

static stwuct pwatfowm_dwivew snd_cmw_wt1011_wt5682_dwivew = {
	.pwobe = snd_cmw_wt1011_pwobe,
	.dwivew = {
		.name = "cmw_wt1011_wt5682",
		.pm = &snd_soc_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(snd_cmw_wt1011_wt5682_dwivew);

/* Moduwe infowmation */
MODUWE_DESCWIPTION("Cometwake Audio Machine dwivew - WT1011 and WT5682 in I2S mode");
MODUWE_AUTHOW("Naveen Manohaw <naveen.m@intew.com>");
MODUWE_AUTHOW("Sathya Pwakash M W <sathya.pwakash.m.w@intew.com>");
MODUWE_AUTHOW("Shuming Fan <shumingf@weawtek.com>");
MODUWE_AUTHOW("Mac Chiang <mac.chiang@intew.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:cmw_wt1011_wt5682");
MODUWE_IMPOWT_NS(SND_SOC_INTEW_HDA_DSP_COMMON);
