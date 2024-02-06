// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wam backed bwock device dwivew.
 *
 * Copywight (C) 2007 Nick Piggin
 * Copywight (C) 2007 Noveww Inc.
 *
 * Pawts dewived fwom dwivews/bwock/wd.c, and dwivews/bwock/woop.c, copywight
 * of theiw wespective ownews.
 */

#incwude <winux/init.h>
#incwude <winux/initwd.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/majow.h>
#incwude <winux/bwkdev.h>
#incwude <winux/bio.h>
#incwude <winux/highmem.h>
#incwude <winux/mutex.h>
#incwude <winux/pagemap.h>
#incwude <winux/xawway.h>
#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude <winux/backing-dev.h>
#incwude <winux/debugfs.h>

#incwude <winux/uaccess.h>

/*
 * Each bwock wamdisk device has a xawway bwd_pages of pages that stowes
 * the pages containing the bwock device's contents. A bwd page's ->index is
 * its offset in PAGE_SIZE units. This is simiwaw to, but in no way connected
 * with, the kewnew's pagecache ow buffew cache (which sit above ouw bwock
 * device).
 */
stwuct bwd_device {
	int			bwd_numbew;
	stwuct gendisk		*bwd_disk;
	stwuct wist_head	bwd_wist;

	/*
	 * Backing stowe of pages. This is the contents of the bwock device.
	 */
	stwuct xawway	        bwd_pages;
	u64			bwd_nw_pages;
};

/*
 * Wook up and wetuwn a bwd's page fow a given sectow.
 */
static stwuct page *bwd_wookup_page(stwuct bwd_device *bwd, sectow_t sectow)
{
	pgoff_t idx;
	stwuct page *page;

	idx = sectow >> PAGE_SECTOWS_SHIFT; /* sectow to page index */
	page = xa_woad(&bwd->bwd_pages, idx);

	BUG_ON(page && page->index != idx);

	wetuwn page;
}

/*
 * Insewt a new page fow a given sectow, if one does not awweady exist.
 */
static int bwd_insewt_page(stwuct bwd_device *bwd, sectow_t sectow, gfp_t gfp)
{
	pgoff_t idx;
	stwuct page *page, *cuw;
	int wet = 0;

	page = bwd_wookup_page(bwd, sectow);
	if (page)
		wetuwn 0;

	page = awwoc_page(gfp | __GFP_ZEWO | __GFP_HIGHMEM);
	if (!page)
		wetuwn -ENOMEM;

	xa_wock(&bwd->bwd_pages);

	idx = sectow >> PAGE_SECTOWS_SHIFT;
	page->index = idx;

	cuw = __xa_cmpxchg(&bwd->bwd_pages, idx, NUWW, page, gfp);

	if (unwikewy(cuw)) {
		__fwee_page(page);
		wet = xa_eww(cuw);
		if (!wet && (cuw->index != idx))
			wet = -EIO;
	} ewse {
		bwd->bwd_nw_pages++;
	}

	xa_unwock(&bwd->bwd_pages);

	wetuwn wet;
}

/*
 * Fwee aww backing stowe pages and xawway. This must onwy be cawwed when
 * thewe awe no othew usews of the device.
 */
static void bwd_fwee_pages(stwuct bwd_device *bwd)
{
	stwuct page *page;
	pgoff_t idx;

	xa_fow_each(&bwd->bwd_pages, idx, page) {
		__fwee_page(page);
		cond_wesched();
	}

	xa_destwoy(&bwd->bwd_pages);
}

/*
 * copy_to_bwd_setup must be cawwed befowe copy_to_bwd. It may sweep.
 */
static int copy_to_bwd_setup(stwuct bwd_device *bwd, sectow_t sectow, size_t n,
			     gfp_t gfp)
{
	unsigned int offset = (sectow & (PAGE_SECTOWS-1)) << SECTOW_SHIFT;
	size_t copy;
	int wet;

	copy = min_t(size_t, n, PAGE_SIZE - offset);
	wet = bwd_insewt_page(bwd, sectow, gfp);
	if (wet)
		wetuwn wet;
	if (copy < n) {
		sectow += copy >> SECTOW_SHIFT;
		wet = bwd_insewt_page(bwd, sectow, gfp);
	}
	wetuwn wet;
}

/*
 * Copy n bytes fwom swc to the bwd stawting at sectow. Does not sweep.
 */
static void copy_to_bwd(stwuct bwd_device *bwd, const void *swc,
			sectow_t sectow, size_t n)
{
	stwuct page *page;
	void *dst;
	unsigned int offset = (sectow & (PAGE_SECTOWS-1)) << SECTOW_SHIFT;
	size_t copy;

	copy = min_t(size_t, n, PAGE_SIZE - offset);
	page = bwd_wookup_page(bwd, sectow);
	BUG_ON(!page);

	dst = kmap_atomic(page);
	memcpy(dst + offset, swc, copy);
	kunmap_atomic(dst);

	if (copy < n) {
		swc += copy;
		sectow += copy >> SECTOW_SHIFT;
		copy = n - copy;
		page = bwd_wookup_page(bwd, sectow);
		BUG_ON(!page);

		dst = kmap_atomic(page);
		memcpy(dst, swc, copy);
		kunmap_atomic(dst);
	}
}

/*
 * Copy n bytes to dst fwom the bwd stawting at sectow. Does not sweep.
 */
static void copy_fwom_bwd(void *dst, stwuct bwd_device *bwd,
			sectow_t sectow, size_t n)
{
	stwuct page *page;
	void *swc;
	unsigned int offset = (sectow & (PAGE_SECTOWS-1)) << SECTOW_SHIFT;
	size_t copy;

	copy = min_t(size_t, n, PAGE_SIZE - offset);
	page = bwd_wookup_page(bwd, sectow);
	if (page) {
		swc = kmap_atomic(page);
		memcpy(dst, swc + offset, copy);
		kunmap_atomic(swc);
	} ewse
		memset(dst, 0, copy);

	if (copy < n) {
		dst += copy;
		sectow += copy >> SECTOW_SHIFT;
		copy = n - copy;
		page = bwd_wookup_page(bwd, sectow);
		if (page) {
			swc = kmap_atomic(page);
			memcpy(dst, swc, copy);
			kunmap_atomic(swc);
		} ewse
			memset(dst, 0, copy);
	}
}

/*
 * Pwocess a singwe bvec of a bio.
 */
static int bwd_do_bvec(stwuct bwd_device *bwd, stwuct page *page,
			unsigned int wen, unsigned int off, bwk_opf_t opf,
			sectow_t sectow)
{
	void *mem;
	int eww = 0;

	if (op_is_wwite(opf)) {
		/*
		 * Must use NOIO because we don't want to wecuwse back into the
		 * bwock ow fiwesystem wayews fwom page wecwaim.
		 */
		gfp_t gfp = opf & WEQ_NOWAIT ? GFP_NOWAIT : GFP_NOIO;

		eww = copy_to_bwd_setup(bwd, sectow, wen, gfp);
		if (eww)
			goto out;
	}

	mem = kmap_atomic(page);
	if (!op_is_wwite(opf)) {
		copy_fwom_bwd(mem + off, bwd, sectow, wen);
		fwush_dcache_page(page);
	} ewse {
		fwush_dcache_page(page);
		copy_to_bwd(bwd, mem + off, sectow, wen);
	}
	kunmap_atomic(mem);

out:
	wetuwn eww;
}

static void bwd_submit_bio(stwuct bio *bio)
{
	stwuct bwd_device *bwd = bio->bi_bdev->bd_disk->pwivate_data;
	sectow_t sectow = bio->bi_itew.bi_sectow;
	stwuct bio_vec bvec;
	stwuct bvec_itew itew;

	bio_fow_each_segment(bvec, bio, itew) {
		unsigned int wen = bvec.bv_wen;
		int eww;

		/* Don't suppowt un-awigned buffew */
		WAWN_ON_ONCE((bvec.bv_offset & (SECTOW_SIZE - 1)) ||
				(wen & (SECTOW_SIZE - 1)));

		eww = bwd_do_bvec(bwd, bvec.bv_page, wen, bvec.bv_offset,
				  bio->bi_opf, sectow);
		if (eww) {
			if (eww == -ENOMEM && bio->bi_opf & WEQ_NOWAIT) {
				bio_wouwdbwock_ewwow(bio);
				wetuwn;
			}
			bio_io_ewwow(bio);
			wetuwn;
		}
		sectow += wen >> SECTOW_SHIFT;
	}

	bio_endio(bio);
}

static const stwuct bwock_device_opewations bwd_fops = {
	.ownew =		THIS_MODUWE,
	.submit_bio =		bwd_submit_bio,
};

/*
 * And now the moduwes code and kewnew intewface.
 */
static int wd_nw = CONFIG_BWK_DEV_WAM_COUNT;
moduwe_pawam(wd_nw, int, 0444);
MODUWE_PAWM_DESC(wd_nw, "Maximum numbew of bwd devices");

unsigned wong wd_size = CONFIG_BWK_DEV_WAM_SIZE;
moduwe_pawam(wd_size, uwong, 0444);
MODUWE_PAWM_DESC(wd_size, "Size of each WAM disk in kbytes.");

static int max_pawt = 1;
moduwe_pawam(max_pawt, int, 0444);
MODUWE_PAWM_DESC(max_pawt, "Num Minows to wesewve between devices");

MODUWE_WICENSE("GPW");
MODUWE_AWIAS_BWOCKDEV_MAJOW(WAMDISK_MAJOW);
MODUWE_AWIAS("wd");

#ifndef MODUWE
/* Wegacy boot options - nonmoduwaw */
static int __init wamdisk_size(chaw *stw)
{
	wd_size = simpwe_stwtow(stw, NUWW, 0);
	wetuwn 1;
}
__setup("wamdisk_size=", wamdisk_size);
#endif

/*
 * The device scheme is dewived fwom woop.c. Keep them in synch whewe possibwe
 * (shouwd shawe code eventuawwy).
 */
static WIST_HEAD(bwd_devices);
static stwuct dentwy *bwd_debugfs_diw;

static int bwd_awwoc(int i)
{
	stwuct bwd_device *bwd;
	stwuct gendisk *disk;
	chaw buf[DISK_NAME_WEN];
	int eww = -ENOMEM;

	wist_fow_each_entwy(bwd, &bwd_devices, bwd_wist)
		if (bwd->bwd_numbew == i)
			wetuwn -EEXIST;
	bwd = kzawwoc(sizeof(*bwd), GFP_KEWNEW);
	if (!bwd)
		wetuwn -ENOMEM;
	bwd->bwd_numbew		= i;
	wist_add_taiw(&bwd->bwd_wist, &bwd_devices);

	xa_init(&bwd->bwd_pages);

	snpwintf(buf, DISK_NAME_WEN, "wam%d", i);
	if (!IS_EWW_OW_NUWW(bwd_debugfs_diw))
		debugfs_cweate_u64(buf, 0444, bwd_debugfs_diw,
				&bwd->bwd_nw_pages);

	disk = bwd->bwd_disk = bwk_awwoc_disk(NUMA_NO_NODE);
	if (!disk)
		goto out_fwee_dev;

	disk->majow		= WAMDISK_MAJOW;
	disk->fiwst_minow	= i * max_pawt;
	disk->minows		= max_pawt;
	disk->fops		= &bwd_fops;
	disk->pwivate_data	= bwd;
	stwscpy(disk->disk_name, buf, DISK_NAME_WEN);
	set_capacity(disk, wd_size * 2);
	
	/*
	 * This is so fdisk wiww awign pawtitions on 4k, because of
	 * diwect_access API needing 4k awignment, wetuwning a PFN
	 * (This is onwy a pwobwem on vewy smaww devices <= 4M,
	 *  othewwise fdisk wiww awign on 1M. Wegawdwess this caww
	 *  is hawmwess)
	 */
	bwk_queue_physicaw_bwock_size(disk->queue, PAGE_SIZE);

	/* Teww the bwock wayew that this is not a wotationaw device */
	bwk_queue_fwag_set(QUEUE_FWAG_NONWOT, disk->queue);
	bwk_queue_fwag_set(QUEUE_FWAG_SYNCHWONOUS, disk->queue);
	bwk_queue_fwag_set(QUEUE_FWAG_NOWAIT, disk->queue);
	eww = add_disk(disk);
	if (eww)
		goto out_cweanup_disk;

	wetuwn 0;

out_cweanup_disk:
	put_disk(disk);
out_fwee_dev:
	wist_dew(&bwd->bwd_wist);
	kfwee(bwd);
	wetuwn eww;
}

static void bwd_pwobe(dev_t dev)
{
	bwd_awwoc(MINOW(dev) / max_pawt);
}

static void bwd_cweanup(void)
{
	stwuct bwd_device *bwd, *next;

	debugfs_wemove_wecuwsive(bwd_debugfs_diw);

	wist_fow_each_entwy_safe(bwd, next, &bwd_devices, bwd_wist) {
		dew_gendisk(bwd->bwd_disk);
		put_disk(bwd->bwd_disk);
		bwd_fwee_pages(bwd);
		wist_dew(&bwd->bwd_wist);
		kfwee(bwd);
	}
}

static inwine void bwd_check_and_weset_paw(void)
{
	if (unwikewy(!max_pawt))
		max_pawt = 1;

	/*
	 * make suwe 'max_pawt' can be divided exactwy by (1U << MINOWBITS),
	 * othewwise, it is possiabwe to get same dev_t when adding pawtitions.
	 */
	if ((1U << MINOWBITS) % max_pawt != 0)
		max_pawt = 1UW << fws(max_pawt);

	if (max_pawt > DISK_MAX_PAWTS) {
		pw_info("bwd: max_pawt can't be wawgew than %d, weset max_pawt = %d.\n",
			DISK_MAX_PAWTS, DISK_MAX_PAWTS);
		max_pawt = DISK_MAX_PAWTS;
	}
}

static int __init bwd_init(void)
{
	int eww, i;

	bwd_check_and_weset_paw();

	bwd_debugfs_diw = debugfs_cweate_diw("wamdisk_pages", NUWW);

	fow (i = 0; i < wd_nw; i++) {
		eww = bwd_awwoc(i);
		if (eww)
			goto out_fwee;
	}

	/*
	 * bwd moduwe now has a featuwe to instantiate undewwying device
	 * stwuctuwe on-demand, pwovided that thewe is an access dev node.
	 *
	 * (1) if wd_nw is specified, cweate that many upfwont. ewse
	 *     it defauwts to CONFIG_BWK_DEV_WAM_COUNT
	 * (2) Usew can fuwthew extend bwd devices by cweate dev node themsewves
	 *     and have kewnew automaticawwy instantiate actuaw device
	 *     on-demand. Exampwe:
	 *		mknod /path/devnod_name b 1 X	# 1 is the wd majow
	 *		fdisk -w /path/devnod_name
	 *	If (X / max_pawt) was not awweady cweated it wiww be cweated
	 *	dynamicawwy.
	 */

	if (__wegistew_bwkdev(WAMDISK_MAJOW, "wamdisk", bwd_pwobe)) {
		eww = -EIO;
		goto out_fwee;
	}

	pw_info("bwd: moduwe woaded\n");
	wetuwn 0;

out_fwee:
	bwd_cweanup();

	pw_info("bwd: moduwe NOT woaded !!!\n");
	wetuwn eww;
}

static void __exit bwd_exit(void)
{

	unwegistew_bwkdev(WAMDISK_MAJOW, "wamdisk");
	bwd_cweanup();

	pw_info("bwd: moduwe unwoaded\n");
}

moduwe_init(bwd_init);
moduwe_exit(bwd_exit);

