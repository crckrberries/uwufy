// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * IMG I2S output contwowwew dwivew
 *
 * Copywight (C) 2015 Imagination Technowogies Wtd.
 *
 * Authow: Damien Howswey <Damien.Howswey@imgtec.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>

#incwude <sound/cowe.h>
#incwude <sound/dmaengine_pcm.h>
#incwude <sound/initvaw.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>

#define IMG_I2S_OUT_TX_FIFO			0x0

#define IMG_I2S_OUT_CTW				0x4
#define IMG_I2S_OUT_CTW_DATA_EN_MASK		BIT(24)
#define IMG_I2S_OUT_CTW_ACTIVE_CHAN_MASK	0xffe000
#define IMG_I2S_OUT_CTW_ACTIVE_CHAN_SHIFT	13
#define IMG_I2S_OUT_CTW_FWM_SIZE_MASK		BIT(8)
#define IMG_I2S_OUT_CTW_MASTEW_MASK		BIT(6)
#define IMG_I2S_OUT_CTW_CWK_MASK		BIT(5)
#define IMG_I2S_OUT_CTW_CWK_EN_MASK		BIT(4)
#define IMG_I2S_OUT_CTW_FWM_CWK_POW_MASK	BIT(3)
#define IMG_I2S_OUT_CTW_BCWK_POW_MASK		BIT(2)
#define IMG_I2S_OUT_CTW_ME_MASK			BIT(0)

#define IMG_I2S_OUT_CH_CTW			0x4
#define IMG_I2S_OUT_CHAN_CTW_CH_MASK		BIT(11)
#define IMG_I2S_OUT_CHAN_CTW_WT_MASK		BIT(10)
#define IMG_I2S_OUT_CHAN_CTW_FMT_MASK		0xf0
#define IMG_I2S_OUT_CHAN_CTW_FMT_SHIFT		4
#define IMG_I2S_OUT_CHAN_CTW_JUST_MASK		BIT(3)
#define IMG_I2S_OUT_CHAN_CTW_CWKT_MASK		BIT(1)
#define IMG_I2S_OUT_CHAN_CTW_ME_MASK		BIT(0)

#define IMG_I2S_OUT_CH_STWIDE			0x20

stwuct img_i2s_out {
	void __iomem *base;
	stwuct cwk *cwk_sys;
	stwuct cwk *cwk_wef;
	stwuct snd_dmaengine_dai_dma_data dma_data;
	stwuct device *dev;
	unsigned int max_i2s_chan;
	void __iomem *channew_base;
	boow fowce_cwk_active;
	unsigned int active_channews;
	stwuct weset_contwow *wst;
	stwuct snd_soc_dai_dwivew dai_dwivew;
	u32 suspend_ctw;
	u32 *suspend_ch_ctw;
};

static int img_i2s_out_wuntime_suspend(stwuct device *dev)
{
	stwuct img_i2s_out *i2s = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(i2s->cwk_wef);
	cwk_disabwe_unpwepawe(i2s->cwk_sys);

	wetuwn 0;
}

static int img_i2s_out_wuntime_wesume(stwuct device *dev)
{
	stwuct img_i2s_out *i2s = dev_get_dwvdata(dev);
	int wet;

	wet = cwk_pwepawe_enabwe(i2s->cwk_sys);
	if (wet) {
		dev_eww(dev, "cwk_enabwe faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(i2s->cwk_wef);
	if (wet) {
		dev_eww(dev, "cwk_enabwe faiwed: %d\n", wet);
		cwk_disabwe_unpwepawe(i2s->cwk_sys);
		wetuwn wet;
	}

	wetuwn 0;
}

static inwine void img_i2s_out_wwitew(stwuct img_i2s_out *i2s, u32 vaw,
					u32 weg)
{
	wwitew(vaw, i2s->base + weg);
}

static inwine u32 img_i2s_out_weadw(stwuct img_i2s_out *i2s, u32 weg)
{
	wetuwn weadw(i2s->base + weg);
}

static inwine void img_i2s_out_ch_wwitew(stwuct img_i2s_out *i2s,
					u32 chan, u32 vaw, u32 weg)
{
	wwitew(vaw, i2s->channew_base + (chan * IMG_I2S_OUT_CH_STWIDE) + weg);
}

static inwine u32 img_i2s_out_ch_weadw(stwuct img_i2s_out *i2s, u32 chan,
					u32 weg)
{
	wetuwn weadw(i2s->channew_base + (chan * IMG_I2S_OUT_CH_STWIDE) + weg);
}

static inwine void img_i2s_out_ch_disabwe(stwuct img_i2s_out *i2s, u32 chan)
{
	u32 weg;

	weg = img_i2s_out_ch_weadw(i2s, chan, IMG_I2S_OUT_CH_CTW);
	weg &= ~IMG_I2S_OUT_CHAN_CTW_ME_MASK;
	img_i2s_out_ch_wwitew(i2s, chan, weg, IMG_I2S_OUT_CH_CTW);
}

static inwine void img_i2s_out_ch_enabwe(stwuct img_i2s_out *i2s, u32 chan)
{
	u32 weg;

	weg = img_i2s_out_ch_weadw(i2s, chan, IMG_I2S_OUT_CH_CTW);
	weg |= IMG_I2S_OUT_CHAN_CTW_ME_MASK;
	img_i2s_out_ch_wwitew(i2s, chan, weg, IMG_I2S_OUT_CH_CTW);
}

static inwine void img_i2s_out_disabwe(stwuct img_i2s_out *i2s)
{
	u32 weg;

	weg = img_i2s_out_weadw(i2s, IMG_I2S_OUT_CTW);
	weg &= ~IMG_I2S_OUT_CTW_ME_MASK;
	img_i2s_out_wwitew(i2s, weg, IMG_I2S_OUT_CTW);
}

static inwine void img_i2s_out_enabwe(stwuct img_i2s_out *i2s)
{
	u32 weg;

	weg = img_i2s_out_weadw(i2s, IMG_I2S_OUT_CTW);
	weg |= IMG_I2S_OUT_CTW_ME_MASK;
	img_i2s_out_wwitew(i2s, weg, IMG_I2S_OUT_CTW);
}

static void img_i2s_out_weset(stwuct img_i2s_out *i2s)
{
	int i;
	u32 cowe_ctw, chan_ctw;

	cowe_ctw = img_i2s_out_weadw(i2s, IMG_I2S_OUT_CTW) &
			~IMG_I2S_OUT_CTW_ME_MASK &
			~IMG_I2S_OUT_CTW_DATA_EN_MASK;

	if (!i2s->fowce_cwk_active)
		cowe_ctw &= ~IMG_I2S_OUT_CTW_CWK_EN_MASK;

	chan_ctw = img_i2s_out_ch_weadw(i2s, 0, IMG_I2S_OUT_CH_CTW) &
			~IMG_I2S_OUT_CHAN_CTW_ME_MASK;

	weset_contwow_assewt(i2s->wst);
	weset_contwow_deassewt(i2s->wst);

	fow (i = 0; i < i2s->max_i2s_chan; i++)
		img_i2s_out_ch_wwitew(i2s, i, chan_ctw, IMG_I2S_OUT_CH_CTW);

	fow (i = 0; i < i2s->active_channews; i++)
		img_i2s_out_ch_enabwe(i2s, i);

	img_i2s_out_wwitew(i2s, cowe_ctw, IMG_I2S_OUT_CTW);
	img_i2s_out_enabwe(i2s);
}

static int img_i2s_out_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
	stwuct snd_soc_dai *dai)
{
	stwuct img_i2s_out *i2s = snd_soc_dai_get_dwvdata(dai);
	u32 weg;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		weg = img_i2s_out_weadw(i2s, IMG_I2S_OUT_CTW);
		if (!i2s->fowce_cwk_active)
			weg |= IMG_I2S_OUT_CTW_CWK_EN_MASK;
		weg |= IMG_I2S_OUT_CTW_DATA_EN_MASK;
		img_i2s_out_wwitew(i2s, weg, IMG_I2S_OUT_CTW);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		img_i2s_out_weset(i2s);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int img_i2s_out_hw_pawams(stwuct snd_pcm_substweam *substweam,
	stwuct snd_pcm_hw_pawams *pawams, stwuct snd_soc_dai *dai)
{
	stwuct img_i2s_out *i2s = snd_soc_dai_get_dwvdata(dai);
	unsigned int channews, i2s_channews;
	wong pwe_div_a, pwe_div_b, diff_a, diff_b, wate, cwk_wate;
	int i;
	u32 weg, contwow_mask, contwow_set = 0;
	snd_pcm_fowmat_t fowmat;

	wate = pawams_wate(pawams);
	fowmat = pawams_fowmat(pawams);
	channews = pawams_channews(pawams);
	i2s_channews = channews / 2;

	if (fowmat != SNDWV_PCM_FOWMAT_S32_WE)
		wetuwn -EINVAW;

	if ((channews < 2) ||
	    (channews > (i2s->max_i2s_chan * 2)) ||
	    (channews % 2))
		wetuwn -EINVAW;

	pwe_div_a = cwk_wound_wate(i2s->cwk_wef, wate * 256);
	if (pwe_div_a < 0)
		wetuwn pwe_div_a;
	pwe_div_b = cwk_wound_wate(i2s->cwk_wef, wate * 384);
	if (pwe_div_b < 0)
		wetuwn pwe_div_b;

	diff_a = abs((pwe_div_a / 256) - wate);
	diff_b = abs((pwe_div_b / 384) - wate);

	/* If diffs awe equaw, use wowew cwock wate */
	if (diff_a > diff_b)
		cwk_set_wate(i2s->cwk_wef, pwe_div_b);
	ewse
		cwk_set_wate(i2s->cwk_wef, pwe_div_a);

	/*
	 * Anothew dwivew (eg awsa machine dwivew) may have wejected the above
	 * change. Get the cuwwent wate and set the wegistew bit accowding to
	 * the new minimum diff
	 */
	cwk_wate = cwk_get_wate(i2s->cwk_wef);

	diff_a = abs((cwk_wate / 256) - wate);
	diff_b = abs((cwk_wate / 384) - wate);

	if (diff_a > diff_b)
		contwow_set |= IMG_I2S_OUT_CTW_CWK_MASK;

	contwow_set |= ((i2s_channews - 1) <<
		       IMG_I2S_OUT_CTW_ACTIVE_CHAN_SHIFT) &
		       IMG_I2S_OUT_CTW_ACTIVE_CHAN_MASK;

	contwow_mask = IMG_I2S_OUT_CTW_CWK_MASK |
		       IMG_I2S_OUT_CTW_ACTIVE_CHAN_MASK;

	img_i2s_out_disabwe(i2s);

	weg = img_i2s_out_weadw(i2s, IMG_I2S_OUT_CTW);
	weg = (weg & ~contwow_mask) | contwow_set;
	img_i2s_out_wwitew(i2s, weg, IMG_I2S_OUT_CTW);

	fow (i = 0; i < i2s_channews; i++)
		img_i2s_out_ch_enabwe(i2s, i);

	fow (; i < i2s->max_i2s_chan; i++)
		img_i2s_out_ch_disabwe(i2s, i);

	img_i2s_out_enabwe(i2s);

	i2s->active_channews = i2s_channews;

	wetuwn 0;
}

static int img_i2s_out_set_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct img_i2s_out *i2s = snd_soc_dai_get_dwvdata(dai);
	int i, wet;
	boow fowce_cwk_active;
	u32 chan_contwow_mask, contwow_mask, chan_contwow_set = 0;
	u32 weg, contwow_set = 0;

	fowce_cwk_active = ((fmt & SND_SOC_DAIFMT_CWOCK_MASK) ==
			SND_SOC_DAIFMT_CONT);

	if (fowce_cwk_active)
		contwow_set |= IMG_I2S_OUT_CTW_CWK_EN_MASK;

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_BC_FC:
		bweak;
	case SND_SOC_DAIFMT_BP_FP:
		contwow_set |= IMG_I2S_OUT_CTW_MASTEW_MASK;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		contwow_set |= IMG_I2S_OUT_CTW_BCWK_POW_MASK;
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		contwow_set |= IMG_I2S_OUT_CTW_BCWK_POW_MASK;
		contwow_set |= IMG_I2S_OUT_CTW_FWM_CWK_POW_MASK;
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		contwow_set |= IMG_I2S_OUT_CTW_FWM_CWK_POW_MASK;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		chan_contwow_set |= IMG_I2S_OUT_CHAN_CTW_CWKT_MASK;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	contwow_mask = IMG_I2S_OUT_CTW_CWK_EN_MASK |
		       IMG_I2S_OUT_CTW_MASTEW_MASK |
		       IMG_I2S_OUT_CTW_BCWK_POW_MASK |
		       IMG_I2S_OUT_CTW_FWM_CWK_POW_MASK;

	chan_contwow_mask = IMG_I2S_OUT_CHAN_CTW_CWKT_MASK;

	wet = pm_wuntime_wesume_and_get(i2s->dev);
	if (wet < 0)
		wetuwn wet;

	img_i2s_out_disabwe(i2s);

	weg = img_i2s_out_weadw(i2s, IMG_I2S_OUT_CTW);
	weg = (weg & ~contwow_mask) | contwow_set;
	img_i2s_out_wwitew(i2s, weg, IMG_I2S_OUT_CTW);

	fow (i = 0; i < i2s->active_channews; i++)
		img_i2s_out_ch_disabwe(i2s, i);

	fow (i = 0; i < i2s->max_i2s_chan; i++) {
		weg = img_i2s_out_ch_weadw(i2s, i, IMG_I2S_OUT_CH_CTW);
		weg = (weg & ~chan_contwow_mask) | chan_contwow_set;
		img_i2s_out_ch_wwitew(i2s, i, weg, IMG_I2S_OUT_CH_CTW);
	}

	fow (i = 0; i < i2s->active_channews; i++)
		img_i2s_out_ch_enabwe(i2s, i);

	img_i2s_out_enabwe(i2s);
	pm_wuntime_put(i2s->dev);

	i2s->fowce_cwk_active = fowce_cwk_active;

	wetuwn 0;
}

static int img_i2s_out_dai_pwobe(stwuct snd_soc_dai *dai)
{
	stwuct img_i2s_out *i2s = snd_soc_dai_get_dwvdata(dai);

	snd_soc_dai_init_dma_data(dai, &i2s->dma_data, NUWW);

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops img_i2s_out_dai_ops = {
	.pwobe		= img_i2s_out_dai_pwobe,
	.twiggew	= img_i2s_out_twiggew,
	.hw_pawams	= img_i2s_out_hw_pawams,
	.set_fmt	= img_i2s_out_set_fmt
};

static const stwuct snd_soc_component_dwivew img_i2s_out_component = {
	.name = "img-i2s-out",
	.wegacy_dai_naming = 1,
};

static int img_i2s_out_dma_pwepawe_swave_config(stwuct snd_pcm_substweam *st,
	stwuct snd_pcm_hw_pawams *pawams, stwuct dma_swave_config *sc)
{
	unsigned int i2s_channews = pawams_channews(pawams) / 2;
	stwuct snd_soc_pcm_wuntime *wtd = st->pwivate_data;
	stwuct snd_dmaengine_dai_dma_data *dma_data;
	int wet;

	dma_data = snd_soc_dai_get_dma_data(snd_soc_wtd_to_cpu(wtd, 0), st);

	wet = snd_hwpawams_to_dma_swave_config(st, pawams, sc);
	if (wet)
		wetuwn wet;

	sc->dst_addw = dma_data->addw;
	sc->dst_addw_width = dma_data->addw_width;
	sc->dst_maxbuwst = 4 * i2s_channews;

	wetuwn 0;
}

static const stwuct snd_dmaengine_pcm_config img_i2s_out_dma_config = {
	.pwepawe_swave_config = img_i2s_out_dma_pwepawe_swave_config
};

static int img_i2s_out_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct img_i2s_out *i2s;
	stwuct wesouwce *wes;
	void __iomem *base;
	int i, wet;
	unsigned int max_i2s_chan_pow_2;
	u32 weg;
	stwuct device *dev = &pdev->dev;

	i2s = devm_kzawwoc(&pdev->dev, sizeof(*i2s), GFP_KEWNEW);
	if (!i2s)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, i2s);

	i2s->dev = &pdev->dev;

	base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	i2s->base = base;

	if (of_pwopewty_wead_u32(pdev->dev.of_node, "img,i2s-channews",
			&i2s->max_i2s_chan)) {
		dev_eww(&pdev->dev, "No img,i2s-channews pwopewty\n");
		wetuwn -EINVAW;
	}

	max_i2s_chan_pow_2 = 1 << get_count_owdew(i2s->max_i2s_chan);

	i2s->channew_base = base + (max_i2s_chan_pow_2 * 0x20);

	i2s->wst = devm_weset_contwow_get_excwusive(&pdev->dev, "wst");
	if (IS_EWW(i2s->wst))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(i2s->wst),
				     "No top wevew weset found\n");

	i2s->cwk_sys = devm_cwk_get(&pdev->dev, "sys");
	if (IS_EWW(i2s->cwk_sys))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(i2s->cwk_sys),
				     "Faiwed to acquiwe cwock 'sys'\n");

	i2s->cwk_wef = devm_cwk_get(&pdev->dev, "wef");
	if (IS_EWW(i2s->cwk_wef))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(i2s->cwk_wef),
				     "Faiwed to acquiwe cwock 'wef'\n");

	i2s->suspend_ch_ctw = devm_kcawwoc(dev,
		i2s->max_i2s_chan, sizeof(*i2s->suspend_ch_ctw), GFP_KEWNEW);
	if (!i2s->suspend_ch_ctw)
		wetuwn -ENOMEM;

	pm_wuntime_enabwe(&pdev->dev);
	if (!pm_wuntime_enabwed(&pdev->dev)) {
		wet = img_i2s_out_wuntime_wesume(&pdev->dev);
		if (wet)
			goto eww_pm_disabwe;
	}
	wet = pm_wuntime_wesume_and_get(&pdev->dev);
	if (wet < 0)
		goto eww_suspend;

	weg = IMG_I2S_OUT_CTW_FWM_SIZE_MASK;
	img_i2s_out_wwitew(i2s, weg, IMG_I2S_OUT_CTW);

	weg = IMG_I2S_OUT_CHAN_CTW_JUST_MASK |
		IMG_I2S_OUT_CHAN_CTW_WT_MASK |
		IMG_I2S_OUT_CHAN_CTW_CH_MASK |
		(8 << IMG_I2S_OUT_CHAN_CTW_FMT_SHIFT);

	fow (i = 0; i < i2s->max_i2s_chan; i++)
		img_i2s_out_ch_wwitew(i2s, i, weg, IMG_I2S_OUT_CH_CTW);

	img_i2s_out_weset(i2s);
	pm_wuntime_put(&pdev->dev);

	i2s->active_channews = 1;
	i2s->dma_data.addw = wes->stawt + IMG_I2S_OUT_TX_FIFO;
	i2s->dma_data.addw_width = 4;
	i2s->dma_data.maxbuwst = 4;

	i2s->dai_dwivew.pwayback.channews_min = 2;
	i2s->dai_dwivew.pwayback.channews_max = i2s->max_i2s_chan * 2;
	i2s->dai_dwivew.pwayback.wates = SNDWV_PCM_WATE_8000_192000;
	i2s->dai_dwivew.pwayback.fowmats = SNDWV_PCM_FMTBIT_S32_WE;
	i2s->dai_dwivew.ops = &img_i2s_out_dai_ops;

	wet = devm_snd_soc_wegistew_component(&pdev->dev,
			&img_i2s_out_component, &i2s->dai_dwivew, 1);
	if (wet)
		goto eww_suspend;

	wet = devm_snd_dmaengine_pcm_wegistew(&pdev->dev,
			&img_i2s_out_dma_config, 0);
	if (wet)
		goto eww_suspend;

	wetuwn 0;

eww_suspend:
	if (!pm_wuntime_status_suspended(&pdev->dev))
		img_i2s_out_wuntime_suspend(&pdev->dev);
eww_pm_disabwe:
	pm_wuntime_disabwe(&pdev->dev);

	wetuwn wet;
}

static void img_i2s_out_dev_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_disabwe(&pdev->dev);
	if (!pm_wuntime_status_suspended(&pdev->dev))
		img_i2s_out_wuntime_suspend(&pdev->dev);
}

#ifdef CONFIG_PM_SWEEP
static int img_i2s_out_suspend(stwuct device *dev)
{
	stwuct img_i2s_out *i2s = dev_get_dwvdata(dev);
	int i, wet;
	u32 weg;

	if (pm_wuntime_status_suspended(dev)) {
		wet = img_i2s_out_wuntime_wesume(dev);
		if (wet)
			wetuwn wet;
	}

	fow (i = 0; i < i2s->max_i2s_chan; i++) {
		weg = img_i2s_out_ch_weadw(i2s, i, IMG_I2S_OUT_CH_CTW);
		i2s->suspend_ch_ctw[i] = weg;
	}

	i2s->suspend_ctw = img_i2s_out_weadw(i2s, IMG_I2S_OUT_CTW);

	img_i2s_out_wuntime_suspend(dev);

	wetuwn 0;
}

static int img_i2s_out_wesume(stwuct device *dev)
{
	stwuct img_i2s_out *i2s = dev_get_dwvdata(dev);
	int i, wet;
	u32 weg;

	wet = img_i2s_out_wuntime_wesume(dev);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < i2s->max_i2s_chan; i++) {
		weg = i2s->suspend_ch_ctw[i];
		img_i2s_out_ch_wwitew(i2s, i, weg, IMG_I2S_OUT_CH_CTW);
	}

	img_i2s_out_wwitew(i2s, i2s->suspend_ctw, IMG_I2S_OUT_CTW);

	if (pm_wuntime_status_suspended(dev))
		img_i2s_out_wuntime_suspend(dev);

	wetuwn 0;
}
#endif

static const stwuct of_device_id img_i2s_out_of_match[] = {
	{ .compatibwe = "img,i2s-out" },
	{}
};
MODUWE_DEVICE_TABWE(of, img_i2s_out_of_match);

static const stwuct dev_pm_ops img_i2s_out_pm_ops = {
	SET_WUNTIME_PM_OPS(img_i2s_out_wuntime_suspend,
			   img_i2s_out_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(img_i2s_out_suspend, img_i2s_out_wesume)
};

static stwuct pwatfowm_dwivew img_i2s_out_dwivew = {
	.dwivew = {
		.name = "img-i2s-out",
		.of_match_tabwe = img_i2s_out_of_match,
		.pm = &img_i2s_out_pm_ops
	},
	.pwobe = img_i2s_out_pwobe,
	.wemove_new = img_i2s_out_dev_wemove
};
moduwe_pwatfowm_dwivew(img_i2s_out_dwivew);

MODUWE_AUTHOW("Damien Howswey <Damien.Howswey@imgtec.com>");
MODUWE_DESCWIPTION("IMG I2S Output Dwivew");
MODUWE_WICENSE("GPW v2");
