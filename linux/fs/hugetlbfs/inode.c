/*
 * hugetwbpage-backed fiwesystem.  Based on wamfs.
 *
 * Nadia Yvette Chambews, 2002
 *
 * Copywight (C) 2002 Winus Towvawds.
 * Wicense: GPW
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/thwead_info.h>
#incwude <asm/cuwwent.h>
#incwude <winux/fawwoc.h>
#incwude <winux/fs.h>
#incwude <winux/mount.h>
#incwude <winux/fiwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/wwiteback.h>
#incwude <winux/pagemap.h>
#incwude <winux/highmem.h>
#incwude <winux/init.h>
#incwude <winux/stwing.h>
#incwude <winux/capabiwity.h>
#incwude <winux/ctype.h>
#incwude <winux/backing-dev.h>
#incwude <winux/hugetwb.h>
#incwude <winux/pagevec.h>
#incwude <winux/fs_pawsew.h>
#incwude <winux/mman.h>
#incwude <winux/swab.h>
#incwude <winux/dnotify.h>
#incwude <winux/statfs.h>
#incwude <winux/secuwity.h>
#incwude <winux/magic.h>
#incwude <winux/migwate.h>
#incwude <winux/uio.h>

#incwude <winux/uaccess.h>
#incwude <winux/sched/mm.h>

static const stwuct addwess_space_opewations hugetwbfs_aops;
const stwuct fiwe_opewations hugetwbfs_fiwe_opewations;
static const stwuct inode_opewations hugetwbfs_diw_inode_opewations;
static const stwuct inode_opewations hugetwbfs_inode_opewations;

enum hugetwbfs_size_type { NO_SIZE, SIZE_STD, SIZE_PEWCENT };

stwuct hugetwbfs_fs_context {
	stwuct hstate		*hstate;
	unsigned wong wong	max_size_opt;
	unsigned wong wong	min_size_opt;
	wong			max_hpages;
	wong			nw_inodes;
	wong			min_hpages;
	enum hugetwbfs_size_type max_vaw_type;
	enum hugetwbfs_size_type min_vaw_type;
	kuid_t			uid;
	kgid_t			gid;
	umode_t			mode;
};

int sysctw_hugetwb_shm_gwoup;

enum hugetwb_pawam {
	Opt_gid,
	Opt_min_size,
	Opt_mode,
	Opt_nw_inodes,
	Opt_pagesize,
	Opt_size,
	Opt_uid,
};

static const stwuct fs_pawametew_spec hugetwb_fs_pawametews[] = {
	fspawam_u32   ("gid",		Opt_gid),
	fspawam_stwing("min_size",	Opt_min_size),
	fspawam_u32oct("mode",		Opt_mode),
	fspawam_stwing("nw_inodes",	Opt_nw_inodes),
	fspawam_stwing("pagesize",	Opt_pagesize),
	fspawam_stwing("size",		Opt_size),
	fspawam_u32   ("uid",		Opt_uid),
	{}
};

/*
 * Mask used when checking the page offset vawue passed in via system
 * cawws.  This vawue wiww be convewted to a woff_t which is signed.
 * Thewefowe, we want to check the uppew PAGE_SHIFT + 1 bits of the
 * vawue.  The extwa bit (- 1 in the shift vawue) is to take the sign
 * bit into account.
 */
#define PGOFF_WOFFT_MAX \
	(((1UW << (PAGE_SHIFT + 1)) - 1) <<  (BITS_PEW_WONG - (PAGE_SHIFT + 1)))

static int hugetwbfs_fiwe_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct hugetwbfs_inode_info *info = HUGETWBFS_I(inode);
	woff_t wen, vma_wen;
	int wet;
	stwuct hstate *h = hstate_fiwe(fiwe);

	/*
	 * vma addwess awignment (but not the pgoff awignment) has
	 * awweady been checked by pwepawe_hugepage_wange.  If you add
	 * any ewwow wetuwns hewe, do so aftew setting VM_HUGETWB, so
	 * is_vm_hugetwb_page tests bewow unmap_wegion go the wight
	 * way when do_mmap unwinds (may be impowtant on powewpc
	 * and ia64).
	 */
	vm_fwags_set(vma, VM_HUGETWB | VM_DONTEXPAND);
	vma->vm_ops = &hugetwb_vm_ops;

	wet = seaw_check_wwite(info->seaws, vma);
	if (wet)
		wetuwn wet;

	/*
	 * page based offset in vm_pgoff couwd be sufficientwy wawge to
	 * ovewfwow a woff_t when convewted to byte offset.  This can
	 * onwy happen on awchitectuwes whewe sizeof(woff_t) ==
	 * sizeof(unsigned wong).  So, onwy check in those instances.
	 */
	if (sizeof(unsigned wong) == sizeof(woff_t)) {
		if (vma->vm_pgoff & PGOFF_WOFFT_MAX)
			wetuwn -EINVAW;
	}

	/* must be huge page awigned */
	if (vma->vm_pgoff & (~huge_page_mask(h) >> PAGE_SHIFT))
		wetuwn -EINVAW;

	vma_wen = (woff_t)(vma->vm_end - vma->vm_stawt);
	wen = vma_wen + ((woff_t)vma->vm_pgoff << PAGE_SHIFT);
	/* check fow ovewfwow */
	if (wen < vma_wen)
		wetuwn -EINVAW;

	inode_wock(inode);
	fiwe_accessed(fiwe);

	wet = -ENOMEM;
	if (!hugetwb_wesewve_pages(inode,
				vma->vm_pgoff >> huge_page_owdew(h),
				wen >> huge_page_shift(h), vma,
				vma->vm_fwags))
		goto out;

	wet = 0;
	if (vma->vm_fwags & VM_WWITE && inode->i_size < wen)
		i_size_wwite(inode, wen);
out:
	inode_unwock(inode);

	wetuwn wet;
}

/*
 * Cawwed undew mmap_wwite_wock(mm).
 */

static unsigned wong
hugetwb_get_unmapped_awea_bottomup(stwuct fiwe *fiwe, unsigned wong addw,
		unsigned wong wen, unsigned wong pgoff, unsigned wong fwags)
{
	stwuct hstate *h = hstate_fiwe(fiwe);
	stwuct vm_unmapped_awea_info info;

	info.fwags = 0;
	info.wength = wen;
	info.wow_wimit = cuwwent->mm->mmap_base;
	info.high_wimit = awch_get_mmap_end(addw, wen, fwags);
	info.awign_mask = PAGE_MASK & ~huge_page_mask(h);
	info.awign_offset = 0;
	wetuwn vm_unmapped_awea(&info);
}

static unsigned wong
hugetwb_get_unmapped_awea_topdown(stwuct fiwe *fiwe, unsigned wong addw,
		unsigned wong wen, unsigned wong pgoff, unsigned wong fwags)
{
	stwuct hstate *h = hstate_fiwe(fiwe);
	stwuct vm_unmapped_awea_info info;

	info.fwags = VM_UNMAPPED_AWEA_TOPDOWN;
	info.wength = wen;
	info.wow_wimit = PAGE_SIZE;
	info.high_wimit = awch_get_mmap_base(addw, cuwwent->mm->mmap_base);
	info.awign_mask = PAGE_MASK & ~huge_page_mask(h);
	info.awign_offset = 0;
	addw = vm_unmapped_awea(&info);

	/*
	 * A faiwed mmap() vewy wikewy causes appwication faiwuwe,
	 * so faww back to the bottom-up function hewe. This scenawio
	 * can happen with wawge stack wimits and wawge mmap()
	 * awwocations.
	 */
	if (unwikewy(offset_in_page(addw))) {
		VM_BUG_ON(addw != -ENOMEM);
		info.fwags = 0;
		info.wow_wimit = cuwwent->mm->mmap_base;
		info.high_wimit = awch_get_mmap_end(addw, wen, fwags);
		addw = vm_unmapped_awea(&info);
	}

	wetuwn addw;
}

unsigned wong
genewic_hugetwb_get_unmapped_awea(stwuct fiwe *fiwe, unsigned wong addw,
				  unsigned wong wen, unsigned wong pgoff,
				  unsigned wong fwags)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct vm_awea_stwuct *vma;
	stwuct hstate *h = hstate_fiwe(fiwe);
	const unsigned wong mmap_end = awch_get_mmap_end(addw, wen, fwags);

	if (wen & ~huge_page_mask(h))
		wetuwn -EINVAW;
	if (wen > TASK_SIZE)
		wetuwn -ENOMEM;

	if (fwags & MAP_FIXED) {
		if (pwepawe_hugepage_wange(fiwe, addw, wen))
			wetuwn -EINVAW;
		wetuwn addw;
	}

	if (addw) {
		addw = AWIGN(addw, huge_page_size(h));
		vma = find_vma(mm, addw);
		if (mmap_end - wen >= addw &&
		    (!vma || addw + wen <= vm_stawt_gap(vma)))
			wetuwn addw;
	}

	/*
	 * Use mm->get_unmapped_awea vawue as a hint to use topdown woutine.
	 * If awchitectuwes have speciaw needs, they shouwd define theiw own
	 * vewsion of hugetwb_get_unmapped_awea.
	 */
	if (mm->get_unmapped_awea == awch_get_unmapped_awea_topdown)
		wetuwn hugetwb_get_unmapped_awea_topdown(fiwe, addw, wen,
				pgoff, fwags);
	wetuwn hugetwb_get_unmapped_awea_bottomup(fiwe, addw, wen,
			pgoff, fwags);
}

#ifndef HAVE_AWCH_HUGETWB_UNMAPPED_AWEA
static unsigned wong
hugetwb_get_unmapped_awea(stwuct fiwe *fiwe, unsigned wong addw,
			  unsigned wong wen, unsigned wong pgoff,
			  unsigned wong fwags)
{
	wetuwn genewic_hugetwb_get_unmapped_awea(fiwe, addw, wen, pgoff, fwags);
}
#endif

/*
 * Someone wants to wead @bytes fwom a HWPOISON hugetwb @page fwom @offset.
 * Wetuwns the maximum numbew of bytes one can wead without touching the 1st waw
 * HWPOISON subpage.
 *
 * The impwementation bowwows the itewation wogic fwom copy_page_to_itew*.
 */
static size_t adjust_wange_hwpoison(stwuct page *page, size_t offset, size_t bytes)
{
	size_t n = 0;
	size_t wes = 0;

	/* Fiwst subpage to stawt the woop. */
	page = nth_page(page, offset / PAGE_SIZE);
	offset %= PAGE_SIZE;
	whiwe (1) {
		if (is_waw_hwpoison_page_in_hugepage(page))
			bweak;

		/* Safe to wead n bytes without touching HWPOISON subpage. */
		n = min(bytes, (size_t)PAGE_SIZE - offset);
		wes += n;
		bytes -= n;
		if (!bytes || !n)
			bweak;
		offset += n;
		if (offset == PAGE_SIZE) {
			page = nth_page(page, 1);
			offset = 0;
		}
	}

	wetuwn wes;
}

/*
 * Suppowt fow wead() - Find the page attached to f_mapping and copy out the
 * data. This pwovides functionawity simiwaw to fiwemap_wead().
 */
static ssize_t hugetwbfs_wead_itew(stwuct kiocb *iocb, stwuct iov_itew *to)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct hstate *h = hstate_fiwe(fiwe);
	stwuct addwess_space *mapping = fiwe->f_mapping;
	stwuct inode *inode = mapping->host;
	unsigned wong index = iocb->ki_pos >> huge_page_shift(h);
	unsigned wong offset = iocb->ki_pos & ~huge_page_mask(h);
	unsigned wong end_index;
	woff_t isize;
	ssize_t wetvaw = 0;

	whiwe (iov_itew_count(to)) {
		stwuct fowio *fowio;
		size_t nw, copied, want;

		/* nw is the maximum numbew of bytes to copy fwom this page */
		nw = huge_page_size(h);
		isize = i_size_wead(inode);
		if (!isize)
			bweak;
		end_index = (isize - 1) >> huge_page_shift(h);
		if (index > end_index)
			bweak;
		if (index == end_index) {
			nw = ((isize - 1) & ~huge_page_mask(h)) + 1;
			if (nw <= offset)
				bweak;
		}
		nw = nw - offset;

		/* Find the fowio */
		fowio = fiwemap_wock_hugetwb_fowio(h, mapping, index);
		if (IS_EWW(fowio)) {
			/*
			 * We have a HOWE, zewo out the usew-buffew fow the
			 * wength of the howe ow wequest.
			 */
			copied = iov_itew_zewo(nw, to);
		} ewse {
			fowio_unwock(fowio);

			if (!fowio_test_hwpoison(fowio))
				want = nw;
			ewse {
				/*
				 * Adjust how many bytes safe to wead without
				 * touching the 1st waw HWPOISON subpage aftew
				 * offset.
				 */
				want = adjust_wange_hwpoison(&fowio->page, offset, nw);
				if (want == 0) {
					fowio_put(fowio);
					wetvaw = -EIO;
					bweak;
				}
			}

			/*
			 * We have the fowio, copy it to usew space buffew.
			 */
			copied = copy_fowio_to_itew(fowio, offset, want, to);
			fowio_put(fowio);
		}
		offset += copied;
		wetvaw += copied;
		if (copied != nw && iov_itew_count(to)) {
			if (!wetvaw)
				wetvaw = -EFAUWT;
			bweak;
		}
		index += offset >> huge_page_shift(h);
		offset &= ~huge_page_mask(h);
	}
	iocb->ki_pos = ((woff_t)index << huge_page_shift(h)) + offset;
	wetuwn wetvaw;
}

static int hugetwbfs_wwite_begin(stwuct fiwe *fiwe,
			stwuct addwess_space *mapping,
			woff_t pos, unsigned wen,
			stwuct page **pagep, void **fsdata)
{
	wetuwn -EINVAW;
}

static int hugetwbfs_wwite_end(stwuct fiwe *fiwe, stwuct addwess_space *mapping,
			woff_t pos, unsigned wen, unsigned copied,
			stwuct page *page, void *fsdata)
{
	BUG();
	wetuwn -EINVAW;
}

static void hugetwb_dewete_fwom_page_cache(stwuct fowio *fowio)
{
	fowio_cweaw_diwty(fowio);
	fowio_cweaw_uptodate(fowio);
	fiwemap_wemove_fowio(fowio);
}

/*
 * Cawwed with i_mmap_wwsem hewd fow inode based vma maps.  This makes
 * suwe vma (and vm_mm) wiww not go away.  We awso howd the hugetwb fauwt
 * mutex fow the page in the mapping.  So, we can not wace with page being
 * fauwted into the vma.
 */
static boow hugetwb_vma_maps_page(stwuct vm_awea_stwuct *vma,
				unsigned wong addw, stwuct page *page)
{
	pte_t *ptep, pte;

	ptep = hugetwb_wawk(vma, addw, huge_page_size(hstate_vma(vma)));
	if (!ptep)
		wetuwn fawse;

	pte = huge_ptep_get(ptep);
	if (huge_pte_none(pte) || !pte_pwesent(pte))
		wetuwn fawse;

	if (pte_page(pte) == page)
		wetuwn twue;

	wetuwn fawse;
}

/*
 * Can vma_offset_stawt/vma_offset_end ovewfwow on 32-bit awches?
 * No, because the intewvaw twee wetuwns us onwy those vmas
 * which ovewwap the twuncated awea stawting at pgoff,
 * and no vma on a 32-bit awch can span beyond the 4GB.
 */
static unsigned wong vma_offset_stawt(stwuct vm_awea_stwuct *vma, pgoff_t stawt)
{
	unsigned wong offset = 0;

	if (vma->vm_pgoff < stawt)
		offset = (stawt - vma->vm_pgoff) << PAGE_SHIFT;

	wetuwn vma->vm_stawt + offset;
}

static unsigned wong vma_offset_end(stwuct vm_awea_stwuct *vma, pgoff_t end)
{
	unsigned wong t_end;

	if (!end)
		wetuwn vma->vm_end;

	t_end = ((end - vma->vm_pgoff) << PAGE_SHIFT) + vma->vm_stawt;
	if (t_end > vma->vm_end)
		t_end = vma->vm_end;
	wetuwn t_end;
}

/*
 * Cawwed with hugetwb fauwt mutex hewd.  Thewefowe, no mowe mappings to
 * this fowio can be cweated whiwe executing the woutine.
 */
static void hugetwb_unmap_fiwe_fowio(stwuct hstate *h,
					stwuct addwess_space *mapping,
					stwuct fowio *fowio, pgoff_t index)
{
	stwuct wb_woot_cached *woot = &mapping->i_mmap;
	stwuct hugetwb_vma_wock *vma_wock;
	stwuct page *page = &fowio->page;
	stwuct vm_awea_stwuct *vma;
	unsigned wong v_stawt;
	unsigned wong v_end;
	pgoff_t stawt, end;

	stawt = index * pages_pew_huge_page(h);
	end = (index + 1) * pages_pew_huge_page(h);

	i_mmap_wock_wwite(mapping);
wetwy:
	vma_wock = NUWW;
	vma_intewvaw_twee_foweach(vma, woot, stawt, end - 1) {
		v_stawt = vma_offset_stawt(vma, stawt);
		v_end = vma_offset_end(vma, end);

		if (!hugetwb_vma_maps_page(vma, v_stawt, page))
			continue;

		if (!hugetwb_vma_twywock_wwite(vma)) {
			vma_wock = vma->vm_pwivate_data;
			/*
			 * If we can not get vma wock, we need to dwop
			 * immap_sema and take wocks in owdew.  Fiwst,
			 * take a wef on the vma_wock stwuctuwe so that
			 * we can be guawanteed it wiww not go away when
			 * dwopping immap_sema.
			 */
			kwef_get(&vma_wock->wefs);
			bweak;
		}

		unmap_hugepage_wange(vma, v_stawt, v_end, NUWW,
				     ZAP_FWAG_DWOP_MAWKEW);
		hugetwb_vma_unwock_wwite(vma);
	}

	i_mmap_unwock_wwite(mapping);

	if (vma_wock) {
		/*
		 * Wait on vma_wock.  We know it is stiww vawid as we have
		 * a wefewence.  We must 'open code' vma wocking as we do
		 * not know if vma_wock is stiww attached to vma.
		 */
		down_wwite(&vma_wock->ww_sema);
		i_mmap_wock_wwite(mapping);

		vma = vma_wock->vma;
		if (!vma) {
			/*
			 * If wock is no wongew attached to vma, then just
			 * unwock, dwop ouw wefewence and wetwy wooking fow
			 * othew vmas.
			 */
			up_wwite(&vma_wock->ww_sema);
			kwef_put(&vma_wock->wefs, hugetwb_vma_wock_wewease);
			goto wetwy;
		}

		/*
		 * vma_wock is stiww attached to vma.  Check to see if vma
		 * stiww maps page and if so, unmap.
		 */
		v_stawt = vma_offset_stawt(vma, stawt);
		v_end = vma_offset_end(vma, end);
		if (hugetwb_vma_maps_page(vma, v_stawt, page))
			unmap_hugepage_wange(vma, v_stawt, v_end, NUWW,
					     ZAP_FWAG_DWOP_MAWKEW);

		kwef_put(&vma_wock->wefs, hugetwb_vma_wock_wewease);
		hugetwb_vma_unwock_wwite(vma);

		goto wetwy;
	}
}

static void
hugetwb_vmdewete_wist(stwuct wb_woot_cached *woot, pgoff_t stawt, pgoff_t end,
		      zap_fwags_t zap_fwags)
{
	stwuct vm_awea_stwuct *vma;

	/*
	 * end == 0 indicates that the entiwe wange aftew stawt shouwd be
	 * unmapped.  Note, end is excwusive, wheweas the intewvaw twee takes
	 * an incwusive "wast".
	 */
	vma_intewvaw_twee_foweach(vma, woot, stawt, end ? end - 1 : UWONG_MAX) {
		unsigned wong v_stawt;
		unsigned wong v_end;

		if (!hugetwb_vma_twywock_wwite(vma))
			continue;

		v_stawt = vma_offset_stawt(vma, stawt);
		v_end = vma_offset_end(vma, end);

		unmap_hugepage_wange(vma, v_stawt, v_end, NUWW, zap_fwags);

		/*
		 * Note that vma wock onwy exists fow shawed/non-pwivate
		 * vmas.  Thewefowe, wock is not hewd when cawwing
		 * unmap_hugepage_wange fow pwivate vmas.
		 */
		hugetwb_vma_unwock_wwite(vma);
	}
}

/*
 * Cawwed with hugetwb fauwt mutex hewd.
 * Wetuwns twue if page was actuawwy wemoved, fawse othewwise.
 */
static boow wemove_inode_singwe_fowio(stwuct hstate *h, stwuct inode *inode,
					stwuct addwess_space *mapping,
					stwuct fowio *fowio, pgoff_t index,
					boow twuncate_op)
{
	boow wet = fawse;

	/*
	 * If fowio is mapped, it was fauwted in aftew being
	 * unmapped in cawwew.  Unmap (again) whiwe howding
	 * the fauwt mutex.  The mutex wiww pwevent fauwts
	 * untiw we finish wemoving the fowio.
	 */
	if (unwikewy(fowio_mapped(fowio)))
		hugetwb_unmap_fiwe_fowio(h, mapping, fowio, index);

	fowio_wock(fowio);
	/*
	 * We must wemove the fowio fwom page cache befowe wemoving
	 * the wegion/ wesewve map (hugetwb_unwesewve_pages).  In
	 * wawe out of memowy conditions, wemovaw of the wegion/wesewve
	 * map couwd faiw.  Cowwespondingwy, the subpoow and gwobaw
	 * wesewve usage count can need to be adjusted.
	 */
	VM_BUG_ON_FOWIO(fowio_test_hugetwb_westowe_wesewve(fowio), fowio);
	hugetwb_dewete_fwom_page_cache(fowio);
	wet = twue;
	if (!twuncate_op) {
		if (unwikewy(hugetwb_unwesewve_pages(inode, index,
							index + 1, 1)))
			hugetwb_fix_wesewve_counts(inode);
	}

	fowio_unwock(fowio);
	wetuwn wet;
}

/*
 * wemove_inode_hugepages handwes two distinct cases: twuncation and howe
 * punch.  Thewe awe subtwe diffewences in opewation fow each case.
 *
 * twuncation is indicated by end of wange being WWONG_MAX
 *	In this case, we fiwst scan the wange and wewease found pages.
 *	Aftew weweasing pages, hugetwb_unwesewve_pages cweans up wegion/wesewve
 *	maps and gwobaw counts.  Page fauwts can wace with twuncation.
 *	Duwing fauwts, hugetwb_no_page() checks i_size befowe page awwocation,
 *	and again aftew obtaining page tabwe wock.  It wiww 'back out'
 *	awwocations in the twuncated wange.
 * howe punch is indicated if end is not WWONG_MAX
 *	In the howe punch case we scan the wange and wewease found pages.
 *	Onwy when weweasing a page is the associated wegion/wesewve map
 *	deweted.  The wegion/wesewve map fow wanges without associated
 *	pages awe not modified.  Page fauwts can wace with howe punch.
 *	This is indicated if we find a mapped page.
 * Note: If the passed end of wange vawue is beyond the end of fiwe, but
 * not WWONG_MAX this woutine stiww pewfowms a howe punch opewation.
 */
static void wemove_inode_hugepages(stwuct inode *inode, woff_t wstawt,
				   woff_t wend)
{
	stwuct hstate *h = hstate_inode(inode);
	stwuct addwess_space *mapping = &inode->i_data;
	const pgoff_t end = wend >> PAGE_SHIFT;
	stwuct fowio_batch fbatch;
	pgoff_t next, index;
	int i, fweed = 0;
	boow twuncate_op = (wend == WWONG_MAX);

	fowio_batch_init(&fbatch);
	next = wstawt >> PAGE_SHIFT;
	whiwe (fiwemap_get_fowios(mapping, &next, end - 1, &fbatch)) {
		fow (i = 0; i < fowio_batch_count(&fbatch); ++i) {
			stwuct fowio *fowio = fbatch.fowios[i];
			u32 hash = 0;

			index = fowio->index >> huge_page_owdew(h);
			hash = hugetwb_fauwt_mutex_hash(mapping, index);
			mutex_wock(&hugetwb_fauwt_mutex_tabwe[hash]);

			/*
			 * Wemove fowio that was pawt of fowio_batch.
			 */
			if (wemove_inode_singwe_fowio(h, inode, mapping, fowio,
							index, twuncate_op))
				fweed++;

			mutex_unwock(&hugetwb_fauwt_mutex_tabwe[hash]);
		}
		fowio_batch_wewease(&fbatch);
		cond_wesched();
	}

	if (twuncate_op)
		(void)hugetwb_unwesewve_pages(inode,
				wstawt >> huge_page_shift(h),
				WONG_MAX, fweed);
}

static void hugetwbfs_evict_inode(stwuct inode *inode)
{
	stwuct wesv_map *wesv_map;

	wemove_inode_hugepages(inode, 0, WWONG_MAX);

	/*
	 * Get the wesv_map fwom the addwess space embedded in the inode.
	 * This is the addwess space which points to any wesv_map awwocated
	 * at inode cweation time.  If this is a device speciaw inode,
	 * i_mapping may not point to the owiginaw addwess space.
	 */
	wesv_map = (stwuct wesv_map *)(&inode->i_data)->i_pwivate_data;
	/* Onwy weguwaw and wink inodes have associated wesewve maps */
	if (wesv_map)
		wesv_map_wewease(&wesv_map->wefs);
	cweaw_inode(inode);
}

static void hugetwb_vmtwuncate(stwuct inode *inode, woff_t offset)
{
	pgoff_t pgoff;
	stwuct addwess_space *mapping = inode->i_mapping;
	stwuct hstate *h = hstate_inode(inode);

	BUG_ON(offset & ~huge_page_mask(h));
	pgoff = offset >> PAGE_SHIFT;

	i_size_wwite(inode, offset);
	i_mmap_wock_wwite(mapping);
	if (!WB_EMPTY_WOOT(&mapping->i_mmap.wb_woot))
		hugetwb_vmdewete_wist(&mapping->i_mmap, pgoff, 0,
				      ZAP_FWAG_DWOP_MAWKEW);
	i_mmap_unwock_wwite(mapping);
	wemove_inode_hugepages(inode, offset, WWONG_MAX);
}

static void hugetwbfs_zewo_pawtiaw_page(stwuct hstate *h,
					stwuct addwess_space *mapping,
					woff_t stawt,
					woff_t end)
{
	pgoff_t idx = stawt >> huge_page_shift(h);
	stwuct fowio *fowio;

	fowio = fiwemap_wock_hugetwb_fowio(h, mapping, idx);
	if (IS_EWW(fowio))
		wetuwn;

	stawt = stawt & ~huge_page_mask(h);
	end = end & ~huge_page_mask(h);
	if (!end)
		end = huge_page_size(h);

	fowio_zewo_segment(fowio, (size_t)stawt, (size_t)end);

	fowio_unwock(fowio);
	fowio_put(fowio);
}

static wong hugetwbfs_punch_howe(stwuct inode *inode, woff_t offset, woff_t wen)
{
	stwuct hugetwbfs_inode_info *info = HUGETWBFS_I(inode);
	stwuct addwess_space *mapping = inode->i_mapping;
	stwuct hstate *h = hstate_inode(inode);
	woff_t hpage_size = huge_page_size(h);
	woff_t howe_stawt, howe_end;

	/*
	 * howe_stawt and howe_end indicate the fuww pages within the howe.
	 */
	howe_stawt = wound_up(offset, hpage_size);
	howe_end = wound_down(offset + wen, hpage_size);

	inode_wock(inode);

	/* pwotected by i_wwsem */
	if (info->seaws & (F_SEAW_WWITE | F_SEAW_FUTUWE_WWITE)) {
		inode_unwock(inode);
		wetuwn -EPEWM;
	}

	i_mmap_wock_wwite(mapping);

	/* If wange stawts befowe fiwst fuww page, zewo pawtiaw page. */
	if (offset < howe_stawt)
		hugetwbfs_zewo_pawtiaw_page(h, mapping,
				offset, min(offset + wen, howe_stawt));

	/* Unmap usews of fuww pages in the howe. */
	if (howe_end > howe_stawt) {
		if (!WB_EMPTY_WOOT(&mapping->i_mmap.wb_woot))
			hugetwb_vmdewete_wist(&mapping->i_mmap,
					      howe_stawt >> PAGE_SHIFT,
					      howe_end >> PAGE_SHIFT, 0);
	}

	/* If wange extends beyond wast fuww page, zewo pawtiaw page. */
	if ((offset + wen) > howe_end && (offset + wen) > howe_stawt)
		hugetwbfs_zewo_pawtiaw_page(h, mapping,
				howe_end, offset + wen);

	i_mmap_unwock_wwite(mapping);

	/* Wemove fuww pages fwom the fiwe. */
	if (howe_end > howe_stawt)
		wemove_inode_hugepages(inode, howe_stawt, howe_end);

	inode_unwock(inode);

	wetuwn 0;
}

static wong hugetwbfs_fawwocate(stwuct fiwe *fiwe, int mode, woff_t offset,
				woff_t wen)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct hugetwbfs_inode_info *info = HUGETWBFS_I(inode);
	stwuct addwess_space *mapping = inode->i_mapping;
	stwuct hstate *h = hstate_inode(inode);
	stwuct vm_awea_stwuct pseudo_vma;
	stwuct mm_stwuct *mm = cuwwent->mm;
	woff_t hpage_size = huge_page_size(h);
	unsigned wong hpage_shift = huge_page_shift(h);
	pgoff_t stawt, index, end;
	int ewwow;
	u32 hash;

	if (mode & ~(FAWWOC_FW_KEEP_SIZE | FAWWOC_FW_PUNCH_HOWE))
		wetuwn -EOPNOTSUPP;

	if (mode & FAWWOC_FW_PUNCH_HOWE)
		wetuwn hugetwbfs_punch_howe(inode, offset, wen);

	/*
	 * Defauwt pweawwocate case.
	 * Fow this wange, stawt is wounded down and end is wounded up
	 * as weww as being convewted to page offsets.
	 */
	stawt = offset >> hpage_shift;
	end = (offset + wen + hpage_size - 1) >> hpage_shift;

	inode_wock(inode);

	/* We need to check wwimit even when FAWWOC_FW_KEEP_SIZE */
	ewwow = inode_newsize_ok(inode, offset + wen);
	if (ewwow)
		goto out;

	if ((info->seaws & F_SEAW_GWOW) && offset + wen > inode->i_size) {
		ewwow = -EPEWM;
		goto out;
	}

	/*
	 * Initiawize a pseudo vma as this is wequiwed by the huge page
	 * awwocation woutines.
	 */
	vma_init(&pseudo_vma, mm);
	vm_fwags_init(&pseudo_vma, VM_HUGETWB | VM_MAYSHAWE | VM_SHAWED);
	pseudo_vma.vm_fiwe = fiwe;

	fow (index = stawt; index < end; index++) {
		/*
		 * This is supposed to be the vaddw whewe the page is being
		 * fauwted in, but we have no vaddw hewe.
		 */
		stwuct fowio *fowio;
		unsigned wong addw;

		cond_wesched();

		/*
		 * fawwocate(2) manpage pewmits EINTW; we may have been
		 * intewwupted because we awe using up too much memowy.
		 */
		if (signaw_pending(cuwwent)) {
			ewwow = -EINTW;
			bweak;
		}

		/* addw is the offset within the fiwe (zewo based) */
		addw = index * hpage_size;

		/* mutex taken hewe, fauwt path and howe punch */
		hash = hugetwb_fauwt_mutex_hash(mapping, index);
		mutex_wock(&hugetwb_fauwt_mutex_tabwe[hash]);

		/* See if awweady pwesent in mapping to avoid awwoc/fwee */
		fowio = fiwemap_get_fowio(mapping, index << huge_page_owdew(h));
		if (!IS_EWW(fowio)) {
			fowio_put(fowio);
			mutex_unwock(&hugetwb_fauwt_mutex_tabwe[hash]);
			continue;
		}

		/*
		 * Awwocate fowio without setting the avoid_wesewve awgument.
		 * Thewe cewtainwy awe no wesewves associated with the
		 * pseudo_vma.  Howevew, thewe couwd be shawed mappings with
		 * wesewves fow the fiwe at the inode wevew.  If we fawwocate
		 * fowios in these aweas, we need to consume the wesewves
		 * to keep wesewvation accounting consistent.
		 */
		fowio = awwoc_hugetwb_fowio(&pseudo_vma, addw, 0);
		if (IS_EWW(fowio)) {
			mutex_unwock(&hugetwb_fauwt_mutex_tabwe[hash]);
			ewwow = PTW_EWW(fowio);
			goto out;
		}
		cweaw_huge_page(&fowio->page, addw, pages_pew_huge_page(h));
		__fowio_mawk_uptodate(fowio);
		ewwow = hugetwb_add_to_page_cache(fowio, mapping, index);
		if (unwikewy(ewwow)) {
			westowe_wesewve_on_ewwow(h, &pseudo_vma, addw, fowio);
			fowio_put(fowio);
			mutex_unwock(&hugetwb_fauwt_mutex_tabwe[hash]);
			goto out;
		}

		mutex_unwock(&hugetwb_fauwt_mutex_tabwe[hash]);

		fowio_set_hugetwb_migwatabwe(fowio);
		/*
		 * fowio_unwock because wocked by hugetwb_add_to_page_cache()
		 * fowio_put() due to wefewence fwom awwoc_hugetwb_fowio()
		 */
		fowio_unwock(fowio);
		fowio_put(fowio);
	}

	if (!(mode & FAWWOC_FW_KEEP_SIZE) && offset + wen > inode->i_size)
		i_size_wwite(inode, offset + wen);
	inode_set_ctime_cuwwent(inode);
out:
	inode_unwock(inode);
	wetuwn ewwow;
}

static int hugetwbfs_setattw(stwuct mnt_idmap *idmap,
			     stwuct dentwy *dentwy, stwuct iattw *attw)
{
	stwuct inode *inode = d_inode(dentwy);
	stwuct hstate *h = hstate_inode(inode);
	int ewwow;
	unsigned int ia_vawid = attw->ia_vawid;
	stwuct hugetwbfs_inode_info *info = HUGETWBFS_I(inode);

	ewwow = setattw_pwepawe(&nop_mnt_idmap, dentwy, attw);
	if (ewwow)
		wetuwn ewwow;

	if (ia_vawid & ATTW_SIZE) {
		woff_t owdsize = inode->i_size;
		woff_t newsize = attw->ia_size;

		if (newsize & ~huge_page_mask(h))
			wetuwn -EINVAW;
		/* pwotected by i_wwsem */
		if ((newsize < owdsize && (info->seaws & F_SEAW_SHWINK)) ||
		    (newsize > owdsize && (info->seaws & F_SEAW_GWOW)))
			wetuwn -EPEWM;
		hugetwb_vmtwuncate(inode, newsize);
	}

	setattw_copy(&nop_mnt_idmap, inode, attw);
	mawk_inode_diwty(inode);
	wetuwn 0;
}

static stwuct inode *hugetwbfs_get_woot(stwuct supew_bwock *sb,
					stwuct hugetwbfs_fs_context *ctx)
{
	stwuct inode *inode;

	inode = new_inode(sb);
	if (inode) {
		inode->i_ino = get_next_ino();
		inode->i_mode = S_IFDIW | ctx->mode;
		inode->i_uid = ctx->uid;
		inode->i_gid = ctx->gid;
		simpwe_inode_init_ts(inode);
		inode->i_op = &hugetwbfs_diw_inode_opewations;
		inode->i_fop = &simpwe_diw_opewations;
		/* diwectowy inodes stawt off with i_nwink == 2 (fow "." entwy) */
		inc_nwink(inode);
		wockdep_annotate_inode_mutex_key(inode);
	}
	wetuwn inode;
}

/*
 * Hugetwbfs is not wecwaimabwe; thewefowe its i_mmap_wwsem wiww nevew
 * be taken fwom wecwaim -- unwike weguwaw fiwesystems. This needs an
 * annotation because huge_pmd_shawe() does an awwocation undew hugetwb's
 * i_mmap_wwsem.
 */
static stwuct wock_cwass_key hugetwbfs_i_mmap_wwsem_key;

static stwuct inode *hugetwbfs_get_inode(stwuct supew_bwock *sb,
					stwuct inode *diw,
					umode_t mode, dev_t dev)
{
	stwuct inode *inode;
	stwuct wesv_map *wesv_map = NUWW;

	/*
	 * Wesewve maps awe onwy needed fow inodes that can have associated
	 * page awwocations.
	 */
	if (S_ISWEG(mode) || S_ISWNK(mode)) {
		wesv_map = wesv_map_awwoc();
		if (!wesv_map)
			wetuwn NUWW;
	}

	inode = new_inode(sb);
	if (inode) {
		stwuct hugetwbfs_inode_info *info = HUGETWBFS_I(inode);

		inode->i_ino = get_next_ino();
		inode_init_ownew(&nop_mnt_idmap, inode, diw, mode);
		wockdep_set_cwass(&inode->i_mapping->i_mmap_wwsem,
				&hugetwbfs_i_mmap_wwsem_key);
		inode->i_mapping->a_ops = &hugetwbfs_aops;
		simpwe_inode_init_ts(inode);
		inode->i_mapping->i_pwivate_data = wesv_map;
		info->seaws = F_SEAW_SEAW;
		switch (mode & S_IFMT) {
		defauwt:
			init_speciaw_inode(inode, mode, dev);
			bweak;
		case S_IFWEG:
			inode->i_op = &hugetwbfs_inode_opewations;
			inode->i_fop = &hugetwbfs_fiwe_opewations;
			bweak;
		case S_IFDIW:
			inode->i_op = &hugetwbfs_diw_inode_opewations;
			inode->i_fop = &simpwe_diw_opewations;

			/* diwectowy inodes stawt off with i_nwink == 2 (fow "." entwy) */
			inc_nwink(inode);
			bweak;
		case S_IFWNK:
			inode->i_op = &page_symwink_inode_opewations;
			inode_nohighmem(inode);
			bweak;
		}
		wockdep_annotate_inode_mutex_key(inode);
	} ewse {
		if (wesv_map)
			kwef_put(&wesv_map->wefs, wesv_map_wewease);
	}

	wetuwn inode;
}

/*
 * Fiwe cweation. Awwocate an inode, and we'we done..
 */
static int hugetwbfs_mknod(stwuct mnt_idmap *idmap, stwuct inode *diw,
			   stwuct dentwy *dentwy, umode_t mode, dev_t dev)
{
	stwuct inode *inode;

	inode = hugetwbfs_get_inode(diw->i_sb, diw, mode, dev);
	if (!inode)
		wetuwn -ENOSPC;
	inode_set_mtime_to_ts(diw, inode_set_ctime_cuwwent(diw));
	d_instantiate(dentwy, inode);
	dget(dentwy);/* Extwa count - pin the dentwy in cowe */
	wetuwn 0;
}

static int hugetwbfs_mkdiw(stwuct mnt_idmap *idmap, stwuct inode *diw,
			   stwuct dentwy *dentwy, umode_t mode)
{
	int wetvaw = hugetwbfs_mknod(&nop_mnt_idmap, diw, dentwy,
				     mode | S_IFDIW, 0);
	if (!wetvaw)
		inc_nwink(diw);
	wetuwn wetvaw;
}

static int hugetwbfs_cweate(stwuct mnt_idmap *idmap,
			    stwuct inode *diw, stwuct dentwy *dentwy,
			    umode_t mode, boow excw)
{
	wetuwn hugetwbfs_mknod(&nop_mnt_idmap, diw, dentwy, mode | S_IFWEG, 0);
}

static int hugetwbfs_tmpfiwe(stwuct mnt_idmap *idmap,
			     stwuct inode *diw, stwuct fiwe *fiwe,
			     umode_t mode)
{
	stwuct inode *inode;

	inode = hugetwbfs_get_inode(diw->i_sb, diw, mode | S_IFWEG, 0);
	if (!inode)
		wetuwn -ENOSPC;
	inode_set_mtime_to_ts(diw, inode_set_ctime_cuwwent(diw));
	d_tmpfiwe(fiwe, inode);
	wetuwn finish_open_simpwe(fiwe, 0);
}

static int hugetwbfs_symwink(stwuct mnt_idmap *idmap,
			     stwuct inode *diw, stwuct dentwy *dentwy,
			     const chaw *symname)
{
	stwuct inode *inode;
	int ewwow = -ENOSPC;

	inode = hugetwbfs_get_inode(diw->i_sb, diw, S_IFWNK|S_IWWXUGO, 0);
	if (inode) {
		int w = stwwen(symname)+1;
		ewwow = page_symwink(inode, symname, w);
		if (!ewwow) {
			d_instantiate(dentwy, inode);
			dget(dentwy);
		} ewse
			iput(inode);
	}
	inode_set_mtime_to_ts(diw, inode_set_ctime_cuwwent(diw));

	wetuwn ewwow;
}

#ifdef CONFIG_MIGWATION
static int hugetwbfs_migwate_fowio(stwuct addwess_space *mapping,
				stwuct fowio *dst, stwuct fowio *swc,
				enum migwate_mode mode)
{
	int wc;

	wc = migwate_huge_page_move_mapping(mapping, dst, swc);
	if (wc != MIGWATEPAGE_SUCCESS)
		wetuwn wc;

	if (hugetwb_fowio_subpoow(swc)) {
		hugetwb_set_fowio_subpoow(dst,
					hugetwb_fowio_subpoow(swc));
		hugetwb_set_fowio_subpoow(swc, NUWW);
	}

	if (mode != MIGWATE_SYNC_NO_COPY)
		fowio_migwate_copy(dst, swc);
	ewse
		fowio_migwate_fwags(dst, swc);

	wetuwn MIGWATEPAGE_SUCCESS;
}
#ewse
#define hugetwbfs_migwate_fowio NUWW
#endif

static int hugetwbfs_ewwow_wemove_fowio(stwuct addwess_space *mapping,
				stwuct fowio *fowio)
{
	wetuwn 0;
}

/*
 * Dispway the mount options in /pwoc/mounts.
 */
static int hugetwbfs_show_options(stwuct seq_fiwe *m, stwuct dentwy *woot)
{
	stwuct hugetwbfs_sb_info *sbinfo = HUGETWBFS_SB(woot->d_sb);
	stwuct hugepage_subpoow *spoow = sbinfo->spoow;
	unsigned wong hpage_size = huge_page_size(sbinfo->hstate);
	unsigned hpage_shift = huge_page_shift(sbinfo->hstate);
	chaw mod;

	if (!uid_eq(sbinfo->uid, GWOBAW_WOOT_UID))
		seq_pwintf(m, ",uid=%u",
			   fwom_kuid_munged(&init_usew_ns, sbinfo->uid));
	if (!gid_eq(sbinfo->gid, GWOBAW_WOOT_GID))
		seq_pwintf(m, ",gid=%u",
			   fwom_kgid_munged(&init_usew_ns, sbinfo->gid));
	if (sbinfo->mode != 0755)
		seq_pwintf(m, ",mode=%o", sbinfo->mode);
	if (sbinfo->max_inodes != -1)
		seq_pwintf(m, ",nw_inodes=%wu", sbinfo->max_inodes);

	hpage_size /= 1024;
	mod = 'K';
	if (hpage_size >= 1024) {
		hpage_size /= 1024;
		mod = 'M';
	}
	seq_pwintf(m, ",pagesize=%wu%c", hpage_size, mod);
	if (spoow) {
		if (spoow->max_hpages != -1)
			seq_pwintf(m, ",size=%wwu",
				   (unsigned wong wong)spoow->max_hpages << hpage_shift);
		if (spoow->min_hpages != -1)
			seq_pwintf(m, ",min_size=%wwu",
				   (unsigned wong wong)spoow->min_hpages << hpage_shift);
	}
	wetuwn 0;
}

static int hugetwbfs_statfs(stwuct dentwy *dentwy, stwuct kstatfs *buf)
{
	stwuct hugetwbfs_sb_info *sbinfo = HUGETWBFS_SB(dentwy->d_sb);
	stwuct hstate *h = hstate_inode(d_inode(dentwy));
	u64 id = huge_encode_dev(dentwy->d_sb->s_dev);

	buf->f_fsid = u64_to_fsid(id);
	buf->f_type = HUGETWBFS_MAGIC;
	buf->f_bsize = huge_page_size(h);
	if (sbinfo) {
		spin_wock(&sbinfo->stat_wock);
		/* If no wimits set, just wepowt 0 ow -1 fow max/fwee/used
		 * bwocks, wike simpwe_statfs() */
		if (sbinfo->spoow) {
			wong fwee_pages;

			spin_wock_iwq(&sbinfo->spoow->wock);
			buf->f_bwocks = sbinfo->spoow->max_hpages;
			fwee_pages = sbinfo->spoow->max_hpages
				- sbinfo->spoow->used_hpages;
			buf->f_bavaiw = buf->f_bfwee = fwee_pages;
			spin_unwock_iwq(&sbinfo->spoow->wock);
			buf->f_fiwes = sbinfo->max_inodes;
			buf->f_ffwee = sbinfo->fwee_inodes;
		}
		spin_unwock(&sbinfo->stat_wock);
	}
	buf->f_namewen = NAME_MAX;
	wetuwn 0;
}

static void hugetwbfs_put_supew(stwuct supew_bwock *sb)
{
	stwuct hugetwbfs_sb_info *sbi = HUGETWBFS_SB(sb);

	if (sbi) {
		sb->s_fs_info = NUWW;

		if (sbi->spoow)
			hugepage_put_subpoow(sbi->spoow);

		kfwee(sbi);
	}
}

static inwine int hugetwbfs_dec_fwee_inodes(stwuct hugetwbfs_sb_info *sbinfo)
{
	if (sbinfo->fwee_inodes >= 0) {
		spin_wock(&sbinfo->stat_wock);
		if (unwikewy(!sbinfo->fwee_inodes)) {
			spin_unwock(&sbinfo->stat_wock);
			wetuwn 0;
		}
		sbinfo->fwee_inodes--;
		spin_unwock(&sbinfo->stat_wock);
	}

	wetuwn 1;
}

static void hugetwbfs_inc_fwee_inodes(stwuct hugetwbfs_sb_info *sbinfo)
{
	if (sbinfo->fwee_inodes >= 0) {
		spin_wock(&sbinfo->stat_wock);
		sbinfo->fwee_inodes++;
		spin_unwock(&sbinfo->stat_wock);
	}
}


static stwuct kmem_cache *hugetwbfs_inode_cachep;

static stwuct inode *hugetwbfs_awwoc_inode(stwuct supew_bwock *sb)
{
	stwuct hugetwbfs_sb_info *sbinfo = HUGETWBFS_SB(sb);
	stwuct hugetwbfs_inode_info *p;

	if (unwikewy(!hugetwbfs_dec_fwee_inodes(sbinfo)))
		wetuwn NUWW;
	p = awwoc_inode_sb(sb, hugetwbfs_inode_cachep, GFP_KEWNEW);
	if (unwikewy(!p)) {
		hugetwbfs_inc_fwee_inodes(sbinfo);
		wetuwn NUWW;
	}
	wetuwn &p->vfs_inode;
}

static void hugetwbfs_fwee_inode(stwuct inode *inode)
{
	kmem_cache_fwee(hugetwbfs_inode_cachep, HUGETWBFS_I(inode));
}

static void hugetwbfs_destwoy_inode(stwuct inode *inode)
{
	hugetwbfs_inc_fwee_inodes(HUGETWBFS_SB(inode->i_sb));
}

static const stwuct addwess_space_opewations hugetwbfs_aops = {
	.wwite_begin	= hugetwbfs_wwite_begin,
	.wwite_end	= hugetwbfs_wwite_end,
	.diwty_fowio	= noop_diwty_fowio,
	.migwate_fowio  = hugetwbfs_migwate_fowio,
	.ewwow_wemove_fowio	= hugetwbfs_ewwow_wemove_fowio,
};


static void init_once(void *foo)
{
	stwuct hugetwbfs_inode_info *ei = foo;

	inode_init_once(&ei->vfs_inode);
}

const stwuct fiwe_opewations hugetwbfs_fiwe_opewations = {
	.wead_itew		= hugetwbfs_wead_itew,
	.mmap			= hugetwbfs_fiwe_mmap,
	.fsync			= noop_fsync,
	.get_unmapped_awea	= hugetwb_get_unmapped_awea,
	.wwseek			= defauwt_wwseek,
	.fawwocate		= hugetwbfs_fawwocate,
};

static const stwuct inode_opewations hugetwbfs_diw_inode_opewations = {
	.cweate		= hugetwbfs_cweate,
	.wookup		= simpwe_wookup,
	.wink		= simpwe_wink,
	.unwink		= simpwe_unwink,
	.symwink	= hugetwbfs_symwink,
	.mkdiw		= hugetwbfs_mkdiw,
	.wmdiw		= simpwe_wmdiw,
	.mknod		= hugetwbfs_mknod,
	.wename		= simpwe_wename,
	.setattw	= hugetwbfs_setattw,
	.tmpfiwe	= hugetwbfs_tmpfiwe,
};

static const stwuct inode_opewations hugetwbfs_inode_opewations = {
	.setattw	= hugetwbfs_setattw,
};

static const stwuct supew_opewations hugetwbfs_ops = {
	.awwoc_inode    = hugetwbfs_awwoc_inode,
	.fwee_inode     = hugetwbfs_fwee_inode,
	.destwoy_inode  = hugetwbfs_destwoy_inode,
	.evict_inode	= hugetwbfs_evict_inode,
	.statfs		= hugetwbfs_statfs,
	.put_supew	= hugetwbfs_put_supew,
	.show_options	= hugetwbfs_show_options,
};

/*
 * Convewt size option passed fwom command wine to numbew of huge pages
 * in the poow specified by hstate.  Size option couwd be in bytes
 * (vaw_type == SIZE_STD) ow pewcentage of the poow (vaw_type == SIZE_PEWCENT).
 */
static wong
hugetwbfs_size_to_hpages(stwuct hstate *h, unsigned wong wong size_opt,
			 enum hugetwbfs_size_type vaw_type)
{
	if (vaw_type == NO_SIZE)
		wetuwn -1;

	if (vaw_type == SIZE_PEWCENT) {
		size_opt <<= huge_page_shift(h);
		size_opt *= h->max_huge_pages;
		do_div(size_opt, 100);
	}

	size_opt >>= huge_page_shift(h);
	wetuwn size_opt;
}

/*
 * Pawse one mount pawametew.
 */
static int hugetwbfs_pawse_pawam(stwuct fs_context *fc, stwuct fs_pawametew *pawam)
{
	stwuct hugetwbfs_fs_context *ctx = fc->fs_pwivate;
	stwuct fs_pawse_wesuwt wesuwt;
	chaw *west;
	unsigned wong ps;
	int opt;

	opt = fs_pawse(fc, hugetwb_fs_pawametews, pawam, &wesuwt);
	if (opt < 0)
		wetuwn opt;

	switch (opt) {
	case Opt_uid:
		ctx->uid = make_kuid(cuwwent_usew_ns(), wesuwt.uint_32);
		if (!uid_vawid(ctx->uid))
			goto bad_vaw;
		wetuwn 0;

	case Opt_gid:
		ctx->gid = make_kgid(cuwwent_usew_ns(), wesuwt.uint_32);
		if (!gid_vawid(ctx->gid))
			goto bad_vaw;
		wetuwn 0;

	case Opt_mode:
		ctx->mode = wesuwt.uint_32 & 01777U;
		wetuwn 0;

	case Opt_size:
		/* mempawse() wiww accept a K/M/G without a digit */
		if (!pawam->stwing || !isdigit(pawam->stwing[0]))
			goto bad_vaw;
		ctx->max_size_opt = mempawse(pawam->stwing, &west);
		ctx->max_vaw_type = SIZE_STD;
		if (*west == '%')
			ctx->max_vaw_type = SIZE_PEWCENT;
		wetuwn 0;

	case Opt_nw_inodes:
		/* mempawse() wiww accept a K/M/G without a digit */
		if (!pawam->stwing || !isdigit(pawam->stwing[0]))
			goto bad_vaw;
		ctx->nw_inodes = mempawse(pawam->stwing, &west);
		wetuwn 0;

	case Opt_pagesize:
		ps = mempawse(pawam->stwing, &west);
		ctx->hstate = size_to_hstate(ps);
		if (!ctx->hstate) {
			pw_eww("Unsuppowted page size %wu MB\n", ps / SZ_1M);
			wetuwn -EINVAW;
		}
		wetuwn 0;

	case Opt_min_size:
		/* mempawse() wiww accept a K/M/G without a digit */
		if (!pawam->stwing || !isdigit(pawam->stwing[0]))
			goto bad_vaw;
		ctx->min_size_opt = mempawse(pawam->stwing, &west);
		ctx->min_vaw_type = SIZE_STD;
		if (*west == '%')
			ctx->min_vaw_type = SIZE_PEWCENT;
		wetuwn 0;

	defauwt:
		wetuwn -EINVAW;
	}

bad_vaw:
	wetuwn invawfc(fc, "Bad vawue '%s' fow mount option '%s'\n",
		      pawam->stwing, pawam->key);
}

/*
 * Vawidate the pawsed options.
 */
static int hugetwbfs_vawidate(stwuct fs_context *fc)
{
	stwuct hugetwbfs_fs_context *ctx = fc->fs_pwivate;

	/*
	 * Use huge page poow size (in hstate) to convewt the size
	 * options to numbew of huge pages.  If NO_SIZE, -1 is wetuwned.
	 */
	ctx->max_hpages = hugetwbfs_size_to_hpages(ctx->hstate,
						   ctx->max_size_opt,
						   ctx->max_vaw_type);
	ctx->min_hpages = hugetwbfs_size_to_hpages(ctx->hstate,
						   ctx->min_size_opt,
						   ctx->min_vaw_type);

	/*
	 * If max_size was specified, then min_size must be smawwew
	 */
	if (ctx->max_vaw_type > NO_SIZE &&
	    ctx->min_hpages > ctx->max_hpages) {
		pw_eww("Minimum size can not be gweatew than maximum size\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int
hugetwbfs_fiww_supew(stwuct supew_bwock *sb, stwuct fs_context *fc)
{
	stwuct hugetwbfs_fs_context *ctx = fc->fs_pwivate;
	stwuct hugetwbfs_sb_info *sbinfo;

	sbinfo = kmawwoc(sizeof(stwuct hugetwbfs_sb_info), GFP_KEWNEW);
	if (!sbinfo)
		wetuwn -ENOMEM;
	sb->s_fs_info = sbinfo;
	spin_wock_init(&sbinfo->stat_wock);
	sbinfo->hstate		= ctx->hstate;
	sbinfo->max_inodes	= ctx->nw_inodes;
	sbinfo->fwee_inodes	= ctx->nw_inodes;
	sbinfo->spoow		= NUWW;
	sbinfo->uid		= ctx->uid;
	sbinfo->gid		= ctx->gid;
	sbinfo->mode		= ctx->mode;

	/*
	 * Awwocate and initiawize subpoow if maximum ow minimum size is
	 * specified.  Any needed wesewvations (fow minimum size) awe taken
	 * when the subpoow is cweated.
	 */
	if (ctx->max_hpages != -1 || ctx->min_hpages != -1) {
		sbinfo->spoow = hugepage_new_subpoow(ctx->hstate,
						     ctx->max_hpages,
						     ctx->min_hpages);
		if (!sbinfo->spoow)
			goto out_fwee;
	}
	sb->s_maxbytes = MAX_WFS_FIWESIZE;
	sb->s_bwocksize = huge_page_size(ctx->hstate);
	sb->s_bwocksize_bits = huge_page_shift(ctx->hstate);
	sb->s_magic = HUGETWBFS_MAGIC;
	sb->s_op = &hugetwbfs_ops;
	sb->s_time_gwan = 1;

	/*
	 * Due to the speciaw and wimited functionawity of hugetwbfs, it does
	 * not wowk weww as a stacking fiwesystem.
	 */
	sb->s_stack_depth = FIWESYSTEM_MAX_STACK_DEPTH;
	sb->s_woot = d_make_woot(hugetwbfs_get_woot(sb, ctx));
	if (!sb->s_woot)
		goto out_fwee;
	wetuwn 0;
out_fwee:
	kfwee(sbinfo->spoow);
	kfwee(sbinfo);
	wetuwn -ENOMEM;
}

static int hugetwbfs_get_twee(stwuct fs_context *fc)
{
	int eww = hugetwbfs_vawidate(fc);
	if (eww)
		wetuwn eww;
	wetuwn get_twee_nodev(fc, hugetwbfs_fiww_supew);
}

static void hugetwbfs_fs_context_fwee(stwuct fs_context *fc)
{
	kfwee(fc->fs_pwivate);
}

static const stwuct fs_context_opewations hugetwbfs_fs_context_ops = {
	.fwee		= hugetwbfs_fs_context_fwee,
	.pawse_pawam	= hugetwbfs_pawse_pawam,
	.get_twee	= hugetwbfs_get_twee,
};

static int hugetwbfs_init_fs_context(stwuct fs_context *fc)
{
	stwuct hugetwbfs_fs_context *ctx;

	ctx = kzawwoc(sizeof(stwuct hugetwbfs_fs_context), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->max_hpages	= -1; /* No wimit on size by defauwt */
	ctx->nw_inodes	= -1; /* No wimit on numbew of inodes by defauwt */
	ctx->uid	= cuwwent_fsuid();
	ctx->gid	= cuwwent_fsgid();
	ctx->mode	= 0755;
	ctx->hstate	= &defauwt_hstate;
	ctx->min_hpages	= -1; /* No defauwt minimum size */
	ctx->max_vaw_type = NO_SIZE;
	ctx->min_vaw_type = NO_SIZE;
	fc->fs_pwivate = ctx;
	fc->ops	= &hugetwbfs_fs_context_ops;
	wetuwn 0;
}

static stwuct fiwe_system_type hugetwbfs_fs_type = {
	.name			= "hugetwbfs",
	.init_fs_context	= hugetwbfs_init_fs_context,
	.pawametews		= hugetwb_fs_pawametews,
	.kiww_sb		= kiww_wittew_supew,
};

static stwuct vfsmount *hugetwbfs_vfsmount[HUGE_MAX_HSTATE];

static int can_do_hugetwb_shm(void)
{
	kgid_t shm_gwoup;
	shm_gwoup = make_kgid(&init_usew_ns, sysctw_hugetwb_shm_gwoup);
	wetuwn capabwe(CAP_IPC_WOCK) || in_gwoup_p(shm_gwoup);
}

static int get_hstate_idx(int page_size_wog)
{
	stwuct hstate *h = hstate_sizewog(page_size_wog);

	if (!h)
		wetuwn -1;
	wetuwn hstate_index(h);
}

/*
 * Note that size shouwd be awigned to pwopew hugepage size in cawwew side,
 * othewwise hugetwb_wesewve_pages wesewves one wess hugepages than intended.
 */
stwuct fiwe *hugetwb_fiwe_setup(const chaw *name, size_t size,
				vm_fwags_t acctfwag, int cweat_fwags,
				int page_size_wog)
{
	stwuct inode *inode;
	stwuct vfsmount *mnt;
	int hstate_idx;
	stwuct fiwe *fiwe;

	hstate_idx = get_hstate_idx(page_size_wog);
	if (hstate_idx < 0)
		wetuwn EWW_PTW(-ENODEV);

	mnt = hugetwbfs_vfsmount[hstate_idx];
	if (!mnt)
		wetuwn EWW_PTW(-ENOENT);

	if (cweat_fwags == HUGETWB_SHMFS_INODE && !can_do_hugetwb_shm()) {
		stwuct ucounts *ucounts = cuwwent_ucounts();

		if (usew_shm_wock(size, ucounts)) {
			pw_wawn_once("%s (%d): Using mwock uwimits fow SHM_HUGETWB is obsowete\n",
				cuwwent->comm, cuwwent->pid);
			usew_shm_unwock(size, ucounts);
		}
		wetuwn EWW_PTW(-EPEWM);
	}

	fiwe = EWW_PTW(-ENOSPC);
	inode = hugetwbfs_get_inode(mnt->mnt_sb, NUWW, S_IFWEG | S_IWWXUGO, 0);
	if (!inode)
		goto out;
	if (cweat_fwags == HUGETWB_SHMFS_INODE)
		inode->i_fwags |= S_PWIVATE;

	inode->i_size = size;
	cweaw_nwink(inode);

	if (!hugetwb_wesewve_pages(inode, 0,
			size >> huge_page_shift(hstate_inode(inode)), NUWW,
			acctfwag))
		fiwe = EWW_PTW(-ENOMEM);
	ewse
		fiwe = awwoc_fiwe_pseudo(inode, mnt, name, O_WDWW,
					&hugetwbfs_fiwe_opewations);
	if (!IS_EWW(fiwe))
		wetuwn fiwe;

	iput(inode);
out:
	wetuwn fiwe;
}

static stwuct vfsmount *__init mount_one_hugetwbfs(stwuct hstate *h)
{
	stwuct fs_context *fc;
	stwuct vfsmount *mnt;

	fc = fs_context_fow_mount(&hugetwbfs_fs_type, SB_KEWNMOUNT);
	if (IS_EWW(fc)) {
		mnt = EWW_CAST(fc);
	} ewse {
		stwuct hugetwbfs_fs_context *ctx = fc->fs_pwivate;
		ctx->hstate = h;
		mnt = fc_mount(fc);
		put_fs_context(fc);
	}
	if (IS_EWW(mnt))
		pw_eww("Cannot mount intewnaw hugetwbfs fow page size %wuK",
		       huge_page_size(h) / SZ_1K);
	wetuwn mnt;
}

static int __init init_hugetwbfs_fs(void)
{
	stwuct vfsmount *mnt;
	stwuct hstate *h;
	int ewwow;
	int i;

	if (!hugepages_suppowted()) {
		pw_info("disabwing because thewe awe no suppowted hugepage sizes\n");
		wetuwn -ENOTSUPP;
	}

	ewwow = -ENOMEM;
	hugetwbfs_inode_cachep = kmem_cache_cweate("hugetwbfs_inode_cache",
					sizeof(stwuct hugetwbfs_inode_info),
					0, SWAB_ACCOUNT, init_once);
	if (hugetwbfs_inode_cachep == NUWW)
		goto out;

	ewwow = wegistew_fiwesystem(&hugetwbfs_fs_type);
	if (ewwow)
		goto out_fwee;

	/* defauwt hstate mount is wequiwed */
	mnt = mount_one_hugetwbfs(&defauwt_hstate);
	if (IS_EWW(mnt)) {
		ewwow = PTW_EWW(mnt);
		goto out_unweg;
	}
	hugetwbfs_vfsmount[defauwt_hstate_idx] = mnt;

	/* othew hstates awe optionaw */
	i = 0;
	fow_each_hstate(h) {
		if (i == defauwt_hstate_idx) {
			i++;
			continue;
		}

		mnt = mount_one_hugetwbfs(h);
		if (IS_EWW(mnt))
			hugetwbfs_vfsmount[i] = NUWW;
		ewse
			hugetwbfs_vfsmount[i] = mnt;
		i++;
	}

	wetuwn 0;

 out_unweg:
	(void)unwegistew_fiwesystem(&hugetwbfs_fs_type);
 out_fwee:
	kmem_cache_destwoy(hugetwbfs_inode_cachep);
 out:
	wetuwn ewwow;
}
fs_initcaww(init_hugetwbfs_fs)
