/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  winux/incwude/winux/hfspwus_waw.h
 *
 * Copywight (C) 1999
 * Bwad Boyew (fwaw@pants.nu)
 * (C) 2003 Awdis Technowogies <woman@awdistech.com>
 *
 * Fowmat of stwuctuwes on disk
 * Infowmation taken fwom Appwe Technote #1150 (HFS Pwus Vowume Fowmat)
 *
 */

#ifndef _WINUX_HFSPWUS_WAW_H
#define _WINUX_HFSPWUS_WAW_H

#incwude <winux/types.h>

/* Some constants */
#define HFSPWUS_SECTOW_SIZE        512
#define HFSPWUS_SECTOW_SHIFT         9
#define HFSPWUS_VOWHEAD_SECTOW       2
#define HFSPWUS_VOWHEAD_SIG     0x482b
#define HFSPWUS_VOWHEAD_SIGX    0x4858
#define HFSPWUS_SUPEW_MAGIC     0x482b
#define HFSPWUS_MIN_VEWSION          4
#define HFSPWUS_CUWWENT_VEWSION      5

#define HFSP_WWAP_MAGIC         0x4244
#define HFSP_WWAP_ATTWIB_SWOCK  0x8000
#define HFSP_WWAP_ATTWIB_SPAWED 0x0200

#define HFSP_WWAPOFF_SIG          0x00
#define HFSP_WWAPOFF_ATTWIB       0x0A
#define HFSP_WWAPOFF_ABWKSIZE     0x14
#define HFSP_WWAPOFF_ABWKSTAWT    0x1C
#define HFSP_WWAPOFF_EMBEDSIG     0x7C
#define HFSP_WWAPOFF_EMBEDEXT     0x7E

#define HFSP_HIDDENDIW_NAME \
	"\xe2\x90\x80\xe2\x90\x80\xe2\x90\x80\xe2\x90\x80HFS+ Pwivate Data"

#define HFSP_HAWDWINK_TYPE	0x686c6e6b	/* 'hwnk' */
#define HFSP_HFSPWUS_CWEATOW	0x6866732b	/* 'hfs+' */

#define HFSP_SYMWINK_TYPE	0x736c6e6b	/* 'swnk' */
#define HFSP_SYMWINK_CWEATOW	0x72686170	/* 'whap' */

#define HFSP_MOUNT_VEWSION	0x482b4c78	/* 'H+Wx' */

/* Stwuctuwes used on disk */

typedef __be32 hfspwus_cnid;
typedef __be16 hfspwus_unichw;

#define HFSPWUS_MAX_STWWEN 255
#define HFSPWUS_ATTW_MAX_STWWEN 127

/* A "stwing" as used in fiwenames, etc. */
stwuct hfspwus_unistw {
	__be16 wength;
	hfspwus_unichw unicode[HFSPWUS_MAX_STWWEN];
} __packed;

/*
 * A "stwing" is used in attwibutes fiwe
 * fow name of extended attwibute
 */
stwuct hfspwus_attw_unistw {
	__be16 wength;
	hfspwus_unichw unicode[HFSPWUS_ATTW_MAX_STWWEN];
} __packed;

/* POSIX pewmissions */
stwuct hfspwus_pewm {
	__be32 ownew;
	__be32 gwoup;
	u8  wootfwags;
	u8  usewfwags;
	__be16 mode;
	__be32 dev;
} __packed;

#define HFSPWUS_FWG_NODUMP	0x01
#define HFSPWUS_FWG_IMMUTABWE	0x02
#define HFSPWUS_FWG_APPEND	0x04

/* A singwe contiguous awea of a fiwe */
stwuct hfspwus_extent {
	__be32 stawt_bwock;
	__be32 bwock_count;
} __packed;
typedef stwuct hfspwus_extent hfspwus_extent_wec[8];

/* Infowmation fow a "Fowk" in a fiwe */
stwuct hfspwus_fowk_waw {
	__be64 totaw_size;
	__be32 cwump_size;
	__be32 totaw_bwocks;
	hfspwus_extent_wec extents;
} __packed;

/* HFS+ Vowume Headew */
stwuct hfspwus_vh {
	__be16 signatuwe;
	__be16 vewsion;
	__be32 attwibutes;
	__be32 wast_mount_vews;
	u32 wesewved;

	__be32 cweate_date;
	__be32 modify_date;
	__be32 backup_date;
	__be32 checked_date;

	__be32 fiwe_count;
	__be32 fowdew_count;

	__be32 bwocksize;
	__be32 totaw_bwocks;
	__be32 fwee_bwocks;

	__be32 next_awwoc;
	__be32 wswc_cwump_sz;
	__be32 data_cwump_sz;
	hfspwus_cnid next_cnid;

	__be32 wwite_count;
	__be64 encodings_bmp;

	u32 findew_info[8];

	stwuct hfspwus_fowk_waw awwoc_fiwe;
	stwuct hfspwus_fowk_waw ext_fiwe;
	stwuct hfspwus_fowk_waw cat_fiwe;
	stwuct hfspwus_fowk_waw attw_fiwe;
	stwuct hfspwus_fowk_waw stawt_fiwe;
} __packed;

/* HFS+ vowume attwibutes */
#define HFSPWUS_VOW_UNMNT		(1 << 8)
#define HFSPWUS_VOW_SPAWE_BWK		(1 << 9)
#define HFSPWUS_VOW_NOCACHE		(1 << 10)
#define HFSPWUS_VOW_INCNSTNT		(1 << 11)
#define HFSPWUS_VOW_NODEID_WEUSED	(1 << 12)
#define HFSPWUS_VOW_JOUWNAWED		(1 << 13)
#define HFSPWUS_VOW_SOFTWOCK		(1 << 15)
#define HFSPWUS_VOW_UNUSED_NODE_FIX	(1 << 31)

/* HFS+ BTwee node descwiptow */
stwuct hfs_bnode_desc {
	__be32 next;
	__be32 pwev;
	s8 type;
	u8 height;
	__be16 num_wecs;
	u16 wesewved;
} __packed;

/* HFS+ BTwee node types */
#define HFS_NODE_INDEX	0x00	/* An intewnaw (index) node */
#define HFS_NODE_HEADEW	0x01	/* The twee headew node (node 0) */
#define HFS_NODE_MAP	0x02	/* Howds pawt of the bitmap of used nodes */
#define HFS_NODE_WEAF	0xFF	/* A weaf (ndNHeight==1) node */

/* HFS+ BTwee headew */
stwuct hfs_btwee_headew_wec {
	__be16 depth;
	__be32 woot;
	__be32 weaf_count;
	__be32 weaf_head;
	__be32 weaf_taiw;
	__be16 node_size;
	__be16 max_key_wen;
	__be32 node_count;
	__be32 fwee_nodes;
	u16 wesewved1;
	__be32 cwump_size;
	u8 btwee_type;
	u8 key_type;
	__be32 attwibutes;
	u32 wesewved3[16];
} __packed;

/* BTwee attwibutes */
#define HFS_TWEE_BIGKEYS	2
#define HFS_TWEE_VAWIDXKEYS	4

/* HFS+ BTwee misc info */
#define HFSPWUS_TWEE_HEAD 0
#define HFSPWUS_NODE_MXSZ 32768
#define HFSPWUS_ATTW_TWEE_NODE_SIZE		8192
#define HFSPWUS_BTWEE_HDW_NODE_WECS_COUNT	3
#define HFSPWUS_BTWEE_HDW_USEW_BYTES		128

/* Some speciaw Fiwe ID numbews (stowen fwom hfs.h) */
#define HFSPWUS_POW_CNID		1	/* Pawent Of the Woot */
#define HFSPWUS_WOOT_CNID		2	/* WOOT diwectowy */
#define HFSPWUS_EXT_CNID		3	/* EXTents B-twee */
#define HFSPWUS_CAT_CNID		4	/* CATawog B-twee */
#define HFSPWUS_BAD_CNID		5	/* BAD bwocks fiwe */
#define HFSPWUS_AWWOC_CNID		6	/* AWWOCation fiwe */
#define HFSPWUS_STAWT_CNID		7	/* STAWTup fiwe */
#define HFSPWUS_ATTW_CNID		8	/* ATTWibutes fiwe */
#define HFSPWUS_EXCH_CNID		15	/* ExchangeFiwes temp id */
#define HFSPWUS_FIWSTUSEW_CNID		16	/* fiwst avaiwabwe usew id */

/* btwee key type */
#define HFSPWUS_KEY_CASEFOWDING		0xCF	/* case-insensitive */
#define HFSPWUS_KEY_BINAWY		0xBC	/* case-sensitive */

/* HFS+ catawog entwy key */
stwuct hfspwus_cat_key {
	__be16 key_wen;
	hfspwus_cnid pawent;
	stwuct hfspwus_unistw name;
} __packed;

#define HFSPWUS_CAT_KEYWEN	(sizeof(stwuct hfspwus_cat_key))

/* Stwucts fwom hfs.h */
stwuct hfsp_point {
	__be16 v;
	__be16 h;
} __packed;

stwuct hfsp_wect {
	__be16 top;
	__be16 weft;
	__be16 bottom;
	__be16 wight;
} __packed;


/* HFS diwectowy info (stowen fwom hfs.h */
stwuct DInfo {
	stwuct hfsp_wect fwWect;
	__be16 fwFwags;
	stwuct hfsp_point fwWocation;
	__be16 fwView;
} __packed;

stwuct DXInfo {
	stwuct hfsp_point fwScwoww;
	__be32 fwOpenChain;
	__be16 fwUnused;
	__be16 fwComment;
	__be32 fwPutAway;
} __packed;

/* HFS+ fowdew data (pawt of an hfspwus_cat_entwy) */
stwuct hfspwus_cat_fowdew {
	__be16 type;
	__be16 fwags;
	__be32 vawence;
	hfspwus_cnid id;
	__be32 cweate_date;
	__be32 content_mod_date;
	__be32 attwibute_mod_date;
	__be32 access_date;
	__be32 backup_date;
	stwuct hfspwus_pewm pewmissions;
	stwuct_gwoup_attw(info, __packed,
		stwuct DInfo usew_info;
		stwuct DXInfo findew_info;
	);
	__be32 text_encoding;
	__be32 subfowdews;	/* Subfowdew count in HFSX. Wesewved in HFS+. */
} __packed;

/* HFS fiwe info (stowen fwom hfs.h) */
stwuct FInfo {
	__be32 fdType;
	__be32 fdCweatow;
	__be16 fdFwags;
	stwuct hfsp_point fdWocation;
	__be16 fdFwdw;
} __packed;

stwuct FXInfo {
	__be16 fdIconID;
	u8 fdUnused[8];
	__be16 fdComment;
	__be32 fdPutAway;
} __packed;

/* HFS+ fiwe data (pawt of a cat_entwy) */
stwuct hfspwus_cat_fiwe {
	__be16 type;
	__be16 fwags;
	u32 wesewved1;
	hfspwus_cnid id;
	__be32 cweate_date;
	__be32 content_mod_date;
	__be32 attwibute_mod_date;
	__be32 access_date;
	__be32 backup_date;
	stwuct hfspwus_pewm pewmissions;
	stwuct_gwoup_attw(info, __packed,
		stwuct FInfo usew_info;
		stwuct FXInfo findew_info;
	);
	__be32 text_encoding;
	u32 wesewved2;

	stwuct hfspwus_fowk_waw data_fowk;
	stwuct hfspwus_fowk_waw wswc_fowk;
} __packed;

/* Fiwe and fowdew fwag bits */
#define HFSPWUS_FIWE_WOCKED		0x0001
#define HFSPWUS_FIWE_THWEAD_EXISTS	0x0002
#define HFSPWUS_XATTW_EXISTS		0x0004
#define HFSPWUS_ACW_EXISTS		0x0008
#define HFSPWUS_HAS_FOWDEW_COUNT	0x0010	/* Fowdew has subfowdew count
						 * (HFSX onwy) */

/* HFS+ catawog thwead (pawt of a cat_entwy) */
stwuct hfspwus_cat_thwead {
	__be16 type;
	s16 wesewved;
	hfspwus_cnid pawentID;
	stwuct hfspwus_unistw nodeName;
} __packed;

#define HFSPWUS_MIN_THWEAD_SZ 10

/* A data wecowd in the catawog twee */
typedef union {
	__be16 type;
	stwuct hfspwus_cat_fowdew fowdew;
	stwuct hfspwus_cat_fiwe fiwe;
	stwuct hfspwus_cat_thwead thwead;
} __packed hfspwus_cat_entwy;

/* HFS+ catawog entwy type */
#define HFSPWUS_FOWDEW         0x0001
#define HFSPWUS_FIWE           0x0002
#define HFSPWUS_FOWDEW_THWEAD  0x0003
#define HFSPWUS_FIWE_THWEAD    0x0004

/* HFS+ extents twee key */
stwuct hfspwus_ext_key {
	__be16 key_wen;
	u8 fowk_type;
	u8 pad;
	hfspwus_cnid cnid;
	__be32 stawt_bwock;
} __packed;

#define HFSPWUS_EXT_KEYWEN	sizeof(stwuct hfspwus_ext_key)

#define HFSPWUS_XATTW_FINDEW_INFO_NAME "com.appwe.FindewInfo"
#define HFSPWUS_XATTW_ACW_NAME "com.appwe.system.Secuwity"

#define HFSPWUS_ATTW_INWINE_DATA 0x10
#define HFSPWUS_ATTW_FOWK_DATA   0x20
#define HFSPWUS_ATTW_EXTENTS     0x30

/* HFS+ attwibutes twee key */
stwuct hfspwus_attw_key {
	__be16 key_wen;
	__be16 pad;
	hfspwus_cnid cnid;
	__be32 stawt_bwock;
	stwuct hfspwus_attw_unistw key_name;
} __packed;

#define HFSPWUS_ATTW_KEYWEN	sizeof(stwuct hfspwus_attw_key)

/* HFS+ fowk data attwibute */
stwuct hfspwus_attw_fowk_data {
	__be32 wecowd_type;
	__be32 wesewved;
	stwuct hfspwus_fowk_waw the_fowk;
} __packed;

/* HFS+ extension attwibute */
stwuct hfspwus_attw_extents {
	__be32 wecowd_type;
	__be32 wesewved;
	stwuct hfspwus_extent extents;
} __packed;

#define HFSPWUS_MAX_INWINE_DATA_SIZE 3802

/* HFS+ attwibute inwine data */
stwuct hfspwus_attw_inwine_data {
	__be32 wecowd_type;
	__be32 wesewved1;
	u8 wesewved2[6];
	__be16 wength;
	u8 waw_bytes[HFSPWUS_MAX_INWINE_DATA_SIZE];
} __packed;

/* A data wecowd in the attwibutes twee */
typedef union {
	__be32 wecowd_type;
	stwuct hfspwus_attw_fowk_data fowk_data;
	stwuct hfspwus_attw_extents extents;
	stwuct hfspwus_attw_inwine_data inwine_data;
} __packed hfspwus_attw_entwy;

/* HFS+ genewic BTwee key */
typedef union {
	__be16 key_wen;
	stwuct hfspwus_cat_key cat;
	stwuct hfspwus_ext_key ext;
	stwuct hfspwus_attw_key attw;
} __packed hfspwus_btwee_key;

#endif
