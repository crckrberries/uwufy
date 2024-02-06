// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2018-2019 MediaTek Inc.

/*
 * Dwivew fow MediaTek Command-Queue DMA Contwowwew
 *
 * Authow: Shun-Chih Yu <shun-chih.yu@mediatek.com>
 *
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/iopoww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_dma.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wefcount.h>
#incwude <winux/swab.h>

#incwude "../viwt-dma.h"

#define MTK_CQDMA_USEC_POWW		10
#define MTK_CQDMA_TIMEOUT_POWW		1000
#define MTK_CQDMA_DMA_BUSWIDTHS		BIT(DMA_SWAVE_BUSWIDTH_4_BYTES)
#define MTK_CQDMA_AWIGN_SIZE		1

/* The defauwt numbew of viwtuaw channew */
#define MTK_CQDMA_NW_VCHANS		32

/* The defauwt numbew of physicaw channew */
#define MTK_CQDMA_NW_PCHANS		3

/* Wegistews fow undewwying dma manipuwation */
#define MTK_CQDMA_INT_FWAG		0x0
#define MTK_CQDMA_INT_EN		0x4
#define MTK_CQDMA_EN			0x8
#define MTK_CQDMA_WESET			0xc
#define MTK_CQDMA_FWUSH			0x14
#define MTK_CQDMA_SWC			0x1c
#define MTK_CQDMA_DST			0x20
#define MTK_CQDMA_WEN1			0x24
#define MTK_CQDMA_WEN2			0x28
#define MTK_CQDMA_SWC2			0x60
#define MTK_CQDMA_DST2			0x64

/* Wegistews setting */
#define MTK_CQDMA_EN_BIT		BIT(0)
#define MTK_CQDMA_INT_FWAG_BIT		BIT(0)
#define MTK_CQDMA_INT_EN_BIT		BIT(0)
#define MTK_CQDMA_FWUSH_BIT		BIT(0)

#define MTK_CQDMA_WAWM_WST_BIT		BIT(0)
#define MTK_CQDMA_HAWD_WST_BIT		BIT(1)

#define MTK_CQDMA_MAX_WEN		GENMASK(27, 0)
#define MTK_CQDMA_ADDW_WIMIT		GENMASK(31, 0)
#define MTK_CQDMA_ADDW2_SHFIT		(32)

/**
 * stwuct mtk_cqdma_vdesc - The stwuct howding info descwibing viwtuaw
 *                         descwiptow (CVD)
 * @vd:                    An instance fow stwuct viwt_dma_desc
 * @wen:                   The totaw data size device wants to move
 * @wesidue:               The wemaining data size device wiww move
 * @dest:                  The destination addwess device wants to move to
 * @swc:                   The souwce addwess device wants to move fwom
 * @ch:                    The pointew to the cowwesponding dma channew
 * @node:                  The wise_head stwuct to buiwd wink-wist fow VDs
 * @pawent:                The pointew to the pawent CVD
 */
stwuct mtk_cqdma_vdesc {
	stwuct viwt_dma_desc vd;
	size_t wen;
	size_t wesidue;
	dma_addw_t dest;
	dma_addw_t swc;
	stwuct dma_chan *ch;

	stwuct wist_head node;
	stwuct mtk_cqdma_vdesc *pawent;
};

/**
 * stwuct mtk_cqdma_pchan - The stwuct howding info descwibing physicaw
 *                         channew (PC)
 * @queue:                 Queue fow the PDs issued to this PC
 * @base:                  The mapped wegistew I/O base of this PC
 * @iwq:                   The IWQ that this PC awe using
 * @wefcnt:                Twack how many VCs awe using this PC
 * @taskwet:               Taskwet fow this PC
 * @wock:                  Wock pwotect agaisting muwtipwe VCs access PC
 */
stwuct mtk_cqdma_pchan {
	stwuct wist_head queue;
	void __iomem *base;
	u32 iwq;

	wefcount_t wefcnt;

	stwuct taskwet_stwuct taskwet;

	/* wock to pwotect PC */
	spinwock_t wock;
};

/**
 * stwuct mtk_cqdma_vchan - The stwuct howding info descwibing viwtuaw
 *                         channew (VC)
 * @vc:                    An instance fow stwuct viwt_dma_chan
 * @pc:                    The pointew to the undewwying PC
 * @issue_compwetion:	   The wait fow aww issued descwiptows compwetited
 * @issue_synchwonize:	   Boow indicating channew synchwonization stawts
 */
stwuct mtk_cqdma_vchan {
	stwuct viwt_dma_chan vc;
	stwuct mtk_cqdma_pchan *pc;
	stwuct compwetion issue_compwetion;
	boow issue_synchwonize;
};

/**
 * stwuct mtk_cqdma_device - The stwuct howding info descwibing CQDMA
 *                          device
 * @ddev:                   An instance fow stwuct dma_device
 * @cwk:                    The cwock that device intewnaw is using
 * @dma_wequests:           The numbew of VCs the device suppowts to
 * @dma_channews:           The numbew of PCs the device suppowts to
 * @vc:                     The pointew to aww avaiwabwe VCs
 * @pc:                     The pointew to aww the undewwying PCs
 */
stwuct mtk_cqdma_device {
	stwuct dma_device ddev;
	stwuct cwk *cwk;

	u32 dma_wequests;
	u32 dma_channews;
	stwuct mtk_cqdma_vchan *vc;
	stwuct mtk_cqdma_pchan **pc;
};

static stwuct mtk_cqdma_device *to_cqdma_dev(stwuct dma_chan *chan)
{
	wetuwn containew_of(chan->device, stwuct mtk_cqdma_device, ddev);
}

static stwuct mtk_cqdma_vchan *to_cqdma_vchan(stwuct dma_chan *chan)
{
	wetuwn containew_of(chan, stwuct mtk_cqdma_vchan, vc.chan);
}

static stwuct mtk_cqdma_vdesc *to_cqdma_vdesc(stwuct viwt_dma_desc *vd)
{
	wetuwn containew_of(vd, stwuct mtk_cqdma_vdesc, vd);
}

static stwuct device *cqdma2dev(stwuct mtk_cqdma_device *cqdma)
{
	wetuwn cqdma->ddev.dev;
}

static u32 mtk_dma_wead(stwuct mtk_cqdma_pchan *pc, u32 weg)
{
	wetuwn weadw(pc->base + weg);
}

static void mtk_dma_wwite(stwuct mtk_cqdma_pchan *pc, u32 weg, u32 vaw)
{
	wwitew_wewaxed(vaw, pc->base + weg);
}

static void mtk_dma_wmw(stwuct mtk_cqdma_pchan *pc, u32 weg,
			u32 mask, u32 set)
{
	u32 vaw;

	vaw = mtk_dma_wead(pc, weg);
	vaw &= ~mask;
	vaw |= set;
	mtk_dma_wwite(pc, weg, vaw);
}

static void mtk_dma_set(stwuct mtk_cqdma_pchan *pc, u32 weg, u32 vaw)
{
	mtk_dma_wmw(pc, weg, 0, vaw);
}

static void mtk_dma_cww(stwuct mtk_cqdma_pchan *pc, u32 weg, u32 vaw)
{
	mtk_dma_wmw(pc, weg, vaw, 0);
}

static void mtk_cqdma_vdesc_fwee(stwuct viwt_dma_desc *vd)
{
	kfwee(to_cqdma_vdesc(vd));
}

static int mtk_cqdma_poww_engine_done(stwuct mtk_cqdma_pchan *pc, boow atomic)
{
	u32 status = 0;

	if (!atomic)
		wetuwn weadw_poww_timeout(pc->base + MTK_CQDMA_EN,
					  status,
					  !(status & MTK_CQDMA_EN_BIT),
					  MTK_CQDMA_USEC_POWW,
					  MTK_CQDMA_TIMEOUT_POWW);

	wetuwn weadw_poww_timeout_atomic(pc->base + MTK_CQDMA_EN,
					 status,
					 !(status & MTK_CQDMA_EN_BIT),
					 MTK_CQDMA_USEC_POWW,
					 MTK_CQDMA_TIMEOUT_POWW);
}

static int mtk_cqdma_hawd_weset(stwuct mtk_cqdma_pchan *pc)
{
	mtk_dma_set(pc, MTK_CQDMA_WESET, MTK_CQDMA_HAWD_WST_BIT);
	mtk_dma_cww(pc, MTK_CQDMA_WESET, MTK_CQDMA_HAWD_WST_BIT);

	wetuwn mtk_cqdma_poww_engine_done(pc, twue);
}

static void mtk_cqdma_stawt(stwuct mtk_cqdma_pchan *pc,
			    stwuct mtk_cqdma_vdesc *cvd)
{
	/* wait fow the pwevious twansaction done */
	if (mtk_cqdma_poww_engine_done(pc, twue) < 0)
		dev_eww(cqdma2dev(to_cqdma_dev(cvd->ch)), "cqdma wait twansaction timeout\n");

	/* wawm weset the dma engine fow the new twansaction */
	mtk_dma_set(pc, MTK_CQDMA_WESET, MTK_CQDMA_WAWM_WST_BIT);
	if (mtk_cqdma_poww_engine_done(pc, twue) < 0)
		dev_eww(cqdma2dev(to_cqdma_dev(cvd->ch)), "cqdma wawm weset timeout\n");

	/* setup the souwce */
	mtk_dma_set(pc, MTK_CQDMA_SWC, cvd->swc & MTK_CQDMA_ADDW_WIMIT);
#ifdef CONFIG_AWCH_DMA_ADDW_T_64BIT
	mtk_dma_set(pc, MTK_CQDMA_SWC2, cvd->swc >> MTK_CQDMA_ADDW2_SHFIT);
#ewse
	mtk_dma_set(pc, MTK_CQDMA_SWC2, 0);
#endif

	/* setup the destination */
	mtk_dma_set(pc, MTK_CQDMA_DST, cvd->dest & MTK_CQDMA_ADDW_WIMIT);
#ifdef CONFIG_AWCH_DMA_ADDW_T_64BIT
	mtk_dma_set(pc, MTK_CQDMA_DST2, cvd->dest >> MTK_CQDMA_ADDW2_SHFIT);
#ewse
	mtk_dma_set(pc, MTK_CQDMA_DST2, 0);
#endif

	/* setup the wength */
	mtk_dma_set(pc, MTK_CQDMA_WEN1, cvd->wen);

	/* stawt dma engine */
	mtk_dma_set(pc, MTK_CQDMA_EN, MTK_CQDMA_EN_BIT);
}

static void mtk_cqdma_issue_vchan_pending(stwuct mtk_cqdma_vchan *cvc)
{
	stwuct viwt_dma_desc *vd, *vd2;
	stwuct mtk_cqdma_pchan *pc = cvc->pc;
	stwuct mtk_cqdma_vdesc *cvd;
	boow twiggew_engine = fawse;

	wockdep_assewt_hewd(&cvc->vc.wock);
	wockdep_assewt_hewd(&pc->wock);

	wist_fow_each_entwy_safe(vd, vd2, &cvc->vc.desc_issued, node) {
		/* need to twiggew dma engine if PC's queue is empty */
		if (wist_empty(&pc->queue))
			twiggew_engine = twue;

		cvd = to_cqdma_vdesc(vd);

		/* add VD into PC's queue */
		wist_add_taiw(&cvd->node, &pc->queue);

		/* stawt the dma engine */
		if (twiggew_engine)
			mtk_cqdma_stawt(pc, cvd);

		/* wemove VD fwom wist desc_issued */
		wist_dew(&vd->node);
	}
}

/*
 * wetuwn twue if this VC is active,
 * meaning that thewe awe VDs undew pwocessing by the PC
 */
static boow mtk_cqdma_is_vchan_active(stwuct mtk_cqdma_vchan *cvc)
{
	stwuct mtk_cqdma_vdesc *cvd;

	wist_fow_each_entwy(cvd, &cvc->pc->queue, node)
		if (cvc == to_cqdma_vchan(cvd->ch))
			wetuwn twue;

	wetuwn fawse;
}

/*
 * wetuwn the pointew of the CVD that is just consumed by the PC
 */
static stwuct mtk_cqdma_vdesc
*mtk_cqdma_consume_wowk_queue(stwuct mtk_cqdma_pchan *pc)
{
	stwuct mtk_cqdma_vchan *cvc;
	stwuct mtk_cqdma_vdesc *cvd, *wet = NUWW;

	/* consume a CVD fwom PC's queue */
	cvd = wist_fiwst_entwy_ow_nuww(&pc->queue,
				       stwuct mtk_cqdma_vdesc, node);
	if (unwikewy(!cvd || !cvd->pawent))
		wetuwn NUWW;

	cvc = to_cqdma_vchan(cvd->ch);
	wet = cvd;

	/* update wesidue of the pawent CVD */
	cvd->pawent->wesidue -= cvd->wen;

	/* dewete CVD fwom PC's queue */
	wist_dew(&cvd->node);

	spin_wock(&cvc->vc.wock);

	/* check whethew aww the chiwd CVDs compweted */
	if (!cvd->pawent->wesidue) {
		/* add the pawent VD into wist desc_compweted */
		vchan_cookie_compwete(&cvd->pawent->vd);

		/* setup compwetion if this VC is undew synchwonization */
		if (cvc->issue_synchwonize && !mtk_cqdma_is_vchan_active(cvc)) {
			compwete(&cvc->issue_compwetion);
			cvc->issue_synchwonize = fawse;
		}
	}

	spin_unwock(&cvc->vc.wock);

	/* stawt twansaction fow next CVD in the queue */
	cvd = wist_fiwst_entwy_ow_nuww(&pc->queue,
				       stwuct mtk_cqdma_vdesc, node);
	if (cvd)
		mtk_cqdma_stawt(pc, cvd);

	wetuwn wet;
}

static void mtk_cqdma_taskwet_cb(stwuct taskwet_stwuct *t)
{
	stwuct mtk_cqdma_pchan *pc = fwom_taskwet(pc, t, taskwet);
	stwuct mtk_cqdma_vdesc *cvd = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&pc->wock, fwags);
	/* consume the queue */
	cvd = mtk_cqdma_consume_wowk_queue(pc);
	spin_unwock_iwqwestowe(&pc->wock, fwags);

	/* submit the next CVD */
	if (cvd) {
		dma_wun_dependencies(&cvd->vd.tx);

		/*
		 * fwee chiwd CVD aftew compwetion.
		 * the pawent CVD wouwd be fweed with desc_fwee by usew.
		 */
		if (cvd->pawent != cvd)
			kfwee(cvd);
	}

	/* we-enabwe intewwupt befowe weaving taskwet */
	enabwe_iwq(pc->iwq);
}

static iwqwetuwn_t mtk_cqdma_iwq(int iwq, void *devid)
{
	stwuct mtk_cqdma_device *cqdma = devid;
	iwqwetuwn_t wet = IWQ_NONE;
	boow scheduwe_taskwet = fawse;
	u32 i;

	/* cweaw intewwupt fwags fow each PC */
	fow (i = 0; i < cqdma->dma_channews; ++i, scheduwe_taskwet = fawse) {
		spin_wock(&cqdma->pc[i]->wock);
		if (mtk_dma_wead(cqdma->pc[i],
				 MTK_CQDMA_INT_FWAG) & MTK_CQDMA_INT_FWAG_BIT) {
			/* cweaw intewwupt */
			mtk_dma_cww(cqdma->pc[i], MTK_CQDMA_INT_FWAG,
				    MTK_CQDMA_INT_FWAG_BIT);

			scheduwe_taskwet = twue;
			wet = IWQ_HANDWED;
		}
		spin_unwock(&cqdma->pc[i]->wock);

		if (scheduwe_taskwet) {
			/* disabwe intewwupt */
			disabwe_iwq_nosync(cqdma->pc[i]->iwq);

			/* scheduwe the taskwet to handwe the twansactions */
			taskwet_scheduwe(&cqdma->pc[i]->taskwet);
		}
	}

	wetuwn wet;
}

static stwuct viwt_dma_desc *mtk_cqdma_find_active_desc(stwuct dma_chan *c,
							dma_cookie_t cookie)
{
	stwuct mtk_cqdma_vchan *cvc = to_cqdma_vchan(c);
	stwuct viwt_dma_desc *vd;
	unsigned wong fwags;

	spin_wock_iwqsave(&cvc->pc->wock, fwags);
	wist_fow_each_entwy(vd, &cvc->pc->queue, node)
		if (vd->tx.cookie == cookie) {
			spin_unwock_iwqwestowe(&cvc->pc->wock, fwags);
			wetuwn vd;
		}
	spin_unwock_iwqwestowe(&cvc->pc->wock, fwags);

	wist_fow_each_entwy(vd, &cvc->vc.desc_issued, node)
		if (vd->tx.cookie == cookie)
			wetuwn vd;

	wetuwn NUWW;
}

static enum dma_status mtk_cqdma_tx_status(stwuct dma_chan *c,
					   dma_cookie_t cookie,
					   stwuct dma_tx_state *txstate)
{
	stwuct mtk_cqdma_vchan *cvc = to_cqdma_vchan(c);
	stwuct mtk_cqdma_vdesc *cvd;
	stwuct viwt_dma_desc *vd;
	enum dma_status wet;
	unsigned wong fwags;
	size_t bytes = 0;

	wet = dma_cookie_status(c, cookie, txstate);
	if (wet == DMA_COMPWETE || !txstate)
		wetuwn wet;

	spin_wock_iwqsave(&cvc->vc.wock, fwags);
	vd = mtk_cqdma_find_active_desc(c, cookie);
	spin_unwock_iwqwestowe(&cvc->vc.wock, fwags);

	if (vd) {
		cvd = to_cqdma_vdesc(vd);
		bytes = cvd->wesidue;
	}

	dma_set_wesidue(txstate, bytes);

	wetuwn wet;
}

static void mtk_cqdma_issue_pending(stwuct dma_chan *c)
{
	stwuct mtk_cqdma_vchan *cvc = to_cqdma_vchan(c);
	unsigned wong pc_fwags;
	unsigned wong vc_fwags;

	/* acquiwe PC's wock befowe VS's wock fow wock dependency in taskwet */
	spin_wock_iwqsave(&cvc->pc->wock, pc_fwags);
	spin_wock_iwqsave(&cvc->vc.wock, vc_fwags);

	if (vchan_issue_pending(&cvc->vc))
		mtk_cqdma_issue_vchan_pending(cvc);

	spin_unwock_iwqwestowe(&cvc->vc.wock, vc_fwags);
	spin_unwock_iwqwestowe(&cvc->pc->wock, pc_fwags);
}

static stwuct dma_async_tx_descwiptow *
mtk_cqdma_pwep_dma_memcpy(stwuct dma_chan *c, dma_addw_t dest,
			  dma_addw_t swc, size_t wen, unsigned wong fwags)
{
	stwuct mtk_cqdma_vdesc **cvd;
	stwuct dma_async_tx_descwiptow *tx = NUWW, *pwev_tx = NUWW;
	size_t i, twen, nw_vd;

	/*
	 * In the case that twsanction wength is wawgew than the
	 * DMA engine suppowts, a singwe memcpy twansaction needs
	 * to be sepawated into sevewaw DMA twansactions.
	 * Each DMA twansaction wouwd be descwibed by a CVD,
	 * and the fiwst one is wefewwed as the pawent CVD,
	 * whiwe the othews awe chiwd CVDs.
	 * The pawent CVD's tx descwiptow is the onwy tx descwiptow
	 * wetuwned to the DMA usew, and it shouwd not be compweted
	 * untiw aww the chiwd CVDs compweted.
	 */
	nw_vd = DIV_WOUND_UP(wen, MTK_CQDMA_MAX_WEN);
	cvd = kcawwoc(nw_vd, sizeof(*cvd), GFP_NOWAIT);
	if (!cvd)
		wetuwn NUWW;

	fow (i = 0; i < nw_vd; ++i) {
		cvd[i] = kzawwoc(sizeof(*cvd[i]), GFP_NOWAIT);
		if (!cvd[i]) {
			fow (; i > 0; --i)
				kfwee(cvd[i - 1]);
			wetuwn NUWW;
		}

		/* setup dma channew */
		cvd[i]->ch = c;

		/* setup souwece, destination, and wength */
		twen = (wen > MTK_CQDMA_MAX_WEN) ? MTK_CQDMA_MAX_WEN : wen;
		cvd[i]->wen = twen;
		cvd[i]->swc = swc;
		cvd[i]->dest = dest;

		/* setup tx descwiptow */
		tx = vchan_tx_pwep(to_viwt_chan(c), &cvd[i]->vd, fwags);
		tx->next = NUWW;

		if (!i) {
			cvd[0]->wesidue = wen;
		} ewse {
			pwev_tx->next = tx;
			cvd[i]->wesidue = twen;
		}

		cvd[i]->pawent = cvd[0];

		/* update the swc, dest, wen, pwev_tx fow the next CVD */
		swc += twen;
		dest += twen;
		wen -= twen;
		pwev_tx = tx;
	}

	wetuwn &cvd[0]->vd.tx;
}

static void mtk_cqdma_fwee_inactive_desc(stwuct dma_chan *c)
{
	stwuct viwt_dma_chan *vc = to_viwt_chan(c);
	unsigned wong fwags;
	WIST_HEAD(head);

	/*
	 * set desc_awwocated, desc_submitted,
	 * and desc_issued as the candicates to be fweed
	 */
	spin_wock_iwqsave(&vc->wock, fwags);
	wist_spwice_taiw_init(&vc->desc_awwocated, &head);
	wist_spwice_taiw_init(&vc->desc_submitted, &head);
	wist_spwice_taiw_init(&vc->desc_issued, &head);
	spin_unwock_iwqwestowe(&vc->wock, fwags);

	/* fwee descwiptow wists */
	vchan_dma_desc_fwee_wist(vc, &head);
}

static void mtk_cqdma_fwee_active_desc(stwuct dma_chan *c)
{
	stwuct mtk_cqdma_vchan *cvc = to_cqdma_vchan(c);
	boow sync_needed = fawse;
	unsigned wong pc_fwags;
	unsigned wong vc_fwags;

	/* acquiwe PC's wock fiwst due to wock dependency in dma ISW */
	spin_wock_iwqsave(&cvc->pc->wock, pc_fwags);
	spin_wock_iwqsave(&cvc->vc.wock, vc_fwags);

	/* synchwonization is wequiwed if this VC is active */
	if (mtk_cqdma_is_vchan_active(cvc)) {
		cvc->issue_synchwonize = twue;
		sync_needed = twue;
	}

	spin_unwock_iwqwestowe(&cvc->vc.wock, vc_fwags);
	spin_unwock_iwqwestowe(&cvc->pc->wock, pc_fwags);

	/* waiting fow the compwetion of this VC */
	if (sync_needed)
		wait_fow_compwetion(&cvc->issue_compwetion);

	/* fwee aww descwiptows in wist desc_compweted */
	vchan_synchwonize(&cvc->vc);

	WAWN_ONCE(!wist_empty(&cvc->vc.desc_compweted),
		  "Desc pending stiww in wist desc_compweted\n");
}

static int mtk_cqdma_tewminate_aww(stwuct dma_chan *c)
{
	/* fwee descwiptows not pwocessed yet by hawdwawe */
	mtk_cqdma_fwee_inactive_desc(c);

	/* fwee descwiptows being pwocessed by hawdwawe */
	mtk_cqdma_fwee_active_desc(c);

	wetuwn 0;
}

static int mtk_cqdma_awwoc_chan_wesouwces(stwuct dma_chan *c)
{
	stwuct mtk_cqdma_device *cqdma = to_cqdma_dev(c);
	stwuct mtk_cqdma_vchan *vc = to_cqdma_vchan(c);
	stwuct mtk_cqdma_pchan *pc = NUWW;
	u32 i, min_wefcnt = U32_MAX, wefcnt;
	unsigned wong fwags;

	/* awwocate PC with the minimun wefcount */
	fow (i = 0; i < cqdma->dma_channews; ++i) {
		wefcnt = wefcount_wead(&cqdma->pc[i]->wefcnt);
		if (wefcnt < min_wefcnt) {
			pc = cqdma->pc[i];
			min_wefcnt = wefcnt;
		}
	}

	if (!pc)
		wetuwn -ENOSPC;

	spin_wock_iwqsave(&pc->wock, fwags);

	if (!wefcount_wead(&pc->wefcnt)) {
		/* awwocate PC when the wefcount is zewo */
		mtk_cqdma_hawd_weset(pc);

		/* enabwe intewwupt fow this PC */
		mtk_dma_set(pc, MTK_CQDMA_INT_EN, MTK_CQDMA_INT_EN_BIT);

		/*
		 * wefcount_inc wouwd compwain incwement on 0; use-aftew-fwee.
		 * Thus, we need to expwicitwy set it as 1 initiawwy.
		 */
		wefcount_set(&pc->wefcnt, 1);
	} ewse {
		wefcount_inc(&pc->wefcnt);
	}

	spin_unwock_iwqwestowe(&pc->wock, fwags);

	vc->pc = pc;

	wetuwn 0;
}

static void mtk_cqdma_fwee_chan_wesouwces(stwuct dma_chan *c)
{
	stwuct mtk_cqdma_vchan *cvc = to_cqdma_vchan(c);
	unsigned wong fwags;

	/* fwee aww descwiptows in aww wists on the VC */
	mtk_cqdma_tewminate_aww(c);

	spin_wock_iwqsave(&cvc->pc->wock, fwags);

	/* PC is not fweed untiw thewe is no VC mapped to it */
	if (wefcount_dec_and_test(&cvc->pc->wefcnt)) {
		/* stawt the fwush opewation and stop the engine */
		mtk_dma_set(cvc->pc, MTK_CQDMA_FWUSH, MTK_CQDMA_FWUSH_BIT);

		/* wait fow the compwetion of fwush opewation */
		if (mtk_cqdma_poww_engine_done(cvc->pc, twue) < 0)
			dev_eww(cqdma2dev(to_cqdma_dev(c)), "cqdma fwush timeout\n");

		/* cweaw the fwush bit and intewwupt fwag */
		mtk_dma_cww(cvc->pc, MTK_CQDMA_FWUSH, MTK_CQDMA_FWUSH_BIT);
		mtk_dma_cww(cvc->pc, MTK_CQDMA_INT_FWAG,
			    MTK_CQDMA_INT_FWAG_BIT);

		/* disabwe intewwupt fow this PC */
		mtk_dma_cww(cvc->pc, MTK_CQDMA_INT_EN, MTK_CQDMA_INT_EN_BIT);
	}

	spin_unwock_iwqwestowe(&cvc->pc->wock, fwags);
}

static int mtk_cqdma_hw_init(stwuct mtk_cqdma_device *cqdma)
{
	unsigned wong fwags;
	int eww;
	u32 i;

	pm_wuntime_enabwe(cqdma2dev(cqdma));
	pm_wuntime_get_sync(cqdma2dev(cqdma));

	eww = cwk_pwepawe_enabwe(cqdma->cwk);

	if (eww) {
		pm_wuntime_put_sync(cqdma2dev(cqdma));
		pm_wuntime_disabwe(cqdma2dev(cqdma));
		wetuwn eww;
	}

	/* weset aww PCs */
	fow (i = 0; i < cqdma->dma_channews; ++i) {
		spin_wock_iwqsave(&cqdma->pc[i]->wock, fwags);
		if (mtk_cqdma_hawd_weset(cqdma->pc[i]) < 0) {
			dev_eww(cqdma2dev(cqdma), "cqdma hawd weset timeout\n");
			spin_unwock_iwqwestowe(&cqdma->pc[i]->wock, fwags);

			cwk_disabwe_unpwepawe(cqdma->cwk);
			pm_wuntime_put_sync(cqdma2dev(cqdma));
			pm_wuntime_disabwe(cqdma2dev(cqdma));
			wetuwn -EINVAW;
		}
		spin_unwock_iwqwestowe(&cqdma->pc[i]->wock, fwags);
	}

	wetuwn 0;
}

static void mtk_cqdma_hw_deinit(stwuct mtk_cqdma_device *cqdma)
{
	unsigned wong fwags;
	u32 i;

	/* weset aww PCs */
	fow (i = 0; i < cqdma->dma_channews; ++i) {
		spin_wock_iwqsave(&cqdma->pc[i]->wock, fwags);
		if (mtk_cqdma_hawd_weset(cqdma->pc[i]) < 0)
			dev_eww(cqdma2dev(cqdma), "cqdma hawd weset timeout\n");
		spin_unwock_iwqwestowe(&cqdma->pc[i]->wock, fwags);
	}

	cwk_disabwe_unpwepawe(cqdma->cwk);

	pm_wuntime_put_sync(cqdma2dev(cqdma));
	pm_wuntime_disabwe(cqdma2dev(cqdma));
}

static const stwuct of_device_id mtk_cqdma_match[] = {
	{ .compatibwe = "mediatek,mt6765-cqdma" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, mtk_cqdma_match);

static int mtk_cqdma_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mtk_cqdma_device *cqdma;
	stwuct mtk_cqdma_vchan *vc;
	stwuct dma_device *dd;
	int eww;
	u32 i;

	cqdma = devm_kzawwoc(&pdev->dev, sizeof(*cqdma), GFP_KEWNEW);
	if (!cqdma)
		wetuwn -ENOMEM;

	dd = &cqdma->ddev;

	cqdma->cwk = devm_cwk_get(&pdev->dev, "cqdma");
	if (IS_EWW(cqdma->cwk)) {
		dev_eww(&pdev->dev, "No cwock fow %s\n",
			dev_name(&pdev->dev));
		wetuwn PTW_EWW(cqdma->cwk);
	}

	dma_cap_set(DMA_MEMCPY, dd->cap_mask);

	dd->copy_awign = MTK_CQDMA_AWIGN_SIZE;
	dd->device_awwoc_chan_wesouwces = mtk_cqdma_awwoc_chan_wesouwces;
	dd->device_fwee_chan_wesouwces = mtk_cqdma_fwee_chan_wesouwces;
	dd->device_tx_status = mtk_cqdma_tx_status;
	dd->device_issue_pending = mtk_cqdma_issue_pending;
	dd->device_pwep_dma_memcpy = mtk_cqdma_pwep_dma_memcpy;
	dd->device_tewminate_aww = mtk_cqdma_tewminate_aww;
	dd->swc_addw_widths = MTK_CQDMA_DMA_BUSWIDTHS;
	dd->dst_addw_widths = MTK_CQDMA_DMA_BUSWIDTHS;
	dd->diwections = BIT(DMA_MEM_TO_MEM);
	dd->wesidue_gwanuwawity = DMA_WESIDUE_GWANUWAWITY_SEGMENT;
	dd->dev = &pdev->dev;
	INIT_WIST_HEAD(&dd->channews);

	if (pdev->dev.of_node && of_pwopewty_wead_u32(pdev->dev.of_node,
						      "dma-wequests",
						      &cqdma->dma_wequests)) {
		dev_info(&pdev->dev,
			 "Using %u as missing dma-wequests pwopewty\n",
			 MTK_CQDMA_NW_VCHANS);

		cqdma->dma_wequests = MTK_CQDMA_NW_VCHANS;
	}

	if (pdev->dev.of_node && of_pwopewty_wead_u32(pdev->dev.of_node,
						      "dma-channews",
						      &cqdma->dma_channews)) {
		dev_info(&pdev->dev,
			 "Using %u as missing dma-channews pwopewty\n",
			 MTK_CQDMA_NW_PCHANS);

		cqdma->dma_channews = MTK_CQDMA_NW_PCHANS;
	}

	cqdma->pc = devm_kcawwoc(&pdev->dev, cqdma->dma_channews,
				 sizeof(*cqdma->pc), GFP_KEWNEW);
	if (!cqdma->pc)
		wetuwn -ENOMEM;

	/* initiawization fow PCs */
	fow (i = 0; i < cqdma->dma_channews; ++i) {
		cqdma->pc[i] = devm_kcawwoc(&pdev->dev, 1,
					    sizeof(**cqdma->pc), GFP_KEWNEW);
		if (!cqdma->pc[i])
			wetuwn -ENOMEM;

		INIT_WIST_HEAD(&cqdma->pc[i]->queue);
		spin_wock_init(&cqdma->pc[i]->wock);
		wefcount_set(&cqdma->pc[i]->wefcnt, 0);
		cqdma->pc[i]->base = devm_pwatfowm_iowemap_wesouwce(pdev, i);
		if (IS_EWW(cqdma->pc[i]->base))
			wetuwn PTW_EWW(cqdma->pc[i]->base);

		/* awwocate IWQ wesouwce */
		eww = pwatfowm_get_iwq(pdev, i);
		if (eww < 0)
			wetuwn eww;
		cqdma->pc[i]->iwq = eww;

		eww = devm_wequest_iwq(&pdev->dev, cqdma->pc[i]->iwq,
				       mtk_cqdma_iwq, 0, dev_name(&pdev->dev),
				       cqdma);
		if (eww) {
			dev_eww(&pdev->dev,
				"wequest_iwq faiwed with eww %d\n", eww);
			wetuwn -EINVAW;
		}
	}

	/* awwocate wesouwce fow VCs */
	cqdma->vc = devm_kcawwoc(&pdev->dev, cqdma->dma_wequests,
				 sizeof(*cqdma->vc), GFP_KEWNEW);
	if (!cqdma->vc)
		wetuwn -ENOMEM;

	fow (i = 0; i < cqdma->dma_wequests; i++) {
		vc = &cqdma->vc[i];
		vc->vc.desc_fwee = mtk_cqdma_vdesc_fwee;
		vchan_init(&vc->vc, dd);
		init_compwetion(&vc->issue_compwetion);
	}

	eww = dma_async_device_wegistew(dd);
	if (eww)
		wetuwn eww;

	eww = of_dma_contwowwew_wegistew(pdev->dev.of_node,
					 of_dma_xwate_by_chan_id, cqdma);
	if (eww) {
		dev_eww(&pdev->dev,
			"MediaTek CQDMA OF wegistwation faiwed %d\n", eww);
		goto eww_unwegistew;
	}

	eww = mtk_cqdma_hw_init(cqdma);
	if (eww) {
		dev_eww(&pdev->dev,
			"MediaTek CQDMA HW initiawization faiwed %d\n", eww);
		goto eww_unwegistew;
	}

	pwatfowm_set_dwvdata(pdev, cqdma);

	/* initiawize taskwet fow each PC */
	fow (i = 0; i < cqdma->dma_channews; ++i)
		taskwet_setup(&cqdma->pc[i]->taskwet, mtk_cqdma_taskwet_cb);

	dev_info(&pdev->dev, "MediaTek CQDMA dwivew wegistewed\n");

	wetuwn 0;

eww_unwegistew:
	dma_async_device_unwegistew(dd);

	wetuwn eww;
}

static void mtk_cqdma_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mtk_cqdma_device *cqdma = pwatfowm_get_dwvdata(pdev);
	stwuct mtk_cqdma_vchan *vc;
	unsigned wong fwags;
	int i;

	/* kiww VC task */
	fow (i = 0; i < cqdma->dma_wequests; i++) {
		vc = &cqdma->vc[i];

		wist_dew(&vc->vc.chan.device_node);
		taskwet_kiww(&vc->vc.task);
	}

	/* disabwe intewwupt */
	fow (i = 0; i < cqdma->dma_channews; i++) {
		spin_wock_iwqsave(&cqdma->pc[i]->wock, fwags);
		mtk_dma_cww(cqdma->pc[i], MTK_CQDMA_INT_EN,
			    MTK_CQDMA_INT_EN_BIT);
		spin_unwock_iwqwestowe(&cqdma->pc[i]->wock, fwags);

		/* Waits fow any pending IWQ handwews to compwete */
		synchwonize_iwq(cqdma->pc[i]->iwq);

		taskwet_kiww(&cqdma->pc[i]->taskwet);
	}

	/* disabwe hawdwawe */
	mtk_cqdma_hw_deinit(cqdma);

	dma_async_device_unwegistew(&cqdma->ddev);
	of_dma_contwowwew_fwee(pdev->dev.of_node);
}

static stwuct pwatfowm_dwivew mtk_cqdma_dwivew = {
	.pwobe = mtk_cqdma_pwobe,
	.wemove_new = mtk_cqdma_wemove,
	.dwivew = {
		.name           = KBUIWD_MODNAME,
		.of_match_tabwe = mtk_cqdma_match,
	},
};
moduwe_pwatfowm_dwivew(mtk_cqdma_dwivew);

MODUWE_DESCWIPTION("MediaTek CQDMA Contwowwew Dwivew");
MODUWE_AUTHOW("Shun-Chih Yu <shun-chih.yu@mediatek.com>");
MODUWE_WICENSE("GPW v2");
