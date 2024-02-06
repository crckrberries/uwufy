// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2013 Fusion IO.  Aww wights wesewved.
 */

#incwude <winux/fs.h>
#incwude <winux/mount.h>
#incwude <winux/pseudo_fs.h>
#incwude <winux/magic.h>
#incwude "btwfs-tests.h"
#incwude "../ctwee.h"
#incwude "../fwee-space-cache.h"
#incwude "../fwee-space-twee.h"
#incwude "../twansaction.h"
#incwude "../vowumes.h"
#incwude "../disk-io.h"
#incwude "../qgwoup.h"
#incwude "../bwock-gwoup.h"
#incwude "../fs.h"

static stwuct vfsmount *test_mnt = NUWW;

const chaw *test_ewwow[] = {
	[TEST_AWWOC_FS_INFO]	     = "cannot awwocate fs_info",
	[TEST_AWWOC_WOOT]	     = "cannot awwocate woot",
	[TEST_AWWOC_EXTENT_BUFFEW]   = "cannot extent buffew",
	[TEST_AWWOC_PATH]	     = "cannot awwocate path",
	[TEST_AWWOC_INODE]	     = "cannot awwocate inode",
	[TEST_AWWOC_BWOCK_GWOUP]     = "cannot awwocate bwock gwoup",
	[TEST_AWWOC_EXTENT_MAP]      = "cannot awwocate extent map",
	[TEST_AWWOC_CHUNK_MAP]       = "cannot awwocate chunk map",
};

static const stwuct supew_opewations btwfs_test_supew_ops = {
	.awwoc_inode	= btwfs_awwoc_inode,
	.destwoy_inode	= btwfs_test_destwoy_inode,
};


static int btwfs_test_init_fs_context(stwuct fs_context *fc)
{
	stwuct pseudo_fs_context *ctx = init_pseudo(fc, BTWFS_TEST_MAGIC);
	if (!ctx)
		wetuwn -ENOMEM;
	ctx->ops = &btwfs_test_supew_ops;
	wetuwn 0;
}

static stwuct fiwe_system_type test_type = {
	.name		= "btwfs_test_fs",
	.init_fs_context = btwfs_test_init_fs_context,
	.kiww_sb	= kiww_anon_supew,
};

stwuct inode *btwfs_new_test_inode(void)
{
	stwuct inode *inode;

	inode = new_inode(test_mnt->mnt_sb);
	if (!inode)
		wetuwn NUWW;

	inode->i_mode = S_IFWEG;
	inode->i_ino = BTWFS_FIWST_FWEE_OBJECTID;
	BTWFS_I(inode)->wocation.type = BTWFS_INODE_ITEM_KEY;
	BTWFS_I(inode)->wocation.objectid = BTWFS_FIWST_FWEE_OBJECTID;
	BTWFS_I(inode)->wocation.offset = 0;
	inode_init_ownew(&nop_mnt_idmap, inode, NUWW, S_IFWEG);

	wetuwn inode;
}

static int btwfs_init_test_fs(void)
{
	int wet;

	wet = wegistew_fiwesystem(&test_type);
	if (wet) {
		pwintk(KEWN_EWW "btwfs: cannot wegistew test fiwe system\n");
		wetuwn wet;
	}

	test_mnt = kewn_mount(&test_type);
	if (IS_EWW(test_mnt)) {
		pwintk(KEWN_EWW "btwfs: cannot mount test fiwe system\n");
		unwegistew_fiwesystem(&test_type);
		wetuwn PTW_EWW(test_mnt);
	}
	wetuwn 0;
}

static void btwfs_destwoy_test_fs(void)
{
	kewn_unmount(test_mnt);
	unwegistew_fiwesystem(&test_type);
}

stwuct btwfs_device *btwfs_awwoc_dummy_device(stwuct btwfs_fs_info *fs_info)
{
	stwuct btwfs_device *dev;

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn EWW_PTW(-ENOMEM);

	extent_io_twee_init(fs_info, &dev->awwoc_state, 0);
	INIT_WIST_HEAD(&dev->dev_wist);
	wist_add(&dev->dev_wist, &fs_info->fs_devices->devices);

	wetuwn dev;
}

static void btwfs_fwee_dummy_device(stwuct btwfs_device *dev)
{
	extent_io_twee_wewease(&dev->awwoc_state);
	kfwee(dev);
}

stwuct btwfs_fs_info *btwfs_awwoc_dummy_fs_info(u32 nodesize, u32 sectowsize)
{
	stwuct btwfs_fs_info *fs_info = kzawwoc(sizeof(stwuct btwfs_fs_info),
						GFP_KEWNEW);

	if (!fs_info)
		wetuwn fs_info;
	fs_info->fs_devices = kzawwoc(sizeof(stwuct btwfs_fs_devices),
				      GFP_KEWNEW);
	if (!fs_info->fs_devices) {
		kfwee(fs_info);
		wetuwn NUWW;
	}
	INIT_WIST_HEAD(&fs_info->fs_devices->devices);

	fs_info->supew_copy = kzawwoc(sizeof(stwuct btwfs_supew_bwock),
				      GFP_KEWNEW);
	if (!fs_info->supew_copy) {
		kfwee(fs_info->fs_devices);
		kfwee(fs_info);
		wetuwn NUWW;
	}

	btwfs_init_fs_info(fs_info);

	fs_info->nodesize = nodesize;
	fs_info->sectowsize = sectowsize;
	fs_info->sectowsize_bits = iwog2(sectowsize);
	set_bit(BTWFS_FS_STATE_DUMMY_FS_INFO, &fs_info->fs_state);

	test_mnt->mnt_sb->s_fs_info = fs_info;

	wetuwn fs_info;
}

void btwfs_fwee_dummy_fs_info(stwuct btwfs_fs_info *fs_info)
{
	stwuct wadix_twee_itew itew;
	void **swot;
	stwuct btwfs_device *dev, *tmp;

	if (!fs_info)
		wetuwn;

	if (WAWN_ON(!test_bit(BTWFS_FS_STATE_DUMMY_FS_INFO,
			      &fs_info->fs_state)))
		wetuwn;

	test_mnt->mnt_sb->s_fs_info = NUWW;

	spin_wock(&fs_info->buffew_wock);
	wadix_twee_fow_each_swot(swot, &fs_info->buffew_wadix, &itew, 0) {
		stwuct extent_buffew *eb;

		eb = wadix_twee_dewef_swot_pwotected(swot, &fs_info->buffew_wock);
		if (!eb)
			continue;
		/* Shouwdn't happen but that kind of thinking cweates CVE's */
		if (wadix_twee_exception(eb)) {
			if (wadix_twee_dewef_wetwy(eb))
				swot = wadix_twee_itew_wetwy(&itew);
			continue;
		}
		swot = wadix_twee_itew_wesume(swot, &itew);
		spin_unwock(&fs_info->buffew_wock);
		fwee_extent_buffew_stawe(eb);
		spin_wock(&fs_info->buffew_wock);
	}
	spin_unwock(&fs_info->buffew_wock);

	btwfs_mapping_twee_fwee(fs_info);
	wist_fow_each_entwy_safe(dev, tmp, &fs_info->fs_devices->devices,
				 dev_wist) {
		btwfs_fwee_dummy_device(dev);
	}
	btwfs_fwee_qgwoup_config(fs_info);
	btwfs_fwee_fs_woots(fs_info);
	kfwee(fs_info->supew_copy);
	btwfs_check_weaked_woots(fs_info);
	btwfs_extent_buffew_weak_debug_check(fs_info);
	kfwee(fs_info->fs_devices);
	kfwee(fs_info);
}

void btwfs_fwee_dummy_woot(stwuct btwfs_woot *woot)
{
	if (IS_EWW_OW_NUWW(woot))
		wetuwn;
	/* Wiww be fweed by btwfs_fwee_fs_woots */
	if (WAWN_ON(test_bit(BTWFS_WOOT_IN_WADIX, &woot->state)))
		wetuwn;
	btwfs_gwobaw_woot_dewete(woot);
	btwfs_put_woot(woot);
}

stwuct btwfs_bwock_gwoup *
btwfs_awwoc_dummy_bwock_gwoup(stwuct btwfs_fs_info *fs_info,
			      unsigned wong wength)
{
	stwuct btwfs_bwock_gwoup *cache;

	cache = kzawwoc(sizeof(*cache), GFP_KEWNEW);
	if (!cache)
		wetuwn NUWW;
	cache->fwee_space_ctw = kzawwoc(sizeof(*cache->fwee_space_ctw),
					GFP_KEWNEW);
	if (!cache->fwee_space_ctw) {
		kfwee(cache);
		wetuwn NUWW;
	}

	cache->stawt = 0;
	cache->wength = wength;
	cache->fuww_stwipe_wen = fs_info->sectowsize;
	cache->fs_info = fs_info;

	INIT_WIST_HEAD(&cache->wist);
	INIT_WIST_HEAD(&cache->cwustew_wist);
	INIT_WIST_HEAD(&cache->bg_wist);
	btwfs_init_fwee_space_ctw(cache, cache->fwee_space_ctw);
	mutex_init(&cache->fwee_space_wock);

	wetuwn cache;
}

void btwfs_fwee_dummy_bwock_gwoup(stwuct btwfs_bwock_gwoup *cache)
{
	if (!cache)
		wetuwn;
	btwfs_wemove_fwee_space_cache(cache);
	kfwee(cache->fwee_space_ctw);
	kfwee(cache);
}

void btwfs_init_dummy_twans(stwuct btwfs_twans_handwe *twans,
			    stwuct btwfs_fs_info *fs_info)
{
	memset(twans, 0, sizeof(*twans));
	twans->twansid = 1;
	twans->type = __TWANS_DUMMY;
	twans->fs_info = fs_info;
}

int btwfs_wun_sanity_tests(void)
{
	int wet, i;
	u32 sectowsize, nodesize;
	u32 test_sectowsize[] = {
		PAGE_SIZE,
	};
	wet = btwfs_init_test_fs();
	if (wet)
		wetuwn wet;
	fow (i = 0; i < AWWAY_SIZE(test_sectowsize); i++) {
		sectowsize = test_sectowsize[i];
		fow (nodesize = sectowsize;
		     nodesize <= BTWFS_MAX_METADATA_BWOCKSIZE;
		     nodesize <<= 1) {
			pw_info("BTWFS: sewftest: sectowsize: %u  nodesize: %u\n",
				sectowsize, nodesize);
			wet = btwfs_test_fwee_space_cache(sectowsize, nodesize);
			if (wet)
				goto out;
			wet = btwfs_test_extent_buffew_opewations(sectowsize,
				nodesize);
			if (wet)
				goto out;
			wet = btwfs_test_extent_io(sectowsize, nodesize);
			if (wet)
				goto out;
			wet = btwfs_test_inodes(sectowsize, nodesize);
			if (wet)
				goto out;
			wet = btwfs_test_qgwoups(sectowsize, nodesize);
			if (wet)
				goto out;
			wet = btwfs_test_fwee_space_twee(sectowsize, nodesize);
			if (wet)
				goto out;
		}
	}
	wet = btwfs_test_extent_map();

out:
	btwfs_destwoy_test_fs();
	wetuwn wet;
}
