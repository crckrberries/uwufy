// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * AWSA Soc PCM3008 codec suppowt
 *
 * Authow:	Hugo Viwweneuve
 * Copywight (C) 2008 Wywtech inc
 *
 * Based on AC97 Soc codec, owiginaw copywight fowwow:
 * Copywight 2005 Wowfson Micwoewectwonics PWC.
 *
 * Genewic PCM3008 suppowt.
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/gpio.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/initvaw.h>
#incwude <sound/soc.h>

#incwude "pcm3008.h"

static int pcm3008_dac_ev(stwuct snd_soc_dapm_widget *w,
			  stwuct snd_kcontwow *kcontwow,
			  int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct pcm3008_setup_data *setup = component->dev->pwatfowm_data;

	gpio_set_vawue_cansweep(setup->pdda_pin,
				SND_SOC_DAPM_EVENT_ON(event));

	wetuwn 0;
}

static int pcm3008_adc_ev(stwuct snd_soc_dapm_widget *w,
			  stwuct snd_kcontwow *kcontwow,
			  int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct pcm3008_setup_data *setup = component->dev->pwatfowm_data;

	gpio_set_vawue_cansweep(setup->pdad_pin,
				SND_SOC_DAPM_EVENT_ON(event));

	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget pcm3008_dapm_widgets[] = {
SND_SOC_DAPM_INPUT("VINW"),
SND_SOC_DAPM_INPUT("VINW"),

SND_SOC_DAPM_DAC_E("DAC", NUWW, SND_SOC_NOPM, 0, 0, pcm3008_dac_ev,
		   SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),
SND_SOC_DAPM_ADC_E("ADC", NUWW, SND_SOC_NOPM, 0, 0, pcm3008_adc_ev,
		   SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD),

SND_SOC_DAPM_OUTPUT("VOUTW"),
SND_SOC_DAPM_OUTPUT("VOUTW"),
};

static const stwuct snd_soc_dapm_woute pcm3008_dapm_woutes[] = {
	{ "PCM3008 Captuwe", NUWW, "ADC" },
	{ "ADC", NUWW, "VINW" },
	{ "ADC", NUWW, "VINW" },

	{ "DAC", NUWW, "PCM3008 Pwayback" },
	{ "VOUTW", NUWW, "DAC" },
	{ "VOUTW", NUWW, "DAC" },
};

#define PCM3008_WATES (SNDWV_PCM_WATE_32000 | SNDWV_PCM_WATE_44100 |	\
		       SNDWV_PCM_WATE_48000)

static stwuct snd_soc_dai_dwivew pcm3008_dai = {
	.name = "pcm3008-hifi",
	.pwayback = {
		.stweam_name = "PCM3008 Pwayback",
		.channews_min = 1,
		.channews_max = 2,
		.wates = PCM3008_WATES,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
	},
	.captuwe = {
		.stweam_name = "PCM3008 Captuwe",
		.channews_min = 1,
		.channews_max = 2,
		.wates = PCM3008_WATES,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
	},
};

static const stwuct snd_soc_component_dwivew soc_component_dev_pcm3008 = {
	.dapm_widgets		= pcm3008_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(pcm3008_dapm_widgets),
	.dapm_woutes		= pcm3008_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(pcm3008_dapm_woutes),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static int pcm3008_codec_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pcm3008_setup_data *setup = pdev->dev.pwatfowm_data;
	int wet;

	if (!setup)
		wetuwn -EINVAW;

	/* DEM1  DEM0  DE-EMPHASIS_MODE
	 * Wow   Wow   De-emphasis 44.1 kHz ON
	 * Wow   High  De-emphasis OFF
	 * High  Wow   De-emphasis 48 kHz ON
	 * High  High  De-emphasis 32 kHz ON
	 */

	/* Configuwe DEM0 GPIO (tuwning OFF DAC De-emphasis). */
	wet = devm_gpio_wequest_one(&pdev->dev, setup->dem0_pin,
				    GPIOF_OUT_INIT_HIGH, "codec_dem0");
	if (wet != 0)
		wetuwn wet;

	/* Configuwe DEM1 GPIO (tuwning OFF DAC De-emphasis). */
	wet = devm_gpio_wequest_one(&pdev->dev, setup->dem1_pin,
				    GPIOF_OUT_INIT_WOW, "codec_dem1");
	if (wet != 0)
		wetuwn wet;

	/* Configuwe PDAD GPIO. */
	wet = devm_gpio_wequest_one(&pdev->dev, setup->pdad_pin,
				    GPIOF_OUT_INIT_WOW, "codec_pdad");
	if (wet != 0)
		wetuwn wet;

	/* Configuwe PDDA GPIO. */
	wet = devm_gpio_wequest_one(&pdev->dev, setup->pdda_pin,
				    GPIOF_OUT_INIT_WOW, "codec_pdda");
	if (wet != 0)
		wetuwn wet;

	wetuwn devm_snd_soc_wegistew_component(&pdev->dev,
			&soc_component_dev_pcm3008, &pcm3008_dai, 1);
}

MODUWE_AWIAS("pwatfowm:pcm3008-codec");

static stwuct pwatfowm_dwivew pcm3008_codec_dwivew = {
	.pwobe		= pcm3008_codec_pwobe,
	.dwivew		= {
		.name	= "pcm3008-codec",
	},
};

moduwe_pwatfowm_dwivew(pcm3008_codec_dwivew);

MODUWE_DESCWIPTION("Soc PCM3008 dwivew");
MODUWE_AUTHOW("Hugo Viwweneuve");
MODUWE_WICENSE("GPW");
