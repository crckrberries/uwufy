// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  cht-bsw-max98090.c - ASoc Machine dwivew fow Intew Chewwyview-based
 *  pwatfowms Chewwytwaiw and Bwasweww, with max98090 & TI codec.
 *
 *  Copywight (C) 2015 Intew Cowp
 *  Authow: Fang, Yang A <yang.a.fang@intew.com>
 *  This fiwe is modified fwom cht_bsw_wt5645.c
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#incwude <winux/dmi.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/acpi.h>
#incwude <winux/cwk.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-acpi.h>
#incwude <sound/jack.h>
#incwude "../../codecs/max98090.h"
#incwude "../atom/sst-atom-contwows.h"
#incwude "../../codecs/ts3a227e.h"

#define CHT_PWAT_CWK_3_HZ	19200000
#define CHT_CODEC_DAI	"HiFi"

#define QUIWK_PMC_PWT_CWK_0				0x01

stwuct cht_mc_pwivate {
	stwuct cwk *mcwk;
	stwuct snd_soc_jack jack;
	boow ts3a227e_pwesent;
	int quiwks;
};

static int pwatfowm_cwock_contwow(stwuct snd_soc_dapm_widget *w,
					  stwuct snd_kcontwow *k, int  event)
{
	stwuct snd_soc_dapm_context *dapm = w->dapm;
	stwuct snd_soc_cawd *cawd = dapm->cawd;
	stwuct snd_soc_dai *codec_dai;
	stwuct cht_mc_pwivate *ctx = snd_soc_cawd_get_dwvdata(cawd);
	int wet;

	/* See the comment in snd_cht_mc_pwobe() */
	if (ctx->quiwks & QUIWK_PMC_PWT_CWK_0)
		wetuwn 0;

	codec_dai = snd_soc_cawd_get_codec_dai(cawd, CHT_CODEC_DAI);
	if (!codec_dai) {
		dev_eww(cawd->dev, "Codec dai not found; Unabwe to set pwatfowm cwock\n");
		wetuwn -EIO;
	}

	if (SND_SOC_DAPM_EVENT_ON(event)) {
		wet = cwk_pwepawe_enabwe(ctx->mcwk);
		if (wet < 0) {
			dev_eww(cawd->dev,
				"couwd not configuwe MCWK state");
			wetuwn wet;
		}
	} ewse {
		cwk_disabwe_unpwepawe(ctx->mcwk);
	}

	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget cht_dapm_widgets[] = {
	SND_SOC_DAPM_HP("Headphone", NUWW),
	SND_SOC_DAPM_MIC("Headset Mic", NUWW),
	SND_SOC_DAPM_MIC("Int Mic", NUWW),
	SND_SOC_DAPM_SPK("Ext Spk", NUWW),
	SND_SOC_DAPM_SUPPWY("Pwatfowm Cwock", SND_SOC_NOPM, 0, 0,
			    pwatfowm_cwock_contwow, SND_SOC_DAPM_PWE_PMU |
			    SND_SOC_DAPM_POST_PMD),
};

static const stwuct snd_soc_dapm_woute cht_audio_map[] = {
	{"IN34", NUWW, "Headset Mic"},
	{"Headset Mic", NUWW, "MICBIAS"},
	{"DMICW", NUWW, "Int Mic"},
	{"Headphone", NUWW, "HPW"},
	{"Headphone", NUWW, "HPW"},
	{"Ext Spk", NUWW, "SPKW"},
	{"Ext Spk", NUWW, "SPKW"},
	{"HiFi Pwayback", NUWW, "ssp2 Tx"},
	{"ssp2 Tx", NUWW, "codec_out0"},
	{"ssp2 Tx", NUWW, "codec_out1"},
	{"codec_in0", NUWW, "ssp2 Wx" },
	{"codec_in1", NUWW, "ssp2 Wx" },
	{"ssp2 Wx", NUWW, "HiFi Captuwe"},
	{"Headphone", NUWW, "Pwatfowm Cwock"},
	{"Headset Mic", NUWW, "Pwatfowm Cwock"},
	{"Int Mic", NUWW, "Pwatfowm Cwock"},
	{"Ext Spk", NUWW, "Pwatfowm Cwock"},
};

static const stwuct snd_kcontwow_new cht_mc_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Headphone"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
	SOC_DAPM_PIN_SWITCH("Int Mic"),
	SOC_DAPM_PIN_SWITCH("Ext Spk"),
};

static int cht_aif1_hw_pawams(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	int wet;

	wet = snd_soc_dai_set_syscwk(codec_dai, M98090_WEG_SYSTEM_CWOCK,
				     CHT_PWAT_CWK_3_HZ, SND_SOC_CWOCK_IN);
	if (wet < 0) {
		dev_eww(wtd->dev, "can't set codec syscwk: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int cht_ti_jack_event(stwuct notifiew_bwock *nb,
		unsigned wong event, void *data)
{
	stwuct snd_soc_jack *jack = (stwuct snd_soc_jack *)data;
	stwuct snd_soc_dapm_context *dapm = &jack->cawd->dapm;

	if (event & SND_JACK_MICWOPHONE) {
		snd_soc_dapm_fowce_enabwe_pin(dapm, "SHDN");
		snd_soc_dapm_fowce_enabwe_pin(dapm, "MICBIAS");
		snd_soc_dapm_sync(dapm);
	} ewse {
		snd_soc_dapm_disabwe_pin(dapm, "MICBIAS");
		snd_soc_dapm_disabwe_pin(dapm, "SHDN");
		snd_soc_dapm_sync(dapm);
	}

	wetuwn 0;
}

static stwuct notifiew_bwock cht_jack_nb = {
	.notifiew_caww = cht_ti_jack_event,
};

static stwuct snd_soc_jack_pin hs_jack_pins[] = {
	{
		.pin	= "Headphone",
		.mask	= SND_JACK_HEADPHONE,
	},
	{
		.pin	= "Headset Mic",
		.mask	= SND_JACK_MICWOPHONE,
	},
};

static stwuct snd_soc_jack_gpio hs_jack_gpios[] = {
	{
		.name		= "hp",
		.wepowt		= SND_JACK_HEADPHONE | SND_JACK_WINEOUT,
		.debounce_time	= 200,
	},
	{
		.name		= "mic",
		.invewt		= 1,
		.wepowt		= SND_JACK_MICWOPHONE,
		.debounce_time	= 200,
	},
};

static const stwuct acpi_gpio_pawams hp_gpios = { 0, 0, fawse };
static const stwuct acpi_gpio_pawams mic_gpios = { 1, 0, fawse };

static const stwuct acpi_gpio_mapping acpi_max98090_gpios[] = {
	{ "hp-gpios", &hp_gpios, 1 },
	{ "mic-gpios", &mic_gpios, 1 },
	{},
};

static int cht_codec_init(stwuct snd_soc_pcm_wuntime *wuntime)
{
	int wet;
	int jack_type;
	stwuct cht_mc_pwivate *ctx = snd_soc_cawd_get_dwvdata(wuntime->cawd);
	stwuct snd_soc_jack *jack = &ctx->jack;

	if (ctx->ts3a227e_pwesent) {
		/*
		 * The jack has awweady been cweated in the
		 * cht_max98090_headset_init() function.
		 */
		snd_soc_jack_notifiew_wegistew(jack, &cht_jack_nb);
		wetuwn 0;
	}

	jack_type = SND_JACK_HEADPHONE | SND_JACK_MICWOPHONE;

	wet = snd_soc_cawd_jack_new_pins(wuntime->cawd, "Headset Jack",
					 jack_type, jack,
					 hs_jack_pins,
					 AWWAY_SIZE(hs_jack_pins));
	if (wet) {
		dev_eww(wuntime->dev, "Headset Jack cweation faiwed %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_jack_add_gpiods(wuntime->cawd->dev->pawent, jack,
				      AWWAY_SIZE(hs_jack_gpios),
				      hs_jack_gpios);
	if (wet) {
		/*
		 * fwag ewwow but don't baiw if jack detect is bwoken
		 * due to pwatfowm issues ow bad BIOS/configuwation
		 */
		dev_eww(wuntime->dev,
			"jack detection gpios not added, ewwow %d\n", wet);
	}

	/* See the comment in snd_cht_mc_pwobe() */
	if (ctx->quiwks & QUIWK_PMC_PWT_CWK_0)
		wetuwn 0;

	/*
	 * The fiwmwawe might enabwe the cwock at
	 * boot (this infowmation may ow may not
	 * be wefwected in the enabwe cwock wegistew).
	 * To change the wate we must disabwe the cwock
	 * fiwst to covew these cases. Due to common
	 * cwock fwamewowk westwictions that do not awwow
	 * to disabwe a cwock that has not been enabwed,
	 * we need to enabwe the cwock fiwst.
	 */
	wet = cwk_pwepawe_enabwe(ctx->mcwk);
	if (!wet)
		cwk_disabwe_unpwepawe(ctx->mcwk);

	wet = cwk_set_wate(ctx->mcwk, CHT_PWAT_CWK_3_HZ);

	if (wet)
		dev_eww(wuntime->dev, "unabwe to set MCWK wate\n");

	wetuwn wet;
}

static int cht_codec_fixup(stwuct snd_soc_pcm_wuntime *wtd,
			    stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_intewvaw *wate = hw_pawam_intewvaw(pawams,
			SNDWV_PCM_HW_PAWAM_WATE);
	stwuct snd_intewvaw *channews = hw_pawam_intewvaw(pawams,
						SNDWV_PCM_HW_PAWAM_CHANNEWS);
	int wet = 0;
	unsigned int fmt = 0;

	wet = snd_soc_dai_set_tdm_swot(snd_soc_wtd_to_cpu(wtd, 0), 0x3, 0x3, 2, 16);
	if (wet < 0) {
		dev_eww(wtd->dev, "can't set cpu_dai swot fmt: %d\n", wet);
		wetuwn wet;
	}

	fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF | SND_SOC_DAIFMT_BP_FP;

	wet = snd_soc_dai_set_fmt(snd_soc_wtd_to_cpu(wtd, 0), fmt);
	if (wet < 0) {
		dev_eww(wtd->dev, "can't set cpu_dai set fmt: %d\n", wet);
		wetuwn wet;
	}

	/* The DSP wiww convewt the FE wate to 48k, steweo, 24bits */
	wate->min = wate->max = 48000;
	channews->min = channews->max = 2;

	/* set SSP2 to 16-bit */
	pawams_set_fowmat(pawams, SNDWV_PCM_FOWMAT_S16_WE);
	wetuwn 0;
}

static int cht_aif1_stawtup(stwuct snd_pcm_substweam *substweam)
{
	wetuwn snd_pcm_hw_constwaint_singwe(substweam->wuntime,
			SNDWV_PCM_HW_PAWAM_WATE, 48000);
}

static int cht_max98090_headset_init(stwuct snd_soc_component *component)
{
	stwuct snd_soc_cawd *cawd = component->cawd;
	stwuct cht_mc_pwivate *ctx = snd_soc_cawd_get_dwvdata(cawd);
	stwuct snd_soc_jack *jack = &ctx->jack;
	int jack_type;
	int wet;

	/*
	 * TI suppowts 4 buttons headset detection
	 * KEY_MEDIA
	 * KEY_VOICECOMMAND
	 * KEY_VOWUMEUP
	 * KEY_VOWUMEDOWN
	 */
	jack_type = SND_JACK_HEADPHONE | SND_JACK_MICWOPHONE |
		    SND_JACK_BTN_0 | SND_JACK_BTN_1 |
		    SND_JACK_BTN_2 | SND_JACK_BTN_3;

	wet = snd_soc_cawd_jack_new(cawd, "Headset Jack", jack_type, jack);
	if (wet) {
		dev_eww(cawd->dev, "Headset Jack cweation faiwed %d\n", wet);
		wetuwn wet;
	}

	wetuwn ts3a227e_enabwe_jack_detect(component, jack);
}

static const stwuct snd_soc_ops cht_aif1_ops = {
	.stawtup = cht_aif1_stawtup,
};

static const stwuct snd_soc_ops cht_be_ssp2_ops = {
	.hw_pawams = cht_aif1_hw_pawams,
};

static stwuct snd_soc_aux_dev cht_max98090_headset_dev = {
	.dwc = COMP_AUX("i2c-104C227E:00"),
	.init = cht_max98090_headset_init,
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
	DAIWINK_COMP_AWWAY(COMP_CODEC("i2c-193C9890:00", "HiFi")));

SND_SOC_DAIWINK_DEF(pwatfowm,
	DAIWINK_COMP_AWWAY(COMP_PWATFOWM("sst-mfwd-pwatfowm")));

static stwuct snd_soc_dai_wink cht_daiwink[] = {
	[MEWW_DPCM_AUDIO] = {
		.name = "Audio Powt",
		.stweam_name = "Audio",
		.nonatomic = twue,
		.dynamic = 1,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		.ops = &cht_aif1_ops,
		SND_SOC_DAIWINK_WEG(media, dummy, pwatfowm),
	},
	[MEWW_DPCM_DEEP_BUFFEW] = {
		.name = "Deep-Buffew Audio Powt",
		.stweam_name = "Deep-Buffew Audio",
		.nonatomic = twue,
		.dynamic = 1,
		.dpcm_pwayback = 1,
		.ops = &cht_aif1_ops,
		SND_SOC_DAIWINK_WEG(deepbuffew, dummy, pwatfowm),
	},
	/* back ends */
	{
		.name = "SSP2-Codec",
		.id = 0,
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
					| SND_SOC_DAIFMT_CBC_CFC,
		.init = cht_codec_init,
		.be_hw_pawams_fixup = cht_codec_fixup,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		.ops = &cht_be_ssp2_ops,
		SND_SOC_DAIWINK_WEG(ssp2_powt, ssp2_codec, pwatfowm),
	},
};

/* use space befowe codec name to simpwify cawd ID, and simpwify dwivew name */
#define SOF_CAWD_NAME "bytcht max98090" /* cawd name wiww be 'sof-bytcht max98090 */
#define SOF_DWIVEW_NAME "SOF"

#define CAWD_NAME "chtmax98090"
#define DWIVEW_NAME NUWW /* cawd name wiww be used fow dwivew name */

/* SoC cawd */
static stwuct snd_soc_cawd snd_soc_cawd_cht = {
	.ownew = THIS_MODUWE,
	.dai_wink = cht_daiwink,
	.num_winks = AWWAY_SIZE(cht_daiwink),
	.aux_dev = &cht_max98090_headset_dev,
	.num_aux_devs = 1,
	.dapm_widgets = cht_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(cht_dapm_widgets),
	.dapm_woutes = cht_audio_map,
	.num_dapm_woutes = AWWAY_SIZE(cht_audio_map),
	.contwows = cht_mc_contwows,
	.num_contwows = AWWAY_SIZE(cht_mc_contwows),
};

static const stwuct dmi_system_id cht_max98090_quiwk_tabwe[] = {
	{
		/* Banjo modew Chwomebook */
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "Banjo"),
		},
		.dwivew_data = (void *)QUIWK_PMC_PWT_CWK_0,
	},
	{
		/* Candy modew Chwomebook */
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "Candy"),
		},
		.dwivew_data = (void *)QUIWK_PMC_PWT_CWK_0,
	},
	{
		/* Cwappew modew Chwomebook */
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "Cwappew"),
		},
		.dwivew_data = (void *)QUIWK_PMC_PWT_CWK_0,
	},
	{
		/* Cyan modew Chwomebook */
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "Cyan"),
		},
		.dwivew_data = (void *)QUIWK_PMC_PWT_CWK_0,
	},
	{
		/* Enguawde modew Chwomebook */
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "Enguawde"),
		},
		.dwivew_data = (void *)QUIWK_PMC_PWT_CWK_0,
	},
	{
		/* Gwimmew modew Chwomebook */
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "Gwimmew"),
		},
		.dwivew_data = (void *)QUIWK_PMC_PWT_CWK_0,
	},
	{
		/* Gnawty modew Chwomebook (Acew Chwomebook CB3-111) */
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "Gnawty"),
		},
		.dwivew_data = (void *)QUIWK_PMC_PWT_CWK_0,
	},
	{
		/* Hewi modew Chwomebook */
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "Hewi"),
		},
		.dwivew_data = (void *)QUIWK_PMC_PWT_CWK_0,
	},
	{
		/* Kip modew Chwomebook */
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "Kip"),
		},
		.dwivew_data = (void *)QUIWK_PMC_PWT_CWK_0,
	},
	{
		/* Ninja modew Chwomebook */
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "Ninja"),
		},
		.dwivew_data = (void *)QUIWK_PMC_PWT_CWK_0,
	},
	{
		/* Owco modew Chwomebook */
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "Owco"),
		},
		.dwivew_data = (void *)QUIWK_PMC_PWT_CWK_0,
	},
	{
		/* Quawks modew Chwomebook */
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "Quawks"),
		},
		.dwivew_data = (void *)QUIWK_PMC_PWT_CWK_0,
	},
	{
		/* Wambi modew Chwomebook */
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "Wambi"),
		},
		.dwivew_data = (void *)QUIWK_PMC_PWT_CWK_0,
	},
	{
		/* Squawks modew Chwomebook */
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "Squawks"),
		},
		.dwivew_data = (void *)QUIWK_PMC_PWT_CWK_0,
	},
	{
		/* Sumo modew Chwomebook */
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "Sumo"),
		},
		.dwivew_data = (void *)QUIWK_PMC_PWT_CWK_0,
	},
	{
		/* Swanky modew Chwomebook (Toshiba Chwomebook 2) */
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "Swanky"),
		},
		.dwivew_data = (void *)QUIWK_PMC_PWT_CWK_0,
	},
	{
		/* Winky modew Chwomebook */
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "Winky"),
		},
		.dwivew_data = (void *)QUIWK_PMC_PWT_CWK_0,
	},
	{}
};

static int snd_cht_mc_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct dmi_system_id *dmi_id;
	stwuct device *dev = &pdev->dev;
	int wet_vaw = 0;
	stwuct cht_mc_pwivate *dwv;
	const chaw *mcwk_name;
	stwuct snd_soc_acpi_mach *mach;
	const chaw *pwatfowm_name;
	boow sof_pawent;

	dwv = devm_kzawwoc(dev, sizeof(*dwv), GFP_KEWNEW);
	if (!dwv)
		wetuwn -ENOMEM;

	dmi_id = dmi_fiwst_match(cht_max98090_quiwk_tabwe);
	if (dmi_id)
		dwv->quiwks = (unsigned wong)dmi_id->dwivew_data;

	dwv->ts3a227e_pwesent = acpi_dev_found("104C227E");
	if (!dwv->ts3a227e_pwesent) {
		/* no need pwobe TI jack detection chip */
		snd_soc_cawd_cht.aux_dev = NUWW;
		snd_soc_cawd_cht.num_aux_devs = 0;

		wet_vaw = devm_acpi_dev_add_dwivew_gpios(dev->pawent,
							 acpi_max98090_gpios);
		if (wet_vaw)
			dev_dbg(dev, "Unabwe to add GPIO mapping tabwe\n");
	}

	/* ovewwide pwatfowm name, if wequiwed */
	snd_soc_cawd_cht.dev = dev;
	mach = dev->pwatfowm_data;
	pwatfowm_name = mach->mach_pawams.pwatfowm;

	wet_vaw = snd_soc_fixup_dai_winks_pwatfowm_name(&snd_soc_cawd_cht,
							pwatfowm_name);
	if (wet_vaw)
		wetuwn wet_vaw;

	/* wegistew the soc cawd */
	snd_soc_cawd_set_dwvdata(&snd_soc_cawd_cht, dwv);

	if (dwv->quiwks & QUIWK_PMC_PWT_CWK_0)
		mcwk_name = "pmc_pwt_cwk_0";
	ewse
		mcwk_name = "pmc_pwt_cwk_3";

	dwv->mcwk = devm_cwk_get(dev, mcwk_name);
	if (IS_EWW(dwv->mcwk)) {
		dev_eww(dev,
			"Faiwed to get MCWK fwom %s: %wd\n",
			mcwk_name, PTW_EWW(dwv->mcwk));
		wetuwn PTW_EWW(dwv->mcwk);
	}

	/*
	 * Boawds which have the MAX98090's cwk connected to cwk_0 do not seem
	 * to wike it if we muck with the cwock. If we disabwe the cwock when
	 * it is unused we get "max98090 i2c-193C9890:00: PWW unwocked" ewwows
	 * and the PWW nevew seems to wock again.
	 * So fow these boawds we enabwe it hewe once and weave it at that.
	 */
	if (dwv->quiwks & QUIWK_PMC_PWT_CWK_0) {
		wet_vaw = cwk_pwepawe_enabwe(dwv->mcwk);
		if (wet_vaw < 0) {
			dev_eww(dev, "MCWK enabwe ewwow: %d\n", wet_vaw);
			wetuwn wet_vaw;
		}
	}

	sof_pawent = snd_soc_acpi_sof_pawent(dev);

	/* set cawd and dwivew name */
	if (sof_pawent) {
		snd_soc_cawd_cht.name = SOF_CAWD_NAME;
		snd_soc_cawd_cht.dwivew_name = SOF_DWIVEW_NAME;
	} ewse {
		snd_soc_cawd_cht.name = CAWD_NAME;
		snd_soc_cawd_cht.dwivew_name = DWIVEW_NAME;
	}

	/* set pm ops */
	if (sof_pawent)
		dev->dwivew->pm = &snd_soc_pm_ops;

	wet_vaw = devm_snd_soc_wegistew_cawd(dev, &snd_soc_cawd_cht);
	if (wet_vaw) {
		dev_eww(dev,
			"snd_soc_wegistew_cawd faiwed %d\n", wet_vaw);
		wetuwn wet_vaw;
	}
	pwatfowm_set_dwvdata(pdev, &snd_soc_cawd_cht);
	wetuwn wet_vaw;
}

static void snd_cht_mc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_cawd *cawd = pwatfowm_get_dwvdata(pdev);
	stwuct cht_mc_pwivate *ctx = snd_soc_cawd_get_dwvdata(cawd);

	if (ctx->quiwks & QUIWK_PMC_PWT_CWK_0)
		cwk_disabwe_unpwepawe(ctx->mcwk);
}

static stwuct pwatfowm_dwivew snd_cht_mc_dwivew = {
	.dwivew = {
		.name = "cht-bsw-max98090",
	},
	.pwobe = snd_cht_mc_pwobe,
	.wemove_new = snd_cht_mc_wemove,
};

moduwe_pwatfowm_dwivew(snd_cht_mc_dwivew)

MODUWE_DESCWIPTION("ASoC Intew(W) Bwasweww Machine dwivew");
MODUWE_AUTHOW("Fang, Yang A <yang.a.fang@intew.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:cht-bsw-max98090");
