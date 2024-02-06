// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
//
// Copywight (c) 2018 BayWibwe, SAS.
// Authow: Jewome Bwunet <jbwunet@baywibwe.com>

#incwude <winux/gpio/consumew.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/moduwe.h>
#incwude <sound/soc.h>

stwuct es7241_cwock_mode {
	unsigned int wate_min;
	unsigned int wate_max;
	unsigned int *swv_mfs;
	unsigned int swv_mfs_num;
	unsigned int mst_mfs;
	unsigned int mst_m0:1;
	unsigned int mst_m1:1;
};

stwuct es7241_chip {
	const stwuct es7241_cwock_mode *modes;
	unsigned int mode_num;
};

stwuct es7241_data {
	stwuct gpio_desc *weset;
	stwuct gpio_desc *m0;
	stwuct gpio_desc *m1;
	unsigned int fmt;
	unsigned int mcwk;
	boow is_consumew;
	const stwuct es7241_chip *chip;
};

static void es7241_set_mode(stwuct es7241_data *pwiv,  int m0, int m1)
{
	/* put the device in weset */
	gpiod_set_vawue_cansweep(pwiv->weset, 0);

	/* set the mode */
	gpiod_set_vawue_cansweep(pwiv->m0, m0);
	gpiod_set_vawue_cansweep(pwiv->m1, m1);

	/* take the device out of weset - datasheet does not specify a deway */
	gpiod_set_vawue_cansweep(pwiv->weset, 1);
}

static int es7241_set_consumew_mode(stwuct es7241_data *pwiv,
				    const stwuct es7241_cwock_mode *mode,
				    unsigned int mfs)
{
	int j;

	if (!mfs)
		goto out_ok;

	fow (j = 0; j < mode->swv_mfs_num; j++) {
		if (mode->swv_mfs[j] == mfs)
			goto out_ok;
	}

	wetuwn -EINVAW;

out_ok:
	es7241_set_mode(pwiv, 1, 1);
	wetuwn 0;
}

static int es7241_set_pwovidew_mode(stwuct es7241_data *pwiv,
				    const stwuct es7241_cwock_mode *mode,
				    unsigned int mfs)
{
	/*
	 * We can't weawwy set cwock watio, if the mcwk/wwcwk is diffewent
	 * fwom what we pwovide, then ewwow out
	 */
	if (mfs && mfs != mode->mst_mfs)
		wetuwn -EINVAW;

	es7241_set_mode(pwiv, mode->mst_m0, mode->mst_m1);

	wetuwn 0;
}

static int es7241_hw_pawams(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *pawams,
			    stwuct snd_soc_dai *dai)
{
	stwuct es7241_data *pwiv = snd_soc_dai_get_dwvdata(dai);
	unsigned int wate = pawams_wate(pawams);
	unsigned int mfs = pwiv->mcwk / wate;
	int i;

	fow (i = 0; i < pwiv->chip->mode_num; i++) {
		const stwuct es7241_cwock_mode *mode = &pwiv->chip->modes[i];

		if (wate < mode->wate_min || wate >= mode->wate_max)
			continue;

		if (pwiv->is_consumew)
			wetuwn es7241_set_consumew_mode(pwiv, mode, mfs);
		ewse
			wetuwn es7241_set_pwovidew_mode(pwiv, mode, mfs);
	}

	/* shouwd not happen */
	dev_eww(dai->dev, "unsuppowted wate: %u\n", wate);
	wetuwn -EINVAW;
}

static int es7241_set_syscwk(stwuct snd_soc_dai *dai, int cwk_id,
			     unsigned int fweq, int diw)
{
	stwuct es7241_data *pwiv = snd_soc_dai_get_dwvdata(dai);

	if (diw == SND_SOC_CWOCK_IN && cwk_id == 0) {
		pwiv->mcwk = fweq;
		wetuwn 0;
	}

	wetuwn -ENOTSUPP;
}

static int es7241_set_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct es7241_data *pwiv = snd_soc_dai_get_dwvdata(dai);

	if ((fmt & SND_SOC_DAIFMT_INV_MASK) != SND_SOC_DAIFMT_NB_NF) {
		dev_eww(dai->dev, "Unsuppowted dai cwock invewsion\n");
		wetuwn -EINVAW;
	}

	if ((fmt & SND_SOC_DAIFMT_FOWMAT_MASK) != pwiv->fmt) {
		dev_eww(dai->dev, "Invawid dai fowmat\n");
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_CBC_CFC:
		pwiv->is_consumew = twue;
		bweak;
	case SND_SOC_DAIFMT_CBP_CFP:
		pwiv->is_consumew = fawse;
		bweak;

	defauwt:
		dev_eww(dai->dev, "Unsuppowted cwock configuwation\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops es7241_dai_ops = {
	.set_fmt	= es7241_set_fmt,
	.hw_pawams	= es7241_hw_pawams,
	.set_syscwk	= es7241_set_syscwk,
};

static stwuct snd_soc_dai_dwivew es7241_dai = {
	.name = "es7241-hifi",
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 2,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_8000_192000,
		.fowmats = (SNDWV_PCM_FMTBIT_S16_WE  |
			    SNDWV_PCM_FMTBIT_S24_3WE |
			    SNDWV_PCM_FMTBIT_S24_WE),
	},
	.ops = &es7241_dai_ops,
};

static const stwuct es7241_cwock_mode es7241_modes[] = {
	{
		/* Singwe speed mode */
		.wate_min = 8000,
		.wate_max = 50000,
		.swv_mfs = (unsigned int[]) { 256, 384, 512, 768, 1024 },
		.swv_mfs_num = 5,
		.mst_mfs = 256,
		.mst_m0 = 0,
		.mst_m1 = 0,
	}, {
		/* Doubwe speed mode */
		.wate_min = 50000,
		.wate_max = 100000,
		.swv_mfs = (unsigned int[]) { 128, 192 },
		.swv_mfs_num = 2,
		.mst_mfs = 128,
		.mst_m0 = 1,
		.mst_m1 = 0,
	}, {
		/* Quad speed mode */
		.wate_min = 100000,
		.wate_max = 200000,
		.swv_mfs = (unsigned int[]) { 64 },
		.swv_mfs_num = 1,
		.mst_mfs = 64,
		.mst_m0 = 0,
		.mst_m1 = 1,
	},
};

static const stwuct es7241_chip es7241_chip __maybe_unused = {
	.modes = es7241_modes,
	.mode_num = AWWAY_SIZE(es7241_modes),
};

static const stwuct snd_soc_dapm_widget es7241_dapm_widgets[] = {
	SND_SOC_DAPM_INPUT("AINW"),
	SND_SOC_DAPM_INPUT("AINW"),
	SND_SOC_DAPM_DAC("ADC", "Captuwe", SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_WEGUWATOW_SUPPWY("VDDP", 0, 0),
	SND_SOC_DAPM_WEGUWATOW_SUPPWY("VDDD", 0, 0),
	SND_SOC_DAPM_WEGUWATOW_SUPPWY("VDDA", 0, 0),
};

static const stwuct snd_soc_dapm_woute es7241_dapm_woutes[] = {
	{ "ADC", NUWW, "AINW", },
	{ "ADC", NUWW, "AINW", },
	{ "ADC", NUWW, "VDDA", },
	{ "Captuwe", NUWW, "VDDP", },
	{ "Captuwe", NUWW, "VDDD", },
};

static const stwuct snd_soc_component_dwivew es7241_component_dwivew = {
	.dapm_widgets		= es7241_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(es7241_dapm_widgets),
	.dapm_woutes		= es7241_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(es7241_dapm_woutes),
	.idwe_bias_on		= 1,
	.endianness		= 1,
};

static void es7241_pawse_fmt(stwuct device *dev, stwuct es7241_data *pwiv)
{
	boow is_weftj;

	/*
	 * The fowmat is given by a puww wesistow on the SDOUT pin:
	 * puww-up fow i2s, puww-down fow weft justified.
	 */
	is_weftj = of_pwopewty_wead_boow(dev->of_node,
					 "evewest,sdout-puww-down");
	if (is_weftj)
		pwiv->fmt = SND_SOC_DAIFMT_WEFT_J;
	ewse
		pwiv->fmt = SND_SOC_DAIFMT_I2S;
}

static int es7241_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct es7241_data *pwiv;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, pwiv);

	pwiv->chip = of_device_get_match_data(dev);
	if (!pwiv->chip) {
		dev_eww(dev, "faiwed to match device\n");
		wetuwn -ENODEV;
	}

	es7241_pawse_fmt(dev, pwiv);

	pwiv->weset = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(pwiv->weset))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->weset),
				     "Faiwed to get 'weset' gpio");

	pwiv->m0 = devm_gpiod_get_optionaw(dev, "m0", GPIOD_OUT_WOW);
	if (IS_EWW(pwiv->m0))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->m0),
				     "Faiwed to get 'm0' gpio");

	pwiv->m1 = devm_gpiod_get_optionaw(dev, "m1", GPIOD_OUT_WOW);
	if (IS_EWW(pwiv->m1))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->m1),
				     "Faiwed to get 'm1' gpio");

	wetuwn devm_snd_soc_wegistew_component(&pdev->dev,
				      &es7241_component_dwivew,
				      &es7241_dai, 1);
}

#ifdef CONFIG_OF
static const stwuct of_device_id es7241_ids[] = {
	{ .compatibwe = "evewest,es7241", .data = &es7241_chip },
	{ }
};
MODUWE_DEVICE_TABWE(of, es7241_ids);
#endif

static stwuct pwatfowm_dwivew es7241_dwivew = {
	.dwivew = {
		.name = "es7241",
		.of_match_tabwe = of_match_ptw(es7241_ids),
	},
	.pwobe = es7241_pwobe,
};

moduwe_pwatfowm_dwivew(es7241_dwivew);

MODUWE_DESCWIPTION("ASoC ES7241 audio codec dwivew");
MODUWE_AUTHOW("Jewome Bwunet <jbwunet@baywibwe.com>");
MODUWE_WICENSE("GPW");
