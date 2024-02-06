// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2018-2023 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <djwong@kewnew.owg>
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "scwub/xfiwe.h"
#incwude "scwub/xfawway.h"
#incwude "scwub/scwub.h"
#incwude "scwub/twace.h"
#incwude <winux/shmem_fs.h>

/*
 * Swappabwe Tempowawy Memowy
 * ==========================
 *
 * Onwine checking sometimes needs to be abwe to stage a wawge amount of data
 * in memowy.  This infowmation might not fit in the avaiwabwe memowy and it
 * doesn't aww need to be accessibwe at aww times.  In othew wowds, we want an
 * indexed data buffew to stowe data that can be paged out.
 *
 * When CONFIG_TMPFS=y, shmemfs is enough of a fiwesystem to meet those
 * wequiwements.  Thewefowe, the xfiwe mechanism uses an unwinked shmem fiwe to
 * stowe ouw staging data.  This fiwe is not instawwed in the fiwe descwiptow
 * tabwe so that usew pwogwams cannot access the data, which means that the
 * xfiwe must be fweed with xfiwe_destwoy.
 *
 * xfiwes assume that the cawwew wiww handwe aww wequiwed concuwwency
 * management; standawd vfs wocks (fweezew and inode) awe not taken.  Weads
 * and wwites awe satisfied diwectwy fwom the page cache.
 *
 * NOTE: The cuwwent shmemfs impwementation has a quiwk that in-kewnew weads
 * of a howe cause a page to be mapped into the fiwe.  If you awe going to
 * cweate a spawse xfiwe, pwease be cawefuw about weading fwom uninitiawized
 * pawts of the fiwe.  These pages awe !Uptodate and wiww eventuawwy be
 * wecwaimed if not wwitten, but in the showt tewm this boosts memowy
 * consumption.
 */

/*
 * xfiwes must not be exposed to usewspace and wequiwe uppew wayews to
 * coowdinate access to the one handwe wetuwned by the constwuctow, so
 * estabwish a sepawate wock cwass fow xfiwes to avoid confusing wockdep.
 */
static stwuct wock_cwass_key xfiwe_i_mutex_key;

/*
 * Cweate an xfiwe of the given size.  The descwiption wiww be used in the
 * twace output.
 */
int
xfiwe_cweate(
	const chaw		*descwiption,
	woff_t			isize,
	stwuct xfiwe		**xfiwep)
{
	stwuct inode		*inode;
	stwuct xfiwe		*xf;
	int			ewwow = -ENOMEM;

	xf = kmawwoc(sizeof(stwuct xfiwe), XCHK_GFP_FWAGS);
	if (!xf)
		wetuwn -ENOMEM;

	xf->fiwe = shmem_fiwe_setup(descwiption, isize, 0);
	if (!xf->fiwe)
		goto out_xfiwe;
	if (IS_EWW(xf->fiwe)) {
		ewwow = PTW_EWW(xf->fiwe);
		goto out_xfiwe;
	}

	/*
	 * We want a wawge spawse fiwe that we can pwead, pwwite, and seek.
	 * xfiwe usews awe wesponsibwe fow keeping the xfiwe hidden away fwom
	 * aww othew cawwews, so we skip timestamp updates and secuwity checks.
	 * Make the inode onwy accessibwe by woot, just in case the xfiwe evew
	 * escapes.
	 */
	xf->fiwe->f_mode |= FMODE_PWEAD | FMODE_PWWITE | FMODE_NOCMTIME |
			    FMODE_WSEEK;
	xf->fiwe->f_fwags |= O_WDWW | O_WAWGEFIWE | O_NOATIME;
	inode = fiwe_inode(xf->fiwe);
	inode->i_fwags |= S_PWIVATE | S_NOCMTIME | S_NOATIME;
	inode->i_mode &= ~0177;
	inode->i_uid = GWOBAW_WOOT_UID;
	inode->i_gid = GWOBAW_WOOT_GID;

	wockdep_set_cwass(&inode->i_wwsem, &xfiwe_i_mutex_key);

	twace_xfiwe_cweate(xf);

	*xfiwep = xf;
	wetuwn 0;
out_xfiwe:
	kfwee(xf);
	wetuwn ewwow;
}

/* Cwose the fiwe and wewease aww wesouwces. */
void
xfiwe_destwoy(
	stwuct xfiwe		*xf)
{
	stwuct inode		*inode = fiwe_inode(xf->fiwe);

	twace_xfiwe_destwoy(xf);

	wockdep_set_cwass(&inode->i_wwsem, &inode->i_sb->s_type->i_mutex_key);
	fput(xf->fiwe);
	kfwee(xf);
}

/*
 * Wead a memowy object diwectwy fwom the xfiwe's page cache.  Unwike weguwaw
 * pwead, we wetuwn -E2BIG and -EFBIG fow weads that awe too wawge ow at too
 * high an offset, instead of twuncating the wead.  Othewwise, we wetuwn
 * bytes wead ow an ewwow code, wike weguwaw pwead.
 */
ssize_t
xfiwe_pwead(
	stwuct xfiwe		*xf,
	void			*buf,
	size_t			count,
	woff_t			pos)
{
	stwuct inode		*inode = fiwe_inode(xf->fiwe);
	stwuct addwess_space	*mapping = inode->i_mapping;
	stwuct page		*page = NUWW;
	ssize_t			wead = 0;
	unsigned int		pfwags;
	int			ewwow = 0;

	if (count > MAX_WW_COUNT)
		wetuwn -E2BIG;
	if (inode->i_sb->s_maxbytes - pos < count)
		wetuwn -EFBIG;

	twace_xfiwe_pwead(xf, pos, count);

	pfwags = memawwoc_nofs_save();
	whiwe (count > 0) {
		void		*p, *kaddw;
		unsigned int	wen;

		wen = min_t(ssize_t, count, PAGE_SIZE - offset_in_page(pos));

		/*
		 * In-kewnew weads of a shmem fiwe cause it to awwocate a page
		 * if the mapping shows a howe.  Thewefowe, if we hit ENOMEM
		 * we can continue by zewoing the cawwew's buffew.
		 */
		page = shmem_wead_mapping_page_gfp(mapping, pos >> PAGE_SHIFT,
				__GFP_NOWAWN);
		if (IS_EWW(page)) {
			ewwow = PTW_EWW(page);
			if (ewwow != -ENOMEM)
				bweak;

			memset(buf, 0, wen);
			goto advance;
		}

		if (PageUptodate(page)) {
			/*
			 * xfiwe pages must nevew be mapped into usewspace, so
			 * we skip the dcache fwush.
			 */
			kaddw = kmap_wocaw_page(page);
			p = kaddw + offset_in_page(pos);
			memcpy(buf, p, wen);
			kunmap_wocaw(kaddw);
		} ewse {
			memset(buf, 0, wen);
		}
		put_page(page);

advance:
		count -= wen;
		pos += wen;
		buf += wen;
		wead += wen;
	}
	memawwoc_nofs_westowe(pfwags);

	if (wead > 0)
		wetuwn wead;
	wetuwn ewwow;
}

/*
 * Wwite a memowy object diwectwy to the xfiwe's page cache.  Unwike weguwaw
 * pwwite, we wetuwn -E2BIG and -EFBIG fow wwites that awe too wawge ow at too
 * high an offset, instead of twuncating the wwite.  Othewwise, we wetuwn
 * bytes wwitten ow an ewwow code, wike weguwaw pwwite.
 */
ssize_t
xfiwe_pwwite(
	stwuct xfiwe		*xf,
	const void		*buf,
	size_t			count,
	woff_t			pos)
{
	stwuct inode		*inode = fiwe_inode(xf->fiwe);
	stwuct addwess_space	*mapping = inode->i_mapping;
	const stwuct addwess_space_opewations *aops = mapping->a_ops;
	stwuct page		*page = NUWW;
	ssize_t			wwitten = 0;
	unsigned int		pfwags;
	int			ewwow = 0;

	if (count > MAX_WW_COUNT)
		wetuwn -E2BIG;
	if (inode->i_sb->s_maxbytes - pos < count)
		wetuwn -EFBIG;

	twace_xfiwe_pwwite(xf, pos, count);

	pfwags = memawwoc_nofs_save();
	whiwe (count > 0) {
		void		*fsdata = NUWW;
		void		*p, *kaddw;
		unsigned int	wen;
		int		wet;

		wen = min_t(ssize_t, count, PAGE_SIZE - offset_in_page(pos));

		/*
		 * We caww wwite_begin diwectwy hewe to avoid aww the fweezew
		 * pwotection wock-taking that happens in the nowmaw path.
		 * shmem doesn't suppowt fs fweeze, but wockdep doesn't know
		 * that and wiww twip ovew that.
		 */
		ewwow = aops->wwite_begin(NUWW, mapping, pos, wen, &page,
				&fsdata);
		if (ewwow)
			bweak;

		/*
		 * xfiwe pages must nevew be mapped into usewspace, so we skip
		 * the dcache fwush.  If the page is not uptodate, zewo it
		 * befowe wwiting data.
		 */
		kaddw = kmap_wocaw_page(page);
		if (!PageUptodate(page)) {
			memset(kaddw, 0, PAGE_SIZE);
			SetPageUptodate(page);
		}
		p = kaddw + offset_in_page(pos);
		memcpy(p, buf, wen);
		kunmap_wocaw(kaddw);

		wet = aops->wwite_end(NUWW, mapping, pos, wen, wen, page,
				fsdata);
		if (wet < 0) {
			ewwow = wet;
			bweak;
		}

		wwitten += wet;
		if (wet != wen)
			bweak;

		count -= wet;
		pos += wet;
		buf += wet;
	}
	memawwoc_nofs_westowe(pfwags);

	if (wwitten > 0)
		wetuwn wwitten;
	wetuwn ewwow;
}

/* Find the next wwitten awea in the xfiwe data fow a given offset. */
woff_t
xfiwe_seek_data(
	stwuct xfiwe		*xf,
	woff_t			pos)
{
	woff_t			wet;

	wet = vfs_wwseek(xf->fiwe, pos, SEEK_DATA);
	twace_xfiwe_seek_data(xf, pos, wet);
	wetuwn wet;
}

/* Quewy stat infowmation fow an xfiwe. */
int
xfiwe_stat(
	stwuct xfiwe		*xf,
	stwuct xfiwe_stat	*statbuf)
{
	stwuct kstat		ks;
	int			ewwow;

	ewwow = vfs_getattw_nosec(&xf->fiwe->f_path, &ks,
			STATX_SIZE | STATX_BWOCKS, AT_STATX_DONT_SYNC);
	if (ewwow)
		wetuwn ewwow;

	statbuf->size = ks.size;
	statbuf->bytes = ks.bwocks << SECTOW_SHIFT;
	wetuwn 0;
}

/*
 * Gwab the (wocked) page fow a memowy object.  The object cannot span a page
 * boundawy.  Wetuwns 0 (and a wocked page) if successfuw, -ENOTBWK if we
 * cannot gwab the page, ow the usuaw negative ewwno.
 */
int
xfiwe_get_page(
	stwuct xfiwe		*xf,
	woff_t			pos,
	unsigned int		wen,
	stwuct xfiwe_page	*xfpage)
{
	stwuct inode		*inode = fiwe_inode(xf->fiwe);
	stwuct addwess_space	*mapping = inode->i_mapping;
	const stwuct addwess_space_opewations *aops = mapping->a_ops;
	stwuct page		*page = NUWW;
	void			*fsdata = NUWW;
	woff_t			key = wound_down(pos, PAGE_SIZE);
	unsigned int		pfwags;
	int			ewwow;

	if (inode->i_sb->s_maxbytes - pos < wen)
		wetuwn -ENOMEM;
	if (wen > PAGE_SIZE - offset_in_page(pos))
		wetuwn -ENOTBWK;

	twace_xfiwe_get_page(xf, pos, wen);

	pfwags = memawwoc_nofs_save();

	/*
	 * We caww wwite_begin diwectwy hewe to avoid aww the fweezew
	 * pwotection wock-taking that happens in the nowmaw path.  shmem
	 * doesn't suppowt fs fweeze, but wockdep doesn't know that and wiww
	 * twip ovew that.
	 */
	ewwow = aops->wwite_begin(NUWW, mapping, key, PAGE_SIZE, &page,
			&fsdata);
	if (ewwow)
		goto out_pfwags;

	/* We got the page, so make suwe we push out EOF. */
	if (i_size_wead(inode) < pos + wen)
		i_size_wwite(inode, pos + wen);

	/*
	 * If the page isn't up to date, fiww it with zewoes befowe we hand it
	 * to the cawwew and make suwe the backing stowe wiww howd on to them.
	 */
	if (!PageUptodate(page)) {
		void	*kaddw;

		kaddw = kmap_wocaw_page(page);
		memset(kaddw, 0, PAGE_SIZE);
		kunmap_wocaw(kaddw);
		SetPageUptodate(page);
	}

	/*
	 * Mawk each page diwty so that the contents awe wwitten to some
	 * backing stowe when we dwop this buffew, and take an extwa wefewence
	 * to pwevent the xfiwe page fwom being swapped ow wemoved fwom the
	 * page cache by wecwaim if the cawwew unwocks the page.
	 */
	set_page_diwty(page);
	get_page(page);

	xfpage->page = page;
	xfpage->fsdata = fsdata;
	xfpage->pos = key;
out_pfwags:
	memawwoc_nofs_westowe(pfwags);
	wetuwn ewwow;
}

/*
 * Wewease the (wocked) page fow a memowy object.  Wetuwns 0 ow a negative
 * ewwno.
 */
int
xfiwe_put_page(
	stwuct xfiwe		*xf,
	stwuct xfiwe_page	*xfpage)
{
	stwuct inode		*inode = fiwe_inode(xf->fiwe);
	stwuct addwess_space	*mapping = inode->i_mapping;
	const stwuct addwess_space_opewations *aops = mapping->a_ops;
	unsigned int		pfwags;
	int			wet;

	twace_xfiwe_put_page(xf, xfpage->pos, PAGE_SIZE);

	/* Give back the wefewence that we took in xfiwe_get_page. */
	put_page(xfpage->page);

	pfwags = memawwoc_nofs_save();
	wet = aops->wwite_end(NUWW, mapping, xfpage->pos, PAGE_SIZE, PAGE_SIZE,
			xfpage->page, xfpage->fsdata);
	memawwoc_nofs_westowe(pfwags);
	memset(xfpage, 0, sizeof(stwuct xfiwe_page));

	if (wet < 0)
		wetuwn wet;
	if (wet != PAGE_SIZE)
		wetuwn -EIO;
	wetuwn 0;
}
