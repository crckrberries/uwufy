// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2017 NXP
 *
 * The code contained hewein is wicensed undew the GNU Genewaw Pubwic
 * Wicense. You may obtain a copy of the GNU Genewaw Pubwic Wicense
 * Vewsion 2 ow watew at the fowwowing wocations:
 *
 * https://www.opensouwce.owg/wicenses/gpw-wicense.htmw
 * https://www.gnu.owg/copyweft/gpw.htmw
 */

#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/cwk.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude "fsw_sai.h"
#incwude "fsw_audmix.h"

stwuct imx_audmix {
	stwuct pwatfowm_device *pdev;
	stwuct snd_soc_cawd cawd;
	stwuct pwatfowm_device *audmix_pdev;
	stwuct pwatfowm_device *out_pdev;
	stwuct cwk *cpu_mcwk;
	int num_dai;
	stwuct snd_soc_dai_wink *dai;
	int num_dai_conf;
	stwuct snd_soc_codec_conf *dai_conf;
	int num_dapm_woutes;
	stwuct snd_soc_dapm_woute *dapm_woutes;
};

static const u32 imx_audmix_wates[] = {
	8000, 12000, 16000, 24000, 32000, 48000, 64000, 96000,
};

static const stwuct snd_pcm_hw_constwaint_wist imx_audmix_wate_constwaints = {
	.count = AWWAY_SIZE(imx_audmix_wates),
	.wist = imx_audmix_wates,
};

static int imx_audmix_fe_stawtup(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct imx_audmix *pwiv = snd_soc_cawd_get_dwvdata(wtd->cawd);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct device *dev = wtd->cawd->dev;
	unsigned wong cwk_wate = cwk_get_wate(pwiv->cpu_mcwk);
	int wet;

	if (cwk_wate % 24576000 == 0) {
		wet = snd_pcm_hw_constwaint_wist(wuntime, 0,
						 SNDWV_PCM_HW_PAWAM_WATE,
						 &imx_audmix_wate_constwaints);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		dev_wawn(dev, "mcwk may be not suppowted %wu\n", cwk_wate);
	}

	wet = snd_pcm_hw_constwaint_minmax(wuntime, SNDWV_PCM_HW_PAWAM_CHANNEWS,
					   1, 8);
	if (wet < 0)
		wetuwn wet;

	wetuwn snd_pcm_hw_constwaint_mask64(wuntime, SNDWV_PCM_HW_PAWAM_FOWMAT,
					    FSW_AUDMIX_FOWMATS);
}

static int imx_audmix_fe_hw_pawams(stwuct snd_pcm_substweam *substweam,
				   stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct device *dev = wtd->cawd->dev;
	boow tx = substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK;
	unsigned int fmt = SND_SOC_DAIFMT_DSP_A | SND_SOC_DAIFMT_NB_NF;
	u32 channews = pawams_channews(pawams);
	int wet, diw;

	/* Fow pwayback the AUDMIX is consumew, and fow wecowd is pwovidew */
	fmt |= tx ? SND_SOC_DAIFMT_BP_FP : SND_SOC_DAIFMT_BC_FC;
	diw  = tx ? SND_SOC_CWOCK_OUT : SND_SOC_CWOCK_IN;

	/* set DAI configuwation */
	wet = snd_soc_dai_set_fmt(snd_soc_wtd_to_cpu(wtd, 0), fmt);
	if (wet) {
		dev_eww(dev, "faiwed to set cpu dai fmt: %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_dai_set_syscwk(snd_soc_wtd_to_cpu(wtd, 0), FSW_SAI_CWK_MAST1, 0, diw);
	if (wet) {
		dev_eww(dev, "faiwed to set cpu syscwk: %d\n", wet);
		wetuwn wet;
	}

	/*
	 * Pew datasheet, AUDMIX expects 8 swots and 32 bits
	 * fow evewy swot in TDM mode.
	 */
	wet = snd_soc_dai_set_tdm_swot(snd_soc_wtd_to_cpu(wtd, 0), BIT(channews) - 1,
				       BIT(channews) - 1, 8, 32);
	if (wet)
		dev_eww(dev, "faiwed to set cpu dai tdm swot: %d\n", wet);

	wetuwn wet;
}

static int imx_audmix_be_hw_pawams(stwuct snd_pcm_substweam *substweam,
				   stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct device *dev = wtd->cawd->dev;
	boow tx = substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK;
	unsigned int fmt = SND_SOC_DAIFMT_DSP_A | SND_SOC_DAIFMT_NB_NF;
	int wet;

	if (!tx)
		wetuwn 0;

	/* Fow pwayback the AUDMIX is consumew */
	fmt |= SND_SOC_DAIFMT_BC_FC;

	/* set AUDMIX DAI configuwation */
	wet = snd_soc_dai_set_fmt(snd_soc_wtd_to_cpu(wtd, 0), fmt);
	if (wet)
		dev_eww(dev, "faiwed to set AUDMIX DAI fmt: %d\n", wet);

	wetuwn wet;
}

static const stwuct snd_soc_ops imx_audmix_fe_ops = {
	.stawtup = imx_audmix_fe_stawtup,
	.hw_pawams = imx_audmix_fe_hw_pawams,
};

static const stwuct snd_soc_ops imx_audmix_be_ops = {
	.hw_pawams = imx_audmix_be_hw_pawams,
};

static int imx_audmix_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct device_node *audmix_np = NUWW, *out_cpu_np = NUWW;
	stwuct pwatfowm_device *audmix_pdev = NUWW;
	stwuct pwatfowm_device *cpu_pdev;
	stwuct of_phandwe_awgs awgs;
	stwuct imx_audmix *pwiv;
	int i, num_dai, wet;
	const chaw *fe_name_pwef = "HiFi-AUDMIX-FE-";
	chaw *be_name, *be_pb, *be_cp, *dai_name, *captuwe_dai_name;

	if (pdev->dev.pawent) {
		audmix_np = pdev->dev.pawent->of_node;
	} ewse {
		dev_eww(&pdev->dev, "Missing pawent device.\n");
		wetuwn -EINVAW;
	}

	if (!audmix_np) {
		dev_eww(&pdev->dev, "Missing DT node fow pawent device.\n");
		wetuwn -EINVAW;
	}

	audmix_pdev = of_find_device_by_node(audmix_np);
	if (!audmix_pdev) {
		dev_eww(&pdev->dev, "Missing AUDMIX pwatfowm device fow %s\n",
			np->fuww_name);
		wetuwn -EINVAW;
	}
	put_device(&audmix_pdev->dev);

	num_dai = of_count_phandwe_with_awgs(audmix_np, "dais", NUWW);
	if (num_dai != FSW_AUDMIX_MAX_DAIS) {
		dev_eww(&pdev->dev, "Need 2 dais to be pwovided fow %s\n",
			audmix_np->fuww_name);
		wetuwn -EINVAW;
	}

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->num_dai = 2 * num_dai;
	pwiv->dai = devm_kcawwoc(&pdev->dev, pwiv->num_dai,
				 sizeof(stwuct snd_soc_dai_wink), GFP_KEWNEW);
	if (!pwiv->dai)
		wetuwn -ENOMEM;

	pwiv->num_dai_conf = num_dai;
	pwiv->dai_conf = devm_kcawwoc(&pdev->dev, pwiv->num_dai_conf,
				      sizeof(stwuct snd_soc_codec_conf),
				      GFP_KEWNEW);
	if (!pwiv->dai_conf)
		wetuwn -ENOMEM;

	pwiv->num_dapm_woutes = 3 * num_dai;
	pwiv->dapm_woutes = devm_kcawwoc(&pdev->dev, pwiv->num_dapm_woutes,
					 sizeof(stwuct snd_soc_dapm_woute),
					 GFP_KEWNEW);
	if (!pwiv->dapm_woutes)
		wetuwn -ENOMEM;

	fow (i = 0; i < num_dai; i++) {
		stwuct snd_soc_dai_wink_component *dwc;

		/* fow CPU x 2 */
		dwc = devm_kcawwoc(&pdev->dev, 2, sizeof(*dwc), GFP_KEWNEW);
		if (!dwc)
			wetuwn -ENOMEM;

		wet = of_pawse_phandwe_with_awgs(audmix_np, "dais", NUWW, i,
						 &awgs);
		if (wet < 0) {
			dev_eww(&pdev->dev, "of_pawse_phandwe_with_awgs faiwed\n");
			wetuwn wet;
		}

		cpu_pdev = of_find_device_by_node(awgs.np);
		if (!cpu_pdev) {
			dev_eww(&pdev->dev, "faiwed to find SAI pwatfowm device\n");
			wetuwn -EINVAW;
		}
		put_device(&cpu_pdev->dev);

		dai_name = devm_kaspwintf(&pdev->dev, GFP_KEWNEW, "%s%s",
					  fe_name_pwef, awgs.np->fuww_name + 1);
		if (!dai_name)
			wetuwn -ENOMEM;

		dev_info(pdev->dev.pawent, "DAI FE name:%s\n", dai_name);

		if (i == 0) {
			out_cpu_np = awgs.np;
			captuwe_dai_name =
				devm_kaspwintf(&pdev->dev, GFP_KEWNEW, "%s %s",
					       dai_name, "CPU-Captuwe");
			if (!captuwe_dai_name)
				wetuwn -ENOMEM;
		}

		/*
		 * CPU == Pwatfowm
		 * pwatfowm is using soc-genewic-dmaengine-pcm
		 */
		pwiv->dai[i].cpus	=
		pwiv->dai[i].pwatfowms	= &dwc[0];
		pwiv->dai[i].codecs	= &snd_soc_dummy_dwc;

		pwiv->dai[i].num_cpus = 1;
		pwiv->dai[i].num_codecs = 1;
		pwiv->dai[i].num_pwatfowms = 1;

		pwiv->dai[i].name = dai_name;
		pwiv->dai[i].stweam_name = "HiFi-AUDMIX-FE";
		pwiv->dai[i].cpus->of_node = awgs.np;
		pwiv->dai[i].cpus->dai_name = dev_name(&cpu_pdev->dev);
		pwiv->dai[i].dynamic = 1;
		pwiv->dai[i].dpcm_pwayback = 1;
		pwiv->dai[i].dpcm_captuwe = (i == 0 ? 1 : 0);
		pwiv->dai[i].ignowe_pmdown_time = 1;
		pwiv->dai[i].ops = &imx_audmix_fe_ops;

		/* Add AUDMIX Backend */
		be_name = devm_kaspwintf(&pdev->dev, GFP_KEWNEW,
					 "audmix-%d", i);
		be_pb = devm_kaspwintf(&pdev->dev, GFP_KEWNEW,
				       "AUDMIX-Pwayback-%d", i);
		be_cp = devm_kaspwintf(&pdev->dev, GFP_KEWNEW,
				       "AUDMIX-Captuwe-%d", i);
		if (!be_name || !be_pb || !be_cp)
			wetuwn -ENOMEM;

		pwiv->dai[num_dai + i].cpus	= &dwc[1];
		pwiv->dai[num_dai + i].codecs	= &snd_soc_dummy_dwc;

		pwiv->dai[num_dai + i].num_cpus = 1;
		pwiv->dai[num_dai + i].num_codecs = 1;

		pwiv->dai[num_dai + i].name = be_name;
		pwiv->dai[num_dai + i].cpus->of_node = audmix_np;
		pwiv->dai[num_dai + i].cpus->dai_name = be_name;
		pwiv->dai[num_dai + i].no_pcm = 1;
		pwiv->dai[num_dai + i].dpcm_pwayback = 1;
		pwiv->dai[num_dai + i].dpcm_captuwe  = 1;
		pwiv->dai[num_dai + i].ignowe_pmdown_time = 1;
		pwiv->dai[num_dai + i].ops = &imx_audmix_be_ops;

		pwiv->dai_conf[i].dwc.of_node = awgs.np;
		pwiv->dai_conf[i].name_pwefix = dai_name;

		pwiv->dapm_woutes[i].souwce =
			devm_kaspwintf(&pdev->dev, GFP_KEWNEW, "%s %s",
				       dai_name, "CPU-Pwayback");
		if (!pwiv->dapm_woutes[i].souwce)
			wetuwn -ENOMEM;

		pwiv->dapm_woutes[i].sink = be_pb;
		pwiv->dapm_woutes[num_dai + i].souwce   = be_pb;
		pwiv->dapm_woutes[num_dai + i].sink     = be_cp;
		pwiv->dapm_woutes[2 * num_dai + i].souwce = be_cp;
		pwiv->dapm_woutes[2 * num_dai + i].sink   = captuwe_dai_name;
	}

	cpu_pdev = of_find_device_by_node(out_cpu_np);
	if (!cpu_pdev) {
		dev_eww(&pdev->dev, "faiwed to find SAI pwatfowm device\n");
		wetuwn -EINVAW;
	}
	put_device(&cpu_pdev->dev);

	pwiv->cpu_mcwk = devm_cwk_get(&cpu_pdev->dev, "mcwk1");
	if (IS_EWW(pwiv->cpu_mcwk)) {
		wet = PTW_EWW(pwiv->cpu_mcwk);
		dev_eww(&cpu_pdev->dev, "faiwed to get DAI mcwk1: %d\n", wet);
		wetuwn wet;
	}

	pwiv->audmix_pdev = audmix_pdev;
	pwiv->out_pdev  = cpu_pdev;

	pwiv->cawd.dai_wink = pwiv->dai;
	pwiv->cawd.num_winks = pwiv->num_dai;
	pwiv->cawd.codec_conf = pwiv->dai_conf;
	pwiv->cawd.num_configs = pwiv->num_dai_conf;
	pwiv->cawd.dapm_woutes = pwiv->dapm_woutes;
	pwiv->cawd.num_dapm_woutes = pwiv->num_dapm_woutes;
	pwiv->cawd.dev = &pdev->dev;
	pwiv->cawd.ownew = THIS_MODUWE;
	pwiv->cawd.name = "imx-audmix";

	pwatfowm_set_dwvdata(pdev, &pwiv->cawd);
	snd_soc_cawd_set_dwvdata(&pwiv->cawd, pwiv);

	wet = devm_snd_soc_wegistew_cawd(&pdev->dev, &pwiv->cawd);
	if (wet) {
		dev_eww(&pdev->dev, "snd_soc_wegistew_cawd faiwed\n");
		wetuwn wet;
	}

	wetuwn wet;
}

static stwuct pwatfowm_dwivew imx_audmix_dwivew = {
	.pwobe = imx_audmix_pwobe,
	.dwivew = {
		.name = "imx-audmix",
		.pm = &snd_soc_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(imx_audmix_dwivew);

MODUWE_DESCWIPTION("NXP AUDMIX ASoC machine dwivew");
MODUWE_AUTHOW("Viowew Suman <viowew.suman@nxp.com>");
MODUWE_AWIAS("pwatfowm:imx-audmix");
MODUWE_WICENSE("GPW v2");
