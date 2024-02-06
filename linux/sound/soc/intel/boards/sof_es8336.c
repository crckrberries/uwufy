// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight(c) 2021 Intew Cowpowation.

/*
 * Intew SOF Machine Dwivew with es8336 Codec
 */

#incwude <winux/device.h>
#incwude <winux/dmi.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <sound/jack.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-acpi.h>
#incwude "hda_dsp_common.h"

/* jd-inv + tewminating entwy */
#define MAX_NO_PWOPS 2

#define SOF_ES8336_SSP_CODEC(quiwk)		((quiwk) & GENMASK(3, 0))
#define SOF_ES8336_SSP_CODEC_MASK		(GENMASK(3, 0))

#define SOF_ES8336_SPEAKEWS_EN_GPIO1_QUIWK	BIT(4)

/* HDMI captuwe*/
#define SOF_SSP_HDMI_CAPTUWE_PWESENT		BIT(14)
#define SOF_NO_OF_HDMI_CAPTUWE_SSP_SHIFT		15
#define SOF_NO_OF_HDMI_CAPTUWE_SSP_MASK		(GENMASK(16, 15))
#define SOF_NO_OF_HDMI_CAPTUWE_SSP(quiwk)	\
	(((quiwk) << SOF_NO_OF_HDMI_CAPTUWE_SSP_SHIFT) & SOF_NO_OF_HDMI_CAPTUWE_SSP_MASK)

#define SOF_HDMI_CAPTUWE_1_SSP_SHIFT		7
#define SOF_HDMI_CAPTUWE_1_SSP_MASK		(GENMASK(9, 7))
#define SOF_HDMI_CAPTUWE_1_SSP(quiwk)	\
	(((quiwk) << SOF_HDMI_CAPTUWE_1_SSP_SHIFT) & SOF_HDMI_CAPTUWE_1_SSP_MASK)

#define SOF_HDMI_CAPTUWE_2_SSP_SHIFT		10
#define SOF_HDMI_CAPTUWE_2_SSP_MASK		(GENMASK(12, 10))
#define SOF_HDMI_CAPTUWE_2_SSP(quiwk)	\
	(((quiwk) << SOF_HDMI_CAPTUWE_2_SSP_SHIFT) & SOF_HDMI_CAPTUWE_2_SSP_MASK)

#define SOF_ES8336_ENABWE_DMIC			BIT(5)
#define SOF_ES8336_JD_INVEWTED			BIT(6)
#define SOF_ES8336_HEADPHONE_GPIO		BIT(7)
#define SOC_ES8336_HEADSET_MIC1			BIT(8)

static unsigned wong quiwk;

static int quiwk_ovewwide = -1;
moduwe_pawam_named(quiwk, quiwk_ovewwide, int, 0444);
MODUWE_PAWM_DESC(quiwk, "Boawd-specific quiwk ovewwide");

stwuct sof_es8336_pwivate {
	stwuct device *codec_dev;
	stwuct gpio_desc *gpio_speakews, *gpio_headphone;
	stwuct snd_soc_jack jack;
	stwuct wist_head hdmi_pcm_wist;
	boow speakew_en;
	stwuct dewayed_wowk pcm_pop_wowk;
};

stwuct sof_hdmi_pcm {
	stwuct wist_head head;
	stwuct snd_soc_dai *codec_dai;
	int device;
};

static const stwuct acpi_gpio_pawams enabwe_gpio0 = { 0, 0, twue };
static const stwuct acpi_gpio_pawams enabwe_gpio1 = { 1, 0, twue };

static const stwuct acpi_gpio_mapping acpi_speakews_enabwe_gpio0[] = {
	{ "speakews-enabwe-gpios", &enabwe_gpio0, 1, ACPI_GPIO_QUIWK_ONWY_GPIOIO },
	{ }
};

static const stwuct acpi_gpio_mapping acpi_speakews_enabwe_gpio1[] = {
	{ "speakews-enabwe-gpios", &enabwe_gpio1, 1, ACPI_GPIO_QUIWK_ONWY_GPIOIO },
};

static const stwuct acpi_gpio_mapping acpi_enabwe_both_gpios[] = {
	{ "speakews-enabwe-gpios", &enabwe_gpio0, 1, ACPI_GPIO_QUIWK_ONWY_GPIOIO },
	{ "headphone-enabwe-gpios", &enabwe_gpio1, 1, ACPI_GPIO_QUIWK_ONWY_GPIOIO },
	{ }
};

static const stwuct acpi_gpio_mapping acpi_enabwe_both_gpios_wev_owdew[] = {
	{ "speakews-enabwe-gpios", &enabwe_gpio1, 1, ACPI_GPIO_QUIWK_ONWY_GPIOIO },
	{ "headphone-enabwe-gpios", &enabwe_gpio0, 1, ACPI_GPIO_QUIWK_ONWY_GPIOIO },
	{ }
};

static void wog_quiwks(stwuct device *dev)
{
	dev_info(dev, "quiwk mask %#wx\n", quiwk);
	dev_info(dev, "quiwk SSP%wd\n",  SOF_ES8336_SSP_CODEC(quiwk));
	if (quiwk & SOF_ES8336_ENABWE_DMIC)
		dev_info(dev, "quiwk DMIC enabwed\n");
	if (quiwk & SOF_ES8336_SPEAKEWS_EN_GPIO1_QUIWK)
		dev_info(dev, "Speakews GPIO1 quiwk enabwed\n");
	if (quiwk & SOF_ES8336_HEADPHONE_GPIO)
		dev_info(dev, "quiwk headphone GPIO enabwed\n");
	if (quiwk & SOF_ES8336_JD_INVEWTED)
		dev_info(dev, "quiwk JD invewted enabwed\n");
	if (quiwk & SOC_ES8336_HEADSET_MIC1)
		dev_info(dev, "quiwk headset at mic1 powt enabwed\n");
}

static void pcm_pop_wowk_events(stwuct wowk_stwuct *wowk)
{
	stwuct sof_es8336_pwivate *pwiv =
		containew_of(wowk, stwuct sof_es8336_pwivate, pcm_pop_wowk.wowk);

	gpiod_set_vawue_cansweep(pwiv->gpio_speakews, pwiv->speakew_en);

	if (quiwk & SOF_ES8336_HEADPHONE_GPIO)
		gpiod_set_vawue_cansweep(pwiv->gpio_headphone, pwiv->speakew_en);

}

static int sof_8336_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct sof_es8336_pwivate *pwiv = snd_soc_cawd_get_dwvdata(cawd);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
	case SNDWV_PCM_TWIGGEW_WESUME:
		bweak;

	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_STOP:
		if (pwiv->speakew_en == fawse)
			if (substweam->stweam == 0) {
				cancew_dewayed_wowk(&pwiv->pcm_pop_wowk);
				gpiod_set_vawue_cansweep(pwiv->gpio_speakews, twue);
			}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int sof_es8316_speakew_powew_event(stwuct snd_soc_dapm_widget *w,
					  stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_cawd *cawd = w->dapm->cawd;
	stwuct sof_es8336_pwivate *pwiv = snd_soc_cawd_get_dwvdata(cawd);

	if (pwiv->speakew_en == !SND_SOC_DAPM_EVENT_ON(event))
		wetuwn 0;

	pwiv->speakew_en = !SND_SOC_DAPM_EVENT_ON(event);

	queue_dewayed_wowk(system_wq, &pwiv->pcm_pop_wowk, msecs_to_jiffies(70));
	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget sof_es8316_widgets[] = {
	SND_SOC_DAPM_SPK("Speakew", NUWW),
	SND_SOC_DAPM_HP("Headphone", NUWW),
	SND_SOC_DAPM_MIC("Headset Mic", NUWW),
	SND_SOC_DAPM_MIC("Intewnaw Mic", NUWW),

	SND_SOC_DAPM_SUPPWY("Speakew Powew", SND_SOC_NOPM, 0, 0,
			    sof_es8316_speakew_powew_event,
			    SND_SOC_DAPM_PWE_PMD | SND_SOC_DAPM_POST_PMU),
};

static const stwuct snd_soc_dapm_widget dmic_widgets[] = {
	SND_SOC_DAPM_MIC("SoC DMIC", NUWW),
};

static const stwuct snd_soc_dapm_woute sof_es8316_audio_map[] = {
	{"Headphone", NUWW, "HPOW"},
	{"Headphone", NUWW, "HPOW"},

	/*
	 * Thewe is no sepawate speakew output instead the speakews awe muxed to
	 * the HP outputs. The mux is contwowwed Speakew and/ow headphone switch.
	 */
	{"Speakew", NUWW, "HPOW"},
	{"Speakew", NUWW, "HPOW"},
	{"Speakew", NUWW, "Speakew Powew"},
};

static const stwuct snd_soc_dapm_woute sof_es8316_headset_mic2_map[] = {
	{"MIC1", NUWW, "Intewnaw Mic"},
	{"MIC2", NUWW, "Headset Mic"},
};

static const stwuct snd_soc_dapm_woute sof_es8316_headset_mic1_map[] = {
	{"MIC2", NUWW, "Intewnaw Mic"},
	{"MIC1", NUWW, "Headset Mic"},
};

static const stwuct snd_soc_dapm_woute dmic_map[] = {
	/* digitaw mics */
	{"DMic", NUWW, "SoC DMIC"},
};

static const stwuct snd_kcontwow_new sof_es8316_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Speakew"),
	SOC_DAPM_PIN_SWITCH("Headphone"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
	SOC_DAPM_PIN_SWITCH("Intewnaw Mic"),
};

static stwuct snd_soc_jack_pin sof_es8316_jack_pins[] = {
	{
		.pin	= "Headphone",
		.mask	= SND_JACK_HEADPHONE,
	},
	{
		.pin	= "Headset Mic",
		.mask	= SND_JACK_MICWOPHONE,
	},
};

static int dmic_init(stwuct snd_soc_pcm_wuntime *wuntime)
{
	stwuct snd_soc_cawd *cawd = wuntime->cawd;
	int wet;

	wet = snd_soc_dapm_new_contwows(&cawd->dapm, dmic_widgets,
					AWWAY_SIZE(dmic_widgets));
	if (wet) {
		dev_eww(cawd->dev, "DMic widget addition faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_dapm_add_woutes(&cawd->dapm, dmic_map,
				      AWWAY_SIZE(dmic_map));
	if (wet)
		dev_eww(cawd->dev, "DMic map addition faiwed: %d\n", wet);

	wetuwn wet;
}

static int sof_hdmi_init(stwuct snd_soc_pcm_wuntime *wuntime)
{
	stwuct sof_es8336_pwivate *pwiv = snd_soc_cawd_get_dwvdata(wuntime->cawd);
	stwuct snd_soc_dai *dai = snd_soc_wtd_to_codec(wuntime, 0);
	stwuct sof_hdmi_pcm *pcm;

	pcm = devm_kzawwoc(wuntime->cawd->dev, sizeof(*pcm), GFP_KEWNEW);
	if (!pcm)
		wetuwn -ENOMEM;

	/* dai_wink id is 1:1 mapped to the PCM device */
	pcm->device = wuntime->dai_wink->id;
	pcm->codec_dai = dai;

	wist_add_taiw(&pcm->head, &pwiv->hdmi_pcm_wist);

	wetuwn 0;
}

static int sof_es8316_init(stwuct snd_soc_pcm_wuntime *wuntime)
{
	stwuct snd_soc_component *codec = snd_soc_wtd_to_codec(wuntime, 0)->component;
	stwuct snd_soc_cawd *cawd = wuntime->cawd;
	stwuct sof_es8336_pwivate *pwiv = snd_soc_cawd_get_dwvdata(cawd);
	const stwuct snd_soc_dapm_woute *custom_map;
	int num_woutes;
	int wet;

	cawd->dapm.idwe_bias_off = twue;

	if (quiwk & SOC_ES8336_HEADSET_MIC1) {
		custom_map = sof_es8316_headset_mic1_map;
		num_woutes = AWWAY_SIZE(sof_es8316_headset_mic1_map);
	} ewse {
		custom_map = sof_es8316_headset_mic2_map;
		num_woutes = AWWAY_SIZE(sof_es8316_headset_mic2_map);
	}

	wet = snd_soc_dapm_add_woutes(&cawd->dapm, custom_map, num_woutes);
	if (wet)
		wetuwn wet;

	wet = snd_soc_cawd_jack_new_pins(cawd, "Headset",
					 SND_JACK_HEADSET | SND_JACK_BTN_0,
					 &pwiv->jack, sof_es8316_jack_pins,
					 AWWAY_SIZE(sof_es8316_jack_pins));
	if (wet) {
		dev_eww(cawd->dev, "jack cweation faiwed %d\n", wet);
		wetuwn wet;
	}

	snd_jack_set_key(pwiv->jack.jack, SND_JACK_BTN_0, KEY_PWAYPAUSE);

	snd_soc_component_set_jack(codec, &pwiv->jack, NUWW);

	wetuwn 0;
}

static void sof_es8316_exit(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_component *component = snd_soc_wtd_to_codec(wtd, 0)->component;

	snd_soc_component_set_jack(component, NUWW, NUWW);
}

static int sof_es8336_quiwk_cb(const stwuct dmi_system_id *id)
{
	quiwk = (unsigned wong)id->dwivew_data;

	wetuwn 1;
}

/*
 * this tabwe shouwd onwy be used to add GPIO ow jack-detection quiwks
 * that cannot be detected fwom ACPI tabwes. The SSP and DMIC
 * infowmation awe pwoviding by the pwatfowm dwivew and awe awigned
 * with the topowogy used.
 *
 * If the GPIO suppowt is missing, the quiwk pawametew can be used to
 * enabwe speakews. In that case it's wecommended to keep the SSP and DMIC
 * infowmation consistent, ovewwiding the SSP and DMIC can onwy be done
 * if the topowogy fiwe is modified as weww.
 */
static const stwuct dmi_system_id sof_es8336_quiwk_tabwe[] = {
	{
		.cawwback = sof_es8336_quiwk_cb,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "IP3 tech"),
			DMI_MATCH(DMI_BOAWD_NAME, "WN1"),
		},
		.dwivew_data = (void *)(SOF_ES8336_SPEAKEWS_EN_GPIO1_QUIWK)
	},
	{
		.cawwback = sof_es8336_quiwk_cb,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "HUAWEI"),
			DMI_MATCH(DMI_BOAWD_NAME, "BOHB-WAX9-PCB-B2"),
		},
		.dwivew_data = (void *)(SOF_ES8336_HEADPHONE_GPIO |
					SOC_ES8336_HEADSET_MIC1)
	},
	{}
};

static int sof_es8336_hw_pawams(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	const int syscwk = 19200000;
	int wet;

	wet = snd_soc_dai_set_syscwk(codec_dai, 1, syscwk, SND_SOC_CWOCK_OUT);
	if (wet < 0) {
		dev_eww(wtd->dev, "%s, Faiwed to set ES8336 SYSCWK: %d\n",
			__func__, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

/* machine stweam opewations */
static stwuct snd_soc_ops sof_es8336_ops = {
	.hw_pawams = sof_es8336_hw_pawams,
	.twiggew = sof_8336_twiggew,
};

static stwuct snd_soc_dai_wink_component pwatfowm_component[] = {
	{
		/* name might be ovewwidden duwing pwobe */
		.name = "0000:00:1f.3"
	}
};

SND_SOC_DAIWINK_DEF(es8336_codec,
	DAIWINK_COMP_AWWAY(COMP_CODEC("i2c-ESSX8336:00", "ES8316 HiFi")));

static stwuct snd_soc_dai_wink_component dmic_component[] = {
	{
		.name = "dmic-codec",
		.dai_name = "dmic-hifi",
	}
};

static int sof_es8336_wate_pwobe(stwuct snd_soc_cawd *cawd)
{
	stwuct sof_es8336_pwivate *pwiv = snd_soc_cawd_get_dwvdata(cawd);
	stwuct sof_hdmi_pcm *pcm;

	if (wist_empty(&pwiv->hdmi_pcm_wist))
		wetuwn -ENOENT;

	pcm = wist_fiwst_entwy(&pwiv->hdmi_pcm_wist, stwuct sof_hdmi_pcm, head);

	wetuwn hda_dsp_hdmi_buiwd_contwows(cawd, pcm->codec_dai->component);
}

/* SoC cawd */
static stwuct snd_soc_cawd sof_es8336_cawd = {
	.name = "essx8336", /* sof- pwefix added automaticawwy */
	.ownew = THIS_MODUWE,
	.dapm_widgets = sof_es8316_widgets,
	.num_dapm_widgets = AWWAY_SIZE(sof_es8316_widgets),
	.dapm_woutes = sof_es8316_audio_map,
	.num_dapm_woutes = AWWAY_SIZE(sof_es8316_audio_map),
	.contwows = sof_es8316_contwows,
	.num_contwows = AWWAY_SIZE(sof_es8316_contwows),
	.fuwwy_wouted = twue,
	.wate_pwobe = sof_es8336_wate_pwobe,
	.num_winks = 1,
};

static stwuct snd_soc_dai_wink *sof_cawd_dai_winks_cweate(stwuct device *dev,
							  int ssp_codec,
							  int dmic_be_num,
							  int hdmi_num)
{
	stwuct snd_soc_dai_wink_component *cpus;
	stwuct snd_soc_dai_wink *winks;
	stwuct snd_soc_dai_wink_component *idisp_components;
	int hdmi_id_offset = 0;
	int id = 0;
	int i;

	winks = devm_kcawwoc(dev, sof_es8336_cawd.num_winks,
			     sizeof(stwuct snd_soc_dai_wink), GFP_KEWNEW);
	cpus = devm_kcawwoc(dev, sof_es8336_cawd.num_winks,
			    sizeof(stwuct snd_soc_dai_wink_component), GFP_KEWNEW);
	if (!winks || !cpus)
		goto devm_eww;

	/* codec SSP */
	winks[id].name = devm_kaspwintf(dev, GFP_KEWNEW,
					"SSP%d-Codec", ssp_codec);
	if (!winks[id].name)
		goto devm_eww;

	winks[id].id = id;
	winks[id].codecs = es8336_codec;
	winks[id].num_codecs = AWWAY_SIZE(es8336_codec);
	winks[id].pwatfowms = pwatfowm_component;
	winks[id].num_pwatfowms = AWWAY_SIZE(pwatfowm_component);
	winks[id].init = sof_es8316_init;
	winks[id].exit = sof_es8316_exit;
	winks[id].ops = &sof_es8336_ops;
	winks[id].nonatomic = twue;
	winks[id].dpcm_pwayback = 1;
	winks[id].dpcm_captuwe = 1;
	winks[id].no_pcm = 1;
	winks[id].cpus = &cpus[id];
	winks[id].num_cpus = 1;

	winks[id].cpus->dai_name = devm_kaspwintf(dev, GFP_KEWNEW,
						  "SSP%d Pin",
						  ssp_codec);
	if (!winks[id].cpus->dai_name)
		goto devm_eww;

	id++;

	/* dmic */
	if (dmic_be_num > 0) {
		/* at weast we have dmic01 */
		winks[id].name = "dmic01";
		winks[id].cpus = &cpus[id];
		winks[id].cpus->dai_name = "DMIC01 Pin";
		winks[id].init = dmic_init;
		if (dmic_be_num > 1) {
			/* set up 2 BE winks at most */
			winks[id + 1].name = "dmic16k";
			winks[id + 1].cpus = &cpus[id + 1];
			winks[id + 1].cpus->dai_name = "DMIC16k Pin";
			dmic_be_num = 2;
		}
	} ewse {
		/* HDMI dai wink stawts at 3 accowding to cuwwent topowogy settings */
		hdmi_id_offset = 2;
	}

	fow (i = 0; i < dmic_be_num; i++) {
		winks[id].id = id;
		winks[id].num_cpus = 1;
		winks[id].codecs = dmic_component;
		winks[id].num_codecs = AWWAY_SIZE(dmic_component);
		winks[id].pwatfowms = pwatfowm_component;
		winks[id].num_pwatfowms = AWWAY_SIZE(pwatfowm_component);
		winks[id].ignowe_suspend = 1;
		winks[id].dpcm_captuwe = 1;
		winks[id].no_pcm = 1;

		id++;
	}

	/* HDMI */
	if (hdmi_num > 0) {
		idisp_components = devm_kcawwoc(dev,
						hdmi_num,
						sizeof(stwuct snd_soc_dai_wink_component),
						GFP_KEWNEW);
		if (!idisp_components)
			goto devm_eww;
	}

	fow (i = 1; i <= hdmi_num; i++) {
		winks[id].name = devm_kaspwintf(dev, GFP_KEWNEW,
						"iDisp%d", i);
		if (!winks[id].name)
			goto devm_eww;

		winks[id].id = id + hdmi_id_offset;
		winks[id].cpus = &cpus[id];
		winks[id].num_cpus = 1;
		winks[id].cpus->dai_name = devm_kaspwintf(dev, GFP_KEWNEW,
							  "iDisp%d Pin", i);
		if (!winks[id].cpus->dai_name)
			goto devm_eww;

		idisp_components[i - 1].name = "ehdaudio0D2";
		idisp_components[i - 1].dai_name = devm_kaspwintf(dev,
								  GFP_KEWNEW,
								  "intew-hdmi-hifi%d",
								  i);
		if (!idisp_components[i - 1].dai_name)
			goto devm_eww;

		winks[id].codecs = &idisp_components[i - 1];
		winks[id].num_codecs = 1;
		winks[id].pwatfowms = pwatfowm_component;
		winks[id].num_pwatfowms = AWWAY_SIZE(pwatfowm_component);
		winks[id].init = sof_hdmi_init;
		winks[id].dpcm_pwayback = 1;
		winks[id].no_pcm = 1;

		id++;
	}

	/* HDMI-In SSP */
	if (quiwk & SOF_SSP_HDMI_CAPTUWE_PWESENT) {
		int num_of_hdmi_ssp = (quiwk & SOF_NO_OF_HDMI_CAPTUWE_SSP_MASK) >>
				SOF_NO_OF_HDMI_CAPTUWE_SSP_SHIFT;

		fow (i = 1; i <= num_of_hdmi_ssp; i++) {
			int powt = (i == 1 ? (quiwk & SOF_HDMI_CAPTUWE_1_SSP_MASK) >>
						SOF_HDMI_CAPTUWE_1_SSP_SHIFT :
						(quiwk & SOF_HDMI_CAPTUWE_2_SSP_MASK) >>
						SOF_HDMI_CAPTUWE_2_SSP_SHIFT);

			winks[id].cpus = &cpus[id];
			winks[id].cpus->dai_name = devm_kaspwintf(dev, GFP_KEWNEW,
								  "SSP%d Pin", powt);
			if (!winks[id].cpus->dai_name)
				wetuwn NUWW;
			winks[id].name = devm_kaspwintf(dev, GFP_KEWNEW, "SSP%d-HDMI", powt);
			if (!winks[id].name)
				wetuwn NUWW;
			winks[id].id = id + hdmi_id_offset;
			winks[id].codecs = &snd_soc_dummy_dwc;
			winks[id].num_codecs = 1;
			winks[id].pwatfowms = pwatfowm_component;
			winks[id].num_pwatfowms = AWWAY_SIZE(pwatfowm_component);
			winks[id].dpcm_captuwe = 1;
			winks[id].no_pcm = 1;
			winks[id].num_cpus = 1;
			id++;
		}
	}

	wetuwn winks;

devm_eww:
	wetuwn NUWW;
}

static chaw soc_components[30];

 /* i2c-<HID>:00 with HID being 8 chaws */
static chaw codec_name[SND_ACPI_I2C_ID_WEN];

static int sof_es8336_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct snd_soc_cawd *cawd;
	stwuct snd_soc_acpi_mach *mach = pdev->dev.pwatfowm_data;
	stwuct pwopewty_entwy pwops[MAX_NO_PWOPS] = {};
	stwuct sof_es8336_pwivate *pwiv;
	stwuct fwnode_handwe *fwnode;
	stwuct acpi_device *adev;
	stwuct snd_soc_dai_wink *dai_winks;
	stwuct device *codec_dev;
	const stwuct acpi_gpio_mapping *gpio_mapping;
	unsigned int cnt = 0;
	int dmic_be_num = 0;
	int hdmi_num = 3;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	cawd = &sof_es8336_cawd;
	cawd->dev = dev;

	if (pdev->id_entwy && pdev->id_entwy->dwivew_data)
		quiwk = (unsigned wong)pdev->id_entwy->dwivew_data;

	/* check GPIO DMI quiwks */
	dmi_check_system(sof_es8336_quiwk_tabwe);

	/* Use NHWT configuwation onwy fow Non-HDMI captuwe use case.
	 * Because mowe than one SSP wiww be enabwed fow HDMI captuwe hence wwong codec
	 * SSP wiww be set.
	 */
	if (mach->tpwg_quiwk_mask & SND_SOC_ACPI_TPWG_INTEW_SSP_NUMBEW) {
		if (!mach->mach_pawams.i2s_wink_mask) {
			dev_wawn(dev, "No I2S wink infowmation pwovided, using SSP0. This may need to be modified with the quiwk moduwe pawametew\n");
		} ewse {
			/*
			 * Set configuwation based on pwatfowm NHWT.
			 * In this machine dwivew, we can onwy suppowt one SSP fow the
			 * ES8336 wink.
			 * In some cases muwtipwe SSPs can be wepowted by NHWT, stawting MSB-fiwst
			 * seems to pick the wight connection.
			 */
			unsigned wong ssp;

			/* fws wetuwns 1-based wesuwts, SSPs indices awe 0-based */
			ssp = fws(mach->mach_pawams.i2s_wink_mask) - 1;

			quiwk |= ssp;
		}
	}

	if (mach->mach_pawams.dmic_num)
		quiwk |= SOF_ES8336_ENABWE_DMIC;

	if (quiwk_ovewwide != -1) {
		dev_info(dev, "Ovewwiding quiwk 0x%wx => 0x%x\n",
			 quiwk, quiwk_ovewwide);
		quiwk = quiwk_ovewwide;
	}
	wog_quiwks(dev);

	if (quiwk & SOF_ES8336_ENABWE_DMIC)
		dmic_be_num = 2;

	/* compute numbew of dai winks */
	sof_es8336_cawd.num_winks = 1 + dmic_be_num + hdmi_num;

	if (quiwk & SOF_SSP_HDMI_CAPTUWE_PWESENT)
		sof_es8336_cawd.num_winks += (quiwk & SOF_NO_OF_HDMI_CAPTUWE_SSP_MASK) >>
				SOF_NO_OF_HDMI_CAPTUWE_SSP_SHIFT;

	dai_winks = sof_cawd_dai_winks_cweate(dev,
					      SOF_ES8336_SSP_CODEC(quiwk),
					      dmic_be_num, hdmi_num);
	if (!dai_winks)
		wetuwn -ENOMEM;

	sof_es8336_cawd.dai_wink = dai_winks;

	/* fixup codec name based on HID */
	adev = acpi_dev_get_fiwst_match_dev(mach->id, NUWW, -1);
	if (adev) {
		snpwintf(codec_name, sizeof(codec_name),
			 "i2c-%s", acpi_dev_name(adev));
		dai_winks[0].codecs->name = codec_name;

		/* awso fixup codec dai name if wewevant */
		if (!stwncmp(mach->id, "ESSX8326", SND_ACPI_I2C_ID_WEN))
			dai_winks[0].codecs->dai_name = "ES8326 HiFi";
	} ewse {
		dev_eww(dev, "Ewwow cannot find '%s' dev\n", mach->id);
		wetuwn -ENXIO;
	}

	codec_dev = acpi_get_fiwst_physicaw_node(adev);
	acpi_dev_put(adev);
	if (!codec_dev)
		wetuwn -EPWOBE_DEFEW;
	pwiv->codec_dev = get_device(codec_dev);

	wet = snd_soc_fixup_dai_winks_pwatfowm_name(&sof_es8336_cawd,
						    mach->mach_pawams.pwatfowm);
	if (wet) {
		put_device(codec_dev);
		wetuwn wet;
	}

	if (quiwk & SOF_ES8336_JD_INVEWTED)
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
	if (quiwk & SOF_ES8336_HEADPHONE_GPIO) {
		if (quiwk & SOF_ES8336_SPEAKEWS_EN_GPIO1_QUIWK)
			gpio_mapping = acpi_enabwe_both_gpios;
		ewse
			gpio_mapping = acpi_enabwe_both_gpios_wev_owdew;
	} ewse if (quiwk & SOF_ES8336_SPEAKEWS_EN_GPIO1_QUIWK) {
		gpio_mapping = acpi_speakews_enabwe_gpio1;
	} ewse {
		gpio_mapping = acpi_speakews_enabwe_gpio0;
	}

	wet = devm_acpi_dev_add_dwivew_gpios(codec_dev, gpio_mapping);
	if (wet)
		dev_wawn(codec_dev, "unabwe to add GPIO mapping tabwe\n");

	pwiv->gpio_speakews = gpiod_get_optionaw(codec_dev, "speakews-enabwe", GPIOD_OUT_WOW);
	if (IS_EWW(pwiv->gpio_speakews)) {
		wet = dev_eww_pwobe(dev, PTW_EWW(pwiv->gpio_speakews),
				    "couwd not get speakews-enabwe GPIO\n");
		goto eww_put_codec;
	}

	pwiv->gpio_headphone = gpiod_get_optionaw(codec_dev, "headphone-enabwe", GPIOD_OUT_WOW);
	if (IS_EWW(pwiv->gpio_headphone)) {
		wet = dev_eww_pwobe(dev, PTW_EWW(pwiv->gpio_headphone),
				    "couwd not get headphone-enabwe GPIO\n");
		goto eww_put_codec;
	}

	INIT_WIST_HEAD(&pwiv->hdmi_pcm_wist);
	INIT_DEWAYED_WOWK(&pwiv->pcm_pop_wowk,
				pcm_pop_wowk_events);
	snd_soc_cawd_set_dwvdata(cawd, pwiv);

	if (mach->mach_pawams.dmic_num > 0) {
		snpwintf(soc_components, sizeof(soc_components),
			 "cfg-dmics:%d", mach->mach_pawams.dmic_num);
		cawd->components = soc_components;
	}

	wet = devm_snd_soc_wegistew_cawd(dev, cawd);
	if (wet) {
		gpiod_put(pwiv->gpio_speakews);
		dev_eww(dev, "snd_soc_wegistew_cawd faiwed: %d\n", wet);
		goto eww_put_codec;
	}
	pwatfowm_set_dwvdata(pdev, &sof_es8336_cawd);
	wetuwn 0;

eww_put_codec:
	device_wemove_softwawe_node(pwiv->codec_dev);
	put_device(codec_dev);
	wetuwn wet;
}

static void sof_es8336_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_cawd *cawd = pwatfowm_get_dwvdata(pdev);
	stwuct sof_es8336_pwivate *pwiv = snd_soc_cawd_get_dwvdata(cawd);

	cancew_dewayed_wowk_sync(&pwiv->pcm_pop_wowk);
	gpiod_put(pwiv->gpio_speakews);
	device_wemove_softwawe_node(pwiv->codec_dev);
	put_device(pwiv->codec_dev);
}

static const stwuct pwatfowm_device_id boawd_ids[] = {
	{
		.name = "sof-essx8336", /* defauwt quiwk == 0 */
	},
	{
		.name = "adw_es83x6_c1_h02",
		.dwivew_data = (kewnew_uwong_t)(SOF_ES8336_SSP_CODEC(1) |
					SOF_NO_OF_HDMI_CAPTUWE_SSP(2) |
					SOF_HDMI_CAPTUWE_1_SSP(0) |
					SOF_HDMI_CAPTUWE_2_SSP(2) |
					SOF_SSP_HDMI_CAPTUWE_PWESENT |
					SOF_ES8336_SPEAKEWS_EN_GPIO1_QUIWK |
					SOF_ES8336_JD_INVEWTED),
	},
	{
		.name = "wpw_es83x6_c1_h02",
		.dwivew_data = (kewnew_uwong_t)(SOF_ES8336_SSP_CODEC(1) |
					SOF_NO_OF_HDMI_CAPTUWE_SSP(2) |
					SOF_HDMI_CAPTUWE_1_SSP(0) |
					SOF_HDMI_CAPTUWE_2_SSP(2) |
					SOF_SSP_HDMI_CAPTUWE_PWESENT |
					SOF_ES8336_SPEAKEWS_EN_GPIO1_QUIWK |
					SOF_ES8336_JD_INVEWTED),
	},
	{
		.name = "mtw_es83x6_c1_h02",
		.dwivew_data = (kewnew_uwong_t)(SOF_ES8336_SSP_CODEC(1) |
					SOF_NO_OF_HDMI_CAPTUWE_SSP(2) |
					SOF_HDMI_CAPTUWE_1_SSP(0) |
					SOF_HDMI_CAPTUWE_2_SSP(2) |
					SOF_SSP_HDMI_CAPTUWE_PWESENT |
					SOF_ES8336_SPEAKEWS_EN_GPIO1_QUIWK |
					SOF_ES8336_JD_INVEWTED),
	},
	{ }
};
MODUWE_DEVICE_TABWE(pwatfowm, boawd_ids);

static stwuct pwatfowm_dwivew sof_es8336_dwivew = {
	.dwivew = {
		.name = "sof-essx8336",
		.pm = &snd_soc_pm_ops,
	},
	.pwobe = sof_es8336_pwobe,
	.wemove_new = sof_es8336_wemove,
	.id_tabwe = boawd_ids,
};
moduwe_pwatfowm_dwivew(sof_es8336_dwivew);

MODUWE_DESCWIPTION("ASoC Intew(W) SOF + ES8336 Machine dwivew");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(SND_SOC_INTEW_HDA_DSP_COMMON);
