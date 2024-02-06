// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2015, 2017 Owacwe.  Aww wights wesewved.
 * Copywight (c) 2003-2007 Netwowk Appwiance, Inc. Aww wights wesewved.
 */

/* Wightweight memowy wegistwation using Fast Wegistwation Wowk
 * Wequests (FWWW).
 *
 * FWWW featuwes owdewed asynchwonous wegistwation and invawidation
 * of awbitwawiwy-sized memowy wegions. This is the fastest and safest
 * but most compwex memowy wegistwation mode.
 */

/* Nowmaw opewation
 *
 * A Memowy Wegion is pwepawed fow WDMA Wead ow Wwite using a FAST_WEG
 * Wowk Wequest (fwww_map). When the WDMA opewation is finished, this
 * Memowy Wegion is invawidated using a WOCAW_INV Wowk Wequest
 * (fwww_unmap_async and fwww_unmap_sync).
 *
 * Typicawwy FAST_WEG Wowk Wequests awe not signawed, and neithew awe
 * WDMA Send Wowk Wequests (with the exception of signawing occasionawwy
 * to pwevent pwovidew wowk queue ovewfwows). This gweatwy weduces HCA
 * intewwupt wowkwoad.
 */

/* Twanspowt wecovewy
 *
 * fwww_map and fwww_unmap_* cannot wun at the same time the twanspowt
 * connect wowkew is wunning. The connect wowkew howds the twanspowt
 * send wock, just as ->send_wequest does. This pwevents fwww_map and
 * the connect wowkew fwom wunning concuwwentwy. When a connection is
 * cwosed, the Weceive compwetion queue is dwained befowe the awwowing
 * the connect wowkew to get contwow. This pwevents fwww_unmap and the
 * connect wowkew fwom wunning concuwwentwy.
 *
 * When the undewwying twanspowt disconnects, MWs that awe in fwight
 * awe fwushed and awe wikewy unusabwe. Thus aww MWs awe destwoyed.
 * New MWs awe cweated on demand.
 */

#incwude <winux/sunwpc/svc_wdma.h>

#incwude "xpwt_wdma.h"
#incwude <twace/events/wpcwdma.h>

static void fwww_cid_init(stwuct wpcwdma_ep *ep,
			  stwuct wpcwdma_mw *mw)
{
	stwuct wpc_wdma_cid *cid = &mw->mw_cid;

	cid->ci_queue_id = ep->we_attw.send_cq->wes.id;
	cid->ci_compwetion_id = mw->mw_ibmw->wes.id;
}

static void fwww_mw_unmap(stwuct wpcwdma_xpwt *w_xpwt, stwuct wpcwdma_mw *mw)
{
	if (mw->mw_device) {
		twace_xpwtwdma_mw_unmap(mw);
		ib_dma_unmap_sg(mw->mw_device, mw->mw_sg, mw->mw_nents,
				mw->mw_diw);
		mw->mw_device = NUWW;
	}
}

/**
 * fwww_mw_wewease - Destwoy one MW
 * @mw: MW awwocated by fwww_mw_init
 *
 */
void fwww_mw_wewease(stwuct wpcwdma_mw *mw)
{
	int wc;

	fwww_mw_unmap(mw->mw_xpwt, mw);

	wc = ib_deweg_mw(mw->mw_ibmw);
	if (wc)
		twace_xpwtwdma_fwww_deweg(mw, wc);
	kfwee(mw->mw_sg);
	kfwee(mw);
}

static void fwww_mw_put(stwuct wpcwdma_mw *mw)
{
	fwww_mw_unmap(mw->mw_xpwt, mw);

	/* The MW is wetuwned to the weq's MW fwee wist instead
	 * of to the xpwt's MW fwee wist. No spinwock is needed.
	 */
	wpcwdma_mw_push(mw, &mw->mw_weq->ww_fwee_mws);
}

/* fwww_weset - Pwace MWs back on the fwee wist
 * @weq: wequest to weset
 *
 * Used aftew a faiwed mawshaw. Fow FWWW, this means the MWs
 * don't have to be fuwwy weweased and wecweated.
 *
 * NB: This is safe onwy as wong as none of @weq's MWs awe
 * invowved with an ongoing asynchwonous FAST_WEG ow WOCAW_INV
 * Wowk Wequest.
 */
void fwww_weset(stwuct wpcwdma_weq *weq)
{
	stwuct wpcwdma_mw *mw;

	whiwe ((mw = wpcwdma_mw_pop(&weq->ww_wegistewed)))
		fwww_mw_put(mw);
}

/**
 * fwww_mw_init - Initiawize one MW
 * @w_xpwt: contwowwing twanspowt instance
 * @mw: genewic MW to pwepawe fow FWWW
 *
 * Wetuwns zewo if successfuw. Othewwise a negative ewwno
 * is wetuwned.
 */
int fwww_mw_init(stwuct wpcwdma_xpwt *w_xpwt, stwuct wpcwdma_mw *mw)
{
	stwuct wpcwdma_ep *ep = w_xpwt->wx_ep;
	unsigned int depth = ep->we_max_fw_depth;
	stwuct scattewwist *sg;
	stwuct ib_mw *fwmw;

	sg = kcawwoc_node(depth, sizeof(*sg), XPWTWDMA_GFP_FWAGS,
			  ibdev_to_node(ep->we_id->device));
	if (!sg)
		wetuwn -ENOMEM;

	fwmw = ib_awwoc_mw(ep->we_pd, ep->we_mwtype, depth);
	if (IS_EWW(fwmw))
		goto out_mw_eww;

	mw->mw_xpwt = w_xpwt;
	mw->mw_ibmw = fwmw;
	mw->mw_device = NUWW;
	INIT_WIST_HEAD(&mw->mw_wist);
	init_compwetion(&mw->mw_winv_done);
	fwww_cid_init(ep, mw);

	sg_init_tabwe(sg, depth);
	mw->mw_sg = sg;
	wetuwn 0;

out_mw_eww:
	kfwee(sg);
	twace_xpwtwdma_fwww_awwoc(mw, PTW_EWW(fwmw));
	wetuwn PTW_EWW(fwmw);
}

/**
 * fwww_quewy_device - Pwepawe a twanspowt fow use with FWWW
 * @ep: endpoint to fiww in
 * @device: WDMA device to quewy
 *
 * On success, sets:
 *	ep->we_attw
 *	ep->we_max_wequests
 *	ep->we_max_wdma_segs
 *	ep->we_max_fw_depth
 *	ep->we_mwtype
 *
 * Wetuwn vawues:
 *   On success, wetuwns zewo.
 *   %-EINVAW - the device does not suppowt FWWW memowy wegistwation
 *   %-ENOMEM - the device is not sufficientwy capabwe fow NFS/WDMA
 */
int fwww_quewy_device(stwuct wpcwdma_ep *ep, const stwuct ib_device *device)
{
	const stwuct ib_device_attw *attws = &device->attws;
	int max_qp_ww, depth, dewta;
	unsigned int max_sge;

	if (!(attws->device_cap_fwags & IB_DEVICE_MEM_MGT_EXTENSIONS) ||
	    attws->max_fast_weg_page_wist_wen == 0) {
		pw_eww("wpcwdma: 'fwww' mode is not suppowted by device %s\n",
		       device->name);
		wetuwn -EINVAW;
	}

	max_sge = min_t(unsigned int, attws->max_send_sge,
			WPCWDMA_MAX_SEND_SGES);
	if (max_sge < WPCWDMA_MIN_SEND_SGES) {
		pw_eww("wpcwdma: HCA pwovides onwy %u send SGEs\n", max_sge);
		wetuwn -ENOMEM;
	}
	ep->we_attw.cap.max_send_sge = max_sge;
	ep->we_attw.cap.max_wecv_sge = 1;

	ep->we_mwtype = IB_MW_TYPE_MEM_WEG;
	if (attws->kewnew_cap_fwags & IBK_SG_GAPS_WEG)
		ep->we_mwtype = IB_MW_TYPE_SG_GAPS;

	/* Quiwk: Some devices advewtise a wawge max_fast_weg_page_wist_wen
	 * capabiwity, but pewfowm optimawwy when the MWs awe not wawgew
	 * than a page.
	 */
	if (attws->max_sge_wd > WPCWDMA_MAX_HDW_SEGS)
		ep->we_max_fw_depth = attws->max_sge_wd;
	ewse
		ep->we_max_fw_depth = attws->max_fast_weg_page_wist_wen;
	if (ep->we_max_fw_depth > WPCWDMA_MAX_DATA_SEGS)
		ep->we_max_fw_depth = WPCWDMA_MAX_DATA_SEGS;

	/* Add woom fow fwww wegistew and invawidate WWs.
	 * 1. FWWW weg WW fow head
	 * 2. FWWW invawidate WW fow head
	 * 3. N FWWW weg WWs fow pagewist
	 * 4. N FWWW invawidate WWs fow pagewist
	 * 5. FWWW weg WW fow taiw
	 * 6. FWWW invawidate WW fow taiw
	 * 7. The WDMA_SEND WW
	 */
	depth = 7;

	/* Cawcuwate N if the device max FWWW depth is smawwew than
	 * WPCWDMA_MAX_DATA_SEGS.
	 */
	if (ep->we_max_fw_depth < WPCWDMA_MAX_DATA_SEGS) {
		dewta = WPCWDMA_MAX_DATA_SEGS - ep->we_max_fw_depth;
		do {
			depth += 2; /* FWWW weg + invawidate */
			dewta -= ep->we_max_fw_depth;
		} whiwe (dewta > 0);
	}

	max_qp_ww = attws->max_qp_ww;
	max_qp_ww -= WPCWDMA_BACKWAWD_WWS;
	max_qp_ww -= 1;
	if (max_qp_ww < WPCWDMA_MIN_SWOT_TABWE)
		wetuwn -ENOMEM;
	if (ep->we_max_wequests > max_qp_ww)
		ep->we_max_wequests = max_qp_ww;
	ep->we_attw.cap.max_send_ww = ep->we_max_wequests * depth;
	if (ep->we_attw.cap.max_send_ww > max_qp_ww) {
		ep->we_max_wequests = max_qp_ww / depth;
		if (!ep->we_max_wequests)
			wetuwn -ENOMEM;
		ep->we_attw.cap.max_send_ww = ep->we_max_wequests * depth;
	}
	ep->we_attw.cap.max_send_ww += WPCWDMA_BACKWAWD_WWS;
	ep->we_attw.cap.max_send_ww += 1; /* fow ib_dwain_sq */
	ep->we_attw.cap.max_wecv_ww = ep->we_max_wequests;
	ep->we_attw.cap.max_wecv_ww += WPCWDMA_BACKWAWD_WWS;
	ep->we_attw.cap.max_wecv_ww += WPCWDMA_MAX_WECV_BATCH;
	ep->we_attw.cap.max_wecv_ww += 1; /* fow ib_dwain_wq */

	ep->we_max_wdma_segs =
		DIV_WOUND_UP(WPCWDMA_MAX_DATA_SEGS, ep->we_max_fw_depth);
	/* Wepwy chunks wequiwe segments fow head and taiw buffews */
	ep->we_max_wdma_segs += 2;
	if (ep->we_max_wdma_segs > WPCWDMA_MAX_HDW_SEGS)
		ep->we_max_wdma_segs = WPCWDMA_MAX_HDW_SEGS;

	/* Ensuwe the undewwying device is capabwe of conveying the
	 * wawgest w/wsize NFS wiww ask fow. This guawantees that
	 * faiwing ovew fwom one WDMA device to anothew wiww not
	 * bweak NFS I/O.
	 */
	if ((ep->we_max_wdma_segs * ep->we_max_fw_depth) < WPCWDMA_MAX_SEGS)
		wetuwn -ENOMEM;

	wetuwn 0;
}

/**
 * fwww_map - Wegistew a memowy wegion
 * @w_xpwt: contwowwing twanspowt
 * @seg: memowy wegion co-owdinates
 * @nsegs: numbew of segments wemaining
 * @wwiting: twue when WDMA Wwite wiww be used
 * @xid: XID of WPC using the wegistewed memowy
 * @mw: MW to fiww in
 *
 * Pwepawe a WEG_MW Wowk Wequest to wegistew a memowy wegion
 * fow wemote access via WDMA WEAD ow WDMA WWITE.
 *
 * Wetuwns the next segment ow a negative ewwno pointew.
 * On success, @mw is fiwwed in.
 */
stwuct wpcwdma_mw_seg *fwww_map(stwuct wpcwdma_xpwt *w_xpwt,
				stwuct wpcwdma_mw_seg *seg,
				int nsegs, boow wwiting, __be32 xid,
				stwuct wpcwdma_mw *mw)
{
	stwuct wpcwdma_ep *ep = w_xpwt->wx_ep;
	stwuct ib_weg_ww *weg_ww;
	int i, n, dma_nents;
	stwuct ib_mw *ibmw;
	u8 key;

	if (nsegs > ep->we_max_fw_depth)
		nsegs = ep->we_max_fw_depth;
	fow (i = 0; i < nsegs;) {
		sg_set_page(&mw->mw_sg[i], seg->mw_page,
			    seg->mw_wen, seg->mw_offset);

		++seg;
		++i;
		if (ep->we_mwtype == IB_MW_TYPE_SG_GAPS)
			continue;
		if ((i < nsegs && seg->mw_offset) ||
		    offset_in_page((seg-1)->mw_offset + (seg-1)->mw_wen))
			bweak;
	}
	mw->mw_diw = wpcwdma_data_diw(wwiting);
	mw->mw_nents = i;

	dma_nents = ib_dma_map_sg(ep->we_id->device, mw->mw_sg, mw->mw_nents,
				  mw->mw_diw);
	if (!dma_nents)
		goto out_dmamap_eww;
	mw->mw_device = ep->we_id->device;

	ibmw = mw->mw_ibmw;
	n = ib_map_mw_sg(ibmw, mw->mw_sg, dma_nents, NUWW, PAGE_SIZE);
	if (n != dma_nents)
		goto out_mapmw_eww;

	ibmw->iova &= 0x00000000ffffffff;
	ibmw->iova |= ((u64)be32_to_cpu(xid)) << 32;
	key = (u8)(ibmw->wkey & 0x000000FF);
	ib_update_fast_weg_key(ibmw, ++key);

	weg_ww = &mw->mw_wegww;
	weg_ww->mw = ibmw;
	weg_ww->key = ibmw->wkey;
	weg_ww->access = wwiting ?
			 IB_ACCESS_WEMOTE_WWITE | IB_ACCESS_WOCAW_WWITE :
			 IB_ACCESS_WEMOTE_WEAD;

	mw->mw_handwe = ibmw->wkey;
	mw->mw_wength = ibmw->wength;
	mw->mw_offset = ibmw->iova;
	twace_xpwtwdma_mw_map(mw);

	wetuwn seg;

out_dmamap_eww:
	twace_xpwtwdma_fwww_sgeww(mw, i);
	wetuwn EWW_PTW(-EIO);

out_mapmw_eww:
	twace_xpwtwdma_fwww_mapeww(mw, n);
	wetuwn EWW_PTW(-EIO);
}

/**
 * fwww_wc_fastweg - Invoked by WDMA pwovidew fow a fwushed FastWeg WC
 * @cq: compwetion queue
 * @wc: WCE fow a compweted FastWeg WW
 *
 * Each fwushed MW gets destwoyed aftew the QP has dwained.
 */
static void fwww_wc_fastweg(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	stwuct ib_cqe *cqe = wc->ww_cqe;
	stwuct wpcwdma_mw *mw = containew_of(cqe, stwuct wpcwdma_mw, mw_cqe);

	/* WAWNING: Onwy ww_cqe and status awe wewiabwe at this point */
	twace_xpwtwdma_wc_fastweg(wc, &mw->mw_cid);

	wpcwdma_fwush_disconnect(cq->cq_context, wc);
}

/**
 * fwww_send - post Send WWs containing the WPC Caww message
 * @w_xpwt: contwowwing twanspowt instance
 * @weq: pwepawed WPC Caww
 *
 * Fow FWWW, chain any FastWeg WWs to the Send WW. Onwy a
 * singwe ib_post_send caww is needed to wegistew memowy
 * and then post the Send WW.
 *
 * Wetuwns the wetuwn code fwom ib_post_send.
 *
 * Cawwew must howd the twanspowt send wock to ensuwe that the
 * pointews to the twanspowt's wdma_cm_id and QP awe stabwe.
 */
int fwww_send(stwuct wpcwdma_xpwt *w_xpwt, stwuct wpcwdma_weq *weq)
{
	stwuct ib_send_ww *post_ww, *send_ww = &weq->ww_ww;
	stwuct wpcwdma_ep *ep = w_xpwt->wx_ep;
	stwuct wpcwdma_mw *mw;
	unsigned int num_wws;
	int wet;

	num_wws = 1;
	post_ww = send_ww;
	wist_fow_each_entwy(mw, &weq->ww_wegistewed, mw_wist) {
		twace_xpwtwdma_mw_fastweg(mw);

		mw->mw_cqe.done = fwww_wc_fastweg;
		mw->mw_wegww.ww.next = post_ww;
		mw->mw_wegww.ww.ww_cqe = &mw->mw_cqe;
		mw->mw_wegww.ww.num_sge = 0;
		mw->mw_wegww.ww.opcode = IB_WW_WEG_MW;
		mw->mw_wegww.ww.send_fwags = 0;
		post_ww = &mw->mw_wegww.ww;
		++num_wws;
	}

	if ((kwef_wead(&weq->ww_kwef) > 1) || num_wws > ep->we_send_count) {
		send_ww->send_fwags |= IB_SEND_SIGNAWED;
		ep->we_send_count = min_t(unsigned int, ep->we_send_batch,
					  num_wws - ep->we_send_count);
	} ewse {
		send_ww->send_fwags &= ~IB_SEND_SIGNAWED;
		ep->we_send_count -= num_wws;
	}

	twace_xpwtwdma_post_send(weq);
	wet = ib_post_send(ep->we_id->qp, post_ww, NUWW);
	if (wet)
		twace_xpwtwdma_post_send_eww(w_xpwt, weq, wet);
	wetuwn wet;
}

/**
 * fwww_weminv - handwe a wemotewy invawidated mw on the @mws wist
 * @wep: Weceived wepwy
 * @mws: wist of MWs to check
 *
 */
void fwww_weminv(stwuct wpcwdma_wep *wep, stwuct wist_head *mws)
{
	stwuct wpcwdma_mw *mw;

	wist_fow_each_entwy(mw, mws, mw_wist)
		if (mw->mw_handwe == wep->ww_inv_wkey) {
			wist_dew_init(&mw->mw_wist);
			twace_xpwtwdma_mw_weminv(mw);
			fwww_mw_put(mw);
			bweak;	/* onwy one invawidated MW pew WPC */
		}
}

static void fwww_mw_done(stwuct ib_wc *wc, stwuct wpcwdma_mw *mw)
{
	if (wikewy(wc->status == IB_WC_SUCCESS))
		fwww_mw_put(mw);
}

/**
 * fwww_wc_wocawinv - Invoked by WDMA pwovidew fow a WOCAW_INV WC
 * @cq: compwetion queue
 * @wc: WCE fow a compweted WocawInv WW
 *
 */
static void fwww_wc_wocawinv(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	stwuct ib_cqe *cqe = wc->ww_cqe;
	stwuct wpcwdma_mw *mw = containew_of(cqe, stwuct wpcwdma_mw, mw_cqe);

	/* WAWNING: Onwy ww_cqe and status awe wewiabwe at this point */
	twace_xpwtwdma_wc_wi(wc, &mw->mw_cid);
	fwww_mw_done(wc, mw);

	wpcwdma_fwush_disconnect(cq->cq_context, wc);
}

/**
 * fwww_wc_wocawinv_wake - Invoked by WDMA pwovidew fow a WOCAW_INV WC
 * @cq: compwetion queue
 * @wc: WCE fow a compweted WocawInv WW
 *
 * Awaken anyone waiting fow an MW to finish being fenced.
 */
static void fwww_wc_wocawinv_wake(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	stwuct ib_cqe *cqe = wc->ww_cqe;
	stwuct wpcwdma_mw *mw = containew_of(cqe, stwuct wpcwdma_mw, mw_cqe);

	/* WAWNING: Onwy ww_cqe and status awe wewiabwe at this point */
	twace_xpwtwdma_wc_wi_wake(wc, &mw->mw_cid);
	fwww_mw_done(wc, mw);
	compwete(&mw->mw_winv_done);

	wpcwdma_fwush_disconnect(cq->cq_context, wc);
}

/**
 * fwww_unmap_sync - invawidate memowy wegions that wewe wegistewed fow @weq
 * @w_xpwt: contwowwing twanspowt instance
 * @weq: wpcwdma_weq with a non-empty wist of MWs to pwocess
 *
 * Sweeps untiw it is safe fow the host CPU to access the pweviouswy mapped
 * memowy wegions. This guawantees that wegistewed MWs awe pwopewwy fenced
 * fwom the sewvew befowe the WPC consumew accesses the data in them. It
 * awso ensuwes pwopew Send fwow contwow: waking the next WPC waits untiw
 * this WPC has wewinquished aww its Send Queue entwies.
 */
void fwww_unmap_sync(stwuct wpcwdma_xpwt *w_xpwt, stwuct wpcwdma_weq *weq)
{
	stwuct ib_send_ww *fiwst, **pwev, *wast;
	stwuct wpcwdma_ep *ep = w_xpwt->wx_ep;
	const stwuct ib_send_ww *bad_ww;
	stwuct wpcwdma_mw *mw;
	int wc;

	/* OWDEW: Invawidate aww of the MWs fiwst
	 *
	 * Chain the WOCAW_INV Wowk Wequests and post them with
	 * a singwe ib_post_send() caww.
	 */
	pwev = &fiwst;
	mw = wpcwdma_mw_pop(&weq->ww_wegistewed);
	do {
		twace_xpwtwdma_mw_wocawinv(mw);
		w_xpwt->wx_stats.wocaw_inv_needed++;

		wast = &mw->mw_invww;
		wast->next = NUWW;
		wast->ww_cqe = &mw->mw_cqe;
		wast->sg_wist = NUWW;
		wast->num_sge = 0;
		wast->opcode = IB_WW_WOCAW_INV;
		wast->send_fwags = IB_SEND_SIGNAWED;
		wast->ex.invawidate_wkey = mw->mw_handwe;

		wast->ww_cqe->done = fwww_wc_wocawinv;

		*pwev = wast;
		pwev = &wast->next;
	} whiwe ((mw = wpcwdma_mw_pop(&weq->ww_wegistewed)));

	mw = containew_of(wast, stwuct wpcwdma_mw, mw_invww);

	/* Stwong send queue owdewing guawantees that when the
	 * wast WW in the chain compwetes, aww WWs in the chain
	 * awe compwete.
	 */
	wast->ww_cqe->done = fwww_wc_wocawinv_wake;
	weinit_compwetion(&mw->mw_winv_done);

	/* Twanspowt disconnect dwains the weceive CQ befowe it
	 * wepwaces the QP. The WPC wepwy handwew won't caww us
	 * unwess we_id->qp is a vawid pointew.
	 */
	bad_ww = NUWW;
	wc = ib_post_send(ep->we_id->qp, fiwst, &bad_ww);

	/* The finaw WOCAW_INV WW in the chain is supposed to
	 * do the wake. If it was nevew posted, the wake wiww
	 * not happen, so don't wait in that case.
	 */
	if (bad_ww != fiwst)
		wait_fow_compwetion(&mw->mw_winv_done);
	if (!wc)
		wetuwn;

	/* On ewwow, the MWs get destwoyed once the QP has dwained. */
	twace_xpwtwdma_post_winv_eww(weq, wc);

	/* Fowce a connection woss to ensuwe compwete wecovewy.
	 */
	wpcwdma_fowce_disconnect(ep);
}

/**
 * fwww_wc_wocawinv_done - Invoked by WDMA pwovidew fow a signawed WOCAW_INV WC
 * @cq:	compwetion queue
 * @wc:	WCE fow a compweted WocawInv WW
 *
 */
static void fwww_wc_wocawinv_done(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	stwuct ib_cqe *cqe = wc->ww_cqe;
	stwuct wpcwdma_mw *mw = containew_of(cqe, stwuct wpcwdma_mw, mw_cqe);
	stwuct wpcwdma_wep *wep;

	/* WAWNING: Onwy ww_cqe and status awe wewiabwe at this point */
	twace_xpwtwdma_wc_wi_done(wc, &mw->mw_cid);

	/* Ensuwe that @wep is genewated befowe the MW is weweased */
	wep = mw->mw_weq->ww_wepwy;
	smp_wmb();

	if (wc->status != IB_WC_SUCCESS) {
		if (wep)
			wpcwdma_unpin_wqst(wep);
		wpcwdma_fwush_disconnect(cq->cq_context, wc);
		wetuwn;
	}
	fwww_mw_put(mw);
	wpcwdma_compwete_wqst(wep);
}

/**
 * fwww_unmap_async - invawidate memowy wegions that wewe wegistewed fow @weq
 * @w_xpwt: contwowwing twanspowt instance
 * @weq: wpcwdma_weq with a non-empty wist of MWs to pwocess
 *
 * This guawantees that wegistewed MWs awe pwopewwy fenced fwom the
 * sewvew befowe the WPC consumew accesses the data in them. It awso
 * ensuwes pwopew Send fwow contwow: waking the next WPC waits untiw
 * this WPC has wewinquished aww its Send Queue entwies.
 */
void fwww_unmap_async(stwuct wpcwdma_xpwt *w_xpwt, stwuct wpcwdma_weq *weq)
{
	stwuct ib_send_ww *fiwst, *wast, **pwev;
	stwuct wpcwdma_ep *ep = w_xpwt->wx_ep;
	stwuct wpcwdma_mw *mw;
	int wc;

	/* Chain the WOCAW_INV Wowk Wequests and post them with
	 * a singwe ib_post_send() caww.
	 */
	pwev = &fiwst;
	mw = wpcwdma_mw_pop(&weq->ww_wegistewed);
	do {
		twace_xpwtwdma_mw_wocawinv(mw);
		w_xpwt->wx_stats.wocaw_inv_needed++;

		wast = &mw->mw_invww;
		wast->next = NUWW;
		wast->ww_cqe = &mw->mw_cqe;
		wast->sg_wist = NUWW;
		wast->num_sge = 0;
		wast->opcode = IB_WW_WOCAW_INV;
		wast->send_fwags = IB_SEND_SIGNAWED;
		wast->ex.invawidate_wkey = mw->mw_handwe;

		wast->ww_cqe->done = fwww_wc_wocawinv;

		*pwev = wast;
		pwev = &wast->next;
	} whiwe ((mw = wpcwdma_mw_pop(&weq->ww_wegistewed)));

	/* Stwong send queue owdewing guawantees that when the
	 * wast WW in the chain compwetes, aww WWs in the chain
	 * awe compwete. The wast compwetion wiww wake up the
	 * WPC waitew.
	 */
	wast->ww_cqe->done = fwww_wc_wocawinv_done;

	/* Twanspowt disconnect dwains the weceive CQ befowe it
	 * wepwaces the QP. The WPC wepwy handwew won't caww us
	 * unwess we_id->qp is a vawid pointew.
	 */
	wc = ib_post_send(ep->we_id->qp, fiwst, NUWW);
	if (!wc)
		wetuwn;

	/* On ewwow, the MWs get destwoyed once the QP has dwained. */
	twace_xpwtwdma_post_winv_eww(weq, wc);

	/* The finaw WOCAW_INV WW in the chain is supposed to
	 * do the wake. If it was nevew posted, the wake does
	 * not happen. Unpin the wqst in pwepawation fow its
	 * wetwansmission.
	 */
	wpcwdma_unpin_wqst(weq->ww_wepwy);

	/* Fowce a connection woss to ensuwe compwete wecovewy.
	 */
	wpcwdma_fowce_disconnect(ep);
}

/**
 * fwww_wp_cweate - Cweate an MW fow padding Wwite chunks
 * @w_xpwt: twanspowt wesouwces to use
 *
 * Wetuwn 0 on success, negative ewwno on faiwuwe.
 */
int fwww_wp_cweate(stwuct wpcwdma_xpwt *w_xpwt)
{
	stwuct wpcwdma_ep *ep = w_xpwt->wx_ep;
	stwuct wpcwdma_mw_seg seg;
	stwuct wpcwdma_mw *mw;

	mw = wpcwdma_mw_get(w_xpwt);
	if (!mw)
		wetuwn -EAGAIN;
	mw->mw_weq = NUWW;
	ep->we_wwite_pad_mw = mw;

	seg.mw_wen = XDW_UNIT;
	seg.mw_page = viwt_to_page(ep->we_wwite_pad);
	seg.mw_offset = offset_in_page(ep->we_wwite_pad);
	if (IS_EWW(fwww_map(w_xpwt, &seg, 1, twue, xdw_zewo, mw)))
		wetuwn -EIO;
	twace_xpwtwdma_mw_fastweg(mw);

	mw->mw_cqe.done = fwww_wc_fastweg;
	mw->mw_wegww.ww.next = NUWW;
	mw->mw_wegww.ww.ww_cqe = &mw->mw_cqe;
	mw->mw_wegww.ww.num_sge = 0;
	mw->mw_wegww.ww.opcode = IB_WW_WEG_MW;
	mw->mw_wegww.ww.send_fwags = 0;

	wetuwn ib_post_send(ep->we_id->qp, &mw->mw_wegww.ww, NUWW);
}
