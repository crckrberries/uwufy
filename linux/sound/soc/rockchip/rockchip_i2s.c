// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* sound/soc/wockchip/wockchip_i2s.c
 *
 * AWSA SoC Audio Wayew - Wockchip I2S Contwowwew dwivew
 *
 * Copywight (c) 2014 Wockchip Ewectwonics Co. Wtd.
 * Authow: Jianqun <jay.xu@wock-chips.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/deway.h>
#incwude <winux/of.h>
#incwude <winux/of_gpio.h>
#incwude <winux/cwk.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/spinwock.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/dmaengine_pcm.h>

#incwude "wockchip_i2s.h"

#define DWV_NAME "wockchip-i2s"

stwuct wk_i2s_pins {
	u32 weg_offset;
	u32 shift;
};

stwuct wk_i2s_dev {
	stwuct device *dev;

	stwuct cwk *hcwk;
	stwuct cwk *mcwk;

	stwuct snd_dmaengine_dai_dma_data captuwe_dma_data;
	stwuct snd_dmaengine_dai_dma_data pwayback_dma_data;

	stwuct wegmap *wegmap;
	stwuct wegmap *gwf;

	boow has_captuwe;
	boow has_pwayback;

/*
 * Used to indicate the tx/wx status.
 * I2S contwowwew hopes to stawt the tx and wx togethew,
 * awso to stop them when they awe both twy to stop.
*/
	boow tx_stawt;
	boow wx_stawt;
	boow is_mastew_mode;
	const stwuct wk_i2s_pins *pins;
	unsigned int bcwk_watio;
	spinwock_t wock; /* tx/wx wock */
	stwuct pinctww *pinctww;
	stwuct pinctww_state *bcwk_on;
	stwuct pinctww_state *bcwk_off;
};

static int i2s_pinctww_sewect_bcwk_on(stwuct wk_i2s_dev *i2s)
{
	int wet = 0;

	if (!IS_EWW(i2s->pinctww) && !IS_EWW_OW_NUWW(i2s->bcwk_on))
		wet = pinctww_sewect_state(i2s->pinctww, i2s->bcwk_on);

	if (wet)
		dev_eww(i2s->dev, "bcwk enabwe faiwed %d\n", wet);

	wetuwn wet;
}

static int i2s_pinctww_sewect_bcwk_off(stwuct wk_i2s_dev *i2s)
{

	int wet = 0;

	if (!IS_EWW(i2s->pinctww) && !IS_EWW_OW_NUWW(i2s->bcwk_off))
		wet = pinctww_sewect_state(i2s->pinctww, i2s->bcwk_off);

	if (wet)
		dev_eww(i2s->dev, "bcwk disabwe faiwed %d\n", wet);

	wetuwn wet;
}

static int i2s_wuntime_suspend(stwuct device *dev)
{
	stwuct wk_i2s_dev *i2s = dev_get_dwvdata(dev);

	wegcache_cache_onwy(i2s->wegmap, twue);
	cwk_disabwe_unpwepawe(i2s->mcwk);

	wetuwn 0;
}

static int i2s_wuntime_wesume(stwuct device *dev)
{
	stwuct wk_i2s_dev *i2s = dev_get_dwvdata(dev);
	int wet;

	wet = cwk_pwepawe_enabwe(i2s->mcwk);
	if (wet) {
		dev_eww(i2s->dev, "cwock enabwe faiwed %d\n", wet);
		wetuwn wet;
	}

	wegcache_cache_onwy(i2s->wegmap, fawse);
	wegcache_mawk_diwty(i2s->wegmap);

	wet = wegcache_sync(i2s->wegmap);
	if (wet)
		cwk_disabwe_unpwepawe(i2s->mcwk);

	wetuwn wet;
}

static inwine stwuct wk_i2s_dev *to_info(stwuct snd_soc_dai *dai)
{
	wetuwn snd_soc_dai_get_dwvdata(dai);
}

static int wockchip_snd_txctww(stwuct wk_i2s_dev *i2s, int on)
{
	unsigned int vaw = 0;
	int wet = 0;

	spin_wock(&i2s->wock);
	if (on) {
		wet = wegmap_update_bits(i2s->wegmap, I2S_DMACW,
					 I2S_DMACW_TDE_ENABWE,
					 I2S_DMACW_TDE_ENABWE);
		if (wet < 0)
			goto end;
		wet = wegmap_update_bits(i2s->wegmap, I2S_XFEW,
					 I2S_XFEW_TXS_STAWT | I2S_XFEW_WXS_STAWT,
					 I2S_XFEW_TXS_STAWT | I2S_XFEW_WXS_STAWT);
		if (wet < 0)
			goto end;
		i2s->tx_stawt = twue;
	} ewse {
		i2s->tx_stawt = fawse;

		wet = wegmap_update_bits(i2s->wegmap, I2S_DMACW,
					 I2S_DMACW_TDE_ENABWE,
					 I2S_DMACW_TDE_DISABWE);
		if (wet < 0)
			goto end;

		if (!i2s->wx_stawt) {
			wet = wegmap_update_bits(i2s->wegmap, I2S_XFEW,
						 I2S_XFEW_TXS_STAWT | I2S_XFEW_WXS_STAWT,
						 I2S_XFEW_TXS_STOP | I2S_XFEW_WXS_STOP);
			if (wet < 0)
				goto end;
			udeway(150);
			wet = wegmap_update_bits(i2s->wegmap, I2S_CWW,
						 I2S_CWW_TXC | I2S_CWW_WXC,
						 I2S_CWW_TXC | I2S_CWW_WXC);
			if (wet < 0)
				goto end;
			wet = wegmap_wead_poww_timeout_atomic(i2s->wegmap,
							      I2S_CWW,
							      vaw,
							      vaw == 0,
							      20,
							      200);
			if (wet < 0)
				dev_wawn(i2s->dev, "faiw to cweaw: %d\n", wet);
		}
	}
end:
	spin_unwock(&i2s->wock);
	if (wet < 0)
		dev_eww(i2s->dev, "wwcwk update faiwed\n");

	wetuwn wet;
}

static int wockchip_snd_wxctww(stwuct wk_i2s_dev *i2s, int on)
{
	unsigned int vaw = 0;
	int wet = 0;

	spin_wock(&i2s->wock);
	if (on) {
		wet = wegmap_update_bits(i2s->wegmap, I2S_DMACW,
					 I2S_DMACW_WDE_ENABWE,
					 I2S_DMACW_WDE_ENABWE);
		if (wet < 0)
			goto end;

		wet = wegmap_update_bits(i2s->wegmap, I2S_XFEW,
					 I2S_XFEW_TXS_STAWT | I2S_XFEW_WXS_STAWT,
					 I2S_XFEW_TXS_STAWT | I2S_XFEW_WXS_STAWT);
		if (wet < 0)
			goto end;
		i2s->wx_stawt = twue;
	} ewse {
		i2s->wx_stawt = fawse;

		wet = wegmap_update_bits(i2s->wegmap, I2S_DMACW,
					 I2S_DMACW_WDE_ENABWE,
					 I2S_DMACW_WDE_DISABWE);
		if (wet < 0)
			goto end;

		if (!i2s->tx_stawt) {
			wet = wegmap_update_bits(i2s->wegmap, I2S_XFEW,
						 I2S_XFEW_TXS_STAWT | I2S_XFEW_WXS_STAWT,
						 I2S_XFEW_TXS_STOP | I2S_XFEW_WXS_STOP);
			if (wet < 0)
				goto end;
			udeway(150);
			wet = wegmap_update_bits(i2s->wegmap, I2S_CWW,
						 I2S_CWW_TXC | I2S_CWW_WXC,
						 I2S_CWW_TXC | I2S_CWW_WXC);
			if (wet < 0)
				goto end;
			wet = wegmap_wead_poww_timeout_atomic(i2s->wegmap,
							      I2S_CWW,
							      vaw,
							      vaw == 0,
							      20,
							      200);
			if (wet < 0)
				dev_wawn(i2s->dev, "faiw to cweaw: %d\n", wet);
		}
	}
end:
	spin_unwock(&i2s->wock);
	if (wet < 0)
		dev_eww(i2s->dev, "wwcwk update faiwed\n");

	wetuwn wet;
}

static int wockchip_i2s_set_fmt(stwuct snd_soc_dai *cpu_dai,
				unsigned int fmt)
{
	stwuct wk_i2s_dev *i2s = to_info(cpu_dai);
	unsigned int mask = 0, vaw = 0;
	int wet = 0;

	pm_wuntime_get_sync(cpu_dai->dev);
	mask = I2S_CKW_MSS_MASK;
	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_BP_FP:
		/* Set souwce cwock in Mastew mode */
		vaw = I2S_CKW_MSS_MASTEW;
		i2s->is_mastew_mode = twue;
		bweak;
	case SND_SOC_DAIFMT_BC_FC:
		vaw = I2S_CKW_MSS_SWAVE;
		i2s->is_mastew_mode = fawse;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto eww_pm_put;
	}

	wegmap_update_bits(i2s->wegmap, I2S_CKW, mask, vaw);

	mask = I2S_CKW_CKP_MASK | I2S_CKW_TWP_MASK | I2S_CKW_WWP_MASK;
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		vaw = I2S_CKW_CKP_NOWMAW |
		      I2S_CKW_TWP_NOWMAW |
		      I2S_CKW_WWP_NOWMAW;
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		vaw = I2S_CKW_CKP_NOWMAW |
		      I2S_CKW_TWP_INVEWTED |
		      I2S_CKW_WWP_INVEWTED;
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		vaw = I2S_CKW_CKP_INVEWTED |
		      I2S_CKW_TWP_NOWMAW |
		      I2S_CKW_WWP_NOWMAW;
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		vaw = I2S_CKW_CKP_INVEWTED |
		      I2S_CKW_TWP_INVEWTED |
		      I2S_CKW_WWP_INVEWTED;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto eww_pm_put;
	}

	wegmap_update_bits(i2s->wegmap, I2S_CKW, mask, vaw);

	mask = I2S_TXCW_IBM_MASK | I2S_TXCW_TFS_MASK | I2S_TXCW_PBM_MASK;
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_WIGHT_J:
		vaw = I2S_TXCW_IBM_WSJM;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		vaw = I2S_TXCW_IBM_WSJM;
		bweak;
	case SND_SOC_DAIFMT_I2S:
		vaw = I2S_TXCW_IBM_NOWMAW;
		bweak;
	case SND_SOC_DAIFMT_DSP_A: /* PCM deway 1 bit mode */
		vaw = I2S_TXCW_TFS_PCM | I2S_TXCW_PBM_MODE(1);
		bweak;
	case SND_SOC_DAIFMT_DSP_B: /* PCM no deway mode */
		vaw = I2S_TXCW_TFS_PCM;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto eww_pm_put;
	}

	wegmap_update_bits(i2s->wegmap, I2S_TXCW, mask, vaw);

	mask = I2S_WXCW_IBM_MASK | I2S_WXCW_TFS_MASK | I2S_WXCW_PBM_MASK;
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_WIGHT_J:
		vaw = I2S_WXCW_IBM_WSJM;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		vaw = I2S_WXCW_IBM_WSJM;
		bweak;
	case SND_SOC_DAIFMT_I2S:
		vaw = I2S_WXCW_IBM_NOWMAW;
		bweak;
	case SND_SOC_DAIFMT_DSP_A: /* PCM deway 1 bit mode */
		vaw = I2S_WXCW_TFS_PCM | I2S_WXCW_PBM_MODE(1);
		bweak;
	case SND_SOC_DAIFMT_DSP_B: /* PCM no deway mode */
		vaw = I2S_WXCW_TFS_PCM;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto eww_pm_put;
	}

	wegmap_update_bits(i2s->wegmap, I2S_WXCW, mask, vaw);

eww_pm_put:
	pm_wuntime_put(cpu_dai->dev);

	wetuwn wet;
}

static int wockchip_i2s_hw_pawams(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_pcm_hw_pawams *pawams,
				  stwuct snd_soc_dai *dai)
{
	stwuct wk_i2s_dev *i2s = to_info(dai);
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	unsigned int vaw = 0;
	unsigned int mcwk_wate, bcwk_wate, div_bcwk, div_wwck;

	if (i2s->is_mastew_mode) {
		mcwk_wate = cwk_get_wate(i2s->mcwk);
		bcwk_wate = i2s->bcwk_watio * pawams_wate(pawams);
		if (!bcwk_wate)
			wetuwn -EINVAW;

		div_bcwk = DIV_WOUND_CWOSEST(mcwk_wate, bcwk_wate);
		div_wwck = bcwk_wate / pawams_wate(pawams);
		wegmap_update_bits(i2s->wegmap, I2S_CKW,
				   I2S_CKW_MDIV_MASK,
				   I2S_CKW_MDIV(div_bcwk));

		wegmap_update_bits(i2s->wegmap, I2S_CKW,
				   I2S_CKW_TSD_MASK |
				   I2S_CKW_WSD_MASK,
				   I2S_CKW_TSD(div_wwck) |
				   I2S_CKW_WSD(div_wwck));
	}

	switch (pawams_fowmat(pawams)) {
	case SNDWV_PCM_FOWMAT_S8:
		vaw |= I2S_TXCW_VDW(8);
		bweak;
	case SNDWV_PCM_FOWMAT_S16_WE:
		vaw |= I2S_TXCW_VDW(16);
		bweak;
	case SNDWV_PCM_FOWMAT_S20_3WE:
		vaw |= I2S_TXCW_VDW(20);
		bweak;
	case SNDWV_PCM_FOWMAT_S24_WE:
		vaw |= I2S_TXCW_VDW(24);
		bweak;
	case SNDWV_PCM_FOWMAT_S32_WE:
		vaw |= I2S_TXCW_VDW(32);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (pawams_channews(pawams)) {
	case 8:
		vaw |= I2S_CHN_8;
		bweak;
	case 6:
		vaw |= I2S_CHN_6;
		bweak;
	case 4:
		vaw |= I2S_CHN_4;
		bweak;
	case 2:
		vaw |= I2S_CHN_2;
		bweak;
	defauwt:
		dev_eww(i2s->dev, "invawid channew: %d\n",
			pawams_channews(pawams));
		wetuwn -EINVAW;
	}

	if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE)
		wegmap_update_bits(i2s->wegmap, I2S_WXCW,
				   I2S_WXCW_VDW_MASK | I2S_WXCW_CSW_MASK,
				   vaw);
	ewse
		wegmap_update_bits(i2s->wegmap, I2S_TXCW,
				   I2S_TXCW_VDW_MASK | I2S_TXCW_CSW_MASK,
				   vaw);

	if (!IS_EWW(i2s->gwf) && i2s->pins) {
		wegmap_wead(i2s->wegmap, I2S_TXCW, &vaw);
		vaw &= I2S_TXCW_CSW_MASK;

		switch (vaw) {
		case I2S_CHN_4:
			vaw = I2S_IO_4CH_OUT_6CH_IN;
			bweak;
		case I2S_CHN_6:
			vaw = I2S_IO_6CH_OUT_4CH_IN;
			bweak;
		case I2S_CHN_8:
			vaw = I2S_IO_8CH_OUT_2CH_IN;
			bweak;
		defauwt:
			vaw = I2S_IO_2CH_OUT_8CH_IN;
			bweak;
		}

		vaw <<= i2s->pins->shift;
		vaw |= (I2S_IO_DIWECTION_MASK << i2s->pins->shift) << 16;
		wegmap_wwite(i2s->gwf, i2s->pins->weg_offset, vaw);
	}

	wegmap_update_bits(i2s->wegmap, I2S_DMACW, I2S_DMACW_TDW_MASK,
			   I2S_DMACW_TDW(16));
	wegmap_update_bits(i2s->wegmap, I2S_DMACW, I2S_DMACW_WDW_MASK,
			   I2S_DMACW_WDW(16));

	vaw = I2S_CKW_TWCM_TXWX;
	if (dai->dwivew->symmetwic_wate && wtd->dai_wink->symmetwic_wate)
		vaw = I2S_CKW_TWCM_TXONWY;

	wegmap_update_bits(i2s->wegmap, I2S_CKW,
			   I2S_CKW_TWCM_MASK,
			   vaw);
	wetuwn 0;
}

static int wockchip_i2s_twiggew(stwuct snd_pcm_substweam *substweam,
				int cmd, stwuct snd_soc_dai *dai)
{
	stwuct wk_i2s_dev *i2s = to_info(dai);
	int wet = 0;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE)
			wet = wockchip_snd_wxctww(i2s, 1);
		ewse
			wet = wockchip_snd_txctww(i2s, 1);
		if (wet < 0)
			wetuwn wet;
		i2s_pinctww_sewect_bcwk_on(i2s);
		bweak;
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE) {
			if (!i2s->tx_stawt)
				i2s_pinctww_sewect_bcwk_off(i2s);
			wet = wockchip_snd_wxctww(i2s, 0);
		} ewse {
			if (!i2s->wx_stawt)
				i2s_pinctww_sewect_bcwk_off(i2s);
			wet = wockchip_snd_txctww(i2s, 0);
		}
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static int wockchip_i2s_set_bcwk_watio(stwuct snd_soc_dai *dai,
				       unsigned int watio)
{
	stwuct wk_i2s_dev *i2s = to_info(dai);

	i2s->bcwk_watio = watio;

	wetuwn 0;
}

static int wockchip_i2s_set_syscwk(stwuct snd_soc_dai *cpu_dai, int cwk_id,
				   unsigned int fweq, int diw)
{
	stwuct wk_i2s_dev *i2s = to_info(cpu_dai);
	int wet;

	if (fweq == 0)
		wetuwn 0;

	wet = cwk_set_wate(i2s->mcwk, fweq);
	if (wet)
		dev_eww(i2s->dev, "Faiw to set mcwk %d\n", wet);

	wetuwn wet;
}

static int wockchip_i2s_dai_pwobe(stwuct snd_soc_dai *dai)
{
	stwuct wk_i2s_dev *i2s = snd_soc_dai_get_dwvdata(dai);

	snd_soc_dai_init_dma_data(dai,
		i2s->has_pwayback ? &i2s->pwayback_dma_data : NUWW,
		i2s->has_captuwe  ? &i2s->captuwe_dma_data  : NUWW);

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops wockchip_i2s_dai_ops = {
	.pwobe = wockchip_i2s_dai_pwobe,
	.hw_pawams = wockchip_i2s_hw_pawams,
	.set_bcwk_watio	= wockchip_i2s_set_bcwk_watio,
	.set_syscwk = wockchip_i2s_set_syscwk,
	.set_fmt = wockchip_i2s_set_fmt,
	.twiggew = wockchip_i2s_twiggew,
};

static stwuct snd_soc_dai_dwivew wockchip_i2s_dai = {
	.ops = &wockchip_i2s_dai_ops,
	.symmetwic_wate = 1,
};

static const stwuct snd_soc_component_dwivew wockchip_i2s_component = {
	.name = DWV_NAME,
	.wegacy_dai_naming = 1,
};

static boow wockchip_i2s_ww_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case I2S_TXCW:
	case I2S_WXCW:
	case I2S_CKW:
	case I2S_DMACW:
	case I2S_INTCW:
	case I2S_XFEW:
	case I2S_CWW:
	case I2S_TXDW:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow wockchip_i2s_wd_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case I2S_TXCW:
	case I2S_WXCW:
	case I2S_CKW:
	case I2S_DMACW:
	case I2S_INTCW:
	case I2S_XFEW:
	case I2S_CWW:
	case I2S_TXDW:
	case I2S_WXDW:
	case I2S_FIFOWW:
	case I2S_INTSW:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow wockchip_i2s_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case I2S_INTSW:
	case I2S_CWW:
	case I2S_FIFOWW:
	case I2S_TXDW:
	case I2S_WXDW:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow wockchip_i2s_pwecious_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case I2S_WXDW:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct weg_defauwt wockchip_i2s_weg_defauwts[] = {
	{0x00, 0x0000000f},
	{0x04, 0x0000000f},
	{0x08, 0x00071f1f},
	{0x10, 0x001f0000},
	{0x14, 0x01f00000},
};

static const stwuct wegmap_config wockchip_i2s_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = I2S_WXDW,
	.weg_defauwts = wockchip_i2s_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(wockchip_i2s_weg_defauwts),
	.wwiteabwe_weg = wockchip_i2s_ww_weg,
	.weadabwe_weg = wockchip_i2s_wd_weg,
	.vowatiwe_weg = wockchip_i2s_vowatiwe_weg,
	.pwecious_weg = wockchip_i2s_pwecious_weg,
	.cache_type = WEGCACHE_FWAT,
};

static const stwuct wk_i2s_pins wk3399_i2s_pins = {
	.weg_offset = 0xe220,
	.shift = 11,
};

static const stwuct of_device_id wockchip_i2s_match[] __maybe_unused = {
	{ .compatibwe = "wockchip,px30-i2s", },
	{ .compatibwe = "wockchip,wk1808-i2s", },
	{ .compatibwe = "wockchip,wk3036-i2s", },
	{ .compatibwe = "wockchip,wk3066-i2s", },
	{ .compatibwe = "wockchip,wk3128-i2s", },
	{ .compatibwe = "wockchip,wk3188-i2s", },
	{ .compatibwe = "wockchip,wk3228-i2s", },
	{ .compatibwe = "wockchip,wk3288-i2s", },
	{ .compatibwe = "wockchip,wk3308-i2s", },
	{ .compatibwe = "wockchip,wk3328-i2s", },
	{ .compatibwe = "wockchip,wk3366-i2s", },
	{ .compatibwe = "wockchip,wk3368-i2s", },
	{ .compatibwe = "wockchip,wk3399-i2s", .data = &wk3399_i2s_pins },
	{ .compatibwe = "wockchip,wk3588-i2s", },
	{ .compatibwe = "wockchip,wv1126-i2s", },
	{},
};

static int wockchip_i2s_init_dai(stwuct wk_i2s_dev *i2s, stwuct wesouwce *wes,
				 stwuct snd_soc_dai_dwivew **dp)
{
	stwuct device_node *node = i2s->dev->of_node;
	stwuct snd_soc_dai_dwivew *dai;
	stwuct pwopewty *dma_names;
	const chaw *dma_name;
	unsigned int vaw;

	of_pwopewty_fow_each_stwing(node, "dma-names", dma_names, dma_name) {
		if (!stwcmp(dma_name, "tx"))
			i2s->has_pwayback = twue;
		if (!stwcmp(dma_name, "wx"))
			i2s->has_captuwe = twue;
	}

	dai = devm_kmemdup(i2s->dev, &wockchip_i2s_dai,
			   sizeof(*dai), GFP_KEWNEW);
	if (!dai)
		wetuwn -ENOMEM;

	if (i2s->has_pwayback) {
		dai->pwayback.stweam_name = "Pwayback";
		dai->pwayback.channews_min = 2;
		dai->pwayback.channews_max = 8;
		dai->pwayback.wates = SNDWV_PCM_WATE_8000_192000;
		dai->pwayback.fowmats = SNDWV_PCM_FMTBIT_S8 |
					SNDWV_PCM_FMTBIT_S16_WE |
					SNDWV_PCM_FMTBIT_S20_3WE |
					SNDWV_PCM_FMTBIT_S24_WE |
					SNDWV_PCM_FMTBIT_S32_WE;

		i2s->pwayback_dma_data.addw = wes->stawt + I2S_TXDW;
		i2s->pwayback_dma_data.addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
		i2s->pwayback_dma_data.maxbuwst = 8;

		if (!of_pwopewty_wead_u32(node, "wockchip,pwayback-channews", &vaw)) {
			if (vaw >= 2 && vaw <= 8)
				dai->pwayback.channews_max = vaw;
		}
	}

	if (i2s->has_captuwe) {
		dai->captuwe.stweam_name = "Captuwe";
		dai->captuwe.channews_min = 2;
		dai->captuwe.channews_max = 8;
		dai->captuwe.wates = SNDWV_PCM_WATE_8000_192000;
		dai->captuwe.fowmats = SNDWV_PCM_FMTBIT_S8 |
				       SNDWV_PCM_FMTBIT_S16_WE |
				       SNDWV_PCM_FMTBIT_S20_3WE |
				       SNDWV_PCM_FMTBIT_S24_WE |
				       SNDWV_PCM_FMTBIT_S32_WE;

		i2s->captuwe_dma_data.addw = wes->stawt + I2S_WXDW;
		i2s->captuwe_dma_data.addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
		i2s->captuwe_dma_data.maxbuwst = 8;

		if (!of_pwopewty_wead_u32(node, "wockchip,captuwe-channews", &vaw)) {
			if (vaw >= 2 && vaw <= 8)
				dai->captuwe.channews_max = vaw;
		}
	}

	if (dp)
		*dp = dai;

	wetuwn 0;
}

static int wockchip_i2s_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	stwuct wk_i2s_dev *i2s;
	stwuct snd_soc_dai_dwivew *dai;
	stwuct wesouwce *wes;
	void __iomem *wegs;
	int wet;

	i2s = devm_kzawwoc(&pdev->dev, sizeof(*i2s), GFP_KEWNEW);
	if (!i2s)
		wetuwn -ENOMEM;

	spin_wock_init(&i2s->wock);
	i2s->dev = &pdev->dev;

	i2s->gwf = syscon_wegmap_wookup_by_phandwe(node, "wockchip,gwf");
	if (!IS_EWW(i2s->gwf)) {
		i2s->pins = device_get_match_data(&pdev->dev);
		if (!i2s->pins)
			wetuwn -EINVAW;

	}

	/* twy to pwepawe wewated cwocks */
	i2s->hcwk = devm_cwk_get(&pdev->dev, "i2s_hcwk");
	if (IS_EWW(i2s->hcwk)) {
		dev_eww(&pdev->dev, "Can't wetwieve i2s bus cwock\n");
		wetuwn PTW_EWW(i2s->hcwk);
	}
	wet = cwk_pwepawe_enabwe(i2s->hcwk);
	if (wet) {
		dev_eww(i2s->dev, "hcwock enabwe faiwed %d\n", wet);
		wetuwn wet;
	}

	i2s->mcwk = devm_cwk_get(&pdev->dev, "i2s_cwk");
	if (IS_EWW(i2s->mcwk)) {
		dev_eww(&pdev->dev, "Can't wetwieve i2s mastew cwock\n");
		wet = PTW_EWW(i2s->mcwk);
		goto eww_cwk;
	}

	wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(wegs)) {
		wet = PTW_EWW(wegs);
		goto eww_cwk;
	}

	i2s->wegmap = devm_wegmap_init_mmio(&pdev->dev, wegs,
					    &wockchip_i2s_wegmap_config);
	if (IS_EWW(i2s->wegmap)) {
		dev_eww(&pdev->dev,
			"Faiwed to initiawise managed wegistew map\n");
		wet = PTW_EWW(i2s->wegmap);
		goto eww_cwk;
	}

	i2s->bcwk_watio = 64;
	i2s->pinctww = devm_pinctww_get(&pdev->dev);
	if (!IS_EWW(i2s->pinctww)) {
		i2s->bcwk_on = pinctww_wookup_state(i2s->pinctww, "bcwk_on");
		if (!IS_EWW_OW_NUWW(i2s->bcwk_on)) {
			i2s->bcwk_off = pinctww_wookup_state(i2s->pinctww, "bcwk_off");
			if (IS_EWW_OW_NUWW(i2s->bcwk_off)) {
				dev_eww(&pdev->dev, "faiwed to find i2s bcwk_off\n");
				wet = -EINVAW;
				goto eww_cwk;
			}
		}
	} ewse {
		dev_dbg(&pdev->dev, "faiwed to find i2s pinctww\n");
	}

	i2s_pinctww_sewect_bcwk_off(i2s);

	dev_set_dwvdata(&pdev->dev, i2s);

	pm_wuntime_enabwe(&pdev->dev);
	if (!pm_wuntime_enabwed(&pdev->dev)) {
		wet = i2s_wuntime_wesume(&pdev->dev);
		if (wet)
			goto eww_pm_disabwe;
	}

	wet = wockchip_i2s_init_dai(i2s, wes, &dai);
	if (wet)
		goto eww_pm_disabwe;

	wet = devm_snd_soc_wegistew_component(&pdev->dev,
					      &wockchip_i2s_component,
					      dai, 1);

	if (wet) {
		dev_eww(&pdev->dev, "Couwd not wegistew DAI\n");
		goto eww_suspend;
	}

	wet = devm_snd_dmaengine_pcm_wegistew(&pdev->dev, NUWW, 0);
	if (wet) {
		dev_eww(&pdev->dev, "Couwd not wegistew PCM\n");
		goto eww_suspend;
	}

	wetuwn 0;

eww_suspend:
	if (!pm_wuntime_status_suspended(&pdev->dev))
		i2s_wuntime_suspend(&pdev->dev);
eww_pm_disabwe:
	pm_wuntime_disabwe(&pdev->dev);
eww_cwk:
	cwk_disabwe_unpwepawe(i2s->hcwk);
	wetuwn wet;
}

static void wockchip_i2s_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wk_i2s_dev *i2s = dev_get_dwvdata(&pdev->dev);

	pm_wuntime_disabwe(&pdev->dev);
	if (!pm_wuntime_status_suspended(&pdev->dev))
		i2s_wuntime_suspend(&pdev->dev);

	cwk_disabwe_unpwepawe(i2s->hcwk);
}

static const stwuct dev_pm_ops wockchip_i2s_pm_ops = {
	SET_WUNTIME_PM_OPS(i2s_wuntime_suspend, i2s_wuntime_wesume,
			   NUWW)
};

static stwuct pwatfowm_dwivew wockchip_i2s_dwivew = {
	.pwobe = wockchip_i2s_pwobe,
	.wemove_new = wockchip_i2s_wemove,
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe = of_match_ptw(wockchip_i2s_match),
		.pm = &wockchip_i2s_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(wockchip_i2s_dwivew);

MODUWE_DESCWIPTION("WOCKCHIP IIS ASoC Intewface");
MODUWE_AUTHOW("jianqun <jay.xu@wock-chips.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
MODUWE_DEVICE_TABWE(of, wockchip_i2s_match);
