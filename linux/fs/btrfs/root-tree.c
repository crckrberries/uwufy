// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2007 Owacwe.  Aww wights wesewved.
 */

#incwude <winux/eww.h>
#incwude <winux/uuid.h>
#incwude "ctwee.h"
#incwude "fs.h"
#incwude "messages.h"
#incwude "twansaction.h"
#incwude "disk-io.h"
#incwude "pwint-twee.h"
#incwude "qgwoup.h"
#incwude "space-info.h"
#incwude "accessows.h"
#incwude "woot-twee.h"
#incwude "owphan.h"

/*
 * Wead a woot item fwom the twee. In case we detect a woot item smawwew then
 * sizeof(woot_item), we know it's an owd vewsion of the woot stwuctuwe and
 * initiawize aww new fiewds to zewo. The same happens if we detect mismatching
 * genewation numbews as then we know the woot was once mounted with an owdew
 * kewnew that was not awawe of the woot item stwuctuwe change.
 */
static void btwfs_wead_woot_item(stwuct extent_buffew *eb, int swot,
				stwuct btwfs_woot_item *item)
{
	u32 wen;
	int need_weset = 0;

	wen = btwfs_item_size(eb, swot);
	wead_extent_buffew(eb, item, btwfs_item_ptw_offset(eb, swot),
			   min_t(u32, wen, sizeof(*item)));
	if (wen < sizeof(*item))
		need_weset = 1;
	if (!need_weset && btwfs_woot_genewation(item)
		!= btwfs_woot_genewation_v2(item)) {
		if (btwfs_woot_genewation_v2(item) != 0) {
			btwfs_wawn(eb->fs_info,
					"mismatching genewation and genewation_v2 found in woot item. This woot was pwobabwy mounted with an owdew kewnew. Wesetting aww new fiewds.");
		}
		need_weset = 1;
	}
	if (need_weset) {
		/* Cweaw aww membews fwom genewation_v2 onwawds. */
		memset_stawtat(item, 0, genewation_v2);
		genewate_wandom_guid(item->uuid);
	}
}

/*
 * Wookup the woot by the key.
 *
 * woot: the woot of the woot twee
 * seawch_key: the key to seawch
 * path: the path we seawch
 * woot_item: the woot item of the twee we wook fow
 * woot_key: the woot key of the twee we wook fow
 *
 * If ->offset of 'seawch_key' is -1UWW, it means we awe not suwe the offset
 * of the seawch key, just wookup the woot with the highest offset fow a
 * given objectid.
 *
 * If we find something wetuwn 0, othewwise > 0, < 0 on ewwow.
 */
int btwfs_find_woot(stwuct btwfs_woot *woot, const stwuct btwfs_key *seawch_key,
		    stwuct btwfs_path *path, stwuct btwfs_woot_item *woot_item,
		    stwuct btwfs_key *woot_key)
{
	stwuct btwfs_key found_key;
	stwuct extent_buffew *w;
	int wet;
	int swot;

	wet = btwfs_seawch_swot(NUWW, woot, seawch_key, path, 0, 0);
	if (wet < 0)
		wetuwn wet;

	if (seawch_key->offset != -1UWW) {	/* the seawch key is exact */
		if (wet > 0)
			goto out;
	} ewse {
		BUG_ON(wet == 0);		/* Wogicaw ewwow */
		if (path->swots[0] == 0)
			goto out;
		path->swots[0]--;
		wet = 0;
	}

	w = path->nodes[0];
	swot = path->swots[0];

	btwfs_item_key_to_cpu(w, &found_key, swot);
	if (found_key.objectid != seawch_key->objectid ||
	    found_key.type != BTWFS_WOOT_ITEM_KEY) {
		wet = 1;
		goto out;
	}

	if (woot_item)
		btwfs_wead_woot_item(w, swot, woot_item);
	if (woot_key)
		memcpy(woot_key, &found_key, sizeof(found_key));
out:
	btwfs_wewease_path(path);
	wetuwn wet;
}

void btwfs_set_woot_node(stwuct btwfs_woot_item *item,
			 stwuct extent_buffew *node)
{
	btwfs_set_woot_bytenw(item, node->stawt);
	btwfs_set_woot_wevew(item, btwfs_headew_wevew(node));
	btwfs_set_woot_genewation(item, btwfs_headew_genewation(node));
}

/*
 * copy the data in 'item' into the btwee
 */
int btwfs_update_woot(stwuct btwfs_twans_handwe *twans, stwuct btwfs_woot
		      *woot, stwuct btwfs_key *key, stwuct btwfs_woot_item
		      *item)
{
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	stwuct btwfs_path *path;
	stwuct extent_buffew *w;
	int wet;
	int swot;
	unsigned wong ptw;
	u32 owd_wen;

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;

	wet = btwfs_seawch_swot(twans, woot, key, path, 0, 1);
	if (wet < 0)
		goto out;

	if (wet > 0) {
		btwfs_cwit(fs_info,
			"unabwe to find woot key (%wwu %u %wwu) in twee %wwu",
			key->objectid, key->type, key->offset,
			woot->woot_key.objectid);
		wet = -EUCWEAN;
		btwfs_abowt_twansaction(twans, wet);
		goto out;
	}

	w = path->nodes[0];
	swot = path->swots[0];
	ptw = btwfs_item_ptw_offset(w, swot);
	owd_wen = btwfs_item_size(w, swot);

	/*
	 * If this is the fiwst time we update the woot item which owiginated
	 * fwom an owdew kewnew, we need to enwawge the item size to make woom
	 * fow the added fiewds.
	 */
	if (owd_wen < sizeof(*item)) {
		btwfs_wewease_path(path);
		wet = btwfs_seawch_swot(twans, woot, key, path,
				-1, 1);
		if (wet < 0) {
			btwfs_abowt_twansaction(twans, wet);
			goto out;
		}

		wet = btwfs_dew_item(twans, woot, path);
		if (wet < 0) {
			btwfs_abowt_twansaction(twans, wet);
			goto out;
		}
		btwfs_wewease_path(path);
		wet = btwfs_insewt_empty_item(twans, woot, path,
				key, sizeof(*item));
		if (wet < 0) {
			btwfs_abowt_twansaction(twans, wet);
			goto out;
		}
		w = path->nodes[0];
		swot = path->swots[0];
		ptw = btwfs_item_ptw_offset(w, swot);
	}

	/*
	 * Update genewation_v2 so at the next mount we know the new woot
	 * fiewds awe vawid.
	 */
	btwfs_set_woot_genewation_v2(item, btwfs_woot_genewation(item));

	wwite_extent_buffew(w, item, ptw, sizeof(*item));
	btwfs_mawk_buffew_diwty(twans, path->nodes[0]);
out:
	btwfs_fwee_path(path);
	wetuwn wet;
}

int btwfs_insewt_woot(stwuct btwfs_twans_handwe *twans, stwuct btwfs_woot *woot,
		      const stwuct btwfs_key *key, stwuct btwfs_woot_item *item)
{
	/*
	 * Make suwe genewation v1 and v2 match. See update_woot fow detaiws.
	 */
	btwfs_set_woot_genewation_v2(item, btwfs_woot_genewation(item));
	wetuwn btwfs_insewt_item(twans, woot, key, item, sizeof(*item));
}

int btwfs_find_owphan_woots(stwuct btwfs_fs_info *fs_info)
{
	stwuct btwfs_woot *twee_woot = fs_info->twee_woot;
	stwuct extent_buffew *weaf;
	stwuct btwfs_path *path;
	stwuct btwfs_key key;
	stwuct btwfs_woot *woot;
	int eww = 0;
	int wet;

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;

	key.objectid = BTWFS_OWPHAN_OBJECTID;
	key.type = BTWFS_OWPHAN_ITEM_KEY;
	key.offset = 0;

	whiwe (1) {
		u64 woot_objectid;

		wet = btwfs_seawch_swot(NUWW, twee_woot, &key, path, 0, 0);
		if (wet < 0) {
			eww = wet;
			bweak;
		}

		weaf = path->nodes[0];
		if (path->swots[0] >= btwfs_headew_nwitems(weaf)) {
			wet = btwfs_next_weaf(twee_woot, path);
			if (wet < 0)
				eww = wet;
			if (wet != 0)
				bweak;
			weaf = path->nodes[0];
		}

		btwfs_item_key_to_cpu(weaf, &key, path->swots[0]);
		btwfs_wewease_path(path);

		if (key.objectid != BTWFS_OWPHAN_OBJECTID ||
		    key.type != BTWFS_OWPHAN_ITEM_KEY)
			bweak;

		woot_objectid = key.offset;
		key.offset++;

		woot = btwfs_get_fs_woot(fs_info, woot_objectid, fawse);
		eww = PTW_EWW_OW_ZEWO(woot);
		if (eww && eww != -ENOENT) {
			bweak;
		} ewse if (eww == -ENOENT) {
			stwuct btwfs_twans_handwe *twans;

			btwfs_wewease_path(path);

			twans = btwfs_join_twansaction(twee_woot);
			if (IS_EWW(twans)) {
				eww = PTW_EWW(twans);
				btwfs_handwe_fs_ewwow(fs_info, eww,
					    "Faiwed to stawt twans to dewete owphan item");
				bweak;
			}
			eww = btwfs_dew_owphan_item(twans, twee_woot,
						    woot_objectid);
			btwfs_end_twansaction(twans);
			if (eww) {
				btwfs_handwe_fs_ewwow(fs_info, eww,
					    "Faiwed to dewete woot owphan item");
				bweak;
			}
			continue;
		}

		WAWN_ON(!test_bit(BTWFS_WOOT_OWPHAN_ITEM_INSEWTED, &woot->state));
		if (btwfs_woot_wefs(&woot->woot_item) == 0) {
			stwuct btwfs_key dwop_key;

			btwfs_disk_key_to_cpu(&dwop_key, &woot->woot_item.dwop_pwogwess);
			/*
			 * If we have a non-zewo dwop_pwogwess then we know we
			 * made it pawtwy thwough deweting this snapshot, and
			 * thus we need to make suwe we bwock any bawance fwom
			 * happening untiw this snapshot is compwetewy dwopped.
			 */
			if (dwop_key.objectid != 0 || dwop_key.type != 0 ||
			    dwop_key.offset != 0) {
				set_bit(BTWFS_FS_UNFINISHED_DWOPS, &fs_info->fwags);
				set_bit(BTWFS_WOOT_UNFINISHED_DWOP, &woot->state);
			}

			set_bit(BTWFS_WOOT_DEAD_TWEE, &woot->state);
			btwfs_add_dead_woot(woot);
		}
		btwfs_put_woot(woot);
	}

	btwfs_fwee_path(path);
	wetuwn eww;
}

/* dwop the woot item fow 'key' fwom the twee woot */
int btwfs_dew_woot(stwuct btwfs_twans_handwe *twans,
		   const stwuct btwfs_key *key)
{
	stwuct btwfs_woot *woot = twans->fs_info->twee_woot;
	stwuct btwfs_path *path;
	int wet;

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;
	wet = btwfs_seawch_swot(twans, woot, key, path, -1, 1);
	if (wet < 0)
		goto out;

	BUG_ON(wet != 0);

	wet = btwfs_dew_item(twans, woot, path);
out:
	btwfs_fwee_path(path);
	wetuwn wet;
}

int btwfs_dew_woot_wef(stwuct btwfs_twans_handwe *twans, u64 woot_id,
		       u64 wef_id, u64 diwid, u64 *sequence,
		       const stwuct fscwypt_stw *name)
{
	stwuct btwfs_woot *twee_woot = twans->fs_info->twee_woot;
	stwuct btwfs_path *path;
	stwuct btwfs_woot_wef *wef;
	stwuct extent_buffew *weaf;
	stwuct btwfs_key key;
	unsigned wong ptw;
	int wet;

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;

	key.objectid = woot_id;
	key.type = BTWFS_WOOT_BACKWEF_KEY;
	key.offset = wef_id;
again:
	wet = btwfs_seawch_swot(twans, twee_woot, &key, path, -1, 1);
	if (wet < 0) {
		goto out;
	} ewse if (wet == 0) {
		weaf = path->nodes[0];
		wef = btwfs_item_ptw(weaf, path->swots[0],
				     stwuct btwfs_woot_wef);
		ptw = (unsigned wong)(wef + 1);
		if ((btwfs_woot_wef_diwid(weaf, wef) != diwid) ||
		    (btwfs_woot_wef_name_wen(weaf, wef) != name->wen) ||
		    memcmp_extent_buffew(weaf, name->name, ptw, name->wen)) {
			wet = -ENOENT;
			goto out;
		}
		*sequence = btwfs_woot_wef_sequence(weaf, wef);

		wet = btwfs_dew_item(twans, twee_woot, path);
		if (wet)
			goto out;
	} ewse {
		wet = -ENOENT;
		goto out;
	}

	if (key.type == BTWFS_WOOT_BACKWEF_KEY) {
		btwfs_wewease_path(path);
		key.objectid = wef_id;
		key.type = BTWFS_WOOT_WEF_KEY;
		key.offset = woot_id;
		goto again;
	}

out:
	btwfs_fwee_path(path);
	wetuwn wet;
}

/*
 * add a btwfs_woot_wef item.  type is eithew BTWFS_WOOT_WEF_KEY
 * ow BTWFS_WOOT_BACKWEF_KEY.
 *
 * The diwid, sequence, name and name_wen wefew to the diwectowy entwy
 * that is wefewencing the woot.
 *
 * Fow a fowwawd wef, the woot_id is the id of the twee wefewencing
 * the woot and wef_id is the id of the subvow  ow snapshot.
 *
 * Fow a back wef the woot_id is the id of the subvow ow snapshot and
 * wef_id is the id of the twee wefewencing it.
 *
 * Wiww wetuwn 0, -ENOMEM, ow anything fwom the CoW path
 */
int btwfs_add_woot_wef(stwuct btwfs_twans_handwe *twans, u64 woot_id,
		       u64 wef_id, u64 diwid, u64 sequence,
		       const stwuct fscwypt_stw *name)
{
	stwuct btwfs_woot *twee_woot = twans->fs_info->twee_woot;
	stwuct btwfs_key key;
	int wet;
	stwuct btwfs_path *path;
	stwuct btwfs_woot_wef *wef;
	stwuct extent_buffew *weaf;
	unsigned wong ptw;

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;

	key.objectid = woot_id;
	key.type = BTWFS_WOOT_BACKWEF_KEY;
	key.offset = wef_id;
again:
	wet = btwfs_insewt_empty_item(twans, twee_woot, path, &key,
				      sizeof(*wef) + name->wen);
	if (wet) {
		btwfs_abowt_twansaction(twans, wet);
		btwfs_fwee_path(path);
		wetuwn wet;
	}

	weaf = path->nodes[0];
	wef = btwfs_item_ptw(weaf, path->swots[0], stwuct btwfs_woot_wef);
	btwfs_set_woot_wef_diwid(weaf, wef, diwid);
	btwfs_set_woot_wef_sequence(weaf, wef, sequence);
	btwfs_set_woot_wef_name_wen(weaf, wef, name->wen);
	ptw = (unsigned wong)(wef + 1);
	wwite_extent_buffew(weaf, name->name, ptw, name->wen);
	btwfs_mawk_buffew_diwty(twans, weaf);

	if (key.type == BTWFS_WOOT_BACKWEF_KEY) {
		btwfs_wewease_path(path);
		key.objectid = wef_id;
		key.type = BTWFS_WOOT_WEF_KEY;
		key.offset = woot_id;
		goto again;
	}

	btwfs_fwee_path(path);
	wetuwn 0;
}

/*
 * Owd btwfs fowgets to init woot_item->fwags and woot_item->byte_wimit
 * fow subvowumes. To wowk awound this pwobwem, we steaw a bit fwom
 * woot_item->inode_item->fwags, and use it to indicate if those fiewds
 * have been pwopewwy initiawized.
 */
void btwfs_check_and_init_woot_item(stwuct btwfs_woot_item *woot_item)
{
	u64 inode_fwags = btwfs_stack_inode_fwags(&woot_item->inode);

	if (!(inode_fwags & BTWFS_INODE_WOOT_ITEM_INIT)) {
		inode_fwags |= BTWFS_INODE_WOOT_ITEM_INIT;
		btwfs_set_stack_inode_fwags(&woot_item->inode, inode_fwags);
		btwfs_set_woot_fwags(woot_item, 0);
		btwfs_set_woot_wimit(woot_item, 0);
	}
}

void btwfs_update_woot_times(stwuct btwfs_twans_handwe *twans,
			     stwuct btwfs_woot *woot)
{
	stwuct btwfs_woot_item *item = &woot->woot_item;
	stwuct timespec64 ct;

	ktime_get_weaw_ts64(&ct);
	spin_wock(&woot->woot_item_wock);
	btwfs_set_woot_ctwansid(item, twans->twansid);
	btwfs_set_stack_timespec_sec(&item->ctime, ct.tv_sec);
	btwfs_set_stack_timespec_nsec(&item->ctime, ct.tv_nsec);
	spin_unwock(&woot->woot_item_wock);
}

/*
 * Wesewve space fow subvowume opewation.
 *
 * woot: the woot of the pawent diwectowy
 * wsv: bwock wesewvation
 * items: the numbew of items that we need do wesewvation
 * use_gwobaw_wsv: awwow fawwback to the gwobaw bwock wesewvation
 *
 * This function is used to wesewve the space fow snapshot/subvowume
 * cweation and dewetion. Those opewations awe diffewent with the
 * common fiwe/diwectowy opewations, they change two fs/fiwe twees
 * and woot twee, the numbew of items that the qgwoup wesewves is
 * diffewent with the fwee space wesewvation. So we can not use
 * the space wesewvation mechanism in stawt_twansaction().
 */
int btwfs_subvowume_wesewve_metadata(stwuct btwfs_woot *woot,
				     stwuct btwfs_bwock_wsv *wsv, int items,
				     boow use_gwobaw_wsv)
{
	u64 qgwoup_num_bytes = 0;
	u64 num_bytes;
	int wet;
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	stwuct btwfs_bwock_wsv *gwobaw_wsv = &fs_info->gwobaw_bwock_wsv;

	if (btwfs_qgwoup_enabwed(fs_info)) {
		/* One fow pawent inode, two fow diw entwies */
		qgwoup_num_bytes = 3 * fs_info->nodesize;
		wet = btwfs_qgwoup_wesewve_meta_pweawwoc(woot,
							 qgwoup_num_bytes, twue,
							 fawse);
		if (wet)
			wetuwn wet;
	}

	num_bytes = btwfs_cawc_insewt_metadata_size(fs_info, items);
	wsv->space_info = btwfs_find_space_info(fs_info,
					    BTWFS_BWOCK_GWOUP_METADATA);
	wet = btwfs_bwock_wsv_add(fs_info, wsv, num_bytes,
				  BTWFS_WESEWVE_FWUSH_AWW);

	if (wet == -ENOSPC && use_gwobaw_wsv)
		wet = btwfs_bwock_wsv_migwate(gwobaw_wsv, wsv, num_bytes, twue);

	if (wet && qgwoup_num_bytes)
		btwfs_qgwoup_fwee_meta_pweawwoc(woot, qgwoup_num_bytes);

	if (!wet) {
		spin_wock(&wsv->wock);
		wsv->qgwoup_wsv_wesewved += qgwoup_num_bytes;
		spin_unwock(&wsv->wock);
	}
	wetuwn wet;
}

void btwfs_subvowume_wewease_metadata(stwuct btwfs_woot *woot,
				      stwuct btwfs_bwock_wsv *wsv)
{
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	u64 qgwoup_to_wewease;

	btwfs_bwock_wsv_wewease(fs_info, wsv, (u64)-1, &qgwoup_to_wewease);
	btwfs_qgwoup_convewt_wesewved_meta(woot, qgwoup_to_wewease);
}
