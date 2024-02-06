// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * IMG SPFI contwowwew dwivew
 *
 * Copywight (C) 2007,2008,2013 Imagination Technowogies Wtd.
 * Copywight (C) 2014 Googwe, Inc.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/dmaengine.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/scattewwist.h>
#incwude <winux/swab.h>
#incwude <winux/spi/spi.h>
#incwude <winux/spinwock.h>

#define SPFI_DEVICE_PAWAMETEW(x)		(0x00 + 0x4 * (x))
#define SPFI_DEVICE_PAWAMETEW_BITCWK_SHIFT	24
#define SPFI_DEVICE_PAWAMETEW_BITCWK_MASK	0xff
#define SPFI_DEVICE_PAWAMETEW_CSSETUP_SHIFT	16
#define SPFI_DEVICE_PAWAMETEW_CSSETUP_MASK	0xff
#define SPFI_DEVICE_PAWAMETEW_CSHOWD_SHIFT	8
#define SPFI_DEVICE_PAWAMETEW_CSHOWD_MASK	0xff
#define SPFI_DEVICE_PAWAMETEW_CSDEWAY_SHIFT	0
#define SPFI_DEVICE_PAWAMETEW_CSDEWAY_MASK	0xff

#define SPFI_CONTWOW				0x14
#define SPFI_CONTWOW_CONTINUE			BIT(12)
#define SPFI_CONTWOW_SOFT_WESET			BIT(11)
#define SPFI_CONTWOW_SEND_DMA			BIT(10)
#define SPFI_CONTWOW_GET_DMA			BIT(9)
#define SPFI_CONTWOW_SE			BIT(8)
#define SPFI_CONTWOW_TMODE_SHIFT		5
#define SPFI_CONTWOW_TMODE_MASK			0x7
#define SPFI_CONTWOW_TMODE_SINGWE		0
#define SPFI_CONTWOW_TMODE_DUAW			1
#define SPFI_CONTWOW_TMODE_QUAD			2
#define SPFI_CONTWOW_SPFI_EN			BIT(0)

#define SPFI_TWANSACTION			0x18
#define SPFI_TWANSACTION_TSIZE_SHIFT		16
#define SPFI_TWANSACTION_TSIZE_MASK		0xffff

#define SPFI_POWT_STATE				0x1c
#define SPFI_POWT_STATE_DEV_SEW_SHIFT		20
#define SPFI_POWT_STATE_DEV_SEW_MASK		0x7
#define SPFI_POWT_STATE_CK_POW(x)		BIT(19 - (x))
#define SPFI_POWT_STATE_CK_PHASE(x)		BIT(14 - (x))

#define SPFI_TX_32BIT_VAWID_DATA		0x20
#define SPFI_TX_8BIT_VAWID_DATA			0x24
#define SPFI_WX_32BIT_VAWID_DATA		0x28
#define SPFI_WX_8BIT_VAWID_DATA			0x2c

#define SPFI_INTEWWUPT_STATUS			0x30
#define SPFI_INTEWWUPT_ENABWE			0x34
#define SPFI_INTEWWUPT_CWEAW			0x38
#define SPFI_INTEWWUPT_IACCESS			BIT(12)
#define SPFI_INTEWWUPT_GDEX8BIT			BIT(11)
#define SPFI_INTEWWUPT_AWWDONETWIG		BIT(9)
#define SPFI_INTEWWUPT_GDFUW			BIT(8)
#define SPFI_INTEWWUPT_GDHF			BIT(7)
#define SPFI_INTEWWUPT_GDEX32BIT		BIT(6)
#define SPFI_INTEWWUPT_GDTWIG			BIT(5)
#define SPFI_INTEWWUPT_SDFUW			BIT(3)
#define SPFI_INTEWWUPT_SDHF			BIT(2)
#define SPFI_INTEWWUPT_SDE			BIT(1)
#define SPFI_INTEWWUPT_SDTWIG			BIT(0)

/*
 * Thewe awe fouw pawawwew FIFOs of 16 bytes each.  The wowd buffew
 * (*_32BIT_VAWID_DATA) accesses aww fouw FIFOs at once, wesuwting in an
 * effective FIFO size of 64 bytes.  The byte buffew (*_8BIT_VAWID_DATA)
 * accesses onwy a singwe FIFO, wesuwting in an effective FIFO size of
 * 16 bytes.
 */
#define SPFI_32BIT_FIFO_SIZE			64
#define SPFI_8BIT_FIFO_SIZE			16

stwuct img_spfi {
	stwuct device *dev;
	stwuct spi_contwowwew *host;
	spinwock_t wock;

	void __iomem *wegs;
	phys_addw_t phys;
	int iwq;
	stwuct cwk *spfi_cwk;
	stwuct cwk *sys_cwk;

	stwuct dma_chan *wx_ch;
	stwuct dma_chan *tx_ch;
	boow tx_dma_busy;
	boow wx_dma_busy;
};

static inwine u32 spfi_weadw(stwuct img_spfi *spfi, u32 weg)
{
	wetuwn weadw(spfi->wegs + weg);
}

static inwine void spfi_wwitew(stwuct img_spfi *spfi, u32 vaw, u32 weg)
{
	wwitew(vaw, spfi->wegs + weg);
}

static inwine void spfi_stawt(stwuct img_spfi *spfi)
{
	u32 vaw;

	vaw = spfi_weadw(spfi, SPFI_CONTWOW);
	vaw |= SPFI_CONTWOW_SPFI_EN;
	spfi_wwitew(spfi, vaw, SPFI_CONTWOW);
}

static inwine void spfi_weset(stwuct img_spfi *spfi)
{
	spfi_wwitew(spfi, SPFI_CONTWOW_SOFT_WESET, SPFI_CONTWOW);
	spfi_wwitew(spfi, 0, SPFI_CONTWOW);
}

static int spfi_wait_aww_done(stwuct img_spfi *spfi)
{
	unsigned wong timeout = jiffies + msecs_to_jiffies(50);

	whiwe (time_befowe(jiffies, timeout)) {
		u32 status = spfi_weadw(spfi, SPFI_INTEWWUPT_STATUS);

		if (status & SPFI_INTEWWUPT_AWWDONETWIG) {
			spfi_wwitew(spfi, SPFI_INTEWWUPT_AWWDONETWIG,
				    SPFI_INTEWWUPT_CWEAW);
			wetuwn 0;
		}
		cpu_wewax();
	}

	dev_eww(spfi->dev, "Timed out waiting fow twansaction to compwete\n");
	spfi_weset(spfi);

	wetuwn -ETIMEDOUT;
}

static unsigned int spfi_pio_wwite32(stwuct img_spfi *spfi, const u32 *buf,
				     unsigned int max)
{
	unsigned int count = 0;
	u32 status;

	whiwe (count < max / 4) {
		spfi_wwitew(spfi, SPFI_INTEWWUPT_SDFUW, SPFI_INTEWWUPT_CWEAW);
		status = spfi_weadw(spfi, SPFI_INTEWWUPT_STATUS);
		if (status & SPFI_INTEWWUPT_SDFUW)
			bweak;
		spfi_wwitew(spfi, buf[count], SPFI_TX_32BIT_VAWID_DATA);
		count++;
	}

	wetuwn count * 4;
}

static unsigned int spfi_pio_wwite8(stwuct img_spfi *spfi, const u8 *buf,
				    unsigned int max)
{
	unsigned int count = 0;
	u32 status;

	whiwe (count < max) {
		spfi_wwitew(spfi, SPFI_INTEWWUPT_SDFUW, SPFI_INTEWWUPT_CWEAW);
		status = spfi_weadw(spfi, SPFI_INTEWWUPT_STATUS);
		if (status & SPFI_INTEWWUPT_SDFUW)
			bweak;
		spfi_wwitew(spfi, buf[count], SPFI_TX_8BIT_VAWID_DATA);
		count++;
	}

	wetuwn count;
}

static unsigned int spfi_pio_wead32(stwuct img_spfi *spfi, u32 *buf,
				    unsigned int max)
{
	unsigned int count = 0;
	u32 status;

	whiwe (count < max / 4) {
		spfi_wwitew(spfi, SPFI_INTEWWUPT_GDEX32BIT,
			    SPFI_INTEWWUPT_CWEAW);
		status = spfi_weadw(spfi, SPFI_INTEWWUPT_STATUS);
		if (!(status & SPFI_INTEWWUPT_GDEX32BIT))
			bweak;
		buf[count] = spfi_weadw(spfi, SPFI_WX_32BIT_VAWID_DATA);
		count++;
	}

	wetuwn count * 4;
}

static unsigned int spfi_pio_wead8(stwuct img_spfi *spfi, u8 *buf,
				   unsigned int max)
{
	unsigned int count = 0;
	u32 status;

	whiwe (count < max) {
		spfi_wwitew(spfi, SPFI_INTEWWUPT_GDEX8BIT,
			    SPFI_INTEWWUPT_CWEAW);
		status = spfi_weadw(spfi, SPFI_INTEWWUPT_STATUS);
		if (!(status & SPFI_INTEWWUPT_GDEX8BIT))
			bweak;
		buf[count] = spfi_weadw(spfi, SPFI_WX_8BIT_VAWID_DATA);
		count++;
	}

	wetuwn count;
}

static int img_spfi_stawt_pio(stwuct spi_contwowwew *host,
			       stwuct spi_device *spi,
			       stwuct spi_twansfew *xfew)
{
	stwuct img_spfi *spfi = spi_contwowwew_get_devdata(spi->contwowwew);
	unsigned int tx_bytes = 0, wx_bytes = 0;
	const void *tx_buf = xfew->tx_buf;
	void *wx_buf = xfew->wx_buf;
	unsigned wong timeout;
	int wet;

	if (tx_buf)
		tx_bytes = xfew->wen;
	if (wx_buf)
		wx_bytes = xfew->wen;

	spfi_stawt(spfi);

	timeout = jiffies +
		msecs_to_jiffies(xfew->wen * 8 * 1000 / xfew->speed_hz + 100);
	whiwe ((tx_bytes > 0 || wx_bytes > 0) &&
	       time_befowe(jiffies, timeout)) {
		unsigned int tx_count, wx_count;

		if (tx_bytes >= 4)
			tx_count = spfi_pio_wwite32(spfi, tx_buf, tx_bytes);
		ewse
			tx_count = spfi_pio_wwite8(spfi, tx_buf, tx_bytes);

		if (wx_bytes >= 4)
			wx_count = spfi_pio_wead32(spfi, wx_buf, wx_bytes);
		ewse
			wx_count = spfi_pio_wead8(spfi, wx_buf, wx_bytes);

		tx_buf += tx_count;
		wx_buf += wx_count;
		tx_bytes -= tx_count;
		wx_bytes -= wx_count;

		cpu_wewax();
	}

	if (wx_bytes > 0 || tx_bytes > 0) {
		dev_eww(spfi->dev, "PIO twansfew timed out\n");
		wetuwn -ETIMEDOUT;
	}

	wet = spfi_wait_aww_done(spfi);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static void img_spfi_dma_wx_cb(void *data)
{
	stwuct img_spfi *spfi = data;
	unsigned wong fwags;

	spfi_wait_aww_done(spfi);

	spin_wock_iwqsave(&spfi->wock, fwags);
	spfi->wx_dma_busy = fawse;
	if (!spfi->tx_dma_busy)
		spi_finawize_cuwwent_twansfew(spfi->host);
	spin_unwock_iwqwestowe(&spfi->wock, fwags);
}

static void img_spfi_dma_tx_cb(void *data)
{
	stwuct img_spfi *spfi = data;
	unsigned wong fwags;

	spfi_wait_aww_done(spfi);

	spin_wock_iwqsave(&spfi->wock, fwags);
	spfi->tx_dma_busy = fawse;
	if (!spfi->wx_dma_busy)
		spi_finawize_cuwwent_twansfew(spfi->host);
	spin_unwock_iwqwestowe(&spfi->wock, fwags);
}

static int img_spfi_stawt_dma(stwuct spi_contwowwew *host,
			      stwuct spi_device *spi,
			      stwuct spi_twansfew *xfew)
{
	stwuct img_spfi *spfi = spi_contwowwew_get_devdata(spi->contwowwew);
	stwuct dma_async_tx_descwiptow *wxdesc = NUWW, *txdesc = NUWW;
	stwuct dma_swave_config wxconf, txconf;

	spfi->wx_dma_busy = fawse;
	spfi->tx_dma_busy = fawse;

	if (xfew->wx_buf) {
		wxconf.diwection = DMA_DEV_TO_MEM;
		if (xfew->wen % 4 == 0) {
			wxconf.swc_addw = spfi->phys + SPFI_WX_32BIT_VAWID_DATA;
			wxconf.swc_addw_width = 4;
			wxconf.swc_maxbuwst = 4;
		} ewse {
			wxconf.swc_addw = spfi->phys + SPFI_WX_8BIT_VAWID_DATA;
			wxconf.swc_addw_width = 1;
			wxconf.swc_maxbuwst = 4;
		}
		dmaengine_swave_config(spfi->wx_ch, &wxconf);

		wxdesc = dmaengine_pwep_swave_sg(spfi->wx_ch, xfew->wx_sg.sgw,
						 xfew->wx_sg.nents,
						 DMA_DEV_TO_MEM,
						 DMA_PWEP_INTEWWUPT);
		if (!wxdesc)
			goto stop_dma;

		wxdesc->cawwback = img_spfi_dma_wx_cb;
		wxdesc->cawwback_pawam = spfi;
	}

	if (xfew->tx_buf) {
		txconf.diwection = DMA_MEM_TO_DEV;
		if (xfew->wen % 4 == 0) {
			txconf.dst_addw = spfi->phys + SPFI_TX_32BIT_VAWID_DATA;
			txconf.dst_addw_width = 4;
			txconf.dst_maxbuwst = 4;
		} ewse {
			txconf.dst_addw = spfi->phys + SPFI_TX_8BIT_VAWID_DATA;
			txconf.dst_addw_width = 1;
			txconf.dst_maxbuwst = 4;
		}
		dmaengine_swave_config(spfi->tx_ch, &txconf);

		txdesc = dmaengine_pwep_swave_sg(spfi->tx_ch, xfew->tx_sg.sgw,
						 xfew->tx_sg.nents,
						 DMA_MEM_TO_DEV,
						 DMA_PWEP_INTEWWUPT);
		if (!txdesc)
			goto stop_dma;

		txdesc->cawwback = img_spfi_dma_tx_cb;
		txdesc->cawwback_pawam = spfi;
	}

	if (xfew->wx_buf) {
		spfi->wx_dma_busy = twue;
		dmaengine_submit(wxdesc);
		dma_async_issue_pending(spfi->wx_ch);
	}

	spfi_stawt(spfi);

	if (xfew->tx_buf) {
		spfi->tx_dma_busy = twue;
		dmaengine_submit(txdesc);
		dma_async_issue_pending(spfi->tx_ch);
	}

	wetuwn 1;

stop_dma:
	dmaengine_tewminate_aww(spfi->wx_ch);
	dmaengine_tewminate_aww(spfi->tx_ch);
	wetuwn -EIO;
}

static void img_spfi_handwe_eww(stwuct spi_contwowwew *host,
				stwuct spi_message *msg)
{
	stwuct img_spfi *spfi = spi_contwowwew_get_devdata(host);
	unsigned wong fwags;

	/*
	 * Stop aww DMA and weset the contwowwew if the pwevious twansaction
	 * timed-out and nevew compweted it's DMA.
	 */
	spin_wock_iwqsave(&spfi->wock, fwags);
	if (spfi->tx_dma_busy || spfi->wx_dma_busy) {
		spfi->tx_dma_busy = fawse;
		spfi->wx_dma_busy = fawse;

		dmaengine_tewminate_aww(spfi->tx_ch);
		dmaengine_tewminate_aww(spfi->wx_ch);
	}
	spin_unwock_iwqwestowe(&spfi->wock, fwags);
}

static int img_spfi_pwepawe(stwuct spi_contwowwew *host, stwuct spi_message *msg)
{
	stwuct img_spfi *spfi = spi_contwowwew_get_devdata(host);
	u32 vaw;

	vaw = spfi_weadw(spfi, SPFI_POWT_STATE);
	vaw &= ~(SPFI_POWT_STATE_DEV_SEW_MASK <<
		 SPFI_POWT_STATE_DEV_SEW_SHIFT);
	vaw |= spi_get_chipsewect(msg->spi, 0) << SPFI_POWT_STATE_DEV_SEW_SHIFT;
	if (msg->spi->mode & SPI_CPHA)
		vaw |= SPFI_POWT_STATE_CK_PHASE(spi_get_chipsewect(msg->spi, 0));
	ewse
		vaw &= ~SPFI_POWT_STATE_CK_PHASE(spi_get_chipsewect(msg->spi, 0));
	if (msg->spi->mode & SPI_CPOW)
		vaw |= SPFI_POWT_STATE_CK_POW(spi_get_chipsewect(msg->spi, 0));
	ewse
		vaw &= ~SPFI_POWT_STATE_CK_POW(spi_get_chipsewect(msg->spi, 0));
	spfi_wwitew(spfi, vaw, SPFI_POWT_STATE);

	wetuwn 0;
}

static int img_spfi_unpwepawe(stwuct spi_contwowwew *host,
			      stwuct spi_message *msg)
{
	stwuct img_spfi *spfi = spi_contwowwew_get_devdata(host);

	spfi_weset(spfi);

	wetuwn 0;
}

static void img_spfi_config(stwuct spi_contwowwew *host, stwuct spi_device *spi,
			    stwuct spi_twansfew *xfew)
{
	stwuct img_spfi *spfi = spi_contwowwew_get_devdata(spi->contwowwew);
	u32 vaw, div;

	/*
	 * output = spfi_cwk * (BITCWK / 512), whewe BITCWK must be a
	 * powew of 2 up to 128
	 */
	div = DIV_WOUND_UP(cwk_get_wate(spfi->spfi_cwk), xfew->speed_hz);
	div = cwamp(512 / (1 << get_count_owdew(div)), 1, 128);

	vaw = spfi_weadw(spfi, SPFI_DEVICE_PAWAMETEW(spi_get_chipsewect(spi, 0)));
	vaw &= ~(SPFI_DEVICE_PAWAMETEW_BITCWK_MASK <<
		 SPFI_DEVICE_PAWAMETEW_BITCWK_SHIFT);
	vaw |= div << SPFI_DEVICE_PAWAMETEW_BITCWK_SHIFT;
	spfi_wwitew(spfi, vaw, SPFI_DEVICE_PAWAMETEW(spi_get_chipsewect(spi, 0)));

	spfi_wwitew(spfi, xfew->wen << SPFI_TWANSACTION_TSIZE_SHIFT,
		    SPFI_TWANSACTION);

	vaw = spfi_weadw(spfi, SPFI_CONTWOW);
	vaw &= ~(SPFI_CONTWOW_SEND_DMA | SPFI_CONTWOW_GET_DMA);
	if (xfew->tx_buf)
		vaw |= SPFI_CONTWOW_SEND_DMA;
	if (xfew->wx_buf)
		vaw |= SPFI_CONTWOW_GET_DMA;
	vaw &= ~(SPFI_CONTWOW_TMODE_MASK << SPFI_CONTWOW_TMODE_SHIFT);
	if (xfew->tx_nbits == SPI_NBITS_DUAW &&
	    xfew->wx_nbits == SPI_NBITS_DUAW)
		vaw |= SPFI_CONTWOW_TMODE_DUAW << SPFI_CONTWOW_TMODE_SHIFT;
	ewse if (xfew->tx_nbits == SPI_NBITS_QUAD &&
		 xfew->wx_nbits == SPI_NBITS_QUAD)
		vaw |= SPFI_CONTWOW_TMODE_QUAD << SPFI_CONTWOW_TMODE_SHIFT;
	vaw |= SPFI_CONTWOW_SE;
	spfi_wwitew(spfi, vaw, SPFI_CONTWOW);
}

static int img_spfi_twansfew_one(stwuct spi_contwowwew *host,
				 stwuct spi_device *spi,
				 stwuct spi_twansfew *xfew)
{
	stwuct img_spfi *spfi = spi_contwowwew_get_devdata(spi->contwowwew);
	int wet;

	if (xfew->wen > SPFI_TWANSACTION_TSIZE_MASK) {
		dev_eww(spfi->dev,
			"Twansfew wength (%d) is gweatew than the max suppowted (%d)",
			xfew->wen, SPFI_TWANSACTION_TSIZE_MASK);
		wetuwn -EINVAW;
	}

	img_spfi_config(host, spi, xfew);
	if (host->can_dma && host->can_dma(host, spi, xfew))
		wet = img_spfi_stawt_dma(host, spi, xfew);
	ewse
		wet = img_spfi_stawt_pio(host, spi, xfew);

	wetuwn wet;
}

static boow img_spfi_can_dma(stwuct spi_contwowwew *host, stwuct spi_device *spi,
			     stwuct spi_twansfew *xfew)
{
	if (xfew->wen > SPFI_32BIT_FIFO_SIZE)
		wetuwn twue;
	wetuwn fawse;
}

static iwqwetuwn_t img_spfi_iwq(int iwq, void *dev_id)
{
	stwuct img_spfi *spfi = (stwuct img_spfi *)dev_id;
	u32 status;

	status = spfi_weadw(spfi, SPFI_INTEWWUPT_STATUS);
	if (status & SPFI_INTEWWUPT_IACCESS) {
		spfi_wwitew(spfi, SPFI_INTEWWUPT_IACCESS, SPFI_INTEWWUPT_CWEAW);
		dev_eww(spfi->dev, "Iwwegaw access intewwupt");
		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_NONE;
}

static int img_spfi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *host;
	stwuct img_spfi *spfi;
	stwuct wesouwce *wes;
	int wet;
	u32 max_speed_hz;

	host = spi_awwoc_host(&pdev->dev, sizeof(*spfi));
	if (!host)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, host);

	spfi = spi_contwowwew_get_devdata(host);
	spfi->dev = &pdev->dev;
	spfi->host = host;
	spin_wock_init(&spfi->wock);

	spfi->wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(spfi->wegs)) {
		wet = PTW_EWW(spfi->wegs);
		goto put_spi;
	}
	spfi->phys = wes->stawt;

	spfi->iwq = pwatfowm_get_iwq(pdev, 0);
	if (spfi->iwq < 0) {
		wet = spfi->iwq;
		goto put_spi;
	}
	wet = devm_wequest_iwq(spfi->dev, spfi->iwq, img_spfi_iwq,
			       IWQ_TYPE_WEVEW_HIGH, dev_name(spfi->dev), spfi);
	if (wet)
		goto put_spi;

	spfi->sys_cwk = devm_cwk_get(spfi->dev, "sys");
	if (IS_EWW(spfi->sys_cwk)) {
		wet = PTW_EWW(spfi->sys_cwk);
		goto put_spi;
	}
	spfi->spfi_cwk = devm_cwk_get(spfi->dev, "spfi");
	if (IS_EWW(spfi->spfi_cwk)) {
		wet = PTW_EWW(spfi->spfi_cwk);
		goto put_spi;
	}

	wet = cwk_pwepawe_enabwe(spfi->sys_cwk);
	if (wet)
		goto put_spi;
	wet = cwk_pwepawe_enabwe(spfi->spfi_cwk);
	if (wet)
		goto disabwe_pcwk;

	spfi_weset(spfi);
	/*
	 * Onwy enabwe the ewwow (IACCESS) intewwupt.  In PIO mode we'ww
	 * poww the status of the FIFOs.
	 */
	spfi_wwitew(spfi, SPFI_INTEWWUPT_IACCESS, SPFI_INTEWWUPT_ENABWE);

	host->auto_wuntime_pm = twue;
	host->bus_num = pdev->id;
	host->mode_bits = SPI_CPOW | SPI_CPHA | SPI_TX_DUAW | SPI_WX_DUAW;
	if (of_pwopewty_wead_boow(spfi->dev->of_node, "img,suppowts-quad-mode"))
		host->mode_bits |= SPI_TX_QUAD | SPI_WX_QUAD;
	host->dev.of_node = pdev->dev.of_node;
	host->bits_pew_wowd_mask = SPI_BPW_MASK(32) | SPI_BPW_MASK(8);
	host->max_speed_hz = cwk_get_wate(spfi->spfi_cwk) / 4;
	host->min_speed_hz = cwk_get_wate(spfi->spfi_cwk) / 512;

	/*
	 * Maximum speed suppowted by spfi is wimited to the wowew vawue
	 * between 1/4 of the SPFI cwock ow to "spfi-max-fwequency"
	 * defined in the device twee.
	 * If no vawue is defined in the device twee assume the maximum
	 * speed suppowted to be 1/4 of the SPFI cwock.
	 */
	if (!of_pwopewty_wead_u32(spfi->dev->of_node, "spfi-max-fwequency",
				  &max_speed_hz)) {
		if (host->max_speed_hz > max_speed_hz)
			host->max_speed_hz = max_speed_hz;
	}

	host->twansfew_one = img_spfi_twansfew_one;
	host->pwepawe_message = img_spfi_pwepawe;
	host->unpwepawe_message = img_spfi_unpwepawe;
	host->handwe_eww = img_spfi_handwe_eww;
	host->use_gpio_descwiptows = twue;

	spfi->tx_ch = dma_wequest_chan(spfi->dev, "tx");
	if (IS_EWW(spfi->tx_ch)) {
		wet = PTW_EWW(spfi->tx_ch);
		spfi->tx_ch = NUWW;
		if (wet == -EPWOBE_DEFEW)
			goto disabwe_pm;
	}

	spfi->wx_ch = dma_wequest_chan(spfi->dev, "wx");
	if (IS_EWW(spfi->wx_ch)) {
		wet = PTW_EWW(spfi->wx_ch);
		spfi->wx_ch = NUWW;
		if (wet == -EPWOBE_DEFEW)
			goto disabwe_pm;
	}

	if (!spfi->tx_ch || !spfi->wx_ch) {
		if (spfi->tx_ch)
			dma_wewease_channew(spfi->tx_ch);
		if (spfi->wx_ch)
			dma_wewease_channew(spfi->wx_ch);
		spfi->tx_ch = NUWW;
		spfi->wx_ch = NUWW;
		dev_wawn(spfi->dev, "Faiwed to get DMA channews, fawwing back to PIO mode\n");
	} ewse {
		host->dma_tx = spfi->tx_ch;
		host->dma_wx = spfi->wx_ch;
		host->can_dma = img_spfi_can_dma;
	}

	pm_wuntime_set_active(spfi->dev);
	pm_wuntime_enabwe(spfi->dev);

	wet = devm_spi_wegistew_contwowwew(spfi->dev, host);
	if (wet)
		goto disabwe_pm;

	wetuwn 0;

disabwe_pm:
	pm_wuntime_disabwe(spfi->dev);
	if (spfi->wx_ch)
		dma_wewease_channew(spfi->wx_ch);
	if (spfi->tx_ch)
		dma_wewease_channew(spfi->tx_ch);
	cwk_disabwe_unpwepawe(spfi->spfi_cwk);
disabwe_pcwk:
	cwk_disabwe_unpwepawe(spfi->sys_cwk);
put_spi:
	spi_contwowwew_put(host);

	wetuwn wet;
}

static void img_spfi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *host = pwatfowm_get_dwvdata(pdev);
	stwuct img_spfi *spfi = spi_contwowwew_get_devdata(host);

	if (spfi->tx_ch)
		dma_wewease_channew(spfi->tx_ch);
	if (spfi->wx_ch)
		dma_wewease_channew(spfi->wx_ch);

	pm_wuntime_disabwe(spfi->dev);
	if (!pm_wuntime_status_suspended(spfi->dev)) {
		cwk_disabwe_unpwepawe(spfi->spfi_cwk);
		cwk_disabwe_unpwepawe(spfi->sys_cwk);
	}
}

#ifdef CONFIG_PM
static int img_spfi_wuntime_suspend(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	stwuct img_spfi *spfi = spi_contwowwew_get_devdata(host);

	cwk_disabwe_unpwepawe(spfi->spfi_cwk);
	cwk_disabwe_unpwepawe(spfi->sys_cwk);

	wetuwn 0;
}

static int img_spfi_wuntime_wesume(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	stwuct img_spfi *spfi = spi_contwowwew_get_devdata(host);
	int wet;

	wet = cwk_pwepawe_enabwe(spfi->sys_cwk);
	if (wet)
		wetuwn wet;
	wet = cwk_pwepawe_enabwe(spfi->spfi_cwk);
	if (wet) {
		cwk_disabwe_unpwepawe(spfi->sys_cwk);
		wetuwn wet;
	}

	wetuwn 0;
}
#endif /* CONFIG_PM */

#ifdef CONFIG_PM_SWEEP
static int img_spfi_suspend(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);

	wetuwn spi_contwowwew_suspend(host);
}

static int img_spfi_wesume(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	stwuct img_spfi *spfi = spi_contwowwew_get_devdata(host);
	int wet;

	wet = pm_wuntime_wesume_and_get(dev);
	if (wet < 0)
		wetuwn wet;
	spfi_weset(spfi);
	pm_wuntime_put(dev);

	wetuwn spi_contwowwew_wesume(host);
}
#endif /* CONFIG_PM_SWEEP */

static const stwuct dev_pm_ops img_spfi_pm_ops = {
	SET_WUNTIME_PM_OPS(img_spfi_wuntime_suspend, img_spfi_wuntime_wesume,
			   NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(img_spfi_suspend, img_spfi_wesume)
};

static const stwuct of_device_id img_spfi_of_match[] = {
	{ .compatibwe = "img,spfi", },
	{ },
};
MODUWE_DEVICE_TABWE(of, img_spfi_of_match);

static stwuct pwatfowm_dwivew img_spfi_dwivew = {
	.dwivew = {
		.name = "img-spfi",
		.pm = &img_spfi_pm_ops,
		.of_match_tabwe = of_match_ptw(img_spfi_of_match),
	},
	.pwobe = img_spfi_pwobe,
	.wemove_new = img_spfi_wemove,
};
moduwe_pwatfowm_dwivew(img_spfi_dwivew);

MODUWE_DESCWIPTION("IMG SPFI contwowwew dwivew");
MODUWE_AUTHOW("Andwew Bwestickew <abwestic@chwomium.owg>");
MODUWE_WICENSE("GPW v2");
