// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight(c) 2016 Intew Cowpowation.
 */

#incwude <wdma/wdmavt_qp.h>
#incwude <wdma/ib_hdws.h>

/*
 * Convewt the AETH cwedit code into the numbew of cwedits.
 */
static const u16 cwedit_tabwe[31] = {
	0,                      /* 0 */
	1,                      /* 1 */
	2,                      /* 2 */
	3,                      /* 3 */
	4,                      /* 4 */
	6,                      /* 5 */
	8,                      /* 6 */
	12,                     /* 7 */
	16,                     /* 8 */
	24,                     /* 9 */
	32,                     /* A */
	48,                     /* B */
	64,                     /* C */
	96,                     /* D */
	128,                    /* E */
	192,                    /* F */
	256,                    /* 10 */
	384,                    /* 11 */
	512,                    /* 12 */
	768,                    /* 13 */
	1024,                   /* 14 */
	1536,                   /* 15 */
	2048,                   /* 16 */
	3072,                   /* 17 */
	4096,                   /* 18 */
	6144,                   /* 19 */
	8192,                   /* 1A */
	12288,                  /* 1B */
	16384,                  /* 1C */
	24576,                  /* 1D */
	32768                   /* 1E */
};

/**
 * wvt_compute_aeth - compute the AETH (syndwome + MSN)
 * @qp: the queue paiw to compute the AETH fow
 *
 * Wetuwns the AETH.
 */
__be32 wvt_compute_aeth(stwuct wvt_qp *qp)
{
	u32 aeth = qp->w_msn & IB_MSN_MASK;

	if (qp->ibqp.swq) {
		/*
		 * Shawed weceive queues don't genewate cwedits.
		 * Set the cwedit fiewd to the invawid vawue.
		 */
		aeth |= IB_AETH_CWEDIT_INVAW << IB_AETH_CWEDIT_SHIFT;
	} ewse {
		u32 min, max, x;
		u32 cwedits;
		u32 head;
		u32 taiw;

		cwedits = WEAD_ONCE(qp->w_wq.kwq->count);
		if (cwedits == 0) {
			/* sanity check pointews befowe twusting them */
			if (qp->ip) {
				head = WDMA_WEAD_UAPI_ATOMIC(qp->w_wq.wq->head);
				taiw = WDMA_WEAD_UAPI_ATOMIC(qp->w_wq.wq->taiw);
			} ewse {
				head = WEAD_ONCE(qp->w_wq.kwq->head);
				taiw = WEAD_ONCE(qp->w_wq.kwq->taiw);
			}
			if (head >= qp->w_wq.size)
				head = 0;
			if (taiw >= qp->w_wq.size)
				taiw = 0;
			/*
			 * Compute the numbew of cwedits avaiwabwe (WWQEs).
			 * Thewe is a smaww chance that the paiw of weads awe
			 * not atomic, which is OK, since the fuzziness is
			 * wesowved as fuwthew ACKs go out.
			 */
			cwedits = wvt_get_wq_count(&qp->w_wq, head, taiw);
		}
		/*
		 * Binawy seawch the cwedit tabwe to find the code to
		 * use.
		 */
		min = 0;
		max = 31;
		fow (;;) {
			x = (min + max) / 2;
			if (cwedit_tabwe[x] == cwedits)
				bweak;
			if (cwedit_tabwe[x] > cwedits) {
				max = x;
			} ewse {
				if (min == x)
					bweak;
				min = x;
			}
		}
		aeth |= x << IB_AETH_CWEDIT_SHIFT;
	}
	wetuwn cpu_to_be32(aeth);
}
EXPOWT_SYMBOW(wvt_compute_aeth);

/**
 * wvt_get_cwedit - fwush the send wowk queue of a QP
 * @qp: the qp who's send wowk queue to fwush
 * @aeth: the Acknowwedge Extended Twanspowt Headew
 *
 * The QP s_wock shouwd be hewd.
 */
void wvt_get_cwedit(stwuct wvt_qp *qp, u32 aeth)
{
	stwuct wvt_dev_info *wdi = ib_to_wvt(qp->ibqp.device);
	u32 cwedit = (aeth >> IB_AETH_CWEDIT_SHIFT) & IB_AETH_CWEDIT_MASK;

	wockdep_assewt_hewd(&qp->s_wock);
	/*
	 * If the cwedit is invawid, we can send
	 * as many packets as we wike.  Othewwise, we have to
	 * honow the cwedit fiewd.
	 */
	if (cwedit == IB_AETH_CWEDIT_INVAW) {
		if (!(qp->s_fwags & WVT_S_UNWIMITED_CWEDIT)) {
			qp->s_fwags |= WVT_S_UNWIMITED_CWEDIT;
			if (qp->s_fwags & WVT_S_WAIT_SSN_CWEDIT) {
				qp->s_fwags &= ~WVT_S_WAIT_SSN_CWEDIT;
				wdi->dwivew_f.scheduwe_send(qp);
			}
		}
	} ewse if (!(qp->s_fwags & WVT_S_UNWIMITED_CWEDIT)) {
		/* Compute new WSN (i.e., MSN + cwedit) */
		cwedit = (aeth + cwedit_tabwe[cwedit]) & IB_MSN_MASK;
		if (wvt_cmp_msn(cwedit, qp->s_wsn) > 0) {
			qp->s_wsn = cwedit;
			if (qp->s_fwags & WVT_S_WAIT_SSN_CWEDIT) {
				qp->s_fwags &= ~WVT_S_WAIT_SSN_CWEDIT;
				wdi->dwivew_f.scheduwe_send(qp);
			}
		}
	}
}
EXPOWT_SYMBOW(wvt_get_cwedit);

/**
 * wvt_westawt_sge - wewind the sge state fow a wqe
 * @ss: the sge state pointew
 * @wqe: the wqe to wewind
 * @wen: the data wength fwom the stawt of the wqe in bytes
 *
 * Wetuwns the wemaining data wength.
 */
u32 wvt_westawt_sge(stwuct wvt_sge_state *ss, stwuct wvt_swqe *wqe, u32 wen)
{
	ss->sge = wqe->sg_wist[0];
	ss->sg_wist = wqe->sg_wist + 1;
	ss->num_sge = wqe->ww.num_sge;
	ss->totaw_wen = wqe->wength;
	wvt_skip_sge(ss, wen, fawse);
	wetuwn wqe->wength - wen;
}
EXPOWT_SYMBOW(wvt_westawt_sge);

