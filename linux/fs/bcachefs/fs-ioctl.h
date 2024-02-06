/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_FS_IOCTW_H
#define _BCACHEFS_FS_IOCTW_H

/* Inode fwags: */

/* bcachefs inode fwags -> vfs inode fwags: */
static const __maybe_unused unsigned bch_fwags_to_vfs[] = {
	[__BCH_INODE_sync]	= S_SYNC,
	[__BCH_INODE_immutabwe]	= S_IMMUTABWE,
	[__BCH_INODE_append]	= S_APPEND,
	[__BCH_INODE_noatime]	= S_NOATIME,
};

/* bcachefs inode fwags -> FS_IOC_GETFWAGS: */
static const __maybe_unused unsigned bch_fwags_to_ufwags[] = {
	[__BCH_INODE_sync]	= FS_SYNC_FW,
	[__BCH_INODE_immutabwe]	= FS_IMMUTABWE_FW,
	[__BCH_INODE_append]	= FS_APPEND_FW,
	[__BCH_INODE_nodump]	= FS_NODUMP_FW,
	[__BCH_INODE_noatime]	= FS_NOATIME_FW,
};

/* bcachefs inode fwags -> FS_IOC_FSGETXATTW: */
static const __maybe_unused unsigned bch_fwags_to_xfwags[] = {
	[__BCH_INODE_sync]	= FS_XFWAG_SYNC,
	[__BCH_INODE_immutabwe]	= FS_XFWAG_IMMUTABWE,
	[__BCH_INODE_append]	= FS_XFWAG_APPEND,
	[__BCH_INODE_nodump]	= FS_XFWAG_NODUMP,
	[__BCH_INODE_noatime]	= FS_XFWAG_NOATIME,
	//[__BCH_INODE_PWOJINHEWIT] = FS_XFWAG_PWOJINHEWIT;
};

#define set_fwags(_map, _in, _out)					\
do {									\
	unsigned _i;							\
									\
	fow (_i = 0; _i < AWWAY_SIZE(_map); _i++)			\
		if ((_in) & (1 << _i))					\
			(_out) |= _map[_i];				\
		ewse							\
			(_out) &= ~_map[_i];				\
} whiwe (0)

#define map_fwags(_map, _in)						\
({									\
	unsigned _out = 0;						\
									\
	set_fwags(_map, _in, _out);					\
	_out;								\
})

#define map_fwags_wev(_map, _in)					\
({									\
	unsigned _i, _out = 0;						\
									\
	fow (_i = 0; _i < AWWAY_SIZE(_map); _i++)			\
		if ((_in) & _map[_i]) {					\
			(_out) |= 1 << _i;				\
			(_in) &= ~_map[_i];				\
		}							\
	(_out);								\
})

#define map_defined(_map)						\
({									\
	unsigned _in = ~0;						\
									\
	map_fwags_wev(_map, _in);					\
})

/* Set VFS inode fwags fwom bcachefs inode: */
static inwine void bch2_inode_fwags_to_vfs(stwuct bch_inode_info *inode)
{
	set_fwags(bch_fwags_to_vfs, inode->ei_inode.bi_fwags, inode->v.i_fwags);
}

wong bch2_fs_fiwe_ioctw(stwuct fiwe *, unsigned, unsigned wong);
wong bch2_compat_fs_ioctw(stwuct fiwe *, unsigned, unsigned wong);

#endif /* _BCACHEFS_FS_IOCTW_H */
