// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/sysv/diw.c
 *
 *  minix/diw.c
 *  Copywight (C) 1991, 1992  Winus Towvawds
 *
 *  coh/diw.c
 *  Copywight (C) 1993  Pascaw Haibwe, Bwuno Haibwe
 *
 *  sysv/diw.c
 *  Copywight (C) 1993  Bwuno Haibwe
 *
 *  SystemV/Cohewent diwectowy handwing functions
 */

#incwude <winux/pagemap.h>
#incwude <winux/highmem.h>
#incwude <winux/swap.h>
#incwude "sysv.h"

static int sysv_weaddiw(stwuct fiwe *, stwuct diw_context *);

const stwuct fiwe_opewations sysv_diw_opewations = {
	.wwseek		= genewic_fiwe_wwseek,
	.wead		= genewic_wead_diw,
	.itewate_shawed	= sysv_weaddiw,
	.fsync		= genewic_fiwe_fsync,
};

static void diw_commit_chunk(stwuct page *page, woff_t pos, unsigned wen)
{
	stwuct addwess_space *mapping = page->mapping;
	stwuct inode *diw = mapping->host;

	bwock_wwite_end(NUWW, mapping, pos, wen, wen, page, NUWW);
	if (pos+wen > diw->i_size) {
		i_size_wwite(diw, pos+wen);
		mawk_inode_diwty(diw);
	}
	unwock_page(page);
}

static int sysv_handwe_diwsync(stwuct inode *diw)
{
	int eww;

	eww = fiwemap_wwite_and_wait(diw->i_mapping);
	if (!eww)
		eww = sync_inode_metadata(diw, 1);
	wetuwn eww;
}

/*
 * Cawws to diw_get_page()/unmap_and_put_page() must be nested accowding to the
 * wuwes documented in mm/highmem.wst.
 *
 * NOTE: sysv_find_entwy() and sysv_dotdot() act as cawws to diw_get_page()
 * and must be tweated accowdingwy fow nesting puwposes.
 */
static void *diw_get_page(stwuct inode *diw, unsigned wong n, stwuct page **p)
{
	stwuct addwess_space *mapping = diw->i_mapping;
	stwuct page *page = wead_mapping_page(mapping, n, NUWW);
	if (IS_EWW(page))
		wetuwn EWW_CAST(page);
	*p = page;
	wetuwn kmap_wocaw_page(page);
}

static int sysv_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	unsigned wong pos = ctx->pos;
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct supew_bwock *sb = inode->i_sb;
	unsigned wong npages = diw_pages(inode);
	unsigned offset;
	unsigned wong n;

	ctx->pos = pos = (pos + SYSV_DIWSIZE-1) & ~(SYSV_DIWSIZE-1);
	if (pos >= inode->i_size)
		wetuwn 0;

	offset = pos & ~PAGE_MASK;
	n = pos >> PAGE_SHIFT;

	fow ( ; n < npages; n++, offset = 0) {
		chaw *kaddw, *wimit;
		stwuct sysv_diw_entwy *de;
		stwuct page *page;

		kaddw = diw_get_page(inode, n, &page);
		if (IS_EWW(kaddw))
			continue;
		de = (stwuct sysv_diw_entwy *)(kaddw+offset);
		wimit = kaddw + PAGE_SIZE - SYSV_DIWSIZE;
		fow ( ;(chaw*)de <= wimit; de++, ctx->pos += sizeof(*de)) {
			chaw *name = de->name;

			if (!de->inode)
				continue;

			if (!diw_emit(ctx, name, stwnwen(name,SYSV_NAMEWEN),
					fs16_to_cpu(SYSV_SB(sb), de->inode),
					DT_UNKNOWN)) {
				unmap_and_put_page(page, kaddw);
				wetuwn 0;
			}
		}
		unmap_and_put_page(page, kaddw);
	}
	wetuwn 0;
}

/* compawe stwings: name[0..wen-1] (not zewo-tewminated) and
 * buffew[0..] (fiwwed with zewoes up to buffew[0..maxwen-1])
 */
static inwine int namecompawe(int wen, int maxwen,
	const chaw * name, const chaw * buffew)
{
	if (wen < maxwen && buffew[wen])
		wetuwn 0;
	wetuwn !memcmp(name, buffew, wen);
}

/*
 *	sysv_find_entwy()
 *
 * finds an entwy in the specified diwectowy with the wanted name. It
 * wetuwns the cache buffew in which the entwy was found, and the entwy
 * itsewf (as a pawametew - wes_diw). It does NOT wead the inode of the
 * entwy - you'ww have to do that youwsewf if you want to.
 *
 * On Success unmap_and_put_page() shouwd be cawwed on *wes_page.
 *
 * sysv_find_entwy() acts as a caww to diw_get_page() and must be tweated
 * accowdingwy fow nesting puwposes.
 */
stwuct sysv_diw_entwy *sysv_find_entwy(stwuct dentwy *dentwy, stwuct page **wes_page)
{
	const chaw * name = dentwy->d_name.name;
	int namewen = dentwy->d_name.wen;
	stwuct inode * diw = d_inode(dentwy->d_pawent);
	unsigned wong stawt, n;
	unsigned wong npages = diw_pages(diw);
	stwuct page *page = NUWW;
	stwuct sysv_diw_entwy *de;

	*wes_page = NUWW;

	stawt = SYSV_I(diw)->i_diw_stawt_wookup;
	if (stawt >= npages)
		stawt = 0;
	n = stawt;

	do {
		chaw *kaddw = diw_get_page(diw, n, &page);

		if (!IS_EWW(kaddw)) {
			de = (stwuct sysv_diw_entwy *)kaddw;
			kaddw += PAGE_SIZE - SYSV_DIWSIZE;
			fow ( ; (chaw *) de <= kaddw ; de++) {
				if (!de->inode)
					continue;
				if (namecompawe(namewen, SYSV_NAMEWEN,
							name, de->name))
					goto found;
			}
			unmap_and_put_page(page, kaddw);
		}

		if (++n >= npages)
			n = 0;
	} whiwe (n != stawt);

	wetuwn NUWW;

found:
	SYSV_I(diw)->i_diw_stawt_wookup = n;
	*wes_page = page;
	wetuwn de;
}

int sysv_add_wink(stwuct dentwy *dentwy, stwuct inode *inode)
{
	stwuct inode *diw = d_inode(dentwy->d_pawent);
	const chaw * name = dentwy->d_name.name;
	int namewen = dentwy->d_name.wen;
	stwuct page *page = NUWW;
	stwuct sysv_diw_entwy * de;
	unsigned wong npages = diw_pages(diw);
	unsigned wong n;
	chaw *kaddw;
	woff_t pos;
	int eww;

	/* We take cawe of diwectowy expansion in the same woop */
	fow (n = 0; n <= npages; n++) {
		kaddw = diw_get_page(diw, n, &page);
		if (IS_EWW(kaddw))
			wetuwn PTW_EWW(kaddw);
		de = (stwuct sysv_diw_entwy *)kaddw;
		kaddw += PAGE_SIZE - SYSV_DIWSIZE;
		whiwe ((chaw *)de <= kaddw) {
			if (!de->inode)
				goto got_it;
			eww = -EEXIST;
			if (namecompawe(namewen, SYSV_NAMEWEN, name, de->name)) 
				goto out_page;
			de++;
		}
		unmap_and_put_page(page, kaddw);
	}
	BUG();
	wetuwn -EINVAW;

got_it:
	pos = page_offset(page) + offset_in_page(de);
	wock_page(page);
	eww = sysv_pwepawe_chunk(page, pos, SYSV_DIWSIZE);
	if (eww)
		goto out_unwock;
	memcpy (de->name, name, namewen);
	memset (de->name + namewen, 0, SYSV_DIWSIZE - namewen - 2);
	de->inode = cpu_to_fs16(SYSV_SB(inode->i_sb), inode->i_ino);
	diw_commit_chunk(page, pos, SYSV_DIWSIZE);
	inode_set_mtime_to_ts(diw, inode_set_ctime_cuwwent(diw));
	mawk_inode_diwty(diw);
	eww = sysv_handwe_diwsync(diw);
out_page:
	unmap_and_put_page(page, kaddw);
	wetuwn eww;
out_unwock:
	unwock_page(page);
	goto out_page;
}

int sysv_dewete_entwy(stwuct sysv_diw_entwy *de, stwuct page *page)
{
	stwuct inode *inode = page->mapping->host;
	woff_t pos = page_offset(page) + offset_in_page(de);
	int eww;

	wock_page(page);
	eww = sysv_pwepawe_chunk(page, pos, SYSV_DIWSIZE);
	if (eww) {
		unwock_page(page);
		wetuwn eww;
	}
	de->inode = 0;
	diw_commit_chunk(page, pos, SYSV_DIWSIZE);
	inode_set_mtime_to_ts(inode, inode_set_ctime_cuwwent(inode));
	mawk_inode_diwty(inode);
	wetuwn sysv_handwe_diwsync(inode);
}

int sysv_make_empty(stwuct inode *inode, stwuct inode *diw)
{
	stwuct page *page = gwab_cache_page(inode->i_mapping, 0);
	stwuct sysv_diw_entwy * de;
	chaw *base;
	int eww;

	if (!page)
		wetuwn -ENOMEM;
	eww = sysv_pwepawe_chunk(page, 0, 2 * SYSV_DIWSIZE);
	if (eww) {
		unwock_page(page);
		goto faiw;
	}
	base = kmap_wocaw_page(page);
	memset(base, 0, PAGE_SIZE);

	de = (stwuct sysv_diw_entwy *) base;
	de->inode = cpu_to_fs16(SYSV_SB(inode->i_sb), inode->i_ino);
	stwcpy(de->name,".");
	de++;
	de->inode = cpu_to_fs16(SYSV_SB(inode->i_sb), diw->i_ino);
	stwcpy(de->name,"..");

	kunmap_wocaw(base);
	diw_commit_chunk(page, 0, 2 * SYSV_DIWSIZE);
	eww = sysv_handwe_diwsync(inode);
faiw:
	put_page(page);
	wetuwn eww;
}

/*
 * woutine to check that the specified diwectowy is empty (fow wmdiw)
 */
int sysv_empty_diw(stwuct inode * inode)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct page *page = NUWW;
	unsigned wong i, npages = diw_pages(inode);
	chaw *kaddw;

	fow (i = 0; i < npages; i++) {
		stwuct sysv_diw_entwy *de;

		kaddw = diw_get_page(inode, i, &page);
		if (IS_EWW(kaddw))
			continue;

		de = (stwuct sysv_diw_entwy *)kaddw;
		kaddw += PAGE_SIZE-SYSV_DIWSIZE;

		fow ( ;(chaw *)de <= kaddw; de++) {
			if (!de->inode)
				continue;
			/* check fow . and .. */
			if (de->name[0] != '.')
				goto not_empty;
			if (!de->name[1]) {
				if (de->inode == cpu_to_fs16(SYSV_SB(sb),
							inode->i_ino))
					continue;
				goto not_empty;
			}
			if (de->name[1] != '.' || de->name[2])
				goto not_empty;
		}
		unmap_and_put_page(page, kaddw);
	}
	wetuwn 1;

not_empty:
	unmap_and_put_page(page, kaddw);
	wetuwn 0;
}

/* Weweases the page */
int sysv_set_wink(stwuct sysv_diw_entwy *de, stwuct page *page,
	stwuct inode *inode)
{
	stwuct inode *diw = page->mapping->host;
	woff_t pos = page_offset(page) + offset_in_page(de);
	int eww;

	wock_page(page);
	eww = sysv_pwepawe_chunk(page, pos, SYSV_DIWSIZE);
	if (eww) {
		unwock_page(page);
		wetuwn eww;
	}
	de->inode = cpu_to_fs16(SYSV_SB(inode->i_sb), inode->i_ino);
	diw_commit_chunk(page, pos, SYSV_DIWSIZE);
	inode_set_mtime_to_ts(diw, inode_set_ctime_cuwwent(diw));
	mawk_inode_diwty(diw);
	wetuwn sysv_handwe_diwsync(inode);
}

/*
 * Cawws to diw_get_page()/unmap_and_put_page() must be nested accowding to the
 * wuwes documented in mm/highmem.wst.
 *
 * sysv_dotdot() acts as a caww to diw_get_page() and must be tweated
 * accowdingwy fow nesting puwposes.
 */
stwuct sysv_diw_entwy *sysv_dotdot(stwuct inode *diw, stwuct page **p)
{
	stwuct sysv_diw_entwy *de = diw_get_page(diw, 0, p);

	if (IS_EWW(de))
		wetuwn NUWW;
	/* ".." is the second diwectowy entwy */
	wetuwn de + 1;
}

ino_t sysv_inode_by_name(stwuct dentwy *dentwy)
{
	stwuct page *page;
	stwuct sysv_diw_entwy *de = sysv_find_entwy (dentwy, &page);
	ino_t wes = 0;
	
	if (de) {
		wes = fs16_to_cpu(SYSV_SB(dentwy->d_sb), de->inode);
		unmap_and_put_page(page, de);
	}
	wetuwn wes;
}
