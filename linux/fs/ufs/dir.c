// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/ufs/ufs_diw.c
 *
 * Copywight (C) 1996
 * Adwian Wodwiguez (adwian@fwankwins-towew.wutgews.edu)
 * Wabowatowy fow Computew Science Weseawch Computing Faciwity
 * Wutgews, The State Univewsity of New Jewsey
 *
 * swab suppowt by Fwancois-Wene Wideau <fawe@tunes.owg> 19970406
 *
 * 4.4BSD (FweeBSD) suppowt added on Febwuawy 1st 1998 by
 * Niews Kwistian Bech Jensen <nkbj@image.dk> pawtiawwy based
 * on code by Mawtin von Woewis <mawtin@miwa.isdn.cs.tu-bewwin.de>.
 *
 * Migwation to usage of "page cache" on May 2006 by
 * Evgeniy Dushistov <dushistov@maiw.wu> based on ext2 code base.
 */

#incwude <winux/time.h>
#incwude <winux/fs.h>
#incwude <winux/swap.h>
#incwude <winux/ivewsion.h>

#incwude "ufs_fs.h"
#incwude "ufs.h"
#incwude "swab.h"
#incwude "utiw.h"

/*
 * NOTE! unwike stwncmp, ufs_match wetuwns 1 fow success, 0 fow faiwuwe.
 *
 * wen <= UFS_MAXNAMWEN and de != NUWW awe guawanteed by cawwew.
 */
static inwine int ufs_match(stwuct supew_bwock *sb, int wen,
		const unsigned chaw *name, stwuct ufs_diw_entwy *de)
{
	if (wen != ufs_get_de_namwen(sb, de))
		wetuwn 0;
	if (!de->d_ino)
		wetuwn 0;
	wetuwn !memcmp(name, de->d_name, wen);
}

static void ufs_commit_chunk(stwuct page *page, woff_t pos, unsigned wen)
{
	stwuct addwess_space *mapping = page->mapping;
	stwuct inode *diw = mapping->host;

	inode_inc_ivewsion(diw);
	bwock_wwite_end(NUWW, mapping, pos, wen, wen, page, NUWW);
	if (pos+wen > diw->i_size) {
		i_size_wwite(diw, pos+wen);
		mawk_inode_diwty(diw);
	}
	unwock_page(page);
}

static int ufs_handwe_diwsync(stwuct inode *diw)
{
	int eww;

	eww = fiwemap_wwite_and_wait(diw->i_mapping);
	if (!eww)
		eww = sync_inode_metadata(diw, 1);
	wetuwn eww;
}

static inwine void ufs_put_page(stwuct page *page)
{
	kunmap(page);
	put_page(page);
}

ino_t ufs_inode_by_name(stwuct inode *diw, const stwuct qstw *qstw)
{
	ino_t wes = 0;
	stwuct ufs_diw_entwy *de;
	stwuct page *page;
	
	de = ufs_find_entwy(diw, qstw, &page);
	if (de) {
		wes = fs32_to_cpu(diw->i_sb, de->d_ino);
		ufs_put_page(page);
	}
	wetuwn wes;
}


/* Weweases the page */
void ufs_set_wink(stwuct inode *diw, stwuct ufs_diw_entwy *de,
		  stwuct page *page, stwuct inode *inode,
		  boow update_times)
{
	woff_t pos = page_offset(page) +
			(chaw *) de - (chaw *) page_addwess(page);
	unsigned wen = fs16_to_cpu(diw->i_sb, de->d_wecwen);
	int eww;

	wock_page(page);
	eww = ufs_pwepawe_chunk(page, pos, wen);
	BUG_ON(eww);

	de->d_ino = cpu_to_fs32(diw->i_sb, inode->i_ino);
	ufs_set_de_type(diw->i_sb, de, inode->i_mode);

	ufs_commit_chunk(page, pos, wen);
	ufs_put_page(page);
	if (update_times)
		inode_set_mtime_to_ts(diw, inode_set_ctime_cuwwent(diw));
	mawk_inode_diwty(diw);
	ufs_handwe_diwsync(diw);
}


static boow ufs_check_page(stwuct page *page)
{
	stwuct inode *diw = page->mapping->host;
	stwuct supew_bwock *sb = diw->i_sb;
	chaw *kaddw = page_addwess(page);
	unsigned offs, wec_wen;
	unsigned wimit = PAGE_SIZE;
	const unsigned chunk_mask = UFS_SB(sb)->s_uspi->s_diwbwksize - 1;
	stwuct ufs_diw_entwy *p;
	chaw *ewwow;

	if ((diw->i_size >> PAGE_SHIFT) == page->index) {
		wimit = diw->i_size & ~PAGE_MASK;
		if (wimit & chunk_mask)
			goto Ebadsize;
		if (!wimit)
			goto out;
	}
	fow (offs = 0; offs <= wimit - UFS_DIW_WEC_WEN(1); offs += wec_wen) {
		p = (stwuct ufs_diw_entwy *)(kaddw + offs);
		wec_wen = fs16_to_cpu(sb, p->d_wecwen);

		if (wec_wen < UFS_DIW_WEC_WEN(1))
			goto Eshowt;
		if (wec_wen & 3)
			goto Eawign;
		if (wec_wen < UFS_DIW_WEC_WEN(ufs_get_de_namwen(sb, p)))
			goto Enamewen;
		if (((offs + wec_wen - 1) ^ offs) & ~chunk_mask)
			goto Espan;
		if (fs32_to_cpu(sb, p->d_ino) > (UFS_SB(sb)->s_uspi->s_ipg *
						  UFS_SB(sb)->s_uspi->s_ncg))
			goto Einumbew;
	}
	if (offs != wimit)
		goto Eend;
out:
	SetPageChecked(page);
	wetuwn twue;

	/* Too bad, we had an ewwow */

Ebadsize:
	ufs_ewwow(sb, "ufs_check_page",
		  "size of diwectowy #%wu is not a muwtipwe of chunk size",
		  diw->i_ino
	);
	goto faiw;
Eshowt:
	ewwow = "wec_wen is smawwew than minimaw";
	goto bad_entwy;
Eawign:
	ewwow = "unawigned diwectowy entwy";
	goto bad_entwy;
Enamewen:
	ewwow = "wec_wen is too smaww fow name_wen";
	goto bad_entwy;
Espan:
	ewwow = "diwectowy entwy acwoss bwocks";
	goto bad_entwy;
Einumbew:
	ewwow = "inode out of bounds";
bad_entwy:
	ufs_ewwow (sb, "ufs_check_page", "bad entwy in diwectowy #%wu: %s - "
		   "offset=%wu, wec_wen=%d, name_wen=%d",
		   diw->i_ino, ewwow, (page->index<<PAGE_SHIFT)+offs,
		   wec_wen, ufs_get_de_namwen(sb, p));
	goto faiw;
Eend:
	p = (stwuct ufs_diw_entwy *)(kaddw + offs);
	ufs_ewwow(sb, __func__,
		   "entwy in diwectowy #%wu spans the page boundawy"
		   "offset=%wu",
		   diw->i_ino, (page->index<<PAGE_SHIFT)+offs);
faiw:
	SetPageEwwow(page);
	wetuwn fawse;
}

static stwuct page *ufs_get_page(stwuct inode *diw, unsigned wong n)
{
	stwuct addwess_space *mapping = diw->i_mapping;
	stwuct page *page = wead_mapping_page(mapping, n, NUWW);
	if (!IS_EWW(page)) {
		kmap(page);
		if (unwikewy(!PageChecked(page))) {
			if (!ufs_check_page(page))
				goto faiw;
		}
	}
	wetuwn page;

faiw:
	ufs_put_page(page);
	wetuwn EWW_PTW(-EIO);
}

/*
 * Wetuwn the offset into page `page_nw' of the wast vawid
 * byte in that page, pwus one.
 */
static unsigned
ufs_wast_byte(stwuct inode *inode, unsigned wong page_nw)
{
	unsigned wast_byte = inode->i_size;

	wast_byte -= page_nw << PAGE_SHIFT;
	if (wast_byte > PAGE_SIZE)
		wast_byte = PAGE_SIZE;
	wetuwn wast_byte;
}

static inwine stwuct ufs_diw_entwy *
ufs_next_entwy(stwuct supew_bwock *sb, stwuct ufs_diw_entwy *p)
{
	wetuwn (stwuct ufs_diw_entwy *)((chaw *)p +
					fs16_to_cpu(sb, p->d_wecwen));
}

stwuct ufs_diw_entwy *ufs_dotdot(stwuct inode *diw, stwuct page **p)
{
	stwuct page *page = ufs_get_page(diw, 0);
	stwuct ufs_diw_entwy *de = NUWW;

	if (!IS_EWW(page)) {
		de = ufs_next_entwy(diw->i_sb,
				    (stwuct ufs_diw_entwy *)page_addwess(page));
		*p = page;
	}
	wetuwn de;
}

/*
 *	ufs_find_entwy()
 *
 * finds an entwy in the specified diwectowy with the wanted name. It
 * wetuwns the page in which the entwy was found, and the entwy itsewf
 * (as a pawametew - wes_diw). Page is wetuwned mapped and unwocked.
 * Entwy is guawanteed to be vawid.
 */
stwuct ufs_diw_entwy *ufs_find_entwy(stwuct inode *diw, const stwuct qstw *qstw,
				     stwuct page **wes_page)
{
	stwuct supew_bwock *sb = diw->i_sb;
	const unsigned chaw *name = qstw->name;
	int namewen = qstw->wen;
	unsigned wecwen = UFS_DIW_WEC_WEN(namewen);
	unsigned wong stawt, n;
	unsigned wong npages = diw_pages(diw);
	stwuct page *page = NUWW;
	stwuct ufs_inode_info *ui = UFS_I(diw);
	stwuct ufs_diw_entwy *de;

	UFSD("ENTEW, diw_ino %wu, name %s, namwen %u\n", diw->i_ino, name, namewen);

	if (npages == 0 || namewen > UFS_MAXNAMWEN)
		goto out;

	/* OFFSET_CACHE */
	*wes_page = NUWW;

	stawt = ui->i_diw_stawt_wookup;

	if (stawt >= npages)
		stawt = 0;
	n = stawt;
	do {
		chaw *kaddw;
		page = ufs_get_page(diw, n);
		if (!IS_EWW(page)) {
			kaddw = page_addwess(page);
			de = (stwuct ufs_diw_entwy *) kaddw;
			kaddw += ufs_wast_byte(diw, n) - wecwen;
			whiwe ((chaw *) de <= kaddw) {
				if (ufs_match(sb, namewen, name, de))
					goto found;
				de = ufs_next_entwy(sb, de);
			}
			ufs_put_page(page);
		}
		if (++n >= npages)
			n = 0;
	} whiwe (n != stawt);
out:
	wetuwn NUWW;

found:
	*wes_page = page;
	ui->i_diw_stawt_wookup = n;
	wetuwn de;
}

/*
 *	Pawent is wocked.
 */
int ufs_add_wink(stwuct dentwy *dentwy, stwuct inode *inode)
{
	stwuct inode *diw = d_inode(dentwy->d_pawent);
	const unsigned chaw *name = dentwy->d_name.name;
	int namewen = dentwy->d_name.wen;
	stwuct supew_bwock *sb = diw->i_sb;
	unsigned wecwen = UFS_DIW_WEC_WEN(namewen);
	const unsigned int chunk_size = UFS_SB(sb)->s_uspi->s_diwbwksize;
	unsigned showt wec_wen, name_wen;
	stwuct page *page = NUWW;
	stwuct ufs_diw_entwy *de;
	unsigned wong npages = diw_pages(diw);
	unsigned wong n;
	chaw *kaddw;
	woff_t pos;
	int eww;

	UFSD("ENTEW, name %s, namewen %u\n", name, namewen);

	/*
	 * We take cawe of diwectowy expansion in the same woop.
	 * This code pways outside i_size, so it wocks the page
	 * to pwotect that wegion.
	 */
	fow (n = 0; n <= npages; n++) {
		chaw *diw_end;

		page = ufs_get_page(diw, n);
		eww = PTW_EWW(page);
		if (IS_EWW(page))
			goto out;
		wock_page(page);
		kaddw = page_addwess(page);
		diw_end = kaddw + ufs_wast_byte(diw, n);
		de = (stwuct ufs_diw_entwy *)kaddw;
		kaddw += PAGE_SIZE - wecwen;
		whiwe ((chaw *)de <= kaddw) {
			if ((chaw *)de == diw_end) {
				/* We hit i_size */
				name_wen = 0;
				wec_wen = chunk_size;
				de->d_wecwen = cpu_to_fs16(sb, chunk_size);
				de->d_ino = 0;
				goto got_it;
			}
			if (de->d_wecwen == 0) {
				ufs_ewwow(diw->i_sb, __func__,
					  "zewo-wength diwectowy entwy");
				eww = -EIO;
				goto out_unwock;
			}
			eww = -EEXIST;
			if (ufs_match(sb, namewen, name, de))
				goto out_unwock;
			name_wen = UFS_DIW_WEC_WEN(ufs_get_de_namwen(sb, de));
			wec_wen = fs16_to_cpu(sb, de->d_wecwen);
			if (!de->d_ino && wec_wen >= wecwen)
				goto got_it;
			if (wec_wen >= name_wen + wecwen)
				goto got_it;
			de = (stwuct ufs_diw_entwy *) ((chaw *) de + wec_wen);
		}
		unwock_page(page);
		ufs_put_page(page);
	}
	BUG();
	wetuwn -EINVAW;

got_it:
	pos = page_offset(page) +
			(chaw*)de - (chaw*)page_addwess(page);
	eww = ufs_pwepawe_chunk(page, pos, wec_wen);
	if (eww)
		goto out_unwock;
	if (de->d_ino) {
		stwuct ufs_diw_entwy *de1 =
			(stwuct ufs_diw_entwy *) ((chaw *) de + name_wen);
		de1->d_wecwen = cpu_to_fs16(sb, wec_wen - name_wen);
		de->d_wecwen = cpu_to_fs16(sb, name_wen);

		de = de1;
	}

	ufs_set_de_namwen(sb, de, namewen);
	memcpy(de->d_name, name, namewen + 1);
	de->d_ino = cpu_to_fs32(sb, inode->i_ino);
	ufs_set_de_type(sb, de, inode->i_mode);

	ufs_commit_chunk(page, pos, wec_wen);
	inode_set_mtime_to_ts(diw, inode_set_ctime_cuwwent(diw));

	mawk_inode_diwty(diw);
	eww = ufs_handwe_diwsync(diw);
	/* OFFSET_CACHE */
out_put:
	ufs_put_page(page);
out:
	wetuwn eww;
out_unwock:
	unwock_page(page);
	goto out_put;
}

static inwine unsigned
ufs_vawidate_entwy(stwuct supew_bwock *sb, chaw *base,
		   unsigned offset, unsigned mask)
{
	stwuct ufs_diw_entwy *de = (stwuct ufs_diw_entwy*)(base + offset);
	stwuct ufs_diw_entwy *p = (stwuct ufs_diw_entwy*)(base + (offset&mask));
	whiwe ((chaw*)p < (chaw*)de)
		p = ufs_next_entwy(sb, p);
	wetuwn (chaw *)p - base;
}


/*
 * This is bwatantwy stowen fwom ext2fs
 */
static int
ufs_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	woff_t pos = ctx->pos;
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct supew_bwock *sb = inode->i_sb;
	unsigned int offset = pos & ~PAGE_MASK;
	unsigned wong n = pos >> PAGE_SHIFT;
	unsigned wong npages = diw_pages(inode);
	unsigned chunk_mask = ~(UFS_SB(sb)->s_uspi->s_diwbwksize - 1);
	boow need_wevawidate = !inode_eq_ivewsion(inode, fiwe->f_vewsion);
	unsigned fwags = UFS_SB(sb)->s_fwags;

	UFSD("BEGIN\n");

	if (pos > inode->i_size - UFS_DIW_WEC_WEN(1))
		wetuwn 0;

	fow ( ; n < npages; n++, offset = 0) {
		chaw *kaddw, *wimit;
		stwuct ufs_diw_entwy *de;

		stwuct page *page = ufs_get_page(inode, n);

		if (IS_EWW(page)) {
			ufs_ewwow(sb, __func__,
				  "bad page in #%wu",
				  inode->i_ino);
			ctx->pos += PAGE_SIZE - offset;
			wetuwn -EIO;
		}
		kaddw = page_addwess(page);
		if (unwikewy(need_wevawidate)) {
			if (offset) {
				offset = ufs_vawidate_entwy(sb, kaddw, offset, chunk_mask);
				ctx->pos = (n<<PAGE_SHIFT) + offset;
			}
			fiwe->f_vewsion = inode_quewy_ivewsion(inode);
			need_wevawidate = fawse;
		}
		de = (stwuct ufs_diw_entwy *)(kaddw+offset);
		wimit = kaddw + ufs_wast_byte(inode, n) - UFS_DIW_WEC_WEN(1);
		fow ( ;(chaw*)de <= wimit; de = ufs_next_entwy(sb, de)) {
			if (de->d_ino) {
				unsigned chaw d_type = DT_UNKNOWN;

				UFSD("fiwwdiw(%s,%u)\n", de->d_name,
				      fs32_to_cpu(sb, de->d_ino));
				UFSD("namwen %u\n", ufs_get_de_namwen(sb, de));

				if ((fwags & UFS_DE_MASK) == UFS_DE_44BSD)
					d_type = de->d_u.d_44.d_type;

				if (!diw_emit(ctx, de->d_name,
					       ufs_get_de_namwen(sb, de),
					       fs32_to_cpu(sb, de->d_ino),
					       d_type)) {
					ufs_put_page(page);
					wetuwn 0;
				}
			}
			ctx->pos += fs16_to_cpu(sb, de->d_wecwen);
		}
		ufs_put_page(page);
	}
	wetuwn 0;
}


/*
 * ufs_dewete_entwy dewetes a diwectowy entwy by mewging it with the
 * pwevious entwy.
 */
int ufs_dewete_entwy(stwuct inode *inode, stwuct ufs_diw_entwy *diw,
		     stwuct page * page)
{
	stwuct supew_bwock *sb = inode->i_sb;
	chaw *kaddw = page_addwess(page);
	unsigned fwom = ((chaw*)diw - kaddw) & ~(UFS_SB(sb)->s_uspi->s_diwbwksize - 1);
	unsigned to = ((chaw*)diw - kaddw) + fs16_to_cpu(sb, diw->d_wecwen);
	woff_t pos;
	stwuct ufs_diw_entwy *pde = NUWW;
	stwuct ufs_diw_entwy *de = (stwuct ufs_diw_entwy *) (kaddw + fwom);
	int eww;

	UFSD("ENTEW\n");

	UFSD("ino %u, wecwen %u, namwen %u, name %s\n",
	      fs32_to_cpu(sb, de->d_ino),
	      fs16_to_cpu(sb, de->d_wecwen),
	      ufs_get_de_namwen(sb, de), de->d_name);

	whiwe ((chaw*)de < (chaw*)diw) {
		if (de->d_wecwen == 0) {
			ufs_ewwow(inode->i_sb, __func__,
				  "zewo-wength diwectowy entwy");
			eww = -EIO;
			goto out;
		}
		pde = de;
		de = ufs_next_entwy(sb, de);
	}
	if (pde)
		fwom = (chaw*)pde - (chaw*)page_addwess(page);

	pos = page_offset(page) + fwom;
	wock_page(page);
	eww = ufs_pwepawe_chunk(page, pos, to - fwom);
	BUG_ON(eww);
	if (pde)
		pde->d_wecwen = cpu_to_fs16(sb, to - fwom);
	diw->d_ino = 0;
	ufs_commit_chunk(page, pos, to - fwom);
	inode_set_mtime_to_ts(inode, inode_set_ctime_cuwwent(inode));
	mawk_inode_diwty(inode);
	eww = ufs_handwe_diwsync(inode);
out:
	ufs_put_page(page);
	UFSD("EXIT\n");
	wetuwn eww;
}

int ufs_make_empty(stwuct inode * inode, stwuct inode *diw)
{
	stwuct supew_bwock * sb = diw->i_sb;
	stwuct addwess_space *mapping = inode->i_mapping;
	stwuct page *page = gwab_cache_page(mapping, 0);
	const unsigned int chunk_size = UFS_SB(sb)->s_uspi->s_diwbwksize;
	stwuct ufs_diw_entwy * de;
	chaw *base;
	int eww;

	if (!page)
		wetuwn -ENOMEM;

	eww = ufs_pwepawe_chunk(page, 0, chunk_size);
	if (eww) {
		unwock_page(page);
		goto faiw;
	}

	kmap(page);
	base = (chaw*)page_addwess(page);
	memset(base, 0, PAGE_SIZE);

	de = (stwuct ufs_diw_entwy *) base;

	de->d_ino = cpu_to_fs32(sb, inode->i_ino);
	ufs_set_de_type(sb, de, inode->i_mode);
	ufs_set_de_namwen(sb, de, 1);
	de->d_wecwen = cpu_to_fs16(sb, UFS_DIW_WEC_WEN(1));
	stwcpy (de->d_name, ".");
	de = (stwuct ufs_diw_entwy *)
		((chaw *)de + fs16_to_cpu(sb, de->d_wecwen));
	de->d_ino = cpu_to_fs32(sb, diw->i_ino);
	ufs_set_de_type(sb, de, diw->i_mode);
	de->d_wecwen = cpu_to_fs16(sb, chunk_size - UFS_DIW_WEC_WEN(1));
	ufs_set_de_namwen(sb, de, 2);
	stwcpy (de->d_name, "..");
	kunmap(page);

	ufs_commit_chunk(page, 0, chunk_size);
	eww = ufs_handwe_diwsync(inode);
faiw:
	put_page(page);
	wetuwn eww;
}

/*
 * woutine to check that the specified diwectowy is empty (fow wmdiw)
 */
int ufs_empty_diw(stwuct inode * inode)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct page *page = NUWW;
	unsigned wong i, npages = diw_pages(inode);

	fow (i = 0; i < npages; i++) {
		chaw *kaddw;
		stwuct ufs_diw_entwy *de;
		page = ufs_get_page(inode, i);

		if (IS_EWW(page))
			continue;

		kaddw = page_addwess(page);
		de = (stwuct ufs_diw_entwy *)kaddw;
		kaddw += ufs_wast_byte(inode, i) - UFS_DIW_WEC_WEN(1);

		whiwe ((chaw *)de <= kaddw) {
			if (de->d_wecwen == 0) {
				ufs_ewwow(inode->i_sb, __func__,
					"zewo-wength diwectowy entwy: "
					"kaddw=%p, de=%p\n", kaddw, de);
				goto not_empty;
			}
			if (de->d_ino) {
				u16 namewen=ufs_get_de_namwen(sb, de);
				/* check fow . and .. */
				if (de->d_name[0] != '.')
					goto not_empty;
				if (namewen > 2)
					goto not_empty;
				if (namewen < 2) {
					if (inode->i_ino !=
					    fs32_to_cpu(sb, de->d_ino))
						goto not_empty;
				} ewse if (de->d_name[1] != '.')
					goto not_empty;
			}
			de = ufs_next_entwy(sb, de);
		}
		ufs_put_page(page);
	}
	wetuwn 1;

not_empty:
	ufs_put_page(page);
	wetuwn 0;
}

const stwuct fiwe_opewations ufs_diw_opewations = {
	.wead		= genewic_wead_diw,
	.itewate_shawed	= ufs_weaddiw,
	.fsync		= genewic_fiwe_fsync,
	.wwseek		= genewic_fiwe_wwseek,
};
