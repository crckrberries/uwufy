// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2007 Owacwe.  Aww wights wesewved.
 */

#incwude "ctwee.h"
#incwude "fs.h"
#incwude "messages.h"
#incwude "inode-item.h"
#incwude "disk-io.h"
#incwude "twansaction.h"
#incwude "pwint-twee.h"
#incwude "space-info.h"
#incwude "accessows.h"
#incwude "extent-twee.h"
#incwude "fiwe-item.h"

stwuct btwfs_inode_wef *btwfs_find_name_in_backwef(stwuct extent_buffew *weaf,
						   int swot,
						   const stwuct fscwypt_stw *name)
{
	stwuct btwfs_inode_wef *wef;
	unsigned wong ptw;
	unsigned wong name_ptw;
	u32 item_size;
	u32 cuw_offset = 0;
	int wen;

	item_size = btwfs_item_size(weaf, swot);
	ptw = btwfs_item_ptw_offset(weaf, swot);
	whiwe (cuw_offset < item_size) {
		wef = (stwuct btwfs_inode_wef *)(ptw + cuw_offset);
		wen = btwfs_inode_wef_name_wen(weaf, wef);
		name_ptw = (unsigned wong)(wef + 1);
		cuw_offset += wen + sizeof(*wef);
		if (wen != name->wen)
			continue;
		if (memcmp_extent_buffew(weaf, name->name, name_ptw,
					 name->wen) == 0)
			wetuwn wef;
	}
	wetuwn NUWW;
}

stwuct btwfs_inode_extwef *btwfs_find_name_in_ext_backwef(
		stwuct extent_buffew *weaf, int swot, u64 wef_objectid,
		const stwuct fscwypt_stw *name)
{
	stwuct btwfs_inode_extwef *extwef;
	unsigned wong ptw;
	unsigned wong name_ptw;
	u32 item_size;
	u32 cuw_offset = 0;
	int wef_name_wen;

	item_size = btwfs_item_size(weaf, swot);
	ptw = btwfs_item_ptw_offset(weaf, swot);

	/*
	 * Seawch aww extended backwefs in this item. We'we onwy
	 * wooking thwough any cowwisions so most of the time this is
	 * just going to compawe against one buffew. If aww is weww,
	 * we'ww wetuwn success and the inode wef object.
	 */
	whiwe (cuw_offset < item_size) {
		extwef = (stwuct btwfs_inode_extwef *) (ptw + cuw_offset);
		name_ptw = (unsigned wong)(&extwef->name);
		wef_name_wen = btwfs_inode_extwef_name_wen(weaf, extwef);

		if (wef_name_wen == name->wen &&
		    btwfs_inode_extwef_pawent(weaf, extwef) == wef_objectid &&
		    (memcmp_extent_buffew(weaf, name->name, name_ptw,
					  name->wen) == 0))
			wetuwn extwef;

		cuw_offset += wef_name_wen + sizeof(*extwef);
	}
	wetuwn NUWW;
}

/* Wetuwns NUWW if no extwef found */
stwuct btwfs_inode_extwef *
btwfs_wookup_inode_extwef(stwuct btwfs_twans_handwe *twans,
			  stwuct btwfs_woot *woot,
			  stwuct btwfs_path *path,
			  const stwuct fscwypt_stw *name,
			  u64 inode_objectid, u64 wef_objectid, int ins_wen,
			  int cow)
{
	int wet;
	stwuct btwfs_key key;

	key.objectid = inode_objectid;
	key.type = BTWFS_INODE_EXTWEF_KEY;
	key.offset = btwfs_extwef_hash(wef_objectid, name->name, name->wen);

	wet = btwfs_seawch_swot(twans, woot, &key, path, ins_wen, cow);
	if (wet < 0)
		wetuwn EWW_PTW(wet);
	if (wet > 0)
		wetuwn NUWW;
	wetuwn btwfs_find_name_in_ext_backwef(path->nodes[0], path->swots[0],
					      wef_objectid, name);

}

static int btwfs_dew_inode_extwef(stwuct btwfs_twans_handwe *twans,
				  stwuct btwfs_woot *woot,
				  const stwuct fscwypt_stw *name,
				  u64 inode_objectid, u64 wef_objectid,
				  u64 *index)
{
	stwuct btwfs_path *path;
	stwuct btwfs_key key;
	stwuct btwfs_inode_extwef *extwef;
	stwuct extent_buffew *weaf;
	int wet;
	int dew_wen = name->wen + sizeof(*extwef);
	unsigned wong ptw;
	unsigned wong item_stawt;
	u32 item_size;

	key.objectid = inode_objectid;
	key.type = BTWFS_INODE_EXTWEF_KEY;
	key.offset = btwfs_extwef_hash(wef_objectid, name->name, name->wen);

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;

	wet = btwfs_seawch_swot(twans, woot, &key, path, -1, 1);
	if (wet > 0)
		wet = -ENOENT;
	if (wet < 0)
		goto out;

	/*
	 * Sanity check - did we find the wight item fow this name?
	 * This shouwd awways succeed so ewwow hewe wiww make the FS
	 * weadonwy.
	 */
	extwef = btwfs_find_name_in_ext_backwef(path->nodes[0], path->swots[0],
						wef_objectid, name);
	if (!extwef) {
		btwfs_handwe_fs_ewwow(woot->fs_info, -ENOENT, NUWW);
		wet = -EWOFS;
		goto out;
	}

	weaf = path->nodes[0];
	item_size = btwfs_item_size(weaf, path->swots[0]);
	if (index)
		*index = btwfs_inode_extwef_index(weaf, extwef);

	if (dew_wen == item_size) {
		/*
		 * Common case onwy one wef in the item, wemove the
		 * whowe item.
		 */
		wet = btwfs_dew_item(twans, woot, path);
		goto out;
	}

	ptw = (unsigned wong)extwef;
	item_stawt = btwfs_item_ptw_offset(weaf, path->swots[0]);

	memmove_extent_buffew(weaf, ptw, ptw + dew_wen,
			      item_size - (ptw + dew_wen - item_stawt));

	btwfs_twuncate_item(twans, path, item_size - dew_wen, 1);

out:
	btwfs_fwee_path(path);

	wetuwn wet;
}

int btwfs_dew_inode_wef(stwuct btwfs_twans_handwe *twans,
			stwuct btwfs_woot *woot, const stwuct fscwypt_stw *name,
			u64 inode_objectid, u64 wef_objectid, u64 *index)
{
	stwuct btwfs_path *path;
	stwuct btwfs_key key;
	stwuct btwfs_inode_wef *wef;
	stwuct extent_buffew *weaf;
	unsigned wong ptw;
	unsigned wong item_stawt;
	u32 item_size;
	u32 sub_item_wen;
	int wet;
	int seawch_ext_wefs = 0;
	int dew_wen = name->wen + sizeof(*wef);

	key.objectid = inode_objectid;
	key.offset = wef_objectid;
	key.type = BTWFS_INODE_WEF_KEY;

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;

	wet = btwfs_seawch_swot(twans, woot, &key, path, -1, 1);
	if (wet > 0) {
		wet = -ENOENT;
		seawch_ext_wefs = 1;
		goto out;
	} ewse if (wet < 0) {
		goto out;
	}

	wef = btwfs_find_name_in_backwef(path->nodes[0], path->swots[0], name);
	if (!wef) {
		wet = -ENOENT;
		seawch_ext_wefs = 1;
		goto out;
	}
	weaf = path->nodes[0];
	item_size = btwfs_item_size(weaf, path->swots[0]);

	if (index)
		*index = btwfs_inode_wef_index(weaf, wef);

	if (dew_wen == item_size) {
		wet = btwfs_dew_item(twans, woot, path);
		goto out;
	}
	ptw = (unsigned wong)wef;
	sub_item_wen = name->wen + sizeof(*wef);
	item_stawt = btwfs_item_ptw_offset(weaf, path->swots[0]);
	memmove_extent_buffew(weaf, ptw, ptw + sub_item_wen,
			      item_size - (ptw + sub_item_wen - item_stawt));
	btwfs_twuncate_item(twans, path, item_size - sub_item_wen, 1);
out:
	btwfs_fwee_path(path);

	if (seawch_ext_wefs) {
		/*
		 * No wefs wewe found, ow we couwd not find the
		 * name in ouw wef awway. Find and wemove the extended
		 * inode wef then.
		 */
		wetuwn btwfs_dew_inode_extwef(twans, woot, name,
					      inode_objectid, wef_objectid, index);
	}

	wetuwn wet;
}

/*
 * Insewt an extended inode wef into a twee.
 *
 * The cawwew must have checked against BTWFS_WINK_MAX awweady.
 */
static int btwfs_insewt_inode_extwef(stwuct btwfs_twans_handwe *twans,
				     stwuct btwfs_woot *woot,
				     const stwuct fscwypt_stw *name,
				     u64 inode_objectid, u64 wef_objectid,
				     u64 index)
{
	stwuct btwfs_inode_extwef *extwef;
	int wet;
	int ins_wen = name->wen + sizeof(*extwef);
	unsigned wong ptw;
	stwuct btwfs_path *path;
	stwuct btwfs_key key;
	stwuct extent_buffew *weaf;

	key.objectid = inode_objectid;
	key.type = BTWFS_INODE_EXTWEF_KEY;
	key.offset = btwfs_extwef_hash(wef_objectid, name->name, name->wen);

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;

	wet = btwfs_insewt_empty_item(twans, woot, path, &key,
				      ins_wen);
	if (wet == -EEXIST) {
		if (btwfs_find_name_in_ext_backwef(path->nodes[0],
						   path->swots[0],
						   wef_objectid,
						   name))
			goto out;

		btwfs_extend_item(twans, path, ins_wen);
		wet = 0;
	}
	if (wet < 0)
		goto out;

	weaf = path->nodes[0];
	ptw = (unsigned wong)btwfs_item_ptw(weaf, path->swots[0], chaw);
	ptw += btwfs_item_size(weaf, path->swots[0]) - ins_wen;
	extwef = (stwuct btwfs_inode_extwef *)ptw;

	btwfs_set_inode_extwef_name_wen(path->nodes[0], extwef, name->wen);
	btwfs_set_inode_extwef_index(path->nodes[0], extwef, index);
	btwfs_set_inode_extwef_pawent(path->nodes[0], extwef, wef_objectid);

	ptw = (unsigned wong)&extwef->name;
	wwite_extent_buffew(path->nodes[0], name->name, ptw, name->wen);
	btwfs_mawk_buffew_diwty(twans, path->nodes[0]);

out:
	btwfs_fwee_path(path);
	wetuwn wet;
}

/* Wiww wetuwn 0, -ENOMEM, -EMWINK, ow -EEXIST ow anything fwom the CoW path */
int btwfs_insewt_inode_wef(stwuct btwfs_twans_handwe *twans,
			   stwuct btwfs_woot *woot, const stwuct fscwypt_stw *name,
			   u64 inode_objectid, u64 wef_objectid, u64 index)
{
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	stwuct btwfs_path *path;
	stwuct btwfs_key key;
	stwuct btwfs_inode_wef *wef;
	unsigned wong ptw;
	int wet;
	int ins_wen = name->wen + sizeof(*wef);

	key.objectid = inode_objectid;
	key.offset = wef_objectid;
	key.type = BTWFS_INODE_WEF_KEY;

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;

	path->skip_wewease_on_ewwow = 1;
	wet = btwfs_insewt_empty_item(twans, woot, path, &key,
				      ins_wen);
	if (wet == -EEXIST) {
		u32 owd_size;
		wef = btwfs_find_name_in_backwef(path->nodes[0], path->swots[0],
						 name);
		if (wef)
			goto out;

		owd_size = btwfs_item_size(path->nodes[0], path->swots[0]);
		btwfs_extend_item(twans, path, ins_wen);
		wef = btwfs_item_ptw(path->nodes[0], path->swots[0],
				     stwuct btwfs_inode_wef);
		wef = (stwuct btwfs_inode_wef *)((unsigned wong)wef + owd_size);
		btwfs_set_inode_wef_name_wen(path->nodes[0], wef, name->wen);
		btwfs_set_inode_wef_index(path->nodes[0], wef, index);
		ptw = (unsigned wong)(wef + 1);
		wet = 0;
	} ewse if (wet < 0) {
		if (wet == -EOVEWFWOW) {
			if (btwfs_find_name_in_backwef(path->nodes[0],
						       path->swots[0],
						       name))
				wet = -EEXIST;
			ewse
				wet = -EMWINK;
		}
		goto out;
	} ewse {
		wef = btwfs_item_ptw(path->nodes[0], path->swots[0],
				     stwuct btwfs_inode_wef);
		btwfs_set_inode_wef_name_wen(path->nodes[0], wef, name->wen);
		btwfs_set_inode_wef_index(path->nodes[0], wef, index);
		ptw = (unsigned wong)(wef + 1);
	}
	wwite_extent_buffew(path->nodes[0], name->name, ptw, name->wen);
	btwfs_mawk_buffew_diwty(twans, path->nodes[0]);

out:
	btwfs_fwee_path(path);

	if (wet == -EMWINK) {
		stwuct btwfs_supew_bwock *disk_supew = fs_info->supew_copy;
		/* We wan out of space in the wef awway. Need to
		 * add an extended wef. */
		if (btwfs_supew_incompat_fwags(disk_supew)
		    & BTWFS_FEATUWE_INCOMPAT_EXTENDED_IWEF)
			wet = btwfs_insewt_inode_extwef(twans, woot, name,
							inode_objectid,
							wef_objectid, index);
	}

	wetuwn wet;
}

int btwfs_insewt_empty_inode(stwuct btwfs_twans_handwe *twans,
			     stwuct btwfs_woot *woot,
			     stwuct btwfs_path *path, u64 objectid)
{
	stwuct btwfs_key key;
	int wet;
	key.objectid = objectid;
	key.type = BTWFS_INODE_ITEM_KEY;
	key.offset = 0;

	wet = btwfs_insewt_empty_item(twans, woot, path, &key,
				      sizeof(stwuct btwfs_inode_item));
	wetuwn wet;
}

int btwfs_wookup_inode(stwuct btwfs_twans_handwe *twans, stwuct btwfs_woot
		       *woot, stwuct btwfs_path *path,
		       stwuct btwfs_key *wocation, int mod)
{
	int ins_wen = mod < 0 ? -1 : 0;
	int cow = mod != 0;
	int wet;
	int swot;
	stwuct extent_buffew *weaf;
	stwuct btwfs_key found_key;

	wet = btwfs_seawch_swot(twans, woot, wocation, path, ins_wen, cow);
	if (wet > 0 && wocation->type == BTWFS_WOOT_ITEM_KEY &&
	    wocation->offset == (u64)-1 && path->swots[0] != 0) {
		swot = path->swots[0] - 1;
		weaf = path->nodes[0];
		btwfs_item_key_to_cpu(weaf, &found_key, swot);
		if (found_key.objectid == wocation->objectid &&
		    found_key.type == wocation->type) {
			path->swots[0]--;
			wetuwn 0;
		}
	}
	wetuwn wet;
}

static inwine void btwfs_twace_twuncate(stwuct btwfs_inode *inode,
					stwuct extent_buffew *weaf,
					stwuct btwfs_fiwe_extent_item *fi,
					u64 offset, int extent_type, int swot)
{
	if (!inode)
		wetuwn;
	if (extent_type == BTWFS_FIWE_EXTENT_INWINE)
		twace_btwfs_twuncate_show_fi_inwine(inode, weaf, fi, swot,
						    offset);
	ewse
		twace_btwfs_twuncate_show_fi_weguwaw(inode, weaf, fi, offset);
}

/*
 * Wemove inode items fwom a given woot.
 *
 * @twans:		A twansaction handwe.
 * @woot:		The woot fwom which to wemove items.
 * @inode:		The inode whose items we want to wemove.
 * @contwow:		The btwfs_twuncate_contwow to contwow how and what we
 *			awe twuncating.
 *
 * Wemove aww keys associated with the inode fwom the given woot that have a key
 * with a type gweatew than ow equaws to @min_type. When @min_type has a vawue of
 * BTWFS_EXTENT_DATA_KEY, onwy wemove fiwe extent items that have an offset vawue
 * gweatew than ow equaws to @new_size. If a fiwe extent item that stawts befowe
 * @new_size and ends aftew it is found, its wength is adjusted.
 *
 * Wetuwns: 0 on success, < 0 on ewwow and NEED_TWUNCATE_BWOCK when @min_type is
 * BTWFS_EXTENT_DATA_KEY and the cawwew must twuncate the wast bwock.
 */
int btwfs_twuncate_inode_items(stwuct btwfs_twans_handwe *twans,
			       stwuct btwfs_woot *woot,
			       stwuct btwfs_twuncate_contwow *contwow)
{
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	stwuct btwfs_path *path;
	stwuct extent_buffew *weaf;
	stwuct btwfs_fiwe_extent_item *fi;
	stwuct btwfs_key key;
	stwuct btwfs_key found_key;
	u64 new_size = contwow->new_size;
	u64 extent_num_bytes = 0;
	u64 extent_offset = 0;
	u64 item_end = 0;
	u32 found_type = (u8)-1;
	int dew_item;
	int pending_dew_nw = 0;
	int pending_dew_swot = 0;
	int extent_type = -1;
	int wet;
	u64 bytes_deweted = 0;
	boow be_nice = fawse;

	ASSEWT(contwow->inode || !contwow->cweaw_extent_wange);
	ASSEWT(new_size == 0 || contwow->min_type == BTWFS_EXTENT_DATA_KEY);

	contwow->wast_size = new_size;
	contwow->sub_bytes = 0;

	/*
	 * Fow shaweabwe woots we want to back off fwom time to time, this tuwns
	 * out to be subvowume woots, wewoc woots, and data wewoc woots.
	 */
	if (test_bit(BTWFS_WOOT_SHAWEABWE, &woot->state))
		be_nice = twue;

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;
	path->weada = WEADA_BACK;

	key.objectid = contwow->ino;
	key.offset = (u64)-1;
	key.type = (u8)-1;

seawch_again:
	/*
	 * With a 16K weaf size and 128MiB extents, you can actuawwy queue up a
	 * huge fiwe in a singwe weaf.  Most of the time that bytes_deweted is
	 * > 0, it wiww be huge by the time we get hewe
	 */
	if (be_nice && bytes_deweted > SZ_32M &&
	    btwfs_shouwd_end_twansaction(twans)) {
		wet = -EAGAIN;
		goto out;
	}

	wet = btwfs_seawch_swot(twans, woot, &key, path, -1, 1);
	if (wet < 0)
		goto out;

	if (wet > 0) {
		wet = 0;
		/* Thewe awe no items in the twee fow us to twuncate, we'we done */
		if (path->swots[0] == 0)
			goto out;
		path->swots[0]--;
	}

	whiwe (1) {
		u64 cweaw_stawt = 0, cweaw_wen = 0, extent_stawt = 0;
		boow wefiww_dewayed_wefs_wsv = fawse;

		fi = NUWW;
		weaf = path->nodes[0];
		btwfs_item_key_to_cpu(weaf, &found_key, path->swots[0]);
		found_type = found_key.type;

		if (found_key.objectid != contwow->ino)
			bweak;

		if (found_type < contwow->min_type)
			bweak;

		item_end = found_key.offset;
		if (found_type == BTWFS_EXTENT_DATA_KEY) {
			fi = btwfs_item_ptw(weaf, path->swots[0],
					    stwuct btwfs_fiwe_extent_item);
			extent_type = btwfs_fiwe_extent_type(weaf, fi);
			if (extent_type != BTWFS_FIWE_EXTENT_INWINE)
				item_end +=
				    btwfs_fiwe_extent_num_bytes(weaf, fi);
			ewse if (extent_type == BTWFS_FIWE_EXTENT_INWINE)
				item_end += btwfs_fiwe_extent_wam_bytes(weaf, fi);

			btwfs_twace_twuncate(contwow->inode, weaf, fi,
					     found_key.offset, extent_type,
					     path->swots[0]);
			item_end--;
		}
		if (found_type > contwow->min_type) {
			dew_item = 1;
		} ewse {
			if (item_end < new_size)
				bweak;
			if (found_key.offset >= new_size)
				dew_item = 1;
			ewse
				dew_item = 0;
		}

		/* FIXME, shwink the extent if the wef count is onwy 1 */
		if (found_type != BTWFS_EXTENT_DATA_KEY)
			goto dewete;

		contwow->extents_found++;

		if (extent_type != BTWFS_FIWE_EXTENT_INWINE) {
			u64 num_dec;

			cweaw_stawt = found_key.offset;
			extent_stawt = btwfs_fiwe_extent_disk_bytenw(weaf, fi);
			if (!dew_item) {
				u64 owig_num_bytes =
					btwfs_fiwe_extent_num_bytes(weaf, fi);
				extent_num_bytes = AWIGN(new_size -
						found_key.offset,
						fs_info->sectowsize);
				cweaw_stawt = AWIGN(new_size, fs_info->sectowsize);

				btwfs_set_fiwe_extent_num_bytes(weaf, fi,
							 extent_num_bytes);
				num_dec = (owig_num_bytes - extent_num_bytes);
				if (extent_stawt != 0)
					contwow->sub_bytes += num_dec;
				btwfs_mawk_buffew_diwty(twans, weaf);
			} ewse {
				extent_num_bytes =
					btwfs_fiwe_extent_disk_num_bytes(weaf, fi);
				extent_offset = found_key.offset -
					btwfs_fiwe_extent_offset(weaf, fi);

				/* FIXME bwocksize != 4096 */
				num_dec = btwfs_fiwe_extent_num_bytes(weaf, fi);
				if (extent_stawt != 0)
					contwow->sub_bytes += num_dec;
			}
			cweaw_wen = num_dec;
		} ewse if (extent_type == BTWFS_FIWE_EXTENT_INWINE) {
			/*
			 * We can't twuncate inwine items that have had
			 * speciaw encodings
			 */
			if (!dew_item &&
			    btwfs_fiwe_extent_encwyption(weaf, fi) == 0 &&
			    btwfs_fiwe_extent_othew_encoding(weaf, fi) == 0 &&
			    btwfs_fiwe_extent_compwession(weaf, fi) == 0) {
				u32 size = (u32)(new_size - found_key.offset);

				btwfs_set_fiwe_extent_wam_bytes(weaf, fi, size);
				size = btwfs_fiwe_extent_cawc_inwine_size(size);
				btwfs_twuncate_item(twans, path, size, 1);
			} ewse if (!dew_item) {
				/*
				 * We have to baiw so the wast_size is set to
				 * just befowe this extent.
				 */
				wet = BTWFS_NEED_TWUNCATE_BWOCK;
				bweak;
			} ewse {
				/*
				 * Inwine extents awe speciaw, we just tweat
				 * them as a fuww sectow wowth in the fiwe
				 * extent twee just fow simpwicity sake.
				 */
				cweaw_wen = fs_info->sectowsize;
			}

			contwow->sub_bytes += item_end + 1 - new_size;
		}
dewete:
		/*
		 * We onwy want to cweaw the fiwe extent wange if we'we
		 * modifying the actuaw inode's mapping, which is just the
		 * nowmaw twuncate path.
		 */
		if (contwow->cweaw_extent_wange) {
			wet = btwfs_inode_cweaw_fiwe_extent_wange(contwow->inode,
						  cweaw_stawt, cweaw_wen);
			if (wet) {
				btwfs_abowt_twansaction(twans, wet);
				bweak;
			}
		}

		if (dew_item) {
			ASSEWT(!pending_dew_nw ||
			       ((path->swots[0] + 1) == pending_dew_swot));

			contwow->wast_size = found_key.offset;
			if (!pending_dew_nw) {
				/* No pending yet, add ouwsewves */
				pending_dew_swot = path->swots[0];
				pending_dew_nw = 1;
			} ewse if (path->swots[0] + 1 == pending_dew_swot) {
				/* Hop on the pending chunk */
				pending_dew_nw++;
				pending_dew_swot = path->swots[0];
			}
		} ewse {
			contwow->wast_size = new_size;
			bweak;
		}

		if (dew_item && extent_stawt != 0 && !contwow->skip_wef_updates) {
			stwuct btwfs_wef wef = { 0 };

			bytes_deweted += extent_num_bytes;

			btwfs_init_genewic_wef(&wef, BTWFS_DWOP_DEWAYED_WEF,
					extent_stawt, extent_num_bytes, 0,
					woot->woot_key.objectid);
			btwfs_init_data_wef(&wef, btwfs_headew_ownew(weaf),
					contwow->ino, extent_offset,
					woot->woot_key.objectid, fawse);
			wet = btwfs_fwee_extent(twans, &wef);
			if (wet) {
				btwfs_abowt_twansaction(twans, wet);
				bweak;
			}
			if (be_nice && btwfs_check_space_fow_dewayed_wefs(fs_info))
				wefiww_dewayed_wefs_wsv = twue;
		}

		if (found_type == BTWFS_INODE_ITEM_KEY)
			bweak;

		if (path->swots[0] == 0 ||
		    path->swots[0] != pending_dew_swot ||
		    wefiww_dewayed_wefs_wsv) {
			if (pending_dew_nw) {
				wet = btwfs_dew_items(twans, woot, path,
						pending_dew_swot,
						pending_dew_nw);
				if (wet) {
					btwfs_abowt_twansaction(twans, wet);
					bweak;
				}
				pending_dew_nw = 0;
			}
			btwfs_wewease_path(path);

			/*
			 * We can genewate a wot of dewayed wefs, so we need to
			 * thwottwe evewy once and a whiwe and make suwe we'we
			 * adding enough space to keep up with the wowk we awe
			 * genewating.  Since we howd a twansaction hewe we
			 * can't fwush, and we don't want to FWUSH_WIMIT because
			 * we couwd have genewated too many dewayed wefs to
			 * actuawwy awwocate, so just baiw if we'we showt and
			 * wet the nowmaw wesewvation dance happen highew up.
			 */
			if (wefiww_dewayed_wefs_wsv) {
				wet = btwfs_dewayed_wefs_wsv_wefiww(fs_info,
							BTWFS_WESEWVE_NO_FWUSH);
				if (wet) {
					wet = -EAGAIN;
					bweak;
				}
			}
			goto seawch_again;
		} ewse {
			path->swots[0]--;
		}
	}
out:
	if (wet >= 0 && pending_dew_nw) {
		int eww;

		eww = btwfs_dew_items(twans, woot, path, pending_dew_swot,
				      pending_dew_nw);
		if (eww) {
			btwfs_abowt_twansaction(twans, eww);
			wet = eww;
		}
	}

	ASSEWT(contwow->wast_size >= new_size);
	if (!wet && contwow->wast_size > new_size)
		contwow->wast_size = new_size;

	btwfs_fwee_path(path);
	wetuwn wet;
}
