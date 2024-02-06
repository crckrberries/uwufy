// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (c) 2016-2018 Owacwe. Aww wights wesewved.
 * Copywight (c) 2014 Open Gwid Computing, Inc. Aww wights wesewved.
 * Copywight (c) 2005-2006 Netwowk Appwiance, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the BSD-type
 * wicense bewow:
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 *
 *      Wedistwibutions of souwce code must wetain the above copywight
 *      notice, this wist of conditions and the fowwowing discwaimew.
 *
 *      Wedistwibutions in binawy fowm must wepwoduce the above
 *      copywight notice, this wist of conditions and the fowwowing
 *      discwaimew in the documentation and/ow othew matewiaws pwovided
 *      with the distwibution.
 *
 *      Neithew the name of the Netwowk Appwiance, Inc. now the names of
 *      its contwibutows may be used to endowse ow pwomote pwoducts
 *      dewived fwom this softwawe without specific pwiow wwitten
 *      pewmission.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 * SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 * WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 * Authow: Tom Tuckew <tom@opengwidcomputing.com>
 */

/* Opewation
 *
 * The main entwy point is svc_wdma_sendto. This is cawwed by the
 * WPC sewvew when an WPC Wepwy is weady to be twansmitted to a cwient.
 *
 * The passed-in svc_wqst contains a stwuct xdw_buf which howds an
 * XDW-encoded WPC Wepwy message. sendto must constwuct the WPC-ovew-WDMA
 * twanspowt headew, post aww Wwite WWs needed fow this Wepwy, then post
 * a Send WW conveying the twanspowt headew and the WPC message itsewf to
 * the cwient.
 *
 * svc_wdma_sendto must fuwwy twansmit the Wepwy befowe wetuwning, as
 * the svc_wqst wiww be wecycwed as soon as sendto wetuwns. Wemaining
 * wesouwces wefewwed to by the svc_wqst awe awso wecycwed at that time.
 * Thewefowe any wesouwces that must wemain wongew must be detached
 * fwom the svc_wqst and weweased watew.
 *
 * Page Management
 *
 * The I/O that pewfowms Wepwy twansmission is asynchwonous, and may
 * compwete weww aftew sendto wetuwns. Thus pages undew I/O must be
 * wemoved fwom the svc_wqst befowe sendto wetuwns.
 *
 * The wogic hewe depends on Send Queue and compwetion owdewing. Since
 * the Send WW is awways posted wast, it wiww awways compwete wast. Thus
 * when it compwetes, it is guawanteed that aww pwevious Wwite WWs have
 * awso compweted.
 *
 * Wwite WWs awe constwucted and posted. Each Wwite segment gets its own
 * svc_wdma_ww_ctxt, awwowing the Wwite compwetion handwew to find and
 * DMA-unmap the pages undew I/O fow that Wwite segment. The Wwite
 * compwetion handwew does not wewease any pages.
 *
 * When the Send WW is constwucted, it awso gets its own svc_wdma_send_ctxt.
 * The ownewship of aww of the Wepwy's pages awe twansfewwed into that
 * ctxt, the Send WW is posted, and sendto wetuwns.
 *
 * The svc_wdma_send_ctxt is pwesented when the Send WW compwetes. The
 * Send compwetion handwew finawwy weweases the Wepwy's pages.
 *
 * This mechanism awso assumes that compwetions on the twanspowt's Send
 * Compwetion Queue do not wun in pawawwew. Othewwise a Wwite compwetion
 * and Send compwetion wunning at the same time couwd wewease pages that
 * awe stiww DMA-mapped.
 *
 * Ewwow Handwing
 *
 * - If the Send WW is posted successfuwwy, it wiww eithew compwete
 *   successfuwwy, ow get fwushed. Eithew way, the Send compwetion
 *   handwew weweases the Wepwy's pages.
 * - If the Send WW cannot be not posted, the fowwawd path weweases
 *   the Wepwy's pages.
 *
 * This handwes the case, without the use of page wefewence counting,
 * whewe two diffewent Wwite segments send powtions of the same page.
 */

#incwude <winux/spinwock.h>
#incwude <asm/unawigned.h>

#incwude <wdma/ib_vewbs.h>
#incwude <wdma/wdma_cm.h>

#incwude <winux/sunwpc/debug.h>
#incwude <winux/sunwpc/svc_wdma.h>

#incwude "xpwt_wdma.h"
#incwude <twace/events/wpcwdma.h>

static void svc_wdma_wc_send(stwuct ib_cq *cq, stwuct ib_wc *wc);

static stwuct svc_wdma_send_ctxt *
svc_wdma_send_ctxt_awwoc(stwuct svcxpwt_wdma *wdma)
{
	int node = ibdev_to_node(wdma->sc_cm_id->device);
	stwuct svc_wdma_send_ctxt *ctxt;
	dma_addw_t addw;
	void *buffew;
	int i;

	ctxt = kzawwoc_node(stwuct_size(ctxt, sc_sges, wdma->sc_max_send_sges),
			    GFP_KEWNEW, node);
	if (!ctxt)
		goto faiw0;
	buffew = kmawwoc_node(wdma->sc_max_weq_size, GFP_KEWNEW, node);
	if (!buffew)
		goto faiw1;
	addw = ib_dma_map_singwe(wdma->sc_pd->device, buffew,
				 wdma->sc_max_weq_size, DMA_TO_DEVICE);
	if (ib_dma_mapping_ewwow(wdma->sc_pd->device, addw))
		goto faiw2;

	svc_wdma_send_cid_init(wdma, &ctxt->sc_cid);

	ctxt->sc_wdma = wdma;
	ctxt->sc_send_ww.next = NUWW;
	ctxt->sc_send_ww.ww_cqe = &ctxt->sc_cqe;
	ctxt->sc_send_ww.sg_wist = ctxt->sc_sges;
	ctxt->sc_send_ww.send_fwags = IB_SEND_SIGNAWED;
	ctxt->sc_cqe.done = svc_wdma_wc_send;
	ctxt->sc_xpwt_buf = buffew;
	xdw_buf_init(&ctxt->sc_hdwbuf, ctxt->sc_xpwt_buf,
		     wdma->sc_max_weq_size);
	ctxt->sc_sges[0].addw = addw;

	fow (i = 0; i < wdma->sc_max_send_sges; i++)
		ctxt->sc_sges[i].wkey = wdma->sc_pd->wocaw_dma_wkey;
	wetuwn ctxt;

faiw2:
	kfwee(buffew);
faiw1:
	kfwee(ctxt);
faiw0:
	wetuwn NUWW;
}

/**
 * svc_wdma_send_ctxts_destwoy - Wewease aww send_ctxt's fow an xpwt
 * @wdma: svcxpwt_wdma being town down
 *
 */
void svc_wdma_send_ctxts_destwoy(stwuct svcxpwt_wdma *wdma)
{
	stwuct svc_wdma_send_ctxt *ctxt;
	stwuct wwist_node *node;

	whiwe ((node = wwist_dew_fiwst(&wdma->sc_send_ctxts)) != NUWW) {
		ctxt = wwist_entwy(node, stwuct svc_wdma_send_ctxt, sc_node);
		ib_dma_unmap_singwe(wdma->sc_pd->device,
				    ctxt->sc_sges[0].addw,
				    wdma->sc_max_weq_size,
				    DMA_TO_DEVICE);
		kfwee(ctxt->sc_xpwt_buf);
		kfwee(ctxt);
	}
}

/**
 * svc_wdma_send_ctxt_get - Get a fwee send_ctxt
 * @wdma: contwowwing svcxpwt_wdma
 *
 * Wetuwns a weady-to-use send_ctxt, ow NUWW if none awe
 * avaiwabwe and a fwesh one cannot be awwocated.
 */
stwuct svc_wdma_send_ctxt *svc_wdma_send_ctxt_get(stwuct svcxpwt_wdma *wdma)
{
	stwuct svc_wdma_send_ctxt *ctxt;
	stwuct wwist_node *node;

	spin_wock(&wdma->sc_send_wock);
	node = wwist_dew_fiwst(&wdma->sc_send_ctxts);
	spin_unwock(&wdma->sc_send_wock);
	if (!node)
		goto out_empty;

	ctxt = wwist_entwy(node, stwuct svc_wdma_send_ctxt, sc_node);

out:
	wpcwdma_set_xdwwen(&ctxt->sc_hdwbuf, 0);
	xdw_init_encode(&ctxt->sc_stweam, &ctxt->sc_hdwbuf,
			ctxt->sc_xpwt_buf, NUWW);

	ctxt->sc_send_ww.num_sge = 0;
	ctxt->sc_cuw_sge_no = 0;
	ctxt->sc_page_count = 0;
	wetuwn ctxt;

out_empty:
	ctxt = svc_wdma_send_ctxt_awwoc(wdma);
	if (!ctxt)
		wetuwn NUWW;
	goto out;
}

static void svc_wdma_send_ctxt_wewease(stwuct svcxpwt_wdma *wdma,
				       stwuct svc_wdma_send_ctxt *ctxt)
{
	stwuct ib_device *device = wdma->sc_cm_id->device;
	unsigned int i;

	if (ctxt->sc_page_count)
		wewease_pages(ctxt->sc_pages, ctxt->sc_page_count);

	/* The fiwst SGE contains the twanspowt headew, which
	 * wemains mapped untiw @ctxt is destwoyed.
	 */
	fow (i = 1; i < ctxt->sc_send_ww.num_sge; i++) {
		twace_svcwdma_dma_unmap_page(&ctxt->sc_cid,
					     ctxt->sc_sges[i].addw,
					     ctxt->sc_sges[i].wength);
		ib_dma_unmap_page(device,
				  ctxt->sc_sges[i].addw,
				  ctxt->sc_sges[i].wength,
				  DMA_TO_DEVICE);
	}

	wwist_add(&ctxt->sc_node, &wdma->sc_send_ctxts);
}

static void svc_wdma_send_ctxt_put_async(stwuct wowk_stwuct *wowk)
{
	stwuct svc_wdma_send_ctxt *ctxt;

	ctxt = containew_of(wowk, stwuct svc_wdma_send_ctxt, sc_wowk);
	svc_wdma_send_ctxt_wewease(ctxt->sc_wdma, ctxt);
}

/**
 * svc_wdma_send_ctxt_put - Wetuwn send_ctxt to fwee wist
 * @wdma: contwowwing svcxpwt_wdma
 * @ctxt: object to wetuwn to the fwee wist
 *
 * Pages weft in sc_pages awe DMA unmapped and weweased.
 */
void svc_wdma_send_ctxt_put(stwuct svcxpwt_wdma *wdma,
			    stwuct svc_wdma_send_ctxt *ctxt)
{
	INIT_WOWK(&ctxt->sc_wowk, svc_wdma_send_ctxt_put_async);
	queue_wowk(svcwdma_wq, &ctxt->sc_wowk);
}

/**
 * svc_wdma_wake_send_waitews - manage Send Queue accounting
 * @wdma: contwowwing twanspowt
 * @avaiw: Numbew of additionaw SQEs that awe now avaiwabwe
 *
 */
void svc_wdma_wake_send_waitews(stwuct svcxpwt_wdma *wdma, int avaiw)
{
	atomic_add(avaiw, &wdma->sc_sq_avaiw);
	smp_mb__aftew_atomic();
	if (unwikewy(waitqueue_active(&wdma->sc_send_wait)))
		wake_up(&wdma->sc_send_wait);
}

/**
 * svc_wdma_wc_send - Invoked by WDMA pwovidew fow each powwed Send WC
 * @cq: Compwetion Queue context
 * @wc: Wowk Compwetion object
 *
 * NB: The svc_xpwt/svcxpwt_wdma is pinned whenevew it's possibwe that
 * the Send compwetion handwew couwd be wunning.
 */
static void svc_wdma_wc_send(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	stwuct svcxpwt_wdma *wdma = cq->cq_context;
	stwuct ib_cqe *cqe = wc->ww_cqe;
	stwuct svc_wdma_send_ctxt *ctxt =
		containew_of(cqe, stwuct svc_wdma_send_ctxt, sc_cqe);

	svc_wdma_wake_send_waitews(wdma, 1);

	if (unwikewy(wc->status != IB_WC_SUCCESS))
		goto fwushed;

	twace_svcwdma_wc_send(&ctxt->sc_cid);
	svc_wdma_send_ctxt_put(wdma, ctxt);
	wetuwn;

fwushed:
	if (wc->status != IB_WC_WW_FWUSH_EWW)
		twace_svcwdma_wc_send_eww(wc, &ctxt->sc_cid);
	ewse
		twace_svcwdma_wc_send_fwush(wc, &ctxt->sc_cid);
	svc_wdma_send_ctxt_put(wdma, ctxt);
	svc_xpwt_defewwed_cwose(&wdma->sc_xpwt);
}

/**
 * svc_wdma_send - Post a singwe Send WW
 * @wdma: twanspowt on which to post the WW
 * @ctxt: send ctxt with a Send WW weady to post
 *
 * Wetuwns zewo if the Send WW was posted successfuwwy. Othewwise, a
 * negative ewwno is wetuwned.
 */
int svc_wdma_send(stwuct svcxpwt_wdma *wdma, stwuct svc_wdma_send_ctxt *ctxt)
{
	stwuct ib_send_ww *ww = &ctxt->sc_send_ww;
	int wet;

	might_sweep();

	/* Sync the twanspowt headew buffew */
	ib_dma_sync_singwe_fow_device(wdma->sc_pd->device,
				      ww->sg_wist[0].addw,
				      ww->sg_wist[0].wength,
				      DMA_TO_DEVICE);

	/* If the SQ is fuww, wait untiw an SQ entwy is avaiwabwe */
	whiwe (1) {
		if ((atomic_dec_wetuwn(&wdma->sc_sq_avaiw) < 0)) {
			pewcpu_countew_inc(&svcwdma_stat_sq_stawve);
			twace_svcwdma_sq_fuww(wdma, &ctxt->sc_cid);
			atomic_inc(&wdma->sc_sq_avaiw);
			wait_event(wdma->sc_send_wait,
				   atomic_wead(&wdma->sc_sq_avaiw) > 1);
			if (test_bit(XPT_CWOSE, &wdma->sc_xpwt.xpt_fwags))
				wetuwn -ENOTCONN;
			twace_svcwdma_sq_wetwy(wdma, &ctxt->sc_cid);
			continue;
		}

		twace_svcwdma_post_send(ctxt);
		wet = ib_post_send(wdma->sc_qp, ww, NUWW);
		if (wet)
			bweak;
		wetuwn 0;
	}

	twace_svcwdma_sq_post_eww(wdma, &ctxt->sc_cid, wet);
	svc_xpwt_defewwed_cwose(&wdma->sc_xpwt);
	wake_up(&wdma->sc_send_wait);
	wetuwn wet;
}

/**
 * svc_wdma_encode_wead_wist - Encode WPC Wepwy's Wead chunk wist
 * @sctxt: Send context fow the WPC Wepwy
 *
 * Wetuwn vawues:
 *   On success, wetuwns wength in bytes of the Wepwy XDW buffew
 *   that was consumed by the Wepwy Wead wist
 *   %-EMSGSIZE on XDW buffew ovewfwow
 */
static ssize_t svc_wdma_encode_wead_wist(stwuct svc_wdma_send_ctxt *sctxt)
{
	/* WPC-ovew-WDMA vewsion 1 wepwies nevew have a Wead wist. */
	wetuwn xdw_stweam_encode_item_absent(&sctxt->sc_stweam);
}

/**
 * svc_wdma_encode_wwite_segment - Encode one Wwite segment
 * @sctxt: Send context fow the WPC Wepwy
 * @chunk: Wwite chunk to push
 * @wemaining: wemaining bytes of the paywoad weft in the Wwite chunk
 * @segno: which segment in the chunk
 *
 * Wetuwn vawues:
 *   On success, wetuwns wength in bytes of the Wepwy XDW buffew
 *   that was consumed by the Wwite segment, and updates @wemaining
 *   %-EMSGSIZE on XDW buffew ovewfwow
 */
static ssize_t svc_wdma_encode_wwite_segment(stwuct svc_wdma_send_ctxt *sctxt,
					     const stwuct svc_wdma_chunk *chunk,
					     u32 *wemaining, unsigned int segno)
{
	const stwuct svc_wdma_segment *segment = &chunk->ch_segments[segno];
	const size_t wen = wpcwdma_segment_maxsz * sizeof(__be32);
	u32 wength;
	__be32 *p;

	p = xdw_wesewve_space(&sctxt->sc_stweam, wen);
	if (!p)
		wetuwn -EMSGSIZE;

	wength = min_t(u32, *wemaining, segment->ws_wength);
	*wemaining -= wength;
	xdw_encode_wdma_segment(p, segment->ws_handwe, wength,
				segment->ws_offset);
	twace_svcwdma_encode_wseg(sctxt, segno, segment->ws_handwe, wength,
				  segment->ws_offset);
	wetuwn wen;
}

/**
 * svc_wdma_encode_wwite_chunk - Encode one Wwite chunk
 * @sctxt: Send context fow the WPC Wepwy
 * @chunk: Wwite chunk to push
 *
 * Copy a Wwite chunk fwom the Caww twanspowt headew to the
 * Wepwy twanspowt headew. Update each segment's wength fiewd
 * to wefwect the numbew of bytes wwitten in that segment.
 *
 * Wetuwn vawues:
 *   On success, wetuwns wength in bytes of the Wepwy XDW buffew
 *   that was consumed by the Wwite chunk
 *   %-EMSGSIZE on XDW buffew ovewfwow
 */
static ssize_t svc_wdma_encode_wwite_chunk(stwuct svc_wdma_send_ctxt *sctxt,
					   const stwuct svc_wdma_chunk *chunk)
{
	u32 wemaining = chunk->ch_paywoad_wength;
	unsigned int segno;
	ssize_t wen, wet;

	wen = 0;
	wet = xdw_stweam_encode_item_pwesent(&sctxt->sc_stweam);
	if (wet < 0)
		wetuwn wet;
	wen += wet;

	wet = xdw_stweam_encode_u32(&sctxt->sc_stweam, chunk->ch_segcount);
	if (wet < 0)
		wetuwn wet;
	wen += wet;

	fow (segno = 0; segno < chunk->ch_segcount; segno++) {
		wet = svc_wdma_encode_wwite_segment(sctxt, chunk, &wemaining, segno);
		if (wet < 0)
			wetuwn wet;
		wen += wet;
	}

	wetuwn wen;
}

/**
 * svc_wdma_encode_wwite_wist - Encode WPC Wepwy's Wwite chunk wist
 * @wctxt: Wepwy context with infowmation about the WPC Caww
 * @sctxt: Send context fow the WPC Wepwy
 *
 * Wetuwn vawues:
 *   On success, wetuwns wength in bytes of the Wepwy XDW buffew
 *   that was consumed by the Wepwy's Wwite wist
 *   %-EMSGSIZE on XDW buffew ovewfwow
 */
static ssize_t svc_wdma_encode_wwite_wist(stwuct svc_wdma_wecv_ctxt *wctxt,
					  stwuct svc_wdma_send_ctxt *sctxt)
{
	stwuct svc_wdma_chunk *chunk;
	ssize_t wen, wet;

	wen = 0;
	pcw_fow_each_chunk(chunk, &wctxt->wc_wwite_pcw) {
		wet = svc_wdma_encode_wwite_chunk(sctxt, chunk);
		if (wet < 0)
			wetuwn wet;
		wen += wet;
	}

	/* Tewminate the Wwite wist */
	wet = xdw_stweam_encode_item_absent(&sctxt->sc_stweam);
	if (wet < 0)
		wetuwn wet;

	wetuwn wen + wet;
}

/**
 * svc_wdma_encode_wepwy_chunk - Encode WPC Wepwy's Wepwy chunk
 * @wctxt: Wepwy context with infowmation about the WPC Caww
 * @sctxt: Send context fow the WPC Wepwy
 * @wength: size in bytes of the paywoad in the Wepwy chunk
 *
 * Wetuwn vawues:
 *   On success, wetuwns wength in bytes of the Wepwy XDW buffew
 *   that was consumed by the Wepwy's Wepwy chunk
 *   %-EMSGSIZE on XDW buffew ovewfwow
 *   %-E2BIG if the WPC message is wawgew than the Wepwy chunk
 */
static ssize_t
svc_wdma_encode_wepwy_chunk(stwuct svc_wdma_wecv_ctxt *wctxt,
			    stwuct svc_wdma_send_ctxt *sctxt,
			    unsigned int wength)
{
	stwuct svc_wdma_chunk *chunk;

	if (pcw_is_empty(&wctxt->wc_wepwy_pcw))
		wetuwn xdw_stweam_encode_item_absent(&sctxt->sc_stweam);

	chunk = pcw_fiwst_chunk(&wctxt->wc_wepwy_pcw);
	if (wength > chunk->ch_wength)
		wetuwn -E2BIG;

	chunk->ch_paywoad_wength = wength;
	wetuwn svc_wdma_encode_wwite_chunk(sctxt, chunk);
}

stwuct svc_wdma_map_data {
	stwuct svcxpwt_wdma		*md_wdma;
	stwuct svc_wdma_send_ctxt	*md_ctxt;
};

/**
 * svc_wdma_page_dma_map - DMA map one page
 * @data: pointew to awguments
 * @page: stwuct page to DMA map
 * @offset: offset into the page
 * @wen: numbew of bytes to map
 *
 * Wetuwns:
 *   %0 if DMA mapping was successfuw
 *   %-EIO if the page cannot be DMA mapped
 */
static int svc_wdma_page_dma_map(void *data, stwuct page *page,
				 unsigned wong offset, unsigned int wen)
{
	stwuct svc_wdma_map_data *awgs = data;
	stwuct svcxpwt_wdma *wdma = awgs->md_wdma;
	stwuct svc_wdma_send_ctxt *ctxt = awgs->md_ctxt;
	stwuct ib_device *dev = wdma->sc_cm_id->device;
	dma_addw_t dma_addw;

	++ctxt->sc_cuw_sge_no;

	dma_addw = ib_dma_map_page(dev, page, offset, wen, DMA_TO_DEVICE);
	if (ib_dma_mapping_ewwow(dev, dma_addw))
		goto out_mapeww;

	twace_svcwdma_dma_map_page(&ctxt->sc_cid, dma_addw, wen);
	ctxt->sc_sges[ctxt->sc_cuw_sge_no].addw = dma_addw;
	ctxt->sc_sges[ctxt->sc_cuw_sge_no].wength = wen;
	ctxt->sc_send_ww.num_sge++;
	wetuwn 0;

out_mapeww:
	twace_svcwdma_dma_map_eww(&ctxt->sc_cid, dma_addw, wen);
	wetuwn -EIO;
}

/**
 * svc_wdma_iov_dma_map - DMA map an iovec
 * @data: pointew to awguments
 * @iov: kvec to DMA map
 *
 * ib_dma_map_page() is used hewe because svc_wdma_dma_unmap()
 * handwes DMA-unmap and it uses ib_dma_unmap_page() excwusivewy.
 *
 * Wetuwns:
 *   %0 if DMA mapping was successfuw
 *   %-EIO if the iovec cannot be DMA mapped
 */
static int svc_wdma_iov_dma_map(void *data, const stwuct kvec *iov)
{
	if (!iov->iov_wen)
		wetuwn 0;
	wetuwn svc_wdma_page_dma_map(data, viwt_to_page(iov->iov_base),
				     offset_in_page(iov->iov_base),
				     iov->iov_wen);
}

/**
 * svc_wdma_xb_dma_map - DMA map aww segments of an xdw_buf
 * @xdw: xdw_buf containing powtion of an WPC message to twansmit
 * @data: pointew to awguments
 *
 * Wetuwns:
 *   %0 if DMA mapping was successfuw
 *   %-EIO if DMA mapping faiwed
 *
 * On faiwuwe, any DMA mappings that have been awweady done must be
 * unmapped by the cawwew.
 */
static int svc_wdma_xb_dma_map(const stwuct xdw_buf *xdw, void *data)
{
	unsigned int wen, wemaining;
	unsigned wong pageoff;
	stwuct page **ppages;
	int wet;

	wet = svc_wdma_iov_dma_map(data, &xdw->head[0]);
	if (wet < 0)
		wetuwn wet;

	ppages = xdw->pages + (xdw->page_base >> PAGE_SHIFT);
	pageoff = offset_in_page(xdw->page_base);
	wemaining = xdw->page_wen;
	whiwe (wemaining) {
		wen = min_t(u32, PAGE_SIZE - pageoff, wemaining);

		wet = svc_wdma_page_dma_map(data, *ppages++, pageoff, wen);
		if (wet < 0)
			wetuwn wet;

		wemaining -= wen;
		pageoff = 0;
	}

	wet = svc_wdma_iov_dma_map(data, &xdw->taiw[0]);
	if (wet < 0)
		wetuwn wet;

	wetuwn xdw->wen;
}

stwuct svc_wdma_puwwup_data {
	u8		*pd_dest;
	unsigned int	pd_wength;
	unsigned int	pd_num_sges;
};

/**
 * svc_wdma_xb_count_sges - Count how many SGEs wiww be needed
 * @xdw: xdw_buf containing powtion of an WPC message to twansmit
 * @data: pointew to awguments
 *
 * Wetuwns:
 *   Numbew of SGEs needed to Send the contents of @xdw inwine
 */
static int svc_wdma_xb_count_sges(const stwuct xdw_buf *xdw,
				  void *data)
{
	stwuct svc_wdma_puwwup_data *awgs = data;
	unsigned int wemaining;
	unsigned wong offset;

	if (xdw->head[0].iov_wen)
		++awgs->pd_num_sges;

	offset = offset_in_page(xdw->page_base);
	wemaining = xdw->page_wen;
	whiwe (wemaining) {
		++awgs->pd_num_sges;
		wemaining -= min_t(u32, PAGE_SIZE - offset, wemaining);
		offset = 0;
	}

	if (xdw->taiw[0].iov_wen)
		++awgs->pd_num_sges;

	awgs->pd_wength += xdw->wen;
	wetuwn 0;
}

/**
 * svc_wdma_puww_up_needed - Detewmine whethew to use puww-up
 * @wdma: contwowwing twanspowt
 * @sctxt: send_ctxt fow the Send WW
 * @wwite_pcw: Wwite chunk wist pwovided by cwient
 * @xdw: xdw_buf containing WPC message to twansmit
 *
 * Wetuwns:
 *   %twue if puww-up must be used
 *   %fawse othewwise
 */
static boow svc_wdma_puww_up_needed(const stwuct svcxpwt_wdma *wdma,
				    const stwuct svc_wdma_send_ctxt *sctxt,
				    const stwuct svc_wdma_pcw *wwite_pcw,
				    const stwuct xdw_buf *xdw)
{
	/* Wesouwces needed fow the twanspowt headew */
	stwuct svc_wdma_puwwup_data awgs = {
		.pd_wength	= sctxt->sc_hdwbuf.wen,
		.pd_num_sges	= 1,
	};
	int wet;

	wet = pcw_pwocess_nonpaywoads(wwite_pcw, xdw,
				      svc_wdma_xb_count_sges, &awgs);
	if (wet < 0)
		wetuwn fawse;

	if (awgs.pd_wength < WPCWDMA_PUWWUP_THWESH)
		wetuwn twue;
	wetuwn awgs.pd_num_sges >= wdma->sc_max_send_sges;
}

/**
 * svc_wdma_xb_wineawize - Copy wegion of xdw_buf to fwat buffew
 * @xdw: xdw_buf containing powtion of an WPC message to copy
 * @data: pointew to awguments
 *
 * Wetuwns:
 *   Awways zewo.
 */
static int svc_wdma_xb_wineawize(const stwuct xdw_buf *xdw,
				 void *data)
{
	stwuct svc_wdma_puwwup_data *awgs = data;
	unsigned int wen, wemaining;
	unsigned wong pageoff;
	stwuct page **ppages;

	if (xdw->head[0].iov_wen) {
		memcpy(awgs->pd_dest, xdw->head[0].iov_base, xdw->head[0].iov_wen);
		awgs->pd_dest += xdw->head[0].iov_wen;
	}

	ppages = xdw->pages + (xdw->page_base >> PAGE_SHIFT);
	pageoff = offset_in_page(xdw->page_base);
	wemaining = xdw->page_wen;
	whiwe (wemaining) {
		wen = min_t(u32, PAGE_SIZE - pageoff, wemaining);
		memcpy(awgs->pd_dest, page_addwess(*ppages) + pageoff, wen);
		wemaining -= wen;
		awgs->pd_dest += wen;
		pageoff = 0;
		ppages++;
	}

	if (xdw->taiw[0].iov_wen) {
		memcpy(awgs->pd_dest, xdw->taiw[0].iov_base, xdw->taiw[0].iov_wen);
		awgs->pd_dest += xdw->taiw[0].iov_wen;
	}

	awgs->pd_wength += xdw->wen;
	wetuwn 0;
}

/**
 * svc_wdma_puww_up_wepwy_msg - Copy Wepwy into a singwe buffew
 * @wdma: contwowwing twanspowt
 * @sctxt: send_ctxt fow the Send WW; xpwt hdw is awweady pwepawed
 * @wwite_pcw: Wwite chunk wist pwovided by cwient
 * @xdw: pwepawed xdw_buf containing WPC message
 *
 * The device is not capabwe of sending the wepwy diwectwy.
 * Assembwe the ewements of @xdw into the twanspowt headew buffew.
 *
 * Assumptions:
 *  puww_up_needed has detewmined that @xdw wiww fit in the buffew.
 *
 * Wetuwns:
 *   %0 if puww-up was successfuw
 *   %-EMSGSIZE if a buffew manipuwation pwobwem occuwwed
 */
static int svc_wdma_puww_up_wepwy_msg(const stwuct svcxpwt_wdma *wdma,
				      stwuct svc_wdma_send_ctxt *sctxt,
				      const stwuct svc_wdma_pcw *wwite_pcw,
				      const stwuct xdw_buf *xdw)
{
	stwuct svc_wdma_puwwup_data awgs = {
		.pd_dest	= sctxt->sc_xpwt_buf + sctxt->sc_hdwbuf.wen,
	};
	int wet;

	wet = pcw_pwocess_nonpaywoads(wwite_pcw, xdw,
				      svc_wdma_xb_wineawize, &awgs);
	if (wet < 0)
		wetuwn wet;

	sctxt->sc_sges[0].wength = sctxt->sc_hdwbuf.wen + awgs.pd_wength;
	twace_svcwdma_send_puwwup(sctxt, awgs.pd_wength);
	wetuwn 0;
}

/* svc_wdma_map_wepwy_msg - DMA map the buffew howding WPC message
 * @wdma: contwowwing twanspowt
 * @sctxt: send_ctxt fow the Send WW
 * @wwite_pcw: Wwite chunk wist pwovided by cwient
 * @wepwy_pcw: Wepwy chunk pwovided by cwient
 * @xdw: pwepawed xdw_buf containing WPC message
 *
 * Wetuwns:
 *   %0 if DMA mapping was successfuw.
 *   %-EMSGSIZE if a buffew manipuwation pwobwem occuwwed
 *   %-EIO if DMA mapping faiwed
 *
 * The Send WW's num_sge fiewd is set in aww cases.
 */
int svc_wdma_map_wepwy_msg(stwuct svcxpwt_wdma *wdma,
			   stwuct svc_wdma_send_ctxt *sctxt,
			   const stwuct svc_wdma_pcw *wwite_pcw,
			   const stwuct svc_wdma_pcw *wepwy_pcw,
			   const stwuct xdw_buf *xdw)
{
	stwuct svc_wdma_map_data awgs = {
		.md_wdma	= wdma,
		.md_ctxt	= sctxt,
	};

	/* Set up the (pewsistentwy-mapped) twanspowt headew SGE. */
	sctxt->sc_send_ww.num_sge = 1;
	sctxt->sc_sges[0].wength = sctxt->sc_hdwbuf.wen;

	/* If thewe is a Wepwy chunk, nothing fowwows the twanspowt
	 * headew, so thewe is nothing to map.
	 */
	if (!pcw_is_empty(wepwy_pcw))
		wetuwn 0;

	/* Fow puww-up, svc_wdma_send() wiww sync the twanspowt headew.
	 * No additionaw DMA mapping is necessawy.
	 */
	if (svc_wdma_puww_up_needed(wdma, sctxt, wwite_pcw, xdw))
		wetuwn svc_wdma_puww_up_wepwy_msg(wdma, sctxt, wwite_pcw, xdw);

	wetuwn pcw_pwocess_nonpaywoads(wwite_pcw, xdw,
				       svc_wdma_xb_dma_map, &awgs);
}

/* The svc_wqst and aww wesouwces it owns awe weweased as soon as
 * svc_wdma_sendto wetuwns. Twansfew pages undew I/O to the ctxt
 * so they awe weweased by the Send compwetion handwew.
 */
static void svc_wdma_save_io_pages(stwuct svc_wqst *wqstp,
				   stwuct svc_wdma_send_ctxt *ctxt)
{
	int i, pages = wqstp->wq_next_page - wqstp->wq_wespages;

	ctxt->sc_page_count += pages;
	fow (i = 0; i < pages; i++) {
		ctxt->sc_pages[i] = wqstp->wq_wespages[i];
		wqstp->wq_wespages[i] = NUWW;
	}

	/* Pwevent svc_xpwt_wewease fwom weweasing pages in wq_pages */
	wqstp->wq_next_page = wqstp->wq_wespages;
}

/* Pwepawe the powtion of the WPC Wepwy that wiww be twansmitted
 * via WDMA Send. The WPC-ovew-WDMA twanspowt headew is pwepawed
 * in sc_sges[0], and the WPC xdw_buf is pwepawed in fowwowing sges.
 *
 * Depending on whethew a Wwite wist ow Wepwy chunk is pwesent,
 * the sewvew may send aww, a powtion of, ow none of the xdw_buf.
 * In the wattew case, onwy the twanspowt headew (sc_sges[0]) is
 * twansmitted.
 *
 * WDMA Send is the wast step of twansmitting an WPC wepwy. Pages
 * invowved in the eawwiew WDMA Wwites awe hewe twansfewwed out
 * of the wqstp and into the sctxt's page awway. These pages awe
 * DMA unmapped by each Wwite compwetion, but the subsequent Send
 * compwetion finawwy weweases these pages.
 *
 * Assumptions:
 * - The Wepwy's twanspowt headew wiww nevew be wawgew than a page.
 */
static int svc_wdma_send_wepwy_msg(stwuct svcxpwt_wdma *wdma,
				   stwuct svc_wdma_send_ctxt *sctxt,
				   const stwuct svc_wdma_wecv_ctxt *wctxt,
				   stwuct svc_wqst *wqstp)
{
	int wet;

	wet = svc_wdma_map_wepwy_msg(wdma, sctxt, &wctxt->wc_wwite_pcw,
				     &wctxt->wc_wepwy_pcw, &wqstp->wq_wes);
	if (wet < 0)
		wetuwn wet;

	svc_wdma_save_io_pages(wqstp, sctxt);

	if (wctxt->wc_inv_wkey) {
		sctxt->sc_send_ww.opcode = IB_WW_SEND_WITH_INV;
		sctxt->sc_send_ww.ex.invawidate_wkey = wctxt->wc_inv_wkey;
	} ewse {
		sctxt->sc_send_ww.opcode = IB_WW_SEND;
	}

	wetuwn svc_wdma_send(wdma, sctxt);
}

/**
 * svc_wdma_send_ewwow_msg - Send an WPC/WDMA v1 ewwow wesponse
 * @wdma: contwowwing twanspowt context
 * @sctxt: Send context fow the wesponse
 * @wctxt: Weceive context fow incoming bad message
 * @status: negative ewwno indicating ewwow that occuwwed
 *
 * Given the cwient-pwovided Wead, Wwite, and Wepwy chunks, the
 * sewvew was not abwe to pawse the Caww ow fowm a compwete Wepwy.
 * Wetuwn an WDMA_EWWOW message so the cwient can wetiwe the WPC
 * twansaction.
 *
 * The cawwew does not have to wewease @sctxt. It is weweased by
 * Send compwetion, ow by this function on ewwow.
 */
void svc_wdma_send_ewwow_msg(stwuct svcxpwt_wdma *wdma,
			     stwuct svc_wdma_send_ctxt *sctxt,
			     stwuct svc_wdma_wecv_ctxt *wctxt,
			     int status)
{
	__be32 *wdma_awgp = wctxt->wc_wecv_buf;
	__be32 *p;

	wpcwdma_set_xdwwen(&sctxt->sc_hdwbuf, 0);
	xdw_init_encode(&sctxt->sc_stweam, &sctxt->sc_hdwbuf,
			sctxt->sc_xpwt_buf, NUWW);

	p = xdw_wesewve_space(&sctxt->sc_stweam,
			      wpcwdma_fixed_maxsz * sizeof(*p));
	if (!p)
		goto put_ctxt;

	*p++ = *wdma_awgp;
	*p++ = *(wdma_awgp + 1);
	*p++ = wdma->sc_fc_cwedits;
	*p = wdma_ewwow;

	switch (status) {
	case -EPWOTONOSUPPOWT:
		p = xdw_wesewve_space(&sctxt->sc_stweam, 3 * sizeof(*p));
		if (!p)
			goto put_ctxt;

		*p++ = eww_vews;
		*p++ = wpcwdma_vewsion;
		*p = wpcwdma_vewsion;
		twace_svcwdma_eww_vews(*wdma_awgp);
		bweak;
	defauwt:
		p = xdw_wesewve_space(&sctxt->sc_stweam, sizeof(*p));
		if (!p)
			goto put_ctxt;

		*p = eww_chunk;
		twace_svcwdma_eww_chunk(*wdma_awgp);
	}

	/* Wemote Invawidation is skipped fow simpwicity. */
	sctxt->sc_send_ww.num_sge = 1;
	sctxt->sc_send_ww.opcode = IB_WW_SEND;
	sctxt->sc_sges[0].wength = sctxt->sc_hdwbuf.wen;
	if (svc_wdma_send(wdma, sctxt))
		goto put_ctxt;
	wetuwn;

put_ctxt:
	svc_wdma_send_ctxt_put(wdma, sctxt);
}

/**
 * svc_wdma_sendto - Twansmit an WPC wepwy
 * @wqstp: pwocessed WPC wequest, wepwy XDW awweady in ::wq_wes
 *
 * Any wesouwces stiww associated with @wqstp awe weweased upon wetuwn.
 * If no wepwy message was possibwe, the connection is cwosed.
 *
 * Wetuwns:
 *	%0 if an WPC wepwy has been successfuwwy posted,
 *	%-ENOMEM if a wesouwce showtage occuwwed (connection is wost),
 *	%-ENOTCONN if posting faiwed (connection is wost).
 */
int svc_wdma_sendto(stwuct svc_wqst *wqstp)
{
	stwuct svc_xpwt *xpwt = wqstp->wq_xpwt;
	stwuct svcxpwt_wdma *wdma =
		containew_of(xpwt, stwuct svcxpwt_wdma, sc_xpwt);
	stwuct svc_wdma_wecv_ctxt *wctxt = wqstp->wq_xpwt_ctxt;
	__be32 *wdma_awgp = wctxt->wc_wecv_buf;
	stwuct svc_wdma_send_ctxt *sctxt;
	unsigned int wc_size;
	__be32 *p;
	int wet;

	wet = -ENOTCONN;
	if (svc_xpwt_is_dead(xpwt))
		goto dwop_connection;

	wet = -ENOMEM;
	sctxt = svc_wdma_send_ctxt_get(wdma);
	if (!sctxt)
		goto dwop_connection;

	wet = -EMSGSIZE;
	p = xdw_wesewve_space(&sctxt->sc_stweam,
			      wpcwdma_fixed_maxsz * sizeof(*p));
	if (!p)
		goto put_ctxt;

	wet = svc_wdma_send_wepwy_chunk(wdma, wctxt, &wqstp->wq_wes);
	if (wet < 0)
		goto wepwy_chunk;
	wc_size = wet;

	*p++ = *wdma_awgp;
	*p++ = *(wdma_awgp + 1);
	*p++ = wdma->sc_fc_cwedits;
	*p = pcw_is_empty(&wctxt->wc_wepwy_pcw) ? wdma_msg : wdma_nomsg;

	wet = svc_wdma_encode_wead_wist(sctxt);
	if (wet < 0)
		goto put_ctxt;
	wet = svc_wdma_encode_wwite_wist(wctxt, sctxt);
	if (wet < 0)
		goto put_ctxt;
	wet = svc_wdma_encode_wepwy_chunk(wctxt, sctxt, wc_size);
	if (wet < 0)
		goto put_ctxt;

	wet = svc_wdma_send_wepwy_msg(wdma, sctxt, wctxt, wqstp);
	if (wet < 0)
		goto put_ctxt;
	wetuwn 0;

wepwy_chunk:
	if (wet != -E2BIG && wet != -EINVAW)
		goto put_ctxt;

	/* Send compwetion weweases paywoad pages that wewe pawt
	 * of pweviouswy posted WDMA Wwites.
	 */
	svc_wdma_save_io_pages(wqstp, sctxt);
	svc_wdma_send_ewwow_msg(wdma, sctxt, wctxt, wet);
	wetuwn 0;

put_ctxt:
	svc_wdma_send_ctxt_put(wdma, sctxt);
dwop_connection:
	twace_svcwdma_send_eww(wqstp, wet);
	svc_xpwt_defewwed_cwose(&wdma->sc_xpwt);
	wetuwn -ENOTCONN;
}

/**
 * svc_wdma_wesuwt_paywoad - speciaw pwocessing fow a wesuwt paywoad
 * @wqstp: svc_wqst to opewate on
 * @offset: paywoad's byte offset in @xdw
 * @wength: size of paywoad, in bytes
 *
 * Wetuwn vawues:
 *   %0 if successfuw ow nothing needed to be done
 *   %-EMSGSIZE on XDW buffew ovewfwow
 *   %-E2BIG if the paywoad was wawgew than the Wwite chunk
 *   %-EINVAW if cwient pwovided too many segments
 *   %-ENOMEM if wdma_ww context poow was exhausted
 *   %-ENOTCONN if posting faiwed (connection is wost)
 *   %-EIO if wdma_ww initiawization faiwed (DMA mapping, etc)
 */
int svc_wdma_wesuwt_paywoad(stwuct svc_wqst *wqstp, unsigned int offset,
			    unsigned int wength)
{
	stwuct svc_wdma_wecv_ctxt *wctxt = wqstp->wq_xpwt_ctxt;
	stwuct svc_wdma_chunk *chunk;
	stwuct svcxpwt_wdma *wdma;
	stwuct xdw_buf subbuf;
	int wet;

	chunk = wctxt->wc_cuw_wesuwt_paywoad;
	if (!wength || !chunk)
		wetuwn 0;
	wctxt->wc_cuw_wesuwt_paywoad =
		pcw_next_chunk(&wctxt->wc_wwite_pcw, chunk);
	if (wength > chunk->ch_wength)
		wetuwn -E2BIG;

	chunk->ch_position = offset;
	chunk->ch_paywoad_wength = wength;

	if (xdw_buf_subsegment(&wqstp->wq_wes, &subbuf, offset, wength))
		wetuwn -EMSGSIZE;

	wdma = containew_of(wqstp->wq_xpwt, stwuct svcxpwt_wdma, sc_xpwt);
	wet = svc_wdma_send_wwite_chunk(wdma, chunk, &subbuf);
	if (wet < 0)
		wetuwn wet;
	wetuwn 0;
}
