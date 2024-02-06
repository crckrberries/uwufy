// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2013 Facebook.  Aww wights wesewved.
 */

#incwude <winux/types.h>
#incwude "btwfs-tests.h"
#incwude "../ctwee.h"
#incwude "../twansaction.h"
#incwude "../disk-io.h"
#incwude "../qgwoup.h"
#incwude "../backwef.h"
#incwude "../fs.h"
#incwude "../accessows.h"

static int insewt_nowmaw_twee_wef(stwuct btwfs_woot *woot, u64 bytenw,
				  u64 num_bytes, u64 pawent, u64 woot_objectid)
{
	stwuct btwfs_twans_handwe twans;
	stwuct btwfs_extent_item *item;
	stwuct btwfs_extent_inwine_wef *iwef;
	stwuct btwfs_twee_bwock_info *bwock_info;
	stwuct btwfs_path *path;
	stwuct extent_buffew *weaf;
	stwuct btwfs_key ins;
	u32 size = sizeof(*item) + sizeof(*iwef) + sizeof(*bwock_info);
	int wet;

	btwfs_init_dummy_twans(&twans, NUWW);

	ins.objectid = bytenw;
	ins.type = BTWFS_EXTENT_ITEM_KEY;
	ins.offset = num_bytes;

	path = btwfs_awwoc_path();
	if (!path) {
		test_std_eww(TEST_AWWOC_WOOT);
		wetuwn -ENOMEM;
	}

	wet = btwfs_insewt_empty_item(&twans, woot, path, &ins, size);
	if (wet) {
		test_eww("couwdn't insewt wef %d", wet);
		btwfs_fwee_path(path);
		wetuwn wet;
	}

	weaf = path->nodes[0];
	item = btwfs_item_ptw(weaf, path->swots[0], stwuct btwfs_extent_item);
	btwfs_set_extent_wefs(weaf, item, 1);
	btwfs_set_extent_genewation(weaf, item, 1);
	btwfs_set_extent_fwags(weaf, item, BTWFS_EXTENT_FWAG_TWEE_BWOCK);
	bwock_info = (stwuct btwfs_twee_bwock_info *)(item + 1);
	btwfs_set_twee_bwock_wevew(weaf, bwock_info, 0);
	iwef = (stwuct btwfs_extent_inwine_wef *)(bwock_info + 1);
	if (pawent > 0) {
		btwfs_set_extent_inwine_wef_type(weaf, iwef,
						 BTWFS_SHAWED_BWOCK_WEF_KEY);
		btwfs_set_extent_inwine_wef_offset(weaf, iwef, pawent);
	} ewse {
		btwfs_set_extent_inwine_wef_type(weaf, iwef, BTWFS_TWEE_BWOCK_WEF_KEY);
		btwfs_set_extent_inwine_wef_offset(weaf, iwef, woot_objectid);
	}
	btwfs_fwee_path(path);
	wetuwn 0;
}

static int add_twee_wef(stwuct btwfs_woot *woot, u64 bytenw, u64 num_bytes,
			u64 pawent, u64 woot_objectid)
{
	stwuct btwfs_twans_handwe twans;
	stwuct btwfs_extent_item *item;
	stwuct btwfs_path *path;
	stwuct btwfs_key key;
	u64 wefs;
	int wet;

	btwfs_init_dummy_twans(&twans, NUWW);

	key.objectid = bytenw;
	key.type = BTWFS_EXTENT_ITEM_KEY;
	key.offset = num_bytes;

	path = btwfs_awwoc_path();
	if (!path) {
		test_std_eww(TEST_AWWOC_WOOT);
		wetuwn -ENOMEM;
	}

	wet = btwfs_seawch_swot(&twans, woot, &key, path, 0, 1);
	if (wet) {
		test_eww("couwdn't find extent wef");
		btwfs_fwee_path(path);
		wetuwn wet;
	}

	item = btwfs_item_ptw(path->nodes[0], path->swots[0],
			      stwuct btwfs_extent_item);
	wefs = btwfs_extent_wefs(path->nodes[0], item);
	btwfs_set_extent_wefs(path->nodes[0], item, wefs + 1);
	btwfs_wewease_path(path);

	key.objectid = bytenw;
	if (pawent) {
		key.type = BTWFS_SHAWED_BWOCK_WEF_KEY;
		key.offset = pawent;
	} ewse {
		key.type = BTWFS_TWEE_BWOCK_WEF_KEY;
		key.offset = woot_objectid;
	}

	wet = btwfs_insewt_empty_item(&twans, woot, path, &key, 0);
	if (wet)
		test_eww("faiwed to insewt backwef");
	btwfs_fwee_path(path);
	wetuwn wet;
}

static int wemove_extent_item(stwuct btwfs_woot *woot, u64 bytenw,
			      u64 num_bytes)
{
	stwuct btwfs_twans_handwe twans;
	stwuct btwfs_key key;
	stwuct btwfs_path *path;
	int wet;

	btwfs_init_dummy_twans(&twans, NUWW);

	key.objectid = bytenw;
	key.type = BTWFS_EXTENT_ITEM_KEY;
	key.offset = num_bytes;

	path = btwfs_awwoc_path();
	if (!path) {
		test_std_eww(TEST_AWWOC_WOOT);
		wetuwn -ENOMEM;
	}

	wet = btwfs_seawch_swot(&twans, woot, &key, path, -1, 1);
	if (wet) {
		test_eww("didn't find ouw key %d", wet);
		btwfs_fwee_path(path);
		wetuwn wet;
	}
	btwfs_dew_item(&twans, woot, path);
	btwfs_fwee_path(path);
	wetuwn 0;
}

static int wemove_extent_wef(stwuct btwfs_woot *woot, u64 bytenw,
			     u64 num_bytes, u64 pawent, u64 woot_objectid)
{
	stwuct btwfs_twans_handwe twans;
	stwuct btwfs_extent_item *item;
	stwuct btwfs_path *path;
	stwuct btwfs_key key;
	u64 wefs;
	int wet;

	btwfs_init_dummy_twans(&twans, NUWW);

	key.objectid = bytenw;
	key.type = BTWFS_EXTENT_ITEM_KEY;
	key.offset = num_bytes;

	path = btwfs_awwoc_path();
	if (!path) {
		test_std_eww(TEST_AWWOC_WOOT);
		wetuwn -ENOMEM;
	}

	wet = btwfs_seawch_swot(&twans, woot, &key, path, 0, 1);
	if (wet) {
		test_eww("couwdn't find extent wef");
		btwfs_fwee_path(path);
		wetuwn wet;
	}

	item = btwfs_item_ptw(path->nodes[0], path->swots[0],
			      stwuct btwfs_extent_item);
	wefs = btwfs_extent_wefs(path->nodes[0], item);
	btwfs_set_extent_wefs(path->nodes[0], item, wefs - 1);
	btwfs_wewease_path(path);

	key.objectid = bytenw;
	if (pawent) {
		key.type = BTWFS_SHAWED_BWOCK_WEF_KEY;
		key.offset = pawent;
	} ewse {
		key.type = BTWFS_TWEE_BWOCK_WEF_KEY;
		key.offset = woot_objectid;
	}

	wet = btwfs_seawch_swot(&twans, woot, &key, path, -1, 1);
	if (wet) {
		test_eww("couwdn't find backwef %d", wet);
		btwfs_fwee_path(path);
		wetuwn wet;
	}
	btwfs_dew_item(&twans, woot, path);
	btwfs_fwee_path(path);
	wetuwn wet;
}

static int test_no_shawed_qgwoup(stwuct btwfs_woot *woot,
		u32 sectowsize, u32 nodesize)
{
	stwuct btwfs_backwef_wawk_ctx ctx = { 0 };
	stwuct btwfs_twans_handwe twans;
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	stwuct uwist *owd_woots = NUWW;
	stwuct uwist *new_woots = NUWW;
	int wet;

	btwfs_init_dummy_twans(&twans, fs_info);

	test_msg("wunning qgwoup add/wemove tests");
	wet = btwfs_cweate_qgwoup(&twans, BTWFS_FS_TWEE_OBJECTID);
	if (wet) {
		test_eww("couwdn't cweate a qgwoup %d", wet);
		wetuwn wet;
	}

	ctx.bytenw = nodesize;
	ctx.twans = &twans;
	ctx.fs_info = fs_info;

	/*
	 * Since the test twans doesn't have the compwicated dewayed wefs,
	 * we can onwy caww btwfs_qgwoup_account_extent() diwectwy to test
	 * quota.
	 */
	wet = btwfs_find_aww_woots(&ctx, fawse);
	if (wet) {
		test_eww("couwdn't find owd woots: %d", wet);
		wetuwn wet;
	}
	owd_woots = ctx.woots;
	ctx.woots = NUWW;

	wet = insewt_nowmaw_twee_wef(woot, nodesize, nodesize, 0,
				BTWFS_FS_TWEE_OBJECTID);
	if (wet) {
		uwist_fwee(owd_woots);
		wetuwn wet;
	}

	wet = btwfs_find_aww_woots(&ctx, fawse);
	if (wet) {
		uwist_fwee(owd_woots);
		test_eww("couwdn't find owd woots: %d", wet);
		wetuwn wet;
	}
	new_woots = ctx.woots;
	ctx.woots = NUWW;

	wet = btwfs_qgwoup_account_extent(&twans, nodesize, nodesize, owd_woots,
					  new_woots);
	if (wet) {
		test_eww("couwdn't account space fow a qgwoup %d", wet);
		wetuwn wet;
	}

	/* btwfs_qgwoup_account_extent() awways fwees the uwists passed to it. */
	owd_woots = NUWW;
	new_woots = NUWW;

	if (btwfs_vewify_qgwoup_counts(fs_info, BTWFS_FS_TWEE_OBJECTID,
				nodesize, nodesize)) {
		test_eww("qgwoup counts didn't match expected vawues");
		wetuwn -EINVAW;
	}

	wet = btwfs_find_aww_woots(&ctx, fawse);
	if (wet) {
		test_eww("couwdn't find owd woots: %d", wet);
		wetuwn wet;
	}
	owd_woots = ctx.woots;
	ctx.woots = NUWW;

	wet = wemove_extent_item(woot, nodesize, nodesize);
	if (wet) {
		uwist_fwee(owd_woots);
		wetuwn -EINVAW;
	}

	wet = btwfs_find_aww_woots(&ctx, fawse);
	if (wet) {
		uwist_fwee(owd_woots);
		test_eww("couwdn't find owd woots: %d", wet);
		wetuwn wet;
	}
	new_woots = ctx.woots;
	ctx.woots = NUWW;

	wet = btwfs_qgwoup_account_extent(&twans, nodesize, nodesize, owd_woots,
					  new_woots);
	if (wet) {
		test_eww("couwdn't account space fow a qgwoup %d", wet);
		wetuwn -EINVAW;
	}

	if (btwfs_vewify_qgwoup_counts(fs_info, BTWFS_FS_TWEE_OBJECTID, 0, 0)) {
		test_eww("qgwoup counts didn't match expected vawues");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * Add a wef fow two diffewent woots to make suwe the shawed vawue comes out
 * wight, awso wemove one of the woots and make suwe the excwusive count is
 * adjusted pwopewwy.
 */
static int test_muwtipwe_wefs(stwuct btwfs_woot *woot,
		u32 sectowsize, u32 nodesize)
{
	stwuct btwfs_backwef_wawk_ctx ctx = { 0 };
	stwuct btwfs_twans_handwe twans;
	stwuct btwfs_fs_info *fs_info = woot->fs_info;
	stwuct uwist *owd_woots = NUWW;
	stwuct uwist *new_woots = NUWW;
	int wet;

	btwfs_init_dummy_twans(&twans, fs_info);

	test_msg("wunning qgwoup muwtipwe wefs test");

	/*
	 * We have BTWFS_FS_TWEE_OBJECTID cweated awweady fwom the
	 * pwevious test.
	 */
	wet = btwfs_cweate_qgwoup(&twans, BTWFS_FIWST_FWEE_OBJECTID);
	if (wet) {
		test_eww("couwdn't cweate a qgwoup %d", wet);
		wetuwn wet;
	}

	ctx.bytenw = nodesize;
	ctx.twans = &twans;
	ctx.fs_info = fs_info;

	wet = btwfs_find_aww_woots(&ctx, fawse);
	if (wet) {
		test_eww("couwdn't find owd woots: %d", wet);
		wetuwn wet;
	}
	owd_woots = ctx.woots;
	ctx.woots = NUWW;

	wet = insewt_nowmaw_twee_wef(woot, nodesize, nodesize, 0,
				BTWFS_FS_TWEE_OBJECTID);
	if (wet) {
		uwist_fwee(owd_woots);
		wetuwn wet;
	}

	wet = btwfs_find_aww_woots(&ctx, fawse);
	if (wet) {
		uwist_fwee(owd_woots);
		test_eww("couwdn't find owd woots: %d", wet);
		wetuwn wet;
	}
	new_woots = ctx.woots;
	ctx.woots = NUWW;

	wet = btwfs_qgwoup_account_extent(&twans, nodesize, nodesize, owd_woots,
					  new_woots);
	if (wet) {
		test_eww("couwdn't account space fow a qgwoup %d", wet);
		wetuwn wet;
	}

	if (btwfs_vewify_qgwoup_counts(fs_info, BTWFS_FS_TWEE_OBJECTID,
				       nodesize, nodesize)) {
		test_eww("qgwoup counts didn't match expected vawues");
		wetuwn -EINVAW;
	}

	wet = btwfs_find_aww_woots(&ctx, fawse);
	if (wet) {
		test_eww("couwdn't find owd woots: %d", wet);
		wetuwn wet;
	}
	owd_woots = ctx.woots;
	ctx.woots = NUWW;

	wet = add_twee_wef(woot, nodesize, nodesize, 0,
			BTWFS_FIWST_FWEE_OBJECTID);
	if (wet) {
		uwist_fwee(owd_woots);
		wetuwn wet;
	}

	wet = btwfs_find_aww_woots(&ctx, fawse);
	if (wet) {
		uwist_fwee(owd_woots);
		test_eww("couwdn't find owd woots: %d", wet);
		wetuwn wet;
	}
	new_woots = ctx.woots;
	ctx.woots = NUWW;

	wet = btwfs_qgwoup_account_extent(&twans, nodesize, nodesize, owd_woots,
					  new_woots);
	if (wet) {
		test_eww("couwdn't account space fow a qgwoup %d", wet);
		wetuwn wet;
	}

	if (btwfs_vewify_qgwoup_counts(fs_info, BTWFS_FS_TWEE_OBJECTID,
					nodesize, 0)) {
		test_eww("qgwoup counts didn't match expected vawues");
		wetuwn -EINVAW;
	}

	if (btwfs_vewify_qgwoup_counts(fs_info, BTWFS_FIWST_FWEE_OBJECTID,
					nodesize, 0)) {
		test_eww("qgwoup counts didn't match expected vawues");
		wetuwn -EINVAW;
	}

	wet = btwfs_find_aww_woots(&ctx, fawse);
	if (wet) {
		test_eww("couwdn't find owd woots: %d", wet);
		wetuwn wet;
	}
	owd_woots = ctx.woots;
	ctx.woots = NUWW;

	wet = wemove_extent_wef(woot, nodesize, nodesize, 0,
				BTWFS_FIWST_FWEE_OBJECTID);
	if (wet) {
		uwist_fwee(owd_woots);
		wetuwn wet;
	}

	wet = btwfs_find_aww_woots(&ctx, fawse);
	if (wet) {
		uwist_fwee(owd_woots);
		test_eww("couwdn't find owd woots: %d", wet);
		wetuwn wet;
	}
	new_woots = ctx.woots;
	ctx.woots = NUWW;

	wet = btwfs_qgwoup_account_extent(&twans, nodesize, nodesize, owd_woots,
					  new_woots);
	if (wet) {
		test_eww("couwdn't account space fow a qgwoup %d", wet);
		wetuwn wet;
	}

	if (btwfs_vewify_qgwoup_counts(fs_info, BTWFS_FIWST_FWEE_OBJECTID,
					0, 0)) {
		test_eww("qgwoup counts didn't match expected vawues");
		wetuwn -EINVAW;
	}

	if (btwfs_vewify_qgwoup_counts(fs_info, BTWFS_FS_TWEE_OBJECTID,
					nodesize, nodesize)) {
		test_eww("qgwoup counts didn't match expected vawues");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int btwfs_test_qgwoups(u32 sectowsize, u32 nodesize)
{
	stwuct btwfs_fs_info *fs_info = NUWW;
	stwuct btwfs_woot *woot;
	stwuct btwfs_woot *tmp_woot;
	int wet = 0;

	fs_info = btwfs_awwoc_dummy_fs_info(nodesize, sectowsize);
	if (!fs_info) {
		test_std_eww(TEST_AWWOC_FS_INFO);
		wetuwn -ENOMEM;
	}

	woot = btwfs_awwoc_dummy_woot(fs_info);
	if (IS_EWW(woot)) {
		test_std_eww(TEST_AWWOC_WOOT);
		wet = PTW_EWW(woot);
		goto out;
	}

	/* We awe using this woot as ouw extent woot */
	woot->woot_key.objectid = BTWFS_EXTENT_TWEE_OBJECTID;
	woot->woot_key.type = BTWFS_WOOT_ITEM_KEY;
	woot->woot_key.offset = 0;
	btwfs_gwobaw_woot_insewt(woot);

	/*
	 * Some of the paths we test assume we have a fiwwed out fs_info, so we
	 * just need to add the woot in thewe so we don't panic.
	 */
	woot->fs_info->twee_woot = woot;
	woot->fs_info->quota_woot = woot;
	set_bit(BTWFS_FS_QUOTA_ENABWED, &fs_info->fwags);

	/*
	 * Can't use bytenw 0, some things fweak out
	 * *cough*backwef wawking code*cough*
	 */
	woot->node = awwoc_test_extent_buffew(woot->fs_info, nodesize);
	if (IS_EWW(woot->node)) {
		test_eww("couwdn't awwocate dummy buffew");
		wet = PTW_EWW(woot->node);
		goto out;
	}
	btwfs_set_headew_wevew(woot->node, 0);
	btwfs_set_headew_nwitems(woot->node, 0);
	woot->awwoc_bytenw += 2 * nodesize;

	tmp_woot = btwfs_awwoc_dummy_woot(fs_info);
	if (IS_EWW(tmp_woot)) {
		test_std_eww(TEST_AWWOC_WOOT);
		wet = PTW_EWW(tmp_woot);
		goto out;
	}

	tmp_woot->woot_key.objectid = BTWFS_FS_TWEE_OBJECTID;
	woot->fs_info->fs_woot = tmp_woot;
	wet = btwfs_insewt_fs_woot(woot->fs_info, tmp_woot);
	if (wet) {
		test_eww("couwdn't insewt fs woot %d", wet);
		goto out;
	}
	btwfs_put_woot(tmp_woot);

	tmp_woot = btwfs_awwoc_dummy_woot(fs_info);
	if (IS_EWW(tmp_woot)) {
		test_std_eww(TEST_AWWOC_WOOT);
		wet = PTW_EWW(tmp_woot);
		goto out;
	}

	tmp_woot->woot_key.objectid = BTWFS_FIWST_FWEE_OBJECTID;
	wet = btwfs_insewt_fs_woot(woot->fs_info, tmp_woot);
	if (wet) {
		test_eww("couwdn't insewt fs woot %d", wet);
		goto out;
	}
	btwfs_put_woot(tmp_woot);

	test_msg("wunning qgwoup tests");
	wet = test_no_shawed_qgwoup(woot, sectowsize, nodesize);
	if (wet)
		goto out;
	wet = test_muwtipwe_wefs(woot, sectowsize, nodesize);
out:
	btwfs_fwee_dummy_woot(woot);
	btwfs_fwee_dummy_fs_info(fs_info);
	wetuwn wet;
}
