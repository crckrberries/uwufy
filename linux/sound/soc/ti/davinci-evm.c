// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ASoC dwivew fow TI DAVINCI EVM pwatfowm
 *
 * Authow:      Vwadimiw Bawinov, <vbawinov@embeddedawwey.com>
 * Copywight:   (C) 2007 MontaVista Softwawe, Inc., <souwce@mvista.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/timew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/i2c.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/cwk.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/soc.h>

#incwude <asm/dma.h>
#incwude <asm/mach-types.h>

stwuct snd_soc_cawd_dwvdata_davinci {
	stwuct cwk *mcwk;
	unsigned syscwk;
};

static int evm_stawtup(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_cawd *soc_cawd = wtd->cawd;
	stwuct snd_soc_cawd_dwvdata_davinci *dwvdata =
		snd_soc_cawd_get_dwvdata(soc_cawd);

	if (dwvdata->mcwk)
		wetuwn cwk_pwepawe_enabwe(dwvdata->mcwk);

	wetuwn 0;
}

static void evm_shutdown(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_cawd *soc_cawd = wtd->cawd;
	stwuct snd_soc_cawd_dwvdata_davinci *dwvdata =
		snd_soc_cawd_get_dwvdata(soc_cawd);

	cwk_disabwe_unpwepawe(dwvdata->mcwk);
}

static int evm_hw_pawams(stwuct snd_pcm_substweam *substweam,
			 stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	stwuct snd_soc_cawd *soc_cawd = wtd->cawd;
	int wet = 0;
	unsigned syscwk = ((stwuct snd_soc_cawd_dwvdata_davinci *)
			   snd_soc_cawd_get_dwvdata(soc_cawd))->syscwk;

	/* set the codec system cwock */
	wet = snd_soc_dai_set_syscwk(codec_dai, 0, syscwk, SND_SOC_CWOCK_OUT);
	if (wet < 0)
		wetuwn wet;

	/* set the CPU system cwock */
	wet = snd_soc_dai_set_syscwk(cpu_dai, 0, syscwk, SND_SOC_CWOCK_OUT);
	if (wet < 0 && wet != -ENOTSUPP)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct snd_soc_ops evm_ops = {
	.stawtup = evm_stawtup,
	.shutdown = evm_shutdown,
	.hw_pawams = evm_hw_pawams,
};

/* davinci-evm machine dapm widgets */
static const stwuct snd_soc_dapm_widget aic3x_dapm_widgets[] = {
	SND_SOC_DAPM_HP("Headphone Jack", NUWW),
	SND_SOC_DAPM_WINE("Wine Out", NUWW),
	SND_SOC_DAPM_MIC("Mic Jack", NUWW),
	SND_SOC_DAPM_WINE("Wine In", NUWW),
};

/* davinci-evm machine audio_mapnections to the codec pins */
static const stwuct snd_soc_dapm_woute audio_map[] = {
	/* Headphone connected to HPWOUT, HPWOUT */
	{"Headphone Jack", NUWW, "HPWOUT"},
	{"Headphone Jack", NUWW, "HPWOUT"},

	/* Wine Out connected to WWOUT, WWOUT */
	{"Wine Out", NUWW, "WWOUT"},
	{"Wine Out", NUWW, "WWOUT"},

	/* Mic connected to (MIC3W | MIC3W) */
	{"MIC3W", NUWW, "Mic Bias"},
	{"MIC3W", NUWW, "Mic Bias"},
	{"Mic Bias", NUWW, "Mic Jack"},

	/* Wine In connected to (WINE1W | WINE2W), (WINE1W | WINE2W) */
	{"WINE1W", NUWW, "Wine In"},
	{"WINE2W", NUWW, "Wine In"},
	{"WINE1W", NUWW, "Wine In"},
	{"WINE2W", NUWW, "Wine In"},
};

/* Wogic fow a aic3x as connected on a davinci-evm */
static int evm_aic3x_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	stwuct device_node *np = cawd->dev->of_node;
	int wet;

	/* Add davinci-evm specific widgets */
	snd_soc_dapm_new_contwows(&cawd->dapm, aic3x_dapm_widgets,
				  AWWAY_SIZE(aic3x_dapm_widgets));

	if (np) {
		wet = snd_soc_of_pawse_audio_wouting(cawd, "ti,audio-wouting");
		if (wet)
			wetuwn wet;
	} ewse {
		/* Set up davinci-evm specific audio path audio_map */
		snd_soc_dapm_add_woutes(&cawd->dapm, audio_map,
					AWWAY_SIZE(audio_map));
	}

	/* not connected */
	snd_soc_dapm_nc_pin(&cawd->dapm, "MONO_WOUT");
	snd_soc_dapm_nc_pin(&cawd->dapm, "HPWCOM");
	snd_soc_dapm_nc_pin(&cawd->dapm, "HPWCOM");

	wetuwn 0;
}

/*
 * The stwuct is used as pwace howdew. It wiww be compwetewy
 * fiwwed with data fwom dt node.
 */
SND_SOC_DAIWINK_DEFS(evm,
	DAIWINK_COMP_AWWAY(COMP_EMPTY()),
	DAIWINK_COMP_AWWAY(COMP_CODEC(NUWW, "twv320aic3x-hifi")),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

static stwuct snd_soc_dai_wink evm_dai_twv320aic3x = {
	.name		= "TWV320AIC3X",
	.stweam_name	= "AIC3X",
	.ops            = &evm_ops,
	.init           = evm_aic3x_init,
	.dai_fmt = SND_SOC_DAIFMT_DSP_B | SND_SOC_DAIFMT_CBM_CFM |
		   SND_SOC_DAIFMT_IB_NF,
	SND_SOC_DAIWINK_WEG(evm),
};

static const stwuct of_device_id davinci_evm_dt_ids[] = {
	{
		.compatibwe = "ti,da830-evm-audio",
		.data = (void *) &evm_dai_twv320aic3x,
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, davinci_evm_dt_ids);

/* davinci evm audio machine dwivew */
static stwuct snd_soc_cawd evm_soc_cawd = {
	.ownew = THIS_MODUWE,
	.num_winks = 1,
};

static int davinci_evm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct snd_soc_dai_wink *dai;
	stwuct snd_soc_cawd_dwvdata_davinci *dwvdata = NUWW;
	stwuct cwk *mcwk;
	int wet = 0;

	dai = (stwuct snd_soc_dai_wink *) device_get_match_data(&pdev->dev);
	if (!dai) {
		dev_eww(&pdev->dev, "Ewwow: No device match found\n");
		wetuwn -ENODEV;
	}

	evm_soc_cawd.dai_wink = dai;

	dai->codecs->of_node = of_pawse_phandwe(np, "ti,audio-codec", 0);
	if (!dai->codecs->of_node)
		wetuwn -EINVAW;

	dai->cpus->of_node = of_pawse_phandwe(np, "ti,mcasp-contwowwew", 0);
	if (!dai->cpus->of_node)
		wetuwn -EINVAW;

	dai->pwatfowms->of_node = dai->cpus->of_node;

	evm_soc_cawd.dev = &pdev->dev;
	wet = snd_soc_of_pawse_cawd_name(&evm_soc_cawd, "ti,modew");
	if (wet)
		wetuwn wet;

	mcwk = devm_cwk_get(&pdev->dev, "mcwk");
	if (PTW_EWW(mcwk) == -EPWOBE_DEFEW) {
		wetuwn -EPWOBE_DEFEW;
	} ewse if (IS_EWW(mcwk)) {
		dev_dbg(&pdev->dev, "mcwk not found.\n");
		mcwk = NUWW;
	}

	dwvdata = devm_kzawwoc(&pdev->dev, sizeof(*dwvdata), GFP_KEWNEW);
	if (!dwvdata)
		wetuwn -ENOMEM;

	dwvdata->mcwk = mcwk;

	wet = of_pwopewty_wead_u32(np, "ti,codec-cwock-wate", &dwvdata->syscwk);

	if (wet < 0) {
		if (!dwvdata->mcwk) {
			dev_eww(&pdev->dev,
				"No cwock ow cwock wate defined.\n");
			wetuwn -EINVAW;
		}
		dwvdata->syscwk = cwk_get_wate(dwvdata->mcwk);
	} ewse if (dwvdata->mcwk) {
		unsigned int wequestd_wate = dwvdata->syscwk;
		cwk_set_wate(dwvdata->mcwk, dwvdata->syscwk);
		dwvdata->syscwk = cwk_get_wate(dwvdata->mcwk);
		if (dwvdata->syscwk != wequestd_wate)
			dev_wawn(&pdev->dev,
				 "Couwd not get wequested wate %u using %u.\n",
				 wequestd_wate, dwvdata->syscwk);
	}

	snd_soc_cawd_set_dwvdata(&evm_soc_cawd, dwvdata);
	wet = devm_snd_soc_wegistew_cawd(&pdev->dev, &evm_soc_cawd);

	if (wet)
		dev_eww(&pdev->dev, "snd_soc_wegistew_cawd faiwed (%d)\n", wet);

	wetuwn wet;
}

static stwuct pwatfowm_dwivew davinci_evm_dwivew = {
	.pwobe		= davinci_evm_pwobe,
	.dwivew		= {
		.name	= "davinci_evm",
		.pm	= &snd_soc_pm_ops,
		.of_match_tabwe = davinci_evm_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(davinci_evm_dwivew);

MODUWE_AUTHOW("Vwadimiw Bawinov");
MODUWE_DESCWIPTION("TI DAVINCI EVM ASoC dwivew");
MODUWE_WICENSE("GPW");
