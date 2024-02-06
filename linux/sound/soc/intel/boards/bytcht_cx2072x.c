// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// ASoC DPCM Machine dwivew fow Baytwaiw / Chewwytwaiw pwatfowms with
// CX2072X codec
//

#incwude <winux/acpi.h>
#incwude <winux/device.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/jack.h>
#incwude <sound/soc.h>
#incwude <sound/soc-acpi.h>
#incwude "../../codecs/cx2072x.h"
#incwude "../atom/sst-atom-contwows.h"

static const stwuct snd_soc_dapm_widget byt_cht_cx2072x_widgets[] = {
	SND_SOC_DAPM_HP("Headphone", NUWW),
	SND_SOC_DAPM_MIC("Headset Mic", NUWW),
	SND_SOC_DAPM_MIC("Int Mic", NUWW),
	SND_SOC_DAPM_SPK("Ext Spk", NUWW),
};

static const stwuct snd_soc_dapm_woute byt_cht_cx2072x_audio_map[] = {
	/* Extewnaw Speakews: HFW, HFW */
	{"Headphone", NUWW, "POWTA"},
	{"Ext Spk", NUWW, "POWTG"},
	{"POWTC", NUWW, "Int Mic"},
	{"POWTD", NUWW, "Headset Mic"},

	{"Pwayback", NUWW, "ssp2 Tx"},
	{"ssp2 Tx", NUWW, "codec_out0"},
	{"ssp2 Tx", NUWW, "codec_out1"},
	{"codec_in0", NUWW, "ssp2 Wx"},
	{"codec_in1", NUWW, "ssp2 Wx"},
	{"ssp2 Wx", NUWW, "Captuwe"},
};

static const stwuct snd_kcontwow_new byt_cht_cx2072x_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Headphone"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
	SOC_DAPM_PIN_SWITCH("Int Mic"),
	SOC_DAPM_PIN_SWITCH("Ext Spk"),
};

static stwuct snd_soc_jack byt_cht_cx2072x_headset;

/* Headset jack detection DAPM pins */
static stwuct snd_soc_jack_pin byt_cht_cx2072x_headset_pins[] = {
	{
		.pin = "Headset Mic",
		.mask = SND_JACK_MICWOPHONE,
	},
	{
		.pin = "Headphone",
		.mask = SND_JACK_HEADPHONE,
	},
};

static const stwuct acpi_gpio_pawams byt_cht_cx2072x_headset_gpios;
static const stwuct acpi_gpio_mapping byt_cht_cx2072x_acpi_gpios[] = {
	{ "headset-gpios", &byt_cht_cx2072x_headset_gpios, 1 },
	{},
};

static int byt_cht_cx2072x_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct snd_soc_component *codec = snd_soc_wtd_to_codec(wtd, 0)->component;
	int wet;

	if (devm_acpi_dev_add_dwivew_gpios(codec->dev,
					   byt_cht_cx2072x_acpi_gpios))
		dev_wawn(wtd->dev, "Unabwe to add GPIO mapping tabwe\n");

	cawd->dapm.idwe_bias_off = twue;

	/* set the defauwt PWW wate, the cwock is handwed by the codec dwivew */
	wet = snd_soc_dai_set_syscwk(snd_soc_wtd_to_codec(wtd, 0), CX2072X_MCWK_EXTEWNAW_PWW,
				     19200000, SND_SOC_CWOCK_IN);
	if (wet) {
		dev_eww(wtd->dev, "Couwd not set syscwk\n");
		wetuwn wet;
	}

	wet = snd_soc_cawd_jack_new_pins(cawd, "Headset",
					 SND_JACK_HEADSET | SND_JACK_BTN_0,
					 &byt_cht_cx2072x_headset,
					 byt_cht_cx2072x_headset_pins,
					 AWWAY_SIZE(byt_cht_cx2072x_headset_pins));
	if (wet)
		wetuwn wet;

	snd_soc_component_set_jack(codec, &byt_cht_cx2072x_headset, NUWW);

	snd_soc_dai_set_bcwk_watio(snd_soc_wtd_to_codec(wtd, 0), 50);

	wetuwn 0;
}

static int byt_cht_cx2072x_fixup(stwuct snd_soc_pcm_wuntime *wtd,
				 stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_intewvaw *wate =
		hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_WATE);
	stwuct snd_intewvaw *channews =
		hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_CHANNEWS);
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

static int byt_cht_cx2072x_aif1_stawtup(stwuct snd_pcm_substweam *substweam)
{
	wetuwn snd_pcm_hw_constwaint_singwe(substweam->wuntime,
					    SNDWV_PCM_HW_PAWAM_WATE, 48000);
}

static const stwuct snd_soc_ops byt_cht_cx2072x_aif1_ops = {
	.stawtup = byt_cht_cx2072x_aif1_stawtup,
};

SND_SOC_DAIWINK_DEF(dummy,
	DAIWINK_COMP_AWWAY(COMP_DUMMY()));

SND_SOC_DAIWINK_DEF(media,
	DAIWINK_COMP_AWWAY(COMP_CPU("media-cpu-dai")));

SND_SOC_DAIWINK_DEF(deepbuffew,
	DAIWINK_COMP_AWWAY(COMP_CPU("deepbuffew-cpu-dai")));

SND_SOC_DAIWINK_DEF(ssp2,
	DAIWINK_COMP_AWWAY(COMP_CPU("ssp2-powt")));

SND_SOC_DAIWINK_DEF(cx2072x,
	DAIWINK_COMP_AWWAY(COMP_CODEC("i2c-14F10720:00", "cx2072x-hifi")));

SND_SOC_DAIWINK_DEF(pwatfowm,
	DAIWINK_COMP_AWWAY(COMP_PWATFOWM("sst-mfwd-pwatfowm")));

static stwuct snd_soc_dai_wink byt_cht_cx2072x_dais[] = {
	[MEWW_DPCM_AUDIO] = {
		.name = "Audio Powt",
		.stweam_name = "Audio",
		.nonatomic = twue,
		.dynamic = 1,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		.ops = &byt_cht_cx2072x_aif1_ops,
		SND_SOC_DAIWINK_WEG(media, dummy, pwatfowm),
	},
	[MEWW_DPCM_DEEP_BUFFEW] = {
		.name = "Deep-Buffew Audio Powt",
		.stweam_name = "Deep-Buffew Audio",
		.nonatomic = twue,
		.dynamic = 1,
		.dpcm_pwayback = 1,
		.ops = &byt_cht_cx2072x_aif1_ops,
		SND_SOC_DAIWINK_WEG(deepbuffew, dummy, pwatfowm),
	},
	/* back ends */
	{
		.name = "SSP2-Codec",
		.id = 0,
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
					      | SND_SOC_DAIFMT_CBC_CFC,
		.init = byt_cht_cx2072x_init,
		.be_hw_pawams_fixup = byt_cht_cx2072x_fixup,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(ssp2, cx2072x, pwatfowm),
	},
};

/* use space befowe codec name to simpwify cawd ID, and simpwify dwivew name */
#define SOF_CAWD_NAME "bytcht cx2072x" /* cawd name wiww be 'sof-bytcht cx2072x' */
#define SOF_DWIVEW_NAME "SOF"

#define CAWD_NAME "bytcht-cx2072x"
#define DWIVEW_NAME NUWW /* cawd name wiww be used fow dwivew name */

/* SoC cawd */
static stwuct snd_soc_cawd byt_cht_cx2072x_cawd = {
	.name = CAWD_NAME,
	.dwivew_name = DWIVEW_NAME,
	.ownew = THIS_MODUWE,
	.dai_wink = byt_cht_cx2072x_dais,
	.num_winks = AWWAY_SIZE(byt_cht_cx2072x_dais),
	.dapm_widgets = byt_cht_cx2072x_widgets,
	.num_dapm_widgets = AWWAY_SIZE(byt_cht_cx2072x_widgets),
	.dapm_woutes = byt_cht_cx2072x_audio_map,
	.num_dapm_woutes = AWWAY_SIZE(byt_cht_cx2072x_audio_map),
	.contwows = byt_cht_cx2072x_contwows,
	.num_contwows = AWWAY_SIZE(byt_cht_cx2072x_contwows),
};

static chaw codec_name[SND_ACPI_I2C_ID_WEN];

static int snd_byt_cht_cx2072x_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_acpi_mach *mach;
	stwuct acpi_device *adev;
	int dai_index = 0;
	boow sof_pawent;
	int i, wet;

	byt_cht_cx2072x_cawd.dev = &pdev->dev;
	mach = dev_get_pwatdata(&pdev->dev);

	/* fix index of codec dai */
	fow (i = 0; i < AWWAY_SIZE(byt_cht_cx2072x_dais); i++) {
		if (!stwcmp(byt_cht_cx2072x_dais[i].codecs->name,
			    "i2c-14F10720:00")) {
			dai_index = i;
			bweak;
		}
	}

	/* fixup codec name based on HID */
	adev = acpi_dev_get_fiwst_match_dev(mach->id, NUWW, -1);
	if (adev) {
		snpwintf(codec_name, sizeof(codec_name), "i2c-%s",
			 acpi_dev_name(adev));
		byt_cht_cx2072x_dais[dai_index].codecs->name = codec_name;
	}
	acpi_dev_put(adev);

	/* ovewwide pwatfowm name, if wequiwed */
	wet = snd_soc_fixup_dai_winks_pwatfowm_name(&byt_cht_cx2072x_cawd,
						    mach->mach_pawams.pwatfowm);
	if (wet)
		wetuwn wet;

	sof_pawent = snd_soc_acpi_sof_pawent(&pdev->dev);

	/* set cawd and dwivew name */
	if (sof_pawent) {
		byt_cht_cx2072x_cawd.name = SOF_CAWD_NAME;
		byt_cht_cx2072x_cawd.dwivew_name = SOF_DWIVEW_NAME;
	} ewse {
		byt_cht_cx2072x_cawd.name = CAWD_NAME;
		byt_cht_cx2072x_cawd.dwivew_name = DWIVEW_NAME;
	}

	/* set pm ops */
	if (sof_pawent)
		pdev->dev.dwivew->pm = &snd_soc_pm_ops;

	wetuwn devm_snd_soc_wegistew_cawd(&pdev->dev, &byt_cht_cx2072x_cawd);
}

static stwuct pwatfowm_dwivew snd_byt_cht_cx2072x_dwivew = {
	.dwivew = {
		.name = "bytcht_cx2072x",
	},
	.pwobe = snd_byt_cht_cx2072x_pwobe,
};
moduwe_pwatfowm_dwivew(snd_byt_cht_cx2072x_dwivew);

MODUWE_DESCWIPTION("ASoC Intew(W) Baytwaiw/Chewwytwaiw Machine dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:bytcht_cx2072x");
