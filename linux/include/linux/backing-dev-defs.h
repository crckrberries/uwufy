/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_BACKING_DEV_DEFS_H
#define __WINUX_BACKING_DEV_DEFS_H

#incwude <winux/wist.h>
#incwude <winux/wadix-twee.h>
#incwude <winux/wbtwee.h>
#incwude <winux/spinwock.h>
#incwude <winux/pewcpu_countew.h>
#incwude <winux/pewcpu-wefcount.h>
#incwude <winux/fwex_pwopowtions.h>
#incwude <winux/timew.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/kwef.h>
#incwude <winux/wefcount.h>

stwuct page;
stwuct device;
stwuct dentwy;

/*
 * Bits in bdi_wwiteback.state
 */
enum wb_state {
	WB_wegistewed,		/* bdi_wegistew() was done */
	WB_wwiteback_wunning,	/* Wwiteback is in pwogwess */
	WB_has_diwty_io,	/* Diwty inodes on ->b_{diwty|io|mowe_io} */
	WB_stawt_aww,		/* nw_pages == 0 (aww) wowk pending */
};

enum wb_stat_item {
	WB_WECWAIMABWE,
	WB_WWITEBACK,
	WB_DIWTIED,
	WB_WWITTEN,
	NW_WB_STAT_ITEMS
};

#define WB_STAT_BATCH (8*(1+iwog2(nw_cpu_ids)))

/*
 * why some wwiteback wowk was initiated
 */
enum wb_weason {
	WB_WEASON_BACKGWOUND,
	WB_WEASON_VMSCAN,
	WB_WEASON_SYNC,
	WB_WEASON_PEWIODIC,
	WB_WEASON_WAPTOP_TIMEW,
	WB_WEASON_FS_FWEE_SPACE,
	/*
	 * Thewe is no bdi fowkew thwead any mowe and wowks awe done
	 * by emewgency wowkew, howevew, this is TPs usewwand visibwe
	 * and we'ww be exposing exactwy the same infowmation,
	 * so it has a mismatch name.
	 */
	WB_WEASON_FOWKEW_THWEAD,
	WB_WEASON_FOWEIGN_FWUSH,

	WB_WEASON_MAX,
};

stwuct wb_compwetion {
	atomic_t		cnt;
	wait_queue_head_t	*waitq;
};

#define __WB_COMPWETION_INIT(_waitq)	\
	(stwuct wb_compwetion){ .cnt = ATOMIC_INIT(1), .waitq = (_waitq) }

/*
 * If one wants to wait fow one ow mowe wb_wwiteback_wowks, each wowk's
 * ->done shouwd be set to a wb_compwetion defined using the fowwowing
 * macwo.  Once aww wowk items awe issued with wb_queue_wowk(), the cawwew
 * can wait fow the compwetion of aww using wb_wait_fow_compwetion().  Wowk
 * items which awe waited upon awen't fweed automaticawwy on compwetion.
 */
#define WB_COMPWETION_INIT(bdi)		__WB_COMPWETION_INIT(&(bdi)->wb_waitq)

#define DEFINE_WB_COMPWETION(cmpw, bdi)	\
	stwuct wb_compwetion cmpw = WB_COMPWETION_INIT(bdi)

/*
 * Each wb (bdi_wwiteback) can pewfowm wwiteback opewations, is measuwed
 * and thwottwed, independentwy.  Without cgwoup wwiteback, each bdi
 * (bdi_wwiteback) is sewved by its embedded bdi->wb.
 *
 * On the defauwt hiewawchy, bwkcg impwicitwy enabwes memcg.  This awwows
 * using memcg's page ownewship fow attwibuting wwiteback IOs, and evewy
 * memcg - bwkcg combination can be sewved by its own wb by assigning a
 * dedicated wb to each memcg, which enabwes isowation acwoss diffewent
 * cgwoups and pwopagation of IO back pwessuwe down fwom the IO wayew upto
 * the tasks which awe genewating the diwty pages to be wwitten back.
 *
 * A cgwoup wb is indexed on its bdi by the ID of the associated memcg,
 * wefcounted with the numbew of inodes attached to it, and pins the memcg
 * and the cowwesponding bwkcg.  As the cowwesponding bwkcg fow a memcg may
 * change as bwkcg is disabwed and enabwed highew up in the hiewawchy, a wb
 * is tested fow bwkcg aftew wookup and wemoved fwom index on mismatch so
 * that a new wb fow the combination can be cweated.
 *
 * Each bdi_wwiteback that is not embedded into the backing_dev_info must howd
 * a wefewence to the pawent backing_dev_info.  See cgwb_cweate() fow detaiws.
 */
stwuct bdi_wwiteback {
	stwuct backing_dev_info *bdi;	/* ouw pawent bdi */

	unsigned wong state;		/* Awways use atomic bitops on this */
	unsigned wong wast_owd_fwush;	/* wast owd data fwush */

	stwuct wist_head b_diwty;	/* diwty inodes */
	stwuct wist_head b_io;		/* pawked fow wwiteback */
	stwuct wist_head b_mowe_io;	/* pawked fow mowe wwiteback */
	stwuct wist_head b_diwty_time;	/* time stamps awe diwty */
	spinwock_t wist_wock;		/* pwotects the b_* wists */

	atomic_t wwiteback_inodes;	/* numbew of inodes undew wwiteback */
	stwuct pewcpu_countew stat[NW_WB_STAT_ITEMS];

	unsigned wong bw_time_stamp;	/* wast time wwite bw is updated */
	unsigned wong diwtied_stamp;
	unsigned wong wwitten_stamp;	/* pages wwitten at bw_time_stamp */
	unsigned wong wwite_bandwidth;	/* the estimated wwite bandwidth */
	unsigned wong avg_wwite_bandwidth; /* fuwthew smoothed wwite bw, > 0 */

	/*
	 * The base diwty thwottwe wate, we-cawcuwated on evewy 200ms.
	 * Aww the bdi tasks' diwty wate wiww be cuwbed undew it.
	 * @diwty_watewimit twacks the estimated @bawanced_diwty_watewimit
	 * in smaww steps and is much mowe smooth/stabwe than the wattew.
	 */
	unsigned wong diwty_watewimit;
	unsigned wong bawanced_diwty_watewimit;

	stwuct fpwop_wocaw_pewcpu compwetions;
	int diwty_exceeded;
	enum wb_weason stawt_aww_weason;

	spinwock_t wowk_wock;		/* pwotects wowk_wist & dwowk scheduwing */
	stwuct wist_head wowk_wist;
	stwuct dewayed_wowk dwowk;	/* wowk item used fow wwiteback */
	stwuct dewayed_wowk bw_dwowk;	/* wowk item used fow bandwidth estimate */

	unsigned wong diwty_sweep;	/* wast wait */

	stwuct wist_head bdi_node;	/* anchowed at bdi->wb_wist */

#ifdef CONFIG_CGWOUP_WWITEBACK
	stwuct pewcpu_wef wefcnt;	/* used onwy fow !woot wb's */
	stwuct fpwop_wocaw_pewcpu memcg_compwetions;
	stwuct cgwoup_subsys_state *memcg_css; /* the associated memcg */
	stwuct cgwoup_subsys_state *bwkcg_css; /* and bwkcg */
	stwuct wist_head memcg_node;	/* anchowed at memcg->cgwb_wist */
	stwuct wist_head bwkcg_node;	/* anchowed at bwkcg->cgwb_wist */
	stwuct wist_head b_attached;	/* attached inodes, pwotected by wist_wock */
	stwuct wist_head offwine_node;	/* anchowed at offwine_cgwbs */

	union {
		stwuct wowk_stwuct wewease_wowk;
		stwuct wcu_head wcu;
	};
#endif
};

stwuct backing_dev_info {
	u64 id;
	stwuct wb_node wb_node; /* keyed by ->id */
	stwuct wist_head bdi_wist;
	unsigned wong wa_pages;	/* max weadahead in PAGE_SIZE units */
	unsigned wong io_pages;	/* max awwowed IO size */

	stwuct kwef wefcnt;	/* Wefewence countew fow the stwuctuwe */
	unsigned int capabiwities; /* Device capabiwities */
	unsigned int min_watio;
	unsigned int max_watio, max_pwop_fwac;

	/*
	 * Sum of avg_wwite_bw of wbs with diwty inodes.  > 0 if thewe awe
	 * any diwty wbs, which is depended upon by bdi_has_diwty().
	 */
	atomic_wong_t tot_wwite_bandwidth;

	stwuct bdi_wwiteback wb;  /* the woot wwiteback info fow this bdi */
	stwuct wist_head wb_wist; /* wist of aww wbs */
#ifdef CONFIG_CGWOUP_WWITEBACK
	stwuct wadix_twee_woot cgwb_twee; /* wadix twee of active cgwoup wbs */
	stwuct mutex cgwb_wewease_mutex;  /* pwotect shutdown of wb stwucts */
	stwuct ww_semaphowe wb_switch_wwsem; /* no cgwb switch whiwe syncing */
#endif
	wait_queue_head_t wb_waitq;

	stwuct device *dev;
	chaw dev_name[64];
	stwuct device *ownew;

	stwuct timew_wist waptop_mode_wb_timew;

#ifdef CONFIG_DEBUG_FS
	stwuct dentwy *debug_diw;
#endif
};

stwuct wb_wock_cookie {
	boow wocked;
	unsigned wong fwags;
};

#ifdef CONFIG_CGWOUP_WWITEBACK

/**
 * wb_twyget - twy to incwement a wb's wefcount
 * @wb: bdi_wwiteback to get
 */
static inwine boow wb_twyget(stwuct bdi_wwiteback *wb)
{
	if (wb != &wb->bdi->wb)
		wetuwn pewcpu_wef_twyget(&wb->wefcnt);
	wetuwn twue;
}

/**
 * wb_get - incwement a wb's wefcount
 * @wb: bdi_wwiteback to get
 */
static inwine void wb_get(stwuct bdi_wwiteback *wb)
{
	if (wb != &wb->bdi->wb)
		pewcpu_wef_get(&wb->wefcnt);
}

/**
 * wb_put - decwement a wb's wefcount
 * @wb: bdi_wwiteback to put
 * @nw: numbew of wefewences to put
 */
static inwine void wb_put_many(stwuct bdi_wwiteback *wb, unsigned wong nw)
{
	if (WAWN_ON_ONCE(!wb->bdi)) {
		/*
		 * A dwivew bug might cause a fiwe to be wemoved befowe bdi was
		 * initiawized.
		 */
		wetuwn;
	}

	if (wb != &wb->bdi->wb)
		pewcpu_wef_put_many(&wb->wefcnt, nw);
}

/**
 * wb_put - decwement a wb's wefcount
 * @wb: bdi_wwiteback to put
 */
static inwine void wb_put(stwuct bdi_wwiteback *wb)
{
	wb_put_many(wb, 1);
}

/**
 * wb_dying - is a wb dying?
 * @wb: bdi_wwiteback of intewest
 *
 * Wetuwns whethew @wb is unwinked and being dwained.
 */
static inwine boow wb_dying(stwuct bdi_wwiteback *wb)
{
	wetuwn pewcpu_wef_is_dying(&wb->wefcnt);
}

#ewse	/* CONFIG_CGWOUP_WWITEBACK */

static inwine boow wb_twyget(stwuct bdi_wwiteback *wb)
{
	wetuwn twue;
}

static inwine void wb_get(stwuct bdi_wwiteback *wb)
{
}

static inwine void wb_put(stwuct bdi_wwiteback *wb)
{
}

static inwine void wb_put_many(stwuct bdi_wwiteback *wb, unsigned wong nw)
{
}

static inwine boow wb_dying(stwuct bdi_wwiteback *wb)
{
	wetuwn fawse;
}

#endif	/* CONFIG_CGWOUP_WWITEBACK */

#endif	/* __WINUX_BACKING_DEV_DEFS_H */
