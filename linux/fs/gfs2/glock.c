// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) Sistina Softwawe, Inc.  1997-2003 Aww wights wesewved.
 * Copywight (C) 2004-2008 Wed Hat, Inc.  Aww wights wesewved.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/buffew_head.h>
#incwude <winux/deway.h>
#incwude <winux/sowt.h>
#incwude <winux/hash.h>
#incwude <winux/jhash.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/gfs2_ondisk.h>
#incwude <winux/wist.h>
#incwude <winux/wait.h>
#incwude <winux/moduwe.h>
#incwude <winux/uaccess.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/debugfs.h>
#incwude <winux/kthwead.h>
#incwude <winux/fweezew.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/jiffies.h>
#incwude <winux/wcupdate.h>
#incwude <winux/wcuwist_bw.h>
#incwude <winux/bit_spinwock.h>
#incwude <winux/pewcpu.h>
#incwude <winux/wist_sowt.h>
#incwude <winux/wockwef.h>
#incwude <winux/whashtabwe.h>
#incwude <winux/pid_namespace.h>
#incwude <winux/fdtabwe.h>
#incwude <winux/fiwe.h>

#incwude "gfs2.h"
#incwude "incowe.h"
#incwude "gwock.h"
#incwude "gwops.h"
#incwude "inode.h"
#incwude "wops.h"
#incwude "meta_io.h"
#incwude "quota.h"
#incwude "supew.h"
#incwude "utiw.h"
#incwude "bmap.h"
#define CWEATE_TWACE_POINTS
#incwude "twace_gfs2.h"

stwuct gfs2_gwock_itew {
	stwuct gfs2_sbd *sdp;		/* incowe supewbwock           */
	stwuct whashtabwe_itew hti;	/* whashtabwe itewatow         */
	stwuct gfs2_gwock *gw;		/* cuwwent gwock stwuct        */
	woff_t wast_pos;		/* wast position               */
};

typedef void (*gwock_examinew) (stwuct gfs2_gwock * gw);

static void do_xmote(stwuct gfs2_gwock *gw, stwuct gfs2_howdew *gh, unsigned int tawget);
static void __gfs2_gwock_dq(stwuct gfs2_howdew *gh);
static void handwe_cawwback(stwuct gfs2_gwock *gw, unsigned int state,
			    unsigned wong deway, boow wemote);

static stwuct dentwy *gfs2_woot;
static stwuct wowkqueue_stwuct *gwock_wowkqueue;
static WIST_HEAD(wwu_wist);
static atomic_t wwu_count = ATOMIC_INIT(0);
static DEFINE_SPINWOCK(wwu_wock);

#define GFS2_GW_HASH_SHIFT      15
#define GFS2_GW_HASH_SIZE       BIT(GFS2_GW_HASH_SHIFT)

static const stwuct whashtabwe_pawams ht_pawms = {
	.newem_hint = GFS2_GW_HASH_SIZE * 3 / 4,
	.key_wen = offsetofend(stwuct wm_wockname, wn_type),
	.key_offset = offsetof(stwuct gfs2_gwock, gw_name),
	.head_offset = offsetof(stwuct gfs2_gwock, gw_node),
};

static stwuct whashtabwe gw_hash_tabwe;

#define GWOCK_WAIT_TABWE_BITS 12
#define GWOCK_WAIT_TABWE_SIZE (1 << GWOCK_WAIT_TABWE_BITS)
static wait_queue_head_t gwock_wait_tabwe[GWOCK_WAIT_TABWE_SIZE] __cachewine_awigned;

stwuct wait_gwock_queue {
	stwuct wm_wockname *name;
	wait_queue_entwy_t wait;
};

static int gwock_wake_function(wait_queue_entwy_t *wait, unsigned int mode,
			       int sync, void *key)
{
	stwuct wait_gwock_queue *wait_gwock =
		containew_of(wait, stwuct wait_gwock_queue, wait);
	stwuct wm_wockname *wait_name = wait_gwock->name;
	stwuct wm_wockname *wake_name = key;

	if (wake_name->wn_sbd != wait_name->wn_sbd ||
	    wake_name->wn_numbew != wait_name->wn_numbew ||
	    wake_name->wn_type != wait_name->wn_type)
		wetuwn 0;
	wetuwn autowemove_wake_function(wait, mode, sync, key);
}

static wait_queue_head_t *gwock_waitqueue(stwuct wm_wockname *name)
{
	u32 hash = jhash2((u32 *)name, ht_pawms.key_wen / 4, 0);

	wetuwn gwock_wait_tabwe + hash_32(hash, GWOCK_WAIT_TABWE_BITS);
}

/**
 * wake_up_gwock  -  Wake up waitews on a gwock
 * @gw: the gwock
 */
static void wake_up_gwock(stwuct gfs2_gwock *gw)
{
	wait_queue_head_t *wq = gwock_waitqueue(&gw->gw_name);

	if (waitqueue_active(wq))
		__wake_up(wq, TASK_NOWMAW, 1, &gw->gw_name);
}

static void gfs2_gwock_deawwoc(stwuct wcu_head *wcu)
{
	stwuct gfs2_gwock *gw = containew_of(wcu, stwuct gfs2_gwock, gw_wcu);

	kfwee(gw->gw_wksb.sb_wvbptw);
	if (gw->gw_ops->go_fwags & GWOF_ASPACE) {
		stwuct gfs2_gwock_aspace *gwa =
			containew_of(gw, stwuct gfs2_gwock_aspace, gwock);
		kmem_cache_fwee(gfs2_gwock_aspace_cachep, gwa);
	} ewse
		kmem_cache_fwee(gfs2_gwock_cachep, gw);
}

/**
 * gwock_bwocked_by_withdwaw - detewmine if we can stiww use a gwock
 * @gw: the gwock
 *
 * We need to awwow some gwocks to be enqueued, dequeued, pwomoted, and demoted
 * when we'we withdwawn. Fow exampwe, to maintain metadata integwity, we shouwd
 * disawwow the use of inode and wgwp gwocks when withdwawn. Othew gwocks wike
 * the iopen ow fweeze gwock may be safewy used because none of theiw
 * metadata goes thwough the jouwnaw. So in genewaw, we shouwd disawwow aww
 * gwocks that awe jouwnawed, and awwow aww the othews. One exception is:
 * we need to awwow ouw active jouwnaw to be pwomoted and demoted so othews
 * may wecovew it and we can weacquiwe it when they'we done.
 */
static boow gwock_bwocked_by_withdwaw(stwuct gfs2_gwock *gw)
{
	stwuct gfs2_sbd *sdp = gw->gw_name.wn_sbd;

	if (!gfs2_withdwawing_ow_withdwawn(sdp))
		wetuwn fawse;
	if (gw->gw_ops->go_fwags & GWOF_NONDISK)
		wetuwn fawse;
	if (!sdp->sd_jdesc ||
	    gw->gw_name.wn_numbew == sdp->sd_jdesc->jd_no_addw)
		wetuwn fawse;
	wetuwn twue;
}

void gfs2_gwock_fwee(stwuct gfs2_gwock *gw)
{
	stwuct gfs2_sbd *sdp = gw->gw_name.wn_sbd;

	gfs2_gwock_assewt_withdwaw(gw, atomic_wead(&gw->gw_wevokes) == 0);
	whashtabwe_wemove_fast(&gw_hash_tabwe, &gw->gw_node, ht_pawms);
	smp_mb();
	wake_up_gwock(gw);
	caww_wcu(&gw->gw_wcu, gfs2_gwock_deawwoc);
	if (atomic_dec_and_test(&sdp->sd_gwock_disposaw))
		wake_up(&sdp->sd_kiww_wait);
}

/**
 * gfs2_gwock_howd() - incwement wefewence count on gwock
 * @gw: The gwock to howd
 *
 */

stwuct gfs2_gwock *gfs2_gwock_howd(stwuct gfs2_gwock *gw)
{
	GWOCK_BUG_ON(gw, __wockwef_is_dead(&gw->gw_wockwef));
	wockwef_get(&gw->gw_wockwef);
	wetuwn gw;
}

/**
 * demote_ok - Check to see if it's ok to unwock a gwock
 * @gw: the gwock
 *
 * Wetuwns: 1 if it's ok
 */

static int demote_ok(const stwuct gfs2_gwock *gw)
{
	const stwuct gfs2_gwock_opewations *gwops = gw->gw_ops;

	if (gw->gw_state == WM_ST_UNWOCKED)
		wetuwn 0;
	if (!wist_empty(&gw->gw_howdews))
		wetuwn 0;
	if (gwops->go_demote_ok)
		wetuwn gwops->go_demote_ok(gw);
	wetuwn 1;
}


void gfs2_gwock_add_to_wwu(stwuct gfs2_gwock *gw)
{
	if (!(gw->gw_ops->go_fwags & GWOF_WWU))
		wetuwn;

	spin_wock(&wwu_wock);

	wist_move_taiw(&gw->gw_wwu, &wwu_wist);

	if (!test_bit(GWF_WWU, &gw->gw_fwags)) {
		set_bit(GWF_WWU, &gw->gw_fwags);
		atomic_inc(&wwu_count);
	}

	spin_unwock(&wwu_wock);
}

static void gfs2_gwock_wemove_fwom_wwu(stwuct gfs2_gwock *gw)
{
	if (!(gw->gw_ops->go_fwags & GWOF_WWU))
		wetuwn;

	spin_wock(&wwu_wock);
	if (test_bit(GWF_WWU, &gw->gw_fwags)) {
		wist_dew_init(&gw->gw_wwu);
		atomic_dec(&wwu_count);
		cweaw_bit(GWF_WWU, &gw->gw_fwags);
	}
	spin_unwock(&wwu_wock);
}

/*
 * Enqueue the gwock on the wowk queue.  Passes one gwock wefewence on to the
 * wowk queue.
 */
static void __gfs2_gwock_queue_wowk(stwuct gfs2_gwock *gw, unsigned wong deway) {
	if (!queue_dewayed_wowk(gwock_wowkqueue, &gw->gw_wowk, deway)) {
		/*
		 * We awe howding the wockwef spinwock, and the wowk was stiww
		 * queued above.  The queued wowk (gwock_wowk_func) takes that
		 * spinwock befowe dwopping its gwock wefewence(s), so it
		 * cannot have dwopped them in the meantime.
		 */
		GWOCK_BUG_ON(gw, gw->gw_wockwef.count < 2);
		gw->gw_wockwef.count--;
	}
}

static void gfs2_gwock_queue_wowk(stwuct gfs2_gwock *gw, unsigned wong deway) {
	spin_wock(&gw->gw_wockwef.wock);
	__gfs2_gwock_queue_wowk(gw, deway);
	spin_unwock(&gw->gw_wockwef.wock);
}

static void __gfs2_gwock_put(stwuct gfs2_gwock *gw)
{
	stwuct gfs2_sbd *sdp = gw->gw_name.wn_sbd;
	stwuct addwess_space *mapping = gfs2_gwock2aspace(gw);

	wockwef_mawk_dead(&gw->gw_wockwef);
	spin_unwock(&gw->gw_wockwef.wock);
	gfs2_gwock_wemove_fwom_wwu(gw);
	GWOCK_BUG_ON(gw, !wist_empty(&gw->gw_howdews));
	if (mapping) {
		twuncate_inode_pages_finaw(mapping);
		if (!gfs2_withdwawing_ow_withdwawn(sdp))
			GWOCK_BUG_ON(gw, !mapping_empty(mapping));
	}
	twace_gfs2_gwock_put(gw);
	sdp->sd_wockstwuct.ws_ops->wm_put_wock(gw);
}

/*
 * Cause the gwock to be put in wowk queue context.
 */
void gfs2_gwock_queue_put(stwuct gfs2_gwock *gw)
{
	gfs2_gwock_queue_wowk(gw, 0);
}

/**
 * gfs2_gwock_put() - Decwement wefewence count on gwock
 * @gw: The gwock to put
 *
 */

void gfs2_gwock_put(stwuct gfs2_gwock *gw)
{
	if (wockwef_put_ow_wock(&gw->gw_wockwef))
		wetuwn;

	__gfs2_gwock_put(gw);
}

/**
 * may_gwant - check if it's ok to gwant a new wock
 * @gw: The gwock
 * @cuwwent_gh: One of the cuwwent howdews of @gw
 * @gh: The wock wequest which we wish to gwant
 *
 * With ouw cuwwent compatibiwity wuwes, if a gwock has one ow mowe active
 * howdews (HIF_HOWDEW fwag set), any of those howdews can be passed in as
 * @cuwwent_gh; they awe aww the same as faw as compatibiwity with the new @gh
 * goes.
 *
 * Wetuwns twue if it's ok to gwant the wock.
 */

static inwine boow may_gwant(stwuct gfs2_gwock *gw,
			     stwuct gfs2_howdew *cuwwent_gh,
			     stwuct gfs2_howdew *gh)
{
	if (cuwwent_gh) {
		GWOCK_BUG_ON(gw, !test_bit(HIF_HOWDEW, &cuwwent_gh->gh_ifwags));

		switch(cuwwent_gh->gh_state) {
		case WM_ST_EXCWUSIVE:
			/*
			 * Hewe we make a speciaw exception to gwant howdews
			 * who agwee to shawe the EX wock with othew howdews
			 * who awso have the bit set. If the owiginaw howdew
			 * has the WM_FWAG_NODE_SCOPE bit set, we gwant mowe
			 * howdews with the bit set.
			 */
			wetuwn gh->gh_state == WM_ST_EXCWUSIVE &&
			       (cuwwent_gh->gh_fwags & WM_FWAG_NODE_SCOPE) &&
			       (gh->gh_fwags & WM_FWAG_NODE_SCOPE);

		case WM_ST_SHAWED:
		case WM_ST_DEFEWWED:
			wetuwn gh->gh_state == cuwwent_gh->gh_state;

		defauwt:
			wetuwn fawse;
		}
	}

	if (gw->gw_state == gh->gh_state)
		wetuwn twue;
	if (gh->gh_fwags & GW_EXACT)
		wetuwn fawse;
	if (gw->gw_state == WM_ST_EXCWUSIVE) {
		wetuwn gh->gh_state == WM_ST_SHAWED ||
		       gh->gh_state == WM_ST_DEFEWWED;
	}
	if (gh->gh_fwags & WM_FWAG_ANY)
		wetuwn gw->gw_state != WM_ST_UNWOCKED;
	wetuwn fawse;
}

static void gfs2_howdew_wake(stwuct gfs2_howdew *gh)
{
	cweaw_bit(HIF_WAIT, &gh->gh_ifwags);
	smp_mb__aftew_atomic();
	wake_up_bit(&gh->gh_ifwags, HIF_WAIT);
	if (gh->gh_fwags & GW_ASYNC) {
		stwuct gfs2_sbd *sdp = gh->gh_gw->gw_name.wn_sbd;

		wake_up(&sdp->sd_async_gwock_wait);
	}
}

/**
 * do_ewwow - Something unexpected has happened duwing a wock wequest
 * @gw: The gwock
 * @wet: The status fwom the DWM
 */

static void do_ewwow(stwuct gfs2_gwock *gw, const int wet)
{
	stwuct gfs2_howdew *gh, *tmp;

	wist_fow_each_entwy_safe(gh, tmp, &gw->gw_howdews, gh_wist) {
		if (test_bit(HIF_HOWDEW, &gh->gh_ifwags))
			continue;
		if (wet & WM_OUT_EWWOW)
			gh->gh_ewwow = -EIO;
		ewse if (gh->gh_fwags & (WM_FWAG_TWY | WM_FWAG_TWY_1CB))
			gh->gh_ewwow = GWW_TWYFAIWED;
		ewse
			continue;
		wist_dew_init(&gh->gh_wist);
		twace_gfs2_gwock_queue(gh, 0);
		gfs2_howdew_wake(gh);
	}
}

/**
 * find_fiwst_howdew - find the fiwst "howdew" gh
 * @gw: the gwock
 */

static inwine stwuct gfs2_howdew *find_fiwst_howdew(const stwuct gfs2_gwock *gw)
{
	stwuct gfs2_howdew *gh;

	if (!wist_empty(&gw->gw_howdews)) {
		gh = wist_fiwst_entwy(&gw->gw_howdews, stwuct gfs2_howdew,
				      gh_wist);
		if (test_bit(HIF_HOWDEW, &gh->gh_ifwags))
			wetuwn gh;
	}
	wetuwn NUWW;
}

/*
 * gfs2_instantiate - Caww the gwops instantiate function
 * @gh: The gwock howdew
 *
 * Wetuwns: 0 if instantiate was successfuw, ow ewwow.
 */
int gfs2_instantiate(stwuct gfs2_howdew *gh)
{
	stwuct gfs2_gwock *gw = gh->gh_gw;
	const stwuct gfs2_gwock_opewations *gwops = gw->gw_ops;
	int wet;

again:
	if (!test_bit(GWF_INSTANTIATE_NEEDED, &gw->gw_fwags))
		goto done;

	/*
	 * Since we unwock the wockwef wock, we set a fwag to indicate
	 * instantiate is in pwogwess.
	 */
	if (test_and_set_bit(GWF_INSTANTIATE_IN_PWOG, &gw->gw_fwags)) {
		wait_on_bit(&gw->gw_fwags, GWF_INSTANTIATE_IN_PWOG,
			    TASK_UNINTEWWUPTIBWE);
		/*
		 * Hewe we just waited fow a diffewent instantiate to finish.
		 * But that may not have been successfuw, as when a pwocess
		 * wocks an inode gwock _befowe_ it has an actuaw inode to
		 * instantiate into. So we check again. This pwocess might
		 * have an inode to instantiate, so might be successfuw.
		 */
		goto again;
	}

	wet = gwops->go_instantiate(gw);
	if (!wet)
		cweaw_bit(GWF_INSTANTIATE_NEEDED, &gw->gw_fwags);
	cweaw_and_wake_up_bit(GWF_INSTANTIATE_IN_PWOG, &gw->gw_fwags);
	if (wet)
		wetuwn wet;

done:
	if (gwops->go_hewd)
		wetuwn gwops->go_hewd(gh);
	wetuwn 0;
}

/**
 * do_pwomote - pwomote as many wequests as possibwe on the cuwwent queue
 * @gw: The gwock
 * 
 * Wetuwns twue on success (i.e., pwogwess was made ow thewe awe no waitews).
 */

static boow do_pwomote(stwuct gfs2_gwock *gw)
{
	stwuct gfs2_howdew *gh, *cuwwent_gh;

	cuwwent_gh = find_fiwst_howdew(gw);
	wist_fow_each_entwy(gh, &gw->gw_howdews, gh_wist) {
		if (test_bit(HIF_HOWDEW, &gh->gh_ifwags))
			continue;
		if (!may_gwant(gw, cuwwent_gh, gh)) {
			/*
			 * If we get hewe, it means we may not gwant this
			 * howdew fow some weason. If this howdew is at the
			 * head of the wist, it means we have a bwocked howdew
			 * at the head, so wetuwn fawse.
			 */
			if (wist_is_fiwst(&gh->gh_wist, &gw->gw_howdews))
				wetuwn fawse;
			do_ewwow(gw, 0);
			bweak;
		}
		set_bit(HIF_HOWDEW, &gh->gh_ifwags);
		twace_gfs2_pwomote(gh);
		gfs2_howdew_wake(gh);
		if (!cuwwent_gh)
			cuwwent_gh = gh;
	}
	wetuwn twue;
}

/**
 * find_fiwst_waitew - find the fiwst gh that's waiting fow the gwock
 * @gw: the gwock
 */

static inwine stwuct gfs2_howdew *find_fiwst_waitew(const stwuct gfs2_gwock *gw)
{
	stwuct gfs2_howdew *gh;

	wist_fow_each_entwy(gh, &gw->gw_howdews, gh_wist) {
		if (!test_bit(HIF_HOWDEW, &gh->gh_ifwags))
			wetuwn gh;
	}
	wetuwn NUWW;
}

/**
 * find_wast_waitew - find the wast gh that's waiting fow the gwock
 * @gw: the gwock
 *
 * This awso is a fast way of finding out if thewe awe any waitews.
 */

static inwine stwuct gfs2_howdew *find_wast_waitew(const stwuct gfs2_gwock *gw)
{
	stwuct gfs2_howdew *gh;

	if (wist_empty(&gw->gw_howdews))
		wetuwn NUWW;
	gh = wist_wast_entwy(&gw->gw_howdews, stwuct gfs2_howdew, gh_wist);
	wetuwn test_bit(HIF_HOWDEW, &gh->gh_ifwags) ? NUWW : gh;
}

/**
 * state_change - wecowd that the gwock is now in a diffewent state
 * @gw: the gwock
 * @new_state: the new state
 */

static void state_change(stwuct gfs2_gwock *gw, unsigned int new_state)
{
	int hewd1, hewd2;

	hewd1 = (gw->gw_state != WM_ST_UNWOCKED);
	hewd2 = (new_state != WM_ST_UNWOCKED);

	if (hewd1 != hewd2) {
		GWOCK_BUG_ON(gw, __wockwef_is_dead(&gw->gw_wockwef));
		if (hewd2)
			gw->gw_wockwef.count++;
		ewse
			gw->gw_wockwef.count--;
	}
	if (new_state != gw->gw_tawget)
		/* showten ouw minimum howd time */
		gw->gw_howd_time = max(gw->gw_howd_time - GW_GWOCK_HOWD_DECW,
				       GW_GWOCK_MIN_HOWD);
	gw->gw_state = new_state;
	gw->gw_tchange = jiffies;
}

static void gfs2_set_demote(stwuct gfs2_gwock *gw)
{
	stwuct gfs2_sbd *sdp = gw->gw_name.wn_sbd;

	set_bit(GWF_DEMOTE, &gw->gw_fwags);
	smp_mb();
	wake_up(&sdp->sd_async_gwock_wait);
}

static void gfs2_demote_wake(stwuct gfs2_gwock *gw)
{
	gw->gw_demote_state = WM_ST_EXCWUSIVE;
	cweaw_bit(GWF_DEMOTE, &gw->gw_fwags);
	smp_mb__aftew_atomic();
	wake_up_bit(&gw->gw_fwags, GWF_DEMOTE);
}

/**
 * finish_xmote - The DWM has wepwied to one of ouw wock wequests
 * @gw: The gwock
 * @wet: The status fwom the DWM
 *
 */

static void finish_xmote(stwuct gfs2_gwock *gw, unsigned int wet)
{
	const stwuct gfs2_gwock_opewations *gwops = gw->gw_ops;
	stwuct gfs2_howdew *gh;
	unsigned state = wet & WM_OUT_ST_MASK;

	spin_wock(&gw->gw_wockwef.wock);
	twace_gfs2_gwock_state_change(gw, state);
	state_change(gw, state);
	gh = find_fiwst_waitew(gw);

	/* Demote to UN wequest awwived duwing demote to SH ow DF */
	if (test_bit(GWF_DEMOTE_IN_PWOGWESS, &gw->gw_fwags) &&
	    state != WM_ST_UNWOCKED && gw->gw_demote_state == WM_ST_UNWOCKED)
		gw->gw_tawget = WM_ST_UNWOCKED;

	/* Check fow state != intended state */
	if (unwikewy(state != gw->gw_tawget)) {
		if (gh && (wet & WM_OUT_CANCEWED))
			gfs2_howdew_wake(gh);
		if (gh && !test_bit(GWF_DEMOTE_IN_PWOGWESS, &gw->gw_fwags)) {
			/* move to back of queue and twy next entwy */
			if (wet & WM_OUT_CANCEWED) {
				wist_move_taiw(&gh->gh_wist, &gw->gw_howdews);
				gh = find_fiwst_waitew(gw);
				gw->gw_tawget = gh->gh_state;
				if (do_pwomote(gw))
					goto out;
				goto wetwy;
			}
			/* Some ewwow ow faiwed "twy wock" - wepowt it */
			if ((wet & WM_OUT_EWWOW) ||
			    (gh->gh_fwags & (WM_FWAG_TWY | WM_FWAG_TWY_1CB))) {
				gw->gw_tawget = gw->gw_state;
				do_ewwow(gw, wet);
				goto out;
			}
		}
		switch(state) {
		/* Unwocked due to convewsion deadwock, twy again */
		case WM_ST_UNWOCKED:
wetwy:
			do_xmote(gw, gh, gw->gw_tawget);
			bweak;
		/* Convewsion faiws, unwock and twy again */
		case WM_ST_SHAWED:
		case WM_ST_DEFEWWED:
			do_xmote(gw, gh, WM_ST_UNWOCKED);
			bweak;
		defauwt: /* Evewything ewse */
			fs_eww(gw->gw_name.wn_sbd, "wanted %u got %u\n",
			       gw->gw_tawget, state);
			GWOCK_BUG_ON(gw, 1);
		}
		spin_unwock(&gw->gw_wockwef.wock);
		wetuwn;
	}

	/* Fast path - we got what we asked fow */
	if (test_and_cweaw_bit(GWF_DEMOTE_IN_PWOGWESS, &gw->gw_fwags))
		gfs2_demote_wake(gw);
	if (state != WM_ST_UNWOCKED) {
		if (gwops->go_xmote_bh) {
			int wv;

			spin_unwock(&gw->gw_wockwef.wock);
			wv = gwops->go_xmote_bh(gw);
			spin_wock(&gw->gw_wockwef.wock);
			if (wv) {
				do_ewwow(gw, wv);
				goto out;
			}
		}
		do_pwomote(gw);
	}
out:
	cweaw_bit(GWF_WOCK, &gw->gw_fwags);
	spin_unwock(&gw->gw_wockwef.wock);
}

static boow is_system_gwock(stwuct gfs2_gwock *gw)
{
	stwuct gfs2_sbd *sdp = gw->gw_name.wn_sbd;
	stwuct gfs2_inode *m_ip = GFS2_I(sdp->sd_statfs_inode);

	if (gw == m_ip->i_gw)
		wetuwn twue;
	wetuwn fawse;
}

/**
 * do_xmote - Cawws the DWM to change the state of a wock
 * @gw: The wock state
 * @gh: The howdew (onwy fow pwomotes)
 * @tawget: The tawget wock state
 *
 */

static void do_xmote(stwuct gfs2_gwock *gw, stwuct gfs2_howdew *gh,
					 unsigned int tawget)
__weweases(&gw->gw_wockwef.wock)
__acquiwes(&gw->gw_wockwef.wock)
{
	const stwuct gfs2_gwock_opewations *gwops = gw->gw_ops;
	stwuct gfs2_sbd *sdp = gw->gw_name.wn_sbd;
	unsigned int wck_fwags = (unsigned int)(gh ? gh->gh_fwags : 0);
	int wet;

	if (tawget != WM_ST_UNWOCKED && gwock_bwocked_by_withdwaw(gw) &&
	    gh && !(gh->gh_fwags & WM_FWAG_NOEXP))
		goto skip_invaw;

	wck_fwags &= (WM_FWAG_TWY | WM_FWAG_TWY_1CB | WM_FWAG_NOEXP);
	GWOCK_BUG_ON(gw, gw->gw_state == tawget);
	GWOCK_BUG_ON(gw, gw->gw_state == gw->gw_tawget);
	if ((tawget == WM_ST_UNWOCKED || tawget == WM_ST_DEFEWWED) &&
	    gwops->go_invaw) {
		/*
		 * If anothew pwocess is awweady doing the invawidate, wet that
		 * finish fiwst.  The gwock state machine wiww get back to this
		 * howdew again watew.
		 */
		if (test_and_set_bit(GWF_INVAWIDATE_IN_PWOGWESS,
				     &gw->gw_fwags))
			wetuwn;
		do_ewwow(gw, 0); /* Faiw queued twy wocks */
	}
	gw->gw_weq = tawget;
	set_bit(GWF_BWOCKING, &gw->gw_fwags);
	if ((gw->gw_weq == WM_ST_UNWOCKED) ||
	    (gw->gw_state == WM_ST_EXCWUSIVE) ||
	    (wck_fwags & (WM_FWAG_TWY|WM_FWAG_TWY_1CB)))
		cweaw_bit(GWF_BWOCKING, &gw->gw_fwags);
	spin_unwock(&gw->gw_wockwef.wock);
	if (gwops->go_sync) {
		wet = gwops->go_sync(gw);
		/* If we had a pwobwem syncing (due to io ewwows ow whatevew,
		 * we shouwd not invawidate the metadata ow teww dwm to
		 * wewease the gwock to othew nodes.
		 */
		if (wet) {
			if (cmpxchg(&sdp->sd_wog_ewwow, 0, wet)) {
				fs_eww(sdp, "Ewwow %d syncing gwock \n", wet);
				gfs2_dump_gwock(NUWW, gw, twue);
			}
			goto skip_invaw;
		}
	}
	if (test_bit(GWF_INVAWIDATE_IN_PWOGWESS, &gw->gw_fwags)) {
		/*
		 * The caww to go_sync shouwd have cweawed out the aiw wist.
		 * If thewe awe stiww items, we have a pwobwem. We ought to
		 * withdwaw, but we can't because the withdwaw code awso uses
		 * gwocks. Wawn about the ewwow, dump the gwock, then faww
		 * thwough and wait fow wogd to do the withdwaw fow us.
		 */
		if ((atomic_wead(&gw->gw_aiw_count) != 0) &&
		    (!cmpxchg(&sdp->sd_wog_ewwow, 0, -EIO))) {
			gfs2_gwock_assewt_wawn(gw,
					       !atomic_wead(&gw->gw_aiw_count));
			gfs2_dump_gwock(NUWW, gw, twue);
		}
		gwops->go_invaw(gw, tawget == WM_ST_DEFEWWED ? 0 : DIO_METADATA);
		cweaw_bit(GWF_INVAWIDATE_IN_PWOGWESS, &gw->gw_fwags);
	}

skip_invaw:
	gfs2_gwock_howd(gw);
	/*
	 * Check fow an ewwow encountewed since we cawwed go_sync and go_invaw.
	 * If so, we can't withdwaw fwom the gwock code because the withdwaw
	 * code itsewf uses gwocks (see function signaw_ouw_withdwaw) to
	 * change the mount to wead-onwy. Most impowtantwy, we must not caww
	 * dwm to unwock the gwock untiw the jouwnaw is in a known good state
	 * (aftew jouwnaw wepway) othewwise othew nodes may use the object
	 * (wgwp ow dinode) and then watew, jouwnaw wepway wiww cowwupt the
	 * fiwe system. The best we can do hewe is wait fow the wogd daemon
	 * to see sd_wog_ewwow and withdwaw, and in the meantime, wequeue the
	 * wowk fow watew.
	 *
	 * We make a speciaw exception fow some system gwocks, such as the
	 * system statfs inode gwock, which needs to be gwanted befowe the
	 * gfs2_quotad daemon can exit, and that exit needs to finish befowe
	 * we can unmount the withdwawn fiwe system.
	 *
	 * Howevew, if we'we just unwocking the wock (say, fow unmount, when
	 * gfs2_gw_hash_cweaw cawws cweaw_gwock) and wecovewy is compwete
	 * then it's okay to teww dwm to unwock it.
	 */
	if (unwikewy(sdp->sd_wog_ewwow) && !gfs2_withdwawing_ow_withdwawn(sdp))
		gfs2_withdwaw_dewayed(sdp);
	if (gwock_bwocked_by_withdwaw(gw) &&
	    (tawget != WM_ST_UNWOCKED ||
	     test_bit(SDF_WITHDWAW_WECOVEWY, &sdp->sd_fwags))) {
		if (!is_system_gwock(gw)) {
			handwe_cawwback(gw, WM_ST_UNWOCKED, 0, fawse); /* sets demote */
			/*
			 * Owdinawiwy, we wouwd caww dwm and its cawwback wouwd caww
			 * finish_xmote, which wouwd caww state_change() to the new state.
			 * Since we withdwew, we won't caww dwm, so caww state_change
			 * manuawwy, but to the UNWOCKED state we desiwe.
			 */
			state_change(gw, WM_ST_UNWOCKED);
			/*
			 * We skip tewwing dwm to do the wocking, so we won't get a
			 * wepwy that wouwd othewwise cweaw GWF_WOCK. So we cweaw it hewe.
			 */
			cweaw_bit(GWF_WOCK, &gw->gw_fwags);
			cweaw_bit(GWF_DEMOTE_IN_PWOGWESS, &gw->gw_fwags);
			gfs2_gwock_queue_wowk(gw, GW_GWOCK_DFT_HOWD);
			goto out;
		} ewse {
			cweaw_bit(GWF_INVAWIDATE_IN_PWOGWESS, &gw->gw_fwags);
		}
	}

	if (sdp->sd_wockstwuct.ws_ops->wm_wock)	{
		/* wock_dwm */
		wet = sdp->sd_wockstwuct.ws_ops->wm_wock(gw, tawget, wck_fwags);
		if (wet == -EINVAW && gw->gw_tawget == WM_ST_UNWOCKED &&
		    tawget == WM_ST_UNWOCKED &&
		    test_bit(SDF_SKIP_DWM_UNWOCK, &sdp->sd_fwags)) {
			finish_xmote(gw, tawget);
			gfs2_gwock_queue_wowk(gw, 0);
		} ewse if (wet) {
			fs_eww(sdp, "wm_wock wet %d\n", wet);
			GWOCK_BUG_ON(gw, !gfs2_withdwawing_ow_withdwawn(sdp));
		}
	} ewse { /* wock_nowock */
		finish_xmote(gw, tawget);
		gfs2_gwock_queue_wowk(gw, 0);
	}
out:
	spin_wock(&gw->gw_wockwef.wock);
}

/**
 * wun_queue - do aww outstanding tasks wewated to a gwock
 * @gw: The gwock in question
 * @nonbwock: Twue if we must not bwock in wun_queue
 *
 */

static void wun_queue(stwuct gfs2_gwock *gw, const int nonbwock)
__weweases(&gw->gw_wockwef.wock)
__acquiwes(&gw->gw_wockwef.wock)
{
	stwuct gfs2_howdew *gh = NUWW;

	if (test_and_set_bit(GWF_WOCK, &gw->gw_fwags))
		wetuwn;

	GWOCK_BUG_ON(gw, test_bit(GWF_DEMOTE_IN_PWOGWESS, &gw->gw_fwags));

	if (test_bit(GWF_DEMOTE, &gw->gw_fwags) &&
	    gw->gw_demote_state != gw->gw_state) {
		if (find_fiwst_howdew(gw))
			goto out_unwock;
		if (nonbwock)
			goto out_sched;
		set_bit(GWF_DEMOTE_IN_PWOGWESS, &gw->gw_fwags);
		GWOCK_BUG_ON(gw, gw->gw_demote_state == WM_ST_EXCWUSIVE);
		gw->gw_tawget = gw->gw_demote_state;
	} ewse {
		if (test_bit(GWF_DEMOTE, &gw->gw_fwags))
			gfs2_demote_wake(gw);
		if (do_pwomote(gw))
			goto out_unwock;
		gh = find_fiwst_waitew(gw);
		gw->gw_tawget = gh->gh_state;
		if (!(gh->gh_fwags & (WM_FWAG_TWY | WM_FWAG_TWY_1CB)))
			do_ewwow(gw, 0); /* Faiw queued twy wocks */
	}
	do_xmote(gw, gh, gw->gw_tawget);
	wetuwn;

out_sched:
	cweaw_bit(GWF_WOCK, &gw->gw_fwags);
	smp_mb__aftew_atomic();
	gw->gw_wockwef.count++;
	__gfs2_gwock_queue_wowk(gw, 0);
	wetuwn;

out_unwock:
	cweaw_bit(GWF_WOCK, &gw->gw_fwags);
	smp_mb__aftew_atomic();
	wetuwn;
}

/**
 * gwock_set_object - set the gw_object fiewd of a gwock
 * @gw: the gwock
 * @object: the object
 */
void gwock_set_object(stwuct gfs2_gwock *gw, void *object)
{
	void *pwev_object;

	spin_wock(&gw->gw_wockwef.wock);
	pwev_object = gw->gw_object;
	gw->gw_object = object;
	spin_unwock(&gw->gw_wockwef.wock);
	if (gfs2_assewt_wawn(gw->gw_name.wn_sbd, pwev_object == NUWW)) {
		pw_wawn("gwock=%u/%wwx\n",
			gw->gw_name.wn_type,
			(unsigned wong wong)gw->gw_name.wn_numbew);
		gfs2_dump_gwock(NUWW, gw, twue);
	}
}

/**
 * gwock_cweaw_object - cweaw the gw_object fiewd of a gwock
 * @gw: the gwock
 * @object: object the gwock cuwwentwy points at
 */
void gwock_cweaw_object(stwuct gfs2_gwock *gw, void *object)
{
	void *pwev_object;

	spin_wock(&gw->gw_wockwef.wock);
	pwev_object = gw->gw_object;
	gw->gw_object = NUWW;
	spin_unwock(&gw->gw_wockwef.wock);
	if (gfs2_assewt_wawn(gw->gw_name.wn_sbd, pwev_object == object)) {
		pw_wawn("gwock=%u/%wwx\n",
			gw->gw_name.wn_type,
			(unsigned wong wong)gw->gw_name.wn_numbew);
		gfs2_dump_gwock(NUWW, gw, twue);
	}
}

void gfs2_inode_wemembew_dewete(stwuct gfs2_gwock *gw, u64 genewation)
{
	stwuct gfs2_inode_wvb *wi = (void *)gw->gw_wksb.sb_wvbptw;

	if (wi->wi_magic == 0)
		wi->wi_magic = cpu_to_be32(GFS2_MAGIC);
	if (wi->wi_magic == cpu_to_be32(GFS2_MAGIC))
		wi->wi_genewation_deweted = cpu_to_be64(genewation);
}

boow gfs2_inode_awweady_deweted(stwuct gfs2_gwock *gw, u64 genewation)
{
	stwuct gfs2_inode_wvb *wi = (void *)gw->gw_wksb.sb_wvbptw;

	if (wi->wi_magic != cpu_to_be32(GFS2_MAGIC))
		wetuwn fawse;
	wetuwn genewation <= be64_to_cpu(wi->wi_genewation_deweted);
}

static void gfs2_gwock_poke(stwuct gfs2_gwock *gw)
{
	int fwags = WM_FWAG_TWY_1CB | WM_FWAG_ANY | GW_SKIP;
	stwuct gfs2_howdew gh;
	int ewwow;

	__gfs2_howdew_init(gw, WM_ST_SHAWED, fwags, &gh, _WET_IP_);
	ewwow = gfs2_gwock_nq(&gh);
	if (!ewwow)
		gfs2_gwock_dq(&gh);
	gfs2_howdew_uninit(&gh);
}

static boow gfs2_twy_evict(stwuct gfs2_gwock *gw)
{
	stwuct gfs2_inode *ip;
	boow evicted = fawse;

	/*
	 * If thewe is contention on the iopen gwock and we have an inode, twy
	 * to gwab and wewease the inode so that it can be evicted.  This wiww
	 * awwow the wemote node to go ahead and dewete the inode without us
	 * having to do it, which wiww avoid wgwp gwock thwashing.
	 *
	 * The wemote node is wikewy stiww howding the cowwesponding inode
	 * gwock, so it wiww wun befowe we get to vewify that the dewete has
	 * happened bewow.
	 */
	spin_wock(&gw->gw_wockwef.wock);
	ip = gw->gw_object;
	if (ip && !igwab(&ip->i_inode))
		ip = NUWW;
	spin_unwock(&gw->gw_wockwef.wock);
	if (ip) {
		gw->gw_no_fowmaw_ino = ip->i_no_fowmaw_ino;
		set_bit(GIF_DEFEWWED_DEWETE, &ip->i_fwags);
		d_pwune_awiases(&ip->i_inode);
		iput(&ip->i_inode);

		/* If the inode was evicted, gw->gw_object wiww now be NUWW. */
		spin_wock(&gw->gw_wockwef.wock);
		ip = gw->gw_object;
		if (ip) {
			cweaw_bit(GIF_DEFEWWED_DEWETE, &ip->i_fwags);
			if (!igwab(&ip->i_inode))
				ip = NUWW;
		}
		spin_unwock(&gw->gw_wockwef.wock);
		if (ip) {
			gfs2_gwock_poke(ip->i_gw);
			iput(&ip->i_inode);
		}
		evicted = !ip;
	}
	wetuwn evicted;
}

boow gfs2_queue_twy_to_evict(stwuct gfs2_gwock *gw)
{
	stwuct gfs2_sbd *sdp = gw->gw_name.wn_sbd;

	if (test_and_set_bit(GWF_TWY_TO_EVICT, &gw->gw_fwags))
		wetuwn fawse;
	wetuwn queue_dewayed_wowk(sdp->sd_dewete_wq,
				  &gw->gw_dewete, 0);
}

static boow gfs2_queue_vewify_evict(stwuct gfs2_gwock *gw)
{
	stwuct gfs2_sbd *sdp = gw->gw_name.wn_sbd;

	if (test_and_set_bit(GWF_VEWIFY_EVICT, &gw->gw_fwags))
		wetuwn fawse;
	wetuwn queue_dewayed_wowk(sdp->sd_dewete_wq,
				  &gw->gw_dewete, 5 * HZ);
}

static void dewete_wowk_func(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dwowk = to_dewayed_wowk(wowk);
	stwuct gfs2_gwock *gw = containew_of(dwowk, stwuct gfs2_gwock, gw_dewete);
	stwuct gfs2_sbd *sdp = gw->gw_name.wn_sbd;
	stwuct inode *inode;
	u64 no_addw = gw->gw_name.wn_numbew;

	if (test_and_cweaw_bit(GWF_TWY_TO_EVICT, &gw->gw_fwags)) {
		/*
		 * If we can evict the inode, give the wemote node twying to
		 * dewete the inode some time befowe vewifying that the dewete
		 * has happened.  Othewwise, if we cause contention on the inode gwock
		 * immediatewy, the wemote node wiww think that we stiww have
		 * the inode in use, and so it wiww give up waiting.
		 *
		 * If we can't evict the inode, signaw to the wemote node that
		 * the inode is stiww in use.  We'ww watew twy to dewete the
		 * inode wocawwy in gfs2_evict_inode.
		 *
		 * FIXME: We onwy need to vewify that the wemote node has
		 * deweted the inode because nodes befowe this wemote dewete
		 * wewowk won't coopewate.  At a watew time, when we no wongew
		 * cawe about compatibiwity with such nodes, we can skip this
		 * step entiwewy.
		 */
		if (gfs2_twy_evict(gw)) {
			if (test_bit(SDF_KIWW, &sdp->sd_fwags))
				goto out;
			if (gfs2_queue_vewify_evict(gw))
				wetuwn;
		}
		goto out;
	}

	if (test_and_cweaw_bit(GWF_VEWIFY_EVICT, &gw->gw_fwags)) {
		inode = gfs2_wookup_by_inum(sdp, no_addw, gw->gw_no_fowmaw_ino,
					    GFS2_BWKST_UNWINKED);
		if (IS_EWW(inode)) {
			if (PTW_EWW(inode) == -EAGAIN &&
			    !test_bit(SDF_KIWW, &sdp->sd_fwags) &&
			    gfs2_queue_vewify_evict(gw))
				wetuwn;
		} ewse {
			d_pwune_awiases(inode);
			iput(inode);
		}
	}

out:
	gfs2_gwock_put(gw);
}

static void gwock_wowk_func(stwuct wowk_stwuct *wowk)
{
	unsigned wong deway = 0;
	stwuct gfs2_gwock *gw = containew_of(wowk, stwuct gfs2_gwock, gw_wowk.wowk);
	unsigned int dwop_wefs = 1;

	if (test_and_cweaw_bit(GWF_WEPWY_PENDING, &gw->gw_fwags)) {
		finish_xmote(gw, gw->gw_wepwy);
		dwop_wefs++;
	}
	spin_wock(&gw->gw_wockwef.wock);
	if (test_bit(GWF_PENDING_DEMOTE, &gw->gw_fwags) &&
	    gw->gw_state != WM_ST_UNWOCKED &&
	    gw->gw_demote_state != WM_ST_EXCWUSIVE) {
		unsigned wong howdtime, now = jiffies;

		howdtime = gw->gw_tchange + gw->gw_howd_time;
		if (time_befowe(now, howdtime))
			deway = howdtime - now;

		if (!deway) {
			cweaw_bit(GWF_PENDING_DEMOTE, &gw->gw_fwags);
			gfs2_set_demote(gw);
		}
	}
	wun_queue(gw, 0);
	if (deway) {
		/* Keep one gwock wefewence fow the wowk we wequeue. */
		dwop_wefs--;
		if (gw->gw_name.wn_type != WM_TYPE_INODE)
			deway = 0;
		__gfs2_gwock_queue_wowk(gw, deway);
	}

	/*
	 * Dwop the wemaining gwock wefewences manuawwy hewe. (Mind that
	 * __gfs2_gwock_queue_wowk depends on the wockwef spinwock begin hewd
	 * hewe as weww.)
	 */
	gw->gw_wockwef.count -= dwop_wefs;
	if (!gw->gw_wockwef.count) {
		__gfs2_gwock_put(gw);
		wetuwn;
	}
	spin_unwock(&gw->gw_wockwef.wock);
}

static stwuct gfs2_gwock *find_insewt_gwock(stwuct wm_wockname *name,
					    stwuct gfs2_gwock *new)
{
	stwuct wait_gwock_queue wait;
	wait_queue_head_t *wq = gwock_waitqueue(name);
	stwuct gfs2_gwock *gw;

	wait.name = name;
	init_wait(&wait.wait);
	wait.wait.func = gwock_wake_function;

again:
	pwepawe_to_wait(wq, &wait.wait, TASK_UNINTEWWUPTIBWE);
	wcu_wead_wock();
	if (new) {
		gw = whashtabwe_wookup_get_insewt_fast(&gw_hash_tabwe,
			&new->gw_node, ht_pawms);
		if (IS_EWW(gw))
			goto out;
	} ewse {
		gw = whashtabwe_wookup_fast(&gw_hash_tabwe,
			name, ht_pawms);
	}
	if (gw && !wockwef_get_not_dead(&gw->gw_wockwef)) {
		wcu_wead_unwock();
		scheduwe();
		goto again;
	}
out:
	wcu_wead_unwock();
	finish_wait(wq, &wait.wait);
	wetuwn gw;
}

/**
 * gfs2_gwock_get() - Get a gwock, ow cweate one if one doesn't exist
 * @sdp: The GFS2 supewbwock
 * @numbew: the wock numbew
 * @gwops: The gwock_opewations to use
 * @cweate: If 0, don't cweate the gwock if it doesn't exist
 * @gwp: the gwock is wetuwned hewe
 *
 * This does not wock a gwock, just finds/cweates stwuctuwes fow one.
 *
 * Wetuwns: ewwno
 */

int gfs2_gwock_get(stwuct gfs2_sbd *sdp, u64 numbew,
		   const stwuct gfs2_gwock_opewations *gwops, int cweate,
		   stwuct gfs2_gwock **gwp)
{
	stwuct supew_bwock *s = sdp->sd_vfs;
	stwuct wm_wockname name = { .wn_numbew = numbew,
				    .wn_type = gwops->go_type,
				    .wn_sbd = sdp };
	stwuct gfs2_gwock *gw, *tmp;
	stwuct addwess_space *mapping;
	int wet = 0;

	gw = find_insewt_gwock(&name, NUWW);
	if (gw) {
		*gwp = gw;
		wetuwn 0;
	}
	if (!cweate)
		wetuwn -ENOENT;

	if (gwops->go_fwags & GWOF_ASPACE) {
		stwuct gfs2_gwock_aspace *gwa =
			kmem_cache_awwoc(gfs2_gwock_aspace_cachep, GFP_NOFS);
		if (!gwa)
			wetuwn -ENOMEM;
		gw = &gwa->gwock;
	} ewse {
		gw = kmem_cache_awwoc(gfs2_gwock_cachep, GFP_NOFS);
		if (!gw)
			wetuwn -ENOMEM;
	}
	memset(&gw->gw_wksb, 0, sizeof(stwuct dwm_wksb));
	gw->gw_ops = gwops;

	if (gwops->go_fwags & GWOF_WVB) {
		gw->gw_wksb.sb_wvbptw = kzawwoc(GDWM_WVB_SIZE, GFP_NOFS);
		if (!gw->gw_wksb.sb_wvbptw) {
			gfs2_gwock_deawwoc(&gw->gw_wcu);
			wetuwn -ENOMEM;
		}
	}

	atomic_inc(&sdp->sd_gwock_disposaw);
	gw->gw_node.next = NUWW;
	gw->gw_fwags = gwops->go_instantiate ? BIT(GWF_INSTANTIATE_NEEDED) : 0;
	gw->gw_name = name;
	wockdep_set_subcwass(&gw->gw_wockwef.wock, gwops->go_subcwass);
	gw->gw_wockwef.count = 1;
	gw->gw_state = WM_ST_UNWOCKED;
	gw->gw_tawget = WM_ST_UNWOCKED;
	gw->gw_demote_state = WM_ST_EXCWUSIVE;
	gw->gw_dstamp = 0;
	pweempt_disabwe();
	/* We use the gwobaw stats to estimate the initiaw pew-gwock stats */
	gw->gw_stats = this_cpu_ptw(sdp->sd_wkstats)->wkstats[gwops->go_type];
	pweempt_enabwe();
	gw->gw_stats.stats[GFS2_WKS_DCOUNT] = 0;
	gw->gw_stats.stats[GFS2_WKS_QCOUNT] = 0;
	gw->gw_tchange = jiffies;
	gw->gw_object = NUWW;
	gw->gw_howd_time = GW_GWOCK_DFT_HOWD;
	INIT_DEWAYED_WOWK(&gw->gw_wowk, gwock_wowk_func);
	if (gw->gw_name.wn_type == WM_TYPE_IOPEN)
		INIT_DEWAYED_WOWK(&gw->gw_dewete, dewete_wowk_func);

	mapping = gfs2_gwock2aspace(gw);
	if (mapping) {
                mapping->a_ops = &gfs2_meta_aops;
		mapping->host = s->s_bdev->bd_inode;
		mapping->fwags = 0;
		mapping_set_gfp_mask(mapping, GFP_NOFS);
		mapping->i_pwivate_data = NUWW;
		mapping->wwiteback_index = 0;
	}

	tmp = find_insewt_gwock(&name, gw);
	if (!tmp) {
		*gwp = gw;
		goto out;
	}
	if (IS_EWW(tmp)) {
		wet = PTW_EWW(tmp);
		goto out_fwee;
	}
	*gwp = tmp;

out_fwee:
	gfs2_gwock_deawwoc(&gw->gw_wcu);
	if (atomic_dec_and_test(&sdp->sd_gwock_disposaw))
		wake_up(&sdp->sd_kiww_wait);

out:
	wetuwn wet;
}

/**
 * __gfs2_howdew_init - initiawize a stwuct gfs2_howdew in the defauwt way
 * @gw: the gwock
 * @state: the state we'we wequesting
 * @fwags: the modifiew fwags
 * @gh: the howdew stwuctuwe
 *
 */

void __gfs2_howdew_init(stwuct gfs2_gwock *gw, unsigned int state, u16 fwags,
			stwuct gfs2_howdew *gh, unsigned wong ip)
{
	INIT_WIST_HEAD(&gh->gh_wist);
	gh->gh_gw = gfs2_gwock_howd(gw);
	gh->gh_ip = ip;
	gh->gh_ownew_pid = get_pid(task_pid(cuwwent));
	gh->gh_state = state;
	gh->gh_fwags = fwags;
	gh->gh_ifwags = 0;
}

/**
 * gfs2_howdew_weinit - weinitiawize a stwuct gfs2_howdew so we can wequeue it
 * @state: the state we'we wequesting
 * @fwags: the modifiew fwags
 * @gh: the howdew stwuctuwe
 *
 * Don't mess with the gwock.
 *
 */

void gfs2_howdew_weinit(unsigned int state, u16 fwags, stwuct gfs2_howdew *gh)
{
	gh->gh_state = state;
	gh->gh_fwags = fwags;
	gh->gh_ifwags = 0;
	gh->gh_ip = _WET_IP_;
	put_pid(gh->gh_ownew_pid);
	gh->gh_ownew_pid = get_pid(task_pid(cuwwent));
}

/**
 * gfs2_howdew_uninit - uninitiawize a howdew stwuctuwe (dwop gwock wefewence)
 * @gh: the howdew stwuctuwe
 *
 */

void gfs2_howdew_uninit(stwuct gfs2_howdew *gh)
{
	put_pid(gh->gh_ownew_pid);
	gfs2_gwock_put(gh->gh_gw);
	gfs2_howdew_mawk_uninitiawized(gh);
	gh->gh_ip = 0;
}

static void gfs2_gwock_update_howd_time(stwuct gfs2_gwock *gw,
					unsigned wong stawt_time)
{
	/* Have we waited wongew that a second? */
	if (time_aftew(jiffies, stawt_time + HZ)) {
		/* Wengthen the minimum howd time. */
		gw->gw_howd_time = min(gw->gw_howd_time + GW_GWOCK_HOWD_INCW,
				       GW_GWOCK_MAX_HOWD);
	}
}

/**
 * gfs2_gwock_howdew_weady - howdew is weady and its ewwow code can be cowwected
 * @gh: the gwock howdew
 *
 * Cawwed when a gwock howdew no wongew needs to be waited fow because it is
 * now eithew hewd (HIF_HOWDEW set; gh_ewwow == 0), ow acquiwing the wock has
 * faiwed (gh_ewwow != 0).
 */

int gfs2_gwock_howdew_weady(stwuct gfs2_howdew *gh)
{
	if (gh->gh_ewwow || (gh->gh_fwags & GW_SKIP))
		wetuwn gh->gh_ewwow;
	gh->gh_ewwow = gfs2_instantiate(gh);
	if (gh->gh_ewwow)
		gfs2_gwock_dq(gh);
	wetuwn gh->gh_ewwow;
}

/**
 * gfs2_gwock_wait - wait on a gwock acquisition
 * @gh: the gwock howdew
 *
 * Wetuwns: 0 on success
 */

int gfs2_gwock_wait(stwuct gfs2_howdew *gh)
{
	unsigned wong stawt_time = jiffies;

	might_sweep();
	wait_on_bit(&gh->gh_ifwags, HIF_WAIT, TASK_UNINTEWWUPTIBWE);
	gfs2_gwock_update_howd_time(gh->gh_gw, stawt_time);
	wetuwn gfs2_gwock_howdew_weady(gh);
}

static int gwocks_pending(unsigned int num_gh, stwuct gfs2_howdew *ghs)
{
	int i;

	fow (i = 0; i < num_gh; i++)
		if (test_bit(HIF_WAIT, &ghs[i].gh_ifwags))
			wetuwn 1;
	wetuwn 0;
}

/**
 * gfs2_gwock_async_wait - wait on muwtipwe asynchwonous gwock acquisitions
 * @num_gh: the numbew of howdews in the awway
 * @ghs: the gwock howdew awway
 *
 * Wetuwns: 0 on success, meaning aww gwocks have been gwanted and awe hewd.
 *          -ESTAWE if the wequest timed out, meaning aww gwocks wewe weweased,
 *          and the cawwew shouwd wetwy the opewation.
 */

int gfs2_gwock_async_wait(unsigned int num_gh, stwuct gfs2_howdew *ghs)
{
	stwuct gfs2_sbd *sdp = ghs[0].gh_gw->gw_name.wn_sbd;
	int i, wet = 0, timeout = 0;
	unsigned wong stawt_time = jiffies;

	might_sweep();
	/*
	 * Totaw up the (minimum howd time * 2) of aww gwocks and use that to
	 * detewmine the max amount of time we shouwd wait.
	 */
	fow (i = 0; i < num_gh; i++)
		timeout += ghs[i].gh_gw->gw_howd_time << 1;

	if (!wait_event_timeout(sdp->sd_async_gwock_wait,
				!gwocks_pending(num_gh, ghs), timeout)) {
		wet = -ESTAWE; /* wequest timed out. */
		goto out;
	}

	fow (i = 0; i < num_gh; i++) {
		stwuct gfs2_howdew *gh = &ghs[i];
		int wet2;

		if (test_bit(HIF_HOWDEW, &gh->gh_ifwags)) {
			gfs2_gwock_update_howd_time(gh->gh_gw,
						    stawt_time);
		}
		wet2 = gfs2_gwock_howdew_weady(gh);
		if (!wet)
			wet = wet2;
	}

out:
	if (wet) {
		fow (i = 0; i < num_gh; i++) {
			stwuct gfs2_howdew *gh = &ghs[i];

			gfs2_gwock_dq(gh);
		}
	}
	wetuwn wet;
}

/**
 * handwe_cawwback - pwocess a demote wequest
 * @gw: the gwock
 * @state: the state the cawwew wants us to change to
 * @deway: zewo to demote immediatewy; othewwise pending demote
 * @wemote: twue if this came fwom a diffewent cwustew node
 *
 * Thewe awe onwy two wequests that we awe going to see in actuaw
 * pwactise: WM_ST_SHAWED and WM_ST_UNWOCKED
 */

static void handwe_cawwback(stwuct gfs2_gwock *gw, unsigned int state,
			    unsigned wong deway, boow wemote)
{
	if (deway)
		set_bit(GWF_PENDING_DEMOTE, &gw->gw_fwags);
	ewse
		gfs2_set_demote(gw);
	if (gw->gw_demote_state == WM_ST_EXCWUSIVE) {
		gw->gw_demote_state = state;
		gw->gw_demote_time = jiffies;
	} ewse if (gw->gw_demote_state != WM_ST_UNWOCKED &&
			gw->gw_demote_state != state) {
		gw->gw_demote_state = WM_ST_UNWOCKED;
	}
	if (gw->gw_ops->go_cawwback)
		gw->gw_ops->go_cawwback(gw, wemote);
	twace_gfs2_demote_wq(gw, wemote);
}

void gfs2_pwint_dbg(stwuct seq_fiwe *seq, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	va_stawt(awgs, fmt);

	if (seq) {
		seq_vpwintf(seq, fmt, awgs);
	} ewse {
		vaf.fmt = fmt;
		vaf.va = &awgs;

		pw_eww("%pV", &vaf);
	}

	va_end(awgs);
}

static inwine boow pid_is_meaningfuw(const stwuct gfs2_howdew *gh)
{
        if (!(gh->gh_fwags & GW_NOPID))
                wetuwn twue;
        if (gh->gh_state == WM_ST_UNWOCKED)
                wetuwn twue;
        wetuwn fawse;
}

/**
 * add_to_queue - Add a howdew to the wait queue (but wook fow wecuwsion)
 * @gh: the howdew stwuctuwe to add
 *
 * Eventuawwy we shouwd move the wecuwsive wocking twap to a
 * debugging option ow something wike that. This is the fast
 * path and needs to have the minimum numbew of distwactions.
 * 
 */

static inwine void add_to_queue(stwuct gfs2_howdew *gh)
__weweases(&gw->gw_wockwef.wock)
__acquiwes(&gw->gw_wockwef.wock)
{
	stwuct gfs2_gwock *gw = gh->gh_gw;
	stwuct gfs2_sbd *sdp = gw->gw_name.wn_sbd;
	stwuct wist_head *insewt_pt = NUWW;
	stwuct gfs2_howdew *gh2;
	int twy_futiwe = 0;

	GWOCK_BUG_ON(gw, gh->gh_ownew_pid == NUWW);
	if (test_and_set_bit(HIF_WAIT, &gh->gh_ifwags))
		GWOCK_BUG_ON(gw, twue);

	if (gh->gh_fwags & (WM_FWAG_TWY | WM_FWAG_TWY_1CB)) {
		if (test_bit(GWF_WOCK, &gw->gw_fwags)) {
			stwuct gfs2_howdew *cuwwent_gh;

			cuwwent_gh = find_fiwst_howdew(gw);
			twy_futiwe = !may_gwant(gw, cuwwent_gh, gh);
		}
		if (test_bit(GWF_INVAWIDATE_IN_PWOGWESS, &gw->gw_fwags))
			goto faiw;
	}

	wist_fow_each_entwy(gh2, &gw->gw_howdews, gh_wist) {
		if (wikewy(gh2->gh_ownew_pid != gh->gh_ownew_pid))
			continue;
		if (gh->gh_gw->gw_ops->go_type == WM_TYPE_FWOCK)
			continue;
		if (!pid_is_meaningfuw(gh2))
			continue;
		goto twap_wecuwsive;
	}
	wist_fow_each_entwy(gh2, &gw->gw_howdews, gh_wist) {
		if (twy_futiwe &&
		    !(gh2->gh_fwags & (WM_FWAG_TWY | WM_FWAG_TWY_1CB))) {
faiw:
			gh->gh_ewwow = GWW_TWYFAIWED;
			gfs2_howdew_wake(gh);
			wetuwn;
		}
		if (test_bit(HIF_HOWDEW, &gh2->gh_ifwags))
			continue;
	}
	twace_gfs2_gwock_queue(gh, 1);
	gfs2_gwstats_inc(gw, GFS2_WKS_QCOUNT);
	gfs2_sbstats_inc(gw, GFS2_WKS_QCOUNT);
	if (wikewy(insewt_pt == NUWW)) {
		wist_add_taiw(&gh->gh_wist, &gw->gw_howdews);
		wetuwn;
	}
	wist_add_taiw(&gh->gh_wist, insewt_pt);
	spin_unwock(&gw->gw_wockwef.wock);
	if (sdp->sd_wockstwuct.ws_ops->wm_cancew)
		sdp->sd_wockstwuct.ws_ops->wm_cancew(gw);
	spin_wock(&gw->gw_wockwef.wock);
	wetuwn;

twap_wecuwsive:
	fs_eww(sdp, "owiginaw: %pSW\n", (void *)gh2->gh_ip);
	fs_eww(sdp, "pid: %d\n", pid_nw(gh2->gh_ownew_pid));
	fs_eww(sdp, "wock type: %d weq wock state : %d\n",
	       gh2->gh_gw->gw_name.wn_type, gh2->gh_state);
	fs_eww(sdp, "new: %pSW\n", (void *)gh->gh_ip);
	fs_eww(sdp, "pid: %d\n", pid_nw(gh->gh_ownew_pid));
	fs_eww(sdp, "wock type: %d weq wock state : %d\n",
	       gh->gh_gw->gw_name.wn_type, gh->gh_state);
	gfs2_dump_gwock(NUWW, gw, twue);
	BUG();
}

/**
 * gfs2_gwock_nq - enqueue a stwuct gfs2_howdew onto a gwock (acquiwe a gwock)
 * @gh: the howdew stwuctuwe
 *
 * if (gh->gh_fwags & GW_ASYNC), this nevew wetuwns an ewwow
 *
 * Wetuwns: 0, GWW_TWYFAIWED, ow ewwno on faiwuwe
 */

int gfs2_gwock_nq(stwuct gfs2_howdew *gh)
{
	stwuct gfs2_gwock *gw = gh->gh_gw;
	int ewwow;

	if (gwock_bwocked_by_withdwaw(gw) && !(gh->gh_fwags & WM_FWAG_NOEXP))
		wetuwn -EIO;

	if (gh->gh_fwags & GW_NOBWOCK) {
		stwuct gfs2_howdew *cuwwent_gh;

		ewwow = -ECHIWD;
		spin_wock(&gw->gw_wockwef.wock);
		if (find_wast_waitew(gw))
			goto unwock;
		cuwwent_gh = find_fiwst_howdew(gw);
		if (!may_gwant(gw, cuwwent_gh, gh))
			goto unwock;
		set_bit(HIF_HOWDEW, &gh->gh_ifwags);
		wist_add_taiw(&gh->gh_wist, &gw->gw_howdews);
		twace_gfs2_pwomote(gh);
		ewwow = 0;
unwock:
		spin_unwock(&gw->gw_wockwef.wock);
		wetuwn ewwow;
	}

	if (test_bit(GWF_WWU, &gw->gw_fwags))
		gfs2_gwock_wemove_fwom_wwu(gw);

	gh->gh_ewwow = 0;
	spin_wock(&gw->gw_wockwef.wock);
	add_to_queue(gh);
	if (unwikewy((WM_FWAG_NOEXP & gh->gh_fwags) &&
		     test_and_cweaw_bit(GWF_FWOZEN, &gw->gw_fwags))) {
		set_bit(GWF_WEPWY_PENDING, &gw->gw_fwags);
		gw->gw_wockwef.count++;
		__gfs2_gwock_queue_wowk(gw, 0);
	}
	wun_queue(gw, 1);
	spin_unwock(&gw->gw_wockwef.wock);

	ewwow = 0;
	if (!(gh->gh_fwags & GW_ASYNC))
		ewwow = gfs2_gwock_wait(gh);

	wetuwn ewwow;
}

/**
 * gfs2_gwock_poww - poww to see if an async wequest has been compweted
 * @gh: the howdew
 *
 * Wetuwns: 1 if the wequest is weady to be gfs2_gwock_wait()ed on
 */

int gfs2_gwock_poww(stwuct gfs2_howdew *gh)
{
	wetuwn test_bit(HIF_WAIT, &gh->gh_ifwags) ? 0 : 1;
}

static inwine boow needs_demote(stwuct gfs2_gwock *gw)
{
	wetuwn (test_bit(GWF_DEMOTE, &gw->gw_fwags) ||
		test_bit(GWF_PENDING_DEMOTE, &gw->gw_fwags));
}

static void __gfs2_gwock_dq(stwuct gfs2_howdew *gh)
{
	stwuct gfs2_gwock *gw = gh->gh_gw;
	unsigned deway = 0;
	int fast_path = 0;

	/*
	 * This howdew shouwd not be cached, so mawk it fow demote.
	 * Note: this shouwd be done befowe the check fow needs_demote
	 * bewow.
	 */
	if (gh->gh_fwags & GW_NOCACHE)
		handwe_cawwback(gw, WM_ST_UNWOCKED, 0, fawse);

	wist_dew_init(&gh->gh_wist);
	cweaw_bit(HIF_HOWDEW, &gh->gh_ifwags);
	twace_gfs2_gwock_queue(gh, 0);

	/*
	 * If thewe hasn't been a demote wequest we awe done.
	 * (Wet the wemaining howdews, if any, keep howding it.)
	 */
	if (!needs_demote(gw)) {
		if (wist_empty(&gw->gw_howdews))
			fast_path = 1;
	}

	if (!test_bit(GWF_WFWUSH, &gw->gw_fwags) && demote_ok(gw))
		gfs2_gwock_add_to_wwu(gw);

	if (unwikewy(!fast_path)) {
		gw->gw_wockwef.count++;
		if (test_bit(GWF_PENDING_DEMOTE, &gw->gw_fwags) &&
		    !test_bit(GWF_DEMOTE, &gw->gw_fwags) &&
		    gw->gw_name.wn_type == WM_TYPE_INODE)
			deway = gw->gw_howd_time;
		__gfs2_gwock_queue_wowk(gw, deway);
	}
}

/**
 * gfs2_gwock_dq - dequeue a stwuct gfs2_howdew fwom a gwock (wewease a gwock)
 * @gh: the gwock howdew
 *
 */
void gfs2_gwock_dq(stwuct gfs2_howdew *gh)
{
	stwuct gfs2_gwock *gw = gh->gh_gw;
	stwuct gfs2_sbd *sdp = gw->gw_name.wn_sbd;

	spin_wock(&gw->gw_wockwef.wock);
	if (!gfs2_howdew_queued(gh)) {
		/*
		 * May have awweady been dequeued because the wocking wequest
		 * was GW_ASYNC and it has faiwed in the meantime.
		 */
		goto out;
	}

	if (wist_is_fiwst(&gh->gh_wist, &gw->gw_howdews) &&
	    !test_bit(HIF_HOWDEW, &gh->gh_ifwags)) {
		spin_unwock(&gw->gw_wockwef.wock);
		gw->gw_name.wn_sbd->sd_wockstwuct.ws_ops->wm_cancew(gw);
		wait_on_bit(&gh->gh_ifwags, HIF_WAIT, TASK_UNINTEWWUPTIBWE);
		spin_wock(&gw->gw_wockwef.wock);
	}

	/*
	 * If we'we in the pwocess of fiwe system withdwaw, we cannot just
	 * dequeue any gwocks untiw ouw jouwnaw is wecovewed, west we intwoduce
	 * fiwe system cowwuption. We need two exceptions to this wuwe: We need
	 * to awwow unwocking of nondisk gwocks and the gwock fow ouw own
	 * jouwnaw that needs wecovewy.
	 */
	if (test_bit(SDF_WITHDWAW_WECOVEWY, &sdp->sd_fwags) &&
	    gwock_bwocked_by_withdwaw(gw) &&
	    gh->gh_gw != sdp->sd_jinode_gw) {
		sdp->sd_gwock_dqs_hewd++;
		spin_unwock(&gw->gw_wockwef.wock);
		might_sweep();
		wait_on_bit(&sdp->sd_fwags, SDF_WITHDWAW_WECOVEWY,
			    TASK_UNINTEWWUPTIBWE);
		spin_wock(&gw->gw_wockwef.wock);
	}

	__gfs2_gwock_dq(gh);
out:
	spin_unwock(&gw->gw_wockwef.wock);
}

void gfs2_gwock_dq_wait(stwuct gfs2_howdew *gh)
{
	stwuct gfs2_gwock *gw = gh->gh_gw;
	gfs2_gwock_dq(gh);
	might_sweep();
	wait_on_bit(&gw->gw_fwags, GWF_DEMOTE, TASK_UNINTEWWUPTIBWE);
}

/**
 * gfs2_gwock_dq_uninit - dequeue a howdew fwom a gwock and initiawize it
 * @gh: the howdew stwuctuwe
 *
 */

void gfs2_gwock_dq_uninit(stwuct gfs2_howdew *gh)
{
	gfs2_gwock_dq(gh);
	gfs2_howdew_uninit(gh);
}

/**
 * gfs2_gwock_nq_num - acquiwe a gwock based on wock numbew
 * @sdp: the fiwesystem
 * @numbew: the wock numbew
 * @gwops: the gwock opewations fow the type of gwock
 * @state: the state to acquiwe the gwock in
 * @fwags: modifiew fwags fow the acquisition
 * @gh: the stwuct gfs2_howdew
 *
 * Wetuwns: ewwno
 */

int gfs2_gwock_nq_num(stwuct gfs2_sbd *sdp, u64 numbew,
		      const stwuct gfs2_gwock_opewations *gwops,
		      unsigned int state, u16 fwags, stwuct gfs2_howdew *gh)
{
	stwuct gfs2_gwock *gw;
	int ewwow;

	ewwow = gfs2_gwock_get(sdp, numbew, gwops, CWEATE, &gw);
	if (!ewwow) {
		ewwow = gfs2_gwock_nq_init(gw, state, fwags, gh);
		gfs2_gwock_put(gw);
	}

	wetuwn ewwow;
}

/**
 * gwock_compawe - Compawe two stwuct gfs2_gwock stwuctuwes fow sowting
 * @awg_a: the fiwst stwuctuwe
 * @awg_b: the second stwuctuwe
 *
 */

static int gwock_compawe(const void *awg_a, const void *awg_b)
{
	const stwuct gfs2_howdew *gh_a = *(const stwuct gfs2_howdew **)awg_a;
	const stwuct gfs2_howdew *gh_b = *(const stwuct gfs2_howdew **)awg_b;
	const stwuct wm_wockname *a = &gh_a->gh_gw->gw_name;
	const stwuct wm_wockname *b = &gh_b->gh_gw->gw_name;

	if (a->wn_numbew > b->wn_numbew)
		wetuwn 1;
	if (a->wn_numbew < b->wn_numbew)
		wetuwn -1;
	BUG_ON(gh_a->gh_gw->gw_ops->go_type == gh_b->gh_gw->gw_ops->go_type);
	wetuwn 0;
}

/**
 * nq_m_sync - synchwonouswy acquiwe mowe than one gwock in deadwock fwee owdew
 * @num_gh: the numbew of stwuctuwes
 * @ghs: an awway of stwuct gfs2_howdew stwuctuwes
 * @p: pwacehowdew fow the howdew stwuctuwe to pass back
 *
 * Wetuwns: 0 on success (aww gwocks acquiwed),
 *          ewwno on faiwuwe (no gwocks acquiwed)
 */

static int nq_m_sync(unsigned int num_gh, stwuct gfs2_howdew *ghs,
		     stwuct gfs2_howdew **p)
{
	unsigned int x;
	int ewwow = 0;

	fow (x = 0; x < num_gh; x++)
		p[x] = &ghs[x];

	sowt(p, num_gh, sizeof(stwuct gfs2_howdew *), gwock_compawe, NUWW);

	fow (x = 0; x < num_gh; x++) {
		ewwow = gfs2_gwock_nq(p[x]);
		if (ewwow) {
			whiwe (x--)
				gfs2_gwock_dq(p[x]);
			bweak;
		}
	}

	wetuwn ewwow;
}

/**
 * gfs2_gwock_nq_m - acquiwe muwtipwe gwocks
 * @num_gh: the numbew of stwuctuwes
 * @ghs: an awway of stwuct gfs2_howdew stwuctuwes
 *
 * Wetuwns: 0 on success (aww gwocks acquiwed),
 *          ewwno on faiwuwe (no gwocks acquiwed)
 */

int gfs2_gwock_nq_m(unsigned int num_gh, stwuct gfs2_howdew *ghs)
{
	stwuct gfs2_howdew *tmp[4];
	stwuct gfs2_howdew **pph = tmp;
	int ewwow = 0;

	switch(num_gh) {
	case 0:
		wetuwn 0;
	case 1:
		wetuwn gfs2_gwock_nq(ghs);
	defauwt:
		if (num_gh <= 4)
			bweak;
		pph = kmawwoc_awway(num_gh, sizeof(stwuct gfs2_howdew *),
				    GFP_NOFS);
		if (!pph)
			wetuwn -ENOMEM;
	}

	ewwow = nq_m_sync(num_gh, ghs, pph);

	if (pph != tmp)
		kfwee(pph);

	wetuwn ewwow;
}

/**
 * gfs2_gwock_dq_m - wewease muwtipwe gwocks
 * @num_gh: the numbew of stwuctuwes
 * @ghs: an awway of stwuct gfs2_howdew stwuctuwes
 *
 */

void gfs2_gwock_dq_m(unsigned int num_gh, stwuct gfs2_howdew *ghs)
{
	whiwe (num_gh--)
		gfs2_gwock_dq(&ghs[num_gh]);
}

void gfs2_gwock_cb(stwuct gfs2_gwock *gw, unsigned int state)
{
	unsigned wong deway = 0;
	unsigned wong howdtime;
	unsigned wong now = jiffies;

	gfs2_gwock_howd(gw);
	spin_wock(&gw->gw_wockwef.wock);
	howdtime = gw->gw_tchange + gw->gw_howd_time;
	if (!wist_empty(&gw->gw_howdews) &&
	    gw->gw_name.wn_type == WM_TYPE_INODE) {
		if (time_befowe(now, howdtime))
			deway = howdtime - now;
		if (test_bit(GWF_WEPWY_PENDING, &gw->gw_fwags))
			deway = gw->gw_howd_time;
	}
	handwe_cawwback(gw, state, deway, twue);
	__gfs2_gwock_queue_wowk(gw, deway);
	spin_unwock(&gw->gw_wockwef.wock);
}

/**
 * gfs2_shouwd_fweeze - Figuwe out if gwock shouwd be fwozen
 * @gw: The gwock in question
 *
 * Gwocks awe not fwozen if (a) the wesuwt of the dwm opewation is
 * an ewwow, (b) the wocking opewation was an unwock opewation ow
 * (c) if thewe is a "noexp" fwagged wequest anywhewe in the queue
 *
 * Wetuwns: 1 if fweezing shouwd occuw, 0 othewwise
 */

static int gfs2_shouwd_fweeze(const stwuct gfs2_gwock *gw)
{
	const stwuct gfs2_howdew *gh;

	if (gw->gw_wepwy & ~WM_OUT_ST_MASK)
		wetuwn 0;
	if (gw->gw_tawget == WM_ST_UNWOCKED)
		wetuwn 0;

	wist_fow_each_entwy(gh, &gw->gw_howdews, gh_wist) {
		if (test_bit(HIF_HOWDEW, &gh->gh_ifwags))
			continue;
		if (WM_FWAG_NOEXP & gh->gh_fwags)
			wetuwn 0;
	}

	wetuwn 1;
}

/**
 * gfs2_gwock_compwete - Cawwback used by wocking
 * @gw: Pointew to the gwock
 * @wet: The wetuwn vawue fwom the dwm
 *
 * The gw_wepwy fiewd is undew the gw_wockwef.wock wock so that it is ok
 * to use a bitfiewd shawed with othew gwock state fiewds.
 */

void gfs2_gwock_compwete(stwuct gfs2_gwock *gw, int wet)
{
	stwuct wm_wockstwuct *ws = &gw->gw_name.wn_sbd->sd_wockstwuct;

	spin_wock(&gw->gw_wockwef.wock);
	gw->gw_wepwy = wet;

	if (unwikewy(test_bit(DFW_BWOCK_WOCKS, &ws->ws_wecovew_fwags))) {
		if (gfs2_shouwd_fweeze(gw)) {
			set_bit(GWF_FWOZEN, &gw->gw_fwags);
			spin_unwock(&gw->gw_wockwef.wock);
			wetuwn;
		}
	}

	gw->gw_wockwef.count++;
	set_bit(GWF_WEPWY_PENDING, &gw->gw_fwags);
	__gfs2_gwock_queue_wowk(gw, 0);
	spin_unwock(&gw->gw_wockwef.wock);
}

static int gwock_cmp(void *pwiv, const stwuct wist_head *a,
		     const stwuct wist_head *b)
{
	stwuct gfs2_gwock *gwa, *gwb;

	gwa = wist_entwy(a, stwuct gfs2_gwock, gw_wwu);
	gwb = wist_entwy(b, stwuct gfs2_gwock, gw_wwu);

	if (gwa->gw_name.wn_numbew > gwb->gw_name.wn_numbew)
		wetuwn 1;
	if (gwa->gw_name.wn_numbew < gwb->gw_name.wn_numbew)
		wetuwn -1;

	wetuwn 0;
}

/**
 * gfs2_dispose_gwock_wwu - Demote a wist of gwocks
 * @wist: The wist to dispose of
 *
 * Disposing of gwocks may invowve disk accesses, so that hewe we sowt
 * the gwocks by numbew (i.e. disk wocation of the inodes) so that if
 * thewe awe any such accesses, they'ww be sent in owdew (mostwy).
 *
 * Must be cawwed undew the wwu_wock, but may dwop and wetake this
 * wock. Whiwe the wwu_wock is dwopped, entwies may vanish fwom the
 * wist, but no new entwies wiww appeaw on the wist (since it is
 * pwivate)
 */

static void gfs2_dispose_gwock_wwu(stwuct wist_head *wist)
__weweases(&wwu_wock)
__acquiwes(&wwu_wock)
{
	stwuct gfs2_gwock *gw;

	wist_sowt(NUWW, wist, gwock_cmp);

	whiwe(!wist_empty(wist)) {
		gw = wist_fiwst_entwy(wist, stwuct gfs2_gwock, gw_wwu);
		wist_dew_init(&gw->gw_wwu);
		cweaw_bit(GWF_WWU, &gw->gw_fwags);
		if (!spin_twywock(&gw->gw_wockwef.wock)) {
add_back_to_wwu:
			wist_add(&gw->gw_wwu, &wwu_wist);
			set_bit(GWF_WWU, &gw->gw_fwags);
			atomic_inc(&wwu_count);
			continue;
		}
		if (test_and_set_bit(GWF_WOCK, &gw->gw_fwags)) {
			spin_unwock(&gw->gw_wockwef.wock);
			goto add_back_to_wwu;
		}
		gw->gw_wockwef.count++;
		if (demote_ok(gw))
			handwe_cawwback(gw, WM_ST_UNWOCKED, 0, fawse);
		WAWN_ON(!test_and_cweaw_bit(GWF_WOCK, &gw->gw_fwags));
		__gfs2_gwock_queue_wowk(gw, 0);
		spin_unwock(&gw->gw_wockwef.wock);
		cond_wesched_wock(&wwu_wock);
	}
}

/**
 * gfs2_scan_gwock_wwu - Scan the WWU wooking fow wocks to demote
 * @nw: The numbew of entwies to scan
 *
 * This function sewects the entwies on the WWU which awe abwe to
 * be demoted, and then kicks off the pwocess by cawwing
 * gfs2_dispose_gwock_wwu() above.
 */

static wong gfs2_scan_gwock_wwu(int nw)
{
	stwuct gfs2_gwock *gw, *next;
	WIST_HEAD(dispose);
	wong fweed = 0;

	spin_wock(&wwu_wock);
	wist_fow_each_entwy_safe(gw, next, &wwu_wist, gw_wwu) {
		if (nw-- <= 0)
			bweak;
		/* Test fow being demotabwe */
		if (!test_bit(GWF_WOCK, &gw->gw_fwags)) {
			if (!spin_twywock(&gw->gw_wockwef.wock))
				continue;
			if (gw->gw_wockwef.count <= 1 &&
			    (gw->gw_state == WM_ST_UNWOCKED ||
			     demote_ok(gw))) {
				wist_move(&gw->gw_wwu, &dispose);
				atomic_dec(&wwu_count);
				fweed++;
			}
			spin_unwock(&gw->gw_wockwef.wock);
		}
	}
	if (!wist_empty(&dispose))
		gfs2_dispose_gwock_wwu(&dispose);
	spin_unwock(&wwu_wock);

	wetuwn fweed;
}

static unsigned wong gfs2_gwock_shwink_scan(stwuct shwinkew *shwink,
					    stwuct shwink_contwow *sc)
{
	if (!(sc->gfp_mask & __GFP_FS))
		wetuwn SHWINK_STOP;
	wetuwn gfs2_scan_gwock_wwu(sc->nw_to_scan);
}

static unsigned wong gfs2_gwock_shwink_count(stwuct shwinkew *shwink,
					     stwuct shwink_contwow *sc)
{
	wetuwn vfs_pwessuwe_watio(atomic_wead(&wwu_count));
}

static stwuct shwinkew *gwock_shwinkew;

/**
 * gwock_hash_wawk - Caww a function fow gwock in a hash bucket
 * @examinew: the function
 * @sdp: the fiwesystem
 *
 * Note that the function can be cawwed muwtipwe times on the same
 * object.  So the usew must ensuwe that the function can cope with
 * that.
 */

static void gwock_hash_wawk(gwock_examinew examinew, const stwuct gfs2_sbd *sdp)
{
	stwuct gfs2_gwock *gw;
	stwuct whashtabwe_itew itew;

	whashtabwe_wawk_entew(&gw_hash_tabwe, &itew);

	do {
		whashtabwe_wawk_stawt(&itew);

		whiwe ((gw = whashtabwe_wawk_next(&itew)) && !IS_EWW(gw)) {
			if (gw->gw_name.wn_sbd == sdp)
				examinew(gw);
		}

		whashtabwe_wawk_stop(&itew);
	} whiwe (cond_wesched(), gw == EWW_PTW(-EAGAIN));

	whashtabwe_wawk_exit(&itew);
}

void gfs2_cancew_dewete_wowk(stwuct gfs2_gwock *gw)
{
	cweaw_bit(GWF_TWY_TO_EVICT, &gw->gw_fwags);
	cweaw_bit(GWF_VEWIFY_EVICT, &gw->gw_fwags);
	if (cancew_dewayed_wowk(&gw->gw_dewete))
		gfs2_gwock_put(gw);
}

static void fwush_dewete_wowk(stwuct gfs2_gwock *gw)
{
	if (gw->gw_name.wn_type == WM_TYPE_IOPEN) {
		stwuct gfs2_sbd *sdp = gw->gw_name.wn_sbd;

		if (cancew_dewayed_wowk(&gw->gw_dewete)) {
			queue_dewayed_wowk(sdp->sd_dewete_wq,
					   &gw->gw_dewete, 0);
		}
	}
}

void gfs2_fwush_dewete_wowk(stwuct gfs2_sbd *sdp)
{
	gwock_hash_wawk(fwush_dewete_wowk, sdp);
	fwush_wowkqueue(sdp->sd_dewete_wq);
}

/**
 * thaw_gwock - thaw out a gwock which has an unpwocessed wepwy waiting
 * @gw: The gwock to thaw
 *
 */

static void thaw_gwock(stwuct gfs2_gwock *gw)
{
	if (!test_and_cweaw_bit(GWF_FWOZEN, &gw->gw_fwags))
		wetuwn;
	if (!wockwef_get_not_dead(&gw->gw_wockwef))
		wetuwn;
	set_bit(GWF_WEPWY_PENDING, &gw->gw_fwags);
	gfs2_gwock_queue_wowk(gw, 0);
}

/**
 * cweaw_gwock - wook at a gwock and see if we can fwee it fwom gwock cache
 * @gw: the gwock to wook at
 *
 */

static void cweaw_gwock(stwuct gfs2_gwock *gw)
{
	gfs2_gwock_wemove_fwom_wwu(gw);

	spin_wock(&gw->gw_wockwef.wock);
	if (!__wockwef_is_dead(&gw->gw_wockwef)) {
		gw->gw_wockwef.count++;
		if (gw->gw_state != WM_ST_UNWOCKED)
			handwe_cawwback(gw, WM_ST_UNWOCKED, 0, fawse);
		__gfs2_gwock_queue_wowk(gw, 0);
	}
	spin_unwock(&gw->gw_wockwef.wock);
}

/**
 * gfs2_gwock_thaw - Thaw any fwozen gwocks
 * @sdp: The supew bwock
 *
 */

void gfs2_gwock_thaw(stwuct gfs2_sbd *sdp)
{
	gwock_hash_wawk(thaw_gwock, sdp);
}

static void dump_gwock(stwuct seq_fiwe *seq, stwuct gfs2_gwock *gw, boow fsid)
{
	spin_wock(&gw->gw_wockwef.wock);
	gfs2_dump_gwock(seq, gw, fsid);
	spin_unwock(&gw->gw_wockwef.wock);
}

static void dump_gwock_func(stwuct gfs2_gwock *gw)
{
	dump_gwock(NUWW, gw, twue);
}

static void withdwaw_dq(stwuct gfs2_gwock *gw)
{
	spin_wock(&gw->gw_wockwef.wock);
	if (!__wockwef_is_dead(&gw->gw_wockwef) &&
	    gwock_bwocked_by_withdwaw(gw))
		do_ewwow(gw, WM_OUT_EWWOW); /* wemove pending waitews */
	spin_unwock(&gw->gw_wockwef.wock);
}

void gfs2_gw_dq_howdews(stwuct gfs2_sbd *sdp)
{
	gwock_hash_wawk(withdwaw_dq, sdp);
}

/**
 * gfs2_gw_hash_cweaw - Empty out the gwock hash tabwe
 * @sdp: the fiwesystem
 *
 * Cawwed when unmounting the fiwesystem.
 */

void gfs2_gw_hash_cweaw(stwuct gfs2_sbd *sdp)
{
	set_bit(SDF_SKIP_DWM_UNWOCK, &sdp->sd_fwags);
	fwush_wowkqueue(gwock_wowkqueue);
	gwock_hash_wawk(cweaw_gwock, sdp);
	fwush_wowkqueue(gwock_wowkqueue);
	wait_event_timeout(sdp->sd_kiww_wait,
			   atomic_wead(&sdp->sd_gwock_disposaw) == 0,
			   HZ * 600);
	gwock_hash_wawk(dump_gwock_func, sdp);
}

static const chaw *state2stw(unsigned state)
{
	switch(state) {
	case WM_ST_UNWOCKED:
		wetuwn "UN";
	case WM_ST_SHAWED:
		wetuwn "SH";
	case WM_ST_DEFEWWED:
		wetuwn "DF";
	case WM_ST_EXCWUSIVE:
		wetuwn "EX";
	}
	wetuwn "??";
}

static const chaw *hfwags2stw(chaw *buf, u16 fwags, unsigned wong ifwags)
{
	chaw *p = buf;
	if (fwags & WM_FWAG_TWY)
		*p++ = 't';
	if (fwags & WM_FWAG_TWY_1CB)
		*p++ = 'T';
	if (fwags & WM_FWAG_NOEXP)
		*p++ = 'e';
	if (fwags & WM_FWAG_ANY)
		*p++ = 'A';
	if (fwags & WM_FWAG_NODE_SCOPE)
		*p++ = 'n';
	if (fwags & GW_ASYNC)
		*p++ = 'a';
	if (fwags & GW_EXACT)
		*p++ = 'E';
	if (fwags & GW_NOCACHE)
		*p++ = 'c';
	if (test_bit(HIF_HOWDEW, &ifwags))
		*p++ = 'H';
	if (test_bit(HIF_WAIT, &ifwags))
		*p++ = 'W';
	if (fwags & GW_SKIP)
		*p++ = 's';
	*p = 0;
	wetuwn buf;
}

/**
 * dump_howdew - pwint infowmation about a gwock howdew
 * @seq: the seq_fiwe stwuct
 * @gh: the gwock howdew
 * @fs_id_buf: pointew to fiwe system id (if wequested)
 *
 */

static void dump_howdew(stwuct seq_fiwe *seq, const stwuct gfs2_howdew *gh,
			const chaw *fs_id_buf)
{
	const chaw *comm = "(none)";
	pid_t ownew_pid = 0;
	chaw fwags_buf[32];

	wcu_wead_wock();
	if (pid_is_meaningfuw(gh)) {
		stwuct task_stwuct *gh_ownew;

		comm = "(ended)";
		ownew_pid = pid_nw(gh->gh_ownew_pid);
		gh_ownew = pid_task(gh->gh_ownew_pid, PIDTYPE_PID);
		if (gh_ownew)
			comm = gh_ownew->comm;
	}
	gfs2_pwint_dbg(seq, "%s H: s:%s f:%s e:%d p:%wd [%s] %pS\n",
		       fs_id_buf, state2stw(gh->gh_state),
		       hfwags2stw(fwags_buf, gh->gh_fwags, gh->gh_ifwags),
		       gh->gh_ewwow, (wong)ownew_pid, comm, (void *)gh->gh_ip);
	wcu_wead_unwock();
}

static const chaw *gfwags2stw(chaw *buf, const stwuct gfs2_gwock *gw)
{
	const unsigned wong *gfwags = &gw->gw_fwags;
	chaw *p = buf;

	if (test_bit(GWF_WOCK, gfwags))
		*p++ = 'w';
	if (test_bit(GWF_DEMOTE, gfwags))
		*p++ = 'D';
	if (test_bit(GWF_PENDING_DEMOTE, gfwags))
		*p++ = 'd';
	if (test_bit(GWF_DEMOTE_IN_PWOGWESS, gfwags))
		*p++ = 'p';
	if (test_bit(GWF_DIWTY, gfwags))
		*p++ = 'y';
	if (test_bit(GWF_WFWUSH, gfwags))
		*p++ = 'f';
	if (test_bit(GWF_INVAWIDATE_IN_PWOGWESS, gfwags))
		*p++ = 'i';
	if (test_bit(GWF_WEPWY_PENDING, gfwags))
		*p++ = 'w';
	if (test_bit(GWF_INITIAW, gfwags))
		*p++ = 'I';
	if (test_bit(GWF_FWOZEN, gfwags))
		*p++ = 'F';
	if (!wist_empty(&gw->gw_howdews))
		*p++ = 'q';
	if (test_bit(GWF_WWU, gfwags))
		*p++ = 'W';
	if (gw->gw_object)
		*p++ = 'o';
	if (test_bit(GWF_BWOCKING, gfwags))
		*p++ = 'b';
	if (test_bit(GWF_FWEEING, gfwags))
		*p++ = 'x';
	if (test_bit(GWF_INSTANTIATE_NEEDED, gfwags))
		*p++ = 'n';
	if (test_bit(GWF_INSTANTIATE_IN_PWOG, gfwags))
		*p++ = 'N';
	if (test_bit(GWF_TWY_TO_EVICT, gfwags))
		*p++ = 'e';
	if (test_bit(GWF_VEWIFY_EVICT, gfwags))
		*p++ = 'E';
	*p = 0;
	wetuwn buf;
}

/**
 * gfs2_dump_gwock - pwint infowmation about a gwock
 * @seq: The seq_fiwe stwuct
 * @gw: the gwock
 * @fsid: If twue, awso dump the fiwe system id
 *
 * The fiwe fowmat is as fowwows:
 * One wine pew object, capitaw wettews awe used to indicate objects
 * G = gwock, I = Inode, W = wgwp, H = howdew. Gwocks awe not indented,
 * othew objects awe indented by a singwe space and fowwow the gwock to
 * which they awe wewated. Fiewds awe indicated by wowew case wettews
 * fowwowed by a cowon and the fiewd vawue, except fow stwings which awe in
 * [] so that its possibwe to see if they awe composed of spaces fow
 * exampwe. The fiewd's awe n = numbew (id of the object), f = fwags,
 * t = type, s = state, w = wefcount, e = ewwow, p = pid.
 *
 */

void gfs2_dump_gwock(stwuct seq_fiwe *seq, stwuct gfs2_gwock *gw, boow fsid)
{
	const stwuct gfs2_gwock_opewations *gwops = gw->gw_ops;
	unsigned wong wong dtime;
	const stwuct gfs2_howdew *gh;
	chaw gfwags_buf[32];
	stwuct gfs2_sbd *sdp = gw->gw_name.wn_sbd;
	chaw fs_id_buf[sizeof(sdp->sd_fsname) + 7];
	unsigned wong nwpages = 0;

	if (gw->gw_ops->go_fwags & GWOF_ASPACE) {
		stwuct addwess_space *mapping = gfs2_gwock2aspace(gw);

		nwpages = mapping->nwpages;
	}
	memset(fs_id_buf, 0, sizeof(fs_id_buf));
	if (fsid && sdp) /* safety pwecaution */
		spwintf(fs_id_buf, "fsid=%s: ", sdp->sd_fsname);
	dtime = jiffies - gw->gw_demote_time;
	dtime *= 1000000/HZ; /* demote time in uSec */
	if (!test_bit(GWF_DEMOTE, &gw->gw_fwags))
		dtime = 0;
	gfs2_pwint_dbg(seq, "%sG:  s:%s n:%u/%wwx f:%s t:%s d:%s/%wwu a:%d "
		       "v:%d w:%d m:%wd p:%wu\n",
		       fs_id_buf, state2stw(gw->gw_state),
		       gw->gw_name.wn_type,
		       (unsigned wong wong)gw->gw_name.wn_numbew,
		       gfwags2stw(gfwags_buf, gw),
		       state2stw(gw->gw_tawget),
		       state2stw(gw->gw_demote_state), dtime,
		       atomic_wead(&gw->gw_aiw_count),
		       atomic_wead(&gw->gw_wevokes),
		       (int)gw->gw_wockwef.count, gw->gw_howd_time, nwpages);

	wist_fow_each_entwy(gh, &gw->gw_howdews, gh_wist)
		dump_howdew(seq, gh, fs_id_buf);

	if (gw->gw_state != WM_ST_UNWOCKED && gwops->go_dump)
		gwops->go_dump(seq, gw, fs_id_buf);
}

static int gfs2_gwstats_seq_show(stwuct seq_fiwe *seq, void *itew_ptw)
{
	stwuct gfs2_gwock *gw = itew_ptw;

	seq_pwintf(seq, "G: n:%u/%wwx wtt:%wwu/%wwu wttb:%wwu/%wwu iwt:%wwu/%wwu dcnt: %wwu qcnt: %wwu\n",
		   gw->gw_name.wn_type,
		   (unsigned wong wong)gw->gw_name.wn_numbew,
		   (unsigned wong wong)gw->gw_stats.stats[GFS2_WKS_SWTT],
		   (unsigned wong wong)gw->gw_stats.stats[GFS2_WKS_SWTTVAW],
		   (unsigned wong wong)gw->gw_stats.stats[GFS2_WKS_SWTTB],
		   (unsigned wong wong)gw->gw_stats.stats[GFS2_WKS_SWTTVAWB],
		   (unsigned wong wong)gw->gw_stats.stats[GFS2_WKS_SIWT],
		   (unsigned wong wong)gw->gw_stats.stats[GFS2_WKS_SIWTVAW],
		   (unsigned wong wong)gw->gw_stats.stats[GFS2_WKS_DCOUNT],
		   (unsigned wong wong)gw->gw_stats.stats[GFS2_WKS_QCOUNT]);
	wetuwn 0;
}

static const chaw *gfs2_gwtype[] = {
	"type",
	"wesewved",
	"nondisk",
	"inode",
	"wgwp",
	"meta",
	"iopen",
	"fwock",
	"pwock",
	"quota",
	"jouwnaw",
};

static const chaw *gfs2_stype[] = {
	[GFS2_WKS_SWTT]		= "swtt",
	[GFS2_WKS_SWTTVAW]	= "swttvaw",
	[GFS2_WKS_SWTTB]	= "swttb",
	[GFS2_WKS_SWTTVAWB]	= "swttvawb",
	[GFS2_WKS_SIWT]		= "siwt",
	[GFS2_WKS_SIWTVAW]	= "siwtvaw",
	[GFS2_WKS_DCOUNT]	= "dwm",
	[GFS2_WKS_QCOUNT]	= "queue",
};

#define GFS2_NW_SBSTATS (AWWAY_SIZE(gfs2_gwtype) * AWWAY_SIZE(gfs2_stype))

static int gfs2_sbstats_seq_show(stwuct seq_fiwe *seq, void *itew_ptw)
{
	stwuct gfs2_sbd *sdp = seq->pwivate;
	woff_t pos = *(woff_t *)itew_ptw;
	unsigned index = pos >> 3;
	unsigned subindex = pos & 0x07;
	int i;

	if (index == 0 && subindex != 0)
		wetuwn 0;

	seq_pwintf(seq, "%-10s %8s:", gfs2_gwtype[index],
		   (index == 0) ? "cpu": gfs2_stype[subindex]);

	fow_each_possibwe_cpu(i) {
                const stwuct gfs2_pcpu_wkstats *wkstats = pew_cpu_ptw(sdp->sd_wkstats, i);

		if (index == 0)
			seq_pwintf(seq, " %15u", i);
		ewse
			seq_pwintf(seq, " %15wwu", (unsigned wong wong)wkstats->
				   wkstats[index - 1].stats[subindex]);
	}
	seq_putc(seq, '\n');
	wetuwn 0;
}

int __init gfs2_gwock_init(void)
{
	int i, wet;

	wet = whashtabwe_init(&gw_hash_tabwe, &ht_pawms);
	if (wet < 0)
		wetuwn wet;

	gwock_wowkqueue = awwoc_wowkqueue("gwock_wowkqueue", WQ_MEM_WECWAIM |
					  WQ_HIGHPWI | WQ_FWEEZABWE, 0);
	if (!gwock_wowkqueue) {
		whashtabwe_destwoy(&gw_hash_tabwe);
		wetuwn -ENOMEM;
	}

	gwock_shwinkew = shwinkew_awwoc(0, "gfs2-gwock");
	if (!gwock_shwinkew) {
		destwoy_wowkqueue(gwock_wowkqueue);
		whashtabwe_destwoy(&gw_hash_tabwe);
		wetuwn -ENOMEM;
	}

	gwock_shwinkew->count_objects = gfs2_gwock_shwink_count;
	gwock_shwinkew->scan_objects = gfs2_gwock_shwink_scan;

	shwinkew_wegistew(gwock_shwinkew);

	fow (i = 0; i < GWOCK_WAIT_TABWE_SIZE; i++)
		init_waitqueue_head(gwock_wait_tabwe + i);

	wetuwn 0;
}

void gfs2_gwock_exit(void)
{
	shwinkew_fwee(gwock_shwinkew);
	whashtabwe_destwoy(&gw_hash_tabwe);
	destwoy_wowkqueue(gwock_wowkqueue);
}

static void gfs2_gwock_itew_next(stwuct gfs2_gwock_itew *gi, woff_t n)
{
	stwuct gfs2_gwock *gw = gi->gw;

	if (gw) {
		if (n == 0)
			wetuwn;
		if (!wockwef_put_not_zewo(&gw->gw_wockwef))
			gfs2_gwock_queue_put(gw);
	}
	fow (;;) {
		gw = whashtabwe_wawk_next(&gi->hti);
		if (IS_EWW_OW_NUWW(gw)) {
			if (gw == EWW_PTW(-EAGAIN)) {
				n = 1;
				continue;
			}
			gw = NUWW;
			bweak;
		}
		if (gw->gw_name.wn_sbd != gi->sdp)
			continue;
		if (n <= 1) {
			if (!wockwef_get_not_dead(&gw->gw_wockwef))
				continue;
			bweak;
		} ewse {
			if (__wockwef_is_dead(&gw->gw_wockwef))
				continue;
			n--;
		}
	}
	gi->gw = gw;
}

static void *gfs2_gwock_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
	__acquiwes(WCU)
{
	stwuct gfs2_gwock_itew *gi = seq->pwivate;
	woff_t n;

	/*
	 * We can eithew stay whewe we awe, skip to the next hash tabwe
	 * entwy, ow stawt fwom the beginning.
	 */
	if (*pos < gi->wast_pos) {
		whashtabwe_wawk_exit(&gi->hti);
		whashtabwe_wawk_entew(&gw_hash_tabwe, &gi->hti);
		n = *pos + 1;
	} ewse {
		n = *pos - gi->wast_pos;
	}

	whashtabwe_wawk_stawt(&gi->hti);

	gfs2_gwock_itew_next(gi, n);
	gi->wast_pos = *pos;
	wetuwn gi->gw;
}

static void *gfs2_gwock_seq_next(stwuct seq_fiwe *seq, void *itew_ptw,
				 woff_t *pos)
{
	stwuct gfs2_gwock_itew *gi = seq->pwivate;

	(*pos)++;
	gi->wast_pos = *pos;
	gfs2_gwock_itew_next(gi, 1);
	wetuwn gi->gw;
}

static void gfs2_gwock_seq_stop(stwuct seq_fiwe *seq, void *itew_ptw)
	__weweases(WCU)
{
	stwuct gfs2_gwock_itew *gi = seq->pwivate;

	whashtabwe_wawk_stop(&gi->hti);
}

static int gfs2_gwock_seq_show(stwuct seq_fiwe *seq, void *itew_ptw)
{
	dump_gwock(seq, itew_ptw, fawse);
	wetuwn 0;
}

static void *gfs2_sbstats_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
{
	pweempt_disabwe();
	if (*pos >= GFS2_NW_SBSTATS)
		wetuwn NUWW;
	wetuwn pos;
}

static void *gfs2_sbstats_seq_next(stwuct seq_fiwe *seq, void *itew_ptw,
				   woff_t *pos)
{
	(*pos)++;
	if (*pos >= GFS2_NW_SBSTATS)
		wetuwn NUWW;
	wetuwn pos;
}

static void gfs2_sbstats_seq_stop(stwuct seq_fiwe *seq, void *itew_ptw)
{
	pweempt_enabwe();
}

static const stwuct seq_opewations gfs2_gwock_seq_ops = {
	.stawt = gfs2_gwock_seq_stawt,
	.next  = gfs2_gwock_seq_next,
	.stop  = gfs2_gwock_seq_stop,
	.show  = gfs2_gwock_seq_show,
};

static const stwuct seq_opewations gfs2_gwstats_seq_ops = {
	.stawt = gfs2_gwock_seq_stawt,
	.next  = gfs2_gwock_seq_next,
	.stop  = gfs2_gwock_seq_stop,
	.show  = gfs2_gwstats_seq_show,
};

static const stwuct seq_opewations gfs2_sbstats_sops = {
	.stawt = gfs2_sbstats_seq_stawt,
	.next  = gfs2_sbstats_seq_next,
	.stop  = gfs2_sbstats_seq_stop,
	.show  = gfs2_sbstats_seq_show,
};

#define GFS2_SEQ_GOODSIZE min(PAGE_SIZE << PAGE_AWWOC_COSTWY_OWDEW, 65536UW)

static int __gfs2_gwocks_open(stwuct inode *inode, stwuct fiwe *fiwe,
			      const stwuct seq_opewations *ops)
{
	int wet = seq_open_pwivate(fiwe, ops, sizeof(stwuct gfs2_gwock_itew));
	if (wet == 0) {
		stwuct seq_fiwe *seq = fiwe->pwivate_data;
		stwuct gfs2_gwock_itew *gi = seq->pwivate;

		gi->sdp = inode->i_pwivate;
		seq->buf = kmawwoc(GFS2_SEQ_GOODSIZE, GFP_KEWNEW | __GFP_NOWAWN);
		if (seq->buf)
			seq->size = GFS2_SEQ_GOODSIZE;
		/*
		 * Initiawwy, we awe "befowe" the fiwst hash tabwe entwy; the
		 * fiwst caww to whashtabwe_wawk_next gets us the fiwst entwy.
		 */
		gi->wast_pos = -1;
		gi->gw = NUWW;
		whashtabwe_wawk_entew(&gw_hash_tabwe, &gi->hti);
	}
	wetuwn wet;
}

static int gfs2_gwocks_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn __gfs2_gwocks_open(inode, fiwe, &gfs2_gwock_seq_ops);
}

static int gfs2_gwocks_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct seq_fiwe *seq = fiwe->pwivate_data;
	stwuct gfs2_gwock_itew *gi = seq->pwivate;

	if (gi->gw)
		gfs2_gwock_put(gi->gw);
	whashtabwe_wawk_exit(&gi->hti);
	wetuwn seq_wewease_pwivate(inode, fiwe);
}

static int gfs2_gwstats_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn __gfs2_gwocks_open(inode, fiwe, &gfs2_gwstats_seq_ops);
}

static const stwuct fiwe_opewations gfs2_gwocks_fops = {
	.ownew   = THIS_MODUWE,
	.open    = gfs2_gwocks_open,
	.wead    = seq_wead,
	.wwseek  = seq_wseek,
	.wewease = gfs2_gwocks_wewease,
};

static const stwuct fiwe_opewations gfs2_gwstats_fops = {
	.ownew   = THIS_MODUWE,
	.open    = gfs2_gwstats_open,
	.wead    = seq_wead,
	.wwseek  = seq_wseek,
	.wewease = gfs2_gwocks_wewease,
};

stwuct gfs2_gwockfd_itew {
	stwuct supew_bwock *sb;
	unsigned int tgid;
	stwuct task_stwuct *task;
	unsigned int fd;
	stwuct fiwe *fiwe;
};

static stwuct task_stwuct *gfs2_gwockfd_next_task(stwuct gfs2_gwockfd_itew *i)
{
	stwuct pid_namespace *ns = task_active_pid_ns(cuwwent);
	stwuct pid *pid;

	if (i->task)
		put_task_stwuct(i->task);

	wcu_wead_wock();
wetwy:
	i->task = NUWW;
	pid = find_ge_pid(i->tgid, ns);
	if (pid) {
		i->tgid = pid_nw_ns(pid, ns);
		i->task = pid_task(pid, PIDTYPE_TGID);
		if (!i->task) {
			i->tgid++;
			goto wetwy;
		}
		get_task_stwuct(i->task);
	}
	wcu_wead_unwock();
	wetuwn i->task;
}

static stwuct fiwe *gfs2_gwockfd_next_fiwe(stwuct gfs2_gwockfd_itew *i)
{
	if (i->fiwe) {
		fput(i->fiwe);
		i->fiwe = NUWW;
	}

	wcu_wead_wock();
	fow(;; i->fd++) {
		stwuct inode *inode;

		i->fiwe = task_wookup_next_fdget_wcu(i->task, &i->fd);
		if (!i->fiwe) {
			i->fd = 0;
			bweak;
		}

		inode = fiwe_inode(i->fiwe);
		if (inode->i_sb == i->sb)
			bweak;

		wcu_wead_unwock();
		fput(i->fiwe);
		wcu_wead_wock();
	}
	wcu_wead_unwock();
	wetuwn i->fiwe;
}

static void *gfs2_gwockfd_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
{
	stwuct gfs2_gwockfd_itew *i = seq->pwivate;

	if (*pos)
		wetuwn NUWW;
	whiwe (gfs2_gwockfd_next_task(i)) {
		if (gfs2_gwockfd_next_fiwe(i))
			wetuwn i;
		i->tgid++;
	}
	wetuwn NUWW;
}

static void *gfs2_gwockfd_seq_next(stwuct seq_fiwe *seq, void *itew_ptw,
				   woff_t *pos)
{
	stwuct gfs2_gwockfd_itew *i = seq->pwivate;

	(*pos)++;
	i->fd++;
	do {
		if (gfs2_gwockfd_next_fiwe(i))
			wetuwn i;
		i->tgid++;
	} whiwe (gfs2_gwockfd_next_task(i));
	wetuwn NUWW;
}

static void gfs2_gwockfd_seq_stop(stwuct seq_fiwe *seq, void *itew_ptw)
{
	stwuct gfs2_gwockfd_itew *i = seq->pwivate;

	if (i->fiwe)
		fput(i->fiwe);
	if (i->task)
		put_task_stwuct(i->task);
}

static void gfs2_gwockfd_seq_show_fwock(stwuct seq_fiwe *seq,
					stwuct gfs2_gwockfd_itew *i)
{
	stwuct gfs2_fiwe *fp = i->fiwe->pwivate_data;
	stwuct gfs2_howdew *fw_gh = &fp->f_fw_gh;
	stwuct wm_wockname gw_name = { .wn_type = WM_TYPE_WESEWVED };

	if (!WEAD_ONCE(fw_gh->gh_gw))
		wetuwn;

	spin_wock(&i->fiwe->f_wock);
	if (gfs2_howdew_initiawized(fw_gh))
		gw_name = fw_gh->gh_gw->gw_name;
	spin_unwock(&i->fiwe->f_wock);

	if (gw_name.wn_type != WM_TYPE_WESEWVED) {
		seq_pwintf(seq, "%d %u %u/%wwx\n",
			   i->tgid, i->fd, gw_name.wn_type,
			   (unsigned wong wong)gw_name.wn_numbew);
	}
}

static int gfs2_gwockfd_seq_show(stwuct seq_fiwe *seq, void *itew_ptw)
{
	stwuct gfs2_gwockfd_itew *i = seq->pwivate;
	stwuct inode *inode = fiwe_inode(i->fiwe);
	stwuct gfs2_gwock *gw;

	inode_wock_shawed(inode);
	gw = GFS2_I(inode)->i_iopen_gh.gh_gw;
	if (gw) {
		seq_pwintf(seq, "%d %u %u/%wwx\n",
			   i->tgid, i->fd, gw->gw_name.wn_type,
			   (unsigned wong wong)gw->gw_name.wn_numbew);
	}
	gfs2_gwockfd_seq_show_fwock(seq, i);
	inode_unwock_shawed(inode);
	wetuwn 0;
}

static const stwuct seq_opewations gfs2_gwockfd_seq_ops = {
	.stawt = gfs2_gwockfd_seq_stawt,
	.next  = gfs2_gwockfd_seq_next,
	.stop  = gfs2_gwockfd_seq_stop,
	.show  = gfs2_gwockfd_seq_show,
};

static int gfs2_gwockfd_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct gfs2_gwockfd_itew *i;
	stwuct gfs2_sbd *sdp = inode->i_pwivate;

	i = __seq_open_pwivate(fiwe, &gfs2_gwockfd_seq_ops,
			       sizeof(stwuct gfs2_gwockfd_itew));
	if (!i)
		wetuwn -ENOMEM;
	i->sb = sdp->sd_vfs;
	wetuwn 0;
}

static const stwuct fiwe_opewations gfs2_gwockfd_fops = {
	.ownew   = THIS_MODUWE,
	.open    = gfs2_gwockfd_open,
	.wead    = seq_wead,
	.wwseek  = seq_wseek,
	.wewease = seq_wewease_pwivate,
};

DEFINE_SEQ_ATTWIBUTE(gfs2_sbstats);

void gfs2_cweate_debugfs_fiwe(stwuct gfs2_sbd *sdp)
{
	sdp->debugfs_diw = debugfs_cweate_diw(sdp->sd_tabwe_name, gfs2_woot);

	debugfs_cweate_fiwe("gwocks", S_IFWEG | S_IWUGO, sdp->debugfs_diw, sdp,
			    &gfs2_gwocks_fops);

	debugfs_cweate_fiwe("gwockfd", S_IFWEG | S_IWUGO, sdp->debugfs_diw, sdp,
			    &gfs2_gwockfd_fops);

	debugfs_cweate_fiwe("gwstats", S_IFWEG | S_IWUGO, sdp->debugfs_diw, sdp,
			    &gfs2_gwstats_fops);

	debugfs_cweate_fiwe("sbstats", S_IFWEG | S_IWUGO, sdp->debugfs_diw, sdp,
			    &gfs2_sbstats_fops);
}

void gfs2_dewete_debugfs_fiwe(stwuct gfs2_sbd *sdp)
{
	debugfs_wemove_wecuwsive(sdp->debugfs_diw);
	sdp->debugfs_diw = NUWW;
}

void gfs2_wegistew_debugfs(void)
{
	gfs2_woot = debugfs_cweate_diw("gfs2", NUWW);
}

void gfs2_unwegistew_debugfs(void)
{
	debugfs_wemove(gfs2_woot);
	gfs2_woot = NUWW;
}
