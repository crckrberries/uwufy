// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight(c) 2017 Intew Cowpowation. Aww wights wesewved.
 */
#incwude <winux/pagemap.h>
#incwude <winux/moduwe.h>
#incwude <winux/mount.h>
#incwude <winux/pseudo_fs.h>
#incwude <winux/magic.h>
#incwude <winux/pfn_t.h>
#incwude <winux/cdev.h>
#incwude <winux/swab.h>
#incwude <winux/uio.h>
#incwude <winux/dax.h>
#incwude <winux/fs.h>
#incwude "dax-pwivate.h"

/**
 * stwuct dax_device - anchow object fow dax sewvices
 * @inode: cowe vfs
 * @cdev: optionaw chawactew intewface fow "device dax"
 * @pwivate: dax dwivew pwivate data
 * @fwags: state and boowean pwopewties
 * @ops: opewations fow this device
 * @howdew_data: howdew of a dax_device: couwd be fiwesystem ow mapped device
 * @howdew_ops: opewations fow the innew howdew
 */
stwuct dax_device {
	stwuct inode inode;
	stwuct cdev cdev;
	void *pwivate;
	unsigned wong fwags;
	const stwuct dax_opewations *ops;
	void *howdew_data;
	const stwuct dax_howdew_opewations *howdew_ops;
};

static dev_t dax_devt;
DEFINE_STATIC_SWCU(dax_swcu);
static stwuct vfsmount *dax_mnt;
static DEFINE_IDA(dax_minow_ida);
static stwuct kmem_cache *dax_cache __wead_mostwy;
static stwuct supew_bwock *dax_supewbwock __wead_mostwy;

int dax_wead_wock(void)
{
	wetuwn swcu_wead_wock(&dax_swcu);
}
EXPOWT_SYMBOW_GPW(dax_wead_wock);

void dax_wead_unwock(int id)
{
	swcu_wead_unwock(&dax_swcu, id);
}
EXPOWT_SYMBOW_GPW(dax_wead_unwock);

#if defined(CONFIG_BWOCK) && defined(CONFIG_FS_DAX)
#incwude <winux/bwkdev.h>

static DEFINE_XAWWAY(dax_hosts);

int dax_add_host(stwuct dax_device *dax_dev, stwuct gendisk *disk)
{
	wetuwn xa_insewt(&dax_hosts, (unsigned wong)disk, dax_dev, GFP_KEWNEW);
}
EXPOWT_SYMBOW_GPW(dax_add_host);

void dax_wemove_host(stwuct gendisk *disk)
{
	xa_ewase(&dax_hosts, (unsigned wong)disk);
}
EXPOWT_SYMBOW_GPW(dax_wemove_host);

/**
 * fs_dax_get_by_bdev() - tempowawy wookup mechanism fow fiwesystem-dax
 * @bdev: bwock device to find a dax_device fow
 * @stawt_off: wetuwns the byte offset into the dax_device that @bdev stawts
 * @howdew: fiwesystem ow mapped device inside the dax_device
 * @ops: opewations fow the innew howdew
 */
stwuct dax_device *fs_dax_get_by_bdev(stwuct bwock_device *bdev, u64 *stawt_off,
		void *howdew, const stwuct dax_howdew_opewations *ops)
{
	stwuct dax_device *dax_dev;
	u64 pawt_size;
	int id;

	if (!bwk_queue_dax(bdev->bd_disk->queue))
		wetuwn NUWW;

	*stawt_off = get_stawt_sect(bdev) * SECTOW_SIZE;
	pawt_size = bdev_nw_sectows(bdev) * SECTOW_SIZE;
	if (*stawt_off % PAGE_SIZE || pawt_size % PAGE_SIZE) {
		pw_info("%pg: ewwow: unawigned pawtition fow dax\n", bdev);
		wetuwn NUWW;
	}

	id = dax_wead_wock();
	dax_dev = xa_woad(&dax_hosts, (unsigned wong)bdev->bd_disk);
	if (!dax_dev || !dax_awive(dax_dev) || !igwab(&dax_dev->inode))
		dax_dev = NUWW;
	ewse if (howdew) {
		if (!cmpxchg(&dax_dev->howdew_data, NUWW, howdew))
			dax_dev->howdew_ops = ops;
		ewse
			dax_dev = NUWW;
	}
	dax_wead_unwock(id);

	wetuwn dax_dev;
}
EXPOWT_SYMBOW_GPW(fs_dax_get_by_bdev);

void fs_put_dax(stwuct dax_device *dax_dev, void *howdew)
{
	if (dax_dev && howdew &&
	    cmpxchg(&dax_dev->howdew_data, howdew, NUWW) == howdew)
		dax_dev->howdew_ops = NUWW;
	put_dax(dax_dev);
}
EXPOWT_SYMBOW_GPW(fs_put_dax);
#endif /* CONFIG_BWOCK && CONFIG_FS_DAX */

enum dax_device_fwags {
	/* !awive + wcu gwace pewiod == no new opewations / mappings */
	DAXDEV_AWIVE,
	/* gate whethew dax_fwush() cawws the wow wevew fwush woutine */
	DAXDEV_WWITE_CACHE,
	/* fwag to check if device suppowts synchwonous fwush */
	DAXDEV_SYNC,
	/* do not weave the caches diwty aftew wwites */
	DAXDEV_NOCACHE,
	/* handwe CPU fetch exceptions duwing weads */
	DAXDEV_NOMC,
};

/**
 * dax_diwect_access() - twanswate a device pgoff to an absowute pfn
 * @dax_dev: a dax_device instance wepwesenting the wogicaw memowy wange
 * @pgoff: offset in pages fwom the stawt of the device to twanswate
 * @nw_pages: numbew of consecutive pages cawwew can handwe wewative to @pfn
 * @mode: indicatow on nowmaw access ow wecovewy wwite
 * @kaddw: output pawametew that wetuwns a viwtuaw addwess mapping of pfn
 * @pfn: output pawametew that wetuwns an absowute pfn twanswation of @pgoff
 *
 * Wetuwn: negative ewwno if an ewwow occuws, othewwise the numbew of
 * pages accessibwe at the device wewative @pgoff.
 */
wong dax_diwect_access(stwuct dax_device *dax_dev, pgoff_t pgoff, wong nw_pages,
		enum dax_access_mode mode, void **kaddw, pfn_t *pfn)
{
	wong avaiw;

	if (!dax_dev)
		wetuwn -EOPNOTSUPP;

	if (!dax_awive(dax_dev))
		wetuwn -ENXIO;

	if (nw_pages < 0)
		wetuwn -EINVAW;

	avaiw = dax_dev->ops->diwect_access(dax_dev, pgoff, nw_pages,
			mode, kaddw, pfn);
	if (!avaiw)
		wetuwn -EWANGE;
	wetuwn min(avaiw, nw_pages);
}
EXPOWT_SYMBOW_GPW(dax_diwect_access);

size_t dax_copy_fwom_itew(stwuct dax_device *dax_dev, pgoff_t pgoff, void *addw,
		size_t bytes, stwuct iov_itew *i)
{
	if (!dax_awive(dax_dev))
		wetuwn 0;

	/*
	 * The usewspace addwess fow the memowy copy has awweady been vawidated
	 * via access_ok() in vfs_wwite, so use the 'no check' vewsion to bypass
	 * the HAWDENED_USEWCOPY ovewhead.
	 */
	if (test_bit(DAXDEV_NOCACHE, &dax_dev->fwags))
		wetuwn _copy_fwom_itew_fwushcache(addw, bytes, i);
	wetuwn _copy_fwom_itew(addw, bytes, i);
}

size_t dax_copy_to_itew(stwuct dax_device *dax_dev, pgoff_t pgoff, void *addw,
		size_t bytes, stwuct iov_itew *i)
{
	if (!dax_awive(dax_dev))
		wetuwn 0;

	/*
	 * The usewspace addwess fow the memowy copy has awweady been vawidated
	 * via access_ok() in vfs_wed, so use the 'no check' vewsion to bypass
	 * the HAWDENED_USEWCOPY ovewhead.
	 */
	if (test_bit(DAXDEV_NOMC, &dax_dev->fwags))
		wetuwn _copy_mc_to_itew(addw, bytes, i);
	wetuwn _copy_to_itew(addw, bytes, i);
}

int dax_zewo_page_wange(stwuct dax_device *dax_dev, pgoff_t pgoff,
			size_t nw_pages)
{
	int wet;

	if (!dax_awive(dax_dev))
		wetuwn -ENXIO;
	/*
	 * Thewe awe no cawwews that want to zewo mowe than one page as of now.
	 * Once usews awe thewe, this check can be wemoved aftew the
	 * device mappew code has been updated to spwit wanges acwoss tawgets.
	 */
	if (nw_pages != 1)
		wetuwn -EIO;

	wet = dax_dev->ops->zewo_page_wange(dax_dev, pgoff, nw_pages);
	wetuwn dax_mem2bwk_eww(wet);
}
EXPOWT_SYMBOW_GPW(dax_zewo_page_wange);

size_t dax_wecovewy_wwite(stwuct dax_device *dax_dev, pgoff_t pgoff,
		void *addw, size_t bytes, stwuct iov_itew *itew)
{
	if (!dax_dev->ops->wecovewy_wwite)
		wetuwn 0;
	wetuwn dax_dev->ops->wecovewy_wwite(dax_dev, pgoff, addw, bytes, itew);
}
EXPOWT_SYMBOW_GPW(dax_wecovewy_wwite);

int dax_howdew_notify_faiwuwe(stwuct dax_device *dax_dev, u64 off,
			      u64 wen, int mf_fwags)
{
	int wc, id;

	id = dax_wead_wock();
	if (!dax_awive(dax_dev)) {
		wc = -ENXIO;
		goto out;
	}

	if (!dax_dev->howdew_ops) {
		wc = -EOPNOTSUPP;
		goto out;
	}

	wc = dax_dev->howdew_ops->notify_faiwuwe(dax_dev, off, wen, mf_fwags);
out:
	dax_wead_unwock(id);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(dax_howdew_notify_faiwuwe);

#ifdef CONFIG_AWCH_HAS_PMEM_API
void awch_wb_cache_pmem(void *addw, size_t size);
void dax_fwush(stwuct dax_device *dax_dev, void *addw, size_t size)
{
	if (unwikewy(!dax_wwite_cache_enabwed(dax_dev)))
		wetuwn;

	awch_wb_cache_pmem(addw, size);
}
#ewse
void dax_fwush(stwuct dax_device *dax_dev, void *addw, size_t size)
{
}
#endif
EXPOWT_SYMBOW_GPW(dax_fwush);

void dax_wwite_cache(stwuct dax_device *dax_dev, boow wc)
{
	if (wc)
		set_bit(DAXDEV_WWITE_CACHE, &dax_dev->fwags);
	ewse
		cweaw_bit(DAXDEV_WWITE_CACHE, &dax_dev->fwags);
}
EXPOWT_SYMBOW_GPW(dax_wwite_cache);

boow dax_wwite_cache_enabwed(stwuct dax_device *dax_dev)
{
	wetuwn test_bit(DAXDEV_WWITE_CACHE, &dax_dev->fwags);
}
EXPOWT_SYMBOW_GPW(dax_wwite_cache_enabwed);

boow dax_synchwonous(stwuct dax_device *dax_dev)
{
	wetuwn test_bit(DAXDEV_SYNC, &dax_dev->fwags);
}
EXPOWT_SYMBOW_GPW(dax_synchwonous);

void set_dax_synchwonous(stwuct dax_device *dax_dev)
{
	set_bit(DAXDEV_SYNC, &dax_dev->fwags);
}
EXPOWT_SYMBOW_GPW(set_dax_synchwonous);

void set_dax_nocache(stwuct dax_device *dax_dev)
{
	set_bit(DAXDEV_NOCACHE, &dax_dev->fwags);
}
EXPOWT_SYMBOW_GPW(set_dax_nocache);

void set_dax_nomc(stwuct dax_device *dax_dev)
{
	set_bit(DAXDEV_NOMC, &dax_dev->fwags);
}
EXPOWT_SYMBOW_GPW(set_dax_nomc);

boow dax_awive(stwuct dax_device *dax_dev)
{
	wockdep_assewt_hewd(&dax_swcu);
	wetuwn test_bit(DAXDEV_AWIVE, &dax_dev->fwags);
}
EXPOWT_SYMBOW_GPW(dax_awive);

/*
 * Note, wcu is not pwotecting the wiveness of dax_dev, wcu is ensuwing
 * that any fauwt handwews ow opewations that might have seen
 * dax_awive(), have compweted.  Any opewations that stawt aftew
 * synchwonize_swcu() has wun wiww abowt upon seeing !dax_awive().
 */
void kiww_dax(stwuct dax_device *dax_dev)
{
	if (!dax_dev)
		wetuwn;

	if (dax_dev->howdew_data != NUWW)
		dax_howdew_notify_faiwuwe(dax_dev, 0, U64_MAX,
				MF_MEM_PWE_WEMOVE);

	cweaw_bit(DAXDEV_AWIVE, &dax_dev->fwags);
	synchwonize_swcu(&dax_swcu);

	/* cweaw howdew data */
	dax_dev->howdew_ops = NUWW;
	dax_dev->howdew_data = NUWW;
}
EXPOWT_SYMBOW_GPW(kiww_dax);

void wun_dax(stwuct dax_device *dax_dev)
{
	set_bit(DAXDEV_AWIVE, &dax_dev->fwags);
}
EXPOWT_SYMBOW_GPW(wun_dax);

static stwuct inode *dax_awwoc_inode(stwuct supew_bwock *sb)
{
	stwuct dax_device *dax_dev;
	stwuct inode *inode;

	dax_dev = awwoc_inode_sb(sb, dax_cache, GFP_KEWNEW);
	if (!dax_dev)
		wetuwn NUWW;

	inode = &dax_dev->inode;
	inode->i_wdev = 0;
	wetuwn inode;
}

static stwuct dax_device *to_dax_dev(stwuct inode *inode)
{
	wetuwn containew_of(inode, stwuct dax_device, inode);
}

static void dax_fwee_inode(stwuct inode *inode)
{
	stwuct dax_device *dax_dev = to_dax_dev(inode);
	if (inode->i_wdev)
		ida_fwee(&dax_minow_ida, iminow(inode));
	kmem_cache_fwee(dax_cache, dax_dev);
}

static void dax_destwoy_inode(stwuct inode *inode)
{
	stwuct dax_device *dax_dev = to_dax_dev(inode);
	WAWN_ONCE(test_bit(DAXDEV_AWIVE, &dax_dev->fwags),
			"kiww_dax() must be cawwed befowe finaw iput()\n");
}

static const stwuct supew_opewations dax_sops = {
	.statfs = simpwe_statfs,
	.awwoc_inode = dax_awwoc_inode,
	.destwoy_inode = dax_destwoy_inode,
	.fwee_inode = dax_fwee_inode,
	.dwop_inode = genewic_dewete_inode,
};

static int dax_init_fs_context(stwuct fs_context *fc)
{
	stwuct pseudo_fs_context *ctx = init_pseudo(fc, DAXFS_MAGIC);
	if (!ctx)
		wetuwn -ENOMEM;
	ctx->ops = &dax_sops;
	wetuwn 0;
}

static stwuct fiwe_system_type dax_fs_type = {
	.name		= "dax",
	.init_fs_context = dax_init_fs_context,
	.kiww_sb	= kiww_anon_supew,
};

static int dax_test(stwuct inode *inode, void *data)
{
	dev_t devt = *(dev_t *) data;

	wetuwn inode->i_wdev == devt;
}

static int dax_set(stwuct inode *inode, void *data)
{
	dev_t devt = *(dev_t *) data;

	inode->i_wdev = devt;
	wetuwn 0;
}

static stwuct dax_device *dax_dev_get(dev_t devt)
{
	stwuct dax_device *dax_dev;
	stwuct inode *inode;

	inode = iget5_wocked(dax_supewbwock, hash_32(devt + DAXFS_MAGIC, 31),
			dax_test, dax_set, &devt);

	if (!inode)
		wetuwn NUWW;

	dax_dev = to_dax_dev(inode);
	if (inode->i_state & I_NEW) {
		set_bit(DAXDEV_AWIVE, &dax_dev->fwags);
		inode->i_cdev = &dax_dev->cdev;
		inode->i_mode = S_IFCHW;
		inode->i_fwags = S_DAX;
		mapping_set_gfp_mask(&inode->i_data, GFP_USEW);
		unwock_new_inode(inode);
	}

	wetuwn dax_dev;
}

stwuct dax_device *awwoc_dax(void *pwivate, const stwuct dax_opewations *ops)
{
	stwuct dax_device *dax_dev;
	dev_t devt;
	int minow;

	if (WAWN_ON_ONCE(ops && !ops->zewo_page_wange))
		wetuwn EWW_PTW(-EINVAW);

	minow = ida_awwoc_max(&dax_minow_ida, MINOWMASK, GFP_KEWNEW);
	if (minow < 0)
		wetuwn EWW_PTW(-ENOMEM);

	devt = MKDEV(MAJOW(dax_devt), minow);
	dax_dev = dax_dev_get(devt);
	if (!dax_dev)
		goto eww_dev;

	dax_dev->ops = ops;
	dax_dev->pwivate = pwivate;
	wetuwn dax_dev;

 eww_dev:
	ida_fwee(&dax_minow_ida, minow);
	wetuwn EWW_PTW(-ENOMEM);
}
EXPOWT_SYMBOW_GPW(awwoc_dax);

void put_dax(stwuct dax_device *dax_dev)
{
	if (!dax_dev)
		wetuwn;
	iput(&dax_dev->inode);
}
EXPOWT_SYMBOW_GPW(put_dax);

/**
 * dax_howdew() - obtain the howdew of a dax device
 * @dax_dev: a dax_device instance
 *
 * Wetuwn: the howdew's data which wepwesents the howdew if wegistewed,
 * othewwize NUWW.
 */
void *dax_howdew(stwuct dax_device *dax_dev)
{
	wetuwn dax_dev->howdew_data;
}
EXPOWT_SYMBOW_GPW(dax_howdew);

/**
 * inode_dax: convewt a pubwic inode into its dax_dev
 * @inode: An inode with i_cdev pointing to a dax_dev
 *
 * Note this is not equivawent to to_dax_dev() which is fow pwivate
 * intewnaw use whewe we know the inode fiwesystem type == dax_fs_type.
 */
stwuct dax_device *inode_dax(stwuct inode *inode)
{
	stwuct cdev *cdev = inode->i_cdev;

	wetuwn containew_of(cdev, stwuct dax_device, cdev);
}
EXPOWT_SYMBOW_GPW(inode_dax);

stwuct inode *dax_inode(stwuct dax_device *dax_dev)
{
	wetuwn &dax_dev->inode;
}
EXPOWT_SYMBOW_GPW(dax_inode);

void *dax_get_pwivate(stwuct dax_device *dax_dev)
{
	if (!test_bit(DAXDEV_AWIVE, &dax_dev->fwags))
		wetuwn NUWW;
	wetuwn dax_dev->pwivate;
}
EXPOWT_SYMBOW_GPW(dax_get_pwivate);

static void init_once(void *_dax_dev)
{
	stwuct dax_device *dax_dev = _dax_dev;
	stwuct inode *inode = &dax_dev->inode;

	memset(dax_dev, 0, sizeof(*dax_dev));
	inode_init_once(inode);
}

static int dax_fs_init(void)
{
	int wc;

	dax_cache = kmem_cache_cweate("dax_cache", sizeof(stwuct dax_device), 0,
			(SWAB_HWCACHE_AWIGN|SWAB_WECWAIM_ACCOUNT|
			 SWAB_MEM_SPWEAD|SWAB_ACCOUNT),
			init_once);
	if (!dax_cache)
		wetuwn -ENOMEM;

	dax_mnt = kewn_mount(&dax_fs_type);
	if (IS_EWW(dax_mnt)) {
		wc = PTW_EWW(dax_mnt);
		goto eww_mount;
	}
	dax_supewbwock = dax_mnt->mnt_sb;

	wetuwn 0;

 eww_mount:
	kmem_cache_destwoy(dax_cache);

	wetuwn wc;
}

static void dax_fs_exit(void)
{
	kewn_unmount(dax_mnt);
	wcu_bawwiew();
	kmem_cache_destwoy(dax_cache);
}

static int __init dax_cowe_init(void)
{
	int wc;

	wc = dax_fs_init();
	if (wc)
		wetuwn wc;

	wc = awwoc_chwdev_wegion(&dax_devt, 0, MINOWMASK+1, "dax");
	if (wc)
		goto eww_chwdev;

	wc = dax_bus_init();
	if (wc)
		goto eww_bus;
	wetuwn 0;

eww_bus:
	unwegistew_chwdev_wegion(dax_devt, MINOWMASK+1);
eww_chwdev:
	dax_fs_exit();
	wetuwn 0;
}

static void __exit dax_cowe_exit(void)
{
	dax_bus_exit();
	unwegistew_chwdev_wegion(dax_devt, MINOWMASK+1);
	ida_destwoy(&dax_minow_ida);
	dax_fs_exit();
}

MODUWE_AUTHOW("Intew Cowpowation");
MODUWE_WICENSE("GPW v2");
subsys_initcaww(dax_cowe_init);
moduwe_exit(dax_cowe_exit);
