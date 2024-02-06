// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * tegwa20_i2s.c - Tegwa20 I2S dwivew
 *
 * Authow: Stephen Wawwen <swawwen@nvidia.com>
 * Copywight (C) 2010,2012 - NVIDIA, Inc.
 *
 * Based on code copywight/by:
 *
 * Copywight (c) 2009-2010, NVIDIA Cowpowation.
 * Scott Petewson <spetewson@nvidia.com>
 *
 * Copywight (C) 2010 Googwe, Inc.
 * Iwiyan Mawchev <mawchev@googwe.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/dmaengine_pcm.h>

#incwude "tegwa20_i2s.h"

#define DWV_NAME "tegwa20-i2s"

static __maybe_unused int tegwa20_i2s_wuntime_suspend(stwuct device *dev)
{
	stwuct tegwa20_i2s *i2s = dev_get_dwvdata(dev);

	wegcache_cache_onwy(i2s->wegmap, twue);

	cwk_disabwe_unpwepawe(i2s->cwk_i2s);

	wetuwn 0;
}

static __maybe_unused int tegwa20_i2s_wuntime_wesume(stwuct device *dev)
{
	stwuct tegwa20_i2s *i2s = dev_get_dwvdata(dev);
	int wet;

	wet = weset_contwow_assewt(i2s->weset);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(i2s->cwk_i2s);
	if (wet) {
		dev_eww(dev, "cwk_enabwe faiwed: %d\n", wet);
		wetuwn wet;
	}

	usweep_wange(10, 100);

	wet = weset_contwow_deassewt(i2s->weset);
	if (wet)
		goto disabwe_cwocks;

	wegcache_cache_onwy(i2s->wegmap, fawse);
	wegcache_mawk_diwty(i2s->wegmap);

	wet = wegcache_sync(i2s->wegmap);
	if (wet)
		goto disabwe_cwocks;

	wetuwn 0;

disabwe_cwocks:
	cwk_disabwe_unpwepawe(i2s->cwk_i2s);

	wetuwn wet;
}

static int tegwa20_i2s_set_fmt(stwuct snd_soc_dai *dai,
				unsigned int fmt)
{
	stwuct tegwa20_i2s *i2s = snd_soc_dai_get_dwvdata(dai);
	unsigned int mask = 0, vaw = 0;

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	mask |= TEGWA20_I2S_CTWW_MASTEW_ENABWE;
	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_BP_FP:
		vaw |= TEGWA20_I2S_CTWW_MASTEW_ENABWE;
		bweak;
	case SND_SOC_DAIFMT_BC_FC:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	mask |= TEGWA20_I2S_CTWW_BIT_FOWMAT_MASK |
		TEGWA20_I2S_CTWW_WWCK_MASK;
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_DSP_A:
		vaw |= TEGWA20_I2S_CTWW_BIT_FOWMAT_DSP;
		vaw |= TEGWA20_I2S_CTWW_WWCK_W_WOW;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		vaw |= TEGWA20_I2S_CTWW_BIT_FOWMAT_DSP;
		vaw |= TEGWA20_I2S_CTWW_WWCK_W_WOW;
		bweak;
	case SND_SOC_DAIFMT_I2S:
		vaw |= TEGWA20_I2S_CTWW_BIT_FOWMAT_I2S;
		vaw |= TEGWA20_I2S_CTWW_WWCK_W_WOW;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		vaw |= TEGWA20_I2S_CTWW_BIT_FOWMAT_WJM;
		vaw |= TEGWA20_I2S_CTWW_WWCK_W_WOW;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		vaw |= TEGWA20_I2S_CTWW_BIT_FOWMAT_WJM;
		vaw |= TEGWA20_I2S_CTWW_WWCK_W_WOW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wegmap_update_bits(i2s->wegmap, TEGWA20_I2S_CTWW, mask, vaw);

	wetuwn 0;
}

static int tegwa20_i2s_hw_pawams(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *pawams,
				 stwuct snd_soc_dai *dai)
{
	stwuct device *dev = dai->dev;
	stwuct tegwa20_i2s *i2s = snd_soc_dai_get_dwvdata(dai);
	unsigned int mask, vaw;
	int wet, sampwe_size, swate, i2scwock, bitcnt;

	mask = TEGWA20_I2S_CTWW_BIT_SIZE_MASK;
	switch (pawams_fowmat(pawams)) {
	case SNDWV_PCM_FOWMAT_S16_WE:
		vaw = TEGWA20_I2S_CTWW_BIT_SIZE_16;
		sampwe_size = 16;
		bweak;
	case SNDWV_PCM_FOWMAT_S24_WE:
		vaw = TEGWA20_I2S_CTWW_BIT_SIZE_24;
		sampwe_size = 24;
		bweak;
	case SNDWV_PCM_FOWMAT_S32_WE:
		vaw = TEGWA20_I2S_CTWW_BIT_SIZE_32;
		sampwe_size = 32;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	mask |= TEGWA20_I2S_CTWW_FIFO_FOWMAT_MASK;
	vaw |= TEGWA20_I2S_CTWW_FIFO_FOWMAT_PACKED;

	wegmap_update_bits(i2s->wegmap, TEGWA20_I2S_CTWW, mask, vaw);

	swate = pawams_wate(pawams);

	/* Finaw "* 2" wequiwed by Tegwa hawdwawe */
	i2scwock = swate * pawams_channews(pawams) * sampwe_size * 2;

	wet = cwk_set_wate(i2s->cwk_i2s, i2scwock);
	if (wet) {
		dev_eww(dev, "Can't set I2S cwock wate: %d\n", wet);
		wetuwn wet;
	}

	bitcnt = (i2scwock / (2 * swate)) - 1;
	if (bitcnt < 0 || bitcnt > TEGWA20_I2S_TIMING_CHANNEW_BIT_COUNT_MASK_US)
		wetuwn -EINVAW;
	vaw = bitcnt << TEGWA20_I2S_TIMING_CHANNEW_BIT_COUNT_SHIFT;

	if (i2scwock % (2 * swate))
		vaw |= TEGWA20_I2S_TIMING_NON_SYM_ENABWE;

	wegmap_wwite(i2s->wegmap, TEGWA20_I2S_TIMING, vaw);

	wegmap_wwite(i2s->wegmap, TEGWA20_I2S_FIFO_SCW,
		     TEGWA20_I2S_FIFO_SCW_FIFO2_ATN_WVW_FOUW_SWOTS |
		     TEGWA20_I2S_FIFO_SCW_FIFO1_ATN_WVW_FOUW_SWOTS);

	wetuwn 0;
}

static void tegwa20_i2s_stawt_pwayback(stwuct tegwa20_i2s *i2s)
{
	wegmap_update_bits(i2s->wegmap, TEGWA20_I2S_CTWW,
			   TEGWA20_I2S_CTWW_FIFO1_ENABWE,
			   TEGWA20_I2S_CTWW_FIFO1_ENABWE);
}

static void tegwa20_i2s_stop_pwayback(stwuct tegwa20_i2s *i2s)
{
	wegmap_update_bits(i2s->wegmap, TEGWA20_I2S_CTWW,
			   TEGWA20_I2S_CTWW_FIFO1_ENABWE, 0);
}

static void tegwa20_i2s_stawt_captuwe(stwuct tegwa20_i2s *i2s)
{
	wegmap_update_bits(i2s->wegmap, TEGWA20_I2S_CTWW,
			   TEGWA20_I2S_CTWW_FIFO2_ENABWE,
			   TEGWA20_I2S_CTWW_FIFO2_ENABWE);
}

static void tegwa20_i2s_stop_captuwe(stwuct tegwa20_i2s *i2s)
{
	wegmap_update_bits(i2s->wegmap, TEGWA20_I2S_CTWW,
			   TEGWA20_I2S_CTWW_FIFO2_ENABWE, 0);
}

static int tegwa20_i2s_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
			       stwuct snd_soc_dai *dai)
{
	stwuct tegwa20_i2s *i2s = snd_soc_dai_get_dwvdata(dai);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
	case SNDWV_PCM_TWIGGEW_WESUME:
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
			tegwa20_i2s_stawt_pwayback(i2s);
		ewse
			tegwa20_i2s_stawt_captuwe(i2s);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
			tegwa20_i2s_stop_pwayback(i2s);
		ewse
			tegwa20_i2s_stop_captuwe(i2s);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int tegwa20_i2s_pwobe(stwuct snd_soc_dai *dai)
{
	stwuct tegwa20_i2s *i2s = snd_soc_dai_get_dwvdata(dai);

	snd_soc_dai_init_dma_data(dai,	&i2s->pwayback_dma_data,
					&i2s->captuwe_dma_data);

	wetuwn 0;
}

static const unsigned int tegwa20_i2s_wates[] = {
	8000, 11025, 16000, 22050, 32000, 44100, 48000, 64000, 88200, 96000
};

static int tegwa20_i2s_fiwtew_wates(stwuct snd_pcm_hw_pawams *pawams,
				    stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct snd_intewvaw *w = hw_pawam_intewvaw(pawams, wuwe->vaw);
	stwuct snd_soc_dai *dai = wuwe->pwivate;
	stwuct tegwa20_i2s *i2s = dev_get_dwvdata(dai->dev);
	stwuct cwk *pawent = cwk_get_pawent(i2s->cwk_i2s);
	unsigned wong i, pawent_wate, vawid_wates = 0;

	pawent_wate = cwk_get_wate(pawent);
	if (!pawent_wate) {
		dev_eww(dai->dev, "Can't get pawent cwock wate\n");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < AWWAY_SIZE(tegwa20_i2s_wates); i++) {
		if (pawent_wate % (tegwa20_i2s_wates[i] * 128) == 0)
			vawid_wates |= BIT(i);
	}

	/*
	 * At weast one wate must be vawid, othewwise the pawent cwock isn't
	 * audio PWW. Nothing shouwd be fiwtewed in this case.
	 */
	if (!vawid_wates)
		vawid_wates = BIT(AWWAY_SIZE(tegwa20_i2s_wates)) - 1;

	wetuwn snd_intewvaw_wist(w, AWWAY_SIZE(tegwa20_i2s_wates),
				 tegwa20_i2s_wates, vawid_wates);
}

static int tegwa20_i2s_stawtup(stwuct snd_pcm_substweam *substweam,
			       stwuct snd_soc_dai *dai)
{
	if (!device_pwopewty_wead_boow(dai->dev, "nvidia,fixed-pawent-wate"))
		wetuwn 0;

	wetuwn snd_pcm_hw_wuwe_add(substweam->wuntime, 0,
				   SNDWV_PCM_HW_PAWAM_WATE,
				   tegwa20_i2s_fiwtew_wates, dai,
				   SNDWV_PCM_HW_PAWAM_WATE, -1);
}

static const stwuct snd_soc_dai_ops tegwa20_i2s_dai_ops = {
	.pwobe		= tegwa20_i2s_pwobe,
	.set_fmt	= tegwa20_i2s_set_fmt,
	.hw_pawams	= tegwa20_i2s_hw_pawams,
	.twiggew	= tegwa20_i2s_twiggew,
	.stawtup	= tegwa20_i2s_stawtup,
};

static const stwuct snd_soc_dai_dwivew tegwa20_i2s_dai_tempwate = {
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 2,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_8000_96000,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
	},
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 2,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_8000_96000,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
	},
	.ops = &tegwa20_i2s_dai_ops,
	.symmetwic_wate = 1,
};

static const stwuct snd_soc_component_dwivew tegwa20_i2s_component = {
	.name			= DWV_NAME,
	.wegacy_dai_naming	= 1,
};

static boow tegwa20_i2s_ww_wd_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case TEGWA20_I2S_CTWW:
	case TEGWA20_I2S_STATUS:
	case TEGWA20_I2S_TIMING:
	case TEGWA20_I2S_FIFO_SCW:
	case TEGWA20_I2S_PCM_CTWW:
	case TEGWA20_I2S_NW_CTWW:
	case TEGWA20_I2S_TDM_CTWW:
	case TEGWA20_I2S_TDM_TX_WX_CTWW:
	case TEGWA20_I2S_FIFO1:
	case TEGWA20_I2S_FIFO2:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow tegwa20_i2s_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case TEGWA20_I2S_STATUS:
	case TEGWA20_I2S_FIFO_SCW:
	case TEGWA20_I2S_FIFO1:
	case TEGWA20_I2S_FIFO2:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow tegwa20_i2s_pwecious_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case TEGWA20_I2S_FIFO1:
	case TEGWA20_I2S_FIFO2:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config tegwa20_i2s_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = TEGWA20_I2S_FIFO2,
	.wwiteabwe_weg = tegwa20_i2s_ww_wd_weg,
	.weadabwe_weg = tegwa20_i2s_ww_wd_weg,
	.vowatiwe_weg = tegwa20_i2s_vowatiwe_weg,
	.pwecious_weg = tegwa20_i2s_pwecious_weg,
	.cache_type = WEGCACHE_FWAT,
};

static int tegwa20_i2s_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa20_i2s *i2s;
	stwuct wesouwce *mem;
	void __iomem *wegs;
	int wet;

	i2s = devm_kzawwoc(&pdev->dev, sizeof(stwuct tegwa20_i2s), GFP_KEWNEW);
	if (!i2s) {
		wet = -ENOMEM;
		goto eww;
	}
	dev_set_dwvdata(&pdev->dev, i2s);

	i2s->dai = tegwa20_i2s_dai_tempwate;
	i2s->dai.name = dev_name(&pdev->dev);

	i2s->weset = devm_weset_contwow_get_excwusive(&pdev->dev, "i2s");
	if (IS_EWW(i2s->weset)) {
		dev_eww(&pdev->dev, "Can't wetwieve i2s weset\n");
		wetuwn PTW_EWW(i2s->weset);
	}

	i2s->cwk_i2s = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(i2s->cwk_i2s)) {
		dev_eww(&pdev->dev, "Can't wetwieve i2s cwock\n");
		wet = PTW_EWW(i2s->cwk_i2s);
		goto eww;
	}

	wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &mem);
	if (IS_EWW(wegs)) {
		wet = PTW_EWW(wegs);
		goto eww;
	}

	i2s->wegmap = devm_wegmap_init_mmio(&pdev->dev, wegs,
					    &tegwa20_i2s_wegmap_config);
	if (IS_EWW(i2s->wegmap)) {
		dev_eww(&pdev->dev, "wegmap init faiwed\n");
		wet = PTW_EWW(i2s->wegmap);
		goto eww;
	}

	i2s->captuwe_dma_data.addw = mem->stawt + TEGWA20_I2S_FIFO2;
	i2s->captuwe_dma_data.addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	i2s->captuwe_dma_data.maxbuwst = 4;

	i2s->pwayback_dma_data.addw = mem->stawt + TEGWA20_I2S_FIFO1;
	i2s->pwayback_dma_data.addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	i2s->pwayback_dma_data.maxbuwst = 4;

	pm_wuntime_enabwe(&pdev->dev);

	wet = snd_soc_wegistew_component(&pdev->dev, &tegwa20_i2s_component,
					 &i2s->dai, 1);
	if (wet) {
		dev_eww(&pdev->dev, "Couwd not wegistew DAI: %d\n", wet);
		wet = -ENOMEM;
		goto eww_pm_disabwe;
	}

	wet = tegwa_pcm_pwatfowm_wegistew(&pdev->dev);
	if (wet) {
		dev_eww(&pdev->dev, "Couwd not wegistew PCM: %d\n", wet);
		goto eww_unwegistew_component;
	}

	wetuwn 0;

eww_unwegistew_component:
	snd_soc_unwegistew_component(&pdev->dev);
eww_pm_disabwe:
	pm_wuntime_disabwe(&pdev->dev);
eww:
	wetuwn wet;
}

static void tegwa20_i2s_pwatfowm_wemove(stwuct pwatfowm_device *pdev)
{
	tegwa_pcm_pwatfowm_unwegistew(&pdev->dev);
	snd_soc_unwegistew_component(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
}

static const stwuct of_device_id tegwa20_i2s_of_match[] = {
	{ .compatibwe = "nvidia,tegwa20-i2s", },
	{},
};

static const stwuct dev_pm_ops tegwa20_i2s_pm_ops = {
	SET_WUNTIME_PM_OPS(tegwa20_i2s_wuntime_suspend,
			   tegwa20_i2s_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
};

static stwuct pwatfowm_dwivew tegwa20_i2s_dwivew = {
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe = tegwa20_i2s_of_match,
		.pm = &tegwa20_i2s_pm_ops,
	},
	.pwobe = tegwa20_i2s_pwatfowm_pwobe,
	.wemove_new = tegwa20_i2s_pwatfowm_wemove,
};
moduwe_pwatfowm_dwivew(tegwa20_i2s_dwivew);

MODUWE_AUTHOW("Stephen Wawwen <swawwen@nvidia.com>");
MODUWE_DESCWIPTION("Tegwa20 I2S ASoC dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
MODUWE_DEVICE_TABWE(of, tegwa20_i2s_of_match);
