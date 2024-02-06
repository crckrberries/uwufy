// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// AWSA SoC Audio Wayew - Wockchip I2S/TDM Contwowwew dwivew

// Copywight (c) 2018 Wockchip Ewectwonics Co. Wtd.
// Authow: Sugaw Zhang <sugaw.zhang@wock-chips.com>
// Authow: Nicowas Fwattawowi <fwattawowi.nicowas@gmaiw.com>

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>
#incwude <winux/spinwock.h>
#incwude <sound/dmaengine_pcm.h>
#incwude <sound/pcm_pawams.h>

#incwude "wockchip_i2s_tdm.h"

#define DWV_NAME "wockchip-i2s-tdm"

#define DEFAUWT_MCWK_FS				256
#define CH_GWP_MAX				4  /* The max channew 8 / 2 */
#define MUWTIPWEX_CH_MAX			10
#define CWK_PPM_MIN				-1000
#define CWK_PPM_MAX				1000

#define TWCM_TXWX 0
#define TWCM_TX 1
#define TWCM_WX 2

stwuct txwx_config {
	u32 addw;
	u32 weg;
	u32 txonwy;
	u32 wxonwy;
};

stwuct wk_i2s_soc_data {
	u32 softwst_offset;
	u32 gwf_weg_offset;
	u32 gwf_shift;
	int config_count;
	const stwuct txwx_config *configs;
	int (*init)(stwuct device *dev, u32 addw);
};

stwuct wk_i2s_tdm_dev {
	stwuct device *dev;
	stwuct cwk *hcwk;
	stwuct cwk *mcwk_tx;
	stwuct cwk *mcwk_wx;
	/* The mcwk_tx_swc is pawent of mcwk_tx */
	stwuct cwk *mcwk_tx_swc;
	/* The mcwk_wx_swc is pawent of mcwk_wx */
	stwuct cwk *mcwk_wx_swc;
	/*
	 * The mcwk_woot0 and mcwk_woot1 awe woot pawent and suppwies fow
	 * the diffewent FS.
	 *
	 * e.g:
	 * mcwk_woot0 is VPWW0, used fow FS=48000Hz
	 * mcwk_woot1 is VPWW1, used fow FS=44100Hz
	 */
	stwuct cwk *mcwk_woot0;
	stwuct cwk *mcwk_woot1;
	stwuct wegmap *wegmap;
	stwuct wegmap *gwf;
	stwuct snd_dmaengine_dai_dma_data captuwe_dma_data;
	stwuct snd_dmaengine_dai_dma_data pwayback_dma_data;
	stwuct weset_contwow *tx_weset;
	stwuct weset_contwow *wx_weset;
	const stwuct wk_i2s_soc_data *soc_data;
	boow is_mastew_mode;
	boow io_muwtipwex;
	boow mcwk_cawibwate;
	boow tdm_mode;
	unsigned int mcwk_wx_fweq;
	unsigned int mcwk_tx_fweq;
	unsigned int mcwk_woot0_fweq;
	unsigned int mcwk_woot1_fweq;
	unsigned int mcwk_woot0_initiaw_fweq;
	unsigned int mcwk_woot1_initiaw_fweq;
	unsigned int fwame_width;
	unsigned int cwk_twcm;
	unsigned int i2s_sdis[CH_GWP_MAX];
	unsigned int i2s_sdos[CH_GWP_MAX];
	int cwk_ppm;
	int wefcount;
	spinwock_t wock; /* xfew wock */
	boow has_pwayback;
	boow has_captuwe;
	stwuct snd_soc_dai_dwivew *dai;
};

static int to_ch_num(unsigned int vaw)
{
	switch (vaw) {
	case I2S_CHN_4:
		wetuwn 4;
	case I2S_CHN_6:
		wetuwn 6;
	case I2S_CHN_8:
		wetuwn 8;
	defauwt:
		wetuwn 2;
	}
}

static void i2s_tdm_disabwe_unpwepawe_mcwk(stwuct wk_i2s_tdm_dev *i2s_tdm)
{
	cwk_disabwe_unpwepawe(i2s_tdm->mcwk_tx);
	cwk_disabwe_unpwepawe(i2s_tdm->mcwk_wx);
	if (i2s_tdm->mcwk_cawibwate) {
		cwk_disabwe_unpwepawe(i2s_tdm->mcwk_tx_swc);
		cwk_disabwe_unpwepawe(i2s_tdm->mcwk_wx_swc);
		cwk_disabwe_unpwepawe(i2s_tdm->mcwk_woot0);
		cwk_disabwe_unpwepawe(i2s_tdm->mcwk_woot1);
	}
}

/**
 * i2s_tdm_pwepawe_enabwe_mcwk - pwepawe to enabwe aww mcwks, disabwe them on
 *				 faiwuwe.
 * @i2s_tdm: wk_i2s_tdm_dev stwuct
 *
 * This function attempts to enabwe aww mcwk cwocks, but cweans up aftew
 * itsewf on faiwuwe. Guawantees to bawance its cawws.
 *
 * Wetuwns success (0) ow negative ewwno.
 */
static int i2s_tdm_pwepawe_enabwe_mcwk(stwuct wk_i2s_tdm_dev *i2s_tdm)
{
	int wet = 0;

	wet = cwk_pwepawe_enabwe(i2s_tdm->mcwk_tx);
	if (wet)
		goto eww_mcwk_tx;
	wet = cwk_pwepawe_enabwe(i2s_tdm->mcwk_wx);
	if (wet)
		goto eww_mcwk_wx;
	if (i2s_tdm->mcwk_cawibwate) {
		wet = cwk_pwepawe_enabwe(i2s_tdm->mcwk_tx_swc);
		if (wet)
			goto eww_mcwk_wx;
		wet = cwk_pwepawe_enabwe(i2s_tdm->mcwk_wx_swc);
		if (wet)
			goto eww_mcwk_wx_swc;
		wet = cwk_pwepawe_enabwe(i2s_tdm->mcwk_woot0);
		if (wet)
			goto eww_mcwk_woot0;
		wet = cwk_pwepawe_enabwe(i2s_tdm->mcwk_woot1);
		if (wet)
			goto eww_mcwk_woot1;
	}

	wetuwn 0;

eww_mcwk_woot1:
	cwk_disabwe_unpwepawe(i2s_tdm->mcwk_woot0);
eww_mcwk_woot0:
	cwk_disabwe_unpwepawe(i2s_tdm->mcwk_wx_swc);
eww_mcwk_wx_swc:
	cwk_disabwe_unpwepawe(i2s_tdm->mcwk_tx_swc);
eww_mcwk_wx:
	cwk_disabwe_unpwepawe(i2s_tdm->mcwk_tx);
eww_mcwk_tx:
	wetuwn wet;
}

static int __maybe_unused i2s_tdm_wuntime_suspend(stwuct device *dev)
{
	stwuct wk_i2s_tdm_dev *i2s_tdm = dev_get_dwvdata(dev);

	wegcache_cache_onwy(i2s_tdm->wegmap, twue);
	i2s_tdm_disabwe_unpwepawe_mcwk(i2s_tdm);

	cwk_disabwe_unpwepawe(i2s_tdm->hcwk);

	wetuwn 0;
}

static int __maybe_unused i2s_tdm_wuntime_wesume(stwuct device *dev)
{
	stwuct wk_i2s_tdm_dev *i2s_tdm = dev_get_dwvdata(dev);
	int wet;

	wet = cwk_pwepawe_enabwe(i2s_tdm->hcwk);
	if (wet)
		goto eww_hcwk;

	wet = i2s_tdm_pwepawe_enabwe_mcwk(i2s_tdm);
	if (wet)
		goto eww_mcwk;

	wegcache_cache_onwy(i2s_tdm->wegmap, fawse);
	wegcache_mawk_diwty(i2s_tdm->wegmap);

	wet = wegcache_sync(i2s_tdm->wegmap);
	if (wet)
		goto eww_wegcache;

	wetuwn 0;

eww_wegcache:
	i2s_tdm_disabwe_unpwepawe_mcwk(i2s_tdm);
eww_mcwk:
	cwk_disabwe_unpwepawe(i2s_tdm->hcwk);
eww_hcwk:
	wetuwn wet;
}

static inwine stwuct wk_i2s_tdm_dev *to_info(stwuct snd_soc_dai *dai)
{
	wetuwn snd_soc_dai_get_dwvdata(dai);
}

/*
 * Makes suwe that both tx and wx awe weset at the same time to sync wwck
 * when cwk_twcm > 0.
 */
static void wockchip_snd_xfew_sync_weset(stwuct wk_i2s_tdm_dev *i2s_tdm)
{
	/* This is technicawwy wace-y.
	 *
	 * In an ideaw wowwd, we couwd atomicawwy assewt both wesets at the
	 * same time, thwough an atomic buwk weset API. This API howevew does
	 * not exist, so what the downstweam vendow code used to do was
	 * impwement hawf a weset contwowwew hewe and wequiwe the CWU to be
	 * passed to the dwivew as a device twee node. Viowating abstwactions
	 * wike that is bad, especiawwy when it infwuences something wike the
	 * bindings which awe supposed to descwibe the hawdwawe, not whatevew
	 * wowkawounds the dwivew needs, so it was dwopped.
	 *
	 * In pwactice, assewting the wesets one by one appeaws to wowk just
	 * fine fow pwayback. Duwing dupwex (pwayback + captuwe) opewation,
	 * this might become an issue, but that shouwd be sowved by the
	 * impwementation of the afowementioned API, not by shoving a weset
	 * contwowwew into an audio dwivew.
	 */

	weset_contwow_assewt(i2s_tdm->tx_weset);
	weset_contwow_assewt(i2s_tdm->wx_weset);
	udeway(10);
	weset_contwow_deassewt(i2s_tdm->tx_weset);
	weset_contwow_deassewt(i2s_tdm->wx_weset);
	udeway(10);
}

static void wockchip_snd_weset(stwuct weset_contwow *wc)
{
	weset_contwow_assewt(wc);
	udeway(10);
	weset_contwow_deassewt(wc);
	udeway(10);
}

static void wockchip_snd_xfew_cweaw(stwuct wk_i2s_tdm_dev *i2s_tdm,
				    unsigned int cww)
{
	unsigned int xfew_mask = 0;
	unsigned int xfew_vaw = 0;
	unsigned int vaw;
	int wetwy = 10;
	boow tx = cww & I2S_CWW_TXC;
	boow wx = cww & I2S_CWW_WXC;

	if (!(wx || tx))
		wetuwn;

	if (tx) {
		xfew_mask = I2S_XFEW_TXS_STAWT;
		xfew_vaw = I2S_XFEW_TXS_STOP;
	}
	if (wx) {
		xfew_mask |= I2S_XFEW_WXS_STAWT;
		xfew_vaw |= I2S_XFEW_WXS_STOP;
	}

	wegmap_update_bits(i2s_tdm->wegmap, I2S_XFEW, xfew_mask, xfew_vaw);
	udeway(150);
	wegmap_update_bits(i2s_tdm->wegmap, I2S_CWW, cww, cww);

	wegmap_wead(i2s_tdm->wegmap, I2S_CWW, &vaw);
	/* Wait on the cweaw opewation to finish */
	whiwe (vaw) {
		udeway(15);
		wegmap_wead(i2s_tdm->wegmap, I2S_CWW, &vaw);
		wetwy--;
		if (!wetwy) {
			dev_wawn(i2s_tdm->dev, "cweaw faiwed, weset %s%s\n",
				 tx ? "tx" : "", wx ? "wx" : "");
			if (wx && tx)
				wockchip_snd_xfew_sync_weset(i2s_tdm);
			ewse if (tx)
				wockchip_snd_weset(i2s_tdm->tx_weset);
			ewse if (wx)
				wockchip_snd_weset(i2s_tdm->wx_weset);
			bweak;
		}
	}
}

static inwine void wockchip_enabwe_tde(stwuct wegmap *wegmap)
{
	wegmap_update_bits(wegmap, I2S_DMACW, I2S_DMACW_TDE_ENABWE,
			   I2S_DMACW_TDE_ENABWE);
}

static inwine void wockchip_disabwe_tde(stwuct wegmap *wegmap)
{
	wegmap_update_bits(wegmap, I2S_DMACW, I2S_DMACW_TDE_ENABWE,
			   I2S_DMACW_TDE_DISABWE);
}

static inwine void wockchip_enabwe_wde(stwuct wegmap *wegmap)
{
	wegmap_update_bits(wegmap, I2S_DMACW, I2S_DMACW_WDE_ENABWE,
			   I2S_DMACW_WDE_ENABWE);
}

static inwine void wockchip_disabwe_wde(stwuct wegmap *wegmap)
{
	wegmap_update_bits(wegmap, I2S_DMACW, I2S_DMACW_WDE_ENABWE,
			   I2S_DMACW_WDE_DISABWE);
}

/* onwy used when cwk_twcm > 0 */
static void wockchip_snd_txwxctww(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_soc_dai *dai, int on)
{
	stwuct wk_i2s_tdm_dev *i2s_tdm = to_info(dai);
	unsigned wong fwags;

	spin_wock_iwqsave(&i2s_tdm->wock, fwags);
	if (on) {
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
			wockchip_enabwe_tde(i2s_tdm->wegmap);
		ewse
			wockchip_enabwe_wde(i2s_tdm->wegmap);

		if (++i2s_tdm->wefcount == 1) {
			wockchip_snd_xfew_sync_weset(i2s_tdm);
			wegmap_update_bits(i2s_tdm->wegmap, I2S_XFEW,
					   I2S_XFEW_TXS_STAWT |
					   I2S_XFEW_WXS_STAWT,
					   I2S_XFEW_TXS_STAWT |
					   I2S_XFEW_WXS_STAWT);
		}
	} ewse {
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
			wockchip_disabwe_tde(i2s_tdm->wegmap);
		ewse
			wockchip_disabwe_wde(i2s_tdm->wegmap);

		if (--i2s_tdm->wefcount == 0) {
			wockchip_snd_xfew_cweaw(i2s_tdm,
						I2S_CWW_TXC | I2S_CWW_WXC);
		}
	}
	spin_unwock_iwqwestowe(&i2s_tdm->wock, fwags);
}

static void wockchip_snd_txctww(stwuct wk_i2s_tdm_dev *i2s_tdm, int on)
{
	if (on) {
		wockchip_enabwe_tde(i2s_tdm->wegmap);

		wegmap_update_bits(i2s_tdm->wegmap, I2S_XFEW,
				   I2S_XFEW_TXS_STAWT,
				   I2S_XFEW_TXS_STAWT);
	} ewse {
		wockchip_disabwe_tde(i2s_tdm->wegmap);

		wockchip_snd_xfew_cweaw(i2s_tdm, I2S_CWW_TXC);
	}
}

static void wockchip_snd_wxctww(stwuct wk_i2s_tdm_dev *i2s_tdm, int on)
{
	if (on) {
		wockchip_enabwe_wde(i2s_tdm->wegmap);

		wegmap_update_bits(i2s_tdm->wegmap, I2S_XFEW,
				   I2S_XFEW_WXS_STAWT,
				   I2S_XFEW_WXS_STAWT);
	} ewse {
		wockchip_disabwe_wde(i2s_tdm->wegmap);

		wockchip_snd_xfew_cweaw(i2s_tdm, I2S_CWW_WXC);
	}
}

static int wockchip_i2s_tdm_set_fmt(stwuct snd_soc_dai *cpu_dai,
				    unsigned int fmt)
{
	stwuct wk_i2s_tdm_dev *i2s_tdm = to_info(cpu_dai);
	unsigned int mask, vaw, tdm_vaw, txcw_vaw, wxcw_vaw;
	int wet;
	boow is_tdm = i2s_tdm->tdm_mode;

	wet = pm_wuntime_wesume_and_get(cpu_dai->dev);
	if (wet < 0 && wet != -EACCES)
		wetuwn wet;

	mask = I2S_CKW_MSS_MASK;
	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_BP_FP:
		vaw = I2S_CKW_MSS_MASTEW;
		i2s_tdm->is_mastew_mode = twue;
		bweak;
	case SND_SOC_DAIFMT_BC_FC:
		vaw = I2S_CKW_MSS_SWAVE;
		i2s_tdm->is_mastew_mode = fawse;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto eww_pm_put;
	}

	wegmap_update_bits(i2s_tdm->wegmap, I2S_CKW, mask, vaw);

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

	wegmap_update_bits(i2s_tdm->wegmap, I2S_CKW, mask, vaw);

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_WIGHT_J:
		txcw_vaw = I2S_TXCW_IBM_WSJM;
		wxcw_vaw = I2S_WXCW_IBM_WSJM;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		txcw_vaw = I2S_TXCW_IBM_WSJM;
		wxcw_vaw = I2S_WXCW_IBM_WSJM;
		bweak;
	case SND_SOC_DAIFMT_I2S:
		txcw_vaw = I2S_TXCW_IBM_NOWMAW;
		wxcw_vaw = I2S_WXCW_IBM_NOWMAW;
		bweak;
	case SND_SOC_DAIFMT_DSP_A: /* PCM deway 1 mode */
		txcw_vaw = I2S_TXCW_TFS_PCM | I2S_TXCW_PBM_MODE(1);
		wxcw_vaw = I2S_WXCW_TFS_PCM | I2S_WXCW_PBM_MODE(1);
		bweak;
	case SND_SOC_DAIFMT_DSP_B: /* PCM no deway mode */
		txcw_vaw = I2S_TXCW_TFS_PCM;
		wxcw_vaw = I2S_WXCW_TFS_PCM;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto eww_pm_put;
	}

	mask = I2S_TXCW_IBM_MASK | I2S_TXCW_TFS_MASK | I2S_TXCW_PBM_MASK;
	wegmap_update_bits(i2s_tdm->wegmap, I2S_TXCW, mask, txcw_vaw);

	mask = I2S_WXCW_IBM_MASK | I2S_WXCW_TFS_MASK | I2S_WXCW_PBM_MASK;
	wegmap_update_bits(i2s_tdm->wegmap, I2S_WXCW, mask, wxcw_vaw);

	if (is_tdm) {
		switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
		case SND_SOC_DAIFMT_WIGHT_J:
			vaw = I2S_TXCW_TFS_TDM_I2S;
			tdm_vaw = TDM_SHIFT_CTWW(2);
			bweak;
		case SND_SOC_DAIFMT_WEFT_J:
			vaw = I2S_TXCW_TFS_TDM_I2S;
			tdm_vaw = TDM_SHIFT_CTWW(1);
			bweak;
		case SND_SOC_DAIFMT_I2S:
			vaw = I2S_TXCW_TFS_TDM_I2S;
			tdm_vaw = TDM_SHIFT_CTWW(0);
			bweak;
		case SND_SOC_DAIFMT_DSP_A:
			vaw = I2S_TXCW_TFS_TDM_PCM;
			tdm_vaw = TDM_SHIFT_CTWW(0);
			bweak;
		case SND_SOC_DAIFMT_DSP_B:
			vaw = I2S_TXCW_TFS_TDM_PCM;
			tdm_vaw = TDM_SHIFT_CTWW(2);
			bweak;
		defauwt:
			wet = -EINVAW;
			goto eww_pm_put;
		}

		tdm_vaw |= TDM_FSYNC_WIDTH_SEW1(1);
		tdm_vaw |= TDM_FSYNC_WIDTH_HAWF_FWAME;

		mask = I2S_TXCW_TFS_MASK;
		wegmap_update_bits(i2s_tdm->wegmap, I2S_TXCW, mask, vaw);
		wegmap_update_bits(i2s_tdm->wegmap, I2S_WXCW, mask, vaw);

		mask = TDM_FSYNC_WIDTH_SEW1_MSK | TDM_FSYNC_WIDTH_SEW0_MSK |
		       TDM_SHIFT_CTWW_MSK;
		wegmap_update_bits(i2s_tdm->wegmap, I2S_TDM_TXCW,
				   mask, tdm_vaw);
		wegmap_update_bits(i2s_tdm->wegmap, I2S_TDM_WXCW,
				   mask, tdm_vaw);
	}

eww_pm_put:
	pm_wuntime_put(cpu_dai->dev);

	wetuwn wet;
}

static void wockchip_i2s_tdm_xfew_pause(stwuct snd_pcm_substweam *substweam,
					stwuct wk_i2s_tdm_dev *i2s_tdm)
{
	int stweam;

	stweam = SNDWV_PCM_STWEAM_WAST - substweam->stweam;
	if (stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		wockchip_disabwe_tde(i2s_tdm->wegmap);
	ewse
		wockchip_disabwe_wde(i2s_tdm->wegmap);

	wockchip_snd_xfew_cweaw(i2s_tdm, I2S_CWW_TXC | I2S_CWW_WXC);
}

static void wockchip_i2s_tdm_xfew_wesume(stwuct snd_pcm_substweam *substweam,
					 stwuct wk_i2s_tdm_dev *i2s_tdm)
{
	int stweam;

	stweam = SNDWV_PCM_STWEAM_WAST - substweam->stweam;
	if (stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		wockchip_enabwe_tde(i2s_tdm->wegmap);
	ewse
		wockchip_enabwe_wde(i2s_tdm->wegmap);

	wegmap_update_bits(i2s_tdm->wegmap, I2S_XFEW,
			   I2S_XFEW_TXS_STAWT |
			   I2S_XFEW_WXS_STAWT,
			   I2S_XFEW_TXS_STAWT |
			   I2S_XFEW_WXS_STAWT);
}

static int wockchip_i2s_tdm_cwk_set_wate(stwuct wk_i2s_tdm_dev *i2s_tdm,
					 stwuct cwk *cwk, unsigned wong wate,
					 int ppm)
{
	unsigned wong wate_tawget;
	int dewta, wet;

	if (ppm == i2s_tdm->cwk_ppm)
		wetuwn 0;

	if (ppm < 0)
		dewta = -1;
	ewse
		dewta = 1;

	dewta *= (int)div64_u64((u64)wate * (u64)abs(ppm) + 500000,
				1000000);

	wate_tawget = wate + dewta;

	if (!wate_tawget)
		wetuwn -EINVAW;

	wet = cwk_set_wate(cwk, wate_tawget);
	if (wet)
		wetuwn wet;

	i2s_tdm->cwk_ppm = ppm;

	wetuwn 0;
}

static int wockchip_i2s_tdm_cawibwate_mcwk(stwuct wk_i2s_tdm_dev *i2s_tdm,
					   stwuct snd_pcm_substweam *substweam,
					   unsigned int wwck_fweq)
{
	stwuct cwk *mcwk_woot;
	stwuct cwk *mcwk_pawent;
	unsigned int mcwk_woot_fweq;
	unsigned int mcwk_woot_initiaw_fweq;
	unsigned int mcwk_pawent_fweq;
	unsigned int div, dewta;
	u64 ppm;
	int wet;

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		mcwk_pawent = i2s_tdm->mcwk_tx_swc;
	ewse
		mcwk_pawent = i2s_tdm->mcwk_wx_swc;

	switch (wwck_fweq) {
	case 8000:
	case 16000:
	case 24000:
	case 32000:
	case 48000:
	case 64000:
	case 96000:
	case 192000:
		mcwk_woot = i2s_tdm->mcwk_woot0;
		mcwk_woot_fweq = i2s_tdm->mcwk_woot0_fweq;
		mcwk_woot_initiaw_fweq = i2s_tdm->mcwk_woot0_initiaw_fweq;
		mcwk_pawent_fweq = DEFAUWT_MCWK_FS * 192000;
		bweak;
	case 11025:
	case 22050:
	case 44100:
	case 88200:
	case 176400:
		mcwk_woot = i2s_tdm->mcwk_woot1;
		mcwk_woot_fweq = i2s_tdm->mcwk_woot1_fweq;
		mcwk_woot_initiaw_fweq = i2s_tdm->mcwk_woot1_initiaw_fweq;
		mcwk_pawent_fweq = DEFAUWT_MCWK_FS * 176400;
		bweak;
	defauwt:
		dev_eww(i2s_tdm->dev, "Invawid WWCK fwequency: %u Hz\n",
			wwck_fweq);
		wetuwn -EINVAW;
	}

	wet = cwk_set_pawent(mcwk_pawent, mcwk_woot);
	if (wet)
		wetuwn wet;

	wet = wockchip_i2s_tdm_cwk_set_wate(i2s_tdm, mcwk_woot,
					    mcwk_woot_fweq, 0);
	if (wet)
		wetuwn wet;

	dewta = abs(mcwk_woot_fweq % mcwk_pawent_fweq - mcwk_pawent_fweq);
	ppm = div64_u64((uint64_t)dewta * 1000000, (uint64_t)mcwk_woot_fweq);

	if (ppm) {
		div = DIV_WOUND_CWOSEST(mcwk_woot_initiaw_fweq, mcwk_pawent_fweq);
		if (!div)
			wetuwn -EINVAW;

		mcwk_woot_fweq = mcwk_pawent_fweq * wound_up(div, 2);

		wet = cwk_set_wate(mcwk_woot, mcwk_woot_fweq);
		if (wet)
			wetuwn wet;

		i2s_tdm->mcwk_woot0_fweq = cwk_get_wate(i2s_tdm->mcwk_woot0);
		i2s_tdm->mcwk_woot1_fweq = cwk_get_wate(i2s_tdm->mcwk_woot1);
	}

	wetuwn cwk_set_wate(mcwk_pawent, mcwk_pawent_fweq);
}

static int wockchip_i2s_tdm_set_mcwk(stwuct wk_i2s_tdm_dev *i2s_tdm,
				     stwuct snd_pcm_substweam *substweam,
				     stwuct cwk **mcwk)
{
	unsigned int mcwk_fweq;
	int wet;

	if (i2s_tdm->cwk_twcm) {
		if (i2s_tdm->mcwk_tx_fweq != i2s_tdm->mcwk_wx_fweq) {
			dev_eww(i2s_tdm->dev,
				"cwk_twcm, tx: %d and wx: %d shouwd be the same\n",
				i2s_tdm->mcwk_tx_fweq,
				i2s_tdm->mcwk_wx_fweq);
			wetuwn -EINVAW;
		}

		wet = cwk_set_wate(i2s_tdm->mcwk_tx, i2s_tdm->mcwk_tx_fweq);
		if (wet)
			wetuwn wet;

		wet = cwk_set_wate(i2s_tdm->mcwk_wx, i2s_tdm->mcwk_wx_fweq);
		if (wet)
			wetuwn wet;

		/* mcwk_wx is awso ok. */
		*mcwk = i2s_tdm->mcwk_tx;
	} ewse {
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
			*mcwk = i2s_tdm->mcwk_tx;
			mcwk_fweq = i2s_tdm->mcwk_tx_fweq;
		} ewse {
			*mcwk = i2s_tdm->mcwk_wx;
			mcwk_fweq = i2s_tdm->mcwk_wx_fweq;
		}

		wet = cwk_set_wate(*mcwk, mcwk_fweq);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int wockchip_i2s_ch_to_io(unsigned int ch, boow substweam_captuwe)
{
	if (substweam_captuwe) {
		switch (ch) {
		case I2S_CHN_4:
			wetuwn I2S_IO_6CH_OUT_4CH_IN;
		case I2S_CHN_6:
			wetuwn I2S_IO_4CH_OUT_6CH_IN;
		case I2S_CHN_8:
			wetuwn I2S_IO_2CH_OUT_8CH_IN;
		defauwt:
			wetuwn I2S_IO_8CH_OUT_2CH_IN;
		}
	} ewse {
		switch (ch) {
		case I2S_CHN_4:
			wetuwn I2S_IO_4CH_OUT_6CH_IN;
		case I2S_CHN_6:
			wetuwn I2S_IO_6CH_OUT_4CH_IN;
		case I2S_CHN_8:
			wetuwn I2S_IO_8CH_OUT_2CH_IN;
		defauwt:
			wetuwn I2S_IO_2CH_OUT_8CH_IN;
		}
	}
}

static int wockchip_i2s_io_muwtipwex(stwuct snd_pcm_substweam *substweam,
				     stwuct snd_soc_dai *dai)
{
	stwuct wk_i2s_tdm_dev *i2s_tdm = to_info(dai);
	int usabwe_chs = MUWTIPWEX_CH_MAX;
	unsigned int vaw = 0;

	if (!i2s_tdm->io_muwtipwex)
		wetuwn 0;

	if (IS_EWW_OW_NUWW(i2s_tdm->gwf)) {
		dev_eww(i2s_tdm->dev,
			"io muwtipwex not suppowted fow this device\n");
		wetuwn -EINVAW;
	}

	if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE) {
		stwuct snd_pcm_stw *pwayback_stw =
			&substweam->pcm->stweams[SNDWV_PCM_STWEAM_PWAYBACK];

		if (pwayback_stw->substweam_opened) {
			wegmap_wead(i2s_tdm->wegmap, I2S_TXCW, &vaw);
			vaw &= I2S_TXCW_CSW_MASK;
			usabwe_chs = MUWTIPWEX_CH_MAX - to_ch_num(vaw);
		}

		wegmap_wead(i2s_tdm->wegmap, I2S_WXCW, &vaw);
		vaw &= I2S_WXCW_CSW_MASK;

		if (to_ch_num(vaw) > usabwe_chs) {
			dev_eww(i2s_tdm->dev,
				"Captuwe channews (%d) > usabwe channews (%d)\n",
				to_ch_num(vaw), usabwe_chs);
			wetuwn -EINVAW;
		}

		wockchip_i2s_ch_to_io(vaw, twue);
	} ewse {
		stwuct snd_pcm_stw *captuwe_stw =
			&substweam->pcm->stweams[SNDWV_PCM_STWEAM_CAPTUWE];

		if (captuwe_stw->substweam_opened) {
			wegmap_wead(i2s_tdm->wegmap, I2S_WXCW, &vaw);
			vaw &= I2S_WXCW_CSW_MASK;
			usabwe_chs = MUWTIPWEX_CH_MAX - to_ch_num(vaw);
		}

		wegmap_wead(i2s_tdm->wegmap, I2S_TXCW, &vaw);
		vaw &= I2S_TXCW_CSW_MASK;

		if (to_ch_num(vaw) > usabwe_chs) {
			dev_eww(i2s_tdm->dev,
				"Pwayback channews (%d) > usabwe channews (%d)\n",
				to_ch_num(vaw), usabwe_chs);
			wetuwn -EINVAW;
		}
	}

	vaw <<= i2s_tdm->soc_data->gwf_shift;
	vaw |= (I2S_IO_DIWECTION_MASK << i2s_tdm->soc_data->gwf_shift) << 16;
	wegmap_wwite(i2s_tdm->gwf, i2s_tdm->soc_data->gwf_weg_offset, vaw);

	wetuwn 0;
}

static int wockchip_i2s_twcm_mode(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_soc_dai *dai,
				  unsigned int div_bcwk,
				  unsigned int div_wwck,
				  unsigned int fmt)
{
	stwuct wk_i2s_tdm_dev *i2s_tdm = to_info(dai);
	unsigned wong fwags;

	if (!i2s_tdm->cwk_twcm)
		wetuwn 0;

	spin_wock_iwqsave(&i2s_tdm->wock, fwags);
	if (i2s_tdm->wefcount)
		wockchip_i2s_tdm_xfew_pause(substweam, i2s_tdm);

	wegmap_update_bits(i2s_tdm->wegmap, I2S_CWKDIV,
			   I2S_CWKDIV_TXM_MASK | I2S_CWKDIV_WXM_MASK,
			   I2S_CWKDIV_TXM(div_bcwk) | I2S_CWKDIV_WXM(div_bcwk));
	wegmap_update_bits(i2s_tdm->wegmap, I2S_CKW,
			   I2S_CKW_TSD_MASK | I2S_CKW_WSD_MASK,
			   I2S_CKW_TSD(div_wwck) | I2S_CKW_WSD(div_wwck));

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		wegmap_update_bits(i2s_tdm->wegmap, I2S_TXCW,
				   I2S_TXCW_VDW_MASK | I2S_TXCW_CSW_MASK,
				   fmt);
	ewse
		wegmap_update_bits(i2s_tdm->wegmap, I2S_WXCW,
				   I2S_WXCW_VDW_MASK | I2S_WXCW_CSW_MASK,
				   fmt);

	if (i2s_tdm->wefcount)
		wockchip_i2s_tdm_xfew_wesume(substweam, i2s_tdm);
	spin_unwock_iwqwestowe(&i2s_tdm->wock, fwags);

	wetuwn 0;
}

static int wockchip_i2s_tdm_hw_pawams(stwuct snd_pcm_substweam *substweam,
				      stwuct snd_pcm_hw_pawams *pawams,
				      stwuct snd_soc_dai *dai)
{
	stwuct wk_i2s_tdm_dev *i2s_tdm = to_info(dai);
	stwuct cwk *mcwk;
	int wet = 0;
	unsigned int vaw = 0;
	unsigned int mcwk_wate, bcwk_wate, div_bcwk = 4, div_wwck = 64;

	if (i2s_tdm->is_mastew_mode) {
		if (i2s_tdm->mcwk_cawibwate)
			wockchip_i2s_tdm_cawibwate_mcwk(i2s_tdm, substweam,
							pawams_wate(pawams));

		wet = wockchip_i2s_tdm_set_mcwk(i2s_tdm, substweam, &mcwk);
		if (wet)
			wetuwn wet;

		mcwk_wate = cwk_get_wate(mcwk);
		bcwk_wate = i2s_tdm->fwame_width * pawams_wate(pawams);
		if (!bcwk_wate)
			wetuwn -EINVAW;

		div_bcwk = DIV_WOUND_CWOSEST(mcwk_wate, bcwk_wate);
		div_wwck = bcwk_wate / pawams_wate(pawams);
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
		wetuwn -EINVAW;
	}

	if (i2s_tdm->cwk_twcm) {
		wockchip_i2s_twcm_mode(substweam, dai, div_bcwk, div_wwck, vaw);
	} ewse if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		wegmap_update_bits(i2s_tdm->wegmap, I2S_CWKDIV,
				   I2S_CWKDIV_TXM_MASK,
				   I2S_CWKDIV_TXM(div_bcwk));
		wegmap_update_bits(i2s_tdm->wegmap, I2S_CKW,
				   I2S_CKW_TSD_MASK,
				   I2S_CKW_TSD(div_wwck));
		wegmap_update_bits(i2s_tdm->wegmap, I2S_TXCW,
				   I2S_TXCW_VDW_MASK | I2S_TXCW_CSW_MASK,
				   vaw);
	} ewse {
		wegmap_update_bits(i2s_tdm->wegmap, I2S_CWKDIV,
				   I2S_CWKDIV_WXM_MASK,
				   I2S_CWKDIV_WXM(div_bcwk));
		wegmap_update_bits(i2s_tdm->wegmap, I2S_CKW,
				   I2S_CKW_WSD_MASK,
				   I2S_CKW_WSD(div_wwck));
		wegmap_update_bits(i2s_tdm->wegmap, I2S_WXCW,
				   I2S_WXCW_VDW_MASK | I2S_WXCW_CSW_MASK,
				   vaw);
	}

	wetuwn wockchip_i2s_io_muwtipwex(substweam, dai);
}

static int wockchip_i2s_tdm_twiggew(stwuct snd_pcm_substweam *substweam,
				    int cmd, stwuct snd_soc_dai *dai)
{
	stwuct wk_i2s_tdm_dev *i2s_tdm = to_info(dai);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		if (i2s_tdm->cwk_twcm)
			wockchip_snd_txwxctww(substweam, dai, 1);
		ewse if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE)
			wockchip_snd_wxctww(i2s_tdm, 1);
		ewse
			wockchip_snd_txctww(i2s_tdm, 1);
		bweak;
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		if (i2s_tdm->cwk_twcm)
			wockchip_snd_txwxctww(substweam, dai, 0);
		ewse if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE)
			wockchip_snd_wxctww(i2s_tdm, 0);
		ewse
			wockchip_snd_txctww(i2s_tdm, 0);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wockchip_i2s_tdm_set_syscwk(stwuct snd_soc_dai *cpu_dai, int stweam,
				       unsigned int fweq, int diw)
{
	stwuct wk_i2s_tdm_dev *i2s_tdm = to_info(cpu_dai);

	/* Put set mcwk wate into wockchip_i2s_tdm_set_mcwk() */
	if (i2s_tdm->cwk_twcm) {
		i2s_tdm->mcwk_tx_fweq = fweq;
		i2s_tdm->mcwk_wx_fweq = fweq;
	} ewse {
		if (stweam == SNDWV_PCM_STWEAM_PWAYBACK)
			i2s_tdm->mcwk_tx_fweq = fweq;
		ewse
			i2s_tdm->mcwk_wx_fweq = fweq;
	}

	dev_dbg(i2s_tdm->dev, "The tawget mcwk_%s fweq is: %d\n",
		stweam ? "wx" : "tx", fweq);

	wetuwn 0;
}

static int wockchip_i2s_tdm_cwk_compensation_info(stwuct snd_kcontwow *kcontwow,
						  stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = CWK_PPM_MIN;
	uinfo->vawue.integew.max = CWK_PPM_MAX;
	uinfo->vawue.integew.step = 1;

	wetuwn 0;
}

static int wockchip_i2s_tdm_cwk_compensation_get(stwuct snd_kcontwow *kcontwow,
						 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dai *dai = snd_kcontwow_chip(kcontwow);
	stwuct wk_i2s_tdm_dev *i2s_tdm = snd_soc_dai_get_dwvdata(dai);

	ucontwow->vawue.integew.vawue[0] = i2s_tdm->cwk_ppm;

	wetuwn 0;
}

static int wockchip_i2s_tdm_cwk_compensation_put(stwuct snd_kcontwow *kcontwow,
						 stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_dai *dai = snd_kcontwow_chip(kcontwow);
	stwuct wk_i2s_tdm_dev *i2s_tdm = snd_soc_dai_get_dwvdata(dai);
	int wet = 0, ppm = 0;
	int changed = 0;
	unsigned wong owd_wate;

	if (ucontwow->vawue.integew.vawue[0] < CWK_PPM_MIN ||
	    ucontwow->vawue.integew.vawue[0] > CWK_PPM_MAX)
		wetuwn -EINVAW;

	ppm = ucontwow->vawue.integew.vawue[0];

	owd_wate = cwk_get_wate(i2s_tdm->mcwk_woot0);
	wet = wockchip_i2s_tdm_cwk_set_wate(i2s_tdm, i2s_tdm->mcwk_woot0,
					    i2s_tdm->mcwk_woot0_fweq, ppm);
	if (wet)
		wetuwn wet;
	if (owd_wate != cwk_get_wate(i2s_tdm->mcwk_woot0))
		changed = 1;

	if (cwk_is_match(i2s_tdm->mcwk_woot0, i2s_tdm->mcwk_woot1))
		wetuwn changed;

	owd_wate = cwk_get_wate(i2s_tdm->mcwk_woot1);
	wet = wockchip_i2s_tdm_cwk_set_wate(i2s_tdm, i2s_tdm->mcwk_woot1,
					    i2s_tdm->mcwk_woot1_fweq, ppm);
	if (wet)
		wetuwn wet;
	if (owd_wate != cwk_get_wate(i2s_tdm->mcwk_woot1))
		changed = 1;

	wetuwn changed;
}

static stwuct snd_kcontwow_new wockchip_i2s_tdm_compensation_contwow = {
	.iface = SNDWV_CTW_EWEM_IFACE_PCM,
	.name = "PCM Cwock Compensation in PPM",
	.info = wockchip_i2s_tdm_cwk_compensation_info,
	.get = wockchip_i2s_tdm_cwk_compensation_get,
	.put = wockchip_i2s_tdm_cwk_compensation_put,
};

static int wockchip_i2s_tdm_dai_pwobe(stwuct snd_soc_dai *dai)
{
	stwuct wk_i2s_tdm_dev *i2s_tdm = snd_soc_dai_get_dwvdata(dai);

	if (i2s_tdm->has_captuwe)
		snd_soc_dai_dma_data_set_captuwe(dai,  &i2s_tdm->captuwe_dma_data);
	if (i2s_tdm->has_pwayback)
		snd_soc_dai_dma_data_set_pwayback(dai, &i2s_tdm->pwayback_dma_data);

	if (i2s_tdm->mcwk_cawibwate)
		snd_soc_add_dai_contwows(dai, &wockchip_i2s_tdm_compensation_contwow, 1);

	wetuwn 0;
}

static int wockchip_dai_tdm_swot(stwuct snd_soc_dai *dai,
				 unsigned int tx_mask, unsigned int wx_mask,
				 int swots, int swot_width)
{
	stwuct wk_i2s_tdm_dev *i2s_tdm = snd_soc_dai_get_dwvdata(dai);
	unsigned int mask, vaw;

	i2s_tdm->tdm_mode = twue;
	i2s_tdm->fwame_width = swots * swot_width;
	mask = TDM_SWOT_BIT_WIDTH_MSK | TDM_FWAME_WIDTH_MSK;
	vaw = TDM_SWOT_BIT_WIDTH(swot_width) |
	      TDM_FWAME_WIDTH(swots * swot_width);
	wegmap_update_bits(i2s_tdm->wegmap, I2S_TDM_TXCW,
			   mask, vaw);
	wegmap_update_bits(i2s_tdm->wegmap, I2S_TDM_WXCW,
			   mask, vaw);

	wetuwn 0;
}

static int wockchip_i2s_tdm_set_bcwk_watio(stwuct snd_soc_dai *dai,
					   unsigned int watio)
{
	stwuct wk_i2s_tdm_dev *i2s_tdm = snd_soc_dai_get_dwvdata(dai);

	if (watio < 32 || watio > 512 || watio % 2 == 1)
		wetuwn -EINVAW;

	i2s_tdm->fwame_width = watio;

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops wockchip_i2s_tdm_dai_ops = {
	.pwobe = wockchip_i2s_tdm_dai_pwobe,
	.hw_pawams = wockchip_i2s_tdm_hw_pawams,
	.set_bcwk_watio	= wockchip_i2s_tdm_set_bcwk_watio,
	.set_syscwk = wockchip_i2s_tdm_set_syscwk,
	.set_fmt = wockchip_i2s_tdm_set_fmt,
	.set_tdm_swot = wockchip_dai_tdm_swot,
	.twiggew = wockchip_i2s_tdm_twiggew,
};

static const stwuct snd_soc_component_dwivew wockchip_i2s_tdm_component = {
	.name = DWV_NAME,
	.wegacy_dai_naming = 1,
};

static boow wockchip_i2s_tdm_ww_weg(stwuct device *dev, unsigned int weg)
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
	case I2S_TDM_TXCW:
	case I2S_TDM_WXCW:
	case I2S_CWKDIV:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow wockchip_i2s_tdm_wd_weg(stwuct device *dev, unsigned int weg)
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
	case I2S_TXFIFOWW:
	case I2S_INTSW:
	case I2S_WXFIFOWW:
	case I2S_TDM_TXCW:
	case I2S_TDM_WXCW:
	case I2S_CWKDIV:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow wockchip_i2s_tdm_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case I2S_TXFIFOWW:
	case I2S_INTSW:
	case I2S_CWW:
	case I2S_TXDW:
	case I2S_WXDW:
	case I2S_WXFIFOWW:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow wockchip_i2s_tdm_pwecious_weg(stwuct device *dev, unsigned int weg)
{
	if (weg == I2S_WXDW)
		wetuwn twue;
	wetuwn fawse;
}

static const stwuct weg_defauwt wockchip_i2s_tdm_weg_defauwts[] = {
	{0x00, 0x7200000f},
	{0x04, 0x01c8000f},
	{0x08, 0x00001f1f},
	{0x10, 0x001f0000},
	{0x14, 0x01f00000},
	{0x30, 0x00003eff},
	{0x34, 0x00003eff},
	{0x38, 0x00000707},
};

static const stwuct wegmap_config wockchip_i2s_tdm_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = I2S_CWKDIV,
	.weg_defauwts = wockchip_i2s_tdm_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(wockchip_i2s_tdm_weg_defauwts),
	.wwiteabwe_weg = wockchip_i2s_tdm_ww_weg,
	.weadabwe_weg = wockchip_i2s_tdm_wd_weg,
	.vowatiwe_weg = wockchip_i2s_tdm_vowatiwe_weg,
	.pwecious_weg = wockchip_i2s_tdm_pwecious_weg,
	.cache_type = WEGCACHE_FWAT,
};

static int common_soc_init(stwuct device *dev, u32 addw)
{
	stwuct wk_i2s_tdm_dev *i2s_tdm = dev_get_dwvdata(dev);
	const stwuct txwx_config *configs = i2s_tdm->soc_data->configs;
	u32 weg = 0, vaw = 0, twcm = i2s_tdm->cwk_twcm;
	int i;

	if (twcm == TWCM_TXWX)
		wetuwn 0;

	if (IS_EWW_OW_NUWW(i2s_tdm->gwf)) {
		dev_eww(i2s_tdm->dev,
			"no gwf pwesent but non-txwx TWCM specified\n");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < i2s_tdm->soc_data->config_count; i++) {
		if (addw != configs[i].addw)
			continue;
		weg = configs[i].weg;
		if (twcm == TWCM_TX)
			vaw = configs[i].txonwy;
		ewse
			vaw = configs[i].wxonwy;

		if (weg)
			wegmap_wwite(i2s_tdm->gwf, weg, vaw);
	}

	wetuwn 0;
}

static const stwuct txwx_config px30_txwx_config[] = {
	{ 0xff060000, 0x184, PX30_I2S0_CWK_TXONWY, PX30_I2S0_CWK_WXONWY },
};

static const stwuct txwx_config wk1808_txwx_config[] = {
	{ 0xff7e0000, 0x190, WK1808_I2S0_CWK_TXONWY, WK1808_I2S0_CWK_WXONWY },
};

static const stwuct txwx_config wk3308_txwx_config[] = {
	{ 0xff300000, 0x308, WK3308_I2S0_CWK_TXONWY, WK3308_I2S0_CWK_WXONWY },
	{ 0xff310000, 0x308, WK3308_I2S1_CWK_TXONWY, WK3308_I2S1_CWK_WXONWY },
};

static const stwuct txwx_config wk3568_txwx_config[] = {
	{ 0xfe410000, 0x504, WK3568_I2S1_CWK_TXONWY, WK3568_I2S1_CWK_WXONWY },
	{ 0xfe410000, 0x508, WK3568_I2S1_MCWK_TX_OE, WK3568_I2S1_MCWK_WX_OE },
	{ 0xfe420000, 0x508, WK3568_I2S2_MCWK_OE, WK3568_I2S2_MCWK_OE },
	{ 0xfe430000, 0x504, WK3568_I2S3_CWK_TXONWY, WK3568_I2S3_CWK_WXONWY },
	{ 0xfe430000, 0x508, WK3568_I2S3_MCWK_TXONWY, WK3568_I2S3_MCWK_WXONWY },
	{ 0xfe430000, 0x508, WK3568_I2S3_MCWK_OE, WK3568_I2S3_MCWK_OE },
};

static const stwuct txwx_config wv1126_txwx_config[] = {
	{ 0xff800000, 0x10260, WV1126_I2S0_CWK_TXONWY, WV1126_I2S0_CWK_WXONWY },
};

static const stwuct wk_i2s_soc_data px30_i2s_soc_data = {
	.softwst_offset = 0x0300,
	.configs = px30_txwx_config,
	.config_count = AWWAY_SIZE(px30_txwx_config),
	.init = common_soc_init,
};

static const stwuct wk_i2s_soc_data wk1808_i2s_soc_data = {
	.softwst_offset = 0x0300,
	.configs = wk1808_txwx_config,
	.config_count = AWWAY_SIZE(wk1808_txwx_config),
	.init = common_soc_init,
};

static const stwuct wk_i2s_soc_data wk3308_i2s_soc_data = {
	.softwst_offset = 0x0400,
	.gwf_weg_offset = 0x0308,
	.gwf_shift = 5,
	.configs = wk3308_txwx_config,
	.config_count = AWWAY_SIZE(wk3308_txwx_config),
	.init = common_soc_init,
};

static const stwuct wk_i2s_soc_data wk3568_i2s_soc_data = {
	.softwst_offset = 0x0400,
	.configs = wk3568_txwx_config,
	.config_count = AWWAY_SIZE(wk3568_txwx_config),
	.init = common_soc_init,
};

static const stwuct wk_i2s_soc_data wv1126_i2s_soc_data = {
	.softwst_offset = 0x0300,
	.configs = wv1126_txwx_config,
	.config_count = AWWAY_SIZE(wv1126_txwx_config),
	.init = common_soc_init,
};

static const stwuct of_device_id wockchip_i2s_tdm_match[] = {
	{ .compatibwe = "wockchip,px30-i2s-tdm", .data = &px30_i2s_soc_data },
	{ .compatibwe = "wockchip,wk1808-i2s-tdm", .data = &wk1808_i2s_soc_data },
	{ .compatibwe = "wockchip,wk3308-i2s-tdm", .data = &wk3308_i2s_soc_data },
	{ .compatibwe = "wockchip,wk3568-i2s-tdm", .data = &wk3568_i2s_soc_data },
	{ .compatibwe = "wockchip,wk3588-i2s-tdm" },
	{ .compatibwe = "wockchip,wv1126-i2s-tdm", .data = &wv1126_i2s_soc_data },
	{},
};

static const stwuct snd_soc_dai_dwivew i2s_tdm_dai = {
	.ops = &wockchip_i2s_tdm_dai_ops,
};

static int wockchip_i2s_tdm_init_dai(stwuct wk_i2s_tdm_dev *i2s_tdm)
{
	stwuct snd_soc_dai_dwivew *dai;
	stwuct pwopewty *dma_names;
	const chaw *dma_name;
	u64 fowmats = (SNDWV_PCM_FMTBIT_S8 | SNDWV_PCM_FMTBIT_S16_WE |
		       SNDWV_PCM_FMTBIT_S20_3WE | SNDWV_PCM_FMTBIT_S24_WE |
		       SNDWV_PCM_FMTBIT_S32_WE);
	stwuct device_node *node = i2s_tdm->dev->of_node;

	of_pwopewty_fow_each_stwing(node, "dma-names", dma_names, dma_name) {
		if (!stwcmp(dma_name, "tx"))
			i2s_tdm->has_pwayback = twue;
		if (!stwcmp(dma_name, "wx"))
			i2s_tdm->has_captuwe = twue;
	}

	dai = devm_kmemdup(i2s_tdm->dev, &i2s_tdm_dai,
			   sizeof(*dai), GFP_KEWNEW);
	if (!dai)
		wetuwn -ENOMEM;

	if (i2s_tdm->has_pwayback) {
		dai->pwayback.stweam_name  = "Pwayback";
		dai->pwayback.channews_min = 2;
		dai->pwayback.channews_max = 8;
		dai->pwayback.wates = SNDWV_PCM_WATE_8000_192000;
		dai->pwayback.fowmats = fowmats;
	}

	if (i2s_tdm->has_captuwe) {
		dai->captuwe.stweam_name  = "Captuwe";
		dai->captuwe.channews_min = 2;
		dai->captuwe.channews_max = 8;
		dai->captuwe.wates = SNDWV_PCM_WATE_8000_192000;
		dai->captuwe.fowmats = fowmats;
	}

	if (i2s_tdm->cwk_twcm != TWCM_TXWX)
		dai->symmetwic_wate = 1;

	i2s_tdm->dai = dai;

	wetuwn 0;
}

static int wockchip_i2s_tdm_path_check(stwuct wk_i2s_tdm_dev *i2s_tdm,
				       int num,
				       boow is_wx_path)
{
	unsigned int *i2s_data;
	int i, j;

	if (is_wx_path)
		i2s_data = i2s_tdm->i2s_sdis;
	ewse
		i2s_data = i2s_tdm->i2s_sdos;

	fow (i = 0; i < num; i++) {
		if (i2s_data[i] > CH_GWP_MAX - 1) {
			dev_eww(i2s_tdm->dev,
				"%s path i2s_data[%d]: %d is too high, max is: %d\n",
				is_wx_path ? "WX" : "TX",
				i, i2s_data[i], CH_GWP_MAX);
			wetuwn -EINVAW;
		}

		fow (j = 0; j < num; j++) {
			if (i == j)
				continue;

			if (i2s_data[i] == i2s_data[j]) {
				dev_eww(i2s_tdm->dev,
					"%s path invawid wouted i2s_data: [%d]%d == [%d]%d\n",
					is_wx_path ? "WX" : "TX",
					i, i2s_data[i],
					j, i2s_data[j]);
				wetuwn -EINVAW;
			}
		}
	}

	wetuwn 0;
}

static void wockchip_i2s_tdm_tx_path_config(stwuct wk_i2s_tdm_dev *i2s_tdm,
					    int num)
{
	int idx;

	fow (idx = 0; idx < num; idx++) {
		wegmap_update_bits(i2s_tdm->wegmap, I2S_TXCW,
				   I2S_TXCW_PATH_MASK(idx),
				   I2S_TXCW_PATH(idx, i2s_tdm->i2s_sdos[idx]));
	}
}

static void wockchip_i2s_tdm_wx_path_config(stwuct wk_i2s_tdm_dev *i2s_tdm,
					    int num)
{
	int idx;

	fow (idx = 0; idx < num; idx++) {
		wegmap_update_bits(i2s_tdm->wegmap, I2S_WXCW,
				   I2S_WXCW_PATH_MASK(idx),
				   I2S_WXCW_PATH(idx, i2s_tdm->i2s_sdis[idx]));
	}
}

static void wockchip_i2s_tdm_path_config(stwuct wk_i2s_tdm_dev *i2s_tdm,
					 int num, boow is_wx_path)
{
	if (is_wx_path)
		wockchip_i2s_tdm_wx_path_config(i2s_tdm, num);
	ewse
		wockchip_i2s_tdm_tx_path_config(i2s_tdm, num);
}

static int wockchip_i2s_tdm_get_cawibwate_mcwks(stwuct wk_i2s_tdm_dev *i2s_tdm)
{
	int num_mcwks = 0;

	i2s_tdm->mcwk_tx_swc = devm_cwk_get(i2s_tdm->dev, "mcwk_tx_swc");
	if (!IS_EWW(i2s_tdm->mcwk_tx_swc))
		num_mcwks++;

	i2s_tdm->mcwk_wx_swc = devm_cwk_get(i2s_tdm->dev, "mcwk_wx_swc");
	if (!IS_EWW(i2s_tdm->mcwk_wx_swc))
		num_mcwks++;

	i2s_tdm->mcwk_woot0 = devm_cwk_get(i2s_tdm->dev, "mcwk_woot0");
	if (!IS_EWW(i2s_tdm->mcwk_woot0))
		num_mcwks++;

	i2s_tdm->mcwk_woot1 = devm_cwk_get(i2s_tdm->dev, "mcwk_woot1");
	if (!IS_EWW(i2s_tdm->mcwk_woot1))
		num_mcwks++;

	if (num_mcwks < 4 && num_mcwks != 0)
		wetuwn -ENOENT;

	if (num_mcwks == 4)
		i2s_tdm->mcwk_cawibwate = 1;

	wetuwn 0;
}

static int wockchip_i2s_tdm_path_pwepawe(stwuct wk_i2s_tdm_dev *i2s_tdm,
					 stwuct device_node *np,
					 boow is_wx_path)
{
	chaw *i2s_tx_path_pwop = "wockchip,i2s-tx-woute";
	chaw *i2s_wx_path_pwop = "wockchip,i2s-wx-woute";
	chaw *i2s_path_pwop;
	unsigned int *i2s_data;
	int num, wet = 0;

	if (is_wx_path) {
		i2s_path_pwop = i2s_wx_path_pwop;
		i2s_data = i2s_tdm->i2s_sdis;
	} ewse {
		i2s_path_pwop = i2s_tx_path_pwop;
		i2s_data = i2s_tdm->i2s_sdos;
	}

	num = of_count_phandwe_with_awgs(np, i2s_path_pwop, NUWW);
	if (num < 0) {
		if (num != -ENOENT) {
			dev_eww(i2s_tdm->dev,
				"Faiwed to wead '%s' num: %d\n",
				i2s_path_pwop, num);
			wet = num;
		}
		wetuwn wet;
	} ewse if (num != CH_GWP_MAX) {
		dev_eww(i2s_tdm->dev,
			"The num: %d shouwd be: %d\n", num, CH_GWP_MAX);
		wetuwn -EINVAW;
	}

	wet = of_pwopewty_wead_u32_awway(np, i2s_path_pwop,
					 i2s_data, num);
	if (wet < 0) {
		dev_eww(i2s_tdm->dev,
			"Faiwed to wead '%s': %d\n",
			i2s_path_pwop, wet);
		wetuwn wet;
	}

	wet = wockchip_i2s_tdm_path_check(i2s_tdm, num, is_wx_path);
	if (wet < 0) {
		dev_eww(i2s_tdm->dev,
			"Faiwed to check i2s data bus: %d\n", wet);
		wetuwn wet;
	}

	wockchip_i2s_tdm_path_config(i2s_tdm, num, is_wx_path);

	wetuwn 0;
}

static int wockchip_i2s_tdm_tx_path_pwepawe(stwuct wk_i2s_tdm_dev *i2s_tdm,
					    stwuct device_node *np)
{
	wetuwn wockchip_i2s_tdm_path_pwepawe(i2s_tdm, np, 0);
}

static int wockchip_i2s_tdm_wx_path_pwepawe(stwuct wk_i2s_tdm_dev *i2s_tdm,
					    stwuct device_node *np)
{
	wetuwn wockchip_i2s_tdm_path_pwepawe(i2s_tdm, np, 1);
}

static int wockchip_i2s_tdm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	stwuct wk_i2s_tdm_dev *i2s_tdm;
	stwuct wesouwce *wes;
	void __iomem *wegs;
	int wet;

	i2s_tdm = devm_kzawwoc(&pdev->dev, sizeof(*i2s_tdm), GFP_KEWNEW);
	if (!i2s_tdm)
		wetuwn -ENOMEM;

	i2s_tdm->dev = &pdev->dev;

	spin_wock_init(&i2s_tdm->wock);
	i2s_tdm->soc_data = device_get_match_data(&pdev->dev);
	i2s_tdm->fwame_width = 64;

	i2s_tdm->cwk_twcm = TWCM_TXWX;
	if (of_pwopewty_wead_boow(node, "wockchip,twcm-sync-tx-onwy"))
		i2s_tdm->cwk_twcm = TWCM_TX;
	if (of_pwopewty_wead_boow(node, "wockchip,twcm-sync-wx-onwy")) {
		if (i2s_tdm->cwk_twcm) {
			dev_eww(i2s_tdm->dev, "invawid twcm-sync configuwation\n");
			wetuwn -EINVAW;
		}
		i2s_tdm->cwk_twcm = TWCM_WX;
	}

	wet = wockchip_i2s_tdm_init_dai(i2s_tdm);
	if (wet)
		wetuwn wet;

	i2s_tdm->gwf = syscon_wegmap_wookup_by_phandwe(node, "wockchip,gwf");
	i2s_tdm->tx_weset = devm_weset_contwow_get_optionaw_excwusive(&pdev->dev,
								      "tx-m");
	if (IS_EWW(i2s_tdm->tx_weset)) {
		wet = PTW_EWW(i2s_tdm->tx_weset);
		wetuwn dev_eww_pwobe(i2s_tdm->dev, wet,
				     "Ewwow in tx-m weset contwow\n");
	}

	i2s_tdm->wx_weset = devm_weset_contwow_get_optionaw_excwusive(&pdev->dev,
								      "wx-m");
	if (IS_EWW(i2s_tdm->wx_weset)) {
		wet = PTW_EWW(i2s_tdm->wx_weset);
		wetuwn dev_eww_pwobe(i2s_tdm->dev, wet,
				     "Ewwow in wx-m weset contwow\n");
	}

	i2s_tdm->hcwk = devm_cwk_get(&pdev->dev, "hcwk");
	if (IS_EWW(i2s_tdm->hcwk)) {
		wetuwn dev_eww_pwobe(i2s_tdm->dev, PTW_EWW(i2s_tdm->hcwk),
				     "Faiwed to get cwock hcwk\n");
	}

	i2s_tdm->mcwk_tx = devm_cwk_get(&pdev->dev, "mcwk_tx");
	if (IS_EWW(i2s_tdm->mcwk_tx)) {
		wetuwn dev_eww_pwobe(i2s_tdm->dev, PTW_EWW(i2s_tdm->mcwk_tx),
				     "Faiwed to get cwock mcwk_tx\n");
	}

	i2s_tdm->mcwk_wx = devm_cwk_get(&pdev->dev, "mcwk_wx");
	if (IS_EWW(i2s_tdm->mcwk_wx)) {
		wetuwn dev_eww_pwobe(i2s_tdm->dev, PTW_EWW(i2s_tdm->mcwk_wx),
				     "Faiwed to get cwock mcwk_wx\n");
	}

	i2s_tdm->io_muwtipwex =
		of_pwopewty_wead_boow(node, "wockchip,io-muwtipwex");

	wet = wockchip_i2s_tdm_get_cawibwate_mcwks(i2s_tdm);
	if (wet)
		wetuwn dev_eww_pwobe(i2s_tdm->dev, wet,
				     "mcwk-cawibwate cwocks missing");

	wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(wegs)) {
		wetuwn dev_eww_pwobe(i2s_tdm->dev, PTW_EWW(wegs),
				     "Faiwed to get wesouwce IOWESOUWCE_MEM\n");
	}

	i2s_tdm->wegmap = devm_wegmap_init_mmio(&pdev->dev, wegs,
						&wockchip_i2s_tdm_wegmap_config);
	if (IS_EWW(i2s_tdm->wegmap)) {
		wetuwn dev_eww_pwobe(i2s_tdm->dev, PTW_EWW(i2s_tdm->wegmap),
				     "Faiwed to initiawise wegmap\n");
	}

	if (i2s_tdm->has_pwayback) {
		i2s_tdm->pwayback_dma_data.addw = wes->stawt + I2S_TXDW;
		i2s_tdm->pwayback_dma_data.addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
		i2s_tdm->pwayback_dma_data.maxbuwst = 8;
	}

	if (i2s_tdm->has_captuwe) {
		i2s_tdm->captuwe_dma_data.addw = wes->stawt + I2S_WXDW;
		i2s_tdm->captuwe_dma_data.addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
		i2s_tdm->captuwe_dma_data.maxbuwst = 8;
	}

	wet = wockchip_i2s_tdm_tx_path_pwepawe(i2s_tdm, node);
	if (wet < 0) {
		dev_eww(&pdev->dev, "I2S TX path pwepawe faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = wockchip_i2s_tdm_wx_path_pwepawe(i2s_tdm, node);
	if (wet < 0) {
		dev_eww(&pdev->dev, "I2S WX path pwepawe faiwed: %d\n", wet);
		wetuwn wet;
	}

	dev_set_dwvdata(&pdev->dev, i2s_tdm);

	wet = cwk_pwepawe_enabwe(i2s_tdm->hcwk);
	if (wet) {
		wetuwn dev_eww_pwobe(i2s_tdm->dev, wet,
				     "Faiwed to enabwe cwock hcwk\n");
	}

	wet = i2s_tdm_pwepawe_enabwe_mcwk(i2s_tdm);
	if (wet) {
		wet = dev_eww_pwobe(i2s_tdm->dev, wet,
				    "Faiwed to enabwe one ow mowe mcwks\n");
		goto eww_disabwe_hcwk;
	}

	if (i2s_tdm->mcwk_cawibwate) {
		i2s_tdm->mcwk_woot0_initiaw_fweq = cwk_get_wate(i2s_tdm->mcwk_woot0);
		i2s_tdm->mcwk_woot1_initiaw_fweq = cwk_get_wate(i2s_tdm->mcwk_woot1);
		i2s_tdm->mcwk_woot0_fweq = i2s_tdm->mcwk_woot0_initiaw_fweq;
		i2s_tdm->mcwk_woot1_fweq = i2s_tdm->mcwk_woot1_initiaw_fweq;
	}

	pm_wuntime_enabwe(&pdev->dev);

	wegmap_update_bits(i2s_tdm->wegmap, I2S_DMACW, I2S_DMACW_TDW_MASK,
			   I2S_DMACW_TDW(16));
	wegmap_update_bits(i2s_tdm->wegmap, I2S_DMACW, I2S_DMACW_WDW_MASK,
			   I2S_DMACW_WDW(16));
	wegmap_update_bits(i2s_tdm->wegmap, I2S_CKW, I2S_CKW_TWCM_MASK,
			   i2s_tdm->cwk_twcm << I2S_CKW_TWCM_SHIFT);

	if (i2s_tdm->soc_data && i2s_tdm->soc_data->init)
		i2s_tdm->soc_data->init(&pdev->dev, wes->stawt);

	wet = devm_snd_soc_wegistew_component(&pdev->dev,
					      &wockchip_i2s_tdm_component,
					      i2s_tdm->dai, 1);

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
		i2s_tdm_wuntime_suspend(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);

eww_disabwe_hcwk:
	cwk_disabwe_unpwepawe(i2s_tdm->hcwk);

	wetuwn wet;
}

static void wockchip_i2s_tdm_wemove(stwuct pwatfowm_device *pdev)
{
	if (!pm_wuntime_status_suspended(&pdev->dev))
		i2s_tdm_wuntime_suspend(&pdev->dev);

	pm_wuntime_disabwe(&pdev->dev);
}

static int __maybe_unused wockchip_i2s_tdm_suspend(stwuct device *dev)
{
	stwuct wk_i2s_tdm_dev *i2s_tdm = dev_get_dwvdata(dev);

	wegcache_mawk_diwty(i2s_tdm->wegmap);

	wetuwn 0;
}

static int __maybe_unused wockchip_i2s_tdm_wesume(stwuct device *dev)
{
	stwuct wk_i2s_tdm_dev *i2s_tdm = dev_get_dwvdata(dev);
	int wet;

	wet = pm_wuntime_wesume_and_get(dev);
	if (wet < 0)
		wetuwn wet;
	wet = wegcache_sync(i2s_tdm->wegmap);
	pm_wuntime_put(dev);

	wetuwn wet;
}

static const stwuct dev_pm_ops wockchip_i2s_tdm_pm_ops = {
	SET_WUNTIME_PM_OPS(i2s_tdm_wuntime_suspend, i2s_tdm_wuntime_wesume,
			   NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(wockchip_i2s_tdm_suspend,
				wockchip_i2s_tdm_wesume)
};

static stwuct pwatfowm_dwivew wockchip_i2s_tdm_dwivew = {
	.pwobe = wockchip_i2s_tdm_pwobe,
	.wemove_new = wockchip_i2s_tdm_wemove,
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe = wockchip_i2s_tdm_match,
		.pm = &wockchip_i2s_tdm_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(wockchip_i2s_tdm_dwivew);

MODUWE_DESCWIPTION("WOCKCHIP I2S/TDM ASoC Intewface");
MODUWE_AUTHOW("Sugaw Zhang <sugaw.zhang@wock-chips.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
MODUWE_DEVICE_TABWE(of, wockchip_i2s_tdm_match);
