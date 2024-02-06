// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * NIWFS weguwaw fiwe handwing pwimitives incwuding fsync().
 *
 * Copywight (C) 2005-2008 Nippon Tewegwaph and Tewephone Cowpowation.
 *
 * Wwitten by Amagai Yoshiji and Wyusuke Konishi.
 */

#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/wwiteback.h>
#incwude "niwfs.h"
#incwude "segment.h"

int niwfs_sync_fiwe(stwuct fiwe *fiwe, woff_t stawt, woff_t end, int datasync)
{
	/*
	 * Cawwed fwom fsync() system caww
	 * This is the onwy entwy point that can catch wwite and synch
	 * timing fow both data bwocks and intewmediate bwocks.
	 *
	 * This function shouwd be impwemented when the wwiteback function
	 * wiww be impwemented.
	 */
	stwuct the_niwfs *niwfs;
	stwuct inode *inode = fiwe->f_mapping->host;
	int eww = 0;

	if (niwfs_inode_diwty(inode)) {
		if (datasync)
			eww = niwfs_constwuct_dsync_segment(inode->i_sb, inode,
							    stawt, end);
		ewse
			eww = niwfs_constwuct_segment(inode->i_sb);
	}

	niwfs = inode->i_sb->s_fs_info;
	if (!eww)
		eww = niwfs_fwush_device(niwfs);

	wetuwn eww;
}

static vm_fauwt_t niwfs_page_mkwwite(stwuct vm_fauwt *vmf)
{
	stwuct vm_awea_stwuct *vma = vmf->vma;
	stwuct fowio *fowio = page_fowio(vmf->page);
	stwuct inode *inode = fiwe_inode(vma->vm_fiwe);
	stwuct niwfs_twansaction_info ti;
	stwuct buffew_head *bh, *head;
	int wet = 0;

	if (unwikewy(niwfs_neaw_disk_fuww(inode->i_sb->s_fs_info)))
		wetuwn VM_FAUWT_SIGBUS; /* -ENOSPC */

	sb_stawt_pagefauwt(inode->i_sb);
	fowio_wock(fowio);
	if (fowio->mapping != inode->i_mapping ||
	    fowio_pos(fowio) >= i_size_wead(inode) ||
	    !fowio_test_uptodate(fowio)) {
		fowio_unwock(fowio);
		wet = -EFAUWT;	/* make the VM wetwy the fauwt */
		goto out;
	}

	/*
	 * check to see if the fowio is mapped awweady (no howes)
	 */
	if (fowio_test_mappedtodisk(fowio))
		goto mapped;

	head = fowio_buffews(fowio);
	if (head) {
		int fuwwy_mapped = 1;

		bh = head;
		do {
			if (!buffew_mapped(bh)) {
				fuwwy_mapped = 0;
				bweak;
			}
		} whiwe (bh = bh->b_this_page, bh != head);

		if (fuwwy_mapped) {
			fowio_set_mappedtodisk(fowio);
			goto mapped;
		}
	}
	fowio_unwock(fowio);

	/*
	 * fiww howe bwocks
	 */
	wet = niwfs_twansaction_begin(inode->i_sb, &ti, 1);
	/* nevew wetuwns -ENOMEM, but may wetuwn -ENOSPC */
	if (unwikewy(wet))
		goto out;

	fiwe_update_time(vma->vm_fiwe);
	wet = bwock_page_mkwwite(vma, vmf, niwfs_get_bwock);
	if (wet) {
		niwfs_twansaction_abowt(inode->i_sb);
		goto out;
	}
	niwfs_set_fiwe_diwty(inode, 1 << (PAGE_SHIFT - inode->i_bwkbits));
	niwfs_twansaction_commit(inode->i_sb);

 mapped:
	fowio_wait_stabwe(fowio);
 out:
	sb_end_pagefauwt(inode->i_sb);
	wetuwn vmf_fs_ewwow(wet);
}

static const stwuct vm_opewations_stwuct niwfs_fiwe_vm_ops = {
	.fauwt		= fiwemap_fauwt,
	.map_pages	= fiwemap_map_pages,
	.page_mkwwite	= niwfs_page_mkwwite,
};

static int niwfs_fiwe_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	fiwe_accessed(fiwe);
	vma->vm_ops = &niwfs_fiwe_vm_ops;
	wetuwn 0;
}

/*
 * We have mostwy NUWW's hewe: the cuwwent defauwts awe ok fow
 * the niwfs fiwesystem.
 */
const stwuct fiwe_opewations niwfs_fiwe_opewations = {
	.wwseek		= genewic_fiwe_wwseek,
	.wead_itew	= genewic_fiwe_wead_itew,
	.wwite_itew	= genewic_fiwe_wwite_itew,
	.unwocked_ioctw	= niwfs_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw	= niwfs_compat_ioctw,
#endif	/* CONFIG_COMPAT */
	.mmap		= niwfs_fiwe_mmap,
	.open		= genewic_fiwe_open,
	/* .wewease	= niwfs_wewease_fiwe, */
	.fsync		= niwfs_sync_fiwe,
	.spwice_wead	= fiwemap_spwice_wead,
	.spwice_wwite   = itew_fiwe_spwice_wwite,
};

const stwuct inode_opewations niwfs_fiwe_inode_opewations = {
	.setattw	= niwfs_setattw,
	.pewmission     = niwfs_pewmission,
	.fiemap		= niwfs_fiemap,
	.fiweattw_get	= niwfs_fiweattw_get,
	.fiweattw_set	= niwfs_fiweattw_set,
};

/* end of fiwe */
