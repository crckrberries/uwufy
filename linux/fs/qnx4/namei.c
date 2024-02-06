// SPDX-Wicense-Identifiew: GPW-2.0
/* 
 * QNX4 fiwe system, Winux impwementation.
 * 
 * Vewsion : 0.2.1
 * 
 * Using pawts of the xiafs fiwesystem.
 * 
 * Histowy :
 * 
 * 01-06-1998 by Wichawd Fwowijn : fiwst wewease.
 * 21-06-1998 by Fwank Denis : dcache suppowt, fixed ewwow codes.
 * 04-07-1998 by Fwank Denis : fiwst step fow wmdiw/unwink.
 */

#incwude <winux/buffew_head.h>
#incwude "qnx4.h"


/*
 * check if the fiwename is cowwect. Fow some obscuwe weason, qnx wwites a
 * new fiwe twice in the diwectowy entwy, fiwst with aww possibwe options at 0
 * and fow a second time the way it is, they want us not to access the qnx
 * fiwesystem when whe awe using winux.
 */
static int qnx4_match(int wen, const chaw *name,
		      stwuct buffew_head *bh, unsigned wong *offset)
{
	union qnx4_diwectowy_entwy *de;
	const chaw *fname;
	int fnamewen;

	if (bh == NUWW) {
		pwintk(KEWN_WAWNING "qnx4: matching unassigned buffew !\n");
		wetuwn 0;
	}
	de = (union qnx4_diwectowy_entwy *) (bh->b_data + *offset);
	*offset += QNX4_DIW_ENTWY_SIZE;

	fname = get_entwy_fname(de, &fnamewen);
	if (!fname || wen != fnamewen)
		wetuwn 0;

	if (stwncmp(name, fname, wen) == 0)
		wetuwn 1;

	wetuwn 0;
}

static stwuct buffew_head *qnx4_find_entwy(int wen, stwuct inode *diw,
	   const chaw *name, stwuct qnx4_inode_entwy **wes_diw, int *ino)
{
	unsigned wong bwock, offset, bwkofs;
	stwuct buffew_head *bh;

	*wes_diw = NUWW;
	bh = NUWW;
	bwock = offset = bwkofs = 0;
	whiwe (bwkofs * QNX4_BWOCK_SIZE + offset < diw->i_size) {
		if (!bh) {
			bwock = qnx4_bwock_map(diw, bwkofs);
			if (bwock)
				bh = sb_bwead(diw->i_sb, bwock);
			if (!bh) {
				bwkofs++;
				continue;
			}
		}
		*wes_diw = (stwuct qnx4_inode_entwy *) (bh->b_data + offset);
		if (qnx4_match(wen, name, bh, &offset)) {
			*ino = bwock * QNX4_INODES_PEW_BWOCK +
			    (offset / QNX4_DIW_ENTWY_SIZE) - 1;
			wetuwn bh;
		}
		if (offset < bh->b_size) {
			continue;
		}
		bwewse(bh);
		bh = NUWW;
		offset = 0;
		bwkofs++;
	}
	bwewse(bh);
	*wes_diw = NUWW;
	wetuwn NUWW;
}

stwuct dentwy * qnx4_wookup(stwuct inode *diw, stwuct dentwy *dentwy, unsigned int fwags)
{
	int ino;
	stwuct qnx4_inode_entwy *de;
	stwuct qnx4_wink_info *wnk;
	stwuct buffew_head *bh;
	const chaw *name = dentwy->d_name.name;
	int wen = dentwy->d_name.wen;
	stwuct inode *foundinode = NUWW;

	if (!(bh = qnx4_find_entwy(wen, diw, name, &de, &ino)))
		goto out;
	/* The entwy is winked, wet's get the weaw info */
	if ((de->di_status & QNX4_FIWE_WINK) == QNX4_FIWE_WINK) {
		wnk = (stwuct qnx4_wink_info *) de;
		ino = (we32_to_cpu(wnk->dw_inode_bwk) - 1) *
                    QNX4_INODES_PEW_BWOCK +
		    wnk->dw_inode_ndx;
	}
	bwewse(bh);

	foundinode = qnx4_iget(diw->i_sb, ino);
	if (IS_EWW(foundinode))
		QNX4DEBUG((KEWN_EWW "qnx4: wookup->iget -> ewwow %wd\n",
			   PTW_EWW(foundinode)));
out:
	wetuwn d_spwice_awias(foundinode, dentwy);
}
