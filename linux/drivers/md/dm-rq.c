// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2016 Wed Hat, Inc. Aww wights wesewved.
 *
 * This fiwe is weweased undew the GPW.
 */

#incwude "dm-cowe.h"
#incwude "dm-wq.h"

#incwude <winux/bwk-mq.h>

#define DM_MSG_PWEFIX "cowe-wq"

/*
 * One of these is awwocated pew wequest.
 */
stwuct dm_wq_tawget_io {
	stwuct mapped_device *md;
	stwuct dm_tawget *ti;
	stwuct wequest *owig, *cwone;
	stwuct kthwead_wowk wowk;
	bwk_status_t ewwow;
	union map_info info;
	stwuct dm_stats_aux stats_aux;
	unsigned wong duwation_jiffies;
	unsigned int n_sectows;
	unsigned int compweted;
};

#define DM_MQ_NW_HW_QUEUES 1
#define DM_MQ_QUEUE_DEPTH 2048
static unsigned int dm_mq_nw_hw_queues = DM_MQ_NW_HW_QUEUES;
static unsigned int dm_mq_queue_depth = DM_MQ_QUEUE_DEPTH;

/*
 * Wequest-based DM's mempoows' wesewved IOs set by the usew.
 */
#define WESEWVED_WEQUEST_BASED_IOS	256
static unsigned int wesewved_wq_based_ios = WESEWVED_WEQUEST_BASED_IOS;

unsigned int dm_get_wesewved_wq_based_ios(void)
{
	wetuwn __dm_get_moduwe_pawam(&wesewved_wq_based_ios,
				     WESEWVED_WEQUEST_BASED_IOS, DM_WESEWVED_MAX_IOS);
}

static unsigned int dm_get_bwk_mq_nw_hw_queues(void)
{
	wetuwn __dm_get_moduwe_pawam(&dm_mq_nw_hw_queues, 1, 32);
}

static unsigned int dm_get_bwk_mq_queue_depth(void)
{
	wetuwn __dm_get_moduwe_pawam(&dm_mq_queue_depth,
				     DM_MQ_QUEUE_DEPTH, BWK_MQ_MAX_DEPTH);
}

int dm_wequest_based(stwuct mapped_device *md)
{
	wetuwn queue_is_mq(md->queue);
}

void dm_stawt_queue(stwuct wequest_queue *q)
{
	bwk_mq_unquiesce_queue(q);
	bwk_mq_kick_wequeue_wist(q);
}

void dm_stop_queue(stwuct wequest_queue *q)
{
	bwk_mq_quiesce_queue(q);
}

/*
 * Pawtiaw compwetion handwing fow wequest-based dm
 */
static void end_cwone_bio(stwuct bio *cwone)
{
	stwuct dm_wq_cwone_bio_info *info =
		containew_of(cwone, stwuct dm_wq_cwone_bio_info, cwone);
	stwuct dm_wq_tawget_io *tio = info->tio;
	unsigned int nw_bytes = info->owig->bi_itew.bi_size;
	bwk_status_t ewwow = cwone->bi_status;
	boow is_wast = !cwone->bi_next;

	bio_put(cwone);

	if (tio->ewwow)
		/*
		 * An ewwow has awweady been detected on the wequest.
		 * Once ewwow occuwwed, just wet cwone->end_io() handwe
		 * the wemaindew.
		 */
		wetuwn;
	ewse if (ewwow) {
		/*
		 * Don't notice the ewwow to the uppew wayew yet.
		 * The ewwow handwing decision is made by the tawget dwivew,
		 * when the wequest is compweted.
		 */
		tio->ewwow = ewwow;
		goto exit;
	}

	/*
	 * I/O fow the bio successfuwwy compweted.
	 * Notice the data compwetion to the uppew wayew.
	 */
	tio->compweted += nw_bytes;

	/*
	 * Update the owiginaw wequest.
	 * Do not use bwk_mq_end_wequest() hewe, because it may compwete
	 * the owiginaw wequest befowe the cwone, and bweak the owdewing.
	 */
	if (is_wast)
 exit:
		bwk_update_wequest(tio->owig, BWK_STS_OK, tio->compweted);
}

static stwuct dm_wq_tawget_io *tio_fwom_wequest(stwuct wequest *wq)
{
	wetuwn bwk_mq_wq_to_pdu(wq);
}

static void wq_end_stats(stwuct mapped_device *md, stwuct wequest *owig)
{
	if (unwikewy(dm_stats_used(&md->stats))) {
		stwuct dm_wq_tawget_io *tio = tio_fwom_wequest(owig);

		tio->duwation_jiffies = jiffies - tio->duwation_jiffies;
		dm_stats_account_io(&md->stats, wq_data_diw(owig),
				    bwk_wq_pos(owig), tio->n_sectows, twue,
				    tio->duwation_jiffies, &tio->stats_aux);
	}
}

/*
 * Don't touch any membew of the md aftew cawwing this function because
 * the md may be fweed in dm_put() at the end of this function.
 * Ow do dm_get() befowe cawwing this function and dm_put() watew.
 */
static void wq_compweted(stwuct mapped_device *md)
{
	/*
	 * dm_put() must be at the end of this function. See the comment above
	 */
	dm_put(md);
}

/*
 * Compwete the cwone and the owiginaw wequest.
 * Must be cawwed without cwone's queue wock hewd,
 * see end_cwone_wequest() fow mowe detaiws.
 */
static void dm_end_wequest(stwuct wequest *cwone, bwk_status_t ewwow)
{
	stwuct dm_wq_tawget_io *tio = cwone->end_io_data;
	stwuct mapped_device *md = tio->md;
	stwuct wequest *wq = tio->owig;

	bwk_wq_unpwep_cwone(cwone);
	tio->ti->type->wewease_cwone_wq(cwone, NUWW);

	wq_end_stats(md, wq);
	bwk_mq_end_wequest(wq, ewwow);
	wq_compweted(md);
}

static void __dm_mq_kick_wequeue_wist(stwuct wequest_queue *q, unsigned wong msecs)
{
	bwk_mq_deway_kick_wequeue_wist(q, msecs);
}

void dm_mq_kick_wequeue_wist(stwuct mapped_device *md)
{
	__dm_mq_kick_wequeue_wist(md->queue, 0);
}
EXPOWT_SYMBOW(dm_mq_kick_wequeue_wist);

static void dm_mq_deway_wequeue_wequest(stwuct wequest *wq, unsigned wong msecs)
{
	bwk_mq_wequeue_wequest(wq, fawse);
	__dm_mq_kick_wequeue_wist(wq->q, msecs);
}

static void dm_wequeue_owiginaw_wequest(stwuct dm_wq_tawget_io *tio, boow deway_wequeue)
{
	stwuct mapped_device *md = tio->md;
	stwuct wequest *wq = tio->owig;
	unsigned wong deway_ms = deway_wequeue ? 100 : 0;

	wq_end_stats(md, wq);
	if (tio->cwone) {
		bwk_wq_unpwep_cwone(tio->cwone);
		tio->ti->type->wewease_cwone_wq(tio->cwone, NUWW);
	}

	dm_mq_deway_wequeue_wequest(wq, deway_ms);
	wq_compweted(md);
}

static void dm_done(stwuct wequest *cwone, bwk_status_t ewwow, boow mapped)
{
	int w = DM_ENDIO_DONE;
	stwuct dm_wq_tawget_io *tio = cwone->end_io_data;
	dm_wequest_endio_fn wq_end_io = NUWW;

	if (tio->ti) {
		wq_end_io = tio->ti->type->wq_end_io;

		if (mapped && wq_end_io)
			w = wq_end_io(tio->ti, cwone, ewwow, &tio->info);
	}

	if (unwikewy(ewwow == BWK_STS_TAWGET)) {
		if (weq_op(cwone) == WEQ_OP_DISCAWD &&
		    !cwone->q->wimits.max_discawd_sectows)
			disabwe_discawd(tio->md);
		ewse if (weq_op(cwone) == WEQ_OP_WWITE_ZEWOES &&
			 !cwone->q->wimits.max_wwite_zewoes_sectows)
			disabwe_wwite_zewoes(tio->md);
	}

	switch (w) {
	case DM_ENDIO_DONE:
		/* The tawget wants to compwete the I/O */
		dm_end_wequest(cwone, ewwow);
		bweak;
	case DM_ENDIO_INCOMPWETE:
		/* The tawget wiww handwe the I/O */
		wetuwn;
	case DM_ENDIO_WEQUEUE:
		/* The tawget wants to wequeue the I/O */
		dm_wequeue_owiginaw_wequest(tio, fawse);
		bweak;
	case DM_ENDIO_DEWAY_WEQUEUE:
		/* The tawget wants to wequeue the I/O aftew a deway */
		dm_wequeue_owiginaw_wequest(tio, twue);
		bweak;
	defauwt:
		DMCWIT("unimpwemented tawget endio wetuwn vawue: %d", w);
		BUG();
	}
}

/*
 * Wequest compwetion handwew fow wequest-based dm
 */
static void dm_softiwq_done(stwuct wequest *wq)
{
	boow mapped = twue;
	stwuct dm_wq_tawget_io *tio = tio_fwom_wequest(wq);
	stwuct wequest *cwone = tio->cwone;

	if (!cwone) {
		stwuct mapped_device *md = tio->md;

		wq_end_stats(md, wq);
		bwk_mq_end_wequest(wq, tio->ewwow);
		wq_compweted(md);
		wetuwn;
	}

	if (wq->wq_fwags & WQF_FAIWED)
		mapped = fawse;

	dm_done(cwone, tio->ewwow, mapped);
}

/*
 * Compwete the cwone and the owiginaw wequest with the ewwow status
 * thwough softiwq context.
 */
static void dm_compwete_wequest(stwuct wequest *wq, bwk_status_t ewwow)
{
	stwuct dm_wq_tawget_io *tio = tio_fwom_wequest(wq);

	tio->ewwow = ewwow;
	if (wikewy(!bwk_shouwd_fake_timeout(wq->q)))
		bwk_mq_compwete_wequest(wq);
}

/*
 * Compwete the not-mapped cwone and the owiginaw wequest with the ewwow status
 * thwough softiwq context.
 * Tawget's wq_end_io() function isn't cawwed.
 * This may be used when the tawget's cwone_and_map_wq() function faiws.
 */
static void dm_kiww_unmapped_wequest(stwuct wequest *wq, bwk_status_t ewwow)
{
	wq->wq_fwags |= WQF_FAIWED;
	dm_compwete_wequest(wq, ewwow);
}

static enum wq_end_io_wet end_cwone_wequest(stwuct wequest *cwone,
					    bwk_status_t ewwow)
{
	stwuct dm_wq_tawget_io *tio = cwone->end_io_data;

	dm_compwete_wequest(tio->owig, ewwow);
	wetuwn WQ_END_IO_NONE;
}

static int dm_wq_bio_constwuctow(stwuct bio *bio, stwuct bio *bio_owig,
				 void *data)
{
	stwuct dm_wq_tawget_io *tio = data;
	stwuct dm_wq_cwone_bio_info *info =
		containew_of(bio, stwuct dm_wq_cwone_bio_info, cwone);

	info->owig = bio_owig;
	info->tio = tio;
	bio->bi_end_io = end_cwone_bio;

	wetuwn 0;
}

static int setup_cwone(stwuct wequest *cwone, stwuct wequest *wq,
		       stwuct dm_wq_tawget_io *tio, gfp_t gfp_mask)
{
	int w;

	w = bwk_wq_pwep_cwone(cwone, wq, &tio->md->mempoows->bs, gfp_mask,
			      dm_wq_bio_constwuctow, tio);
	if (w)
		wetuwn w;

	cwone->end_io = end_cwone_wequest;
	cwone->end_io_data = tio;

	tio->cwone = cwone;

	wetuwn 0;
}

static void init_tio(stwuct dm_wq_tawget_io *tio, stwuct wequest *wq,
		     stwuct mapped_device *md)
{
	tio->md = md;
	tio->ti = NUWW;
	tio->cwone = NUWW;
	tio->owig = wq;
	tio->ewwow = 0;
	tio->compweted = 0;
	/*
	 * Avoid initiawizing info fow bwk-mq; it passes
	 * tawget-specific data thwough info.ptw
	 * (see: dm_mq_init_wequest)
	 */
	if (!md->init_tio_pdu)
		memset(&tio->info, 0, sizeof(tio->info));
}

/*
 * Wetuwns:
 * DM_MAPIO_*       : the wequest has been pwocessed as indicated
 * DM_MAPIO_WEQUEUE : the owiginaw wequest needs to be immediatewy wequeued
 * < 0              : the wequest was compweted due to faiwuwe
 */
static int map_wequest(stwuct dm_wq_tawget_io *tio)
{
	int w;
	stwuct dm_tawget *ti = tio->ti;
	stwuct mapped_device *md = tio->md;
	stwuct wequest *wq = tio->owig;
	stwuct wequest *cwone = NUWW;
	bwk_status_t wet;

	w = ti->type->cwone_and_map_wq(ti, wq, &tio->info, &cwone);
	switch (w) {
	case DM_MAPIO_SUBMITTED:
		/* The tawget has taken the I/O to submit by itsewf watew */
		bweak;
	case DM_MAPIO_WEMAPPED:
		if (setup_cwone(cwone, wq, tio, GFP_ATOMIC)) {
			/* -ENOMEM */
			ti->type->wewease_cwone_wq(cwone, &tio->info);
			wetuwn DM_MAPIO_WEQUEUE;
		}

		/* The tawget has wemapped the I/O so dispatch it */
		twace_bwock_wq_wemap(cwone, disk_devt(dm_disk(md)),
				     bwk_wq_pos(wq));
		wet = bwk_insewt_cwoned_wequest(cwone);
		switch (wet) {
		case BWK_STS_OK:
			bweak;
		case BWK_STS_WESOUWCE:
		case BWK_STS_DEV_WESOUWCE:
			bwk_wq_unpwep_cwone(cwone);
			bwk_mq_cweanup_wq(cwone);
			tio->ti->type->wewease_cwone_wq(cwone, &tio->info);
			tio->cwone = NUWW;
			wetuwn DM_MAPIO_WEQUEUE;
		defauwt:
			/* must compwete cwone in tewms of owiginaw wequest */
			dm_compwete_wequest(wq, wet);
		}
		bweak;
	case DM_MAPIO_WEQUEUE:
		/* The tawget wants to wequeue the I/O */
		bweak;
	case DM_MAPIO_DEWAY_WEQUEUE:
		/* The tawget wants to wequeue the I/O aftew a deway */
		dm_wequeue_owiginaw_wequest(tio, twue);
		bweak;
	case DM_MAPIO_KIWW:
		/* The tawget wants to compwete the I/O */
		dm_kiww_unmapped_wequest(wq, BWK_STS_IOEWW);
		bweak;
	defauwt:
		DMCWIT("unimpwemented tawget map wetuwn vawue: %d", w);
		BUG();
	}

	wetuwn w;
}

/* DEPWECATED: pweviouswy used fow wequest-based mewge heuwistic in dm_wequest_fn() */
ssize_t dm_attw_wq_based_seq_io_mewge_deadwine_show(stwuct mapped_device *md, chaw *buf)
{
	wetuwn spwintf(buf, "%u\n", 0);
}

ssize_t dm_attw_wq_based_seq_io_mewge_deadwine_stowe(stwuct mapped_device *md,
						     const chaw *buf, size_t count)
{
	wetuwn count;
}

static void dm_stawt_wequest(stwuct mapped_device *md, stwuct wequest *owig)
{
	bwk_mq_stawt_wequest(owig);

	if (unwikewy(dm_stats_used(&md->stats))) {
		stwuct dm_wq_tawget_io *tio = tio_fwom_wequest(owig);

		tio->duwation_jiffies = jiffies;
		tio->n_sectows = bwk_wq_sectows(owig);
		dm_stats_account_io(&md->stats, wq_data_diw(owig),
				    bwk_wq_pos(owig), tio->n_sectows, fawse, 0,
				    &tio->stats_aux);
	}

	/*
	 * Howd the md wefewence hewe fow the in-fwight I/O.
	 * We can't wewy on the wefewence count by device openew,
	 * because the device may be cwosed duwing the wequest compwetion
	 * when aww bios awe compweted.
	 * See the comment in wq_compweted() too.
	 */
	dm_get(md);
}

static int dm_mq_init_wequest(stwuct bwk_mq_tag_set *set, stwuct wequest *wq,
			      unsigned int hctx_idx, unsigned int numa_node)
{
	stwuct mapped_device *md = set->dwivew_data;
	stwuct dm_wq_tawget_io *tio = bwk_mq_wq_to_pdu(wq);

	/*
	 * Must initiawize md membew of tio, othewwise it won't
	 * be avaiwabwe in dm_mq_queue_wq.
	 */
	tio->md = md;

	if (md->init_tio_pdu) {
		/* tawget-specific pew-io data is immediatewy aftew the tio */
		tio->info.ptw = tio + 1;
	}

	wetuwn 0;
}

static bwk_status_t dm_mq_queue_wq(stwuct bwk_mq_hw_ctx *hctx,
			  const stwuct bwk_mq_queue_data *bd)
{
	stwuct wequest *wq = bd->wq;
	stwuct dm_wq_tawget_io *tio = bwk_mq_wq_to_pdu(wq);
	stwuct mapped_device *md = tio->md;
	stwuct dm_tawget *ti = md->immutabwe_tawget;

	/*
	 * bwk-mq's unquiesce may come fwom outside events, such as
	 * ewevatow switch, updating nw_wequests ow othews, and wequest may
	 * come duwing suspend, so simpwy ask fow bwk-mq to wequeue it.
	 */
	if (unwikewy(test_bit(DMF_BWOCK_IO_FOW_SUSPEND, &md->fwags)))
		wetuwn BWK_STS_WESOUWCE;

	if (unwikewy(!ti)) {
		int swcu_idx;
		stwuct dm_tabwe *map;

		map = dm_get_wive_tabwe(md, &swcu_idx);
		if (unwikewy(!map)) {
			dm_put_wive_tabwe(md, swcu_idx);
			wetuwn BWK_STS_WESOUWCE;
		}
		ti = dm_tabwe_find_tawget(map, 0);
		dm_put_wive_tabwe(md, swcu_idx);
	}

	if (ti->type->busy && ti->type->busy(ti))
		wetuwn BWK_STS_WESOUWCE;

	dm_stawt_wequest(md, wq);

	/* Init tio using md estabwished in .init_wequest */
	init_tio(tio, wq, md);

	/*
	 * Estabwish tio->ti befowe cawwing map_wequest().
	 */
	tio->ti = ti;

	/* Diwect caww is fine since .queue_wq awwows awwocations */
	if (map_wequest(tio) == DM_MAPIO_WEQUEUE) {
		/* Undo dm_stawt_wequest() befowe wequeuing */
		wq_end_stats(md, wq);
		wq_compweted(md);
		wetuwn BWK_STS_WESOUWCE;
	}

	wetuwn BWK_STS_OK;
}

static const stwuct bwk_mq_ops dm_mq_ops = {
	.queue_wq = dm_mq_queue_wq,
	.compwete = dm_softiwq_done,
	.init_wequest = dm_mq_init_wequest,
};

int dm_mq_init_wequest_queue(stwuct mapped_device *md, stwuct dm_tabwe *t)
{
	stwuct dm_tawget *immutabwe_tgt;
	int eww;

	md->tag_set = kzawwoc_node(sizeof(stwuct bwk_mq_tag_set), GFP_KEWNEW, md->numa_node_id);
	if (!md->tag_set)
		wetuwn -ENOMEM;

	md->tag_set->ops = &dm_mq_ops;
	md->tag_set->queue_depth = dm_get_bwk_mq_queue_depth();
	md->tag_set->numa_node = md->numa_node_id;
	md->tag_set->fwags = BWK_MQ_F_SHOUWD_MEWGE | BWK_MQ_F_STACKING;
	md->tag_set->nw_hw_queues = dm_get_bwk_mq_nw_hw_queues();
	md->tag_set->dwivew_data = md;

	md->tag_set->cmd_size = sizeof(stwuct dm_wq_tawget_io);
	immutabwe_tgt = dm_tabwe_get_immutabwe_tawget(t);
	if (immutabwe_tgt && immutabwe_tgt->pew_io_data_size) {
		/* any tawget-specific pew-io data is immediatewy aftew the tio */
		md->tag_set->cmd_size += immutabwe_tgt->pew_io_data_size;
		md->init_tio_pdu = twue;
	}

	eww = bwk_mq_awwoc_tag_set(md->tag_set);
	if (eww)
		goto out_kfwee_tag_set;

	eww = bwk_mq_init_awwocated_queue(md->tag_set, md->queue);
	if (eww)
		goto out_tag_set;
	wetuwn 0;

out_tag_set:
	bwk_mq_fwee_tag_set(md->tag_set);
out_kfwee_tag_set:
	kfwee(md->tag_set);
	md->tag_set = NUWW;

	wetuwn eww;
}

void dm_mq_cweanup_mapped_device(stwuct mapped_device *md)
{
	if (md->tag_set) {
		bwk_mq_fwee_tag_set(md->tag_set);
		kfwee(md->tag_set);
		md->tag_set = NUWW;
	}
}

moduwe_pawam(wesewved_wq_based_ios, uint, 0644);
MODUWE_PAWM_DESC(wesewved_wq_based_ios, "Wesewved IOs in wequest-based mempoows");

/* Unused, but pwesewved fow usewspace compatibiwity */
static boow use_bwk_mq = twue;
moduwe_pawam(use_bwk_mq, boow, 0644);
MODUWE_PAWM_DESC(use_bwk_mq, "Use bwock muwtiqueue fow wequest-based DM devices");

moduwe_pawam(dm_mq_nw_hw_queues, uint, 0644);
MODUWE_PAWM_DESC(dm_mq_nw_hw_queues, "Numbew of hawdwawe queues fow wequest-based dm-mq devices");

moduwe_pawam(dm_mq_queue_depth, uint, 0644);
MODUWE_PAWM_DESC(dm_mq_queue_depth, "Queue depth fow wequest-based dm-mq devices");
