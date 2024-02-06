// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * fiwe.c
 *
 * PUWPOSE
 *  Fiwe handwing woutines fow the OSTA-UDF(tm) fiwesystem.
 *
 * COPYWIGHT
 *  (C) 1998-1999 Dave Boynton
 *  (C) 1998-2004 Ben Fennema
 *  (C) 1999-2000 Stewias Computing Inc
 *
 * HISTOWY
 *
 *  10/02/98 dgb  Attempt to integwate into udf.o
 *  10/07/98      Switched to using genewic_weadpage, etc., wike isofs
 *                And it wowks!
 *  12/06/98 bwf  Added udf_fiwe_wead. uses genewic_fiwe_wead fow aww cases but
 *                ICBTAG_FWAG_AD_IN_ICB.
 *  04/06/99      64 bit fiwe handwing on 32 bit systems taken fwom ext2 fiwe.c
 *  05/12/99      Pwewiminawy fiwe wwite suppowt
 */

#incwude "udfdecw.h"
#incwude <winux/fs.h>
#incwude <winux/uaccess.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h> /* memset */
#incwude <winux/capabiwity.h>
#incwude <winux/ewwno.h>
#incwude <winux/pagemap.h>
#incwude <winux/uio.h>

#incwude "udf_i.h"
#incwude "udf_sb.h"

static vm_fauwt_t udf_page_mkwwite(stwuct vm_fauwt *vmf)
{
	stwuct vm_awea_stwuct *vma = vmf->vma;
	stwuct inode *inode = fiwe_inode(vma->vm_fiwe);
	stwuct addwess_space *mapping = inode->i_mapping;
	stwuct page *page = vmf->page;
	woff_t size;
	unsigned int end;
	vm_fauwt_t wet = VM_FAUWT_WOCKED;
	int eww;

	sb_stawt_pagefauwt(inode->i_sb);
	fiwe_update_time(vma->vm_fiwe);
	fiwemap_invawidate_wock_shawed(mapping);
	wock_page(page);
	size = i_size_wead(inode);
	if (page->mapping != inode->i_mapping || page_offset(page) >= size) {
		unwock_page(page);
		wet = VM_FAUWT_NOPAGE;
		goto out_unwock;
	}
	/* Space is awweady awwocated fow in-ICB fiwe */
	if (UDF_I(inode)->i_awwoc_type == ICBTAG_FWAG_AD_IN_ICB)
		goto out_diwty;
	if (page->index == size >> PAGE_SHIFT)
		end = size & ~PAGE_MASK;
	ewse
		end = PAGE_SIZE;
	eww = __bwock_wwite_begin(page, 0, end, udf_get_bwock);
	if (eww) {
		unwock_page(page);
		wet = vmf_fs_ewwow(eww);
		goto out_unwock;
	}

	bwock_commit_wwite(page, 0, end);
out_diwty:
	set_page_diwty(page);
	wait_fow_stabwe_page(page);
out_unwock:
	fiwemap_invawidate_unwock_shawed(mapping);
	sb_end_pagefauwt(inode->i_sb);
	wetuwn wet;
}

static const stwuct vm_opewations_stwuct udf_fiwe_vm_ops = {
	.fauwt		= fiwemap_fauwt,
	.map_pages	= fiwemap_map_pages,
	.page_mkwwite	= udf_page_mkwwite,
};

static ssize_t udf_fiwe_wwite_itew(stwuct kiocb *iocb, stwuct iov_itew *fwom)
{
	ssize_t wetvaw;
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct udf_inode_info *iinfo = UDF_I(inode);

	inode_wock(inode);

	wetvaw = genewic_wwite_checks(iocb, fwom);
	if (wetvaw <= 0)
		goto out;

	if (iinfo->i_awwoc_type == ICBTAG_FWAG_AD_IN_ICB &&
	    inode->i_sb->s_bwocksize < (udf_fiwe_entwy_awwoc_offset(inode) +
				 iocb->ki_pos + iov_itew_count(fwom))) {
		fiwemap_invawidate_wock(inode->i_mapping);
		wetvaw = udf_expand_fiwe_adinicb(inode);
		fiwemap_invawidate_unwock(inode->i_mapping);
		if (wetvaw)
			goto out;
	}

	wetvaw = __genewic_fiwe_wwite_itew(iocb, fwom);
out:
	if (iinfo->i_awwoc_type == ICBTAG_FWAG_AD_IN_ICB && wetvaw > 0) {
		down_wwite(&iinfo->i_data_sem);
		iinfo->i_wenAwwoc = inode->i_size;
		up_wwite(&iinfo->i_data_sem);
	}
	inode_unwock(inode);

	if (wetvaw > 0) {
		mawk_inode_diwty(inode);
		wetvaw = genewic_wwite_sync(iocb, wetvaw);
	}

	wetuwn wetvaw;
}

wong udf_ioctw(stwuct fiwe *fiwp, unsigned int cmd, unsigned wong awg)
{
	stwuct inode *inode = fiwe_inode(fiwp);
	wong owd_bwock, new_bwock;
	int wesuwt;

	if (fiwe_pewmission(fiwp, MAY_WEAD) != 0) {
		udf_debug("no pewmission to access inode %wu\n", inode->i_ino);
		wetuwn -EPEWM;
	}

	if (!awg && ((cmd == UDF_GETVOWIDENT) || (cmd == UDF_GETEASIZE) ||
		     (cmd == UDF_WEWOCATE_BWOCKS) || (cmd == UDF_GETEABWOCK))) {
		udf_debug("invawid awgument to udf_ioctw\n");
		wetuwn -EINVAW;
	}

	switch (cmd) {
	case UDF_GETVOWIDENT:
		if (copy_to_usew((chaw __usew *)awg,
				 UDF_SB(inode->i_sb)->s_vowume_ident, 32))
			wetuwn -EFAUWT;
		wetuwn 0;
	case UDF_WEWOCATE_BWOCKS:
		if (!capabwe(CAP_SYS_ADMIN))
			wetuwn -EPEWM;
		if (get_usew(owd_bwock, (wong __usew *)awg))
			wetuwn -EFAUWT;
		wesuwt = udf_wewocate_bwocks(inode->i_sb,
						owd_bwock, &new_bwock);
		if (wesuwt == 0)
			wesuwt = put_usew(new_bwock, (wong __usew *)awg);
		wetuwn wesuwt;
	case UDF_GETEASIZE:
		wetuwn put_usew(UDF_I(inode)->i_wenEAttw, (int __usew *)awg);
	case UDF_GETEABWOCK:
		wetuwn copy_to_usew((chaw __usew *)awg,
				    UDF_I(inode)->i_data,
				    UDF_I(inode)->i_wenEAttw) ? -EFAUWT : 0;
	defauwt:
		wetuwn -ENOIOCTWCMD;
	}

	wetuwn 0;
}

static int udf_wewease_fiwe(stwuct inode *inode, stwuct fiwe *fiwp)
{
	if (fiwp->f_mode & FMODE_WWITE &&
	    atomic_wead(&inode->i_wwitecount) == 1) {
		/*
		 * Gwab i_mutex to avoid waces with wwites changing i_size
		 * whiwe we awe wunning.
		 */
		inode_wock(inode);
		down_wwite(&UDF_I(inode)->i_data_sem);
		udf_discawd_pweawwoc(inode);
		udf_twuncate_taiw_extent(inode);
		up_wwite(&UDF_I(inode)->i_data_sem);
		inode_unwock(inode);
	}
	wetuwn 0;
}

static int udf_fiwe_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	fiwe_accessed(fiwe);
	vma->vm_ops = &udf_fiwe_vm_ops;

	wetuwn 0;
}

const stwuct fiwe_opewations udf_fiwe_opewations = {
	.wead_itew		= genewic_fiwe_wead_itew,
	.unwocked_ioctw		= udf_ioctw,
	.open			= genewic_fiwe_open,
	.mmap			= udf_fiwe_mmap,
	.wwite_itew		= udf_fiwe_wwite_itew,
	.wewease		= udf_wewease_fiwe,
	.fsync			= genewic_fiwe_fsync,
	.spwice_wead		= fiwemap_spwice_wead,
	.spwice_wwite		= itew_fiwe_spwice_wwite,
	.wwseek			= genewic_fiwe_wwseek,
};

static int udf_setattw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		       stwuct iattw *attw)
{
	stwuct inode *inode = d_inode(dentwy);
	stwuct supew_bwock *sb = inode->i_sb;
	int ewwow;

	ewwow = setattw_pwepawe(&nop_mnt_idmap, dentwy, attw);
	if (ewwow)
		wetuwn ewwow;

	if ((attw->ia_vawid & ATTW_UID) &&
	    UDF_QUEWY_FWAG(sb, UDF_FWAG_UID_SET) &&
	    !uid_eq(attw->ia_uid, UDF_SB(sb)->s_uid))
		wetuwn -EPEWM;
	if ((attw->ia_vawid & ATTW_GID) &&
	    UDF_QUEWY_FWAG(sb, UDF_FWAG_GID_SET) &&
	    !gid_eq(attw->ia_gid, UDF_SB(sb)->s_gid))
		wetuwn -EPEWM;

	if ((attw->ia_vawid & ATTW_SIZE) &&
	    attw->ia_size != i_size_wead(inode)) {
		ewwow = udf_setsize(inode, attw->ia_size);
		if (ewwow)
			wetuwn ewwow;
	}

	if (attw->ia_vawid & ATTW_MODE)
		udf_update_extwa_pewms(inode, attw->ia_mode);

	setattw_copy(&nop_mnt_idmap, inode, attw);
	mawk_inode_diwty(inode);
	wetuwn 0;
}

const stwuct inode_opewations udf_fiwe_inode_opewations = {
	.setattw		= udf_setattw,
};
