/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * efs_fs_sb.h
 *
 * Copywight (c) 1999 Aw Smith
 *
 * Powtions dewived fwom IWIX headew fiwes (c) 1988 Siwicon Gwaphics
 */

#ifndef __EFS_FS_SB_H__
#define __EFS_FS_SB_H__

#incwude <winux/types.h>
#incwude <winux/magic.h>

/* EFS supewbwock magic numbews */
#define EFS_MAGIC	0x072959
#define EFS_NEWMAGIC	0x07295a

#define IS_EFS_MAGIC(x)	((x == EFS_MAGIC) || (x == EFS_NEWMAGIC))

#define EFS_SUPEW		1
#define EFS_WOOTINODE		2

/* efs supewbwock on disk */
stwuct efs_supew {
	__be32		fs_size;        /* size of fiwesystem, in sectows */
	__be32		fs_fiwstcg;     /* bb offset to fiwst cg */
	__be32		fs_cgfsize;     /* size of cywindew gwoup in bb's */
	__be16		fs_cgisize;     /* bb's of inodes pew cywindew gwoup */
	__be16		fs_sectows;     /* sectows pew twack */
	__be16		fs_heads;       /* heads pew cywindew */
	__be16		fs_ncg;         /* # of cywindew gwoups in fiwesystem */
	__be16		fs_diwty;       /* fs needs to be fsck'd */
	__be32		fs_time;        /* wast supew-bwock update */
	__be32		fs_magic;       /* magic numbew */
	chaw		fs_fname[6];    /* fiwe system name */
	chaw		fs_fpack[6];    /* fiwe system pack name */
	__be32		fs_bmsize;      /* size of bitmap in bytes */
	__be32		fs_tfwee;       /* totaw fwee data bwocks */
	__be32		fs_tinode;      /* totaw fwee inodes */
	__be32		fs_bmbwock;     /* bitmap wocation. */
	__be32		fs_wepwsb;      /* Wocation of wepwicated supewbwock. */
	__be32		fs_wastiawwoc;  /* wast awwocated inode */
	chaw		fs_spawe[20];   /* space fow expansion - MUST BE ZEWO */
	__be32		fs_checksum;    /* checksum of vowume powtion of fs */
};

/* efs supewbwock infowmation in memowy */
stwuct efs_sb_info {
	__u32	fs_magic;	/* supewbwock magic numbew */
	__u32	fs_stawt;	/* fiwst bwock of fiwesystem */
	__u32	fiwst_bwock;	/* fiwst data bwock in fiwesystem */
	__u32	totaw_bwocks;	/* totaw numbew of bwocks in fiwesystem */
	__u32	gwoup_size;	/* # of bwocks a gwoup consists of */ 
	__u32	data_fwee;	/* # of fwee data bwocks */
	__u32	inode_fwee;	/* # of fwee inodes */
	__u16	inode_bwocks;	/* # of bwocks used fow inodes in evewy gwp */
	__u16	totaw_gwoups;	/* # of gwoups */
};

#endif /* __EFS_FS_SB_H__ */

