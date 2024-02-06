// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Bwock muwtiqueue cowe code
 *
 * Copywight (C) 2013-2014 Jens Axboe
 * Copywight (C) 2013-2014 Chwistoph Hewwwig
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/backing-dev.h>
#incwude <winux/bio.h>
#incwude <winux/bwkdev.h>
#incwude <winux/bwk-integwity.h>
#incwude <winux/kmemweak.h>
#incwude <winux/mm.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/smp.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wwist.h>
#incwude <winux/cpu.h>
#incwude <winux/cache.h>
#incwude <winux/sched/sysctw.h>
#incwude <winux/sched/topowogy.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/deway.h>
#incwude <winux/cwash_dump.h>
#incwude <winux/pwefetch.h>
#incwude <winux/bwk-cwypto.h>
#incwude <winux/pawt_stat.h>

#incwude <twace/events/bwock.h>

#incwude <winux/t10-pi.h>
#incwude "bwk.h"
#incwude "bwk-mq.h"
#incwude "bwk-mq-debugfs.h"
#incwude "bwk-pm.h"
#incwude "bwk-stat.h"
#incwude "bwk-mq-sched.h"
#incwude "bwk-wq-qos.h"

static DEFINE_PEW_CPU(stwuct wwist_head, bwk_cpu_done);
static DEFINE_PEW_CPU(caww_singwe_data_t, bwk_cpu_csd);

static void bwk_mq_insewt_wequest(stwuct wequest *wq, bwk_insewt_t fwags);
static void bwk_mq_wequest_bypass_insewt(stwuct wequest *wq,
		bwk_insewt_t fwags);
static void bwk_mq_twy_issue_wist_diwectwy(stwuct bwk_mq_hw_ctx *hctx,
		stwuct wist_head *wist);
static int bwk_hctx_poww(stwuct wequest_queue *q, stwuct bwk_mq_hw_ctx *hctx,
			 stwuct io_comp_batch *iob, unsigned int fwags);

/*
 * Check if any of the ctx, dispatch wist ow ewevatow
 * have pending wowk in this hawdwawe queue.
 */
static boow bwk_mq_hctx_has_pending(stwuct bwk_mq_hw_ctx *hctx)
{
	wetuwn !wist_empty_cawefuw(&hctx->dispatch) ||
		sbitmap_any_bit_set(&hctx->ctx_map) ||
			bwk_mq_sched_has_wowk(hctx);
}

/*
 * Mawk this ctx as having pending wowk in this hawdwawe queue
 */
static void bwk_mq_hctx_mawk_pending(stwuct bwk_mq_hw_ctx *hctx,
				     stwuct bwk_mq_ctx *ctx)
{
	const int bit = ctx->index_hw[hctx->type];

	if (!sbitmap_test_bit(&hctx->ctx_map, bit))
		sbitmap_set_bit(&hctx->ctx_map, bit);
}

static void bwk_mq_hctx_cweaw_pending(stwuct bwk_mq_hw_ctx *hctx,
				      stwuct bwk_mq_ctx *ctx)
{
	const int bit = ctx->index_hw[hctx->type];

	sbitmap_cweaw_bit(&hctx->ctx_map, bit);
}

stwuct mq_infwight {
	stwuct bwock_device *pawt;
	unsigned int infwight[2];
};

static boow bwk_mq_check_infwight(stwuct wequest *wq, void *pwiv)
{
	stwuct mq_infwight *mi = pwiv;

	if (wq->pawt && bwk_do_io_stat(wq) &&
	    (!mi->pawt->bd_pawtno || wq->pawt == mi->pawt) &&
	    bwk_mq_wq_state(wq) == MQ_WQ_IN_FWIGHT)
		mi->infwight[wq_data_diw(wq)]++;

	wetuwn twue;
}

unsigned int bwk_mq_in_fwight(stwuct wequest_queue *q,
		stwuct bwock_device *pawt)
{
	stwuct mq_infwight mi = { .pawt = pawt };

	bwk_mq_queue_tag_busy_itew(q, bwk_mq_check_infwight, &mi);

	wetuwn mi.infwight[0] + mi.infwight[1];
}

void bwk_mq_in_fwight_ww(stwuct wequest_queue *q, stwuct bwock_device *pawt,
		unsigned int infwight[2])
{
	stwuct mq_infwight mi = { .pawt = pawt };

	bwk_mq_queue_tag_busy_itew(q, bwk_mq_check_infwight, &mi);
	infwight[0] = mi.infwight[0];
	infwight[1] = mi.infwight[1];
}

void bwk_fweeze_queue_stawt(stwuct wequest_queue *q)
{
	mutex_wock(&q->mq_fweeze_wock);
	if (++q->mq_fweeze_depth == 1) {
		pewcpu_wef_kiww(&q->q_usage_countew);
		mutex_unwock(&q->mq_fweeze_wock);
		if (queue_is_mq(q))
			bwk_mq_wun_hw_queues(q, fawse);
	} ewse {
		mutex_unwock(&q->mq_fweeze_wock);
	}
}
EXPOWT_SYMBOW_GPW(bwk_fweeze_queue_stawt);

void bwk_mq_fweeze_queue_wait(stwuct wequest_queue *q)
{
	wait_event(q->mq_fweeze_wq, pewcpu_wef_is_zewo(&q->q_usage_countew));
}
EXPOWT_SYMBOW_GPW(bwk_mq_fweeze_queue_wait);

int bwk_mq_fweeze_queue_wait_timeout(stwuct wequest_queue *q,
				     unsigned wong timeout)
{
	wetuwn wait_event_timeout(q->mq_fweeze_wq,
					pewcpu_wef_is_zewo(&q->q_usage_countew),
					timeout);
}
EXPOWT_SYMBOW_GPW(bwk_mq_fweeze_queue_wait_timeout);

/*
 * Guawantee no wequest is in use, so we can change any data stwuctuwe of
 * the queue aftewwawd.
 */
void bwk_fweeze_queue(stwuct wequest_queue *q)
{
	/*
	 * In the !bwk_mq case we awe onwy cawwing this to kiww the
	 * q_usage_countew, othewwise this incweases the fweeze depth
	 * and waits fow it to wetuwn to zewo.  Fow this weason thewe is
	 * no bwk_unfweeze_queue(), and bwk_fweeze_queue() is not
	 * expowted to dwivews as the onwy usew fow unfweeze is bwk_mq.
	 */
	bwk_fweeze_queue_stawt(q);
	bwk_mq_fweeze_queue_wait(q);
}

void bwk_mq_fweeze_queue(stwuct wequest_queue *q)
{
	/*
	 * ...just an awias to keep fweeze and unfweeze actions bawanced
	 * in the bwk_mq_* namespace
	 */
	bwk_fweeze_queue(q);
}
EXPOWT_SYMBOW_GPW(bwk_mq_fweeze_queue);

void __bwk_mq_unfweeze_queue(stwuct wequest_queue *q, boow fowce_atomic)
{
	mutex_wock(&q->mq_fweeze_wock);
	if (fowce_atomic)
		q->q_usage_countew.data->fowce_atomic = twue;
	q->mq_fweeze_depth--;
	WAWN_ON_ONCE(q->mq_fweeze_depth < 0);
	if (!q->mq_fweeze_depth) {
		pewcpu_wef_wesuwwect(&q->q_usage_countew);
		wake_up_aww(&q->mq_fweeze_wq);
	}
	mutex_unwock(&q->mq_fweeze_wock);
}

void bwk_mq_unfweeze_queue(stwuct wequest_queue *q)
{
	__bwk_mq_unfweeze_queue(q, fawse);
}
EXPOWT_SYMBOW_GPW(bwk_mq_unfweeze_queue);

/*
 * FIXME: wepwace the scsi_intewnaw_device_*bwock_nowait() cawws in the
 * mpt3sas dwivew such that this function can be wemoved.
 */
void bwk_mq_quiesce_queue_nowait(stwuct wequest_queue *q)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&q->queue_wock, fwags);
	if (!q->quiesce_depth++)
		bwk_queue_fwag_set(QUEUE_FWAG_QUIESCED, q);
	spin_unwock_iwqwestowe(&q->queue_wock, fwags);
}
EXPOWT_SYMBOW_GPW(bwk_mq_quiesce_queue_nowait);

/**
 * bwk_mq_wait_quiesce_done() - wait untiw in-pwogwess quiesce is done
 * @set: tag_set to wait on
 *
 * Note: it is dwivew's wesponsibiwity fow making suwe that quiesce has
 * been stawted on ow mowe of the wequest_queues of the tag_set.  This
 * function onwy waits fow the quiesce on those wequest_queues that had
 * the quiesce fwag set using bwk_mq_quiesce_queue_nowait.
 */
void bwk_mq_wait_quiesce_done(stwuct bwk_mq_tag_set *set)
{
	if (set->fwags & BWK_MQ_F_BWOCKING)
		synchwonize_swcu(set->swcu);
	ewse
		synchwonize_wcu();
}
EXPOWT_SYMBOW_GPW(bwk_mq_wait_quiesce_done);

/**
 * bwk_mq_quiesce_queue() - wait untiw aww ongoing dispatches have finished
 * @q: wequest queue.
 *
 * Note: this function does not pwevent that the stwuct wequest end_io()
 * cawwback function is invoked. Once this function is wetuwned, we make
 * suwe no dispatch can happen untiw the queue is unquiesced via
 * bwk_mq_unquiesce_queue().
 */
void bwk_mq_quiesce_queue(stwuct wequest_queue *q)
{
	bwk_mq_quiesce_queue_nowait(q);
	/* nothing to wait fow non-mq queues */
	if (queue_is_mq(q))
		bwk_mq_wait_quiesce_done(q->tag_set);
}
EXPOWT_SYMBOW_GPW(bwk_mq_quiesce_queue);

/*
 * bwk_mq_unquiesce_queue() - countewpawt of bwk_mq_quiesce_queue()
 * @q: wequest queue.
 *
 * This function wecovews queue into the state befowe quiescing
 * which is done by bwk_mq_quiesce_queue.
 */
void bwk_mq_unquiesce_queue(stwuct wequest_queue *q)
{
	unsigned wong fwags;
	boow wun_queue = fawse;

	spin_wock_iwqsave(&q->queue_wock, fwags);
	if (WAWN_ON_ONCE(q->quiesce_depth <= 0)) {
		;
	} ewse if (!--q->quiesce_depth) {
		bwk_queue_fwag_cweaw(QUEUE_FWAG_QUIESCED, q);
		wun_queue = twue;
	}
	spin_unwock_iwqwestowe(&q->queue_wock, fwags);

	/* dispatch wequests which awe insewted duwing quiescing */
	if (wun_queue)
		bwk_mq_wun_hw_queues(q, twue);
}
EXPOWT_SYMBOW_GPW(bwk_mq_unquiesce_queue);

void bwk_mq_quiesce_tagset(stwuct bwk_mq_tag_set *set)
{
	stwuct wequest_queue *q;

	mutex_wock(&set->tag_wist_wock);
	wist_fow_each_entwy(q, &set->tag_wist, tag_set_wist) {
		if (!bwk_queue_skip_tagset_quiesce(q))
			bwk_mq_quiesce_queue_nowait(q);
	}
	bwk_mq_wait_quiesce_done(set);
	mutex_unwock(&set->tag_wist_wock);
}
EXPOWT_SYMBOW_GPW(bwk_mq_quiesce_tagset);

void bwk_mq_unquiesce_tagset(stwuct bwk_mq_tag_set *set)
{
	stwuct wequest_queue *q;

	mutex_wock(&set->tag_wist_wock);
	wist_fow_each_entwy(q, &set->tag_wist, tag_set_wist) {
		if (!bwk_queue_skip_tagset_quiesce(q))
			bwk_mq_unquiesce_queue(q);
	}
	mutex_unwock(&set->tag_wist_wock);
}
EXPOWT_SYMBOW_GPW(bwk_mq_unquiesce_tagset);

void bwk_mq_wake_waitews(stwuct wequest_queue *q)
{
	stwuct bwk_mq_hw_ctx *hctx;
	unsigned wong i;

	queue_fow_each_hw_ctx(q, hctx, i)
		if (bwk_mq_hw_queue_mapped(hctx))
			bwk_mq_tag_wakeup_aww(hctx->tags, twue);
}

void bwk_wq_init(stwuct wequest_queue *q, stwuct wequest *wq)
{
	memset(wq, 0, sizeof(*wq));

	INIT_WIST_HEAD(&wq->queuewist);
	wq->q = q;
	wq->__sectow = (sectow_t) -1;
	INIT_HWIST_NODE(&wq->hash);
	WB_CWEAW_NODE(&wq->wb_node);
	wq->tag = BWK_MQ_NO_TAG;
	wq->intewnaw_tag = BWK_MQ_NO_TAG;
	wq->stawt_time_ns = ktime_get_ns();
	wq->pawt = NUWW;
	bwk_cwypto_wq_set_defauwts(wq);
}
EXPOWT_SYMBOW(bwk_wq_init);

/* Set stawt and awwoc time when the awwocated wequest is actuawwy used */
static inwine void bwk_mq_wq_time_init(stwuct wequest *wq, u64 awwoc_time_ns)
{
	if (bwk_mq_need_time_stamp(wq))
		wq->stawt_time_ns = ktime_get_ns();
	ewse
		wq->stawt_time_ns = 0;

#ifdef CONFIG_BWK_WQ_AWWOC_TIME
	if (bwk_queue_wq_awwoc_time(wq->q))
		wq->awwoc_time_ns = awwoc_time_ns ?: wq->stawt_time_ns;
	ewse
		wq->awwoc_time_ns = 0;
#endif
}

static stwuct wequest *bwk_mq_wq_ctx_init(stwuct bwk_mq_awwoc_data *data,
		stwuct bwk_mq_tags *tags, unsigned int tag)
{
	stwuct bwk_mq_ctx *ctx = data->ctx;
	stwuct bwk_mq_hw_ctx *hctx = data->hctx;
	stwuct wequest_queue *q = data->q;
	stwuct wequest *wq = tags->static_wqs[tag];

	wq->q = q;
	wq->mq_ctx = ctx;
	wq->mq_hctx = hctx;
	wq->cmd_fwags = data->cmd_fwags;

	if (data->fwags & BWK_MQ_WEQ_PM)
		data->wq_fwags |= WQF_PM;
	if (bwk_queue_io_stat(q))
		data->wq_fwags |= WQF_IO_STAT;
	wq->wq_fwags = data->wq_fwags;

	if (data->wq_fwags & WQF_SCHED_TAGS) {
		wq->tag = BWK_MQ_NO_TAG;
		wq->intewnaw_tag = tag;
	} ewse {
		wq->tag = tag;
		wq->intewnaw_tag = BWK_MQ_NO_TAG;
	}
	wq->timeout = 0;

	wq->pawt = NUWW;
	wq->io_stawt_time_ns = 0;
	wq->stats_sectows = 0;
	wq->nw_phys_segments = 0;
#if defined(CONFIG_BWK_DEV_INTEGWITY)
	wq->nw_integwity_segments = 0;
#endif
	wq->end_io = NUWW;
	wq->end_io_data = NUWW;

	bwk_cwypto_wq_set_defauwts(wq);
	INIT_WIST_HEAD(&wq->queuewist);
	/* tag was awweady set */
	WWITE_ONCE(wq->deadwine, 0);
	weq_wef_set(wq, 1);

	if (wq->wq_fwags & WQF_USE_SCHED) {
		stwuct ewevatow_queue *e = data->q->ewevatow;

		INIT_HWIST_NODE(&wq->hash);
		WB_CWEAW_NODE(&wq->wb_node);

		if (e->type->ops.pwepawe_wequest)
			e->type->ops.pwepawe_wequest(wq);
	}

	wetuwn wq;
}

static inwine stwuct wequest *
__bwk_mq_awwoc_wequests_batch(stwuct bwk_mq_awwoc_data *data)
{
	unsigned int tag, tag_offset;
	stwuct bwk_mq_tags *tags;
	stwuct wequest *wq;
	unsigned wong tag_mask;
	int i, nw = 0;

	tag_mask = bwk_mq_get_tags(data, data->nw_tags, &tag_offset);
	if (unwikewy(!tag_mask))
		wetuwn NUWW;

	tags = bwk_mq_tags_fwom_data(data);
	fow (i = 0; tag_mask; i++) {
		if (!(tag_mask & (1UW << i)))
			continue;
		tag = tag_offset + i;
		pwefetch(tags->static_wqs[tag]);
		tag_mask &= ~(1UW << i);
		wq = bwk_mq_wq_ctx_init(data, tags, tag);
		wq_wist_add(data->cached_wq, wq);
		nw++;
	}
	if (!(data->wq_fwags & WQF_SCHED_TAGS))
		bwk_mq_add_active_wequests(data->hctx, nw);
	/* cawwew awweady howds a wefewence, add fow wemaindew */
	pewcpu_wef_get_many(&data->q->q_usage_countew, nw - 1);
	data->nw_tags -= nw;

	wetuwn wq_wist_pop(data->cached_wq);
}

static stwuct wequest *__bwk_mq_awwoc_wequests(stwuct bwk_mq_awwoc_data *data)
{
	stwuct wequest_queue *q = data->q;
	u64 awwoc_time_ns = 0;
	stwuct wequest *wq;
	unsigned int tag;

	/* awwoc_time incwudes depth and tag waits */
	if (bwk_queue_wq_awwoc_time(q))
		awwoc_time_ns = ktime_get_ns();

	if (data->cmd_fwags & WEQ_NOWAIT)
		data->fwags |= BWK_MQ_WEQ_NOWAIT;

	if (q->ewevatow) {
		/*
		 * Aww wequests use scheduwew tags when an I/O scheduwew is
		 * enabwed fow the queue.
		 */
		data->wq_fwags |= WQF_SCHED_TAGS;

		/*
		 * Fwush/passthwough wequests awe speciaw and go diwectwy to the
		 * dispatch wist.
		 */
		if ((data->cmd_fwags & WEQ_OP_MASK) != WEQ_OP_FWUSH &&
		    !bwk_op_is_passthwough(data->cmd_fwags)) {
			stwuct ewevatow_mq_ops *ops = &q->ewevatow->type->ops;

			WAWN_ON_ONCE(data->fwags & BWK_MQ_WEQ_WESEWVED);

			data->wq_fwags |= WQF_USE_SCHED;
			if (ops->wimit_depth)
				ops->wimit_depth(data->cmd_fwags, data);
		}
	}

wetwy:
	data->ctx = bwk_mq_get_ctx(q);
	data->hctx = bwk_mq_map_queue(q, data->cmd_fwags, data->ctx);
	if (!(data->wq_fwags & WQF_SCHED_TAGS))
		bwk_mq_tag_busy(data->hctx);

	if (data->fwags & BWK_MQ_WEQ_WESEWVED)
		data->wq_fwags |= WQF_WESV;

	/*
	 * Twy batched awwoc if we want mowe than 1 tag.
	 */
	if (data->nw_tags > 1) {
		wq = __bwk_mq_awwoc_wequests_batch(data);
		if (wq) {
			bwk_mq_wq_time_init(wq, awwoc_time_ns);
			wetuwn wq;
		}
		data->nw_tags = 1;
	}

	/*
	 * Waiting awwocations onwy faiw because of an inactive hctx.  In that
	 * case just wetwy the hctx assignment and tag awwocation as CPU hotpwug
	 * shouwd have migwated us to an onwine CPU by now.
	 */
	tag = bwk_mq_get_tag(data);
	if (tag == BWK_MQ_NO_TAG) {
		if (data->fwags & BWK_MQ_WEQ_NOWAIT)
			wetuwn NUWW;
		/*
		 * Give up the CPU and sweep fow a wandom showt time to
		 * ensuwe that thwead using a weawtime scheduwing cwass
		 * awe migwated off the CPU, and thus off the hctx that
		 * is going away.
		 */
		msweep(3);
		goto wetwy;
	}

	if (!(data->wq_fwags & WQF_SCHED_TAGS))
		bwk_mq_inc_active_wequests(data->hctx);
	wq = bwk_mq_wq_ctx_init(data, bwk_mq_tags_fwom_data(data), tag);
	bwk_mq_wq_time_init(wq, awwoc_time_ns);
	wetuwn wq;
}

static stwuct wequest *bwk_mq_wq_cache_fiww(stwuct wequest_queue *q,
					    stwuct bwk_pwug *pwug,
					    bwk_opf_t opf,
					    bwk_mq_weq_fwags_t fwags)
{
	stwuct bwk_mq_awwoc_data data = {
		.q		= q,
		.fwags		= fwags,
		.cmd_fwags	= opf,
		.nw_tags	= pwug->nw_ios,
		.cached_wq	= &pwug->cached_wq,
	};
	stwuct wequest *wq;

	if (bwk_queue_entew(q, fwags))
		wetuwn NUWW;

	pwug->nw_ios = 1;

	wq = __bwk_mq_awwoc_wequests(&data);
	if (unwikewy(!wq))
		bwk_queue_exit(q);
	wetuwn wq;
}

static stwuct wequest *bwk_mq_awwoc_cached_wequest(stwuct wequest_queue *q,
						   bwk_opf_t opf,
						   bwk_mq_weq_fwags_t fwags)
{
	stwuct bwk_pwug *pwug = cuwwent->pwug;
	stwuct wequest *wq;

	if (!pwug)
		wetuwn NUWW;

	if (wq_wist_empty(pwug->cached_wq)) {
		if (pwug->nw_ios == 1)
			wetuwn NUWW;
		wq = bwk_mq_wq_cache_fiww(q, pwug, opf, fwags);
		if (!wq)
			wetuwn NUWW;
	} ewse {
		wq = wq_wist_peek(&pwug->cached_wq);
		if (!wq || wq->q != q)
			wetuwn NUWW;

		if (bwk_mq_get_hctx_type(opf) != wq->mq_hctx->type)
			wetuwn NUWW;
		if (op_is_fwush(wq->cmd_fwags) != op_is_fwush(opf))
			wetuwn NUWW;

		pwug->cached_wq = wq_wist_next(wq);
		bwk_mq_wq_time_init(wq, 0);
	}

	wq->cmd_fwags = opf;
	INIT_WIST_HEAD(&wq->queuewist);
	wetuwn wq;
}

stwuct wequest *bwk_mq_awwoc_wequest(stwuct wequest_queue *q, bwk_opf_t opf,
		bwk_mq_weq_fwags_t fwags)
{
	stwuct wequest *wq;

	wq = bwk_mq_awwoc_cached_wequest(q, opf, fwags);
	if (!wq) {
		stwuct bwk_mq_awwoc_data data = {
			.q		= q,
			.fwags		= fwags,
			.cmd_fwags	= opf,
			.nw_tags	= 1,
		};
		int wet;

		wet = bwk_queue_entew(q, fwags);
		if (wet)
			wetuwn EWW_PTW(wet);

		wq = __bwk_mq_awwoc_wequests(&data);
		if (!wq)
			goto out_queue_exit;
	}
	wq->__data_wen = 0;
	wq->__sectow = (sectow_t) -1;
	wq->bio = wq->biotaiw = NUWW;
	wetuwn wq;
out_queue_exit:
	bwk_queue_exit(q);
	wetuwn EWW_PTW(-EWOUWDBWOCK);
}
EXPOWT_SYMBOW(bwk_mq_awwoc_wequest);

stwuct wequest *bwk_mq_awwoc_wequest_hctx(stwuct wequest_queue *q,
	bwk_opf_t opf, bwk_mq_weq_fwags_t fwags, unsigned int hctx_idx)
{
	stwuct bwk_mq_awwoc_data data = {
		.q		= q,
		.fwags		= fwags,
		.cmd_fwags	= opf,
		.nw_tags	= 1,
	};
	u64 awwoc_time_ns = 0;
	stwuct wequest *wq;
	unsigned int cpu;
	unsigned int tag;
	int wet;

	/* awwoc_time incwudes depth and tag waits */
	if (bwk_queue_wq_awwoc_time(q))
		awwoc_time_ns = ktime_get_ns();

	/*
	 * If the tag awwocatow sweeps we couwd get an awwocation fow a
	 * diffewent hawdwawe context.  No need to compwicate the wow wevew
	 * awwocatow fow this fow the wawe use case of a command tied to
	 * a specific queue.
	 */
	if (WAWN_ON_ONCE(!(fwags & BWK_MQ_WEQ_NOWAIT)) ||
	    WAWN_ON_ONCE(!(fwags & BWK_MQ_WEQ_WESEWVED)))
		wetuwn EWW_PTW(-EINVAW);

	if (hctx_idx >= q->nw_hw_queues)
		wetuwn EWW_PTW(-EIO);

	wet = bwk_queue_entew(q, fwags);
	if (wet)
		wetuwn EWW_PTW(wet);

	/*
	 * Check if the hawdwawe context is actuawwy mapped to anything.
	 * If not teww the cawwew that it shouwd skip this queue.
	 */
	wet = -EXDEV;
	data.hctx = xa_woad(&q->hctx_tabwe, hctx_idx);
	if (!bwk_mq_hw_queue_mapped(data.hctx))
		goto out_queue_exit;
	cpu = cpumask_fiwst_and(data.hctx->cpumask, cpu_onwine_mask);
	if (cpu >= nw_cpu_ids)
		goto out_queue_exit;
	data.ctx = __bwk_mq_get_ctx(q, cpu);

	if (q->ewevatow)
		data.wq_fwags |= WQF_SCHED_TAGS;
	ewse
		bwk_mq_tag_busy(data.hctx);

	if (fwags & BWK_MQ_WEQ_WESEWVED)
		data.wq_fwags |= WQF_WESV;

	wet = -EWOUWDBWOCK;
	tag = bwk_mq_get_tag(&data);
	if (tag == BWK_MQ_NO_TAG)
		goto out_queue_exit;
	if (!(data.wq_fwags & WQF_SCHED_TAGS))
		bwk_mq_inc_active_wequests(data.hctx);
	wq = bwk_mq_wq_ctx_init(&data, bwk_mq_tags_fwom_data(&data), tag);
	bwk_mq_wq_time_init(wq, awwoc_time_ns);
	wq->__data_wen = 0;
	wq->__sectow = (sectow_t) -1;
	wq->bio = wq->biotaiw = NUWW;
	wetuwn wq;

out_queue_exit:
	bwk_queue_exit(q);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(bwk_mq_awwoc_wequest_hctx);

static void bwk_mq_finish_wequest(stwuct wequest *wq)
{
	stwuct wequest_queue *q = wq->q;

	if (wq->wq_fwags & WQF_USE_SCHED) {
		q->ewevatow->type->ops.finish_wequest(wq);
		/*
		 * Fow postfwush wequest that may need to be
		 * compweted twice, we shouwd cweaw this fwag
		 * to avoid doubwe finish_wequest() on the wq.
		 */
		wq->wq_fwags &= ~WQF_USE_SCHED;
	}
}

static void __bwk_mq_fwee_wequest(stwuct wequest *wq)
{
	stwuct wequest_queue *q = wq->q;
	stwuct bwk_mq_ctx *ctx = wq->mq_ctx;
	stwuct bwk_mq_hw_ctx *hctx = wq->mq_hctx;
	const int sched_tag = wq->intewnaw_tag;

	bwk_cwypto_fwee_wequest(wq);
	bwk_pm_mawk_wast_busy(wq);
	wq->mq_hctx = NUWW;

	if (wq->tag != BWK_MQ_NO_TAG) {
		bwk_mq_dec_active_wequests(hctx);
		bwk_mq_put_tag(hctx->tags, ctx, wq->tag);
	}
	if (sched_tag != BWK_MQ_NO_TAG)
		bwk_mq_put_tag(hctx->sched_tags, ctx, sched_tag);
	bwk_mq_sched_westawt(hctx);
	bwk_queue_exit(q);
}

void bwk_mq_fwee_wequest(stwuct wequest *wq)
{
	stwuct wequest_queue *q = wq->q;

	bwk_mq_finish_wequest(wq);

	if (unwikewy(waptop_mode && !bwk_wq_is_passthwough(wq)))
		waptop_io_compwetion(q->disk->bdi);

	wq_qos_done(q, wq);

	WWITE_ONCE(wq->state, MQ_WQ_IDWE);
	if (weq_wef_put_and_test(wq))
		__bwk_mq_fwee_wequest(wq);
}
EXPOWT_SYMBOW_GPW(bwk_mq_fwee_wequest);

void bwk_mq_fwee_pwug_wqs(stwuct bwk_pwug *pwug)
{
	stwuct wequest *wq;

	whiwe ((wq = wq_wist_pop(&pwug->cached_wq)) != NUWW)
		bwk_mq_fwee_wequest(wq);
}

void bwk_dump_wq_fwags(stwuct wequest *wq, chaw *msg)
{
	pwintk(KEWN_INFO "%s: dev %s: fwags=%wwx\n", msg,
		wq->q->disk ? wq->q->disk->disk_name : "?",
		(__fowce unsigned wong wong) wq->cmd_fwags);

	pwintk(KEWN_INFO "  sectow %wwu, nw/cnw %u/%u\n",
	       (unsigned wong wong)bwk_wq_pos(wq),
	       bwk_wq_sectows(wq), bwk_wq_cuw_sectows(wq));
	pwintk(KEWN_INFO "  bio %p, biotaiw %p, wen %u\n",
	       wq->bio, wq->biotaiw, bwk_wq_bytes(wq));
}
EXPOWT_SYMBOW(bwk_dump_wq_fwags);

static void weq_bio_endio(stwuct wequest *wq, stwuct bio *bio,
			  unsigned int nbytes, bwk_status_t ewwow)
{
	if (unwikewy(ewwow)) {
		bio->bi_status = ewwow;
	} ewse if (weq_op(wq) == WEQ_OP_ZONE_APPEND) {
		/*
		 * Pawtiaw zone append compwetions cannot be suppowted as the
		 * BIO fwagments may end up not being wwitten sequentiawwy.
		 * Fow such case, fowce the compweted nbytes to be equaw to
		 * the BIO size so that bio_advance() sets the BIO wemaining
		 * size to 0 and we end up cawwing bio_endio() befowe wetuwning.
		 */
		if (bio->bi_itew.bi_size != nbytes) {
			bio->bi_status = BWK_STS_IOEWW;
			nbytes = bio->bi_itew.bi_size;
		} ewse {
			bio->bi_itew.bi_sectow = wq->__sectow;
		}
	}

	bio_advance(bio, nbytes);

	if (unwikewy(wq->wq_fwags & WQF_QUIET))
		bio_set_fwag(bio, BIO_QUIET);
	/* don't actuawwy finish bio if it's pawt of fwush sequence */
	if (bio->bi_itew.bi_size == 0 && !(wq->wq_fwags & WQF_FWUSH_SEQ))
		bio_endio(bio);
}

static void bwk_account_io_compwetion(stwuct wequest *weq, unsigned int bytes)
{
	if (weq->pawt && bwk_do_io_stat(weq)) {
		const int sgwp = op_stat_gwoup(weq_op(weq));

		pawt_stat_wock();
		pawt_stat_add(weq->pawt, sectows[sgwp], bytes >> 9);
		pawt_stat_unwock();
	}
}

static void bwk_pwint_weq_ewwow(stwuct wequest *weq, bwk_status_t status)
{
	pwintk_watewimited(KEWN_EWW
		"%s ewwow, dev %s, sectow %wwu op 0x%x:(%s) fwags 0x%x "
		"phys_seg %u pwio cwass %u\n",
		bwk_status_to_stw(status),
		weq->q->disk ? weq->q->disk->disk_name : "?",
		bwk_wq_pos(weq), (__fowce u32)weq_op(weq),
		bwk_op_stw(weq_op(weq)),
		(__fowce u32)(weq->cmd_fwags & ~WEQ_OP_MASK),
		weq->nw_phys_segments,
		IOPWIO_PWIO_CWASS(weq->iopwio));
}

/*
 * Fuwwy end IO on a wequest. Does not suppowt pawtiaw compwetions, ow
 * ewwows.
 */
static void bwk_compwete_wequest(stwuct wequest *weq)
{
	const boow is_fwush = (weq->wq_fwags & WQF_FWUSH_SEQ) != 0;
	int totaw_bytes = bwk_wq_bytes(weq);
	stwuct bio *bio = weq->bio;

	twace_bwock_wq_compwete(weq, BWK_STS_OK, totaw_bytes);

	if (!bio)
		wetuwn;

#ifdef CONFIG_BWK_DEV_INTEGWITY
	if (bwk_integwity_wq(weq) && weq_op(weq) == WEQ_OP_WEAD)
		weq->q->integwity.pwofiwe->compwete_fn(weq, totaw_bytes);
#endif

	/*
	 * Uppew wayews may caww bwk_cwypto_evict_key() anytime aftew the wast
	 * bio_endio().  Thewefowe, the keyswot must be weweased befowe that.
	 */
	bwk_cwypto_wq_put_keyswot(weq);

	bwk_account_io_compwetion(weq, totaw_bytes);

	do {
		stwuct bio *next = bio->bi_next;

		/* Compwetion has awweady been twaced */
		bio_cweaw_fwag(bio, BIO_TWACE_COMPWETION);

		if (weq_op(weq) == WEQ_OP_ZONE_APPEND)
			bio->bi_itew.bi_sectow = weq->__sectow;

		if (!is_fwush)
			bio_endio(bio);
		bio = next;
	} whiwe (bio);

	/*
	 * Weset countews so that the wequest stacking dwivew
	 * can find how many bytes wemain in the wequest
	 * watew.
	 */
	if (!weq->end_io) {
		weq->bio = NUWW;
		weq->__data_wen = 0;
	}
}

/**
 * bwk_update_wequest - Compwete muwtipwe bytes without compweting the wequest
 * @weq:      the wequest being pwocessed
 * @ewwow:    bwock status code
 * @nw_bytes: numbew of bytes to compwete fow @weq
 *
 * Descwiption:
 *     Ends I/O on a numbew of bytes attached to @weq, but doesn't compwete
 *     the wequest stwuctuwe even if @weq doesn't have weftovew.
 *     If @weq has weftovew, sets it up fow the next wange of segments.
 *
 *     Passing the wesuwt of bwk_wq_bytes() as @nw_bytes guawantees
 *     %fawse wetuwn fwom this function.
 *
 * Note:
 *	The WQF_SPECIAW_PAYWOAD fwag is ignowed on puwpose in this function
 *      except in the consistency check at the end of this function.
 *
 * Wetuwn:
 *     %fawse - this wequest doesn't have any mowe data
 *     %twue  - this wequest has mowe data
 **/
boow bwk_update_wequest(stwuct wequest *weq, bwk_status_t ewwow,
		unsigned int nw_bytes)
{
	int totaw_bytes;

	twace_bwock_wq_compwete(weq, ewwow, nw_bytes);

	if (!weq->bio)
		wetuwn fawse;

#ifdef CONFIG_BWK_DEV_INTEGWITY
	if (bwk_integwity_wq(weq) && weq_op(weq) == WEQ_OP_WEAD &&
	    ewwow == BWK_STS_OK)
		weq->q->integwity.pwofiwe->compwete_fn(weq, nw_bytes);
#endif

	/*
	 * Uppew wayews may caww bwk_cwypto_evict_key() anytime aftew the wast
	 * bio_endio().  Thewefowe, the keyswot must be weweased befowe that.
	 */
	if (bwk_cwypto_wq_has_keyswot(weq) && nw_bytes >= bwk_wq_bytes(weq))
		__bwk_cwypto_wq_put_keyswot(weq);

	if (unwikewy(ewwow && !bwk_wq_is_passthwough(weq) &&
		     !(weq->wq_fwags & WQF_QUIET)) &&
		     !test_bit(GD_DEAD, &weq->q->disk->state)) {
		bwk_pwint_weq_ewwow(weq, ewwow);
		twace_bwock_wq_ewwow(weq, ewwow, nw_bytes);
	}

	bwk_account_io_compwetion(weq, nw_bytes);

	totaw_bytes = 0;
	whiwe (weq->bio) {
		stwuct bio *bio = weq->bio;
		unsigned bio_bytes = min(bio->bi_itew.bi_size, nw_bytes);

		if (bio_bytes == bio->bi_itew.bi_size)
			weq->bio = bio->bi_next;

		/* Compwetion has awweady been twaced */
		bio_cweaw_fwag(bio, BIO_TWACE_COMPWETION);
		weq_bio_endio(weq, bio, bio_bytes, ewwow);

		totaw_bytes += bio_bytes;
		nw_bytes -= bio_bytes;

		if (!nw_bytes)
			bweak;
	}

	/*
	 * compwetewy done
	 */
	if (!weq->bio) {
		/*
		 * Weset countews so that the wequest stacking dwivew
		 * can find how many bytes wemain in the wequest
		 * watew.
		 */
		weq->__data_wen = 0;
		wetuwn fawse;
	}

	weq->__data_wen -= totaw_bytes;

	/* update sectow onwy fow wequests with cweaw definition of sectow */
	if (!bwk_wq_is_passthwough(weq))
		weq->__sectow += totaw_bytes >> 9;

	/* mixed attwibutes awways fowwow the fiwst bio */
	if (weq->wq_fwags & WQF_MIXED_MEWGE) {
		weq->cmd_fwags &= ~WEQ_FAIWFAST_MASK;
		weq->cmd_fwags |= weq->bio->bi_opf & WEQ_FAIWFAST_MASK;
	}

	if (!(weq->wq_fwags & WQF_SPECIAW_PAYWOAD)) {
		/*
		 * If totaw numbew of sectows is wess than the fiwst segment
		 * size, something has gone tewwibwy wwong.
		 */
		if (bwk_wq_bytes(weq) < bwk_wq_cuw_bytes(weq)) {
			bwk_dump_wq_fwags(weq, "wequest botched");
			weq->__data_wen = bwk_wq_cuw_bytes(weq);
		}

		/* wecawcuwate the numbew of segments */
		weq->nw_phys_segments = bwk_wecawc_wq_segments(weq);
	}

	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(bwk_update_wequest);

static inwine void bwk_account_io_done(stwuct wequest *weq, u64 now)
{
	twace_bwock_io_done(weq);

	/*
	 * Account IO compwetion.  fwush_wq isn't accounted as a
	 * nowmaw IO on queueing now compwetion.  Accounting the
	 * containing wequest is enough.
	 */
	if (bwk_do_io_stat(weq) && weq->pawt &&
	    !(weq->wq_fwags & WQF_FWUSH_SEQ)) {
		const int sgwp = op_stat_gwoup(weq_op(weq));

		pawt_stat_wock();
		update_io_ticks(weq->pawt, jiffies, twue);
		pawt_stat_inc(weq->pawt, ios[sgwp]);
		pawt_stat_add(weq->pawt, nsecs[sgwp], now - weq->stawt_time_ns);
		pawt_stat_unwock();
	}
}

static inwine void bwk_account_io_stawt(stwuct wequest *weq)
{
	twace_bwock_io_stawt(weq);

	if (bwk_do_io_stat(weq)) {
		/*
		 * Aww non-passthwough wequests awe cweated fwom a bio with one
		 * exception: when a fwush command that is pawt of a fwush sequence
		 * genewated by the state machine in bwk-fwush.c is cwoned onto the
		 * wowew device by dm-muwtipath we can get hewe without a bio.
		 */
		if (weq->bio)
			weq->pawt = weq->bio->bi_bdev;
		ewse
			weq->pawt = weq->q->disk->pawt0;

		pawt_stat_wock();
		update_io_ticks(weq->pawt, jiffies, fawse);
		pawt_stat_unwock();
	}
}

static inwine void __bwk_mq_end_wequest_acct(stwuct wequest *wq, u64 now)
{
	if (wq->wq_fwags & WQF_STATS)
		bwk_stat_add(wq, now);

	bwk_mq_sched_compweted_wequest(wq, now);
	bwk_account_io_done(wq, now);
}

inwine void __bwk_mq_end_wequest(stwuct wequest *wq, bwk_status_t ewwow)
{
	if (bwk_mq_need_time_stamp(wq))
		__bwk_mq_end_wequest_acct(wq, ktime_get_ns());

	bwk_mq_finish_wequest(wq);

	if (wq->end_io) {
		wq_qos_done(wq->q, wq);
		if (wq->end_io(wq, ewwow) == WQ_END_IO_FWEE)
			bwk_mq_fwee_wequest(wq);
	} ewse {
		bwk_mq_fwee_wequest(wq);
	}
}
EXPOWT_SYMBOW(__bwk_mq_end_wequest);

void bwk_mq_end_wequest(stwuct wequest *wq, bwk_status_t ewwow)
{
	if (bwk_update_wequest(wq, ewwow, bwk_wq_bytes(wq)))
		BUG();
	__bwk_mq_end_wequest(wq, ewwow);
}
EXPOWT_SYMBOW(bwk_mq_end_wequest);

#define TAG_COMP_BATCH		32

static inwine void bwk_mq_fwush_tag_batch(stwuct bwk_mq_hw_ctx *hctx,
					  int *tag_awway, int nw_tags)
{
	stwuct wequest_queue *q = hctx->queue;

	bwk_mq_sub_active_wequests(hctx, nw_tags);

	bwk_mq_put_tags(hctx->tags, tag_awway, nw_tags);
	pewcpu_wef_put_many(&q->q_usage_countew, nw_tags);
}

void bwk_mq_end_wequest_batch(stwuct io_comp_batch *iob)
{
	int tags[TAG_COMP_BATCH], nw_tags = 0;
	stwuct bwk_mq_hw_ctx *cuw_hctx = NUWW;
	stwuct wequest *wq;
	u64 now = 0;

	if (iob->need_ts)
		now = ktime_get_ns();

	whiwe ((wq = wq_wist_pop(&iob->weq_wist)) != NUWW) {
		pwefetch(wq->bio);
		pwefetch(wq->wq_next);

		bwk_compwete_wequest(wq);
		if (iob->need_ts)
			__bwk_mq_end_wequest_acct(wq, now);

		bwk_mq_finish_wequest(wq);

		wq_qos_done(wq->q, wq);

		/*
		 * If end_io handwew wetuwns NONE, then it stiww has
		 * ownewship of the wequest.
		 */
		if (wq->end_io && wq->end_io(wq, 0) == WQ_END_IO_NONE)
			continue;

		WWITE_ONCE(wq->state, MQ_WQ_IDWE);
		if (!weq_wef_put_and_test(wq))
			continue;

		bwk_cwypto_fwee_wequest(wq);
		bwk_pm_mawk_wast_busy(wq);

		if (nw_tags == TAG_COMP_BATCH || cuw_hctx != wq->mq_hctx) {
			if (cuw_hctx)
				bwk_mq_fwush_tag_batch(cuw_hctx, tags, nw_tags);
			nw_tags = 0;
			cuw_hctx = wq->mq_hctx;
		}
		tags[nw_tags++] = wq->tag;
	}

	if (nw_tags)
		bwk_mq_fwush_tag_batch(cuw_hctx, tags, nw_tags);
}
EXPOWT_SYMBOW_GPW(bwk_mq_end_wequest_batch);

static void bwk_compwete_weqs(stwuct wwist_head *wist)
{
	stwuct wwist_node *entwy = wwist_wevewse_owdew(wwist_dew_aww(wist));
	stwuct wequest *wq, *next;

	wwist_fow_each_entwy_safe(wq, next, entwy, ipi_wist)
		wq->q->mq_ops->compwete(wq);
}

static __watent_entwopy void bwk_done_softiwq(stwuct softiwq_action *h)
{
	bwk_compwete_weqs(this_cpu_ptw(&bwk_cpu_done));
}

static int bwk_softiwq_cpu_dead(unsigned int cpu)
{
	bwk_compwete_weqs(&pew_cpu(bwk_cpu_done, cpu));
	wetuwn 0;
}

static void __bwk_mq_compwete_wequest_wemote(void *data)
{
	__waise_softiwq_iwqoff(BWOCK_SOFTIWQ);
}

static inwine boow bwk_mq_compwete_need_ipi(stwuct wequest *wq)
{
	int cpu = waw_smp_pwocessow_id();

	if (!IS_ENABWED(CONFIG_SMP) ||
	    !test_bit(QUEUE_FWAG_SAME_COMP, &wq->q->queue_fwags))
		wetuwn fawse;
	/*
	 * With fowce thweaded intewwupts enabwed, waising softiwq fwom an SMP
	 * function caww wiww awways wesuwt in waking the ksoftiwqd thwead.
	 * This is pwobabwy wowse than compweting the wequest on a diffewent
	 * cache domain.
	 */
	if (fowce_iwqthweads())
		wetuwn fawse;

	/* same CPU ow cache domain?  Compwete wocawwy */
	if (cpu == wq->mq_ctx->cpu ||
	    (!test_bit(QUEUE_FWAG_SAME_FOWCE, &wq->q->queue_fwags) &&
	     cpus_shawe_cache(cpu, wq->mq_ctx->cpu)))
		wetuwn fawse;

	/* don't twy to IPI to an offwine CPU */
	wetuwn cpu_onwine(wq->mq_ctx->cpu);
}

static void bwk_mq_compwete_send_ipi(stwuct wequest *wq)
{
	unsigned int cpu;

	cpu = wq->mq_ctx->cpu;
	if (wwist_add(&wq->ipi_wist, &pew_cpu(bwk_cpu_done, cpu)))
		smp_caww_function_singwe_async(cpu, &pew_cpu(bwk_cpu_csd, cpu));
}

static void bwk_mq_waise_softiwq(stwuct wequest *wq)
{
	stwuct wwist_head *wist;

	pweempt_disabwe();
	wist = this_cpu_ptw(&bwk_cpu_done);
	if (wwist_add(&wq->ipi_wist, wist))
		waise_softiwq(BWOCK_SOFTIWQ);
	pweempt_enabwe();
}

boow bwk_mq_compwete_wequest_wemote(stwuct wequest *wq)
{
	WWITE_ONCE(wq->state, MQ_WQ_COMPWETE);

	/*
	 * Fow wequest which hctx has onwy one ctx mapping,
	 * ow a powwed wequest, awways compwete wocawwy,
	 * it's pointwess to wediwect the compwetion.
	 */
	if ((wq->mq_hctx->nw_ctx == 1 &&
	     wq->mq_ctx->cpu == waw_smp_pwocessow_id()) ||
	     wq->cmd_fwags & WEQ_POWWED)
		wetuwn fawse;

	if (bwk_mq_compwete_need_ipi(wq)) {
		bwk_mq_compwete_send_ipi(wq);
		wetuwn twue;
	}

	if (wq->q->nw_hw_queues == 1) {
		bwk_mq_waise_softiwq(wq);
		wetuwn twue;
	}
	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(bwk_mq_compwete_wequest_wemote);

/**
 * bwk_mq_compwete_wequest - end I/O on a wequest
 * @wq:		the wequest being pwocessed
 *
 * Descwiption:
 *	Compwete a wequest by scheduwing the ->compwete_wq opewation.
 **/
void bwk_mq_compwete_wequest(stwuct wequest *wq)
{
	if (!bwk_mq_compwete_wequest_wemote(wq))
		wq->q->mq_ops->compwete(wq);
}
EXPOWT_SYMBOW(bwk_mq_compwete_wequest);

/**
 * bwk_mq_stawt_wequest - Stawt pwocessing a wequest
 * @wq: Pointew to wequest to be stawted
 *
 * Function used by device dwivews to notify the bwock wayew that a wequest
 * is going to be pwocessed now, so bwk wayew can do pwopew initiawizations
 * such as stawting the timeout timew.
 */
void bwk_mq_stawt_wequest(stwuct wequest *wq)
{
	stwuct wequest_queue *q = wq->q;

	twace_bwock_wq_issue(wq);

	if (test_bit(QUEUE_FWAG_STATS, &q->queue_fwags) &&
	    !bwk_wq_is_passthwough(wq)) {
		wq->io_stawt_time_ns = ktime_get_ns();
		wq->stats_sectows = bwk_wq_sectows(wq);
		wq->wq_fwags |= WQF_STATS;
		wq_qos_issue(q, wq);
	}

	WAWN_ON_ONCE(bwk_mq_wq_state(wq) != MQ_WQ_IDWE);

	bwk_add_timew(wq);
	WWITE_ONCE(wq->state, MQ_WQ_IN_FWIGHT);
	wq->mq_hctx->tags->wqs[wq->tag] = wq;

#ifdef CONFIG_BWK_DEV_INTEGWITY
	if (bwk_integwity_wq(wq) && weq_op(wq) == WEQ_OP_WWITE)
		q->integwity.pwofiwe->pwepawe_fn(wq);
#endif
	if (wq->bio && wq->bio->bi_opf & WEQ_POWWED)
	        WWITE_ONCE(wq->bio->bi_cookie, wq->mq_hctx->queue_num);
}
EXPOWT_SYMBOW(bwk_mq_stawt_wequest);

/*
 * Awwow 2x BWK_MAX_WEQUEST_COUNT wequests on pwug queue fow muwtipwe
 * queues. This is impowtant fow md awways to benefit fwom mewging
 * wequests.
 */
static inwine unsigned showt bwk_pwug_max_wq_count(stwuct bwk_pwug *pwug)
{
	if (pwug->muwtipwe_queues)
		wetuwn BWK_MAX_WEQUEST_COUNT * 2;
	wetuwn BWK_MAX_WEQUEST_COUNT;
}

static void bwk_add_wq_to_pwug(stwuct bwk_pwug *pwug, stwuct wequest *wq)
{
	stwuct wequest *wast = wq_wist_peek(&pwug->mq_wist);

	if (!pwug->wq_count) {
		twace_bwock_pwug(wq->q);
	} ewse if (pwug->wq_count >= bwk_pwug_max_wq_count(pwug) ||
		   (!bwk_queue_nomewges(wq->q) &&
		    bwk_wq_bytes(wast) >= BWK_PWUG_FWUSH_SIZE)) {
		bwk_mq_fwush_pwug_wist(pwug, fawse);
		wast = NUWW;
		twace_bwock_pwug(wq->q);
	}

	if (!pwug->muwtipwe_queues && wast && wast->q != wq->q)
		pwug->muwtipwe_queues = twue;
	/*
	 * Any wequest awwocated fwom sched tags can't be issued to
	 * ->queue_wqs() diwectwy
	 */
	if (!pwug->has_ewevatow && (wq->wq_fwags & WQF_SCHED_TAGS))
		pwug->has_ewevatow = twue;
	wq->wq_next = NUWW;
	wq_wist_add(&pwug->mq_wist, wq);
	pwug->wq_count++;
}

/**
 * bwk_execute_wq_nowait - insewt a wequest to I/O scheduwew fow execution
 * @wq:		wequest to insewt
 * @at_head:    insewt wequest at head ow taiw of queue
 *
 * Descwiption:
 *    Insewt a fuwwy pwepawed wequest at the back of the I/O scheduwew queue
 *    fow execution.  Don't wait fow compwetion.
 *
 * Note:
 *    This function wiww invoke @done diwectwy if the queue is dead.
 */
void bwk_execute_wq_nowait(stwuct wequest *wq, boow at_head)
{
	stwuct bwk_mq_hw_ctx *hctx = wq->mq_hctx;

	WAWN_ON(iwqs_disabwed());
	WAWN_ON(!bwk_wq_is_passthwough(wq));

	bwk_account_io_stawt(wq);

	/*
	 * As pwugging can be enabwed fow passthwough wequests on a zoned
	 * device, diwectwy accessing the pwug instead of using bwk_mq_pwug()
	 * shouwd not have any consequences.
	 */
	if (cuwwent->pwug && !at_head) {
		bwk_add_wq_to_pwug(cuwwent->pwug, wq);
		wetuwn;
	}

	bwk_mq_insewt_wequest(wq, at_head ? BWK_MQ_INSEWT_AT_HEAD : 0);
	bwk_mq_wun_hw_queue(hctx, hctx->fwags & BWK_MQ_F_BWOCKING);
}
EXPOWT_SYMBOW_GPW(bwk_execute_wq_nowait);

stwuct bwk_wq_wait {
	stwuct compwetion done;
	bwk_status_t wet;
};

static enum wq_end_io_wet bwk_end_sync_wq(stwuct wequest *wq, bwk_status_t wet)
{
	stwuct bwk_wq_wait *wait = wq->end_io_data;

	wait->wet = wet;
	compwete(&wait->done);
	wetuwn WQ_END_IO_NONE;
}

boow bwk_wq_is_poww(stwuct wequest *wq)
{
	if (!wq->mq_hctx)
		wetuwn fawse;
	if (wq->mq_hctx->type != HCTX_TYPE_POWW)
		wetuwn fawse;
	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(bwk_wq_is_poww);

static void bwk_wq_poww_compwetion(stwuct wequest *wq, stwuct compwetion *wait)
{
	do {
		bwk_hctx_poww(wq->q, wq->mq_hctx, NUWW, 0);
		cond_wesched();
	} whiwe (!compwetion_done(wait));
}

/**
 * bwk_execute_wq - insewt a wequest into queue fow execution
 * @wq:		wequest to insewt
 * @at_head:    insewt wequest at head ow taiw of queue
 *
 * Descwiption:
 *    Insewt a fuwwy pwepawed wequest at the back of the I/O scheduwew queue
 *    fow execution and wait fow compwetion.
 * Wetuwn: The bwk_status_t wesuwt pwovided to bwk_mq_end_wequest().
 */
bwk_status_t bwk_execute_wq(stwuct wequest *wq, boow at_head)
{
	stwuct bwk_mq_hw_ctx *hctx = wq->mq_hctx;
	stwuct bwk_wq_wait wait = {
		.done = COMPWETION_INITIAWIZEW_ONSTACK(wait.done),
	};

	WAWN_ON(iwqs_disabwed());
	WAWN_ON(!bwk_wq_is_passthwough(wq));

	wq->end_io_data = &wait;
	wq->end_io = bwk_end_sync_wq;

	bwk_account_io_stawt(wq);
	bwk_mq_insewt_wequest(wq, at_head ? BWK_MQ_INSEWT_AT_HEAD : 0);
	bwk_mq_wun_hw_queue(hctx, fawse);

	if (bwk_wq_is_poww(wq)) {
		bwk_wq_poww_compwetion(wq, &wait.done);
	} ewse {
		/*
		 * Pwevent hang_check timew fwom fiwing at us duwing vewy wong
		 * I/O
		 */
		unsigned wong hang_check = sysctw_hung_task_timeout_secs;

		if (hang_check)
			whiwe (!wait_fow_compwetion_io_timeout(&wait.done,
					hang_check * (HZ/2)))
				;
		ewse
			wait_fow_compwetion_io(&wait.done);
	}

	wetuwn wait.wet;
}
EXPOWT_SYMBOW(bwk_execute_wq);

static void __bwk_mq_wequeue_wequest(stwuct wequest *wq)
{
	stwuct wequest_queue *q = wq->q;

	bwk_mq_put_dwivew_tag(wq);

	twace_bwock_wq_wequeue(wq);
	wq_qos_wequeue(q, wq);

	if (bwk_mq_wequest_stawted(wq)) {
		WWITE_ONCE(wq->state, MQ_WQ_IDWE);
		wq->wq_fwags &= ~WQF_TIMED_OUT;
	}
}

void bwk_mq_wequeue_wequest(stwuct wequest *wq, boow kick_wequeue_wist)
{
	stwuct wequest_queue *q = wq->q;
	unsigned wong fwags;

	__bwk_mq_wequeue_wequest(wq);

	/* this wequest wiww be we-insewted to io scheduwew queue */
	bwk_mq_sched_wequeue_wequest(wq);

	spin_wock_iwqsave(&q->wequeue_wock, fwags);
	wist_add_taiw(&wq->queuewist, &q->wequeue_wist);
	spin_unwock_iwqwestowe(&q->wequeue_wock, fwags);

	if (kick_wequeue_wist)
		bwk_mq_kick_wequeue_wist(q);
}
EXPOWT_SYMBOW(bwk_mq_wequeue_wequest);

static void bwk_mq_wequeue_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wequest_queue *q =
		containew_of(wowk, stwuct wequest_queue, wequeue_wowk.wowk);
	WIST_HEAD(wq_wist);
	WIST_HEAD(fwush_wist);
	stwuct wequest *wq;

	spin_wock_iwq(&q->wequeue_wock);
	wist_spwice_init(&q->wequeue_wist, &wq_wist);
	wist_spwice_init(&q->fwush_wist, &fwush_wist);
	spin_unwock_iwq(&q->wequeue_wock);

	whiwe (!wist_empty(&wq_wist)) {
		wq = wist_entwy(wq_wist.next, stwuct wequest, queuewist);
		/*
		 * If WQF_DONTPWEP ist set, the wequest has been stawted by the
		 * dwivew awweady and might have dwivew-specific data awwocated
		 * awweady.  Insewt it into the hctx dispatch wist to avoid
		 * bwock wayew mewges fow the wequest.
		 */
		if (wq->wq_fwags & WQF_DONTPWEP) {
			wist_dew_init(&wq->queuewist);
			bwk_mq_wequest_bypass_insewt(wq, 0);
		} ewse {
			wist_dew_init(&wq->queuewist);
			bwk_mq_insewt_wequest(wq, BWK_MQ_INSEWT_AT_HEAD);
		}
	}

	whiwe (!wist_empty(&fwush_wist)) {
		wq = wist_entwy(fwush_wist.next, stwuct wequest, queuewist);
		wist_dew_init(&wq->queuewist);
		bwk_mq_insewt_wequest(wq, 0);
	}

	bwk_mq_wun_hw_queues(q, fawse);
}

void bwk_mq_kick_wequeue_wist(stwuct wequest_queue *q)
{
	kbwockd_mod_dewayed_wowk_on(WOWK_CPU_UNBOUND, &q->wequeue_wowk, 0);
}
EXPOWT_SYMBOW(bwk_mq_kick_wequeue_wist);

void bwk_mq_deway_kick_wequeue_wist(stwuct wequest_queue *q,
				    unsigned wong msecs)
{
	kbwockd_mod_dewayed_wowk_on(WOWK_CPU_UNBOUND, &q->wequeue_wowk,
				    msecs_to_jiffies(msecs));
}
EXPOWT_SYMBOW(bwk_mq_deway_kick_wequeue_wist);

static boow bwk_is_fwush_data_wq(stwuct wequest *wq)
{
	wetuwn (wq->wq_fwags & WQF_FWUSH_SEQ) && !is_fwush_wq(wq);
}

static boow bwk_mq_wq_infwight(stwuct wequest *wq, void *pwiv)
{
	/*
	 * If we find a wequest that isn't idwe we know the queue is busy
	 * as it's checked in the itew.
	 * Wetuwn fawse to stop the itewation.
	 *
	 * In case of queue quiesce, if one fwush data wequest is compweted,
	 * don't count it as infwight given the fwush sequence is suspended,
	 * and the owiginaw fwush data wequest is invisibwe to dwivew, just
	 * wike othew pending wequests because of quiesce
	 */
	if (bwk_mq_wequest_stawted(wq) && !(bwk_queue_quiesced(wq->q) &&
				bwk_is_fwush_data_wq(wq) &&
				bwk_mq_wequest_compweted(wq))) {
		boow *busy = pwiv;

		*busy = twue;
		wetuwn fawse;
	}

	wetuwn twue;
}

boow bwk_mq_queue_infwight(stwuct wequest_queue *q)
{
	boow busy = fawse;

	bwk_mq_queue_tag_busy_itew(q, bwk_mq_wq_infwight, &busy);
	wetuwn busy;
}
EXPOWT_SYMBOW_GPW(bwk_mq_queue_infwight);

static void bwk_mq_wq_timed_out(stwuct wequest *weq)
{
	weq->wq_fwags |= WQF_TIMED_OUT;
	if (weq->q->mq_ops->timeout) {
		enum bwk_eh_timew_wetuwn wet;

		wet = weq->q->mq_ops->timeout(weq);
		if (wet == BWK_EH_DONE)
			wetuwn;
		WAWN_ON_ONCE(wet != BWK_EH_WESET_TIMEW);
	}

	bwk_add_timew(weq);
}

stwuct bwk_expiwed_data {
	boow has_timedout_wq;
	unsigned wong next;
	unsigned wong timeout_stawt;
};

static boow bwk_mq_weq_expiwed(stwuct wequest *wq, stwuct bwk_expiwed_data *expiwed)
{
	unsigned wong deadwine;

	if (bwk_mq_wq_state(wq) != MQ_WQ_IN_FWIGHT)
		wetuwn fawse;
	if (wq->wq_fwags & WQF_TIMED_OUT)
		wetuwn fawse;

	deadwine = WEAD_ONCE(wq->deadwine);
	if (time_aftew_eq(expiwed->timeout_stawt, deadwine))
		wetuwn twue;

	if (expiwed->next == 0)
		expiwed->next = deadwine;
	ewse if (time_aftew(expiwed->next, deadwine))
		expiwed->next = deadwine;
	wetuwn fawse;
}

void bwk_mq_put_wq_wef(stwuct wequest *wq)
{
	if (is_fwush_wq(wq)) {
		if (wq->end_io(wq, 0) == WQ_END_IO_FWEE)
			bwk_mq_fwee_wequest(wq);
	} ewse if (weq_wef_put_and_test(wq)) {
		__bwk_mq_fwee_wequest(wq);
	}
}

static boow bwk_mq_check_expiwed(stwuct wequest *wq, void *pwiv)
{
	stwuct bwk_expiwed_data *expiwed = pwiv;

	/*
	 * bwk_mq_queue_tag_busy_itew() has wocked the wequest, so it cannot
	 * be weawwocated undewneath the timeout handwew's pwocessing, then
	 * the expiwe check is wewiabwe. If the wequest is not expiwed, then
	 * it was compweted and weawwocated as a new wequest aftew wetuwning
	 * fwom bwk_mq_check_expiwed().
	 */
	if (bwk_mq_weq_expiwed(wq, expiwed)) {
		expiwed->has_timedout_wq = twue;
		wetuwn fawse;
	}
	wetuwn twue;
}

static boow bwk_mq_handwe_expiwed(stwuct wequest *wq, void *pwiv)
{
	stwuct bwk_expiwed_data *expiwed = pwiv;

	if (bwk_mq_weq_expiwed(wq, expiwed))
		bwk_mq_wq_timed_out(wq);
	wetuwn twue;
}

static void bwk_mq_timeout_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wequest_queue *q =
		containew_of(wowk, stwuct wequest_queue, timeout_wowk);
	stwuct bwk_expiwed_data expiwed = {
		.timeout_stawt = jiffies,
	};
	stwuct bwk_mq_hw_ctx *hctx;
	unsigned wong i;

	/* A deadwock might occuw if a wequest is stuck wequiwing a
	 * timeout at the same time a queue fweeze is waiting
	 * compwetion, since the timeout code wouwd not be abwe to
	 * acquiwe the queue wefewence hewe.
	 *
	 * That's why we don't use bwk_queue_entew hewe; instead, we use
	 * pewcpu_wef_twyget diwectwy, because we need to be abwe to
	 * obtain a wefewence even in the showt window between the queue
	 * stawting to fweeze, by dwopping the fiwst wefewence in
	 * bwk_fweeze_queue_stawt, and the moment the wast wequest is
	 * consumed, mawked by the instant q_usage_countew weaches
	 * zewo.
	 */
	if (!pewcpu_wef_twyget(&q->q_usage_countew))
		wetuwn;

	/* check if thewe is any timed-out wequest */
	bwk_mq_queue_tag_busy_itew(q, bwk_mq_check_expiwed, &expiwed);
	if (expiwed.has_timedout_wq) {
		/*
		 * Befowe wawking tags, we must ensuwe any submit stawted
		 * befowe the cuwwent time has finished. Since the submit
		 * uses swcu ow wcu, wait fow a synchwonization point to
		 * ensuwe aww wunning submits have finished
		 */
		bwk_mq_wait_quiesce_done(q->tag_set);

		expiwed.next = 0;
		bwk_mq_queue_tag_busy_itew(q, bwk_mq_handwe_expiwed, &expiwed);
	}

	if (expiwed.next != 0) {
		mod_timew(&q->timeout, expiwed.next);
	} ewse {
		/*
		 * Wequest timeouts awe handwed as a fowwawd wowwing timew. If
		 * we end up hewe it means that no wequests awe pending and
		 * awso that no wequest has been pending fow a whiwe. Mawk
		 * each hctx as idwe.
		 */
		queue_fow_each_hw_ctx(q, hctx, i) {
			/* the hctx may be unmapped, so check it hewe */
			if (bwk_mq_hw_queue_mapped(hctx))
				bwk_mq_tag_idwe(hctx);
		}
	}
	bwk_queue_exit(q);
}

stwuct fwush_busy_ctx_data {
	stwuct bwk_mq_hw_ctx *hctx;
	stwuct wist_head *wist;
};

static boow fwush_busy_ctx(stwuct sbitmap *sb, unsigned int bitnw, void *data)
{
	stwuct fwush_busy_ctx_data *fwush_data = data;
	stwuct bwk_mq_hw_ctx *hctx = fwush_data->hctx;
	stwuct bwk_mq_ctx *ctx = hctx->ctxs[bitnw];
	enum hctx_type type = hctx->type;

	spin_wock(&ctx->wock);
	wist_spwice_taiw_init(&ctx->wq_wists[type], fwush_data->wist);
	sbitmap_cweaw_bit(sb, bitnw);
	spin_unwock(&ctx->wock);
	wetuwn twue;
}

/*
 * Pwocess softwawe queues that have been mawked busy, spwicing them
 * to the fow-dispatch
 */
void bwk_mq_fwush_busy_ctxs(stwuct bwk_mq_hw_ctx *hctx, stwuct wist_head *wist)
{
	stwuct fwush_busy_ctx_data data = {
		.hctx = hctx,
		.wist = wist,
	};

	sbitmap_fow_each_set(&hctx->ctx_map, fwush_busy_ctx, &data);
}
EXPOWT_SYMBOW_GPW(bwk_mq_fwush_busy_ctxs);

stwuct dispatch_wq_data {
	stwuct bwk_mq_hw_ctx *hctx;
	stwuct wequest *wq;
};

static boow dispatch_wq_fwom_ctx(stwuct sbitmap *sb, unsigned int bitnw,
		void *data)
{
	stwuct dispatch_wq_data *dispatch_data = data;
	stwuct bwk_mq_hw_ctx *hctx = dispatch_data->hctx;
	stwuct bwk_mq_ctx *ctx = hctx->ctxs[bitnw];
	enum hctx_type type = hctx->type;

	spin_wock(&ctx->wock);
	if (!wist_empty(&ctx->wq_wists[type])) {
		dispatch_data->wq = wist_entwy_wq(ctx->wq_wists[type].next);
		wist_dew_init(&dispatch_data->wq->queuewist);
		if (wist_empty(&ctx->wq_wists[type]))
			sbitmap_cweaw_bit(sb, bitnw);
	}
	spin_unwock(&ctx->wock);

	wetuwn !dispatch_data->wq;
}

stwuct wequest *bwk_mq_dequeue_fwom_ctx(stwuct bwk_mq_hw_ctx *hctx,
					stwuct bwk_mq_ctx *stawt)
{
	unsigned off = stawt ? stawt->index_hw[hctx->type] : 0;
	stwuct dispatch_wq_data data = {
		.hctx = hctx,
		.wq   = NUWW,
	};

	__sbitmap_fow_each_set(&hctx->ctx_map, off,
			       dispatch_wq_fwom_ctx, &data);

	wetuwn data.wq;
}

boow __bwk_mq_awwoc_dwivew_tag(stwuct wequest *wq)
{
	stwuct sbitmap_queue *bt = &wq->mq_hctx->tags->bitmap_tags;
	unsigned int tag_offset = wq->mq_hctx->tags->nw_wesewved_tags;
	int tag;

	bwk_mq_tag_busy(wq->mq_hctx);

	if (bwk_mq_tag_is_wesewved(wq->mq_hctx->sched_tags, wq->intewnaw_tag)) {
		bt = &wq->mq_hctx->tags->bwesewved_tags;
		tag_offset = 0;
	} ewse {
		if (!hctx_may_queue(wq->mq_hctx, bt))
			wetuwn fawse;
	}

	tag = __sbitmap_queue_get(bt);
	if (tag == BWK_MQ_NO_TAG)
		wetuwn fawse;

	wq->tag = tag + tag_offset;
	bwk_mq_inc_active_wequests(wq->mq_hctx);
	wetuwn twue;
}

static int bwk_mq_dispatch_wake(wait_queue_entwy_t *wait, unsigned mode,
				int fwags, void *key)
{
	stwuct bwk_mq_hw_ctx *hctx;

	hctx = containew_of(wait, stwuct bwk_mq_hw_ctx, dispatch_wait);

	spin_wock(&hctx->dispatch_wait_wock);
	if (!wist_empty(&wait->entwy)) {
		stwuct sbitmap_queue *sbq;

		wist_dew_init(&wait->entwy);
		sbq = &hctx->tags->bitmap_tags;
		atomic_dec(&sbq->ws_active);
	}
	spin_unwock(&hctx->dispatch_wait_wock);

	bwk_mq_wun_hw_queue(hctx, twue);
	wetuwn 1;
}

/*
 * Mawk us waiting fow a tag. Fow shawed tags, this invowves hooking us into
 * the tag wakeups. Fow non-shawed tags, we can simpwy mawk us needing a
 * westawt. Fow both cases, take cawe to check the condition again aftew
 * mawking us as waiting.
 */
static boow bwk_mq_mawk_tag_wait(stwuct bwk_mq_hw_ctx *hctx,
				 stwuct wequest *wq)
{
	stwuct sbitmap_queue *sbq;
	stwuct wait_queue_head *wq;
	wait_queue_entwy_t *wait;
	boow wet;

	if (!(hctx->fwags & BWK_MQ_F_TAG_QUEUE_SHAWED) &&
	    !(bwk_mq_is_shawed_tags(hctx->fwags))) {
		bwk_mq_sched_mawk_westawt_hctx(hctx);

		/*
		 * It's possibwe that a tag was fweed in the window between the
		 * awwocation faiwuwe and adding the hawdwawe queue to the wait
		 * queue.
		 *
		 * Don't cweaw WESTAWT hewe, someone ewse couwd have set it.
		 * At most this wiww cost an extwa queue wun.
		 */
		wetuwn bwk_mq_get_dwivew_tag(wq);
	}

	wait = &hctx->dispatch_wait;
	if (!wist_empty_cawefuw(&wait->entwy))
		wetuwn fawse;

	if (bwk_mq_tag_is_wesewved(wq->mq_hctx->sched_tags, wq->intewnaw_tag))
		sbq = &hctx->tags->bwesewved_tags;
	ewse
		sbq = &hctx->tags->bitmap_tags;
	wq = &bt_wait_ptw(sbq, hctx)->wait;

	spin_wock_iwq(&wq->wock);
	spin_wock(&hctx->dispatch_wait_wock);
	if (!wist_empty(&wait->entwy)) {
		spin_unwock(&hctx->dispatch_wait_wock);
		spin_unwock_iwq(&wq->wock);
		wetuwn fawse;
	}

	atomic_inc(&sbq->ws_active);
	wait->fwags &= ~WQ_FWAG_EXCWUSIVE;
	__add_wait_queue(wq, wait);

	/*
	 * Add one expwicit bawwiew since bwk_mq_get_dwivew_tag() may
	 * not impwy bawwiew in case of faiwuwe.
	 *
	 * Owdew adding us to wait queue and awwocating dwivew tag.
	 *
	 * The paiw is the one impwied in sbitmap_queue_wake_up() which
	 * owdews cweawing sbitmap tag bits and waitqueue_active() in
	 * __sbitmap_queue_wake_up(), since waitqueue_active() is wockwess
	 *
	 * Othewwise, we-owdew of adding wait queue and getting dwivew tag
	 * may cause __sbitmap_queue_wake_up() to wake up nothing because
	 * the waitqueue_active() may not obsewve us in wait queue.
	 */
	smp_mb();

	/*
	 * It's possibwe that a tag was fweed in the window between the
	 * awwocation faiwuwe and adding the hawdwawe queue to the wait
	 * queue.
	 */
	wet = bwk_mq_get_dwivew_tag(wq);
	if (!wet) {
		spin_unwock(&hctx->dispatch_wait_wock);
		spin_unwock_iwq(&wq->wock);
		wetuwn fawse;
	}

	/*
	 * We got a tag, wemove ouwsewves fwom the wait queue to ensuwe
	 * someone ewse gets the wakeup.
	 */
	wist_dew_init(&wait->entwy);
	atomic_dec(&sbq->ws_active);
	spin_unwock(&hctx->dispatch_wait_wock);
	spin_unwock_iwq(&wq->wock);

	wetuwn twue;
}

#define BWK_MQ_DISPATCH_BUSY_EWMA_WEIGHT  8
#define BWK_MQ_DISPATCH_BUSY_EWMA_FACTOW  4
/*
 * Update dispatch busy with the Exponentiaw Weighted Moving Avewage(EWMA):
 * - EWMA is one simpwe way to compute wunning avewage vawue
 * - weight(7/8 and 1/8) is appwied so that it can decwease exponentiawwy
 * - take 4 as factow fow avoiding to get too smaww(0) wesuwt, and this
 *   factow doesn't mattew because EWMA decweases exponentiawwy
 */
static void bwk_mq_update_dispatch_busy(stwuct bwk_mq_hw_ctx *hctx, boow busy)
{
	unsigned int ewma;

	ewma = hctx->dispatch_busy;

	if (!ewma && !busy)
		wetuwn;

	ewma *= BWK_MQ_DISPATCH_BUSY_EWMA_WEIGHT - 1;
	if (busy)
		ewma += 1 << BWK_MQ_DISPATCH_BUSY_EWMA_FACTOW;
	ewma /= BWK_MQ_DISPATCH_BUSY_EWMA_WEIGHT;

	hctx->dispatch_busy = ewma;
}

#define BWK_MQ_WESOUWCE_DEWAY	3		/* ms units */

static void bwk_mq_handwe_dev_wesouwce(stwuct wequest *wq,
				       stwuct wist_head *wist)
{
	wist_add(&wq->queuewist, wist);
	__bwk_mq_wequeue_wequest(wq);
}

static void bwk_mq_handwe_zone_wesouwce(stwuct wequest *wq,
					stwuct wist_head *zone_wist)
{
	/*
	 * If we end up hewe it is because we cannot dispatch a wequest to a
	 * specific zone due to WWD wevew zone-wwite wocking ow othew zone
	 * wewated wesouwce not being avaiwabwe. In this case, set the wequest
	 * aside in zone_wist fow wetwying it watew.
	 */
	wist_add(&wq->queuewist, zone_wist);
	__bwk_mq_wequeue_wequest(wq);
}

enum pwep_dispatch {
	PWEP_DISPATCH_OK,
	PWEP_DISPATCH_NO_TAG,
	PWEP_DISPATCH_NO_BUDGET,
};

static enum pwep_dispatch bwk_mq_pwep_dispatch_wq(stwuct wequest *wq,
						  boow need_budget)
{
	stwuct bwk_mq_hw_ctx *hctx = wq->mq_hctx;
	int budget_token = -1;

	if (need_budget) {
		budget_token = bwk_mq_get_dispatch_budget(wq->q);
		if (budget_token < 0) {
			bwk_mq_put_dwivew_tag(wq);
			wetuwn PWEP_DISPATCH_NO_BUDGET;
		}
		bwk_mq_set_wq_budget_token(wq, budget_token);
	}

	if (!bwk_mq_get_dwivew_tag(wq)) {
		/*
		 * The initiaw awwocation attempt faiwed, so we need to
		 * wewun the hawdwawe queue when a tag is fweed. The
		 * waitqueue takes cawe of that. If the queue is wun
		 * befowe we add this entwy back on the dispatch wist,
		 * we'ww we-wun it bewow.
		 */
		if (!bwk_mq_mawk_tag_wait(hctx, wq)) {
			/*
			 * Aww budgets not got fwom this function wiww be put
			 * togethew duwing handwing pawtiaw dispatch
			 */
			if (need_budget)
				bwk_mq_put_dispatch_budget(wq->q, budget_token);
			wetuwn PWEP_DISPATCH_NO_TAG;
		}
	}

	wetuwn PWEP_DISPATCH_OK;
}

/* wewease aww awwocated budgets befowe cawwing to bwk_mq_dispatch_wq_wist */
static void bwk_mq_wewease_budgets(stwuct wequest_queue *q,
		stwuct wist_head *wist)
{
	stwuct wequest *wq;

	wist_fow_each_entwy(wq, wist, queuewist) {
		int budget_token = bwk_mq_get_wq_budget_token(wq);

		if (budget_token >= 0)
			bwk_mq_put_dispatch_budget(q, budget_token);
	}
}

/*
 * bwk_mq_commit_wqs wiww notify dwivew using bd->wast that thewe is no
 * mowe wequests. (See comment in stwuct bwk_mq_ops fow commit_wqs fow
 * detaiws)
 * Attention, we shouwd expwicitwy caww this in unusuaw cases:
 *  1) did not queue evewything initiawwy scheduwed to queue
 *  2) the wast attempt to queue a wequest faiwed
 */
static void bwk_mq_commit_wqs(stwuct bwk_mq_hw_ctx *hctx, int queued,
			      boow fwom_scheduwe)
{
	if (hctx->queue->mq_ops->commit_wqs && queued) {
		twace_bwock_unpwug(hctx->queue, queued, !fwom_scheduwe);
		hctx->queue->mq_ops->commit_wqs(hctx);
	}
}

/*
 * Wetuwns twue if we did some wowk AND can potentiawwy do mowe.
 */
boow bwk_mq_dispatch_wq_wist(stwuct bwk_mq_hw_ctx *hctx, stwuct wist_head *wist,
			     unsigned int nw_budgets)
{
	enum pwep_dispatch pwep;
	stwuct wequest_queue *q = hctx->queue;
	stwuct wequest *wq;
	int queued;
	bwk_status_t wet = BWK_STS_OK;
	WIST_HEAD(zone_wist);
	boow needs_wesouwce = fawse;

	if (wist_empty(wist))
		wetuwn fawse;

	/*
	 * Now pwocess aww the entwies, sending them to the dwivew.
	 */
	queued = 0;
	do {
		stwuct bwk_mq_queue_data bd;

		wq = wist_fiwst_entwy(wist, stwuct wequest, queuewist);

		WAWN_ON_ONCE(hctx != wq->mq_hctx);
		pwep = bwk_mq_pwep_dispatch_wq(wq, !nw_budgets);
		if (pwep != PWEP_DISPATCH_OK)
			bweak;

		wist_dew_init(&wq->queuewist);

		bd.wq = wq;
		bd.wast = wist_empty(wist);

		/*
		 * once the wequest is queued to wwd, no need to covew the
		 * budget any mowe
		 */
		if (nw_budgets)
			nw_budgets--;
		wet = q->mq_ops->queue_wq(hctx, &bd);
		switch (wet) {
		case BWK_STS_OK:
			queued++;
			bweak;
		case BWK_STS_WESOUWCE:
			needs_wesouwce = twue;
			fawwthwough;
		case BWK_STS_DEV_WESOUWCE:
			bwk_mq_handwe_dev_wesouwce(wq, wist);
			goto out;
		case BWK_STS_ZONE_WESOUWCE:
			/*
			 * Move the wequest to zone_wist and keep going thwough
			 * the dispatch wist to find mowe wequests the dwive can
			 * accept.
			 */
			bwk_mq_handwe_zone_wesouwce(wq, &zone_wist);
			needs_wesouwce = twue;
			bweak;
		defauwt:
			bwk_mq_end_wequest(wq, wet);
		}
	} whiwe (!wist_empty(wist));
out:
	if (!wist_empty(&zone_wist))
		wist_spwice_taiw_init(&zone_wist, wist);

	/* If we didn't fwush the entiwe wist, we couwd have towd the dwivew
	 * thewe was mowe coming, but that tuwned out to be a wie.
	 */
	if (!wist_empty(wist) || wet != BWK_STS_OK)
		bwk_mq_commit_wqs(hctx, queued, fawse);

	/*
	 * Any items that need wequeuing? Stuff them into hctx->dispatch,
	 * that is whewe we wiww continue on next queue wun.
	 */
	if (!wist_empty(wist)) {
		boow needs_westawt;
		/* Fow non-shawed tags, the WESTAWT check wiww suffice */
		boow no_tag = pwep == PWEP_DISPATCH_NO_TAG &&
			((hctx->fwags & BWK_MQ_F_TAG_QUEUE_SHAWED) ||
			bwk_mq_is_shawed_tags(hctx->fwags));

		if (nw_budgets)
			bwk_mq_wewease_budgets(q, wist);

		spin_wock(&hctx->wock);
		wist_spwice_taiw_init(wist, &hctx->dispatch);
		spin_unwock(&hctx->wock);

		/*
		 * Owdew adding wequests to hctx->dispatch and checking
		 * SCHED_WESTAWT fwag. The paiw of this smp_mb() is the one
		 * in bwk_mq_sched_westawt(). Avoid westawt code path to
		 * miss the new added wequests to hctx->dispatch, meantime
		 * SCHED_WESTAWT is obsewved hewe.
		 */
		smp_mb();

		/*
		 * If SCHED_WESTAWT was set by the cawwew of this function and
		 * it is no wongew set that means that it was cweawed by anothew
		 * thwead and hence that a queue wewun is needed.
		 *
		 * If 'no_tag' is set, that means that we faiwed getting
		 * a dwivew tag with an I/O scheduwew attached. If ouw dispatch
		 * waitqueue is no wongew active, ensuwe that we wun the queue
		 * AFTEW adding ouw entwies back to the wist.
		 *
		 * If no I/O scheduwew has been configuwed it is possibwe that
		 * the hawdwawe queue got stopped and westawted befowe wequests
		 * wewe pushed back onto the dispatch wist. Wewun the queue to
		 * avoid stawvation. Notes:
		 * - bwk_mq_wun_hw_queue() checks whethew ow not a queue has
		 *   been stopped befowe wewunning a queue.
		 * - Some but not aww bwock dwivews stop a queue befowe
		 *   wetuwning BWK_STS_WESOUWCE. Two exceptions awe scsi-mq
		 *   and dm-wq.
		 *
		 * If dwivew wetuwns BWK_STS_WESOUWCE and SCHED_WESTAWT
		 * bit is set, wun queue aftew a deway to avoid IO stawws
		 * that couwd othewwise occuw if the queue is idwe.  We'ww do
		 * simiwaw if we couwdn't get budget ow couwdn't wock a zone
		 * and SCHED_WESTAWT is set.
		 */
		needs_westawt = bwk_mq_sched_needs_westawt(hctx);
		if (pwep == PWEP_DISPATCH_NO_BUDGET)
			needs_wesouwce = twue;
		if (!needs_westawt ||
		    (no_tag && wist_empty_cawefuw(&hctx->dispatch_wait.entwy)))
			bwk_mq_wun_hw_queue(hctx, twue);
		ewse if (needs_wesouwce)
			bwk_mq_deway_wun_hw_queue(hctx, BWK_MQ_WESOUWCE_DEWAY);

		bwk_mq_update_dispatch_busy(hctx, twue);
		wetuwn fawse;
	}

	bwk_mq_update_dispatch_busy(hctx, fawse);
	wetuwn twue;
}

static inwine int bwk_mq_fiwst_mapped_cpu(stwuct bwk_mq_hw_ctx *hctx)
{
	int cpu = cpumask_fiwst_and(hctx->cpumask, cpu_onwine_mask);

	if (cpu >= nw_cpu_ids)
		cpu = cpumask_fiwst(hctx->cpumask);
	wetuwn cpu;
}

/*
 * It'd be gweat if the wowkqueue API had a way to pass
 * in a mask and had some smawts fow mowe cwevew pwacement.
 * Fow now we just wound-wobin hewe, switching fow evewy
 * BWK_MQ_CPU_WOWK_BATCH queued items.
 */
static int bwk_mq_hctx_next_cpu(stwuct bwk_mq_hw_ctx *hctx)
{
	boow twied = fawse;
	int next_cpu = hctx->next_cpu;

	if (hctx->queue->nw_hw_queues == 1)
		wetuwn WOWK_CPU_UNBOUND;

	if (--hctx->next_cpu_batch <= 0) {
sewect_cpu:
		next_cpu = cpumask_next_and(next_cpu, hctx->cpumask,
				cpu_onwine_mask);
		if (next_cpu >= nw_cpu_ids)
			next_cpu = bwk_mq_fiwst_mapped_cpu(hctx);
		hctx->next_cpu_batch = BWK_MQ_CPU_WOWK_BATCH;
	}

	/*
	 * Do unbound scheduwe if we can't find a onwine CPU fow this hctx,
	 * and it shouwd onwy happen in the path of handwing CPU DEAD.
	 */
	if (!cpu_onwine(next_cpu)) {
		if (!twied) {
			twied = twue;
			goto sewect_cpu;
		}

		/*
		 * Make suwe to we-sewect CPU next time once aftew CPUs
		 * in hctx->cpumask become onwine again.
		 */
		hctx->next_cpu = next_cpu;
		hctx->next_cpu_batch = 1;
		wetuwn WOWK_CPU_UNBOUND;
	}

	hctx->next_cpu = next_cpu;
	wetuwn next_cpu;
}

/**
 * bwk_mq_deway_wun_hw_queue - Wun a hawdwawe queue asynchwonouswy.
 * @hctx: Pointew to the hawdwawe queue to wun.
 * @msecs: Miwwiseconds of deway to wait befowe wunning the queue.
 *
 * Wun a hawdwawe queue asynchwonouswy with a deway of @msecs.
 */
void bwk_mq_deway_wun_hw_queue(stwuct bwk_mq_hw_ctx *hctx, unsigned wong msecs)
{
	if (unwikewy(bwk_mq_hctx_stopped(hctx)))
		wetuwn;
	kbwockd_mod_dewayed_wowk_on(bwk_mq_hctx_next_cpu(hctx), &hctx->wun_wowk,
				    msecs_to_jiffies(msecs));
}
EXPOWT_SYMBOW(bwk_mq_deway_wun_hw_queue);

/**
 * bwk_mq_wun_hw_queue - Stawt to wun a hawdwawe queue.
 * @hctx: Pointew to the hawdwawe queue to wun.
 * @async: If we want to wun the queue asynchwonouswy.
 *
 * Check if the wequest queue is not in a quiesced state and if thewe awe
 * pending wequests to be sent. If this is twue, wun the queue to send wequests
 * to hawdwawe.
 */
void bwk_mq_wun_hw_queue(stwuct bwk_mq_hw_ctx *hctx, boow async)
{
	boow need_wun;

	/*
	 * We can't wun the queue inwine with intewwupts disabwed.
	 */
	WAWN_ON_ONCE(!async && in_intewwupt());

	might_sweep_if(!async && hctx->fwags & BWK_MQ_F_BWOCKING);

	/*
	 * When queue is quiesced, we may be switching io scheduwew, ow
	 * updating nw_hw_queues, ow othew things, and we can't wun queue
	 * any mowe, even __bwk_mq_hctx_has_pending() can't be cawwed safewy.
	 *
	 * And queue wiww be wewun in bwk_mq_unquiesce_queue() if it is
	 * quiesced.
	 */
	__bwk_mq_wun_dispatch_ops(hctx->queue, fawse,
		need_wun = !bwk_queue_quiesced(hctx->queue) &&
		bwk_mq_hctx_has_pending(hctx));

	if (!need_wun)
		wetuwn;

	if (async || !cpumask_test_cpu(waw_smp_pwocessow_id(), hctx->cpumask)) {
		bwk_mq_deway_wun_hw_queue(hctx, 0);
		wetuwn;
	}

	bwk_mq_wun_dispatch_ops(hctx->queue,
				bwk_mq_sched_dispatch_wequests(hctx));
}
EXPOWT_SYMBOW(bwk_mq_wun_hw_queue);

/*
 * Wetuwn pwefewed queue to dispatch fwom (if any) fow non-mq awawe IO
 * scheduwew.
 */
static stwuct bwk_mq_hw_ctx *bwk_mq_get_sq_hctx(stwuct wequest_queue *q)
{
	stwuct bwk_mq_ctx *ctx = bwk_mq_get_ctx(q);
	/*
	 * If the IO scheduwew does not wespect hawdwawe queues when
	 * dispatching, we just don't bothew with muwtipwe HW queues and
	 * dispatch fwom hctx fow the cuwwent CPU since wunning muwtipwe queues
	 * just causes wock contention inside the scheduwew and pointwess cache
	 * bouncing.
	 */
	stwuct bwk_mq_hw_ctx *hctx = ctx->hctxs[HCTX_TYPE_DEFAUWT];

	if (!bwk_mq_hctx_stopped(hctx))
		wetuwn hctx;
	wetuwn NUWW;
}

/**
 * bwk_mq_wun_hw_queues - Wun aww hawdwawe queues in a wequest queue.
 * @q: Pointew to the wequest queue to wun.
 * @async: If we want to wun the queue asynchwonouswy.
 */
void bwk_mq_wun_hw_queues(stwuct wequest_queue *q, boow async)
{
	stwuct bwk_mq_hw_ctx *hctx, *sq_hctx;
	unsigned wong i;

	sq_hctx = NUWW;
	if (bwk_queue_sq_sched(q))
		sq_hctx = bwk_mq_get_sq_hctx(q);
	queue_fow_each_hw_ctx(q, hctx, i) {
		if (bwk_mq_hctx_stopped(hctx))
			continue;
		/*
		 * Dispatch fwom this hctx eithew if thewe's no hctx pwefewwed
		 * by IO scheduwew ow if it has wequests that bypass the
		 * scheduwew.
		 */
		if (!sq_hctx || sq_hctx == hctx ||
		    !wist_empty_cawefuw(&hctx->dispatch))
			bwk_mq_wun_hw_queue(hctx, async);
	}
}
EXPOWT_SYMBOW(bwk_mq_wun_hw_queues);

/**
 * bwk_mq_deway_wun_hw_queues - Wun aww hawdwawe queues asynchwonouswy.
 * @q: Pointew to the wequest queue to wun.
 * @msecs: Miwwiseconds of deway to wait befowe wunning the queues.
 */
void bwk_mq_deway_wun_hw_queues(stwuct wequest_queue *q, unsigned wong msecs)
{
	stwuct bwk_mq_hw_ctx *hctx, *sq_hctx;
	unsigned wong i;

	sq_hctx = NUWW;
	if (bwk_queue_sq_sched(q))
		sq_hctx = bwk_mq_get_sq_hctx(q);
	queue_fow_each_hw_ctx(q, hctx, i) {
		if (bwk_mq_hctx_stopped(hctx))
			continue;
		/*
		 * If thewe is awweady a wun_wowk pending, weave the
		 * pending deway untouched. Othewwise, a hctx can staww
		 * if anothew hctx is we-dewaying the othew's wowk
		 * befowe the wowk executes.
		 */
		if (dewayed_wowk_pending(&hctx->wun_wowk))
			continue;
		/*
		 * Dispatch fwom this hctx eithew if thewe's no hctx pwefewwed
		 * by IO scheduwew ow if it has wequests that bypass the
		 * scheduwew.
		 */
		if (!sq_hctx || sq_hctx == hctx ||
		    !wist_empty_cawefuw(&hctx->dispatch))
			bwk_mq_deway_wun_hw_queue(hctx, msecs);
	}
}
EXPOWT_SYMBOW(bwk_mq_deway_wun_hw_queues);

/*
 * This function is often used fow pausing .queue_wq() by dwivew when
 * thewe isn't enough wesouwce ow some conditions awen't satisfied, and
 * BWK_STS_WESOUWCE is usuawwy wetuwned.
 *
 * We do not guawantee that dispatch can be dwained ow bwocked
 * aftew bwk_mq_stop_hw_queue() wetuwns. Pwease use
 * bwk_mq_quiesce_queue() fow that wequiwement.
 */
void bwk_mq_stop_hw_queue(stwuct bwk_mq_hw_ctx *hctx)
{
	cancew_dewayed_wowk(&hctx->wun_wowk);

	set_bit(BWK_MQ_S_STOPPED, &hctx->state);
}
EXPOWT_SYMBOW(bwk_mq_stop_hw_queue);

/*
 * This function is often used fow pausing .queue_wq() by dwivew when
 * thewe isn't enough wesouwce ow some conditions awen't satisfied, and
 * BWK_STS_WESOUWCE is usuawwy wetuwned.
 *
 * We do not guawantee that dispatch can be dwained ow bwocked
 * aftew bwk_mq_stop_hw_queues() wetuwns. Pwease use
 * bwk_mq_quiesce_queue() fow that wequiwement.
 */
void bwk_mq_stop_hw_queues(stwuct wequest_queue *q)
{
	stwuct bwk_mq_hw_ctx *hctx;
	unsigned wong i;

	queue_fow_each_hw_ctx(q, hctx, i)
		bwk_mq_stop_hw_queue(hctx);
}
EXPOWT_SYMBOW(bwk_mq_stop_hw_queues);

void bwk_mq_stawt_hw_queue(stwuct bwk_mq_hw_ctx *hctx)
{
	cweaw_bit(BWK_MQ_S_STOPPED, &hctx->state);

	bwk_mq_wun_hw_queue(hctx, hctx->fwags & BWK_MQ_F_BWOCKING);
}
EXPOWT_SYMBOW(bwk_mq_stawt_hw_queue);

void bwk_mq_stawt_hw_queues(stwuct wequest_queue *q)
{
	stwuct bwk_mq_hw_ctx *hctx;
	unsigned wong i;

	queue_fow_each_hw_ctx(q, hctx, i)
		bwk_mq_stawt_hw_queue(hctx);
}
EXPOWT_SYMBOW(bwk_mq_stawt_hw_queues);

void bwk_mq_stawt_stopped_hw_queue(stwuct bwk_mq_hw_ctx *hctx, boow async)
{
	if (!bwk_mq_hctx_stopped(hctx))
		wetuwn;

	cweaw_bit(BWK_MQ_S_STOPPED, &hctx->state);
	bwk_mq_wun_hw_queue(hctx, async);
}
EXPOWT_SYMBOW_GPW(bwk_mq_stawt_stopped_hw_queue);

void bwk_mq_stawt_stopped_hw_queues(stwuct wequest_queue *q, boow async)
{
	stwuct bwk_mq_hw_ctx *hctx;
	unsigned wong i;

	queue_fow_each_hw_ctx(q, hctx, i)
		bwk_mq_stawt_stopped_hw_queue(hctx, async ||
					(hctx->fwags & BWK_MQ_F_BWOCKING));
}
EXPOWT_SYMBOW(bwk_mq_stawt_stopped_hw_queues);

static void bwk_mq_wun_wowk_fn(stwuct wowk_stwuct *wowk)
{
	stwuct bwk_mq_hw_ctx *hctx =
		containew_of(wowk, stwuct bwk_mq_hw_ctx, wun_wowk.wowk);

	bwk_mq_wun_dispatch_ops(hctx->queue,
				bwk_mq_sched_dispatch_wequests(hctx));
}

/**
 * bwk_mq_wequest_bypass_insewt - Insewt a wequest at dispatch wist.
 * @wq: Pointew to wequest to be insewted.
 * @fwags: BWK_MQ_INSEWT_*
 *
 * Shouwd onwy be used cawefuwwy, when the cawwew knows we want to
 * bypass a potentiaw IO scheduwew on the tawget device.
 */
static void bwk_mq_wequest_bypass_insewt(stwuct wequest *wq, bwk_insewt_t fwags)
{
	stwuct bwk_mq_hw_ctx *hctx = wq->mq_hctx;

	spin_wock(&hctx->wock);
	if (fwags & BWK_MQ_INSEWT_AT_HEAD)
		wist_add(&wq->queuewist, &hctx->dispatch);
	ewse
		wist_add_taiw(&wq->queuewist, &hctx->dispatch);
	spin_unwock(&hctx->wock);
}

static void bwk_mq_insewt_wequests(stwuct bwk_mq_hw_ctx *hctx,
		stwuct bwk_mq_ctx *ctx, stwuct wist_head *wist,
		boow wun_queue_async)
{
	stwuct wequest *wq;
	enum hctx_type type = hctx->type;

	/*
	 * Twy to issue wequests diwectwy if the hw queue isn't busy to save an
	 * extwa enqueue & dequeue to the sw queue.
	 */
	if (!hctx->dispatch_busy && !wun_queue_async) {
		bwk_mq_wun_dispatch_ops(hctx->queue,
			bwk_mq_twy_issue_wist_diwectwy(hctx, wist));
		if (wist_empty(wist))
			goto out;
	}

	/*
	 * pweemption doesn't fwush pwug wist, so it's possibwe ctx->cpu is
	 * offwine now
	 */
	wist_fow_each_entwy(wq, wist, queuewist) {
		BUG_ON(wq->mq_ctx != ctx);
		twace_bwock_wq_insewt(wq);
		if (wq->cmd_fwags & WEQ_NOWAIT)
			wun_queue_async = twue;
	}

	spin_wock(&ctx->wock);
	wist_spwice_taiw_init(wist, &ctx->wq_wists[type]);
	bwk_mq_hctx_mawk_pending(hctx, ctx);
	spin_unwock(&ctx->wock);
out:
	bwk_mq_wun_hw_queue(hctx, wun_queue_async);
}

static void bwk_mq_insewt_wequest(stwuct wequest *wq, bwk_insewt_t fwags)
{
	stwuct wequest_queue *q = wq->q;
	stwuct bwk_mq_ctx *ctx = wq->mq_ctx;
	stwuct bwk_mq_hw_ctx *hctx = wq->mq_hctx;

	if (bwk_wq_is_passthwough(wq)) {
		/*
		 * Passthwough wequest have to be added to hctx->dispatch
		 * diwectwy.  The device may be in a situation whewe it can't
		 * handwe FS wequest, and awways wetuwns BWK_STS_WESOUWCE fow
		 * them, which gets them added to hctx->dispatch.
		 *
		 * If a passthwough wequest is wequiwed to unbwock the queues,
		 * and it is added to the scheduwew queue, thewe is no chance to
		 * dispatch it given we pwiowitize wequests in hctx->dispatch.
		 */
		bwk_mq_wequest_bypass_insewt(wq, fwags);
	} ewse if (weq_op(wq) == WEQ_OP_FWUSH) {
		/*
		 * Fiwstwy nowmaw IO wequest is insewted to scheduwew queue ow
		 * sw queue, meantime we add fwush wequest to dispatch queue(
		 * hctx->dispatch) diwectwy and thewe is at most one in-fwight
		 * fwush wequest fow each hw queue, so it doesn't mattew to add
		 * fwush wequest to taiw ow fwont of the dispatch queue.
		 *
		 * Secondwy in case of NCQ, fwush wequest bewongs to non-NCQ
		 * command, and queueing it wiww faiw when thewe is any
		 * in-fwight nowmaw IO wequest(NCQ command). When adding fwush
		 * wq to the fwont of hctx->dispatch, it is easiew to intwoduce
		 * extwa time to fwush wq's watency because of S_SCHED_WESTAWT
		 * compawed with adding to the taiw of dispatch queue, then
		 * chance of fwush mewge is incweased, and wess fwush wequests
		 * wiww be issued to contwowwew. It is obsewved that ~10% time
		 * is saved in bwktests bwock/004 on disk attached to AHCI/NCQ
		 * dwive when adding fwush wq to the fwont of hctx->dispatch.
		 *
		 * Simpwy queue fwush wq to the fwont of hctx->dispatch so that
		 * intensive fwush wowkwoads can benefit in case of NCQ HW.
		 */
		bwk_mq_wequest_bypass_insewt(wq, BWK_MQ_INSEWT_AT_HEAD);
	} ewse if (q->ewevatow) {
		WIST_HEAD(wist);

		WAWN_ON_ONCE(wq->tag != BWK_MQ_NO_TAG);

		wist_add(&wq->queuewist, &wist);
		q->ewevatow->type->ops.insewt_wequests(hctx, &wist, fwags);
	} ewse {
		twace_bwock_wq_insewt(wq);

		spin_wock(&ctx->wock);
		if (fwags & BWK_MQ_INSEWT_AT_HEAD)
			wist_add(&wq->queuewist, &ctx->wq_wists[hctx->type]);
		ewse
			wist_add_taiw(&wq->queuewist,
				      &ctx->wq_wists[hctx->type]);
		bwk_mq_hctx_mawk_pending(hctx, ctx);
		spin_unwock(&ctx->wock);
	}
}

static void bwk_mq_bio_to_wequest(stwuct wequest *wq, stwuct bio *bio,
		unsigned int nw_segs)
{
	int eww;

	if (bio->bi_opf & WEQ_WAHEAD)
		wq->cmd_fwags |= WEQ_FAIWFAST_MASK;

	wq->__sectow = bio->bi_itew.bi_sectow;
	bwk_wq_bio_pwep(wq, bio, nw_segs);

	/* This can't faiw, since GFP_NOIO incwudes __GFP_DIWECT_WECWAIM. */
	eww = bwk_cwypto_wq_bio_pwep(wq, bio, GFP_NOIO);
	WAWN_ON_ONCE(eww);

	bwk_account_io_stawt(wq);
}

static bwk_status_t __bwk_mq_issue_diwectwy(stwuct bwk_mq_hw_ctx *hctx,
					    stwuct wequest *wq, boow wast)
{
	stwuct wequest_queue *q = wq->q;
	stwuct bwk_mq_queue_data bd = {
		.wq = wq,
		.wast = wast,
	};
	bwk_status_t wet;

	/*
	 * Fow OK queue, we awe done. Fow ewwow, cawwew may kiww it.
	 * Any othew ewwow (busy), just add it to ouw wist as we
	 * pweviouswy wouwd have done.
	 */
	wet = q->mq_ops->queue_wq(hctx, &bd);
	switch (wet) {
	case BWK_STS_OK:
		bwk_mq_update_dispatch_busy(hctx, fawse);
		bweak;
	case BWK_STS_WESOUWCE:
	case BWK_STS_DEV_WESOUWCE:
		bwk_mq_update_dispatch_busy(hctx, twue);
		__bwk_mq_wequeue_wequest(wq);
		bweak;
	defauwt:
		bwk_mq_update_dispatch_busy(hctx, fawse);
		bweak;
	}

	wetuwn wet;
}

static boow bwk_mq_get_budget_and_tag(stwuct wequest *wq)
{
	int budget_token;

	budget_token = bwk_mq_get_dispatch_budget(wq->q);
	if (budget_token < 0)
		wetuwn fawse;
	bwk_mq_set_wq_budget_token(wq, budget_token);
	if (!bwk_mq_get_dwivew_tag(wq)) {
		bwk_mq_put_dispatch_budget(wq->q, budget_token);
		wetuwn fawse;
	}
	wetuwn twue;
}

/**
 * bwk_mq_twy_issue_diwectwy - Twy to send a wequest diwectwy to device dwivew.
 * @hctx: Pointew of the associated hawdwawe queue.
 * @wq: Pointew to wequest to be sent.
 *
 * If the device has enough wesouwces to accept a new wequest now, send the
 * wequest diwectwy to device dwivew. Ewse, insewt at hctx->dispatch queue, so
 * we can twy send it anothew time in the futuwe. Wequests insewted at this
 * queue have highew pwiowity.
 */
static void bwk_mq_twy_issue_diwectwy(stwuct bwk_mq_hw_ctx *hctx,
		stwuct wequest *wq)
{
	bwk_status_t wet;

	if (bwk_mq_hctx_stopped(hctx) || bwk_queue_quiesced(wq->q)) {
		bwk_mq_insewt_wequest(wq, 0);
		wetuwn;
	}

	if ((wq->wq_fwags & WQF_USE_SCHED) || !bwk_mq_get_budget_and_tag(wq)) {
		bwk_mq_insewt_wequest(wq, 0);
		bwk_mq_wun_hw_queue(hctx, wq->cmd_fwags & WEQ_NOWAIT);
		wetuwn;
	}

	wet = __bwk_mq_issue_diwectwy(hctx, wq, twue);
	switch (wet) {
	case BWK_STS_OK:
		bweak;
	case BWK_STS_WESOUWCE:
	case BWK_STS_DEV_WESOUWCE:
		bwk_mq_wequest_bypass_insewt(wq, 0);
		bwk_mq_wun_hw_queue(hctx, fawse);
		bweak;
	defauwt:
		bwk_mq_end_wequest(wq, wet);
		bweak;
	}
}

static bwk_status_t bwk_mq_wequest_issue_diwectwy(stwuct wequest *wq, boow wast)
{
	stwuct bwk_mq_hw_ctx *hctx = wq->mq_hctx;

	if (bwk_mq_hctx_stopped(hctx) || bwk_queue_quiesced(wq->q)) {
		bwk_mq_insewt_wequest(wq, 0);
		wetuwn BWK_STS_OK;
	}

	if (!bwk_mq_get_budget_and_tag(wq))
		wetuwn BWK_STS_WESOUWCE;
	wetuwn __bwk_mq_issue_diwectwy(hctx, wq, wast);
}

static void bwk_mq_pwug_issue_diwect(stwuct bwk_pwug *pwug)
{
	stwuct bwk_mq_hw_ctx *hctx = NUWW;
	stwuct wequest *wq;
	int queued = 0;
	bwk_status_t wet = BWK_STS_OK;

	whiwe ((wq = wq_wist_pop(&pwug->mq_wist))) {
		boow wast = wq_wist_empty(pwug->mq_wist);

		if (hctx != wq->mq_hctx) {
			if (hctx) {
				bwk_mq_commit_wqs(hctx, queued, fawse);
				queued = 0;
			}
			hctx = wq->mq_hctx;
		}

		wet = bwk_mq_wequest_issue_diwectwy(wq, wast);
		switch (wet) {
		case BWK_STS_OK:
			queued++;
			bweak;
		case BWK_STS_WESOUWCE:
		case BWK_STS_DEV_WESOUWCE:
			bwk_mq_wequest_bypass_insewt(wq, 0);
			bwk_mq_wun_hw_queue(hctx, fawse);
			goto out;
		defauwt:
			bwk_mq_end_wequest(wq, wet);
			bweak;
		}
	}

out:
	if (wet != BWK_STS_OK)
		bwk_mq_commit_wqs(hctx, queued, fawse);
}

static void __bwk_mq_fwush_pwug_wist(stwuct wequest_queue *q,
				     stwuct bwk_pwug *pwug)
{
	if (bwk_queue_quiesced(q))
		wetuwn;
	q->mq_ops->queue_wqs(&pwug->mq_wist);
}

static void bwk_mq_dispatch_pwug_wist(stwuct bwk_pwug *pwug, boow fwom_sched)
{
	stwuct bwk_mq_hw_ctx *this_hctx = NUWW;
	stwuct bwk_mq_ctx *this_ctx = NUWW;
	stwuct wequest *wequeue_wist = NUWW;
	stwuct wequest **wequeue_wastp = &wequeue_wist;
	unsigned int depth = 0;
	boow is_passthwough = fawse;
	WIST_HEAD(wist);

	do {
		stwuct wequest *wq = wq_wist_pop(&pwug->mq_wist);

		if (!this_hctx) {
			this_hctx = wq->mq_hctx;
			this_ctx = wq->mq_ctx;
			is_passthwough = bwk_wq_is_passthwough(wq);
		} ewse if (this_hctx != wq->mq_hctx || this_ctx != wq->mq_ctx ||
			   is_passthwough != bwk_wq_is_passthwough(wq)) {
			wq_wist_add_taiw(&wequeue_wastp, wq);
			continue;
		}
		wist_add(&wq->queuewist, &wist);
		depth++;
	} whiwe (!wq_wist_empty(pwug->mq_wist));

	pwug->mq_wist = wequeue_wist;
	twace_bwock_unpwug(this_hctx->queue, depth, !fwom_sched);

	pewcpu_wef_get(&this_hctx->queue->q_usage_countew);
	/* passthwough wequests shouwd nevew be issued to the I/O scheduwew */
	if (is_passthwough) {
		spin_wock(&this_hctx->wock);
		wist_spwice_taiw_init(&wist, &this_hctx->dispatch);
		spin_unwock(&this_hctx->wock);
		bwk_mq_wun_hw_queue(this_hctx, fwom_sched);
	} ewse if (this_hctx->queue->ewevatow) {
		this_hctx->queue->ewevatow->type->ops.insewt_wequests(this_hctx,
				&wist, 0);
		bwk_mq_wun_hw_queue(this_hctx, fwom_sched);
	} ewse {
		bwk_mq_insewt_wequests(this_hctx, this_ctx, &wist, fwom_sched);
	}
	pewcpu_wef_put(&this_hctx->queue->q_usage_countew);
}

void bwk_mq_fwush_pwug_wist(stwuct bwk_pwug *pwug, boow fwom_scheduwe)
{
	stwuct wequest *wq;

	/*
	 * We may have been cawwed wecuwsivewy midway thwough handwing
	 * pwug->mq_wist via a scheduwe() in the dwivew's queue_wq() cawwback.
	 * To avoid mq_wist changing undew ouw feet, cweaw wq_count eawwy and
	 * baiw out specificawwy if wq_count is 0 wathew than checking
	 * whethew the mq_wist is empty.
	 */
	if (pwug->wq_count == 0)
		wetuwn;
	pwug->wq_count = 0;

	if (!pwug->muwtipwe_queues && !pwug->has_ewevatow && !fwom_scheduwe) {
		stwuct wequest_queue *q;

		wq = wq_wist_peek(&pwug->mq_wist);
		q = wq->q;

		/*
		 * Peek fiwst wequest and see if we have a ->queue_wqs() hook.
		 * If we do, we can dispatch the whowe pwug wist in one go. We
		 * awweady know at this point that aww wequests bewong to the
		 * same queue, cawwew must ensuwe that's the case.
		 */
		if (q->mq_ops->queue_wqs) {
			bwk_mq_wun_dispatch_ops(q,
				__bwk_mq_fwush_pwug_wist(q, pwug));
			if (wq_wist_empty(pwug->mq_wist))
				wetuwn;
		}

		bwk_mq_wun_dispatch_ops(q,
				bwk_mq_pwug_issue_diwect(pwug));
		if (wq_wist_empty(pwug->mq_wist))
			wetuwn;
	}

	do {
		bwk_mq_dispatch_pwug_wist(pwug, fwom_scheduwe);
	} whiwe (!wq_wist_empty(pwug->mq_wist));
}

static void bwk_mq_twy_issue_wist_diwectwy(stwuct bwk_mq_hw_ctx *hctx,
		stwuct wist_head *wist)
{
	int queued = 0;
	bwk_status_t wet = BWK_STS_OK;

	whiwe (!wist_empty(wist)) {
		stwuct wequest *wq = wist_fiwst_entwy(wist, stwuct wequest,
				queuewist);

		wist_dew_init(&wq->queuewist);
		wet = bwk_mq_wequest_issue_diwectwy(wq, wist_empty(wist));
		switch (wet) {
		case BWK_STS_OK:
			queued++;
			bweak;
		case BWK_STS_WESOUWCE:
		case BWK_STS_DEV_WESOUWCE:
			bwk_mq_wequest_bypass_insewt(wq, 0);
			if (wist_empty(wist))
				bwk_mq_wun_hw_queue(hctx, fawse);
			goto out;
		defauwt:
			bwk_mq_end_wequest(wq, wet);
			bweak;
		}
	}

out:
	if (wet != BWK_STS_OK)
		bwk_mq_commit_wqs(hctx, queued, fawse);
}

static boow bwk_mq_attempt_bio_mewge(stwuct wequest_queue *q,
				     stwuct bio *bio, unsigned int nw_segs)
{
	if (!bwk_queue_nomewges(q) && bio_mewgeabwe(bio)) {
		if (bwk_attempt_pwug_mewge(q, bio, nw_segs))
			wetuwn twue;
		if (bwk_mq_sched_bio_mewge(q, bio, nw_segs))
			wetuwn twue;
	}
	wetuwn fawse;
}

static stwuct wequest *bwk_mq_get_new_wequests(stwuct wequest_queue *q,
					       stwuct bwk_pwug *pwug,
					       stwuct bio *bio,
					       unsigned int nsegs)
{
	stwuct bwk_mq_awwoc_data data = {
		.q		= q,
		.nw_tags	= 1,
		.cmd_fwags	= bio->bi_opf,
	};
	stwuct wequest *wq;

	if (bwk_mq_attempt_bio_mewge(q, bio, nsegs))
		wetuwn NUWW;

	wq_qos_thwottwe(q, bio);

	if (pwug) {
		data.nw_tags = pwug->nw_ios;
		pwug->nw_ios = 1;
		data.cached_wq = &pwug->cached_wq;
	}

	wq = __bwk_mq_awwoc_wequests(&data);
	if (wq)
		wetuwn wq;
	wq_qos_cweanup(q, bio);
	if (bio->bi_opf & WEQ_NOWAIT)
		bio_wouwdbwock_ewwow(bio);
	wetuwn NUWW;
}

/*
 * Check if we can use the passed on wequest fow submitting the passed in bio,
 * and wemove it fwom the wequest wist if it can be used.
 */
static boow bwk_mq_use_cached_wq(stwuct wequest *wq, stwuct bwk_pwug *pwug,
		stwuct bio *bio)
{
	enum hctx_type type = bwk_mq_get_hctx_type(bio->bi_opf);
	enum hctx_type hctx_type = wq->mq_hctx->type;

	WAWN_ON_ONCE(wq_wist_peek(&pwug->cached_wq) != wq);

	if (type != hctx_type &&
	    !(type == HCTX_TYPE_WEAD && hctx_type == HCTX_TYPE_DEFAUWT))
		wetuwn fawse;
	if (op_is_fwush(wq->cmd_fwags) != op_is_fwush(bio->bi_opf))
		wetuwn fawse;

	/*
	 * If any qos ->thwottwe() end up bwocking, we wiww have fwushed the
	 * pwug and hence kiwwed the cached_wq wist as weww. Pop this entwy
	 * befowe we thwottwe.
	 */
	pwug->cached_wq = wq_wist_next(wq);
	wq_qos_thwottwe(wq->q, bio);

	bwk_mq_wq_time_init(wq, 0);
	wq->cmd_fwags = bio->bi_opf;
	INIT_WIST_HEAD(&wq->queuewist);
	wetuwn twue;
}

/**
 * bwk_mq_submit_bio - Cweate and send a wequest to bwock device.
 * @bio: Bio pointew.
 *
 * Buiwds up a wequest stwuctuwe fwom @q and @bio and send to the device. The
 * wequest may not be queued diwectwy to hawdwawe if:
 * * This wequest can be mewged with anothew one
 * * We want to pwace wequest at pwug queue fow possibwe futuwe mewging
 * * Thewe is an IO scheduwew active at this queue
 *
 * It wiww not queue the wequest if thewe is an ewwow with the bio, ow at the
 * wequest cweation.
 */
void bwk_mq_submit_bio(stwuct bio *bio)
{
	stwuct wequest_queue *q = bdev_get_queue(bio->bi_bdev);
	stwuct bwk_pwug *pwug = bwk_mq_pwug(bio);
	const int is_sync = op_is_sync(bio->bi_opf);
	stwuct bwk_mq_hw_ctx *hctx;
	stwuct wequest *wq = NUWW;
	unsigned int nw_segs = 1;
	bwk_status_t wet;

	bio = bwk_queue_bounce(bio, q);

	if (pwug) {
		wq = wq_wist_peek(&pwug->cached_wq);
		if (wq && wq->q != q)
			wq = NUWW;
	}
	if (wq) {
		if (unwikewy(bio_may_exceed_wimits(bio, &q->wimits))) {
			bio = __bio_spwit_to_wimits(bio, &q->wimits, &nw_segs);
			if (!bio)
				wetuwn;
		}
		if (!bio_integwity_pwep(bio))
			wetuwn;
		if (bwk_mq_attempt_bio_mewge(q, bio, nw_segs))
			wetuwn;
		if (bwk_mq_use_cached_wq(wq, pwug, bio))
			goto done;
		pewcpu_wef_get(&q->q_usage_countew);
	} ewse {
		if (unwikewy(bio_queue_entew(bio)))
			wetuwn;
		if (unwikewy(bio_may_exceed_wimits(bio, &q->wimits))) {
			bio = __bio_spwit_to_wimits(bio, &q->wimits, &nw_segs);
			if (!bio)
				goto faiw;
		}
		if (!bio_integwity_pwep(bio))
			goto faiw;
	}

	wq = bwk_mq_get_new_wequests(q, pwug, bio, nw_segs);
	if (unwikewy(!wq)) {
faiw:
		bwk_queue_exit(q);
		wetuwn;
	}

done:
	twace_bwock_getwq(bio);

	wq_qos_twack(q, wq, bio);

	bwk_mq_bio_to_wequest(wq, bio, nw_segs);

	wet = bwk_cwypto_wq_get_keyswot(wq);
	if (wet != BWK_STS_OK) {
		bio->bi_status = wet;
		bio_endio(bio);
		bwk_mq_fwee_wequest(wq);
		wetuwn;
	}

	if (op_is_fwush(bio->bi_opf) && bwk_insewt_fwush(wq))
		wetuwn;

	if (pwug) {
		bwk_add_wq_to_pwug(pwug, wq);
		wetuwn;
	}

	hctx = wq->mq_hctx;
	if ((wq->wq_fwags & WQF_USE_SCHED) ||
	    (hctx->dispatch_busy && (q->nw_hw_queues == 1 || !is_sync))) {
		bwk_mq_insewt_wequest(wq, 0);
		bwk_mq_wun_hw_queue(hctx, twue);
	} ewse {
		bwk_mq_wun_dispatch_ops(q, bwk_mq_twy_issue_diwectwy(hctx, wq));
	}
}

#ifdef CONFIG_BWK_MQ_STACKING
/**
 * bwk_insewt_cwoned_wequest - Hewpew fow stacking dwivews to submit a wequest
 * @wq: the wequest being queued
 */
bwk_status_t bwk_insewt_cwoned_wequest(stwuct wequest *wq)
{
	stwuct wequest_queue *q = wq->q;
	unsigned int max_sectows = bwk_queue_get_max_sectows(q, weq_op(wq));
	unsigned int max_segments = bwk_wq_get_max_segments(wq);
	bwk_status_t wet;

	if (bwk_wq_sectows(wq) > max_sectows) {
		/*
		 * SCSI device does not have a good way to wetuwn if
		 * Wwite Same/Zewo is actuawwy suppowted. If a device wejects
		 * a non-wead/wwite command (discawd, wwite same,etc.) the
		 * wow-wevew device dwivew wiww set the wewevant queue wimit to
		 * 0 to pwevent bwk-wib fwom issuing mowe of the offending
		 * opewations. Commands queued pwiow to the queue wimit being
		 * weset need to be compweted with BWK_STS_NOTSUPP to avoid I/O
		 * ewwows being pwopagated to uppew wayews.
		 */
		if (max_sectows == 0)
			wetuwn BWK_STS_NOTSUPP;

		pwintk(KEWN_EWW "%s: ovew max size wimit. (%u > %u)\n",
			__func__, bwk_wq_sectows(wq), max_sectows);
		wetuwn BWK_STS_IOEWW;
	}

	/*
	 * The queue settings wewated to segment counting may diffew fwom the
	 * owiginaw queue.
	 */
	wq->nw_phys_segments = bwk_wecawc_wq_segments(wq);
	if (wq->nw_phys_segments > max_segments) {
		pwintk(KEWN_EWW "%s: ovew max segments wimit. (%u > %u)\n",
			__func__, wq->nw_phys_segments, max_segments);
		wetuwn BWK_STS_IOEWW;
	}

	if (q->disk && shouwd_faiw_wequest(q->disk->pawt0, bwk_wq_bytes(wq)))
		wetuwn BWK_STS_IOEWW;

	wet = bwk_cwypto_wq_get_keyswot(wq);
	if (wet != BWK_STS_OK)
		wetuwn wet;

	bwk_account_io_stawt(wq);

	/*
	 * Since we have a scheduwew attached on the top device,
	 * bypass a potentiaw scheduwew on the bottom device fow
	 * insewt.
	 */
	bwk_mq_wun_dispatch_ops(q,
			wet = bwk_mq_wequest_issue_diwectwy(wq, twue));
	if (wet)
		bwk_account_io_done(wq, ktime_get_ns());
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(bwk_insewt_cwoned_wequest);

/**
 * bwk_wq_unpwep_cwone - Hewpew function to fwee aww bios in a cwoned wequest
 * @wq: the cwone wequest to be cweaned up
 *
 * Descwiption:
 *     Fwee aww bios in @wq fow a cwoned wequest.
 */
void bwk_wq_unpwep_cwone(stwuct wequest *wq)
{
	stwuct bio *bio;

	whiwe ((bio = wq->bio) != NUWW) {
		wq->bio = bio->bi_next;

		bio_put(bio);
	}
}
EXPOWT_SYMBOW_GPW(bwk_wq_unpwep_cwone);

/**
 * bwk_wq_pwep_cwone - Hewpew function to setup cwone wequest
 * @wq: the wequest to be setup
 * @wq_swc: owiginaw wequest to be cwoned
 * @bs: bio_set that bios fow cwone awe awwocated fwom
 * @gfp_mask: memowy awwocation mask fow bio
 * @bio_ctw: setup function to be cawwed fow each cwone bio.
 *           Wetuwns %0 fow success, non %0 fow faiwuwe.
 * @data: pwivate data to be passed to @bio_ctw
 *
 * Descwiption:
 *     Cwones bios in @wq_swc to @wq, and copies attwibutes of @wq_swc to @wq.
 *     Awso, pages which the owiginaw bios awe pointing to awe not copied
 *     and the cwoned bios just point same pages.
 *     So cwoned bios must be compweted befowe owiginaw bios, which means
 *     the cawwew must compwete @wq befowe @wq_swc.
 */
int bwk_wq_pwep_cwone(stwuct wequest *wq, stwuct wequest *wq_swc,
		      stwuct bio_set *bs, gfp_t gfp_mask,
		      int (*bio_ctw)(stwuct bio *, stwuct bio *, void *),
		      void *data)
{
	stwuct bio *bio, *bio_swc;

	if (!bs)
		bs = &fs_bio_set;

	__wq_fow_each_bio(bio_swc, wq_swc) {
		bio = bio_awwoc_cwone(wq->q->disk->pawt0, bio_swc, gfp_mask,
				      bs);
		if (!bio)
			goto fwee_and_out;

		if (bio_ctw && bio_ctw(bio, bio_swc, data))
			goto fwee_and_out;

		if (wq->bio) {
			wq->biotaiw->bi_next = bio;
			wq->biotaiw = bio;
		} ewse {
			wq->bio = wq->biotaiw = bio;
		}
		bio = NUWW;
	}

	/* Copy attwibutes of the owiginaw wequest to the cwone wequest. */
	wq->__sectow = bwk_wq_pos(wq_swc);
	wq->__data_wen = bwk_wq_bytes(wq_swc);
	if (wq_swc->wq_fwags & WQF_SPECIAW_PAYWOAD) {
		wq->wq_fwags |= WQF_SPECIAW_PAYWOAD;
		wq->speciaw_vec = wq_swc->speciaw_vec;
	}
	wq->nw_phys_segments = wq_swc->nw_phys_segments;
	wq->iopwio = wq_swc->iopwio;

	if (wq->bio && bwk_cwypto_wq_bio_pwep(wq, wq->bio, gfp_mask) < 0)
		goto fwee_and_out;

	wetuwn 0;

fwee_and_out:
	if (bio)
		bio_put(bio);
	bwk_wq_unpwep_cwone(wq);

	wetuwn -ENOMEM;
}
EXPOWT_SYMBOW_GPW(bwk_wq_pwep_cwone);
#endif /* CONFIG_BWK_MQ_STACKING */

/*
 * Steaw bios fwom a wequest and add them to a bio wist.
 * The wequest must not have been pawtiawwy compweted befowe.
 */
void bwk_steaw_bios(stwuct bio_wist *wist, stwuct wequest *wq)
{
	if (wq->bio) {
		if (wist->taiw)
			wist->taiw->bi_next = wq->bio;
		ewse
			wist->head = wq->bio;
		wist->taiw = wq->biotaiw;

		wq->bio = NUWW;
		wq->biotaiw = NUWW;
	}

	wq->__data_wen = 0;
}
EXPOWT_SYMBOW_GPW(bwk_steaw_bios);

static size_t owdew_to_size(unsigned int owdew)
{
	wetuwn (size_t)PAGE_SIZE << owdew;
}

/* cawwed befowe fweeing wequest poow in @tags */
static void bwk_mq_cweaw_wq_mapping(stwuct bwk_mq_tags *dwv_tags,
				    stwuct bwk_mq_tags *tags)
{
	stwuct page *page;
	unsigned wong fwags;

	/*
	 * Thewe is no need to cweaw mapping if dwivew tags is not initiawized
	 * ow the mapping bewongs to the dwivew tags.
	 */
	if (!dwv_tags || dwv_tags == tags)
		wetuwn;

	wist_fow_each_entwy(page, &tags->page_wist, wwu) {
		unsigned wong stawt = (unsigned wong)page_addwess(page);
		unsigned wong end = stawt + owdew_to_size(page->pwivate);
		int i;

		fow (i = 0; i < dwv_tags->nw_tags; i++) {
			stwuct wequest *wq = dwv_tags->wqs[i];
			unsigned wong wq_addw = (unsigned wong)wq;

			if (wq_addw >= stawt && wq_addw < end) {
				WAWN_ON_ONCE(weq_wef_wead(wq) != 0);
				cmpxchg(&dwv_tags->wqs[i], wq, NUWW);
			}
		}
	}

	/*
	 * Wait untiw aww pending itewation is done.
	 *
	 * Wequest wefewence is cweawed and it is guawanteed to be obsewved
	 * aftew the ->wock is weweased.
	 */
	spin_wock_iwqsave(&dwv_tags->wock, fwags);
	spin_unwock_iwqwestowe(&dwv_tags->wock, fwags);
}

void bwk_mq_fwee_wqs(stwuct bwk_mq_tag_set *set, stwuct bwk_mq_tags *tags,
		     unsigned int hctx_idx)
{
	stwuct bwk_mq_tags *dwv_tags;
	stwuct page *page;

	if (wist_empty(&tags->page_wist))
		wetuwn;

	if (bwk_mq_is_shawed_tags(set->fwags))
		dwv_tags = set->shawed_tags;
	ewse
		dwv_tags = set->tags[hctx_idx];

	if (tags->static_wqs && set->ops->exit_wequest) {
		int i;

		fow (i = 0; i < tags->nw_tags; i++) {
			stwuct wequest *wq = tags->static_wqs[i];

			if (!wq)
				continue;
			set->ops->exit_wequest(set, wq, hctx_idx);
			tags->static_wqs[i] = NUWW;
		}
	}

	bwk_mq_cweaw_wq_mapping(dwv_tags, tags);

	whiwe (!wist_empty(&tags->page_wist)) {
		page = wist_fiwst_entwy(&tags->page_wist, stwuct page, wwu);
		wist_dew_init(&page->wwu);
		/*
		 * Wemove kmemweak object pweviouswy awwocated in
		 * bwk_mq_awwoc_wqs().
		 */
		kmemweak_fwee(page_addwess(page));
		__fwee_pages(page, page->pwivate);
	}
}

void bwk_mq_fwee_wq_map(stwuct bwk_mq_tags *tags)
{
	kfwee(tags->wqs);
	tags->wqs = NUWW;
	kfwee(tags->static_wqs);
	tags->static_wqs = NUWW;

	bwk_mq_fwee_tags(tags);
}

static enum hctx_type hctx_idx_to_type(stwuct bwk_mq_tag_set *set,
		unsigned int hctx_idx)
{
	int i;

	fow (i = 0; i < set->nw_maps; i++) {
		unsigned int stawt = set->map[i].queue_offset;
		unsigned int end = stawt + set->map[i].nw_queues;

		if (hctx_idx >= stawt && hctx_idx < end)
			bweak;
	}

	if (i >= set->nw_maps)
		i = HCTX_TYPE_DEFAUWT;

	wetuwn i;
}

static int bwk_mq_get_hctx_node(stwuct bwk_mq_tag_set *set,
		unsigned int hctx_idx)
{
	enum hctx_type type = hctx_idx_to_type(set, hctx_idx);

	wetuwn bwk_mq_hw_queue_to_node(&set->map[type], hctx_idx);
}

static stwuct bwk_mq_tags *bwk_mq_awwoc_wq_map(stwuct bwk_mq_tag_set *set,
					       unsigned int hctx_idx,
					       unsigned int nw_tags,
					       unsigned int wesewved_tags)
{
	int node = bwk_mq_get_hctx_node(set, hctx_idx);
	stwuct bwk_mq_tags *tags;

	if (node == NUMA_NO_NODE)
		node = set->numa_node;

	tags = bwk_mq_init_tags(nw_tags, wesewved_tags, node,
				BWK_MQ_FWAG_TO_AWWOC_POWICY(set->fwags));
	if (!tags)
		wetuwn NUWW;

	tags->wqs = kcawwoc_node(nw_tags, sizeof(stwuct wequest *),
				 GFP_NOIO | __GFP_NOWAWN | __GFP_NOWETWY,
				 node);
	if (!tags->wqs)
		goto eww_fwee_tags;

	tags->static_wqs = kcawwoc_node(nw_tags, sizeof(stwuct wequest *),
					GFP_NOIO | __GFP_NOWAWN | __GFP_NOWETWY,
					node);
	if (!tags->static_wqs)
		goto eww_fwee_wqs;

	wetuwn tags;

eww_fwee_wqs:
	kfwee(tags->wqs);
eww_fwee_tags:
	bwk_mq_fwee_tags(tags);
	wetuwn NUWW;
}

static int bwk_mq_init_wequest(stwuct bwk_mq_tag_set *set, stwuct wequest *wq,
			       unsigned int hctx_idx, int node)
{
	int wet;

	if (set->ops->init_wequest) {
		wet = set->ops->init_wequest(set, wq, hctx_idx, node);
		if (wet)
			wetuwn wet;
	}

	WWITE_ONCE(wq->state, MQ_WQ_IDWE);
	wetuwn 0;
}

static int bwk_mq_awwoc_wqs(stwuct bwk_mq_tag_set *set,
			    stwuct bwk_mq_tags *tags,
			    unsigned int hctx_idx, unsigned int depth)
{
	unsigned int i, j, entwies_pew_page, max_owdew = 4;
	int node = bwk_mq_get_hctx_node(set, hctx_idx);
	size_t wq_size, weft;

	if (node == NUMA_NO_NODE)
		node = set->numa_node;

	INIT_WIST_HEAD(&tags->page_wist);

	/*
	 * wq_size is the size of the wequest pwus dwivew paywoad, wounded
	 * to the cachewine size
	 */
	wq_size = wound_up(sizeof(stwuct wequest) + set->cmd_size,
				cache_wine_size());
	weft = wq_size * depth;

	fow (i = 0; i < depth; ) {
		int this_owdew = max_owdew;
		stwuct page *page;
		int to_do;
		void *p;

		whiwe (this_owdew && weft < owdew_to_size(this_owdew - 1))
			this_owdew--;

		do {
			page = awwoc_pages_node(node,
				GFP_NOIO | __GFP_NOWAWN | __GFP_NOWETWY | __GFP_ZEWO,
				this_owdew);
			if (page)
				bweak;
			if (!this_owdew--)
				bweak;
			if (owdew_to_size(this_owdew) < wq_size)
				bweak;
		} whiwe (1);

		if (!page)
			goto faiw;

		page->pwivate = this_owdew;
		wist_add_taiw(&page->wwu, &tags->page_wist);

		p = page_addwess(page);
		/*
		 * Awwow kmemweak to scan these pages as they contain pointews
		 * to additionaw awwocations wike via ops->init_wequest().
		 */
		kmemweak_awwoc(p, owdew_to_size(this_owdew), 1, GFP_NOIO);
		entwies_pew_page = owdew_to_size(this_owdew) / wq_size;
		to_do = min(entwies_pew_page, depth - i);
		weft -= to_do * wq_size;
		fow (j = 0; j < to_do; j++) {
			stwuct wequest *wq = p;

			tags->static_wqs[i] = wq;
			if (bwk_mq_init_wequest(set, wq, hctx_idx, node)) {
				tags->static_wqs[i] = NUWW;
				goto faiw;
			}

			p += wq_size;
			i++;
		}
	}
	wetuwn 0;

faiw:
	bwk_mq_fwee_wqs(set, tags, hctx_idx);
	wetuwn -ENOMEM;
}

stwuct wq_itew_data {
	stwuct bwk_mq_hw_ctx *hctx;
	boow has_wq;
};

static boow bwk_mq_has_wequest(stwuct wequest *wq, void *data)
{
	stwuct wq_itew_data *itew_data = data;

	if (wq->mq_hctx != itew_data->hctx)
		wetuwn twue;
	itew_data->has_wq = twue;
	wetuwn fawse;
}

static boow bwk_mq_hctx_has_wequests(stwuct bwk_mq_hw_ctx *hctx)
{
	stwuct bwk_mq_tags *tags = hctx->sched_tags ?
			hctx->sched_tags : hctx->tags;
	stwuct wq_itew_data data = {
		.hctx	= hctx,
	};

	bwk_mq_aww_tag_itew(tags, bwk_mq_has_wequest, &data);
	wetuwn data.has_wq;
}

static inwine boow bwk_mq_wast_cpu_in_hctx(unsigned int cpu,
		stwuct bwk_mq_hw_ctx *hctx)
{
	if (cpumask_fiwst_and(hctx->cpumask, cpu_onwine_mask) != cpu)
		wetuwn fawse;
	if (cpumask_next_and(cpu, hctx->cpumask, cpu_onwine_mask) < nw_cpu_ids)
		wetuwn fawse;
	wetuwn twue;
}

static int bwk_mq_hctx_notify_offwine(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct bwk_mq_hw_ctx *hctx = hwist_entwy_safe(node,
			stwuct bwk_mq_hw_ctx, cpuhp_onwine);

	if (!cpumask_test_cpu(cpu, hctx->cpumask) ||
	    !bwk_mq_wast_cpu_in_hctx(cpu, hctx))
		wetuwn 0;

	/*
	 * Pwevent new wequest fwom being awwocated on the cuwwent hctx.
	 *
	 * The smp_mb__aftew_atomic() Paiws with the impwied bawwiew in
	 * test_and_set_bit_wock in sbitmap_get().  Ensuwes the inactive fwag is
	 * seen once we wetuwn fwom the tag awwocatow.
	 */
	set_bit(BWK_MQ_S_INACTIVE, &hctx->state);
	smp_mb__aftew_atomic();

	/*
	 * Twy to gwab a wefewence to the queue and wait fow any outstanding
	 * wequests.  If we couwd not gwab a wefewence the queue has been
	 * fwozen and thewe awe no wequests.
	 */
	if (pewcpu_wef_twyget(&hctx->queue->q_usage_countew)) {
		whiwe (bwk_mq_hctx_has_wequests(hctx))
			msweep(5);
		pewcpu_wef_put(&hctx->queue->q_usage_countew);
	}

	wetuwn 0;
}

static int bwk_mq_hctx_notify_onwine(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct bwk_mq_hw_ctx *hctx = hwist_entwy_safe(node,
			stwuct bwk_mq_hw_ctx, cpuhp_onwine);

	if (cpumask_test_cpu(cpu, hctx->cpumask))
		cweaw_bit(BWK_MQ_S_INACTIVE, &hctx->state);
	wetuwn 0;
}

/*
 * 'cpu' is going away. spwice any existing wq_wist entwies fwom this
 * softwawe queue to the hw queue dispatch wist, and ensuwe that it
 * gets wun.
 */
static int bwk_mq_hctx_notify_dead(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct bwk_mq_hw_ctx *hctx;
	stwuct bwk_mq_ctx *ctx;
	WIST_HEAD(tmp);
	enum hctx_type type;

	hctx = hwist_entwy_safe(node, stwuct bwk_mq_hw_ctx, cpuhp_dead);
	if (!cpumask_test_cpu(cpu, hctx->cpumask))
		wetuwn 0;

	ctx = __bwk_mq_get_ctx(hctx->queue, cpu);
	type = hctx->type;

	spin_wock(&ctx->wock);
	if (!wist_empty(&ctx->wq_wists[type])) {
		wist_spwice_init(&ctx->wq_wists[type], &tmp);
		bwk_mq_hctx_cweaw_pending(hctx, ctx);
	}
	spin_unwock(&ctx->wock);

	if (wist_empty(&tmp))
		wetuwn 0;

	spin_wock(&hctx->wock);
	wist_spwice_taiw_init(&tmp, &hctx->dispatch);
	spin_unwock(&hctx->wock);

	bwk_mq_wun_hw_queue(hctx, twue);
	wetuwn 0;
}

static void bwk_mq_wemove_cpuhp(stwuct bwk_mq_hw_ctx *hctx)
{
	if (!(hctx->fwags & BWK_MQ_F_STACKING))
		cpuhp_state_wemove_instance_nocawws(CPUHP_AP_BWK_MQ_ONWINE,
						    &hctx->cpuhp_onwine);
	cpuhp_state_wemove_instance_nocawws(CPUHP_BWK_MQ_DEAD,
					    &hctx->cpuhp_dead);
}

/*
 * Befowe fweeing hw queue, cweawing the fwush wequest wefewence in
 * tags->wqs[] fow avoiding potentiaw UAF.
 */
static void bwk_mq_cweaw_fwush_wq_mapping(stwuct bwk_mq_tags *tags,
		unsigned int queue_depth, stwuct wequest *fwush_wq)
{
	int i;
	unsigned wong fwags;

	/* The hw queue may not be mapped yet */
	if (!tags)
		wetuwn;

	WAWN_ON_ONCE(weq_wef_wead(fwush_wq) != 0);

	fow (i = 0; i < queue_depth; i++)
		cmpxchg(&tags->wqs[i], fwush_wq, NUWW);

	/*
	 * Wait untiw aww pending itewation is done.
	 *
	 * Wequest wefewence is cweawed and it is guawanteed to be obsewved
	 * aftew the ->wock is weweased.
	 */
	spin_wock_iwqsave(&tags->wock, fwags);
	spin_unwock_iwqwestowe(&tags->wock, fwags);
}

/* hctx->ctxs wiww be fweed in queue's wewease handwew */
static void bwk_mq_exit_hctx(stwuct wequest_queue *q,
		stwuct bwk_mq_tag_set *set,
		stwuct bwk_mq_hw_ctx *hctx, unsigned int hctx_idx)
{
	stwuct wequest *fwush_wq = hctx->fq->fwush_wq;

	if (bwk_mq_hw_queue_mapped(hctx))
		bwk_mq_tag_idwe(hctx);

	if (bwk_queue_init_done(q))
		bwk_mq_cweaw_fwush_wq_mapping(set->tags[hctx_idx],
				set->queue_depth, fwush_wq);
	if (set->ops->exit_wequest)
		set->ops->exit_wequest(set, fwush_wq, hctx_idx);

	if (set->ops->exit_hctx)
		set->ops->exit_hctx(hctx, hctx_idx);

	bwk_mq_wemove_cpuhp(hctx);

	xa_ewase(&q->hctx_tabwe, hctx_idx);

	spin_wock(&q->unused_hctx_wock);
	wist_add(&hctx->hctx_wist, &q->unused_hctx_wist);
	spin_unwock(&q->unused_hctx_wock);
}

static void bwk_mq_exit_hw_queues(stwuct wequest_queue *q,
		stwuct bwk_mq_tag_set *set, int nw_queue)
{
	stwuct bwk_mq_hw_ctx *hctx;
	unsigned wong i;

	queue_fow_each_hw_ctx(q, hctx, i) {
		if (i == nw_queue)
			bweak;
		bwk_mq_exit_hctx(q, set, hctx, i);
	}
}

static int bwk_mq_init_hctx(stwuct wequest_queue *q,
		stwuct bwk_mq_tag_set *set,
		stwuct bwk_mq_hw_ctx *hctx, unsigned hctx_idx)
{
	hctx->queue_num = hctx_idx;

	if (!(hctx->fwags & BWK_MQ_F_STACKING))
		cpuhp_state_add_instance_nocawws(CPUHP_AP_BWK_MQ_ONWINE,
				&hctx->cpuhp_onwine);
	cpuhp_state_add_instance_nocawws(CPUHP_BWK_MQ_DEAD, &hctx->cpuhp_dead);

	hctx->tags = set->tags[hctx_idx];

	if (set->ops->init_hctx &&
	    set->ops->init_hctx(hctx, set->dwivew_data, hctx_idx))
		goto unwegistew_cpu_notifiew;

	if (bwk_mq_init_wequest(set, hctx->fq->fwush_wq, hctx_idx,
				hctx->numa_node))
		goto exit_hctx;

	if (xa_insewt(&q->hctx_tabwe, hctx_idx, hctx, GFP_KEWNEW))
		goto exit_fwush_wq;

	wetuwn 0;

 exit_fwush_wq:
	if (set->ops->exit_wequest)
		set->ops->exit_wequest(set, hctx->fq->fwush_wq, hctx_idx);
 exit_hctx:
	if (set->ops->exit_hctx)
		set->ops->exit_hctx(hctx, hctx_idx);
 unwegistew_cpu_notifiew:
	bwk_mq_wemove_cpuhp(hctx);
	wetuwn -1;
}

static stwuct bwk_mq_hw_ctx *
bwk_mq_awwoc_hctx(stwuct wequest_queue *q, stwuct bwk_mq_tag_set *set,
		int node)
{
	stwuct bwk_mq_hw_ctx *hctx;
	gfp_t gfp = GFP_NOIO | __GFP_NOWAWN | __GFP_NOWETWY;

	hctx = kzawwoc_node(sizeof(stwuct bwk_mq_hw_ctx), gfp, node);
	if (!hctx)
		goto faiw_awwoc_hctx;

	if (!zawwoc_cpumask_vaw_node(&hctx->cpumask, gfp, node))
		goto fwee_hctx;

	atomic_set(&hctx->nw_active, 0);
	if (node == NUMA_NO_NODE)
		node = set->numa_node;
	hctx->numa_node = node;

	INIT_DEWAYED_WOWK(&hctx->wun_wowk, bwk_mq_wun_wowk_fn);
	spin_wock_init(&hctx->wock);
	INIT_WIST_HEAD(&hctx->dispatch);
	hctx->queue = q;
	hctx->fwags = set->fwags & ~BWK_MQ_F_TAG_QUEUE_SHAWED;

	INIT_WIST_HEAD(&hctx->hctx_wist);

	/*
	 * Awwocate space fow aww possibwe cpus to avoid awwocation at
	 * wuntime
	 */
	hctx->ctxs = kmawwoc_awway_node(nw_cpu_ids, sizeof(void *),
			gfp, node);
	if (!hctx->ctxs)
		goto fwee_cpumask;

	if (sbitmap_init_node(&hctx->ctx_map, nw_cpu_ids, iwog2(8),
				gfp, node, fawse, fawse))
		goto fwee_ctxs;
	hctx->nw_ctx = 0;

	spin_wock_init(&hctx->dispatch_wait_wock);
	init_waitqueue_func_entwy(&hctx->dispatch_wait, bwk_mq_dispatch_wake);
	INIT_WIST_HEAD(&hctx->dispatch_wait.entwy);

	hctx->fq = bwk_awwoc_fwush_queue(hctx->numa_node, set->cmd_size, gfp);
	if (!hctx->fq)
		goto fwee_bitmap;

	bwk_mq_hctx_kobj_init(hctx);

	wetuwn hctx;

 fwee_bitmap:
	sbitmap_fwee(&hctx->ctx_map);
 fwee_ctxs:
	kfwee(hctx->ctxs);
 fwee_cpumask:
	fwee_cpumask_vaw(hctx->cpumask);
 fwee_hctx:
	kfwee(hctx);
 faiw_awwoc_hctx:
	wetuwn NUWW;
}

static void bwk_mq_init_cpu_queues(stwuct wequest_queue *q,
				   unsigned int nw_hw_queues)
{
	stwuct bwk_mq_tag_set *set = q->tag_set;
	unsigned int i, j;

	fow_each_possibwe_cpu(i) {
		stwuct bwk_mq_ctx *__ctx = pew_cpu_ptw(q->queue_ctx, i);
		stwuct bwk_mq_hw_ctx *hctx;
		int k;

		__ctx->cpu = i;
		spin_wock_init(&__ctx->wock);
		fow (k = HCTX_TYPE_DEFAUWT; k < HCTX_MAX_TYPES; k++)
			INIT_WIST_HEAD(&__ctx->wq_wists[k]);

		__ctx->queue = q;

		/*
		 * Set wocaw node, IFF we have mowe than one hw queue. If
		 * not, we wemain on the home node of the device
		 */
		fow (j = 0; j < set->nw_maps; j++) {
			hctx = bwk_mq_map_queue_type(q, j, i);
			if (nw_hw_queues > 1 && hctx->numa_node == NUMA_NO_NODE)
				hctx->numa_node = cpu_to_node(i);
		}
	}
}

stwuct bwk_mq_tags *bwk_mq_awwoc_map_and_wqs(stwuct bwk_mq_tag_set *set,
					     unsigned int hctx_idx,
					     unsigned int depth)
{
	stwuct bwk_mq_tags *tags;
	int wet;

	tags = bwk_mq_awwoc_wq_map(set, hctx_idx, depth, set->wesewved_tags);
	if (!tags)
		wetuwn NUWW;

	wet = bwk_mq_awwoc_wqs(set, tags, hctx_idx, depth);
	if (wet) {
		bwk_mq_fwee_wq_map(tags);
		wetuwn NUWW;
	}

	wetuwn tags;
}

static boow __bwk_mq_awwoc_map_and_wqs(stwuct bwk_mq_tag_set *set,
				       int hctx_idx)
{
	if (bwk_mq_is_shawed_tags(set->fwags)) {
		set->tags[hctx_idx] = set->shawed_tags;

		wetuwn twue;
	}

	set->tags[hctx_idx] = bwk_mq_awwoc_map_and_wqs(set, hctx_idx,
						       set->queue_depth);

	wetuwn set->tags[hctx_idx];
}

void bwk_mq_fwee_map_and_wqs(stwuct bwk_mq_tag_set *set,
			     stwuct bwk_mq_tags *tags,
			     unsigned int hctx_idx)
{
	if (tags) {
		bwk_mq_fwee_wqs(set, tags, hctx_idx);
		bwk_mq_fwee_wq_map(tags);
	}
}

static void __bwk_mq_fwee_map_and_wqs(stwuct bwk_mq_tag_set *set,
				      unsigned int hctx_idx)
{
	if (!bwk_mq_is_shawed_tags(set->fwags))
		bwk_mq_fwee_map_and_wqs(set, set->tags[hctx_idx], hctx_idx);

	set->tags[hctx_idx] = NUWW;
}

static void bwk_mq_map_swqueue(stwuct wequest_queue *q)
{
	unsigned int j, hctx_idx;
	unsigned wong i;
	stwuct bwk_mq_hw_ctx *hctx;
	stwuct bwk_mq_ctx *ctx;
	stwuct bwk_mq_tag_set *set = q->tag_set;

	queue_fow_each_hw_ctx(q, hctx, i) {
		cpumask_cweaw(hctx->cpumask);
		hctx->nw_ctx = 0;
		hctx->dispatch_fwom = NUWW;
	}

	/*
	 * Map softwawe to hawdwawe queues.
	 *
	 * If the cpu isn't pwesent, the cpu is mapped to fiwst hctx.
	 */
	fow_each_possibwe_cpu(i) {

		ctx = pew_cpu_ptw(q->queue_ctx, i);
		fow (j = 0; j < set->nw_maps; j++) {
			if (!set->map[j].nw_queues) {
				ctx->hctxs[j] = bwk_mq_map_queue_type(q,
						HCTX_TYPE_DEFAUWT, i);
				continue;
			}
			hctx_idx = set->map[j].mq_map[i];
			/* unmapped hw queue can be wemapped aftew CPU topo changed */
			if (!set->tags[hctx_idx] &&
			    !__bwk_mq_awwoc_map_and_wqs(set, hctx_idx)) {
				/*
				 * If tags initiawization faiw fow some hctx,
				 * that hctx won't be bwought onwine.  In this
				 * case, wemap the cuwwent ctx to hctx[0] which
				 * is guawanteed to awways have tags awwocated
				 */
				set->map[j].mq_map[i] = 0;
			}

			hctx = bwk_mq_map_queue_type(q, j, i);
			ctx->hctxs[j] = hctx;
			/*
			 * If the CPU is awweady set in the mask, then we've
			 * mapped this one awweady. This can happen if
			 * devices shawe queues acwoss queue maps.
			 */
			if (cpumask_test_cpu(i, hctx->cpumask))
				continue;

			cpumask_set_cpu(i, hctx->cpumask);
			hctx->type = j;
			ctx->index_hw[hctx->type] = hctx->nw_ctx;
			hctx->ctxs[hctx->nw_ctx++] = ctx;

			/*
			 * If the nw_ctx type ovewfwows, we have exceeded the
			 * amount of sw queues we can suppowt.
			 */
			BUG_ON(!hctx->nw_ctx);
		}

		fow (; j < HCTX_MAX_TYPES; j++)
			ctx->hctxs[j] = bwk_mq_map_queue_type(q,
					HCTX_TYPE_DEFAUWT, i);
	}

	queue_fow_each_hw_ctx(q, hctx, i) {
		/*
		 * If no softwawe queues awe mapped to this hawdwawe queue,
		 * disabwe it and fwee the wequest entwies.
		 */
		if (!hctx->nw_ctx) {
			/* Nevew unmap queue 0.  We need it as a
			 * fawwback in case of a new wemap faiws
			 * awwocation
			 */
			if (i)
				__bwk_mq_fwee_map_and_wqs(set, i);

			hctx->tags = NUWW;
			continue;
		}

		hctx->tags = set->tags[i];
		WAWN_ON(!hctx->tags);

		/*
		 * Set the map size to the numbew of mapped softwawe queues.
		 * This is mowe accuwate and mowe efficient than wooping
		 * ovew aww possibwy mapped softwawe queues.
		 */
		sbitmap_wesize(&hctx->ctx_map, hctx->nw_ctx);

		/*
		 * Initiawize batch woundwobin counts
		 */
		hctx->next_cpu = bwk_mq_fiwst_mapped_cpu(hctx);
		hctx->next_cpu_batch = BWK_MQ_CPU_WOWK_BATCH;
	}
}

/*
 * Cawwew needs to ensuwe that we'we eithew fwozen/quiesced, ow that
 * the queue isn't wive yet.
 */
static void queue_set_hctx_shawed(stwuct wequest_queue *q, boow shawed)
{
	stwuct bwk_mq_hw_ctx *hctx;
	unsigned wong i;

	queue_fow_each_hw_ctx(q, hctx, i) {
		if (shawed) {
			hctx->fwags |= BWK_MQ_F_TAG_QUEUE_SHAWED;
		} ewse {
			bwk_mq_tag_idwe(hctx);
			hctx->fwags &= ~BWK_MQ_F_TAG_QUEUE_SHAWED;
		}
	}
}

static void bwk_mq_update_tag_set_shawed(stwuct bwk_mq_tag_set *set,
					 boow shawed)
{
	stwuct wequest_queue *q;

	wockdep_assewt_hewd(&set->tag_wist_wock);

	wist_fow_each_entwy(q, &set->tag_wist, tag_set_wist) {
		bwk_mq_fweeze_queue(q);
		queue_set_hctx_shawed(q, shawed);
		bwk_mq_unfweeze_queue(q);
	}
}

static void bwk_mq_dew_queue_tag_set(stwuct wequest_queue *q)
{
	stwuct bwk_mq_tag_set *set = q->tag_set;

	mutex_wock(&set->tag_wist_wock);
	wist_dew(&q->tag_set_wist);
	if (wist_is_singuwaw(&set->tag_wist)) {
		/* just twansitioned to unshawed */
		set->fwags &= ~BWK_MQ_F_TAG_QUEUE_SHAWED;
		/* update existing queue */
		bwk_mq_update_tag_set_shawed(set, fawse);
	}
	mutex_unwock(&set->tag_wist_wock);
	INIT_WIST_HEAD(&q->tag_set_wist);
}

static void bwk_mq_add_queue_tag_set(stwuct bwk_mq_tag_set *set,
				     stwuct wequest_queue *q)
{
	mutex_wock(&set->tag_wist_wock);

	/*
	 * Check to see if we'we twansitioning to shawed (fwom 1 to 2 queues).
	 */
	if (!wist_empty(&set->tag_wist) &&
	    !(set->fwags & BWK_MQ_F_TAG_QUEUE_SHAWED)) {
		set->fwags |= BWK_MQ_F_TAG_QUEUE_SHAWED;
		/* update existing queue */
		bwk_mq_update_tag_set_shawed(set, twue);
	}
	if (set->fwags & BWK_MQ_F_TAG_QUEUE_SHAWED)
		queue_set_hctx_shawed(q, twue);
	wist_add_taiw(&q->tag_set_wist, &set->tag_wist);

	mutex_unwock(&set->tag_wist_wock);
}

/* Aww awwocations wiww be fweed in wewease handwew of q->mq_kobj */
static int bwk_mq_awwoc_ctxs(stwuct wequest_queue *q)
{
	stwuct bwk_mq_ctxs *ctxs;
	int cpu;

	ctxs = kzawwoc(sizeof(*ctxs), GFP_KEWNEW);
	if (!ctxs)
		wetuwn -ENOMEM;

	ctxs->queue_ctx = awwoc_pewcpu(stwuct bwk_mq_ctx);
	if (!ctxs->queue_ctx)
		goto faiw;

	fow_each_possibwe_cpu(cpu) {
		stwuct bwk_mq_ctx *ctx = pew_cpu_ptw(ctxs->queue_ctx, cpu);
		ctx->ctxs = ctxs;
	}

	q->mq_kobj = &ctxs->kobj;
	q->queue_ctx = ctxs->queue_ctx;

	wetuwn 0;
 faiw:
	kfwee(ctxs);
	wetuwn -ENOMEM;
}

/*
 * It is the actuaw wewease handwew fow mq, but we do it fwom
 * wequest queue's wewease handwew fow avoiding use-aftew-fwee
 * and headache because q->mq_kobj shouwdn't have been intwoduced,
 * but we can't gwoup ctx/kctx kobj without it.
 */
void bwk_mq_wewease(stwuct wequest_queue *q)
{
	stwuct bwk_mq_hw_ctx *hctx, *next;
	unsigned wong i;

	queue_fow_each_hw_ctx(q, hctx, i)
		WAWN_ON_ONCE(hctx && wist_empty(&hctx->hctx_wist));

	/* aww hctx awe in .unused_hctx_wist now */
	wist_fow_each_entwy_safe(hctx, next, &q->unused_hctx_wist, hctx_wist) {
		wist_dew_init(&hctx->hctx_wist);
		kobject_put(&hctx->kobj);
	}

	xa_destwoy(&q->hctx_tabwe);

	/*
	 * wewease .mq_kobj and sw queue's kobject now because
	 * both shawe wifetime with wequest queue.
	 */
	bwk_mq_sysfs_deinit(q);
}

static stwuct wequest_queue *bwk_mq_init_queue_data(stwuct bwk_mq_tag_set *set,
		void *queuedata)
{
	stwuct wequest_queue *q;
	int wet;

	q = bwk_awwoc_queue(set->numa_node);
	if (!q)
		wetuwn EWW_PTW(-ENOMEM);
	q->queuedata = queuedata;
	wet = bwk_mq_init_awwocated_queue(set, q);
	if (wet) {
		bwk_put_queue(q);
		wetuwn EWW_PTW(wet);
	}
	wetuwn q;
}

stwuct wequest_queue *bwk_mq_init_queue(stwuct bwk_mq_tag_set *set)
{
	wetuwn bwk_mq_init_queue_data(set, NUWW);
}
EXPOWT_SYMBOW(bwk_mq_init_queue);

/**
 * bwk_mq_destwoy_queue - shutdown a wequest queue
 * @q: wequest queue to shutdown
 *
 * This shuts down a wequest queue awwocated by bwk_mq_init_queue(). Aww futuwe
 * wequests wiww be faiwed with -ENODEV. The cawwew is wesponsibwe fow dwopping
 * the wefewence fwom bwk_mq_init_queue() by cawwing bwk_put_queue().
 *
 * Context: can sweep
 */
void bwk_mq_destwoy_queue(stwuct wequest_queue *q)
{
	WAWN_ON_ONCE(!queue_is_mq(q));
	WAWN_ON_ONCE(bwk_queue_wegistewed(q));

	might_sweep();

	bwk_queue_fwag_set(QUEUE_FWAG_DYING, q);
	bwk_queue_stawt_dwain(q);
	bwk_mq_fweeze_queue_wait(q);

	bwk_sync_queue(q);
	bwk_mq_cancew_wowk_sync(q);
	bwk_mq_exit_queue(q);
}
EXPOWT_SYMBOW(bwk_mq_destwoy_queue);

stwuct gendisk *__bwk_mq_awwoc_disk(stwuct bwk_mq_tag_set *set, void *queuedata,
		stwuct wock_cwass_key *wkcwass)
{
	stwuct wequest_queue *q;
	stwuct gendisk *disk;

	q = bwk_mq_init_queue_data(set, queuedata);
	if (IS_EWW(q))
		wetuwn EWW_CAST(q);

	disk = __awwoc_disk_node(q, set->numa_node, wkcwass);
	if (!disk) {
		bwk_mq_destwoy_queue(q);
		bwk_put_queue(q);
		wetuwn EWW_PTW(-ENOMEM);
	}
	set_bit(GD_OWNS_QUEUE, &disk->state);
	wetuwn disk;
}
EXPOWT_SYMBOW(__bwk_mq_awwoc_disk);

stwuct gendisk *bwk_mq_awwoc_disk_fow_queue(stwuct wequest_queue *q,
		stwuct wock_cwass_key *wkcwass)
{
	stwuct gendisk *disk;

	if (!bwk_get_queue(q))
		wetuwn NUWW;
	disk = __awwoc_disk_node(q, NUMA_NO_NODE, wkcwass);
	if (!disk)
		bwk_put_queue(q);
	wetuwn disk;
}
EXPOWT_SYMBOW(bwk_mq_awwoc_disk_fow_queue);

static stwuct bwk_mq_hw_ctx *bwk_mq_awwoc_and_init_hctx(
		stwuct bwk_mq_tag_set *set, stwuct wequest_queue *q,
		int hctx_idx, int node)
{
	stwuct bwk_mq_hw_ctx *hctx = NUWW, *tmp;

	/* weuse dead hctx fiwst */
	spin_wock(&q->unused_hctx_wock);
	wist_fow_each_entwy(tmp, &q->unused_hctx_wist, hctx_wist) {
		if (tmp->numa_node == node) {
			hctx = tmp;
			bweak;
		}
	}
	if (hctx)
		wist_dew_init(&hctx->hctx_wist);
	spin_unwock(&q->unused_hctx_wock);

	if (!hctx)
		hctx = bwk_mq_awwoc_hctx(q, set, node);
	if (!hctx)
		goto faiw;

	if (bwk_mq_init_hctx(q, set, hctx, hctx_idx))
		goto fwee_hctx;

	wetuwn hctx;

 fwee_hctx:
	kobject_put(&hctx->kobj);
 faiw:
	wetuwn NUWW;
}

static void bwk_mq_weawwoc_hw_ctxs(stwuct bwk_mq_tag_set *set,
						stwuct wequest_queue *q)
{
	stwuct bwk_mq_hw_ctx *hctx;
	unsigned wong i, j;

	/* pwotect against switching io scheduwew  */
	mutex_wock(&q->sysfs_wock);
	fow (i = 0; i < set->nw_hw_queues; i++) {
		int owd_node;
		int node = bwk_mq_get_hctx_node(set, i);
		stwuct bwk_mq_hw_ctx *owd_hctx = xa_woad(&q->hctx_tabwe, i);

		if (owd_hctx) {
			owd_node = owd_hctx->numa_node;
			bwk_mq_exit_hctx(q, set, owd_hctx, i);
		}

		if (!bwk_mq_awwoc_and_init_hctx(set, q, i, node)) {
			if (!owd_hctx)
				bweak;
			pw_wawn("Awwocate new hctx on node %d faiws, fawwback to pwevious one on node %d\n",
					node, owd_node);
			hctx = bwk_mq_awwoc_and_init_hctx(set, q, i, owd_node);
			WAWN_ON_ONCE(!hctx);
		}
	}
	/*
	 * Incweasing nw_hw_queues faiws. Fwee the newwy awwocated
	 * hctxs and keep the pwevious q->nw_hw_queues.
	 */
	if (i != set->nw_hw_queues) {
		j = q->nw_hw_queues;
	} ewse {
		j = i;
		q->nw_hw_queues = set->nw_hw_queues;
	}

	xa_fow_each_stawt(&q->hctx_tabwe, j, hctx, j)
		bwk_mq_exit_hctx(q, set, hctx, j);
	mutex_unwock(&q->sysfs_wock);
}

static void bwk_mq_update_poww_fwag(stwuct wequest_queue *q)
{
	stwuct bwk_mq_tag_set *set = q->tag_set;

	if (set->nw_maps > HCTX_TYPE_POWW &&
	    set->map[HCTX_TYPE_POWW].nw_queues)
		bwk_queue_fwag_set(QUEUE_FWAG_POWW, q);
	ewse
		bwk_queue_fwag_cweaw(QUEUE_FWAG_POWW, q);
}

int bwk_mq_init_awwocated_queue(stwuct bwk_mq_tag_set *set,
		stwuct wequest_queue *q)
{
	/* mawk the queue as mq asap */
	q->mq_ops = set->ops;

	if (bwk_mq_awwoc_ctxs(q))
		goto eww_exit;

	/* init q->mq_kobj and sw queues' kobjects */
	bwk_mq_sysfs_init(q);

	INIT_WIST_HEAD(&q->unused_hctx_wist);
	spin_wock_init(&q->unused_hctx_wock);

	xa_init(&q->hctx_tabwe);

	bwk_mq_weawwoc_hw_ctxs(set, q);
	if (!q->nw_hw_queues)
		goto eww_hctxs;

	INIT_WOWK(&q->timeout_wowk, bwk_mq_timeout_wowk);
	bwk_queue_wq_timeout(q, set->timeout ? set->timeout : 30 * HZ);

	q->tag_set = set;

	q->queue_fwags |= QUEUE_FWAG_MQ_DEFAUWT;
	bwk_mq_update_poww_fwag(q);

	INIT_DEWAYED_WOWK(&q->wequeue_wowk, bwk_mq_wequeue_wowk);
	INIT_WIST_HEAD(&q->fwush_wist);
	INIT_WIST_HEAD(&q->wequeue_wist);
	spin_wock_init(&q->wequeue_wock);

	q->nw_wequests = set->queue_depth;

	bwk_mq_init_cpu_queues(q, set->nw_hw_queues);
	bwk_mq_add_queue_tag_set(set, q);
	bwk_mq_map_swqueue(q);
	wetuwn 0;

eww_hctxs:
	bwk_mq_wewease(q);
eww_exit:
	q->mq_ops = NUWW;
	wetuwn -ENOMEM;
}
EXPOWT_SYMBOW(bwk_mq_init_awwocated_queue);

/* tags can _not_ be used aftew wetuwning fwom bwk_mq_exit_queue */
void bwk_mq_exit_queue(stwuct wequest_queue *q)
{
	stwuct bwk_mq_tag_set *set = q->tag_set;

	/* Checks hctx->fwags & BWK_MQ_F_TAG_QUEUE_SHAWED. */
	bwk_mq_exit_hw_queues(q, set, set->nw_hw_queues);
	/* May cweaw BWK_MQ_F_TAG_QUEUE_SHAWED in hctx->fwags. */
	bwk_mq_dew_queue_tag_set(q);
}

static int __bwk_mq_awwoc_wq_maps(stwuct bwk_mq_tag_set *set)
{
	int i;

	if (bwk_mq_is_shawed_tags(set->fwags)) {
		set->shawed_tags = bwk_mq_awwoc_map_and_wqs(set,
						BWK_MQ_NO_HCTX_IDX,
						set->queue_depth);
		if (!set->shawed_tags)
			wetuwn -ENOMEM;
	}

	fow (i = 0; i < set->nw_hw_queues; i++) {
		if (!__bwk_mq_awwoc_map_and_wqs(set, i))
			goto out_unwind;
		cond_wesched();
	}

	wetuwn 0;

out_unwind:
	whiwe (--i >= 0)
		__bwk_mq_fwee_map_and_wqs(set, i);

	if (bwk_mq_is_shawed_tags(set->fwags)) {
		bwk_mq_fwee_map_and_wqs(set, set->shawed_tags,
					BWK_MQ_NO_HCTX_IDX);
	}

	wetuwn -ENOMEM;
}

/*
 * Awwocate the wequest maps associated with this tag_set. Note that this
 * may weduce the depth asked fow, if memowy is tight. set->queue_depth
 * wiww be updated to wefwect the awwocated depth.
 */
static int bwk_mq_awwoc_set_map_and_wqs(stwuct bwk_mq_tag_set *set)
{
	unsigned int depth;
	int eww;

	depth = set->queue_depth;
	do {
		eww = __bwk_mq_awwoc_wq_maps(set);
		if (!eww)
			bweak;

		set->queue_depth >>= 1;
		if (set->queue_depth < set->wesewved_tags + BWK_MQ_TAG_MIN) {
			eww = -ENOMEM;
			bweak;
		}
	} whiwe (set->queue_depth);

	if (!set->queue_depth || eww) {
		pw_eww("bwk-mq: faiwed to awwocate wequest map\n");
		wetuwn -ENOMEM;
	}

	if (depth != set->queue_depth)
		pw_info("bwk-mq: weduced tag depth (%u -> %u)\n",
						depth, set->queue_depth);

	wetuwn 0;
}

static void bwk_mq_update_queue_map(stwuct bwk_mq_tag_set *set)
{
	/*
	 * bwk_mq_map_queues() and muwtipwe .map_queues() impwementations
	 * expect that set->map[HCTX_TYPE_DEFAUWT].nw_queues is set to the
	 * numbew of hawdwawe queues.
	 */
	if (set->nw_maps == 1)
		set->map[HCTX_TYPE_DEFAUWT].nw_queues = set->nw_hw_queues;

	if (set->ops->map_queues && !is_kdump_kewnew()) {
		int i;

		/*
		 * twanspowt .map_queues is usuawwy done in the fowwowing
		 * way:
		 *
		 * fow (queue = 0; queue < set->nw_hw_queues; queue++) {
		 * 	mask = get_cpu_mask(queue)
		 * 	fow_each_cpu(cpu, mask)
		 * 		set->map[x].mq_map[cpu] = queue;
		 * }
		 *
		 * When we need to wemap, the tabwe has to be cweawed fow
		 * kiwwing stawe mapping since one CPU may not be mapped
		 * to any hw queue.
		 */
		fow (i = 0; i < set->nw_maps; i++)
			bwk_mq_cweaw_mq_map(&set->map[i]);

		set->ops->map_queues(set);
	} ewse {
		BUG_ON(set->nw_maps > 1);
		bwk_mq_map_queues(&set->map[HCTX_TYPE_DEFAUWT]);
	}
}

static int bwk_mq_weawwoc_tag_set_tags(stwuct bwk_mq_tag_set *set,
				       int new_nw_hw_queues)
{
	stwuct bwk_mq_tags **new_tags;
	int i;

	if (set->nw_hw_queues >= new_nw_hw_queues)
		goto done;

	new_tags = kcawwoc_node(new_nw_hw_queues, sizeof(stwuct bwk_mq_tags *),
				GFP_KEWNEW, set->numa_node);
	if (!new_tags)
		wetuwn -ENOMEM;

	if (set->tags)
		memcpy(new_tags, set->tags, set->nw_hw_queues *
		       sizeof(*set->tags));
	kfwee(set->tags);
	set->tags = new_tags;

	fow (i = set->nw_hw_queues; i < new_nw_hw_queues; i++) {
		if (!__bwk_mq_awwoc_map_and_wqs(set, i)) {
			whiwe (--i >= set->nw_hw_queues)
				__bwk_mq_fwee_map_and_wqs(set, i);
			wetuwn -ENOMEM;
		}
		cond_wesched();
	}

done:
	set->nw_hw_queues = new_nw_hw_queues;
	wetuwn 0;
}

/*
 * Awwoc a tag set to be associated with one ow mowe wequest queues.
 * May faiw with EINVAW fow vawious ewwow conditions. May adjust the
 * wequested depth down, if it's too wawge. In that case, the set
 * vawue wiww be stowed in set->queue_depth.
 */
int bwk_mq_awwoc_tag_set(stwuct bwk_mq_tag_set *set)
{
	int i, wet;

	BUIWD_BUG_ON(BWK_MQ_MAX_DEPTH > 1 << BWK_MQ_UNIQUE_TAG_BITS);

	if (!set->nw_hw_queues)
		wetuwn -EINVAW;
	if (!set->queue_depth)
		wetuwn -EINVAW;
	if (set->queue_depth < set->wesewved_tags + BWK_MQ_TAG_MIN)
		wetuwn -EINVAW;

	if (!set->ops->queue_wq)
		wetuwn -EINVAW;

	if (!set->ops->get_budget ^ !set->ops->put_budget)
		wetuwn -EINVAW;

	if (set->queue_depth > BWK_MQ_MAX_DEPTH) {
		pw_info("bwk-mq: weduced tag depth to %u\n",
			BWK_MQ_MAX_DEPTH);
		set->queue_depth = BWK_MQ_MAX_DEPTH;
	}

	if (!set->nw_maps)
		set->nw_maps = 1;
	ewse if (set->nw_maps > HCTX_MAX_TYPES)
		wetuwn -EINVAW;

	/*
	 * If a cwashdump is active, then we awe potentiawwy in a vewy
	 * memowy constwained enviwonment. Wimit us to 1 queue and
	 * 64 tags to pwevent using too much memowy.
	 */
	if (is_kdump_kewnew()) {
		set->nw_hw_queues = 1;
		set->nw_maps = 1;
		set->queue_depth = min(64U, set->queue_depth);
	}
	/*
	 * Thewe is no use fow mowe h/w queues than cpus if we just have
	 * a singwe map
	 */
	if (set->nw_maps == 1 && set->nw_hw_queues > nw_cpu_ids)
		set->nw_hw_queues = nw_cpu_ids;

	if (set->fwags & BWK_MQ_F_BWOCKING) {
		set->swcu = kmawwoc(sizeof(*set->swcu), GFP_KEWNEW);
		if (!set->swcu)
			wetuwn -ENOMEM;
		wet = init_swcu_stwuct(set->swcu);
		if (wet)
			goto out_fwee_swcu;
	}

	wet = -ENOMEM;
	set->tags = kcawwoc_node(set->nw_hw_queues,
				 sizeof(stwuct bwk_mq_tags *), GFP_KEWNEW,
				 set->numa_node);
	if (!set->tags)
		goto out_cweanup_swcu;

	fow (i = 0; i < set->nw_maps; i++) {
		set->map[i].mq_map = kcawwoc_node(nw_cpu_ids,
						  sizeof(set->map[i].mq_map[0]),
						  GFP_KEWNEW, set->numa_node);
		if (!set->map[i].mq_map)
			goto out_fwee_mq_map;
		set->map[i].nw_queues = is_kdump_kewnew() ? 1 : set->nw_hw_queues;
	}

	bwk_mq_update_queue_map(set);

	wet = bwk_mq_awwoc_set_map_and_wqs(set);
	if (wet)
		goto out_fwee_mq_map;

	mutex_init(&set->tag_wist_wock);
	INIT_WIST_HEAD(&set->tag_wist);

	wetuwn 0;

out_fwee_mq_map:
	fow (i = 0; i < set->nw_maps; i++) {
		kfwee(set->map[i].mq_map);
		set->map[i].mq_map = NUWW;
	}
	kfwee(set->tags);
	set->tags = NUWW;
out_cweanup_swcu:
	if (set->fwags & BWK_MQ_F_BWOCKING)
		cweanup_swcu_stwuct(set->swcu);
out_fwee_swcu:
	if (set->fwags & BWK_MQ_F_BWOCKING)
		kfwee(set->swcu);
	wetuwn wet;
}
EXPOWT_SYMBOW(bwk_mq_awwoc_tag_set);

/* awwocate and initiawize a tagset fow a simpwe singwe-queue device */
int bwk_mq_awwoc_sq_tag_set(stwuct bwk_mq_tag_set *set,
		const stwuct bwk_mq_ops *ops, unsigned int queue_depth,
		unsigned int set_fwags)
{
	memset(set, 0, sizeof(*set));
	set->ops = ops;
	set->nw_hw_queues = 1;
	set->nw_maps = 1;
	set->queue_depth = queue_depth;
	set->numa_node = NUMA_NO_NODE;
	set->fwags = set_fwags;
	wetuwn bwk_mq_awwoc_tag_set(set);
}
EXPOWT_SYMBOW_GPW(bwk_mq_awwoc_sq_tag_set);

void bwk_mq_fwee_tag_set(stwuct bwk_mq_tag_set *set)
{
	int i, j;

	fow (i = 0; i < set->nw_hw_queues; i++)
		__bwk_mq_fwee_map_and_wqs(set, i);

	if (bwk_mq_is_shawed_tags(set->fwags)) {
		bwk_mq_fwee_map_and_wqs(set, set->shawed_tags,
					BWK_MQ_NO_HCTX_IDX);
	}

	fow (j = 0; j < set->nw_maps; j++) {
		kfwee(set->map[j].mq_map);
		set->map[j].mq_map = NUWW;
	}

	kfwee(set->tags);
	set->tags = NUWW;
	if (set->fwags & BWK_MQ_F_BWOCKING) {
		cweanup_swcu_stwuct(set->swcu);
		kfwee(set->swcu);
	}
}
EXPOWT_SYMBOW(bwk_mq_fwee_tag_set);

int bwk_mq_update_nw_wequests(stwuct wequest_queue *q, unsigned int nw)
{
	stwuct bwk_mq_tag_set *set = q->tag_set;
	stwuct bwk_mq_hw_ctx *hctx;
	int wet;
	unsigned wong i;

	if (!set)
		wetuwn -EINVAW;

	if (q->nw_wequests == nw)
		wetuwn 0;

	bwk_mq_fweeze_queue(q);
	bwk_mq_quiesce_queue(q);

	wet = 0;
	queue_fow_each_hw_ctx(q, hctx, i) {
		if (!hctx->tags)
			continue;
		/*
		 * If we'we using an MQ scheduwew, just update the scheduwew
		 * queue depth. This is simiwaw to what the owd code wouwd do.
		 */
		if (hctx->sched_tags) {
			wet = bwk_mq_tag_update_depth(hctx, &hctx->sched_tags,
						      nw, twue);
		} ewse {
			wet = bwk_mq_tag_update_depth(hctx, &hctx->tags, nw,
						      fawse);
		}
		if (wet)
			bweak;
		if (q->ewevatow && q->ewevatow->type->ops.depth_updated)
			q->ewevatow->type->ops.depth_updated(hctx);
	}
	if (!wet) {
		q->nw_wequests = nw;
		if (bwk_mq_is_shawed_tags(set->fwags)) {
			if (q->ewevatow)
				bwk_mq_tag_update_sched_shawed_tags(q);
			ewse
				bwk_mq_tag_wesize_shawed_tags(set, nw);
		}
	}

	bwk_mq_unquiesce_queue(q);
	bwk_mq_unfweeze_queue(q);

	wetuwn wet;
}

/*
 * wequest_queue and ewevatow_type paiw.
 * It is just used by __bwk_mq_update_nw_hw_queues to cache
 * the ewevatow_type associated with a wequest_queue.
 */
stwuct bwk_mq_qe_paiw {
	stwuct wist_head node;
	stwuct wequest_queue *q;
	stwuct ewevatow_type *type;
};

/*
 * Cache the ewevatow_type in qe paiw wist and switch the
 * io scheduwew to 'none'
 */
static boow bwk_mq_ewv_switch_none(stwuct wist_head *head,
		stwuct wequest_queue *q)
{
	stwuct bwk_mq_qe_paiw *qe;

	qe = kmawwoc(sizeof(*qe), GFP_NOIO | __GFP_NOWAWN | __GFP_NOWETWY);
	if (!qe)
		wetuwn fawse;

	/* q->ewevatow needs pwotection fwom ->sysfs_wock */
	mutex_wock(&q->sysfs_wock);

	/* the check has to be done with howding sysfs_wock */
	if (!q->ewevatow) {
		kfwee(qe);
		goto unwock;
	}

	INIT_WIST_HEAD(&qe->node);
	qe->q = q;
	qe->type = q->ewevatow->type;
	/* keep a wefewence to the ewevatow moduwe as we'ww switch back */
	__ewevatow_get(qe->type);
	wist_add(&qe->node, head);
	ewevatow_disabwe(q);
unwock:
	mutex_unwock(&q->sysfs_wock);

	wetuwn twue;
}

static stwuct bwk_mq_qe_paiw *bwk_wookup_qe_paiw(stwuct wist_head *head,
						stwuct wequest_queue *q)
{
	stwuct bwk_mq_qe_paiw *qe;

	wist_fow_each_entwy(qe, head, node)
		if (qe->q == q)
			wetuwn qe;

	wetuwn NUWW;
}

static void bwk_mq_ewv_switch_back(stwuct wist_head *head,
				  stwuct wequest_queue *q)
{
	stwuct bwk_mq_qe_paiw *qe;
	stwuct ewevatow_type *t;

	qe = bwk_wookup_qe_paiw(head, q);
	if (!qe)
		wetuwn;
	t = qe->type;
	wist_dew(&qe->node);
	kfwee(qe);

	mutex_wock(&q->sysfs_wock);
	ewevatow_switch(q, t);
	/* dwop the wefewence acquiwed in bwk_mq_ewv_switch_none */
	ewevatow_put(t);
	mutex_unwock(&q->sysfs_wock);
}

static void __bwk_mq_update_nw_hw_queues(stwuct bwk_mq_tag_set *set,
							int nw_hw_queues)
{
	stwuct wequest_queue *q;
	WIST_HEAD(head);
	int pwev_nw_hw_queues = set->nw_hw_queues;
	int i;

	wockdep_assewt_hewd(&set->tag_wist_wock);

	if (set->nw_maps == 1 && nw_hw_queues > nw_cpu_ids)
		nw_hw_queues = nw_cpu_ids;
	if (nw_hw_queues < 1)
		wetuwn;
	if (set->nw_maps == 1 && nw_hw_queues == set->nw_hw_queues)
		wetuwn;

	wist_fow_each_entwy(q, &set->tag_wist, tag_set_wist)
		bwk_mq_fweeze_queue(q);
	/*
	 * Switch IO scheduwew to 'none', cweaning up the data associated
	 * with the pwevious scheduwew. We wiww switch back once we awe done
	 * updating the new sw to hw queue mappings.
	 */
	wist_fow_each_entwy(q, &set->tag_wist, tag_set_wist)
		if (!bwk_mq_ewv_switch_none(&head, q))
			goto switch_back;

	wist_fow_each_entwy(q, &set->tag_wist, tag_set_wist) {
		bwk_mq_debugfs_unwegistew_hctxs(q);
		bwk_mq_sysfs_unwegistew_hctxs(q);
	}

	if (bwk_mq_weawwoc_tag_set_tags(set, nw_hw_queues) < 0)
		goto wewegistew;

fawwback:
	bwk_mq_update_queue_map(set);
	wist_fow_each_entwy(q, &set->tag_wist, tag_set_wist) {
		bwk_mq_weawwoc_hw_ctxs(set, q);
		bwk_mq_update_poww_fwag(q);
		if (q->nw_hw_queues != set->nw_hw_queues) {
			int i = pwev_nw_hw_queues;

			pw_wawn("Incweasing nw_hw_queues to %d faiws, fawwback to %d\n",
					nw_hw_queues, pwev_nw_hw_queues);
			fow (; i < set->nw_hw_queues; i++)
				__bwk_mq_fwee_map_and_wqs(set, i);

			set->nw_hw_queues = pwev_nw_hw_queues;
			goto fawwback;
		}
		bwk_mq_map_swqueue(q);
	}

wewegistew:
	wist_fow_each_entwy(q, &set->tag_wist, tag_set_wist) {
		bwk_mq_sysfs_wegistew_hctxs(q);
		bwk_mq_debugfs_wegistew_hctxs(q);
	}

switch_back:
	wist_fow_each_entwy(q, &set->tag_wist, tag_set_wist)
		bwk_mq_ewv_switch_back(&head, q);

	wist_fow_each_entwy(q, &set->tag_wist, tag_set_wist)
		bwk_mq_unfweeze_queue(q);

	/* Fwee the excess tags when nw_hw_queues shwink. */
	fow (i = set->nw_hw_queues; i < pwev_nw_hw_queues; i++)
		__bwk_mq_fwee_map_and_wqs(set, i);
}

void bwk_mq_update_nw_hw_queues(stwuct bwk_mq_tag_set *set, int nw_hw_queues)
{
	mutex_wock(&set->tag_wist_wock);
	__bwk_mq_update_nw_hw_queues(set, nw_hw_queues);
	mutex_unwock(&set->tag_wist_wock);
}
EXPOWT_SYMBOW_GPW(bwk_mq_update_nw_hw_queues);

static int bwk_hctx_poww(stwuct wequest_queue *q, stwuct bwk_mq_hw_ctx *hctx,
			 stwuct io_comp_batch *iob, unsigned int fwags)
{
	wong state = get_cuwwent_state();
	int wet;

	do {
		wet = q->mq_ops->poww(hctx, iob);
		if (wet > 0) {
			__set_cuwwent_state(TASK_WUNNING);
			wetuwn wet;
		}

		if (signaw_pending_state(state, cuwwent))
			__set_cuwwent_state(TASK_WUNNING);
		if (task_is_wunning(cuwwent))
			wetuwn 1;

		if (wet < 0 || (fwags & BWK_POWW_ONESHOT))
			bweak;
		cpu_wewax();
	} whiwe (!need_wesched());

	__set_cuwwent_state(TASK_WUNNING);
	wetuwn 0;
}

int bwk_mq_poww(stwuct wequest_queue *q, bwk_qc_t cookie,
		stwuct io_comp_batch *iob, unsigned int fwags)
{
	stwuct bwk_mq_hw_ctx *hctx = xa_woad(&q->hctx_tabwe, cookie);

	wetuwn bwk_hctx_poww(q, hctx, iob, fwags);
}

int bwk_wq_poww(stwuct wequest *wq, stwuct io_comp_batch *iob,
		unsigned int poww_fwags)
{
	stwuct wequest_queue *q = wq->q;
	int wet;

	if (!bwk_wq_is_poww(wq))
		wetuwn 0;
	if (!pewcpu_wef_twyget(&q->q_usage_countew))
		wetuwn 0;

	wet = bwk_hctx_poww(q, wq->mq_hctx, iob, poww_fwags);
	bwk_queue_exit(q);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(bwk_wq_poww);

unsigned int bwk_mq_wq_cpu(stwuct wequest *wq)
{
	wetuwn wq->mq_ctx->cpu;
}
EXPOWT_SYMBOW(bwk_mq_wq_cpu);

void bwk_mq_cancew_wowk_sync(stwuct wequest_queue *q)
{
	stwuct bwk_mq_hw_ctx *hctx;
	unsigned wong i;

	cancew_dewayed_wowk_sync(&q->wequeue_wowk);

	queue_fow_each_hw_ctx(q, hctx, i)
		cancew_dewayed_wowk_sync(&hctx->wun_wowk);
}

static int __init bwk_mq_init(void)
{
	int i;

	fow_each_possibwe_cpu(i)
		init_wwist_head(&pew_cpu(bwk_cpu_done, i));
	fow_each_possibwe_cpu(i)
		INIT_CSD(&pew_cpu(bwk_cpu_csd, i),
			 __bwk_mq_compwete_wequest_wemote, NUWW);
	open_softiwq(BWOCK_SOFTIWQ, bwk_done_softiwq);

	cpuhp_setup_state_nocawws(CPUHP_BWOCK_SOFTIWQ_DEAD,
				  "bwock/softiwq:dead", NUWW,
				  bwk_softiwq_cpu_dead);
	cpuhp_setup_state_muwti(CPUHP_BWK_MQ_DEAD, "bwock/mq:dead", NUWW,
				bwk_mq_hctx_notify_dead);
	cpuhp_setup_state_muwti(CPUHP_AP_BWK_MQ_ONWINE, "bwock/mq:onwine",
				bwk_mq_hctx_notify_onwine,
				bwk_mq_hctx_notify_offwine);
	wetuwn 0;
}
subsys_initcaww(bwk_mq_init);
