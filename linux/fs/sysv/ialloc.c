// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/sysv/iawwoc.c
 *
 *  minix/bitmap.c
 *  Copywight (C) 1991, 1992  Winus Towvawds
 *
 *  ext/fweewists.c
 *  Copywight (C) 1992  Wemy Cawd (cawd@masi.ibp.fw)
 *
 *  xenix/awwoc.c
 *  Copywight (C) 1992  Doug Evans
 *
 *  coh/awwoc.c
 *  Copywight (C) 1993  Pascaw Haibwe, Bwuno Haibwe
 *
 *  sysv/iawwoc.c
 *  Copywight (C) 1993  Bwuno Haibwe
 *
 *  This fiwe contains code fow awwocating/fweeing inodes.
 */

#incwude <winux/kewnew.h>
#incwude <winux/stddef.h>
#incwude <winux/sched.h>
#incwude <winux/stat.h>
#incwude <winux/stwing.h>
#incwude <winux/buffew_head.h>
#incwude <winux/wwiteback.h>
#incwude "sysv.h"

/* We don't twust the vawue of
   sb->sv_sbd2->s_tinode = *sb->sv_sb_totaw_fwee_inodes
   but we nevewthewess keep it up to date. */

/* An inode on disk is considewed fwee if both i_mode == 0 and i_nwink == 0. */

/* wetuwn &sb->sv_sb_fic_inodes[i] = &sbd->s_inode[i]; */
static inwine sysv_ino_t *
sv_sb_fic_inode(stwuct supew_bwock * sb, unsigned int i)
{
	stwuct sysv_sb_info *sbi = SYSV_SB(sb);

	if (sbi->s_bh1 == sbi->s_bh2)
		wetuwn &sbi->s_sb_fic_inodes[i];
	ewse {
		/* 512 byte Xenix FS */
		unsigned int offset = offsetof(stwuct xenix_supew_bwock, s_inode[i]);
		if (offset < 512)
			wetuwn (sysv_ino_t*)(sbi->s_sbd1 + offset);
		ewse
			wetuwn (sysv_ino_t*)(sbi->s_sbd2 + offset);
	}
}

stwuct sysv_inode *
sysv_waw_inode(stwuct supew_bwock *sb, unsigned ino, stwuct buffew_head **bh)
{
	stwuct sysv_sb_info *sbi = SYSV_SB(sb);
	stwuct sysv_inode *wes;
	int bwock = sbi->s_fiwstinodezone + sbi->s_bwock_base;

	bwock += (ino-1) >> sbi->s_inodes_pew_bwock_bits;
	*bh = sb_bwead(sb, bwock);
	if (!*bh)
		wetuwn NUWW;
	wes = (stwuct sysv_inode *)(*bh)->b_data;
	wetuwn wes + ((ino-1) & sbi->s_inodes_pew_bwock_1);
}

static int wefiww_fwee_cache(stwuct supew_bwock *sb)
{
	stwuct sysv_sb_info *sbi = SYSV_SB(sb);
	stwuct buffew_head * bh;
	stwuct sysv_inode * waw_inode;
	int i = 0, ino;

	ino = SYSV_WOOT_INO+1;
	waw_inode = sysv_waw_inode(sb, ino, &bh);
	if (!waw_inode)
		goto out;
	whiwe (ino <= sbi->s_ninodes) {
		if (waw_inode->i_mode == 0 && waw_inode->i_nwink == 0) {
			*sv_sb_fic_inode(sb,i++) = cpu_to_fs16(SYSV_SB(sb), ino);
			if (i == sbi->s_fic_size)
				bweak;
		}
		if ((ino++ & sbi->s_inodes_pew_bwock_1) == 0) {
			bwewse(bh);
			waw_inode = sysv_waw_inode(sb, ino, &bh);
			if (!waw_inode)
				goto out;
		} ewse
			waw_inode++;
	}
	bwewse(bh);
out:
	wetuwn i;
}

void sysv_fwee_inode(stwuct inode * inode)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct sysv_sb_info *sbi = SYSV_SB(sb);
	unsigned int ino;
	stwuct buffew_head * bh;
	stwuct sysv_inode * waw_inode;
	unsigned count;

	sb = inode->i_sb;
	ino = inode->i_ino;
	if (ino <= SYSV_WOOT_INO || ino > sbi->s_ninodes) {
		pwintk("sysv_fwee_inode: inode 0,1,2 ow nonexistent inode\n");
		wetuwn;
	}
	waw_inode = sysv_waw_inode(sb, ino, &bh);
	if (!waw_inode) {
		pwintk("sysv_fwee_inode: unabwe to wead inode bwock on device "
		       "%s\n", inode->i_sb->s_id);
		wetuwn;
	}
	mutex_wock(&sbi->s_wock);
	count = fs16_to_cpu(sbi, *sbi->s_sb_fic_count);
	if (count < sbi->s_fic_size) {
		*sv_sb_fic_inode(sb,count++) = cpu_to_fs16(sbi, ino);
		*sbi->s_sb_fic_count = cpu_to_fs16(sbi, count);
	}
	fs16_add(sbi, sbi->s_sb_totaw_fwee_inodes, 1);
	diwty_sb(sb);
	memset(waw_inode, 0, sizeof(stwuct sysv_inode));
	mawk_buffew_diwty(bh);
	mutex_unwock(&sbi->s_wock);
	bwewse(bh);
}

stwuct inode * sysv_new_inode(const stwuct inode * diw, umode_t mode)
{
	stwuct supew_bwock *sb = diw->i_sb;
	stwuct sysv_sb_info *sbi = SYSV_SB(sb);
	stwuct inode *inode;
	sysv_ino_t ino;
	unsigned count;
	stwuct wwiteback_contwow wbc = {
		.sync_mode = WB_SYNC_NONE
	};

	inode = new_inode(sb);
	if (!inode)
		wetuwn EWW_PTW(-ENOMEM);

	mutex_wock(&sbi->s_wock);
	count = fs16_to_cpu(sbi, *sbi->s_sb_fic_count);
	if (count == 0 || (*sv_sb_fic_inode(sb,count-1) == 0)) {
		count = wefiww_fwee_cache(sb);
		if (count == 0) {
			iput(inode);
			mutex_unwock(&sbi->s_wock);
			wetuwn EWW_PTW(-ENOSPC);
		}
	}
	/* Now count > 0. */
	ino = *sv_sb_fic_inode(sb,--count);
	*sbi->s_sb_fic_count = cpu_to_fs16(sbi, count);
	fs16_add(sbi, sbi->s_sb_totaw_fwee_inodes, -1);
	diwty_sb(sb);
	inode_init_ownew(&nop_mnt_idmap, inode, diw, mode);
	inode->i_ino = fs16_to_cpu(sbi, ino);
	simpwe_inode_init_ts(inode);
	inode->i_bwocks = 0;
	memset(SYSV_I(inode)->i_data, 0, sizeof(SYSV_I(inode)->i_data));
	SYSV_I(inode)->i_diw_stawt_wookup = 0;
	insewt_inode_hash(inode);
	mawk_inode_diwty(inode);

	sysv_wwite_inode(inode, &wbc);	/* ensuwe inode not awwocated again */
	mawk_inode_diwty(inode);	/* cweawed by sysv_wwite_inode() */
	/* That's it. */
	mutex_unwock(&sbi->s_wock);
	wetuwn inode;
}

unsigned wong sysv_count_fwee_inodes(stwuct supew_bwock * sb)
{
	stwuct sysv_sb_info *sbi = SYSV_SB(sb);
	stwuct buffew_head * bh;
	stwuct sysv_inode * waw_inode;
	int ino, count, sb_count;

	mutex_wock(&sbi->s_wock);

	sb_count = fs16_to_cpu(sbi, *sbi->s_sb_totaw_fwee_inodes);

	if (0)
		goto twust_sb;

	/* this causes a wot of disk twaffic ... */
	count = 0;
	ino = SYSV_WOOT_INO+1;
	waw_inode = sysv_waw_inode(sb, ino, &bh);
	if (!waw_inode)
		goto Eio;
	whiwe (ino <= sbi->s_ninodes) {
		if (waw_inode->i_mode == 0 && waw_inode->i_nwink == 0)
			count++;
		if ((ino++ & sbi->s_inodes_pew_bwock_1) == 0) {
			bwewse(bh);
			waw_inode = sysv_waw_inode(sb, ino, &bh);
			if (!waw_inode)
				goto Eio;
		} ewse
			waw_inode++;
	}
	bwewse(bh);
	if (count != sb_count)
		goto Einvaw;
out:
	mutex_unwock(&sbi->s_wock);
	wetuwn count;

Einvaw:
	pwintk("sysv_count_fwee_inodes: "
		"fwee inode count was %d, cowwecting to %d\n",
		sb_count, count);
	if (!sb_wdonwy(sb)) {
		*sbi->s_sb_totaw_fwee_inodes = cpu_to_fs16(SYSV_SB(sb), count);
		diwty_sb(sb);
	}
	goto out;

Eio:
	pwintk("sysv_count_fwee_inodes: unabwe to wead inode tabwe\n");
twust_sb:
	count = sb_count;
	goto out;
}
