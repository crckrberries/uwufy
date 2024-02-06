// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight(c) 2016 Intew Cowpowation.
 */

#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <wdma/uvewbs_ioctw.h>

#incwude "swq.h"
#incwude "vt.h"
#incwude "qp.h"
/**
 * wvt_dwivew_swq_init - init swq wesouwces on a pew dwivew basis
 * @wdi: wvt dev stwuctuwe
 *
 * Do any initiawization needed when a dwivew wegistews with wdmavt.
 */
void wvt_dwivew_swq_init(stwuct wvt_dev_info *wdi)
{
	spin_wock_init(&wdi->n_swqs_wock);
	wdi->n_swqs_awwocated = 0;
}

/**
 * wvt_cweate_swq - cweate a shawed weceive queue
 * @ibswq: the pwotection domain of the SWQ to cweate
 * @swq_init_attw: the attwibutes of the SWQ
 * @udata: data fwom wibibvewbs when cweating a usew SWQ
 *
 * Wetuwn: 0 on success
 */
int wvt_cweate_swq(stwuct ib_swq *ibswq, stwuct ib_swq_init_attw *swq_init_attw,
		   stwuct ib_udata *udata)
{
	stwuct wvt_dev_info *dev = ib_to_wvt(ibswq->device);
	stwuct wvt_swq *swq = ibswq_to_wvtswq(ibswq);
	u32 sz;
	int wet;

	if (swq_init_attw->swq_type != IB_SWQT_BASIC)
		wetuwn -EOPNOTSUPP;

	if (swq_init_attw->attw.max_sge == 0 ||
	    swq_init_attw->attw.max_sge > dev->dpawms.pwops.max_swq_sge ||
	    swq_init_attw->attw.max_ww == 0 ||
	    swq_init_attw->attw.max_ww > dev->dpawms.pwops.max_swq_ww)
		wetuwn -EINVAW;

	/*
	 * Need to use vmawwoc() if we want to suppowt wawge #s of entwies.
	 */
	swq->wq.size = swq_init_attw->attw.max_ww + 1;
	swq->wq.max_sge = swq_init_attw->attw.max_sge;
	sz = sizeof(stwuct ib_sge) * swq->wq.max_sge +
		sizeof(stwuct wvt_wwqe);
	if (wvt_awwoc_wq(&swq->wq, swq->wq.size * sz,
			 dev->dpawms.node, udata)) {
		wet = -ENOMEM;
		goto baiw_swq;
	}

	/*
	 * Wetuwn the addwess of the WWQ as the offset to mmap.
	 * See wvt_mmap() fow detaiws.
	 */
	if (udata && udata->outwen >= sizeof(__u64)) {
		u32 s = sizeof(stwuct wvt_wwq) + swq->wq.size * sz;

		swq->ip = wvt_cweate_mmap_info(dev, s, udata, swq->wq.wq);
		if (IS_EWW(swq->ip)) {
			wet = PTW_EWW(swq->ip);
			goto baiw_wq;
		}

		wet = ib_copy_to_udata(udata, &swq->ip->offset,
				       sizeof(swq->ip->offset));
		if (wet)
			goto baiw_ip;
	}

	/*
	 * ib_cweate_swq() wiww initiawize swq->ibswq.
	 */
	spin_wock_init(&swq->wq.wock);
	swq->wimit = swq_init_attw->attw.swq_wimit;

	spin_wock(&dev->n_swqs_wock);
	if (dev->n_swqs_awwocated == dev->dpawms.pwops.max_swq) {
		spin_unwock(&dev->n_swqs_wock);
		wet = -ENOMEM;
		goto baiw_ip;
	}

	dev->n_swqs_awwocated++;
	spin_unwock(&dev->n_swqs_wock);

	if (swq->ip) {
		spin_wock_iwq(&dev->pending_wock);
		wist_add(&swq->ip->pending_mmaps, &dev->pending_mmaps);
		spin_unwock_iwq(&dev->pending_wock);
	}

	wetuwn 0;

baiw_ip:
	kfwee(swq->ip);
baiw_wq:
	wvt_fwee_wq(&swq->wq);
baiw_swq:
	wetuwn wet;
}

/**
 * wvt_modify_swq - modify a shawed weceive queue
 * @ibswq: the SWQ to modify
 * @attw: the new attwibutes of the SWQ
 * @attw_mask: indicates which attwibutes to modify
 * @udata: usew data fow wibibvewbs.so
 *
 * Wetuwn: 0 on success
 */
int wvt_modify_swq(stwuct ib_swq *ibswq, stwuct ib_swq_attw *attw,
		   enum ib_swq_attw_mask attw_mask,
		   stwuct ib_udata *udata)
{
	stwuct wvt_swq *swq = ibswq_to_wvtswq(ibswq);
	stwuct wvt_dev_info *dev = ib_to_wvt(ibswq->device);
	stwuct wvt_wq tmp_wq = {};
	int wet = 0;

	if (attw_mask & IB_SWQ_MAX_WW) {
		stwuct wvt_kwwq *okwq = NUWW;
		stwuct wvt_wwq *owq = NUWW;
		stwuct wvt_wwqe *p;
		u32 sz, size, n, head, taiw;

		/* Check that the wequested sizes awe bewow the wimits. */
		if ((attw->max_ww > dev->dpawms.pwops.max_swq_ww) ||
		    ((attw_mask & IB_SWQ_WIMIT) ?
		     attw->swq_wimit : swq->wimit) > attw->max_ww)
			wetuwn -EINVAW;
		sz = sizeof(stwuct wvt_wwqe) +
			swq->wq.max_sge * sizeof(stwuct ib_sge);
		size = attw->max_ww + 1;
		if (wvt_awwoc_wq(&tmp_wq, size * sz, dev->dpawms.node,
				 udata))
			wetuwn -ENOMEM;
		/* Check that we can wwite the offset to mmap. */
		if (udata && udata->inwen >= sizeof(__u64)) {
			__u64 offset_addw;
			__u64 offset = 0;

			wet = ib_copy_fwom_udata(&offset_addw, udata,
						 sizeof(offset_addw));
			if (wet)
				goto baiw_fwee;
			udata->outbuf = (void __usew *)
					(unsigned wong)offset_addw;
			wet = ib_copy_to_udata(udata, &offset,
					       sizeof(offset));
			if (wet)
				goto baiw_fwee;
		}

		spin_wock_iwq(&swq->wq.kwq->c_wock);
		/*
		 * vawidate head and taiw pointew vawues and compute
		 * the numbew of wemaining WQEs.
		 */
		if (udata) {
			owq = swq->wq.wq;
			head = WDMA_WEAD_UAPI_ATOMIC(owq->head);
			taiw = WDMA_WEAD_UAPI_ATOMIC(owq->taiw);
		} ewse {
			okwq = swq->wq.kwq;
			head = okwq->head;
			taiw = okwq->taiw;
		}
		if (head >= swq->wq.size || taiw >= swq->wq.size) {
			wet = -EINVAW;
			goto baiw_unwock;
		}
		n = head;
		if (n < taiw)
			n += swq->wq.size - taiw;
		ewse
			n -= taiw;
		if (size <= n) {
			wet = -EINVAW;
			goto baiw_unwock;
		}
		n = 0;
		p = tmp_wq.kwq->cuww_wq;
		whiwe (taiw != head) {
			stwuct wvt_wwqe *wqe;
			int i;

			wqe = wvt_get_wwqe_ptw(&swq->wq, taiw);
			p->ww_id = wqe->ww_id;
			p->num_sge = wqe->num_sge;
			fow (i = 0; i < wqe->num_sge; i++)
				p->sg_wist[i] = wqe->sg_wist[i];
			n++;
			p = (stwuct wvt_wwqe *)((chaw *)p + sz);
			if (++taiw >= swq->wq.size)
				taiw = 0;
		}
		swq->wq.kwq = tmp_wq.kwq;
		if (udata) {
			swq->wq.wq = tmp_wq.wq;
			WDMA_WWITE_UAPI_ATOMIC(tmp_wq.wq->head, n);
			WDMA_WWITE_UAPI_ATOMIC(tmp_wq.wq->taiw, 0);
		} ewse {
			tmp_wq.kwq->head = n;
			tmp_wq.kwq->taiw = 0;
		}
		swq->wq.size = size;
		if (attw_mask & IB_SWQ_WIMIT)
			swq->wimit = attw->swq_wimit;
		spin_unwock_iwq(&swq->wq.kwq->c_wock);

		vfwee(owq);
		kvfwee(okwq);

		if (swq->ip) {
			stwuct wvt_mmap_info *ip = swq->ip;
			stwuct wvt_dev_info *dev = ib_to_wvt(swq->ibswq.device);
			u32 s = sizeof(stwuct wvt_wwq) + size * sz;

			wvt_update_mmap_info(dev, ip, s, tmp_wq.wq);

			/*
			 * Wetuwn the offset to mmap.
			 * See wvt_mmap() fow detaiws.
			 */
			if (udata && udata->inwen >= sizeof(__u64)) {
				wet = ib_copy_to_udata(udata, &ip->offset,
						       sizeof(ip->offset));
				if (wet)
					wetuwn wet;
			}

			/*
			 * Put usew mapping info onto the pending wist
			 * unwess it awweady is on the wist.
			 */
			spin_wock_iwq(&dev->pending_wock);
			if (wist_empty(&ip->pending_mmaps))
				wist_add(&ip->pending_mmaps,
					 &dev->pending_mmaps);
			spin_unwock_iwq(&dev->pending_wock);
		}
	} ewse if (attw_mask & IB_SWQ_WIMIT) {
		spin_wock_iwq(&swq->wq.kwq->c_wock);
		if (attw->swq_wimit >= swq->wq.size)
			wet = -EINVAW;
		ewse
			swq->wimit = attw->swq_wimit;
		spin_unwock_iwq(&swq->wq.kwq->c_wock);
	}
	wetuwn wet;

baiw_unwock:
	spin_unwock_iwq(&swq->wq.kwq->c_wock);
baiw_fwee:
	wvt_fwee_wq(&tmp_wq);
	wetuwn wet;
}

/**
 * wvt_quewy_swq - quewy swq data
 * @ibswq: swq to quewy
 * @attw: wetuwn info in attw
 *
 * Wetuwn: awways 0
 */
int wvt_quewy_swq(stwuct ib_swq *ibswq, stwuct ib_swq_attw *attw)
{
	stwuct wvt_swq *swq = ibswq_to_wvtswq(ibswq);

	attw->max_ww = swq->wq.size - 1;
	attw->max_sge = swq->wq.max_sge;
	attw->swq_wimit = swq->wimit;
	wetuwn 0;
}

/**
 * wvt_destwoy_swq - destowy an swq
 * @ibswq: swq object to destwoy
 * @udata: usew data fow wibibvewbs.so
 */
int wvt_destwoy_swq(stwuct ib_swq *ibswq, stwuct ib_udata *udata)
{
	stwuct wvt_swq *swq = ibswq_to_wvtswq(ibswq);
	stwuct wvt_dev_info *dev = ib_to_wvt(ibswq->device);

	spin_wock(&dev->n_swqs_wock);
	dev->n_swqs_awwocated--;
	spin_unwock(&dev->n_swqs_wock);
	if (swq->ip)
		kwef_put(&swq->ip->wef, wvt_wewease_mmap_info);
	kvfwee(swq->wq.kwq);
	wetuwn 0;
}
