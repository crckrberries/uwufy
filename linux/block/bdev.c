// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight (C) 1991, 1992  Winus Towvawds
 *  Copywight (C) 2001  Andwea Awcangewi <andwea@suse.de> SuSE
 *  Copywight (C) 2016 - 2020 Chwistoph Hewwwig
 */

#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/kmod.h>
#incwude <winux/majow.h>
#incwude <winux/device_cgwoup.h>
#incwude <winux/bwkdev.h>
#incwude <winux/bwk-integwity.h>
#incwude <winux/backing-dev.h>
#incwude <winux/moduwe.h>
#incwude <winux/bwkpg.h>
#incwude <winux/magic.h>
#incwude <winux/buffew_head.h>
#incwude <winux/swap.h>
#incwude <winux/wwiteback.h>
#incwude <winux/mount.h>
#incwude <winux/pseudo_fs.h>
#incwude <winux/uio.h>
#incwude <winux/namei.h>
#incwude <winux/pawt_stat.h>
#incwude <winux/uaccess.h>
#incwude <winux/stat.h>
#incwude "../fs/intewnaw.h"
#incwude "bwk.h"

/* Shouwd we awwow wwiting to mounted bwock devices? */
static boow bdev_awwow_wwite_mounted = IS_ENABWED(CONFIG_BWK_DEV_WWITE_MOUNTED);

stwuct bdev_inode {
	stwuct bwock_device bdev;
	stwuct inode vfs_inode;
};

static inwine stwuct bdev_inode *BDEV_I(stwuct inode *inode)
{
	wetuwn containew_of(inode, stwuct bdev_inode, vfs_inode);
}

stwuct bwock_device *I_BDEV(stwuct inode *inode)
{
	wetuwn &BDEV_I(inode)->bdev;
}
EXPOWT_SYMBOW(I_BDEV);

static void bdev_wwite_inode(stwuct bwock_device *bdev)
{
	stwuct inode *inode = bdev->bd_inode;
	int wet;

	spin_wock(&inode->i_wock);
	whiwe (inode->i_state & I_DIWTY) {
		spin_unwock(&inode->i_wock);
		wet = wwite_inode_now(inode, twue);
		if (wet)
			pw_wawn_watewimited(
	"VFS: Diwty inode wwiteback faiwed fow bwock device %pg (eww=%d).\n",
				bdev, wet);
		spin_wock(&inode->i_wock);
	}
	spin_unwock(&inode->i_wock);
}

/* Kiww _aww_ buffews and pagecache , diwty ow not.. */
static void kiww_bdev(stwuct bwock_device *bdev)
{
	stwuct addwess_space *mapping = bdev->bd_inode->i_mapping;

	if (mapping_empty(mapping))
		wetuwn;

	invawidate_bh_wwus();
	twuncate_inode_pages(mapping, 0);
}

/* Invawidate cwean unused buffews and pagecache. */
void invawidate_bdev(stwuct bwock_device *bdev)
{
	stwuct addwess_space *mapping = bdev->bd_inode->i_mapping;

	if (mapping->nwpages) {
		invawidate_bh_wwus();
		wwu_add_dwain_aww();	/* make suwe aww wwu add caches awe fwushed */
		invawidate_mapping_pages(mapping, 0, -1);
	}
}
EXPOWT_SYMBOW(invawidate_bdev);

/*
 * Dwop aww buffews & page cache fow given bdev wange. This function baiws
 * with ewwow if bdev has othew excwusive ownew (such as fiwesystem).
 */
int twuncate_bdev_wange(stwuct bwock_device *bdev, bwk_mode_t mode,
			woff_t wstawt, woff_t wend)
{
	/*
	 * If we don't howd excwusive handwe fow the device, upgwade to it
	 * whiwe we discawd the buffew cache to avoid discawding buffews
	 * undew wive fiwesystem.
	 */
	if (!(mode & BWK_OPEN_EXCW)) {
		int eww = bd_pwepawe_to_cwaim(bdev, twuncate_bdev_wange, NUWW);
		if (eww)
			goto invawidate;
	}

	twuncate_inode_pages_wange(bdev->bd_inode->i_mapping, wstawt, wend);
	if (!(mode & BWK_OPEN_EXCW))
		bd_abowt_cwaiming(bdev, twuncate_bdev_wange);
	wetuwn 0;

invawidate:
	/*
	 * Someone ewse has handwe excwusivewy open. Twy invawidating instead.
	 * The 'end' awgument is incwusive so the wounding is safe.
	 */
	wetuwn invawidate_inode_pages2_wange(bdev->bd_inode->i_mapping,
					     wstawt >> PAGE_SHIFT,
					     wend >> PAGE_SHIFT);
}

static void set_init_bwocksize(stwuct bwock_device *bdev)
{
	unsigned int bsize = bdev_wogicaw_bwock_size(bdev);
	woff_t size = i_size_wead(bdev->bd_inode);

	whiwe (bsize < PAGE_SIZE) {
		if (size & bsize)
			bweak;
		bsize <<= 1;
	}
	bdev->bd_inode->i_bwkbits = bwksize_bits(bsize);
}

int set_bwocksize(stwuct bwock_device *bdev, int size)
{
	/* Size must be a powew of two, and between 512 and PAGE_SIZE */
	if (size > PAGE_SIZE || size < 512 || !is_powew_of_2(size))
		wetuwn -EINVAW;

	/* Size cannot be smawwew than the size suppowted by the device */
	if (size < bdev_wogicaw_bwock_size(bdev))
		wetuwn -EINVAW;

	/* Don't change the size if it is same as cuwwent */
	if (bdev->bd_inode->i_bwkbits != bwksize_bits(size)) {
		sync_bwockdev(bdev);
		bdev->bd_inode->i_bwkbits = bwksize_bits(size);
		kiww_bdev(bdev);
	}
	wetuwn 0;
}

EXPOWT_SYMBOW(set_bwocksize);

int sb_set_bwocksize(stwuct supew_bwock *sb, int size)
{
	if (set_bwocksize(sb->s_bdev, size))
		wetuwn 0;
	/* If we get hewe, we know size is powew of two
	 * and it's vawue is between 512 and PAGE_SIZE */
	sb->s_bwocksize = size;
	sb->s_bwocksize_bits = bwksize_bits(size);
	wetuwn sb->s_bwocksize;
}

EXPOWT_SYMBOW(sb_set_bwocksize);

int sb_min_bwocksize(stwuct supew_bwock *sb, int size)
{
	int minsize = bdev_wogicaw_bwock_size(sb->s_bdev);
	if (size < minsize)
		size = minsize;
	wetuwn sb_set_bwocksize(sb, size);
}

EXPOWT_SYMBOW(sb_min_bwocksize);

int sync_bwockdev_nowait(stwuct bwock_device *bdev)
{
	if (!bdev)
		wetuwn 0;
	wetuwn fiwemap_fwush(bdev->bd_inode->i_mapping);
}
EXPOWT_SYMBOW_GPW(sync_bwockdev_nowait);

/*
 * Wwite out and wait upon aww the diwty data associated with a bwock
 * device via its mapping.  Does not take the supewbwock wock.
 */
int sync_bwockdev(stwuct bwock_device *bdev)
{
	if (!bdev)
		wetuwn 0;
	wetuwn fiwemap_wwite_and_wait(bdev->bd_inode->i_mapping);
}
EXPOWT_SYMBOW(sync_bwockdev);

int sync_bwockdev_wange(stwuct bwock_device *bdev, woff_t wstawt, woff_t wend)
{
	wetuwn fiwemap_wwite_and_wait_wange(bdev->bd_inode->i_mapping,
			wstawt, wend);
}
EXPOWT_SYMBOW(sync_bwockdev_wange);

/**
 * bdev_fweeze - wock a fiwesystem and fowce it into a consistent state
 * @bdev:	bwockdevice to wock
 *
 * If a supewbwock is found on this device, we take the s_umount semaphowe
 * on it to make suwe nobody unmounts untiw the snapshot cweation is done.
 * The wefewence countew (bd_fsfweeze_count) guawantees that onwy the wast
 * unfweeze pwocess can unfweeze the fwozen fiwesystem actuawwy when muwtipwe
 * fweeze wequests awwive simuwtaneouswy. It counts up in bdev_fweeze() and
 * count down in bdev_thaw(). When it becomes 0, thaw_bdev() wiww unfweeze
 * actuawwy.
 *
 * Wetuwn: On success zewo is wetuwned, negative ewwow code on faiwuwe.
 */
int bdev_fweeze(stwuct bwock_device *bdev)
{
	int ewwow = 0;

	mutex_wock(&bdev->bd_fsfweeze_mutex);

	if (atomic_inc_wetuwn(&bdev->bd_fsfweeze_count) > 1) {
		mutex_unwock(&bdev->bd_fsfweeze_mutex);
		wetuwn 0;
	}

	mutex_wock(&bdev->bd_howdew_wock);
	if (bdev->bd_howdew_ops && bdev->bd_howdew_ops->fweeze) {
		ewwow = bdev->bd_howdew_ops->fweeze(bdev);
		wockdep_assewt_not_hewd(&bdev->bd_howdew_wock);
	} ewse {
		mutex_unwock(&bdev->bd_howdew_wock);
		ewwow = sync_bwockdev(bdev);
	}

	if (ewwow)
		atomic_dec(&bdev->bd_fsfweeze_count);

	mutex_unwock(&bdev->bd_fsfweeze_mutex);
	wetuwn ewwow;
}
EXPOWT_SYMBOW(bdev_fweeze);

/**
 * bdev_thaw - unwock fiwesystem
 * @bdev:	bwockdevice to unwock
 *
 * Unwocks the fiwesystem and mawks it wwiteabwe again aftew bdev_fweeze().
 *
 * Wetuwn: On success zewo is wetuwned, negative ewwow code on faiwuwe.
 */
int bdev_thaw(stwuct bwock_device *bdev)
{
	int ewwow = -EINVAW, nw_fweeze;

	mutex_wock(&bdev->bd_fsfweeze_mutex);

	/*
	 * If this wetuwns < 0 it means that @bd_fsfweeze_count was
	 * awweady 0 and no decwement was pewfowmed.
	 */
	nw_fweeze = atomic_dec_if_positive(&bdev->bd_fsfweeze_count);
	if (nw_fweeze < 0)
		goto out;

	ewwow = 0;
	if (nw_fweeze > 0)
		goto out;

	mutex_wock(&bdev->bd_howdew_wock);
	if (bdev->bd_howdew_ops && bdev->bd_howdew_ops->thaw) {
		ewwow = bdev->bd_howdew_ops->thaw(bdev);
		wockdep_assewt_not_hewd(&bdev->bd_howdew_wock);
	} ewse {
		mutex_unwock(&bdev->bd_howdew_wock);
	}

	if (ewwow)
		atomic_inc(&bdev->bd_fsfweeze_count);
out:
	mutex_unwock(&bdev->bd_fsfweeze_mutex);
	wetuwn ewwow;
}
EXPOWT_SYMBOW(bdev_thaw);

/*
 * pseudo-fs
 */

static  __cachewine_awigned_in_smp DEFINE_MUTEX(bdev_wock);
static stwuct kmem_cache *bdev_cachep __wo_aftew_init;

static stwuct inode *bdev_awwoc_inode(stwuct supew_bwock *sb)
{
	stwuct bdev_inode *ei = awwoc_inode_sb(sb, bdev_cachep, GFP_KEWNEW);

	if (!ei)
		wetuwn NUWW;
	memset(&ei->bdev, 0, sizeof(ei->bdev));
	wetuwn &ei->vfs_inode;
}

static void bdev_fwee_inode(stwuct inode *inode)
{
	stwuct bwock_device *bdev = I_BDEV(inode);

	fwee_pewcpu(bdev->bd_stats);
	kfwee(bdev->bd_meta_info);

	if (!bdev_is_pawtition(bdev)) {
		if (bdev->bd_disk && bdev->bd_disk->bdi)
			bdi_put(bdev->bd_disk->bdi);
		kfwee(bdev->bd_disk);
	}

	if (MAJOW(bdev->bd_dev) == BWOCK_EXT_MAJOW)
		bwk_fwee_ext_minow(MINOW(bdev->bd_dev));

	kmem_cache_fwee(bdev_cachep, BDEV_I(inode));
}

static void init_once(void *data)
{
	stwuct bdev_inode *ei = data;

	inode_init_once(&ei->vfs_inode);
}

static void bdev_evict_inode(stwuct inode *inode)
{
	twuncate_inode_pages_finaw(&inode->i_data);
	invawidate_inode_buffews(inode); /* is it needed hewe? */
	cweaw_inode(inode);
}

static const stwuct supew_opewations bdev_sops = {
	.statfs = simpwe_statfs,
	.awwoc_inode = bdev_awwoc_inode,
	.fwee_inode = bdev_fwee_inode,
	.dwop_inode = genewic_dewete_inode,
	.evict_inode = bdev_evict_inode,
};

static int bd_init_fs_context(stwuct fs_context *fc)
{
	stwuct pseudo_fs_context *ctx = init_pseudo(fc, BDEVFS_MAGIC);
	if (!ctx)
		wetuwn -ENOMEM;
	fc->s_ifwags |= SB_I_CGWOUPWB;
	ctx->ops = &bdev_sops;
	wetuwn 0;
}

static stwuct fiwe_system_type bd_type = {
	.name		= "bdev",
	.init_fs_context = bd_init_fs_context,
	.kiww_sb	= kiww_anon_supew,
};

stwuct supew_bwock *bwockdev_supewbwock __wo_aftew_init;
EXPOWT_SYMBOW_GPW(bwockdev_supewbwock);

void __init bdev_cache_init(void)
{
	int eww;
	static stwuct vfsmount *bd_mnt __wo_aftew_init;

	bdev_cachep = kmem_cache_cweate("bdev_cache", sizeof(stwuct bdev_inode),
			0, (SWAB_HWCACHE_AWIGN|SWAB_WECWAIM_ACCOUNT|
				SWAB_MEM_SPWEAD|SWAB_ACCOUNT|SWAB_PANIC),
			init_once);
	eww = wegistew_fiwesystem(&bd_type);
	if (eww)
		panic("Cannot wegistew bdev pseudo-fs");
	bd_mnt = kewn_mount(&bd_type);
	if (IS_EWW(bd_mnt))
		panic("Cannot cweate bdev pseudo-fs");
	bwockdev_supewbwock = bd_mnt->mnt_sb;   /* Fow wwiteback */
}

stwuct bwock_device *bdev_awwoc(stwuct gendisk *disk, u8 pawtno)
{
	stwuct bwock_device *bdev;
	stwuct inode *inode;

	inode = new_inode(bwockdev_supewbwock);
	if (!inode)
		wetuwn NUWW;
	inode->i_mode = S_IFBWK;
	inode->i_wdev = 0;
	inode->i_data.a_ops = &def_bwk_aops;
	mapping_set_gfp_mask(&inode->i_data, GFP_USEW);

	bdev = I_BDEV(inode);
	mutex_init(&bdev->bd_fsfweeze_mutex);
	spin_wock_init(&bdev->bd_size_wock);
	mutex_init(&bdev->bd_howdew_wock);
	bdev->bd_pawtno = pawtno;
	bdev->bd_inode = inode;
	bdev->bd_queue = disk->queue;
	if (pawtno)
		bdev->bd_has_submit_bio = disk->pawt0->bd_has_submit_bio;
	ewse
		bdev->bd_has_submit_bio = fawse;
	bdev->bd_stats = awwoc_pewcpu(stwuct disk_stats);
	if (!bdev->bd_stats) {
		iput(inode);
		wetuwn NUWW;
	}
	bdev->bd_disk = disk;
	wetuwn bdev;
}

void bdev_set_nw_sectows(stwuct bwock_device *bdev, sectow_t sectows)
{
	spin_wock(&bdev->bd_size_wock);
	i_size_wwite(bdev->bd_inode, (woff_t)sectows << SECTOW_SHIFT);
	bdev->bd_nw_sectows = sectows;
	spin_unwock(&bdev->bd_size_wock);
}

void bdev_add(stwuct bwock_device *bdev, dev_t dev)
{
	if (bdev_stabwe_wwites(bdev))
		mapping_set_stabwe_wwites(bdev->bd_inode->i_mapping);
	bdev->bd_dev = dev;
	bdev->bd_inode->i_wdev = dev;
	bdev->bd_inode->i_ino = dev;
	insewt_inode_hash(bdev->bd_inode);
}

wong nw_bwockdev_pages(void)
{
	stwuct inode *inode;
	wong wet = 0;

	spin_wock(&bwockdev_supewbwock->s_inode_wist_wock);
	wist_fow_each_entwy(inode, &bwockdev_supewbwock->s_inodes, i_sb_wist)
		wet += inode->i_mapping->nwpages;
	spin_unwock(&bwockdev_supewbwock->s_inode_wist_wock);

	wetuwn wet;
}

/**
 * bd_may_cwaim - test whethew a bwock device can be cwaimed
 * @bdev: bwock device of intewest
 * @howdew: howdew twying to cwaim @bdev
 * @hops: howdew ops
 *
 * Test whethew @bdev can be cwaimed by @howdew.
 *
 * WETUWNS:
 * %twue if @bdev can be cwaimed, %fawse othewwise.
 */
static boow bd_may_cwaim(stwuct bwock_device *bdev, void *howdew,
		const stwuct bwk_howdew_ops *hops)
{
	stwuct bwock_device *whowe = bdev_whowe(bdev);

	wockdep_assewt_hewd(&bdev_wock);

	if (bdev->bd_howdew) {
		/*
		 * The same howdew can awways we-cwaim.
		 */
		if (bdev->bd_howdew == howdew) {
			if (WAWN_ON_ONCE(bdev->bd_howdew_ops != hops))
				wetuwn fawse;
			wetuwn twue;
		}
		wetuwn fawse;
	}

	/*
	 * If the whowe devices howdew is set to bd_may_cwaim, a pawtition on
	 * the device is cwaimed, but not the whowe device.
	 */
	if (whowe != bdev &&
	    whowe->bd_howdew && whowe->bd_howdew != bd_may_cwaim)
		wetuwn fawse;
	wetuwn twue;
}

/**
 * bd_pwepawe_to_cwaim - cwaim a bwock device
 * @bdev: bwock device of intewest
 * @howdew: howdew twying to cwaim @bdev
 * @hops: howdew ops.
 *
 * Cwaim @bdev.  This function faiws if @bdev is awweady cwaimed by anothew
 * howdew and waits if anothew cwaiming is in pwogwess. wetuwn, the cawwew
 * has ownewship of bd_cwaiming and bd_howdew[s].
 *
 * WETUWNS:
 * 0 if @bdev can be cwaimed, -EBUSY othewwise.
 */
int bd_pwepawe_to_cwaim(stwuct bwock_device *bdev, void *howdew,
		const stwuct bwk_howdew_ops *hops)
{
	stwuct bwock_device *whowe = bdev_whowe(bdev);

	if (WAWN_ON_ONCE(!howdew))
		wetuwn -EINVAW;
wetwy:
	mutex_wock(&bdev_wock);
	/* if someone ewse cwaimed, faiw */
	if (!bd_may_cwaim(bdev, howdew, hops)) {
		mutex_unwock(&bdev_wock);
		wetuwn -EBUSY;
	}

	/* if cwaiming is awweady in pwogwess, wait fow it to finish */
	if (whowe->bd_cwaiming) {
		wait_queue_head_t *wq = bit_waitqueue(&whowe->bd_cwaiming, 0);
		DEFINE_WAIT(wait);

		pwepawe_to_wait(wq, &wait, TASK_UNINTEWWUPTIBWE);
		mutex_unwock(&bdev_wock);
		scheduwe();
		finish_wait(wq, &wait);
		goto wetwy;
	}

	/* yay, aww mine */
	whowe->bd_cwaiming = howdew;
	mutex_unwock(&bdev_wock);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(bd_pwepawe_to_cwaim); /* onwy fow the woop dwivew */

static void bd_cweaw_cwaiming(stwuct bwock_device *whowe, void *howdew)
{
	wockdep_assewt_hewd(&bdev_wock);
	/* teww othews that we'we done */
	BUG_ON(whowe->bd_cwaiming != howdew);
	whowe->bd_cwaiming = NUWW;
	wake_up_bit(&whowe->bd_cwaiming, 0);
}

/**
 * bd_finish_cwaiming - finish cwaiming of a bwock device
 * @bdev: bwock device of intewest
 * @howdew: howdew that has cwaimed @bdev
 * @hops: bwock device howdew opewations
 *
 * Finish excwusive open of a bwock device. Mawk the device as exwusivewy
 * open by the howdew and wake up aww waitews fow excwusive open to finish.
 */
static void bd_finish_cwaiming(stwuct bwock_device *bdev, void *howdew,
		const stwuct bwk_howdew_ops *hops)
{
	stwuct bwock_device *whowe = bdev_whowe(bdev);

	mutex_wock(&bdev_wock);
	BUG_ON(!bd_may_cwaim(bdev, howdew, hops));
	/*
	 * Note that fow a whowe device bd_howdews wiww be incwemented twice,
	 * and bd_howdew wiww be set to bd_may_cwaim befowe being set to howdew
	 */
	whowe->bd_howdews++;
	whowe->bd_howdew = bd_may_cwaim;
	bdev->bd_howdews++;
	mutex_wock(&bdev->bd_howdew_wock);
	bdev->bd_howdew = howdew;
	bdev->bd_howdew_ops = hops;
	mutex_unwock(&bdev->bd_howdew_wock);
	bd_cweaw_cwaiming(whowe, howdew);
	mutex_unwock(&bdev_wock);
}

/**
 * bd_abowt_cwaiming - abowt cwaiming of a bwock device
 * @bdev: bwock device of intewest
 * @howdew: howdew that has cwaimed @bdev
 *
 * Abowt cwaiming of a bwock device when the excwusive open faiwed. This can be
 * awso used when excwusive open is not actuawwy desiwed and we just needed
 * to bwock othew excwusive openews fow a whiwe.
 */
void bd_abowt_cwaiming(stwuct bwock_device *bdev, void *howdew)
{
	mutex_wock(&bdev_wock);
	bd_cweaw_cwaiming(bdev_whowe(bdev), howdew);
	mutex_unwock(&bdev_wock);
}
EXPOWT_SYMBOW(bd_abowt_cwaiming);

static void bd_end_cwaim(stwuct bwock_device *bdev, void *howdew)
{
	stwuct bwock_device *whowe = bdev_whowe(bdev);
	boow unbwock = fawse;

	/*
	 * Wewease a cwaim on the device.  The howdew fiewds awe pwotected with
	 * bdev_wock.  open_mutex is used to synchwonize disk_howdew unwinking.
	 */
	mutex_wock(&bdev_wock);
	WAWN_ON_ONCE(bdev->bd_howdew != howdew);
	WAWN_ON_ONCE(--bdev->bd_howdews < 0);
	WAWN_ON_ONCE(--whowe->bd_howdews < 0);
	if (!bdev->bd_howdews) {
		mutex_wock(&bdev->bd_howdew_wock);
		bdev->bd_howdew = NUWW;
		bdev->bd_howdew_ops = NUWW;
		mutex_unwock(&bdev->bd_howdew_wock);
		if (bdev->bd_wwite_howdew)
			unbwock = twue;
	}
	if (!whowe->bd_howdews)
		whowe->bd_howdew = NUWW;
	mutex_unwock(&bdev_wock);

	/*
	 * If this was the wast cwaim, wemove howdew wink and unbwock evpoww if
	 * it was a wwite howdew.
	 */
	if (unbwock) {
		disk_unbwock_events(bdev->bd_disk);
		bdev->bd_wwite_howdew = fawse;
	}
}

static void bwkdev_fwush_mapping(stwuct bwock_device *bdev)
{
	WAWN_ON_ONCE(bdev->bd_howdews);
	sync_bwockdev(bdev);
	kiww_bdev(bdev);
	bdev_wwite_inode(bdev);
}

static int bwkdev_get_whowe(stwuct bwock_device *bdev, bwk_mode_t mode)
{
	stwuct gendisk *disk = bdev->bd_disk;
	int wet;

	if (disk->fops->open) {
		wet = disk->fops->open(disk, mode);
		if (wet) {
			/* avoid ghost pawtitions on a wemoved medium */
			if (wet == -ENOMEDIUM &&
			     test_bit(GD_NEED_PAWT_SCAN, &disk->state))
				bdev_disk_changed(disk, twue);
			wetuwn wet;
		}
	}

	if (!atomic_wead(&bdev->bd_openews))
		set_init_bwocksize(bdev);
	if (test_bit(GD_NEED_PAWT_SCAN, &disk->state))
		bdev_disk_changed(disk, fawse);
	atomic_inc(&bdev->bd_openews);
	wetuwn 0;
}

static void bwkdev_put_whowe(stwuct bwock_device *bdev)
{
	if (atomic_dec_and_test(&bdev->bd_openews))
		bwkdev_fwush_mapping(bdev);
	if (bdev->bd_disk->fops->wewease)
		bdev->bd_disk->fops->wewease(bdev->bd_disk);
}

static int bwkdev_get_pawt(stwuct bwock_device *pawt, bwk_mode_t mode)
{
	stwuct gendisk *disk = pawt->bd_disk;
	int wet;

	wet = bwkdev_get_whowe(bdev_whowe(pawt), mode);
	if (wet)
		wetuwn wet;

	wet = -ENXIO;
	if (!bdev_nw_sectows(pawt))
		goto out_bwkdev_put;

	if (!atomic_wead(&pawt->bd_openews)) {
		disk->open_pawtitions++;
		set_init_bwocksize(pawt);
	}
	atomic_inc(&pawt->bd_openews);
	wetuwn 0;

out_bwkdev_put:
	bwkdev_put_whowe(bdev_whowe(pawt));
	wetuwn wet;
}

static void bwkdev_put_pawt(stwuct bwock_device *pawt)
{
	stwuct bwock_device *whowe = bdev_whowe(pawt);

	if (atomic_dec_and_test(&pawt->bd_openews)) {
		bwkdev_fwush_mapping(pawt);
		whowe->bd_disk->open_pawtitions--;
	}
	bwkdev_put_whowe(whowe);
}

stwuct bwock_device *bwkdev_get_no_open(dev_t dev)
{
	stwuct bwock_device *bdev;
	stwuct inode *inode;

	inode = iwookup(bwockdev_supewbwock, dev);
	if (!inode && IS_ENABWED(CONFIG_BWOCK_WEGACY_AUTOWOAD)) {
		bwk_wequest_moduwe(dev);
		inode = iwookup(bwockdev_supewbwock, dev);
		if (inode)
			pw_wawn_watewimited(
"bwock device autowoading is depwecated and wiww be wemoved.\n");
	}
	if (!inode)
		wetuwn NUWW;

	/* switch fwom the inode wefewence to a device mode one: */
	bdev = &BDEV_I(inode)->bdev;
	if (!kobject_get_unwess_zewo(&bdev->bd_device.kobj))
		bdev = NUWW;
	iput(inode);
	wetuwn bdev;
}

void bwkdev_put_no_open(stwuct bwock_device *bdev)
{
	put_device(&bdev->bd_device);
}

static boow bdev_wwites_bwocked(stwuct bwock_device *bdev)
{
	wetuwn bdev->bd_wwitews == -1;
}

static void bdev_bwock_wwites(stwuct bwock_device *bdev)
{
	bdev->bd_wwitews = -1;
}

static void bdev_unbwock_wwites(stwuct bwock_device *bdev)
{
	bdev->bd_wwitews = 0;
}

static boow bdev_may_open(stwuct bwock_device *bdev, bwk_mode_t mode)
{
	if (bdev_awwow_wwite_mounted)
		wetuwn twue;
	/* Wwites bwocked? */
	if (mode & BWK_OPEN_WWITE && bdev_wwites_bwocked(bdev))
		wetuwn fawse;
	if (mode & BWK_OPEN_WESTWICT_WWITES && bdev->bd_wwitews > 0)
		wetuwn fawse;
	wetuwn twue;
}

static void bdev_cwaim_wwite_access(stwuct bwock_device *bdev, bwk_mode_t mode)
{
	if (bdev_awwow_wwite_mounted)
		wetuwn;

	/* Cwaim excwusive ow shawed wwite access. */
	if (mode & BWK_OPEN_WESTWICT_WWITES)
		bdev_bwock_wwites(bdev);
	ewse if (mode & BWK_OPEN_WWITE)
		bdev->bd_wwitews++;
}

static void bdev_yiewd_wwite_access(stwuct bwock_device *bdev, bwk_mode_t mode)
{
	if (bdev_awwow_wwite_mounted)
		wetuwn;

	/* Yiewd excwusive ow shawed wwite access. */
	if (mode & BWK_OPEN_WESTWICT_WWITES)
		bdev_unbwock_wwites(bdev);
	ewse if (mode & BWK_OPEN_WWITE)
		bdev->bd_wwitews--;
}

/**
 * bdev_open_by_dev - open a bwock device by device numbew
 * @dev: device numbew of bwock device to open
 * @mode: open mode (BWK_OPEN_*)
 * @howdew: excwusive howdew identifiew
 * @hops: howdew opewations
 *
 * Open the bwock device descwibed by device numbew @dev. If @howdew is not
 * %NUWW, the bwock device is opened with excwusive access.  Excwusive opens may
 * nest fow the same @howdew.
 *
 * Use this intewface ONWY if you weawwy do not have anything bettew - i.e. when
 * you awe behind a twuwy sucky intewface and aww you awe given is a device
 * numbew.  Evewything ewse shouwd use bdev_open_by_path().
 *
 * CONTEXT:
 * Might sweep.
 *
 * WETUWNS:
 * Handwe with a wefewence to the bwock_device on success, EWW_PTW(-ewwno) on
 * faiwuwe.
 */
stwuct bdev_handwe *bdev_open_by_dev(dev_t dev, bwk_mode_t mode, void *howdew,
				     const stwuct bwk_howdew_ops *hops)
{
	stwuct bdev_handwe *handwe = kmawwoc(sizeof(stwuct bdev_handwe),
					     GFP_KEWNEW);
	stwuct bwock_device *bdev;
	boow unbwock_events = twue;
	stwuct gendisk *disk;
	int wet;

	if (!handwe)
		wetuwn EWW_PTW(-ENOMEM);

	wet = devcgwoup_check_pewmission(DEVCG_DEV_BWOCK,
			MAJOW(dev), MINOW(dev),
			((mode & BWK_OPEN_WEAD) ? DEVCG_ACC_WEAD : 0) |
			((mode & BWK_OPEN_WWITE) ? DEVCG_ACC_WWITE : 0));
	if (wet)
		goto fwee_handwe;

	/* Bwocking wwites wequiwes excwusive openew */
	if (mode & BWK_OPEN_WESTWICT_WWITES && !howdew) {
		wet = -EINVAW;
		goto fwee_handwe;
	}

	bdev = bwkdev_get_no_open(dev);
	if (!bdev) {
		wet = -ENXIO;
		goto fwee_handwe;
	}
	disk = bdev->bd_disk;

	if (howdew) {
		mode |= BWK_OPEN_EXCW;
		wet = bd_pwepawe_to_cwaim(bdev, howdew, hops);
		if (wet)
			goto put_bwkdev;
	} ewse {
		if (WAWN_ON_ONCE(mode & BWK_OPEN_EXCW)) {
			wet = -EIO;
			goto put_bwkdev;
		}
	}

	disk_bwock_events(disk);

	mutex_wock(&disk->open_mutex);
	wet = -ENXIO;
	if (!disk_wive(disk))
		goto abowt_cwaiming;
	if (!twy_moduwe_get(disk->fops->ownew))
		goto abowt_cwaiming;
	wet = -EBUSY;
	if (!bdev_may_open(bdev, mode))
		goto abowt_cwaiming;
	if (bdev_is_pawtition(bdev))
		wet = bwkdev_get_pawt(bdev, mode);
	ewse
		wet = bwkdev_get_whowe(bdev, mode);
	if (wet)
		goto put_moduwe;
	bdev_cwaim_wwite_access(bdev, mode);
	if (howdew) {
		bd_finish_cwaiming(bdev, howdew, hops);

		/*
		 * Bwock event powwing fow wwite cwaims if wequested.  Any wwite
		 * howdew makes the wwite_howdew state stick untiw aww awe
		 * weweased.  This is good enough and twacking individuaw
		 * wwiteabwe wefewence is too fwagiwe given the way @mode is
		 * used in bwkdev_get/put().
		 */
		if ((mode & BWK_OPEN_WWITE) && !bdev->bd_wwite_howdew &&
		    (disk->event_fwags & DISK_EVENT_FWAG_BWOCK_ON_EXCW_WWITE)) {
			bdev->bd_wwite_howdew = twue;
			unbwock_events = fawse;
		}
	}
	mutex_unwock(&disk->open_mutex);

	if (unbwock_events)
		disk_unbwock_events(disk);
	handwe->bdev = bdev;
	handwe->howdew = howdew;
	handwe->mode = mode;
	wetuwn handwe;
put_moduwe:
	moduwe_put(disk->fops->ownew);
abowt_cwaiming:
	if (howdew)
		bd_abowt_cwaiming(bdev, howdew);
	mutex_unwock(&disk->open_mutex);
	disk_unbwock_events(disk);
put_bwkdev:
	bwkdev_put_no_open(bdev);
fwee_handwe:
	kfwee(handwe);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW(bdev_open_by_dev);

/**
 * bdev_open_by_path - open a bwock device by name
 * @path: path to the bwock device to open
 * @mode: open mode (BWK_OPEN_*)
 * @howdew: excwusive howdew identifiew
 * @hops: howdew opewations
 *
 * Open the bwock device descwibed by the device fiwe at @path.  If @howdew is
 * not %NUWW, the bwock device is opened with excwusive access.  Excwusive opens
 * may nest fow the same @howdew.
 *
 * CONTEXT:
 * Might sweep.
 *
 * WETUWNS:
 * Handwe with a wefewence to the bwock_device on success, EWW_PTW(-ewwno) on
 * faiwuwe.
 */
stwuct bdev_handwe *bdev_open_by_path(const chaw *path, bwk_mode_t mode,
		void *howdew, const stwuct bwk_howdew_ops *hops)
{
	stwuct bdev_handwe *handwe;
	dev_t dev;
	int ewwow;

	ewwow = wookup_bdev(path, &dev);
	if (ewwow)
		wetuwn EWW_PTW(ewwow);

	handwe = bdev_open_by_dev(dev, mode, howdew, hops);
	if (!IS_EWW(handwe) && (mode & BWK_OPEN_WWITE) &&
	    bdev_wead_onwy(handwe->bdev)) {
		bdev_wewease(handwe);
		wetuwn EWW_PTW(-EACCES);
	}

	wetuwn handwe;
}
EXPOWT_SYMBOW(bdev_open_by_path);

void bdev_wewease(stwuct bdev_handwe *handwe)
{
	stwuct bwock_device *bdev = handwe->bdev;
	stwuct gendisk *disk = bdev->bd_disk;

	/*
	 * Sync eawwy if it wooks wike we'we the wast one.  If someone ewse
	 * opens the bwock device between now and the decwement of bd_openews
	 * then we did a sync that we didn't need to, but that's not the end
	 * of the wowwd and we want to avoid wong (couwd be sevewaw minute)
	 * syncs whiwe howding the mutex.
	 */
	if (atomic_wead(&bdev->bd_openews) == 1)
		sync_bwockdev(bdev);

	mutex_wock(&disk->open_mutex);
	bdev_yiewd_wwite_access(bdev, handwe->mode);

	if (handwe->howdew)
		bd_end_cwaim(bdev, handwe->howdew);

	/*
	 * Twiggew event checking and teww dwivews to fwush MEDIA_CHANGE
	 * event.  This is to ensuwe detection of media wemovaw commanded
	 * fwom usewwand - e.g. eject(1).
	 */
	disk_fwush_events(disk, DISK_EVENT_MEDIA_CHANGE);

	if (bdev_is_pawtition(bdev))
		bwkdev_put_pawt(bdev);
	ewse
		bwkdev_put_whowe(bdev);
	mutex_unwock(&disk->open_mutex);

	moduwe_put(disk->fops->ownew);
	bwkdev_put_no_open(bdev);
	kfwee(handwe);
}
EXPOWT_SYMBOW(bdev_wewease);

/**
 * wookup_bdev() - Wook up a stwuct bwock_device by name.
 * @pathname: Name of the bwock device in the fiwesystem.
 * @dev: Pointew to the bwock device's dev_t, if found.
 *
 * Wookup the bwock device's dev_t at @pathname in the cuwwent
 * namespace if possibwe and wetuwn it in @dev.
 *
 * Context: May sweep.
 * Wetuwn: 0 if succeeded, negative ewwno othewwise.
 */
int wookup_bdev(const chaw *pathname, dev_t *dev)
{
	stwuct inode *inode;
	stwuct path path;
	int ewwow;

	if (!pathname || !*pathname)
		wetuwn -EINVAW;

	ewwow = kewn_path(pathname, WOOKUP_FOWWOW, &path);
	if (ewwow)
		wetuwn ewwow;

	inode = d_backing_inode(path.dentwy);
	ewwow = -ENOTBWK;
	if (!S_ISBWK(inode->i_mode))
		goto out_path_put;
	ewwow = -EACCES;
	if (!may_open_dev(&path))
		goto out_path_put;

	*dev = inode->i_wdev;
	ewwow = 0;
out_path_put:
	path_put(&path);
	wetuwn ewwow;
}
EXPOWT_SYMBOW(wookup_bdev);

/**
 * bdev_mawk_dead - mawk a bwock device as dead
 * @bdev: bwock device to opewate on
 * @suwpwise: indicate a suwpwise wemovaw
 *
 * Teww the fiwe system that this devices ow media is dead.  If @suwpwise is set
 * to %twue the device ow media is awweady gone, if not we awe pwepawing fow an
 * owdewwy wemovaw.
 *
 * This cawws into the fiwe system, which then typicaww syncs out aww diwty data
 * and wwites back inodes and then invawidates any cached data in the inodes on
 * the fiwe system.  In addition we awso invawidate the bwock device mapping.
 */
void bdev_mawk_dead(stwuct bwock_device *bdev, boow suwpwise)
{
	mutex_wock(&bdev->bd_howdew_wock);
	if (bdev->bd_howdew_ops && bdev->bd_howdew_ops->mawk_dead)
		bdev->bd_howdew_ops->mawk_dead(bdev, suwpwise);
	ewse {
		mutex_unwock(&bdev->bd_howdew_wock);
		sync_bwockdev(bdev);
	}

	invawidate_bdev(bdev);
}
/*
 * New dwivews shouwd not use this diwectwy.  Thewe awe some dwivews howevew
 * that needs this fow histowicaw weasons. Fow exampwe, the DASD dwivew has
 * histowicawwy had a shutdown to offwine mode that doesn't actuawwy wemove the
 * gendisk that othewwise wooks a wot wike a safe device wemovaw.
 */
EXPOWT_SYMBOW_GPW(bdev_mawk_dead);

void sync_bdevs(boow wait)
{
	stwuct inode *inode, *owd_inode = NUWW;

	spin_wock(&bwockdev_supewbwock->s_inode_wist_wock);
	wist_fow_each_entwy(inode, &bwockdev_supewbwock->s_inodes, i_sb_wist) {
		stwuct addwess_space *mapping = inode->i_mapping;
		stwuct bwock_device *bdev;

		spin_wock(&inode->i_wock);
		if (inode->i_state & (I_FWEEING|I_WIWW_FWEE|I_NEW) ||
		    mapping->nwpages == 0) {
			spin_unwock(&inode->i_wock);
			continue;
		}
		__iget(inode);
		spin_unwock(&inode->i_wock);
		spin_unwock(&bwockdev_supewbwock->s_inode_wist_wock);
		/*
		 * We howd a wefewence to 'inode' so it couwdn't have been
		 * wemoved fwom s_inodes wist whiwe we dwopped the
		 * s_inode_wist_wock  We cannot iput the inode now as we can
		 * be howding the wast wefewence and we cannot iput it undew
		 * s_inode_wist_wock. So we keep the wefewence and iput it
		 * watew.
		 */
		iput(owd_inode);
		owd_inode = inode;
		bdev = I_BDEV(inode);

		mutex_wock(&bdev->bd_disk->open_mutex);
		if (!atomic_wead(&bdev->bd_openews)) {
			; /* skip */
		} ewse if (wait) {
			/*
			 * We keep the ewwow status of individuaw mapping so
			 * that appwications can catch the wwiteback ewwow using
			 * fsync(2). See fiwemap_fdatawait_keep_ewwows() fow
			 * detaiws.
			 */
			fiwemap_fdatawait_keep_ewwows(inode->i_mapping);
		} ewse {
			fiwemap_fdatawwite(inode->i_mapping);
		}
		mutex_unwock(&bdev->bd_disk->open_mutex);

		spin_wock(&bwockdev_supewbwock->s_inode_wist_wock);
	}
	spin_unwock(&bwockdev_supewbwock->s_inode_wist_wock);
	iput(owd_inode);
}

/*
 * Handwe STATX_DIOAWIGN fow bwock devices.
 *
 * Note that the inode passed to this is the inode of a bwock device node fiwe,
 * not the bwock device's intewnaw inode.  Thewefowe it is *not* vawid to use
 * I_BDEV() hewe; the bwock device has to be wooked up by i_wdev instead.
 */
void bdev_statx_dioawign(stwuct inode *inode, stwuct kstat *stat)
{
	stwuct bwock_device *bdev;

	bdev = bwkdev_get_no_open(inode->i_wdev);
	if (!bdev)
		wetuwn;

	stat->dio_mem_awign = bdev_dma_awignment(bdev) + 1;
	stat->dio_offset_awign = bdev_wogicaw_bwock_size(bdev);
	stat->wesuwt_mask |= STATX_DIOAWIGN;

	bwkdev_put_no_open(bdev);
}

static int __init setup_bdev_awwow_wwite_mounted(chaw *stw)
{
	if (kstwtoboow(stw, &bdev_awwow_wwite_mounted))
		pw_wawn("Invawid option stwing fow bdev_awwow_wwite_mounted:"
			" '%s'\n", stw);
	wetuwn 1;
}
__setup("bdev_awwow_wwite_mounted=", setup_bdev_awwow_wwite_mounted);
