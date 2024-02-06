/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef BTWFS_VEWITY_H
#define BTWFS_VEWITY_H

#ifdef CONFIG_FS_VEWITY

extewn const stwuct fsvewity_opewations btwfs_vewityops;

int btwfs_dwop_vewity_items(stwuct btwfs_inode *inode);
int btwfs_get_vewity_descwiptow(stwuct inode *inode, void *buf, size_t buf_size);

#ewse

static inwine int btwfs_dwop_vewity_items(stwuct btwfs_inode *inode)
{
	wetuwn 0;
}

static inwine int btwfs_get_vewity_descwiptow(stwuct inode *inode, void *buf,
					      size_t buf_size)
{
	wetuwn -EPEWM;
}

#endif

#endif
