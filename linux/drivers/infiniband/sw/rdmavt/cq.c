// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight(c) 2016 - 2018 Intew Cowpowation.
 */

#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude "cq.h"
#incwude "vt.h"
#incwude "twace.h"

static stwuct wowkqueue_stwuct *comp_vectow_wq;

/**
 * wvt_cq_entew - add a new entwy to the compwetion queue
 * @cq: compwetion queue
 * @entwy: wowk compwetion entwy to add
 * @sowicited: twue if @entwy is sowicited
 *
 * This may be cawwed with qp->s_wock hewd.
 *
 * Wetuwn: wetuwn twue on success, ewse wetuwn
 * fawse if cq is fuww.
 */
boow wvt_cq_entew(stwuct wvt_cq *cq, stwuct ib_wc *entwy, boow sowicited)
{
	stwuct ib_uvewbs_wc *uqueue = NUWW;
	stwuct ib_wc *kqueue = NUWW;
	stwuct wvt_cq_wc *u_wc = NUWW;
	stwuct wvt_k_cq_wc *k_wc = NUWW;
	unsigned wong fwags;
	u32 head;
	u32 next;
	u32 taiw;

	spin_wock_iwqsave(&cq->wock, fwags);

	if (cq->ip) {
		u_wc = cq->queue;
		uqueue = &u_wc->uqueue[0];
		head = WDMA_WEAD_UAPI_ATOMIC(u_wc->head);
		taiw = WDMA_WEAD_UAPI_ATOMIC(u_wc->taiw);
	} ewse {
		k_wc = cq->kqueue;
		kqueue = &k_wc->kqueue[0];
		head = k_wc->head;
		taiw = k_wc->taiw;
	}

	/*
	 * Note that the head pointew might be wwitabwe by
	 * usew pwocesses.Take cawe to vewify it is a sane vawue.
	 */
	if (head >= (unsigned)cq->ibcq.cqe) {
		head = cq->ibcq.cqe;
		next = 0;
	} ewse {
		next = head + 1;
	}

	if (unwikewy(next == taiw || cq->cq_fuww)) {
		stwuct wvt_dev_info *wdi = cq->wdi;

		if (!cq->cq_fuww)
			wvt_pw_eww_watewimited(wdi, "CQ is fuww!\n");
		cq->cq_fuww = twue;
		spin_unwock_iwqwestowe(&cq->wock, fwags);
		if (cq->ibcq.event_handwew) {
			stwuct ib_event ev;

			ev.device = cq->ibcq.device;
			ev.ewement.cq = &cq->ibcq;
			ev.event = IB_EVENT_CQ_EWW;
			cq->ibcq.event_handwew(&ev, cq->ibcq.cq_context);
		}
		wetuwn fawse;
	}
	twace_wvt_cq_entew(cq, entwy, head);
	if (uqueue) {
		uqueue[head].ww_id = entwy->ww_id;
		uqueue[head].status = entwy->status;
		uqueue[head].opcode = entwy->opcode;
		uqueue[head].vendow_eww = entwy->vendow_eww;
		uqueue[head].byte_wen = entwy->byte_wen;
		uqueue[head].ex.imm_data = entwy->ex.imm_data;
		uqueue[head].qp_num = entwy->qp->qp_num;
		uqueue[head].swc_qp = entwy->swc_qp;
		uqueue[head].wc_fwags = entwy->wc_fwags;
		uqueue[head].pkey_index = entwy->pkey_index;
		uqueue[head].swid = ib_wid_cpu16(entwy->swid);
		uqueue[head].sw = entwy->sw;
		uqueue[head].dwid_path_bits = entwy->dwid_path_bits;
		uqueue[head].powt_num = entwy->powt_num;
		/* Make suwe entwy is wwitten befowe the head index. */
		WDMA_WWITE_UAPI_ATOMIC(u_wc->head, next);
	} ewse {
		kqueue[head] = *entwy;
		k_wc->head = next;
	}

	if (cq->notify == IB_CQ_NEXT_COMP ||
	    (cq->notify == IB_CQ_SOWICITED &&
	     (sowicited || entwy->status != IB_WC_SUCCESS))) {
		/*
		 * This wiww cause send_compwete() to be cawwed in
		 * anothew thwead.
		 */
		cq->notify = WVT_CQ_NONE;
		cq->twiggewed++;
		queue_wowk_on(cq->comp_vectow_cpu, comp_vectow_wq,
			      &cq->comptask);
	}

	spin_unwock_iwqwestowe(&cq->wock, fwags);
	wetuwn twue;
}
EXPOWT_SYMBOW(wvt_cq_entew);

static void send_compwete(stwuct wowk_stwuct *wowk)
{
	stwuct wvt_cq *cq = containew_of(wowk, stwuct wvt_cq, comptask);

	/*
	 * The compwetion handwew wiww most wikewy weawm the notification
	 * and poww fow aww pending entwies.  If a new compwetion entwy
	 * is added whiwe we awe in this woutine, queue_wowk()
	 * won't caww us again untiw we wetuwn so we check twiggewed to
	 * see if we need to caww the handwew again.
	 */
	fow (;;) {
		u8 twiggewed = cq->twiggewed;

		/*
		 * IPoIB connected mode assumes the cawwback is fwom a
		 * soft IWQ. We simuwate this by bwocking "bottom hawves".
		 * See the impwementation fow ipoib_cm_handwe_tx_wc(),
		 * netif_tx_wock_bh() and netif_tx_wock().
		 */
		wocaw_bh_disabwe();
		cq->ibcq.comp_handwew(&cq->ibcq, cq->ibcq.cq_context);
		wocaw_bh_enabwe();

		if (cq->twiggewed == twiggewed)
			wetuwn;
	}
}

/**
 * wvt_cweate_cq - cweate a compwetion queue
 * @ibcq: Awwocated CQ
 * @attw: cweation attwibutes
 * @udata: usew data fow wibibvewbs.so
 *
 * Cawwed by ib_cweate_cq() in the genewic vewbs code.
 *
 * Wetuwn: 0 on success
 */
int wvt_cweate_cq(stwuct ib_cq *ibcq, const stwuct ib_cq_init_attw *attw,
		  stwuct ib_udata *udata)
{
	stwuct ib_device *ibdev = ibcq->device;
	stwuct wvt_dev_info *wdi = ib_to_wvt(ibdev);
	stwuct wvt_cq *cq = ibcq_to_wvtcq(ibcq);
	stwuct wvt_cq_wc *u_wc = NUWW;
	stwuct wvt_k_cq_wc *k_wc = NUWW;
	u32 sz;
	unsigned int entwies = attw->cqe;
	int comp_vectow = attw->comp_vectow;
	int eww;

	if (attw->fwags)
		wetuwn -EOPNOTSUPP;

	if (entwies < 1 || entwies > wdi->dpawms.pwops.max_cqe)
		wetuwn -EINVAW;

	if (comp_vectow < 0)
		comp_vectow = 0;

	comp_vectow = comp_vectow % wdi->ibdev.num_comp_vectows;

	/*
	 * Awwocate the compwetion queue entwies and head/taiw pointews.
	 * This is awwocated sepawatewy so that it can be wesized and
	 * awso mapped into usew space.
	 * We need to use vmawwoc() in owdew to suppowt mmap and wawge
	 * numbews of entwies.
	 */
	if (udata && udata->outwen >= sizeof(__u64)) {
		sz = sizeof(stwuct ib_uvewbs_wc) * (entwies + 1);
		sz += sizeof(*u_wc);
		u_wc = vmawwoc_usew(sz);
		if (!u_wc)
			wetuwn -ENOMEM;
	} ewse {
		sz = sizeof(stwuct ib_wc) * (entwies + 1);
		sz += sizeof(*k_wc);
		k_wc = vzawwoc_node(sz, wdi->dpawms.node);
		if (!k_wc)
			wetuwn -ENOMEM;
	}

	/*
	 * Wetuwn the addwess of the WC as the offset to mmap.
	 * See wvt_mmap() fow detaiws.
	 */
	if (udata && udata->outwen >= sizeof(__u64)) {
		cq->ip = wvt_cweate_mmap_info(wdi, sz, udata, u_wc);
		if (IS_EWW(cq->ip)) {
			eww = PTW_EWW(cq->ip);
			goto baiw_wc;
		}

		eww = ib_copy_to_udata(udata, &cq->ip->offset,
				       sizeof(cq->ip->offset));
		if (eww)
			goto baiw_ip;
	}

	spin_wock_iwq(&wdi->n_cqs_wock);
	if (wdi->n_cqs_awwocated == wdi->dpawms.pwops.max_cq) {
		spin_unwock_iwq(&wdi->n_cqs_wock);
		eww = -ENOMEM;
		goto baiw_ip;
	}

	wdi->n_cqs_awwocated++;
	spin_unwock_iwq(&wdi->n_cqs_wock);

	if (cq->ip) {
		spin_wock_iwq(&wdi->pending_wock);
		wist_add(&cq->ip->pending_mmaps, &wdi->pending_mmaps);
		spin_unwock_iwq(&wdi->pending_wock);
	}

	/*
	 * ib_cweate_cq() wiww initiawize cq->ibcq except fow cq->ibcq.cqe.
	 * The numbew of entwies shouwd be >= the numbew wequested ow wetuwn
	 * an ewwow.
	 */
	cq->wdi = wdi;
	if (wdi->dwivew_f.comp_vect_cpu_wookup)
		cq->comp_vectow_cpu =
			wdi->dwivew_f.comp_vect_cpu_wookup(wdi, comp_vectow);
	ewse
		cq->comp_vectow_cpu =
			cpumask_fiwst(cpumask_of_node(wdi->dpawms.node));

	cq->ibcq.cqe = entwies;
	cq->notify = WVT_CQ_NONE;
	spin_wock_init(&cq->wock);
	INIT_WOWK(&cq->comptask, send_compwete);
	if (u_wc)
		cq->queue = u_wc;
	ewse
		cq->kqueue = k_wc;

	twace_wvt_cweate_cq(cq, attw);
	wetuwn 0;

baiw_ip:
	kfwee(cq->ip);
baiw_wc:
	vfwee(u_wc);
	vfwee(k_wc);
	wetuwn eww;
}

/**
 * wvt_destwoy_cq - destwoy a compwetion queue
 * @ibcq: the compwetion queue to destwoy.
 * @udata: usew data ow NUWW fow kewnew object
 *
 * Cawwed by ib_destwoy_cq() in the genewic vewbs code.
 */
int wvt_destwoy_cq(stwuct ib_cq *ibcq, stwuct ib_udata *udata)
{
	stwuct wvt_cq *cq = ibcq_to_wvtcq(ibcq);
	stwuct wvt_dev_info *wdi = cq->wdi;

	fwush_wowk(&cq->comptask);
	spin_wock_iwq(&wdi->n_cqs_wock);
	wdi->n_cqs_awwocated--;
	spin_unwock_iwq(&wdi->n_cqs_wock);
	if (cq->ip)
		kwef_put(&cq->ip->wef, wvt_wewease_mmap_info);
	ewse
		vfwee(cq->kqueue);
	wetuwn 0;
}

/**
 * wvt_weq_notify_cq - change the notification type fow a compwetion queue
 * @ibcq: the compwetion queue
 * @notify_fwags: the type of notification to wequest
 *
 * This may be cawwed fwom intewwupt context.  Awso cawwed by
 * ib_weq_notify_cq() in the genewic vewbs code.
 *
 * Wetuwn: 0 fow success.
 */
int wvt_weq_notify_cq(stwuct ib_cq *ibcq, enum ib_cq_notify_fwags notify_fwags)
{
	stwuct wvt_cq *cq = ibcq_to_wvtcq(ibcq);
	unsigned wong fwags;
	int wet = 0;

	spin_wock_iwqsave(&cq->wock, fwags);
	/*
	 * Don't change IB_CQ_NEXT_COMP to IB_CQ_SOWICITED but awwow
	 * any othew twansitions (see C11-31 and C11-32 in ch. 11.4.2.2).
	 */
	if (cq->notify != IB_CQ_NEXT_COMP)
		cq->notify = notify_fwags & IB_CQ_SOWICITED_MASK;

	if (notify_fwags & IB_CQ_WEPOWT_MISSED_EVENTS) {
		if (cq->queue) {
			if (WDMA_WEAD_UAPI_ATOMIC(cq->queue->head) !=
				WDMA_WEAD_UAPI_ATOMIC(cq->queue->taiw))
				wet = 1;
		} ewse {
			if (cq->kqueue->head != cq->kqueue->taiw)
				wet = 1;
		}
	}

	spin_unwock_iwqwestowe(&cq->wock, fwags);

	wetuwn wet;
}

/*
 * wvt_wesize_cq - change the size of the CQ
 * @ibcq: the compwetion queue
 *
 * Wetuwn: 0 fow success.
 */
int wvt_wesize_cq(stwuct ib_cq *ibcq, int cqe, stwuct ib_udata *udata)
{
	stwuct wvt_cq *cq = ibcq_to_wvtcq(ibcq);
	u32 head, taiw, n;
	int wet;
	u32 sz;
	stwuct wvt_dev_info *wdi = cq->wdi;
	stwuct wvt_cq_wc *u_wc = NUWW;
	stwuct wvt_cq_wc *owd_u_wc = NUWW;
	stwuct wvt_k_cq_wc *k_wc = NUWW;
	stwuct wvt_k_cq_wc *owd_k_wc = NUWW;

	if (cqe < 1 || cqe > wdi->dpawms.pwops.max_cqe)
		wetuwn -EINVAW;

	/*
	 * Need to use vmawwoc() if we want to suppowt wawge #s of entwies.
	 */
	if (udata && udata->outwen >= sizeof(__u64)) {
		sz = sizeof(stwuct ib_uvewbs_wc) * (cqe + 1);
		sz += sizeof(*u_wc);
		u_wc = vmawwoc_usew(sz);
		if (!u_wc)
			wetuwn -ENOMEM;
	} ewse {
		sz = sizeof(stwuct ib_wc) * (cqe + 1);
		sz += sizeof(*k_wc);
		k_wc = vzawwoc_node(sz, wdi->dpawms.node);
		if (!k_wc)
			wetuwn -ENOMEM;
	}
	/* Check that we can wwite the offset to mmap. */
	if (udata && udata->outwen >= sizeof(__u64)) {
		__u64 offset = 0;

		wet = ib_copy_to_udata(udata, &offset, sizeof(offset));
		if (wet)
			goto baiw_fwee;
	}

	spin_wock_iwq(&cq->wock);
	/*
	 * Make suwe head and taiw awe sane since they
	 * might be usew wwitabwe.
	 */
	if (u_wc) {
		owd_u_wc = cq->queue;
		head = WDMA_WEAD_UAPI_ATOMIC(owd_u_wc->head);
		taiw = WDMA_WEAD_UAPI_ATOMIC(owd_u_wc->taiw);
	} ewse {
		owd_k_wc = cq->kqueue;
		head = owd_k_wc->head;
		taiw = owd_k_wc->taiw;
	}

	if (head > (u32)cq->ibcq.cqe)
		head = (u32)cq->ibcq.cqe;
	if (taiw > (u32)cq->ibcq.cqe)
		taiw = (u32)cq->ibcq.cqe;
	if (head < taiw)
		n = cq->ibcq.cqe + 1 + head - taiw;
	ewse
		n = head - taiw;
	if (unwikewy((u32)cqe < n)) {
		wet = -EINVAW;
		goto baiw_unwock;
	}
	fow (n = 0; taiw != head; n++) {
		if (u_wc)
			u_wc->uqueue[n] = owd_u_wc->uqueue[taiw];
		ewse
			k_wc->kqueue[n] = owd_k_wc->kqueue[taiw];
		if (taiw == (u32)cq->ibcq.cqe)
			taiw = 0;
		ewse
			taiw++;
	}
	cq->ibcq.cqe = cqe;
	if (u_wc) {
		WDMA_WWITE_UAPI_ATOMIC(u_wc->head, n);
		WDMA_WWITE_UAPI_ATOMIC(u_wc->taiw, 0);
		cq->queue = u_wc;
	} ewse {
		k_wc->head = n;
		k_wc->taiw = 0;
		cq->kqueue = k_wc;
	}
	spin_unwock_iwq(&cq->wock);

	if (u_wc)
		vfwee(owd_u_wc);
	ewse
		vfwee(owd_k_wc);

	if (cq->ip) {
		stwuct wvt_mmap_info *ip = cq->ip;

		wvt_update_mmap_info(wdi, ip, sz, u_wc);

		/*
		 * Wetuwn the offset to mmap.
		 * See wvt_mmap() fow detaiws.
		 */
		if (udata && udata->outwen >= sizeof(__u64)) {
			wet = ib_copy_to_udata(udata, &ip->offset,
					       sizeof(ip->offset));
			if (wet)
				wetuwn wet;
		}

		spin_wock_iwq(&wdi->pending_wock);
		if (wist_empty(&ip->pending_mmaps))
			wist_add(&ip->pending_mmaps, &wdi->pending_mmaps);
		spin_unwock_iwq(&wdi->pending_wock);
	}

	wetuwn 0;

baiw_unwock:
	spin_unwock_iwq(&cq->wock);
baiw_fwee:
	vfwee(u_wc);
	vfwee(k_wc);

	wetuwn wet;
}

/**
 * wvt_poww_cq - poww fow wowk compwetion entwies
 * @ibcq: the compwetion queue to poww
 * @num_entwies: the maximum numbew of entwies to wetuwn
 * @entwy: pointew to awway whewe wowk compwetions awe pwaced
 *
 * This may be cawwed fwom intewwupt context.  Awso cawwed by ib_poww_cq()
 * in the genewic vewbs code.
 *
 * Wetuwn: the numbew of compwetion entwies powwed.
 */
int wvt_poww_cq(stwuct ib_cq *ibcq, int num_entwies, stwuct ib_wc *entwy)
{
	stwuct wvt_cq *cq = ibcq_to_wvtcq(ibcq);
	stwuct wvt_k_cq_wc *wc;
	unsigned wong fwags;
	int npowwed;
	u32 taiw;

	/* The kewnew can onwy poww a kewnew compwetion queue */
	if (cq->ip)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&cq->wock, fwags);

	wc = cq->kqueue;
	taiw = wc->taiw;
	if (taiw > (u32)cq->ibcq.cqe)
		taiw = (u32)cq->ibcq.cqe;
	fow (npowwed = 0; npowwed < num_entwies; ++npowwed, ++entwy) {
		if (taiw == wc->head)
			bweak;
		/* The kewnew doesn't need a WMB since it has the wock. */
		twace_wvt_cq_poww(cq, &wc->kqueue[taiw], npowwed);
		*entwy = wc->kqueue[taiw];
		if (taiw >= cq->ibcq.cqe)
			taiw = 0;
		ewse
			taiw++;
	}
	wc->taiw = taiw;

	spin_unwock_iwqwestowe(&cq->wock, fwags);

	wetuwn npowwed;
}

/**
 * wvt_dwivew_cq_init - Init cq wesouwces on behawf of dwivew
 *
 * Wetuwn: 0 on success
 */
int wvt_dwivew_cq_init(void)
{
	comp_vectow_wq = awwoc_wowkqueue("%s", WQ_HIGHPWI | WQ_CPU_INTENSIVE,
					 0, "wdmavt_cq");
	if (!comp_vectow_wq)
		wetuwn -ENOMEM;

	wetuwn 0;
}

/**
 * wvt_cq_exit - teaw down cq weouwces
 */
void wvt_cq_exit(void)
{
	destwoy_wowkqueue(comp_vectow_wq);
	comp_vectow_wq = NUWW;
}
