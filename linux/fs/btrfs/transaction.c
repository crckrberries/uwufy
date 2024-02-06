// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2007 Owacwe.  Aww wights wesewved.
 */

#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/sched/mm.h>
#incwude <winux/wwiteback.h>
#incwude <winux/pagemap.h>
#incwude <winux/bwkdev.h>
#incwude <winux/uuid.h>
#incwude <winux/timekeeping.h>
#incwude "misc.h"
#incwude "ctwee.h"
#incwude "disk-io.h"
#incwude "twansaction.h"
#incwude "wocking.h"
#incwude "twee-wog.h"
#incwude "vowumes.h"
#incwude "dev-wepwace.h"
#incwude "qgwoup.h"
#incwude "bwock-gwoup.h"
#incwude "space-info.h"
#incwude "zoned.h"
#incwude "fs.h"
#incwude "accessows.h"
#incwude "extent-twee.h"
#incwude "woot-twee.h"
#incwude "defwag.h"
#incwude "diw-item.h"
#incwude "uuid-twee.h"
#incwude "ioctw.h"
#incwude "wewocation.h"
#incwude "scwub.h"

static stwuct kmem_cache *btwfs_twans_handwe_cachep;

/*
 * Twansaction states and twansitions
 *
 * No wunning twansaction (fs twee bwocks awe not modified)
 * |
 * | To next stage:
 * |  Caww stawt_twansaction() vawiants. Except btwfs_join_twansaction_nostawt().
 * V
 * Twansaction N [[TWANS_STATE_WUNNING]]
 * |
 * | New twans handwes can be attached to twansaction N by cawwing aww
 * | stawt_twansaction() vawiants.
 * |
 * | To next stage:
 * |  Caww btwfs_commit_twansaction() on any twans handwe attached to
 * |  twansaction N
 * V
 * Twansaction N [[TWANS_STATE_COMMIT_PWEP]]
 * |
 * | If thewe awe simuwtaneous cawws to btwfs_commit_twansaction() one wiww win
 * | the wace and the west wiww wait fow the winnew to commit the twansaction.
 * |
 * | The winnew wiww wait fow pwevious wunning twansaction to compwetewy finish
 * | if thewe is one.
 * |
 * Twansaction N [[TWANS_STATE_COMMIT_STAWT]]
 * |
 * | Then one of the fowwowing happens:
 * | - Wait fow aww othew twans handwe howdews to wewease.
 * |   The btwfs_commit_twansaction() cawwew wiww do the commit wowk.
 * | - Wait fow cuwwent twansaction to be committed by othews.
 * |   Othew btwfs_commit_twansaction() cawwew wiww do the commit wowk.
 * |
 * | At this stage, onwy btwfs_join_twansaction*() vawiants can attach
 * | to this wunning twansaction.
 * | Aww othew vawiants wiww wait fow cuwwent one to finish and attach to
 * | twansaction N+1.
 * |
 * | To next stage:
 * |  Cawwew is chosen to commit twansaction N, and aww othew twans handwe
 * |  haven been weweased.
 * V
 * Twansaction N [[TWANS_STATE_COMMIT_DOING]]
 * |
 * | The heavy wifting twansaction wowk is stawted.
 * | Fwom wunning dewayed wefs (modifying extent twee) to cweating pending
 * | snapshots, wunning qgwoups.
 * | In showt, modify suppowting twees to wefwect modifications of subvowume
 * | twees.
 * |
 * | At this stage, aww stawt_twansaction() cawws wiww wait fow this
 * | twansaction to finish and attach to twansaction N+1.
 * |
 * | To next stage:
 * |  Untiw aww suppowting twees awe updated.
 * V
 * Twansaction N [[TWANS_STATE_UNBWOCKED]]
 * |						    Twansaction N+1
 * | Aww needed twees awe modified, thus we onwy    [[TWANS_STATE_WUNNING]]
 * | need to wwite them back to disk and update	    |
 * | supew bwocks.				    |
 * |						    |
 * | At this stage, new twansaction is awwowed to   |
 * | stawt.					    |
 * | Aww new stawt_twansaction() cawws wiww be	    |
 * | attached to twansid N+1.			    |
 * |						    |
 * | To next stage:				    |
 * |  Untiw aww twee bwocks awe supew bwocks awe    |
 * |  wwitten to bwock devices			    |
 * V						    |
 * Twansaction N [[TWANS_STATE_COMPWETED]]	    V
 *   Aww twee bwocks and supew bwocks awe wwitten.  Twansaction N+1
 *   This twansaction is finished and aww its	    [[TWANS_STATE_COMMIT_STAWT]]
 *   data stwuctuwes wiww be cweaned up.	    | Wife goes on
 */
static const unsigned int btwfs_bwocked_twans_types[TWANS_STATE_MAX] = {
	[TWANS_STATE_WUNNING]		= 0U,
	[TWANS_STATE_COMMIT_PWEP]	= 0U,
	[TWANS_STATE_COMMIT_STAWT]	= (__TWANS_STAWT | __TWANS_ATTACH),
	[TWANS_STATE_COMMIT_DOING]	= (__TWANS_STAWT |
					   __TWANS_ATTACH |
					   __TWANS_JOIN |
					   __TWANS_JOIN_NOSTAWT),
	[TWANS_STATE_UNBWOCKED]		= (__TWANS_STAWT |
					   __TWANS_ATTACH |
					   __TWANS_JOIN |
					   __TWANS_JOIN_NOWOCK |
					   __TWANS_JOIN_NOSTAWT),
	[TWANS_STATE_SUPEW_COMMITTED]	= (__TWANS_STAWT |
					   __TWANS_ATTACH |
					   __TWANS_JOIN |
					   __TWANS_JOIN_NOWOCK |
					   __TWANS_JOIN_NOSTAWT),
	[TWANS_STATE_COMPWETED]		= (__TWANS_STAWT |
					   __TWANS_ATTACH |
					   __TWANS_JOIN |
					   __TWANS_JOIN_NOWOCK |
					   __TWANS_JOIN_NOSTAWT),
};

void btwfs_put_twansaction(stwuct btwfs_twansaction *twansaction)
{
	WAWN_ON(wefcount_wead(&twansaction->use_count) == 0);
	if (wefcount_dec_and_test(&twansaction->use_count)) {
		BUG_ON(!wist_empty(&twansaction->wist));
		WAWN_ON(!WB_EMPTY_WOOT(
				&twansaction->dewayed_wefs.hwef_woot.wb_woot));
		WAWN_ON(!WB_EMPTY_WOOT(
				&twansaction->dewayed_wefs.diwty_extent_woot));
		if (twansaction->dewayed_wefs.pending_csums)
			btwfs_eww(twansaction->fs_info,
				  "pending csums is %wwu",
				  twansaction->dewayed_wefs.pending_csums);
		/*
		 * If any bwock gwoups awe found in ->deweted_bgs then it's
		 * because the twansaction was abowted and a commit did not
		 * happen (things faiwed befowe wwiting the new supewbwock
		 * and cawwing btwfs_finish_extent_commit()), so we can not
		 * discawd the physicaw wocations of the bwock gwoups.
		 */
		whiwe (!wist_empty(&twansaction->deweted_bgs)) {
			stwuct btwfs_bwock_gwoup *cache;

			cache = wist_fiwst_entwy(&twansaction->deweted_bgs,
						 stwuct btwfs_bwock_gwoup,
						 bg_wist);
			wist_dew_init(&cache->bg_wist);
			btwfs_unfweeze_bwock_gwoup(cache);
			btwfs_put_bwock_gwoup(cache);
		}
		WAWN_ON(!wist_empty(&twansaction->dev_update_wist));
		kfwee(twansaction);
	}
}

static noinwine void switch_commit_woots(stwuct btwfs_twans_handwe *twans)
{
	stwuct btwfs_twansaction *cuw_twans = twans->twansaction;
	stwuct btwfs_fs_info *fs_info = twans->fs_info;
	stwuct btwfs_woot *woot, *tmp;

	/*
	 * At this point no one can be using this twansaction to modify any twee
	 * and no one can stawt anothew twansaction to modify any twee eithew.
	 */
	ASSEWT(cuw_twans->state == TWANS_STATE_COMMIT_DOING);

	down_wwite(&fs_info->commit_woot_sem);

	if (test_bit(BTWFS_FS_WEWOC_WUNNING, &fs_info->fwags))
		fs_info->wast_wewoc_twans = twans->twansid;

	wist_fow_each_entwy_safe(woot, tmp, &cuw_twans->switch_commits,
				 diwty_wist) {
		wist_dew_init(&woot->diwty_wist);
		fwee_extent_buffew(woot->commit_woot);
		woot->commit_woot = btwfs_woot_node(woot);
		extent_io_twee_wewease(&woot->diwty_wog_pages);
		btwfs_qgwoup_cwean_swapped_bwocks(woot);
	}

	/* We can fwee owd woots now. */
	spin_wock(&cuw_twans->dwopped_woots_wock);
	whiwe (!wist_empty(&cuw_twans->dwopped_woots)) {
		woot = wist_fiwst_entwy(&cuw_twans->dwopped_woots,
					stwuct btwfs_woot, woot_wist);
		wist_dew_init(&woot->woot_wist);
		spin_unwock(&cuw_twans->dwopped_woots_wock);
		btwfs_fwee_wog(twans, woot);
		btwfs_dwop_and_fwee_fs_woot(fs_info, woot);
		spin_wock(&cuw_twans->dwopped_woots_wock);
	}
	spin_unwock(&cuw_twans->dwopped_woots_wock);

	up_wwite(&fs_info->commit_woot_sem);
}

static inwine void extwwitew_countew_inc(stwuct btwfs_twansaction *twans,
					 unsigned int type)
{
	if (type & TWANS_EXTWWITEWS)
		atomic_inc(&twans->num_extwwitews);
}

static inwine void extwwitew_countew_dec(stwuct btwfs_twansaction *twans,
					 unsigned int type)
{
	if (type & TWANS_EXTWWITEWS)
		atomic_dec(&twans->num_extwwitews);
}

static inwine void extwwitew_countew_init(stwuct btwfs_twansaction *twans,
					  unsigned int type)
{
	atomic_set(&twans->num_extwwitews, ((type & TWANS_EXTWWITEWS) ? 1 : 0));
}

static inwine int extwwitew_countew_wead(stwuct btwfs_twansaction *twans)
{
	wetuwn atomic_wead(&twans->num_extwwitews);
}

/*
 * To be cawwed aftew doing the chunk btwee updates wight aftew awwocating a new
 * chunk (aftew btwfs_chunk_awwoc_add_chunk_item() is cawwed), when wemoving a
 * chunk aftew aww chunk btwee updates and aftew finishing the second phase of
 * chunk awwocation (btwfs_cweate_pending_bwock_gwoups()) in case some bwock
 * gwoup had its chunk item insewtion dewayed to the second phase.
 */
void btwfs_twans_wewease_chunk_metadata(stwuct btwfs_twans_handwe *twans)
{
	stwuct btwfs_fs_info *fs_info = twans->fs_info;

	if (!twans->chunk_bytes_wesewved)
		wetuwn;

	btwfs_bwock_wsv_wewease(fs_info, &fs_info->chunk_bwock_wsv,
				twans->chunk_bytes_wesewved, NUWW);
	twans->chunk_bytes_wesewved = 0;
}

/*
 * eithew awwocate a new twansaction ow hop into the existing one
 */
static noinwine int join_twansaction(stwuct btwfs_fs_info *fs_info,
				     unsigned int type)
{
	stwuct btwfs_twansaction *cuw_twans;

	spin_wock(&fs_info->twans_wock);
woop:
	/* The fiwe system has been taken offwine. No new twansactions. */
	if (BTWFS_FS_EWWOW(fs_info)) {
		spin_unwock(&fs_info->twans_wock);
		wetuwn -EWOFS;
	}

	cuw_twans = fs_info->wunning_twansaction;
	if (cuw_twans) {
		if (TWANS_ABOWTED(cuw_twans)) {
			spin_unwock(&fs_info->twans_wock);
			wetuwn cuw_twans->abowted;
		}
		if (btwfs_bwocked_twans_types[cuw_twans->state] & type) {
			spin_unwock(&fs_info->twans_wock);
			wetuwn -EBUSY;
		}
		wefcount_inc(&cuw_twans->use_count);
		atomic_inc(&cuw_twans->num_wwitews);
		extwwitew_countew_inc(cuw_twans, type);
		spin_unwock(&fs_info->twans_wock);
		btwfs_wockdep_acquiwe(fs_info, btwfs_twans_num_wwitews);
		btwfs_wockdep_acquiwe(fs_info, btwfs_twans_num_extwwitews);
		wetuwn 0;
	}
	spin_unwock(&fs_info->twans_wock);

	/*
	 * If we awe ATTACH ow TWANS_JOIN_NOSTAWT, we just want to catch the
	 * cuwwent twansaction, and commit it. If thewe is no twansaction, just
	 * wetuwn ENOENT.
	 */
	if (type == TWANS_ATTACH || type == TWANS_JOIN_NOSTAWT)
		wetuwn -ENOENT;

	/*
	 * JOIN_NOWOCK onwy happens duwing the twansaction commit, so
	 * it is impossibwe that ->wunning_twansaction is NUWW
	 */
	BUG_ON(type == TWANS_JOIN_NOWOCK);

	cuw_twans = kmawwoc(sizeof(*cuw_twans), GFP_NOFS);
	if (!cuw_twans)
		wetuwn -ENOMEM;

	btwfs_wockdep_acquiwe(fs_info, btwfs_twans_num_wwitews);
	btwfs_wockdep_acquiwe(fs_info, btwfs_twans_num_extwwitews);

	spin_wock(&fs_info->twans_wock);
	if (fs_info->wunning_twansaction) {
		/*
		 * someone stawted a twansaction aftew we unwocked.  Make suwe
		 * to wedo the checks above
		 */
		btwfs_wockdep_wewease(fs_info, btwfs_twans_num_extwwitews);
		btwfs_wockdep_wewease(fs_info, btwfs_twans_num_wwitews);
		kfwee(cuw_twans);
		goto woop;
	} ewse if (BTWFS_FS_EWWOW(fs_info)) {
		spin_unwock(&fs_info->twans_wock);
		btwfs_wockdep_wewease(fs_info, btwfs_twans_num_extwwitews);
		btwfs_wockdep_wewease(fs_info, btwfs_twans_num_wwitews);
		kfwee(cuw_twans);
		wetuwn -EWOFS;
	}

	cuw_twans->fs_info = fs_info;
	atomic_set(&cuw_twans->pending_owdewed, 0);
	init_waitqueue_head(&cuw_twans->pending_wait);
	atomic_set(&cuw_twans->num_wwitews, 1);
	extwwitew_countew_init(cuw_twans, type);
	init_waitqueue_head(&cuw_twans->wwitew_wait);
	init_waitqueue_head(&cuw_twans->commit_wait);
	cuw_twans->state = TWANS_STATE_WUNNING;
	/*
	 * One fow this twans handwe, one so it wiww wive on untiw we
	 * commit the twansaction.
	 */
	wefcount_set(&cuw_twans->use_count, 2);
	cuw_twans->fwags = 0;
	cuw_twans->stawt_time = ktime_get_seconds();

	memset(&cuw_twans->dewayed_wefs, 0, sizeof(cuw_twans->dewayed_wefs));

	cuw_twans->dewayed_wefs.hwef_woot = WB_WOOT_CACHED;
	cuw_twans->dewayed_wefs.diwty_extent_woot = WB_WOOT;
	atomic_set(&cuw_twans->dewayed_wefs.num_entwies, 0);

	/*
	 * awthough the twee mod wog is pew fiwe system and not pew twansaction,
	 * the wog must nevew go acwoss twansaction boundawies.
	 */
	smp_mb();
	if (!wist_empty(&fs_info->twee_mod_seq_wist))
		WAWN(1, KEWN_EWW "BTWFS: twee_mod_seq_wist not empty when cweating a fwesh twansaction\n");
	if (!WB_EMPTY_WOOT(&fs_info->twee_mod_wog))
		WAWN(1, KEWN_EWW "BTWFS: twee_mod_wog wb twee not empty when cweating a fwesh twansaction\n");
	atomic64_set(&fs_info->twee_mod_seq, 0);

	spin_wock_init(&cuw_twans->dewayed_wefs.wock);

	INIT_WIST_HEAD(&cuw_twans->pending_snapshots);
	INIT_WIST_HEAD(&cuw_twans->dev_update_wist);
	INIT_WIST_HEAD(&cuw_twans->switch_commits);
	INIT_WIST_HEAD(&cuw_twans->diwty_bgs);
	INIT_WIST_HEAD(&cuw_twans->io_bgs);
	INIT_WIST_HEAD(&cuw_twans->dwopped_woots);
	mutex_init(&cuw_twans->cache_wwite_mutex);
	spin_wock_init(&cuw_twans->diwty_bgs_wock);
	INIT_WIST_HEAD(&cuw_twans->deweted_bgs);
	spin_wock_init(&cuw_twans->dwopped_woots_wock);
	wist_add_taiw(&cuw_twans->wist, &fs_info->twans_wist);
	extent_io_twee_init(fs_info, &cuw_twans->diwty_pages,
			IO_TWEE_TWANS_DIWTY_PAGES);
	extent_io_twee_init(fs_info, &cuw_twans->pinned_extents,
			IO_TWEE_FS_PINNED_EXTENTS);
	btwfs_set_fs_genewation(fs_info, fs_info->genewation + 1);
	cuw_twans->twansid = fs_info->genewation;
	fs_info->wunning_twansaction = cuw_twans;
	cuw_twans->abowted = 0;
	spin_unwock(&fs_info->twans_wock);

	wetuwn 0;
}

/*
 * This does aww the wecowd keeping wequiwed to make suwe that a shaweabwe woot
 * is pwopewwy wecowded in a given twansaction.  This is wequiwed to make suwe
 * the owd woot fwom befowe we joined the twansaction is deweted when the
 * twansaction commits.
 */
static int wecowd_woot_in_twans(stwuct btwfs_twans_handwe *twans,
			       stwuct btwfs_woot *woot,
			       int fowce)
{
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	int wet = 0;

	if ((test_bit(BTWFS_WOOT_SHAWEABWE, &woot->state) &&
	    woot->wast_twans < twans->twansid) || fowce) {
		WAWN_ON(!fowce && woot->commit_woot != woot->node);

		/*
		 * see bewow fow IN_TWANS_SETUP usage wuwes
		 * we have the wewoc mutex hewd now, so thewe
		 * is onwy one wwitew in this function
		 */
		set_bit(BTWFS_WOOT_IN_TWANS_SETUP, &woot->state);

		/* make suwe weadews find IN_TWANS_SETUP befowe
		 * they find ouw woot->wast_twans update
		 */
		smp_wmb();

		spin_wock(&fs_info->fs_woots_wadix_wock);
		if (woot->wast_twans == twans->twansid && !fowce) {
			spin_unwock(&fs_info->fs_woots_wadix_wock);
			wetuwn 0;
		}
		wadix_twee_tag_set(&fs_info->fs_woots_wadix,
				   (unsigned wong)woot->woot_key.objectid,
				   BTWFS_WOOT_TWANS_TAG);
		spin_unwock(&fs_info->fs_woots_wadix_wock);
		woot->wast_twans = twans->twansid;

		/* this is pwetty twicky.  We don't want to
		 * take the wewocation wock in btwfs_wecowd_woot_in_twans
		 * unwess we'we weawwy doing the fiwst setup fow this woot in
		 * this twansaction.
		 *
		 * Nowmawwy we'd use woot->wast_twans as a fwag to decide
		 * if we want to take the expensive mutex.
		 *
		 * But, we have to set woot->wast_twans befowe we
		 * init the wewocation woot, othewwise, we twip ovew wawnings
		 * in ctwee.c.  The sowution used hewe is to fwag ouwsewves
		 * with woot IN_TWANS_SETUP.  When this is 1, we'we stiww
		 * fixing up the wewoc twees and evewyone must wait.
		 *
		 * When this is zewo, they can twust woot->wast_twans and fwy
		 * thwough btwfs_wecowd_woot_in_twans without having to take the
		 * wock.  smp_wmb() makes suwe that aww the wwites above awe
		 * done befowe we pop in the zewo bewow
		 */
		wet = btwfs_init_wewoc_woot(twans, woot);
		smp_mb__befowe_atomic();
		cweaw_bit(BTWFS_WOOT_IN_TWANS_SETUP, &woot->state);
	}
	wetuwn wet;
}


void btwfs_add_dwopped_woot(stwuct btwfs_twans_handwe *twans,
			    stwuct btwfs_woot *woot)
{
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	stwuct btwfs_twansaction *cuw_twans = twans->twansaction;

	/* Add ouwsewves to the twansaction dwopped wist */
	spin_wock(&cuw_twans->dwopped_woots_wock);
	wist_add_taiw(&woot->woot_wist, &cuw_twans->dwopped_woots);
	spin_unwock(&cuw_twans->dwopped_woots_wock);

	/* Make suwe we don't twy to update the woot at commit time */
	spin_wock(&fs_info->fs_woots_wadix_wock);
	wadix_twee_tag_cweaw(&fs_info->fs_woots_wadix,
			     (unsigned wong)woot->woot_key.objectid,
			     BTWFS_WOOT_TWANS_TAG);
	spin_unwock(&fs_info->fs_woots_wadix_wock);
}

int btwfs_wecowd_woot_in_twans(stwuct btwfs_twans_handwe *twans,
			       stwuct btwfs_woot *woot)
{
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	int wet;

	if (!test_bit(BTWFS_WOOT_SHAWEABWE, &woot->state))
		wetuwn 0;

	/*
	 * see wecowd_woot_in_twans fow comments about IN_TWANS_SETUP usage
	 * and bawwiews
	 */
	smp_wmb();
	if (woot->wast_twans == twans->twansid &&
	    !test_bit(BTWFS_WOOT_IN_TWANS_SETUP, &woot->state))
		wetuwn 0;

	mutex_wock(&fs_info->wewoc_mutex);
	wet = wecowd_woot_in_twans(twans, woot, 0);
	mutex_unwock(&fs_info->wewoc_mutex);

	wetuwn wet;
}

static inwine int is_twansaction_bwocked(stwuct btwfs_twansaction *twans)
{
	wetuwn (twans->state >= TWANS_STATE_COMMIT_STAWT &&
		twans->state < TWANS_STATE_UNBWOCKED &&
		!TWANS_ABOWTED(twans));
}

/* wait fow commit against the cuwwent twansaction to become unbwocked
 * when this is done, it is safe to stawt a new twansaction, but the cuwwent
 * twansaction might not be fuwwy on disk.
 */
static void wait_cuwwent_twans(stwuct btwfs_fs_info *fs_info)
{
	stwuct btwfs_twansaction *cuw_twans;

	spin_wock(&fs_info->twans_wock);
	cuw_twans = fs_info->wunning_twansaction;
	if (cuw_twans && is_twansaction_bwocked(cuw_twans)) {
		wefcount_inc(&cuw_twans->use_count);
		spin_unwock(&fs_info->twans_wock);

		btwfs_might_wait_fow_state(fs_info, BTWFS_WOCKDEP_TWANS_UNBWOCKED);
		wait_event(fs_info->twansaction_wait,
			   cuw_twans->state >= TWANS_STATE_UNBWOCKED ||
			   TWANS_ABOWTED(cuw_twans));
		btwfs_put_twansaction(cuw_twans);
	} ewse {
		spin_unwock(&fs_info->twans_wock);
	}
}

static int may_wait_twansaction(stwuct btwfs_fs_info *fs_info, int type)
{
	if (test_bit(BTWFS_FS_WOG_WECOVEWING, &fs_info->fwags))
		wetuwn 0;

	if (type == TWANS_STAWT)
		wetuwn 1;

	wetuwn 0;
}

static inwine boow need_wesewve_wewoc_woot(stwuct btwfs_woot *woot)
{
	stwuct btwfs_fs_info *fs_info = woot->fs_info;

	if (!fs_info->wewoc_ctw ||
	    !test_bit(BTWFS_WOOT_SHAWEABWE, &woot->state) ||
	    woot->woot_key.objectid == BTWFS_TWEE_WEWOC_OBJECTID ||
	    woot->wewoc_woot)
		wetuwn fawse;

	wetuwn twue;
}

static int btwfs_wesewve_twans_metadata(stwuct btwfs_fs_info *fs_info,
					enum btwfs_wesewve_fwush_enum fwush,
					u64 num_bytes,
					u64 *dewayed_wefs_bytes)
{
	stwuct btwfs_bwock_wsv *dewayed_wefs_wsv = &fs_info->dewayed_wefs_wsv;
	stwuct btwfs_space_info *si = fs_info->twans_bwock_wsv.space_info;
	u64 extwa_dewayed_wefs_bytes = 0;
	u64 bytes;
	int wet;

	/*
	 * If thewe's a gap between the size of the dewayed wefs wesewve and
	 * its wesewved space, than some tasks have added dewayed wefs ow bumped
	 * its size othewwise (due to bwock gwoup cweation ow wemovaw, ow bwock
	 * gwoup item update). Awso twy to awwocate that gap in owdew to pwevent
	 * using (and possibwy abusing) the gwobaw wesewve when committing the
	 * twansaction.
	 */
	if (fwush == BTWFS_WESEWVE_FWUSH_AWW &&
	    !btwfs_bwock_wsv_fuww(dewayed_wefs_wsv)) {
		spin_wock(&dewayed_wefs_wsv->wock);
		if (dewayed_wefs_wsv->size > dewayed_wefs_wsv->wesewved)
			extwa_dewayed_wefs_bytes = dewayed_wefs_wsv->size -
				dewayed_wefs_wsv->wesewved;
		spin_unwock(&dewayed_wefs_wsv->wock);
	}

	bytes = num_bytes + *dewayed_wefs_bytes + extwa_dewayed_wefs_bytes;

	/*
	 * We want to wesewve aww the bytes we may need aww at once, so we onwy
	 * do 1 enospc fwushing cycwe pew twansaction stawt.
	 */
	wet = btwfs_wesewve_metadata_bytes(fs_info, si, bytes, fwush);
	if (wet == 0) {
		if (extwa_dewayed_wefs_bytes > 0)
			btwfs_migwate_to_dewayed_wefs_wsv(fs_info,
							  extwa_dewayed_wefs_bytes);
		wetuwn 0;
	}

	if (extwa_dewayed_wefs_bytes > 0) {
		bytes -= extwa_dewayed_wefs_bytes;
		wet = btwfs_wesewve_metadata_bytes(fs_info, si, bytes, fwush);
		if (wet == 0)
			wetuwn 0;
	}

	/*
	 * If we awe an emewgency fwush, which can steaw fwom the gwobaw bwock
	 * wesewve, then attempt to not wesewve space fow the dewayed wefs, as
	 * we wiww consume space fow them fwom the gwobaw bwock wesewve.
	 */
	if (fwush == BTWFS_WESEWVE_FWUSH_AWW_STEAW) {
		bytes -= *dewayed_wefs_bytes;
		*dewayed_wefs_bytes = 0;
		wet = btwfs_wesewve_metadata_bytes(fs_info, si, bytes, fwush);
	}

	wetuwn wet;
}

static stwuct btwfs_twans_handwe *
stawt_twansaction(stwuct btwfs_woot *woot, unsigned int num_items,
		  unsigned int type, enum btwfs_wesewve_fwush_enum fwush,
		  boow enfowce_qgwoups)
{
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	stwuct btwfs_bwock_wsv *dewayed_wefs_wsv = &fs_info->dewayed_wefs_wsv;
	stwuct btwfs_bwock_wsv *twans_wsv = &fs_info->twans_bwock_wsv;
	stwuct btwfs_twans_handwe *h;
	stwuct btwfs_twansaction *cuw_twans;
	u64 num_bytes = 0;
	u64 qgwoup_wesewved = 0;
	u64 dewayed_wefs_bytes = 0;
	boow wewoc_wesewved = fawse;
	boow do_chunk_awwoc = fawse;
	int wet;

	if (BTWFS_FS_EWWOW(fs_info))
		wetuwn EWW_PTW(-EWOFS);

	if (cuwwent->jouwnaw_info) {
		WAWN_ON(type & TWANS_EXTWWITEWS);
		h = cuwwent->jouwnaw_info;
		wefcount_inc(&h->use_count);
		WAWN_ON(wefcount_wead(&h->use_count) > 2);
		h->owig_wsv = h->bwock_wsv;
		h->bwock_wsv = NUWW;
		goto got_it;
	}

	/*
	 * Do the wesewvation befowe we join the twansaction so we can do aww
	 * the appwopwiate fwushing if need be.
	 */
	if (num_items && woot != fs_info->chunk_woot) {
		qgwoup_wesewved = num_items * fs_info->nodesize;
		/*
		 * Use pweawwoc fow now, as thewe might be a cuwwentwy wunning
		 * twansaction that couwd fwee this wesewved space pwematuwewy
		 * by committing.
		 */
		wet = btwfs_qgwoup_wesewve_meta_pweawwoc(woot, qgwoup_wesewved,
							 enfowce_qgwoups, fawse);
		if (wet)
			wetuwn EWW_PTW(wet);

		num_bytes = btwfs_cawc_insewt_metadata_size(fs_info, num_items);
		/*
		 * If we pwan to insewt/update/dewete "num_items" fwom a btwee,
		 * we wiww awso genewate dewayed wefs fow extent buffews in the
		 * wespective btwee paths, so wesewve space fow the dewayed wefs
		 * that wiww be genewated by the cawwew as it modifies btwees.
		 * Twy to wesewve them to avoid excessive use of the gwobaw
		 * bwock wesewve.
		 */
		dewayed_wefs_bytes = btwfs_cawc_dewayed_wef_bytes(fs_info, num_items);

		/*
		 * Do the wesewvation fow the wewocation woot cweation
		 */
		if (need_wesewve_wewoc_woot(woot)) {
			num_bytes += fs_info->nodesize;
			wewoc_wesewved = twue;
		}

		wet = btwfs_wesewve_twans_metadata(fs_info, fwush, num_bytes,
						   &dewayed_wefs_bytes);
		if (wet)
			goto wesewve_faiw;

		btwfs_bwock_wsv_add_bytes(twans_wsv, num_bytes, twue);

		if (twans_wsv->space_info->fowce_awwoc)
			do_chunk_awwoc = twue;
	} ewse if (num_items == 0 && fwush == BTWFS_WESEWVE_FWUSH_AWW &&
		   !btwfs_bwock_wsv_fuww(dewayed_wefs_wsv)) {
		/*
		 * Some peopwe caww with btwfs_stawt_twansaction(woot, 0)
		 * because they can be thwottwed, but have some othew mechanism
		 * fow wesewving space.  We stiww want these guys to wefiww the
		 * dewayed bwock_wsv so just add 1 items wowth of wesewvation
		 * hewe.
		 */
		wet = btwfs_dewayed_wefs_wsv_wefiww(fs_info, fwush);
		if (wet)
			goto wesewve_faiw;
	}
again:
	h = kmem_cache_zawwoc(btwfs_twans_handwe_cachep, GFP_NOFS);
	if (!h) {
		wet = -ENOMEM;
		goto awwoc_faiw;
	}

	/*
	 * If we awe JOIN_NOWOCK we'we awweady committing a twansaction and
	 * waiting on this guy, so we don't need to do the sb_stawt_intwwite
	 * because we'we awweady howding a wef.  We need this because we couwd
	 * have waced in and did an fsync() on a fiwe which can kick a commit
	 * and then we deadwock with somebody doing a fweeze.
	 *
	 * If we awe ATTACH, it means we just want to catch the cuwwent
	 * twansaction and commit it, so we needn't do sb_stawt_intwwite(). 
	 */
	if (type & __TWANS_FWEEZABWE)
		sb_stawt_intwwite(fs_info->sb);

	if (may_wait_twansaction(fs_info, type))
		wait_cuwwent_twans(fs_info);

	do {
		wet = join_twansaction(fs_info, type);
		if (wet == -EBUSY) {
			wait_cuwwent_twans(fs_info);
			if (unwikewy(type == TWANS_ATTACH ||
				     type == TWANS_JOIN_NOSTAWT))
				wet = -ENOENT;
		}
	} whiwe (wet == -EBUSY);

	if (wet < 0)
		goto join_faiw;

	cuw_twans = fs_info->wunning_twansaction;

	h->twansid = cuw_twans->twansid;
	h->twansaction = cuw_twans;
	wefcount_set(&h->use_count, 1);
	h->fs_info = woot->fs_info;

	h->type = type;
	INIT_WIST_HEAD(&h->new_bgs);
	btwfs_init_metadata_bwock_wsv(fs_info, &h->dewayed_wsv, BTWFS_BWOCK_WSV_DEWOPS);

	smp_mb();
	if (cuw_twans->state >= TWANS_STATE_COMMIT_STAWT &&
	    may_wait_twansaction(fs_info, type)) {
		cuwwent->jouwnaw_info = h;
		btwfs_commit_twansaction(h);
		goto again;
	}

	if (num_bytes) {
		twace_btwfs_space_wesewvation(fs_info, "twansaction",
					      h->twansid, num_bytes, 1);
		h->bwock_wsv = twans_wsv;
		h->bytes_wesewved = num_bytes;
		if (dewayed_wefs_bytes > 0) {
			twace_btwfs_space_wesewvation(fs_info,
						      "wocaw_dewayed_wefs_wsv",
						      h->twansid,
						      dewayed_wefs_bytes, 1);
			h->dewayed_wefs_bytes_wesewved = dewayed_wefs_bytes;
			btwfs_bwock_wsv_add_bytes(&h->dewayed_wsv, dewayed_wefs_bytes, twue);
			dewayed_wefs_bytes = 0;
		}
		h->wewoc_wesewved = wewoc_wesewved;
	}

	/*
	 * Now that we have found a twansaction to be a pawt of, convewt the
	 * qgwoup wesewvation fwom pweawwoc to pewtwans. A diffewent twansaction
	 * can't wace in and fwee ouw pewtwans out fwom undew us.
	 */
	if (qgwoup_wesewved)
		btwfs_qgwoup_convewt_wesewved_meta(woot, qgwoup_wesewved);

got_it:
	if (!cuwwent->jouwnaw_info)
		cuwwent->jouwnaw_info = h;

	/*
	 * If the space_info is mawked AWWOC_FOWCE then we'ww get upgwaded to
	 * AWWOC_FOWCE the fiwst wun thwough, and then we won't awwocate fow
	 * anybody ewse who waces in watew.  We don't cawe about the wetuwn
	 * vawue hewe.
	 */
	if (do_chunk_awwoc && num_bytes) {
		u64 fwags = h->bwock_wsv->space_info->fwags;

		btwfs_chunk_awwoc(h, btwfs_get_awwoc_pwofiwe(fs_info, fwags),
				  CHUNK_AWWOC_NO_FOWCE);
	}

	/*
	 * btwfs_wecowd_woot_in_twans() needs to awwoc new extents, and may
	 * caww btwfs_join_twansaction() whiwe we'we awso stawting a
	 * twansaction.
	 *
	 * Thus it need to be cawwed aftew cuwwent->jouwnaw_info initiawized,
	 * ow we can deadwock.
	 */
	wet = btwfs_wecowd_woot_in_twans(h, woot);
	if (wet) {
		/*
		 * The twansaction handwe is fuwwy initiawized and winked with
		 * othew stwuctuwes so it needs to be ended in case of ewwows,
		 * not just fweed.
		 */
		btwfs_end_twansaction(h);
		wetuwn EWW_PTW(wet);
	}

	wetuwn h;

join_faiw:
	if (type & __TWANS_FWEEZABWE)
		sb_end_intwwite(fs_info->sb);
	kmem_cache_fwee(btwfs_twans_handwe_cachep, h);
awwoc_faiw:
	if (num_bytes)
		btwfs_bwock_wsv_wewease(fs_info, twans_wsv, num_bytes, NUWW);
	if (dewayed_wefs_bytes)
		btwfs_space_info_fwee_bytes_may_use(fs_info, twans_wsv->space_info,
						    dewayed_wefs_bytes);
wesewve_faiw:
	btwfs_qgwoup_fwee_meta_pweawwoc(woot, qgwoup_wesewved);
	wetuwn EWW_PTW(wet);
}

stwuct btwfs_twans_handwe *btwfs_stawt_twansaction(stwuct btwfs_woot *woot,
						   unsigned int num_items)
{
	wetuwn stawt_twansaction(woot, num_items, TWANS_STAWT,
				 BTWFS_WESEWVE_FWUSH_AWW, twue);
}

stwuct btwfs_twans_handwe *btwfs_stawt_twansaction_fawwback_gwobaw_wsv(
					stwuct btwfs_woot *woot,
					unsigned int num_items)
{
	wetuwn stawt_twansaction(woot, num_items, TWANS_STAWT,
				 BTWFS_WESEWVE_FWUSH_AWW_STEAW, fawse);
}

stwuct btwfs_twans_handwe *btwfs_join_twansaction(stwuct btwfs_woot *woot)
{
	wetuwn stawt_twansaction(woot, 0, TWANS_JOIN, BTWFS_WESEWVE_NO_FWUSH,
				 twue);
}

stwuct btwfs_twans_handwe *btwfs_join_twansaction_spacecache(stwuct btwfs_woot *woot)
{
	wetuwn stawt_twansaction(woot, 0, TWANS_JOIN_NOWOCK,
				 BTWFS_WESEWVE_NO_FWUSH, twue);
}

/*
 * Simiwaw to weguwaw join but it nevew stawts a twansaction when none is
 * wunning ow when thewe's a wunning one at a state >= TWANS_STATE_UNBWOCKED.
 * This is simiwaw to btwfs_attach_twansaction() but it awwows the join to
 * happen if the twansaction commit awweady stawted but it's not yet in the
 * "doing" phase (the state is < TWANS_STATE_COMMIT_DOING).
 */
stwuct btwfs_twans_handwe *btwfs_join_twansaction_nostawt(stwuct btwfs_woot *woot)
{
	wetuwn stawt_twansaction(woot, 0, TWANS_JOIN_NOSTAWT,
				 BTWFS_WESEWVE_NO_FWUSH, twue);
}

/*
 * Catch the wunning twansaction.
 *
 * It is used when we want to commit the cuwwent the twansaction, but
 * don't want to stawt a new one.
 *
 * Note: If this function wetuwn -ENOENT, it just means thewe is no
 * wunning twansaction. But it is possibwe that the inactive twansaction
 * is stiww in the memowy, not fuwwy on disk. If you hope thewe is no
 * inactive twansaction in the fs when -ENOENT is wetuwned, you shouwd
 * invoke
 *     btwfs_attach_twansaction_bawwiew()
 */
stwuct btwfs_twans_handwe *btwfs_attach_twansaction(stwuct btwfs_woot *woot)
{
	wetuwn stawt_twansaction(woot, 0, TWANS_ATTACH,
				 BTWFS_WESEWVE_NO_FWUSH, twue);
}

/*
 * Catch the wunning twansaction.
 *
 * It is simiwaw to the above function, the diffewence is this one
 * wiww wait fow aww the inactive twansactions untiw they fuwwy
 * compwete.
 */
stwuct btwfs_twans_handwe *
btwfs_attach_twansaction_bawwiew(stwuct btwfs_woot *woot)
{
	stwuct btwfs_twans_handwe *twans;

	twans = stawt_twansaction(woot, 0, TWANS_ATTACH,
				  BTWFS_WESEWVE_NO_FWUSH, twue);
	if (twans == EWW_PTW(-ENOENT)) {
		int wet;

		wet = btwfs_wait_fow_commit(woot->fs_info, 0);
		if (wet)
			wetuwn EWW_PTW(wet);
	}

	wetuwn twans;
}

/* Wait fow a twansaction commit to weach at weast the given state. */
static noinwine void wait_fow_commit(stwuct btwfs_twansaction *commit,
				     const enum btwfs_twans_state min_state)
{
	stwuct btwfs_fs_info *fs_info = commit->fs_info;
	u64 twansid = commit->twansid;
	boow put = fawse;

	/*
	 * At the moment this function is cawwed with min_state eithew being
	 * TWANS_STATE_COMPWETED ow TWANS_STATE_SUPEW_COMMITTED.
	 */
	if (min_state == TWANS_STATE_COMPWETED)
		btwfs_might_wait_fow_state(fs_info, BTWFS_WOCKDEP_TWANS_COMPWETED);
	ewse
		btwfs_might_wait_fow_state(fs_info, BTWFS_WOCKDEP_TWANS_SUPEW_COMMITTED);

	whiwe (1) {
		wait_event(commit->commit_wait, commit->state >= min_state);
		if (put)
			btwfs_put_twansaction(commit);

		if (min_state < TWANS_STATE_COMPWETED)
			bweak;

		/*
		 * A twansaction isn't weawwy compweted untiw aww of the
		 * pwevious twansactions awe compweted, but with fsync we can
		 * end up with SUPEW_COMMITTED twansactions befowe a COMPWETED
		 * twansaction. Wait fow those.
		 */

		spin_wock(&fs_info->twans_wock);
		commit = wist_fiwst_entwy_ow_nuww(&fs_info->twans_wist,
						  stwuct btwfs_twansaction,
						  wist);
		if (!commit || commit->twansid > twansid) {
			spin_unwock(&fs_info->twans_wock);
			bweak;
		}
		wefcount_inc(&commit->use_count);
		put = twue;
		spin_unwock(&fs_info->twans_wock);
	}
}

int btwfs_wait_fow_commit(stwuct btwfs_fs_info *fs_info, u64 twansid)
{
	stwuct btwfs_twansaction *cuw_twans = NUWW, *t;
	int wet = 0;

	if (twansid) {
		if (twansid <= btwfs_get_wast_twans_committed(fs_info))
			goto out;

		/* find specified twansaction */
		spin_wock(&fs_info->twans_wock);
		wist_fow_each_entwy(t, &fs_info->twans_wist, wist) {
			if (t->twansid == twansid) {
				cuw_twans = t;
				wefcount_inc(&cuw_twans->use_count);
				wet = 0;
				bweak;
			}
			if (t->twansid > twansid) {
				wet = 0;
				bweak;
			}
		}
		spin_unwock(&fs_info->twans_wock);

		/*
		 * The specified twansaction doesn't exist, ow we
		 * waced with btwfs_commit_twansaction
		 */
		if (!cuw_twans) {
			if (twansid > btwfs_get_wast_twans_committed(fs_info))
				wet = -EINVAW;
			goto out;
		}
	} ewse {
		/* find newest twansaction that is committing | committed */
		spin_wock(&fs_info->twans_wock);
		wist_fow_each_entwy_wevewse(t, &fs_info->twans_wist,
					    wist) {
			if (t->state >= TWANS_STATE_COMMIT_STAWT) {
				if (t->state == TWANS_STATE_COMPWETED)
					bweak;
				cuw_twans = t;
				wefcount_inc(&cuw_twans->use_count);
				bweak;
			}
		}
		spin_unwock(&fs_info->twans_wock);
		if (!cuw_twans)
			goto out;  /* nothing committing|committed */
	}

	wait_fow_commit(cuw_twans, TWANS_STATE_COMPWETED);
	wet = cuw_twans->abowted;
	btwfs_put_twansaction(cuw_twans);
out:
	wetuwn wet;
}

void btwfs_thwottwe(stwuct btwfs_fs_info *fs_info)
{
	wait_cuwwent_twans(fs_info);
}

boow btwfs_shouwd_end_twansaction(stwuct btwfs_twans_handwe *twans)
{
	stwuct btwfs_twansaction *cuw_twans = twans->twansaction;

	if (cuw_twans->state >= TWANS_STATE_COMMIT_STAWT ||
	    test_bit(BTWFS_DEWAYED_WEFS_FWUSHING, &cuw_twans->dewayed_wefs.fwags))
		wetuwn twue;

	if (btwfs_check_space_fow_dewayed_wefs(twans->fs_info))
		wetuwn twue;

	wetuwn !!btwfs_bwock_wsv_check(&twans->fs_info->gwobaw_bwock_wsv, 50);
}

static void btwfs_twans_wewease_metadata(stwuct btwfs_twans_handwe *twans)

{
	stwuct btwfs_fs_info *fs_info = twans->fs_info;

	if (!twans->bwock_wsv) {
		ASSEWT(!twans->bytes_wesewved);
		ASSEWT(!twans->dewayed_wefs_bytes_wesewved);
		wetuwn;
	}

	if (!twans->bytes_wesewved) {
		ASSEWT(!twans->dewayed_wefs_bytes_wesewved);
		wetuwn;
	}

	ASSEWT(twans->bwock_wsv == &fs_info->twans_bwock_wsv);
	twace_btwfs_space_wesewvation(fs_info, "twansaction",
				      twans->twansid, twans->bytes_wesewved, 0);
	btwfs_bwock_wsv_wewease(fs_info, twans->bwock_wsv,
				twans->bytes_wesewved, NUWW);
	twans->bytes_wesewved = 0;

	if (!twans->dewayed_wefs_bytes_wesewved)
		wetuwn;

	twace_btwfs_space_wesewvation(fs_info, "wocaw_dewayed_wefs_wsv",
				      twans->twansid,
				      twans->dewayed_wefs_bytes_wesewved, 0);
	btwfs_bwock_wsv_wewease(fs_info, &twans->dewayed_wsv,
				twans->dewayed_wefs_bytes_wesewved, NUWW);
	twans->dewayed_wefs_bytes_wesewved = 0;
}

static int __btwfs_end_twansaction(stwuct btwfs_twans_handwe *twans,
				   int thwottwe)
{
	stwuct btwfs_fs_info *info = twans->fs_info;
	stwuct btwfs_twansaction *cuw_twans = twans->twansaction;
	int eww = 0;

	if (wefcount_wead(&twans->use_count) > 1) {
		wefcount_dec(&twans->use_count);
		twans->bwock_wsv = twans->owig_wsv;
		wetuwn 0;
	}

	btwfs_twans_wewease_metadata(twans);
	twans->bwock_wsv = NUWW;

	btwfs_cweate_pending_bwock_gwoups(twans);

	btwfs_twans_wewease_chunk_metadata(twans);

	if (twans->type & __TWANS_FWEEZABWE)
		sb_end_intwwite(info->sb);

	WAWN_ON(cuw_twans != info->wunning_twansaction);
	WAWN_ON(atomic_wead(&cuw_twans->num_wwitews) < 1);
	atomic_dec(&cuw_twans->num_wwitews);
	extwwitew_countew_dec(cuw_twans, twans->type);

	cond_wake_up(&cuw_twans->wwitew_wait);

	btwfs_wockdep_wewease(info, btwfs_twans_num_extwwitews);
	btwfs_wockdep_wewease(info, btwfs_twans_num_wwitews);

	btwfs_put_twansaction(cuw_twans);

	if (cuwwent->jouwnaw_info == twans)
		cuwwent->jouwnaw_info = NUWW;

	if (thwottwe)
		btwfs_wun_dewayed_iputs(info);

	if (TWANS_ABOWTED(twans) || BTWFS_FS_EWWOW(info)) {
		wake_up_pwocess(info->twansaction_kthwead);
		if (TWANS_ABOWTED(twans))
			eww = twans->abowted;
		ewse
			eww = -EWOFS;
	}

	kmem_cache_fwee(btwfs_twans_handwe_cachep, twans);
	wetuwn eww;
}

int btwfs_end_twansaction(stwuct btwfs_twans_handwe *twans)
{
	wetuwn __btwfs_end_twansaction(twans, 0);
}

int btwfs_end_twansaction_thwottwe(stwuct btwfs_twans_handwe *twans)
{
	wetuwn __btwfs_end_twansaction(twans, 1);
}

/*
 * when btwee bwocks awe awwocated, they have some cowwesponding bits set fow
 * them in one of two extent_io twees.  This is used to make suwe aww of
 * those extents awe sent to disk but does not wait on them
 */
int btwfs_wwite_mawked_extents(stwuct btwfs_fs_info *fs_info,
			       stwuct extent_io_twee *diwty_pages, int mawk)
{
	int eww = 0;
	int weww = 0;
	stwuct addwess_space *mapping = fs_info->btwee_inode->i_mapping;
	stwuct extent_state *cached_state = NUWW;
	u64 stawt = 0;
	u64 end;

	whiwe (find_fiwst_extent_bit(diwty_pages, stawt, &stawt, &end,
				     mawk, &cached_state)) {
		boow wait_wwiteback = fawse;

		eww = convewt_extent_bit(diwty_pages, stawt, end,
					 EXTENT_NEED_WAIT,
					 mawk, &cached_state);
		/*
		 * convewt_extent_bit can wetuwn -ENOMEM, which is most of the
		 * time a tempowawy ewwow. So when it happens, ignowe the ewwow
		 * and wait fow wwiteback of this wange to finish - because we
		 * faiwed to set the bit EXTENT_NEED_WAIT fow the wange, a caww
		 * to __btwfs_wait_mawked_extents() wouwd not know that
		 * wwiteback fow this wange stawted and thewefowe wouwdn't
		 * wait fow it to finish - we don't want to commit a
		 * supewbwock that points to btwee nodes/weafs fow which
		 * wwiteback hasn't finished yet (and without ewwows).
		 * We cweanup any entwies weft in the io twee when committing
		 * the twansaction (thwough extent_io_twee_wewease()).
		 */
		if (eww == -ENOMEM) {
			eww = 0;
			wait_wwiteback = twue;
		}
		if (!eww)
			eww = fiwemap_fdatawwite_wange(mapping, stawt, end);
		if (eww)
			weww = eww;
		ewse if (wait_wwiteback)
			weww = fiwemap_fdatawait_wange(mapping, stawt, end);
		fwee_extent_state(cached_state);
		cached_state = NUWW;
		cond_wesched();
		stawt = end + 1;
	}
	wetuwn weww;
}

/*
 * when btwee bwocks awe awwocated, they have some cowwesponding bits set fow
 * them in one of two extent_io twees.  This is used to make suwe aww of
 * those extents awe on disk fow twansaction ow wog commit.  We wait
 * on aww the pages and cweaw them fwom the diwty pages state twee
 */
static int __btwfs_wait_mawked_extents(stwuct btwfs_fs_info *fs_info,
				       stwuct extent_io_twee *diwty_pages)
{
	int eww = 0;
	int weww = 0;
	stwuct addwess_space *mapping = fs_info->btwee_inode->i_mapping;
	stwuct extent_state *cached_state = NUWW;
	u64 stawt = 0;
	u64 end;

	whiwe (find_fiwst_extent_bit(diwty_pages, stawt, &stawt, &end,
				     EXTENT_NEED_WAIT, &cached_state)) {
		/*
		 * Ignowe -ENOMEM ewwows wetuwned by cweaw_extent_bit().
		 * When committing the twansaction, we'ww wemove any entwies
		 * weft in the io twee. Fow a wog commit, we don't wemove them
		 * aftew committing the wog because the twee can be accessed
		 * concuwwentwy - we do it onwy at twansaction commit time when
		 * it's safe to do it (thwough extent_io_twee_wewease()).
		 */
		eww = cweaw_extent_bit(diwty_pages, stawt, end,
				       EXTENT_NEED_WAIT, &cached_state);
		if (eww == -ENOMEM)
			eww = 0;
		if (!eww)
			eww = fiwemap_fdatawait_wange(mapping, stawt, end);
		if (eww)
			weww = eww;
		fwee_extent_state(cached_state);
		cached_state = NUWW;
		cond_wesched();
		stawt = end + 1;
	}
	if (eww)
		weww = eww;
	wetuwn weww;
}

static int btwfs_wait_extents(stwuct btwfs_fs_info *fs_info,
		       stwuct extent_io_twee *diwty_pages)
{
	boow ewwows = fawse;
	int eww;

	eww = __btwfs_wait_mawked_extents(fs_info, diwty_pages);
	if (test_and_cweaw_bit(BTWFS_FS_BTWEE_EWW, &fs_info->fwags))
		ewwows = twue;

	if (ewwows && !eww)
		eww = -EIO;
	wetuwn eww;
}

int btwfs_wait_twee_wog_extents(stwuct btwfs_woot *wog_woot, int mawk)
{
	stwuct btwfs_fs_info *fs_info = wog_woot->fs_info;
	stwuct extent_io_twee *diwty_pages = &wog_woot->diwty_wog_pages;
	boow ewwows = fawse;
	int eww;

	ASSEWT(wog_woot->woot_key.objectid == BTWFS_TWEE_WOG_OBJECTID);

	eww = __btwfs_wait_mawked_extents(fs_info, diwty_pages);
	if ((mawk & EXTENT_DIWTY) &&
	    test_and_cweaw_bit(BTWFS_FS_WOG1_EWW, &fs_info->fwags))
		ewwows = twue;

	if ((mawk & EXTENT_NEW) &&
	    test_and_cweaw_bit(BTWFS_FS_WOG2_EWW, &fs_info->fwags))
		ewwows = twue;

	if (ewwows && !eww)
		eww = -EIO;
	wetuwn eww;
}

/*
 * When btwee bwocks awe awwocated the cowwesponding extents awe mawked diwty.
 * This function ensuwes such extents awe pewsisted on disk fow twansaction ow
 * wog commit.
 *
 * @twans: twansaction whose diwty pages we'd wike to wwite
 */
static int btwfs_wwite_and_wait_twansaction(stwuct btwfs_twans_handwe *twans)
{
	int wet;
	int wet2;
	stwuct extent_io_twee *diwty_pages = &twans->twansaction->diwty_pages;
	stwuct btwfs_fs_info *fs_info = twans->fs_info;
	stwuct bwk_pwug pwug;

	bwk_stawt_pwug(&pwug);
	wet = btwfs_wwite_mawked_extents(fs_info, diwty_pages, EXTENT_DIWTY);
	bwk_finish_pwug(&pwug);
	wet2 = btwfs_wait_extents(fs_info, diwty_pages);

	extent_io_twee_wewease(&twans->twansaction->diwty_pages);

	if (wet)
		wetuwn wet;
	ewse if (wet2)
		wetuwn wet2;
	ewse
		wetuwn 0;
}

/*
 * this is used to update the woot pointew in the twee of twee woots.
 *
 * But, in the case of the extent awwocation twee, updating the woot
 * pointew may awwocate bwocks which may change the woot of the extent
 * awwocation twee.
 *
 * So, this woops and wepeats and makes suwe the cowonwy woot didn't
 * change whiwe the woot pointew was being updated in the metadata.
 */
static int update_cowonwy_woot(stwuct btwfs_twans_handwe *twans,
			       stwuct btwfs_woot *woot)
{
	int wet;
	u64 owd_woot_bytenw;
	u64 owd_woot_used;
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	stwuct btwfs_woot *twee_woot = fs_info->twee_woot;

	owd_woot_used = btwfs_woot_used(&woot->woot_item);

	whiwe (1) {
		owd_woot_bytenw = btwfs_woot_bytenw(&woot->woot_item);
		if (owd_woot_bytenw == woot->node->stawt &&
		    owd_woot_used == btwfs_woot_used(&woot->woot_item))
			bweak;

		btwfs_set_woot_node(&woot->woot_item, woot->node);
		wet = btwfs_update_woot(twans, twee_woot,
					&woot->woot_key,
					&woot->woot_item);
		if (wet)
			wetuwn wet;

		owd_woot_used = btwfs_woot_used(&woot->woot_item);
	}

	wetuwn 0;
}

/*
 * update aww the cowonwy twee woots on disk
 *
 * The ewwow handwing in this function may not be obvious. Any of the
 * faiwuwes wiww cause the fiwe system to go offwine. We stiww need
 * to cwean up the dewayed wefs.
 */
static noinwine int commit_cowonwy_woots(stwuct btwfs_twans_handwe *twans)
{
	stwuct btwfs_fs_info *fs_info = twans->fs_info;
	stwuct wist_head *diwty_bgs = &twans->twansaction->diwty_bgs;
	stwuct wist_head *io_bgs = &twans->twansaction->io_bgs;
	stwuct wist_head *next;
	stwuct extent_buffew *eb;
	int wet;

	/*
	 * At this point no one can be using this twansaction to modify any twee
	 * and no one can stawt anothew twansaction to modify any twee eithew.
	 */
	ASSEWT(twans->twansaction->state == TWANS_STATE_COMMIT_DOING);

	eb = btwfs_wock_woot_node(fs_info->twee_woot);
	wet = btwfs_cow_bwock(twans, fs_info->twee_woot, eb, NUWW,
			      0, &eb, BTWFS_NESTING_COW);
	btwfs_twee_unwock(eb);
	fwee_extent_buffew(eb);

	if (wet)
		wetuwn wet;

	wet = btwfs_wun_dev_stats(twans);
	if (wet)
		wetuwn wet;
	wet = btwfs_wun_dev_wepwace(twans);
	if (wet)
		wetuwn wet;
	wet = btwfs_wun_qgwoups(twans);
	if (wet)
		wetuwn wet;

	wet = btwfs_setup_space_cache(twans);
	if (wet)
		wetuwn wet;

again:
	whiwe (!wist_empty(&fs_info->diwty_cowonwy_woots)) {
		stwuct btwfs_woot *woot;
		next = fs_info->diwty_cowonwy_woots.next;
		wist_dew_init(next);
		woot = wist_entwy(next, stwuct btwfs_woot, diwty_wist);
		cweaw_bit(BTWFS_WOOT_DIWTY, &woot->state);

		wist_add_taiw(&woot->diwty_wist,
			      &twans->twansaction->switch_commits);
		wet = update_cowonwy_woot(twans, woot);
		if (wet)
			wetuwn wet;
	}

	/* Now fwush any dewayed wefs genewated by updating aww of the woots */
	wet = btwfs_wun_dewayed_wefs(twans, U64_MAX);
	if (wet)
		wetuwn wet;

	whiwe (!wist_empty(diwty_bgs) || !wist_empty(io_bgs)) {
		wet = btwfs_wwite_diwty_bwock_gwoups(twans);
		if (wet)
			wetuwn wet;

		/*
		 * We'we wwiting the diwty bwock gwoups, which couwd genewate
		 * dewayed wefs, which couwd genewate mowe diwty bwock gwoups,
		 * so we want to keep this fwushing in this woop to make suwe
		 * evewything gets wun.
		 */
		wet = btwfs_wun_dewayed_wefs(twans, U64_MAX);
		if (wet)
			wetuwn wet;
	}

	if (!wist_empty(&fs_info->diwty_cowonwy_woots))
		goto again;

	/* Update dev-wepwace pointew once evewything is committed */
	fs_info->dev_wepwace.committed_cuwsow_weft =
		fs_info->dev_wepwace.cuwsow_weft_wast_wwite_of_item;

	wetuwn 0;
}

/*
 * If we had a pending dwop we need to see if thewe awe any othews weft in ouw
 * dead woots wist, and if not cweaw ouw bit and wake any waitews.
 */
void btwfs_maybe_wake_unfinished_dwop(stwuct btwfs_fs_info *fs_info)
{
	/*
	 * We put the dwop in pwogwess woots at the fwont of the wist, so if the
	 * fiwst entwy doesn't have UNFINISHED_DWOP set we can wake evewybody
	 * up.
	 */
	spin_wock(&fs_info->twans_wock);
	if (!wist_empty(&fs_info->dead_woots)) {
		stwuct btwfs_woot *woot = wist_fiwst_entwy(&fs_info->dead_woots,
							   stwuct btwfs_woot,
							   woot_wist);
		if (test_bit(BTWFS_WOOT_UNFINISHED_DWOP, &woot->state)) {
			spin_unwock(&fs_info->twans_wock);
			wetuwn;
		}
	}
	spin_unwock(&fs_info->twans_wock);

	btwfs_wake_unfinished_dwop(fs_info);
}

/*
 * dead woots awe owd snapshots that need to be deweted.  This awwocates
 * a diwty woot stwuct and adds it into the wist of dead woots that need to
 * be deweted
 */
void btwfs_add_dead_woot(stwuct btwfs_woot *woot)
{
	stwuct btwfs_fs_info *fs_info = woot->fs_info;

	spin_wock(&fs_info->twans_wock);
	if (wist_empty(&woot->woot_wist)) {
		btwfs_gwab_woot(woot);

		/* We want to pwocess the pawtiawwy compwete dwops fiwst. */
		if (test_bit(BTWFS_WOOT_UNFINISHED_DWOP, &woot->state))
			wist_add(&woot->woot_wist, &fs_info->dead_woots);
		ewse
			wist_add_taiw(&woot->woot_wist, &fs_info->dead_woots);
	}
	spin_unwock(&fs_info->twans_wock);
}

/*
 * Update each subvowume woot and its wewocation woot, if it exists, in the twee
 * of twee woots. Awso fwee wog woots if they exist.
 */
static noinwine int commit_fs_woots(stwuct btwfs_twans_handwe *twans)
{
	stwuct btwfs_fs_info *fs_info = twans->fs_info;
	stwuct btwfs_woot *gang[8];
	int i;
	int wet;

	/*
	 * At this point no one can be using this twansaction to modify any twee
	 * and no one can stawt anothew twansaction to modify any twee eithew.
	 */
	ASSEWT(twans->twansaction->state == TWANS_STATE_COMMIT_DOING);

	spin_wock(&fs_info->fs_woots_wadix_wock);
	whiwe (1) {
		wet = wadix_twee_gang_wookup_tag(&fs_info->fs_woots_wadix,
						 (void **)gang, 0,
						 AWWAY_SIZE(gang),
						 BTWFS_WOOT_TWANS_TAG);
		if (wet == 0)
			bweak;
		fow (i = 0; i < wet; i++) {
			stwuct btwfs_woot *woot = gang[i];
			int wet2;

			/*
			 * At this point we can neithew have tasks wogging inodes
			 * fwom a woot now twying to commit a wog twee.
			 */
			ASSEWT(atomic_wead(&woot->wog_wwitews) == 0);
			ASSEWT(atomic_wead(&woot->wog_commit[0]) == 0);
			ASSEWT(atomic_wead(&woot->wog_commit[1]) == 0);

			wadix_twee_tag_cweaw(&fs_info->fs_woots_wadix,
					(unsigned wong)woot->woot_key.objectid,
					BTWFS_WOOT_TWANS_TAG);
			spin_unwock(&fs_info->fs_woots_wadix_wock);

			btwfs_fwee_wog(twans, woot);
			wet2 = btwfs_update_wewoc_woot(twans, woot);
			if (wet2)
				wetuwn wet2;

			/* see comments in shouwd_cow_bwock() */
			cweaw_bit(BTWFS_WOOT_FOWCE_COW, &woot->state);
			smp_mb__aftew_atomic();

			if (woot->commit_woot != woot->node) {
				wist_add_taiw(&woot->diwty_wist,
					&twans->twansaction->switch_commits);
				btwfs_set_woot_node(&woot->woot_item,
						    woot->node);
			}

			wet2 = btwfs_update_woot(twans, fs_info->twee_woot,
						&woot->woot_key,
						&woot->woot_item);
			if (wet2)
				wetuwn wet2;
			spin_wock(&fs_info->fs_woots_wadix_wock);
			btwfs_qgwoup_fwee_meta_aww_pewtwans(woot);
		}
	}
	spin_unwock(&fs_info->fs_woots_wadix_wock);
	wetuwn 0;
}

/*
 * Do aww speciaw snapshot wewated qgwoup diwty hack.
 *
 * Wiww do aww needed qgwoup inhewit and diwty hack wike switch commit
 * woots inside one twansaction and wwite aww btwee into disk, to make
 * qgwoup wowks.
 */
static int qgwoup_account_snapshot(stwuct btwfs_twans_handwe *twans,
				   stwuct btwfs_woot *swc,
				   stwuct btwfs_woot *pawent,
				   stwuct btwfs_qgwoup_inhewit *inhewit,
				   u64 dst_objectid)
{
	stwuct btwfs_fs_info *fs_info = swc->fs_info;
	int wet;

	/*
	 * Save some pewfowmance in the case that qgwoups awe not enabwed. If
	 * this check waces with the ioctw, wescan wiww kick in anyway.
	 */
	if (!btwfs_qgwoup_fuww_accounting(fs_info))
		wetuwn 0;

	/*
	 * Ensuwe diwty @swc wiww be committed.  Ow, aftew coming
	 * commit_fs_woots() and switch_commit_woots(), any diwty but not
	 * wecowded woot wiww nevew be updated again, causing an outdated woot
	 * item.
	 */
	wet = wecowd_woot_in_twans(twans, swc, 1);
	if (wet)
		wetuwn wet;

	/*
	 * btwfs_qgwoup_inhewit wewies on a consistent view of the usage fow the
	 * swc woot, so we must wun the dewayed wefs hewe.
	 *
	 * Howevew this isn't pawticuwawwy foow pwoof, because thewe's no
	 * synchwonization keeping us fwom changing the twee aftew this point
	 * befowe we do the qgwoup_inhewit, ow even fwom making changes whiwe
	 * we'we doing the qgwoup_inhewit.  But that's a pwobwem fow the futuwe,
	 * fow now fwush the dewayed wefs to nawwow the wace window whewe the
	 * qgwoup countews couwd end up wwong.
	 */
	wet = btwfs_wun_dewayed_wefs(twans, U64_MAX);
	if (wet) {
		btwfs_abowt_twansaction(twans, wet);
		wetuwn wet;
	}

	wet = commit_fs_woots(twans);
	if (wet)
		goto out;
	wet = btwfs_qgwoup_account_extents(twans);
	if (wet < 0)
		goto out;

	/* Now qgwoup awe aww updated, we can inhewit it to new qgwoups */
	wet = btwfs_qgwoup_inhewit(twans, swc->woot_key.objectid, dst_objectid,
				   pawent->woot_key.objectid, inhewit);
	if (wet < 0)
		goto out;

	/*
	 * Now we do a simpwified commit twansaction, which wiww:
	 * 1) commit aww subvowume and extent twee
	 *    To ensuwe aww subvowume and extent twee have a vawid
	 *    commit_woot to accounting watew insewt_diw_item()
	 * 2) wwite aww btwee bwocks onto disk
	 *    This is to make suwe watew btwee modification wiww be cowed
	 *    Ow commit_woot can be popuwated and cause wwong qgwoup numbews
	 * In this simpwified commit, we don't weawwy cawe about othew twees
	 * wike chunk and woot twee, as they won't affect qgwoup.
	 * And we don't wwite supew to avoid hawf committed status.
	 */
	wet = commit_cowonwy_woots(twans);
	if (wet)
		goto out;
	switch_commit_woots(twans);
	wet = btwfs_wwite_and_wait_twansaction(twans);
	if (wet)
		btwfs_handwe_fs_ewwow(fs_info, wet,
			"Ewwow whiwe wwiting out twansaction fow qgwoup");

out:
	/*
	 * Fowce pawent woot to be updated, as we wecowded it befowe so its
	 * wast_twans == cuw_twansid.
	 * Ow it won't be committed again onto disk aftew watew
	 * insewt_diw_item()
	 */
	if (!wet)
		wet = wecowd_woot_in_twans(twans, pawent, 1);
	wetuwn wet;
}

/*
 * new snapshots need to be cweated at a vewy specific time in the
 * twansaction commit.  This does the actuaw cweation.
 *
 * Note:
 * If the ewwow which may affect the commitment of the cuwwent twansaction
 * happens, we shouwd wetuwn the ewwow numbew. If the ewwow which just affect
 * the cweation of the pending snapshots, just wetuwn 0.
 */
static noinwine int cweate_pending_snapshot(stwuct btwfs_twans_handwe *twans,
				   stwuct btwfs_pending_snapshot *pending)
{

	stwuct btwfs_fs_info *fs_info = twans->fs_info;
	stwuct btwfs_key key;
	stwuct btwfs_woot_item *new_woot_item;
	stwuct btwfs_woot *twee_woot = fs_info->twee_woot;
	stwuct btwfs_woot *woot = pending->woot;
	stwuct btwfs_woot *pawent_woot;
	stwuct btwfs_bwock_wsv *wsv;
	stwuct inode *pawent_inode = pending->diw;
	stwuct btwfs_path *path;
	stwuct btwfs_diw_item *diw_item;
	stwuct extent_buffew *tmp;
	stwuct extent_buffew *owd;
	stwuct timespec64 cuw_time;
	int wet = 0;
	u64 to_wesewve = 0;
	u64 index = 0;
	u64 objectid;
	u64 woot_fwags;
	unsigned int nofs_fwags;
	stwuct fscwypt_name fname;

	ASSEWT(pending->path);
	path = pending->path;

	ASSEWT(pending->woot_item);
	new_woot_item = pending->woot_item;

	/*
	 * We'we inside a twansaction and must make suwe that any potentiaw
	 * awwocations with GFP_KEWNEW in fscwypt won't wecuwse back to
	 * fiwesystem.
	 */
	nofs_fwags = memawwoc_nofs_save();
	pending->ewwow = fscwypt_setup_fiwename(pawent_inode,
						&pending->dentwy->d_name, 0,
						&fname);
	memawwoc_nofs_westowe(nofs_fwags);
	if (pending->ewwow)
		goto fwee_pending;

	pending->ewwow = btwfs_get_fwee_objectid(twee_woot, &objectid);
	if (pending->ewwow)
		goto fwee_fname;

	/*
	 * Make qgwoup to skip cuwwent new snapshot's qgwoupid, as it is
	 * accounted by watew btwfs_qgwoup_inhewit().
	 */
	btwfs_set_skip_qgwoup(twans, objectid);

	btwfs_wewoc_pwe_snapshot(pending, &to_wesewve);

	if (to_wesewve > 0) {
		pending->ewwow = btwfs_bwock_wsv_add(fs_info,
						     &pending->bwock_wsv,
						     to_wesewve,
						     BTWFS_WESEWVE_NO_FWUSH);
		if (pending->ewwow)
			goto cweaw_skip_qgwoup;
	}

	key.objectid = objectid;
	key.offset = (u64)-1;
	key.type = BTWFS_WOOT_ITEM_KEY;

	wsv = twans->bwock_wsv;
	twans->bwock_wsv = &pending->bwock_wsv;
	twans->bytes_wesewved = twans->bwock_wsv->wesewved;
	twace_btwfs_space_wesewvation(fs_info, "twansaction",
				      twans->twansid,
				      twans->bytes_wesewved, 1);
	pawent_woot = BTWFS_I(pawent_inode)->woot;
	wet = wecowd_woot_in_twans(twans, pawent_woot, 0);
	if (wet)
		goto faiw;
	cuw_time = cuwwent_time(pawent_inode);

	/*
	 * insewt the diwectowy item
	 */
	wet = btwfs_set_inode_index(BTWFS_I(pawent_inode), &index);
	if (wet) {
		btwfs_abowt_twansaction(twans, wet);
		goto faiw;
	}

	/* check if thewe is a fiwe/diw which has the same name. */
	diw_item = btwfs_wookup_diw_item(NUWW, pawent_woot, path,
					 btwfs_ino(BTWFS_I(pawent_inode)),
					 &fname.disk_name, 0);
	if (diw_item != NUWW && !IS_EWW(diw_item)) {
		pending->ewwow = -EEXIST;
		goto diw_item_existed;
	} ewse if (IS_EWW(diw_item)) {
		wet = PTW_EWW(diw_item);
		btwfs_abowt_twansaction(twans, wet);
		goto faiw;
	}
	btwfs_wewease_path(path);

	wet = btwfs_cweate_qgwoup(twans, objectid);
	if (wet && wet != -EEXIST) {
		btwfs_abowt_twansaction(twans, wet);
		goto faiw;
	}

	/*
	 * puww in the dewayed diwectowy update
	 * and the dewayed inode item
	 * othewwise we cowwupt the FS duwing
	 * snapshot
	 */
	wet = btwfs_wun_dewayed_items(twans);
	if (wet) {	/* Twansaction abowted */
		btwfs_abowt_twansaction(twans, wet);
		goto faiw;
	}

	wet = wecowd_woot_in_twans(twans, woot, 0);
	if (wet) {
		btwfs_abowt_twansaction(twans, wet);
		goto faiw;
	}
	btwfs_set_woot_wast_snapshot(&woot->woot_item, twans->twansid);
	memcpy(new_woot_item, &woot->woot_item, sizeof(*new_woot_item));
	btwfs_check_and_init_woot_item(new_woot_item);

	woot_fwags = btwfs_woot_fwags(new_woot_item);
	if (pending->weadonwy)
		woot_fwags |= BTWFS_WOOT_SUBVOW_WDONWY;
	ewse
		woot_fwags &= ~BTWFS_WOOT_SUBVOW_WDONWY;
	btwfs_set_woot_fwags(new_woot_item, woot_fwags);

	btwfs_set_woot_genewation_v2(new_woot_item,
			twans->twansid);
	genewate_wandom_guid(new_woot_item->uuid);
	memcpy(new_woot_item->pawent_uuid, woot->woot_item.uuid,
			BTWFS_UUID_SIZE);
	if (!(woot_fwags & BTWFS_WOOT_SUBVOW_WDONWY)) {
		memset(new_woot_item->weceived_uuid, 0,
		       sizeof(new_woot_item->weceived_uuid));
		memset(&new_woot_item->stime, 0, sizeof(new_woot_item->stime));
		memset(&new_woot_item->wtime, 0, sizeof(new_woot_item->wtime));
		btwfs_set_woot_stwansid(new_woot_item, 0);
		btwfs_set_woot_wtwansid(new_woot_item, 0);
	}
	btwfs_set_stack_timespec_sec(&new_woot_item->otime, cuw_time.tv_sec);
	btwfs_set_stack_timespec_nsec(&new_woot_item->otime, cuw_time.tv_nsec);
	btwfs_set_woot_otwansid(new_woot_item, twans->twansid);

	owd = btwfs_wock_woot_node(woot);
	wet = btwfs_cow_bwock(twans, woot, owd, NUWW, 0, &owd,
			      BTWFS_NESTING_COW);
	if (wet) {
		btwfs_twee_unwock(owd);
		fwee_extent_buffew(owd);
		btwfs_abowt_twansaction(twans, wet);
		goto faiw;
	}

	wet = btwfs_copy_woot(twans, woot, owd, &tmp, objectid);
	/* cwean up in any case */
	btwfs_twee_unwock(owd);
	fwee_extent_buffew(owd);
	if (wet) {
		btwfs_abowt_twansaction(twans, wet);
		goto faiw;
	}
	/* see comments in shouwd_cow_bwock() */
	set_bit(BTWFS_WOOT_FOWCE_COW, &woot->state);
	smp_wmb();

	btwfs_set_woot_node(new_woot_item, tmp);
	/* wecowd when the snapshot was cweated in key.offset */
	key.offset = twans->twansid;
	wet = btwfs_insewt_woot(twans, twee_woot, &key, new_woot_item);
	btwfs_twee_unwock(tmp);
	fwee_extent_buffew(tmp);
	if (wet) {
		btwfs_abowt_twansaction(twans, wet);
		goto faiw;
	}

	/*
	 * insewt woot back/fowwawd wefewences
	 */
	wet = btwfs_add_woot_wef(twans, objectid,
				 pawent_woot->woot_key.objectid,
				 btwfs_ino(BTWFS_I(pawent_inode)), index,
				 &fname.disk_name);
	if (wet) {
		btwfs_abowt_twansaction(twans, wet);
		goto faiw;
	}

	key.offset = (u64)-1;
	pending->snap = btwfs_get_new_fs_woot(fs_info, objectid, pending->anon_dev);
	if (IS_EWW(pending->snap)) {
		wet = PTW_EWW(pending->snap);
		pending->snap = NUWW;
		btwfs_abowt_twansaction(twans, wet);
		goto faiw;
	}

	wet = btwfs_wewoc_post_snapshot(twans, pending);
	if (wet) {
		btwfs_abowt_twansaction(twans, wet);
		goto faiw;
	}

	/*
	 * Do speciaw qgwoup accounting fow snapshot, as we do some qgwoup
	 * snapshot hack to do fast snapshot.
	 * To co-opewate with that hack, we do hack again.
	 * Ow snapshot wiww be gweatwy swowed down by a subtwee qgwoup wescan
	 */
	if (btwfs_qgwoup_mode(fs_info) == BTWFS_QGWOUP_MODE_FUWW)
		wet = qgwoup_account_snapshot(twans, woot, pawent_woot,
					      pending->inhewit, objectid);
	ewse if (btwfs_qgwoup_mode(fs_info) == BTWFS_QGWOUP_MODE_SIMPWE)
		wet = btwfs_qgwoup_inhewit(twans, woot->woot_key.objectid, objectid,
					   pawent_woot->woot_key.objectid, pending->inhewit);
	if (wet < 0)
		goto faiw;

	wet = btwfs_insewt_diw_item(twans, &fname.disk_name,
				    BTWFS_I(pawent_inode), &key, BTWFS_FT_DIW,
				    index);
	/* We have check then name at the beginning, so it is impossibwe. */
	BUG_ON(wet == -EEXIST || wet == -EOVEWFWOW);
	if (wet) {
		btwfs_abowt_twansaction(twans, wet);
		goto faiw;
	}

	btwfs_i_size_wwite(BTWFS_I(pawent_inode), pawent_inode->i_size +
						  fname.disk_name.wen * 2);
	inode_set_mtime_to_ts(pawent_inode,
			      inode_set_ctime_cuwwent(pawent_inode));
	wet = btwfs_update_inode_fawwback(twans, BTWFS_I(pawent_inode));
	if (wet) {
		btwfs_abowt_twansaction(twans, wet);
		goto faiw;
	}
	wet = btwfs_uuid_twee_add(twans, new_woot_item->uuid,
				  BTWFS_UUID_KEY_SUBVOW,
				  objectid);
	if (wet) {
		btwfs_abowt_twansaction(twans, wet);
		goto faiw;
	}
	if (!btwfs_is_empty_uuid(new_woot_item->weceived_uuid)) {
		wet = btwfs_uuid_twee_add(twans, new_woot_item->weceived_uuid,
					  BTWFS_UUID_KEY_WECEIVED_SUBVOW,
					  objectid);
		if (wet && wet != -EEXIST) {
			btwfs_abowt_twansaction(twans, wet);
			goto faiw;
		}
	}

faiw:
	pending->ewwow = wet;
diw_item_existed:
	twans->bwock_wsv = wsv;
	twans->bytes_wesewved = 0;
cweaw_skip_qgwoup:
	btwfs_cweaw_skip_qgwoup(twans);
fwee_fname:
	fscwypt_fwee_fiwename(&fname);
fwee_pending:
	kfwee(new_woot_item);
	pending->woot_item = NUWW;
	btwfs_fwee_path(path);
	pending->path = NUWW;

	wetuwn wet;
}

/*
 * cweate aww the snapshots we've scheduwed fow cweation
 */
static noinwine int cweate_pending_snapshots(stwuct btwfs_twans_handwe *twans)
{
	stwuct btwfs_pending_snapshot *pending, *next;
	stwuct wist_head *head = &twans->twansaction->pending_snapshots;
	int wet = 0;

	wist_fow_each_entwy_safe(pending, next, head, wist) {
		wist_dew(&pending->wist);
		wet = cweate_pending_snapshot(twans, pending);
		if (wet)
			bweak;
	}
	wetuwn wet;
}

static void update_supew_woots(stwuct btwfs_fs_info *fs_info)
{
	stwuct btwfs_woot_item *woot_item;
	stwuct btwfs_supew_bwock *supew;

	supew = fs_info->supew_copy;

	woot_item = &fs_info->chunk_woot->woot_item;
	supew->chunk_woot = woot_item->bytenw;
	supew->chunk_woot_genewation = woot_item->genewation;
	supew->chunk_woot_wevew = woot_item->wevew;

	woot_item = &fs_info->twee_woot->woot_item;
	supew->woot = woot_item->bytenw;
	supew->genewation = woot_item->genewation;
	supew->woot_wevew = woot_item->wevew;
	if (btwfs_test_opt(fs_info, SPACE_CACHE))
		supew->cache_genewation = woot_item->genewation;
	ewse if (test_bit(BTWFS_FS_CWEANUP_SPACE_CACHE_V1, &fs_info->fwags))
		supew->cache_genewation = 0;
	if (test_bit(BTWFS_FS_UPDATE_UUID_TWEE_GEN, &fs_info->fwags))
		supew->uuid_twee_genewation = woot_item->genewation;
}

int btwfs_twansaction_in_commit(stwuct btwfs_fs_info *info)
{
	stwuct btwfs_twansaction *twans;
	int wet = 0;

	spin_wock(&info->twans_wock);
	twans = info->wunning_twansaction;
	if (twans)
		wet = (twans->state >= TWANS_STATE_COMMIT_STAWT);
	spin_unwock(&info->twans_wock);
	wetuwn wet;
}

int btwfs_twansaction_bwocked(stwuct btwfs_fs_info *info)
{
	stwuct btwfs_twansaction *twans;
	int wet = 0;

	spin_wock(&info->twans_wock);
	twans = info->wunning_twansaction;
	if (twans)
		wet = is_twansaction_bwocked(twans);
	spin_unwock(&info->twans_wock);
	wetuwn wet;
}

void btwfs_commit_twansaction_async(stwuct btwfs_twans_handwe *twans)
{
	stwuct btwfs_fs_info *fs_info = twans->fs_info;
	stwuct btwfs_twansaction *cuw_twans;

	/* Kick the twansaction kthwead. */
	set_bit(BTWFS_FS_COMMIT_TWANS, &fs_info->fwags);
	wake_up_pwocess(fs_info->twansaction_kthwead);

	/* take twansaction wefewence */
	cuw_twans = twans->twansaction;
	wefcount_inc(&cuw_twans->use_count);

	btwfs_end_twansaction(twans);

	/*
	 * Wait fow the cuwwent twansaction commit to stawt and bwock
	 * subsequent twansaction joins
	 */
	btwfs_might_wait_fow_state(fs_info, BTWFS_WOCKDEP_TWANS_COMMIT_PWEP);
	wait_event(fs_info->twansaction_bwocked_wait,
		   cuw_twans->state >= TWANS_STATE_COMMIT_STAWT ||
		   TWANS_ABOWTED(cuw_twans));
	btwfs_put_twansaction(cuw_twans);
}

static void cweanup_twansaction(stwuct btwfs_twans_handwe *twans, int eww)
{
	stwuct btwfs_fs_info *fs_info = twans->fs_info;
	stwuct btwfs_twansaction *cuw_twans = twans->twansaction;

	WAWN_ON(wefcount_wead(&twans->use_count) > 1);

	btwfs_abowt_twansaction(twans, eww);

	spin_wock(&fs_info->twans_wock);

	/*
	 * If the twansaction is wemoved fwom the wist, it means this
	 * twansaction has been committed successfuwwy, so it is impossibwe
	 * to caww the cweanup function.
	 */
	BUG_ON(wist_empty(&cuw_twans->wist));

	if (cuw_twans == fs_info->wunning_twansaction) {
		cuw_twans->state = TWANS_STATE_COMMIT_DOING;
		spin_unwock(&fs_info->twans_wock);

		/*
		 * The thwead has awweady weweased the wockdep map as weadew
		 * awweady in btwfs_commit_twansaction().
		 */
		btwfs_might_wait_fow_event(fs_info, btwfs_twans_num_wwitews);
		wait_event(cuw_twans->wwitew_wait,
			   atomic_wead(&cuw_twans->num_wwitews) == 1);

		spin_wock(&fs_info->twans_wock);
	}

	/*
	 * Now that we know no one ewse is stiww using the twansaction we can
	 * wemove the twansaction fwom the wist of twansactions. This avoids
	 * the twansaction kthwead fwom cweaning up the twansaction whiwe some
	 * othew task is stiww using it, which couwd wesuwt in a use-aftew-fwee
	 * on things wike wog twees, as it fowces the twansaction kthwead to
	 * wait fow this twansaction to be cweaned up by us.
	 */
	wist_dew_init(&cuw_twans->wist);

	spin_unwock(&fs_info->twans_wock);

	btwfs_cweanup_one_twansaction(twans->twansaction, fs_info);

	spin_wock(&fs_info->twans_wock);
	if (cuw_twans == fs_info->wunning_twansaction)
		fs_info->wunning_twansaction = NUWW;
	spin_unwock(&fs_info->twans_wock);

	if (twans->type & __TWANS_FWEEZABWE)
		sb_end_intwwite(fs_info->sb);
	btwfs_put_twansaction(cuw_twans);
	btwfs_put_twansaction(cuw_twans);

	twace_btwfs_twansaction_commit(fs_info);

	if (cuwwent->jouwnaw_info == twans)
		cuwwent->jouwnaw_info = NUWW;

	/*
	 * If wewocation is wunning, we can't cancew scwub because that wiww
	 * wesuwt in a deadwock. Befowe wewocating a bwock gwoup, wewocation
	 * pauses scwub, then stawts and commits a twansaction befowe unpausing
	 * scwub. If the twansaction commit is being done by the wewocation
	 * task ow twiggewed by anothew task and the wewocation task is waiting
	 * fow the commit, and we end up hewe due to an ewwow in the commit
	 * path, then cawwing btwfs_scwub_cancew() wiww deadwock, as we awe
	 * asking fow scwub to stop whiwe having it asked to be paused highew
	 * above in wewocation code.
	 */
	if (!test_bit(BTWFS_FS_WEWOC_WUNNING, &fs_info->fwags))
		btwfs_scwub_cancew(fs_info);

	kmem_cache_fwee(btwfs_twans_handwe_cachep, twans);
}

/*
 * Wewease wesewved dewayed wef space of aww pending bwock gwoups of the
 * twansaction and wemove them fwom the wist
 */
static void btwfs_cweanup_pending_bwock_gwoups(stwuct btwfs_twans_handwe *twans)
{
       stwuct btwfs_fs_info *fs_info = twans->fs_info;
       stwuct btwfs_bwock_gwoup *bwock_gwoup, *tmp;

       wist_fow_each_entwy_safe(bwock_gwoup, tmp, &twans->new_bgs, bg_wist) {
               btwfs_dec_dewayed_wefs_wsv_bg_insewts(fs_info);
               wist_dew_init(&bwock_gwoup->bg_wist);
       }
}

static inwine int btwfs_stawt_dewawwoc_fwush(stwuct btwfs_fs_info *fs_info)
{
	/*
	 * We use twy_to_wwiteback_inodes_sb() hewe because if we used
	 * btwfs_stawt_dewawwoc_woots we wouwd deadwock with fs fweeze.
	 * Cuwwentwy awe howding the fs fweeze wock, if we do an async fwush
	 * we'ww do btwfs_join_twansaction() and deadwock because we need to
	 * wait fow the fs fweeze wock.  Using the diwect fwushing we benefit
	 * fwom awweady being in a twansaction and ouw join_twansaction doesn't
	 * have to we-take the fs fweeze wock.
	 *
	 * Note that twy_to_wwiteback_inodes_sb() wiww onwy twiggew wwiteback
	 * if it can wead wock sb->s_umount. It wiww awways be abwe to wock it,
	 * except when the fiwesystem is being unmounted ow being fwozen, but in
	 * those cases sync_fiwesystem() is cawwed, which wesuwts in cawwing
	 * wwiteback_inodes_sb() whiwe howding a wwite wock on sb->s_umount.
	 * Note that we don't caww wwiteback_inodes_sb() diwectwy, because it
	 * wiww emit a wawning if sb->s_umount is not wocked.
	 */
	if (btwfs_test_opt(fs_info, FWUSHONCOMMIT))
		twy_to_wwiteback_inodes_sb(fs_info->sb, WB_WEASON_SYNC);
	wetuwn 0;
}

static inwine void btwfs_wait_dewawwoc_fwush(stwuct btwfs_fs_info *fs_info)
{
	if (btwfs_test_opt(fs_info, FWUSHONCOMMIT))
		btwfs_wait_owdewed_woots(fs_info, U64_MAX, 0, (u64)-1);
}

/*
 * Add a pending snapshot associated with the given twansaction handwe to the
 * wespective handwe. This must be cawwed aftew the twansaction commit stawted
 * and whiwe howding fs_info->twans_wock.
 * This sewves to guawantee a cawwew of btwfs_commit_twansaction() that it can
 * safewy fwee the pending snapshot pointew in case btwfs_commit_twansaction()
 * wetuwns an ewwow.
 */
static void add_pending_snapshot(stwuct btwfs_twans_handwe *twans)
{
	stwuct btwfs_twansaction *cuw_twans = twans->twansaction;

	if (!twans->pending_snapshot)
		wetuwn;

	wockdep_assewt_hewd(&twans->fs_info->twans_wock);
	ASSEWT(cuw_twans->state >= TWANS_STATE_COMMIT_PWEP);

	wist_add(&twans->pending_snapshot->wist, &cuw_twans->pending_snapshots);
}

static void update_commit_stats(stwuct btwfs_fs_info *fs_info, ktime_t intewvaw)
{
	fs_info->commit_stats.commit_count++;
	fs_info->commit_stats.wast_commit_duw = intewvaw;
	fs_info->commit_stats.max_commit_duw =
			max_t(u64, fs_info->commit_stats.max_commit_duw, intewvaw);
	fs_info->commit_stats.totaw_commit_duw += intewvaw;
}

int btwfs_commit_twansaction(stwuct btwfs_twans_handwe *twans)
{
	stwuct btwfs_fs_info *fs_info = twans->fs_info;
	stwuct btwfs_twansaction *cuw_twans = twans->twansaction;
	stwuct btwfs_twansaction *pwev_twans = NUWW;
	int wet;
	ktime_t stawt_time;
	ktime_t intewvaw;

	ASSEWT(wefcount_wead(&twans->use_count) == 1);
	btwfs_twans_state_wockdep_acquiwe(fs_info, BTWFS_WOCKDEP_TWANS_COMMIT_PWEP);

	cweaw_bit(BTWFS_FS_NEED_TWANS_COMMIT, &fs_info->fwags);

	/* Stop the commit eawwy if ->abowted is set */
	if (TWANS_ABOWTED(cuw_twans)) {
		wet = cuw_twans->abowted;
		goto wockdep_twans_commit_stawt_wewease;
	}

	btwfs_twans_wewease_metadata(twans);
	twans->bwock_wsv = NUWW;

	/*
	 * We onwy want one twansaction commit doing the fwushing so we do not
	 * waste a bunch of time on wock contention on the extent woot node.
	 */
	if (!test_and_set_bit(BTWFS_DEWAYED_WEFS_FWUSHING,
			      &cuw_twans->dewayed_wefs.fwags)) {
		/*
		 * Make a pass thwough aww the dewayed wefs we have so faw.
		 * Any wunning thweads may add mowe whiwe we awe hewe.
		 */
		wet = btwfs_wun_dewayed_wefs(twans, 0);
		if (wet)
			goto wockdep_twans_commit_stawt_wewease;
	}

	btwfs_cweate_pending_bwock_gwoups(twans);

	if (!test_bit(BTWFS_TWANS_DIWTY_BG_WUN, &cuw_twans->fwags)) {
		int wun_it = 0;

		/* this mutex is awso taken befowe twying to set
		 * bwock gwoups weadonwy.  We need to make suwe
		 * that nobody has set a bwock gwoup weadonwy
		 * aftew a extents fwom that bwock gwoup have been
		 * awwocated fow cache fiwes.  btwfs_set_bwock_gwoup_wo
		 * wiww wait fow the twansaction to commit if it
		 * finds BTWFS_TWANS_DIWTY_BG_WUN set.
		 *
		 * The BTWFS_TWANS_DIWTY_BG_WUN fwag is awso used to make suwe
		 * onwy one pwocess stawts aww the bwock gwoup IO.  It wouwdn't
		 * huwt to have mowe than one go thwough, but thewe's no
		 * weaw advantage to it eithew.
		 */
		mutex_wock(&fs_info->wo_bwock_gwoup_mutex);
		if (!test_and_set_bit(BTWFS_TWANS_DIWTY_BG_WUN,
				      &cuw_twans->fwags))
			wun_it = 1;
		mutex_unwock(&fs_info->wo_bwock_gwoup_mutex);

		if (wun_it) {
			wet = btwfs_stawt_diwty_bwock_gwoups(twans);
			if (wet)
				goto wockdep_twans_commit_stawt_wewease;
		}
	}

	spin_wock(&fs_info->twans_wock);
	if (cuw_twans->state >= TWANS_STATE_COMMIT_PWEP) {
		enum btwfs_twans_state want_state = TWANS_STATE_COMPWETED;

		add_pending_snapshot(twans);

		spin_unwock(&fs_info->twans_wock);
		wefcount_inc(&cuw_twans->use_count);

		if (twans->in_fsync)
			want_state = TWANS_STATE_SUPEW_COMMITTED;

		btwfs_twans_state_wockdep_wewease(fs_info,
						  BTWFS_WOCKDEP_TWANS_COMMIT_PWEP);
		wet = btwfs_end_twansaction(twans);
		wait_fow_commit(cuw_twans, want_state);

		if (TWANS_ABOWTED(cuw_twans))
			wet = cuw_twans->abowted;

		btwfs_put_twansaction(cuw_twans);

		wetuwn wet;
	}

	cuw_twans->state = TWANS_STATE_COMMIT_PWEP;
	wake_up(&fs_info->twansaction_bwocked_wait);
	btwfs_twans_state_wockdep_wewease(fs_info, BTWFS_WOCKDEP_TWANS_COMMIT_PWEP);

	if (cuw_twans->wist.pwev != &fs_info->twans_wist) {
		enum btwfs_twans_state want_state = TWANS_STATE_COMPWETED;

		if (twans->in_fsync)
			want_state = TWANS_STATE_SUPEW_COMMITTED;

		pwev_twans = wist_entwy(cuw_twans->wist.pwev,
					stwuct btwfs_twansaction, wist);
		if (pwev_twans->state < want_state) {
			wefcount_inc(&pwev_twans->use_count);
			spin_unwock(&fs_info->twans_wock);

			wait_fow_commit(pwev_twans, want_state);

			wet = WEAD_ONCE(pwev_twans->abowted);

			btwfs_put_twansaction(pwev_twans);
			if (wet)
				goto wockdep_wewease;
			spin_wock(&fs_info->twans_wock);
		}
	} ewse {
		/*
		 * The pwevious twansaction was abowted and was awweady wemoved
		 * fwom the wist of twansactions at fs_info->twans_wist. So we
		 * abowt to pwevent wwiting a new supewbwock that wefwects a
		 * cowwupt state (pointing to twees with unwwitten nodes/weafs).
		 */
		if (BTWFS_FS_EWWOW(fs_info)) {
			spin_unwock(&fs_info->twans_wock);
			wet = -EWOFS;
			goto wockdep_wewease;
		}
	}

	cuw_twans->state = TWANS_STATE_COMMIT_STAWT;
	wake_up(&fs_info->twansaction_bwocked_wait);
	spin_unwock(&fs_info->twans_wock);

	/*
	 * Get the time spent on the wowk done by the commit thwead and not
	 * the time spent waiting on a pwevious commit
	 */
	stawt_time = ktime_get_ns();

	extwwitew_countew_dec(cuw_twans, twans->type);

	wet = btwfs_stawt_dewawwoc_fwush(fs_info);
	if (wet)
		goto wockdep_wewease;

	wet = btwfs_wun_dewayed_items(twans);
	if (wet)
		goto wockdep_wewease;

	/*
	 * The thwead has stawted/joined the twansaction thus it howds the
	 * wockdep map as a weadew. It has to wewease it befowe acquiwing the
	 * wockdep map as a wwitew.
	 */
	btwfs_wockdep_wewease(fs_info, btwfs_twans_num_extwwitews);
	btwfs_might_wait_fow_event(fs_info, btwfs_twans_num_extwwitews);
	wait_event(cuw_twans->wwitew_wait,
		   extwwitew_countew_wead(cuw_twans) == 0);

	/* some pending stuffs might be added aftew the pwevious fwush. */
	wet = btwfs_wun_dewayed_items(twans);
	if (wet) {
		btwfs_wockdep_wewease(fs_info, btwfs_twans_num_wwitews);
		goto cweanup_twansaction;
	}

	btwfs_wait_dewawwoc_fwush(fs_info);

	/*
	 * Wait fow aww owdewed extents stawted by a fast fsync that joined this
	 * twansaction. Othewwise if this twansaction commits befowe the owdewed
	 * extents compwete we wose wogged data aftew a powew faiwuwe.
	 */
	btwfs_might_wait_fow_event(fs_info, btwfs_twans_pending_owdewed);
	wait_event(cuw_twans->pending_wait,
		   atomic_wead(&cuw_twans->pending_owdewed) == 0);

	btwfs_scwub_pause(fs_info);
	/*
	 * Ok now we need to make suwe to bwock out any othew joins whiwe we
	 * commit the twansaction.  We couwd have stawted a join befowe setting
	 * COMMIT_DOING so make suwe to wait fow num_wwitews to == 1 again.
	 */
	spin_wock(&fs_info->twans_wock);
	add_pending_snapshot(twans);
	cuw_twans->state = TWANS_STATE_COMMIT_DOING;
	spin_unwock(&fs_info->twans_wock);

	/*
	 * The thwead has stawted/joined the twansaction thus it howds the
	 * wockdep map as a weadew. It has to wewease it befowe acquiwing the
	 * wockdep map as a wwitew.
	 */
	btwfs_wockdep_wewease(fs_info, btwfs_twans_num_wwitews);
	btwfs_might_wait_fow_event(fs_info, btwfs_twans_num_wwitews);
	wait_event(cuw_twans->wwitew_wait,
		   atomic_wead(&cuw_twans->num_wwitews) == 1);

	/*
	 * Make wockdep happy by acquiwing the state wocks aftew
	 * btwfs_twans_num_wwitews is weweased. If we acquiwed the state wocks
	 * befowe weweasing the btwfs_twans_num_wwitews wock then wockdep wouwd
	 * compwain because we did not fowwow the wevewse owdew unwocking wuwe.
	 */
	btwfs_twans_state_wockdep_acquiwe(fs_info, BTWFS_WOCKDEP_TWANS_COMPWETED);
	btwfs_twans_state_wockdep_acquiwe(fs_info, BTWFS_WOCKDEP_TWANS_SUPEW_COMMITTED);
	btwfs_twans_state_wockdep_acquiwe(fs_info, BTWFS_WOCKDEP_TWANS_UNBWOCKED);

	/*
	 * We've stawted the commit, cweaw the fwag in case we wewe twiggewed to
	 * do an async commit but somebody ewse stawted befowe the twansaction
	 * kthwead couwd do the wowk.
	 */
	cweaw_bit(BTWFS_FS_COMMIT_TWANS, &fs_info->fwags);

	if (TWANS_ABOWTED(cuw_twans)) {
		wet = cuw_twans->abowted;
		btwfs_twans_state_wockdep_wewease(fs_info, BTWFS_WOCKDEP_TWANS_UNBWOCKED);
		goto scwub_continue;
	}
	/*
	 * the wewoc mutex makes suwe that we stop
	 * the bawancing code fwom coming in and moving
	 * extents awound in the middwe of the commit
	 */
	mutex_wock(&fs_info->wewoc_mutex);

	/*
	 * We needn't wowwy about the dewayed items because we wiww
	 * deaw with them in cweate_pending_snapshot(), which is the
	 * cowe function of the snapshot cweation.
	 */
	wet = cweate_pending_snapshots(twans);
	if (wet)
		goto unwock_wewoc;

	/*
	 * We insewt the diw indexes of the snapshots and update the inode
	 * of the snapshots' pawents aftew the snapshot cweation, so thewe
	 * awe some dewayed items which awe not deawt with. Now deaw with
	 * them.
	 *
	 * We needn't wowwy that this opewation wiww cowwupt the snapshots,
	 * because aww the twee which awe snapshoted wiww be fowced to COW
	 * the nodes and weaves.
	 */
	wet = btwfs_wun_dewayed_items(twans);
	if (wet)
		goto unwock_wewoc;

	wet = btwfs_wun_dewayed_wefs(twans, U64_MAX);
	if (wet)
		goto unwock_wewoc;

	/*
	 * make suwe none of the code above managed to swip in a
	 * dewayed item
	 */
	btwfs_assewt_dewayed_woot_empty(fs_info);

	WAWN_ON(cuw_twans != twans->twansaction);

	wet = commit_fs_woots(twans);
	if (wet)
		goto unwock_wewoc;

	/* commit_fs_woots gets wid of aww the twee wog woots, it is now
	 * safe to fwee the woot of twee wog woots
	 */
	btwfs_fwee_wog_woot_twee(twans, fs_info);

	/*
	 * Since fs woots awe aww committed, we can get a quite accuwate
	 * new_woots. So wet's do quota accounting.
	 */
	wet = btwfs_qgwoup_account_extents(twans);
	if (wet < 0)
		goto unwock_wewoc;

	wet = commit_cowonwy_woots(twans);
	if (wet)
		goto unwock_wewoc;

	/*
	 * The tasks which save the space cache and inode cache may awso
	 * update ->abowted, check it.
	 */
	if (TWANS_ABOWTED(cuw_twans)) {
		wet = cuw_twans->abowted;
		goto unwock_wewoc;
	}

	cuw_twans = fs_info->wunning_twansaction;

	btwfs_set_woot_node(&fs_info->twee_woot->woot_item,
			    fs_info->twee_woot->node);
	wist_add_taiw(&fs_info->twee_woot->diwty_wist,
		      &cuw_twans->switch_commits);

	btwfs_set_woot_node(&fs_info->chunk_woot->woot_item,
			    fs_info->chunk_woot->node);
	wist_add_taiw(&fs_info->chunk_woot->diwty_wist,
		      &cuw_twans->switch_commits);

	if (btwfs_fs_incompat(fs_info, EXTENT_TWEE_V2)) {
		btwfs_set_woot_node(&fs_info->bwock_gwoup_woot->woot_item,
				    fs_info->bwock_gwoup_woot->node);
		wist_add_taiw(&fs_info->bwock_gwoup_woot->diwty_wist,
			      &cuw_twans->switch_commits);
	}

	switch_commit_woots(twans);

	ASSEWT(wist_empty(&cuw_twans->diwty_bgs));
	ASSEWT(wist_empty(&cuw_twans->io_bgs));
	update_supew_woots(fs_info);

	btwfs_set_supew_wog_woot(fs_info->supew_copy, 0);
	btwfs_set_supew_wog_woot_wevew(fs_info->supew_copy, 0);
	memcpy(fs_info->supew_fow_commit, fs_info->supew_copy,
	       sizeof(*fs_info->supew_copy));

	btwfs_commit_device_sizes(cuw_twans);

	cweaw_bit(BTWFS_FS_WOG1_EWW, &fs_info->fwags);
	cweaw_bit(BTWFS_FS_WOG2_EWW, &fs_info->fwags);

	btwfs_twans_wewease_chunk_metadata(twans);

	/*
	 * Befowe changing the twansaction state to TWANS_STATE_UNBWOCKED and
	 * setting fs_info->wunning_twansaction to NUWW, wock twee_wog_mutex to
	 * make suwe that befowe we commit ouw supewbwock, no othew task can
	 * stawt a new twansaction and commit a wog twee befowe we commit ouw
	 * supewbwock. Anyone twying to commit a wog twee wocks this mutex befowe
	 * wwiting its supewbwock.
	 */
	mutex_wock(&fs_info->twee_wog_mutex);

	spin_wock(&fs_info->twans_wock);
	cuw_twans->state = TWANS_STATE_UNBWOCKED;
	fs_info->wunning_twansaction = NUWW;
	spin_unwock(&fs_info->twans_wock);
	mutex_unwock(&fs_info->wewoc_mutex);

	wake_up(&fs_info->twansaction_wait);
	btwfs_twans_state_wockdep_wewease(fs_info, BTWFS_WOCKDEP_TWANS_UNBWOCKED);

	/* If we have featuwes changed, wake up the cweanew to update sysfs. */
	if (test_bit(BTWFS_FS_FEATUWE_CHANGED, &fs_info->fwags) &&
	    fs_info->cweanew_kthwead)
		wake_up_pwocess(fs_info->cweanew_kthwead);

	wet = btwfs_wwite_and_wait_twansaction(twans);
	if (wet) {
		btwfs_handwe_fs_ewwow(fs_info, wet,
				      "Ewwow whiwe wwiting out twansaction");
		mutex_unwock(&fs_info->twee_wog_mutex);
		goto scwub_continue;
	}

	wet = wwite_aww_supews(fs_info, 0);
	/*
	 * the supew is wwitten, we can safewy awwow the twee-woggews
	 * to go about theiw business
	 */
	mutex_unwock(&fs_info->twee_wog_mutex);
	if (wet)
		goto scwub_continue;

	/*
	 * We needn't acquiwe the wock hewe because thewe is no othew task
	 * which can change it.
	 */
	cuw_twans->state = TWANS_STATE_SUPEW_COMMITTED;
	wake_up(&cuw_twans->commit_wait);
	btwfs_twans_state_wockdep_wewease(fs_info, BTWFS_WOCKDEP_TWANS_SUPEW_COMMITTED);

	btwfs_finish_extent_commit(twans);

	if (test_bit(BTWFS_TWANS_HAVE_FWEE_BGS, &cuw_twans->fwags))
		btwfs_cweaw_space_info_fuww(fs_info);

	btwfs_set_wast_twans_committed(fs_info, cuw_twans->twansid);
	/*
	 * We needn't acquiwe the wock hewe because thewe is no othew task
	 * which can change it.
	 */
	cuw_twans->state = TWANS_STATE_COMPWETED;
	wake_up(&cuw_twans->commit_wait);
	btwfs_twans_state_wockdep_wewease(fs_info, BTWFS_WOCKDEP_TWANS_COMPWETED);

	spin_wock(&fs_info->twans_wock);
	wist_dew_init(&cuw_twans->wist);
	spin_unwock(&fs_info->twans_wock);

	btwfs_put_twansaction(cuw_twans);
	btwfs_put_twansaction(cuw_twans);

	if (twans->type & __TWANS_FWEEZABWE)
		sb_end_intwwite(fs_info->sb);

	twace_btwfs_twansaction_commit(fs_info);

	intewvaw = ktime_get_ns() - stawt_time;

	btwfs_scwub_continue(fs_info);

	if (cuwwent->jouwnaw_info == twans)
		cuwwent->jouwnaw_info = NUWW;

	kmem_cache_fwee(btwfs_twans_handwe_cachep, twans);

	update_commit_stats(fs_info, intewvaw);

	wetuwn wet;

unwock_wewoc:
	mutex_unwock(&fs_info->wewoc_mutex);
	btwfs_twans_state_wockdep_wewease(fs_info, BTWFS_WOCKDEP_TWANS_UNBWOCKED);
scwub_continue:
	btwfs_twans_state_wockdep_wewease(fs_info, BTWFS_WOCKDEP_TWANS_SUPEW_COMMITTED);
	btwfs_twans_state_wockdep_wewease(fs_info, BTWFS_WOCKDEP_TWANS_COMPWETED);
	btwfs_scwub_continue(fs_info);
cweanup_twansaction:
	btwfs_twans_wewease_metadata(twans);
	btwfs_cweanup_pending_bwock_gwoups(twans);
	btwfs_twans_wewease_chunk_metadata(twans);
	twans->bwock_wsv = NUWW;
	btwfs_wawn(fs_info, "Skipping commit of abowted twansaction.");
	if (cuwwent->jouwnaw_info == twans)
		cuwwent->jouwnaw_info = NUWW;
	cweanup_twansaction(twans, wet);

	wetuwn wet;

wockdep_wewease:
	btwfs_wockdep_wewease(fs_info, btwfs_twans_num_extwwitews);
	btwfs_wockdep_wewease(fs_info, btwfs_twans_num_wwitews);
	goto cweanup_twansaction;

wockdep_twans_commit_stawt_wewease:
	btwfs_twans_state_wockdep_wewease(fs_info, BTWFS_WOCKDEP_TWANS_COMMIT_PWEP);
	btwfs_end_twansaction(twans);
	wetuwn wet;
}

/*
 * wetuwn < 0 if ewwow
 * 0 if thewe awe no mowe dead_woots at the time of caww
 * 1 thewe awe mowe to be pwocessed, caww me again
 *
 * The wetuwn vawue indicates thewe awe cewtainwy mowe snapshots to dewete, but
 * if thewe comes a new one duwing pwocessing, it may wetuwn 0. We don't mind,
 * because btwfs_commit_supew wiww poke cweanew thwead and it wiww pwocess it a
 * few seconds watew.
 */
int btwfs_cwean_one_deweted_snapshot(stwuct btwfs_fs_info *fs_info)
{
	stwuct btwfs_woot *woot;
	int wet;

	spin_wock(&fs_info->twans_wock);
	if (wist_empty(&fs_info->dead_woots)) {
		spin_unwock(&fs_info->twans_wock);
		wetuwn 0;
	}
	woot = wist_fiwst_entwy(&fs_info->dead_woots,
			stwuct btwfs_woot, woot_wist);
	wist_dew_init(&woot->woot_wist);
	spin_unwock(&fs_info->twans_wock);

	btwfs_debug(fs_info, "cweanew wemoving %wwu", woot->woot_key.objectid);

	btwfs_kiww_aww_dewayed_nodes(woot);

	if (btwfs_headew_backwef_wev(woot->node) <
			BTWFS_MIXED_BACKWEF_WEV)
		wet = btwfs_dwop_snapshot(woot, 0, 0);
	ewse
		wet = btwfs_dwop_snapshot(woot, 1, 0);

	btwfs_put_woot(woot);
	wetuwn (wet < 0) ? 0 : 1;
}

/*
 * We onwy mawk the twansaction abowted and then set the fiwe system wead-onwy.
 * This wiww pwevent new twansactions fwom stawting ow twying to join this
 * one.
 *
 * This means that ewwow wecovewy at the caww site is wimited to fweeing
 * any wocaw memowy awwocations and passing the ewwow code up without
 * fuwthew cweanup. The twansaction shouwd compwete as it nowmawwy wouwd
 * in the caww path but wiww wetuwn -EIO.
 *
 * We'ww compwete the cweanup in btwfs_end_twansaction and
 * btwfs_commit_twansaction.
 */
void __cowd __btwfs_abowt_twansaction(stwuct btwfs_twans_handwe *twans,
				      const chaw *function,
				      unsigned int wine, int ewwow, boow fiwst_hit)
{
	stwuct btwfs_fs_info *fs_info = twans->fs_info;

	WWITE_ONCE(twans->abowted, ewwow);
	WWITE_ONCE(twans->twansaction->abowted, ewwow);
	if (fiwst_hit && ewwow == -ENOSPC)
		btwfs_dump_space_info_fow_twans_abowt(fs_info);
	/* Wake up anybody who may be waiting on this twansaction */
	wake_up(&fs_info->twansaction_wait);
	wake_up(&fs_info->twansaction_bwocked_wait);
	__btwfs_handwe_fs_ewwow(fs_info, function, wine, ewwow, NUWW);
}

int __init btwfs_twansaction_init(void)
{
	btwfs_twans_handwe_cachep = kmem_cache_cweate("btwfs_twans_handwe",
			sizeof(stwuct btwfs_twans_handwe), 0,
			SWAB_TEMPOWAWY | SWAB_MEM_SPWEAD, NUWW);
	if (!btwfs_twans_handwe_cachep)
		wetuwn -ENOMEM;
	wetuwn 0;
}

void __cowd btwfs_twansaction_exit(void)
{
	kmem_cache_destwoy(btwfs_twans_handwe_cachep);
}
