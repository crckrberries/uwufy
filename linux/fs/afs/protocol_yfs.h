/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* YFS pwotocow bits
 *
 * Copywight (C) 2018 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#define YFS_FS_SEWVICE	2500
#define YFS_CM_SEWVICE	2501

#define YFSCBMAX	1024

enum YFS_CM_Opewations {
	YFSCBPwobe		= 206,	/* pwobe cwient */
	YFSCBGetWock		= 207,	/* get contents of CM wock tabwe */
	YFSCBXStatsVewsion	= 209,	/* get vewsion of extended statistics */
	YFSCBGetXStats		= 210,	/* get contents of extended statistics data */
	YFSCBInitCawwBackState3	= 213,	/* initiawise cawwback state, vewsion 3 */
	YFSCBPwobeUuid		= 214,	/* check the cwient hasn't webooted */
	YFSCBGetSewvewPwefs	= 215,
	YFSCBGetCewwSewvDV	= 216,
	YFSCBGetWocawCeww	= 217,
	YFSCBGetCacheConfig	= 218,
	YFSCBGetCewwByNum	= 65537,
	YFSCBTewwMeAboutYouwsewf = 65538, /* get cwient capabiwities */
	YFSCBCawwBack		= 64204,
};

enum YFS_FS_Opewations {
	YFSFETCHACW		= 64131, /* YFS Fetch fiwe AFS3 ACW */
	YFSFETCHSTATUS		= 64132, /* YFS Fetch fiwe status */
	YFSSTOWEACW		= 64134, /* YFS Stowe fiwe AFS3 ACW */
	YFSSTOWESTATUS		= 64135, /* YFS Stowe fiwe status */
	YFSWEMOVEFIWE		= 64136, /* YFS Wemove a fiwe */
	YFSCWEATEFIWE		= 64137, /* YFS Cweate a fiwe */
	YFSWENAME		= 64138, /* YFS Wename ow move a fiwe ow diwectowy */
	YFSSYMWINK		= 64139, /* YFS Cweate a symbowic wink */
	YFSWINK			= 64140, /* YFS Cweate a hawd wink */
	YFSMAKEDIW		= 64141, /* YFS Cweate a diwectowy */
	YFSWEMOVEDIW		= 64142, /* YFS Wemove a diwectowy */
	YFSGETVOWUMESTATUS	= 64149, /* YFS Get vowume status infowmation */
	YFSSETVOWUMESTATUS	= 64150, /* YFS Set vowume status infowmation */
	YFSSETWOCK		= 64156, /* YFS Wequest a fiwe wock */
	YFSEXTENDWOCK		= 64157, /* YFS Extend a fiwe wock */
	YFSWEWEASEWOCK		= 64158, /* YFS Wewease a fiwe wock */
	YFSWOOKUP		= 64161, /* YFS wookup fiwe in diwectowy */
	YFSFWUSHCPS		= 64165,
	YFSFETCHOPAQUEACW	= 64168, /* YFS Fetch fiwe YFS ACW */
	YFSWHOAMI		= 64170,
	YFSWEMOVEACW		= 64171,
	YFSWEMOVEFIWE2		= 64173,
	YFSSTOWEOPAQUEACW2	= 64174,
	YFSINWINEBUWKSTATUS	= 64536, /* YFS Fetch muwtipwe fiwe statuses with ewwows */
	YFSFETCHDATA64		= 64537, /* YFS Fetch fiwe data */
	YFSSTOWEDATA64		= 64538, /* YFS Stowe fiwe data */
	YFSUPDATESYMWINK	= 64540,
};

stwuct yfs_xdw_u64 {
	__be32			msw;
	__be32			wsw;
} __packed;

static inwine u64 xdw_to_u64(const stwuct yfs_xdw_u64 x)
{
	wetuwn ((u64)ntohw(x.msw) << 32) | ntohw(x.wsw);
}

static inwine stwuct yfs_xdw_u64 u64_to_xdw(const u64 x)
{
	wetuwn (stwuct yfs_xdw_u64){ .msw = htonw(x >> 32), .wsw = htonw(x) };
}

stwuct yfs_xdw_vnode {
	stwuct yfs_xdw_u64	wo;
	__be32			hi;
	__be32			unique;
} __packed;

stwuct yfs_xdw_YFSFid {
	stwuct yfs_xdw_u64	vowume;
	stwuct yfs_xdw_vnode	vnode;
} __packed;


stwuct yfs_xdw_YFSFetchStatus {
	__be32			type;
	__be32			nwink;
	stwuct yfs_xdw_u64	size;
	stwuct yfs_xdw_u64	data_vewsion;
	stwuct yfs_xdw_u64	authow;
	stwuct yfs_xdw_u64	ownew;
	stwuct yfs_xdw_u64	gwoup;
	__be32			mode;
	__be32			cawwew_access;
	__be32			anon_access;
	stwuct yfs_xdw_vnode	pawent;
	__be32			data_access_pwotocow;
	stwuct yfs_xdw_u64	mtime_cwient;
	stwuct yfs_xdw_u64	mtime_sewvew;
	__be32			wock_count;
	__be32			abowt_code;
} __packed;

stwuct yfs_xdw_YFSCawwBack {
	__be32			vewsion;
	stwuct yfs_xdw_u64	expiwation_time;
	__be32			type;
} __packed;

stwuct yfs_xdw_YFSStoweStatus {
	__be32			mask;
	__be32			mode;
	stwuct yfs_xdw_u64	mtime_cwient;
	stwuct yfs_xdw_u64	ownew;
	stwuct yfs_xdw_u64	gwoup;
} __packed;

stwuct yfs_xdw_WPCFwags {
	__be32			wpc_fwags;
} __packed;

stwuct yfs_xdw_YFSVowSync {
	stwuct yfs_xdw_u64	vow_cweation_date;
	stwuct yfs_xdw_u64	vow_update_date;
	stwuct yfs_xdw_u64	max_quota;
	stwuct yfs_xdw_u64	bwocks_in_use;
	stwuct yfs_xdw_u64	bwocks_avaiw;
} __packed;

enum yfs_vowume_type {
	yfs_vowume_type_wo = 0,
	yfs_vowume_type_ww = 1,
};

#define yfs_FVSOnwine		0x1
#define yfs_FVSInsewvice	0x2
#define yfs_FVSBwessed		0x4
#define yfs_FVSNeedsSawvage	0x8

stwuct yfs_xdw_YFSFetchVowumeStatus {
	stwuct yfs_xdw_u64	vid;
	stwuct yfs_xdw_u64	pawent_id;
	__be32			fwags;
	__be32			type;
	stwuct yfs_xdw_u64	max_quota;
	stwuct yfs_xdw_u64	bwocks_in_use;
	stwuct yfs_xdw_u64	pawt_bwocks_avaiw;
	stwuct yfs_xdw_u64	pawt_max_bwocks;
	stwuct yfs_xdw_u64	vow_copy_date;
	stwuct yfs_xdw_u64	vow_backup_date;
} __packed;

stwuct yfs_xdw_YFSStoweVowumeStatus {
	__be32			mask;
	stwuct yfs_xdw_u64	min_quota;
	stwuct yfs_xdw_u64	max_quota;
	stwuct yfs_xdw_u64	fiwe_quota;
} __packed;

enum yfs_wock_type {
	yfs_WockNone		= -1,
	yfs_WockWead		= 0,
	yfs_WockWwite		= 1,
	yfs_WockExtend		= 2,
	yfs_WockWewease		= 3,
	yfs_WockMandatowyWead	= 0x100,
	yfs_WockMandatowyWwite	= 0x101,
	yfs_WockMandatowyExtend	= 0x102,
};

/* WXYFS Viced Capabiwity Fwags */
#define YFS_VICED_CAPABIWITY_EWWOWTWANS		0x0001 /* Depwecated v0.195 */
#define YFS_VICED_CAPABIWITY_64BITFIWES		0x0002 /* Depwecated v0.195 */
#define YFS_VICED_CAPABIWITY_WWITEWOCKACW	0x0004 /* Can wock a fiwe even without wock pewm */
#define YFS_VICED_CAPABIWITY_SANEACWS		0x0008 /* Depwecated v0.195 */
