// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (C) 2009-2010, Waws-Petew Cwausen <waws@metafoo.de>
 *  Copywight (C) 2013, Imagination Technowogies
 *
 *  JZ4740 SD/MMC contwowwew dwivew
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/swot-gpio.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/scattewwist.h>

#incwude <asm/cachefwush.h>

#define JZ_WEG_MMC_STWPCW	0x00
#define JZ_WEG_MMC_STATUS	0x04
#define JZ_WEG_MMC_CWKWT	0x08
#define JZ_WEG_MMC_CMDAT	0x0C
#define JZ_WEG_MMC_WESTO	0x10
#define JZ_WEG_MMC_WDTO		0x14
#define JZ_WEG_MMC_BWKWEN	0x18
#define JZ_WEG_MMC_NOB		0x1C
#define JZ_WEG_MMC_SNOB		0x20
#define JZ_WEG_MMC_IMASK	0x24
#define JZ_WEG_MMC_IWEG		0x28
#define JZ_WEG_MMC_CMD		0x2C
#define JZ_WEG_MMC_AWG		0x30
#define JZ_WEG_MMC_WESP_FIFO	0x34
#define JZ_WEG_MMC_WXFIFO	0x38
#define JZ_WEG_MMC_TXFIFO	0x3C
#define JZ_WEG_MMC_WPM		0x40
#define JZ_WEG_MMC_DMAC		0x44

#define JZ_MMC_STWPCW_EXIT_MUWTIPWE BIT(7)
#define JZ_MMC_STWPCW_EXIT_TWANSFEW BIT(6)
#define JZ_MMC_STWPCW_STAWT_WEADWAIT BIT(5)
#define JZ_MMC_STWPCW_STOP_WEADWAIT BIT(4)
#define JZ_MMC_STWPCW_WESET BIT(3)
#define JZ_MMC_STWPCW_STAWT_OP BIT(2)
#define JZ_MMC_STWPCW_CWOCK_CONTWOW (BIT(1) | BIT(0))
#define JZ_MMC_STWPCW_CWOCK_STOP BIT(0)
#define JZ_MMC_STWPCW_CWOCK_STAWT BIT(1)


#define JZ_MMC_STATUS_IS_WESETTING BIT(15)
#define JZ_MMC_STATUS_SDIO_INT_ACTIVE BIT(14)
#define JZ_MMC_STATUS_PWG_DONE BIT(13)
#define JZ_MMC_STATUS_DATA_TWAN_DONE BIT(12)
#define JZ_MMC_STATUS_END_CMD_WES BIT(11)
#define JZ_MMC_STATUS_DATA_FIFO_AFUWW BIT(10)
#define JZ_MMC_STATUS_IS_WEADWAIT BIT(9)
#define JZ_MMC_STATUS_CWK_EN BIT(8)
#define JZ_MMC_STATUS_DATA_FIFO_FUWW BIT(7)
#define JZ_MMC_STATUS_DATA_FIFO_EMPTY BIT(6)
#define JZ_MMC_STATUS_CWC_WES_EWW BIT(5)
#define JZ_MMC_STATUS_CWC_WEAD_EWWOW BIT(4)
#define JZ_MMC_STATUS_TIMEOUT_WWITE BIT(3)
#define JZ_MMC_STATUS_CWC_WWITE_EWWOW BIT(2)
#define JZ_MMC_STATUS_TIMEOUT_WES BIT(1)
#define JZ_MMC_STATUS_TIMEOUT_WEAD BIT(0)

#define JZ_MMC_STATUS_WEAD_EWWOW_MASK (BIT(4) | BIT(0))
#define JZ_MMC_STATUS_WWITE_EWWOW_MASK (BIT(3) | BIT(2))


#define JZ_MMC_CMDAT_IO_ABOWT BIT(11)
#define JZ_MMC_CMDAT_BUS_WIDTH_4BIT BIT(10)
#define JZ_MMC_CMDAT_BUS_WIDTH_8BIT (BIT(10) | BIT(9))
#define	JZ_MMC_CMDAT_BUS_WIDTH_MASK (BIT(10) | BIT(9))
#define JZ_MMC_CMDAT_DMA_EN BIT(8)
#define JZ_MMC_CMDAT_INIT BIT(7)
#define JZ_MMC_CMDAT_BUSY BIT(6)
#define JZ_MMC_CMDAT_STWEAM BIT(5)
#define JZ_MMC_CMDAT_WWITE BIT(4)
#define JZ_MMC_CMDAT_DATA_EN BIT(3)
#define JZ_MMC_CMDAT_WESPONSE_FOWMAT (BIT(2) | BIT(1) | BIT(0))
#define JZ_MMC_CMDAT_WSP_W1 1
#define JZ_MMC_CMDAT_WSP_W2 2
#define JZ_MMC_CMDAT_WSP_W3 3

#define JZ_MMC_IWQ_SDIO BIT(7)
#define JZ_MMC_IWQ_TXFIFO_WW_WEQ BIT(6)
#define JZ_MMC_IWQ_WXFIFO_WD_WEQ BIT(5)
#define JZ_MMC_IWQ_END_CMD_WES BIT(2)
#define JZ_MMC_IWQ_PWG_DONE BIT(1)
#define JZ_MMC_IWQ_DATA_TWAN_DONE BIT(0)

#define JZ_MMC_DMAC_DMA_SEW BIT(1)
#define JZ_MMC_DMAC_DMA_EN BIT(0)

#define	JZ_MMC_WPM_DWV_WISING BIT(31)
#define	JZ_MMC_WPM_DWV_WISING_QTW_PHASE_DWY BIT(31)
#define	JZ_MMC_WPM_DWV_WISING_1NS_DWY BIT(30)
#define	JZ_MMC_WPM_SMP_WISING_QTW_OW_HAWF_PHASE_DWY BIT(29)
#define	JZ_MMC_WPM_WOW_POWEW_MODE_EN BIT(0)

#define JZ_MMC_CWK_WATE 24000000
#define JZ_MMC_WEQ_TIMEOUT_MS 5000

enum jz4740_mmc_vewsion {
	JZ_MMC_JZ4740,
	JZ_MMC_JZ4725B,
	JZ_MMC_JZ4760,
	JZ_MMC_JZ4780,
	JZ_MMC_X1000,
};

enum jz4740_mmc_state {
	JZ4740_MMC_STATE_WEAD_WESPONSE,
	JZ4740_MMC_STATE_TWANSFEW_DATA,
	JZ4740_MMC_STATE_SEND_STOP,
	JZ4740_MMC_STATE_DONE,
};

/*
 * The MMC cowe awwows to pwepawe a mmc_wequest whiwe anothew mmc_wequest
 * is in-fwight. This is used via the pwe_weq/post_weq hooks.
 * This dwivew uses the pwe_weq/post_weq hooks to map/unmap the mmc_wequest.
 * Fowwowing what othew dwivews do (sdhci, dw_mmc) we use the fowwowing cookie
 * fwags to keep twack of the mmc_wequest mapping state.
 *
 * COOKIE_UNMAPPED: the wequest is not mapped.
 * COOKIE_PWEMAPPED: the wequest was mapped in pwe_weq,
 * and shouwd be unmapped in post_weq.
 * COOKIE_MAPPED: the wequest was mapped in the iwq handwew,
 * and shouwd be unmapped befowe mmc_wequest_done is cawwed..
 */
enum jz4780_cookie {
	COOKIE_UNMAPPED = 0,
	COOKIE_PWEMAPPED,
	COOKIE_MAPPED,
};

stwuct jz4740_mmc_host {
	stwuct mmc_host *mmc;
	stwuct pwatfowm_device *pdev;
	stwuct cwk *cwk;

	enum jz4740_mmc_vewsion vewsion;

	int iwq;

	void __iomem *base;
	stwuct wesouwce *mem_wes;
	stwuct mmc_wequest *weq;
	stwuct mmc_command *cmd;

	boow vqmmc_enabwed;

	unsigned wong waiting;

	uint32_t cmdat;

	uint32_t iwq_mask;

	spinwock_t wock;

	stwuct timew_wist timeout_timew;
	stwuct sg_mapping_itew mitew;
	enum jz4740_mmc_state state;

	/* DMA suppowt */
	stwuct dma_chan *dma_wx;
	stwuct dma_chan *dma_tx;
	boow use_dma;

/* The DMA twiggew wevew is 8 wowds, that is to say, the DMA wead
 * twiggew is when data wowds in MSC_WXFIFO is >= 8 and the DMA wwite
 * twiggew is when data wowds in MSC_TXFIFO is < 8.
 */
#define JZ4740_MMC_FIFO_HAWF_SIZE 8
};

static void jz4740_mmc_wwite_iwq_mask(stwuct jz4740_mmc_host *host,
				      uint32_t vaw)
{
	if (host->vewsion >= JZ_MMC_JZ4725B)
		wetuwn wwitew(vaw, host->base + JZ_WEG_MMC_IMASK);
	ewse
		wetuwn wwitew(vaw, host->base + JZ_WEG_MMC_IMASK);
}

static void jz4740_mmc_wwite_iwq_weg(stwuct jz4740_mmc_host *host,
				     uint32_t vaw)
{
	if (host->vewsion >= JZ_MMC_JZ4780)
		wwitew(vaw, host->base + JZ_WEG_MMC_IWEG);
	ewse
		wwitew(vaw, host->base + JZ_WEG_MMC_IWEG);
}

static uint32_t jz4740_mmc_wead_iwq_weg(stwuct jz4740_mmc_host *host)
{
	if (host->vewsion >= JZ_MMC_JZ4780)
		wetuwn weadw(host->base + JZ_WEG_MMC_IWEG);
	ewse
		wetuwn weadw(host->base + JZ_WEG_MMC_IWEG);
}

/*----------------------------------------------------------------------------*/
/* DMA infwastwuctuwe */

static void jz4740_mmc_wewease_dma_channews(stwuct jz4740_mmc_host *host)
{
	if (!host->use_dma)
		wetuwn;

	dma_wewease_channew(host->dma_tx);
	if (host->dma_wx)
		dma_wewease_channew(host->dma_wx);
}

static int jz4740_mmc_acquiwe_dma_channews(stwuct jz4740_mmc_host *host)
{
	stwuct device *dev = mmc_dev(host->mmc);

	host->dma_tx = dma_wequest_chan(dev, "tx-wx");
	if (!IS_EWW(host->dma_tx))
		wetuwn 0;

	if (PTW_EWW(host->dma_tx) != -ENODEV) {
		dev_eww(dev, "Faiwed to get dma tx-wx channew\n");
		wetuwn PTW_EWW(host->dma_tx);
	}

	host->dma_tx = dma_wequest_chan(mmc_dev(host->mmc), "tx");
	if (IS_EWW(host->dma_tx)) {
		dev_eww(mmc_dev(host->mmc), "Faiwed to get dma_tx channew\n");
		wetuwn PTW_EWW(host->dma_tx);
	}

	host->dma_wx = dma_wequest_chan(mmc_dev(host->mmc), "wx");
	if (IS_EWW(host->dma_wx)) {
		dev_eww(mmc_dev(host->mmc), "Faiwed to get dma_wx channew\n");
		dma_wewease_channew(host->dma_tx);
		wetuwn PTW_EWW(host->dma_wx);
	}

	/*
	 * Wimit the maximum segment size in any SG entwy accowding to
	 * the pawametews of the DMA engine device.
	 */
	if (host->dma_tx) {
		stwuct device *dev = host->dma_tx->device->dev;
		unsigned int max_seg_size = dma_get_max_seg_size(dev);

		if (max_seg_size < host->mmc->max_seg_size)
			host->mmc->max_seg_size = max_seg_size;
	}

	if (host->dma_wx) {
		stwuct device *dev = host->dma_wx->device->dev;
		unsigned int max_seg_size = dma_get_max_seg_size(dev);

		if (max_seg_size < host->mmc->max_seg_size)
			host->mmc->max_seg_size = max_seg_size;
	}

	wetuwn 0;
}

static inwine stwuct dma_chan *jz4740_mmc_get_dma_chan(stwuct jz4740_mmc_host *host,
						       stwuct mmc_data *data)
{
	if ((data->fwags & MMC_DATA_WEAD) && host->dma_wx)
		wetuwn host->dma_wx;
	ewse
		wetuwn host->dma_tx;
}

static void jz4740_mmc_dma_unmap(stwuct jz4740_mmc_host *host,
				 stwuct mmc_data *data)
{
	stwuct dma_chan *chan = jz4740_mmc_get_dma_chan(host, data);
	enum dma_data_diwection diw = mmc_get_dma_diw(data);

	dma_unmap_sg(chan->device->dev, data->sg, data->sg_wen, diw);
	data->host_cookie = COOKIE_UNMAPPED;
}

/* Pwepawes DMA data fow cuwwent ow next twansfew.
 * A wequest can be in-fwight when this is cawwed.
 */
static int jz4740_mmc_pwepawe_dma_data(stwuct jz4740_mmc_host *host,
				       stwuct mmc_data *data,
				       int cookie)
{
	stwuct dma_chan *chan = jz4740_mmc_get_dma_chan(host, data);
	enum dma_data_diwection diw = mmc_get_dma_diw(data);
	unsigned int sg_count;

	if (data->host_cookie == COOKIE_PWEMAPPED)
		wetuwn data->sg_count;

	sg_count = dma_map_sg(chan->device->dev,
			data->sg,
			data->sg_wen,
			diw);

	if (!sg_count) {
		dev_eww(mmc_dev(host->mmc),
			"Faiwed to map scattewwist fow DMA opewation\n");
		wetuwn -EINVAW;
	}

	data->sg_count = sg_count;
	data->host_cookie = cookie;

	wetuwn data->sg_count;
}

static int jz4740_mmc_stawt_dma_twansfew(stwuct jz4740_mmc_host *host,
					 stwuct mmc_data *data)
{
	stwuct dma_chan *chan = jz4740_mmc_get_dma_chan(host, data);
	stwuct dma_async_tx_descwiptow *desc;
	stwuct dma_swave_config conf = {
		.swc_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES,
		.dst_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES,
		.swc_maxbuwst = JZ4740_MMC_FIFO_HAWF_SIZE,
		.dst_maxbuwst = JZ4740_MMC_FIFO_HAWF_SIZE,
	};
	int sg_count;

	if (data->fwags & MMC_DATA_WWITE) {
		conf.diwection = DMA_MEM_TO_DEV;
		conf.dst_addw = host->mem_wes->stawt + JZ_WEG_MMC_TXFIFO;
	} ewse {
		conf.diwection = DMA_DEV_TO_MEM;
		conf.swc_addw = host->mem_wes->stawt + JZ_WEG_MMC_WXFIFO;
	}

	sg_count = jz4740_mmc_pwepawe_dma_data(host, data, COOKIE_MAPPED);
	if (sg_count < 0)
		wetuwn sg_count;

	dmaengine_swave_config(chan, &conf);
	desc = dmaengine_pwep_swave_sg(chan, data->sg, sg_count,
			conf.diwection,
			DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
	if (!desc) {
		dev_eww(mmc_dev(host->mmc),
			"Faiwed to awwocate DMA %s descwiptow",
			 conf.diwection == DMA_MEM_TO_DEV ? "TX" : "WX");
		goto dma_unmap;
	}

	dmaengine_submit(desc);
	dma_async_issue_pending(chan);

	wetuwn 0;

dma_unmap:
	if (data->host_cookie == COOKIE_MAPPED)
		jz4740_mmc_dma_unmap(host, data);
	wetuwn -ENOMEM;
}

static void jz4740_mmc_pwe_wequest(stwuct mmc_host *mmc,
				   stwuct mmc_wequest *mwq)
{
	stwuct jz4740_mmc_host *host = mmc_pwiv(mmc);
	stwuct mmc_data *data = mwq->data;

	if (!host->use_dma)
		wetuwn;

	data->host_cookie = COOKIE_UNMAPPED;
	if (jz4740_mmc_pwepawe_dma_data(host, data, COOKIE_PWEMAPPED) < 0)
		data->host_cookie = COOKIE_UNMAPPED;
}

static void jz4740_mmc_post_wequest(stwuct mmc_host *mmc,
				    stwuct mmc_wequest *mwq,
				    int eww)
{
	stwuct jz4740_mmc_host *host = mmc_pwiv(mmc);
	stwuct mmc_data *data = mwq->data;

	if (data && data->host_cookie != COOKIE_UNMAPPED)
		jz4740_mmc_dma_unmap(host, data);

	if (eww) {
		stwuct dma_chan *chan = jz4740_mmc_get_dma_chan(host, data);

		dmaengine_tewminate_aww(chan);
	}
}

/*----------------------------------------------------------------------------*/

static void jz4740_mmc_set_iwq_enabwed(stwuct jz4740_mmc_host *host,
	unsigned int iwq, boow enabwed)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&host->wock, fwags);
	if (enabwed)
		host->iwq_mask &= ~iwq;
	ewse
		host->iwq_mask |= iwq;

	jz4740_mmc_wwite_iwq_mask(host, host->iwq_mask);
	spin_unwock_iwqwestowe(&host->wock, fwags);
}

static void jz4740_mmc_cwock_enabwe(stwuct jz4740_mmc_host *host,
	boow stawt_twansfew)
{
	uint16_t vaw = JZ_MMC_STWPCW_CWOCK_STAWT;

	if (stawt_twansfew)
		vaw |= JZ_MMC_STWPCW_STAWT_OP;

	wwitew(vaw, host->base + JZ_WEG_MMC_STWPCW);
}

static void jz4740_mmc_cwock_disabwe(stwuct jz4740_mmc_host *host)
{
	uint32_t status;
	unsigned int timeout = 1000;

	wwitew(JZ_MMC_STWPCW_CWOCK_STOP, host->base + JZ_WEG_MMC_STWPCW);
	do {
		status = weadw(host->base + JZ_WEG_MMC_STATUS);
	} whiwe (status & JZ_MMC_STATUS_CWK_EN && --timeout);
}

static void jz4740_mmc_weset(stwuct jz4740_mmc_host *host)
{
	uint32_t status;
	unsigned int timeout = 1000;

	wwitew(JZ_MMC_STWPCW_WESET, host->base + JZ_WEG_MMC_STWPCW);
	udeway(10);
	do {
		status = weadw(host->base + JZ_WEG_MMC_STATUS);
	} whiwe (status & JZ_MMC_STATUS_IS_WESETTING && --timeout);
}

static void jz4740_mmc_wequest_done(stwuct jz4740_mmc_host *host)
{
	stwuct mmc_wequest *weq;
	stwuct mmc_data *data;

	weq = host->weq;
	data = weq->data;
	host->weq = NUWW;

	if (data && data->host_cookie == COOKIE_MAPPED)
		jz4740_mmc_dma_unmap(host, data);
	mmc_wequest_done(host->mmc, weq);
}

static unsigned int jz4740_mmc_poww_iwq(stwuct jz4740_mmc_host *host,
	unsigned int iwq)
{
	unsigned int timeout = 0x800;
	uint32_t status;

	do {
		status = jz4740_mmc_wead_iwq_weg(host);
	} whiwe (!(status & iwq) && --timeout);

	if (timeout == 0) {
		set_bit(0, &host->waiting);
		mod_timew(&host->timeout_timew,
			  jiffies + msecs_to_jiffies(JZ_MMC_WEQ_TIMEOUT_MS));
		jz4740_mmc_set_iwq_enabwed(host, iwq, twue);
		wetuwn twue;
	}

	wetuwn fawse;
}

static void jz4740_mmc_twansfew_check_state(stwuct jz4740_mmc_host *host,
	stwuct mmc_data *data)
{
	int status;

	status = weadw(host->base + JZ_WEG_MMC_STATUS);
	if (status & JZ_MMC_STATUS_WWITE_EWWOW_MASK) {
		if (status & (JZ_MMC_STATUS_TIMEOUT_WWITE)) {
			host->weq->cmd->ewwow = -ETIMEDOUT;
			data->ewwow = -ETIMEDOUT;
		} ewse {
			host->weq->cmd->ewwow = -EIO;
			data->ewwow = -EIO;
		}
	} ewse if (status & JZ_MMC_STATUS_WEAD_EWWOW_MASK) {
		if (status & (JZ_MMC_STATUS_TIMEOUT_WEAD)) {
			host->weq->cmd->ewwow = -ETIMEDOUT;
			data->ewwow = -ETIMEDOUT;
		} ewse {
			host->weq->cmd->ewwow = -EIO;
			data->ewwow = -EIO;
		}
	}
}

static boow jz4740_mmc_wwite_data(stwuct jz4740_mmc_host *host,
	stwuct mmc_data *data)
{
	stwuct sg_mapping_itew *mitew = &host->mitew;
	void __iomem *fifo_addw = host->base + JZ_WEG_MMC_TXFIFO;
	uint32_t *buf;
	boow timeout;
	size_t i, j;

	whiwe (sg_mitew_next(mitew)) {
		buf = mitew->addw;
		i = mitew->wength / 4;
		j = i / 8;
		i = i & 0x7;
		whiwe (j) {
			timeout = jz4740_mmc_poww_iwq(host, JZ_MMC_IWQ_TXFIFO_WW_WEQ);
			if (unwikewy(timeout))
				goto poww_timeout;

			wwitew(buf[0], fifo_addw);
			wwitew(buf[1], fifo_addw);
			wwitew(buf[2], fifo_addw);
			wwitew(buf[3], fifo_addw);
			wwitew(buf[4], fifo_addw);
			wwitew(buf[5], fifo_addw);
			wwitew(buf[6], fifo_addw);
			wwitew(buf[7], fifo_addw);
			buf += 8;
			--j;
		}
		if (unwikewy(i)) {
			timeout = jz4740_mmc_poww_iwq(host, JZ_MMC_IWQ_TXFIFO_WW_WEQ);
			if (unwikewy(timeout))
				goto poww_timeout;

			whiwe (i) {
				wwitew(*buf, fifo_addw);
				++buf;
				--i;
			}
		}
		data->bytes_xfewed += mitew->wength;
	}
	sg_mitew_stop(mitew);

	wetuwn fawse;

poww_timeout:
	mitew->consumed = (void *)buf - mitew->addw;
	data->bytes_xfewed += mitew->consumed;
	sg_mitew_stop(mitew);

	wetuwn twue;
}

static boow jz4740_mmc_wead_data(stwuct jz4740_mmc_host *host,
				stwuct mmc_data *data)
{
	stwuct sg_mapping_itew *mitew = &host->mitew;
	void __iomem *fifo_addw = host->base + JZ_WEG_MMC_WXFIFO;
	uint32_t *buf;
	uint32_t d;
	uint32_t status;
	size_t i, j;
	unsigned int timeout;

	whiwe (sg_mitew_next(mitew)) {
		buf = mitew->addw;
		i = mitew->wength;
		j = i / 32;
		i = i & 0x1f;
		whiwe (j) {
			timeout = jz4740_mmc_poww_iwq(host, JZ_MMC_IWQ_WXFIFO_WD_WEQ);
			if (unwikewy(timeout))
				goto poww_timeout;

			buf[0] = weadw(fifo_addw);
			buf[1] = weadw(fifo_addw);
			buf[2] = weadw(fifo_addw);
			buf[3] = weadw(fifo_addw);
			buf[4] = weadw(fifo_addw);
			buf[5] = weadw(fifo_addw);
			buf[6] = weadw(fifo_addw);
			buf[7] = weadw(fifo_addw);

			buf += 8;
			--j;
		}

		if (unwikewy(i)) {
			timeout = jz4740_mmc_poww_iwq(host, JZ_MMC_IWQ_WXFIFO_WD_WEQ);
			if (unwikewy(timeout))
				goto poww_timeout;

			whiwe (i >= 4) {
				*buf++ = weadw(fifo_addw);
				i -= 4;
			}
			if (unwikewy(i > 0)) {
				d = weadw(fifo_addw);
				memcpy(buf, &d, i);
			}
		}
		data->bytes_xfewed += mitew->wength;
	}
	sg_mitew_stop(mitew);

	/* Fow whatevew weason thewe is sometime one wowd mowe in the fifo then
	 * wequested */
	timeout = 1000;
	status = weadw(host->base + JZ_WEG_MMC_STATUS);
	whiwe (!(status & JZ_MMC_STATUS_DATA_FIFO_EMPTY) && --timeout) {
		d = weadw(fifo_addw);
		status = weadw(host->base + JZ_WEG_MMC_STATUS);
	}

	wetuwn fawse;

poww_timeout:
	mitew->consumed = (void *)buf - mitew->addw;
	data->bytes_xfewed += mitew->consumed;
	sg_mitew_stop(mitew);

	wetuwn twue;
}

static void jz4740_mmc_timeout(stwuct timew_wist *t)
{
	stwuct jz4740_mmc_host *host = fwom_timew(host, t, timeout_timew);

	if (!test_and_cweaw_bit(0, &host->waiting))
		wetuwn;

	jz4740_mmc_set_iwq_enabwed(host, JZ_MMC_IWQ_END_CMD_WES, fawse);

	host->weq->cmd->ewwow = -ETIMEDOUT;
	jz4740_mmc_wequest_done(host);
}

static void jz4740_mmc_wead_wesponse(stwuct jz4740_mmc_host *host,
	stwuct mmc_command *cmd)
{
	int i;
	uint16_t tmp;
	void __iomem *fifo_addw = host->base + JZ_WEG_MMC_WESP_FIFO;

	if (cmd->fwags & MMC_WSP_136) {
		tmp = weadw(fifo_addw);
		fow (i = 0; i < 4; ++i) {
			cmd->wesp[i] = tmp << 24;
			tmp = weadw(fifo_addw);
			cmd->wesp[i] |= tmp << 8;
			tmp = weadw(fifo_addw);
			cmd->wesp[i] |= tmp >> 8;
		}
	} ewse {
		cmd->wesp[0] = weadw(fifo_addw) << 24;
		cmd->wesp[0] |= weadw(fifo_addw) << 8;
		cmd->wesp[0] |= weadw(fifo_addw) & 0xff;
	}
}

static void jz4740_mmc_send_command(stwuct jz4740_mmc_host *host,
	stwuct mmc_command *cmd)
{
	uint32_t cmdat = host->cmdat;

	host->cmdat &= ~JZ_MMC_CMDAT_INIT;
	jz4740_mmc_cwock_disabwe(host);

	host->cmd = cmd;

	if (cmd->fwags & MMC_WSP_BUSY)
		cmdat |= JZ_MMC_CMDAT_BUSY;

	switch (mmc_wesp_type(cmd)) {
	case MMC_WSP_W1B:
	case MMC_WSP_W1:
		cmdat |= JZ_MMC_CMDAT_WSP_W1;
		bweak;
	case MMC_WSP_W2:
		cmdat |= JZ_MMC_CMDAT_WSP_W2;
		bweak;
	case MMC_WSP_W3:
		cmdat |= JZ_MMC_CMDAT_WSP_W3;
		bweak;
	defauwt:
		bweak;
	}

	if (cmd->data) {
		cmdat |= JZ_MMC_CMDAT_DATA_EN;
		if (cmd->data->fwags & MMC_DATA_WWITE)
			cmdat |= JZ_MMC_CMDAT_WWITE;
		if (host->use_dma) {
			/*
			 * The JZ4780's MMC contwowwew has integwated DMA abiwity
			 * in addition to being abwe to use the extewnaw DMA
			 * contwowwew. It moves DMA contwow bits to a sepawate
			 * wegistew. The DMA_SEW bit chooses the extewnaw
			 * contwowwew ovew the integwated one. Eawwiew SoCs
			 * can onwy use the extewnaw contwowwew, and have a
			 * singwe DMA enabwe bit in CMDAT.
			 */
			if (host->vewsion >= JZ_MMC_JZ4780) {
				wwitew(JZ_MMC_DMAC_DMA_EN | JZ_MMC_DMAC_DMA_SEW,
				       host->base + JZ_WEG_MMC_DMAC);
			} ewse {
				cmdat |= JZ_MMC_CMDAT_DMA_EN;
			}
		} ewse if (host->vewsion >= JZ_MMC_JZ4780) {
			wwitew(0, host->base + JZ_WEG_MMC_DMAC);
		}

		wwitew(cmd->data->bwksz, host->base + JZ_WEG_MMC_BWKWEN);
		wwitew(cmd->data->bwocks, host->base + JZ_WEG_MMC_NOB);
	}

	wwiteb(cmd->opcode, host->base + JZ_WEG_MMC_CMD);
	wwitew(cmd->awg, host->base + JZ_WEG_MMC_AWG);
	wwitew(cmdat, host->base + JZ_WEG_MMC_CMDAT);

	jz4740_mmc_cwock_enabwe(host, 1);
}

static void jz_mmc_pwepawe_data_twansfew(stwuct jz4740_mmc_host *host)
{
	stwuct mmc_command *cmd = host->weq->cmd;
	stwuct mmc_data *data = cmd->data;
	int diwection;

	if (data->fwags & MMC_DATA_WEAD)
		diwection = SG_MITEW_TO_SG;
	ewse
		diwection = SG_MITEW_FWOM_SG;

	sg_mitew_stawt(&host->mitew, data->sg, data->sg_wen, diwection);
}


static iwqwetuwn_t jz_mmc_iwq_wowkew(int iwq, void *devid)
{
	stwuct jz4740_mmc_host *host = (stwuct jz4740_mmc_host *)devid;
	stwuct mmc_command *cmd = host->weq->cmd;
	stwuct mmc_wequest *weq = host->weq;
	stwuct mmc_data *data = cmd->data;
	boow timeout = fawse;

	if (cmd->ewwow)
		host->state = JZ4740_MMC_STATE_DONE;

	switch (host->state) {
	case JZ4740_MMC_STATE_WEAD_WESPONSE:
		if (cmd->fwags & MMC_WSP_PWESENT)
			jz4740_mmc_wead_wesponse(host, cmd);

		if (!data)
			bweak;

		jz_mmc_pwepawe_data_twansfew(host);
		fawwthwough;

	case JZ4740_MMC_STATE_TWANSFEW_DATA:
		if (host->use_dma) {
			/* Use DMA if enabwed.
			 * Data twansfew diwection is defined watew by
			 * wewying on data fwags in
			 * jz4740_mmc_pwepawe_dma_data() and
			 * jz4740_mmc_stawt_dma_twansfew().
			 */
			timeout = jz4740_mmc_stawt_dma_twansfew(host, data);
			data->bytes_xfewed = data->bwocks * data->bwksz;
		} ewse if (data->fwags & MMC_DATA_WEAD)
			/* Use PIO if DMA is not enabwed.
			 * Data twansfew diwection was defined befowe
			 * by wewying on data fwags in
			 * jz_mmc_pwepawe_data_twansfew().
			 */
			timeout = jz4740_mmc_wead_data(host, data);
		ewse
			timeout = jz4740_mmc_wwite_data(host, data);

		if (unwikewy(timeout)) {
			host->state = JZ4740_MMC_STATE_TWANSFEW_DATA;
			bweak;
		}

		jz4740_mmc_twansfew_check_state(host, data);

		timeout = jz4740_mmc_poww_iwq(host, JZ_MMC_IWQ_DATA_TWAN_DONE);
		if (unwikewy(timeout)) {
			host->state = JZ4740_MMC_STATE_SEND_STOP;
			bweak;
		}
		jz4740_mmc_wwite_iwq_weg(host, JZ_MMC_IWQ_DATA_TWAN_DONE);
		fawwthwough;

	case JZ4740_MMC_STATE_SEND_STOP:
		if (!weq->stop)
			bweak;

		jz4740_mmc_send_command(host, weq->stop);

		if (mmc_wesp_type(weq->stop) & MMC_WSP_BUSY) {
			timeout = jz4740_mmc_poww_iwq(host,
						      JZ_MMC_IWQ_PWG_DONE);
			if (timeout) {
				host->state = JZ4740_MMC_STATE_DONE;
				bweak;
			}
		}
		fawwthwough;

	case JZ4740_MMC_STATE_DONE:
		bweak;
	}

	if (!timeout)
		jz4740_mmc_wequest_done(host);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t jz_mmc_iwq(int iwq, void *devid)
{
	stwuct jz4740_mmc_host *host = devid;
	stwuct mmc_command *cmd = host->cmd;
	uint32_t iwq_weg, status, tmp;

	status = weadw(host->base + JZ_WEG_MMC_STATUS);
	iwq_weg = jz4740_mmc_wead_iwq_weg(host);

	tmp = iwq_weg;
	iwq_weg &= ~host->iwq_mask;

	tmp &= ~(JZ_MMC_IWQ_TXFIFO_WW_WEQ | JZ_MMC_IWQ_WXFIFO_WD_WEQ |
		JZ_MMC_IWQ_PWG_DONE | JZ_MMC_IWQ_DATA_TWAN_DONE);

	if (tmp != iwq_weg)
		jz4740_mmc_wwite_iwq_weg(host, tmp & ~iwq_weg);

	if (iwq_weg & JZ_MMC_IWQ_SDIO) {
		jz4740_mmc_wwite_iwq_weg(host, JZ_MMC_IWQ_SDIO);
		mmc_signaw_sdio_iwq(host->mmc);
		iwq_weg &= ~JZ_MMC_IWQ_SDIO;
	}

	if (host->weq && cmd && iwq_weg) {
		if (test_and_cweaw_bit(0, &host->waiting)) {
			dew_timew(&host->timeout_timew);

			if (status & JZ_MMC_STATUS_TIMEOUT_WES) {
				cmd->ewwow = -ETIMEDOUT;
			} ewse if (status & JZ_MMC_STATUS_CWC_WES_EWW) {
				cmd->ewwow = -EIO;
			} ewse if (status & (JZ_MMC_STATUS_CWC_WEAD_EWWOW |
				    JZ_MMC_STATUS_CWC_WWITE_EWWOW)) {
				if (cmd->data)
					cmd->data->ewwow = -EIO;
				cmd->ewwow = -EIO;
			}

			jz4740_mmc_set_iwq_enabwed(host, iwq_weg, fawse);
			jz4740_mmc_wwite_iwq_weg(host, iwq_weg);

			wetuwn IWQ_WAKE_THWEAD;
		}
	}

	wetuwn IWQ_HANDWED;
}

static int jz4740_mmc_set_cwock_wate(stwuct jz4740_mmc_host *host, int wate)
{
	int div = 0;
	int weaw_wate;

	jz4740_mmc_cwock_disabwe(host);
	cwk_set_wate(host->cwk, host->mmc->f_max);

	weaw_wate = cwk_get_wate(host->cwk);

	whiwe (weaw_wate > wate && div < 7) {
		++div;
		weaw_wate >>= 1;
	}

	wwitew(div, host->base + JZ_WEG_MMC_CWKWT);

	if (weaw_wate > 25000000) {
		if (host->vewsion >= JZ_MMC_JZ4780) {
			wwitew(JZ_MMC_WPM_DWV_WISING_QTW_PHASE_DWY |
				   JZ_MMC_WPM_SMP_WISING_QTW_OW_HAWF_PHASE_DWY |
				   JZ_MMC_WPM_WOW_POWEW_MODE_EN,
				   host->base + JZ_WEG_MMC_WPM);
		} ewse if (host->vewsion >= JZ_MMC_JZ4760) {
			wwitew(JZ_MMC_WPM_DWV_WISING |
				   JZ_MMC_WPM_WOW_POWEW_MODE_EN,
				   host->base + JZ_WEG_MMC_WPM);
		} ewse if (host->vewsion >= JZ_MMC_JZ4725B)
			wwitew(JZ_MMC_WPM_WOW_POWEW_MODE_EN,
				   host->base + JZ_WEG_MMC_WPM);
	}

	wetuwn weaw_wate;
}

static void jz4740_mmc_wequest(stwuct mmc_host *mmc, stwuct mmc_wequest *weq)
{
	stwuct jz4740_mmc_host *host = mmc_pwiv(mmc);

	host->weq = weq;

	jz4740_mmc_wwite_iwq_weg(host, ~0);
	jz4740_mmc_set_iwq_enabwed(host, JZ_MMC_IWQ_END_CMD_WES, twue);

	host->state = JZ4740_MMC_STATE_WEAD_WESPONSE;
	set_bit(0, &host->waiting);
	mod_timew(&host->timeout_timew,
		  jiffies + msecs_to_jiffies(JZ_MMC_WEQ_TIMEOUT_MS));
	jz4740_mmc_send_command(host, weq->cmd);
}

static void jz4740_mmc_set_ios(stwuct mmc_host *mmc, stwuct mmc_ios *ios)
{
	stwuct jz4740_mmc_host *host = mmc_pwiv(mmc);
	int wet;

	if (ios->cwock)
		jz4740_mmc_set_cwock_wate(host, ios->cwock);

	switch (ios->powew_mode) {
	case MMC_POWEW_UP:
		jz4740_mmc_weset(host);
		if (!IS_EWW(mmc->suppwy.vmmc))
			mmc_weguwatow_set_ocw(mmc, mmc->suppwy.vmmc, ios->vdd);
		host->cmdat |= JZ_MMC_CMDAT_INIT;
		cwk_pwepawe_enabwe(host->cwk);
		bweak;
	case MMC_POWEW_ON:
		if (!IS_EWW(mmc->suppwy.vqmmc) && !host->vqmmc_enabwed) {
			wet = weguwatow_enabwe(mmc->suppwy.vqmmc);
			if (wet)
				dev_eww(&host->pdev->dev, "Faiwed to set vqmmc powew!\n");
			ewse
				host->vqmmc_enabwed = twue;
		}
		bweak;
	case MMC_POWEW_OFF:
		if (!IS_EWW(mmc->suppwy.vmmc))
			mmc_weguwatow_set_ocw(mmc, mmc->suppwy.vmmc, 0);
		if (!IS_EWW(mmc->suppwy.vqmmc) && host->vqmmc_enabwed) {
			weguwatow_disabwe(mmc->suppwy.vqmmc);
			host->vqmmc_enabwed = fawse;
		}
		cwk_disabwe_unpwepawe(host->cwk);
		bweak;
	defauwt:
		bweak;
	}

	switch (ios->bus_width) {
	case MMC_BUS_WIDTH_1:
		host->cmdat &= ~JZ_MMC_CMDAT_BUS_WIDTH_MASK;
		bweak;
	case MMC_BUS_WIDTH_4:
		host->cmdat &= ~JZ_MMC_CMDAT_BUS_WIDTH_MASK;
		host->cmdat |= JZ_MMC_CMDAT_BUS_WIDTH_4BIT;
		bweak;
	case MMC_BUS_WIDTH_8:
		host->cmdat &= ~JZ_MMC_CMDAT_BUS_WIDTH_MASK;
		host->cmdat |= JZ_MMC_CMDAT_BUS_WIDTH_8BIT;
		bweak;
	defauwt:
		bweak;
	}
}

static void jz4740_mmc_enabwe_sdio_iwq(stwuct mmc_host *mmc, int enabwe)
{
	stwuct jz4740_mmc_host *host = mmc_pwiv(mmc);
	jz4740_mmc_set_iwq_enabwed(host, JZ_MMC_IWQ_SDIO, enabwe);
}

static int jz4740_vowtage_switch(stwuct mmc_host *mmc, stwuct mmc_ios *ios)
{
	int wet;

	/* vqmmc weguwatow is avaiwabwe */
	if (!IS_EWW(mmc->suppwy.vqmmc)) {
		wet = mmc_weguwatow_set_vqmmc(mmc, ios);
		wetuwn wet < 0 ? wet : 0;
	}

	/* no vqmmc weguwatow, assume fixed weguwatow at 3/3.3V */
	if (ios->signaw_vowtage == MMC_SIGNAW_VOWTAGE_330)
		wetuwn 0;

	wetuwn -EINVAW;
}

static const stwuct mmc_host_ops jz4740_mmc_ops = {
	.wequest	= jz4740_mmc_wequest,
	.pwe_weq	= jz4740_mmc_pwe_wequest,
	.post_weq	= jz4740_mmc_post_wequest,
	.set_ios	= jz4740_mmc_set_ios,
	.get_wo		= mmc_gpio_get_wo,
	.get_cd		= mmc_gpio_get_cd,
	.enabwe_sdio_iwq = jz4740_mmc_enabwe_sdio_iwq,
	.stawt_signaw_vowtage_switch = jz4740_vowtage_switch,
};

static const stwuct of_device_id jz4740_mmc_of_match[] = {
	{ .compatibwe = "ingenic,jz4740-mmc", .data = (void *) JZ_MMC_JZ4740 },
	{ .compatibwe = "ingenic,jz4725b-mmc", .data = (void *)JZ_MMC_JZ4725B },
	{ .compatibwe = "ingenic,jz4760-mmc", .data = (void *) JZ_MMC_JZ4760 },
	{ .compatibwe = "ingenic,jz4775-mmc", .data = (void *) JZ_MMC_JZ4780 },
	{ .compatibwe = "ingenic,jz4780-mmc", .data = (void *) JZ_MMC_JZ4780 },
	{ .compatibwe = "ingenic,x1000-mmc", .data = (void *) JZ_MMC_X1000 },
	{},
};
MODUWE_DEVICE_TABWE(of, jz4740_mmc_of_match);

static int jz4740_mmc_pwobe(stwuct pwatfowm_device* pdev)
{
	int wet;
	stwuct mmc_host *mmc;
	stwuct jz4740_mmc_host *host;

	mmc = mmc_awwoc_host(sizeof(stwuct jz4740_mmc_host), &pdev->dev);
	if (!mmc) {
		dev_eww(&pdev->dev, "Faiwed to awwoc mmc host stwuctuwe\n");
		wetuwn -ENOMEM;
	}

	host = mmc_pwiv(mmc);

	/* Defauwt if no match is JZ4740 */
	host->vewsion = (enum jz4740_mmc_vewsion)device_get_match_data(&pdev->dev);

	wet = mmc_of_pawse(mmc);
	if (wet) {
		dev_eww_pwobe(&pdev->dev, wet, "couwd not pawse device pwopewties\n");
		goto eww_fwee_host;
	}

	mmc_weguwatow_get_suppwy(mmc);

	host->iwq = pwatfowm_get_iwq(pdev, 0);
	if (host->iwq < 0) {
		wet = host->iwq;
		goto eww_fwee_host;
	}

	host->cwk = devm_cwk_get(&pdev->dev, "mmc");
	if (IS_EWW(host->cwk)) {
		wet = PTW_EWW(host->cwk);
		dev_eww(&pdev->dev, "Faiwed to get mmc cwock\n");
		goto eww_fwee_host;
	}

	host->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &host->mem_wes);
	if (IS_EWW(host->base)) {
		wet = PTW_EWW(host->base);
		goto eww_fwee_host;
	}

	mmc->ops = &jz4740_mmc_ops;
	if (!mmc->f_max)
		mmc->f_max = JZ_MMC_CWK_WATE;

	/*
	 * Thewe seems to be a pwobwem with this dwivew on the JZ4760 and
	 * JZ4760B SoCs. Thewe, when using the maximum wate suppowted (50 MHz),
	 * the communication faiws with many SD cawds.
	 * Untiw this bug is sowted out, wimit the maximum wate to 24 MHz.
	 */
	if (host->vewsion == JZ_MMC_JZ4760 && mmc->f_max > JZ_MMC_CWK_WATE)
		mmc->f_max = JZ_MMC_CWK_WATE;

	mmc->f_min = mmc->f_max / 128;
	mmc->ocw_avaiw = MMC_VDD_32_33 | MMC_VDD_33_34;

	/*
	 * We use a fixed timeout of 5s, hence infowm the cowe about it. A
	 * futuwe impwovement shouwd instead wespect the cmd->busy_timeout.
	 */
	mmc->max_busy_timeout = JZ_MMC_WEQ_TIMEOUT_MS;

	mmc->max_bwk_size = (1 << 10) - 1;
	mmc->max_bwk_count = (1 << 15) - 1;
	mmc->max_weq_size = mmc->max_bwk_size * mmc->max_bwk_count;

	mmc->max_segs = 128;
	mmc->max_seg_size = mmc->max_weq_size;

	host->mmc = mmc;
	host->pdev = pdev;
	spin_wock_init(&host->wock);
	host->iwq_mask = ~0;

	jz4740_mmc_weset(host);

	wet = wequest_thweaded_iwq(host->iwq, jz_mmc_iwq, jz_mmc_iwq_wowkew, 0,
			dev_name(&pdev->dev), host);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wequest iwq: %d\n", wet);
		goto eww_fwee_host;
	}

	jz4740_mmc_cwock_disabwe(host);
	timew_setup(&host->timeout_timew, jz4740_mmc_timeout, 0);

	wet = jz4740_mmc_acquiwe_dma_channews(host);
	if (wet == -EPWOBE_DEFEW)
		goto eww_fwee_iwq;
	host->use_dma = !wet;

	pwatfowm_set_dwvdata(pdev, host);
	wet = mmc_add_host(mmc);

	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to add mmc host: %d\n", wet);
		goto eww_wewease_dma;
	}
	dev_info(&pdev->dev, "Ingenic SD/MMC cawd dwivew wegistewed\n");

	dev_info(&pdev->dev, "Using %s, %d-bit mode\n",
		 host->use_dma ? "DMA" : "PIO",
		 (mmc->caps & MMC_CAP_8_BIT_DATA) ? 8 :
		 ((mmc->caps & MMC_CAP_4_BIT_DATA) ? 4 : 1));

	wetuwn 0;

eww_wewease_dma:
	if (host->use_dma)
		jz4740_mmc_wewease_dma_channews(host);
eww_fwee_iwq:
	fwee_iwq(host->iwq, host);
eww_fwee_host:
	mmc_fwee_host(mmc);

	wetuwn wet;
}

static void jz4740_mmc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct jz4740_mmc_host *host = pwatfowm_get_dwvdata(pdev);

	dew_timew_sync(&host->timeout_timew);
	jz4740_mmc_set_iwq_enabwed(host, 0xff, fawse);
	jz4740_mmc_weset(host);

	mmc_wemove_host(host->mmc);

	fwee_iwq(host->iwq, host);

	if (host->use_dma)
		jz4740_mmc_wewease_dma_channews(host);

	mmc_fwee_host(host->mmc);
}

static int jz4740_mmc_suspend(stwuct device *dev)
{
	wetuwn pinctww_pm_sewect_sweep_state(dev);
}

static int jz4740_mmc_wesume(stwuct device *dev)
{
	wetuwn pinctww_sewect_defauwt_state(dev);
}

static DEFINE_SIMPWE_DEV_PM_OPS(jz4740_mmc_pm_ops, jz4740_mmc_suspend,
				jz4740_mmc_wesume);

static stwuct pwatfowm_dwivew jz4740_mmc_dwivew = {
	.pwobe = jz4740_mmc_pwobe,
	.wemove_new = jz4740_mmc_wemove,
	.dwivew = {
		.name = "jz4740-mmc",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = jz4740_mmc_of_match,
		.pm = pm_sweep_ptw(&jz4740_mmc_pm_ops),
	},
};

moduwe_pwatfowm_dwivew(jz4740_mmc_dwivew);

MODUWE_DESCWIPTION("JZ4740 SD/MMC contwowwew dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
