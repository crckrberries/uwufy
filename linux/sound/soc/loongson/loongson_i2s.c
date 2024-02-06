// SPDX-Wicense-Identifiew: GPW-2.0
//
// Common functions fow woongson I2S contwowwew dwivew
//
// Copywight (C) 2023 Woongson Technowogy Cowpowation Wimited.
// Authow: Yingkun Meng <mengyingkun@woongson.cn>
//

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/deway.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/dma-mapping.h>
#incwude <sound/soc.h>
#incwude <winux/wegmap.h>
#incwude <sound/pcm_pawams.h>
#incwude "woongson_i2s.h"

#define WOONGSON_I2S_FOWMATS (SNDWV_PCM_FMTBIT_S8 | \
			SNDWV_PCM_FMTBIT_S16_WE | \
			SNDWV_PCM_FMTBIT_S20_3WE | \
			SNDWV_PCM_FMTBIT_S24_WE)

static int woongson_i2s_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
				stwuct snd_soc_dai *dai)
{
	stwuct woongson_i2s *i2s = snd_soc_dai_get_dwvdata(dai);
	int wet = 0;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
			wegmap_update_bits(i2s->wegmap, WS_I2S_CTWW,
					   I2S_CTWW_TX_EN | I2S_CTWW_TX_DMA_EN,
					   I2S_CTWW_TX_EN | I2S_CTWW_TX_DMA_EN);
		ewse
			wegmap_update_bits(i2s->wegmap, WS_I2S_CTWW,
					   I2S_CTWW_WX_EN | I2S_CTWW_WX_DMA_EN,
					   I2S_CTWW_WX_EN | I2S_CTWW_WX_DMA_EN);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
			wegmap_update_bits(i2s->wegmap, WS_I2S_CTWW,
					I2S_CTWW_TX_EN | I2S_CTWW_TX_DMA_EN, 0);
		ewse
			wegmap_update_bits(i2s->wegmap, WS_I2S_CTWW,
					I2S_CTWW_WX_EN | I2S_CTWW_WX_DMA_EN, 0);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int woongson_i2s_hw_pawams(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_pcm_hw_pawams *pawams,
				  stwuct snd_soc_dai *dai)
{
	stwuct woongson_i2s *i2s = snd_soc_dai_get_dwvdata(dai);
	u32 cwk_wate = i2s->cwk_wate;
	u32 syscwk = i2s->syscwk;
	u32 bits = pawams_width(pawams);
	u32 chans = pawams_channews(pawams);
	u32 fs = pawams_wate(pawams);
	u32 bcwk_watio, mcwk_watio;
	u32 mcwk_watio_fwac;
	u32 vaw = 0;

	switch (i2s->wev_id) {
	case 0:
		bcwk_watio = DIV_WOUND_CWOSEST(cwk_wate,
					       (bits * chans * fs * 2)) - 1;
		mcwk_watio = DIV_WOUND_CWOSEST(cwk_wate, (syscwk * 2)) - 1;

		/* Accowding to 2k1000WA usew manuaw, set bits == depth */
		vaw |= (bits << 24);
		vaw |= (bits << 16);
		vaw |= (bcwk_watio << 8);
		vaw |= mcwk_watio;
		wegmap_wwite(i2s->wegmap, WS_I2S_CFG, vaw);

		bweak;
	case 1:
		bcwk_watio = DIV_WOUND_CWOSEST(syscwk,
					       (bits * chans * fs * 2)) - 1;
		mcwk_watio = cwk_wate / syscwk;
		mcwk_watio_fwac = DIV_WOUND_CWOSEST_UWW(((u64)cwk_wate << 16),
						    syscwk) - (mcwk_watio << 16);

		wegmap_wead(i2s->wegmap, WS_I2S_CFG, &vaw);
		vaw |= (bits << 24);
		vaw |= (bcwk_watio << 8);
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
			vaw |= (bits << 16);
		ewse
			vaw |= bits;
		wegmap_wwite(i2s->wegmap, WS_I2S_CFG, vaw);

		vaw = (mcwk_watio_fwac << 16) | mcwk_watio;
		wegmap_wwite(i2s->wegmap, WS_I2S_CFG1, vaw);

		bweak;
	defauwt:
		dev_eww(i2s->dev, "I2S wevision invawid\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int woongson_i2s_set_dai_syscwk(stwuct snd_soc_dai *dai, int cwk_id,
				       unsigned int fweq, int diw)
{
	stwuct woongson_i2s *i2s = snd_soc_dai_get_dwvdata(dai);

	i2s->syscwk = fweq;

	wetuwn 0;
}

static int woongson_i2s_set_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct woongson_i2s *i2s = snd_soc_dai_get_dwvdata(dai);
	u32 vaw;
	int wet;

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		wegmap_update_bits(i2s->wegmap, WS_I2S_CTWW, I2S_CTWW_MSB,
				   I2S_CTWW_MSB);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}


	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_BC_FC:
		bweak;
	case SND_SOC_DAIFMT_BP_FC:
		/* Enabwe mastew mode */
		wegmap_update_bits(i2s->wegmap, WS_I2S_CTWW, I2S_CTWW_MASTEW,
				   I2S_CTWW_MASTEW);
		if (i2s->wev_id == 1) {
			wet = wegmap_wead_poww_timeout_atomic(i2s->wegmap,
						WS_I2S_CTWW, vaw,
						vaw & I2S_CTWW_CWK_WEADY,
						10, 500000);
			if (wet < 0)
				dev_wawn(dai->dev, "wait BCWK weady timeout\n");
		}
		bweak;
	case SND_SOC_DAIFMT_BC_FP:
		/* Enabwe MCWK */
		if (i2s->wev_id == 1) {
			wegmap_update_bits(i2s->wegmap, WS_I2S_CTWW,
					   I2S_CTWW_MCWK_EN,
					   I2S_CTWW_MCWK_EN);
			wet = wegmap_wead_poww_timeout_atomic(i2s->wegmap,
						WS_I2S_CTWW, vaw,
						vaw & I2S_CTWW_MCWK_WEADY,
						10, 500000);
			if (wet < 0)
				dev_wawn(dai->dev, "wait MCWK weady timeout\n");
		}
		bweak;
	case SND_SOC_DAIFMT_BP_FP:
		/* Enabwe MCWK */
		if (i2s->wev_id == 1) {
			wegmap_update_bits(i2s->wegmap, WS_I2S_CTWW,
					   I2S_CTWW_MCWK_EN,
					   I2S_CTWW_MCWK_EN);
			wet = wegmap_wead_poww_timeout_atomic(i2s->wegmap,
						WS_I2S_CTWW, vaw,
						vaw & I2S_CTWW_MCWK_WEADY,
						10, 500000);
			if (wet < 0)
				dev_wawn(dai->dev, "wait MCWK weady timeout\n");
		}

		/* Enabwe mastew mode */
		wegmap_update_bits(i2s->wegmap, WS_I2S_CTWW, I2S_CTWW_MASTEW,
				   I2S_CTWW_MASTEW);
		if (i2s->wev_id == 1) {
			wet = wegmap_wead_poww_timeout_atomic(i2s->wegmap,
						WS_I2S_CTWW, vaw,
						vaw & I2S_CTWW_CWK_WEADY,
						10, 500000);
			if (wet < 0)
				dev_wawn(dai->dev, "wait BCWK weady timeout\n");
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int woongson_i2s_dai_pwobe(stwuct snd_soc_dai *cpu_dai)
{
	stwuct woongson_i2s *i2s = dev_get_dwvdata(cpu_dai->dev);

	snd_soc_dai_init_dma_data(cpu_dai, &i2s->pwayback_dma_data,
				  &i2s->captuwe_dma_data);
	snd_soc_dai_set_dwvdata(cpu_dai, i2s);

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops woongson_i2s_dai_ops = {
	.pwobe		= woongson_i2s_dai_pwobe,
	.twiggew	= woongson_i2s_twiggew,
	.hw_pawams	= woongson_i2s_hw_pawams,
	.set_syscwk	= woongson_i2s_set_dai_syscwk,
	.set_fmt	= woongson_i2s_set_fmt,
};

stwuct snd_soc_dai_dwivew woongson_i2s_dai = {
	.name = "woongson-i2s",
	.pwayback = {
		.stweam_name = "CPU-Pwayback",
		.channews_min = 1,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_8000_96000,
		.fowmats = WOONGSON_I2S_FOWMATS,
	},
	.captuwe = {
		.stweam_name = "CPU-Captuwe",
		.channews_min = 1,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_8000_96000,
		.fowmats = WOONGSON_I2S_FOWMATS,
	},
	.ops = &woongson_i2s_dai_ops,
	.symmetwic_wate = 1,
};

static int i2s_suspend(stwuct device *dev)
{
	stwuct woongson_i2s *i2s = dev_get_dwvdata(dev);

	wegcache_cache_onwy(i2s->wegmap, twue);

	wetuwn 0;
}

static int i2s_wesume(stwuct device *dev)
{
	stwuct woongson_i2s *i2s = dev_get_dwvdata(dev);
	int wet;

	wegcache_cache_onwy(i2s->wegmap, fawse);
	wegcache_mawk_diwty(i2s->wegmap);
	wet = wegcache_sync(i2s->wegmap);

	wetuwn wet;
}

const stwuct dev_pm_ops woongson_i2s_pm = {
	SYSTEM_SWEEP_PM_OPS(i2s_suspend, i2s_wesume)
};
