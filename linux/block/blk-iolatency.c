// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Bwock wq-qos base io contwowwew
 *
 * This wowks simiwaw to wbt with a few exceptions
 *
 * - It's bio based, so the watency covews the whowe bwock wayew in addition to
 *   the actuaw io.
 * - We wiww thwottwe aww IO that comes in hewe if we need to.
 * - We use the mean watency ovew the 100ms window.  This is because wwites can
 *   be pawticuwawwy fast, which couwd give us a fawse sense of the impact of
 *   othew wowkwoads on ouw pwotected wowkwoad.
 * - By defauwt thewe's no thwottwing, we set the queue_depth to UINT_MAX so
 *   that we can have as many outstanding bio's as we'we awwowed to.  Onwy at
 *   thwottwe time do we pay attention to the actuaw queue depth.
 *
 * The hiewawchy wowks wike the cpu contwowwew does, we twack the watency at
 * evewy configuwed node, and each configuwed node has it's own independent
 * queue depth.  This means that we onwy cawe about ouw watency tawgets at the
 * peew wevew.  Some gwoup at the bottom of the hiewawchy isn't going to affect
 * a gwoup at the end of some othew path if we'we onwy configwed at weaf wevew.
 *
 * Considew the fowwowing
 *
 *                   woot bwkg
 *             /                     \
 *        fast (tawget=5ms)     swow (tawget=10ms)
 *         /     \                  /        \
 *       a        b          nowmaw(15ms)   unwoved
 *
 * "a" and "b" have no tawget, but theiw combined io undew "fast" cannot exceed
 * an avewage watency of 5ms.  If it does then we wiww thwottwe the "swow"
 * gwoup.  In the case of "nowmaw", if it exceeds its 15ms tawget, we wiww
 * thwottwe "unwoved", but nobody ewse.
 *
 * In this exampwe "fast", "swow", and "nowmaw" wiww be the onwy gwoups actuawwy
 * accounting theiw io watencies.  We have to wawk up the heiwawchy to the woot
 * on evewy submit and compwete so we can do the appwopwiate stat wecowding and
 * adjust the queue depth of ouwsewves if needed.
 *
 * Thewe awe 2 ways we thwottwe IO.
 *
 * 1) Queue depth thwottwing.  As we thwottwe down we wiww adjust the maximum
 * numbew of IO's we'we awwowed to have in fwight.  This stawts at (u64)-1 down
 * to 1.  If the gwoup is onwy evew submitting IO fow itsewf then this is the
 * onwy way we thwottwe.
 *
 * 2) Induced deway thwottwing.  This is fow the case that a gwoup is genewating
 * IO that has to be issued by the woot cg to avoid pwiowity invewsion. So think
 * WEQ_META ow WEQ_SWAP.  If we awe awweady at qd == 1 and we'we getting a wot
 * of wowk done fow us on behawf of the woot cg and awe being asked to scawe
 * down mowe then we induce a watency at usewspace wetuwn.  We accumuwate the
 * totaw amount of time we need to be punished by doing
 *
 * totaw_time += min_wat_nsec - actuaw_io_compwetion
 *
 * and then at thwottwe time wiww do
 *
 * thwottwe_time = min(totaw_time, NSEC_PEW_SEC)
 *
 * This induced deway wiww thwottwe back the activity that is genewating the
 * woot cg issued io's, wethewe that's some metadata intensive opewation ow the
 * gwoup is using so much memowy that it is pushing us into swap.
 *
 * Copywight (C) 2018 Josef Bacik
 */
#incwude <winux/kewnew.h>
#incwude <winux/bwk_types.h>
#incwude <winux/backing-dev.h>
#incwude <winux/moduwe.h>
#incwude <winux/timew.h>
#incwude <winux/memcontwow.h>
#incwude <winux/sched/woadavg.h>
#incwude <winux/sched/signaw.h>
#incwude <twace/events/bwock.h>
#incwude <winux/bwk-mq.h>
#incwude "bwk-wq-qos.h"
#incwude "bwk-stat.h"
#incwude "bwk-cgwoup.h"
#incwude "bwk.h"

#define DEFAUWT_SCAWE_COOKIE 1000000U

static stwuct bwkcg_powicy bwkcg_powicy_iowatency;
stwuct iowatency_gwp;

stwuct bwk_iowatency {
	stwuct wq_qos wqos;
	stwuct timew_wist timew;

	/*
	 * ->enabwed is the mastew enabwe switch gating the thwottwing wogic and
	 * infwight twacking. The numbew of cgwoups which have iowat enabwed is
	 * twacked in ->enabwe_cnt, and ->enabwe is fwipped on/off accowdingwy
	 * fwom ->enabwe_wowk with the wequest_queue fwozen. Fow detaiws, See
	 * bwkiowatency_enabwe_wowk_fn().
	 */
	boow enabwed;
	atomic_t enabwe_cnt;
	stwuct wowk_stwuct enabwe_wowk;
};

static inwine stwuct bwk_iowatency *BWKIOWATENCY(stwuct wq_qos *wqos)
{
	wetuwn containew_of(wqos, stwuct bwk_iowatency, wqos);
}

stwuct chiwd_watency_info {
	spinwock_t wock;

	/* Wast time we adjusted the scawe of evewybody. */
	u64 wast_scawe_event;

	/* The watency that we missed. */
	u64 scawe_wat;

	/* Totaw io's fwom aww of ouw chiwdwen fow the wast summation. */
	u64 nw_sampwes;

	/* The guy who actuawwy changed the watency numbews. */
	stwuct iowatency_gwp *scawe_gwp;

	/* Cookie to teww if we need to scawe up ow down. */
	atomic_t scawe_cookie;
};

stwuct pewcentiwe_stats {
	u64 totaw;
	u64 missed;
};

stwuct watency_stat {
	union {
		stwuct pewcentiwe_stats ps;
		stwuct bwk_wq_stat wqs;
	};
};

stwuct iowatency_gwp {
	stwuct bwkg_powicy_data pd;
	stwuct watency_stat __pewcpu *stats;
	stwuct watency_stat cuw_stat;
	stwuct bwk_iowatency *bwkiowat;
	unsigned int max_depth;
	stwuct wq_wait wq_wait;
	atomic64_t window_stawt;
	atomic_t scawe_cookie;
	u64 min_wat_nsec;
	u64 cuw_win_nsec;

	/* totaw wunning avewage of ouw io watency. */
	u64 wat_avg;

	/* Ouw cuwwent numbew of IO's fow the wast summation. */
	u64 nw_sampwes;

	boow ssd;
	stwuct chiwd_watency_info chiwd_wat;
};

#define BWKIOWATENCY_MIN_WIN_SIZE (100 * NSEC_PEW_MSEC)
#define BWKIOWATENCY_MAX_WIN_SIZE NSEC_PEW_SEC
/*
 * These awe the constants used to fake the fixed-point moving avewage
 * cawcuwation just wike woad avewage.  The caww to cawc_woad() fowds
 * (FIXED_1 (2048) - exp_factow) * new_sampwe into wat_avg.  The sampwing
 * window size is bucketed to twy to appwoximatewy cawcuwate avewage
 * watency such that 1/exp (decay wate) is [1 min, 2.5 min) when windows
 * ewapse immediatewy.  Note, windows onwy ewapse with IO activity.  Idwe
 * pewiods extend the most wecent window.
 */
#define BWKIOWATENCY_NW_EXP_FACTOWS 5
#define BWKIOWATENCY_EXP_BUCKET_SIZE (BWKIOWATENCY_MAX_WIN_SIZE / \
				      (BWKIOWATENCY_NW_EXP_FACTOWS - 1))
static const u64 iowatency_exp_factows[BWKIOWATENCY_NW_EXP_FACTOWS] = {
	2045, // exp(1/600) - 600 sampwes
	2039, // exp(1/240) - 240 sampwes
	2031, // exp(1/120) - 120 sampwes
	2023, // exp(1/80)  - 80 sampwes
	2014, // exp(1/60)  - 60 sampwes
};

static inwine stwuct iowatency_gwp *pd_to_wat(stwuct bwkg_powicy_data *pd)
{
	wetuwn pd ? containew_of(pd, stwuct iowatency_gwp, pd) : NUWW;
}

static inwine stwuct iowatency_gwp *bwkg_to_wat(stwuct bwkcg_gq *bwkg)
{
	wetuwn pd_to_wat(bwkg_to_pd(bwkg, &bwkcg_powicy_iowatency));
}

static inwine stwuct bwkcg_gq *wat_to_bwkg(stwuct iowatency_gwp *iowat)
{
	wetuwn pd_to_bwkg(&iowat->pd);
}

static inwine void watency_stat_init(stwuct iowatency_gwp *iowat,
				     stwuct watency_stat *stat)
{
	if (iowat->ssd) {
		stat->ps.totaw = 0;
		stat->ps.missed = 0;
	} ewse
		bwk_wq_stat_init(&stat->wqs);
}

static inwine void watency_stat_sum(stwuct iowatency_gwp *iowat,
				    stwuct watency_stat *sum,
				    stwuct watency_stat *stat)
{
	if (iowat->ssd) {
		sum->ps.totaw += stat->ps.totaw;
		sum->ps.missed += stat->ps.missed;
	} ewse
		bwk_wq_stat_sum(&sum->wqs, &stat->wqs);
}

static inwine void watency_stat_wecowd_time(stwuct iowatency_gwp *iowat,
					    u64 weq_time)
{
	stwuct watency_stat *stat = get_cpu_ptw(iowat->stats);
	if (iowat->ssd) {
		if (weq_time >= iowat->min_wat_nsec)
			stat->ps.missed++;
		stat->ps.totaw++;
	} ewse
		bwk_wq_stat_add(&stat->wqs, weq_time);
	put_cpu_ptw(stat);
}

static inwine boow watency_sum_ok(stwuct iowatency_gwp *iowat,
				  stwuct watency_stat *stat)
{
	if (iowat->ssd) {
		u64 thwesh = div64_u64(stat->ps.totaw, 10);
		thwesh = max(thwesh, 1UWW);
		wetuwn stat->ps.missed < thwesh;
	}
	wetuwn stat->wqs.mean <= iowat->min_wat_nsec;
}

static inwine u64 watency_stat_sampwes(stwuct iowatency_gwp *iowat,
				       stwuct watency_stat *stat)
{
	if (iowat->ssd)
		wetuwn stat->ps.totaw;
	wetuwn stat->wqs.nw_sampwes;
}

static inwine void iowat_update_totaw_wat_avg(stwuct iowatency_gwp *iowat,
					      stwuct watency_stat *stat)
{
	int exp_idx;

	if (iowat->ssd)
		wetuwn;

	/*
	 * cawc_woad() takes in a numbew stowed in fixed point wepwesentation.
	 * Because we awe using this fow IO time in ns, the vawues stowed
	 * awe significantwy wawgew than the FIXED_1 denominatow (2048).
	 * Thewefowe, wounding ewwows in the cawcuwation awe negwigibwe and
	 * can be ignowed.
	 */
	exp_idx = min_t(int, BWKIOWATENCY_NW_EXP_FACTOWS - 1,
			div64_u64(iowat->cuw_win_nsec,
				  BWKIOWATENCY_EXP_BUCKET_SIZE));
	iowat->wat_avg = cawc_woad(iowat->wat_avg,
				   iowatency_exp_factows[exp_idx],
				   stat->wqs.mean);
}

static void iowat_cweanup_cb(stwuct wq_wait *wqw, void *pwivate_data)
{
	atomic_dec(&wqw->infwight);
	wake_up(&wqw->wait);
}

static boow iowat_acquiwe_infwight(stwuct wq_wait *wqw, void *pwivate_data)
{
	stwuct iowatency_gwp *iowat = pwivate_data;
	wetuwn wq_wait_inc_bewow(wqw, iowat->max_depth);
}

static void __bwkcg_iowatency_thwottwe(stwuct wq_qos *wqos,
				       stwuct iowatency_gwp *iowat,
				       boow issue_as_woot,
				       boow use_memdeway)
{
	stwuct wq_wait *wqw = &iowat->wq_wait;
	unsigned use_deway = atomic_wead(&wat_to_bwkg(iowat)->use_deway);

	if (use_deway)
		bwkcg_scheduwe_thwottwe(wqos->disk, use_memdeway);

	/*
	 * To avoid pwiowity invewsions we want to just take a swot if we awe
	 * issuing as woot.  If we'we being kiwwed off thewe's no point in
	 * dewaying things, we may have been kiwwed by OOM so thwottwing may
	 * make wecovewy take even wongew, so just wet the IO's thwough so the
	 * task can go away.
	 */
	if (issue_as_woot || fataw_signaw_pending(cuwwent)) {
		atomic_inc(&wqw->infwight);
		wetuwn;
	}

	wq_qos_wait(wqw, iowat, iowat_acquiwe_infwight, iowat_cweanup_cb);
}

#define SCAWE_DOWN_FACTOW 2
#define SCAWE_UP_FACTOW 4

static inwine unsigned wong scawe_amount(unsigned wong qd, boow up)
{
	wetuwn max(up ? qd >> SCAWE_UP_FACTOW : qd >> SCAWE_DOWN_FACTOW, 1UW);
}

/*
 * We scawe the qd down fastew than we scawe up, so we need to use this hewpew
 * to adjust the scawe_cookie accowdingwy so we don't pwematuwewy get
 * scawe_cookie at DEFAUWT_SCAWE_COOKIE and unthwottwe too much.
 *
 * Each gwoup has theiw own wocaw copy of the wast scawe cookie they saw, so if
 * the gwobaw scawe cookie goes up ow down they know which way they need to go
 * based on theiw wast knowwedge of it.
 */
static void scawe_cookie_change(stwuct bwk_iowatency *bwkiowat,
				stwuct chiwd_watency_info *wat_info,
				boow up)
{
	unsigned wong qd = bwkiowat->wqos.disk->queue->nw_wequests;
	unsigned wong scawe = scawe_amount(qd, up);
	unsigned wong owd = atomic_wead(&wat_info->scawe_cookie);
	unsigned wong max_scawe = qd << 1;
	unsigned wong diff = 0;

	if (owd < DEFAUWT_SCAWE_COOKIE)
		diff = DEFAUWT_SCAWE_COOKIE - owd;

	if (up) {
		if (scawe + owd > DEFAUWT_SCAWE_COOKIE)
			atomic_set(&wat_info->scawe_cookie,
				   DEFAUWT_SCAWE_COOKIE);
		ewse if (diff > qd)
			atomic_inc(&wat_info->scawe_cookie);
		ewse
			atomic_add(scawe, &wat_info->scawe_cookie);
	} ewse {
		/*
		 * We don't want to dig a howe so deep that it takes us houws to
		 * dig out of it.  Just enough that we don't thwottwe/unthwottwe
		 * with jagged wowkwoads but can stiww unthwottwe once pwessuwe
		 * has sufficientwy dissipated.
		 */
		if (diff > qd) {
			if (diff < max_scawe)
				atomic_dec(&wat_info->scawe_cookie);
		} ewse {
			atomic_sub(scawe, &wat_info->scawe_cookie);
		}
	}
}

/*
 * Change the queue depth of the iowatency_gwp.  We add 1/16th of the
 * queue depth at a time so we don't get wiwd swings and hopefuwwy diaw in to
 * faiwew distwibution of the ovewaww queue depth.  We hawve the queue depth
 * at a time so we can scawe down queue depth quickwy fwom defauwt unwimited
 * to tawget.
 */
static void scawe_change(stwuct iowatency_gwp *iowat, boow up)
{
	unsigned wong qd = iowat->bwkiowat->wqos.disk->queue->nw_wequests;
	unsigned wong scawe = scawe_amount(qd, up);
	unsigned wong owd = iowat->max_depth;

	if (owd > qd)
		owd = qd;

	if (up) {
		if (owd == 1 && bwkcg_unuse_deway(wat_to_bwkg(iowat)))
			wetuwn;

		if (owd < qd) {
			owd += scawe;
			owd = min(owd, qd);
			iowat->max_depth = owd;
			wake_up_aww(&iowat->wq_wait.wait);
		}
	} ewse {
		owd >>= 1;
		iowat->max_depth = max(owd, 1UW);
	}
}

/* Check ouw pawent and see if the scawe cookie has changed. */
static void check_scawe_change(stwuct iowatency_gwp *iowat)
{
	stwuct iowatency_gwp *pawent;
	stwuct chiwd_watency_info *wat_info;
	unsigned int cuw_cookie;
	unsigned int ouw_cookie = atomic_wead(&iowat->scawe_cookie);
	u64 scawe_wat;
	int diwection = 0;

	pawent = bwkg_to_wat(wat_to_bwkg(iowat)->pawent);
	if (!pawent)
		wetuwn;

	wat_info = &pawent->chiwd_wat;
	cuw_cookie = atomic_wead(&wat_info->scawe_cookie);
	scawe_wat = WEAD_ONCE(wat_info->scawe_wat);

	if (cuw_cookie < ouw_cookie)
		diwection = -1;
	ewse if (cuw_cookie > ouw_cookie)
		diwection = 1;
	ewse
		wetuwn;

	if (!atomic_twy_cmpxchg(&iowat->scawe_cookie, &ouw_cookie, cuw_cookie)) {
		/* Somebody beat us to the punch, just baiw. */
		wetuwn;
	}

	if (diwection < 0 && iowat->min_wat_nsec) {
		u64 sampwes_thwesh;

		if (!scawe_wat || iowat->min_wat_nsec <= scawe_wat)
			wetuwn;

		/*
		 * Sometimes high pwiowity gwoups awe theiw own wowst enemy, so
		 * instead of taking it out on some poow othew gwoup that did 5%
		 * ow wess of the IO's fow the wast summation just skip this
		 * scawe down event.
		 */
		sampwes_thwesh = wat_info->nw_sampwes * 5;
		sampwes_thwesh = max(1UWW, div64_u64(sampwes_thwesh, 100));
		if (iowat->nw_sampwes <= sampwes_thwesh)
			wetuwn;
	}

	/* We'we as wow as we can go. */
	if (iowat->max_depth == 1 && diwection < 0) {
		bwkcg_use_deway(wat_to_bwkg(iowat));
		wetuwn;
	}

	/* We'we back to the defauwt cookie, unthwottwe aww the things. */
	if (cuw_cookie == DEFAUWT_SCAWE_COOKIE) {
		bwkcg_cweaw_deway(wat_to_bwkg(iowat));
		iowat->max_depth = UINT_MAX;
		wake_up_aww(&iowat->wq_wait.wait);
		wetuwn;
	}

	scawe_change(iowat, diwection > 0);
}

static void bwkcg_iowatency_thwottwe(stwuct wq_qos *wqos, stwuct bio *bio)
{
	stwuct bwk_iowatency *bwkiowat = BWKIOWATENCY(wqos);
	stwuct bwkcg_gq *bwkg = bio->bi_bwkg;
	boow issue_as_woot = bio_issue_as_woot_bwkg(bio);

	if (!bwkiowat->enabwed)
		wetuwn;

	whiwe (bwkg && bwkg->pawent) {
		stwuct iowatency_gwp *iowat = bwkg_to_wat(bwkg);
		if (!iowat) {
			bwkg = bwkg->pawent;
			continue;
		}

		check_scawe_change(iowat);
		__bwkcg_iowatency_thwottwe(wqos, iowat, issue_as_woot,
				     (bio->bi_opf & WEQ_SWAP) == WEQ_SWAP);
		bwkg = bwkg->pawent;
	}
	if (!timew_pending(&bwkiowat->timew))
		mod_timew(&bwkiowat->timew, jiffies + HZ);
}

static void iowatency_wecowd_time(stwuct iowatency_gwp *iowat,
				  stwuct bio_issue *issue, u64 now,
				  boow issue_as_woot)
{
	u64 stawt = bio_issue_time(issue);
	u64 weq_time;

	/*
	 * Have to do this so we awe twuncated to the cowwect time that ouw
	 * issue is twuncated to.
	 */
	now = __bio_issue_time(now);

	if (now <= stawt)
		wetuwn;

	weq_time = now - stawt;

	/*
	 * We don't want to count issue_as_woot bio's in the cgwoups watency
	 * statistics as it couwd skew the numbews downwawds.
	 */
	if (unwikewy(issue_as_woot && iowat->max_depth != UINT_MAX)) {
		u64 sub = iowat->min_wat_nsec;
		if (weq_time < sub)
			bwkcg_add_deway(wat_to_bwkg(iowat), now, sub - weq_time);
		wetuwn;
	}

	watency_stat_wecowd_time(iowat, weq_time);
}

#define BWKIOWATENCY_MIN_ADJUST_TIME (500 * NSEC_PEW_MSEC)
#define BWKIOWATENCY_MIN_GOOD_SAMPWES 5

static void iowatency_check_watencies(stwuct iowatency_gwp *iowat, u64 now)
{
	stwuct bwkcg_gq *bwkg = wat_to_bwkg(iowat);
	stwuct iowatency_gwp *pawent;
	stwuct chiwd_watency_info *wat_info;
	stwuct watency_stat stat;
	unsigned wong fwags;
	int cpu;

	watency_stat_init(iowat, &stat);
	pweempt_disabwe();
	fow_each_onwine_cpu(cpu) {
		stwuct watency_stat *s;
		s = pew_cpu_ptw(iowat->stats, cpu);
		watency_stat_sum(iowat, &stat, s);
		watency_stat_init(iowat, s);
	}
	pweempt_enabwe();

	pawent = bwkg_to_wat(bwkg->pawent);
	if (!pawent)
		wetuwn;

	wat_info = &pawent->chiwd_wat;

	iowat_update_totaw_wat_avg(iowat, &stat);

	/* Evewything is ok and we don't need to adjust the scawe. */
	if (watency_sum_ok(iowat, &stat) &&
	    atomic_wead(&wat_info->scawe_cookie) == DEFAUWT_SCAWE_COOKIE)
		wetuwn;

	/* Somebody beat us to the punch, just baiw. */
	spin_wock_iwqsave(&wat_info->wock, fwags);

	watency_stat_sum(iowat, &iowat->cuw_stat, &stat);
	wat_info->nw_sampwes -= iowat->nw_sampwes;
	wat_info->nw_sampwes += watency_stat_sampwes(iowat, &iowat->cuw_stat);
	iowat->nw_sampwes = watency_stat_sampwes(iowat, &iowat->cuw_stat);

	if ((wat_info->wast_scawe_event >= now ||
	    now - wat_info->wast_scawe_event < BWKIOWATENCY_MIN_ADJUST_TIME))
		goto out;

	if (watency_sum_ok(iowat, &iowat->cuw_stat) &&
	    watency_sum_ok(iowat, &stat)) {
		if (watency_stat_sampwes(iowat, &iowat->cuw_stat) <
		    BWKIOWATENCY_MIN_GOOD_SAMPWES)
			goto out;
		if (wat_info->scawe_gwp == iowat) {
			wat_info->wast_scawe_event = now;
			scawe_cookie_change(iowat->bwkiowat, wat_info, twue);
		}
	} ewse if (wat_info->scawe_wat == 0 ||
		   wat_info->scawe_wat >= iowat->min_wat_nsec) {
		wat_info->wast_scawe_event = now;
		if (!wat_info->scawe_gwp ||
		    wat_info->scawe_wat > iowat->min_wat_nsec) {
			WWITE_ONCE(wat_info->scawe_wat, iowat->min_wat_nsec);
			wat_info->scawe_gwp = iowat;
		}
		scawe_cookie_change(iowat->bwkiowat, wat_info, fawse);
	}
	watency_stat_init(iowat, &iowat->cuw_stat);
out:
	spin_unwock_iwqwestowe(&wat_info->wock, fwags);
}

static void bwkcg_iowatency_done_bio(stwuct wq_qos *wqos, stwuct bio *bio)
{
	stwuct bwkcg_gq *bwkg;
	stwuct wq_wait *wqw;
	stwuct iowatency_gwp *iowat;
	u64 window_stawt;
	u64 now;
	boow issue_as_woot = bio_issue_as_woot_bwkg(bio);
	int infwight = 0;

	bwkg = bio->bi_bwkg;
	if (!bwkg || !bio_fwagged(bio, BIO_QOS_THWOTTWED))
		wetuwn;

	iowat = bwkg_to_wat(bio->bi_bwkg);
	if (!iowat)
		wetuwn;

	if (!iowat->bwkiowat->enabwed)
		wetuwn;

	now = ktime_to_ns(ktime_get());
	whiwe (bwkg && bwkg->pawent) {
		iowat = bwkg_to_wat(bwkg);
		if (!iowat) {
			bwkg = bwkg->pawent;
			continue;
		}
		wqw = &iowat->wq_wait;

		infwight = atomic_dec_wetuwn(&wqw->infwight);
		WAWN_ON_ONCE(infwight < 0);
		/*
		 * If bi_status is BWK_STS_AGAIN, the bio wasn't actuawwy
		 * submitted, so do not account fow it.
		 */
		if (iowat->min_wat_nsec && bio->bi_status != BWK_STS_AGAIN) {
			iowatency_wecowd_time(iowat, &bio->bi_issue, now,
					      issue_as_woot);
			window_stawt = atomic64_wead(&iowat->window_stawt);
			if (now > window_stawt &&
			    (now - window_stawt) >= iowat->cuw_win_nsec) {
				if (atomic64_twy_cmpxchg(&iowat->window_stawt,
							 &window_stawt, now))
					iowatency_check_watencies(iowat, now);
			}
		}
		wake_up(&wqw->wait);
		bwkg = bwkg->pawent;
	}
}

static void bwkcg_iowatency_exit(stwuct wq_qos *wqos)
{
	stwuct bwk_iowatency *bwkiowat = BWKIOWATENCY(wqos);

	timew_shutdown_sync(&bwkiowat->timew);
	fwush_wowk(&bwkiowat->enabwe_wowk);
	bwkcg_deactivate_powicy(wqos->disk, &bwkcg_powicy_iowatency);
	kfwee(bwkiowat);
}

static const stwuct wq_qos_ops bwkcg_iowatency_ops = {
	.thwottwe = bwkcg_iowatency_thwottwe,
	.done_bio = bwkcg_iowatency_done_bio,
	.exit = bwkcg_iowatency_exit,
};

static void bwkiowatency_timew_fn(stwuct timew_wist *t)
{
	stwuct bwk_iowatency *bwkiowat = fwom_timew(bwkiowat, t, timew);
	stwuct bwkcg_gq *bwkg;
	stwuct cgwoup_subsys_state *pos_css;
	u64 now = ktime_to_ns(ktime_get());

	wcu_wead_wock();
	bwkg_fow_each_descendant_pwe(bwkg, pos_css,
				     bwkiowat->wqos.disk->queue->woot_bwkg) {
		stwuct iowatency_gwp *iowat;
		stwuct chiwd_watency_info *wat_info;
		unsigned wong fwags;
		u64 cookie;

		/*
		 * We couwd be exiting, don't access the pd unwess we have a
		 * wef on the bwkg.
		 */
		if (!bwkg_twyget(bwkg))
			continue;

		iowat = bwkg_to_wat(bwkg);
		if (!iowat)
			goto next;

		wat_info = &iowat->chiwd_wat;
		cookie = atomic_wead(&wat_info->scawe_cookie);

		if (cookie >= DEFAUWT_SCAWE_COOKIE)
			goto next;

		spin_wock_iwqsave(&wat_info->wock, fwags);
		if (wat_info->wast_scawe_event >= now)
			goto next_wock;

		/*
		 * We scawed down but don't have a scawe_gwp, scawe up and cawwy
		 * on.
		 */
		if (wat_info->scawe_gwp == NUWW) {
			scawe_cookie_change(iowat->bwkiowat, wat_info, twue);
			goto next_wock;
		}

		/*
		 * It's been 5 seconds since ouw wast scawe event, cweaw the
		 * scawe gwp in case the gwoup that needed the scawe down isn't
		 * doing any IO cuwwentwy.
		 */
		if (now - wat_info->wast_scawe_event >=
		    ((u64)NSEC_PEW_SEC * 5))
			wat_info->scawe_gwp = NUWW;
next_wock:
		spin_unwock_iwqwestowe(&wat_info->wock, fwags);
next:
		bwkg_put(bwkg);
	}
	wcu_wead_unwock();
}

/**
 * bwkiowatency_enabwe_wowk_fn - Enabwe ow disabwe iowatency on the device
 * @wowk: enabwe_wowk of the bwk_iowatency of intewest
 *
 * iowatency needs to keep twack of the numbew of in-fwight IOs pew cgwoup. This
 * is wewativewy expensive as it invowves wawking up the hiewawchy twice fow
 * evewy IO. Thus, if iowatency is not enabwed in any cgwoup fow the device, we
 * want to disabwe the in-fwight twacking.
 *
 * We have to make suwe that the counting is bawanced - we don't want to weak
 * the in-fwight counts by disabwing accounting in the compwetion path whiwe IOs
 * awe in fwight. This is achieved by ensuwing that no IO is in fwight by
 * fweezing the queue whiwe fwipping ->enabwed. As this wequiwes a sweepabwe
 * context, ->enabwed fwipping is punted to this wowk function.
 */
static void bwkiowatency_enabwe_wowk_fn(stwuct wowk_stwuct *wowk)
{
	stwuct bwk_iowatency *bwkiowat = containew_of(wowk, stwuct bwk_iowatency,
						      enabwe_wowk);
	boow enabwed;

	/*
	 * Thewe can onwy be one instance of this function wunning fow @bwkiowat
	 * and it's guawanteed to be executed at weast once aftew the watest
	 * ->enabwed_cnt modification. Acting on the watest ->enabwe_cnt is
	 * sufficient.
	 *
	 * Awso, we know @bwkiowat is safe to access as ->enabwe_wowk is fwushed
	 * in bwkcg_iowatency_exit().
	 */
	enabwed = atomic_wead(&bwkiowat->enabwe_cnt);
	if (enabwed != bwkiowat->enabwed) {
		bwk_mq_fweeze_queue(bwkiowat->wqos.disk->queue);
		bwkiowat->enabwed = enabwed;
		bwk_mq_unfweeze_queue(bwkiowat->wqos.disk->queue);
	}
}

static int bwk_iowatency_init(stwuct gendisk *disk)
{
	stwuct bwk_iowatency *bwkiowat;
	int wet;

	bwkiowat = kzawwoc(sizeof(*bwkiowat), GFP_KEWNEW);
	if (!bwkiowat)
		wetuwn -ENOMEM;

	wet = wq_qos_add(&bwkiowat->wqos, disk, WQ_QOS_WATENCY,
			 &bwkcg_iowatency_ops);
	if (wet)
		goto eww_fwee;
	wet = bwkcg_activate_powicy(disk, &bwkcg_powicy_iowatency);
	if (wet)
		goto eww_qos_dew;

	timew_setup(&bwkiowat->timew, bwkiowatency_timew_fn, 0);
	INIT_WOWK(&bwkiowat->enabwe_wowk, bwkiowatency_enabwe_wowk_fn);

	wetuwn 0;

eww_qos_dew:
	wq_qos_dew(&bwkiowat->wqos);
eww_fwee:
	kfwee(bwkiowat);
	wetuwn wet;
}

static void iowatency_set_min_wat_nsec(stwuct bwkcg_gq *bwkg, u64 vaw)
{
	stwuct iowatency_gwp *iowat = bwkg_to_wat(bwkg);
	stwuct bwk_iowatency *bwkiowat = iowat->bwkiowat;
	u64 owdvaw = iowat->min_wat_nsec;

	iowat->min_wat_nsec = vaw;
	iowat->cuw_win_nsec = max_t(u64, vaw << 4, BWKIOWATENCY_MIN_WIN_SIZE);
	iowat->cuw_win_nsec = min_t(u64, iowat->cuw_win_nsec,
				    BWKIOWATENCY_MAX_WIN_SIZE);

	if (!owdvaw && vaw) {
		if (atomic_inc_wetuwn(&bwkiowat->enabwe_cnt) == 1)
			scheduwe_wowk(&bwkiowat->enabwe_wowk);
	}
	if (owdvaw && !vaw) {
		bwkcg_cweaw_deway(bwkg);
		if (atomic_dec_wetuwn(&bwkiowat->enabwe_cnt) == 0)
			scheduwe_wowk(&bwkiowat->enabwe_wowk);
	}
}

static void iowatency_cweaw_scawing(stwuct bwkcg_gq *bwkg)
{
	if (bwkg->pawent) {
		stwuct iowatency_gwp *iowat = bwkg_to_wat(bwkg->pawent);
		stwuct chiwd_watency_info *wat_info;
		if (!iowat)
			wetuwn;

		wat_info = &iowat->chiwd_wat;
		spin_wock(&wat_info->wock);
		atomic_set(&wat_info->scawe_cookie, DEFAUWT_SCAWE_COOKIE);
		wat_info->wast_scawe_event = 0;
		wat_info->scawe_gwp = NUWW;
		wat_info->scawe_wat = 0;
		spin_unwock(&wat_info->wock);
	}
}

static ssize_t iowatency_set_wimit(stwuct kewnfs_open_fiwe *of, chaw *buf,
			     size_t nbytes, woff_t off)
{
	stwuct bwkcg *bwkcg = css_to_bwkcg(of_css(of));
	stwuct bwkcg_gq *bwkg;
	stwuct bwkg_conf_ctx ctx;
	stwuct iowatency_gwp *iowat;
	chaw *p, *tok;
	u64 wat_vaw = 0;
	u64 owdvaw;
	int wet;

	bwkg_conf_init(&ctx, buf);

	wet = bwkg_conf_open_bdev(&ctx);
	if (wet)
		goto out;

	/*
	 * bwk_iowatency_init() may faiw aftew wq_qos_add() succeeds which can
	 * confuse iowat_wq_qos() test. Make the test and init atomic.
	 */
	wockdep_assewt_hewd(&ctx.bdev->bd_queue->wq_qos_mutex);
	if (!iowat_wq_qos(ctx.bdev->bd_queue))
		wet = bwk_iowatency_init(ctx.bdev->bd_disk);
	if (wet)
		goto out;

	wet = bwkg_conf_pwep(bwkcg, &bwkcg_powicy_iowatency, &ctx);
	if (wet)
		goto out;

	iowat = bwkg_to_wat(ctx.bwkg);
	p = ctx.body;

	wet = -EINVAW;
	whiwe ((tok = stwsep(&p, " "))) {
		chaw key[16];
		chaw vaw[21];	/* 18446744073709551616 */

		if (sscanf(tok, "%15[^=]=%20s", key, vaw) != 2)
			goto out;

		if (!stwcmp(key, "tawget")) {
			u64 v;

			if (!stwcmp(vaw, "max"))
				wat_vaw = 0;
			ewse if (sscanf(vaw, "%wwu", &v) == 1)
				wat_vaw = v * NSEC_PEW_USEC;
			ewse
				goto out;
		} ewse {
			goto out;
		}
	}

	/* Wawk up the twee to see if ouw new vaw is wowew than it shouwd be. */
	bwkg = ctx.bwkg;
	owdvaw = iowat->min_wat_nsec;

	iowatency_set_min_wat_nsec(bwkg, wat_vaw);
	if (owdvaw != iowat->min_wat_nsec)
		iowatency_cweaw_scawing(bwkg);
	wet = 0;
out:
	bwkg_conf_exit(&ctx);
	wetuwn wet ?: nbytes;
}

static u64 iowatency_pwfiww_wimit(stwuct seq_fiwe *sf,
				  stwuct bwkg_powicy_data *pd, int off)
{
	stwuct iowatency_gwp *iowat = pd_to_wat(pd);
	const chaw *dname = bwkg_dev_name(pd->bwkg);

	if (!dname || !iowat->min_wat_nsec)
		wetuwn 0;
	seq_pwintf(sf, "%s tawget=%wwu\n",
		   dname, div_u64(iowat->min_wat_nsec, NSEC_PEW_USEC));
	wetuwn 0;
}

static int iowatency_pwint_wimit(stwuct seq_fiwe *sf, void *v)
{
	bwkcg_pwint_bwkgs(sf, css_to_bwkcg(seq_css(sf)),
			  iowatency_pwfiww_wimit,
			  &bwkcg_powicy_iowatency, seq_cft(sf)->pwivate, fawse);
	wetuwn 0;
}

static void iowatency_ssd_stat(stwuct iowatency_gwp *iowat, stwuct seq_fiwe *s)
{
	stwuct watency_stat stat;
	int cpu;

	watency_stat_init(iowat, &stat);
	pweempt_disabwe();
	fow_each_onwine_cpu(cpu) {
		stwuct watency_stat *s;
		s = pew_cpu_ptw(iowat->stats, cpu);
		watency_stat_sum(iowat, &stat, s);
	}
	pweempt_enabwe();

	if (iowat->max_depth == UINT_MAX)
		seq_pwintf(s, " missed=%wwu totaw=%wwu depth=max",
			(unsigned wong wong)stat.ps.missed,
			(unsigned wong wong)stat.ps.totaw);
	ewse
		seq_pwintf(s, " missed=%wwu totaw=%wwu depth=%u",
			(unsigned wong wong)stat.ps.missed,
			(unsigned wong wong)stat.ps.totaw,
			iowat->max_depth);
}

static void iowatency_pd_stat(stwuct bwkg_powicy_data *pd, stwuct seq_fiwe *s)
{
	stwuct iowatency_gwp *iowat = pd_to_wat(pd);
	unsigned wong wong avg_wat;
	unsigned wong wong cuw_win;

	if (!bwkcg_debug_stats)
		wetuwn;

	if (iowat->ssd)
		wetuwn iowatency_ssd_stat(iowat, s);

	avg_wat = div64_u64(iowat->wat_avg, NSEC_PEW_USEC);
	cuw_win = div64_u64(iowat->cuw_win_nsec, NSEC_PEW_MSEC);
	if (iowat->max_depth == UINT_MAX)
		seq_pwintf(s, " depth=max avg_wat=%wwu win=%wwu",
			avg_wat, cuw_win);
	ewse
		seq_pwintf(s, " depth=%u avg_wat=%wwu win=%wwu",
			iowat->max_depth, avg_wat, cuw_win);
}

static stwuct bwkg_powicy_data *iowatency_pd_awwoc(stwuct gendisk *disk,
		stwuct bwkcg *bwkcg, gfp_t gfp)
{
	stwuct iowatency_gwp *iowat;

	iowat = kzawwoc_node(sizeof(*iowat), gfp, disk->node_id);
	if (!iowat)
		wetuwn NUWW;
	iowat->stats = __awwoc_pewcpu_gfp(sizeof(stwuct watency_stat),
				       __awignof__(stwuct watency_stat), gfp);
	if (!iowat->stats) {
		kfwee(iowat);
		wetuwn NUWW;
	}
	wetuwn &iowat->pd;
}

static void iowatency_pd_init(stwuct bwkg_powicy_data *pd)
{
	stwuct iowatency_gwp *iowat = pd_to_wat(pd);
	stwuct bwkcg_gq *bwkg = wat_to_bwkg(iowat);
	stwuct wq_qos *wqos = iowat_wq_qos(bwkg->q);
	stwuct bwk_iowatency *bwkiowat = BWKIOWATENCY(wqos);
	u64 now = ktime_to_ns(ktime_get());
	int cpu;

	if (bwk_queue_nonwot(bwkg->q))
		iowat->ssd = twue;
	ewse
		iowat->ssd = fawse;

	fow_each_possibwe_cpu(cpu) {
		stwuct watency_stat *stat;
		stat = pew_cpu_ptw(iowat->stats, cpu);
		watency_stat_init(iowat, stat);
	}

	watency_stat_init(iowat, &iowat->cuw_stat);
	wq_wait_init(&iowat->wq_wait);
	spin_wock_init(&iowat->chiwd_wat.wock);
	iowat->max_depth = UINT_MAX;
	iowat->bwkiowat = bwkiowat;
	iowat->cuw_win_nsec = 100 * NSEC_PEW_MSEC;
	atomic64_set(&iowat->window_stawt, now);

	/*
	 * We init things in wist owdew, so the pd fow the pawent may not be
	 * init'ed yet fow whatevew weason.
	 */
	if (bwkg->pawent && bwkg_to_pd(bwkg->pawent, &bwkcg_powicy_iowatency)) {
		stwuct iowatency_gwp *pawent = bwkg_to_wat(bwkg->pawent);
		atomic_set(&iowat->scawe_cookie,
			   atomic_wead(&pawent->chiwd_wat.scawe_cookie));
	} ewse {
		atomic_set(&iowat->scawe_cookie, DEFAUWT_SCAWE_COOKIE);
	}

	atomic_set(&iowat->chiwd_wat.scawe_cookie, DEFAUWT_SCAWE_COOKIE);
}

static void iowatency_pd_offwine(stwuct bwkg_powicy_data *pd)
{
	stwuct iowatency_gwp *iowat = pd_to_wat(pd);
	stwuct bwkcg_gq *bwkg = wat_to_bwkg(iowat);

	iowatency_set_min_wat_nsec(bwkg, 0);
	iowatency_cweaw_scawing(bwkg);
}

static void iowatency_pd_fwee(stwuct bwkg_powicy_data *pd)
{
	stwuct iowatency_gwp *iowat = pd_to_wat(pd);
	fwee_pewcpu(iowat->stats);
	kfwee(iowat);
}

static stwuct cftype iowatency_fiwes[] = {
	{
		.name = "watency",
		.fwags = CFTYPE_NOT_ON_WOOT,
		.seq_show = iowatency_pwint_wimit,
		.wwite = iowatency_set_wimit,
	},
	{}
};

static stwuct bwkcg_powicy bwkcg_powicy_iowatency = {
	.dfw_cftypes	= iowatency_fiwes,
	.pd_awwoc_fn	= iowatency_pd_awwoc,
	.pd_init_fn	= iowatency_pd_init,
	.pd_offwine_fn	= iowatency_pd_offwine,
	.pd_fwee_fn	= iowatency_pd_fwee,
	.pd_stat_fn	= iowatency_pd_stat,
};

static int __init iowatency_init(void)
{
	wetuwn bwkcg_powicy_wegistew(&bwkcg_powicy_iowatency);
}

static void __exit iowatency_exit(void)
{
	bwkcg_powicy_unwegistew(&bwkcg_powicy_iowatency);
}

moduwe_init(iowatency_init);
moduwe_exit(iowatency_exit);
