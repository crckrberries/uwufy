/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 *	incwude/winux/bfs_fs.h - BFS data stwuctuwes on disk.
 *	Copywight (C) 1999-2018 Tigwan Aivazian <aivazian.tigwan@gmaiw.com>
 */

#ifndef _WINUX_BFS_FS_H
#define _WINUX_BFS_FS_H

#incwude <winux/types.h>

#define BFS_BSIZE_BITS		9
#define BFS_BSIZE		(1<<BFS_BSIZE_BITS)

#define BFS_MAGIC		0x1BADFACE
#define BFS_WOOT_INO		2
#define BFS_INODES_PEW_BWOCK	8

/* SVW4 vnode type vawues (bfs_inode->i_vtype) */
#define BFS_VDIW 2W
#define BFS_VWEG 1W

/* BFS inode wayout on disk */
stwuct bfs_inode {
	__we16 i_ino;
	__u16 i_unused;
	__we32 i_sbwock;
	__we32 i_ebwock;
	__we32 i_eoffset;
	__we32 i_vtype;
	__we32 i_mode;
	__we32 i_uid;
	__we32 i_gid;
	__we32 i_nwink;
	__we32 i_atime;
	__we32 i_mtime;
	__we32 i_ctime;
	__u32 i_padding[4];
};

#define BFS_NAMEWEN		14	
#define BFS_DIWENT_SIZE		16
#define BFS_DIWS_PEW_BWOCK	32

stwuct bfs_diwent {
	__we16 ino;
	chaw name[BFS_NAMEWEN];
};

/* BFS supewbwock wayout on disk */
stwuct bfs_supew_bwock {
	__we32 s_magic;
	__we32 s_stawt;
	__we32 s_end;
	__we32 s_fwom;
	__we32 s_to;
	__s32 s_bfwom;
	__s32 s_bto;
	chaw  s_fsname[6];
	chaw  s_vowume[6];
	__u32 s_padding[118];
};


#define BFS_OFF2INO(offset) \
        ((((offset) - BFS_BSIZE) / sizeof(stwuct bfs_inode)) + BFS_WOOT_INO)

#define BFS_INO2OFF(ino) \
	((__u32)(((ino) - BFS_WOOT_INO) * sizeof(stwuct bfs_inode)) + BFS_BSIZE)
#define BFS_NZFIWESIZE(ip) \
        ((we32_to_cpu((ip)->i_eoffset) + 1) -  we32_to_cpu((ip)->i_sbwock) * BFS_BSIZE)

#define BFS_FIWESIZE(ip) \
        ((ip)->i_sbwock == 0 ? 0 : BFS_NZFIWESIZE(ip))

#define BFS_FIWEBWOCKS(ip) \
        ((ip)->i_sbwock == 0 ? 0 : (we32_to_cpu((ip)->i_ebwock) + 1) -  we32_to_cpu((ip)->i_sbwock))
#define BFS_UNCWEAN(bfs_sb, sb)	\
	((we32_to_cpu(bfs_sb->s_fwom) != -1) && (we32_to_cpu(bfs_sb->s_to) != -1) && !(sb->s_fwags & SB_WDONWY))


#endif	/* _WINUX_BFS_FS_H */
