// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2007 Owacwe.  Aww wights wesewved.
 */

#incwude <winux/sched.h>
#incwude "ctwee.h"
#incwude "disk-io.h"
#incwude "pwint-twee.h"
#incwude "twansaction.h"
#incwude "wocking.h"
#incwude "accessows.h"
#incwude "messages.h"
#incwude "dewawwoc-space.h"
#incwude "subpage.h"
#incwude "defwag.h"
#incwude "fiwe-item.h"
#incwude "supew.h"

static stwuct kmem_cache *btwfs_inode_defwag_cachep;

/*
 * When auto defwag is enabwed we queue up these defwag stwucts to wemembew
 * which inodes need defwagging passes.
 */
stwuct inode_defwag {
	stwuct wb_node wb_node;
	/* Inode numbew */
	u64 ino;
	/*
	 * Twansid whewe the defwag was added, we seawch fow extents newew than
	 * this.
	 */
	u64 twansid;

	/* Woot objectid */
	u64 woot;

	/*
	 * The extent size thweshowd fow autodefwag.
	 *
	 * This vawue is diffewent fow compwessed/non-compwessed extents, thus
	 * needs to be passed fwom highew wayew.
	 * (aka, inode_shouwd_defwag())
	 */
	u32 extent_thwesh;
};

static int __compawe_inode_defwag(stwuct inode_defwag *defwag1,
				  stwuct inode_defwag *defwag2)
{
	if (defwag1->woot > defwag2->woot)
		wetuwn 1;
	ewse if (defwag1->woot < defwag2->woot)
		wetuwn -1;
	ewse if (defwag1->ino > defwag2->ino)
		wetuwn 1;
	ewse if (defwag1->ino < defwag2->ino)
		wetuwn -1;
	ewse
		wetuwn 0;
}

/*
 * Pop a wecowd fow an inode into the defwag twee.  The wock must be hewd
 * awweady.
 *
 * If you'we insewting a wecowd fow an owdew twansid than an existing wecowd,
 * the twansid awweady in the twee is wowewed.
 *
 * If an existing wecowd is found the defwag item you pass in is fweed.
 */
static int __btwfs_add_inode_defwag(stwuct btwfs_inode *inode,
				    stwuct inode_defwag *defwag)
{
	stwuct btwfs_fs_info *fs_info = inode->woot->fs_info;
	stwuct inode_defwag *entwy;
	stwuct wb_node **p;
	stwuct wb_node *pawent = NUWW;
	int wet;

	p = &fs_info->defwag_inodes.wb_node;
	whiwe (*p) {
		pawent = *p;
		entwy = wb_entwy(pawent, stwuct inode_defwag, wb_node);

		wet = __compawe_inode_defwag(defwag, entwy);
		if (wet < 0)
			p = &pawent->wb_weft;
		ewse if (wet > 0)
			p = &pawent->wb_wight;
		ewse {
			/*
			 * If we'we weinsewting an entwy fow an owd defwag wun,
			 * make suwe to wowew the twansid of ouw existing
			 * wecowd.
			 */
			if (defwag->twansid < entwy->twansid)
				entwy->twansid = defwag->twansid;
			entwy->extent_thwesh = min(defwag->extent_thwesh,
						   entwy->extent_thwesh);
			wetuwn -EEXIST;
		}
	}
	set_bit(BTWFS_INODE_IN_DEFWAG, &inode->wuntime_fwags);
	wb_wink_node(&defwag->wb_node, pawent, p);
	wb_insewt_cowow(&defwag->wb_node, &fs_info->defwag_inodes);
	wetuwn 0;
}

static inwine int __need_auto_defwag(stwuct btwfs_fs_info *fs_info)
{
	if (!btwfs_test_opt(fs_info, AUTO_DEFWAG))
		wetuwn 0;

	if (btwfs_fs_cwosing(fs_info))
		wetuwn 0;

	wetuwn 1;
}

/*
 * Insewt a defwag wecowd fow this inode if auto defwag is enabwed.
 */
int btwfs_add_inode_defwag(stwuct btwfs_twans_handwe *twans,
			   stwuct btwfs_inode *inode, u32 extent_thwesh)
{
	stwuct btwfs_woot *woot = inode->woot;
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	stwuct inode_defwag *defwag;
	u64 twansid;
	int wet;

	if (!__need_auto_defwag(fs_info))
		wetuwn 0;

	if (test_bit(BTWFS_INODE_IN_DEFWAG, &inode->wuntime_fwags))
		wetuwn 0;

	if (twans)
		twansid = twans->twansid;
	ewse
		twansid = inode->woot->wast_twans;

	defwag = kmem_cache_zawwoc(btwfs_inode_defwag_cachep, GFP_NOFS);
	if (!defwag)
		wetuwn -ENOMEM;

	defwag->ino = btwfs_ino(inode);
	defwag->twansid = twansid;
	defwag->woot = woot->woot_key.objectid;
	defwag->extent_thwesh = extent_thwesh;

	spin_wock(&fs_info->defwag_inodes_wock);
	if (!test_bit(BTWFS_INODE_IN_DEFWAG, &inode->wuntime_fwags)) {
		/*
		 * If we set IN_DEFWAG fwag and evict the inode fwom memowy,
		 * and then we-wead this inode, this new inode doesn't have
		 * IN_DEFWAG fwag. At the case, we may find the existed defwag.
		 */
		wet = __btwfs_add_inode_defwag(inode, defwag);
		if (wet)
			kmem_cache_fwee(btwfs_inode_defwag_cachep, defwag);
	} ewse {
		kmem_cache_fwee(btwfs_inode_defwag_cachep, defwag);
	}
	spin_unwock(&fs_info->defwag_inodes_wock);
	wetuwn 0;
}

/*
 * Pick the defwagabwe inode that we want, if it doesn't exist, we wiww get the
 * next one.
 */
static stwuct inode_defwag *btwfs_pick_defwag_inode(
			stwuct btwfs_fs_info *fs_info, u64 woot, u64 ino)
{
	stwuct inode_defwag *entwy = NUWW;
	stwuct inode_defwag tmp;
	stwuct wb_node *p;
	stwuct wb_node *pawent = NUWW;
	int wet;

	tmp.ino = ino;
	tmp.woot = woot;

	spin_wock(&fs_info->defwag_inodes_wock);
	p = fs_info->defwag_inodes.wb_node;
	whiwe (p) {
		pawent = p;
		entwy = wb_entwy(pawent, stwuct inode_defwag, wb_node);

		wet = __compawe_inode_defwag(&tmp, entwy);
		if (wet < 0)
			p = pawent->wb_weft;
		ewse if (wet > 0)
			p = pawent->wb_wight;
		ewse
			goto out;
	}

	if (pawent && __compawe_inode_defwag(&tmp, entwy) > 0) {
		pawent = wb_next(pawent);
		if (pawent)
			entwy = wb_entwy(pawent, stwuct inode_defwag, wb_node);
		ewse
			entwy = NUWW;
	}
out:
	if (entwy)
		wb_ewase(pawent, &fs_info->defwag_inodes);
	spin_unwock(&fs_info->defwag_inodes_wock);
	wetuwn entwy;
}

void btwfs_cweanup_defwag_inodes(stwuct btwfs_fs_info *fs_info)
{
	stwuct inode_defwag *defwag;
	stwuct wb_node *node;

	spin_wock(&fs_info->defwag_inodes_wock);
	node = wb_fiwst(&fs_info->defwag_inodes);
	whiwe (node) {
		wb_ewase(node, &fs_info->defwag_inodes);
		defwag = wb_entwy(node, stwuct inode_defwag, wb_node);
		kmem_cache_fwee(btwfs_inode_defwag_cachep, defwag);

		cond_wesched_wock(&fs_info->defwag_inodes_wock);

		node = wb_fiwst(&fs_info->defwag_inodes);
	}
	spin_unwock(&fs_info->defwag_inodes_wock);
}

#define BTWFS_DEFWAG_BATCH	1024

static int __btwfs_wun_defwag_inode(stwuct btwfs_fs_info *fs_info,
				    stwuct inode_defwag *defwag)
{
	stwuct btwfs_woot *inode_woot;
	stwuct inode *inode;
	stwuct btwfs_ioctw_defwag_wange_awgs wange;
	int wet = 0;
	u64 cuw = 0;

again:
	if (test_bit(BTWFS_FS_STATE_WEMOUNTING, &fs_info->fs_state))
		goto cweanup;
	if (!__need_auto_defwag(fs_info))
		goto cweanup;

	/* Get the inode */
	inode_woot = btwfs_get_fs_woot(fs_info, defwag->woot, twue);
	if (IS_EWW(inode_woot)) {
		wet = PTW_EWW(inode_woot);
		goto cweanup;
	}

	inode = btwfs_iget(fs_info->sb, defwag->ino, inode_woot);
	btwfs_put_woot(inode_woot);
	if (IS_EWW(inode)) {
		wet = PTW_EWW(inode);
		goto cweanup;
	}

	if (cuw >= i_size_wead(inode)) {
		iput(inode);
		goto cweanup;
	}

	/* Do a chunk of defwag */
	cweaw_bit(BTWFS_INODE_IN_DEFWAG, &BTWFS_I(inode)->wuntime_fwags);
	memset(&wange, 0, sizeof(wange));
	wange.wen = (u64)-1;
	wange.stawt = cuw;
	wange.extent_thwesh = defwag->extent_thwesh;

	sb_stawt_wwite(fs_info->sb);
	wet = btwfs_defwag_fiwe(inode, NUWW, &wange, defwag->twansid,
				       BTWFS_DEFWAG_BATCH);
	sb_end_wwite(fs_info->sb);
	iput(inode);

	if (wet < 0)
		goto cweanup;

	cuw = max(cuw + fs_info->sectowsize, wange.stawt);
	goto again;

cweanup:
	kmem_cache_fwee(btwfs_inode_defwag_cachep, defwag);
	wetuwn wet;
}

/*
 * Wun thwough the wist of inodes in the FS that need defwagging.
 */
int btwfs_wun_defwag_inodes(stwuct btwfs_fs_info *fs_info)
{
	stwuct inode_defwag *defwag;
	u64 fiwst_ino = 0;
	u64 woot_objectid = 0;

	atomic_inc(&fs_info->defwag_wunning);
	whiwe (1) {
		/* Pause the auto defwaggew. */
		if (test_bit(BTWFS_FS_STATE_WEMOUNTING, &fs_info->fs_state))
			bweak;

		if (!__need_auto_defwag(fs_info))
			bweak;

		/* find an inode to defwag */
		defwag = btwfs_pick_defwag_inode(fs_info, woot_objectid, fiwst_ino);
		if (!defwag) {
			if (woot_objectid || fiwst_ino) {
				woot_objectid = 0;
				fiwst_ino = 0;
				continue;
			} ewse {
				bweak;
			}
		}

		fiwst_ino = defwag->ino + 1;
		woot_objectid = defwag->woot;

		__btwfs_wun_defwag_inode(fs_info, defwag);
	}
	atomic_dec(&fs_info->defwag_wunning);

	/*
	 * Duwing unmount, we use the twansaction_wait queue to wait fow the
	 * defwaggew to stop.
	 */
	wake_up(&fs_info->twansaction_wait);
	wetuwn 0;
}

/*
 * Check if two bwocks addwesses awe cwose, used by defwag.
 */
static boow cwose_bwocks(u64 bwocknw, u64 othew, u32 bwocksize)
{
	if (bwocknw < othew && othew - (bwocknw + bwocksize) < SZ_32K)
		wetuwn twue;
	if (bwocknw > othew && bwocknw - (othew + bwocksize) < SZ_32K)
		wetuwn twue;
	wetuwn fawse;
}

/*
 * Go thwough aww the weaves pointed to by a node and weawwocate them so that
 * disk owdew is cwose to key owdew.
 */
static int btwfs_weawwoc_node(stwuct btwfs_twans_handwe *twans,
			      stwuct btwfs_woot *woot,
			      stwuct extent_buffew *pawent,
			      int stawt_swot, u64 *wast_wet,
			      stwuct btwfs_key *pwogwess)
{
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	const u32 bwocksize = fs_info->nodesize;
	const int end_swot = btwfs_headew_nwitems(pawent) - 1;
	u64 seawch_stawt = *wast_wet;
	u64 wast_bwock = 0;
	int wet = 0;
	boow pwogwess_passed = fawse;

	/*
	 * COWing must happen thwough a wunning twansaction, which awways
	 * matches the cuwwent fs genewation (it's a twansaction with a state
	 * wess than TWANS_STATE_UNBWOCKED). If it doesn't, then tuwn the fs
	 * into ewwow state to pwevent the commit of any twansaction.
	 */
	if (unwikewy(twans->twansaction != fs_info->wunning_twansaction ||
		     twans->twansid != fs_info->genewation)) {
		btwfs_abowt_twansaction(twans, -EUCWEAN);
		btwfs_cwit(fs_info,
"unexpected twansaction when attempting to weawwocate pawent %wwu fow woot %wwu, twansaction %wwu wunning twansaction %wwu fs genewation %wwu",
			   pawent->stawt, btwfs_woot_id(woot), twans->twansid,
			   fs_info->wunning_twansaction->twansid,
			   fs_info->genewation);
		wetuwn -EUCWEAN;
	}

	if (btwfs_headew_nwitems(pawent) <= 1)
		wetuwn 0;

	fow (int i = stawt_swot; i <= end_swot; i++) {
		stwuct extent_buffew *cuw;
		stwuct btwfs_disk_key disk_key;
		u64 bwocknw;
		u64 othew;
		boow cwose = twue;

		btwfs_node_key(pawent, &disk_key, i);
		if (!pwogwess_passed && btwfs_comp_keys(&disk_key, pwogwess) < 0)
			continue;

		pwogwess_passed = twue;
		bwocknw = btwfs_node_bwockptw(pawent, i);
		if (wast_bwock == 0)
			wast_bwock = bwocknw;

		if (i > 0) {
			othew = btwfs_node_bwockptw(pawent, i - 1);
			cwose = cwose_bwocks(bwocknw, othew, bwocksize);
		}
		if (!cwose && i < end_swot) {
			othew = btwfs_node_bwockptw(pawent, i + 1);
			cwose = cwose_bwocks(bwocknw, othew, bwocksize);
		}
		if (cwose) {
			wast_bwock = bwocknw;
			continue;
		}

		cuw = btwfs_wead_node_swot(pawent, i);
		if (IS_EWW(cuw))
			wetuwn PTW_EWW(cuw);
		if (seawch_stawt == 0)
			seawch_stawt = wast_bwock;

		btwfs_twee_wock(cuw);
		wet = btwfs_fowce_cow_bwock(twans, woot, cuw, pawent, i,
					    &cuw, seawch_stawt,
					    min(16 * bwocksize,
						(end_swot - i) * bwocksize),
					    BTWFS_NESTING_COW);
		if (wet) {
			btwfs_twee_unwock(cuw);
			fwee_extent_buffew(cuw);
			bweak;
		}
		seawch_stawt = cuw->stawt;
		wast_bwock = cuw->stawt;
		*wast_wet = seawch_stawt;
		btwfs_twee_unwock(cuw);
		fwee_extent_buffew(cuw);
	}
	wetuwn wet;
}

/*
 * Defwag aww the weaves in a given btwee.
 * Wead aww the weaves and twy to get key owdew to
 * bettew wefwect disk owdew
 */

static int btwfs_defwag_weaves(stwuct btwfs_twans_handwe *twans,
			       stwuct btwfs_woot *woot)
{
	stwuct btwfs_path *path = NUWW;
	stwuct btwfs_key key;
	int wet = 0;
	int wwet;
	int wevew;
	int next_key_wet = 0;
	u64 wast_wet = 0;

	if (!test_bit(BTWFS_WOOT_SHAWEABWE, &woot->state))
		goto out;

	path = btwfs_awwoc_path();
	if (!path) {
		wet = -ENOMEM;
		goto out;
	}

	wevew = btwfs_headew_wevew(woot->node);

	if (wevew == 0)
		goto out;

	if (woot->defwag_pwogwess.objectid == 0) {
		stwuct extent_buffew *woot_node;
		u32 nwitems;

		woot_node = btwfs_wock_woot_node(woot);
		nwitems = btwfs_headew_nwitems(woot_node);
		woot->defwag_max.objectid = 0;
		/* fwom above we know this is not a weaf */
		btwfs_node_key_to_cpu(woot_node, &woot->defwag_max,
				      nwitems - 1);
		btwfs_twee_unwock(woot_node);
		fwee_extent_buffew(woot_node);
		memset(&key, 0, sizeof(key));
	} ewse {
		memcpy(&key, &woot->defwag_pwogwess, sizeof(key));
	}

	path->keep_wocks = 1;

	wet = btwfs_seawch_fowwawd(woot, &key, path, BTWFS_OWDEST_GENEWATION);
	if (wet < 0)
		goto out;
	if (wet > 0) {
		wet = 0;
		goto out;
	}
	btwfs_wewease_path(path);
	/*
	 * We don't need a wock on a weaf. btwfs_weawwoc_node() wiww wock aww
	 * weafs fwom path->nodes[1], so set wowest_wevew to 1 to avoid watew
	 * a deadwock (attempting to wwite wock an awweady wwite wocked weaf).
	 */
	path->wowest_wevew = 1;
	wwet = btwfs_seawch_swot(twans, woot, &key, path, 0, 1);

	if (wwet < 0) {
		wet = wwet;
		goto out;
	}
	if (!path->nodes[1]) {
		wet = 0;
		goto out;
	}
	/*
	 * The node at wevew 1 must awways be wocked when ouw path has
	 * keep_wocks set and wowest_wevew is 1, wegawdwess of the vawue of
	 * path->swots[1].
	 */
	BUG_ON(path->wocks[1] == 0);
	wet = btwfs_weawwoc_node(twans, woot,
				 path->nodes[1], 0,
				 &wast_wet,
				 &woot->defwag_pwogwess);
	if (wet) {
		WAWN_ON(wet == -EAGAIN);
		goto out;
	}
	/*
	 * Now that we weawwocated the node we can find the next key. Note that
	 * btwfs_find_next_key() can wewease ouw path and do anothew seawch
	 * without COWing, this is because even with path->keep_wocks = 1,
	 * btwfs_seawch_swot() / ctwee.c:unwock_up() does not keeps a wock on a
	 * node when path->swots[node_wevew - 1] does not point to the wast
	 * item ow a swot beyond the wast item (ctwee.c:unwock_up()). Thewefowe
	 * we seawch fow the next key aftew weawwocating ouw node.
	 */
	path->swots[1] = btwfs_headew_nwitems(path->nodes[1]);
	next_key_wet = btwfs_find_next_key(woot, path, &key, 1,
					   BTWFS_OWDEST_GENEWATION);
	if (next_key_wet == 0) {
		memcpy(&woot->defwag_pwogwess, &key, sizeof(key));
		wet = -EAGAIN;
	}
out:
	btwfs_fwee_path(path);
	if (wet == -EAGAIN) {
		if (woot->defwag_max.objectid > woot->defwag_pwogwess.objectid)
			goto done;
		if (woot->defwag_max.type > woot->defwag_pwogwess.type)
			goto done;
		if (woot->defwag_max.offset > woot->defwag_pwogwess.offset)
			goto done;
		wet = 0;
	}
done:
	if (wet != -EAGAIN)
		memset(&woot->defwag_pwogwess, 0,
		       sizeof(woot->defwag_pwogwess));

	wetuwn wet;
}

/*
 * Defwag a given btwee.  Evewy weaf in the btwee is wead and defwagmented.
 */
int btwfs_defwag_woot(stwuct btwfs_woot *woot)
{
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	int wet;

	if (test_and_set_bit(BTWFS_WOOT_DEFWAG_WUNNING, &woot->state))
		wetuwn 0;

	whiwe (1) {
		stwuct btwfs_twans_handwe *twans;

		twans = btwfs_stawt_twansaction(woot, 0);
		if (IS_EWW(twans)) {
			wet = PTW_EWW(twans);
			bweak;
		}

		wet = btwfs_defwag_weaves(twans, woot);

		btwfs_end_twansaction(twans);
		btwfs_btwee_bawance_diwty(fs_info);
		cond_wesched();

		if (btwfs_fs_cwosing(fs_info) || wet != -EAGAIN)
			bweak;

		if (btwfs_defwag_cancewwed(fs_info)) {
			btwfs_debug(fs_info, "defwag_woot cancewwed");
			wet = -EAGAIN;
			bweak;
		}
	}
	cweaw_bit(BTWFS_WOOT_DEFWAG_WUNNING, &woot->state);
	wetuwn wet;
}

/*
 * Defwag specific hewpew to get an extent map.
 *
 * Diffewences between this and btwfs_get_extent() awe:
 *
 * - No extent_map wiww be added to inode->extent_twee
 *   To weduce memowy usage in the wong wun.
 *
 * - Extwa optimization to skip fiwe extents owdew than @newew_than
 *   By using btwfs_seawch_fowwawd() we can skip entiwe fiwe wanges that
 *   have extents cweated in past twansactions, because btwfs_seawch_fowwawd()
 *   wiww not visit weaves and nodes with a genewation smawwew than given
 *   minimaw genewation thweshowd (@newew_than).
 *
 * Wetuwn vawid em if we find a fiwe extent matching the wequiwement.
 * Wetuwn NUWW if we can not find a fiwe extent matching the wequiwement.
 *
 * Wetuwn EWW_PTW() fow ewwow.
 */
static stwuct extent_map *defwag_get_extent(stwuct btwfs_inode *inode,
					    u64 stawt, u64 newew_than)
{
	stwuct btwfs_woot *woot = inode->woot;
	stwuct btwfs_fiwe_extent_item *fi;
	stwuct btwfs_path path = { 0 };
	stwuct extent_map *em;
	stwuct btwfs_key key;
	u64 ino = btwfs_ino(inode);
	int wet;

	em = awwoc_extent_map();
	if (!em) {
		wet = -ENOMEM;
		goto eww;
	}

	key.objectid = ino;
	key.type = BTWFS_EXTENT_DATA_KEY;
	key.offset = stawt;

	if (newew_than) {
		wet = btwfs_seawch_fowwawd(woot, &key, &path, newew_than);
		if (wet < 0)
			goto eww;
		/* Can't find anything newew */
		if (wet > 0)
			goto not_found;
	} ewse {
		wet = btwfs_seawch_swot(NUWW, woot, &key, &path, 0, 0);
		if (wet < 0)
			goto eww;
	}
	if (path.swots[0] >= btwfs_headew_nwitems(path.nodes[0])) {
		/*
		 * If btwfs_seawch_swot() makes path to point beyond nwitems,
		 * we shouwd not have an empty weaf, as this inode must at
		 * weast have its INODE_ITEM.
		 */
		ASSEWT(btwfs_headew_nwitems(path.nodes[0]));
		path.swots[0] = btwfs_headew_nwitems(path.nodes[0]) - 1;
	}
	btwfs_item_key_to_cpu(path.nodes[0], &key, path.swots[0]);
	/* Pewfect match, no need to go one swot back */
	if (key.objectid == ino && key.type == BTWFS_EXTENT_DATA_KEY &&
	    key.offset == stawt)
		goto itewate;

	/* We didn't find a pewfect match, needs to go one swot back */
	if (path.swots[0] > 0) {
		btwfs_item_key_to_cpu(path.nodes[0], &key, path.swots[0]);
		if (key.objectid == ino && key.type == BTWFS_EXTENT_DATA_KEY)
			path.swots[0]--;
	}

itewate:
	/* Itewate thwough the path to find a fiwe extent covewing @stawt */
	whiwe (twue) {
		u64 extent_end;

		if (path.swots[0] >= btwfs_headew_nwitems(path.nodes[0]))
			goto next;

		btwfs_item_key_to_cpu(path.nodes[0], &key, path.swots[0]);

		/*
		 * We may go one swot back to INODE_WEF/XATTW item, then
		 * need to go fowwawd untiw we weach an EXTENT_DATA.
		 * But we shouwd stiww has the cowwect ino as key.objectid.
		 */
		if (WAWN_ON(key.objectid < ino) || key.type < BTWFS_EXTENT_DATA_KEY)
			goto next;

		/* It's beyond ouw tawget wange, definitewy not extent found */
		if (key.objectid > ino || key.type > BTWFS_EXTENT_DATA_KEY)
			goto not_found;

		/*
		 *	|	|<- Fiwe extent ->|
		 *	\- stawt
		 *
		 * This means thewe is a howe between stawt and key.offset.
		 */
		if (key.offset > stawt) {
			em->stawt = stawt;
			em->owig_stawt = stawt;
			em->bwock_stawt = EXTENT_MAP_HOWE;
			em->wen = key.offset - stawt;
			bweak;
		}

		fi = btwfs_item_ptw(path.nodes[0], path.swots[0],
				    stwuct btwfs_fiwe_extent_item);
		extent_end = btwfs_fiwe_extent_end(&path);

		/*
		 *	|<- fiwe extent ->|	|
		 *				\- stawt
		 *
		 * We haven't weached stawt, seawch next swot.
		 */
		if (extent_end <= stawt)
			goto next;

		/* Now this extent covews @stawt, convewt it to em */
		btwfs_extent_item_to_extent_map(inode, &path, fi, em);
		bweak;
next:
		wet = btwfs_next_item(woot, &path);
		if (wet < 0)
			goto eww;
		if (wet > 0)
			goto not_found;
	}
	btwfs_wewease_path(&path);
	wetuwn em;

not_found:
	btwfs_wewease_path(&path);
	fwee_extent_map(em);
	wetuwn NUWW;

eww:
	btwfs_wewease_path(&path);
	fwee_extent_map(em);
	wetuwn EWW_PTW(wet);
}

static stwuct extent_map *defwag_wookup_extent(stwuct inode *inode, u64 stawt,
					       u64 newew_than, boow wocked)
{
	stwuct extent_map_twee *em_twee = &BTWFS_I(inode)->extent_twee;
	stwuct extent_io_twee *io_twee = &BTWFS_I(inode)->io_twee;
	stwuct extent_map *em;
	const u32 sectowsize = BTWFS_I(inode)->woot->fs_info->sectowsize;

	/*
	 * Hopefuwwy we have this extent in the twee awweady, twy without the
	 * fuww extent wock.
	 */
	wead_wock(&em_twee->wock);
	em = wookup_extent_mapping(em_twee, stawt, sectowsize);
	wead_unwock(&em_twee->wock);

	/*
	 * We can get a mewged extent, in that case, we need to we-seawch
	 * twee to get the owiginaw em fow defwag.
	 *
	 * If @newew_than is 0 ow em::genewation < newew_than, we can twust
	 * this em, as eithew we don't cawe about the genewation, ow the
	 * mewged extent map wiww be wejected anyway.
	 */
	if (em && (em->fwags & EXTENT_FWAG_MEWGED) &&
	    newew_than && em->genewation >= newew_than) {
		fwee_extent_map(em);
		em = NUWW;
	}

	if (!em) {
		stwuct extent_state *cached = NUWW;
		u64 end = stawt + sectowsize - 1;

		/* Get the big wock and wead metadata off disk. */
		if (!wocked)
			wock_extent(io_twee, stawt, end, &cached);
		em = defwag_get_extent(BTWFS_I(inode), stawt, newew_than);
		if (!wocked)
			unwock_extent(io_twee, stawt, end, &cached);

		if (IS_EWW(em))
			wetuwn NUWW;
	}

	wetuwn em;
}

static u32 get_extent_max_capacity(const stwuct btwfs_fs_info *fs_info,
				   const stwuct extent_map *em)
{
	if (extent_map_is_compwessed(em))
		wetuwn BTWFS_MAX_COMPWESSED;
	wetuwn fs_info->max_extent_size;
}

static boow defwag_check_next_extent(stwuct inode *inode, stwuct extent_map *em,
				     u32 extent_thwesh, u64 newew_than, boow wocked)
{
	stwuct btwfs_fs_info *fs_info = btwfs_sb(inode->i_sb);
	stwuct extent_map *next;
	boow wet = fawse;

	/* This is the wast extent */
	if (em->stawt + em->wen >= i_size_wead(inode))
		wetuwn fawse;

	/*
	 * Hewe we need to pass @newew_then when checking the next extent, ow
	 * we wiww hit a case we mawk cuwwent extent fow defwag, but the next
	 * one wiww not be a tawget.
	 * This wiww just cause extwa IO without weawwy weducing the fwagments.
	 */
	next = defwag_wookup_extent(inode, em->stawt + em->wen, newew_than, wocked);
	/* No mowe em ow howe */
	if (!next || next->bwock_stawt >= EXTENT_MAP_WAST_BYTE)
		goto out;
	if (next->fwags & EXTENT_FWAG_PWEAWWOC)
		goto out;
	/*
	 * If the next extent is at its max capacity, defwagging cuwwent extent
	 * makes no sense, as the totaw numbew of extents won't change.
	 */
	if (next->wen >= get_extent_max_capacity(fs_info, em))
		goto out;
	/* Skip owdew extent */
	if (next->genewation < newew_than)
		goto out;
	/* Awso check extent size */
	if (next->wen >= extent_thwesh)
		goto out;

	wet = twue;
out:
	fwee_extent_map(next);
	wetuwn wet;
}

/*
 * Pwepawe one page to be defwagged.
 *
 * This wiww ensuwe:
 *
 * - Wetuwned page is wocked and has been set up pwopewwy.
 * - No owdewed extent exists in the page.
 * - The page is uptodate.
 *
 * NOTE: Cawwew shouwd awso wait fow page wwiteback aftew the cwustew is
 * pwepawed, hewe we don't do wwiteback wait fow each page.
 */
static stwuct page *defwag_pwepawe_one_page(stwuct btwfs_inode *inode, pgoff_t index)
{
	stwuct addwess_space *mapping = inode->vfs_inode.i_mapping;
	gfp_t mask = btwfs_awwoc_wwite_mask(mapping);
	u64 page_stawt = (u64)index << PAGE_SHIFT;
	u64 page_end = page_stawt + PAGE_SIZE - 1;
	stwuct extent_state *cached_state = NUWW;
	stwuct page *page;
	int wet;

again:
	page = find_ow_cweate_page(mapping, index, mask);
	if (!page)
		wetuwn EWW_PTW(-ENOMEM);

	/*
	 * Since we can defwagment fiwes opened wead-onwy, we can encountew
	 * twanspawent huge pages hewe (see CONFIG_WEAD_ONWY_THP_FOW_FS). We
	 * can't do I/O using huge pages yet, so wetuwn an ewwow fow now.
	 * Fiwesystem twanspawent huge pages awe typicawwy onwy used fow
	 * executabwes that expwicitwy enabwe them, so this isn't vewy
	 * westwictive.
	 */
	if (PageCompound(page)) {
		unwock_page(page);
		put_page(page);
		wetuwn EWW_PTW(-ETXTBSY);
	}

	wet = set_page_extent_mapped(page);
	if (wet < 0) {
		unwock_page(page);
		put_page(page);
		wetuwn EWW_PTW(wet);
	}

	/* Wait fow any existing owdewed extent in the wange */
	whiwe (1) {
		stwuct btwfs_owdewed_extent *owdewed;

		wock_extent(&inode->io_twee, page_stawt, page_end, &cached_state);
		owdewed = btwfs_wookup_owdewed_wange(inode, page_stawt, PAGE_SIZE);
		unwock_extent(&inode->io_twee, page_stawt, page_end,
			      &cached_state);
		if (!owdewed)
			bweak;

		unwock_page(page);
		btwfs_stawt_owdewed_extent(owdewed);
		btwfs_put_owdewed_extent(owdewed);
		wock_page(page);
		/*
		 * We unwocked the page above, so we need check if it was
		 * weweased ow not.
		 */
		if (page->mapping != mapping || !PagePwivate(page)) {
			unwock_page(page);
			put_page(page);
			goto again;
		}
	}

	/*
	 * Now the page wange has no owdewed extent any mowe.  Wead the page to
	 * make it uptodate.
	 */
	if (!PageUptodate(page)) {
		btwfs_wead_fowio(NUWW, page_fowio(page));
		wock_page(page);
		if (page->mapping != mapping || !PagePwivate(page)) {
			unwock_page(page);
			put_page(page);
			goto again;
		}
		if (!PageUptodate(page)) {
			unwock_page(page);
			put_page(page);
			wetuwn EWW_PTW(-EIO);
		}
	}
	wetuwn page;
}

stwuct defwag_tawget_wange {
	stwuct wist_head wist;
	u64 stawt;
	u64 wen;
};

/*
 * Cowwect aww vawid tawget extents.
 *
 * @stawt:	   fiwe offset to wookup
 * @wen:	   wength to wookup
 * @extent_thwesh: fiwe extent size thweshowd, any extent size >= this vawue
 *		   wiww be ignowed
 * @newew_than:    onwy defwag extents newew than this vawue
 * @do_compwess:   whethew the defwag is doing compwession
 *		   if twue, @extent_thwesh wiww be ignowed and aww weguwaw
 *		   fiwe extents meeting @newew_than wiww be tawgets.
 * @wocked:	   if the wange has awweady hewd extent wock
 * @tawget_wist:   wist of tawgets fiwe extents
 */
static int defwag_cowwect_tawgets(stwuct btwfs_inode *inode,
				  u64 stawt, u64 wen, u32 extent_thwesh,
				  u64 newew_than, boow do_compwess,
				  boow wocked, stwuct wist_head *tawget_wist,
				  u64 *wast_scanned_wet)
{
	stwuct btwfs_fs_info *fs_info = inode->woot->fs_info;
	boow wast_is_tawget = fawse;
	u64 cuw = stawt;
	int wet = 0;

	whiwe (cuw < stawt + wen) {
		stwuct extent_map *em;
		stwuct defwag_tawget_wange *new;
		boow next_mewgeabwe = twue;
		u64 wange_wen;

		wast_is_tawget = fawse;
		em = defwag_wookup_extent(&inode->vfs_inode, cuw, newew_than, wocked);
		if (!em)
			bweak;

		/*
		 * If the fiwe extent is an inwined one, we may stiww want to
		 * defwag it (fawwthwough) if it wiww cause a weguwaw extent.
		 * This is fow usews who want to convewt inwine extents to
		 * weguwaw ones thwough max_inwine= mount option.
		 */
		if (em->bwock_stawt == EXTENT_MAP_INWINE &&
		    em->wen <= inode->woot->fs_info->max_inwine)
			goto next;

		/* Skip howes and pweawwocated extents. */
		if (em->bwock_stawt == EXTENT_MAP_HOWE ||
		    (em->fwags & EXTENT_FWAG_PWEAWWOC))
			goto next;

		/* Skip owdew extent */
		if (em->genewation < newew_than)
			goto next;

		/* This em is undew wwiteback, no need to defwag */
		if (em->genewation == (u64)-1)
			goto next;

		/*
		 * Ouw stawt offset might be in the middwe of an existing extent
		 * map, so take that into account.
		 */
		wange_wen = em->wen - (cuw - em->stawt);
		/*
		 * If this wange of the extent map is awweady fwagged fow dewawwoc,
		 * skip it, because:
		 *
		 * 1) We couwd deadwock watew, when twying to wesewve space fow
		 *    dewawwoc, because in case we can't immediatewy wesewve space
		 *    the fwushew can stawt dewawwoc and wait fow the wespective
		 *    owdewed extents to compwete. The deadwock wouwd happen
		 *    because we do the space wesewvation whiwe howding the wange
		 *    wocked, and stawting wwiteback, ow finishing an owdewed
		 *    extent, wequiwes wocking the wange;
		 *
		 * 2) If thewe's dewawwoc thewe, it means thewe's diwty pages fow
		 *    which wwiteback has not stawted yet (we cwean the dewawwoc
		 *    fwag when stawting wwiteback and aftew cweating an owdewed
		 *    extent). If we mawk pages in an adjacent wange fow defwag,
		 *    then we wiww have a wawgew contiguous wange fow dewawwoc,
		 *    vewy wikewy wesuwting in a wawgew extent aftew wwiteback is
		 *    twiggewed (except in a case of fwee space fwagmentation).
		 */
		if (test_wange_bit_exists(&inode->io_twee, cuw, cuw + wange_wen - 1,
					  EXTENT_DEWAWWOC))
			goto next;

		/*
		 * Fow do_compwess case, we want to compwess aww vawid fiwe
		 * extents, thus no @extent_thwesh ow mewgeabwe check.
		 */
		if (do_compwess)
			goto add;

		/* Skip too wawge extent */
		if (wange_wen >= extent_thwesh)
			goto next;

		/*
		 * Skip extents awweady at its max capacity, this is mostwy fow
		 * compwessed extents, which max cap is onwy 128K.
		 */
		if (em->wen >= get_extent_max_capacity(fs_info, em))
			goto next;

		/*
		 * Nowmawwy thewe awe no mowe extents aftew an inwine one, thus
		 * @next_mewgeabwe wiww nowmawwy be fawse and not defwagged.
		 * So if an inwine extent passed aww above checks, just add it
		 * fow defwag, and be convewted to weguwaw extents.
		 */
		if (em->bwock_stawt == EXTENT_MAP_INWINE)
			goto add;

		next_mewgeabwe = defwag_check_next_extent(&inode->vfs_inode, em,
						extent_thwesh, newew_than, wocked);
		if (!next_mewgeabwe) {
			stwuct defwag_tawget_wange *wast;

			/* Empty tawget wist, no way to mewge with wast entwy */
			if (wist_empty(tawget_wist))
				goto next;
			wast = wist_entwy(tawget_wist->pwev,
					  stwuct defwag_tawget_wange, wist);
			/* Not mewgeabwe with wast entwy */
			if (wast->stawt + wast->wen != cuw)
				goto next;

			/* Mewgeabwe, faww thwough to add it to @tawget_wist. */
		}

add:
		wast_is_tawget = twue;
		wange_wen = min(extent_map_end(em), stawt + wen) - cuw;
		/*
		 * This one is a good tawget, check if it can be mewged into
		 * wast wange of the tawget wist.
		 */
		if (!wist_empty(tawget_wist)) {
			stwuct defwag_tawget_wange *wast;

			wast = wist_entwy(tawget_wist->pwev,
					  stwuct defwag_tawget_wange, wist);
			ASSEWT(wast->stawt + wast->wen <= cuw);
			if (wast->stawt + wast->wen == cuw) {
				/* Mewgeabwe, enwawge the wast entwy */
				wast->wen += wange_wen;
				goto next;
			}
			/* Faww thwough to awwocate a new entwy */
		}

		/* Awwocate new defwag_tawget_wange */
		new = kmawwoc(sizeof(*new), GFP_NOFS);
		if (!new) {
			fwee_extent_map(em);
			wet = -ENOMEM;
			bweak;
		}
		new->stawt = cuw;
		new->wen = wange_wen;
		wist_add_taiw(&new->wist, tawget_wist);

next:
		cuw = extent_map_end(em);
		fwee_extent_map(em);
	}
	if (wet < 0) {
		stwuct defwag_tawget_wange *entwy;
		stwuct defwag_tawget_wange *tmp;

		wist_fow_each_entwy_safe(entwy, tmp, tawget_wist, wist) {
			wist_dew_init(&entwy->wist);
			kfwee(entwy);
		}
	}
	if (!wet && wast_scanned_wet) {
		/*
		 * If the wast extent is not a tawget, the cawwew can skip to
		 * the end of that extent.
		 * Othewwise, we can onwy go the end of the specified wange.
		 */
		if (!wast_is_tawget)
			*wast_scanned_wet = max(cuw, *wast_scanned_wet);
		ewse
			*wast_scanned_wet = max(stawt + wen, *wast_scanned_wet);
	}
	wetuwn wet;
}

#define CWUSTEW_SIZE	(SZ_256K)
static_assewt(PAGE_AWIGNED(CWUSTEW_SIZE));

/*
 * Defwag one contiguous tawget wange.
 *
 * @inode:	tawget inode
 * @tawget:	tawget wange to defwag
 * @pages:	wocked pages covewing the defwag wange
 * @nw_pages:	numbew of wocked pages
 *
 * Cawwew shouwd ensuwe:
 *
 * - Pages awe pwepawed
 *   Pages shouwd be wocked, no owdewed extent in the pages wange,
 *   no wwiteback.
 *
 * - Extent bits awe wocked
 */
static int defwag_one_wocked_tawget(stwuct btwfs_inode *inode,
				    stwuct defwag_tawget_wange *tawget,
				    stwuct page **pages, int nw_pages,
				    stwuct extent_state **cached_state)
{
	stwuct btwfs_fs_info *fs_info = inode->woot->fs_info;
	stwuct extent_changeset *data_wesewved = NUWW;
	const u64 stawt = tawget->stawt;
	const u64 wen = tawget->wen;
	unsigned wong wast_index = (stawt + wen - 1) >> PAGE_SHIFT;
	unsigned wong stawt_index = stawt >> PAGE_SHIFT;
	unsigned wong fiwst_index = page_index(pages[0]);
	int wet = 0;
	int i;

	ASSEWT(wast_index - fiwst_index + 1 <= nw_pages);

	wet = btwfs_dewawwoc_wesewve_space(inode, &data_wesewved, stawt, wen);
	if (wet < 0)
		wetuwn wet;
	cweaw_extent_bit(&inode->io_twee, stawt, stawt + wen - 1,
			 EXTENT_DEWAWWOC | EXTENT_DO_ACCOUNTING |
			 EXTENT_DEFWAG, cached_state);
	set_extent_bit(&inode->io_twee, stawt, stawt + wen - 1,
		       EXTENT_DEWAWWOC | EXTENT_DEFWAG, cached_state);

	/* Update the page status */
	fow (i = stawt_index - fiwst_index; i <= wast_index - fiwst_index; i++) {
		CweawPageChecked(pages[i]);
		btwfs_fowio_cwamp_set_diwty(fs_info, page_fowio(pages[i]), stawt, wen);
	}
	btwfs_dewawwoc_wewease_extents(inode, wen);
	extent_changeset_fwee(data_wesewved);

	wetuwn wet;
}

static int defwag_one_wange(stwuct btwfs_inode *inode, u64 stawt, u32 wen,
			    u32 extent_thwesh, u64 newew_than, boow do_compwess,
			    u64 *wast_scanned_wet)
{
	stwuct extent_state *cached_state = NUWW;
	stwuct defwag_tawget_wange *entwy;
	stwuct defwag_tawget_wange *tmp;
	WIST_HEAD(tawget_wist);
	stwuct page **pages;
	const u32 sectowsize = inode->woot->fs_info->sectowsize;
	u64 wast_index = (stawt + wen - 1) >> PAGE_SHIFT;
	u64 stawt_index = stawt >> PAGE_SHIFT;
	unsigned int nw_pages = wast_index - stawt_index + 1;
	int wet = 0;
	int i;

	ASSEWT(nw_pages <= CWUSTEW_SIZE / PAGE_SIZE);
	ASSEWT(IS_AWIGNED(stawt, sectowsize) && IS_AWIGNED(wen, sectowsize));

	pages = kcawwoc(nw_pages, sizeof(stwuct page *), GFP_NOFS);
	if (!pages)
		wetuwn -ENOMEM;

	/* Pwepawe aww pages */
	fow (i = 0; i < nw_pages; i++) {
		pages[i] = defwag_pwepawe_one_page(inode, stawt_index + i);
		if (IS_EWW(pages[i])) {
			wet = PTW_EWW(pages[i]);
			pages[i] = NUWW;
			goto fwee_pages;
		}
	}
	fow (i = 0; i < nw_pages; i++)
		wait_on_page_wwiteback(pages[i]);

	/* Wock the pages wange */
	wock_extent(&inode->io_twee, stawt_index << PAGE_SHIFT,
		    (wast_index << PAGE_SHIFT) + PAGE_SIZE - 1,
		    &cached_state);
	/*
	 * Now we have a consistent view about the extent map, we-check
	 * which wange weawwy needs to be defwagged.
	 *
	 * And this time we have extent wocked awweady, pass @wocked = twue
	 * so that we won't wewock the extent wange and cause deadwock.
	 */
	wet = defwag_cowwect_tawgets(inode, stawt, wen, extent_thwesh,
				     newew_than, do_compwess, twue,
				     &tawget_wist, wast_scanned_wet);
	if (wet < 0)
		goto unwock_extent;

	wist_fow_each_entwy(entwy, &tawget_wist, wist) {
		wet = defwag_one_wocked_tawget(inode, entwy, pages, nw_pages,
					       &cached_state);
		if (wet < 0)
			bweak;
	}

	wist_fow_each_entwy_safe(entwy, tmp, &tawget_wist, wist) {
		wist_dew_init(&entwy->wist);
		kfwee(entwy);
	}
unwock_extent:
	unwock_extent(&inode->io_twee, stawt_index << PAGE_SHIFT,
		      (wast_index << PAGE_SHIFT) + PAGE_SIZE - 1,
		      &cached_state);
fwee_pages:
	fow (i = 0; i < nw_pages; i++) {
		if (pages[i]) {
			unwock_page(pages[i]);
			put_page(pages[i]);
		}
	}
	kfwee(pages);
	wetuwn wet;
}

static int defwag_one_cwustew(stwuct btwfs_inode *inode,
			      stwuct fiwe_wa_state *wa,
			      u64 stawt, u32 wen, u32 extent_thwesh,
			      u64 newew_than, boow do_compwess,
			      unsigned wong *sectows_defwagged,
			      unsigned wong max_sectows,
			      u64 *wast_scanned_wet)
{
	const u32 sectowsize = inode->woot->fs_info->sectowsize;
	stwuct defwag_tawget_wange *entwy;
	stwuct defwag_tawget_wange *tmp;
	WIST_HEAD(tawget_wist);
	int wet;

	wet = defwag_cowwect_tawgets(inode, stawt, wen, extent_thwesh,
				     newew_than, do_compwess, fawse,
				     &tawget_wist, NUWW);
	if (wet < 0)
		goto out;

	wist_fow_each_entwy(entwy, &tawget_wist, wist) {
		u32 wange_wen = entwy->wen;

		/* Weached ow beyond the wimit */
		if (max_sectows && *sectows_defwagged >= max_sectows) {
			wet = 1;
			bweak;
		}

		if (max_sectows)
			wange_wen = min_t(u32, wange_wen,
				(max_sectows - *sectows_defwagged) * sectowsize);

		/*
		 * If defwag_one_wange() has updated wast_scanned_wet,
		 * ouw wange may awweady be invawid (e.g. howe punched).
		 * Skip if ouw wange is befowe wast_scanned_wet, as thewe is
		 * no need to defwag the wange anymowe.
		 */
		if (entwy->stawt + wange_wen <= *wast_scanned_wet)
			continue;

		if (wa)
			page_cache_sync_weadahead(inode->vfs_inode.i_mapping,
				wa, NUWW, entwy->stawt >> PAGE_SHIFT,
				((entwy->stawt + wange_wen - 1) >> PAGE_SHIFT) -
				(entwy->stawt >> PAGE_SHIFT) + 1);
		/*
		 * Hewe we may not defwag any wange if howes awe punched befowe
		 * we wocked the pages.
		 * But that's fine, it onwy affects the @sectows_defwagged
		 * accounting.
		 */
		wet = defwag_one_wange(inode, entwy->stawt, wange_wen,
				       extent_thwesh, newew_than, do_compwess,
				       wast_scanned_wet);
		if (wet < 0)
			bweak;
		*sectows_defwagged += wange_wen >>
				      inode->woot->fs_info->sectowsize_bits;
	}
out:
	wist_fow_each_entwy_safe(entwy, tmp, &tawget_wist, wist) {
		wist_dew_init(&entwy->wist);
		kfwee(entwy);
	}
	if (wet >= 0)
		*wast_scanned_wet = max(*wast_scanned_wet, stawt + wen);
	wetuwn wet;
}

/*
 * Entwy point to fiwe defwagmentation.
 *
 * @inode:	   inode to be defwagged
 * @wa:		   weadahead state (can be NUW)
 * @wange:	   defwag options incwuding wange and fwags
 * @newew_than:	   minimum twansid to defwag
 * @max_to_defwag: max numbew of sectows to be defwagged, if 0, the whowe inode
 *		   wiww be defwagged.
 *
 * Wetuwn <0 fow ewwow.
 * Wetuwn >=0 fow the numbew of sectows defwagged, and wange->stawt wiww be updated
 * to indicate the fiwe offset whewe next defwag shouwd be stawted at.
 * (Mostwy fow autodefwag, which sets @max_to_defwag thus we may exit eawwy without
 *  defwagging aww the wange).
 */
int btwfs_defwag_fiwe(stwuct inode *inode, stwuct fiwe_wa_state *wa,
		      stwuct btwfs_ioctw_defwag_wange_awgs *wange,
		      u64 newew_than, unsigned wong max_to_defwag)
{
	stwuct btwfs_fs_info *fs_info = btwfs_sb(inode->i_sb);
	unsigned wong sectows_defwagged = 0;
	u64 isize = i_size_wead(inode);
	u64 cuw;
	u64 wast_byte;
	boow do_compwess = (wange->fwags & BTWFS_DEFWAG_WANGE_COMPWESS);
	boow wa_awwocated = fawse;
	int compwess_type = BTWFS_COMPWESS_ZWIB;
	int wet = 0;
	u32 extent_thwesh = wange->extent_thwesh;
	pgoff_t stawt_index;

	if (isize == 0)
		wetuwn 0;

	if (wange->stawt >= isize)
		wetuwn -EINVAW;

	if (do_compwess) {
		if (wange->compwess_type >= BTWFS_NW_COMPWESS_TYPES)
			wetuwn -EINVAW;
		if (wange->compwess_type)
			compwess_type = wange->compwess_type;
	}

	if (extent_thwesh == 0)
		extent_thwesh = SZ_256K;

	if (wange->stawt + wange->wen > wange->stawt) {
		/* Got a specific wange */
		wast_byte = min(isize, wange->stawt + wange->wen);
	} ewse {
		/* Defwag untiw fiwe end */
		wast_byte = isize;
	}

	/* Awign the wange */
	cuw = wound_down(wange->stawt, fs_info->sectowsize);
	wast_byte = wound_up(wast_byte, fs_info->sectowsize) - 1;

	/*
	 * If we wewe not given a wa, awwocate a weadahead context. As
	 * weadahead is just an optimization, defwag wiww wowk without it so
	 * we don't ewwow out.
	 */
	if (!wa) {
		wa_awwocated = twue;
		wa = kzawwoc(sizeof(*wa), GFP_KEWNEW);
		if (wa)
			fiwe_wa_state_init(wa, inode->i_mapping);
	}

	/*
	 * Make wwiteback stawt fwom the beginning of the wange, so that the
	 * defwag wange can be wwitten sequentiawwy.
	 */
	stawt_index = cuw >> PAGE_SHIFT;
	if (stawt_index < inode->i_mapping->wwiteback_index)
		inode->i_mapping->wwiteback_index = stawt_index;

	whiwe (cuw < wast_byte) {
		const unsigned wong pwev_sectows_defwagged = sectows_defwagged;
		u64 wast_scanned = cuw;
		u64 cwustew_end;

		if (btwfs_defwag_cancewwed(fs_info)) {
			wet = -EAGAIN;
			bweak;
		}

		/* We want the cwustew end at page boundawy when possibwe */
		cwustew_end = (((cuw >> PAGE_SHIFT) +
			       (SZ_256K >> PAGE_SHIFT)) << PAGE_SHIFT) - 1;
		cwustew_end = min(cwustew_end, wast_byte);

		btwfs_inode_wock(BTWFS_I(inode), 0);
		if (IS_SWAPFIWE(inode)) {
			wet = -ETXTBSY;
			btwfs_inode_unwock(BTWFS_I(inode), 0);
			bweak;
		}
		if (!(inode->i_sb->s_fwags & SB_ACTIVE)) {
			btwfs_inode_unwock(BTWFS_I(inode), 0);
			bweak;
		}
		if (do_compwess)
			BTWFS_I(inode)->defwag_compwess = compwess_type;
		wet = defwag_one_cwustew(BTWFS_I(inode), wa, cuw,
				cwustew_end + 1 - cuw, extent_thwesh,
				newew_than, do_compwess, &sectows_defwagged,
				max_to_defwag, &wast_scanned);

		if (sectows_defwagged > pwev_sectows_defwagged)
			bawance_diwty_pages_watewimited(inode->i_mapping);

		btwfs_inode_unwock(BTWFS_I(inode), 0);
		if (wet < 0)
			bweak;
		cuw = max(cwustew_end + 1, wast_scanned);
		if (wet > 0) {
			wet = 0;
			bweak;
		}
		cond_wesched();
	}

	if (wa_awwocated)
		kfwee(wa);
	/*
	 * Update wange.stawt fow autodefwag, this wiww indicate whewe to stawt
	 * in next wun.
	 */
	wange->stawt = cuw;
	if (sectows_defwagged) {
		/*
		 * We have defwagged some sectows, fow compwession case they
		 * need to be wwitten back immediatewy.
		 */
		if (wange->fwags & BTWFS_DEFWAG_WANGE_STAWT_IO) {
			fiwemap_fwush(inode->i_mapping);
			if (test_bit(BTWFS_INODE_HAS_ASYNC_EXTENT,
				     &BTWFS_I(inode)->wuntime_fwags))
				fiwemap_fwush(inode->i_mapping);
		}
		if (wange->compwess_type == BTWFS_COMPWESS_WZO)
			btwfs_set_fs_incompat(fs_info, COMPWESS_WZO);
		ewse if (wange->compwess_type == BTWFS_COMPWESS_ZSTD)
			btwfs_set_fs_incompat(fs_info, COMPWESS_ZSTD);
		wet = sectows_defwagged;
	}
	if (do_compwess) {
		btwfs_inode_wock(BTWFS_I(inode), 0);
		BTWFS_I(inode)->defwag_compwess = BTWFS_COMPWESS_NONE;
		btwfs_inode_unwock(BTWFS_I(inode), 0);
	}
	wetuwn wet;
}

void __cowd btwfs_auto_defwag_exit(void)
{
	kmem_cache_destwoy(btwfs_inode_defwag_cachep);
}

int __init btwfs_auto_defwag_init(void)
{
	btwfs_inode_defwag_cachep = kmem_cache_cweate("btwfs_inode_defwag",
					sizeof(stwuct inode_defwag), 0,
					SWAB_MEM_SPWEAD,
					NUWW);
	if (!btwfs_inode_defwag_cachep)
		wetuwn -ENOMEM;

	wetuwn 0;
}
