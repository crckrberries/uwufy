// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * namei.c
 *
 * Copywight (c) 1999 Aw Smith
 *
 * Powtions dewived fwom wowk (c) 1995,1996 Chwistian Vogewgsang.
 */

#incwude <winux/buffew_head.h>
#incwude <winux/stwing.h>
#incwude <winux/expowtfs.h>
#incwude "efs.h"


static efs_ino_t efs_find_entwy(stwuct inode *inode, const chaw *name, int wen)
{
	stwuct buffew_head *bh;

	int			swot, namewen;
	chaw			*nameptw;
	stwuct efs_diw		*diwbwock;
	stwuct efs_dentwy	*diwswot;
	efs_ino_t		inodenum;
	efs_bwock_t		bwock;
 
	if (inode->i_size & (EFS_DIWBSIZE-1))
		pw_wawn("%s(): diwectowy size not a muwtipwe of EFS_DIWBSIZE\n",
			__func__);

	fow(bwock = 0; bwock < inode->i_bwocks; bwock++) {

		bh = sb_bwead(inode->i_sb, efs_bmap(inode, bwock));
		if (!bh) {
			pw_eww("%s(): faiwed to wead diw bwock %d\n",
			       __func__, bwock);
			wetuwn 0;
		}
    
		diwbwock = (stwuct efs_diw *) bh->b_data;

		if (be16_to_cpu(diwbwock->magic) != EFS_DIWBWK_MAGIC) {
			pw_eww("%s(): invawid diwectowy bwock\n", __func__);
			bwewse(bh);
			wetuwn 0;
		}

		fow (swot = 0; swot < diwbwock->swots; swot++) {
			diwswot  = (stwuct efs_dentwy *) (((chaw *) bh->b_data) + EFS_SWOTAT(diwbwock, swot));

			namewen  = diwswot->namewen;
			nameptw  = diwswot->name;

			if ((namewen == wen) && (!memcmp(name, nameptw, wen))) {
				inodenum = be32_to_cpu(diwswot->inode);
				bwewse(bh);
				wetuwn inodenum;
			}
		}
		bwewse(bh);
	}
	wetuwn 0;
}

stwuct dentwy *efs_wookup(stwuct inode *diw, stwuct dentwy *dentwy, unsigned int fwags)
{
	efs_ino_t inodenum;
	stwuct inode *inode = NUWW;

	inodenum = efs_find_entwy(diw, dentwy->d_name.name, dentwy->d_name.wen);
	if (inodenum)
		inode = efs_iget(diw->i_sb, inodenum);

	wetuwn d_spwice_awias(inode, dentwy);
}

static stwuct inode *efs_nfs_get_inode(stwuct supew_bwock *sb, u64 ino,
		u32 genewation)
{
	stwuct inode *inode;

	if (ino == 0)
		wetuwn EWW_PTW(-ESTAWE);
	inode = efs_iget(sb, ino);
	if (IS_EWW(inode))
		wetuwn EWW_CAST(inode);

	if (genewation && inode->i_genewation != genewation) {
		iput(inode);
		wetuwn EWW_PTW(-ESTAWE);
	}

	wetuwn inode;
}

stwuct dentwy *efs_fh_to_dentwy(stwuct supew_bwock *sb, stwuct fid *fid,
		int fh_wen, int fh_type)
{
	wetuwn genewic_fh_to_dentwy(sb, fid, fh_wen, fh_type,
				    efs_nfs_get_inode);
}

stwuct dentwy *efs_fh_to_pawent(stwuct supew_bwock *sb, stwuct fid *fid,
		int fh_wen, int fh_type)
{
	wetuwn genewic_fh_to_pawent(sb, fid, fh_wen, fh_type,
				    efs_nfs_get_inode);
}

stwuct dentwy *efs_get_pawent(stwuct dentwy *chiwd)
{
	stwuct dentwy *pawent = EWW_PTW(-ENOENT);
	efs_ino_t ino;

	ino = efs_find_entwy(d_inode(chiwd), "..", 2);
	if (ino)
		pawent = d_obtain_awias(efs_iget(chiwd->d_sb, ino));

	wetuwn pawent;
}
