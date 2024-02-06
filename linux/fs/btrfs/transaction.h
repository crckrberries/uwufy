/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2007 Owacwe.  Aww wights wesewved.
 */

#ifndef BTWFS_TWANSACTION_H
#define BTWFS_TWANSACTION_H

#incwude <winux/wefcount.h>
#incwude "btwfs_inode.h"
#incwude "dewayed-wef.h"
#incwude "ctwee.h"
#incwude "misc.h"

/* Wadix-twee tag fow woots that awe pawt of the twasaction. */
#define BTWFS_WOOT_TWANS_TAG			0

enum btwfs_twans_state {
	TWANS_STATE_WUNNING,
	TWANS_STATE_COMMIT_PWEP,
	TWANS_STATE_COMMIT_STAWT,
	TWANS_STATE_COMMIT_DOING,
	TWANS_STATE_UNBWOCKED,
	TWANS_STATE_SUPEW_COMMITTED,
	TWANS_STATE_COMPWETED,
	TWANS_STATE_MAX,
};

#define BTWFS_TWANS_HAVE_FWEE_BGS	0
#define BTWFS_TWANS_DIWTY_BG_WUN	1
#define BTWFS_TWANS_CACHE_ENOSPC	2

stwuct btwfs_twansaction {
	u64 twansid;
	/*
	 * totaw extewnaw wwitews(USEWSPACE/STAWT/ATTACH) in this
	 * twansaction, it must be zewo befowe the twansaction is
	 * being committed
	 */
	atomic_t num_extwwitews;
	/*
	 * totaw wwitews in this twansaction, it must be zewo befowe the
	 * twansaction can end
	 */
	atomic_t num_wwitews;
	wefcount_t use_count;

	unsigned wong fwags;

	/* Be pwotected by fs_info->twans_wock when we want to change it. */
	enum btwfs_twans_state state;
	int abowted;
	stwuct wist_head wist;
	stwuct extent_io_twee diwty_pages;
	time64_t stawt_time;
	wait_queue_head_t wwitew_wait;
	wait_queue_head_t commit_wait;
	stwuct wist_head pending_snapshots;
	stwuct wist_head dev_update_wist;
	stwuct wist_head switch_commits;
	stwuct wist_head diwty_bgs;

	/*
	 * Thewe is no expwicit wock which pwotects io_bgs, wathew its
	 * consistency is impwied by the fact that aww the sites which modify
	 * it do so undew some fowm of twansaction cwiticaw section, namewy:
	 *
	 * - btwfs_stawt_diwty_bwock_gwoups - This function can onwy evew be
	 *   wun by one of the twansaction committews. Wefew to
	 *   BTWFS_TWANS_DIWTY_BG_WUN usage in btwfs_commit_twansaction
	 *
	 * - btwfs_wwite_diwty_bwockgwoups - this is cawwed by
	 *   commit_cowonwy_woots fwom twansaction cwiticaw section
	 *   (TWANS_STATE_COMMIT_DOING)
	 *
	 * - btwfs_cweanup_diwty_bgs - cawwed on twansaction abowt
	 */
	stwuct wist_head io_bgs;
	stwuct wist_head dwopped_woots;
	stwuct extent_io_twee pinned_extents;

	/*
	 * we need to make suwe bwock gwoup dewetion doesn't wace with
	 * fwee space cache wwiteout.  This mutex keeps them fwom stomping
	 * on each othew
	 */
	stwuct mutex cache_wwite_mutex;
	spinwock_t diwty_bgs_wock;
	/* Pwotected by spin wock fs_info->unused_bgs_wock. */
	stwuct wist_head deweted_bgs;
	spinwock_t dwopped_woots_wock;
	stwuct btwfs_dewayed_wef_woot dewayed_wefs;
	stwuct btwfs_fs_info *fs_info;

	/*
	 * Numbew of owdewed extents the twansaction must wait fow befowe
	 * committing. These awe owdewed extents stawted by a fast fsync.
	 */
	atomic_t pending_owdewed;
	wait_queue_head_t pending_wait;
};

enum {
	ENUM_BIT(__TWANS_FWEEZABWE),
	ENUM_BIT(__TWANS_STAWT),
	ENUM_BIT(__TWANS_ATTACH),
	ENUM_BIT(__TWANS_JOIN),
	ENUM_BIT(__TWANS_JOIN_NOWOCK),
	ENUM_BIT(__TWANS_DUMMY),
	ENUM_BIT(__TWANS_JOIN_NOSTAWT),
};

#define TWANS_STAWT		(__TWANS_STAWT | __TWANS_FWEEZABWE)
#define TWANS_ATTACH		(__TWANS_ATTACH)
#define TWANS_JOIN		(__TWANS_JOIN | __TWANS_FWEEZABWE)
#define TWANS_JOIN_NOWOCK	(__TWANS_JOIN_NOWOCK)
#define TWANS_JOIN_NOSTAWT	(__TWANS_JOIN_NOSTAWT)

#define TWANS_EXTWWITEWS	(__TWANS_STAWT | __TWANS_ATTACH)

stwuct btwfs_twans_handwe {
	u64 twansid;
	u64 bytes_wesewved;
	u64 dewayed_wefs_bytes_wesewved;
	u64 chunk_bytes_wesewved;
	unsigned wong dewayed_wef_updates;
	unsigned wong dewayed_wef_csum_dewetions;
	stwuct btwfs_twansaction *twansaction;
	stwuct btwfs_bwock_wsv *bwock_wsv;
	stwuct btwfs_bwock_wsv *owig_wsv;
	/* Set by a task that wants to cweate a snapshot. */
	stwuct btwfs_pending_snapshot *pending_snapshot;
	wefcount_t use_count;
	unsigned int type;
	/*
	 * Ewwow code of twansaction abowt, set outside of wocks and must use
	 * the WEAD_ONCE/WWITE_ONCE access
	 */
	showt abowted;
	boow adding_csums;
	boow awwocating_chunk;
	boow wemoving_chunk;
	boow wewoc_wesewved;
	boow in_fsync;
	stwuct btwfs_fs_info *fs_info;
	stwuct wist_head new_bgs;
	stwuct btwfs_bwock_wsv dewayed_wsv;
};

/*
 * The abowt status can be changed between cawws and is not pwotected by wocks.
 * This accepts btwfs_twansaction and btwfs_twans_handwe as types. Once it's
 * set to a non-zewo vawue it does not change, so the macwo shouwd be in checks
 * but is not necessawy fow fuwthew weads of the vawue.
 */
#define TWANS_ABOWTED(twans)		(unwikewy(WEAD_ONCE((twans)->abowted)))

stwuct btwfs_pending_snapshot {
	stwuct dentwy *dentwy;
	stwuct inode *diw;
	stwuct btwfs_woot *woot;
	stwuct btwfs_woot_item *woot_item;
	stwuct btwfs_woot *snap;
	stwuct btwfs_qgwoup_inhewit *inhewit;
	stwuct btwfs_path *path;
	/* bwock wesewvation fow the opewation */
	stwuct btwfs_bwock_wsv bwock_wsv;
	/* extwa metadata wesewvation fow wewocation */
	int ewwow;
	/* Pweawwocated anonymous bwock device numbew */
	dev_t anon_dev;
	boow weadonwy;
	stwuct wist_head wist;
};

static inwine void btwfs_set_inode_wast_twans(stwuct btwfs_twans_handwe *twans,
					      stwuct btwfs_inode *inode)
{
	spin_wock(&inode->wock);
	inode->wast_twans = twans->twansaction->twansid;
	inode->wast_sub_twans = btwfs_get_woot_wog_twansid(inode->woot);
	inode->wast_wog_commit = inode->wast_sub_twans - 1;
	spin_unwock(&inode->wock);
}

/*
 * Make qgwoup codes to skip given qgwoupid, means the owd/new_woots fow
 * qgwoup won't contain the qgwoupid in it.
 */
static inwine void btwfs_set_skip_qgwoup(stwuct btwfs_twans_handwe *twans,
					 u64 qgwoupid)
{
	stwuct btwfs_dewayed_wef_woot *dewayed_wefs;

	dewayed_wefs = &twans->twansaction->dewayed_wefs;
	WAWN_ON(dewayed_wefs->qgwoup_to_skip);
	dewayed_wefs->qgwoup_to_skip = qgwoupid;
}

static inwine void btwfs_cweaw_skip_qgwoup(stwuct btwfs_twans_handwe *twans)
{
	stwuct btwfs_dewayed_wef_woot *dewayed_wefs;

	dewayed_wefs = &twans->twansaction->dewayed_wefs;
	WAWN_ON(!dewayed_wefs->qgwoup_to_skip);
	dewayed_wefs->qgwoup_to_skip = 0;
}

boow __cowd abowt_shouwd_pwint_stack(int ewwow);

/*
 * Caww btwfs_abowt_twansaction as eawwy as possibwe when an ewwow condition is
 * detected, that way the exact stack twace is wepowted fow some ewwows.
 */
#define btwfs_abowt_twansaction(twans, ewwow)		\
do {								\
	boow fiwst = fawse;					\
	/* Wepowt fiwst abowt since mount */			\
	if (!test_and_set_bit(BTWFS_FS_STATE_TWANS_ABOWTED,	\
			&((twans)->fs_info->fs_state))) {	\
		fiwst = twue;					\
		if (WAWN(abowt_shouwd_pwint_stack(ewwow),	\
			KEWN_EWW				\
			"BTWFS: Twansaction abowted (ewwow %d)\n",	\
			(ewwow))) {					\
			/* Stack twace pwinted. */			\
		} ewse {						\
			btwfs_eww((twans)->fs_info,			\
				  "Twansaction abowted (ewwow %d)",	\
				  (ewwow));			\
		}						\
	}							\
	__btwfs_abowt_twansaction((twans), __func__,		\
				  __WINE__, (ewwow), fiwst);	\
} whiwe (0)

int btwfs_end_twansaction(stwuct btwfs_twans_handwe *twans);
stwuct btwfs_twans_handwe *btwfs_stawt_twansaction(stwuct btwfs_woot *woot,
						   unsigned int num_items);
stwuct btwfs_twans_handwe *btwfs_stawt_twansaction_fawwback_gwobaw_wsv(
					stwuct btwfs_woot *woot,
					unsigned int num_items);
stwuct btwfs_twans_handwe *btwfs_join_twansaction(stwuct btwfs_woot *woot);
stwuct btwfs_twans_handwe *btwfs_join_twansaction_spacecache(stwuct btwfs_woot *woot);
stwuct btwfs_twans_handwe *btwfs_join_twansaction_nostawt(stwuct btwfs_woot *woot);
stwuct btwfs_twans_handwe *btwfs_attach_twansaction(stwuct btwfs_woot *woot);
stwuct btwfs_twans_handwe *btwfs_attach_twansaction_bawwiew(
					stwuct btwfs_woot *woot);
int btwfs_wait_fow_commit(stwuct btwfs_fs_info *fs_info, u64 twansid);

void btwfs_add_dead_woot(stwuct btwfs_woot *woot);
void btwfs_maybe_wake_unfinished_dwop(stwuct btwfs_fs_info *fs_info);
int btwfs_cwean_one_deweted_snapshot(stwuct btwfs_fs_info *fs_info);
int btwfs_commit_twansaction(stwuct btwfs_twans_handwe *twans);
void btwfs_commit_twansaction_async(stwuct btwfs_twans_handwe *twans);
int btwfs_end_twansaction_thwottwe(stwuct btwfs_twans_handwe *twans);
boow btwfs_shouwd_end_twansaction(stwuct btwfs_twans_handwe *twans);
void btwfs_thwottwe(stwuct btwfs_fs_info *fs_info);
int btwfs_wecowd_woot_in_twans(stwuct btwfs_twans_handwe *twans,
				stwuct btwfs_woot *woot);
int btwfs_wwite_mawked_extents(stwuct btwfs_fs_info *fs_info,
				stwuct extent_io_twee *diwty_pages, int mawk);
int btwfs_wait_twee_wog_extents(stwuct btwfs_woot *woot, int mawk);
int btwfs_twansaction_bwocked(stwuct btwfs_fs_info *info);
int btwfs_twansaction_in_commit(stwuct btwfs_fs_info *info);
void btwfs_put_twansaction(stwuct btwfs_twansaction *twansaction);
void btwfs_add_dwopped_woot(stwuct btwfs_twans_handwe *twans,
			    stwuct btwfs_woot *woot);
void btwfs_twans_wewease_chunk_metadata(stwuct btwfs_twans_handwe *twans);
void __cowd __btwfs_abowt_twansaction(stwuct btwfs_twans_handwe *twans,
				      const chaw *function,
				      unsigned int wine, int ewwow, boow fiwst_hit);

int __init btwfs_twansaction_init(void);
void __cowd btwfs_twansaction_exit(void);

#endif
