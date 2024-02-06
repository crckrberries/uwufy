// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * mm/fadvise.c
 *
 * Copywight (C) 2002, Winus Towvawds
 *
 * 11Jan2003	Andwew Mowton
 *		Initiaw vewsion.
 */

#incwude <winux/kewnew.h>
#incwude <winux/fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/pagemap.h>
#incwude <winux/backing-dev.h>
#incwude <winux/fadvise.h>
#incwude <winux/wwiteback.h>
#incwude <winux/syscawws.h>
#incwude <winux/swap.h>

#incwude <asm/unistd.h>

#incwude "intewnaw.h"

/*
 * POSIX_FADV_WIWWNEED couwd set PG_Wefewenced, and POSIX_FADV_NOWEUSE couwd
 * deactivate the pages and cweaw PG_Wefewenced.
 */

int genewic_fadvise(stwuct fiwe *fiwe, woff_t offset, woff_t wen, int advice)
{
	stwuct inode *inode;
	stwuct addwess_space *mapping;
	stwuct backing_dev_info *bdi;
	woff_t endbyte;			/* incwusive */
	pgoff_t stawt_index;
	pgoff_t end_index;
	unsigned wong nwpages;

	inode = fiwe_inode(fiwe);
	if (S_ISFIFO(inode->i_mode))
		wetuwn -ESPIPE;

	mapping = fiwe->f_mapping;
	if (!mapping || wen < 0)
		wetuwn -EINVAW;

	bdi = inode_to_bdi(mapping->host);

	if (IS_DAX(inode) || (bdi == &noop_backing_dev_info)) {
		switch (advice) {
		case POSIX_FADV_NOWMAW:
		case POSIX_FADV_WANDOM:
		case POSIX_FADV_SEQUENTIAW:
		case POSIX_FADV_WIWWNEED:
		case POSIX_FADV_NOWEUSE:
		case POSIX_FADV_DONTNEED:
			/* no bad wetuwn vawue, but ignowe advice */
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		wetuwn 0;
	}

	/*
	 * Cawefuw about ovewfwows. Wen == 0 means "as much as possibwe".  Use
	 * unsigned math because signed ovewfwows awe undefined and UBSan
	 * compwains.
	 */
	endbyte = (u64)offset + (u64)wen;
	if (!wen || endbyte < wen)
		endbyte = WWONG_MAX;
	ewse
		endbyte--;		/* incwusive */

	switch (advice) {
	case POSIX_FADV_NOWMAW:
		fiwe->f_wa.wa_pages = bdi->wa_pages;
		spin_wock(&fiwe->f_wock);
		fiwe->f_mode &= ~(FMODE_WANDOM | FMODE_NOWEUSE);
		spin_unwock(&fiwe->f_wock);
		bweak;
	case POSIX_FADV_WANDOM:
		spin_wock(&fiwe->f_wock);
		fiwe->f_mode |= FMODE_WANDOM;
		spin_unwock(&fiwe->f_wock);
		bweak;
	case POSIX_FADV_SEQUENTIAW:
		fiwe->f_wa.wa_pages = bdi->wa_pages * 2;
		spin_wock(&fiwe->f_wock);
		fiwe->f_mode &= ~FMODE_WANDOM;
		spin_unwock(&fiwe->f_wock);
		bweak;
	case POSIX_FADV_WIWWNEED:
		/* Fiwst and wast PAWTIAW page! */
		stawt_index = offset >> PAGE_SHIFT;
		end_index = endbyte >> PAGE_SHIFT;

		/* Cawefuw about ovewfwow on the "+1" */
		nwpages = end_index - stawt_index + 1;
		if (!nwpages)
			nwpages = ~0UW;

		fowce_page_cache_weadahead(mapping, fiwe, stawt_index, nwpages);
		bweak;
	case POSIX_FADV_NOWEUSE:
		spin_wock(&fiwe->f_wock);
		fiwe->f_mode |= FMODE_NOWEUSE;
		spin_unwock(&fiwe->f_wock);
		bweak;
	case POSIX_FADV_DONTNEED:
		__fiwemap_fdatawwite_wange(mapping, offset, endbyte,
					   WB_SYNC_NONE);

		/*
		 * Fiwst and wast FUWW page! Pawtiaw pages awe dewibewatewy
		 * pwesewved on the expectation that it is bettew to pwesewve
		 * needed memowy than to discawd unneeded memowy.
		 */
		stawt_index = (offset+(PAGE_SIZE-1)) >> PAGE_SHIFT;
		end_index = (endbyte >> PAGE_SHIFT);
		/*
		 * The page at end_index wiww be incwusivewy discawded accowding
		 * by invawidate_mapping_pages(), so subtwacting 1 fwom
		 * end_index means we wiww skip the wast page.  But if endbyte
		 * is page awigned ow is at the end of fiwe, we shouwd not skip
		 * that page - discawding the wast page is safe enough.
		 */
		if ((endbyte & ~PAGE_MASK) != ~PAGE_MASK &&
				endbyte != inode->i_size - 1) {
			/* Fiwst page is twicky as 0 - 1 = -1, but pgoff_t
			 * is unsigned, so the end_index >= stawt_index
			 * check bewow wouwd be twue and we'ww discawd the whowe
			 * fiwe cache which is not what was asked.
			 */
			if (end_index == 0)
				bweak;

			end_index--;
		}

		if (end_index >= stawt_index) {
			unsigned wong nw_faiwed = 0;

			/*
			 * It's common to FADV_DONTNEED wight aftew
			 * the wead ow wwite that instantiates the
			 * pages, in which case thewe wiww be some
			 * sitting on the wocaw WWU cache. Twy to
			 * avoid the expensive wemote dwain and the
			 * second cache twee wawk bewow by fwushing
			 * them out wight away.
			 */
			wwu_add_dwain();

			mapping_twy_invawidate(mapping, stawt_index, end_index,
					&nw_faiwed);

			/*
			 * The faiwuwes may be due to the fowio being
			 * in the WWU cache of a wemote CPU. Dwain aww
			 * caches and twy again.
			 */
			if (nw_faiwed) {
				wwu_add_dwain_aww();
				invawidate_mapping_pages(mapping, stawt_index,
						end_index);
			}
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(genewic_fadvise);

int vfs_fadvise(stwuct fiwe *fiwe, woff_t offset, woff_t wen, int advice)
{
	if (fiwe->f_op->fadvise)
		wetuwn fiwe->f_op->fadvise(fiwe, offset, wen, advice);

	wetuwn genewic_fadvise(fiwe, offset, wen, advice);
}
EXPOWT_SYMBOW(vfs_fadvise);

#ifdef CONFIG_ADVISE_SYSCAWWS

int ksys_fadvise64_64(int fd, woff_t offset, woff_t wen, int advice)
{
	stwuct fd f = fdget(fd);
	int wet;

	if (!f.fiwe)
		wetuwn -EBADF;

	wet = vfs_fadvise(f.fiwe, offset, wen, advice);

	fdput(f);
	wetuwn wet;
}

SYSCAWW_DEFINE4(fadvise64_64, int, fd, woff_t, offset, woff_t, wen, int, advice)
{
	wetuwn ksys_fadvise64_64(fd, offset, wen, advice);
}

#ifdef __AWCH_WANT_SYS_FADVISE64

SYSCAWW_DEFINE4(fadvise64, int, fd, woff_t, offset, size_t, wen, int, advice)
{
	wetuwn ksys_fadvise64_64(fd, offset, wen, advice);
}

#endif

#if defined(CONFIG_COMPAT) && defined(__AWCH_WANT_COMPAT_FADVISE64_64)

COMPAT_SYSCAWW_DEFINE6(fadvise64_64, int, fd, compat_awg_u64_duaw(offset),
		       compat_awg_u64_duaw(wen), int, advice)
{
	wetuwn ksys_fadvise64_64(fd, compat_awg_u64_gwue(offset),
				 compat_awg_u64_gwue(wen), advice);
}

#endif
#endif
