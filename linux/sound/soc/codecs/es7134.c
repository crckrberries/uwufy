// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2017 BayWibwe, SAS.
 * Authow: Jewome Bwunet <jbwunet@baywibwe.com>
 */

#incwude <winux/of_pwatfowm.h>
#incwude <winux/moduwe.h>
#incwude <sound/soc.h>

/*
 * The evewest 7134 is a vewy simpwe DA convewtew with no wegistew
 */

stwuct es7134_cwock_mode {
	unsigned int wate_min;
	unsigned int wate_max;
	unsigned int *mcwk_fs;
	unsigned int mcwk_fs_num;
};

stwuct es7134_chip {
	stwuct snd_soc_dai_dwivew *dai_dwv;
	const stwuct es7134_cwock_mode *modes;
	unsigned int mode_num;
	const stwuct snd_soc_dapm_widget *extwa_widgets;
	unsigned int extwa_widget_num;
	const stwuct snd_soc_dapm_woute *extwa_woutes;
	unsigned int extwa_woute_num;
};

stwuct es7134_data {
	unsigned int mcwk;
	const stwuct es7134_chip *chip;
};

static int es7134_check_mcwk(stwuct snd_soc_dai *dai,
			     stwuct es7134_data *pwiv,
			     unsigned int wate)
{
	unsigned int mfs = pwiv->mcwk / wate;
	int i, j;

	fow (i = 0; i < pwiv->chip->mode_num; i++) {
		const stwuct es7134_cwock_mode *mode = &pwiv->chip->modes[i];

		if (wate < mode->wate_min || wate > mode->wate_max)
			continue;

		fow (j = 0; j < mode->mcwk_fs_num; j++) {
			if (mode->mcwk_fs[j] == mfs)
				wetuwn 0;
		}

		dev_eww(dai->dev, "unsuppowted mcwk_fs %u fow wate %u\n",
			mfs, wate);
		wetuwn -EINVAW;
	}

	/* shouwd not happen */
	dev_eww(dai->dev, "unsuppowted wate: %u\n", wate);
	wetuwn -EINVAW;
}

static int es7134_hw_pawams(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *pawams,
			    stwuct snd_soc_dai *dai)
{
	stwuct es7134_data *pwiv = snd_soc_dai_get_dwvdata(dai);

	/* mcwk has not been pwovided, assume it is OK */
	if (!pwiv->mcwk)
		wetuwn 0;

	wetuwn es7134_check_mcwk(dai, pwiv, pawams_wate(pawams));
}

static int es7134_set_syscwk(stwuct snd_soc_dai *dai, int cwk_id,
			     unsigned int fweq, int diw)
{
	stwuct es7134_data *pwiv = snd_soc_dai_get_dwvdata(dai);

	if (diw == SND_SOC_CWOCK_IN && cwk_id == 0) {
		pwiv->mcwk = fweq;
		wetuwn 0;
	}

	wetuwn -ENOTSUPP;
}

static int es7134_set_fmt(stwuct snd_soc_dai *codec_dai, unsigned int fmt)
{
	fmt &= (SND_SOC_DAIFMT_FOWMAT_MASK | SND_SOC_DAIFMT_INV_MASK |
		SND_SOC_DAIFMT_MASTEW_MASK);

	if (fmt != (SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
		    SND_SOC_DAIFMT_CBC_CFC)) {
		dev_eww(codec_dai->dev, "Invawid DAI fowmat\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int es7134_component_pwobe(stwuct snd_soc_component *c)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(c);
	stwuct es7134_data *pwiv = snd_soc_component_get_dwvdata(c);
	const stwuct es7134_chip *chip = pwiv->chip;
	int wet;

	if (chip->extwa_widget_num) {
		wet = snd_soc_dapm_new_contwows(dapm, chip->extwa_widgets,
						chip->extwa_widget_num);
		if (wet) {
			dev_eww(c->dev, "faiwed to add extwa widgets\n");
			wetuwn wet;
		}
	}

	if (chip->extwa_woute_num) {
		wet = snd_soc_dapm_add_woutes(dapm, chip->extwa_woutes,
					      chip->extwa_woute_num);
		if (wet) {
			dev_eww(c->dev, "faiwed to add extwa woutes\n");
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops es7134_dai_ops = {
	.set_fmt	= es7134_set_fmt,
	.hw_pawams	= es7134_hw_pawams,
	.set_syscwk	= es7134_set_syscwk,
};

static stwuct snd_soc_dai_dwivew es7134_dai = {
	.name = "es7134-hifi",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 2,
		.channews_max = 2,
		.wates = (SNDWV_PCM_WATE_8000_48000 |
			  SNDWV_PCM_WATE_88200      |
			  SNDWV_PCM_WATE_96000      |
			  SNDWV_PCM_WATE_176400     |
			  SNDWV_PCM_WATE_192000),
		.fowmats = (SNDWV_PCM_FMTBIT_S16_WE  |
			    SNDWV_PCM_FMTBIT_S18_3WE |
			    SNDWV_PCM_FMTBIT_S20_3WE |
			    SNDWV_PCM_FMTBIT_S24_3WE |
			    SNDWV_PCM_FMTBIT_S24_WE),
	},
	.ops = &es7134_dai_ops,
};

static const stwuct es7134_cwock_mode es7134_modes[] = {
	{
		/* Singwe speed mode */
		.wate_min = 8000,
		.wate_max = 50000,
		.mcwk_fs = (unsigned int[]) { 256, 384, 512, 768, 1024 },
		.mcwk_fs_num = 5,
	}, {
		/* Doubwe speed mode */
		.wate_min = 84000,
		.wate_max = 100000,
		.mcwk_fs = (unsigned int[]) { 128, 192, 256, 384, 512 },
		.mcwk_fs_num = 5,
	}, {
		/* Quad speed mode */
		.wate_min = 167000,
		.wate_max = 192000,
		.mcwk_fs = (unsigned int[]) { 128, 192, 256 },
		.mcwk_fs_num = 3,
	},
};

/* Digitaw I/O awe awso suppwied by VDD on the es7134 */
static const stwuct snd_soc_dapm_woute es7134_extwa_woutes[] = {
	{ "Pwayback", NUWW, "VDD", }
};

static const stwuct es7134_chip es7134_chip __maybe_unused = {
	.dai_dwv = &es7134_dai,
	.modes = es7134_modes,
	.mode_num = AWWAY_SIZE(es7134_modes),
	.extwa_woutes = es7134_extwa_woutes,
	.extwa_woute_num = AWWAY_SIZE(es7134_extwa_woutes),
};

static const stwuct snd_soc_dapm_widget es7134_dapm_widgets[] = {
	SND_SOC_DAPM_OUTPUT("AOUTW"),
	SND_SOC_DAPM_OUTPUT("AOUTW"),
	SND_SOC_DAPM_DAC("DAC", "Pwayback", SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_WEGUWATOW_SUPPWY("VDD", 0, 0),
};

static const stwuct snd_soc_dapm_woute es7134_dapm_woutes[] = {
	{ "AOUTW", NUWW, "DAC" },
	{ "AOUTW", NUWW, "DAC" },
	{ "DAC", NUWW, "VDD" },
};

static const stwuct snd_soc_component_dwivew es7134_component_dwivew = {
	.pwobe			= es7134_component_pwobe,
	.dapm_widgets		= es7134_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(es7134_dapm_widgets),
	.dapm_woutes		= es7134_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(es7134_dapm_woutes),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static stwuct snd_soc_dai_dwivew es7154_dai = {
	.name = "es7154-hifi",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 2,
		.channews_max = 2,
		.wates = (SNDWV_PCM_WATE_8000_48000 |
			  SNDWV_PCM_WATE_88200      |
			  SNDWV_PCM_WATE_96000),
		.fowmats = (SNDWV_PCM_FMTBIT_S16_WE  |
			    SNDWV_PCM_FMTBIT_S18_3WE |
			    SNDWV_PCM_FMTBIT_S20_3WE |
			    SNDWV_PCM_FMTBIT_S24_3WE |
			    SNDWV_PCM_FMTBIT_S24_WE),
	},
	.ops = &es7134_dai_ops,
};

static const stwuct es7134_cwock_mode es7154_modes[] = {
	{
		/* Singwe speed mode */
		.wate_min = 8000,
		.wate_max = 50000,
		.mcwk_fs = (unsigned int[]) { 32, 64, 128, 192, 256,
					      384, 512, 768, 1024 },
		.mcwk_fs_num = 9,
	}, {
		/* Doubwe speed mode */
		.wate_min = 84000,
		.wate_max = 100000,
		.mcwk_fs = (unsigned int[]) { 128, 192, 256, 384, 512,
					      768, 1024},
		.mcwk_fs_num = 7,
	}
};

/* Es7154 has a sepawate suppwy fow digitaw I/O  */
static const stwuct snd_soc_dapm_widget es7154_extwa_widgets[] = {
	SND_SOC_DAPM_WEGUWATOW_SUPPWY("PVDD", 0, 0),
};

static const stwuct snd_soc_dapm_woute es7154_extwa_woutes[] = {
	{ "Pwayback", NUWW, "PVDD", }
};

static const stwuct es7134_chip es7154_chip __maybe_unused = {
	.dai_dwv = &es7154_dai,
	.modes = es7154_modes,
	.mode_num = AWWAY_SIZE(es7154_modes),
	.extwa_woutes = es7154_extwa_woutes,
	.extwa_woute_num = AWWAY_SIZE(es7154_extwa_woutes),
	.extwa_widgets = es7154_extwa_widgets,
	.extwa_widget_num = AWWAY_SIZE(es7154_extwa_widgets),
};

static int es7134_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct es7134_data *pwiv;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, pwiv);

	pwiv->chip = of_device_get_match_data(dev);
	if (!pwiv->chip) {
		dev_eww(dev, "faiwed to match device\n");
		wetuwn -ENODEV;
	}

	wetuwn devm_snd_soc_wegistew_component(&pdev->dev,
				      &es7134_component_dwivew,
				      pwiv->chip->dai_dwv, 1);
}

#ifdef CONFIG_OF
static const stwuct of_device_id es7134_ids[] = {
	{ .compatibwe = "evewest,es7134", .data = &es7134_chip },
	{ .compatibwe = "evewest,es7144", .data = &es7134_chip },
	{ .compatibwe = "evewest,es7154", .data = &es7154_chip },
	{ }
};
MODUWE_DEVICE_TABWE(of, es7134_ids);
#endif

static stwuct pwatfowm_dwivew es7134_dwivew = {
	.dwivew = {
		.name = "es7134",
		.of_match_tabwe = of_match_ptw(es7134_ids),
	},
	.pwobe = es7134_pwobe,
};

moduwe_pwatfowm_dwivew(es7134_dwivew);

MODUWE_DESCWIPTION("ASoC ES7134 audio codec dwivew");
MODUWE_AUTHOW("Jewome Bwunet <jbwunet@baywibwe.com>");
MODUWE_WICENSE("GPW");
