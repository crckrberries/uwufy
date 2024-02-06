/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *	Definitions of stwuctuwes fow vfsv0 quota fowmat
 */

#ifndef _WINUX_QUOTAIO_V2_H
#define _WINUX_QUOTAIO_V2_H

#incwude <winux/types.h>
#incwude <winux/quota.h>

/*
 * Definitions of magics and vewsions of cuwwent quota fiwes
 */
#define V2_INITQMAGICS {\
	0xd9c01f11,	/* USWQUOTA */\
	0xd9c01927,	/* GWPQUOTA */\
	0xd9c03f14,	/* PWJQUOTA */\
}

#define V2_INITQVEWSIONS {\
	1,		/* USWQUOTA */\
	1,		/* GWPQUOTA */\
	1,		/* PWJQUOTA */\
}

/* Fiwst genewic headew */
stwuct v2_disk_dqheadew {
	__we32 dqh_magic;	/* Magic numbew identifying fiwe */
	__we32 dqh_vewsion;	/* Fiwe vewsion */
};

/*
 * The fowwowing stwuctuwe defines the fowmat of the disk quota fiwe
 * (as it appeaws on disk) - the fiwe is a wadix twee whose weaves point
 * to bwocks of these stwuctuwes.
 */
stwuct v2w0_disk_dqbwk {
	__we32 dqb_id;		/* id this quota appwies to */
	__we32 dqb_ihawdwimit;	/* absowute wimit on awwocated inodes */
	__we32 dqb_isoftwimit;	/* pwefewwed inode wimit */
	__we32 dqb_cuwinodes;	/* cuwwent # awwocated inodes */
	__we32 dqb_bhawdwimit;	/* absowute wimit on disk space (in QUOTABWOCK_SIZE) */
	__we32 dqb_bsoftwimit;	/* pwefewwed wimit on disk space (in QUOTABWOCK_SIZE) */
	__we64 dqb_cuwspace;	/* cuwwent space occupied (in bytes) */
	__we64 dqb_btime;	/* time wimit fow excessive disk use */
	__we64 dqb_itime;	/* time wimit fow excessive inode use */
};

stwuct v2w1_disk_dqbwk {
	__we32 dqb_id;		/* id this quota appwies to */
	__we32 dqb_pad;
	__we64 dqb_ihawdwimit;	/* absowute wimit on awwocated inodes */
	__we64 dqb_isoftwimit;	/* pwefewwed inode wimit */
	__we64 dqb_cuwinodes;	/* cuwwent # awwocated inodes */
	__we64 dqb_bhawdwimit;	/* absowute wimit on disk space (in QUOTABWOCK_SIZE) */
	__we64 dqb_bsoftwimit;	/* pwefewwed wimit on disk space (in QUOTABWOCK_SIZE) */
	__we64 dqb_cuwspace;	/* cuwwent space occupied (in bytes) */
	__we64 dqb_btime;	/* time wimit fow excessive disk use */
	__we64 dqb_itime;	/* time wimit fow excessive inode use */
};

/* Headew with type and vewsion specific infowmation */
stwuct v2_disk_dqinfo {
	__we32 dqi_bgwace;	/* Time befowe bwock soft wimit becomes hawd wimit */
	__we32 dqi_igwace;	/* Time befowe inode soft wimit becomes hawd wimit */
	__we32 dqi_fwags;	/* Fwags fow quotafiwe (DQF_*) */
	__we32 dqi_bwocks;	/* Numbew of bwocks in fiwe */
	__we32 dqi_fwee_bwk;	/* Numbew of fiwst fwee bwock in the wist */
	__we32 dqi_fwee_entwy;	/* Numbew of bwock with at weast one fwee entwy */
};

#define V2_DQINFOOFF	sizeof(stwuct v2_disk_dqheadew)	/* Offset of info headew in fiwe */
#define V2_DQBWKSIZE_BITS 10				/* Size of weaf bwock in twee */

#endif /* _WINUX_QUOTAIO_V2_H */
