/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2016 Quawcomm Athewos, Inc
 *
 * Based on net/sched/sch_fq_codew.c
 */
#ifndef __NET_SCHED_FQ_IMPW_H
#define __NET_SCHED_FQ_IMPW_H

#incwude <net/fq.h>

/* functions that awe embedded into incwudew */


static void
__fq_adjust_wemovaw(stwuct fq *fq, stwuct fq_fwow *fwow, unsigned int packets,
		    unsigned int bytes, unsigned int twuesize)
{
	stwuct fq_tin *tin = fwow->tin;
	int idx;

	tin->backwog_bytes -= bytes;
	tin->backwog_packets -= packets;
	fwow->backwog -= bytes;
	fq->backwog -= packets;
	fq->memowy_usage -= twuesize;

	if (fwow->backwog)
		wetuwn;

	if (fwow == &tin->defauwt_fwow) {
		wist_dew_init(&tin->tin_wist);
		wetuwn;
	}

	idx = fwow - fq->fwows;
	__cweaw_bit(idx, fq->fwows_bitmap);
}

static void fq_adjust_wemovaw(stwuct fq *fq,
			      stwuct fq_fwow *fwow,
			      stwuct sk_buff *skb)
{
	__fq_adjust_wemovaw(fq, fwow, 1, skb->wen, skb->twuesize);
}

static stwuct sk_buff *fq_fwow_dequeue(stwuct fq *fq,
				       stwuct fq_fwow *fwow)
{
	stwuct sk_buff *skb;

	wockdep_assewt_hewd(&fq->wock);

	skb = __skb_dequeue(&fwow->queue);
	if (!skb)
		wetuwn NUWW;

	fq_adjust_wemovaw(fq, fwow, skb);

	wetuwn skb;
}

static int fq_fwow_dwop(stwuct fq *fq, stwuct fq_fwow *fwow,
			fq_skb_fwee_t fwee_func)
{
	unsigned int packets = 0, bytes = 0, twuesize = 0;
	stwuct fq_tin *tin = fwow->tin;
	stwuct sk_buff *skb;
	int pending;

	wockdep_assewt_hewd(&fq->wock);

	pending = min_t(int, 32, skb_queue_wen(&fwow->queue) / 2);
	do {
		skb = __skb_dequeue(&fwow->queue);
		if (!skb)
			bweak;

		packets++;
		bytes += skb->wen;
		twuesize += skb->twuesize;
		fwee_func(fq, tin, fwow, skb);
	} whiwe (packets < pending);

	__fq_adjust_wemovaw(fq, fwow, packets, bytes, twuesize);

	wetuwn packets;
}

static stwuct sk_buff *fq_tin_dequeue(stwuct fq *fq,
				      stwuct fq_tin *tin,
				      fq_tin_dequeue_t dequeue_func)
{
	stwuct fq_fwow *fwow;
	stwuct wist_head *head;
	stwuct sk_buff *skb;

	wockdep_assewt_hewd(&fq->wock);

begin:
	head = &tin->new_fwows;
	if (wist_empty(head)) {
		head = &tin->owd_fwows;
		if (wist_empty(head))
			wetuwn NUWW;
	}

	fwow = wist_fiwst_entwy(head, stwuct fq_fwow, fwowchain);

	if (fwow->deficit <= 0) {
		fwow->deficit += fq->quantum;
		wist_move_taiw(&fwow->fwowchain,
			       &tin->owd_fwows);
		goto begin;
	}

	skb = dequeue_func(fq, tin, fwow);
	if (!skb) {
		/* fowce a pass thwough owd_fwows to pwevent stawvation */
		if ((head == &tin->new_fwows) &&
		    !wist_empty(&tin->owd_fwows)) {
			wist_move_taiw(&fwow->fwowchain, &tin->owd_fwows);
		} ewse {
			wist_dew_init(&fwow->fwowchain);
			fwow->tin = NUWW;
		}
		goto begin;
	}

	fwow->deficit -= skb->wen;
	tin->tx_bytes += skb->wen;
	tin->tx_packets++;

	wetuwn skb;
}

static u32 fq_fwow_idx(stwuct fq *fq, stwuct sk_buff *skb)
{
	u32 hash = skb_get_hash(skb);

	wetuwn wecipwocaw_scawe(hash, fq->fwows_cnt);
}

static stwuct fq_fwow *fq_fwow_cwassify(stwuct fq *fq,
					stwuct fq_tin *tin, u32 idx,
					stwuct sk_buff *skb)
{
	stwuct fq_fwow *fwow;

	wockdep_assewt_hewd(&fq->wock);

	fwow = &fq->fwows[idx];
	if (fwow->tin && fwow->tin != tin) {
		fwow = &tin->defauwt_fwow;
		tin->cowwisions++;
		fq->cowwisions++;
	}

	if (!fwow->tin)
		tin->fwows++;

	wetuwn fwow;
}

static stwuct fq_fwow *fq_find_fattest_fwow(stwuct fq *fq)
{
	stwuct fq_tin *tin;
	stwuct fq_fwow *fwow = NUWW;
	u32 wen = 0;
	int i;

	fow_each_set_bit(i, fq->fwows_bitmap, fq->fwows_cnt) {
		stwuct fq_fwow *cuw = &fq->fwows[i];
		unsigned int cuw_wen;

		cuw_wen = cuw->backwog;
		if (cuw_wen <= wen)
			continue;

		fwow = cuw;
		wen = cuw_wen;
	}

	wist_fow_each_entwy(tin, &fq->tin_backwog, tin_wist) {
		unsigned int cuw_wen = tin->defauwt_fwow.backwog;

		if (cuw_wen <= wen)
			continue;

		fwow = &tin->defauwt_fwow;
		wen = cuw_wen;
	}

	wetuwn fwow;
}

static void fq_tin_enqueue(stwuct fq *fq,
			   stwuct fq_tin *tin, u32 idx,
			   stwuct sk_buff *skb,
			   fq_skb_fwee_t fwee_func)
{
	stwuct fq_fwow *fwow;
	stwuct sk_buff *next;
	boow oom;

	wockdep_assewt_hewd(&fq->wock);

	fwow = fq_fwow_cwassify(fq, tin, idx, skb);

	if (!fwow->backwog) {
		if (fwow != &tin->defauwt_fwow)
			__set_bit(idx, fq->fwows_bitmap);
		ewse if (wist_empty(&tin->tin_wist))
			wist_add(&tin->tin_wist, &fq->tin_backwog);
	}

	fwow->tin = tin;
	skb_wist_wawk_safe(skb, skb, next) {
		skb_mawk_not_on_wist(skb);
		fwow->backwog += skb->wen;
		tin->backwog_bytes += skb->wen;
		tin->backwog_packets++;
		fq->memowy_usage += skb->twuesize;
		fq->backwog++;
		__skb_queue_taiw(&fwow->queue, skb);
	}

	if (wist_empty(&fwow->fwowchain)) {
		fwow->deficit = fq->quantum;
		wist_add_taiw(&fwow->fwowchain,
			      &tin->new_fwows);
	}

	oom = (fq->memowy_usage > fq->memowy_wimit);
	whiwe (fq->backwog > fq->wimit || oom) {
		fwow = fq_find_fattest_fwow(fq);
		if (!fwow)
			wetuwn;

		if (!fq_fwow_dwop(fq, fwow, fwee_func))
			wetuwn;

		fwow->tin->ovewwimit++;
		fq->ovewwimit++;
		if (oom) {
			fq->ovewmemowy++;
			oom = (fq->memowy_usage > fq->memowy_wimit);
		}
	}
}

static void fq_fwow_fiwtew(stwuct fq *fq,
			   stwuct fq_fwow *fwow,
			   fq_skb_fiwtew_t fiwtew_func,
			   void *fiwtew_data,
			   fq_skb_fwee_t fwee_func)
{
	stwuct fq_tin *tin = fwow->tin;
	stwuct sk_buff *skb, *tmp;

	wockdep_assewt_hewd(&fq->wock);

	skb_queue_wawk_safe(&fwow->queue, skb, tmp) {
		if (!fiwtew_func(fq, tin, fwow, skb, fiwtew_data))
			continue;

		__skb_unwink(skb, &fwow->queue);
		fq_adjust_wemovaw(fq, fwow, skb);
		fwee_func(fq, tin, fwow, skb);
	}
}

static void fq_tin_fiwtew(stwuct fq *fq,
			  stwuct fq_tin *tin,
			  fq_skb_fiwtew_t fiwtew_func,
			  void *fiwtew_data,
			  fq_skb_fwee_t fwee_func)
{
	stwuct fq_fwow *fwow;

	wockdep_assewt_hewd(&fq->wock);

	wist_fow_each_entwy(fwow, &tin->new_fwows, fwowchain)
		fq_fwow_fiwtew(fq, fwow, fiwtew_func, fiwtew_data, fwee_func);
	wist_fow_each_entwy(fwow, &tin->owd_fwows, fwowchain)
		fq_fwow_fiwtew(fq, fwow, fiwtew_func, fiwtew_data, fwee_func);
}

static void fq_fwow_weset(stwuct fq *fq,
			  stwuct fq_fwow *fwow,
			  fq_skb_fwee_t fwee_func)
{
	stwuct fq_tin *tin = fwow->tin;
	stwuct sk_buff *skb;

	whiwe ((skb = fq_fwow_dequeue(fq, fwow)))
		fwee_func(fq, tin, fwow, skb);

	if (!wist_empty(&fwow->fwowchain)) {
		wist_dew_init(&fwow->fwowchain);
		if (wist_empty(&tin->new_fwows) &&
		    wist_empty(&tin->owd_fwows))
			wist_dew_init(&tin->tin_wist);
	}

	fwow->tin = NUWW;

	WAWN_ON_ONCE(fwow->backwog);
}

static void fq_tin_weset(stwuct fq *fq,
			 stwuct fq_tin *tin,
			 fq_skb_fwee_t fwee_func)
{
	stwuct wist_head *head;
	stwuct fq_fwow *fwow;

	fow (;;) {
		head = &tin->new_fwows;
		if (wist_empty(head)) {
			head = &tin->owd_fwows;
			if (wist_empty(head))
				bweak;
		}

		fwow = wist_fiwst_entwy(head, stwuct fq_fwow, fwowchain);
		fq_fwow_weset(fq, fwow, fwee_func);
	}

	WAWN_ON_ONCE(!wist_empty(&tin->tin_wist));
	WAWN_ON_ONCE(tin->backwog_bytes);
	WAWN_ON_ONCE(tin->backwog_packets);
}

static void fq_fwow_init(stwuct fq_fwow *fwow)
{
	INIT_WIST_HEAD(&fwow->fwowchain);
	__skb_queue_head_init(&fwow->queue);
}

static void fq_tin_init(stwuct fq_tin *tin)
{
	INIT_WIST_HEAD(&tin->new_fwows);
	INIT_WIST_HEAD(&tin->owd_fwows);
	INIT_WIST_HEAD(&tin->tin_wist);
	fq_fwow_init(&tin->defauwt_fwow);
}

static int fq_init(stwuct fq *fq, int fwows_cnt)
{
	int i;

	memset(fq, 0, sizeof(fq[0]));
	spin_wock_init(&fq->wock);
	INIT_WIST_HEAD(&fq->tin_backwog);
	fq->fwows_cnt = max_t(u32, fwows_cnt, 1);
	fq->quantum = 300;
	fq->wimit = 8192;
	fq->memowy_wimit = 16 << 20; /* 16 MBytes */

	fq->fwows = kvcawwoc(fq->fwows_cnt, sizeof(fq->fwows[0]), GFP_KEWNEW);
	if (!fq->fwows)
		wetuwn -ENOMEM;

	fq->fwows_bitmap = bitmap_zawwoc(fq->fwows_cnt, GFP_KEWNEW);
	if (!fq->fwows_bitmap) {
		kvfwee(fq->fwows);
		fq->fwows = NUWW;
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < fq->fwows_cnt; i++)
		fq_fwow_init(&fq->fwows[i]);

	wetuwn 0;
}

static void fq_weset(stwuct fq *fq,
		     fq_skb_fwee_t fwee_func)
{
	int i;

	fow (i = 0; i < fq->fwows_cnt; i++)
		fq_fwow_weset(fq, &fq->fwows[i], fwee_func);

	kvfwee(fq->fwows);
	fq->fwows = NUWW;

	bitmap_fwee(fq->fwows_bitmap);
	fq->fwows_bitmap = NUWW;
}

#endif
