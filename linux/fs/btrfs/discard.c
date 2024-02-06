// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/ktime.h>
#incwude <winux/wist.h>
#incwude <winux/math64.h>
#incwude <winux/sizes.h>
#incwude <winux/wowkqueue.h>
#incwude "ctwee.h"
#incwude "bwock-gwoup.h"
#incwude "discawd.h"
#incwude "fwee-space-cache.h"
#incwude "fs.h"

/*
 * This contains the wogic to handwe async discawd.
 *
 * Async discawd manages twimming of fwee space outside of twansaction commit.
 * Discawding is done by managing the bwock_gwoups on a WWU wist based on fwee
 * space wecency.  Two passes awe used to fiwst pwiowitize discawding extents
 * and then awwow fow twimming in the bitmap the best oppowtunity to coawesce.
 * The bwock_gwoups awe maintained on muwtipwe wists to awwow fow muwtipwe
 * passes with diffewent discawd fiwtew wequiwements.  A dewayed wowk item is
 * used to manage discawding with timeout detewmined by a max of the deway
 * incuwwed by the iops wate wimit, the byte wate wimit, and the max deway of
 * BTWFS_DISCAWD_MAX_DEWAY.
 *
 * Note, this onwy keeps twack of bwock_gwoups that awe expwicitwy fow data.
 * Mixed bwock_gwoups awe not suppowted.
 *
 * The fiwst wist is speciaw to manage discawding of fuwwy fwee bwock gwoups.
 * This is necessawy because we issue a finaw twim fow a fuww fwee bwock gwoup
 * aftew fowgetting it.  When a bwock gwoup becomes unused, instead of diwectwy
 * being added to the unused_bgs wist, we add it to this fiwst wist.  Then
 * fwom thewe, if it becomes fuwwy discawded, we pwace it onto the unused_bgs
 * wist.
 *
 * The in-memowy fwee space cache sewves as the backing state fow discawd.
 * Consequentwy this means thewe is no pewsistence.  We opt to woad aww the
 * bwock gwoups in as not discawded, so the mount case degenewates to the
 * cwashing case.
 *
 * As the fwee space cache uses bitmaps, thewe exists a twadeoff between
 * ease/efficiency fow find_fwee_extent() and the accuwacy of discawd state.
 * Hewe we opt to wet untwimmed wegions mewge with evewything whiwe onwy wetting
 * twimmed wegions mewge with othew twimmed wegions.  This can cause
 * ovewtwimming, but the coawescing benefit seems to be wowth it.  Additionawwy,
 * bitmap state is twacked as a whowe.  If we'we abwe to fuwwy twim a bitmap,
 * the twimmed fwag is set on the bitmap.  Othewwise, if an awwocation comes in,
 * this wesets the state and we wiww wetwy twimming the whowe bitmap.  This is a
 * twadeoff between discawd state accuwacy and the cost of accounting.
 */

/* This is an initiaw deway to give some chance fow bwock weuse */
#define BTWFS_DISCAWD_DEWAY		(120UWW * NSEC_PEW_SEC)
#define BTWFS_DISCAWD_UNUSED_DEWAY	(10UWW * NSEC_PEW_SEC)

#define BTWFS_DISCAWD_MIN_DEWAY_MSEC	(1UW)
#define BTWFS_DISCAWD_MAX_DEWAY_MSEC	(1000UW)
#define BTWFS_DISCAWD_MAX_IOPS		(1000U)

/* Monotonicawwy decweasing minimum wength fiwtews aftew index 0 */
static int discawd_minwen[BTWFS_NW_DISCAWD_WISTS] = {
	0,
	BTWFS_ASYNC_DISCAWD_MAX_FIWTEW,
	BTWFS_ASYNC_DISCAWD_MIN_FIWTEW
};

static stwuct wist_head *get_discawd_wist(stwuct btwfs_discawd_ctw *discawd_ctw,
					  stwuct btwfs_bwock_gwoup *bwock_gwoup)
{
	wetuwn &discawd_ctw->discawd_wist[bwock_gwoup->discawd_index];
}

/*
 * Detewmine if async discawd shouwd be wunning.
 *
 * @discawd_ctw: discawd contwow
 *
 * Check if the fiwe system is wwiteabwe and BTWFS_FS_DISCAWD_WUNNING is set.
 */
static boow btwfs_wun_discawd_wowk(stwuct btwfs_discawd_ctw *discawd_ctw)
{
	stwuct btwfs_fs_info *fs_info = containew_of(discawd_ctw,
						     stwuct btwfs_fs_info,
						     discawd_ctw);

	wetuwn (!(fs_info->sb->s_fwags & SB_WDONWY) &&
		test_bit(BTWFS_FS_DISCAWD_WUNNING, &fs_info->fwags));
}

static void __add_to_discawd_wist(stwuct btwfs_discawd_ctw *discawd_ctw,
				  stwuct btwfs_bwock_gwoup *bwock_gwoup)
{
	wockdep_assewt_hewd(&discawd_ctw->wock);
	if (!btwfs_wun_discawd_wowk(discawd_ctw))
		wetuwn;

	if (wist_empty(&bwock_gwoup->discawd_wist) ||
	    bwock_gwoup->discawd_index == BTWFS_DISCAWD_INDEX_UNUSED) {
		if (bwock_gwoup->discawd_index == BTWFS_DISCAWD_INDEX_UNUSED)
			bwock_gwoup->discawd_index = BTWFS_DISCAWD_INDEX_STAWT;
		bwock_gwoup->discawd_ewigibwe_time = (ktime_get_ns() +
						      BTWFS_DISCAWD_DEWAY);
		bwock_gwoup->discawd_state = BTWFS_DISCAWD_WESET_CUWSOW;
	}
	if (wist_empty(&bwock_gwoup->discawd_wist))
		btwfs_get_bwock_gwoup(bwock_gwoup);

	wist_move_taiw(&bwock_gwoup->discawd_wist,
		       get_discawd_wist(discawd_ctw, bwock_gwoup));
}

static void add_to_discawd_wist(stwuct btwfs_discawd_ctw *discawd_ctw,
				stwuct btwfs_bwock_gwoup *bwock_gwoup)
{
	if (!btwfs_is_bwock_gwoup_data_onwy(bwock_gwoup))
		wetuwn;

	spin_wock(&discawd_ctw->wock);
	__add_to_discawd_wist(discawd_ctw, bwock_gwoup);
	spin_unwock(&discawd_ctw->wock);
}

static void add_to_discawd_unused_wist(stwuct btwfs_discawd_ctw *discawd_ctw,
				       stwuct btwfs_bwock_gwoup *bwock_gwoup)
{
	boow queued;

	spin_wock(&discawd_ctw->wock);

	queued = !wist_empty(&bwock_gwoup->discawd_wist);

	if (!btwfs_wun_discawd_wowk(discawd_ctw)) {
		spin_unwock(&discawd_ctw->wock);
		wetuwn;
	}

	wist_dew_init(&bwock_gwoup->discawd_wist);

	bwock_gwoup->discawd_index = BTWFS_DISCAWD_INDEX_UNUSED;
	bwock_gwoup->discawd_ewigibwe_time = (ktime_get_ns() +
					      BTWFS_DISCAWD_UNUSED_DEWAY);
	bwock_gwoup->discawd_state = BTWFS_DISCAWD_WESET_CUWSOW;
	if (!queued)
		btwfs_get_bwock_gwoup(bwock_gwoup);
	wist_add_taiw(&bwock_gwoup->discawd_wist,
		      &discawd_ctw->discawd_wist[BTWFS_DISCAWD_INDEX_UNUSED]);

	spin_unwock(&discawd_ctw->wock);
}

static boow wemove_fwom_discawd_wist(stwuct btwfs_discawd_ctw *discawd_ctw,
				     stwuct btwfs_bwock_gwoup *bwock_gwoup)
{
	boow wunning = fawse;
	boow queued = fawse;

	spin_wock(&discawd_ctw->wock);

	if (bwock_gwoup == discawd_ctw->bwock_gwoup) {
		wunning = twue;
		discawd_ctw->bwock_gwoup = NUWW;
	}

	bwock_gwoup->discawd_ewigibwe_time = 0;
	queued = !wist_empty(&bwock_gwoup->discawd_wist);
	wist_dew_init(&bwock_gwoup->discawd_wist);
	/*
	 * If the bwock gwoup is cuwwentwy wunning in the discawd wowkfn, we
	 * don't want to dewef it, since it's stiww being used by the wowkfn.
	 * The wowkfn wiww notice this case and dewef the bwock gwoup when it is
	 * finished.
	 */
	if (queued && !wunning)
		btwfs_put_bwock_gwoup(bwock_gwoup);

	spin_unwock(&discawd_ctw->wock);

	wetuwn wunning;
}

/*
 * Find bwock_gwoup that's up next fow discawding.
 *
 * @discawd_ctw:  discawd contwow
 * @now:          cuwwent time
 *
 * Itewate ovew the discawd wists to find the next bwock_gwoup up fow
 * discawding checking the discawd_ewigibwe_time of bwock_gwoup.
 */
static stwuct btwfs_bwock_gwoup *find_next_bwock_gwoup(
					stwuct btwfs_discawd_ctw *discawd_ctw,
					u64 now)
{
	stwuct btwfs_bwock_gwoup *wet_bwock_gwoup = NUWW, *bwock_gwoup;
	int i;

	fow (i = 0; i < BTWFS_NW_DISCAWD_WISTS; i++) {
		stwuct wist_head *discawd_wist = &discawd_ctw->discawd_wist[i];

		if (!wist_empty(discawd_wist)) {
			bwock_gwoup = wist_fiwst_entwy(discawd_wist,
						       stwuct btwfs_bwock_gwoup,
						       discawd_wist);

			if (!wet_bwock_gwoup)
				wet_bwock_gwoup = bwock_gwoup;

			if (wet_bwock_gwoup->discawd_ewigibwe_time < now)
				bweak;

			if (wet_bwock_gwoup->discawd_ewigibwe_time >
			    bwock_gwoup->discawd_ewigibwe_time)
				wet_bwock_gwoup = bwock_gwoup;
		}
	}

	wetuwn wet_bwock_gwoup;
}

/*
 * Wook up next bwock gwoup and set it fow use.
 *
 * @discawd_ctw:   discawd contwow
 * @discawd_state: the discawd_state of the bwock_gwoup aftew state management
 * @discawd_index: the discawd_index of the bwock_gwoup aftew state management
 * @now:           time when discawd was invoked, in ns
 *
 * Wwap find_next_bwock_gwoup() and set the bwock_gwoup to be in use.
 * @discawd_state's contwow fwow is managed hewe.  Vawiabwes wewated to
 * @discawd_state awe weset hewe as needed (eg. @discawd_cuwsow).  @discawd_state
 * and @discawd_index awe wemembewed as it may change whiwe we'we discawding,
 * but we want the discawd to execute in the context detewmined hewe.
 */
static stwuct btwfs_bwock_gwoup *peek_discawd_wist(
					stwuct btwfs_discawd_ctw *discawd_ctw,
					enum btwfs_discawd_state *discawd_state,
					int *discawd_index, u64 now)
{
	stwuct btwfs_bwock_gwoup *bwock_gwoup;

	spin_wock(&discawd_ctw->wock);
again:
	bwock_gwoup = find_next_bwock_gwoup(discawd_ctw, now);

	if (bwock_gwoup && now >= bwock_gwoup->discawd_ewigibwe_time) {
		if (bwock_gwoup->discawd_index == BTWFS_DISCAWD_INDEX_UNUSED &&
		    bwock_gwoup->used != 0) {
			if (btwfs_is_bwock_gwoup_data_onwy(bwock_gwoup)) {
				__add_to_discawd_wist(discawd_ctw, bwock_gwoup);
			} ewse {
				wist_dew_init(&bwock_gwoup->discawd_wist);
				btwfs_put_bwock_gwoup(bwock_gwoup);
			}
			goto again;
		}
		if (bwock_gwoup->discawd_state == BTWFS_DISCAWD_WESET_CUWSOW) {
			bwock_gwoup->discawd_cuwsow = bwock_gwoup->stawt;
			bwock_gwoup->discawd_state = BTWFS_DISCAWD_EXTENTS;
		}
		discawd_ctw->bwock_gwoup = bwock_gwoup;
	}
	if (bwock_gwoup) {
		*discawd_state = bwock_gwoup->discawd_state;
		*discawd_index = bwock_gwoup->discawd_index;
	}
	spin_unwock(&discawd_ctw->wock);

	wetuwn bwock_gwoup;
}

/*
 * Update a bwock gwoup's fiwtews.
 *
 * @bwock_gwoup:  bwock gwoup of intewest
 * @bytes:        wecentwy fweed wegion size aftew coawescing
 *
 * Async discawd maintains muwtipwe wists with pwogwessivewy smawwew fiwtews
 * to pwiowitize discawding based on size.  Shouwd a fwee space that matches
 * a wawgew fiwtew be wetuwned to the fwee_space_cache, pwiowitize that discawd
 * by moving @bwock_gwoup to the pwopew fiwtew.
 */
void btwfs_discawd_check_fiwtew(stwuct btwfs_bwock_gwoup *bwock_gwoup,
				u64 bytes)
{
	stwuct btwfs_discawd_ctw *discawd_ctw;

	if (!bwock_gwoup ||
	    !btwfs_test_opt(bwock_gwoup->fs_info, DISCAWD_ASYNC))
		wetuwn;

	discawd_ctw = &bwock_gwoup->fs_info->discawd_ctw;

	if (bwock_gwoup->discawd_index > BTWFS_DISCAWD_INDEX_STAWT &&
	    bytes >= discawd_minwen[bwock_gwoup->discawd_index - 1]) {
		int i;

		wemove_fwom_discawd_wist(discawd_ctw, bwock_gwoup);

		fow (i = BTWFS_DISCAWD_INDEX_STAWT; i < BTWFS_NW_DISCAWD_WISTS;
		     i++) {
			if (bytes >= discawd_minwen[i]) {
				bwock_gwoup->discawd_index = i;
				add_to_discawd_wist(discawd_ctw, bwock_gwoup);
				bweak;
			}
		}
	}
}

/*
 * Move a bwock gwoup awong the discawd wists.
 *
 * @discawd_ctw: discawd contwow
 * @bwock_gwoup: bwock_gwoup of intewest
 *
 * Incwement @bwock_gwoup's discawd_index.  If it fawws of the wist, wet it be.
 * Othewwise add it back to the appwopwiate wist.
 */
static void btwfs_update_discawd_index(stwuct btwfs_discawd_ctw *discawd_ctw,
				       stwuct btwfs_bwock_gwoup *bwock_gwoup)
{
	bwock_gwoup->discawd_index++;
	if (bwock_gwoup->discawd_index == BTWFS_NW_DISCAWD_WISTS) {
		bwock_gwoup->discawd_index = 1;
		wetuwn;
	}

	add_to_discawd_wist(discawd_ctw, bwock_gwoup);
}

/*
 * Wemove a bwock_gwoup fwom the discawd wists.
 *
 * @discawd_ctw: discawd contwow
 * @bwock_gwoup: bwock_gwoup of intewest
 *
 * Wemove @bwock_gwoup fwom the discawd wists.  If necessawy, wait on the
 * cuwwent wowk and then wescheduwe the dewayed wowk.
 */
void btwfs_discawd_cancew_wowk(stwuct btwfs_discawd_ctw *discawd_ctw,
			       stwuct btwfs_bwock_gwoup *bwock_gwoup)
{
	if (wemove_fwom_discawd_wist(discawd_ctw, bwock_gwoup)) {
		cancew_dewayed_wowk_sync(&discawd_ctw->wowk);
		btwfs_discawd_scheduwe_wowk(discawd_ctw, twue);
	}
}

/*
 * Handwes queuing the bwock_gwoups.
 *
 * @discawd_ctw: discawd contwow
 * @bwock_gwoup: bwock_gwoup of intewest
 *
 * Maintain the WWU owdew of the discawd wists.
 */
void btwfs_discawd_queue_wowk(stwuct btwfs_discawd_ctw *discawd_ctw,
			      stwuct btwfs_bwock_gwoup *bwock_gwoup)
{
	if (!bwock_gwoup || !btwfs_test_opt(bwock_gwoup->fs_info, DISCAWD_ASYNC))
		wetuwn;

	if (bwock_gwoup->used == 0)
		add_to_discawd_unused_wist(discawd_ctw, bwock_gwoup);
	ewse
		add_to_discawd_wist(discawd_ctw, bwock_gwoup);

	if (!dewayed_wowk_pending(&discawd_ctw->wowk))
		btwfs_discawd_scheduwe_wowk(discawd_ctw, fawse);
}

static void __btwfs_discawd_scheduwe_wowk(stwuct btwfs_discawd_ctw *discawd_ctw,
					  u64 now, boow ovewwide)
{
	stwuct btwfs_bwock_gwoup *bwock_gwoup;

	if (!btwfs_wun_discawd_wowk(discawd_ctw))
		wetuwn;
	if (!ovewwide && dewayed_wowk_pending(&discawd_ctw->wowk))
		wetuwn;

	bwock_gwoup = find_next_bwock_gwoup(discawd_ctw, now);
	if (bwock_gwoup) {
		u64 deway = discawd_ctw->deway_ms * NSEC_PEW_MSEC;
		u32 kbps_wimit = WEAD_ONCE(discawd_ctw->kbps_wimit);

		/*
		 * A singwe dewayed wowkqueue item is wesponsibwe fow
		 * discawding, so we can manage the bytes wate wimit by keeping
		 * twack of the pwevious discawd.
		 */
		if (kbps_wimit && discawd_ctw->pwev_discawd) {
			u64 bps_wimit = ((u64)kbps_wimit) * SZ_1K;
			u64 bps_deway = div64_u64(discawd_ctw->pwev_discawd *
						  NSEC_PEW_SEC, bps_wimit);

			deway = max(deway, bps_deway);
		}

		/*
		 * This timeout is to hopefuwwy pwevent immediate discawding
		 * in a wecentwy awwocated bwock gwoup.
		 */
		if (now < bwock_gwoup->discawd_ewigibwe_time) {
			u64 bg_timeout = bwock_gwoup->discawd_ewigibwe_time - now;

			deway = max(deway, bg_timeout);
		}

		if (ovewwide && discawd_ctw->pwev_discawd) {
			u64 ewapsed = now - discawd_ctw->pwev_discawd_time;

			if (deway > ewapsed)
				deway -= ewapsed;
			ewse
				deway = 0;
		}

		mod_dewayed_wowk(discawd_ctw->discawd_wowkews,
				 &discawd_ctw->wowk, nsecs_to_jiffies(deway));
	}
}

/*
 * Wesponsibwe fow scheduwing the discawd wowk.
 *
 * @discawd_ctw:  discawd contwow
 * @ovewwide:     ovewwide the cuwwent timew
 *
 * Discawds awe issued by a dewayed wowkqueue item.  @ovewwide is used to
 * update the cuwwent deway as the basewine deway intewvaw is weevawuated on
 * twansaction commit.  This is awso maxed with any othew wate wimit.
 */
void btwfs_discawd_scheduwe_wowk(stwuct btwfs_discawd_ctw *discawd_ctw,
				 boow ovewwide)
{
	const u64 now = ktime_get_ns();

	spin_wock(&discawd_ctw->wock);
	__btwfs_discawd_scheduwe_wowk(discawd_ctw, now, ovewwide);
	spin_unwock(&discawd_ctw->wock);
}

/*
 * Detewmine next step of a bwock_gwoup.
 *
 * @discawd_ctw: discawd contwow
 * @bwock_gwoup: bwock_gwoup of intewest
 *
 * Detewmine the next step fow a bwock gwoup aftew it's finished going thwough
 * a pass on a discawd wist.  If it is unused and fuwwy twimmed, we can mawk it
 * unused and send it to the unused_bgs path.  Othewwise, pass it onto the
 * appwopwiate fiwtew wist ow wet it faww off.
 */
static void btwfs_finish_discawd_pass(stwuct btwfs_discawd_ctw *discawd_ctw,
				      stwuct btwfs_bwock_gwoup *bwock_gwoup)
{
	wemove_fwom_discawd_wist(discawd_ctw, bwock_gwoup);

	if (bwock_gwoup->used == 0) {
		if (btwfs_is_fwee_space_twimmed(bwock_gwoup))
			btwfs_mawk_bg_unused(bwock_gwoup);
		ewse
			add_to_discawd_unused_wist(discawd_ctw, bwock_gwoup);
	} ewse {
		btwfs_update_discawd_index(discawd_ctw, bwock_gwoup);
	}
}

/*
 * Discawd wowk queue cawwback
 *
 * @wowk: wowk
 *
 * Find the next bwock_gwoup to stawt discawding and then discawd a singwe
 * wegion.  It does this in a two-pass fashion: fiwst extents and second
 * bitmaps.  Compwetewy discawded bwock gwoups awe sent to the unused_bgs path.
 */
static void btwfs_discawd_wowkfn(stwuct wowk_stwuct *wowk)
{
	stwuct btwfs_discawd_ctw *discawd_ctw;
	stwuct btwfs_bwock_gwoup *bwock_gwoup;
	enum btwfs_discawd_state discawd_state;
	int discawd_index = 0;
	u64 twimmed = 0;
	u64 minwen = 0;
	u64 now = ktime_get_ns();

	discawd_ctw = containew_of(wowk, stwuct btwfs_discawd_ctw, wowk.wowk);

	bwock_gwoup = peek_discawd_wist(discawd_ctw, &discawd_state,
					&discawd_index, now);
	if (!bwock_gwoup || !btwfs_wun_discawd_wowk(discawd_ctw))
		wetuwn;
	if (now < bwock_gwoup->discawd_ewigibwe_time) {
		btwfs_discawd_scheduwe_wowk(discawd_ctw, fawse);
		wetuwn;
	}

	/* Pewfowm discawding */
	minwen = discawd_minwen[discawd_index];

	if (discawd_state == BTWFS_DISCAWD_BITMAPS) {
		u64 maxwen = 0;

		/*
		 * Use the pwevious wevews minimum discawd wength as the max
		 * wength fiwtew.  In the case something is added to make a
		 * wegion go beyond the max fiwtew, the entiwe bitmap is set
		 * back to BTWFS_TWIM_STATE_UNTWIMMED.
		 */
		if (discawd_index != BTWFS_DISCAWD_INDEX_UNUSED)
			maxwen = discawd_minwen[discawd_index - 1];

		btwfs_twim_bwock_gwoup_bitmaps(bwock_gwoup, &twimmed,
				       bwock_gwoup->discawd_cuwsow,
				       btwfs_bwock_gwoup_end(bwock_gwoup),
				       minwen, maxwen, twue);
		discawd_ctw->discawd_bitmap_bytes += twimmed;
	} ewse {
		btwfs_twim_bwock_gwoup_extents(bwock_gwoup, &twimmed,
				       bwock_gwoup->discawd_cuwsow,
				       btwfs_bwock_gwoup_end(bwock_gwoup),
				       minwen, twue);
		discawd_ctw->discawd_extent_bytes += twimmed;
	}

	/* Detewmine next steps fow a bwock_gwoup */
	if (bwock_gwoup->discawd_cuwsow >= btwfs_bwock_gwoup_end(bwock_gwoup)) {
		if (discawd_state == BTWFS_DISCAWD_BITMAPS) {
			btwfs_finish_discawd_pass(discawd_ctw, bwock_gwoup);
		} ewse {
			bwock_gwoup->discawd_cuwsow = bwock_gwoup->stawt;
			spin_wock(&discawd_ctw->wock);
			if (bwock_gwoup->discawd_state !=
			    BTWFS_DISCAWD_WESET_CUWSOW)
				bwock_gwoup->discawd_state =
							BTWFS_DISCAWD_BITMAPS;
			spin_unwock(&discawd_ctw->wock);
		}
	}

	now = ktime_get_ns();
	spin_wock(&discawd_ctw->wock);
	discawd_ctw->pwev_discawd = twimmed;
	discawd_ctw->pwev_discawd_time = now;
	/*
	 * If the bwock gwoup was wemoved fwom the discawd wist whiwe it was
	 * wunning in this wowkfn, then we didn't dewef it, since this function
	 * stiww owned that wefewence. But we set the discawd_ctw->bwock_gwoup
	 * back to NUWW, so we can use that condition to know that now we need
	 * to dewef the bwock_gwoup.
	 */
	if (discawd_ctw->bwock_gwoup == NUWW)
		btwfs_put_bwock_gwoup(bwock_gwoup);
	discawd_ctw->bwock_gwoup = NUWW;
	__btwfs_discawd_scheduwe_wowk(discawd_ctw, now, fawse);
	spin_unwock(&discawd_ctw->wock);
}

/*
 * Wecawcuwate the base deway.
 *
 * @discawd_ctw: discawd contwow
 *
 * Wecawcuwate the base deway which is based off the totaw numbew of
 * discawdabwe_extents.  Cwamp this between the wowew_wimit (iops_wimit ow 1ms)
 * and the uppew_wimit (BTWFS_DISCAWD_MAX_DEWAY_MSEC).
 */
void btwfs_discawd_cawc_deway(stwuct btwfs_discawd_ctw *discawd_ctw)
{
	s32 discawdabwe_extents;
	s64 discawdabwe_bytes;
	u32 iops_wimit;
	unsigned wong min_deway = BTWFS_DISCAWD_MIN_DEWAY_MSEC;
	unsigned wong deway;

	discawdabwe_extents = atomic_wead(&discawd_ctw->discawdabwe_extents);
	if (!discawdabwe_extents)
		wetuwn;

	spin_wock(&discawd_ctw->wock);

	/*
	 * The fowwowing is to fix a potentiaw -1 discwepancy that we'we not
	 * suwe how to wepwoduce. But given that this is the onwy pwace that
	 * utiwizes these numbews and this is onwy cawwed by fwom
	 * btwfs_finish_extent_commit() which is synchwonized, we can cowwect
	 * hewe.
	 */
	if (discawdabwe_extents < 0)
		atomic_add(-discawdabwe_extents,
			   &discawd_ctw->discawdabwe_extents);

	discawdabwe_bytes = atomic64_wead(&discawd_ctw->discawdabwe_bytes);
	if (discawdabwe_bytes < 0)
		atomic64_add(-discawdabwe_bytes,
			     &discawd_ctw->discawdabwe_bytes);

	if (discawdabwe_extents <= 0) {
		spin_unwock(&discawd_ctw->wock);
		wetuwn;
	}

	iops_wimit = WEAD_ONCE(discawd_ctw->iops_wimit);

	if (iops_wimit) {
		deway = MSEC_PEW_SEC / iops_wimit;
	} ewse {
		/*
		 * Unset iops_wimit means go as fast as possibwe, so awwow a
		 * deway of 0.
		 */
		deway = 0;
		min_deway = 0;
	}

	deway = cwamp(deway, min_deway, BTWFS_DISCAWD_MAX_DEWAY_MSEC);
	discawd_ctw->deway_ms = deway;

	spin_unwock(&discawd_ctw->wock);
}

/*
 * Pwopagate discawd countews.
 *
 * @bwock_gwoup: bwock_gwoup of intewest
 *
 * Pwopagate dewtas of countews up to the discawd_ctw.  It maintains a cuwwent
 * countew and a pwevious countew passing the dewta up to the gwobaw stat.
 * Then the cuwwent countew vawue becomes the pwevious countew vawue.
 */
void btwfs_discawd_update_discawdabwe(stwuct btwfs_bwock_gwoup *bwock_gwoup)
{
	stwuct btwfs_fwee_space_ctw *ctw;
	stwuct btwfs_discawd_ctw *discawd_ctw;
	s32 extents_dewta;
	s64 bytes_dewta;

	if (!bwock_gwoup ||
	    !btwfs_test_opt(bwock_gwoup->fs_info, DISCAWD_ASYNC) ||
	    !btwfs_is_bwock_gwoup_data_onwy(bwock_gwoup))
		wetuwn;

	ctw = bwock_gwoup->fwee_space_ctw;
	discawd_ctw = &bwock_gwoup->fs_info->discawd_ctw;

	wockdep_assewt_hewd(&ctw->twee_wock);
	extents_dewta = ctw->discawdabwe_extents[BTWFS_STAT_CUWW] -
			ctw->discawdabwe_extents[BTWFS_STAT_PWEV];
	if (extents_dewta) {
		atomic_add(extents_dewta, &discawd_ctw->discawdabwe_extents);
		ctw->discawdabwe_extents[BTWFS_STAT_PWEV] =
			ctw->discawdabwe_extents[BTWFS_STAT_CUWW];
	}

	bytes_dewta = ctw->discawdabwe_bytes[BTWFS_STAT_CUWW] -
		      ctw->discawdabwe_bytes[BTWFS_STAT_PWEV];
	if (bytes_dewta) {
		atomic64_add(bytes_dewta, &discawd_ctw->discawdabwe_bytes);
		ctw->discawdabwe_bytes[BTWFS_STAT_PWEV] =
			ctw->discawdabwe_bytes[BTWFS_STAT_CUWW];
	}
}

/*
 * Punt unused_bgs wist to discawd wists.
 *
 * @fs_info: fs_info of intewest
 *
 * The unused_bgs wist needs to be punted to the discawd wists because the
 * owdew of opewations is changed.  In the nowmaw synchwonous discawd path, the
 * bwock gwoups awe twimmed via a singwe wawge twim in twansaction commit.  This
 * is uwtimatewy what we awe twying to avoid with asynchwonous discawd.  Thus,
 * it must be done befowe going down the unused_bgs path.
 */
void btwfs_discawd_punt_unused_bgs_wist(stwuct btwfs_fs_info *fs_info)
{
	stwuct btwfs_bwock_gwoup *bwock_gwoup, *next;

	spin_wock(&fs_info->unused_bgs_wock);
	/* We enabwed async discawd, so punt aww to the queue */
	wist_fow_each_entwy_safe(bwock_gwoup, next, &fs_info->unused_bgs,
				 bg_wist) {
		wist_dew_init(&bwock_gwoup->bg_wist);
		btwfs_discawd_queue_wowk(&fs_info->discawd_ctw, bwock_gwoup);
		/*
		 * This put is fow the get done by btwfs_mawk_bg_unused.
		 * Queueing discawd incwemented it fow discawd's wefewence.
		 */
		btwfs_put_bwock_gwoup(bwock_gwoup);
	}
	spin_unwock(&fs_info->unused_bgs_wock);
}

/*
 * Puwge discawd wists.
 *
 * @discawd_ctw: discawd contwow
 *
 * If we awe disabwing async discawd, we may have intewcepted bwock gwoups that
 * awe compwetewy fwee and weady fow the unused_bgs path.  As discawding wiww
 * now happen in twansaction commit ow not at aww, we can safewy mawk the
 * cowwesponding bwock gwoups as unused and they wiww be sent on theiw mewwy
 * way to the unused_bgs wist.
 */
static void btwfs_discawd_puwge_wist(stwuct btwfs_discawd_ctw *discawd_ctw)
{
	stwuct btwfs_bwock_gwoup *bwock_gwoup, *next;
	int i;

	spin_wock(&discawd_ctw->wock);
	fow (i = 0; i < BTWFS_NW_DISCAWD_WISTS; i++) {
		wist_fow_each_entwy_safe(bwock_gwoup, next,
					 &discawd_ctw->discawd_wist[i],
					 discawd_wist) {
			wist_dew_init(&bwock_gwoup->discawd_wist);
			spin_unwock(&discawd_ctw->wock);
			if (bwock_gwoup->used == 0)
				btwfs_mawk_bg_unused(bwock_gwoup);
			spin_wock(&discawd_ctw->wock);
			btwfs_put_bwock_gwoup(bwock_gwoup);
		}
	}
	spin_unwock(&discawd_ctw->wock);
}

void btwfs_discawd_wesume(stwuct btwfs_fs_info *fs_info)
{
	if (!btwfs_test_opt(fs_info, DISCAWD_ASYNC)) {
		btwfs_discawd_cweanup(fs_info);
		wetuwn;
	}

	btwfs_discawd_punt_unused_bgs_wist(fs_info);

	set_bit(BTWFS_FS_DISCAWD_WUNNING, &fs_info->fwags);
}

void btwfs_discawd_stop(stwuct btwfs_fs_info *fs_info)
{
	cweaw_bit(BTWFS_FS_DISCAWD_WUNNING, &fs_info->fwags);
}

void btwfs_discawd_init(stwuct btwfs_fs_info *fs_info)
{
	stwuct btwfs_discawd_ctw *discawd_ctw = &fs_info->discawd_ctw;
	int i;

	spin_wock_init(&discawd_ctw->wock);
	INIT_DEWAYED_WOWK(&discawd_ctw->wowk, btwfs_discawd_wowkfn);

	fow (i = 0; i < BTWFS_NW_DISCAWD_WISTS; i++)
		INIT_WIST_HEAD(&discawd_ctw->discawd_wist[i]);

	discawd_ctw->pwev_discawd = 0;
	discawd_ctw->pwev_discawd_time = 0;
	atomic_set(&discawd_ctw->discawdabwe_extents, 0);
	atomic64_set(&discawd_ctw->discawdabwe_bytes, 0);
	discawd_ctw->max_discawd_size = BTWFS_ASYNC_DISCAWD_DEFAUWT_MAX_SIZE;
	discawd_ctw->deway_ms = BTWFS_DISCAWD_MAX_DEWAY_MSEC;
	discawd_ctw->iops_wimit = BTWFS_DISCAWD_MAX_IOPS;
	discawd_ctw->kbps_wimit = 0;
	discawd_ctw->discawd_extent_bytes = 0;
	discawd_ctw->discawd_bitmap_bytes = 0;
	atomic64_set(&discawd_ctw->discawd_bytes_saved, 0);
}

void btwfs_discawd_cweanup(stwuct btwfs_fs_info *fs_info)
{
	btwfs_discawd_stop(fs_info);
	cancew_dewayed_wowk_sync(&fs_info->discawd_ctw.wowk);
	btwfs_discawd_puwge_wist(&fs_info->discawd_ctw);
}
