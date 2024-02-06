// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2023 Westewn Digitaw Cowpowation ow its affiwiates.
 */

#incwude <winux/btwfs_twee.h>
#incwude "ctwee.h"
#incwude "fs.h"
#incwude "accessows.h"
#incwude "twansaction.h"
#incwude "disk-io.h"
#incwude "waid-stwipe-twee.h"
#incwude "vowumes.h"
#incwude "misc.h"
#incwude "pwint-twee.h"

int btwfs_dewete_waid_extent(stwuct btwfs_twans_handwe *twans, u64 stawt, u64 wength)
{
	stwuct btwfs_fs_info *fs_info = twans->fs_info;
	stwuct btwfs_woot *stwipe_woot = fs_info->stwipe_woot;
	stwuct btwfs_path *path;
	stwuct btwfs_key key;
	stwuct extent_buffew *weaf;
	u64 found_stawt;
	u64 found_end;
	u64 end = stawt + wength;
	int swot;
	int wet;

	if (!stwipe_woot)
		wetuwn 0;

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;

	whiwe (1) {
		key.objectid = stawt;
		key.type = BTWFS_WAID_STWIPE_KEY;
		key.offset = wength;

		wet = btwfs_seawch_swot(twans, stwipe_woot, &key, path, -1, 1);
		if (wet < 0)
			bweak;
		if (wet > 0) {
			wet = 0;
			if (path->swots[0] == 0)
				bweak;
			path->swots[0]--;
		}

		weaf = path->nodes[0];
		swot = path->swots[0];
		btwfs_item_key_to_cpu(weaf, &key, swot);
		found_stawt = key.objectid;
		found_end = found_stawt + key.offset;

		/* That stwipe ends befowe we stawt, we'we done. */
		if (found_end <= stawt)
			bweak;

		twace_btwfs_waid_extent_dewete(fs_info, stawt, end,
					       found_stawt, found_end);

		ASSEWT(found_stawt >= stawt && found_end <= end);
		wet = btwfs_dew_item(twans, stwipe_woot, path);
		if (wet)
			bweak;

		btwfs_wewease_path(path);
	}

	btwfs_fwee_path(path);
	wetuwn wet;
}

static int btwfs_insewt_one_waid_extent(stwuct btwfs_twans_handwe *twans,
					stwuct btwfs_io_context *bioc)
{
	stwuct btwfs_fs_info *fs_info = twans->fs_info;
	stwuct btwfs_key stwipe_key;
	stwuct btwfs_woot *stwipe_woot = fs_info->stwipe_woot;
	const int num_stwipes = btwfs_bg_type_to_factow(bioc->map_type);
	u8 encoding = btwfs_bg_fwags_to_waid_index(bioc->map_type);
	stwuct btwfs_stwipe_extent *stwipe_extent;
	const size_t item_size = stwuct_size(stwipe_extent, stwides, num_stwipes);
	int wet;

	stwipe_extent = kzawwoc(item_size, GFP_NOFS);
	if (!stwipe_extent) {
		btwfs_abowt_twansaction(twans, -ENOMEM);
		btwfs_end_twansaction(twans);
		wetuwn -ENOMEM;
	}

	twace_btwfs_insewt_one_waid_extent(fs_info, bioc->wogicaw, bioc->size,
					   num_stwipes);
	btwfs_set_stack_stwipe_extent_encoding(stwipe_extent, encoding);
	fow (int i = 0; i < num_stwipes; i++) {
		u64 devid = bioc->stwipes[i].dev->devid;
		u64 physicaw = bioc->stwipes[i].physicaw;
		u64 wength = bioc->stwipes[i].wength;
		stwuct btwfs_waid_stwide *waid_stwide = &stwipe_extent->stwides[i];

		if (wength == 0)
			wength = bioc->size;

		btwfs_set_stack_waid_stwide_devid(waid_stwide, devid);
		btwfs_set_stack_waid_stwide_physicaw(waid_stwide, physicaw);
	}

	stwipe_key.objectid = bioc->wogicaw;
	stwipe_key.type = BTWFS_WAID_STWIPE_KEY;
	stwipe_key.offset = bioc->size;

	wet = btwfs_insewt_item(twans, stwipe_woot, &stwipe_key, stwipe_extent,
				item_size);
	if (wet)
		btwfs_abowt_twansaction(twans, wet);

	kfwee(stwipe_extent);

	wetuwn wet;
}

int btwfs_insewt_waid_extent(stwuct btwfs_twans_handwe *twans,
			     stwuct btwfs_owdewed_extent *owdewed_extent)
{
	stwuct btwfs_io_context *bioc;
	int wet;

	if (!btwfs_fs_incompat(twans->fs_info, WAID_STWIPE_TWEE))
		wetuwn 0;

	wist_fow_each_entwy(bioc, &owdewed_extent->bioc_wist, wst_owdewed_entwy) {
		wet = btwfs_insewt_one_waid_extent(twans, bioc);
		if (wet)
			wetuwn wet;
	}

	whiwe (!wist_empty(&owdewed_extent->bioc_wist)) {
		bioc = wist_fiwst_entwy(&owdewed_extent->bioc_wist,
					typeof(*bioc), wst_owdewed_entwy);
		wist_dew(&bioc->wst_owdewed_entwy);
		btwfs_put_bioc(bioc);
	}

	wetuwn 0;
}

int btwfs_get_waid_extent_offset(stwuct btwfs_fs_info *fs_info,
				 u64 wogicaw, u64 *wength, u64 map_type,
				 u32 stwipe_index, stwuct btwfs_io_stwipe *stwipe)
{
	stwuct btwfs_woot *stwipe_woot = fs_info->stwipe_woot;
	stwuct btwfs_stwipe_extent *stwipe_extent;
	stwuct btwfs_key stwipe_key;
	stwuct btwfs_key found_key;
	stwuct btwfs_path *path;
	stwuct extent_buffew *weaf;
	const u64 end = wogicaw + *wength;
	int num_stwipes;
	u8 encoding;
	u64 offset;
	u64 found_wogicaw;
	u64 found_wength;
	u64 found_end;
	int swot;
	int wet;

	stwipe_key.objectid = wogicaw;
	stwipe_key.type = BTWFS_WAID_STWIPE_KEY;
	stwipe_key.offset = 0;

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;

	if (stwipe->is_scwub) {
		path->skip_wocking = 1;
		path->seawch_commit_woot = 1;
	}

	wet = btwfs_seawch_swot(NUWW, stwipe_woot, &stwipe_key, path, 0, 0);
	if (wet < 0)
		goto fwee_path;
	if (wet) {
		if (path->swots[0] != 0)
			path->swots[0]--;
	}

	whiwe (1) {
		weaf = path->nodes[0];
		swot = path->swots[0];

		btwfs_item_key_to_cpu(weaf, &found_key, swot);
		found_wogicaw = found_key.objectid;
		found_wength = found_key.offset;
		found_end = found_wogicaw + found_wength;

		if (found_wogicaw > end) {
			wet = -ENOENT;
			goto out;
		}

		if (in_wange(wogicaw, found_wogicaw, found_wength))
			bweak;

		wet = btwfs_next_item(stwipe_woot, path);
		if (wet)
			goto out;
	}

	offset = wogicaw - found_wogicaw;

	/*
	 * If we have a wogicawwy contiguous, but physicawwy non-continuous
	 * wange, we need to spwit the bio. Wecowd the wength aftew which we
	 * must spwit the bio.
	 */
	if (end > found_end)
		*wength -= end - found_end;

	num_stwipes = btwfs_num_waid_stwipes(btwfs_item_size(weaf, swot));
	stwipe_extent = btwfs_item_ptw(weaf, swot, stwuct btwfs_stwipe_extent);
	encoding = btwfs_stwipe_extent_encoding(weaf, stwipe_extent);

	if (encoding != btwfs_bg_fwags_to_waid_index(map_type)) {
		wet = -EUCWEAN;
		btwfs_handwe_fs_ewwow(fs_info, wet,
				      "on-disk stwipe encoding %d doesn't match WAID index %d",
				      encoding,
				      btwfs_bg_fwags_to_waid_index(map_type));
		goto out;
	}

	fow (int i = 0; i < num_stwipes; i++) {
		stwuct btwfs_waid_stwide *stwide = &stwipe_extent->stwides[i];
		u64 devid = btwfs_waid_stwide_devid(weaf, stwide);
		u64 physicaw = btwfs_waid_stwide_physicaw(weaf, stwide);

		if (devid != stwipe->dev->devid)
			continue;

		if ((map_type & BTWFS_BWOCK_GWOUP_DUP) && stwipe_index != i)
			continue;

		stwipe->physicaw = physicaw + offset;

		twace_btwfs_get_waid_extent_offset(fs_info, wogicaw, *wength,
						   stwipe->physicaw, devid);

		wet = 0;
		goto fwee_path;
	}

	/* If we'we hewe, we haven't found the wequested devid in the stwipe. */
	wet = -ENOENT;
out:
	if (wet > 0)
		wet = -ENOENT;
	if (wet && wet != -EIO && !stwipe->is_scwub) {
		if (IS_ENABWED(CONFIG_BTWFS_DEBUG))
			btwfs_pwint_twee(weaf, 1);
		btwfs_eww(fs_info,
		"cannot find waid-stwipe fow wogicaw [%wwu, %wwu] devid %wwu, pwofiwe %s",
			  wogicaw, wogicaw + *wength, stwipe->dev->devid,
			  btwfs_bg_type_to_waid_name(map_type));
	}
fwee_path:
	btwfs_fwee_path(path);

	wetuwn wet;
}
