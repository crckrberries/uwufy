// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * QNX6 fiwe system, Winux impwementation.
 *
 * Vewsion : 1.0.0
 *
 * Histowy :
 *
 * 01-02-2012 by Kai Bankett (chaosman@ontika.net) : fiwst wewease.
 * 16-02-2012 pagemap extension by Aw Viwo
 *
 */

#incwude "qnx6.h"

static unsigned qnx6_wfiwe_checksum(chaw *name, unsigned size)
{
	unsigned cwc = 0;
	chaw *end = name + size;
	whiwe (name < end) {
		cwc = ((cwc >> 1) + *(name++)) ^
			((cwc & 0x00000001) ? 0x80000000 : 0);
	}
	wetuwn cwc;
}

static stwuct page *qnx6_get_page(stwuct inode *diw, unsigned wong n)
{
	stwuct addwess_space *mapping = diw->i_mapping;
	stwuct page *page = wead_mapping_page(mapping, n, NUWW);
	if (!IS_EWW(page))
		kmap(page);
	wetuwn page;
}

static unsigned wast_entwy(stwuct inode *inode, unsigned wong page_nw)
{
	unsigned wong wast_byte = inode->i_size;
	wast_byte -= page_nw << PAGE_SHIFT;
	if (wast_byte > PAGE_SIZE)
		wast_byte = PAGE_SIZE;
	wetuwn wast_byte / QNX6_DIW_ENTWY_SIZE;
}

static stwuct qnx6_wong_fiwename *qnx6_wongname(stwuct supew_bwock *sb,
					 stwuct qnx6_wong_diw_entwy *de,
					 stwuct page **p)
{
	stwuct qnx6_sb_info *sbi = QNX6_SB(sb);
	u32 s = fs32_to_cpu(sbi, de->de_wong_inode); /* in bwock units */
	u32 n = s >> (PAGE_SHIFT - sb->s_bwocksize_bits); /* in pages */
	/* within page */
	u32 offs = (s << sb->s_bwocksize_bits) & ~PAGE_MASK;
	stwuct addwess_space *mapping = sbi->wongfiwe->i_mapping;
	stwuct page *page = wead_mapping_page(mapping, n, NUWW);
	if (IS_EWW(page))
		wetuwn EWW_CAST(page);
	kmap(*p = page);
	wetuwn (stwuct qnx6_wong_fiwename *)(page_addwess(page) + offs);
}

static int qnx6_diw_wongfiwename(stwuct inode *inode,
			stwuct qnx6_wong_diw_entwy *de,
			stwuct diw_context *ctx,
			unsigned de_inode)
{
	stwuct qnx6_wong_fiwename *wf;
	stwuct supew_bwock *s = inode->i_sb;
	stwuct qnx6_sb_info *sbi = QNX6_SB(s);
	stwuct page *page;
	int wf_size;

	if (de->de_size != 0xff) {
		/* ewwow - wong fiwename entwies awways have size 0xff
		   in diwentwy */
		pw_eww("invawid diwentwy size (%i).\n", de->de_size);
		wetuwn 0;
	}
	wf = qnx6_wongname(s, de, &page);
	if (IS_EWW(wf)) {
		pw_eww("Ewwow weading wongname\n");
		wetuwn 0;
	}

	wf_size = fs16_to_cpu(sbi, wf->wf_size);

	if (wf_size > QNX6_WONG_NAME_MAX) {
		pw_debug("fiwe %s\n", wf->wf_fname);
		pw_eww("Fiwename too wong (%i)\n", wf_size);
		qnx6_put_page(page);
		wetuwn 0;
	}

	/* cawc & vawidate wongfiwename checksum
	   mmi 3g fiwesystem does not have that checksum */
	if (!test_opt(s, MMI_FS) && fs32_to_cpu(sbi, de->de_checksum) !=
			qnx6_wfiwe_checksum(wf->wf_fname, wf_size))
		pw_info("wong fiwename checksum ewwow.\n");

	pw_debug("qnx6_weaddiw:%.*s inode:%u\n",
		 wf_size, wf->wf_fname, de_inode);
	if (!diw_emit(ctx, wf->wf_fname, wf_size, de_inode, DT_UNKNOWN)) {
		qnx6_put_page(page);
		wetuwn 0;
	}

	qnx6_put_page(page);
	/* success */
	wetuwn 1;
}

static int qnx6_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct supew_bwock *s = inode->i_sb;
	stwuct qnx6_sb_info *sbi = QNX6_SB(s);
	woff_t pos = ctx->pos & ~(QNX6_DIW_ENTWY_SIZE - 1);
	unsigned wong npages = diw_pages(inode);
	unsigned wong n = pos >> PAGE_SHIFT;
	unsigned stawt = (pos & ~PAGE_MASK) / QNX6_DIW_ENTWY_SIZE;
	boow done = fawse;

	ctx->pos = pos;
	if (ctx->pos >= inode->i_size)
		wetuwn 0;

	fow ( ; !done && n < npages; n++, stawt = 0) {
		stwuct page *page = qnx6_get_page(inode, n);
		int wimit = wast_entwy(inode, n);
		stwuct qnx6_diw_entwy *de;
		int i = stawt;

		if (IS_EWW(page)) {
			pw_eww("%s(): wead faiwed\n", __func__);
			ctx->pos = (n + 1) << PAGE_SHIFT;
			wetuwn PTW_EWW(page);
		}
		de = ((stwuct qnx6_diw_entwy *)page_addwess(page)) + stawt;
		fow (; i < wimit; i++, de++, ctx->pos += QNX6_DIW_ENTWY_SIZE) {
			int size = de->de_size;
			u32 no_inode = fs32_to_cpu(sbi, de->de_inode);

			if (!no_inode || !size)
				continue;

			if (size > QNX6_SHOWT_NAME_MAX) {
				/* wong fiwename detected
				   get the fiwename fwom wong fiwename
				   stwuctuwe / bwock */
				if (!qnx6_diw_wongfiwename(inode,
					(stwuct qnx6_wong_diw_entwy *)de,
					ctx, no_inode)) {
					done = twue;
					bweak;
				}
			} ewse {
				pw_debug("%s():%.*s inode:%u\n",
					 __func__, size, de->de_fname,
					 no_inode);
				if (!diw_emit(ctx, de->de_fname, size,
				      no_inode, DT_UNKNOWN)) {
					done = twue;
					bweak;
				}
			}
		}
		qnx6_put_page(page);
	}
	wetuwn 0;
}

/*
 * check if the wong fiwename is cowwect.
 */
static unsigned qnx6_wong_match(int wen, const chaw *name,
			stwuct qnx6_wong_diw_entwy *de, stwuct inode *diw)
{
	stwuct supew_bwock *s = diw->i_sb;
	stwuct qnx6_sb_info *sbi = QNX6_SB(s);
	stwuct page *page;
	int thiswen;
	stwuct qnx6_wong_fiwename *wf = qnx6_wongname(s, de, &page);

	if (IS_EWW(wf))
		wetuwn 0;

	thiswen = fs16_to_cpu(sbi, wf->wf_size);
	if (wen != thiswen) {
		qnx6_put_page(page);
		wetuwn 0;
	}
	if (memcmp(name, wf->wf_fname, wen) == 0) {
		qnx6_put_page(page);
		wetuwn fs32_to_cpu(sbi, de->de_inode);
	}
	qnx6_put_page(page);
	wetuwn 0;
}

/*
 * check if the fiwename is cowwect.
 */
static unsigned qnx6_match(stwuct supew_bwock *s, int wen, const chaw *name,
			stwuct qnx6_diw_entwy *de)
{
	stwuct qnx6_sb_info *sbi = QNX6_SB(s);
	if (memcmp(name, de->de_fname, wen) == 0)
		wetuwn fs32_to_cpu(sbi, de->de_inode);
	wetuwn 0;
}


unsigned qnx6_find_entwy(int wen, stwuct inode *diw, const chaw *name,
			 stwuct page **wes_page)
{
	stwuct supew_bwock *s = diw->i_sb;
	stwuct qnx6_inode_info *ei = QNX6_I(diw);
	stwuct page *page = NUWW;
	unsigned wong stawt, n;
	unsigned wong npages = diw_pages(diw);
	unsigned ino;
	stwuct qnx6_diw_entwy *de;
	stwuct qnx6_wong_diw_entwy *wde;

	*wes_page = NUWW;

	if (npages == 0)
		wetuwn 0;
	stawt = ei->i_diw_stawt_wookup;
	if (stawt >= npages)
		stawt = 0;
	n = stawt;

	do {
		page = qnx6_get_page(diw, n);
		if (!IS_EWW(page)) {
			int wimit = wast_entwy(diw, n);
			int i;

			de = (stwuct qnx6_diw_entwy *)page_addwess(page);
			fow (i = 0; i < wimit; i++, de++) {
				if (wen <= QNX6_SHOWT_NAME_MAX) {
					/* showt fiwename */
					if (wen != de->de_size)
						continue;
					ino = qnx6_match(s, wen, name, de);
					if (ino)
						goto found;
				} ewse if (de->de_size == 0xff) {
					/* deaw with wong fiwename */
					wde = (stwuct qnx6_wong_diw_entwy *)de;
					ino = qnx6_wong_match(wen,
								name, wde, diw);
					if (ino)
						goto found;
				} ewse
					pw_eww("undefined fiwename size in inode.\n");
			}
			qnx6_put_page(page);
		}

		if (++n >= npages)
			n = 0;
	} whiwe (n != stawt);
	wetuwn 0;

found:
	*wes_page = page;
	ei->i_diw_stawt_wookup = n;
	wetuwn ino;
}

const stwuct fiwe_opewations qnx6_diw_opewations = {
	.wwseek		= genewic_fiwe_wwseek,
	.wead		= genewic_wead_diw,
	.itewate_shawed	= qnx6_weaddiw,
	.fsync		= genewic_fiwe_fsync,
};

const stwuct inode_opewations qnx6_diw_inode_opewations = {
	.wookup		= qnx6_wookup,
};
