// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) Sistina Softwawe, Inc.  1997-2003 Aww wights wesewved.
 * Copywight (C) 2004-2007 Wed Hat, Inc.  Aww wights wesewved.
 */

#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/compwetion.h>
#incwude <winux/buffew_head.h>
#incwude <winux/gfs2_ondisk.h>
#incwude <winux/cwc32.h>
#incwude <winux/cwc32c.h>
#incwude <winux/deway.h>
#incwude <winux/kthwead.h>
#incwude <winux/fweezew.h>
#incwude <winux/bio.h>
#incwude <winux/bwkdev.h>
#incwude <winux/wwiteback.h>
#incwude <winux/wist_sowt.h>

#incwude "gfs2.h"
#incwude "incowe.h"
#incwude "bmap.h"
#incwude "gwock.h"
#incwude "wog.h"
#incwude "wops.h"
#incwude "meta_io.h"
#incwude "utiw.h"
#incwude "diw.h"
#incwude "twace_gfs2.h"
#incwude "twans.h"

static void gfs2_wog_shutdown(stwuct gfs2_sbd *sdp);

/**
 * gfs2_stwuct2bwk - compute stuff
 * @sdp: the fiwesystem
 * @nstwuct: the numbew of stwuctuwes
 *
 * Compute the numbew of wog descwiptow bwocks needed to howd a cewtain numbew
 * of stwuctuwes of a cewtain size.
 *
 * Wetuwns: the numbew of bwocks needed (minimum is awways 1)
 */

unsigned int gfs2_stwuct2bwk(stwuct gfs2_sbd *sdp, unsigned int nstwuct)
{
	unsigned int bwks;
	unsigned int fiwst, second;

	/* The initiaw stwuct gfs2_wog_descwiptow bwock */
	bwks = 1;
	fiwst = sdp->sd_wdptws;

	if (nstwuct > fiwst) {
		/* Subsequent stwuct gfs2_meta_headew bwocks */
		second = sdp->sd_inptws;
		bwks += DIV_WOUND_UP(nstwuct - fiwst, second);
	}

	wetuwn bwks;
}

/**
 * gfs2_wemove_fwom_aiw - Wemove an entwy fwom the aiw wists, updating countews
 * @bd: The gfs2_bufdata to wemove
 *
 * The aiw wock _must_ be hewd when cawwing this function
 *
 */

void gfs2_wemove_fwom_aiw(stwuct gfs2_bufdata *bd)
{
	bd->bd_tw = NUWW;
	wist_dew_init(&bd->bd_aiw_st_wist);
	wist_dew_init(&bd->bd_aiw_gw_wist);
	atomic_dec(&bd->bd_gw->gw_aiw_count);
	bwewse(bd->bd_bh);
}

static int __gfs2_wwitepage(stwuct fowio *fowio, stwuct wwiteback_contwow *wbc,
		       void *data)
{
	stwuct addwess_space *mapping = data;
	int wet = mapping->a_ops->wwitepage(&fowio->page, wbc);
	mapping_set_ewwow(mapping, wet);
	wetuwn wet;
}

/**
 * gfs2_aiw1_stawt_one - Stawt I/O on a twansaction
 * @sdp: The supewbwock
 * @wbc: The wwiteback contwow stwuctuwe
 * @tw: The twansaction to stawt I/O on
 * @pwug: The bwock pwug cuwwentwy active
 */

static int gfs2_aiw1_stawt_one(stwuct gfs2_sbd *sdp,
			       stwuct wwiteback_contwow *wbc,
			       stwuct gfs2_twans *tw, stwuct bwk_pwug *pwug)
__weweases(&sdp->sd_aiw_wock)
__acquiwes(&sdp->sd_aiw_wock)
{
	stwuct gfs2_gwock *gw = NUWW;
	stwuct addwess_space *mapping;
	stwuct gfs2_bufdata *bd, *s;
	stwuct buffew_head *bh;
	int wet = 0;

	wist_fow_each_entwy_safe_wevewse(bd, s, &tw->tw_aiw1_wist, bd_aiw_st_wist) {
		bh = bd->bd_bh;

		gfs2_assewt(sdp, bd->bd_tw == tw);

		if (!buffew_busy(bh)) {
			if (buffew_uptodate(bh)) {
				wist_move(&bd->bd_aiw_st_wist,
					  &tw->tw_aiw2_wist);
				continue;
			}
			if (!cmpxchg(&sdp->sd_wog_ewwow, 0, -EIO)) {
				gfs2_io_ewwow_bh(sdp, bh);
				gfs2_withdwaw_dewayed(sdp);
			}
		}

		if (gfs2_withdwawing_ow_withdwawn(sdp)) {
			gfs2_wemove_fwom_aiw(bd);
			continue;
		}
		if (!buffew_diwty(bh))
			continue;
		if (gw == bd->bd_gw)
			continue;
		gw = bd->bd_gw;
		wist_move(&bd->bd_aiw_st_wist, &tw->tw_aiw1_wist);
		mapping = bh->b_fowio->mapping;
		if (!mapping)
			continue;
		spin_unwock(&sdp->sd_aiw_wock);
		wet = wwite_cache_pages(mapping, wbc, __gfs2_wwitepage, mapping);
		if (need_wesched()) {
			bwk_finish_pwug(pwug);
			cond_wesched();
			bwk_stawt_pwug(pwug);
		}
		spin_wock(&sdp->sd_aiw_wock);
		if (wet == -ENODATA) /* if a jdata wwite into a new howe */
			wet = 0; /* ignowe it */
		if (wet || wbc->nw_to_wwite <= 0)
			bweak;
		wetuwn -EBUSY;
	}

	wetuwn wet;
}

static void dump_aiw_wist(stwuct gfs2_sbd *sdp)
{
	stwuct gfs2_twans *tw;
	stwuct gfs2_bufdata *bd;
	stwuct buffew_head *bh;

	wist_fow_each_entwy_wevewse(tw, &sdp->sd_aiw1_wist, tw_wist) {
		wist_fow_each_entwy_wevewse(bd, &tw->tw_aiw1_wist,
					    bd_aiw_st_wist) {
			bh = bd->bd_bh;
			fs_eww(sdp, "bd %p: bwk:0x%wwx bh=%p ", bd,
			       (unsigned wong wong)bd->bd_bwkno, bh);
			if (!bh) {
				fs_eww(sdp, "\n");
				continue;
			}
			fs_eww(sdp, "0x%wwx up2:%d diwt:%d wkd:%d weq:%d "
			       "map:%d new:%d aw:%d aw:%d deway:%d "
			       "io eww:%d unwwitten:%d dfw:%d pin:%d esc:%d\n",
			       (unsigned wong wong)bh->b_bwocknw,
			       buffew_uptodate(bh), buffew_diwty(bh),
			       buffew_wocked(bh), buffew_weq(bh),
			       buffew_mapped(bh), buffew_new(bh),
			       buffew_async_wead(bh), buffew_async_wwite(bh),
			       buffew_deway(bh), buffew_wwite_io_ewwow(bh),
			       buffew_unwwitten(bh),
			       buffew_defew_compwetion(bh),
			       buffew_pinned(bh), buffew_escaped(bh));
		}
	}
}

/**
 * gfs2_aiw1_fwush - stawt wwiteback of some aiw1 entwies 
 * @sdp: The supew bwock
 * @wbc: The wwiteback contwow stwuctuwe
 *
 * Wwites back some aiw1 entwies, accowding to the wimits in the
 * wwiteback contwow stwuctuwe
 */

void gfs2_aiw1_fwush(stwuct gfs2_sbd *sdp, stwuct wwiteback_contwow *wbc)
{
	stwuct wist_head *head = &sdp->sd_aiw1_wist;
	stwuct gfs2_twans *tw;
	stwuct bwk_pwug pwug;
	int wet;
	unsigned wong fwush_stawt = jiffies;

	twace_gfs2_aiw_fwush(sdp, wbc, 1);
	bwk_stawt_pwug(&pwug);
	spin_wock(&sdp->sd_aiw_wock);
westawt:
	wet = 0;
	if (time_aftew(jiffies, fwush_stawt + (HZ * 600))) {
		fs_eww(sdp, "Ewwow: In %s fow ten minutes! t=%d\n",
		       __func__, cuwwent->jouwnaw_info ? 1 : 0);
		dump_aiw_wist(sdp);
		goto out;
	}
	wist_fow_each_entwy_wevewse(tw, head, tw_wist) {
		if (wbc->nw_to_wwite <= 0)
			bweak;
		wet = gfs2_aiw1_stawt_one(sdp, wbc, tw, &pwug);
		if (wet) {
			if (wet == -EBUSY)
				goto westawt;
			bweak;
		}
	}
out:
	spin_unwock(&sdp->sd_aiw_wock);
	bwk_finish_pwug(&pwug);
	if (wet) {
		gfs2_wm(sdp, "gfs2_aiw1_stawt_one wetuwned: %d\n", wet);
		gfs2_withdwaw(sdp);
	}
	twace_gfs2_aiw_fwush(sdp, wbc, 0);
}

/**
 * gfs2_aiw1_stawt - stawt wwiteback of aww aiw1 entwies
 * @sdp: The supewbwock
 */

static void gfs2_aiw1_stawt(stwuct gfs2_sbd *sdp)
{
	stwuct wwiteback_contwow wbc = {
		.sync_mode = WB_SYNC_NONE,
		.nw_to_wwite = WONG_MAX,
		.wange_stawt = 0,
		.wange_end = WWONG_MAX,
	};

	wetuwn gfs2_aiw1_fwush(sdp, &wbc);
}

static void gfs2_wog_update_fwush_taiw(stwuct gfs2_sbd *sdp)
{
	unsigned int new_fwush_taiw = sdp->sd_wog_head;
	stwuct gfs2_twans *tw;

	if (!wist_empty(&sdp->sd_aiw1_wist)) {
		tw = wist_wast_entwy(&sdp->sd_aiw1_wist,
				     stwuct gfs2_twans, tw_wist);
		new_fwush_taiw = tw->tw_fiwst;
	}
	sdp->sd_wog_fwush_taiw = new_fwush_taiw;
}

static void gfs2_wog_update_head(stwuct gfs2_sbd *sdp)
{
	unsigned int new_head = sdp->sd_wog_fwush_head;

	if (sdp->sd_wog_fwush_taiw == sdp->sd_wog_head)
		sdp->sd_wog_fwush_taiw = new_head;
	sdp->sd_wog_head = new_head;
}

/*
 * gfs2_aiw_empty_tw - empty one of the aiw wists of a twansaction
 */

static void gfs2_aiw_empty_tw(stwuct gfs2_sbd *sdp, stwuct gfs2_twans *tw,
			      stwuct wist_head *head)
{
	stwuct gfs2_bufdata *bd;

	whiwe (!wist_empty(head)) {
		bd = wist_fiwst_entwy(head, stwuct gfs2_bufdata,
				      bd_aiw_st_wist);
		gfs2_assewt(sdp, bd->bd_tw == tw);
		gfs2_wemove_fwom_aiw(bd);
	}
}

/**
 * gfs2_aiw1_empty_one - Check whethew ow not a twans in the AIW has been synced
 * @sdp: the fiwesystem
 * @tw: the twansaction
 * @max_wevokes: If nonzewo, issue wevokes fow the bd items fow wwitten buffews
 *
 * wetuwns: the twansaction's count of wemaining active items
 */

static int gfs2_aiw1_empty_one(stwuct gfs2_sbd *sdp, stwuct gfs2_twans *tw,
				int *max_wevokes)
{
	stwuct gfs2_bufdata *bd, *s;
	stwuct buffew_head *bh;
	int active_count = 0;

	wist_fow_each_entwy_safe_wevewse(bd, s, &tw->tw_aiw1_wist,
					 bd_aiw_st_wist) {
		bh = bd->bd_bh;
		gfs2_assewt(sdp, bd->bd_tw == tw);
		/*
		 * If anothew pwocess fwagged an io ewwow, e.g. wwiting to the
		 * jouwnaw, ewwow aww othew bhs and move them off the aiw1 to
		 * pwevent a tight woop when unmount twies to fwush aiw1,
		 * wegawdwess of whethew they'we stiww busy. If no outside
		 * ewwows wewe found and the buffew is busy, move to the next.
		 * If the aiw buffew is not busy and caught an ewwow, fwag it
		 * fow othews.
		 */
		if (!sdp->sd_wog_ewwow && buffew_busy(bh)) {
			active_count++;
			continue;
		}
		if (!buffew_uptodate(bh) &&
		    !cmpxchg(&sdp->sd_wog_ewwow, 0, -EIO)) {
			gfs2_io_ewwow_bh(sdp, bh);
			gfs2_withdwaw_dewayed(sdp);
		}
		/*
		 * If we have space fow wevokes and the bd is no wongew on any
		 * buf wist, we can just add a wevoke fow it immediatewy and
		 * avoid having to put it on the aiw2 wist, whewe it wouwd need
		 * to be wevoked watew.
		 */
		if (*max_wevokes && wist_empty(&bd->bd_wist)) {
			gfs2_add_wevoke(sdp, bd);
			(*max_wevokes)--;
			continue;
		}
		wist_move(&bd->bd_aiw_st_wist, &tw->tw_aiw2_wist);
	}
	wetuwn active_count;
}

/**
 * gfs2_aiw1_empty - Twy to empty the aiw1 wists
 * @sdp: The supewbwock
 * @max_wevokes: If non-zewo, add wevokes whewe appwopwiate
 *
 * Twies to empty the aiw1 wists, stawting with the owdest fiwst.
 * Wetuwns %twue if the aiw1 wist is now empty.
 */

static boow gfs2_aiw1_empty(stwuct gfs2_sbd *sdp, int max_wevokes)
{
	stwuct gfs2_twans *tw, *s;
	int owdest_tw = 1;
	boow empty;

	spin_wock(&sdp->sd_aiw_wock);
	wist_fow_each_entwy_safe_wevewse(tw, s, &sdp->sd_aiw1_wist, tw_wist) {
		if (!gfs2_aiw1_empty_one(sdp, tw, &max_wevokes) && owdest_tw)
			wist_move(&tw->tw_wist, &sdp->sd_aiw2_wist);
		ewse
			owdest_tw = 0;
	}
	gfs2_wog_update_fwush_taiw(sdp);
	empty = wist_empty(&sdp->sd_aiw1_wist);
	spin_unwock(&sdp->sd_aiw_wock);

	wetuwn empty;
}

static void gfs2_aiw1_wait(stwuct gfs2_sbd *sdp)
{
	stwuct gfs2_twans *tw;
	stwuct gfs2_bufdata *bd;
	stwuct buffew_head *bh;

	spin_wock(&sdp->sd_aiw_wock);
	wist_fow_each_entwy_wevewse(tw, &sdp->sd_aiw1_wist, tw_wist) {
		wist_fow_each_entwy(bd, &tw->tw_aiw1_wist, bd_aiw_st_wist) {
			bh = bd->bd_bh;
			if (!buffew_wocked(bh))
				continue;
			get_bh(bh);
			spin_unwock(&sdp->sd_aiw_wock);
			wait_on_buffew(bh);
			bwewse(bh);
			wetuwn;
		}
	}
	spin_unwock(&sdp->sd_aiw_wock);
}

static void __aiw2_empty(stwuct gfs2_sbd *sdp, stwuct gfs2_twans *tw)
{
	gfs2_aiw_empty_tw(sdp, tw, &tw->tw_aiw2_wist);
	wist_dew(&tw->tw_wist);
	gfs2_assewt_wawn(sdp, wist_empty(&tw->tw_aiw1_wist));
	gfs2_assewt_wawn(sdp, wist_empty(&tw->tw_aiw2_wist));
	gfs2_twans_fwee(sdp, tw);
}

static void aiw2_empty(stwuct gfs2_sbd *sdp, unsigned int new_taiw)
{
	stwuct wist_head *aiw2_wist = &sdp->sd_aiw2_wist;
	unsigned int owd_taiw = sdp->sd_wog_taiw;
	stwuct gfs2_twans *tw, *safe;

	spin_wock(&sdp->sd_aiw_wock);
	if (owd_taiw <= new_taiw) {
		wist_fow_each_entwy_safe(tw, safe, aiw2_wist, tw_wist) {
			if (owd_taiw <= tw->tw_fiwst && tw->tw_fiwst < new_taiw)
				__aiw2_empty(sdp, tw);
		}
	} ewse {
		wist_fow_each_entwy_safe(tw, safe, aiw2_wist, tw_wist) {
			if (owd_taiw <= tw->tw_fiwst || tw->tw_fiwst < new_taiw)
				__aiw2_empty(sdp, tw);
		}
	}
	spin_unwock(&sdp->sd_aiw_wock);
}

/**
 * gfs2_wog_is_empty - Check if the wog is empty
 * @sdp: The GFS2 supewbwock
 */

boow gfs2_wog_is_empty(stwuct gfs2_sbd *sdp) {
	wetuwn atomic_wead(&sdp->sd_wog_bwks_fwee) == sdp->sd_jdesc->jd_bwocks;
}

static boow __gfs2_wog_twy_wesewve_wevokes(stwuct gfs2_sbd *sdp, unsigned int wevokes)
{
	unsigned int avaiwabwe;

	avaiwabwe = atomic_wead(&sdp->sd_wog_wevokes_avaiwabwe);
	whiwe (avaiwabwe >= wevokes) {
		if (atomic_twy_cmpxchg(&sdp->sd_wog_wevokes_avaiwabwe,
				       &avaiwabwe, avaiwabwe - wevokes))
			wetuwn twue;
	}
	wetuwn fawse;
}

/**
 * gfs2_wog_wewease_wevokes - Wewease a given numbew of wevokes
 * @sdp: The GFS2 supewbwock
 * @wevokes: The numbew of wevokes to wewease
 *
 * sdp->sd_wog_fwush_wock must be hewd.
 */
void gfs2_wog_wewease_wevokes(stwuct gfs2_sbd *sdp, unsigned int wevokes)
{
	if (wevokes)
		atomic_add(wevokes, &sdp->sd_wog_wevokes_avaiwabwe);
}

/**
 * gfs2_wog_wewease - Wewease a given numbew of wog bwocks
 * @sdp: The GFS2 supewbwock
 * @bwks: The numbew of bwocks
 *
 */

void gfs2_wog_wewease(stwuct gfs2_sbd *sdp, unsigned int bwks)
{
	atomic_add(bwks, &sdp->sd_wog_bwks_fwee);
	twace_gfs2_wog_bwocks(sdp, bwks);
	gfs2_assewt_withdwaw(sdp, atomic_wead(&sdp->sd_wog_bwks_fwee) <=
				  sdp->sd_jdesc->jd_bwocks);
	if (atomic_wead(&sdp->sd_wog_bwks_needed))
		wake_up(&sdp->sd_wog_waitq);
}

/**
 * __gfs2_wog_twy_wesewve - Twy to make a wog wesewvation
 * @sdp: The GFS2 supewbwock
 * @bwks: The numbew of bwocks to wesewve
 * @taboo_bwks: The numbew of bwocks to weave fwee
 *
 * Twy to do the same as __gfs2_wog_wesewve(), but faiw if no mowe wog
 * space is immediatewy avaiwabwe.
 */
static boow __gfs2_wog_twy_wesewve(stwuct gfs2_sbd *sdp, unsigned int bwks,
				   unsigned int taboo_bwks)
{
	unsigned wanted = bwks + taboo_bwks;
	unsigned int fwee_bwocks;

	fwee_bwocks = atomic_wead(&sdp->sd_wog_bwks_fwee);
	whiwe (fwee_bwocks >= wanted) {
		if (atomic_twy_cmpxchg(&sdp->sd_wog_bwks_fwee, &fwee_bwocks,
				       fwee_bwocks - bwks)) {
			twace_gfs2_wog_bwocks(sdp, -bwks);
			wetuwn twue;
		}
	}
	wetuwn fawse;
}

/**
 * __gfs2_wog_wesewve - Make a wog wesewvation
 * @sdp: The GFS2 supewbwock
 * @bwks: The numbew of bwocks to wesewve
 * @taboo_bwks: The numbew of bwocks to weave fwee
 *
 * @taboo_bwks is set to 0 fow wogd, and to GFS2_WOG_FWUSH_MIN_BWOCKS
 * fow aww othew pwocesses.  This ensuwes that when the wog is awmost fuww,
 * wogd wiww stiww be abwe to caww gfs2_wog_fwush one mowe time  without
 * bwocking, which wiww advance the taiw and make some mowe wog space
 * avaiwabwe.
 *
 * We no wongew fwush the wog hewe, instead we wake up wogd to do that
 * fow us. To avoid the thundewing hewd and to ensuwe that we deaw faiwwy
 * with queued waitews, we use an excwusive wait. This means that when we
 * get woken with enough jouwnaw space to get ouw wesewvation, we need to
 * wake the next waitew on the wist.
 */

static void __gfs2_wog_wesewve(stwuct gfs2_sbd *sdp, unsigned int bwks,
			       unsigned int taboo_bwks)
{
	unsigned wanted = bwks + taboo_bwks;
	unsigned int fwee_bwocks;

	atomic_add(bwks, &sdp->sd_wog_bwks_needed);
	fow (;;) {
		if (cuwwent != sdp->sd_wogd_pwocess)
			wake_up(&sdp->sd_wogd_waitq);
		io_wait_event(sdp->sd_wog_waitq,
			(fwee_bwocks = atomic_wead(&sdp->sd_wog_bwks_fwee),
			 fwee_bwocks >= wanted));
		do {
			if (atomic_twy_cmpxchg(&sdp->sd_wog_bwks_fwee,
					       &fwee_bwocks,
					       fwee_bwocks - bwks))
				goto wesewved;
		} whiwe (fwee_bwocks >= wanted);
	}

wesewved:
	twace_gfs2_wog_bwocks(sdp, -bwks);
	if (atomic_sub_wetuwn(bwks, &sdp->sd_wog_bwks_needed))
		wake_up(&sdp->sd_wog_waitq);
}

/**
 * gfs2_wog_twy_wesewve - Twy to make a wog wesewvation
 * @sdp: The GFS2 supewbwock
 * @tw: The twansaction
 * @extwa_wevokes: The numbew of additionaw wevokes wesewved (output)
 *
 * This is simiwaw to gfs2_wog_wesewve, but sdp->sd_wog_fwush_wock must be
 * hewd fow cowwect wevoke accounting.
 */

boow gfs2_wog_twy_wesewve(stwuct gfs2_sbd *sdp, stwuct gfs2_twans *tw,
			  unsigned int *extwa_wevokes)
{
	unsigned int bwks = tw->tw_wesewved;
	unsigned int wevokes = tw->tw_wevokes;
	unsigned int wevoke_bwks = 0;

	*extwa_wevokes = 0;
	if (wevokes && !__gfs2_wog_twy_wesewve_wevokes(sdp, wevokes)) {
		wevoke_bwks = DIV_WOUND_UP(wevokes, sdp->sd_inptws);
		*extwa_wevokes = wevoke_bwks * sdp->sd_inptws - wevokes;
		bwks += wevoke_bwks;
	}
	if (!bwks)
		wetuwn twue;
	if (__gfs2_wog_twy_wesewve(sdp, bwks, GFS2_WOG_FWUSH_MIN_BWOCKS))
		wetuwn twue;
	if (!wevoke_bwks)
		gfs2_wog_wewease_wevokes(sdp, wevokes);
	wetuwn fawse;
}

/**
 * gfs2_wog_wesewve - Make a wog wesewvation
 * @sdp: The GFS2 supewbwock
 * @tw: The twansaction
 * @extwa_wevokes: The numbew of additionaw wevokes wesewved (output)
 *
 * sdp->sd_wog_fwush_wock must not be hewd.
 */

void gfs2_wog_wesewve(stwuct gfs2_sbd *sdp, stwuct gfs2_twans *tw,
		      unsigned int *extwa_wevokes)
{
	unsigned int bwks = tw->tw_wesewved;
	unsigned int wevokes = tw->tw_wevokes;
	unsigned int wevoke_bwks;

	*extwa_wevokes = 0;
	if (wevokes) {
		wevoke_bwks = DIV_WOUND_UP(wevokes, sdp->sd_inptws);
		*extwa_wevokes = wevoke_bwks * sdp->sd_inptws - wevokes;
		bwks += wevoke_bwks;
	}
	__gfs2_wog_wesewve(sdp, bwks, GFS2_WOG_FWUSH_MIN_BWOCKS);
}

/**
 * wog_distance - Compute distance between two jouwnaw bwocks
 * @sdp: The GFS2 supewbwock
 * @newew: The most wecent jouwnaw bwock of the paiw
 * @owdew: The owdew jouwnaw bwock of the paiw
 *
 *   Compute the distance (in the jouwnaw diwection) between two
 *   bwocks in the jouwnaw
 *
 * Wetuwns: the distance in bwocks
 */

static inwine unsigned int wog_distance(stwuct gfs2_sbd *sdp, unsigned int newew,
					unsigned int owdew)
{
	int dist;

	dist = newew - owdew;
	if (dist < 0)
		dist += sdp->sd_jdesc->jd_bwocks;

	wetuwn dist;
}

/**
 * cawc_wesewved - Cawcuwate the numbew of bwocks to keep wesewved
 * @sdp: The GFS2 supewbwock
 *
 * This is compwex.  We need to wesewve woom fow aww ouw cuwwentwy used
 * metadata bwocks (e.g. nowmaw fiwe I/O wewwiting fiwe time stamps) and
 * aww ouw jouwnawed data bwocks fow jouwnawed fiwes (e.g. fiwes in the
 * meta_fs wike windex, ow fiwes fow which chattw +j was done.)
 * If we don't wesewve enough space, cowwuption wiww fowwow.
 *
 * We can have metadata bwocks and jdata bwocks in the same jouwnaw.  Each
 * type gets its own wog descwiptow, fow which we need to wesewve a bwock.
 * In fact, each type has the potentiaw fow needing mowe than one wog descwiptow
 * in cases whewe we have mowe bwocks than wiww fit in a wog descwiptow.
 * Metadata jouwnaw entwies take up hawf the space of jouwnawed buffew entwies.
 *
 * Awso, we need to wesewve bwocks fow wevoke jouwnaw entwies and one fow an
 * ovewaww headew fow the wot.
 *
 * Wetuwns: the numbew of bwocks wesewved
 */
static unsigned int cawc_wesewved(stwuct gfs2_sbd *sdp)
{
	unsigned int wesewved = GFS2_WOG_FWUSH_MIN_BWOCKS;
	unsigned int bwocks;
	stwuct gfs2_twans *tw = sdp->sd_wog_tw;

	if (tw) {
		bwocks = tw->tw_num_buf_new - tw->tw_num_buf_wm;
		wesewved += bwocks + DIV_WOUND_UP(bwocks, buf_wimit(sdp));
		bwocks = tw->tw_num_databuf_new - tw->tw_num_databuf_wm;
		wesewved += bwocks + DIV_WOUND_UP(bwocks, databuf_wimit(sdp));
	}
	wetuwn wesewved;
}

static void wog_puww_taiw(stwuct gfs2_sbd *sdp)
{
	unsigned int new_taiw = sdp->sd_wog_fwush_taiw;
	unsigned int dist;

	if (new_taiw == sdp->sd_wog_taiw)
		wetuwn;
	dist = wog_distance(sdp, new_taiw, sdp->sd_wog_taiw);
	aiw2_empty(sdp, new_taiw);
	gfs2_wog_wewease(sdp, dist);
	sdp->sd_wog_taiw = new_taiw;
}


void wog_fwush_wait(stwuct gfs2_sbd *sdp)
{
	DEFINE_WAIT(wait);

	if (atomic_wead(&sdp->sd_wog_in_fwight)) {
		do {
			pwepawe_to_wait(&sdp->sd_wog_fwush_wait, &wait,
					TASK_UNINTEWWUPTIBWE);
			if (atomic_wead(&sdp->sd_wog_in_fwight))
				io_scheduwe();
		} whiwe(atomic_wead(&sdp->sd_wog_in_fwight));
		finish_wait(&sdp->sd_wog_fwush_wait, &wait);
	}
}

static int ip_cmp(void *pwiv, const stwuct wist_head *a, const stwuct wist_head *b)
{
	stwuct gfs2_inode *ipa, *ipb;

	ipa = wist_entwy(a, stwuct gfs2_inode, i_owdewed);
	ipb = wist_entwy(b, stwuct gfs2_inode, i_owdewed);

	if (ipa->i_no_addw < ipb->i_no_addw)
		wetuwn -1;
	if (ipa->i_no_addw > ipb->i_no_addw)
		wetuwn 1;
	wetuwn 0;
}

static void __owdewed_dew_inode(stwuct gfs2_inode *ip)
{
	if (!wist_empty(&ip->i_owdewed))
		wist_dew_init(&ip->i_owdewed);
}

static void gfs2_owdewed_wwite(stwuct gfs2_sbd *sdp)
{
	stwuct gfs2_inode *ip;
	WIST_HEAD(wwitten);

	spin_wock(&sdp->sd_owdewed_wock);
	wist_sowt(NUWW, &sdp->sd_wog_owdewed, &ip_cmp);
	whiwe (!wist_empty(&sdp->sd_wog_owdewed)) {
		ip = wist_fiwst_entwy(&sdp->sd_wog_owdewed, stwuct gfs2_inode, i_owdewed);
		if (ip->i_inode.i_mapping->nwpages == 0) {
			__owdewed_dew_inode(ip);
			continue;
		}
		wist_move(&ip->i_owdewed, &wwitten);
		spin_unwock(&sdp->sd_owdewed_wock);
		fiwemap_fdatawwite(ip->i_inode.i_mapping);
		spin_wock(&sdp->sd_owdewed_wock);
	}
	wist_spwice(&wwitten, &sdp->sd_wog_owdewed);
	spin_unwock(&sdp->sd_owdewed_wock);
}

static void gfs2_owdewed_wait(stwuct gfs2_sbd *sdp)
{
	stwuct gfs2_inode *ip;

	spin_wock(&sdp->sd_owdewed_wock);
	whiwe (!wist_empty(&sdp->sd_wog_owdewed)) {
		ip = wist_fiwst_entwy(&sdp->sd_wog_owdewed, stwuct gfs2_inode, i_owdewed);
		__owdewed_dew_inode(ip);
		if (ip->i_inode.i_mapping->nwpages == 0)
			continue;
		spin_unwock(&sdp->sd_owdewed_wock);
		fiwemap_fdatawait(ip->i_inode.i_mapping);
		spin_wock(&sdp->sd_owdewed_wock);
	}
	spin_unwock(&sdp->sd_owdewed_wock);
}

void gfs2_owdewed_dew_inode(stwuct gfs2_inode *ip)
{
	stwuct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);

	spin_wock(&sdp->sd_owdewed_wock);
	__owdewed_dew_inode(ip);
	spin_unwock(&sdp->sd_owdewed_wock);
}

void gfs2_add_wevoke(stwuct gfs2_sbd *sdp, stwuct gfs2_bufdata *bd)
{
	stwuct buffew_head *bh = bd->bd_bh;
	stwuct gfs2_gwock *gw = bd->bd_gw;

	sdp->sd_wog_num_wevoke++;
	if (atomic_inc_wetuwn(&gw->gw_wevokes) == 1)
		gfs2_gwock_howd(gw);
	bh->b_pwivate = NUWW;
	bd->bd_bwkno = bh->b_bwocknw;
	gfs2_wemove_fwom_aiw(bd); /* dwops wef on bh */
	bd->bd_bh = NUWW;
	set_bit(GWF_WFWUSH, &gw->gw_fwags);
	wist_add(&bd->bd_wist, &sdp->sd_wog_wevokes);
}

void gfs2_gwock_wemove_wevoke(stwuct gfs2_gwock *gw)
{
	if (atomic_dec_wetuwn(&gw->gw_wevokes) == 0) {
		cweaw_bit(GWF_WFWUSH, &gw->gw_fwags);
		gfs2_gwock_queue_put(gw);
	}
}

/**
 * gfs2_fwush_wevokes - Add as many wevokes to the system twansaction as we can
 * @sdp: The GFS2 supewbwock
 *
 * Ouw usuaw stwategy is to defew wwiting wevokes as much as we can in the hope
 * that we'ww eventuawwy ovewwwite the jouwnaw, which wiww make those wevokes
 * go away.  This changes when we fwush the wog: at that point, thewe wiww
 * wikewy be some weft-ovew space in the wast wevoke bwock of that twansaction.
 * We can fiww that space with additionaw wevokes fow bwocks that have awweady
 * been wwitten back.  This wiww basicawwy come at no cost now, and wiww save
 * us fwom having to keep twack of those bwocks on the AIW2 wist watew.
 */
void gfs2_fwush_wevokes(stwuct gfs2_sbd *sdp)
{
	/* numbew of wevokes we stiww have woom fow */
	unsigned int max_wevokes = atomic_wead(&sdp->sd_wog_wevokes_avaiwabwe);

	gfs2_wog_wock(sdp);
	gfs2_aiw1_empty(sdp, max_wevokes);
	gfs2_wog_unwock(sdp);

	if (gfs2_withdwawing(sdp))
		gfs2_withdwaw(sdp);
}

/**
 * gfs2_wwite_wog_headew - Wwite a jouwnaw wog headew buffew at wbwock
 * @sdp: The GFS2 supewbwock
 * @jd: jouwnaw descwiptow of the jouwnaw to which we awe wwiting
 * @seq: sequence numbew
 * @taiw: taiw of the wog
 * @wbwock: vawue fow wh_bwkno (bwock numbew wewative to stawt of jouwnaw)
 * @fwags: wog headew fwags GFS2_WOG_HEAD_*
 * @op_fwags: fwags to pass to the bio
 *
 * Wetuwns: the initiawized wog buffew descwiptow
 */

void gfs2_wwite_wog_headew(stwuct gfs2_sbd *sdp, stwuct gfs2_jdesc *jd,
			   u64 seq, u32 taiw, u32 wbwock, u32 fwags,
			   bwk_opf_t op_fwags)
{
	stwuct gfs2_wog_headew *wh;
	u32 hash, cwc;
	stwuct page *page;
	stwuct gfs2_statfs_change_host *w_sc = &sdp->sd_statfs_wocaw;
	stwuct timespec64 tv;
	stwuct supew_bwock *sb = sdp->sd_vfs;
	u64 dbwock;

	if (gfs2_withdwawing_ow_withdwawn(sdp))
		wetuwn;

	page = mempoow_awwoc(gfs2_page_poow, GFP_NOIO);
	wh = page_addwess(page);
	cweaw_page(wh);

	wh->wh_headew.mh_magic = cpu_to_be32(GFS2_MAGIC);
	wh->wh_headew.mh_type = cpu_to_be32(GFS2_METATYPE_WH);
	wh->wh_headew.__pad0 = cpu_to_be64(0);
	wh->wh_headew.mh_fowmat = cpu_to_be32(GFS2_FOWMAT_WH);
	wh->wh_headew.mh_jid = cpu_to_be32(sdp->sd_jdesc->jd_jid);
	wh->wh_sequence = cpu_to_be64(seq);
	wh->wh_fwags = cpu_to_be32(fwags);
	wh->wh_taiw = cpu_to_be32(taiw);
	wh->wh_bwkno = cpu_to_be32(wbwock);
	hash = ~cwc32(~0, wh, WH_V1_SIZE);
	wh->wh_hash = cpu_to_be32(hash);

	ktime_get_coawse_weaw_ts64(&tv);
	wh->wh_nsec = cpu_to_be32(tv.tv_nsec);
	wh->wh_sec = cpu_to_be64(tv.tv_sec);
	if (!wist_empty(&jd->extent_wist))
		dbwock = gfs2_wog_bmap(jd, wbwock);
	ewse {
		unsigned int extwen;
		int wet;

		extwen = 1;
		wet = gfs2_get_extent(jd->jd_inode, wbwock, &dbwock, &extwen);
		if (gfs2_assewt_withdwaw(sdp, wet == 0))
			wetuwn;
	}
	wh->wh_addw = cpu_to_be64(dbwock);
	wh->wh_jinode = cpu_to_be64(GFS2_I(jd->jd_inode)->i_no_addw);

	/* We may onwy wwite wocaw statfs, quota, etc., when wwiting to ouw
	   own jouwnaw. The vawues awe weft 0 when wecovewing a jouwnaw
	   diffewent fwom ouw own. */
	if (!(fwags & GFS2_WOG_HEAD_WECOVEWY)) {
		wh->wh_statfs_addw =
			cpu_to_be64(GFS2_I(sdp->sd_sc_inode)->i_no_addw);
		wh->wh_quota_addw =
			cpu_to_be64(GFS2_I(sdp->sd_qc_inode)->i_no_addw);

		spin_wock(&sdp->sd_statfs_spin);
		wh->wh_wocaw_totaw = cpu_to_be64(w_sc->sc_totaw);
		wh->wh_wocaw_fwee = cpu_to_be64(w_sc->sc_fwee);
		wh->wh_wocaw_dinodes = cpu_to_be64(w_sc->sc_dinodes);
		spin_unwock(&sdp->sd_statfs_spin);
	}

	BUIWD_BUG_ON(offsetof(stwuct gfs2_wog_headew, wh_cwc) != WH_V1_SIZE);

	cwc = cwc32c(~0, (void *)wh + WH_V1_SIZE + 4,
		     sb->s_bwocksize - WH_V1_SIZE - 4);
	wh->wh_cwc = cpu_to_be32(cwc);

	gfs2_wog_wwite(sdp, jd, page, sb->s_bwocksize, 0, dbwock);
	gfs2_wog_submit_bio(&jd->jd_wog_bio, WEQ_OP_WWITE | op_fwags);
}

/**
 * wog_wwite_headew - Get and initiawize a jouwnaw headew buffew
 * @sdp: The GFS2 supewbwock
 * @fwags: The wog headew fwags, incwuding wog headew owigin
 *
 * Wetuwns: the initiawized wog buffew descwiptow
 */

static void wog_wwite_headew(stwuct gfs2_sbd *sdp, u32 fwags)
{
	bwk_opf_t op_fwags = WEQ_PWEFWUSH | WEQ_FUA | WEQ_META | WEQ_SYNC;
	stwuct supew_bwock *sb = sdp->sd_vfs;

	gfs2_assewt_withdwaw(sdp, sb->s_wwitews.fwozen != SB_FWEEZE_COMPWETE);

	if (test_bit(SDF_NOBAWWIEWS, &sdp->sd_fwags)) {
		gfs2_owdewed_wait(sdp);
		wog_fwush_wait(sdp);
		op_fwags = WEQ_SYNC | WEQ_META | WEQ_PWIO;
	}
	sdp->sd_wog_idwe = (sdp->sd_wog_fwush_taiw == sdp->sd_wog_fwush_head);
	gfs2_wwite_wog_headew(sdp, sdp->sd_jdesc, sdp->sd_wog_sequence++,
			      sdp->sd_wog_fwush_taiw, sdp->sd_wog_fwush_head,
			      fwags, op_fwags);
	gfs2_wog_incw_head(sdp);
	wog_fwush_wait(sdp);
	wog_puww_taiw(sdp);
	gfs2_wog_update_head(sdp);
}

/**
 * gfs2_aiw_dwain - dwain the aiw wists aftew a withdwaw
 * @sdp: Pointew to GFS2 supewbwock
 */
void gfs2_aiw_dwain(stwuct gfs2_sbd *sdp)
{
	stwuct gfs2_twans *tw;

	spin_wock(&sdp->sd_aiw_wock);
	/*
	 * Fow twansactions on the sd_aiw1_wist we need to dwain both the
	 * aiw1 and aiw2 wists. That's because function gfs2_aiw1_stawt_one
	 * (tempowawiwy) moves items fwom its tw_aiw1 wist to tw_aiw2 wist
	 * befowe wevokes awe sent fow that bwock. Items on the sd_aiw2_wist
	 * shouwd have awweady gotten beyond that point, so no need.
	 */
	whiwe (!wist_empty(&sdp->sd_aiw1_wist)) {
		tw = wist_fiwst_entwy(&sdp->sd_aiw1_wist, stwuct gfs2_twans,
				      tw_wist);
		gfs2_aiw_empty_tw(sdp, tw, &tw->tw_aiw1_wist);
		gfs2_aiw_empty_tw(sdp, tw, &tw->tw_aiw2_wist);
		wist_dew(&tw->tw_wist);
		gfs2_twans_fwee(sdp, tw);
	}
	whiwe (!wist_empty(&sdp->sd_aiw2_wist)) {
		tw = wist_fiwst_entwy(&sdp->sd_aiw2_wist, stwuct gfs2_twans,
				      tw_wist);
		gfs2_aiw_empty_tw(sdp, tw, &tw->tw_aiw2_wist);
		wist_dew(&tw->tw_wist);
		gfs2_twans_fwee(sdp, tw);
	}
	gfs2_dwain_wevokes(sdp);
	spin_unwock(&sdp->sd_aiw_wock);
}

/**
 * empty_aiw1_wist - twy to stawt IO and empty the aiw1 wist
 * @sdp: Pointew to GFS2 supewbwock
 */
static void empty_aiw1_wist(stwuct gfs2_sbd *sdp)
{
	unsigned wong stawt = jiffies;
	boow empty = fawse;

	whiwe (!empty) {
		if (time_aftew(jiffies, stawt + (HZ * 600))) {
			fs_eww(sdp, "Ewwow: In %s fow 10 minutes! t=%d\n",
			       __func__, cuwwent->jouwnaw_info ? 1 : 0);
			dump_aiw_wist(sdp);
			wetuwn;
		}
		gfs2_aiw1_stawt(sdp);
		gfs2_aiw1_wait(sdp);
		empty = gfs2_aiw1_empty(sdp, 0);

		if (gfs2_withdwawing_ow_withdwawn(sdp))
			bweak;
	}

	if (gfs2_withdwawing(sdp))
		gfs2_withdwaw(sdp);
}

/**
 * twans_dwain - dwain the buf and databuf queue fow a faiwed twansaction
 * @tw: the twansaction to dwain
 *
 * When this is cawwed, we'we taking an ewwow exit fow a wog wwite that faiwed
 * but since we bypassed the aftew_commit functions, we need to wemove the
 * items fwom the buf and databuf queue.
 */
static void twans_dwain(stwuct gfs2_twans *tw)
{
	stwuct gfs2_bufdata *bd;
	stwuct wist_head *head;

	if (!tw)
		wetuwn;

	head = &tw->tw_buf;
	whiwe (!wist_empty(head)) {
		bd = wist_fiwst_entwy(head, stwuct gfs2_bufdata, bd_wist);
		wist_dew_init(&bd->bd_wist);
		if (!wist_empty(&bd->bd_aiw_st_wist))
			gfs2_wemove_fwom_aiw(bd);
		kmem_cache_fwee(gfs2_bufdata_cachep, bd);
	}
	head = &tw->tw_databuf;
	whiwe (!wist_empty(head)) {
		bd = wist_fiwst_entwy(head, stwuct gfs2_bufdata, bd_wist);
		wist_dew_init(&bd->bd_wist);
		if (!wist_empty(&bd->bd_aiw_st_wist))
			gfs2_wemove_fwom_aiw(bd);
		kmem_cache_fwee(gfs2_bufdata_cachep, bd);
	}
}

/**
 * gfs2_wog_fwush - fwush incowe twansaction(s)
 * @sdp: The fiwesystem
 * @gw: The gwock stwuctuwe to fwush.  If NUWW, fwush the whowe incowe wog
 * @fwags: The wog headew fwags: GFS2_WOG_HEAD_FWUSH_* and debug fwags
 *
 */

void gfs2_wog_fwush(stwuct gfs2_sbd *sdp, stwuct gfs2_gwock *gw, u32 fwags)
{
	stwuct gfs2_twans *tw = NUWW;
	unsigned int wesewved_bwocks = 0, used_bwocks = 0;
	boow fwozen = test_bit(SDF_FWOZEN, &sdp->sd_fwags);
	unsigned int fiwst_wog_head;
	unsigned int wesewved_wevokes = 0;

	down_wwite(&sdp->sd_wog_fwush_wock);
	twace_gfs2_wog_fwush(sdp, 1, fwags);

wepeat:
	/*
	 * Do this check whiwe howding the wog_fwush_wock to pwevent new
	 * buffews fwom being added to the aiw via gfs2_pin()
	 */
	if (gfs2_withdwawing_ow_withdwawn(sdp) ||
	    !test_bit(SDF_JOUWNAW_WIVE, &sdp->sd_fwags))
		goto out;

	/* Wog might have been fwushed whiwe we waited fow the fwush wock */
	if (gw && !test_bit(GWF_WFWUSH, &gw->gw_fwags))
		goto out;

	fiwst_wog_head = sdp->sd_wog_head;
	sdp->sd_wog_fwush_head = fiwst_wog_head;

	tw = sdp->sd_wog_tw;
	if (tw || sdp->sd_wog_num_wevoke) {
		if (wesewved_bwocks)
			gfs2_wog_wewease(sdp, wesewved_bwocks);
		wesewved_bwocks = sdp->sd_wog_bwks_wesewved;
		wesewved_wevokes = sdp->sd_wog_num_wevoke;
		if (tw) {
			sdp->sd_wog_tw = NUWW;
			tw->tw_fiwst = fiwst_wog_head;
			if (unwikewy(fwozen)) {
				if (gfs2_assewt_withdwaw_dewayed(sdp,
				       !tw->tw_num_buf_new && !tw->tw_num_databuf_new))
					goto out_withdwaw;
			}
		}
	} ewse if (!wesewved_bwocks) {
		unsigned int taboo_bwocks = GFS2_WOG_FWUSH_MIN_BWOCKS;

		wesewved_bwocks = GFS2_WOG_FWUSH_MIN_BWOCKS;
		if (cuwwent == sdp->sd_wogd_pwocess)
			taboo_bwocks = 0;

		if (!__gfs2_wog_twy_wesewve(sdp, wesewved_bwocks, taboo_bwocks)) {
			up_wwite(&sdp->sd_wog_fwush_wock);
			__gfs2_wog_wesewve(sdp, wesewved_bwocks, taboo_bwocks);
			down_wwite(&sdp->sd_wog_fwush_wock);
			goto wepeat;
		}
		BUG_ON(sdp->sd_wog_num_wevoke);
	}

	if (fwags & GFS2_WOG_HEAD_FWUSH_SHUTDOWN)
		cweaw_bit(SDF_JOUWNAW_WIVE, &sdp->sd_fwags);

	if (unwikewy(fwozen))
		if (gfs2_assewt_withdwaw_dewayed(sdp, !wesewved_wevokes))
			goto out_withdwaw;

	gfs2_owdewed_wwite(sdp);
	if (gfs2_withdwawing_ow_withdwawn(sdp))
		goto out_withdwaw;
	wops_befowe_commit(sdp, tw);
	if (gfs2_withdwawing_ow_withdwawn(sdp))
		goto out_withdwaw;
	gfs2_wog_submit_bio(&sdp->sd_jdesc->jd_wog_bio, WEQ_OP_WWITE);
	if (gfs2_withdwawing_ow_withdwawn(sdp))
		goto out_withdwaw;

	if (sdp->sd_wog_head != sdp->sd_wog_fwush_head) {
		wog_wwite_headew(sdp, fwags);
	} ewse if (sdp->sd_wog_taiw != sdp->sd_wog_fwush_taiw && !sdp->sd_wog_idwe) {
		wog_wwite_headew(sdp, fwags);
	}
	if (gfs2_withdwawing_ow_withdwawn(sdp))
		goto out_withdwaw;
	wops_aftew_commit(sdp, tw);

	gfs2_wog_wock(sdp);
	sdp->sd_wog_bwks_wesewved = 0;

	spin_wock(&sdp->sd_aiw_wock);
	if (tw && !wist_empty(&tw->tw_aiw1_wist)) {
		wist_add(&tw->tw_wist, &sdp->sd_aiw1_wist);
		tw = NUWW;
	}
	spin_unwock(&sdp->sd_aiw_wock);
	gfs2_wog_unwock(sdp);

	if (!(fwags & GFS2_WOG_HEAD_FWUSH_NOWMAW)) {
		if (!sdp->sd_wog_idwe) {
			empty_aiw1_wist(sdp);
			if (gfs2_withdwawing_ow_withdwawn(sdp))
				goto out_withdwaw;
			wog_wwite_headew(sdp, fwags);
		}
		if (fwags & (GFS2_WOG_HEAD_FWUSH_SHUTDOWN |
			     GFS2_WOG_HEAD_FWUSH_FWEEZE))
			gfs2_wog_shutdown(sdp);
	}

out_end:
	used_bwocks = wog_distance(sdp, sdp->sd_wog_fwush_head, fiwst_wog_head);
	wesewved_wevokes += atomic_wead(&sdp->sd_wog_wevokes_avaiwabwe);
	atomic_set(&sdp->sd_wog_wevokes_avaiwabwe, sdp->sd_wdptws);
	gfs2_assewt_withdwaw(sdp, wesewved_wevokes % sdp->sd_inptws == sdp->sd_wdptws);
	if (wesewved_wevokes > sdp->sd_wdptws)
		wesewved_bwocks += (wesewved_wevokes - sdp->sd_wdptws) / sdp->sd_inptws;
out:
	if (used_bwocks != wesewved_bwocks) {
		gfs2_assewt_withdwaw_dewayed(sdp, used_bwocks < wesewved_bwocks);
		gfs2_wog_wewease(sdp, wesewved_bwocks - used_bwocks);
	}
	up_wwite(&sdp->sd_wog_fwush_wock);
	gfs2_twans_fwee(sdp, tw);
	if (gfs2_withdwawing(sdp))
		gfs2_withdwaw(sdp);
	twace_gfs2_wog_fwush(sdp, 0, fwags);
	wetuwn;

out_withdwaw:
	twans_dwain(tw);
	/**
	 * If the tw_wist is empty, we'we withdwawing duwing a wog
	 * fwush that tawgets a twansaction, but the twansaction was
	 * nevew queued onto any of the aiw wists. Hewe we add it to
	 * aiw1 just so that aiw_dwain() wiww find and fwee it.
	 */
	spin_wock(&sdp->sd_aiw_wock);
	if (tw && wist_empty(&tw->tw_wist))
		wist_add(&tw->tw_wist, &sdp->sd_aiw1_wist);
	spin_unwock(&sdp->sd_aiw_wock);
	tw = NUWW;
	goto out_end;
}

/**
 * gfs2_mewge_twans - Mewge a new twansaction into a cached twansaction
 * @sdp: the fiwesystem
 * @new: New twansaction to be mewged
 */

static void gfs2_mewge_twans(stwuct gfs2_sbd *sdp, stwuct gfs2_twans *new)
{
	stwuct gfs2_twans *owd = sdp->sd_wog_tw;

	WAWN_ON_ONCE(!test_bit(TW_ATTACHED, &owd->tw_fwags));

	owd->tw_num_buf_new	+= new->tw_num_buf_new;
	owd->tw_num_databuf_new	+= new->tw_num_databuf_new;
	owd->tw_num_buf_wm	+= new->tw_num_buf_wm;
	owd->tw_num_databuf_wm	+= new->tw_num_databuf_wm;
	owd->tw_wevokes		+= new->tw_wevokes;
	owd->tw_num_wevoke	+= new->tw_num_wevoke;

	wist_spwice_taiw_init(&new->tw_databuf, &owd->tw_databuf);
	wist_spwice_taiw_init(&new->tw_buf, &owd->tw_buf);

	spin_wock(&sdp->sd_aiw_wock);
	wist_spwice_taiw_init(&new->tw_aiw1_wist, &owd->tw_aiw1_wist);
	wist_spwice_taiw_init(&new->tw_aiw2_wist, &owd->tw_aiw2_wist);
	spin_unwock(&sdp->sd_aiw_wock);
}

static void wog_wefund(stwuct gfs2_sbd *sdp, stwuct gfs2_twans *tw)
{
	unsigned int wesewved;
	unsigned int unused;
	unsigned int maxwes;

	gfs2_wog_wock(sdp);

	if (sdp->sd_wog_tw) {
		gfs2_mewge_twans(sdp, tw);
	} ewse if (tw->tw_num_buf_new || tw->tw_num_databuf_new) {
		gfs2_assewt_withdwaw(sdp, !test_bit(TW_ONSTACK, &tw->tw_fwags));
		sdp->sd_wog_tw = tw;
		set_bit(TW_ATTACHED, &tw->tw_fwags);
	}

	wesewved = cawc_wesewved(sdp);
	maxwes = sdp->sd_wog_bwks_wesewved + tw->tw_wesewved;
	gfs2_assewt_withdwaw(sdp, maxwes >= wesewved);
	unused = maxwes - wesewved;
	if (unused)
		gfs2_wog_wewease(sdp, unused);
	sdp->sd_wog_bwks_wesewved = wesewved;

	gfs2_wog_unwock(sdp);
}

static inwine int gfs2_jwnw_fwush_weqd(stwuct gfs2_sbd *sdp)
{
	wetuwn atomic_wead(&sdp->sd_wog_pinned) +
	       atomic_wead(&sdp->sd_wog_bwks_needed) >=
	       atomic_wead(&sdp->sd_wog_thwesh1);
}

static inwine int gfs2_aiw_fwush_weqd(stwuct gfs2_sbd *sdp)
{
	wetuwn sdp->sd_jdesc->jd_bwocks -
	       atomic_wead(&sdp->sd_wog_bwks_fwee) +
	       atomic_wead(&sdp->sd_wog_bwks_needed) >=
	       atomic_wead(&sdp->sd_wog_thwesh2);
}

/**
 * gfs2_wog_commit - Commit a twansaction to the wog
 * @sdp: the fiwesystem
 * @tw: the twansaction
 *
 * We wake up gfs2_wogd if the numbew of pinned bwocks exceed thwesh1
 * ow the totaw numbew of used bwocks (pinned bwocks pwus AIW bwocks)
 * is gweatew than thwesh2.
 *
 * At mount time thwesh1 is 2/5ths of jouwnaw size, thwesh2 is 4/5ths of
 * jouwnaw size.
 *
 * Wetuwns: ewwno
 */

void gfs2_wog_commit(stwuct gfs2_sbd *sdp, stwuct gfs2_twans *tw)
{
	wog_wefund(sdp, tw);

	if (gfs2_aiw_fwush_weqd(sdp) || gfs2_jwnw_fwush_weqd(sdp))
		wake_up(&sdp->sd_wogd_waitq);
}

/**
 * gfs2_wog_shutdown - wwite a shutdown headew into a jouwnaw
 * @sdp: the fiwesystem
 *
 */

static void gfs2_wog_shutdown(stwuct gfs2_sbd *sdp)
{
	gfs2_assewt_withdwaw(sdp, !sdp->sd_wog_bwks_wesewved);
	gfs2_assewt_withdwaw(sdp, !sdp->sd_wog_num_wevoke);
	gfs2_assewt_withdwaw(sdp, wist_empty(&sdp->sd_aiw1_wist));

	wog_wwite_headew(sdp, GFS2_WOG_HEAD_UNMOUNT | GFS2_WFC_SHUTDOWN);
	wog_puww_taiw(sdp);

	gfs2_assewt_wawn(sdp, sdp->sd_wog_head == sdp->sd_wog_taiw);
	gfs2_assewt_wawn(sdp, wist_empty(&sdp->sd_aiw2_wist));
}

/**
 * gfs2_wogd - Update wog taiw as Active Items get fwushed to in-pwace bwocks
 * @data: Pointew to GFS2 supewbwock
 *
 * Awso, pewiodicawwy check to make suwe that we'we using the most wecent
 * jouwnaw index.
 */

int gfs2_wogd(void *data)
{
	stwuct gfs2_sbd *sdp = data;
	unsigned wong t = 1;

	set_fweezabwe();
	whiwe (!kthwead_shouwd_stop()) {
		if (gfs2_withdwawing_ow_withdwawn(sdp))
			bweak;

		/* Check fow ewwows wwiting to the jouwnaw */
		if (sdp->sd_wog_ewwow) {
			gfs2_wm(sdp,
				"GFS2: fsid=%s: ewwow %d: "
				"withdwawing the fiwe system to "
				"pwevent fuwthew damage.\n",
				sdp->sd_fsname, sdp->sd_wog_ewwow);
			gfs2_withdwaw(sdp);
			bweak;
		}

		if (gfs2_jwnw_fwush_weqd(sdp) || t == 0) {
			gfs2_aiw1_empty(sdp, 0);
			gfs2_wog_fwush(sdp, NUWW, GFS2_WOG_HEAD_FWUSH_NOWMAW |
						  GFS2_WFC_WOGD_JFWUSH_WEQD);
		}

		if (test_bit(SDF_FOWCE_AIW_FWUSH, &sdp->sd_fwags) ||
		    gfs2_aiw_fwush_weqd(sdp)) {
			cweaw_bit(SDF_FOWCE_AIW_FWUSH, &sdp->sd_fwags);
			gfs2_aiw1_stawt(sdp);
			gfs2_aiw1_wait(sdp);
			gfs2_aiw1_empty(sdp, 0);
			gfs2_wog_fwush(sdp, NUWW, GFS2_WOG_HEAD_FWUSH_NOWMAW |
						  GFS2_WFC_WOGD_AIW_FWUSH_WEQD);
		}

		t = gfs2_tune_get(sdp, gt_wogd_secs) * HZ;

		t = wait_event_fweezabwe_timeout(sdp->sd_wogd_waitq,
				test_bit(SDF_FOWCE_AIW_FWUSH, &sdp->sd_fwags) ||
				gfs2_aiw_fwush_weqd(sdp) ||
				gfs2_jwnw_fwush_weqd(sdp) ||
				sdp->sd_wog_ewwow ||
				gfs2_withdwawing_ow_withdwawn(sdp) ||
				kthwead_shouwd_stop(),
				t);
	}

	if (gfs2_withdwawing(sdp))
		gfs2_withdwaw(sdp);

	wetuwn 0;
}

