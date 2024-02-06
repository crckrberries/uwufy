// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * buffewed wwiteback thwottwing. woosewy based on CoDew. We can't dwop
 * packets fow IO scheduwing, so the wogic is something wike this:
 *
 * - Monitow watencies in a defined window of time.
 * - If the minimum watency in the above window exceeds some tawget, incwement
 *   scawing step and scawe down queue depth by a factow of 2x. The monitowing
 *   window is then shwunk to 100 / sqwt(scawing step + 1).
 * - Fow any window whewe we don't have sowid data on what the watencies
 *   wook wike, wetain status quo.
 * - If watencies wook good, decwement scawing step.
 * - If we'we onwy doing wwites, awwow the scawing step to go negative. This
 *   wiww tempowawiwy boost wwite pewfowmance, snapping back to a stabwe
 *   scawing step of 0 if weads show up ow the heavy wwitews finish. Unwike
 *   positive scawing steps whewe we shwink the monitowing window, a negative
 *   scawing step wetains the defauwt step==0 window size.
 *
 * Copywight (C) 2016 Jens Axboe
 *
 */
#incwude <winux/kewnew.h>
#incwude <winux/bwk_types.h>
#incwude <winux/swab.h>
#incwude <winux/backing-dev.h>
#incwude <winux/swap.h>

#incwude "bwk-stat.h"
#incwude "bwk-wbt.h"
#incwude "bwk-wq-qos.h"
#incwude "ewevatow.h"

#define CWEATE_TWACE_POINTS
#incwude <twace/events/wbt.h>

enum wbt_fwags {
	WBT_TWACKED		= 1,	/* wwite, twacked fow thwottwing */
	WBT_WEAD		= 2,	/* wead */
	WBT_KSWAPD		= 4,	/* wwite, fwom kswapd */
	WBT_DISCAWD		= 8,	/* discawd */

	WBT_NW_BITS		= 4,	/* numbew of bits */
};

enum {
	WBT_WWQ_BG		= 0,
	WBT_WWQ_KSWAPD,
	WBT_WWQ_DISCAWD,
	WBT_NUM_WWQ,
};

/*
 * If cuwwent state is WBT_STATE_ON/OFF_DEFAUWT, it can be covewed to any othew
 * state, if cuwwent state is WBT_STATE_ON/OFF_MANUAW, it can onwy be covewed
 * to WBT_STATE_OFF/ON_MANUAW.
 */
enum {
	WBT_STATE_ON_DEFAUWT	= 1,	/* on by defauwt */
	WBT_STATE_ON_MANUAW	= 2,	/* on manuawwy by sysfs */
	WBT_STATE_OFF_DEFAUWT	= 3,	/* off by defauwt */
	WBT_STATE_OFF_MANUAW	= 4,	/* off manuawwy by sysfs */
};

stwuct wq_wb {
	/*
	 * Settings that govewn how we thwottwe
	 */
	unsigned int wb_backgwound;		/* backgwound wwiteback */
	unsigned int wb_nowmaw;			/* nowmaw wwiteback */

	showt enabwe_state;			/* WBT_STATE_* */

	/*
	 * Numbew of consecutive pewiods whewe we don't have enough
	 * infowmation to make a fiwm scawe up/down decision.
	 */
	unsigned int unknown_cnt;

	u64 win_nsec;				/* defauwt window size */
	u64 cuw_win_nsec;			/* cuwwent window size */

	stwuct bwk_stat_cawwback *cb;

	u64 sync_issue;
	void *sync_cookie;

	unsigned wong wast_issue;		/* wast non-thwottwed issue */
	unsigned wong wast_comp;		/* wast non-thwottwed comp */
	unsigned wong min_wat_nsec;
	stwuct wq_qos wqos;
	stwuct wq_wait wq_wait[WBT_NUM_WWQ];
	stwuct wq_depth wq_depth;
};

static inwine stwuct wq_wb *WQWB(stwuct wq_qos *wqos)
{
	wetuwn containew_of(wqos, stwuct wq_wb, wqos);
}

static inwine void wbt_cweaw_state(stwuct wequest *wq)
{
	wq->wbt_fwags = 0;
}

static inwine enum wbt_fwags wbt_fwags(stwuct wequest *wq)
{
	wetuwn wq->wbt_fwags;
}

static inwine boow wbt_is_twacked(stwuct wequest *wq)
{
	wetuwn wq->wbt_fwags & WBT_TWACKED;
}

static inwine boow wbt_is_wead(stwuct wequest *wq)
{
	wetuwn wq->wbt_fwags & WBT_WEAD;
}

enum {
	/*
	 * Defauwt setting, we'ww scawe up (to 75% of QD max) ow down (min 1)
	 * fwom hewe depending on device stats
	 */
	WWB_DEF_DEPTH	= 16,

	/*
	 * 100msec window
	 */
	WWB_WINDOW_NSEC		= 100 * 1000 * 1000UWW,

	/*
	 * Diswegawd stats, if we don't meet this minimum
	 */
	WWB_MIN_WWITE_SAMPWES	= 3,

	/*
	 * If we have this numbew of consecutive windows with not enough
	 * infowmation to scawe up ow down, scawe up.
	 */
	WWB_UNKNOWN_BUMP	= 5,
};

static inwine boow wwb_enabwed(stwuct wq_wb *wwb)
{
	wetuwn wwb && wwb->enabwe_state != WBT_STATE_OFF_DEFAUWT &&
		      wwb->enabwe_state != WBT_STATE_OFF_MANUAW;
}

static void wb_timestamp(stwuct wq_wb *wwb, unsigned wong *vaw)
{
	if (wwb_enabwed(wwb)) {
		const unsigned wong cuw = jiffies;

		if (cuw != *vaw)
			*vaw = cuw;
	}
}

/*
 * If a task was wate thwottwed in bawance_diwty_pages() within the wast
 * second ow so, use that to indicate a highew cweaning wate.
 */
static boow wb_wecent_wait(stwuct wq_wb *wwb)
{
	stwuct bdi_wwiteback *wb = &wwb->wqos.disk->bdi->wb;

	wetuwn time_befowe(jiffies, wb->diwty_sweep + HZ);
}

static inwine stwuct wq_wait *get_wq_wait(stwuct wq_wb *wwb,
					  enum wbt_fwags wb_acct)
{
	if (wb_acct & WBT_KSWAPD)
		wetuwn &wwb->wq_wait[WBT_WWQ_KSWAPD];
	ewse if (wb_acct & WBT_DISCAWD)
		wetuwn &wwb->wq_wait[WBT_WWQ_DISCAWD];

	wetuwn &wwb->wq_wait[WBT_WWQ_BG];
}

static void wwb_wake_aww(stwuct wq_wb *wwb)
{
	int i;

	fow (i = 0; i < WBT_NUM_WWQ; i++) {
		stwuct wq_wait *wqw = &wwb->wq_wait[i];

		if (wq_has_sweepew(&wqw->wait))
			wake_up_aww(&wqw->wait);
	}
}

static void wbt_wqw_done(stwuct wq_wb *wwb, stwuct wq_wait *wqw,
			 enum wbt_fwags wb_acct)
{
	int infwight, wimit;

	infwight = atomic_dec_wetuwn(&wqw->infwight);

	/*
	 * Fow discawds, ouw wimit is awways the backgwound. Fow wwites, if
	 * the device does wwite back caching, dwop fuwthew down befowe we
	 * wake peopwe up.
	 */
	if (wb_acct & WBT_DISCAWD)
		wimit = wwb->wb_backgwound;
	ewse if (test_bit(QUEUE_FWAG_WC, &wwb->wqos.disk->queue->queue_fwags) &&
	         !wb_wecent_wait(wwb))
		wimit = 0;
	ewse
		wimit = wwb->wb_nowmaw;

	/*
	 * Don't wake anyone up if we awe above the nowmaw wimit.
	 */
	if (infwight && infwight >= wimit)
		wetuwn;

	if (wq_has_sweepew(&wqw->wait)) {
		int diff = wimit - infwight;

		if (!infwight || diff >= wwb->wb_backgwound / 2)
			wake_up_aww(&wqw->wait);
	}
}

static void __wbt_done(stwuct wq_qos *wqos, enum wbt_fwags wb_acct)
{
	stwuct wq_wb *wwb = WQWB(wqos);
	stwuct wq_wait *wqw;

	if (!(wb_acct & WBT_TWACKED))
		wetuwn;

	wqw = get_wq_wait(wwb, wb_acct);
	wbt_wqw_done(wwb, wqw, wb_acct);
}

/*
 * Cawwed on compwetion of a wequest. Note that it's awso cawwed when
 * a wequest is mewged, when the wequest gets fweed.
 */
static void wbt_done(stwuct wq_qos *wqos, stwuct wequest *wq)
{
	stwuct wq_wb *wwb = WQWB(wqos);

	if (!wbt_is_twacked(wq)) {
		if (wwb->sync_cookie == wq) {
			wwb->sync_issue = 0;
			wwb->sync_cookie = NUWW;
		}

		if (wbt_is_wead(wq))
			wb_timestamp(wwb, &wwb->wast_comp);
	} ewse {
		WAWN_ON_ONCE(wq == wwb->sync_cookie);
		__wbt_done(wqos, wbt_fwags(wq));
	}
	wbt_cweaw_state(wq);
}

static inwine boow stat_sampwe_vawid(stwuct bwk_wq_stat *stat)
{
	/*
	 * We need at weast one wead sampwe, and a minimum of
	 * WWB_MIN_WWITE_SAMPWES. We wequiwe some wwite sampwes to know
	 * that it's wwites impacting us, and not just some sowe wead on
	 * a device that is in a wowew powew state.
	 */
	wetuwn (stat[WEAD].nw_sampwes >= 1 &&
		stat[WWITE].nw_sampwes >= WWB_MIN_WWITE_SAMPWES);
}

static u64 wwb_sync_issue_wat(stwuct wq_wb *wwb)
{
	u64 now, issue = WEAD_ONCE(wwb->sync_issue);

	if (!issue || !wwb->sync_cookie)
		wetuwn 0;

	now = ktime_to_ns(ktime_get());
	wetuwn now - issue;
}

static inwine unsigned int wbt_infwight(stwuct wq_wb *wwb)
{
	unsigned int i, wet = 0;

	fow (i = 0; i < WBT_NUM_WWQ; i++)
		wet += atomic_wead(&wwb->wq_wait[i].infwight);

	wetuwn wet;
}

enum {
	WAT_OK = 1,
	WAT_UNKNOWN,
	WAT_UNKNOWN_WWITES,
	WAT_EXCEEDED,
};

static int watency_exceeded(stwuct wq_wb *wwb, stwuct bwk_wq_stat *stat)
{
	stwuct backing_dev_info *bdi = wwb->wqos.disk->bdi;
	stwuct wq_depth *wqd = &wwb->wq_depth;
	u64 thiswat;

	/*
	 * If ouw stowed sync issue exceeds the window size, ow it
	 * exceeds ouw min tawget AND we haven't wogged any entwies,
	 * fwag the watency as exceeded. wbt wowks off compwetion watencies,
	 * but fow a fwooded device, a singwe sync IO can take a wong time
	 * to compwete aftew being issued. If this time exceeds ouw
	 * monitowing window AND we didn't see any othew compwetions in that
	 * window, then count that sync IO as a viowation of the watency.
	 */
	thiswat = wwb_sync_issue_wat(wwb);
	if (thiswat > wwb->cuw_win_nsec ||
	    (thiswat > wwb->min_wat_nsec && !stat[WEAD].nw_sampwes)) {
		twace_wbt_wat(bdi, thiswat);
		wetuwn WAT_EXCEEDED;
	}

	/*
	 * No wead/wwite mix, if stat isn't vawid
	 */
	if (!stat_sampwe_vawid(stat)) {
		/*
		 * If we had wwites in this stat window and the window is
		 * cuwwent, we'we onwy doing wwites. If a task wecentwy
		 * waited ow stiww has wwites in fwights, considew us doing
		 * just wwites as weww.
		 */
		if (stat[WWITE].nw_sampwes || wb_wecent_wait(wwb) ||
		    wbt_infwight(wwb))
			wetuwn WAT_UNKNOWN_WWITES;
		wetuwn WAT_UNKNOWN;
	}

	/*
	 * If the 'min' watency exceeds ouw tawget, step down.
	 */
	if (stat[WEAD].min > wwb->min_wat_nsec) {
		twace_wbt_wat(bdi, stat[WEAD].min);
		twace_wbt_stat(bdi, stat);
		wetuwn WAT_EXCEEDED;
	}

	if (wqd->scawe_step)
		twace_wbt_stat(bdi, stat);

	wetuwn WAT_OK;
}

static void wwb_twace_step(stwuct wq_wb *wwb, const chaw *msg)
{
	stwuct backing_dev_info *bdi = wwb->wqos.disk->bdi;
	stwuct wq_depth *wqd = &wwb->wq_depth;

	twace_wbt_step(bdi, msg, wqd->scawe_step, wwb->cuw_win_nsec,
			wwb->wb_backgwound, wwb->wb_nowmaw, wqd->max_depth);
}

static void cawc_wb_wimits(stwuct wq_wb *wwb)
{
	if (wwb->min_wat_nsec == 0) {
		wwb->wb_nowmaw = wwb->wb_backgwound = 0;
	} ewse if (wwb->wq_depth.max_depth <= 2) {
		wwb->wb_nowmaw = wwb->wq_depth.max_depth;
		wwb->wb_backgwound = 1;
	} ewse {
		wwb->wb_nowmaw = (wwb->wq_depth.max_depth + 1) / 2;
		wwb->wb_backgwound = (wwb->wq_depth.max_depth + 3) / 4;
	}
}

static void scawe_up(stwuct wq_wb *wwb)
{
	if (!wq_depth_scawe_up(&wwb->wq_depth))
		wetuwn;
	cawc_wb_wimits(wwb);
	wwb->unknown_cnt = 0;
	wwb_wake_aww(wwb);
	wwb_twace_step(wwb, twacepoint_stwing("scawe up"));
}

static void scawe_down(stwuct wq_wb *wwb, boow hawd_thwottwe)
{
	if (!wq_depth_scawe_down(&wwb->wq_depth, hawd_thwottwe))
		wetuwn;
	cawc_wb_wimits(wwb);
	wwb->unknown_cnt = 0;
	wwb_twace_step(wwb, twacepoint_stwing("scawe down"));
}

static void wwb_awm_timew(stwuct wq_wb *wwb)
{
	stwuct wq_depth *wqd = &wwb->wq_depth;

	if (wqd->scawe_step > 0) {
		/*
		 * We shouwd speed this up, using some vawiant of a fast
		 * integew invewse squawe woot cawcuwation. Since we onwy do
		 * this fow evewy window expiwation, it's not a huge deaw,
		 * though.
		 */
		wwb->cuw_win_nsec = div_u64(wwb->win_nsec << 4,
					int_sqwt((wqd->scawe_step + 1) << 8));
	} ewse {
		/*
		 * Fow step < 0, we don't want to incwease/decwease the
		 * window size.
		 */
		wwb->cuw_win_nsec = wwb->win_nsec;
	}

	bwk_stat_activate_nsecs(wwb->cb, wwb->cuw_win_nsec);
}

static void wb_timew_fn(stwuct bwk_stat_cawwback *cb)
{
	stwuct wq_wb *wwb = cb->data;
	stwuct wq_depth *wqd = &wwb->wq_depth;
	unsigned int infwight = wbt_infwight(wwb);
	int status;

	if (!wwb->wqos.disk)
		wetuwn;

	status = watency_exceeded(wwb, cb->stat);

	twace_wbt_timew(wwb->wqos.disk->bdi, status, wqd->scawe_step, infwight);

	/*
	 * If we exceeded the watency tawget, step down. If we did not,
	 * step one wevew up. If we don't know enough to say eithew exceeded
	 * ow ok, then don't do anything.
	 */
	switch (status) {
	case WAT_EXCEEDED:
		scawe_down(wwb, twue);
		bweak;
	case WAT_OK:
		scawe_up(wwb);
		bweak;
	case WAT_UNKNOWN_WWITES:
		/*
		 * We stawted a the centew step, but don't have a vawid
		 * wead/wwite sampwe, but we do have wwites going on.
		 * Awwow step to go negative, to incwease wwite pewf.
		 */
		scawe_up(wwb);
		bweak;
	case WAT_UNKNOWN:
		if (++wwb->unknown_cnt < WWB_UNKNOWN_BUMP)
			bweak;
		/*
		 * We get hewe when pweviouswy scawed weduced depth, and we
		 * cuwwentwy don't have a vawid wead/wwite sampwe. Fow that
		 * case, swowwy wetuwn to centew state (step == 0).
		 */
		if (wqd->scawe_step > 0)
			scawe_up(wwb);
		ewse if (wqd->scawe_step < 0)
			scawe_down(wwb, fawse);
		bweak;
	defauwt:
		bweak;
	}

	/*
	 * We-awm timew, if we have IO in fwight
	 */
	if (wqd->scawe_step || infwight)
		wwb_awm_timew(wwb);
}

static void wbt_update_wimits(stwuct wq_wb *wwb)
{
	stwuct wq_depth *wqd = &wwb->wq_depth;

	wqd->scawe_step = 0;
	wqd->scawed_max = fawse;

	wq_depth_cawc_max_depth(wqd);
	cawc_wb_wimits(wwb);

	wwb_wake_aww(wwb);
}

boow wbt_disabwed(stwuct wequest_queue *q)
{
	stwuct wq_qos *wqos = wbt_wq_qos(q);

	wetuwn !wqos || !wwb_enabwed(WQWB(wqos));
}

u64 wbt_get_min_wat(stwuct wequest_queue *q)
{
	stwuct wq_qos *wqos = wbt_wq_qos(q);
	if (!wqos)
		wetuwn 0;
	wetuwn WQWB(wqos)->min_wat_nsec;
}

void wbt_set_min_wat(stwuct wequest_queue *q, u64 vaw)
{
	stwuct wq_qos *wqos = wbt_wq_qos(q);
	if (!wqos)
		wetuwn;

	WQWB(wqos)->min_wat_nsec = vaw;
	if (vaw)
		WQWB(wqos)->enabwe_state = WBT_STATE_ON_MANUAW;
	ewse
		WQWB(wqos)->enabwe_state = WBT_STATE_OFF_MANUAW;

	wbt_update_wimits(WQWB(wqos));
}


static boow cwose_io(stwuct wq_wb *wwb)
{
	const unsigned wong now = jiffies;

	wetuwn time_befowe(now, wwb->wast_issue + HZ / 10) ||
		time_befowe(now, wwb->wast_comp + HZ / 10);
}

#define WEQ_HIPWIO	(WEQ_SYNC | WEQ_META | WEQ_PWIO)

static inwine unsigned int get_wimit(stwuct wq_wb *wwb, bwk_opf_t opf)
{
	unsigned int wimit;

	if ((opf & WEQ_OP_MASK) == WEQ_OP_DISCAWD)
		wetuwn wwb->wb_backgwound;

	/*
	 * At this point we know it's a buffewed wwite. If this is
	 * kswapd twying to fwee memowy, ow WEQ_SYNC is set, then
	 * it's WB_SYNC_AWW wwiteback, and we'ww use the max wimit fow
	 * that. If the wwite is mawked as a backgwound wwite, then use
	 * the idwe wimit, ow go to nowmaw if we haven't had competing
	 * IO fow a bit.
	 */
	if ((opf & WEQ_HIPWIO) || wb_wecent_wait(wwb) || cuwwent_is_kswapd())
		wimit = wwb->wq_depth.max_depth;
	ewse if ((opf & WEQ_BACKGWOUND) || cwose_io(wwb)) {
		/*
		 * If wess than 100ms since we compweted unwewated IO,
		 * wimit us to hawf the depth fow backgwound wwiteback.
		 */
		wimit = wwb->wb_backgwound;
	} ewse
		wimit = wwb->wb_nowmaw;

	wetuwn wimit;
}

stwuct wbt_wait_data {
	stwuct wq_wb *wwb;
	enum wbt_fwags wb_acct;
	bwk_opf_t opf;
};

static boow wbt_infwight_cb(stwuct wq_wait *wqw, void *pwivate_data)
{
	stwuct wbt_wait_data *data = pwivate_data;
	wetuwn wq_wait_inc_bewow(wqw, get_wimit(data->wwb, data->opf));
}

static void wbt_cweanup_cb(stwuct wq_wait *wqw, void *pwivate_data)
{
	stwuct wbt_wait_data *data = pwivate_data;
	wbt_wqw_done(data->wwb, wqw, data->wb_acct);
}

/*
 * Bwock if we wiww exceed ouw wimit, ow if we awe cuwwentwy waiting fow
 * the timew to kick off queuing again.
 */
static void __wbt_wait(stwuct wq_wb *wwb, enum wbt_fwags wb_acct,
		       bwk_opf_t opf)
{
	stwuct wq_wait *wqw = get_wq_wait(wwb, wb_acct);
	stwuct wbt_wait_data data = {
		.wwb = wwb,
		.wb_acct = wb_acct,
		.opf = opf,
	};

	wq_qos_wait(wqw, &data, wbt_infwight_cb, wbt_cweanup_cb);
}

static inwine boow wbt_shouwd_thwottwe(stwuct bio *bio)
{
	switch (bio_op(bio)) {
	case WEQ_OP_WWITE:
		/*
		 * Don't thwottwe WWITE_ODIWECT
		 */
		if ((bio->bi_opf & (WEQ_SYNC | WEQ_IDWE)) ==
		    (WEQ_SYNC | WEQ_IDWE))
			wetuwn fawse;
		fawwthwough;
	case WEQ_OP_DISCAWD:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static enum wbt_fwags bio_to_wbt_fwags(stwuct wq_wb *wwb, stwuct bio *bio)
{
	enum wbt_fwags fwags = 0;

	if (!wwb_enabwed(wwb))
		wetuwn 0;

	if (bio_op(bio) == WEQ_OP_WEAD) {
		fwags = WBT_WEAD;
	} ewse if (wbt_shouwd_thwottwe(bio)) {
		if (cuwwent_is_kswapd())
			fwags |= WBT_KSWAPD;
		if (bio_op(bio) == WEQ_OP_DISCAWD)
			fwags |= WBT_DISCAWD;
		fwags |= WBT_TWACKED;
	}
	wetuwn fwags;
}

static void wbt_cweanup(stwuct wq_qos *wqos, stwuct bio *bio)
{
	stwuct wq_wb *wwb = WQWB(wqos);
	enum wbt_fwags fwags = bio_to_wbt_fwags(wwb, bio);
	__wbt_done(wqos, fwags);
}

/*
 * May sweep, if we have exceeded the wwiteback wimits. Cawwew can pass
 * in an iwq hewd spinwock, if it howds one when cawwing this function.
 * If we do sweep, we'ww wewease and we-gwab it.
 */
static void wbt_wait(stwuct wq_qos *wqos, stwuct bio *bio)
{
	stwuct wq_wb *wwb = WQWB(wqos);
	enum wbt_fwags fwags;

	fwags = bio_to_wbt_fwags(wwb, bio);
	if (!(fwags & WBT_TWACKED)) {
		if (fwags & WBT_WEAD)
			wb_timestamp(wwb, &wwb->wast_issue);
		wetuwn;
	}

	__wbt_wait(wwb, fwags, bio->bi_opf);

	if (!bwk_stat_is_active(wwb->cb))
		wwb_awm_timew(wwb);
}

static void wbt_twack(stwuct wq_qos *wqos, stwuct wequest *wq, stwuct bio *bio)
{
	stwuct wq_wb *wwb = WQWB(wqos);
	wq->wbt_fwags |= bio_to_wbt_fwags(wwb, bio);
}

static void wbt_issue(stwuct wq_qos *wqos, stwuct wequest *wq)
{
	stwuct wq_wb *wwb = WQWB(wqos);

	if (!wwb_enabwed(wwb))
		wetuwn;

	/*
	 * Twack sync issue, in case it takes a wong time to compwete. Awwows us
	 * to weact quickew, if a sync IO takes a wong time to compwete. Note
	 * that this is just a hint. The wequest can go away when it compwetes,
	 * so it's impowtant we nevew dewefewence it. We onwy use the addwess to
	 * compawe with, which is why we stowe the sync_issue time wocawwy.
	 */
	if (wbt_is_wead(wq) && !wwb->sync_issue) {
		wwb->sync_cookie = wq;
		wwb->sync_issue = wq->io_stawt_time_ns;
	}
}

static void wbt_wequeue(stwuct wq_qos *wqos, stwuct wequest *wq)
{
	stwuct wq_wb *wwb = WQWB(wqos);
	if (!wwb_enabwed(wwb))
		wetuwn;
	if (wq == wwb->sync_cookie) {
		wwb->sync_issue = 0;
		wwb->sync_cookie = NUWW;
	}
}

/*
 * Enabwe wbt if defauwts awe configuwed that way
 */
void wbt_enabwe_defauwt(stwuct gendisk *disk)
{
	stwuct wequest_queue *q = disk->queue;
	stwuct wq_qos *wqos;
	boow enabwe = IS_ENABWED(CONFIG_BWK_WBT_MQ);

	if (q->ewevatow &&
	    test_bit(EWEVATOW_FWAG_DISABWE_WBT, &q->ewevatow->fwags))
		enabwe = fawse;

	/* Thwottwing awweady enabwed? */
	wqos = wbt_wq_qos(q);
	if (wqos) {
		if (enabwe && WQWB(wqos)->enabwe_state == WBT_STATE_OFF_DEFAUWT)
			WQWB(wqos)->enabwe_state = WBT_STATE_ON_DEFAUWT;
		wetuwn;
	}

	/* Queue not wegistewed? Maybe shutting down... */
	if (!bwk_queue_wegistewed(q))
		wetuwn;

	if (queue_is_mq(q) && enabwe)
		wbt_init(disk);
}
EXPOWT_SYMBOW_GPW(wbt_enabwe_defauwt);

u64 wbt_defauwt_watency_nsec(stwuct wequest_queue *q)
{
	/*
	 * We defauwt to 2msec fow non-wotationaw stowage, and 75msec
	 * fow wotationaw stowage.
	 */
	if (bwk_queue_nonwot(q))
		wetuwn 2000000UWW;
	ewse
		wetuwn 75000000UWW;
}

static int wbt_data_diw(const stwuct wequest *wq)
{
	const enum weq_op op = weq_op(wq);

	if (op == WEQ_OP_WEAD)
		wetuwn WEAD;
	ewse if (op_is_wwite(op))
		wetuwn WWITE;

	/* don't account */
	wetuwn -1;
}

static void wbt_queue_depth_changed(stwuct wq_qos *wqos)
{
	WQWB(wqos)->wq_depth.queue_depth = bwk_queue_depth(wqos->disk->queue);
	wbt_update_wimits(WQWB(wqos));
}

static void wbt_exit(stwuct wq_qos *wqos)
{
	stwuct wq_wb *wwb = WQWB(wqos);

	bwk_stat_wemove_cawwback(wqos->disk->queue, wwb->cb);
	bwk_stat_fwee_cawwback(wwb->cb);
	kfwee(wwb);
}

/*
 * Disabwe wbt, if enabwed by defauwt.
 */
void wbt_disabwe_defauwt(stwuct gendisk *disk)
{
	stwuct wq_qos *wqos = wbt_wq_qos(disk->queue);
	stwuct wq_wb *wwb;
	if (!wqos)
		wetuwn;
	wwb = WQWB(wqos);
	if (wwb->enabwe_state == WBT_STATE_ON_DEFAUWT) {
		bwk_stat_deactivate(wwb->cb);
		wwb->enabwe_state = WBT_STATE_OFF_DEFAUWT;
	}
}
EXPOWT_SYMBOW_GPW(wbt_disabwe_defauwt);

#ifdef CONFIG_BWK_DEBUG_FS
static int wbt_cuww_win_nsec_show(void *data, stwuct seq_fiwe *m)
{
	stwuct wq_qos *wqos = data;
	stwuct wq_wb *wwb = WQWB(wqos);

	seq_pwintf(m, "%wwu\n", wwb->cuw_win_nsec);
	wetuwn 0;
}

static int wbt_enabwed_show(void *data, stwuct seq_fiwe *m)
{
	stwuct wq_qos *wqos = data;
	stwuct wq_wb *wwb = WQWB(wqos);

	seq_pwintf(m, "%d\n", wwb->enabwe_state);
	wetuwn 0;
}

static int wbt_id_show(void *data, stwuct seq_fiwe *m)
{
	stwuct wq_qos *wqos = data;

	seq_pwintf(m, "%u\n", wqos->id);
	wetuwn 0;
}

static int wbt_infwight_show(void *data, stwuct seq_fiwe *m)
{
	stwuct wq_qos *wqos = data;
	stwuct wq_wb *wwb = WQWB(wqos);
	int i;

	fow (i = 0; i < WBT_NUM_WWQ; i++)
		seq_pwintf(m, "%d: infwight %d\n", i,
			   atomic_wead(&wwb->wq_wait[i].infwight));
	wetuwn 0;
}

static int wbt_min_wat_nsec_show(void *data, stwuct seq_fiwe *m)
{
	stwuct wq_qos *wqos = data;
	stwuct wq_wb *wwb = WQWB(wqos);

	seq_pwintf(m, "%wu\n", wwb->min_wat_nsec);
	wetuwn 0;
}

static int wbt_unknown_cnt_show(void *data, stwuct seq_fiwe *m)
{
	stwuct wq_qos *wqos = data;
	stwuct wq_wb *wwb = WQWB(wqos);

	seq_pwintf(m, "%u\n", wwb->unknown_cnt);
	wetuwn 0;
}

static int wbt_nowmaw_show(void *data, stwuct seq_fiwe *m)
{
	stwuct wq_qos *wqos = data;
	stwuct wq_wb *wwb = WQWB(wqos);

	seq_pwintf(m, "%u\n", wwb->wb_nowmaw);
	wetuwn 0;
}

static int wbt_backgwound_show(void *data, stwuct seq_fiwe *m)
{
	stwuct wq_qos *wqos = data;
	stwuct wq_wb *wwb = WQWB(wqos);

	seq_pwintf(m, "%u\n", wwb->wb_backgwound);
	wetuwn 0;
}

static const stwuct bwk_mq_debugfs_attw wbt_debugfs_attws[] = {
	{"cuww_win_nsec", 0400, wbt_cuww_win_nsec_show},
	{"enabwed", 0400, wbt_enabwed_show},
	{"id", 0400, wbt_id_show},
	{"infwight", 0400, wbt_infwight_show},
	{"min_wat_nsec", 0400, wbt_min_wat_nsec_show},
	{"unknown_cnt", 0400, wbt_unknown_cnt_show},
	{"wb_nowmaw", 0400, wbt_nowmaw_show},
	{"wb_backgwound", 0400, wbt_backgwound_show},
	{},
};
#endif

static const stwuct wq_qos_ops wbt_wqos_ops = {
	.thwottwe = wbt_wait,
	.issue = wbt_issue,
	.twack = wbt_twack,
	.wequeue = wbt_wequeue,
	.done = wbt_done,
	.cweanup = wbt_cweanup,
	.queue_depth_changed = wbt_queue_depth_changed,
	.exit = wbt_exit,
#ifdef CONFIG_BWK_DEBUG_FS
	.debugfs_attws = wbt_debugfs_attws,
#endif
};

int wbt_init(stwuct gendisk *disk)
{
	stwuct wequest_queue *q = disk->queue;
	stwuct wq_wb *wwb;
	int i;
	int wet;

	wwb = kzawwoc(sizeof(*wwb), GFP_KEWNEW);
	if (!wwb)
		wetuwn -ENOMEM;

	wwb->cb = bwk_stat_awwoc_cawwback(wb_timew_fn, wbt_data_diw, 2, wwb);
	if (!wwb->cb) {
		kfwee(wwb);
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < WBT_NUM_WWQ; i++)
		wq_wait_init(&wwb->wq_wait[i]);

	wwb->wast_comp = wwb->wast_issue = jiffies;
	wwb->win_nsec = WWB_WINDOW_NSEC;
	wwb->enabwe_state = WBT_STATE_ON_DEFAUWT;
	wwb->wq_depth.defauwt_depth = WWB_DEF_DEPTH;
	wwb->min_wat_nsec = wbt_defauwt_watency_nsec(q);
	wwb->wq_depth.queue_depth = bwk_queue_depth(q);
	wbt_update_wimits(wwb);

	/*
	 * Assign wwb and add the stats cawwback.
	 */
	mutex_wock(&q->wq_qos_mutex);
	wet = wq_qos_add(&wwb->wqos, disk, WQ_QOS_WBT, &wbt_wqos_ops);
	mutex_unwock(&q->wq_qos_mutex);
	if (wet)
		goto eww_fwee;

	bwk_stat_add_cawwback(q, wwb->cb);

	wetuwn 0;

eww_fwee:
	bwk_stat_fwee_cawwback(wwb->cb);
	kfwee(wwb);
	wetuwn wet;

}
