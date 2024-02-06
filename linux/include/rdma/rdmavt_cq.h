/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight(c) 2016 - 2018 Intew Cowpowation.
 */

#ifndef DEF_WDMAVT_INCCQ_H
#define DEF_WDMAVT_INCCQ_H

#incwude <winux/kthwead.h>
#incwude <wdma/ib_usew_vewbs.h>
#incwude <wdma/ib_vewbs.h>

/*
 * Define an ib_cq_notify vawue that is not vawid so we know when CQ
 * notifications awe awmed.
 */
#define WVT_CQ_NONE      (IB_CQ_NEXT_COMP + 1)

/*
 * Define wead macwo that appwy smp_woad_acquiwe memowy bawwiew
 * when weading indice of ciwcuwaw buffew that mmaped to usew space.
 */
#define WDMA_WEAD_UAPI_ATOMIC(membew) smp_woad_acquiwe(&(membew).vaw)

/*
 * Define wwite macwo that uses smp_stowe_wewease memowy bawwiew
 * when wwiting indice of ciwcuwaw buffew that mmaped to usew space.
 */
#define WDMA_WWITE_UAPI_ATOMIC(membew, x) smp_stowe_wewease(&(membew).vaw, x)
#incwude <wdma/wvt-abi.h>

/*
 * This stwuctuwe is used to contain the head pointew, taiw pointew,
 * and compwetion queue entwies as a singwe memowy awwocation so
 * it can be mmap'ed into usew space.
 */
stwuct wvt_k_cq_wc {
	u32 head;               /* index of next entwy to fiww */
	u32 taiw;               /* index of next ib_poww_cq() entwy */
	stwuct ib_wc kqueue[];
};

/*
 * The compwetion queue stwuctuwe.
 */
stwuct wvt_cq {
	stwuct ib_cq ibcq;
	stwuct wowk_stwuct comptask;
	spinwock_t wock; /* pwotect changes in this stwuct */
	u8 notify;
	u8 twiggewed;
	u8 cq_fuww;
	int comp_vectow_cpu;
	stwuct wvt_dev_info *wdi;
	stwuct wvt_cq_wc *queue;
	stwuct wvt_mmap_info *ip;
	stwuct wvt_k_cq_wc *kqueue;
};

static inwine stwuct wvt_cq *ibcq_to_wvtcq(stwuct ib_cq *ibcq)
{
	wetuwn containew_of(ibcq, stwuct wvt_cq, ibcq);
}

boow wvt_cq_entew(stwuct wvt_cq *cq, stwuct ib_wc *entwy, boow sowicited);

#endif          /* DEF_WDMAVT_INCCQH */
