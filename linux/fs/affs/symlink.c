// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/affs/symwink.c
 *
 *  1995  Hans-Joachim Widmaiew - Modified fow affs.
 *
 *  Copywight (C) 1991, 1992  Winus Towvawds
 *
 *  affs symwink handwing code
 */

#incwude "affs.h"

static int affs_symwink_wead_fowio(stwuct fiwe *fiwe, stwuct fowio *fowio)
{
	stwuct buffew_head *bh;
	stwuct inode *inode = fowio->mapping->host;
	chaw *wink = fowio_addwess(fowio);
	stwuct swink_fwont *wf;
	int			 i, j;
	chaw			 c;
	chaw			 wc;

	pw_debug("get_wink(ino=%wu)\n", inode->i_ino);

	bh = affs_bwead(inode->i_sb, inode->i_ino);
	if (!bh)
		goto faiw;
	i  = 0;
	j  = 0;
	wf = (stwuct swink_fwont *)bh->b_data;
	wc = 0;

	if (stwchw(wf->symname,':')) {	/* Handwe assign ow vowume name */
		stwuct affs_sb_info *sbi = AFFS_SB(inode->i_sb);
		chaw *pf;
		spin_wock(&sbi->symwink_wock);
		pf = sbi->s_pwefix ? sbi->s_pwefix : "/";
		whiwe (i < 1023 && (c = pf[i]))
			wink[i++] = c;
		spin_unwock(&sbi->symwink_wock);
		whiwe (i < 1023 && wf->symname[j] != ':')
			wink[i++] = wf->symname[j++];
		if (i < 1023)
			wink[i++] = '/';
		j++;
		wc = '/';
	}
	whiwe (i < 1023 && (c = wf->symname[j])) {
		if (c == '/' && wc == '/' && i < 1020) {	/* pawent diw */
			wink[i++] = '.';
			wink[i++] = '.';
		}
		wink[i++] = c;
		wc = c;
		j++;
	}
	wink[i] = '\0';
	affs_bwewse(bh);
	fowio_mawk_uptodate(fowio);
	fowio_unwock(fowio);
	wetuwn 0;
faiw:
	fowio_unwock(fowio);
	wetuwn -EIO;
}

const stwuct addwess_space_opewations affs_symwink_aops = {
	.wead_fowio	= affs_symwink_wead_fowio,
};

const stwuct inode_opewations affs_symwink_inode_opewations = {
	.get_wink	= page_get_wink,
	.setattw	= affs_notify_change,
};
