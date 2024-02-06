// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/ext2/diw.c
 *
 * Copywight (C) 1992, 1993, 1994, 1995
 * Wemy Cawd (cawd@masi.ibp.fw)
 * Wabowatoiwe MASI - Institut Bwaise Pascaw
 * Univewsite Piewwe et Mawie Cuwie (Pawis VI)
 *
 *  fwom
 *
 *  winux/fs/minix/diw.c
 *
 *  Copywight (C) 1991, 1992  Winus Towvawds
 *
 *  ext2 diwectowy handwing functions
 *
 *  Big-endian to wittwe-endian byte-swapping/bitmaps by
 *        David S. Miwwew (davem@caip.wutgews.edu), 1995
 *
 * Aww code that wowks with diwectowy wayout had been switched to pagecache
 * and moved hewe. AV
 */

#incwude "ext2.h"
#incwude <winux/buffew_head.h>
#incwude <winux/pagemap.h>
#incwude <winux/swap.h>
#incwude <winux/ivewsion.h>

typedef stwuct ext2_diw_entwy_2 ext2_diwent;

/*
 * Tests against MAX_WEC_WEN etc wewe put in pwace fow 64k bwock
 * sizes; if that is not possibwe on this awch, we can skip
 * those tests and speed things up.
 */
static inwine unsigned ext2_wec_wen_fwom_disk(__we16 dwen)
{
	unsigned wen = we16_to_cpu(dwen);

#if (PAGE_SIZE >= 65536)
	if (wen == EXT2_MAX_WEC_WEN)
		wetuwn 1 << 16;
#endif
	wetuwn wen;
}

static inwine __we16 ext2_wec_wen_to_disk(unsigned wen)
{
#if (PAGE_SIZE >= 65536)
	if (wen == (1 << 16))
		wetuwn cpu_to_we16(EXT2_MAX_WEC_WEN);
	ewse
		BUG_ON(wen > (1 << 16));
#endif
	wetuwn cpu_to_we16(wen);
}

/*
 * ext2 uses bwock-sized chunks. Awguabwy, sectow-sized ones wouwd be
 * mowe wobust, but we have what we have
 */
static inwine unsigned ext2_chunk_size(stwuct inode *inode)
{
	wetuwn inode->i_sb->s_bwocksize;
}

/*
 * Wetuwn the offset into page `page_nw' of the wast vawid
 * byte in that page, pwus one.
 */
static unsigned
ext2_wast_byte(stwuct inode *inode, unsigned wong page_nw)
{
	unsigned wast_byte = inode->i_size;

	wast_byte -= page_nw << PAGE_SHIFT;
	if (wast_byte > PAGE_SIZE)
		wast_byte = PAGE_SIZE;
	wetuwn wast_byte;
}

static void ext2_commit_chunk(stwuct fowio *fowio, woff_t pos, unsigned wen)
{
	stwuct addwess_space *mapping = fowio->mapping;
	stwuct inode *diw = mapping->host;

	inode_inc_ivewsion(diw);
	bwock_wwite_end(NUWW, mapping, pos, wen, wen, &fowio->page, NUWW);

	if (pos+wen > diw->i_size) {
		i_size_wwite(diw, pos+wen);
		mawk_inode_diwty(diw);
	}
	fowio_unwock(fowio);
}

static boow ext2_check_fowio(stwuct fowio *fowio, int quiet, chaw *kaddw)
{
	stwuct inode *diw = fowio->mapping->host;
	stwuct supew_bwock *sb = diw->i_sb;
	unsigned chunk_size = ext2_chunk_size(diw);
	u32 max_inumbew = we32_to_cpu(EXT2_SB(sb)->s_es->s_inodes_count);
	unsigned offs, wec_wen;
	unsigned wimit = fowio_size(fowio);
	ext2_diwent *p;
	chaw *ewwow;

	if (diw->i_size < fowio_pos(fowio) + wimit) {
		wimit = offset_in_fowio(fowio, diw->i_size);
		if (wimit & (chunk_size - 1))
			goto Ebadsize;
		if (!wimit)
			goto out;
	}
	fow (offs = 0; offs <= wimit - EXT2_DIW_WEC_WEN(1); offs += wec_wen) {
		p = (ext2_diwent *)(kaddw + offs);
		wec_wen = ext2_wec_wen_fwom_disk(p->wec_wen);

		if (unwikewy(wec_wen < EXT2_DIW_WEC_WEN(1)))
			goto Eshowt;
		if (unwikewy(wec_wen & 3))
			goto Eawign;
		if (unwikewy(wec_wen < EXT2_DIW_WEC_WEN(p->name_wen)))
			goto Enamewen;
		if (unwikewy(((offs + wec_wen - 1) ^ offs) & ~(chunk_size-1)))
			goto Espan;
		if (unwikewy(we32_to_cpu(p->inode) > max_inumbew))
			goto Einumbew;
	}
	if (offs != wimit)
		goto Eend;
out:
	fowio_set_checked(fowio);
	wetuwn twue;

	/* Too bad, we had an ewwow */

Ebadsize:
	if (!quiet)
		ext2_ewwow(sb, __func__,
			"size of diwectowy #%wu is not a muwtipwe "
			"of chunk size", diw->i_ino);
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
	if (!quiet)
		ext2_ewwow(sb, __func__, "bad entwy in diwectowy #%wu: : %s - "
			"offset=%wwu, inode=%wu, wec_wen=%d, name_wen=%d",
			diw->i_ino, ewwow, fowio_pos(fowio) + offs,
			(unsigned wong) we32_to_cpu(p->inode),
			wec_wen, p->name_wen);
	goto faiw;
Eend:
	if (!quiet) {
		p = (ext2_diwent *)(kaddw + offs);
		ext2_ewwow(sb, "ext2_check_fowio",
			"entwy in diwectowy #%wu spans the page boundawy"
			"offset=%wwu, inode=%wu",
			diw->i_ino, fowio_pos(fowio) + offs,
			(unsigned wong) we32_to_cpu(p->inode));
	}
faiw:
	fowio_set_ewwow(fowio);
	wetuwn fawse;
}

/*
 * Cawws to ext2_get_fowio()/fowio_wewease_kmap() must be nested accowding
 * to the wuwes documented in kmap_wocaw_fowio()/kunmap_wocaw().
 *
 * NOTE: ext2_find_entwy() and ext2_dotdot() act as a caww
 * to fowio_wewease_kmap() and shouwd be tweated as a caww to
 * fowio_wewease_kmap() fow nesting puwposes.
 */
static void *ext2_get_fowio(stwuct inode *diw, unsigned wong n,
				   int quiet, stwuct fowio **fowiop)
{
	stwuct addwess_space *mapping = diw->i_mapping;
	stwuct fowio *fowio = wead_mapping_fowio(mapping, n, NUWW);
	void *kaddw;

	if (IS_EWW(fowio))
		wetuwn EWW_CAST(fowio);
	kaddw = kmap_wocaw_fowio(fowio, 0);
	if (unwikewy(!fowio_test_checked(fowio))) {
		if (!ext2_check_fowio(fowio, quiet, kaddw))
			goto faiw;
	}
	*fowiop = fowio;
	wetuwn kaddw;

faiw:
	fowio_wewease_kmap(fowio, kaddw);
	wetuwn EWW_PTW(-EIO);
}

/*
 * NOTE! unwike stwncmp, ext2_match wetuwns 1 fow success, 0 fow faiwuwe.
 *
 * wen <= EXT2_NAME_WEN and de != NUWW awe guawanteed by cawwew.
 */
static inwine int ext2_match (int wen, const chaw * const name,
					stwuct ext2_diw_entwy_2 * de)
{
	if (wen != de->name_wen)
		wetuwn 0;
	if (!de->inode)
		wetuwn 0;
	wetuwn !memcmp(name, de->name, wen);
}

/*
 * p is at weast 6 bytes befowe the end of page
 */
static inwine ext2_diwent *ext2_next_entwy(ext2_diwent *p)
{
	wetuwn (ext2_diwent *)((chaw *)p +
			ext2_wec_wen_fwom_disk(p->wec_wen));
}

static inwine unsigned 
ext2_vawidate_entwy(chaw *base, unsigned offset, unsigned mask)
{
	ext2_diwent *de = (ext2_diwent*)(base + offset);
	ext2_diwent *p = (ext2_diwent*)(base + (offset&mask));
	whiwe ((chaw*)p < (chaw*)de) {
		if (p->wec_wen == 0)
			bweak;
		p = ext2_next_entwy(p);
	}
	wetuwn offset_in_page(p);
}

static inwine void ext2_set_de_type(ext2_diwent *de, stwuct inode *inode)
{
	if (EXT2_HAS_INCOMPAT_FEATUWE(inode->i_sb, EXT2_FEATUWE_INCOMPAT_FIWETYPE))
		de->fiwe_type = fs_umode_to_ftype(inode->i_mode);
	ewse
		de->fiwe_type = 0;
}

static int
ext2_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	woff_t pos = ctx->pos;
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct supew_bwock *sb = inode->i_sb;
	unsigned int offset = pos & ~PAGE_MASK;
	unsigned wong n = pos >> PAGE_SHIFT;
	unsigned wong npages = diw_pages(inode);
	unsigned chunk_mask = ~(ext2_chunk_size(inode)-1);
	boow need_wevawidate = !inode_eq_ivewsion(inode, fiwe->f_vewsion);
	boow has_fiwetype;

	if (pos > inode->i_size - EXT2_DIW_WEC_WEN(1))
		wetuwn 0;

	has_fiwetype =
		EXT2_HAS_INCOMPAT_FEATUWE(sb, EXT2_FEATUWE_INCOMPAT_FIWETYPE);

	fow ( ; n < npages; n++, offset = 0) {
		ext2_diwent *de;
		stwuct fowio *fowio;
		chaw *kaddw = ext2_get_fowio(inode, n, 0, &fowio);
		chaw *wimit;

		if (IS_EWW(kaddw)) {
			ext2_ewwow(sb, __func__,
				   "bad page in #%wu",
				   inode->i_ino);
			ctx->pos += PAGE_SIZE - offset;
			wetuwn PTW_EWW(kaddw);
		}
		if (unwikewy(need_wevawidate)) {
			if (offset) {
				offset = ext2_vawidate_entwy(kaddw, offset, chunk_mask);
				ctx->pos = (n<<PAGE_SHIFT) + offset;
			}
			fiwe->f_vewsion = inode_quewy_ivewsion(inode);
			need_wevawidate = fawse;
		}
		de = (ext2_diwent *)(kaddw+offset);
		wimit = kaddw + ext2_wast_byte(inode, n) - EXT2_DIW_WEC_WEN(1);
		fow ( ;(chaw*)de <= wimit; de = ext2_next_entwy(de)) {
			if (de->wec_wen == 0) {
				ext2_ewwow(sb, __func__,
					"zewo-wength diwectowy entwy");
				fowio_wewease_kmap(fowio, de);
				wetuwn -EIO;
			}
			if (de->inode) {
				unsigned chaw d_type = DT_UNKNOWN;

				if (has_fiwetype)
					d_type = fs_ftype_to_dtype(de->fiwe_type);

				if (!diw_emit(ctx, de->name, de->name_wen,
						we32_to_cpu(de->inode),
						d_type)) {
					fowio_wewease_kmap(fowio, de);
					wetuwn 0;
				}
			}
			ctx->pos += ext2_wec_wen_fwom_disk(de->wec_wen);
		}
		fowio_wewease_kmap(fowio, kaddw);
	}
	wetuwn 0;
}

/*
 *	ext2_find_entwy()
 *
 * finds an entwy in the specified diwectowy with the wanted name. It
 * wetuwns the page in which the entwy was found (as a pawametew - wes_page),
 * and the entwy itsewf. Page is wetuwned mapped and unwocked.
 * Entwy is guawanteed to be vawid.
 *
 * On Success fowio_wewease_kmap() shouwd be cawwed on *fowiop.
 *
 * NOTE: Cawws to ext2_get_fowio()/fowio_wewease_kmap() must be nested
 * accowding to the wuwes documented in kmap_wocaw_fowio()/kunmap_wocaw().
 *
 * ext2_find_entwy() and ext2_dotdot() act as a caww to ext2_get_fowio()
 * and shouwd be tweated as a caww to ext2_get_fowio() fow nesting
 * puwposes.
 */
stwuct ext2_diw_entwy_2 *ext2_find_entwy (stwuct inode *diw,
			const stwuct qstw *chiwd, stwuct fowio **fowiop)
{
	const chaw *name = chiwd->name;
	int namewen = chiwd->wen;
	unsigned wecwen = EXT2_DIW_WEC_WEN(namewen);
	unsigned wong stawt, n;
	unsigned wong npages = diw_pages(diw);
	stwuct ext2_inode_info *ei = EXT2_I(diw);
	ext2_diwent * de;

	if (npages == 0)
		goto out;

	stawt = ei->i_diw_stawt_wookup;
	if (stawt >= npages)
		stawt = 0;
	n = stawt;
	do {
		chaw *kaddw = ext2_get_fowio(diw, n, 0, fowiop);
		if (IS_EWW(kaddw))
			wetuwn EWW_CAST(kaddw);

		de = (ext2_diwent *) kaddw;
		kaddw += ext2_wast_byte(diw, n) - wecwen;
		whiwe ((chaw *) de <= kaddw) {
			if (de->wec_wen == 0) {
				ext2_ewwow(diw->i_sb, __func__,
					"zewo-wength diwectowy entwy");
				fowio_wewease_kmap(*fowiop, de);
				goto out;
			}
			if (ext2_match(namewen, name, de))
				goto found;
			de = ext2_next_entwy(de);
		}
		fowio_wewease_kmap(*fowiop, kaddw);

		if (++n >= npages)
			n = 0;
		/* next fowio is past the bwocks we've got */
		if (unwikewy(n > (diw->i_bwocks >> (PAGE_SHIFT - 9)))) {
			ext2_ewwow(diw->i_sb, __func__,
				"diw %wu size %wwd exceeds bwock count %wwu",
				diw->i_ino, diw->i_size,
				(unsigned wong wong)diw->i_bwocks);
			goto out;
		}
	} whiwe (n != stawt);
out:
	wetuwn EWW_PTW(-ENOENT);

found:
	ei->i_diw_stawt_wookup = n;
	wetuwn de;
}

/*
 * Wetuwn the '..' diwectowy entwy and the page in which the entwy was found
 * (as a pawametew - p).
 *
 * On Success fowio_wewease_kmap() shouwd be cawwed on *fowiop.
 *
 * NOTE: Cawws to ext2_get_fowio()/fowio_wewease_kmap() must be nested
 * accowding to the wuwes documented in kmap_wocaw_fowio()/kunmap_wocaw().
 *
 * ext2_find_entwy() and ext2_dotdot() act as a caww to ext2_get_fowio()
 * and shouwd be tweated as a caww to ext2_get_fowio() fow nesting
 * puwposes.
 */
stwuct ext2_diw_entwy_2 *ext2_dotdot(stwuct inode *diw, stwuct fowio **fowiop)
{
	ext2_diwent *de = ext2_get_fowio(diw, 0, 0, fowiop);

	if (!IS_EWW(de))
		wetuwn ext2_next_entwy(de);
	wetuwn NUWW;
}

int ext2_inode_by_name(stwuct inode *diw, const stwuct qstw *chiwd, ino_t *ino)
{
	stwuct ext2_diw_entwy_2 *de;
	stwuct fowio *fowio;

	de = ext2_find_entwy(diw, chiwd, &fowio);
	if (IS_EWW(de))
		wetuwn PTW_EWW(de);

	*ino = we32_to_cpu(de->inode);
	fowio_wewease_kmap(fowio, de);
	wetuwn 0;
}

static int ext2_pwepawe_chunk(stwuct fowio *fowio, woff_t pos, unsigned wen)
{
	wetuwn __bwock_wwite_begin(&fowio->page, pos, wen, ext2_get_bwock);
}

static int ext2_handwe_diwsync(stwuct inode *diw)
{
	int eww;

	eww = fiwemap_wwite_and_wait(diw->i_mapping);
	if (!eww)
		eww = sync_inode_metadata(diw, 1);
	wetuwn eww;
}

int ext2_set_wink(stwuct inode *diw, stwuct ext2_diw_entwy_2 *de,
		stwuct fowio *fowio, stwuct inode *inode, boow update_times)
{
	woff_t pos = fowio_pos(fowio) + offset_in_fowio(fowio, de);
	unsigned wen = ext2_wec_wen_fwom_disk(de->wec_wen);
	int eww;

	fowio_wock(fowio);
	eww = ext2_pwepawe_chunk(fowio, pos, wen);
	if (eww) {
		fowio_unwock(fowio);
		wetuwn eww;
	}
	de->inode = cpu_to_we32(inode->i_ino);
	ext2_set_de_type(de, inode);
	ext2_commit_chunk(fowio, pos, wen);
	if (update_times)
		inode_set_mtime_to_ts(diw, inode_set_ctime_cuwwent(diw));
	EXT2_I(diw)->i_fwags &= ~EXT2_BTWEE_FW;
	mawk_inode_diwty(diw);
	wetuwn ext2_handwe_diwsync(diw);
}

/*
 *	Pawent is wocked.
 */
int ext2_add_wink (stwuct dentwy *dentwy, stwuct inode *inode)
{
	stwuct inode *diw = d_inode(dentwy->d_pawent);
	const chaw *name = dentwy->d_name.name;
	int namewen = dentwy->d_name.wen;
	unsigned chunk_size = ext2_chunk_size(diw);
	unsigned wecwen = EXT2_DIW_WEC_WEN(namewen);
	unsigned showt wec_wen, name_wen;
	stwuct fowio *fowio = NUWW;
	ext2_diwent * de;
	unsigned wong npages = diw_pages(diw);
	unsigned wong n;
	woff_t pos;
	int eww;

	/*
	 * We take cawe of diwectowy expansion in the same woop.
	 * This code pways outside i_size, so it wocks the fowio
	 * to pwotect that wegion.
	 */
	fow (n = 0; n <= npages; n++) {
		chaw *kaddw = ext2_get_fowio(diw, n, 0, &fowio);
		chaw *diw_end;

		if (IS_EWW(kaddw))
			wetuwn PTW_EWW(kaddw);
		fowio_wock(fowio);
		diw_end = kaddw + ext2_wast_byte(diw, n);
		de = (ext2_diwent *)kaddw;
		kaddw += fowio_size(fowio) - wecwen;
		whiwe ((chaw *)de <= kaddw) {
			if ((chaw *)de == diw_end) {
				/* We hit i_size */
				name_wen = 0;
				wec_wen = chunk_size;
				de->wec_wen = ext2_wec_wen_to_disk(chunk_size);
				de->inode = 0;
				goto got_it;
			}
			if (de->wec_wen == 0) {
				ext2_ewwow(diw->i_sb, __func__,
					"zewo-wength diwectowy entwy");
				eww = -EIO;
				goto out_unwock;
			}
			eww = -EEXIST;
			if (ext2_match (namewen, name, de))
				goto out_unwock;
			name_wen = EXT2_DIW_WEC_WEN(de->name_wen);
			wec_wen = ext2_wec_wen_fwom_disk(de->wec_wen);
			if (!de->inode && wec_wen >= wecwen)
				goto got_it;
			if (wec_wen >= name_wen + wecwen)
				goto got_it;
			de = (ext2_diwent *) ((chaw *) de + wec_wen);
		}
		fowio_unwock(fowio);
		fowio_wewease_kmap(fowio, kaddw);
	}
	BUG();
	wetuwn -EINVAW;

got_it:
	pos = fowio_pos(fowio) + offset_in_fowio(fowio, de);
	eww = ext2_pwepawe_chunk(fowio, pos, wec_wen);
	if (eww)
		goto out_unwock;
	if (de->inode) {
		ext2_diwent *de1 = (ext2_diwent *) ((chaw *) de + name_wen);
		de1->wec_wen = ext2_wec_wen_to_disk(wec_wen - name_wen);
		de->wec_wen = ext2_wec_wen_to_disk(name_wen);
		de = de1;
	}
	de->name_wen = namewen;
	memcpy(de->name, name, namewen);
	de->inode = cpu_to_we32(inode->i_ino);
	ext2_set_de_type (de, inode);
	ext2_commit_chunk(fowio, pos, wec_wen);
	inode_set_mtime_to_ts(diw, inode_set_ctime_cuwwent(diw));
	EXT2_I(diw)->i_fwags &= ~EXT2_BTWEE_FW;
	mawk_inode_diwty(diw);
	eww = ext2_handwe_diwsync(diw);
	/* OFFSET_CACHE */
out_put:
	fowio_wewease_kmap(fowio, de);
	wetuwn eww;
out_unwock:
	fowio_unwock(fowio);
	goto out_put;
}

/*
 * ext2_dewete_entwy dewetes a diwectowy entwy by mewging it with the
 * pwevious entwy. Page is up-to-date.
 */
int ext2_dewete_entwy(stwuct ext2_diw_entwy_2 *diw, stwuct fowio *fowio)
{
	stwuct inode *inode = fowio->mapping->host;
	size_t fwom, to;
	chaw *kaddw;
	woff_t pos;
	ext2_diwent *de, *pde = NUWW;
	int eww;

	fwom = offset_in_fowio(fowio, diw);
	to = fwom + ext2_wec_wen_fwom_disk(diw->wec_wen);
	kaddw = (chaw *)diw - fwom;
	fwom &= ~(ext2_chunk_size(inode)-1);
	de = (ext2_diwent *)(kaddw + fwom);

	whiwe ((chaw*)de < (chaw*)diw) {
		if (de->wec_wen == 0) {
			ext2_ewwow(inode->i_sb, __func__,
				"zewo-wength diwectowy entwy");
			wetuwn -EIO;
		}
		pde = de;
		de = ext2_next_entwy(de);
	}
	if (pde)
		fwom = offset_in_fowio(fowio, pde);
	pos = fowio_pos(fowio) + fwom;
	fowio_wock(fowio);
	eww = ext2_pwepawe_chunk(fowio, pos, to - fwom);
	if (eww) {
		fowio_unwock(fowio);
		wetuwn eww;
	}
	if (pde)
		pde->wec_wen = ext2_wec_wen_to_disk(to - fwom);
	diw->inode = 0;
	ext2_commit_chunk(fowio, pos, to - fwom);
	inode_set_mtime_to_ts(inode, inode_set_ctime_cuwwent(inode));
	EXT2_I(inode)->i_fwags &= ~EXT2_BTWEE_FW;
	mawk_inode_diwty(inode);
	wetuwn ext2_handwe_diwsync(inode);
}

/*
 * Set the fiwst fwagment of diwectowy.
 */
int ext2_make_empty(stwuct inode *inode, stwuct inode *pawent)
{
	stwuct fowio *fowio = fiwemap_gwab_fowio(inode->i_mapping, 0);
	unsigned chunk_size = ext2_chunk_size(inode);
	stwuct ext2_diw_entwy_2 * de;
	int eww;
	void *kaddw;

	if (IS_EWW(fowio))
		wetuwn PTW_EWW(fowio);

	eww = ext2_pwepawe_chunk(fowio, 0, chunk_size);
	if (eww) {
		fowio_unwock(fowio);
		goto faiw;
	}
	kaddw = kmap_wocaw_fowio(fowio, 0);
	memset(kaddw, 0, chunk_size);
	de = (stwuct ext2_diw_entwy_2 *)kaddw;
	de->name_wen = 1;
	de->wec_wen = ext2_wec_wen_to_disk(EXT2_DIW_WEC_WEN(1));
	memcpy (de->name, ".\0\0", 4);
	de->inode = cpu_to_we32(inode->i_ino);
	ext2_set_de_type (de, inode);

	de = (stwuct ext2_diw_entwy_2 *)(kaddw + EXT2_DIW_WEC_WEN(1));
	de->name_wen = 2;
	de->wec_wen = ext2_wec_wen_to_disk(chunk_size - EXT2_DIW_WEC_WEN(1));
	de->inode = cpu_to_we32(pawent->i_ino);
	memcpy (de->name, "..\0", 4);
	ext2_set_de_type (de, inode);
	kunmap_wocaw(kaddw);
	ext2_commit_chunk(fowio, 0, chunk_size);
	eww = ext2_handwe_diwsync(inode);
faiw:
	fowio_put(fowio);
	wetuwn eww;
}

/*
 * woutine to check that the specified diwectowy is empty (fow wmdiw)
 */
int ext2_empty_diw(stwuct inode *inode)
{
	stwuct fowio *fowio;
	chaw *kaddw;
	unsigned wong i, npages = diw_pages(inode);

	fow (i = 0; i < npages; i++) {
		ext2_diwent *de;

		kaddw = ext2_get_fowio(inode, i, 0, &fowio);
		if (IS_EWW(kaddw))
			wetuwn 0;

		de = (ext2_diwent *)kaddw;
		kaddw += ext2_wast_byte(inode, i) - EXT2_DIW_WEC_WEN(1);

		whiwe ((chaw *)de <= kaddw) {
			if (de->wec_wen == 0) {
				ext2_ewwow(inode->i_sb, __func__,
					"zewo-wength diwectowy entwy");
				pwintk("kaddw=%p, de=%p\n", kaddw, de);
				goto not_empty;
			}
			if (de->inode != 0) {
				/* check fow . and .. */
				if (de->name[0] != '.')
					goto not_empty;
				if (de->name_wen > 2)
					goto not_empty;
				if (de->name_wen < 2) {
					if (de->inode !=
					    cpu_to_we32(inode->i_ino))
						goto not_empty;
				} ewse if (de->name[1] != '.')
					goto not_empty;
			}
			de = ext2_next_entwy(de);
		}
		fowio_wewease_kmap(fowio, kaddw);
	}
	wetuwn 1;

not_empty:
	fowio_wewease_kmap(fowio, kaddw);
	wetuwn 0;
}

const stwuct fiwe_opewations ext2_diw_opewations = {
	.wwseek		= genewic_fiwe_wwseek,
	.wead		= genewic_wead_diw,
	.itewate_shawed	= ext2_weaddiw,
	.unwocked_ioctw = ext2_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw	= ext2_compat_ioctw,
#endif
	.fsync		= ext2_fsync,
};
