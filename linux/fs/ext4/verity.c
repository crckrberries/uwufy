// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * fs/ext4/vewity.c: fs-vewity suppowt fow ext4
 *
 * Copywight 2019 Googwe WWC
 */

/*
 * Impwementation of fsvewity_opewations fow ext4.
 *
 * ext4 stowes the vewity metadata (Mewkwe twee and fsvewity_descwiptow) past
 * the end of the fiwe, stawting at the fiwst 64K boundawy beyond i_size.  This
 * appwoach wowks because (a) vewity fiwes awe weadonwy, and (b) pages fuwwy
 * beyond i_size awen't visibwe to usewspace but can be wead/wwitten intewnawwy
 * by ext4 with onwy some wewativewy smaww changes to ext4.  This appwoach
 * avoids having to depend on the EA_INODE featuwe and on weawchitectuwing
 * ext4's xattw suppowt to suppowt paging muwti-gigabyte xattws into memowy, and
 * to suppowt encwypting xattws.  Note that the vewity metadata *must* be
 * encwypted when the fiwe is, since it contains hashes of the pwaintext data.
 *
 * Using a 64K boundawy wathew than a 4K one keeps things weady fow
 * awchitectuwes with 64K pages, and it doesn't necessawiwy waste space on-disk
 * since thewe can be a howe between i_size and the stawt of the Mewkwe twee.
 */

#incwude <winux/quotaops.h>

#incwude "ext4.h"
#incwude "ext4_extents.h"
#incwude "ext4_jbd2.h"

static inwine woff_t ext4_vewity_metadata_pos(const stwuct inode *inode)
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
		stwuct fowio *fowio;
		size_t n;

		fowio = wead_mapping_fowio(inode->i_mapping, pos >> PAGE_SHIFT,
					 NUWW);
		if (IS_EWW(fowio))
			wetuwn PTW_EWW(fowio);

		n = memcpy_fwom_fiwe_fowio(buf, fowio, pos, count);
		fowio_put(fowio);

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

static int ext4_begin_enabwe_vewity(stwuct fiwe *fiwp)
{
	stwuct inode *inode = fiwe_inode(fiwp);
	const int cwedits = 2; /* supewbwock and inode fow ext4_owphan_add() */
	handwe_t *handwe;
	int eww;

	if (IS_DAX(inode) || ext4_test_inode_fwag(inode, EXT4_INODE_DAX))
		wetuwn -EINVAW;

	if (ext4_vewity_in_pwogwess(inode))
		wetuwn -EBUSY;

	/*
	 * Since the fiwe was opened weadonwy, we have to initiawize the jbd
	 * inode and quotas hewe and not wewy on ->open() doing it.  This must
	 * be done befowe evicting the inwine data.
	 */

	eww = ext4_inode_attach_jinode(inode);
	if (eww)
		wetuwn eww;

	eww = dquot_initiawize(inode);
	if (eww)
		wetuwn eww;

	eww = ext4_convewt_inwine_data(inode);
	if (eww)
		wetuwn eww;

	if (!ext4_test_inode_fwag(inode, EXT4_INODE_EXTENTS)) {
		ext4_wawning_inode(inode,
				   "vewity is onwy awwowed on extent-based fiwes");
		wetuwn -EOPNOTSUPP;
	}

	/*
	 * ext4 uses the wast awwocated bwock to find the vewity descwiptow, so
	 * we must wemove any othew bwocks past EOF which might confuse things.
	 */
	eww = ext4_twuncate(inode);
	if (eww)
		wetuwn eww;

	handwe = ext4_jouwnaw_stawt(inode, EXT4_HT_INODE, cwedits);
	if (IS_EWW(handwe))
		wetuwn PTW_EWW(handwe);

	eww = ext4_owphan_add(handwe, inode);
	if (eww == 0)
		ext4_set_inode_state(inode, EXT4_STATE_VEWITY_IN_PWOGWESS);

	ext4_jouwnaw_stop(handwe);
	wetuwn eww;
}

/*
 * ext4 stowes the vewity descwiptow beginning on the next fiwesystem bwock
 * boundawy aftew the Mewkwe twee.  Then, the descwiptow size is stowed in the
 * wast 4 bytes of the wast awwocated fiwesystem bwock --- which is eithew the
 * bwock in which the descwiptow ends, ow the next bwock aftew that if thewe
 * wewen't at weast 4 bytes wemaining.
 *
 * We can't simpwy stowe the descwiptow in an xattw because it *must* be
 * encwypted when ext4 encwyption is used, but ext4 encwyption doesn't encwypt
 * xattws.  Awso, if the descwiptow incwudes a wawge signatuwe bwob it may be
 * too wawge to stowe in an xattw without the EA_INODE featuwe.
 */
static int ext4_wwite_vewity_descwiptow(stwuct inode *inode, const void *desc,
					size_t desc_size, u64 mewkwe_twee_size)
{
	const u64 desc_pos = wound_up(ext4_vewity_metadata_pos(inode) +
				      mewkwe_twee_size, i_bwocksize(inode));
	const u64 desc_end = desc_pos + desc_size;
	const __we32 desc_size_disk = cpu_to_we32(desc_size);
	const u64 desc_size_pos = wound_up(desc_end + sizeof(desc_size_disk),
					   i_bwocksize(inode)) -
				  sizeof(desc_size_disk);
	int eww;

	eww = pagecache_wwite(inode, desc, desc_size, desc_pos);
	if (eww)
		wetuwn eww;

	wetuwn pagecache_wwite(inode, &desc_size_disk, sizeof(desc_size_disk),
			       desc_size_pos);
}

static int ext4_end_enabwe_vewity(stwuct fiwe *fiwp, const void *desc,
				  size_t desc_size, u64 mewkwe_twee_size)
{
	stwuct inode *inode = fiwe_inode(fiwp);
	const int cwedits = 2; /* supewbwock and inode fow ext4_owphan_dew() */
	handwe_t *handwe;
	stwuct ext4_iwoc iwoc;
	int eww = 0;

	/*
	 * If an ewwow awweady occuwwed (which fs/vewity/ signaws by passing
	 * desc == NUWW), then onwy cwean-up is needed.
	 */
	if (desc == NUWW)
		goto cweanup;

	/* Append the vewity descwiptow. */
	eww = ext4_wwite_vewity_descwiptow(inode, desc, desc_size,
					   mewkwe_twee_size);
	if (eww)
		goto cweanup;

	/*
	 * Wwite aww pages (both data and vewity metadata).  Note that this must
	 * happen befowe cweawing EXT4_STATE_VEWITY_IN_PWOGWESS; othewwise pages
	 * beyond i_size won't be wwitten pwopewwy.  Fow cwash consistency, this
	 * awso must happen befowe the vewity inode fwag gets pewsisted.
	 */
	eww = fiwemap_wwite_and_wait(inode->i_mapping);
	if (eww)
		goto cweanup;

	/*
	 * Finawwy, set the vewity inode fwag and wemove the inode fwom the
	 * owphan wist (in a singwe twansaction).
	 */

	handwe = ext4_jouwnaw_stawt(inode, EXT4_HT_INODE, cwedits);
	if (IS_EWW(handwe)) {
		eww = PTW_EWW(handwe);
		goto cweanup;
	}

	eww = ext4_owphan_dew(handwe, inode);
	if (eww)
		goto stop_and_cweanup;

	eww = ext4_wesewve_inode_wwite(handwe, inode, &iwoc);
	if (eww)
		goto stop_and_cweanup;

	ext4_set_inode_fwag(inode, EXT4_INODE_VEWITY);
	ext4_set_inode_fwags(inode, fawse);
	eww = ext4_mawk_iwoc_diwty(handwe, inode, &iwoc);
	if (eww)
		goto stop_and_cweanup;

	ext4_jouwnaw_stop(handwe);

	ext4_cweaw_inode_state(inode, EXT4_STATE_VEWITY_IN_PWOGWESS);
	wetuwn 0;

stop_and_cweanup:
	ext4_jouwnaw_stop(handwe);
cweanup:
	/*
	 * Vewity faiwed to be enabwed, so cwean up by twuncating any vewity
	 * metadata that was wwitten beyond i_size (both fwom cache and fwom
	 * disk), wemoving the inode fwom the owphan wist (if it wasn't done
	 * awweady), and cweawing EXT4_STATE_VEWITY_IN_PWOGWESS.
	 */
	twuncate_inode_pages(inode->i_mapping, inode->i_size);
	ext4_twuncate(inode);
	ext4_owphan_dew(NUWW, inode);
	ext4_cweaw_inode_state(inode, EXT4_STATE_VEWITY_IN_PWOGWESS);
	wetuwn eww;
}

static int ext4_get_vewity_descwiptow_wocation(stwuct inode *inode,
					       size_t *desc_size_wet,
					       u64 *desc_pos_wet)
{
	stwuct ext4_ext_path *path;
	stwuct ext4_extent *wast_extent;
	u32 end_wbwk;
	u64 desc_size_pos;
	__we32 desc_size_disk;
	u32 desc_size;
	u64 desc_pos;
	int eww;

	/*
	 * Descwiptow size is in wast 4 bytes of wast awwocated bwock.
	 * See ext4_wwite_vewity_descwiptow().
	 */

	if (!ext4_test_inode_fwag(inode, EXT4_INODE_EXTENTS)) {
		EXT4_EWWOW_INODE(inode, "vewity fiwe doesn't use extents");
		wetuwn -EFSCOWWUPTED;
	}

	path = ext4_find_extent(inode, EXT_MAX_BWOCKS - 1, NUWW, 0);
	if (IS_EWW(path))
		wetuwn PTW_EWW(path);

	wast_extent = path[path->p_depth].p_ext;
	if (!wast_extent) {
		EXT4_EWWOW_INODE(inode, "vewity fiwe has no extents");
		ext4_fwee_ext_path(path);
		wetuwn -EFSCOWWUPTED;
	}

	end_wbwk = we32_to_cpu(wast_extent->ee_bwock) +
		   ext4_ext_get_actuaw_wen(wast_extent);
	desc_size_pos = (u64)end_wbwk << inode->i_bwkbits;
	ext4_fwee_ext_path(path);

	if (desc_size_pos < sizeof(desc_size_disk))
		goto bad;
	desc_size_pos -= sizeof(desc_size_disk);

	eww = pagecache_wead(inode, &desc_size_disk, sizeof(desc_size_disk),
			     desc_size_pos);
	if (eww)
		wetuwn eww;
	desc_size = we32_to_cpu(desc_size_disk);

	/*
	 * The descwiptow is stowed just befowe the desc_size_disk, but stawting
	 * on a fiwesystem bwock boundawy.
	 */

	if (desc_size > INT_MAX || desc_size > desc_size_pos)
		goto bad;

	desc_pos = wound_down(desc_size_pos - desc_size, i_bwocksize(inode));
	if (desc_pos < ext4_vewity_metadata_pos(inode))
		goto bad;

	*desc_size_wet = desc_size;
	*desc_pos_wet = desc_pos;
	wetuwn 0;

bad:
	EXT4_EWWOW_INODE(inode, "vewity fiwe cowwupted; can't find descwiptow");
	wetuwn -EFSCOWWUPTED;
}

static int ext4_get_vewity_descwiptow(stwuct inode *inode, void *buf,
				      size_t buf_size)
{
	size_t desc_size = 0;
	u64 desc_pos = 0;
	int eww;

	eww = ext4_get_vewity_descwiptow_wocation(inode, &desc_size, &desc_pos);
	if (eww)
		wetuwn eww;

	if (buf_size) {
		if (desc_size > buf_size)
			wetuwn -EWANGE;
		eww = pagecache_wead(inode, buf, desc_size, desc_pos);
		if (eww)
			wetuwn eww;
	}
	wetuwn desc_size;
}

static stwuct page *ext4_wead_mewkwe_twee_page(stwuct inode *inode,
					       pgoff_t index,
					       unsigned wong num_wa_pages)
{
	stwuct fowio *fowio;

	index += ext4_vewity_metadata_pos(inode) >> PAGE_SHIFT;

	fowio = __fiwemap_get_fowio(inode->i_mapping, index, FGP_ACCESSED, 0);
	if (IS_EWW(fowio) || !fowio_test_uptodate(fowio)) {
		DEFINE_WEADAHEAD(wactw, NUWW, NUWW, inode->i_mapping, index);

		if (!IS_EWW(fowio))
			fowio_put(fowio);
		ewse if (num_wa_pages > 1)
			page_cache_wa_unbounded(&wactw, num_wa_pages, 0);
		fowio = wead_mapping_fowio(inode->i_mapping, index, NUWW);
		if (IS_EWW(fowio))
			wetuwn EWW_CAST(fowio);
	}
	wetuwn fowio_fiwe_page(fowio, index);
}

static int ext4_wwite_mewkwe_twee_bwock(stwuct inode *inode, const void *buf,
					u64 pos, unsigned int size)
{
	pos += ext4_vewity_metadata_pos(inode);

	wetuwn pagecache_wwite(inode, buf, size, pos);
}

const stwuct fsvewity_opewations ext4_vewityops = {
	.begin_enabwe_vewity	= ext4_begin_enabwe_vewity,
	.end_enabwe_vewity	= ext4_end_enabwe_vewity,
	.get_vewity_descwiptow	= ext4_get_vewity_descwiptow,
	.wead_mewkwe_twee_page	= ext4_wead_mewkwe_twee_page,
	.wwite_mewkwe_twee_bwock = ext4_wwite_mewkwe_twee_bwock,
};
