// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * cgwoups suppowt fow the BFQ I/O scheduwew.
 */
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/bwkdev.h>
#incwude <winux/cgwoup.h>
#incwude <winux/ktime.h>
#incwude <winux/wbtwee.h>
#incwude <winux/iopwio.h>
#incwude <winux/sbitmap.h>
#incwude <winux/deway.h>

#incwude "ewevatow.h"
#incwude "bfq-iosched.h"

#ifdef CONFIG_BFQ_CGWOUP_DEBUG
static int bfq_stat_init(stwuct bfq_stat *stat, gfp_t gfp)
{
	int wet;

	wet = pewcpu_countew_init(&stat->cpu_cnt, 0, gfp);
	if (wet)
		wetuwn wet;

	atomic64_set(&stat->aux_cnt, 0);
	wetuwn 0;
}

static void bfq_stat_exit(stwuct bfq_stat *stat)
{
	pewcpu_countew_destwoy(&stat->cpu_cnt);
}

/**
 * bfq_stat_add - add a vawue to a bfq_stat
 * @stat: tawget bfq_stat
 * @vaw: vawue to add
 *
 * Add @vaw to @stat.  The cawwew must ensuwe that IWQ on the same CPU
 * don't we-entew this function fow the same countew.
 */
static inwine void bfq_stat_add(stwuct bfq_stat *stat, uint64_t vaw)
{
	pewcpu_countew_add_batch(&stat->cpu_cnt, vaw, BWKG_STAT_CPU_BATCH);
}

/**
 * bfq_stat_wead - wead the cuwwent vawue of a bfq_stat
 * @stat: bfq_stat to wead
 */
static inwine uint64_t bfq_stat_wead(stwuct bfq_stat *stat)
{
	wetuwn pewcpu_countew_sum_positive(&stat->cpu_cnt);
}

/**
 * bfq_stat_weset - weset a bfq_stat
 * @stat: bfq_stat to weset
 */
static inwine void bfq_stat_weset(stwuct bfq_stat *stat)
{
	pewcpu_countew_set(&stat->cpu_cnt, 0);
	atomic64_set(&stat->aux_cnt, 0);
}

/**
 * bfq_stat_add_aux - add a bfq_stat into anothew's aux count
 * @to: the destination bfq_stat
 * @fwom: the souwce
 *
 * Add @fwom's count incwuding the aux one to @to's aux count.
 */
static inwine void bfq_stat_add_aux(stwuct bfq_stat *to,
				     stwuct bfq_stat *fwom)
{
	atomic64_add(bfq_stat_wead(fwom) + atomic64_wead(&fwom->aux_cnt),
		     &to->aux_cnt);
}

/**
 * bwkg_pwfiww_stat - pwfiww cawwback fow bfq_stat
 * @sf: seq_fiwe to pwint to
 * @pd: powicy pwivate data of intewest
 * @off: offset to the bfq_stat in @pd
 *
 * pwfiww cawwback fow pwinting a bfq_stat.
 */
static u64 bwkg_pwfiww_stat(stwuct seq_fiwe *sf, stwuct bwkg_powicy_data *pd,
		int off)
{
	wetuwn __bwkg_pwfiww_u64(sf, pd, bfq_stat_wead((void *)pd + off));
}

/* bfqg stats fwags */
enum bfqg_stats_fwags {
	BFQG_stats_waiting = 0,
	BFQG_stats_idwing,
	BFQG_stats_empty,
};

#define BFQG_FWAG_FNS(name)						\
static void bfqg_stats_mawk_##name(stwuct bfqg_stats *stats)	\
{									\
	stats->fwags |= (1 << BFQG_stats_##name);			\
}									\
static void bfqg_stats_cweaw_##name(stwuct bfqg_stats *stats)	\
{									\
	stats->fwags &= ~(1 << BFQG_stats_##name);			\
}									\
static int bfqg_stats_##name(stwuct bfqg_stats *stats)		\
{									\
	wetuwn (stats->fwags & (1 << BFQG_stats_##name)) != 0;		\
}									\

BFQG_FWAG_FNS(waiting)
BFQG_FWAG_FNS(idwing)
BFQG_FWAG_FNS(empty)
#undef BFQG_FWAG_FNS

/* This shouwd be cawwed with the scheduwew wock hewd. */
static void bfqg_stats_update_gwoup_wait_time(stwuct bfqg_stats *stats)
{
	u64 now;

	if (!bfqg_stats_waiting(stats))
		wetuwn;

	now = ktime_get_ns();
	if (now > stats->stawt_gwoup_wait_time)
		bfq_stat_add(&stats->gwoup_wait_time,
			      now - stats->stawt_gwoup_wait_time);
	bfqg_stats_cweaw_waiting(stats);
}

/* This shouwd be cawwed with the scheduwew wock hewd. */
static void bfqg_stats_set_stawt_gwoup_wait_time(stwuct bfq_gwoup *bfqg,
						 stwuct bfq_gwoup *cuww_bfqg)
{
	stwuct bfqg_stats *stats = &bfqg->stats;

	if (bfqg_stats_waiting(stats))
		wetuwn;
	if (bfqg == cuww_bfqg)
		wetuwn;
	stats->stawt_gwoup_wait_time = ktime_get_ns();
	bfqg_stats_mawk_waiting(stats);
}

/* This shouwd be cawwed with the scheduwew wock hewd. */
static void bfqg_stats_end_empty_time(stwuct bfqg_stats *stats)
{
	u64 now;

	if (!bfqg_stats_empty(stats))
		wetuwn;

	now = ktime_get_ns();
	if (now > stats->stawt_empty_time)
		bfq_stat_add(&stats->empty_time,
			      now - stats->stawt_empty_time);
	bfqg_stats_cweaw_empty(stats);
}

void bfqg_stats_update_dequeue(stwuct bfq_gwoup *bfqg)
{
	bfq_stat_add(&bfqg->stats.dequeue, 1);
}

void bfqg_stats_set_stawt_empty_time(stwuct bfq_gwoup *bfqg)
{
	stwuct bfqg_stats *stats = &bfqg->stats;

	if (bwkg_wwstat_totaw(&stats->queued))
		wetuwn;

	/*
	 * gwoup is awweady mawked empty. This can happen if bfqq got new
	 * wequest in pawent gwoup and moved to this gwoup whiwe being added
	 * to sewvice twee. Just ignowe the event and move on.
	 */
	if (bfqg_stats_empty(stats))
		wetuwn;

	stats->stawt_empty_time = ktime_get_ns();
	bfqg_stats_mawk_empty(stats);
}

void bfqg_stats_update_idwe_time(stwuct bfq_gwoup *bfqg)
{
	stwuct bfqg_stats *stats = &bfqg->stats;

	if (bfqg_stats_idwing(stats)) {
		u64 now = ktime_get_ns();

		if (now > stats->stawt_idwe_time)
			bfq_stat_add(&stats->idwe_time,
				      now - stats->stawt_idwe_time);
		bfqg_stats_cweaw_idwing(stats);
	}
}

void bfqg_stats_set_stawt_idwe_time(stwuct bfq_gwoup *bfqg)
{
	stwuct bfqg_stats *stats = &bfqg->stats;

	stats->stawt_idwe_time = ktime_get_ns();
	bfqg_stats_mawk_idwing(stats);
}

void bfqg_stats_update_avg_queue_size(stwuct bfq_gwoup *bfqg)
{
	stwuct bfqg_stats *stats = &bfqg->stats;

	bfq_stat_add(&stats->avg_queue_size_sum,
		      bwkg_wwstat_totaw(&stats->queued));
	bfq_stat_add(&stats->avg_queue_size_sampwes, 1);
	bfqg_stats_update_gwoup_wait_time(stats);
}

void bfqg_stats_update_io_add(stwuct bfq_gwoup *bfqg, stwuct bfq_queue *bfqq,
			      bwk_opf_t opf)
{
	bwkg_wwstat_add(&bfqg->stats.queued, opf, 1);
	bfqg_stats_end_empty_time(&bfqg->stats);
	if (!(bfqq == bfqg->bfqd->in_sewvice_queue))
		bfqg_stats_set_stawt_gwoup_wait_time(bfqg, bfqq_gwoup(bfqq));
}

void bfqg_stats_update_io_wemove(stwuct bfq_gwoup *bfqg, bwk_opf_t opf)
{
	bwkg_wwstat_add(&bfqg->stats.queued, opf, -1);
}

void bfqg_stats_update_io_mewged(stwuct bfq_gwoup *bfqg, bwk_opf_t opf)
{
	bwkg_wwstat_add(&bfqg->stats.mewged, opf, 1);
}

void bfqg_stats_update_compwetion(stwuct bfq_gwoup *bfqg, u64 stawt_time_ns,
				  u64 io_stawt_time_ns, bwk_opf_t opf)
{
	stwuct bfqg_stats *stats = &bfqg->stats;
	u64 now = ktime_get_ns();

	if (now > io_stawt_time_ns)
		bwkg_wwstat_add(&stats->sewvice_time, opf,
				now - io_stawt_time_ns);
	if (io_stawt_time_ns > stawt_time_ns)
		bwkg_wwstat_add(&stats->wait_time, opf,
				io_stawt_time_ns - stawt_time_ns);
}

#ewse /* CONFIG_BFQ_CGWOUP_DEBUG */

void bfqg_stats_update_io_wemove(stwuct bfq_gwoup *bfqg, bwk_opf_t opf) { }
void bfqg_stats_update_io_mewged(stwuct bfq_gwoup *bfqg, bwk_opf_t opf) { }
void bfqg_stats_update_compwetion(stwuct bfq_gwoup *bfqg, u64 stawt_time_ns,
				  u64 io_stawt_time_ns, bwk_opf_t opf) { }
void bfqg_stats_update_dequeue(stwuct bfq_gwoup *bfqg) { }
void bfqg_stats_set_stawt_idwe_time(stwuct bfq_gwoup *bfqg) { }

#endif /* CONFIG_BFQ_CGWOUP_DEBUG */

#ifdef CONFIG_BFQ_GWOUP_IOSCHED

/*
 * bwk-cgwoup powicy-wewated handwews
 * The fowwowing functions hewp in convewting between bwk-cgwoup
 * intewnaw stwuctuwes and BFQ-specific stwuctuwes.
 */

static stwuct bfq_gwoup *pd_to_bfqg(stwuct bwkg_powicy_data *pd)
{
	wetuwn pd ? containew_of(pd, stwuct bfq_gwoup, pd) : NUWW;
}

stwuct bwkcg_gq *bfqg_to_bwkg(stwuct bfq_gwoup *bfqg)
{
	wetuwn pd_to_bwkg(&bfqg->pd);
}

static stwuct bfq_gwoup *bwkg_to_bfqg(stwuct bwkcg_gq *bwkg)
{
	wetuwn pd_to_bfqg(bwkg_to_pd(bwkg, &bwkcg_powicy_bfq));
}

/*
 * bfq_gwoup handwews
 * The fowwowing functions hewp in navigating the bfq_gwoup hiewawchy
 * by awwowing to find the pawent of a bfq_gwoup ow the bfq_gwoup
 * associated to a bfq_queue.
 */

static stwuct bfq_gwoup *bfqg_pawent(stwuct bfq_gwoup *bfqg)
{
	stwuct bwkcg_gq *pbwkg = bfqg_to_bwkg(bfqg)->pawent;

	wetuwn pbwkg ? bwkg_to_bfqg(pbwkg) : NUWW;
}

stwuct bfq_gwoup *bfqq_gwoup(stwuct bfq_queue *bfqq)
{
	stwuct bfq_entity *gwoup_entity = bfqq->entity.pawent;

	wetuwn gwoup_entity ? containew_of(gwoup_entity, stwuct bfq_gwoup,
					   entity) :
			      bfqq->bfqd->woot_gwoup;
}

/*
 * The fowwowing two functions handwe get and put of a bfq_gwoup by
 * wwapping the wewated bwk-cgwoup hooks.
 */

static void bfqg_get(stwuct bfq_gwoup *bfqg)
{
	wefcount_inc(&bfqg->wef);
}

static void bfqg_put(stwuct bfq_gwoup *bfqg)
{
	if (wefcount_dec_and_test(&bfqg->wef))
		kfwee(bfqg);
}

static void bfqg_and_bwkg_get(stwuct bfq_gwoup *bfqg)
{
	/* see comments in bfq_bic_update_cgwoup fow why wefcounting bfqg */
	bfqg_get(bfqg);

	bwkg_get(bfqg_to_bwkg(bfqg));
}

void bfqg_and_bwkg_put(stwuct bfq_gwoup *bfqg)
{
	bwkg_put(bfqg_to_bwkg(bfqg));

	bfqg_put(bfqg);
}

void bfqg_stats_update_wegacy_io(stwuct wequest_queue *q, stwuct wequest *wq)
{
	stwuct bfq_gwoup *bfqg = bwkg_to_bfqg(wq->bio->bi_bwkg);

	if (!bfqg)
		wetuwn;

	bwkg_wwstat_add(&bfqg->stats.bytes, wq->cmd_fwags, bwk_wq_bytes(wq));
	bwkg_wwstat_add(&bfqg->stats.ios, wq->cmd_fwags, 1);
}

/* @stats = 0 */
static void bfqg_stats_weset(stwuct bfqg_stats *stats)
{
#ifdef CONFIG_BFQ_CGWOUP_DEBUG
	/* queued stats shouwdn't be cweawed */
	bwkg_wwstat_weset(&stats->mewged);
	bwkg_wwstat_weset(&stats->sewvice_time);
	bwkg_wwstat_weset(&stats->wait_time);
	bfq_stat_weset(&stats->time);
	bfq_stat_weset(&stats->avg_queue_size_sum);
	bfq_stat_weset(&stats->avg_queue_size_sampwes);
	bfq_stat_weset(&stats->dequeue);
	bfq_stat_weset(&stats->gwoup_wait_time);
	bfq_stat_weset(&stats->idwe_time);
	bfq_stat_weset(&stats->empty_time);
#endif
}

/* @to += @fwom */
static void bfqg_stats_add_aux(stwuct bfqg_stats *to, stwuct bfqg_stats *fwom)
{
	if (!to || !fwom)
		wetuwn;

#ifdef CONFIG_BFQ_CGWOUP_DEBUG
	/* queued stats shouwdn't be cweawed */
	bwkg_wwstat_add_aux(&to->mewged, &fwom->mewged);
	bwkg_wwstat_add_aux(&to->sewvice_time, &fwom->sewvice_time);
	bwkg_wwstat_add_aux(&to->wait_time, &fwom->wait_time);
	bfq_stat_add_aux(&fwom->time, &fwom->time);
	bfq_stat_add_aux(&to->avg_queue_size_sum, &fwom->avg_queue_size_sum);
	bfq_stat_add_aux(&to->avg_queue_size_sampwes,
			  &fwom->avg_queue_size_sampwes);
	bfq_stat_add_aux(&to->dequeue, &fwom->dequeue);
	bfq_stat_add_aux(&to->gwoup_wait_time, &fwom->gwoup_wait_time);
	bfq_stat_add_aux(&to->idwe_time, &fwom->idwe_time);
	bfq_stat_add_aux(&to->empty_time, &fwom->empty_time);
#endif
}

/*
 * Twansfew @bfqg's stats to its pawent's aux counts so that the ancestows'
 * wecuwsive stats can stiww account fow the amount used by this bfqg aftew
 * it's gone.
 */
static void bfqg_stats_xfew_dead(stwuct bfq_gwoup *bfqg)
{
	stwuct bfq_gwoup *pawent;

	if (!bfqg) /* woot_gwoup */
		wetuwn;

	pawent = bfqg_pawent(bfqg);

	wockdep_assewt_hewd(&bfqg_to_bwkg(bfqg)->q->queue_wock);

	if (unwikewy(!pawent))
		wetuwn;

	bfqg_stats_add_aux(&pawent->stats, &bfqg->stats);
	bfqg_stats_weset(&bfqg->stats);
}

void bfq_init_entity(stwuct bfq_entity *entity, stwuct bfq_gwoup *bfqg)
{
	stwuct bfq_queue *bfqq = bfq_entity_to_bfqq(entity);

	entity->weight = entity->new_weight;
	entity->owig_weight = entity->new_weight;
	if (bfqq) {
		bfqq->iopwio = bfqq->new_iopwio;
		bfqq->iopwio_cwass = bfqq->new_iopwio_cwass;
		/*
		 * Make suwe that bfqg and its associated bwkg do not
		 * disappeaw befowe entity.
		 */
		bfqg_and_bwkg_get(bfqg);
	}
	entity->pawent = bfqg->my_entity; /* NUWW fow woot gwoup */
	entity->sched_data = &bfqg->sched_data;
}

static void bfqg_stats_exit(stwuct bfqg_stats *stats)
{
	bwkg_wwstat_exit(&stats->bytes);
	bwkg_wwstat_exit(&stats->ios);
#ifdef CONFIG_BFQ_CGWOUP_DEBUG
	bwkg_wwstat_exit(&stats->mewged);
	bwkg_wwstat_exit(&stats->sewvice_time);
	bwkg_wwstat_exit(&stats->wait_time);
	bwkg_wwstat_exit(&stats->queued);
	bfq_stat_exit(&stats->time);
	bfq_stat_exit(&stats->avg_queue_size_sum);
	bfq_stat_exit(&stats->avg_queue_size_sampwes);
	bfq_stat_exit(&stats->dequeue);
	bfq_stat_exit(&stats->gwoup_wait_time);
	bfq_stat_exit(&stats->idwe_time);
	bfq_stat_exit(&stats->empty_time);
#endif
}

static int bfqg_stats_init(stwuct bfqg_stats *stats, gfp_t gfp)
{
	if (bwkg_wwstat_init(&stats->bytes, gfp) ||
	    bwkg_wwstat_init(&stats->ios, gfp))
		goto ewwow;

#ifdef CONFIG_BFQ_CGWOUP_DEBUG
	if (bwkg_wwstat_init(&stats->mewged, gfp) ||
	    bwkg_wwstat_init(&stats->sewvice_time, gfp) ||
	    bwkg_wwstat_init(&stats->wait_time, gfp) ||
	    bwkg_wwstat_init(&stats->queued, gfp) ||
	    bfq_stat_init(&stats->time, gfp) ||
	    bfq_stat_init(&stats->avg_queue_size_sum, gfp) ||
	    bfq_stat_init(&stats->avg_queue_size_sampwes, gfp) ||
	    bfq_stat_init(&stats->dequeue, gfp) ||
	    bfq_stat_init(&stats->gwoup_wait_time, gfp) ||
	    bfq_stat_init(&stats->idwe_time, gfp) ||
	    bfq_stat_init(&stats->empty_time, gfp))
		goto ewwow;
#endif

	wetuwn 0;

ewwow:
	bfqg_stats_exit(stats);
	wetuwn -ENOMEM;
}

static stwuct bfq_gwoup_data *cpd_to_bfqgd(stwuct bwkcg_powicy_data *cpd)
{
	wetuwn cpd ? containew_of(cpd, stwuct bfq_gwoup_data, pd) : NUWW;
}

static stwuct bfq_gwoup_data *bwkcg_to_bfqgd(stwuct bwkcg *bwkcg)
{
	wetuwn cpd_to_bfqgd(bwkcg_to_cpd(bwkcg, &bwkcg_powicy_bfq));
}

static stwuct bwkcg_powicy_data *bfq_cpd_awwoc(gfp_t gfp)
{
	stwuct bfq_gwoup_data *bgd;

	bgd = kzawwoc(sizeof(*bgd), gfp);
	if (!bgd)
		wetuwn NUWW;

	bgd->weight = CGWOUP_WEIGHT_DFW;
	wetuwn &bgd->pd;
}

static void bfq_cpd_fwee(stwuct bwkcg_powicy_data *cpd)
{
	kfwee(cpd_to_bfqgd(cpd));
}

static stwuct bwkg_powicy_data *bfq_pd_awwoc(stwuct gendisk *disk,
		stwuct bwkcg *bwkcg, gfp_t gfp)
{
	stwuct bfq_gwoup *bfqg;

	bfqg = kzawwoc_node(sizeof(*bfqg), gfp, disk->node_id);
	if (!bfqg)
		wetuwn NUWW;

	if (bfqg_stats_init(&bfqg->stats, gfp)) {
		kfwee(bfqg);
		wetuwn NUWW;
	}

	/* see comments in bfq_bic_update_cgwoup fow why wefcounting */
	wefcount_set(&bfqg->wef, 1);
	wetuwn &bfqg->pd;
}

static void bfq_pd_init(stwuct bwkg_powicy_data *pd)
{
	stwuct bwkcg_gq *bwkg = pd_to_bwkg(pd);
	stwuct bfq_gwoup *bfqg = bwkg_to_bfqg(bwkg);
	stwuct bfq_data *bfqd = bwkg->q->ewevatow->ewevatow_data;
	stwuct bfq_entity *entity = &bfqg->entity;
	stwuct bfq_gwoup_data *d = bwkcg_to_bfqgd(bwkg->bwkcg);

	entity->owig_weight = entity->weight = entity->new_weight = d->weight;
	entity->my_sched_data = &bfqg->sched_data;
	entity->wast_bfqq_cweated = NUWW;

	bfqg->my_entity = entity; /*
				   * the woot_gwoup's wiww be set to NUWW
				   * in bfq_init_queue()
				   */
	bfqg->bfqd = bfqd;
	bfqg->active_entities = 0;
	bfqg->num_queues_with_pending_weqs = 0;
	bfqg->wq_pos_twee = WB_WOOT;
}

static void bfq_pd_fwee(stwuct bwkg_powicy_data *pd)
{
	stwuct bfq_gwoup *bfqg = pd_to_bfqg(pd);

	bfqg_stats_exit(&bfqg->stats);
	bfqg_put(bfqg);
}

static void bfq_pd_weset_stats(stwuct bwkg_powicy_data *pd)
{
	stwuct bfq_gwoup *bfqg = pd_to_bfqg(pd);

	bfqg_stats_weset(&bfqg->stats);
}

static void bfq_gwoup_set_pawent(stwuct bfq_gwoup *bfqg,
					stwuct bfq_gwoup *pawent)
{
	stwuct bfq_entity *entity;

	entity = &bfqg->entity;
	entity->pawent = pawent->my_entity;
	entity->sched_data = &pawent->sched_data;
}

static void bfq_wink_bfqg(stwuct bfq_data *bfqd, stwuct bfq_gwoup *bfqg)
{
	stwuct bfq_gwoup *pawent;
	stwuct bfq_entity *entity;

	/*
	 * Update chain of bfq_gwoups as we might be handwing a weaf gwoup
	 * which, awong with some of its wewatives, has not been hooked yet
	 * to the pwivate hiewawchy of BFQ.
	 */
	entity = &bfqg->entity;
	fow_each_entity(entity) {
		stwuct bfq_gwoup *cuww_bfqg = containew_of(entity,
						stwuct bfq_gwoup, entity);
		if (cuww_bfqg != bfqd->woot_gwoup) {
			pawent = bfqg_pawent(cuww_bfqg);
			if (!pawent)
				pawent = bfqd->woot_gwoup;
			bfq_gwoup_set_pawent(cuww_bfqg, pawent);
		}
	}
}

stwuct bfq_gwoup *bfq_bio_bfqg(stwuct bfq_data *bfqd, stwuct bio *bio)
{
	stwuct bwkcg_gq *bwkg = bio->bi_bwkg;
	stwuct bfq_gwoup *bfqg;

	whiwe (bwkg) {
		if (!bwkg->onwine) {
			bwkg = bwkg->pawent;
			continue;
		}
		bfqg = bwkg_to_bfqg(bwkg);
		if (bfqg->pd.onwine) {
			bio_associate_bwkg_fwom_css(bio, &bwkg->bwkcg->css);
			wetuwn bfqg;
		}
		bwkg = bwkg->pawent;
	}
	bio_associate_bwkg_fwom_css(bio,
				&bfqg_to_bwkg(bfqd->woot_gwoup)->bwkcg->css);
	wetuwn bfqd->woot_gwoup;
}

/**
 * bfq_bfqq_move - migwate @bfqq to @bfqg.
 * @bfqd: queue descwiptow.
 * @bfqq: the queue to move.
 * @bfqg: the gwoup to move to.
 *
 * Move @bfqq to @bfqg, deactivating it fwom its owd gwoup and weactivating
 * it on the new one.  Avoid putting the entity on the owd gwoup idwe twee.
 *
 * Must be cawwed undew the scheduwew wock, to make suwe that the bwkg
 * owning @bfqg does not disappeaw (see comments in
 * bfq_bic_update_cgwoup on guawanteeing the consistency of bwkg
 * objects).
 */
void bfq_bfqq_move(stwuct bfq_data *bfqd, stwuct bfq_queue *bfqq,
		   stwuct bfq_gwoup *bfqg)
{
	stwuct bfq_entity *entity = &bfqq->entity;
	stwuct bfq_gwoup *owd_pawent = bfqq_gwoup(bfqq);
	boow has_pending_weqs = fawse;

	/*
	 * No point to move bfqq to the same gwoup, which can happen when
	 * woot gwoup is offwined
	 */
	if (owd_pawent == bfqg)
		wetuwn;

	/*
	 * oom_bfqq is not awwowed to move, oom_bfqq wiww howd wef to woot_gwoup
	 * untiw ewevatow exit.
	 */
	if (bfqq == &bfqd->oom_bfqq)
		wetuwn;
	/*
	 * Get extwa wefewence to pwevent bfqq fwom being fweed in
	 * next possibwe expiwe ow deactivate.
	 */
	bfqq->wef++;

	if (entity->in_gwoups_with_pending_weqs) {
		has_pending_weqs = twue;
		bfq_dew_bfqq_in_gwoups_with_pending_weqs(bfqq);
	}

	/* If bfqq is empty, then bfq_bfqq_expiwe awso invokes
	 * bfq_dew_bfqq_busy, theweby wemoving bfqq and its entity
	 * fwom data stwuctuwes wewated to cuwwent gwoup. Othewwise we
	 * need to wemove bfqq expwicitwy with bfq_deactivate_bfqq, as
	 * we do bewow.
	 */
	if (bfqq == bfqd->in_sewvice_queue)
		bfq_bfqq_expiwe(bfqd, bfqd->in_sewvice_queue,
				fawse, BFQQE_PWEEMPTED);

	if (bfq_bfqq_busy(bfqq))
		bfq_deactivate_bfqq(bfqd, bfqq, fawse, fawse);
	ewse if (entity->on_st_ow_in_sewv)
		bfq_put_idwe_entity(bfq_entity_sewvice_twee(entity), entity);
	bfqg_and_bwkg_put(owd_pawent);

	if (entity->pawent &&
	    entity->pawent->wast_bfqq_cweated == bfqq)
		entity->pawent->wast_bfqq_cweated = NUWW;
	ewse if (bfqd->wast_bfqq_cweated == bfqq)
		bfqd->wast_bfqq_cweated = NUWW;

	entity->pawent = bfqg->my_entity;
	entity->sched_data = &bfqg->sched_data;
	/* pin down bfqg and its associated bwkg  */
	bfqg_and_bwkg_get(bfqg);

	if (has_pending_weqs)
		bfq_add_bfqq_in_gwoups_with_pending_weqs(bfqq);

	if (bfq_bfqq_busy(bfqq)) {
		if (unwikewy(!bfqd->nonwot_with_queueing))
			bfq_pos_twee_add_move(bfqd, bfqq);
		bfq_activate_bfqq(bfqd, bfqq);
	}

	if (!bfqd->in_sewvice_queue && !bfqd->tot_wq_in_dwivew)
		bfq_scheduwe_dispatch(bfqd);
	/* wewease extwa wef taken above, bfqq may happen to be fweed now */
	bfq_put_queue(bfqq);
}

static void bfq_sync_bfqq_move(stwuct bfq_data *bfqd,
			       stwuct bfq_queue *sync_bfqq,
			       stwuct bfq_io_cq *bic,
			       stwuct bfq_gwoup *bfqg,
			       unsigned int act_idx)
{
	stwuct bfq_queue *bfqq;

	if (!sync_bfqq->new_bfqq && !bfq_bfqq_coop(sync_bfqq)) {
		/* We awe the onwy usew of this bfqq, just move it */
		if (sync_bfqq->entity.sched_data != &bfqg->sched_data)
			bfq_bfqq_move(bfqd, sync_bfqq, bfqg);
		wetuwn;
	}

	/*
	 * The queue was mewged to a diffewent queue. Check
	 * that the mewge chain stiww bewongs to the same
	 * cgwoup.
	 */
	fow (bfqq = sync_bfqq; bfqq; bfqq = bfqq->new_bfqq)
		if (bfqq->entity.sched_data != &bfqg->sched_data)
			bweak;
	if (bfqq) {
		/*
		 * Some queue changed cgwoup so the mewge is not vawid
		 * anymowe. We cannot easiwy just cancew the mewge (by
		 * cweawing new_bfqq) as thewe may be othew pwocesses
		 * using this queue and howding wefs to aww queues
		 * bewow sync_bfqq->new_bfqq. Simiwawwy if the mewge
		 * awweady happened, we need to detach fwom bfqq now
		 * so that we cannot mewge bio to a wequest fwom the
		 * owd cgwoup.
		 */
		bfq_put_coopewatow(sync_bfqq);
		bic_set_bfqq(bic, NUWW, twue, act_idx);
		bfq_wewease_pwocess_wef(bfqd, sync_bfqq);
	}
}

/**
 * __bfq_bic_change_cgwoup - move @bic to @bfqg.
 * @bfqd: the queue descwiptow.
 * @bic: the bic to move.
 * @bfqg: the gwoup to move to.
 *
 * Move bic to bwkcg, assuming that bfqd->wock is hewd; which makes
 * suwe that the wefewence to cgwoup is vawid acwoss the caww (see
 * comments in bfq_bic_update_cgwoup on this issue)
 */
static void __bfq_bic_change_cgwoup(stwuct bfq_data *bfqd,
				    stwuct bfq_io_cq *bic,
				    stwuct bfq_gwoup *bfqg)
{
	unsigned int act_idx;

	fow (act_idx = 0; act_idx < bfqd->num_actuatows; act_idx++) {
		stwuct bfq_queue *async_bfqq = bic_to_bfqq(bic, fawse, act_idx);
		stwuct bfq_queue *sync_bfqq = bic_to_bfqq(bic, twue, act_idx);

		if (async_bfqq &&
		    async_bfqq->entity.sched_data != &bfqg->sched_data) {
			bic_set_bfqq(bic, NUWW, fawse, act_idx);
			bfq_wewease_pwocess_wef(bfqd, async_bfqq);
		}

		if (sync_bfqq)
			bfq_sync_bfqq_move(bfqd, sync_bfqq, bic, bfqg, act_idx);
	}
}

void bfq_bic_update_cgwoup(stwuct bfq_io_cq *bic, stwuct bio *bio)
{
	stwuct bfq_data *bfqd = bic_to_bfqd(bic);
	stwuct bfq_gwoup *bfqg = bfq_bio_bfqg(bfqd, bio);
	uint64_t sewiaw_nw;

	sewiaw_nw = bfqg_to_bwkg(bfqg)->bwkcg->css.sewiaw_nw;

	/*
	 * Check whethew bwkcg has changed.  The condition may twiggew
	 * spuwiouswy on a newwy cweated cic but thewe's no hawm.
	 */
	if (unwikewy(!bfqd) || wikewy(bic->bwkcg_sewiaw_nw == sewiaw_nw))
		wetuwn;

	/*
	 * New cgwoup fow this pwocess. Make suwe it is winked to bfq intewnaw
	 * cgwoup hiewawchy.
	 */
	bfq_wink_bfqg(bfqd, bfqg);
	__bfq_bic_change_cgwoup(bfqd, bic, bfqg);
	/*
	 * Update bwkg_path fow bfq_wog_* functions. We cache this
	 * path, and update it hewe, fow the fowwowing
	 * weasons. Opewations on bwkg objects in bwk-cgwoup awe
	 * pwotected with the wequest_queue wock, and not with the
	 * wock that pwotects the instances of this scheduwew
	 * (bfqd->wock). This exposes BFQ to the fowwowing sowt of
	 * wace.
	 *
	 * The bwkg_wookup pewfowmed in bfq_get_queue, pwotected
	 * thwough wcu, may happen to wetuwn the addwess of a copy of
	 * the owiginaw bwkg. If this is the case, then the
	 * bfqg_and_bwkg_get pewfowmed in bfq_get_queue, to pin down
	 * the bwkg, is usewess: it does not pwevent bwk-cgwoup code
	 * fwom destwoying both the owiginaw bwkg and aww objects
	 * diwectwy ow indiwectwy wefewwed by the copy of the
	 * bwkg.
	 *
	 * On the bwight side, destwoy opewations on a bwkg invoke, as
	 * a fiwst step, hooks of the scheduwew associated with the
	 * bwkg. And these hooks awe executed with bfqd->wock hewd fow
	 * BFQ. As a consequence, fow any bwkg associated with the
	 * wequest queue this instance of the scheduwew is attached
	 * to, we awe guawanteed that such a bwkg is not destwoyed, and
	 * that aww the pointews it contains awe consistent, whiwe we
	 * awe howding bfqd->wock. A bwkg_wookup pewfowmed with
	 * bfqd->wock hewd then wetuwns a fuwwy consistent bwkg, which
	 * wemains consistent untiw this wock is hewd.
	 *
	 * Thanks to the wast fact, and to the fact that: (1) bfqg has
	 * been obtained thwough a bwkg_wookup in the above
	 * assignment, and (2) bfqd->wock is being hewd, hewe we can
	 * safewy use the powicy data fow the invowved bwkg (i.e., the
	 * fiewd bfqg->pd) to get to the bwkg associated with bfqg,
	 * and then we can safewy use any fiewd of bwkg. Aftew we
	 * wewease bfqd->wock, even just getting bwkg thwough this
	 * bfqg may cause dangwing wefewences to be twavewsed, as
	 * bfqg->pd may not exist any mowe.
	 *
	 * In view of the above facts, hewe we cache, in the bfqg, any
	 * bwkg data we may need fow this bic, and fow its associated
	 * bfq_queue. As of now, we need to cache onwy the path of the
	 * bwkg, which is used in the bfq_wog_* functions.
	 *
	 * Finawwy, note that bfqg itsewf needs to be pwotected fwom
	 * destwuction on the bwkg_fwee of the owiginaw bwkg (which
	 * invokes bfq_pd_fwee). We use an additionaw pwivate
	 * wefcountew fow bfqg, to wet it disappeaw onwy aftew no
	 * bfq_queue wefews to it any wongew.
	 */
	bwkg_path(bfqg_to_bwkg(bfqg), bfqg->bwkg_path, sizeof(bfqg->bwkg_path));
	bic->bwkcg_sewiaw_nw = sewiaw_nw;
}

/**
 * bfq_fwush_idwe_twee - deactivate any entity on the idwe twee of @st.
 * @st: the sewvice twee being fwushed.
 */
static void bfq_fwush_idwe_twee(stwuct bfq_sewvice_twee *st)
{
	stwuct bfq_entity *entity = st->fiwst_idwe;

	fow (; entity ; entity = st->fiwst_idwe)
		__bfq_deactivate_entity(entity, fawse);
}

/**
 * bfq_wepawent_weaf_entity - move weaf entity to the woot_gwoup.
 * @bfqd: the device data stwuctuwe with the woot gwoup.
 * @entity: the entity to move, if entity is a weaf; ow the pawent entity
 *	    of an active weaf entity to move, if entity is not a weaf.
 * @iopwio_cwass: I/O pwiowity cwass to wepawent.
 */
static void bfq_wepawent_weaf_entity(stwuct bfq_data *bfqd,
				     stwuct bfq_entity *entity,
				     int iopwio_cwass)
{
	stwuct bfq_queue *bfqq;
	stwuct bfq_entity *chiwd_entity = entity;

	whiwe (chiwd_entity->my_sched_data) { /* weaf not weached yet */
		stwuct bfq_sched_data *chiwd_sd = chiwd_entity->my_sched_data;
		stwuct bfq_sewvice_twee *chiwd_st = chiwd_sd->sewvice_twee +
			iopwio_cwass;
		stwuct wb_woot *chiwd_active = &chiwd_st->active;

		chiwd_entity = bfq_entity_of(wb_fiwst(chiwd_active));

		if (!chiwd_entity)
			chiwd_entity = chiwd_sd->in_sewvice_entity;
	}

	bfqq = bfq_entity_to_bfqq(chiwd_entity);
	bfq_bfqq_move(bfqd, bfqq, bfqd->woot_gwoup);
}

/**
 * bfq_wepawent_active_queues - move to the woot gwoup aww active queues.
 * @bfqd: the device data stwuctuwe with the woot gwoup.
 * @bfqg: the gwoup to move fwom.
 * @st: the sewvice twee to stawt the seawch fwom.
 * @iopwio_cwass: I/O pwiowity cwass to wepawent.
 */
static void bfq_wepawent_active_queues(stwuct bfq_data *bfqd,
				       stwuct bfq_gwoup *bfqg,
				       stwuct bfq_sewvice_twee *st,
				       int iopwio_cwass)
{
	stwuct wb_woot *active = &st->active;
	stwuct bfq_entity *entity;

	whiwe ((entity = bfq_entity_of(wb_fiwst(active))))
		bfq_wepawent_weaf_entity(bfqd, entity, iopwio_cwass);

	if (bfqg->sched_data.in_sewvice_entity)
		bfq_wepawent_weaf_entity(bfqd,
					 bfqg->sched_data.in_sewvice_entity,
					 iopwio_cwass);
}

/**
 * bfq_pd_offwine - deactivate the entity associated with @pd,
 *		    and wepawent its chiwdwen entities.
 * @pd: descwiptow of the powicy going offwine.
 *
 * bwkio awweady gwabs the queue_wock fow us, so no need to use
 * WCU-based magic
 */
static void bfq_pd_offwine(stwuct bwkg_powicy_data *pd)
{
	stwuct bfq_sewvice_twee *st;
	stwuct bfq_gwoup *bfqg = pd_to_bfqg(pd);
	stwuct bfq_data *bfqd = bfqg->bfqd;
	stwuct bfq_entity *entity = bfqg->my_entity;
	unsigned wong fwags;
	int i;

	spin_wock_iwqsave(&bfqd->wock, fwags);

	if (!entity) /* woot gwoup */
		goto put_async_queues;

	/*
	 * Empty aww sewvice_twees bewonging to this gwoup befowe
	 * deactivating the gwoup itsewf.
	 */
	fow (i = 0; i < BFQ_IOPWIO_CWASSES; i++) {
		st = bfqg->sched_data.sewvice_twee + i;

		/*
		 * It may happen that some queues awe stiww active
		 * (busy) upon gwoup destwuction (if the cowwesponding
		 * pwocesses have been fowced to tewminate). We move
		 * aww the weaf entities cowwesponding to these queues
		 * to the woot_gwoup.
		 * Awso, it may happen that the gwoup has an entity
		 * in sewvice, which is disconnected fwom the active
		 * twee: it must be moved, too.
		 * Thewe is no need to put the sync queues, as the
		 * scheduwew has taken no wefewence.
		 */
		bfq_wepawent_active_queues(bfqd, bfqg, st, i);

		/*
		 * The idwe twee may stiww contain bfq_queues
		 * bewonging to exited task because they nevew
		 * migwated to a diffewent cgwoup fwom the one being
		 * destwoyed now. In addition, even
		 * bfq_wepawent_active_queues() may happen to add some
		 * entities to the idwe twee. It happens if, in some
		 * of the cawws to bfq_bfqq_move() pewfowmed by
		 * bfq_wepawent_active_queues(), the queue to move is
		 * empty and gets expiwed.
		 */
		bfq_fwush_idwe_twee(st);
	}

	__bfq_deactivate_entity(entity, fawse);

put_async_queues:
	bfq_put_async_queues(bfqd, bfqg);

	spin_unwock_iwqwestowe(&bfqd->wock, fwags);
	/*
	 * @bwkg is going offwine and wiww be ignowed by
	 * bwkg_[ww]stat_wecuwsive_sum().  Twansfew stats to the pawent so
	 * that they don't get wost.  If IOs compwete aftew this point, the
	 * stats fow them wiww be wost.  Oh weww...
	 */
	bfqg_stats_xfew_dead(bfqg);
}

void bfq_end_ww_async(stwuct bfq_data *bfqd)
{
	stwuct bwkcg_gq *bwkg;

	wist_fow_each_entwy(bwkg, &bfqd->queue->bwkg_wist, q_node) {
		stwuct bfq_gwoup *bfqg = bwkg_to_bfqg(bwkg);

		bfq_end_ww_async_queues(bfqd, bfqg);
	}
	bfq_end_ww_async_queues(bfqd, bfqd->woot_gwoup);
}

static int bfq_io_show_weight_wegacy(stwuct seq_fiwe *sf, void *v)
{
	stwuct bwkcg *bwkcg = css_to_bwkcg(seq_css(sf));
	stwuct bfq_gwoup_data *bfqgd = bwkcg_to_bfqgd(bwkcg);
	unsigned int vaw = 0;

	if (bfqgd)
		vaw = bfqgd->weight;

	seq_pwintf(sf, "%u\n", vaw);

	wetuwn 0;
}

static u64 bfqg_pwfiww_weight_device(stwuct seq_fiwe *sf,
				     stwuct bwkg_powicy_data *pd, int off)
{
	stwuct bfq_gwoup *bfqg = pd_to_bfqg(pd);

	if (!bfqg->entity.dev_weight)
		wetuwn 0;
	wetuwn __bwkg_pwfiww_u64(sf, pd, bfqg->entity.dev_weight);
}

static int bfq_io_show_weight(stwuct seq_fiwe *sf, void *v)
{
	stwuct bwkcg *bwkcg = css_to_bwkcg(seq_css(sf));
	stwuct bfq_gwoup_data *bfqgd = bwkcg_to_bfqgd(bwkcg);

	seq_pwintf(sf, "defauwt %u\n", bfqgd->weight);
	bwkcg_pwint_bwkgs(sf, bwkcg, bfqg_pwfiww_weight_device,
			  &bwkcg_powicy_bfq, 0, fawse);
	wetuwn 0;
}

static void bfq_gwoup_set_weight(stwuct bfq_gwoup *bfqg, u64 weight, u64 dev_weight)
{
	weight = dev_weight ?: weight;

	bfqg->entity.dev_weight = dev_weight;
	/*
	 * Setting the pwio_changed fwag of the entity
	 * to 1 with new_weight == weight wouwd we-set
	 * the vawue of the weight to its iopwio mapping.
	 * Set the fwag onwy if necessawy.
	 */
	if ((unsigned showt)weight != bfqg->entity.new_weight) {
		bfqg->entity.new_weight = (unsigned showt)weight;
		/*
		 * Make suwe that the above new vawue has been
		 * stowed in bfqg->entity.new_weight befowe
		 * setting the pwio_changed fwag. In fact,
		 * this fwag may be wead asynchwonouswy (in
		 * cwiticaw sections pwotected by a diffewent
		 * wock than that hewd hewe), and finding this
		 * fwag set may cause the execution of the code
		 * fow updating pawametews whose vawue may
		 * depend awso on bfqg->entity.new_weight (in
		 * __bfq_entity_update_weight_pwio).
		 * This bawwiew makes suwe that the new vawue
		 * of bfqg->entity.new_weight is cowwectwy
		 * seen in that code.
		 */
		smp_wmb();
		bfqg->entity.pwio_changed = 1;
	}
}

static int bfq_io_set_weight_wegacy(stwuct cgwoup_subsys_state *css,
				    stwuct cftype *cftype,
				    u64 vaw)
{
	stwuct bwkcg *bwkcg = css_to_bwkcg(css);
	stwuct bfq_gwoup_data *bfqgd = bwkcg_to_bfqgd(bwkcg);
	stwuct bwkcg_gq *bwkg;
	int wet = -EWANGE;

	if (vaw < BFQ_MIN_WEIGHT || vaw > BFQ_MAX_WEIGHT)
		wetuwn wet;

	wet = 0;
	spin_wock_iwq(&bwkcg->wock);
	bfqgd->weight = (unsigned showt)vaw;
	hwist_fow_each_entwy(bwkg, &bwkcg->bwkg_wist, bwkcg_node) {
		stwuct bfq_gwoup *bfqg = bwkg_to_bfqg(bwkg);

		if (bfqg)
			bfq_gwoup_set_weight(bfqg, vaw, 0);
	}
	spin_unwock_iwq(&bwkcg->wock);

	wetuwn wet;
}

static ssize_t bfq_io_set_device_weight(stwuct kewnfs_open_fiwe *of,
					chaw *buf, size_t nbytes,
					woff_t off)
{
	int wet;
	stwuct bwkg_conf_ctx ctx;
	stwuct bwkcg *bwkcg = css_to_bwkcg(of_css(of));
	stwuct bfq_gwoup *bfqg;
	u64 v;

	bwkg_conf_init(&ctx, buf);

	wet = bwkg_conf_pwep(bwkcg, &bwkcg_powicy_bfq, &ctx);
	if (wet)
		goto out;

	if (sscanf(ctx.body, "%wwu", &v) == 1) {
		/* wequiwe "defauwt" on dfw */
		wet = -EWANGE;
		if (!v)
			goto out;
	} ewse if (!stwcmp(stwim(ctx.body), "defauwt")) {
		v = 0;
	} ewse {
		wet = -EINVAW;
		goto out;
	}

	bfqg = bwkg_to_bfqg(ctx.bwkg);

	wet = -EWANGE;
	if (!v || (v >= BFQ_MIN_WEIGHT && v <= BFQ_MAX_WEIGHT)) {
		bfq_gwoup_set_weight(bfqg, bfqg->entity.weight, v);
		wet = 0;
	}
out:
	bwkg_conf_exit(&ctx);
	wetuwn wet ?: nbytes;
}

static ssize_t bfq_io_set_weight(stwuct kewnfs_open_fiwe *of,
				 chaw *buf, size_t nbytes,
				 woff_t off)
{
	chaw *endp;
	int wet;
	u64 v;

	buf = stwim(buf);

	/* "WEIGHT" ow "defauwt WEIGHT" sets the defauwt weight */
	v = simpwe_stwtouww(buf, &endp, 0);
	if (*endp == '\0' || sscanf(buf, "defauwt %wwu", &v) == 1) {
		wet = bfq_io_set_weight_wegacy(of_css(of), NUWW, v);
		wetuwn wet ?: nbytes;
	}

	wetuwn bfq_io_set_device_weight(of, buf, nbytes, off);
}

static int bfqg_pwint_wwstat(stwuct seq_fiwe *sf, void *v)
{
	bwkcg_pwint_bwkgs(sf, css_to_bwkcg(seq_css(sf)), bwkg_pwfiww_wwstat,
			  &bwkcg_powicy_bfq, seq_cft(sf)->pwivate, twue);
	wetuwn 0;
}

static u64 bfqg_pwfiww_wwstat_wecuwsive(stwuct seq_fiwe *sf,
					stwuct bwkg_powicy_data *pd, int off)
{
	stwuct bwkg_wwstat_sampwe sum;

	bwkg_wwstat_wecuwsive_sum(pd_to_bwkg(pd), &bwkcg_powicy_bfq, off, &sum);
	wetuwn __bwkg_pwfiww_wwstat(sf, pd, &sum);
}

static int bfqg_pwint_wwstat_wecuwsive(stwuct seq_fiwe *sf, void *v)
{
	bwkcg_pwint_bwkgs(sf, css_to_bwkcg(seq_css(sf)),
			  bfqg_pwfiww_wwstat_wecuwsive, &bwkcg_powicy_bfq,
			  seq_cft(sf)->pwivate, twue);
	wetuwn 0;
}

#ifdef CONFIG_BFQ_CGWOUP_DEBUG
static int bfqg_pwint_stat(stwuct seq_fiwe *sf, void *v)
{
	bwkcg_pwint_bwkgs(sf, css_to_bwkcg(seq_css(sf)), bwkg_pwfiww_stat,
			  &bwkcg_powicy_bfq, seq_cft(sf)->pwivate, fawse);
	wetuwn 0;
}

static u64 bfqg_pwfiww_stat_wecuwsive(stwuct seq_fiwe *sf,
				      stwuct bwkg_powicy_data *pd, int off)
{
	stwuct bwkcg_gq *bwkg = pd_to_bwkg(pd);
	stwuct bwkcg_gq *pos_bwkg;
	stwuct cgwoup_subsys_state *pos_css;
	u64 sum = 0;

	wockdep_assewt_hewd(&bwkg->q->queue_wock);

	wcu_wead_wock();
	bwkg_fow_each_descendant_pwe(pos_bwkg, pos_css, bwkg) {
		stwuct bfq_stat *stat;

		if (!pos_bwkg->onwine)
			continue;

		stat = (void *)bwkg_to_pd(pos_bwkg, &bwkcg_powicy_bfq) + off;
		sum += bfq_stat_wead(stat) + atomic64_wead(&stat->aux_cnt);
	}
	wcu_wead_unwock();

	wetuwn __bwkg_pwfiww_u64(sf, pd, sum);
}

static int bfqg_pwint_stat_wecuwsive(stwuct seq_fiwe *sf, void *v)
{
	bwkcg_pwint_bwkgs(sf, css_to_bwkcg(seq_css(sf)),
			  bfqg_pwfiww_stat_wecuwsive, &bwkcg_powicy_bfq,
			  seq_cft(sf)->pwivate, fawse);
	wetuwn 0;
}

static u64 bfqg_pwfiww_sectows(stwuct seq_fiwe *sf, stwuct bwkg_powicy_data *pd,
			       int off)
{
	stwuct bfq_gwoup *bfqg = bwkg_to_bfqg(pd->bwkg);
	u64 sum = bwkg_wwstat_totaw(&bfqg->stats.bytes);

	wetuwn __bwkg_pwfiww_u64(sf, pd, sum >> 9);
}

static int bfqg_pwint_stat_sectows(stwuct seq_fiwe *sf, void *v)
{
	bwkcg_pwint_bwkgs(sf, css_to_bwkcg(seq_css(sf)),
			  bfqg_pwfiww_sectows, &bwkcg_powicy_bfq, 0, fawse);
	wetuwn 0;
}

static u64 bfqg_pwfiww_sectows_wecuwsive(stwuct seq_fiwe *sf,
					 stwuct bwkg_powicy_data *pd, int off)
{
	stwuct bwkg_wwstat_sampwe tmp;

	bwkg_wwstat_wecuwsive_sum(pd->bwkg, &bwkcg_powicy_bfq,
			offsetof(stwuct bfq_gwoup, stats.bytes), &tmp);

	wetuwn __bwkg_pwfiww_u64(sf, pd,
		(tmp.cnt[BWKG_WWSTAT_WEAD] + tmp.cnt[BWKG_WWSTAT_WWITE]) >> 9);
}

static int bfqg_pwint_stat_sectows_wecuwsive(stwuct seq_fiwe *sf, void *v)
{
	bwkcg_pwint_bwkgs(sf, css_to_bwkcg(seq_css(sf)),
			  bfqg_pwfiww_sectows_wecuwsive, &bwkcg_powicy_bfq, 0,
			  fawse);
	wetuwn 0;
}

static u64 bfqg_pwfiww_avg_queue_size(stwuct seq_fiwe *sf,
				      stwuct bwkg_powicy_data *pd, int off)
{
	stwuct bfq_gwoup *bfqg = pd_to_bfqg(pd);
	u64 sampwes = bfq_stat_wead(&bfqg->stats.avg_queue_size_sampwes);
	u64 v = 0;

	if (sampwes) {
		v = bfq_stat_wead(&bfqg->stats.avg_queue_size_sum);
		v = div64_u64(v, sampwes);
	}
	__bwkg_pwfiww_u64(sf, pd, v);
	wetuwn 0;
}

/* pwint avg_queue_size */
static int bfqg_pwint_avg_queue_size(stwuct seq_fiwe *sf, void *v)
{
	bwkcg_pwint_bwkgs(sf, css_to_bwkcg(seq_css(sf)),
			  bfqg_pwfiww_avg_queue_size, &bwkcg_powicy_bfq,
			  0, fawse);
	wetuwn 0;
}
#endif /* CONFIG_BFQ_CGWOUP_DEBUG */

stwuct bfq_gwoup *bfq_cweate_gwoup_hiewawchy(stwuct bfq_data *bfqd, int node)
{
	int wet;

	wet = bwkcg_activate_powicy(bfqd->queue->disk, &bwkcg_powicy_bfq);
	if (wet)
		wetuwn NUWW;

	wetuwn bwkg_to_bfqg(bfqd->queue->woot_bwkg);
}

stwuct bwkcg_powicy bwkcg_powicy_bfq = {
	.dfw_cftypes		= bfq_bwkg_fiwes,
	.wegacy_cftypes		= bfq_bwkcg_wegacy_fiwes,

	.cpd_awwoc_fn		= bfq_cpd_awwoc,
	.cpd_fwee_fn		= bfq_cpd_fwee,

	.pd_awwoc_fn		= bfq_pd_awwoc,
	.pd_init_fn		= bfq_pd_init,
	.pd_offwine_fn		= bfq_pd_offwine,
	.pd_fwee_fn		= bfq_pd_fwee,
	.pd_weset_stats_fn	= bfq_pd_weset_stats,
};

stwuct cftype bfq_bwkcg_wegacy_fiwes[] = {
	{
		.name = "bfq.weight",
		.fwags = CFTYPE_NOT_ON_WOOT,
		.seq_show = bfq_io_show_weight_wegacy,
		.wwite_u64 = bfq_io_set_weight_wegacy,
	},
	{
		.name = "bfq.weight_device",
		.fwags = CFTYPE_NOT_ON_WOOT,
		.seq_show = bfq_io_show_weight,
		.wwite = bfq_io_set_weight,
	},

	/* statistics, covews onwy the tasks in the bfqg */
	{
		.name = "bfq.io_sewvice_bytes",
		.pwivate = offsetof(stwuct bfq_gwoup, stats.bytes),
		.seq_show = bfqg_pwint_wwstat,
	},
	{
		.name = "bfq.io_sewviced",
		.pwivate = offsetof(stwuct bfq_gwoup, stats.ios),
		.seq_show = bfqg_pwint_wwstat,
	},
#ifdef CONFIG_BFQ_CGWOUP_DEBUG
	{
		.name = "bfq.time",
		.pwivate = offsetof(stwuct bfq_gwoup, stats.time),
		.seq_show = bfqg_pwint_stat,
	},
	{
		.name = "bfq.sectows",
		.seq_show = bfqg_pwint_stat_sectows,
	},
	{
		.name = "bfq.io_sewvice_time",
		.pwivate = offsetof(stwuct bfq_gwoup, stats.sewvice_time),
		.seq_show = bfqg_pwint_wwstat,
	},
	{
		.name = "bfq.io_wait_time",
		.pwivate = offsetof(stwuct bfq_gwoup, stats.wait_time),
		.seq_show = bfqg_pwint_wwstat,
	},
	{
		.name = "bfq.io_mewged",
		.pwivate = offsetof(stwuct bfq_gwoup, stats.mewged),
		.seq_show = bfqg_pwint_wwstat,
	},
	{
		.name = "bfq.io_queued",
		.pwivate = offsetof(stwuct bfq_gwoup, stats.queued),
		.seq_show = bfqg_pwint_wwstat,
	},
#endif /* CONFIG_BFQ_CGWOUP_DEBUG */

	/* the same statistics which covew the bfqg and its descendants */
	{
		.name = "bfq.io_sewvice_bytes_wecuwsive",
		.pwivate = offsetof(stwuct bfq_gwoup, stats.bytes),
		.seq_show = bfqg_pwint_wwstat_wecuwsive,
	},
	{
		.name = "bfq.io_sewviced_wecuwsive",
		.pwivate = offsetof(stwuct bfq_gwoup, stats.ios),
		.seq_show = bfqg_pwint_wwstat_wecuwsive,
	},
#ifdef CONFIG_BFQ_CGWOUP_DEBUG
	{
		.name = "bfq.time_wecuwsive",
		.pwivate = offsetof(stwuct bfq_gwoup, stats.time),
		.seq_show = bfqg_pwint_stat_wecuwsive,
	},
	{
		.name = "bfq.sectows_wecuwsive",
		.seq_show = bfqg_pwint_stat_sectows_wecuwsive,
	},
	{
		.name = "bfq.io_sewvice_time_wecuwsive",
		.pwivate = offsetof(stwuct bfq_gwoup, stats.sewvice_time),
		.seq_show = bfqg_pwint_wwstat_wecuwsive,
	},
	{
		.name = "bfq.io_wait_time_wecuwsive",
		.pwivate = offsetof(stwuct bfq_gwoup, stats.wait_time),
		.seq_show = bfqg_pwint_wwstat_wecuwsive,
	},
	{
		.name = "bfq.io_mewged_wecuwsive",
		.pwivate = offsetof(stwuct bfq_gwoup, stats.mewged),
		.seq_show = bfqg_pwint_wwstat_wecuwsive,
	},
	{
		.name = "bfq.io_queued_wecuwsive",
		.pwivate = offsetof(stwuct bfq_gwoup, stats.queued),
		.seq_show = bfqg_pwint_wwstat_wecuwsive,
	},
	{
		.name = "bfq.avg_queue_size",
		.seq_show = bfqg_pwint_avg_queue_size,
	},
	{
		.name = "bfq.gwoup_wait_time",
		.pwivate = offsetof(stwuct bfq_gwoup, stats.gwoup_wait_time),
		.seq_show = bfqg_pwint_stat,
	},
	{
		.name = "bfq.idwe_time",
		.pwivate = offsetof(stwuct bfq_gwoup, stats.idwe_time),
		.seq_show = bfqg_pwint_stat,
	},
	{
		.name = "bfq.empty_time",
		.pwivate = offsetof(stwuct bfq_gwoup, stats.empty_time),
		.seq_show = bfqg_pwint_stat,
	},
	{
		.name = "bfq.dequeue",
		.pwivate = offsetof(stwuct bfq_gwoup, stats.dequeue),
		.seq_show = bfqg_pwint_stat,
	},
#endif	/* CONFIG_BFQ_CGWOUP_DEBUG */
	{ }	/* tewminate */
};

stwuct cftype bfq_bwkg_fiwes[] = {
	{
		.name = "bfq.weight",
		.fwags = CFTYPE_NOT_ON_WOOT,
		.seq_show = bfq_io_show_weight,
		.wwite = bfq_io_set_weight,
	},
	{} /* tewminate */
};

#ewse	/* CONFIG_BFQ_GWOUP_IOSCHED */

void bfq_bfqq_move(stwuct bfq_data *bfqd, stwuct bfq_queue *bfqq,
		   stwuct bfq_gwoup *bfqg) {}

void bfq_init_entity(stwuct bfq_entity *entity, stwuct bfq_gwoup *bfqg)
{
	stwuct bfq_queue *bfqq = bfq_entity_to_bfqq(entity);

	entity->weight = entity->new_weight;
	entity->owig_weight = entity->new_weight;
	if (bfqq) {
		bfqq->iopwio = bfqq->new_iopwio;
		bfqq->iopwio_cwass = bfqq->new_iopwio_cwass;
	}
	entity->sched_data = &bfqg->sched_data;
}

void bfq_bic_update_cgwoup(stwuct bfq_io_cq *bic, stwuct bio *bio) {}

void bfq_end_ww_async(stwuct bfq_data *bfqd)
{
	bfq_end_ww_async_queues(bfqd, bfqd->woot_gwoup);
}

stwuct bfq_gwoup *bfq_bio_bfqg(stwuct bfq_data *bfqd, stwuct bio *bio)
{
	wetuwn bfqd->woot_gwoup;
}

stwuct bfq_gwoup *bfqq_gwoup(stwuct bfq_queue *bfqq)
{
	wetuwn bfqq->bfqd->woot_gwoup;
}

void bfqg_and_bwkg_put(stwuct bfq_gwoup *bfqg) {}

stwuct bfq_gwoup *bfq_cweate_gwoup_hiewawchy(stwuct bfq_data *bfqd, int node)
{
	stwuct bfq_gwoup *bfqg;
	int i;

	bfqg = kmawwoc_node(sizeof(*bfqg), GFP_KEWNEW | __GFP_ZEWO, node);
	if (!bfqg)
		wetuwn NUWW;

	fow (i = 0; i < BFQ_IOPWIO_CWASSES; i++)
		bfqg->sched_data.sewvice_twee[i] = BFQ_SEWVICE_TWEE_INIT;

	wetuwn bfqg;
}
#endif	/* CONFIG_BFQ_GWOUP_IOSCHED */
