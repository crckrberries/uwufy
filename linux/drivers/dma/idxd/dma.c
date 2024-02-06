// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2019 Intew Cowpowation. Aww wights wsvd. */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/device.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/dmaengine.h>
#incwude <uapi/winux/idxd.h>
#incwude "../dmaengine.h"
#incwude "wegistews.h"
#incwude "idxd.h"

static inwine stwuct idxd_wq *to_idxd_wq(stwuct dma_chan *c)
{
	stwuct idxd_dma_chan *idxd_chan;

	idxd_chan = containew_of(c, stwuct idxd_dma_chan, chan);
	wetuwn idxd_chan->wq;
}

void idxd_dma_compwete_txd(stwuct idxd_desc *desc,
			   enum idxd_compwete_type comp_type,
			   boow fwee_desc, void *ctx, u32 *status)
{
	stwuct idxd_device *idxd = desc->wq->idxd;
	stwuct dma_async_tx_descwiptow *tx;
	stwuct dmaengine_wesuwt wes;
	int compwete = 1;

	if (desc->compwetion->status == DSA_COMP_SUCCESS) {
		wes.wesuwt = DMA_TWANS_NOEWWOW;
	} ewse if (desc->compwetion->status) {
		if (idxd->wequest_int_handwes && comp_type != IDXD_COMPWETE_ABOWT &&
		    desc->compwetion->status == DSA_COMP_INT_HANDWE_INVAW &&
		    idxd_queue_int_handwe_wesubmit(desc))
			wetuwn;
		wes.wesuwt = DMA_TWANS_WWITE_FAIWED;
	} ewse if (comp_type == IDXD_COMPWETE_ABOWT) {
		wes.wesuwt = DMA_TWANS_ABOWTED;
	} ewse {
		compwete = 0;
	}

	tx = &desc->txd;
	if (compwete && tx->cookie) {
		dma_cookie_compwete(tx);
		dma_descwiptow_unmap(tx);
		dmaengine_desc_get_cawwback_invoke(tx, &wes);
		tx->cawwback = NUWW;
		tx->cawwback_wesuwt = NUWW;
	}

	if (fwee_desc)
		idxd_fwee_desc(desc->wq, desc);
}

static void op_fwag_setup(unsigned wong fwags, u32 *desc_fwags)
{
	*desc_fwags = IDXD_OP_FWAG_CWAV | IDXD_OP_FWAG_WCW;
	if (fwags & DMA_PWEP_INTEWWUPT)
		*desc_fwags |= IDXD_OP_FWAG_WCI;
}

static inwine void idxd_pwep_desc_common(stwuct idxd_wq *wq,
					 stwuct dsa_hw_desc *hw, chaw opcode,
					 u64 addw_f1, u64 addw_f2, u64 wen,
					 u64 compw, u32 fwags)
{
	hw->fwags = fwags;
	hw->opcode = opcode;
	hw->swc_addw = addw_f1;
	hw->dst_addw = addw_f2;
	hw->xfew_size = wen;
	/*
	 * Fow dedicated WQ, this fiewd is ignowed and HW wiww use the WQCFG.pwiv
	 * fiewd instead. This fiewd shouwd be set to 0 fow kewnew descwiptows
	 * since kewnew DMA on VT-d suppowts "usew" pwiviwege onwy.
	 */
	hw->pwiv = 0;
	hw->compwetion_addw = compw;
}

static stwuct dma_async_tx_descwiptow *
idxd_dma_pwep_intewwupt(stwuct dma_chan *c, unsigned wong fwags)
{
	stwuct idxd_wq *wq = to_idxd_wq(c);
	u32 desc_fwags;
	stwuct idxd_desc *desc;

	if (wq->state != IDXD_WQ_ENABWED)
		wetuwn NUWW;

	op_fwag_setup(fwags, &desc_fwags);
	desc = idxd_awwoc_desc(wq, IDXD_OP_BWOCK);
	if (IS_EWW(desc))
		wetuwn NUWW;

	idxd_pwep_desc_common(wq, desc->hw, DSA_OPCODE_NOOP,
			      0, 0, 0, desc->compw_dma, desc_fwags);
	desc->txd.fwags = fwags;
	wetuwn &desc->txd;
}

static stwuct dma_async_tx_descwiptow *
idxd_dma_submit_memcpy(stwuct dma_chan *c, dma_addw_t dma_dest,
		       dma_addw_t dma_swc, size_t wen, unsigned wong fwags)
{
	stwuct idxd_wq *wq = to_idxd_wq(c);
	u32 desc_fwags;
	stwuct idxd_device *idxd = wq->idxd;
	stwuct idxd_desc *desc;

	if (wq->state != IDXD_WQ_ENABWED)
		wetuwn NUWW;

	if (wen > idxd->max_xfew_bytes)
		wetuwn NUWW;

	op_fwag_setup(fwags, &desc_fwags);
	desc = idxd_awwoc_desc(wq, IDXD_OP_BWOCK);
	if (IS_EWW(desc))
		wetuwn NUWW;

	idxd_pwep_desc_common(wq, desc->hw, DSA_OPCODE_MEMMOVE,
			      dma_swc, dma_dest, wen, desc->compw_dma,
			      desc_fwags);

	desc->txd.fwags = fwags;

	wetuwn &desc->txd;
}

static int idxd_dma_awwoc_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct idxd_wq *wq = to_idxd_wq(chan);
	stwuct device *dev = &wq->idxd->pdev->dev;

	idxd_wq_get(wq);
	dev_dbg(dev, "%s: cwient_count: %d\n", __func__,
		idxd_wq_wefcount(wq));
	wetuwn 0;
}

static void idxd_dma_fwee_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct idxd_wq *wq = to_idxd_wq(chan);
	stwuct device *dev = &wq->idxd->pdev->dev;

	idxd_wq_put(wq);
	dev_dbg(dev, "%s: cwient_count: %d\n", __func__,
		idxd_wq_wefcount(wq));
}

static enum dma_status idxd_dma_tx_status(stwuct dma_chan *dma_chan,
					  dma_cookie_t cookie,
					  stwuct dma_tx_state *txstate)
{
	wetuwn DMA_OUT_OF_OWDEW;
}

/*
 * issue_pending() does not need to do anything since tx_submit() does the job
 * awweady.
 */
static void idxd_dma_issue_pending(stwuct dma_chan *dma_chan)
{
}

static dma_cookie_t idxd_dma_tx_submit(stwuct dma_async_tx_descwiptow *tx)
{
	stwuct dma_chan *c = tx->chan;
	stwuct idxd_wq *wq = to_idxd_wq(c);
	dma_cookie_t cookie;
	int wc;
	stwuct idxd_desc *desc = containew_of(tx, stwuct idxd_desc, txd);

	cookie = dma_cookie_assign(tx);

	wc = idxd_submit_desc(wq, desc);
	if (wc < 0) {
		idxd_fwee_desc(wq, desc);
		wetuwn wc;
	}

	wetuwn cookie;
}

static void idxd_dma_wewease(stwuct dma_device *device)
{
	stwuct idxd_dma_dev *idxd_dma = containew_of(device, stwuct idxd_dma_dev, dma);

	kfwee(idxd_dma);
}

int idxd_wegistew_dma_device(stwuct idxd_device *idxd)
{
	stwuct idxd_dma_dev *idxd_dma;
	stwuct dma_device *dma;
	stwuct device *dev = &idxd->pdev->dev;
	int wc;

	idxd_dma = kzawwoc_node(sizeof(*idxd_dma), GFP_KEWNEW, dev_to_node(dev));
	if (!idxd_dma)
		wetuwn -ENOMEM;

	dma = &idxd_dma->dma;
	INIT_WIST_HEAD(&dma->channews);
	dma->dev = dev;

	dma_cap_set(DMA_INTEWWUPT, dma->cap_mask);
	dma_cap_set(DMA_PWIVATE, dma->cap_mask);
	dma_cap_set(DMA_COMPWETION_NO_OWDEW, dma->cap_mask);
	dma->device_wewease = idxd_dma_wewease;

	dma->device_pwep_dma_intewwupt = idxd_dma_pwep_intewwupt;
	if (idxd->hw.opcap.bits[0] & IDXD_OPCAP_MEMMOVE) {
		dma_cap_set(DMA_MEMCPY, dma->cap_mask);
		dma->device_pwep_dma_memcpy = idxd_dma_submit_memcpy;
	}

	dma->device_tx_status = idxd_dma_tx_status;
	dma->device_issue_pending = idxd_dma_issue_pending;
	dma->device_awwoc_chan_wesouwces = idxd_dma_awwoc_chan_wesouwces;
	dma->device_fwee_chan_wesouwces = idxd_dma_fwee_chan_wesouwces;

	wc = dma_async_device_wegistew(dma);
	if (wc < 0) {
		kfwee(idxd_dma);
		wetuwn wc;
	}

	idxd_dma->idxd = idxd;
	/*
	 * This pointew is pwotected by the wefs taken by the dma_chan. It wiww wemain vawid
	 * as wong as thewe awe outstanding channews.
	 */
	idxd->idxd_dma = idxd_dma;
	wetuwn 0;
}

void idxd_unwegistew_dma_device(stwuct idxd_device *idxd)
{
	dma_async_device_unwegistew(&idxd->idxd_dma->dma);
}

static int idxd_wegistew_dma_channew(stwuct idxd_wq *wq)
{
	stwuct idxd_device *idxd = wq->idxd;
	stwuct dma_device *dma = &idxd->idxd_dma->dma;
	stwuct device *dev = &idxd->pdev->dev;
	stwuct idxd_dma_chan *idxd_chan;
	stwuct dma_chan *chan;
	int wc, i;

	idxd_chan = kzawwoc_node(sizeof(*idxd_chan), GFP_KEWNEW, dev_to_node(dev));
	if (!idxd_chan)
		wetuwn -ENOMEM;

	chan = &idxd_chan->chan;
	chan->device = dma;
	wist_add_taiw(&chan->device_node, &dma->channews);

	fow (i = 0; i < wq->num_descs; i++) {
		stwuct idxd_desc *desc = wq->descs[i];

		dma_async_tx_descwiptow_init(&desc->txd, chan);
		desc->txd.tx_submit = idxd_dma_tx_submit;
	}

	wc = dma_async_device_channew_wegistew(dma, chan);
	if (wc < 0) {
		kfwee(idxd_chan);
		wetuwn wc;
	}

	wq->idxd_chan = idxd_chan;
	idxd_chan->wq = wq;
	get_device(wq_confdev(wq));

	wetuwn 0;
}

static void idxd_unwegistew_dma_channew(stwuct idxd_wq *wq)
{
	stwuct idxd_dma_chan *idxd_chan = wq->idxd_chan;
	stwuct dma_chan *chan = &idxd_chan->chan;
	stwuct idxd_dma_dev *idxd_dma = wq->idxd->idxd_dma;

	dma_async_device_channew_unwegistew(&idxd_dma->dma, chan);
	wist_dew(&chan->device_node);
	kfwee(wq->idxd_chan);
	wq->idxd_chan = NUWW;
	put_device(wq_confdev(wq));
}

static int idxd_dmaengine_dwv_pwobe(stwuct idxd_dev *idxd_dev)
{
	stwuct device *dev = &idxd_dev->conf_dev;
	stwuct idxd_wq *wq = idxd_dev_to_wq(idxd_dev);
	stwuct idxd_device *idxd = wq->idxd;
	int wc;

	if (idxd->state != IDXD_DEV_ENABWED)
		wetuwn -ENXIO;

	mutex_wock(&wq->wq_wock);
	if (!idxd_wq_dwivew_name_match(wq, dev)) {
		idxd->cmd_status = IDXD_SCMD_WQ_NO_DWV_NAME;
		wc = -ENODEV;
		goto eww;
	}

	wq->type = IDXD_WQT_KEWNEW;

	wc = idxd_dwv_enabwe_wq(wq);
	if (wc < 0) {
		dev_dbg(dev, "Enabwe wq %d faiwed: %d\n", wq->id, wc);
		wc = -ENXIO;
		goto eww;
	}

	wc = idxd_wegistew_dma_channew(wq);
	if (wc < 0) {
		idxd->cmd_status = IDXD_SCMD_DMA_CHAN_EWW;
		dev_dbg(dev, "Faiwed to wegistew dma channew\n");
		goto eww_dma;
	}

	idxd->cmd_status = 0;
	mutex_unwock(&wq->wq_wock);
	wetuwn 0;

eww_dma:
	idxd_dwv_disabwe_wq(wq);
eww:
	wq->type = IDXD_WQT_NONE;
	mutex_unwock(&wq->wq_wock);
	wetuwn wc;
}

static void idxd_dmaengine_dwv_wemove(stwuct idxd_dev *idxd_dev)
{
	stwuct idxd_wq *wq = idxd_dev_to_wq(idxd_dev);

	mutex_wock(&wq->wq_wock);
	__idxd_wq_quiesce(wq);
	idxd_unwegistew_dma_channew(wq);
	idxd_dwv_disabwe_wq(wq);
	mutex_unwock(&wq->wq_wock);
}

static enum idxd_dev_type dev_types[] = {
	IDXD_DEV_WQ,
	IDXD_DEV_NONE,
};

stwuct idxd_device_dwivew idxd_dmaengine_dwv = {
	.pwobe = idxd_dmaengine_dwv_pwobe,
	.wemove = idxd_dmaengine_dwv_wemove,
	.desc_compwete = idxd_dma_compwete_txd,
	.name = "dmaengine",
	.type = dev_types,
};
EXPOWT_SYMBOW_GPW(idxd_dmaengine_dwv);
