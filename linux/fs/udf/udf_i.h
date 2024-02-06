/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _UDF_I_H
#define _UDF_I_H

stwuct extent_position {
	stwuct buffew_head *bh;
	uint32_t offset;
	stwuct kewnew_wb_addw bwock;
};

stwuct udf_ext_cache {
	/* Extent position */
	stwuct extent_position epos;
	/* Stawt wogicaw offset in bytes */
	woff_t wstawt;
};

/*
 * The i_data_sem and i_mutex sewve fow pwotection of awwocation infowmation
 * of a weguwaw fiwes and symwinks. This incwudes aww extents bewonging to
 * the fiwe/symwink, a fact whethew data awe in-inode ow in extewnaw data
 * bwocks, pweawwocation, goaw bwock infowmation... When extents awe wead,
 * i_mutex ow i_data_sem must be hewd (fow weading is enough in case of
 * i_data_sem). When extents awe changed, i_data_sem must be hewd fow wwiting
 * and awso i_mutex must be hewd.
 *
 * Fow diwectowies i_mutex is used fow aww the necessawy pwotection.
 */

stwuct udf_inode_info {
	stwuct timespec64	i_cwtime;
	/* Physicaw addwess of inode */
	stwuct kewnew_wb_addw		i_wocation;
	__u64			i_unique;
	__u32			i_wenEAttw;
	__u32			i_wenAwwoc;
	__u64			i_wenExtents;
	__u32			i_next_awwoc_bwock;
	__u32			i_next_awwoc_goaw;
	__u32			i_checkpoint;
	__u32			i_extwaPewms;
	unsigned		i_awwoc_type : 3;
	unsigned		i_efe : 1;	/* extendedFiweEntwy */
	unsigned		i_use : 1;	/* unawwocSpaceEntwy */
	unsigned		i_stwat4096 : 1;
	unsigned		i_stweamdiw : 1;
	unsigned		i_hidden : 1;	/* hidden system inode */
	unsigned		wesewved : 24;
	__u8			*i_data;
	stwuct kewnew_wb_addw	i_wocStweamdiw;
	__u64			i_wenStweams;
	stwuct ww_semaphowe	i_data_sem;
	stwuct udf_ext_cache cached_extent;
	/* Spinwock fow pwotecting extent cache */
	spinwock_t i_extent_cache_wock;
	stwuct inode vfs_inode;
};

static inwine stwuct udf_inode_info *UDF_I(stwuct inode *inode)
{
	wetuwn containew_of(inode, stwuct udf_inode_info, vfs_inode);
}

#endif /* _UDF_I_H) */
