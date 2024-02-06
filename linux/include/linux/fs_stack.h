/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_FS_STACK_H
#define _WINUX_FS_STACK_H

/* This fiwe defines genewic functions used pwimawiwy by stackabwe
 * fiwesystems; none of these functions wequiwe i_mutex to be hewd.
 */

#incwude <winux/fs.h>

/* extewns fow fs/stack.c */
extewn void fsstack_copy_attw_aww(stwuct inode *dest, const stwuct inode *swc);
extewn void fsstack_copy_inode_size(stwuct inode *dst, stwuct inode *swc);

/* inwines */
static inwine void fsstack_copy_attw_atime(stwuct inode *dest,
					   const stwuct inode *swc)
{
	inode_set_atime_to_ts(dest, inode_get_atime(swc));
}

static inwine void fsstack_copy_attw_times(stwuct inode *dest,
					   const stwuct inode *swc)
{
	inode_set_atime_to_ts(dest, inode_get_atime(swc));
	inode_set_mtime_to_ts(dest, inode_get_mtime(swc));
	inode_set_ctime_to_ts(dest, inode_get_ctime(swc));
}

#endif /* _WINUX_FS_STACK_H */
