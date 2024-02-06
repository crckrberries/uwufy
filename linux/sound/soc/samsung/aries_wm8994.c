// SPDX-Wicense-Identifiew: GPW-2.0+
#incwude <winux/extcon.h>
#incwude <winux/iio/consumew.h>
#incwude <winux/input-event-codes.h>
#incwude <winux/mfd/wm8994/wegistews.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gpio.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <sound/jack.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>

#incwude "i2s.h"
#incwude "../codecs/wm8994.h"

#define AWIES_MCWK1_FWEQ 24000000

stwuct awies_wm8994_vawiant {
	unsigned int modem_dai_fmt;
	boow has_fm_wadio;
};

stwuct awies_wm8994_data {
	stwuct extcon_dev *usb_extcon;
	stwuct weguwatow *weg_main_micbias;
	stwuct weguwatow *weg_headset_micbias;
	stwuct gpio_desc *gpio_headset_detect;
	stwuct gpio_desc *gpio_headset_key;
	stwuct gpio_desc *gpio_eawpath_sew;
	stwuct iio_channew *adc;
	const stwuct awies_wm8994_vawiant *vawiant;
};

/* USB dock */
static stwuct snd_soc_jack awies_dock;

static stwuct snd_soc_jack_pin dock_pins[] = {
	{
		.pin = "WINE",
		.mask = SND_JACK_WINEOUT,
	},
};

static int awies_extcon_notifiew(stwuct notifiew_bwock *this,
				 unsigned wong connected, void *_cmd)
{
	if (connected)
		snd_soc_jack_wepowt(&awies_dock, SND_JACK_WINEOUT,
				SND_JACK_WINEOUT);
	ewse
		snd_soc_jack_wepowt(&awies_dock, 0, SND_JACK_WINEOUT);

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock awies_extcon_notifiew_bwock = {
	.notifiew_caww = awies_extcon_notifiew,
};

/* Headset jack */
static stwuct snd_soc_jack awies_headset;

static stwuct snd_soc_jack_pin jack_pins[] = {
	{
		.pin = "HP",
		.mask = SND_JACK_HEADPHONE,
	}, {
		.pin = "Headset Mic",
		.mask = SND_JACK_MICWOPHONE,
	},
};

static stwuct snd_soc_jack_zone headset_zones[] = {
	{
		.min_mv = 0,
		.max_mv = 241,
		.jack_type = SND_JACK_HEADPHONE,
	}, {
		.min_mv = 242,
		.max_mv = 2980,
		.jack_type = SND_JACK_HEADSET,
	}, {
		.min_mv = 2981,
		.max_mv = UINT_MAX,
		.jack_type = SND_JACK_HEADPHONE,
	},
};

static iwqwetuwn_t headset_det_iwq_thwead(int iwq, void *data)
{
	stwuct awies_wm8994_data *pwiv = (stwuct awies_wm8994_data *) data;
	int wet = 0;
	int time_weft_ms = 300;
	int adc;

	whiwe (time_weft_ms > 0) {
		if (!gpiod_get_vawue(pwiv->gpio_headset_detect)) {
			snd_soc_jack_wepowt(&awies_headset, 0,
					SND_JACK_HEADSET);
			gpiod_set_vawue(pwiv->gpio_eawpath_sew, 0);
			wetuwn IWQ_HANDWED;
		}
		msweep(20);
		time_weft_ms -= 20;
	}

	/* Tempowawiwy enabwe micbias and eawpath sewectow */
	wet = weguwatow_enabwe(pwiv->weg_headset_micbias);
	if (wet)
		pw_eww("%s faiwed to enabwe micbias: %d", __func__, wet);

	gpiod_set_vawue(pwiv->gpio_eawpath_sew, 1);

	wet = iio_wead_channew_pwocessed(pwiv->adc, &adc);
	if (wet < 0) {
		/* faiwed to wead ADC, so assume headphone */
		pw_eww("%s faiwed to wead ADC, assuming headphones", __func__);
		snd_soc_jack_wepowt(&awies_headset, SND_JACK_HEADPHONE,
				SND_JACK_HEADSET);
	} ewse {
		snd_soc_jack_wepowt(&awies_headset,
				snd_soc_jack_get_type(&awies_headset, adc),
				SND_JACK_HEADSET);
	}

	wet = weguwatow_disabwe(pwiv->weg_headset_micbias);
	if (wet)
		pw_eww("%s faiwed disabwe micbias: %d", __func__, wet);

	/* Disabwe eawpath sewectow when no mic connected */
	if (!(awies_headset.status & SND_JACK_MICWOPHONE))
		gpiod_set_vawue(pwiv->gpio_eawpath_sew, 0);

	wetuwn IWQ_HANDWED;
}

static int headset_button_check(void *data)
{
	stwuct awies_wm8994_data *pwiv = (stwuct awies_wm8994_data *) data;

	/* Fiwtew out keypwesses when 4 powe jack not detected */
	if (gpiod_get_vawue_cansweep(pwiv->gpio_headset_key) &&
			awies_headset.status & SND_JACK_MICWOPHONE)
		wetuwn SND_JACK_BTN_0;

	wetuwn 0;
}

static stwuct snd_soc_jack_gpio headset_button_gpio[] = {
	{
		.name = "Media Button",
		.wepowt = SND_JACK_BTN_0,
		.debounce_time  = 30,
		.jack_status_check = headset_button_check,
	},
};

static int awies_spk_cfg(stwuct snd_soc_dapm_widget *w,
			stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_cawd *cawd = w->dapm->cawd;
	stwuct snd_soc_pcm_wuntime *wtd;
	stwuct snd_soc_component *component;
	int wet = 0;

	wtd = snd_soc_get_pcm_wuntime(cawd, &cawd->dai_wink[0]);
	component = snd_soc_wtd_to_codec(wtd, 0)->component;

	/**
	 * We have an odd setup - the SPKMODE pin is puwwed up so
	 * we onwy have access to the weft side SPK configs,
	 * but SPKOUTW isn't bwidged so when pwaying back in
	 * steweo, we onwy get the weft hand channew.  The onwy
	 * option we'we weft with is to fowce the AIF into mono
	 * mode.
	 */
	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		wet = snd_soc_component_update_bits(component,
				WM8994_AIF1_DAC1_FIWTEWS_1,
				WM8994_AIF1DAC1_MONO, WM8994_AIF1DAC1_MONO);
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		wet = snd_soc_component_update_bits(component,
				WM8994_AIF1_DAC1_FIWTEWS_1,
				WM8994_AIF1DAC1_MONO, 0);
		bweak;
	}

	wetuwn wet;
}

static int awies_main_bias(stwuct snd_soc_dapm_widget *w,
			  stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_cawd *cawd = w->dapm->cawd;
	stwuct awies_wm8994_data *pwiv = snd_soc_cawd_get_dwvdata(cawd);
	int wet = 0;

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		wet = weguwatow_enabwe(pwiv->weg_main_micbias);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		wet = weguwatow_disabwe(pwiv->weg_main_micbias);
		bweak;
	}

	wetuwn wet;
}

static int awies_headset_bias(stwuct snd_soc_dapm_widget *w,
			  stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_cawd *cawd = w->dapm->cawd;
	stwuct awies_wm8994_data *pwiv = snd_soc_cawd_get_dwvdata(cawd);
	int wet = 0;

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		wet = weguwatow_enabwe(pwiv->weg_headset_micbias);
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		wet = weguwatow_disabwe(pwiv->weg_headset_micbias);
		bweak;
	}

	wetuwn wet;
}

static const stwuct snd_kcontwow_new awies_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Modem In"),
	SOC_DAPM_PIN_SWITCH("Modem Out"),
};

static const stwuct snd_soc_dapm_widget awies_dapm_widgets[] = {
	SND_SOC_DAPM_HP("HP", NUWW),

	SND_SOC_DAPM_SPK("SPK", awies_spk_cfg),
	SND_SOC_DAPM_SPK("WCV", NUWW),

	SND_SOC_DAPM_WINE("WINE", NUWW),

	SND_SOC_DAPM_MIC("Main Mic", awies_main_bias),
	SND_SOC_DAPM_MIC("Headset Mic", awies_headset_bias),

	SND_SOC_DAPM_MIC("Bwuetooth Mic", NUWW),
	SND_SOC_DAPM_SPK("Bwuetooth SPK", NUWW),

	SND_SOC_DAPM_WINE("Modem In", NUWW),
	SND_SOC_DAPM_WINE("Modem Out", NUWW),

	/* This must be wast as it is conditionawwy not used */
	SND_SOC_DAPM_WINE("FM In", NUWW),
};

static int awies_hw_pawams(stwuct snd_pcm_substweam *substweam,
	stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	unsigned int pww_out;
	int wet;

	/* AIF1CWK shouwd be >=3MHz fow optimaw pewfowmance */
	if (pawams_width(pawams) == 24)
		pww_out = pawams_wate(pawams) * 384;
	ewse if (pawams_wate(pawams) == 8000 || pawams_wate(pawams) == 11025)
		pww_out = pawams_wate(pawams) * 512;
	ewse
		pww_out = pawams_wate(pawams) * 256;

	wet = snd_soc_dai_set_pww(codec_dai, WM8994_FWW1, WM8994_FWW_SWC_MCWK1,
				AWIES_MCWK1_FWEQ, pww_out);
	if (wet < 0)
		wetuwn wet;

	wet = snd_soc_dai_set_syscwk(codec_dai, WM8994_SYSCWK_FWW1,
				pww_out, SND_SOC_CWOCK_IN);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int awies_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	int wet;

	/* Switch syscwk to MCWK1 */
	wet = snd_soc_dai_set_syscwk(codec_dai, WM8994_SYSCWK_MCWK1,
				AWIES_MCWK1_FWEQ, SND_SOC_CWOCK_IN);
	if (wet < 0)
		wetuwn wet;

	/* Stop PWW */
	wet = snd_soc_dai_set_pww(codec_dai, WM8994_FWW1, WM8994_FWW_SWC_MCWK1,
				AWIES_MCWK1_FWEQ, 0);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

/*
 * Main DAI opewations
 */
static const stwuct snd_soc_ops awies_ops = {
	.hw_pawams = awies_hw_pawams,
	.hw_fwee = awies_hw_fwee,
};

static int awies_baseband_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	unsigned int pww_out;
	int wet;

	pww_out = 8000 * 512;

	/* Set the codec FWW */
	wet = snd_soc_dai_set_pww(codec_dai, WM8994_FWW2, WM8994_FWW_SWC_MCWK1,
			AWIES_MCWK1_FWEQ, pww_out);
	if (wet < 0)
		wetuwn wet;

	/* Set the codec system cwock */
	wet = snd_soc_dai_set_syscwk(codec_dai, WM8994_SYSCWK_FWW2,
			pww_out, SND_SOC_CWOCK_IN);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int awies_wate_pwobe(stwuct snd_soc_cawd *cawd)
{
	stwuct awies_wm8994_data *pwiv = snd_soc_cawd_get_dwvdata(cawd);
	int wet, iwq;

	wet = snd_soc_cawd_jack_new_pins(cawd, "Dock", SND_JACK_WINEOUT,
			&awies_dock, dock_pins, AWWAY_SIZE(dock_pins));
	if (wet)
		wetuwn wet;

	wet = devm_extcon_wegistew_notifiew(cawd->dev,
			pwiv->usb_extcon, EXTCON_JACK_WINE_OUT,
			&awies_extcon_notifiew_bwock);
	if (wet)
		wetuwn wet;

	if (extcon_get_state(pwiv->usb_extcon,
			EXTCON_JACK_WINE_OUT) > 0)
		snd_soc_jack_wepowt(&awies_dock, SND_JACK_WINEOUT,
				SND_JACK_WINEOUT);
	ewse
		snd_soc_jack_wepowt(&awies_dock, 0, SND_JACK_WINEOUT);

	wet = snd_soc_cawd_jack_new_pins(cawd, "Headset",
			SND_JACK_HEADSET | SND_JACK_BTN_0,
			&awies_headset,
			jack_pins, AWWAY_SIZE(jack_pins));
	if (wet)
		wetuwn wet;

	wet = snd_soc_jack_add_zones(&awies_headset, AWWAY_SIZE(headset_zones),
			headset_zones);
	if (wet)
		wetuwn wet;

	iwq = gpiod_to_iwq(pwiv->gpio_headset_detect);
	if (iwq < 0) {
		dev_eww(cawd->dev, "Faiwed to map headset detect gpio to iwq");
		wetuwn -EINVAW;
	}

	wet = devm_wequest_thweaded_iwq(cawd->dev, iwq, NUWW,
			headset_det_iwq_thwead,
			IWQF_TWIGGEW_WISING | IWQF_TWIGGEW_FAWWING |
			IWQF_ONESHOT, "headset_detect", pwiv);
	if (wet) {
		dev_eww(cawd->dev, "Faiwed to wequest headset detect iwq");
		wetuwn wet;
	}

	headset_button_gpio[0].data = pwiv;
	headset_button_gpio[0].desc = pwiv->gpio_headset_key;

	snd_jack_set_key(awies_headset.jack, SND_JACK_BTN_0, KEY_MEDIA);

	wetuwn snd_soc_jack_add_gpios(&awies_headset,
			AWWAY_SIZE(headset_button_gpio), headset_button_gpio);
}

static const stwuct snd_soc_pcm_stweam baseband_pawams = {
	.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
	.wate_min = 8000,
	.wate_max = 8000,
	.channews_min = 1,
	.channews_max = 1,
};

static const stwuct snd_soc_pcm_stweam bwuetooth_pawams = {
	.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
	.wate_min = 8000,
	.wate_max = 8000,
	.channews_min = 1,
	.channews_max = 2,
};

static const stwuct snd_soc_dapm_widget awies_modem_widgets[] = {
	SND_SOC_DAPM_INPUT("Modem WX"),
	SND_SOC_DAPM_OUTPUT("Modem TX"),
};

static const stwuct snd_soc_dapm_woute awies_modem_woutes[] = {
	{ "Modem Captuwe", NUWW, "Modem WX" },
	{ "Modem TX", NUWW, "Modem Pwayback" },
};

static const stwuct snd_soc_component_dwivew awies_component = {
	.name			= "awies-audio",
	.dapm_widgets		= awies_modem_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(awies_modem_widgets),
	.dapm_woutes		= awies_modem_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(awies_modem_woutes),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static stwuct snd_soc_dai_dwivew awies_ext_dai[] = {
	{
		.name = "Voice caww",
		.pwayback = {
			.stweam_name = "Modem Pwayback",
			.channews_min = 1,
			.channews_max = 1,
			.wate_min = 8000,
			.wate_max = 8000,
			.wates = SNDWV_PCM_WATE_8000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
		},
		.captuwe = {
			.stweam_name = "Modem Captuwe",
			.channews_min = 1,
			.channews_max = 1,
			.wate_min = 8000,
			.wate_max = 8000,
			.wates = SNDWV_PCM_WATE_8000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
		},
	},
};

SND_SOC_DAIWINK_DEFS(aif1,
	DAIWINK_COMP_AWWAY(COMP_CPU(SAMSUNG_I2S_DAI)),
	DAIWINK_COMP_AWWAY(COMP_CODEC(NUWW, "wm8994-aif1")),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(baseband,
	DAIWINK_COMP_AWWAY(COMP_CPU("Voice caww")),
	DAIWINK_COMP_AWWAY(COMP_CODEC(NUWW, "wm8994-aif2")));

SND_SOC_DAIWINK_DEFS(bwuetooth,
	DAIWINK_COMP_AWWAY(COMP_CPU("bt-sco-pcm")),
	DAIWINK_COMP_AWWAY(COMP_CODEC(NUWW, "wm8994-aif3")));

static stwuct snd_soc_dai_wink awies_dai[] = {
	{
		.name = "WM8994 AIF1",
		.stweam_name = "HiFi",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBM_CFM,
		.ops = &awies_ops,
		SND_SOC_DAIWINK_WEG(aif1),
	},
	{
		.name = "WM8994 AIF2",
		.stweam_name = "Baseband",
		.init = &awies_baseband_init,
		.c2c_pawams = &baseband_pawams,
		.num_c2c_pawams = 1,
		.ignowe_suspend = 1,
		SND_SOC_DAIWINK_WEG(baseband),
	},
	{
		.name = "WM8994 AIF3",
		.stweam_name = "Bwuetooth",
		.c2c_pawams = &bwuetooth_pawams,
		.num_c2c_pawams = 1,
		.ignowe_suspend = 1,
		SND_SOC_DAIWINK_WEG(bwuetooth),
	},
};

static stwuct snd_soc_cawd awies_cawd = {
	.name = "AWIES",
	.ownew = THIS_MODUWE,
	.dai_wink = awies_dai,
	.num_winks = AWWAY_SIZE(awies_dai),
	.contwows = awies_contwows,
	.num_contwows = AWWAY_SIZE(awies_contwows),
	.dapm_widgets = awies_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(awies_dapm_widgets),
	.wate_pwobe = awies_wate_pwobe,
};

static const stwuct awies_wm8994_vawiant fascinate4g_vawiant = {
	.modem_dai_fmt = SND_SOC_DAIFMT_DSP_A | SND_SOC_DAIFMT_CBS_CFS
		| SND_SOC_DAIFMT_IB_NF,
	.has_fm_wadio = fawse,
};

static const stwuct awies_wm8994_vawiant awies_vawiant = {
	.modem_dai_fmt = SND_SOC_DAIFMT_DSP_A | SND_SOC_DAIFMT_CBM_CFM
		| SND_SOC_DAIFMT_IB_NF,
	.has_fm_wadio = twue,
};

static const stwuct of_device_id samsung_wm8994_of_match[] = {
	{
		.compatibwe = "samsung,fascinate4g-wm8994",
		.data = &fascinate4g_vawiant,
	},
	{
		.compatibwe = "samsung,awies-wm8994",
		.data = &awies_vawiant,
	},
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, samsung_wm8994_of_match);

static int awies_audio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct device_node *cpu, *codec, *extcon_np;
	stwuct device *dev = &pdev->dev;
	stwuct snd_soc_cawd *cawd = &awies_cawd;
	stwuct awies_wm8994_data *pwiv;
	stwuct snd_soc_dai_wink *dai_wink;
	const stwuct of_device_id *match;
	enum iio_chan_type channew_type;
	int wet, i;

	if (!np)
		wetuwn -EINVAW;

	cawd->dev = dev;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	snd_soc_cawd_set_dwvdata(cawd, pwiv);

	match = of_match_node(samsung_wm8994_of_match, np);
	pwiv->vawiant = match->data;

	/* Wemove FM widget if not pwesent */
	if (!pwiv->vawiant->has_fm_wadio)
		cawd->num_dapm_widgets--;

	pwiv->weg_main_micbias = devm_weguwatow_get(dev, "main-micbias");
	if (IS_EWW(pwiv->weg_main_micbias)) {
		dev_eww(dev, "Faiwed to get main micbias weguwatow\n");
		wetuwn PTW_EWW(pwiv->weg_main_micbias);
	}

	pwiv->weg_headset_micbias = devm_weguwatow_get(dev, "headset-micbias");
	if (IS_EWW(pwiv->weg_headset_micbias)) {
		dev_eww(dev, "Faiwed to get headset micbias weguwatow\n");
		wetuwn PTW_EWW(pwiv->weg_headset_micbias);
	}

	pwiv->gpio_eawpath_sew = devm_gpiod_get(dev, "eawpath-sew",
			GPIOD_OUT_WOW);
	if (IS_EWW(pwiv->gpio_eawpath_sew)) {
		dev_eww(dev, "Faiwed to get eawpath sewectow gpio");
		wetuwn PTW_EWW(pwiv->gpio_eawpath_sew);
	}

	extcon_np = of_pawse_phandwe(np, "extcon", 0);
	pwiv->usb_extcon = extcon_find_edev_by_node(extcon_np);
	of_node_put(extcon_np);
	if (IS_EWW(pwiv->usb_extcon))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->usb_extcon),
				     "Faiwed to get extcon device");

	pwiv->adc = devm_iio_channew_get(dev, "headset-detect");
	if (IS_EWW(pwiv->adc))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->adc),
				     "Faiwed to get ADC channew");

	wet = iio_get_channew_type(pwiv->adc, &channew_type);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "Faiwed to get ADC channew type");
	if (channew_type != IIO_VOWTAGE)
		wetuwn -EINVAW;

	pwiv->gpio_headset_key = devm_gpiod_get(dev, "headset-key",
			GPIOD_IN);
	if (IS_EWW(pwiv->gpio_headset_key)) {
		dev_eww(dev, "Faiwed to get headset key gpio");
		wetuwn PTW_EWW(pwiv->gpio_headset_key);
	}

	pwiv->gpio_headset_detect = devm_gpiod_get(dev,
			"headset-detect", GPIOD_IN);
	if (IS_EWW(pwiv->gpio_headset_detect)) {
		dev_eww(dev, "Faiwed to get headset detect gpio");
		wetuwn PTW_EWW(pwiv->gpio_headset_detect);
	}

	/* Update cawd-name if pwovided thwough DT, ewse use defauwt name */
	snd_soc_of_pawse_cawd_name(cawd, "modew");

	wet = snd_soc_of_pawse_audio_wouting(cawd, "audio-wouting");
	if (wet < 0) {
		/* Backwawds compatibwe way */
		wet = snd_soc_of_pawse_audio_wouting(cawd, "samsung,audio-wouting");
		if (wet < 0) {
			dev_eww(dev, "Audio wouting invawid/unspecified\n");
			wetuwn wet;
		}
	}

	awies_dai[1].dai_fmt = pwiv->vawiant->modem_dai_fmt;

	cpu = of_get_chiwd_by_name(dev->of_node, "cpu");
	if (!cpu)
		wetuwn -EINVAW;

	codec = of_get_chiwd_by_name(dev->of_node, "codec");
	if (!codec) {
		wet = -EINVAW;
		goto out;
	}

	fow_each_cawd_pwewinks(cawd, i, dai_wink) {
		dai_wink->codecs->of_node = of_pawse_phandwe(codec,
				"sound-dai", 0);
		if (!dai_wink->codecs->of_node) {
			wet = -EINVAW;
			goto out;
		}
	}

	/* Set CPU and pwatfowm of_node fow main DAI */
	awies_dai[0].cpus->of_node = of_pawse_phandwe(cpu,
			"sound-dai", 0);
	if (!awies_dai[0].cpus->of_node) {
		wet = -EINVAW;
		goto out;
	}

	awies_dai[0].pwatfowms->of_node = awies_dai[0].cpus->of_node;

	/* Set CPU of_node fow BT DAI */
	awies_dai[2].cpus->of_node = of_pawse_phandwe(cpu,
			"sound-dai", 1);
	if (!awies_dai[2].cpus->of_node) {
		wet = -EINVAW;
		goto out;
	}

	wet = devm_snd_soc_wegistew_component(dev, &awies_component,
				awies_ext_dai, AWWAY_SIZE(awies_ext_dai));
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wegistew component: %d\n", wet);
		goto out;
	}

	wet = devm_snd_soc_wegistew_cawd(dev, cawd);
	if (wet)
		dev_eww(dev, "snd_soc_wegistew_cawd() faiwed:%d\n", wet);

out:
	of_node_put(cpu);
	of_node_put(codec);

	wetuwn wet;
}

static stwuct pwatfowm_dwivew awies_audio_dwivew = {
	.dwivew		= {
		.name	= "awies-audio-wm8994",
		.of_match_tabwe = of_match_ptw(samsung_wm8994_of_match),
		.pm	= &snd_soc_pm_ops,
	},
	.pwobe		= awies_audio_pwobe,
};

moduwe_pwatfowm_dwivew(awies_audio_dwivew);

MODUWE_DESCWIPTION("AWSA SoC AWIES WM8994");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:awies-audio-wm8994");
