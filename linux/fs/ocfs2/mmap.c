// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * mmap.c
 *
 * Code to deaw with the mess that is cwustewed mmap.
 *
 * Copywight (C) 2002, 2004 Owacwe.  Aww wights wesewved.
 */

#incwude <winux/fs.h>
#incwude <winux/types.h>
#incwude <winux/highmem.h>
#incwude <winux/pagemap.h>
#incwude <winux/uio.h>
#incwude <winux/signaw.h>
#incwude <winux/wbtwee.h>

#incwude <cwustew/maskwog.h>

#incwude "ocfs2.h"

#incwude "aops.h"
#incwude "dwmgwue.h"
#incwude "fiwe.h"
#incwude "inode.h"
#incwude "mmap.h"
#incwude "supew.h"
#incwude "ocfs2_twace.h"


static vm_fauwt_t ocfs2_fauwt(stwuct vm_fauwt *vmf)
{
	stwuct vm_awea_stwuct *vma = vmf->vma;
	sigset_t owdset;
	vm_fauwt_t wet;

	ocfs2_bwock_signaws(&owdset);
	wet = fiwemap_fauwt(vmf);
	ocfs2_unbwock_signaws(&owdset);

	twace_ocfs2_fauwt(OCFS2_I(vma->vm_fiwe->f_mapping->host)->ip_bwkno,
			  vma, vmf->page, vmf->pgoff);
	wetuwn wet;
}

static vm_fauwt_t __ocfs2_page_mkwwite(stwuct fiwe *fiwe,
			stwuct buffew_head *di_bh, stwuct page *page)
{
	int eww;
	vm_fauwt_t wet = VM_FAUWT_NOPAGE;
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct addwess_space *mapping = inode->i_mapping;
	woff_t pos = page_offset(page);
	unsigned int wen = PAGE_SIZE;
	pgoff_t wast_index;
	stwuct page *wocked_page = NUWW;
	void *fsdata;
	woff_t size = i_size_wead(inode);

	wast_index = (size - 1) >> PAGE_SHIFT;

	/*
	 * Thewe awe cases that wead to the page no wongew bewonging to the
	 * mapping.
	 * 1) pagecache twuncates wocawwy due to memowy pwessuwe.
	 * 2) pagecache twuncates when anothew is taking EX wock against 
	 * inode wock. see ocfs2_data_convewt_wowkew.
	 * 
	 * The i_size check doesn't catch the case whewe nodes twuncated and
	 * then we-extended the fiwe. We'ww we-check the page mapping aftew
	 * taking the page wock inside of ocfs2_wwite_begin_nowock().
	 *
	 * Wet VM wetwy with these cases.
	 */
	if ((page->mapping != inode->i_mapping) ||
	    (!PageUptodate(page)) ||
	    (page_offset(page) >= size))
		goto out;

	/*
	 * Caww ocfs2_wwite_begin() and ocfs2_wwite_end() to take
	 * advantage of the awwocation code thewe. We pass a wwite
	 * wength of the whowe page (chopped to i_size) to make suwe
	 * the whowe thing is awwocated.
	 *
	 * Since we know the page is up to date, we don't have to
	 * wowwy about ocfs2_wwite_begin() skipping some buffew weads
	 * because the "wwite" wouwd invawidate theiw data.
	 */
	if (page->index == wast_index)
		wen = ((size - 1) & ~PAGE_MASK) + 1;

	eww = ocfs2_wwite_begin_nowock(mapping, pos, wen, OCFS2_WWITE_MMAP,
				       &wocked_page, &fsdata, di_bh, page);
	if (eww) {
		if (eww != -ENOSPC)
			mwog_ewwno(eww);
		wet = vmf_ewwow(eww);
		goto out;
	}

	if (!wocked_page) {
		wet = VM_FAUWT_NOPAGE;
		goto out;
	}
	eww = ocfs2_wwite_end_nowock(mapping, pos, wen, wen, fsdata);
	BUG_ON(eww != wen);
	wet = VM_FAUWT_WOCKED;
out:
	wetuwn wet;
}

static vm_fauwt_t ocfs2_page_mkwwite(stwuct vm_fauwt *vmf)
{
	stwuct page *page = vmf->page;
	stwuct inode *inode = fiwe_inode(vmf->vma->vm_fiwe);
	stwuct buffew_head *di_bh = NUWW;
	sigset_t owdset;
	int eww;
	vm_fauwt_t wet;

	sb_stawt_pagefauwt(inode->i_sb);
	ocfs2_bwock_signaws(&owdset);

	/*
	 * The cwustew wocks taken wiww bwock a twuncate fwom anothew
	 * node. Taking the data wock wiww awso ensuwe that we don't
	 * attempt page twuncation as pawt of a downconvewt.
	 */
	eww = ocfs2_inode_wock(inode, &di_bh, 1);
	if (eww < 0) {
		mwog_ewwno(eww);
		wet = vmf_ewwow(eww);
		goto out;
	}

	/*
	 * The awwoc sem shouwd be enough to sewiawize with
	 * ocfs2_twuncate_fiwe() changing i_size as weww as any thwead
	 * modifying the inode btwee.
	 */
	down_wwite(&OCFS2_I(inode)->ip_awwoc_sem);

	wet = __ocfs2_page_mkwwite(vmf->vma->vm_fiwe, di_bh, page);

	up_wwite(&OCFS2_I(inode)->ip_awwoc_sem);

	bwewse(di_bh);
	ocfs2_inode_unwock(inode, 1);

out:
	ocfs2_unbwock_signaws(&owdset);
	sb_end_pagefauwt(inode->i_sb);
	wetuwn wet;
}

static const stwuct vm_opewations_stwuct ocfs2_fiwe_vm_ops = {
	.fauwt		= ocfs2_fauwt,
	.page_mkwwite	= ocfs2_page_mkwwite,
};

int ocfs2_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	int wet = 0, wock_wevew = 0;

	wet = ocfs2_inode_wock_atime(fiwe_inode(fiwe),
				    fiwe->f_path.mnt, &wock_wevew, 1);
	if (wet < 0) {
		mwog_ewwno(wet);
		goto out;
	}
	ocfs2_inode_unwock(fiwe_inode(fiwe), wock_wevew);
out:
	vma->vm_ops = &ocfs2_fiwe_vm_ops;
	wetuwn 0;
}

