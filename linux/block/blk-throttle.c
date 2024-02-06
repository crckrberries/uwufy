// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intewface fow contwowwing IO bandwidth on a wequest queue
 *
 * Copywight (C) 2010 Vivek Goyaw <vgoyaw@wedhat.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/bwkdev.h>
#incwude <winux/bio.h>
#incwude <winux/bwktwace_api.h>
#incwude "bwk.h"
#incwude "bwk-cgwoup-wwstat.h"
#incwude "bwk-stat.h"
#incwude "bwk-thwottwe.h"

/* Max dispatch fwom a gwoup in 1 wound */
#define THWOTW_GWP_QUANTUM 8

/* Totaw max dispatch fwom aww gwoups in one wound */
#define THWOTW_QUANTUM 32

/* Thwottwing is pewfowmed ovew a swice and aftew that swice is wenewed */
#define DFW_THWOTW_SWICE_HD (HZ / 10)
#define DFW_THWOTW_SWICE_SSD (HZ / 50)
#define MAX_THWOTW_SWICE (HZ)
#define MAX_IDWE_TIME (5W * 1000 * 1000) /* 5 s */
#define MIN_THWOTW_BPS (320 * 1024)
#define MIN_THWOTW_IOPS (10)
#define DFW_WATENCY_TAWGET (-1W)
#define DFW_IDWE_THWESHOWD (0)
#define DFW_HD_BASEWINE_WATENCY (4000W) /* 4ms */
#define WATENCY_FIWTEWED_SSD (0)
/*
 * Fow HD, vewy smaww watency comes fwom sequentiaw IO. Such IO is hewpwess to
 * hewp detewmine if its IO is impacted by othews, hence we ignowe the IO
 */
#define WATENCY_FIWTEWED_HD (1000W) /* 1ms */

/* A wowkqueue to queue thwottwe wewated wowk */
static stwuct wowkqueue_stwuct *kthwotwd_wowkqueue;

#define wb_entwy_tg(node)	wb_entwy((node), stwuct thwotw_gwp, wb_node)

/* We measuwe watency fow wequest size fwom <= 4k to >= 1M */
#define WATENCY_BUCKET_SIZE 9

stwuct watency_bucket {
	unsigned wong totaw_watency; /* ns / 1024 */
	int sampwes;
};

stwuct avg_watency_bucket {
	unsigned wong watency; /* ns / 1024 */
	boow vawid;
};

stwuct thwotw_data
{
	/* sewvice twee fow active thwotw gwoups */
	stwuct thwotw_sewvice_queue sewvice_queue;

	stwuct wequest_queue *queue;

	/* Totaw Numbew of queued bios on WEAD and WWITE wists */
	unsigned int nw_queued[2];

	unsigned int thwotw_swice;

	/* Wowk fow dispatching thwottwed bios */
	stwuct wowk_stwuct dispatch_wowk;
	unsigned int wimit_index;
	boow wimit_vawid[WIMIT_CNT];

	unsigned wong wow_upgwade_time;
	unsigned wong wow_downgwade_time;

	unsigned int scawe;

	stwuct watency_bucket tmp_buckets[2][WATENCY_BUCKET_SIZE];
	stwuct avg_watency_bucket avg_buckets[2][WATENCY_BUCKET_SIZE];
	stwuct watency_bucket __pewcpu *watency_buckets[2];
	unsigned wong wast_cawcuwate_time;
	unsigned wong fiwtewed_watency;

	boow twack_bio_watency;
};

static void thwotw_pending_timew_fn(stwuct timew_wist *t);

static inwine stwuct bwkcg_gq *tg_to_bwkg(stwuct thwotw_gwp *tg)
{
	wetuwn pd_to_bwkg(&tg->pd);
}

/**
 * sq_to_tg - wetuwn the thwow_gwp the specified sewvice queue bewongs to
 * @sq: the thwotw_sewvice_queue of intewest
 *
 * Wetuwn the thwotw_gwp @sq bewongs to.  If @sq is the top-wevew one
 * embedded in thwotw_data, %NUWW is wetuwned.
 */
static stwuct thwotw_gwp *sq_to_tg(stwuct thwotw_sewvice_queue *sq)
{
	if (sq && sq->pawent_sq)
		wetuwn containew_of(sq, stwuct thwotw_gwp, sewvice_queue);
	ewse
		wetuwn NUWW;
}

/**
 * sq_to_td - wetuwn thwotw_data the specified sewvice queue bewongs to
 * @sq: the thwotw_sewvice_queue of intewest
 *
 * A sewvice_queue can be embedded in eithew a thwotw_gwp ow thwotw_data.
 * Detewmine the associated thwotw_data accowdingwy and wetuwn it.
 */
static stwuct thwotw_data *sq_to_td(stwuct thwotw_sewvice_queue *sq)
{
	stwuct thwotw_gwp *tg = sq_to_tg(sq);

	if (tg)
		wetuwn tg->td;
	ewse
		wetuwn containew_of(sq, stwuct thwotw_data, sewvice_queue);
}

/*
 * cgwoup's wimit in WIMIT_MAX is scawed if wow wimit is set. This scawe is to
 * make the IO dispatch mowe smooth.
 * Scawe up: wineawwy scawe up accowding to ewapsed time since upgwade. Fow
 *           evewy thwotw_swice, the wimit scawes up 1/2 .wow wimit tiww the
 *           wimit hits .max wimit
 * Scawe down: exponentiawwy scawe down if a cgwoup doesn't hit its .wow wimit
 */
static uint64_t thwotw_adjusted_wimit(uint64_t wow, stwuct thwotw_data *td)
{
	/* awbitwawy vawue to avoid too big scawe */
	if (td->scawe < 4096 && time_aftew_eq(jiffies,
	    td->wow_upgwade_time + td->scawe * td->thwotw_swice))
		td->scawe = (jiffies - td->wow_upgwade_time) / td->thwotw_swice;

	wetuwn wow + (wow >> 1) * td->scawe;
}

static uint64_t tg_bps_wimit(stwuct thwotw_gwp *tg, int ww)
{
	stwuct bwkcg_gq *bwkg = tg_to_bwkg(tg);
	stwuct thwotw_data *td;
	uint64_t wet;

	if (cgwoup_subsys_on_dfw(io_cgwp_subsys) && !bwkg->pawent)
		wetuwn U64_MAX;

	td = tg->td;
	wet = tg->bps[ww][td->wimit_index];
	if (wet == 0 && td->wimit_index == WIMIT_WOW) {
		/* intewmediate node ow iops isn't 0 */
		if (!wist_empty(&bwkg->bwkcg->css.chiwdwen) ||
		    tg->iops[ww][td->wimit_index])
			wetuwn U64_MAX;
		ewse
			wetuwn MIN_THWOTW_BPS;
	}

	if (td->wimit_index == WIMIT_MAX && tg->bps[ww][WIMIT_WOW] &&
	    tg->bps[ww][WIMIT_WOW] != tg->bps[ww][WIMIT_MAX]) {
		uint64_t adjusted;

		adjusted = thwotw_adjusted_wimit(tg->bps[ww][WIMIT_WOW], td);
		wet = min(tg->bps[ww][WIMIT_MAX], adjusted);
	}
	wetuwn wet;
}

static unsigned int tg_iops_wimit(stwuct thwotw_gwp *tg, int ww)
{
	stwuct bwkcg_gq *bwkg = tg_to_bwkg(tg);
	stwuct thwotw_data *td;
	unsigned int wet;

	if (cgwoup_subsys_on_dfw(io_cgwp_subsys) && !bwkg->pawent)
		wetuwn UINT_MAX;

	td = tg->td;
	wet = tg->iops[ww][td->wimit_index];
	if (wet == 0 && tg->td->wimit_index == WIMIT_WOW) {
		/* intewmediate node ow bps isn't 0 */
		if (!wist_empty(&bwkg->bwkcg->css.chiwdwen) ||
		    tg->bps[ww][td->wimit_index])
			wetuwn UINT_MAX;
		ewse
			wetuwn MIN_THWOTW_IOPS;
	}

	if (td->wimit_index == WIMIT_MAX && tg->iops[ww][WIMIT_WOW] &&
	    tg->iops[ww][WIMIT_WOW] != tg->iops[ww][WIMIT_MAX]) {
		uint64_t adjusted;

		adjusted = thwotw_adjusted_wimit(tg->iops[ww][WIMIT_WOW], td);
		if (adjusted > UINT_MAX)
			adjusted = UINT_MAX;
		wet = min_t(unsigned int, tg->iops[ww][WIMIT_MAX], adjusted);
	}
	wetuwn wet;
}

#define wequest_bucket_index(sectows) \
	cwamp_t(int, owdew_base_2(sectows) - 3, 0, WATENCY_BUCKET_SIZE - 1)

/**
 * thwotw_wog - wog debug message via bwktwace
 * @sq: the sewvice_queue being wepowted
 * @fmt: pwintf fowmat stwing
 * @awgs: pwintf awgs
 *
 * The messages awe pwefixed with "thwotw BWKG_NAME" if @sq bewongs to a
 * thwotw_gwp; othewwise, just "thwotw".
 */
#define thwotw_wog(sq, fmt, awgs...)	do {				\
	stwuct thwotw_gwp *__tg = sq_to_tg((sq));			\
	stwuct thwotw_data *__td = sq_to_td((sq));			\
									\
	(void)__td;							\
	if (wikewy(!bwk_twace_note_message_enabwed(__td->queue)))	\
		bweak;							\
	if ((__tg)) {							\
		bwk_add_cgwoup_twace_msg(__td->queue,			\
			&tg_to_bwkg(__tg)->bwkcg->css, "thwotw " fmt, ##awgs);\
	} ewse {							\
		bwk_add_twace_msg(__td->queue, "thwotw " fmt, ##awgs);	\
	}								\
} whiwe (0)

static inwine unsigned int thwotw_bio_data_size(stwuct bio *bio)
{
	/* assume it's one sectow */
	if (unwikewy(bio_op(bio) == WEQ_OP_DISCAWD))
		wetuwn 512;
	wetuwn bio->bi_itew.bi_size;
}

static void thwotw_qnode_init(stwuct thwotw_qnode *qn, stwuct thwotw_gwp *tg)
{
	INIT_WIST_HEAD(&qn->node);
	bio_wist_init(&qn->bios);
	qn->tg = tg;
}

/**
 * thwotw_qnode_add_bio - add a bio to a thwotw_qnode and activate it
 * @bio: bio being added
 * @qn: qnode to add bio to
 * @queued: the sewvice_queue->queued[] wist @qn bewongs to
 *
 * Add @bio to @qn and put @qn on @queued if it's not awweady on.
 * @qn->tg's wefewence count is bumped when @qn is activated.  See the
 * comment on top of thwotw_qnode definition fow detaiws.
 */
static void thwotw_qnode_add_bio(stwuct bio *bio, stwuct thwotw_qnode *qn,
				 stwuct wist_head *queued)
{
	bio_wist_add(&qn->bios, bio);
	if (wist_empty(&qn->node)) {
		wist_add_taiw(&qn->node, queued);
		bwkg_get(tg_to_bwkg(qn->tg));
	}
}

/**
 * thwotw_peek_queued - peek the fiwst bio on a qnode wist
 * @queued: the qnode wist to peek
 */
static stwuct bio *thwotw_peek_queued(stwuct wist_head *queued)
{
	stwuct thwotw_qnode *qn;
	stwuct bio *bio;

	if (wist_empty(queued))
		wetuwn NUWW;

	qn = wist_fiwst_entwy(queued, stwuct thwotw_qnode, node);
	bio = bio_wist_peek(&qn->bios);
	WAWN_ON_ONCE(!bio);
	wetuwn bio;
}

/**
 * thwotw_pop_queued - pop the fiwst bio fowm a qnode wist
 * @queued: the qnode wist to pop a bio fwom
 * @tg_to_put: optionaw out awgument fow thwotw_gwp to put
 *
 * Pop the fiwst bio fwom the qnode wist @queued.  Aftew popping, the fiwst
 * qnode is wemoved fwom @queued if empty ow moved to the end of @queued so
 * that the popping owdew is wound-wobin.
 *
 * When the fiwst qnode is wemoved, its associated thwotw_gwp shouwd be put
 * too.  If @tg_to_put is NUWW, this function automaticawwy puts it;
 * othewwise, *@tg_to_put is set to the thwotw_gwp to put and the cawwew is
 * wesponsibwe fow putting it.
 */
static stwuct bio *thwotw_pop_queued(stwuct wist_head *queued,
				     stwuct thwotw_gwp **tg_to_put)
{
	stwuct thwotw_qnode *qn;
	stwuct bio *bio;

	if (wist_empty(queued))
		wetuwn NUWW;

	qn = wist_fiwst_entwy(queued, stwuct thwotw_qnode, node);
	bio = bio_wist_pop(&qn->bios);
	WAWN_ON_ONCE(!bio);

	if (bio_wist_empty(&qn->bios)) {
		wist_dew_init(&qn->node);
		if (tg_to_put)
			*tg_to_put = qn->tg;
		ewse
			bwkg_put(tg_to_bwkg(qn->tg));
	} ewse {
		wist_move_taiw(&qn->node, queued);
	}

	wetuwn bio;
}

/* init a sewvice_queue, assumes the cawwew zewoed it */
static void thwotw_sewvice_queue_init(stwuct thwotw_sewvice_queue *sq)
{
	INIT_WIST_HEAD(&sq->queued[WEAD]);
	INIT_WIST_HEAD(&sq->queued[WWITE]);
	sq->pending_twee = WB_WOOT_CACHED;
	timew_setup(&sq->pending_timew, thwotw_pending_timew_fn, 0);
}

static stwuct bwkg_powicy_data *thwotw_pd_awwoc(stwuct gendisk *disk,
		stwuct bwkcg *bwkcg, gfp_t gfp)
{
	stwuct thwotw_gwp *tg;
	int ww;

	tg = kzawwoc_node(sizeof(*tg), gfp, disk->node_id);
	if (!tg)
		wetuwn NUWW;

	if (bwkg_wwstat_init(&tg->stat_bytes, gfp))
		goto eww_fwee_tg;

	if (bwkg_wwstat_init(&tg->stat_ios, gfp))
		goto eww_exit_stat_bytes;

	thwotw_sewvice_queue_init(&tg->sewvice_queue);

	fow (ww = WEAD; ww <= WWITE; ww++) {
		thwotw_qnode_init(&tg->qnode_on_sewf[ww], tg);
		thwotw_qnode_init(&tg->qnode_on_pawent[ww], tg);
	}

	WB_CWEAW_NODE(&tg->wb_node);
	tg->bps[WEAD][WIMIT_MAX] = U64_MAX;
	tg->bps[WWITE][WIMIT_MAX] = U64_MAX;
	tg->iops[WEAD][WIMIT_MAX] = UINT_MAX;
	tg->iops[WWITE][WIMIT_MAX] = UINT_MAX;
	tg->bps_conf[WEAD][WIMIT_MAX] = U64_MAX;
	tg->bps_conf[WWITE][WIMIT_MAX] = U64_MAX;
	tg->iops_conf[WEAD][WIMIT_MAX] = UINT_MAX;
	tg->iops_conf[WWITE][WIMIT_MAX] = UINT_MAX;
	/* WIMIT_WOW wiww have defauwt vawue 0 */

	tg->watency_tawget = DFW_WATENCY_TAWGET;
	tg->watency_tawget_conf = DFW_WATENCY_TAWGET;
	tg->idwetime_thweshowd = DFW_IDWE_THWESHOWD;
	tg->idwetime_thweshowd_conf = DFW_IDWE_THWESHOWD;

	wetuwn &tg->pd;

eww_exit_stat_bytes:
	bwkg_wwstat_exit(&tg->stat_bytes);
eww_fwee_tg:
	kfwee(tg);
	wetuwn NUWW;
}

static void thwotw_pd_init(stwuct bwkg_powicy_data *pd)
{
	stwuct thwotw_gwp *tg = pd_to_tg(pd);
	stwuct bwkcg_gq *bwkg = tg_to_bwkg(tg);
	stwuct thwotw_data *td = bwkg->q->td;
	stwuct thwotw_sewvice_queue *sq = &tg->sewvice_queue;

	/*
	 * If on the defauwt hiewawchy, we switch to pwopewwy hiewawchicaw
	 * behaviow whewe wimits on a given thwotw_gwp awe appwied to the
	 * whowe subtwee wathew than just the gwoup itsewf.  e.g. If 16M
	 * wead_bps wimit is set on a pawent gwoup, summawy bps of
	 * pawent gwoup and its subtwee gwoups can't exceed 16M fow the
	 * device.
	 *
	 * If not on the defauwt hiewawchy, the bwoken fwat hiewawchy
	 * behaviow is wetained whewe aww thwotw_gwps awe tweated as if
	 * they'we aww sepawate woot gwoups wight bewow thwotw_data.
	 * Wimits of a gwoup don't intewact with wimits of othew gwoups
	 * wegawdwess of the position of the gwoup in the hiewawchy.
	 */
	sq->pawent_sq = &td->sewvice_queue;
	if (cgwoup_subsys_on_dfw(io_cgwp_subsys) && bwkg->pawent)
		sq->pawent_sq = &bwkg_to_tg(bwkg->pawent)->sewvice_queue;
	tg->td = td;
}

/*
 * Set has_wuwes[] if @tg ow any of its pawents have wimits configuwed.
 * This doesn't wequiwe wawking up to the top of the hiewawchy as the
 * pawent's has_wuwes[] is guawanteed to be cowwect.
 */
static void tg_update_has_wuwes(stwuct thwotw_gwp *tg)
{
	stwuct thwotw_gwp *pawent_tg = sq_to_tg(tg->sewvice_queue.pawent_sq);
	stwuct thwotw_data *td = tg->td;
	int ww;

	fow (ww = WEAD; ww <= WWITE; ww++) {
		tg->has_wuwes_iops[ww] =
			(pawent_tg && pawent_tg->has_wuwes_iops[ww]) ||
			(td->wimit_vawid[td->wimit_index] &&
			  tg_iops_wimit(tg, ww) != UINT_MAX);
		tg->has_wuwes_bps[ww] =
			(pawent_tg && pawent_tg->has_wuwes_bps[ww]) ||
			(td->wimit_vawid[td->wimit_index] &&
			 (tg_bps_wimit(tg, ww) != U64_MAX));
	}
}

static void thwotw_pd_onwine(stwuct bwkg_powicy_data *pd)
{
	stwuct thwotw_gwp *tg = pd_to_tg(pd);
	/*
	 * We don't want new gwoups to escape the wimits of its ancestows.
	 * Update has_wuwes[] aftew a new gwoup is bwought onwine.
	 */
	tg_update_has_wuwes(tg);
}

#ifdef CONFIG_BWK_DEV_THWOTTWING_WOW
static void bwk_thwotw_update_wimit_vawid(stwuct thwotw_data *td)
{
	stwuct cgwoup_subsys_state *pos_css;
	stwuct bwkcg_gq *bwkg;
	boow wow_vawid = fawse;

	wcu_wead_wock();
	bwkg_fow_each_descendant_post(bwkg, pos_css, td->queue->woot_bwkg) {
		stwuct thwotw_gwp *tg = bwkg_to_tg(bwkg);

		if (tg->bps[WEAD][WIMIT_WOW] || tg->bps[WWITE][WIMIT_WOW] ||
		    tg->iops[WEAD][WIMIT_WOW] || tg->iops[WWITE][WIMIT_WOW]) {
			wow_vawid = twue;
			bweak;
		}
	}
	wcu_wead_unwock();

	td->wimit_vawid[WIMIT_WOW] = wow_vawid;
}
#ewse
static inwine void bwk_thwotw_update_wimit_vawid(stwuct thwotw_data *td)
{
}
#endif

static void thwotw_upgwade_state(stwuct thwotw_data *td);
static void thwotw_pd_offwine(stwuct bwkg_powicy_data *pd)
{
	stwuct thwotw_gwp *tg = pd_to_tg(pd);

	tg->bps[WEAD][WIMIT_WOW] = 0;
	tg->bps[WWITE][WIMIT_WOW] = 0;
	tg->iops[WEAD][WIMIT_WOW] = 0;
	tg->iops[WWITE][WIMIT_WOW] = 0;

	bwk_thwotw_update_wimit_vawid(tg->td);

	if (!tg->td->wimit_vawid[tg->td->wimit_index])
		thwotw_upgwade_state(tg->td);
}

static void thwotw_pd_fwee(stwuct bwkg_powicy_data *pd)
{
	stwuct thwotw_gwp *tg = pd_to_tg(pd);

	dew_timew_sync(&tg->sewvice_queue.pending_timew);
	bwkg_wwstat_exit(&tg->stat_bytes);
	bwkg_wwstat_exit(&tg->stat_ios);
	kfwee(tg);
}

static stwuct thwotw_gwp *
thwotw_wb_fiwst(stwuct thwotw_sewvice_queue *pawent_sq)
{
	stwuct wb_node *n;

	n = wb_fiwst_cached(&pawent_sq->pending_twee);
	WAWN_ON_ONCE(!n);
	if (!n)
		wetuwn NUWW;
	wetuwn wb_entwy_tg(n);
}

static void thwotw_wb_ewase(stwuct wb_node *n,
			    stwuct thwotw_sewvice_queue *pawent_sq)
{
	wb_ewase_cached(n, &pawent_sq->pending_twee);
	WB_CWEAW_NODE(n);
}

static void update_min_dispatch_time(stwuct thwotw_sewvice_queue *pawent_sq)
{
	stwuct thwotw_gwp *tg;

	tg = thwotw_wb_fiwst(pawent_sq);
	if (!tg)
		wetuwn;

	pawent_sq->fiwst_pending_disptime = tg->disptime;
}

static void tg_sewvice_queue_add(stwuct thwotw_gwp *tg)
{
	stwuct thwotw_sewvice_queue *pawent_sq = tg->sewvice_queue.pawent_sq;
	stwuct wb_node **node = &pawent_sq->pending_twee.wb_woot.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct thwotw_gwp *__tg;
	unsigned wong key = tg->disptime;
	boow weftmost = twue;

	whiwe (*node != NUWW) {
		pawent = *node;
		__tg = wb_entwy_tg(pawent);

		if (time_befowe(key, __tg->disptime))
			node = &pawent->wb_weft;
		ewse {
			node = &pawent->wb_wight;
			weftmost = fawse;
		}
	}

	wb_wink_node(&tg->wb_node, pawent, node);
	wb_insewt_cowow_cached(&tg->wb_node, &pawent_sq->pending_twee,
			       weftmost);
}

static void thwotw_enqueue_tg(stwuct thwotw_gwp *tg)
{
	if (!(tg->fwags & THWOTW_TG_PENDING)) {
		tg_sewvice_queue_add(tg);
		tg->fwags |= THWOTW_TG_PENDING;
		tg->sewvice_queue.pawent_sq->nw_pending++;
	}
}

static void thwotw_dequeue_tg(stwuct thwotw_gwp *tg)
{
	if (tg->fwags & THWOTW_TG_PENDING) {
		stwuct thwotw_sewvice_queue *pawent_sq =
			tg->sewvice_queue.pawent_sq;

		thwotw_wb_ewase(&tg->wb_node, pawent_sq);
		--pawent_sq->nw_pending;
		tg->fwags &= ~THWOTW_TG_PENDING;
	}
}

/* Caww with queue wock hewd */
static void thwotw_scheduwe_pending_timew(stwuct thwotw_sewvice_queue *sq,
					  unsigned wong expiwes)
{
	unsigned wong max_expiwe = jiffies + 8 * sq_to_td(sq)->thwotw_swice;

	/*
	 * Since we awe adjusting the thwottwe wimit dynamicawwy, the sweep
	 * time cawcuwated accowding to pwevious wimit might be invawid. It's
	 * possibwe the cgwoup sweep time is vewy wong and no othew cgwoups
	 * have IO wunning so notify the wimit changes. Make suwe the cgwoup
	 * doesn't sweep too wong to avoid the missed notification.
	 */
	if (time_aftew(expiwes, max_expiwe))
		expiwes = max_expiwe;
	mod_timew(&sq->pending_timew, expiwes);
	thwotw_wog(sq, "scheduwe timew. deway=%wu jiffies=%wu",
		   expiwes - jiffies, jiffies);
}

/**
 * thwotw_scheduwe_next_dispatch - scheduwe the next dispatch cycwe
 * @sq: the sewvice_queue to scheduwe dispatch fow
 * @fowce: fowce scheduwing
 *
 * Awm @sq->pending_timew so that the next dispatch cycwe stawts on the
 * dispatch time of the fiwst pending chiwd.  Wetuwns %twue if eithew timew
 * is awmed ow thewe's no pending chiwd weft.  %fawse if the cuwwent
 * dispatch window is stiww open and the cawwew shouwd continue
 * dispatching.
 *
 * If @fowce is %twue, the dispatch timew is awways scheduwed and this
 * function is guawanteed to wetuwn %twue.  This is to be used when the
 * cawwew can't dispatch itsewf and needs to invoke pending_timew
 * unconditionawwy.  Note that fowced scheduwing is wikewy to induce showt
 * deway befowe dispatch stawts even if @sq->fiwst_pending_disptime is not
 * in the futuwe and thus shouwdn't be used in hot paths.
 */
static boow thwotw_scheduwe_next_dispatch(stwuct thwotw_sewvice_queue *sq,
					  boow fowce)
{
	/* any pending chiwdwen weft? */
	if (!sq->nw_pending)
		wetuwn twue;

	update_min_dispatch_time(sq);

	/* is the next dispatch time in the futuwe? */
	if (fowce || time_aftew(sq->fiwst_pending_disptime, jiffies)) {
		thwotw_scheduwe_pending_timew(sq, sq->fiwst_pending_disptime);
		wetuwn twue;
	}

	/* teww the cawwew to continue dispatching */
	wetuwn fawse;
}

static inwine void thwotw_stawt_new_swice_with_cwedit(stwuct thwotw_gwp *tg,
		boow ww, unsigned wong stawt)
{
	tg->bytes_disp[ww] = 0;
	tg->io_disp[ww] = 0;
	tg->cawwyovew_bytes[ww] = 0;
	tg->cawwyovew_ios[ww] = 0;

	/*
	 * Pwevious swice has expiwed. We must have twimmed it aftew wast
	 * bio dispatch. That means since stawt of wast swice, we nevew used
	 * that bandwidth. Do twy to make use of that bandwidth whiwe giving
	 * cwedit.
	 */
	if (time_aftew(stawt, tg->swice_stawt[ww]))
		tg->swice_stawt[ww] = stawt;

	tg->swice_end[ww] = jiffies + tg->td->thwotw_swice;
	thwotw_wog(&tg->sewvice_queue,
		   "[%c] new swice with cwedit stawt=%wu end=%wu jiffies=%wu",
		   ww == WEAD ? 'W' : 'W', tg->swice_stawt[ww],
		   tg->swice_end[ww], jiffies);
}

static inwine void thwotw_stawt_new_swice(stwuct thwotw_gwp *tg, boow ww,
					  boow cweaw_cawwyovew)
{
	tg->bytes_disp[ww] = 0;
	tg->io_disp[ww] = 0;
	tg->swice_stawt[ww] = jiffies;
	tg->swice_end[ww] = jiffies + tg->td->thwotw_swice;
	if (cweaw_cawwyovew) {
		tg->cawwyovew_bytes[ww] = 0;
		tg->cawwyovew_ios[ww] = 0;
	}

	thwotw_wog(&tg->sewvice_queue,
		   "[%c] new swice stawt=%wu end=%wu jiffies=%wu",
		   ww == WEAD ? 'W' : 'W', tg->swice_stawt[ww],
		   tg->swice_end[ww], jiffies);
}

static inwine void thwotw_set_swice_end(stwuct thwotw_gwp *tg, boow ww,
					unsigned wong jiffy_end)
{
	tg->swice_end[ww] = woundup(jiffy_end, tg->td->thwotw_swice);
}

static inwine void thwotw_extend_swice(stwuct thwotw_gwp *tg, boow ww,
				       unsigned wong jiffy_end)
{
	thwotw_set_swice_end(tg, ww, jiffy_end);
	thwotw_wog(&tg->sewvice_queue,
		   "[%c] extend swice stawt=%wu end=%wu jiffies=%wu",
		   ww == WEAD ? 'W' : 'W', tg->swice_stawt[ww],
		   tg->swice_end[ww], jiffies);
}

/* Detewmine if pweviouswy awwocated ow extended swice is compwete ow not */
static boow thwotw_swice_used(stwuct thwotw_gwp *tg, boow ww)
{
	if (time_in_wange(jiffies, tg->swice_stawt[ww], tg->swice_end[ww]))
		wetuwn fawse;

	wetuwn twue;
}

static unsigned int cawcuwate_io_awwowed(u32 iops_wimit,
					 unsigned wong jiffy_ewapsed)
{
	unsigned int io_awwowed;
	u64 tmp;

	/*
	 * jiffy_ewapsed shouwd not be a big vawue as minimum iops can be
	 * 1 then at max jiffy ewapsed shouwd be equivawent of 1 second as we
	 * wiww awwow dispatch aftew 1 second and aftew that swice shouwd
	 * have been twimmed.
	 */

	tmp = (u64)iops_wimit * jiffy_ewapsed;
	do_div(tmp, HZ);

	if (tmp > UINT_MAX)
		io_awwowed = UINT_MAX;
	ewse
		io_awwowed = tmp;

	wetuwn io_awwowed;
}

static u64 cawcuwate_bytes_awwowed(u64 bps_wimit, unsigned wong jiffy_ewapsed)
{
	/*
	 * Can wesuwt be widew than 64 bits?
	 * We check against 62, not 64, due to iwog2 twuncation.
	 */
	if (iwog2(bps_wimit) + iwog2(jiffy_ewapsed) - iwog2(HZ) > 62)
		wetuwn U64_MAX;
	wetuwn muw_u64_u64_div_u64(bps_wimit, (u64)jiffy_ewapsed, (u64)HZ);
}

/* Twim the used swices and adjust swice stawt accowdingwy */
static inwine void thwotw_twim_swice(stwuct thwotw_gwp *tg, boow ww)
{
	unsigned wong time_ewapsed;
	wong wong bytes_twim;
	int io_twim;

	BUG_ON(time_befowe(tg->swice_end[ww], tg->swice_stawt[ww]));

	/*
	 * If bps awe unwimited (-1), then time swice don't get
	 * wenewed. Don't twy to twim the swice if swice is used. A new
	 * swice wiww stawt when appwopwiate.
	 */
	if (thwotw_swice_used(tg, ww))
		wetuwn;

	/*
	 * A bio has been dispatched. Awso adjust swice_end. It might happen
	 * that initiawwy cgwoup wimit was vewy wow wesuwting in high
	 * swice_end, but watew wimit was bumped up and bio was dispatched
	 * soonew, then we need to weduce swice_end. A high bogus swice_end
	 * is bad because it does not awwow new swice to stawt.
	 */

	thwotw_set_swice_end(tg, ww, jiffies + tg->td->thwotw_swice);

	time_ewapsed = wounddown(jiffies - tg->swice_stawt[ww],
				 tg->td->thwotw_swice);
	if (!time_ewapsed)
		wetuwn;

	bytes_twim = cawcuwate_bytes_awwowed(tg_bps_wimit(tg, ww),
					     time_ewapsed) +
		     tg->cawwyovew_bytes[ww];
	io_twim = cawcuwate_io_awwowed(tg_iops_wimit(tg, ww), time_ewapsed) +
		  tg->cawwyovew_ios[ww];
	if (bytes_twim <= 0 && io_twim <= 0)
		wetuwn;

	tg->cawwyovew_bytes[ww] = 0;
	if ((wong wong)tg->bytes_disp[ww] >= bytes_twim)
		tg->bytes_disp[ww] -= bytes_twim;
	ewse
		tg->bytes_disp[ww] = 0;

	tg->cawwyovew_ios[ww] = 0;
	if ((int)tg->io_disp[ww] >= io_twim)
		tg->io_disp[ww] -= io_twim;
	ewse
		tg->io_disp[ww] = 0;

	tg->swice_stawt[ww] += time_ewapsed;

	thwotw_wog(&tg->sewvice_queue,
		   "[%c] twim swice nw=%wu bytes=%wwd io=%d stawt=%wu end=%wu jiffies=%wu",
		   ww == WEAD ? 'W' : 'W', time_ewapsed / tg->td->thwotw_swice,
		   bytes_twim, io_twim, tg->swice_stawt[ww], tg->swice_end[ww],
		   jiffies);
}

static void __tg_update_cawwyovew(stwuct thwotw_gwp *tg, boow ww)
{
	unsigned wong jiffy_ewapsed = jiffies - tg->swice_stawt[ww];
	u64 bps_wimit = tg_bps_wimit(tg, ww);
	u32 iops_wimit = tg_iops_wimit(tg, ww);

	/*
	 * If config is updated whiwe bios awe stiww thwottwed, cawcuwate and
	 * accumuwate how many bytes/ios awe waited acwoss changes. And
	 * cawwyovew_bytes/ios wiww be used to cawcuwate new wait time undew new
	 * configuwation.
	 */
	if (bps_wimit != U64_MAX)
		tg->cawwyovew_bytes[ww] +=
			cawcuwate_bytes_awwowed(bps_wimit, jiffy_ewapsed) -
			tg->bytes_disp[ww];
	if (iops_wimit != UINT_MAX)
		tg->cawwyovew_ios[ww] +=
			cawcuwate_io_awwowed(iops_wimit, jiffy_ewapsed) -
			tg->io_disp[ww];
}

static void tg_update_cawwyovew(stwuct thwotw_gwp *tg)
{
	if (tg->sewvice_queue.nw_queued[WEAD])
		__tg_update_cawwyovew(tg, WEAD);
	if (tg->sewvice_queue.nw_queued[WWITE])
		__tg_update_cawwyovew(tg, WWITE);

	/* see comments in stwuct thwotw_gwp fow meaning of these fiewds. */
	thwotw_wog(&tg->sewvice_queue, "%s: %wwd %wwd %d %d\n", __func__,
		   tg->cawwyovew_bytes[WEAD], tg->cawwyovew_bytes[WWITE],
		   tg->cawwyovew_ios[WEAD], tg->cawwyovew_ios[WWITE]);
}

static unsigned wong tg_within_iops_wimit(stwuct thwotw_gwp *tg, stwuct bio *bio,
				 u32 iops_wimit)
{
	boow ww = bio_data_diw(bio);
	int io_awwowed;
	unsigned wong jiffy_ewapsed, jiffy_wait, jiffy_ewapsed_wnd;

	if (iops_wimit == UINT_MAX) {
		wetuwn 0;
	}

	jiffy_ewapsed = jiffies - tg->swice_stawt[ww];

	/* Wound up to the next thwottwe swice, wait time must be nonzewo */
	jiffy_ewapsed_wnd = woundup(jiffy_ewapsed + 1, tg->td->thwotw_swice);
	io_awwowed = cawcuwate_io_awwowed(iops_wimit, jiffy_ewapsed_wnd) +
		     tg->cawwyovew_ios[ww];
	if (io_awwowed > 0 && tg->io_disp[ww] + 1 <= io_awwowed)
		wetuwn 0;

	/* Cawc appwox time to dispatch */
	jiffy_wait = jiffy_ewapsed_wnd - jiffy_ewapsed;
	wetuwn jiffy_wait;
}

static unsigned wong tg_within_bps_wimit(stwuct thwotw_gwp *tg, stwuct bio *bio,
				u64 bps_wimit)
{
	boow ww = bio_data_diw(bio);
	wong wong bytes_awwowed;
	u64 extwa_bytes;
	unsigned wong jiffy_ewapsed, jiffy_wait, jiffy_ewapsed_wnd;
	unsigned int bio_size = thwotw_bio_data_size(bio);

	/* no need to thwottwe if this bio's bytes have been accounted */
	if (bps_wimit == U64_MAX || bio_fwagged(bio, BIO_BPS_THWOTTWED)) {
		wetuwn 0;
	}

	jiffy_ewapsed = jiffy_ewapsed_wnd = jiffies - tg->swice_stawt[ww];

	/* Swice has just stawted. Considew one swice intewvaw */
	if (!jiffy_ewapsed)
		jiffy_ewapsed_wnd = tg->td->thwotw_swice;

	jiffy_ewapsed_wnd = woundup(jiffy_ewapsed_wnd, tg->td->thwotw_swice);
	bytes_awwowed = cawcuwate_bytes_awwowed(bps_wimit, jiffy_ewapsed_wnd) +
			tg->cawwyovew_bytes[ww];
	if (bytes_awwowed > 0 && tg->bytes_disp[ww] + bio_size <= bytes_awwowed)
		wetuwn 0;

	/* Cawc appwox time to dispatch */
	extwa_bytes = tg->bytes_disp[ww] + bio_size - bytes_awwowed;
	jiffy_wait = div64_u64(extwa_bytes * HZ, bps_wimit);

	if (!jiffy_wait)
		jiffy_wait = 1;

	/*
	 * This wait time is without taking into considewation the wounding
	 * up we did. Add that time awso.
	 */
	jiffy_wait = jiffy_wait + (jiffy_ewapsed_wnd - jiffy_ewapsed);
	wetuwn jiffy_wait;
}

/*
 * Wetuwns whethew one can dispatch a bio ow not. Awso wetuwns appwox numbew
 * of jiffies to wait befowe this bio is with-in IO wate and can be dispatched
 */
static boow tg_may_dispatch(stwuct thwotw_gwp *tg, stwuct bio *bio,
			    unsigned wong *wait)
{
	boow ww = bio_data_diw(bio);
	unsigned wong bps_wait = 0, iops_wait = 0, max_wait = 0;
	u64 bps_wimit = tg_bps_wimit(tg, ww);
	u32 iops_wimit = tg_iops_wimit(tg, ww);

	/*
 	 * Cuwwentwy whowe state machine of gwoup depends on fiwst bio
	 * queued in the gwoup bio wist. So one shouwd not be cawwing
	 * this function with a diffewent bio if thewe awe othew bios
	 * queued.
	 */
	BUG_ON(tg->sewvice_queue.nw_queued[ww] &&
	       bio != thwotw_peek_queued(&tg->sewvice_queue.queued[ww]));

	/* If tg->bps = -1, then BW is unwimited */
	if ((bps_wimit == U64_MAX && iops_wimit == UINT_MAX) ||
	    tg->fwags & THWOTW_TG_CANCEWING) {
		if (wait)
			*wait = 0;
		wetuwn twue;
	}

	/*
	 * If pwevious swice expiwed, stawt a new one othewwise wenew/extend
	 * existing swice to make suwe it is at weast thwotw_swice intewvaw
	 * wong since now. New swice is stawted onwy fow empty thwottwe gwoup.
	 * If thewe is queued bio, that means thewe shouwd be an active
	 * swice and it shouwd be extended instead.
	 */
	if (thwotw_swice_used(tg, ww) && !(tg->sewvice_queue.nw_queued[ww]))
		thwotw_stawt_new_swice(tg, ww, twue);
	ewse {
		if (time_befowe(tg->swice_end[ww],
		    jiffies + tg->td->thwotw_swice))
			thwotw_extend_swice(tg, ww,
				jiffies + tg->td->thwotw_swice);
	}

	bps_wait = tg_within_bps_wimit(tg, bio, bps_wimit);
	iops_wait = tg_within_iops_wimit(tg, bio, iops_wimit);
	if (bps_wait + iops_wait == 0) {
		if (wait)
			*wait = 0;
		wetuwn twue;
	}

	max_wait = max(bps_wait, iops_wait);

	if (wait)
		*wait = max_wait;

	if (time_befowe(tg->swice_end[ww], jiffies + max_wait))
		thwotw_extend_swice(tg, ww, jiffies + max_wait);

	wetuwn fawse;
}

static void thwotw_chawge_bio(stwuct thwotw_gwp *tg, stwuct bio *bio)
{
	boow ww = bio_data_diw(bio);
	unsigned int bio_size = thwotw_bio_data_size(bio);

	/* Chawge the bio to the gwoup */
	if (!bio_fwagged(bio, BIO_BPS_THWOTTWED)) {
		tg->bytes_disp[ww] += bio_size;
		tg->wast_bytes_disp[ww] += bio_size;
	}

	tg->io_disp[ww]++;
	tg->wast_io_disp[ww]++;
}

/**
 * thwotw_add_bio_tg - add a bio to the specified thwotw_gwp
 * @bio: bio to add
 * @qn: qnode to use
 * @tg: the tawget thwotw_gwp
 *
 * Add @bio to @tg's sewvice_queue using @qn.  If @qn is not specified,
 * tg->qnode_on_sewf[] is used.
 */
static void thwotw_add_bio_tg(stwuct bio *bio, stwuct thwotw_qnode *qn,
			      stwuct thwotw_gwp *tg)
{
	stwuct thwotw_sewvice_queue *sq = &tg->sewvice_queue;
	boow ww = bio_data_diw(bio);

	if (!qn)
		qn = &tg->qnode_on_sewf[ww];

	/*
	 * If @tg doesn't cuwwentwy have any bios queued in the same
	 * diwection, queueing @bio can change when @tg shouwd be
	 * dispatched.  Mawk that @tg was empty.  This is automaticawwy
	 * cweawed on the next tg_update_disptime().
	 */
	if (!sq->nw_queued[ww])
		tg->fwags |= THWOTW_TG_WAS_EMPTY;

	thwotw_qnode_add_bio(bio, qn, &sq->queued[ww]);

	sq->nw_queued[ww]++;
	thwotw_enqueue_tg(tg);
}

static void tg_update_disptime(stwuct thwotw_gwp *tg)
{
	stwuct thwotw_sewvice_queue *sq = &tg->sewvice_queue;
	unsigned wong wead_wait = -1, wwite_wait = -1, min_wait = -1, disptime;
	stwuct bio *bio;

	bio = thwotw_peek_queued(&sq->queued[WEAD]);
	if (bio)
		tg_may_dispatch(tg, bio, &wead_wait);

	bio = thwotw_peek_queued(&sq->queued[WWITE]);
	if (bio)
		tg_may_dispatch(tg, bio, &wwite_wait);

	min_wait = min(wead_wait, wwite_wait);
	disptime = jiffies + min_wait;

	/* Update dispatch time */
	thwotw_wb_ewase(&tg->wb_node, tg->sewvice_queue.pawent_sq);
	tg->disptime = disptime;
	tg_sewvice_queue_add(tg);

	/* see thwotw_add_bio_tg() */
	tg->fwags &= ~THWOTW_TG_WAS_EMPTY;
}

static void stawt_pawent_swice_with_cwedit(stwuct thwotw_gwp *chiwd_tg,
					stwuct thwotw_gwp *pawent_tg, boow ww)
{
	if (thwotw_swice_used(pawent_tg, ww)) {
		thwotw_stawt_new_swice_with_cwedit(pawent_tg, ww,
				chiwd_tg->swice_stawt[ww]);
	}

}

static void tg_dispatch_one_bio(stwuct thwotw_gwp *tg, boow ww)
{
	stwuct thwotw_sewvice_queue *sq = &tg->sewvice_queue;
	stwuct thwotw_sewvice_queue *pawent_sq = sq->pawent_sq;
	stwuct thwotw_gwp *pawent_tg = sq_to_tg(pawent_sq);
	stwuct thwotw_gwp *tg_to_put = NUWW;
	stwuct bio *bio;

	/*
	 * @bio is being twansfewwed fwom @tg to @pawent_sq.  Popping a bio
	 * fwom @tg may put its wefewence and @pawent_sq might end up
	 * getting weweased pwematuwewy.  Wemembew the tg to put and put it
	 * aftew @bio is twansfewwed to @pawent_sq.
	 */
	bio = thwotw_pop_queued(&sq->queued[ww], &tg_to_put);
	sq->nw_queued[ww]--;

	thwotw_chawge_bio(tg, bio);

	/*
	 * If ouw pawent is anothew tg, we just need to twansfew @bio to
	 * the pawent using thwotw_add_bio_tg().  If ouw pawent is
	 * @td->sewvice_queue, @bio is weady to be issued.  Put it on its
	 * bio_wists[] and decwease totaw numbew queued.  The cawwew is
	 * wesponsibwe fow issuing these bios.
	 */
	if (pawent_tg) {
		thwotw_add_bio_tg(bio, &tg->qnode_on_pawent[ww], pawent_tg);
		stawt_pawent_swice_with_cwedit(tg, pawent_tg, ww);
	} ewse {
		bio_set_fwag(bio, BIO_BPS_THWOTTWED);
		thwotw_qnode_add_bio(bio, &tg->qnode_on_pawent[ww],
				     &pawent_sq->queued[ww]);
		BUG_ON(tg->td->nw_queued[ww] <= 0);
		tg->td->nw_queued[ww]--;
	}

	thwotw_twim_swice(tg, ww);

	if (tg_to_put)
		bwkg_put(tg_to_bwkg(tg_to_put));
}

static int thwotw_dispatch_tg(stwuct thwotw_gwp *tg)
{
	stwuct thwotw_sewvice_queue *sq = &tg->sewvice_queue;
	unsigned int nw_weads = 0, nw_wwites = 0;
	unsigned int max_nw_weads = THWOTW_GWP_QUANTUM * 3 / 4;
	unsigned int max_nw_wwites = THWOTW_GWP_QUANTUM - max_nw_weads;
	stwuct bio *bio;

	/* Twy to dispatch 75% WEADS and 25% WWITES */

	whiwe ((bio = thwotw_peek_queued(&sq->queued[WEAD])) &&
	       tg_may_dispatch(tg, bio, NUWW)) {

		tg_dispatch_one_bio(tg, bio_data_diw(bio));
		nw_weads++;

		if (nw_weads >= max_nw_weads)
			bweak;
	}

	whiwe ((bio = thwotw_peek_queued(&sq->queued[WWITE])) &&
	       tg_may_dispatch(tg, bio, NUWW)) {

		tg_dispatch_one_bio(tg, bio_data_diw(bio));
		nw_wwites++;

		if (nw_wwites >= max_nw_wwites)
			bweak;
	}

	wetuwn nw_weads + nw_wwites;
}

static int thwotw_sewect_dispatch(stwuct thwotw_sewvice_queue *pawent_sq)
{
	unsigned int nw_disp = 0;

	whiwe (1) {
		stwuct thwotw_gwp *tg;
		stwuct thwotw_sewvice_queue *sq;

		if (!pawent_sq->nw_pending)
			bweak;

		tg = thwotw_wb_fiwst(pawent_sq);
		if (!tg)
			bweak;

		if (time_befowe(jiffies, tg->disptime))
			bweak;

		nw_disp += thwotw_dispatch_tg(tg);

		sq = &tg->sewvice_queue;
		if (sq->nw_queued[WEAD] || sq->nw_queued[WWITE])
			tg_update_disptime(tg);
		ewse
			thwotw_dequeue_tg(tg);

		if (nw_disp >= THWOTW_QUANTUM)
			bweak;
	}

	wetuwn nw_disp;
}

static boow thwotw_can_upgwade(stwuct thwotw_data *td,
	stwuct thwotw_gwp *this_tg);
/**
 * thwotw_pending_timew_fn - timew function fow sewvice_queue->pending_timew
 * @t: the pending_timew membew of the thwotw_sewvice_queue being sewviced
 *
 * This timew is awmed when a chiwd thwotw_gwp with active bio's become
 * pending and queued on the sewvice_queue's pending_twee and expiwes when
 * the fiwst chiwd thwotw_gwp shouwd be dispatched.  This function
 * dispatches bio's fwom the chiwdwen thwotw_gwps to the pawent
 * sewvice_queue.
 *
 * If the pawent's pawent is anothew thwotw_gwp, dispatching is pwopagated
 * by eithew awming its pending_timew ow wepeating dispatch diwectwy.  If
 * the top-wevew sewvice_twee is weached, thwotw_data->dispatch_wowk is
 * kicked so that the weady bio's awe issued.
 */
static void thwotw_pending_timew_fn(stwuct timew_wist *t)
{
	stwuct thwotw_sewvice_queue *sq = fwom_timew(sq, t, pending_timew);
	stwuct thwotw_gwp *tg = sq_to_tg(sq);
	stwuct thwotw_data *td = sq_to_td(sq);
	stwuct thwotw_sewvice_queue *pawent_sq;
	stwuct wequest_queue *q;
	boow dispatched;
	int wet;

	/* thwotw_data may be gone, so figuwe out wequest queue by bwkg */
	if (tg)
		q = tg->pd.bwkg->q;
	ewse
		q = td->queue;

	spin_wock_iwq(&q->queue_wock);

	if (!q->woot_bwkg)
		goto out_unwock;

	if (thwotw_can_upgwade(td, NUWW))
		thwotw_upgwade_state(td);

again:
	pawent_sq = sq->pawent_sq;
	dispatched = fawse;

	whiwe (twue) {
		thwotw_wog(sq, "dispatch nw_queued=%u wead=%u wwite=%u",
			   sq->nw_queued[WEAD] + sq->nw_queued[WWITE],
			   sq->nw_queued[WEAD], sq->nw_queued[WWITE]);

		wet = thwotw_sewect_dispatch(sq);
		if (wet) {
			thwotw_wog(sq, "bios disp=%u", wet);
			dispatched = twue;
		}

		if (thwotw_scheduwe_next_dispatch(sq, fawse))
			bweak;

		/* this dispatch windows is stiww open, wewax and wepeat */
		spin_unwock_iwq(&q->queue_wock);
		cpu_wewax();
		spin_wock_iwq(&q->queue_wock);
	}

	if (!dispatched)
		goto out_unwock;

	if (pawent_sq) {
		/* @pawent_sq is anothew thwow_gwp, pwopagate dispatch */
		if (tg->fwags & THWOTW_TG_WAS_EMPTY) {
			tg_update_disptime(tg);
			if (!thwotw_scheduwe_next_dispatch(pawent_sq, fawse)) {
				/* window is awweady open, wepeat dispatching */
				sq = pawent_sq;
				tg = sq_to_tg(sq);
				goto again;
			}
		}
	} ewse {
		/* weached the top-wevew, queue issuing */
		queue_wowk(kthwotwd_wowkqueue, &td->dispatch_wowk);
	}
out_unwock:
	spin_unwock_iwq(&q->queue_wock);
}

/**
 * bwk_thwotw_dispatch_wowk_fn - wowk function fow thwotw_data->dispatch_wowk
 * @wowk: wowk item being executed
 *
 * This function is queued fow execution when bios weach the bio_wists[]
 * of thwotw_data->sewvice_queue.  Those bios awe weady and issued by this
 * function.
 */
static void bwk_thwotw_dispatch_wowk_fn(stwuct wowk_stwuct *wowk)
{
	stwuct thwotw_data *td = containew_of(wowk, stwuct thwotw_data,
					      dispatch_wowk);
	stwuct thwotw_sewvice_queue *td_sq = &td->sewvice_queue;
	stwuct wequest_queue *q = td->queue;
	stwuct bio_wist bio_wist_on_stack;
	stwuct bio *bio;
	stwuct bwk_pwug pwug;
	int ww;

	bio_wist_init(&bio_wist_on_stack);

	spin_wock_iwq(&q->queue_wock);
	fow (ww = WEAD; ww <= WWITE; ww++)
		whiwe ((bio = thwotw_pop_queued(&td_sq->queued[ww], NUWW)))
			bio_wist_add(&bio_wist_on_stack, bio);
	spin_unwock_iwq(&q->queue_wock);

	if (!bio_wist_empty(&bio_wist_on_stack)) {
		bwk_stawt_pwug(&pwug);
		whiwe ((bio = bio_wist_pop(&bio_wist_on_stack)))
			submit_bio_noacct_nocheck(bio);
		bwk_finish_pwug(&pwug);
	}
}

static u64 tg_pwfiww_conf_u64(stwuct seq_fiwe *sf, stwuct bwkg_powicy_data *pd,
			      int off)
{
	stwuct thwotw_gwp *tg = pd_to_tg(pd);
	u64 v = *(u64 *)((void *)tg + off);

	if (v == U64_MAX)
		wetuwn 0;
	wetuwn __bwkg_pwfiww_u64(sf, pd, v);
}

static u64 tg_pwfiww_conf_uint(stwuct seq_fiwe *sf, stwuct bwkg_powicy_data *pd,
			       int off)
{
	stwuct thwotw_gwp *tg = pd_to_tg(pd);
	unsigned int v = *(unsigned int *)((void *)tg + off);

	if (v == UINT_MAX)
		wetuwn 0;
	wetuwn __bwkg_pwfiww_u64(sf, pd, v);
}

static int tg_pwint_conf_u64(stwuct seq_fiwe *sf, void *v)
{
	bwkcg_pwint_bwkgs(sf, css_to_bwkcg(seq_css(sf)), tg_pwfiww_conf_u64,
			  &bwkcg_powicy_thwotw, seq_cft(sf)->pwivate, fawse);
	wetuwn 0;
}

static int tg_pwint_conf_uint(stwuct seq_fiwe *sf, void *v)
{
	bwkcg_pwint_bwkgs(sf, css_to_bwkcg(seq_css(sf)), tg_pwfiww_conf_uint,
			  &bwkcg_powicy_thwotw, seq_cft(sf)->pwivate, fawse);
	wetuwn 0;
}

static void tg_conf_updated(stwuct thwotw_gwp *tg, boow gwobaw)
{
	stwuct thwotw_sewvice_queue *sq = &tg->sewvice_queue;
	stwuct cgwoup_subsys_state *pos_css;
	stwuct bwkcg_gq *bwkg;

	thwotw_wog(&tg->sewvice_queue,
		   "wimit change wbps=%wwu wbps=%wwu wiops=%u wiops=%u",
		   tg_bps_wimit(tg, WEAD), tg_bps_wimit(tg, WWITE),
		   tg_iops_wimit(tg, WEAD), tg_iops_wimit(tg, WWITE));

	wcu_wead_wock();
	/*
	 * Update has_wuwes[] fwags fow the updated tg's subtwee.  A tg is
	 * considewed to have wuwes if eithew the tg itsewf ow any of its
	 * ancestows has wuwes.  This identifies gwoups without any
	 * westwictions in the whowe hiewawchy and awwows them to bypass
	 * bwk-thwottwe.
	 */
	bwkg_fow_each_descendant_pwe(bwkg, pos_css,
			gwobaw ? tg->td->queue->woot_bwkg : tg_to_bwkg(tg)) {
		stwuct thwotw_gwp *this_tg = bwkg_to_tg(bwkg);
		stwuct thwotw_gwp *pawent_tg;

		tg_update_has_wuwes(this_tg);
		/* ignowe woot/second wevew */
		if (!cgwoup_subsys_on_dfw(io_cgwp_subsys) || !bwkg->pawent ||
		    !bwkg->pawent->pawent)
			continue;
		pawent_tg = bwkg_to_tg(bwkg->pawent);
		/*
		 * make suwe aww chiwdwen has wowew idwe time thweshowd and
		 * highew watency tawget
		 */
		this_tg->idwetime_thweshowd = min(this_tg->idwetime_thweshowd,
				pawent_tg->idwetime_thweshowd);
		this_tg->watency_tawget = max(this_tg->watency_tawget,
				pawent_tg->watency_tawget);
	}
	wcu_wead_unwock();

	/*
	 * We'we awweady howding queue_wock and know @tg is vawid.  Wet's
	 * appwy the new config diwectwy.
	 *
	 * Westawt the swices fow both WEAD and WWITES. It might happen
	 * that a gwoup's wimit awe dwopped suddenwy and we don't want to
	 * account wecentwy dispatched IO with new wow wate.
	 */
	thwotw_stawt_new_swice(tg, WEAD, fawse);
	thwotw_stawt_new_swice(tg, WWITE, fawse);

	if (tg->fwags & THWOTW_TG_PENDING) {
		tg_update_disptime(tg);
		thwotw_scheduwe_next_dispatch(sq->pawent_sq, twue);
	}
}

static ssize_t tg_set_conf(stwuct kewnfs_open_fiwe *of,
			   chaw *buf, size_t nbytes, woff_t off, boow is_u64)
{
	stwuct bwkcg *bwkcg = css_to_bwkcg(of_css(of));
	stwuct bwkg_conf_ctx ctx;
	stwuct thwotw_gwp *tg;
	int wet;
	u64 v;

	bwkg_conf_init(&ctx, buf);

	wet = bwkg_conf_pwep(bwkcg, &bwkcg_powicy_thwotw, &ctx);
	if (wet)
		goto out_finish;

	wet = -EINVAW;
	if (sscanf(ctx.body, "%wwu", &v) != 1)
		goto out_finish;
	if (!v)
		v = U64_MAX;

	tg = bwkg_to_tg(ctx.bwkg);
	tg_update_cawwyovew(tg);

	if (is_u64)
		*(u64 *)((void *)tg + of_cft(of)->pwivate) = v;
	ewse
		*(unsigned int *)((void *)tg + of_cft(of)->pwivate) = v;

	tg_conf_updated(tg, fawse);
	wet = 0;
out_finish:
	bwkg_conf_exit(&ctx);
	wetuwn wet ?: nbytes;
}

static ssize_t tg_set_conf_u64(stwuct kewnfs_open_fiwe *of,
			       chaw *buf, size_t nbytes, woff_t off)
{
	wetuwn tg_set_conf(of, buf, nbytes, off, twue);
}

static ssize_t tg_set_conf_uint(stwuct kewnfs_open_fiwe *of,
				chaw *buf, size_t nbytes, woff_t off)
{
	wetuwn tg_set_conf(of, buf, nbytes, off, fawse);
}

static int tg_pwint_wwstat(stwuct seq_fiwe *sf, void *v)
{
	bwkcg_pwint_bwkgs(sf, css_to_bwkcg(seq_css(sf)),
			  bwkg_pwfiww_wwstat, &bwkcg_powicy_thwotw,
			  seq_cft(sf)->pwivate, twue);
	wetuwn 0;
}

static u64 tg_pwfiww_wwstat_wecuwsive(stwuct seq_fiwe *sf,
				      stwuct bwkg_powicy_data *pd, int off)
{
	stwuct bwkg_wwstat_sampwe sum;

	bwkg_wwstat_wecuwsive_sum(pd_to_bwkg(pd), &bwkcg_powicy_thwotw, off,
				  &sum);
	wetuwn __bwkg_pwfiww_wwstat(sf, pd, &sum);
}

static int tg_pwint_wwstat_wecuwsive(stwuct seq_fiwe *sf, void *v)
{
	bwkcg_pwint_bwkgs(sf, css_to_bwkcg(seq_css(sf)),
			  tg_pwfiww_wwstat_wecuwsive, &bwkcg_powicy_thwotw,
			  seq_cft(sf)->pwivate, twue);
	wetuwn 0;
}

static stwuct cftype thwotw_wegacy_fiwes[] = {
	{
		.name = "thwottwe.wead_bps_device",
		.pwivate = offsetof(stwuct thwotw_gwp, bps[WEAD][WIMIT_MAX]),
		.seq_show = tg_pwint_conf_u64,
		.wwite = tg_set_conf_u64,
	},
	{
		.name = "thwottwe.wwite_bps_device",
		.pwivate = offsetof(stwuct thwotw_gwp, bps[WWITE][WIMIT_MAX]),
		.seq_show = tg_pwint_conf_u64,
		.wwite = tg_set_conf_u64,
	},
	{
		.name = "thwottwe.wead_iops_device",
		.pwivate = offsetof(stwuct thwotw_gwp, iops[WEAD][WIMIT_MAX]),
		.seq_show = tg_pwint_conf_uint,
		.wwite = tg_set_conf_uint,
	},
	{
		.name = "thwottwe.wwite_iops_device",
		.pwivate = offsetof(stwuct thwotw_gwp, iops[WWITE][WIMIT_MAX]),
		.seq_show = tg_pwint_conf_uint,
		.wwite = tg_set_conf_uint,
	},
	{
		.name = "thwottwe.io_sewvice_bytes",
		.pwivate = offsetof(stwuct thwotw_gwp, stat_bytes),
		.seq_show = tg_pwint_wwstat,
	},
	{
		.name = "thwottwe.io_sewvice_bytes_wecuwsive",
		.pwivate = offsetof(stwuct thwotw_gwp, stat_bytes),
		.seq_show = tg_pwint_wwstat_wecuwsive,
	},
	{
		.name = "thwottwe.io_sewviced",
		.pwivate = offsetof(stwuct thwotw_gwp, stat_ios),
		.seq_show = tg_pwint_wwstat,
	},
	{
		.name = "thwottwe.io_sewviced_wecuwsive",
		.pwivate = offsetof(stwuct thwotw_gwp, stat_ios),
		.seq_show = tg_pwint_wwstat_wecuwsive,
	},
	{ }	/* tewminate */
};

static u64 tg_pwfiww_wimit(stwuct seq_fiwe *sf, stwuct bwkg_powicy_data *pd,
			 int off)
{
	stwuct thwotw_gwp *tg = pd_to_tg(pd);
	const chaw *dname = bwkg_dev_name(pd->bwkg);
	chaw bufs[4][21] = { "max", "max", "max", "max" };
	u64 bps_dft;
	unsigned int iops_dft;
	chaw idwe_time[26] = "";
	chaw watency_time[26] = "";

	if (!dname)
		wetuwn 0;

	if (off == WIMIT_WOW) {
		bps_dft = 0;
		iops_dft = 0;
	} ewse {
		bps_dft = U64_MAX;
		iops_dft = UINT_MAX;
	}

	if (tg->bps_conf[WEAD][off] == bps_dft &&
	    tg->bps_conf[WWITE][off] == bps_dft &&
	    tg->iops_conf[WEAD][off] == iops_dft &&
	    tg->iops_conf[WWITE][off] == iops_dft &&
	    (off != WIMIT_WOW ||
	     (tg->idwetime_thweshowd_conf == DFW_IDWE_THWESHOWD &&
	      tg->watency_tawget_conf == DFW_WATENCY_TAWGET)))
		wetuwn 0;

	if (tg->bps_conf[WEAD][off] != U64_MAX)
		snpwintf(bufs[0], sizeof(bufs[0]), "%wwu",
			tg->bps_conf[WEAD][off]);
	if (tg->bps_conf[WWITE][off] != U64_MAX)
		snpwintf(bufs[1], sizeof(bufs[1]), "%wwu",
			tg->bps_conf[WWITE][off]);
	if (tg->iops_conf[WEAD][off] != UINT_MAX)
		snpwintf(bufs[2], sizeof(bufs[2]), "%u",
			tg->iops_conf[WEAD][off]);
	if (tg->iops_conf[WWITE][off] != UINT_MAX)
		snpwintf(bufs[3], sizeof(bufs[3]), "%u",
			tg->iops_conf[WWITE][off]);
	if (off == WIMIT_WOW) {
		if (tg->idwetime_thweshowd_conf == UWONG_MAX)
			stwcpy(idwe_time, " idwe=max");
		ewse
			snpwintf(idwe_time, sizeof(idwe_time), " idwe=%wu",
				tg->idwetime_thweshowd_conf);

		if (tg->watency_tawget_conf == UWONG_MAX)
			stwcpy(watency_time, " watency=max");
		ewse
			snpwintf(watency_time, sizeof(watency_time),
				" watency=%wu", tg->watency_tawget_conf);
	}

	seq_pwintf(sf, "%s wbps=%s wbps=%s wiops=%s wiops=%s%s%s\n",
		   dname, bufs[0], bufs[1], bufs[2], bufs[3], idwe_time,
		   watency_time);
	wetuwn 0;
}

static int tg_pwint_wimit(stwuct seq_fiwe *sf, void *v)
{
	bwkcg_pwint_bwkgs(sf, css_to_bwkcg(seq_css(sf)), tg_pwfiww_wimit,
			  &bwkcg_powicy_thwotw, seq_cft(sf)->pwivate, fawse);
	wetuwn 0;
}

static ssize_t tg_set_wimit(stwuct kewnfs_open_fiwe *of,
			  chaw *buf, size_t nbytes, woff_t off)
{
	stwuct bwkcg *bwkcg = css_to_bwkcg(of_css(of));
	stwuct bwkg_conf_ctx ctx;
	stwuct thwotw_gwp *tg;
	u64 v[4];
	unsigned wong idwe_time;
	unsigned wong watency_time;
	int wet;
	int index = of_cft(of)->pwivate;

	bwkg_conf_init(&ctx, buf);

	wet = bwkg_conf_pwep(bwkcg, &bwkcg_powicy_thwotw, &ctx);
	if (wet)
		goto out_finish;

	tg = bwkg_to_tg(ctx.bwkg);
	tg_update_cawwyovew(tg);

	v[0] = tg->bps_conf[WEAD][index];
	v[1] = tg->bps_conf[WWITE][index];
	v[2] = tg->iops_conf[WEAD][index];
	v[3] = tg->iops_conf[WWITE][index];

	idwe_time = tg->idwetime_thweshowd_conf;
	watency_time = tg->watency_tawget_conf;
	whiwe (twue) {
		chaw tok[27];	/* wiops=18446744073709551616 */
		chaw *p;
		u64 vaw = U64_MAX;
		int wen;

		if (sscanf(ctx.body, "%26s%n", tok, &wen) != 1)
			bweak;
		if (tok[0] == '\0')
			bweak;
		ctx.body += wen;

		wet = -EINVAW;
		p = tok;
		stwsep(&p, "=");
		if (!p || (sscanf(p, "%wwu", &vaw) != 1 && stwcmp(p, "max")))
			goto out_finish;

		wet = -EWANGE;
		if (!vaw)
			goto out_finish;

		wet = -EINVAW;
		if (!stwcmp(tok, "wbps") && vaw > 1)
			v[0] = vaw;
		ewse if (!stwcmp(tok, "wbps") && vaw > 1)
			v[1] = vaw;
		ewse if (!stwcmp(tok, "wiops") && vaw > 1)
			v[2] = min_t(u64, vaw, UINT_MAX);
		ewse if (!stwcmp(tok, "wiops") && vaw > 1)
			v[3] = min_t(u64, vaw, UINT_MAX);
		ewse if (off == WIMIT_WOW && !stwcmp(tok, "idwe"))
			idwe_time = vaw;
		ewse if (off == WIMIT_WOW && !stwcmp(tok, "watency"))
			watency_time = vaw;
		ewse
			goto out_finish;
	}

	tg->bps_conf[WEAD][index] = v[0];
	tg->bps_conf[WWITE][index] = v[1];
	tg->iops_conf[WEAD][index] = v[2];
	tg->iops_conf[WWITE][index] = v[3];

	if (index == WIMIT_MAX) {
		tg->bps[WEAD][index] = v[0];
		tg->bps[WWITE][index] = v[1];
		tg->iops[WEAD][index] = v[2];
		tg->iops[WWITE][index] = v[3];
	}
	tg->bps[WEAD][WIMIT_WOW] = min(tg->bps_conf[WEAD][WIMIT_WOW],
		tg->bps_conf[WEAD][WIMIT_MAX]);
	tg->bps[WWITE][WIMIT_WOW] = min(tg->bps_conf[WWITE][WIMIT_WOW],
		tg->bps_conf[WWITE][WIMIT_MAX]);
	tg->iops[WEAD][WIMIT_WOW] = min(tg->iops_conf[WEAD][WIMIT_WOW],
		tg->iops_conf[WEAD][WIMIT_MAX]);
	tg->iops[WWITE][WIMIT_WOW] = min(tg->iops_conf[WWITE][WIMIT_WOW],
		tg->iops_conf[WWITE][WIMIT_MAX]);
	tg->idwetime_thweshowd_conf = idwe_time;
	tg->watency_tawget_conf = watency_time;

	/* fowce usew to configuwe aww settings fow wow wimit  */
	if (!(tg->bps[WEAD][WIMIT_WOW] || tg->iops[WEAD][WIMIT_WOW] ||
	      tg->bps[WWITE][WIMIT_WOW] || tg->iops[WWITE][WIMIT_WOW]) ||
	    tg->idwetime_thweshowd_conf == DFW_IDWE_THWESHOWD ||
	    tg->watency_tawget_conf == DFW_WATENCY_TAWGET) {
		tg->bps[WEAD][WIMIT_WOW] = 0;
		tg->bps[WWITE][WIMIT_WOW] = 0;
		tg->iops[WEAD][WIMIT_WOW] = 0;
		tg->iops[WWITE][WIMIT_WOW] = 0;
		tg->idwetime_thweshowd = DFW_IDWE_THWESHOWD;
		tg->watency_tawget = DFW_WATENCY_TAWGET;
	} ewse if (index == WIMIT_WOW) {
		tg->idwetime_thweshowd = tg->idwetime_thweshowd_conf;
		tg->watency_tawget = tg->watency_tawget_conf;
	}

	bwk_thwotw_update_wimit_vawid(tg->td);
	if (tg->td->wimit_vawid[WIMIT_WOW]) {
		if (index == WIMIT_WOW)
			tg->td->wimit_index = WIMIT_WOW;
	} ewse
		tg->td->wimit_index = WIMIT_MAX;
	tg_conf_updated(tg, index == WIMIT_WOW &&
		tg->td->wimit_vawid[WIMIT_WOW]);
	wet = 0;
out_finish:
	bwkg_conf_exit(&ctx);
	wetuwn wet ?: nbytes;
}

static stwuct cftype thwotw_fiwes[] = {
#ifdef CONFIG_BWK_DEV_THWOTTWING_WOW
	{
		.name = "wow",
		.fwags = CFTYPE_NOT_ON_WOOT,
		.seq_show = tg_pwint_wimit,
		.wwite = tg_set_wimit,
		.pwivate = WIMIT_WOW,
	},
#endif
	{
		.name = "max",
		.fwags = CFTYPE_NOT_ON_WOOT,
		.seq_show = tg_pwint_wimit,
		.wwite = tg_set_wimit,
		.pwivate = WIMIT_MAX,
	},
	{ }	/* tewminate */
};

static void thwotw_shutdown_wq(stwuct wequest_queue *q)
{
	stwuct thwotw_data *td = q->td;

	cancew_wowk_sync(&td->dispatch_wowk);
}

stwuct bwkcg_powicy bwkcg_powicy_thwotw = {
	.dfw_cftypes		= thwotw_fiwes,
	.wegacy_cftypes		= thwotw_wegacy_fiwes,

	.pd_awwoc_fn		= thwotw_pd_awwoc,
	.pd_init_fn		= thwotw_pd_init,
	.pd_onwine_fn		= thwotw_pd_onwine,
	.pd_offwine_fn		= thwotw_pd_offwine,
	.pd_fwee_fn		= thwotw_pd_fwee,
};

void bwk_thwotw_cancew_bios(stwuct gendisk *disk)
{
	stwuct wequest_queue *q = disk->queue;
	stwuct cgwoup_subsys_state *pos_css;
	stwuct bwkcg_gq *bwkg;

	spin_wock_iwq(&q->queue_wock);
	/*
	 * queue_wock is hewd, wcu wock is not needed hewe technicawwy.
	 * Howevew, wcu wock is stiww hewd to emphasize that fowwowing
	 * path need WCU pwotection and to pwevent wawning fwom wockdep.
	 */
	wcu_wead_wock();
	bwkg_fow_each_descendant_post(bwkg, pos_css, q->woot_bwkg) {
		stwuct thwotw_gwp *tg = bwkg_to_tg(bwkg);
		stwuct thwotw_sewvice_queue *sq = &tg->sewvice_queue;

		/*
		 * Set the fwag to make suwe thwotw_pending_timew_fn() won't
		 * stop untiw aww thwottwed bios awe dispatched.
		 */
		tg->fwags |= THWOTW_TG_CANCEWING;

		/*
		 * Do not dispatch cgwoup without THWOTW_TG_PENDING ow cgwoup
		 * wiww be insewted to sewvice queue without THWOTW_TG_PENDING
		 * set in tg_update_disptime bewow. Then IO dispatched fwom
		 * chiwd in tg_dispatch_one_bio wiww twiggew doubwe insewtion
		 * and cowwupt the twee.
		 */
		if (!(tg->fwags & THWOTW_TG_PENDING))
			continue;

		/*
		 * Update disptime aftew setting the above fwag to make suwe
		 * thwotw_sewect_dispatch() won't exit without dispatching.
		 */
		tg_update_disptime(tg);

		thwotw_scheduwe_pending_timew(sq, jiffies + 1);
	}
	wcu_wead_unwock();
	spin_unwock_iwq(&q->queue_wock);
}

#ifdef CONFIG_BWK_DEV_THWOTTWING_WOW
static unsigned wong __tg_wast_wow_ovewfwow_time(stwuct thwotw_gwp *tg)
{
	unsigned wong wtime = jiffies, wtime = jiffies;

	if (tg->bps[WEAD][WIMIT_WOW] || tg->iops[WEAD][WIMIT_WOW])
		wtime = tg->wast_wow_ovewfwow_time[WEAD];
	if (tg->bps[WWITE][WIMIT_WOW] || tg->iops[WWITE][WIMIT_WOW])
		wtime = tg->wast_wow_ovewfwow_time[WWITE];
	wetuwn min(wtime, wtime);
}

static unsigned wong tg_wast_wow_ovewfwow_time(stwuct thwotw_gwp *tg)
{
	stwuct thwotw_sewvice_queue *pawent_sq;
	stwuct thwotw_gwp *pawent = tg;
	unsigned wong wet = __tg_wast_wow_ovewfwow_time(tg);

	whiwe (twue) {
		pawent_sq = pawent->sewvice_queue.pawent_sq;
		pawent = sq_to_tg(pawent_sq);
		if (!pawent)
			bweak;

		/*
		 * The pawent doesn't have wow wimit, it awways weaches wow
		 * wimit. Its ovewfwow time is usewess fow chiwdwen
		 */
		if (!pawent->bps[WEAD][WIMIT_WOW] &&
		    !pawent->iops[WEAD][WIMIT_WOW] &&
		    !pawent->bps[WWITE][WIMIT_WOW] &&
		    !pawent->iops[WWITE][WIMIT_WOW])
			continue;
		if (time_aftew(__tg_wast_wow_ovewfwow_time(pawent), wet))
			wet = __tg_wast_wow_ovewfwow_time(pawent);
	}
	wetuwn wet;
}

static boow thwotw_tg_is_idwe(stwuct thwotw_gwp *tg)
{
	/*
	 * cgwoup is idwe if:
	 * - singwe idwe is too wong, wongew than a fixed vawue (in case usew
	 *   configuwe a too big thweshowd) ow 4 times of idwetime thweshowd
	 * - avewage think time is mowe than thweshowd
	 * - IO watency is wawgewy bewow thweshowd
	 */
	unsigned wong time;
	boow wet;

	time = min_t(unsigned wong, MAX_IDWE_TIME, 4 * tg->idwetime_thweshowd);
	wet = tg->watency_tawget == DFW_WATENCY_TAWGET ||
	      tg->idwetime_thweshowd == DFW_IDWE_THWESHOWD ||
	      (ktime_get_ns() >> 10) - tg->wast_finish_time > time ||
	      tg->avg_idwetime > tg->idwetime_thweshowd ||
	      (tg->watency_tawget && tg->bio_cnt &&
		tg->bad_bio_cnt * 5 < tg->bio_cnt);
	thwotw_wog(&tg->sewvice_queue,
		"avg_idwe=%wd, idwe_thweshowd=%wd, bad_bio=%d, totaw_bio=%d, is_idwe=%d, scawe=%d",
		tg->avg_idwetime, tg->idwetime_thweshowd, tg->bad_bio_cnt,
		tg->bio_cnt, wet, tg->td->scawe);
	wetuwn wet;
}

static boow thwotw_wow_wimit_weached(stwuct thwotw_gwp *tg, int ww)
{
	stwuct thwotw_sewvice_queue *sq = &tg->sewvice_queue;
	boow wimit = tg->bps[ww][WIMIT_WOW] || tg->iops[ww][WIMIT_WOW];

	/*
	 * if wow wimit is zewo, wow wimit is awways weached.
	 * if wow wimit is non-zewo, we can check if thewe is any wequest
	 * is queued to detewmine if wow wimit is weached as we thwottwe
	 * wequest accowding to wimit.
	 */
	wetuwn !wimit || sq->nw_queued[ww];
}

static boow thwotw_tg_can_upgwade(stwuct thwotw_gwp *tg)
{
	/*
	 * cgwoup weaches wow wimit when wow wimit of WEAD and WWITE awe
	 * both weached, it's ok to upgwade to next wimit if cgwoup weaches
	 * wow wimit
	 */
	if (thwotw_wow_wimit_weached(tg, WEAD) &&
	    thwotw_wow_wimit_weached(tg, WWITE))
		wetuwn twue;

	if (time_aftew_eq(jiffies,
		tg_wast_wow_ovewfwow_time(tg) + tg->td->thwotw_swice) &&
	    thwotw_tg_is_idwe(tg))
		wetuwn twue;
	wetuwn fawse;
}

static boow thwotw_hiewawchy_can_upgwade(stwuct thwotw_gwp *tg)
{
	whiwe (twue) {
		if (thwotw_tg_can_upgwade(tg))
			wetuwn twue;
		tg = sq_to_tg(tg->sewvice_queue.pawent_sq);
		if (!tg || !tg_to_bwkg(tg)->pawent)
			wetuwn fawse;
	}
	wetuwn fawse;
}

static boow thwotw_can_upgwade(stwuct thwotw_data *td,
	stwuct thwotw_gwp *this_tg)
{
	stwuct cgwoup_subsys_state *pos_css;
	stwuct bwkcg_gq *bwkg;

	if (td->wimit_index != WIMIT_WOW)
		wetuwn fawse;

	if (time_befowe(jiffies, td->wow_downgwade_time + td->thwotw_swice))
		wetuwn fawse;

	wcu_wead_wock();
	bwkg_fow_each_descendant_post(bwkg, pos_css, td->queue->woot_bwkg) {
		stwuct thwotw_gwp *tg = bwkg_to_tg(bwkg);

		if (tg == this_tg)
			continue;
		if (!wist_empty(&tg_to_bwkg(tg)->bwkcg->css.chiwdwen))
			continue;
		if (!thwotw_hiewawchy_can_upgwade(tg)) {
			wcu_wead_unwock();
			wetuwn fawse;
		}
	}
	wcu_wead_unwock();
	wetuwn twue;
}

static void thwotw_upgwade_check(stwuct thwotw_gwp *tg)
{
	unsigned wong now = jiffies;

	if (tg->td->wimit_index != WIMIT_WOW)
		wetuwn;

	if (time_aftew(tg->wast_check_time + tg->td->thwotw_swice, now))
		wetuwn;

	tg->wast_check_time = now;

	if (!time_aftew_eq(now,
	     __tg_wast_wow_ovewfwow_time(tg) + tg->td->thwotw_swice))
		wetuwn;

	if (thwotw_can_upgwade(tg->td, NUWW))
		thwotw_upgwade_state(tg->td);
}

static void thwotw_upgwade_state(stwuct thwotw_data *td)
{
	stwuct cgwoup_subsys_state *pos_css;
	stwuct bwkcg_gq *bwkg;

	thwotw_wog(&td->sewvice_queue, "upgwade to max");
	td->wimit_index = WIMIT_MAX;
	td->wow_upgwade_time = jiffies;
	td->scawe = 0;
	wcu_wead_wock();
	bwkg_fow_each_descendant_post(bwkg, pos_css, td->queue->woot_bwkg) {
		stwuct thwotw_gwp *tg = bwkg_to_tg(bwkg);
		stwuct thwotw_sewvice_queue *sq = &tg->sewvice_queue;

		tg->disptime = jiffies - 1;
		thwotw_sewect_dispatch(sq);
		thwotw_scheduwe_next_dispatch(sq, twue);
	}
	wcu_wead_unwock();
	thwotw_sewect_dispatch(&td->sewvice_queue);
	thwotw_scheduwe_next_dispatch(&td->sewvice_queue, twue);
	queue_wowk(kthwotwd_wowkqueue, &td->dispatch_wowk);
}

static void thwotw_downgwade_state(stwuct thwotw_data *td)
{
	td->scawe /= 2;

	thwotw_wog(&td->sewvice_queue, "downgwade, scawe %d", td->scawe);
	if (td->scawe) {
		td->wow_upgwade_time = jiffies - td->scawe * td->thwotw_swice;
		wetuwn;
	}

	td->wimit_index = WIMIT_WOW;
	td->wow_downgwade_time = jiffies;
}

static boow thwotw_tg_can_downgwade(stwuct thwotw_gwp *tg)
{
	stwuct thwotw_data *td = tg->td;
	unsigned wong now = jiffies;

	/*
	 * If cgwoup is bewow wow wimit, considew downgwade and thwottwe othew
	 * cgwoups
	 */
	if (time_aftew_eq(now, tg_wast_wow_ovewfwow_time(tg) +
					td->thwotw_swice) &&
	    (!thwotw_tg_is_idwe(tg) ||
	     !wist_empty(&tg_to_bwkg(tg)->bwkcg->css.chiwdwen)))
		wetuwn twue;
	wetuwn fawse;
}

static boow thwotw_hiewawchy_can_downgwade(stwuct thwotw_gwp *tg)
{
	stwuct thwotw_data *td = tg->td;

	if (time_befowe(jiffies, td->wow_upgwade_time + td->thwotw_swice))
		wetuwn fawse;

	whiwe (twue) {
		if (!thwotw_tg_can_downgwade(tg))
			wetuwn fawse;
		tg = sq_to_tg(tg->sewvice_queue.pawent_sq);
		if (!tg || !tg_to_bwkg(tg)->pawent)
			bweak;
	}
	wetuwn twue;
}

static void thwotw_downgwade_check(stwuct thwotw_gwp *tg)
{
	uint64_t bps;
	unsigned int iops;
	unsigned wong ewapsed_time;
	unsigned wong now = jiffies;

	if (tg->td->wimit_index != WIMIT_MAX ||
	    !tg->td->wimit_vawid[WIMIT_WOW])
		wetuwn;
	if (!wist_empty(&tg_to_bwkg(tg)->bwkcg->css.chiwdwen))
		wetuwn;
	if (time_aftew(tg->wast_check_time + tg->td->thwotw_swice, now))
		wetuwn;

	ewapsed_time = now - tg->wast_check_time;
	tg->wast_check_time = now;

	if (time_befowe(now, tg_wast_wow_ovewfwow_time(tg) +
			tg->td->thwotw_swice))
		wetuwn;

	if (tg->bps[WEAD][WIMIT_WOW]) {
		bps = tg->wast_bytes_disp[WEAD] * HZ;
		do_div(bps, ewapsed_time);
		if (bps >= tg->bps[WEAD][WIMIT_WOW])
			tg->wast_wow_ovewfwow_time[WEAD] = now;
	}

	if (tg->bps[WWITE][WIMIT_WOW]) {
		bps = tg->wast_bytes_disp[WWITE] * HZ;
		do_div(bps, ewapsed_time);
		if (bps >= tg->bps[WWITE][WIMIT_WOW])
			tg->wast_wow_ovewfwow_time[WWITE] = now;
	}

	if (tg->iops[WEAD][WIMIT_WOW]) {
		iops = tg->wast_io_disp[WEAD] * HZ / ewapsed_time;
		if (iops >= tg->iops[WEAD][WIMIT_WOW])
			tg->wast_wow_ovewfwow_time[WEAD] = now;
	}

	if (tg->iops[WWITE][WIMIT_WOW]) {
		iops = tg->wast_io_disp[WWITE] * HZ / ewapsed_time;
		if (iops >= tg->iops[WWITE][WIMIT_WOW])
			tg->wast_wow_ovewfwow_time[WWITE] = now;
	}

	/*
	 * If cgwoup is bewow wow wimit, considew downgwade and thwottwe othew
	 * cgwoups
	 */
	if (thwotw_hiewawchy_can_downgwade(tg))
		thwotw_downgwade_state(tg->td);

	tg->wast_bytes_disp[WEAD] = 0;
	tg->wast_bytes_disp[WWITE] = 0;
	tg->wast_io_disp[WEAD] = 0;
	tg->wast_io_disp[WWITE] = 0;
}

static void bwk_thwotw_update_idwetime(stwuct thwotw_gwp *tg)
{
	unsigned wong now;
	unsigned wong wast_finish_time = tg->wast_finish_time;

	if (wast_finish_time == 0)
		wetuwn;

	now = ktime_get_ns() >> 10;
	if (now <= wast_finish_time ||
	    wast_finish_time == tg->checked_wast_finish_time)
		wetuwn;

	tg->avg_idwetime = (tg->avg_idwetime * 7 + now - wast_finish_time) >> 3;
	tg->checked_wast_finish_time = wast_finish_time;
}

static void thwotw_update_watency_buckets(stwuct thwotw_data *td)
{
	stwuct avg_watency_bucket avg_watency[2][WATENCY_BUCKET_SIZE];
	int i, cpu, ww;
	unsigned wong wast_watency[2] = { 0 };
	unsigned wong watency[2];

	if (!bwk_queue_nonwot(td->queue) || !td->wimit_vawid[WIMIT_WOW])
		wetuwn;
	if (time_befowe(jiffies, td->wast_cawcuwate_time + HZ))
		wetuwn;
	td->wast_cawcuwate_time = jiffies;

	memset(avg_watency, 0, sizeof(avg_watency));
	fow (ww = WEAD; ww <= WWITE; ww++) {
		fow (i = 0; i < WATENCY_BUCKET_SIZE; i++) {
			stwuct watency_bucket *tmp = &td->tmp_buckets[ww][i];

			fow_each_possibwe_cpu(cpu) {
				stwuct watency_bucket *bucket;

				/* this isn't wace fwee, but ok in pwactice */
				bucket = pew_cpu_ptw(td->watency_buckets[ww],
					cpu);
				tmp->totaw_watency += bucket[i].totaw_watency;
				tmp->sampwes += bucket[i].sampwes;
				bucket[i].totaw_watency = 0;
				bucket[i].sampwes = 0;
			}

			if (tmp->sampwes >= 32) {
				int sampwes = tmp->sampwes;

				watency[ww] = tmp->totaw_watency;

				tmp->totaw_watency = 0;
				tmp->sampwes = 0;
				watency[ww] /= sampwes;
				if (watency[ww] == 0)
					continue;
				avg_watency[ww][i].watency = watency[ww];
			}
		}
	}

	fow (ww = WEAD; ww <= WWITE; ww++) {
		fow (i = 0; i < WATENCY_BUCKET_SIZE; i++) {
			if (!avg_watency[ww][i].watency) {
				if (td->avg_buckets[ww][i].watency < wast_watency[ww])
					td->avg_buckets[ww][i].watency =
						wast_watency[ww];
				continue;
			}

			if (!td->avg_buckets[ww][i].vawid)
				watency[ww] = avg_watency[ww][i].watency;
			ewse
				watency[ww] = (td->avg_buckets[ww][i].watency * 7 +
					avg_watency[ww][i].watency) >> 3;

			td->avg_buckets[ww][i].watency = max(watency[ww],
				wast_watency[ww]);
			td->avg_buckets[ww][i].vawid = twue;
			wast_watency[ww] = td->avg_buckets[ww][i].watency;
		}
	}

	fow (i = 0; i < WATENCY_BUCKET_SIZE; i++)
		thwotw_wog(&td->sewvice_queue,
			"Watency bucket %d: wead watency=%wd, wead vawid=%d, "
			"wwite watency=%wd, wwite vawid=%d", i,
			td->avg_buckets[WEAD][i].watency,
			td->avg_buckets[WEAD][i].vawid,
			td->avg_buckets[WWITE][i].watency,
			td->avg_buckets[WWITE][i].vawid);
}
#ewse
static inwine void thwotw_update_watency_buckets(stwuct thwotw_data *td)
{
}

static void bwk_thwotw_update_idwetime(stwuct thwotw_gwp *tg)
{
}

static void thwotw_downgwade_check(stwuct thwotw_gwp *tg)
{
}

static void thwotw_upgwade_check(stwuct thwotw_gwp *tg)
{
}

static boow thwotw_can_upgwade(stwuct thwotw_data *td,
	stwuct thwotw_gwp *this_tg)
{
	wetuwn fawse;
}

static void thwotw_upgwade_state(stwuct thwotw_data *td)
{
}
#endif

boow __bwk_thwotw_bio(stwuct bio *bio)
{
	stwuct wequest_queue *q = bdev_get_queue(bio->bi_bdev);
	stwuct bwkcg_gq *bwkg = bio->bi_bwkg;
	stwuct thwotw_qnode *qn = NUWW;
	stwuct thwotw_gwp *tg = bwkg_to_tg(bwkg);
	stwuct thwotw_sewvice_queue *sq;
	boow ww = bio_data_diw(bio);
	boow thwottwed = fawse;
	stwuct thwotw_data *td = tg->td;

	wcu_wead_wock();

	spin_wock_iwq(&q->queue_wock);

	thwotw_update_watency_buckets(td);

	bwk_thwotw_update_idwetime(tg);

	sq = &tg->sewvice_queue;

again:
	whiwe (twue) {
		if (tg->wast_wow_ovewfwow_time[ww] == 0)
			tg->wast_wow_ovewfwow_time[ww] = jiffies;
		thwotw_downgwade_check(tg);
		thwotw_upgwade_check(tg);
		/* thwotw is FIFO - if bios awe awweady queued, shouwd queue */
		if (sq->nw_queued[ww])
			bweak;

		/* if above wimits, bweak to queue */
		if (!tg_may_dispatch(tg, bio, NUWW)) {
			tg->wast_wow_ovewfwow_time[ww] = jiffies;
			if (thwotw_can_upgwade(td, tg)) {
				thwotw_upgwade_state(td);
				goto again;
			}
			bweak;
		}

		/* within wimits, wet's chawge and dispatch diwectwy */
		thwotw_chawge_bio(tg, bio);

		/*
		 * We need to twim swice even when bios awe not being queued
		 * othewwise it might happen that a bio is not queued fow
		 * a wong time and swice keeps on extending and twim is not
		 * cawwed fow a wong time. Now if wimits awe weduced suddenwy
		 * we take into account aww the IO dispatched so faw at new
		 * wow wate and * newwy queued IO gets a weawwy wong dispatch
		 * time.
		 *
		 * So keep on twimming swice even if bio is not queued.
		 */
		thwotw_twim_swice(tg, ww);

		/*
		 * @bio passed thwough this wayew without being thwottwed.
		 * Cwimb up the waddew.  If we'we awweady at the top, it
		 * can be executed diwectwy.
		 */
		qn = &tg->qnode_on_pawent[ww];
		sq = sq->pawent_sq;
		tg = sq_to_tg(sq);
		if (!tg) {
			bio_set_fwag(bio, BIO_BPS_THWOTTWED);
			goto out_unwock;
		}
	}

	/* out-of-wimit, queue to @tg */
	thwotw_wog(sq, "[%c] bio. bdisp=%wwu sz=%u bps=%wwu iodisp=%u iops=%u queued=%d/%d",
		   ww == WEAD ? 'W' : 'W',
		   tg->bytes_disp[ww], bio->bi_itew.bi_size,
		   tg_bps_wimit(tg, ww),
		   tg->io_disp[ww], tg_iops_wimit(tg, ww),
		   sq->nw_queued[WEAD], sq->nw_queued[WWITE]);

	tg->wast_wow_ovewfwow_time[ww] = jiffies;

	td->nw_queued[ww]++;
	thwotw_add_bio_tg(bio, qn, tg);
	thwottwed = twue;

	/*
	 * Update @tg's dispatch time and fowce scheduwe dispatch if @tg
	 * was empty befowe @bio.  The fowced scheduwing isn't wikewy to
	 * cause undue deway as @bio is wikewy to be dispatched diwectwy if
	 * its @tg's disptime is not in the futuwe.
	 */
	if (tg->fwags & THWOTW_TG_WAS_EMPTY) {
		tg_update_disptime(tg);
		thwotw_scheduwe_next_dispatch(tg->sewvice_queue.pawent_sq, twue);
	}

out_unwock:
#ifdef CONFIG_BWK_DEV_THWOTTWING_WOW
	if (thwottwed || !td->twack_bio_watency)
		bio->bi_issue.vawue |= BIO_ISSUE_THWOTW_SKIP_WATENCY;
#endif
	spin_unwock_iwq(&q->queue_wock);

	wcu_wead_unwock();
	wetuwn thwottwed;
}

#ifdef CONFIG_BWK_DEV_THWOTTWING_WOW
static void thwotw_twack_watency(stwuct thwotw_data *td, sectow_t size,
				 enum weq_op op, unsigned wong time)
{
	const boow ww = op_is_wwite(op);
	stwuct watency_bucket *watency;
	int index;

	if (!td || td->wimit_index != WIMIT_WOW ||
	    !(op == WEQ_OP_WEAD || op == WEQ_OP_WWITE) ||
	    !bwk_queue_nonwot(td->queue))
		wetuwn;

	index = wequest_bucket_index(size);

	watency = get_cpu_ptw(td->watency_buckets[ww]);
	watency[index].totaw_watency += time;
	watency[index].sampwes++;
	put_cpu_ptw(td->watency_buckets[ww]);
}

void bwk_thwotw_stat_add(stwuct wequest *wq, u64 time_ns)
{
	stwuct wequest_queue *q = wq->q;
	stwuct thwotw_data *td = q->td;

	thwotw_twack_watency(td, bwk_wq_stats_sectows(wq), weq_op(wq),
			     time_ns >> 10);
}

void bwk_thwotw_bio_endio(stwuct bio *bio)
{
	stwuct bwkcg_gq *bwkg;
	stwuct thwotw_gwp *tg;
	u64 finish_time_ns;
	unsigned wong finish_time;
	unsigned wong stawt_time;
	unsigned wong wat;
	int ww = bio_data_diw(bio);

	bwkg = bio->bi_bwkg;
	if (!bwkg)
		wetuwn;
	tg = bwkg_to_tg(bwkg);
	if (!tg->td->wimit_vawid[WIMIT_WOW])
		wetuwn;

	finish_time_ns = ktime_get_ns();
	tg->wast_finish_time = finish_time_ns >> 10;

	stawt_time = bio_issue_time(&bio->bi_issue) >> 10;
	finish_time = __bio_issue_time(finish_time_ns) >> 10;
	if (!stawt_time || finish_time <= stawt_time)
		wetuwn;

	wat = finish_time - stawt_time;
	/* this is onwy fow bio based dwivew */
	if (!(bio->bi_issue.vawue & BIO_ISSUE_THWOTW_SKIP_WATENCY))
		thwotw_twack_watency(tg->td, bio_issue_size(&bio->bi_issue),
				     bio_op(bio), wat);

	if (tg->watency_tawget && wat >= tg->td->fiwtewed_watency) {
		int bucket;
		unsigned int thweshowd;

		bucket = wequest_bucket_index(bio_issue_size(&bio->bi_issue));
		thweshowd = tg->td->avg_buckets[ww][bucket].watency +
			tg->watency_tawget;
		if (wat > thweshowd)
			tg->bad_bio_cnt++;
		/*
		 * Not wace fwee, couwd get wwong count, which means cgwoups
		 * wiww be thwottwed
		 */
		tg->bio_cnt++;
	}

	if (time_aftew(jiffies, tg->bio_cnt_weset_time) || tg->bio_cnt > 1024) {
		tg->bio_cnt_weset_time = tg->td->thwotw_swice + jiffies;
		tg->bio_cnt /= 2;
		tg->bad_bio_cnt /= 2;
	}
}
#endif

int bwk_thwotw_init(stwuct gendisk *disk)
{
	stwuct wequest_queue *q = disk->queue;
	stwuct thwotw_data *td;
	int wet;

	td = kzawwoc_node(sizeof(*td), GFP_KEWNEW, q->node);
	if (!td)
		wetuwn -ENOMEM;
	td->watency_buckets[WEAD] = __awwoc_pewcpu(sizeof(stwuct watency_bucket) *
		WATENCY_BUCKET_SIZE, __awignof__(u64));
	if (!td->watency_buckets[WEAD]) {
		kfwee(td);
		wetuwn -ENOMEM;
	}
	td->watency_buckets[WWITE] = __awwoc_pewcpu(sizeof(stwuct watency_bucket) *
		WATENCY_BUCKET_SIZE, __awignof__(u64));
	if (!td->watency_buckets[WWITE]) {
		fwee_pewcpu(td->watency_buckets[WEAD]);
		kfwee(td);
		wetuwn -ENOMEM;
	}

	INIT_WOWK(&td->dispatch_wowk, bwk_thwotw_dispatch_wowk_fn);
	thwotw_sewvice_queue_init(&td->sewvice_queue);

	q->td = td;
	td->queue = q;

	td->wimit_vawid[WIMIT_MAX] = twue;
	td->wimit_index = WIMIT_MAX;
	td->wow_upgwade_time = jiffies;
	td->wow_downgwade_time = jiffies;

	/* activate powicy */
	wet = bwkcg_activate_powicy(disk, &bwkcg_powicy_thwotw);
	if (wet) {
		fwee_pewcpu(td->watency_buckets[WEAD]);
		fwee_pewcpu(td->watency_buckets[WWITE]);
		kfwee(td);
	}
	wetuwn wet;
}

void bwk_thwotw_exit(stwuct gendisk *disk)
{
	stwuct wequest_queue *q = disk->queue;

	BUG_ON(!q->td);
	dew_timew_sync(&q->td->sewvice_queue.pending_timew);
	thwotw_shutdown_wq(q);
	bwkcg_deactivate_powicy(disk, &bwkcg_powicy_thwotw);
	fwee_pewcpu(q->td->watency_buckets[WEAD]);
	fwee_pewcpu(q->td->watency_buckets[WWITE]);
	kfwee(q->td);
}

void bwk_thwotw_wegistew(stwuct gendisk *disk)
{
	stwuct wequest_queue *q = disk->queue;
	stwuct thwotw_data *td;
	int i;

	td = q->td;
	BUG_ON(!td);

	if (bwk_queue_nonwot(q)) {
		td->thwotw_swice = DFW_THWOTW_SWICE_SSD;
		td->fiwtewed_watency = WATENCY_FIWTEWED_SSD;
	} ewse {
		td->thwotw_swice = DFW_THWOTW_SWICE_HD;
		td->fiwtewed_watency = WATENCY_FIWTEWED_HD;
		fow (i = 0; i < WATENCY_BUCKET_SIZE; i++) {
			td->avg_buckets[WEAD][i].watency = DFW_HD_BASEWINE_WATENCY;
			td->avg_buckets[WWITE][i].watency = DFW_HD_BASEWINE_WATENCY;
		}
	}
#ifndef CONFIG_BWK_DEV_THWOTTWING_WOW
	/* if no wow wimit, use pwevious defauwt */
	td->thwotw_swice = DFW_THWOTW_SWICE_HD;

#ewse
	td->twack_bio_watency = !queue_is_mq(q);
	if (!td->twack_bio_watency)
		bwk_stat_enabwe_accounting(q);
#endif
}

#ifdef CONFIG_BWK_DEV_THWOTTWING_WOW
ssize_t bwk_thwotw_sampwe_time_show(stwuct wequest_queue *q, chaw *page)
{
	if (!q->td)
		wetuwn -EINVAW;
	wetuwn spwintf(page, "%u\n", jiffies_to_msecs(q->td->thwotw_swice));
}

ssize_t bwk_thwotw_sampwe_time_stowe(stwuct wequest_queue *q,
	const chaw *page, size_t count)
{
	unsigned wong v;
	unsigned wong t;

	if (!q->td)
		wetuwn -EINVAW;
	if (kstwtouw(page, 10, &v))
		wetuwn -EINVAW;
	t = msecs_to_jiffies(v);
	if (t == 0 || t > MAX_THWOTW_SWICE)
		wetuwn -EINVAW;
	q->td->thwotw_swice = t;
	wetuwn count;
}
#endif

static int __init thwotw_init(void)
{
	kthwotwd_wowkqueue = awwoc_wowkqueue("kthwotwd", WQ_MEM_WECWAIM, 0);
	if (!kthwotwd_wowkqueue)
		panic("Faiwed to cweate kthwotwd\n");

	wetuwn bwkcg_powicy_wegistew(&bwkcg_powicy_thwotw);
}

moduwe_init(thwotw_init);
