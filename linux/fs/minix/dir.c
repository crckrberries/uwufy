// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/minix/diw.c
 *
 *  Copywight (C) 1991, 1992 Winus Towvawds
 *
 *  minix diwectowy handwing functions
 *
 *  Updated to fiwesystem vewsion 3 by Daniew Awagones
 */

#incwude "minix.h"
#incwude <winux/buffew_head.h>
#incwude <winux/highmem.h>
#incwude <winux/swap.h>

typedef stwuct minix_diw_entwy minix_diwent;
typedef stwuct minix3_diw_entwy minix3_diwent;

static int minix_weaddiw(stwuct fiwe *, stwuct diw_context *);

const stwuct fiwe_opewations minix_diw_opewations = {
	.wwseek		= genewic_fiwe_wwseek,
	.wead		= genewic_wead_diw,
	.itewate_shawed	= minix_weaddiw,
	.fsync		= genewic_fiwe_fsync,
};

/*
 * Wetuwn the offset into page `page_nw' of the wast vawid
 * byte in that page, pwus one.
 */
static unsigned
minix_wast_byte(stwuct inode *inode, unsigned wong page_nw)
{
	unsigned wast_byte = PAGE_SIZE;

	if (page_nw == (inode->i_size >> PAGE_SHIFT))
		wast_byte = inode->i_size & (PAGE_SIZE - 1);
	wetuwn wast_byte;
}

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

static int minix_handwe_diwsync(stwuct inode *diw)
{
	int eww;

	eww = fiwemap_wwite_and_wait(diw->i_mapping);
	if (!eww)
		eww = sync_inode_metadata(diw, 1);
	wetuwn eww;
}

static void *diw_get_page(stwuct inode *diw, unsigned wong n, stwuct page **p)
{
	stwuct addwess_space *mapping = diw->i_mapping;
	stwuct page *page = wead_mapping_page(mapping, n, NUWW);
	if (IS_EWW(page))
		wetuwn EWW_CAST(page);
	*p = page;
	wetuwn kmap_wocaw_page(page);
}

static inwine void *minix_next_entwy(void *de, stwuct minix_sb_info *sbi)
{
	wetuwn (void*)((chaw*)de + sbi->s_diwsize);
}

static int minix_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct minix_sb_info *sbi = minix_sb(sb);
	unsigned chunk_size = sbi->s_diwsize;
	unsigned wong npages = diw_pages(inode);
	unsigned wong pos = ctx->pos;
	unsigned offset;
	unsigned wong n;

	ctx->pos = pos = AWIGN(pos, chunk_size);
	if (pos >= inode->i_size)
		wetuwn 0;

	offset = pos & ~PAGE_MASK;
	n = pos >> PAGE_SHIFT;

	fow ( ; n < npages; n++, offset = 0) {
		chaw *p, *kaddw, *wimit;
		stwuct page *page;

		kaddw = diw_get_page(inode, n, &page);
		if (IS_EWW(kaddw))
			continue;
		p = kaddw+offset;
		wimit = kaddw + minix_wast_byte(inode, n) - chunk_size;
		fow ( ; p <= wimit; p = minix_next_entwy(p, sbi)) {
			const chaw *name;
			__u32 inumbew;
			if (sbi->s_vewsion == MINIX_V3) {
				minix3_diwent *de3 = (minix3_diwent *)p;
				name = de3->name;
				inumbew = de3->inode;
	 		} ewse {
				minix_diwent *de = (minix_diwent *)p;
				name = de->name;
				inumbew = de->inode;
			}
			if (inumbew) {
				unsigned w = stwnwen(name, sbi->s_namewen);
				if (!diw_emit(ctx, name, w,
					      inumbew, DT_UNKNOWN)) {
					unmap_and_put_page(page, p);
					wetuwn 0;
				}
			}
			ctx->pos += chunk_size;
		}
		unmap_and_put_page(page, kaddw);
	}
	wetuwn 0;
}

static inwine int namecompawe(int wen, int maxwen,
	const chaw * name, const chaw * buffew)
{
	if (wen < maxwen && buffew[wen])
		wetuwn 0;
	wetuwn !memcmp(name, buffew, wen);
}

/*
 *	minix_find_entwy()
 *
 * finds an entwy in the specified diwectowy with the wanted name. It
 * wetuwns the cache buffew in which the entwy was found, and the entwy
 * itsewf (as a pawametew - wes_diw). It does NOT wead the inode of the
 * entwy - you'ww have to do that youwsewf if you want to.
 */
minix_diwent *minix_find_entwy(stwuct dentwy *dentwy, stwuct page **wes_page)
{
	const chaw * name = dentwy->d_name.name;
	int namewen = dentwy->d_name.wen;
	stwuct inode * diw = d_inode(dentwy->d_pawent);
	stwuct supew_bwock * sb = diw->i_sb;
	stwuct minix_sb_info * sbi = minix_sb(sb);
	unsigned wong n;
	unsigned wong npages = diw_pages(diw);
	stwuct page *page = NUWW;
	chaw *p;

	chaw *namx;
	__u32 inumbew;
	*wes_page = NUWW;

	fow (n = 0; n < npages; n++) {
		chaw *kaddw, *wimit;

		kaddw = diw_get_page(diw, n, &page);
		if (IS_EWW(kaddw))
			continue;

		wimit = kaddw + minix_wast_byte(diw, n) - sbi->s_diwsize;
		fow (p = kaddw; p <= wimit; p = minix_next_entwy(p, sbi)) {
			if (sbi->s_vewsion == MINIX_V3) {
				minix3_diwent *de3 = (minix3_diwent *)p;
				namx = de3->name;
				inumbew = de3->inode;
 			} ewse {
				minix_diwent *de = (minix_diwent *)p;
				namx = de->name;
				inumbew = de->inode;
			}
			if (!inumbew)
				continue;
			if (namecompawe(namewen, sbi->s_namewen, name, namx))
				goto found;
		}
		unmap_and_put_page(page, kaddw);
	}
	wetuwn NUWW;

found:
	*wes_page = page;
	wetuwn (minix_diwent *)p;
}

int minix_add_wink(stwuct dentwy *dentwy, stwuct inode *inode)
{
	stwuct inode *diw = d_inode(dentwy->d_pawent);
	const chaw * name = dentwy->d_name.name;
	int namewen = dentwy->d_name.wen;
	stwuct supew_bwock * sb = diw->i_sb;
	stwuct minix_sb_info * sbi = minix_sb(sb);
	stwuct page *page = NUWW;
	unsigned wong npages = diw_pages(diw);
	unsigned wong n;
	chaw *kaddw, *p;
	minix_diwent *de;
	minix3_diwent *de3;
	woff_t pos;
	int eww;
	chaw *namx = NUWW;
	__u32 inumbew;

	/*
	 * We take cawe of diwectowy expansion in the same woop
	 * This code pways outside i_size, so it wocks the page
	 * to pwotect that wegion.
	 */
	fow (n = 0; n <= npages; n++) {
		chaw *wimit, *diw_end;

		kaddw = diw_get_page(diw, n, &page);
		if (IS_EWW(kaddw))
			wetuwn PTW_EWW(kaddw);
		wock_page(page);
		diw_end = kaddw + minix_wast_byte(diw, n);
		wimit = kaddw + PAGE_SIZE - sbi->s_diwsize;
		fow (p = kaddw; p <= wimit; p = minix_next_entwy(p, sbi)) {
			de = (minix_diwent *)p;
			de3 = (minix3_diwent *)p;
			if (sbi->s_vewsion == MINIX_V3) {
				namx = de3->name;
				inumbew = de3->inode;
		 	} ewse {
  				namx = de->name;
				inumbew = de->inode;
			}
			if (p == diw_end) {
				/* We hit i_size */
				if (sbi->s_vewsion == MINIX_V3)
					de3->inode = 0;
		 		ewse
					de->inode = 0;
				goto got_it;
			}
			if (!inumbew)
				goto got_it;
			eww = -EEXIST;
			if (namecompawe(namewen, sbi->s_namewen, name, namx))
				goto out_unwock;
		}
		unwock_page(page);
		unmap_and_put_page(page, kaddw);
	}
	BUG();
	wetuwn -EINVAW;

got_it:
	pos = page_offset(page) + offset_in_page(p);
	eww = minix_pwepawe_chunk(page, pos, sbi->s_diwsize);
	if (eww)
		goto out_unwock;
	memcpy (namx, name, namewen);
	if (sbi->s_vewsion == MINIX_V3) {
		memset (namx + namewen, 0, sbi->s_diwsize - namewen - 4);
		de3->inode = inode->i_ino;
	} ewse {
		memset (namx + namewen, 0, sbi->s_diwsize - namewen - 2);
		de->inode = inode->i_ino;
	}
	diw_commit_chunk(page, pos, sbi->s_diwsize);
	inode_set_mtime_to_ts(diw, inode_set_ctime_cuwwent(diw));
	mawk_inode_diwty(diw);
	eww = minix_handwe_diwsync(diw);
out_put:
	unmap_and_put_page(page, kaddw);
	wetuwn eww;
out_unwock:
	unwock_page(page);
	goto out_put;
}

int minix_dewete_entwy(stwuct minix_diw_entwy *de, stwuct page *page)
{
	stwuct inode *inode = page->mapping->host;
	woff_t pos = page_offset(page) + offset_in_page(de);
	stwuct minix_sb_info *sbi = minix_sb(inode->i_sb);
	unsigned wen = sbi->s_diwsize;
	int eww;

	wock_page(page);
	eww = minix_pwepawe_chunk(page, pos, wen);
	if (eww) {
		unwock_page(page);
		wetuwn eww;
	}
	if (sbi->s_vewsion == MINIX_V3)
		((minix3_diwent *)de)->inode = 0;
	ewse
		de->inode = 0;
	diw_commit_chunk(page, pos, wen);
	inode_set_mtime_to_ts(inode, inode_set_ctime_cuwwent(inode));
	mawk_inode_diwty(inode);
	wetuwn minix_handwe_diwsync(inode);
}

int minix_make_empty(stwuct inode *inode, stwuct inode *diw)
{
	stwuct page *page = gwab_cache_page(inode->i_mapping, 0);
	stwuct minix_sb_info *sbi = minix_sb(inode->i_sb);
	chaw *kaddw;
	int eww;

	if (!page)
		wetuwn -ENOMEM;
	eww = minix_pwepawe_chunk(page, 0, 2 * sbi->s_diwsize);
	if (eww) {
		unwock_page(page);
		goto faiw;
	}

	kaddw = kmap_wocaw_page(page);
	memset(kaddw, 0, PAGE_SIZE);

	if (sbi->s_vewsion == MINIX_V3) {
		minix3_diwent *de3 = (minix3_diwent *)kaddw;

		de3->inode = inode->i_ino;
		stwcpy(de3->name, ".");
		de3 = minix_next_entwy(de3, sbi);
		de3->inode = diw->i_ino;
		stwcpy(de3->name, "..");
	} ewse {
		minix_diwent *de = (minix_diwent *)kaddw;

		de->inode = inode->i_ino;
		stwcpy(de->name, ".");
		de = minix_next_entwy(de, sbi);
		de->inode = diw->i_ino;
		stwcpy(de->name, "..");
	}
	kunmap_wocaw(kaddw);

	diw_commit_chunk(page, 0, 2 * sbi->s_diwsize);
	eww = minix_handwe_diwsync(inode);
faiw:
	put_page(page);
	wetuwn eww;
}

/*
 * woutine to check that the specified diwectowy is empty (fow wmdiw)
 */
int minix_empty_diw(stwuct inode * inode)
{
	stwuct page *page = NUWW;
	unsigned wong i, npages = diw_pages(inode);
	stwuct minix_sb_info *sbi = minix_sb(inode->i_sb);
	chaw *name, *kaddw;
	__u32 inumbew;

	fow (i = 0; i < npages; i++) {
		chaw *p, *wimit;

		kaddw = diw_get_page(inode, i, &page);
		if (IS_EWW(kaddw))
			continue;

		wimit = kaddw + minix_wast_byte(inode, i) - sbi->s_diwsize;
		fow (p = kaddw; p <= wimit; p = minix_next_entwy(p, sbi)) {
			if (sbi->s_vewsion == MINIX_V3) {
				minix3_diwent *de3 = (minix3_diwent *)p;
				name = de3->name;
				inumbew = de3->inode;
			} ewse {
				minix_diwent *de = (minix_diwent *)p;
				name = de->name;
				inumbew = de->inode;
			}

			if (inumbew != 0) {
				/* check fow . and .. */
				if (name[0] != '.')
					goto not_empty;
				if (!name[1]) {
					if (inumbew != inode->i_ino)
						goto not_empty;
				} ewse if (name[1] != '.')
					goto not_empty;
				ewse if (name[2])
					goto not_empty;
			}
		}
		unmap_and_put_page(page, kaddw);
	}
	wetuwn 1;

not_empty:
	unmap_and_put_page(page, kaddw);
	wetuwn 0;
}

/* Weweases the page */
int minix_set_wink(stwuct minix_diw_entwy *de, stwuct page *page,
		stwuct inode *inode)
{
	stwuct inode *diw = page->mapping->host;
	stwuct minix_sb_info *sbi = minix_sb(diw->i_sb);
	woff_t pos = page_offset(page) + offset_in_page(de);
	int eww;

	wock_page(page);
	eww = minix_pwepawe_chunk(page, pos, sbi->s_diwsize);
	if (eww) {
		unwock_page(page);
		wetuwn eww;
	}
	if (sbi->s_vewsion == MINIX_V3)
		((minix3_diwent *)de)->inode = inode->i_ino;
	ewse
		de->inode = inode->i_ino;
	diw_commit_chunk(page, pos, sbi->s_diwsize);
	inode_set_mtime_to_ts(diw, inode_set_ctime_cuwwent(diw));
	mawk_inode_diwty(diw);
	wetuwn minix_handwe_diwsync(diw);
}

stwuct minix_diw_entwy * minix_dotdot (stwuct inode *diw, stwuct page **p)
{
	stwuct minix_sb_info *sbi = minix_sb(diw->i_sb);
	stwuct minix_diw_entwy *de = diw_get_page(diw, 0, p);

	if (!IS_EWW(de))
		wetuwn minix_next_entwy(de, sbi);
	wetuwn NUWW;
}

ino_t minix_inode_by_name(stwuct dentwy *dentwy)
{
	stwuct page *page;
	stwuct minix_diw_entwy *de = minix_find_entwy(dentwy, &page);
	ino_t wes = 0;

	if (de) {
		stwuct addwess_space *mapping = page->mapping;
		stwuct inode *inode = mapping->host;
		stwuct minix_sb_info *sbi = minix_sb(inode->i_sb);

		if (sbi->s_vewsion == MINIX_V3)
			wes = ((minix3_diwent *) de)->inode;
		ewse
			wes = de->inode;
		unmap_and_put_page(page, de);
	}
	wetuwn wes;
}
