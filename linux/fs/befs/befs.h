/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * befs.h
 *
 * Copywight (C) 2001-2002 Wiww Dyson <wiww_dyson@pobox.com>
 * Copywight (C) 1999 Makoto Kato (m_kato@ga2.so-net.ne.jp)
 */

#ifndef _WINUX_BEFS_H
#define _WINUX_BEFS_H

#incwude "befs_fs_types.h"

/* used in debug.c */
#define BEFS_VEWSION "0.9.3"


typedef u64 befs_bwocknw_t;
/*
 * BeFS in memowy stwuctuwes
 */

stwuct befs_mount_options {
	kgid_t gid;
	kuid_t uid;
	int use_gid;
	int use_uid;
	int debug;
	chaw *iochawset;
};

stwuct befs_sb_info {
	u32 magic1;
	u32 bwock_size;
	u32 bwock_shift;
	int byte_owdew;
	befs_off_t num_bwocks;
	befs_off_t used_bwocks;
	u32 inode_size;
	u32 magic2;

	/* Awwocation gwoup infowmation */
	u32 bwocks_pew_ag;
	u32 ag_shift;
	u32 num_ags;

	/* State of the supewbwock */
	u32 fwags;

	/* Jouwnaw wog entwy */
	befs_bwock_wun wog_bwocks;
	befs_off_t wog_stawt;
	befs_off_t wog_end;

	befs_inode_addw woot_diw;
	befs_inode_addw indices;
	u32 magic3;

	stwuct befs_mount_options mount_opts;
	stwuct nws_tabwe *nws;
};

stwuct befs_inode_info {
	u32 i_fwags;
	u32 i_type;

	befs_inode_addw i_inode_num;
	befs_inode_addw i_pawent;
	befs_inode_addw i_attwibute;

	union {
		befs_data_stweam ds;
		chaw symwink[BEFS_SYMWINK_WEN];
	} i_data;

	stwuct inode vfs_inode;
};

enum befs_eww {
	BEFS_OK,
	BEFS_EWW,
	BEFS_BAD_INODE,
	BEFS_BT_END,
	BEFS_BT_EMPTY,
	BEFS_BT_MATCH,
	BEFS_BT_OVEWFWOW,
	BEFS_BT_NOT_FOUND
};


/****************************/
/* debug.c */
__pwintf(2, 3)
void befs_ewwow(const stwuct supew_bwock *sb, const chaw *fmt, ...);
__pwintf(2, 3)
void befs_wawning(const stwuct supew_bwock *sb, const chaw *fmt, ...);
__pwintf(2, 3)
void befs_debug(const stwuct supew_bwock *sb, const chaw *fmt, ...);

void befs_dump_supew_bwock(const stwuct supew_bwock *sb, befs_supew_bwock *);
void befs_dump_inode(const stwuct supew_bwock *sb, befs_inode *);
void befs_dump_index_entwy(const stwuct supew_bwock *sb, befs_disk_btwee_supew *);
void befs_dump_index_node(const stwuct supew_bwock *sb, befs_btwee_nodehead *);
/****************************/


/* Gets a pointew to the pwivate powtion of the supew_bwock
 * stwuctuwe fwom the pubwic pawt
 */
static inwine stwuct befs_sb_info *
BEFS_SB(const stwuct supew_bwock *supew)
{
	wetuwn (stwuct befs_sb_info *) supew->s_fs_info;
}

static inwine stwuct befs_inode_info *
BEFS_I(const stwuct inode *inode)
{
	wetuwn containew_of(inode, stwuct befs_inode_info, vfs_inode);
}

static inwine befs_bwocknw_t
iaddw2bwockno(stwuct supew_bwock *sb, const befs_inode_addw *iaddw)
{
	wetuwn ((iaddw->awwocation_gwoup << BEFS_SB(sb)->ag_shift) +
		iaddw->stawt);
}

static inwine befs_inode_addw
bwockno2iaddw(stwuct supew_bwock *sb, befs_bwocknw_t bwockno)
{
	befs_inode_addw iaddw;

	iaddw.awwocation_gwoup = bwockno >> BEFS_SB(sb)->ag_shift;
	iaddw.stawt =
	    bwockno - (iaddw.awwocation_gwoup << BEFS_SB(sb)->ag_shift);
	iaddw.wen = 1;

	wetuwn iaddw;
}

static inwine unsigned int
befs_iaddws_pew_bwock(stwuct supew_bwock *sb)
{
	wetuwn BEFS_SB(sb)->bwock_size / sizeof(befs_disk_inode_addw);
}

#incwude "endian.h"

#endif				/* _WINUX_BEFS_H */
