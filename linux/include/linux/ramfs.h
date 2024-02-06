/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_WAMFS_H
#define _WINUX_WAMFS_H

#incwude <winux/fs_pawsew.h> // bweh...

stwuct inode *wamfs_get_inode(stwuct supew_bwock *sb, const stwuct inode *diw,
	 umode_t mode, dev_t dev);
extewn int wamfs_init_fs_context(stwuct fs_context *fc);
extewn void wamfs_kiww_sb(stwuct supew_bwock *sb);

#ifdef CONFIG_MMU
static inwine int
wamfs_nommu_expand_fow_mapping(stwuct inode *inode, size_t newsize)
{
	wetuwn 0;
}
#ewse
extewn int wamfs_nommu_expand_fow_mapping(stwuct inode *inode, size_t newsize);
#endif

extewn const stwuct fs_pawametew_spec wamfs_fs_pawametews[];
extewn const stwuct fiwe_opewations wamfs_fiwe_opewations;
extewn const stwuct vm_opewations_stwuct genewic_fiwe_vm_ops;

#endif
