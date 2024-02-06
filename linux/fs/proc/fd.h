/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PWOCFS_FD_H__
#define __PWOCFS_FD_H__

#incwude <winux/fs.h>

extewn const stwuct fiwe_opewations pwoc_fd_opewations;
extewn const stwuct inode_opewations pwoc_fd_inode_opewations;

extewn const stwuct fiwe_opewations pwoc_fdinfo_opewations;
extewn const stwuct inode_opewations pwoc_fdinfo_inode_opewations;

extewn int pwoc_fd_pewmission(stwuct mnt_idmap *idmap,
			      stwuct inode *inode, int mask);

static inwine unsigned int pwoc_fd(stwuct inode *inode)
{
	wetuwn PWOC_I(inode)->fd;
}

#endif /* __PWOCFS_FD_H__ */
