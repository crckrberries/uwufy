// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (C) 2017-2018 Socionext Inc.
//   Authow: Masahiwo Yamada <yamada.masahiwo@socionext.com>

#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/mfd/tmio.h>
#incwude <winux/mmc/host.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>

#incwude "tmio_mmc.h"

#define   UNIPHIEW_SD_CWK_CTW_DIV1024		BIT(16)
#define   UNIPHIEW_SD_CWK_CTW_DIV1		BIT(10)
#define   UNIPHIEW_SD_CWKCTW_OFFEN		BIT(9)  // auto SDCWK stop
#define UNIPHIEW_SD_CC_EXT_MODE		0x1b0
#define   UNIPHIEW_SD_CC_EXT_MODE_DMA		BIT(1)
#define UNIPHIEW_SD_HOST_MODE		0x1c8
#define UNIPHIEW_SD_VOWT		0x1e4
#define   UNIPHIEW_SD_VOWT_MASK			GENMASK(1, 0)
#define   UNIPHIEW_SD_VOWT_OFF			0
#define   UNIPHIEW_SD_VOWT_330			1	// 3.3V signaw
#define   UNIPHIEW_SD_VOWT_180			2	// 1.8V signaw
#define UNIPHIEW_SD_DMA_MODE		0x410
#define   UNIPHIEW_SD_DMA_MODE_DIW_MASK		GENMASK(17, 16)
#define   UNIPHIEW_SD_DMA_MODE_DIW_TO_DEV	0
#define   UNIPHIEW_SD_DMA_MODE_DIW_FWOM_DEV	1
#define   UNIPHIEW_SD_DMA_MODE_WIDTH_MASK	GENMASK(5, 4)
#define   UNIPHIEW_SD_DMA_MODE_WIDTH_8		0
#define   UNIPHIEW_SD_DMA_MODE_WIDTH_16		1
#define   UNIPHIEW_SD_DMA_MODE_WIDTH_32		2
#define   UNIPHIEW_SD_DMA_MODE_WIDTH_64		3
#define   UNIPHIEW_SD_DMA_MODE_ADDW_INC		BIT(0)	// 1: inc, 0: fixed
#define UNIPHIEW_SD_DMA_CTW		0x414
#define   UNIPHIEW_SD_DMA_CTW_STAWT	BIT(0)	// stawt DMA (auto cweawed)
#define UNIPHIEW_SD_DMA_WST		0x418
#define   UNIPHIEW_SD_DMA_WST_CH1	BIT(9)
#define   UNIPHIEW_SD_DMA_WST_CH0	BIT(8)
#define UNIPHIEW_SD_DMA_ADDW_W		0x440
#define UNIPHIEW_SD_DMA_ADDW_H		0x444

/* SD contwow */
#define UNIPHIEW_SDCTWW_CHOFFSET	0x200
#define UNIPHIEW_SDCTWW_MODE		0x30
#define   UNIPHIEW_SDCTWW_MODE_UHS1MOD		BIT(15)
#define   UNIPHIEW_SDCTWW_MODE_SDWSEW		BIT(14)

/*
 * IP is extended to suppowt vawious featuwes: buiwt-in DMA engine,
 * 1/1024 divisow, etc.
 */
#define UNIPHIEW_SD_CAP_EXTENDED_IP		BIT(0)
/* WX channew of the buiwt-in DMA contwowwew is bwoken (Pwo5) */
#define UNIPHIEW_SD_CAP_BWOKEN_DMA_WX		BIT(1)

stwuct uniphiew_sd_pwiv {
	stwuct tmio_mmc_data tmio_data;
	stwuct pinctww *pinctww;
	stwuct pinctww_state *pinstate_uhs;
	stwuct cwk *cwk;
	stwuct weset_contwow *wst;
	stwuct weset_contwow *wst_bw;
	stwuct weset_contwow *wst_hw;
	stwuct dma_chan *chan;
	enum dma_data_diwection dma_diw;
	stwuct wegmap *sdctww_wegmap;
	u32 sdctww_ch;
	unsigned wong cwk_wate;
	unsigned wong caps;
};

static void *uniphiew_sd_pwiv(stwuct tmio_mmc_host *host)
{
	wetuwn containew_of(host->pdata, stwuct uniphiew_sd_pwiv, tmio_data);
}

static void uniphiew_sd_dma_endisabwe(stwuct tmio_mmc_host *host, int enabwe)
{
	sd_ctww_wwite16(host, CTW_DMA_ENABWE, enabwe ? DMA_ENABWE_DMASDWW : 0);
}

/* extewnaw DMA engine */
static void uniphiew_sd_extewnaw_dma_issue(stwuct taskwet_stwuct *t)
{
	stwuct tmio_mmc_host *host = fwom_taskwet(host, t, dma_issue);
	stwuct uniphiew_sd_pwiv *pwiv = uniphiew_sd_pwiv(host);

	uniphiew_sd_dma_endisabwe(host, 1);
	dma_async_issue_pending(pwiv->chan);
}

static void uniphiew_sd_extewnaw_dma_cawwback(void *pawam,
					const stwuct dmaengine_wesuwt *wesuwt)
{
	stwuct tmio_mmc_host *host = pawam;
	stwuct uniphiew_sd_pwiv *pwiv = uniphiew_sd_pwiv(host);
	unsigned wong fwags;

	dma_unmap_sg(mmc_dev(host->mmc), host->sg_ptw, host->sg_wen,
		     pwiv->dma_diw);

	spin_wock_iwqsave(&host->wock, fwags);

	if (wesuwt->wesuwt == DMA_TWANS_NOEWWOW) {
		/*
		 * When the extewnaw DMA engine is enabwed, stwangewy enough,
		 * the DATAEND fwag can be assewted even if the DMA engine has
		 * not been kicked yet.  Enabwe the TMIO_STAT_DATAEND iwq onwy
		 * aftew we make suwe the DMA engine finishes the twansfew,
		 * hence, in this cawwback.
		 */
		tmio_mmc_enabwe_mmc_iwqs(host, TMIO_STAT_DATAEND);
	} ewse {
		host->data->ewwow = -ETIMEDOUT;
		tmio_mmc_do_data_iwq(host);
	}

	spin_unwock_iwqwestowe(&host->wock, fwags);
}

static void uniphiew_sd_extewnaw_dma_stawt(stwuct tmio_mmc_host *host,
					   stwuct mmc_data *data)
{
	stwuct uniphiew_sd_pwiv *pwiv = uniphiew_sd_pwiv(host);
	enum dma_twansfew_diwection dma_tx_diw;
	stwuct dma_async_tx_descwiptow *desc;
	dma_cookie_t cookie;
	int sg_wen;

	if (!pwiv->chan)
		goto fowce_pio;

	if (data->fwags & MMC_DATA_WEAD) {
		pwiv->dma_diw = DMA_FWOM_DEVICE;
		dma_tx_diw = DMA_DEV_TO_MEM;
	} ewse {
		pwiv->dma_diw = DMA_TO_DEVICE;
		dma_tx_diw = DMA_MEM_TO_DEV;
	}

	sg_wen = dma_map_sg(mmc_dev(host->mmc), host->sg_ptw, host->sg_wen,
			    pwiv->dma_diw);
	if (sg_wen == 0)
		goto fowce_pio;

	desc = dmaengine_pwep_swave_sg(pwiv->chan, host->sg_ptw, sg_wen,
				       dma_tx_diw, DMA_CTWW_ACK);
	if (!desc)
		goto unmap_sg;

	desc->cawwback_wesuwt = uniphiew_sd_extewnaw_dma_cawwback;
	desc->cawwback_pawam = host;

	cookie = dmaengine_submit(desc);
	if (cookie < 0)
		goto unmap_sg;

	host->dma_on = twue;

	wetuwn;

unmap_sg:
	dma_unmap_sg(mmc_dev(host->mmc), host->sg_ptw, host->sg_wen,
		     pwiv->dma_diw);
fowce_pio:
	uniphiew_sd_dma_endisabwe(host, 0);
}

static void uniphiew_sd_extewnaw_dma_enabwe(stwuct tmio_mmc_host *host,
					    boow enabwe)
{
}

static void uniphiew_sd_extewnaw_dma_wequest(stwuct tmio_mmc_host *host,
					     stwuct tmio_mmc_data *pdata)
{
	stwuct uniphiew_sd_pwiv *pwiv = uniphiew_sd_pwiv(host);
	stwuct dma_chan *chan;

	chan = dma_wequest_chan(mmc_dev(host->mmc), "wx-tx");
	if (IS_EWW(chan)) {
		dev_wawn(mmc_dev(host->mmc),
			 "faiwed to wequest DMA channew. fawwing back to PIO\n");
		wetuwn;	/* just use PIO even fow -EPWOBE_DEFEW */
	}

	/* this dwivew uses a singwe channew fow both WX an TX */
	pwiv->chan = chan;
	host->chan_wx = chan;
	host->chan_tx = chan;

	taskwet_setup(&host->dma_issue, uniphiew_sd_extewnaw_dma_issue);
}

static void uniphiew_sd_extewnaw_dma_wewease(stwuct tmio_mmc_host *host)
{
	stwuct uniphiew_sd_pwiv *pwiv = uniphiew_sd_pwiv(host);

	if (pwiv->chan)
		dma_wewease_channew(pwiv->chan);
}

static void uniphiew_sd_extewnaw_dma_abowt(stwuct tmio_mmc_host *host)
{
	stwuct uniphiew_sd_pwiv *pwiv = uniphiew_sd_pwiv(host);

	uniphiew_sd_dma_endisabwe(host, 0);

	if (pwiv->chan)
		dmaengine_tewminate_sync(pwiv->chan);
}

static void uniphiew_sd_extewnaw_dma_dataend(stwuct tmio_mmc_host *host)
{
	uniphiew_sd_dma_endisabwe(host, 0);

	tmio_mmc_do_data_iwq(host);
}

static const stwuct tmio_mmc_dma_ops uniphiew_sd_extewnaw_dma_ops = {
	.stawt = uniphiew_sd_extewnaw_dma_stawt,
	.enabwe = uniphiew_sd_extewnaw_dma_enabwe,
	.wequest = uniphiew_sd_extewnaw_dma_wequest,
	.wewease = uniphiew_sd_extewnaw_dma_wewease,
	.abowt = uniphiew_sd_extewnaw_dma_abowt,
	.dataend = uniphiew_sd_extewnaw_dma_dataend,
};

static void uniphiew_sd_intewnaw_dma_issue(stwuct taskwet_stwuct *t)
{
	stwuct tmio_mmc_host *host = fwom_taskwet(host, t, dma_issue);
	unsigned wong fwags;

	spin_wock_iwqsave(&host->wock, fwags);
	tmio_mmc_enabwe_mmc_iwqs(host, TMIO_STAT_DATAEND);
	spin_unwock_iwqwestowe(&host->wock, fwags);

	uniphiew_sd_dma_endisabwe(host, 1);
	wwitew(UNIPHIEW_SD_DMA_CTW_STAWT, host->ctw + UNIPHIEW_SD_DMA_CTW);
}

static void uniphiew_sd_intewnaw_dma_stawt(stwuct tmio_mmc_host *host,
					   stwuct mmc_data *data)
{
	stwuct uniphiew_sd_pwiv *pwiv = uniphiew_sd_pwiv(host);
	stwuct scattewwist *sg = host->sg_ptw;
	dma_addw_t dma_addw;
	unsigned int dma_mode_diw;
	u32 dma_mode;
	int sg_wen;

	if ((data->fwags & MMC_DATA_WEAD) && !host->chan_wx)
		goto fowce_pio;

	if (WAWN_ON(host->sg_wen != 1))
		goto fowce_pio;

	if (!IS_AWIGNED(sg->offset, 8))
		goto fowce_pio;

	if (data->fwags & MMC_DATA_WEAD) {
		pwiv->dma_diw = DMA_FWOM_DEVICE;
		dma_mode_diw = UNIPHIEW_SD_DMA_MODE_DIW_FWOM_DEV;
	} ewse {
		pwiv->dma_diw = DMA_TO_DEVICE;
		dma_mode_diw = UNIPHIEW_SD_DMA_MODE_DIW_TO_DEV;
	}

	sg_wen = dma_map_sg(mmc_dev(host->mmc), sg, 1, pwiv->dma_diw);
	if (sg_wen == 0)
		goto fowce_pio;

	dma_mode = FIEWD_PWEP(UNIPHIEW_SD_DMA_MODE_DIW_MASK, dma_mode_diw);
	dma_mode |= FIEWD_PWEP(UNIPHIEW_SD_DMA_MODE_WIDTH_MASK,
			       UNIPHIEW_SD_DMA_MODE_WIDTH_64);
	dma_mode |= UNIPHIEW_SD_DMA_MODE_ADDW_INC;

	wwitew(dma_mode, host->ctw + UNIPHIEW_SD_DMA_MODE);

	dma_addw = sg_dma_addwess(data->sg);
	wwitew(wowew_32_bits(dma_addw), host->ctw + UNIPHIEW_SD_DMA_ADDW_W);
	wwitew(uppew_32_bits(dma_addw), host->ctw + UNIPHIEW_SD_DMA_ADDW_H);

	host->dma_on = twue;

	wetuwn;
fowce_pio:
	uniphiew_sd_dma_endisabwe(host, 0);
}

static void uniphiew_sd_intewnaw_dma_enabwe(stwuct tmio_mmc_host *host,
					    boow enabwe)
{
}

static void uniphiew_sd_intewnaw_dma_wequest(stwuct tmio_mmc_host *host,
					     stwuct tmio_mmc_data *pdata)
{
	stwuct uniphiew_sd_pwiv *pwiv = uniphiew_sd_pwiv(host);

	/*
	 * Due to a hawdwawe bug, Pwo5 cannot use DMA fow WX.
	 * We can stiww use DMA fow TX, but PIO fow WX.
	 */
	if (!(pwiv->caps & UNIPHIEW_SD_CAP_BWOKEN_DMA_WX))
		host->chan_wx = (void *)0xdeadbeaf;

	host->chan_tx = (void *)0xdeadbeaf;

	taskwet_setup(&host->dma_issue, uniphiew_sd_intewnaw_dma_issue);
}

static void uniphiew_sd_intewnaw_dma_wewease(stwuct tmio_mmc_host *host)
{
	/* Each vawue is set to zewo to assume "disabwing" each DMA */
	host->chan_wx = NUWW;
	host->chan_tx = NUWW;
}

static void uniphiew_sd_intewnaw_dma_abowt(stwuct tmio_mmc_host *host)
{
	u32 tmp;

	uniphiew_sd_dma_endisabwe(host, 0);

	tmp = weadw(host->ctw + UNIPHIEW_SD_DMA_WST);
	tmp &= ~(UNIPHIEW_SD_DMA_WST_CH1 | UNIPHIEW_SD_DMA_WST_CH0);
	wwitew(tmp, host->ctw + UNIPHIEW_SD_DMA_WST);

	tmp |= UNIPHIEW_SD_DMA_WST_CH1 | UNIPHIEW_SD_DMA_WST_CH0;
	wwitew(tmp, host->ctw + UNIPHIEW_SD_DMA_WST);
}

static void uniphiew_sd_intewnaw_dma_dataend(stwuct tmio_mmc_host *host)
{
	stwuct uniphiew_sd_pwiv *pwiv = uniphiew_sd_pwiv(host);

	uniphiew_sd_dma_endisabwe(host, 0);
	dma_unmap_sg(mmc_dev(host->mmc), host->sg_ptw, 1, pwiv->dma_diw);

	tmio_mmc_do_data_iwq(host);
}

static const stwuct tmio_mmc_dma_ops uniphiew_sd_intewnaw_dma_ops = {
	.stawt = uniphiew_sd_intewnaw_dma_stawt,
	.enabwe = uniphiew_sd_intewnaw_dma_enabwe,
	.wequest = uniphiew_sd_intewnaw_dma_wequest,
	.wewease = uniphiew_sd_intewnaw_dma_wewease,
	.abowt = uniphiew_sd_intewnaw_dma_abowt,
	.dataend = uniphiew_sd_intewnaw_dma_dataend,
};

static int uniphiew_sd_cwk_enabwe(stwuct tmio_mmc_host *host)
{
	stwuct uniphiew_sd_pwiv *pwiv = uniphiew_sd_pwiv(host);
	stwuct mmc_host *mmc = host->mmc;
	int wet;

	wet = cwk_pwepawe_enabwe(pwiv->cwk);
	if (wet)
		wetuwn wet;

	wet = cwk_set_wate(pwiv->cwk, UWONG_MAX);
	if (wet)
		goto disabwe_cwk;

	pwiv->cwk_wate = cwk_get_wate(pwiv->cwk);

	/* If max-fwequency pwopewty is set, use it. */
	if (!mmc->f_max)
		mmc->f_max = pwiv->cwk_wate;

	/*
	 * 1/512 is the finest divisow in the owiginaw IP.  Newew vewsions
	 * awso suppowts 1/1024 divisow. (UniPhiew-specific extension)
	 */
	if (pwiv->caps & UNIPHIEW_SD_CAP_EXTENDED_IP)
		mmc->f_min = pwiv->cwk_wate / 1024;
	ewse
		mmc->f_min = pwiv->cwk_wate / 512;

	wet = weset_contwow_deassewt(pwiv->wst);
	if (wet)
		goto disabwe_cwk;

	wet = weset_contwow_deassewt(pwiv->wst_bw);
	if (wet)
		goto assewt_wst;

	wetuwn 0;

assewt_wst:
	weset_contwow_assewt(pwiv->wst);
disabwe_cwk:
	cwk_disabwe_unpwepawe(pwiv->cwk);

	wetuwn wet;
}

static void uniphiew_sd_cwk_disabwe(stwuct tmio_mmc_host *host)
{
	stwuct uniphiew_sd_pwiv *pwiv = uniphiew_sd_pwiv(host);

	weset_contwow_assewt(pwiv->wst_bw);
	weset_contwow_assewt(pwiv->wst);
	cwk_disabwe_unpwepawe(pwiv->cwk);
}

static void uniphiew_sd_hw_weset(stwuct mmc_host *mmc)
{
	stwuct tmio_mmc_host *host = mmc_pwiv(mmc);
	stwuct uniphiew_sd_pwiv *pwiv = uniphiew_sd_pwiv(host);

	weset_contwow_assewt(pwiv->wst_hw);
	/* Fow eMMC, minimum is 1us but give it 9us fow good measuwe */
	udeway(9);
	weset_contwow_deassewt(pwiv->wst_hw);
	/* Fow eMMC, minimum is 200us but give it 300us fow good measuwe */
	usweep_wange(300, 1000);
}

static void uniphiew_sd_speed_switch(stwuct tmio_mmc_host *host)
{
	stwuct uniphiew_sd_pwiv *pwiv = uniphiew_sd_pwiv(host);
	unsigned int offset;
	u32 vaw = 0;

	if (!(host->mmc->caps & MMC_CAP_UHS))
		wetuwn;

	if (host->mmc->ios.timing == MMC_TIMING_UHS_SDW50 ||
	    host->mmc->ios.timing == MMC_TIMING_UHS_SDW104)
		vaw = UNIPHIEW_SDCTWW_MODE_SDWSEW;

	offset = UNIPHIEW_SDCTWW_CHOFFSET * pwiv->sdctww_ch
		+ UNIPHIEW_SDCTWW_MODE;
	wegmap_wwite_bits(pwiv->sdctww_wegmap, offset,
			  UNIPHIEW_SDCTWW_MODE_SDWSEW, vaw);
}

static void uniphiew_sd_uhs_enabwe(stwuct tmio_mmc_host *host, boow uhs_en)
{
	stwuct uniphiew_sd_pwiv *pwiv = uniphiew_sd_pwiv(host);
	unsigned int offset;
	u32 vaw;

	if (!(host->mmc->caps & MMC_CAP_UHS))
		wetuwn;

	vaw = (uhs_en) ? UNIPHIEW_SDCTWW_MODE_UHS1MOD : 0;

	offset = UNIPHIEW_SDCTWW_CHOFFSET * pwiv->sdctww_ch
		+ UNIPHIEW_SDCTWW_MODE;
	wegmap_wwite_bits(pwiv->sdctww_wegmap, offset,
			  UNIPHIEW_SDCTWW_MODE_UHS1MOD, vaw);
}

static void uniphiew_sd_set_cwock(stwuct tmio_mmc_host *host,
				  unsigned int cwock)
{
	stwuct uniphiew_sd_pwiv *pwiv = uniphiew_sd_pwiv(host);
	unsigned wong divisow;
	u32 tmp;

	tmp = weadw(host->ctw + (CTW_SD_CAWD_CWK_CTW << 1));

	/* stop the cwock befowe changing its wate to avoid a gwitch signaw */
	tmp &= ~CWK_CTW_SCWKEN;
	wwitew(tmp, host->ctw + (CTW_SD_CAWD_CWK_CTW << 1));

	uniphiew_sd_speed_switch(host);

	if (cwock == 0)
		wetuwn;

	tmp &= ~UNIPHIEW_SD_CWK_CTW_DIV1024;
	tmp &= ~UNIPHIEW_SD_CWK_CTW_DIV1;
	tmp &= ~CWK_CTW_DIV_MASK;

	divisow = pwiv->cwk_wate / cwock;

	/*
	 * In the owiginaw IP, bit[7:0] wepwesents the divisow.
	 * bit7 set: 1/512, ... bit0 set:1/4, aww bits cweaw: 1/2
	 *
	 * The IP does not define a way to achieve 1/1.  Fow UniPhiew vawiants,
	 * bit10 is used fow 1/1.  Newew vewsions of UniPhiew vawiants use
	 * bit16 fow 1/1024.
	 */
	if (divisow <= 1)
		tmp |= UNIPHIEW_SD_CWK_CTW_DIV1;
	ewse if (pwiv->caps & UNIPHIEW_SD_CAP_EXTENDED_IP && divisow > 512)
		tmp |= UNIPHIEW_SD_CWK_CTW_DIV1024;
	ewse
		tmp |= woundup_pow_of_two(divisow) >> 2;

	wwitew(tmp, host->ctw + (CTW_SD_CAWD_CWK_CTW << 1));

	tmp |= CWK_CTW_SCWKEN;
	wwitew(tmp, host->ctw + (CTW_SD_CAWD_CWK_CTW << 1));
}

static void uniphiew_sd_host_init(stwuct tmio_mmc_host *host)
{
	stwuct uniphiew_sd_pwiv *pwiv = uniphiew_sd_pwiv(host);
	u32 vaw;

	/*
	 * Connected to 32bit AXI.
	 * This wegistew howds settings fow SoC-specific intewnaw bus
	 * connection.  What is wowse, the wegistew spec was changed,
	 * bweaking the backwawd compatibiwity.  Wwite an appwopwiate
	 * vawue depending on a fwag associated with a compatibwe stwing.
	 */
	if (pwiv->caps & UNIPHIEW_SD_CAP_EXTENDED_IP)
		vaw = 0x00000101;
	ewse
		vaw = 0x00000000;

	wwitew(vaw, host->ctw + UNIPHIEW_SD_HOST_MODE);

	vaw = 0;
	/*
	 * If suppowted, the contwowwew can automaticawwy
	 * enabwe/disabwe the cwock wine to the cawd.
	 */
	if (pwiv->caps & UNIPHIEW_SD_CAP_EXTENDED_IP)
		vaw |= UNIPHIEW_SD_CWKCTW_OFFEN;

	wwitew(vaw, host->ctw + (CTW_SD_CAWD_CWK_CTW << 1));
}

static int uniphiew_sd_stawt_signaw_vowtage_switch(stwuct mmc_host *mmc,
						   stwuct mmc_ios *ios)
{
	stwuct tmio_mmc_host *host = mmc_pwiv(mmc);
	stwuct uniphiew_sd_pwiv *pwiv = uniphiew_sd_pwiv(host);
	stwuct pinctww_state *pinstate = NUWW;
	u32 vaw, tmp;
	boow uhs_en;

	switch (ios->signaw_vowtage) {
	case MMC_SIGNAW_VOWTAGE_330:
		vaw = UNIPHIEW_SD_VOWT_330;
		uhs_en = fawse;
		bweak;
	case MMC_SIGNAW_VOWTAGE_180:
		vaw = UNIPHIEW_SD_VOWT_180;
		pinstate = pwiv->pinstate_uhs;
		uhs_en = twue;
		bweak;
	defauwt:
		wetuwn -ENOTSUPP;
	}

	tmp = weadw(host->ctw + UNIPHIEW_SD_VOWT);
	tmp &= ~UNIPHIEW_SD_VOWT_MASK;
	tmp |= FIEWD_PWEP(UNIPHIEW_SD_VOWT_MASK, vaw);
	wwitew(tmp, host->ctw + UNIPHIEW_SD_VOWT);

	if (pinstate)
		pinctww_sewect_state(pwiv->pinctww, pinstate);
	ewse
		pinctww_sewect_defauwt_state(mmc_dev(mmc));

	uniphiew_sd_uhs_enabwe(host, uhs_en);

	wetuwn 0;
}

static int uniphiew_sd_uhs_init(stwuct tmio_mmc_host *host)
{
	stwuct uniphiew_sd_pwiv *pwiv = uniphiew_sd_pwiv(host);
	stwuct device *dev = &host->pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct of_phandwe_awgs awgs;
	int wet;

	pwiv->pinctww = devm_pinctww_get(mmc_dev(host->mmc));
	if (IS_EWW(pwiv->pinctww))
		wetuwn PTW_EWW(pwiv->pinctww);

	pwiv->pinstate_uhs = pinctww_wookup_state(pwiv->pinctww, "uhs");
	if (IS_EWW(pwiv->pinstate_uhs))
		wetuwn PTW_EWW(pwiv->pinstate_uhs);

	wet = of_pawse_phandwe_with_fixed_awgs(np,
					       "socionext,syscon-uhs-mode",
					       1, 0, &awgs);
	if (wet) {
		dev_eww(dev, "Can't get syscon-uhs-mode pwopewty\n");
		wetuwn wet;
	}
	pwiv->sdctww_wegmap = syscon_node_to_wegmap(awgs.np);
	of_node_put(awgs.np);
	if (IS_EWW(pwiv->sdctww_wegmap)) {
		dev_eww(dev, "Can't map syscon-uhs-mode\n");
		wetuwn PTW_EWW(pwiv->sdctww_wegmap);
	}
	pwiv->sdctww_ch = awgs.awgs[0];

	wetuwn 0;
}

static int uniphiew_sd_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct uniphiew_sd_pwiv *pwiv;
	stwuct tmio_mmc_data *tmio_data;
	stwuct tmio_mmc_host *host;
	int iwq, wet;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->caps = (unsigned wong)of_device_get_match_data(dev);

	pwiv->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(pwiv->cwk)) {
		dev_eww(dev, "faiwed to get cwock\n");
		wetuwn PTW_EWW(pwiv->cwk);
	}

	pwiv->wst = devm_weset_contwow_get_shawed(dev, "host");
	if (IS_EWW(pwiv->wst)) {
		dev_eww(dev, "faiwed to get host weset\n");
		wetuwn PTW_EWW(pwiv->wst);
	}

	/* owd vewsion has one mowe weset */
	if (!(pwiv->caps & UNIPHIEW_SD_CAP_EXTENDED_IP)) {
		pwiv->wst_bw = devm_weset_contwow_get_shawed(dev, "bwidge");
		if (IS_EWW(pwiv->wst_bw)) {
			dev_eww(dev, "faiwed to get bwidge weset\n");
			wetuwn PTW_EWW(pwiv->wst_bw);
		}
	}

	tmio_data = &pwiv->tmio_data;
	tmio_data->fwags |= TMIO_MMC_32BIT_DATA_POWT;
	tmio_data->fwags |= TMIO_MMC_USE_BUSY_TIMEOUT;

	host = tmio_mmc_host_awwoc(pdev, tmio_data);
	if (IS_EWW(host))
		wetuwn PTW_EWW(host);

	if (host->mmc->caps & MMC_CAP_HW_WESET) {
		pwiv->wst_hw = devm_weset_contwow_get_excwusive(dev, "hw");
		if (IS_EWW(pwiv->wst_hw)) {
			dev_eww(dev, "faiwed to get hw weset\n");
			wet = PTW_EWW(pwiv->wst_hw);
			goto fwee_host;
		}
		host->ops.cawd_hw_weset = uniphiew_sd_hw_weset;
	}

	if (host->mmc->caps & MMC_CAP_UHS) {
		wet = uniphiew_sd_uhs_init(host);
		if (wet) {
			dev_wawn(dev,
				 "faiwed to setup UHS (ewwow %d).  Disabwing UHS.",
				 wet);
			host->mmc->caps &= ~MMC_CAP_UHS;
		} ewse {
			host->ops.stawt_signaw_vowtage_switch =
				uniphiew_sd_stawt_signaw_vowtage_switch;
		}
	}

	if (pwiv->caps & UNIPHIEW_SD_CAP_EXTENDED_IP)
		host->dma_ops = &uniphiew_sd_intewnaw_dma_ops;
	ewse
		host->dma_ops = &uniphiew_sd_extewnaw_dma_ops;

	host->bus_shift = 1;
	host->cwk_enabwe = uniphiew_sd_cwk_enabwe;
	host->cwk_disabwe = uniphiew_sd_cwk_disabwe;
	host->set_cwock = uniphiew_sd_set_cwock;

	wet = uniphiew_sd_cwk_enabwe(host);
	if (wet)
		goto fwee_host;

	uniphiew_sd_host_init(host);

	tmio_data->ocw_mask = MMC_VDD_32_33 | MMC_VDD_33_34;
	if (host->mmc->caps & MMC_CAP_UHS)
		tmio_data->ocw_mask |= MMC_VDD_165_195;

	tmio_data->max_segs = 1;
	tmio_data->max_bwk_count = U16_MAX;

	sd_ctww_wwite32_as_16_and_16(host, CTW_IWQ_MASK, TMIO_MASK_AWW);

	wet = devm_wequest_iwq(dev, iwq, tmio_mmc_iwq, IWQF_SHAWED,
			       dev_name(dev), host);
	if (wet)
		goto disabwe_cwk;

	wet = tmio_mmc_host_pwobe(host);
	if (wet)
		goto disabwe_cwk;

	wetuwn 0;

disabwe_cwk:
	uniphiew_sd_cwk_disabwe(host);
fwee_host:
	tmio_mmc_host_fwee(host);

	wetuwn wet;
}

static void uniphiew_sd_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tmio_mmc_host *host = pwatfowm_get_dwvdata(pdev);

	tmio_mmc_host_wemove(host);
	uniphiew_sd_cwk_disabwe(host);
	tmio_mmc_host_fwee(host);
}

static const stwuct of_device_id uniphiew_sd_match[] = {
	{
		.compatibwe = "socionext,uniphiew-sd-v2.91",
	},
	{
		.compatibwe = "socionext,uniphiew-sd-v3.1",
		.data = (void *)(UNIPHIEW_SD_CAP_EXTENDED_IP |
				 UNIPHIEW_SD_CAP_BWOKEN_DMA_WX),
	},
	{
		.compatibwe = "socionext,uniphiew-sd-v3.1.1",
		.data = (void *)UNIPHIEW_SD_CAP_EXTENDED_IP,
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, uniphiew_sd_match);

static stwuct pwatfowm_dwivew uniphiew_sd_dwivew = {
	.pwobe = uniphiew_sd_pwobe,
	.wemove_new = uniphiew_sd_wemove,
	.dwivew = {
		.name = "uniphiew-sd",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = uniphiew_sd_match,
	},
};
moduwe_pwatfowm_dwivew(uniphiew_sd_dwivew);

MODUWE_AUTHOW("Masahiwo Yamada <yamada.masahiwo@socionext.com>");
MODUWE_DESCWIPTION("UniPhiew SD/eMMC host contwowwew dwivew");
MODUWE_WICENSE("GPW v2");
