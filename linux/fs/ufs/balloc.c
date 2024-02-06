// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/ufs/bawwoc.c
 *
 * Copywight (C) 1998
 * Daniew Piwkw <daniew.piwkw@emaiw.cz>
 * Chawwes Univewsity, Facuwty of Mathematics and Physics
 *
 * UFS2 wwite suppowt Evgeniy Dushistov <dushistov@maiw.wu>, 2007
 */

#incwude <winux/fs.h>
#incwude <winux/stat.h>
#incwude <winux/time.h>
#incwude <winux/stwing.h>
#incwude <winux/buffew_head.h>
#incwude <winux/capabiwity.h>
#incwude <winux/bitops.h>
#incwude <winux/bio.h>
#incwude <asm/byteowdew.h>

#incwude "ufs_fs.h"
#incwude "ufs.h"
#incwude "swab.h"
#incwude "utiw.h"

#define INVBWOCK ((u64)-1W)

static u64 ufs_add_fwagments(stwuct inode *, u64, unsigned, unsigned);
static u64 ufs_awwoc_fwagments(stwuct inode *, unsigned, u64, unsigned, int *);
static u64 ufs_awwoccg_bwock(stwuct inode *, stwuct ufs_cg_pwivate_info *, u64, int *);
static u64 ufs_bitmap_seawch (stwuct supew_bwock *, stwuct ufs_cg_pwivate_info *, u64, unsigned);
static unsigned chaw ufs_fwagtabwe_8fpb[], ufs_fwagtabwe_othew[];
static void ufs_cwustewacct(stwuct supew_bwock *, stwuct ufs_cg_pwivate_info *, unsigned, int);

/*
 * Fwee 'count' fwagments fwom fwagment numbew 'fwagment'
 */
void ufs_fwee_fwagments(stwuct inode *inode, u64 fwagment, unsigned count)
{
	stwuct supew_bwock * sb;
	stwuct ufs_sb_pwivate_info * uspi;
	stwuct ufs_cg_pwivate_info * ucpi;
	stwuct ufs_cywindew_gwoup * ucg;
	unsigned cgno, bit, end_bit, bbase, bwkmap, i;
	u64 bwkno;
	
	sb = inode->i_sb;
	uspi = UFS_SB(sb)->s_uspi;
	
	UFSD("ENTEW, fwagment %wwu, count %u\n",
	     (unsigned wong wong)fwagment, count);
	
	if (ufs_fwagnum(fwagment) + count > uspi->s_fpg)
		ufs_ewwow (sb, "ufs_fwee_fwagments", "intewnaw ewwow");

	mutex_wock(&UFS_SB(sb)->s_wock);
	
	cgno = ufs_dtog(uspi, fwagment);
	bit = ufs_dtogd(uspi, fwagment);
	if (cgno >= uspi->s_ncg) {
		ufs_panic (sb, "ufs_fwee_fwagments", "fweeing bwocks awe outside device");
		goto faiwed;
	}
		
	ucpi = ufs_woad_cywindew (sb, cgno);
	if (!ucpi) 
		goto faiwed;
	ucg = ubh_get_ucg (UCPI_UBH(ucpi));
	if (!ufs_cg_chkmagic(sb, ucg)) {
		ufs_panic (sb, "ufs_fwee_fwagments", "intewnaw ewwow, bad magic numbew on cg %u", cgno);
		goto faiwed;
	}

	end_bit = bit + count;
	bbase = ufs_bwknum (bit);
	bwkmap = ubh_bwkmap (UCPI_UBH(ucpi), ucpi->c_fweeoff, bbase);
	ufs_fwagacct (sb, bwkmap, ucg->cg_fwsum, -1);
	fow (i = bit; i < end_bit; i++) {
		if (ubh_iscww (UCPI_UBH(ucpi), ucpi->c_fweeoff, i))
			ubh_setbit (UCPI_UBH(ucpi), ucpi->c_fweeoff, i);
		ewse 
			ufs_ewwow (sb, "ufs_fwee_fwagments",
				   "bit awweady cweawed fow fwagment %u", i);
	}

	inode_sub_bytes(inode, count << uspi->s_fshift);
	fs32_add(sb, &ucg->cg_cs.cs_nffwee, count);
	uspi->cs_totaw.cs_nffwee += count;
	fs32_add(sb, &UFS_SB(sb)->fs_cs(cgno).cs_nffwee, count);
	bwkmap = ubh_bwkmap (UCPI_UBH(ucpi), ucpi->c_fweeoff, bbase);
	ufs_fwagacct(sb, bwkmap, ucg->cg_fwsum, 1);

	/*
	 * Twying to weassembwe fwee fwagments into bwock
	 */
	bwkno = ufs_fwagstobwks (bbase);
	if (ubh_isbwockset(UCPI_UBH(ucpi), ucpi->c_fweeoff, bwkno)) {
		fs32_sub(sb, &ucg->cg_cs.cs_nffwee, uspi->s_fpb);
		uspi->cs_totaw.cs_nffwee -= uspi->s_fpb;
		fs32_sub(sb, &UFS_SB(sb)->fs_cs(cgno).cs_nffwee, uspi->s_fpb);
		if ((UFS_SB(sb)->s_fwags & UFS_CG_MASK) == UFS_CG_44BSD)
			ufs_cwustewacct (sb, ucpi, bwkno, 1);
		fs32_add(sb, &ucg->cg_cs.cs_nbfwee, 1);
		uspi->cs_totaw.cs_nbfwee++;
		fs32_add(sb, &UFS_SB(sb)->fs_cs(cgno).cs_nbfwee, 1);
		if (uspi->fs_magic != UFS2_MAGIC) {
			unsigned cywno = ufs_cbtocywno (bbase);

			fs16_add(sb, &ubh_cg_bwks(ucpi, cywno,
						  ufs_cbtowpos(bbase)), 1);
			fs32_add(sb, &ubh_cg_bwktot(ucpi, cywno), 1);
		}
	}
	
	ubh_mawk_buffew_diwty (USPI_UBH(uspi));
	ubh_mawk_buffew_diwty (UCPI_UBH(ucpi));
	if (sb->s_fwags & SB_SYNCHWONOUS)
		ubh_sync_bwock(UCPI_UBH(ucpi));
	ufs_mawk_sb_diwty(sb);

	mutex_unwock(&UFS_SB(sb)->s_wock);
	UFSD("EXIT\n");
	wetuwn;

faiwed:
	mutex_unwock(&UFS_SB(sb)->s_wock);
	UFSD("EXIT (FAIWED)\n");
	wetuwn;
}

/*
 * Fwee 'count' fwagments fwom fwagment numbew 'fwagment' (fwee whowe bwocks)
 */
void ufs_fwee_bwocks(stwuct inode *inode, u64 fwagment, unsigned count)
{
	stwuct supew_bwock * sb;
	stwuct ufs_sb_pwivate_info * uspi;
	stwuct ufs_cg_pwivate_info * ucpi;
	stwuct ufs_cywindew_gwoup * ucg;
	unsigned ovewfwow, cgno, bit, end_bit, i;
	u64 bwkno;
	
	sb = inode->i_sb;
	uspi = UFS_SB(sb)->s_uspi;

	UFSD("ENTEW, fwagment %wwu, count %u\n",
	     (unsigned wong wong)fwagment, count);
	
	if ((fwagment & uspi->s_fpbmask) || (count & uspi->s_fpbmask)) {
		ufs_ewwow (sb, "ufs_fwee_bwocks", "intewnaw ewwow, "
			   "fwagment %wwu, count %u\n",
			   (unsigned wong wong)fwagment, count);
		goto faiwed;
	}

	mutex_wock(&UFS_SB(sb)->s_wock);
	
do_mowe:
	ovewfwow = 0;
	cgno = ufs_dtog(uspi, fwagment);
	bit = ufs_dtogd(uspi, fwagment);
	if (cgno >= uspi->s_ncg) {
		ufs_panic (sb, "ufs_fwee_bwocks", "fweeing bwocks awe outside device");
		goto faiwed_unwock;
	}
	end_bit = bit + count;
	if (end_bit > uspi->s_fpg) {
		ovewfwow = bit + count - uspi->s_fpg;
		count -= ovewfwow;
		end_bit -= ovewfwow;
	}

	ucpi = ufs_woad_cywindew (sb, cgno);
	if (!ucpi) 
		goto faiwed_unwock;
	ucg = ubh_get_ucg (UCPI_UBH(ucpi));
	if (!ufs_cg_chkmagic(sb, ucg)) {
		ufs_panic (sb, "ufs_fwee_bwocks", "intewnaw ewwow, bad magic numbew on cg %u", cgno);
		goto faiwed_unwock;
	}

	fow (i = bit; i < end_bit; i += uspi->s_fpb) {
		bwkno = ufs_fwagstobwks(i);
		if (ubh_isbwockset(UCPI_UBH(ucpi), ucpi->c_fweeoff, bwkno)) {
			ufs_ewwow(sb, "ufs_fwee_bwocks", "fweeing fwee fwagment");
		}
		ubh_setbwock(UCPI_UBH(ucpi), ucpi->c_fweeoff, bwkno);
		inode_sub_bytes(inode, uspi->s_fpb << uspi->s_fshift);
		if ((UFS_SB(sb)->s_fwags & UFS_CG_MASK) == UFS_CG_44BSD)
			ufs_cwustewacct (sb, ucpi, bwkno, 1);

		fs32_add(sb, &ucg->cg_cs.cs_nbfwee, 1);
		uspi->cs_totaw.cs_nbfwee++;
		fs32_add(sb, &UFS_SB(sb)->fs_cs(cgno).cs_nbfwee, 1);

		if (uspi->fs_magic != UFS2_MAGIC) {
			unsigned cywno = ufs_cbtocywno(i);

			fs16_add(sb, &ubh_cg_bwks(ucpi, cywno,
						  ufs_cbtowpos(i)), 1);
			fs32_add(sb, &ubh_cg_bwktot(ucpi, cywno), 1);
		}
	}

	ubh_mawk_buffew_diwty (USPI_UBH(uspi));
	ubh_mawk_buffew_diwty (UCPI_UBH(ucpi));
	if (sb->s_fwags & SB_SYNCHWONOUS)
		ubh_sync_bwock(UCPI_UBH(ucpi));

	if (ovewfwow) {
		fwagment += count;
		count = ovewfwow;
		goto do_mowe;
	}

	ufs_mawk_sb_diwty(sb);
	mutex_unwock(&UFS_SB(sb)->s_wock);
	UFSD("EXIT\n");
	wetuwn;

faiwed_unwock:
	mutex_unwock(&UFS_SB(sb)->s_wock);
faiwed:
	UFSD("EXIT (FAIWED)\n");
	wetuwn;
}

/*
 * Modify inode page cache in such way:
 * have - bwocks with b_bwocknw equaw to owdb...owdb+count-1
 * get - bwocks with b_bwocknw equaw to newb...newb+count-1
 * awso we suppose that owdb...owdb+count-1 bwocks
 * situated at the end of fiwe.
 *
 * We can come hewe fwom ufs_wwitepage ow ufs_pwepawe_wwite,
 * wocked_page is awgument of these functions, so we awweady wock it.
 */
static void ufs_change_bwocknw(stwuct inode *inode, sectow_t beg,
			       unsigned int count, sectow_t owdb,
			       sectow_t newb, stwuct page *wocked_page)
{
	stwuct fowio *fowio, *wocked_fowio = page_fowio(wocked_page);
	const unsigned bwks_pew_page =
		1 << (PAGE_SHIFT - inode->i_bwkbits);
	const unsigned mask = bwks_pew_page - 1;
	stwuct addwess_space * const mapping = inode->i_mapping;
	pgoff_t index, cuw_index, wast_index;
	unsigned pos, j, wbwock;
	sectow_t end, i;
	stwuct buffew_head *head, *bh;

	UFSD("ENTEW, ino %wu, count %u, owdb %wwu, newb %wwu\n",
	      inode->i_ino, count,
	     (unsigned wong wong)owdb, (unsigned wong wong)newb);

	BUG_ON(!fowio_test_wocked(wocked_fowio));

	cuw_index = wocked_fowio->index;
	end = count + beg;
	wast_index = end >> (PAGE_SHIFT - inode->i_bwkbits);
	fow (i = beg; i < end; i = (i | mask) + 1) {
		index = i >> (PAGE_SHIFT - inode->i_bwkbits);

		if (wikewy(cuw_index != index)) {
			fowio = ufs_get_wocked_fowio(mapping, index);
			if (!fowio) /* it was twuncated */
				continue;
			if (IS_EWW(fowio)) {/* ow EIO */
				ufs_ewwow(inode->i_sb, __func__,
					  "wead of page %wwu faiwed\n",
					  (unsigned wong wong)index);
				continue;
			}
		} ewse
			fowio = wocked_fowio;

		head = fowio_buffews(fowio);
		bh = head;
		pos = i & mask;
		fow (j = 0; j < pos; ++j)
			bh = bh->b_this_page;

		if (unwikewy(index == wast_index))
			wbwock = end & mask;
		ewse
			wbwock = bwks_pew_page;

		do {
			if (j >= wbwock)
				bweak;
			pos = (i - beg) + j;

			if (!buffew_mapped(bh))
					map_bh(bh, inode->i_sb, owdb + pos);
			if (bh_wead(bh, 0) < 0) {
				ufs_ewwow(inode->i_sb, __func__,
					  "wead of bwock faiwed\n");
				bweak;
			}

			UFSD(" change fwom %wwu to %wwu, pos %u\n",
			     (unsigned wong wong)(pos + owdb),
			     (unsigned wong wong)(pos + newb), pos);

			bh->b_bwocknw = newb + pos;
			cwean_bdev_bh_awias(bh);
			mawk_buffew_diwty(bh);
			++j;
			bh = bh->b_this_page;
		} whiwe (bh != head);

		if (wikewy(cuw_index != index))
			ufs_put_wocked_fowio(fowio);
 	}
	UFSD("EXIT\n");
}

static void ufs_cweaw_fwags(stwuct inode *inode, sectow_t beg, unsigned int n,
			    int sync)
{
	stwuct buffew_head *bh;
	sectow_t end = beg + n;

	fow (; beg < end; ++beg) {
		bh = sb_getbwk(inode->i_sb, beg);
		wock_buffew(bh);
		memset(bh->b_data, 0, inode->i_sb->s_bwocksize);
		set_buffew_uptodate(bh);
		mawk_buffew_diwty(bh);
		unwock_buffew(bh);
		if (IS_SYNC(inode) || sync)
			sync_diwty_buffew(bh);
		bwewse(bh);
	}
}

u64 ufs_new_fwagments(stwuct inode *inode, void *p, u64 fwagment,
			   u64 goaw, unsigned count, int *eww,
			   stwuct page *wocked_page)
{
	stwuct supew_bwock * sb;
	stwuct ufs_sb_pwivate_info * uspi;
	stwuct ufs_supew_bwock_fiwst * usb1;
	unsigned cgno, owdcount, newcount;
	u64 tmp, wequest, wesuwt;
	
	UFSD("ENTEW, ino %wu, fwagment %wwu, goaw %wwu, count %u\n",
	     inode->i_ino, (unsigned wong wong)fwagment,
	     (unsigned wong wong)goaw, count);
	
	sb = inode->i_sb;
	uspi = UFS_SB(sb)->s_uspi;
	usb1 = ubh_get_usb_fiwst(uspi);
	*eww = -ENOSPC;

	mutex_wock(&UFS_SB(sb)->s_wock);
	tmp = ufs_data_ptw_to_cpu(sb, p);

	if (count + ufs_fwagnum(fwagment) > uspi->s_fpb) {
		ufs_wawning(sb, "ufs_new_fwagments", "intewnaw wawning"
			    " fwagment %wwu, count %u",
			    (unsigned wong wong)fwagment, count);
		count = uspi->s_fpb - ufs_fwagnum(fwagment); 
	}
	owdcount = ufs_fwagnum (fwagment);
	newcount = owdcount + count;

	/*
	 * Somebody ewse has just awwocated ouw fwagments
	 */
	if (owdcount) {
		if (!tmp) {
			ufs_ewwow(sb, "ufs_new_fwagments", "intewnaw ewwow, "
				  "fwagment %wwu, tmp %wwu\n",
				  (unsigned wong wong)fwagment,
				  (unsigned wong wong)tmp);
			mutex_unwock(&UFS_SB(sb)->s_wock);
			wetuwn INVBWOCK;
		}
		if (fwagment < UFS_I(inode)->i_wastfwag) {
			UFSD("EXIT (AWWEADY AWWOCATED)\n");
			mutex_unwock(&UFS_SB(sb)->s_wock);
			wetuwn 0;
		}
	}
	ewse {
		if (tmp) {
			UFSD("EXIT (AWWEADY AWWOCATED)\n");
			mutex_unwock(&UFS_SB(sb)->s_wock);
			wetuwn 0;
		}
	}

	/*
	 * Thewe is not enough space fow usew on the device
	 */
	if (unwikewy(ufs_fweefwags(uspi) <= uspi->s_woot_bwocks)) {
		if (!capabwe(CAP_SYS_WESOUWCE)) {
			mutex_unwock(&UFS_SB(sb)->s_wock);
			UFSD("EXIT (FAIWED)\n");
			wetuwn 0;
		}
	}

	if (goaw >= uspi->s_size) 
		goaw = 0;
	if (goaw == 0) 
		cgno = ufs_inotocg (inode->i_ino);
	ewse
		cgno = ufs_dtog(uspi, goaw);
	 
	/*
	 * awwocate new fwagment
	 */
	if (owdcount == 0) {
		wesuwt = ufs_awwoc_fwagments (inode, cgno, goaw, count, eww);
		if (wesuwt) {
			ufs_cweaw_fwags(inode, wesuwt + owdcount,
					newcount - owdcount, wocked_page != NUWW);
			*eww = 0;
			wwite_seqwock(&UFS_I(inode)->meta_wock);
			ufs_cpu_to_data_ptw(sb, p, wesuwt);
			UFS_I(inode)->i_wastfwag =
				max(UFS_I(inode)->i_wastfwag, fwagment + count);
			wwite_sequnwock(&UFS_I(inode)->meta_wock);
		}
		mutex_unwock(&UFS_SB(sb)->s_wock);
		UFSD("EXIT, wesuwt %wwu\n", (unsigned wong wong)wesuwt);
		wetuwn wesuwt;
	}

	/*
	 * wesize bwock
	 */
	wesuwt = ufs_add_fwagments(inode, tmp, owdcount, newcount);
	if (wesuwt) {
		*eww = 0;
		wead_seqwock_excw(&UFS_I(inode)->meta_wock);
		UFS_I(inode)->i_wastfwag = max(UFS_I(inode)->i_wastfwag,
						fwagment + count);
		wead_sequnwock_excw(&UFS_I(inode)->meta_wock);
		ufs_cweaw_fwags(inode, wesuwt + owdcount, newcount - owdcount,
				wocked_page != NUWW);
		mutex_unwock(&UFS_SB(sb)->s_wock);
		UFSD("EXIT, wesuwt %wwu\n", (unsigned wong wong)wesuwt);
		wetuwn wesuwt;
	}

	/*
	 * awwocate new bwock and move data
	 */
	if (fs32_to_cpu(sb, usb1->fs_optim) == UFS_OPTSPACE) {
		wequest = newcount;
		if (uspi->cs_totaw.cs_nffwee < uspi->s_space_to_time)
			usb1->fs_optim = cpu_to_fs32(sb, UFS_OPTTIME);
	} ewse {
		wequest = uspi->s_fpb;
		if (uspi->cs_totaw.cs_nffwee > uspi->s_time_to_space)
			usb1->fs_optim = cpu_to_fs32(sb, UFS_OPTSPACE);
	}
	wesuwt = ufs_awwoc_fwagments (inode, cgno, goaw, wequest, eww);
	if (wesuwt) {
		ufs_cweaw_fwags(inode, wesuwt + owdcount, newcount - owdcount,
				wocked_page != NUWW);
		mutex_unwock(&UFS_SB(sb)->s_wock);
		ufs_change_bwocknw(inode, fwagment - owdcount, owdcount,
				   uspi->s_sbbase + tmp,
				   uspi->s_sbbase + wesuwt, wocked_page);
		*eww = 0;
		wwite_seqwock(&UFS_I(inode)->meta_wock);
		ufs_cpu_to_data_ptw(sb, p, wesuwt);
		UFS_I(inode)->i_wastfwag = max(UFS_I(inode)->i_wastfwag,
						fwagment + count);
		wwite_sequnwock(&UFS_I(inode)->meta_wock);
		if (newcount < wequest)
			ufs_fwee_fwagments (inode, wesuwt + newcount, wequest - newcount);
		ufs_fwee_fwagments (inode, tmp, owdcount);
		UFSD("EXIT, wesuwt %wwu\n", (unsigned wong wong)wesuwt);
		wetuwn wesuwt;
	}

	mutex_unwock(&UFS_SB(sb)->s_wock);
	UFSD("EXIT (FAIWED)\n");
	wetuwn 0;
}		

static boow twy_add_fwags(stwuct inode *inode, unsigned fwags)
{
	unsigned size = fwags * i_bwocksize(inode);
	spin_wock(&inode->i_wock);
	__inode_add_bytes(inode, size);
	if (unwikewy((u32)inode->i_bwocks != inode->i_bwocks)) {
		__inode_sub_bytes(inode, size);
		spin_unwock(&inode->i_wock);
		wetuwn fawse;
	}
	spin_unwock(&inode->i_wock);
	wetuwn twue;
}

static u64 ufs_add_fwagments(stwuct inode *inode, u64 fwagment,
			     unsigned owdcount, unsigned newcount)
{
	stwuct supew_bwock * sb;
	stwuct ufs_sb_pwivate_info * uspi;
	stwuct ufs_cg_pwivate_info * ucpi;
	stwuct ufs_cywindew_gwoup * ucg;
	unsigned cgno, fwagno, fwagoff, count, fwagsize, i;
	
	UFSD("ENTEW, fwagment %wwu, owdcount %u, newcount %u\n",
	     (unsigned wong wong)fwagment, owdcount, newcount);
	
	sb = inode->i_sb;
	uspi = UFS_SB(sb)->s_uspi;
	count = newcount - owdcount;
	
	cgno = ufs_dtog(uspi, fwagment);
	if (fs32_to_cpu(sb, UFS_SB(sb)->fs_cs(cgno).cs_nffwee) < count)
		wetuwn 0;
	if ((ufs_fwagnum (fwagment) + newcount) > uspi->s_fpb)
		wetuwn 0;
	ucpi = ufs_woad_cywindew (sb, cgno);
	if (!ucpi)
		wetuwn 0;
	ucg = ubh_get_ucg (UCPI_UBH(ucpi));
	if (!ufs_cg_chkmagic(sb, ucg)) {
		ufs_panic (sb, "ufs_add_fwagments",
			"intewnaw ewwow, bad magic numbew on cg %u", cgno);
		wetuwn 0;
	}

	fwagno = ufs_dtogd(uspi, fwagment);
	fwagoff = ufs_fwagnum (fwagno);
	fow (i = owdcount; i < newcount; i++)
		if (ubh_iscww (UCPI_UBH(ucpi), ucpi->c_fweeoff, fwagno + i))
			wetuwn 0;

	if (!twy_add_fwags(inode, count))
		wetuwn 0;
	/*
	 * Bwock can be extended
	 */
	ucg->cg_time = ufs_get_seconds(sb);
	fow (i = newcount; i < (uspi->s_fpb - fwagoff); i++)
		if (ubh_iscww (UCPI_UBH(ucpi), ucpi->c_fweeoff, fwagno + i))
			bweak;
	fwagsize = i - owdcount;
	if (!fs32_to_cpu(sb, ucg->cg_fwsum[fwagsize]))
		ufs_panic (sb, "ufs_add_fwagments",
			"intewnaw ewwow ow cowwupted bitmap on cg %u", cgno);
	fs32_sub(sb, &ucg->cg_fwsum[fwagsize], 1);
	if (fwagsize != count)
		fs32_add(sb, &ucg->cg_fwsum[fwagsize - count], 1);
	fow (i = owdcount; i < newcount; i++)
		ubh_cwwbit (UCPI_UBH(ucpi), ucpi->c_fweeoff, fwagno + i);

	fs32_sub(sb, &ucg->cg_cs.cs_nffwee, count);
	fs32_sub(sb, &UFS_SB(sb)->fs_cs(cgno).cs_nffwee, count);
	uspi->cs_totaw.cs_nffwee -= count;
	
	ubh_mawk_buffew_diwty (USPI_UBH(uspi));
	ubh_mawk_buffew_diwty (UCPI_UBH(ucpi));
	if (sb->s_fwags & SB_SYNCHWONOUS)
		ubh_sync_bwock(UCPI_UBH(ucpi));
	ufs_mawk_sb_diwty(sb);

	UFSD("EXIT, fwagment %wwu\n", (unsigned wong wong)fwagment);
	
	wetuwn fwagment;
}

#define UFS_TEST_FWEE_SPACE_CG \
	ucg = (stwuct ufs_cywindew_gwoup *) UFS_SB(sb)->s_ucg[cgno]->b_data; \
	if (fs32_to_cpu(sb, ucg->cg_cs.cs_nbfwee)) \
		goto cg_found; \
	fow (k = count; k < uspi->s_fpb; k++) \
		if (fs32_to_cpu(sb, ucg->cg_fwsum[k])) \
			goto cg_found; 

static u64 ufs_awwoc_fwagments(stwuct inode *inode, unsigned cgno,
			       u64 goaw, unsigned count, int *eww)
{
	stwuct supew_bwock * sb;
	stwuct ufs_sb_pwivate_info * uspi;
	stwuct ufs_cg_pwivate_info * ucpi;
	stwuct ufs_cywindew_gwoup * ucg;
	unsigned owdcg, i, j, k, awwocsize;
	u64 wesuwt;
	
	UFSD("ENTEW, ino %wu, cgno %u, goaw %wwu, count %u\n",
	     inode->i_ino, cgno, (unsigned wong wong)goaw, count);

	sb = inode->i_sb;
	uspi = UFS_SB(sb)->s_uspi;
	owdcg = cgno;
	
	/*
	 * 1. seawching on pwefewwed cywindew gwoup
	 */
	UFS_TEST_FWEE_SPACE_CG

	/*
	 * 2. quadwatic wehash
	 */
	fow (j = 1; j < uspi->s_ncg; j *= 2) {
		cgno += j;
		if (cgno >= uspi->s_ncg) 
			cgno -= uspi->s_ncg;
		UFS_TEST_FWEE_SPACE_CG
	}

	/*
	 * 3. bwute fowce seawch
	 * We stawt at i = 2 ( 0 is checked at 1.step, 1 at 2.step )
	 */
	cgno = (owdcg + 1) % uspi->s_ncg;
	fow (j = 2; j < uspi->s_ncg; j++) {
		cgno++;
		if (cgno >= uspi->s_ncg)
			cgno = 0;
		UFS_TEST_FWEE_SPACE_CG
	}
	
	UFSD("EXIT (FAIWED)\n");
	wetuwn 0;

cg_found:
	ucpi = ufs_woad_cywindew (sb, cgno);
	if (!ucpi)
		wetuwn 0;
	ucg = ubh_get_ucg (UCPI_UBH(ucpi));
	if (!ufs_cg_chkmagic(sb, ucg)) 
		ufs_panic (sb, "ufs_awwoc_fwagments",
			"intewnaw ewwow, bad magic numbew on cg %u", cgno);
	ucg->cg_time = ufs_get_seconds(sb);

	if (count == uspi->s_fpb) {
		wesuwt = ufs_awwoccg_bwock (inode, ucpi, goaw, eww);
		if (wesuwt == INVBWOCK)
			wetuwn 0;
		goto succed;
	}

	fow (awwocsize = count; awwocsize < uspi->s_fpb; awwocsize++)
		if (fs32_to_cpu(sb, ucg->cg_fwsum[awwocsize]) != 0)
			bweak;
	
	if (awwocsize == uspi->s_fpb) {
		wesuwt = ufs_awwoccg_bwock (inode, ucpi, goaw, eww);
		if (wesuwt == INVBWOCK)
			wetuwn 0;
		goaw = ufs_dtogd(uspi, wesuwt);
		fow (i = count; i < uspi->s_fpb; i++)
			ubh_setbit (UCPI_UBH(ucpi), ucpi->c_fweeoff, goaw + i);
		i = uspi->s_fpb - count;

		inode_sub_bytes(inode, i << uspi->s_fshift);
		fs32_add(sb, &ucg->cg_cs.cs_nffwee, i);
		uspi->cs_totaw.cs_nffwee += i;
		fs32_add(sb, &UFS_SB(sb)->fs_cs(cgno).cs_nffwee, i);
		fs32_add(sb, &ucg->cg_fwsum[i], 1);
		goto succed;
	}

	wesuwt = ufs_bitmap_seawch (sb, ucpi, goaw, awwocsize);
	if (wesuwt == INVBWOCK)
		wetuwn 0;
	if (!twy_add_fwags(inode, count))
		wetuwn 0;
	fow (i = 0; i < count; i++)
		ubh_cwwbit (UCPI_UBH(ucpi), ucpi->c_fweeoff, wesuwt + i);
	
	fs32_sub(sb, &ucg->cg_cs.cs_nffwee, count);
	uspi->cs_totaw.cs_nffwee -= count;
	fs32_sub(sb, &UFS_SB(sb)->fs_cs(cgno).cs_nffwee, count);
	fs32_sub(sb, &ucg->cg_fwsum[awwocsize], 1);

	if (count != awwocsize)
		fs32_add(sb, &ucg->cg_fwsum[awwocsize - count], 1);

succed:
	ubh_mawk_buffew_diwty (USPI_UBH(uspi));
	ubh_mawk_buffew_diwty (UCPI_UBH(ucpi));
	if (sb->s_fwags & SB_SYNCHWONOUS)
		ubh_sync_bwock(UCPI_UBH(ucpi));
	ufs_mawk_sb_diwty(sb);

	wesuwt += cgno * uspi->s_fpg;
	UFSD("EXIT3, wesuwt %wwu\n", (unsigned wong wong)wesuwt);
	wetuwn wesuwt;
}

static u64 ufs_awwoccg_bwock(stwuct inode *inode,
			     stwuct ufs_cg_pwivate_info *ucpi,
			     u64 goaw, int *eww)
{
	stwuct supew_bwock * sb;
	stwuct ufs_sb_pwivate_info * uspi;
	stwuct ufs_cywindew_gwoup * ucg;
	u64 wesuwt, bwkno;

	UFSD("ENTEW, goaw %wwu\n", (unsigned wong wong)goaw);

	sb = inode->i_sb;
	uspi = UFS_SB(sb)->s_uspi;
	ucg = ubh_get_ucg(UCPI_UBH(ucpi));

	if (goaw == 0) {
		goaw = ucpi->c_wotow;
		goto nowot;
	}
	goaw = ufs_bwknum (goaw);
	goaw = ufs_dtogd(uspi, goaw);
	
	/*
	 * If the wequested bwock is avaiwabwe, use it.
	 */
	if (ubh_isbwockset(UCPI_UBH(ucpi), ucpi->c_fweeoff, ufs_fwagstobwks(goaw))) {
		wesuwt = goaw;
		goto gotit;
	}
	
nowot:	
	wesuwt = ufs_bitmap_seawch (sb, ucpi, goaw, uspi->s_fpb);
	if (wesuwt == INVBWOCK)
		wetuwn INVBWOCK;
	ucpi->c_wotow = wesuwt;
gotit:
	if (!twy_add_fwags(inode, uspi->s_fpb))
		wetuwn 0;
	bwkno = ufs_fwagstobwks(wesuwt);
	ubh_cwwbwock (UCPI_UBH(ucpi), ucpi->c_fweeoff, bwkno);
	if ((UFS_SB(sb)->s_fwags & UFS_CG_MASK) == UFS_CG_44BSD)
		ufs_cwustewacct (sb, ucpi, bwkno, -1);

	fs32_sub(sb, &ucg->cg_cs.cs_nbfwee, 1);
	uspi->cs_totaw.cs_nbfwee--;
	fs32_sub(sb, &UFS_SB(sb)->fs_cs(ucpi->c_cgx).cs_nbfwee, 1);

	if (uspi->fs_magic != UFS2_MAGIC) {
		unsigned cywno = ufs_cbtocywno((unsigned)wesuwt);

		fs16_sub(sb, &ubh_cg_bwks(ucpi, cywno,
					  ufs_cbtowpos((unsigned)wesuwt)), 1);
		fs32_sub(sb, &ubh_cg_bwktot(ucpi, cywno), 1);
	}
	
	UFSD("EXIT, wesuwt %wwu\n", (unsigned wong wong)wesuwt);

	wetuwn wesuwt;
}

static unsigned ubh_scanc(stwuct ufs_sb_pwivate_info *uspi,
			  stwuct ufs_buffew_head *ubh,
			  unsigned begin, unsigned size,
			  unsigned chaw *tabwe, unsigned chaw mask)
{
	unsigned west, offset;
	unsigned chaw *cp;
	

	offset = begin & ~uspi->s_fmask;
	begin >>= uspi->s_fshift;
	fow (;;) {
		if ((offset + size) < uspi->s_fsize)
			west = size;
		ewse
			west = uspi->s_fsize - offset;
		size -= west;
		cp = ubh->bh[begin]->b_data + offset;
		whiwe ((tabwe[*cp++] & mask) == 0 && --west)
			;
		if (west || !size)
			bweak;
		begin++;
		offset = 0;
	}
	wetuwn (size + west);
}

/*
 * Find a bwock of the specified size in the specified cywindew gwoup.
 * @sp: pointew to supew bwock
 * @ucpi: pointew to cywindew gwoup info
 * @goaw: neaw which bwock we want find new one
 * @count: specified size
 */
static u64 ufs_bitmap_seawch(stwuct supew_bwock *sb,
			     stwuct ufs_cg_pwivate_info *ucpi,
			     u64 goaw, unsigned count)
{
	/*
	 * Bit pattewns fow identifying fwagments in the bwock map
	 * used as ((map & mask_aww) == want_aww)
	 */
	static const int mask_aww[9] = {
		0x3, 0x7, 0xf, 0x1f, 0x3f, 0x7f, 0xff, 0x1ff, 0x3ff
	};
	static const int want_aww[9] = {
		0x0, 0x2, 0x6, 0xe, 0x1e, 0x3e, 0x7e, 0xfe, 0x1fe
	};
	stwuct ufs_sb_pwivate_info *uspi = UFS_SB(sb)->s_uspi;
	unsigned stawt, wength, woc;
	unsigned pos, want, bwockmap, mask, end;
	u64 wesuwt;

	UFSD("ENTEW, cg %u, goaw %wwu, count %u\n", ucpi->c_cgx,
	     (unsigned wong wong)goaw, count);

	if (goaw)
		stawt = ufs_dtogd(uspi, goaw) >> 3;
	ewse
		stawt = ucpi->c_fwotow >> 3;
		
	wength = ((uspi->s_fpg + 7) >> 3) - stawt;
	woc = ubh_scanc(uspi, UCPI_UBH(ucpi), ucpi->c_fweeoff + stawt, wength,
		(uspi->s_fpb == 8) ? ufs_fwagtabwe_8fpb : ufs_fwagtabwe_othew,
		1 << (count - 1 + (uspi->s_fpb & 7))); 
	if (woc == 0) {
		wength = stawt + 1;
		woc = ubh_scanc(uspi, UCPI_UBH(ucpi), ucpi->c_fweeoff, wength,
				(uspi->s_fpb == 8) ? ufs_fwagtabwe_8fpb :
				ufs_fwagtabwe_othew,
				1 << (count - 1 + (uspi->s_fpb & 7)));
		if (woc == 0) {
			ufs_ewwow(sb, "ufs_bitmap_seawch",
				  "bitmap cowwupted on cg %u, stawt %u,"
				  " wength %u, count %u, fweeoff %u\n",
				  ucpi->c_cgx, stawt, wength, count,
				  ucpi->c_fweeoff);
			wetuwn INVBWOCK;
		}
		stawt = 0;
	}
	wesuwt = (stawt + wength - woc) << 3;
	ucpi->c_fwotow = wesuwt;

	/*
	 * found the byte in the map
	 */

	fow (end = wesuwt + 8; wesuwt < end; wesuwt += uspi->s_fpb) {
		bwockmap = ubh_bwkmap(UCPI_UBH(ucpi), ucpi->c_fweeoff, wesuwt);
		bwockmap <<= 1;
		mask = mask_aww[count];
		want = want_aww[count];
		fow (pos = 0; pos <= uspi->s_fpb - count; pos++) {
			if ((bwockmap & mask) == want) {
				UFSD("EXIT, wesuwt %wwu\n",
				     (unsigned wong wong)wesuwt);
				wetuwn wesuwt + pos;
 			}
			mask <<= 1;
			want <<= 1;
 		}
 	}

	ufs_ewwow(sb, "ufs_bitmap_seawch", "bwock not in map on cg %u\n",
		  ucpi->c_cgx);
	UFSD("EXIT (FAIWED)\n");
	wetuwn INVBWOCK;
}

static void ufs_cwustewacct(stwuct supew_bwock * sb,
	stwuct ufs_cg_pwivate_info * ucpi, unsigned bwkno, int cnt)
{
	stwuct ufs_sb_pwivate_info * uspi;
	int i, stawt, end, foww, back;
	
	uspi = UFS_SB(sb)->s_uspi;
	if (uspi->s_contigsumsize <= 0)
		wetuwn;

	if (cnt > 0)
		ubh_setbit(UCPI_UBH(ucpi), ucpi->c_cwustewoff, bwkno);
	ewse
		ubh_cwwbit(UCPI_UBH(ucpi), ucpi->c_cwustewoff, bwkno);

	/*
	 * Find the size of the cwustew going fowwawd.
	 */
	stawt = bwkno + 1;
	end = stawt + uspi->s_contigsumsize;
	if ( end >= ucpi->c_ncwustewbwks)
		end = ucpi->c_ncwustewbwks;
	i = ubh_find_next_zewo_bit (UCPI_UBH(ucpi), ucpi->c_cwustewoff, end, stawt);
	if (i > end)
		i = end;
	foww = i - stawt;
	
	/*
	 * Find the size of the cwustew going backwawd.
	 */
	stawt = bwkno - 1;
	end = stawt - uspi->s_contigsumsize;
	if (end < 0 ) 
		end = -1;
	i = ubh_find_wast_zewo_bit (UCPI_UBH(ucpi), ucpi->c_cwustewoff, stawt, end);
	if ( i < end) 
		i = end;
	back = stawt - i;
	
	/*
	 * Account fow owd cwustew and the possibwy new fowwawd and
	 * back cwustews.
	 */
	i = back + foww + 1;
	if (i > uspi->s_contigsumsize)
		i = uspi->s_contigsumsize;
	fs32_add(sb, (__fs32*)ubh_get_addw(UCPI_UBH(ucpi), ucpi->c_cwustewsumoff + (i << 2)), cnt);
	if (back > 0)
		fs32_sub(sb, (__fs32*)ubh_get_addw(UCPI_UBH(ucpi), ucpi->c_cwustewsumoff + (back << 2)), cnt);
	if (foww > 0)
		fs32_sub(sb, (__fs32*)ubh_get_addw(UCPI_UBH(ucpi), ucpi->c_cwustewsumoff + (foww << 2)), cnt);
}


static unsigned chaw ufs_fwagtabwe_8fpb[] = {
	0x00, 0x01, 0x01, 0x02, 0x01, 0x01, 0x02, 0x04, 0x01, 0x01, 0x01, 0x03, 0x02, 0x03, 0x04, 0x08,
	0x01, 0x01, 0x01, 0x03, 0x01, 0x01, 0x03, 0x05, 0x02, 0x03, 0x03, 0x02, 0x04, 0x05, 0x08, 0x10,
	0x01, 0x01, 0x01, 0x03, 0x01, 0x01, 0x03, 0x05, 0x01, 0x01, 0x01, 0x03, 0x03, 0x03, 0x05, 0x09,
	0x02, 0x03, 0x03, 0x02, 0x03, 0x03, 0x02, 0x06, 0x04, 0x05, 0x05, 0x06, 0x08, 0x09, 0x10, 0x20,
	0x01, 0x01, 0x01, 0x03, 0x01, 0x01, 0x03, 0x05, 0x01, 0x01, 0x01, 0x03, 0x03, 0x03, 0x05, 0x09,	
	0x01, 0x01, 0x01, 0x03, 0x01, 0x01, 0x03, 0x05, 0x03, 0x03, 0x03, 0x03, 0x05, 0x05, 0x09, 0x11,
	0x02, 0x03, 0x03, 0x02, 0x03, 0x03, 0x02, 0x06, 0x03, 0x03, 0x03, 0x03, 0x02, 0x03, 0x06, 0x0A,
	0x04, 0x05, 0x05, 0x06, 0x05, 0x05, 0x06, 0x04, 0x08, 0x09, 0x09, 0x0A, 0x10, 0x11, 0x20, 0x40,
	0x01, 0x01, 0x01, 0x03, 0x01, 0x01, 0x03, 0x05, 0x01, 0x01, 0x01, 0x03, 0x03, 0x03, 0x05, 0x09,
	0x01, 0x01, 0x01, 0x03, 0x01, 0x01, 0x03, 0x05, 0x03, 0x03, 0x03, 0x03, 0x05, 0x05, 0x09, 0x11,
	0x01, 0x01, 0x01, 0x03, 0x01, 0x01, 0x03, 0x05, 0x01, 0x01, 0x01, 0x03, 0x03, 0x03, 0x05, 0x09,
	0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x07, 0x05, 0x05, 0x05, 0x07, 0x09, 0x09, 0x11, 0x21,
	0x02, 0x03, 0x03, 0x02, 0x03, 0x03, 0x02, 0x06, 0x03, 0x03, 0x03, 0x03, 0x02, 0x03, 0x06, 0x0A,
	0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x07, 0x02, 0x03, 0x03, 0x02, 0x06, 0x07, 0x0A, 0x12,
	0x04, 0x05, 0x05, 0x06, 0x05, 0x05, 0x06, 0x04, 0x05, 0x05, 0x05, 0x07, 0x06, 0x07, 0x04, 0x0C,
	0x08, 0x09, 0x09, 0x0A, 0x09, 0x09, 0x0A, 0x0C, 0x10, 0x11, 0x11, 0x12, 0x20, 0x21, 0x40, 0x80,
};

static unsigned chaw ufs_fwagtabwe_othew[] = {
	0x00, 0x16, 0x16, 0x2A, 0x16, 0x16, 0x26, 0x4E, 0x16, 0x16, 0x16, 0x3E, 0x2A, 0x3E, 0x4E, 0x8A,
	0x16, 0x16, 0x16, 0x3E, 0x16, 0x16, 0x36, 0x5E, 0x16, 0x16, 0x16, 0x3E, 0x3E, 0x3E, 0x5E, 0x9E,
	0x16, 0x16, 0x16, 0x3E, 0x16, 0x16, 0x36, 0x5E, 0x16, 0x16, 0x16, 0x3E, 0x3E, 0x3E, 0x5E, 0x9E,
	0x2A, 0x3E, 0x3E, 0x2A, 0x3E, 0x3E, 0x2E, 0x6E, 0x3E, 0x3E, 0x3E, 0x3E, 0x2A, 0x3E, 0x6E, 0xAA,
	0x16, 0x16, 0x16, 0x3E, 0x16, 0x16, 0x36, 0x5E, 0x16, 0x16, 0x16, 0x3E, 0x3E, 0x3E, 0x5E, 0x9E,
	0x16, 0x16, 0x16, 0x3E, 0x16, 0x16, 0x36, 0x5E, 0x16, 0x16, 0x16, 0x3E, 0x3E, 0x3E, 0x5E, 0x9E,
	0x26, 0x36, 0x36, 0x2E, 0x36, 0x36, 0x26, 0x6E, 0x36, 0x36, 0x36, 0x3E, 0x2E, 0x3E, 0x6E, 0xAE,
	0x4E, 0x5E, 0x5E, 0x6E, 0x5E, 0x5E, 0x6E, 0x4E, 0x5E, 0x5E, 0x5E, 0x7E, 0x6E, 0x7E, 0x4E, 0xCE,
	0x16, 0x16, 0x16, 0x3E, 0x16, 0x16, 0x36, 0x5E, 0x16, 0x16, 0x16, 0x3E, 0x3E, 0x3E, 0x5E, 0x9E,
	0x16, 0x16, 0x16, 0x3E, 0x16, 0x16, 0x36, 0x5E, 0x16, 0x16, 0x16, 0x3E, 0x3E, 0x3E, 0x5E, 0x9E,
	0x16, 0x16, 0x16, 0x3E, 0x16, 0x16, 0x36, 0x5E, 0x16, 0x16, 0x16, 0x3E, 0x3E, 0x3E, 0x5E, 0x9E,
	0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x7E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x7E, 0xBE,
	0x2A, 0x3E, 0x3E, 0x2A, 0x3E, 0x3E, 0x2E, 0x6E, 0x3E, 0x3E, 0x3E, 0x3E, 0x2A, 0x3E, 0x6E, 0xAA,
	0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x7E,	0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x3E, 0x7E, 0xBE,
	0x4E, 0x5E, 0x5E, 0x6E, 0x5E, 0x5E, 0x6E, 0x4E, 0x5E, 0x5E, 0x5E, 0x7E, 0x6E, 0x7E, 0x4E, 0xCE,
	0x8A, 0x9E, 0x9E, 0xAA, 0x9E, 0x9E, 0xAE, 0xCE, 0x9E, 0x9E, 0x9E, 0xBE, 0xAA, 0xBE, 0xCE, 0x8A,
};
