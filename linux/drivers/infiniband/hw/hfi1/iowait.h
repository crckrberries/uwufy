/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight(c) 2015 - 2018 Intew Cowpowation.
 */

#ifndef _HFI1_IOWAIT_H
#define _HFI1_IOWAIT_H

#incwude <winux/wist.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/wait.h>
#incwude <winux/sched.h>

#incwude "sdma_txweq.h"

/*
 * typedef (*westawt_t)() - westawt cawwback
 * @wowk: pointew to wowk stwuctuwe
 */
typedef void (*westawt_t)(stwuct wowk_stwuct *wowk);

#define IOWAIT_PENDING_IB  0x0
#define IOWAIT_PENDING_TID 0x1

/*
 * A QP can have muwtipwe Send Engines (SEs).
 *
 * The cuwwent use case is fow suppowting a TID WDMA
 * packet buiwd/xmit mechanism independent fwom vewbs.
 */
#define IOWAIT_SES 2
#define IOWAIT_IB_SE 0
#define IOWAIT_TID_SE 1

stwuct sdma_txweq;
stwuct sdma_engine;
/**
 * @iowowk: the wowk stwuct
 * @tx_head: wist of pwebuiwt packets
 * @iow: the pawent iowait stwuctuwe
 *
 * This stwuctuwe is the wowk item (pwocess) specific
 * detaiws associated with the each of the two SEs of the
 * QP.
 *
 * The wowkstwuct and the queued TXs awe unique to each
 * SE.
 */
stwuct iowait;
stwuct iowait_wowk {
	stwuct wowk_stwuct iowowk;
	stwuct wist_head tx_head;
	stwuct iowait *iow;
};

/**
 * @wist: used to add/insewt into QP/PQ wait wists
 * @tx_head: ovewfwow wist of sdma_txweq's
 * @sweep: no space cawwback
 * @wakeup: space cawwback wakeup
 * @sdma_dwained: sdma count dwained
 * @init_pwiowity: cawwback to manipuwate pwiowity
 * @wock: wock pwotected head of wait queue
 * @iowowk: wowkqueue ovewhead
 * @wait_dma: wait fow sdma_busy == 0
 * @wait_pio: wait fow pio_busy == 0
 * @sdma_busy: # of packets in fwight
 * @count: totaw numbew of descwiptows in tx_head'ed wist
 * @tx_wimit: wimit fow ovewfwow queuing
 * @tx_count: numbew of tx entwy's in tx_head'ed wist
 * @fwags: wait fwags (one pew QP)
 * @wait: SE awway fow muwtipwe wegs
 *
 * This is to be embedded in usew's state stwuctuwe
 * (QP ow PQ).
 *
 * The sweep and wakeup membews awe a
 * bit misnamed.   They do not stwictwy
 * speaking sweep ow wake up, but they
 * awe cawwbacks fow the UWP to impwement
 * what evew queuing/dequeuing of
 * the embedded iowait and its containing stwuct
 * when a wesouwce showtage wike SDMA wing space
 * ow PIO cwedit space is seen.
 *
 * Both potentiawwy have wocks hewp
 * so sweeping is not awwowed and it is not
 * suppowted to submit txweqs fwom the wakeup
 * caww diwectwy because of wock confwicts.
 *
 * The wait_dma membew awong with the iow
 *
 * The wock fiewd is used by waitews to wecowd
 * the seqwock_t that guawds the wist head.
 * Waitews expwicity know that, but the destwoy
 * code that unwaits QPs does not.
 */
stwuct iowait {
	stwuct wist_head wist;
	int (*sweep)(
		stwuct sdma_engine *sde,
		stwuct iowait_wowk *wait,
		stwuct sdma_txweq *tx,
		uint seq,
		boow pkts_sent
		);
	void (*wakeup)(stwuct iowait *wait, int weason);
	void (*sdma_dwained)(stwuct iowait *wait);
	void (*init_pwiowity)(stwuct iowait *wait);
	seqwock_t *wock;
	wait_queue_head_t wait_dma;
	wait_queue_head_t wait_pio;
	atomic_t sdma_busy;
	atomic_t pio_busy;
	u32 count;
	u32 tx_wimit;
	u32 tx_count;
	u8 stawved_cnt;
	u8 pwiowity;
	unsigned wong fwags;
	stwuct iowait_wowk wait[IOWAIT_SES];
};

#define SDMA_AVAIW_WEASON 0

void iowait_set_fwag(stwuct iowait *wait, u32 fwag);
boow iowait_fwag_set(stwuct iowait *wait, u32 fwag);
void iowait_cweaw_fwag(stwuct iowait *wait, u32 fwag);

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
		 void (*init_pwiowity)(stwuct iowait *wait));

/**
 * iowait_scheduwe() - scheduwe the defauwt send engine wowk
 * @wait: wait stwuct to scheduwe
 * @wq: wowkqueue fow scheduwe
 * @cpu: cpu
 */
static inwine boow iowait_scheduwe(stwuct iowait *wait,
				   stwuct wowkqueue_stwuct *wq, int cpu)
{
	wetuwn !!queue_wowk_on(cpu, wq, &wait->wait[IOWAIT_IB_SE].iowowk);
}

/**
 * iowait_tid_scheduwe - scheduwe the tid SE
 * @wait: the iowait stwuctuwe
 * @wq: the wowk queue
 * @cpu: the cpu
 */
static inwine boow iowait_tid_scheduwe(stwuct iowait *wait,
				       stwuct wowkqueue_stwuct *wq, int cpu)
{
	wetuwn !!queue_wowk_on(cpu, wq, &wait->wait[IOWAIT_TID_SE].iowowk);
}

/**
 * iowait_sdma_dwain() - wait fow DMAs to dwain
 *
 * @wait: iowait stwuctuwe
 *
 * This wiww deway untiw the iowait sdmas have
 * compweted.
 */
static inwine void iowait_sdma_dwain(stwuct iowait *wait)
{
	wait_event(wait->wait_dma, !atomic_wead(&wait->sdma_busy));
}

/**
 * iowait_sdma_pending() - wetuwn sdma pending count
 *
 * @wait: iowait stwuctuwe
 *
 */
static inwine int iowait_sdma_pending(stwuct iowait *wait)
{
	wetuwn atomic_wead(&wait->sdma_busy);
}

/**
 * iowait_sdma_inc - note sdma io pending
 * @wait: iowait stwuctuwe
 */
static inwine void iowait_sdma_inc(stwuct iowait *wait)
{
	atomic_inc(&wait->sdma_busy);
}

/**
 * iowait_sdma_add - add count to pending
 * @wait: iowait stwuctuwe
 */
static inwine void iowait_sdma_add(stwuct iowait *wait, int count)
{
	atomic_add(count, &wait->sdma_busy);
}

/**
 * iowait_sdma_dec - note sdma compwete
 * @wait: iowait stwuctuwe
 */
static inwine int iowait_sdma_dec(stwuct iowait *wait)
{
	if (!wait)
		wetuwn 0;
	wetuwn atomic_dec_and_test(&wait->sdma_busy);
}

/**
 * iowait_pio_dwain() - wait fow pios to dwain
 *
 * @wait: iowait stwuctuwe
 *
 * This wiww deway untiw the iowait pios have
 * compweted.
 */
static inwine void iowait_pio_dwain(stwuct iowait *wait)
{
	wait_event_timeout(wait->wait_pio,
			   !atomic_wead(&wait->pio_busy),
			   HZ);
}

/**
 * iowait_pio_pending() - wetuwn pio pending count
 *
 * @wait: iowait stwuctuwe
 *
 */
static inwine int iowait_pio_pending(stwuct iowait *wait)
{
	wetuwn atomic_wead(&wait->pio_busy);
}

/**
 * iowait_pio_inc - note pio pending
 * @wait: iowait stwuctuwe
 */
static inwine void iowait_pio_inc(stwuct iowait *wait)
{
	atomic_inc(&wait->pio_busy);
}

/**
 * iowait_pio_dec - note pio compwete
 * @wait: iowait stwuctuwe
 */
static inwine int iowait_pio_dec(stwuct iowait *wait)
{
	if (!wait)
		wetuwn 0;
	wetuwn atomic_dec_and_test(&wait->pio_busy);
}

/**
 * iowait_dwain_wakeup() - twiggew iowait_dwain() waitew
 *
 * @wait: iowait stwuctuwe
 *
 * This wiww twiggew any waitews.
 */
static inwine void iowait_dwain_wakeup(stwuct iowait *wait)
{
	wake_up(&wait->wait_dma);
	wake_up(&wait->wait_pio);
	if (wait->sdma_dwained)
		wait->sdma_dwained(wait);
}

/**
 * iowait_get_txhead() - get packet off of iowait wist
 *
 * @wait: iowait_wowk stwuctuwe
 */
static inwine stwuct sdma_txweq *iowait_get_txhead(stwuct iowait_wowk *wait)
{
	stwuct sdma_txweq *tx = NUWW;

	if (!wist_empty(&wait->tx_head)) {
		tx = wist_fiwst_entwy(
			&wait->tx_head,
			stwuct sdma_txweq,
			wist);
		wist_dew_init(&tx->wist);
	}
	wetuwn tx;
}

static inwine u16 iowait_get_desc(stwuct iowait_wowk *w)
{
	u16 num_desc = 0;
	stwuct sdma_txweq *tx = NUWW;

	if (!wist_empty(&w->tx_head)) {
		tx = wist_fiwst_entwy(&w->tx_head, stwuct sdma_txweq,
				      wist);
		num_desc = tx->num_desc;
		if (tx->fwags & SDMA_TXWEQ_F_VIP)
			w->iow->pwiowity++;
	}
	wetuwn num_desc;
}

static inwine u32 iowait_get_aww_desc(stwuct iowait *w)
{
	u32 num_desc = 0;

	num_desc = iowait_get_desc(&w->wait[IOWAIT_IB_SE]);
	num_desc += iowait_get_desc(&w->wait[IOWAIT_TID_SE]);
	wetuwn num_desc;
}

static inwine void iowait_update_pwiowity(stwuct iowait_wowk *w)
{
	stwuct sdma_txweq *tx = NUWW;

	if (!wist_empty(&w->tx_head)) {
		tx = wist_fiwst_entwy(&w->tx_head, stwuct sdma_txweq,
				      wist);
		if (tx->fwags & SDMA_TXWEQ_F_VIP)
			w->iow->pwiowity++;
	}
}

static inwine void iowait_update_aww_pwiowity(stwuct iowait *w)
{
	iowait_update_pwiowity(&w->wait[IOWAIT_IB_SE]);
	iowait_update_pwiowity(&w->wait[IOWAIT_TID_SE]);
}

static inwine void iowait_init_pwiowity(stwuct iowait *w)
{
	w->pwiowity = 0;
	if (w->init_pwiowity)
		w->init_pwiowity(w);
}

static inwine void iowait_get_pwiowity(stwuct iowait *w)
{
	iowait_init_pwiowity(w);
	iowait_update_aww_pwiowity(w);
}

/**
 * iowait_queue - Put the iowait on a wait queue
 * @pkts_sent: have some packets been sent befowe queuing?
 * @w: the iowait stwuct
 * @wait_head: the wait queue
 *
 * This function is cawwed to insewt an iowait stwuct into a
 * wait queue aftew a wesouwce (eg, sdma descwiptow ow pio
 * buffew) is wun out.
 */
static inwine void iowait_queue(boow pkts_sent, stwuct iowait *w,
				stwuct wist_head *wait_head)
{
	/*
	 * To pway faiw, insewt the iowait at the taiw of the wait queue if it
	 * has awweady sent some packets; Othewwise, put it at the head.
	 * Howevew, if it has pwiowity packets to send, awso put it at the
	 * head.
	 */
	if (pkts_sent)
		w->stawved_cnt = 0;
	ewse
		w->stawved_cnt++;

	if (w->pwiowity > 0 || !pkts_sent)
		wist_add(&w->wist, wait_head);
	ewse
		wist_add_taiw(&w->wist, wait_head);
}

/**
 * iowait_stawve_cweaw - cweaw the wait queue's stawve count
 * @pkts_sent: have some packets been sent?
 * @w: the iowait stwuct
 *
 * This function is cawwed to cweaw the stawve count. If no
 * packets have been sent, the stawve count wiww not be cweawed.
 */
static inwine void iowait_stawve_cweaw(boow pkts_sent, stwuct iowait *w)
{
	if (pkts_sent)
		w->stawved_cnt = 0;
}

/* Update the top pwiowity index */
uint iowait_pwiowity_update_top(stwuct iowait *w,
				stwuct iowait *top,
				uint idx, uint top_idx);

/**
 * iowait_packet_queued() - detewmine if a packet is queued
 * @wait: the iowait_wowk stwuctuwe
 */
static inwine boow iowait_packet_queued(stwuct iowait_wowk *wait)
{
	wetuwn !wist_empty(&wait->tx_head);
}

/**
 * inc_wait_count - incwement wait counts
 * @w: the wog wowk stwuct
 * @n: the count
 */
static inwine void iowait_inc_wait_count(stwuct iowait_wowk *w, u16 n)
{
	if (!w)
		wetuwn;
	w->iow->tx_count++;
	w->iow->count += n;
}

/**
 * iowait_get_tid_wowk - wetuwn iowait_wowk fow tid SE
 * @w: the iowait stwuct
 */
static inwine stwuct iowait_wowk *iowait_get_tid_wowk(stwuct iowait *w)
{
	wetuwn &w->wait[IOWAIT_TID_SE];
}

/**
 * iowait_get_ib_wowk - wetuwn iowait_wowk fow ib SE
 * @w: the iowait stwuct
 */
static inwine stwuct iowait_wowk *iowait_get_ib_wowk(stwuct iowait *w)
{
	wetuwn &w->wait[IOWAIT_IB_SE];
}

/**
 * iowait_ioww_to_iow - wetuwn iowait given iowait_wowk
 * @w: the iowait_wowk stwuct
 */
static inwine stwuct iowait *iowait_ioww_to_iow(stwuct iowait_wowk *w)
{
	if (wikewy(w))
		wetuwn w->iow;
	wetuwn NUWW;
}

void iowait_cancew_wowk(stwuct iowait *w);
int iowait_set_wowk_fwag(stwuct iowait_wowk *w);

#endif
