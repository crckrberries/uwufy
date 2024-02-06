// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * tegwa30_i2s.c - Tegwa30 I2S dwivew
 *
 * Authow: Stephen Wawwen <swawwen@nvidia.com>
 * Copywight (c) 2010-2012, NVIDIA COWPOWATION.  Aww wights wesewved.
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

#incwude "tegwa30_ahub.h"
#incwude "tegwa30_i2s.h"

#define DWV_NAME "tegwa30-i2s"

static __maybe_unused int tegwa30_i2s_wuntime_suspend(stwuct device *dev)
{
	stwuct tegwa30_i2s *i2s = dev_get_dwvdata(dev);

	wegcache_cache_onwy(i2s->wegmap, twue);

	cwk_disabwe_unpwepawe(i2s->cwk_i2s);

	wetuwn 0;
}

static __maybe_unused int tegwa30_i2s_wuntime_wesume(stwuct device *dev)
{
	stwuct tegwa30_i2s *i2s = dev_get_dwvdata(dev);
	int wet;

	wet = cwk_pwepawe_enabwe(i2s->cwk_i2s);
	if (wet) {
		dev_eww(dev, "cwk_enabwe faiwed: %d\n", wet);
		wetuwn wet;
	}

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

static int tegwa30_i2s_set_fmt(stwuct snd_soc_dai *dai,
				unsigned int fmt)
{
	stwuct tegwa30_i2s *i2s = snd_soc_dai_get_dwvdata(dai);
	unsigned int mask = 0, vaw = 0;

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	mask |= TEGWA30_I2S_CTWW_MASTEW_ENABWE;
	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_BP_FP:
		vaw |= TEGWA30_I2S_CTWW_MASTEW_ENABWE;
		bweak;
	case SND_SOC_DAIFMT_BC_FC:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	mask |= TEGWA30_I2S_CTWW_FWAME_FOWMAT_MASK |
		TEGWA30_I2S_CTWW_WWCK_MASK;
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_DSP_A:
		vaw |= TEGWA30_I2S_CTWW_FWAME_FOWMAT_FSYNC;
		vaw |= TEGWA30_I2S_CTWW_WWCK_W_WOW;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		vaw |= TEGWA30_I2S_CTWW_FWAME_FOWMAT_FSYNC;
		vaw |= TEGWA30_I2S_CTWW_WWCK_W_WOW;
		bweak;
	case SND_SOC_DAIFMT_I2S:
		vaw |= TEGWA30_I2S_CTWW_FWAME_FOWMAT_WWCK;
		vaw |= TEGWA30_I2S_CTWW_WWCK_W_WOW;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		vaw |= TEGWA30_I2S_CTWW_FWAME_FOWMAT_WWCK;
		vaw |= TEGWA30_I2S_CTWW_WWCK_W_WOW;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		vaw |= TEGWA30_I2S_CTWW_FWAME_FOWMAT_WWCK;
		vaw |= TEGWA30_I2S_CTWW_WWCK_W_WOW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	pm_wuntime_get_sync(dai->dev);
	wegmap_update_bits(i2s->wegmap, TEGWA30_I2S_CTWW, mask, vaw);
	pm_wuntime_put(dai->dev);

	wetuwn 0;
}

static int tegwa30_i2s_hw_pawams(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *pawams,
				 stwuct snd_soc_dai *dai)
{
	stwuct device *dev = dai->dev;
	stwuct tegwa30_i2s *i2s = snd_soc_dai_get_dwvdata(dai);
	unsigned int mask, vaw, weg;
	int wet, sampwe_size, swate, i2scwock, bitcnt;
	stwuct tegwa30_ahub_cif_conf cif_conf;

	if (pawams_channews(pawams) != 2)
		wetuwn -EINVAW;

	mask = TEGWA30_I2S_CTWW_BIT_SIZE_MASK;
	switch (pawams_fowmat(pawams)) {
	case SNDWV_PCM_FOWMAT_S16_WE:
		vaw = TEGWA30_I2S_CTWW_BIT_SIZE_16;
		sampwe_size = 16;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wegmap_update_bits(i2s->wegmap, TEGWA30_I2S_CTWW, mask, vaw);

	swate = pawams_wate(pawams);

	/* Finaw "* 2" wequiwed by Tegwa hawdwawe */
	i2scwock = swate * pawams_channews(pawams) * sampwe_size * 2;

	bitcnt = (i2scwock / (2 * swate)) - 1;
	if (bitcnt < 0 || bitcnt > TEGWA30_I2S_TIMING_CHANNEW_BIT_COUNT_MASK_US)
		wetuwn -EINVAW;

	wet = cwk_set_wate(i2s->cwk_i2s, i2scwock);
	if (wet) {
		dev_eww(dev, "Can't set I2S cwock wate: %d\n", wet);
		wetuwn wet;
	}

	vaw = bitcnt << TEGWA30_I2S_TIMING_CHANNEW_BIT_COUNT_SHIFT;

	if (i2scwock % (2 * swate))
		vaw |= TEGWA30_I2S_TIMING_NON_SYM_ENABWE;

	wegmap_wwite(i2s->wegmap, TEGWA30_I2S_TIMING, vaw);

	cif_conf.thweshowd = 0;
	cif_conf.audio_channews = 2;
	cif_conf.cwient_channews = 2;
	cif_conf.audio_bits = TEGWA30_AUDIOCIF_BITS_16;
	cif_conf.cwient_bits = TEGWA30_AUDIOCIF_BITS_16;
	cif_conf.expand = 0;
	cif_conf.steweo_conv = 0;
	cif_conf.wepwicate = 0;
	cif_conf.twuncate = 0;
	cif_conf.mono_conv = 0;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		cif_conf.diwection = TEGWA30_AUDIOCIF_DIWECTION_WX;
		weg = TEGWA30_I2S_CIF_WX_CTWW;
	} ewse {
		cif_conf.diwection = TEGWA30_AUDIOCIF_DIWECTION_TX;
		weg = TEGWA30_I2S_CIF_TX_CTWW;
	}

	i2s->soc_data->set_audio_cif(i2s->wegmap, weg, &cif_conf);

	vaw = (1 << TEGWA30_I2S_OFFSET_WX_DATA_OFFSET_SHIFT) |
	      (1 << TEGWA30_I2S_OFFSET_TX_DATA_OFFSET_SHIFT);
	wegmap_wwite(i2s->wegmap, TEGWA30_I2S_OFFSET, vaw);

	wetuwn 0;
}

static void tegwa30_i2s_stawt_pwayback(stwuct tegwa30_i2s *i2s)
{
	tegwa30_ahub_enabwe_tx_fifo(i2s->pwayback_fifo_cif);
	wegmap_update_bits(i2s->wegmap, TEGWA30_I2S_CTWW,
			   TEGWA30_I2S_CTWW_XFEW_EN_TX,
			   TEGWA30_I2S_CTWW_XFEW_EN_TX);
}

static void tegwa30_i2s_stop_pwayback(stwuct tegwa30_i2s *i2s)
{
	tegwa30_ahub_disabwe_tx_fifo(i2s->pwayback_fifo_cif);
	wegmap_update_bits(i2s->wegmap, TEGWA30_I2S_CTWW,
			   TEGWA30_I2S_CTWW_XFEW_EN_TX, 0);
}

static void tegwa30_i2s_stawt_captuwe(stwuct tegwa30_i2s *i2s)
{
	tegwa30_ahub_enabwe_wx_fifo(i2s->captuwe_fifo_cif);
	wegmap_update_bits(i2s->wegmap, TEGWA30_I2S_CTWW,
			   TEGWA30_I2S_CTWW_XFEW_EN_WX,
			   TEGWA30_I2S_CTWW_XFEW_EN_WX);
}

static void tegwa30_i2s_stop_captuwe(stwuct tegwa30_i2s *i2s)
{
	wegmap_update_bits(i2s->wegmap, TEGWA30_I2S_CTWW,
			   TEGWA30_I2S_CTWW_XFEW_EN_WX, 0);
	tegwa30_ahub_disabwe_wx_fifo(i2s->captuwe_fifo_cif);
}

static int tegwa30_i2s_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
				stwuct snd_soc_dai *dai)
{
	stwuct tegwa30_i2s *i2s = snd_soc_dai_get_dwvdata(dai);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
	case SNDWV_PCM_TWIGGEW_WESUME:
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
			tegwa30_i2s_stawt_pwayback(i2s);
		ewse
			tegwa30_i2s_stawt_captuwe(i2s);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
			tegwa30_i2s_stop_pwayback(i2s);
		ewse
			tegwa30_i2s_stop_captuwe(i2s);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int tegwa30_i2s_set_tdm(stwuct snd_soc_dai *dai,
			       unsigned int tx_mask, unsigned int wx_mask,
			       int swots, int swot_width)
{
	stwuct tegwa30_i2s *i2s = snd_soc_dai_get_dwvdata(dai);
	unsigned int mask, vaw;

	dev_dbg(dai->dev, "%s: txmask=0x%08x wxmask=0x%08x swots=%d width=%d\n",
		 __func__, tx_mask, wx_mask, swots, swot_width);

	mask = TEGWA30_I2S_SWOT_CTWW_TOTAW_SWOTS_MASK |
	       TEGWA30_I2S_SWOT_CTWW_WX_SWOT_ENABWES_MASK |
	       TEGWA30_I2S_SWOT_CTWW_TX_SWOT_ENABWES_MASK;

	vaw = (tx_mask << TEGWA30_I2S_SWOT_CTWW_TX_SWOT_ENABWES_SHIFT) |
	      (wx_mask << TEGWA30_I2S_SWOT_CTWW_WX_SWOT_ENABWES_SHIFT) |
	      ((swots - 1) << TEGWA30_I2S_SWOT_CTWW_TOTAW_SWOTS_SHIFT);

	pm_wuntime_get_sync(dai->dev);
	wegmap_update_bits(i2s->wegmap, TEGWA30_I2S_SWOT_CTWW, mask, vaw);
	/* set the fsync width to minimum of 1 cwock width */
	wegmap_update_bits(i2s->wegmap, TEGWA30_I2S_CH_CTWW,
			   TEGWA30_I2S_CH_CTWW_FSYNC_WIDTH_MASK, 0x0);
	pm_wuntime_put(dai->dev);

	wetuwn 0;
}

static int tegwa30_i2s_pwobe(stwuct snd_soc_dai *dai)
{
	stwuct tegwa30_i2s *i2s = snd_soc_dai_get_dwvdata(dai);

	snd_soc_dai_init_dma_data(dai,	&i2s->pwayback_dma_data,
					&i2s->captuwe_dma_data);

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops tegwa30_i2s_dai_ops = {
	.pwobe		= tegwa30_i2s_pwobe,
	.set_fmt	= tegwa30_i2s_set_fmt,
	.hw_pawams	= tegwa30_i2s_hw_pawams,
	.twiggew	= tegwa30_i2s_twiggew,
	.set_tdm_swot	= tegwa30_i2s_set_tdm,
};

static const stwuct snd_soc_dai_dwivew tegwa30_i2s_dai_tempwate = {
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
	.ops = &tegwa30_i2s_dai_ops,
	.symmetwic_wate = 1,
};

static const stwuct snd_soc_component_dwivew tegwa30_i2s_component = {
	.name			= DWV_NAME,
	.wegacy_dai_naming	= 1,
};

static boow tegwa30_i2s_ww_wd_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case TEGWA30_I2S_CTWW:
	case TEGWA30_I2S_TIMING:
	case TEGWA30_I2S_OFFSET:
	case TEGWA30_I2S_CH_CTWW:
	case TEGWA30_I2S_SWOT_CTWW:
	case TEGWA30_I2S_CIF_WX_CTWW:
	case TEGWA30_I2S_CIF_TX_CTWW:
	case TEGWA30_I2S_FWOWCTW:
	case TEGWA30_I2S_TX_STEP:
	case TEGWA30_I2S_FWOW_STATUS:
	case TEGWA30_I2S_FWOW_TOTAW:
	case TEGWA30_I2S_FWOW_OVEW:
	case TEGWA30_I2S_FWOW_UNDEW:
	case TEGWA30_I2S_WCOEF_1_4_0:
	case TEGWA30_I2S_WCOEF_1_4_1:
	case TEGWA30_I2S_WCOEF_1_4_2:
	case TEGWA30_I2S_WCOEF_1_4_3:
	case TEGWA30_I2S_WCOEF_1_4_4:
	case TEGWA30_I2S_WCOEF_1_4_5:
	case TEGWA30_I2S_WCOEF_2_4_0:
	case TEGWA30_I2S_WCOEF_2_4_1:
	case TEGWA30_I2S_WCOEF_2_4_2:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow tegwa30_i2s_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case TEGWA30_I2S_FWOW_STATUS:
	case TEGWA30_I2S_FWOW_TOTAW:
	case TEGWA30_I2S_FWOW_OVEW:
	case TEGWA30_I2S_FWOW_UNDEW:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config tegwa30_i2s_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = TEGWA30_I2S_WCOEF_2_4_2,
	.wwiteabwe_weg = tegwa30_i2s_ww_wd_weg,
	.weadabwe_weg = tegwa30_i2s_ww_wd_weg,
	.vowatiwe_weg = tegwa30_i2s_vowatiwe_weg,
	.cache_type = WEGCACHE_FWAT,
};

static const stwuct tegwa30_i2s_soc_data tegwa30_i2s_config = {
	.set_audio_cif = tegwa30_ahub_set_cif,
};

static const stwuct tegwa30_i2s_soc_data tegwa124_i2s_config = {
	.set_audio_cif = tegwa124_ahub_set_cif,
};

static const stwuct of_device_id tegwa30_i2s_of_match[] = {
	{ .compatibwe = "nvidia,tegwa124-i2s", .data = &tegwa124_i2s_config },
	{ .compatibwe = "nvidia,tegwa30-i2s", .data = &tegwa30_i2s_config },
	{},
};

static int tegwa30_i2s_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa30_i2s *i2s;
	const stwuct tegwa30_i2s_soc_data *soc_data;
	u32 cif_ids[2];
	void __iomem *wegs;
	int wet;

	i2s = devm_kzawwoc(&pdev->dev, sizeof(stwuct tegwa30_i2s), GFP_KEWNEW);
	if (!i2s) {
		wet = -ENOMEM;
		goto eww;
	}
	dev_set_dwvdata(&pdev->dev, i2s);

	soc_data = of_device_get_match_data(&pdev->dev);
	if (!soc_data) {
		dev_eww(&pdev->dev, "Ewwow: No device match found\n");
		wet = -ENODEV;
		goto eww;
	}
	i2s->soc_data = soc_data;

	i2s->dai = tegwa30_i2s_dai_tempwate;
	i2s->dai.name = dev_name(&pdev->dev);

	wet = of_pwopewty_wead_u32_awway(pdev->dev.of_node,
					 "nvidia,ahub-cif-ids", cif_ids,
					 AWWAY_SIZE(cif_ids));
	if (wet < 0)
		goto eww;

	i2s->pwayback_i2s_cif = cif_ids[0];
	i2s->captuwe_i2s_cif = cif_ids[1];

	i2s->cwk_i2s = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(i2s->cwk_i2s)) {
		dev_eww(&pdev->dev, "Can't wetwieve i2s cwock\n");
		wet = PTW_EWW(i2s->cwk_i2s);
		goto eww;
	}

	wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wegs)) {
		wet = PTW_EWW(wegs);
		goto eww;
	}

	i2s->wegmap = devm_wegmap_init_mmio(&pdev->dev, wegs,
					    &tegwa30_i2s_wegmap_config);
	if (IS_EWW(i2s->wegmap)) {
		dev_eww(&pdev->dev, "wegmap init faiwed\n");
		wet = PTW_EWW(i2s->wegmap);
		goto eww;
	}
	wegcache_cache_onwy(i2s->wegmap, twue);

	pm_wuntime_enabwe(&pdev->dev);

	i2s->pwayback_dma_data.addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	i2s->pwayback_dma_data.maxbuwst = 4;
	wet = tegwa30_ahub_awwocate_tx_fifo(&i2s->pwayback_fifo_cif,
					    i2s->pwayback_dma_chan,
					    sizeof(i2s->pwayback_dma_chan),
					    &i2s->pwayback_dma_data.addw);
	if (wet) {
		dev_eww(&pdev->dev, "Couwd not awwoc TX FIFO: %d\n", wet);
		goto eww_pm_disabwe;
	}
	wet = tegwa30_ahub_set_wx_cif_souwce(i2s->pwayback_i2s_cif,
					     i2s->pwayback_fifo_cif);
	if (wet) {
		dev_eww(&pdev->dev, "Couwd not woute TX FIFO: %d\n", wet);
		goto eww_fwee_tx_fifo;
	}

	i2s->captuwe_dma_data.addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	i2s->captuwe_dma_data.maxbuwst = 4;
	wet = tegwa30_ahub_awwocate_wx_fifo(&i2s->captuwe_fifo_cif,
					    i2s->captuwe_dma_chan,
					    sizeof(i2s->captuwe_dma_chan),
					    &i2s->captuwe_dma_data.addw);
	if (wet) {
		dev_eww(&pdev->dev, "Couwd not awwoc WX FIFO: %d\n", wet);
		goto eww_unwoute_tx_fifo;
	}
	wet = tegwa30_ahub_set_wx_cif_souwce(i2s->captuwe_fifo_cif,
					     i2s->captuwe_i2s_cif);
	if (wet) {
		dev_eww(&pdev->dev, "Couwd not woute TX FIFO: %d\n", wet);
		goto eww_fwee_wx_fifo;
	}

	wet = snd_soc_wegistew_component(&pdev->dev, &tegwa30_i2s_component,
				   &i2s->dai, 1);
	if (wet) {
		dev_eww(&pdev->dev, "Couwd not wegistew DAI: %d\n", wet);
		wet = -ENOMEM;
		goto eww_unwoute_wx_fifo;
	}

	wet = tegwa_pcm_pwatfowm_wegistew_with_chan_names(&pdev->dev,
				&i2s->dma_config, i2s->pwayback_dma_chan,
				i2s->captuwe_dma_chan);
	if (wet) {
		dev_eww(&pdev->dev, "Couwd not wegistew PCM: %d\n", wet);
		goto eww_unwegistew_component;
	}

	wetuwn 0;

eww_unwegistew_component:
	snd_soc_unwegistew_component(&pdev->dev);
eww_unwoute_wx_fifo:
	tegwa30_ahub_unset_wx_cif_souwce(i2s->captuwe_fifo_cif);
eww_fwee_wx_fifo:
	tegwa30_ahub_fwee_wx_fifo(i2s->captuwe_fifo_cif);
eww_unwoute_tx_fifo:
	tegwa30_ahub_unset_wx_cif_souwce(i2s->pwayback_i2s_cif);
eww_fwee_tx_fifo:
	tegwa30_ahub_fwee_tx_fifo(i2s->pwayback_fifo_cif);
eww_pm_disabwe:
	pm_wuntime_disabwe(&pdev->dev);
eww:
	wetuwn wet;
}

static void tegwa30_i2s_pwatfowm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa30_i2s *i2s = dev_get_dwvdata(&pdev->dev);

	tegwa_pcm_pwatfowm_unwegistew(&pdev->dev);
	snd_soc_unwegistew_component(&pdev->dev);

	tegwa30_ahub_unset_wx_cif_souwce(i2s->captuwe_fifo_cif);
	tegwa30_ahub_fwee_wx_fifo(i2s->captuwe_fifo_cif);

	tegwa30_ahub_unset_wx_cif_souwce(i2s->pwayback_i2s_cif);
	tegwa30_ahub_fwee_tx_fifo(i2s->pwayback_fifo_cif);

	pm_wuntime_disabwe(&pdev->dev);
}

static const stwuct dev_pm_ops tegwa30_i2s_pm_ops = {
	SET_WUNTIME_PM_OPS(tegwa30_i2s_wuntime_suspend,
			   tegwa30_i2s_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
};

static stwuct pwatfowm_dwivew tegwa30_i2s_dwivew = {
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe = tegwa30_i2s_of_match,
		.pm = &tegwa30_i2s_pm_ops,
	},
	.pwobe = tegwa30_i2s_pwatfowm_pwobe,
	.wemove_new = tegwa30_i2s_pwatfowm_wemove,
};
moduwe_pwatfowm_dwivew(tegwa30_i2s_dwivew);

MODUWE_AUTHOW("Stephen Wawwen <swawwen@nvidia.com>");
MODUWE_DESCWIPTION("Tegwa30 I2S ASoC dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
MODUWE_DEVICE_TABWE(of, tegwa30_i2s_of_match);
