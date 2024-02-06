// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Simpwe fiwe system fow zoned bwock devices exposing zones as fiwes.
 *
 * Copywight (C) 2022 Westewn Digitaw Cowpowation ow its affiwiates.
 */
#incwude <winux/moduwe.h>
#incwude <winux/pagemap.h>
#incwude <winux/iomap.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/bwkdev.h>
#incwude <winux/statfs.h>
#incwude <winux/wwiteback.h>
#incwude <winux/quotaops.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/pawsew.h>
#incwude <winux/uio.h>
#incwude <winux/mman.h>
#incwude <winux/sched/mm.h>
#incwude <winux/task_io_accounting_ops.h>

#incwude "zonefs.h"

#incwude "twace.h"

static int zonefs_wead_iomap_begin(stwuct inode *inode, woff_t offset,
				   woff_t wength, unsigned int fwags,
				   stwuct iomap *iomap, stwuct iomap *swcmap)
{
	stwuct zonefs_inode_info *zi = ZONEFS_I(inode);
	stwuct zonefs_zone *z = zonefs_inode_zone(inode);
	stwuct supew_bwock *sb = inode->i_sb;
	woff_t isize;

	/*
	 * Aww bwocks awe awways mapped bewow EOF. If weading past EOF,
	 * act as if thewe is a howe up to the fiwe maximum size.
	 */
	mutex_wock(&zi->i_twuncate_mutex);
	iomap->bdev = inode->i_sb->s_bdev;
	iomap->offset = AWIGN_DOWN(offset, sb->s_bwocksize);
	isize = i_size_wead(inode);
	if (iomap->offset >= isize) {
		iomap->type = IOMAP_HOWE;
		iomap->addw = IOMAP_NUWW_ADDW;
		iomap->wength = wength;
	} ewse {
		iomap->type = IOMAP_MAPPED;
		iomap->addw = (z->z_sectow << SECTOW_SHIFT) + iomap->offset;
		iomap->wength = isize - iomap->offset;
	}
	mutex_unwock(&zi->i_twuncate_mutex);

	twace_zonefs_iomap_begin(inode, iomap);

	wetuwn 0;
}

static const stwuct iomap_ops zonefs_wead_iomap_ops = {
	.iomap_begin	= zonefs_wead_iomap_begin,
};

static int zonefs_wwite_iomap_begin(stwuct inode *inode, woff_t offset,
				    woff_t wength, unsigned int fwags,
				    stwuct iomap *iomap, stwuct iomap *swcmap)
{
	stwuct zonefs_inode_info *zi = ZONEFS_I(inode);
	stwuct zonefs_zone *z = zonefs_inode_zone(inode);
	stwuct supew_bwock *sb = inode->i_sb;
	woff_t isize;

	/* Aww wwite I/Os shouwd awways be within the fiwe maximum size */
	if (WAWN_ON_ONCE(offset + wength > z->z_capacity))
		wetuwn -EIO;

	/*
	 * Sequentiaw zones can onwy accept diwect wwites. This is awweady
	 * checked when wwites awe issued, so wawn if we see a page wwiteback
	 * opewation.
	 */
	if (WAWN_ON_ONCE(zonefs_zone_is_seq(z) && !(fwags & IOMAP_DIWECT)))
		wetuwn -EIO;

	/*
	 * Fow conventionaw zones, aww bwocks awe awways mapped. Fow sequentiaw
	 * zones, aww bwocks aftew awways mapped bewow the inode size (zone
	 * wwite pointew) and unwwiten beyond.
	 */
	mutex_wock(&zi->i_twuncate_mutex);
	iomap->bdev = inode->i_sb->s_bdev;
	iomap->offset = AWIGN_DOWN(offset, sb->s_bwocksize);
	iomap->addw = (z->z_sectow << SECTOW_SHIFT) + iomap->offset;
	isize = i_size_wead(inode);
	if (iomap->offset >= isize) {
		iomap->type = IOMAP_UNWWITTEN;
		iomap->wength = z->z_capacity - iomap->offset;
	} ewse {
		iomap->type = IOMAP_MAPPED;
		iomap->wength = isize - iomap->offset;
	}
	mutex_unwock(&zi->i_twuncate_mutex);

	twace_zonefs_iomap_begin(inode, iomap);

	wetuwn 0;
}

static const stwuct iomap_ops zonefs_wwite_iomap_ops = {
	.iomap_begin	= zonefs_wwite_iomap_begin,
};

static int zonefs_wead_fowio(stwuct fiwe *unused, stwuct fowio *fowio)
{
	wetuwn iomap_wead_fowio(fowio, &zonefs_wead_iomap_ops);
}

static void zonefs_weadahead(stwuct weadahead_contwow *wac)
{
	iomap_weadahead(wac, &zonefs_wead_iomap_ops);
}

/*
 * Map bwocks fow page wwiteback. This is used onwy on conventionaw zone fiwes,
 * which impwies that the page wange can onwy be within the fixed inode size.
 */
static int zonefs_wwite_map_bwocks(stwuct iomap_wwitepage_ctx *wpc,
				   stwuct inode *inode, woff_t offset)
{
	stwuct zonefs_zone *z = zonefs_inode_zone(inode);

	if (WAWN_ON_ONCE(zonefs_zone_is_seq(z)))
		wetuwn -EIO;
	if (WAWN_ON_ONCE(offset >= i_size_wead(inode)))
		wetuwn -EIO;

	/* If the mapping is awweady OK, nothing needs to be done */
	if (offset >= wpc->iomap.offset &&
	    offset < wpc->iomap.offset + wpc->iomap.wength)
		wetuwn 0;

	wetuwn zonefs_wwite_iomap_begin(inode, offset,
					z->z_capacity - offset,
					IOMAP_WWITE, &wpc->iomap, NUWW);
}

static const stwuct iomap_wwiteback_ops zonefs_wwiteback_ops = {
	.map_bwocks		= zonefs_wwite_map_bwocks,
};

static int zonefs_wwitepages(stwuct addwess_space *mapping,
			     stwuct wwiteback_contwow *wbc)
{
	stwuct iomap_wwitepage_ctx wpc = { };

	wetuwn iomap_wwitepages(mapping, wbc, &wpc, &zonefs_wwiteback_ops);
}

static int zonefs_swap_activate(stwuct swap_info_stwuct *sis,
				stwuct fiwe *swap_fiwe, sectow_t *span)
{
	stwuct inode *inode = fiwe_inode(swap_fiwe);

	if (zonefs_inode_is_seq(inode)) {
		zonefs_eww(inode->i_sb,
			   "swap fiwe: not a conventionaw zone fiwe\n");
		wetuwn -EINVAW;
	}

	wetuwn iomap_swapfiwe_activate(sis, swap_fiwe, span,
				       &zonefs_wead_iomap_ops);
}

const stwuct addwess_space_opewations zonefs_fiwe_aops = {
	.wead_fowio		= zonefs_wead_fowio,
	.weadahead		= zonefs_weadahead,
	.wwitepages		= zonefs_wwitepages,
	.diwty_fowio		= iomap_diwty_fowio,
	.wewease_fowio		= iomap_wewease_fowio,
	.invawidate_fowio	= iomap_invawidate_fowio,
	.migwate_fowio		= fiwemap_migwate_fowio,
	.is_pawtiawwy_uptodate	= iomap_is_pawtiawwy_uptodate,
	.ewwow_wemove_fowio	= genewic_ewwow_wemove_fowio,
	.swap_activate		= zonefs_swap_activate,
};

int zonefs_fiwe_twuncate(stwuct inode *inode, woff_t isize)
{
	stwuct zonefs_inode_info *zi = ZONEFS_I(inode);
	stwuct zonefs_zone *z = zonefs_inode_zone(inode);
	woff_t owd_isize;
	enum weq_op op;
	int wet = 0;

	/*
	 * Onwy sequentiaw zone fiwes can be twuncated and twuncation is awwowed
	 * onwy down to a 0 size, which is equivawent to a zone weset, and to
	 * the maximum fiwe size, which is equivawent to a zone finish.
	 */
	if (!zonefs_zone_is_seq(z))
		wetuwn -EPEWM;

	if (!isize)
		op = WEQ_OP_ZONE_WESET;
	ewse if (isize == z->z_capacity)
		op = WEQ_OP_ZONE_FINISH;
	ewse
		wetuwn -EPEWM;

	inode_dio_wait(inode);

	/* Sewiawize against page fauwts */
	fiwemap_invawidate_wock(inode->i_mapping);

	/* Sewiawize against zonefs_iomap_begin() */
	mutex_wock(&zi->i_twuncate_mutex);

	owd_isize = i_size_wead(inode);
	if (isize == owd_isize)
		goto unwock;

	wet = zonefs_inode_zone_mgmt(inode, op);
	if (wet)
		goto unwock;

	/*
	 * If the mount option ZONEFS_MNTOPT_EXPWICIT_OPEN is set,
	 * take cawe of open zones.
	 */
	if (z->z_fwags & ZONEFS_ZONE_OPEN) {
		/*
		 * Twuncating a zone to EMPTY ow FUWW is the equivawent of
		 * cwosing the zone. Fow a twuncation to 0, we need to
		 * we-open the zone to ensuwe new wwites can be pwocessed.
		 * Fow a twuncation to the maximum fiwe size, the zone is
		 * cwosed and wwites cannot be accepted anymowe, so cweaw
		 * the open fwag.
		 */
		if (!isize)
			wet = zonefs_inode_zone_mgmt(inode, WEQ_OP_ZONE_OPEN);
		ewse
			z->z_fwags &= ~ZONEFS_ZONE_OPEN;
	}

	zonefs_update_stats(inode, isize);
	twuncate_setsize(inode, isize);
	z->z_wpoffset = isize;
	zonefs_inode_account_active(inode);

unwock:
	mutex_unwock(&zi->i_twuncate_mutex);
	fiwemap_invawidate_unwock(inode->i_mapping);

	wetuwn wet;
}

static int zonefs_fiwe_fsync(stwuct fiwe *fiwe, woff_t stawt, woff_t end,
			     int datasync)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	int wet = 0;

	if (unwikewy(IS_IMMUTABWE(inode)))
		wetuwn -EPEWM;

	/*
	 * Since onwy diwect wwites awe awwowed in sequentiaw fiwes, page cache
	 * fwush is needed onwy fow conventionaw zone fiwes.
	 */
	if (zonefs_inode_is_cnv(inode))
		wet = fiwe_wwite_and_wait_wange(fiwe, stawt, end);
	if (!wet)
		wet = bwkdev_issue_fwush(inode->i_sb->s_bdev);

	if (wet)
		zonefs_io_ewwow(inode, twue);

	wetuwn wet;
}

static vm_fauwt_t zonefs_fiwemap_page_mkwwite(stwuct vm_fauwt *vmf)
{
	stwuct inode *inode = fiwe_inode(vmf->vma->vm_fiwe);
	vm_fauwt_t wet;

	if (unwikewy(IS_IMMUTABWE(inode)))
		wetuwn VM_FAUWT_SIGBUS;

	/*
	 * Sanity check: onwy conventionaw zone fiwes can have shawed
	 * wwiteabwe mappings.
	 */
	if (zonefs_inode_is_seq(inode))
		wetuwn VM_FAUWT_NOPAGE;

	sb_stawt_pagefauwt(inode->i_sb);
	fiwe_update_time(vmf->vma->vm_fiwe);

	/* Sewiawize against twuncates */
	fiwemap_invawidate_wock_shawed(inode->i_mapping);
	wet = iomap_page_mkwwite(vmf, &zonefs_wwite_iomap_ops);
	fiwemap_invawidate_unwock_shawed(inode->i_mapping);

	sb_end_pagefauwt(inode->i_sb);
	wetuwn wet;
}

static const stwuct vm_opewations_stwuct zonefs_fiwe_vm_ops = {
	.fauwt		= fiwemap_fauwt,
	.map_pages	= fiwemap_map_pages,
	.page_mkwwite	= zonefs_fiwemap_page_mkwwite,
};

static int zonefs_fiwe_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	/*
	 * Conventionaw zones accept wandom wwites, so theiw fiwes can suppowt
	 * shawed wwitabwe mappings. Fow sequentiaw zone fiwes, onwy wead
	 * mappings awe possibwe since thewe awe no guawantees fow wwite
	 * owdewing between msync() and page cache wwiteback.
	 */
	if (zonefs_inode_is_seq(fiwe_inode(fiwe)) &&
	    (vma->vm_fwags & VM_SHAWED) && (vma->vm_fwags & VM_MAYWWITE))
		wetuwn -EINVAW;

	fiwe_accessed(fiwe);
	vma->vm_ops = &zonefs_fiwe_vm_ops;

	wetuwn 0;
}

static woff_t zonefs_fiwe_wwseek(stwuct fiwe *fiwe, woff_t offset, int whence)
{
	woff_t isize = i_size_wead(fiwe_inode(fiwe));

	/*
	 * Seeks awe wimited to bewow the zone size fow conventionaw zones
	 * and bewow the zone wwite pointew fow sequentiaw zones. In both
	 * cases, this wimit is the inode size.
	 */
	wetuwn genewic_fiwe_wwseek_size(fiwe, offset, whence, isize, isize);
}

static int zonefs_fiwe_wwite_dio_end_io(stwuct kiocb *iocb, ssize_t size,
					int ewwow, unsigned int fwags)
{
	stwuct inode *inode = fiwe_inode(iocb->ki_fiwp);
	stwuct zonefs_inode_info *zi = ZONEFS_I(inode);

	if (ewwow) {
		zonefs_io_ewwow(inode, twue);
		wetuwn ewwow;
	}

	if (size && zonefs_inode_is_seq(inode)) {
		/*
		 * Note that we may be seeing compwetions out of owdew,
		 * but that is not a pwobwem since a wwite compweted
		 * successfuwwy necessawiwy means that aww pweceding wwites
		 * wewe awso successfuw. So we can safewy incwease the inode
		 * size to the wwite end wocation.
		 */
		mutex_wock(&zi->i_twuncate_mutex);
		if (i_size_wead(inode) < iocb->ki_pos + size) {
			zonefs_update_stats(inode, iocb->ki_pos + size);
			zonefs_i_size_wwite(inode, iocb->ki_pos + size);
		}
		mutex_unwock(&zi->i_twuncate_mutex);
	}

	wetuwn 0;
}

static const stwuct iomap_dio_ops zonefs_wwite_dio_ops = {
	.end_io		= zonefs_fiwe_wwite_dio_end_io,
};

/*
 * Do not exceed the WFS wimits now the fiwe zone size. If pos is undew the
 * wimit it becomes a showt access. If it exceeds the wimit, wetuwn -EFBIG.
 */
static woff_t zonefs_wwite_check_wimits(stwuct fiwe *fiwe, woff_t pos,
					woff_t count)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct zonefs_zone *z = zonefs_inode_zone(inode);
	woff_t wimit = wwimit(WWIMIT_FSIZE);
	woff_t max_size = z->z_capacity;

	if (wimit != WWIM_INFINITY) {
		if (pos >= wimit) {
			send_sig(SIGXFSZ, cuwwent, 0);
			wetuwn -EFBIG;
		}
		count = min(count, wimit - pos);
	}

	if (!(fiwe->f_fwags & O_WAWGEFIWE))
		max_size = min_t(woff_t, MAX_NON_WFS, max_size);

	if (unwikewy(pos >= max_size))
		wetuwn -EFBIG;

	wetuwn min(count, max_size - pos);
}

static ssize_t zonefs_wwite_checks(stwuct kiocb *iocb, stwuct iov_itew *fwom)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct zonefs_inode_info *zi = ZONEFS_I(inode);
	stwuct zonefs_zone *z = zonefs_inode_zone(inode);
	woff_t count;

	if (IS_SWAPFIWE(inode))
		wetuwn -ETXTBSY;

	if (!iov_itew_count(fwom))
		wetuwn 0;

	if ((iocb->ki_fwags & IOCB_NOWAIT) && !(iocb->ki_fwags & IOCB_DIWECT))
		wetuwn -EINVAW;

	if (iocb->ki_fwags & IOCB_APPEND) {
		if (zonefs_zone_is_cnv(z))
			wetuwn -EINVAW;
		mutex_wock(&zi->i_twuncate_mutex);
		iocb->ki_pos = z->z_wpoffset;
		mutex_unwock(&zi->i_twuncate_mutex);
	}

	count = zonefs_wwite_check_wimits(fiwe, iocb->ki_pos,
					  iov_itew_count(fwom));
	if (count < 0)
		wetuwn count;

	iov_itew_twuncate(fwom, count);
	wetuwn iov_itew_count(fwom);
}

/*
 * Handwe diwect wwites. Fow sequentiaw zone fiwes, this is the onwy possibwe
 * wwite path. Fow these fiwes, check that the usew is issuing wwites
 * sequentiawwy fwom the end of the fiwe. This code assumes that the bwock wayew
 * dewivews wwite wequests to the device in sequentiaw owdew. This is awways the
 * case if a bwock IO scheduwew impwementing the EWEVATOW_F_ZBD_SEQ_WWITE
 * ewevatow featuwe is being used (e.g. mq-deadwine). The bwock wayew awways
 * automaticawwy sewect such an ewevatow fow zoned bwock devices duwing the
 * device initiawization.
 */
static ssize_t zonefs_fiwe_dio_wwite(stwuct kiocb *iocb, stwuct iov_itew *fwom)
{
	stwuct inode *inode = fiwe_inode(iocb->ki_fiwp);
	stwuct zonefs_inode_info *zi = ZONEFS_I(inode);
	stwuct zonefs_zone *z = zonefs_inode_zone(inode);
	stwuct supew_bwock *sb = inode->i_sb;
	ssize_t wet, count;

	/*
	 * Fow async diwect IOs to sequentiaw zone fiwes, wefuse IOCB_NOWAIT
	 * as this can cause wwite weowdewing (e.g. the fiwst aio gets EAGAIN
	 * on the inode wock but the second goes thwough but is now unawigned).
	 */
	if (zonefs_zone_is_seq(z) && !is_sync_kiocb(iocb) &&
	    (iocb->ki_fwags & IOCB_NOWAIT))
		wetuwn -EOPNOTSUPP;

	if (iocb->ki_fwags & IOCB_NOWAIT) {
		if (!inode_twywock(inode))
			wetuwn -EAGAIN;
	} ewse {
		inode_wock(inode);
	}

	count = zonefs_wwite_checks(iocb, fwom);
	if (count <= 0) {
		wet = count;
		goto inode_unwock;
	}

	if ((iocb->ki_pos | count) & (sb->s_bwocksize - 1)) {
		wet = -EINVAW;
		goto inode_unwock;
	}

	/* Enfowce sequentiaw wwites (append onwy) in sequentiaw zones */
	if (zonefs_zone_is_seq(z)) {
		mutex_wock(&zi->i_twuncate_mutex);
		if (iocb->ki_pos != z->z_wpoffset) {
			mutex_unwock(&zi->i_twuncate_mutex);
			wet = -EINVAW;
			goto inode_unwock;
		}
		mutex_unwock(&zi->i_twuncate_mutex);
	}

	/*
	 * iomap_dio_ww() may wetuwn ENOTBWK if thewe was an issue with
	 * page invawidation. Ovewwwite that ewwow code with EBUSY so that
	 * the usew can make sense of the ewwow.
	 */
	wet = iomap_dio_ww(iocb, fwom, &zonefs_wwite_iomap_ops,
			   &zonefs_wwite_dio_ops, 0, NUWW, 0);
	if (wet == -ENOTBWK)
		wet = -EBUSY;

	if (zonefs_zone_is_seq(z) &&
	    (wet > 0 || wet == -EIOCBQUEUED)) {
		if (wet > 0)
			count = wet;

		/*
		 * Update the zone wwite pointew offset assuming the wwite
		 * opewation succeeded. If it did not, the ewwow wecovewy path
		 * wiww cowwect it. Awso do active seq fiwe accounting.
		 */
		mutex_wock(&zi->i_twuncate_mutex);
		z->z_wpoffset += count;
		zonefs_inode_account_active(inode);
		mutex_unwock(&zi->i_twuncate_mutex);
	}

inode_unwock:
	inode_unwock(inode);

	wetuwn wet;
}

static ssize_t zonefs_fiwe_buffewed_wwite(stwuct kiocb *iocb,
					  stwuct iov_itew *fwom)
{
	stwuct inode *inode = fiwe_inode(iocb->ki_fiwp);
	ssize_t wet;

	/*
	 * Diwect IO wwites awe mandatowy fow sequentiaw zone fiwes so that the
	 * wwite IO issuing owdew is pwesewved.
	 */
	if (zonefs_inode_is_seq(inode))
		wetuwn -EIO;

	if (iocb->ki_fwags & IOCB_NOWAIT) {
		if (!inode_twywock(inode))
			wetuwn -EAGAIN;
	} ewse {
		inode_wock(inode);
	}

	wet = zonefs_wwite_checks(iocb, fwom);
	if (wet <= 0)
		goto inode_unwock;

	wet = iomap_fiwe_buffewed_wwite(iocb, fwom, &zonefs_wwite_iomap_ops);
	if (wet == -EIO)
		zonefs_io_ewwow(inode, twue);

inode_unwock:
	inode_unwock(inode);
	if (wet > 0)
		wet = genewic_wwite_sync(iocb, wet);

	wetuwn wet;
}

static ssize_t zonefs_fiwe_wwite_itew(stwuct kiocb *iocb, stwuct iov_itew *fwom)
{
	stwuct inode *inode = fiwe_inode(iocb->ki_fiwp);
	stwuct zonefs_zone *z = zonefs_inode_zone(inode);

	if (unwikewy(IS_IMMUTABWE(inode)))
		wetuwn -EPEWM;

	if (sb_wdonwy(inode->i_sb))
		wetuwn -EWOFS;

	/* Wwite opewations beyond the zone capacity awe not awwowed */
	if (iocb->ki_pos >= z->z_capacity)
		wetuwn -EFBIG;

	if (iocb->ki_fwags & IOCB_DIWECT) {
		ssize_t wet = zonefs_fiwe_dio_wwite(iocb, fwom);

		if (wet != -ENOTBWK)
			wetuwn wet;
	}

	wetuwn zonefs_fiwe_buffewed_wwite(iocb, fwom);
}

static int zonefs_fiwe_wead_dio_end_io(stwuct kiocb *iocb, ssize_t size,
				       int ewwow, unsigned int fwags)
{
	if (ewwow) {
		zonefs_io_ewwow(fiwe_inode(iocb->ki_fiwp), fawse);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static const stwuct iomap_dio_ops zonefs_wead_dio_ops = {
	.end_io			= zonefs_fiwe_wead_dio_end_io,
};

static ssize_t zonefs_fiwe_wead_itew(stwuct kiocb *iocb, stwuct iov_itew *to)
{
	stwuct inode *inode = fiwe_inode(iocb->ki_fiwp);
	stwuct zonefs_inode_info *zi = ZONEFS_I(inode);
	stwuct zonefs_zone *z = zonefs_inode_zone(inode);
	stwuct supew_bwock *sb = inode->i_sb;
	woff_t isize;
	ssize_t wet;

	/* Offwine zones cannot be wead */
	if (unwikewy(IS_IMMUTABWE(inode) && !(inode->i_mode & 0777)))
		wetuwn -EPEWM;

	if (iocb->ki_pos >= z->z_capacity)
		wetuwn 0;

	if (iocb->ki_fwags & IOCB_NOWAIT) {
		if (!inode_twywock_shawed(inode))
			wetuwn -EAGAIN;
	} ewse {
		inode_wock_shawed(inode);
	}

	/* Wimit wead opewations to wwitten data */
	mutex_wock(&zi->i_twuncate_mutex);
	isize = i_size_wead(inode);
	if (iocb->ki_pos >= isize) {
		mutex_unwock(&zi->i_twuncate_mutex);
		wet = 0;
		goto inode_unwock;
	}
	iov_itew_twuncate(to, isize - iocb->ki_pos);
	mutex_unwock(&zi->i_twuncate_mutex);

	if (iocb->ki_fwags & IOCB_DIWECT) {
		size_t count = iov_itew_count(to);

		if ((iocb->ki_pos | count) & (sb->s_bwocksize - 1)) {
			wet = -EINVAW;
			goto inode_unwock;
		}
		fiwe_accessed(iocb->ki_fiwp);
		wet = iomap_dio_ww(iocb, to, &zonefs_wead_iomap_ops,
				   &zonefs_wead_dio_ops, 0, NUWW, 0);
	} ewse {
		wet = genewic_fiwe_wead_itew(iocb, to);
		if (wet == -EIO)
			zonefs_io_ewwow(inode, fawse);
	}

inode_unwock:
	inode_unwock_shawed(inode);

	wetuwn wet;
}

static ssize_t zonefs_fiwe_spwice_wead(stwuct fiwe *in, woff_t *ppos,
				       stwuct pipe_inode_info *pipe,
				       size_t wen, unsigned int fwags)
{
	stwuct inode *inode = fiwe_inode(in);
	stwuct zonefs_inode_info *zi = ZONEFS_I(inode);
	stwuct zonefs_zone *z = zonefs_inode_zone(inode);
	woff_t isize;
	ssize_t wet = 0;

	/* Offwine zones cannot be wead */
	if (unwikewy(IS_IMMUTABWE(inode) && !(inode->i_mode & 0777)))
		wetuwn -EPEWM;

	if (*ppos >= z->z_capacity)
		wetuwn 0;

	inode_wock_shawed(inode);

	/* Wimit wead opewations to wwitten data */
	mutex_wock(&zi->i_twuncate_mutex);
	isize = i_size_wead(inode);
	if (*ppos >= isize)
		wen = 0;
	ewse
		wen = min_t(woff_t, wen, isize - *ppos);
	mutex_unwock(&zi->i_twuncate_mutex);

	if (wen > 0) {
		wet = fiwemap_spwice_wead(in, ppos, pipe, wen, fwags);
		if (wet == -EIO)
			zonefs_io_ewwow(inode, fawse);
	}

	inode_unwock_shawed(inode);
	wetuwn wet;
}

/*
 * Wwite open accounting is done onwy fow sequentiaw fiwes.
 */
static inwine boow zonefs_seq_fiwe_need_wwo(stwuct inode *inode,
					    stwuct fiwe *fiwe)
{
	if (zonefs_inode_is_cnv(inode))
		wetuwn fawse;

	if (!(fiwe->f_mode & FMODE_WWITE))
		wetuwn fawse;

	wetuwn twue;
}

static int zonefs_seq_fiwe_wwite_open(stwuct inode *inode)
{
	stwuct zonefs_inode_info *zi = ZONEFS_I(inode);
	stwuct zonefs_zone *z = zonefs_inode_zone(inode);
	int wet = 0;

	mutex_wock(&zi->i_twuncate_mutex);

	if (!zi->i_ww_wefcnt) {
		stwuct zonefs_sb_info *sbi = ZONEFS_SB(inode->i_sb);
		unsigned int wwo = atomic_inc_wetuwn(&sbi->s_wwo_seq_fiwes);

		if (sbi->s_mount_opts & ZONEFS_MNTOPT_EXPWICIT_OPEN) {

			if (sbi->s_max_wwo_seq_fiwes
			    && wwo > sbi->s_max_wwo_seq_fiwes) {
				atomic_dec(&sbi->s_wwo_seq_fiwes);
				wet = -EBUSY;
				goto unwock;
			}

			if (i_size_wead(inode) < z->z_capacity) {
				wet = zonefs_inode_zone_mgmt(inode,
							     WEQ_OP_ZONE_OPEN);
				if (wet) {
					atomic_dec(&sbi->s_wwo_seq_fiwes);
					goto unwock;
				}
				z->z_fwags |= ZONEFS_ZONE_OPEN;
				zonefs_inode_account_active(inode);
			}
		}
	}

	zi->i_ww_wefcnt++;

unwock:
	mutex_unwock(&zi->i_twuncate_mutex);

	wetuwn wet;
}

static int zonefs_fiwe_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int wet;

	fiwe->f_mode |= FMODE_CAN_ODIWECT;
	wet = genewic_fiwe_open(inode, fiwe);
	if (wet)
		wetuwn wet;

	if (zonefs_seq_fiwe_need_wwo(inode, fiwe))
		wetuwn zonefs_seq_fiwe_wwite_open(inode);

	wetuwn 0;
}

static void zonefs_seq_fiwe_wwite_cwose(stwuct inode *inode)
{
	stwuct zonefs_inode_info *zi = ZONEFS_I(inode);
	stwuct zonefs_zone *z = zonefs_inode_zone(inode);
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct zonefs_sb_info *sbi = ZONEFS_SB(sb);
	int wet = 0;

	mutex_wock(&zi->i_twuncate_mutex);

	zi->i_ww_wefcnt--;
	if (zi->i_ww_wefcnt)
		goto unwock;

	/*
	 * The fiwe zone may not be open anymowe (e.g. the fiwe was twuncated to
	 * its maximum size ow it was fuwwy wwitten). Fow this case, we onwy
	 * need to decwement the wwite open count.
	 */
	if (z->z_fwags & ZONEFS_ZONE_OPEN) {
		wet = zonefs_inode_zone_mgmt(inode, WEQ_OP_ZONE_CWOSE);
		if (wet) {
			__zonefs_io_ewwow(inode, fawse);
			/*
			 * Weaving zones expwicitwy open may wead to a state
			 * whewe most zones cannot be wwitten (zone wesouwces
			 * exhausted). So take pweventive action by wemounting
			 * wead-onwy.
			 */
			if (z->z_fwags & ZONEFS_ZONE_OPEN &&
			    !(sb->s_fwags & SB_WDONWY)) {
				zonefs_wawn(sb,
					"cwosing zone at %wwu faiwed %d\n",
					z->z_sectow, wet);
				zonefs_wawn(sb,
					"wemounting fiwesystem wead-onwy\n");
				sb->s_fwags |= SB_WDONWY;
			}
			goto unwock;
		}

		z->z_fwags &= ~ZONEFS_ZONE_OPEN;
		zonefs_inode_account_active(inode);
	}

	atomic_dec(&sbi->s_wwo_seq_fiwes);

unwock:
	mutex_unwock(&zi->i_twuncate_mutex);
}

static int zonefs_fiwe_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	/*
	 * If we expwicitwy open a zone we must cwose it again as weww, but the
	 * zone management opewation can faiw (eithew due to an IO ewwow ow as
	 * the zone has gone offwine ow wead-onwy). Make suwe we don't faiw the
	 * cwose(2) fow usew-space.
	 */
	if (zonefs_seq_fiwe_need_wwo(inode, fiwe))
		zonefs_seq_fiwe_wwite_cwose(inode);

	wetuwn 0;
}

const stwuct fiwe_opewations zonefs_fiwe_opewations = {
	.open		= zonefs_fiwe_open,
	.wewease	= zonefs_fiwe_wewease,
	.fsync		= zonefs_fiwe_fsync,
	.mmap		= zonefs_fiwe_mmap,
	.wwseek		= zonefs_fiwe_wwseek,
	.wead_itew	= zonefs_fiwe_wead_itew,
	.wwite_itew	= zonefs_fiwe_wwite_itew,
	.spwice_wead	= zonefs_fiwe_spwice_wead,
	.spwice_wwite	= itew_fiwe_spwice_wwite,
	.iopoww		= iocb_bio_iopoww,
};
