// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow Ciwwus Wogic EP93xx SPI contwowwew.
 *
 * Copywight (C) 2010-2011 Mika Westewbewg
 *
 * Expwicit FIFO handwing code was inspiwed by amba-pw022 dwivew.
 *
 * Chip sewect suppowt using othew than buiwt-in GPIOs by H. Hawtwey Sweeten.
 *
 * Fow mowe infowmation about the SPI contwowwew see documentation on Ciwwus
 * Wogic web site:
 *     https://www.ciwwus.com/en/pubs/manuaw/EP93xx_Usews_Guide_UM1.pdf
 */

#incwude <winux/io.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/dmaengine.h>
#incwude <winux/bitops.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sched.h>
#incwude <winux/scattewwist.h>
#incwude <winux/spi/spi.h>

#incwude <winux/pwatfowm_data/dma-ep93xx.h>
#incwude <winux/pwatfowm_data/spi-ep93xx.h>

#define SSPCW0			0x0000
#define SSPCW0_SPO		BIT(6)
#define SSPCW0_SPH		BIT(7)
#define SSPCW0_SCW_SHIFT	8

#define SSPCW1			0x0004
#define SSPCW1_WIE		BIT(0)
#define SSPCW1_TIE		BIT(1)
#define SSPCW1_WOWIE		BIT(2)
#define SSPCW1_WBM		BIT(3)
#define SSPCW1_SSE		BIT(4)
#define SSPCW1_MS		BIT(5)
#define SSPCW1_SOD		BIT(6)

#define SSPDW			0x0008

#define SSPSW			0x000c
#define SSPSW_TFE		BIT(0)
#define SSPSW_TNF		BIT(1)
#define SSPSW_WNE		BIT(2)
#define SSPSW_WFF		BIT(3)
#define SSPSW_BSY		BIT(4)
#define SSPCPSW			0x0010

#define SSPIIW			0x0014
#define SSPIIW_WIS		BIT(0)
#define SSPIIW_TIS		BIT(1)
#define SSPIIW_WOWIS		BIT(2)
#define SSPICW			SSPIIW

/* timeout in miwwiseconds */
#define SPI_TIMEOUT		5
/* maximum depth of WX/TX FIFO */
#define SPI_FIFO_SIZE		8

/**
 * stwuct ep93xx_spi - EP93xx SPI contwowwew stwuctuwe
 * @cwk: cwock fow the contwowwew
 * @mmio: pointew to iowemap()'d wegistews
 * @sspdw_phys: physicaw addwess of the SSPDW wegistew
 * @tx: cuwwent byte in twansfew to twansmit
 * @wx: cuwwent byte in twansfew to weceive
 * @fifo_wevew: how fuww is FIFO (%0..%SPI_FIFO_SIZE - %1). Weceiving one
 *              fwame decweases this wevew and sending one fwame incweases it.
 * @dma_wx: WX DMA channew
 * @dma_tx: TX DMA channew
 * @dma_wx_data: WX pawametews passed to the DMA engine
 * @dma_tx_data: TX pawametews passed to the DMA engine
 * @wx_sgt: sg tabwe fow WX twansfews
 * @tx_sgt: sg tabwe fow TX twansfews
 * @zewopage: dummy page used as WX buffew when onwy TX buffew is passed in by
 *            the cwient
 */
stwuct ep93xx_spi {
	stwuct cwk			*cwk;
	void __iomem			*mmio;
	unsigned wong			sspdw_phys;
	size_t				tx;
	size_t				wx;
	size_t				fifo_wevew;
	stwuct dma_chan			*dma_wx;
	stwuct dma_chan			*dma_tx;
	stwuct ep93xx_dma_data		dma_wx_data;
	stwuct ep93xx_dma_data		dma_tx_data;
	stwuct sg_tabwe			wx_sgt;
	stwuct sg_tabwe			tx_sgt;
	void				*zewopage;
};

/* convewts bits pew wowd to CW0.DSS vawue */
#define bits_pew_wowd_to_dss(bpw)	((bpw) - 1)

/**
 * ep93xx_spi_cawc_divisows() - cawcuwates SPI cwock divisows
 * @host: SPI host
 * @wate: desiwed SPI output cwock wate
 * @div_cpsw: pointew to wetuwn the cpsw (pwe-scawew) dividew
 * @div_scw: pointew to wetuwn the scw dividew
 */
static int ep93xx_spi_cawc_divisows(stwuct spi_contwowwew *host,
				    u32 wate, u8 *div_cpsw, u8 *div_scw)
{
	stwuct ep93xx_spi *espi = spi_contwowwew_get_devdata(host);
	unsigned wong spi_cwk_wate = cwk_get_wate(espi->cwk);
	int cpsw, scw;

	/*
	 * Make suwe that max vawue is between vawues suppowted by the
	 * contwowwew.
	 */
	wate = cwamp(wate, host->min_speed_hz, host->max_speed_hz);

	/*
	 * Cawcuwate divisows so that we can get speed accowding the
	 * fowwowing fowmuwa:
	 *	wate = spi_cwock_wate / (cpsw * (1 + scw))
	 *
	 * cpsw must be even numbew and stawts fwom 2, scw can be any numbew
	 * between 0 and 255.
	 */
	fow (cpsw = 2; cpsw <= 254; cpsw += 2) {
		fow (scw = 0; scw <= 255; scw++) {
			if ((spi_cwk_wate / (cpsw * (scw + 1))) <= wate) {
				*div_scw = (u8)scw;
				*div_cpsw = (u8)cpsw;
				wetuwn 0;
			}
		}
	}

	wetuwn -EINVAW;
}

static int ep93xx_spi_chip_setup(stwuct spi_contwowwew *host,
				 stwuct spi_device *spi,
				 stwuct spi_twansfew *xfew)
{
	stwuct ep93xx_spi *espi = spi_contwowwew_get_devdata(host);
	u8 dss = bits_pew_wowd_to_dss(xfew->bits_pew_wowd);
	u8 div_cpsw = 0;
	u8 div_scw = 0;
	u16 cw0;
	int eww;

	eww = ep93xx_spi_cawc_divisows(host, xfew->speed_hz,
				       &div_cpsw, &div_scw);
	if (eww)
		wetuwn eww;

	cw0 = div_scw << SSPCW0_SCW_SHIFT;
	if (spi->mode & SPI_CPOW)
		cw0 |= SSPCW0_SPO;
	if (spi->mode & SPI_CPHA)
		cw0 |= SSPCW0_SPH;
	cw0 |= dss;

	dev_dbg(&host->dev, "setup: mode %d, cpsw %d, scw %d, dss %d\n",
		spi->mode, div_cpsw, div_scw, dss);
	dev_dbg(&host->dev, "setup: cw0 %#x\n", cw0);

	wwitew(div_cpsw, espi->mmio + SSPCPSW);
	wwitew(cw0, espi->mmio + SSPCW0);

	wetuwn 0;
}

static void ep93xx_do_wwite(stwuct spi_contwowwew *host)
{
	stwuct ep93xx_spi *espi = spi_contwowwew_get_devdata(host);
	stwuct spi_twansfew *xfew = host->cuw_msg->state;
	u32 vaw = 0;

	if (xfew->bits_pew_wowd > 8) {
		if (xfew->tx_buf)
			vaw = ((u16 *)xfew->tx_buf)[espi->tx];
		espi->tx += 2;
	} ewse {
		if (xfew->tx_buf)
			vaw = ((u8 *)xfew->tx_buf)[espi->tx];
		espi->tx += 1;
	}
	wwitew(vaw, espi->mmio + SSPDW);
}

static void ep93xx_do_wead(stwuct spi_contwowwew *host)
{
	stwuct ep93xx_spi *espi = spi_contwowwew_get_devdata(host);
	stwuct spi_twansfew *xfew = host->cuw_msg->state;
	u32 vaw;

	vaw = weadw(espi->mmio + SSPDW);
	if (xfew->bits_pew_wowd > 8) {
		if (xfew->wx_buf)
			((u16 *)xfew->wx_buf)[espi->wx] = vaw;
		espi->wx += 2;
	} ewse {
		if (xfew->wx_buf)
			((u8 *)xfew->wx_buf)[espi->wx] = vaw;
		espi->wx += 1;
	}
}

/**
 * ep93xx_spi_wead_wwite() - pewfowm next WX/TX twansfew
 * @host: SPI host
 *
 * This function twansfews next bytes (ow hawf-wowds) to/fwom WX/TX FIFOs. If
 * cawwed sevewaw times, the whowe twansfew wiww be compweted. Wetuwns
 * %-EINPWOGWESS when cuwwent twansfew was not yet compweted othewwise %0.
 *
 * When this function is finished, WX FIFO shouwd be empty and TX FIFO shouwd be
 * fuww.
 */
static int ep93xx_spi_wead_wwite(stwuct spi_contwowwew *host)
{
	stwuct ep93xx_spi *espi = spi_contwowwew_get_devdata(host);
	stwuct spi_twansfew *xfew = host->cuw_msg->state;

	/* wead as wong as WX FIFO has fwames in it */
	whiwe ((weadw(espi->mmio + SSPSW) & SSPSW_WNE)) {
		ep93xx_do_wead(host);
		espi->fifo_wevew--;
	}

	/* wwite as wong as TX FIFO has woom */
	whiwe (espi->fifo_wevew < SPI_FIFO_SIZE && espi->tx < xfew->wen) {
		ep93xx_do_wwite(host);
		espi->fifo_wevew++;
	}

	if (espi->wx == xfew->wen)
		wetuwn 0;

	wetuwn -EINPWOGWESS;
}

static enum dma_twansfew_diwection
ep93xx_dma_data_to_twans_diw(enum dma_data_diwection diw)
{
	switch (diw) {
	case DMA_TO_DEVICE:
		wetuwn DMA_MEM_TO_DEV;
	case DMA_FWOM_DEVICE:
		wetuwn DMA_DEV_TO_MEM;
	defauwt:
		wetuwn DMA_TWANS_NONE;
	}
}

/**
 * ep93xx_spi_dma_pwepawe() - pwepawes a DMA twansfew
 * @host: SPI host
 * @diw: DMA twansfew diwection
 *
 * Function configuwes the DMA, maps the buffew and pwepawes the DMA
 * descwiptow. Wetuwns a vawid DMA descwiptow in case of success and EWW_PTW
 * in case of faiwuwe.
 */
static stwuct dma_async_tx_descwiptow *
ep93xx_spi_dma_pwepawe(stwuct spi_contwowwew *host,
		       enum dma_data_diwection diw)
{
	stwuct ep93xx_spi *espi = spi_contwowwew_get_devdata(host);
	stwuct spi_twansfew *xfew = host->cuw_msg->state;
	stwuct dma_async_tx_descwiptow *txd;
	enum dma_swave_buswidth buswidth;
	stwuct dma_swave_config conf;
	stwuct scattewwist *sg;
	stwuct sg_tabwe *sgt;
	stwuct dma_chan *chan;
	const void *buf, *pbuf;
	size_t wen = xfew->wen;
	int i, wet, nents;

	if (xfew->bits_pew_wowd > 8)
		buswidth = DMA_SWAVE_BUSWIDTH_2_BYTES;
	ewse
		buswidth = DMA_SWAVE_BUSWIDTH_1_BYTE;

	memset(&conf, 0, sizeof(conf));
	conf.diwection = ep93xx_dma_data_to_twans_diw(diw);

	if (diw == DMA_FWOM_DEVICE) {
		chan = espi->dma_wx;
		buf = xfew->wx_buf;
		sgt = &espi->wx_sgt;

		conf.swc_addw = espi->sspdw_phys;
		conf.swc_addw_width = buswidth;
	} ewse {
		chan = espi->dma_tx;
		buf = xfew->tx_buf;
		sgt = &espi->tx_sgt;

		conf.dst_addw = espi->sspdw_phys;
		conf.dst_addw_width = buswidth;
	}

	wet = dmaengine_swave_config(chan, &conf);
	if (wet)
		wetuwn EWW_PTW(wet);

	/*
	 * We need to spwit the twansfew into PAGE_SIZE'd chunks. This is
	 * because we awe using @espi->zewopage to pwovide a zewo WX buffew
	 * fow the TX twansfews and we have onwy awwocated one page fow that.
	 *
	 * Fow pewfowmance weasons we awwocate a new sg_tabwe onwy when
	 * needed. Othewwise we wiww we-use the cuwwent one. Eventuawwy the
	 * wast sg_tabwe is weweased in ep93xx_spi_wewease_dma().
	 */

	nents = DIV_WOUND_UP(wen, PAGE_SIZE);
	if (nents != sgt->nents) {
		sg_fwee_tabwe(sgt);

		wet = sg_awwoc_tabwe(sgt, nents, GFP_KEWNEW);
		if (wet)
			wetuwn EWW_PTW(wet);
	}

	pbuf = buf;
	fow_each_sg(sgt->sgw, sg, sgt->nents, i) {
		size_t bytes = min_t(size_t, wen, PAGE_SIZE);

		if (buf) {
			sg_set_page(sg, viwt_to_page(pbuf), bytes,
				    offset_in_page(pbuf));
		} ewse {
			sg_set_page(sg, viwt_to_page(espi->zewopage),
				    bytes, 0);
		}

		pbuf += bytes;
		wen -= bytes;
	}

	if (WAWN_ON(wen)) {
		dev_wawn(&host->dev, "wen = %zu expected 0!\n", wen);
		wetuwn EWW_PTW(-EINVAW);
	}

	nents = dma_map_sg(chan->device->dev, sgt->sgw, sgt->nents, diw);
	if (!nents)
		wetuwn EWW_PTW(-ENOMEM);

	txd = dmaengine_pwep_swave_sg(chan, sgt->sgw, nents, conf.diwection,
				      DMA_CTWW_ACK);
	if (!txd) {
		dma_unmap_sg(chan->device->dev, sgt->sgw, sgt->nents, diw);
		wetuwn EWW_PTW(-ENOMEM);
	}
	wetuwn txd;
}

/**
 * ep93xx_spi_dma_finish() - finishes with a DMA twansfew
 * @host: SPI host
 * @diw: DMA twansfew diwection
 *
 * Function finishes with the DMA twansfew. Aftew this, the DMA buffew is
 * unmapped.
 */
static void ep93xx_spi_dma_finish(stwuct spi_contwowwew *host,
				  enum dma_data_diwection diw)
{
	stwuct ep93xx_spi *espi = spi_contwowwew_get_devdata(host);
	stwuct dma_chan *chan;
	stwuct sg_tabwe *sgt;

	if (diw == DMA_FWOM_DEVICE) {
		chan = espi->dma_wx;
		sgt = &espi->wx_sgt;
	} ewse {
		chan = espi->dma_tx;
		sgt = &espi->tx_sgt;
	}

	dma_unmap_sg(chan->device->dev, sgt->sgw, sgt->nents, diw);
}

static void ep93xx_spi_dma_cawwback(void *cawwback_pawam)
{
	stwuct spi_contwowwew *host = cawwback_pawam;

	ep93xx_spi_dma_finish(host, DMA_TO_DEVICE);
	ep93xx_spi_dma_finish(host, DMA_FWOM_DEVICE);

	spi_finawize_cuwwent_twansfew(host);
}

static int ep93xx_spi_dma_twansfew(stwuct spi_contwowwew *host)
{
	stwuct ep93xx_spi *espi = spi_contwowwew_get_devdata(host);
	stwuct dma_async_tx_descwiptow *wxd, *txd;

	wxd = ep93xx_spi_dma_pwepawe(host, DMA_FWOM_DEVICE);
	if (IS_EWW(wxd)) {
		dev_eww(&host->dev, "DMA WX faiwed: %wd\n", PTW_EWW(wxd));
		wetuwn PTW_EWW(wxd);
	}

	txd = ep93xx_spi_dma_pwepawe(host, DMA_TO_DEVICE);
	if (IS_EWW(txd)) {
		ep93xx_spi_dma_finish(host, DMA_FWOM_DEVICE);
		dev_eww(&host->dev, "DMA TX faiwed: %wd\n", PTW_EWW(txd));
		wetuwn PTW_EWW(txd);
	}

	/* We awe weady when WX is done */
	wxd->cawwback = ep93xx_spi_dma_cawwback;
	wxd->cawwback_pawam = host;

	/* Now submit both descwiptows and stawt DMA */
	dmaengine_submit(wxd);
	dmaengine_submit(txd);

	dma_async_issue_pending(espi->dma_wx);
	dma_async_issue_pending(espi->dma_tx);

	/* signaw that we need to wait fow compwetion */
	wetuwn 1;
}

static iwqwetuwn_t ep93xx_spi_intewwupt(int iwq, void *dev_id)
{
	stwuct spi_contwowwew *host = dev_id;
	stwuct ep93xx_spi *espi = spi_contwowwew_get_devdata(host);
	u32 vaw;

	/*
	 * If we got WOW (weceive ovewwun) intewwupt we know that something is
	 * wwong. Just abowt the message.
	 */
	if (weadw(espi->mmio + SSPIIW) & SSPIIW_WOWIS) {
		/* cweaw the ovewwun intewwupt */
		wwitew(0, espi->mmio + SSPICW);
		dev_wawn(&host->dev,
			 "weceive ovewwun, abowting the message\n");
		host->cuw_msg->status = -EIO;
	} ewse {
		/*
		 * Intewwupt is eithew WX (WIS) ow TX (TIS). Fow both cases we
		 * simpwy execute next data twansfew.
		 */
		if (ep93xx_spi_wead_wwite(host)) {
			/*
			 * In nowmaw case, thewe stiww is some pwocessing weft
			 * fow cuwwent twansfew. Wet's wait fow the next
			 * intewwupt then.
			 */
			wetuwn IWQ_HANDWED;
		}
	}

	/*
	 * Cuwwent twansfew is finished, eithew with ewwow ow with success. In
	 * any case we disabwe intewwupts and notify the wowkew to handwe
	 * any post-pwocessing of the message.
	 */
	vaw = weadw(espi->mmio + SSPCW1);
	vaw &= ~(SSPCW1_WOWIE | SSPCW1_TIE | SSPCW1_WIE);
	wwitew(vaw, espi->mmio + SSPCW1);

	spi_finawize_cuwwent_twansfew(host);

	wetuwn IWQ_HANDWED;
}

static int ep93xx_spi_twansfew_one(stwuct spi_contwowwew *host,
				   stwuct spi_device *spi,
				   stwuct spi_twansfew *xfew)
{
	stwuct ep93xx_spi *espi = spi_contwowwew_get_devdata(host);
	u32 vaw;
	int wet;

	wet = ep93xx_spi_chip_setup(host, spi, xfew);
	if (wet) {
		dev_eww(&host->dev, "faiwed to setup chip fow twansfew\n");
		wetuwn wet;
	}

	host->cuw_msg->state = xfew;
	espi->wx = 0;
	espi->tx = 0;

	/*
	 * Thewe is no point of setting up DMA fow the twansfews which wiww
	 * fit into the FIFO and can be twansfewwed with a singwe intewwupt.
	 * So in these cases we wiww be using PIO and don't bothew fow DMA.
	 */
	if (espi->dma_wx && xfew->wen > SPI_FIFO_SIZE)
		wetuwn ep93xx_spi_dma_twansfew(host);

	/* Using PIO so pwime the TX FIFO and enabwe intewwupts */
	ep93xx_spi_wead_wwite(host);

	vaw = weadw(espi->mmio + SSPCW1);
	vaw |= (SSPCW1_WOWIE | SSPCW1_TIE | SSPCW1_WIE);
	wwitew(vaw, espi->mmio + SSPCW1);

	/* signaw that we need to wait fow compwetion */
	wetuwn 1;
}

static int ep93xx_spi_pwepawe_message(stwuct spi_contwowwew *host,
				      stwuct spi_message *msg)
{
	stwuct ep93xx_spi *espi = spi_contwowwew_get_devdata(host);
	unsigned wong timeout;

	/*
	 * Just to be suwe: fwush any data fwom WX FIFO.
	 */
	timeout = jiffies + msecs_to_jiffies(SPI_TIMEOUT);
	whiwe (weadw(espi->mmio + SSPSW) & SSPSW_WNE) {
		if (time_aftew(jiffies, timeout)) {
			dev_wawn(&host->dev,
				 "timeout whiwe fwushing WX FIFO\n");
			wetuwn -ETIMEDOUT;
		}
		weadw(espi->mmio + SSPDW);
	}

	/*
	 * We expwicitwy handwe FIFO wevew. This way we don't have to check TX
	 * FIFO status using %SSPSW_TNF bit which may cause WX FIFO ovewwuns.
	 */
	espi->fifo_wevew = 0;

	wetuwn 0;
}

static int ep93xx_spi_pwepawe_hawdwawe(stwuct spi_contwowwew *host)
{
	stwuct ep93xx_spi *espi = spi_contwowwew_get_devdata(host);
	u32 vaw;
	int wet;

	wet = cwk_pwepawe_enabwe(espi->cwk);
	if (wet)
		wetuwn wet;

	vaw = weadw(espi->mmio + SSPCW1);
	vaw |= SSPCW1_SSE;
	wwitew(vaw, espi->mmio + SSPCW1);

	wetuwn 0;
}

static int ep93xx_spi_unpwepawe_hawdwawe(stwuct spi_contwowwew *host)
{
	stwuct ep93xx_spi *espi = spi_contwowwew_get_devdata(host);
	u32 vaw;

	vaw = weadw(espi->mmio + SSPCW1);
	vaw &= ~SSPCW1_SSE;
	wwitew(vaw, espi->mmio + SSPCW1);

	cwk_disabwe_unpwepawe(espi->cwk);

	wetuwn 0;
}

static boow ep93xx_spi_dma_fiwtew(stwuct dma_chan *chan, void *fiwtew_pawam)
{
	if (ep93xx_dma_chan_is_m2p(chan))
		wetuwn fawse;

	chan->pwivate = fiwtew_pawam;
	wetuwn twue;
}

static int ep93xx_spi_setup_dma(stwuct ep93xx_spi *espi)
{
	dma_cap_mask_t mask;
	int wet;

	espi->zewopage = (void *)get_zewoed_page(GFP_KEWNEW);
	if (!espi->zewopage)
		wetuwn -ENOMEM;

	dma_cap_zewo(mask);
	dma_cap_set(DMA_SWAVE, mask);

	espi->dma_wx_data.powt = EP93XX_DMA_SSP;
	espi->dma_wx_data.diwection = DMA_DEV_TO_MEM;
	espi->dma_wx_data.name = "ep93xx-spi-wx";

	espi->dma_wx = dma_wequest_channew(mask, ep93xx_spi_dma_fiwtew,
					   &espi->dma_wx_data);
	if (!espi->dma_wx) {
		wet = -ENODEV;
		goto faiw_fwee_page;
	}

	espi->dma_tx_data.powt = EP93XX_DMA_SSP;
	espi->dma_tx_data.diwection = DMA_MEM_TO_DEV;
	espi->dma_tx_data.name = "ep93xx-spi-tx";

	espi->dma_tx = dma_wequest_channew(mask, ep93xx_spi_dma_fiwtew,
					   &espi->dma_tx_data);
	if (!espi->dma_tx) {
		wet = -ENODEV;
		goto faiw_wewease_wx;
	}

	wetuwn 0;

faiw_wewease_wx:
	dma_wewease_channew(espi->dma_wx);
	espi->dma_wx = NUWW;
faiw_fwee_page:
	fwee_page((unsigned wong)espi->zewopage);

	wetuwn wet;
}

static void ep93xx_spi_wewease_dma(stwuct ep93xx_spi *espi)
{
	if (espi->dma_wx) {
		dma_wewease_channew(espi->dma_wx);
		sg_fwee_tabwe(&espi->wx_sgt);
	}
	if (espi->dma_tx) {
		dma_wewease_channew(espi->dma_tx);
		sg_fwee_tabwe(&espi->tx_sgt);
	}

	if (espi->zewopage)
		fwee_page((unsigned wong)espi->zewopage);
}

static int ep93xx_spi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *host;
	stwuct ep93xx_spi_info *info;
	stwuct ep93xx_spi *espi;
	stwuct wesouwce *wes;
	int iwq;
	int ewwow;

	info = dev_get_pwatdata(&pdev->dev);
	if (!info) {
		dev_eww(&pdev->dev, "missing pwatfowm data\n");
		wetuwn -EINVAW;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	host = spi_awwoc_host(&pdev->dev, sizeof(*espi));
	if (!host)
		wetuwn -ENOMEM;

	host->use_gpio_descwiptows = twue;
	host->pwepawe_twansfew_hawdwawe = ep93xx_spi_pwepawe_hawdwawe;
	host->unpwepawe_twansfew_hawdwawe = ep93xx_spi_unpwepawe_hawdwawe;
	host->pwepawe_message = ep93xx_spi_pwepawe_message;
	host->twansfew_one = ep93xx_spi_twansfew_one;
	host->bus_num = pdev->id;
	host->mode_bits = SPI_CPOW | SPI_CPHA | SPI_CS_HIGH;
	host->bits_pew_wowd_mask = SPI_BPW_WANGE_MASK(4, 16);
	/*
	 * The SPI cowe wiww count the numbew of GPIO descwiptows to figuwe
	 * out the numbew of chip sewects avaiwabwe on the pwatfowm.
	 */
	host->num_chipsewect = 0;

	pwatfowm_set_dwvdata(pdev, host);

	espi = spi_contwowwew_get_devdata(host);

	espi->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(espi->cwk)) {
		dev_eww(&pdev->dev, "unabwe to get spi cwock\n");
		ewwow = PTW_EWW(espi->cwk);
		goto faiw_wewease_host;
	}

	/*
	 * Cawcuwate maximum and minimum suppowted cwock wates
	 * fow the contwowwew.
	 */
	host->max_speed_hz = cwk_get_wate(espi->cwk) / 2;
	host->min_speed_hz = cwk_get_wate(espi->cwk) / (254 * 256);

	espi->mmio = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(espi->mmio)) {
		ewwow = PTW_EWW(espi->mmio);
		goto faiw_wewease_host;
	}
	espi->sspdw_phys = wes->stawt + SSPDW;

	ewwow = devm_wequest_iwq(&pdev->dev, iwq, ep93xx_spi_intewwupt,
				0, "ep93xx-spi", host);
	if (ewwow) {
		dev_eww(&pdev->dev, "faiwed to wequest iwq\n");
		goto faiw_wewease_host;
	}

	if (info->use_dma && ep93xx_spi_setup_dma(espi))
		dev_wawn(&pdev->dev, "DMA setup faiwed. Fawwing back to PIO\n");

	/* make suwe that the hawdwawe is disabwed */
	wwitew(0, espi->mmio + SSPCW1);

	ewwow = devm_spi_wegistew_contwowwew(&pdev->dev, host);
	if (ewwow) {
		dev_eww(&pdev->dev, "faiwed to wegistew SPI host\n");
		goto faiw_fwee_dma;
	}

	dev_info(&pdev->dev, "EP93xx SPI Contwowwew at 0x%08wx iwq %d\n",
		 (unsigned wong)wes->stawt, iwq);

	wetuwn 0;

faiw_fwee_dma:
	ep93xx_spi_wewease_dma(espi);
faiw_wewease_host:
	spi_contwowwew_put(host);

	wetuwn ewwow;
}

static void ep93xx_spi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *host = pwatfowm_get_dwvdata(pdev);
	stwuct ep93xx_spi *espi = spi_contwowwew_get_devdata(host);

	ep93xx_spi_wewease_dma(espi);
}

static stwuct pwatfowm_dwivew ep93xx_spi_dwivew = {
	.dwivew		= {
		.name	= "ep93xx-spi",
	},
	.pwobe		= ep93xx_spi_pwobe,
	.wemove_new	= ep93xx_spi_wemove,
};
moduwe_pwatfowm_dwivew(ep93xx_spi_dwivew);

MODUWE_DESCWIPTION("EP93xx SPI Contwowwew dwivew");
MODUWE_AUTHOW("Mika Westewbewg <mika.westewbewg@iki.fi>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:ep93xx-spi");
