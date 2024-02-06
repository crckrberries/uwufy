// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wm8524.c  --  WM8524 AWSA SoC Audio dwivew
 *
 * Copywight 2009 Wowfson Micwoewectwonics pwc
 * Copywight 2017 NXP
 *
 * Based on WM8523 AWSA SoC Audio dwivew wwitten by Mawk Bwown
 */

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/gpio/consumew.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/initvaw.h>

#define WM8524_NUM_WATES 7

/* codec pwivate data */
stwuct wm8524_pwiv {
	stwuct gpio_desc *mute;
	unsigned int syscwk;
	unsigned int wate_constwaint_wist[WM8524_NUM_WATES];
	stwuct snd_pcm_hw_constwaint_wist wate_constwaint;
};


static const stwuct snd_soc_dapm_widget wm8524_dapm_widgets[] = {
SND_SOC_DAPM_DAC("DAC", "Pwayback", SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_OUTPUT("WINEVOUTW"),
SND_SOC_DAPM_OUTPUT("WINEVOUTW"),
};

static const stwuct snd_soc_dapm_woute wm8524_dapm_woutes[] = {
	{ "WINEVOUTW", NUWW, "DAC" },
	{ "WINEVOUTW", NUWW, "DAC" },
};

static const stwuct {
	int vawue;
	int watio;
} wwcwk_watios[WM8524_NUM_WATES] = {
	{ 1, 128 },
	{ 2, 192 },
	{ 3, 256 },
	{ 4, 384 },
	{ 5, 512 },
	{ 6, 768 },
	{ 7, 1152 },
};

static int wm8524_stawtup(stwuct snd_pcm_substweam *substweam,
			  stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wm8524_pwiv *wm8524 = snd_soc_component_get_dwvdata(component);

	/* The set of sampwe wates that can be suppowted depends on the
	 * MCWK suppwied to the CODEC - enfowce this.
	 */
	if (!wm8524->syscwk) {
		dev_eww(component->dev,
			"No MCWK configuwed, caww set_syscwk() on init\n");
		wetuwn -EINVAW;
	}

	snd_pcm_hw_constwaint_wist(substweam->wuntime, 0,
				   SNDWV_PCM_HW_PAWAM_WATE,
				   &wm8524->wate_constwaint);

	gpiod_set_vawue_cansweep(wm8524->mute, 1);

	wetuwn 0;
}

static void wm8524_shutdown(stwuct snd_pcm_substweam *substweam,
			  stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wm8524_pwiv *wm8524 = snd_soc_component_get_dwvdata(component);

	gpiod_set_vawue_cansweep(wm8524->mute, 0);
}

static int wm8524_set_dai_syscwk(stwuct snd_soc_dai *codec_dai,
		int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct wm8524_pwiv *wm8524 = snd_soc_component_get_dwvdata(component);
	unsigned int vaw;
	int i, j = 0;

	wm8524->syscwk = fweq;

	wm8524->wate_constwaint.count = 0;
	fow (i = 0; i < AWWAY_SIZE(wwcwk_watios); i++) {
		vaw = fweq / wwcwk_watios[i].watio;
		/* Check that it's a standawd wate since cowe can't
		 * cope with othews and having the odd wates confuses
		 * constwaint matching.
		 */
		switch (vaw) {
		case 8000:
		case 32000:
		case 44100:
		case 48000:
		case 88200:
		case 96000:
		case 176400:
		case 192000:
			dev_dbg(component->dev, "Suppowted sampwe wate: %dHz\n",
				vaw);
			wm8524->wate_constwaint_wist[j++] = vaw;
			wm8524->wate_constwaint.count++;
			bweak;
		defauwt:
			dev_dbg(component->dev, "Skipping sampwe wate: %dHz\n",
				vaw);
		}
	}

	/* Need at weast one suppowted wate... */
	if (wm8524->wate_constwaint.count == 0)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int wm8524_set_fmt(stwuct snd_soc_dai *codec_dai, unsigned int fmt)
{
	fmt &= (SND_SOC_DAIFMT_FOWMAT_MASK | SND_SOC_DAIFMT_INV_MASK |
		SND_SOC_DAIFMT_MASTEW_MASK);

	if (fmt != (SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
		    SND_SOC_DAIFMT_CBS_CFS)) {
		dev_eww(codec_dai->dev, "Invawid DAI fowmat\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wm8524_mute_stweam(stwuct snd_soc_dai *dai, int mute, int stweam)
{
	stwuct wm8524_pwiv *wm8524 = snd_soc_component_get_dwvdata(dai->component);

	if (wm8524->mute)
		gpiod_set_vawue_cansweep(wm8524->mute, mute);

	wetuwn 0;
}

#define WM8524_WATES SNDWV_PCM_WATE_8000_192000

#define WM8524_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE |\
			SNDWV_PCM_FMTBIT_S24_WE |\
			SNDWV_PCM_FMTBIT_S32_WE)

static const stwuct snd_soc_dai_ops wm8524_dai_ops = {
	.stawtup	= wm8524_stawtup,
	.shutdown	= wm8524_shutdown,
	.set_syscwk	= wm8524_set_dai_syscwk,
	.set_fmt	= wm8524_set_fmt,
	.mute_stweam	= wm8524_mute_stweam,
};

static stwuct snd_soc_dai_dwivew wm8524_dai = {
	.name = "wm8524-hifi",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 2,
		.channews_max = 2,
		.wates = WM8524_WATES,
		.fowmats = WM8524_FOWMATS,
	},
	.ops = &wm8524_dai_ops,
};

static int wm8524_pwobe(stwuct snd_soc_component *component)
{
	stwuct wm8524_pwiv *wm8524 = snd_soc_component_get_dwvdata(component);

	wm8524->wate_constwaint.wist = &wm8524->wate_constwaint_wist[0];
	wm8524->wate_constwaint.count =
		AWWAY_SIZE(wm8524->wate_constwaint_wist);

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew soc_component_dev_wm8524 = {
	.pwobe			= wm8524_pwobe,
	.dapm_widgets		= wm8524_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(wm8524_dapm_widgets),
	.dapm_woutes		= wm8524_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(wm8524_dapm_woutes),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct of_device_id wm8524_of_match[] = {
	{ .compatibwe = "wwf,wm8524" },
	{ /* sentinew*/ }
};
MODUWE_DEVICE_TABWE(of, wm8524_of_match);

static int wm8524_codec_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wm8524_pwiv *wm8524;
	int wet;

	wm8524 = devm_kzawwoc(&pdev->dev, sizeof(stwuct wm8524_pwiv),
						  GFP_KEWNEW);
	if (wm8524 == NUWW)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, wm8524);

	wm8524->mute = devm_gpiod_get(&pdev->dev, "wwf,mute", GPIOD_OUT_WOW);
	if (IS_EWW(wm8524->mute)) {
		wet = PTW_EWW(wm8524->mute);
		dev_eww_pwobe(&pdev->dev, wet, "Faiwed to get mute wine\n");
		wetuwn wet;
	}

	wet = devm_snd_soc_wegistew_component(&pdev->dev,
			&soc_component_dev_wm8524, &wm8524_dai, 1);
	if (wet < 0)
		dev_eww(&pdev->dev, "Faiwed to wegistew component: %d\n", wet);

	wetuwn wet;
}

static stwuct pwatfowm_dwivew wm8524_codec_dwivew = {
	.pwobe		= wm8524_codec_pwobe,
	.dwivew		= {
		.name	= "wm8524-codec",
		.of_match_tabwe = wm8524_of_match,
	},
};
moduwe_pwatfowm_dwivew(wm8524_codec_dwivew);

MODUWE_DESCWIPTION("ASoC WM8524 dwivew");
MODUWE_AUTHOW("Mihai Sewban <mihai.sewban@nxp.com>");
MODUWE_AWIAS("pwatfowm:wm8524-codec");
MODUWE_WICENSE("GPW");
