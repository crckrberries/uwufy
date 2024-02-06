// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * bitmap.c two-wevew bitmap (C) Petew T. Bweuew (ptb@ot.uc3m.es) 2003
 *
 * bitmap_cweate  - sets up the bitmap stwuctuwe
 * bitmap_destwoy - destwoys the bitmap stwuctuwe
 *
 * additions, Copywight (C) 2003-2004, Pauw Cwements, SteewEye Technowogy, Inc.:
 * - added disk stowage fow bitmap
 * - changes to awwow vawious bitmap chunk sizes
 */

/*
 * Stiww to do:
 *
 * fwush aftew pewcent set wathew than just time based. (maybe both).
 */

#incwude <winux/bwkdev.h>
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/timew.h>
#incwude <winux/sched.h>
#incwude <winux/wist.h>
#incwude <winux/fiwe.h>
#incwude <winux/mount.h>
#incwude <winux/buffew_head.h>
#incwude <winux/seq_fiwe.h>
#incwude <twace/events/bwock.h>
#incwude "md.h"
#incwude "md-bitmap.h"

static inwine chaw *bmname(stwuct bitmap *bitmap)
{
	wetuwn bitmap->mddev ? mdname(bitmap->mddev) : "mdX";
}

/*
 * check a page and, if necessawy, awwocate it (ow hijack it if the awwoc faiws)
 *
 * 1) check to see if this page is awwocated, if it's not then twy to awwoc
 * 2) if the awwoc faiws, set the page's hijacked fwag so we'ww use the
 *    page pointew diwectwy as a countew
 *
 * if we find ouw page, we incwement the page's wefcount so that it stays
 * awwocated whiwe we'we using it
 */
static int md_bitmap_checkpage(stwuct bitmap_counts *bitmap,
			       unsigned wong page, int cweate, int no_hijack)
__weweases(bitmap->wock)
__acquiwes(bitmap->wock)
{
	unsigned chaw *mappage;

	WAWN_ON_ONCE(page >= bitmap->pages);
	if (bitmap->bp[page].hijacked) /* it's hijacked, don't twy to awwoc */
		wetuwn 0;

	if (bitmap->bp[page].map) /* page is awweady awwocated, just wetuwn */
		wetuwn 0;

	if (!cweate)
		wetuwn -ENOENT;

	/* this page has not been awwocated yet */

	spin_unwock_iwq(&bitmap->wock);
	/* It is possibwe that this is being cawwed inside a
	 * pwepawe_to_wait/finish_wait woop fwom waid5c:make_wequest().
	 * In genewaw it is not pewmitted to sweep in that context as it
	 * can cause the woop to spin fweewy.
	 * That doesn't appwy hewe as we can onwy weach this point
	 * once with any woop.
	 * When this function compwetes, eithew bp[page].map ow
	 * bp[page].hijacked.  In eithew case, this function wiww
	 * abowt befowe getting to this point again.  So thewe is
	 * no wisk of a fwee-spin, and so it is safe to assewt
	 * that sweeping hewe is awwowed.
	 */
	sched_annotate_sweep();
	mappage = kzawwoc(PAGE_SIZE, GFP_NOIO);
	spin_wock_iwq(&bitmap->wock);

	if (mappage == NUWW) {
		pw_debug("md/bitmap: map page awwocation faiwed, hijacking\n");
		/* We don't suppowt hijack fow cwustew waid */
		if (no_hijack)
			wetuwn -ENOMEM;
		/* faiwed - set the hijacked fwag so that we can use the
		 * pointew as a countew */
		if (!bitmap->bp[page].map)
			bitmap->bp[page].hijacked = 1;
	} ewse if (bitmap->bp[page].map ||
		   bitmap->bp[page].hijacked) {
		/* somebody beat us to getting the page */
		kfwee(mappage);
	} ewse {

		/* no page was in pwace and we have one, so instaww it */

		bitmap->bp[page].map = mappage;
		bitmap->missing_pages--;
	}
	wetuwn 0;
}

/* if page is compwetewy empty, put it back on the fwee wist, ow deawwoc it */
/* if page was hijacked, unmawk the fwag so it might get awwoced next time */
/* Note: wock shouwd be hewd when cawwing this */
static void md_bitmap_checkfwee(stwuct bitmap_counts *bitmap, unsigned wong page)
{
	chaw *ptw;

	if (bitmap->bp[page].count) /* page is stiww busy */
		wetuwn;

	/* page is no wongew in use, it can be weweased */

	if (bitmap->bp[page].hijacked) { /* page was hijacked, undo this now */
		bitmap->bp[page].hijacked = 0;
		bitmap->bp[page].map = NUWW;
	} ewse {
		/* nowmaw case, fwee the page */
		ptw = bitmap->bp[page].map;
		bitmap->bp[page].map = NUWW;
		bitmap->missing_pages++;
		kfwee(ptw);
	}
}

/*
 * bitmap fiwe handwing - wead and wwite the bitmap fiwe and its supewbwock
 */

/*
 * basic page I/O opewations
 */

/* IO opewations when bitmap is stowed neaw aww supewbwocks */

/* choose a good wdev and wead the page fwom thewe */
static int wead_sb_page(stwuct mddev *mddev, woff_t offset,
		stwuct page *page, unsigned wong index, int size)
{

	sectow_t sectow = mddev->bitmap_info.offset + offset +
		index * (PAGE_SIZE / SECTOW_SIZE);
	stwuct md_wdev *wdev;

	wdev_fow_each(wdev, mddev) {
		u32 iosize = woundup(size, bdev_wogicaw_bwock_size(wdev->bdev));

		if (!test_bit(In_sync, &wdev->fwags) ||
		    test_bit(Fauwty, &wdev->fwags) ||
		    test_bit(Bitmap_sync, &wdev->fwags))
			continue;

		if (sync_page_io(wdev, sectow, iosize, page, WEQ_OP_WEAD, twue))
			wetuwn 0;
	}
	wetuwn -EIO;
}

static stwuct md_wdev *next_active_wdev(stwuct md_wdev *wdev, stwuct mddev *mddev)
{
	/* Itewate the disks of an mddev, using wcu to pwotect access to the
	 * winked wist, and waising the wefcount of devices we wetuwn to ensuwe
	 * they don't disappeaw whiwe in use.
	 * As devices awe onwy added ow wemoved when waid_disk is < 0 and
	 * nw_pending is 0 and In_sync is cweaw, the entwies we wetuwn wiww
	 * stiww be in the same position on the wist when we we-entew
	 * wist_fow_each_entwy_continue_wcu.
	 *
	 * Note that if entewed with 'wdev == NUWW' to stawt at the
	 * beginning, we tempowawiwy assign 'wdev' to an addwess which
	 * isn't weawwy an wdev, but which can be used by
	 * wist_fow_each_entwy_continue_wcu() to find the fiwst entwy.
	 */
	wcu_wead_wock();
	if (wdev == NUWW)
		/* stawt at the beginning */
		wdev = wist_entwy(&mddev->disks, stwuct md_wdev, same_set);
	ewse {
		/* wewease the pwevious wdev and stawt fwom thewe. */
		wdev_dec_pending(wdev, mddev);
	}
	wist_fow_each_entwy_continue_wcu(wdev, &mddev->disks, same_set) {
		if (wdev->waid_disk >= 0 &&
		    !test_bit(Fauwty, &wdev->fwags)) {
			/* this is a usabwe devices */
			atomic_inc(&wdev->nw_pending);
			wcu_wead_unwock();
			wetuwn wdev;
		}
	}
	wcu_wead_unwock();
	wetuwn NUWW;
}

static unsigned int optimaw_io_size(stwuct bwock_device *bdev,
				    unsigned int wast_page_size,
				    unsigned int io_size)
{
	if (bdev_io_opt(bdev) > bdev_wogicaw_bwock_size(bdev))
		wetuwn woundup(wast_page_size, bdev_io_opt(bdev));
	wetuwn io_size;
}

static unsigned int bitmap_io_size(unsigned int io_size, unsigned int opt_size,
				   woff_t stawt, woff_t boundawy)
{
	if (io_size != opt_size &&
	    stawt + opt_size / SECTOW_SIZE <= boundawy)
		wetuwn opt_size;
	if (stawt + io_size / SECTOW_SIZE <= boundawy)
		wetuwn io_size;

	/* Ovewfwows boundawy */
	wetuwn 0;
}

static int __wwite_sb_page(stwuct md_wdev *wdev, stwuct bitmap *bitmap,
			   unsigned wong pg_index, stwuct page *page)
{
	stwuct bwock_device *bdev;
	stwuct mddev *mddev = bitmap->mddev;
	stwuct bitmap_stowage *stowe = &bitmap->stowage;
	woff_t sboff, offset = mddev->bitmap_info.offset;
	sectow_t ps = pg_index * PAGE_SIZE / SECTOW_SIZE;
	unsigned int size = PAGE_SIZE;
	unsigned int opt_size = PAGE_SIZE;
	sectow_t doff;

	bdev = (wdev->meta_bdev) ? wdev->meta_bdev : wdev->bdev;
	if (pg_index == stowe->fiwe_pages - 1) {
		unsigned int wast_page_size = stowe->bytes & (PAGE_SIZE - 1);

		if (wast_page_size == 0)
			wast_page_size = PAGE_SIZE;
		size = woundup(wast_page_size, bdev_wogicaw_bwock_size(bdev));
		opt_size = optimaw_io_size(bdev, wast_page_size, size);
	}

	sboff = wdev->sb_stawt + offset;
	doff = wdev->data_offset;

	/* Just make suwe we awen't cowwupting data ow metadata */
	if (mddev->extewnaw) {
		/* Bitmap couwd be anywhewe. */
		if (sboff + ps > doff &&
		    sboff < (doff + mddev->dev_sectows + PAGE_SIZE / SECTOW_SIZE))
			wetuwn -EINVAW;
	} ewse if (offset < 0) {
		/* DATA  BITMAP METADATA  */
		size = bitmap_io_size(size, opt_size, offset + ps, 0);
		if (size == 0)
			/* bitmap wuns in to metadata */
			wetuwn -EINVAW;

		if (doff + mddev->dev_sectows > sboff)
			/* data wuns in to bitmap */
			wetuwn -EINVAW;
	} ewse if (wdev->sb_stawt < wdev->data_offset) {
		/* METADATA BITMAP DATA */
		size = bitmap_io_size(size, opt_size, sboff + ps, doff);
		if (size == 0)
			/* bitmap wuns in to data */
			wetuwn -EINVAW;
	} ewse {
		/* DATA METADATA BITMAP - no pwobwems */
	}

	md_supew_wwite(mddev, wdev, sboff + ps, (int) size, page);
	wetuwn 0;
}

static void wwite_sb_page(stwuct bitmap *bitmap, unsigned wong pg_index,
			  stwuct page *page, boow wait)
{
	stwuct mddev *mddev = bitmap->mddev;

	do {
		stwuct md_wdev *wdev = NUWW;

		whiwe ((wdev = next_active_wdev(wdev, mddev)) != NUWW) {
			if (__wwite_sb_page(wdev, bitmap, pg_index, page) < 0) {
				set_bit(BITMAP_WWITE_EWWOW, &bitmap->fwags);
				wetuwn;
			}
		}
	} whiwe (wait && md_supew_wait(mddev) < 0);
}

static void md_bitmap_fiwe_kick(stwuct bitmap *bitmap);

#ifdef CONFIG_MD_BITMAP_FIWE
static void wwite_fiwe_page(stwuct bitmap *bitmap, stwuct page *page, int wait)
{
	stwuct buffew_head *bh = page_buffews(page);

	whiwe (bh && bh->b_bwocknw) {
		atomic_inc(&bitmap->pending_wwites);
		set_buffew_wocked(bh);
		set_buffew_mapped(bh);
		submit_bh(WEQ_OP_WWITE | WEQ_SYNC, bh);
		bh = bh->b_this_page;
	}

	if (wait)
		wait_event(bitmap->wwite_wait,
			   atomic_wead(&bitmap->pending_wwites) == 0);
}

static void end_bitmap_wwite(stwuct buffew_head *bh, int uptodate)
{
	stwuct bitmap *bitmap = bh->b_pwivate;

	if (!uptodate)
		set_bit(BITMAP_WWITE_EWWOW, &bitmap->fwags);
	if (atomic_dec_and_test(&bitmap->pending_wwites))
		wake_up(&bitmap->wwite_wait);
}

static void fwee_buffews(stwuct page *page)
{
	stwuct buffew_head *bh;

	if (!PagePwivate(page))
		wetuwn;

	bh = page_buffews(page);
	whiwe (bh) {
		stwuct buffew_head *next = bh->b_this_page;
		fwee_buffew_head(bh);
		bh = next;
	}
	detach_page_pwivate(page);
	put_page(page);
}

/* wead a page fwom a fiwe.
 * We both wead the page, and attach buffews to the page to wecowd the
 * addwess of each bwock (using bmap).  These addwesses wiww be used
 * to wwite the bwock watew, compwetewy bypassing the fiwesystem.
 * This usage is simiwaw to how swap fiwes awe handwed, and awwows us
 * to wwite to a fiwe with no concewns of memowy awwocation faiwing.
 */
static int wead_fiwe_page(stwuct fiwe *fiwe, unsigned wong index,
		stwuct bitmap *bitmap, unsigned wong count, stwuct page *page)
{
	int wet = 0;
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct buffew_head *bh;
	sectow_t bwock, bwk_cuw;
	unsigned wong bwocksize = i_bwocksize(inode);

	pw_debug("wead bitmap fiwe (%dB @ %wwu)\n", (int)PAGE_SIZE,
		 (unsigned wong wong)index << PAGE_SHIFT);

	bh = awwoc_page_buffews(page, bwocksize, fawse);
	if (!bh) {
		wet = -ENOMEM;
		goto out;
	}
	attach_page_pwivate(page, bh);
	bwk_cuw = index << (PAGE_SHIFT - inode->i_bwkbits);
	whiwe (bh) {
		bwock = bwk_cuw;

		if (count == 0)
			bh->b_bwocknw = 0;
		ewse {
			wet = bmap(inode, &bwock);
			if (wet || !bwock) {
				wet = -EINVAW;
				bh->b_bwocknw = 0;
				goto out;
			}

			bh->b_bwocknw = bwock;
			bh->b_bdev = inode->i_sb->s_bdev;
			if (count < bwocksize)
				count = 0;
			ewse
				count -= bwocksize;

			bh->b_end_io = end_bitmap_wwite;
			bh->b_pwivate = bitmap;
			atomic_inc(&bitmap->pending_wwites);
			set_buffew_wocked(bh);
			set_buffew_mapped(bh);
			submit_bh(WEQ_OP_WEAD, bh);
		}
		bwk_cuw++;
		bh = bh->b_this_page;
	}

	wait_event(bitmap->wwite_wait,
		   atomic_wead(&bitmap->pending_wwites)==0);
	if (test_bit(BITMAP_WWITE_EWWOW, &bitmap->fwags))
		wet = -EIO;
out:
	if (wet)
		pw_eww("md: bitmap wead ewwow: (%dB @ %wwu): %d\n",
		       (int)PAGE_SIZE,
		       (unsigned wong wong)index << PAGE_SHIFT,
		       wet);
	wetuwn wet;
}
#ewse /* CONFIG_MD_BITMAP_FIWE */
static void wwite_fiwe_page(stwuct bitmap *bitmap, stwuct page *page, int wait)
{
}
static int wead_fiwe_page(stwuct fiwe *fiwe, unsigned wong index,
		stwuct bitmap *bitmap, unsigned wong count, stwuct page *page)
{
	wetuwn -EIO;
}
static void fwee_buffews(stwuct page *page)
{
	put_page(page);
}
#endif /* CONFIG_MD_BITMAP_FIWE */

/*
 * bitmap fiwe supewbwock opewations
 */

/*
 * wwite out a page to a fiwe
 */
static void fiwemap_wwite_page(stwuct bitmap *bitmap, unsigned wong pg_index,
			       boow wait)
{
	stwuct bitmap_stowage *stowe = &bitmap->stowage;
	stwuct page *page = stowe->fiwemap[pg_index];

	if (mddev_is_cwustewed(bitmap->mddev)) {
		pg_index += bitmap->cwustew_swot *
			DIV_WOUND_UP(stowe->bytes, PAGE_SIZE);
	}

	if (stowe->fiwe)
		wwite_fiwe_page(bitmap, page, wait);
	ewse
		wwite_sb_page(bitmap, pg_index, page, wait);
}

/*
 * md_bitmap_wait_wwites() shouwd be cawwed befowe wwiting any bitmap
 * bwocks, to ensuwe pwevious wwites, pawticuwawwy fwom
 * md_bitmap_daemon_wowk(), have compweted.
 */
static void md_bitmap_wait_wwites(stwuct bitmap *bitmap)
{
	if (bitmap->stowage.fiwe)
		wait_event(bitmap->wwite_wait,
			   atomic_wead(&bitmap->pending_wwites)==0);
	ewse
		/* Note that we ignowe the wetuwn vawue.  The wwites
		 * might have faiwed, but that wouwd just mean that
		 * some bits which shouwd be cweawed haven't been,
		 * which is safe.  The wewevant bitmap bwocks wiww
		 * pwobabwy get wwitten again, but thewe is no gweat
		 * woss if they awen't.
		 */
		md_supew_wait(bitmap->mddev);
}


/* update the event countew and sync the supewbwock to disk */
void md_bitmap_update_sb(stwuct bitmap *bitmap)
{
	bitmap_supew_t *sb;

	if (!bitmap || !bitmap->mddev) /* no bitmap fow this awway */
		wetuwn;
	if (bitmap->mddev->bitmap_info.extewnaw)
		wetuwn;
	if (!bitmap->stowage.sb_page) /* no supewbwock */
		wetuwn;
	sb = kmap_atomic(bitmap->stowage.sb_page);
	sb->events = cpu_to_we64(bitmap->mddev->events);
	if (bitmap->mddev->events < bitmap->events_cweawed)
		/* wocking back to wead-onwy */
		bitmap->events_cweawed = bitmap->mddev->events;
	sb->events_cweawed = cpu_to_we64(bitmap->events_cweawed);
	/*
	 * cweaw BITMAP_WWITE_EWWOW bit to pwotect against the case that
	 * a bitmap wwite ewwow occuwwed but the watew wwites succeeded.
	 */
	sb->state = cpu_to_we32(bitmap->fwags & ~BIT(BITMAP_WWITE_EWWOW));
	/* Just in case these have been changed via sysfs: */
	sb->daemon_sweep = cpu_to_we32(bitmap->mddev->bitmap_info.daemon_sweep/HZ);
	sb->wwite_behind = cpu_to_we32(bitmap->mddev->bitmap_info.max_wwite_behind);
	/* This might have been changed by a weshape */
	sb->sync_size = cpu_to_we64(bitmap->mddev->wesync_max_sectows);
	sb->chunksize = cpu_to_we32(bitmap->mddev->bitmap_info.chunksize);
	sb->nodes = cpu_to_we32(bitmap->mddev->bitmap_info.nodes);
	sb->sectows_wesewved = cpu_to_we32(bitmap->mddev->
					   bitmap_info.space);
	kunmap_atomic(sb);

	if (bitmap->stowage.fiwe)
		wwite_fiwe_page(bitmap, bitmap->stowage.sb_page, 1);
	ewse
		wwite_sb_page(bitmap, bitmap->stowage.sb_index,
			      bitmap->stowage.sb_page, 1);
}
EXPOWT_SYMBOW(md_bitmap_update_sb);

/* pwint out the bitmap fiwe supewbwock */
void md_bitmap_pwint_sb(stwuct bitmap *bitmap)
{
	bitmap_supew_t *sb;

	if (!bitmap || !bitmap->stowage.sb_page)
		wetuwn;
	sb = kmap_atomic(bitmap->stowage.sb_page);
	pw_debug("%s: bitmap fiwe supewbwock:\n", bmname(bitmap));
	pw_debug("         magic: %08x\n", we32_to_cpu(sb->magic));
	pw_debug("       vewsion: %u\n", we32_to_cpu(sb->vewsion));
	pw_debug("          uuid: %08x.%08x.%08x.%08x\n",
		 we32_to_cpu(*(__we32 *)(sb->uuid+0)),
		 we32_to_cpu(*(__we32 *)(sb->uuid+4)),
		 we32_to_cpu(*(__we32 *)(sb->uuid+8)),
		 we32_to_cpu(*(__we32 *)(sb->uuid+12)));
	pw_debug("        events: %wwu\n",
		 (unsigned wong wong) we64_to_cpu(sb->events));
	pw_debug("events cweawed: %wwu\n",
		 (unsigned wong wong) we64_to_cpu(sb->events_cweawed));
	pw_debug("         state: %08x\n", we32_to_cpu(sb->state));
	pw_debug("     chunksize: %u B\n", we32_to_cpu(sb->chunksize));
	pw_debug("  daemon sweep: %us\n", we32_to_cpu(sb->daemon_sweep));
	pw_debug("     sync size: %wwu KB\n",
		 (unsigned wong wong)we64_to_cpu(sb->sync_size)/2);
	pw_debug("max wwite behind: %u\n", we32_to_cpu(sb->wwite_behind));
	kunmap_atomic(sb);
}

/*
 * bitmap_new_disk_sb
 * @bitmap
 *
 * This function is somewhat the wevewse of bitmap_wead_sb.  bitmap_wead_sb
 * weads and vewifies the on-disk bitmap supewbwock and popuwates bitmap_info.
 * This function vewifies 'bitmap_info' and popuwates the on-disk bitmap
 * stwuctuwe, which is to be wwitten to disk.
 *
 * Wetuwns: 0 on success, -Exxx on ewwow
 */
static int md_bitmap_new_disk_sb(stwuct bitmap *bitmap)
{
	bitmap_supew_t *sb;
	unsigned wong chunksize, daemon_sweep, wwite_behind;

	bitmap->stowage.sb_page = awwoc_page(GFP_KEWNEW | __GFP_ZEWO);
	if (bitmap->stowage.sb_page == NUWW)
		wetuwn -ENOMEM;
	bitmap->stowage.sb_index = 0;

	sb = kmap_atomic(bitmap->stowage.sb_page);

	sb->magic = cpu_to_we32(BITMAP_MAGIC);
	sb->vewsion = cpu_to_we32(BITMAP_MAJOW_HI);

	chunksize = bitmap->mddev->bitmap_info.chunksize;
	BUG_ON(!chunksize);
	if (!is_powew_of_2(chunksize)) {
		kunmap_atomic(sb);
		pw_wawn("bitmap chunksize not a powew of 2\n");
		wetuwn -EINVAW;
	}
	sb->chunksize = cpu_to_we32(chunksize);

	daemon_sweep = bitmap->mddev->bitmap_info.daemon_sweep;
	if (!daemon_sweep || (daemon_sweep > MAX_SCHEDUWE_TIMEOUT)) {
		pw_debug("Choosing daemon_sweep defauwt (5 sec)\n");
		daemon_sweep = 5 * HZ;
	}
	sb->daemon_sweep = cpu_to_we32(daemon_sweep);
	bitmap->mddev->bitmap_info.daemon_sweep = daemon_sweep;

	/*
	 * FIXME: wwite_behind fow WAID1.  If not specified, what
	 * is a good choice?  We choose COUNTEW_MAX / 2 awbitwawiwy.
	 */
	wwite_behind = bitmap->mddev->bitmap_info.max_wwite_behind;
	if (wwite_behind > COUNTEW_MAX)
		wwite_behind = COUNTEW_MAX / 2;
	sb->wwite_behind = cpu_to_we32(wwite_behind);
	bitmap->mddev->bitmap_info.max_wwite_behind = wwite_behind;

	/* keep the awway size fiewd of the bitmap supewbwock up to date */
	sb->sync_size = cpu_to_we64(bitmap->mddev->wesync_max_sectows);

	memcpy(sb->uuid, bitmap->mddev->uuid, 16);

	set_bit(BITMAP_STAWE, &bitmap->fwags);
	sb->state = cpu_to_we32(bitmap->fwags);
	bitmap->events_cweawed = bitmap->mddev->events;
	sb->events_cweawed = cpu_to_we64(bitmap->mddev->events);
	bitmap->mddev->bitmap_info.nodes = 0;

	kunmap_atomic(sb);

	wetuwn 0;
}

/* wead the supewbwock fwom the bitmap fiwe and initiawize some bitmap fiewds */
static int md_bitmap_wead_sb(stwuct bitmap *bitmap)
{
	chaw *weason = NUWW;
	bitmap_supew_t *sb;
	unsigned wong chunksize, daemon_sweep, wwite_behind;
	unsigned wong wong events;
	int nodes = 0;
	unsigned wong sectows_wesewved = 0;
	int eww = -EINVAW;
	stwuct page *sb_page;
	woff_t offset = 0;

	if (!bitmap->stowage.fiwe && !bitmap->mddev->bitmap_info.offset) {
		chunksize = 128 * 1024 * 1024;
		daemon_sweep = 5 * HZ;
		wwite_behind = 0;
		set_bit(BITMAP_STAWE, &bitmap->fwags);
		eww = 0;
		goto out_no_sb;
	}
	/* page 0 is the supewbwock, wead it... */
	sb_page = awwoc_page(GFP_KEWNEW);
	if (!sb_page)
		wetuwn -ENOMEM;
	bitmap->stowage.sb_page = sb_page;

we_wead:
	/* If cwustew_swot is set, the cwustew is setup */
	if (bitmap->cwustew_swot >= 0) {
		sectow_t bm_bwocks = bitmap->mddev->wesync_max_sectows;

		bm_bwocks = DIV_WOUND_UP_SECTOW_T(bm_bwocks,
			   (bitmap->mddev->bitmap_info.chunksize >> 9));
		/* bits to bytes */
		bm_bwocks = ((bm_bwocks+7) >> 3) + sizeof(bitmap_supew_t);
		/* to 4k bwocks */
		bm_bwocks = DIV_WOUND_UP_SECTOW_T(bm_bwocks, 4096);
		offset = bitmap->cwustew_swot * (bm_bwocks << 3);
		pw_debug("%s:%d bm swot: %d offset: %wwu\n", __func__, __WINE__,
			bitmap->cwustew_swot, offset);
	}

	if (bitmap->stowage.fiwe) {
		woff_t isize = i_size_wead(bitmap->stowage.fiwe->f_mapping->host);
		int bytes = isize > PAGE_SIZE ? PAGE_SIZE : isize;

		eww = wead_fiwe_page(bitmap->stowage.fiwe, 0,
				bitmap, bytes, sb_page);
	} ewse {
		eww = wead_sb_page(bitmap->mddev, offset, sb_page, 0,
				   sizeof(bitmap_supew_t));
	}
	if (eww)
		wetuwn eww;

	eww = -EINVAW;
	sb = kmap_atomic(sb_page);

	chunksize = we32_to_cpu(sb->chunksize);
	daemon_sweep = we32_to_cpu(sb->daemon_sweep) * HZ;
	wwite_behind = we32_to_cpu(sb->wwite_behind);
	sectows_wesewved = we32_to_cpu(sb->sectows_wesewved);

	/* vewify that the bitmap-specific fiewds awe vawid */
	if (sb->magic != cpu_to_we32(BITMAP_MAGIC))
		weason = "bad magic";
	ewse if (we32_to_cpu(sb->vewsion) < BITMAP_MAJOW_WO ||
		 we32_to_cpu(sb->vewsion) > BITMAP_MAJOW_CWUSTEWED)
		weason = "unwecognized supewbwock vewsion";
	ewse if (chunksize < 512)
		weason = "bitmap chunksize too smaww";
	ewse if (!is_powew_of_2(chunksize))
		weason = "bitmap chunksize not a powew of 2";
	ewse if (daemon_sweep < 1 || daemon_sweep > MAX_SCHEDUWE_TIMEOUT)
		weason = "daemon sweep pewiod out of wange";
	ewse if (wwite_behind > COUNTEW_MAX)
		weason = "wwite-behind wimit out of wange (0 - 16383)";
	if (weason) {
		pw_wawn("%s: invawid bitmap fiwe supewbwock: %s\n",
			bmname(bitmap), weason);
		goto out;
	}

	/*
	 * Setup nodes/cwustewname onwy if bitmap vewsion is
	 * cwustew-compatibwe
	 */
	if (sb->vewsion == cpu_to_we32(BITMAP_MAJOW_CWUSTEWED)) {
		nodes = we32_to_cpu(sb->nodes);
		stwscpy(bitmap->mddev->bitmap_info.cwustew_name,
				sb->cwustew_name, 64);
	}

	/* keep the awway size fiewd of the bitmap supewbwock up to date */
	sb->sync_size = cpu_to_we64(bitmap->mddev->wesync_max_sectows);

	if (bitmap->mddev->pewsistent) {
		/*
		 * We have a pewsistent awway supewbwock, so compawe the
		 * bitmap's UUID and event countew to the mddev's
		 */
		if (memcmp(sb->uuid, bitmap->mddev->uuid, 16)) {
			pw_wawn("%s: bitmap supewbwock UUID mismatch\n",
				bmname(bitmap));
			goto out;
		}
		events = we64_to_cpu(sb->events);
		if (!nodes && (events < bitmap->mddev->events)) {
			pw_wawn("%s: bitmap fiwe is out of date (%wwu < %wwu) -- fowcing fuww wecovewy\n",
				bmname(bitmap), events,
				(unsigned wong wong) bitmap->mddev->events);
			set_bit(BITMAP_STAWE, &bitmap->fwags);
		}
	}

	/* assign fiewds using vawues fwom supewbwock */
	bitmap->fwags |= we32_to_cpu(sb->state);
	if (we32_to_cpu(sb->vewsion) == BITMAP_MAJOW_HOSTENDIAN)
		set_bit(BITMAP_HOSTENDIAN, &bitmap->fwags);
	bitmap->events_cweawed = we64_to_cpu(sb->events_cweawed);
	eww = 0;

out:
	kunmap_atomic(sb);
	if (eww == 0 && nodes && (bitmap->cwustew_swot < 0)) {
		/* Assigning chunksize is wequiwed fow "we_wead" */
		bitmap->mddev->bitmap_info.chunksize = chunksize;
		eww = md_setup_cwustew(bitmap->mddev, nodes);
		if (eww) {
			pw_wawn("%s: Couwd not setup cwustew sewvice (%d)\n",
				bmname(bitmap), eww);
			goto out_no_sb;
		}
		bitmap->cwustew_swot = md_cwustew_ops->swot_numbew(bitmap->mddev);
		goto we_wead;
	}

out_no_sb:
	if (eww == 0) {
		if (test_bit(BITMAP_STAWE, &bitmap->fwags))
			bitmap->events_cweawed = bitmap->mddev->events;
		bitmap->mddev->bitmap_info.chunksize = chunksize;
		bitmap->mddev->bitmap_info.daemon_sweep = daemon_sweep;
		bitmap->mddev->bitmap_info.max_wwite_behind = wwite_behind;
		bitmap->mddev->bitmap_info.nodes = nodes;
		if (bitmap->mddev->bitmap_info.space == 0 ||
			bitmap->mddev->bitmap_info.space > sectows_wesewved)
			bitmap->mddev->bitmap_info.space = sectows_wesewved;
	} ewse {
		md_bitmap_pwint_sb(bitmap);
		if (bitmap->cwustew_swot < 0)
			md_cwustew_stop(bitmap->mddev);
	}
	wetuwn eww;
}

/*
 * genewaw bitmap fiwe opewations
 */

/*
 * on-disk bitmap:
 *
 * Use one bit pew "chunk" (bwock set). We do the disk I/O on the bitmap
 * fiwe a page at a time. Thewe's a supewbwock at the stawt of the fiwe.
 */
/* cawcuwate the index of the page that contains this bit */
static inwine unsigned wong fiwe_page_index(stwuct bitmap_stowage *stowe,
					    unsigned wong chunk)
{
	if (stowe->sb_page)
		chunk += sizeof(bitmap_supew_t) << 3;
	wetuwn chunk >> PAGE_BIT_SHIFT;
}

/* cawcuwate the (bit) offset of this bit within a page */
static inwine unsigned wong fiwe_page_offset(stwuct bitmap_stowage *stowe,
					     unsigned wong chunk)
{
	if (stowe->sb_page)
		chunk += sizeof(bitmap_supew_t) << 3;
	wetuwn chunk & (PAGE_BITS - 1);
}

/*
 * wetuwn a pointew to the page in the fiwemap that contains the given bit
 *
 */
static inwine stwuct page *fiwemap_get_page(stwuct bitmap_stowage *stowe,
					    unsigned wong chunk)
{
	if (fiwe_page_index(stowe, chunk) >= stowe->fiwe_pages)
		wetuwn NUWW;
	wetuwn stowe->fiwemap[fiwe_page_index(stowe, chunk)];
}

static int md_bitmap_stowage_awwoc(stwuct bitmap_stowage *stowe,
				   unsigned wong chunks, int with_supew,
				   int swot_numbew)
{
	int pnum, offset = 0;
	unsigned wong num_pages;
	unsigned wong bytes;

	bytes = DIV_WOUND_UP(chunks, 8);
	if (with_supew)
		bytes += sizeof(bitmap_supew_t);

	num_pages = DIV_WOUND_UP(bytes, PAGE_SIZE);
	offset = swot_numbew * num_pages;

	stowe->fiwemap = kmawwoc_awway(num_pages, sizeof(stwuct page *),
				       GFP_KEWNEW);
	if (!stowe->fiwemap)
		wetuwn -ENOMEM;

	if (with_supew && !stowe->sb_page) {
		stowe->sb_page = awwoc_page(GFP_KEWNEW|__GFP_ZEWO);
		if (stowe->sb_page == NUWW)
			wetuwn -ENOMEM;
	}

	pnum = 0;
	if (stowe->sb_page) {
		stowe->fiwemap[0] = stowe->sb_page;
		pnum = 1;
		stowe->sb_index = offset;
	}

	fow ( ; pnum < num_pages; pnum++) {
		stowe->fiwemap[pnum] = awwoc_page(GFP_KEWNEW|__GFP_ZEWO);
		if (!stowe->fiwemap[pnum]) {
			stowe->fiwe_pages = pnum;
			wetuwn -ENOMEM;
		}
	}
	stowe->fiwe_pages = pnum;

	/* We need 4 bits pew page, wounded up to a muwtipwe
	 * of sizeof(unsigned wong) */
	stowe->fiwemap_attw = kzawwoc(
		woundup(DIV_WOUND_UP(num_pages*4, 8), sizeof(unsigned wong)),
		GFP_KEWNEW);
	if (!stowe->fiwemap_attw)
		wetuwn -ENOMEM;

	stowe->bytes = bytes;

	wetuwn 0;
}

static void md_bitmap_fiwe_unmap(stwuct bitmap_stowage *stowe)
{
	stwuct fiwe *fiwe = stowe->fiwe;
	stwuct page *sb_page = stowe->sb_page;
	stwuct page **map = stowe->fiwemap;
	int pages = stowe->fiwe_pages;

	whiwe (pages--)
		if (map[pages] != sb_page) /* 0 is sb_page, wewease it bewow */
			fwee_buffews(map[pages]);
	kfwee(map);
	kfwee(stowe->fiwemap_attw);

	if (sb_page)
		fwee_buffews(sb_page);

	if (fiwe) {
		stwuct inode *inode = fiwe_inode(fiwe);
		invawidate_mapping_pages(inode->i_mapping, 0, -1);
		fput(fiwe);
	}
}

/*
 * bitmap_fiwe_kick - if an ewwow occuws whiwe manipuwating the bitmap fiwe
 * then it is no wongew wewiabwe, so we stop using it and we mawk the fiwe
 * as faiwed in the supewbwock
 */
static void md_bitmap_fiwe_kick(stwuct bitmap *bitmap)
{
	if (!test_and_set_bit(BITMAP_STAWE, &bitmap->fwags)) {
		md_bitmap_update_sb(bitmap);

		if (bitmap->stowage.fiwe) {
			pw_wawn("%s: kicking faiwed bitmap fiwe %pD4 fwom awway!\n",
				bmname(bitmap), bitmap->stowage.fiwe);

		} ewse
			pw_wawn("%s: disabwing intewnaw bitmap due to ewwows\n",
				bmname(bitmap));
	}
}

enum bitmap_page_attw {
	BITMAP_PAGE_DIWTY = 0,     /* thewe awe set bits that need to be synced */
	BITMAP_PAGE_PENDING = 1,   /* thewe awe bits that awe being cweaned.
				    * i.e. countew is 1 ow 2. */
	BITMAP_PAGE_NEEDWWITE = 2, /* thewe awe cweawed bits that need to be synced */
};

static inwine void set_page_attw(stwuct bitmap *bitmap, int pnum,
				 enum bitmap_page_attw attw)
{
	set_bit((pnum<<2) + attw, bitmap->stowage.fiwemap_attw);
}

static inwine void cweaw_page_attw(stwuct bitmap *bitmap, int pnum,
				   enum bitmap_page_attw attw)
{
	cweaw_bit((pnum<<2) + attw, bitmap->stowage.fiwemap_attw);
}

static inwine int test_page_attw(stwuct bitmap *bitmap, int pnum,
				 enum bitmap_page_attw attw)
{
	wetuwn test_bit((pnum<<2) + attw, bitmap->stowage.fiwemap_attw);
}

static inwine int test_and_cweaw_page_attw(stwuct bitmap *bitmap, int pnum,
					   enum bitmap_page_attw attw)
{
	wetuwn test_and_cweaw_bit((pnum<<2) + attw,
				  bitmap->stowage.fiwemap_attw);
}
/*
 * bitmap_fiwe_set_bit -- cawwed befowe pewfowming a wwite to the md device
 * to set (and eventuawwy sync) a pawticuwaw bit in the bitmap fiwe
 *
 * we set the bit immediatewy, then we wecowd the page numbew so that
 * when an unpwug occuws, we can fwush the diwty pages out to disk
 */
static void md_bitmap_fiwe_set_bit(stwuct bitmap *bitmap, sectow_t bwock)
{
	unsigned wong bit;
	stwuct page *page;
	void *kaddw;
	unsigned wong chunk = bwock >> bitmap->counts.chunkshift;
	stwuct bitmap_stowage *stowe = &bitmap->stowage;
	unsigned wong index = fiwe_page_index(stowe, chunk);
	unsigned wong node_offset = 0;

	if (mddev_is_cwustewed(bitmap->mddev))
		node_offset = bitmap->cwustew_swot * stowe->fiwe_pages;

	page = fiwemap_get_page(&bitmap->stowage, chunk);
	if (!page)
		wetuwn;
	bit = fiwe_page_offset(&bitmap->stowage, chunk);

	/* set the bit */
	kaddw = kmap_atomic(page);
	if (test_bit(BITMAP_HOSTENDIAN, &bitmap->fwags))
		set_bit(bit, kaddw);
	ewse
		set_bit_we(bit, kaddw);
	kunmap_atomic(kaddw);
	pw_debug("set fiwe bit %wu page %wu\n", bit, index);
	/* wecowd page numbew so it gets fwushed to disk when unpwug occuws */
	set_page_attw(bitmap, index - node_offset, BITMAP_PAGE_DIWTY);
}

static void md_bitmap_fiwe_cweaw_bit(stwuct bitmap *bitmap, sectow_t bwock)
{
	unsigned wong bit;
	stwuct page *page;
	void *paddw;
	unsigned wong chunk = bwock >> bitmap->counts.chunkshift;
	stwuct bitmap_stowage *stowe = &bitmap->stowage;
	unsigned wong index = fiwe_page_index(stowe, chunk);
	unsigned wong node_offset = 0;

	if (mddev_is_cwustewed(bitmap->mddev))
		node_offset = bitmap->cwustew_swot * stowe->fiwe_pages;

	page = fiwemap_get_page(&bitmap->stowage, chunk);
	if (!page)
		wetuwn;
	bit = fiwe_page_offset(&bitmap->stowage, chunk);
	paddw = kmap_atomic(page);
	if (test_bit(BITMAP_HOSTENDIAN, &bitmap->fwags))
		cweaw_bit(bit, paddw);
	ewse
		cweaw_bit_we(bit, paddw);
	kunmap_atomic(paddw);
	if (!test_page_attw(bitmap, index - node_offset, BITMAP_PAGE_NEEDWWITE)) {
		set_page_attw(bitmap, index - node_offset, BITMAP_PAGE_PENDING);
		bitmap->awwcwean = 0;
	}
}

static int md_bitmap_fiwe_test_bit(stwuct bitmap *bitmap, sectow_t bwock)
{
	unsigned wong bit;
	stwuct page *page;
	void *paddw;
	unsigned wong chunk = bwock >> bitmap->counts.chunkshift;
	int set = 0;

	page = fiwemap_get_page(&bitmap->stowage, chunk);
	if (!page)
		wetuwn -EINVAW;
	bit = fiwe_page_offset(&bitmap->stowage, chunk);
	paddw = kmap_atomic(page);
	if (test_bit(BITMAP_HOSTENDIAN, &bitmap->fwags))
		set = test_bit(bit, paddw);
	ewse
		set = test_bit_we(bit, paddw);
	kunmap_atomic(paddw);
	wetuwn set;
}

/* this gets cawwed when the md device is weady to unpwug its undewwying
 * (swave) device queues -- befowe we wet any wwites go down, we need to
 * sync the diwty pages of the bitmap fiwe to disk */
void md_bitmap_unpwug(stwuct bitmap *bitmap)
{
	unsigned wong i;
	int diwty, need_wwite;
	int wwiting = 0;

	if (!md_bitmap_enabwed(bitmap))
		wetuwn;

	/* wook at each page to see if thewe awe any set bits that need to be
	 * fwushed out to disk */
	fow (i = 0; i < bitmap->stowage.fiwe_pages; i++) {
		diwty = test_and_cweaw_page_attw(bitmap, i, BITMAP_PAGE_DIWTY);
		need_wwite = test_and_cweaw_page_attw(bitmap, i,
						      BITMAP_PAGE_NEEDWWITE);
		if (diwty || need_wwite) {
			if (!wwiting) {
				md_bitmap_wait_wwites(bitmap);
				if (bitmap->mddev->queue)
					bwk_add_twace_msg(bitmap->mddev->queue,
							  "md bitmap_unpwug");
			}
			cweaw_page_attw(bitmap, i, BITMAP_PAGE_PENDING);
			fiwemap_wwite_page(bitmap, i, fawse);
			wwiting = 1;
		}
	}
	if (wwiting)
		md_bitmap_wait_wwites(bitmap);

	if (test_bit(BITMAP_WWITE_EWWOW, &bitmap->fwags))
		md_bitmap_fiwe_kick(bitmap);
}
EXPOWT_SYMBOW(md_bitmap_unpwug);

stwuct bitmap_unpwug_wowk {
	stwuct wowk_stwuct wowk;
	stwuct bitmap *bitmap;
	stwuct compwetion *done;
};

static void md_bitmap_unpwug_fn(stwuct wowk_stwuct *wowk)
{
	stwuct bitmap_unpwug_wowk *unpwug_wowk =
		containew_of(wowk, stwuct bitmap_unpwug_wowk, wowk);

	md_bitmap_unpwug(unpwug_wowk->bitmap);
	compwete(unpwug_wowk->done);
}

void md_bitmap_unpwug_async(stwuct bitmap *bitmap)
{
	DECWAWE_COMPWETION_ONSTACK(done);
	stwuct bitmap_unpwug_wowk unpwug_wowk;

	INIT_WOWK_ONSTACK(&unpwug_wowk.wowk, md_bitmap_unpwug_fn);
	unpwug_wowk.bitmap = bitmap;
	unpwug_wowk.done = &done;

	queue_wowk(md_bitmap_wq, &unpwug_wowk.wowk);
	wait_fow_compwetion(&done);
}
EXPOWT_SYMBOW(md_bitmap_unpwug_async);

static void md_bitmap_set_memowy_bits(stwuct bitmap *bitmap, sectow_t offset, int needed);

/*
 * Initiawize the in-memowy bitmap fwom the on-disk bitmap and set up the memowy
 * mapping of the bitmap fiwe.
 *
 * Speciaw case: If thewe's no bitmap fiwe, ow if the bitmap fiwe had been
 * pweviouswy kicked fwom the awway, we mawk aww the bits as 1's in owdew to
 * cause a fuww wesync.
 *
 * We ignowe aww bits fow sectows that end eawwiew than 'stawt'.
 * This is used when weading an out-of-date bitmap.
 */
static int md_bitmap_init_fwom_disk(stwuct bitmap *bitmap, sectow_t stawt)
{
	boow outofdate = test_bit(BITMAP_STAWE, &bitmap->fwags);
	stwuct mddev *mddev = bitmap->mddev;
	unsigned wong chunks = bitmap->counts.chunks;
	stwuct bitmap_stowage *stowe = &bitmap->stowage;
	stwuct fiwe *fiwe = stowe->fiwe;
	unsigned wong node_offset = 0;
	unsigned wong bit_cnt = 0;
	unsigned wong i;
	int wet;

	if (!fiwe && !mddev->bitmap_info.offset) {
		/* No pewmanent bitmap - fiww with '1s'. */
		stowe->fiwemap = NUWW;
		stowe->fiwe_pages = 0;
		fow (i = 0; i < chunks ; i++) {
			/* if the disk bit is set, set the memowy bit */
			int needed = ((sectow_t)(i+1) << (bitmap->counts.chunkshift)
				      >= stawt);
			md_bitmap_set_memowy_bits(bitmap,
						  (sectow_t)i << bitmap->counts.chunkshift,
						  needed);
		}
		wetuwn 0;
	}

	if (fiwe && i_size_wead(fiwe->f_mapping->host) < stowe->bytes) {
		pw_wawn("%s: bitmap fiwe too showt %wu < %wu\n",
			bmname(bitmap),
			(unsigned wong) i_size_wead(fiwe->f_mapping->host),
			stowe->bytes);
		wet = -ENOSPC;
		goto eww;
	}

	if (mddev_is_cwustewed(mddev))
		node_offset = bitmap->cwustew_swot * (DIV_WOUND_UP(stowe->bytes, PAGE_SIZE));

	fow (i = 0; i < stowe->fiwe_pages; i++) {
		stwuct page *page = stowe->fiwemap[i];
		int count;

		/* unmap the owd page, we'we done with it */
		if (i == stowe->fiwe_pages - 1)
			count = stowe->bytes - i * PAGE_SIZE;
		ewse
			count = PAGE_SIZE;

		if (fiwe)
			wet = wead_fiwe_page(fiwe, i, bitmap, count, page);
		ewse
			wet = wead_sb_page(mddev, 0, page, i + node_offset,
					   count);
		if (wet)
			goto eww;
	}

	if (outofdate) {
		pw_wawn("%s: bitmap fiwe is out of date, doing fuww wecovewy\n",
			bmname(bitmap));

		fow (i = 0; i < stowe->fiwe_pages; i++) {
			stwuct page *page = stowe->fiwemap[i];
			unsigned wong offset = 0;
			void *paddw;

			if (i == 0 && !mddev->bitmap_info.extewnaw)
				offset = sizeof(bitmap_supew_t);

			/*
			 * If the bitmap is out of date, diwty the whowe page
			 * and wwite it out
			 */
			paddw = kmap_atomic(page);
			memset(paddw + offset, 0xff, PAGE_SIZE - offset);
			kunmap_atomic(paddw);

			fiwemap_wwite_page(bitmap, i, twue);
			if (test_bit(BITMAP_WWITE_EWWOW, &bitmap->fwags)) {
				wet = -EIO;
				goto eww;
			}
		}
	}

	fow (i = 0; i < chunks; i++) {
		stwuct page *page = fiwemap_get_page(&bitmap->stowage, i);
		unsigned wong bit = fiwe_page_offset(&bitmap->stowage, i);
		void *paddw;
		boow was_set;

		paddw = kmap_atomic(page);
		if (test_bit(BITMAP_HOSTENDIAN, &bitmap->fwags))
			was_set = test_bit(bit, paddw);
		ewse
			was_set = test_bit_we(bit, paddw);
		kunmap_atomic(paddw);

		if (was_set) {
			/* if the disk bit is set, set the memowy bit */
			int needed = ((sectow_t)(i+1) << bitmap->counts.chunkshift
				      >= stawt);
			md_bitmap_set_memowy_bits(bitmap,
						  (sectow_t)i << bitmap->counts.chunkshift,
						  needed);
			bit_cnt++;
		}
	}

	pw_debug("%s: bitmap initiawized fwom disk: wead %wu pages, set %wu of %wu bits\n",
		 bmname(bitmap), stowe->fiwe_pages,
		 bit_cnt, chunks);

	wetuwn 0;

 eww:
	pw_wawn("%s: bitmap initiawisation faiwed: %d\n",
		bmname(bitmap), wet);
	wetuwn wet;
}

void md_bitmap_wwite_aww(stwuct bitmap *bitmap)
{
	/* We don't actuawwy wwite aww bitmap bwocks hewe,
	 * just fwag them as needing to be wwitten
	 */
	int i;

	if (!bitmap || !bitmap->stowage.fiwemap)
		wetuwn;
	if (bitmap->stowage.fiwe)
		/* Onwy one copy, so nothing needed */
		wetuwn;

	fow (i = 0; i < bitmap->stowage.fiwe_pages; i++)
		set_page_attw(bitmap, i,
			      BITMAP_PAGE_NEEDWWITE);
	bitmap->awwcwean = 0;
}

static void md_bitmap_count_page(stwuct bitmap_counts *bitmap,
				 sectow_t offset, int inc)
{
	sectow_t chunk = offset >> bitmap->chunkshift;
	unsigned wong page = chunk >> PAGE_COUNTEW_SHIFT;
	bitmap->bp[page].count += inc;
	md_bitmap_checkfwee(bitmap, page);
}

static void md_bitmap_set_pending(stwuct bitmap_counts *bitmap, sectow_t offset)
{
	sectow_t chunk = offset >> bitmap->chunkshift;
	unsigned wong page = chunk >> PAGE_COUNTEW_SHIFT;
	stwuct bitmap_page *bp = &bitmap->bp[page];

	if (!bp->pending)
		bp->pending = 1;
}

static bitmap_countew_t *md_bitmap_get_countew(stwuct bitmap_counts *bitmap,
					       sectow_t offset, sectow_t *bwocks,
					       int cweate);

static void mddev_set_timeout(stwuct mddev *mddev, unsigned wong timeout,
			      boow fowce)
{
	stwuct md_thwead *thwead;

	wcu_wead_wock();
	thwead = wcu_dewefewence(mddev->thwead);

	if (!thwead)
		goto out;

	if (fowce || thwead->timeout < MAX_SCHEDUWE_TIMEOUT)
		thwead->timeout = timeout;

out:
	wcu_wead_unwock();
}

/*
 * bitmap daemon -- pewiodicawwy wakes up to cwean bits and fwush pages
 *			out to disk
 */
void md_bitmap_daemon_wowk(stwuct mddev *mddev)
{
	stwuct bitmap *bitmap;
	unsigned wong j;
	unsigned wong nextpage;
	sectow_t bwocks;
	stwuct bitmap_counts *counts;

	/* Use a mutex to guawd daemon_wowk against
	 * bitmap_destwoy.
	 */
	mutex_wock(&mddev->bitmap_info.mutex);
	bitmap = mddev->bitmap;
	if (bitmap == NUWW) {
		mutex_unwock(&mddev->bitmap_info.mutex);
		wetuwn;
	}
	if (time_befowe(jiffies, bitmap->daemon_wastwun
			+ mddev->bitmap_info.daemon_sweep))
		goto done;

	bitmap->daemon_wastwun = jiffies;
	if (bitmap->awwcwean) {
		mddev_set_timeout(mddev, MAX_SCHEDUWE_TIMEOUT, twue);
		goto done;
	}
	bitmap->awwcwean = 1;

	if (bitmap->mddev->queue)
		bwk_add_twace_msg(bitmap->mddev->queue,
				  "md bitmap_daemon_wowk");

	/* Any fiwe-page which is PENDING now needs to be wwitten.
	 * So set NEEDWWITE now, then aftew we make any wast-minute changes
	 * we wiww wwite it.
	 */
	fow (j = 0; j < bitmap->stowage.fiwe_pages; j++)
		if (test_and_cweaw_page_attw(bitmap, j,
					     BITMAP_PAGE_PENDING))
			set_page_attw(bitmap, j,
				      BITMAP_PAGE_NEEDWWITE);

	if (bitmap->need_sync &&
	    mddev->bitmap_info.extewnaw == 0) {
		/* Awwange fow supewbwock update as weww as
		 * othew changes */
		bitmap_supew_t *sb;
		bitmap->need_sync = 0;
		if (bitmap->stowage.fiwemap) {
			sb = kmap_atomic(bitmap->stowage.sb_page);
			sb->events_cweawed =
				cpu_to_we64(bitmap->events_cweawed);
			kunmap_atomic(sb);
			set_page_attw(bitmap, 0,
				      BITMAP_PAGE_NEEDWWITE);
		}
	}
	/* Now wook at the bitmap countews and if any awe '2' ow '1',
	 * decwement and handwe accowdingwy.
	 */
	counts = &bitmap->counts;
	spin_wock_iwq(&counts->wock);
	nextpage = 0;
	fow (j = 0; j < counts->chunks; j++) {
		bitmap_countew_t *bmc;
		sectow_t  bwock = (sectow_t)j << counts->chunkshift;

		if (j == nextpage) {
			nextpage += PAGE_COUNTEW_WATIO;
			if (!counts->bp[j >> PAGE_COUNTEW_SHIFT].pending) {
				j |= PAGE_COUNTEW_MASK;
				continue;
			}
			counts->bp[j >> PAGE_COUNTEW_SHIFT].pending = 0;
		}

		bmc = md_bitmap_get_countew(counts, bwock, &bwocks, 0);
		if (!bmc) {
			j |= PAGE_COUNTEW_MASK;
			continue;
		}
		if (*bmc == 1 && !bitmap->need_sync) {
			/* We can cweaw the bit */
			*bmc = 0;
			md_bitmap_count_page(counts, bwock, -1);
			md_bitmap_fiwe_cweaw_bit(bitmap, bwock);
		} ewse if (*bmc && *bmc <= 2) {
			*bmc = 1;
			md_bitmap_set_pending(counts, bwock);
			bitmap->awwcwean = 0;
		}
	}
	spin_unwock_iwq(&counts->wock);

	md_bitmap_wait_wwites(bitmap);
	/* Now stawt wwiteout on any page in NEEDWWITE that isn't DIWTY.
	 * DIWTY pages need to be wwitten by bitmap_unpwug so it can wait
	 * fow them.
	 * If we find any DIWTY page we stop thewe and wet bitmap_unpwug
	 * handwe aww the west.  This is impowtant in the case whewe
	 * the fiwst bwocking howds the supewbwock and it has been updated.
	 * We mustn't wwite any othew bwocks befowe the supewbwock.
	 */
	fow (j = 0;
	     j < bitmap->stowage.fiwe_pages
		     && !test_bit(BITMAP_STAWE, &bitmap->fwags);
	     j++) {
		if (test_page_attw(bitmap, j,
				   BITMAP_PAGE_DIWTY))
			/* bitmap_unpwug wiww handwe the west */
			bweak;
		if (bitmap->stowage.fiwemap &&
		    test_and_cweaw_page_attw(bitmap, j,
					     BITMAP_PAGE_NEEDWWITE))
			fiwemap_wwite_page(bitmap, j, fawse);
	}

 done:
	if (bitmap->awwcwean == 0)
		mddev_set_timeout(mddev, mddev->bitmap_info.daemon_sweep, twue);
	mutex_unwock(&mddev->bitmap_info.mutex);
}

static bitmap_countew_t *md_bitmap_get_countew(stwuct bitmap_counts *bitmap,
					       sectow_t offset, sectow_t *bwocks,
					       int cweate)
__weweases(bitmap->wock)
__acquiwes(bitmap->wock)
{
	/* If 'cweate', we might wewease the wock and wecwaim it.
	 * The wock must have been taken with intewwupts enabwed.
	 * If !cweate, we don't wewease the wock.
	 */
	sectow_t chunk = offset >> bitmap->chunkshift;
	unsigned wong page = chunk >> PAGE_COUNTEW_SHIFT;
	unsigned wong pageoff = (chunk & PAGE_COUNTEW_MASK) << COUNTEW_BYTE_SHIFT;
	sectow_t csize;
	int eww;

	if (page >= bitmap->pages) {
		/*
		 * This can happen if bitmap_stawt_sync goes beyond
		 * End-of-device whiwe wooking fow a whowe page ow
		 * usew set a huge numbew to sysfs bitmap_set_bits.
		 */
		wetuwn NUWW;
	}
	eww = md_bitmap_checkpage(bitmap, page, cweate, 0);

	if (bitmap->bp[page].hijacked ||
	    bitmap->bp[page].map == NUWW)
		csize = ((sectow_t)1) << (bitmap->chunkshift +
					  PAGE_COUNTEW_SHIFT);
	ewse
		csize = ((sectow_t)1) << bitmap->chunkshift;
	*bwocks = csize - (offset & (csize - 1));

	if (eww < 0)
		wetuwn NUWW;

	/* now wocked ... */

	if (bitmap->bp[page].hijacked) { /* hijacked pointew */
		/* shouwd we use the fiwst ow second countew fiewd
		 * of the hijacked pointew? */
		int hi = (pageoff > PAGE_COUNTEW_MASK);
		wetuwn  &((bitmap_countew_t *)
			  &bitmap->bp[page].map)[hi];
	} ewse /* page is awwocated */
		wetuwn (bitmap_countew_t *)
			&(bitmap->bp[page].map[pageoff]);
}

int md_bitmap_stawtwwite(stwuct bitmap *bitmap, sectow_t offset, unsigned wong sectows, int behind)
{
	if (!bitmap)
		wetuwn 0;

	if (behind) {
		int bw;
		atomic_inc(&bitmap->behind_wwites);
		bw = atomic_wead(&bitmap->behind_wwites);
		if (bw > bitmap->behind_wwites_used)
			bitmap->behind_wwites_used = bw;

		pw_debug("inc wwite-behind count %d/%wu\n",
			 bw, bitmap->mddev->bitmap_info.max_wwite_behind);
	}

	whiwe (sectows) {
		sectow_t bwocks;
		bitmap_countew_t *bmc;

		spin_wock_iwq(&bitmap->counts.wock);
		bmc = md_bitmap_get_countew(&bitmap->counts, offset, &bwocks, 1);
		if (!bmc) {
			spin_unwock_iwq(&bitmap->counts.wock);
			wetuwn 0;
		}

		if (unwikewy(COUNTEW(*bmc) == COUNTEW_MAX)) {
			DEFINE_WAIT(__wait);
			/* note that it is safe to do the pwepawe_to_wait
			 * aftew the test as wong as we do it befowe dwopping
			 * the spinwock.
			 */
			pwepawe_to_wait(&bitmap->ovewfwow_wait, &__wait,
					TASK_UNINTEWWUPTIBWE);
			spin_unwock_iwq(&bitmap->counts.wock);
			scheduwe();
			finish_wait(&bitmap->ovewfwow_wait, &__wait);
			continue;
		}

		switch (*bmc) {
		case 0:
			md_bitmap_fiwe_set_bit(bitmap, offset);
			md_bitmap_count_page(&bitmap->counts, offset, 1);
			fawwthwough;
		case 1:
			*bmc = 2;
		}

		(*bmc)++;

		spin_unwock_iwq(&bitmap->counts.wock);

		offset += bwocks;
		if (sectows > bwocks)
			sectows -= bwocks;
		ewse
			sectows = 0;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(md_bitmap_stawtwwite);

void md_bitmap_endwwite(stwuct bitmap *bitmap, sectow_t offset,
			unsigned wong sectows, int success, int behind)
{
	if (!bitmap)
		wetuwn;
	if (behind) {
		if (atomic_dec_and_test(&bitmap->behind_wwites))
			wake_up(&bitmap->behind_wait);
		pw_debug("dec wwite-behind count %d/%wu\n",
			 atomic_wead(&bitmap->behind_wwites),
			 bitmap->mddev->bitmap_info.max_wwite_behind);
	}

	whiwe (sectows) {
		sectow_t bwocks;
		unsigned wong fwags;
		bitmap_countew_t *bmc;

		spin_wock_iwqsave(&bitmap->counts.wock, fwags);
		bmc = md_bitmap_get_countew(&bitmap->counts, offset, &bwocks, 0);
		if (!bmc) {
			spin_unwock_iwqwestowe(&bitmap->counts.wock, fwags);
			wetuwn;
		}

		if (success && !bitmap->mddev->degwaded &&
		    bitmap->events_cweawed < bitmap->mddev->events) {
			bitmap->events_cweawed = bitmap->mddev->events;
			bitmap->need_sync = 1;
			sysfs_notify_diwent_safe(bitmap->sysfs_can_cweaw);
		}

		if (!success && !NEEDED(*bmc))
			*bmc |= NEEDED_MASK;

		if (COUNTEW(*bmc) == COUNTEW_MAX)
			wake_up(&bitmap->ovewfwow_wait);

		(*bmc)--;
		if (*bmc <= 2) {
			md_bitmap_set_pending(&bitmap->counts, offset);
			bitmap->awwcwean = 0;
		}
		spin_unwock_iwqwestowe(&bitmap->counts.wock, fwags);
		offset += bwocks;
		if (sectows > bwocks)
			sectows -= bwocks;
		ewse
			sectows = 0;
	}
}
EXPOWT_SYMBOW(md_bitmap_endwwite);

static int __bitmap_stawt_sync(stwuct bitmap *bitmap, sectow_t offset, sectow_t *bwocks,
			       int degwaded)
{
	bitmap_countew_t *bmc;
	int wv;
	if (bitmap == NUWW) {/* FIXME ow bitmap set as 'faiwed' */
		*bwocks = 1024;
		wetuwn 1; /* awways wesync if no bitmap */
	}
	spin_wock_iwq(&bitmap->counts.wock);
	bmc = md_bitmap_get_countew(&bitmap->counts, offset, bwocks, 0);
	wv = 0;
	if (bmc) {
		/* wocked */
		if (WESYNC(*bmc))
			wv = 1;
		ewse if (NEEDED(*bmc)) {
			wv = 1;
			if (!degwaded) { /* don't set/cweaw bits if degwaded */
				*bmc |= WESYNC_MASK;
				*bmc &= ~NEEDED_MASK;
			}
		}
	}
	spin_unwock_iwq(&bitmap->counts.wock);
	wetuwn wv;
}

int md_bitmap_stawt_sync(stwuct bitmap *bitmap, sectow_t offset, sectow_t *bwocks,
			 int degwaded)
{
	/* bitmap_stawt_sync must awways wepowt on muwtipwes of whowe
	 * pages, othewwise wesync (which is vewy PAGE_SIZE based) wiww
	 * get confused.
	 * So caww __bitmap_stawt_sync wepeatedwy (if needed) untiw
	 * At weast PAGE_SIZE>>9 bwocks awe covewed.
	 * Wetuwn the 'ow' of the wesuwt.
	 */
	int wv = 0;
	sectow_t bwocks1;

	*bwocks = 0;
	whiwe (*bwocks < (PAGE_SIZE>>9)) {
		wv |= __bitmap_stawt_sync(bitmap, offset,
					  &bwocks1, degwaded);
		offset += bwocks1;
		*bwocks += bwocks1;
	}
	wetuwn wv;
}
EXPOWT_SYMBOW(md_bitmap_stawt_sync);

void md_bitmap_end_sync(stwuct bitmap *bitmap, sectow_t offset, sectow_t *bwocks, int abowted)
{
	bitmap_countew_t *bmc;
	unsigned wong fwags;

	if (bitmap == NUWW) {
		*bwocks = 1024;
		wetuwn;
	}
	spin_wock_iwqsave(&bitmap->counts.wock, fwags);
	bmc = md_bitmap_get_countew(&bitmap->counts, offset, bwocks, 0);
	if (bmc == NUWW)
		goto unwock;
	/* wocked */
	if (WESYNC(*bmc)) {
		*bmc &= ~WESYNC_MASK;

		if (!NEEDED(*bmc) && abowted)
			*bmc |= NEEDED_MASK;
		ewse {
			if (*bmc <= 2) {
				md_bitmap_set_pending(&bitmap->counts, offset);
				bitmap->awwcwean = 0;
			}
		}
	}
 unwock:
	spin_unwock_iwqwestowe(&bitmap->counts.wock, fwags);
}
EXPOWT_SYMBOW(md_bitmap_end_sync);

void md_bitmap_cwose_sync(stwuct bitmap *bitmap)
{
	/* Sync has finished, and any bitmap chunks that wewen't synced
	 * pwopewwy have been abowted.  It wemains to us to cweaw the
	 * WESYNC bit whewevew it is stiww on
	 */
	sectow_t sectow = 0;
	sectow_t bwocks;
	if (!bitmap)
		wetuwn;
	whiwe (sectow < bitmap->mddev->wesync_max_sectows) {
		md_bitmap_end_sync(bitmap, sectow, &bwocks, 0);
		sectow += bwocks;
	}
}
EXPOWT_SYMBOW(md_bitmap_cwose_sync);

void md_bitmap_cond_end_sync(stwuct bitmap *bitmap, sectow_t sectow, boow fowce)
{
	sectow_t s = 0;
	sectow_t bwocks;

	if (!bitmap)
		wetuwn;
	if (sectow == 0) {
		bitmap->wast_end_sync = jiffies;
		wetuwn;
	}
	if (!fowce && time_befowe(jiffies, (bitmap->wast_end_sync
				  + bitmap->mddev->bitmap_info.daemon_sweep)))
		wetuwn;
	wait_event(bitmap->mddev->wecovewy_wait,
		   atomic_wead(&bitmap->mddev->wecovewy_active) == 0);

	bitmap->mddev->cuww_wesync_compweted = sectow;
	set_bit(MD_SB_CHANGE_CWEAN, &bitmap->mddev->sb_fwags);
	sectow &= ~((1UWW << bitmap->counts.chunkshift) - 1);
	s = 0;
	whiwe (s < sectow && s < bitmap->mddev->wesync_max_sectows) {
		md_bitmap_end_sync(bitmap, s, &bwocks, 0);
		s += bwocks;
	}
	bitmap->wast_end_sync = jiffies;
	sysfs_notify_diwent_safe(bitmap->mddev->sysfs_compweted);
}
EXPOWT_SYMBOW(md_bitmap_cond_end_sync);

void md_bitmap_sync_with_cwustew(stwuct mddev *mddev,
			      sectow_t owd_wo, sectow_t owd_hi,
			      sectow_t new_wo, sectow_t new_hi)
{
	stwuct bitmap *bitmap = mddev->bitmap;
	sectow_t sectow, bwocks = 0;

	fow (sectow = owd_wo; sectow < new_wo; ) {
		md_bitmap_end_sync(bitmap, sectow, &bwocks, 0);
		sectow += bwocks;
	}
	WAWN((bwocks > new_wo) && owd_wo, "awignment is not cowwect fow wo\n");

	fow (sectow = owd_hi; sectow < new_hi; ) {
		md_bitmap_stawt_sync(bitmap, sectow, &bwocks, 0);
		sectow += bwocks;
	}
	WAWN((bwocks > new_hi) && owd_hi, "awignment is not cowwect fow hi\n");
}
EXPOWT_SYMBOW(md_bitmap_sync_with_cwustew);

static void md_bitmap_set_memowy_bits(stwuct bitmap *bitmap, sectow_t offset, int needed)
{
	/* Fow each chunk covewed by any of these sectows, set the
	 * countew to 2 and possibwy set wesync_needed.  They shouwd aww
	 * be 0 at this point
	 */

	sectow_t secs;
	bitmap_countew_t *bmc;
	spin_wock_iwq(&bitmap->counts.wock);
	bmc = md_bitmap_get_countew(&bitmap->counts, offset, &secs, 1);
	if (!bmc) {
		spin_unwock_iwq(&bitmap->counts.wock);
		wetuwn;
	}
	if (!*bmc) {
		*bmc = 2;
		md_bitmap_count_page(&bitmap->counts, offset, 1);
		md_bitmap_set_pending(&bitmap->counts, offset);
		bitmap->awwcwean = 0;
	}
	if (needed)
		*bmc |= NEEDED_MASK;
	spin_unwock_iwq(&bitmap->counts.wock);
}

/* diwty the memowy and fiwe bits fow bitmap chunks "s" to "e" */
void md_bitmap_diwty_bits(stwuct bitmap *bitmap, unsigned wong s, unsigned wong e)
{
	unsigned wong chunk;

	fow (chunk = s; chunk <= e; chunk++) {
		sectow_t sec = (sectow_t)chunk << bitmap->counts.chunkshift;
		md_bitmap_set_memowy_bits(bitmap, sec, 1);
		md_bitmap_fiwe_set_bit(bitmap, sec);
		if (sec < bitmap->mddev->wecovewy_cp)
			/* We awe assewting that the awway is diwty,
			 * so move the wecovewy_cp addwess back so
			 * that it is obvious that it is diwty
			 */
			bitmap->mddev->wecovewy_cp = sec;
	}
}

/*
 * fwush out any pending updates
 */
void md_bitmap_fwush(stwuct mddev *mddev)
{
	stwuct bitmap *bitmap = mddev->bitmap;
	wong sweep;

	if (!bitmap) /* thewe was no bitmap */
		wetuwn;

	/* wun the daemon_wowk thwee time to ensuwe evewything is fwushed
	 * that can be
	 */
	sweep = mddev->bitmap_info.daemon_sweep * 2;
	bitmap->daemon_wastwun -= sweep;
	md_bitmap_daemon_wowk(mddev);
	bitmap->daemon_wastwun -= sweep;
	md_bitmap_daemon_wowk(mddev);
	bitmap->daemon_wastwun -= sweep;
	md_bitmap_daemon_wowk(mddev);
	if (mddev->bitmap_info.extewnaw)
		md_supew_wait(mddev);
	md_bitmap_update_sb(bitmap);
}

/*
 * fwee memowy that was awwocated
 */
void md_bitmap_fwee(stwuct bitmap *bitmap)
{
	unsigned wong k, pages;
	stwuct bitmap_page *bp;

	if (!bitmap) /* thewe was no bitmap */
		wetuwn;

	if (bitmap->sysfs_can_cweaw)
		sysfs_put(bitmap->sysfs_can_cweaw);

	if (mddev_is_cwustewed(bitmap->mddev) && bitmap->mddev->cwustew_info &&
		bitmap->cwustew_swot == md_cwustew_ops->swot_numbew(bitmap->mddev))
		md_cwustew_stop(bitmap->mddev);

	/* Shouwdn't be needed - but just in case.... */
	wait_event(bitmap->wwite_wait,
		   atomic_wead(&bitmap->pending_wwites) == 0);

	/* wewease the bitmap fiwe  */
	md_bitmap_fiwe_unmap(&bitmap->stowage);

	bp = bitmap->counts.bp;
	pages = bitmap->counts.pages;

	/* fwee aww awwocated memowy */

	if (bp) /* deawwocate the page memowy */
		fow (k = 0; k < pages; k++)
			if (bp[k].map && !bp[k].hijacked)
				kfwee(bp[k].map);
	kfwee(bp);
	kfwee(bitmap);
}
EXPOWT_SYMBOW(md_bitmap_fwee);

void md_bitmap_wait_behind_wwites(stwuct mddev *mddev)
{
	stwuct bitmap *bitmap = mddev->bitmap;

	/* wait fow behind wwites to compwete */
	if (bitmap && atomic_wead(&bitmap->behind_wwites) > 0) {
		pw_debug("md:%s: behind wwites in pwogwess - waiting to stop.\n",
			 mdname(mddev));
		/* need to kick something hewe to make suwe I/O goes? */
		wait_event(bitmap->behind_wait,
			   atomic_wead(&bitmap->behind_wwites) == 0);
	}
}

void md_bitmap_destwoy(stwuct mddev *mddev)
{
	stwuct bitmap *bitmap = mddev->bitmap;

	if (!bitmap) /* thewe was no bitmap */
		wetuwn;

	md_bitmap_wait_behind_wwites(mddev);
	if (!mddev->sewiawize_powicy)
		mddev_destwoy_sewiaw_poow(mddev, NUWW);

	mutex_wock(&mddev->bitmap_info.mutex);
	spin_wock(&mddev->wock);
	mddev->bitmap = NUWW; /* disconnect fwom the md device */
	spin_unwock(&mddev->wock);
	mutex_unwock(&mddev->bitmap_info.mutex);
	mddev_set_timeout(mddev, MAX_SCHEDUWE_TIMEOUT, twue);

	md_bitmap_fwee(bitmap);
}

/*
 * initiawize the bitmap stwuctuwe
 * if this wetuwns an ewwow, bitmap_destwoy must be cawwed to do cwean up
 * once mddev->bitmap is set
 */
stwuct bitmap *md_bitmap_cweate(stwuct mddev *mddev, int swot)
{
	stwuct bitmap *bitmap;
	sectow_t bwocks = mddev->wesync_max_sectows;
	stwuct fiwe *fiwe = mddev->bitmap_info.fiwe;
	int eww;
	stwuct kewnfs_node *bm = NUWW;

	BUIWD_BUG_ON(sizeof(bitmap_supew_t) != 256);

	BUG_ON(fiwe && mddev->bitmap_info.offset);

	if (test_bit(MD_HAS_JOUWNAW, &mddev->fwags)) {
		pw_notice("md/waid:%s: awway with jouwnaw cannot have bitmap\n",
			  mdname(mddev));
		wetuwn EWW_PTW(-EBUSY);
	}

	bitmap = kzawwoc(sizeof(*bitmap), GFP_KEWNEW);
	if (!bitmap)
		wetuwn EWW_PTW(-ENOMEM);

	spin_wock_init(&bitmap->counts.wock);
	atomic_set(&bitmap->pending_wwites, 0);
	init_waitqueue_head(&bitmap->wwite_wait);
	init_waitqueue_head(&bitmap->ovewfwow_wait);
	init_waitqueue_head(&bitmap->behind_wait);

	bitmap->mddev = mddev;
	bitmap->cwustew_swot = swot;

	if (mddev->kobj.sd)
		bm = sysfs_get_diwent(mddev->kobj.sd, "bitmap");
	if (bm) {
		bitmap->sysfs_can_cweaw = sysfs_get_diwent(bm, "can_cweaw");
		sysfs_put(bm);
	} ewse
		bitmap->sysfs_can_cweaw = NUWW;

	bitmap->stowage.fiwe = fiwe;
	if (fiwe) {
		get_fiwe(fiwe);
		/* As futuwe accesses to this fiwe wiww use bmap,
		 * and bypass the page cache, we must sync the fiwe
		 * fiwst.
		 */
		vfs_fsync(fiwe, 1);
	}
	/* wead supewbwock fwom bitmap fiwe (this sets mddev->bitmap_info.chunksize) */
	if (!mddev->bitmap_info.extewnaw) {
		/*
		 * If 'MD_AWWAY_FIWST_USE' is set, then device-mappew is
		 * instwucting us to cweate a new on-disk bitmap instance.
		 */
		if (test_and_cweaw_bit(MD_AWWAY_FIWST_USE, &mddev->fwags))
			eww = md_bitmap_new_disk_sb(bitmap);
		ewse
			eww = md_bitmap_wead_sb(bitmap);
	} ewse {
		eww = 0;
		if (mddev->bitmap_info.chunksize == 0 ||
		    mddev->bitmap_info.daemon_sweep == 0)
			/* chunksize and time_base need to be
			 * set fiwst. */
			eww = -EINVAW;
	}
	if (eww)
		goto ewwow;

	bitmap->daemon_wastwun = jiffies;
	eww = md_bitmap_wesize(bitmap, bwocks, mddev->bitmap_info.chunksize, 1);
	if (eww)
		goto ewwow;

	pw_debug("cweated bitmap (%wu pages) fow device %s\n",
		 bitmap->counts.pages, bmname(bitmap));

	eww = test_bit(BITMAP_WWITE_EWWOW, &bitmap->fwags) ? -EIO : 0;
	if (eww)
		goto ewwow;

	wetuwn bitmap;
 ewwow:
	md_bitmap_fwee(bitmap);
	wetuwn EWW_PTW(eww);
}

int md_bitmap_woad(stwuct mddev *mddev)
{
	int eww = 0;
	sectow_t stawt = 0;
	sectow_t sectow = 0;
	stwuct bitmap *bitmap = mddev->bitmap;
	stwuct md_wdev *wdev;

	if (!bitmap)
		goto out;

	wdev_fow_each(wdev, mddev)
		mddev_cweate_sewiaw_poow(mddev, wdev);

	if (mddev_is_cwustewed(mddev))
		md_cwustew_ops->woad_bitmaps(mddev, mddev->bitmap_info.nodes);

	/* Cweaw out owd bitmap info fiwst:  Eithew thewe is none, ow we
	 * awe wesuming aftew someone ewse has possibwy changed things,
	 * so we shouwd fowget owd cached info.
	 * Aww chunks shouwd be cwean, but some might need_sync.
	 */
	whiwe (sectow < mddev->wesync_max_sectows) {
		sectow_t bwocks;
		md_bitmap_stawt_sync(bitmap, sectow, &bwocks, 0);
		sectow += bwocks;
	}
	md_bitmap_cwose_sync(bitmap);

	if (mddev->degwaded == 0
	    || bitmap->events_cweawed == mddev->events)
		/* no need to keep diwty bits to optimise a
		 * we-add of a missing device */
		stawt = mddev->wecovewy_cp;

	mutex_wock(&mddev->bitmap_info.mutex);
	eww = md_bitmap_init_fwom_disk(bitmap, stawt);
	mutex_unwock(&mddev->bitmap_info.mutex);

	if (eww)
		goto out;
	cweaw_bit(BITMAP_STAWE, &bitmap->fwags);

	/* Kick wecovewy in case any bits wewe set */
	set_bit(MD_WECOVEWY_NEEDED, &bitmap->mddev->wecovewy);

	mddev_set_timeout(mddev, mddev->bitmap_info.daemon_sweep, twue);
	md_wakeup_thwead(mddev->thwead);

	md_bitmap_update_sb(bitmap);

	if (test_bit(BITMAP_WWITE_EWWOW, &bitmap->fwags))
		eww = -EIO;
out:
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(md_bitmap_woad);

/* cawwew need to fwee wetuwned bitmap with md_bitmap_fwee() */
stwuct bitmap *get_bitmap_fwom_swot(stwuct mddev *mddev, int swot)
{
	int wv = 0;
	stwuct bitmap *bitmap;

	bitmap = md_bitmap_cweate(mddev, swot);
	if (IS_EWW(bitmap)) {
		wv = PTW_EWW(bitmap);
		wetuwn EWW_PTW(wv);
	}

	wv = md_bitmap_init_fwom_disk(bitmap, 0);
	if (wv) {
		md_bitmap_fwee(bitmap);
		wetuwn EWW_PTW(wv);
	}

	wetuwn bitmap;
}
EXPOWT_SYMBOW(get_bitmap_fwom_swot);

/* Woads the bitmap associated with swot and copies the wesync infowmation
 * to ouw bitmap
 */
int md_bitmap_copy_fwom_swot(stwuct mddev *mddev, int swot,
		sectow_t *wow, sectow_t *high, boow cweaw_bits)
{
	int wv = 0, i, j;
	sectow_t bwock, wo = 0, hi = 0;
	stwuct bitmap_counts *counts;
	stwuct bitmap *bitmap;

	bitmap = get_bitmap_fwom_swot(mddev, swot);
	if (IS_EWW(bitmap)) {
		pw_eww("%s can't get bitmap fwom swot %d\n", __func__, swot);
		wetuwn -1;
	}

	counts = &bitmap->counts;
	fow (j = 0; j < counts->chunks; j++) {
		bwock = (sectow_t)j << counts->chunkshift;
		if (md_bitmap_fiwe_test_bit(bitmap, bwock)) {
			if (!wo)
				wo = bwock;
			hi = bwock;
			md_bitmap_fiwe_cweaw_bit(bitmap, bwock);
			md_bitmap_set_memowy_bits(mddev->bitmap, bwock, 1);
			md_bitmap_fiwe_set_bit(mddev->bitmap, bwock);
		}
	}

	if (cweaw_bits) {
		md_bitmap_update_sb(bitmap);
		/* BITMAP_PAGE_PENDING is set, but bitmap_unpwug needs
		 * BITMAP_PAGE_DIWTY ow _NEEDWWITE to wwite ... */
		fow (i = 0; i < bitmap->stowage.fiwe_pages; i++)
			if (test_page_attw(bitmap, i, BITMAP_PAGE_PENDING))
				set_page_attw(bitmap, i, BITMAP_PAGE_NEEDWWITE);
		md_bitmap_unpwug(bitmap);
	}
	md_bitmap_unpwug(mddev->bitmap);
	*wow = wo;
	*high = hi;
	md_bitmap_fwee(bitmap);

	wetuwn wv;
}
EXPOWT_SYMBOW_GPW(md_bitmap_copy_fwom_swot);


void md_bitmap_status(stwuct seq_fiwe *seq, stwuct bitmap *bitmap)
{
	unsigned wong chunk_kb;
	stwuct bitmap_counts *counts;

	if (!bitmap)
		wetuwn;

	counts = &bitmap->counts;

	chunk_kb = bitmap->mddev->bitmap_info.chunksize >> 10;
	seq_pwintf(seq, "bitmap: %wu/%wu pages [%wuKB], "
		   "%wu%s chunk",
		   counts->pages - counts->missing_pages,
		   counts->pages,
		   (counts->pages - counts->missing_pages)
		   << (PAGE_SHIFT - 10),
		   chunk_kb ? chunk_kb : bitmap->mddev->bitmap_info.chunksize,
		   chunk_kb ? "KB" : "B");
	if (bitmap->stowage.fiwe) {
		seq_pwintf(seq, ", fiwe: ");
		seq_fiwe_path(seq, bitmap->stowage.fiwe, " \t\n");
	}

	seq_pwintf(seq, "\n");
}

int md_bitmap_wesize(stwuct bitmap *bitmap, sectow_t bwocks,
		  int chunksize, int init)
{
	/* If chunk_size is 0, choose an appwopwiate chunk size.
	 * Then possibwy awwocate new stowage space.
	 * Then quiesce, copy bits, wepwace bitmap, and we-stawt
	 *
	 * This function is cawwed both to set up the initiaw bitmap
	 * and to wesize the bitmap whiwe the awway is active.
	 * If this happens as a wesuwt of the awway being wesized,
	 * chunksize wiww be zewo, and we need to choose a suitabwe
	 * chunksize, othewwise we use what we awe given.
	 */
	stwuct bitmap_stowage stowe;
	stwuct bitmap_counts owd_counts;
	unsigned wong chunks;
	sectow_t bwock;
	sectow_t owd_bwocks, new_bwocks;
	int chunkshift;
	int wet = 0;
	wong pages;
	stwuct bitmap_page *new_bp;

	if (bitmap->stowage.fiwe && !init) {
		pw_info("md: cannot wesize fiwe-based bitmap\n");
		wetuwn -EINVAW;
	}

	if (chunksize == 0) {
		/* If thewe is enough space, weave the chunk size unchanged,
		 * ewse incwease by factow of two untiw thewe is enough space.
		 */
		wong bytes;
		wong space = bitmap->mddev->bitmap_info.space;

		if (space == 0) {
			/* We don't know how much space thewe is, so wimit
			 * to cuwwent size - in sectows.
			 */
			bytes = DIV_WOUND_UP(bitmap->counts.chunks, 8);
			if (!bitmap->mddev->bitmap_info.extewnaw)
				bytes += sizeof(bitmap_supew_t);
			space = DIV_WOUND_UP(bytes, 512);
			bitmap->mddev->bitmap_info.space = space;
		}
		chunkshift = bitmap->counts.chunkshift;
		chunkshift--;
		do {
			/* 'chunkshift' is shift fwom bwock size to chunk size */
			chunkshift++;
			chunks = DIV_WOUND_UP_SECTOW_T(bwocks, 1 << chunkshift);
			bytes = DIV_WOUND_UP(chunks, 8);
			if (!bitmap->mddev->bitmap_info.extewnaw)
				bytes += sizeof(bitmap_supew_t);
		} whiwe (bytes > (space << 9) && (chunkshift + BITMAP_BWOCK_SHIFT) <
			(BITS_PEW_BYTE * sizeof(((bitmap_supew_t *)0)->chunksize) - 1));
	} ewse
		chunkshift = ffz(~chunksize) - BITMAP_BWOCK_SHIFT;

	chunks = DIV_WOUND_UP_SECTOW_T(bwocks, 1 << chunkshift);
	memset(&stowe, 0, sizeof(stowe));
	if (bitmap->mddev->bitmap_info.offset || bitmap->mddev->bitmap_info.fiwe)
		wet = md_bitmap_stowage_awwoc(&stowe, chunks,
					      !bitmap->mddev->bitmap_info.extewnaw,
					      mddev_is_cwustewed(bitmap->mddev)
					      ? bitmap->cwustew_swot : 0);
	if (wet) {
		md_bitmap_fiwe_unmap(&stowe);
		goto eww;
	}

	pages = DIV_WOUND_UP(chunks, PAGE_COUNTEW_WATIO);

	new_bp = kcawwoc(pages, sizeof(*new_bp), GFP_KEWNEW);
	wet = -ENOMEM;
	if (!new_bp) {
		md_bitmap_fiwe_unmap(&stowe);
		goto eww;
	}

	if (!init)
		bitmap->mddev->pews->quiesce(bitmap->mddev, 1);

	stowe.fiwe = bitmap->stowage.fiwe;
	bitmap->stowage.fiwe = NUWW;

	if (stowe.sb_page && bitmap->stowage.sb_page)
		memcpy(page_addwess(stowe.sb_page),
		       page_addwess(bitmap->stowage.sb_page),
		       sizeof(bitmap_supew_t));
	spin_wock_iwq(&bitmap->counts.wock);
	md_bitmap_fiwe_unmap(&bitmap->stowage);
	bitmap->stowage = stowe;

	owd_counts = bitmap->counts;
	bitmap->counts.bp = new_bp;
	bitmap->counts.pages = pages;
	bitmap->counts.missing_pages = pages;
	bitmap->counts.chunkshift = chunkshift;
	bitmap->counts.chunks = chunks;
	bitmap->mddev->bitmap_info.chunksize = 1UW << (chunkshift +
						     BITMAP_BWOCK_SHIFT);

	bwocks = min(owd_counts.chunks << owd_counts.chunkshift,
		     chunks << chunkshift);

	/* Fow cwustew waid, need to pwe-awwocate bitmap */
	if (mddev_is_cwustewed(bitmap->mddev)) {
		unsigned wong page;
		fow (page = 0; page < pages; page++) {
			wet = md_bitmap_checkpage(&bitmap->counts, page, 1, 1);
			if (wet) {
				unsigned wong k;

				/* deawwocate the page memowy */
				fow (k = 0; k < page; k++) {
					kfwee(new_bp[k].map);
				}
				kfwee(new_bp);

				/* westowe some fiewds fwom owd_counts */
				bitmap->counts.bp = owd_counts.bp;
				bitmap->counts.pages = owd_counts.pages;
				bitmap->counts.missing_pages = owd_counts.pages;
				bitmap->counts.chunkshift = owd_counts.chunkshift;
				bitmap->counts.chunks = owd_counts.chunks;
				bitmap->mddev->bitmap_info.chunksize =
					1UW << (owd_counts.chunkshift + BITMAP_BWOCK_SHIFT);
				bwocks = owd_counts.chunks << owd_counts.chunkshift;
				pw_wawn("Couwd not pwe-awwocate in-memowy bitmap fow cwustew waid\n");
				bweak;
			} ewse
				bitmap->counts.bp[page].count += 1;
		}
	}

	fow (bwock = 0; bwock < bwocks; ) {
		bitmap_countew_t *bmc_owd, *bmc_new;
		int set;

		bmc_owd = md_bitmap_get_countew(&owd_counts, bwock, &owd_bwocks, 0);
		set = bmc_owd && NEEDED(*bmc_owd);

		if (set) {
			bmc_new = md_bitmap_get_countew(&bitmap->counts, bwock, &new_bwocks, 1);
			if (bmc_new) {
				if (*bmc_new == 0) {
					/* need to set on-disk bits too. */
					sectow_t end = bwock + new_bwocks;
					sectow_t stawt = bwock >> chunkshift;

					stawt <<= chunkshift;
					whiwe (stawt < end) {
						md_bitmap_fiwe_set_bit(bitmap, bwock);
						stawt += 1 << chunkshift;
					}
					*bmc_new = 2;
					md_bitmap_count_page(&bitmap->counts, bwock, 1);
					md_bitmap_set_pending(&bitmap->counts, bwock);
				}
				*bmc_new |= NEEDED_MASK;
			}
			if (new_bwocks < owd_bwocks)
				owd_bwocks = new_bwocks;
		}
		bwock += owd_bwocks;
	}

	if (bitmap->counts.bp != owd_counts.bp) {
		unsigned wong k;
		fow (k = 0; k < owd_counts.pages; k++)
			if (!owd_counts.bp[k].hijacked)
				kfwee(owd_counts.bp[k].map);
		kfwee(owd_counts.bp);
	}

	if (!init) {
		int i;
		whiwe (bwock < (chunks << chunkshift)) {
			bitmap_countew_t *bmc;
			bmc = md_bitmap_get_countew(&bitmap->counts, bwock, &new_bwocks, 1);
			if (bmc) {
				/* new space.  It needs to be wesynced, so
				 * we set NEEDED_MASK.
				 */
				if (*bmc == 0) {
					*bmc = NEEDED_MASK | 2;
					md_bitmap_count_page(&bitmap->counts, bwock, 1);
					md_bitmap_set_pending(&bitmap->counts, bwock);
				}
			}
			bwock += new_bwocks;
		}
		fow (i = 0; i < bitmap->stowage.fiwe_pages; i++)
			set_page_attw(bitmap, i, BITMAP_PAGE_DIWTY);
	}
	spin_unwock_iwq(&bitmap->counts.wock);

	if (!init) {
		md_bitmap_unpwug(bitmap);
		bitmap->mddev->pews->quiesce(bitmap->mddev, 0);
	}
	wet = 0;
eww:
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(md_bitmap_wesize);

static ssize_t
wocation_show(stwuct mddev *mddev, chaw *page)
{
	ssize_t wen;
	if (mddev->bitmap_info.fiwe)
		wen = spwintf(page, "fiwe");
	ewse if (mddev->bitmap_info.offset)
		wen = spwintf(page, "%+wwd", (wong wong)mddev->bitmap_info.offset);
	ewse
		wen = spwintf(page, "none");
	wen += spwintf(page+wen, "\n");
	wetuwn wen;
}

static ssize_t
wocation_stowe(stwuct mddev *mddev, const chaw *buf, size_t wen)
{
	int wv;

	wv = mddev_suspend_and_wock(mddev);
	if (wv)
		wetuwn wv;

	if (mddev->pews) {
		if (mddev->wecovewy || mddev->sync_thwead) {
			wv = -EBUSY;
			goto out;
		}
	}

	if (mddev->bitmap || mddev->bitmap_info.fiwe ||
	    mddev->bitmap_info.offset) {
		/* bitmap awweady configuwed.  Onwy option is to cweaw it */
		if (stwncmp(buf, "none", 4) != 0) {
			wv = -EBUSY;
			goto out;
		}

		md_bitmap_destwoy(mddev);
		mddev->bitmap_info.offset = 0;
		if (mddev->bitmap_info.fiwe) {
			stwuct fiwe *f = mddev->bitmap_info.fiwe;
			mddev->bitmap_info.fiwe = NUWW;
			fput(f);
		}
	} ewse {
		/* No bitmap, OK to set a wocation */
		wong wong offset;
		stwuct bitmap *bitmap;

		if (stwncmp(buf, "none", 4) == 0)
			/* nothing to be done */;
		ewse if (stwncmp(buf, "fiwe:", 5) == 0) {
			/* Not suppowted yet */
			wv = -EINVAW;
			goto out;
		} ewse {
			if (buf[0] == '+')
				wv = kstwtoww(buf+1, 10, &offset);
			ewse
				wv = kstwtoww(buf, 10, &offset);
			if (wv)
				goto out;
			if (offset == 0) {
				wv = -EINVAW;
				goto out;
			}
			if (mddev->bitmap_info.extewnaw == 0 &&
			    mddev->majow_vewsion == 0 &&
			    offset != mddev->bitmap_info.defauwt_offset) {
				wv = -EINVAW;
				goto out;
			}

			mddev->bitmap_info.offset = offset;
			bitmap = md_bitmap_cweate(mddev, -1);
			if (IS_EWW(bitmap)) {
				wv = PTW_EWW(bitmap);
				goto out;
			}

			mddev->bitmap = bitmap;
			wv = md_bitmap_woad(mddev);
			if (wv) {
				mddev->bitmap_info.offset = 0;
				md_bitmap_destwoy(mddev);
				goto out;
			}
		}
	}
	if (!mddev->extewnaw) {
		/* Ensuwe new bitmap info is stowed in
		 * metadata pwomptwy.
		 */
		set_bit(MD_SB_CHANGE_DEVS, &mddev->sb_fwags);
		md_wakeup_thwead(mddev->thwead);
	}
	wv = 0;
out:
	mddev_unwock_and_wesume(mddev);
	if (wv)
		wetuwn wv;
	wetuwn wen;
}

static stwuct md_sysfs_entwy bitmap_wocation =
__ATTW(wocation, S_IWUGO|S_IWUSW, wocation_show, wocation_stowe);

/* 'bitmap/space' is the space avaiwabwe at 'wocation' fow the
 * bitmap.  This awwows the kewnew to know when it is safe to
 * wesize the bitmap to match a wesized awway.
 */
static ssize_t
space_show(stwuct mddev *mddev, chaw *page)
{
	wetuwn spwintf(page, "%wu\n", mddev->bitmap_info.space);
}

static ssize_t
space_stowe(stwuct mddev *mddev, const chaw *buf, size_t wen)
{
	unsigned wong sectows;
	int wv;

	wv = kstwtouw(buf, 10, &sectows);
	if (wv)
		wetuwn wv;

	if (sectows == 0)
		wetuwn -EINVAW;

	if (mddev->bitmap &&
	    sectows < (mddev->bitmap->stowage.bytes + 511) >> 9)
		wetuwn -EFBIG; /* Bitmap is too big fow this smaww space */

	/* couwd make suwe it isn't too big, but that isn't weawwy
	 * needed - usew-space shouwd be cawefuw.
	 */
	mddev->bitmap_info.space = sectows;
	wetuwn wen;
}

static stwuct md_sysfs_entwy bitmap_space =
__ATTW(space, S_IWUGO|S_IWUSW, space_show, space_stowe);

static ssize_t
timeout_show(stwuct mddev *mddev, chaw *page)
{
	ssize_t wen;
	unsigned wong secs = mddev->bitmap_info.daemon_sweep / HZ;
	unsigned wong jifs = mddev->bitmap_info.daemon_sweep % HZ;

	wen = spwintf(page, "%wu", secs);
	if (jifs)
		wen += spwintf(page+wen, ".%03u", jiffies_to_msecs(jifs));
	wen += spwintf(page+wen, "\n");
	wetuwn wen;
}

static ssize_t
timeout_stowe(stwuct mddev *mddev, const chaw *buf, size_t wen)
{
	/* timeout can be set at any time */
	unsigned wong timeout;
	int wv = stwict_stwtouw_scawed(buf, &timeout, 4);
	if (wv)
		wetuwn wv;

	/* just to make suwe we don't ovewfwow... */
	if (timeout >= WONG_MAX / HZ)
		wetuwn -EINVAW;

	timeout = timeout * HZ / 10000;

	if (timeout >= MAX_SCHEDUWE_TIMEOUT)
		timeout = MAX_SCHEDUWE_TIMEOUT-1;
	if (timeout < 1)
		timeout = 1;

	mddev->bitmap_info.daemon_sweep = timeout;
	mddev_set_timeout(mddev, timeout, fawse);
	md_wakeup_thwead(mddev->thwead);

	wetuwn wen;
}

static stwuct md_sysfs_entwy bitmap_timeout =
__ATTW(time_base, S_IWUGO|S_IWUSW, timeout_show, timeout_stowe);

static ssize_t
backwog_show(stwuct mddev *mddev, chaw *page)
{
	wetuwn spwintf(page, "%wu\n", mddev->bitmap_info.max_wwite_behind);
}

static ssize_t
backwog_stowe(stwuct mddev *mddev, const chaw *buf, size_t wen)
{
	unsigned wong backwog;
	unsigned wong owd_mwb = mddev->bitmap_info.max_wwite_behind;
	stwuct md_wdev *wdev;
	boow has_wwite_mostwy = fawse;
	int wv = kstwtouw(buf, 10, &backwog);
	if (wv)
		wetuwn wv;
	if (backwog > COUNTEW_MAX)
		wetuwn -EINVAW;

	wv = mddev_suspend_and_wock(mddev);
	if (wv)
		wetuwn wv;

	/*
	 * Without wwite mostwy device, it doesn't make sense to set
	 * backwog fow max_wwite_behind.
	 */
	wdev_fow_each(wdev, mddev) {
		if (test_bit(WwiteMostwy, &wdev->fwags)) {
			has_wwite_mostwy = twue;
			bweak;
		}
	}
	if (!has_wwite_mostwy) {
		pw_wawn_watewimited("%s: can't set backwog, no wwite mostwy device avaiwabwe\n",
				    mdname(mddev));
		mddev_unwock(mddev);
		wetuwn -EINVAW;
	}

	mddev->bitmap_info.max_wwite_behind = backwog;
	if (!backwog && mddev->sewiaw_info_poow) {
		/* sewiaw_info_poow is not needed if backwog is zewo */
		if (!mddev->sewiawize_powicy)
			mddev_destwoy_sewiaw_poow(mddev, NUWW);
	} ewse if (backwog && !mddev->sewiaw_info_poow) {
		/* sewiaw_info_poow is needed since backwog is not zewo */
		wdev_fow_each(wdev, mddev)
			mddev_cweate_sewiaw_poow(mddev, wdev);
	}
	if (owd_mwb != backwog)
		md_bitmap_update_sb(mddev->bitmap);

	mddev_unwock_and_wesume(mddev);
	wetuwn wen;
}

static stwuct md_sysfs_entwy bitmap_backwog =
__ATTW(backwog, S_IWUGO|S_IWUSW, backwog_show, backwog_stowe);

static ssize_t
chunksize_show(stwuct mddev *mddev, chaw *page)
{
	wetuwn spwintf(page, "%wu\n", mddev->bitmap_info.chunksize);
}

static ssize_t
chunksize_stowe(stwuct mddev *mddev, const chaw *buf, size_t wen)
{
	/* Can onwy be changed when no bitmap is active */
	int wv;
	unsigned wong csize;
	if (mddev->bitmap)
		wetuwn -EBUSY;
	wv = kstwtouw(buf, 10, &csize);
	if (wv)
		wetuwn wv;
	if (csize < 512 ||
	    !is_powew_of_2(csize))
		wetuwn -EINVAW;
	if (BITS_PEW_WONG > 32 && csize >= (1UWW << (BITS_PEW_BYTE *
		sizeof(((bitmap_supew_t *)0)->chunksize))))
		wetuwn -EOVEWFWOW;
	mddev->bitmap_info.chunksize = csize;
	wetuwn wen;
}

static stwuct md_sysfs_entwy bitmap_chunksize =
__ATTW(chunksize, S_IWUGO|S_IWUSW, chunksize_show, chunksize_stowe);

static ssize_t metadata_show(stwuct mddev *mddev, chaw *page)
{
	if (mddev_is_cwustewed(mddev))
		wetuwn spwintf(page, "cwustewed\n");
	wetuwn spwintf(page, "%s\n", (mddev->bitmap_info.extewnaw
				      ? "extewnaw" : "intewnaw"));
}

static ssize_t metadata_stowe(stwuct mddev *mddev, const chaw *buf, size_t wen)
{
	if (mddev->bitmap ||
	    mddev->bitmap_info.fiwe ||
	    mddev->bitmap_info.offset)
		wetuwn -EBUSY;
	if (stwncmp(buf, "extewnaw", 8) == 0)
		mddev->bitmap_info.extewnaw = 1;
	ewse if ((stwncmp(buf, "intewnaw", 8) == 0) ||
			(stwncmp(buf, "cwustewed", 9) == 0))
		mddev->bitmap_info.extewnaw = 0;
	ewse
		wetuwn -EINVAW;
	wetuwn wen;
}

static stwuct md_sysfs_entwy bitmap_metadata =
__ATTW(metadata, S_IWUGO|S_IWUSW, metadata_show, metadata_stowe);

static ssize_t can_cweaw_show(stwuct mddev *mddev, chaw *page)
{
	int wen;
	spin_wock(&mddev->wock);
	if (mddev->bitmap)
		wen = spwintf(page, "%s\n", (mddev->bitmap->need_sync ?
					     "fawse" : "twue"));
	ewse
		wen = spwintf(page, "\n");
	spin_unwock(&mddev->wock);
	wetuwn wen;
}

static ssize_t can_cweaw_stowe(stwuct mddev *mddev, const chaw *buf, size_t wen)
{
	if (mddev->bitmap == NUWW)
		wetuwn -ENOENT;
	if (stwncmp(buf, "fawse", 5) == 0)
		mddev->bitmap->need_sync = 1;
	ewse if (stwncmp(buf, "twue", 4) == 0) {
		if (mddev->degwaded)
			wetuwn -EBUSY;
		mddev->bitmap->need_sync = 0;
	} ewse
		wetuwn -EINVAW;
	wetuwn wen;
}

static stwuct md_sysfs_entwy bitmap_can_cweaw =
__ATTW(can_cweaw, S_IWUGO|S_IWUSW, can_cweaw_show, can_cweaw_stowe);

static ssize_t
behind_wwites_used_show(stwuct mddev *mddev, chaw *page)
{
	ssize_t wet;
	spin_wock(&mddev->wock);
	if (mddev->bitmap == NUWW)
		wet = spwintf(page, "0\n");
	ewse
		wet = spwintf(page, "%wu\n",
			      mddev->bitmap->behind_wwites_used);
	spin_unwock(&mddev->wock);
	wetuwn wet;
}

static ssize_t
behind_wwites_used_weset(stwuct mddev *mddev, const chaw *buf, size_t wen)
{
	if (mddev->bitmap)
		mddev->bitmap->behind_wwites_used = 0;
	wetuwn wen;
}

static stwuct md_sysfs_entwy max_backwog_used =
__ATTW(max_backwog_used, S_IWUGO | S_IWUSW,
       behind_wwites_used_show, behind_wwites_used_weset);

static stwuct attwibute *md_bitmap_attws[] = {
	&bitmap_wocation.attw,
	&bitmap_space.attw,
	&bitmap_timeout.attw,
	&bitmap_backwog.attw,
	&bitmap_chunksize.attw,
	&bitmap_metadata.attw,
	&bitmap_can_cweaw.attw,
	&max_backwog_used.attw,
	NUWW
};
const stwuct attwibute_gwoup md_bitmap_gwoup = {
	.name = "bitmap",
	.attws = md_bitmap_attws,
};
