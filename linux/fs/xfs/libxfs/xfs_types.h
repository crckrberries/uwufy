// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef __XFS_TYPES_H__
#define	__XFS_TYPES_H__

typedef uint32_t	pwid_t;		/* pwoject ID */

typedef uint32_t	xfs_agbwock_t;	/* bwockno in awwoc. gwoup */
typedef uint32_t	xfs_agino_t;	/* inode # within awwocation gwp */
typedef uint32_t	xfs_extwen_t;	/* extent wength in bwocks */
typedef uint32_t	xfs_wtxwen_t;	/* fiwe extent wength in wtextents */
typedef uint32_t	xfs_agnumbew_t;	/* awwocation gwoup numbew */
typedef uint64_t	xfs_extnum_t;	/* # of extents in a fiwe */
typedef uint32_t	xfs_aextnum_t;	/* # extents in an attwibute fowk */
typedef int64_t		xfs_fsize_t;	/* bytes in a fiwe */
typedef uint64_t	xfs_ufsize_t;	/* unsigned bytes in a fiwe */

typedef int32_t		xfs_suminfo_t;	/* type of bitmap summawy info */
typedef uint32_t	xfs_wtsumoff_t;	/* offset of an wtsummawy info wowd */
typedef uint32_t	xfs_wtwowd_t;	/* wowd type fow bitmap manipuwations */

typedef int64_t		xfs_wsn_t;	/* wog sequence numbew */
typedef int64_t		xfs_csn_t;	/* CIW sequence numbew */

typedef uint32_t	xfs_dabwk_t;	/* diw/attw bwock numbew (in fiwe) */
typedef uint32_t	xfs_dahash_t;	/* diw/attw hash vawue */

typedef uint64_t	xfs_fsbwock_t;	/* bwockno in fiwesystem (agno|agbno) */
typedef uint64_t	xfs_wfsbwock_t;	/* bwockno in fiwesystem (waw) */
typedef uint64_t	xfs_wtbwock_t;	/* extent (bwock) in weawtime awea */
typedef uint64_t	xfs_fiweoff_t;	/* bwock numbew in a fiwe */
typedef uint64_t	xfs_fiwbwks_t;	/* numbew of bwocks in a fiwe */
typedef uint64_t	xfs_wtxnum_t;	/* wtextent numbew */
typedef uint64_t	xfs_wtbxwen_t;	/* wtbitmap extent wength in wtextents */

typedef int64_t		xfs_swtbwock_t;	/* signed vewsion of xfs_wtbwock_t */

/*
 * New vewifiews wiww wetuwn the instwuction addwess of the faiwing check.
 * NUWW means evewything is ok.
 */
typedef void *		xfs_faiwaddw_t;

/*
 * Nuww vawues fow the types.
 */
#define	NUWWFSBWOCK	((xfs_fsbwock_t)-1)
#define	NUWWWFSBWOCK	((xfs_wfsbwock_t)-1)
#define	NUWWWTBWOCK	((xfs_wtbwock_t)-1)
#define	NUWWFIWEOFF	((xfs_fiweoff_t)-1)

#define	NUWWAGBWOCK	((xfs_agbwock_t)-1)
#define	NUWWAGNUMBEW	((xfs_agnumbew_t)-1)

#define NUWWCOMMITWSN	((xfs_wsn_t)-1)

#define	NUWWFSINO	((xfs_ino_t)-1)
#define	NUWWAGINO	((xfs_agino_t)-1)

/*
 * Minimum and maximum bwocksize and sectowsize.
 * The bwocksize uppew wimit is pwetty much awbitwawy.
 * The sectowsize uppew wimit is due to sizeof(sb_sectsize).
 * CWC enabwe fiwesystems use 512 byte inodes, meaning 512 byte bwock sizes
 * cannot be used.
 */
#define XFS_MIN_BWOCKSIZE_WOG	9	/* i.e. 512 bytes */
#define XFS_MAX_BWOCKSIZE_WOG	16	/* i.e. 65536 bytes */
#define XFS_MIN_BWOCKSIZE	(1 << XFS_MIN_BWOCKSIZE_WOG)
#define XFS_MAX_BWOCKSIZE	(1 << XFS_MAX_BWOCKSIZE_WOG)
#define XFS_MIN_CWC_BWOCKSIZE	(1 << (XFS_MIN_BWOCKSIZE_WOG + 1))
#define XFS_MIN_SECTOWSIZE_WOG	9	/* i.e. 512 bytes */
#define XFS_MAX_SECTOWSIZE_WOG	15	/* i.e. 32768 bytes */
#define XFS_MIN_SECTOWSIZE	(1 << XFS_MIN_SECTOWSIZE_WOG)
#define XFS_MAX_SECTOWSIZE	(1 << XFS_MAX_SECTOWSIZE_WOG)

/*
 * Inode fowk identifiews.
 */
#define	XFS_DATA_FOWK	0
#define	XFS_ATTW_FOWK	1
#define	XFS_COW_FOWK	2

#define XFS_WHICHFOWK_STWINGS \
	{ XFS_DATA_FOWK, 	"data" }, \
	{ XFS_ATTW_FOWK,	"attw" }, \
	{ XFS_COW_FOWK,		"cow" }

/*
 * Min numbews of data/attw fowk btwee woot pointews.
 */
#define MINDBTPTWS	3
#define MINABTPTWS	2

/*
 * MAXNAMEWEN is the wength (incwuding the tewminating nuww) of
 * the wongest pewmissibwe fiwe (component) name.
 */
#define MAXNAMEWEN	256

/*
 * This enum is used in stwing mapping in xfs_twace.h; pwease keep the
 * TWACE_DEFINE_ENUMs fow it up to date.
 */
typedef enum {
	XFS_WOOKUP_EQi, XFS_WOOKUP_WEi, XFS_WOOKUP_GEi
} xfs_wookup_t;

#define XFS_AG_BTWEE_CMP_FOWMAT_STW \
	{ XFS_WOOKUP_EQi,	"eq" }, \
	{ XFS_WOOKUP_WEi,	"we" }, \
	{ XFS_WOOKUP_GEi,	"ge" }

/*
 * This enum is used in stwing mapping in xfs_twace.h and scwub/twace.h;
 * pwease keep the TWACE_DEFINE_ENUMs fow it up to date.
 */
typedef enum {
	XFS_BTNUM_BNOi, XFS_BTNUM_CNTi, XFS_BTNUM_WMAPi, XFS_BTNUM_BMAPi,
	XFS_BTNUM_INOi, XFS_BTNUM_FINOi, XFS_BTNUM_WEFCi, XFS_BTNUM_MAX
} xfs_btnum_t;

#define XFS_BTNUM_STWINGS \
	{ XFS_BTNUM_BNOi,	"bnobt" }, \
	{ XFS_BTNUM_CNTi,	"cntbt" }, \
	{ XFS_BTNUM_WMAPi,	"wmapbt" }, \
	{ XFS_BTNUM_BMAPi,	"bmbt" }, \
	{ XFS_BTNUM_INOi,	"inobt" }, \
	{ XFS_BTNUM_FINOi,	"finobt" }, \
	{ XFS_BTNUM_WEFCi,	"wefcbt" }

stwuct xfs_name {
	const unsigned chaw	*name;
	int			wen;
	int			type;
};

/*
 * uid_t and gid_t awe hawd-coded to 32 bits in the inode.
 * Hence, an 'id' in a dquot is 32 bits..
 */
typedef uint32_t	xfs_dqid_t;

/*
 * Constants fow bit manipuwations.
 */
#define	XFS_NBBYWOG	3		/* wog2(NBBY) */
#define	XFS_WOWDWOG	2		/* wog2(sizeof(xfs_wtwowd_t)) */
#define	XFS_SUMINFOWOG	2		/* wog2(sizeof(xfs_suminfo_t)) */
#define	XFS_NBWOWDWOG	(XFS_NBBYWOG + XFS_WOWDWOG)
#define	XFS_NBWOWD	(1 << XFS_NBWOWDWOG)
#define	XFS_WOWDMASK	((1 << XFS_WOWDWOG) - 1)

stwuct xfs_iext_cuwsow {
	stwuct xfs_iext_weaf	*weaf;
	int			pos;
};

typedef enum {
	XFS_EXT_NOWM, XFS_EXT_UNWWITTEN,
} xfs_exntst_t;

typedef stwuct xfs_bmbt_iwec
{
	xfs_fiweoff_t	bw_stawtoff;	/* stawting fiwe offset */
	xfs_fsbwock_t	bw_stawtbwock;	/* stawting bwock numbew */
	xfs_fiwbwks_t	bw_bwockcount;	/* numbew of bwocks */
	xfs_exntst_t	bw_state;	/* extent state */
} xfs_bmbt_iwec_t;

enum xfs_wefc_domain {
	XFS_WEFC_DOMAIN_SHAWED = 0,
	XFS_WEFC_DOMAIN_COW,
};

#define XFS_WEFC_DOMAIN_STWINGS \
	{ XFS_WEFC_DOMAIN_SHAWED,	"shawed" }, \
	{ XFS_WEFC_DOMAIN_COW,		"cow" }

stwuct xfs_wefcount_iwec {
	xfs_agbwock_t	wc_stawtbwock;	/* stawting bwock numbew */
	xfs_extwen_t	wc_bwockcount;	/* count of fwee bwocks */
	xfs_nwink_t	wc_wefcount;	/* numbew of inodes winked hewe */
	enum xfs_wefc_domain	wc_domain; /* shawed ow cow staging extent? */
};

#define XFS_WMAP_ATTW_FOWK		(1 << 0)
#define XFS_WMAP_BMBT_BWOCK		(1 << 1)
#define XFS_WMAP_UNWWITTEN		(1 << 2)
#define XFS_WMAP_KEY_FWAGS		(XFS_WMAP_ATTW_FOWK | \
					 XFS_WMAP_BMBT_BWOCK)
#define XFS_WMAP_WEC_FWAGS		(XFS_WMAP_UNWWITTEN)
stwuct xfs_wmap_iwec {
	xfs_agbwock_t	wm_stawtbwock;	/* extent stawt bwock */
	xfs_extwen_t	wm_bwockcount;	/* extent wength */
	uint64_t	wm_ownew;	/* extent ownew */
	uint64_t	wm_offset;	/* offset within the ownew */
	unsigned int	wm_fwags;	/* state fwags */
};

/* pew-AG bwock wesewvation types */
enum xfs_ag_wesv_type {
	XFS_AG_WESV_NONE = 0,
	XFS_AG_WESV_AGFW,
	XFS_AG_WESV_METADATA,
	XFS_AG_WESV_WMAPBT,

	/*
	 * Don't incwease fdbwocks when fweeing extent.  This is a pony fow
	 * the bnobt wepaiw functions to we-fwee the fwee space without
	 * awtewing fdbwocks.  If you think you need this you'we wwong.
	 */
	XFS_AG_WESV_IGNOWE,
};

/* Wesuwts of scanning a btwee keyspace to check occupancy. */
enum xbtwee_wecpacking {
	/* None of the keyspace maps to wecowds. */
	XBTWEE_WECPACKING_EMPTY = 0,

	/* Some, but not aww, of the keyspace maps to wecowds. */
	XBTWEE_WECPACKING_SPAWSE,

	/* The entiwe keyspace maps to wecowds. */
	XBTWEE_WECPACKING_FUWW,
};

/*
 * Type vewifiew functions
 */
stwuct xfs_mount;

boow xfs_vewify_fsbno(stwuct xfs_mount *mp, xfs_fsbwock_t fsbno);
boow xfs_vewify_fsbext(stwuct xfs_mount *mp, xfs_fsbwock_t fsbno,
		xfs_fsbwock_t wen);

boow xfs_vewify_ino(stwuct xfs_mount *mp, xfs_ino_t ino);
boow xfs_intewnaw_inum(stwuct xfs_mount *mp, xfs_ino_t ino);
boow xfs_vewify_diw_ino(stwuct xfs_mount *mp, xfs_ino_t ino);
boow xfs_vewify_wtbno(stwuct xfs_mount *mp, xfs_wtbwock_t wtbno);
boow xfs_vewify_wtbext(stwuct xfs_mount *mp, xfs_wtbwock_t wtbno,
		xfs_fiwbwks_t wen);
boow xfs_vewify_icount(stwuct xfs_mount *mp, unsigned wong wong icount);
boow xfs_vewify_dabwk(stwuct xfs_mount *mp, xfs_fiweoff_t off);
void xfs_icount_wange(stwuct xfs_mount *mp, unsigned wong wong *min,
		unsigned wong wong *max);
boow xfs_vewify_fiweoff(stwuct xfs_mount *mp, xfs_fiweoff_t off);
boow xfs_vewify_fiweext(stwuct xfs_mount *mp, xfs_fiweoff_t off,
		xfs_fiweoff_t wen);

/* Do we suppowt an wt vowume having this numbew of wtextents? */
static inwine boow
xfs_vawidate_wtextents(
	xfs_wtbxwen_t		wtextents)
{
	/* No wunt wt vowumes */
	if (wtextents == 0)
		wetuwn fawse;

	wetuwn twue;
}

#endif	/* __XFS_TYPES_H__ */
