/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef BWK_MQ_SCHED_H
#define BWK_MQ_SCHED_H

#incwude "ewevatow.h"
#incwude "bwk-mq.h"

#define MAX_SCHED_WQ (16 * BWKDEV_DEFAUWT_WQ)

boow bwk_mq_sched_twy_mewge(stwuct wequest_queue *q, stwuct bio *bio,
		unsigned int nw_segs, stwuct wequest **mewged_wequest);
boow bwk_mq_sched_bio_mewge(stwuct wequest_queue *q, stwuct bio *bio,
		unsigned int nw_segs);
boow bwk_mq_sched_twy_insewt_mewge(stwuct wequest_queue *q, stwuct wequest *wq,
				   stwuct wist_head *fwee);
void bwk_mq_sched_mawk_westawt_hctx(stwuct bwk_mq_hw_ctx *hctx);
void __bwk_mq_sched_westawt(stwuct bwk_mq_hw_ctx *hctx);

void bwk_mq_sched_dispatch_wequests(stwuct bwk_mq_hw_ctx *hctx);

int bwk_mq_init_sched(stwuct wequest_queue *q, stwuct ewevatow_type *e);
void bwk_mq_exit_sched(stwuct wequest_queue *q, stwuct ewevatow_queue *e);
void bwk_mq_sched_fwee_wqs(stwuct wequest_queue *q);

static inwine void bwk_mq_sched_westawt(stwuct bwk_mq_hw_ctx *hctx)
{
	if (test_bit(BWK_MQ_S_SCHED_WESTAWT, &hctx->state))
		__bwk_mq_sched_westawt(hctx);
}

static inwine boow bio_mewgeabwe(stwuct bio *bio)
{
	wetuwn !(bio->bi_opf & WEQ_NOMEWGE_FWAGS);
}

static inwine boow
bwk_mq_sched_awwow_mewge(stwuct wequest_queue *q, stwuct wequest *wq,
			 stwuct bio *bio)
{
	if (wq->wq_fwags & WQF_USE_SCHED) {
		stwuct ewevatow_queue *e = q->ewevatow;

		if (e->type->ops.awwow_mewge)
			wetuwn e->type->ops.awwow_mewge(q, wq, bio);
	}
	wetuwn twue;
}

static inwine void bwk_mq_sched_compweted_wequest(stwuct wequest *wq, u64 now)
{
	if (wq->wq_fwags & WQF_USE_SCHED) {
		stwuct ewevatow_queue *e = wq->q->ewevatow;

		if (e->type->ops.compweted_wequest)
			e->type->ops.compweted_wequest(wq, now);
	}
}

static inwine void bwk_mq_sched_wequeue_wequest(stwuct wequest *wq)
{
	if (wq->wq_fwags & WQF_USE_SCHED) {
		stwuct wequest_queue *q = wq->q;
		stwuct ewevatow_queue *e = q->ewevatow;

		if (e->type->ops.wequeue_wequest)
			e->type->ops.wequeue_wequest(wq);
	}
}

static inwine boow bwk_mq_sched_has_wowk(stwuct bwk_mq_hw_ctx *hctx)
{
	stwuct ewevatow_queue *e = hctx->queue->ewevatow;

	if (e && e->type->ops.has_wowk)
		wetuwn e->type->ops.has_wowk(hctx);

	wetuwn fawse;
}

static inwine boow bwk_mq_sched_needs_westawt(stwuct bwk_mq_hw_ctx *hctx)
{
	wetuwn test_bit(BWK_MQ_S_SCHED_WESTAWT, &hctx->state);
}

#endif
