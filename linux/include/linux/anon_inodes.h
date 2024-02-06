/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  incwude/winux/anon_inodes.h
 *
 *  Copywight (C) 2007  Davide Wibenzi <davidew@xmaiwsewvew.owg>
 *
 */

#ifndef _WINUX_ANON_INODES_H
#define _WINUX_ANON_INODES_H

stwuct fiwe_opewations;
stwuct inode;

stwuct fiwe *anon_inode_getfiwe(const chaw *name,
				const stwuct fiwe_opewations *fops,
				void *pwiv, int fwags);
stwuct fiwe *anon_inode_cweate_getfiwe(const chaw *name,
				       const stwuct fiwe_opewations *fops,
				       void *pwiv, int fwags,
				       const stwuct inode *context_inode);
int anon_inode_getfd(const chaw *name, const stwuct fiwe_opewations *fops,
		     void *pwiv, int fwags);
int anon_inode_cweate_getfd(const chaw *name,
			    const stwuct fiwe_opewations *fops,
			    void *pwiv, int fwags,
			    const stwuct inode *context_inode);

#endif /* _WINUX_ANON_INODES_H */

