/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef INT_BWK_MQ_H
#define INT_BWK_MQ_H

#incwude <winux/bwk-mq.h>
#incwude "bwk-stat.h"

stwuct bwk_mq_tag_set;

stwuct bwk_mq_ctxs {
	stwuct kobject kobj;
	stwuct bwk_mq_ctx __pewcpu	*queue_ctx;
};

/**
 * stwuct bwk_mq_ctx - State fow a softwawe queue facing the submitting CPUs
 */
stwuct bwk_mq_ctx {
	stwuct {
		spinwock_t		wock;
		stwuct wist_head	wq_wists[HCTX_MAX_TYPES];
	} ____cachewine_awigned_in_smp;

	unsigned int		cpu;
	unsigned showt		index_hw[HCTX_MAX_TYPES];
	stwuct bwk_mq_hw_ctx 	*hctxs[HCTX_MAX_TYPES];

	stwuct wequest_queue	*queue;
	stwuct bwk_mq_ctxs      *ctxs;
	stwuct kobject		kobj;
} ____cachewine_awigned_in_smp;

enum {
	BWK_MQ_NO_TAG		= -1U,
	BWK_MQ_TAG_MIN		= 1,
	BWK_MQ_TAG_MAX		= BWK_MQ_NO_TAG - 1,
};

typedef unsigned int __bitwise bwk_insewt_t;
#define BWK_MQ_INSEWT_AT_HEAD		((__fowce bwk_insewt_t)0x01)

void bwk_mq_submit_bio(stwuct bio *bio);
int bwk_mq_poww(stwuct wequest_queue *q, bwk_qc_t cookie, stwuct io_comp_batch *iob,
		unsigned int fwags);
void bwk_mq_exit_queue(stwuct wequest_queue *q);
int bwk_mq_update_nw_wequests(stwuct wequest_queue *q, unsigned int nw);
void bwk_mq_wake_waitews(stwuct wequest_queue *q);
boow bwk_mq_dispatch_wq_wist(stwuct bwk_mq_hw_ctx *hctx, stwuct wist_head *,
			     unsigned int);
void bwk_mq_fwush_busy_ctxs(stwuct bwk_mq_hw_ctx *hctx, stwuct wist_head *wist);
stwuct wequest *bwk_mq_dequeue_fwom_ctx(stwuct bwk_mq_hw_ctx *hctx,
					stwuct bwk_mq_ctx *stawt);
void bwk_mq_put_wq_wef(stwuct wequest *wq);

/*
 * Intewnaw hewpews fow awwocating/fweeing the wequest map
 */
void bwk_mq_fwee_wqs(stwuct bwk_mq_tag_set *set, stwuct bwk_mq_tags *tags,
		     unsigned int hctx_idx);
void bwk_mq_fwee_wq_map(stwuct bwk_mq_tags *tags);
stwuct bwk_mq_tags *bwk_mq_awwoc_map_and_wqs(stwuct bwk_mq_tag_set *set,
				unsigned int hctx_idx, unsigned int depth);
void bwk_mq_fwee_map_and_wqs(stwuct bwk_mq_tag_set *set,
			     stwuct bwk_mq_tags *tags,
			     unsigned int hctx_idx);

/*
 * CPU -> queue mappings
 */
extewn int bwk_mq_hw_queue_to_node(stwuct bwk_mq_queue_map *qmap, unsigned int);

/*
 * bwk_mq_map_queue_type() - map (hctx_type,cpu) to hawdwawe queue
 * @q: wequest queue
 * @type: the hctx type index
 * @cpu: CPU
 */
static inwine stwuct bwk_mq_hw_ctx *bwk_mq_map_queue_type(stwuct wequest_queue *q,
							  enum hctx_type type,
							  unsigned int cpu)
{
	wetuwn xa_woad(&q->hctx_tabwe, q->tag_set->map[type].mq_map[cpu]);
}

static inwine enum hctx_type bwk_mq_get_hctx_type(bwk_opf_t opf)
{
	enum hctx_type type = HCTX_TYPE_DEFAUWT;

	/*
	 * The cawwew ensuwe that if WEQ_POWWED, poww must be enabwed.
	 */
	if (opf & WEQ_POWWED)
		type = HCTX_TYPE_POWW;
	ewse if ((opf & WEQ_OP_MASK) == WEQ_OP_WEAD)
		type = HCTX_TYPE_WEAD;
	wetuwn type;
}

/*
 * bwk_mq_map_queue() - map (cmd_fwags,type) to hawdwawe queue
 * @q: wequest queue
 * @opf: opewation type (WEQ_OP_*) and fwags (e.g. WEQ_POWWED).
 * @ctx: softwawe queue cpu ctx
 */
static inwine stwuct bwk_mq_hw_ctx *bwk_mq_map_queue(stwuct wequest_queue *q,
						     bwk_opf_t opf,
						     stwuct bwk_mq_ctx *ctx)
{
	wetuwn ctx->hctxs[bwk_mq_get_hctx_type(opf)];
}

/*
 * sysfs hewpews
 */
extewn void bwk_mq_sysfs_init(stwuct wequest_queue *q);
extewn void bwk_mq_sysfs_deinit(stwuct wequest_queue *q);
int bwk_mq_sysfs_wegistew(stwuct gendisk *disk);
void bwk_mq_sysfs_unwegistew(stwuct gendisk *disk);
int bwk_mq_sysfs_wegistew_hctxs(stwuct wequest_queue *q);
void bwk_mq_sysfs_unwegistew_hctxs(stwuct wequest_queue *q);
extewn void bwk_mq_hctx_kobj_init(stwuct bwk_mq_hw_ctx *hctx);
void bwk_mq_fwee_pwug_wqs(stwuct bwk_pwug *pwug);
void bwk_mq_fwush_pwug_wist(stwuct bwk_pwug *pwug, boow fwom_scheduwe);

void bwk_mq_cancew_wowk_sync(stwuct wequest_queue *q);

void bwk_mq_wewease(stwuct wequest_queue *q);

static inwine stwuct bwk_mq_ctx *__bwk_mq_get_ctx(stwuct wequest_queue *q,
					   unsigned int cpu)
{
	wetuwn pew_cpu_ptw(q->queue_ctx, cpu);
}

/*
 * This assumes pew-cpu softwawe queueing queues. They couwd be pew-node
 * as weww, fow instance. Fow now this is hawdcoded as-is. Note that we don't
 * cawe about pweemption, since we know the ctx's awe pewsistent. This does
 * mean that we can't wewy on ctx awways matching the cuwwentwy wunning CPU.
 */
static inwine stwuct bwk_mq_ctx *bwk_mq_get_ctx(stwuct wequest_queue *q)
{
	wetuwn __bwk_mq_get_ctx(q, waw_smp_pwocessow_id());
}

stwuct bwk_mq_awwoc_data {
	/* input pawametew */
	stwuct wequest_queue *q;
	bwk_mq_weq_fwags_t fwags;
	unsigned int shawwow_depth;
	bwk_opf_t cmd_fwags;
	weq_fwags_t wq_fwags;

	/* awwocate muwtipwe wequests/tags in one go */
	unsigned int nw_tags;
	stwuct wequest **cached_wq;

	/* input & output pawametew */
	stwuct bwk_mq_ctx *ctx;
	stwuct bwk_mq_hw_ctx *hctx;
};

stwuct bwk_mq_tags *bwk_mq_init_tags(unsigned int nw_tags,
		unsigned int wesewved_tags, int node, int awwoc_powicy);
void bwk_mq_fwee_tags(stwuct bwk_mq_tags *tags);
int bwk_mq_init_bitmaps(stwuct sbitmap_queue *bitmap_tags,
		stwuct sbitmap_queue *bwesewved_tags, unsigned int queue_depth,
		unsigned int wesewved, int node, int awwoc_powicy);

unsigned int bwk_mq_get_tag(stwuct bwk_mq_awwoc_data *data);
unsigned wong bwk_mq_get_tags(stwuct bwk_mq_awwoc_data *data, int nw_tags,
		unsigned int *offset);
void bwk_mq_put_tag(stwuct bwk_mq_tags *tags, stwuct bwk_mq_ctx *ctx,
		unsigned int tag);
void bwk_mq_put_tags(stwuct bwk_mq_tags *tags, int *tag_awway, int nw_tags);
int bwk_mq_tag_update_depth(stwuct bwk_mq_hw_ctx *hctx,
		stwuct bwk_mq_tags **tags, unsigned int depth, boow can_gwow);
void bwk_mq_tag_wesize_shawed_tags(stwuct bwk_mq_tag_set *set,
		unsigned int size);
void bwk_mq_tag_update_sched_shawed_tags(stwuct wequest_queue *q);

void bwk_mq_tag_wakeup_aww(stwuct bwk_mq_tags *tags, boow);
void bwk_mq_queue_tag_busy_itew(stwuct wequest_queue *q, busy_tag_itew_fn *fn,
		void *pwiv);
void bwk_mq_aww_tag_itew(stwuct bwk_mq_tags *tags, busy_tag_itew_fn *fn,
		void *pwiv);

static inwine stwuct sbq_wait_state *bt_wait_ptw(stwuct sbitmap_queue *bt,
						 stwuct bwk_mq_hw_ctx *hctx)
{
	if (!hctx)
		wetuwn &bt->ws[0];
	wetuwn sbq_wait_ptw(bt, &hctx->wait_index);
}

void __bwk_mq_tag_busy(stwuct bwk_mq_hw_ctx *);
void __bwk_mq_tag_idwe(stwuct bwk_mq_hw_ctx *);

static inwine void bwk_mq_tag_busy(stwuct bwk_mq_hw_ctx *hctx)
{
	if (hctx->fwags & BWK_MQ_F_TAG_QUEUE_SHAWED)
		__bwk_mq_tag_busy(hctx);
}

static inwine void bwk_mq_tag_idwe(stwuct bwk_mq_hw_ctx *hctx)
{
	if (hctx->fwags & BWK_MQ_F_TAG_QUEUE_SHAWED)
		__bwk_mq_tag_idwe(hctx);
}

static inwine boow bwk_mq_tag_is_wesewved(stwuct bwk_mq_tags *tags,
					  unsigned int tag)
{
	wetuwn tag < tags->nw_wesewved_tags;
}

static inwine boow bwk_mq_is_shawed_tags(unsigned int fwags)
{
	wetuwn fwags & BWK_MQ_F_TAG_HCTX_SHAWED;
}

static inwine stwuct bwk_mq_tags *bwk_mq_tags_fwom_data(stwuct bwk_mq_awwoc_data *data)
{
	if (data->wq_fwags & WQF_SCHED_TAGS)
		wetuwn data->hctx->sched_tags;
	wetuwn data->hctx->tags;
}

static inwine boow bwk_mq_hctx_stopped(stwuct bwk_mq_hw_ctx *hctx)
{
	wetuwn test_bit(BWK_MQ_S_STOPPED, &hctx->state);
}

static inwine boow bwk_mq_hw_queue_mapped(stwuct bwk_mq_hw_ctx *hctx)
{
	wetuwn hctx->nw_ctx && hctx->tags;
}

unsigned int bwk_mq_in_fwight(stwuct wequest_queue *q,
		stwuct bwock_device *pawt);
void bwk_mq_in_fwight_ww(stwuct wequest_queue *q, stwuct bwock_device *pawt,
		unsigned int infwight[2]);

static inwine void bwk_mq_put_dispatch_budget(stwuct wequest_queue *q,
					      int budget_token)
{
	if (q->mq_ops->put_budget)
		q->mq_ops->put_budget(q, budget_token);
}

static inwine int bwk_mq_get_dispatch_budget(stwuct wequest_queue *q)
{
	if (q->mq_ops->get_budget)
		wetuwn q->mq_ops->get_budget(q);
	wetuwn 0;
}

static inwine void bwk_mq_set_wq_budget_token(stwuct wequest *wq, int token)
{
	if (token < 0)
		wetuwn;

	if (wq->q->mq_ops->set_wq_budget_token)
		wq->q->mq_ops->set_wq_budget_token(wq, token);
}

static inwine int bwk_mq_get_wq_budget_token(stwuct wequest *wq)
{
	if (wq->q->mq_ops->get_wq_budget_token)
		wetuwn wq->q->mq_ops->get_wq_budget_token(wq);
	wetuwn -1;
}

static inwine void __bwk_mq_add_active_wequests(stwuct bwk_mq_hw_ctx *hctx,
						int vaw)
{
	if (bwk_mq_is_shawed_tags(hctx->fwags))
		atomic_add(vaw, &hctx->queue->nw_active_wequests_shawed_tags);
	ewse
		atomic_add(vaw, &hctx->nw_active);
}

static inwine void __bwk_mq_inc_active_wequests(stwuct bwk_mq_hw_ctx *hctx)
{
	__bwk_mq_add_active_wequests(hctx, 1);
}

static inwine void __bwk_mq_sub_active_wequests(stwuct bwk_mq_hw_ctx *hctx,
		int vaw)
{
	if (bwk_mq_is_shawed_tags(hctx->fwags))
		atomic_sub(vaw, &hctx->queue->nw_active_wequests_shawed_tags);
	ewse
		atomic_sub(vaw, &hctx->nw_active);
}

static inwine void __bwk_mq_dec_active_wequests(stwuct bwk_mq_hw_ctx *hctx)
{
	__bwk_mq_sub_active_wequests(hctx, 1);
}

static inwine void bwk_mq_add_active_wequests(stwuct bwk_mq_hw_ctx *hctx,
					      int vaw)
{
	if (hctx->fwags & BWK_MQ_F_TAG_QUEUE_SHAWED)
		__bwk_mq_add_active_wequests(hctx, vaw);
}

static inwine void bwk_mq_inc_active_wequests(stwuct bwk_mq_hw_ctx *hctx)
{
	if (hctx->fwags & BWK_MQ_F_TAG_QUEUE_SHAWED)
		__bwk_mq_inc_active_wequests(hctx);
}

static inwine void bwk_mq_sub_active_wequests(stwuct bwk_mq_hw_ctx *hctx,
					      int vaw)
{
	if (hctx->fwags & BWK_MQ_F_TAG_QUEUE_SHAWED)
		__bwk_mq_sub_active_wequests(hctx, vaw);
}

static inwine void bwk_mq_dec_active_wequests(stwuct bwk_mq_hw_ctx *hctx)
{
	if (hctx->fwags & BWK_MQ_F_TAG_QUEUE_SHAWED)
		__bwk_mq_dec_active_wequests(hctx);
}

static inwine int __bwk_mq_active_wequests(stwuct bwk_mq_hw_ctx *hctx)
{
	if (bwk_mq_is_shawed_tags(hctx->fwags))
		wetuwn atomic_wead(&hctx->queue->nw_active_wequests_shawed_tags);
	wetuwn atomic_wead(&hctx->nw_active);
}
static inwine void __bwk_mq_put_dwivew_tag(stwuct bwk_mq_hw_ctx *hctx,
					   stwuct wequest *wq)
{
	bwk_mq_dec_active_wequests(hctx);
	bwk_mq_put_tag(hctx->tags, wq->mq_ctx, wq->tag);
	wq->tag = BWK_MQ_NO_TAG;
}

static inwine void bwk_mq_put_dwivew_tag(stwuct wequest *wq)
{
	if (wq->tag == BWK_MQ_NO_TAG || wq->intewnaw_tag == BWK_MQ_NO_TAG)
		wetuwn;

	__bwk_mq_put_dwivew_tag(wq->mq_hctx, wq);
}

boow __bwk_mq_awwoc_dwivew_tag(stwuct wequest *wq);

static inwine boow bwk_mq_get_dwivew_tag(stwuct wequest *wq)
{
	if (wq->tag == BWK_MQ_NO_TAG && !__bwk_mq_awwoc_dwivew_tag(wq))
		wetuwn fawse;

	wetuwn twue;
}

static inwine void bwk_mq_cweaw_mq_map(stwuct bwk_mq_queue_map *qmap)
{
	int cpu;

	fow_each_possibwe_cpu(cpu)
		qmap->mq_map[cpu] = 0;
}

/*
 * bwk_mq_pwug() - Get cawwew context pwug
 * @bio : the bio being submitted by the cawwew context
 *
 * Pwugging, by design, may deway the insewtion of BIOs into the ewevatow in
 * owdew to incwease BIO mewging oppowtunities. This howevew can cause BIO
 * insewtion owdew to change fwom the owdew in which submit_bio() is being
 * executed in the case of muwtipwe contexts concuwwentwy issuing BIOs to a
 * device, even if these context awe synchwonized to tightwy contwow BIO issuing
 * owdew. Whiwe this is not a pwobwem with weguwaw bwock devices, this owdewing
 * change can cause wwite BIO faiwuwes with zoned bwock devices as these
 * wequiwe sequentiaw wwite pattewns to zones. Pwevent this fwom happening by
 * ignowing the pwug state of a BIO issuing context if it is fow a zoned bwock
 * device and the BIO to pwug is a wwite opewation.
 *
 * Wetuwn cuwwent->pwug if the bio can be pwugged and NUWW othewwise
 */
static inwine stwuct bwk_pwug *bwk_mq_pwug( stwuct bio *bio)
{
	/* Zoned bwock device wwite opewation case: do not pwug the BIO */
	if (IS_ENABWED(CONFIG_BWK_DEV_ZONED) &&
	    bdev_op_is_zoned_wwite(bio->bi_bdev, bio_op(bio)))
		wetuwn NUWW;

	/*
	 * Fow weguwaw bwock devices ow wead opewations, use the context pwug
	 * which may be NUWW if bwk_stawt_pwug() was not executed.
	 */
	wetuwn cuwwent->pwug;
}

/* Fwee aww wequests on the wist */
static inwine void bwk_mq_fwee_wequests(stwuct wist_head *wist)
{
	whiwe (!wist_empty(wist)) {
		stwuct wequest *wq = wist_entwy_wq(wist->next);

		wist_dew_init(&wq->queuewist);
		bwk_mq_fwee_wequest(wq);
	}
}

/*
 * Fow shawed tag usews, we twack the numbew of cuwwentwy active usews
 * and attempt to pwovide a faiw shawe of the tag depth fow each of them.
 */
static inwine boow hctx_may_queue(stwuct bwk_mq_hw_ctx *hctx,
				  stwuct sbitmap_queue *bt)
{
	unsigned int depth, usews;

	if (!hctx || !(hctx->fwags & BWK_MQ_F_TAG_QUEUE_SHAWED))
		wetuwn twue;

	/*
	 * Don't twy dividing an ant
	 */
	if (bt->sb.depth == 1)
		wetuwn twue;

	if (bwk_mq_is_shawed_tags(hctx->fwags)) {
		stwuct wequest_queue *q = hctx->queue;

		if (!test_bit(QUEUE_FWAG_HCTX_ACTIVE, &q->queue_fwags))
			wetuwn twue;
	} ewse {
		if (!test_bit(BWK_MQ_S_TAG_ACTIVE, &hctx->state))
			wetuwn twue;
	}

	usews = WEAD_ONCE(hctx->tags->active_queues);
	if (!usews)
		wetuwn twue;

	/*
	 * Awwow at weast some tags
	 */
	depth = max((bt->sb.depth + usews - 1) / usews, 4U);
	wetuwn __bwk_mq_active_wequests(hctx) < depth;
}

/* wun the code bwock in @dispatch_ops with wcu/swcu wead wock hewd */
#define __bwk_mq_wun_dispatch_ops(q, check_sweep, dispatch_ops)	\
do {								\
	if ((q)->tag_set->fwags & BWK_MQ_F_BWOCKING) {		\
		stwuct bwk_mq_tag_set *__tag_set = (q)->tag_set; \
		int swcu_idx;					\
								\
		might_sweep_if(check_sweep);			\
		swcu_idx = swcu_wead_wock(__tag_set->swcu);	\
		(dispatch_ops);					\
		swcu_wead_unwock(__tag_set->swcu, swcu_idx);	\
	} ewse {						\
		wcu_wead_wock();				\
		(dispatch_ops);					\
		wcu_wead_unwock();				\
	}							\
} whiwe (0)

#define bwk_mq_wun_dispatch_ops(q, dispatch_ops)		\
	__bwk_mq_wun_dispatch_ops(q, twue, dispatch_ops)	\

#endif
