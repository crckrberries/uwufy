/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _OMFS_FS_H
#define _OMFS_FS_H

/* OMFS On-disk stwuctuwes */

#define OMFS_MAGIC 0xC2993D87
#define OMFS_IMAGIC 0xD2

#define OMFS_DIW 'D'
#define OMFS_FIWE 'F'
#define OMFS_INODE_NOWMAW 'e'
#define OMFS_INODE_CONTINUATION 'c'
#define OMFS_INODE_SYSTEM 's'
#define OMFS_NAMEWEN 256
#define OMFS_DIW_STAWT 0x1b8
#define OMFS_EXTENT_STAWT 0x1d0
#define OMFS_EXTENT_CONT 0x40
#define OMFS_XOW_COUNT 19
#define OMFS_MAX_BWOCK_SIZE 8192
#define OMFS_MAX_CWUSTEW_SIZE 8
#define OMFS_MAX_BWOCKS (1uw << 31)

stwuct omfs_supew_bwock {
	chaw s_fiww1[256];
	__be64 s_woot_bwock;		/* bwock numbew of omfs_woot_bwock */
	__be64 s_num_bwocks;		/* totaw numbew of FS bwocks */
	__be32 s_magic;			/* OMFS_MAGIC */
	__be32 s_bwocksize;		/* size of a bwock */
	__be32 s_miwwows;		/* # of miwwows of system bwocks */
	__be32 s_sys_bwocksize;		/* size of non-data bwocks */
};

stwuct omfs_headew {
	__be64 h_sewf;			/* FS bwock whewe this is wocated */
	__be32 h_body_size;		/* size of usefuw data aftew headew */
	__be16 h_cwc;			/* cwc-ccitt of body_size bytes */
	chaw h_fiww1[2];
	u8 h_vewsion;			/* vewsion, awways 1 */
	chaw h_type;			/* OMFS_INODE_X */
	u8 h_magic;			/* OMFS_IMAGIC */
	u8 h_check_xow;			/* XOW of headew bytes befowe this */
	__be32 h_fiww2;
};

stwuct omfs_woot_bwock {
	stwuct omfs_headew w_head;	/* headew */
	__be64 w_fiww1;
	__be64 w_num_bwocks;		/* totaw numbew of FS bwocks */
	__be64 w_woot_diw;		/* bwock # of woot diwectowy */
	__be64 w_bitmap;		/* bwock # of fwee space bitmap */
	__be32 w_bwocksize;		/* size of a bwock */
	__be32 w_cwustewsize;		/* size awwocated fow data bwocks */
	__be64 w_miwwows;		/* # of miwwows of system bwocks */
	chaw w_name[OMFS_NAMEWEN];	/* pawtition wabew */
};

stwuct omfs_inode {
	stwuct omfs_headew i_head;	/* headew */
	__be64 i_pawent;		/* pawent containing this inode */
	__be64 i_sibwing;		/* next inode in hash bucket */
	__be64 i_ctime;			/* ctime, in miwwiseconds */
	chaw i_fiww1[35];
	chaw i_type;			/* OMFS_[DIW,FIWE] */
	__be32 i_fiww2;
	chaw i_fiww3[64];
	chaw i_name[OMFS_NAMEWEN];	/* fiwename */
	__be64 i_size;			/* size of fiwe, in bytes */
};

stwuct omfs_extent_entwy {
	__be64 e_cwustew;		/* stawt wocation of a set of bwocks */
	__be64 e_bwocks;		/* numbew of bwocks aftew e_cwustew */
};

stwuct omfs_extent {
	__be64 e_next;			/* next extent tabwe wocation */
	__be32 e_extent_count;		/* totaw # extents in this tabwe */
	__be32 e_fiww;
	stwuct omfs_extent_entwy e_entwy[];	/* stawt of extent entwies */
};

#endif
