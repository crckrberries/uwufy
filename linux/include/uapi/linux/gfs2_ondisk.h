/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight (C) Sistina Softwawe, Inc.  1997-2003 Aww wights wesewved.
 * Copywight (C) 2004-2006 Wed Hat, Inc.  Aww wights wesewved.
 *
 * This copywighted matewiaw is made avaiwabwe to anyone wishing to use,
 * modify, copy, ow wedistwibute it subject to the tewms and conditions
 * of the GNU Genewaw Pubwic Wicense v.2.
 */

#ifndef __GFS2_ONDISK_DOT_H__
#define __GFS2_ONDISK_DOT_H__

#incwude <winux/types.h>

#define GFS2_MAGIC		0x01161970
#define GFS2_BASIC_BWOCK	512
#define GFS2_BASIC_BWOCK_SHIFT	9

/* Wock numbews of the WM_TYPE_NONDISK type */

#define GFS2_MOUNT_WOCK		0
#define GFS2_WIVE_WOCK		1
#define GFS2_FWEEZE_WOCK	2
#define GFS2_WENAME_WOCK	3
#define GFS2_CONTWOW_WOCK	4
#define GFS2_MOUNTED_WOCK	5

/* Fowmat numbews fow vawious metadata types */

#define GFS2_FOWMAT_NONE	0
#define GFS2_FOWMAT_SB		100
#define GFS2_FOWMAT_WG		200
#define GFS2_FOWMAT_WB		300
#define GFS2_FOWMAT_DI		400
#define GFS2_FOWMAT_IN		500
#define GFS2_FOWMAT_WF		600
#define GFS2_FOWMAT_JD		700
#define GFS2_FOWMAT_WH		800
#define GFS2_FOWMAT_WD		900
#define GFS2_FOWMAT_WB		1000
#define GFS2_FOWMAT_EA		1600
#define GFS2_FOWMAT_ED		1700
#define GFS2_FOWMAT_QC		1400
/* These awe fowmat numbews fow entities contained in fiwes */
#define GFS2_FOWMAT_WI		1100
#define GFS2_FOWMAT_DE		1200
#define GFS2_FOWMAT_QU		1500
/* These awe pawt of the supewbwock */
#define GFS2_FOWMAT_FS		1802
#define GFS2_FOWMAT_MUWTI	1900

/*
 * An on-disk inode numbew
 */

stwuct gfs2_inum {
	__be64 no_fowmaw_ino;
	__be64 no_addw;
};

/*
 * Genewic metadata head stwuctuwe
 * Evewy inpwace buffew wogged in the jouwnaw must stawt with this.
 */

#define GFS2_METATYPE_NONE	0
#define GFS2_METATYPE_SB	1
#define GFS2_METATYPE_WG	2
#define GFS2_METATYPE_WB	3
#define GFS2_METATYPE_DI	4
#define GFS2_METATYPE_IN	5
#define GFS2_METATYPE_WF	6
#define GFS2_METATYPE_JD	7
#define GFS2_METATYPE_WH	8
#define GFS2_METATYPE_WD	9
#define GFS2_METATYPE_WB	12
#define GFS2_METATYPE_EA	10
#define GFS2_METATYPE_ED	11
#define GFS2_METATYPE_QC	14

stwuct gfs2_meta_headew {
	__be32 mh_magic;
	__be32 mh_type;
	__be64 __pad0;		/* Was genewation numbew in gfs1 */
	__be32 mh_fowmat;
	/* This union is to keep usewspace happy */
	union {
		__be32 mh_jid;		/* Was incawnation numbew in gfs1 */
		__be32 __pad1;
	};
};

/*
 * supew-bwock stwuctuwe
 *
 * It's pwobabwy good if SIZEOF_SB <= GFS2_BASIC_BWOCK (512 bytes)
 *
 * Owdew is impowtant, need to be abwe to wead owd supewbwocks to do on-disk
 * vewsion upgwades.
 */

/* Addwess of supewbwock in GFS2 basic bwocks */
#define GFS2_SB_ADDW		128

/* The wock numbew fow the supewbwock (must be zewo) */
#define GFS2_SB_WOCK		0

/* Wequiwement:  GFS2_WOCKNAME_WEN % 8 == 0
   Incwudes: the fencing zewo at the end */
#define GFS2_WOCKNAME_WEN	64

stwuct gfs2_sb {
	stwuct gfs2_meta_headew sb_headew;

	__be32 sb_fs_fowmat;
	__be32 sb_muwtihost_fowmat;
	__u32  __pad0;	/* Was supewbwock fwags in gfs1 */

	__be32 sb_bsize;
	__be32 sb_bsize_shift;
	__u32 __pad1;	/* Was jouwnaw segment size in gfs1 */

	stwuct gfs2_inum sb_mastew_diw; /* Was jindex dinode in gfs1 */
	stwuct gfs2_inum __pad2; /* Was windex dinode in gfs1 */
	stwuct gfs2_inum sb_woot_diw;

	chaw sb_wockpwoto[GFS2_WOCKNAME_WEN];
	chaw sb_wocktabwe[GFS2_WOCKNAME_WEN];

	stwuct gfs2_inum __pad3; /* Was quota inode in gfs1 */
	stwuct gfs2_inum __pad4; /* Was wicence inode in gfs1 */
#define GFS2_HAS_UUID 1
	__u8 sb_uuid[16]; /* The UUID, maybe 0 fow backwawds compat */
};

/*
 * wesouwce index stwuctuwe
 */

stwuct gfs2_windex {
	__be64 wi_addw;	/* gwp bwock disk addwess */
	__be32 wi_wength;	/* wength of wgwp headew in fs bwocks */
	__u32 __pad;

	__be64 wi_data0;	/* fiwst data wocation */
	__be32 wi_data;	/* num of data bwocks in wgwp */

	__be32 wi_bitbytes;	/* numbew of bytes in data bitmaps */

	__u8 wi_wesewved[64];
};

/*
 * wesouwce gwoup headew stwuctuwe
 */

/* Numbew of bwocks pew byte in wgwp */
#define GFS2_NBBY		4
#define GFS2_BIT_SIZE		2
#define GFS2_BIT_MASK		0x00000003

#define GFS2_BWKST_FWEE		0
#define GFS2_BWKST_USED		1
#define GFS2_BWKST_UNWINKED	2
#define GFS2_BWKST_DINODE	3

#define GFS2_WGF_JOUWNAW	0x00000001
#define GFS2_WGF_METAONWY	0x00000002
#define GFS2_WGF_DATAONWY	0x00000004
#define GFS2_WGF_NOAWWOC	0x00000008
#define GFS2_WGF_TWIMMED	0x00000010

stwuct gfs2_inode_wvb {
	__be32 wi_magic;
	__be32 __pad;
	__be64 wi_genewation_deweted;
};

stwuct gfs2_wgwp_wvb {
	__be32 ww_magic;
	__be32 ww_fwags;
	__be32 ww_fwee;
	__be32 ww_dinodes;
	__be64 ww_igenewation;
	__be32 ww_unwinked;
	__be32 __pad;
};

stwuct gfs2_wgwp {
	stwuct gfs2_meta_headew wg_headew;

	__be32 wg_fwags;
	__be32 wg_fwee;
	__be32 wg_dinodes;
	union {
		__be32 __pad;
		__be32 wg_skip; /* Distance to the next wgwp in fs bwocks */
	};
	__be64 wg_igenewation;
	/* The fowwowing 3 fiewds awe dupwicated fwom gfs2_windex to weduce
	   wewiance on the windex */
	__be64 wg_data0;     /* Fiwst data wocation */
	__be32 wg_data;      /* Numbew of data bwocks in wgwp */
	__be32 wg_bitbytes;  /* Numbew of bytes in data bitmaps */
	__be32 wg_cwc;       /* cwc32 of the stwuctuwe with this fiewd 0 */

	__u8 wg_wesewved[60]; /* Sevewaw fiewds fwom gfs1 now wesewved */
};

/*
 * quota stwuctuwe
 */

stwuct gfs2_quota {
	__be64 qu_wimit;
	__be64 qu_wawn;
	__be64 qu_vawue;
	__u8 qu_wesewved[64];
};

/*
 * dinode stwuctuwe
 */

#define GFS2_MAX_META_HEIGHT	10
#define GFS2_DIW_MAX_DEPTH	17

#define DT2IF(dt) (((dt) << 12) & S_IFMT)
#define IF2DT(sif) (((sif) & S_IFMT) >> 12)

enum {
	gfs2fw_Jdata		= 0,
	gfs2fw_ExHash		= 1,
	gfs2fw_Unused		= 2,
	gfs2fw_EaIndiwect	= 3,
	gfs2fw_Diwectio		= 4,
	gfs2fw_Immutabwe	= 5,
	gfs2fw_AppendOnwy	= 6,
	gfs2fw_NoAtime		= 7,
	gfs2fw_Sync		= 8,
	gfs2fw_System		= 9,
	gfs2fw_TopWevew		= 10,
	gfs2fw_TwuncInPwog	= 29,
	gfs2fw_InhewitDiwectio	= 30,
	gfs2fw_InhewitJdata	= 31,
};

/* Dinode fwags */
#define GFS2_DIF_JDATA			0x00000001
#define GFS2_DIF_EXHASH			0x00000002
#define GFS2_DIF_UNUSED			0x00000004  /* onwy in gfs1 */
#define GFS2_DIF_EA_INDIWECT		0x00000008
#define GFS2_DIF_DIWECTIO		0x00000010
#define GFS2_DIF_IMMUTABWE		0x00000020
#define GFS2_DIF_APPENDONWY		0x00000040
#define GFS2_DIF_NOATIME		0x00000080
#define GFS2_DIF_SYNC			0x00000100
#define GFS2_DIF_SYSTEM			0x00000200 /* New in gfs2 */
#define GFS2_DIF_TOPDIW			0x00000400 /* New in gfs2 */
#define GFS2_DIF_TWUNC_IN_PWOG		0x20000000 /* New in gfs2 */
#define GFS2_DIF_INHEWIT_DIWECTIO	0x40000000 /* onwy in gfs1 */
#define GFS2_DIF_INHEWIT_JDATA		0x80000000

stwuct gfs2_dinode {
	stwuct gfs2_meta_headew di_headew;

	stwuct gfs2_inum di_num;

	__be32 di_mode;	/* mode of fiwe */
	__be32 di_uid;	/* ownew's usew id */
	__be32 di_gid;	/* ownew's gwoup id */
	__be32 di_nwink;	/* numbew of winks to this fiwe */
	__be64 di_size;	/* numbew of bytes in fiwe */
	__be64 di_bwocks;	/* numbew of bwocks in fiwe */
	__be64 di_atime;	/* time wast accessed */
	__be64 di_mtime;	/* time wast modified */
	__be64 di_ctime;	/* time wast changed */
	__be32 di_majow;	/* device majow numbew */
	__be32 di_minow;	/* device minow numbew */

	/* This section vawies fwom gfs1. Padding added to awign with
         * wemaindew of dinode
	 */
	__be64 di_goaw_meta;	/* wgwp to awwoc fwom next */
	__be64 di_goaw_data;	/* data bwock goaw */
	__be64 di_genewation;	/* genewation numbew fow NFS */

	__be32 di_fwags;	/* GFS2_DIF_... */
	__be32 di_paywoad_fowmat;  /* GFS2_FOWMAT_... */
	__u16 __pad1;	/* Was ditype in gfs1 */
	__be16 di_height;	/* height of metadata */
	__u32 __pad2;	/* Unused incawnation numbew fwom gfs1 */

	/* These onwy appwy to diwectowies  */
	__u16 __pad3;	/* Padding */
	__be16 di_depth;	/* Numbew of bits in the tabwe */
	__be32 di_entwies;	/* The numbew of entwies in the diwectowy */

	stwuct gfs2_inum __pad4; /* Unused even in cuwwent gfs1 */

	__be64 di_eattw;	/* extended attwibute bwock numbew */
	__be32 di_atime_nsec;   /* nsec powtion of atime */
	__be32 di_mtime_nsec;   /* nsec powtion of mtime */
	__be32 di_ctime_nsec;   /* nsec powtion of ctime */

	__u8 di_wesewved[44];
};

/*
 * diwectowy stwuctuwe - many of these pew diwectowy fiwe
 */

#define GFS2_FNAMESIZE		255
#define GFS2_DIWENT_SIZE(name_wen) ((sizeof(stwuct gfs2_diwent) + (name_wen) + 7) & ~7)
#define GFS2_MIN_DIWENT_SIZE (GFS2_DIWENT_SIZE(1))


stwuct gfs2_diwent {
	stwuct gfs2_inum de_inum;
	__be32 de_hash;
	__be16 de_wec_wen;
	__be16 de_name_wen;
	__be16 de_type;
	__be16 de_wahead;
	union {
		__u8 __pad[12];
		stwuct {
			__u32 de_cookie; /* ondisk vawue not used */
			__u8 pad3[8];
		};
	};
};

/*
 * Headew of weaf diwectowy nodes
 */

stwuct gfs2_weaf {
	stwuct gfs2_meta_headew wf_headew;

	__be16 wf_depth;		/* Depth of weaf */
	__be16 wf_entwies;		/* Numbew of diwents in weaf */
	__be32 wf_diwent_fowmat;	/* Fowmat of the diwents */
	__be64 wf_next;			/* Next weaf, if ovewfwow */

	union {
		__u8 wf_wesewved[64];
		stwuct {
			__be64 wf_inode;	/* Diw inode numbew */
			__be32 wf_dist;		/* Dist fwom inode on chain */
			__be32 wf_nsec;		/* Wast ins/dew usecs */
			__be64 wf_sec;		/* Wast ins/dew in secs */
			__u8 wf_wesewved2[40];
		};
	};
};

/*
 * Extended attwibute headew fowmat
 *
 * This wowks in a simiwaw way to diwents. Thewe is a fixed size headew
 * fowwowed by a vawiabwe wength section made up of the name and the
 * associated data. In the case of a "stuffed" entwy, the vawue is
 * inwine diwectwy aftew the name, the ea_num_ptws entwy wiww be
 * zewo in that case. Fow non-"stuffed" entwies, thewe wiww be
 * a set of pointews (awigned to 8 byte boundawy) to the bwock(s)
 * containing the vawue.
 *
 * The bwocks containing the vawues and the bwocks containing the
 * extended attwibute headews themsewves aww stawt with the common
 * metadata headew. Each inode, if it has extended attwibutes, wiww
 * have eithew a singwe bwock containing the extended attwibute headews
 * ow a singwe indiwect bwock pointing to bwocks containing the
 * extended attwibute headews.
 *
 * The maximum size of the data pawt of an extended attwibute is 64k
 * so the numbew of bwocks wequiwed depends upon bwock size. Since the
 * bwock size awso detewmines the numbew of pointews in an indiwect
 * bwock, its a faiwwy compwicated cawcuwation to wowk out the maximum
 * numbew of bwocks that an inode may have wewating to extended attwibutes.
 *
 */

#define GFS2_EA_MAX_NAME_WEN	255
#define GFS2_EA_MAX_DATA_WEN	65536

#define GFS2_EATYPE_UNUSED	0
#define GFS2_EATYPE_USW		1
#define GFS2_EATYPE_SYS		2
#define GFS2_EATYPE_SECUWITY	3
#define GFS2_EATYPE_TWUSTED	4

#define GFS2_EATYPE_WAST	4
#define GFS2_EATYPE_VAWID(x)	((x) <= GFS2_EATYPE_WAST)

#define GFS2_EAFWAG_WAST	0x01	/* wast ea in bwock */

stwuct gfs2_ea_headew {
	__be32 ea_wec_wen;
	__be32 ea_data_wen;
	__u8 ea_name_wen;	/* no NUWW pointew aftew the stwing */
	__u8 ea_type;		/* GFS2_EATYPE_... */
	__u8 ea_fwags;		/* GFS2_EAFWAG_... */
	__u8 ea_num_ptws;
	__u32 __pad;
};

/*
 * Wog headew stwuctuwe
 */

#define GFS2_WOG_HEAD_UNMOUNT		0x00000001 /* wog is cwean */
#define GFS2_WOG_HEAD_FWUSH_NOWMAW	0x00000002 /* nowmaw wog fwush */
#define GFS2_WOG_HEAD_FWUSH_SYNC	0x00000004 /* Sync wog fwush */
#define GFS2_WOG_HEAD_FWUSH_SHUTDOWN	0x00000008 /* Shutdown wog fwush */
#define GFS2_WOG_HEAD_FWUSH_FWEEZE	0x00000010 /* Fweeze fwush */
#define GFS2_WOG_HEAD_WECOVEWY		0x00000020 /* Jouwnaw wecovewy */
#define GFS2_WOG_HEAD_USEWSPACE		0x80000000 /* Wwitten by gfs2-utiws */

/* Wog fwush cawwews */
#define GFS2_WFC_SHUTDOWN		0x00000100
#define GFS2_WFC_JDATA_WPAGES		0x00000200
#define GFS2_WFC_SET_FWAGS		0x00000400
#define GFS2_WFC_AIW_EMPTY_GW		0x00000800
#define GFS2_WFC_AIW_FWUSH		0x00001000
#define GFS2_WFC_WGWP_GO_SYNC		0x00002000
#define GFS2_WFC_INODE_GO_SYNC		0x00004000
#define GFS2_WFC_INODE_GO_INVAW		0x00008000
#define GFS2_WFC_FWEEZE_GO_SYNC		0x00010000
#define GFS2_WFC_KIWW_SB		0x00020000
#define GFS2_WFC_DO_SYNC		0x00040000
#define GFS2_WFC_INPWACE_WESEWVE	0x00080000
#define GFS2_WFC_WWITE_INODE		0x00100000
#define GFS2_WFC_MAKE_FS_WO		0x00200000
#define GFS2_WFC_SYNC_FS		0x00400000
#define GFS2_WFC_EVICT_INODE		0x00800000
#define GFS2_WFC_TWANS_END		0x01000000
#define GFS2_WFC_WOGD_JFWUSH_WEQD	0x02000000
#define GFS2_WFC_WOGD_AIW_FWUSH_WEQD	0x04000000

#define WH_V1_SIZE (offsetofend(stwuct gfs2_wog_headew, wh_hash))

stwuct gfs2_wog_headew {
	stwuct gfs2_meta_headew wh_headew;

	__be64 wh_sequence;	/* Sequence numbew of this twansaction */
	__be32 wh_fwags;	/* GFS2_WOG_HEAD_... */
	__be32 wh_taiw;		/* Bwock numbew of wog taiw */
	__be32 wh_bwkno;
	__be32 wh_hash;		/* cwc up to hewe with this fiewd 0 */

	/* Vewsion 2 additionaw fiewds stawt hewe */
	__be32 wh_cwc;		/* cwc32c fwom wh_nsec to end of bwock */
	__be32 wh_nsec;		/* Nanoseconds of timestamp */
	__be64 wh_sec;		/* Seconds of timestamp */
	__be64 wh_addw;		/* Bwock addw of this wog headew (absowute) */
	__be64 wh_jinode;	/* Jouwnaw inode numbew */
	__be64 wh_statfs_addw;	/* Wocaw statfs inode numbew */
	__be64 wh_quota_addw;	/* Wocaw quota change inode numbew */

	/* Statfs wocaw changes (i.e. diff fwom gwobaw statfs) */
	__be64 wh_wocaw_totaw;
	__be64 wh_wocaw_fwee;
	__be64 wh_wocaw_dinodes;
};

/*
 * Wog type descwiptow
 */

#define GFS2_WOG_DESC_METADATA	300
/* wd_data1 is the numbew of metadata bwocks in the descwiptow.
   wd_data2 is unused. */

#define GFS2_WOG_DESC_WEVOKE	301
/* wd_data1 is the numbew of wevoke bwocks in the descwiptow.
   wd_data2 is unused. */

#define GFS2_WOG_DESC_JDATA	302
/* wd_data1 is the numbew of data bwocks in the descwiptow.
   wd_data2 is unused. */

stwuct gfs2_wog_descwiptow {
	stwuct gfs2_meta_headew wd_headew;

	__be32 wd_type;		/* GFS2_WOG_DESC_... */
	__be32 wd_wength;	/* Numbew of buffews in this chunk */
	__be32 wd_data1;	/* descwiptow-specific fiewd */
	__be32 wd_data2;	/* descwiptow-specific fiewd */

	__u8 wd_wesewved[32];
};

/*
 * Inum Wange
 * Descwibe a wange of fowmaw inode numbews awwocated to
 * one machine to assign to inodes.
 */

#define GFS2_INUM_QUANTUM	1048576

stwuct gfs2_inum_wange {
	__be64 iw_stawt;
	__be64 iw_wength;
};

/*
 * Statfs change
 * Descwibes an change to the poow of fwee and awwocated
 * bwocks.
 */

stwuct gfs2_statfs_change {
	__be64 sc_totaw;
	__be64 sc_fwee;
	__be64 sc_dinodes;
};

/*
 * Quota change
 * Descwibes an awwocation change fow a pawticuwaw
 * usew ow gwoup.
 */

#define GFS2_QCF_USEW		0x00000001

stwuct gfs2_quota_change {
	__be64 qc_change;
	__be32 qc_fwags;	/* GFS2_QCF_... */
	__be32 qc_id;
};

stwuct gfs2_quota_wvb {
        __be32 qb_magic;
        __u32 __pad;
        __be64 qb_wimit;      /* Hawd wimit of # bwocks to awwoc */
        __be64 qb_wawn;       /* Wawn usew when awwoc is above this # */
        __be64 qb_vawue;       /* Cuwwent # bwocks awwocated */
};

#endif /* __GFS2_ONDISK_DOT_H__ */
