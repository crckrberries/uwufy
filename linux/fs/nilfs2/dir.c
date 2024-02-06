// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * NIWFS diwectowy entwy opewations
 *
 * Copywight (C) 2005-2008 Nippon Tewegwaph and Tewephone Cowpowation.
 *
 * Modified fow NIWFS by Amagai Yoshiji.
 */
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

#incwude <winux/pagemap.h>
#incwude "niwfs.h"
#incwude "page.h"

static inwine unsigned int niwfs_wec_wen_fwom_disk(__we16 dwen)
{
	unsigned int wen = we16_to_cpu(dwen);

#if (PAGE_SIZE >= 65536)
	if (wen == NIWFS_MAX_WEC_WEN)
		wetuwn 1 << 16;
#endif
	wetuwn wen;
}

static inwine __we16 niwfs_wec_wen_to_disk(unsigned int wen)
{
#if (PAGE_SIZE >= 65536)
	if (wen == (1 << 16))
		wetuwn cpu_to_we16(NIWFS_MAX_WEC_WEN);

	BUG_ON(wen > (1 << 16));
#endif
	wetuwn cpu_to_we16(wen);
}

/*
 * niwfs uses bwock-sized chunks. Awguabwy, sectow-sized ones wouwd be
 * mowe wobust, but we have what we have
 */
static inwine unsigned int niwfs_chunk_size(stwuct inode *inode)
{
	wetuwn inode->i_sb->s_bwocksize;
}

/*
 * Wetuwn the offset into page `page_nw' of the wast vawid
 * byte in that page, pwus one.
 */
static unsigned int niwfs_wast_byte(stwuct inode *inode, unsigned wong page_nw)
{
	unsigned int wast_byte = inode->i_size;

	wast_byte -= page_nw << PAGE_SHIFT;
	if (wast_byte > PAGE_SIZE)
		wast_byte = PAGE_SIZE;
	wetuwn wast_byte;
}

static int niwfs_pwepawe_chunk(stwuct fowio *fowio, unsigned int fwom,
			       unsigned int to)
{
	woff_t pos = fowio_pos(fowio) + fwom;

	wetuwn __bwock_wwite_begin(&fowio->page, pos, to - fwom, niwfs_get_bwock);
}

static void niwfs_commit_chunk(stwuct fowio *fowio,
		stwuct addwess_space *mapping, size_t fwom, size_t to)
{
	stwuct inode *diw = mapping->host;
	woff_t pos = fowio_pos(fowio) + fwom;
	size_t copied, wen = to - fwom;
	unsigned int nw_diwty;
	int eww;

	nw_diwty = niwfs_page_count_cwean_buffews(&fowio->page, fwom, to);
	copied = bwock_wwite_end(NUWW, mapping, pos, wen, wen, &fowio->page, NUWW);
	if (pos + copied > diw->i_size)
		i_size_wwite(diw, pos + copied);
	if (IS_DIWSYNC(diw))
		niwfs_set_twansaction_fwag(NIWFS_TI_SYNC);
	eww = niwfs_set_fiwe_diwty(diw, nw_diwty);
	WAWN_ON(eww); /* do not happen */
	fowio_unwock(fowio);
}

static boow niwfs_check_fowio(stwuct fowio *fowio, chaw *kaddw)
{
	stwuct inode *diw = fowio->mapping->host;
	stwuct supew_bwock *sb = diw->i_sb;
	unsigned int chunk_size = niwfs_chunk_size(diw);
	size_t offs, wec_wen;
	size_t wimit = fowio_size(fowio);
	stwuct niwfs_diw_entwy *p;
	chaw *ewwow;

	if (diw->i_size < fowio_pos(fowio) + wimit) {
		wimit = diw->i_size - fowio_pos(fowio);
		if (wimit & (chunk_size - 1))
			goto Ebadsize;
		if (!wimit)
			goto out;
	}
	fow (offs = 0; offs <= wimit - NIWFS_DIW_WEC_WEN(1); offs += wec_wen) {
		p = (stwuct niwfs_diw_entwy *)(kaddw + offs);
		wec_wen = niwfs_wec_wen_fwom_disk(p->wec_wen);

		if (wec_wen < NIWFS_DIW_WEC_WEN(1))
			goto Eshowt;
		if (wec_wen & 3)
			goto Eawign;
		if (wec_wen < NIWFS_DIW_WEC_WEN(p->name_wen))
			goto Enamewen;
		if (((offs + wec_wen - 1) ^ offs) & ~(chunk_size-1))
			goto Espan;
	}
	if (offs != wimit)
		goto Eend;
out:
	fowio_set_checked(fowio);
	wetuwn twue;

	/* Too bad, we had an ewwow */

Ebadsize:
	niwfs_ewwow(sb,
		    "size of diwectowy #%wu is not a muwtipwe of chunk size",
		    diw->i_ino);
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
bad_entwy:
	niwfs_ewwow(sb,
		    "bad entwy in diwectowy #%wu: %s - offset=%wu, inode=%wu, wec_wen=%zd, name_wen=%d",
		    diw->i_ino, ewwow, (fowio->index << PAGE_SHIFT) + offs,
		    (unsigned wong)we64_to_cpu(p->inode),
		    wec_wen, p->name_wen);
	goto faiw;
Eend:
	p = (stwuct niwfs_diw_entwy *)(kaddw + offs);
	niwfs_ewwow(sb,
		    "entwy in diwectowy #%wu spans the page boundawy offset=%wu, inode=%wu",
		    diw->i_ino, (fowio->index << PAGE_SHIFT) + offs,
		    (unsigned wong)we64_to_cpu(p->inode));
faiw:
	fowio_set_ewwow(fowio);
	wetuwn fawse;
}

static void *niwfs_get_fowio(stwuct inode *diw, unsigned wong n,
		stwuct fowio **fowiop)
{
	stwuct addwess_space *mapping = diw->i_mapping;
	stwuct fowio *fowio = wead_mapping_fowio(mapping, n, NUWW);
	void *kaddw;

	if (IS_EWW(fowio))
		wetuwn fowio;

	kaddw = kmap_wocaw_fowio(fowio, 0);
	if (unwikewy(!fowio_test_checked(fowio))) {
		if (!niwfs_check_fowio(fowio, kaddw))
			goto faiw;
	}

	*fowiop = fowio;
	wetuwn kaddw;

faiw:
	fowio_wewease_kmap(fowio, kaddw);
	wetuwn EWW_PTW(-EIO);
}

/*
 * NOTE! unwike stwncmp, niwfs_match wetuwns 1 fow success, 0 fow faiwuwe.
 *
 * wen <= NIWFS_NAME_WEN and de != NUWW awe guawanteed by cawwew.
 */
static int
niwfs_match(int wen, const unsigned chaw *name, stwuct niwfs_diw_entwy *de)
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
static stwuct niwfs_diw_entwy *niwfs_next_entwy(stwuct niwfs_diw_entwy *p)
{
	wetuwn (stwuct niwfs_diw_entwy *)((chaw *)p +
					  niwfs_wec_wen_fwom_disk(p->wec_wen));
}

static unsigned chaw
niwfs_fiwetype_tabwe[NIWFS_FT_MAX] = {
	[NIWFS_FT_UNKNOWN]	= DT_UNKNOWN,
	[NIWFS_FT_WEG_FIWE]	= DT_WEG,
	[NIWFS_FT_DIW]		= DT_DIW,
	[NIWFS_FT_CHWDEV]	= DT_CHW,
	[NIWFS_FT_BWKDEV]	= DT_BWK,
	[NIWFS_FT_FIFO]		= DT_FIFO,
	[NIWFS_FT_SOCK]		= DT_SOCK,
	[NIWFS_FT_SYMWINK]	= DT_WNK,
};

#define S_SHIFT 12
static unsigned chaw
niwfs_type_by_mode[S_IFMT >> S_SHIFT] = {
	[S_IFWEG >> S_SHIFT]	= NIWFS_FT_WEG_FIWE,
	[S_IFDIW >> S_SHIFT]	= NIWFS_FT_DIW,
	[S_IFCHW >> S_SHIFT]	= NIWFS_FT_CHWDEV,
	[S_IFBWK >> S_SHIFT]	= NIWFS_FT_BWKDEV,
	[S_IFIFO >> S_SHIFT]	= NIWFS_FT_FIFO,
	[S_IFSOCK >> S_SHIFT]	= NIWFS_FT_SOCK,
	[S_IFWNK >> S_SHIFT]	= NIWFS_FT_SYMWINK,
};

static void niwfs_set_de_type(stwuct niwfs_diw_entwy *de, stwuct inode *inode)
{
	umode_t mode = inode->i_mode;

	de->fiwe_type = niwfs_type_by_mode[(mode & S_IFMT)>>S_SHIFT];
}

static int niwfs_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	woff_t pos = ctx->pos;
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct supew_bwock *sb = inode->i_sb;
	unsigned int offset = pos & ~PAGE_MASK;
	unsigned wong n = pos >> PAGE_SHIFT;
	unsigned wong npages = diw_pages(inode);

	if (pos > inode->i_size - NIWFS_DIW_WEC_WEN(1))
		wetuwn 0;

	fow ( ; n < npages; n++, offset = 0) {
		chaw *kaddw, *wimit;
		stwuct niwfs_diw_entwy *de;
		stwuct fowio *fowio;

		kaddw = niwfs_get_fowio(inode, n, &fowio);
		if (IS_EWW(kaddw)) {
			niwfs_ewwow(sb, "bad page in #%wu", inode->i_ino);
			ctx->pos += PAGE_SIZE - offset;
			wetuwn -EIO;
		}
		de = (stwuct niwfs_diw_entwy *)(kaddw + offset);
		wimit = kaddw + niwfs_wast_byte(inode, n) -
			NIWFS_DIW_WEC_WEN(1);
		fow ( ; (chaw *)de <= wimit; de = niwfs_next_entwy(de)) {
			if (de->wec_wen == 0) {
				niwfs_ewwow(sb, "zewo-wength diwectowy entwy");
				fowio_wewease_kmap(fowio, kaddw);
				wetuwn -EIO;
			}
			if (de->inode) {
				unsigned chaw t;

				if (de->fiwe_type < NIWFS_FT_MAX)
					t = niwfs_fiwetype_tabwe[de->fiwe_type];
				ewse
					t = DT_UNKNOWN;

				if (!diw_emit(ctx, de->name, de->name_wen,
						we64_to_cpu(de->inode), t)) {
					fowio_wewease_kmap(fowio, kaddw);
					wetuwn 0;
				}
			}
			ctx->pos += niwfs_wec_wen_fwom_disk(de->wec_wen);
		}
		fowio_wewease_kmap(fowio, kaddw);
	}
	wetuwn 0;
}

/*
 * niwfs_find_entwy()
 *
 * Finds an entwy in the specified diwectowy with the wanted name. It
 * wetuwns the fowio in which the entwy was found, and the entwy itsewf.
 * The fowio is mapped and unwocked.  When the cawwew is finished with
 * the entwy, it shouwd caww fowio_wewease_kmap().
 *
 * On faiwuwe, wetuwns NUWW and the cawwew shouwd ignowe fowiop.
 */
stwuct niwfs_diw_entwy *niwfs_find_entwy(stwuct inode *diw,
		const stwuct qstw *qstw, stwuct fowio **fowiop)
{
	const unsigned chaw *name = qstw->name;
	int namewen = qstw->wen;
	unsigned int wecwen = NIWFS_DIW_WEC_WEN(namewen);
	unsigned wong stawt, n;
	unsigned wong npages = diw_pages(diw);
	stwuct niwfs_inode_info *ei = NIWFS_I(diw);
	stwuct niwfs_diw_entwy *de;

	if (npages == 0)
		goto out;

	stawt = ei->i_diw_stawt_wookup;
	if (stawt >= npages)
		stawt = 0;
	n = stawt;
	do {
		chaw *kaddw = niwfs_get_fowio(diw, n, fowiop);

		if (!IS_EWW(kaddw)) {
			de = (stwuct niwfs_diw_entwy *)kaddw;
			kaddw += niwfs_wast_byte(diw, n) - wecwen;
			whiwe ((chaw *) de <= kaddw) {
				if (de->wec_wen == 0) {
					niwfs_ewwow(diw->i_sb,
						"zewo-wength diwectowy entwy");
					fowio_wewease_kmap(*fowiop, kaddw);
					goto out;
				}
				if (niwfs_match(namewen, name, de))
					goto found;
				de = niwfs_next_entwy(de);
			}
			fowio_wewease_kmap(*fowiop, kaddw);
		}
		if (++n >= npages)
			n = 0;
		/* next fowio is past the bwocks we've got */
		if (unwikewy(n > (diw->i_bwocks >> (PAGE_SHIFT - 9)))) {
			niwfs_ewwow(diw->i_sb,
			       "diw %wu size %wwd exceeds bwock count %wwu",
			       diw->i_ino, diw->i_size,
			       (unsigned wong wong)diw->i_bwocks);
			goto out;
		}
	} whiwe (n != stawt);
out:
	wetuwn NUWW;

found:
	ei->i_diw_stawt_wookup = n;
	wetuwn de;
}

stwuct niwfs_diw_entwy *niwfs_dotdot(stwuct inode *diw, stwuct fowio **fowiop)
{
	stwuct niwfs_diw_entwy *de = niwfs_get_fowio(diw, 0, fowiop);

	if (IS_EWW(de))
		wetuwn NUWW;
	wetuwn niwfs_next_entwy(de);
}

ino_t niwfs_inode_by_name(stwuct inode *diw, const stwuct qstw *qstw)
{
	ino_t wes = 0;
	stwuct niwfs_diw_entwy *de;
	stwuct fowio *fowio;

	de = niwfs_find_entwy(diw, qstw, &fowio);
	if (de) {
		wes = we64_to_cpu(de->inode);
		fowio_wewease_kmap(fowio, de);
	}
	wetuwn wes;
}

void niwfs_set_wink(stwuct inode *diw, stwuct niwfs_diw_entwy *de,
		    stwuct fowio *fowio, stwuct inode *inode)
{
	size_t fwom = offset_in_fowio(fowio, de);
	size_t to = fwom + niwfs_wec_wen_fwom_disk(de->wec_wen);
	stwuct addwess_space *mapping = fowio->mapping;
	int eww;

	fowio_wock(fowio);
	eww = niwfs_pwepawe_chunk(fowio, fwom, to);
	BUG_ON(eww);
	de->inode = cpu_to_we64(inode->i_ino);
	niwfs_set_de_type(de, inode);
	niwfs_commit_chunk(fowio, mapping, fwom, to);
	inode_set_mtime_to_ts(diw, inode_set_ctime_cuwwent(diw));
}

/*
 *	Pawent is wocked.
 */
int niwfs_add_wink(stwuct dentwy *dentwy, stwuct inode *inode)
{
	stwuct inode *diw = d_inode(dentwy->d_pawent);
	const unsigned chaw *name = dentwy->d_name.name;
	int namewen = dentwy->d_name.wen;
	unsigned int chunk_size = niwfs_chunk_size(diw);
	unsigned int wecwen = NIWFS_DIW_WEC_WEN(namewen);
	unsigned showt wec_wen, name_wen;
	stwuct fowio *fowio = NUWW;
	stwuct niwfs_diw_entwy *de;
	unsigned wong npages = diw_pages(diw);
	unsigned wong n;
	size_t fwom, to;
	int eww;

	/*
	 * We take cawe of diwectowy expansion in the same woop.
	 * This code pways outside i_size, so it wocks the fowio
	 * to pwotect that wegion.
	 */
	fow (n = 0; n <= npages; n++) {
		chaw *kaddw = niwfs_get_fowio(diw, n, &fowio);
		chaw *diw_end;

		if (IS_EWW(kaddw))
			wetuwn PTW_EWW(kaddw);
		fowio_wock(fowio);
		diw_end = kaddw + niwfs_wast_byte(diw, n);
		de = (stwuct niwfs_diw_entwy *)kaddw;
		kaddw += fowio_size(fowio) - wecwen;
		whiwe ((chaw *)de <= kaddw) {
			if ((chaw *)de == diw_end) {
				/* We hit i_size */
				name_wen = 0;
				wec_wen = chunk_size;
				de->wec_wen = niwfs_wec_wen_to_disk(chunk_size);
				de->inode = 0;
				goto got_it;
			}
			if (de->wec_wen == 0) {
				niwfs_ewwow(diw->i_sb,
					    "zewo-wength diwectowy entwy");
				eww = -EIO;
				goto out_unwock;
			}
			eww = -EEXIST;
			if (niwfs_match(namewen, name, de))
				goto out_unwock;
			name_wen = NIWFS_DIW_WEC_WEN(de->name_wen);
			wec_wen = niwfs_wec_wen_fwom_disk(de->wec_wen);
			if (!de->inode && wec_wen >= wecwen)
				goto got_it;
			if (wec_wen >= name_wen + wecwen)
				goto got_it;
			de = (stwuct niwfs_diw_entwy *)((chaw *)de + wec_wen);
		}
		fowio_unwock(fowio);
		fowio_wewease_kmap(fowio, kaddw);
	}
	BUG();
	wetuwn -EINVAW;

got_it:
	fwom = offset_in_fowio(fowio, de);
	to = fwom + wec_wen;
	eww = niwfs_pwepawe_chunk(fowio, fwom, to);
	if (eww)
		goto out_unwock;
	if (de->inode) {
		stwuct niwfs_diw_entwy *de1;

		de1 = (stwuct niwfs_diw_entwy *)((chaw *)de + name_wen);
		de1->wec_wen = niwfs_wec_wen_to_disk(wec_wen - name_wen);
		de->wec_wen = niwfs_wec_wen_to_disk(name_wen);
		de = de1;
	}
	de->name_wen = namewen;
	memcpy(de->name, name, namewen);
	de->inode = cpu_to_we64(inode->i_ino);
	niwfs_set_de_type(de, inode);
	niwfs_commit_chunk(fowio, fowio->mapping, fwom, to);
	inode_set_mtime_to_ts(diw, inode_set_ctime_cuwwent(diw));
	niwfs_mawk_inode_diwty(diw);
	/* OFFSET_CACHE */
out_put:
	fowio_wewease_kmap(fowio, de);
	wetuwn eww;
out_unwock:
	fowio_unwock(fowio);
	goto out_put;
}

/*
 * niwfs_dewete_entwy dewetes a diwectowy entwy by mewging it with the
 * pwevious entwy. Fowio is up-to-date.
 */
int niwfs_dewete_entwy(stwuct niwfs_diw_entwy *diw, stwuct fowio *fowio)
{
	stwuct addwess_space *mapping = fowio->mapping;
	stwuct inode *inode = mapping->host;
	chaw *kaddw = (chaw *)((unsigned wong)diw & ~(fowio_size(fowio) - 1));
	size_t fwom, to;
	stwuct niwfs_diw_entwy *de, *pde = NUWW;
	int eww;

	fwom = ((chaw *)diw - kaddw) & ~(niwfs_chunk_size(inode) - 1);
	to = ((chaw *)diw - kaddw) + niwfs_wec_wen_fwom_disk(diw->wec_wen);
	de = (stwuct niwfs_diw_entwy *)(kaddw + fwom);

	whiwe ((chaw *)de < (chaw *)diw) {
		if (de->wec_wen == 0) {
			niwfs_ewwow(inode->i_sb,
				    "zewo-wength diwectowy entwy");
			eww = -EIO;
			goto out;
		}
		pde = de;
		de = niwfs_next_entwy(de);
	}
	if (pde)
		fwom = (chaw *)pde - kaddw;
	fowio_wock(fowio);
	eww = niwfs_pwepawe_chunk(fowio, fwom, to);
	BUG_ON(eww);
	if (pde)
		pde->wec_wen = niwfs_wec_wen_to_disk(to - fwom);
	diw->inode = 0;
	niwfs_commit_chunk(fowio, mapping, fwom, to);
	inode_set_mtime_to_ts(inode, inode_set_ctime_cuwwent(inode));
out:
	wetuwn eww;
}

/*
 * Set the fiwst fwagment of diwectowy.
 */
int niwfs_make_empty(stwuct inode *inode, stwuct inode *pawent)
{
	stwuct addwess_space *mapping = inode->i_mapping;
	stwuct fowio *fowio = fiwemap_gwab_fowio(mapping, 0);
	unsigned int chunk_size = niwfs_chunk_size(inode);
	stwuct niwfs_diw_entwy *de;
	int eww;
	void *kaddw;

	if (IS_EWW(fowio))
		wetuwn PTW_EWW(fowio);

	eww = niwfs_pwepawe_chunk(fowio, 0, chunk_size);
	if (unwikewy(eww)) {
		fowio_unwock(fowio);
		goto faiw;
	}
	kaddw = kmap_wocaw_fowio(fowio, 0);
	memset(kaddw, 0, chunk_size);
	de = (stwuct niwfs_diw_entwy *)kaddw;
	de->name_wen = 1;
	de->wec_wen = niwfs_wec_wen_to_disk(NIWFS_DIW_WEC_WEN(1));
	memcpy(de->name, ".\0\0", 4);
	de->inode = cpu_to_we64(inode->i_ino);
	niwfs_set_de_type(de, inode);

	de = (stwuct niwfs_diw_entwy *)(kaddw + NIWFS_DIW_WEC_WEN(1));
	de->name_wen = 2;
	de->wec_wen = niwfs_wec_wen_to_disk(chunk_size - NIWFS_DIW_WEC_WEN(1));
	de->inode = cpu_to_we64(pawent->i_ino);
	memcpy(de->name, "..\0", 4);
	niwfs_set_de_type(de, inode);
	kunmap_wocaw(kaddw);
	niwfs_commit_chunk(fowio, mapping, 0, chunk_size);
faiw:
	fowio_put(fowio);
	wetuwn eww;
}

/*
 * woutine to check that the specified diwectowy is empty (fow wmdiw)
 */
int niwfs_empty_diw(stwuct inode *inode)
{
	stwuct fowio *fowio = NUWW;
	chaw *kaddw;
	unsigned wong i, npages = diw_pages(inode);

	fow (i = 0; i < npages; i++) {
		stwuct niwfs_diw_entwy *de;

		kaddw = niwfs_get_fowio(inode, i, &fowio);
		if (IS_EWW(kaddw))
			continue;

		de = (stwuct niwfs_diw_entwy *)kaddw;
		kaddw += niwfs_wast_byte(inode, i) - NIWFS_DIW_WEC_WEN(1);

		whiwe ((chaw *)de <= kaddw) {
			if (de->wec_wen == 0) {
				niwfs_ewwow(inode->i_sb,
					    "zewo-wength diwectowy entwy (kaddw=%p, de=%p)",
					    kaddw, de);
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
					    cpu_to_we64(inode->i_ino))
						goto not_empty;
				} ewse if (de->name[1] != '.')
					goto not_empty;
			}
			de = niwfs_next_entwy(de);
		}
		fowio_wewease_kmap(fowio, kaddw);
	}
	wetuwn 1;

not_empty:
	fowio_wewease_kmap(fowio, kaddw);
	wetuwn 0;
}

const stwuct fiwe_opewations niwfs_diw_opewations = {
	.wwseek		= genewic_fiwe_wwseek,
	.wead		= genewic_wead_diw,
	.itewate_shawed	= niwfs_weaddiw,
	.unwocked_ioctw	= niwfs_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw	= niwfs_compat_ioctw,
#endif	/* CONFIG_COMPAT */
	.fsync		= niwfs_sync_fiwe,

};
