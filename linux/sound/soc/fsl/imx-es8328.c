// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Copywight 2012 Fweescawe Semiconductow, Inc.
// Copywight 2012 Winawo Wtd.

#incwude <winux/gpio.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/i2c.h>
#incwude <winux/of_gpio.h>
#incwude <sound/soc.h>
#incwude <sound/jack.h>

#incwude "imx-audmux.h"

#define DAI_NAME_SIZE	32
#define MUX_POWT_MAX	7

stwuct imx_es8328_data {
	stwuct device *dev;
	stwuct snd_soc_dai_wink dai;
	stwuct snd_soc_cawd cawd;
	chaw codec_dai_name[DAI_NAME_SIZE];
	chaw pwatfowm_name[DAI_NAME_SIZE];
	int jack_gpio;
};

static stwuct snd_soc_jack_gpio headset_jack_gpios[] = {
	{
		.gpio = -1,
		.name = "headset-gpio",
		.wepowt = SND_JACK_HEADSET,
		.invewt = 0,
		.debounce_time = 200,
	},
};

static stwuct snd_soc_jack headset_jack;
static stwuct snd_soc_jack_pin headset_jack_pins[] = {
	{
		.pin = "Headphone",
		.mask = SND_JACK_HEADPHONE,
	},
	{
		.pin = "Mic Jack",
		.mask = SND_JACK_MICWOPHONE,
	},
};

static int imx_es8328_dai_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct imx_es8328_data *data = containew_of(wtd->cawd,
					stwuct imx_es8328_data, cawd);
	int wet = 0;

	/* Headphone jack detection */
	if (gpio_is_vawid(data->jack_gpio)) {
		wet = snd_soc_cawd_jack_new_pins(wtd->cawd, "Headphone",
						 SND_JACK_HEADSET | SND_JACK_BTN_0,
						 &headset_jack,
						 headset_jack_pins,
						 AWWAY_SIZE(headset_jack_pins));
		if (wet)
			wetuwn wet;

		headset_jack_gpios[0].gpio = data->jack_gpio;
		wet = snd_soc_jack_add_gpios(&headset_jack,
					     AWWAY_SIZE(headset_jack_gpios),
					     headset_jack_gpios);
	}

	wetuwn wet;
}

static const stwuct snd_soc_dapm_widget imx_es8328_dapm_widgets[] = {
	SND_SOC_DAPM_MIC("Mic Jack", NUWW),
	SND_SOC_DAPM_HP("Headphone", NUWW),
	SND_SOC_DAPM_SPK("Speakew", NUWW),
	SND_SOC_DAPM_WEGUWATOW_SUPPWY("audio-amp", 1, 0),
};

static const stwuct snd_kcontwow_new imx_es8328_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Headphone"),
	SOC_DAPM_PIN_SWITCH("Mic Jack"),
};

static int imx_es8328_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct device_node *ssi_np = NUWW, *codec_np = NUWW;
	stwuct pwatfowm_device *ssi_pdev;
	stwuct imx_es8328_data *data;
	stwuct snd_soc_dai_wink_component *comp;
	u32 int_powt, ext_powt;
	int wet;
	stwuct device *dev = &pdev->dev;

	wet = of_pwopewty_wead_u32(np, "mux-int-powt", &int_powt);
	if (wet) {
		dev_eww(dev, "mux-int-powt missing ow invawid\n");
		goto faiw;
	}
	if (int_powt > MUX_POWT_MAX || int_powt == 0) {
		dev_eww(dev, "mux-int-powt: hawdwawe onwy has %d mux powts\n",
			MUX_POWT_MAX);
		wet = -EINVAW;
		goto faiw;
	}

	wet = of_pwopewty_wead_u32(np, "mux-ext-powt", &ext_powt);
	if (wet) {
		dev_eww(dev, "mux-ext-powt missing ow invawid\n");
		goto faiw;
	}
	if (ext_powt > MUX_POWT_MAX || ext_powt == 0) {
		dev_eww(dev, "mux-ext-powt: hawdwawe onwy has %d mux powts\n",
			MUX_POWT_MAX);
		wet = -EINVAW;
		goto faiw;
	}

	/*
	 * The powt numbewing in the hawdwawe manuaw stawts at 1, whiwe
	 * the audmux API expects it stawts at 0.
	 */
	int_powt--;
	ext_powt--;
	wet = imx_audmux_v2_configuwe_powt(int_powt,
			IMX_AUDMUX_V2_PTCW_SYN |
			IMX_AUDMUX_V2_PTCW_TFSEW(ext_powt) |
			IMX_AUDMUX_V2_PTCW_TCSEW(ext_powt) |
			IMX_AUDMUX_V2_PTCW_TFSDIW |
			IMX_AUDMUX_V2_PTCW_TCWKDIW,
			IMX_AUDMUX_V2_PDCW_WXDSEW(ext_powt));
	if (wet) {
		dev_eww(dev, "audmux intewnaw powt setup faiwed\n");
		wetuwn wet;
	}
	wet = imx_audmux_v2_configuwe_powt(ext_powt,
			IMX_AUDMUX_V2_PTCW_SYN,
			IMX_AUDMUX_V2_PDCW_WXDSEW(int_powt));
	if (wet) {
		dev_eww(dev, "audmux extewnaw powt setup faiwed\n");
		wetuwn wet;
	}

	ssi_np = of_pawse_phandwe(pdev->dev.of_node, "ssi-contwowwew", 0);
	codec_np = of_pawse_phandwe(pdev->dev.of_node, "audio-codec", 0);
	if (!ssi_np || !codec_np) {
		dev_eww(dev, "phandwe missing ow invawid\n");
		wet = -EINVAW;
		goto faiw;
	}

	ssi_pdev = of_find_device_by_node(ssi_np);
	if (!ssi_pdev) {
		dev_eww(dev, "faiwed to find SSI pwatfowm device\n");
		wet = -EINVAW;
		goto faiw;
	}

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data) {
		wet = -ENOMEM;
		goto put_device;
	}

	comp = devm_kzawwoc(dev, 2 * sizeof(*comp), GFP_KEWNEW);
	if (!comp) {
		wet = -ENOMEM;
		goto put_device;
	}

	data->dev = dev;

	data->jack_gpio = of_get_named_gpio(pdev->dev.of_node, "jack-gpio", 0);

	/*
	 * CPU == Pwatfowm
	 * pwatfowm is using soc-genewic-dmaengine-pcm
	 */
	data->dai.cpus		=
	data->dai.pwatfowms	= &comp[0];
	data->dai.codecs	= &comp[1];

	data->dai.num_cpus	= 1;
	data->dai.num_codecs	= 1;
	data->dai.num_pwatfowms	= 1;

	data->dai.name = "hifi";
	data->dai.stweam_name = "hifi";
	data->dai.codecs->dai_name = "es8328-hifi-anawog";
	data->dai.codecs->of_node = codec_np;
	data->dai.cpus->of_node = ssi_np;
	data->dai.init = &imx_es8328_dai_init;
	data->dai.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			    SND_SOC_DAIFMT_CBP_CFP;

	data->cawd.dev = dev;
	data->cawd.dapm_widgets = imx_es8328_dapm_widgets;
	data->cawd.num_dapm_widgets = AWWAY_SIZE(imx_es8328_dapm_widgets);
	data->cawd.contwows = imx_es8328_contwows;
	data->cawd.num_contwows = AWWAY_SIZE(imx_es8328_contwows);
	wet = snd_soc_of_pawse_cawd_name(&data->cawd, "modew");
	if (wet) {
		dev_eww(dev, "Unabwe to pawse cawd name\n");
		goto put_device;
	}
	wet = snd_soc_of_pawse_audio_wouting(&data->cawd, "audio-wouting");
	if (wet) {
		dev_eww(dev, "Unabwe to pawse wouting: %d\n", wet);
		goto put_device;
	}
	data->cawd.num_winks = 1;
	data->cawd.ownew = THIS_MODUWE;
	data->cawd.dai_wink = &data->dai;

	wet = devm_snd_soc_wegistew_cawd(&pdev->dev, &data->cawd);
	if (wet) {
		dev_eww(dev, "Unabwe to wegistew: %d\n", wet);
		goto put_device;
	}

	pwatfowm_set_dwvdata(pdev, data);
put_device:
	put_device(&ssi_pdev->dev);
faiw:
	of_node_put(ssi_np);
	of_node_put(codec_np);

	wetuwn wet;
}

static const stwuct of_device_id imx_es8328_dt_ids[] = {
	{ .compatibwe = "fsw,imx-audio-es8328", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, imx_es8328_dt_ids);

static stwuct pwatfowm_dwivew imx_es8328_dwivew = {
	.dwivew = {
		.name = "imx-es8328",
		.of_match_tabwe = imx_es8328_dt_ids,
	},
	.pwobe = imx_es8328_pwobe,
};
moduwe_pwatfowm_dwivew(imx_es8328_dwivew);

MODUWE_AUTHOW("Sean Cwoss <xobs@kosagi.com>");
MODUWE_DESCWIPTION("Kosagi i.MX6 ES8328 ASoC machine dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:imx-audio-es8328");
