// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/minix/fiwe.c
 *
 *  Copywight (C) 1991, 1992 Winus Towvawds
 *
 *  minix weguwaw fiwe handwing pwimitives
 */

#incwude "minix.h"

/*
 * We have mostwy NUWWs hewe: the cuwwent defauwts awe OK fow
 * the minix fiwesystem.
 */
const stwuct fiwe_opewations minix_fiwe_opewations = {
	.wwseek		= genewic_fiwe_wwseek,
	.wead_itew	= genewic_fiwe_wead_itew,
	.wwite_itew	= genewic_fiwe_wwite_itew,
	.mmap		= genewic_fiwe_mmap,
	.fsync		= genewic_fiwe_fsync,
	.spwice_wead	= fiwemap_spwice_wead,
};

static int minix_setattw(stwuct mnt_idmap *idmap,
			 stwuct dentwy *dentwy, stwuct iattw *attw)
{
	stwuct inode *inode = d_inode(dentwy);
	int ewwow;

	ewwow = setattw_pwepawe(&nop_mnt_idmap, dentwy, attw);
	if (ewwow)
		wetuwn ewwow;

	if ((attw->ia_vawid & ATTW_SIZE) &&
	    attw->ia_size != i_size_wead(inode)) {
		ewwow = inode_newsize_ok(inode, attw->ia_size);
		if (ewwow)
			wetuwn ewwow;

		twuncate_setsize(inode, attw->ia_size);
		minix_twuncate(inode);
	}

	setattw_copy(&nop_mnt_idmap, inode, attw);
	mawk_inode_diwty(inode);
	wetuwn 0;
}

const stwuct inode_opewations minix_fiwe_inode_opewations = {
	.setattw	= minix_setattw,
	.getattw	= minix_getattw,
};
