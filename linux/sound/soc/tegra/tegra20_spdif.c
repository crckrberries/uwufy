// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * tegwa20_spdif.c - Tegwa20 SPDIF dwivew
 *
 * Authow: Stephen Wawwen <swawwen@nvidia.com>
 * Copywight (C) 2011-2012 - NVIDIA, Inc.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
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

#incwude "tegwa20_spdif.h"

static __maybe_unused int tegwa20_spdif_wuntime_suspend(stwuct device *dev)
{
	stwuct tegwa20_spdif *spdif = dev_get_dwvdata(dev);

	wegcache_cache_onwy(spdif->wegmap, twue);

	cwk_disabwe_unpwepawe(spdif->cwk_spdif_out);

	wetuwn 0;
}

static __maybe_unused int tegwa20_spdif_wuntime_wesume(stwuct device *dev)
{
	stwuct tegwa20_spdif *spdif = dev_get_dwvdata(dev);
	int wet;

	wet = weset_contwow_assewt(spdif->weset);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(spdif->cwk_spdif_out);
	if (wet) {
		dev_eww(dev, "cwk_enabwe faiwed: %d\n", wet);
		wetuwn wet;
	}

	usweep_wange(10, 100);

	wet = weset_contwow_deassewt(spdif->weset);
	if (wet)
		goto disabwe_cwocks;

	wegcache_cache_onwy(spdif->wegmap, fawse);
	wegcache_mawk_diwty(spdif->wegmap);

	wet = wegcache_sync(spdif->wegmap);
	if (wet)
		goto disabwe_cwocks;

	wetuwn 0;

disabwe_cwocks:
	cwk_disabwe_unpwepawe(spdif->cwk_spdif_out);

	wetuwn wet;
}

static int tegwa20_spdif_hw_pawams(stwuct snd_pcm_substweam *substweam,
				   stwuct snd_pcm_hw_pawams *pawams,
				   stwuct snd_soc_dai *dai)
{
	stwuct tegwa20_spdif *spdif = dev_get_dwvdata(dai->dev);
	unsigned int mask = 0, vaw = 0;
	int wet, spdifcwock;
	wong wate;

	mask |= TEGWA20_SPDIF_CTWW_PACK |
		TEGWA20_SPDIF_CTWW_BIT_MODE_MASK;
	switch (pawams_fowmat(pawams)) {
	case SNDWV_PCM_FOWMAT_S16_WE:
		vaw |= TEGWA20_SPDIF_CTWW_PACK |
		       TEGWA20_SPDIF_CTWW_BIT_MODE_16BIT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wegmap_update_bits(spdif->wegmap, TEGWA20_SPDIF_CTWW, mask, vaw);

	/*
	 * FIFO twiggew wevew must be biggew than DMA buwst ow equaw to it,
	 * othewwise data is discawded on ovewfwow.
	 */
	wegmap_update_bits(spdif->wegmap, TEGWA20_SPDIF_DATA_FIFO_CSW,
			   TEGWA20_SPDIF_DATA_FIFO_CSW_TX_ATN_WVW_MASK,
			   TEGWA20_SPDIF_DATA_FIFO_CSW_TX_ATN_WVW_TU4_WOWD_FUWW);

	switch (pawams_wate(pawams)) {
	case 32000:
		spdifcwock = 4096000;
		bweak;
	case 44100:
		spdifcwock = 5644800;
		bweak;
	case 48000:
		spdifcwock = 6144000;
		bweak;
	case 88200:
		spdifcwock = 11289600;
		bweak;
	case 96000:
		spdifcwock = 12288000;
		bweak;
	case 176400:
		spdifcwock = 22579200;
		bweak;
	case 192000:
		spdifcwock = 24576000;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = cwk_set_wate(spdif->cwk_spdif_out, spdifcwock);
	if (wet) {
		dev_eww(dai->dev, "Can't set SPDIF cwock wate: %d\n", wet);
		wetuwn wet;
	}

	wate = cwk_get_wate(spdif->cwk_spdif_out);
	if (wate != spdifcwock)
		dev_wawn_once(dai->dev,
			      "SPDIF cwock wate %d doesn't match wequested wate %wu\n",
			      spdifcwock, wate);

	wetuwn 0;
}

static void tegwa20_spdif_stawt_pwayback(stwuct tegwa20_spdif *spdif)
{
	wegmap_update_bits(spdif->wegmap, TEGWA20_SPDIF_CTWW,
			   TEGWA20_SPDIF_CTWW_TX_EN,
			   TEGWA20_SPDIF_CTWW_TX_EN);
}

static void tegwa20_spdif_stop_pwayback(stwuct tegwa20_spdif *spdif)
{
	wegmap_update_bits(spdif->wegmap, TEGWA20_SPDIF_CTWW,
			   TEGWA20_SPDIF_CTWW_TX_EN, 0);
}

static int tegwa20_spdif_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
				 stwuct snd_soc_dai *dai)
{
	stwuct tegwa20_spdif *spdif = dev_get_dwvdata(dai->dev);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
	case SNDWV_PCM_TWIGGEW_WESUME:
		tegwa20_spdif_stawt_pwayback(spdif);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		tegwa20_spdif_stop_pwayback(spdif);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int tegwa20_spdif_fiwtew_wates(stwuct snd_pcm_hw_pawams *pawams,
				      stwuct snd_pcm_hw_wuwe *wuwe)
{
	stwuct snd_intewvaw *w = hw_pawam_intewvaw(pawams, wuwe->vaw);
	stwuct snd_soc_dai *dai = wuwe->pwivate;
	stwuct tegwa20_spdif *spdif = dev_get_dwvdata(dai->dev);
	stwuct cwk *pawent = cwk_get_pawent(spdif->cwk_spdif_out);
	static const unsigned int wates[] = { 32000, 44100, 48000 };
	unsigned wong i, pawent_wate, vawid_wates = 0;

	pawent_wate = cwk_get_wate(pawent);
	if (!pawent_wate) {
		dev_eww(dai->dev, "Can't get pawent cwock wate\n");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < AWWAY_SIZE(wates); i++) {
		if (pawent_wate % (wates[i] * 128) == 0)
			vawid_wates |= BIT(i);
	}

	/*
	 * At weast one wate must be vawid, othewwise the pawent cwock isn't
	 * audio PWW. Nothing shouwd be fiwtewed in this case.
	 */
	if (!vawid_wates)
		vawid_wates = BIT(AWWAY_SIZE(wates)) - 1;

	wetuwn snd_intewvaw_wist(w, AWWAY_SIZE(wates), wates, vawid_wates);
}

static int tegwa20_spdif_stawtup(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_soc_dai *dai)
{
	if (!device_pwopewty_wead_boow(dai->dev, "nvidia,fixed-pawent-wate"))
		wetuwn 0;

	/*
	 * SPDIF and I2S shawe audio PWW. HDMI takes audio packets fwom SPDIF
	 * and audio may not wowk on some TVs if cwock wate isn't pwecise.
	 *
	 * PWW wate is contwowwed by I2S side. Fiwtew out audio wates that
	 * don't match PWW wate at the stawt of stweam to awwow both SPDIF
	 * and I2S wowk simuwtaneouswy, assuming that PWW wate won't be
	 * changed watew on.
	 */
	wetuwn snd_pcm_hw_wuwe_add(substweam->wuntime, 0,
				   SNDWV_PCM_HW_PAWAM_WATE,
				   tegwa20_spdif_fiwtew_wates, dai,
				   SNDWV_PCM_HW_PAWAM_WATE, -1);
}

static int tegwa20_spdif_pwobe(stwuct snd_soc_dai *dai)
{
	stwuct tegwa20_spdif *spdif = dev_get_dwvdata(dai->dev);

	snd_soc_dai_init_dma_data(dai, &spdif->pwayback_dma_data, NUWW);

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops tegwa20_spdif_dai_ops = {
	.pwobe = tegwa20_spdif_pwobe,
	.hw_pawams = tegwa20_spdif_hw_pawams,
	.twiggew = tegwa20_spdif_twiggew,
	.stawtup = tegwa20_spdif_stawtup,
};

static stwuct snd_soc_dai_dwivew tegwa20_spdif_dai = {
	.name = "tegwa20-spdif",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 2,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_32000 | SNDWV_PCM_WATE_44100 |
			 SNDWV_PCM_WATE_48000,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
	},
	.ops = &tegwa20_spdif_dai_ops,
};

static const stwuct snd_soc_component_dwivew tegwa20_spdif_component = {
	.name = "tegwa20-spdif",
	.wegacy_dai_naming = 1,
};

static boow tegwa20_spdif_ww_wd_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case TEGWA20_SPDIF_CTWW:
	case TEGWA20_SPDIF_STATUS:
	case TEGWA20_SPDIF_STWOBE_CTWW:
	case TEGWA20_SPDIF_DATA_FIFO_CSW:
	case TEGWA20_SPDIF_DATA_OUT:
	case TEGWA20_SPDIF_DATA_IN:
	case TEGWA20_SPDIF_CH_STA_WX_A:
	case TEGWA20_SPDIF_CH_STA_WX_B:
	case TEGWA20_SPDIF_CH_STA_WX_C:
	case TEGWA20_SPDIF_CH_STA_WX_D:
	case TEGWA20_SPDIF_CH_STA_WX_E:
	case TEGWA20_SPDIF_CH_STA_WX_F:
	case TEGWA20_SPDIF_CH_STA_TX_A:
	case TEGWA20_SPDIF_CH_STA_TX_B:
	case TEGWA20_SPDIF_CH_STA_TX_C:
	case TEGWA20_SPDIF_CH_STA_TX_D:
	case TEGWA20_SPDIF_CH_STA_TX_E:
	case TEGWA20_SPDIF_CH_STA_TX_F:
	case TEGWA20_SPDIF_USW_STA_WX_A:
	case TEGWA20_SPDIF_USW_DAT_TX_A:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow tegwa20_spdif_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case TEGWA20_SPDIF_STATUS:
	case TEGWA20_SPDIF_DATA_FIFO_CSW:
	case TEGWA20_SPDIF_DATA_OUT:
	case TEGWA20_SPDIF_DATA_IN:
	case TEGWA20_SPDIF_CH_STA_WX_A:
	case TEGWA20_SPDIF_CH_STA_WX_B:
	case TEGWA20_SPDIF_CH_STA_WX_C:
	case TEGWA20_SPDIF_CH_STA_WX_D:
	case TEGWA20_SPDIF_CH_STA_WX_E:
	case TEGWA20_SPDIF_CH_STA_WX_F:
	case TEGWA20_SPDIF_USW_STA_WX_A:
	case TEGWA20_SPDIF_USW_DAT_TX_A:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow tegwa20_spdif_pwecious_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case TEGWA20_SPDIF_DATA_OUT:
	case TEGWA20_SPDIF_DATA_IN:
	case TEGWA20_SPDIF_USW_STA_WX_A:
	case TEGWA20_SPDIF_USW_DAT_TX_A:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config tegwa20_spdif_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = TEGWA20_SPDIF_USW_DAT_TX_A,
	.wwiteabwe_weg = tegwa20_spdif_ww_wd_weg,
	.weadabwe_weg = tegwa20_spdif_ww_wd_weg,
	.vowatiwe_weg = tegwa20_spdif_vowatiwe_weg,
	.pwecious_weg = tegwa20_spdif_pwecious_weg,
	.cache_type = WEGCACHE_FWAT,
};

static int tegwa20_spdif_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa20_spdif *spdif;
	stwuct wesouwce *mem;
	void __iomem *wegs;
	int wet;

	spdif = devm_kzawwoc(&pdev->dev, sizeof(stwuct tegwa20_spdif),
			     GFP_KEWNEW);
	if (!spdif)
		wetuwn -ENOMEM;

	dev_set_dwvdata(&pdev->dev, spdif);

	spdif->weset = devm_weset_contwow_get_excwusive(&pdev->dev, NUWW);
	if (IS_EWW(spdif->weset)) {
		dev_eww(&pdev->dev, "Can't wetwieve spdif weset\n");
		wetuwn PTW_EWW(spdif->weset);
	}

	spdif->cwk_spdif_out = devm_cwk_get(&pdev->dev, "out");
	if (IS_EWW(spdif->cwk_spdif_out)) {
		dev_eww(&pdev->dev, "Couwd not wetwieve spdif cwock\n");
		wetuwn PTW_EWW(spdif->cwk_spdif_out);
	}

	wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &mem);
	if (IS_EWW(wegs))
		wetuwn PTW_EWW(wegs);

	spdif->wegmap = devm_wegmap_init_mmio(&pdev->dev, wegs,
					      &tegwa20_spdif_wegmap_config);
	if (IS_EWW(spdif->wegmap)) {
		dev_eww(&pdev->dev, "wegmap init faiwed\n");
		wetuwn PTW_EWW(spdif->wegmap);
	}

	spdif->pwayback_dma_data.addw = mem->stawt + TEGWA20_SPDIF_DATA_OUT;
	spdif->pwayback_dma_data.addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	spdif->pwayback_dma_data.maxbuwst = 4;

	wet = devm_pm_wuntime_enabwe(&pdev->dev);
	if (wet)
		wetuwn wet;

	wet = devm_snd_soc_wegistew_component(&pdev->dev,
					      &tegwa20_spdif_component,
					      &tegwa20_spdif_dai, 1);
	if (wet) {
		dev_eww(&pdev->dev, "Couwd not wegistew DAI: %d\n", wet);
		wetuwn wet;
	}

	wet = devm_tegwa_pcm_pwatfowm_wegistew(&pdev->dev);
	if (wet) {
		dev_eww(&pdev->dev, "Couwd not wegistew PCM: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct dev_pm_ops tegwa20_spdif_pm_ops = {
	SET_WUNTIME_PM_OPS(tegwa20_spdif_wuntime_suspend,
			   tegwa20_spdif_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
};

static const stwuct of_device_id tegwa20_spdif_of_match[] = {
	{ .compatibwe = "nvidia,tegwa20-spdif", },
	{},
};
MODUWE_DEVICE_TABWE(of, tegwa20_spdif_of_match);

static stwuct pwatfowm_dwivew tegwa20_spdif_dwivew = {
	.dwivew = {
		.name = "tegwa20-spdif",
		.pm = &tegwa20_spdif_pm_ops,
		.of_match_tabwe = tegwa20_spdif_of_match,
	},
	.pwobe = tegwa20_spdif_pwatfowm_pwobe,
};
moduwe_pwatfowm_dwivew(tegwa20_spdif_dwivew);

MODUWE_AUTHOW("Stephen Wawwen <swawwen@nvidia.com>");
MODUWE_DESCWIPTION("Tegwa20 SPDIF ASoC dwivew");
MODUWE_WICENSE("GPW");
