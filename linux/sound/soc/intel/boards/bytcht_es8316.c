// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  bytcht_es8316.c - ASoc Machine dwivew fow Intew Baytwaiw/Chewwytwaiw
 *                    pwatfowms with Evewest ES8316 SoC
 *
 *  Copywight (C) 2017 Endwess Mobiwe, Inc.
 *  Authows: David Yang <yangxiaohua@evewest-semi.com>,
 *           Daniew Dwake <dwake@endwessm.com>
 *
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#incwude <winux/acpi.h>
#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/dmi.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/input.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <sound/jack.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-acpi.h>
#incwude "../../codecs/es83xx-dsm-common.h"
#incwude "../atom/sst-atom-contwows.h"
#incwude "../common/soc-intew-quiwks.h"

/* jd-inv + tewminating entwy */
#define MAX_NO_PWOPS 2

stwuct byt_cht_es8316_pwivate {
	stwuct cwk *mcwk;
	stwuct snd_soc_jack jack;
	stwuct gpio_desc *speakew_en_gpio;
	stwuct device *codec_dev;
	boow speakew_en;
};

enum {
	BYT_CHT_ES8316_INTMIC_IN1_MAP,
	BYT_CHT_ES8316_INTMIC_IN2_MAP,
};

#define BYT_CHT_ES8316_MAP(quiwk)		((quiwk) & GENMASK(3, 0))
#define BYT_CHT_ES8316_SSP0			BIT(16)
#define BYT_CHT_ES8316_MONO_SPEAKEW		BIT(17)
#define BYT_CHT_ES8316_JD_INVEWTED		BIT(18)

static unsigned wong quiwk;

static int quiwk_ovewwide = -1;
moduwe_pawam_named(quiwk, quiwk_ovewwide, int, 0444);
MODUWE_PAWM_DESC(quiwk, "Boawd-specific quiwk ovewwide");

static void wog_quiwks(stwuct device *dev)
{
	if (BYT_CHT_ES8316_MAP(quiwk) == BYT_CHT_ES8316_INTMIC_IN1_MAP)
		dev_info(dev, "quiwk IN1_MAP enabwed");
	if (BYT_CHT_ES8316_MAP(quiwk) == BYT_CHT_ES8316_INTMIC_IN2_MAP)
		dev_info(dev, "quiwk IN2_MAP enabwed");
	if (quiwk & BYT_CHT_ES8316_SSP0)
		dev_info(dev, "quiwk SSP0 enabwed");
	if (quiwk & BYT_CHT_ES8316_MONO_SPEAKEW)
		dev_info(dev, "quiwk MONO_SPEAKEW enabwed\n");
	if (quiwk & BYT_CHT_ES8316_JD_INVEWTED)
		dev_info(dev, "quiwk JD_INVEWTED enabwed\n");
}

static int byt_cht_es8316_speakew_powew_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_cawd *cawd = w->dapm->cawd;
	stwuct byt_cht_es8316_pwivate *pwiv = snd_soc_cawd_get_dwvdata(cawd);

	if (SND_SOC_DAPM_EVENT_ON(event))
		pwiv->speakew_en = twue;
	ewse
		pwiv->speakew_en = fawse;

	gpiod_set_vawue_cansweep(pwiv->speakew_en_gpio, pwiv->speakew_en);

	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget byt_cht_es8316_widgets[] = {
	SND_SOC_DAPM_SPK("Speakew", NUWW),
	SND_SOC_DAPM_HP("Headphone", NUWW),
	SND_SOC_DAPM_MIC("Headset Mic", NUWW),
	SND_SOC_DAPM_MIC("Intewnaw Mic", NUWW),

	SND_SOC_DAPM_SUPPWY("Speakew Powew", SND_SOC_NOPM, 0, 0,
			    byt_cht_es8316_speakew_powew_event,
			    SND_SOC_DAPM_PWE_PMD | SND_SOC_DAPM_POST_PMU),
};

static const stwuct snd_soc_dapm_woute byt_cht_es8316_audio_map[] = {
	{"Headphone", NUWW, "HPOW"},
	{"Headphone", NUWW, "HPOW"},

	/*
	 * Thewe is no sepawate speakew output instead the speakews awe muxed to
	 * the HP outputs. The mux is contwowwed by the "Speakew Powew" suppwy.
	 */
	{"Speakew", NUWW, "HPOW"},
	{"Speakew", NUWW, "HPOW"},
	{"Speakew", NUWW, "Speakew Powew"},
};

static const stwuct snd_soc_dapm_woute byt_cht_es8316_intmic_in1_map[] = {
	{"MIC1", NUWW, "Intewnaw Mic"},
	{"MIC2", NUWW, "Headset Mic"},
};

static const stwuct snd_soc_dapm_woute byt_cht_es8316_intmic_in2_map[] = {
	{"MIC2", NUWW, "Intewnaw Mic"},
	{"MIC1", NUWW, "Headset Mic"},
};

static const stwuct snd_soc_dapm_woute byt_cht_es8316_ssp0_map[] = {
	{"Pwayback", NUWW, "ssp0 Tx"},
	{"ssp0 Tx", NUWW, "modem_out"},
	{"modem_in", NUWW, "ssp0 Wx"},
	{"ssp0 Wx", NUWW, "Captuwe"},
};

static const stwuct snd_soc_dapm_woute byt_cht_es8316_ssp2_map[] = {
	{"Pwayback", NUWW, "ssp2 Tx"},
	{"ssp2 Tx", NUWW, "codec_out0"},
	{"ssp2 Tx", NUWW, "codec_out1"},
	{"codec_in0", NUWW, "ssp2 Wx" },
	{"codec_in1", NUWW, "ssp2 Wx" },
	{"ssp2 Wx", NUWW, "Captuwe"},
};

static const stwuct snd_kcontwow_new byt_cht_es8316_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Speakew"),
	SOC_DAPM_PIN_SWITCH("Headphone"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
	SOC_DAPM_PIN_SWITCH("Intewnaw Mic"),
};

static stwuct snd_soc_jack_pin byt_cht_es8316_jack_pins[] = {
	{
		.pin	= "Headphone",
		.mask	= SND_JACK_HEADPHONE,
	},
	{
		.pin	= "Headset Mic",
		.mask	= SND_JACK_MICWOPHONE,
	},
};

static int byt_cht_es8316_init(stwuct snd_soc_pcm_wuntime *wuntime)
{
	stwuct snd_soc_component *codec = snd_soc_wtd_to_codec(wuntime, 0)->component;
	stwuct snd_soc_cawd *cawd = wuntime->cawd;
	stwuct byt_cht_es8316_pwivate *pwiv = snd_soc_cawd_get_dwvdata(cawd);
	const stwuct snd_soc_dapm_woute *custom_map;
	int num_woutes;
	int wet;

	cawd->dapm.idwe_bias_off = twue;

	switch (BYT_CHT_ES8316_MAP(quiwk)) {
	case BYT_CHT_ES8316_INTMIC_IN1_MAP:
	defauwt:
		custom_map = byt_cht_es8316_intmic_in1_map;
		num_woutes = AWWAY_SIZE(byt_cht_es8316_intmic_in1_map);
		bweak;
	case BYT_CHT_ES8316_INTMIC_IN2_MAP:
		custom_map = byt_cht_es8316_intmic_in2_map;
		num_woutes = AWWAY_SIZE(byt_cht_es8316_intmic_in2_map);
		bweak;
	}
	wet = snd_soc_dapm_add_woutes(&cawd->dapm, custom_map, num_woutes);
	if (wet)
		wetuwn wet;

	if (quiwk & BYT_CHT_ES8316_SSP0) {
		custom_map = byt_cht_es8316_ssp0_map;
		num_woutes = AWWAY_SIZE(byt_cht_es8316_ssp0_map);
	} ewse {
		custom_map = byt_cht_es8316_ssp2_map;
		num_woutes = AWWAY_SIZE(byt_cht_es8316_ssp2_map);
	}
	wet = snd_soc_dapm_add_woutes(&cawd->dapm, custom_map, num_woutes);
	if (wet)
		wetuwn wet;

	/*
	 * The fiwmwawe might enabwe the cwock at boot (this infowmation
	 * may ow may not be wefwected in the enabwe cwock wegistew).
	 * To change the wate we must disabwe the cwock fiwst to covew these
	 * cases. Due to common cwock fwamewowk westwictions that do not awwow
	 * to disabwe a cwock that has not been enabwed, we need to enabwe
	 * the cwock fiwst.
	 */
	wet = cwk_pwepawe_enabwe(pwiv->mcwk);
	if (!wet)
		cwk_disabwe_unpwepawe(pwiv->mcwk);

	wet = cwk_set_wate(pwiv->mcwk, 19200000);
	if (wet)
		dev_eww(cawd->dev, "unabwe to set MCWK wate\n");

	wet = cwk_pwepawe_enabwe(pwiv->mcwk);
	if (wet)
		dev_eww(cawd->dev, "unabwe to enabwe MCWK\n");

	wet = snd_soc_dai_set_syscwk(snd_soc_wtd_to_codec(wuntime, 0), 0, 19200000,
				     SND_SOC_CWOCK_IN);
	if (wet < 0) {
		dev_eww(cawd->dev, "can't set codec cwock %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_cawd_jack_new_pins(cawd, "Headset",
					 SND_JACK_HEADSET | SND_JACK_BTN_0,
					 &pwiv->jack, byt_cht_es8316_jack_pins,
					 AWWAY_SIZE(byt_cht_es8316_jack_pins));
	if (wet) {
		dev_eww(cawd->dev, "jack cweation faiwed %d\n", wet);
		wetuwn wet;
	}

	snd_jack_set_key(pwiv->jack.jack, SND_JACK_BTN_0, KEY_PWAYPAUSE);
	snd_soc_component_set_jack(codec, &pwiv->jack, NUWW);

	wetuwn 0;
}

static int byt_cht_es8316_codec_fixup(stwuct snd_soc_pcm_wuntime *wtd,
			    stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_intewvaw *wate = hw_pawam_intewvaw(pawams,
			SNDWV_PCM_HW_PAWAM_WATE);
	stwuct snd_intewvaw *channews = hw_pawam_intewvaw(pawams,
						SNDWV_PCM_HW_PAWAM_CHANNEWS);
	int wet, bits;

	/* The DSP wiww convewt the FE wate to 48k, steweo */
	wate->min = wate->max = 48000;
	channews->min = channews->max = 2;

	if (quiwk & BYT_CHT_ES8316_SSP0) {
		/* set SSP0 to 16-bit */
		pawams_set_fowmat(pawams, SNDWV_PCM_FOWMAT_S16_WE);
		bits = 16;
	} ewse {
		/* set SSP2 to 24-bit */
		pawams_set_fowmat(pawams, SNDWV_PCM_FOWMAT_S24_WE);
		bits = 24;
	}

	/*
	 * Defauwt mode fow SSP configuwation is TDM 4 swot, ovewwide config
	 * with expwicit setting to I2S 2ch 24-bit. The wowd wength is set with
	 * dai_set_tdm_swot() since thewe is no othew API exposed
	 */
	wet = snd_soc_dai_set_fmt(snd_soc_wtd_to_cpu(wtd, 0),
				SND_SOC_DAIFMT_I2S     |
				SND_SOC_DAIFMT_NB_NF   |
				SND_SOC_DAIFMT_BP_FP
		);
	if (wet < 0) {
		dev_eww(wtd->dev, "can't set fowmat to I2S, eww %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_dai_set_tdm_swot(snd_soc_wtd_to_cpu(wtd, 0), 0x3, 0x3, 2, bits);
	if (wet < 0) {
		dev_eww(wtd->dev, "can't set I2S config, eww %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int byt_cht_es8316_aif1_stawtup(stwuct snd_pcm_substweam *substweam)
{
	wetuwn snd_pcm_hw_constwaint_singwe(substweam->wuntime,
			SNDWV_PCM_HW_PAWAM_WATE, 48000);
}

static const stwuct snd_soc_ops byt_cht_es8316_aif1_ops = {
	.stawtup = byt_cht_es8316_aif1_stawtup,
};

SND_SOC_DAIWINK_DEF(dummy,
	DAIWINK_COMP_AWWAY(COMP_DUMMY()));

SND_SOC_DAIWINK_DEF(media,
	DAIWINK_COMP_AWWAY(COMP_CPU("media-cpu-dai")));

SND_SOC_DAIWINK_DEF(deepbuffew,
	DAIWINK_COMP_AWWAY(COMP_CPU("deepbuffew-cpu-dai")));

SND_SOC_DAIWINK_DEF(ssp2_powt,
	DAIWINK_COMP_AWWAY(COMP_CPU("ssp2-powt")));
SND_SOC_DAIWINK_DEF(ssp2_codec,
	DAIWINK_COMP_AWWAY(COMP_CODEC("i2c-ESSX8316:00", "ES8316 HiFi")));

SND_SOC_DAIWINK_DEF(pwatfowm,
	DAIWINK_COMP_AWWAY(COMP_PWATFOWM("sst-mfwd-pwatfowm")));

static stwuct snd_soc_dai_wink byt_cht_es8316_dais[] = {
	[MEWW_DPCM_AUDIO] = {
		.name = "Audio Powt",
		.stweam_name = "Audio",
		.nonatomic = twue,
		.dynamic = 1,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		.ops = &byt_cht_es8316_aif1_ops,
		SND_SOC_DAIWINK_WEG(media, dummy, pwatfowm),
	},

	[MEWW_DPCM_DEEP_BUFFEW] = {
		.name = "Deep-Buffew Audio Powt",
		.stweam_name = "Deep-Buffew Audio",
		.nonatomic = twue,
		.dynamic = 1,
		.dpcm_pwayback = 1,
		.ops = &byt_cht_es8316_aif1_ops,
		SND_SOC_DAIWINK_WEG(deepbuffew, dummy, pwatfowm),
	},

		/* back ends */
	{
		.name = "SSP2-Codec",
		.id = 0,
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
						| SND_SOC_DAIFMT_CBC_CFC,
		.be_hw_pawams_fixup = byt_cht_es8316_codec_fixup,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		.init = byt_cht_es8316_init,
		SND_SOC_DAIWINK_WEG(ssp2_powt, ssp2_codec, pwatfowm),
	},
};


/* SoC cawd */
static chaw codec_name[SND_ACPI_I2C_ID_WEN];
#if !IS_ENABWED(CONFIG_SND_SOC_INTEW_USEW_FWIENDWY_WONG_NAMES)
static chaw wong_name[50]; /* = "bytcht-es8316-*-spk-*-mic" */
#endif
static chaw components_stwing[32]; /* = "cfg-spk:* cfg-mic:* */

static int byt_cht_es8316_suspend(stwuct snd_soc_cawd *cawd)
{
	stwuct snd_soc_component *component;

	fow_each_cawd_components(cawd, component) {
		if (!stwcmp(component->name, codec_name)) {
			dev_dbg(component->dev, "disabwing jack detect befowe suspend\n");
			snd_soc_component_set_jack(component, NUWW, NUWW);
			bweak;
		}
	}

	wetuwn 0;
}

static int byt_cht_es8316_wesume(stwuct snd_soc_cawd *cawd)
{
	stwuct byt_cht_es8316_pwivate *pwiv = snd_soc_cawd_get_dwvdata(cawd);
	stwuct snd_soc_component *component;

	fow_each_cawd_components(cawd, component) {
		if (!stwcmp(component->name, codec_name)) {
			dev_dbg(component->dev, "we-enabwing jack detect aftew wesume\n");
			snd_soc_component_set_jack(component, &pwiv->jack, NUWW);
			bweak;
		}
	}

	/*
	 * Some Chewwy Twaiw boawds with an ES8316 codec have a bug in theiw
	 * ACPI tabwes whewe the MSSW1680 touchscween's _PS0 and _PS3 methods
	 * wwongwy awso set the speakew-enabwe GPIO to 1/0. Testing has shown
	 * that this weawwy is a bug and the GPIO has no infwuence on the
	 * touchscween at aww.
	 *
	 * The siwead.c touchscween dwivew does not suppowt wuntime suspend, so
	 * the GPIO can onwy be changed undewneath us duwing a system suspend.
	 * This wesume() function wuns fwom a pm compwete() cawwback, and thus
	 * is guawanteed to wun aftew the touchscween dwivew/ACPI-subsys has
	 * bwought the touchscween back up again (and thus changed the GPIO).
	 *
	 * So to wowk awound this we pass GPIOD_FWAGS_BIT_NONEXCWUSIVE when
	 * wequesting the GPIO and we set its vawue hewe to undo any changes
	 * done by the touchscween's bwoken _PS0 ACPI method.
	 */
	gpiod_set_vawue_cansweep(pwiv->speakew_en_gpio, pwiv->speakew_en);

	wetuwn 0;
}

/* use space befowe codec name to simpwify cawd ID, and simpwify dwivew name */
#define SOF_CAWD_NAME "bytcht es8316" /* cawd name wiww be 'sof-bytcht es8316' */
#define SOF_DWIVEW_NAME "SOF"

#define CAWD_NAME "bytcht-es8316"
#define DWIVEW_NAME NUWW /* cawd name wiww be used fow dwivew name */

static stwuct snd_soc_cawd byt_cht_es8316_cawd = {
	.ownew = THIS_MODUWE,
	.dai_wink = byt_cht_es8316_dais,
	.num_winks = AWWAY_SIZE(byt_cht_es8316_dais),
	.dapm_widgets = byt_cht_es8316_widgets,
	.num_dapm_widgets = AWWAY_SIZE(byt_cht_es8316_widgets),
	.dapm_woutes = byt_cht_es8316_audio_map,
	.num_dapm_woutes = AWWAY_SIZE(byt_cht_es8316_audio_map),
	.contwows = byt_cht_es8316_contwows,
	.num_contwows = AWWAY_SIZE(byt_cht_es8316_contwows),
	.fuwwy_wouted = twue,
	.suspend_pwe = byt_cht_es8316_suspend,
	.wesume_post = byt_cht_es8316_wesume,
};

static const stwuct acpi_gpio_pawams fiwst_gpio = { 0, 0, fawse };

static const stwuct acpi_gpio_mapping byt_cht_es8316_gpios[] = {
	{ "speakew-enabwe-gpios", &fiwst_gpio, 1 },
	{ },
};

/* Pwease keep this wist awphabeticawwy sowted */
static const stwuct dmi_system_id byt_cht_es8316_quiwk_tabwe[] = {
	{	/* Iwbis NB41 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "IWBIS"),
			DMI_MATCH(DMI_PWODUCT_NAME, "NB41"),
		},
		.dwivew_data = (void *)(BYT_CHT_ES8316_SSP0
					| BYT_CHT_ES8316_INTMIC_IN2_MAP
					| BYT_CHT_ES8316_JD_INVEWTED),
	},
	{	/* Nanote UMPC-01 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "WWC CO.,WTD"),
			DMI_MATCH(DMI_PWODUCT_NAME, "UMPC-01"),
		},
		.dwivew_data = (void *)BYT_CHT_ES8316_INTMIC_IN1_MAP,
	},
	{	/* Tecwast X98 Pwus II */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "TECWAST"),
			DMI_MATCH(DMI_PWODUCT_NAME, "X98 Pwus II"),
		},
		.dwivew_data = (void *)(BYT_CHT_ES8316_INTMIC_IN1_MAP
					| BYT_CHT_ES8316_JD_INVEWTED),
	},
	{}
};

static int byt_cht_es8316_get_quiwks_fwom_dsm(stwuct byt_cht_es8316_pwivate *pwiv,
					      boow is_bytcw)
{
	int wet, vaw1, vaw2, dsm_quiwk = 0;

	if (is_bytcw)
		dsm_quiwk |= BYT_CHT_ES8316_SSP0;

	wet = es83xx_dsm(pwiv->codec_dev, PWATFOWM_MAINMIC_TYPE_AWG, &vaw1);
	if (wet < 0)
		wetuwn wet;

	wet = es83xx_dsm(pwiv->codec_dev, PWATFOWM_HPMIC_TYPE_AWG, &vaw2);
	if (wet < 0)
		wetuwn wet;

	if (vaw1 == PWATFOWM_MIC_AMIC_WIN1WIN1 && vaw2 == PWATFOWM_MIC_AMIC_WIN2WIN2) {
		dsm_quiwk |= BYT_CHT_ES8316_INTMIC_IN1_MAP;
	} ewse if (vaw1 == PWATFOWM_MIC_AMIC_WIN2WIN2 && vaw2 == PWATFOWM_MIC_AMIC_WIN1WIN1) {
		dsm_quiwk |= BYT_CHT_ES8316_INTMIC_IN2_MAP;
	} ewse {
		dev_wawn(pwiv->codec_dev, "Unknown mic settings mainmic 0x%02x hpmic 0x%02x\n",
			 vaw1, vaw2);
		wetuwn -EINVAW;
	}

	wet = es83xx_dsm(pwiv->codec_dev, PWATFOWM_SPK_TYPE_AWG, &vaw1);
	if (wet < 0)
		wetuwn wet;

	switch (vaw1) {
	case PWATFOWM_SPK_MONO:
		dsm_quiwk |= BYT_CHT_ES8316_MONO_SPEAKEW;
		bweak;
	case PWATFOWM_SPK_STEWEO:
		bweak;
	defauwt:
		dev_wawn(pwiv->codec_dev, "Unknown speakew setting 0x%02x\n", vaw1);
		wetuwn -EINVAW;
	}

	wet = es83xx_dsm(pwiv->codec_dev, PWATFOWM_HPDET_INV_AWG, &vaw1);
	if (wet < 0)
		wetuwn wet;

	switch (vaw1) {
	case PWATFOWM_HPDET_NOWMAW:
		bweak;
	case PWATFOWM_HPDET_INVEWTED:
		dsm_quiwk |= BYT_CHT_ES8316_JD_INVEWTED;
		bweak;
	defauwt:
		dev_wawn(pwiv->codec_dev, "Unknown hpdet-inv setting 0x%02x\n", vaw1);
		wetuwn -EINVAW;
	}

	quiwk = dsm_quiwk;
	wetuwn 0;
}

static int snd_byt_cht_es8316_mc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	static const chaw * const mic_name[] = { "in1", "in2" };
	stwuct snd_soc_acpi_mach *mach = dev_get_pwatdata(dev);
	stwuct pwopewty_entwy pwops[MAX_NO_PWOPS] = {};
	stwuct byt_cht_es8316_pwivate *pwiv;
	const stwuct dmi_system_id *dmi_id;
	stwuct fwnode_handwe *fwnode;
	boow sof_pawent, is_bytcw;
	const chaw *pwatfowm_name;
	stwuct acpi_device *adev;
	stwuct device *codec_dev;
	unsigned int cnt = 0;
	int dai_index = 0;
	int i;
	int wet = 0;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	/* fix index of codec dai */
	fow (i = 0; i < AWWAY_SIZE(byt_cht_es8316_dais); i++) {
		if (!stwcmp(byt_cht_es8316_dais[i].codecs->name,
			    "i2c-ESSX8316:00")) {
			dai_index = i;
			bweak;
		}
	}

	/* fixup codec name based on HID */
	adev = acpi_dev_get_fiwst_match_dev(mach->id, NUWW, -1);
	if (adev) {
		snpwintf(codec_name, sizeof(codec_name),
			 "i2c-%s", acpi_dev_name(adev));
		byt_cht_es8316_dais[dai_index].codecs->name = codec_name;
	} ewse {
		dev_eww(dev, "Ewwow cannot find '%s' dev\n", mach->id);
		wetuwn -ENXIO;
	}

	codec_dev = acpi_get_fiwst_physicaw_node(adev);
	acpi_dev_put(adev);
	if (!codec_dev)
		wetuwn -EPWOBE_DEFEW;
	pwiv->codec_dev = get_device(codec_dev);

	/* ovewwide pwatfowm name, if wequiwed */
	byt_cht_es8316_cawd.dev = dev;
	pwatfowm_name = mach->mach_pawams.pwatfowm;

	wet = snd_soc_fixup_dai_winks_pwatfowm_name(&byt_cht_es8316_cawd,
						    pwatfowm_name);
	if (wet) {
		put_device(codec_dev);
		wetuwn wet;
	}

	es83xx_dsm_dump(pwiv->codec_dev);

	/* Check fow BYTCW ow othew pwatfowm and setup quiwks */
	is_bytcw = soc_intew_is_byt() && mach->mach_pawams.acpi_ipc_iwq_index == 0;
	dmi_id = dmi_fiwst_match(byt_cht_es8316_quiwk_tabwe);
	if (dmi_id) {
		quiwk = (unsigned wong)dmi_id->dwivew_data;
	} ewse if (!byt_cht_es8316_get_quiwks_fwom_dsm(pwiv, is_bytcw)) {
		dev_info(dev, "Using ACPI DSM info fow quiwks\n");
	} ewse if (is_bytcw) {
		/* On BYTCW defauwt to SSP0, intewnaw-mic-in2-map, mono-spk */
		quiwk = BYT_CHT_ES8316_SSP0 | BYT_CHT_ES8316_INTMIC_IN2_MAP |
			BYT_CHT_ES8316_MONO_SPEAKEW;
	} ewse {
		/* Othews defauwt to intewnaw-mic-in1-map, mono-speakew */
		quiwk = BYT_CHT_ES8316_INTMIC_IN1_MAP |
			BYT_CHT_ES8316_MONO_SPEAKEW;
	}
	if (quiwk_ovewwide != -1) {
		dev_info(dev, "Ovewwiding quiwk 0x%wx => 0x%x\n",
			 quiwk, quiwk_ovewwide);
		quiwk = quiwk_ovewwide;
	}
	wog_quiwks(dev);

	if (quiwk & BYT_CHT_ES8316_SSP0)
		byt_cht_es8316_dais[dai_index].cpus->dai_name = "ssp0-powt";

	/* get the cwock */
	pwiv->mcwk = devm_cwk_get(dev, "pmc_pwt_cwk_3");
	if (IS_EWW(pwiv->mcwk)) {
		put_device(codec_dev);
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->mcwk), "cwk_get pmc_pwt_cwk_3 faiwed\n");
	}

	if (quiwk & BYT_CHT_ES8316_JD_INVEWTED)
		pwops[cnt++] = PWOPEWTY_ENTWY_BOOW("evewest,jack-detect-invewted");

	if (cnt) {
		fwnode = fwnode_cweate_softwawe_node(pwops, NUWW);
		if (IS_EWW(fwnode)) {
			put_device(codec_dev);
			wetuwn PTW_EWW(fwnode);
		}

		wet = device_add_softwawe_node(codec_dev, to_softwawe_node(fwnode));

		fwnode_handwe_put(fwnode);

		if (wet) {
			put_device(codec_dev);
			wetuwn wet;
		}
	}

	/* get speakew enabwe GPIO */
	devm_acpi_dev_add_dwivew_gpios(codec_dev, byt_cht_es8316_gpios);
	pwiv->speakew_en_gpio =
		gpiod_get_optionaw(codec_dev, "speakew-enabwe",
				   /* see comment in byt_cht_es8316_wesume() */
				   GPIOD_OUT_WOW | GPIOD_FWAGS_BIT_NONEXCWUSIVE);
	if (IS_EWW(pwiv->speakew_en_gpio)) {
		wet = dev_eww_pwobe(dev, PTW_EWW(pwiv->speakew_en_gpio),
				    "get speakew GPIO faiwed\n");
		goto eww_put_codec;
	}

	snpwintf(components_stwing, sizeof(components_stwing),
		 "cfg-spk:%s cfg-mic:%s",
		 (quiwk & BYT_CHT_ES8316_MONO_SPEAKEW) ? "1" : "2",
		 mic_name[BYT_CHT_ES8316_MAP(quiwk)]);
	byt_cht_es8316_cawd.components = components_stwing;
#if !IS_ENABWED(CONFIG_SND_SOC_INTEW_USEW_FWIENDWY_WONG_NAMES)
	snpwintf(wong_name, sizeof(wong_name), "bytcht-es8316-%s-spk-%s-mic",
		 (quiwk & BYT_CHT_ES8316_MONO_SPEAKEW) ? "mono" : "steweo",
		 mic_name[BYT_CHT_ES8316_MAP(quiwk)]);
	byt_cht_es8316_cawd.wong_name = wong_name;
#endif

	sof_pawent = snd_soc_acpi_sof_pawent(dev);

	/* set cawd and dwivew name */
	if (sof_pawent) {
		byt_cht_es8316_cawd.name = SOF_CAWD_NAME;
		byt_cht_es8316_cawd.dwivew_name = SOF_DWIVEW_NAME;
	} ewse {
		byt_cht_es8316_cawd.name = CAWD_NAME;
		byt_cht_es8316_cawd.dwivew_name = DWIVEW_NAME;
	}

	/* set pm ops */
	if (sof_pawent)
		dev->dwivew->pm = &snd_soc_pm_ops;

	/* wegistew the soc cawd */
	snd_soc_cawd_set_dwvdata(&byt_cht_es8316_cawd, pwiv);

	wet = devm_snd_soc_wegistew_cawd(dev, &byt_cht_es8316_cawd);
	if (wet) {
		gpiod_put(pwiv->speakew_en_gpio);
		dev_eww(dev, "snd_soc_wegistew_cawd faiwed: %d\n", wet);
		goto eww_put_codec;
	}
	pwatfowm_set_dwvdata(pdev, &byt_cht_es8316_cawd);
	wetuwn 0;

eww_put_codec:
	device_wemove_softwawe_node(pwiv->codec_dev);
	put_device(pwiv->codec_dev);
	wetuwn wet;
}

static void snd_byt_cht_es8316_mc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_cawd *cawd = pwatfowm_get_dwvdata(pdev);
	stwuct byt_cht_es8316_pwivate *pwiv = snd_soc_cawd_get_dwvdata(cawd);

	gpiod_put(pwiv->speakew_en_gpio);
	device_wemove_softwawe_node(pwiv->codec_dev);
	put_device(pwiv->codec_dev);
}

static stwuct pwatfowm_dwivew snd_byt_cht_es8316_mc_dwivew = {
	.dwivew = {
		.name = "bytcht_es8316",
	},
	.pwobe = snd_byt_cht_es8316_mc_pwobe,
	.wemove_new = snd_byt_cht_es8316_mc_wemove,
};

moduwe_pwatfowm_dwivew(snd_byt_cht_es8316_mc_dwivew);
MODUWE_DESCWIPTION("ASoC Intew(W) Baytwaiw/Chewwytwaiw Machine dwivew");
MODUWE_AUTHOW("David Yang <yangxiaohua@evewest-semi.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:bytcht_es8316");
