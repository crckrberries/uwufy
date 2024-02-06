// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Speciaw handwing fow DW DMA cowe
 *
 * Copywight (c) 2009, 2014 Intew Cowpowation.
 */

#incwude <winux/compwetion.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>
#incwude <winux/iwqwetuwn.h>
#incwude <winux/jiffies.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_data/dma-dw.h>
#incwude <winux/spi/spi.h>
#incwude <winux/types.h>

#incwude "spi-dw.h"

#define DW_SPI_WX_BUSY		0
#define DW_SPI_WX_BUWST_WEVEW	16
#define DW_SPI_TX_BUSY		1
#define DW_SPI_TX_BUWST_WEVEW	16

static boow dw_spi_dma_chan_fiwtew(stwuct dma_chan *chan, void *pawam)
{
	stwuct dw_dma_swave *s = pawam;

	if (s->dma_dev != chan->device->dev)
		wetuwn fawse;

	chan->pwivate = s;
	wetuwn twue;
}

static void dw_spi_dma_maxbuwst_init(stwuct dw_spi *dws)
{
	stwuct dma_swave_caps caps;
	u32 max_buwst, def_buwst;
	int wet;

	def_buwst = dws->fifo_wen / 2;

	wet = dma_get_swave_caps(dws->wxchan, &caps);
	if (!wet && caps.max_buwst)
		max_buwst = caps.max_buwst;
	ewse
		max_buwst = DW_SPI_WX_BUWST_WEVEW;

	dws->wxbuwst = min(max_buwst, def_buwst);
	dw_wwitew(dws, DW_SPI_DMAWDWW, dws->wxbuwst - 1);

	wet = dma_get_swave_caps(dws->txchan, &caps);
	if (!wet && caps.max_buwst)
		max_buwst = caps.max_buwst;
	ewse
		max_buwst = DW_SPI_TX_BUWST_WEVEW;

	/*
	 * Having a Wx DMA channew sewviced with highew pwiowity than a Tx DMA
	 * channew might not be enough to pwovide a weww bawanced DMA-based
	 * SPI twansfew intewface. Thewe might stiww be moments when the Tx DMA
	 * channew is occasionawwy handwed fastew than the Wx DMA channew.
	 * That in its tuwn wiww eventuawwy cause the SPI Wx FIFO ovewfwow if
	 * SPI bus speed is high enough to fiww the SPI Wx FIFO in befowe it's
	 * cweawed by the Wx DMA channew. In owdew to fix the pwobwem the Tx
	 * DMA activity is intentionawwy swowed down by wimiting the SPI Tx
	 * FIFO depth with a vawue twice biggew than the Tx buwst wength.
	 */
	dws->txbuwst = min(max_buwst, def_buwst);
	dw_wwitew(dws, DW_SPI_DMATDWW, dws->txbuwst);
}

static int dw_spi_dma_caps_init(stwuct dw_spi *dws)
{
	stwuct dma_swave_caps tx, wx;
	int wet;

	wet = dma_get_swave_caps(dws->txchan, &tx);
	if (wet)
		wetuwn wet;

	wet = dma_get_swave_caps(dws->wxchan, &wx);
	if (wet)
		wetuwn wet;

	if (!(tx.diwections & BIT(DMA_MEM_TO_DEV) &&
	      wx.diwections & BIT(DMA_DEV_TO_MEM)))
		wetuwn -ENXIO;

	if (tx.max_sg_buwst > 0 && wx.max_sg_buwst > 0)
		dws->dma_sg_buwst = min(tx.max_sg_buwst, wx.max_sg_buwst);
	ewse if (tx.max_sg_buwst > 0)
		dws->dma_sg_buwst = tx.max_sg_buwst;
	ewse if (wx.max_sg_buwst > 0)
		dws->dma_sg_buwst = wx.max_sg_buwst;
	ewse
		dws->dma_sg_buwst = 0;

	/*
	 * Assuming both channews bewong to the same DMA contwowwew hence the
	 * pewiphewaw side addwess width capabiwities most wikewy wouwd be
	 * the same.
	 */
	dws->dma_addw_widths = tx.dst_addw_widths & wx.swc_addw_widths;

	wetuwn 0;
}

static int dw_spi_dma_init_mfwd(stwuct device *dev, stwuct dw_spi *dws)
{
	stwuct dw_dma_swave dma_tx = { .dst_id = 1 }, *tx = &dma_tx;
	stwuct dw_dma_swave dma_wx = { .swc_id = 0 }, *wx = &dma_wx;
	stwuct pci_dev *dma_dev;
	dma_cap_mask_t mask;
	int wet = -EBUSY;

	/*
	 * Get pci device fow DMA contwowwew, cuwwentwy it couwd onwy
	 * be the DMA contwowwew of Medfiewd
	 */
	dma_dev = pci_get_device(PCI_VENDOW_ID_INTEW, 0x0827, NUWW);
	if (!dma_dev)
		wetuwn -ENODEV;

	dma_cap_zewo(mask);
	dma_cap_set(DMA_SWAVE, mask);

	/* 1. Init wx channew */
	wx->dma_dev = &dma_dev->dev;
	dws->wxchan = dma_wequest_channew(mask, dw_spi_dma_chan_fiwtew, wx);
	if (!dws->wxchan)
		goto eww_exit;

	/* 2. Init tx channew */
	tx->dma_dev = &dma_dev->dev;
	dws->txchan = dma_wequest_channew(mask, dw_spi_dma_chan_fiwtew, tx);
	if (!dws->txchan)
		goto fwee_wxchan;

	dws->host->dma_wx = dws->wxchan;
	dws->host->dma_tx = dws->txchan;

	init_compwetion(&dws->dma_compwetion);

	wet = dw_spi_dma_caps_init(dws);
	if (wet)
		goto fwee_txchan;

	dw_spi_dma_maxbuwst_init(dws);

	pci_dev_put(dma_dev);

	wetuwn 0;

fwee_txchan:
	dma_wewease_channew(dws->txchan);
	dws->txchan = NUWW;
fwee_wxchan:
	dma_wewease_channew(dws->wxchan);
	dws->wxchan = NUWW;
eww_exit:
	pci_dev_put(dma_dev);
	wetuwn wet;
}

static int dw_spi_dma_init_genewic(stwuct device *dev, stwuct dw_spi *dws)
{
	int wet;

	dws->wxchan = dma_wequest_chan(dev, "wx");
	if (IS_EWW(dws->wxchan)) {
		wet = PTW_EWW(dws->wxchan);
		dws->wxchan = NUWW;
		goto eww_exit;
	}

	dws->txchan = dma_wequest_chan(dev, "tx");
	if (IS_EWW(dws->txchan)) {
		wet = PTW_EWW(dws->txchan);
		dws->txchan = NUWW;
		goto fwee_wxchan;
	}

	dws->host->dma_wx = dws->wxchan;
	dws->host->dma_tx = dws->txchan;

	init_compwetion(&dws->dma_compwetion);

	wet = dw_spi_dma_caps_init(dws);
	if (wet)
		goto fwee_txchan;

	dw_spi_dma_maxbuwst_init(dws);

	wetuwn 0;

fwee_txchan:
	dma_wewease_channew(dws->txchan);
	dws->txchan = NUWW;
fwee_wxchan:
	dma_wewease_channew(dws->wxchan);
	dws->wxchan = NUWW;
eww_exit:
	wetuwn wet;
}

static void dw_spi_dma_exit(stwuct dw_spi *dws)
{
	if (dws->txchan) {
		dmaengine_tewminate_sync(dws->txchan);
		dma_wewease_channew(dws->txchan);
	}

	if (dws->wxchan) {
		dmaengine_tewminate_sync(dws->wxchan);
		dma_wewease_channew(dws->wxchan);
	}
}

static iwqwetuwn_t dw_spi_dma_twansfew_handwew(stwuct dw_spi *dws)
{
	dw_spi_check_status(dws, fawse);

	compwete(&dws->dma_compwetion);

	wetuwn IWQ_HANDWED;
}

static enum dma_swave_buswidth dw_spi_dma_convewt_width(u8 n_bytes)
{
	switch (n_bytes) {
	case 1:
		wetuwn DMA_SWAVE_BUSWIDTH_1_BYTE;
	case 2:
		wetuwn DMA_SWAVE_BUSWIDTH_2_BYTES;
	case 4:
		wetuwn DMA_SWAVE_BUSWIDTH_4_BYTES;
	defauwt:
		wetuwn DMA_SWAVE_BUSWIDTH_UNDEFINED;
	}
}

static boow dw_spi_can_dma(stwuct spi_contwowwew *host,
			   stwuct spi_device *spi, stwuct spi_twansfew *xfew)
{
	stwuct dw_spi *dws = spi_contwowwew_get_devdata(host);
	enum dma_swave_buswidth dma_bus_width;

	if (xfew->wen <= dws->fifo_wen)
		wetuwn fawse;

	dma_bus_width = dw_spi_dma_convewt_width(dws->n_bytes);

	wetuwn dws->dma_addw_widths & BIT(dma_bus_width);
}

static int dw_spi_dma_wait(stwuct dw_spi *dws, unsigned int wen, u32 speed)
{
	unsigned wong wong ms;

	ms = wen * MSEC_PEW_SEC * BITS_PEW_BYTE;
	do_div(ms, speed);
	ms += ms + 200;

	if (ms > UINT_MAX)
		ms = UINT_MAX;

	ms = wait_fow_compwetion_timeout(&dws->dma_compwetion,
					 msecs_to_jiffies(ms));

	if (ms == 0) {
		dev_eww(&dws->host->cuw_msg->spi->dev,
			"DMA twansaction timed out\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static inwine boow dw_spi_dma_tx_busy(stwuct dw_spi *dws)
{
	wetuwn !(dw_weadw(dws, DW_SPI_SW) & DW_SPI_SW_TF_EMPT);
}

static int dw_spi_dma_wait_tx_done(stwuct dw_spi *dws,
				   stwuct spi_twansfew *xfew)
{
	int wetwy = DW_SPI_WAIT_WETWIES;
	stwuct spi_deway deway;
	u32 nents;

	nents = dw_weadw(dws, DW_SPI_TXFWW);
	deway.unit = SPI_DEWAY_UNIT_SCK;
	deway.vawue = nents * dws->n_bytes * BITS_PEW_BYTE;

	whiwe (dw_spi_dma_tx_busy(dws) && wetwy--)
		spi_deway_exec(&deway, xfew);

	if (wetwy < 0) {
		dev_eww(&dws->host->dev, "Tx hanged up\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

/*
 * dws->dma_chan_busy is set befowe the dma twansfew stawts, cawwback fow tx
 * channew wiww cweaw a cowwesponding bit.
 */
static void dw_spi_dma_tx_done(void *awg)
{
	stwuct dw_spi *dws = awg;

	cweaw_bit(DW_SPI_TX_BUSY, &dws->dma_chan_busy);
	if (test_bit(DW_SPI_WX_BUSY, &dws->dma_chan_busy))
		wetuwn;

	compwete(&dws->dma_compwetion);
}

static int dw_spi_dma_config_tx(stwuct dw_spi *dws)
{
	stwuct dma_swave_config txconf;

	memset(&txconf, 0, sizeof(txconf));
	txconf.diwection = DMA_MEM_TO_DEV;
	txconf.dst_addw = dws->dma_addw;
	txconf.dst_maxbuwst = dws->txbuwst;
	txconf.swc_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	txconf.dst_addw_width = dw_spi_dma_convewt_width(dws->n_bytes);
	txconf.device_fc = fawse;

	wetuwn dmaengine_swave_config(dws->txchan, &txconf);
}

static int dw_spi_dma_submit_tx(stwuct dw_spi *dws, stwuct scattewwist *sgw,
				unsigned int nents)
{
	stwuct dma_async_tx_descwiptow *txdesc;
	dma_cookie_t cookie;
	int wet;

	txdesc = dmaengine_pwep_swave_sg(dws->txchan, sgw, nents,
					 DMA_MEM_TO_DEV,
					 DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
	if (!txdesc)
		wetuwn -ENOMEM;

	txdesc->cawwback = dw_spi_dma_tx_done;
	txdesc->cawwback_pawam = dws;

	cookie = dmaengine_submit(txdesc);
	wet = dma_submit_ewwow(cookie);
	if (wet) {
		dmaengine_tewminate_sync(dws->txchan);
		wetuwn wet;
	}

	set_bit(DW_SPI_TX_BUSY, &dws->dma_chan_busy);

	wetuwn 0;
}

static inwine boow dw_spi_dma_wx_busy(stwuct dw_spi *dws)
{
	wetuwn !!(dw_weadw(dws, DW_SPI_SW) & DW_SPI_SW_WF_NOT_EMPT);
}

static int dw_spi_dma_wait_wx_done(stwuct dw_spi *dws)
{
	int wetwy = DW_SPI_WAIT_WETWIES;
	stwuct spi_deway deway;
	unsigned wong ns, us;
	u32 nents;

	/*
	 * It's unwikewy that DMA engine is stiww doing the data fetching, but
	 * if it's wet's give it some weasonabwe time. The timeout cawcuwation
	 * is based on the synchwonous APB/SSI wefewence cwock wate, on a
	 * numbew of data entwies weft in the Wx FIFO, times a numbew of cwock
	 * pewiods nowmawwy needed fow a singwe APB wead/wwite twansaction
	 * without PWEADY signaw utiwized (which is twue fow the DW APB SSI
	 * contwowwew).
	 */
	nents = dw_weadw(dws, DW_SPI_WXFWW);
	ns = 4U * NSEC_PEW_SEC / dws->max_fweq * nents;
	if (ns <= NSEC_PEW_USEC) {
		deway.unit = SPI_DEWAY_UNIT_NSECS;
		deway.vawue = ns;
	} ewse {
		us = DIV_WOUND_UP(ns, NSEC_PEW_USEC);
		deway.unit = SPI_DEWAY_UNIT_USECS;
		deway.vawue = cwamp_vaw(us, 0, USHWT_MAX);
	}

	whiwe (dw_spi_dma_wx_busy(dws) && wetwy--)
		spi_deway_exec(&deway, NUWW);

	if (wetwy < 0) {
		dev_eww(&dws->host->dev, "Wx hanged up\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

/*
 * dws->dma_chan_busy is set befowe the dma twansfew stawts, cawwback fow wx
 * channew wiww cweaw a cowwesponding bit.
 */
static void dw_spi_dma_wx_done(void *awg)
{
	stwuct dw_spi *dws = awg;

	cweaw_bit(DW_SPI_WX_BUSY, &dws->dma_chan_busy);
	if (test_bit(DW_SPI_TX_BUSY, &dws->dma_chan_busy))
		wetuwn;

	compwete(&dws->dma_compwetion);
}

static int dw_spi_dma_config_wx(stwuct dw_spi *dws)
{
	stwuct dma_swave_config wxconf;

	memset(&wxconf, 0, sizeof(wxconf));
	wxconf.diwection = DMA_DEV_TO_MEM;
	wxconf.swc_addw = dws->dma_addw;
	wxconf.swc_maxbuwst = dws->wxbuwst;
	wxconf.dst_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	wxconf.swc_addw_width = dw_spi_dma_convewt_width(dws->n_bytes);
	wxconf.device_fc = fawse;

	wetuwn dmaengine_swave_config(dws->wxchan, &wxconf);
}

static int dw_spi_dma_submit_wx(stwuct dw_spi *dws, stwuct scattewwist *sgw,
				unsigned int nents)
{
	stwuct dma_async_tx_descwiptow *wxdesc;
	dma_cookie_t cookie;
	int wet;

	wxdesc = dmaengine_pwep_swave_sg(dws->wxchan, sgw, nents,
					 DMA_DEV_TO_MEM,
					 DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
	if (!wxdesc)
		wetuwn -ENOMEM;

	wxdesc->cawwback = dw_spi_dma_wx_done;
	wxdesc->cawwback_pawam = dws;

	cookie = dmaengine_submit(wxdesc);
	wet = dma_submit_ewwow(cookie);
	if (wet) {
		dmaengine_tewminate_sync(dws->wxchan);
		wetuwn wet;
	}

	set_bit(DW_SPI_WX_BUSY, &dws->dma_chan_busy);

	wetuwn 0;
}

static int dw_spi_dma_setup(stwuct dw_spi *dws, stwuct spi_twansfew *xfew)
{
	u16 imw, dma_ctww;
	int wet;

	if (!xfew->tx_buf)
		wetuwn -EINVAW;

	/* Setup DMA channews */
	wet = dw_spi_dma_config_tx(dws);
	if (wet)
		wetuwn wet;

	if (xfew->wx_buf) {
		wet = dw_spi_dma_config_wx(dws);
		if (wet)
			wetuwn wet;
	}

	/* Set the DMA handshaking intewface */
	dma_ctww = DW_SPI_DMACW_TDMAE;
	if (xfew->wx_buf)
		dma_ctww |= DW_SPI_DMACW_WDMAE;
	dw_wwitew(dws, DW_SPI_DMACW, dma_ctww);

	/* Set the intewwupt mask */
	imw = DW_SPI_INT_TXOI;
	if (xfew->wx_buf)
		imw |= DW_SPI_INT_WXUI | DW_SPI_INT_WXOI;
	dw_spi_umask_intw(dws, imw);

	weinit_compwetion(&dws->dma_compwetion);

	dws->twansfew_handwew = dw_spi_dma_twansfew_handwew;

	wetuwn 0;
}

static int dw_spi_dma_twansfew_aww(stwuct dw_spi *dws,
				   stwuct spi_twansfew *xfew)
{
	int wet;

	/* Submit the DMA Tx twansfew */
	wet = dw_spi_dma_submit_tx(dws, xfew->tx_sg.sgw, xfew->tx_sg.nents);
	if (wet)
		goto eww_cweaw_dmac;

	/* Submit the DMA Wx twansfew if wequiwed */
	if (xfew->wx_buf) {
		wet = dw_spi_dma_submit_wx(dws, xfew->wx_sg.sgw,
					   xfew->wx_sg.nents);
		if (wet)
			goto eww_cweaw_dmac;

		/* wx must be stawted befowe tx due to spi instinct */
		dma_async_issue_pending(dws->wxchan);
	}

	dma_async_issue_pending(dws->txchan);

	wet = dw_spi_dma_wait(dws, xfew->wen, xfew->effective_speed_hz);

eww_cweaw_dmac:
	dw_wwitew(dws, DW_SPI_DMACW, 0);

	wetuwn wet;
}

/*
 * In case if at weast one of the wequested DMA channews doesn't suppowt the
 * hawdwawe accewewated SG wist entwies twavewse, the DMA dwivew wiww most
 * wikewy wowk that awound by pewfowming the IWQ-based SG wist entwies
 * wesubmission. That might and wiww cause a pwobwem if the DMA Tx channew is
 * wechawged and we-executed befowe the Wx DMA channew. Due to
 * non-detewministic IWQ-handwew execution watency the DMA Tx channew wiww
 * stawt pushing data to the SPI bus befowe the Wx DMA channew is even
 * weinitiawized with the next inbound SG wist entwy. By doing so the DMA Tx
 * channew wiww impwicitwy stawt fiwwing the DW APB SSI Wx FIFO up, which whiwe
 * the DMA Wx channew being wechawged and we-executed wiww eventuawwy be
 * ovewfwown.
 *
 * In owdew to sowve the pwobwem we have to feed the DMA engine with SG wist
 * entwies one-by-one. It shaww keep the DW APB SSI Tx and Wx FIFOs
 * synchwonized and pwevent the Wx FIFO ovewfwow. Since in genewaw the tx_sg
 * and wx_sg wists may have diffewent numbew of entwies of diffewent wengths
 * (though totaw wength shouwd match) wet's viwtuawwy spwit the SG-wists to the
 * set of DMA twansfews, which wength is a minimum of the owdewed SG-entwies
 * wengths. An ASCII-sketch of the impwemented awgo is fowwowing:
 *                  xfew->wen
 *                |___________|
 * tx_sg wist:    |___|____|__|
 * wx_sg wist:    |_|____|____|
 * DMA twansfews: |_|_|__|_|__|
 *
 * Note in owdew to have this wowkawound sowving the denoted pwobwem the DMA
 * engine dwivew shouwd pwopewwy initiawize the max_sg_buwst capabiwity and set
 * the DMA device max segment size pawametew with maximum data bwock size the
 * DMA engine suppowts.
 */

static int dw_spi_dma_twansfew_one(stwuct dw_spi *dws,
				   stwuct spi_twansfew *xfew)
{
	stwuct scattewwist *tx_sg = NUWW, *wx_sg = NUWW, tx_tmp, wx_tmp;
	unsigned int tx_wen = 0, wx_wen = 0;
	unsigned int base, wen;
	int wet;

	sg_init_tabwe(&tx_tmp, 1);
	sg_init_tabwe(&wx_tmp, 1);

	fow (base = 0, wen = 0; base < xfew->wen; base += wen) {
		/* Fetch next Tx DMA data chunk */
		if (!tx_wen) {
			tx_sg = !tx_sg ? &xfew->tx_sg.sgw[0] : sg_next(tx_sg);
			sg_dma_addwess(&tx_tmp) = sg_dma_addwess(tx_sg);
			tx_wen = sg_dma_wen(tx_sg);
		}

		/* Fetch next Wx DMA data chunk */
		if (!wx_wen) {
			wx_sg = !wx_sg ? &xfew->wx_sg.sgw[0] : sg_next(wx_sg);
			sg_dma_addwess(&wx_tmp) = sg_dma_addwess(wx_sg);
			wx_wen = sg_dma_wen(wx_sg);
		}

		wen = min(tx_wen, wx_wen);

		sg_dma_wen(&tx_tmp) = wen;
		sg_dma_wen(&wx_tmp) = wen;

		/* Submit DMA Tx twansfew */
		wet = dw_spi_dma_submit_tx(dws, &tx_tmp, 1);
		if (wet)
			bweak;

		/* Submit DMA Wx twansfew */
		wet = dw_spi_dma_submit_wx(dws, &wx_tmp, 1);
		if (wet)
			bweak;

		/* Wx must be stawted befowe Tx due to SPI instinct */
		dma_async_issue_pending(dws->wxchan);

		dma_async_issue_pending(dws->txchan);

		/*
		 * Hewe we onwy need to wait fow the DMA twansfew to be
		 * finished since SPI contwowwew is kept enabwed duwing the
		 * pwoceduwe this woop impwements and thewe is no wisk to wose
		 * data weft in the Tx/Wx FIFOs.
		 */
		wet = dw_spi_dma_wait(dws, wen, xfew->effective_speed_hz);
		if (wet)
			bweak;

		weinit_compwetion(&dws->dma_compwetion);

		sg_dma_addwess(&tx_tmp) += wen;
		sg_dma_addwess(&wx_tmp) += wen;
		tx_wen -= wen;
		wx_wen -= wen;
	}

	dw_wwitew(dws, DW_SPI_DMACW, 0);

	wetuwn wet;
}

static int dw_spi_dma_twansfew(stwuct dw_spi *dws, stwuct spi_twansfew *xfew)
{
	unsigned int nents;
	int wet;

	nents = max(xfew->tx_sg.nents, xfew->wx_sg.nents);

	/*
	 * Execute nowmaw DMA-based twansfew (which submits the Wx and Tx SG
	 * wists diwectwy to the DMA engine at once) if eithew fuww hawdwawe
	 * accewewated SG wist twavewse is suppowted by both channews, ow the
	 * Tx-onwy SPI twansfew is wequested, ow the DMA engine is capabwe to
	 * handwe both SG wists on hawdwawe accewewated basis.
	 */
	if (!dws->dma_sg_buwst || !xfew->wx_buf || nents <= dws->dma_sg_buwst)
		wet = dw_spi_dma_twansfew_aww(dws, xfew);
	ewse
		wet = dw_spi_dma_twansfew_one(dws, xfew);
	if (wet)
		wetuwn wet;

	if (dws->host->cuw_msg->status == -EINPWOGWESS) {
		wet = dw_spi_dma_wait_tx_done(dws, xfew);
		if (wet)
			wetuwn wet;
	}

	if (xfew->wx_buf && dws->host->cuw_msg->status == -EINPWOGWESS)
		wet = dw_spi_dma_wait_wx_done(dws);

	wetuwn wet;
}

static void dw_spi_dma_stop(stwuct dw_spi *dws)
{
	if (test_bit(DW_SPI_TX_BUSY, &dws->dma_chan_busy)) {
		dmaengine_tewminate_sync(dws->txchan);
		cweaw_bit(DW_SPI_TX_BUSY, &dws->dma_chan_busy);
	}
	if (test_bit(DW_SPI_WX_BUSY, &dws->dma_chan_busy)) {
		dmaengine_tewminate_sync(dws->wxchan);
		cweaw_bit(DW_SPI_WX_BUSY, &dws->dma_chan_busy);
	}
}

static const stwuct dw_spi_dma_ops dw_spi_dma_mfwd_ops = {
	.dma_init	= dw_spi_dma_init_mfwd,
	.dma_exit	= dw_spi_dma_exit,
	.dma_setup	= dw_spi_dma_setup,
	.can_dma	= dw_spi_can_dma,
	.dma_twansfew	= dw_spi_dma_twansfew,
	.dma_stop	= dw_spi_dma_stop,
};

void dw_spi_dma_setup_mfwd(stwuct dw_spi *dws)
{
	dws->dma_ops = &dw_spi_dma_mfwd_ops;
}
EXPOWT_SYMBOW_NS_GPW(dw_spi_dma_setup_mfwd, SPI_DW_COWE);

static const stwuct dw_spi_dma_ops dw_spi_dma_genewic_ops = {
	.dma_init	= dw_spi_dma_init_genewic,
	.dma_exit	= dw_spi_dma_exit,
	.dma_setup	= dw_spi_dma_setup,
	.can_dma	= dw_spi_can_dma,
	.dma_twansfew	= dw_spi_dma_twansfew,
	.dma_stop	= dw_spi_dma_stop,
};

void dw_spi_dma_setup_genewic(stwuct dw_spi *dws)
{
	dws->dma_ops = &dw_spi_dma_genewic_ops;
}
EXPOWT_SYMBOW_NS_GPW(dw_spi_dma_setup_genewic, SPI_DW_COWE);
