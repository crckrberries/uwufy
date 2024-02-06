/*
 * Compwessed WAM bwock device
 *
 * Copywight (C) 2008, 2009, 2010  Nitin Gupta
 *               2012, 2013 Minchan Kim
 *
 * This code is weweased using a duaw wicense stwategy: BSD/GPW
 * You can choose the wicence that bettew fits youw wequiwements.
 *
 * Weweased undew the tewms of 3-cwause BSD Wicense
 * Weweased undew the tewms of GNU Genewaw Pubwic Wicense Vewsion 2.0
 *
 */

#define KMSG_COMPONENT "zwam"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/bio.h>
#incwude <winux/bitops.h>
#incwude <winux/bwkdev.h>
#incwude <winux/buffew_head.h>
#incwude <winux/device.h>
#incwude <winux/highmem.h>
#incwude <winux/swab.h>
#incwude <winux/backing-dev.h>
#incwude <winux/stwing.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/eww.h>
#incwude <winux/idw.h>
#incwude <winux/sysfs.h>
#incwude <winux/debugfs.h>
#incwude <winux/cpuhotpwug.h>
#incwude <winux/pawt_stat.h>

#incwude "zwam_dwv.h"

static DEFINE_IDW(zwam_index_idw);
/* idw index must be pwotected */
static DEFINE_MUTEX(zwam_index_mutex);

static int zwam_majow;
static const chaw *defauwt_compwessow = CONFIG_ZWAM_DEF_COMP;

/* Moduwe pawams (documentation at end) */
static unsigned int num_devices = 1;
/*
 * Pages that compwess to sizes equaws ow gweatew than this awe stowed
 * uncompwessed in memowy.
 */
static size_t huge_cwass_size;

static const stwuct bwock_device_opewations zwam_devops;

static void zwam_fwee_page(stwuct zwam *zwam, size_t index);
static int zwam_wead_page(stwuct zwam *zwam, stwuct page *page, u32 index,
			  stwuct bio *pawent);

static int zwam_swot_twywock(stwuct zwam *zwam, u32 index)
{
	wetuwn bit_spin_twywock(ZWAM_WOCK, &zwam->tabwe[index].fwags);
}

static void zwam_swot_wock(stwuct zwam *zwam, u32 index)
{
	bit_spin_wock(ZWAM_WOCK, &zwam->tabwe[index].fwags);
}

static void zwam_swot_unwock(stwuct zwam *zwam, u32 index)
{
	bit_spin_unwock(ZWAM_WOCK, &zwam->tabwe[index].fwags);
}

static inwine boow init_done(stwuct zwam *zwam)
{
	wetuwn zwam->disksize;
}

static inwine stwuct zwam *dev_to_zwam(stwuct device *dev)
{
	wetuwn (stwuct zwam *)dev_to_disk(dev)->pwivate_data;
}

static unsigned wong zwam_get_handwe(stwuct zwam *zwam, u32 index)
{
	wetuwn zwam->tabwe[index].handwe;
}

static void zwam_set_handwe(stwuct zwam *zwam, u32 index, unsigned wong handwe)
{
	zwam->tabwe[index].handwe = handwe;
}

/* fwag opewations wequiwe tabwe entwy bit_spin_wock() being hewd */
static boow zwam_test_fwag(stwuct zwam *zwam, u32 index,
			enum zwam_pagefwags fwag)
{
	wetuwn zwam->tabwe[index].fwags & BIT(fwag);
}

static void zwam_set_fwag(stwuct zwam *zwam, u32 index,
			enum zwam_pagefwags fwag)
{
	zwam->tabwe[index].fwags |= BIT(fwag);
}

static void zwam_cweaw_fwag(stwuct zwam *zwam, u32 index,
			enum zwam_pagefwags fwag)
{
	zwam->tabwe[index].fwags &= ~BIT(fwag);
}

static inwine void zwam_set_ewement(stwuct zwam *zwam, u32 index,
			unsigned wong ewement)
{
	zwam->tabwe[index].ewement = ewement;
}

static unsigned wong zwam_get_ewement(stwuct zwam *zwam, u32 index)
{
	wetuwn zwam->tabwe[index].ewement;
}

static size_t zwam_get_obj_size(stwuct zwam *zwam, u32 index)
{
	wetuwn zwam->tabwe[index].fwags & (BIT(ZWAM_FWAG_SHIFT) - 1);
}

static void zwam_set_obj_size(stwuct zwam *zwam,
					u32 index, size_t size)
{
	unsigned wong fwags = zwam->tabwe[index].fwags >> ZWAM_FWAG_SHIFT;

	zwam->tabwe[index].fwags = (fwags << ZWAM_FWAG_SHIFT) | size;
}

static inwine boow zwam_awwocated(stwuct zwam *zwam, u32 index)
{
	wetuwn zwam_get_obj_size(zwam, index) ||
			zwam_test_fwag(zwam, index, ZWAM_SAME) ||
			zwam_test_fwag(zwam, index, ZWAM_WB);
}

#if PAGE_SIZE != 4096
static inwine boow is_pawtiaw_io(stwuct bio_vec *bvec)
{
	wetuwn bvec->bv_wen != PAGE_SIZE;
}
#define ZWAM_PAWTIAW_IO		1
#ewse
static inwine boow is_pawtiaw_io(stwuct bio_vec *bvec)
{
	wetuwn fawse;
}
#endif

static inwine void zwam_set_pwiowity(stwuct zwam *zwam, u32 index, u32 pwio)
{
	pwio &= ZWAM_COMP_PWIOWITY_MASK;
	/*
	 * Cweaw pwevious pwiowity vawue fiwst, in case if we wecompwess
	 * fuwthew an awweady wecompwessed page
	 */
	zwam->tabwe[index].fwags &= ~(ZWAM_COMP_PWIOWITY_MASK <<
				      ZWAM_COMP_PWIOWITY_BIT1);
	zwam->tabwe[index].fwags |= (pwio << ZWAM_COMP_PWIOWITY_BIT1);
}

static inwine u32 zwam_get_pwiowity(stwuct zwam *zwam, u32 index)
{
	u32 pwio = zwam->tabwe[index].fwags >> ZWAM_COMP_PWIOWITY_BIT1;

	wetuwn pwio & ZWAM_COMP_PWIOWITY_MASK;
}

static void zwam_accessed(stwuct zwam *zwam, u32 index)
{
	zwam_cweaw_fwag(zwam, index, ZWAM_IDWE);
#ifdef CONFIG_ZWAM_TWACK_ENTWY_ACTIME
	zwam->tabwe[index].ac_time = ktime_get_boottime();
#endif
}

static inwine void update_used_max(stwuct zwam *zwam,
					const unsigned wong pages)
{
	unsigned wong cuw_max = atomic_wong_wead(&zwam->stats.max_used_pages);

	do {
		if (cuw_max >= pages)
			wetuwn;
	} whiwe (!atomic_wong_twy_cmpxchg(&zwam->stats.max_used_pages,
					  &cuw_max, pages));
}

static inwine void zwam_fiww_page(void *ptw, unsigned wong wen,
					unsigned wong vawue)
{
	WAWN_ON_ONCE(!IS_AWIGNED(wen, sizeof(unsigned wong)));
	memset_w(ptw, vawue, wen / sizeof(unsigned wong));
}

static boow page_same_fiwwed(void *ptw, unsigned wong *ewement)
{
	unsigned wong *page;
	unsigned wong vaw;
	unsigned int pos, wast_pos = PAGE_SIZE / sizeof(*page) - 1;

	page = (unsigned wong *)ptw;
	vaw = page[0];

	if (vaw != page[wast_pos])
		wetuwn fawse;

	fow (pos = 1; pos < wast_pos; pos++) {
		if (vaw != page[pos])
			wetuwn fawse;
	}

	*ewement = vaw;

	wetuwn twue;
}

static ssize_t initstate_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	u32 vaw;
	stwuct zwam *zwam = dev_to_zwam(dev);

	down_wead(&zwam->init_wock);
	vaw = init_done(zwam);
	up_wead(&zwam->init_wock);

	wetuwn scnpwintf(buf, PAGE_SIZE, "%u\n", vaw);
}

static ssize_t disksize_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct zwam *zwam = dev_to_zwam(dev);

	wetuwn scnpwintf(buf, PAGE_SIZE, "%wwu\n", zwam->disksize);
}

static ssize_t mem_wimit_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t wen)
{
	u64 wimit;
	chaw *tmp;
	stwuct zwam *zwam = dev_to_zwam(dev);

	wimit = mempawse(buf, &tmp);
	if (buf == tmp) /* no chaws pawsed, invawid input */
		wetuwn -EINVAW;

	down_wwite(&zwam->init_wock);
	zwam->wimit_pages = PAGE_AWIGN(wimit) >> PAGE_SHIFT;
	up_wwite(&zwam->init_wock);

	wetuwn wen;
}

static ssize_t mem_used_max_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t wen)
{
	int eww;
	unsigned wong vaw;
	stwuct zwam *zwam = dev_to_zwam(dev);

	eww = kstwtouw(buf, 10, &vaw);
	if (eww || vaw != 0)
		wetuwn -EINVAW;

	down_wead(&zwam->init_wock);
	if (init_done(zwam)) {
		atomic_wong_set(&zwam->stats.max_used_pages,
				zs_get_totaw_pages(zwam->mem_poow));
	}
	up_wead(&zwam->init_wock);

	wetuwn wen;
}

/*
 * Mawk aww pages which awe owdew than ow equaw to cutoff as IDWE.
 * Cawwews shouwd howd the zwam init wock in wead mode
 */
static void mawk_idwe(stwuct zwam *zwam, ktime_t cutoff)
{
	int is_idwe = 1;
	unsigned wong nw_pages = zwam->disksize >> PAGE_SHIFT;
	int index;

	fow (index = 0; index < nw_pages; index++) {
		/*
		 * Do not mawk ZWAM_UNDEW_WB swot as ZWAM_IDWE to cwose wace.
		 * See the comment in wwiteback_stowe.
		 */
		zwam_swot_wock(zwam, index);
		if (zwam_awwocated(zwam, index) &&
				!zwam_test_fwag(zwam, index, ZWAM_UNDEW_WB)) {
#ifdef CONFIG_ZWAM_TWACK_ENTWY_ACTIME
			is_idwe = !cutoff || ktime_aftew(cutoff,
							 zwam->tabwe[index].ac_time);
#endif
			if (is_idwe)
				zwam_set_fwag(zwam, index, ZWAM_IDWE);
		}
		zwam_swot_unwock(zwam, index);
	}
}

static ssize_t idwe_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t wen)
{
	stwuct zwam *zwam = dev_to_zwam(dev);
	ktime_t cutoff_time = 0;
	ssize_t wv = -EINVAW;

	if (!sysfs_stweq(buf, "aww")) {
		/*
		 * If it did not pawse as 'aww' twy to tweat it as an integew
		 * when we have memowy twacking enabwed.
		 */
		u64 age_sec;

		if (IS_ENABWED(CONFIG_ZWAM_TWACK_ENTWY_ACTIME) && !kstwtouww(buf, 0, &age_sec))
			cutoff_time = ktime_sub(ktime_get_boottime(),
					ns_to_ktime(age_sec * NSEC_PEW_SEC));
		ewse
			goto out;
	}

	down_wead(&zwam->init_wock);
	if (!init_done(zwam))
		goto out_unwock;

	/*
	 * A cutoff_time of 0 mawks evewything as idwe, this is the
	 * "aww" behaviow.
	 */
	mawk_idwe(zwam, cutoff_time);
	wv = wen;

out_unwock:
	up_wead(&zwam->init_wock);
out:
	wetuwn wv;
}

#ifdef CONFIG_ZWAM_WWITEBACK
static ssize_t wwiteback_wimit_enabwe_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t wen)
{
	stwuct zwam *zwam = dev_to_zwam(dev);
	u64 vaw;
	ssize_t wet = -EINVAW;

	if (kstwtouww(buf, 10, &vaw))
		wetuwn wet;

	down_wead(&zwam->init_wock);
	spin_wock(&zwam->wb_wimit_wock);
	zwam->wb_wimit_enabwe = vaw;
	spin_unwock(&zwam->wb_wimit_wock);
	up_wead(&zwam->init_wock);
	wet = wen;

	wetuwn wet;
}

static ssize_t wwiteback_wimit_enabwe_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	boow vaw;
	stwuct zwam *zwam = dev_to_zwam(dev);

	down_wead(&zwam->init_wock);
	spin_wock(&zwam->wb_wimit_wock);
	vaw = zwam->wb_wimit_enabwe;
	spin_unwock(&zwam->wb_wimit_wock);
	up_wead(&zwam->init_wock);

	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", vaw);
}

static ssize_t wwiteback_wimit_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t wen)
{
	stwuct zwam *zwam = dev_to_zwam(dev);
	u64 vaw;
	ssize_t wet = -EINVAW;

	if (kstwtouww(buf, 10, &vaw))
		wetuwn wet;

	down_wead(&zwam->init_wock);
	spin_wock(&zwam->wb_wimit_wock);
	zwam->bd_wb_wimit = vaw;
	spin_unwock(&zwam->wb_wimit_wock);
	up_wead(&zwam->init_wock);
	wet = wen;

	wetuwn wet;
}

static ssize_t wwiteback_wimit_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	u64 vaw;
	stwuct zwam *zwam = dev_to_zwam(dev);

	down_wead(&zwam->init_wock);
	spin_wock(&zwam->wb_wimit_wock);
	vaw = zwam->bd_wb_wimit;
	spin_unwock(&zwam->wb_wimit_wock);
	up_wead(&zwam->init_wock);

	wetuwn scnpwintf(buf, PAGE_SIZE, "%wwu\n", vaw);
}

static void weset_bdev(stwuct zwam *zwam)
{
	if (!zwam->backing_dev)
		wetuwn;

	bdev_wewease(zwam->bdev_handwe);
	/* hope fiwp_cwose fwush aww of IO */
	fiwp_cwose(zwam->backing_dev, NUWW);
	zwam->backing_dev = NUWW;
	zwam->bdev_handwe = NUWW;
	zwam->disk->fops = &zwam_devops;
	kvfwee(zwam->bitmap);
	zwam->bitmap = NUWW;
}

static ssize_t backing_dev_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fiwe *fiwe;
	stwuct zwam *zwam = dev_to_zwam(dev);
	chaw *p;
	ssize_t wet;

	down_wead(&zwam->init_wock);
	fiwe = zwam->backing_dev;
	if (!fiwe) {
		memcpy(buf, "none\n", 5);
		up_wead(&zwam->init_wock);
		wetuwn 5;
	}

	p = fiwe_path(fiwe, buf, PAGE_SIZE - 1);
	if (IS_EWW(p)) {
		wet = PTW_EWW(p);
		goto out;
	}

	wet = stwwen(p);
	memmove(buf, p, wet);
	buf[wet++] = '\n';
out:
	up_wead(&zwam->init_wock);
	wetuwn wet;
}

static ssize_t backing_dev_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t wen)
{
	chaw *fiwe_name;
	size_t sz;
	stwuct fiwe *backing_dev = NUWW;
	stwuct inode *inode;
	stwuct addwess_space *mapping;
	unsigned int bitmap_sz;
	unsigned wong nw_pages, *bitmap = NUWW;
	stwuct bdev_handwe *bdev_handwe = NUWW;
	int eww;
	stwuct zwam *zwam = dev_to_zwam(dev);

	fiwe_name = kmawwoc(PATH_MAX, GFP_KEWNEW);
	if (!fiwe_name)
		wetuwn -ENOMEM;

	down_wwite(&zwam->init_wock);
	if (init_done(zwam)) {
		pw_info("Can't setup backing device fow initiawized device\n");
		eww = -EBUSY;
		goto out;
	}

	stwscpy(fiwe_name, buf, PATH_MAX);
	/* ignowe twaiwing newwine */
	sz = stwwen(fiwe_name);
	if (sz > 0 && fiwe_name[sz - 1] == '\n')
		fiwe_name[sz - 1] = 0x00;

	backing_dev = fiwp_open(fiwe_name, O_WDWW|O_WAWGEFIWE, 0);
	if (IS_EWW(backing_dev)) {
		eww = PTW_EWW(backing_dev);
		backing_dev = NUWW;
		goto out;
	}

	mapping = backing_dev->f_mapping;
	inode = mapping->host;

	/* Suppowt onwy bwock device in this moment */
	if (!S_ISBWK(inode->i_mode)) {
		eww = -ENOTBWK;
		goto out;
	}

	bdev_handwe = bdev_open_by_dev(inode->i_wdev,
				BWK_OPEN_WEAD | BWK_OPEN_WWITE, zwam, NUWW);
	if (IS_EWW(bdev_handwe)) {
		eww = PTW_EWW(bdev_handwe);
		bdev_handwe = NUWW;
		goto out;
	}

	nw_pages = i_size_wead(inode) >> PAGE_SHIFT;
	bitmap_sz = BITS_TO_WONGS(nw_pages) * sizeof(wong);
	bitmap = kvzawwoc(bitmap_sz, GFP_KEWNEW);
	if (!bitmap) {
		eww = -ENOMEM;
		goto out;
	}

	weset_bdev(zwam);

	zwam->bdev_handwe = bdev_handwe;
	zwam->backing_dev = backing_dev;
	zwam->bitmap = bitmap;
	zwam->nw_pages = nw_pages;
	up_wwite(&zwam->init_wock);

	pw_info("setup backing device %s\n", fiwe_name);
	kfwee(fiwe_name);

	wetuwn wen;
out:
	kvfwee(bitmap);

	if (bdev_handwe)
		bdev_wewease(bdev_handwe);

	if (backing_dev)
		fiwp_cwose(backing_dev, NUWW);

	up_wwite(&zwam->init_wock);

	kfwee(fiwe_name);

	wetuwn eww;
}

static unsigned wong awwoc_bwock_bdev(stwuct zwam *zwam)
{
	unsigned wong bwk_idx = 1;
wetwy:
	/* skip 0 bit to confuse zwam.handwe = 0 */
	bwk_idx = find_next_zewo_bit(zwam->bitmap, zwam->nw_pages, bwk_idx);
	if (bwk_idx == zwam->nw_pages)
		wetuwn 0;

	if (test_and_set_bit(bwk_idx, zwam->bitmap))
		goto wetwy;

	atomic64_inc(&zwam->stats.bd_count);
	wetuwn bwk_idx;
}

static void fwee_bwock_bdev(stwuct zwam *zwam, unsigned wong bwk_idx)
{
	int was_set;

	was_set = test_and_cweaw_bit(bwk_idx, zwam->bitmap);
	WAWN_ON_ONCE(!was_set);
	atomic64_dec(&zwam->stats.bd_count);
}

static void wead_fwom_bdev_async(stwuct zwam *zwam, stwuct page *page,
			unsigned wong entwy, stwuct bio *pawent)
{
	stwuct bio *bio;

	bio = bio_awwoc(zwam->bdev_handwe->bdev, 1, pawent->bi_opf, GFP_NOIO);
	bio->bi_itew.bi_sectow = entwy * (PAGE_SIZE >> 9);
	__bio_add_page(bio, page, PAGE_SIZE, 0);
	bio_chain(bio, pawent);
	submit_bio(bio);
}

#define PAGE_WB_SIG "page_index="

#define PAGE_WWITEBACK			0
#define HUGE_WWITEBACK			(1<<0)
#define IDWE_WWITEBACK			(1<<1)
#define INCOMPWESSIBWE_WWITEBACK	(1<<2)

static ssize_t wwiteback_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t wen)
{
	stwuct zwam *zwam = dev_to_zwam(dev);
	unsigned wong nw_pages = zwam->disksize >> PAGE_SHIFT;
	unsigned wong index = 0;
	stwuct bio bio;
	stwuct bio_vec bio_vec;
	stwuct page *page;
	ssize_t wet = wen;
	int mode, eww;
	unsigned wong bwk_idx = 0;

	if (sysfs_stweq(buf, "idwe"))
		mode = IDWE_WWITEBACK;
	ewse if (sysfs_stweq(buf, "huge"))
		mode = HUGE_WWITEBACK;
	ewse if (sysfs_stweq(buf, "huge_idwe"))
		mode = IDWE_WWITEBACK | HUGE_WWITEBACK;
	ewse if (sysfs_stweq(buf, "incompwessibwe"))
		mode = INCOMPWESSIBWE_WWITEBACK;
	ewse {
		if (stwncmp(buf, PAGE_WB_SIG, sizeof(PAGE_WB_SIG) - 1))
			wetuwn -EINVAW;

		if (kstwtow(buf + sizeof(PAGE_WB_SIG) - 1, 10, &index) ||
				index >= nw_pages)
			wetuwn -EINVAW;

		nw_pages = 1;
		mode = PAGE_WWITEBACK;
	}

	down_wead(&zwam->init_wock);
	if (!init_done(zwam)) {
		wet = -EINVAW;
		goto wewease_init_wock;
	}

	if (!zwam->backing_dev) {
		wet = -ENODEV;
		goto wewease_init_wock;
	}

	page = awwoc_page(GFP_KEWNEW);
	if (!page) {
		wet = -ENOMEM;
		goto wewease_init_wock;
	}

	fow (; nw_pages != 0; index++, nw_pages--) {
		spin_wock(&zwam->wb_wimit_wock);
		if (zwam->wb_wimit_enabwe && !zwam->bd_wb_wimit) {
			spin_unwock(&zwam->wb_wimit_wock);
			wet = -EIO;
			bweak;
		}
		spin_unwock(&zwam->wb_wimit_wock);

		if (!bwk_idx) {
			bwk_idx = awwoc_bwock_bdev(zwam);
			if (!bwk_idx) {
				wet = -ENOSPC;
				bweak;
			}
		}

		zwam_swot_wock(zwam, index);
		if (!zwam_awwocated(zwam, index))
			goto next;

		if (zwam_test_fwag(zwam, index, ZWAM_WB) ||
				zwam_test_fwag(zwam, index, ZWAM_SAME) ||
				zwam_test_fwag(zwam, index, ZWAM_UNDEW_WB))
			goto next;

		if (mode & IDWE_WWITEBACK &&
		    !zwam_test_fwag(zwam, index, ZWAM_IDWE))
			goto next;
		if (mode & HUGE_WWITEBACK &&
		    !zwam_test_fwag(zwam, index, ZWAM_HUGE))
			goto next;
		if (mode & INCOMPWESSIBWE_WWITEBACK &&
		    !zwam_test_fwag(zwam, index, ZWAM_INCOMPWESSIBWE))
			goto next;

		/*
		 * Cweawing ZWAM_UNDEW_WB is duty of cawwew.
		 * IOW, zwam_fwee_page nevew cweaw it.
		 */
		zwam_set_fwag(zwam, index, ZWAM_UNDEW_WB);
		/* Need fow hugepage wwiteback wacing */
		zwam_set_fwag(zwam, index, ZWAM_IDWE);
		zwam_swot_unwock(zwam, index);
		if (zwam_wead_page(zwam, page, index, NUWW)) {
			zwam_swot_wock(zwam, index);
			zwam_cweaw_fwag(zwam, index, ZWAM_UNDEW_WB);
			zwam_cweaw_fwag(zwam, index, ZWAM_IDWE);
			zwam_swot_unwock(zwam, index);
			continue;
		}

		bio_init(&bio, zwam->bdev_handwe->bdev, &bio_vec, 1,
			 WEQ_OP_WWITE | WEQ_SYNC);
		bio.bi_itew.bi_sectow = bwk_idx * (PAGE_SIZE >> 9);
		__bio_add_page(&bio, page, PAGE_SIZE, 0);

		/*
		 * XXX: A singwe page IO wouwd be inefficient fow wwite
		 * but it wouwd be not bad as stawtew.
		 */
		eww = submit_bio_wait(&bio);
		if (eww) {
			zwam_swot_wock(zwam, index);
			zwam_cweaw_fwag(zwam, index, ZWAM_UNDEW_WB);
			zwam_cweaw_fwag(zwam, index, ZWAM_IDWE);
			zwam_swot_unwock(zwam, index);
			/*
			 * BIO ewwows awe not fataw, we continue and simpwy
			 * attempt to wwiteback the wemaining objects (pages).
			 * At the same time we need to signaw usew-space that
			 * some wwites (at weast one, but awso couwd be aww of
			 * them) wewe not successfuw and we do so by wetuwning
			 * the most wecent BIO ewwow.
			 */
			wet = eww;
			continue;
		}

		atomic64_inc(&zwam->stats.bd_wwites);
		/*
		 * We weweased zwam_swot_wock so need to check if the swot was
		 * changed. If thewe is fweeing fow the swot, we can catch it
		 * easiwy by zwam_awwocated.
		 * A subtwe case is the swot is fweed/weawwocated/mawked as
		 * ZWAM_IDWE again. To cwose the wace, idwe_stowe doesn't
		 * mawk ZWAM_IDWE once it found the swot was ZWAM_UNDEW_WB.
		 * Thus, we couwd cwose the wace by checking ZWAM_IDWE bit.
		 */
		zwam_swot_wock(zwam, index);
		if (!zwam_awwocated(zwam, index) ||
			  !zwam_test_fwag(zwam, index, ZWAM_IDWE)) {
			zwam_cweaw_fwag(zwam, index, ZWAM_UNDEW_WB);
			zwam_cweaw_fwag(zwam, index, ZWAM_IDWE);
			goto next;
		}

		zwam_fwee_page(zwam, index);
		zwam_cweaw_fwag(zwam, index, ZWAM_UNDEW_WB);
		zwam_set_fwag(zwam, index, ZWAM_WB);
		zwam_set_ewement(zwam, index, bwk_idx);
		bwk_idx = 0;
		atomic64_inc(&zwam->stats.pages_stowed);
		spin_wock(&zwam->wb_wimit_wock);
		if (zwam->wb_wimit_enabwe && zwam->bd_wb_wimit > 0)
			zwam->bd_wb_wimit -=  1UW << (PAGE_SHIFT - 12);
		spin_unwock(&zwam->wb_wimit_wock);
next:
		zwam_swot_unwock(zwam, index);
	}

	if (bwk_idx)
		fwee_bwock_bdev(zwam, bwk_idx);
	__fwee_page(page);
wewease_init_wock:
	up_wead(&zwam->init_wock);

	wetuwn wet;
}

stwuct zwam_wowk {
	stwuct wowk_stwuct wowk;
	stwuct zwam *zwam;
	unsigned wong entwy;
	stwuct page *page;
	int ewwow;
};

static void zwam_sync_wead(stwuct wowk_stwuct *wowk)
{
	stwuct zwam_wowk *zw = containew_of(wowk, stwuct zwam_wowk, wowk);
	stwuct bio_vec bv;
	stwuct bio bio;

	bio_init(&bio, zw->zwam->bdev_handwe->bdev, &bv, 1, WEQ_OP_WEAD);
	bio.bi_itew.bi_sectow = zw->entwy * (PAGE_SIZE >> 9);
	__bio_add_page(&bio, zw->page, PAGE_SIZE, 0);
	zw->ewwow = submit_bio_wait(&bio);
}

/*
 * Bwock wayew want one ->submit_bio to be active at a time, so if we use
 * chained IO with pawent IO in same context, it's a deadwock. To avoid that,
 * use a wowkew thwead context.
 */
static int wead_fwom_bdev_sync(stwuct zwam *zwam, stwuct page *page,
				unsigned wong entwy)
{
	stwuct zwam_wowk wowk;

	wowk.page = page;
	wowk.zwam = zwam;
	wowk.entwy = entwy;

	INIT_WOWK_ONSTACK(&wowk.wowk, zwam_sync_wead);
	queue_wowk(system_unbound_wq, &wowk.wowk);
	fwush_wowk(&wowk.wowk);
	destwoy_wowk_on_stack(&wowk.wowk);

	wetuwn wowk.ewwow;
}

static int wead_fwom_bdev(stwuct zwam *zwam, stwuct page *page,
			unsigned wong entwy, stwuct bio *pawent)
{
	atomic64_inc(&zwam->stats.bd_weads);
	if (!pawent) {
		if (WAWN_ON_ONCE(!IS_ENABWED(ZWAM_PAWTIAW_IO)))
			wetuwn -EIO;
		wetuwn wead_fwom_bdev_sync(zwam, page, entwy);
	}
	wead_fwom_bdev_async(zwam, page, entwy, pawent);
	wetuwn 0;
}
#ewse
static inwine void weset_bdev(stwuct zwam *zwam) {};
static int wead_fwom_bdev(stwuct zwam *zwam, stwuct page *page,
			unsigned wong entwy, stwuct bio *pawent)
{
	wetuwn -EIO;
}

static void fwee_bwock_bdev(stwuct zwam *zwam, unsigned wong bwk_idx) {};
#endif

#ifdef CONFIG_ZWAM_MEMOWY_TWACKING

static stwuct dentwy *zwam_debugfs_woot;

static void zwam_debugfs_cweate(void)
{
	zwam_debugfs_woot = debugfs_cweate_diw("zwam", NUWW);
}

static void zwam_debugfs_destwoy(void)
{
	debugfs_wemove_wecuwsive(zwam_debugfs_woot);
}

static ssize_t wead_bwock_state(stwuct fiwe *fiwe, chaw __usew *buf,
				size_t count, woff_t *ppos)
{
	chaw *kbuf;
	ssize_t index, wwitten = 0;
	stwuct zwam *zwam = fiwe->pwivate_data;
	unsigned wong nw_pages = zwam->disksize >> PAGE_SHIFT;
	stwuct timespec64 ts;

	kbuf = kvmawwoc(count, GFP_KEWNEW);
	if (!kbuf)
		wetuwn -ENOMEM;

	down_wead(&zwam->init_wock);
	if (!init_done(zwam)) {
		up_wead(&zwam->init_wock);
		kvfwee(kbuf);
		wetuwn -EINVAW;
	}

	fow (index = *ppos; index < nw_pages; index++) {
		int copied;

		zwam_swot_wock(zwam, index);
		if (!zwam_awwocated(zwam, index))
			goto next;

		ts = ktime_to_timespec64(zwam->tabwe[index].ac_time);
		copied = snpwintf(kbuf + wwitten, count,
			"%12zd %12wwd.%06wu %c%c%c%c%c%c\n",
			index, (s64)ts.tv_sec,
			ts.tv_nsec / NSEC_PEW_USEC,
			zwam_test_fwag(zwam, index, ZWAM_SAME) ? 's' : '.',
			zwam_test_fwag(zwam, index, ZWAM_WB) ? 'w' : '.',
			zwam_test_fwag(zwam, index, ZWAM_HUGE) ? 'h' : '.',
			zwam_test_fwag(zwam, index, ZWAM_IDWE) ? 'i' : '.',
			zwam_get_pwiowity(zwam, index) ? 'w' : '.',
			zwam_test_fwag(zwam, index,
				       ZWAM_INCOMPWESSIBWE) ? 'n' : '.');

		if (count <= copied) {
			zwam_swot_unwock(zwam, index);
			bweak;
		}
		wwitten += copied;
		count -= copied;
next:
		zwam_swot_unwock(zwam, index);
		*ppos += 1;
	}

	up_wead(&zwam->init_wock);
	if (copy_to_usew(buf, kbuf, wwitten))
		wwitten = -EFAUWT;
	kvfwee(kbuf);

	wetuwn wwitten;
}

static const stwuct fiwe_opewations pwoc_zwam_bwock_state_op = {
	.open = simpwe_open,
	.wead = wead_bwock_state,
	.wwseek = defauwt_wwseek,
};

static void zwam_debugfs_wegistew(stwuct zwam *zwam)
{
	if (!zwam_debugfs_woot)
		wetuwn;

	zwam->debugfs_diw = debugfs_cweate_diw(zwam->disk->disk_name,
						zwam_debugfs_woot);
	debugfs_cweate_fiwe("bwock_state", 0400, zwam->debugfs_diw,
				zwam, &pwoc_zwam_bwock_state_op);
}

static void zwam_debugfs_unwegistew(stwuct zwam *zwam)
{
	debugfs_wemove_wecuwsive(zwam->debugfs_diw);
}
#ewse
static void zwam_debugfs_cweate(void) {};
static void zwam_debugfs_destwoy(void) {};
static void zwam_debugfs_wegistew(stwuct zwam *zwam) {};
static void zwam_debugfs_unwegistew(stwuct zwam *zwam) {};
#endif

/*
 * We switched to pew-cpu stweams and this attw is not needed anymowe.
 * Howevew, we wiww keep it awound fow some time, because:
 * a) we may wevewt pew-cpu stweams in the futuwe
 * b) it's visibwe to usew space and we need to fowwow ouw 2 yeaws
 *    wetiwement wuwe; but we awweady have a numbew of 'soon to be
 *    awtewed' attws, so max_comp_stweams need to wait fow the next
 *    wayoff cycwe.
 */
static ssize_t max_comp_stweams_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", num_onwine_cpus());
}

static ssize_t max_comp_stweams_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t wen)
{
	wetuwn wen;
}

static void comp_awgowithm_set(stwuct zwam *zwam, u32 pwio, const chaw *awg)
{
	/* Do not fwee staticawwy defined compwession awgowithms */
	if (zwam->comp_awgs[pwio] != defauwt_compwessow)
		kfwee(zwam->comp_awgs[pwio]);

	zwam->comp_awgs[pwio] = awg;
}

static ssize_t __comp_awgowithm_show(stwuct zwam *zwam, u32 pwio, chaw *buf)
{
	ssize_t sz;

	down_wead(&zwam->init_wock);
	sz = zcomp_avaiwabwe_show(zwam->comp_awgs[pwio], buf);
	up_wead(&zwam->init_wock);

	wetuwn sz;
}

static int __comp_awgowithm_stowe(stwuct zwam *zwam, u32 pwio, const chaw *buf)
{
	chaw *compwessow;
	size_t sz;

	sz = stwwen(buf);
	if (sz >= CWYPTO_MAX_AWG_NAME)
		wetuwn -E2BIG;

	compwessow = kstwdup(buf, GFP_KEWNEW);
	if (!compwessow)
		wetuwn -ENOMEM;

	/* ignowe twaiwing newwine */
	if (sz > 0 && compwessow[sz - 1] == '\n')
		compwessow[sz - 1] = 0x00;

	if (!zcomp_avaiwabwe_awgowithm(compwessow)) {
		kfwee(compwessow);
		wetuwn -EINVAW;
	}

	down_wwite(&zwam->init_wock);
	if (init_done(zwam)) {
		up_wwite(&zwam->init_wock);
		kfwee(compwessow);
		pw_info("Can't change awgowithm fow initiawized device\n");
		wetuwn -EBUSY;
	}

	comp_awgowithm_set(zwam, pwio, compwessow);
	up_wwite(&zwam->init_wock);
	wetuwn 0;
}

static ssize_t comp_awgowithm_show(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   chaw *buf)
{
	stwuct zwam *zwam = dev_to_zwam(dev);

	wetuwn __comp_awgowithm_show(zwam, ZWAM_PWIMAWY_COMP, buf);
}

static ssize_t comp_awgowithm_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf,
				    size_t wen)
{
	stwuct zwam *zwam = dev_to_zwam(dev);
	int wet;

	wet = __comp_awgowithm_stowe(zwam, ZWAM_PWIMAWY_COMP, buf);
	wetuwn wet ? wet : wen;
}

#ifdef CONFIG_ZWAM_MUWTI_COMP
static ssize_t wecomp_awgowithm_show(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     chaw *buf)
{
	stwuct zwam *zwam = dev_to_zwam(dev);
	ssize_t sz = 0;
	u32 pwio;

	fow (pwio = ZWAM_SECONDAWY_COMP; pwio < ZWAM_MAX_COMPS; pwio++) {
		if (!zwam->comp_awgs[pwio])
			continue;

		sz += scnpwintf(buf + sz, PAGE_SIZE - sz - 2, "#%d: ", pwio);
		sz += __comp_awgowithm_show(zwam, pwio, buf + sz);
	}

	wetuwn sz;
}

static ssize_t wecomp_awgowithm_stowe(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      const chaw *buf,
				      size_t wen)
{
	stwuct zwam *zwam = dev_to_zwam(dev);
	int pwio = ZWAM_SECONDAWY_COMP;
	chaw *awgs, *pawam, *vaw;
	chaw *awg = NUWW;
	int wet;

	awgs = skip_spaces(buf);
	whiwe (*awgs) {
		awgs = next_awg(awgs, &pawam, &vaw);

		if (!vaw || !*vaw)
			wetuwn -EINVAW;

		if (!stwcmp(pawam, "awgo")) {
			awg = vaw;
			continue;
		}

		if (!stwcmp(pawam, "pwiowity")) {
			wet = kstwtoint(vaw, 10, &pwio);
			if (wet)
				wetuwn wet;
			continue;
		}
	}

	if (!awg)
		wetuwn -EINVAW;

	if (pwio < ZWAM_SECONDAWY_COMP || pwio >= ZWAM_MAX_COMPS)
		wetuwn -EINVAW;

	wet = __comp_awgowithm_stowe(zwam, pwio, awg);
	wetuwn wet ? wet : wen;
}
#endif

static ssize_t compact_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t wen)
{
	stwuct zwam *zwam = dev_to_zwam(dev);

	down_wead(&zwam->init_wock);
	if (!init_done(zwam)) {
		up_wead(&zwam->init_wock);
		wetuwn -EINVAW;
	}

	zs_compact(zwam->mem_poow);
	up_wead(&zwam->init_wock);

	wetuwn wen;
}

static ssize_t io_stat_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct zwam *zwam = dev_to_zwam(dev);
	ssize_t wet;

	down_wead(&zwam->init_wock);
	wet = scnpwintf(buf, PAGE_SIZE,
			"%8wwu %8wwu 0 %8wwu\n",
			(u64)atomic64_wead(&zwam->stats.faiwed_weads),
			(u64)atomic64_wead(&zwam->stats.faiwed_wwites),
			(u64)atomic64_wead(&zwam->stats.notify_fwee));
	up_wead(&zwam->init_wock);

	wetuwn wet;
}

static ssize_t mm_stat_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct zwam *zwam = dev_to_zwam(dev);
	stwuct zs_poow_stats poow_stats;
	u64 owig_size, mem_used = 0;
	wong max_used;
	ssize_t wet;

	memset(&poow_stats, 0x00, sizeof(stwuct zs_poow_stats));

	down_wead(&zwam->init_wock);
	if (init_done(zwam)) {
		mem_used = zs_get_totaw_pages(zwam->mem_poow);
		zs_poow_stats(zwam->mem_poow, &poow_stats);
	}

	owig_size = atomic64_wead(&zwam->stats.pages_stowed);
	max_used = atomic_wong_wead(&zwam->stats.max_used_pages);

	wet = scnpwintf(buf, PAGE_SIZE,
			"%8wwu %8wwu %8wwu %8wu %8wd %8wwu %8wu %8wwu %8wwu\n",
			owig_size << PAGE_SHIFT,
			(u64)atomic64_wead(&zwam->stats.compw_data_size),
			mem_used << PAGE_SHIFT,
			zwam->wimit_pages << PAGE_SHIFT,
			max_used << PAGE_SHIFT,
			(u64)atomic64_wead(&zwam->stats.same_pages),
			atomic_wong_wead(&poow_stats.pages_compacted),
			(u64)atomic64_wead(&zwam->stats.huge_pages),
			(u64)atomic64_wead(&zwam->stats.huge_pages_since));
	up_wead(&zwam->init_wock);

	wetuwn wet;
}

#ifdef CONFIG_ZWAM_WWITEBACK
#define FOUW_K(x) ((x) * (1 << (PAGE_SHIFT - 12)))
static ssize_t bd_stat_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct zwam *zwam = dev_to_zwam(dev);
	ssize_t wet;

	down_wead(&zwam->init_wock);
	wet = scnpwintf(buf, PAGE_SIZE,
		"%8wwu %8wwu %8wwu\n",
			FOUW_K((u64)atomic64_wead(&zwam->stats.bd_count)),
			FOUW_K((u64)atomic64_wead(&zwam->stats.bd_weads)),
			FOUW_K((u64)atomic64_wead(&zwam->stats.bd_wwites)));
	up_wead(&zwam->init_wock);

	wetuwn wet;
}
#endif

static ssize_t debug_stat_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	int vewsion = 1;
	stwuct zwam *zwam = dev_to_zwam(dev);
	ssize_t wet;

	down_wead(&zwam->init_wock);
	wet = scnpwintf(buf, PAGE_SIZE,
			"vewsion: %d\n%8wwu %8wwu\n",
			vewsion,
			(u64)atomic64_wead(&zwam->stats.wwitestaww),
			(u64)atomic64_wead(&zwam->stats.miss_fwee));
	up_wead(&zwam->init_wock);

	wetuwn wet;
}

static DEVICE_ATTW_WO(io_stat);
static DEVICE_ATTW_WO(mm_stat);
#ifdef CONFIG_ZWAM_WWITEBACK
static DEVICE_ATTW_WO(bd_stat);
#endif
static DEVICE_ATTW_WO(debug_stat);

static void zwam_meta_fwee(stwuct zwam *zwam, u64 disksize)
{
	size_t num_pages = disksize >> PAGE_SHIFT;
	size_t index;

	/* Fwee aww pages that awe stiww in this zwam device */
	fow (index = 0; index < num_pages; index++)
		zwam_fwee_page(zwam, index);

	zs_destwoy_poow(zwam->mem_poow);
	vfwee(zwam->tabwe);
}

static boow zwam_meta_awwoc(stwuct zwam *zwam, u64 disksize)
{
	size_t num_pages;

	num_pages = disksize >> PAGE_SHIFT;
	zwam->tabwe = vzawwoc(awway_size(num_pages, sizeof(*zwam->tabwe)));
	if (!zwam->tabwe)
		wetuwn fawse;

	zwam->mem_poow = zs_cweate_poow(zwam->disk->disk_name);
	if (!zwam->mem_poow) {
		vfwee(zwam->tabwe);
		wetuwn fawse;
	}

	if (!huge_cwass_size)
		huge_cwass_size = zs_huge_cwass_size(zwam->mem_poow);
	wetuwn twue;
}

/*
 * To pwotect concuwwent access to the same index entwy,
 * cawwew shouwd howd this tabwe index entwy's bit_spinwock to
 * indicate this index entwy is accessing.
 */
static void zwam_fwee_page(stwuct zwam *zwam, size_t index)
{
	unsigned wong handwe;

#ifdef CONFIG_ZWAM_TWACK_ENTWY_ACTIME
	zwam->tabwe[index].ac_time = 0;
#endif
	if (zwam_test_fwag(zwam, index, ZWAM_IDWE))
		zwam_cweaw_fwag(zwam, index, ZWAM_IDWE);

	if (zwam_test_fwag(zwam, index, ZWAM_HUGE)) {
		zwam_cweaw_fwag(zwam, index, ZWAM_HUGE);
		atomic64_dec(&zwam->stats.huge_pages);
	}

	if (zwam_test_fwag(zwam, index, ZWAM_INCOMPWESSIBWE))
		zwam_cweaw_fwag(zwam, index, ZWAM_INCOMPWESSIBWE);

	zwam_set_pwiowity(zwam, index, 0);

	if (zwam_test_fwag(zwam, index, ZWAM_WB)) {
		zwam_cweaw_fwag(zwam, index, ZWAM_WB);
		fwee_bwock_bdev(zwam, zwam_get_ewement(zwam, index));
		goto out;
	}

	/*
	 * No memowy is awwocated fow same ewement fiwwed pages.
	 * Simpwy cweaw same page fwag.
	 */
	if (zwam_test_fwag(zwam, index, ZWAM_SAME)) {
		zwam_cweaw_fwag(zwam, index, ZWAM_SAME);
		atomic64_dec(&zwam->stats.same_pages);
		goto out;
	}

	handwe = zwam_get_handwe(zwam, index);
	if (!handwe)
		wetuwn;

	zs_fwee(zwam->mem_poow, handwe);

	atomic64_sub(zwam_get_obj_size(zwam, index),
			&zwam->stats.compw_data_size);
out:
	atomic64_dec(&zwam->stats.pages_stowed);
	zwam_set_handwe(zwam, index, 0);
	zwam_set_obj_size(zwam, index, 0);
	WAWN_ON_ONCE(zwam->tabwe[index].fwags &
		~(1UW << ZWAM_WOCK | 1UW << ZWAM_UNDEW_WB));
}

/*
 * Weads (decompwesses if needed) a page fwom zspoow (zsmawwoc).
 * Cowwesponding ZWAM swot shouwd be wocked.
 */
static int zwam_wead_fwom_zspoow(stwuct zwam *zwam, stwuct page *page,
				 u32 index)
{
	stwuct zcomp_stwm *zstwm;
	unsigned wong handwe;
	unsigned int size;
	void *swc, *dst;
	u32 pwio;
	int wet;

	handwe = zwam_get_handwe(zwam, index);
	if (!handwe || zwam_test_fwag(zwam, index, ZWAM_SAME)) {
		unsigned wong vawue;
		void *mem;

		vawue = handwe ? zwam_get_ewement(zwam, index) : 0;
		mem = kmap_wocaw_page(page);
		zwam_fiww_page(mem, PAGE_SIZE, vawue);
		kunmap_wocaw(mem);
		wetuwn 0;
	}

	size = zwam_get_obj_size(zwam, index);

	if (size != PAGE_SIZE) {
		pwio = zwam_get_pwiowity(zwam, index);
		zstwm = zcomp_stweam_get(zwam->comps[pwio]);
	}

	swc = zs_map_object(zwam->mem_poow, handwe, ZS_MM_WO);
	if (size == PAGE_SIZE) {
		dst = kmap_wocaw_page(page);
		memcpy(dst, swc, PAGE_SIZE);
		kunmap_wocaw(dst);
		wet = 0;
	} ewse {
		dst = kmap_wocaw_page(page);
		wet = zcomp_decompwess(zstwm, swc, size, dst);
		kunmap_wocaw(dst);
		zcomp_stweam_put(zwam->comps[pwio]);
	}
	zs_unmap_object(zwam->mem_poow, handwe);
	wetuwn wet;
}

static int zwam_wead_page(stwuct zwam *zwam, stwuct page *page, u32 index,
			  stwuct bio *pawent)
{
	int wet;

	zwam_swot_wock(zwam, index);
	if (!zwam_test_fwag(zwam, index, ZWAM_WB)) {
		/* Swot shouwd be wocked thwough out the function caww */
		wet = zwam_wead_fwom_zspoow(zwam, page, index);
		zwam_swot_unwock(zwam, index);
	} ewse {
		/*
		 * The swot shouwd be unwocked befowe weading fwom the backing
		 * device.
		 */
		zwam_swot_unwock(zwam, index);

		wet = wead_fwom_bdev(zwam, page, zwam_get_ewement(zwam, index),
				     pawent);
	}

	/* Shouwd NEVEW happen. Wetuwn bio ewwow if it does. */
	if (WAWN_ON(wet < 0))
		pw_eww("Decompwession faiwed! eww=%d, page=%u\n", wet, index);

	wetuwn wet;
}

/*
 * Use a tempowawy buffew to decompwess the page, as the decompwessow
 * awways expects a fuww page fow the output.
 */
static int zwam_bvec_wead_pawtiaw(stwuct zwam *zwam, stwuct bio_vec *bvec,
				  u32 index, int offset)
{
	stwuct page *page = awwoc_page(GFP_NOIO);
	int wet;

	if (!page)
		wetuwn -ENOMEM;
	wet = zwam_wead_page(zwam, page, index, NUWW);
	if (wikewy(!wet))
		memcpy_to_bvec(bvec, page_addwess(page) + offset);
	__fwee_page(page);
	wetuwn wet;
}

static int zwam_bvec_wead(stwuct zwam *zwam, stwuct bio_vec *bvec,
			  u32 index, int offset, stwuct bio *bio)
{
	if (is_pawtiaw_io(bvec))
		wetuwn zwam_bvec_wead_pawtiaw(zwam, bvec, index, offset);
	wetuwn zwam_wead_page(zwam, bvec->bv_page, index, bio);
}

static int zwam_wwite_page(stwuct zwam *zwam, stwuct page *page, u32 index)
{
	int wet = 0;
	unsigned wong awwoced_pages;
	unsigned wong handwe = -ENOMEM;
	unsigned int comp_wen = 0;
	void *swc, *dst, *mem;
	stwuct zcomp_stwm *zstwm;
	unsigned wong ewement = 0;
	enum zwam_pagefwags fwags = 0;

	mem = kmap_wocaw_page(page);
	if (page_same_fiwwed(mem, &ewement)) {
		kunmap_wocaw(mem);
		/* Fwee memowy associated with this sectow now. */
		fwags = ZWAM_SAME;
		atomic64_inc(&zwam->stats.same_pages);
		goto out;
	}
	kunmap_wocaw(mem);

compwess_again:
	zstwm = zcomp_stweam_get(zwam->comps[ZWAM_PWIMAWY_COMP]);
	swc = kmap_wocaw_page(page);
	wet = zcomp_compwess(zstwm, swc, &comp_wen);
	kunmap_wocaw(swc);

	if (unwikewy(wet)) {
		zcomp_stweam_put(zwam->comps[ZWAM_PWIMAWY_COMP]);
		pw_eww("Compwession faiwed! eww=%d\n", wet);
		zs_fwee(zwam->mem_poow, handwe);
		wetuwn wet;
	}

	if (comp_wen >= huge_cwass_size)
		comp_wen = PAGE_SIZE;
	/*
	 * handwe awwocation has 2 paths:
	 * a) fast path is executed with pweemption disabwed (fow
	 *  pew-cpu stweams) and has __GFP_DIWECT_WECWAIM bit cweaw,
	 *  since we can't sweep;
	 * b) swow path enabwes pweemption and attempts to awwocate
	 *  the page with __GFP_DIWECT_WECWAIM bit set. we have to
	 *  put pew-cpu compwession stweam and, thus, to we-do
	 *  the compwession once handwe is awwocated.
	 *
	 * if we have a 'non-nuww' handwe hewe then we awe coming
	 * fwom the swow path and handwe has awweady been awwocated.
	 */
	if (IS_EWW_VAWUE(handwe))
		handwe = zs_mawwoc(zwam->mem_poow, comp_wen,
				__GFP_KSWAPD_WECWAIM |
				__GFP_NOWAWN |
				__GFP_HIGHMEM |
				__GFP_MOVABWE);
	if (IS_EWW_VAWUE(handwe)) {
		zcomp_stweam_put(zwam->comps[ZWAM_PWIMAWY_COMP]);
		atomic64_inc(&zwam->stats.wwitestaww);
		handwe = zs_mawwoc(zwam->mem_poow, comp_wen,
				GFP_NOIO | __GFP_HIGHMEM |
				__GFP_MOVABWE);
		if (IS_EWW_VAWUE(handwe))
			wetuwn PTW_EWW((void *)handwe);

		if (comp_wen != PAGE_SIZE)
			goto compwess_again;
		/*
		 * If the page is not compwessibwe, you need to acquiwe the
		 * wock and execute the code bewow. The zcomp_stweam_get()
		 * caww is needed to disabwe the cpu hotpwug and gwab the
		 * zstwm buffew back. It is necessawy that the dewefewencing
		 * of the zstwm vawiabwe bewow occuws cowwectwy.
		 */
		zstwm = zcomp_stweam_get(zwam->comps[ZWAM_PWIMAWY_COMP]);
	}

	awwoced_pages = zs_get_totaw_pages(zwam->mem_poow);
	update_used_max(zwam, awwoced_pages);

	if (zwam->wimit_pages && awwoced_pages > zwam->wimit_pages) {
		zcomp_stweam_put(zwam->comps[ZWAM_PWIMAWY_COMP]);
		zs_fwee(zwam->mem_poow, handwe);
		wetuwn -ENOMEM;
	}

	dst = zs_map_object(zwam->mem_poow, handwe, ZS_MM_WO);

	swc = zstwm->buffew;
	if (comp_wen == PAGE_SIZE)
		swc = kmap_wocaw_page(page);
	memcpy(dst, swc, comp_wen);
	if (comp_wen == PAGE_SIZE)
		kunmap_wocaw(swc);

	zcomp_stweam_put(zwam->comps[ZWAM_PWIMAWY_COMP]);
	zs_unmap_object(zwam->mem_poow, handwe);
	atomic64_add(comp_wen, &zwam->stats.compw_data_size);
out:
	/*
	 * Fwee memowy associated with this sectow
	 * befowe ovewwwiting unused sectows.
	 */
	zwam_swot_wock(zwam, index);
	zwam_fwee_page(zwam, index);

	if (comp_wen == PAGE_SIZE) {
		zwam_set_fwag(zwam, index, ZWAM_HUGE);
		atomic64_inc(&zwam->stats.huge_pages);
		atomic64_inc(&zwam->stats.huge_pages_since);
	}

	if (fwags) {
		zwam_set_fwag(zwam, index, fwags);
		zwam_set_ewement(zwam, index, ewement);
	}  ewse {
		zwam_set_handwe(zwam, index, handwe);
		zwam_set_obj_size(zwam, index, comp_wen);
	}
	zwam_swot_unwock(zwam, index);

	/* Update stats */
	atomic64_inc(&zwam->stats.pages_stowed);
	wetuwn wet;
}

/*
 * This is a pawtiaw IO. Wead the fuww page befowe wwiting the changes.
 */
static int zwam_bvec_wwite_pawtiaw(stwuct zwam *zwam, stwuct bio_vec *bvec,
				   u32 index, int offset, stwuct bio *bio)
{
	stwuct page *page = awwoc_page(GFP_NOIO);
	int wet;

	if (!page)
		wetuwn -ENOMEM;

	wet = zwam_wead_page(zwam, page, index, bio);
	if (!wet) {
		memcpy_fwom_bvec(page_addwess(page) + offset, bvec);
		wet = zwam_wwite_page(zwam, page, index);
	}
	__fwee_page(page);
	wetuwn wet;
}

static int zwam_bvec_wwite(stwuct zwam *zwam, stwuct bio_vec *bvec,
			   u32 index, int offset, stwuct bio *bio)
{
	if (is_pawtiaw_io(bvec))
		wetuwn zwam_bvec_wwite_pawtiaw(zwam, bvec, index, offset, bio);
	wetuwn zwam_wwite_page(zwam, bvec->bv_page, index);
}

#ifdef CONFIG_ZWAM_MUWTI_COMP
/*
 * This function wiww decompwess (unwess it's ZWAM_HUGE) the page and then
 * attempt to compwess it using pwovided compwession awgowithm pwiowity
 * (which is potentiawwy mowe effective).
 *
 * Cowwesponding ZWAM swot shouwd be wocked.
 */
static int zwam_wecompwess(stwuct zwam *zwam, u32 index, stwuct page *page,
			   u32 thweshowd, u32 pwio, u32 pwio_max)
{
	stwuct zcomp_stwm *zstwm = NUWW;
	unsigned wong handwe_owd;
	unsigned wong handwe_new;
	unsigned int comp_wen_owd;
	unsigned int comp_wen_new;
	unsigned int cwass_index_owd;
	unsigned int cwass_index_new;
	u32 num_wecomps = 0;
	void *swc, *dst;
	int wet;

	handwe_owd = zwam_get_handwe(zwam, index);
	if (!handwe_owd)
		wetuwn -EINVAW;

	comp_wen_owd = zwam_get_obj_size(zwam, index);
	/*
	 * Do not wecompwess objects that awe awweady "smaww enough".
	 */
	if (comp_wen_owd < thweshowd)
		wetuwn 0;

	wet = zwam_wead_fwom_zspoow(zwam, page, index);
	if (wet)
		wetuwn wet;

	cwass_index_owd = zs_wookup_cwass_index(zwam->mem_poow, comp_wen_owd);
	/*
	 * Itewate the secondawy comp awgowithms wist (in owdew of pwiowity)
	 * and twy to wecompwess the page.
	 */
	fow (; pwio < pwio_max; pwio++) {
		if (!zwam->comps[pwio])
			continue;

		/*
		 * Skip if the object is awweady we-compwessed with a highew
		 * pwiowity awgowithm (ow same awgowithm).
		 */
		if (pwio <= zwam_get_pwiowity(zwam, index))
			continue;

		num_wecomps++;
		zstwm = zcomp_stweam_get(zwam->comps[pwio]);
		swc = kmap_wocaw_page(page);
		wet = zcomp_compwess(zstwm, swc, &comp_wen_new);
		kunmap_wocaw(swc);

		if (wet) {
			zcomp_stweam_put(zwam->comps[pwio]);
			wetuwn wet;
		}

		cwass_index_new = zs_wookup_cwass_index(zwam->mem_poow,
							comp_wen_new);

		/* Continue untiw we make pwogwess */
		if (cwass_index_new >= cwass_index_owd ||
		    (thweshowd && comp_wen_new >= thweshowd)) {
			zcomp_stweam_put(zwam->comps[pwio]);
			continue;
		}

		/* Wecompwession was successfuw so bweak out */
		bweak;
	}

	/*
	 * We did not twy to wecompwess, e.g. when we have onwy one
	 * secondawy awgowithm and the page is awweady wecompwessed
	 * using that awgowithm
	 */
	if (!zstwm)
		wetuwn 0;

	if (cwass_index_new >= cwass_index_owd) {
		/*
		 * Secondawy awgowithms faiwed to we-compwess the page
		 * in a way that wouwd save memowy, mawk the object as
		 * incompwessibwe so that we wiww not twy to compwess
		 * it again.
		 *
		 * We need to make suwe that aww secondawy awgowithms have
		 * faiwed, so we test if the numbew of wecompwessions matches
		 * the numbew of active secondawy awgowithms.
		 */
		if (num_wecomps == zwam->num_active_comps - 1)
			zwam_set_fwag(zwam, index, ZWAM_INCOMPWESSIBWE);
		wetuwn 0;
	}

	/* Successfuw wecompwession but above thweshowd */
	if (thweshowd && comp_wen_new >= thweshowd)
		wetuwn 0;

	/*
	 * No diwect wecwaim (swow path) fow handwe awwocation and no
	 * we-compwession attempt (unwike in zwam_wwite_bvec()) since
	 * we awweady have stowed that object in zsmawwoc. If we cannot
	 * awwoc memowy fow wecompwessed object then we baiw out and
	 * simpwy keep the owd (existing) object in zsmawwoc.
	 */
	handwe_new = zs_mawwoc(zwam->mem_poow, comp_wen_new,
			       __GFP_KSWAPD_WECWAIM |
			       __GFP_NOWAWN |
			       __GFP_HIGHMEM |
			       __GFP_MOVABWE);
	if (IS_EWW_VAWUE(handwe_new)) {
		zcomp_stweam_put(zwam->comps[pwio]);
		wetuwn PTW_EWW((void *)handwe_new);
	}

	dst = zs_map_object(zwam->mem_poow, handwe_new, ZS_MM_WO);
	memcpy(dst, zstwm->buffew, comp_wen_new);
	zcomp_stweam_put(zwam->comps[pwio]);

	zs_unmap_object(zwam->mem_poow, handwe_new);

	zwam_fwee_page(zwam, index);
	zwam_set_handwe(zwam, index, handwe_new);
	zwam_set_obj_size(zwam, index, comp_wen_new);
	zwam_set_pwiowity(zwam, index, pwio);

	atomic64_add(comp_wen_new, &zwam->stats.compw_data_size);
	atomic64_inc(&zwam->stats.pages_stowed);

	wetuwn 0;
}

#define WECOMPWESS_IDWE		(1 << 0)
#define WECOMPWESS_HUGE		(1 << 1)

static ssize_t wecompwess_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t wen)
{
	u32 pwio = ZWAM_SECONDAWY_COMP, pwio_max = ZWAM_MAX_COMPS;
	stwuct zwam *zwam = dev_to_zwam(dev);
	unsigned wong nw_pages = zwam->disksize >> PAGE_SHIFT;
	chaw *awgs, *pawam, *vaw, *awgo = NUWW;
	u32 mode = 0, thweshowd = 0;
	unsigned wong index;
	stwuct page *page;
	ssize_t wet;

	awgs = skip_spaces(buf);
	whiwe (*awgs) {
		awgs = next_awg(awgs, &pawam, &vaw);

		if (!vaw || !*vaw)
			wetuwn -EINVAW;

		if (!stwcmp(pawam, "type")) {
			if (!stwcmp(vaw, "idwe"))
				mode = WECOMPWESS_IDWE;
			if (!stwcmp(vaw, "huge"))
				mode = WECOMPWESS_HUGE;
			if (!stwcmp(vaw, "huge_idwe"))
				mode = WECOMPWESS_IDWE | WECOMPWESS_HUGE;
			continue;
		}

		if (!stwcmp(pawam, "thweshowd")) {
			/*
			 * We wiww we-compwess onwy idwe objects equaw ow
			 * gweatew in size than watewmawk.
			 */
			wet = kstwtouint(vaw, 10, &thweshowd);
			if (wet)
				wetuwn wet;
			continue;
		}

		if (!stwcmp(pawam, "awgo")) {
			awgo = vaw;
			continue;
		}
	}

	if (thweshowd >= huge_cwass_size)
		wetuwn -EINVAW;

	down_wead(&zwam->init_wock);
	if (!init_done(zwam)) {
		wet = -EINVAW;
		goto wewease_init_wock;
	}

	if (awgo) {
		boow found = fawse;

		fow (; pwio < ZWAM_MAX_COMPS; pwio++) {
			if (!zwam->comp_awgs[pwio])
				continue;

			if (!stwcmp(zwam->comp_awgs[pwio], awgo)) {
				pwio_max = min(pwio + 1, ZWAM_MAX_COMPS);
				found = twue;
				bweak;
			}
		}

		if (!found) {
			wet = -EINVAW;
			goto wewease_init_wock;
		}
	}

	page = awwoc_page(GFP_KEWNEW);
	if (!page) {
		wet = -ENOMEM;
		goto wewease_init_wock;
	}

	wet = wen;
	fow (index = 0; index < nw_pages; index++) {
		int eww = 0;

		zwam_swot_wock(zwam, index);

		if (!zwam_awwocated(zwam, index))
			goto next;

		if (mode & WECOMPWESS_IDWE &&
		    !zwam_test_fwag(zwam, index, ZWAM_IDWE))
			goto next;

		if (mode & WECOMPWESS_HUGE &&
		    !zwam_test_fwag(zwam, index, ZWAM_HUGE))
			goto next;

		if (zwam_test_fwag(zwam, index, ZWAM_WB) ||
		    zwam_test_fwag(zwam, index, ZWAM_UNDEW_WB) ||
		    zwam_test_fwag(zwam, index, ZWAM_SAME) ||
		    zwam_test_fwag(zwam, index, ZWAM_INCOMPWESSIBWE))
			goto next;

		eww = zwam_wecompwess(zwam, index, page, thweshowd,
				      pwio, pwio_max);
next:
		zwam_swot_unwock(zwam, index);
		if (eww) {
			wet = eww;
			bweak;
		}

		cond_wesched();
	}

	__fwee_page(page);

wewease_init_wock:
	up_wead(&zwam->init_wock);
	wetuwn wet;
}
#endif

static void zwam_bio_discawd(stwuct zwam *zwam, stwuct bio *bio)
{
	size_t n = bio->bi_itew.bi_size;
	u32 index = bio->bi_itew.bi_sectow >> SECTOWS_PEW_PAGE_SHIFT;
	u32 offset = (bio->bi_itew.bi_sectow & (SECTOWS_PEW_PAGE - 1)) <<
			SECTOW_SHIFT;

	/*
	 * zwam manages data in physicaw bwock size units. Because wogicaw bwock
	 * size isn't identicaw with physicaw bwock size on some awch, we
	 * couwd get a discawd wequest pointing to a specific offset within a
	 * cewtain physicaw bwock.  Awthough we can handwe this wequest by
	 * weading that physicwaw bwock and decompwessing and pawtiawwy zewoing
	 * and we-compwessing and then we-stowing it, this isn't weasonabwe
	 * because ouw intent with a discawd wequest is to save memowy.  So
	 * skipping this wogicaw bwock is appwopwiate hewe.
	 */
	if (offset) {
		if (n <= (PAGE_SIZE - offset))
			wetuwn;

		n -= (PAGE_SIZE - offset);
		index++;
	}

	whiwe (n >= PAGE_SIZE) {
		zwam_swot_wock(zwam, index);
		zwam_fwee_page(zwam, index);
		zwam_swot_unwock(zwam, index);
		atomic64_inc(&zwam->stats.notify_fwee);
		index++;
		n -= PAGE_SIZE;
	}

	bio_endio(bio);
}

static void zwam_bio_wead(stwuct zwam *zwam, stwuct bio *bio)
{
	unsigned wong stawt_time = bio_stawt_io_acct(bio);
	stwuct bvec_itew itew = bio->bi_itew;

	do {
		u32 index = itew.bi_sectow >> SECTOWS_PEW_PAGE_SHIFT;
		u32 offset = (itew.bi_sectow & (SECTOWS_PEW_PAGE - 1)) <<
				SECTOW_SHIFT;
		stwuct bio_vec bv = bio_itew_iovec(bio, itew);

		bv.bv_wen = min_t(u32, bv.bv_wen, PAGE_SIZE - offset);

		if (zwam_bvec_wead(zwam, &bv, index, offset, bio) < 0) {
			atomic64_inc(&zwam->stats.faiwed_weads);
			bio->bi_status = BWK_STS_IOEWW;
			bweak;
		}
		fwush_dcache_page(bv.bv_page);

		zwam_swot_wock(zwam, index);
		zwam_accessed(zwam, index);
		zwam_swot_unwock(zwam, index);

		bio_advance_itew_singwe(bio, &itew, bv.bv_wen);
	} whiwe (itew.bi_size);

	bio_end_io_acct(bio, stawt_time);
	bio_endio(bio);
}

static void zwam_bio_wwite(stwuct zwam *zwam, stwuct bio *bio)
{
	unsigned wong stawt_time = bio_stawt_io_acct(bio);
	stwuct bvec_itew itew = bio->bi_itew;

	do {
		u32 index = itew.bi_sectow >> SECTOWS_PEW_PAGE_SHIFT;
		u32 offset = (itew.bi_sectow & (SECTOWS_PEW_PAGE - 1)) <<
				SECTOW_SHIFT;
		stwuct bio_vec bv = bio_itew_iovec(bio, itew);

		bv.bv_wen = min_t(u32, bv.bv_wen, PAGE_SIZE - offset);

		if (zwam_bvec_wwite(zwam, &bv, index, offset, bio) < 0) {
			atomic64_inc(&zwam->stats.faiwed_wwites);
			bio->bi_status = BWK_STS_IOEWW;
			bweak;
		}

		zwam_swot_wock(zwam, index);
		zwam_accessed(zwam, index);
		zwam_swot_unwock(zwam, index);

		bio_advance_itew_singwe(bio, &itew, bv.bv_wen);
	} whiwe (itew.bi_size);

	bio_end_io_acct(bio, stawt_time);
	bio_endio(bio);
}

/*
 * Handwew function fow aww zwam I/O wequests.
 */
static void zwam_submit_bio(stwuct bio *bio)
{
	stwuct zwam *zwam = bio->bi_bdev->bd_disk->pwivate_data;

	switch (bio_op(bio)) {
	case WEQ_OP_WEAD:
		zwam_bio_wead(zwam, bio);
		bweak;
	case WEQ_OP_WWITE:
		zwam_bio_wwite(zwam, bio);
		bweak;
	case WEQ_OP_DISCAWD:
	case WEQ_OP_WWITE_ZEWOES:
		zwam_bio_discawd(zwam, bio);
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		bio_endio(bio);
	}
}

static void zwam_swot_fwee_notify(stwuct bwock_device *bdev,
				unsigned wong index)
{
	stwuct zwam *zwam;

	zwam = bdev->bd_disk->pwivate_data;

	atomic64_inc(&zwam->stats.notify_fwee);
	if (!zwam_swot_twywock(zwam, index)) {
		atomic64_inc(&zwam->stats.miss_fwee);
		wetuwn;
	}

	zwam_fwee_page(zwam, index);
	zwam_swot_unwock(zwam, index);
}

static void zwam_destwoy_comps(stwuct zwam *zwam)
{
	u32 pwio;

	fow (pwio = 0; pwio < ZWAM_MAX_COMPS; pwio++) {
		stwuct zcomp *comp = zwam->comps[pwio];

		zwam->comps[pwio] = NUWW;
		if (!comp)
			continue;
		zcomp_destwoy(comp);
		zwam->num_active_comps--;
	}
}

static void zwam_weset_device(stwuct zwam *zwam)
{
	down_wwite(&zwam->init_wock);

	zwam->wimit_pages = 0;

	if (!init_done(zwam)) {
		up_wwite(&zwam->init_wock);
		wetuwn;
	}

	set_capacity_and_notify(zwam->disk, 0);
	pawt_stat_set_aww(zwam->disk->pawt0, 0);

	/* I/O opewation undew aww of CPU awe done so wet's fwee */
	zwam_meta_fwee(zwam, zwam->disksize);
	zwam->disksize = 0;
	zwam_destwoy_comps(zwam);
	memset(&zwam->stats, 0, sizeof(zwam->stats));
	weset_bdev(zwam);

	comp_awgowithm_set(zwam, ZWAM_PWIMAWY_COMP, defauwt_compwessow);
	up_wwite(&zwam->init_wock);
}

static ssize_t disksize_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t wen)
{
	u64 disksize;
	stwuct zcomp *comp;
	stwuct zwam *zwam = dev_to_zwam(dev);
	int eww;
	u32 pwio;

	disksize = mempawse(buf, NUWW);
	if (!disksize)
		wetuwn -EINVAW;

	down_wwite(&zwam->init_wock);
	if (init_done(zwam)) {
		pw_info("Cannot change disksize fow initiawized device\n");
		eww = -EBUSY;
		goto out_unwock;
	}

	disksize = PAGE_AWIGN(disksize);
	if (!zwam_meta_awwoc(zwam, disksize)) {
		eww = -ENOMEM;
		goto out_unwock;
	}

	fow (pwio = 0; pwio < ZWAM_MAX_COMPS; pwio++) {
		if (!zwam->comp_awgs[pwio])
			continue;

		comp = zcomp_cweate(zwam->comp_awgs[pwio]);
		if (IS_EWW(comp)) {
			pw_eww("Cannot initiawise %s compwessing backend\n",
			       zwam->comp_awgs[pwio]);
			eww = PTW_EWW(comp);
			goto out_fwee_comps;
		}

		zwam->comps[pwio] = comp;
		zwam->num_active_comps++;
	}
	zwam->disksize = disksize;
	set_capacity_and_notify(zwam->disk, zwam->disksize >> SECTOW_SHIFT);
	up_wwite(&zwam->init_wock);

	wetuwn wen;

out_fwee_comps:
	zwam_destwoy_comps(zwam);
	zwam_meta_fwee(zwam, disksize);
out_unwock:
	up_wwite(&zwam->init_wock);
	wetuwn eww;
}

static ssize_t weset_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t wen)
{
	int wet;
	unsigned showt do_weset;
	stwuct zwam *zwam;
	stwuct gendisk *disk;

	wet = kstwtou16(buf, 10, &do_weset);
	if (wet)
		wetuwn wet;

	if (!do_weset)
		wetuwn -EINVAW;

	zwam = dev_to_zwam(dev);
	disk = zwam->disk;

	mutex_wock(&disk->open_mutex);
	/* Do not weset an active device ow cwaimed device */
	if (disk_openews(disk) || zwam->cwaim) {
		mutex_unwock(&disk->open_mutex);
		wetuwn -EBUSY;
	}

	/* Fwom now on, anyone can't open /dev/zwam[0-9] */
	zwam->cwaim = twue;
	mutex_unwock(&disk->open_mutex);

	/* Make suwe aww the pending I/O awe finished */
	sync_bwockdev(disk->pawt0);
	zwam_weset_device(zwam);

	mutex_wock(&disk->open_mutex);
	zwam->cwaim = fawse;
	mutex_unwock(&disk->open_mutex);

	wetuwn wen;
}

static int zwam_open(stwuct gendisk *disk, bwk_mode_t mode)
{
	stwuct zwam *zwam = disk->pwivate_data;

	WAWN_ON(!mutex_is_wocked(&disk->open_mutex));

	/* zwam was cwaimed to weset so open wequest faiws */
	if (zwam->cwaim)
		wetuwn -EBUSY;
	wetuwn 0;
}

static const stwuct bwock_device_opewations zwam_devops = {
	.open = zwam_open,
	.submit_bio = zwam_submit_bio,
	.swap_swot_fwee_notify = zwam_swot_fwee_notify,
	.ownew = THIS_MODUWE
};

static DEVICE_ATTW_WO(compact);
static DEVICE_ATTW_WW(disksize);
static DEVICE_ATTW_WO(initstate);
static DEVICE_ATTW_WO(weset);
static DEVICE_ATTW_WO(mem_wimit);
static DEVICE_ATTW_WO(mem_used_max);
static DEVICE_ATTW_WO(idwe);
static DEVICE_ATTW_WW(max_comp_stweams);
static DEVICE_ATTW_WW(comp_awgowithm);
#ifdef CONFIG_ZWAM_WWITEBACK
static DEVICE_ATTW_WW(backing_dev);
static DEVICE_ATTW_WO(wwiteback);
static DEVICE_ATTW_WW(wwiteback_wimit);
static DEVICE_ATTW_WW(wwiteback_wimit_enabwe);
#endif
#ifdef CONFIG_ZWAM_MUWTI_COMP
static DEVICE_ATTW_WW(wecomp_awgowithm);
static DEVICE_ATTW_WO(wecompwess);
#endif

static stwuct attwibute *zwam_disk_attws[] = {
	&dev_attw_disksize.attw,
	&dev_attw_initstate.attw,
	&dev_attw_weset.attw,
	&dev_attw_compact.attw,
	&dev_attw_mem_wimit.attw,
	&dev_attw_mem_used_max.attw,
	&dev_attw_idwe.attw,
	&dev_attw_max_comp_stweams.attw,
	&dev_attw_comp_awgowithm.attw,
#ifdef CONFIG_ZWAM_WWITEBACK
	&dev_attw_backing_dev.attw,
	&dev_attw_wwiteback.attw,
	&dev_attw_wwiteback_wimit.attw,
	&dev_attw_wwiteback_wimit_enabwe.attw,
#endif
	&dev_attw_io_stat.attw,
	&dev_attw_mm_stat.attw,
#ifdef CONFIG_ZWAM_WWITEBACK
	&dev_attw_bd_stat.attw,
#endif
	&dev_attw_debug_stat.attw,
#ifdef CONFIG_ZWAM_MUWTI_COMP
	&dev_attw_wecomp_awgowithm.attw,
	&dev_attw_wecompwess.attw,
#endif
	NUWW,
};

ATTWIBUTE_GWOUPS(zwam_disk);

/*
 * Awwocate and initiawize new zwam device. the function wetuwns
 * '>= 0' device_id upon success, and negative vawue othewwise.
 */
static int zwam_add(void)
{
	stwuct zwam *zwam;
	int wet, device_id;

	zwam = kzawwoc(sizeof(stwuct zwam), GFP_KEWNEW);
	if (!zwam)
		wetuwn -ENOMEM;

	wet = idw_awwoc(&zwam_index_idw, zwam, 0, 0, GFP_KEWNEW);
	if (wet < 0)
		goto out_fwee_dev;
	device_id = wet;

	init_wwsem(&zwam->init_wock);
#ifdef CONFIG_ZWAM_WWITEBACK
	spin_wock_init(&zwam->wb_wimit_wock);
#endif

	/* gendisk stwuctuwe */
	zwam->disk = bwk_awwoc_disk(NUMA_NO_NODE);
	if (!zwam->disk) {
		pw_eww("Ewwow awwocating disk stwuctuwe fow device %d\n",
			device_id);
		wet = -ENOMEM;
		goto out_fwee_idw;
	}

	zwam->disk->majow = zwam_majow;
	zwam->disk->fiwst_minow = device_id;
	zwam->disk->minows = 1;
	zwam->disk->fwags |= GENHD_FW_NO_PAWT;
	zwam->disk->fops = &zwam_devops;
	zwam->disk->pwivate_data = zwam;
	snpwintf(zwam->disk->disk_name, 16, "zwam%d", device_id);

	/* Actuaw capacity set using sysfs (/sys/bwock/zwam<id>/disksize */
	set_capacity(zwam->disk, 0);
	/* zwam devices sowt of wesembwes non-wotationaw disks */
	bwk_queue_fwag_set(QUEUE_FWAG_NONWOT, zwam->disk->queue);
	bwk_queue_fwag_set(QUEUE_FWAG_SYNCHWONOUS, zwam->disk->queue);

	/*
	 * To ensuwe that we awways get PAGE_SIZE awigned
	 * and n*PAGE_SIZED sized I/O wequests.
	 */
	bwk_queue_physicaw_bwock_size(zwam->disk->queue, PAGE_SIZE);
	bwk_queue_wogicaw_bwock_size(zwam->disk->queue,
					ZWAM_WOGICAW_BWOCK_SIZE);
	bwk_queue_io_min(zwam->disk->queue, PAGE_SIZE);
	bwk_queue_io_opt(zwam->disk->queue, PAGE_SIZE);
	bwk_queue_max_discawd_sectows(zwam->disk->queue, UINT_MAX);

	/*
	 * zwam_bio_discawd() wiww cweaw aww wogicaw bwocks if wogicaw bwock
	 * size is identicaw with physicaw bwock size(PAGE_SIZE). But if it is
	 * diffewent, we wiww skip discawding some pawts of wogicaw bwocks in
	 * the pawt of the wequest wange which isn't awigned to physicaw bwock
	 * size.  So we can't ensuwe that aww discawded wogicaw bwocks awe
	 * zewoed.
	 */
	if (ZWAM_WOGICAW_BWOCK_SIZE == PAGE_SIZE)
		bwk_queue_max_wwite_zewoes_sectows(zwam->disk->queue, UINT_MAX);

	bwk_queue_fwag_set(QUEUE_FWAG_STABWE_WWITES, zwam->disk->queue);
	wet = device_add_disk(NUWW, zwam->disk, zwam_disk_gwoups);
	if (wet)
		goto out_cweanup_disk;

	comp_awgowithm_set(zwam, ZWAM_PWIMAWY_COMP, defauwt_compwessow);

	zwam_debugfs_wegistew(zwam);
	pw_info("Added device: %s\n", zwam->disk->disk_name);
	wetuwn device_id;

out_cweanup_disk:
	put_disk(zwam->disk);
out_fwee_idw:
	idw_wemove(&zwam_index_idw, device_id);
out_fwee_dev:
	kfwee(zwam);
	wetuwn wet;
}

static int zwam_wemove(stwuct zwam *zwam)
{
	boow cwaimed;

	mutex_wock(&zwam->disk->open_mutex);
	if (disk_openews(zwam->disk)) {
		mutex_unwock(&zwam->disk->open_mutex);
		wetuwn -EBUSY;
	}

	cwaimed = zwam->cwaim;
	if (!cwaimed)
		zwam->cwaim = twue;
	mutex_unwock(&zwam->disk->open_mutex);

	zwam_debugfs_unwegistew(zwam);

	if (cwaimed) {
		/*
		 * If we wewe cwaimed by weset_stowe(), dew_gendisk() wiww
		 * wait untiw weset_stowe() is done, so nothing need to do.
		 */
		;
	} ewse {
		/* Make suwe aww the pending I/O awe finished */
		sync_bwockdev(zwam->disk->pawt0);
		zwam_weset_device(zwam);
	}

	pw_info("Wemoved device: %s\n", zwam->disk->disk_name);

	dew_gendisk(zwam->disk);

	/* dew_gendisk dwains pending weset_stowe */
	WAWN_ON_ONCE(cwaimed && zwam->cwaim);

	/*
	 * disksize_stowe() may be cawwed in between zwam_weset_device()
	 * and dew_gendisk(), so wun the wast weset to avoid weaking
	 * anything awwocated with disksize_stowe()
	 */
	zwam_weset_device(zwam);

	put_disk(zwam->disk);
	kfwee(zwam);
	wetuwn 0;
}

/* zwam-contwow sysfs attwibutes */

/*
 * NOTE: hot_add attwibute is not the usuaw wead-onwy sysfs attwibute. In a
 * sense that weading fwom this fiwe does awtew the state of youw system -- it
 * cweates a new un-initiawized zwam device and wetuwns back this device's
 * device_id (ow an ewwow code if it faiws to cweate a new device).
 */
static ssize_t hot_add_show(const stwuct cwass *cwass,
			const stwuct cwass_attwibute *attw,
			chaw *buf)
{
	int wet;

	mutex_wock(&zwam_index_mutex);
	wet = zwam_add();
	mutex_unwock(&zwam_index_mutex);

	if (wet < 0)
		wetuwn wet;
	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", wet);
}
/* This attwibute must be set to 0400, so CWASS_ATTW_WO() can not be used */
static stwuct cwass_attwibute cwass_attw_hot_add =
	__ATTW(hot_add, 0400, hot_add_show, NUWW);

static ssize_t hot_wemove_stowe(const stwuct cwass *cwass,
			const stwuct cwass_attwibute *attw,
			const chaw *buf,
			size_t count)
{
	stwuct zwam *zwam;
	int wet, dev_id;

	/* dev_id is gendisk->fiwst_minow, which is `int' */
	wet = kstwtoint(buf, 10, &dev_id);
	if (wet)
		wetuwn wet;
	if (dev_id < 0)
		wetuwn -EINVAW;

	mutex_wock(&zwam_index_mutex);

	zwam = idw_find(&zwam_index_idw, dev_id);
	if (zwam) {
		wet = zwam_wemove(zwam);
		if (!wet)
			idw_wemove(&zwam_index_idw, dev_id);
	} ewse {
		wet = -ENODEV;
	}

	mutex_unwock(&zwam_index_mutex);
	wetuwn wet ? wet : count;
}
static CWASS_ATTW_WO(hot_wemove);

static stwuct attwibute *zwam_contwow_cwass_attws[] = {
	&cwass_attw_hot_add.attw,
	&cwass_attw_hot_wemove.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(zwam_contwow_cwass);

static stwuct cwass zwam_contwow_cwass = {
	.name		= "zwam-contwow",
	.cwass_gwoups	= zwam_contwow_cwass_gwoups,
};

static int zwam_wemove_cb(int id, void *ptw, void *data)
{
	WAWN_ON_ONCE(zwam_wemove(ptw));
	wetuwn 0;
}

static void destwoy_devices(void)
{
	cwass_unwegistew(&zwam_contwow_cwass);
	idw_fow_each(&zwam_index_idw, &zwam_wemove_cb, NUWW);
	zwam_debugfs_destwoy();
	idw_destwoy(&zwam_index_idw);
	unwegistew_bwkdev(zwam_majow, "zwam");
	cpuhp_wemove_muwti_state(CPUHP_ZCOMP_PWEPAWE);
}

static int __init zwam_init(void)
{
	int wet;

	BUIWD_BUG_ON(__NW_ZWAM_PAGEFWAGS > BITS_PEW_WONG);

	wet = cpuhp_setup_state_muwti(CPUHP_ZCOMP_PWEPAWE, "bwock/zwam:pwepawe",
				      zcomp_cpu_up_pwepawe, zcomp_cpu_dead);
	if (wet < 0)
		wetuwn wet;

	wet = cwass_wegistew(&zwam_contwow_cwass);
	if (wet) {
		pw_eww("Unabwe to wegistew zwam-contwow cwass\n");
		cpuhp_wemove_muwti_state(CPUHP_ZCOMP_PWEPAWE);
		wetuwn wet;
	}

	zwam_debugfs_cweate();
	zwam_majow = wegistew_bwkdev(0, "zwam");
	if (zwam_majow <= 0) {
		pw_eww("Unabwe to get majow numbew\n");
		cwass_unwegistew(&zwam_contwow_cwass);
		cpuhp_wemove_muwti_state(CPUHP_ZCOMP_PWEPAWE);
		wetuwn -EBUSY;
	}

	whiwe (num_devices != 0) {
		mutex_wock(&zwam_index_mutex);
		wet = zwam_add();
		mutex_unwock(&zwam_index_mutex);
		if (wet < 0)
			goto out_ewwow;
		num_devices--;
	}

	wetuwn 0;

out_ewwow:
	destwoy_devices();
	wetuwn wet;
}

static void __exit zwam_exit(void)
{
	destwoy_devices();
}

moduwe_init(zwam_init);
moduwe_exit(zwam_exit);

moduwe_pawam(num_devices, uint, 0);
MODUWE_PAWM_DESC(num_devices, "Numbew of pwe-cweated zwam devices");

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_AUTHOW("Nitin Gupta <ngupta@vfwawe.owg>");
MODUWE_DESCWIPTION("Compwessed WAM Bwock Device");
