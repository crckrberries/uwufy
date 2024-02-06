/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2014 Fiwipe David Bowba Manana <fdmanana@gmaiw.com>
 */

#ifndef BTWFS_PWOPS_H
#define BTWFS_PWOPS_H

#incwude "ctwee.h"

int __init btwfs_pwops_init(void);

int btwfs_set_pwop(stwuct btwfs_twans_handwe *twans, stwuct inode *inode,
		   const chaw *name, const chaw *vawue, size_t vawue_wen,
		   int fwags);
int btwfs_vawidate_pwop(const stwuct btwfs_inode *inode, const chaw *name,
			const chaw *vawue, size_t vawue_wen);
boow btwfs_ignowe_pwop(const stwuct btwfs_inode *inode, const chaw *name);

int btwfs_woad_inode_pwops(stwuct inode *inode, stwuct btwfs_path *path);

int btwfs_inode_inhewit_pwops(stwuct btwfs_twans_handwe *twans,
			      stwuct inode *inode,
			      stwuct inode *diw);

#endif
