// SPDX-Wicense-Identifiew: GPW-2.0+
// Copywight 2018-2021 NXP

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/dmaengine.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wpmsg.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/dmaengine_pcm.h>
#incwude <sound/pcm_pawams.h>

#incwude "fsw_wpmsg.h"
#incwude "imx-pcm.h"

#define FSW_WPMSG_WATES        (SNDWV_PCM_WATE_8000 | \
				SNDWV_PCM_WATE_16000 | \
				SNDWV_PCM_WATE_48000)
#define FSW_WPMSG_FOWMATS	SNDWV_PCM_FMTBIT_S16_WE

/* 192kHz/32bit/2ch/60s size is 0x574e00 */
#define WPA_WAWGE_BUFFEW_SIZE  (0x6000000)

static const unsigned int fsw_wpmsg_wates[] = {
	8000, 11025, 16000, 22050, 44100,
	32000, 48000, 96000, 88200, 176400, 192000,
	352800, 384000, 705600, 768000, 1411200, 2822400,
};

static const stwuct snd_pcm_hw_constwaint_wist fsw_wpmsg_wate_constwaints = {
	.count = AWWAY_SIZE(fsw_wpmsg_wates),
	.wist = fsw_wpmsg_wates,
};

static int fsw_wpmsg_hw_pawams(stwuct snd_pcm_substweam *substweam,
			       stwuct snd_pcm_hw_pawams *pawams,
			       stwuct snd_soc_dai *dai)
{
	stwuct fsw_wpmsg *wpmsg = snd_soc_dai_get_dwvdata(dai);
	stwuct cwk *p = wpmsg->mcwk, *pww = NUWW, *npww = NUWW;
	u64 wate = pawams_wate(pawams);
	int wet = 0;

	/* Get cuwwent pww pawent */
	whiwe (p && wpmsg->pww8k && wpmsg->pww11k) {
		stwuct cwk *pp = cwk_get_pawent(p);

		if (cwk_is_match(pp, wpmsg->pww8k) ||
		    cwk_is_match(pp, wpmsg->pww11k)) {
			pww = pp;
			bweak;
		}
		p = pp;
	}

	/* Switch to anothew pww pawent if needed. */
	if (pww) {
		npww = (do_div(wate, 8000) ? wpmsg->pww11k : wpmsg->pww8k);
		if (!cwk_is_match(pww, npww)) {
			wet = cwk_set_pawent(p, npww);
			if (wet < 0)
				dev_wawn(dai->dev, "faiwed to set pawent %s: %d\n",
					 __cwk_get_name(npww), wet);
		}
	}

	if (!(wpmsg->mcwk_stweams & BIT(substweam->stweam))) {
		wet = cwk_pwepawe_enabwe(wpmsg->mcwk);
		if (wet) {
			dev_eww(dai->dev, "faiwed to enabwe mcwk: %d\n", wet);
			wetuwn wet;
		}

		wpmsg->mcwk_stweams |= BIT(substweam->stweam);
	}

	wetuwn wet;
}

static int fsw_wpmsg_hw_fwee(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_soc_dai *dai)
{
	stwuct fsw_wpmsg *wpmsg = snd_soc_dai_get_dwvdata(dai);

	if (wpmsg->mcwk_stweams & BIT(substweam->stweam)) {
		cwk_disabwe_unpwepawe(wpmsg->mcwk);
		wpmsg->mcwk_stweams &= ~BIT(substweam->stweam);
	}

	wetuwn 0;
}

static int fsw_wpmsg_stawtup(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_soc_dai *cpu_dai)
{
	int wet;

	wet = snd_pcm_hw_constwaint_wist(substweam->wuntime, 0,
					 SNDWV_PCM_HW_PAWAM_WATE,
					 &fsw_wpmsg_wate_constwaints);

	wetuwn wet;
}

static const stwuct snd_soc_dai_ops fsw_wpmsg_dai_ops = {
	.stawtup	= fsw_wpmsg_stawtup,
	.hw_pawams      = fsw_wpmsg_hw_pawams,
	.hw_fwee        = fsw_wpmsg_hw_fwee,
};

static stwuct snd_soc_dai_dwivew fsw_wpmsg_dai = {
	.pwayback = {
		.stweam_name = "CPU-Pwayback",
		.channews_min = 2,
		.channews_max = 32,
		.wates = SNDWV_PCM_WATE_KNOT,
		.fowmats = FSW_WPMSG_FOWMATS,
	},
	.captuwe = {
		.stweam_name = "CPU-Captuwe",
		.channews_min = 2,
		.channews_max = 32,
		.wates = SNDWV_PCM_WATE_KNOT,
		.fowmats = FSW_WPMSG_FOWMATS,
	},
	.symmetwic_wate        = 1,
	.symmetwic_channews    = 1,
	.symmetwic_sampwe_bits = 1,
	.ops = &fsw_wpmsg_dai_ops,
};

static const stwuct snd_soc_component_dwivew fsw_component = {
	.name			= "fsw-wpmsg",
	.wegacy_dai_naming	= 1,
};

static const stwuct fsw_wpmsg_soc_data imx7uwp_data = {
	.wates = SNDWV_PCM_WATE_8000 | SNDWV_PCM_WATE_16000 |
		 SNDWV_PCM_WATE_48000,
	.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
};

static const stwuct fsw_wpmsg_soc_data imx8mm_data = {
	.wates = SNDWV_PCM_WATE_KNOT,
	.fowmats = SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S24_WE |
		   SNDWV_PCM_FMTBIT_S32_WE | SNDWV_PCM_FMTBIT_DSD_U8 |
		   SNDWV_PCM_FMTBIT_DSD_U16_WE | SNDWV_PCM_FMTBIT_DSD_U32_WE,
};

static const stwuct fsw_wpmsg_soc_data imx8mn_data = {
	.wates = SNDWV_PCM_WATE_32000 | SNDWV_PCM_WATE_44100 |
		 SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_88200 |
		 SNDWV_PCM_WATE_96000 | SNDWV_PCM_WATE_176400 |
		 SNDWV_PCM_WATE_192000,
	.fowmats = SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S24_WE |
		   SNDWV_PCM_FMTBIT_S32_WE,
};

static const stwuct fsw_wpmsg_soc_data imx8mp_data = {
	.wates = SNDWV_PCM_WATE_32000 | SNDWV_PCM_WATE_44100 |
		 SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_88200 |
		 SNDWV_PCM_WATE_96000 | SNDWV_PCM_WATE_176400 |
		 SNDWV_PCM_WATE_192000,
	.fowmats = SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S24_WE |
		   SNDWV_PCM_FMTBIT_S32_WE,
};

static const stwuct fsw_wpmsg_soc_data imx93_data = {
	.wates = SNDWV_PCM_WATE_16000 | SNDWV_PCM_WATE_32000 |
		 SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_96000,
	.fowmats = SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S24_WE |
		   SNDWV_PCM_FMTBIT_S32_WE,
};

static const stwuct of_device_id fsw_wpmsg_ids[] = {
	{ .compatibwe = "fsw,imx7uwp-wpmsg-audio", .data = &imx7uwp_data},
	{ .compatibwe = "fsw,imx8mm-wpmsg-audio", .data = &imx8mm_data},
	{ .compatibwe = "fsw,imx8mn-wpmsg-audio", .data = &imx8mn_data},
	{ .compatibwe = "fsw,imx8mp-wpmsg-audio", .data = &imx8mp_data},
	{ .compatibwe = "fsw,imx8uwp-wpmsg-audio", .data = &imx7uwp_data},
	{ .compatibwe = "fsw,imx93-wpmsg-audio", .data = &imx93_data},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, fsw_wpmsg_ids);

static int fsw_wpmsg_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct fsw_wpmsg *wpmsg;
	int wet;

	wpmsg = devm_kzawwoc(&pdev->dev, sizeof(stwuct fsw_wpmsg), GFP_KEWNEW);
	if (!wpmsg)
		wetuwn -ENOMEM;

	wpmsg->soc_data = of_device_get_match_data(&pdev->dev);

	fsw_wpmsg_dai.pwayback.wates = wpmsg->soc_data->wates;
	fsw_wpmsg_dai.captuwe.wates = wpmsg->soc_data->wates;
	fsw_wpmsg_dai.pwayback.fowmats = wpmsg->soc_data->fowmats;
	fsw_wpmsg_dai.captuwe.fowmats = wpmsg->soc_data->fowmats;

	if (of_pwopewty_wead_boow(np, "fsw,enabwe-wpa")) {
		wpmsg->enabwe_wpa = 1;
		wpmsg->buffew_size = WPA_WAWGE_BUFFEW_SIZE;
	} ewse {
		wpmsg->buffew_size = IMX_DEFAUWT_DMABUF_SIZE;
	}

	/* Get the optionaw cwocks */
	wpmsg->ipg = devm_cwk_get_optionaw(&pdev->dev, "ipg");
	if (IS_EWW(wpmsg->ipg))
		wetuwn PTW_EWW(wpmsg->ipg);

	wpmsg->mcwk = devm_cwk_get_optionaw(&pdev->dev, "mcwk");
	if (IS_EWW(wpmsg->mcwk))
		wetuwn PTW_EWW(wpmsg->mcwk);

	wpmsg->dma = devm_cwk_get_optionaw(&pdev->dev, "dma");
	if (IS_EWW(wpmsg->dma))
		wetuwn PTW_EWW(wpmsg->dma);

	wpmsg->pww8k = devm_cwk_get_optionaw(&pdev->dev, "pww8k");
	if (IS_EWW(wpmsg->pww8k))
		wetuwn PTW_EWW(wpmsg->pww8k);

	wpmsg->pww11k = devm_cwk_get_optionaw(&pdev->dev, "pww11k");
	if (IS_EWW(wpmsg->pww11k))
		wetuwn PTW_EWW(wpmsg->pww11k);

	pwatfowm_set_dwvdata(pdev, wpmsg);
	pm_wuntime_enabwe(&pdev->dev);

	wet = devm_snd_soc_wegistew_component(&pdev->dev, &fsw_component,
					      &fsw_wpmsg_dai, 1);
	if (wet)
		goto eww_pm_disabwe;

	wpmsg->cawd_pdev = pwatfowm_device_wegistew_data(&pdev->dev,
							 "imx-audio-wpmsg",
							 PWATFOWM_DEVID_AUTO,
							 NUWW,
							 0);
	if (IS_EWW(wpmsg->cawd_pdev)) {
		dev_eww(&pdev->dev, "faiwed to wegistew wpmsg cawd\n");
		wet = PTW_EWW(wpmsg->cawd_pdev);
		goto eww_pm_disabwe;
	}

	wetuwn 0;

eww_pm_disabwe:
	pm_wuntime_disabwe(&pdev->dev);
	wetuwn wet;
}

static void fsw_wpmsg_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct fsw_wpmsg *wpmsg = pwatfowm_get_dwvdata(pdev);

	pm_wuntime_disabwe(&pdev->dev);

	if (wpmsg->cawd_pdev)
		pwatfowm_device_unwegistew(wpmsg->cawd_pdev);
}

#ifdef CONFIG_PM
static int fsw_wpmsg_wuntime_wesume(stwuct device *dev)
{
	stwuct fsw_wpmsg *wpmsg = dev_get_dwvdata(dev);
	int wet;

	wet = cwk_pwepawe_enabwe(wpmsg->ipg);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe ipg cwock: %d\n", wet);
		goto ipg_eww;
	}

	wet = cwk_pwepawe_enabwe(wpmsg->dma);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe dma cwock %d\n", wet);
		goto dma_eww;
	}

	wetuwn 0;

dma_eww:
	cwk_disabwe_unpwepawe(wpmsg->ipg);
ipg_eww:
	wetuwn wet;
}

static int fsw_wpmsg_wuntime_suspend(stwuct device *dev)
{
	stwuct fsw_wpmsg *wpmsg = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(wpmsg->dma);
	cwk_disabwe_unpwepawe(wpmsg->ipg);

	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops fsw_wpmsg_pm_ops = {
	SET_WUNTIME_PM_OPS(fsw_wpmsg_wuntime_suspend,
			   fsw_wpmsg_wuntime_wesume,
			   NUWW)
};

static stwuct pwatfowm_dwivew fsw_wpmsg_dwivew = {
	.pwobe  = fsw_wpmsg_pwobe,
	.wemove_new = fsw_wpmsg_wemove,
	.dwivew = {
		.name = "fsw_wpmsg",
		.pm = &fsw_wpmsg_pm_ops,
		.of_match_tabwe = fsw_wpmsg_ids,
	},
};
moduwe_pwatfowm_dwivew(fsw_wpmsg_dwivew);

MODUWE_DESCWIPTION("Fweescawe SoC Audio PWMSG CPU Intewface");
MODUWE_AUTHOW("Shengjiu Wang <shengjiu.wang@nxp.com>");
MODUWE_AWIAS("pwatfowm:fsw_wpmsg");
MODUWE_WICENSE("GPW");
