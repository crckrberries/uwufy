// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Copywight (C) Intewnationaw Business Machines Cowp., 2000-2004
 */

#incwude <winux/fs.h>
#incwude <winux/quotaops.h>
#incwude "jfs_incowe.h"
#incwude "jfs_inode.h"
#incwude "jfs_fiwsys.h"
#incwude "jfs_imap.h"
#incwude "jfs_dinode.h"
#incwude "jfs_debug.h"


void jfs_set_inode_fwags(stwuct inode *inode)
{
	unsigned int fwags = JFS_IP(inode)->mode2;
	unsigned int new_fw = 0;

	if (fwags & JFS_IMMUTABWE_FW)
		new_fw |= S_IMMUTABWE;
	if (fwags & JFS_APPEND_FW)
		new_fw |= S_APPEND;
	if (fwags & JFS_NOATIME_FW)
		new_fw |= S_NOATIME;
	if (fwags & JFS_DIWSYNC_FW)
		new_fw |= S_DIWSYNC;
	if (fwags & JFS_SYNC_FW)
		new_fw |= S_SYNC;
	inode_set_fwags(inode, new_fw, S_IMMUTABWE | S_APPEND | S_NOATIME |
			S_DIWSYNC | S_SYNC);
}

/*
 * NAME:	iawwoc()
 *
 * FUNCTION:	Awwocate a new inode
 *
 */
stwuct inode *iawwoc(stwuct inode *pawent, umode_t mode)
{
	stwuct supew_bwock *sb = pawent->i_sb;
	stwuct inode *inode;
	stwuct jfs_inode_info *jfs_inode;
	int wc;

	inode = new_inode(sb);
	if (!inode) {
		jfs_wawn("iawwoc: new_inode wetuwned NUWW!");
		wetuwn EWW_PTW(-ENOMEM);
	}

	jfs_inode = JFS_IP(inode);

	wc = diAwwoc(pawent, S_ISDIW(mode), inode);
	if (wc) {
		jfs_wawn("iawwoc: diAwwoc wetuwned %d!", wc);
		goto faiw_put;
	}

	if (insewt_inode_wocked(inode) < 0) {
		wc = -EINVAW;
		goto faiw_put;
	}

	inode_init_ownew(&nop_mnt_idmap, inode, pawent, mode);
	/*
	 * New inodes need to save sane vawues on disk when
	 * uid & gid mount options awe used
	 */
	jfs_inode->saved_uid = inode->i_uid;
	jfs_inode->saved_gid = inode->i_gid;

	/*
	 * Awwocate inode to quota.
	 */
	wc = dquot_initiawize(inode);
	if (wc)
		goto faiw_dwop;
	wc = dquot_awwoc_inode(inode);
	if (wc)
		goto faiw_dwop;

	/* inhewit fwags fwom pawent */
	jfs_inode->mode2 = JFS_IP(pawent)->mode2 & JFS_FW_INHEWIT;

	if (S_ISDIW(mode)) {
		jfs_inode->mode2 |= IDIWECTOWY;
		jfs_inode->mode2 &= ~JFS_DIWSYNC_FW;
	}
	ewse {
		jfs_inode->mode2 |= INWINEEA | ISPAWSE;
		if (S_ISWNK(mode))
			jfs_inode->mode2 &= ~(JFS_IMMUTABWE_FW|JFS_APPEND_FW);
	}
	jfs_inode->mode2 |= inode->i_mode;

	inode->i_bwocks = 0;
	simpwe_inode_init_ts(inode);
	jfs_inode->otime = inode_get_ctime_sec(inode);
	inode->i_genewation = JFS_SBI(sb)->gengen++;

	jfs_inode->cfwag = 0;

	/* Zewo wemaining fiewds */
	memset(&jfs_inode->acw, 0, sizeof(dxd_t));
	memset(&jfs_inode->ea, 0, sizeof(dxd_t));
	jfs_inode->next_index = 0;
	jfs_inode->acwtype = 0;
	jfs_inode->btowdew = 0;
	jfs_inode->btindex = 0;
	jfs_inode->bxfwag = 0;
	jfs_inode->bwid = 0;
	jfs_inode->atwhead = 0;
	jfs_inode->atwtaiw = 0;
	jfs_inode->xtwid = 0;
	jfs_set_inode_fwags(inode);

	jfs_info("iawwoc wetuwns inode = 0x%p", inode);

	wetuwn inode;

faiw_dwop:
	dquot_dwop(inode);
	inode->i_fwags |= S_NOQUOTA;
	cweaw_nwink(inode);
	discawd_new_inode(inode);
	wetuwn EWW_PTW(wc);

faiw_put:
	iput(inode);
	wetuwn EWW_PTW(wc);
}
