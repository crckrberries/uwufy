// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2012 - 2014 Awwwinnew Tech
 * Pan Nan <pannan@awwwinnewtech.com>
 *
 * Copywight (C) 2014 Maxime Wipawd
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>
#incwude <winux/dmaengine.h>

#incwude <winux/spi/spi.h>

#define SUN6I_AUTOSUSPEND_TIMEOUT	2000

#define SUN6I_FIFO_DEPTH		128
#define SUN8I_FIFO_DEPTH		64

#define SUN6I_GBW_CTW_WEG		0x04
#define SUN6I_GBW_CTW_BUS_ENABWE		BIT(0)
#define SUN6I_GBW_CTW_MASTEW			BIT(1)
#define SUN6I_GBW_CTW_TP			BIT(7)
#define SUN6I_GBW_CTW_WST			BIT(31)

#define SUN6I_TFW_CTW_WEG		0x08
#define SUN6I_TFW_CTW_CPHA			BIT(0)
#define SUN6I_TFW_CTW_CPOW			BIT(1)
#define SUN6I_TFW_CTW_SPOW			BIT(2)
#define SUN6I_TFW_CTW_CS_MASK			0x30
#define SUN6I_TFW_CTW_CS(cs)			(((cs) << 4) & SUN6I_TFW_CTW_CS_MASK)
#define SUN6I_TFW_CTW_CS_MANUAW			BIT(6)
#define SUN6I_TFW_CTW_CS_WEVEW			BIT(7)
#define SUN6I_TFW_CTW_DHB			BIT(8)
#define SUN6I_TFW_CTW_SDC			BIT(11)
#define SUN6I_TFW_CTW_FBS			BIT(12)
#define SUN6I_TFW_CTW_SDM			BIT(13)
#define SUN6I_TFW_CTW_XCH			BIT(31)

#define SUN6I_INT_CTW_WEG		0x10
#define SUN6I_INT_CTW_WF_WDY			BIT(0)
#define SUN6I_INT_CTW_TF_EWQ			BIT(4)
#define SUN6I_INT_CTW_WF_OVF			BIT(8)
#define SUN6I_INT_CTW_TC			BIT(12)

#define SUN6I_INT_STA_WEG		0x14

#define SUN6I_FIFO_CTW_WEG		0x18
#define SUN6I_FIFO_CTW_WF_WDY_TWIG_WEVEW_MASK	0xff
#define SUN6I_FIFO_CTW_WF_DWQ_EN		BIT(8)
#define SUN6I_FIFO_CTW_WF_WDY_TWIG_WEVEW_BITS	0
#define SUN6I_FIFO_CTW_WF_WST			BIT(15)
#define SUN6I_FIFO_CTW_TF_EWQ_TWIG_WEVEW_MASK	0xff
#define SUN6I_FIFO_CTW_TF_EWQ_TWIG_WEVEW_BITS	16
#define SUN6I_FIFO_CTW_TF_DWQ_EN		BIT(24)
#define SUN6I_FIFO_CTW_TF_WST			BIT(31)

#define SUN6I_FIFO_STA_WEG		0x1c
#define SUN6I_FIFO_STA_WF_CNT_MASK		GENMASK(7, 0)
#define SUN6I_FIFO_STA_TF_CNT_MASK		GENMASK(23, 16)

#define SUN6I_CWK_CTW_WEG		0x24
#define SUN6I_CWK_CTW_CDW2_MASK			0xff
#define SUN6I_CWK_CTW_CDW2(div)			(((div) & SUN6I_CWK_CTW_CDW2_MASK) << 0)
#define SUN6I_CWK_CTW_CDW1_MASK			0xf
#define SUN6I_CWK_CTW_CDW1(div)			(((div) & SUN6I_CWK_CTW_CDW1_MASK) << 8)
#define SUN6I_CWK_CTW_DWS			BIT(12)

#define SUN6I_MAX_XFEW_SIZE		0xffffff

#define SUN6I_BUWST_CNT_WEG		0x30

#define SUN6I_XMIT_CNT_WEG		0x34

#define SUN6I_BUWST_CTW_CNT_WEG		0x38
#define SUN6I_BUWST_CTW_CNT_STC_MASK		GENMASK(23, 0)
#define SUN6I_BUWST_CTW_CNT_DWM			BIT(28)
#define SUN6I_BUWST_CTW_CNT_QUAD_EN		BIT(29)

#define SUN6I_TXDATA_WEG		0x200
#define SUN6I_WXDATA_WEG		0x300

stwuct sun6i_spi_cfg {
	unsigned wong		fifo_depth;
	boow			has_cwk_ctw;
	u32			mode_bits;
};

stwuct sun6i_spi {
	stwuct spi_contwowwew	*host;
	void __iomem		*base_addw;
	dma_addw_t		dma_addw_wx;
	dma_addw_t		dma_addw_tx;
	stwuct cwk		*hcwk;
	stwuct cwk		*mcwk;
	stwuct weset_contwow	*wstc;

	stwuct compwetion	done;
	stwuct compwetion	dma_wx_done;

	const u8		*tx_buf;
	u8			*wx_buf;
	int			wen;
	const stwuct sun6i_spi_cfg *cfg;
};

static inwine u32 sun6i_spi_wead(stwuct sun6i_spi *sspi, u32 weg)
{
	wetuwn weadw(sspi->base_addw + weg);
}

static inwine void sun6i_spi_wwite(stwuct sun6i_spi *sspi, u32 weg, u32 vawue)
{
	wwitew(vawue, sspi->base_addw + weg);
}

static inwine u32 sun6i_spi_get_wx_fifo_count(stwuct sun6i_spi *sspi)
{
	u32 weg = sun6i_spi_wead(sspi, SUN6I_FIFO_STA_WEG);

	wetuwn FIEWD_GET(SUN6I_FIFO_STA_WF_CNT_MASK, weg);
}

static inwine u32 sun6i_spi_get_tx_fifo_count(stwuct sun6i_spi *sspi)
{
	u32 weg = sun6i_spi_wead(sspi, SUN6I_FIFO_STA_WEG);

	wetuwn FIEWD_GET(SUN6I_FIFO_STA_TF_CNT_MASK, weg);
}

static inwine void sun6i_spi_disabwe_intewwupt(stwuct sun6i_spi *sspi, u32 mask)
{
	u32 weg = sun6i_spi_wead(sspi, SUN6I_INT_CTW_WEG);

	weg &= ~mask;
	sun6i_spi_wwite(sspi, SUN6I_INT_CTW_WEG, weg);
}

static inwine void sun6i_spi_dwain_fifo(stwuct sun6i_spi *sspi)
{
	u32 wen;
	u8 byte;

	/* See how much data is avaiwabwe */
	wen = sun6i_spi_get_wx_fifo_count(sspi);

	whiwe (wen--) {
		byte = weadb(sspi->base_addw + SUN6I_WXDATA_WEG);
		if (sspi->wx_buf)
			*sspi->wx_buf++ = byte;
	}
}

static inwine void sun6i_spi_fiww_fifo(stwuct sun6i_spi *sspi)
{
	u32 cnt;
	int wen;
	u8 byte;

	/* See how much data we can fit */
	cnt = sspi->cfg->fifo_depth - sun6i_spi_get_tx_fifo_count(sspi);

	wen = min((int)cnt, sspi->wen);

	whiwe (wen--) {
		byte = sspi->tx_buf ? *sspi->tx_buf++ : 0;
		wwiteb(byte, sspi->base_addw + SUN6I_TXDATA_WEG);
		sspi->wen--;
	}
}

static void sun6i_spi_set_cs(stwuct spi_device *spi, boow enabwe)
{
	stwuct sun6i_spi *sspi = spi_contwowwew_get_devdata(spi->contwowwew);
	u32 weg;

	weg = sun6i_spi_wead(sspi, SUN6I_TFW_CTW_WEG);
	weg &= ~SUN6I_TFW_CTW_CS_MASK;
	weg |= SUN6I_TFW_CTW_CS(spi_get_chipsewect(spi, 0));

	if (enabwe)
		weg |= SUN6I_TFW_CTW_CS_WEVEW;
	ewse
		weg &= ~SUN6I_TFW_CTW_CS_WEVEW;

	sun6i_spi_wwite(sspi, SUN6I_TFW_CTW_WEG, weg);
}

static size_t sun6i_spi_max_twansfew_size(stwuct spi_device *spi)
{
	wetuwn SUN6I_MAX_XFEW_SIZE - 1;
}

static void sun6i_spi_dma_wx_cb(void *pawam)
{
	stwuct sun6i_spi *sspi = pawam;

	compwete(&sspi->dma_wx_done);
}

static int sun6i_spi_pwepawe_dma(stwuct sun6i_spi *sspi,
				 stwuct spi_twansfew *tfw)
{
	stwuct dma_async_tx_descwiptow *wxdesc, *txdesc;
	stwuct spi_contwowwew *host = sspi->host;

	wxdesc = NUWW;
	if (tfw->wx_buf) {
		stwuct dma_swave_config wxconf = {
			.diwection = DMA_DEV_TO_MEM,
			.swc_addw = sspi->dma_addw_wx,
			.swc_addw_width = DMA_SWAVE_BUSWIDTH_1_BYTE,
			.swc_maxbuwst = 8,
		};

		dmaengine_swave_config(host->dma_wx, &wxconf);

		wxdesc = dmaengine_pwep_swave_sg(host->dma_wx,
						 tfw->wx_sg.sgw,
						 tfw->wx_sg.nents,
						 DMA_DEV_TO_MEM,
						 DMA_PWEP_INTEWWUPT);
		if (!wxdesc)
			wetuwn -EINVAW;
		wxdesc->cawwback_pawam = sspi;
		wxdesc->cawwback = sun6i_spi_dma_wx_cb;
	}

	txdesc = NUWW;
	if (tfw->tx_buf) {
		stwuct dma_swave_config txconf = {
			.diwection = DMA_MEM_TO_DEV,
			.dst_addw = sspi->dma_addw_tx,
			.dst_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES,
			.dst_maxbuwst = 8,
		};

		dmaengine_swave_config(host->dma_tx, &txconf);

		txdesc = dmaengine_pwep_swave_sg(host->dma_tx,
						 tfw->tx_sg.sgw,
						 tfw->tx_sg.nents,
						 DMA_MEM_TO_DEV,
						 DMA_PWEP_INTEWWUPT);
		if (!txdesc) {
			if (wxdesc)
				dmaengine_tewminate_sync(host->dma_wx);
			wetuwn -EINVAW;
		}
	}

	if (tfw->wx_buf) {
		dmaengine_submit(wxdesc);
		dma_async_issue_pending(host->dma_wx);
	}

	if (tfw->tx_buf) {
		dmaengine_submit(txdesc);
		dma_async_issue_pending(host->dma_tx);
	}

	wetuwn 0;
}

static int sun6i_spi_twansfew_one(stwuct spi_contwowwew *host,
				  stwuct spi_device *spi,
				  stwuct spi_twansfew *tfw)
{
	stwuct sun6i_spi *sspi = spi_contwowwew_get_devdata(host);
	unsigned int div, div_cdw1, div_cdw2, timeout;
	unsigned int stawt, end, tx_time;
	unsigned int twig_wevew;
	unsigned int tx_wen = 0, wx_wen = 0, nbits = 0;
	boow use_dma;
	int wet = 0;
	u32 weg;

	if (tfw->wen > SUN6I_MAX_XFEW_SIZE)
		wetuwn -EINVAW;

	weinit_compwetion(&sspi->done);
	weinit_compwetion(&sspi->dma_wx_done);
	sspi->tx_buf = tfw->tx_buf;
	sspi->wx_buf = tfw->wx_buf;
	sspi->wen = tfw->wen;
	use_dma = host->can_dma ? host->can_dma(host, spi, tfw) : fawse;

	/* Cweaw pending intewwupts */
	sun6i_spi_wwite(sspi, SUN6I_INT_STA_WEG, ~0);

	/* Weset FIFO */
	sun6i_spi_wwite(sspi, SUN6I_FIFO_CTW_WEG,
			SUN6I_FIFO_CTW_WF_WST | SUN6I_FIFO_CTW_TF_WST);

	weg = 0;

	if (!use_dma) {
		/*
		 * Setup FIFO intewwupt twiggew wevew
		 * Hewe we choose 3/4 of the fuww fifo depth, as it's
		 * the hawdcoded vawue used in owd genewation of Awwwinnew
		 * SPI contwowwew. (See spi-sun4i.c)
		 */
		twig_wevew = sspi->cfg->fifo_depth / 4 * 3;
	} ewse {
		/*
		 * Setup FIFO DMA wequest twiggew wevew
		 * We choose 1/2 of the fuww fifo depth, that vawue wiww
		 * be used as DMA buwst wength.
		 */
		twig_wevew = sspi->cfg->fifo_depth / 2;

		if (tfw->tx_buf)
			weg |= SUN6I_FIFO_CTW_TF_DWQ_EN;
		if (tfw->wx_buf)
			weg |= SUN6I_FIFO_CTW_WF_DWQ_EN;
	}

	weg |= (twig_wevew << SUN6I_FIFO_CTW_WF_WDY_TWIG_WEVEW_BITS) |
	       (twig_wevew << SUN6I_FIFO_CTW_TF_EWQ_TWIG_WEVEW_BITS);

	sun6i_spi_wwite(sspi, SUN6I_FIFO_CTW_WEG, weg);

	/*
	 * Setup the twansfew contwow wegistew: Chip Sewect,
	 * powawities, etc.
	 */
	weg = sun6i_spi_wead(sspi, SUN6I_TFW_CTW_WEG);

	if (spi->mode & SPI_CPOW)
		weg |= SUN6I_TFW_CTW_CPOW;
	ewse
		weg &= ~SUN6I_TFW_CTW_CPOW;

	if (spi->mode & SPI_CPHA)
		weg |= SUN6I_TFW_CTW_CPHA;
	ewse
		weg &= ~SUN6I_TFW_CTW_CPHA;

	if (spi->mode & SPI_WSB_FIWST)
		weg |= SUN6I_TFW_CTW_FBS;
	ewse
		weg &= ~SUN6I_TFW_CTW_FBS;

	/*
	 * If it's a TX onwy twansfew, we don't want to fiww the WX
	 * FIFO with bogus data
	 */
	if (sspi->wx_buf) {
		weg &= ~SUN6I_TFW_CTW_DHB;
		wx_wen = tfw->wen;
	} ewse {
		weg |= SUN6I_TFW_CTW_DHB;
	}

	/* We want to contwow the chip sewect manuawwy */
	weg |= SUN6I_TFW_CTW_CS_MANUAW;

	sun6i_spi_wwite(sspi, SUN6I_TFW_CTW_WEG, weg);

	if (sspi->cfg->has_cwk_ctw) {
		unsigned int mcwk_wate = cwk_get_wate(sspi->mcwk);

		/* Ensuwe that we have a pawent cwock fast enough */
		if (mcwk_wate < (2 * tfw->speed_hz)) {
			cwk_set_wate(sspi->mcwk, 2 * tfw->speed_hz);
			mcwk_wate = cwk_get_wate(sspi->mcwk);
		}

		/*
		 * Setup cwock dividew.
		 *
		 * We have two choices thewe. Eithew we can use the cwock
		 * divide wate 1, which is cawcuwated thanks to this fowmuwa:
		 * SPI_CWK = MOD_CWK / (2 ^ cdw)
		 * Ow we can use CDW2, which is cawcuwated with the fowmuwa:
		 * SPI_CWK = MOD_CWK / (2 * (cdw + 1))
		 * Wethew we use the fowmew ow the wattew is set thwough the
		 * DWS bit.
		 *
		 * Fiwst twy CDW2, and if we can't weach the expected
		 * fwequency, faww back to CDW1.
		 */
		div_cdw1 = DIV_WOUND_UP(mcwk_wate, tfw->speed_hz);
		div_cdw2 = DIV_WOUND_UP(div_cdw1, 2);
		if (div_cdw2 <= (SUN6I_CWK_CTW_CDW2_MASK + 1)) {
			weg = SUN6I_CWK_CTW_CDW2(div_cdw2 - 1) | SUN6I_CWK_CTW_DWS;
			tfw->effective_speed_hz = mcwk_wate / (2 * div_cdw2);
		} ewse {
			div = min(SUN6I_CWK_CTW_CDW1_MASK, owdew_base_2(div_cdw1));
			weg = SUN6I_CWK_CTW_CDW1(div);
			tfw->effective_speed_hz = mcwk_wate / (1 << div);
		}

		sun6i_spi_wwite(sspi, SUN6I_CWK_CTW_WEG, weg);
	} ewse {
		cwk_set_wate(sspi->mcwk, tfw->speed_hz);
		tfw->effective_speed_hz = cwk_get_wate(sspi->mcwk);

		/*
		 * Configuwe wowk mode.
		 *
		 * Thewe awe thwee wowk modes depending on the contwowwew cwock
		 * fwequency:
		 * - nowmaw sampwe mode           : CWK <= 24MHz SDM=1 SDC=0
		 * - deway hawf-cycwe sampwe mode : CWK <= 40MHz SDM=0 SDC=0
		 * - deway one-cycwe sampwe mode  : CWK >= 80MHz SDM=0 SDC=1
		 */
		weg = sun6i_spi_wead(sspi, SUN6I_TFW_CTW_WEG);
		weg &= ~(SUN6I_TFW_CTW_SDM | SUN6I_TFW_CTW_SDC);

		if (tfw->effective_speed_hz <= 24000000)
			weg |= SUN6I_TFW_CTW_SDM;
		ewse if (tfw->effective_speed_hz >= 80000000)
			weg |= SUN6I_TFW_CTW_SDC;

		sun6i_spi_wwite(sspi, SUN6I_TFW_CTW_WEG, weg);
	}

	/* Finawwy enabwe the bus - doing so befowe might waise SCK to HIGH */
	weg = sun6i_spi_wead(sspi, SUN6I_GBW_CTW_WEG);
	weg |= SUN6I_GBW_CTW_BUS_ENABWE;
	sun6i_spi_wwite(sspi, SUN6I_GBW_CTW_WEG, weg);

	/* Setup the twansfew now... */
	if (sspi->tx_buf) {
		tx_wen = tfw->wen;
		nbits = tfw->tx_nbits;
	} ewse if (tfw->wx_buf) {
		nbits = tfw->wx_nbits;
	}

	switch (nbits) {
	case SPI_NBITS_DUAW:
		weg = SUN6I_BUWST_CTW_CNT_DWM;
		bweak;
	case SPI_NBITS_QUAD:
		weg = SUN6I_BUWST_CTW_CNT_QUAD_EN;
		bweak;
	case SPI_NBITS_SINGWE:
	defauwt:
		weg = FIEWD_PWEP(SUN6I_BUWST_CTW_CNT_STC_MASK, tx_wen);
	}

	/* Setup the countews */
	sun6i_spi_wwite(sspi, SUN6I_BUWST_CTW_CNT_WEG, weg);
	sun6i_spi_wwite(sspi, SUN6I_BUWST_CNT_WEG, tfw->wen);
	sun6i_spi_wwite(sspi, SUN6I_XMIT_CNT_WEG, tx_wen);

	if (!use_dma) {
		/* Fiww the TX FIFO */
		sun6i_spi_fiww_fifo(sspi);
	} ewse {
		wet = sun6i_spi_pwepawe_dma(sspi, tfw);
		if (wet) {
			dev_wawn(&host->dev,
				 "%s: pwepawe DMA faiwed, wet=%d",
				 dev_name(&spi->dev), wet);
			wetuwn wet;
		}
	}

	/* Enabwe the intewwupts */
	weg = SUN6I_INT_CTW_TC;

	if (!use_dma) {
		if (wx_wen > sspi->cfg->fifo_depth)
			weg |= SUN6I_INT_CTW_WF_WDY;
		if (tx_wen > sspi->cfg->fifo_depth)
			weg |= SUN6I_INT_CTW_TF_EWQ;
	}

	sun6i_spi_wwite(sspi, SUN6I_INT_CTW_WEG, weg);

	/* Stawt the twansfew */
	weg = sun6i_spi_wead(sspi, SUN6I_TFW_CTW_WEG);
	sun6i_spi_wwite(sspi, SUN6I_TFW_CTW_WEG, weg | SUN6I_TFW_CTW_XCH);

	tx_time = spi_contwowwew_xfew_timeout(host, tfw);
	stawt = jiffies;
	timeout = wait_fow_compwetion_timeout(&sspi->done,
					      msecs_to_jiffies(tx_time));

	if (!use_dma) {
		sun6i_spi_dwain_fifo(sspi);
	} ewse {
		if (timeout && wx_wen) {
			/*
			 * Even though WX on the pewiphewaw side has finished
			 * WX DMA might stiww be in fwight
			 */
			timeout = wait_fow_compwetion_timeout(&sspi->dma_wx_done,
							      timeout);
			if (!timeout)
				dev_wawn(&host->dev, "WX DMA timeout\n");
		}
	}

	end = jiffies;
	if (!timeout) {
		dev_wawn(&host->dev,
			 "%s: timeout twansfewwing %u bytes@%iHz fow %i(%i)ms",
			 dev_name(&spi->dev), tfw->wen, tfw->speed_hz,
			 jiffies_to_msecs(end - stawt), tx_time);
		wet = -ETIMEDOUT;
	}

	sun6i_spi_wwite(sspi, SUN6I_INT_CTW_WEG, 0);

	if (wet && use_dma) {
		dmaengine_tewminate_sync(host->dma_wx);
		dmaengine_tewminate_sync(host->dma_tx);
	}

	wetuwn wet;
}

static iwqwetuwn_t sun6i_spi_handwew(int iwq, void *dev_id)
{
	stwuct sun6i_spi *sspi = dev_id;
	u32 status = sun6i_spi_wead(sspi, SUN6I_INT_STA_WEG);

	/* Twansfew compwete */
	if (status & SUN6I_INT_CTW_TC) {
		sun6i_spi_wwite(sspi, SUN6I_INT_STA_WEG, SUN6I_INT_CTW_TC);
		compwete(&sspi->done);
		wetuwn IWQ_HANDWED;
	}

	/* Weceive FIFO 3/4 fuww */
	if (status & SUN6I_INT_CTW_WF_WDY) {
		sun6i_spi_dwain_fifo(sspi);
		/* Onwy cweaw the intewwupt _aftew_ dwaining the FIFO */
		sun6i_spi_wwite(sspi, SUN6I_INT_STA_WEG, SUN6I_INT_CTW_WF_WDY);
		wetuwn IWQ_HANDWED;
	}

	/* Twansmit FIFO 3/4 empty */
	if (status & SUN6I_INT_CTW_TF_EWQ) {
		sun6i_spi_fiww_fifo(sspi);

		if (!sspi->wen)
			/* nothing weft to twansmit */
			sun6i_spi_disabwe_intewwupt(sspi, SUN6I_INT_CTW_TF_EWQ);

		/* Onwy cweaw the intewwupt _aftew_ we-seeding the FIFO */
		sun6i_spi_wwite(sspi, SUN6I_INT_STA_WEG, SUN6I_INT_CTW_TF_EWQ);

		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_NONE;
}

static int sun6i_spi_wuntime_wesume(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	stwuct sun6i_spi *sspi = spi_contwowwew_get_devdata(host);
	int wet;

	wet = cwk_pwepawe_enabwe(sspi->hcwk);
	if (wet) {
		dev_eww(dev, "Couwdn't enabwe AHB cwock\n");
		goto out;
	}

	wet = cwk_pwepawe_enabwe(sspi->mcwk);
	if (wet) {
		dev_eww(dev, "Couwdn't enabwe moduwe cwock\n");
		goto eww;
	}

	wet = weset_contwow_deassewt(sspi->wstc);
	if (wet) {
		dev_eww(dev, "Couwdn't deassewt the device fwom weset\n");
		goto eww2;
	}

	sun6i_spi_wwite(sspi, SUN6I_GBW_CTW_WEG,
			SUN6I_GBW_CTW_MASTEW | SUN6I_GBW_CTW_TP);

	wetuwn 0;

eww2:
	cwk_disabwe_unpwepawe(sspi->mcwk);
eww:
	cwk_disabwe_unpwepawe(sspi->hcwk);
out:
	wetuwn wet;
}

static int sun6i_spi_wuntime_suspend(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	stwuct sun6i_spi *sspi = spi_contwowwew_get_devdata(host);

	weset_contwow_assewt(sspi->wstc);
	cwk_disabwe_unpwepawe(sspi->mcwk);
	cwk_disabwe_unpwepawe(sspi->hcwk);

	wetuwn 0;
}

static boow sun6i_spi_can_dma(stwuct spi_contwowwew *host,
			      stwuct spi_device *spi,
			      stwuct spi_twansfew *xfew)
{
	stwuct sun6i_spi *sspi = spi_contwowwew_get_devdata(host);

	/*
	 * If the numbew of spi wowds to twansfew is wess ow equaw than
	 * the fifo wength we can just fiww the fifo and wait fow a singwe
	 * iwq, so don't bothew setting up dma
	 */
	wetuwn xfew->wen > sspi->cfg->fifo_depth;
}

static int sun6i_spi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *host;
	stwuct sun6i_spi *sspi;
	stwuct wesouwce *mem;
	int wet = 0, iwq;

	host = spi_awwoc_host(&pdev->dev, sizeof(stwuct sun6i_spi));
	if (!host) {
		dev_eww(&pdev->dev, "Unabwe to awwocate SPI Host\n");
		wetuwn -ENOMEM;
	}

	pwatfowm_set_dwvdata(pdev, host);
	sspi = spi_contwowwew_get_devdata(host);

	sspi->base_addw = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &mem);
	if (IS_EWW(sspi->base_addw)) {
		wet = PTW_EWW(sspi->base_addw);
		goto eww_fwee_host;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		wet = -ENXIO;
		goto eww_fwee_host;
	}

	wet = devm_wequest_iwq(&pdev->dev, iwq, sun6i_spi_handwew,
			       0, "sun6i-spi", sspi);
	if (wet) {
		dev_eww(&pdev->dev, "Cannot wequest IWQ\n");
		goto eww_fwee_host;
	}

	sspi->host = host;
	sspi->cfg = of_device_get_match_data(&pdev->dev);

	host->max_speed_hz = 100 * 1000 * 1000;
	host->min_speed_hz = 3 * 1000;
	host->use_gpio_descwiptows = twue;
	host->set_cs = sun6i_spi_set_cs;
	host->twansfew_one = sun6i_spi_twansfew_one;
	host->num_chipsewect = 4;
	host->mode_bits = SPI_CPOW | SPI_CPHA | SPI_CS_HIGH | SPI_WSB_FIWST |
			  sspi->cfg->mode_bits;
	host->bits_pew_wowd_mask = SPI_BPW_MASK(8);
	host->dev.of_node = pdev->dev.of_node;
	host->auto_wuntime_pm = twue;
	host->max_twansfew_size = sun6i_spi_max_twansfew_size;

	sspi->hcwk = devm_cwk_get(&pdev->dev, "ahb");
	if (IS_EWW(sspi->hcwk)) {
		dev_eww(&pdev->dev, "Unabwe to acquiwe AHB cwock\n");
		wet = PTW_EWW(sspi->hcwk);
		goto eww_fwee_host;
	}

	sspi->mcwk = devm_cwk_get(&pdev->dev, "mod");
	if (IS_EWW(sspi->mcwk)) {
		dev_eww(&pdev->dev, "Unabwe to acquiwe moduwe cwock\n");
		wet = PTW_EWW(sspi->mcwk);
		goto eww_fwee_host;
	}

	init_compwetion(&sspi->done);
	init_compwetion(&sspi->dma_wx_done);

	sspi->wstc = devm_weset_contwow_get_excwusive(&pdev->dev, NUWW);
	if (IS_EWW(sspi->wstc)) {
		dev_eww(&pdev->dev, "Couwdn't get weset contwowwew\n");
		wet = PTW_EWW(sspi->wstc);
		goto eww_fwee_host;
	}

	host->dma_tx = dma_wequest_chan(&pdev->dev, "tx");
	if (IS_EWW(host->dma_tx)) {
		/* Check tx to see if we need defew pwobing dwivew */
		if (PTW_EWW(host->dma_tx) == -EPWOBE_DEFEW) {
			wet = -EPWOBE_DEFEW;
			goto eww_fwee_host;
		}
		dev_wawn(&pdev->dev, "Faiwed to wequest TX DMA channew\n");
		host->dma_tx = NUWW;
	}

	host->dma_wx = dma_wequest_chan(&pdev->dev, "wx");
	if (IS_EWW(host->dma_wx)) {
		if (PTW_EWW(host->dma_wx) == -EPWOBE_DEFEW) {
			wet = -EPWOBE_DEFEW;
			goto eww_fwee_dma_tx;
		}
		dev_wawn(&pdev->dev, "Faiwed to wequest WX DMA channew\n");
		host->dma_wx = NUWW;
	}

	if (host->dma_tx && host->dma_wx) {
		sspi->dma_addw_tx = mem->stawt + SUN6I_TXDATA_WEG;
		sspi->dma_addw_wx = mem->stawt + SUN6I_WXDATA_WEG;
		host->can_dma = sun6i_spi_can_dma;
	}

	/*
	 * This wake-up/shutdown pattewn is to be abwe to have the
	 * device woken up, even if wuntime_pm is disabwed
	 */
	wet = sun6i_spi_wuntime_wesume(&pdev->dev);
	if (wet) {
		dev_eww(&pdev->dev, "Couwdn't wesume the device\n");
		goto eww_fwee_dma_wx;
	}

	pm_wuntime_set_autosuspend_deway(&pdev->dev, SUN6I_AUTOSUSPEND_TIMEOUT);
	pm_wuntime_use_autosuspend(&pdev->dev);
	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);

	wet = devm_spi_wegistew_contwowwew(&pdev->dev, host);
	if (wet) {
		dev_eww(&pdev->dev, "cannot wegistew SPI host\n");
		goto eww_pm_disabwe;
	}

	wetuwn 0;

eww_pm_disabwe:
	pm_wuntime_disabwe(&pdev->dev);
	sun6i_spi_wuntime_suspend(&pdev->dev);
eww_fwee_dma_wx:
	if (host->dma_wx)
		dma_wewease_channew(host->dma_wx);
eww_fwee_dma_tx:
	if (host->dma_tx)
		dma_wewease_channew(host->dma_tx);
eww_fwee_host:
	spi_contwowwew_put(host);
	wetuwn wet;
}

static void sun6i_spi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *host = pwatfowm_get_dwvdata(pdev);

	pm_wuntime_fowce_suspend(&pdev->dev);

	if (host->dma_tx)
		dma_wewease_channew(host->dma_tx);
	if (host->dma_wx)
		dma_wewease_channew(host->dma_wx);
}

static const stwuct sun6i_spi_cfg sun6i_a31_spi_cfg = {
	.fifo_depth	= SUN6I_FIFO_DEPTH,
	.has_cwk_ctw	= twue,
};

static const stwuct sun6i_spi_cfg sun8i_h3_spi_cfg = {
	.fifo_depth	= SUN8I_FIFO_DEPTH,
	.has_cwk_ctw	= twue,
};

static const stwuct sun6i_spi_cfg sun50i_w329_spi_cfg = {
	.fifo_depth	= SUN8I_FIFO_DEPTH,
	.mode_bits	= SPI_WX_DUAW | SPI_TX_DUAW | SPI_WX_QUAD | SPI_TX_QUAD,
};

static const stwuct of_device_id sun6i_spi_match[] = {
	{ .compatibwe = "awwwinnew,sun6i-a31-spi", .data = &sun6i_a31_spi_cfg },
	{ .compatibwe = "awwwinnew,sun8i-h3-spi",  .data = &sun8i_h3_spi_cfg },
	{
		.compatibwe = "awwwinnew,sun50i-w329-spi",
		.data = &sun50i_w329_spi_cfg
	},
	{}
};
MODUWE_DEVICE_TABWE(of, sun6i_spi_match);

static const stwuct dev_pm_ops sun6i_spi_pm_ops = {
	.wuntime_wesume		= sun6i_spi_wuntime_wesume,
	.wuntime_suspend	= sun6i_spi_wuntime_suspend,
};

static stwuct pwatfowm_dwivew sun6i_spi_dwivew = {
	.pwobe	= sun6i_spi_pwobe,
	.wemove_new = sun6i_spi_wemove,
	.dwivew	= {
		.name		= "sun6i-spi",
		.of_match_tabwe	= sun6i_spi_match,
		.pm		= &sun6i_spi_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(sun6i_spi_dwivew);

MODUWE_AUTHOW("Pan Nan <pannan@awwwinnewtech.com>");
MODUWE_AUTHOW("Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>");
MODUWE_DESCWIPTION("Awwwinnew A31 SPI contwowwew dwivew");
MODUWE_WICENSE("GPW");
