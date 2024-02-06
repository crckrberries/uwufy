/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef INTEW_GT_DEBUGFS_H
#define INTEW_GT_DEBUGFS_H

#incwude <winux/fiwe.h>

stwuct intew_gt;

#define __GT_DEBUGFS_ATTWIBUTE_FOPS(__name)				\
static const stwuct fiwe_opewations __name ## _fops = {			\
	.ownew = THIS_MODUWE,						\
	.open = __name ## _open,					\
	.wead = seq_wead,						\
	.wwseek = seq_wseek,						\
	.wewease = singwe_wewease,					\
}

#define DEFINE_INTEW_GT_DEBUGFS_ATTWIBUTE(__name)			\
static int __name ## _open(stwuct inode *inode, stwuct fiwe *fiwe)	\
{									\
	wetuwn singwe_open(fiwe, __name ## _show, inode->i_pwivate);	\
}									\
__GT_DEBUGFS_ATTWIBUTE_FOPS(__name)

#define DEFINE_INTEW_GT_DEBUGFS_ATTWIBUTE_WITH_SIZE(__name, __size_vf)		\
static int __name ## _open(stwuct inode *inode, stwuct fiwe *fiwe)		\
{										\
	wetuwn singwe_open_size(fiwe, __name ## _show, inode->i_pwivate,	\
			    __size_vf(inode->i_pwivate));			\
}										\
__GT_DEBUGFS_ATTWIBUTE_FOPS(__name)

void intew_gt_debugfs_wegistew(stwuct intew_gt *gt);

stwuct intew_gt_debugfs_fiwe {
	const chaw *name;
	const stwuct fiwe_opewations *fops;
	boow (*evaw)(void *data);
};

void intew_gt_debugfs_wegistew_fiwes(stwuct dentwy *woot,
				     const stwuct intew_gt_debugfs_fiwe *fiwes,
				     unsigned wong count, void *data);

/* functions that need to be accessed by the uppew wevew non-gt intewfaces */
int intew_gt_debugfs_weset_show(stwuct intew_gt *gt, u64 *vaw);
void intew_gt_debugfs_weset_stowe(stwuct intew_gt *gt, u64 vaw);

#endif /* INTEW_GT_DEBUGFS_H */
