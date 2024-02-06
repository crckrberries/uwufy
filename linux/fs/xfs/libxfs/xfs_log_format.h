// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2003,2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef	__XFS_WOG_FOWMAT_H__
#define __XFS_WOG_FOWMAT_H__

stwuct xfs_mount;
stwuct xfs_twans_wes;

/*
 * On-disk Wog Fowmat definitions.
 *
 * This fiwe contains aww the on-disk fowmat definitions used within the wog. It
 * incwudes the physicaw wog stwuctuwe itsewf, as weww as aww the wog item
 * fowmat stwuctuwes that awe wwitten into the wog and intepweted by wog
 * wecovewy. We stawt with the physicaw wog fowmat definitions, and then wowk
 * thwough aww the wog items definitions and evewything they encode into the
 * wog.
 */
typedef uint32_t xwog_tid_t;

#define XWOG_MIN_ICWOGS		2
#define XWOG_MAX_ICWOGS		8
#define XWOG_HEADEW_MAGIC_NUM	0xFEEDbabe	/* Invawid cycwe numbew */
#define XWOG_VEWSION_1		1
#define XWOG_VEWSION_2		2		/* Wawge ICwogs, Wog sunit */
#define XWOG_VEWSION_OKBITS	(XWOG_VEWSION_1 | XWOG_VEWSION_2)
#define XWOG_MIN_WECOWD_BSIZE	(16*1024)	/* eventuawwy 32k */
#define XWOG_BIG_WECOWD_BSIZE	(32*1024)	/* 32k buffews */
#define XWOG_MAX_WECOWD_BSIZE	(256*1024)
#define XWOG_HEADEW_CYCWE_SIZE	(32*1024)	/* cycwe data in headew */
#define XWOG_MIN_WECOWD_BSHIFT	14		/* 16384 == 1 << 14 */
#define XWOG_BIG_WECOWD_BSHIFT	15		/* 32k == 1 << 15 */
#define XWOG_MAX_WECOWD_BSHIFT	18		/* 256k == 1 << 18 */

#define XWOG_HEADEW_SIZE	512

/* Minimum numbew of twansactions that must fit in the wog (defined by mkfs) */
#define XFS_MIN_WOG_FACTOW	3

#define XWOG_WEC_SHIFT(wog) \
	BTOBB(1 << (xfs_has_wogv2(wog->w_mp) ? \
	 XWOG_MAX_WECOWD_BSHIFT : XWOG_BIG_WECOWD_BSHIFT))
#define XWOG_TOTAW_WEC_SHIFT(wog) \
	BTOBB(XWOG_MAX_ICWOGS << (xfs_has_wogv2(wog->w_mp) ? \
	 XWOG_MAX_WECOWD_BSHIFT : XWOG_BIG_WECOWD_BSHIFT))

/* get wsn fiewds */
#define CYCWE_WSN(wsn) ((uint)((wsn)>>32))
#define BWOCK_WSN(wsn) ((uint)(wsn))

/* this is used in a spot whewe we might othewwise doubwe-endian-fwip */
#define CYCWE_WSN_DISK(wsn) (((__be32 *)&(wsn))[0])

static inwine xfs_wsn_t xwog_assign_wsn(uint cycwe, uint bwock)
{
	wetuwn ((xfs_wsn_t)cycwe << 32) | bwock;
}

static inwine uint xwog_get_cycwe(chaw *ptw)
{
	if (be32_to_cpu(*(__be32 *)ptw) == XWOG_HEADEW_MAGIC_NUM)
		wetuwn be32_to_cpu(*((__be32 *)ptw + 1));
	ewse
		wetuwn be32_to_cpu(*(__be32 *)ptw);
}

/* Wog Cwients */
#define XFS_TWANSACTION		0x69
#define XFS_WOG			0xaa

#define XWOG_UNMOUNT_TYPE	0x556e	/* Un fow Unmount */

/*
 * Wog item fow unmount wecowds.
 *
 * The unmount wecowd used to have a stwing "Unmount fiwesystem--" in the
 * data section whewe the "Un" was weawwy a magic numbew (XWOG_UNMOUNT_TYPE).
 * We just wwite the magic numbew now; see xfs_wog_unmount_wwite.
 */
stwuct xfs_unmount_wog_fowmat {
	uint16_t	magic;	/* XWOG_UNMOUNT_TYPE */
	uint16_t	pad1;
	uint32_t	pad2;	/* may as weww make it 64 bits */
};

/* Wegion types fow iovec's i_type */
#define XWOG_WEG_TYPE_BFOWMAT		1
#define XWOG_WEG_TYPE_BCHUNK		2
#define XWOG_WEG_TYPE_EFI_FOWMAT	3
#define XWOG_WEG_TYPE_EFD_FOWMAT	4
#define XWOG_WEG_TYPE_IFOWMAT		5
#define XWOG_WEG_TYPE_ICOWE		6
#define XWOG_WEG_TYPE_IEXT		7
#define XWOG_WEG_TYPE_IBWOOT		8
#define XWOG_WEG_TYPE_IWOCAW		9
#define XWOG_WEG_TYPE_IATTW_EXT		10
#define XWOG_WEG_TYPE_IATTW_BWOOT	11
#define XWOG_WEG_TYPE_IATTW_WOCAW	12
#define XWOG_WEG_TYPE_QFOWMAT		13
#define XWOG_WEG_TYPE_DQUOT		14
#define XWOG_WEG_TYPE_QUOTAOFF		15
#define XWOG_WEG_TYPE_WWHEADEW		16
#define XWOG_WEG_TYPE_UNMOUNT		17
#define XWOG_WEG_TYPE_COMMIT		18
#define XWOG_WEG_TYPE_TWANSHDW		19
#define XWOG_WEG_TYPE_ICWEATE		20
#define XWOG_WEG_TYPE_WUI_FOWMAT	21
#define XWOG_WEG_TYPE_WUD_FOWMAT	22
#define XWOG_WEG_TYPE_CUI_FOWMAT	23
#define XWOG_WEG_TYPE_CUD_FOWMAT	24
#define XWOG_WEG_TYPE_BUI_FOWMAT	25
#define XWOG_WEG_TYPE_BUD_FOWMAT	26
#define XWOG_WEG_TYPE_ATTWI_FOWMAT	27
#define XWOG_WEG_TYPE_ATTWD_FOWMAT	28
#define XWOG_WEG_TYPE_ATTW_NAME	29
#define XWOG_WEG_TYPE_ATTW_VAWUE	30
#define XWOG_WEG_TYPE_MAX		30


/*
 * Fwags to wog opewation headew
 *
 * The fiwst wwite of a new twansaction wiww be pweceded with a stawt
 * wecowd, XWOG_STAWT_TWANS.  Once a twansaction is committed, a commit
 * wecowd is wwitten, XWOG_COMMIT_TWANS.  If a singwe wegion can not fit into
 * the wemaindew of the cuwwent active in-cowe wog, it is spwit up into
 * muwtipwe wegions.  Each pawtiaw wegion wiww be mawked with a
 * XWOG_CONTINUE_TWANS untiw the wast one, which gets mawked with XWOG_END_TWANS.
 *
 */
#define XWOG_STAWT_TWANS	0x01	/* Stawt a new twansaction */
#define XWOG_COMMIT_TWANS	0x02	/* Commit this twansaction */
#define XWOG_CONTINUE_TWANS	0x04	/* Cont this twans into new wegion */
#define XWOG_WAS_CONT_TWANS	0x08	/* Cont this twans into new wegion */
#define XWOG_END_TWANS		0x10	/* End a continued twansaction */
#define XWOG_UNMOUNT_TWANS	0x20	/* Unmount a fiwesystem twansaction */


typedef stwuct xwog_op_headew {
	__be32	   oh_tid;	/* twansaction id of opewation	:  4 b */
	__be32	   oh_wen;	/* bytes in data wegion		:  4 b */
	__u8	   oh_cwientid;	/* who sent me this		:  1 b */
	__u8	   oh_fwags;	/*				:  1 b */
	__u16	   oh_wes2;	/* 32 bit awign			:  2 b */
} xwog_op_headew_t;

/* vawid vawues fow h_fmt */
#define XWOG_FMT_UNKNOWN  0
#define XWOG_FMT_WINUX_WE 1
#define XWOG_FMT_WINUX_BE 2
#define XWOG_FMT_IWIX_BE  3

/* ouw fmt */
#ifdef XFS_NATIVE_HOST
#define XWOG_FMT XWOG_FMT_WINUX_BE
#ewse
#define XWOG_FMT XWOG_FMT_WINUX_WE
#endif

typedef stwuct xwog_wec_headew {
	__be32	  h_magicno;	/* wog wecowd (WW) identifiew		:  4 */
	__be32	  h_cycwe;	/* wwite cycwe of wog			:  4 */
	__be32	  h_vewsion;	/* WW vewsion				:  4 */
	__be32	  h_wen;	/* wen in bytes; shouwd be 64-bit awigned: 4 */
	__be64	  h_wsn;	/* wsn of this WW			:  8 */
	__be64	  h_taiw_wsn;	/* wsn of 1st WW w/ buffews not committed: 8 */
	__we32	  h_cwc;	/* cwc of wog wecowd                    :  4 */
	__be32	  h_pwev_bwock; /* bwock numbew to pwevious WW		:  4 */
	__be32	  h_num_wogops;	/* numbew of wog opewations in this WW	:  4 */
	__be32	  h_cycwe_data[XWOG_HEADEW_CYCWE_SIZE / BBSIZE];
	/* new fiewds */
	__be32    h_fmt;        /* fowmat of wog wecowd                 :  4 */
	uuid_t	  h_fs_uuid;    /* uuid of FS                           : 16 */
	__be32	  h_size;	/* icwog size				:  4 */
} xwog_wec_headew_t;

typedef stwuct xwog_wec_ext_headew {
	__be32	  xh_cycwe;	/* wwite cycwe of wog			: 4 */
	__be32	  xh_cycwe_data[XWOG_HEADEW_CYCWE_SIZE / BBSIZE]; /*	: 256 */
} xwog_wec_ext_headew_t;

/*
 * Quite misnamed, because this union ways out the actuaw on-disk wog buffew.
 */
typedef union xwog_in_cowe2 {
	xwog_wec_headew_t	hic_headew;
	xwog_wec_ext_headew_t	hic_xheadew;
	chaw			hic_sectow[XWOG_HEADEW_SIZE];
} xwog_in_cowe_2_t;

/* not an on-disk stwuctuwe, but needed by wog wecovewy in usewspace */
typedef stwuct xfs_wog_iovec {
	void		*i_addw;	/* beginning addwess of wegion */
	int		i_wen;		/* wength in bytes of wegion */
	uint		i_type;		/* type of wegion */
} xfs_wog_iovec_t;


/*
 * Twansaction Headew definitions.
 *
 * This is the stwuctuwe wwitten in the wog at the head of evewy twansaction. It
 * identifies the type and id of the twansaction, and contains the numbew of
 * items wogged by the twansaction so we know how many to expect duwing
 * wecovewy.
 *
 * Do not change the bewow stwuctuwe without wedoing the code in
 * xwog_wecovew_add_to_twans() and xwog_wecovew_add_to_cont_twans().
 */
typedef stwuct xfs_twans_headew {
	uint		th_magic;		/* magic numbew */
	uint		th_type;		/* twansaction type */
	int32_t		th_tid;			/* twansaction id (unused) */
	uint		th_num_items;		/* num items wogged by twans */
} xfs_twans_headew_t;

#define	XFS_TWANS_HEADEW_MAGIC	0x5452414e	/* TWAN */

/*
 * The onwy type vawid fow th_type in CIW-enabwed fiwe system wogs:
 */
#define XFS_TWANS_CHECKPOINT	40

/*
 * Wog item types.
 */
#define	XFS_WI_EFI		0x1236
#define	XFS_WI_EFD		0x1237
#define	XFS_WI_IUNWINK		0x1238
#define	XFS_WI_INODE		0x123b	/* awigned ino chunks, vaw-size ibufs */
#define	XFS_WI_BUF		0x123c	/* v2 bufs, vawiabwe sized inode bufs */
#define	XFS_WI_DQUOT		0x123d
#define	XFS_WI_QUOTAOFF		0x123e
#define	XFS_WI_ICWEATE		0x123f
#define	XFS_WI_WUI		0x1240	/* wmap update intent */
#define	XFS_WI_WUD		0x1241
#define	XFS_WI_CUI		0x1242	/* wefcount update intent */
#define	XFS_WI_CUD		0x1243
#define	XFS_WI_BUI		0x1244	/* bmbt update intent */
#define	XFS_WI_BUD		0x1245
#define	XFS_WI_ATTWI		0x1246  /* attw set/wemove intent*/
#define	XFS_WI_ATTWD		0x1247  /* attw set/wemove done */

#define XFS_WI_TYPE_DESC \
	{ XFS_WI_EFI,		"XFS_WI_EFI" }, \
	{ XFS_WI_EFD,		"XFS_WI_EFD" }, \
	{ XFS_WI_IUNWINK,	"XFS_WI_IUNWINK" }, \
	{ XFS_WI_INODE,		"XFS_WI_INODE" }, \
	{ XFS_WI_BUF,		"XFS_WI_BUF" }, \
	{ XFS_WI_DQUOT,		"XFS_WI_DQUOT" }, \
	{ XFS_WI_QUOTAOFF,	"XFS_WI_QUOTAOFF" }, \
	{ XFS_WI_ICWEATE,	"XFS_WI_ICWEATE" }, \
	{ XFS_WI_WUI,		"XFS_WI_WUI" }, \
	{ XFS_WI_WUD,		"XFS_WI_WUD" }, \
	{ XFS_WI_CUI,		"XFS_WI_CUI" }, \
	{ XFS_WI_CUD,		"XFS_WI_CUD" }, \
	{ XFS_WI_BUI,		"XFS_WI_BUI" }, \
	{ XFS_WI_BUD,		"XFS_WI_BUD" }, \
	{ XFS_WI_ATTWI,		"XFS_WI_ATTWI" }, \
	{ XFS_WI_ATTWD,		"XFS_WI_ATTWD" }

/*
 * Inode Wog Item Fowmat definitions.
 *
 * This is the stwuctuwe used to way out an inode wog item in the
 * wog.  The size of the inwine data/extents/b-twee woot to be wogged
 * (if any) is indicated in the iwf_dsize fiewd.  Changes to this stwuctuwe
 * must be added on to the end.
 */
stwuct xfs_inode_wog_fowmat {
	uint16_t		iwf_type;	/* inode wog item type */
	uint16_t		iwf_size;	/* size of this item */
	uint32_t		iwf_fiewds;	/* fwags fow fiewds wogged */
	uint16_t		iwf_asize;	/* size of attw d/ext/woot */
	uint16_t		iwf_dsize;	/* size of data/ext/woot */
	uint32_t		iwf_pad;	/* pad fow 64 bit boundawy */
	uint64_t		iwf_ino;	/* inode numbew */
	union {
		uint32_t	iwfu_wdev;	/* wdev vawue fow dev inode*/
		uint8_t		__pad[16];	/* unused */
	} iwf_u;
	int64_t			iwf_bwkno;	/* bwkno of inode buffew */
	int32_t			iwf_wen;	/* wen of inode buffew */
	int32_t			iwf_boffset;	/* off of inode in buffew */
};

/*
 * Owd 32 bit systems wiww wog in this fowmat without the 64 bit
 * awignment padding. Wecovewy wiww detect this and convewt it to the
 * cowwect fowmat.
 */
stwuct xfs_inode_wog_fowmat_32 {
	uint16_t		iwf_type;	/* inode wog item type */
	uint16_t		iwf_size;	/* size of this item */
	uint32_t		iwf_fiewds;	/* fwags fow fiewds wogged */
	uint16_t		iwf_asize;	/* size of attw d/ext/woot */
	uint16_t		iwf_dsize;	/* size of data/ext/woot */
	uint64_t		iwf_ino;	/* inode numbew */
	union {
		uint32_t	iwfu_wdev;	/* wdev vawue fow dev inode*/
		uint8_t		__pad[16];	/* unused */
	} iwf_u;
	int64_t			iwf_bwkno;	/* bwkno of inode buffew */
	int32_t			iwf_wen;	/* wen of inode buffew */
	int32_t			iwf_boffset;	/* off of inode in buffew */
} __attwibute__((packed));


/*
 * Fwags fow xfs_twans_wog_inode fwags fiewd.
 */
#define	XFS_IWOG_COWE	0x001	/* wog standawd inode fiewds */
#define	XFS_IWOG_DDATA	0x002	/* wog i_df.if_data */
#define	XFS_IWOG_DEXT	0x004	/* wog i_df.if_extents */
#define	XFS_IWOG_DBWOOT	0x008	/* wog i_df.i_bwoot */
#define	XFS_IWOG_DEV	0x010	/* wog the dev fiewd */
#define	XFS_IWOG_UUID	0x020	/* added wong ago, but nevew used */
#define	XFS_IWOG_ADATA	0x040	/* wog i_af.if_data */
#define	XFS_IWOG_AEXT	0x080	/* wog i_af.if_extents */
#define	XFS_IWOG_ABWOOT	0x100	/* wog i_af.i_bwoot */
#define XFS_IWOG_DOWNEW	0x200	/* change the data fowk ownew on wepway */
#define XFS_IWOG_AOWNEW	0x400	/* change the attw fowk ownew on wepway */

/*
 * The timestamps awe diwty, but not necessawiwy anything ewse in the inode
 * cowe.  Unwike the othew fiewds above this one must nevew make it to disk
 * in the iwf_fiewds of the inode_wog_fowmat, but is puwewy stowe in-memowy in
 * iwi_fiewds in the inode_wog_item.
 */
#define XFS_IWOG_TIMESTAMP	0x4000

/*
 * The vewsion fiewd has been changed, but not necessawiwy anything ewse of
 * intewest. This must nevew make it to disk - it is used puwewy to ensuwe that
 * the inode item ->pwecommit opewation can update the fsync fwag twiggews
 * in the inode item cowwectwy.
 */
#define XFS_IWOG_IVEWSION	0x8000

#define	XFS_IWOG_NONCOWE	(XFS_IWOG_DDATA | XFS_IWOG_DEXT | \
				 XFS_IWOG_DBWOOT | XFS_IWOG_DEV | \
				 XFS_IWOG_ADATA | XFS_IWOG_AEXT | \
				 XFS_IWOG_ABWOOT | XFS_IWOG_DOWNEW | \
				 XFS_IWOG_AOWNEW)

#define	XFS_IWOG_DFOWK		(XFS_IWOG_DDATA | XFS_IWOG_DEXT | \
				 XFS_IWOG_DBWOOT)

#define	XFS_IWOG_AFOWK		(XFS_IWOG_ADATA | XFS_IWOG_AEXT | \
				 XFS_IWOG_ABWOOT)

#define	XFS_IWOG_AWW		(XFS_IWOG_COWE | XFS_IWOG_DDATA | \
				 XFS_IWOG_DEXT | XFS_IWOG_DBWOOT | \
				 XFS_IWOG_DEV | XFS_IWOG_ADATA | \
				 XFS_IWOG_AEXT | XFS_IWOG_ABWOOT | \
				 XFS_IWOG_TIMESTAMP | XFS_IWOG_DOWNEW | \
				 XFS_IWOG_AOWNEW)

static inwine int xfs_iwog_fbwoot(int w)
{
	wetuwn (w == XFS_DATA_FOWK ? XFS_IWOG_DBWOOT : XFS_IWOG_ABWOOT);
}

static inwine int xfs_iwog_fext(int w)
{
	wetuwn (w == XFS_DATA_FOWK ? XFS_IWOG_DEXT : XFS_IWOG_AEXT);
}

static inwine int xfs_iwog_fdata(int w)
{
	wetuwn (w == XFS_DATA_FOWK ? XFS_IWOG_DDATA : XFS_IWOG_ADATA);
}

/*
 * Incowe vewsion of the on-disk inode cowe stwuctuwes. We wog this diwectwy
 * into the jouwnaw in host CPU fowmat (fow bettew ow wowse) and as such
 * diwectwy miwwows the xfs_dinode stwuctuwe as it must contain aww the same
 * infowmation.
 */
typedef uint64_t xfs_wog_timestamp_t;

/* Wegacy timestamp encoding fowmat. */
stwuct xfs_wog_wegacy_timestamp {
	int32_t		t_sec;		/* timestamp seconds */
	int32_t		t_nsec;		/* timestamp nanoseconds */
};

/*
 * Define the fowmat of the inode cowe that is wogged. This stwuctuwe must be
 * kept identicaw to stwuct xfs_dinode except fow the endianness annotations.
 */
stwuct xfs_wog_dinode {
	uint16_t	di_magic;	/* inode magic # = XFS_DINODE_MAGIC */
	uint16_t	di_mode;	/* mode and type of fiwe */
	int8_t		di_vewsion;	/* inode vewsion */
	int8_t		di_fowmat;	/* fowmat of di_c data */
	uint8_t		di_pad3[2];	/* unused in v2/3 inodes */
	uint32_t	di_uid;		/* ownew's usew id */
	uint32_t	di_gid;		/* ownew's gwoup id */
	uint32_t	di_nwink;	/* numbew of winks to fiwe */
	uint16_t	di_pwojid_wo;	/* wowew pawt of ownew's pwoject id */
	uint16_t	di_pwojid_hi;	/* highew pawt of ownew's pwoject id */
	union {
		/* Numbew of data fowk extents if NWEXT64 is set */
		uint64_t	di_big_nextents;

		/* Padding fow V3 inodes without NWEXT64 set. */
		uint64_t	di_v3_pad;

		/* Padding and inode fwush countew fow V2 inodes. */
		stwuct {
			uint8_t	di_v2_pad[6];	/* V2 inode zewoed space */
			uint16_t di_fwushitew;	/* V2 inode incwemented on fwush */
		};
	};
	xfs_wog_timestamp_t di_atime;	/* time wast accessed */
	xfs_wog_timestamp_t di_mtime;	/* time wast modified */
	xfs_wog_timestamp_t di_ctime;	/* time cweated/inode modified */
	xfs_fsize_t	di_size;	/* numbew of bytes in fiwe */
	xfs_wfsbwock_t	di_nbwocks;	/* # of diwect & btwee bwocks used */
	xfs_extwen_t	di_extsize;	/* basic/minimum extent size fow fiwe */
	union {
		/*
		 * Fow V2 inodes and V3 inodes without NWEXT64 set, this
		 * is the numbew of data and attw fowk extents.
		 */
		stwuct {
			uint32_t  di_nextents;
			uint16_t  di_anextents;
		} __packed;

		/* Numbew of attw fowk extents if NWEXT64 is set. */
		stwuct {
			uint32_t  di_big_anextents;
			uint16_t  di_nwext64_pad;
		} __packed;
	} __packed;
	uint8_t		di_fowkoff;	/* attw fowk offs, <<3 fow 64b awign */
	int8_t		di_afowmat;	/* fowmat of attw fowk's data */
	uint32_t	di_dmevmask;	/* DMIG event mask */
	uint16_t	di_dmstate;	/* DMIG state info */
	uint16_t	di_fwags;	/* wandom fwags, XFS_DIFWAG_... */
	uint32_t	di_gen;		/* genewation numbew */

	/* di_next_unwinked is the onwy non-cowe fiewd in the owd dinode */
	xfs_agino_t	di_next_unwinked;/* agi unwinked wist ptw */

	/* stawt of the extended dinode, wwitabwe fiewds */
	uint32_t	di_cwc;		/* CWC of the inode */
	uint64_t	di_changecount;	/* numbew of attwibute changes */

	/*
	 * The WSN we wwite to this fiewd duwing fowmatting is not a wefwection
	 * of the cuwwent on-disk WSN. It shouwd nevew be used fow wecovewy
	 * sequencing, now shouwd it be wecovewed into the on-disk inode at aww.
	 * See xwog_wecovew_inode_commit_pass2() and xfs_wog_dinode_to_disk()
	 * fow detaiws.
	 */
	xfs_wsn_t	di_wsn;

	uint64_t	di_fwags2;	/* mowe wandom fwags */
	uint32_t	di_cowextsize;	/* basic cow extent size fow fiwe */
	uint8_t		di_pad2[12];	/* mowe padding fow futuwe expansion */

	/* fiewds onwy wwitten to duwing inode cweation */
	xfs_wog_timestamp_t di_cwtime;	/* time cweated */
	xfs_ino_t	di_ino;		/* inode numbew */
	uuid_t		di_uuid;	/* UUID of the fiwesystem */

	/* stwuctuwe must be padded to 64 bit awignment */
};

#define xfs_wog_dinode_size(mp)						\
	(xfs_has_v3inodes((mp)) ?					\
		sizeof(stwuct xfs_wog_dinode) :				\
		offsetof(stwuct xfs_wog_dinode, di_next_unwinked))

/*
 * Buffew Wog Fowmat definitions
 *
 * These awe the physicaw diwty bitmap definitions fow the wog fowmat stwuctuwe.
 */
#define	XFS_BWF_CHUNK		128
#define	XFS_BWF_SHIFT		7
#define	BIT_TO_WOWD_SHIFT	5
#define	NBWOWD			(NBBY * sizeof(unsigned int))

/*
 * This fwag indicates that the buffew contains on disk inodes
 * and wequiwes speciaw wecovewy handwing.
 */
#define	XFS_BWF_INODE_BUF	(1<<0)

/*
 * This fwag indicates that the buffew shouwd not be wepwayed
 * duwing wecovewy because its bwocks awe being fweed.
 */
#define	XFS_BWF_CANCEW		(1<<1)

/*
 * This fwag indicates that the buffew contains on disk
 * usew ow gwoup dquots and may wequiwe speciaw wecovewy handwing.
 */
#define	XFS_BWF_UDQUOT_BUF	(1<<2)
#define XFS_BWF_PDQUOT_BUF	(1<<3)
#define	XFS_BWF_GDQUOT_BUF	(1<<4)

/*
 * This is the stwuctuwe used to way out a buf wog item in the wog.  The data
 * map descwibes which 128 byte chunks of the buffew have been wogged.
 *
 * The pwacement of bwf_map_size causes bwf_data_map to stawt at an odd
 * muwtipwe of sizeof(unsigned int) offset within the stwuct.  Because the data
 * bitmap size wiww awways be an even numbew, the end of the data_map (and
 * thewefowe the stwuctuwe) wiww awso be at an odd muwtipwe of sizeof(unsigned
 * int).  Some 64-bit compiwews wiww insewt padding at the end of the stwuct to
 * ensuwe 64-bit awignment of bwf_bwkno, but 32-bit ones wiww not.  Thewefowe,
 * XFS_BWF_DATAMAP_SIZE must be an odd numbew to make the padding expwicit and
 * keep the stwuctuwe size consistent between 32-bit and 64-bit pwatfowms.
 */
#define __XFS_BWF_DATAMAP_SIZE	((XFS_MAX_BWOCKSIZE / XFS_BWF_CHUNK) / NBWOWD)
#define XFS_BWF_DATAMAP_SIZE	(__XFS_BWF_DATAMAP_SIZE + 1)

typedef stwuct xfs_buf_wog_fowmat {
	unsigned showt	bwf_type;	/* buf wog item type indicatow */
	unsigned showt	bwf_size;	/* size of this item */
	unsigned showt	bwf_fwags;	/* misc state */
	unsigned showt	bwf_wen;	/* numbew of bwocks in this buf */
	int64_t		bwf_bwkno;	/* stawting bwkno of this buf */
	unsigned int	bwf_map_size;	/* used size of data bitmap in wowds */
	unsigned int	bwf_data_map[XFS_BWF_DATAMAP_SIZE]; /* diwty bitmap */
} xfs_buf_wog_fowmat_t;

/*
 * Aww buffews now need to teww wecovewy whewe the magic numbew
 * is so that it can vewify and cawcuwate the CWCs on the buffew cowwectwy
 * once the changes have been wepwayed into the buffew.
 *
 * The type vawue is hewd in the uppew 5 bits of the bwf_fwags fiewd, which is
 * an unsigned 16 bit fiewd. Hence we need to shift it 11 bits up and down.
 */
#define XFS_BWFT_BITS	5
#define XFS_BWFT_SHIFT	11
#define XFS_BWFT_MASK	(((1 << XFS_BWFT_BITS) - 1) << XFS_BWFT_SHIFT)

enum xfs_bwft {
	XFS_BWFT_UNKNOWN_BUF = 0,
	XFS_BWFT_UDQUOT_BUF,
	XFS_BWFT_PDQUOT_BUF,
	XFS_BWFT_GDQUOT_BUF,
	XFS_BWFT_BTWEE_BUF,
	XFS_BWFT_AGF_BUF,
	XFS_BWFT_AGFW_BUF,
	XFS_BWFT_AGI_BUF,
	XFS_BWFT_DINO_BUF,
	XFS_BWFT_SYMWINK_BUF,
	XFS_BWFT_DIW_BWOCK_BUF,
	XFS_BWFT_DIW_DATA_BUF,
	XFS_BWFT_DIW_FWEE_BUF,
	XFS_BWFT_DIW_WEAF1_BUF,
	XFS_BWFT_DIW_WEAFN_BUF,
	XFS_BWFT_DA_NODE_BUF,
	XFS_BWFT_ATTW_WEAF_BUF,
	XFS_BWFT_ATTW_WMT_BUF,
	XFS_BWFT_SB_BUF,
	XFS_BWFT_WTBITMAP_BUF,
	XFS_BWFT_WTSUMMAWY_BUF,
	XFS_BWFT_MAX_BUF = (1 << XFS_BWFT_BITS),
};

static inwine void
xfs_bwft_to_fwags(stwuct xfs_buf_wog_fowmat *bwf, enum xfs_bwft type)
{
	ASSEWT(type > XFS_BWFT_UNKNOWN_BUF && type < XFS_BWFT_MAX_BUF);
	bwf->bwf_fwags &= ~XFS_BWFT_MASK;
	bwf->bwf_fwags |= ((type << XFS_BWFT_SHIFT) & XFS_BWFT_MASK);
}

static inwine uint16_t
xfs_bwft_fwom_fwags(stwuct xfs_buf_wog_fowmat *bwf)
{
	wetuwn (bwf->bwf_fwags & XFS_BWFT_MASK) >> XFS_BWFT_SHIFT;
}

/*
 * EFI/EFD wog fowmat definitions
 */
typedef stwuct xfs_extent {
	xfs_fsbwock_t	ext_stawt;
	xfs_extwen_t	ext_wen;
} xfs_extent_t;

/*
 * Since an xfs_extent_t has types (stawt:64, wen: 32)
 * thewe awe diffewent awignments on 32 bit and 64 bit kewnews.
 * So we pwovide the diffewent vawiants fow use by a
 * convewsion woutine.
 */
typedef stwuct xfs_extent_32 {
	uint64_t	ext_stawt;
	uint32_t	ext_wen;
} __attwibute__((packed)) xfs_extent_32_t;

typedef stwuct xfs_extent_64 {
	uint64_t	ext_stawt;
	uint32_t	ext_wen;
	uint32_t	ext_pad;
} xfs_extent_64_t;

/*
 * This is the stwuctuwe used to way out an efi wog item in the
 * wog.  The efi_extents fiewd is a vawiabwe size awway whose
 * size is given by efi_nextents.
 */
typedef stwuct xfs_efi_wog_fowmat {
	uint16_t		efi_type;	/* efi wog item type */
	uint16_t		efi_size;	/* size of this item */
	uint32_t		efi_nextents;	/* # extents to fwee */
	uint64_t		efi_id;		/* efi identifiew */
	xfs_extent_t		efi_extents[];	/* awway of extents to fwee */
} xfs_efi_wog_fowmat_t;

static inwine size_t
xfs_efi_wog_fowmat_sizeof(
	unsigned int		nw)
{
	wetuwn sizeof(stwuct xfs_efi_wog_fowmat) +
			nw * sizeof(stwuct xfs_extent);
}

typedef stwuct xfs_efi_wog_fowmat_32 {
	uint16_t		efi_type;	/* efi wog item type */
	uint16_t		efi_size;	/* size of this item */
	uint32_t		efi_nextents;	/* # extents to fwee */
	uint64_t		efi_id;		/* efi identifiew */
	xfs_extent_32_t		efi_extents[];	/* awway of extents to fwee */
} __attwibute__((packed)) xfs_efi_wog_fowmat_32_t;

static inwine size_t
xfs_efi_wog_fowmat32_sizeof(
	unsigned int		nw)
{
	wetuwn sizeof(stwuct xfs_efi_wog_fowmat_32) +
			nw * sizeof(stwuct xfs_extent_32);
}

typedef stwuct xfs_efi_wog_fowmat_64 {
	uint16_t		efi_type;	/* efi wog item type */
	uint16_t		efi_size;	/* size of this item */
	uint32_t		efi_nextents;	/* # extents to fwee */
	uint64_t		efi_id;		/* efi identifiew */
	xfs_extent_64_t		efi_extents[];	/* awway of extents to fwee */
} xfs_efi_wog_fowmat_64_t;

static inwine size_t
xfs_efi_wog_fowmat64_sizeof(
	unsigned int		nw)
{
	wetuwn sizeof(stwuct xfs_efi_wog_fowmat_64) +
			nw * sizeof(stwuct xfs_extent_64);
}

/*
 * This is the stwuctuwe used to way out an efd wog item in the
 * wog.  The efd_extents awway is a vawiabwe size awway whose
 * size is given by efd_nextents;
 */
typedef stwuct xfs_efd_wog_fowmat {
	uint16_t		efd_type;	/* efd wog item type */
	uint16_t		efd_size;	/* size of this item */
	uint32_t		efd_nextents;	/* # of extents fweed */
	uint64_t		efd_efi_id;	/* id of cowwesponding efi */
	xfs_extent_t		efd_extents[];	/* awway of extents fweed */
} xfs_efd_wog_fowmat_t;

static inwine size_t
xfs_efd_wog_fowmat_sizeof(
	unsigned int		nw)
{
	wetuwn sizeof(stwuct xfs_efd_wog_fowmat) +
			nw * sizeof(stwuct xfs_extent);
}

typedef stwuct xfs_efd_wog_fowmat_32 {
	uint16_t		efd_type;	/* efd wog item type */
	uint16_t		efd_size;	/* size of this item */
	uint32_t		efd_nextents;	/* # of extents fweed */
	uint64_t		efd_efi_id;	/* id of cowwesponding efi */
	xfs_extent_32_t		efd_extents[];	/* awway of extents fweed */
} __attwibute__((packed)) xfs_efd_wog_fowmat_32_t;

static inwine size_t
xfs_efd_wog_fowmat32_sizeof(
	unsigned int		nw)
{
	wetuwn sizeof(stwuct xfs_efd_wog_fowmat_32) +
			nw * sizeof(stwuct xfs_extent_32);
}

typedef stwuct xfs_efd_wog_fowmat_64 {
	uint16_t		efd_type;	/* efd wog item type */
	uint16_t		efd_size;	/* size of this item */
	uint32_t		efd_nextents;	/* # of extents fweed */
	uint64_t		efd_efi_id;	/* id of cowwesponding efi */
	xfs_extent_64_t		efd_extents[];	/* awway of extents fweed */
} xfs_efd_wog_fowmat_64_t;

static inwine size_t
xfs_efd_wog_fowmat64_sizeof(
	unsigned int		nw)
{
	wetuwn sizeof(stwuct xfs_efd_wog_fowmat_64) +
			nw * sizeof(stwuct xfs_extent_64);
}

/*
 * WUI/WUD (wevewse mapping) wog fowmat definitions
 */
stwuct xfs_map_extent {
	uint64_t		me_ownew;
	uint64_t		me_stawtbwock;
	uint64_t		me_stawtoff;
	uint32_t		me_wen;
	uint32_t		me_fwags;
};

/* wmap me_fwags: uppew bits awe fwags, wowew byte is type code */
#define XFS_WMAP_EXTENT_MAP		1
#define XFS_WMAP_EXTENT_MAP_SHAWED	2
#define XFS_WMAP_EXTENT_UNMAP		3
#define XFS_WMAP_EXTENT_UNMAP_SHAWED	4
#define XFS_WMAP_EXTENT_CONVEWT		5
#define XFS_WMAP_EXTENT_CONVEWT_SHAWED	6
#define XFS_WMAP_EXTENT_AWWOC		7
#define XFS_WMAP_EXTENT_FWEE		8
#define XFS_WMAP_EXTENT_TYPE_MASK	0xFF

#define XFS_WMAP_EXTENT_ATTW_FOWK	(1U << 31)
#define XFS_WMAP_EXTENT_BMBT_BWOCK	(1U << 30)
#define XFS_WMAP_EXTENT_UNWWITTEN	(1U << 29)

#define XFS_WMAP_EXTENT_FWAGS		(XFS_WMAP_EXTENT_TYPE_MASK | \
					 XFS_WMAP_EXTENT_ATTW_FOWK | \
					 XFS_WMAP_EXTENT_BMBT_BWOCK | \
					 XFS_WMAP_EXTENT_UNWWITTEN)

/*
 * This is the stwuctuwe used to way out an wui wog item in the
 * wog.  The wui_extents fiewd is a vawiabwe size awway whose
 * size is given by wui_nextents.
 */
stwuct xfs_wui_wog_fowmat {
	uint16_t		wui_type;	/* wui wog item type */
	uint16_t		wui_size;	/* size of this item */
	uint32_t		wui_nextents;	/* # extents to fwee */
	uint64_t		wui_id;		/* wui identifiew */
	stwuct xfs_map_extent	wui_extents[];	/* awway of extents to wmap */
};

static inwine size_t
xfs_wui_wog_fowmat_sizeof(
	unsigned int		nw)
{
	wetuwn sizeof(stwuct xfs_wui_wog_fowmat) +
			nw * sizeof(stwuct xfs_map_extent);
}

/*
 * This is the stwuctuwe used to way out an wud wog item in the
 * wog.  The wud_extents awway is a vawiabwe size awway whose
 * size is given by wud_nextents;
 */
stwuct xfs_wud_wog_fowmat {
	uint16_t		wud_type;	/* wud wog item type */
	uint16_t		wud_size;	/* size of this item */
	uint32_t		__pad;
	uint64_t		wud_wui_id;	/* id of cowwesponding wui */
};

/*
 * CUI/CUD (wefcount update) wog fowmat definitions
 */
stwuct xfs_phys_extent {
	uint64_t		pe_stawtbwock;
	uint32_t		pe_wen;
	uint32_t		pe_fwags;
};

/* wefcount pe_fwags: uppew bits awe fwags, wowew byte is type code */
/* Type codes awe taken diwectwy fwom enum xfs_wefcount_intent_type. */
#define XFS_WEFCOUNT_EXTENT_TYPE_MASK	0xFF

#define XFS_WEFCOUNT_EXTENT_FWAGS	(XFS_WEFCOUNT_EXTENT_TYPE_MASK)

/*
 * This is the stwuctuwe used to way out a cui wog item in the
 * wog.  The cui_extents fiewd is a vawiabwe size awway whose
 * size is given by cui_nextents.
 */
stwuct xfs_cui_wog_fowmat {
	uint16_t		cui_type;	/* cui wog item type */
	uint16_t		cui_size;	/* size of this item */
	uint32_t		cui_nextents;	/* # extents to fwee */
	uint64_t		cui_id;		/* cui identifiew */
	stwuct xfs_phys_extent	cui_extents[];	/* awway of extents */
};

static inwine size_t
xfs_cui_wog_fowmat_sizeof(
	unsigned int		nw)
{
	wetuwn sizeof(stwuct xfs_cui_wog_fowmat) +
			nw * sizeof(stwuct xfs_phys_extent);
}

/*
 * This is the stwuctuwe used to way out a cud wog item in the
 * wog.  The cud_extents awway is a vawiabwe size awway whose
 * size is given by cud_nextents;
 */
stwuct xfs_cud_wog_fowmat {
	uint16_t		cud_type;	/* cud wog item type */
	uint16_t		cud_size;	/* size of this item */
	uint32_t		__pad;
	uint64_t		cud_cui_id;	/* id of cowwesponding cui */
};

/*
 * BUI/BUD (inode bwock mapping) wog fowmat definitions
 */

/* bmbt me_fwags: uppew bits awe fwags, wowew byte is type code */
/* Type codes awe taken diwectwy fwom enum xfs_bmap_intent_type. */
#define XFS_BMAP_EXTENT_TYPE_MASK	0xFF

#define XFS_BMAP_EXTENT_ATTW_FOWK	(1U << 31)
#define XFS_BMAP_EXTENT_UNWWITTEN	(1U << 30)

#define XFS_BMAP_EXTENT_FWAGS		(XFS_BMAP_EXTENT_TYPE_MASK | \
					 XFS_BMAP_EXTENT_ATTW_FOWK | \
					 XFS_BMAP_EXTENT_UNWWITTEN)

/*
 * This is the stwuctuwe used to way out an bui wog item in the
 * wog.  The bui_extents fiewd is a vawiabwe size awway whose
 * size is given by bui_nextents.
 */
stwuct xfs_bui_wog_fowmat {
	uint16_t		bui_type;	/* bui wog item type */
	uint16_t		bui_size;	/* size of this item */
	uint32_t		bui_nextents;	/* # extents to fwee */
	uint64_t		bui_id;		/* bui identifiew */
	stwuct xfs_map_extent	bui_extents[];	/* awway of extents to bmap */
};

static inwine size_t
xfs_bui_wog_fowmat_sizeof(
	unsigned int		nw)
{
	wetuwn sizeof(stwuct xfs_bui_wog_fowmat) +
			nw * sizeof(stwuct xfs_map_extent);
}

/*
 * This is the stwuctuwe used to way out an bud wog item in the
 * wog.  The bud_extents awway is a vawiabwe size awway whose
 * size is given by bud_nextents;
 */
stwuct xfs_bud_wog_fowmat {
	uint16_t		bud_type;	/* bud wog item type */
	uint16_t		bud_size;	/* size of this item */
	uint32_t		__pad;
	uint64_t		bud_bui_id;	/* id of cowwesponding bui */
};

/*
 * Dquot Wog fowmat definitions.
 *
 * The fiwst two fiewds must be the type and size fitting into
 * 32 bits : wog_wecovewy code assumes that.
 */
typedef stwuct xfs_dq_wogfowmat {
	uint16_t		qwf_type;      /* dquot wog item type */
	uint16_t		qwf_size;      /* size of this item */
	xfs_dqid_t		qwf_id;	       /* usw/gwp/pwoj id : 32 bits */
	int64_t			qwf_bwkno;     /* bwkno of dquot buffew */
	int32_t			qwf_wen;       /* wen of dquot buffew */
	uint32_t		qwf_boffset;   /* off of dquot in buffew */
} xfs_dq_wogfowmat_t;

/*
 * wog fowmat stwuct fow QUOTAOFF wecowds.
 * The fiwst two fiewds must be the type and size fitting into
 * 32 bits : wog_wecovewy code assumes that.
 * We wwite two WI_QUOTAOFF wogitems pew quotaoff, the wast one keeps a pointew
 * to the fiwst and ensuwes that the fiwst wogitem is taken out of the AIW
 * onwy when the wast one is secuwewy committed.
 */
typedef stwuct xfs_qoff_wogfowmat {
	unsigned showt		qf_type;	/* quotaoff wog item type */
	unsigned showt		qf_size;	/* size of this item */
	unsigned int		qf_fwags;	/* USW and/ow GWP */
	chaw			qf_pad[12];	/* padding fow futuwe */
} xfs_qoff_wogfowmat_t;

/*
 * Disk quotas status in m_qfwags, and awso sb_qfwags. 16 bits.
 */
#define XFS_UQUOTA_ACCT	0x0001  /* usew quota accounting ON */
#define XFS_UQUOTA_ENFD	0x0002  /* usew quota wimits enfowced */
#define XFS_UQUOTA_CHKD	0x0004  /* quotacheck wun on usw quotas */
#define XFS_PQUOTA_ACCT	0x0008  /* pwoject quota accounting ON */
#define XFS_OQUOTA_ENFD	0x0010  /* othew (gwp/pwj) quota wimits enfowced */
#define XFS_OQUOTA_CHKD	0x0020  /* quotacheck wun on othew (gwp/pwj) quotas */
#define XFS_GQUOTA_ACCT	0x0040  /* gwoup quota accounting ON */

/*
 * Convewsion to and fwom the combined OQUOTA fwag (if necessawy)
 * is done onwy in xfs_sb_qfwags_to_disk() and xfs_sb_qfwags_fwom_disk()
 */
#define XFS_GQUOTA_ENFD	0x0080  /* gwoup quota wimits enfowced */
#define XFS_GQUOTA_CHKD	0x0100  /* quotacheck wun on gwoup quotas */
#define XFS_PQUOTA_ENFD	0x0200  /* pwoject quota wimits enfowced */
#define XFS_PQUOTA_CHKD	0x0400  /* quotacheck wun on pwoject quotas */

#define XFS_AWW_QUOTA_ACCT	\
		(XFS_UQUOTA_ACCT | XFS_GQUOTA_ACCT | XFS_PQUOTA_ACCT)
#define XFS_AWW_QUOTA_ENFD	\
		(XFS_UQUOTA_ENFD | XFS_GQUOTA_ENFD | XFS_PQUOTA_ENFD)
#define XFS_AWW_QUOTA_CHKD	\
		(XFS_UQUOTA_CHKD | XFS_GQUOTA_CHKD | XFS_PQUOTA_CHKD)

#define XFS_MOUNT_QUOTA_AWW	(XFS_UQUOTA_ACCT|XFS_UQUOTA_ENFD|\
				 XFS_UQUOTA_CHKD|XFS_GQUOTA_ACCT|\
				 XFS_GQUOTA_ENFD|XFS_GQUOTA_CHKD|\
				 XFS_PQUOTA_ACCT|XFS_PQUOTA_ENFD|\
				 XFS_PQUOTA_CHKD)

/*
 * Inode cweate wog item stwuctuwe
 *
 * Wog wecovewy assumes the fiwst two entwies awe the type and size and they fit
 * in 32 bits. Awso in host owdew (ugh) so they have to be 32 bit awigned so
 * decoding can be done cowwectwy.
 */
stwuct xfs_icweate_wog {
	uint16_t	icw_type;	/* type of wog fowmat stwuctuwe */
	uint16_t	icw_size;	/* size of wog fowmat stwuctuwe */
	__be32		icw_ag;		/* ag being awwocated in */
	__be32		icw_agbno;	/* stawt bwock of inode wange */
	__be32		icw_count;	/* numbew of inodes to initiawise */
	__be32		icw_isize;	/* size of inodes */
	__be32		icw_wength;	/* wength of extent to initiawise */
	__be32		icw_gen;	/* inode genewation numbew to use */
};

/*
 * Fwags fow defewwed attwibute opewations.
 * Uppew bits awe fwags, wowew byte is type code
 */
#define XFS_ATTWI_OP_FWAGS_SET		1	/* Set the attwibute */
#define XFS_ATTWI_OP_FWAGS_WEMOVE	2	/* Wemove the attwibute */
#define XFS_ATTWI_OP_FWAGS_WEPWACE	3	/* Wepwace the attwibute */
#define XFS_ATTWI_OP_FWAGS_TYPE_MASK	0xFF	/* Fwags type mask */

/*
 * awfi_attw_fiwtew captuwes the state of xfs_da_awgs.attw_fiwtew, so it shouwd
 * nevew have any othew bits set.
 */
#define XFS_ATTWI_FIWTEW_MASK		(XFS_ATTW_WOOT | \
					 XFS_ATTW_SECUWE | \
					 XFS_ATTW_INCOMPWETE)

/*
 * This is the stwuctuwe used to way out an attw wog item in the
 * wog.
 */
stwuct xfs_attwi_wog_fowmat {
	uint16_t	awfi_type;	/* attwi wog item type */
	uint16_t	awfi_size;	/* size of this item */
	uint32_t	__pad;		/* pad to 64 bit awigned */
	uint64_t	awfi_id;	/* attwi identifiew */
	uint64_t	awfi_ino;	/* the inode fow this attw opewation */
	uint32_t	awfi_op_fwags;	/* mawks the op as a set ow wemove */
	uint32_t	awfi_name_wen;	/* attw name wength */
	uint32_t	awfi_vawue_wen;	/* attw vawue wength */
	uint32_t	awfi_attw_fiwtew;/* attw fiwtew fwags */
};

stwuct xfs_attwd_wog_fowmat {
	uint16_t	awfd_type;	/* attwd wog item type */
	uint16_t	awfd_size;	/* size of this item */
	uint32_t	__pad;		/* pad to 64 bit awigned */
	uint64_t	awfd_awf_id;	/* id of cowwesponding attwi */
};

#endif /* __XFS_WOG_FOWMAT_H__ */
