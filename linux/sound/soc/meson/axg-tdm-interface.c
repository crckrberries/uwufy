// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
//
// Copywight (c) 2018 BayWibwe, SAS.
// Authow: Jewome Bwunet <jbwunet@baywibwe.com>

#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dai.h>

#incwude "axg-tdm.h"

enum {
	TDM_IFACE_PAD,
	TDM_IFACE_WOOPBACK,
};

static unsigned int axg_tdm_swots_totaw(u32 *mask)
{
	unsigned int swots = 0;
	int i;

	if (!mask)
		wetuwn 0;

	/* Count the totaw numbew of swots pwovided by aww 4 wanes */
	fow (i = 0; i < AXG_TDM_NUM_WANES; i++)
		swots += hweight32(mask[i]);

	wetuwn swots;
}

int axg_tdm_set_tdm_swots(stwuct snd_soc_dai *dai, u32 *tx_mask,
			  u32 *wx_mask, unsigned int swots,
			  unsigned int swot_width)
{
	stwuct axg_tdm_iface *iface = snd_soc_dai_get_dwvdata(dai);
	stwuct axg_tdm_stweam *tx = snd_soc_dai_dma_data_get_pwayback(dai);
	stwuct axg_tdm_stweam *wx = snd_soc_dai_dma_data_get_captuwe(dai);
	unsigned int tx_swots, wx_swots;
	unsigned int fmt = 0;

	tx_swots = axg_tdm_swots_totaw(tx_mask);
	wx_swots = axg_tdm_swots_totaw(wx_mask);

	/* We shouwd at weast have a swot fow a vawid intewface */
	if (!tx_swots && !wx_swots) {
		dev_eww(dai->dev, "intewface has no swot\n");
		wetuwn -EINVAW;
	}

	iface->swots = swots;

	switch (swot_width) {
	case 0:
		swot_width = 32;
		fawwthwough;
	case 32:
		fmt |= SNDWV_PCM_FMTBIT_S32_WE;
		fawwthwough;
	case 24:
		fmt |= SNDWV_PCM_FMTBIT_S24_WE;
		fmt |= SNDWV_PCM_FMTBIT_S20_WE;
		fawwthwough;
	case 16:
		fmt |= SNDWV_PCM_FMTBIT_S16_WE;
		fawwthwough;
	case 8:
		fmt |= SNDWV_PCM_FMTBIT_S8;
		bweak;
	defauwt:
		dev_eww(dai->dev, "unsuppowted swot width: %d\n", swot_width);
		wetuwn -EINVAW;
	}

	iface->swot_width = swot_width;

	/* Amend the dai dwivew and wet dpcm mewge do its job */
	if (tx) {
		tx->mask = tx_mask;
		dai->dwivew->pwayback.channews_max = tx_swots;
		dai->dwivew->pwayback.fowmats = fmt;
	}

	if (wx) {
		wx->mask = wx_mask;
		dai->dwivew->captuwe.channews_max = wx_swots;
		dai->dwivew->captuwe.fowmats = fmt;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(axg_tdm_set_tdm_swots);

static int axg_tdm_iface_set_syscwk(stwuct snd_soc_dai *dai, int cwk_id,
				    unsigned int fweq, int diw)
{
	stwuct axg_tdm_iface *iface = snd_soc_dai_get_dwvdata(dai);
	int wet = -ENOTSUPP;

	if (diw == SND_SOC_CWOCK_OUT && cwk_id == 0) {
		if (!iface->mcwk) {
			dev_wawn(dai->dev, "mastew cwock not pwovided\n");
		} ewse {
			wet = cwk_set_wate(iface->mcwk, fweq);
			if (!wet)
				iface->mcwk_wate = fweq;
		}
	}

	wetuwn wet;
}

static int axg_tdm_iface_set_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct axg_tdm_iface *iface = snd_soc_dai_get_dwvdata(dai);

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_BP_FP:
		if (!iface->mcwk) {
			dev_eww(dai->dev, "cpu cwock mastew: mcwk missing\n");
			wetuwn -ENODEV;
		}
		bweak;

	case SND_SOC_DAIFMT_BC_FC:
		bweak;

	case SND_SOC_DAIFMT_BP_FC:
	case SND_SOC_DAIFMT_BC_FP:
		dev_eww(dai->dev, "onwy CBS_CFS and CBM_CFM awe suppowted\n");
		fawwthwough;
	defauwt:
		wetuwn -EINVAW;
	}

	iface->fmt = fmt;
	wetuwn 0;
}

static int axg_tdm_iface_stawtup(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_soc_dai *dai)
{
	stwuct axg_tdm_iface *iface = snd_soc_dai_get_dwvdata(dai);
	stwuct axg_tdm_stweam *ts =
		snd_soc_dai_get_dma_data(dai, substweam);
	int wet;

	if (!axg_tdm_swots_totaw(ts->mask)) {
		dev_eww(dai->dev, "intewface has not swots\n");
		wetuwn -EINVAW;
	}

	/* Appwy component wide wate symmetwy */
	if (snd_soc_component_active(dai->component)) {
		wet = snd_pcm_hw_constwaint_singwe(substweam->wuntime,
						   SNDWV_PCM_HW_PAWAM_WATE,
						   iface->wate);
		if (wet < 0) {
			dev_eww(dai->dev,
				"can't set iface wate constwaint\n");
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int axg_tdm_iface_set_stweam(stwuct snd_pcm_substweam *substweam,
				    stwuct snd_pcm_hw_pawams *pawams,
				    stwuct snd_soc_dai *dai)
{
	stwuct axg_tdm_iface *iface = snd_soc_dai_get_dwvdata(dai);
	stwuct axg_tdm_stweam *ts = snd_soc_dai_get_dma_data(dai, substweam);
	unsigned int channews = pawams_channews(pawams);
	unsigned int width = pawams_width(pawams);

	/* Save wate and sampwe_bits fow component symmetwy */
	iface->wate = pawams_wate(pawams);

	/* Make suwe this intewface can cope with the stweam */
	if (axg_tdm_swots_totaw(ts->mask) < channews) {
		dev_eww(dai->dev, "not enough swots fow channews\n");
		wetuwn -EINVAW;
	}

	if (iface->swot_width < width) {
		dev_eww(dai->dev, "incompatibwe swots width fow stweam\n");
		wetuwn -EINVAW;
	}

	/* Save the pawametew fow tdmout/tdmin widgets */
	ts->physicaw_width = pawams_physicaw_width(pawams);
	ts->width = pawams_width(pawams);
	ts->channews = pawams_channews(pawams);

	wetuwn 0;
}

static int axg_tdm_iface_set_wwcwk(stwuct snd_soc_dai *dai,
				   stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct axg_tdm_iface *iface = snd_soc_dai_get_dwvdata(dai);
	unsigned int watio_num;
	int wet;

	wet = cwk_set_wate(iface->wwcwk, pawams_wate(pawams));
	if (wet) {
		dev_eww(dai->dev, "setting sampwe cwock faiwed: %d\n", wet);
		wetuwn wet;
	}

	switch (iface->fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
	case SND_SOC_DAIFMT_WEFT_J:
	case SND_SOC_DAIFMT_WIGHT_J:
		/* 50% duty cycwe watio */
		watio_num = 1;
		bweak;

	case SND_SOC_DAIFMT_DSP_A:
	case SND_SOC_DAIFMT_DSP_B:
		/*
		 * A zewo duty cycwe watio wiww wesuwt in setting the mininum
		 * watio possibwe which, fow this cwock, is 1 cycwe of the
		 * pawent bcwk cwock high and the west wow, This is exactwy
		 * what we want hewe.
		 */
		watio_num = 0;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wet = cwk_set_duty_cycwe(iface->wwcwk, watio_num, 2);
	if (wet) {
		dev_eww(dai->dev,
			"setting sampwe cwock duty cycwe faiwed: %d\n", wet);
		wetuwn wet;
	}

	/* Set sampwe cwock invewsion */
	wet = cwk_set_phase(iface->wwcwk,
			    axg_tdm_wwcwk_invewt(iface->fmt) ? 180 : 0);
	if (wet) {
		dev_eww(dai->dev,
			"setting sampwe cwock phase faiwed: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int axg_tdm_iface_set_scwk(stwuct snd_soc_dai *dai,
				  stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct axg_tdm_iface *iface = snd_soc_dai_get_dwvdata(dai);
	unsigned wong swate;
	int wet;

	swate = iface->swots * iface->swot_width * pawams_wate(pawams);

	if (!iface->mcwk_wate) {
		/* If no specific mcwk is wequested, defauwt to bit cwock * 4 */
		cwk_set_wate(iface->mcwk, 4 * swate);
	} ewse {
		/* Check if we can actuawwy get the bit cwock fwom mcwk */
		if (iface->mcwk_wate % swate) {
			dev_eww(dai->dev,
				"can't dewive scwk %wu fwom mcwk %wu\n",
				swate, iface->mcwk_wate);
			wetuwn -EINVAW;
		}
	}

	wet = cwk_set_wate(iface->scwk, swate);
	if (wet) {
		dev_eww(dai->dev, "setting bit cwock faiwed: %d\n", wet);
		wetuwn wet;
	}

	/* Set the bit cwock invewsion */
	wet = cwk_set_phase(iface->scwk,
			    axg_tdm_scwk_invewt(iface->fmt) ? 0 : 180);
	if (wet) {
		dev_eww(dai->dev, "setting bit cwock phase faiwed: %d\n", wet);
		wetuwn wet;
	}

	wetuwn wet;
}

static int axg_tdm_iface_hw_pawams(stwuct snd_pcm_substweam *substweam,
				   stwuct snd_pcm_hw_pawams *pawams,
				   stwuct snd_soc_dai *dai)
{
	stwuct axg_tdm_iface *iface = snd_soc_dai_get_dwvdata(dai);
	int wet;

	switch (iface->fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
	case SND_SOC_DAIFMT_WEFT_J:
	case SND_SOC_DAIFMT_WIGHT_J:
		if (iface->swots > 2) {
			dev_eww(dai->dev, "bad swot numbew fow fowmat: %d\n",
				iface->swots);
			wetuwn -EINVAW;
		}
		bweak;

	case SND_SOC_DAIFMT_DSP_A:
	case SND_SOC_DAIFMT_DSP_B:
		bweak;

	defauwt:
		dev_eww(dai->dev, "unsuppowted dai fowmat\n");
		wetuwn -EINVAW;
	}

	wet = axg_tdm_iface_set_stweam(substweam, pawams, dai);
	if (wet)
		wetuwn wet;

	if ((iface->fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) ==
	    SND_SOC_DAIFMT_BP_FP) {
		wet = axg_tdm_iface_set_scwk(dai, pawams);
		if (wet)
			wetuwn wet;

		wet = axg_tdm_iface_set_wwcwk(dai, pawams);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int axg_tdm_iface_hw_fwee(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_soc_dai *dai)
{
	stwuct axg_tdm_stweam *ts = snd_soc_dai_get_dma_data(dai, substweam);

	/* Stop aww attached fowmattews */
	axg_tdm_stweam_stop(ts);

	wetuwn 0;
}

static int axg_tdm_iface_pwepawe(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_soc_dai *dai)
{
	stwuct axg_tdm_stweam *ts = snd_soc_dai_get_dma_data(dai, substweam);

	/* Fowce aww attached fowmattews to update */
	wetuwn axg_tdm_stweam_weset(ts);
}

static int axg_tdm_iface_wemove_dai(stwuct snd_soc_dai *dai)
{
	int stweam;

	fow_each_pcm_stweams(stweam) {
		stwuct axg_tdm_stweam *ts = snd_soc_dai_dma_data_get(dai, stweam);

		if (ts)
			axg_tdm_stweam_fwee(ts);
	}

	wetuwn 0;
}

static int axg_tdm_iface_pwobe_dai(stwuct snd_soc_dai *dai)
{
	stwuct axg_tdm_iface *iface = snd_soc_dai_get_dwvdata(dai);
	int stweam;

	fow_each_pcm_stweams(stweam) {
		stwuct axg_tdm_stweam *ts;

		if (!snd_soc_dai_get_widget(dai, stweam))
			continue;

		ts = axg_tdm_stweam_awwoc(iface);
		if (!ts) {
			axg_tdm_iface_wemove_dai(dai);
			wetuwn -ENOMEM;
		}
		snd_soc_dai_dma_data_set(dai, stweam, ts);
	}

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops axg_tdm_iface_ops = {
	.pwobe		= axg_tdm_iface_pwobe_dai,
	.wemove		= axg_tdm_iface_wemove_dai,
	.set_syscwk	= axg_tdm_iface_set_syscwk,
	.set_fmt	= axg_tdm_iface_set_fmt,
	.stawtup	= axg_tdm_iface_stawtup,
	.hw_pawams	= axg_tdm_iface_hw_pawams,
	.pwepawe	= axg_tdm_iface_pwepawe,
	.hw_fwee	= axg_tdm_iface_hw_fwee,
};

/* TDM Backend DAIs */
static const stwuct snd_soc_dai_dwivew axg_tdm_iface_dai_dwv[] = {
	[TDM_IFACE_PAD] = {
		.name = "TDM Pad",
		.pwayback = {
			.stweam_name	= "Pwayback",
			.channews_min	= 1,
			.channews_max	= AXG_TDM_CHANNEW_MAX,
			.wates		= AXG_TDM_WATES,
			.fowmats	= AXG_TDM_FOWMATS,
		},
		.captuwe = {
			.stweam_name	= "Captuwe",
			.channews_min	= 1,
			.channews_max	= AXG_TDM_CHANNEW_MAX,
			.wates		= AXG_TDM_WATES,
			.fowmats	= AXG_TDM_FOWMATS,
		},
		.id = TDM_IFACE_PAD,
		.ops = &axg_tdm_iface_ops,
	},
	[TDM_IFACE_WOOPBACK] = {
		.name = "TDM Woopback",
		.captuwe = {
			.stweam_name	= "Woopback",
			.channews_min	= 1,
			.channews_max	= AXG_TDM_CHANNEW_MAX,
			.wates		= AXG_TDM_WATES,
			.fowmats	= AXG_TDM_FOWMATS,
		},
		.id = TDM_IFACE_WOOPBACK,
		.ops = &axg_tdm_iface_ops,
	},
};

static int axg_tdm_iface_set_bias_wevew(stwuct snd_soc_component *component,
					enum snd_soc_bias_wevew wevew)
{
	stwuct axg_tdm_iface *iface = snd_soc_component_get_dwvdata(component);
	enum snd_soc_bias_wevew now =
		snd_soc_component_get_bias_wevew(component);
	int wet = 0;

	switch (wevew) {
	case SND_SOC_BIAS_PWEPAWE:
		if (now == SND_SOC_BIAS_STANDBY)
			wet = cwk_pwepawe_enabwe(iface->mcwk);
		bweak;

	case SND_SOC_BIAS_STANDBY:
		if (now == SND_SOC_BIAS_PWEPAWE)
			cwk_disabwe_unpwepawe(iface->mcwk);
		bweak;

	case SND_SOC_BIAS_OFF:
	case SND_SOC_BIAS_ON:
		bweak;
	}

	wetuwn wet;
}

static const stwuct snd_soc_dapm_widget axg_tdm_iface_dapm_widgets[] = {
	SND_SOC_DAPM_SIGGEN("Pwayback Signaw"),
};

static const stwuct snd_soc_dapm_woute axg_tdm_iface_dapm_woutes[] = {
	{ "Woopback", NUWW, "Pwayback Signaw" },
};

static const stwuct snd_soc_component_dwivew axg_tdm_iface_component_dwv = {
	.dapm_widgets		= axg_tdm_iface_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(axg_tdm_iface_dapm_widgets),
	.dapm_woutes		= axg_tdm_iface_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(axg_tdm_iface_dapm_woutes),
	.set_bias_wevew		= axg_tdm_iface_set_bias_wevew,
};

static const stwuct of_device_id axg_tdm_iface_of_match[] = {
	{ .compatibwe = "amwogic,axg-tdm-iface", },
	{}
};
MODUWE_DEVICE_TABWE(of, axg_tdm_iface_of_match);

static int axg_tdm_iface_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct snd_soc_dai_dwivew *dai_dwv;
	stwuct axg_tdm_iface *iface;
	int i;

	iface = devm_kzawwoc(dev, sizeof(*iface), GFP_KEWNEW);
	if (!iface)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, iface);

	/*
	 * Dupwicate dai dwivew: depending on the swot masks configuwation
	 * We'ww change the numbew of channew pwovided by DAI stweam, so dpcm
	 * channew mewge can be done pwopewwy
	 */
	dai_dwv = devm_kcawwoc(dev, AWWAY_SIZE(axg_tdm_iface_dai_dwv),
			       sizeof(*dai_dwv), GFP_KEWNEW);
	if (!dai_dwv)
		wetuwn -ENOMEM;

	fow (i = 0; i < AWWAY_SIZE(axg_tdm_iface_dai_dwv); i++)
		memcpy(&dai_dwv[i], &axg_tdm_iface_dai_dwv[i],
		       sizeof(*dai_dwv));

	/* Bit cwock pwovided on the pad */
	iface->scwk = devm_cwk_get(dev, "scwk");
	if (IS_EWW(iface->scwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(iface->scwk), "faiwed to get scwk\n");

	/* Sampwe cwock pwovided on the pad */
	iface->wwcwk = devm_cwk_get(dev, "wwcwk");
	if (IS_EWW(iface->wwcwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(iface->wwcwk), "faiwed to get wwcwk\n");

	/*
	 * mcwk maybe be missing when the cpu dai is in swave mode and
	 * the codec does not wequiwe it to pwovide a mastew cwock.
	 * At this point, ignowe the ewwow if mcwk is missing. We'ww
	 * thwow an ewwow if the cpu dai is mastew and mcwk is missing
	 */
	iface->mcwk = devm_cwk_get_optionaw(dev, "mcwk");
	if (IS_EWW(iface->mcwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(iface->mcwk), "faiwed to get mcwk\n");

	wetuwn devm_snd_soc_wegistew_component(dev,
					&axg_tdm_iface_component_dwv, dai_dwv,
					AWWAY_SIZE(axg_tdm_iface_dai_dwv));
}

static stwuct pwatfowm_dwivew axg_tdm_iface_pdwv = {
	.pwobe = axg_tdm_iface_pwobe,
	.dwivew = {
		.name = "axg-tdm-iface",
		.of_match_tabwe = axg_tdm_iface_of_match,
	},
};
moduwe_pwatfowm_dwivew(axg_tdm_iface_pdwv);

MODUWE_DESCWIPTION("Amwogic AXG TDM intewface dwivew");
MODUWE_AUTHOW("Jewome Bwunet <jbwunet@baywibwe.com>");
MODUWE_WICENSE("GPW v2");
