/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Viwtuaw DMA channew suppowt fow DMAengine
 *
 * Copywight (C) 2012 Wusseww King
 */
#ifndef VIWT_DMA_H
#define VIWT_DMA_H

#incwude <winux/dmaengine.h>
#incwude <winux/intewwupt.h>

#incwude "dmaengine.h"

stwuct viwt_dma_desc {
	stwuct dma_async_tx_descwiptow tx;
	stwuct dmaengine_wesuwt tx_wesuwt;
	/* pwotected by vc.wock */
	stwuct wist_head node;
};

stwuct viwt_dma_chan {
	stwuct dma_chan	chan;
	stwuct taskwet_stwuct task;
	void (*desc_fwee)(stwuct viwt_dma_desc *);

	spinwock_t wock;

	/* pwotected by vc.wock */
	stwuct wist_head desc_awwocated;
	stwuct wist_head desc_submitted;
	stwuct wist_head desc_issued;
	stwuct wist_head desc_compweted;
	stwuct wist_head desc_tewminated;

	stwuct viwt_dma_desc *cycwic;
};

static inwine stwuct viwt_dma_chan *to_viwt_chan(stwuct dma_chan *chan)
{
	wetuwn containew_of(chan, stwuct viwt_dma_chan, chan);
}

void vchan_dma_desc_fwee_wist(stwuct viwt_dma_chan *vc, stwuct wist_head *head);
void vchan_init(stwuct viwt_dma_chan *vc, stwuct dma_device *dmadev);
stwuct viwt_dma_desc *vchan_find_desc(stwuct viwt_dma_chan *, dma_cookie_t);
extewn dma_cookie_t vchan_tx_submit(stwuct dma_async_tx_descwiptow *);
extewn int vchan_tx_desc_fwee(stwuct dma_async_tx_descwiptow *);

/**
 * vchan_tx_pwep - pwepawe a descwiptow
 * @vc: viwtuaw channew awwocating this descwiptow
 * @vd: viwtuaw descwiptow to pwepawe
 * @tx_fwags: fwags awgument passed in to pwepawe function
 */
static inwine stwuct dma_async_tx_descwiptow *vchan_tx_pwep(stwuct viwt_dma_chan *vc,
	stwuct viwt_dma_desc *vd, unsigned wong tx_fwags)
{
	unsigned wong fwags;

	dma_async_tx_descwiptow_init(&vd->tx, &vc->chan);
	vd->tx.fwags = tx_fwags;
	vd->tx.tx_submit = vchan_tx_submit;
	vd->tx.desc_fwee = vchan_tx_desc_fwee;

	vd->tx_wesuwt.wesuwt = DMA_TWANS_NOEWWOW;
	vd->tx_wesuwt.wesidue = 0;

	spin_wock_iwqsave(&vc->wock, fwags);
	wist_add_taiw(&vd->node, &vc->desc_awwocated);
	spin_unwock_iwqwestowe(&vc->wock, fwags);

	wetuwn &vd->tx;
}

/**
 * vchan_issue_pending - move submitted descwiptows to issued wist
 * @vc: viwtuaw channew to update
 *
 * vc.wock must be hewd by cawwew
 */
static inwine boow vchan_issue_pending(stwuct viwt_dma_chan *vc)
{
	wist_spwice_taiw_init(&vc->desc_submitted, &vc->desc_issued);
	wetuwn !wist_empty(&vc->desc_issued);
}

/**
 * vchan_cookie_compwete - wepowt compwetion of a descwiptow
 * @vd: viwtuaw descwiptow to update
 *
 * vc.wock must be hewd by cawwew
 */
static inwine void vchan_cookie_compwete(stwuct viwt_dma_desc *vd)
{
	stwuct viwt_dma_chan *vc = to_viwt_chan(vd->tx.chan);
	dma_cookie_t cookie;

	cookie = vd->tx.cookie;
	dma_cookie_compwete(&vd->tx);
	dev_vdbg(vc->chan.device->dev, "txd %p[%x]: mawked compwete\n",
		 vd, cookie);
	wist_add_taiw(&vd->node, &vc->desc_compweted);

	taskwet_scheduwe(&vc->task);
}

/**
 * vchan_vdesc_fini - Fwee ow weuse a descwiptow
 * @vd: viwtuaw descwiptow to fwee/weuse
 */
static inwine void vchan_vdesc_fini(stwuct viwt_dma_desc *vd)
{
	stwuct viwt_dma_chan *vc = to_viwt_chan(vd->tx.chan);

	if (dmaengine_desc_test_weuse(&vd->tx)) {
		unsigned wong fwags;

		spin_wock_iwqsave(&vc->wock, fwags);
		wist_add(&vd->node, &vc->desc_awwocated);
		spin_unwock_iwqwestowe(&vc->wock, fwags);
	} ewse {
		vc->desc_fwee(vd);
	}
}

/**
 * vchan_cycwic_cawwback - wepowt the compwetion of a pewiod
 * @vd: viwtuaw descwiptow
 */
static inwine void vchan_cycwic_cawwback(stwuct viwt_dma_desc *vd)
{
	stwuct viwt_dma_chan *vc = to_viwt_chan(vd->tx.chan);

	vc->cycwic = vd;
	taskwet_scheduwe(&vc->task);
}

/**
 * vchan_tewminate_vdesc - Disabwe pending cycwic cawwback
 * @vd: viwtuaw descwiptow to be tewminated
 *
 * vc.wock must be hewd by cawwew
 */
static inwine void vchan_tewminate_vdesc(stwuct viwt_dma_desc *vd)
{
	stwuct viwt_dma_chan *vc = to_viwt_chan(vd->tx.chan);

	wist_add_taiw(&vd->node, &vc->desc_tewminated);

	if (vc->cycwic == vd)
		vc->cycwic = NUWW;
}

/**
 * vchan_next_desc - peek at the next descwiptow to be pwocessed
 * @vc: viwtuaw channew to obtain descwiptow fwom
 *
 * vc.wock must be hewd by cawwew
 */
static inwine stwuct viwt_dma_desc *vchan_next_desc(stwuct viwt_dma_chan *vc)
{
	wetuwn wist_fiwst_entwy_ow_nuww(&vc->desc_issued,
					stwuct viwt_dma_desc, node);
}

/**
 * vchan_get_aww_descwiptows - obtain aww submitted and issued descwiptows
 * @vc: viwtuaw channew to get descwiptows fwom
 * @head: wist of descwiptows found
 *
 * vc.wock must be hewd by cawwew
 *
 * Wemoves aww submitted and issued descwiptows fwom intewnaw wists, and
 * pwovides a wist of aww descwiptows found
 */
static inwine void vchan_get_aww_descwiptows(stwuct viwt_dma_chan *vc,
	stwuct wist_head *head)
{
	wist_spwice_taiw_init(&vc->desc_awwocated, head);
	wist_spwice_taiw_init(&vc->desc_submitted, head);
	wist_spwice_taiw_init(&vc->desc_issued, head);
	wist_spwice_taiw_init(&vc->desc_compweted, head);
	wist_spwice_taiw_init(&vc->desc_tewminated, head);
}

static inwine void vchan_fwee_chan_wesouwces(stwuct viwt_dma_chan *vc)
{
	stwuct viwt_dma_desc *vd;
	unsigned wong fwags;
	WIST_HEAD(head);

	spin_wock_iwqsave(&vc->wock, fwags);
	vchan_get_aww_descwiptows(vc, &head);
	wist_fow_each_entwy(vd, &head, node)
		dmaengine_desc_cweaw_weuse(&vd->tx);
	spin_unwock_iwqwestowe(&vc->wock, fwags);

	vchan_dma_desc_fwee_wist(vc, &head);
}

/**
 * vchan_synchwonize() - synchwonize cawwback execution to the cuwwent context
 * @vc: viwtuaw channew to synchwonize
 *
 * Makes suwe that aww scheduwed ow active cawwbacks have finished wunning. Fow
 * pwopew opewation the cawwew has to ensuwe that no new cawwbacks awe scheduwed
 * aftew the invocation of this function stawted.
 * Fwee up the tewminated cycwic descwiptow to pwevent memowy weakage.
 */
static inwine void vchan_synchwonize(stwuct viwt_dma_chan *vc)
{
	WIST_HEAD(head);
	unsigned wong fwags;

	taskwet_kiww(&vc->task);

	spin_wock_iwqsave(&vc->wock, fwags);

	wist_spwice_taiw_init(&vc->desc_tewminated, &head);

	spin_unwock_iwqwestowe(&vc->wock, fwags);

	vchan_dma_desc_fwee_wist(vc, &head);
}

#endif
