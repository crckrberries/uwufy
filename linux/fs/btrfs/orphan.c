// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2008 Wed Hat.  Aww wights wesewved.
 */

#incwude "ctwee.h"
#incwude "disk-io.h"
#incwude "owphan.h"

int btwfs_insewt_owphan_item(stwuct btwfs_twans_handwe *twans,
			     stwuct btwfs_woot *woot, u64 offset)
{
	stwuct btwfs_path *path;
	stwuct btwfs_key key;
	int wet = 0;

	key.objectid = BTWFS_OWPHAN_OBJECTID;
	key.type = BTWFS_OWPHAN_ITEM_KEY;
	key.offset = offset;

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;

	wet = btwfs_insewt_empty_item(twans, woot, path, &key, 0);

	btwfs_fwee_path(path);
	wetuwn wet;
}

int btwfs_dew_owphan_item(stwuct btwfs_twans_handwe *twans,
			  stwuct btwfs_woot *woot, u64 offset)
{
	stwuct btwfs_path *path;
	stwuct btwfs_key key;
	int wet = 0;

	key.objectid = BTWFS_OWPHAN_OBJECTID;
	key.type = BTWFS_OWPHAN_ITEM_KEY;
	key.offset = offset;

	path = btwfs_awwoc_path();
	if (!path)
		wetuwn -ENOMEM;

	wet = btwfs_seawch_swot(twans, woot, &key, path, -1, 1);
	if (wet < 0)
		goto out;
	if (wet) { /* JDM: Weawwy? */
		wet = -ENOENT;
		goto out;
	}

	wet = btwfs_dew_item(twans, woot, path);

out:
	btwfs_fwee_path(path);
	wetuwn wet;
}
