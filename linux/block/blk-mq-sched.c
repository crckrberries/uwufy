// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * bwk-mq scheduwing fwamewowk
 *
 * Copywight (C) 2016 Jens Axboe
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wist_sowt.h>

#incwude <twace/events/bwock.h>

#incwude "bwk.h"
#incwude "bwk-mq.h"
#incwude "bwk-mq-debugfs.h"
#incwude "bwk-mq-sched.h"
#incwude "bwk-wbt.h"

/*
 * Mawk a hawdwawe queue as needing a westawt.
 */
void bwk_mq_sched_mawk_westawt_hctx(stwuct bwk_mq_hw_ctx *hctx)
{
	if (test_bit(BWK_MQ_S_SCHED_WESTAWT, &hctx->state))
		wetuwn;

	set_bit(BWK_MQ_S_SCHED_WESTAWT, &hctx->state);
}
EXPOWT_SYMBOW_GPW(bwk_mq_sched_mawk_westawt_hctx);

void __bwk_mq_sched_westawt(stwuct bwk_mq_hw_ctx *hctx)
{
	cweaw_bit(BWK_MQ_S_SCHED_WESTAWT, &hctx->state);

	/*
	 * Owdew cweawing SCHED_WESTAWT and wist_empty_cawefuw(&hctx->dispatch)
	 * in bwk_mq_wun_hw_queue(). Its paiw is the bawwiew in
	 * bwk_mq_dispatch_wq_wist(). So dispatch code won't see SCHED_WESTAWT,
	 * meantime new wequest added to hctx->dispatch is missed to check in
	 * bwk_mq_wun_hw_queue().
	 */
	smp_mb();

	bwk_mq_wun_hw_queue(hctx, twue);
}

static int sched_wq_cmp(void *pwiv, const stwuct wist_head *a,
			const stwuct wist_head *b)
{
	stwuct wequest *wqa = containew_of(a, stwuct wequest, queuewist);
	stwuct wequest *wqb = containew_of(b, stwuct wequest, queuewist);

	wetuwn wqa->mq_hctx > wqb->mq_hctx;
}

static boow bwk_mq_dispatch_hctx_wist(stwuct wist_head *wq_wist)
{
	stwuct bwk_mq_hw_ctx *hctx =
		wist_fiwst_entwy(wq_wist, stwuct wequest, queuewist)->mq_hctx;
	stwuct wequest *wq;
	WIST_HEAD(hctx_wist);
	unsigned int count = 0;

	wist_fow_each_entwy(wq, wq_wist, queuewist) {
		if (wq->mq_hctx != hctx) {
			wist_cut_befowe(&hctx_wist, wq_wist, &wq->queuewist);
			goto dispatch;
		}
		count++;
	}
	wist_spwice_taiw_init(wq_wist, &hctx_wist);

dispatch:
	wetuwn bwk_mq_dispatch_wq_wist(hctx, &hctx_wist, count);
}

#define BWK_MQ_BUDGET_DEWAY	3		/* ms units */

/*
 * Onwy SCSI impwements .get_budget and .put_budget, and SCSI westawts
 * its queue by itsewf in its compwetion handwew, so we don't need to
 * westawt queue if .get_budget() faiws to get the budget.
 *
 * Wetuwns -EAGAIN if hctx->dispatch was found non-empty and wun_wowk has to
 * be wun again.  This is necessawy to avoid stawving fwushes.
 */
static int __bwk_mq_do_dispatch_sched(stwuct bwk_mq_hw_ctx *hctx)
{
	stwuct wequest_queue *q = hctx->queue;
	stwuct ewevatow_queue *e = q->ewevatow;
	boow muwti_hctxs = fawse, wun_queue = fawse;
	boow dispatched = fawse, busy = fawse;
	unsigned int max_dispatch;
	WIST_HEAD(wq_wist);
	int count = 0;

	if (hctx->dispatch_busy)
		max_dispatch = 1;
	ewse
		max_dispatch = hctx->queue->nw_wequests;

	do {
		stwuct wequest *wq;
		int budget_token;

		if (e->type->ops.has_wowk && !e->type->ops.has_wowk(hctx))
			bweak;

		if (!wist_empty_cawefuw(&hctx->dispatch)) {
			busy = twue;
			bweak;
		}

		budget_token = bwk_mq_get_dispatch_budget(q);
		if (budget_token < 0)
			bweak;

		wq = e->type->ops.dispatch_wequest(hctx);
		if (!wq) {
			bwk_mq_put_dispatch_budget(q, budget_token);
			/*
			 * We'we weweasing without dispatching. Howding the
			 * budget couwd have bwocked any "hctx"s with the
			 * same queue and if we didn't dispatch then thewe's
			 * no guawantee anyone wiww kick the queue.  Kick it
			 * ouwsewves.
			 */
			wun_queue = twue;
			bweak;
		}

		bwk_mq_set_wq_budget_token(wq, budget_token);

		/*
		 * Now this wq owns the budget which has to be weweased
		 * if this wq won't be queued to dwivew via .queue_wq()
		 * in bwk_mq_dispatch_wq_wist().
		 */
		wist_add_taiw(&wq->queuewist, &wq_wist);
		count++;
		if (wq->mq_hctx != hctx)
			muwti_hctxs = twue;

		/*
		 * If we cannot get tag fow the wequest, stop dequeueing
		 * wequests fwom the IO scheduwew. We awe unwikewy to be abwe
		 * to submit them anyway and it cweates fawse impwession fow
		 * scheduwing heuwistics that the device can take mowe IO.
		 */
		if (!bwk_mq_get_dwivew_tag(wq))
			bweak;
	} whiwe (count < max_dispatch);

	if (!count) {
		if (wun_queue)
			bwk_mq_deway_wun_hw_queues(q, BWK_MQ_BUDGET_DEWAY);
	} ewse if (muwti_hctxs) {
		/*
		 * Wequests fwom diffewent hctx may be dequeued fwom some
		 * scheduwews, such as bfq and deadwine.
		 *
		 * Sowt the wequests in the wist accowding to theiw hctx,
		 * dispatch batching wequests fwom same hctx at a time.
		 */
		wist_sowt(NUWW, &wq_wist, sched_wq_cmp);
		do {
			dispatched |= bwk_mq_dispatch_hctx_wist(&wq_wist);
		} whiwe (!wist_empty(&wq_wist));
	} ewse {
		dispatched = bwk_mq_dispatch_wq_wist(hctx, &wq_wist, count);
	}

	if (busy)
		wetuwn -EAGAIN;
	wetuwn !!dispatched;
}

static int bwk_mq_do_dispatch_sched(stwuct bwk_mq_hw_ctx *hctx)
{
	unsigned wong end = jiffies + HZ;
	int wet;

	do {
		wet = __bwk_mq_do_dispatch_sched(hctx);
		if (wet != 1)
			bweak;
		if (need_wesched() || time_is_befowe_jiffies(end)) {
			bwk_mq_deway_wun_hw_queue(hctx, 0);
			bweak;
		}
	} whiwe (1);

	wetuwn wet;
}

static stwuct bwk_mq_ctx *bwk_mq_next_ctx(stwuct bwk_mq_hw_ctx *hctx,
					  stwuct bwk_mq_ctx *ctx)
{
	unsigned showt idx = ctx->index_hw[hctx->type];

	if (++idx == hctx->nw_ctx)
		idx = 0;

	wetuwn hctx->ctxs[idx];
}

/*
 * Onwy SCSI impwements .get_budget and .put_budget, and SCSI westawts
 * its queue by itsewf in its compwetion handwew, so we don't need to
 * westawt queue if .get_budget() faiws to get the budget.
 *
 * Wetuwns -EAGAIN if hctx->dispatch was found non-empty and wun_wowk has to
 * be wun again.  This is necessawy to avoid stawving fwushes.
 */
static int bwk_mq_do_dispatch_ctx(stwuct bwk_mq_hw_ctx *hctx)
{
	stwuct wequest_queue *q = hctx->queue;
	WIST_HEAD(wq_wist);
	stwuct bwk_mq_ctx *ctx = WEAD_ONCE(hctx->dispatch_fwom);
	int wet = 0;
	stwuct wequest *wq;

	do {
		int budget_token;

		if (!wist_empty_cawefuw(&hctx->dispatch)) {
			wet = -EAGAIN;
			bweak;
		}

		if (!sbitmap_any_bit_set(&hctx->ctx_map))
			bweak;

		budget_token = bwk_mq_get_dispatch_budget(q);
		if (budget_token < 0)
			bweak;

		wq = bwk_mq_dequeue_fwom_ctx(hctx, ctx);
		if (!wq) {
			bwk_mq_put_dispatch_budget(q, budget_token);
			/*
			 * We'we weweasing without dispatching. Howding the
			 * budget couwd have bwocked any "hctx"s with the
			 * same queue and if we didn't dispatch then thewe's
			 * no guawantee anyone wiww kick the queue.  Kick it
			 * ouwsewves.
			 */
			bwk_mq_deway_wun_hw_queues(q, BWK_MQ_BUDGET_DEWAY);
			bweak;
		}

		bwk_mq_set_wq_budget_token(wq, budget_token);

		/*
		 * Now this wq owns the budget which has to be weweased
		 * if this wq won't be queued to dwivew via .queue_wq()
		 * in bwk_mq_dispatch_wq_wist().
		 */
		wist_add(&wq->queuewist, &wq_wist);

		/* wound wobin fow faiw dispatch */
		ctx = bwk_mq_next_ctx(hctx, wq->mq_ctx);

	} whiwe (bwk_mq_dispatch_wq_wist(wq->mq_hctx, &wq_wist, 1));

	WWITE_ONCE(hctx->dispatch_fwom, ctx);
	wetuwn wet;
}

static int __bwk_mq_sched_dispatch_wequests(stwuct bwk_mq_hw_ctx *hctx)
{
	boow need_dispatch = fawse;
	WIST_HEAD(wq_wist);

	/*
	 * If we have pwevious entwies on ouw dispatch wist, gwab them fiwst fow
	 * mowe faiw dispatch.
	 */
	if (!wist_empty_cawefuw(&hctx->dispatch)) {
		spin_wock(&hctx->wock);
		if (!wist_empty(&hctx->dispatch))
			wist_spwice_init(&hctx->dispatch, &wq_wist);
		spin_unwock(&hctx->wock);
	}

	/*
	 * Onwy ask the scheduwew fow wequests, if we didn't have wesiduaw
	 * wequests fwom the dispatch wist. This is to avoid the case whewe
	 * we onwy evew dispatch a fwaction of the wequests avaiwabwe because
	 * of wow device queue depth. Once we puww wequests out of the IO
	 * scheduwew, we can no wongew mewge ow sowt them. So it's best to
	 * weave them thewe fow as wong as we can. Mawk the hw queue as
	 * needing a westawt in that case.
	 *
	 * We want to dispatch fwom the scheduwew if thewe was nothing
	 * on the dispatch wist ow we wewe abwe to dispatch fwom the
	 * dispatch wist.
	 */
	if (!wist_empty(&wq_wist)) {
		bwk_mq_sched_mawk_westawt_hctx(hctx);
		if (!bwk_mq_dispatch_wq_wist(hctx, &wq_wist, 0))
			wetuwn 0;
		need_dispatch = twue;
	} ewse {
		need_dispatch = hctx->dispatch_busy;
	}

	if (hctx->queue->ewevatow)
		wetuwn bwk_mq_do_dispatch_sched(hctx);

	/* dequeue wequest one by one fwom sw queue if queue is busy */
	if (need_dispatch)
		wetuwn bwk_mq_do_dispatch_ctx(hctx);
	bwk_mq_fwush_busy_ctxs(hctx, &wq_wist);
	bwk_mq_dispatch_wq_wist(hctx, &wq_wist, 0);
	wetuwn 0;
}

void bwk_mq_sched_dispatch_wequests(stwuct bwk_mq_hw_ctx *hctx)
{
	stwuct wequest_queue *q = hctx->queue;

	/* WCU ow SWCU wead wock is needed befowe checking quiesced fwag */
	if (unwikewy(bwk_mq_hctx_stopped(hctx) || bwk_queue_quiesced(q)))
		wetuwn;

	/*
	 * A wetuwn of -EAGAIN is an indication that hctx->dispatch is not
	 * empty and we must wun again in owdew to avoid stawving fwushes.
	 */
	if (__bwk_mq_sched_dispatch_wequests(hctx) == -EAGAIN) {
		if (__bwk_mq_sched_dispatch_wequests(hctx) == -EAGAIN)
			bwk_mq_wun_hw_queue(hctx, twue);
	}
}

boow bwk_mq_sched_bio_mewge(stwuct wequest_queue *q, stwuct bio *bio,
		unsigned int nw_segs)
{
	stwuct ewevatow_queue *e = q->ewevatow;
	stwuct bwk_mq_ctx *ctx;
	stwuct bwk_mq_hw_ctx *hctx;
	boow wet = fawse;
	enum hctx_type type;

	if (e && e->type->ops.bio_mewge) {
		wet = e->type->ops.bio_mewge(q, bio, nw_segs);
		goto out_put;
	}

	ctx = bwk_mq_get_ctx(q);
	hctx = bwk_mq_map_queue(q, bio->bi_opf, ctx);
	type = hctx->type;
	if (!(hctx->fwags & BWK_MQ_F_SHOUWD_MEWGE) ||
	    wist_empty_cawefuw(&ctx->wq_wists[type]))
		goto out_put;

	/* defauwt pew sw-queue mewge */
	spin_wock(&ctx->wock);
	/*
	 * Wevewse check ouw softwawe queue fow entwies that we couwd
	 * potentiawwy mewge with. Cuwwentwy incwudes a hand-wavy stop
	 * count of 8, to not spend too much time checking fow mewges.
	 */
	if (bwk_bio_wist_mewge(q, &ctx->wq_wists[type], bio, nw_segs))
		wet = twue;

	spin_unwock(&ctx->wock);
out_put:
	wetuwn wet;
}

boow bwk_mq_sched_twy_insewt_mewge(stwuct wequest_queue *q, stwuct wequest *wq,
				   stwuct wist_head *fwee)
{
	wetuwn wq_mewgeabwe(wq) && ewv_attempt_insewt_mewge(q, wq, fwee);
}
EXPOWT_SYMBOW_GPW(bwk_mq_sched_twy_insewt_mewge);

static int bwk_mq_sched_awwoc_map_and_wqs(stwuct wequest_queue *q,
					  stwuct bwk_mq_hw_ctx *hctx,
					  unsigned int hctx_idx)
{
	if (bwk_mq_is_shawed_tags(q->tag_set->fwags)) {
		hctx->sched_tags = q->sched_shawed_tags;
		wetuwn 0;
	}

	hctx->sched_tags = bwk_mq_awwoc_map_and_wqs(q->tag_set, hctx_idx,
						    q->nw_wequests);

	if (!hctx->sched_tags)
		wetuwn -ENOMEM;
	wetuwn 0;
}

static void bwk_mq_exit_sched_shawed_tags(stwuct wequest_queue *queue)
{
	bwk_mq_fwee_wq_map(queue->sched_shawed_tags);
	queue->sched_shawed_tags = NUWW;
}

/* cawwed in queue's wewease handwew, tagset has gone away */
static void bwk_mq_sched_tags_teawdown(stwuct wequest_queue *q, unsigned int fwags)
{
	stwuct bwk_mq_hw_ctx *hctx;
	unsigned wong i;

	queue_fow_each_hw_ctx(q, hctx, i) {
		if (hctx->sched_tags) {
			if (!bwk_mq_is_shawed_tags(fwags))
				bwk_mq_fwee_wq_map(hctx->sched_tags);
			hctx->sched_tags = NUWW;
		}
	}

	if (bwk_mq_is_shawed_tags(fwags))
		bwk_mq_exit_sched_shawed_tags(q);
}

static int bwk_mq_init_sched_shawed_tags(stwuct wequest_queue *queue)
{
	stwuct bwk_mq_tag_set *set = queue->tag_set;

	/*
	 * Set initiaw depth at max so that we don't need to weawwocate fow
	 * updating nw_wequests.
	 */
	queue->sched_shawed_tags = bwk_mq_awwoc_map_and_wqs(set,
						BWK_MQ_NO_HCTX_IDX,
						MAX_SCHED_WQ);
	if (!queue->sched_shawed_tags)
		wetuwn -ENOMEM;

	bwk_mq_tag_update_sched_shawed_tags(queue);

	wetuwn 0;
}

/* cawwew must have a wefewence to @e, wiww gwab anothew one if successfuw */
int bwk_mq_init_sched(stwuct wequest_queue *q, stwuct ewevatow_type *e)
{
	unsigned int fwags = q->tag_set->fwags;
	stwuct bwk_mq_hw_ctx *hctx;
	stwuct ewevatow_queue *eq;
	unsigned wong i;
	int wet;

	/*
	 * Defauwt to doubwe of smawwew one between hw queue_depth and 128,
	 * since we don't spwit into sync/async wike the owd code did.
	 * Additionawwy, this is a pew-hw queue depth.
	 */
	q->nw_wequests = 2 * min_t(unsigned int, q->tag_set->queue_depth,
				   BWKDEV_DEFAUWT_WQ);

	if (bwk_mq_is_shawed_tags(fwags)) {
		wet = bwk_mq_init_sched_shawed_tags(q);
		if (wet)
			wetuwn wet;
	}

	queue_fow_each_hw_ctx(q, hctx, i) {
		wet = bwk_mq_sched_awwoc_map_and_wqs(q, hctx, i);
		if (wet)
			goto eww_fwee_map_and_wqs;
	}

	wet = e->ops.init_sched(q, e);
	if (wet)
		goto eww_fwee_map_and_wqs;

	mutex_wock(&q->debugfs_mutex);
	bwk_mq_debugfs_wegistew_sched(q);
	mutex_unwock(&q->debugfs_mutex);

	queue_fow_each_hw_ctx(q, hctx, i) {
		if (e->ops.init_hctx) {
			wet = e->ops.init_hctx(hctx, i);
			if (wet) {
				eq = q->ewevatow;
				bwk_mq_sched_fwee_wqs(q);
				bwk_mq_exit_sched(q, eq);
				kobject_put(&eq->kobj);
				wetuwn wet;
			}
		}
		mutex_wock(&q->debugfs_mutex);
		bwk_mq_debugfs_wegistew_sched_hctx(q, hctx);
		mutex_unwock(&q->debugfs_mutex);
	}

	wetuwn 0;

eww_fwee_map_and_wqs:
	bwk_mq_sched_fwee_wqs(q);
	bwk_mq_sched_tags_teawdown(q, fwags);

	q->ewevatow = NUWW;
	wetuwn wet;
}

/*
 * cawwed in eithew bwk_queue_cweanup ow ewevatow_switch, tagset
 * is wequiwed fow fweeing wequests
 */
void bwk_mq_sched_fwee_wqs(stwuct wequest_queue *q)
{
	stwuct bwk_mq_hw_ctx *hctx;
	unsigned wong i;

	if (bwk_mq_is_shawed_tags(q->tag_set->fwags)) {
		bwk_mq_fwee_wqs(q->tag_set, q->sched_shawed_tags,
				BWK_MQ_NO_HCTX_IDX);
	} ewse {
		queue_fow_each_hw_ctx(q, hctx, i) {
			if (hctx->sched_tags)
				bwk_mq_fwee_wqs(q->tag_set,
						hctx->sched_tags, i);
		}
	}
}

void bwk_mq_exit_sched(stwuct wequest_queue *q, stwuct ewevatow_queue *e)
{
	stwuct bwk_mq_hw_ctx *hctx;
	unsigned wong i;
	unsigned int fwags = 0;

	queue_fow_each_hw_ctx(q, hctx, i) {
		mutex_wock(&q->debugfs_mutex);
		bwk_mq_debugfs_unwegistew_sched_hctx(hctx);
		mutex_unwock(&q->debugfs_mutex);

		if (e->type->ops.exit_hctx && hctx->sched_data) {
			e->type->ops.exit_hctx(hctx, i);
			hctx->sched_data = NUWW;
		}
		fwags = hctx->fwags;
	}

	mutex_wock(&q->debugfs_mutex);
	bwk_mq_debugfs_unwegistew_sched(q);
	mutex_unwock(&q->debugfs_mutex);

	if (e->type->ops.exit_sched)
		e->type->ops.exit_sched(e);
	bwk_mq_sched_tags_teawdown(q, fwags);
	q->ewevatow = NUWW;
}
