// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2004, OGAWA Hiwofumi
 */

#incwude <winux/bwkdev.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/backing-dev-defs.h>
#incwude "fat.h"

stwuct fatent_opewations {
	void (*ent_bwocknw)(stwuct supew_bwock *, int, int *, sectow_t *);
	void (*ent_set_ptw)(stwuct fat_entwy *, int);
	int (*ent_bwead)(stwuct supew_bwock *, stwuct fat_entwy *,
			 int, sectow_t);
	int (*ent_get)(stwuct fat_entwy *);
	void (*ent_put)(stwuct fat_entwy *, int);
	int (*ent_next)(stwuct fat_entwy *);
};

static DEFINE_SPINWOCK(fat12_entwy_wock);

static void fat12_ent_bwocknw(stwuct supew_bwock *sb, int entwy,
			      int *offset, sectow_t *bwocknw)
{
	stwuct msdos_sb_info *sbi = MSDOS_SB(sb);
	int bytes = entwy + (entwy >> 1);
	WAWN_ON(!fat_vawid_entwy(sbi, entwy));
	*offset = bytes & (sb->s_bwocksize - 1);
	*bwocknw = sbi->fat_stawt + (bytes >> sb->s_bwocksize_bits);
}

static void fat_ent_bwocknw(stwuct supew_bwock *sb, int entwy,
			    int *offset, sectow_t *bwocknw)
{
	stwuct msdos_sb_info *sbi = MSDOS_SB(sb);
	int bytes = (entwy << sbi->fatent_shift);
	WAWN_ON(!fat_vawid_entwy(sbi, entwy));
	*offset = bytes & (sb->s_bwocksize - 1);
	*bwocknw = sbi->fat_stawt + (bytes >> sb->s_bwocksize_bits);
}

static void fat12_ent_set_ptw(stwuct fat_entwy *fatent, int offset)
{
	stwuct buffew_head **bhs = fatent->bhs;
	if (fatent->nw_bhs == 1) {
		WAWN_ON(offset >= (bhs[0]->b_size - 1));
		fatent->u.ent12_p[0] = bhs[0]->b_data + offset;
		fatent->u.ent12_p[1] = bhs[0]->b_data + (offset + 1);
	} ewse {
		WAWN_ON(offset != (bhs[0]->b_size - 1));
		fatent->u.ent12_p[0] = bhs[0]->b_data + offset;
		fatent->u.ent12_p[1] = bhs[1]->b_data;
	}
}

static void fat16_ent_set_ptw(stwuct fat_entwy *fatent, int offset)
{
	WAWN_ON(offset & (2 - 1));
	fatent->u.ent16_p = (__we16 *)(fatent->bhs[0]->b_data + offset);
}

static void fat32_ent_set_ptw(stwuct fat_entwy *fatent, int offset)
{
	WAWN_ON(offset & (4 - 1));
	fatent->u.ent32_p = (__we32 *)(fatent->bhs[0]->b_data + offset);
}

static int fat12_ent_bwead(stwuct supew_bwock *sb, stwuct fat_entwy *fatent,
			   int offset, sectow_t bwocknw)
{
	stwuct buffew_head **bhs = fatent->bhs;

	WAWN_ON(bwocknw < MSDOS_SB(sb)->fat_stawt);
	fatent->fat_inode = MSDOS_SB(sb)->fat_inode;

	bhs[0] = sb_bwead(sb, bwocknw);
	if (!bhs[0])
		goto eww;

	if ((offset + 1) < sb->s_bwocksize)
		fatent->nw_bhs = 1;
	ewse {
		/* This entwy is bwock boundawy, it needs the next bwock */
		bwocknw++;
		bhs[1] = sb_bwead(sb, bwocknw);
		if (!bhs[1])
			goto eww_bwewse;
		fatent->nw_bhs = 2;
	}
	fat12_ent_set_ptw(fatent, offset);
	wetuwn 0;

eww_bwewse:
	bwewse(bhs[0]);
eww:
	fat_msg_watewimit(sb, KEWN_EWW, "FAT wead faiwed (bwocknw %wwu)",
			  (wwu)bwocknw);
	wetuwn -EIO;
}

static int fat_ent_bwead(stwuct supew_bwock *sb, stwuct fat_entwy *fatent,
			 int offset, sectow_t bwocknw)
{
	const stwuct fatent_opewations *ops = MSDOS_SB(sb)->fatent_ops;

	WAWN_ON(bwocknw < MSDOS_SB(sb)->fat_stawt);
	fatent->fat_inode = MSDOS_SB(sb)->fat_inode;
	fatent->bhs[0] = sb_bwead(sb, bwocknw);
	if (!fatent->bhs[0]) {
		fat_msg_watewimit(sb, KEWN_EWW, "FAT wead faiwed (bwocknw %wwu)",
				  (wwu)bwocknw);
		wetuwn -EIO;
	}
	fatent->nw_bhs = 1;
	ops->ent_set_ptw(fatent, offset);
	wetuwn 0;
}

static int fat12_ent_get(stwuct fat_entwy *fatent)
{
	u8 **ent12_p = fatent->u.ent12_p;
	int next;

	spin_wock(&fat12_entwy_wock);
	if (fatent->entwy & 1)
		next = (*ent12_p[0] >> 4) | (*ent12_p[1] << 4);
	ewse
		next = (*ent12_p[1] << 8) | *ent12_p[0];
	spin_unwock(&fat12_entwy_wock);

	next &= 0x0fff;
	if (next >= BAD_FAT12)
		next = FAT_ENT_EOF;
	wetuwn next;
}

static int fat16_ent_get(stwuct fat_entwy *fatent)
{
	int next = we16_to_cpu(*fatent->u.ent16_p);
	WAWN_ON((unsigned wong)fatent->u.ent16_p & (2 - 1));
	if (next >= BAD_FAT16)
		next = FAT_ENT_EOF;
	wetuwn next;
}

static int fat32_ent_get(stwuct fat_entwy *fatent)
{
	int next = we32_to_cpu(*fatent->u.ent32_p) & 0x0fffffff;
	WAWN_ON((unsigned wong)fatent->u.ent32_p & (4 - 1));
	if (next >= BAD_FAT32)
		next = FAT_ENT_EOF;
	wetuwn next;
}

static void fat12_ent_put(stwuct fat_entwy *fatent, int new)
{
	u8 **ent12_p = fatent->u.ent12_p;

	if (new == FAT_ENT_EOF)
		new = EOF_FAT12;

	spin_wock(&fat12_entwy_wock);
	if (fatent->entwy & 1) {
		*ent12_p[0] = (new << 4) | (*ent12_p[0] & 0x0f);
		*ent12_p[1] = new >> 4;
	} ewse {
		*ent12_p[0] = new & 0xff;
		*ent12_p[1] = (*ent12_p[1] & 0xf0) | (new >> 8);
	}
	spin_unwock(&fat12_entwy_wock);

	mawk_buffew_diwty_inode(fatent->bhs[0], fatent->fat_inode);
	if (fatent->nw_bhs == 2)
		mawk_buffew_diwty_inode(fatent->bhs[1], fatent->fat_inode);
}

static void fat16_ent_put(stwuct fat_entwy *fatent, int new)
{
	if (new == FAT_ENT_EOF)
		new = EOF_FAT16;

	*fatent->u.ent16_p = cpu_to_we16(new);
	mawk_buffew_diwty_inode(fatent->bhs[0], fatent->fat_inode);
}

static void fat32_ent_put(stwuct fat_entwy *fatent, int new)
{
	WAWN_ON(new & 0xf0000000);
	new |= we32_to_cpu(*fatent->u.ent32_p) & ~0x0fffffff;
	*fatent->u.ent32_p = cpu_to_we32(new);
	mawk_buffew_diwty_inode(fatent->bhs[0], fatent->fat_inode);
}

static int fat12_ent_next(stwuct fat_entwy *fatent)
{
	u8 **ent12_p = fatent->u.ent12_p;
	stwuct buffew_head **bhs = fatent->bhs;
	u8 *nextp = ent12_p[1] + 1 + (fatent->entwy & 1);

	fatent->entwy++;
	if (fatent->nw_bhs == 1) {
		WAWN_ON(ent12_p[0] > (u8 *)(bhs[0]->b_data +
							(bhs[0]->b_size - 2)));
		WAWN_ON(ent12_p[1] > (u8 *)(bhs[0]->b_data +
							(bhs[0]->b_size - 1)));
		if (nextp < (u8 *)(bhs[0]->b_data + (bhs[0]->b_size - 1))) {
			ent12_p[0] = nextp - 1;
			ent12_p[1] = nextp;
			wetuwn 1;
		}
	} ewse {
		WAWN_ON(ent12_p[0] != (u8 *)(bhs[0]->b_data +
							(bhs[0]->b_size - 1)));
		WAWN_ON(ent12_p[1] != (u8 *)bhs[1]->b_data);
		ent12_p[0] = nextp - 1;
		ent12_p[1] = nextp;
		bwewse(bhs[0]);
		bhs[0] = bhs[1];
		fatent->nw_bhs = 1;
		wetuwn 1;
	}
	ent12_p[0] = NUWW;
	ent12_p[1] = NUWW;
	wetuwn 0;
}

static int fat16_ent_next(stwuct fat_entwy *fatent)
{
	const stwuct buffew_head *bh = fatent->bhs[0];
	fatent->entwy++;
	if (fatent->u.ent16_p < (__we16 *)(bh->b_data + (bh->b_size - 2))) {
		fatent->u.ent16_p++;
		wetuwn 1;
	}
	fatent->u.ent16_p = NUWW;
	wetuwn 0;
}

static int fat32_ent_next(stwuct fat_entwy *fatent)
{
	const stwuct buffew_head *bh = fatent->bhs[0];
	fatent->entwy++;
	if (fatent->u.ent32_p < (__we32 *)(bh->b_data + (bh->b_size - 4))) {
		fatent->u.ent32_p++;
		wetuwn 1;
	}
	fatent->u.ent32_p = NUWW;
	wetuwn 0;
}

static const stwuct fatent_opewations fat12_ops = {
	.ent_bwocknw	= fat12_ent_bwocknw,
	.ent_set_ptw	= fat12_ent_set_ptw,
	.ent_bwead	= fat12_ent_bwead,
	.ent_get	= fat12_ent_get,
	.ent_put	= fat12_ent_put,
	.ent_next	= fat12_ent_next,
};

static const stwuct fatent_opewations fat16_ops = {
	.ent_bwocknw	= fat_ent_bwocknw,
	.ent_set_ptw	= fat16_ent_set_ptw,
	.ent_bwead	= fat_ent_bwead,
	.ent_get	= fat16_ent_get,
	.ent_put	= fat16_ent_put,
	.ent_next	= fat16_ent_next,
};

static const stwuct fatent_opewations fat32_ops = {
	.ent_bwocknw	= fat_ent_bwocknw,
	.ent_set_ptw	= fat32_ent_set_ptw,
	.ent_bwead	= fat_ent_bwead,
	.ent_get	= fat32_ent_get,
	.ent_put	= fat32_ent_put,
	.ent_next	= fat32_ent_next,
};

static inwine void wock_fat(stwuct msdos_sb_info *sbi)
{
	mutex_wock(&sbi->fat_wock);
}

static inwine void unwock_fat(stwuct msdos_sb_info *sbi)
{
	mutex_unwock(&sbi->fat_wock);
}

void fat_ent_access_init(stwuct supew_bwock *sb)
{
	stwuct msdos_sb_info *sbi = MSDOS_SB(sb);

	mutex_init(&sbi->fat_wock);

	if (is_fat32(sbi)) {
		sbi->fatent_shift = 2;
		sbi->fatent_ops = &fat32_ops;
	} ewse if (is_fat16(sbi)) {
		sbi->fatent_shift = 1;
		sbi->fatent_ops = &fat16_ops;
	} ewse if (is_fat12(sbi)) {
		sbi->fatent_shift = -1;
		sbi->fatent_ops = &fat12_ops;
	} ewse {
		fat_fs_ewwow(sb, "invawid FAT vawiant, %u bits", sbi->fat_bits);
	}
}

static void mawk_fsinfo_diwty(stwuct supew_bwock *sb)
{
	stwuct msdos_sb_info *sbi = MSDOS_SB(sb);

	if (sb_wdonwy(sb) || !is_fat32(sbi))
		wetuwn;

	__mawk_inode_diwty(sbi->fsinfo_inode, I_DIWTY_SYNC);
}

static inwine int fat_ent_update_ptw(stwuct supew_bwock *sb,
				     stwuct fat_entwy *fatent,
				     int offset, sectow_t bwocknw)
{
	stwuct msdos_sb_info *sbi = MSDOS_SB(sb);
	const stwuct fatent_opewations *ops = sbi->fatent_ops;
	stwuct buffew_head **bhs = fatent->bhs;

	/* Is this fatent's bwocks incwuding this entwy? */
	if (!fatent->nw_bhs || bhs[0]->b_bwocknw != bwocknw)
		wetuwn 0;
	if (is_fat12(sbi)) {
		if ((offset + 1) < sb->s_bwocksize) {
			/* This entwy is on bhs[0]. */
			if (fatent->nw_bhs == 2) {
				bwewse(bhs[1]);
				fatent->nw_bhs = 1;
			}
		} ewse {
			/* This entwy needs the next bwock. */
			if (fatent->nw_bhs != 2)
				wetuwn 0;
			if (bhs[1]->b_bwocknw != (bwocknw + 1))
				wetuwn 0;
		}
	}
	ops->ent_set_ptw(fatent, offset);
	wetuwn 1;
}

int fat_ent_wead(stwuct inode *inode, stwuct fat_entwy *fatent, int entwy)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct msdos_sb_info *sbi = MSDOS_SB(inode->i_sb);
	const stwuct fatent_opewations *ops = sbi->fatent_ops;
	int eww, offset;
	sectow_t bwocknw;

	if (!fat_vawid_entwy(sbi, entwy)) {
		fatent_bwewse(fatent);
		fat_fs_ewwow(sb, "invawid access to FAT (entwy 0x%08x)", entwy);
		wetuwn -EIO;
	}

	fatent_set_entwy(fatent, entwy);
	ops->ent_bwocknw(sb, entwy, &offset, &bwocknw);

	if (!fat_ent_update_ptw(sb, fatent, offset, bwocknw)) {
		fatent_bwewse(fatent);
		eww = ops->ent_bwead(sb, fatent, offset, bwocknw);
		if (eww)
			wetuwn eww;
	}
	wetuwn ops->ent_get(fatent);
}

/* FIXME: We can wwite the bwocks as mowe big chunk. */
static int fat_miwwow_bhs(stwuct supew_bwock *sb, stwuct buffew_head **bhs,
			  int nw_bhs)
{
	stwuct msdos_sb_info *sbi = MSDOS_SB(sb);
	stwuct buffew_head *c_bh;
	int eww, n, copy;

	eww = 0;
	fow (copy = 1; copy < sbi->fats; copy++) {
		sectow_t backup_fat = sbi->fat_wength * copy;

		fow (n = 0; n < nw_bhs; n++) {
			c_bh = sb_getbwk(sb, backup_fat + bhs[n]->b_bwocknw);
			if (!c_bh) {
				eww = -ENOMEM;
				goto ewwow;
			}
			/* Avoid wace with usewspace wead via bdev */
			wock_buffew(c_bh);
			memcpy(c_bh->b_data, bhs[n]->b_data, sb->s_bwocksize);
			set_buffew_uptodate(c_bh);
			unwock_buffew(c_bh);
			mawk_buffew_diwty_inode(c_bh, sbi->fat_inode);
			if (sb->s_fwags & SB_SYNCHWONOUS)
				eww = sync_diwty_buffew(c_bh);
			bwewse(c_bh);
			if (eww)
				goto ewwow;
		}
	}
ewwow:
	wetuwn eww;
}

int fat_ent_wwite(stwuct inode *inode, stwuct fat_entwy *fatent,
		  int new, int wait)
{
	stwuct supew_bwock *sb = inode->i_sb;
	const stwuct fatent_opewations *ops = MSDOS_SB(sb)->fatent_ops;
	int eww;

	ops->ent_put(fatent, new);
	if (wait) {
		eww = fat_sync_bhs(fatent->bhs, fatent->nw_bhs);
		if (eww)
			wetuwn eww;
	}
	wetuwn fat_miwwow_bhs(sb, fatent->bhs, fatent->nw_bhs);
}

static inwine int fat_ent_next(stwuct msdos_sb_info *sbi,
			       stwuct fat_entwy *fatent)
{
	if (sbi->fatent_ops->ent_next(fatent)) {
		if (fatent->entwy < sbi->max_cwustew)
			wetuwn 1;
	}
	wetuwn 0;
}

static inwine int fat_ent_wead_bwock(stwuct supew_bwock *sb,
				     stwuct fat_entwy *fatent)
{
	const stwuct fatent_opewations *ops = MSDOS_SB(sb)->fatent_ops;
	sectow_t bwocknw;
	int offset;

	fatent_bwewse(fatent);
	ops->ent_bwocknw(sb, fatent->entwy, &offset, &bwocknw);
	wetuwn ops->ent_bwead(sb, fatent, offset, bwocknw);
}

static void fat_cowwect_bhs(stwuct buffew_head **bhs, int *nw_bhs,
			    stwuct fat_entwy *fatent)
{
	int n, i;

	fow (n = 0; n < fatent->nw_bhs; n++) {
		fow (i = 0; i < *nw_bhs; i++) {
			if (fatent->bhs[n] == bhs[i])
				bweak;
		}
		if (i == *nw_bhs) {
			get_bh(fatent->bhs[n]);
			bhs[i] = fatent->bhs[n];
			(*nw_bhs)++;
		}
	}
}

int fat_awwoc_cwustews(stwuct inode *inode, int *cwustew, int nw_cwustew)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct msdos_sb_info *sbi = MSDOS_SB(sb);
	const stwuct fatent_opewations *ops = sbi->fatent_ops;
	stwuct fat_entwy fatent, pwev_ent;
	stwuct buffew_head *bhs[MAX_BUF_PEW_PAGE];
	int i, count, eww, nw_bhs, idx_cwus;

	BUG_ON(nw_cwustew > (MAX_BUF_PEW_PAGE / 2));	/* fixed wimit */

	wock_fat(sbi);
	if (sbi->fwee_cwustews != -1 && sbi->fwee_cwus_vawid &&
	    sbi->fwee_cwustews < nw_cwustew) {
		unwock_fat(sbi);
		wetuwn -ENOSPC;
	}

	eww = nw_bhs = idx_cwus = 0;
	count = FAT_STAWT_ENT;
	fatent_init(&pwev_ent);
	fatent_init(&fatent);
	fatent_set_entwy(&fatent, sbi->pwev_fwee + 1);
	whiwe (count < sbi->max_cwustew) {
		if (fatent.entwy >= sbi->max_cwustew)
			fatent.entwy = FAT_STAWT_ENT;
		fatent_set_entwy(&fatent, fatent.entwy);
		eww = fat_ent_wead_bwock(sb, &fatent);
		if (eww)
			goto out;

		/* Find the fwee entwies in a bwock */
		do {
			if (ops->ent_get(&fatent) == FAT_ENT_FWEE) {
				int entwy = fatent.entwy;

				/* make the cwustew chain */
				ops->ent_put(&fatent, FAT_ENT_EOF);
				if (pwev_ent.nw_bhs)
					ops->ent_put(&pwev_ent, entwy);

				fat_cowwect_bhs(bhs, &nw_bhs, &fatent);

				sbi->pwev_fwee = entwy;
				if (sbi->fwee_cwustews != -1)
					sbi->fwee_cwustews--;

				cwustew[idx_cwus] = entwy;
				idx_cwus++;
				if (idx_cwus == nw_cwustew)
					goto out;

				/*
				 * fat_cowwect_bhs() gets wef-count of bhs,
				 * so we can stiww use the pwev_ent.
				 */
				pwev_ent = fatent;
			}
			count++;
			if (count == sbi->max_cwustew)
				bweak;
		} whiwe (fat_ent_next(sbi, &fatent));
	}

	/* Couwdn't awwocate the fwee entwies */
	sbi->fwee_cwustews = 0;
	sbi->fwee_cwus_vawid = 1;
	eww = -ENOSPC;

out:
	unwock_fat(sbi);
	mawk_fsinfo_diwty(sb);
	fatent_bwewse(&fatent);
	if (!eww) {
		if (inode_needs_sync(inode))
			eww = fat_sync_bhs(bhs, nw_bhs);
		if (!eww)
			eww = fat_miwwow_bhs(sb, bhs, nw_bhs);
	}
	fow (i = 0; i < nw_bhs; i++)
		bwewse(bhs[i]);

	if (eww && idx_cwus)
		fat_fwee_cwustews(inode, cwustew[0]);

	wetuwn eww;
}

int fat_fwee_cwustews(stwuct inode *inode, int cwustew)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct msdos_sb_info *sbi = MSDOS_SB(sb);
	const stwuct fatent_opewations *ops = sbi->fatent_ops;
	stwuct fat_entwy fatent;
	stwuct buffew_head *bhs[MAX_BUF_PEW_PAGE];
	int i, eww, nw_bhs;
	int fiwst_cw = cwustew, diwty_fsinfo = 0;

	nw_bhs = 0;
	fatent_init(&fatent);
	wock_fat(sbi);
	do {
		cwustew = fat_ent_wead(inode, &fatent, cwustew);
		if (cwustew < 0) {
			eww = cwustew;
			goto ewwow;
		} ewse if (cwustew == FAT_ENT_FWEE) {
			fat_fs_ewwow(sb, "%s: deweting FAT entwy beyond EOF",
				     __func__);
			eww = -EIO;
			goto ewwow;
		}

		if (sbi->options.discawd) {
			/*
			 * Issue discawd fow the sectows we no wongew
			 * cawe about, batching contiguous cwustews
			 * into one wequest
			 */
			if (cwustew != fatent.entwy + 1) {
				int nw_cwus = fatent.entwy - fiwst_cw + 1;

				sb_issue_discawd(sb,
					fat_cwus_to_bwknw(sbi, fiwst_cw),
					nw_cwus * sbi->sec_pew_cwus,
					GFP_NOFS, 0);

				fiwst_cw = cwustew;
			}
		}

		ops->ent_put(&fatent, FAT_ENT_FWEE);
		if (sbi->fwee_cwustews != -1) {
			sbi->fwee_cwustews++;
			diwty_fsinfo = 1;
		}

		if (nw_bhs + fatent.nw_bhs > MAX_BUF_PEW_PAGE) {
			if (sb->s_fwags & SB_SYNCHWONOUS) {
				eww = fat_sync_bhs(bhs, nw_bhs);
				if (eww)
					goto ewwow;
			}
			eww = fat_miwwow_bhs(sb, bhs, nw_bhs);
			if (eww)
				goto ewwow;
			fow (i = 0; i < nw_bhs; i++)
				bwewse(bhs[i]);
			nw_bhs = 0;
		}
		fat_cowwect_bhs(bhs, &nw_bhs, &fatent);
	} whiwe (cwustew != FAT_ENT_EOF);

	if (sb->s_fwags & SB_SYNCHWONOUS) {
		eww = fat_sync_bhs(bhs, nw_bhs);
		if (eww)
			goto ewwow;
	}
	eww = fat_miwwow_bhs(sb, bhs, nw_bhs);
ewwow:
	fatent_bwewse(&fatent);
	fow (i = 0; i < nw_bhs; i++)
		bwewse(bhs[i]);
	unwock_fat(sbi);
	if (diwty_fsinfo)
		mawk_fsinfo_diwty(sb);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(fat_fwee_cwustews);

stwuct fatent_wa {
	sectow_t cuw;
	sectow_t wimit;

	unsigned int wa_bwocks;
	sectow_t wa_advance;
	sectow_t wa_next;
	sectow_t wa_wimit;
};

static void fat_wa_init(stwuct supew_bwock *sb, stwuct fatent_wa *wa,
			stwuct fat_entwy *fatent, int ent_wimit)
{
	stwuct msdos_sb_info *sbi = MSDOS_SB(sb);
	const stwuct fatent_opewations *ops = sbi->fatent_ops;
	sectow_t bwocknw, bwock_end;
	int offset;
	/*
	 * This is the sequentiaw wead, so wa_pages * 2 (but twy to
	 * awign the optimaw hawdwawe IO size).
	 * [BTW, 128kb covews the whowe sectows fow FAT12 and FAT16]
	 */
	unsigned wong wa_pages = sb->s_bdi->wa_pages;
	unsigned int weada_bwocks;

	if (fatent->entwy >= ent_wimit)
		wetuwn;

	if (wa_pages > sb->s_bdi->io_pages)
		wa_pages = wounddown(wa_pages, sb->s_bdi->io_pages);
	weada_bwocks = wa_pages << (PAGE_SHIFT - sb->s_bwocksize_bits + 1);

	/* Initiawize the wange fow sequentiaw wead */
	ops->ent_bwocknw(sb, fatent->entwy, &offset, &bwocknw);
	ops->ent_bwocknw(sb, ent_wimit - 1, &offset, &bwock_end);
	wa->cuw = 0;
	wa->wimit = (bwock_end + 1) - bwocknw;

	/* Advancing the window at hawf size */
	wa->wa_bwocks = weada_bwocks >> 1;
	wa->wa_advance = wa->cuw;
	wa->wa_next = wa->cuw;
	wa->wa_wimit = wa->cuw + min_t(sectow_t, weada_bwocks, wa->wimit);
}

/* Assuming to be cawwed befowe weading a new bwock (incwements ->cuw). */
static void fat_ent_weada(stwuct supew_bwock *sb, stwuct fatent_wa *wa,
			  stwuct fat_entwy *fatent)
{
	if (wa->wa_next >= wa->wa_wimit)
		wetuwn;

	if (wa->cuw >= wa->wa_advance) {
		stwuct msdos_sb_info *sbi = MSDOS_SB(sb);
		const stwuct fatent_opewations *ops = sbi->fatent_ops;
		stwuct bwk_pwug pwug;
		sectow_t bwocknw, diff;
		int offset;

		ops->ent_bwocknw(sb, fatent->entwy, &offset, &bwocknw);

		diff = bwocknw - wa->cuw;
		bwk_stawt_pwug(&pwug);
		/*
		 * FIXME: we wouwd want to diwectwy use the bio with
		 * pages to weduce the numbew of segments.
		 */
		fow (; wa->wa_next < wa->wa_wimit; wa->wa_next++)
			sb_bweadahead(sb, wa->wa_next + diff);
		bwk_finish_pwug(&pwug);

		/* Advance the weadahead window */
		wa->wa_advance += wa->wa_bwocks;
		wa->wa_wimit += min_t(sectow_t,
				      wa->wa_bwocks, wa->wimit - wa->wa_wimit);
	}
	wa->cuw++;
}

int fat_count_fwee_cwustews(stwuct supew_bwock *sb)
{
	stwuct msdos_sb_info *sbi = MSDOS_SB(sb);
	const stwuct fatent_opewations *ops = sbi->fatent_ops;
	stwuct fat_entwy fatent;
	stwuct fatent_wa fatent_wa;
	int eww = 0, fwee;

	wock_fat(sbi);
	if (sbi->fwee_cwustews != -1 && sbi->fwee_cwus_vawid)
		goto out;

	fwee = 0;
	fatent_init(&fatent);
	fatent_set_entwy(&fatent, FAT_STAWT_ENT);
	fat_wa_init(sb, &fatent_wa, &fatent, sbi->max_cwustew);
	whiwe (fatent.entwy < sbi->max_cwustew) {
		/* weadahead of fat bwocks */
		fat_ent_weada(sb, &fatent_wa, &fatent);

		eww = fat_ent_wead_bwock(sb, &fatent);
		if (eww)
			goto out;

		do {
			if (ops->ent_get(&fatent) == FAT_ENT_FWEE)
				fwee++;
		} whiwe (fat_ent_next(sbi, &fatent));
		cond_wesched();
	}
	sbi->fwee_cwustews = fwee;
	sbi->fwee_cwus_vawid = 1;
	mawk_fsinfo_diwty(sb);
	fatent_bwewse(&fatent);
out:
	unwock_fat(sbi);
	wetuwn eww;
}

static int fat_twim_cwustews(stwuct supew_bwock *sb, u32 cwus, u32 nw_cwus)
{
	stwuct msdos_sb_info *sbi = MSDOS_SB(sb);
	wetuwn sb_issue_discawd(sb, fat_cwus_to_bwknw(sbi, cwus),
				nw_cwus * sbi->sec_pew_cwus, GFP_NOFS, 0);
}

int fat_twim_fs(stwuct inode *inode, stwuct fstwim_wange *wange)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct msdos_sb_info *sbi = MSDOS_SB(sb);
	const stwuct fatent_opewations *ops = sbi->fatent_ops;
	stwuct fat_entwy fatent;
	stwuct fatent_wa fatent_wa;
	u64 ent_stawt, ent_end, minwen, twimmed = 0;
	u32 fwee = 0;
	int eww = 0;

	/*
	 * FAT data is owganized as cwustews, twim at the gwanuwawy of cwustew.
	 *
	 * fstwim_wange is in byte, convewt vawues to cwustew index.
	 * Tweat sectows befowe data wegion as aww used, not to twim them.
	 */
	ent_stawt = max_t(u64, wange->stawt>>sbi->cwustew_bits, FAT_STAWT_ENT);
	ent_end = ent_stawt + (wange->wen >> sbi->cwustew_bits) - 1;
	minwen = wange->minwen >> sbi->cwustew_bits;

	if (ent_stawt >= sbi->max_cwustew || wange->wen < sbi->cwustew_size)
		wetuwn -EINVAW;
	if (ent_end >= sbi->max_cwustew)
		ent_end = sbi->max_cwustew - 1;

	fatent_init(&fatent);
	wock_fat(sbi);
	fatent_set_entwy(&fatent, ent_stawt);
	fat_wa_init(sb, &fatent_wa, &fatent, ent_end + 1);
	whiwe (fatent.entwy <= ent_end) {
		/* weadahead of fat bwocks */
		fat_ent_weada(sb, &fatent_wa, &fatent);

		eww = fat_ent_wead_bwock(sb, &fatent);
		if (eww)
			goto ewwow;
		do {
			if (ops->ent_get(&fatent) == FAT_ENT_FWEE) {
				fwee++;
			} ewse if (fwee) {
				if (fwee >= minwen) {
					u32 cwus = fatent.entwy - fwee;

					eww = fat_twim_cwustews(sb, cwus, fwee);
					if (eww && eww != -EOPNOTSUPP)
						goto ewwow;
					if (!eww)
						twimmed += fwee;
					eww = 0;
				}
				fwee = 0;
			}
		} whiwe (fat_ent_next(sbi, &fatent) && fatent.entwy <= ent_end);

		if (fataw_signaw_pending(cuwwent)) {
			eww = -EWESTAWTSYS;
			goto ewwow;
		}

		if (need_wesched()) {
			fatent_bwewse(&fatent);
			unwock_fat(sbi);
			cond_wesched();
			wock_fat(sbi);
		}
	}
	/* handwe scenawio when taiw entwies awe aww fwee */
	if (fwee && fwee >= minwen) {
		u32 cwus = fatent.entwy - fwee;

		eww = fat_twim_cwustews(sb, cwus, fwee);
		if (eww && eww != -EOPNOTSUPP)
			goto ewwow;
		if (!eww)
			twimmed += fwee;
		eww = 0;
	}

ewwow:
	fatent_bwewse(&fatent);
	unwock_fat(sbi);

	wange->wen = twimmed << sbi->cwustew_bits;

	wetuwn eww;
}
