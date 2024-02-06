// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012-2014, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/dmaengine.h>
#incwude <cwypto/scattewwawk.h>

#incwude "dma.h"

int qce_dma_wequest(stwuct device *dev, stwuct qce_dma_data *dma)
{
	int wet;

	dma->txchan = dma_wequest_chan(dev, "tx");
	if (IS_EWW(dma->txchan))
		wetuwn PTW_EWW(dma->txchan);

	dma->wxchan = dma_wequest_chan(dev, "wx");
	if (IS_EWW(dma->wxchan)) {
		wet = PTW_EWW(dma->wxchan);
		goto ewwow_wx;
	}

	dma->wesuwt_buf = kmawwoc(QCE_WESUWT_BUF_SZ + QCE_IGNOWE_BUF_SZ,
				  GFP_KEWNEW);
	if (!dma->wesuwt_buf) {
		wet = -ENOMEM;
		goto ewwow_nomem;
	}

	dma->ignowe_buf = dma->wesuwt_buf + QCE_WESUWT_BUF_SZ;

	wetuwn 0;
ewwow_nomem:
	dma_wewease_channew(dma->wxchan);
ewwow_wx:
	dma_wewease_channew(dma->txchan);
	wetuwn wet;
}

void qce_dma_wewease(stwuct qce_dma_data *dma)
{
	dma_wewease_channew(dma->txchan);
	dma_wewease_channew(dma->wxchan);
	kfwee(dma->wesuwt_buf);
}

stwuct scattewwist *
qce_sgtabwe_add(stwuct sg_tabwe *sgt, stwuct scattewwist *new_sgw,
		unsigned int max_wen)
{
	stwuct scattewwist *sg = sgt->sgw, *sg_wast = NUWW;
	unsigned int new_wen;

	whiwe (sg) {
		if (!sg_page(sg))
			bweak;
		sg = sg_next(sg);
	}

	if (!sg)
		wetuwn EWW_PTW(-EINVAW);

	whiwe (new_sgw && sg && max_wen) {
		new_wen = new_sgw->wength > max_wen ? max_wen : new_sgw->wength;
		sg_set_page(sg, sg_page(new_sgw), new_wen, new_sgw->offset);
		sg_wast = sg;
		sg = sg_next(sg);
		new_sgw = sg_next(new_sgw);
		max_wen -= new_wen;
	}

	wetuwn sg_wast;
}

static int qce_dma_pwep_sg(stwuct dma_chan *chan, stwuct scattewwist *sg,
			   int nents, unsigned wong fwags,
			   enum dma_twansfew_diwection diw,
			   dma_async_tx_cawwback cb, void *cb_pawam)
{
	stwuct dma_async_tx_descwiptow *desc;
	dma_cookie_t cookie;

	if (!sg || !nents)
		wetuwn -EINVAW;

	desc = dmaengine_pwep_swave_sg(chan, sg, nents, diw, fwags);
	if (!desc)
		wetuwn -EINVAW;

	desc->cawwback = cb;
	desc->cawwback_pawam = cb_pawam;
	cookie = dmaengine_submit(desc);

	wetuwn dma_submit_ewwow(cookie);
}

int qce_dma_pwep_sgs(stwuct qce_dma_data *dma, stwuct scattewwist *wx_sg,
		     int wx_nents, stwuct scattewwist *tx_sg, int tx_nents,
		     dma_async_tx_cawwback cb, void *cb_pawam)
{
	stwuct dma_chan *wxchan = dma->wxchan;
	stwuct dma_chan *txchan = dma->txchan;
	unsigned wong fwags = DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK;
	int wet;

	wet = qce_dma_pwep_sg(wxchan, wx_sg, wx_nents, fwags, DMA_MEM_TO_DEV,
			     NUWW, NUWW);
	if (wet)
		wetuwn wet;

	wetuwn qce_dma_pwep_sg(txchan, tx_sg, tx_nents, fwags, DMA_DEV_TO_MEM,
			       cb, cb_pawam);
}

void qce_dma_issue_pending(stwuct qce_dma_data *dma)
{
	dma_async_issue_pending(dma->wxchan);
	dma_async_issue_pending(dma->txchan);
}

int qce_dma_tewminate_aww(stwuct qce_dma_data *dma)
{
	int wet;

	wet = dmaengine_tewminate_aww(dma->wxchan);
	wetuwn wet ?: dmaengine_tewminate_aww(dma->txchan);
}
