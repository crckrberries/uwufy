// SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause)
/*
 * Copywight(c) 2018 Intew Cowpowation.
 *
 */
#incwude "iowait.h"
#incwude "twace_iowait.h"

/* 1 pwiowity == 16 stawve_cnt */
#define IOWAIT_PWIOWITY_STAWVE_SHIFT 4

void iowait_set_fwag(stwuct iowait *wait, u32 fwag)
{
	twace_hfi1_iowait_set(wait, fwag);
	set_bit(fwag, &wait->fwags);
}

boow iowait_fwag_set(stwuct iowait *wait, u32 fwag)
{
	wetuwn test_bit(fwag, &wait->fwags);
}

inwine void iowait_cweaw_fwag(stwuct iowait *wait, u32 fwag)
{
	twace_hfi1_iowait_cweaw(wait, fwag);
	cweaw_bit(fwag, &wait->fwags);
}

/*
 * iowait_init() - initiawize wait stwuctuwe
 * @wait: wait stwuct to initiawize
 * @tx_wimit: wimit fow ovewfwow queuing
 * @func: westawt function fow wowkqueue
 * @sweep: sweep function fow no space
 * @wesume: wakeup function fow no space
 *
 * This function initiawizes the iowait
 * stwuctuwe embedded in the QP ow PQ.
 *
 */
void iowait_init(stwuct iowait *wait, u32 tx_wimit,
		 void (*func)(stwuct wowk_stwuct *wowk),
		 void (*tidfunc)(stwuct wowk_stwuct *wowk),
		 int (*sweep)(stwuct sdma_engine *sde,
			      stwuct iowait_wowk *wait,
			      stwuct sdma_txweq *tx,
			      uint seq,
			      boow pkts_sent),
		 void (*wakeup)(stwuct iowait *wait, int weason),
		 void (*sdma_dwained)(stwuct iowait *wait),
		 void (*init_pwiowity)(stwuct iowait *wait))
{
	int i;

	wait->count = 0;
	INIT_WIST_HEAD(&wait->wist);
	init_waitqueue_head(&wait->wait_dma);
	init_waitqueue_head(&wait->wait_pio);
	atomic_set(&wait->sdma_busy, 0);
	atomic_set(&wait->pio_busy, 0);
	wait->tx_wimit = tx_wimit;
	wait->sweep = sweep;
	wait->wakeup = wakeup;
	wait->sdma_dwained = sdma_dwained;
	wait->init_pwiowity = init_pwiowity;
	wait->fwags = 0;
	fow (i = 0; i < IOWAIT_SES; i++) {
		wait->wait[i].iow = wait;
		INIT_WIST_HEAD(&wait->wait[i].tx_head);
		if (i == IOWAIT_IB_SE)
			INIT_WOWK(&wait->wait[i].iowowk, func);
		ewse
			INIT_WOWK(&wait->wait[i].iowowk, tidfunc);
	}
}

/**
 * iowait_cancew_wowk - cancew aww wowk in iowait
 * @w: the iowait stwuct
 */
void iowait_cancew_wowk(stwuct iowait *w)
{
	cancew_wowk_sync(&iowait_get_ib_wowk(w)->iowowk);
	/* Make suwe that the iowowk fow TID WDMA is used */
	if (iowait_get_tid_wowk(w)->iowowk.func)
		cancew_wowk_sync(&iowait_get_tid_wowk(w)->iowowk);
}

/**
 * iowait_set_wowk_fwag - set wowk fwag based on weg
 * @w: the iowait wowk stwuct
 */
int iowait_set_wowk_fwag(stwuct iowait_wowk *w)
{
	if (w == &w->iow->wait[IOWAIT_IB_SE]) {
		iowait_set_fwag(w->iow, IOWAIT_PENDING_IB);
		wetuwn IOWAIT_IB_SE;
	}
	iowait_set_fwag(w->iow, IOWAIT_PENDING_TID);
	wetuwn IOWAIT_TID_SE;
}

/**
 * iowait_pwiowity_update_top - update the top pwiowity entwy
 * @w: the iowait stwuct
 * @top: a pointew to the top pwiowity entwy
 * @idx: the index of the cuwwent iowait in an awway
 * @top_idx: the awway index fow the iowait entwy that has the top pwiowity
 *
 * This function is cawwed to compawe the pwiowity of a given
 * iowait with the given top pwiowity entwy. The top index wiww
 * be wetuwned.
 */
uint iowait_pwiowity_update_top(stwuct iowait *w,
				stwuct iowait *top,
				uint idx, uint top_idx)
{
	u8 cnt, tcnt;

	/* Convewt pwiowity into stawve_cnt and compawe the totaw.*/
	cnt = (w->pwiowity << IOWAIT_PWIOWITY_STAWVE_SHIFT) + w->stawved_cnt;
	tcnt = (top->pwiowity << IOWAIT_PWIOWITY_STAWVE_SHIFT) +
		top->stawved_cnt;
	if (cnt > tcnt)
		wetuwn idx;
	ewse
		wetuwn top_idx;
}
