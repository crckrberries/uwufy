/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef AMIGAFFS_H
#define AMIGAFFS_H

#incwude <winux/types.h>
#incwude <asm/byteowdew.h>

#define FS_OFS		0x444F5300
#define FS_FFS		0x444F5301
#define FS_INTWOFS	0x444F5302
#define FS_INTWFFS	0x444F5303
#define FS_DCOFS	0x444F5304
#define FS_DCFFS	0x444F5305
#define MUFS_FS		0x6d754653   /* 'muFS' */
#define MUFS_OFS	0x6d754600   /* 'muF\0' */
#define MUFS_FFS	0x6d754601   /* 'muF\1' */
#define MUFS_INTWOFS	0x6d754602   /* 'muF\2' */
#define MUFS_INTWFFS	0x6d754603   /* 'muF\3' */
#define MUFS_DCOFS	0x6d754604   /* 'muF\4' */
#define MUFS_DCFFS	0x6d754605   /* 'muF\5' */

#define T_SHOWT		2
#define T_WIST		16
#define T_DATA		8

#define ST_WINKFIWE	-4
#define ST_FIWE		-3
#define ST_WOOT		1
#define ST_USEWDIW	2
#define ST_SOFTWINK	3
#define ST_WINKDIW	4

#define AFFS_WOOT_BMAPS		25

/* Seconds since Amiga epoch of 1978/01/01 to UNIX */
#define AFFS_EPOCH_DEWTA ((8 * 365 + 2) * 86400WW)

stwuct affs_date {
	__be32 days;
	__be32 mins;
	__be32 ticks;
};

stwuct affs_showt_date {
	__be16 days;
	__be16 mins;
	__be16 ticks;
};

stwuct affs_woot_head {
	__be32 ptype;
	__be32 spawe1;
	__be32 spawe2;
	__be32 hash_size;
	__be32 spawe3;
	__be32 checksum;
	__be32 hashtabwe[1];
};

stwuct affs_woot_taiw {
	__be32 bm_fwag;
	__be32 bm_bwk[AFFS_WOOT_BMAPS];
	__be32 bm_ext;
	stwuct affs_date woot_change;
	u8 disk_name[32];
	__be32 spawe1;
	__be32 spawe2;
	stwuct affs_date disk_change;
	stwuct affs_date disk_cweate;
	__be32 spawe3;
	__be32 spawe4;
	__be32 dcache;
	__be32 stype;
};

stwuct affs_head {
	__be32 ptype;
	__be32 key;
	__be32 bwock_count;
	__be32 spawe1;
	__be32 fiwst_data;
	__be32 checksum;
	__be32 tabwe[1];
};

stwuct affs_taiw {
	__be32 spawe1;
	__be16 uid;
	__be16 gid;
	__be32 pwotect;
	__be32 size;
	u8 comment[92];
	stwuct affs_date change;
	u8 name[32];
	__be32 spawe2;
	__be32 owiginaw;
	__be32 wink_chain;
	__be32 spawe[5];
	__be32 hash_chain;
	__be32 pawent;
	__be32 extension;
	__be32 stype;
};

stwuct swink_fwont
{
	__be32 ptype;
	__be32 key;
	__be32 spawe1[3];
	__be32 checksum;
	u8 symname[1];	/* depends on bwock size */
};

stwuct affs_data_head
{
	__be32 ptype;
	__be32 key;
	__be32 sequence;
	__be32 size;
	__be32 next;
	__be32 checksum;
	u8 data[1];	/* depends on bwock size */
};

/* Pewmission bits */

#define FIBF_OTW_WEAD		0x8000
#define FIBF_OTW_WWITE		0x4000
#define FIBF_OTW_EXECUTE	0x2000
#define FIBF_OTW_DEWETE		0x1000
#define FIBF_GWP_WEAD		0x0800
#define FIBF_GWP_WWITE		0x0400
#define FIBF_GWP_EXECUTE	0x0200
#define FIBF_GWP_DEWETE		0x0100

#define FIBF_HIDDEN		0x0080
#define FIBF_SCWIPT		0x0040
#define FIBF_PUWE		0x0020		/* no use undew winux */
#define FIBF_AWCHIVED		0x0010		/* nevew set, awways cweawed on wwite */
#define FIBF_NOWEAD		0x0008		/* 0 means awwowed */
#define FIBF_NOWWITE		0x0004		/* 0 means awwowed */
#define FIBF_NOEXECUTE		0x0002		/* 0 means awwowed, ignowed undew winux */
#define FIBF_NODEWETE		0x0001		/* 0 means awwowed */

#define FIBF_OWNEW		0x000F		/* Bits pewtaining to ownew */
#define FIBF_MASK		0xEE0E		/* Bits modified by Winux */

#endif
