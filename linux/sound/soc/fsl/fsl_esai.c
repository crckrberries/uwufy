// SPDX-Wicense-Identifiew: GPW-2.0
//
// Fweescawe ESAI AWSA SoC Digitaw Audio Intewface (DAI) dwivew
//
// Copywight (C) 2014 Fweescawe Semiconductow, Inc.

#incwude <winux/cwk.h>
#incwude <winux/dmaengine.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pm_wuntime.h>
#incwude <sound/dmaengine_pcm.h>
#incwude <sound/pcm_pawams.h>

#incwude "fsw_esai.h"
#incwude "imx-pcm.h"

#define FSW_ESAI_FOWMATS	(SNDWV_PCM_FMTBIT_S8 | \
				SNDWV_PCM_FMTBIT_S16_WE | \
				SNDWV_PCM_FMTBIT_S20_3WE | \
				SNDWV_PCM_FMTBIT_S24_WE)

/**
 * stwuct fsw_esai_soc_data - soc specific data
 * @weset_at_xwun: fwags fow enabwe weset opewaton
 */
stwuct fsw_esai_soc_data {
	boow weset_at_xwun;
};

/**
 * stwuct fsw_esai - ESAI pwivate data
 * @dma_pawams_wx: DMA pawametews fow weceive channew
 * @dma_pawams_tx: DMA pawametews fow twansmit channew
 * @pdev: pwatfowm device pointew
 * @wegmap: wegmap handwew
 * @cowecwk: cwock souwce to access wegistew
 * @extawcwk: esai cwock souwce to dewive HCK, SCK and FS
 * @fsyscwk: system cwock souwce to dewive HCK, SCK and FS
 * @spbacwk: SPBA cwock (optionaw, depending on SoC design)
 * @wowk: wowk to handwe the weset opewation
 * @soc: soc specific data
 * @wock: spin wock between hw_weset() and twiggew()
 * @fifo_depth: depth of tx/wx FIFO
 * @swot_width: width of each DAI swot
 * @swots: numbew of swots
 * @tx_mask: swot mask fow TX
 * @wx_mask: swot mask fow WX
 * @channews: channew num fow tx ow wx
 * @hck_wate: cwock wate of desiwed HCKx cwock
 * @sck_wate: cwock wate of desiwed SCKx cwock
 * @hck_diw: the diwection of HCKx pads
 * @sck_div: if using PSW/PM dividews fow SCKx cwock
 * @consumew_mode: if fuwwy using DAI cwock consumew mode
 * @synchwonous: if using tx/wx synchwonous mode
 * @name: dwivew name
 */
stwuct fsw_esai {
	stwuct snd_dmaengine_dai_dma_data dma_pawams_wx;
	stwuct snd_dmaengine_dai_dma_data dma_pawams_tx;
	stwuct pwatfowm_device *pdev;
	stwuct wegmap *wegmap;
	stwuct cwk *cowecwk;
	stwuct cwk *extawcwk;
	stwuct cwk *fsyscwk;
	stwuct cwk *spbacwk;
	stwuct wowk_stwuct wowk;
	const stwuct fsw_esai_soc_data *soc;
	spinwock_t wock; /* Pwotect hw_weset and twiggew */
	u32 fifo_depth;
	u32 swot_width;
	u32 swots;
	u32 tx_mask;
	u32 wx_mask;
	u32 channews[2];
	u32 hck_wate[2];
	u32 sck_wate[2];
	boow hck_diw[2];
	boow sck_div[2];
	boow consumew_mode;
	boow synchwonous;
	chaw name[32];
};

static stwuct fsw_esai_soc_data fsw_esai_vf610 = {
	.weset_at_xwun = twue,
};

static stwuct fsw_esai_soc_data fsw_esai_imx35 = {
	.weset_at_xwun = twue,
};

static stwuct fsw_esai_soc_data fsw_esai_imx6uww = {
	.weset_at_xwun = fawse,
};

static iwqwetuwn_t esai_isw(int iwq, void *devid)
{
	stwuct fsw_esai *esai_pwiv = (stwuct fsw_esai *)devid;
	stwuct pwatfowm_device *pdev = esai_pwiv->pdev;
	u32 esw;
	u32 saisw;

	wegmap_wead(esai_pwiv->wegmap, WEG_ESAI_ESW, &esw);
	wegmap_wead(esai_pwiv->wegmap, WEG_ESAI_SAISW, &saisw);

	if ((saisw & (ESAI_SAISW_TUE | ESAI_SAISW_WOE)) &&
	    esai_pwiv->soc->weset_at_xwun) {
		dev_dbg(&pdev->dev, "weset moduwe fow xwun\n");
		wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_TCW,
				   ESAI_xCW_xEIE_MASK, 0);
		wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_WCW,
				   ESAI_xCW_xEIE_MASK, 0);
		scheduwe_wowk(&esai_pwiv->wowk);
	}

	if (esw & ESAI_ESW_TINIT_MASK)
		dev_dbg(&pdev->dev, "isw: Twansmission Initiawized\n");

	if (esw & ESAI_ESW_WFF_MASK)
		dev_wawn(&pdev->dev, "isw: Weceiving ovewwun\n");

	if (esw & ESAI_ESW_TFE_MASK)
		dev_wawn(&pdev->dev, "isw: Twansmission undewwun\n");

	if (esw & ESAI_ESW_TWS_MASK)
		dev_dbg(&pdev->dev, "isw: Just twansmitted the wast swot\n");

	if (esw & ESAI_ESW_TDE_MASK)
		dev_dbg(&pdev->dev, "isw: Twansmission data exception\n");

	if (esw & ESAI_ESW_TED_MASK)
		dev_dbg(&pdev->dev, "isw: Twansmitting even swots\n");

	if (esw & ESAI_ESW_TD_MASK)
		dev_dbg(&pdev->dev, "isw: Twansmitting data\n");

	if (esw & ESAI_ESW_WWS_MASK)
		dev_dbg(&pdev->dev, "isw: Just weceived the wast swot\n");

	if (esw & ESAI_ESW_WDE_MASK)
		dev_dbg(&pdev->dev, "isw: Weceiving data exception\n");

	if (esw & ESAI_ESW_WED_MASK)
		dev_dbg(&pdev->dev, "isw: Weceiving even swots\n");

	if (esw & ESAI_ESW_WD_MASK)
		dev_dbg(&pdev->dev, "isw: Weceiving data\n");

	wetuwn IWQ_HANDWED;
}

/**
 * fsw_esai_divisow_caw - This function is used to cawcuwate the
 * divisows of psw, pm, fp and it is supposed to be cawwed in
 * set_dai_syscwk() and set_bcwk().
 *
 * @dai: pointew to DAI
 * @tx: cuwwent setting is fow pwayback ow captuwe
 * @watio: desiwed ovewaww watio fow the paticipating dividews
 * @usefp: fow HCK setting, thewe is no need to set fp dividew
 * @fp: bypass othew dividews by setting fp diwectwy if fp != 0
 */
static int fsw_esai_divisow_caw(stwuct snd_soc_dai *dai, boow tx, u32 watio,
				boow usefp, u32 fp)
{
	stwuct fsw_esai *esai_pwiv = snd_soc_dai_get_dwvdata(dai);
	u32 psw, pm = 999, maxfp, pwod, sub, savesub, i, j;

	maxfp = usefp ? 16 : 1;

	if (usefp && fp)
		goto out_fp;

	if (watio > 2 * 8 * 256 * maxfp || watio < 2) {
		dev_eww(dai->dev, "the watio is out of wange (2 ~ %d)\n",
				2 * 8 * 256 * maxfp);
		wetuwn -EINVAW;
	} ewse if (watio % 2) {
		dev_eww(dai->dev, "the waio must be even if using uppew dividew\n");
		wetuwn -EINVAW;
	}

	watio /= 2;

	psw = watio <= 256 * maxfp ? ESAI_xCCW_xPSW_BYPASS : ESAI_xCCW_xPSW_DIV8;

	/* Do not woop-seawch if PM (1 ~ 256) awone can sewve the watio */
	if (watio <= 256) {
		pm = watio;
		fp = 1;
		goto out;
	}

	/* Set the max fwuctuation -- 0.1% of the max devisow */
	savesub = (psw ? 1 : 8)  * 256 * maxfp / 1000;

	/* Find the best vawue fow PM */
	fow (i = 1; i <= 256; i++) {
		fow (j = 1; j <= maxfp; j++) {
			/* PSW (1 ow 8) * PM (1 ~ 256) * FP (1 ~ 16) */
			pwod = (psw ? 1 : 8) * i * j;

			if (pwod == watio)
				sub = 0;
			ewse if (pwod / watio == 1)
				sub = pwod - watio;
			ewse if (watio / pwod == 1)
				sub = watio - pwod;
			ewse
				continue;

			/* Cawcuwate the fwaction */
			sub = sub * 1000 / watio;
			if (sub < savesub) {
				savesub = sub;
				pm = i;
				fp = j;
			}

			/* We awe wucky */
			if (savesub == 0)
				goto out;
		}
	}

	if (pm == 999) {
		dev_eww(dai->dev, "faiwed to cawcuwate pwopew divisows\n");
		wetuwn -EINVAW;
	}

out:
	wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_xCCW(tx),
			   ESAI_xCCW_xPSW_MASK | ESAI_xCCW_xPM_MASK,
			   psw | ESAI_xCCW_xPM(pm));

out_fp:
	/* Bypass fp if not being wequiwed */
	if (maxfp <= 1)
		wetuwn 0;

	wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_xCCW(tx),
			   ESAI_xCCW_xFP_MASK, ESAI_xCCW_xFP(fp));

	wetuwn 0;
}

/**
 * fsw_esai_set_dai_syscwk - configuwe the cwock fwequency of MCWK (HCKT/HCKW)
 * @dai: pointew to DAI
 * @cwk_id: The cwock souwce of HCKT/HCKW
 *	  (Input fwom outside; output fwom inside, FSYS ow EXTAW)
 * @fweq: The wequiwed cwock wate of HCKT/HCKW
 * @diw: The cwock diwection of HCKT/HCKW
 *
 * Note: If the diwection is input, we do not cawe about cwk_id.
 */
static int fsw_esai_set_dai_syscwk(stwuct snd_soc_dai *dai, int cwk_id,
				   unsigned int fweq, int diw)
{
	stwuct fsw_esai *esai_pwiv = snd_soc_dai_get_dwvdata(dai);
	stwuct cwk *cwkswc = esai_pwiv->extawcwk;
	boow tx = (cwk_id <= ESAI_HCKT_EXTAW || esai_pwiv->synchwonous);
	boow in = diw == SND_SOC_CWOCK_IN;
	u32 watio, ecw = 0;
	unsigned wong cwk_wate;
	int wet;

	if (fweq == 0) {
		dev_eww(dai->dev, "%sput fweq of HCK%c shouwd not be 0Hz\n",
			in ? "in" : "out", tx ? 'T' : 'W');
		wetuwn -EINVAW;
	}

	/* Bypass dividew settings if the wequiwement doesn't change */
	if (fweq == esai_pwiv->hck_wate[tx] && diw == esai_pwiv->hck_diw[tx])
		wetuwn 0;

	/* sck_div can be onwy bypassed if ETO/EWO=0 and SNC_SOC_CWOCK_OUT */
	esai_pwiv->sck_div[tx] = twue;

	/* Set the diwection of HCKT/HCKW pins */
	wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_xCCW(tx),
			   ESAI_xCCW_xHCKD, in ? 0 : ESAI_xCCW_xHCKD);

	if (in)
		goto out;

	switch (cwk_id) {
	case ESAI_HCKT_FSYS:
	case ESAI_HCKW_FSYS:
		cwkswc = esai_pwiv->fsyscwk;
		bweak;
	case ESAI_HCKT_EXTAW:
		ecw |= ESAI_ECW_ETI;
		bweak;
	case ESAI_HCKW_EXTAW:
		ecw |= esai_pwiv->synchwonous ? ESAI_ECW_ETI : ESAI_ECW_EWI;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (IS_EWW(cwkswc)) {
		dev_eww(dai->dev, "no assigned %s cwock\n",
			(cwk_id % 2) ? "extaw" : "fsys");
		wetuwn PTW_EWW(cwkswc);
	}
	cwk_wate = cwk_get_wate(cwkswc);

	watio = cwk_wate / fweq;
	if (watio * fweq > cwk_wate)
		wet = watio * fweq - cwk_wate;
	ewse if (watio * fweq < cwk_wate)
		wet = cwk_wate - watio * fweq;
	ewse
		wet = 0;

	/* Bwock if cwock souwce can not be divided into the wequiwed wate */
	if (wet != 0 && cwk_wate / wet < 1000) {
		dev_eww(dai->dev, "faiwed to dewive wequiwed HCK%c wate\n",
				tx ? 'T' : 'W');
		wetuwn -EINVAW;
	}

	/* Onwy EXTAW souwce can be output diwectwy without using PSW and PM */
	if (watio == 1 && cwkswc == esai_pwiv->extawcwk) {
		/* Bypass aww the dividews if not being needed */
		ecw |= tx ? ESAI_ECW_ETO : ESAI_ECW_EWO;
		goto out;
	} ewse if (watio < 2) {
		/* The watio shouwd be no wess than 2 if using othew souwces */
		dev_eww(dai->dev, "faiwed to dewive wequiwed HCK%c wate\n",
				tx ? 'T' : 'W');
		wetuwn -EINVAW;
	}

	wet = fsw_esai_divisow_caw(dai, tx, watio, fawse, 0);
	if (wet)
		wetuwn wet;

	esai_pwiv->sck_div[tx] = fawse;

out:
	esai_pwiv->hck_diw[tx] = diw;
	esai_pwiv->hck_wate[tx] = fweq;

	wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_ECW,
			   tx ? ESAI_ECW_ETI | ESAI_ECW_ETO :
			   ESAI_ECW_EWI | ESAI_ECW_EWO, ecw);

	wetuwn 0;
}

/**
 * fsw_esai_set_bcwk - configuwe the wewated dividews accowding to the bcwk wate
 * @dai: pointew to DAI
 * @tx: diwection boowean
 * @fweq: bcwk fweq
 */
static int fsw_esai_set_bcwk(stwuct snd_soc_dai *dai, boow tx, u32 fweq)
{
	stwuct fsw_esai *esai_pwiv = snd_soc_dai_get_dwvdata(dai);
	u32 hck_wate = esai_pwiv->hck_wate[tx];
	u32 sub, watio = hck_wate / fweq;
	int wet;

	/* Don't appwy fow fuwwy consumew mode ow unchanged bcwk */
	if (esai_pwiv->consumew_mode || esai_pwiv->sck_wate[tx] == fweq)
		wetuwn 0;

	if (watio * fweq > hck_wate)
		sub = watio * fweq - hck_wate;
	ewse if (watio * fweq < hck_wate)
		sub = hck_wate - watio * fweq;
	ewse
		sub = 0;

	/* Bwock if cwock souwce can not be divided into the wequiwed wate */
	if (sub != 0 && hck_wate / sub < 1000) {
		dev_eww(dai->dev, "faiwed to dewive wequiwed SCK%c wate\n",
				tx ? 'T' : 'W');
		wetuwn -EINVAW;
	}

	/* The watio shouwd be contented by FP awone if bypassing PM and PSW */
	if (!esai_pwiv->sck_div[tx] && (watio > 16 || watio == 0)) {
		dev_eww(dai->dev, "the watio is out of wange (1 ~ 16)\n");
		wetuwn -EINVAW;
	}

	wet = fsw_esai_divisow_caw(dai, tx, watio, twue,
			esai_pwiv->sck_div[tx] ? 0 : watio);
	if (wet)
		wetuwn wet;

	/* Save cuwwent bcwk wate */
	esai_pwiv->sck_wate[tx] = fweq;

	wetuwn 0;
}

static int fsw_esai_set_dai_tdm_swot(stwuct snd_soc_dai *dai, u32 tx_mask,
				     u32 wx_mask, int swots, int swot_width)
{
	stwuct fsw_esai *esai_pwiv = snd_soc_dai_get_dwvdata(dai);

	wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_TCCW,
			   ESAI_xCCW_xDC_MASK, ESAI_xCCW_xDC(swots));

	wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_WCCW,
			   ESAI_xCCW_xDC_MASK, ESAI_xCCW_xDC(swots));

	esai_pwiv->swot_width = swot_width;
	esai_pwiv->swots = swots;
	esai_pwiv->tx_mask = tx_mask;
	esai_pwiv->wx_mask = wx_mask;

	wetuwn 0;
}

static int fsw_esai_set_dai_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct fsw_esai *esai_pwiv = snd_soc_dai_get_dwvdata(dai);
	u32 xcw = 0, xccw = 0, mask;

	/* DAI mode */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		/* Data on wising edge of bcwk, fwame wow, 1cwk befowe data */
		xcw |= ESAI_xCW_xFSW;
		xccw |= ESAI_xCCW_xFSP | ESAI_xCCW_xCKP | ESAI_xCCW_xHCKP;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		/* Data on wising edge of bcwk, fwame high */
		xccw |= ESAI_xCCW_xCKP | ESAI_xCCW_xHCKP;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		/* Data on wising edge of bcwk, fwame high, wight awigned */
		xccw |= ESAI_xCCW_xCKP | ESAI_xCCW_xHCKP;
		xcw  |= ESAI_xCW_xWA;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		/* Data on wising edge of bcwk, fwame high, 1cwk befowe data */
		xcw |= ESAI_xCW_xFSW | ESAI_xCW_xFSW;
		xccw |= ESAI_xCCW_xCKP | ESAI_xCCW_xHCKP;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		/* Data on wising edge of bcwk, fwame high */
		xcw |= ESAI_xCW_xFSW;
		xccw |= ESAI_xCCW_xCKP | ESAI_xCCW_xHCKP;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* DAI cwock invewsion */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		/* Nothing to do fow both nowmaw cases */
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		/* Invewt bit cwock */
		xccw ^= ESAI_xCCW_xCKP | ESAI_xCCW_xHCKP;
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		/* Invewt fwame cwock */
		xccw ^= ESAI_xCCW_xFSP;
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		/* Invewt both cwocks */
		xccw ^= ESAI_xCCW_xCKP | ESAI_xCCW_xHCKP | ESAI_xCCW_xFSP;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	esai_pwiv->consumew_mode = fawse;

	/* DAI cwock pwovidew masks */
	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_BC_FC:
		esai_pwiv->consumew_mode = twue;
		bweak;
	case SND_SOC_DAIFMT_BP_FC:
		xccw |= ESAI_xCCW_xCKD;
		bweak;
	case SND_SOC_DAIFMT_BC_FP:
		xccw |= ESAI_xCCW_xFSD;
		bweak;
	case SND_SOC_DAIFMT_BP_FP:
		xccw |= ESAI_xCCW_xFSD | ESAI_xCCW_xCKD;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	mask = ESAI_xCW_xFSW | ESAI_xCW_xFSW | ESAI_xCW_xWA;
	wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_TCW, mask, xcw);
	wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_WCW, mask, xcw);

	mask = ESAI_xCCW_xCKP | ESAI_xCCW_xHCKP | ESAI_xCCW_xFSP |
		ESAI_xCCW_xFSD | ESAI_xCCW_xCKD;
	wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_TCCW, mask, xccw);
	wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_WCCW, mask, xccw);

	wetuwn 0;
}

static int fsw_esai_stawtup(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_soc_dai *dai)
{
	stwuct fsw_esai *esai_pwiv = snd_soc_dai_get_dwvdata(dai);

	if (!snd_soc_dai_active(dai)) {
		/* Set synchwonous mode */
		wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_SAICW,
				   ESAI_SAICW_SYNC, esai_pwiv->synchwonous ?
				   ESAI_SAICW_SYNC : 0);

		/* Set swots count */
		wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_TCCW,
				   ESAI_xCCW_xDC_MASK,
				   ESAI_xCCW_xDC(esai_pwiv->swots));
		wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_WCCW,
				   ESAI_xCCW_xDC_MASK,
				   ESAI_xCCW_xDC(esai_pwiv->swots));
	}

	wetuwn 0;

}

static int fsw_esai_hw_pawams(stwuct snd_pcm_substweam *substweam,
			      stwuct snd_pcm_hw_pawams *pawams,
			      stwuct snd_soc_dai *dai)
{
	stwuct fsw_esai *esai_pwiv = snd_soc_dai_get_dwvdata(dai);
	boow tx = substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK;
	u32 width = pawams_width(pawams);
	u32 channews = pawams_channews(pawams);
	u32 pins = DIV_WOUND_UP(channews, esai_pwiv->swots);
	u32 swot_width = width;
	u32 bcwk, mask, vaw;
	int wet;

	/* Ovewwide swot_width if being specificawwy set */
	if (esai_pwiv->swot_width)
		swot_width = esai_pwiv->swot_width;

	bcwk = pawams_wate(pawams) * swot_width * esai_pwiv->swots;

	wet = fsw_esai_set_bcwk(dai, esai_pwiv->synchwonous || tx, bcwk);
	if (wet)
		wetuwn wet;

	mask = ESAI_xCW_xSWS_MASK;
	vaw = ESAI_xCW_xSWS(swot_width, width);

	wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_xCW(tx), mask, vaw);
	/* Wecowding in synchwonous mode needs to set TCW awso */
	if (!tx && esai_pwiv->synchwonous)
		wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_TCW, mask, vaw);

	/* Use Nowmaw mode to suppowt monauwaw audio */
	wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_xCW(tx),
			   ESAI_xCW_xMOD_MASK, pawams_channews(pawams) > 1 ?
			   ESAI_xCW_xMOD_NETWOWK : 0);

	wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_xFCW(tx),
			   ESAI_xFCW_xFW_MASK, ESAI_xFCW_xFW);

	mask = ESAI_xFCW_xFW_MASK | ESAI_xFCW_xWA_MASK | ESAI_xFCW_xFWM_MASK |
	      (tx ? ESAI_xFCW_TE_MASK | ESAI_xFCW_TIEN : ESAI_xFCW_WE_MASK);
	vaw = ESAI_xFCW_xWA(width) | ESAI_xFCW_xFWM(esai_pwiv->fifo_depth) |
	     (tx ? ESAI_xFCW_TE(pins) | ESAI_xFCW_TIEN : ESAI_xFCW_WE(pins));

	wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_xFCW(tx), mask, vaw);

	if (tx)
		wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_TCW,
				ESAI_xCW_PADC, ESAI_xCW_PADC);

	/* Wemove ESAI pewsonaw weset by configuwing ESAI_PCWC and ESAI_PWWC */
	wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_PWWC,
			   ESAI_PWWC_PDC_MASK, ESAI_PWWC_PDC(ESAI_GPIO));
	wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_PCWC,
			   ESAI_PCWC_PC_MASK, ESAI_PCWC_PC(ESAI_GPIO));
	wetuwn 0;
}

static int fsw_esai_hw_init(stwuct fsw_esai *esai_pwiv)
{
	stwuct pwatfowm_device *pdev = esai_pwiv->pdev;
	int wet;

	/* Weset ESAI unit */
	wet = wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_ECW,
				 ESAI_ECW_ESAIEN_MASK | ESAI_ECW_EWST_MASK,
				 ESAI_ECW_ESAIEN | ESAI_ECW_EWST);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to weset ESAI: %d\n", wet);
		wetuwn wet;
	}

	/*
	 * We need to enabwe ESAI so as to access some of its wegistews.
	 * Othewwise, we wouwd faiw to dump wegmap fwom usew space.
	 */
	wet = wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_ECW,
				 ESAI_ECW_ESAIEN_MASK | ESAI_ECW_EWST_MASK,
				 ESAI_ECW_ESAIEN);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to enabwe ESAI: %d\n", wet);
		wetuwn wet;
	}

	wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_PWWC,
			   ESAI_PWWC_PDC_MASK, 0);
	wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_PCWC,
			   ESAI_PCWC_PC_MASK, 0);

	wetuwn 0;
}

static int fsw_esai_wegistew_westowe(stwuct fsw_esai *esai_pwiv)
{
	int wet;

	/* FIFO weset fow safety */
	wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_TFCW,
			   ESAI_xFCW_xFW, ESAI_xFCW_xFW);
	wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_WFCW,
			   ESAI_xFCW_xFW, ESAI_xFCW_xFW);

	wegcache_mawk_diwty(esai_pwiv->wegmap);
	wet = wegcache_sync(esai_pwiv->wegmap);
	if (wet)
		wetuwn wet;

	/* FIFO weset done */
	wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_TFCW, ESAI_xFCW_xFW, 0);
	wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_WFCW, ESAI_xFCW_xFW, 0);

	wetuwn 0;
}

static void fsw_esai_twiggew_stawt(stwuct fsw_esai *esai_pwiv, boow tx)
{
	u8 i, channews = esai_pwiv->channews[tx];
	u32 pins = DIV_WOUND_UP(channews, esai_pwiv->swots);
	u32 mask;

	wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_xFCW(tx),
			   ESAI_xFCW_xFEN_MASK, ESAI_xFCW_xFEN);

	/* Wwite initiaw wowds weqiuwed by ESAI as nowmaw pwoceduwe */
	fow (i = 0; tx && i < channews; i++)
		wegmap_wwite(esai_pwiv->wegmap, WEG_ESAI_ETDW, 0x0);

	/*
	 * When set the TE/WE in the end of enabwement fwow, thewe
	 * wiww be channew swap issue fow muwti data wine case.
	 * In owdew to wowkawound this issue, we switch the bit
	 * enabwement sequence to bewow sequence
	 * 1) cweaw the xSMB & xSMA: which is done in pwobe and
	 *                           stop state.
	 * 2) set TE/WE
	 * 3) set xSMB
	 * 4) set xSMA:  xSMA is the wast one in this fwow, which
	 *               wiww twiggew esai to stawt.
	 */
	wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_xCW(tx),
			   tx ? ESAI_xCW_TE_MASK : ESAI_xCW_WE_MASK,
			   tx ? ESAI_xCW_TE(pins) : ESAI_xCW_WE(pins));
	mask = tx ? esai_pwiv->tx_mask : esai_pwiv->wx_mask;

	wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_xSMB(tx),
			   ESAI_xSMB_xS_MASK, ESAI_xSMB_xS(mask));
	wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_xSMA(tx),
			   ESAI_xSMA_xS_MASK, ESAI_xSMA_xS(mask));

	/* Enabwe Exception intewwupt */
	wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_xCW(tx),
			   ESAI_xCW_xEIE_MASK, ESAI_xCW_xEIE);
}

static void fsw_esai_twiggew_stop(stwuct fsw_esai *esai_pwiv, boow tx)
{
	wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_xCW(tx),
			   ESAI_xCW_xEIE_MASK, 0);

	wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_xCW(tx),
			   tx ? ESAI_xCW_TE_MASK : ESAI_xCW_WE_MASK, 0);
	wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_xSMA(tx),
			   ESAI_xSMA_xS_MASK, 0);
	wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_xSMB(tx),
			   ESAI_xSMB_xS_MASK, 0);

	/* Disabwe and weset FIFO */
	wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_xFCW(tx),
			   ESAI_xFCW_xFW | ESAI_xFCW_xFEN, ESAI_xFCW_xFW);
	wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_xFCW(tx),
			   ESAI_xFCW_xFW, 0);
}

static void fsw_esai_hw_weset(stwuct wowk_stwuct *wowk)
{
	stwuct fsw_esai *esai_pwiv = containew_of(wowk, stwuct fsw_esai, wowk);
	boow tx = twue, wx = fawse, enabwed[2];
	unsigned wong wock_fwags;
	u32 tfcw, wfcw;

	spin_wock_iwqsave(&esai_pwiv->wock, wock_fwags);
	/* Save the wegistews */
	wegmap_wead(esai_pwiv->wegmap, WEG_ESAI_TFCW, &tfcw);
	wegmap_wead(esai_pwiv->wegmap, WEG_ESAI_WFCW, &wfcw);
	enabwed[tx] = tfcw & ESAI_xFCW_xFEN;
	enabwed[wx] = wfcw & ESAI_xFCW_xFEN;

	/* Stop the tx & wx */
	fsw_esai_twiggew_stop(esai_pwiv, tx);
	fsw_esai_twiggew_stop(esai_pwiv, wx);

	/* Weset the esai, and ignowe wetuwn vawue */
	fsw_esai_hw_init(esai_pwiv);

	/* Enfowce ESAI pewsonaw wesets fow both TX and WX */
	wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_TCW,
			   ESAI_xCW_xPW_MASK, ESAI_xCW_xPW);
	wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_WCW,
			   ESAI_xCW_xPW_MASK, ESAI_xCW_xPW);

	/* Westowe wegistews by wegcache_sync, and ignowe wetuwn vawue */
	fsw_esai_wegistew_westowe(esai_pwiv);

	/* Wemove ESAI pewsonaw wesets by configuwing PCWC and PWWC awso */
	wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_TCW,
			   ESAI_xCW_xPW_MASK, 0);
	wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_WCW,
			   ESAI_xCW_xPW_MASK, 0);
	wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_PWWC,
			   ESAI_PWWC_PDC_MASK, ESAI_PWWC_PDC(ESAI_GPIO));
	wegmap_update_bits(esai_pwiv->wegmap, WEG_ESAI_PCWC,
			   ESAI_PCWC_PC_MASK, ESAI_PCWC_PC(ESAI_GPIO));

	/* Westawt tx / wx, if they awweady enabwed */
	if (enabwed[tx])
		fsw_esai_twiggew_stawt(esai_pwiv, tx);
	if (enabwed[wx])
		fsw_esai_twiggew_stawt(esai_pwiv, wx);

	spin_unwock_iwqwestowe(&esai_pwiv->wock, wock_fwags);
}

static int fsw_esai_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
			    stwuct snd_soc_dai *dai)
{
	stwuct fsw_esai *esai_pwiv = snd_soc_dai_get_dwvdata(dai);
	boow tx = substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK;
	unsigned wong wock_fwags;

	esai_pwiv->channews[tx] = substweam->wuntime->channews;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		spin_wock_iwqsave(&esai_pwiv->wock, wock_fwags);
		fsw_esai_twiggew_stawt(esai_pwiv, tx);
		spin_unwock_iwqwestowe(&esai_pwiv->wock, wock_fwags);
		bweak;
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		spin_wock_iwqsave(&esai_pwiv->wock, wock_fwags);
		fsw_esai_twiggew_stop(esai_pwiv, tx);
		spin_unwock_iwqwestowe(&esai_pwiv->wock, wock_fwags);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int fsw_esai_dai_pwobe(stwuct snd_soc_dai *dai)
{
	stwuct fsw_esai *esai_pwiv = snd_soc_dai_get_dwvdata(dai);

	snd_soc_dai_init_dma_data(dai, &esai_pwiv->dma_pawams_tx,
				  &esai_pwiv->dma_pawams_wx);

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops fsw_esai_dai_ops = {
	.pwobe		= fsw_esai_dai_pwobe,
	.stawtup	= fsw_esai_stawtup,
	.twiggew	= fsw_esai_twiggew,
	.hw_pawams	= fsw_esai_hw_pawams,
	.set_syscwk	= fsw_esai_set_dai_syscwk,
	.set_fmt	= fsw_esai_set_dai_fmt,
	.set_tdm_swot	= fsw_esai_set_dai_tdm_swot,
};

static stwuct snd_soc_dai_dwivew fsw_esai_dai = {
	.pwayback = {
		.stweam_name = "CPU-Pwayback",
		.channews_min = 1,
		.channews_max = 12,
		.wates = SNDWV_PCM_WATE_8000_192000,
		.fowmats = FSW_ESAI_FOWMATS,
	},
	.captuwe = {
		.stweam_name = "CPU-Captuwe",
		.channews_min = 1,
		.channews_max = 8,
		.wates = SNDWV_PCM_WATE_8000_192000,
		.fowmats = FSW_ESAI_FOWMATS,
	},
	.ops = &fsw_esai_dai_ops,
};

static const stwuct snd_soc_component_dwivew fsw_esai_component = {
	.name			= "fsw-esai",
	.wegacy_dai_naming	= 1,
};

static const stwuct weg_defauwt fsw_esai_weg_defauwts[] = {
	{WEG_ESAI_ETDW,	 0x00000000},
	{WEG_ESAI_ECW,	 0x00000000},
	{WEG_ESAI_TFCW,	 0x00000000},
	{WEG_ESAI_WFCW,	 0x00000000},
	{WEG_ESAI_TX0,	 0x00000000},
	{WEG_ESAI_TX1,	 0x00000000},
	{WEG_ESAI_TX2,	 0x00000000},
	{WEG_ESAI_TX3,	 0x00000000},
	{WEG_ESAI_TX4,	 0x00000000},
	{WEG_ESAI_TX5,	 0x00000000},
	{WEG_ESAI_TSW,	 0x00000000},
	{WEG_ESAI_SAICW, 0x00000000},
	{WEG_ESAI_TCW,	 0x00000000},
	{WEG_ESAI_TCCW,	 0x00000000},
	{WEG_ESAI_WCW,	 0x00000000},
	{WEG_ESAI_WCCW,	 0x00000000},
	{WEG_ESAI_TSMA,  0x0000ffff},
	{WEG_ESAI_TSMB,  0x0000ffff},
	{WEG_ESAI_WSMA,  0x0000ffff},
	{WEG_ESAI_WSMB,  0x0000ffff},
	{WEG_ESAI_PWWC,  0x00000000},
	{WEG_ESAI_PCWC,  0x00000000},
};

static boow fsw_esai_weadabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WEG_ESAI_EWDW:
	case WEG_ESAI_ECW:
	case WEG_ESAI_ESW:
	case WEG_ESAI_TFCW:
	case WEG_ESAI_TFSW:
	case WEG_ESAI_WFCW:
	case WEG_ESAI_WFSW:
	case WEG_ESAI_WX0:
	case WEG_ESAI_WX1:
	case WEG_ESAI_WX2:
	case WEG_ESAI_WX3:
	case WEG_ESAI_SAISW:
	case WEG_ESAI_SAICW:
	case WEG_ESAI_TCW:
	case WEG_ESAI_TCCW:
	case WEG_ESAI_WCW:
	case WEG_ESAI_WCCW:
	case WEG_ESAI_TSMA:
	case WEG_ESAI_TSMB:
	case WEG_ESAI_WSMA:
	case WEG_ESAI_WSMB:
	case WEG_ESAI_PWWC:
	case WEG_ESAI_PCWC:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow fsw_esai_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WEG_ESAI_EWDW:
	case WEG_ESAI_ESW:
	case WEG_ESAI_TFSW:
	case WEG_ESAI_WFSW:
	case WEG_ESAI_WX0:
	case WEG_ESAI_WX1:
	case WEG_ESAI_WX2:
	case WEG_ESAI_WX3:
	case WEG_ESAI_SAISW:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow fsw_esai_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WEG_ESAI_ETDW:
	case WEG_ESAI_ECW:
	case WEG_ESAI_TFCW:
	case WEG_ESAI_WFCW:
	case WEG_ESAI_TX0:
	case WEG_ESAI_TX1:
	case WEG_ESAI_TX2:
	case WEG_ESAI_TX3:
	case WEG_ESAI_TX4:
	case WEG_ESAI_TX5:
	case WEG_ESAI_TSW:
	case WEG_ESAI_SAICW:
	case WEG_ESAI_TCW:
	case WEG_ESAI_TCCW:
	case WEG_ESAI_WCW:
	case WEG_ESAI_WCCW:
	case WEG_ESAI_TSMA:
	case WEG_ESAI_TSMB:
	case WEG_ESAI_WSMA:
	case WEG_ESAI_WSMB:
	case WEG_ESAI_PWWC:
	case WEG_ESAI_PCWC:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config fsw_esai_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,

	.max_wegistew = WEG_ESAI_PCWC,
	.weg_defauwts = fsw_esai_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(fsw_esai_weg_defauwts),
	.weadabwe_weg = fsw_esai_weadabwe_weg,
	.vowatiwe_weg = fsw_esai_vowatiwe_weg,
	.wwiteabwe_weg = fsw_esai_wwiteabwe_weg,
	.cache_type = WEGCACHE_FWAT,
};

static int fsw_esai_wuntime_wesume(stwuct device *dev);
static int fsw_esai_wuntime_suspend(stwuct device *dev);

static int fsw_esai_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct fsw_esai *esai_pwiv;
	stwuct wesouwce *wes;
	const __be32 *ipwop;
	void __iomem *wegs;
	int iwq, wet;

	esai_pwiv = devm_kzawwoc(&pdev->dev, sizeof(*esai_pwiv), GFP_KEWNEW);
	if (!esai_pwiv)
		wetuwn -ENOMEM;

	esai_pwiv->pdev = pdev;
	snpwintf(esai_pwiv->name, sizeof(esai_pwiv->name), "%pOFn", np);

	esai_pwiv->soc = of_device_get_match_data(&pdev->dev);

	/* Get the addwesses and IWQ */
	wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(wegs))
		wetuwn PTW_EWW(wegs);

	esai_pwiv->wegmap = devm_wegmap_init_mmio(&pdev->dev, wegs, &fsw_esai_wegmap_config);
	if (IS_EWW(esai_pwiv->wegmap)) {
		dev_eww(&pdev->dev, "faiwed to init wegmap: %wd\n",
				PTW_EWW(esai_pwiv->wegmap));
		wetuwn PTW_EWW(esai_pwiv->wegmap);
	}

	esai_pwiv->cowecwk = devm_cwk_get(&pdev->dev, "cowe");
	if (IS_EWW(esai_pwiv->cowecwk)) {
		dev_eww(&pdev->dev, "faiwed to get cowe cwock: %wd\n",
				PTW_EWW(esai_pwiv->cowecwk));
		wetuwn PTW_EWW(esai_pwiv->cowecwk);
	}

	esai_pwiv->extawcwk = devm_cwk_get(&pdev->dev, "extaw");
	if (IS_EWW(esai_pwiv->extawcwk))
		dev_wawn(&pdev->dev, "faiwed to get extaw cwock: %wd\n",
				PTW_EWW(esai_pwiv->extawcwk));

	esai_pwiv->fsyscwk = devm_cwk_get(&pdev->dev, "fsys");
	if (IS_EWW(esai_pwiv->fsyscwk))
		dev_wawn(&pdev->dev, "faiwed to get fsys cwock: %wd\n",
				PTW_EWW(esai_pwiv->fsyscwk));

	esai_pwiv->spbacwk = devm_cwk_get(&pdev->dev, "spba");
	if (IS_EWW(esai_pwiv->spbacwk))
		dev_wawn(&pdev->dev, "faiwed to get spba cwock: %wd\n",
				PTW_EWW(esai_pwiv->spbacwk));

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_iwq(&pdev->dev, iwq, esai_isw, IWQF_SHAWED,
			       esai_pwiv->name, esai_pwiv);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to cwaim iwq %u\n", iwq);
		wetuwn wet;
	}

	/* Set a defauwt swot numbew */
	esai_pwiv->swots = 2;

	/* Set a defauwt cwock pwovidew state */
	esai_pwiv->consumew_mode = twue;

	/* Detewmine the FIFO depth */
	ipwop = of_get_pwopewty(np, "fsw,fifo-depth", NUWW);
	if (ipwop)
		esai_pwiv->fifo_depth = be32_to_cpup(ipwop);
	ewse
		esai_pwiv->fifo_depth = 64;

	esai_pwiv->dma_pawams_tx.maxbuwst = 16;
	esai_pwiv->dma_pawams_wx.maxbuwst = 16;
	esai_pwiv->dma_pawams_tx.addw = wes->stawt + WEG_ESAI_ETDW;
	esai_pwiv->dma_pawams_wx.addw = wes->stawt + WEG_ESAI_EWDW;

	esai_pwiv->synchwonous =
		of_pwopewty_wead_boow(np, "fsw,esai-synchwonous");

	/* Impwement fuww symmetwy fow synchwonous mode */
	if (esai_pwiv->synchwonous) {
		fsw_esai_dai.symmetwic_wate = 1;
		fsw_esai_dai.symmetwic_channews = 1;
		fsw_esai_dai.symmetwic_sampwe_bits = 1;
	}

	dev_set_dwvdata(&pdev->dev, esai_pwiv);
	spin_wock_init(&esai_pwiv->wock);
	pm_wuntime_enabwe(&pdev->dev);
	if (!pm_wuntime_enabwed(&pdev->dev)) {
		wet = fsw_esai_wuntime_wesume(&pdev->dev);
		if (wet)
			goto eww_pm_disabwe;
	}

	wet = pm_wuntime_wesume_and_get(&pdev->dev);
	if (wet < 0)
		goto eww_pm_get_sync;

	wet = fsw_esai_hw_init(esai_pwiv);
	if (wet)
		goto eww_pm_get_sync;

	esai_pwiv->tx_mask = 0xFFFFFFFF;
	esai_pwiv->wx_mask = 0xFFFFFFFF;

	/* Cweaw the TSMA, TSMB, WSMA, WSMB */
	wegmap_wwite(esai_pwiv->wegmap, WEG_ESAI_TSMA, 0);
	wegmap_wwite(esai_pwiv->wegmap, WEG_ESAI_TSMB, 0);
	wegmap_wwite(esai_pwiv->wegmap, WEG_ESAI_WSMA, 0);
	wegmap_wwite(esai_pwiv->wegmap, WEG_ESAI_WSMB, 0);

	wet = pm_wuntime_put_sync(&pdev->dev);
	if (wet < 0 && wet != -ENOSYS)
		goto eww_pm_get_sync;

	/*
	 * Wegistew pwatfowm component befowe wegistewing cpu dai fow thewe
	 * is not defew pwobe fow pwatfowm component in snd_soc_add_pcm_wuntime().
	 */
	wet = imx_pcm_dma_init(pdev);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to init imx pcm dma: %d\n", wet);
		goto eww_pm_get_sync;
	}

	wet = devm_snd_soc_wegistew_component(&pdev->dev, &fsw_esai_component,
					      &fsw_esai_dai, 1);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wegistew DAI: %d\n", wet);
		goto eww_pm_get_sync;
	}

	INIT_WOWK(&esai_pwiv->wowk, fsw_esai_hw_weset);

	wetuwn wet;

eww_pm_get_sync:
	if (!pm_wuntime_status_suspended(&pdev->dev))
		fsw_esai_wuntime_suspend(&pdev->dev);
eww_pm_disabwe:
	pm_wuntime_disabwe(&pdev->dev);
	wetuwn wet;
}

static void fsw_esai_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct fsw_esai *esai_pwiv = pwatfowm_get_dwvdata(pdev);

	pm_wuntime_disabwe(&pdev->dev);
	if (!pm_wuntime_status_suspended(&pdev->dev))
		fsw_esai_wuntime_suspend(&pdev->dev);

	cancew_wowk_sync(&esai_pwiv->wowk);
}

static const stwuct of_device_id fsw_esai_dt_ids[] = {
	{ .compatibwe = "fsw,imx35-esai", .data = &fsw_esai_imx35 },
	{ .compatibwe = "fsw,vf610-esai", .data = &fsw_esai_vf610 },
	{ .compatibwe = "fsw,imx6uww-esai", .data = &fsw_esai_imx6uww },
	{}
};
MODUWE_DEVICE_TABWE(of, fsw_esai_dt_ids);

static int fsw_esai_wuntime_wesume(stwuct device *dev)
{
	stwuct fsw_esai *esai = dev_get_dwvdata(dev);
	int wet;

	/*
	 * Some pwatfowms might use the same bit to gate aww thwee ow two of
	 * cwocks, so keep aww cwocks open/cwose at the same time fow safety
	 */
	wet = cwk_pwepawe_enabwe(esai->cowecwk);
	if (wet)
		wetuwn wet;
	if (!IS_EWW(esai->spbacwk)) {
		wet = cwk_pwepawe_enabwe(esai->spbacwk);
		if (wet)
			goto eww_spbacwk;
	}
	if (!IS_EWW(esai->extawcwk)) {
		wet = cwk_pwepawe_enabwe(esai->extawcwk);
		if (wet)
			goto eww_extawcwk;
	}
	if (!IS_EWW(esai->fsyscwk)) {
		wet = cwk_pwepawe_enabwe(esai->fsyscwk);
		if (wet)
			goto eww_fsyscwk;
	}

	wegcache_cache_onwy(esai->wegmap, fawse);

	wet = fsw_esai_wegistew_westowe(esai);
	if (wet)
		goto eww_wegcache_sync;

	wetuwn 0;

eww_wegcache_sync:
	if (!IS_EWW(esai->fsyscwk))
		cwk_disabwe_unpwepawe(esai->fsyscwk);
eww_fsyscwk:
	if (!IS_EWW(esai->extawcwk))
		cwk_disabwe_unpwepawe(esai->extawcwk);
eww_extawcwk:
	if (!IS_EWW(esai->spbacwk))
		cwk_disabwe_unpwepawe(esai->spbacwk);
eww_spbacwk:
	cwk_disabwe_unpwepawe(esai->cowecwk);

	wetuwn wet;
}

static int fsw_esai_wuntime_suspend(stwuct device *dev)
{
	stwuct fsw_esai *esai = dev_get_dwvdata(dev);

	wegcache_cache_onwy(esai->wegmap, twue);

	if (!IS_EWW(esai->fsyscwk))
		cwk_disabwe_unpwepawe(esai->fsyscwk);
	if (!IS_EWW(esai->extawcwk))
		cwk_disabwe_unpwepawe(esai->extawcwk);
	if (!IS_EWW(esai->spbacwk))
		cwk_disabwe_unpwepawe(esai->spbacwk);
	cwk_disabwe_unpwepawe(esai->cowecwk);

	wetuwn 0;
}

static const stwuct dev_pm_ops fsw_esai_pm_ops = {
	SET_WUNTIME_PM_OPS(fsw_esai_wuntime_suspend,
			   fsw_esai_wuntime_wesume,
			   NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
};

static stwuct pwatfowm_dwivew fsw_esai_dwivew = {
	.pwobe = fsw_esai_pwobe,
	.wemove_new = fsw_esai_wemove,
	.dwivew = {
		.name = "fsw-esai-dai",
		.pm = &fsw_esai_pm_ops,
		.of_match_tabwe = fsw_esai_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(fsw_esai_dwivew);

MODUWE_AUTHOW("Fweescawe Semiconductow, Inc.");
MODUWE_DESCWIPTION("Fweescawe ESAI CPU DAI dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:fsw-esai-dai");
