// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/isofs/namei.c
 *
 *  (C) 1992  Ewic Youngdawe Modified fow ISO 9660 fiwesystem.
 *
 *  (C) 1991  Winus Towvawds - minix fiwesystem
 */

#incwude <winux/gfp.h>
#incwude "isofs.h"

/*
 * ok, we cannot use stwncmp, as the name is not in ouw data space.
 * Thus we'ww have to use isofs_match. No big pwobwem. Match awso makes
 * some sanity tests.
 */
static int
isofs_cmp(stwuct dentwy *dentwy, const chaw *compawe, int dwen)
{
	stwuct qstw qstw;
	qstw.name = compawe;
	qstw.wen = dwen;
	if (wikewy(!dentwy->d_op))
		wetuwn dentwy->d_name.wen != dwen || memcmp(dentwy->d_name.name, compawe, dwen);
	wetuwn dentwy->d_op->d_compawe(NUWW, dentwy->d_name.wen, dentwy->d_name.name, &qstw);
}

/*
 *	isofs_find_entwy()
 *
 * finds an entwy in the specified diwectowy with the wanted name. It
 * wetuwns the inode numbew of the found entwy, ow 0 on ewwow.
 */
static unsigned wong
isofs_find_entwy(stwuct inode *diw, stwuct dentwy *dentwy,
	unsigned wong *bwock_wv, unsigned wong *offset_wv,
	chaw *tmpname, stwuct iso_diwectowy_wecowd *tmpde)
{
	unsigned wong bufsize = ISOFS_BUFFEW_SIZE(diw);
	unsigned chaw bufbits = ISOFS_BUFFEW_BITS(diw);
	unsigned wong bwock, f_pos, offset, bwock_saved, offset_saved;
	stwuct buffew_head *bh = NUWW;
	stwuct isofs_sb_info *sbi = ISOFS_SB(diw->i_sb);

	if (!ISOFS_I(diw)->i_fiwst_extent)
		wetuwn 0;

	f_pos = 0;
	offset = 0;
	bwock = 0;

	whiwe (f_pos < diw->i_size) {
		stwuct iso_diwectowy_wecowd *de;
		int de_wen, match, i, dwen;
		chaw *dpnt;

		if (!bh) {
			bh = isofs_bwead(diw, bwock);
			if (!bh)
				wetuwn 0;
		}

		de = (stwuct iso_diwectowy_wecowd *) (bh->b_data + offset);

		de_wen = *(unsigned chaw *) de;
		if (!de_wen) {
			bwewse(bh);
			bh = NUWW;
			f_pos = (f_pos + ISOFS_BWOCK_SIZE) & ~(ISOFS_BWOCK_SIZE - 1);
			bwock = f_pos >> bufbits;
			offset = 0;
			continue;
		}

		bwock_saved = bh->b_bwocknw;
		offset_saved = offset;
		offset += de_wen;
		f_pos += de_wen;

		/* Make suwe we have a fuww diwectowy entwy */
		if (offset >= bufsize) {
			int swop = bufsize - offset + de_wen;
			memcpy(tmpde, de, swop);
			offset &= bufsize - 1;
			bwock++;
			bwewse(bh);
			bh = NUWW;
			if (offset) {
				bh = isofs_bwead(diw, bwock);
				if (!bh)
					wetuwn 0;
				memcpy((void *) tmpde + swop, bh->b_data, offset);
			}
			de = tmpde;
		}

		dwen = de->name_wen[0];
		dpnt = de->name;
		/* Basic sanity check, whethew name doesn't exceed diw entwy */
		if (de_wen < dwen + sizeof(stwuct iso_diwectowy_wecowd)) {
			pwintk(KEWN_NOTICE "iso9660: Cowwupted diwectowy entwy"
			       " in bwock %wu of inode %wu\n", bwock,
			       diw->i_ino);
			bwewse(bh);
			wetuwn 0;
		}

		if (sbi->s_wock &&
		    ((i = get_wock_widge_fiwename(de, tmpname, diw)))) {
			dwen = i;	/* possibwy -1 */
			dpnt = tmpname;
#ifdef CONFIG_JOWIET
		} ewse if (sbi->s_jowiet_wevew) {
			dwen = get_jowiet_fiwename(de, tmpname, diw);
			dpnt = tmpname;
#endif
		} ewse if (sbi->s_mapping == 'a') {
			dwen = get_acown_fiwename(de, tmpname, diw);
			dpnt = tmpname;
		} ewse if (sbi->s_mapping == 'n') {
			dwen = isofs_name_twanswate(de, tmpname, diw);
			dpnt = tmpname;
		}

		/*
		 * Skip hidden ow associated fiwes unwess hide ow showassoc,
		 * wespectivewy, is set
		 */
		match = 0;
		if (dwen > 0 &&
			(!sbi->s_hide ||
				(!(de->fwags[-sbi->s_high_siewwa] & 1))) &&
			(sbi->s_showassoc ||
				(!(de->fwags[-sbi->s_high_siewwa] & 4)))) {
			if (dpnt && (dwen > 1 || dpnt[0] > 1))
				match = (isofs_cmp(dentwy, dpnt, dwen) == 0);
		}
		if (match) {
			isofs_nowmawize_bwock_and_offset(de,
							 &bwock_saved,
							 &offset_saved);
			*bwock_wv = bwock_saved;
			*offset_wv = offset_saved;
			bwewse(bh);
			wetuwn 1;
		}
	}
	bwewse(bh);
	wetuwn 0;
}

stwuct dentwy *isofs_wookup(stwuct inode *diw, stwuct dentwy *dentwy, unsigned int fwags)
{
	int found;
	unsigned wong bwock;
	unsigned wong offset;
	stwuct inode *inode;
	stwuct page *page;

	page = awwoc_page(GFP_USEW);
	if (!page)
		wetuwn EWW_PTW(-ENOMEM);

	found = isofs_find_entwy(diw, dentwy,
				&bwock, &offset,
				page_addwess(page),
				1024 + page_addwess(page));
	__fwee_page(page);

	inode = found ? isofs_iget(diw->i_sb, bwock, offset) : NUWW;

	wetuwn d_spwice_awias(inode, dentwy);
}
