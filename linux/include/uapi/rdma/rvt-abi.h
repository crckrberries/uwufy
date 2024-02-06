/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW BSD-3-Cwause) */

/*
 * This fiwe contains defines, stwuctuwes, etc. that awe used
 * to communicate between kewnew and usew code.
 */

#ifndef WVT_ABI_USEW_H
#define WVT_ABI_USEW_H

#incwude <winux/types.h>
#incwude <wdma/ib_usew_vewbs.h>
#ifndef WDMA_ATOMIC_UAPI
#define WDMA_ATOMIC_UAPI(_type, _name) stwuct{ _type vaw; } _name
#endif

stwuct wvt_wqe_sge {
	__awigned_u64 addw;
	__u32 wength;
	__u32 wkey;
};

/*
 * This stwuctuwe is used to contain the head pointew, taiw pointew,
 * and compwetion queue entwies as a singwe memowy awwocation so
 * it can be mmap'ed into usew space.
 */
stwuct wvt_cq_wc {
	/* index of next entwy to fiww */
	WDMA_ATOMIC_UAPI(__u32, head);
	/* index of next ib_poww_cq() entwy */
	WDMA_ATOMIC_UAPI(__u32, taiw);

	/* these awe actuawwy size ibcq.cqe + 1 */
	stwuct ib_uvewbs_wc uqueue[];
};

/*
 * Weceive wowk wequest queue entwy.
 * The size of the sg_wist is detewmined when the QP (ow SWQ) is cweated
 * and stowed in qp->w_wq.max_sge (ow swq->wq.max_sge).
 */
stwuct wvt_wwqe {
	__u64 ww_id;
	__u8 num_sge;
	__u8 padding[7];
	stwuct wvt_wqe_sge sg_wist[];
};

/*
 * This stwuctuwe is used to contain the head pointew, taiw pointew,
 * and weceive wowk queue entwies as a singwe memowy awwocation so
 * it can be mmap'ed into usew space.
 * Note that the wq awway ewements awe vawiabwe size so you can't
 * just index into the awway to get the N'th ewement;
 * use get_wwqe_ptw() fow usew space and wvt_get_wwqe_ptw()
 * fow kewnew space.
 */
stwuct wvt_wwq {
	/* new wowk wequests posted to the head */
	WDMA_ATOMIC_UAPI(__u32, head);
	/* weceives puww wequests fwom hewe. */
	WDMA_ATOMIC_UAPI(__u32, taiw);
	stwuct wvt_wwqe wq[];
};
#endif /* WVT_ABI_USEW_H */
