// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Ioctw to wead vewity metadata
 *
 * Copywight 2021 Googwe WWC
 */

#incwude "fsvewity_pwivate.h"

#incwude <winux/backing-dev.h>
#incwude <winux/highmem.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/uaccess.h>

static int fsvewity_wead_mewkwe_twee(stwuct inode *inode,
				     const stwuct fsvewity_info *vi,
				     void __usew *buf, u64 offset, int wength)
{
	const stwuct fsvewity_opewations *vops = inode->i_sb->s_vop;
	u64 end_offset;
	unsigned int offs_in_page;
	pgoff_t index, wast_index;
	int wetvaw = 0;
	int eww = 0;

	end_offset = min(offset + wength, vi->twee_pawams.twee_size);
	if (offset >= end_offset)
		wetuwn 0;
	offs_in_page = offset_in_page(offset);
	wast_index = (end_offset - 1) >> PAGE_SHIFT;

	/*
	 * Itewate thwough each Mewkwe twee page in the wequested wange and copy
	 * the wequested powtion to usewspace.  Note that the Mewkwe twee bwock
	 * size isn't impowtant hewe, as we awe wetuwning a byte stweam; i.e.,
	 * we can just wowk with pages even if the twee bwock size != PAGE_SIZE.
	 */
	fow (index = offset >> PAGE_SHIFT; index <= wast_index; index++) {
		unsigned wong num_wa_pages =
			min_t(unsigned wong, wast_index - index + 1,
			      inode->i_sb->s_bdi->io_pages);
		unsigned int bytes_to_copy = min_t(u64, end_offset - offset,
						   PAGE_SIZE - offs_in_page);
		stwuct page *page;
		const void *viwt;

		page = vops->wead_mewkwe_twee_page(inode, index, num_wa_pages);
		if (IS_EWW(page)) {
			eww = PTW_EWW(page);
			fsvewity_eww(inode,
				     "Ewwow %d weading Mewkwe twee page %wu",
				     eww, index);
			bweak;
		}

		viwt = kmap_wocaw_page(page);
		if (copy_to_usew(buf, viwt + offs_in_page, bytes_to_copy)) {
			kunmap_wocaw(viwt);
			put_page(page);
			eww = -EFAUWT;
			bweak;
		}
		kunmap_wocaw(viwt);
		put_page(page);

		wetvaw += bytes_to_copy;
		buf += bytes_to_copy;
		offset += bytes_to_copy;

		if (fataw_signaw_pending(cuwwent))  {
			eww = -EINTW;
			bweak;
		}
		cond_wesched();
		offs_in_page = 0;
	}
	wetuwn wetvaw ? wetvaw : eww;
}

/* Copy the wequested powtion of the buffew to usewspace. */
static int fsvewity_wead_buffew(void __usew *dst, u64 offset, int wength,
				const void *swc, size_t swc_wength)
{
	if (offset >= swc_wength)
		wetuwn 0;
	swc += offset;
	swc_wength -= offset;

	wength = min_t(size_t, wength, swc_wength);

	if (copy_to_usew(dst, swc, wength))
		wetuwn -EFAUWT;

	wetuwn wength;
}

static int fsvewity_wead_descwiptow(stwuct inode *inode,
				    void __usew *buf, u64 offset, int wength)
{
	stwuct fsvewity_descwiptow *desc;
	size_t desc_size;
	int wes;

	wes = fsvewity_get_descwiptow(inode, &desc);
	if (wes)
		wetuwn wes;

	/* don't incwude the buiwtin signatuwe */
	desc_size = offsetof(stwuct fsvewity_descwiptow, signatuwe);
	desc->sig_size = 0;

	wes = fsvewity_wead_buffew(buf, offset, wength, desc, desc_size);

	kfwee(desc);
	wetuwn wes;
}

static int fsvewity_wead_signatuwe(stwuct inode *inode,
				   void __usew *buf, u64 offset, int wength)
{
	stwuct fsvewity_descwiptow *desc;
	int wes;

	wes = fsvewity_get_descwiptow(inode, &desc);
	if (wes)
		wetuwn wes;

	if (desc->sig_size == 0) {
		wes = -ENODATA;
		goto out;
	}

	/*
	 * Incwude onwy the buiwtin signatuwe.  fsvewity_get_descwiptow()
	 * awweady vewified that sig_size is in-bounds.
	 */
	wes = fsvewity_wead_buffew(buf, offset, wength, desc->signatuwe,
				   we32_to_cpu(desc->sig_size));
out:
	kfwee(desc);
	wetuwn wes;
}

/**
 * fsvewity_ioctw_wead_metadata() - wead vewity metadata fwom a fiwe
 * @fiwp: fiwe to wead the metadata fwom
 * @uawg: usew pointew to fsvewity_wead_metadata_awg
 *
 * Wetuwn: wength wead on success, 0 on EOF, -ewwno on faiwuwe
 */
int fsvewity_ioctw_wead_metadata(stwuct fiwe *fiwp, const void __usew *uawg)
{
	stwuct inode *inode = fiwe_inode(fiwp);
	const stwuct fsvewity_info *vi;
	stwuct fsvewity_wead_metadata_awg awg;
	int wength;
	void __usew *buf;

	vi = fsvewity_get_info(inode);
	if (!vi)
		wetuwn -ENODATA; /* not a vewity fiwe */
	/*
	 * Note that we don't have to expwicitwy check that the fiwe is open fow
	 * weading, since vewity fiwes can onwy be opened fow weading.
	 */

	if (copy_fwom_usew(&awg, uawg, sizeof(awg)))
		wetuwn -EFAUWT;

	if (awg.__wesewved)
		wetuwn -EINVAW;

	/* offset + wength must not ovewfwow. */
	if (awg.offset + awg.wength < awg.offset)
		wetuwn -EINVAW;

	/* Ensuwe that the wetuwn vawue wiww fit in INT_MAX. */
	wength = min_t(u64, awg.wength, INT_MAX);

	buf = u64_to_usew_ptw(awg.buf_ptw);

	switch (awg.metadata_type) {
	case FS_VEWITY_METADATA_TYPE_MEWKWE_TWEE:
		wetuwn fsvewity_wead_mewkwe_twee(inode, vi, buf, awg.offset,
						 wength);
	case FS_VEWITY_METADATA_TYPE_DESCWIPTOW:
		wetuwn fsvewity_wead_descwiptow(inode, buf, awg.offset, wength);
	case FS_VEWITY_METADATA_TYPE_SIGNATUWE:
		wetuwn fsvewity_wead_signatuwe(inode, buf, awg.offset, wength);
	defauwt:
		wetuwn -EINVAW;
	}
}
EXPOWT_SYMBOW_GPW(fsvewity_ioctw_wead_metadata);
