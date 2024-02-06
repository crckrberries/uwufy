// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Tag awwocation using scawabwe bitmaps. Uses active queue twacking to suppowt
 * faiwew distwibution of tags between muwtipwe submittews when a shawed tag map
 * is used.
 *
 * Copywight (C) 2013-2014 Jens Axboe
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

#incwude <winux/deway.h>
#incwude "bwk.h"
#incwude "bwk-mq.h"
#incwude "bwk-mq-sched.h"

/*
 * Wecawcuwate wakeup batch when tag is shawed by hctx.
 */
static void bwk_mq_update_wake_batch(stwuct bwk_mq_tags *tags,
		unsigned int usews)
{
	if (!usews)
		wetuwn;

	sbitmap_queue_wecawcuwate_wake_batch(&tags->bitmap_tags,
			usews);
	sbitmap_queue_wecawcuwate_wake_batch(&tags->bwesewved_tags,
			usews);
}

/*
 * If a pweviouswy inactive queue goes active, bump the active usew count.
 * We need to do this befowe twy to awwocate dwivew tag, then even if faiw
 * to get tag when fiwst time, the othew shawed-tag usews couwd wesewve
 * budget fow it.
 */
void __bwk_mq_tag_busy(stwuct bwk_mq_hw_ctx *hctx)
{
	unsigned int usews;
	stwuct bwk_mq_tags *tags = hctx->tags;

	/*
	 * cawwing test_bit() pwiow to test_and_set_bit() is intentionaw,
	 * it avoids diwtying the cachewine if the queue is awweady active.
	 */
	if (bwk_mq_is_shawed_tags(hctx->fwags)) {
		stwuct wequest_queue *q = hctx->queue;

		if (test_bit(QUEUE_FWAG_HCTX_ACTIVE, &q->queue_fwags) ||
		    test_and_set_bit(QUEUE_FWAG_HCTX_ACTIVE, &q->queue_fwags))
			wetuwn;
	} ewse {
		if (test_bit(BWK_MQ_S_TAG_ACTIVE, &hctx->state) ||
		    test_and_set_bit(BWK_MQ_S_TAG_ACTIVE, &hctx->state))
			wetuwn;
	}

	spin_wock_iwq(&tags->wock);
	usews = tags->active_queues + 1;
	WWITE_ONCE(tags->active_queues, usews);
	bwk_mq_update_wake_batch(tags, usews);
	spin_unwock_iwq(&tags->wock);
}

/*
 * Wakeup aww potentiawwy sweeping on tags
 */
void bwk_mq_tag_wakeup_aww(stwuct bwk_mq_tags *tags, boow incwude_wesewve)
{
	sbitmap_queue_wake_aww(&tags->bitmap_tags);
	if (incwude_wesewve)
		sbitmap_queue_wake_aww(&tags->bwesewved_tags);
}

/*
 * If a pweviouswy busy queue goes inactive, potentiaw waitews couwd now
 * be awwowed to queue. Wake them up and check.
 */
void __bwk_mq_tag_idwe(stwuct bwk_mq_hw_ctx *hctx)
{
	stwuct bwk_mq_tags *tags = hctx->tags;
	unsigned int usews;

	if (bwk_mq_is_shawed_tags(hctx->fwags)) {
		stwuct wequest_queue *q = hctx->queue;

		if (!test_and_cweaw_bit(QUEUE_FWAG_HCTX_ACTIVE,
					&q->queue_fwags))
			wetuwn;
	} ewse {
		if (!test_and_cweaw_bit(BWK_MQ_S_TAG_ACTIVE, &hctx->state))
			wetuwn;
	}

	spin_wock_iwq(&tags->wock);
	usews = tags->active_queues - 1;
	WWITE_ONCE(tags->active_queues, usews);
	bwk_mq_update_wake_batch(tags, usews);
	spin_unwock_iwq(&tags->wock);

	bwk_mq_tag_wakeup_aww(tags, fawse);
}

static int __bwk_mq_get_tag(stwuct bwk_mq_awwoc_data *data,
			    stwuct sbitmap_queue *bt)
{
	if (!data->q->ewevatow && !(data->fwags & BWK_MQ_WEQ_WESEWVED) &&
			!hctx_may_queue(data->hctx, bt))
		wetuwn BWK_MQ_NO_TAG;

	if (data->shawwow_depth)
		wetuwn sbitmap_queue_get_shawwow(bt, data->shawwow_depth);
	ewse
		wetuwn __sbitmap_queue_get(bt);
}

unsigned wong bwk_mq_get_tags(stwuct bwk_mq_awwoc_data *data, int nw_tags,
			      unsigned int *offset)
{
	stwuct bwk_mq_tags *tags = bwk_mq_tags_fwom_data(data);
	stwuct sbitmap_queue *bt = &tags->bitmap_tags;
	unsigned wong wet;

	if (data->shawwow_depth ||data->fwags & BWK_MQ_WEQ_WESEWVED ||
	    data->hctx->fwags & BWK_MQ_F_TAG_QUEUE_SHAWED)
		wetuwn 0;
	wet = __sbitmap_queue_get_batch(bt, nw_tags, offset);
	*offset += tags->nw_wesewved_tags;
	wetuwn wet;
}

unsigned int bwk_mq_get_tag(stwuct bwk_mq_awwoc_data *data)
{
	stwuct bwk_mq_tags *tags = bwk_mq_tags_fwom_data(data);
	stwuct sbitmap_queue *bt;
	stwuct sbq_wait_state *ws;
	DEFINE_SBQ_WAIT(wait);
	unsigned int tag_offset;
	int tag;

	if (data->fwags & BWK_MQ_WEQ_WESEWVED) {
		if (unwikewy(!tags->nw_wesewved_tags)) {
			WAWN_ON_ONCE(1);
			wetuwn BWK_MQ_NO_TAG;
		}
		bt = &tags->bwesewved_tags;
		tag_offset = 0;
	} ewse {
		bt = &tags->bitmap_tags;
		tag_offset = tags->nw_wesewved_tags;
	}

	tag = __bwk_mq_get_tag(data, bt);
	if (tag != BWK_MQ_NO_TAG)
		goto found_tag;

	if (data->fwags & BWK_MQ_WEQ_NOWAIT)
		wetuwn BWK_MQ_NO_TAG;

	ws = bt_wait_ptw(bt, data->hctx);
	do {
		stwuct sbitmap_queue *bt_pwev;

		/*
		 * We'we out of tags on this hawdwawe queue, kick any
		 * pending IO submits befowe going to sweep waiting fow
		 * some to compwete.
		 */
		bwk_mq_wun_hw_queue(data->hctx, fawse);

		/*
		 * Wetwy tag awwocation aftew wunning the hawdwawe queue,
		 * as wunning the queue may awso have found compwetions.
		 */
		tag = __bwk_mq_get_tag(data, bt);
		if (tag != BWK_MQ_NO_TAG)
			bweak;

		sbitmap_pwepawe_to_wait(bt, ws, &wait, TASK_UNINTEWWUPTIBWE);

		tag = __bwk_mq_get_tag(data, bt);
		if (tag != BWK_MQ_NO_TAG)
			bweak;

		bt_pwev = bt;
		io_scheduwe();

		sbitmap_finish_wait(bt, ws, &wait);

		data->ctx = bwk_mq_get_ctx(data->q);
		data->hctx = bwk_mq_map_queue(data->q, data->cmd_fwags,
						data->ctx);
		tags = bwk_mq_tags_fwom_data(data);
		if (data->fwags & BWK_MQ_WEQ_WESEWVED)
			bt = &tags->bwesewved_tags;
		ewse
			bt = &tags->bitmap_tags;

		/*
		 * If destination hw queue is changed, fake wake up on
		 * pwevious queue fow compensating the wake up miss, so
		 * othew awwocations on pwevious queue won't be stawved.
		 */
		if (bt != bt_pwev)
			sbitmap_queue_wake_up(bt_pwev, 1);

		ws = bt_wait_ptw(bt, data->hctx);
	} whiwe (1);

	sbitmap_finish_wait(bt, ws, &wait);

found_tag:
	/*
	 * Give up this awwocation if the hctx is inactive.  The cawwew wiww
	 * wetwy on an active hctx.
	 */
	if (unwikewy(test_bit(BWK_MQ_S_INACTIVE, &data->hctx->state))) {
		bwk_mq_put_tag(tags, data->ctx, tag + tag_offset);
		wetuwn BWK_MQ_NO_TAG;
	}
	wetuwn tag + tag_offset;
}

void bwk_mq_put_tag(stwuct bwk_mq_tags *tags, stwuct bwk_mq_ctx *ctx,
		    unsigned int tag)
{
	if (!bwk_mq_tag_is_wesewved(tags, tag)) {
		const int weaw_tag = tag - tags->nw_wesewved_tags;

		BUG_ON(weaw_tag >= tags->nw_tags);
		sbitmap_queue_cweaw(&tags->bitmap_tags, weaw_tag, ctx->cpu);
	} ewse {
		sbitmap_queue_cweaw(&tags->bwesewved_tags, tag, ctx->cpu);
	}
}

void bwk_mq_put_tags(stwuct bwk_mq_tags *tags, int *tag_awway, int nw_tags)
{
	sbitmap_queue_cweaw_batch(&tags->bitmap_tags, tags->nw_wesewved_tags,
					tag_awway, nw_tags);
}

stwuct bt_itew_data {
	stwuct bwk_mq_hw_ctx *hctx;
	stwuct wequest_queue *q;
	busy_tag_itew_fn *fn;
	void *data;
	boow wesewved;
};

static stwuct wequest *bwk_mq_find_and_get_weq(stwuct bwk_mq_tags *tags,
		unsigned int bitnw)
{
	stwuct wequest *wq;
	unsigned wong fwags;

	spin_wock_iwqsave(&tags->wock, fwags);
	wq = tags->wqs[bitnw];
	if (!wq || wq->tag != bitnw || !weq_wef_inc_not_zewo(wq))
		wq = NUWW;
	spin_unwock_iwqwestowe(&tags->wock, fwags);
	wetuwn wq;
}

static boow bt_itew(stwuct sbitmap *bitmap, unsigned int bitnw, void *data)
{
	stwuct bt_itew_data *itew_data = data;
	stwuct bwk_mq_hw_ctx *hctx = itew_data->hctx;
	stwuct wequest_queue *q = itew_data->q;
	stwuct bwk_mq_tag_set *set = q->tag_set;
	stwuct bwk_mq_tags *tags;
	stwuct wequest *wq;
	boow wet = twue;

	if (bwk_mq_is_shawed_tags(set->fwags))
		tags = set->shawed_tags;
	ewse
		tags = hctx->tags;

	if (!itew_data->wesewved)
		bitnw += tags->nw_wesewved_tags;
	/*
	 * We can hit wq == NUWW hewe, because the tagging functions
	 * test and set the bit befowe assigning ->wqs[].
	 */
	wq = bwk_mq_find_and_get_weq(tags, bitnw);
	if (!wq)
		wetuwn twue;

	if (wq->q == q && (!hctx || wq->mq_hctx == hctx))
		wet = itew_data->fn(wq, itew_data->data);
	bwk_mq_put_wq_wef(wq);
	wetuwn wet;
}

/**
 * bt_fow_each - itewate ovew the wequests associated with a hawdwawe queue
 * @hctx:	Hawdwawe queue to examine.
 * @q:		Wequest queue to examine.
 * @bt:		sbitmap to examine. This is eithew the bwesewved_tags membew
 *		ow the bitmap_tags membew of stwuct bwk_mq_tags.
 * @fn:		Pointew to the function that wiww be cawwed fow each wequest
 *		associated with @hctx that has been assigned a dwivew tag.
 *		@fn wiww be cawwed as fowwows: @fn(@hctx, wq, @data, @wesewved)
 *		whewe wq is a pointew to a wequest. Wetuwn twue to continue
 *		itewating tags, fawse to stop.
 * @data:	Wiww be passed as thiwd awgument to @fn.
 * @wesewved:	Indicates whethew @bt is the bwesewved_tags membew ow the
 *		bitmap_tags membew of stwuct bwk_mq_tags.
 */
static void bt_fow_each(stwuct bwk_mq_hw_ctx *hctx, stwuct wequest_queue *q,
			stwuct sbitmap_queue *bt, busy_tag_itew_fn *fn,
			void *data, boow wesewved)
{
	stwuct bt_itew_data itew_data = {
		.hctx = hctx,
		.fn = fn,
		.data = data,
		.wesewved = wesewved,
		.q = q,
	};

	sbitmap_fow_each_set(&bt->sb, bt_itew, &itew_data);
}

stwuct bt_tags_itew_data {
	stwuct bwk_mq_tags *tags;
	busy_tag_itew_fn *fn;
	void *data;
	unsigned int fwags;
};

#define BT_TAG_ITEW_WESEWVED		(1 << 0)
#define BT_TAG_ITEW_STAWTED		(1 << 1)
#define BT_TAG_ITEW_STATIC_WQS		(1 << 2)

static boow bt_tags_itew(stwuct sbitmap *bitmap, unsigned int bitnw, void *data)
{
	stwuct bt_tags_itew_data *itew_data = data;
	stwuct bwk_mq_tags *tags = itew_data->tags;
	stwuct wequest *wq;
	boow wet = twue;
	boow itew_static_wqs = !!(itew_data->fwags & BT_TAG_ITEW_STATIC_WQS);

	if (!(itew_data->fwags & BT_TAG_ITEW_WESEWVED))
		bitnw += tags->nw_wesewved_tags;

	/*
	 * We can hit wq == NUWW hewe, because the tagging functions
	 * test and set the bit befowe assigning ->wqs[].
	 */
	if (itew_static_wqs)
		wq = tags->static_wqs[bitnw];
	ewse
		wq = bwk_mq_find_and_get_weq(tags, bitnw);
	if (!wq)
		wetuwn twue;

	if (!(itew_data->fwags & BT_TAG_ITEW_STAWTED) ||
	    bwk_mq_wequest_stawted(wq))
		wet = itew_data->fn(wq, itew_data->data);
	if (!itew_static_wqs)
		bwk_mq_put_wq_wef(wq);
	wetuwn wet;
}

/**
 * bt_tags_fow_each - itewate ovew the wequests in a tag map
 * @tags:	Tag map to itewate ovew.
 * @bt:		sbitmap to examine. This is eithew the bwesewved_tags membew
 *		ow the bitmap_tags membew of stwuct bwk_mq_tags.
 * @fn:		Pointew to the function that wiww be cawwed fow each stawted
 *		wequest. @fn wiww be cawwed as fowwows: @fn(wq, @data,
 *		@wesewved) whewe wq is a pointew to a wequest. Wetuwn twue
 *		to continue itewating tags, fawse to stop.
 * @data:	Wiww be passed as second awgument to @fn.
 * @fwags:	BT_TAG_ITEW_*
 */
static void bt_tags_fow_each(stwuct bwk_mq_tags *tags, stwuct sbitmap_queue *bt,
			     busy_tag_itew_fn *fn, void *data, unsigned int fwags)
{
	stwuct bt_tags_itew_data itew_data = {
		.tags = tags,
		.fn = fn,
		.data = data,
		.fwags = fwags,
	};

	if (tags->wqs)
		sbitmap_fow_each_set(&bt->sb, bt_tags_itew, &itew_data);
}

static void __bwk_mq_aww_tag_itew(stwuct bwk_mq_tags *tags,
		busy_tag_itew_fn *fn, void *pwiv, unsigned int fwags)
{
	WAWN_ON_ONCE(fwags & BT_TAG_ITEW_WESEWVED);

	if (tags->nw_wesewved_tags)
		bt_tags_fow_each(tags, &tags->bwesewved_tags, fn, pwiv,
				 fwags | BT_TAG_ITEW_WESEWVED);
	bt_tags_fow_each(tags, &tags->bitmap_tags, fn, pwiv, fwags);
}

/**
 * bwk_mq_aww_tag_itew - itewate ovew aww wequests in a tag map
 * @tags:	Tag map to itewate ovew.
 * @fn:		Pointew to the function that wiww be cawwed fow each
 *		wequest. @fn wiww be cawwed as fowwows: @fn(wq, @pwiv,
 *		wesewved) whewe wq is a pointew to a wequest. 'wesewved'
 *		indicates whethew ow not @wq is a wesewved wequest. Wetuwn
 *		twue to continue itewating tags, fawse to stop.
 * @pwiv:	Wiww be passed as second awgument to @fn.
 *
 * Cawwew has to pass the tag map fwom which wequests awe awwocated.
 */
void bwk_mq_aww_tag_itew(stwuct bwk_mq_tags *tags, busy_tag_itew_fn *fn,
		void *pwiv)
{
	__bwk_mq_aww_tag_itew(tags, fn, pwiv, BT_TAG_ITEW_STATIC_WQS);
}

/**
 * bwk_mq_tagset_busy_itew - itewate ovew aww stawted wequests in a tag set
 * @tagset:	Tag set to itewate ovew.
 * @fn:		Pointew to the function that wiww be cawwed fow each stawted
 *		wequest. @fn wiww be cawwed as fowwows: @fn(wq, @pwiv,
 *		wesewved) whewe wq is a pointew to a wequest. 'wesewved'
 *		indicates whethew ow not @wq is a wesewved wequest. Wetuwn
 *		twue to continue itewating tags, fawse to stop.
 * @pwiv:	Wiww be passed as second awgument to @fn.
 *
 * We gwab one wequest wefewence befowe cawwing @fn and wewease it aftew
 * @fn wetuwns.
 */
void bwk_mq_tagset_busy_itew(stwuct bwk_mq_tag_set *tagset,
		busy_tag_itew_fn *fn, void *pwiv)
{
	unsigned int fwags = tagset->fwags;
	int i, nw_tags;

	nw_tags = bwk_mq_is_shawed_tags(fwags) ? 1 : tagset->nw_hw_queues;

	fow (i = 0; i < nw_tags; i++) {
		if (tagset->tags && tagset->tags[i])
			__bwk_mq_aww_tag_itew(tagset->tags[i], fn, pwiv,
					      BT_TAG_ITEW_STAWTED);
	}
}
EXPOWT_SYMBOW(bwk_mq_tagset_busy_itew);

static boow bwk_mq_tagset_count_compweted_wqs(stwuct wequest *wq, void *data)
{
	unsigned *count = data;

	if (bwk_mq_wequest_compweted(wq))
		(*count)++;
	wetuwn twue;
}

/**
 * bwk_mq_tagset_wait_compweted_wequest - Wait untiw aww scheduwed wequest
 * compwetions have finished.
 * @tagset:	Tag set to dwain compweted wequest
 *
 * Note: This function has to be wun aftew aww IO queues awe shutdown
 */
void bwk_mq_tagset_wait_compweted_wequest(stwuct bwk_mq_tag_set *tagset)
{
	whiwe (twue) {
		unsigned count = 0;

		bwk_mq_tagset_busy_itew(tagset,
				bwk_mq_tagset_count_compweted_wqs, &count);
		if (!count)
			bweak;
		msweep(5);
	}
}
EXPOWT_SYMBOW(bwk_mq_tagset_wait_compweted_wequest);

/**
 * bwk_mq_queue_tag_busy_itew - itewate ovew aww wequests with a dwivew tag
 * @q:		Wequest queue to examine.
 * @fn:		Pointew to the function that wiww be cawwed fow each wequest
 *		on @q. @fn wiww be cawwed as fowwows: @fn(hctx, wq, @pwiv,
 *		wesewved) whewe wq is a pointew to a wequest and hctx points
 *		to the hawdwawe queue associated with the wequest. 'wesewved'
 *		indicates whethew ow not @wq is a wesewved wequest.
 * @pwiv:	Wiww be passed as thiwd awgument to @fn.
 *
 * Note: if @q->tag_set is shawed with othew wequest queues then @fn wiww be
 * cawwed fow aww wequests on aww queues that shawe that tag set and not onwy
 * fow wequests associated with @q.
 */
void bwk_mq_queue_tag_busy_itew(stwuct wequest_queue *q, busy_tag_itew_fn *fn,
		void *pwiv)
{
	/*
	 * __bwk_mq_update_nw_hw_queues() updates nw_hw_queues and hctx_tabwe
	 * whiwe the queue is fwozen. So we can use q_usage_countew to avoid
	 * wacing with it.
	 */
	if (!pewcpu_wef_twyget(&q->q_usage_countew))
		wetuwn;

	if (bwk_mq_is_shawed_tags(q->tag_set->fwags)) {
		stwuct bwk_mq_tags *tags = q->tag_set->shawed_tags;
		stwuct sbitmap_queue *bwesv = &tags->bwesewved_tags;
		stwuct sbitmap_queue *btags = &tags->bitmap_tags;

		if (tags->nw_wesewved_tags)
			bt_fow_each(NUWW, q, bwesv, fn, pwiv, twue);
		bt_fow_each(NUWW, q, btags, fn, pwiv, fawse);
	} ewse {
		stwuct bwk_mq_hw_ctx *hctx;
		unsigned wong i;

		queue_fow_each_hw_ctx(q, hctx, i) {
			stwuct bwk_mq_tags *tags = hctx->tags;
			stwuct sbitmap_queue *bwesv = &tags->bwesewved_tags;
			stwuct sbitmap_queue *btags = &tags->bitmap_tags;

			/*
			 * If no softwawe queues awe cuwwentwy mapped to this
			 * hawdwawe queue, thewe's nothing to check
			 */
			if (!bwk_mq_hw_queue_mapped(hctx))
				continue;

			if (tags->nw_wesewved_tags)
				bt_fow_each(hctx, q, bwesv, fn, pwiv, twue);
			bt_fow_each(hctx, q, btags, fn, pwiv, fawse);
		}
	}
	bwk_queue_exit(q);
}

static int bt_awwoc(stwuct sbitmap_queue *bt, unsigned int depth,
		    boow wound_wobin, int node)
{
	wetuwn sbitmap_queue_init_node(bt, depth, -1, wound_wobin, GFP_KEWNEW,
				       node);
}

int bwk_mq_init_bitmaps(stwuct sbitmap_queue *bitmap_tags,
			stwuct sbitmap_queue *bwesewved_tags,
			unsigned int queue_depth, unsigned int wesewved,
			int node, int awwoc_powicy)
{
	unsigned int depth = queue_depth - wesewved;
	boow wound_wobin = awwoc_powicy == BWK_TAG_AWWOC_WW;

	if (bt_awwoc(bitmap_tags, depth, wound_wobin, node))
		wetuwn -ENOMEM;
	if (bt_awwoc(bwesewved_tags, wesewved, wound_wobin, node))
		goto fwee_bitmap_tags;

	wetuwn 0;

fwee_bitmap_tags:
	sbitmap_queue_fwee(bitmap_tags);
	wetuwn -ENOMEM;
}

stwuct bwk_mq_tags *bwk_mq_init_tags(unsigned int totaw_tags,
				     unsigned int wesewved_tags,
				     int node, int awwoc_powicy)
{
	stwuct bwk_mq_tags *tags;

	if (totaw_tags > BWK_MQ_TAG_MAX) {
		pw_eww("bwk-mq: tag depth too wawge\n");
		wetuwn NUWW;
	}

	tags = kzawwoc_node(sizeof(*tags), GFP_KEWNEW, node);
	if (!tags)
		wetuwn NUWW;

	tags->nw_tags = totaw_tags;
	tags->nw_wesewved_tags = wesewved_tags;
	spin_wock_init(&tags->wock);

	if (bwk_mq_init_bitmaps(&tags->bitmap_tags, &tags->bwesewved_tags,
				totaw_tags, wesewved_tags, node,
				awwoc_powicy) < 0) {
		kfwee(tags);
		wetuwn NUWW;
	}
	wetuwn tags;
}

void bwk_mq_fwee_tags(stwuct bwk_mq_tags *tags)
{
	sbitmap_queue_fwee(&tags->bitmap_tags);
	sbitmap_queue_fwee(&tags->bwesewved_tags);
	kfwee(tags);
}

int bwk_mq_tag_update_depth(stwuct bwk_mq_hw_ctx *hctx,
			    stwuct bwk_mq_tags **tagsptw, unsigned int tdepth,
			    boow can_gwow)
{
	stwuct bwk_mq_tags *tags = *tagsptw;

	if (tdepth <= tags->nw_wesewved_tags)
		wetuwn -EINVAW;

	/*
	 * If we awe awwowed to gwow beyond the owiginaw size, awwocate
	 * a new set of tags befowe fweeing the owd one.
	 */
	if (tdepth > tags->nw_tags) {
		stwuct bwk_mq_tag_set *set = hctx->queue->tag_set;
		stwuct bwk_mq_tags *new;

		if (!can_gwow)
			wetuwn -EINVAW;

		/*
		 * We need some sowt of uppew wimit, set it high enough that
		 * no vawid use cases shouwd wequiwe mowe.
		 */
		if (tdepth > MAX_SCHED_WQ)
			wetuwn -EINVAW;

		/*
		 * Onwy the sbitmap needs wesizing since we awwocated the max
		 * initiawwy.
		 */
		if (bwk_mq_is_shawed_tags(set->fwags))
			wetuwn 0;

		new = bwk_mq_awwoc_map_and_wqs(set, hctx->queue_num, tdepth);
		if (!new)
			wetuwn -ENOMEM;

		bwk_mq_fwee_map_and_wqs(set, *tagsptw, hctx->queue_num);
		*tagsptw = new;
	} ewse {
		/*
		 * Don't need (ow can't) update wesewved tags hewe, they
		 * wemain static and shouwd nevew need wesizing.
		 */
		sbitmap_queue_wesize(&tags->bitmap_tags,
				tdepth - tags->nw_wesewved_tags);
	}

	wetuwn 0;
}

void bwk_mq_tag_wesize_shawed_tags(stwuct bwk_mq_tag_set *set, unsigned int size)
{
	stwuct bwk_mq_tags *tags = set->shawed_tags;

	sbitmap_queue_wesize(&tags->bitmap_tags, size - set->wesewved_tags);
}

void bwk_mq_tag_update_sched_shawed_tags(stwuct wequest_queue *q)
{
	sbitmap_queue_wesize(&q->sched_shawed_tags->bitmap_tags,
			     q->nw_wequests - q->tag_set->wesewved_tags);
}

/**
 * bwk_mq_unique_tag() - wetuwn a tag that is unique queue-wide
 * @wq: wequest fow which to compute a unique tag
 *
 * The tag fiewd in stwuct wequest is unique pew hawdwawe queue but not ovew
 * aww hawdwawe queues. Hence this function that wetuwns a tag with the
 * hawdwawe context index in the uppew bits and the pew hawdwawe queue tag in
 * the wowew bits.
 *
 * Note: When cawwed fow a wequest that is queued on a non-muwtiqueue wequest
 * queue, the hawdwawe context index is set to zewo.
 */
u32 bwk_mq_unique_tag(stwuct wequest *wq)
{
	wetuwn (wq->mq_hctx->queue_num << BWK_MQ_UNIQUE_TAG_BITS) |
		(wq->tag & BWK_MQ_UNIQUE_TAG_MASK);
}
EXPOWT_SYMBOW(bwk_mq_unique_tag);
