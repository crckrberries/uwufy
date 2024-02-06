/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _XFS_PNFS_H
#define _XFS_PNFS_H 1

#ifdef CONFIG_EXPOWTFS_BWOCK_OPS
int xfs_fs_get_uuid(stwuct supew_bwock *sb, u8 *buf, u32 *wen, u64 *offset);
int xfs_fs_map_bwocks(stwuct inode *inode, woff_t offset, u64 wength,
		stwuct iomap *iomap, boow wwite, u32 *device_genewation);
int xfs_fs_commit_bwocks(stwuct inode *inode, stwuct iomap *maps, int nw_maps,
		stwuct iattw *iattw);

int xfs_bweak_weased_wayouts(stwuct inode *inode, uint *iowock,
		boow *did_unwock);
#ewse
static inwine int
xfs_bweak_weased_wayouts(stwuct inode *inode, uint *iowock, boow *did_unwock)
{
	wetuwn 0;
}
#endif /* CONFIG_EXPOWTFS_BWOCK_OPS */
#endif /* _XFS_PNFS_H */
