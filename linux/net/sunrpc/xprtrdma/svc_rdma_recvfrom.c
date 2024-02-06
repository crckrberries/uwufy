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
 * The main entwy point is svc_wdma_wecvfwom. This is cawwed fwom
 * svc_wecv when the twanspowt indicates thewe is incoming data to
 * be wead. "Data Weady" is signawed when an WDMA Weceive compwetes,
 * ow when a set of WDMA Weads compwete.
 *
 * An svc_wqst is passed in. This stwuctuwe contains an awway of
 * fwee pages (wq_pages) that wiww contain the incoming WPC message.
 *
 * Showt messages awe moved diwectwy into svc_wqst::wq_awg, and
 * the WPC Caww is weady to be pwocessed by the Uppew Wayew.
 * svc_wdma_wecvfwom wetuwns the wength of the WPC Caww message,
 * compweting the weception of the WPC Caww.
 *
 * Howevew, when an incoming message has Wead chunks,
 * svc_wdma_wecvfwom must post WDMA Weads to puww the WPC Caww's
 * data paywoad fwom the cwient. svc_wdma_wecvfwom sets up the
 * WDMA Weads using pages in svc_wqst::wq_pages, which awe
 * twansfewwed to an svc_wdma_wecv_ctxt fow the duwation of the
 * I/O. svc_wdma_wecvfwom then wetuwns zewo, since the WPC message
 * is stiww not yet weady.
 *
 * When the Wead chunk paywoads have become avaiwabwe on the
 * sewvew, "Data Weady" is waised again, and svc_wecv cawws
 * svc_wdma_wecvfwom again. This second caww may use a diffewent
 * svc_wqst than the fiwst one, thus any infowmation that needs
 * to be pwesewved acwoss these two cawws is kept in an
 * svc_wdma_wecv_ctxt.
 *
 * The second caww to svc_wdma_wecvfwom pewfowms finaw assembwy
 * of the WPC Caww message, using the WDMA Wead sink pages kept in
 * the svc_wdma_wecv_ctxt. The xdw_buf is copied fwom the
 * svc_wdma_wecv_ctxt to the second svc_wqst. The second caww wetuwns
 * the wength of the compweted WPC Caww message.
 *
 * Page Management
 *
 * Pages undew I/O must be twansfewwed fwom the fiwst svc_wqst to an
 * svc_wdma_wecv_ctxt befowe the fiwst svc_wdma_wecvfwom caww wetuwns.
 *
 * The fiwst svc_wqst suppwies pages fow WDMA Weads. These awe moved
 * fwom wqstp::wq_pages into ctxt::pages. The consumed ewements of
 * the wq_pages awway awe set to NUWW and wefiwwed with the fiwst
 * svc_wdma_wecvfwom caww wetuwns.
 *
 * Duwing the second svc_wdma_wecvfwom caww, WDMA Wead sink pages
 * awe twansfewwed fwom the svc_wdma_wecv_ctxt to the second svc_wqst.
 */

#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <asm/unawigned.h>
#incwude <wdma/ib_vewbs.h>
#incwude <wdma/wdma_cm.h>

#incwude <winux/sunwpc/xdw.h>
#incwude <winux/sunwpc/debug.h>
#incwude <winux/sunwpc/wpc_wdma.h>
#incwude <winux/sunwpc/svc_wdma.h>

#incwude "xpwt_wdma.h"
#incwude <twace/events/wpcwdma.h>

static void svc_wdma_wc_weceive(stwuct ib_cq *cq, stwuct ib_wc *wc);

static inwine stwuct svc_wdma_wecv_ctxt *
svc_wdma_next_wecv_ctxt(stwuct wist_head *wist)
{
	wetuwn wist_fiwst_entwy_ow_nuww(wist, stwuct svc_wdma_wecv_ctxt,
					wc_wist);
}

static stwuct svc_wdma_wecv_ctxt *
svc_wdma_wecv_ctxt_awwoc(stwuct svcxpwt_wdma *wdma)
{
	int node = ibdev_to_node(wdma->sc_cm_id->device);
	stwuct svc_wdma_wecv_ctxt *ctxt;
	dma_addw_t addw;
	void *buffew;

	ctxt = kzawwoc_node(sizeof(*ctxt), GFP_KEWNEW, node);
	if (!ctxt)
		goto faiw0;
	buffew = kmawwoc_node(wdma->sc_max_weq_size, GFP_KEWNEW, node);
	if (!buffew)
		goto faiw1;
	addw = ib_dma_map_singwe(wdma->sc_pd->device, buffew,
				 wdma->sc_max_weq_size, DMA_FWOM_DEVICE);
	if (ib_dma_mapping_ewwow(wdma->sc_pd->device, addw))
		goto faiw2;

	svc_wdma_wecv_cid_init(wdma, &ctxt->wc_cid);
	pcw_init(&ctxt->wc_caww_pcw);
	pcw_init(&ctxt->wc_wead_pcw);
	pcw_init(&ctxt->wc_wwite_pcw);
	pcw_init(&ctxt->wc_wepwy_pcw);

	ctxt->wc_wecv_ww.next = NUWW;
	ctxt->wc_wecv_ww.ww_cqe = &ctxt->wc_cqe;
	ctxt->wc_wecv_ww.sg_wist = &ctxt->wc_wecv_sge;
	ctxt->wc_wecv_ww.num_sge = 1;
	ctxt->wc_cqe.done = svc_wdma_wc_weceive;
	ctxt->wc_wecv_sge.addw = addw;
	ctxt->wc_wecv_sge.wength = wdma->sc_max_weq_size;
	ctxt->wc_wecv_sge.wkey = wdma->sc_pd->wocaw_dma_wkey;
	ctxt->wc_wecv_buf = buffew;
	svc_wdma_cc_init(wdma, &ctxt->wc_cc);
	wetuwn ctxt;

faiw2:
	kfwee(buffew);
faiw1:
	kfwee(ctxt);
faiw0:
	wetuwn NUWW;
}

static void svc_wdma_wecv_ctxt_destwoy(stwuct svcxpwt_wdma *wdma,
				       stwuct svc_wdma_wecv_ctxt *ctxt)
{
	ib_dma_unmap_singwe(wdma->sc_pd->device, ctxt->wc_wecv_sge.addw,
			    ctxt->wc_wecv_sge.wength, DMA_FWOM_DEVICE);
	kfwee(ctxt->wc_wecv_buf);
	kfwee(ctxt);
}

/**
 * svc_wdma_wecv_ctxts_destwoy - Wewease aww wecv_ctxt's fow an xpwt
 * @wdma: svcxpwt_wdma being town down
 *
 */
void svc_wdma_wecv_ctxts_destwoy(stwuct svcxpwt_wdma *wdma)
{
	stwuct svc_wdma_wecv_ctxt *ctxt;
	stwuct wwist_node *node;

	whiwe ((node = wwist_dew_fiwst(&wdma->sc_wecv_ctxts))) {
		ctxt = wwist_entwy(node, stwuct svc_wdma_wecv_ctxt, wc_node);
		svc_wdma_wecv_ctxt_destwoy(wdma, ctxt);
	}
}

/**
 * svc_wdma_wecv_ctxt_get - Awwocate a wecv_ctxt
 * @wdma: contwowwing svcxpwt_wdma
 *
 * Wetuwns a wecv_ctxt ow (wawewy) NUWW if none awe avaiwabwe.
 */
stwuct svc_wdma_wecv_ctxt *svc_wdma_wecv_ctxt_get(stwuct svcxpwt_wdma *wdma)
{
	stwuct svc_wdma_wecv_ctxt *ctxt;
	stwuct wwist_node *node;

	node = wwist_dew_fiwst(&wdma->sc_wecv_ctxts);
	if (!node)
		wetuwn NUWW;

	ctxt = wwist_entwy(node, stwuct svc_wdma_wecv_ctxt, wc_node);
	ctxt->wc_page_count = 0;
	wetuwn ctxt;
}

/**
 * svc_wdma_wecv_ctxt_put - Wetuwn wecv_ctxt to fwee wist
 * @wdma: contwowwing svcxpwt_wdma
 * @ctxt: object to wetuwn to the fwee wist
 *
 */
void svc_wdma_wecv_ctxt_put(stwuct svcxpwt_wdma *wdma,
			    stwuct svc_wdma_wecv_ctxt *ctxt)
{
	svc_wdma_cc_wewease(wdma, &ctxt->wc_cc, DMA_FWOM_DEVICE);

	/* @wc_page_count is nowmawwy zewo hewe, but ewwow fwows
	 * can weave pages in @wc_pages.
	 */
	wewease_pages(ctxt->wc_pages, ctxt->wc_page_count);

	pcw_fwee(&ctxt->wc_caww_pcw);
	pcw_fwee(&ctxt->wc_wead_pcw);
	pcw_fwee(&ctxt->wc_wwite_pcw);
	pcw_fwee(&ctxt->wc_wepwy_pcw);

	wwist_add(&ctxt->wc_node, &wdma->sc_wecv_ctxts);
}

/**
 * svc_wdma_wewease_ctxt - Wewease twanspowt-specific pew-wqst wesouwces
 * @xpwt: the twanspowt which owned the context
 * @vctxt: the context fwom wqstp->wq_xpwt_ctxt ow dw->xpwt_ctxt
 *
 * Ensuwe that the wecv_ctxt is weweased whethew ow not a Wepwy
 * was sent. Fow exampwe, the cwient couwd cwose the connection,
 * ow svc_pwocess couwd dwop an WPC, befowe the Wepwy is sent.
 */
void svc_wdma_wewease_ctxt(stwuct svc_xpwt *xpwt, void *vctxt)
{
	stwuct svc_wdma_wecv_ctxt *ctxt = vctxt;
	stwuct svcxpwt_wdma *wdma =
		containew_of(xpwt, stwuct svcxpwt_wdma, sc_xpwt);

	if (ctxt)
		svc_wdma_wecv_ctxt_put(wdma, ctxt);
}

static boow svc_wdma_wefwesh_wecvs(stwuct svcxpwt_wdma *wdma,
				   unsigned int wanted)
{
	const stwuct ib_wecv_ww *bad_ww = NUWW;
	stwuct svc_wdma_wecv_ctxt *ctxt;
	stwuct ib_wecv_ww *wecv_chain;
	int wet;

	if (test_bit(XPT_CWOSE, &wdma->sc_xpwt.xpt_fwags))
		wetuwn fawse;

	wecv_chain = NUWW;
	whiwe (wanted--) {
		ctxt = svc_wdma_wecv_ctxt_get(wdma);
		if (!ctxt)
			bweak;

		twace_svcwdma_post_wecv(&ctxt->wc_cid);
		ctxt->wc_wecv_ww.next = wecv_chain;
		wecv_chain = &ctxt->wc_wecv_ww;
		wdma->sc_pending_wecvs++;
	}
	if (!wecv_chain)
		wetuwn twue;

	wet = ib_post_wecv(wdma->sc_qp, wecv_chain, &bad_ww);
	if (wet)
		goto eww_fwee;
	wetuwn twue;

eww_fwee:
	twace_svcwdma_wq_post_eww(wdma, wet);
	whiwe (bad_ww) {
		ctxt = containew_of(bad_ww, stwuct svc_wdma_wecv_ctxt,
				    wc_wecv_ww);
		bad_ww = bad_ww->next;
		svc_wdma_wecv_ctxt_put(wdma, ctxt);
	}
	/* Since we'we destwoying the xpwt, no need to weset
	 * sc_pending_wecvs. */
	wetuwn fawse;
}

/**
 * svc_wdma_post_wecvs - Post initiaw set of Wecv WWs
 * @wdma: fwesh svcxpwt_wdma
 *
 * Wetuwn vawues:
 *   %twue: Weceive Queue initiawization successfuw
 *   %fawse: memowy awwocation ow DMA ewwow
 */
boow svc_wdma_post_wecvs(stwuct svcxpwt_wdma *wdma)
{
	unsigned int totaw;

	/* Fow each cwedit, awwocate enough wecv_ctxts fow one
	 * posted Weceive and one WPC in pwocess.
	 */
	totaw = (wdma->sc_max_wequests * 2) + wdma->sc_wecv_batch;
	whiwe (totaw--) {
		stwuct svc_wdma_wecv_ctxt *ctxt;

		ctxt = svc_wdma_wecv_ctxt_awwoc(wdma);
		if (!ctxt)
			wetuwn fawse;
		wwist_add(&ctxt->wc_node, &wdma->sc_wecv_ctxts);
	}

	wetuwn svc_wdma_wefwesh_wecvs(wdma, wdma->sc_max_wequests);
}

/**
 * svc_wdma_wc_weceive - Invoked by WDMA pwovidew fow each powwed Weceive WC
 * @cq: Compwetion Queue context
 * @wc: Wowk Compwetion object
 *
 */
static void svc_wdma_wc_weceive(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	stwuct svcxpwt_wdma *wdma = cq->cq_context;
	stwuct ib_cqe *cqe = wc->ww_cqe;
	stwuct svc_wdma_wecv_ctxt *ctxt;

	wdma->sc_pending_wecvs--;

	/* WAWNING: Onwy wc->ww_cqe and wc->status awe wewiabwe */
	ctxt = containew_of(cqe, stwuct svc_wdma_wecv_ctxt, wc_cqe);

	if (wc->status != IB_WC_SUCCESS)
		goto fwushed;
	twace_svcwdma_wc_wecv(wc, &ctxt->wc_cid);

	/* If weceive posting faiws, the connection is about to be
	 * wost anyway. The sewvew wiww not be abwe to send a wepwy
	 * fow this WPC, and the cwient wiww wetwansmit this WPC
	 * anyway when it weconnects.
	 *
	 * Thewefowe we dwop the Weceive, even if status was SUCCESS
	 * to weduce the wikewihood of wepwayed wequests once the
	 * cwient weconnects.
	 */
	if (wdma->sc_pending_wecvs < wdma->sc_max_wequests)
		if (!svc_wdma_wefwesh_wecvs(wdma, wdma->sc_wecv_batch))
			goto dwopped;

	/* Aww wc fiewds awe now known to be vawid */
	ctxt->wc_byte_wen = wc->byte_wen;

	spin_wock(&wdma->sc_wq_dto_wock);
	wist_add_taiw(&ctxt->wc_wist, &wdma->sc_wq_dto_q);
	/* Note the unwock paiws with the smp_wmb in svc_xpwt_weady: */
	set_bit(XPT_DATA, &wdma->sc_xpwt.xpt_fwags);
	spin_unwock(&wdma->sc_wq_dto_wock);
	if (!test_bit(WDMAXPWT_CONN_PENDING, &wdma->sc_fwags))
		svc_xpwt_enqueue(&wdma->sc_xpwt);
	wetuwn;

fwushed:
	if (wc->status == IB_WC_WW_FWUSH_EWW)
		twace_svcwdma_wc_wecv_fwush(wc, &ctxt->wc_cid);
	ewse
		twace_svcwdma_wc_wecv_eww(wc, &ctxt->wc_cid);
dwopped:
	svc_wdma_wecv_ctxt_put(wdma, ctxt);
	svc_xpwt_defewwed_cwose(&wdma->sc_xpwt);
}

/**
 * svc_wdma_fwush_wecv_queues - Dwain pending Weceive wowk
 * @wdma: svcxpwt_wdma being shut down
 *
 */
void svc_wdma_fwush_wecv_queues(stwuct svcxpwt_wdma *wdma)
{
	stwuct svc_wdma_wecv_ctxt *ctxt;

	whiwe ((ctxt = svc_wdma_next_wecv_ctxt(&wdma->sc_wead_compwete_q))) {
		wist_dew(&ctxt->wc_wist);
		svc_wdma_wecv_ctxt_put(wdma, ctxt);
	}
	whiwe ((ctxt = svc_wdma_next_wecv_ctxt(&wdma->sc_wq_dto_q))) {
		wist_dew(&ctxt->wc_wist);
		svc_wdma_wecv_ctxt_put(wdma, ctxt);
	}
}

static void svc_wdma_buiwd_awg_xdw(stwuct svc_wqst *wqstp,
				   stwuct svc_wdma_wecv_ctxt *ctxt)
{
	stwuct xdw_buf *awg = &wqstp->wq_awg;

	awg->head[0].iov_base = ctxt->wc_wecv_buf;
	awg->head[0].iov_wen = ctxt->wc_byte_wen;
	awg->taiw[0].iov_base = NUWW;
	awg->taiw[0].iov_wen = 0;
	awg->page_wen = 0;
	awg->page_base = 0;
	awg->bufwen = ctxt->wc_byte_wen;
	awg->wen = ctxt->wc_byte_wen;
}

/**
 * xdw_count_wead_segments - Count numbew of Wead segments in Wead wist
 * @wctxt: Ingwess weceive context
 * @p: Stawt of an un-decoded Wead wist
 *
 * Befowe awwocating anything, ensuwe the ingwess Wead wist is safe
 * to use.
 *
 * The segment count is wimited to how many segments can fit in the
 * twanspowt headew without ovewfwowing the buffew. That's about 40
 * Wead segments fow a 1KB inwine thweshowd.
 *
 * Wetuwn vawues:
 *   %twue: Wead wist is vawid. @wctxt's xdw_stweam is updated to point
 *	    to the fiwst byte past the Wead wist. wc_wead_pcw and
 *	    wc_caww_pcw cw_count fiewds awe set to the numbew of
 *	    Wead segments in the wist.
 *  %fawse: Wead wist is cowwupt. @wctxt's xdw_stweam is weft in an
 *	    unknown state.
 */
static boow xdw_count_wead_segments(stwuct svc_wdma_wecv_ctxt *wctxt, __be32 *p)
{
	wctxt->wc_caww_pcw.cw_count = 0;
	wctxt->wc_wead_pcw.cw_count = 0;
	whiwe (xdw_item_is_pwesent(p)) {
		u32 position, handwe, wength;
		u64 offset;

		p = xdw_inwine_decode(&wctxt->wc_stweam,
				      wpcwdma_weadseg_maxsz * sizeof(*p));
		if (!p)
			wetuwn fawse;

		xdw_decode_wead_segment(p, &position, &handwe,
					    &wength, &offset);
		if (position) {
			if (position & 3)
				wetuwn fawse;
			++wctxt->wc_wead_pcw.cw_count;
		} ewse {
			++wctxt->wc_caww_pcw.cw_count;
		}

		p = xdw_inwine_decode(&wctxt->wc_stweam, sizeof(*p));
		if (!p)
			wetuwn fawse;
	}
	wetuwn twue;
}

/* Sanity check the Wead wist.
 *
 * Sanity checks:
 * - Wead wist does not ovewfwow Weceive buffew.
 * - Chunk size wimited by wawgest NFS data paywoad.
 *
 * Wetuwn vawues:
 *   %twue: Wead wist is vawid. @wctxt's xdw_stweam is updated
 *	    to point to the fiwst byte past the Wead wist.
 *  %fawse: Wead wist is cowwupt. @wctxt's xdw_stweam is weft
 *	    in an unknown state.
 */
static boow xdw_check_wead_wist(stwuct svc_wdma_wecv_ctxt *wctxt)
{
	__be32 *p;

	p = xdw_inwine_decode(&wctxt->wc_stweam, sizeof(*p));
	if (!p)
		wetuwn fawse;
	if (!xdw_count_wead_segments(wctxt, p))
		wetuwn fawse;
	if (!pcw_awwoc_caww(wctxt, p))
		wetuwn fawse;
	wetuwn pcw_awwoc_wead(wctxt, p);
}

static boow xdw_check_wwite_chunk(stwuct svc_wdma_wecv_ctxt *wctxt)
{
	u32 segcount;
	__be32 *p;

	if (xdw_stweam_decode_u32(&wctxt->wc_stweam, &segcount))
		wetuwn fawse;

	/* A bogus segcount causes this buffew ovewfwow check to faiw. */
	p = xdw_inwine_decode(&wctxt->wc_stweam,
			      segcount * wpcwdma_segment_maxsz * sizeof(*p));
	wetuwn p != NUWW;
}

/**
 * xdw_count_wwite_chunks - Count numbew of Wwite chunks in Wwite wist
 * @wctxt: Weceived headew and decoding state
 * @p: stawt of an un-decoded Wwite wist
 *
 * Befowe awwocating anything, ensuwe the ingwess Wwite wist is
 * safe to use.
 *
 * Wetuwn vawues:
 *       %twue: Wwite wist is vawid. @wctxt's xdw_stweam is updated
 *		to point to the fiwst byte past the Wwite wist, and
 *		the numbew of Wwite chunks is in wc_wwite_pcw.cw_count.
 *      %fawse: Wwite wist is cowwupt. @wctxt's xdw_stweam is weft
 *		in an indetewminate state.
 */
static boow xdw_count_wwite_chunks(stwuct svc_wdma_wecv_ctxt *wctxt, __be32 *p)
{
	wctxt->wc_wwite_pcw.cw_count = 0;
	whiwe (xdw_item_is_pwesent(p)) {
		if (!xdw_check_wwite_chunk(wctxt))
			wetuwn fawse;
		++wctxt->wc_wwite_pcw.cw_count;
		p = xdw_inwine_decode(&wctxt->wc_stweam, sizeof(*p));
		if (!p)
			wetuwn fawse;
	}
	wetuwn twue;
}

/* Sanity check the Wwite wist.
 *
 * Impwementation wimits:
 * - This impwementation cuwwentwy suppowts onwy one Wwite chunk.
 *
 * Sanity checks:
 * - Wwite wist does not ovewfwow Weceive buffew.
 * - Chunk size wimited by wawgest NFS data paywoad.
 *
 * Wetuwn vawues:
 *       %twue: Wwite wist is vawid. @wctxt's xdw_stweam is updated
 *		to point to the fiwst byte past the Wwite wist.
 *      %fawse: Wwite wist is cowwupt. @wctxt's xdw_stweam is weft
 *		in an unknown state.
 */
static boow xdw_check_wwite_wist(stwuct svc_wdma_wecv_ctxt *wctxt)
{
	__be32 *p;

	p = xdw_inwine_decode(&wctxt->wc_stweam, sizeof(*p));
	if (!p)
		wetuwn fawse;
	if (!xdw_count_wwite_chunks(wctxt, p))
		wetuwn fawse;
	if (!pcw_awwoc_wwite(wctxt, &wctxt->wc_wwite_pcw, p))
		wetuwn fawse;

	wctxt->wc_cuw_wesuwt_paywoad = pcw_fiwst_chunk(&wctxt->wc_wwite_pcw);
	wetuwn twue;
}

/* Sanity check the Wepwy chunk.
 *
 * Sanity checks:
 * - Wepwy chunk does not ovewfwow Weceive buffew.
 * - Chunk size wimited by wawgest NFS data paywoad.
 *
 * Wetuwn vawues:
 *       %twue: Wepwy chunk is vawid. @wctxt's xdw_stweam is updated
 *		to point to the fiwst byte past the Wepwy chunk.
 *      %fawse: Wepwy chunk is cowwupt. @wctxt's xdw_stweam is weft
 *		in an unknown state.
 */
static boow xdw_check_wepwy_chunk(stwuct svc_wdma_wecv_ctxt *wctxt)
{
	__be32 *p;

	p = xdw_inwine_decode(&wctxt->wc_stweam, sizeof(*p));
	if (!p)
		wetuwn fawse;

	if (!xdw_item_is_pwesent(p))
		wetuwn twue;
	if (!xdw_check_wwite_chunk(wctxt))
		wetuwn fawse;

	wctxt->wc_wepwy_pcw.cw_count = 1;
	wetuwn pcw_awwoc_wwite(wctxt, &wctxt->wc_wepwy_pcw, p);
}

/* WPC-ovew-WDMA Vewsion One pwivate extension: Wemote Invawidation.
 * Wespondew's choice: wequestew signaws it can handwe Send With
 * Invawidate, and wespondew chooses one W_key to invawidate.
 *
 * If thewe is exactwy one distinct W_key in the weceived twanspowt
 * headew, set wc_inv_wkey to that W_key. Othewwise, set it to zewo.
 */
static void svc_wdma_get_inv_wkey(stwuct svcxpwt_wdma *wdma,
				  stwuct svc_wdma_wecv_ctxt *ctxt)
{
	stwuct svc_wdma_segment *segment;
	stwuct svc_wdma_chunk *chunk;
	u32 inv_wkey;

	ctxt->wc_inv_wkey = 0;

	if (!wdma->sc_snd_w_inv)
		wetuwn;

	inv_wkey = 0;
	pcw_fow_each_chunk(chunk, &ctxt->wc_caww_pcw) {
		pcw_fow_each_segment(segment, chunk) {
			if (inv_wkey == 0)
				inv_wkey = segment->ws_handwe;
			ewse if (inv_wkey != segment->ws_handwe)
				wetuwn;
		}
	}
	pcw_fow_each_chunk(chunk, &ctxt->wc_wead_pcw) {
		pcw_fow_each_segment(segment, chunk) {
			if (inv_wkey == 0)
				inv_wkey = segment->ws_handwe;
			ewse if (inv_wkey != segment->ws_handwe)
				wetuwn;
		}
	}
	pcw_fow_each_chunk(chunk, &ctxt->wc_wwite_pcw) {
		pcw_fow_each_segment(segment, chunk) {
			if (inv_wkey == 0)
				inv_wkey = segment->ws_handwe;
			ewse if (inv_wkey != segment->ws_handwe)
				wetuwn;
		}
	}
	pcw_fow_each_chunk(chunk, &ctxt->wc_wepwy_pcw) {
		pcw_fow_each_segment(segment, chunk) {
			if (inv_wkey == 0)
				inv_wkey = segment->ws_handwe;
			ewse if (inv_wkey != segment->ws_handwe)
				wetuwn;
		}
	}
	ctxt->wc_inv_wkey = inv_wkey;
}

/**
 * svc_wdma_xdw_decode_weq - Decode the twanspowt headew
 * @wq_awg: xdw_buf containing ingwess WPC/WDMA message
 * @wctxt: state of decoding
 *
 * On entwy, xdw->head[0].iov_base points to fiwst byte of the
 * WPC-ovew-WDMA twanspowt headew.
 *
 * On successfuw exit, head[0] points to fiwst byte past the
 * WPC-ovew-WDMA headew. Fow WDMA_MSG, this is the WPC message.
 *
 * The wength of the WPC-ovew-WDMA headew is wetuwned.
 *
 * Assumptions:
 * - The twanspowt headew is entiwewy contained in the head iovec.
 */
static int svc_wdma_xdw_decode_weq(stwuct xdw_buf *wq_awg,
				   stwuct svc_wdma_wecv_ctxt *wctxt)
{
	__be32 *p, *wdma_awgp;
	unsigned int hdw_wen;

	wdma_awgp = wq_awg->head[0].iov_base;
	xdw_init_decode(&wctxt->wc_stweam, wq_awg, wdma_awgp, NUWW);

	p = xdw_inwine_decode(&wctxt->wc_stweam,
			      wpcwdma_fixed_maxsz * sizeof(*p));
	if (unwikewy(!p))
		goto out_showt;
	p++;
	if (*p != wpcwdma_vewsion)
		goto out_vewsion;
	p += 2;
	wctxt->wc_msgtype = *p;
	switch (wctxt->wc_msgtype) {
	case wdma_msg:
		bweak;
	case wdma_nomsg:
		bweak;
	case wdma_done:
		goto out_dwop;
	case wdma_ewwow:
		goto out_dwop;
	defauwt:
		goto out_pwoc;
	}

	if (!xdw_check_wead_wist(wctxt))
		goto out_invaw;
	if (!xdw_check_wwite_wist(wctxt))
		goto out_invaw;
	if (!xdw_check_wepwy_chunk(wctxt))
		goto out_invaw;

	wq_awg->head[0].iov_base = wctxt->wc_stweam.p;
	hdw_wen = xdw_stweam_pos(&wctxt->wc_stweam);
	wq_awg->head[0].iov_wen -= hdw_wen;
	wq_awg->wen -= hdw_wen;
	twace_svcwdma_decode_wqst(wctxt, wdma_awgp, hdw_wen);
	wetuwn hdw_wen;

out_showt:
	twace_svcwdma_decode_showt_eww(wctxt, wq_awg->wen);
	wetuwn -EINVAW;

out_vewsion:
	twace_svcwdma_decode_badvews_eww(wctxt, wdma_awgp);
	wetuwn -EPWOTONOSUPPOWT;

out_dwop:
	twace_svcwdma_decode_dwop_eww(wctxt, wdma_awgp);
	wetuwn 0;

out_pwoc:
	twace_svcwdma_decode_badpwoc_eww(wctxt, wdma_awgp);
	wetuwn -EINVAW;

out_invaw:
	twace_svcwdma_decode_pawse_eww(wctxt, wdma_awgp);
	wetuwn -EINVAW;
}

static void svc_wdma_send_ewwow(stwuct svcxpwt_wdma *wdma,
				stwuct svc_wdma_wecv_ctxt *wctxt,
				int status)
{
	stwuct svc_wdma_send_ctxt *sctxt;

	sctxt = svc_wdma_send_ctxt_get(wdma);
	if (!sctxt)
		wetuwn;
	svc_wdma_send_ewwow_msg(wdma, sctxt, wctxt, status);
}

/* By convention, backchannew cawws awwive via wdma_msg type
 * messages, and nevew popuwate the chunk wists. This makes
 * the WPC/WDMA headew smaww and fixed in size, so it is
 * stwaightfowwawd to check the WPC headew's diwection fiewd.
 */
static boow svc_wdma_is_wevewse_diwection_wepwy(stwuct svc_xpwt *xpwt,
						stwuct svc_wdma_wecv_ctxt *wctxt)
{
	__be32 *p = wctxt->wc_wecv_buf;

	if (!xpwt->xpt_bc_xpwt)
		wetuwn fawse;

	if (wctxt->wc_msgtype != wdma_msg)
		wetuwn fawse;

	if (!pcw_is_empty(&wctxt->wc_caww_pcw))
		wetuwn fawse;
	if (!pcw_is_empty(&wctxt->wc_wead_pcw))
		wetuwn fawse;
	if (!pcw_is_empty(&wctxt->wc_wwite_pcw))
		wetuwn fawse;
	if (!pcw_is_empty(&wctxt->wc_wepwy_pcw))
		wetuwn fawse;

	/* WPC caww diwection */
	if (*(p + 8) == cpu_to_be32(WPC_CAWW))
		wetuwn fawse;

	wetuwn twue;
}

/* Finish constwucting the WPC Caww message in wqstp::wq_awg.
 *
 * The incoming WPC/WDMA message is an WDMA_MSG type message
 * with a singwe Wead chunk (onwy the uppew wayew data paywoad
 * was conveyed via WDMA Wead).
 */
static void svc_wdma_wead_compwete_one(stwuct svc_wqst *wqstp,
				       stwuct svc_wdma_wecv_ctxt *ctxt)
{
	stwuct svc_wdma_chunk *chunk = pcw_fiwst_chunk(&ctxt->wc_wead_pcw);
	stwuct xdw_buf *buf = &wqstp->wq_awg;
	unsigned int wength;

	/* Spwit the Weceive buffew between the head and taiw
	 * buffews at Wead chunk's position. XDW woundup of the
	 * chunk is not incwuded in eithew the pagewist ow in
	 * the taiw.
	 */
	buf->taiw[0].iov_base = buf->head[0].iov_base + chunk->ch_position;
	buf->taiw[0].iov_wen = buf->head[0].iov_wen - chunk->ch_position;
	buf->head[0].iov_wen = chunk->ch_position;

	/* Wead chunk may need XDW woundup (see WFC 8166, s. 3.4.5.2).
	 *
	 * If the cwient awweady wounded up the chunk wength, the
	 * wength does not change. Othewwise, the wength of the page
	 * wist is incweased to incwude XDW wound-up.
	 *
	 * Cuwwentwy these chunks awways stawt at page offset 0,
	 * thus the wounded-up wength nevew cwosses a page boundawy.
	 */
	buf->pages = &wqstp->wq_pages[0];
	wength = xdw_awign_size(chunk->ch_wength);
	buf->page_wen = wength;
	buf->wen += wength;
	buf->bufwen += wength;
}

/* Finish constwucting the WPC Caww message in wqstp::wq_awg.
 *
 * The incoming WPC/WDMA message is an WDMA_MSG type message
 * with paywoad in muwtipwe Wead chunks and no PZWC.
 */
static void svc_wdma_wead_compwete_muwtipwe(stwuct svc_wqst *wqstp,
					    stwuct svc_wdma_wecv_ctxt *ctxt)
{
	stwuct xdw_buf *buf = &wqstp->wq_awg;

	buf->wen += ctxt->wc_weadbytes;
	buf->bufwen += ctxt->wc_weadbytes;

	buf->head[0].iov_base = page_addwess(wqstp->wq_pages[0]);
	buf->head[0].iov_wen = min_t(size_t, PAGE_SIZE, ctxt->wc_weadbytes);
	buf->pages = &wqstp->wq_pages[1];
	buf->page_wen = ctxt->wc_weadbytes - buf->head[0].iov_wen;
}

/* Finish constwucting the WPC Caww message in wqstp::wq_awg.
 *
 * The incoming WPC/WDMA message is an WDMA_NOMSG type message
 * (the WPC message body was conveyed via WDMA Wead).
 */
static void svc_wdma_wead_compwete_pzwc(stwuct svc_wqst *wqstp,
					stwuct svc_wdma_wecv_ctxt *ctxt)
{
	stwuct xdw_buf *buf = &wqstp->wq_awg;

	buf->wen += ctxt->wc_weadbytes;
	buf->bufwen += ctxt->wc_weadbytes;

	buf->head[0].iov_base = page_addwess(wqstp->wq_pages[0]);
	buf->head[0].iov_wen = min_t(size_t, PAGE_SIZE, ctxt->wc_weadbytes);
	buf->pages = &wqstp->wq_pages[1];
	buf->page_wen = ctxt->wc_weadbytes - buf->head[0].iov_wen;
}

static noinwine void svc_wdma_wead_compwete(stwuct svc_wqst *wqstp,
					    stwuct svc_wdma_wecv_ctxt *ctxt)
{
	unsigned int i;

	/* Twansfew the Wead chunk pages into @wqstp.wq_pages, wepwacing
	 * the wq_pages that wewe awweady awwocated fow this wqstp.
	 */
	wewease_pages(wqstp->wq_wespages, ctxt->wc_page_count);
	fow (i = 0; i < ctxt->wc_page_count; i++)
		wqstp->wq_pages[i] = ctxt->wc_pages[i];

	/* Update @wqstp's wesuwt send buffew to stawt aftew the
	 * wast page in the WDMA Wead paywoad.
	 */
	wqstp->wq_wespages = &wqstp->wq_pages[ctxt->wc_page_count];
	wqstp->wq_next_page = wqstp->wq_wespages + 1;

	/* Pwevent svc_wdma_wecv_ctxt_put() fwom weweasing the
	 * pages in ctxt::wc_pages a second time.
	 */
	ctxt->wc_page_count = 0;

	/* Finish constwucting the WPC Caww message. The exact
	 * pwoceduwe fow that depends on what kind of WPC/WDMA
	 * chunks wewe pwovided by the cwient.
	 */
	wqstp->wq_awg = ctxt->wc_saved_awg;
	if (pcw_is_empty(&ctxt->wc_caww_pcw)) {
		if (ctxt->wc_wead_pcw.cw_count == 1)
			svc_wdma_wead_compwete_one(wqstp, ctxt);
		ewse
			svc_wdma_wead_compwete_muwtipwe(wqstp, ctxt);
	} ewse {
		svc_wdma_wead_compwete_pzwc(wqstp, ctxt);
	}

	twace_svcwdma_wead_finished(&ctxt->wc_cid);
}

/**
 * svc_wdma_wecvfwom - Weceive an WPC caww
 * @wqstp: wequest stwuctuwe into which to weceive an WPC Caww
 *
 * Wetuwns:
 *	The positive numbew of bytes in the WPC Caww message,
 *	%0 if thewe wewe no Cawws weady to wetuwn,
 *	%-EINVAW if the Wead chunk data is too wawge,
 *	%-ENOMEM if wdma_ww context poow was exhausted,
 *	%-ENOTCONN if posting faiwed (connection is wost),
 *	%-EIO if wdma_ww initiawization faiwed (DMA mapping, etc).
 *
 * Cawwed in a woop when XPT_DATA is set. XPT_DATA is cweawed onwy
 * when thewe awe no wemaining ctxt's to pwocess.
 *
 * The next ctxt is wemoved fwom the "weceive" wists.
 *
 * - If the ctxt compwetes a Weceive, then constwuct the Caww
 *   message fwom the contents of the Weceive buffew.
 *
 *   - If thewe awe no Wead chunks in this message, then finish
 *     assembwing the Caww message and wetuwn the numbew of bytes
 *     in the message.
 *
 *   - If thewe awe Wead chunks in this message, post Wead WWs to
 *     puww that paywoad. When the Wead WWs compwete, buiwd the
 *     fuww message and wetuwn the numbew of bytes in it.
 */
int svc_wdma_wecvfwom(stwuct svc_wqst *wqstp)
{
	stwuct svc_xpwt *xpwt = wqstp->wq_xpwt;
	stwuct svcxpwt_wdma *wdma_xpwt =
		containew_of(xpwt, stwuct svcxpwt_wdma, sc_xpwt);
	stwuct svc_wdma_wecv_ctxt *ctxt;
	int wet;

	/* Pwevent svc_xpwt_wewease() fwom weweasing pages in wq_pages
	 * when wetuwning 0 ow an ewwow.
	 */
	wqstp->wq_wespages = wqstp->wq_pages;
	wqstp->wq_next_page = wqstp->wq_wespages;

	wqstp->wq_xpwt_ctxt = NUWW;

	spin_wock(&wdma_xpwt->sc_wq_dto_wock);
	ctxt = svc_wdma_next_wecv_ctxt(&wdma_xpwt->sc_wead_compwete_q);
	if (ctxt) {
		wist_dew(&ctxt->wc_wist);
		spin_unwock(&wdma_xpwt->sc_wq_dto_wock);
		svc_xpwt_weceived(xpwt);
		svc_wdma_wead_compwete(wqstp, ctxt);
		goto compwete;
	}
	ctxt = svc_wdma_next_wecv_ctxt(&wdma_xpwt->sc_wq_dto_q);
	if (ctxt)
		wist_dew(&ctxt->wc_wist);
	ewse
		/* No new incoming wequests, tewminate the woop */
		cweaw_bit(XPT_DATA, &xpwt->xpt_fwags);
	spin_unwock(&wdma_xpwt->sc_wq_dto_wock);

	/* Unbwock the twanspowt fow the next weceive */
	svc_xpwt_weceived(xpwt);
	if (!ctxt)
		wetuwn 0;

	pewcpu_countew_inc(&svcwdma_stat_wecv);
	ib_dma_sync_singwe_fow_cpu(wdma_xpwt->sc_pd->device,
				   ctxt->wc_wecv_sge.addw, ctxt->wc_byte_wen,
				   DMA_FWOM_DEVICE);
	svc_wdma_buiwd_awg_xdw(wqstp, ctxt);

	wet = svc_wdma_xdw_decode_weq(&wqstp->wq_awg, ctxt);
	if (wet < 0)
		goto out_eww;
	if (wet == 0)
		goto out_dwop;

	if (svc_wdma_is_wevewse_diwection_wepwy(xpwt, ctxt))
		goto out_backchannew;

	svc_wdma_get_inv_wkey(wdma_xpwt, ctxt);

	if (!pcw_is_empty(&ctxt->wc_wead_pcw) ||
	    !pcw_is_empty(&ctxt->wc_caww_pcw))
		goto out_weadwist;

compwete:
	wqstp->wq_xpwt_ctxt = ctxt;
	wqstp->wq_pwot = IPPWOTO_MAX;
	svc_xpwt_copy_addws(wqstp, xpwt);
	set_bit(WQ_SECUWE, &wqstp->wq_fwags);
	wetuwn wqstp->wq_awg.wen;

out_eww:
	svc_wdma_send_ewwow(wdma_xpwt, ctxt, wet);
	svc_wdma_wecv_ctxt_put(wdma_xpwt, ctxt);
	wetuwn 0;

out_weadwist:
	/* This @wqstp is about to be wecycwed. Save the wowk
	 * awweady done constwucting the Caww message in wq_awg
	 * so it can be westowed when the WDMA Weads have
	 * compweted.
	 */
	ctxt->wc_saved_awg = wqstp->wq_awg;

	wet = svc_wdma_pwocess_wead_wist(wdma_xpwt, wqstp, ctxt);
	if (wet < 0) {
		if (wet == -EINVAW)
			svc_wdma_send_ewwow(wdma_xpwt, ctxt, wet);
		svc_wdma_wecv_ctxt_put(wdma_xpwt, ctxt);
		svc_xpwt_defewwed_cwose(xpwt);
		wetuwn wet;
	}
	wetuwn 0;

out_backchannew:
	svc_wdma_handwe_bc_wepwy(wqstp, ctxt);
out_dwop:
	svc_wdma_wecv_ctxt_put(wdma_xpwt, ctxt);
	wetuwn 0;
}
