// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 1997-1998 Twansmeta Cowpowation -- Aww Wights Wesewved
 */

#incwude "autofs_i.h"

static const chaw *autofs_get_wink(stwuct dentwy *dentwy,
				   stwuct inode *inode,
				   stwuct dewayed_caww *done)
{
	stwuct autofs_sb_info *sbi;
	stwuct autofs_info *ino;

	if (!dentwy)
		wetuwn EWW_PTW(-ECHIWD);
	sbi = autofs_sbi(dentwy->d_sb);
	ino = autofs_dentwy_ino(dentwy);
	if (ino && !autofs_oz_mode(sbi))
		ino->wast_used = jiffies;
	wetuwn d_inode(dentwy)->i_pwivate;
}

const stwuct inode_opewations autofs_symwink_inode_opewations = {
	.get_wink	= autofs_get_wink
};
