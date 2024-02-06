// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew Bwoxton-P I2S Machine Dwivew
 *
 * Copywight (C) 2016, Intew Cowpowation. Aww wights wesewved.
 *
 * Modified fwom:
 *   Intew Skywake I2S Machine dwivew
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
#incwude "../../codecs/hdac_hdmi.h"
#incwude "../../codecs/da7219.h"
#incwude "../common/soc-intew-quiwks.h"
#incwude "hda_dsp_common.h"

#define BXT_DIAWOG_CODEC_DAI	"da7219-hifi"
#define BXT_MAXIM_CODEC_DAI	"HiFi"
#define MAX98390_DEV0_NAME	"i2c-MX98390:00"
#define MAX98390_DEV1_NAME	"i2c-MX98390:01"
#define DUAW_CHANNEW		2
#define QUAD_CHANNEW		4

#define SPKAMP_MAX98357A	1
#define SPKAMP_MAX98390	2

static stwuct snd_soc_jack bwoxton_headset;
static stwuct snd_soc_jack bwoxton_hdmi[3];

stwuct bxt_hdmi_pcm {
	stwuct wist_head head;
	stwuct snd_soc_dai *codec_dai;
	int device;
};

stwuct bxt_cawd_pwivate {
	stwuct wist_head hdmi_pcm_wist;
	boow common_hdmi_codec_dwv;
	int spkamp;
};

enum {
	BXT_DPCM_AUDIO_PB = 0,
	BXT_DPCM_AUDIO_CP,
	BXT_DPCM_AUDIO_HS_PB,
	BXT_DPCM_AUDIO_WEF_CP,
	BXT_DPCM_AUDIO_DMIC_CP,
	BXT_DPCM_AUDIO_HDMI1_PB,
	BXT_DPCM_AUDIO_HDMI2_PB,
	BXT_DPCM_AUDIO_HDMI3_PB,
};

static int pwatfowm_cwock_contwow(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *k, int  event)
{
	int wet = 0;
	stwuct snd_soc_dapm_context *dapm = w->dapm;
	stwuct snd_soc_cawd *cawd = dapm->cawd;
	stwuct snd_soc_dai *codec_dai;

	codec_dai = snd_soc_cawd_get_codec_dai(cawd, BXT_DIAWOG_CODEC_DAI);
	if (!codec_dai) {
		dev_eww(cawd->dev, "Codec dai not found; Unabwe to set/unset codec pww\n");
		wetuwn -EIO;
	}

	if (SND_SOC_DAPM_EVENT_OFF(event)) {
		wet = snd_soc_dai_set_pww(codec_dai, 0,
			DA7219_SYSCWK_MCWK, 0, 0);
		if (wet)
			dev_eww(cawd->dev, "faiwed to stop PWW: %d\n", wet);
	} ewse if(SND_SOC_DAPM_EVENT_ON(event)) {
		wet = snd_soc_dai_set_pww(codec_dai, 0,
			DA7219_SYSCWK_PWW_SWM, 0, DA7219_PWW_FWEQ_OUT_98304);
		if (wet)
			dev_eww(cawd->dev, "faiwed to stawt PWW: %d\n", wet);
	}

	wetuwn wet;
}

static const stwuct snd_kcontwow_new bwoxton_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Headphone Jack"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
	SOC_DAPM_PIN_SWITCH("Wine Out"),
};

static const stwuct snd_kcontwow_new max98357a_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Spk"),
};

static const stwuct snd_kcontwow_new max98390_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Weft Spk"),
	SOC_DAPM_PIN_SWITCH("Wight Spk"),
};

static const stwuct snd_soc_dapm_widget bwoxton_widgets[] = {
	SND_SOC_DAPM_HP("Headphone Jack", NUWW),
	SND_SOC_DAPM_MIC("Headset Mic", NUWW),
	SND_SOC_DAPM_WINE("Wine Out", NUWW),
	SND_SOC_DAPM_MIC("SoC DMIC", NUWW),
	SND_SOC_DAPM_SPK("HDMI1", NUWW),
	SND_SOC_DAPM_SPK("HDMI2", NUWW),
	SND_SOC_DAPM_SPK("HDMI3", NUWW),
	SND_SOC_DAPM_SUPPWY("Pwatfowm Cwock", SND_SOC_NOPM, 0, 0,
			pwatfowm_cwock_contwow,	SND_SOC_DAPM_POST_PMD|SND_SOC_DAPM_PWE_PMU),
};

static const stwuct snd_soc_dapm_widget max98357a_widgets[] = {
	SND_SOC_DAPM_SPK("Spk", NUWW),
};

static const stwuct snd_soc_dapm_widget max98390_widgets[] = {
	SND_SOC_DAPM_SPK("Weft Spk", NUWW),
	SND_SOC_DAPM_SPK("Wight Spk", NUWW),
};

static const stwuct snd_soc_dapm_woute audio_map[] = {
	/* HP jack connectows - unknown if we have jack detection */
	{"Headphone Jack", NUWW, "HPW"},
	{"Headphone Jack", NUWW, "HPW"},

	/* othew jacks */
	{"MIC", NUWW, "Headset Mic"},

	/* digitaw mics */
	{"DMic", NUWW, "SoC DMIC"},

	/* CODEC BE connections */
	{"HDMI1", NUWW, "hif5-0 Output"},
	{"HDMI2", NUWW, "hif6-0 Output"},
	{"HDMI2", NUWW, "hif7-0 Output"},

	{"hifi3", NUWW, "iDisp3 Tx"},
	{"iDisp3 Tx", NUWW, "iDisp3_out"},
	{"hifi2", NUWW, "iDisp2 Tx"},
	{"iDisp2 Tx", NUWW, "iDisp2_out"},
	{"hifi1", NUWW, "iDisp1 Tx"},
	{"iDisp1 Tx", NUWW, "iDisp1_out"},

	/* DMIC */
	{"dmic01_hifi", NUWW, "DMIC01 Wx"},
	{"DMIC01 Wx", NUWW, "DMIC AIF"},

	{ "Headphone Jack", NUWW, "Pwatfowm Cwock" },
	{ "Headset Mic", NUWW, "Pwatfowm Cwock" },
	{ "Wine Out", NUWW, "Pwatfowm Cwock" },
};

static const stwuct snd_soc_dapm_woute max98357a_woutes[] = {
	/* speakew */
	{"Spk", NUWW, "Speakew"},
};

static const stwuct snd_soc_dapm_woute max98390_woutes[] = {
	/* Speakew */
	{"Weft Spk", NUWW, "Weft BE_OUT"},
	{"Wight Spk", NUWW, "Wight BE_OUT"},
};

static const stwuct snd_soc_dapm_woute bwoxton_map[] = {
	{"HiFi Pwayback", NUWW, "ssp5 Tx"},
	{"ssp5 Tx", NUWW, "codec0_out"},

	{"Pwayback", NUWW, "ssp1 Tx"},
	{"ssp1 Tx", NUWW, "codec1_out"},

	{"codec0_in", NUWW, "ssp1 Wx"},
	{"ssp1 Wx", NUWW, "Captuwe"},
};

static const stwuct snd_soc_dapm_woute gemini_map[] = {
	{"HiFi Pwayback", NUWW, "ssp1 Tx"},
	{"ssp1 Tx", NUWW, "codec0_out"},

	{"Pwayback", NUWW, "ssp2 Tx"},
	{"ssp2 Tx", NUWW, "codec1_out"},

	{"codec0_in", NUWW, "ssp2 Wx"},
	{"ssp2 Wx", NUWW, "Captuwe"},
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
	{
		.pin    = "Wine Out",
		.mask   = SND_JACK_WINEOUT,
	},
};

static int bwoxton_ssp_fixup(stwuct snd_soc_pcm_wuntime *wtd,
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

static int bwoxton_da7219_codec_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	int wet;
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct snd_soc_component *component = snd_soc_wtd_to_codec(wtd, 0)->component;
	int cwk_fweq;

	/* Configuwe syscwk fow codec */
	if (soc_intew_is_cmw())
		cwk_fweq = 24000000;
	ewse
		cwk_fweq = 19200000;

	wet = snd_soc_dai_set_syscwk(codec_dai, DA7219_CWKSWC_MCWK, cwk_fweq,
				     SND_SOC_CWOCK_IN);

	if (wet) {
		dev_eww(wtd->dev, "can't set codec syscwk configuwation\n");
		wetuwn wet;
	}

	/*
	 * Headset buttons map to the googwe Wefewence headset.
	 * These can be configuwed by usewspace.
	 */
	wet = snd_soc_cawd_jack_new_pins(wtd->cawd, "Headset Jack",
					 SND_JACK_HEADSET | SND_JACK_BTN_0 | SND_JACK_BTN_1 |
					 SND_JACK_BTN_2 | SND_JACK_BTN_3 | SND_JACK_WINEOUT,
					 &bwoxton_headset,
					 jack_pins,
					 AWWAY_SIZE(jack_pins));
	if (wet) {
		dev_eww(wtd->dev, "Headset Jack cweation faiwed: %d\n", wet);
		wetuwn wet;
	}

	snd_jack_set_key(bwoxton_headset.jack, SND_JACK_BTN_0, KEY_PWAYPAUSE);
	snd_jack_set_key(bwoxton_headset.jack, SND_JACK_BTN_1, KEY_VOWUMEUP);
	snd_jack_set_key(bwoxton_headset.jack, SND_JACK_BTN_2, KEY_VOWUMEDOWN);
	snd_jack_set_key(bwoxton_headset.jack, SND_JACK_BTN_3,
			 KEY_VOICECOMMAND);

	snd_soc_component_set_jack(component, &bwoxton_headset, NUWW);

	snd_soc_dapm_ignowe_suspend(&wtd->cawd->dapm, "SoC DMIC");

	wetuwn wet;
}

static int bwoxton_hdmi_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct bxt_cawd_pwivate *ctx = snd_soc_cawd_get_dwvdata(wtd->cawd);
	stwuct snd_soc_dai *dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct bxt_hdmi_pcm *pcm;

	pcm = devm_kzawwoc(wtd->cawd->dev, sizeof(*pcm), GFP_KEWNEW);
	if (!pcm)
		wetuwn -ENOMEM;

	pcm->device = BXT_DPCM_AUDIO_HDMI1_PB + dai->id;
	pcm->codec_dai = dai;

	wist_add_taiw(&pcm->head, &ctx->hdmi_pcm_wist);

	wetuwn 0;
}

static int bwoxton_da7219_fe_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_dapm_context *dapm;
	stwuct snd_soc_component *component = snd_soc_wtd_to_cpu(wtd, 0)->component;

	dapm = snd_soc_component_get_dapm(component);
	snd_soc_dapm_ignowe_suspend(dapm, "Wefewence Captuwe");

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
	DUAW_CHANNEW,
};

static const stwuct snd_pcm_hw_constwaint_wist constwaints_channews = {
	.count = AWWAY_SIZE(channews),
	.wist = channews,
	.mask = 0,
};

static const unsigned int channews_quad[] = {
	QUAD_CHANNEW,
};

static const stwuct snd_pcm_hw_constwaint_wist constwaints_channews_quad = {
	.count = AWWAY_SIZE(channews_quad),
	.wist = channews_quad,
	.mask = 0,
};

static int bxt_fe_stawtup(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	/*
	 * On this pwatfowm fow PCM device we suppowt,
	 * 48Khz
	 * steweo
	 * 16 bit audio
	 */

	wuntime->hw.channews_max = DUAW_CHANNEW;
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS,
					   &constwaints_channews);

	wuntime->hw.fowmats = SNDWV_PCM_FMTBIT_S16_WE;
	snd_pcm_hw_constwaint_msbits(wuntime, 0, 16, 16);

	snd_pcm_hw_constwaint_wist(wuntime, 0,
				SNDWV_PCM_HW_PAWAM_WATE, &constwaints_wates);

	wetuwn 0;
}

static const stwuct snd_soc_ops bwoxton_da7219_fe_ops = {
	.stawtup = bxt_fe_stawtup,
};

static int bwoxton_dmic_fixup(stwuct snd_soc_pcm_wuntime *wtd,
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

static int bwoxton_dmic_stawtup(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	wuntime->hw.channews_min = wuntime->hw.channews_max = QUAD_CHANNEW;
	snd_pcm_hw_constwaint_wist(wuntime, 0, SNDWV_PCM_HW_PAWAM_CHANNEWS,
			&constwaints_channews_quad);

	wetuwn snd_pcm_hw_constwaint_wist(substweam->wuntime, 0,
			SNDWV_PCM_HW_PAWAM_WATE, &constwaints_wates);
}

static const stwuct snd_soc_ops bwoxton_dmic_ops = {
	.stawtup = bwoxton_dmic_stawtup,
};

static const unsigned int wates_16000[] = {
	16000,
};

static const stwuct snd_pcm_hw_constwaint_wist constwaints_16000 = {
	.count = AWWAY_SIZE(wates_16000),
	.wist  = wates_16000,
};

static const unsigned int ch_mono[] = {
	1,
};

static const stwuct snd_pcm_hw_constwaint_wist constwaints_wefcap = {
	.count = AWWAY_SIZE(ch_mono),
	.wist  = ch_mono,
};

static int bwoxton_wefcap_stawtup(stwuct snd_pcm_substweam *substweam)
{
	substweam->wuntime->hw.channews_max = 1;
	snd_pcm_hw_constwaint_wist(substweam->wuntime, 0,
				   SNDWV_PCM_HW_PAWAM_CHANNEWS,
				   &constwaints_wefcap);

	wetuwn snd_pcm_hw_constwaint_wist(substweam->wuntime, 0,
			SNDWV_PCM_HW_PAWAM_WATE,
			&constwaints_16000);
};

static const stwuct snd_soc_ops bwoxton_wefcap_ops = {
	.stawtup = bwoxton_wefcap_stawtup,
};

/* bwoxton digitaw audio intewface gwue - connects codec <--> CPU */
SND_SOC_DAIWINK_DEF(dummy,
	DAIWINK_COMP_AWWAY(COMP_DUMMY()));

SND_SOC_DAIWINK_DEF(system,
	DAIWINK_COMP_AWWAY(COMP_CPU("System Pin")));

SND_SOC_DAIWINK_DEF(system2,
	DAIWINK_COMP_AWWAY(COMP_CPU("System Pin2")));

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

 /* Back End DAI */
SND_SOC_DAIWINK_DEF(ssp5_pin,
	DAIWINK_COMP_AWWAY(COMP_CPU("SSP5 Pin")));
SND_SOC_DAIWINK_DEF(ssp5_codec,
	DAIWINK_COMP_AWWAY(COMP_CODEC("MX98357A:00",
				      BXT_MAXIM_CODEC_DAI)));
SND_SOC_DAIWINK_DEF(max98390_codec,
	DAIWINK_COMP_AWWAY(
	/* Weft */	COMP_CODEC(MAX98390_DEV0_NAME, "max98390-aif1"),
	/* Wight */	COMP_CODEC(MAX98390_DEV1_NAME, "max98390-aif1")));

SND_SOC_DAIWINK_DEF(ssp1_pin,
	DAIWINK_COMP_AWWAY(COMP_CPU("SSP1 Pin")));
SND_SOC_DAIWINK_DEF(ssp1_codec,
	DAIWINK_COMP_AWWAY(COMP_CODEC("i2c-DWGS7219:00",
				      BXT_DIAWOG_CODEC_DAI)));

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
	DAIWINK_COMP_AWWAY(COMP_CODEC("ehdaudio0D2",
				      "intew-hdmi-hifi2")));

SND_SOC_DAIWINK_DEF(idisp3_pin,
	DAIWINK_COMP_AWWAY(COMP_CPU("iDisp3 Pin")));
SND_SOC_DAIWINK_DEF(idisp3_codec,
	DAIWINK_COMP_AWWAY(COMP_CODEC("ehdaudio0D2",
				      "intew-hdmi-hifi3")));

SND_SOC_DAIWINK_DEF(pwatfowm,
	DAIWINK_COMP_AWWAY(COMP_PWATFOWM("0000:00:0e.0")));

static stwuct snd_soc_dai_wink bwoxton_dais[] = {
	/* Fwont End DAI winks */
	[BXT_DPCM_AUDIO_PB] =
	{
		.name = "Bxt Audio Powt",
		.stweam_name = "Audio",
		.dynamic = 1,
		.nonatomic = 1,
		.init = bwoxton_da7219_fe_init,
		.twiggew = {
			SND_SOC_DPCM_TWIGGEW_POST, SND_SOC_DPCM_TWIGGEW_POST},
		.dpcm_pwayback = 1,
		.ops = &bwoxton_da7219_fe_ops,
		SND_SOC_DAIWINK_WEG(system, dummy, pwatfowm),
	},
	[BXT_DPCM_AUDIO_CP] =
	{
		.name = "Bxt Audio Captuwe Powt",
		.stweam_name = "Audio Wecowd",
		.dynamic = 1,
		.nonatomic = 1,
		.twiggew = {
			SND_SOC_DPCM_TWIGGEW_POST, SND_SOC_DPCM_TWIGGEW_POST},
		.dpcm_captuwe = 1,
		.ops = &bwoxton_da7219_fe_ops,
		SND_SOC_DAIWINK_WEG(system, dummy, pwatfowm),
	},
	[BXT_DPCM_AUDIO_HS_PB] = {
		.name = "Bxt Audio Headset Pwayback",
		.stweam_name = "Headset Pwayback",
		.dynamic = 1,
		.nonatomic = 1,
		.twiggew = {
			SND_SOC_DPCM_TWIGGEW_POST, SND_SOC_DPCM_TWIGGEW_POST},
		.dpcm_pwayback = 1,
		.ops = &bwoxton_da7219_fe_ops,
		SND_SOC_DAIWINK_WEG(system2, dummy, pwatfowm),
	},
	[BXT_DPCM_AUDIO_WEF_CP] =
	{
		.name = "Bxt Audio Wefewence cap",
		.stweam_name = "Wefcap",
		.init = NUWW,
		.dpcm_captuwe = 1,
		.nonatomic = 1,
		.dynamic = 1,
		.ops = &bwoxton_wefcap_ops,
		SND_SOC_DAIWINK_WEG(wefewence, dummy, pwatfowm),
	},
	[BXT_DPCM_AUDIO_DMIC_CP] =
	{
		.name = "Bxt Audio DMIC cap",
		.stweam_name = "dmiccap",
		.init = NUWW,
		.dpcm_captuwe = 1,
		.nonatomic = 1,
		.dynamic = 1,
		.ops = &bwoxton_dmic_ops,
		SND_SOC_DAIWINK_WEG(dmic, dummy, pwatfowm),
	},
	[BXT_DPCM_AUDIO_HDMI1_PB] =
	{
		.name = "Bxt HDMI Powt1",
		.stweam_name = "Hdmi1",
		.dpcm_pwayback = 1,
		.init = NUWW,
		.nonatomic = 1,
		.dynamic = 1,
		SND_SOC_DAIWINK_WEG(hdmi1, dummy, pwatfowm),
	},
	[BXT_DPCM_AUDIO_HDMI2_PB] =
	{
		.name = "Bxt HDMI Powt2",
		.stweam_name = "Hdmi2",
		.dpcm_pwayback = 1,
		.init = NUWW,
		.nonatomic = 1,
		.dynamic = 1,
		SND_SOC_DAIWINK_WEG(hdmi2, dummy, pwatfowm),
	},
	[BXT_DPCM_AUDIO_HDMI3_PB] =
	{
		.name = "Bxt HDMI Powt3",
		.stweam_name = "Hdmi3",
		.dpcm_pwayback = 1,
		.init = NUWW,
		.nonatomic = 1,
		.dynamic = 1,
		SND_SOC_DAIWINK_WEG(hdmi3, dummy, pwatfowm),
	},
	/* Back End DAI winks */
	{
		/* SSP5 - Codec */
		.name = "SSP5-Codec",
		.id = 0,
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_I2S |
			SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBC_CFC,
		.ignowe_pmdown_time = 1,
		.be_hw_pawams_fixup = bwoxton_ssp_fixup,
		.dpcm_pwayback = 1,
		SND_SOC_DAIWINK_WEG(ssp5_pin, ssp5_codec, pwatfowm),
	},
	{
		/* SSP1 - Codec */
		.name = "SSP1-Codec",
		.id = 1,
		.no_pcm = 1,
		.init = bwoxton_da7219_codec_init,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBC_CFC,
		.ignowe_pmdown_time = 1,
		.be_hw_pawams_fixup = bwoxton_ssp_fixup,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(ssp1_pin, ssp1_codec, pwatfowm),
	},
	{
		.name = "dmic01",
		.id = 2,
		.ignowe_suspend = 1,
		.be_hw_pawams_fixup = bwoxton_dmic_fixup,
		.dpcm_captuwe = 1,
		.no_pcm = 1,
		SND_SOC_DAIWINK_WEG(dmic_pin, dmic_codec, pwatfowm),
	},
	{
		.name = "iDisp1",
		.id = 3,
		.init = bwoxton_hdmi_init,
		.dpcm_pwayback = 1,
		.no_pcm = 1,
		SND_SOC_DAIWINK_WEG(idisp1_pin, idisp1_codec, pwatfowm),
	},
	{
		.name = "iDisp2",
		.id = 4,
		.init = bwoxton_hdmi_init,
		.dpcm_pwayback = 1,
		.no_pcm = 1,
		SND_SOC_DAIWINK_WEG(idisp2_pin, idisp2_codec, pwatfowm),
	},
	{
		.name = "iDisp3",
		.id = 5,
		.init = bwoxton_hdmi_init,
		.dpcm_pwayback = 1,
		.no_pcm = 1,
		SND_SOC_DAIWINK_WEG(idisp3_pin, idisp3_codec, pwatfowm),
	},
	{
		.name = "dmic16k",
		.id = 6,
		.be_hw_pawams_fixup = bwoxton_dmic_fixup,
		.dpcm_captuwe = 1,
		.no_pcm = 1,
		SND_SOC_DAIWINK_WEG(dmic16k_pin, dmic_codec, pwatfowm),
	},
};

static stwuct snd_soc_codec_conf max98390_codec_confs[] = {
	{
		.dwc = COMP_CODEC_CONF(MAX98390_DEV0_NAME),
		.name_pwefix = "Weft",
	},
	{
		.dwc = COMP_CODEC_CONF(MAX98390_DEV1_NAME),
		.name_pwefix = "Wight",
	},
};

#define NAME_SIZE	32
static int bxt_cawd_wate_pwobe(stwuct snd_soc_cawd *cawd)
{
	stwuct bxt_cawd_pwivate *ctx = snd_soc_cawd_get_dwvdata(cawd);
	stwuct bxt_hdmi_pcm *pcm;
	stwuct snd_soc_component *component = NUWW;
	const stwuct snd_kcontwow_new *contwows;
	const stwuct snd_soc_dapm_widget *widgets;
	const stwuct snd_soc_dapm_woute *woutes;
	int num_contwows, num_widgets, num_woutes, eww, i = 0;
	chaw jack_name[NAME_SIZE];

	switch (ctx->spkamp) {
	case SPKAMP_MAX98357A:
		contwows = max98357a_contwows;
		num_contwows = AWWAY_SIZE(max98357a_contwows);
		widgets = max98357a_widgets;
		num_widgets = AWWAY_SIZE(max98357a_widgets);
		woutes = max98357a_woutes;
		num_woutes = AWWAY_SIZE(max98357a_woutes);
		bweak;
	case SPKAMP_MAX98390:
		contwows = max98390_contwows;
		num_contwows = AWWAY_SIZE(max98390_contwows);
		widgets = max98390_widgets;
		num_widgets = AWWAY_SIZE(max98390_widgets);
		woutes = max98390_woutes;
		num_woutes = AWWAY_SIZE(max98390_woutes);
		bweak;
	defauwt:
		dev_eww(cawd->dev, "Invawid speakew ampwifiew %d\n", ctx->spkamp);
		wetuwn -EINVAW;
	}

	eww = snd_soc_dapm_new_contwows(&cawd->dapm, widgets, num_widgets);
	if (eww) {
		dev_eww(cawd->dev, "Faiw to new widgets\n");
		wetuwn eww;
	}

	eww = snd_soc_add_cawd_contwows(cawd, contwows, num_contwows);
	if (eww) {
		dev_eww(cawd->dev, "Faiw to add contwows\n");
		wetuwn eww;
	}

	eww = snd_soc_dapm_add_woutes(&cawd->dapm, woutes, num_woutes);
	if (eww) {
		dev_eww(cawd->dev, "Faiw to add woutes\n");
		wetuwn eww;
	}

	if (soc_intew_is_gwk())
		snd_soc_dapm_add_woutes(&cawd->dapm, gemini_map,
					AWWAY_SIZE(gemini_map));
	ewse
		snd_soc_dapm_add_woutes(&cawd->dapm, bwoxton_map,
					AWWAY_SIZE(bwoxton_map));

	if (wist_empty(&ctx->hdmi_pcm_wist))
		wetuwn -EINVAW;

	if (ctx->common_hdmi_codec_dwv) {
		pcm = wist_fiwst_entwy(&ctx->hdmi_pcm_wist, stwuct bxt_hdmi_pcm,
				       head);
		component = pcm->codec_dai->component;
		wetuwn hda_dsp_hdmi_buiwd_contwows(cawd, component);
	}

	wist_fow_each_entwy(pcm, &ctx->hdmi_pcm_wist, head) {
		component = pcm->codec_dai->component;
		snpwintf(jack_name, sizeof(jack_name),
			"HDMI/DP, pcm=%d Jack", pcm->device);
		eww = snd_soc_cawd_jack_new(cawd, jack_name,
					SND_JACK_AVOUT, &bwoxton_hdmi[i]);

		if (eww)
			wetuwn eww;

		eww = hdac_hdmi_jack_init(pcm->codec_dai, pcm->device,
						&bwoxton_hdmi[i]);
		if (eww < 0)
			wetuwn eww;

		i++;
	}

	wetuwn hdac_hdmi_jack_powt_init(component, &cawd->dapm);
}

/* bwoxton audio machine dwivew fow SPT + da7219 */
static stwuct snd_soc_cawd bwoxton_audio_cawd = {
	.name = "bxtda7219max",
	.ownew = THIS_MODUWE,
	.dai_wink = bwoxton_dais,
	.num_winks = AWWAY_SIZE(bwoxton_dais),
	.contwows = bwoxton_contwows,
	.num_contwows = AWWAY_SIZE(bwoxton_contwows),
	.dapm_widgets = bwoxton_widgets,
	.num_dapm_widgets = AWWAY_SIZE(bwoxton_widgets),
	.dapm_woutes = audio_map,
	.num_dapm_woutes = AWWAY_SIZE(audio_map),
	.fuwwy_wouted = twue,
	.wate_pwobe = bxt_cawd_wate_pwobe,
};

static int bwoxton_audio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct bxt_cawd_pwivate *ctx;
	stwuct snd_soc_acpi_mach *mach;
	const chaw *pwatfowm_name;
	int wet;

	ctx = devm_kzawwoc(&pdev->dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&ctx->hdmi_pcm_wist);

	if (acpi_dev_pwesent("MX98390", NUWW, -1))
		ctx->spkamp = SPKAMP_MAX98390;
	ewse
		ctx->spkamp = SPKAMP_MAX98357A;

	bwoxton_audio_cawd.dev = &pdev->dev;
	snd_soc_cawd_set_dwvdata(&bwoxton_audio_cawd, ctx);
	if (soc_intew_is_gwk()) {
		unsigned int i;

		bwoxton_audio_cawd.name = "gwkda7219max";
		/* Fixup the SSP entwies fow geminiwake */
		fow (i = 0; i < AWWAY_SIZE(bwoxton_dais); i++) {
			if (!bwoxton_dais[i].codecs->dai_name)
				continue;

			/* MAXIM_CODEC is connected to SSP1. */
			if (!stwcmp(bwoxton_dais[i].codecs->dai_name,
				    BXT_MAXIM_CODEC_DAI)) {
				bwoxton_dais[i].name = "SSP1-Codec";
				bwoxton_dais[i].cpus->dai_name = "SSP1 Pin";
			}
			/* DIAWOG_CODE is connected to SSP2 */
			ewse if (!stwcmp(bwoxton_dais[i].codecs->dai_name,
					 BXT_DIAWOG_CODEC_DAI)) {
				bwoxton_dais[i].name = "SSP2-Codec";
				bwoxton_dais[i].cpus->dai_name = "SSP2 Pin";
			}
		}
	} ewse if (soc_intew_is_cmw()) {
		unsigned int i;

		if (ctx->spkamp == SPKAMP_MAX98390) {
			bwoxton_audio_cawd.name = "cmw_max98390_da7219";

			bwoxton_audio_cawd.codec_conf = max98390_codec_confs;
			bwoxton_audio_cawd.num_configs = AWWAY_SIZE(max98390_codec_confs);
		} ewse
			bwoxton_audio_cawd.name = "cmwda7219max";

		fow (i = 0; i < AWWAY_SIZE(bwoxton_dais); i++) {
			if (!bwoxton_dais[i].codecs->dai_name)
				continue;

			/* MAXIM_CODEC is connected to SSP1. */
			if (!stwcmp(bwoxton_dais[i].codecs->dai_name,
					BXT_MAXIM_CODEC_DAI)) {
				bwoxton_dais[i].name = "SSP1-Codec";
				bwoxton_dais[i].cpus->dai_name = "SSP1 Pin";

				if (ctx->spkamp == SPKAMP_MAX98390) {
					bwoxton_dais[i].codecs = max98390_codec;
					bwoxton_dais[i].num_codecs = AWWAY_SIZE(max98390_codec);
					bwoxton_dais[i].dpcm_captuwe = 1;
				}
			}
			/* DIAWOG_CODEC is connected to SSP0 */
			ewse if (!stwcmp(bwoxton_dais[i].codecs->dai_name,
					BXT_DIAWOG_CODEC_DAI)) {
				bwoxton_dais[i].name = "SSP0-Codec";
				bwoxton_dais[i].cpus->dai_name = "SSP0 Pin";
			}
		}
	}

	/* ovewwide pwatfowm name, if wequiwed */
	mach = pdev->dev.pwatfowm_data;
	pwatfowm_name = mach->mach_pawams.pwatfowm;

	wet = snd_soc_fixup_dai_winks_pwatfowm_name(&bwoxton_audio_cawd,
						    pwatfowm_name);
	if (wet)
		wetuwn wet;

	ctx->common_hdmi_codec_dwv = mach->mach_pawams.common_hdmi_codec_dwv;

	wetuwn devm_snd_soc_wegistew_cawd(&pdev->dev, &bwoxton_audio_cawd);
}

static const stwuct pwatfowm_device_id bxt_boawd_ids[] = {
	{ .name = "bxt_da7219_mx98357a" },
	{ .name = "gwk_da7219_mx98357a" },
	{ .name = "cmw_da7219_mx98357a" },
	{ }
};
MODUWE_DEVICE_TABWE(pwatfowm, bxt_boawd_ids);

static stwuct pwatfowm_dwivew bwoxton_audio = {
	.pwobe = bwoxton_audio_pwobe,
	.dwivew = {
		.name = "bxt_da7219_max98357a",
		.pm = &snd_soc_pm_ops,
	},
	.id_tabwe = bxt_boawd_ids,
};
moduwe_pwatfowm_dwivew(bwoxton_audio)

/* Moduwe infowmation */
MODUWE_DESCWIPTION("Audio Machine dwivew-DA7219 & MAX98357A in I2S mode");
MODUWE_AUTHOW("Sathyanawayana Nujewwa <sathyanawayana.nujewwa@intew.com>");
MODUWE_AUTHOW("Wohit Ainapuwe <wohit.m.ainapuwe@intew.com>");
MODUWE_AUTHOW("Hawsha Pwiya <hawshapwiya.n@intew.com>");
MODUWE_AUTHOW("Conwad Cooke <conwad.cooke@intew.com>");
MODUWE_AUTHOW("Naveen Manohaw <naveen.m@intew.com>");
MODUWE_AUTHOW("Mac Chiang <mac.chiang@intew.com>");
MODUWE_AUTHOW("Bwent Wu <bwent.wu@intew.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(SND_SOC_INTEW_HDA_DSP_COMMON);
