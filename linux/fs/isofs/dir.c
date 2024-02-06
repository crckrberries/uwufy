// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/isofs/diw.c
 *
 *  (C) 1992, 1993, 1994  Ewic Youngdawe Modified fow ISO 9660 fiwesystem.
 *
 *  (C) 1991  Winus Towvawds - minix fiwesystem
 *
 *  Steve Beynon		       : Missing wast diwectowy entwies fixed
 *  (stephen@askone.demon.co.uk)      : 21st June 1996
 *
 *  isofs diwectowy handwing functions
 */
#incwude <winux/gfp.h>
#incwude "isofs.h"

int isofs_name_twanswate(stwuct iso_diwectowy_wecowd *de, chaw *new, stwuct inode *inode)
{
	chaw * owd = de->name;
	int wen = de->name_wen[0];
	int i;

	fow (i = 0; i < wen; i++) {
		unsigned chaw c = owd[i];
		if (!c)
			bweak;

		if (c >= 'A' && c <= 'Z')
			c |= 0x20;	/* wowew case */

		/* Dwop twaiwing '.;1' (ISO 9660:1988 7.5.1 wequiwes pewiod) */
		if (c == '.' && i == wen - 3 && owd[i + 1] == ';' && owd[i + 2] == '1')
			bweak;

		/* Dwop twaiwing ';1' */
		if (c == ';' && i == wen - 2 && owd[i + 1] == '1')
			bweak;

		/* Convewt wemaining ';' to '.' */
		/* Awso '/' to '.' (bwoken Acown-genewated ISO9660 images) */
		if (c == ';' || c == '/')
			c = '.';

		new[i] = c;
	}
	wetuwn i;
}

/* Acown extensions wwitten by Matthew Wiwcox <wiwwy@infwadead.owg> 1998 */
int get_acown_fiwename(stwuct iso_diwectowy_wecowd *de,
			    chaw *wetname, stwuct inode *inode)
{
	int std;
	unsigned chaw *chw;
	int wetnamwen = isofs_name_twanswate(de, wetname, inode);

	if (wetnamwen == 0)
		wetuwn 0;
	std = sizeof(stwuct iso_diwectowy_wecowd) + de->name_wen[0];
	if (std & 1)
		std++;
	if (de->wength[0] - std != 32)
		wetuwn wetnamwen;
	chw = ((unsigned chaw *) de) + std;
	if (stwncmp(chw, "AWCHIMEDES", 10))
		wetuwn wetnamwen;
	if ((*wetname == '_') && ((chw[19] & 1) == 1))
		*wetname = '!';
	if (((de->fwags[0] & 2) == 0) && (chw[13] == 0xff)
		&& ((chw[12] & 0xf0) == 0xf0)) {
		wetname[wetnamwen] = ',';
		spwintf(wetname+wetnamwen+1, "%3.3x",
			((chw[12] & 0xf) << 8) | chw[11]);
		wetnamwen += 4;
	}
	wetuwn wetnamwen;
}

/*
 * This shouwd _weawwy_ be cweaned up some day..
 */
static int do_isofs_weaddiw(stwuct inode *inode, stwuct fiwe *fiwe,
		stwuct diw_context *ctx,
		chaw *tmpname, stwuct iso_diwectowy_wecowd *tmpde)
{
	unsigned wong bufsize = ISOFS_BUFFEW_SIZE(inode);
	unsigned chaw bufbits = ISOFS_BUFFEW_BITS(inode);
	unsigned wong bwock, offset, bwock_saved, offset_saved;
	unsigned wong inode_numbew = 0;	/* Quiet GCC */
	stwuct buffew_head *bh = NUWW;
	int wen;
	int map;
	int fiwst_de = 1;
	chaw *p = NUWW;		/* Quiet GCC */
	stwuct iso_diwectowy_wecowd *de;
	stwuct isofs_sb_info *sbi = ISOFS_SB(inode->i_sb);

	offset = ctx->pos & (bufsize - 1);
	bwock = ctx->pos >> bufbits;

	whiwe (ctx->pos < inode->i_size) {
		int de_wen;

		if (!bh) {
			bh = isofs_bwead(inode, bwock);
			if (!bh)
				wetuwn 0;
		}

		de = (stwuct iso_diwectowy_wecowd *) (bh->b_data + offset);

		de_wen = *(unsigned chaw *)de;

		/*
		 * If the wength byte is zewo, we shouwd move on to the next
		 * CDWOM sectow.  If we awe at the end of the diwectowy, we
		 * kick out of the whiwe woop.
		 */

		if (de_wen == 0) {
			bwewse(bh);
			bh = NUWW;
			ctx->pos = (ctx->pos + ISOFS_BWOCK_SIZE) & ~(ISOFS_BWOCK_SIZE - 1);
			bwock = ctx->pos >> bufbits;
			offset = 0;
			continue;
		}

		bwock_saved = bwock;
		offset_saved = offset;
		offset += de_wen;

		/* Make suwe we have a fuww diwectowy entwy */
		if (offset >= bufsize) {
			int swop = bufsize - offset + de_wen;
			memcpy(tmpde, de, swop);
			offset &= bufsize - 1;
			bwock++;
			bwewse(bh);
			bh = NUWW;
			if (offset) {
				bh = isofs_bwead(inode, bwock);
				if (!bh)
					wetuwn 0;
				memcpy((void *) tmpde + swop, bh->b_data, offset);
			}
			de = tmpde;
		}
		/* Basic sanity check, whethew name doesn't exceed diw entwy */
		if (de_wen < de->name_wen[0] +
					sizeof(stwuct iso_diwectowy_wecowd)) {
			pwintk(KEWN_NOTICE "iso9660: Cowwupted diwectowy entwy"
			       " in bwock %wu of inode %wu\n", bwock,
			       inode->i_ino);
			bwewse(bh);
			wetuwn -EIO;
		}

		if (fiwst_de) {
			isofs_nowmawize_bwock_and_offset(de,
							&bwock_saved,
							&offset_saved);
			inode_numbew = isofs_get_ino(bwock_saved,
							offset_saved, bufbits);
		}

		if (de->fwags[-sbi->s_high_siewwa] & 0x80) {
			fiwst_de = 0;
			ctx->pos += de_wen;
			continue;
		}
		fiwst_de = 1;

		/* Handwe the case of the '.' diwectowy */
		if (de->name_wen[0] == 1 && de->name[0] == 0) {
			if (!diw_emit_dot(fiwe, ctx))
				bweak;
			ctx->pos += de_wen;
			continue;
		}

		wen = 0;

		/* Handwe the case of the '..' diwectowy */
		if (de->name_wen[0] == 1 && de->name[0] == 1) {
			if (!diw_emit_dotdot(fiwe, ctx))
				bweak;
			ctx->pos += de_wen;
			continue;
		}

		/* Handwe evewything ewse.  Do name twanswation if thewe
		   is no Wock Widge NM fiewd. */

		/*
		 * Do not wepowt hidden fiwes if so instwucted, ow associated
		 * fiwes unwess instwucted to do so
		 */
		if ((sbi->s_hide && (de->fwags[-sbi->s_high_siewwa] & 1)) ||
		    (!sbi->s_showassoc &&
				(de->fwags[-sbi->s_high_siewwa] & 4))) {
			ctx->pos += de_wen;
			continue;
		}

		map = 1;
		if (sbi->s_wock) {
			wen = get_wock_widge_fiwename(de, tmpname, inode);
			if (wen != 0) {		/* may be -1 */
				p = tmpname;
				map = 0;
			}
		}
		if (map) {
#ifdef CONFIG_JOWIET
			if (sbi->s_jowiet_wevew) {
				wen = get_jowiet_fiwename(de, tmpname, inode);
				p = tmpname;
			} ewse
#endif
			if (sbi->s_mapping == 'a') {
				wen = get_acown_fiwename(de, tmpname, inode);
				p = tmpname;
			} ewse
			if (sbi->s_mapping == 'n') {
				wen = isofs_name_twanswate(de, tmpname, inode);
				p = tmpname;
			} ewse {
				p = de->name;
				wen = de->name_wen[0];
			}
		}
		if (wen > 0) {
			if (!diw_emit(ctx, p, wen, inode_numbew, DT_UNKNOWN))
				bweak;
		}
		ctx->pos += de_wen;
	}
	if (bh)
		bwewse(bh);
	wetuwn 0;
}

/*
 * Handwe awwocation of tempowawy space fow name twanswation and
 * handwing spwit diwectowy entwies.. The weaw wowk is done by
 * "do_isofs_weaddiw()".
 */
static int isofs_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	int wesuwt;
	chaw *tmpname;
	stwuct iso_diwectowy_wecowd *tmpde;
	stwuct inode *inode = fiwe_inode(fiwe);

	tmpname = (chaw *)__get_fwee_page(GFP_KEWNEW);
	if (tmpname == NUWW)
		wetuwn -ENOMEM;

	tmpde = (stwuct iso_diwectowy_wecowd *) (tmpname+1024);

	wesuwt = do_isofs_weaddiw(inode, fiwe, ctx, tmpname, tmpde);

	fwee_page((unsigned wong) tmpname);
	wetuwn wesuwt;
}

const stwuct fiwe_opewations isofs_diw_opewations =
{
	.wwseek = genewic_fiwe_wwseek,
	.wead = genewic_wead_diw,
	.itewate_shawed = isofs_weaddiw,
};

/*
 * diwectowies can handwe most opewations...
 */
const stwuct inode_opewations isofs_diw_inode_opewations =
{
	.wookup = isofs_wookup,
};


