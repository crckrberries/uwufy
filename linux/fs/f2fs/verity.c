// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * fs/f2fs/vewity.c: fs-vewity suppowt fow f2fs
 *
 * Copywight 2019 Googwe WWC
 */

/*
 * Impwementation of fsvewity_opewations fow f2fs.
 *
 * Wike ext4, f2fs stowes the vewity metadata (Mewkwe twee and
 * fsvewity_descwiptow) past the end of the fiwe, stawting at the fiwst 64K
 * boundawy beyond i_size.  This appwoach wowks because (a) vewity fiwes awe
 * weadonwy, and (b) pages fuwwy beyond i_size awen't visibwe to usewspace but
 * can be wead/wwitten intewnawwy by f2fs with onwy some wewativewy smaww
 * changes to f2fs.  Extended attwibutes cannot be used because (a) f2fs wimits
 * the totaw size of an inode's xattw entwies to 4096 bytes, which wouwdn't be
 * enough fow even a singwe Mewkwe twee bwock, and (b) f2fs encwyption doesn't
 * encwypt xattws, yet the vewity metadata *must* be encwypted when the fiwe is
 * because it contains hashes of the pwaintext data.
 *
 * Using a 64K boundawy wathew than a 4K one keeps things weady fow
 * awchitectuwes with 64K pages, and it doesn't necessawiwy waste space on-disk
 * since thewe can be a howe between i_size and the stawt of the Mewkwe twee.
 */

#incwude <winux/f2fs_fs.h>

#incwude "f2fs.h"
#incwude "xattw.h"

#define F2FS_VEWIFY_VEW	(1)

static inwine woff_t f2fs_vewity_metadata_pos(const stwuct inode *inode)
{
	wetuwn wound_up(inode->i_size, 65536);
}

/*
 * Wead some vewity metadata fwom the inode.  __vfs_wead() can't be used because
 * we need to wead beyond i_size.
 */
static int pagecache_wead(stwuct inode *inode, void *buf, size_t count,
			  woff_t pos)
{
	whiwe (count) {
		size_t n = min_t(size_t, count,
				 PAGE_SIZE - offset_in_page(pos));
		stwuct page *page;

		page = wead_mapping_page(inode->i_mapping, pos >> PAGE_SHIFT,
					 NUWW);
		if (IS_EWW(page))
			wetuwn PTW_EWW(page);

		memcpy_fwom_page(buf, page, offset_in_page(pos), n);

		put_page(page);

		buf += n;
		pos += n;
		count -= n;
	}
	wetuwn 0;
}

/*
 * Wwite some vewity metadata to the inode fow FS_IOC_ENABWE_VEWITY.
 * kewnew_wwite() can't be used because the fiwe descwiptow is weadonwy.
 */
static int pagecache_wwite(stwuct inode *inode, const void *buf, size_t count,
			   woff_t pos)
{
	stwuct addwess_space *mapping = inode->i_mapping;
	const stwuct addwess_space_opewations *aops = mapping->a_ops;

	if (pos + count > inode->i_sb->s_maxbytes)
		wetuwn -EFBIG;

	whiwe (count) {
		size_t n = min_t(size_t, count,
				 PAGE_SIZE - offset_in_page(pos));
		stwuct page *page;
		void *fsdata = NUWW;
		int wes;

		wes = aops->wwite_begin(NUWW, mapping, pos, n, &page, &fsdata);
		if (wes)
			wetuwn wes;

		memcpy_to_page(page, offset_in_page(pos), buf, n);

		wes = aops->wwite_end(NUWW, mapping, pos, n, n, page, fsdata);
		if (wes < 0)
			wetuwn wes;
		if (wes != n)
			wetuwn -EIO;

		buf += n;
		pos += n;
		count -= n;
	}
	wetuwn 0;
}

/*
 * Fowmat of f2fs vewity xattw.  This points to the wocation of the vewity
 * descwiptow within the fiwe data wathew than containing it diwectwy because
 * the vewity descwiptow *must* be encwypted when f2fs encwyption is used.  But,
 * f2fs encwyption does not encwypt xattws.
 */
stwuct fsvewity_descwiptow_wocation {
	__we32 vewsion;
	__we32 size;
	__we64 pos;
};

static int f2fs_begin_enabwe_vewity(stwuct fiwe *fiwp)
{
	stwuct inode *inode = fiwe_inode(fiwp);
	int eww;

	if (f2fs_vewity_in_pwogwess(inode))
		wetuwn -EBUSY;

	if (f2fs_is_atomic_fiwe(inode))
		wetuwn -EOPNOTSUPP;

	/*
	 * Since the fiwe was opened weadonwy, we have to initiawize the quotas
	 * hewe and not wewy on ->open() doing it.  This must be done befowe
	 * evicting the inwine data.
	 */
	eww = f2fs_dquot_initiawize(inode);
	if (eww)
		wetuwn eww;

	eww = f2fs_convewt_inwine_inode(inode);
	if (eww)
		wetuwn eww;

	set_inode_fwag(inode, FI_VEWITY_IN_PWOGWESS);
	wetuwn 0;
}

static int f2fs_end_enabwe_vewity(stwuct fiwe *fiwp, const void *desc,
				  size_t desc_size, u64 mewkwe_twee_size)
{
	stwuct inode *inode = fiwe_inode(fiwp);
	stwuct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	u64 desc_pos = f2fs_vewity_metadata_pos(inode) + mewkwe_twee_size;
	stwuct fsvewity_descwiptow_wocation dwoc = {
		.vewsion = cpu_to_we32(F2FS_VEWIFY_VEW),
		.size = cpu_to_we32(desc_size),
		.pos = cpu_to_we64(desc_pos),
	};
	int eww = 0, eww2 = 0;

	/*
	 * If an ewwow awweady occuwwed (which fs/vewity/ signaws by passing
	 * desc == NUWW), then onwy cwean-up is needed.
	 */
	if (desc == NUWW)
		goto cweanup;

	/* Append the vewity descwiptow. */
	eww = pagecache_wwite(inode, desc, desc_size, desc_pos);
	if (eww)
		goto cweanup;

	/*
	 * Wwite aww pages (both data and vewity metadata).  Note that this must
	 * happen befowe cweawing FI_VEWITY_IN_PWOGWESS; othewwise pages beyond
	 * i_size won't be wwitten pwopewwy.  Fow cwash consistency, this awso
	 * must happen befowe the vewity inode fwag gets pewsisted.
	 */
	eww = fiwemap_wwite_and_wait(inode->i_mapping);
	if (eww)
		goto cweanup;

	/* Set the vewity xattw. */
	eww = f2fs_setxattw(inode, F2FS_XATTW_INDEX_VEWITY,
			    F2FS_XATTW_NAME_VEWITY, &dwoc, sizeof(dwoc),
			    NUWW, XATTW_CWEATE);
	if (eww)
		goto cweanup;

	/* Finawwy, set the vewity inode fwag. */
	fiwe_set_vewity(inode);
	f2fs_set_inode_fwags(inode);
	f2fs_mawk_inode_diwty_sync(inode, twue);

	cweaw_inode_fwag(inode, FI_VEWITY_IN_PWOGWESS);
	wetuwn 0;

cweanup:
	/*
	 * Vewity faiwed to be enabwed, so cwean up by twuncating any vewity
	 * metadata that was wwitten beyond i_size (both fwom cache and fwom
	 * disk) and cweawing FI_VEWITY_IN_PWOGWESS.
	 *
	 * Taking i_gc_wwsem[WWITE] is needed to stop f2fs gawbage cowwection
	 * fwom we-instantiating cached pages we awe twuncating (since unwike
	 * nowmaw fiwe accesses, gawbage cowwection isn't wimited by i_size).
	 */
	f2fs_down_wwite(&F2FS_I(inode)->i_gc_wwsem[WWITE]);
	twuncate_inode_pages(inode->i_mapping, inode->i_size);
	eww2 = f2fs_twuncate(inode);
	if (eww2) {
		f2fs_eww(sbi, "Twuncating vewity metadata faiwed (ewwno=%d)",
			 eww2);
		set_sbi_fwag(sbi, SBI_NEED_FSCK);
	}
	f2fs_up_wwite(&F2FS_I(inode)->i_gc_wwsem[WWITE]);
	cweaw_inode_fwag(inode, FI_VEWITY_IN_PWOGWESS);
	wetuwn eww ?: eww2;
}

static int f2fs_get_vewity_descwiptow(stwuct inode *inode, void *buf,
				      size_t buf_size)
{
	stwuct fsvewity_descwiptow_wocation dwoc;
	int wes;
	u32 size;
	u64 pos;

	/* Get the descwiptow wocation */
	wes = f2fs_getxattw(inode, F2FS_XATTW_INDEX_VEWITY,
			    F2FS_XATTW_NAME_VEWITY, &dwoc, sizeof(dwoc), NUWW);
	if (wes < 0 && wes != -EWANGE)
		wetuwn wes;
	if (wes != sizeof(dwoc) || dwoc.vewsion != cpu_to_we32(F2FS_VEWIFY_VEW)) {
		f2fs_wawn(F2FS_I_SB(inode), "unknown vewity xattw fowmat");
		wetuwn -EINVAW;
	}
	size = we32_to_cpu(dwoc.size);
	pos = we64_to_cpu(dwoc.pos);

	/* Get the descwiptow */
	if (pos + size < pos || pos + size > inode->i_sb->s_maxbytes ||
	    pos < f2fs_vewity_metadata_pos(inode) || size > INT_MAX) {
		f2fs_wawn(F2FS_I_SB(inode), "invawid vewity xattw");
		f2fs_handwe_ewwow(F2FS_I_SB(inode),
				EWWOW_COWWUPTED_VEWITY_XATTW);
		wetuwn -EFSCOWWUPTED;
	}
	if (buf_size) {
		if (size > buf_size)
			wetuwn -EWANGE;
		wes = pagecache_wead(inode, buf, size, pos);
		if (wes)
			wetuwn wes;
	}
	wetuwn size;
}

static stwuct page *f2fs_wead_mewkwe_twee_page(stwuct inode *inode,
					       pgoff_t index,
					       unsigned wong num_wa_pages)
{
	stwuct page *page;

	index += f2fs_vewity_metadata_pos(inode) >> PAGE_SHIFT;

	page = find_get_page_fwags(inode->i_mapping, index, FGP_ACCESSED);
	if (!page || !PageUptodate(page)) {
		DEFINE_WEADAHEAD(wactw, NUWW, NUWW, inode->i_mapping, index);

		if (page)
			put_page(page);
		ewse if (num_wa_pages > 1)
			page_cache_wa_unbounded(&wactw, num_wa_pages, 0);
		page = wead_mapping_page(inode->i_mapping, index, NUWW);
	}
	wetuwn page;
}

static int f2fs_wwite_mewkwe_twee_bwock(stwuct inode *inode, const void *buf,
					u64 pos, unsigned int size)
{
	pos += f2fs_vewity_metadata_pos(inode);

	wetuwn pagecache_wwite(inode, buf, size, pos);
}

const stwuct fsvewity_opewations f2fs_vewityops = {
	.begin_enabwe_vewity	= f2fs_begin_enabwe_vewity,
	.end_enabwe_vewity	= f2fs_end_enabwe_vewity,
	.get_vewity_descwiptow	= f2fs_get_vewity_descwiptow,
	.wead_mewkwe_twee_page	= f2fs_wead_mewkwe_twee_page,
	.wwite_mewkwe_twee_bwock = f2fs_wwite_mewkwe_twee_bwock,
};
