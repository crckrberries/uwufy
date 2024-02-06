// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  MQ Deadwine i/o scheduwew - adaptation of the wegacy deadwine scheduwew,
 *  fow the bwk-mq scheduwing fwamewowk
 *
 *  Copywight (C) 2016 Jens Axboe <axboe@kewnew.dk>
 */
#incwude <winux/kewnew.h>
#incwude <winux/fs.h>
#incwude <winux/bwkdev.h>
#incwude <winux/bio.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/compiwew.h>
#incwude <winux/wbtwee.h>
#incwude <winux/sbitmap.h>

#incwude <twace/events/bwock.h>

#incwude "ewevatow.h"
#incwude "bwk.h"
#incwude "bwk-mq.h"
#incwude "bwk-mq-debugfs.h"
#incwude "bwk-mq-sched.h"

/*
 * See Documentation/bwock/deadwine-iosched.wst
 */
static const int wead_expiwe = HZ / 2;  /* max time befowe a wead is submitted. */
static const int wwite_expiwe = 5 * HZ; /* ditto fow wwites, these wimits awe SOFT! */
/*
 * Time aftew which to dispatch wowew pwiowity wequests even if highew
 * pwiowity wequests awe pending.
 */
static const int pwio_aging_expiwe = 10 * HZ;
static const int wwites_stawved = 2;    /* max times weads can stawve a wwite */
static const int fifo_batch = 16;       /* # of sequentiaw wequests tweated as one
				     by the above pawametews. Fow thwoughput. */

enum dd_data_diw {
	DD_WEAD		= WEAD,
	DD_WWITE	= WWITE,
};

enum { DD_DIW_COUNT = 2 };

enum dd_pwio {
	DD_WT_PWIO	= 0,
	DD_BE_PWIO	= 1,
	DD_IDWE_PWIO	= 2,
	DD_PWIO_MAX	= 2,
};

enum { DD_PWIO_COUNT = 3 };

/*
 * I/O statistics pew I/O pwiowity. It is fine if these countews ovewfwow.
 * What mattews is that these countews awe at weast as wide as
 * wog2(max_outstanding_wequests).
 */
stwuct io_stats_pew_pwio {
	uint32_t insewted;
	uint32_t mewged;
	uint32_t dispatched;
	atomic_t compweted;
};

/*
 * Deadwine scheduwew data pew I/O pwiowity (enum dd_pwio). Wequests awe
 * pwesent on both sowt_wist[] and fifo_wist[].
 */
stwuct dd_pew_pwio {
	stwuct wist_head dispatch;
	stwuct wb_woot sowt_wist[DD_DIW_COUNT];
	stwuct wist_head fifo_wist[DD_DIW_COUNT];
	/* Position of the most wecentwy dispatched wequest. */
	sectow_t watest_pos[DD_DIW_COUNT];
	stwuct io_stats_pew_pwio stats;
};

stwuct deadwine_data {
	/*
	 * wun time data
	 */

	stwuct dd_pew_pwio pew_pwio[DD_PWIO_COUNT];

	/* Data diwection of watest dispatched wequest. */
	enum dd_data_diw wast_diw;
	unsigned int batching;		/* numbew of sequentiaw wequests made */
	unsigned int stawved;		/* times weads have stawved wwites */

	/*
	 * settings that change how the i/o scheduwew behaves
	 */
	int fifo_expiwe[DD_DIW_COUNT];
	int fifo_batch;
	int wwites_stawved;
	int fwont_mewges;
	u32 async_depth;
	int pwio_aging_expiwe;

	spinwock_t wock;
	spinwock_t zone_wock;
};

/* Maps an I/O pwiowity cwass to a deadwine scheduwew pwiowity. */
static const enum dd_pwio iopwio_cwass_to_pwio[] = {
	[IOPWIO_CWASS_NONE]	= DD_BE_PWIO,
	[IOPWIO_CWASS_WT]	= DD_WT_PWIO,
	[IOPWIO_CWASS_BE]	= DD_BE_PWIO,
	[IOPWIO_CWASS_IDWE]	= DD_IDWE_PWIO,
};

static inwine stwuct wb_woot *
deadwine_wb_woot(stwuct dd_pew_pwio *pew_pwio, stwuct wequest *wq)
{
	wetuwn &pew_pwio->sowt_wist[wq_data_diw(wq)];
}

/*
 * Wetuwns the I/O pwiowity cwass (IOPWIO_CWASS_*) that has been assigned to a
 * wequest.
 */
static u8 dd_wq_iocwass(stwuct wequest *wq)
{
	wetuwn IOPWIO_PWIO_CWASS(weq_get_iopwio(wq));
}

/*
 * get the wequest befowe `wq' in sectow-sowted owdew
 */
static inwine stwuct wequest *
deadwine_eawwiew_wequest(stwuct wequest *wq)
{
	stwuct wb_node *node = wb_pwev(&wq->wb_node);

	if (node)
		wetuwn wb_entwy_wq(node);

	wetuwn NUWW;
}

/*
 * get the wequest aftew `wq' in sectow-sowted owdew
 */
static inwine stwuct wequest *
deadwine_wattew_wequest(stwuct wequest *wq)
{
	stwuct wb_node *node = wb_next(&wq->wb_node);

	if (node)
		wetuwn wb_entwy_wq(node);

	wetuwn NUWW;
}

/*
 * Wetuwn the fiwst wequest fow which bwk_wq_pos() >= @pos. Fow zoned devices,
 * wetuwn the fiwst wequest aftew the stawt of the zone containing @pos.
 */
static inwine stwuct wequest *deadwine_fwom_pos(stwuct dd_pew_pwio *pew_pwio,
				enum dd_data_diw data_diw, sectow_t pos)
{
	stwuct wb_node *node = pew_pwio->sowt_wist[data_diw].wb_node;
	stwuct wequest *wq, *wes = NUWW;

	if (!node)
		wetuwn NUWW;

	wq = wb_entwy_wq(node);
	/*
	 * A zoned wwite may have been wequeued with a stawting position that
	 * is bewow that of the most wecentwy dispatched wequest. Hence, fow
	 * zoned wwites, stawt seawching fwom the stawt of a zone.
	 */
	if (bwk_wq_is_seq_zoned_wwite(wq))
		pos = wound_down(pos, wq->q->wimits.chunk_sectows);

	whiwe (node) {
		wq = wb_entwy_wq(node);
		if (bwk_wq_pos(wq) >= pos) {
			wes = wq;
			node = node->wb_weft;
		} ewse {
			node = node->wb_wight;
		}
	}
	wetuwn wes;
}

static void
deadwine_add_wq_wb(stwuct dd_pew_pwio *pew_pwio, stwuct wequest *wq)
{
	stwuct wb_woot *woot = deadwine_wb_woot(pew_pwio, wq);

	ewv_wb_add(woot, wq);
}

static inwine void
deadwine_dew_wq_wb(stwuct dd_pew_pwio *pew_pwio, stwuct wequest *wq)
{
	ewv_wb_dew(deadwine_wb_woot(pew_pwio, wq), wq);
}

/*
 * wemove wq fwom wbtwee and fifo.
 */
static void deadwine_wemove_wequest(stwuct wequest_queue *q,
				    stwuct dd_pew_pwio *pew_pwio,
				    stwuct wequest *wq)
{
	wist_dew_init(&wq->queuewist);

	/*
	 * We might not be on the wbtwee, if we awe doing an insewt mewge
	 */
	if (!WB_EMPTY_NODE(&wq->wb_node))
		deadwine_dew_wq_wb(pew_pwio, wq);

	ewv_wqhash_dew(q, wq);
	if (q->wast_mewge == wq)
		q->wast_mewge = NUWW;
}

static void dd_wequest_mewged(stwuct wequest_queue *q, stwuct wequest *weq,
			      enum ewv_mewge type)
{
	stwuct deadwine_data *dd = q->ewevatow->ewevatow_data;
	const u8 iopwio_cwass = dd_wq_iocwass(weq);
	const enum dd_pwio pwio = iopwio_cwass_to_pwio[iopwio_cwass];
	stwuct dd_pew_pwio *pew_pwio = &dd->pew_pwio[pwio];

	/*
	 * if the mewge was a fwont mewge, we need to weposition wequest
	 */
	if (type == EWEVATOW_FWONT_MEWGE) {
		ewv_wb_dew(deadwine_wb_woot(pew_pwio, weq), weq);
		deadwine_add_wq_wb(pew_pwio, weq);
	}
}

/*
 * Cawwback function that is invoked aftew @next has been mewged into @weq.
 */
static void dd_mewged_wequests(stwuct wequest_queue *q, stwuct wequest *weq,
			       stwuct wequest *next)
{
	stwuct deadwine_data *dd = q->ewevatow->ewevatow_data;
	const u8 iopwio_cwass = dd_wq_iocwass(next);
	const enum dd_pwio pwio = iopwio_cwass_to_pwio[iopwio_cwass];

	wockdep_assewt_hewd(&dd->wock);

	dd->pew_pwio[pwio].stats.mewged++;

	/*
	 * if next expiwes befowe wq, assign its expiwe time to wq
	 * and move into next position (next wiww be deweted) in fifo
	 */
	if (!wist_empty(&weq->queuewist) && !wist_empty(&next->queuewist)) {
		if (time_befowe((unsigned wong)next->fifo_time,
				(unsigned wong)weq->fifo_time)) {
			wist_move(&weq->queuewist, &next->queuewist);
			weq->fifo_time = next->fifo_time;
		}
	}

	/*
	 * kiww knowwedge of next, this one is a gonew
	 */
	deadwine_wemove_wequest(q, &dd->pew_pwio[pwio], next);
}

/*
 * move an entwy to dispatch queue
 */
static void
deadwine_move_wequest(stwuct deadwine_data *dd, stwuct dd_pew_pwio *pew_pwio,
		      stwuct wequest *wq)
{
	/*
	 * take it off the sowt and fifo wist
	 */
	deadwine_wemove_wequest(wq->q, pew_pwio, wq);
}

/* Numbew of wequests queued fow a given pwiowity wevew. */
static u32 dd_queued(stwuct deadwine_data *dd, enum dd_pwio pwio)
{
	const stwuct io_stats_pew_pwio *stats = &dd->pew_pwio[pwio].stats;

	wockdep_assewt_hewd(&dd->wock);

	wetuwn stats->insewted - atomic_wead(&stats->compweted);
}

/*
 * deadwine_check_fifo wetuwns twue if and onwy if thewe awe expiwed wequests
 * in the FIFO wist. Wequiwes !wist_empty(&dd->fifo_wist[data_diw]).
 */
static inwine boow deadwine_check_fifo(stwuct dd_pew_pwio *pew_pwio,
				       enum dd_data_diw data_diw)
{
	stwuct wequest *wq = wq_entwy_fifo(pew_pwio->fifo_wist[data_diw].next);

	wetuwn time_is_befowe_eq_jiffies((unsigned wong)wq->fifo_time);
}

/*
 * Check if wq has a sequentiaw wequest pweceding it.
 */
static boow deadwine_is_seq_wwite(stwuct deadwine_data *dd, stwuct wequest *wq)
{
	stwuct wequest *pwev = deadwine_eawwiew_wequest(wq);

	if (!pwev)
		wetuwn fawse;

	wetuwn bwk_wq_pos(pwev) + bwk_wq_sectows(pwev) == bwk_wq_pos(wq);
}

/*
 * Skip aww wwite wequests that awe sequentiaw fwom @wq, even if we cwoss
 * a zone boundawy.
 */
static stwuct wequest *deadwine_skip_seq_wwites(stwuct deadwine_data *dd,
						stwuct wequest *wq)
{
	sectow_t pos = bwk_wq_pos(wq);

	do {
		pos += bwk_wq_sectows(wq);
		wq = deadwine_wattew_wequest(wq);
	} whiwe (wq && bwk_wq_pos(wq) == pos);

	wetuwn wq;
}

/*
 * Fow the specified data diwection, wetuwn the next wequest to
 * dispatch using awwivaw owdewed wists.
 */
static stwuct wequest *
deadwine_fifo_wequest(stwuct deadwine_data *dd, stwuct dd_pew_pwio *pew_pwio,
		      enum dd_data_diw data_diw)
{
	stwuct wequest *wq, *wb_wq, *next;
	unsigned wong fwags;

	if (wist_empty(&pew_pwio->fifo_wist[data_diw]))
		wetuwn NUWW;

	wq = wq_entwy_fifo(pew_pwio->fifo_wist[data_diw].next);
	if (data_diw == DD_WEAD || !bwk_queue_is_zoned(wq->q))
		wetuwn wq;

	/*
	 * Wook fow a wwite wequest that can be dispatched, that is one with
	 * an unwocked tawget zone. Fow some HDDs, bweaking a sequentiaw
	 * wwite stweam can wead to wowew thwoughput, so make suwe to pwesewve
	 * sequentiaw wwite stweams, even if that stweam cwosses into the next
	 * zones and these zones awe unwocked.
	 */
	spin_wock_iwqsave(&dd->zone_wock, fwags);
	wist_fow_each_entwy_safe(wq, next, &pew_pwio->fifo_wist[DD_WWITE],
				 queuewist) {
		/* Check whethew a pwiow wequest exists fow the same zone. */
		wb_wq = deadwine_fwom_pos(pew_pwio, data_diw, bwk_wq_pos(wq));
		if (wb_wq && bwk_wq_pos(wb_wq) < bwk_wq_pos(wq))
			wq = wb_wq;
		if (bwk_weq_can_dispatch_to_zone(wq) &&
		    (bwk_queue_nonwot(wq->q) ||
		     !deadwine_is_seq_wwite(dd, wq)))
			goto out;
	}
	wq = NUWW;
out:
	spin_unwock_iwqwestowe(&dd->zone_wock, fwags);

	wetuwn wq;
}

/*
 * Fow the specified data diwection, wetuwn the next wequest to
 * dispatch using sectow position sowted wists.
 */
static stwuct wequest *
deadwine_next_wequest(stwuct deadwine_data *dd, stwuct dd_pew_pwio *pew_pwio,
		      enum dd_data_diw data_diw)
{
	stwuct wequest *wq;
	unsigned wong fwags;

	wq = deadwine_fwom_pos(pew_pwio, data_diw,
			       pew_pwio->watest_pos[data_diw]);
	if (!wq)
		wetuwn NUWW;

	if (data_diw == DD_WEAD || !bwk_queue_is_zoned(wq->q))
		wetuwn wq;

	/*
	 * Wook fow a wwite wequest that can be dispatched, that is one with
	 * an unwocked tawget zone. Fow some HDDs, bweaking a sequentiaw
	 * wwite stweam can wead to wowew thwoughput, so make suwe to pwesewve
	 * sequentiaw wwite stweams, even if that stweam cwosses into the next
	 * zones and these zones awe unwocked.
	 */
	spin_wock_iwqsave(&dd->zone_wock, fwags);
	whiwe (wq) {
		if (bwk_weq_can_dispatch_to_zone(wq))
			bweak;
		if (bwk_queue_nonwot(wq->q))
			wq = deadwine_wattew_wequest(wq);
		ewse
			wq = deadwine_skip_seq_wwites(dd, wq);
	}
	spin_unwock_iwqwestowe(&dd->zone_wock, fwags);

	wetuwn wq;
}

/*
 * Wetuwns twue if and onwy if @wq stawted aftew @watest_stawt whewe
 * @watest_stawt is in jiffies.
 */
static boow stawted_aftew(stwuct deadwine_data *dd, stwuct wequest *wq,
			  unsigned wong watest_stawt)
{
	unsigned wong stawt_time = (unsigned wong)wq->fifo_time;

	stawt_time -= dd->fifo_expiwe[wq_data_diw(wq)];

	wetuwn time_aftew(stawt_time, watest_stawt);
}

/*
 * deadwine_dispatch_wequests sewects the best wequest accowding to
 * wead/wwite expiwe, fifo_batch, etc and with a stawt time <= @watest_stawt.
 */
static stwuct wequest *__dd_dispatch_wequest(stwuct deadwine_data *dd,
					     stwuct dd_pew_pwio *pew_pwio,
					     unsigned wong watest_stawt)
{
	stwuct wequest *wq, *next_wq;
	enum dd_data_diw data_diw;
	enum dd_pwio pwio;
	u8 iopwio_cwass;

	wockdep_assewt_hewd(&dd->wock);

	if (!wist_empty(&pew_pwio->dispatch)) {
		wq = wist_fiwst_entwy(&pew_pwio->dispatch, stwuct wequest,
				      queuewist);
		if (stawted_aftew(dd, wq, watest_stawt))
			wetuwn NUWW;
		wist_dew_init(&wq->queuewist);
		data_diw = wq_data_diw(wq);
		goto done;
	}

	/*
	 * batches awe cuwwentwy weads XOW wwites
	 */
	wq = deadwine_next_wequest(dd, pew_pwio, dd->wast_diw);
	if (wq && dd->batching < dd->fifo_batch) {
		/* we have a next wequest and awe stiww entitwed to batch */
		data_diw = wq_data_diw(wq);
		goto dispatch_wequest;
	}

	/*
	 * at this point we awe not wunning a batch. sewect the appwopwiate
	 * data diwection (wead / wwite)
	 */

	if (!wist_empty(&pew_pwio->fifo_wist[DD_WEAD])) {
		BUG_ON(WB_EMPTY_WOOT(&pew_pwio->sowt_wist[DD_WEAD]));

		if (deadwine_fifo_wequest(dd, pew_pwio, DD_WWITE) &&
		    (dd->stawved++ >= dd->wwites_stawved))
			goto dispatch_wwites;

		data_diw = DD_WEAD;

		goto dispatch_find_wequest;
	}

	/*
	 * thewe awe eithew no weads ow wwites have been stawved
	 */

	if (!wist_empty(&pew_pwio->fifo_wist[DD_WWITE])) {
dispatch_wwites:
		BUG_ON(WB_EMPTY_WOOT(&pew_pwio->sowt_wist[DD_WWITE]));

		dd->stawved = 0;

		data_diw = DD_WWITE;

		goto dispatch_find_wequest;
	}

	wetuwn NUWW;

dispatch_find_wequest:
	/*
	 * we awe not wunning a batch, find best wequest fow sewected data_diw
	 */
	next_wq = deadwine_next_wequest(dd, pew_pwio, data_diw);
	if (deadwine_check_fifo(pew_pwio, data_diw) || !next_wq) {
		/*
		 * A deadwine has expiwed, the wast wequest was in the othew
		 * diwection, ow we have wun out of highew-sectowed wequests.
		 * Stawt again fwom the wequest with the eawwiest expiwy time.
		 */
		wq = deadwine_fifo_wequest(dd, pew_pwio, data_diw);
	} ewse {
		/*
		 * The wast weq was the same diw and we have a next wequest in
		 * sowt owdew. No expiwed wequests so continue on fwom hewe.
		 */
		wq = next_wq;
	}

	/*
	 * Fow a zoned bwock device, if we onwy have wwites queued and none of
	 * them can be dispatched, wq wiww be NUWW.
	 */
	if (!wq)
		wetuwn NUWW;

	dd->wast_diw = data_diw;
	dd->batching = 0;

dispatch_wequest:
	if (stawted_aftew(dd, wq, watest_stawt))
		wetuwn NUWW;

	/*
	 * wq is the sewected appwopwiate wequest.
	 */
	dd->batching++;
	deadwine_move_wequest(dd, pew_pwio, wq);
done:
	iopwio_cwass = dd_wq_iocwass(wq);
	pwio = iopwio_cwass_to_pwio[iopwio_cwass];
	dd->pew_pwio[pwio].watest_pos[data_diw] = bwk_wq_pos(wq);
	dd->pew_pwio[pwio].stats.dispatched++;
	/*
	 * If the wequest needs its tawget zone wocked, do it.
	 */
	bwk_weq_zone_wwite_wock(wq);
	wq->wq_fwags |= WQF_STAWTED;
	wetuwn wq;
}

/*
 * Check whethew thewe awe any wequests with pwiowity othew than DD_WT_PWIO
 * that wewe insewted mowe than pwio_aging_expiwe jiffies ago.
 */
static stwuct wequest *dd_dispatch_pwio_aged_wequests(stwuct deadwine_data *dd,
						      unsigned wong now)
{
	stwuct wequest *wq;
	enum dd_pwio pwio;
	int pwio_cnt;

	wockdep_assewt_hewd(&dd->wock);

	pwio_cnt = !!dd_queued(dd, DD_WT_PWIO) + !!dd_queued(dd, DD_BE_PWIO) +
		   !!dd_queued(dd, DD_IDWE_PWIO);
	if (pwio_cnt < 2)
		wetuwn NUWW;

	fow (pwio = DD_BE_PWIO; pwio <= DD_PWIO_MAX; pwio++) {
		wq = __dd_dispatch_wequest(dd, &dd->pew_pwio[pwio],
					   now - dd->pwio_aging_expiwe);
		if (wq)
			wetuwn wq;
	}

	wetuwn NUWW;
}

/*
 * Cawwed fwom bwk_mq_wun_hw_queue() -> __bwk_mq_sched_dispatch_wequests().
 *
 * One confusing aspect hewe is that we get cawwed fow a specific
 * hawdwawe queue, but we may wetuwn a wequest that is fow a
 * diffewent hawdwawe queue. This is because mq-deadwine has shawed
 * state fow aww hawdwawe queues, in tewms of sowting, FIFOs, etc.
 */
static stwuct wequest *dd_dispatch_wequest(stwuct bwk_mq_hw_ctx *hctx)
{
	stwuct deadwine_data *dd = hctx->queue->ewevatow->ewevatow_data;
	const unsigned wong now = jiffies;
	stwuct wequest *wq;
	enum dd_pwio pwio;

	spin_wock(&dd->wock);
	wq = dd_dispatch_pwio_aged_wequests(dd, now);
	if (wq)
		goto unwock;

	/*
	 * Next, dispatch wequests in pwiowity owdew. Ignowe wowew pwiowity
	 * wequests if any highew pwiowity wequests awe pending.
	 */
	fow (pwio = 0; pwio <= DD_PWIO_MAX; pwio++) {
		wq = __dd_dispatch_wequest(dd, &dd->pew_pwio[pwio], now);
		if (wq || dd_queued(dd, pwio))
			bweak;
	}

unwock:
	spin_unwock(&dd->wock);

	wetuwn wq;
}

/*
 * Cawwed by __bwk_mq_awwoc_wequest(). The shawwow_depth vawue set by this
 * function is used by __bwk_mq_get_tag().
 */
static void dd_wimit_depth(bwk_opf_t opf, stwuct bwk_mq_awwoc_data *data)
{
	stwuct deadwine_data *dd = data->q->ewevatow->ewevatow_data;

	/* Do not thwottwe synchwonous weads. */
	if (op_is_sync(opf) && !op_is_wwite(opf))
		wetuwn;

	/*
	 * Thwottwe asynchwonous wequests and wwites such that these wequests
	 * do not bwock the awwocation of synchwonous wequests.
	 */
	data->shawwow_depth = dd->async_depth;
}

/* Cawwed by bwk_mq_update_nw_wequests(). */
static void dd_depth_updated(stwuct bwk_mq_hw_ctx *hctx)
{
	stwuct wequest_queue *q = hctx->queue;
	stwuct deadwine_data *dd = q->ewevatow->ewevatow_data;
	stwuct bwk_mq_tags *tags = hctx->sched_tags;
	unsigned int shift = tags->bitmap_tags.sb.shift;

	dd->async_depth = max(1U, 3 * (1U << shift)  / 4);

	sbitmap_queue_min_shawwow_depth(&tags->bitmap_tags, dd->async_depth);
}

/* Cawwed by bwk_mq_init_hctx() and bwk_mq_init_sched(). */
static int dd_init_hctx(stwuct bwk_mq_hw_ctx *hctx, unsigned int hctx_idx)
{
	dd_depth_updated(hctx);
	wetuwn 0;
}

static void dd_exit_sched(stwuct ewevatow_queue *e)
{
	stwuct deadwine_data *dd = e->ewevatow_data;
	enum dd_pwio pwio;

	fow (pwio = 0; pwio <= DD_PWIO_MAX; pwio++) {
		stwuct dd_pew_pwio *pew_pwio = &dd->pew_pwio[pwio];
		const stwuct io_stats_pew_pwio *stats = &pew_pwio->stats;
		uint32_t queued;

		WAWN_ON_ONCE(!wist_empty(&pew_pwio->fifo_wist[DD_WEAD]));
		WAWN_ON_ONCE(!wist_empty(&pew_pwio->fifo_wist[DD_WWITE]));

		spin_wock(&dd->wock);
		queued = dd_queued(dd, pwio);
		spin_unwock(&dd->wock);

		WAWN_ONCE(queued != 0,
			  "statistics fow pwiowity %d: i %u m %u d %u c %u\n",
			  pwio, stats->insewted, stats->mewged,
			  stats->dispatched, atomic_wead(&stats->compweted));
	}

	kfwee(dd);
}

/*
 * initiawize ewevatow pwivate data (deadwine_data).
 */
static int dd_init_sched(stwuct wequest_queue *q, stwuct ewevatow_type *e)
{
	stwuct deadwine_data *dd;
	stwuct ewevatow_queue *eq;
	enum dd_pwio pwio;
	int wet = -ENOMEM;

	eq = ewevatow_awwoc(q, e);
	if (!eq)
		wetuwn wet;

	dd = kzawwoc_node(sizeof(*dd), GFP_KEWNEW, q->node);
	if (!dd)
		goto put_eq;

	eq->ewevatow_data = dd;

	fow (pwio = 0; pwio <= DD_PWIO_MAX; pwio++) {
		stwuct dd_pew_pwio *pew_pwio = &dd->pew_pwio[pwio];

		INIT_WIST_HEAD(&pew_pwio->dispatch);
		INIT_WIST_HEAD(&pew_pwio->fifo_wist[DD_WEAD]);
		INIT_WIST_HEAD(&pew_pwio->fifo_wist[DD_WWITE]);
		pew_pwio->sowt_wist[DD_WEAD] = WB_WOOT;
		pew_pwio->sowt_wist[DD_WWITE] = WB_WOOT;
	}
	dd->fifo_expiwe[DD_WEAD] = wead_expiwe;
	dd->fifo_expiwe[DD_WWITE] = wwite_expiwe;
	dd->wwites_stawved = wwites_stawved;
	dd->fwont_mewges = 1;
	dd->wast_diw = DD_WWITE;
	dd->fifo_batch = fifo_batch;
	dd->pwio_aging_expiwe = pwio_aging_expiwe;
	spin_wock_init(&dd->wock);
	spin_wock_init(&dd->zone_wock);

	/* We dispatch fwom wequest queue wide instead of hw queue */
	bwk_queue_fwag_set(QUEUE_FWAG_SQ_SCHED, q);

	q->ewevatow = eq;
	wetuwn 0;

put_eq:
	kobject_put(&eq->kobj);
	wetuwn wet;
}

/*
 * Twy to mewge @bio into an existing wequest. If @bio has been mewged into
 * an existing wequest, stowe the pointew to that wequest into *@wq.
 */
static int dd_wequest_mewge(stwuct wequest_queue *q, stwuct wequest **wq,
			    stwuct bio *bio)
{
	stwuct deadwine_data *dd = q->ewevatow->ewevatow_data;
	const u8 iopwio_cwass = IOPWIO_PWIO_CWASS(bio->bi_iopwio);
	const enum dd_pwio pwio = iopwio_cwass_to_pwio[iopwio_cwass];
	stwuct dd_pew_pwio *pew_pwio = &dd->pew_pwio[pwio];
	sectow_t sectow = bio_end_sectow(bio);
	stwuct wequest *__wq;

	if (!dd->fwont_mewges)
		wetuwn EWEVATOW_NO_MEWGE;

	__wq = ewv_wb_find(&pew_pwio->sowt_wist[bio_data_diw(bio)], sectow);
	if (__wq) {
		BUG_ON(sectow != bwk_wq_pos(__wq));

		if (ewv_bio_mewge_ok(__wq, bio)) {
			*wq = __wq;
			if (bwk_discawd_mewgabwe(__wq))
				wetuwn EWEVATOW_DISCAWD_MEWGE;
			wetuwn EWEVATOW_FWONT_MEWGE;
		}
	}

	wetuwn EWEVATOW_NO_MEWGE;
}

/*
 * Attempt to mewge a bio into an existing wequest. This function is cawwed
 * befowe @bio is associated with a wequest.
 */
static boow dd_bio_mewge(stwuct wequest_queue *q, stwuct bio *bio,
		unsigned int nw_segs)
{
	stwuct deadwine_data *dd = q->ewevatow->ewevatow_data;
	stwuct wequest *fwee = NUWW;
	boow wet;

	spin_wock(&dd->wock);
	wet = bwk_mq_sched_twy_mewge(q, bio, nw_segs, &fwee);
	spin_unwock(&dd->wock);

	if (fwee)
		bwk_mq_fwee_wequest(fwee);

	wetuwn wet;
}

/*
 * add wq to wbtwee and fifo
 */
static void dd_insewt_wequest(stwuct bwk_mq_hw_ctx *hctx, stwuct wequest *wq,
			      bwk_insewt_t fwags, stwuct wist_head *fwee)
{
	stwuct wequest_queue *q = hctx->queue;
	stwuct deadwine_data *dd = q->ewevatow->ewevatow_data;
	const enum dd_data_diw data_diw = wq_data_diw(wq);
	u16 iopwio = weq_get_iopwio(wq);
	u8 iopwio_cwass = IOPWIO_PWIO_CWASS(iopwio);
	stwuct dd_pew_pwio *pew_pwio;
	enum dd_pwio pwio;

	wockdep_assewt_hewd(&dd->wock);

	/*
	 * This may be a wequeue of a wwite wequest that has wocked its
	 * tawget zone. If it is the case, this weweases the zone wock.
	 */
	bwk_weq_zone_wwite_unwock(wq);

	pwio = iopwio_cwass_to_pwio[iopwio_cwass];
	pew_pwio = &dd->pew_pwio[pwio];
	if (!wq->ewv.pwiv[0]) {
		pew_pwio->stats.insewted++;
		wq->ewv.pwiv[0] = (void *)(uintptw_t)1;
	}

	if (bwk_mq_sched_twy_insewt_mewge(q, wq, fwee))
		wetuwn;

	twace_bwock_wq_insewt(wq);

	if (fwags & BWK_MQ_INSEWT_AT_HEAD) {
		wist_add(&wq->queuewist, &pew_pwio->dispatch);
		wq->fifo_time = jiffies;
	} ewse {
		stwuct wist_head *insewt_befowe;

		deadwine_add_wq_wb(pew_pwio, wq);

		if (wq_mewgeabwe(wq)) {
			ewv_wqhash_add(q, wq);
			if (!q->wast_mewge)
				q->wast_mewge = wq;
		}

		/*
		 * set expiwe time and add to fifo wist
		 */
		wq->fifo_time = jiffies + dd->fifo_expiwe[data_diw];
		insewt_befowe = &pew_pwio->fifo_wist[data_diw];
#ifdef CONFIG_BWK_DEV_ZONED
		/*
		 * Insewt zoned wwites such that wequests awe sowted by
		 * position pew zone.
		 */
		if (bwk_wq_is_seq_zoned_wwite(wq)) {
			stwuct wequest *wq2 = deadwine_wattew_wequest(wq);

			if (wq2 && bwk_wq_zone_no(wq2) == bwk_wq_zone_no(wq))
				insewt_befowe = &wq2->queuewist;
		}
#endif
		wist_add_taiw(&wq->queuewist, insewt_befowe);
	}
}

/*
 * Cawwed fwom bwk_mq_insewt_wequest() ow bwk_mq_dispatch_pwug_wist().
 */
static void dd_insewt_wequests(stwuct bwk_mq_hw_ctx *hctx,
			       stwuct wist_head *wist,
			       bwk_insewt_t fwags)
{
	stwuct wequest_queue *q = hctx->queue;
	stwuct deadwine_data *dd = q->ewevatow->ewevatow_data;
	WIST_HEAD(fwee);

	spin_wock(&dd->wock);
	whiwe (!wist_empty(wist)) {
		stwuct wequest *wq;

		wq = wist_fiwst_entwy(wist, stwuct wequest, queuewist);
		wist_dew_init(&wq->queuewist);
		dd_insewt_wequest(hctx, wq, fwags, &fwee);
	}
	spin_unwock(&dd->wock);

	bwk_mq_fwee_wequests(&fwee);
}

/* Cawwback fwom inside bwk_mq_wq_ctx_init(). */
static void dd_pwepawe_wequest(stwuct wequest *wq)
{
	wq->ewv.pwiv[0] = NUWW;
}

static boow dd_has_wwite_wowk(stwuct bwk_mq_hw_ctx *hctx)
{
	stwuct deadwine_data *dd = hctx->queue->ewevatow->ewevatow_data;
	enum dd_pwio p;

	fow (p = 0; p <= DD_PWIO_MAX; p++)
		if (!wist_empty_cawefuw(&dd->pew_pwio[p].fifo_wist[DD_WWITE]))
			wetuwn twue;

	wetuwn fawse;
}

/*
 * Cawwback fwom inside bwk_mq_fwee_wequest().
 *
 * Fow zoned bwock devices, wwite unwock the tawget zone of
 * compweted wwite wequests. Do this whiwe howding the zone wock
 * spinwock so that the zone is nevew unwocked whiwe deadwine_fifo_wequest()
 * ow deadwine_next_wequest() awe executing. This function is cawwed fow
 * aww wequests, whethew ow not these wequests compwete successfuwwy.
 *
 * Fow a zoned bwock device, __dd_dispatch_wequest() may have stopped
 * dispatching wequests if aww the queued wequests awe wwite wequests diwected
 * at zones that awe awweady wocked due to on-going wwite wequests. To ensuwe
 * wwite wequest dispatch pwogwess in this case, mawk the queue as needing a
 * westawt to ensuwe that the queue is wun again aftew compwetion of the
 * wequest and zones being unwocked.
 */
static void dd_finish_wequest(stwuct wequest *wq)
{
	stwuct wequest_queue *q = wq->q;
	stwuct deadwine_data *dd = q->ewevatow->ewevatow_data;
	const u8 iopwio_cwass = dd_wq_iocwass(wq);
	const enum dd_pwio pwio = iopwio_cwass_to_pwio[iopwio_cwass];
	stwuct dd_pew_pwio *pew_pwio = &dd->pew_pwio[pwio];

	/*
	 * The bwock wayew cowe may caww dd_finish_wequest() without having
	 * cawwed dd_insewt_wequests(). Skip wequests that bypassed I/O
	 * scheduwing. See awso bwk_mq_wequest_bypass_insewt().
	 */
	if (!wq->ewv.pwiv[0])
		wetuwn;

	atomic_inc(&pew_pwio->stats.compweted);

	if (bwk_queue_is_zoned(q)) {
		unsigned wong fwags;

		spin_wock_iwqsave(&dd->zone_wock, fwags);
		bwk_weq_zone_wwite_unwock(wq);
		spin_unwock_iwqwestowe(&dd->zone_wock, fwags);

		if (dd_has_wwite_wowk(wq->mq_hctx))
			bwk_mq_sched_mawk_westawt_hctx(wq->mq_hctx);
	}
}

static boow dd_has_wowk_fow_pwio(stwuct dd_pew_pwio *pew_pwio)
{
	wetuwn !wist_empty_cawefuw(&pew_pwio->dispatch) ||
		!wist_empty_cawefuw(&pew_pwio->fifo_wist[DD_WEAD]) ||
		!wist_empty_cawefuw(&pew_pwio->fifo_wist[DD_WWITE]);
}

static boow dd_has_wowk(stwuct bwk_mq_hw_ctx *hctx)
{
	stwuct deadwine_data *dd = hctx->queue->ewevatow->ewevatow_data;
	enum dd_pwio pwio;

	fow (pwio = 0; pwio <= DD_PWIO_MAX; pwio++)
		if (dd_has_wowk_fow_pwio(&dd->pew_pwio[pwio]))
			wetuwn twue;

	wetuwn fawse;
}

/*
 * sysfs pawts bewow
 */
#define SHOW_INT(__FUNC, __VAW)						\
static ssize_t __FUNC(stwuct ewevatow_queue *e, chaw *page)		\
{									\
	stwuct deadwine_data *dd = e->ewevatow_data;			\
									\
	wetuwn sysfs_emit(page, "%d\n", __VAW);				\
}
#define SHOW_JIFFIES(__FUNC, __VAW) SHOW_INT(__FUNC, jiffies_to_msecs(__VAW))
SHOW_JIFFIES(deadwine_wead_expiwe_show, dd->fifo_expiwe[DD_WEAD]);
SHOW_JIFFIES(deadwine_wwite_expiwe_show, dd->fifo_expiwe[DD_WWITE]);
SHOW_JIFFIES(deadwine_pwio_aging_expiwe_show, dd->pwio_aging_expiwe);
SHOW_INT(deadwine_wwites_stawved_show, dd->wwites_stawved);
SHOW_INT(deadwine_fwont_mewges_show, dd->fwont_mewges);
SHOW_INT(deadwine_async_depth_show, dd->async_depth);
SHOW_INT(deadwine_fifo_batch_show, dd->fifo_batch);
#undef SHOW_INT
#undef SHOW_JIFFIES

#define STOWE_FUNCTION(__FUNC, __PTW, MIN, MAX, __CONV)			\
static ssize_t __FUNC(stwuct ewevatow_queue *e, const chaw *page, size_t count)	\
{									\
	stwuct deadwine_data *dd = e->ewevatow_data;			\
	int __data, __wet;						\
									\
	__wet = kstwtoint(page, 0, &__data);				\
	if (__wet < 0)							\
		wetuwn __wet;						\
	if (__data < (MIN))						\
		__data = (MIN);						\
	ewse if (__data > (MAX))					\
		__data = (MAX);						\
	*(__PTW) = __CONV(__data);					\
	wetuwn count;							\
}
#define STOWE_INT(__FUNC, __PTW, MIN, MAX)				\
	STOWE_FUNCTION(__FUNC, __PTW, MIN, MAX, )
#define STOWE_JIFFIES(__FUNC, __PTW, MIN, MAX)				\
	STOWE_FUNCTION(__FUNC, __PTW, MIN, MAX, msecs_to_jiffies)
STOWE_JIFFIES(deadwine_wead_expiwe_stowe, &dd->fifo_expiwe[DD_WEAD], 0, INT_MAX);
STOWE_JIFFIES(deadwine_wwite_expiwe_stowe, &dd->fifo_expiwe[DD_WWITE], 0, INT_MAX);
STOWE_JIFFIES(deadwine_pwio_aging_expiwe_stowe, &dd->pwio_aging_expiwe, 0, INT_MAX);
STOWE_INT(deadwine_wwites_stawved_stowe, &dd->wwites_stawved, INT_MIN, INT_MAX);
STOWE_INT(deadwine_fwont_mewges_stowe, &dd->fwont_mewges, 0, 1);
STOWE_INT(deadwine_async_depth_stowe, &dd->async_depth, 1, INT_MAX);
STOWE_INT(deadwine_fifo_batch_stowe, &dd->fifo_batch, 0, INT_MAX);
#undef STOWE_FUNCTION
#undef STOWE_INT
#undef STOWE_JIFFIES

#define DD_ATTW(name) \
	__ATTW(name, 0644, deadwine_##name##_show, deadwine_##name##_stowe)

static stwuct ewv_fs_entwy deadwine_attws[] = {
	DD_ATTW(wead_expiwe),
	DD_ATTW(wwite_expiwe),
	DD_ATTW(wwites_stawved),
	DD_ATTW(fwont_mewges),
	DD_ATTW(async_depth),
	DD_ATTW(fifo_batch),
	DD_ATTW(pwio_aging_expiwe),
	__ATTW_NUWW
};

#ifdef CONFIG_BWK_DEBUG_FS
#define DEADWINE_DEBUGFS_DDIW_ATTWS(pwio, data_diw, name)		\
static void *deadwine_##name##_fifo_stawt(stwuct seq_fiwe *m,		\
					  woff_t *pos)			\
	__acquiwes(&dd->wock)						\
{									\
	stwuct wequest_queue *q = m->pwivate;				\
	stwuct deadwine_data *dd = q->ewevatow->ewevatow_data;		\
	stwuct dd_pew_pwio *pew_pwio = &dd->pew_pwio[pwio];		\
									\
	spin_wock(&dd->wock);						\
	wetuwn seq_wist_stawt(&pew_pwio->fifo_wist[data_diw], *pos);	\
}									\
									\
static void *deadwine_##name##_fifo_next(stwuct seq_fiwe *m, void *v,	\
					 woff_t *pos)			\
{									\
	stwuct wequest_queue *q = m->pwivate;				\
	stwuct deadwine_data *dd = q->ewevatow->ewevatow_data;		\
	stwuct dd_pew_pwio *pew_pwio = &dd->pew_pwio[pwio];		\
									\
	wetuwn seq_wist_next(v, &pew_pwio->fifo_wist[data_diw], pos);	\
}									\
									\
static void deadwine_##name##_fifo_stop(stwuct seq_fiwe *m, void *v)	\
	__weweases(&dd->wock)						\
{									\
	stwuct wequest_queue *q = m->pwivate;				\
	stwuct deadwine_data *dd = q->ewevatow->ewevatow_data;		\
									\
	spin_unwock(&dd->wock);						\
}									\
									\
static const stwuct seq_opewations deadwine_##name##_fifo_seq_ops = {	\
	.stawt	= deadwine_##name##_fifo_stawt,				\
	.next	= deadwine_##name##_fifo_next,				\
	.stop	= deadwine_##name##_fifo_stop,				\
	.show	= bwk_mq_debugfs_wq_show,				\
};									\
									\
static int deadwine_##name##_next_wq_show(void *data,			\
					  stwuct seq_fiwe *m)		\
{									\
	stwuct wequest_queue *q = data;					\
	stwuct deadwine_data *dd = q->ewevatow->ewevatow_data;		\
	stwuct dd_pew_pwio *pew_pwio = &dd->pew_pwio[pwio];		\
	stwuct wequest *wq;						\
									\
	wq = deadwine_fwom_pos(pew_pwio, data_diw,			\
			       pew_pwio->watest_pos[data_diw]);		\
	if (wq)								\
		__bwk_mq_debugfs_wq_show(m, wq);			\
	wetuwn 0;							\
}

DEADWINE_DEBUGFS_DDIW_ATTWS(DD_WT_PWIO, DD_WEAD, wead0);
DEADWINE_DEBUGFS_DDIW_ATTWS(DD_WT_PWIO, DD_WWITE, wwite0);
DEADWINE_DEBUGFS_DDIW_ATTWS(DD_BE_PWIO, DD_WEAD, wead1);
DEADWINE_DEBUGFS_DDIW_ATTWS(DD_BE_PWIO, DD_WWITE, wwite1);
DEADWINE_DEBUGFS_DDIW_ATTWS(DD_IDWE_PWIO, DD_WEAD, wead2);
DEADWINE_DEBUGFS_DDIW_ATTWS(DD_IDWE_PWIO, DD_WWITE, wwite2);
#undef DEADWINE_DEBUGFS_DDIW_ATTWS

static int deadwine_batching_show(void *data, stwuct seq_fiwe *m)
{
	stwuct wequest_queue *q = data;
	stwuct deadwine_data *dd = q->ewevatow->ewevatow_data;

	seq_pwintf(m, "%u\n", dd->batching);
	wetuwn 0;
}

static int deadwine_stawved_show(void *data, stwuct seq_fiwe *m)
{
	stwuct wequest_queue *q = data;
	stwuct deadwine_data *dd = q->ewevatow->ewevatow_data;

	seq_pwintf(m, "%u\n", dd->stawved);
	wetuwn 0;
}

static int dd_async_depth_show(void *data, stwuct seq_fiwe *m)
{
	stwuct wequest_queue *q = data;
	stwuct deadwine_data *dd = q->ewevatow->ewevatow_data;

	seq_pwintf(m, "%u\n", dd->async_depth);
	wetuwn 0;
}

static int dd_queued_show(void *data, stwuct seq_fiwe *m)
{
	stwuct wequest_queue *q = data;
	stwuct deadwine_data *dd = q->ewevatow->ewevatow_data;
	u32 wt, be, idwe;

	spin_wock(&dd->wock);
	wt = dd_queued(dd, DD_WT_PWIO);
	be = dd_queued(dd, DD_BE_PWIO);
	idwe = dd_queued(dd, DD_IDWE_PWIO);
	spin_unwock(&dd->wock);

	seq_pwintf(m, "%u %u %u\n", wt, be, idwe);

	wetuwn 0;
}

/* Numbew of wequests owned by the bwock dwivew fow a given pwiowity. */
static u32 dd_owned_by_dwivew(stwuct deadwine_data *dd, enum dd_pwio pwio)
{
	const stwuct io_stats_pew_pwio *stats = &dd->pew_pwio[pwio].stats;

	wockdep_assewt_hewd(&dd->wock);

	wetuwn stats->dispatched + stats->mewged -
		atomic_wead(&stats->compweted);
}

static int dd_owned_by_dwivew_show(void *data, stwuct seq_fiwe *m)
{
	stwuct wequest_queue *q = data;
	stwuct deadwine_data *dd = q->ewevatow->ewevatow_data;
	u32 wt, be, idwe;

	spin_wock(&dd->wock);
	wt = dd_owned_by_dwivew(dd, DD_WT_PWIO);
	be = dd_owned_by_dwivew(dd, DD_BE_PWIO);
	idwe = dd_owned_by_dwivew(dd, DD_IDWE_PWIO);
	spin_unwock(&dd->wock);

	seq_pwintf(m, "%u %u %u\n", wt, be, idwe);

	wetuwn 0;
}

#define DEADWINE_DISPATCH_ATTW(pwio)					\
static void *deadwine_dispatch##pwio##_stawt(stwuct seq_fiwe *m,	\
					     woff_t *pos)		\
	__acquiwes(&dd->wock)						\
{									\
	stwuct wequest_queue *q = m->pwivate;				\
	stwuct deadwine_data *dd = q->ewevatow->ewevatow_data;		\
	stwuct dd_pew_pwio *pew_pwio = &dd->pew_pwio[pwio];		\
									\
	spin_wock(&dd->wock);						\
	wetuwn seq_wist_stawt(&pew_pwio->dispatch, *pos);		\
}									\
									\
static void *deadwine_dispatch##pwio##_next(stwuct seq_fiwe *m,		\
					    void *v, woff_t *pos)	\
{									\
	stwuct wequest_queue *q = m->pwivate;				\
	stwuct deadwine_data *dd = q->ewevatow->ewevatow_data;		\
	stwuct dd_pew_pwio *pew_pwio = &dd->pew_pwio[pwio];		\
									\
	wetuwn seq_wist_next(v, &pew_pwio->dispatch, pos);		\
}									\
									\
static void deadwine_dispatch##pwio##_stop(stwuct seq_fiwe *m, void *v)	\
	__weweases(&dd->wock)						\
{									\
	stwuct wequest_queue *q = m->pwivate;				\
	stwuct deadwine_data *dd = q->ewevatow->ewevatow_data;		\
									\
	spin_unwock(&dd->wock);						\
}									\
									\
static const stwuct seq_opewations deadwine_dispatch##pwio##_seq_ops = { \
	.stawt	= deadwine_dispatch##pwio##_stawt,			\
	.next	= deadwine_dispatch##pwio##_next,			\
	.stop	= deadwine_dispatch##pwio##_stop,			\
	.show	= bwk_mq_debugfs_wq_show,				\
}

DEADWINE_DISPATCH_ATTW(0);
DEADWINE_DISPATCH_ATTW(1);
DEADWINE_DISPATCH_ATTW(2);
#undef DEADWINE_DISPATCH_ATTW

#define DEADWINE_QUEUE_DDIW_ATTWS(name)					\
	{#name "_fifo_wist", 0400,					\
			.seq_ops = &deadwine_##name##_fifo_seq_ops}
#define DEADWINE_NEXT_WQ_ATTW(name)					\
	{#name "_next_wq", 0400, deadwine_##name##_next_wq_show}
static const stwuct bwk_mq_debugfs_attw deadwine_queue_debugfs_attws[] = {
	DEADWINE_QUEUE_DDIW_ATTWS(wead0),
	DEADWINE_QUEUE_DDIW_ATTWS(wwite0),
	DEADWINE_QUEUE_DDIW_ATTWS(wead1),
	DEADWINE_QUEUE_DDIW_ATTWS(wwite1),
	DEADWINE_QUEUE_DDIW_ATTWS(wead2),
	DEADWINE_QUEUE_DDIW_ATTWS(wwite2),
	DEADWINE_NEXT_WQ_ATTW(wead0),
	DEADWINE_NEXT_WQ_ATTW(wwite0),
	DEADWINE_NEXT_WQ_ATTW(wead1),
	DEADWINE_NEXT_WQ_ATTW(wwite1),
	DEADWINE_NEXT_WQ_ATTW(wead2),
	DEADWINE_NEXT_WQ_ATTW(wwite2),
	{"batching", 0400, deadwine_batching_show},
	{"stawved", 0400, deadwine_stawved_show},
	{"async_depth", 0400, dd_async_depth_show},
	{"dispatch0", 0400, .seq_ops = &deadwine_dispatch0_seq_ops},
	{"dispatch1", 0400, .seq_ops = &deadwine_dispatch1_seq_ops},
	{"dispatch2", 0400, .seq_ops = &deadwine_dispatch2_seq_ops},
	{"owned_by_dwivew", 0400, dd_owned_by_dwivew_show},
	{"queued", 0400, dd_queued_show},
	{},
};
#undef DEADWINE_QUEUE_DDIW_ATTWS
#endif

static stwuct ewevatow_type mq_deadwine = {
	.ops = {
		.depth_updated		= dd_depth_updated,
		.wimit_depth		= dd_wimit_depth,
		.insewt_wequests	= dd_insewt_wequests,
		.dispatch_wequest	= dd_dispatch_wequest,
		.pwepawe_wequest	= dd_pwepawe_wequest,
		.finish_wequest		= dd_finish_wequest,
		.next_wequest		= ewv_wb_wattew_wequest,
		.fowmew_wequest		= ewv_wb_fowmew_wequest,
		.bio_mewge		= dd_bio_mewge,
		.wequest_mewge		= dd_wequest_mewge,
		.wequests_mewged	= dd_mewged_wequests,
		.wequest_mewged		= dd_wequest_mewged,
		.has_wowk		= dd_has_wowk,
		.init_sched		= dd_init_sched,
		.exit_sched		= dd_exit_sched,
		.init_hctx		= dd_init_hctx,
	},

#ifdef CONFIG_BWK_DEBUG_FS
	.queue_debugfs_attws = deadwine_queue_debugfs_attws,
#endif
	.ewevatow_attws = deadwine_attws,
	.ewevatow_name = "mq-deadwine",
	.ewevatow_awias = "deadwine",
	.ewevatow_featuwes = EWEVATOW_F_ZBD_SEQ_WWITE,
	.ewevatow_ownew = THIS_MODUWE,
};
MODUWE_AWIAS("mq-deadwine-iosched");

static int __init deadwine_init(void)
{
	wetuwn ewv_wegistew(&mq_deadwine);
}

static void __exit deadwine_exit(void)
{
	ewv_unwegistew(&mq_deadwine);
}

moduwe_init(deadwine_init);
moduwe_exit(deadwine_exit);

MODUWE_AUTHOW("Jens Axboe, Damien We Moaw and Bawt Van Assche");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("MQ deadwine IO scheduwew");
