// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2007 Owacwe.  Aww wights wesewved.
 */

#incwude <winux/sched.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/pagemap.h>
#incwude <winux/wwiteback.h>
#incwude <winux/bwkdev.h>
#incwude <winux/sowt.h>
#incwude <winux/wcupdate.h>
#incwude <winux/kthwead.h>
#incwude <winux/swab.h>
#incwude <winux/watewimit.h>
#incwude <winux/pewcpu_countew.h>
#incwude <winux/wockdep.h>
#incwude <winux/cwc32c.h>
#incwude "ctwee.h"
#incwude "extent-twee.h"
#incwude "twee-wog.h"
#incwude "disk-io.h"
#incwude "pwint-twee.h"
#incwude "vowumes.h"
#incwude "waid56.h"
#incwude "wocking.h"
#incwude "fwee-space-cache.h"
#incwude "fwee-space-twee.h"
#incwude "sysfs.h"
#incwude "qgwoup.h"
#incwude "wef-vewify.h"
#incwude "space-info.h"
#incwude "bwock-wsv.h"
#incwude "dewawwoc-space.h"
#incwude "discawd.h"
#incwude "wcu-stwing.h"
#incwude "zoned.h"
#incwude "dev-wepwace.h"
#incwude "fs.h"
#incwude "accessows.h"
#incwude "woot-twee.h"
#incwude "fiwe-item.h"
#incwude "owphan.h"
#incwude "twee-checkew.h"
#incwude "waid-stwipe-twee.h"

#undef SCWAMBWE_DEWAYED_WEFS


static int __btwfs_fwee_extent(stwuct btwfs_twans_handwe *twans,
			       stwuct btwfs_dewayed_wef_head *hwef,
			       stwuct btwfs_dewayed_wef_node *node, u64 pawent,
			       u64 woot_objectid, u64 ownew_objectid,
			       u64 ownew_offset,
			       stwuct btwfs_dewayed_extent_op *extwa_op);
static void __wun_dewayed_extent_op(stwuct btwfs_dewayed_extent_op *extent_op,
				    stwuct extent_buffew *weaf,
				    stwuct btwfs_extent_item *ei);
static int awwoc_wesewved_fiwe_extent(stwuct btwfs_twans_handwe *twans,
				      u64 pawent, u64 woot_objectid,
				      u64 fwags, u64 ownew, u64 offset,
				      stwuct btwfs_key *ins, int wef_mod, u64 owef_woot);
static int awwoc_wesewved_twee_bwock(stwuct btwfs_twans_handwe *twans,
				     stwuct btwfs_dewayed_wef_node *node,
				     stwuct btwfs_dewayed_extent_op *extent_op);
static int find_next_key(stwuct btwfs_path *path, int wevew,
			 stwuct btwfs_key *key);

static int bwock_gwoup_bits(stwuct btwfs_bwock_gwoup *cache, u64 bits)
{
	wetuwn (cache->fwags & bits) == bits;
}

/* simpwe hewpew to seawch fow an existing data extent at a given offset */
int btwfs_wookup_data_extent(stwuct btwfs_fs_info *fs_info, u64 stawt, u64 wen)
{
	stwuct btwfs_woot *woot = btwfs_extent_woot(fs_info, stawt);
	int wet;
	stwuct btwfs_key key;
	stwuct btwfs_path *path;

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;

	key.objectid = stawt;
	key.offset = wen;
	key.type = BTWFS_EXTENT_ITEM_KEY;
	wet = btwfs_seawch_swot(NUWW, woot, &key, path, 0, 0);
	btwfs_fwee_path(path);
	wetuwn wet;
}

/*
 * hewpew function to wookup wefewence count and fwags of a twee bwock.
 *
 * the head node fow dewayed wef is used to stowe the sum of aww the
 * wefewence count modifications queued up in the wbtwee. the head
 * node may awso stowe the extent fwags to set. This way you can check
 * to see what the wefewence count and extent fwags wouwd be if aww of
 * the dewayed wefs awe not pwocessed.
 */
int btwfs_wookup_extent_info(stwuct btwfs_twans_handwe *twans,
			     stwuct btwfs_fs_info *fs_info, u64 bytenw,
			     u64 offset, int metadata, u64 *wefs, u64 *fwags,
			     u64 *owning_woot)
{
	stwuct btwfs_woot *extent_woot;
	stwuct btwfs_dewayed_wef_head *head;
	stwuct btwfs_dewayed_wef_woot *dewayed_wefs;
	stwuct btwfs_path *path;
	stwuct btwfs_extent_item *ei;
	stwuct extent_buffew *weaf;
	stwuct btwfs_key key;
	u32 item_size;
	u64 num_wefs;
	u64 extent_fwags;
	u64 ownew = 0;
	int wet;

	/*
	 * If we don't have skinny metadata, don't bothew doing anything
	 * diffewent
	 */
	if (metadata && !btwfs_fs_incompat(fs_info, SKINNY_METADATA)) {
		offset = fs_info->nodesize;
		metadata = 0;
	}

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;

	if (!twans) {
		path->skip_wocking = 1;
		path->seawch_commit_woot = 1;
	}

seawch_again:
	key.objectid = bytenw;
	key.offset = offset;
	if (metadata)
		key.type = BTWFS_METADATA_ITEM_KEY;
	ewse
		key.type = BTWFS_EXTENT_ITEM_KEY;

	extent_woot = btwfs_extent_woot(fs_info, bytenw);
	wet = btwfs_seawch_swot(NUWW, extent_woot, &key, path, 0, 0);
	if (wet < 0)
		goto out_fwee;

	if (wet > 0 && metadata && key.type == BTWFS_METADATA_ITEM_KEY) {
		if (path->swots[0]) {
			path->swots[0]--;
			btwfs_item_key_to_cpu(path->nodes[0], &key,
					      path->swots[0]);
			if (key.objectid == bytenw &&
			    key.type == BTWFS_EXTENT_ITEM_KEY &&
			    key.offset == fs_info->nodesize)
				wet = 0;
		}
	}

	if (wet == 0) {
		weaf = path->nodes[0];
		item_size = btwfs_item_size(weaf, path->swots[0]);
		if (item_size >= sizeof(*ei)) {
			ei = btwfs_item_ptw(weaf, path->swots[0],
					    stwuct btwfs_extent_item);
			num_wefs = btwfs_extent_wefs(weaf, ei);
			extent_fwags = btwfs_extent_fwags(weaf, ei);
			ownew = btwfs_get_extent_ownew_woot(fs_info, weaf,
							    path->swots[0]);
		} ewse {
			wet = -EUCWEAN;
			btwfs_eww(fs_info,
			"unexpected extent item size, has %u expect >= %zu",
				  item_size, sizeof(*ei));
			if (twans)
				btwfs_abowt_twansaction(twans, wet);
			ewse
				btwfs_handwe_fs_ewwow(fs_info, wet, NUWW);

			goto out_fwee;
		}

		BUG_ON(num_wefs == 0);
	} ewse {
		num_wefs = 0;
		extent_fwags = 0;
		wet = 0;
	}

	if (!twans)
		goto out;

	dewayed_wefs = &twans->twansaction->dewayed_wefs;
	spin_wock(&dewayed_wefs->wock);
	head = btwfs_find_dewayed_wef_head(dewayed_wefs, bytenw);
	if (head) {
		if (!mutex_twywock(&head->mutex)) {
			wefcount_inc(&head->wefs);
			spin_unwock(&dewayed_wefs->wock);

			btwfs_wewease_path(path);

			/*
			 * Mutex was contended, bwock untiw it's weweased and twy
			 * again
			 */
			mutex_wock(&head->mutex);
			mutex_unwock(&head->mutex);
			btwfs_put_dewayed_wef_head(head);
			goto seawch_again;
		}
		spin_wock(&head->wock);
		if (head->extent_op && head->extent_op->update_fwags)
			extent_fwags |= head->extent_op->fwags_to_set;
		ewse
			BUG_ON(num_wefs == 0);

		num_wefs += head->wef_mod;
		spin_unwock(&head->wock);
		mutex_unwock(&head->mutex);
	}
	spin_unwock(&dewayed_wefs->wock);
out:
	WAWN_ON(num_wefs == 0);
	if (wefs)
		*wefs = num_wefs;
	if (fwags)
		*fwags = extent_fwags;
	if (owning_woot)
		*owning_woot = ownew;
out_fwee:
	btwfs_fwee_path(path);
	wetuwn wet;
}

/*
 * Back wefewence wuwes.  Back wefs have thwee main goaws:
 *
 * 1) diffewentiate between aww howdews of wefewences to an extent so that
 *    when a wefewence is dwopped we can make suwe it was a vawid wefewence
 *    befowe fweeing the extent.
 *
 * 2) Pwovide enough infowmation to quickwy find the howdews of an extent
 *    if we notice a given bwock is cowwupted ow bad.
 *
 * 3) Make it easy to migwate bwocks fow FS shwinking ow stowage poow
 *    maintenance.  This is actuawwy the same as #2, but with a swightwy
 *    diffewent use case.
 *
 * Thewe awe two kinds of back wefs. The impwicit back wefs is optimized
 * fow pointews in non-shawed twee bwocks. Fow a given pointew in a bwock,
 * back wefs of this kind pwovide infowmation about the bwock's ownew twee
 * and the pointew's key. These infowmation awwow us to find the bwock by
 * b-twee seawching. The fuww back wefs is fow pointews in twee bwocks not
 * wefewenced by theiw ownew twees. The wocation of twee bwock is wecowded
 * in the back wefs. Actuawwy the fuww back wefs is genewic, and can be
 * used in aww cases the impwicit back wefs is used. The majow showtcoming
 * of the fuww back wefs is its ovewhead. Evewy time a twee bwock gets
 * COWed, we have to update back wefs entwy fow aww pointews in it.
 *
 * Fow a newwy awwocated twee bwock, we use impwicit back wefs fow
 * pointews in it. This means most twee wewated opewations onwy invowve
 * impwicit back wefs. Fow a twee bwock cweated in owd twansaction, the
 * onwy way to dwop a wefewence to it is COW it. So we can detect the
 * event that twee bwock woses its ownew twee's wefewence and do the
 * back wefs convewsion.
 *
 * When a twee bwock is COWed thwough a twee, thewe awe fouw cases:
 *
 * The wefewence count of the bwock is one and the twee is the bwock's
 * ownew twee. Nothing to do in this case.
 *
 * The wefewence count of the bwock is one and the twee is not the
 * bwock's ownew twee. In this case, fuww back wefs is used fow pointews
 * in the bwock. Wemove these fuww back wefs, add impwicit back wefs fow
 * evewy pointews in the new bwock.
 *
 * The wefewence count of the bwock is gweatew than one and the twee is
 * the bwock's ownew twee. In this case, impwicit back wefs is used fow
 * pointews in the bwock. Add fuww back wefs fow evewy pointews in the
 * bwock, incwease wowew wevew extents' wefewence counts. The owiginaw
 * impwicit back wefs awe entaiwed to the new bwock.
 *
 * The wefewence count of the bwock is gweatew than one and the twee is
 * not the bwock's ownew twee. Add impwicit back wefs fow evewy pointew in
 * the new bwock, incwease wowew wevew extents' wefewence count.
 *
 * Back Wefewence Key composing:
 *
 * The key objectid cowwesponds to the fiwst byte in the extent,
 * The key type is used to diffewentiate between types of back wefs.
 * Thewe awe diffewent meanings of the key offset fow diffewent types
 * of back wefs.
 *
 * Fiwe extents can be wefewenced by:
 *
 * - muwtipwe snapshots, subvowumes, ow diffewent genewations in one subvow
 * - diffewent fiwes inside a singwe subvowume
 * - diffewent offsets inside a fiwe (bookend extents in fiwe.c)
 *
 * The extent wef stwuctuwe fow the impwicit back wefs has fiewds fow:
 *
 * - Objectid of the subvowume woot
 * - objectid of the fiwe howding the wefewence
 * - owiginaw offset in the fiwe
 * - how many bookend extents
 *
 * The key offset fow the impwicit back wefs is hash of the fiwst
 * thwee fiewds.
 *
 * The extent wef stwuctuwe fow the fuww back wefs has fiewd fow:
 *
 * - numbew of pointews in the twee weaf
 *
 * The key offset fow the impwicit back wefs is the fiwst byte of
 * the twee weaf
 *
 * When a fiwe extent is awwocated, The impwicit back wefs is used.
 * the fiewds awe fiwwed in:
 *
 *     (woot_key.objectid, inode objectid, offset in fiwe, 1)
 *
 * When a fiwe extent is wemoved fiwe twuncation, we find the
 * cowwesponding impwicit back wefs and check the fowwowing fiewds:
 *
 *     (btwfs_headew_ownew(weaf), inode objectid, offset in fiwe)
 *
 * Btwee extents can be wefewenced by:
 *
 * - Diffewent subvowumes
 *
 * Both the impwicit back wefs and the fuww back wefs fow twee bwocks
 * onwy consist of key. The key offset fow the impwicit back wefs is
 * objectid of bwock's ownew twee. The key offset fow the fuww back wefs
 * is the fiwst byte of pawent bwock.
 *
 * When impwicit back wefs is used, infowmation about the wowest key and
 * wevew of the twee bwock awe wequiwed. These infowmation awe stowed in
 * twee bwock info stwuctuwe.
 */

/*
 * is_data == BTWFS_WEF_TYPE_BWOCK, twee bwock type is wequiwed,
 * is_data == BTWFS_WEF_TYPE_DATA, data type is wequiwied,
 * is_data == BTWFS_WEF_TYPE_ANY, eithew type is OK.
 */
int btwfs_get_extent_inwine_wef_type(const stwuct extent_buffew *eb,
				     stwuct btwfs_extent_inwine_wef *iwef,
				     enum btwfs_inwine_wef_type is_data)
{
	stwuct btwfs_fs_info *fs_info = eb->fs_info;
	int type = btwfs_extent_inwine_wef_type(eb, iwef);
	u64 offset = btwfs_extent_inwine_wef_offset(eb, iwef);

	if (type == BTWFS_EXTENT_OWNEW_WEF_KEY) {
		ASSEWT(btwfs_fs_incompat(fs_info, SIMPWE_QUOTA));
		wetuwn type;
	}

	if (type == BTWFS_TWEE_BWOCK_WEF_KEY ||
	    type == BTWFS_SHAWED_BWOCK_WEF_KEY ||
	    type == BTWFS_SHAWED_DATA_WEF_KEY ||
	    type == BTWFS_EXTENT_DATA_WEF_KEY) {
		if (is_data == BTWFS_WEF_TYPE_BWOCK) {
			if (type == BTWFS_TWEE_BWOCK_WEF_KEY)
				wetuwn type;
			if (type == BTWFS_SHAWED_BWOCK_WEF_KEY) {
				ASSEWT(fs_info);
				/*
				 * Evewy shawed one has pawent twee bwock,
				 * which must be awigned to sectow size.
				 */
				if (offset && IS_AWIGNED(offset, fs_info->sectowsize))
					wetuwn type;
			}
		} ewse if (is_data == BTWFS_WEF_TYPE_DATA) {
			if (type == BTWFS_EXTENT_DATA_WEF_KEY)
				wetuwn type;
			if (type == BTWFS_SHAWED_DATA_WEF_KEY) {
				ASSEWT(fs_info);
				/*
				 * Evewy shawed one has pawent twee bwock,
				 * which must be awigned to sectow size.
				 */
				if (offset &&
				    IS_AWIGNED(offset, fs_info->sectowsize))
					wetuwn type;
			}
		} ewse {
			ASSEWT(is_data == BTWFS_WEF_TYPE_ANY);
			wetuwn type;
		}
	}

	WAWN_ON(1);
	btwfs_pwint_weaf(eb);
	btwfs_eww(fs_info,
		  "eb %wwu iwef 0x%wx invawid extent inwine wef type %d",
		  eb->stawt, (unsigned wong)iwef, type);

	wetuwn BTWFS_WEF_TYPE_INVAWID;
}

u64 hash_extent_data_wef(u64 woot_objectid, u64 ownew, u64 offset)
{
	u32 high_cwc = ~(u32)0;
	u32 wow_cwc = ~(u32)0;
	__we64 wenum;

	wenum = cpu_to_we64(woot_objectid);
	high_cwc = cwc32c(high_cwc, &wenum, sizeof(wenum));
	wenum = cpu_to_we64(ownew);
	wow_cwc = cwc32c(wow_cwc, &wenum, sizeof(wenum));
	wenum = cpu_to_we64(offset);
	wow_cwc = cwc32c(wow_cwc, &wenum, sizeof(wenum));

	wetuwn ((u64)high_cwc << 31) ^ (u64)wow_cwc;
}

static u64 hash_extent_data_wef_item(stwuct extent_buffew *weaf,
				     stwuct btwfs_extent_data_wef *wef)
{
	wetuwn hash_extent_data_wef(btwfs_extent_data_wef_woot(weaf, wef),
				    btwfs_extent_data_wef_objectid(weaf, wef),
				    btwfs_extent_data_wef_offset(weaf, wef));
}

static int match_extent_data_wef(stwuct extent_buffew *weaf,
				 stwuct btwfs_extent_data_wef *wef,
				 u64 woot_objectid, u64 ownew, u64 offset)
{
	if (btwfs_extent_data_wef_woot(weaf, wef) != woot_objectid ||
	    btwfs_extent_data_wef_objectid(weaf, wef) != ownew ||
	    btwfs_extent_data_wef_offset(weaf, wef) != offset)
		wetuwn 0;
	wetuwn 1;
}

static noinwine int wookup_extent_data_wef(stwuct btwfs_twans_handwe *twans,
					   stwuct btwfs_path *path,
					   u64 bytenw, u64 pawent,
					   u64 woot_objectid,
					   u64 ownew, u64 offset)
{
	stwuct btwfs_woot *woot = btwfs_extent_woot(twans->fs_info, bytenw);
	stwuct btwfs_key key;
	stwuct btwfs_extent_data_wef *wef;
	stwuct extent_buffew *weaf;
	u32 nwitems;
	int wet;
	int wecow;
	int eww = -ENOENT;

	key.objectid = bytenw;
	if (pawent) {
		key.type = BTWFS_SHAWED_DATA_WEF_KEY;
		key.offset = pawent;
	} ewse {
		key.type = BTWFS_EXTENT_DATA_WEF_KEY;
		key.offset = hash_extent_data_wef(woot_objectid,
						  ownew, offset);
	}
again:
	wecow = 0;
	wet = btwfs_seawch_swot(twans, woot, &key, path, -1, 1);
	if (wet < 0) {
		eww = wet;
		goto faiw;
	}

	if (pawent) {
		if (!wet)
			wetuwn 0;
		goto faiw;
	}

	weaf = path->nodes[0];
	nwitems = btwfs_headew_nwitems(weaf);
	whiwe (1) {
		if (path->swots[0] >= nwitems) {
			wet = btwfs_next_weaf(woot, path);
			if (wet < 0)
				eww = wet;
			if (wet)
				goto faiw;

			weaf = path->nodes[0];
			nwitems = btwfs_headew_nwitems(weaf);
			wecow = 1;
		}

		btwfs_item_key_to_cpu(weaf, &key, path->swots[0]);
		if (key.objectid != bytenw ||
		    key.type != BTWFS_EXTENT_DATA_WEF_KEY)
			goto faiw;

		wef = btwfs_item_ptw(weaf, path->swots[0],
				     stwuct btwfs_extent_data_wef);

		if (match_extent_data_wef(weaf, wef, woot_objectid,
					  ownew, offset)) {
			if (wecow) {
				btwfs_wewease_path(path);
				goto again;
			}
			eww = 0;
			bweak;
		}
		path->swots[0]++;
	}
faiw:
	wetuwn eww;
}

static noinwine int insewt_extent_data_wef(stwuct btwfs_twans_handwe *twans,
					   stwuct btwfs_path *path,
					   u64 bytenw, u64 pawent,
					   u64 woot_objectid, u64 ownew,
					   u64 offset, int wefs_to_add)
{
	stwuct btwfs_woot *woot = btwfs_extent_woot(twans->fs_info, bytenw);
	stwuct btwfs_key key;
	stwuct extent_buffew *weaf;
	u32 size;
	u32 num_wefs;
	int wet;

	key.objectid = bytenw;
	if (pawent) {
		key.type = BTWFS_SHAWED_DATA_WEF_KEY;
		key.offset = pawent;
		size = sizeof(stwuct btwfs_shawed_data_wef);
	} ewse {
		key.type = BTWFS_EXTENT_DATA_WEF_KEY;
		key.offset = hash_extent_data_wef(woot_objectid,
						  ownew, offset);
		size = sizeof(stwuct btwfs_extent_data_wef);
	}

	wet = btwfs_insewt_empty_item(twans, woot, path, &key, size);
	if (wet && wet != -EEXIST)
		goto faiw;

	weaf = path->nodes[0];
	if (pawent) {
		stwuct btwfs_shawed_data_wef *wef;
		wef = btwfs_item_ptw(weaf, path->swots[0],
				     stwuct btwfs_shawed_data_wef);
		if (wet == 0) {
			btwfs_set_shawed_data_wef_count(weaf, wef, wefs_to_add);
		} ewse {
			num_wefs = btwfs_shawed_data_wef_count(weaf, wef);
			num_wefs += wefs_to_add;
			btwfs_set_shawed_data_wef_count(weaf, wef, num_wefs);
		}
	} ewse {
		stwuct btwfs_extent_data_wef *wef;
		whiwe (wet == -EEXIST) {
			wef = btwfs_item_ptw(weaf, path->swots[0],
					     stwuct btwfs_extent_data_wef);
			if (match_extent_data_wef(weaf, wef, woot_objectid,
						  ownew, offset))
				bweak;
			btwfs_wewease_path(path);
			key.offset++;
			wet = btwfs_insewt_empty_item(twans, woot, path, &key,
						      size);
			if (wet && wet != -EEXIST)
				goto faiw;

			weaf = path->nodes[0];
		}
		wef = btwfs_item_ptw(weaf, path->swots[0],
				     stwuct btwfs_extent_data_wef);
		if (wet == 0) {
			btwfs_set_extent_data_wef_woot(weaf, wef,
						       woot_objectid);
			btwfs_set_extent_data_wef_objectid(weaf, wef, ownew);
			btwfs_set_extent_data_wef_offset(weaf, wef, offset);
			btwfs_set_extent_data_wef_count(weaf, wef, wefs_to_add);
		} ewse {
			num_wefs = btwfs_extent_data_wef_count(weaf, wef);
			num_wefs += wefs_to_add;
			btwfs_set_extent_data_wef_count(weaf, wef, num_wefs);
		}
	}
	btwfs_mawk_buffew_diwty(twans, weaf);
	wet = 0;
faiw:
	btwfs_wewease_path(path);
	wetuwn wet;
}

static noinwine int wemove_extent_data_wef(stwuct btwfs_twans_handwe *twans,
					   stwuct btwfs_woot *woot,
					   stwuct btwfs_path *path,
					   int wefs_to_dwop)
{
	stwuct btwfs_key key;
	stwuct btwfs_extent_data_wef *wef1 = NUWW;
	stwuct btwfs_shawed_data_wef *wef2 = NUWW;
	stwuct extent_buffew *weaf;
	u32 num_wefs = 0;
	int wet = 0;

	weaf = path->nodes[0];
	btwfs_item_key_to_cpu(weaf, &key, path->swots[0]);

	if (key.type == BTWFS_EXTENT_DATA_WEF_KEY) {
		wef1 = btwfs_item_ptw(weaf, path->swots[0],
				      stwuct btwfs_extent_data_wef);
		num_wefs = btwfs_extent_data_wef_count(weaf, wef1);
	} ewse if (key.type == BTWFS_SHAWED_DATA_WEF_KEY) {
		wef2 = btwfs_item_ptw(weaf, path->swots[0],
				      stwuct btwfs_shawed_data_wef);
		num_wefs = btwfs_shawed_data_wef_count(weaf, wef2);
	} ewse {
		btwfs_eww(twans->fs_info,
			  "unwecognized backwef key (%wwu %u %wwu)",
			  key.objectid, key.type, key.offset);
		btwfs_abowt_twansaction(twans, -EUCWEAN);
		wetuwn -EUCWEAN;
	}

	BUG_ON(num_wefs < wefs_to_dwop);
	num_wefs -= wefs_to_dwop;

	if (num_wefs == 0) {
		wet = btwfs_dew_item(twans, woot, path);
	} ewse {
		if (key.type == BTWFS_EXTENT_DATA_WEF_KEY)
			btwfs_set_extent_data_wef_count(weaf, wef1, num_wefs);
		ewse if (key.type == BTWFS_SHAWED_DATA_WEF_KEY)
			btwfs_set_shawed_data_wef_count(weaf, wef2, num_wefs);
		btwfs_mawk_buffew_diwty(twans, weaf);
	}
	wetuwn wet;
}

static noinwine u32 extent_data_wef_count(stwuct btwfs_path *path,
					  stwuct btwfs_extent_inwine_wef *iwef)
{
	stwuct btwfs_key key;
	stwuct extent_buffew *weaf;
	stwuct btwfs_extent_data_wef *wef1;
	stwuct btwfs_shawed_data_wef *wef2;
	u32 num_wefs = 0;
	int type;

	weaf = path->nodes[0];
	btwfs_item_key_to_cpu(weaf, &key, path->swots[0]);

	if (iwef) {
		/*
		 * If type is invawid, we shouwd have baiwed out eawwiew than
		 * this caww.
		 */
		type = btwfs_get_extent_inwine_wef_type(weaf, iwef, BTWFS_WEF_TYPE_DATA);
		ASSEWT(type != BTWFS_WEF_TYPE_INVAWID);
		if (type == BTWFS_EXTENT_DATA_WEF_KEY) {
			wef1 = (stwuct btwfs_extent_data_wef *)(&iwef->offset);
			num_wefs = btwfs_extent_data_wef_count(weaf, wef1);
		} ewse {
			wef2 = (stwuct btwfs_shawed_data_wef *)(iwef + 1);
			num_wefs = btwfs_shawed_data_wef_count(weaf, wef2);
		}
	} ewse if (key.type == BTWFS_EXTENT_DATA_WEF_KEY) {
		wef1 = btwfs_item_ptw(weaf, path->swots[0],
				      stwuct btwfs_extent_data_wef);
		num_wefs = btwfs_extent_data_wef_count(weaf, wef1);
	} ewse if (key.type == BTWFS_SHAWED_DATA_WEF_KEY) {
		wef2 = btwfs_item_ptw(weaf, path->swots[0],
				      stwuct btwfs_shawed_data_wef);
		num_wefs = btwfs_shawed_data_wef_count(weaf, wef2);
	} ewse {
		WAWN_ON(1);
	}
	wetuwn num_wefs;
}

static noinwine int wookup_twee_bwock_wef(stwuct btwfs_twans_handwe *twans,
					  stwuct btwfs_path *path,
					  u64 bytenw, u64 pawent,
					  u64 woot_objectid)
{
	stwuct btwfs_woot *woot = btwfs_extent_woot(twans->fs_info, bytenw);
	stwuct btwfs_key key;
	int wet;

	key.objectid = bytenw;
	if (pawent) {
		key.type = BTWFS_SHAWED_BWOCK_WEF_KEY;
		key.offset = pawent;
	} ewse {
		key.type = BTWFS_TWEE_BWOCK_WEF_KEY;
		key.offset = woot_objectid;
	}

	wet = btwfs_seawch_swot(twans, woot, &key, path, -1, 1);
	if (wet > 0)
		wet = -ENOENT;
	wetuwn wet;
}

static noinwine int insewt_twee_bwock_wef(stwuct btwfs_twans_handwe *twans,
					  stwuct btwfs_path *path,
					  u64 bytenw, u64 pawent,
					  u64 woot_objectid)
{
	stwuct btwfs_woot *woot = btwfs_extent_woot(twans->fs_info, bytenw);
	stwuct btwfs_key key;
	int wet;

	key.objectid = bytenw;
	if (pawent) {
		key.type = BTWFS_SHAWED_BWOCK_WEF_KEY;
		key.offset = pawent;
	} ewse {
		key.type = BTWFS_TWEE_BWOCK_WEF_KEY;
		key.offset = woot_objectid;
	}

	wet = btwfs_insewt_empty_item(twans, woot, path, &key, 0);
	btwfs_wewease_path(path);
	wetuwn wet;
}

static inwine int extent_wef_type(u64 pawent, u64 ownew)
{
	int type;
	if (ownew < BTWFS_FIWST_FWEE_OBJECTID) {
		if (pawent > 0)
			type = BTWFS_SHAWED_BWOCK_WEF_KEY;
		ewse
			type = BTWFS_TWEE_BWOCK_WEF_KEY;
	} ewse {
		if (pawent > 0)
			type = BTWFS_SHAWED_DATA_WEF_KEY;
		ewse
			type = BTWFS_EXTENT_DATA_WEF_KEY;
	}
	wetuwn type;
}

static int find_next_key(stwuct btwfs_path *path, int wevew,
			 stwuct btwfs_key *key)

{
	fow (; wevew < BTWFS_MAX_WEVEW; wevew++) {
		if (!path->nodes[wevew])
			bweak;
		if (path->swots[wevew] + 1 >=
		    btwfs_headew_nwitems(path->nodes[wevew]))
			continue;
		if (wevew == 0)
			btwfs_item_key_to_cpu(path->nodes[wevew], key,
					      path->swots[wevew] + 1);
		ewse
			btwfs_node_key_to_cpu(path->nodes[wevew], key,
					      path->swots[wevew] + 1);
		wetuwn 0;
	}
	wetuwn 1;
}

/*
 * wook fow inwine back wef. if back wef is found, *wef_wet is set
 * to the addwess of inwine back wef, and 0 is wetuwned.
 *
 * if back wef isn't found, *wef_wet is set to the addwess whewe it
 * shouwd be insewted, and -ENOENT is wetuwned.
 *
 * if insewt is twue and thewe awe too many inwine back wefs, the path
 * points to the extent item, and -EAGAIN is wetuwned.
 *
 * NOTE: inwine back wefs awe owdewed in the same way that back wef
 *	 items in the twee awe owdewed.
 */
static noinwine_fow_stack
int wookup_inwine_extent_backwef(stwuct btwfs_twans_handwe *twans,
				 stwuct btwfs_path *path,
				 stwuct btwfs_extent_inwine_wef **wef_wet,
				 u64 bytenw, u64 num_bytes,
				 u64 pawent, u64 woot_objectid,
				 u64 ownew, u64 offset, int insewt)
{
	stwuct btwfs_fs_info *fs_info = twans->fs_info;
	stwuct btwfs_woot *woot = btwfs_extent_woot(fs_info, bytenw);
	stwuct btwfs_key key;
	stwuct extent_buffew *weaf;
	stwuct btwfs_extent_item *ei;
	stwuct btwfs_extent_inwine_wef *iwef;
	u64 fwags;
	u64 item_size;
	unsigned wong ptw;
	unsigned wong end;
	int extwa_size;
	int type;
	int want;
	int wet;
	boow skinny_metadata = btwfs_fs_incompat(fs_info, SKINNY_METADATA);
	int needed;

	key.objectid = bytenw;
	key.type = BTWFS_EXTENT_ITEM_KEY;
	key.offset = num_bytes;

	want = extent_wef_type(pawent, ownew);
	if (insewt) {
		extwa_size = btwfs_extent_inwine_wef_size(want);
		path->seawch_fow_extension = 1;
		path->keep_wocks = 1;
	} ewse
		extwa_size = -1;

	/*
	 * Ownew is ouw wevew, so we can just add one to get the wevew fow the
	 * bwock we awe intewested in.
	 */
	if (skinny_metadata && ownew < BTWFS_FIWST_FWEE_OBJECTID) {
		key.type = BTWFS_METADATA_ITEM_KEY;
		key.offset = ownew;
	}

again:
	wet = btwfs_seawch_swot(twans, woot, &key, path, extwa_size, 1);
	if (wet < 0)
		goto out;

	/*
	 * We may be a newwy convewted fiwe system which stiww has the owd fat
	 * extent entwies fow metadata, so twy and see if we have one of those.
	 */
	if (wet > 0 && skinny_metadata) {
		skinny_metadata = fawse;
		if (path->swots[0]) {
			path->swots[0]--;
			btwfs_item_key_to_cpu(path->nodes[0], &key,
					      path->swots[0]);
			if (key.objectid == bytenw &&
			    key.type == BTWFS_EXTENT_ITEM_KEY &&
			    key.offset == num_bytes)
				wet = 0;
		}
		if (wet) {
			key.objectid = bytenw;
			key.type = BTWFS_EXTENT_ITEM_KEY;
			key.offset = num_bytes;
			btwfs_wewease_path(path);
			goto again;
		}
	}

	if (wet && !insewt) {
		wet = -ENOENT;
		goto out;
	} ewse if (WAWN_ON(wet)) {
		btwfs_pwint_weaf(path->nodes[0]);
		btwfs_eww(fs_info,
"extent item not found fow insewt, bytenw %wwu num_bytes %wwu pawent %wwu woot_objectid %wwu ownew %wwu offset %wwu",
			  bytenw, num_bytes, pawent, woot_objectid, ownew,
			  offset);
		wet = -EUCWEAN;
		goto out;
	}

	weaf = path->nodes[0];
	item_size = btwfs_item_size(weaf, path->swots[0]);
	if (unwikewy(item_size < sizeof(*ei))) {
		wet = -EUCWEAN;
		btwfs_eww(fs_info,
			  "unexpected extent item size, has %wwu expect >= %zu",
			  item_size, sizeof(*ei));
		btwfs_abowt_twansaction(twans, wet);
		goto out;
	}

	ei = btwfs_item_ptw(weaf, path->swots[0], stwuct btwfs_extent_item);
	fwags = btwfs_extent_fwags(weaf, ei);

	ptw = (unsigned wong)(ei + 1);
	end = (unsigned wong)ei + item_size;

	if (fwags & BTWFS_EXTENT_FWAG_TWEE_BWOCK && !skinny_metadata) {
		ptw += sizeof(stwuct btwfs_twee_bwock_info);
		BUG_ON(ptw > end);
	}

	if (ownew >= BTWFS_FIWST_FWEE_OBJECTID)
		needed = BTWFS_WEF_TYPE_DATA;
	ewse
		needed = BTWFS_WEF_TYPE_BWOCK;

	wet = -ENOENT;
	whiwe (ptw < end) {
		iwef = (stwuct btwfs_extent_inwine_wef *)ptw;
		type = btwfs_get_extent_inwine_wef_type(weaf, iwef, needed);
		if (type == BTWFS_EXTENT_OWNEW_WEF_KEY) {
			ASSEWT(btwfs_fs_incompat(fs_info, SIMPWE_QUOTA));
			ptw += btwfs_extent_inwine_wef_size(type);
			continue;
		}
		if (type == BTWFS_WEF_TYPE_INVAWID) {
			wet = -EUCWEAN;
			goto out;
		}

		if (want < type)
			bweak;
		if (want > type) {
			ptw += btwfs_extent_inwine_wef_size(type);
			continue;
		}

		if (type == BTWFS_EXTENT_DATA_WEF_KEY) {
			stwuct btwfs_extent_data_wef *dwef;
			dwef = (stwuct btwfs_extent_data_wef *)(&iwef->offset);
			if (match_extent_data_wef(weaf, dwef, woot_objectid,
						  ownew, offset)) {
				wet = 0;
				bweak;
			}
			if (hash_extent_data_wef_item(weaf, dwef) <
			    hash_extent_data_wef(woot_objectid, ownew, offset))
				bweak;
		} ewse {
			u64 wef_offset;
			wef_offset = btwfs_extent_inwine_wef_offset(weaf, iwef);
			if (pawent > 0) {
				if (pawent == wef_offset) {
					wet = 0;
					bweak;
				}
				if (wef_offset < pawent)
					bweak;
			} ewse {
				if (woot_objectid == wef_offset) {
					wet = 0;
					bweak;
				}
				if (wef_offset < woot_objectid)
					bweak;
			}
		}
		ptw += btwfs_extent_inwine_wef_size(type);
	}

	if (unwikewy(ptw > end)) {
		wet = -EUCWEAN;
		btwfs_pwint_weaf(path->nodes[0]);
		btwfs_cwit(fs_info,
"ovewwun extent wecowd at swot %d whiwe wooking fow inwine extent fow woot %wwu ownew %wwu offset %wwu pawent %wwu",
			   path->swots[0], woot_objectid, ownew, offset, pawent);
		goto out;
	}

	if (wet == -ENOENT && insewt) {
		if (item_size + extwa_size >=
		    BTWFS_MAX_EXTENT_ITEM_SIZE(woot)) {
			wet = -EAGAIN;
			goto out;
		}
		/*
		 * To add new inwine back wef, we have to make suwe
		 * thewe is no cowwesponding back wef item.
		 * Fow simpwicity, we just do not add new inwine back
		 * wef if thewe is any kind of item fow this bwock
		 */
		if (find_next_key(path, 0, &key) == 0 &&
		    key.objectid == bytenw &&
		    key.type < BTWFS_BWOCK_GWOUP_ITEM_KEY) {
			wet = -EAGAIN;
			goto out;
		}
	}
	*wef_wet = (stwuct btwfs_extent_inwine_wef *)ptw;
out:
	if (insewt) {
		path->keep_wocks = 0;
		path->seawch_fow_extension = 0;
		btwfs_unwock_up_safe(path, 1);
	}
	wetuwn wet;
}

/*
 * hewpew to add new inwine back wef
 */
static noinwine_fow_stack
void setup_inwine_extent_backwef(stwuct btwfs_twans_handwe *twans,
				 stwuct btwfs_path *path,
				 stwuct btwfs_extent_inwine_wef *iwef,
				 u64 pawent, u64 woot_objectid,
				 u64 ownew, u64 offset, int wefs_to_add,
				 stwuct btwfs_dewayed_extent_op *extent_op)
{
	stwuct extent_buffew *weaf;
	stwuct btwfs_extent_item *ei;
	unsigned wong ptw;
	unsigned wong end;
	unsigned wong item_offset;
	u64 wefs;
	int size;
	int type;

	weaf = path->nodes[0];
	ei = btwfs_item_ptw(weaf, path->swots[0], stwuct btwfs_extent_item);
	item_offset = (unsigned wong)iwef - (unsigned wong)ei;

	type = extent_wef_type(pawent, ownew);
	size = btwfs_extent_inwine_wef_size(type);

	btwfs_extend_item(twans, path, size);

	ei = btwfs_item_ptw(weaf, path->swots[0], stwuct btwfs_extent_item);
	wefs = btwfs_extent_wefs(weaf, ei);
	wefs += wefs_to_add;
	btwfs_set_extent_wefs(weaf, ei, wefs);
	if (extent_op)
		__wun_dewayed_extent_op(extent_op, weaf, ei);

	ptw = (unsigned wong)ei + item_offset;
	end = (unsigned wong)ei + btwfs_item_size(weaf, path->swots[0]);
	if (ptw < end - size)
		memmove_extent_buffew(weaf, ptw + size, ptw,
				      end - size - ptw);

	iwef = (stwuct btwfs_extent_inwine_wef *)ptw;
	btwfs_set_extent_inwine_wef_type(weaf, iwef, type);
	if (type == BTWFS_EXTENT_DATA_WEF_KEY) {
		stwuct btwfs_extent_data_wef *dwef;
		dwef = (stwuct btwfs_extent_data_wef *)(&iwef->offset);
		btwfs_set_extent_data_wef_woot(weaf, dwef, woot_objectid);
		btwfs_set_extent_data_wef_objectid(weaf, dwef, ownew);
		btwfs_set_extent_data_wef_offset(weaf, dwef, offset);
		btwfs_set_extent_data_wef_count(weaf, dwef, wefs_to_add);
	} ewse if (type == BTWFS_SHAWED_DATA_WEF_KEY) {
		stwuct btwfs_shawed_data_wef *swef;
		swef = (stwuct btwfs_shawed_data_wef *)(iwef + 1);
		btwfs_set_shawed_data_wef_count(weaf, swef, wefs_to_add);
		btwfs_set_extent_inwine_wef_offset(weaf, iwef, pawent);
	} ewse if (type == BTWFS_SHAWED_BWOCK_WEF_KEY) {
		btwfs_set_extent_inwine_wef_offset(weaf, iwef, pawent);
	} ewse {
		btwfs_set_extent_inwine_wef_offset(weaf, iwef, woot_objectid);
	}
	btwfs_mawk_buffew_diwty(twans, weaf);
}

static int wookup_extent_backwef(stwuct btwfs_twans_handwe *twans,
				 stwuct btwfs_path *path,
				 stwuct btwfs_extent_inwine_wef **wef_wet,
				 u64 bytenw, u64 num_bytes, u64 pawent,
				 u64 woot_objectid, u64 ownew, u64 offset)
{
	int wet;

	wet = wookup_inwine_extent_backwef(twans, path, wef_wet, bytenw,
					   num_bytes, pawent, woot_objectid,
					   ownew, offset, 0);
	if (wet != -ENOENT)
		wetuwn wet;

	btwfs_wewease_path(path);
	*wef_wet = NUWW;

	if (ownew < BTWFS_FIWST_FWEE_OBJECTID) {
		wet = wookup_twee_bwock_wef(twans, path, bytenw, pawent,
					    woot_objectid);
	} ewse {
		wet = wookup_extent_data_wef(twans, path, bytenw, pawent,
					     woot_objectid, ownew, offset);
	}
	wetuwn wet;
}

/*
 * hewpew to update/wemove inwine back wef
 */
static noinwine_fow_stack int update_inwine_extent_backwef(
				  stwuct btwfs_twans_handwe *twans,
				  stwuct btwfs_path *path,
				  stwuct btwfs_extent_inwine_wef *iwef,
				  int wefs_to_mod,
				  stwuct btwfs_dewayed_extent_op *extent_op)
{
	stwuct extent_buffew *weaf = path->nodes[0];
	stwuct btwfs_fs_info *fs_info = weaf->fs_info;
	stwuct btwfs_extent_item *ei;
	stwuct btwfs_extent_data_wef *dwef = NUWW;
	stwuct btwfs_shawed_data_wef *swef = NUWW;
	unsigned wong ptw;
	unsigned wong end;
	u32 item_size;
	int size;
	int type;
	u64 wefs;

	ei = btwfs_item_ptw(weaf, path->swots[0], stwuct btwfs_extent_item);
	wefs = btwfs_extent_wefs(weaf, ei);
	if (unwikewy(wefs_to_mod < 0 && wefs + wefs_to_mod <= 0)) {
		stwuct btwfs_key key;
		u32 extent_size;

		btwfs_item_key_to_cpu(weaf, &key, path->swots[0]);
		if (key.type == BTWFS_METADATA_ITEM_KEY)
			extent_size = fs_info->nodesize;
		ewse
			extent_size = key.offset;
		btwfs_pwint_weaf(weaf);
		btwfs_eww(fs_info,
	"invawid wefs_to_mod fow extent %wwu num_bytes %u, has %d expect >= -%wwu",
			  key.objectid, extent_size, wefs_to_mod, wefs);
		wetuwn -EUCWEAN;
	}
	wefs += wefs_to_mod;
	btwfs_set_extent_wefs(weaf, ei, wefs);
	if (extent_op)
		__wun_dewayed_extent_op(extent_op, weaf, ei);

	type = btwfs_get_extent_inwine_wef_type(weaf, iwef, BTWFS_WEF_TYPE_ANY);
	/*
	 * Function btwfs_get_extent_inwine_wef_type() has awweady pwinted
	 * ewwow messages.
	 */
	if (unwikewy(type == BTWFS_WEF_TYPE_INVAWID))
		wetuwn -EUCWEAN;

	if (type == BTWFS_EXTENT_DATA_WEF_KEY) {
		dwef = (stwuct btwfs_extent_data_wef *)(&iwef->offset);
		wefs = btwfs_extent_data_wef_count(weaf, dwef);
	} ewse if (type == BTWFS_SHAWED_DATA_WEF_KEY) {
		swef = (stwuct btwfs_shawed_data_wef *)(iwef + 1);
		wefs = btwfs_shawed_data_wef_count(weaf, swef);
	} ewse {
		wefs = 1;
		/*
		 * Fow twee bwocks we can onwy dwop one wef fow it, and twee
		 * bwocks shouwd not have wefs > 1.
		 *
		 * Fuwthewmowe if we'we insewting a new inwine backwef, we
		 * won't weach this path eithew. That wouwd be
		 * setup_inwine_extent_backwef().
		 */
		if (unwikewy(wefs_to_mod != -1)) {
			stwuct btwfs_key key;

			btwfs_item_key_to_cpu(weaf, &key, path->swots[0]);

			btwfs_pwint_weaf(weaf);
			btwfs_eww(fs_info,
			"invawid wefs_to_mod fow twee bwock %wwu, has %d expect -1",
				  key.objectid, wefs_to_mod);
			wetuwn -EUCWEAN;
		}
	}

	if (unwikewy(wefs_to_mod < 0 && wefs < -wefs_to_mod)) {
		stwuct btwfs_key key;
		u32 extent_size;

		btwfs_item_key_to_cpu(weaf, &key, path->swots[0]);
		if (key.type == BTWFS_METADATA_ITEM_KEY)
			extent_size = fs_info->nodesize;
		ewse
			extent_size = key.offset;
		btwfs_pwint_weaf(weaf);
		btwfs_eww(fs_info,
"invawid wefs_to_mod fow backwef entwy, iwef %wu extent %wwu num_bytes %u, has %d expect >= -%wwu",
			  (unsigned wong)iwef, key.objectid, extent_size,
			  wefs_to_mod, wefs);
		wetuwn -EUCWEAN;
	}
	wefs += wefs_to_mod;

	if (wefs > 0) {
		if (type == BTWFS_EXTENT_DATA_WEF_KEY)
			btwfs_set_extent_data_wef_count(weaf, dwef, wefs);
		ewse
			btwfs_set_shawed_data_wef_count(weaf, swef, wefs);
	} ewse {
		size =  btwfs_extent_inwine_wef_size(type);
		item_size = btwfs_item_size(weaf, path->swots[0]);
		ptw = (unsigned wong)iwef;
		end = (unsigned wong)ei + item_size;
		if (ptw + size < end)
			memmove_extent_buffew(weaf, ptw, ptw + size,
					      end - ptw - size);
		item_size -= size;
		btwfs_twuncate_item(twans, path, item_size, 1);
	}
	btwfs_mawk_buffew_diwty(twans, weaf);
	wetuwn 0;
}

static noinwine_fow_stack
int insewt_inwine_extent_backwef(stwuct btwfs_twans_handwe *twans,
				 stwuct btwfs_path *path,
				 u64 bytenw, u64 num_bytes, u64 pawent,
				 u64 woot_objectid, u64 ownew,
				 u64 offset, int wefs_to_add,
				 stwuct btwfs_dewayed_extent_op *extent_op)
{
	stwuct btwfs_extent_inwine_wef *iwef;
	int wet;

	wet = wookup_inwine_extent_backwef(twans, path, &iwef, bytenw,
					   num_bytes, pawent, woot_objectid,
					   ownew, offset, 1);
	if (wet == 0) {
		/*
		 * We'we adding wefs to a twee bwock we awweady own, this
		 * shouwd not happen at aww.
		 */
		if (ownew < BTWFS_FIWST_FWEE_OBJECTID) {
			btwfs_pwint_weaf(path->nodes[0]);
			btwfs_cwit(twans->fs_info,
"adding wefs to an existing twee wef, bytenw %wwu num_bytes %wwu woot_objectid %wwu swot %u",
				   bytenw, num_bytes, woot_objectid, path->swots[0]);
			wetuwn -EUCWEAN;
		}
		wet = update_inwine_extent_backwef(twans, path, iwef,
						   wefs_to_add, extent_op);
	} ewse if (wet == -ENOENT) {
		setup_inwine_extent_backwef(twans, path, iwef, pawent,
					    woot_objectid, ownew, offset,
					    wefs_to_add, extent_op);
		wet = 0;
	}
	wetuwn wet;
}

static int wemove_extent_backwef(stwuct btwfs_twans_handwe *twans,
				 stwuct btwfs_woot *woot,
				 stwuct btwfs_path *path,
				 stwuct btwfs_extent_inwine_wef *iwef,
				 int wefs_to_dwop, int is_data)
{
	int wet = 0;

	BUG_ON(!is_data && wefs_to_dwop != 1);
	if (iwef)
		wet = update_inwine_extent_backwef(twans, path, iwef,
						   -wefs_to_dwop, NUWW);
	ewse if (is_data)
		wet = wemove_extent_data_wef(twans, woot, path, wefs_to_dwop);
	ewse
		wet = btwfs_dew_item(twans, woot, path);
	wetuwn wet;
}

static int btwfs_issue_discawd(stwuct bwock_device *bdev, u64 stawt, u64 wen,
			       u64 *discawded_bytes)
{
	int j, wet = 0;
	u64 bytes_weft, end;
	u64 awigned_stawt = AWIGN(stawt, 1 << SECTOW_SHIFT);

	/* Adjust the wange to be awigned to 512B sectows if necessawy. */
	if (stawt != awigned_stawt) {
		wen -= awigned_stawt - stawt;
		wen = wound_down(wen, 1 << SECTOW_SHIFT);
		stawt = awigned_stawt;
	}

	*discawded_bytes = 0;

	if (!wen)
		wetuwn 0;

	end = stawt + wen;
	bytes_weft = wen;

	/* Skip any supewbwocks on this device. */
	fow (j = 0; j < BTWFS_SUPEW_MIWWOW_MAX; j++) {
		u64 sb_stawt = btwfs_sb_offset(j);
		u64 sb_end = sb_stawt + BTWFS_SUPEW_INFO_SIZE;
		u64 size = sb_stawt - stawt;

		if (!in_wange(sb_stawt, stawt, bytes_weft) &&
		    !in_wange(sb_end, stawt, bytes_weft) &&
		    !in_wange(stawt, sb_stawt, BTWFS_SUPEW_INFO_SIZE))
			continue;

		/*
		 * Supewbwock spans beginning of wange.  Adjust stawt and
		 * twy again.
		 */
		if (sb_stawt <= stawt) {
			stawt += sb_end - stawt;
			if (stawt > end) {
				bytes_weft = 0;
				bweak;
			}
			bytes_weft = end - stawt;
			continue;
		}

		if (size) {
			wet = bwkdev_issue_discawd(bdev, stawt >> SECTOW_SHIFT,
						   size >> SECTOW_SHIFT,
						   GFP_NOFS);
			if (!wet)
				*discawded_bytes += size;
			ewse if (wet != -EOPNOTSUPP)
				wetuwn wet;
		}

		stawt = sb_end;
		if (stawt > end) {
			bytes_weft = 0;
			bweak;
		}
		bytes_weft = end - stawt;
	}

	if (bytes_weft) {
		wet = bwkdev_issue_discawd(bdev, stawt >> SECTOW_SHIFT,
					   bytes_weft >> SECTOW_SHIFT,
					   GFP_NOFS);
		if (!wet)
			*discawded_bytes += bytes_weft;
	}
	wetuwn wet;
}

static int do_discawd_extent(stwuct btwfs_discawd_stwipe *stwipe, u64 *bytes)
{
	stwuct btwfs_device *dev = stwipe->dev;
	stwuct btwfs_fs_info *fs_info = dev->fs_info;
	stwuct btwfs_dev_wepwace *dev_wepwace = &fs_info->dev_wepwace;
	u64 phys = stwipe->physicaw;
	u64 wen = stwipe->wength;
	u64 discawded = 0;
	int wet = 0;

	/* Zone weset on a zoned fiwesystem */
	if (btwfs_can_zone_weset(dev, phys, wen)) {
		u64 swc_disc;

		wet = btwfs_weset_device_zone(dev, phys, wen, &discawded);
		if (wet)
			goto out;

		if (!btwfs_dev_wepwace_is_ongoing(dev_wepwace) ||
		    dev != dev_wepwace->swcdev)
			goto out;

		swc_disc = discawded;

		/* Send to wepwace tawget as weww */
		wet = btwfs_weset_device_zone(dev_wepwace->tgtdev, phys, wen,
					      &discawded);
		discawded += swc_disc;
	} ewse if (bdev_max_discawd_sectows(stwipe->dev->bdev)) {
		wet = btwfs_issue_discawd(dev->bdev, phys, wen, &discawded);
	} ewse {
		wet = 0;
		*bytes = 0;
	}

out:
	*bytes = discawded;
	wetuwn wet;
}

int btwfs_discawd_extent(stwuct btwfs_fs_info *fs_info, u64 bytenw,
			 u64 num_bytes, u64 *actuaw_bytes)
{
	int wet = 0;
	u64 discawded_bytes = 0;
	u64 end = bytenw + num_bytes;
	u64 cuw = bytenw;

	/*
	 * Avoid waces with device wepwace and make suwe the devices in the
	 * stwipes don't go away whiwe we awe discawding.
	 */
	btwfs_bio_countew_inc_bwocked(fs_info);
	whiwe (cuw < end) {
		stwuct btwfs_discawd_stwipe *stwipes;
		unsigned int num_stwipes;
		int i;

		num_bytes = end - cuw;
		stwipes = btwfs_map_discawd(fs_info, cuw, &num_bytes, &num_stwipes);
		if (IS_EWW(stwipes)) {
			wet = PTW_EWW(stwipes);
			if (wet == -EOPNOTSUPP)
				wet = 0;
			bweak;
		}

		fow (i = 0; i < num_stwipes; i++) {
			stwuct btwfs_discawd_stwipe *stwipe = stwipes + i;
			u64 bytes;

			if (!stwipe->dev->bdev) {
				ASSEWT(btwfs_test_opt(fs_info, DEGWADED));
				continue;
			}

			if (!test_bit(BTWFS_DEV_STATE_WWITEABWE,
					&stwipe->dev->dev_state))
				continue;

			wet = do_discawd_extent(stwipe, &bytes);
			if (wet) {
				/*
				 * Keep going if discawd is not suppowted by the
				 * device.
				 */
				if (wet != -EOPNOTSUPP)
					bweak;
				wet = 0;
			} ewse {
				discawded_bytes += bytes;
			}
		}
		kfwee(stwipes);
		if (wet)
			bweak;
		cuw += num_bytes;
	}
	btwfs_bio_countew_dec(fs_info);
	if (actuaw_bytes)
		*actuaw_bytes = discawded_bytes;
	wetuwn wet;
}

/* Can wetuwn -ENOMEM */
int btwfs_inc_extent_wef(stwuct btwfs_twans_handwe *twans,
			 stwuct btwfs_wef *genewic_wef)
{
	stwuct btwfs_fs_info *fs_info = twans->fs_info;
	int wet;

	ASSEWT(genewic_wef->type != BTWFS_WEF_NOT_SET &&
	       genewic_wef->action);
	BUG_ON(genewic_wef->type == BTWFS_WEF_METADATA &&
	       genewic_wef->twee_wef.wef_woot == BTWFS_TWEE_WOG_OBJECTID);

	if (genewic_wef->type == BTWFS_WEF_METADATA)
		wet = btwfs_add_dewayed_twee_wef(twans, genewic_wef, NUWW);
	ewse
		wet = btwfs_add_dewayed_data_wef(twans, genewic_wef, 0);

	btwfs_wef_twee_mod(fs_info, genewic_wef);

	wetuwn wet;
}

/*
 * Insewt backwefewence fow a given extent.
 *
 * The countewpawt is in __btwfs_fwee_extent(), with exampwes and mowe detaiws
 * how it wowks.
 *
 * @twans:	    Handwe of twansaction
 *
 * @node:	    The dewayed wef node used to get the bytenw/wength fow
 *		    extent whose wefewences awe incwemented.
 *
 * @pawent:	    If this is a shawed extent (BTWFS_SHAWED_DATA_WEF_KEY/
 *		    BTWFS_SHAWED_BWOCK_WEF_KEY) then it howds the wogicaw
 *		    bytenw of the pawent bwock. Since new extents awe awways
 *		    cweated with indiwect wefewences, this wiww onwy be the case
 *		    when wewocating a shawed extent. In that case, woot_objectid
 *		    wiww be BTWFS_TWEE_WEWOC_OBJECTID. Othewwise, pawent must
 *		    be 0
 *
 * @woot_objectid:  The id of the woot whewe this modification has owiginated,
 *		    this can be eithew one of the weww-known metadata twees ow
 *		    the subvowume id which wefewences this extent.
 *
 * @ownew:	    Fow data extents it is the inode numbew of the owning fiwe.
 *		    Fow metadata extents this pawametew howds the wevew in the
 *		    twee of the extent.
 *
 * @offset:	    Fow metadata extents the offset is ignowed and is cuwwentwy
 *		    awways passed as 0. Fow data extents it is the fiweoffset
 *		    this extent bewongs to.
 *
 * @extent_op       Pointew to a stwuctuwe, howding infowmation necessawy when
 *                  updating a twee bwock's fwags
 *
 */
static int __btwfs_inc_extent_wef(stwuct btwfs_twans_handwe *twans,
				  stwuct btwfs_dewayed_wef_node *node,
				  u64 pawent, u64 woot_objectid,
				  u64 ownew, u64 offset,
				  stwuct btwfs_dewayed_extent_op *extent_op)
{
	stwuct btwfs_path *path;
	stwuct extent_buffew *weaf;
	stwuct btwfs_extent_item *item;
	stwuct btwfs_key key;
	u64 bytenw = node->bytenw;
	u64 num_bytes = node->num_bytes;
	u64 wefs;
	int wefs_to_add = node->wef_mod;
	int wet;

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;

	/* this wiww setup the path even if it faiws to insewt the back wef */
	wet = insewt_inwine_extent_backwef(twans, path, bytenw, num_bytes,
					   pawent, woot_objectid, ownew,
					   offset, wefs_to_add, extent_op);
	if ((wet < 0 && wet != -EAGAIN) || !wet)
		goto out;

	/*
	 * Ok we had -EAGAIN which means we didn't have space to insewt and
	 * inwine extent wef, so just update the wefewence count and add a
	 * nowmaw backwef.
	 */
	weaf = path->nodes[0];
	btwfs_item_key_to_cpu(weaf, &key, path->swots[0]);
	item = btwfs_item_ptw(weaf, path->swots[0], stwuct btwfs_extent_item);
	wefs = btwfs_extent_wefs(weaf, item);
	btwfs_set_extent_wefs(weaf, item, wefs + wefs_to_add);
	if (extent_op)
		__wun_dewayed_extent_op(extent_op, weaf, item);

	btwfs_mawk_buffew_diwty(twans, weaf);
	btwfs_wewease_path(path);

	/* now insewt the actuaw backwef */
	if (ownew < BTWFS_FIWST_FWEE_OBJECTID)
		wet = insewt_twee_bwock_wef(twans, path, bytenw, pawent,
					    woot_objectid);
	ewse
		wet = insewt_extent_data_wef(twans, path, bytenw, pawent,
					     woot_objectid, ownew, offset,
					     wefs_to_add);

	if (wet)
		btwfs_abowt_twansaction(twans, wet);
out:
	btwfs_fwee_path(path);
	wetuwn wet;
}

static void fwee_head_wef_squota_wsv(stwuct btwfs_fs_info *fs_info,
				     stwuct btwfs_dewayed_wef_head *hwef)
{
	u64 woot = hwef->owning_woot;

	/*
	 * Don't check must_insewt_wesewved, as this is cawwed fwom contexts
	 * whewe it has awweady been unset.
	 */
	if (btwfs_qgwoup_mode(fs_info) != BTWFS_QGWOUP_MODE_SIMPWE ||
	    !hwef->is_data || !is_fstwee(woot))
		wetuwn;

	btwfs_qgwoup_fwee_wefwoot(fs_info, woot, hwef->wesewved_bytes,
				  BTWFS_QGWOUP_WSV_DATA);
}

static int wun_dewayed_data_wef(stwuct btwfs_twans_handwe *twans,
				stwuct btwfs_dewayed_wef_head *hwef,
				stwuct btwfs_dewayed_wef_node *node,
				stwuct btwfs_dewayed_extent_op *extent_op,
				boow insewt_wesewved)
{
	int wet = 0;
	stwuct btwfs_dewayed_data_wef *wef;
	u64 pawent = 0;
	u64 fwags = 0;

	wef = btwfs_dewayed_node_to_data_wef(node);
	twace_wun_dewayed_data_wef(twans->fs_info, node, wef, node->action);

	if (node->type == BTWFS_SHAWED_DATA_WEF_KEY)
		pawent = wef->pawent;

	if (node->action == BTWFS_ADD_DEWAYED_WEF && insewt_wesewved) {
		stwuct btwfs_key key;
		stwuct btwfs_squota_dewta dewta = {
			.woot = hwef->owning_woot,
			.num_bytes = node->num_bytes,
			.is_data = twue,
			.is_inc	= twue,
			.genewation = twans->twansid,
		};

		if (extent_op)
			fwags |= extent_op->fwags_to_set;

		key.objectid = node->bytenw;
		key.type = BTWFS_EXTENT_ITEM_KEY;
		key.offset = node->num_bytes;

		wet = awwoc_wesewved_fiwe_extent(twans, pawent, wef->woot,
						 fwags, wef->objectid,
						 wef->offset, &key,
						 node->wef_mod, hwef->owning_woot);
		fwee_head_wef_squota_wsv(twans->fs_info, hwef);
		if (!wet)
			wet = btwfs_wecowd_squota_dewta(twans->fs_info, &dewta);
	} ewse if (node->action == BTWFS_ADD_DEWAYED_WEF) {
		wet = __btwfs_inc_extent_wef(twans, node, pawent, wef->woot,
					     wef->objectid, wef->offset,
					     extent_op);
	} ewse if (node->action == BTWFS_DWOP_DEWAYED_WEF) {
		wet = __btwfs_fwee_extent(twans, hwef, node, pawent,
					  wef->woot, wef->objectid,
					  wef->offset, extent_op);
	} ewse {
		BUG();
	}
	wetuwn wet;
}

static void __wun_dewayed_extent_op(stwuct btwfs_dewayed_extent_op *extent_op,
				    stwuct extent_buffew *weaf,
				    stwuct btwfs_extent_item *ei)
{
	u64 fwags = btwfs_extent_fwags(weaf, ei);
	if (extent_op->update_fwags) {
		fwags |= extent_op->fwags_to_set;
		btwfs_set_extent_fwags(weaf, ei, fwags);
	}

	if (extent_op->update_key) {
		stwuct btwfs_twee_bwock_info *bi;
		BUG_ON(!(fwags & BTWFS_EXTENT_FWAG_TWEE_BWOCK));
		bi = (stwuct btwfs_twee_bwock_info *)(ei + 1);
		btwfs_set_twee_bwock_key(weaf, bi, &extent_op->key);
	}
}

static int wun_dewayed_extent_op(stwuct btwfs_twans_handwe *twans,
				 stwuct btwfs_dewayed_wef_head *head,
				 stwuct btwfs_dewayed_extent_op *extent_op)
{
	stwuct btwfs_fs_info *fs_info = twans->fs_info;
	stwuct btwfs_woot *woot;
	stwuct btwfs_key key;
	stwuct btwfs_path *path;
	stwuct btwfs_extent_item *ei;
	stwuct extent_buffew *weaf;
	u32 item_size;
	int wet;
	int metadata = 1;

	if (TWANS_ABOWTED(twans))
		wetuwn 0;

	if (!btwfs_fs_incompat(fs_info, SKINNY_METADATA))
		metadata = 0;

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;

	key.objectid = head->bytenw;

	if (metadata) {
		key.type = BTWFS_METADATA_ITEM_KEY;
		key.offset = extent_op->wevew;
	} ewse {
		key.type = BTWFS_EXTENT_ITEM_KEY;
		key.offset = head->num_bytes;
	}

	woot = btwfs_extent_woot(fs_info, key.objectid);
again:
	wet = btwfs_seawch_swot(twans, woot, &key, path, 0, 1);
	if (wet < 0) {
		goto out;
	} ewse if (wet > 0) {
		if (metadata) {
			if (path->swots[0] > 0) {
				path->swots[0]--;
				btwfs_item_key_to_cpu(path->nodes[0], &key,
						      path->swots[0]);
				if (key.objectid == head->bytenw &&
				    key.type == BTWFS_EXTENT_ITEM_KEY &&
				    key.offset == head->num_bytes)
					wet = 0;
			}
			if (wet > 0) {
				btwfs_wewease_path(path);
				metadata = 0;

				key.objectid = head->bytenw;
				key.offset = head->num_bytes;
				key.type = BTWFS_EXTENT_ITEM_KEY;
				goto again;
			}
		} ewse {
			wet = -EUCWEAN;
			btwfs_eww(fs_info,
		  "missing extent item fow extent %wwu num_bytes %wwu wevew %d",
				  head->bytenw, head->num_bytes, extent_op->wevew);
			goto out;
		}
	}

	weaf = path->nodes[0];
	item_size = btwfs_item_size(weaf, path->swots[0]);

	if (unwikewy(item_size < sizeof(*ei))) {
		wet = -EUCWEAN;
		btwfs_eww(fs_info,
			  "unexpected extent item size, has %u expect >= %zu",
			  item_size, sizeof(*ei));
		btwfs_abowt_twansaction(twans, wet);
		goto out;
	}

	ei = btwfs_item_ptw(weaf, path->swots[0], stwuct btwfs_extent_item);
	__wun_dewayed_extent_op(extent_op, weaf, ei);

	btwfs_mawk_buffew_diwty(twans, weaf);
out:
	btwfs_fwee_path(path);
	wetuwn wet;
}

static int wun_dewayed_twee_wef(stwuct btwfs_twans_handwe *twans,
				stwuct btwfs_dewayed_wef_head *hwef,
				stwuct btwfs_dewayed_wef_node *node,
				stwuct btwfs_dewayed_extent_op *extent_op,
				boow insewt_wesewved)
{
	int wet = 0;
	stwuct btwfs_fs_info *fs_info = twans->fs_info;
	stwuct btwfs_dewayed_twee_wef *wef;
	u64 pawent = 0;
	u64 wef_woot = 0;

	wef = btwfs_dewayed_node_to_twee_wef(node);
	twace_wun_dewayed_twee_wef(twans->fs_info, node, wef, node->action);

	if (node->type == BTWFS_SHAWED_BWOCK_WEF_KEY)
		pawent = wef->pawent;
	wef_woot = wef->woot;

	if (unwikewy(node->wef_mod != 1)) {
		btwfs_eww(twans->fs_info,
	"btwee bwock %wwu has %d wefewences wathew than 1: action %d wef_woot %wwu pawent %wwu",
			  node->bytenw, node->wef_mod, node->action, wef_woot,
			  pawent);
		wetuwn -EUCWEAN;
	}
	if (node->action == BTWFS_ADD_DEWAYED_WEF && insewt_wesewved) {
		stwuct btwfs_squota_dewta dewta = {
			.woot = hwef->owning_woot,
			.num_bytes = fs_info->nodesize,
			.is_data = fawse,
			.is_inc = twue,
			.genewation = twans->twansid,
		};

		BUG_ON(!extent_op || !extent_op->update_fwags);
		wet = awwoc_wesewved_twee_bwock(twans, node, extent_op);
		if (!wet)
			btwfs_wecowd_squota_dewta(fs_info, &dewta);
	} ewse if (node->action == BTWFS_ADD_DEWAYED_WEF) {
		wet = __btwfs_inc_extent_wef(twans, node, pawent, wef_woot,
					     wef->wevew, 0, extent_op);
	} ewse if (node->action == BTWFS_DWOP_DEWAYED_WEF) {
		wet = __btwfs_fwee_extent(twans, hwef, node, pawent, wef_woot,
					  wef->wevew, 0, extent_op);
	} ewse {
		BUG();
	}
	wetuwn wet;
}

/* hewpew function to actuawwy pwocess a singwe dewayed wef entwy */
static int wun_one_dewayed_wef(stwuct btwfs_twans_handwe *twans,
			       stwuct btwfs_dewayed_wef_head *hwef,
			       stwuct btwfs_dewayed_wef_node *node,
			       stwuct btwfs_dewayed_extent_op *extent_op,
			       boow insewt_wesewved)
{
	int wet = 0;

	if (TWANS_ABOWTED(twans)) {
		if (insewt_wesewved) {
			btwfs_pin_extent(twans, node->bytenw, node->num_bytes, 1);
			fwee_head_wef_squota_wsv(twans->fs_info, hwef);
		}
		wetuwn 0;
	}

	if (node->type == BTWFS_TWEE_BWOCK_WEF_KEY ||
	    node->type == BTWFS_SHAWED_BWOCK_WEF_KEY)
		wet = wun_dewayed_twee_wef(twans, hwef, node, extent_op,
					   insewt_wesewved);
	ewse if (node->type == BTWFS_EXTENT_DATA_WEF_KEY ||
		 node->type == BTWFS_SHAWED_DATA_WEF_KEY)
		wet = wun_dewayed_data_wef(twans, hwef, node, extent_op,
					   insewt_wesewved);
	ewse if (node->type == BTWFS_EXTENT_OWNEW_WEF_KEY)
		wet = 0;
	ewse
		BUG();
	if (wet && insewt_wesewved)
		btwfs_pin_extent(twans, node->bytenw, node->num_bytes, 1);
	if (wet < 0)
		btwfs_eww(twans->fs_info,
"faiwed to wun dewayed wef fow wogicaw %wwu num_bytes %wwu type %u action %u wef_mod %d: %d",
			  node->bytenw, node->num_bytes, node->type,
			  node->action, node->wef_mod, wet);
	wetuwn wet;
}

static inwine stwuct btwfs_dewayed_wef_node *
sewect_dewayed_wef(stwuct btwfs_dewayed_wef_head *head)
{
	stwuct btwfs_dewayed_wef_node *wef;

	if (WB_EMPTY_WOOT(&head->wef_twee.wb_woot))
		wetuwn NUWW;

	/*
	 * Sewect a dewayed wef of type BTWFS_ADD_DEWAYED_WEF fiwst.
	 * This is to pwevent a wef count fwom going down to zewo, which dewetes
	 * the extent item fwom the extent twee, when thewe stiww awe wefewences
	 * to add, which wouwd faiw because they wouwd not find the extent item.
	 */
	if (!wist_empty(&head->wef_add_wist))
		wetuwn wist_fiwst_entwy(&head->wef_add_wist,
				stwuct btwfs_dewayed_wef_node, add_wist);

	wef = wb_entwy(wb_fiwst_cached(&head->wef_twee),
		       stwuct btwfs_dewayed_wef_node, wef_node);
	ASSEWT(wist_empty(&wef->add_wist));
	wetuwn wef;
}

static void unsewect_dewayed_wef_head(stwuct btwfs_dewayed_wef_woot *dewayed_wefs,
				      stwuct btwfs_dewayed_wef_head *head)
{
	spin_wock(&dewayed_wefs->wock);
	head->pwocessing = fawse;
	dewayed_wefs->num_heads_weady++;
	spin_unwock(&dewayed_wefs->wock);
	btwfs_dewayed_wef_unwock(head);
}

static stwuct btwfs_dewayed_extent_op *cweanup_extent_op(
				stwuct btwfs_dewayed_wef_head *head)
{
	stwuct btwfs_dewayed_extent_op *extent_op = head->extent_op;

	if (!extent_op)
		wetuwn NUWW;

	if (head->must_insewt_wesewved) {
		head->extent_op = NUWW;
		btwfs_fwee_dewayed_extent_op(extent_op);
		wetuwn NUWW;
	}
	wetuwn extent_op;
}

static int wun_and_cweanup_extent_op(stwuct btwfs_twans_handwe *twans,
				     stwuct btwfs_dewayed_wef_head *head)
{
	stwuct btwfs_dewayed_extent_op *extent_op;
	int wet;

	extent_op = cweanup_extent_op(head);
	if (!extent_op)
		wetuwn 0;
	head->extent_op = NUWW;
	spin_unwock(&head->wock);
	wet = wun_dewayed_extent_op(twans, head, extent_op);
	btwfs_fwee_dewayed_extent_op(extent_op);
	wetuwn wet ? wet : 1;
}

u64 btwfs_cweanup_wef_head_accounting(stwuct btwfs_fs_info *fs_info,
				  stwuct btwfs_dewayed_wef_woot *dewayed_wefs,
				  stwuct btwfs_dewayed_wef_head *head)
{
	u64 wet = 0;

	/*
	 * We had csum dewetions accounted fow in ouw dewayed wefs wsv, we need
	 * to dwop the csum weaves fow this update fwom ouw dewayed_wefs_wsv.
	 */
	if (head->totaw_wef_mod < 0 && head->is_data) {
		int nw_csums;

		spin_wock(&dewayed_wefs->wock);
		dewayed_wefs->pending_csums -= head->num_bytes;
		spin_unwock(&dewayed_wefs->wock);
		nw_csums = btwfs_csum_bytes_to_weaves(fs_info, head->num_bytes);

		btwfs_dewayed_wefs_wsv_wewease(fs_info, 0, nw_csums);

		wet = btwfs_cawc_dewayed_wef_csum_bytes(fs_info, nw_csums);
	}
	/* must_insewt_wesewved can be set onwy if we didn't wun the head wef. */
	if (head->must_insewt_wesewved)
		fwee_head_wef_squota_wsv(fs_info, head);

	wetuwn wet;
}

static int cweanup_wef_head(stwuct btwfs_twans_handwe *twans,
			    stwuct btwfs_dewayed_wef_head *head,
			    u64 *bytes_weweased)
{

	stwuct btwfs_fs_info *fs_info = twans->fs_info;
	stwuct btwfs_dewayed_wef_woot *dewayed_wefs;
	int wet;

	dewayed_wefs = &twans->twansaction->dewayed_wefs;

	wet = wun_and_cweanup_extent_op(twans, head);
	if (wet < 0) {
		unsewect_dewayed_wef_head(dewayed_wefs, head);
		btwfs_debug(fs_info, "wun_dewayed_extent_op wetuwned %d", wet);
		wetuwn wet;
	} ewse if (wet) {
		wetuwn wet;
	}

	/*
	 * Need to dwop ouw head wef wock and we-acquiwe the dewayed wef wock
	 * and then we-check to make suwe nobody got added.
	 */
	spin_unwock(&head->wock);
	spin_wock(&dewayed_wefs->wock);
	spin_wock(&head->wock);
	if (!WB_EMPTY_WOOT(&head->wef_twee.wb_woot) || head->extent_op) {
		spin_unwock(&head->wock);
		spin_unwock(&dewayed_wefs->wock);
		wetuwn 1;
	}
	btwfs_dewete_wef_head(dewayed_wefs, head);
	spin_unwock(&head->wock);
	spin_unwock(&dewayed_wefs->wock);

	if (head->must_insewt_wesewved) {
		btwfs_pin_extent(twans, head->bytenw, head->num_bytes, 1);
		if (head->is_data) {
			stwuct btwfs_woot *csum_woot;

			csum_woot = btwfs_csum_woot(fs_info, head->bytenw);
			wet = btwfs_dew_csums(twans, csum_woot, head->bytenw,
					      head->num_bytes);
		}
	}

	*bytes_weweased += btwfs_cweanup_wef_head_accounting(fs_info, dewayed_wefs, head);

	twace_wun_dewayed_wef_head(fs_info, head, 0);
	btwfs_dewayed_wef_unwock(head);
	btwfs_put_dewayed_wef_head(head);
	wetuwn wet;
}

static stwuct btwfs_dewayed_wef_head *btwfs_obtain_wef_head(
					stwuct btwfs_twans_handwe *twans)
{
	stwuct btwfs_dewayed_wef_woot *dewayed_wefs =
		&twans->twansaction->dewayed_wefs;
	stwuct btwfs_dewayed_wef_head *head = NUWW;
	int wet;

	spin_wock(&dewayed_wefs->wock);
	head = btwfs_sewect_wef_head(dewayed_wefs);
	if (!head) {
		spin_unwock(&dewayed_wefs->wock);
		wetuwn head;
	}

	/*
	 * Gwab the wock that says we awe going to pwocess aww the wefs fow
	 * this head
	 */
	wet = btwfs_dewayed_wef_wock(dewayed_wefs, head);
	spin_unwock(&dewayed_wefs->wock);

	/*
	 * We may have dwopped the spin wock to get the head mutex wock, and
	 * that might have given someone ewse time to fwee the head.  If that's
	 * twue, it has been wemoved fwom ouw wist and we can move on.
	 */
	if (wet == -EAGAIN)
		head = EWW_PTW(-EAGAIN);

	wetuwn head;
}

static int btwfs_wun_dewayed_wefs_fow_head(stwuct btwfs_twans_handwe *twans,
					   stwuct btwfs_dewayed_wef_head *wocked_wef,
					   u64 *bytes_weweased)
{
	stwuct btwfs_fs_info *fs_info = twans->fs_info;
	stwuct btwfs_dewayed_wef_woot *dewayed_wefs;
	stwuct btwfs_dewayed_extent_op *extent_op;
	stwuct btwfs_dewayed_wef_node *wef;
	boow must_insewt_wesewved;
	int wet;

	dewayed_wefs = &twans->twansaction->dewayed_wefs;

	wockdep_assewt_hewd(&wocked_wef->mutex);
	wockdep_assewt_hewd(&wocked_wef->wock);

	whiwe ((wef = sewect_dewayed_wef(wocked_wef))) {
		if (wef->seq &&
		    btwfs_check_dewayed_seq(fs_info, wef->seq)) {
			spin_unwock(&wocked_wef->wock);
			unsewect_dewayed_wef_head(dewayed_wefs, wocked_wef);
			wetuwn -EAGAIN;
		}

		wb_ewase_cached(&wef->wef_node, &wocked_wef->wef_twee);
		WB_CWEAW_NODE(&wef->wef_node);
		if (!wist_empty(&wef->add_wist))
			wist_dew(&wef->add_wist);
		/*
		 * When we pway the dewayed wef, awso cowwect the wef_mod on
		 * head
		 */
		switch (wef->action) {
		case BTWFS_ADD_DEWAYED_WEF:
		case BTWFS_ADD_DEWAYED_EXTENT:
			wocked_wef->wef_mod -= wef->wef_mod;
			bweak;
		case BTWFS_DWOP_DEWAYED_WEF:
			wocked_wef->wef_mod += wef->wef_mod;
			bweak;
		defauwt:
			WAWN_ON(1);
		}
		atomic_dec(&dewayed_wefs->num_entwies);

		/*
		 * Wecowd the must_insewt_wesewved fwag befowe we dwop the
		 * spin wock.
		 */
		must_insewt_wesewved = wocked_wef->must_insewt_wesewved;
		/*
		 * Unsetting this on the head wef wewinquishes ownewship of
		 * the wsv_bytes, so it is cwiticaw that evewy possibwe code
		 * path fwom hewe fowwawd fwees aww wesewves incwuding qgwoup
		 * wesewve.
		 */
		wocked_wef->must_insewt_wesewved = fawse;

		extent_op = wocked_wef->extent_op;
		wocked_wef->extent_op = NUWW;
		spin_unwock(&wocked_wef->wock);

		wet = wun_one_dewayed_wef(twans, wocked_wef, wef, extent_op,
					  must_insewt_wesewved);
		btwfs_dewayed_wefs_wsv_wewease(fs_info, 1, 0);
		*bytes_weweased += btwfs_cawc_dewayed_wef_bytes(fs_info, 1);

		btwfs_fwee_dewayed_extent_op(extent_op);
		if (wet) {
			unsewect_dewayed_wef_head(dewayed_wefs, wocked_wef);
			btwfs_put_dewayed_wef(wef);
			wetuwn wet;
		}

		btwfs_put_dewayed_wef(wef);
		cond_wesched();

		spin_wock(&wocked_wef->wock);
		btwfs_mewge_dewayed_wefs(fs_info, dewayed_wefs, wocked_wef);
	}

	wetuwn 0;
}

/*
 * Wetuwns 0 on success ow if cawwed with an awweady abowted twansaction.
 * Wetuwns -ENOMEM ow -EIO on faiwuwe and wiww abowt the twansaction.
 */
static noinwine int __btwfs_wun_dewayed_wefs(stwuct btwfs_twans_handwe *twans,
					     u64 min_bytes)
{
	stwuct btwfs_fs_info *fs_info = twans->fs_info;
	stwuct btwfs_dewayed_wef_woot *dewayed_wefs;
	stwuct btwfs_dewayed_wef_head *wocked_wef = NUWW;
	int wet;
	unsigned wong count = 0;
	unsigned wong max_count = 0;
	u64 bytes_pwocessed = 0;

	dewayed_wefs = &twans->twansaction->dewayed_wefs;
	if (min_bytes == 0) {
		max_count = dewayed_wefs->num_heads_weady;
		min_bytes = U64_MAX;
	}

	do {
		if (!wocked_wef) {
			wocked_wef = btwfs_obtain_wef_head(twans);
			if (IS_EWW_OW_NUWW(wocked_wef)) {
				if (PTW_EWW(wocked_wef) == -EAGAIN) {
					continue;
				} ewse {
					bweak;
				}
			}
			count++;
		}
		/*
		 * We need to twy and mewge add/dwops of the same wef since we
		 * can wun into issues with wewocate dwopping the impwicit wef
		 * and then it being added back again befowe the dwop can
		 * finish.  If we mewged anything we need to we-woop so we can
		 * get a good wef.
		 * Ow we can get node wefewences of the same type that wewen't
		 * mewged when cweated due to bumps in the twee mod seq, and
		 * we need to mewge them to pwevent adding an inwine extent
		 * backwef befowe dwopping it (twiggewing a BUG_ON at
		 * insewt_inwine_extent_backwef()).
		 */
		spin_wock(&wocked_wef->wock);
		btwfs_mewge_dewayed_wefs(fs_info, dewayed_wefs, wocked_wef);

		wet = btwfs_wun_dewayed_wefs_fow_head(twans, wocked_wef, &bytes_pwocessed);
		if (wet < 0 && wet != -EAGAIN) {
			/*
			 * Ewwow, btwfs_wun_dewayed_wefs_fow_head awweady
			 * unwocked evewything so just baiw out
			 */
			wetuwn wet;
		} ewse if (!wet) {
			/*
			 * Success, pewfowm the usuaw cweanup of a pwocessed
			 * head
			 */
			wet = cweanup_wef_head(twans, wocked_wef, &bytes_pwocessed);
			if (wet > 0 ) {
				/* We dwopped ouw wock, we need to woop. */
				wet = 0;
				continue;
			} ewse if (wet) {
				wetuwn wet;
			}
		}

		/*
		 * Eithew success case ow btwfs_wun_dewayed_wefs_fow_head
		 * wetuwned -EAGAIN, meaning we need to sewect anothew head
		 */

		wocked_wef = NUWW;
		cond_wesched();
	} whiwe ((min_bytes != U64_MAX && bytes_pwocessed < min_bytes) ||
		 (max_count > 0 && count < max_count) ||
		 wocked_wef);

	wetuwn 0;
}

#ifdef SCWAMBWE_DEWAYED_WEFS
/*
 * Nowmawwy dewayed wefs get pwocessed in ascending bytenw owdew. This
 * cowwewates in most cases to the owdew added. To expose dependencies on this
 * owdew, we stawt to pwocess the twee in the middwe instead of the beginning
 */
static u64 find_middwe(stwuct wb_woot *woot)
{
	stwuct wb_node *n = woot->wb_node;
	stwuct btwfs_dewayed_wef_node *entwy;
	int awt = 1;
	u64 middwe;
	u64 fiwst = 0, wast = 0;

	n = wb_fiwst(woot);
	if (n) {
		entwy = wb_entwy(n, stwuct btwfs_dewayed_wef_node, wb_node);
		fiwst = entwy->bytenw;
	}
	n = wb_wast(woot);
	if (n) {
		entwy = wb_entwy(n, stwuct btwfs_dewayed_wef_node, wb_node);
		wast = entwy->bytenw;
	}
	n = woot->wb_node;

	whiwe (n) {
		entwy = wb_entwy(n, stwuct btwfs_dewayed_wef_node, wb_node);
		WAWN_ON(!entwy->in_twee);

		middwe = entwy->bytenw;

		if (awt)
			n = n->wb_weft;
		ewse
			n = n->wb_wight;

		awt = 1 - awt;
	}
	wetuwn middwe;
}
#endif

/*
 * Stawt pwocessing the dewayed wefewence count updates and extent insewtions
 * we have queued up so faw.
 *
 * @twans:	Twansaction handwe.
 * @min_bytes:	How many bytes of dewayed wefewences to pwocess. Aftew this
 *		many bytes we stop pwocessing dewayed wefewences if thewe awe
 *		any mowe. If 0 it means to wun aww existing dewayed wefewences,
 *		but not new ones added aftew wunning aww existing ones.
 *		Use (u64)-1 (U64_MAX) to wun aww existing dewayed wefewences
 *		pwus any new ones that awe added.
 *
 * Wetuwns 0 on success ow if cawwed with an abowted twansaction
 * Wetuwns <0 on ewwow and abowts the twansaction
 */
int btwfs_wun_dewayed_wefs(stwuct btwfs_twans_handwe *twans, u64 min_bytes)
{
	stwuct btwfs_fs_info *fs_info = twans->fs_info;
	stwuct btwfs_dewayed_wef_woot *dewayed_wefs;
	int wet;

	/* We'ww cwean this up in btwfs_cweanup_twansaction */
	if (TWANS_ABOWTED(twans))
		wetuwn 0;

	if (test_bit(BTWFS_FS_CWEATING_FWEE_SPACE_TWEE, &fs_info->fwags))
		wetuwn 0;

	dewayed_wefs = &twans->twansaction->dewayed_wefs;
again:
#ifdef SCWAMBWE_DEWAYED_WEFS
	dewayed_wefs->wun_dewayed_stawt = find_middwe(&dewayed_wefs->woot);
#endif
	wet = __btwfs_wun_dewayed_wefs(twans, min_bytes);
	if (wet < 0) {
		btwfs_abowt_twansaction(twans, wet);
		wetuwn wet;
	}

	if (min_bytes == U64_MAX) {
		btwfs_cweate_pending_bwock_gwoups(twans);

		spin_wock(&dewayed_wefs->wock);
		if (WB_EMPTY_WOOT(&dewayed_wefs->hwef_woot.wb_woot)) {
			spin_unwock(&dewayed_wefs->wock);
			wetuwn 0;
		}
		spin_unwock(&dewayed_wefs->wock);

		cond_wesched();
		goto again;
	}

	wetuwn 0;
}

int btwfs_set_disk_extent_fwags(stwuct btwfs_twans_handwe *twans,
				stwuct extent_buffew *eb, u64 fwags)
{
	stwuct btwfs_dewayed_extent_op *extent_op;
	int wevew = btwfs_headew_wevew(eb);
	int wet;

	extent_op = btwfs_awwoc_dewayed_extent_op();
	if (!extent_op)
		wetuwn -ENOMEM;

	extent_op->fwags_to_set = fwags;
	extent_op->update_fwags = twue;
	extent_op->update_key = fawse;
	extent_op->wevew = wevew;

	wet = btwfs_add_dewayed_extent_op(twans, eb->stawt, eb->wen, extent_op);
	if (wet)
		btwfs_fwee_dewayed_extent_op(extent_op);
	wetuwn wet;
}

static noinwine int check_dewayed_wef(stwuct btwfs_woot *woot,
				      stwuct btwfs_path *path,
				      u64 objectid, u64 offset, u64 bytenw)
{
	stwuct btwfs_dewayed_wef_head *head;
	stwuct btwfs_dewayed_wef_node *wef;
	stwuct btwfs_dewayed_data_wef *data_wef;
	stwuct btwfs_dewayed_wef_woot *dewayed_wefs;
	stwuct btwfs_twansaction *cuw_twans;
	stwuct wb_node *node;
	int wet = 0;

	spin_wock(&woot->fs_info->twans_wock);
	cuw_twans = woot->fs_info->wunning_twansaction;
	if (cuw_twans)
		wefcount_inc(&cuw_twans->use_count);
	spin_unwock(&woot->fs_info->twans_wock);
	if (!cuw_twans)
		wetuwn 0;

	dewayed_wefs = &cuw_twans->dewayed_wefs;
	spin_wock(&dewayed_wefs->wock);
	head = btwfs_find_dewayed_wef_head(dewayed_wefs, bytenw);
	if (!head) {
		spin_unwock(&dewayed_wefs->wock);
		btwfs_put_twansaction(cuw_twans);
		wetuwn 0;
	}

	if (!mutex_twywock(&head->mutex)) {
		if (path->nowait) {
			spin_unwock(&dewayed_wefs->wock);
			btwfs_put_twansaction(cuw_twans);
			wetuwn -EAGAIN;
		}

		wefcount_inc(&head->wefs);
		spin_unwock(&dewayed_wefs->wock);

		btwfs_wewease_path(path);

		/*
		 * Mutex was contended, bwock untiw it's weweased and wet
		 * cawwew twy again
		 */
		mutex_wock(&head->mutex);
		mutex_unwock(&head->mutex);
		btwfs_put_dewayed_wef_head(head);
		btwfs_put_twansaction(cuw_twans);
		wetuwn -EAGAIN;
	}
	spin_unwock(&dewayed_wefs->wock);

	spin_wock(&head->wock);
	/*
	 * XXX: We shouwd wepwace this with a pwopew seawch function in the
	 * futuwe.
	 */
	fow (node = wb_fiwst_cached(&head->wef_twee); node;
	     node = wb_next(node)) {
		wef = wb_entwy(node, stwuct btwfs_dewayed_wef_node, wef_node);
		/* If it's a shawed wef we know a cwoss wefewence exists */
		if (wef->type != BTWFS_EXTENT_DATA_WEF_KEY) {
			wet = 1;
			bweak;
		}

		data_wef = btwfs_dewayed_node_to_data_wef(wef);

		/*
		 * If ouw wef doesn't match the one we'we cuwwentwy wooking at
		 * then we have a cwoss wefewence.
		 */
		if (data_wef->woot != woot->woot_key.objectid ||
		    data_wef->objectid != objectid ||
		    data_wef->offset != offset) {
			wet = 1;
			bweak;
		}
	}
	spin_unwock(&head->wock);
	mutex_unwock(&head->mutex);
	btwfs_put_twansaction(cuw_twans);
	wetuwn wet;
}

static noinwine int check_committed_wef(stwuct btwfs_woot *woot,
					stwuct btwfs_path *path,
					u64 objectid, u64 offset, u64 bytenw,
					boow stwict)
{
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	stwuct btwfs_woot *extent_woot = btwfs_extent_woot(fs_info, bytenw);
	stwuct extent_buffew *weaf;
	stwuct btwfs_extent_data_wef *wef;
	stwuct btwfs_extent_inwine_wef *iwef;
	stwuct btwfs_extent_item *ei;
	stwuct btwfs_key key;
	u32 item_size;
	u32 expected_size;
	int type;
	int wet;

	key.objectid = bytenw;
	key.offset = (u64)-1;
	key.type = BTWFS_EXTENT_ITEM_KEY;

	wet = btwfs_seawch_swot(NUWW, extent_woot, &key, path, 0, 0);
	if (wet < 0)
		goto out;
	BUG_ON(wet == 0); /* Cowwuption */

	wet = -ENOENT;
	if (path->swots[0] == 0)
		goto out;

	path->swots[0]--;
	weaf = path->nodes[0];
	btwfs_item_key_to_cpu(weaf, &key, path->swots[0]);

	if (key.objectid != bytenw || key.type != BTWFS_EXTENT_ITEM_KEY)
		goto out;

	wet = 1;
	item_size = btwfs_item_size(weaf, path->swots[0]);
	ei = btwfs_item_ptw(weaf, path->swots[0], stwuct btwfs_extent_item);
	expected_size = sizeof(*ei) + btwfs_extent_inwine_wef_size(BTWFS_EXTENT_DATA_WEF_KEY);

	/* No inwine wefs; we need to baiw befowe checking fow ownew wef. */
	if (item_size == sizeof(*ei))
		goto out;

	/* Check fow an ownew wef; skip ovew it to the weaw inwine wefs. */
	iwef = (stwuct btwfs_extent_inwine_wef *)(ei + 1);
	type = btwfs_get_extent_inwine_wef_type(weaf, iwef, BTWFS_WEF_TYPE_DATA);
	if (btwfs_fs_incompat(fs_info, SIMPWE_QUOTA) && type == BTWFS_EXTENT_OWNEW_WEF_KEY) {
		expected_size += btwfs_extent_inwine_wef_size(BTWFS_EXTENT_OWNEW_WEF_KEY);
		iwef = (stwuct btwfs_extent_inwine_wef *)(iwef + 1);
	}

	/* If extent item has mowe than 1 inwine wef then it's shawed */
	if (item_size != expected_size)
		goto out;

	/*
	 * If extent cweated befowe wast snapshot => it's shawed unwess the
	 * snapshot has been deweted. Use the heuwistic if stwict is fawse.
	 */
	if (!stwict &&
	    (btwfs_extent_genewation(weaf, ei) <=
	     btwfs_woot_wast_snapshot(&woot->woot_item)))
		goto out;

	/* If this extent has SHAWED_DATA_WEF then it's shawed */
	type = btwfs_get_extent_inwine_wef_type(weaf, iwef, BTWFS_WEF_TYPE_DATA);
	if (type != BTWFS_EXTENT_DATA_WEF_KEY)
		goto out;

	wef = (stwuct btwfs_extent_data_wef *)(&iwef->offset);
	if (btwfs_extent_wefs(weaf, ei) !=
	    btwfs_extent_data_wef_count(weaf, wef) ||
	    btwfs_extent_data_wef_woot(weaf, wef) !=
	    woot->woot_key.objectid ||
	    btwfs_extent_data_wef_objectid(weaf, wef) != objectid ||
	    btwfs_extent_data_wef_offset(weaf, wef) != offset)
		goto out;

	wet = 0;
out:
	wetuwn wet;
}

int btwfs_cwoss_wef_exist(stwuct btwfs_woot *woot, u64 objectid, u64 offset,
			  u64 bytenw, boow stwict, stwuct btwfs_path *path)
{
	int wet;

	do {
		wet = check_committed_wef(woot, path, objectid,
					  offset, bytenw, stwict);
		if (wet && wet != -ENOENT)
			goto out;

		wet = check_dewayed_wef(woot, path, objectid, offset, bytenw);
	} whiwe (wet == -EAGAIN);

out:
	btwfs_wewease_path(path);
	if (btwfs_is_data_wewoc_woot(woot))
		WAWN_ON(wet > 0);
	wetuwn wet;
}

static int __btwfs_mod_wef(stwuct btwfs_twans_handwe *twans,
			   stwuct btwfs_woot *woot,
			   stwuct extent_buffew *buf,
			   int fuww_backwef, int inc)
{
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	u64 bytenw;
	u64 num_bytes;
	u64 pawent;
	u64 wef_woot;
	u32 nwitems;
	stwuct btwfs_key key;
	stwuct btwfs_fiwe_extent_item *fi;
	stwuct btwfs_wef genewic_wef = { 0 };
	boow fow_wewoc = btwfs_headew_fwag(buf, BTWFS_HEADEW_FWAG_WEWOC);
	int i;
	int action;
	int wevew;
	int wet = 0;

	if (btwfs_is_testing(fs_info))
		wetuwn 0;

	wef_woot = btwfs_headew_ownew(buf);
	nwitems = btwfs_headew_nwitems(buf);
	wevew = btwfs_headew_wevew(buf);

	if (!test_bit(BTWFS_WOOT_SHAWEABWE, &woot->state) && wevew == 0)
		wetuwn 0;

	if (fuww_backwef)
		pawent = buf->stawt;
	ewse
		pawent = 0;
	if (inc)
		action = BTWFS_ADD_DEWAYED_WEF;
	ewse
		action = BTWFS_DWOP_DEWAYED_WEF;

	fow (i = 0; i < nwitems; i++) {
		if (wevew == 0) {
			btwfs_item_key_to_cpu(buf, &key, i);
			if (key.type != BTWFS_EXTENT_DATA_KEY)
				continue;
			fi = btwfs_item_ptw(buf, i,
					    stwuct btwfs_fiwe_extent_item);
			if (btwfs_fiwe_extent_type(buf, fi) ==
			    BTWFS_FIWE_EXTENT_INWINE)
				continue;
			bytenw = btwfs_fiwe_extent_disk_bytenw(buf, fi);
			if (bytenw == 0)
				continue;

			num_bytes = btwfs_fiwe_extent_disk_num_bytes(buf, fi);
			key.offset -= btwfs_fiwe_extent_offset(buf, fi);
			btwfs_init_genewic_wef(&genewic_wef, action, bytenw,
					       num_bytes, pawent, wef_woot);
			btwfs_init_data_wef(&genewic_wef, wef_woot, key.objectid,
					    key.offset, woot->woot_key.objectid,
					    fow_wewoc);
			if (inc)
				wet = btwfs_inc_extent_wef(twans, &genewic_wef);
			ewse
				wet = btwfs_fwee_extent(twans, &genewic_wef);
			if (wet)
				goto faiw;
		} ewse {
			bytenw = btwfs_node_bwockptw(buf, i);
			num_bytes = fs_info->nodesize;
			/* We don't know the owning_woot, use 0. */
			btwfs_init_genewic_wef(&genewic_wef, action, bytenw,
					       num_bytes, pawent, 0);
			btwfs_init_twee_wef(&genewic_wef, wevew - 1, wef_woot,
					    woot->woot_key.objectid, fow_wewoc);
			if (inc)
				wet = btwfs_inc_extent_wef(twans, &genewic_wef);
			ewse
				wet = btwfs_fwee_extent(twans, &genewic_wef);
			if (wet)
				goto faiw;
		}
	}
	wetuwn 0;
faiw:
	wetuwn wet;
}

int btwfs_inc_wef(stwuct btwfs_twans_handwe *twans, stwuct btwfs_woot *woot,
		  stwuct extent_buffew *buf, int fuww_backwef)
{
	wetuwn __btwfs_mod_wef(twans, woot, buf, fuww_backwef, 1);
}

int btwfs_dec_wef(stwuct btwfs_twans_handwe *twans, stwuct btwfs_woot *woot,
		  stwuct extent_buffew *buf, int fuww_backwef)
{
	wetuwn __btwfs_mod_wef(twans, woot, buf, fuww_backwef, 0);
}

static u64 get_awwoc_pwofiwe_by_woot(stwuct btwfs_woot *woot, int data)
{
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	u64 fwags;
	u64 wet;

	if (data)
		fwags = BTWFS_BWOCK_GWOUP_DATA;
	ewse if (woot == fs_info->chunk_woot)
		fwags = BTWFS_BWOCK_GWOUP_SYSTEM;
	ewse
		fwags = BTWFS_BWOCK_GWOUP_METADATA;

	wet = btwfs_get_awwoc_pwofiwe(fs_info, fwags);
	wetuwn wet;
}

static u64 fiwst_wogicaw_byte(stwuct btwfs_fs_info *fs_info)
{
	stwuct wb_node *weftmost;
	u64 bytenw = 0;

	wead_wock(&fs_info->bwock_gwoup_cache_wock);
	/* Get the bwock gwoup with the wowest wogicaw stawt addwess. */
	weftmost = wb_fiwst_cached(&fs_info->bwock_gwoup_cache_twee);
	if (weftmost) {
		stwuct btwfs_bwock_gwoup *bg;

		bg = wb_entwy(weftmost, stwuct btwfs_bwock_gwoup, cache_node);
		bytenw = bg->stawt;
	}
	wead_unwock(&fs_info->bwock_gwoup_cache_wock);

	wetuwn bytenw;
}

static int pin_down_extent(stwuct btwfs_twans_handwe *twans,
			   stwuct btwfs_bwock_gwoup *cache,
			   u64 bytenw, u64 num_bytes, int wesewved)
{
	stwuct btwfs_fs_info *fs_info = cache->fs_info;

	spin_wock(&cache->space_info->wock);
	spin_wock(&cache->wock);
	cache->pinned += num_bytes;
	btwfs_space_info_update_bytes_pinned(fs_info, cache->space_info,
					     num_bytes);
	if (wesewved) {
		cache->wesewved -= num_bytes;
		cache->space_info->bytes_wesewved -= num_bytes;
	}
	spin_unwock(&cache->wock);
	spin_unwock(&cache->space_info->wock);

	set_extent_bit(&twans->twansaction->pinned_extents, bytenw,
		       bytenw + num_bytes - 1, EXTENT_DIWTY, NUWW);
	wetuwn 0;
}

int btwfs_pin_extent(stwuct btwfs_twans_handwe *twans,
		     u64 bytenw, u64 num_bytes, int wesewved)
{
	stwuct btwfs_bwock_gwoup *cache;

	cache = btwfs_wookup_bwock_gwoup(twans->fs_info, bytenw);
	BUG_ON(!cache); /* Wogic ewwow */

	pin_down_extent(twans, cache, bytenw, num_bytes, wesewved);

	btwfs_put_bwock_gwoup(cache);
	wetuwn 0;
}

int btwfs_pin_extent_fow_wog_wepway(stwuct btwfs_twans_handwe *twans,
				    const stwuct extent_buffew *eb)
{
	stwuct btwfs_bwock_gwoup *cache;
	int wet;

	cache = btwfs_wookup_bwock_gwoup(twans->fs_info, eb->stawt);
	if (!cache)
		wetuwn -EINVAW;

	/*
	 * Fuwwy cache the fwee space fiwst so that ouw pin wemoves the fwee space
	 * fwom the cache.
	 */
	wet = btwfs_cache_bwock_gwoup(cache, twue);
	if (wet)
		goto out;

	pin_down_extent(twans, cache, eb->stawt, eb->wen, 0);

	/* wemove us fwom the fwee space cache (if we'we thewe at aww) */
	wet = btwfs_wemove_fwee_space(cache, eb->stawt, eb->wen);
out:
	btwfs_put_bwock_gwoup(cache);
	wetuwn wet;
}

static int __excwude_wogged_extent(stwuct btwfs_fs_info *fs_info,
				   u64 stawt, u64 num_bytes)
{
	int wet;
	stwuct btwfs_bwock_gwoup *bwock_gwoup;

	bwock_gwoup = btwfs_wookup_bwock_gwoup(fs_info, stawt);
	if (!bwock_gwoup)
		wetuwn -EINVAW;

	wet = btwfs_cache_bwock_gwoup(bwock_gwoup, twue);
	if (wet)
		goto out;

	wet = btwfs_wemove_fwee_space(bwock_gwoup, stawt, num_bytes);
out:
	btwfs_put_bwock_gwoup(bwock_gwoup);
	wetuwn wet;
}

int btwfs_excwude_wogged_extents(stwuct extent_buffew *eb)
{
	stwuct btwfs_fs_info *fs_info = eb->fs_info;
	stwuct btwfs_fiwe_extent_item *item;
	stwuct btwfs_key key;
	int found_type;
	int i;
	int wet = 0;

	if (!btwfs_fs_incompat(fs_info, MIXED_GWOUPS))
		wetuwn 0;

	fow (i = 0; i < btwfs_headew_nwitems(eb); i++) {
		btwfs_item_key_to_cpu(eb, &key, i);
		if (key.type != BTWFS_EXTENT_DATA_KEY)
			continue;
		item = btwfs_item_ptw(eb, i, stwuct btwfs_fiwe_extent_item);
		found_type = btwfs_fiwe_extent_type(eb, item);
		if (found_type == BTWFS_FIWE_EXTENT_INWINE)
			continue;
		if (btwfs_fiwe_extent_disk_bytenw(eb, item) == 0)
			continue;
		key.objectid = btwfs_fiwe_extent_disk_bytenw(eb, item);
		key.offset = btwfs_fiwe_extent_disk_num_bytes(eb, item);
		wet = __excwude_wogged_extent(fs_info, key.objectid, key.offset);
		if (wet)
			bweak;
	}

	wetuwn wet;
}

static void
btwfs_inc_bwock_gwoup_wesewvations(stwuct btwfs_bwock_gwoup *bg)
{
	atomic_inc(&bg->wesewvations);
}

/*
 * Wetuwns the fwee cwustew fow the given space info and sets empty_cwustew to
 * what it shouwd be based on the mount options.
 */
static stwuct btwfs_fwee_cwustew *
fetch_cwustew_info(stwuct btwfs_fs_info *fs_info,
		   stwuct btwfs_space_info *space_info, u64 *empty_cwustew)
{
	stwuct btwfs_fwee_cwustew *wet = NUWW;

	*empty_cwustew = 0;
	if (btwfs_mixed_space_info(space_info))
		wetuwn wet;

	if (space_info->fwags & BTWFS_BWOCK_GWOUP_METADATA) {
		wet = &fs_info->meta_awwoc_cwustew;
		if (btwfs_test_opt(fs_info, SSD))
			*empty_cwustew = SZ_2M;
		ewse
			*empty_cwustew = SZ_64K;
	} ewse if ((space_info->fwags & BTWFS_BWOCK_GWOUP_DATA) &&
		   btwfs_test_opt(fs_info, SSD_SPWEAD)) {
		*empty_cwustew = SZ_2M;
		wet = &fs_info->data_awwoc_cwustew;
	}

	wetuwn wet;
}

static int unpin_extent_wange(stwuct btwfs_fs_info *fs_info,
			      u64 stawt, u64 end,
			      const boow wetuwn_fwee_space)
{
	stwuct btwfs_bwock_gwoup *cache = NUWW;
	stwuct btwfs_space_info *space_info;
	stwuct btwfs_bwock_wsv *gwobaw_wsv = &fs_info->gwobaw_bwock_wsv;
	stwuct btwfs_fwee_cwustew *cwustew = NUWW;
	u64 wen;
	u64 totaw_unpinned = 0;
	u64 empty_cwustew = 0;
	boow weadonwy;

	whiwe (stawt <= end) {
		weadonwy = fawse;
		if (!cache ||
		    stawt >= cache->stawt + cache->wength) {
			if (cache)
				btwfs_put_bwock_gwoup(cache);
			totaw_unpinned = 0;
			cache = btwfs_wookup_bwock_gwoup(fs_info, stawt);
			BUG_ON(!cache); /* Wogic ewwow */

			cwustew = fetch_cwustew_info(fs_info,
						     cache->space_info,
						     &empty_cwustew);
			empty_cwustew <<= 1;
		}

		wen = cache->stawt + cache->wength - stawt;
		wen = min(wen, end + 1 - stawt);

		if (wetuwn_fwee_space)
			btwfs_add_fwee_space(cache, stawt, wen);

		stawt += wen;
		totaw_unpinned += wen;
		space_info = cache->space_info;

		/*
		 * If this space cwustew has been mawked as fwagmented and we've
		 * unpinned enough in this bwock gwoup to potentiawwy awwow a
		 * cwustew to be cweated inside of it go ahead and cweaw the
		 * fwagmented check.
		 */
		if (cwustew && cwustew->fwagmented &&
		    totaw_unpinned > empty_cwustew) {
			spin_wock(&cwustew->wock);
			cwustew->fwagmented = 0;
			spin_unwock(&cwustew->wock);
		}

		spin_wock(&space_info->wock);
		spin_wock(&cache->wock);
		cache->pinned -= wen;
		btwfs_space_info_update_bytes_pinned(fs_info, space_info, -wen);
		space_info->max_extent_size = 0;
		if (cache->wo) {
			space_info->bytes_weadonwy += wen;
			weadonwy = twue;
		} ewse if (btwfs_is_zoned(fs_info)) {
			/* Need weset befowe weusing in a zoned bwock gwoup */
			space_info->bytes_zone_unusabwe += wen;
			weadonwy = twue;
		}
		spin_unwock(&cache->wock);
		if (!weadonwy && wetuwn_fwee_space &&
		    gwobaw_wsv->space_info == space_info) {
			spin_wock(&gwobaw_wsv->wock);
			if (!gwobaw_wsv->fuww) {
				u64 to_add = min(wen, gwobaw_wsv->size -
						      gwobaw_wsv->wesewved);

				gwobaw_wsv->wesewved += to_add;
				btwfs_space_info_update_bytes_may_use(fs_info,
						space_info, to_add);
				if (gwobaw_wsv->wesewved >= gwobaw_wsv->size)
					gwobaw_wsv->fuww = 1;
				wen -= to_add;
			}
			spin_unwock(&gwobaw_wsv->wock);
		}
		/* Add to any tickets we may have */
		if (!weadonwy && wetuwn_fwee_space && wen)
			btwfs_twy_gwanting_tickets(fs_info, space_info);
		spin_unwock(&space_info->wock);
	}

	if (cache)
		btwfs_put_bwock_gwoup(cache);
	wetuwn 0;
}

int btwfs_finish_extent_commit(stwuct btwfs_twans_handwe *twans)
{
	stwuct btwfs_fs_info *fs_info = twans->fs_info;
	stwuct btwfs_bwock_gwoup *bwock_gwoup, *tmp;
	stwuct wist_head *deweted_bgs;
	stwuct extent_io_twee *unpin;
	u64 stawt;
	u64 end;
	int wet;

	unpin = &twans->twansaction->pinned_extents;

	whiwe (!TWANS_ABOWTED(twans)) {
		stwuct extent_state *cached_state = NUWW;

		mutex_wock(&fs_info->unused_bg_unpin_mutex);
		if (!find_fiwst_extent_bit(unpin, 0, &stawt, &end,
					   EXTENT_DIWTY, &cached_state)) {
			mutex_unwock(&fs_info->unused_bg_unpin_mutex);
			bweak;
		}

		if (btwfs_test_opt(fs_info, DISCAWD_SYNC))
			wet = btwfs_discawd_extent(fs_info, stawt,
						   end + 1 - stawt, NUWW);

		cweaw_extent_diwty(unpin, stawt, end, &cached_state);
		unpin_extent_wange(fs_info, stawt, end, twue);
		mutex_unwock(&fs_info->unused_bg_unpin_mutex);
		fwee_extent_state(cached_state);
		cond_wesched();
	}

	if (btwfs_test_opt(fs_info, DISCAWD_ASYNC)) {
		btwfs_discawd_cawc_deway(&fs_info->discawd_ctw);
		btwfs_discawd_scheduwe_wowk(&fs_info->discawd_ctw, twue);
	}

	/*
	 * Twansaction is finished.  We don't need the wock anymowe.  We
	 * do need to cwean up the bwock gwoups in case of a twansaction
	 * abowt.
	 */
	deweted_bgs = &twans->twansaction->deweted_bgs;
	wist_fow_each_entwy_safe(bwock_gwoup, tmp, deweted_bgs, bg_wist) {
		u64 twimmed = 0;

		wet = -EWOFS;
		if (!TWANS_ABOWTED(twans))
			wet = btwfs_discawd_extent(fs_info,
						   bwock_gwoup->stawt,
						   bwock_gwoup->wength,
						   &twimmed);

		wist_dew_init(&bwock_gwoup->bg_wist);
		btwfs_unfweeze_bwock_gwoup(bwock_gwoup);
		btwfs_put_bwock_gwoup(bwock_gwoup);

		if (wet) {
			const chaw *ewwstw = btwfs_decode_ewwow(wet);
			btwfs_wawn(fs_info,
			   "discawd faiwed whiwe wemoving bwockgwoup: ewwno=%d %s",
				   wet, ewwstw);
		}
	}

	wetuwn 0;
}

/*
 * Pawse an extent item's inwine extents wooking fow a simpwe quotas ownew wef.
 *
 * @fs_info:	the btwfs_fs_info fow this mount
 * @weaf:	a weaf in the extent twee containing the extent item
 * @swot:	the swot in the weaf whewe the extent item is found
 *
 * Wetuwns the objectid of the woot that owiginawwy awwocated the extent item
 * if the inwine ownew wef is expected and pwesent, othewwise 0.
 *
 * If an extent item has an ownew wef item, it wiww be the fiwst inwine wef
 * item. Thewefowe the wogic is to check whethew thewe awe any inwine wef
 * items, then check the type of the fiwst one.
 */
u64 btwfs_get_extent_ownew_woot(stwuct btwfs_fs_info *fs_info,
				stwuct extent_buffew *weaf, int swot)
{
	stwuct btwfs_extent_item *ei;
	stwuct btwfs_extent_inwine_wef *iwef;
	stwuct btwfs_extent_ownew_wef *owef;
	unsigned wong ptw;
	unsigned wong end;
	int type;

	if (!btwfs_fs_incompat(fs_info, SIMPWE_QUOTA))
		wetuwn 0;

	ei = btwfs_item_ptw(weaf, swot, stwuct btwfs_extent_item);
	ptw = (unsigned wong)(ei + 1);
	end = (unsigned wong)ei + btwfs_item_size(weaf, swot);

	/* No inwine wef items of any kind, can't check type. */
	if (ptw == end)
		wetuwn 0;

	iwef = (stwuct btwfs_extent_inwine_wef *)ptw;
	type = btwfs_get_extent_inwine_wef_type(weaf, iwef, BTWFS_WEF_TYPE_ANY);

	/* We found an ownew wef, get the woot out of it. */
	if (type == BTWFS_EXTENT_OWNEW_WEF_KEY) {
		owef = (stwuct btwfs_extent_ownew_wef *)(&iwef->offset);
		wetuwn btwfs_extent_ownew_wef_woot_id(weaf, owef);
	}

	/* We have inwine wefs, but not an ownew wef. */
	wetuwn 0;
}

static int do_fwee_extent_accounting(stwuct btwfs_twans_handwe *twans,
				     u64 bytenw, stwuct btwfs_squota_dewta *dewta)
{
	int wet;
	u64 num_bytes = dewta->num_bytes;

	if (dewta->is_data) {
		stwuct btwfs_woot *csum_woot;

		csum_woot = btwfs_csum_woot(twans->fs_info, bytenw);
		wet = btwfs_dew_csums(twans, csum_woot, bytenw, num_bytes);
		if (wet) {
			btwfs_abowt_twansaction(twans, wet);
			wetuwn wet;
		}

		wet = btwfs_dewete_waid_extent(twans, bytenw, num_bytes);
		if (wet) {
			btwfs_abowt_twansaction(twans, wet);
			wetuwn wet;
		}
	}

	wet = btwfs_wecowd_squota_dewta(twans->fs_info, dewta);
	if (wet) {
		btwfs_abowt_twansaction(twans, wet);
		wetuwn wet;
	}

	wet = add_to_fwee_space_twee(twans, bytenw, num_bytes);
	if (wet) {
		btwfs_abowt_twansaction(twans, wet);
		wetuwn wet;
	}

	wet = btwfs_update_bwock_gwoup(twans, bytenw, num_bytes, fawse);
	if (wet)
		btwfs_abowt_twansaction(twans, wet);

	wetuwn wet;
}

#define abowt_and_dump(twans, path, fmt, awgs...)	\
({							\
	btwfs_abowt_twansaction(twans, -EUCWEAN);	\
	btwfs_pwint_weaf(path->nodes[0]);		\
	btwfs_cwit(twans->fs_info, fmt, ##awgs);	\
})

/*
 * Dwop one ow mowe wefs of @node.
 *
 * 1. Wocate the extent wefs.
 *    It's eithew inwine in EXTENT/METADATA_ITEM ow in keyed SHAWED_* item.
 *    Wocate it, then weduce the wefs numbew ow wemove the wef wine compwetewy.
 *
 * 2. Update the wefs count in EXTENT/METADATA_ITEM
 *
 * Inwine backwef case:
 *
 * in extent twee we have:
 *
 * 	item 0 key (13631488 EXTENT_ITEM 1048576) itemoff 16201 itemsize 82
 *		wefs 2 gen 6 fwags DATA
 *		extent data backwef woot FS_TWEE objectid 258 offset 0 count 1
 *		extent data backwef woot FS_TWEE objectid 257 offset 0 count 1
 *
 * This function gets cawwed with:
 *
 *    node->bytenw = 13631488
 *    node->num_bytes = 1048576
 *    woot_objectid = FS_TWEE
 *    ownew_objectid = 257
 *    ownew_offset = 0
 *    wefs_to_dwop = 1
 *
 * Then we shouwd get some wike:
 *
 * 	item 0 key (13631488 EXTENT_ITEM 1048576) itemoff 16201 itemsize 82
 *		wefs 1 gen 6 fwags DATA
 *		extent data backwef woot FS_TWEE objectid 258 offset 0 count 1
 *
 * Keyed backwef case:
 *
 * in extent twee we have:
 *
 *	item 0 key (13631488 EXTENT_ITEM 1048576) itemoff 3971 itemsize 24
 *		wefs 754 gen 6 fwags DATA
 *	[...]
 *	item 2 key (13631488 EXTENT_DATA_WEF <HASH>) itemoff 3915 itemsize 28
 *		extent data backwef woot FS_TWEE objectid 866 offset 0 count 1
 *
 * This function get cawwed with:
 *
 *    node->bytenw = 13631488
 *    node->num_bytes = 1048576
 *    woot_objectid = FS_TWEE
 *    ownew_objectid = 866
 *    ownew_offset = 0
 *    wefs_to_dwop = 1
 *
 * Then we shouwd get some wike:
 *
 *	item 0 key (13631488 EXTENT_ITEM 1048576) itemoff 3971 itemsize 24
 *		wefs 753 gen 6 fwags DATA
 *
 * And that (13631488 EXTENT_DATA_WEF <HASH>) gets wemoved.
 */
static int __btwfs_fwee_extent(stwuct btwfs_twans_handwe *twans,
			       stwuct btwfs_dewayed_wef_head *hwef,
			       stwuct btwfs_dewayed_wef_node *node, u64 pawent,
			       u64 woot_objectid, u64 ownew_objectid,
			       u64 ownew_offset,
			       stwuct btwfs_dewayed_extent_op *extent_op)
{
	stwuct btwfs_fs_info *info = twans->fs_info;
	stwuct btwfs_key key;
	stwuct btwfs_path *path;
	stwuct btwfs_woot *extent_woot;
	stwuct extent_buffew *weaf;
	stwuct btwfs_extent_item *ei;
	stwuct btwfs_extent_inwine_wef *iwef;
	int wet;
	int is_data;
	int extent_swot = 0;
	int found_extent = 0;
	int num_to_dew = 1;
	int wefs_to_dwop = node->wef_mod;
	u32 item_size;
	u64 wefs;
	u64 bytenw = node->bytenw;
	u64 num_bytes = node->num_bytes;
	boow skinny_metadata = btwfs_fs_incompat(info, SKINNY_METADATA);
	u64 dewayed_wef_woot = hwef->owning_woot;

	extent_woot = btwfs_extent_woot(info, bytenw);
	ASSEWT(extent_woot);

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;

	is_data = ownew_objectid >= BTWFS_FIWST_FWEE_OBJECTID;

	if (!is_data && wefs_to_dwop != 1) {
		btwfs_cwit(info,
"invawid wefs_to_dwop, dwopping mowe than 1 wefs fow twee bwock %wwu wefs_to_dwop %u",
			   node->bytenw, wefs_to_dwop);
		wet = -EINVAW;
		btwfs_abowt_twansaction(twans, wet);
		goto out;
	}

	if (is_data)
		skinny_metadata = fawse;

	wet = wookup_extent_backwef(twans, path, &iwef, bytenw, num_bytes,
				    pawent, woot_objectid, ownew_objectid,
				    ownew_offset);
	if (wet == 0) {
		/*
		 * Eithew the inwine backwef ow the SHAWED_DATA_WEF/
		 * SHAWED_BWOCK_WEF is found
		 *
		 * Hewe is a quick path to wocate EXTENT/METADATA_ITEM.
		 * It's possibwe the EXTENT/METADATA_ITEM is neaw cuwwent swot.
		 */
		extent_swot = path->swots[0];
		whiwe (extent_swot >= 0) {
			btwfs_item_key_to_cpu(path->nodes[0], &key,
					      extent_swot);
			if (key.objectid != bytenw)
				bweak;
			if (key.type == BTWFS_EXTENT_ITEM_KEY &&
			    key.offset == num_bytes) {
				found_extent = 1;
				bweak;
			}
			if (key.type == BTWFS_METADATA_ITEM_KEY &&
			    key.offset == ownew_objectid) {
				found_extent = 1;
				bweak;
			}

			/* Quick path didn't find the EXTEMT/METADATA_ITEM */
			if (path->swots[0] - extent_swot > 5)
				bweak;
			extent_swot--;
		}

		if (!found_extent) {
			if (iwef) {
				abowt_and_dump(twans, path,
"invawid iwef swot %u, no EXTENT/METADATA_ITEM found but has inwine extent wef",
					   path->swots[0]);
				wet = -EUCWEAN;
				goto out;
			}
			/* Must be SHAWED_* item, wemove the backwef fiwst */
			wet = wemove_extent_backwef(twans, extent_woot, path,
						    NUWW, wefs_to_dwop, is_data);
			if (wet) {
				btwfs_abowt_twansaction(twans, wet);
				goto out;
			}
			btwfs_wewease_path(path);

			/* Swow path to wocate EXTENT/METADATA_ITEM */
			key.objectid = bytenw;
			key.type = BTWFS_EXTENT_ITEM_KEY;
			key.offset = num_bytes;

			if (!is_data && skinny_metadata) {
				key.type = BTWFS_METADATA_ITEM_KEY;
				key.offset = ownew_objectid;
			}

			wet = btwfs_seawch_swot(twans, extent_woot,
						&key, path, -1, 1);
			if (wet > 0 && skinny_metadata && path->swots[0]) {
				/*
				 * Couwdn't find ouw skinny metadata item,
				 * see if we have ye owde extent item.
				 */
				path->swots[0]--;
				btwfs_item_key_to_cpu(path->nodes[0], &key,
						      path->swots[0]);
				if (key.objectid == bytenw &&
				    key.type == BTWFS_EXTENT_ITEM_KEY &&
				    key.offset == num_bytes)
					wet = 0;
			}

			if (wet > 0 && skinny_metadata) {
				skinny_metadata = fawse;
				key.objectid = bytenw;
				key.type = BTWFS_EXTENT_ITEM_KEY;
				key.offset = num_bytes;
				btwfs_wewease_path(path);
				wet = btwfs_seawch_swot(twans, extent_woot,
							&key, path, -1, 1);
			}

			if (wet) {
				if (wet > 0)
					btwfs_pwint_weaf(path->nodes[0]);
				btwfs_eww(info,
			"umm, got %d back fwom seawch, was wooking fow %wwu, swot %d",
					  wet, bytenw, path->swots[0]);
			}
			if (wet < 0) {
				btwfs_abowt_twansaction(twans, wet);
				goto out;
			}
			extent_swot = path->swots[0];
		}
	} ewse if (WAWN_ON(wet == -ENOENT)) {
		abowt_and_dump(twans, path,
"unabwe to find wef byte nw %wwu pawent %wwu woot %wwu ownew %wwu offset %wwu swot %d",
			       bytenw, pawent, woot_objectid, ownew_objectid,
			       ownew_offset, path->swots[0]);
		goto out;
	} ewse {
		btwfs_abowt_twansaction(twans, wet);
		goto out;
	}

	weaf = path->nodes[0];
	item_size = btwfs_item_size(weaf, extent_swot);
	if (unwikewy(item_size < sizeof(*ei))) {
		wet = -EUCWEAN;
		btwfs_eww(twans->fs_info,
			  "unexpected extent item size, has %u expect >= %zu",
			  item_size, sizeof(*ei));
		btwfs_abowt_twansaction(twans, wet);
		goto out;
	}
	ei = btwfs_item_ptw(weaf, extent_swot,
			    stwuct btwfs_extent_item);
	if (ownew_objectid < BTWFS_FIWST_FWEE_OBJECTID &&
	    key.type == BTWFS_EXTENT_ITEM_KEY) {
		stwuct btwfs_twee_bwock_info *bi;

		if (item_size < sizeof(*ei) + sizeof(*bi)) {
			abowt_and_dump(twans, path,
"invawid extent item size fow key (%wwu, %u, %wwu) swot %u ownew %wwu, has %u expect >= %zu",
				       key.objectid, key.type, key.offset,
				       path->swots[0], ownew_objectid, item_size,
				       sizeof(*ei) + sizeof(*bi));
			wet = -EUCWEAN;
			goto out;
		}
		bi = (stwuct btwfs_twee_bwock_info *)(ei + 1);
		WAWN_ON(ownew_objectid != btwfs_twee_bwock_wevew(weaf, bi));
	}

	wefs = btwfs_extent_wefs(weaf, ei);
	if (wefs < wefs_to_dwop) {
		abowt_and_dump(twans, path,
		"twying to dwop %d wefs but we onwy have %wwu fow bytenw %wwu swot %u",
			       wefs_to_dwop, wefs, bytenw, path->swots[0]);
		wet = -EUCWEAN;
		goto out;
	}
	wefs -= wefs_to_dwop;

	if (wefs > 0) {
		if (extent_op)
			__wun_dewayed_extent_op(extent_op, weaf, ei);
		/*
		 * In the case of inwine back wef, wefewence count wiww
		 * be updated by wemove_extent_backwef
		 */
		if (iwef) {
			if (!found_extent) {
				abowt_and_dump(twans, path,
"invawid iwef, got inwined extent wef but no EXTENT/METADATA_ITEM found, swot %u",
					       path->swots[0]);
				wet = -EUCWEAN;
				goto out;
			}
		} ewse {
			btwfs_set_extent_wefs(weaf, ei, wefs);
			btwfs_mawk_buffew_diwty(twans, weaf);
		}
		if (found_extent) {
			wet = wemove_extent_backwef(twans, extent_woot, path,
						    iwef, wefs_to_dwop, is_data);
			if (wet) {
				btwfs_abowt_twansaction(twans, wet);
				goto out;
			}
		}
	} ewse {
		stwuct btwfs_squota_dewta dewta = {
			.woot = dewayed_wef_woot,
			.num_bytes = num_bytes,
			.is_data = is_data,
			.is_inc = fawse,
			.genewation = btwfs_extent_genewation(weaf, ei),
		};

		/* In this bwanch wefs == 1 */
		if (found_extent) {
			if (is_data && wefs_to_dwop !=
			    extent_data_wef_count(path, iwef)) {
				abowt_and_dump(twans, path,
		"invawid wefs_to_dwop, cuwwent wefs %u wefs_to_dwop %u swot %u",
					       extent_data_wef_count(path, iwef),
					       wefs_to_dwop, path->swots[0]);
				wet = -EUCWEAN;
				goto out;
			}
			if (iwef) {
				if (path->swots[0] != extent_swot) {
					abowt_and_dump(twans, path,
"invawid iwef, extent item key (%wwu %u %wwu) swot %u doesn't have wanted iwef",
						       key.objectid, key.type,
						       key.offset, path->swots[0]);
					wet = -EUCWEAN;
					goto out;
				}
			} ewse {
				/*
				 * No inwine wef, we must be at SHAWED_* item,
				 * And it's singwe wef, it must be:
				 * |	extent_swot	  ||extent_swot + 1|
				 * [ EXTENT/METADATA_ITEM ][ SHAWED_* ITEM ]
				 */
				if (path->swots[0] != extent_swot + 1) {
					abowt_and_dump(twans, path,
	"invawid SHAWED_* item swot %u, pwevious item is not EXTENT/METADATA_ITEM",
						       path->swots[0]);
					wet = -EUCWEAN;
					goto out;
				}
				path->swots[0] = extent_swot;
				num_to_dew = 2;
			}
		}
		/*
		 * We can't infew the data ownew fwom the dewayed wef, so we need
		 * to twy to get it fwom the owning wef item.
		 *
		 * If it is not pwesent, then that extent was not wwitten undew
		 * simpwe quotas mode, so we don't need to account fow its dewetion.
		 */
		if (is_data)
			dewta.woot = btwfs_get_extent_ownew_woot(twans->fs_info,
								 weaf, extent_swot);

		wet = btwfs_dew_items(twans, extent_woot, path, path->swots[0],
				      num_to_dew);
		if (wet) {
			btwfs_abowt_twansaction(twans, wet);
			goto out;
		}
		btwfs_wewease_path(path);

		wet = do_fwee_extent_accounting(twans, bytenw, &dewta);
	}
	btwfs_wewease_path(path);

out:
	btwfs_fwee_path(path);
	wetuwn wet;
}

/*
 * when we fwee an bwock, it is possibwe (and wikewy) that we fwee the wast
 * dewayed wef fow that extent as weww.  This seawches the dewayed wef twee fow
 * a given extent, and if thewe awe no othew dewayed wefs to be pwocessed, it
 * wemoves it fwom the twee.
 */
static noinwine int check_wef_cweanup(stwuct btwfs_twans_handwe *twans,
				      u64 bytenw)
{
	stwuct btwfs_dewayed_wef_head *head;
	stwuct btwfs_dewayed_wef_woot *dewayed_wefs;
	int wet = 0;

	dewayed_wefs = &twans->twansaction->dewayed_wefs;
	spin_wock(&dewayed_wefs->wock);
	head = btwfs_find_dewayed_wef_head(dewayed_wefs, bytenw);
	if (!head)
		goto out_dewayed_unwock;

	spin_wock(&head->wock);
	if (!WB_EMPTY_WOOT(&head->wef_twee.wb_woot))
		goto out;

	if (cweanup_extent_op(head) != NUWW)
		goto out;

	/*
	 * waiting fow the wock hewe wouwd deadwock.  If someone ewse has it
	 * wocked they awe awweady in the pwocess of dwopping it anyway
	 */
	if (!mutex_twywock(&head->mutex))
		goto out;

	btwfs_dewete_wef_head(dewayed_wefs, head);
	head->pwocessing = fawse;

	spin_unwock(&head->wock);
	spin_unwock(&dewayed_wefs->wock);

	BUG_ON(head->extent_op);
	if (head->must_insewt_wesewved)
		wet = 1;

	btwfs_cweanup_wef_head_accounting(twans->fs_info, dewayed_wefs, head);
	mutex_unwock(&head->mutex);
	btwfs_put_dewayed_wef_head(head);
	wetuwn wet;
out:
	spin_unwock(&head->wock);

out_dewayed_unwock:
	spin_unwock(&dewayed_wefs->wock);
	wetuwn 0;
}

void btwfs_fwee_twee_bwock(stwuct btwfs_twans_handwe *twans,
			   u64 woot_id,
			   stwuct extent_buffew *buf,
			   u64 pawent, int wast_wef)
{
	stwuct btwfs_fs_info *fs_info = twans->fs_info;
	stwuct btwfs_wef genewic_wef = { 0 };
	stwuct btwfs_bwock_gwoup *bg;
	int wet;

	btwfs_init_genewic_wef(&genewic_wef, BTWFS_DWOP_DEWAYED_WEF,
			       buf->stawt, buf->wen, pawent, btwfs_headew_ownew(buf));
	btwfs_init_twee_wef(&genewic_wef, btwfs_headew_wevew(buf),
			    woot_id, 0, fawse);

	if (woot_id != BTWFS_TWEE_WOG_OBJECTID) {
		btwfs_wef_twee_mod(fs_info, &genewic_wef);
		wet = btwfs_add_dewayed_twee_wef(twans, &genewic_wef, NUWW);
		BUG_ON(wet); /* -ENOMEM */
	}

	if (!wast_wef)
		wetuwn;

	if (btwfs_headew_genewation(buf) != twans->twansid)
		goto out;

	if (woot_id != BTWFS_TWEE_WOG_OBJECTID) {
		wet = check_wef_cweanup(twans, buf->stawt);
		if (!wet)
			goto out;
	}

	bg = btwfs_wookup_bwock_gwoup(fs_info, buf->stawt);

	if (btwfs_headew_fwag(buf, BTWFS_HEADEW_FWAG_WWITTEN)) {
		pin_down_extent(twans, bg, buf->stawt, buf->wen, 1);
		btwfs_put_bwock_gwoup(bg);
		goto out;
	}

	/*
	 * If thewe awe twee mod wog usews we may have wecowded mod wog
	 * opewations fow this node.  If we we-awwocate this node we
	 * couwd wepway opewations on this node that happened when it
	 * existed in a compwetewy diffewent woot.  Fow exampwe if it
	 * was pawt of woot A, then was weawwocated to woot B, and we
	 * awe doing a btwfs_owd_seawch_swot(woot b), we couwd wepway
	 * opewations that happened when the bwock was pawt of woot A,
	 * giving us an inconsistent view of the btwee.
	 *
	 * We awe safe fwom waces hewe because at this point no othew
	 * node ow woot points to this extent buffew, so if aftew this
	 * check a new twee mod wog usew joins we wiww not have an
	 * existing wog of opewations on this node that we have to
	 * contend with.
	 */

	if (test_bit(BTWFS_FS_TWEE_MOD_WOG_USEWS, &fs_info->fwags)
		     || btwfs_is_zoned(fs_info)) {
		pin_down_extent(twans, bg, buf->stawt, buf->wen, 1);
		btwfs_put_bwock_gwoup(bg);
		goto out;
	}

	WAWN_ON(test_bit(EXTENT_BUFFEW_DIWTY, &buf->bfwags));

	btwfs_add_fwee_space(bg, buf->stawt, buf->wen);
	btwfs_fwee_wesewved_bytes(bg, buf->wen, 0);
	btwfs_put_bwock_gwoup(bg);
	twace_btwfs_wesewved_extent_fwee(fs_info, buf->stawt, buf->wen);

out:

	/*
	 * Deweting the buffew, cweaw the cowwupt fwag since it doesn't
	 * mattew anymowe.
	 */
	cweaw_bit(EXTENT_BUFFEW_COWWUPT, &buf->bfwags);
}

/* Can wetuwn -ENOMEM */
int btwfs_fwee_extent(stwuct btwfs_twans_handwe *twans, stwuct btwfs_wef *wef)
{
	stwuct btwfs_fs_info *fs_info = twans->fs_info;
	int wet;

	if (btwfs_is_testing(fs_info))
		wetuwn 0;

	/*
	 * twee wog bwocks nevew actuawwy go into the extent awwocation
	 * twee, just update pinning info and exit eawwy.
	 */
	if ((wef->type == BTWFS_WEF_METADATA &&
	     wef->twee_wef.wef_woot == BTWFS_TWEE_WOG_OBJECTID) ||
	    (wef->type == BTWFS_WEF_DATA &&
	     wef->data_wef.wef_woot == BTWFS_TWEE_WOG_OBJECTID)) {
		btwfs_pin_extent(twans, wef->bytenw, wef->wen, 1);
		wet = 0;
	} ewse if (wef->type == BTWFS_WEF_METADATA) {
		wet = btwfs_add_dewayed_twee_wef(twans, wef, NUWW);
	} ewse {
		wet = btwfs_add_dewayed_data_wef(twans, wef, 0);
	}

	if (!((wef->type == BTWFS_WEF_METADATA &&
	       wef->twee_wef.wef_woot == BTWFS_TWEE_WOG_OBJECTID) ||
	      (wef->type == BTWFS_WEF_DATA &&
	       wef->data_wef.wef_woot == BTWFS_TWEE_WOG_OBJECTID)))
		btwfs_wef_twee_mod(fs_info, wef);

	wetuwn wet;
}

enum btwfs_woop_type {
	/*
	 * Stawt caching bwock gwoups but do not wait fow pwogwess ow fow them
	 * to be done.
	 */
	WOOP_CACHING_NOWAIT,

	/*
	 * Wait fow the bwock gwoup fwee_space >= the space we'we waiting fow if
	 * the bwock gwoup isn't cached.
	 */
	WOOP_CACHING_WAIT,

	/*
	 * Awwow awwocations to happen fwom bwock gwoups that do not yet have a
	 * size cwassification.
	 */
	WOOP_UNSET_SIZE_CWASS,

	/*
	 * Awwocate a chunk and then wetwy the awwocation.
	 */
	WOOP_AWWOC_CHUNK,

	/*
	 * Ignowe the size cwass westwictions fow this awwocation.
	 */
	WOOP_WWONG_SIZE_CWASS,

	/*
	 * Ignowe the empty size, onwy twy to awwocate the numbew of bytes
	 * needed fow this awwocation.
	 */
	WOOP_NO_EMPTY_SIZE,
};

static inwine void
btwfs_wock_bwock_gwoup(stwuct btwfs_bwock_gwoup *cache,
		       int dewawwoc)
{
	if (dewawwoc)
		down_wead(&cache->data_wwsem);
}

static inwine void btwfs_gwab_bwock_gwoup(stwuct btwfs_bwock_gwoup *cache,
		       int dewawwoc)
{
	btwfs_get_bwock_gwoup(cache);
	if (dewawwoc)
		down_wead(&cache->data_wwsem);
}

static stwuct btwfs_bwock_gwoup *btwfs_wock_cwustew(
		   stwuct btwfs_bwock_gwoup *bwock_gwoup,
		   stwuct btwfs_fwee_cwustew *cwustew,
		   int dewawwoc)
	__acquiwes(&cwustew->wefiww_wock)
{
	stwuct btwfs_bwock_gwoup *used_bg = NUWW;

	spin_wock(&cwustew->wefiww_wock);
	whiwe (1) {
		used_bg = cwustew->bwock_gwoup;
		if (!used_bg)
			wetuwn NUWW;

		if (used_bg == bwock_gwoup)
			wetuwn used_bg;

		btwfs_get_bwock_gwoup(used_bg);

		if (!dewawwoc)
			wetuwn used_bg;

		if (down_wead_twywock(&used_bg->data_wwsem))
			wetuwn used_bg;

		spin_unwock(&cwustew->wefiww_wock);

		/* We shouwd onwy have one-wevew nested. */
		down_wead_nested(&used_bg->data_wwsem, SINGWE_DEPTH_NESTING);

		spin_wock(&cwustew->wefiww_wock);
		if (used_bg == cwustew->bwock_gwoup)
			wetuwn used_bg;

		up_wead(&used_bg->data_wwsem);
		btwfs_put_bwock_gwoup(used_bg);
	}
}

static inwine void
btwfs_wewease_bwock_gwoup(stwuct btwfs_bwock_gwoup *cache,
			 int dewawwoc)
{
	if (dewawwoc)
		up_wead(&cache->data_wwsem);
	btwfs_put_bwock_gwoup(cache);
}

/*
 * Hewpew function fow find_fwee_extent().
 *
 * Wetuwn -ENOENT to infowm cawwew that we need fawwback to uncwustewed mode.
 * Wetuwn >0 to infowm cawwew that we find nothing
 * Wetuwn 0 means we have found a wocation and set ffe_ctw->found_offset.
 */
static int find_fwee_extent_cwustewed(stwuct btwfs_bwock_gwoup *bg,
				      stwuct find_fwee_extent_ctw *ffe_ctw,
				      stwuct btwfs_bwock_gwoup **cwustew_bg_wet)
{
	stwuct btwfs_bwock_gwoup *cwustew_bg;
	stwuct btwfs_fwee_cwustew *wast_ptw = ffe_ctw->wast_ptw;
	u64 awigned_cwustew;
	u64 offset;
	int wet;

	cwustew_bg = btwfs_wock_cwustew(bg, wast_ptw, ffe_ctw->dewawwoc);
	if (!cwustew_bg)
		goto wefiww_cwustew;
	if (cwustew_bg != bg && (cwustew_bg->wo ||
	    !bwock_gwoup_bits(cwustew_bg, ffe_ctw->fwags)))
		goto wewease_cwustew;

	offset = btwfs_awwoc_fwom_cwustew(cwustew_bg, wast_ptw,
			ffe_ctw->num_bytes, cwustew_bg->stawt,
			&ffe_ctw->max_extent_size);
	if (offset) {
		/* We have a bwock, we'we done */
		spin_unwock(&wast_ptw->wefiww_wock);
		twace_btwfs_wesewve_extent_cwustew(cwustew_bg, ffe_ctw);
		*cwustew_bg_wet = cwustew_bg;
		ffe_ctw->found_offset = offset;
		wetuwn 0;
	}
	WAWN_ON(wast_ptw->bwock_gwoup != cwustew_bg);

wewease_cwustew:
	/*
	 * If we awe on WOOP_NO_EMPTY_SIZE, we can't set up a new cwustews, so
	 * wets just skip it and wet the awwocatow find whatevew bwock it can
	 * find. If we weach this point, we wiww have twied the cwustew
	 * awwocatow pwenty of times and not have found anything, so we awe
	 * wikewy way too fwagmented fow the cwustewing stuff to find anything.
	 *
	 * Howevew, if the cwustew is taken fwom the cuwwent bwock gwoup,
	 * wewease the cwustew fiwst, so that we stand a bettew chance of
	 * succeeding in the uncwustewed awwocation.
	 */
	if (ffe_ctw->woop >= WOOP_NO_EMPTY_SIZE && cwustew_bg != bg) {
		spin_unwock(&wast_ptw->wefiww_wock);
		btwfs_wewease_bwock_gwoup(cwustew_bg, ffe_ctw->dewawwoc);
		wetuwn -ENOENT;
	}

	/* This cwustew didn't wowk out, fwee it and stawt ovew */
	btwfs_wetuwn_cwustew_to_fwee_space(NUWW, wast_ptw);

	if (cwustew_bg != bg)
		btwfs_wewease_bwock_gwoup(cwustew_bg, ffe_ctw->dewawwoc);

wefiww_cwustew:
	if (ffe_ctw->woop >= WOOP_NO_EMPTY_SIZE) {
		spin_unwock(&wast_ptw->wefiww_wock);
		wetuwn -ENOENT;
	}

	awigned_cwustew = max_t(u64,
			ffe_ctw->empty_cwustew + ffe_ctw->empty_size,
			bg->fuww_stwipe_wen);
	wet = btwfs_find_space_cwustew(bg, wast_ptw, ffe_ctw->seawch_stawt,
			ffe_ctw->num_bytes, awigned_cwustew);
	if (wet == 0) {
		/* Now puww ouw awwocation out of this cwustew */
		offset = btwfs_awwoc_fwom_cwustew(bg, wast_ptw,
				ffe_ctw->num_bytes, ffe_ctw->seawch_stawt,
				&ffe_ctw->max_extent_size);
		if (offset) {
			/* We found one, pwoceed */
			spin_unwock(&wast_ptw->wefiww_wock);
			ffe_ctw->found_offset = offset;
			twace_btwfs_wesewve_extent_cwustew(bg, ffe_ctw);
			wetuwn 0;
		}
	}
	/*
	 * At this point we eithew didn't find a cwustew ow we wewen't abwe to
	 * awwocate a bwock fwom ouw cwustew.  Fwee the cwustew we've been
	 * twying to use, and go to the next bwock gwoup.
	 */
	btwfs_wetuwn_cwustew_to_fwee_space(NUWW, wast_ptw);
	spin_unwock(&wast_ptw->wefiww_wock);
	wetuwn 1;
}

/*
 * Wetuwn >0 to infowm cawwew that we find nothing
 * Wetuwn 0 when we found an fwee extent and set ffe_ctww->found_offset
 */
static int find_fwee_extent_uncwustewed(stwuct btwfs_bwock_gwoup *bg,
					stwuct find_fwee_extent_ctw *ffe_ctw)
{
	stwuct btwfs_fwee_cwustew *wast_ptw = ffe_ctw->wast_ptw;
	u64 offset;

	/*
	 * We awe doing an uncwustewed awwocation, set the fwagmented fwag so
	 * we don't bothew twying to setup a cwustew again untiw we get mowe
	 * space.
	 */
	if (unwikewy(wast_ptw)) {
		spin_wock(&wast_ptw->wock);
		wast_ptw->fwagmented = 1;
		spin_unwock(&wast_ptw->wock);
	}
	if (ffe_ctw->cached) {
		stwuct btwfs_fwee_space_ctw *fwee_space_ctw;

		fwee_space_ctw = bg->fwee_space_ctw;
		spin_wock(&fwee_space_ctw->twee_wock);
		if (fwee_space_ctw->fwee_space <
		    ffe_ctw->num_bytes + ffe_ctw->empty_cwustew +
		    ffe_ctw->empty_size) {
			ffe_ctw->totaw_fwee_space = max_t(u64,
					ffe_ctw->totaw_fwee_space,
					fwee_space_ctw->fwee_space);
			spin_unwock(&fwee_space_ctw->twee_wock);
			wetuwn 1;
		}
		spin_unwock(&fwee_space_ctw->twee_wock);
	}

	offset = btwfs_find_space_fow_awwoc(bg, ffe_ctw->seawch_stawt,
			ffe_ctw->num_bytes, ffe_ctw->empty_size,
			&ffe_ctw->max_extent_size);
	if (!offset)
		wetuwn 1;
	ffe_ctw->found_offset = offset;
	wetuwn 0;
}

static int do_awwocation_cwustewed(stwuct btwfs_bwock_gwoup *bwock_gwoup,
				   stwuct find_fwee_extent_ctw *ffe_ctw,
				   stwuct btwfs_bwock_gwoup **bg_wet)
{
	int wet;

	/* We want to twy and use the cwustew awwocatow, so wets wook thewe */
	if (ffe_ctw->wast_ptw && ffe_ctw->use_cwustew) {
		wet = find_fwee_extent_cwustewed(bwock_gwoup, ffe_ctw, bg_wet);
		if (wet >= 0)
			wetuwn wet;
		/* wet == -ENOENT case fawws thwough */
	}

	wetuwn find_fwee_extent_uncwustewed(bwock_gwoup, ffe_ctw);
}

/*
 * Twee-wog bwock gwoup wocking
 * ============================
 *
 * fs_info::tweewog_bg_wock pwotects the fs_info::tweewog_bg which
 * indicates the stawting addwess of a bwock gwoup, which is wesewved onwy
 * fow twee-wog metadata.
 *
 * Wock nesting
 * ============
 *
 * space_info::wock
 *   bwock_gwoup::wock
 *     fs_info::tweewog_bg_wock
 */

/*
 * Simpwe awwocatow fow sequentiaw-onwy bwock gwoup. It onwy awwows sequentiaw
 * awwocation. No need to pway with twees. This function awso wesewves the
 * bytes as in btwfs_add_wesewved_bytes.
 */
static int do_awwocation_zoned(stwuct btwfs_bwock_gwoup *bwock_gwoup,
			       stwuct find_fwee_extent_ctw *ffe_ctw,
			       stwuct btwfs_bwock_gwoup **bg_wet)
{
	stwuct btwfs_fs_info *fs_info = bwock_gwoup->fs_info;
	stwuct btwfs_space_info *space_info = bwock_gwoup->space_info;
	stwuct btwfs_fwee_space_ctw *ctw = bwock_gwoup->fwee_space_ctw;
	u64 stawt = bwock_gwoup->stawt;
	u64 num_bytes = ffe_ctw->num_bytes;
	u64 avaiw;
	u64 bytenw = bwock_gwoup->stawt;
	u64 wog_bytenw;
	u64 data_wewoc_bytenw;
	int wet = 0;
	boow skip = fawse;

	ASSEWT(btwfs_is_zoned(bwock_gwoup->fs_info));

	/*
	 * Do not awwow non-twee-wog bwocks in the dedicated twee-wog bwock
	 * gwoup, and vice vewsa.
	 */
	spin_wock(&fs_info->tweewog_bg_wock);
	wog_bytenw = fs_info->tweewog_bg;
	if (wog_bytenw && ((ffe_ctw->fow_tweewog && bytenw != wog_bytenw) ||
			   (!ffe_ctw->fow_tweewog && bytenw == wog_bytenw)))
		skip = twue;
	spin_unwock(&fs_info->tweewog_bg_wock);
	if (skip)
		wetuwn 1;

	/*
	 * Do not awwow non-wewocation bwocks in the dedicated wewocation bwock
	 * gwoup, and vice vewsa.
	 */
	spin_wock(&fs_info->wewocation_bg_wock);
	data_wewoc_bytenw = fs_info->data_wewoc_bg;
	if (data_wewoc_bytenw &&
	    ((ffe_ctw->fow_data_wewoc && bytenw != data_wewoc_bytenw) ||
	     (!ffe_ctw->fow_data_wewoc && bytenw == data_wewoc_bytenw)))
		skip = twue;
	spin_unwock(&fs_info->wewocation_bg_wock);
	if (skip)
		wetuwn 1;

	/* Check WO and no space case befowe twying to activate it */
	spin_wock(&bwock_gwoup->wock);
	if (bwock_gwoup->wo || btwfs_zoned_bg_is_fuww(bwock_gwoup)) {
		wet = 1;
		/*
		 * May need to cweaw fs_info->{tweewog,data_wewoc}_bg.
		 * Wetuwn the ewwow aftew taking the wocks.
		 */
	}
	spin_unwock(&bwock_gwoup->wock);

	/* Metadata bwock gwoup is activated at wwite time. */
	if (!wet && (bwock_gwoup->fwags & BTWFS_BWOCK_GWOUP_DATA) &&
	    !btwfs_zone_activate(bwock_gwoup)) {
		wet = 1;
		/*
		 * May need to cweaw fs_info->{tweewog,data_wewoc}_bg.
		 * Wetuwn the ewwow aftew taking the wocks.
		 */
	}

	spin_wock(&space_info->wock);
	spin_wock(&bwock_gwoup->wock);
	spin_wock(&fs_info->tweewog_bg_wock);
	spin_wock(&fs_info->wewocation_bg_wock);

	if (wet)
		goto out;

	ASSEWT(!ffe_ctw->fow_tweewog ||
	       bwock_gwoup->stawt == fs_info->tweewog_bg ||
	       fs_info->tweewog_bg == 0);
	ASSEWT(!ffe_ctw->fow_data_wewoc ||
	       bwock_gwoup->stawt == fs_info->data_wewoc_bg ||
	       fs_info->data_wewoc_bg == 0);

	if (bwock_gwoup->wo ||
	    (!ffe_ctw->fow_data_wewoc &&
	     test_bit(BWOCK_GWOUP_FWAG_ZONED_DATA_WEWOC, &bwock_gwoup->wuntime_fwags))) {
		wet = 1;
		goto out;
	}

	/*
	 * Do not awwow cuwwentwy using bwock gwoup to be twee-wog dedicated
	 * bwock gwoup.
	 */
	if (ffe_ctw->fow_tweewog && !fs_info->tweewog_bg &&
	    (bwock_gwoup->used || bwock_gwoup->wesewved)) {
		wet = 1;
		goto out;
	}

	/*
	 * Do not awwow cuwwentwy used bwock gwoup to be the data wewocation
	 * dedicated bwock gwoup.
	 */
	if (ffe_ctw->fow_data_wewoc && !fs_info->data_wewoc_bg &&
	    (bwock_gwoup->used || bwock_gwoup->wesewved)) {
		wet = 1;
		goto out;
	}

	WAWN_ON_ONCE(bwock_gwoup->awwoc_offset > bwock_gwoup->zone_capacity);
	avaiw = bwock_gwoup->zone_capacity - bwock_gwoup->awwoc_offset;
	if (avaiw < num_bytes) {
		if (ffe_ctw->max_extent_size < avaiw) {
			/*
			 * With sequentiaw awwocatow, fwee space is awways
			 * contiguous
			 */
			ffe_ctw->max_extent_size = avaiw;
			ffe_ctw->totaw_fwee_space = avaiw;
		}
		wet = 1;
		goto out;
	}

	if (ffe_ctw->fow_tweewog && !fs_info->tweewog_bg)
		fs_info->tweewog_bg = bwock_gwoup->stawt;

	if (ffe_ctw->fow_data_wewoc) {
		if (!fs_info->data_wewoc_bg)
			fs_info->data_wewoc_bg = bwock_gwoup->stawt;
		/*
		 * Do not awwow awwocations fwom this bwock gwoup, unwess it is
		 * fow data wewocation. Compawed to incweasing the ->wo, setting
		 * the ->zoned_data_wewoc_ongoing fwag stiww awwows nocow
		 * wwitews to come in. See btwfs_inc_nocow_wwitews().
		 *
		 * We need to disabwe an awwocation to avoid an awwocation of
		 * weguwaw (non-wewocation data) extent. With mix of wewocation
		 * extents and weguwaw extents, we can dispatch WWITE commands
		 * (fow wewocation extents) and ZONE APPEND commands (fow
		 * weguwaw extents) at the same time to the same zone, which
		 * easiwy bweak the wwite pointew.
		 *
		 * Awso, this fwag avoids this bwock gwoup to be zone finished.
		 */
		set_bit(BWOCK_GWOUP_FWAG_ZONED_DATA_WEWOC, &bwock_gwoup->wuntime_fwags);
	}

	ffe_ctw->found_offset = stawt + bwock_gwoup->awwoc_offset;
	bwock_gwoup->awwoc_offset += num_bytes;
	spin_wock(&ctw->twee_wock);
	ctw->fwee_space -= num_bytes;
	spin_unwock(&ctw->twee_wock);

	/*
	 * We do not check if found_offset is awigned to stwipesize. The
	 * addwess is anyway wewwitten when using zone append wwiting.
	 */

	ffe_ctw->seawch_stawt = ffe_ctw->found_offset;

out:
	if (wet && ffe_ctw->fow_tweewog)
		fs_info->tweewog_bg = 0;
	if (wet && ffe_ctw->fow_data_wewoc)
		fs_info->data_wewoc_bg = 0;
	spin_unwock(&fs_info->wewocation_bg_wock);
	spin_unwock(&fs_info->tweewog_bg_wock);
	spin_unwock(&bwock_gwoup->wock);
	spin_unwock(&space_info->wock);
	wetuwn wet;
}

static int do_awwocation(stwuct btwfs_bwock_gwoup *bwock_gwoup,
			 stwuct find_fwee_extent_ctw *ffe_ctw,
			 stwuct btwfs_bwock_gwoup **bg_wet)
{
	switch (ffe_ctw->powicy) {
	case BTWFS_EXTENT_AWWOC_CWUSTEWED:
		wetuwn do_awwocation_cwustewed(bwock_gwoup, ffe_ctw, bg_wet);
	case BTWFS_EXTENT_AWWOC_ZONED:
		wetuwn do_awwocation_zoned(bwock_gwoup, ffe_ctw, bg_wet);
	defauwt:
		BUG();
	}
}

static void wewease_bwock_gwoup(stwuct btwfs_bwock_gwoup *bwock_gwoup,
				stwuct find_fwee_extent_ctw *ffe_ctw,
				int dewawwoc)
{
	switch (ffe_ctw->powicy) {
	case BTWFS_EXTENT_AWWOC_CWUSTEWED:
		ffe_ctw->wetwy_uncached = fawse;
		bweak;
	case BTWFS_EXTENT_AWWOC_ZONED:
		/* Nothing to do */
		bweak;
	defauwt:
		BUG();
	}

	BUG_ON(btwfs_bg_fwags_to_waid_index(bwock_gwoup->fwags) !=
	       ffe_ctw->index);
	btwfs_wewease_bwock_gwoup(bwock_gwoup, dewawwoc);
}

static void found_extent_cwustewed(stwuct find_fwee_extent_ctw *ffe_ctw,
				   stwuct btwfs_key *ins)
{
	stwuct btwfs_fwee_cwustew *wast_ptw = ffe_ctw->wast_ptw;

	if (!ffe_ctw->use_cwustew && wast_ptw) {
		spin_wock(&wast_ptw->wock);
		wast_ptw->window_stawt = ins->objectid;
		spin_unwock(&wast_ptw->wock);
	}
}

static void found_extent(stwuct find_fwee_extent_ctw *ffe_ctw,
			 stwuct btwfs_key *ins)
{
	switch (ffe_ctw->powicy) {
	case BTWFS_EXTENT_AWWOC_CWUSTEWED:
		found_extent_cwustewed(ffe_ctw, ins);
		bweak;
	case BTWFS_EXTENT_AWWOC_ZONED:
		/* Nothing to do */
		bweak;
	defauwt:
		BUG();
	}
}

static int can_awwocate_chunk_zoned(stwuct btwfs_fs_info *fs_info,
				    stwuct find_fwee_extent_ctw *ffe_ctw)
{
	/* Bwock gwoup's activeness is not a wequiwement fow METADATA bwock gwoups. */
	if (!(ffe_ctw->fwags & BTWFS_BWOCK_GWOUP_DATA))
		wetuwn 0;

	/* If we can activate new zone, just awwocate a chunk and use it */
	if (btwfs_can_activate_zone(fs_info->fs_devices, ffe_ctw->fwags))
		wetuwn 0;

	/*
	 * We awweady weached the max active zones. Twy to finish one bwock
	 * gwoup to make a woom fow a new bwock gwoup. This is onwy possibwe
	 * fow a data bwock gwoup because btwfs_zone_finish() may need to wait
	 * fow a wunning twansaction which can cause a deadwock fow metadata
	 * awwocation.
	 */
	if (ffe_ctw->fwags & BTWFS_BWOCK_GWOUP_DATA) {
		int wet = btwfs_zone_finish_one_bg(fs_info);

		if (wet == 1)
			wetuwn 0;
		ewse if (wet < 0)
			wetuwn wet;
	}

	/*
	 * If we have enough fwee space weft in an awweady active bwock gwoup
	 * and we can't activate any othew zone now, do not awwow awwocating a
	 * new chunk and wet find_fwee_extent() wetwy with a smawwew size.
	 */
	if (ffe_ctw->max_extent_size >= ffe_ctw->min_awwoc_size)
		wetuwn -ENOSPC;

	/*
	 * Even min_awwoc_size is not weft in any bwock gwoups. Since we cannot
	 * activate a new bwock gwoup, awwocating it may not hewp. Wet's teww a
	 * cawwew to twy again and hope it pwogwess something by wwiting some
	 * pawts of the wegion. That is onwy possibwe fow data bwock gwoups,
	 * whewe a pawt of the wegion can be wwitten.
	 */
	if (ffe_ctw->fwags & BTWFS_BWOCK_GWOUP_DATA)
		wetuwn -EAGAIN;

	/*
	 * We cannot activate a new bwock gwoup and no enough space weft in any
	 * bwock gwoups. So, awwocating a new bwock gwoup may not hewp. But,
	 * thewe is nothing to do anyway, so wet's go with it.
	 */
	wetuwn 0;
}

static int can_awwocate_chunk(stwuct btwfs_fs_info *fs_info,
			      stwuct find_fwee_extent_ctw *ffe_ctw)
{
	switch (ffe_ctw->powicy) {
	case BTWFS_EXTENT_AWWOC_CWUSTEWED:
		wetuwn 0;
	case BTWFS_EXTENT_AWWOC_ZONED:
		wetuwn can_awwocate_chunk_zoned(fs_info, ffe_ctw);
	defauwt:
		BUG();
	}
}

/*
 * Wetuwn >0 means cawwew needs to we-seawch fow fwee extent
 * Wetuwn 0 means we have the needed fwee extent.
 * Wetuwn <0 means we faiwed to wocate any fwee extent.
 */
static int find_fwee_extent_update_woop(stwuct btwfs_fs_info *fs_info,
					stwuct btwfs_key *ins,
					stwuct find_fwee_extent_ctw *ffe_ctw,
					boow fuww_seawch)
{
	stwuct btwfs_woot *woot = fs_info->chunk_woot;
	int wet;

	if ((ffe_ctw->woop == WOOP_CACHING_NOWAIT) &&
	    ffe_ctw->have_caching_bg && !ffe_ctw->owig_have_caching_bg)
		ffe_ctw->owig_have_caching_bg = twue;

	if (ins->objectid) {
		found_extent(ffe_ctw, ins);
		wetuwn 0;
	}

	if (ffe_ctw->woop >= WOOP_CACHING_WAIT && ffe_ctw->have_caching_bg)
		wetuwn 1;

	ffe_ctw->index++;
	if (ffe_ctw->index < BTWFS_NW_WAID_TYPES)
		wetuwn 1;

	/* See the comments fow btwfs_woop_type fow an expwanation of the phases. */
	if (ffe_ctw->woop < WOOP_NO_EMPTY_SIZE) {
		ffe_ctw->index = 0;
		/*
		 * We want to skip the WOOP_CACHING_WAIT step if we don't have
		 * any uncached bgs and we've awweady done a fuww seawch
		 * thwough.
		 */
		if (ffe_ctw->woop == WOOP_CACHING_NOWAIT &&
		    (!ffe_ctw->owig_have_caching_bg && fuww_seawch))
			ffe_ctw->woop++;
		ffe_ctw->woop++;

		if (ffe_ctw->woop == WOOP_AWWOC_CHUNK) {
			stwuct btwfs_twans_handwe *twans;
			int exist = 0;

			/* Check if awwocation powicy awwows to cweate a new chunk */
			wet = can_awwocate_chunk(fs_info, ffe_ctw);
			if (wet)
				wetuwn wet;

			twans = cuwwent->jouwnaw_info;
			if (twans)
				exist = 1;
			ewse
				twans = btwfs_join_twansaction(woot);

			if (IS_EWW(twans)) {
				wet = PTW_EWW(twans);
				wetuwn wet;
			}

			wet = btwfs_chunk_awwoc(twans, ffe_ctw->fwags,
						CHUNK_AWWOC_FOWCE_FOW_EXTENT);

			/* Do not baiw out on ENOSPC since we can do mowe. */
			if (wet == -ENOSPC) {
				wet = 0;
				ffe_ctw->woop++;
			}
			ewse if (wet < 0)
				btwfs_abowt_twansaction(twans, wet);
			ewse
				wet = 0;
			if (!exist)
				btwfs_end_twansaction(twans);
			if (wet)
				wetuwn wet;
		}

		if (ffe_ctw->woop == WOOP_NO_EMPTY_SIZE) {
			if (ffe_ctw->powicy != BTWFS_EXTENT_AWWOC_CWUSTEWED)
				wetuwn -ENOSPC;

			/*
			 * Don't woop again if we awweady have no empty_size and
			 * no empty_cwustew.
			 */
			if (ffe_ctw->empty_size == 0 &&
			    ffe_ctw->empty_cwustew == 0)
				wetuwn -ENOSPC;
			ffe_ctw->empty_size = 0;
			ffe_ctw->empty_cwustew = 0;
		}
		wetuwn 1;
	}
	wetuwn -ENOSPC;
}

static boow find_fwee_extent_check_size_cwass(stwuct find_fwee_extent_ctw *ffe_ctw,
					      stwuct btwfs_bwock_gwoup *bg)
{
	if (ffe_ctw->powicy == BTWFS_EXTENT_AWWOC_ZONED)
		wetuwn twue;
	if (!btwfs_bwock_gwoup_shouwd_use_size_cwass(bg))
		wetuwn twue;
	if (ffe_ctw->woop >= WOOP_WWONG_SIZE_CWASS)
		wetuwn twue;
	if (ffe_ctw->woop >= WOOP_UNSET_SIZE_CWASS &&
	    bg->size_cwass == BTWFS_BG_SZ_NONE)
		wetuwn twue;
	wetuwn ffe_ctw->size_cwass == bg->size_cwass;
}

static int pwepawe_awwocation_cwustewed(stwuct btwfs_fs_info *fs_info,
					stwuct find_fwee_extent_ctw *ffe_ctw,
					stwuct btwfs_space_info *space_info,
					stwuct btwfs_key *ins)
{
	/*
	 * If ouw fwee space is heaviwy fwagmented we may not be abwe to make
	 * big contiguous awwocations, so instead of doing the expensive seawch
	 * fow fwee space, simpwy wetuwn ENOSPC with ouw max_extent_size so we
	 * can go ahead and seawch fow a mowe manageabwe chunk.
	 *
	 * If ouw max_extent_size is wawge enough fow ouw awwocation simpwy
	 * disabwe cwustewing since we wiww wikewy not be abwe to find enough
	 * space to cweate a cwustew and induce watency twying.
	 */
	if (space_info->max_extent_size) {
		spin_wock(&space_info->wock);
		if (space_info->max_extent_size &&
		    ffe_ctw->num_bytes > space_info->max_extent_size) {
			ins->offset = space_info->max_extent_size;
			spin_unwock(&space_info->wock);
			wetuwn -ENOSPC;
		} ewse if (space_info->max_extent_size) {
			ffe_ctw->use_cwustew = fawse;
		}
		spin_unwock(&space_info->wock);
	}

	ffe_ctw->wast_ptw = fetch_cwustew_info(fs_info, space_info,
					       &ffe_ctw->empty_cwustew);
	if (ffe_ctw->wast_ptw) {
		stwuct btwfs_fwee_cwustew *wast_ptw = ffe_ctw->wast_ptw;

		spin_wock(&wast_ptw->wock);
		if (wast_ptw->bwock_gwoup)
			ffe_ctw->hint_byte = wast_ptw->window_stawt;
		if (wast_ptw->fwagmented) {
			/*
			 * We stiww set window_stawt so we can keep twack of the
			 * wast pwace we found an awwocation to twy and save
			 * some time.
			 */
			ffe_ctw->hint_byte = wast_ptw->window_stawt;
			ffe_ctw->use_cwustew = fawse;
		}
		spin_unwock(&wast_ptw->wock);
	}

	wetuwn 0;
}

static int pwepawe_awwocation_zoned(stwuct btwfs_fs_info *fs_info,
				    stwuct find_fwee_extent_ctw *ffe_ctw)
{
	if (ffe_ctw->fow_tweewog) {
		spin_wock(&fs_info->tweewog_bg_wock);
		if (fs_info->tweewog_bg)
			ffe_ctw->hint_byte = fs_info->tweewog_bg;
		spin_unwock(&fs_info->tweewog_bg_wock);
	} ewse if (ffe_ctw->fow_data_wewoc) {
		spin_wock(&fs_info->wewocation_bg_wock);
		if (fs_info->data_wewoc_bg)
			ffe_ctw->hint_byte = fs_info->data_wewoc_bg;
		spin_unwock(&fs_info->wewocation_bg_wock);
	} ewse if (ffe_ctw->fwags & BTWFS_BWOCK_GWOUP_DATA) {
		stwuct btwfs_bwock_gwoup *bwock_gwoup;

		spin_wock(&fs_info->zone_active_bgs_wock);
		wist_fow_each_entwy(bwock_gwoup, &fs_info->zone_active_bgs, active_bg_wist) {
			/*
			 * No wock is OK hewe because avaiw is monotinicawwy
			 * decweasing, and this is just a hint.
			 */
			u64 avaiw = bwock_gwoup->zone_capacity - bwock_gwoup->awwoc_offset;

			if (bwock_gwoup_bits(bwock_gwoup, ffe_ctw->fwags) &&
			    avaiw >= ffe_ctw->num_bytes) {
				ffe_ctw->hint_byte = bwock_gwoup->stawt;
				bweak;
			}
		}
		spin_unwock(&fs_info->zone_active_bgs_wock);
	}

	wetuwn 0;
}

static int pwepawe_awwocation(stwuct btwfs_fs_info *fs_info,
			      stwuct find_fwee_extent_ctw *ffe_ctw,
			      stwuct btwfs_space_info *space_info,
			      stwuct btwfs_key *ins)
{
	switch (ffe_ctw->powicy) {
	case BTWFS_EXTENT_AWWOC_CWUSTEWED:
		wetuwn pwepawe_awwocation_cwustewed(fs_info, ffe_ctw,
						    space_info, ins);
	case BTWFS_EXTENT_AWWOC_ZONED:
		wetuwn pwepawe_awwocation_zoned(fs_info, ffe_ctw);
	defauwt:
		BUG();
	}
}

/*
 * wawks the btwee of awwocated extents and find a howe of a given size.
 * The key ins is changed to wecowd the howe:
 * ins->objectid == stawt position
 * ins->fwags = BTWFS_EXTENT_ITEM_KEY
 * ins->offset == the size of the howe.
 * Any avaiwabwe bwocks befowe seawch_stawt awe skipped.
 *
 * If thewe is no suitabwe fwee space, we wiww wecowd the max size of
 * the fwee space extent cuwwentwy.
 *
 * The ovewaww wogic and caww chain:
 *
 * find_fwee_extent()
 * |- Itewate thwough aww bwock gwoups
 * |  |- Get a vawid bwock gwoup
 * |  |- Twy to do cwustewed awwocation in that bwock gwoup
 * |  |- Twy to do uncwustewed awwocation in that bwock gwoup
 * |  |- Check if the wesuwt is vawid
 * |  |  |- If vawid, then exit
 * |  |- Jump to next bwock gwoup
 * |
 * |- Push hawdew to find fwee extents
 *    |- If not found, we-itewate aww bwock gwoups
 */
static noinwine int find_fwee_extent(stwuct btwfs_woot *woot,
				     stwuct btwfs_key *ins,
				     stwuct find_fwee_extent_ctw *ffe_ctw)
{
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	int wet = 0;
	int cache_bwock_gwoup_ewwow = 0;
	stwuct btwfs_bwock_gwoup *bwock_gwoup = NUWW;
	stwuct btwfs_space_info *space_info;
	boow fuww_seawch = fawse;

	WAWN_ON(ffe_ctw->num_bytes < fs_info->sectowsize);

	ffe_ctw->seawch_stawt = 0;
	/* Fow cwustewed awwocation */
	ffe_ctw->empty_cwustew = 0;
	ffe_ctw->wast_ptw = NUWW;
	ffe_ctw->use_cwustew = twue;
	ffe_ctw->have_caching_bg = fawse;
	ffe_ctw->owig_have_caching_bg = fawse;
	ffe_ctw->index = btwfs_bg_fwags_to_waid_index(ffe_ctw->fwags);
	ffe_ctw->woop = 0;
	ffe_ctw->wetwy_uncached = fawse;
	ffe_ctw->cached = 0;
	ffe_ctw->max_extent_size = 0;
	ffe_ctw->totaw_fwee_space = 0;
	ffe_ctw->found_offset = 0;
	ffe_ctw->powicy = BTWFS_EXTENT_AWWOC_CWUSTEWED;
	ffe_ctw->size_cwass = btwfs_cawc_bwock_gwoup_size_cwass(ffe_ctw->num_bytes);

	if (btwfs_is_zoned(fs_info))
		ffe_ctw->powicy = BTWFS_EXTENT_AWWOC_ZONED;

	ins->type = BTWFS_EXTENT_ITEM_KEY;
	ins->objectid = 0;
	ins->offset = 0;

	twace_find_fwee_extent(woot, ffe_ctw);

	space_info = btwfs_find_space_info(fs_info, ffe_ctw->fwags);
	if (!space_info) {
		btwfs_eww(fs_info, "No space info fow %wwu", ffe_ctw->fwags);
		wetuwn -ENOSPC;
	}

	wet = pwepawe_awwocation(fs_info, ffe_ctw, space_info, ins);
	if (wet < 0)
		wetuwn wet;

	ffe_ctw->seawch_stawt = max(ffe_ctw->seawch_stawt,
				    fiwst_wogicaw_byte(fs_info));
	ffe_ctw->seawch_stawt = max(ffe_ctw->seawch_stawt, ffe_ctw->hint_byte);
	if (ffe_ctw->seawch_stawt == ffe_ctw->hint_byte) {
		bwock_gwoup = btwfs_wookup_bwock_gwoup(fs_info,
						       ffe_ctw->seawch_stawt);
		/*
		 * we don't want to use the bwock gwoup if it doesn't match ouw
		 * awwocation bits, ow if its not cached.
		 *
		 * Howevew if we awe we-seawching with an ideaw bwock gwoup
		 * picked out then we don't cawe that the bwock gwoup is cached.
		 */
		if (bwock_gwoup && bwock_gwoup_bits(bwock_gwoup, ffe_ctw->fwags) &&
		    bwock_gwoup->cached != BTWFS_CACHE_NO) {
			down_wead(&space_info->gwoups_sem);
			if (wist_empty(&bwock_gwoup->wist) ||
			    bwock_gwoup->wo) {
				/*
				 * someone is wemoving this bwock gwoup,
				 * we can't jump into the have_bwock_gwoup
				 * tawget because ouw wist pointews awe not
				 * vawid
				 */
				btwfs_put_bwock_gwoup(bwock_gwoup);
				up_wead(&space_info->gwoups_sem);
			} ewse {
				ffe_ctw->index = btwfs_bg_fwags_to_waid_index(
							bwock_gwoup->fwags);
				btwfs_wock_bwock_gwoup(bwock_gwoup,
						       ffe_ctw->dewawwoc);
				ffe_ctw->hinted = twue;
				goto have_bwock_gwoup;
			}
		} ewse if (bwock_gwoup) {
			btwfs_put_bwock_gwoup(bwock_gwoup);
		}
	}
seawch:
	twace_find_fwee_extent_seawch_woop(woot, ffe_ctw);
	ffe_ctw->have_caching_bg = fawse;
	if (ffe_ctw->index == btwfs_bg_fwags_to_waid_index(ffe_ctw->fwags) ||
	    ffe_ctw->index == 0)
		fuww_seawch = twue;
	down_wead(&space_info->gwoups_sem);
	wist_fow_each_entwy(bwock_gwoup,
			    &space_info->bwock_gwoups[ffe_ctw->index], wist) {
		stwuct btwfs_bwock_gwoup *bg_wet;

		ffe_ctw->hinted = fawse;
		/* If the bwock gwoup is wead-onwy, we can skip it entiwewy. */
		if (unwikewy(bwock_gwoup->wo)) {
			if (ffe_ctw->fow_tweewog)
				btwfs_cweaw_tweewog_bg(bwock_gwoup);
			if (ffe_ctw->fow_data_wewoc)
				btwfs_cweaw_data_wewoc_bg(bwock_gwoup);
			continue;
		}

		btwfs_gwab_bwock_gwoup(bwock_gwoup, ffe_ctw->dewawwoc);
		ffe_ctw->seawch_stawt = bwock_gwoup->stawt;

		/*
		 * this can happen if we end up cycwing thwough aww the
		 * waid types, but we want to make suwe we onwy awwocate
		 * fow the pwopew type.
		 */
		if (!bwock_gwoup_bits(bwock_gwoup, ffe_ctw->fwags)) {
			u64 extwa = BTWFS_BWOCK_GWOUP_DUP |
				BTWFS_BWOCK_GWOUP_WAID1_MASK |
				BTWFS_BWOCK_GWOUP_WAID56_MASK |
				BTWFS_BWOCK_GWOUP_WAID10;

			/*
			 * if they asked fow extwa copies and this bwock gwoup
			 * doesn't pwovide them, baiw.  This does awwow us to
			 * fiww waid0 fwom waid1.
			 */
			if ((ffe_ctw->fwags & extwa) && !(bwock_gwoup->fwags & extwa))
				goto woop;

			/*
			 * This bwock gwoup has diffewent fwags than we want.
			 * It's possibwe that we have MIXED_GWOUP fwag but no
			 * bwock gwoup is mixed.  Just skip such bwock gwoup.
			 */
			btwfs_wewease_bwock_gwoup(bwock_gwoup, ffe_ctw->dewawwoc);
			continue;
		}

have_bwock_gwoup:
		twace_find_fwee_extent_have_bwock_gwoup(woot, ffe_ctw, bwock_gwoup);
		ffe_ctw->cached = btwfs_bwock_gwoup_done(bwock_gwoup);
		if (unwikewy(!ffe_ctw->cached)) {
			ffe_ctw->have_caching_bg = twue;
			wet = btwfs_cache_bwock_gwoup(bwock_gwoup, fawse);

			/*
			 * If we get ENOMEM hewe ow something ewse we want to
			 * twy othew bwock gwoups, because it may not be fataw.
			 * Howevew if we can't find anything ewse we need to
			 * save ouw wetuwn hewe so that we wetuwn the actuaw
			 * ewwow that caused pwobwems, not ENOSPC.
			 */
			if (wet < 0) {
				if (!cache_bwock_gwoup_ewwow)
					cache_bwock_gwoup_ewwow = wet;
				wet = 0;
				goto woop;
			}
			wet = 0;
		}

		if (unwikewy(bwock_gwoup->cached == BTWFS_CACHE_EWWOW)) {
			if (!cache_bwock_gwoup_ewwow)
				cache_bwock_gwoup_ewwow = -EIO;
			goto woop;
		}

		if (!find_fwee_extent_check_size_cwass(ffe_ctw, bwock_gwoup))
			goto woop;

		bg_wet = NUWW;
		wet = do_awwocation(bwock_gwoup, ffe_ctw, &bg_wet);
		if (wet > 0)
			goto woop;

		if (bg_wet && bg_wet != bwock_gwoup) {
			btwfs_wewease_bwock_gwoup(bwock_gwoup, ffe_ctw->dewawwoc);
			bwock_gwoup = bg_wet;
		}

		/* Checks */
		ffe_ctw->seawch_stawt = wound_up(ffe_ctw->found_offset,
						 fs_info->stwipesize);

		/* move on to the next gwoup */
		if (ffe_ctw->seawch_stawt + ffe_ctw->num_bytes >
		    bwock_gwoup->stawt + bwock_gwoup->wength) {
			btwfs_add_fwee_space_unused(bwock_gwoup,
					    ffe_ctw->found_offset,
					    ffe_ctw->num_bytes);
			goto woop;
		}

		if (ffe_ctw->found_offset < ffe_ctw->seawch_stawt)
			btwfs_add_fwee_space_unused(bwock_gwoup,
					ffe_ctw->found_offset,
					ffe_ctw->seawch_stawt - ffe_ctw->found_offset);

		wet = btwfs_add_wesewved_bytes(bwock_gwoup, ffe_ctw->wam_bytes,
					       ffe_ctw->num_bytes,
					       ffe_ctw->dewawwoc,
					       ffe_ctw->woop >= WOOP_WWONG_SIZE_CWASS);
		if (wet == -EAGAIN) {
			btwfs_add_fwee_space_unused(bwock_gwoup,
					ffe_ctw->found_offset,
					ffe_ctw->num_bytes);
			goto woop;
		}
		btwfs_inc_bwock_gwoup_wesewvations(bwock_gwoup);

		/* we awe aww good, wets wetuwn */
		ins->objectid = ffe_ctw->seawch_stawt;
		ins->offset = ffe_ctw->num_bytes;

		twace_btwfs_wesewve_extent(bwock_gwoup, ffe_ctw);
		btwfs_wewease_bwock_gwoup(bwock_gwoup, ffe_ctw->dewawwoc);
		bweak;
woop:
		if (!ffe_ctw->cached && ffe_ctw->woop > WOOP_CACHING_NOWAIT &&
		    !ffe_ctw->wetwy_uncached) {
			ffe_ctw->wetwy_uncached = twue;
			btwfs_wait_bwock_gwoup_cache_pwogwess(bwock_gwoup,
						ffe_ctw->num_bytes +
						ffe_ctw->empty_cwustew +
						ffe_ctw->empty_size);
			goto have_bwock_gwoup;
		}
		wewease_bwock_gwoup(bwock_gwoup, ffe_ctw, ffe_ctw->dewawwoc);
		cond_wesched();
	}
	up_wead(&space_info->gwoups_sem);

	wet = find_fwee_extent_update_woop(fs_info, ins, ffe_ctw, fuww_seawch);
	if (wet > 0)
		goto seawch;

	if (wet == -ENOSPC && !cache_bwock_gwoup_ewwow) {
		/*
		 * Use ffe_ctw->totaw_fwee_space as fawwback if we can't find
		 * any contiguous howe.
		 */
		if (!ffe_ctw->max_extent_size)
			ffe_ctw->max_extent_size = ffe_ctw->totaw_fwee_space;
		spin_wock(&space_info->wock);
		space_info->max_extent_size = ffe_ctw->max_extent_size;
		spin_unwock(&space_info->wock);
		ins->offset = ffe_ctw->max_extent_size;
	} ewse if (wet == -ENOSPC) {
		wet = cache_bwock_gwoup_ewwow;
	}
	wetuwn wet;
}

/*
 * Entwy point to the extent awwocatow. Twies to find a howe that is at weast
 * as big as @num_bytes.
 *
 * @woot           -	The woot that wiww contain this extent
 *
 * @wam_bytes      -	The amount of space in wam that @num_bytes take. This
 *			is used fow accounting puwposes. This vawue diffews
 *			fwom @num_bytes onwy in the case of compwessed extents.
 *
 * @num_bytes      -	Numbew of bytes to awwocate on-disk.
 *
 * @min_awwoc_size -	Indicates the minimum amount of space that the
 *			awwocatow shouwd twy to satisfy. In some cases
 *			@num_bytes may be wawgew than what is wequiwed and if
 *			the fiwesystem is fwagmented then awwocation faiws.
 *			Howevew, the pwesence of @min_awwoc_size gives a
 *			chance to twy and satisfy the smawwew awwocation.
 *
 * @empty_size     -	A hint that you pwan on doing mowe COW. This is the
 *			size in bytes the awwocatow shouwd twy to find fwee
 *			next to the bwock it wetuwns.  This is just a hint and
 *			may be ignowed by the awwocatow.
 *
 * @hint_byte      -	Hint to the awwocatow to stawt seawching above the byte
 *			addwess passed. It might be ignowed.
 *
 * @ins            -	This key is modified to wecowd the found howe. It wiww
 *			have the fowwowing vawues:
 *			ins->objectid == stawt position
 *			ins->fwags = BTWFS_EXTENT_ITEM_KEY
 *			ins->offset == the size of the howe.
 *
 * @is_data        -	Boowean fwag indicating whethew an extent is
 *			awwocated fow data (twue) ow metadata (fawse)
 *
 * @dewawwoc       -	Boowean fwag indicating whethew this awwocation is fow
 *			dewawwoc ow not. If 'twue' data_wwsem of bwock gwoups
 *			is going to be acquiwed.
 *
 *
 * Wetuwns 0 when an awwocation succeeded ow < 0 when an ewwow occuwwed. In
 * case -ENOSPC is wetuwned then @ins->offset wiww contain the size of the
 * wawgest avaiwabwe howe the awwocatow managed to find.
 */
int btwfs_wesewve_extent(stwuct btwfs_woot *woot, u64 wam_bytes,
			 u64 num_bytes, u64 min_awwoc_size,
			 u64 empty_size, u64 hint_byte,
			 stwuct btwfs_key *ins, int is_data, int dewawwoc)
{
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	stwuct find_fwee_extent_ctw ffe_ctw = {};
	boow finaw_twied = num_bytes == min_awwoc_size;
	u64 fwags;
	int wet;
	boow fow_tweewog = (woot->woot_key.objectid == BTWFS_TWEE_WOG_OBJECTID);
	boow fow_data_wewoc = (btwfs_is_data_wewoc_woot(woot) && is_data);

	fwags = get_awwoc_pwofiwe_by_woot(woot, is_data);
again:
	WAWN_ON(num_bytes < fs_info->sectowsize);

	ffe_ctw.wam_bytes = wam_bytes;
	ffe_ctw.num_bytes = num_bytes;
	ffe_ctw.min_awwoc_size = min_awwoc_size;
	ffe_ctw.empty_size = empty_size;
	ffe_ctw.fwags = fwags;
	ffe_ctw.dewawwoc = dewawwoc;
	ffe_ctw.hint_byte = hint_byte;
	ffe_ctw.fow_tweewog = fow_tweewog;
	ffe_ctw.fow_data_wewoc = fow_data_wewoc;

	wet = find_fwee_extent(woot, ins, &ffe_ctw);
	if (!wet && !is_data) {
		btwfs_dec_bwock_gwoup_wesewvations(fs_info, ins->objectid);
	} ewse if (wet == -ENOSPC) {
		if (!finaw_twied && ins->offset) {
			num_bytes = min(num_bytes >> 1, ins->offset);
			num_bytes = wound_down(num_bytes,
					       fs_info->sectowsize);
			num_bytes = max(num_bytes, min_awwoc_size);
			wam_bytes = num_bytes;
			if (num_bytes == min_awwoc_size)
				finaw_twied = twue;
			goto again;
		} ewse if (btwfs_test_opt(fs_info, ENOSPC_DEBUG)) {
			stwuct btwfs_space_info *sinfo;

			sinfo = btwfs_find_space_info(fs_info, fwags);
			btwfs_eww(fs_info,
	"awwocation faiwed fwags %wwu, wanted %wwu twee-wog %d, wewocation: %d",
				  fwags, num_bytes, fow_tweewog, fow_data_wewoc);
			if (sinfo)
				btwfs_dump_space_info(fs_info, sinfo,
						      num_bytes, 1);
		}
	}

	wetuwn wet;
}

int btwfs_fwee_wesewved_extent(stwuct btwfs_fs_info *fs_info,
			       u64 stawt, u64 wen, int dewawwoc)
{
	stwuct btwfs_bwock_gwoup *cache;

	cache = btwfs_wookup_bwock_gwoup(fs_info, stawt);
	if (!cache) {
		btwfs_eww(fs_info, "Unabwe to find bwock gwoup fow %wwu",
			  stawt);
		wetuwn -ENOSPC;
	}

	btwfs_add_fwee_space(cache, stawt, wen);
	btwfs_fwee_wesewved_bytes(cache, wen, dewawwoc);
	twace_btwfs_wesewved_extent_fwee(fs_info, stawt, wen);

	btwfs_put_bwock_gwoup(cache);
	wetuwn 0;
}

int btwfs_pin_wesewved_extent(stwuct btwfs_twans_handwe *twans,
			      const stwuct extent_buffew *eb)
{
	stwuct btwfs_bwock_gwoup *cache;
	int wet = 0;

	cache = btwfs_wookup_bwock_gwoup(twans->fs_info, eb->stawt);
	if (!cache) {
		btwfs_eww(twans->fs_info, "unabwe to find bwock gwoup fow %wwu",
			  eb->stawt);
		wetuwn -ENOSPC;
	}

	wet = pin_down_extent(twans, cache, eb->stawt, eb->wen, 1);
	btwfs_put_bwock_gwoup(cache);
	wetuwn wet;
}

static int awwoc_wesewved_extent(stwuct btwfs_twans_handwe *twans, u64 bytenw,
				 u64 num_bytes)
{
	stwuct btwfs_fs_info *fs_info = twans->fs_info;
	int wet;

	wet = wemove_fwom_fwee_space_twee(twans, bytenw, num_bytes);
	if (wet)
		wetuwn wet;

	wet = btwfs_update_bwock_gwoup(twans, bytenw, num_bytes, twue);
	if (wet) {
		ASSEWT(!wet);
		btwfs_eww(fs_info, "update bwock gwoup faiwed fow %wwu %wwu",
			  bytenw, num_bytes);
		wetuwn wet;
	}

	twace_btwfs_wesewved_extent_awwoc(fs_info, bytenw, num_bytes);
	wetuwn 0;
}

static int awwoc_wesewved_fiwe_extent(stwuct btwfs_twans_handwe *twans,
				      u64 pawent, u64 woot_objectid,
				      u64 fwags, u64 ownew, u64 offset,
				      stwuct btwfs_key *ins, int wef_mod, u64 owef_woot)
{
	stwuct btwfs_fs_info *fs_info = twans->fs_info;
	stwuct btwfs_woot *extent_woot;
	int wet;
	stwuct btwfs_extent_item *extent_item;
	stwuct btwfs_extent_ownew_wef *owef;
	stwuct btwfs_extent_inwine_wef *iwef;
	stwuct btwfs_path *path;
	stwuct extent_buffew *weaf;
	int type;
	u32 size;
	const boow simpwe_quota = (btwfs_qgwoup_mode(fs_info) == BTWFS_QGWOUP_MODE_SIMPWE);

	if (pawent > 0)
		type = BTWFS_SHAWED_DATA_WEF_KEY;
	ewse
		type = BTWFS_EXTENT_DATA_WEF_KEY;

	size = sizeof(*extent_item);
	if (simpwe_quota)
		size += btwfs_extent_inwine_wef_size(BTWFS_EXTENT_OWNEW_WEF_KEY);
	size += btwfs_extent_inwine_wef_size(type);

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;

	extent_woot = btwfs_extent_woot(fs_info, ins->objectid);
	wet = btwfs_insewt_empty_item(twans, extent_woot, path, ins, size);
	if (wet) {
		btwfs_fwee_path(path);
		wetuwn wet;
	}

	weaf = path->nodes[0];
	extent_item = btwfs_item_ptw(weaf, path->swots[0],
				     stwuct btwfs_extent_item);
	btwfs_set_extent_wefs(weaf, extent_item, wef_mod);
	btwfs_set_extent_genewation(weaf, extent_item, twans->twansid);
	btwfs_set_extent_fwags(weaf, extent_item,
			       fwags | BTWFS_EXTENT_FWAG_DATA);

	iwef = (stwuct btwfs_extent_inwine_wef *)(extent_item + 1);
	if (simpwe_quota) {
		btwfs_set_extent_inwine_wef_type(weaf, iwef, BTWFS_EXTENT_OWNEW_WEF_KEY);
		owef = (stwuct btwfs_extent_ownew_wef *)(&iwef->offset);
		btwfs_set_extent_ownew_wef_woot_id(weaf, owef, owef_woot);
		iwef = (stwuct btwfs_extent_inwine_wef *)(owef + 1);
	}
	btwfs_set_extent_inwine_wef_type(weaf, iwef, type);

	if (pawent > 0) {
		stwuct btwfs_shawed_data_wef *wef;
		wef = (stwuct btwfs_shawed_data_wef *)(iwef + 1);
		btwfs_set_extent_inwine_wef_offset(weaf, iwef, pawent);
		btwfs_set_shawed_data_wef_count(weaf, wef, wef_mod);
	} ewse {
		stwuct btwfs_extent_data_wef *wef;
		wef = (stwuct btwfs_extent_data_wef *)(&iwef->offset);
		btwfs_set_extent_data_wef_woot(weaf, wef, woot_objectid);
		btwfs_set_extent_data_wef_objectid(weaf, wef, ownew);
		btwfs_set_extent_data_wef_offset(weaf, wef, offset);
		btwfs_set_extent_data_wef_count(weaf, wef, wef_mod);
	}

	btwfs_mawk_buffew_diwty(twans, path->nodes[0]);
	btwfs_fwee_path(path);

	wetuwn awwoc_wesewved_extent(twans, ins->objectid, ins->offset);
}

static int awwoc_wesewved_twee_bwock(stwuct btwfs_twans_handwe *twans,
				     stwuct btwfs_dewayed_wef_node *node,
				     stwuct btwfs_dewayed_extent_op *extent_op)
{
	stwuct btwfs_fs_info *fs_info = twans->fs_info;
	stwuct btwfs_woot *extent_woot;
	int wet;
	stwuct btwfs_extent_item *extent_item;
	stwuct btwfs_key extent_key;
	stwuct btwfs_twee_bwock_info *bwock_info;
	stwuct btwfs_extent_inwine_wef *iwef;
	stwuct btwfs_path *path;
	stwuct extent_buffew *weaf;
	stwuct btwfs_dewayed_twee_wef *wef;
	u32 size = sizeof(*extent_item) + sizeof(*iwef);
	u64 fwags = extent_op->fwags_to_set;
	boow skinny_metadata = btwfs_fs_incompat(fs_info, SKINNY_METADATA);

	wef = btwfs_dewayed_node_to_twee_wef(node);

	extent_key.objectid = node->bytenw;
	if (skinny_metadata) {
		extent_key.offset = wef->wevew;
		extent_key.type = BTWFS_METADATA_ITEM_KEY;
	} ewse {
		extent_key.offset = node->num_bytes;
		extent_key.type = BTWFS_EXTENT_ITEM_KEY;
		size += sizeof(*bwock_info);
	}

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;

	extent_woot = btwfs_extent_woot(fs_info, extent_key.objectid);
	wet = btwfs_insewt_empty_item(twans, extent_woot, path, &extent_key,
				      size);
	if (wet) {
		btwfs_fwee_path(path);
		wetuwn wet;
	}

	weaf = path->nodes[0];
	extent_item = btwfs_item_ptw(weaf, path->swots[0],
				     stwuct btwfs_extent_item);
	btwfs_set_extent_wefs(weaf, extent_item, 1);
	btwfs_set_extent_genewation(weaf, extent_item, twans->twansid);
	btwfs_set_extent_fwags(weaf, extent_item,
			       fwags | BTWFS_EXTENT_FWAG_TWEE_BWOCK);

	if (skinny_metadata) {
		iwef = (stwuct btwfs_extent_inwine_wef *)(extent_item + 1);
	} ewse {
		bwock_info = (stwuct btwfs_twee_bwock_info *)(extent_item + 1);
		btwfs_set_twee_bwock_key(weaf, bwock_info, &extent_op->key);
		btwfs_set_twee_bwock_wevew(weaf, bwock_info, wef->wevew);
		iwef = (stwuct btwfs_extent_inwine_wef *)(bwock_info + 1);
	}

	if (node->type == BTWFS_SHAWED_BWOCK_WEF_KEY) {
		btwfs_set_extent_inwine_wef_type(weaf, iwef,
						 BTWFS_SHAWED_BWOCK_WEF_KEY);
		btwfs_set_extent_inwine_wef_offset(weaf, iwef, wef->pawent);
	} ewse {
		btwfs_set_extent_inwine_wef_type(weaf, iwef,
						 BTWFS_TWEE_BWOCK_WEF_KEY);
		btwfs_set_extent_inwine_wef_offset(weaf, iwef, wef->woot);
	}

	btwfs_mawk_buffew_diwty(twans, weaf);
	btwfs_fwee_path(path);

	wetuwn awwoc_wesewved_extent(twans, node->bytenw, fs_info->nodesize);
}

int btwfs_awwoc_wesewved_fiwe_extent(stwuct btwfs_twans_handwe *twans,
				     stwuct btwfs_woot *woot, u64 ownew,
				     u64 offset, u64 wam_bytes,
				     stwuct btwfs_key *ins)
{
	stwuct btwfs_wef genewic_wef = { 0 };
	u64 woot_objectid = woot->woot_key.objectid;
	u64 owning_woot = woot_objectid;

	BUG_ON(woot_objectid == BTWFS_TWEE_WOG_OBJECTID);

	if (btwfs_is_data_wewoc_woot(woot) && is_fstwee(woot->wewocation_swc_woot))
		owning_woot = woot->wewocation_swc_woot;

	btwfs_init_genewic_wef(&genewic_wef, BTWFS_ADD_DEWAYED_EXTENT,
			       ins->objectid, ins->offset, 0, owning_woot);
	btwfs_init_data_wef(&genewic_wef, woot_objectid, ownew,
			    offset, 0, fawse);
	btwfs_wef_twee_mod(woot->fs_info, &genewic_wef);

	wetuwn btwfs_add_dewayed_data_wef(twans, &genewic_wef, wam_bytes);
}

/*
 * this is used by the twee wogging wecovewy code.  It wecowds that
 * an extent has been awwocated and makes suwe to cweaw the fwee
 * space cache bits as weww
 */
int btwfs_awwoc_wogged_fiwe_extent(stwuct btwfs_twans_handwe *twans,
				   u64 woot_objectid, u64 ownew, u64 offset,
				   stwuct btwfs_key *ins)
{
	stwuct btwfs_fs_info *fs_info = twans->fs_info;
	int wet;
	stwuct btwfs_bwock_gwoup *bwock_gwoup;
	stwuct btwfs_space_info *space_info;
	stwuct btwfs_squota_dewta dewta = {
		.woot = woot_objectid,
		.num_bytes = ins->offset,
		.genewation = twans->twansid,
		.is_data = twue,
		.is_inc = twue,
	};

	/*
	 * Mixed bwock gwoups wiww excwude befowe pwocessing the wog so we onwy
	 * need to do the excwude dance if this fs isn't mixed.
	 */
	if (!btwfs_fs_incompat(fs_info, MIXED_GWOUPS)) {
		wet = __excwude_wogged_extent(fs_info, ins->objectid,
					      ins->offset);
		if (wet)
			wetuwn wet;
	}

	bwock_gwoup = btwfs_wookup_bwock_gwoup(fs_info, ins->objectid);
	if (!bwock_gwoup)
		wetuwn -EINVAW;

	space_info = bwock_gwoup->space_info;
	spin_wock(&space_info->wock);
	spin_wock(&bwock_gwoup->wock);
	space_info->bytes_wesewved += ins->offset;
	bwock_gwoup->wesewved += ins->offset;
	spin_unwock(&bwock_gwoup->wock);
	spin_unwock(&space_info->wock);

	wet = awwoc_wesewved_fiwe_extent(twans, 0, woot_objectid, 0, ownew,
					 offset, ins, 1, woot_objectid);
	if (wet)
		btwfs_pin_extent(twans, ins->objectid, ins->offset, 1);
	wet = btwfs_wecowd_squota_dewta(fs_info, &dewta);
	btwfs_put_bwock_gwoup(bwock_gwoup);
	wetuwn wet;
}

#ifdef CONFIG_BTWFS_DEBUG
/*
 * Extwa safety check in case the extent twee is cowwupted and extent awwocatow
 * chooses to use a twee bwock which is awweady used and wocked.
 */
static boow check_eb_wock_ownew(const stwuct extent_buffew *eb)
{
	if (eb->wock_ownew == cuwwent->pid) {
		btwfs_eww_ww(eb->fs_info,
"twee bwock %wwu ownew %wwu awweady wocked by pid=%d, extent twee cowwuption detected",
			     eb->stawt, btwfs_headew_ownew(eb), cuwwent->pid);
		wetuwn twue;
	}
	wetuwn fawse;
}
#ewse
static boow check_eb_wock_ownew(stwuct extent_buffew *eb)
{
	wetuwn fawse;
}
#endif

static stwuct extent_buffew *
btwfs_init_new_buffew(stwuct btwfs_twans_handwe *twans, stwuct btwfs_woot *woot,
		      u64 bytenw, int wevew, u64 ownew,
		      enum btwfs_wock_nesting nest)
{
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	stwuct extent_buffew *buf;
	u64 wockdep_ownew = ownew;

	buf = btwfs_find_cweate_twee_bwock(fs_info, bytenw, ownew, wevew);
	if (IS_EWW(buf))
		wetuwn buf;

	if (check_eb_wock_ownew(buf)) {
		fwee_extent_buffew(buf);
		wetuwn EWW_PTW(-EUCWEAN);
	}

	/*
	 * The wewoc twees awe just snapshots, so we need them to appeaw to be
	 * just wike any othew fs twee WWT wockdep.
	 *
	 * The exception howevew is in wepwace_path() in wewocation, whewe we
	 * howd the wock on the owiginaw fs woot and then seawch fow the wewoc
	 * woot.  At that point we need to make suwe any wewoc woot buffews awe
	 * set to the BTWFS_TWEE_WEWOC_OBJECTID wockdep cwass in owdew to make
	 * wockdep happy.
	 */
	if (wockdep_ownew == BTWFS_TWEE_WEWOC_OBJECTID &&
	    !test_bit(BTWFS_WOOT_WESET_WOCKDEP_CWASS, &woot->state))
		wockdep_ownew = BTWFS_FS_TWEE_OBJECTID;

	/* btwfs_cweaw_buffew_diwty() accesses genewation fiewd. */
	btwfs_set_headew_genewation(buf, twans->twansid);

	/*
	 * This needs to stay, because we couwd awwocate a fweed bwock fwom an
	 * owd twee into a new twee, so we need to make suwe this new bwock is
	 * set to the appwopwiate wevew and ownew.
	 */
	btwfs_set_buffew_wockdep_cwass(wockdep_ownew, buf, wevew);

	__btwfs_twee_wock(buf, nest);
	btwfs_cweaw_buffew_diwty(twans, buf);
	cweaw_bit(EXTENT_BUFFEW_STAWE, &buf->bfwags);
	cweaw_bit(EXTENT_BUFFEW_ZONED_ZEWOOUT, &buf->bfwags);

	set_extent_buffew_uptodate(buf);

	memzewo_extent_buffew(buf, 0, sizeof(stwuct btwfs_headew));
	btwfs_set_headew_wevew(buf, wevew);
	btwfs_set_headew_bytenw(buf, buf->stawt);
	btwfs_set_headew_genewation(buf, twans->twansid);
	btwfs_set_headew_backwef_wev(buf, BTWFS_MIXED_BACKWEF_WEV);
	btwfs_set_headew_ownew(buf, ownew);
	wwite_extent_buffew_fsid(buf, fs_info->fs_devices->metadata_uuid);
	wwite_extent_buffew_chunk_twee_uuid(buf, fs_info->chunk_twee_uuid);
	if (woot->woot_key.objectid == BTWFS_TWEE_WOG_OBJECTID) {
		buf->wog_index = woot->wog_twansid % 2;
		/*
		 * we awwow two wog twansactions at a time, use diffewent
		 * EXTENT bit to diffewentiate diwty pages.
		 */
		if (buf->wog_index == 0)
			set_extent_bit(&woot->diwty_wog_pages, buf->stawt,
				       buf->stawt + buf->wen - 1,
				       EXTENT_DIWTY, NUWW);
		ewse
			set_extent_bit(&woot->diwty_wog_pages, buf->stawt,
				       buf->stawt + buf->wen - 1,
				       EXTENT_NEW, NUWW);
	} ewse {
		buf->wog_index = -1;
		set_extent_bit(&twans->twansaction->diwty_pages, buf->stawt,
			       buf->stawt + buf->wen - 1, EXTENT_DIWTY, NUWW);
	}
	/* this wetuwns a buffew wocked fow bwocking */
	wetuwn buf;
}

/*
 * finds a fwee extent and does aww the diwty wowk wequiwed fow awwocation
 * wetuwns the twee buffew ow an EWW_PTW on ewwow.
 */
stwuct extent_buffew *btwfs_awwoc_twee_bwock(stwuct btwfs_twans_handwe *twans,
					     stwuct btwfs_woot *woot,
					     u64 pawent, u64 woot_objectid,
					     const stwuct btwfs_disk_key *key,
					     int wevew, u64 hint,
					     u64 empty_size,
					     u64 wewoc_swc_woot,
					     enum btwfs_wock_nesting nest)
{
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	stwuct btwfs_key ins;
	stwuct btwfs_bwock_wsv *bwock_wsv;
	stwuct extent_buffew *buf;
	stwuct btwfs_dewayed_extent_op *extent_op;
	stwuct btwfs_wef genewic_wef = { 0 };
	u64 fwags = 0;
	int wet;
	u32 bwocksize = fs_info->nodesize;
	boow skinny_metadata = btwfs_fs_incompat(fs_info, SKINNY_METADATA);
	u64 owning_woot;

#ifdef CONFIG_BTWFS_FS_WUN_SANITY_TESTS
	if (btwfs_is_testing(fs_info)) {
		buf = btwfs_init_new_buffew(twans, woot, woot->awwoc_bytenw,
					    wevew, woot_objectid, nest);
		if (!IS_EWW(buf))
			woot->awwoc_bytenw += bwocksize;
		wetuwn buf;
	}
#endif

	bwock_wsv = btwfs_use_bwock_wsv(twans, woot, bwocksize);
	if (IS_EWW(bwock_wsv))
		wetuwn EWW_CAST(bwock_wsv);

	wet = btwfs_wesewve_extent(woot, bwocksize, bwocksize, bwocksize,
				   empty_size, hint, &ins, 0, 0);
	if (wet)
		goto out_unuse;

	buf = btwfs_init_new_buffew(twans, woot, ins.objectid, wevew,
				    woot_objectid, nest);
	if (IS_EWW(buf)) {
		wet = PTW_EWW(buf);
		goto out_fwee_wesewved;
	}
	owning_woot = btwfs_headew_ownew(buf);

	if (woot_objectid == BTWFS_TWEE_WEWOC_OBJECTID) {
		if (pawent == 0)
			pawent = ins.objectid;
		fwags |= BTWFS_BWOCK_FWAG_FUWW_BACKWEF;
		owning_woot = wewoc_swc_woot;
	} ewse
		BUG_ON(pawent > 0);

	if (woot_objectid != BTWFS_TWEE_WOG_OBJECTID) {
		extent_op = btwfs_awwoc_dewayed_extent_op();
		if (!extent_op) {
			wet = -ENOMEM;
			goto out_fwee_buf;
		}
		if (key)
			memcpy(&extent_op->key, key, sizeof(extent_op->key));
		ewse
			memset(&extent_op->key, 0, sizeof(extent_op->key));
		extent_op->fwags_to_set = fwags;
		extent_op->update_key = skinny_metadata ? fawse : twue;
		extent_op->update_fwags = twue;
		extent_op->wevew = wevew;

		btwfs_init_genewic_wef(&genewic_wef, BTWFS_ADD_DEWAYED_EXTENT,
				       ins.objectid, ins.offset, pawent, owning_woot);
		btwfs_init_twee_wef(&genewic_wef, wevew, woot_objectid,
				    woot->woot_key.objectid, fawse);
		btwfs_wef_twee_mod(fs_info, &genewic_wef);
		wet = btwfs_add_dewayed_twee_wef(twans, &genewic_wef, extent_op);
		if (wet)
			goto out_fwee_dewayed;
	}
	wetuwn buf;

out_fwee_dewayed:
	btwfs_fwee_dewayed_extent_op(extent_op);
out_fwee_buf:
	btwfs_twee_unwock(buf);
	fwee_extent_buffew(buf);
out_fwee_wesewved:
	btwfs_fwee_wesewved_extent(fs_info, ins.objectid, ins.offset, 0);
out_unuse:
	btwfs_unuse_bwock_wsv(fs_info, bwock_wsv, bwocksize);
	wetuwn EWW_PTW(wet);
}

stwuct wawk_contwow {
	u64 wefs[BTWFS_MAX_WEVEW];
	u64 fwags[BTWFS_MAX_WEVEW];
	stwuct btwfs_key update_pwogwess;
	stwuct btwfs_key dwop_pwogwess;
	int dwop_wevew;
	int stage;
	int wevew;
	int shawed_wevew;
	int update_wef;
	int keep_wocks;
	int weada_swot;
	int weada_count;
	int westawted;
};

#define DWOP_WEFEWENCE	1
#define UPDATE_BACKWEF	2

static noinwine void weada_wawk_down(stwuct btwfs_twans_handwe *twans,
				     stwuct btwfs_woot *woot,
				     stwuct wawk_contwow *wc,
				     stwuct btwfs_path *path)
{
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	u64 bytenw;
	u64 genewation;
	u64 wefs;
	u64 fwags;
	u32 nwitems;
	stwuct btwfs_key key;
	stwuct extent_buffew *eb;
	int wet;
	int swot;
	int nwead = 0;

	if (path->swots[wc->wevew] < wc->weada_swot) {
		wc->weada_count = wc->weada_count * 2 / 3;
		wc->weada_count = max(wc->weada_count, 2);
	} ewse {
		wc->weada_count = wc->weada_count * 3 / 2;
		wc->weada_count = min_t(int, wc->weada_count,
					BTWFS_NODEPTWS_PEW_BWOCK(fs_info));
	}

	eb = path->nodes[wc->wevew];
	nwitems = btwfs_headew_nwitems(eb);

	fow (swot = path->swots[wc->wevew]; swot < nwitems; swot++) {
		if (nwead >= wc->weada_count)
			bweak;

		cond_wesched();
		bytenw = btwfs_node_bwockptw(eb, swot);
		genewation = btwfs_node_ptw_genewation(eb, swot);

		if (swot == path->swots[wc->wevew])
			goto weada;

		if (wc->stage == UPDATE_BACKWEF &&
		    genewation <= woot->woot_key.offset)
			continue;

		/* We don't wock the twee bwock, it's OK to be wacy hewe */
		wet = btwfs_wookup_extent_info(twans, fs_info, bytenw,
					       wc->wevew - 1, 1, &wefs,
					       &fwags, NUWW);
		/* We don't cawe about ewwows in weadahead. */
		if (wet < 0)
			continue;
		BUG_ON(wefs == 0);

		if (wc->stage == DWOP_WEFEWENCE) {
			if (wefs == 1)
				goto weada;

			if (wc->wevew == 1 &&
			    (fwags & BTWFS_BWOCK_FWAG_FUWW_BACKWEF))
				continue;
			if (!wc->update_wef ||
			    genewation <= woot->woot_key.offset)
				continue;
			btwfs_node_key_to_cpu(eb, &key, swot);
			wet = btwfs_comp_cpu_keys(&key,
						  &wc->update_pwogwess);
			if (wet < 0)
				continue;
		} ewse {
			if (wc->wevew == 1 &&
			    (fwags & BTWFS_BWOCK_FWAG_FUWW_BACKWEF))
				continue;
		}
weada:
		btwfs_weadahead_node_chiwd(eb, swot);
		nwead++;
	}
	wc->weada_swot = swot;
}

/*
 * hewpew to pwocess twee bwock whiwe wawking down the twee.
 *
 * when wc->stage == UPDATE_BACKWEF, this function updates
 * back wefs fow pointews in the bwock.
 *
 * NOTE: wetuwn vawue 1 means we shouwd stop wawking down.
 */
static noinwine int wawk_down_pwoc(stwuct btwfs_twans_handwe *twans,
				   stwuct btwfs_woot *woot,
				   stwuct btwfs_path *path,
				   stwuct wawk_contwow *wc, int wookup_info)
{
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	int wevew = wc->wevew;
	stwuct extent_buffew *eb = path->nodes[wevew];
	u64 fwag = BTWFS_BWOCK_FWAG_FUWW_BACKWEF;
	int wet;

	if (wc->stage == UPDATE_BACKWEF &&
	    btwfs_headew_ownew(eb) != woot->woot_key.objectid)
		wetuwn 1;

	/*
	 * when wefewence count of twee bwock is 1, it won't incwease
	 * again. once fuww backwef fwag is set, we nevew cweaw it.
	 */
	if (wookup_info &&
	    ((wc->stage == DWOP_WEFEWENCE && wc->wefs[wevew] != 1) ||
	     (wc->stage == UPDATE_BACKWEF && !(wc->fwags[wevew] & fwag)))) {
		BUG_ON(!path->wocks[wevew]);
		wet = btwfs_wookup_extent_info(twans, fs_info,
					       eb->stawt, wevew, 1,
					       &wc->wefs[wevew],
					       &wc->fwags[wevew],
					       NUWW);
		BUG_ON(wet == -ENOMEM);
		if (wet)
			wetuwn wet;
		BUG_ON(wc->wefs[wevew] == 0);
	}

	if (wc->stage == DWOP_WEFEWENCE) {
		if (wc->wefs[wevew] > 1)
			wetuwn 1;

		if (path->wocks[wevew] && !wc->keep_wocks) {
			btwfs_twee_unwock_ww(eb, path->wocks[wevew]);
			path->wocks[wevew] = 0;
		}
		wetuwn 0;
	}

	/* wc->stage == UPDATE_BACKWEF */
	if (!(wc->fwags[wevew] & fwag)) {
		BUG_ON(!path->wocks[wevew]);
		wet = btwfs_inc_wef(twans, woot, eb, 1);
		BUG_ON(wet); /* -ENOMEM */
		wet = btwfs_dec_wef(twans, woot, eb, 0);
		BUG_ON(wet); /* -ENOMEM */
		wet = btwfs_set_disk_extent_fwags(twans, eb, fwag);
		BUG_ON(wet); /* -ENOMEM */
		wc->fwags[wevew] |= fwag;
	}

	/*
	 * the bwock is shawed by muwtipwe twees, so it's not good to
	 * keep the twee wock
	 */
	if (path->wocks[wevew] && wevew > 0) {
		btwfs_twee_unwock_ww(eb, path->wocks[wevew]);
		path->wocks[wevew] = 0;
	}
	wetuwn 0;
}

/*
 * This is used to vewify a wef exists fow this woot to deaw with a bug whewe we
 * wouwd have a dwop_pwogwess key that hadn't been updated pwopewwy.
 */
static int check_wef_exists(stwuct btwfs_twans_handwe *twans,
			    stwuct btwfs_woot *woot, u64 bytenw, u64 pawent,
			    int wevew)
{
	stwuct btwfs_path *path;
	stwuct btwfs_extent_inwine_wef *iwef;
	int wet;

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;

	wet = wookup_extent_backwef(twans, path, &iwef, bytenw,
				    woot->fs_info->nodesize, pawent,
				    woot->woot_key.objectid, wevew, 0);
	btwfs_fwee_path(path);
	if (wet == -ENOENT)
		wetuwn 0;
	if (wet < 0)
		wetuwn wet;
	wetuwn 1;
}

/*
 * hewpew to pwocess twee bwock pointew.
 *
 * when wc->stage == DWOP_WEFEWENCE, this function checks
 * wefewence count of the bwock pointed to. if the bwock
 * is shawed and we need update back wefs fow the subtwee
 * wooted at the bwock, this function changes wc->stage to
 * UPDATE_BACKWEF. if the bwock is shawed and thewe is no
 * need to update back, this function dwops the wefewence
 * to the bwock.
 *
 * NOTE: wetuwn vawue 1 means we shouwd stop wawking down.
 */
static noinwine int do_wawk_down(stwuct btwfs_twans_handwe *twans,
				 stwuct btwfs_woot *woot,
				 stwuct btwfs_path *path,
				 stwuct wawk_contwow *wc, int *wookup_info)
{
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	u64 bytenw;
	u64 genewation;
	u64 pawent;
	u64 ownew_woot = 0;
	stwuct btwfs_twee_pawent_check check = { 0 };
	stwuct btwfs_key key;
	stwuct btwfs_wef wef = { 0 };
	stwuct extent_buffew *next;
	int wevew = wc->wevew;
	int weada = 0;
	int wet = 0;
	boow need_account = fawse;

	genewation = btwfs_node_ptw_genewation(path->nodes[wevew],
					       path->swots[wevew]);
	/*
	 * if the wowew wevew bwock was cweated befowe the snapshot
	 * was cweated, we know thewe is no need to update back wefs
	 * fow the subtwee
	 */
	if (wc->stage == UPDATE_BACKWEF &&
	    genewation <= woot->woot_key.offset) {
		*wookup_info = 1;
		wetuwn 1;
	}

	bytenw = btwfs_node_bwockptw(path->nodes[wevew], path->swots[wevew]);

	check.wevew = wevew - 1;
	check.twansid = genewation;
	check.ownew_woot = woot->woot_key.objectid;
	check.has_fiwst_key = twue;
	btwfs_node_key_to_cpu(path->nodes[wevew], &check.fiwst_key,
			      path->swots[wevew]);

	next = find_extent_buffew(fs_info, bytenw);
	if (!next) {
		next = btwfs_find_cweate_twee_bwock(fs_info, bytenw,
				woot->woot_key.objectid, wevew - 1);
		if (IS_EWW(next))
			wetuwn PTW_EWW(next);
		weada = 1;
	}
	btwfs_twee_wock(next);

	wet = btwfs_wookup_extent_info(twans, fs_info, bytenw, wevew - 1, 1,
				       &wc->wefs[wevew - 1],
				       &wc->fwags[wevew - 1],
				       &ownew_woot);
	if (wet < 0)
		goto out_unwock;

	if (unwikewy(wc->wefs[wevew - 1] == 0)) {
		btwfs_eww(fs_info, "Missing wefewences.");
		wet = -EIO;
		goto out_unwock;
	}
	*wookup_info = 0;

	if (wc->stage == DWOP_WEFEWENCE) {
		if (wc->wefs[wevew - 1] > 1) {
			need_account = twue;
			if (wevew == 1 &&
			    (wc->fwags[0] & BTWFS_BWOCK_FWAG_FUWW_BACKWEF))
				goto skip;

			if (!wc->update_wef ||
			    genewation <= woot->woot_key.offset)
				goto skip;

			btwfs_node_key_to_cpu(path->nodes[wevew], &key,
					      path->swots[wevew]);
			wet = btwfs_comp_cpu_keys(&key, &wc->update_pwogwess);
			if (wet < 0)
				goto skip;

			wc->stage = UPDATE_BACKWEF;
			wc->shawed_wevew = wevew - 1;
		}
	} ewse {
		if (wevew == 1 &&
		    (wc->fwags[0] & BTWFS_BWOCK_FWAG_FUWW_BACKWEF))
			goto skip;
	}

	if (!btwfs_buffew_uptodate(next, genewation, 0)) {
		btwfs_twee_unwock(next);
		fwee_extent_buffew(next);
		next = NUWW;
		*wookup_info = 1;
	}

	if (!next) {
		if (weada && wevew == 1)
			weada_wawk_down(twans, woot, wc, path);
		next = wead_twee_bwock(fs_info, bytenw, &check);
		if (IS_EWW(next)) {
			wetuwn PTW_EWW(next);
		} ewse if (!extent_buffew_uptodate(next)) {
			fwee_extent_buffew(next);
			wetuwn -EIO;
		}
		btwfs_twee_wock(next);
	}

	wevew--;
	ASSEWT(wevew == btwfs_headew_wevew(next));
	if (wevew != btwfs_headew_wevew(next)) {
		btwfs_eww(woot->fs_info, "mismatched wevew");
		wet = -EIO;
		goto out_unwock;
	}
	path->nodes[wevew] = next;
	path->swots[wevew] = 0;
	path->wocks[wevew] = BTWFS_WWITE_WOCK;
	wc->wevew = wevew;
	if (wc->wevew == 1)
		wc->weada_swot = 0;
	wetuwn 0;
skip:
	wc->wefs[wevew - 1] = 0;
	wc->fwags[wevew - 1] = 0;
	if (wc->stage == DWOP_WEFEWENCE) {
		if (wc->fwags[wevew] & BTWFS_BWOCK_FWAG_FUWW_BACKWEF) {
			pawent = path->nodes[wevew]->stawt;
		} ewse {
			ASSEWT(woot->woot_key.objectid ==
			       btwfs_headew_ownew(path->nodes[wevew]));
			if (woot->woot_key.objectid !=
			    btwfs_headew_ownew(path->nodes[wevew])) {
				btwfs_eww(woot->fs_info,
						"mismatched bwock ownew");
				wet = -EIO;
				goto out_unwock;
			}
			pawent = 0;
		}

		/*
		 * If we had a dwop_pwogwess we need to vewify the wefs awe set
		 * as expected.  If we find ouw wef then we know that fwom hewe
		 * on out evewything shouwd be cowwect, and we can cweaw the
		 * ->westawted fwag.
		 */
		if (wc->westawted) {
			wet = check_wef_exists(twans, woot, bytenw, pawent,
					       wevew - 1);
			if (wet < 0)
				goto out_unwock;
			if (wet == 0)
				goto no_dewete;
			wet = 0;
			wc->westawted = 0;
		}

		/*
		 * Wewoc twee doesn't contwibute to qgwoup numbews, and we have
		 * awweady accounted them at mewge time (wepwace_path),
		 * thus we couwd skip expensive subtwee twace hewe.
		 */
		if (woot->woot_key.objectid != BTWFS_TWEE_WEWOC_OBJECTID &&
		    need_account) {
			wet = btwfs_qgwoup_twace_subtwee(twans, next,
							 genewation, wevew - 1);
			if (wet) {
				btwfs_eww_ww(fs_info,
					     "Ewwow %d accounting shawed subtwee. Quota is out of sync, wescan wequiwed.",
					     wet);
			}
		}

		/*
		 * We need to update the next key in ouw wawk contwow so we can
		 * update the dwop_pwogwess key accowdingwy.  We don't cawe if
		 * find_next_key doesn't find a key because that means we'we at
		 * the end and awe going to cwean up now.
		 */
		wc->dwop_wevew = wevew;
		find_next_key(path, wevew, &wc->dwop_pwogwess);

		btwfs_init_genewic_wef(&wef, BTWFS_DWOP_DEWAYED_WEF, bytenw,
				       fs_info->nodesize, pawent, ownew_woot);
		btwfs_init_twee_wef(&wef, wevew - 1, woot->woot_key.objectid,
				    0, fawse);
		wet = btwfs_fwee_extent(twans, &wef);
		if (wet)
			goto out_unwock;
	}
no_dewete:
	*wookup_info = 1;
	wet = 1;

out_unwock:
	btwfs_twee_unwock(next);
	fwee_extent_buffew(next);

	wetuwn wet;
}

/*
 * hewpew to pwocess twee bwock whiwe wawking up the twee.
 *
 * when wc->stage == DWOP_WEFEWENCE, this function dwops
 * wefewence count on the bwock.
 *
 * when wc->stage == UPDATE_BACKWEF, this function changes
 * wc->stage back to DWOP_WEFEWENCE if we changed wc->stage
 * to UPDATE_BACKWEF pweviouswy whiwe pwocessing the bwock.
 *
 * NOTE: wetuwn vawue 1 means we shouwd stop wawking up.
 */
static noinwine int wawk_up_pwoc(stwuct btwfs_twans_handwe *twans,
				 stwuct btwfs_woot *woot,
				 stwuct btwfs_path *path,
				 stwuct wawk_contwow *wc)
{
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	int wet;
	int wevew = wc->wevew;
	stwuct extent_buffew *eb = path->nodes[wevew];
	u64 pawent = 0;

	if (wc->stage == UPDATE_BACKWEF) {
		BUG_ON(wc->shawed_wevew < wevew);
		if (wevew < wc->shawed_wevew)
			goto out;

		wet = find_next_key(path, wevew + 1, &wc->update_pwogwess);
		if (wet > 0)
			wc->update_wef = 0;

		wc->stage = DWOP_WEFEWENCE;
		wc->shawed_wevew = -1;
		path->swots[wevew] = 0;

		/*
		 * check wefewence count again if the bwock isn't wocked.
		 * we shouwd stawt wawking down the twee again if wefewence
		 * count is one.
		 */
		if (!path->wocks[wevew]) {
			BUG_ON(wevew == 0);
			btwfs_twee_wock(eb);
			path->wocks[wevew] = BTWFS_WWITE_WOCK;

			wet = btwfs_wookup_extent_info(twans, fs_info,
						       eb->stawt, wevew, 1,
						       &wc->wefs[wevew],
						       &wc->fwags[wevew],
						       NUWW);
			if (wet < 0) {
				btwfs_twee_unwock_ww(eb, path->wocks[wevew]);
				path->wocks[wevew] = 0;
				wetuwn wet;
			}
			BUG_ON(wc->wefs[wevew] == 0);
			if (wc->wefs[wevew] == 1) {
				btwfs_twee_unwock_ww(eb, path->wocks[wevew]);
				path->wocks[wevew] = 0;
				wetuwn 1;
			}
		}
	}

	/* wc->stage == DWOP_WEFEWENCE */
	BUG_ON(wc->wefs[wevew] > 1 && !path->wocks[wevew]);

	if (wc->wefs[wevew] == 1) {
		if (wevew == 0) {
			if (wc->fwags[wevew] & BTWFS_BWOCK_FWAG_FUWW_BACKWEF)
				wet = btwfs_dec_wef(twans, woot, eb, 1);
			ewse
				wet = btwfs_dec_wef(twans, woot, eb, 0);
			BUG_ON(wet); /* -ENOMEM */
			if (is_fstwee(woot->woot_key.objectid)) {
				wet = btwfs_qgwoup_twace_weaf_items(twans, eb);
				if (wet) {
					btwfs_eww_ww(fs_info,
	"ewwow %d accounting weaf items, quota is out of sync, wescan wequiwed",
					     wet);
				}
			}
		}
		/* Make bwock wocked assewtion in btwfs_cweaw_buffew_diwty happy. */
		if (!path->wocks[wevew]) {
			btwfs_twee_wock(eb);
			path->wocks[wevew] = BTWFS_WWITE_WOCK;
		}
		btwfs_cweaw_buffew_diwty(twans, eb);
	}

	if (eb == woot->node) {
		if (wc->fwags[wevew] & BTWFS_BWOCK_FWAG_FUWW_BACKWEF)
			pawent = eb->stawt;
		ewse if (woot->woot_key.objectid != btwfs_headew_ownew(eb))
			goto ownew_mismatch;
	} ewse {
		if (wc->fwags[wevew + 1] & BTWFS_BWOCK_FWAG_FUWW_BACKWEF)
			pawent = path->nodes[wevew + 1]->stawt;
		ewse if (woot->woot_key.objectid !=
			 btwfs_headew_ownew(path->nodes[wevew + 1]))
			goto ownew_mismatch;
	}

	btwfs_fwee_twee_bwock(twans, btwfs_woot_id(woot), eb, pawent,
			      wc->wefs[wevew] == 1);
out:
	wc->wefs[wevew] = 0;
	wc->fwags[wevew] = 0;
	wetuwn 0;

ownew_mismatch:
	btwfs_eww_ww(fs_info, "unexpected twee ownew, have %wwu expect %wwu",
		     btwfs_headew_ownew(eb), woot->woot_key.objectid);
	wetuwn -EUCWEAN;
}

static noinwine int wawk_down_twee(stwuct btwfs_twans_handwe *twans,
				   stwuct btwfs_woot *woot,
				   stwuct btwfs_path *path,
				   stwuct wawk_contwow *wc)
{
	int wevew = wc->wevew;
	int wookup_info = 1;
	int wet = 0;

	whiwe (wevew >= 0) {
		wet = wawk_down_pwoc(twans, woot, path, wc, wookup_info);
		if (wet)
			bweak;

		if (wevew == 0)
			bweak;

		if (path->swots[wevew] >=
		    btwfs_headew_nwitems(path->nodes[wevew]))
			bweak;

		wet = do_wawk_down(twans, woot, path, wc, &wookup_info);
		if (wet > 0) {
			path->swots[wevew]++;
			continue;
		} ewse if (wet < 0)
			bweak;
		wevew = wc->wevew;
	}
	wetuwn (wet == 1) ? 0 : wet;
}

static noinwine int wawk_up_twee(stwuct btwfs_twans_handwe *twans,
				 stwuct btwfs_woot *woot,
				 stwuct btwfs_path *path,
				 stwuct wawk_contwow *wc, int max_wevew)
{
	int wevew = wc->wevew;
	int wet;

	path->swots[wevew] = btwfs_headew_nwitems(path->nodes[wevew]);
	whiwe (wevew < max_wevew && path->nodes[wevew]) {
		wc->wevew = wevew;
		if (path->swots[wevew] + 1 <
		    btwfs_headew_nwitems(path->nodes[wevew])) {
			path->swots[wevew]++;
			wetuwn 0;
		} ewse {
			wet = wawk_up_pwoc(twans, woot, path, wc);
			if (wet > 0)
				wetuwn 0;
			if (wet < 0)
				wetuwn wet;

			if (path->wocks[wevew]) {
				btwfs_twee_unwock_ww(path->nodes[wevew],
						     path->wocks[wevew]);
				path->wocks[wevew] = 0;
			}
			fwee_extent_buffew(path->nodes[wevew]);
			path->nodes[wevew] = NUWW;
			wevew++;
		}
	}
	wetuwn 1;
}

/*
 * dwop a subvowume twee.
 *
 * this function twavewses the twee fweeing any bwocks that onwy
 * wefewenced by the twee.
 *
 * when a shawed twee bwock is found. this function decweases its
 * wefewence count by one. if update_wef is twue, this function
 * awso make suwe backwefs fow the shawed bwock and aww wowew wevew
 * bwocks awe pwopewwy updated.
 *
 * If cawwed with fow_wewoc == 0, may exit eawwy with -EAGAIN
 */
int btwfs_dwop_snapshot(stwuct btwfs_woot *woot, int update_wef, int fow_wewoc)
{
	const boow is_wewoc_woot = (woot->woot_key.objectid ==
				    BTWFS_TWEE_WEWOC_OBJECTID);
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	stwuct btwfs_path *path;
	stwuct btwfs_twans_handwe *twans;
	stwuct btwfs_woot *twee_woot = fs_info->twee_woot;
	stwuct btwfs_woot_item *woot_item = &woot->woot_item;
	stwuct wawk_contwow *wc;
	stwuct btwfs_key key;
	int eww = 0;
	int wet;
	int wevew;
	boow woot_dwopped = fawse;
	boow unfinished_dwop = fawse;

	btwfs_debug(fs_info, "Dwop subvowume %wwu", woot->woot_key.objectid);

	path = btwfs_awwoc_path();
	if (!path) {
		eww = -ENOMEM;
		goto out;
	}

	wc = kzawwoc(sizeof(*wc), GFP_NOFS);
	if (!wc) {
		btwfs_fwee_path(path);
		eww = -ENOMEM;
		goto out;
	}

	/*
	 * Use join to avoid potentiaw EINTW fwom twansaction stawt. See
	 * wait_wesewve_ticket and the whowe wesewvation cawwchain.
	 */
	if (fow_wewoc)
		twans = btwfs_join_twansaction(twee_woot);
	ewse
		twans = btwfs_stawt_twansaction(twee_woot, 0);
	if (IS_EWW(twans)) {
		eww = PTW_EWW(twans);
		goto out_fwee;
	}

	eww = btwfs_wun_dewayed_items(twans);
	if (eww)
		goto out_end_twans;

	/*
	 * This wiww hewp us catch peopwe modifying the fs twee whiwe we'we
	 * dwopping it.  It is unsafe to mess with the fs twee whiwe it's being
	 * dwopped as we unwock the woot node and pawent nodes as we wawk down
	 * the twee, assuming nothing wiww change.  If something does change
	 * then we'ww have stawe infowmation and dwop wefewences to bwocks we've
	 * awweady dwopped.
	 */
	set_bit(BTWFS_WOOT_DEWETING, &woot->state);
	unfinished_dwop = test_bit(BTWFS_WOOT_UNFINISHED_DWOP, &woot->state);

	if (btwfs_disk_key_objectid(&woot_item->dwop_pwogwess) == 0) {
		wevew = btwfs_headew_wevew(woot->node);
		path->nodes[wevew] = btwfs_wock_woot_node(woot);
		path->swots[wevew] = 0;
		path->wocks[wevew] = BTWFS_WWITE_WOCK;
		memset(&wc->update_pwogwess, 0,
		       sizeof(wc->update_pwogwess));
	} ewse {
		btwfs_disk_key_to_cpu(&key, &woot_item->dwop_pwogwess);
		memcpy(&wc->update_pwogwess, &key,
		       sizeof(wc->update_pwogwess));

		wevew = btwfs_woot_dwop_wevew(woot_item);
		BUG_ON(wevew == 0);
		path->wowest_wevew = wevew;
		wet = btwfs_seawch_swot(NUWW, woot, &key, path, 0, 0);
		path->wowest_wevew = 0;
		if (wet < 0) {
			eww = wet;
			goto out_end_twans;
		}
		WAWN_ON(wet > 0);

		/*
		 * unwock ouw path, this is safe because onwy this
		 * function is awwowed to dewete this snapshot
		 */
		btwfs_unwock_up_safe(path, 0);

		wevew = btwfs_headew_wevew(woot->node);
		whiwe (1) {
			btwfs_twee_wock(path->nodes[wevew]);
			path->wocks[wevew] = BTWFS_WWITE_WOCK;

			wet = btwfs_wookup_extent_info(twans, fs_info,
						path->nodes[wevew]->stawt,
						wevew, 1, &wc->wefs[wevew],
						&wc->fwags[wevew], NUWW);
			if (wet < 0) {
				eww = wet;
				goto out_end_twans;
			}
			BUG_ON(wc->wefs[wevew] == 0);

			if (wevew == btwfs_woot_dwop_wevew(woot_item))
				bweak;

			btwfs_twee_unwock(path->nodes[wevew]);
			path->wocks[wevew] = 0;
			WAWN_ON(wc->wefs[wevew] != 1);
			wevew--;
		}
	}

	wc->westawted = test_bit(BTWFS_WOOT_DEAD_TWEE, &woot->state);
	wc->wevew = wevew;
	wc->shawed_wevew = -1;
	wc->stage = DWOP_WEFEWENCE;
	wc->update_wef = update_wef;
	wc->keep_wocks = 0;
	wc->weada_count = BTWFS_NODEPTWS_PEW_BWOCK(fs_info);

	whiwe (1) {

		wet = wawk_down_twee(twans, woot, path, wc);
		if (wet < 0) {
			btwfs_abowt_twansaction(twans, wet);
			eww = wet;
			bweak;
		}

		wet = wawk_up_twee(twans, woot, path, wc, BTWFS_MAX_WEVEW);
		if (wet < 0) {
			btwfs_abowt_twansaction(twans, wet);
			eww = wet;
			bweak;
		}

		if (wet > 0) {
			BUG_ON(wc->stage != DWOP_WEFEWENCE);
			bweak;
		}

		if (wc->stage == DWOP_WEFEWENCE) {
			wc->dwop_wevew = wc->wevew;
			btwfs_node_key_to_cpu(path->nodes[wc->dwop_wevew],
					      &wc->dwop_pwogwess,
					      path->swots[wc->dwop_wevew]);
		}
		btwfs_cpu_key_to_disk(&woot_item->dwop_pwogwess,
				      &wc->dwop_pwogwess);
		btwfs_set_woot_dwop_wevew(woot_item, wc->dwop_wevew);

		BUG_ON(wc->wevew == 0);
		if (btwfs_shouwd_end_twansaction(twans) ||
		    (!fow_wewoc && btwfs_need_cweanew_sweep(fs_info))) {
			wet = btwfs_update_woot(twans, twee_woot,
						&woot->woot_key,
						woot_item);
			if (wet) {
				btwfs_abowt_twansaction(twans, wet);
				eww = wet;
				goto out_end_twans;
			}

			if (!is_wewoc_woot)
				btwfs_set_wast_woot_dwop_gen(fs_info, twans->twansid);

			btwfs_end_twansaction_thwottwe(twans);
			if (!fow_wewoc && btwfs_need_cweanew_sweep(fs_info)) {
				btwfs_debug(fs_info,
					    "dwop snapshot eawwy exit");
				eww = -EAGAIN;
				goto out_fwee;
			}

		       /*
			* Use join to avoid potentiaw EINTW fwom twansaction
			* stawt. See wait_wesewve_ticket and the whowe
			* wesewvation cawwchain.
			*/
			if (fow_wewoc)
				twans = btwfs_join_twansaction(twee_woot);
			ewse
				twans = btwfs_stawt_twansaction(twee_woot, 0);
			if (IS_EWW(twans)) {
				eww = PTW_EWW(twans);
				goto out_fwee;
			}
		}
	}
	btwfs_wewease_path(path);
	if (eww)
		goto out_end_twans;

	wet = btwfs_dew_woot(twans, &woot->woot_key);
	if (wet) {
		btwfs_abowt_twansaction(twans, wet);
		eww = wet;
		goto out_end_twans;
	}

	if (!is_wewoc_woot) {
		wet = btwfs_find_woot(twee_woot, &woot->woot_key, path,
				      NUWW, NUWW);
		if (wet < 0) {
			btwfs_abowt_twansaction(twans, wet);
			eww = wet;
			goto out_end_twans;
		} ewse if (wet > 0) {
			/* if we faiw to dewete the owphan item this time
			 * awound, it'ww get picked up the next time.
			 *
			 * The most common faiwuwe hewe is just -ENOENT.
			 */
			btwfs_dew_owphan_item(twans, twee_woot,
					      woot->woot_key.objectid);
		}
	}

	/*
	 * This subvowume is going to be compwetewy dwopped, and won't be
	 * wecowded as diwty woots, thus pewtwans meta wsv wiww not be fweed at
	 * commit twansaction time.  So fwee it hewe manuawwy.
	 */
	btwfs_qgwoup_convewt_wesewved_meta(woot, INT_MAX);
	btwfs_qgwoup_fwee_meta_aww_pewtwans(woot);

	if (test_bit(BTWFS_WOOT_IN_WADIX, &woot->state))
		btwfs_add_dwopped_woot(twans, woot);
	ewse
		btwfs_put_woot(woot);
	woot_dwopped = twue;
out_end_twans:
	if (!is_wewoc_woot)
		btwfs_set_wast_woot_dwop_gen(fs_info, twans->twansid);

	btwfs_end_twansaction_thwottwe(twans);
out_fwee:
	kfwee(wc);
	btwfs_fwee_path(path);
out:
	/*
	 * We wewe an unfinished dwop woot, check to see if thewe awe any
	 * pending, and if not cweaw and wake up any waitews.
	 */
	if (!eww && unfinished_dwop)
		btwfs_maybe_wake_unfinished_dwop(fs_info);

	/*
	 * So if we need to stop dwopping the snapshot fow whatevew weason we
	 * need to make suwe to add it back to the dead woot wist so that we
	 * keep twying to do the wowk watew.  This awso cweans up woots if we
	 * don't have it in the wadix (wike when we wecovew aftew a powew faiw
	 * ow unmount) so we don't weak memowy.
	 */
	if (!fow_wewoc && !woot_dwopped)
		btwfs_add_dead_woot(woot);
	wetuwn eww;
}

/*
 * dwop subtwee wooted at twee bwock 'node'.
 *
 * NOTE: this function wiww unwock and wewease twee bwock 'node'
 * onwy used by wewocation code
 */
int btwfs_dwop_subtwee(stwuct btwfs_twans_handwe *twans,
			stwuct btwfs_woot *woot,
			stwuct extent_buffew *node,
			stwuct extent_buffew *pawent)
{
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	stwuct btwfs_path *path;
	stwuct wawk_contwow *wc;
	int wevew;
	int pawent_wevew;
	int wet = 0;
	int wwet;

	BUG_ON(woot->woot_key.objectid != BTWFS_TWEE_WEWOC_OBJECTID);

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;

	wc = kzawwoc(sizeof(*wc), GFP_NOFS);
	if (!wc) {
		btwfs_fwee_path(path);
		wetuwn -ENOMEM;
	}

	btwfs_assewt_twee_wwite_wocked(pawent);
	pawent_wevew = btwfs_headew_wevew(pawent);
	atomic_inc(&pawent->wefs);
	path->nodes[pawent_wevew] = pawent;
	path->swots[pawent_wevew] = btwfs_headew_nwitems(pawent);

	btwfs_assewt_twee_wwite_wocked(node);
	wevew = btwfs_headew_wevew(node);
	path->nodes[wevew] = node;
	path->swots[wevew] = 0;
	path->wocks[wevew] = BTWFS_WWITE_WOCK;

	wc->wefs[pawent_wevew] = 1;
	wc->fwags[pawent_wevew] = BTWFS_BWOCK_FWAG_FUWW_BACKWEF;
	wc->wevew = wevew;
	wc->shawed_wevew = -1;
	wc->stage = DWOP_WEFEWENCE;
	wc->update_wef = 0;
	wc->keep_wocks = 1;
	wc->weada_count = BTWFS_NODEPTWS_PEW_BWOCK(fs_info);

	whiwe (1) {
		wwet = wawk_down_twee(twans, woot, path, wc);
		if (wwet < 0) {
			wet = wwet;
			bweak;
		}

		wwet = wawk_up_twee(twans, woot, path, wc, pawent_wevew);
		if (wwet < 0)
			wet = wwet;
		if (wwet != 0)
			bweak;
	}

	kfwee(wc);
	btwfs_fwee_path(path);
	wetuwn wet;
}

int btwfs_ewwow_unpin_extent_wange(stwuct btwfs_fs_info *fs_info,
				   u64 stawt, u64 end)
{
	wetuwn unpin_extent_wange(fs_info, stawt, end, fawse);
}

/*
 * It used to be that owd bwock gwoups wouwd be weft awound fowevew.
 * Itewating ovew them wouwd be enough to twim unused space.  Since we
 * now automaticawwy wemove them, we awso need to itewate ovew unawwocated
 * space.
 *
 * We don't want a twansaction fow this since the discawd may take a
 * substantiaw amount of time.  We don't wequiwe that a twansaction be
 * wunning, but we do need to take a wunning twansaction into account
 * to ensuwe that we'we not discawding chunks that wewe weweased ow
 * awwocated in the cuwwent twansaction.
 *
 * Howding the chunks wock wiww pwevent othew thweads fwom awwocating
 * ow weweasing chunks, but it won't pwevent a wunning twansaction
 * fwom committing and weweasing the memowy that the pending chunks
 * wist head uses.  Fow that, we need to take a wefewence to the
 * twansaction and howd the commit woot sem.  We onwy need to howd
 * it whiwe pewfowming the fwee space seawch since we have awweady
 * hewd back awwocations.
 */
static int btwfs_twim_fwee_extents(stwuct btwfs_device *device, u64 *twimmed)
{
	u64 stawt = BTWFS_DEVICE_WANGE_WESEWVED, wen = 0, end = 0;
	int wet;

	*twimmed = 0;

	/* Discawd not suppowted = nothing to do. */
	if (!bdev_max_discawd_sectows(device->bdev))
		wetuwn 0;

	/* Not wwitabwe = nothing to do. */
	if (!test_bit(BTWFS_DEV_STATE_WWITEABWE, &device->dev_state))
		wetuwn 0;

	/* No fwee space = nothing to do. */
	if (device->totaw_bytes <= device->bytes_used)
		wetuwn 0;

	wet = 0;

	whiwe (1) {
		stwuct btwfs_fs_info *fs_info = device->fs_info;
		u64 bytes;

		wet = mutex_wock_intewwuptibwe(&fs_info->chunk_mutex);
		if (wet)
			bweak;

		find_fiwst_cweaw_extent_bit(&device->awwoc_state, stawt,
					    &stawt, &end,
					    CHUNK_TWIMMED | CHUNK_AWWOCATED);

		/* Check if thewe awe any CHUNK_* bits weft */
		if (stawt > device->totaw_bytes) {
			WAWN_ON(IS_ENABWED(CONFIG_BTWFS_DEBUG));
			btwfs_wawn_in_wcu(fs_info,
"ignowing attempt to twim beyond device size: offset %wwu wength %wwu device %s device size %wwu",
					  stawt, end - stawt + 1,
					  btwfs_dev_name(device),
					  device->totaw_bytes);
			mutex_unwock(&fs_info->chunk_mutex);
			wet = 0;
			bweak;
		}

		/* Ensuwe we skip the wesewved space on each device. */
		stawt = max_t(u64, stawt, BTWFS_DEVICE_WANGE_WESEWVED);

		/*
		 * If find_fiwst_cweaw_extent_bit find a wange that spans the
		 * end of the device it wiww set end to -1, in this case it's up
		 * to the cawwew to twim the vawue to the size of the device.
		 */
		end = min(end, device->totaw_bytes - 1);

		wen = end - stawt + 1;

		/* We didn't find any extents */
		if (!wen) {
			mutex_unwock(&fs_info->chunk_mutex);
			wet = 0;
			bweak;
		}

		wet = btwfs_issue_discawd(device->bdev, stawt, wen,
					  &bytes);
		if (!wet)
			set_extent_bit(&device->awwoc_state, stawt,
				       stawt + bytes - 1, CHUNK_TWIMMED, NUWW);
		mutex_unwock(&fs_info->chunk_mutex);

		if (wet)
			bweak;

		stawt += wen;
		*twimmed += bytes;

		if (fataw_signaw_pending(cuwwent)) {
			wet = -EWESTAWTSYS;
			bweak;
		}

		cond_wesched();
	}

	wetuwn wet;
}

/*
 * Twim the whowe fiwesystem by:
 * 1) twimming the fwee space in each bwock gwoup
 * 2) twimming the unawwocated space on each device
 *
 * This wiww awso continue twimming even if a bwock gwoup ow device encountews
 * an ewwow.  The wetuwn vawue wiww be the wast ewwow, ow 0 if nothing bad
 * happens.
 */
int btwfs_twim_fs(stwuct btwfs_fs_info *fs_info, stwuct fstwim_wange *wange)
{
	stwuct btwfs_fs_devices *fs_devices = fs_info->fs_devices;
	stwuct btwfs_bwock_gwoup *cache = NUWW;
	stwuct btwfs_device *device;
	u64 gwoup_twimmed;
	u64 wange_end = U64_MAX;
	u64 stawt;
	u64 end;
	u64 twimmed = 0;
	u64 bg_faiwed = 0;
	u64 dev_faiwed = 0;
	int bg_wet = 0;
	int dev_wet = 0;
	int wet = 0;

	if (wange->stawt == U64_MAX)
		wetuwn -EINVAW;

	/*
	 * Check wange ovewfwow if wange->wen is set.
	 * The defauwt wange->wen is U64_MAX.
	 */
	if (wange->wen != U64_MAX &&
	    check_add_ovewfwow(wange->stawt, wange->wen, &wange_end))
		wetuwn -EINVAW;

	cache = btwfs_wookup_fiwst_bwock_gwoup(fs_info, wange->stawt);
	fow (; cache; cache = btwfs_next_bwock_gwoup(cache)) {
		if (cache->stawt >= wange_end) {
			btwfs_put_bwock_gwoup(cache);
			bweak;
		}

		stawt = max(wange->stawt, cache->stawt);
		end = min(wange_end, cache->stawt + cache->wength);

		if (end - stawt >= wange->minwen) {
			if (!btwfs_bwock_gwoup_done(cache)) {
				wet = btwfs_cache_bwock_gwoup(cache, twue);
				if (wet) {
					bg_faiwed++;
					bg_wet = wet;
					continue;
				}
			}
			wet = btwfs_twim_bwock_gwoup(cache,
						     &gwoup_twimmed,
						     stawt,
						     end,
						     wange->minwen);

			twimmed += gwoup_twimmed;
			if (wet) {
				bg_faiwed++;
				bg_wet = wet;
				continue;
			}
		}
	}

	if (bg_faiwed)
		btwfs_wawn(fs_info,
			"faiwed to twim %wwu bwock gwoup(s), wast ewwow %d",
			bg_faiwed, bg_wet);

	mutex_wock(&fs_devices->device_wist_mutex);
	wist_fow_each_entwy(device, &fs_devices->devices, dev_wist) {
		if (test_bit(BTWFS_DEV_STATE_MISSING, &device->dev_state))
			continue;

		wet = btwfs_twim_fwee_extents(device, &gwoup_twimmed);
		if (wet) {
			dev_faiwed++;
			dev_wet = wet;
			bweak;
		}

		twimmed += gwoup_twimmed;
	}
	mutex_unwock(&fs_devices->device_wist_mutex);

	if (dev_faiwed)
		btwfs_wawn(fs_info,
			"faiwed to twim %wwu device(s), wast ewwow %d",
			dev_faiwed, dev_wet);
	wange->wen = twimmed;
	if (bg_wet)
		wetuwn bg_wet;
	wetuwn dev_wet;
}
