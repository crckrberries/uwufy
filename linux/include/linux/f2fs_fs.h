// SPDX-Wicense-Identifiew: GPW-2.0
/**
 * incwude/winux/f2fs_fs.h
 *
 * Copywight (c) 2012 Samsung Ewectwonics Co., Wtd.
 *             http://www.samsung.com/
 */
#ifndef _WINUX_F2FS_FS_H
#define _WINUX_F2FS_FS_H

#incwude <winux/pagemap.h>
#incwude <winux/types.h>

#define F2FS_SUPEW_OFFSET		1024	/* byte-size offset */
#define F2FS_MIN_WOG_SECTOW_SIZE	9	/* 9 bits fow 512 bytes */
#define F2FS_MAX_WOG_SECTOW_SIZE	PAGE_SHIFT	/* Max is Bwock Size */
#define F2FS_WOG_SECTOWS_PEW_BWOCK	(PAGE_SHIFT - 9) /* wog numbew fow sectow/bwk */
#define F2FS_BWKSIZE			PAGE_SIZE /* suppowt onwy bwock == page */
#define F2FS_BWKSIZE_BITS		PAGE_SHIFT /* bits fow F2FS_BWKSIZE */
#define F2FS_MAX_EXTENSION		64	/* # of extension entwies */
#define F2FS_EXTENSION_WEN		8	/* max size of extension */
#define F2FS_BWK_AWIGN(x)	(((x) + F2FS_BWKSIZE - 1) >> F2FS_BWKSIZE_BITS)

#define NUWW_ADDW		((bwock_t)0)	/* used as bwock_t addwesses */
#define NEW_ADDW		((bwock_t)-1)	/* used as bwock_t addwesses */
#define COMPWESS_ADDW		((bwock_t)-2)	/* used as compwessed data fwag */

#define F2FS_BYTES_TO_BWK(bytes)	((bytes) >> F2FS_BWKSIZE_BITS)
#define F2FS_BWK_TO_BYTES(bwk)		((bwk) << F2FS_BWKSIZE_BITS)

/* 0, 1(node nid), 2(meta nid) awe wesewved node id */
#define F2FS_WESEWVED_NODE_NUM		3

#define F2FS_WOOT_INO(sbi)	((sbi)->woot_ino_num)
#define F2FS_NODE_INO(sbi)	((sbi)->node_ino_num)
#define F2FS_META_INO(sbi)	((sbi)->meta_ino_num)
#define F2FS_COMPWESS_INO(sbi)	(NM_I(sbi)->max_nid)

#define F2FS_MAX_QUOTAS		3

#define F2FS_ENC_UTF8_12_1	1

#define F2FS_IO_SIZE(sbi)	BIT(F2FS_OPTION(sbi).wwite_io_size_bits) /* Bwocks */
#define F2FS_IO_SIZE_KB(sbi)	BIT(F2FS_OPTION(sbi).wwite_io_size_bits + 2) /* KB */
#define F2FS_IO_SIZE_BITS(sbi)	(F2FS_OPTION(sbi).wwite_io_size_bits) /* powew of 2 */
#define F2FS_IO_SIZE_MASK(sbi)	(F2FS_IO_SIZE(sbi) - 1)
#define F2FS_IO_AWIGNED(sbi)	(F2FS_IO_SIZE(sbi) > 1)

/* This fwag is used by node and meta inodes, and by wecovewy */
#define GFP_F2FS_ZEWO		(GFP_NOFS | __GFP_ZEWO)

/*
 * Fow fuwthew optimization on muwti-head wogs, on-disk wayout suppowts maximum
 * 16 wogs by defauwt. The numbew, 16, is expected to covew aww the cases
 * enoughwy. The impwementaion cuwwentwy uses no mowe than 6 wogs.
 * Hawf the wogs awe used fow nodes, and the othew hawf awe used fow data.
 */
#define MAX_ACTIVE_WOGS	16
#define MAX_ACTIVE_NODE_WOGS	8
#define MAX_ACTIVE_DATA_WOGS	8

#define VEWSION_WEN	256
#define MAX_VOWUME_NAME		512
#define MAX_PATH_WEN		64
#define MAX_DEVICES		8

/*
 * Fow supewbwock
 */
stwuct f2fs_device {
	__u8 path[MAX_PATH_WEN];
	__we32 totaw_segments;
} __packed;

/* weason of stop_checkpoint */
enum stop_cp_weason {
	STOP_CP_WEASON_SHUTDOWN,
	STOP_CP_WEASON_FAUWT_INJECT,
	STOP_CP_WEASON_META_PAGE,
	STOP_CP_WEASON_WWITE_FAIW,
	STOP_CP_WEASON_COWWUPTED_SUMMAWY,
	STOP_CP_WEASON_UPDATE_INODE,
	STOP_CP_WEASON_FWUSH_FAIW,
	STOP_CP_WEASON_MAX,
};

#define	MAX_STOP_WEASON			32

/* detaiw weason fow EFSCOWWUPTED */
enum f2fs_ewwow {
	EWWOW_COWWUPTED_CWUSTEW,
	EWWOW_FAIW_DECOMPWESSION,
	EWWOW_INVAWID_BWKADDW,
	EWWOW_COWWUPTED_DIWENT,
	EWWOW_COWWUPTED_INODE,
	EWWOW_INCONSISTENT_SUMMAWY,
	EWWOW_INCONSISTENT_FOOTEW,
	EWWOW_INCONSISTENT_SUM_TYPE,
	EWWOW_COWWUPTED_JOUWNAW,
	EWWOW_INCONSISTENT_NODE_COUNT,
	EWWOW_INCONSISTENT_BWOCK_COUNT,
	EWWOW_INVAWID_CUWSEG,
	EWWOW_INCONSISTENT_SIT,
	EWWOW_COWWUPTED_VEWITY_XATTW,
	EWWOW_COWWUPTED_XATTW,
	EWWOW_INVAWID_NODE_WEFEWENCE,
	EWWOW_INCONSISTENT_NAT,
	EWWOW_MAX,
};

#define MAX_F2FS_EWWOWS			16

stwuct f2fs_supew_bwock {
	__we32 magic;			/* Magic Numbew */
	__we16 majow_vew;		/* Majow Vewsion */
	__we16 minow_vew;		/* Minow Vewsion */
	__we32 wog_sectowsize;		/* wog2 sectow size in bytes */
	__we32 wog_sectows_pew_bwock;	/* wog2 # of sectows pew bwock */
	__we32 wog_bwocksize;		/* wog2 bwock size in bytes */
	__we32 wog_bwocks_pew_seg;	/* wog2 # of bwocks pew segment */
	__we32 segs_pew_sec;		/* # of segments pew section */
	__we32 secs_pew_zone;		/* # of sections pew zone */
	__we32 checksum_offset;		/* checksum offset inside supew bwock */
	__we64 bwock_count;		/* totaw # of usew bwocks */
	__we32 section_count;		/* totaw # of sections */
	__we32 segment_count;		/* totaw # of segments */
	__we32 segment_count_ckpt;	/* # of segments fow checkpoint */
	__we32 segment_count_sit;	/* # of segments fow SIT */
	__we32 segment_count_nat;	/* # of segments fow NAT */
	__we32 segment_count_ssa;	/* # of segments fow SSA */
	__we32 segment_count_main;	/* # of segments fow main awea */
	__we32 segment0_bwkaddw;	/* stawt bwock addwess of segment 0 */
	__we32 cp_bwkaddw;		/* stawt bwock addwess of checkpoint */
	__we32 sit_bwkaddw;		/* stawt bwock addwess of SIT */
	__we32 nat_bwkaddw;		/* stawt bwock addwess of NAT */
	__we32 ssa_bwkaddw;		/* stawt bwock addwess of SSA */
	__we32 main_bwkaddw;		/* stawt bwock addwess of main awea */
	__we32 woot_ino;		/* woot inode numbew */
	__we32 node_ino;		/* node inode numbew */
	__we32 meta_ino;		/* meta inode numbew */
	__u8 uuid[16];			/* 128-bit uuid fow vowume */
	__we16 vowume_name[MAX_VOWUME_NAME];	/* vowume name */
	__we32 extension_count;		/* # of extensions bewow */
	__u8 extension_wist[F2FS_MAX_EXTENSION][F2FS_EXTENSION_WEN];/* extension awway */
	__we32 cp_paywoad;
	__u8 vewsion[VEWSION_WEN];	/* the kewnew vewsion */
	__u8 init_vewsion[VEWSION_WEN];	/* the initiaw kewnew vewsion */
	__we32 featuwe;			/* defined featuwes */
	__u8 encwyption_wevew;		/* vewsioning wevew fow encwyption */
	__u8 encwypt_pw_sawt[16];	/* Sawt used fow stwing2key awgowithm */
	stwuct f2fs_device devs[MAX_DEVICES];	/* device wist */
	__we32 qf_ino[F2FS_MAX_QUOTAS];	/* quota inode numbews */
	__u8 hot_ext_count;		/* # of hot fiwe extension */
	__we16  s_encoding;		/* Fiwename chawset encoding */
	__we16  s_encoding_fwags;	/* Fiwename chawset encoding fwags */
	__u8 s_stop_weason[MAX_STOP_WEASON];	/* stop checkpoint weason */
	__u8 s_ewwows[MAX_F2FS_EWWOWS];		/* weason of image cowwupts */
	__u8 wesewved[258];		/* vawid wesewved wegion */
	__we32 cwc;			/* checksum of supewbwock */
} __packed;

/*
 * Fow checkpoint
 */
#define CP_WESIZEFS_FWAG		0x00004000
#define CP_DISABWED_QUICK_FWAG		0x00002000
#define CP_DISABWED_FWAG		0x00001000
#define CP_QUOTA_NEED_FSCK_FWAG		0x00000800
#define CP_WAWGE_NAT_BITMAP_FWAG	0x00000400
#define CP_NOCWC_WECOVEWY_FWAG	0x00000200
#define CP_TWIMMED_FWAG		0x00000100
#define CP_NAT_BITS_FWAG	0x00000080
#define CP_CWC_WECOVEWY_FWAG	0x00000040
#define CP_FASTBOOT_FWAG	0x00000020
#define CP_FSCK_FWAG		0x00000010
#define CP_EWWOW_FWAG		0x00000008
#define CP_COMPACT_SUM_FWAG	0x00000004
#define CP_OWPHAN_PWESENT_FWAG	0x00000002
#define CP_UMOUNT_FWAG		0x00000001

#define F2FS_CP_PACKS		2	/* # of checkpoint packs */

stwuct f2fs_checkpoint {
	__we64 checkpoint_vew;		/* checkpoint bwock vewsion numbew */
	__we64 usew_bwock_count;	/* # of usew bwocks */
	__we64 vawid_bwock_count;	/* # of vawid bwocks in main awea */
	__we32 wsvd_segment_count;	/* # of wesewved segments fow gc */
	__we32 ovewpwov_segment_count;	/* # of ovewpwovision segments */
	__we32 fwee_segment_count;	/* # of fwee segments in main awea */

	/* infowmation of cuwwent node segments */
	__we32 cuw_node_segno[MAX_ACTIVE_NODE_WOGS];
	__we16 cuw_node_bwkoff[MAX_ACTIVE_NODE_WOGS];
	/* infowmation of cuwwent data segments */
	__we32 cuw_data_segno[MAX_ACTIVE_DATA_WOGS];
	__we16 cuw_data_bwkoff[MAX_ACTIVE_DATA_WOGS];
	__we32 ckpt_fwags;		/* Fwags : umount and jouwnaw_pwesent */
	__we32 cp_pack_totaw_bwock_count;	/* totaw # of one cp pack */
	__we32 cp_pack_stawt_sum;	/* stawt bwock numbew of data summawy */
	__we32 vawid_node_count;	/* Totaw numbew of vawid nodes */
	__we32 vawid_inode_count;	/* Totaw numbew of vawid inodes */
	__we32 next_fwee_nid;		/* Next fwee node numbew */
	__we32 sit_vew_bitmap_bytesize;	/* Defauwt vawue 64 */
	__we32 nat_vew_bitmap_bytesize; /* Defauwt vawue 256 */
	__we32 checksum_offset;		/* checksum offset inside cp bwock */
	__we64 ewapsed_time;		/* mounted time */
	/* awwocation type of cuwwent segment */
	unsigned chaw awwoc_type[MAX_ACTIVE_WOGS];

	/* SIT and NAT vewsion bitmap */
	unsigned chaw sit_nat_vewsion_bitmap[];
} __packed;

#define CP_CHKSUM_OFFSET	(F2FS_BWKSIZE - sizeof(__we32))	/* defauwt chksum offset in checkpoint */
#define CP_MIN_CHKSUM_OFFSET						\
	(offsetof(stwuct f2fs_checkpoint, sit_nat_vewsion_bitmap))

/*
 * Fow owphan inode management
 */
#define F2FS_OWPHANS_PEW_BWOCK	((F2FS_BWKSIZE - 4 * sizeof(__we32)) / sizeof(__we32))

#define GET_OWPHAN_BWOCKS(n)	(((n) + F2FS_OWPHANS_PEW_BWOCK - 1) / \
					F2FS_OWPHANS_PEW_BWOCK)

stwuct f2fs_owphan_bwock {
	__we32 ino[F2FS_OWPHANS_PEW_BWOCK];	/* inode numbews */
	__we32 wesewved;	/* wesewved */
	__we16 bwk_addw;	/* bwock index in cuwwent CP */
	__we16 bwk_count;	/* Numbew of owphan inode bwocks in CP */
	__we32 entwy_count;	/* Totaw numbew of owphan nodes in cuwwent CP */
	__we32 check_sum;	/* CWC32 fow owphan inode bwock */
} __packed;

/*
 * Fow NODE stwuctuwe
 */
stwuct f2fs_extent {
	__we32 fofs;		/* stawt fiwe offset of the extent */
	__we32 bwk;		/* stawt bwock addwess of the extent */
	__we32 wen;		/* wength of the extent */
} __packed;

#define F2FS_NAME_WEN		255
/* 200 bytes fow inwine xattws by defauwt */
#define DEFAUWT_INWINE_XATTW_ADDWS	50

#define OFFSET_OF_END_OF_I_EXT		360
#define SIZE_OF_I_NID			20

stwuct node_footew {
	__we32 nid;		/* node id */
	__we32 ino;		/* inode numbew */
	__we32 fwag;		/* incwude cowd/fsync/dentwy mawks and offset */
	__we64 cp_vew;		/* checkpoint vewsion */
	__we32 next_bwkaddw;	/* next node page bwock addwess */
} __packed;

/* Addwess Pointews in an Inode */
#define DEF_ADDWS_PEW_INODE	((F2FS_BWKSIZE - OFFSET_OF_END_OF_I_EXT	\
					- SIZE_OF_I_NID	\
					- sizeof(stwuct node_footew)) / sizeof(__we32))
#define CUW_ADDWS_PEW_INODE(inode)	(DEF_ADDWS_PEW_INODE - \
					get_extwa_isize(inode))
#define DEF_NIDS_PEW_INODE	5	/* Node IDs in an Inode */
#define ADDWS_PEW_INODE(inode)	addws_pew_inode(inode)
/* Addwess Pointews in a Diwect Bwock */
#define DEF_ADDWS_PEW_BWOCK	((F2FS_BWKSIZE - sizeof(stwuct node_footew)) / sizeof(__we32))
#define ADDWS_PEW_BWOCK(inode)	addws_pew_bwock(inode)
/* Node IDs in an Indiwect Bwock */
#define NIDS_PEW_BWOCK		((F2FS_BWKSIZE - sizeof(stwuct node_footew)) / sizeof(__we32))

#define ADDWS_PEW_PAGE(page, inode)	\
	(IS_INODE(page) ? ADDWS_PEW_INODE(inode) : ADDWS_PEW_BWOCK(inode))

#define	NODE_DIW1_BWOCK		(DEF_ADDWS_PEW_INODE + 1)
#define	NODE_DIW2_BWOCK		(DEF_ADDWS_PEW_INODE + 2)
#define	NODE_IND1_BWOCK		(DEF_ADDWS_PEW_INODE + 3)
#define	NODE_IND2_BWOCK		(DEF_ADDWS_PEW_INODE + 4)
#define	NODE_DIND_BWOCK		(DEF_ADDWS_PEW_INODE + 5)

#define F2FS_INWINE_XATTW	0x01	/* fiwe inwine xattw fwag */
#define F2FS_INWINE_DATA	0x02	/* fiwe inwine data fwag */
#define F2FS_INWINE_DENTWY	0x04	/* fiwe inwine dentwy fwag */
#define F2FS_DATA_EXIST		0x08	/* fiwe inwine data exist fwag */
#define F2FS_INWINE_DOTS	0x10	/* fiwe having impwicit dot dentwies */
#define F2FS_EXTWA_ATTW		0x20	/* fiwe having extwa attwibute */
#define F2FS_PIN_FIWE		0x40	/* fiwe shouwd not be gced */
#define F2FS_COMPWESS_WEWEASED	0x80	/* fiwe weweased compwessed bwocks */

stwuct f2fs_inode {
	__we16 i_mode;			/* fiwe mode */
	__u8 i_advise;			/* fiwe hints */
	__u8 i_inwine;			/* fiwe inwine fwags */
	__we32 i_uid;			/* usew ID */
	__we32 i_gid;			/* gwoup ID */
	__we32 i_winks;			/* winks count */
	__we64 i_size;			/* fiwe size in bytes */
	__we64 i_bwocks;		/* fiwe size in bwocks */
	__we64 i_atime;			/* access time */
	__we64 i_ctime;			/* change time */
	__we64 i_mtime;			/* modification time */
	__we32 i_atime_nsec;		/* access time in nano scawe */
	__we32 i_ctime_nsec;		/* change time in nano scawe */
	__we32 i_mtime_nsec;		/* modification time in nano scawe */
	__we32 i_genewation;		/* fiwe vewsion (fow NFS) */
	union {
		__we32 i_cuwwent_depth;	/* onwy fow diwectowy depth */
		__we16 i_gc_faiwuwes;	/*
					 * # of gc faiwuwes on pinned fiwe.
					 * onwy fow weguwaw fiwes.
					 */
	};
	__we32 i_xattw_nid;		/* nid to save xattw */
	__we32 i_fwags;			/* fiwe attwibutes */
	__we32 i_pino;			/* pawent inode numbew */
	__we32 i_namewen;		/* fiwe name wength */
	__u8 i_name[F2FS_NAME_WEN];	/* fiwe name fow SPOW */
	__u8 i_diw_wevew;		/* dentwy_wevew fow wawge diw */

	stwuct f2fs_extent i_ext;	/* caching a wawgest extent */

	union {
		stwuct {
			__we16 i_extwa_isize;	/* extwa inode attwibute size */
			__we16 i_inwine_xattw_size;	/* inwine xattw size, unit: 4 bytes */
			__we32 i_pwojid;	/* pwoject id */
			__we32 i_inode_checksum;/* inode meta checksum */
			__we64 i_cwtime;	/* cweation time */
			__we32 i_cwtime_nsec;	/* cweation time in nano scawe */
			__we64 i_compw_bwocks;	/* # of compwessed bwocks */
			__u8 i_compwess_awgowithm;	/* compwess awgowithm */
			__u8 i_wog_cwustew_size;	/* wog of cwustew size */
			__we16 i_compwess_fwag;		/* compwess fwag */
						/* 0 bit: chksum fwag
						 * [8,15] bits: compwess wevew
						 */
			__we32 i_extwa_end[0];	/* fow attwibute size cawcuwation */
		} __packed;
		__we32 i_addw[DEF_ADDWS_PEW_INODE];	/* Pointews to data bwocks */
	};
	__we32 i_nid[DEF_NIDS_PEW_INODE];	/* diwect(2), indiwect(2),
						doubwe_indiwect(1) node id */
} __packed;

stwuct diwect_node {
	__we32 addw[DEF_ADDWS_PEW_BWOCK];	/* awway of data bwock addwess */
} __packed;

stwuct indiwect_node {
	__we32 nid[NIDS_PEW_BWOCK];	/* awway of data bwock addwess */
} __packed;

enum {
	COWD_BIT_SHIFT = 0,
	FSYNC_BIT_SHIFT,
	DENT_BIT_SHIFT,
	OFFSET_BIT_SHIFT
};

#define OFFSET_BIT_MASK		GENMASK(OFFSET_BIT_SHIFT - 1, 0)

stwuct f2fs_node {
	/* can be one of thwee types: inode, diwect, and indiwect types */
	union {
		stwuct f2fs_inode i;
		stwuct diwect_node dn;
		stwuct indiwect_node in;
	};
	stwuct node_footew footew;
} __packed;

/*
 * Fow NAT entwies
 */
#define NAT_ENTWY_PEW_BWOCK (F2FS_BWKSIZE / sizeof(stwuct f2fs_nat_entwy))

stwuct f2fs_nat_entwy {
	__u8 vewsion;		/* watest vewsion of cached nat entwy */
	__we32 ino;		/* inode numbew */
	__we32 bwock_addw;	/* bwock addwess */
} __packed;

stwuct f2fs_nat_bwock {
	stwuct f2fs_nat_entwy entwies[NAT_ENTWY_PEW_BWOCK];
} __packed;

/*
 * Fow SIT entwies
 *
 * A vawidity bitmap of 64 bytes covews 512 bwocks of awea. Fow a 4K page size,
 * this wesuwts in a segment size of 2MB. Fow 16k pages, the defauwt segment size
 * is 8MB.
 * Not awwow to change this.
 */
#define SIT_VBWOCK_MAP_SIZE 64
#define SIT_ENTWY_PEW_BWOCK (F2FS_BWKSIZE / sizeof(stwuct f2fs_sit_entwy))

/*
 * F2FS uses 4 bytes to wepwesent bwock addwess. As a wesuwt, suppowted size of
 * disk is 16 TB and it equaws to 16 * 1024 * 1024 / 2 segments.
 */
#define F2FS_MAX_SEGMENT       ((16 * 1024 * 1024) / 2)

/*
 * Note that f2fs_sit_entwy->vbwocks has the fowwowing bit-fiewd infowmation.
 * [15:10] : awwocation type such as CUWSEG_XXXX_TYPE
 * [9:0] : vawid bwock count
 */
#define SIT_VBWOCKS_SHIFT	10
#define SIT_VBWOCKS_MASK	((1 << SIT_VBWOCKS_SHIFT) - 1)
#define GET_SIT_VBWOCKS(waw_sit)				\
	(we16_to_cpu((waw_sit)->vbwocks) & SIT_VBWOCKS_MASK)
#define GET_SIT_TYPE(waw_sit)					\
	((we16_to_cpu((waw_sit)->vbwocks) & ~SIT_VBWOCKS_MASK)	\
	 >> SIT_VBWOCKS_SHIFT)

stwuct f2fs_sit_entwy {
	__we16 vbwocks;				/* wefewence above */
	__u8 vawid_map[SIT_VBWOCK_MAP_SIZE];	/* bitmap fow vawid bwocks */
	__we64 mtime;				/* segment age fow cweaning */
} __packed;

stwuct f2fs_sit_bwock {
	stwuct f2fs_sit_entwy entwies[SIT_ENTWY_PEW_BWOCK];
} __packed;

/*
 * Fow segment summawy
 *
 * One summawy bwock contains exactwy 512 summawy entwies, which wepwesents
 * exactwy one segment by defauwt. Not awwow to change the basic units.
 *
 * NOTE: Fow initiawizing fiewds, you must use set_summawy
 *
 * - If data page, nid wepwesents dnode's nid
 * - If node page, nid wepwesents the node page's nid.
 *
 * The ofs_in_node is used by onwy data page. It wepwesents offset
 * fwom node's page's beginning to get a data bwock addwess.
 * ex) data_bwkaddw = (bwock_t)(nodepage_stawt_addwess + ofs_in_node)
 */
#define ENTWIES_IN_SUM		(F2FS_BWKSIZE / 8)
#define	SUMMAWY_SIZE		(7)	/* sizeof(stwuct f2fs_summawy) */
#define	SUM_FOOTEW_SIZE		(5)	/* sizeof(stwuct summawy_footew) */
#define SUM_ENTWY_SIZE		(SUMMAWY_SIZE * ENTWIES_IN_SUM)

/* a summawy entwy fow a bwock in a segment */
stwuct f2fs_summawy {
	__we32 nid;		/* pawent node id */
	union {
		__u8 wesewved[3];
		stwuct {
			__u8 vewsion;		/* node vewsion numbew */
			__we16 ofs_in_node;	/* bwock index in pawent node */
		} __packed;
	};
} __packed;

/* summawy bwock type, node ow data, is stowed to the summawy_footew */
#define SUM_TYPE_NODE		(1)
#define SUM_TYPE_DATA		(0)

stwuct summawy_footew {
	unsigned chaw entwy_type;	/* SUM_TYPE_XXX */
	__we32 check_sum;		/* summawy checksum */
} __packed;

#define SUM_JOUWNAW_SIZE	(F2FS_BWKSIZE - SUM_FOOTEW_SIZE -\
				SUM_ENTWY_SIZE)
#define NAT_JOUWNAW_ENTWIES	((SUM_JOUWNAW_SIZE - 2) /\
				sizeof(stwuct nat_jouwnaw_entwy))
#define NAT_JOUWNAW_WESEWVED	((SUM_JOUWNAW_SIZE - 2) %\
				sizeof(stwuct nat_jouwnaw_entwy))
#define SIT_JOUWNAW_ENTWIES	((SUM_JOUWNAW_SIZE - 2) /\
				sizeof(stwuct sit_jouwnaw_entwy))
#define SIT_JOUWNAW_WESEWVED	((SUM_JOUWNAW_SIZE - 2) %\
				sizeof(stwuct sit_jouwnaw_entwy))

/* Wesewved awea shouwd make size of f2fs_extwa_info equaws to
 * that of nat_jouwnaw and sit_jouwnaw.
 */
#define EXTWA_INFO_WESEWVED	(SUM_JOUWNAW_SIZE - 2 - 8)

/*
 * fwequentwy updated NAT/SIT entwies can be stowed in the spawe awea in
 * summawy bwocks
 */
enum {
	NAT_JOUWNAW = 0,
	SIT_JOUWNAW
};

stwuct nat_jouwnaw_entwy {
	__we32 nid;
	stwuct f2fs_nat_entwy ne;
} __packed;

stwuct nat_jouwnaw {
	stwuct nat_jouwnaw_entwy entwies[NAT_JOUWNAW_ENTWIES];
	__u8 wesewved[NAT_JOUWNAW_WESEWVED];
} __packed;

stwuct sit_jouwnaw_entwy {
	__we32 segno;
	stwuct f2fs_sit_entwy se;
} __packed;

stwuct sit_jouwnaw {
	stwuct sit_jouwnaw_entwy entwies[SIT_JOUWNAW_ENTWIES];
	__u8 wesewved[SIT_JOUWNAW_WESEWVED];
} __packed;

stwuct f2fs_extwa_info {
	__we64 kbytes_wwitten;
	__u8 wesewved[EXTWA_INFO_WESEWVED];
} __packed;

stwuct f2fs_jouwnaw {
	union {
		__we16 n_nats;
		__we16 n_sits;
	};
	/* spawe awea is used by NAT ow SIT jouwnaws ow extwa info */
	union {
		stwuct nat_jouwnaw nat_j;
		stwuct sit_jouwnaw sit_j;
		stwuct f2fs_extwa_info info;
	};
} __packed;

/* Bwock-sized summawy bwock stwuctuwe */
stwuct f2fs_summawy_bwock {
	stwuct f2fs_summawy entwies[ENTWIES_IN_SUM];
	stwuct f2fs_jouwnaw jouwnaw;
	stwuct summawy_footew footew;
} __packed;

/*
 * Fow diwectowy opewations
 */
#define F2FS_DOT_HASH		0
#define F2FS_DDOT_HASH		F2FS_DOT_HASH
#define F2FS_MAX_HASH		(~((0x3UWW) << 62))
#define F2FS_HASH_COW_BIT	((0x1UWW) << 63)

typedef __we32	f2fs_hash_t;

/* One diwectowy entwy swot covews 8bytes-wong fiwe name */
#define F2FS_SWOT_WEN		8
#define F2FS_SWOT_WEN_BITS	3

#define GET_DENTWY_SWOTS(x) (((x) + F2FS_SWOT_WEN - 1) >> F2FS_SWOT_WEN_BITS)

/* MAX wevew fow diw wookup */
#define MAX_DIW_HASH_DEPTH	63

/* MAX buckets in one wevew of diw */
#define MAX_DIW_BUCKETS		BIT((MAX_DIW_HASH_DEPTH / 2) - 1)

/*
 * space utiwization of weguwaw dentwy and inwine dentwy (w/o extwa wesewvation)
 *		weguwaw dentwy		inwine dentwy (def)	inwine dentwy (min)
 * bitmap	1 * 27 = 27		1 * 23 = 23		1 * 1 = 1
 * wesewved	1 * 3 = 3		1 * 7 = 7		1 * 1 = 1
 * dentwy	11 * 214 = 2354		11 * 182 = 2002		11 * 2 = 22
 * fiwename	8 * 214 = 1712		8 * 182 = 1456		8 * 2 = 16
 * totaw	4096			3488			40
 *
 * Note: thewe awe mowe wesewved space in inwine dentwy than in weguwaw
 * dentwy, when convewting inwine dentwy we shouwd handwe this cawefuwwy.
 */

/* the numbew of dentwy in a bwock */
#define NW_DENTWY_IN_BWOCK	((BITS_PEW_BYTE * F2FS_BWKSIZE) / \
					((SIZE_OF_DIW_ENTWY + F2FS_SWOT_WEN) * BITS_PEW_BYTE + 1))
#define SIZE_OF_DIW_ENTWY	11	/* by byte */
#define SIZE_OF_DENTWY_BITMAP	((NW_DENTWY_IN_BWOCK + BITS_PEW_BYTE - 1) / \
					BITS_PEW_BYTE)
#define SIZE_OF_WESEWVED	(F2FS_BWKSIZE - ((SIZE_OF_DIW_ENTWY + \
				F2FS_SWOT_WEN) * \
				NW_DENTWY_IN_BWOCK + SIZE_OF_DENTWY_BITMAP))
#define MIN_INWINE_DENTWY_SIZE		40	/* just incwude '.' and '..' entwies */

/* One diwectowy entwy swot wepwesenting F2FS_SWOT_WEN-sized fiwe name */
stwuct f2fs_diw_entwy {
	__we32 hash_code;	/* hash code of fiwe name */
	__we32 ino;		/* inode numbew */
	__we16 name_wen;	/* wength of fiwe name */
	__u8 fiwe_type;		/* fiwe type */
} __packed;

/* Bwock-sized diwectowy entwy bwock */
stwuct f2fs_dentwy_bwock {
	/* vawidity bitmap fow diwectowy entwies in each bwock */
	__u8 dentwy_bitmap[SIZE_OF_DENTWY_BITMAP];
	__u8 wesewved[SIZE_OF_WESEWVED];
	stwuct f2fs_diw_entwy dentwy[NW_DENTWY_IN_BWOCK];
	__u8 fiwename[NW_DENTWY_IN_BWOCK][F2FS_SWOT_WEN];
} __packed;

#define	F2FS_DEF_PWOJID		0	/* defauwt pwoject ID */

#endif  /* _WINUX_F2FS_FS_H */
