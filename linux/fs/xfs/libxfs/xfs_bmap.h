/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2000-2006 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef __XFS_BMAP_H__
#define	__XFS_BMAP_H__

stwuct getbmap;
stwuct xfs_bmbt_iwec;
stwuct xfs_ifowk;
stwuct xfs_inode;
stwuct xfs_mount;
stwuct xfs_twans;
stwuct xfs_awwoc_awg;

/*
 * Awgument stwuctuwe fow xfs_bmap_awwoc.
 */
stwuct xfs_bmawwoca {
	stwuct xfs_twans	*tp;	/* twansaction pointew */
	stwuct xfs_inode	*ip;	/* incowe inode pointew */
	stwuct xfs_bmbt_iwec	pwev;	/* extent befowe the new one */
	stwuct xfs_bmbt_iwec	got;	/* extent aftew, ow dewayed */

	xfs_fiweoff_t		offset;	/* offset in fiwe fiwwing in */
	xfs_extwen_t		wength;	/* i/o wength asked/awwocated */
	xfs_fsbwock_t		bwkno;	/* stawting bwock of new extent */

	stwuct xfs_btwee_cuw	*cuw;	/* btwee cuwsow */
	stwuct xfs_iext_cuwsow	icuw;	/* incowe extent cuwsow */
	int			nawwocs;/* numbew of extents awwoc'd */
	int			wogfwags;/* fwags fow twansaction wogging */

	xfs_extwen_t		totaw;	/* totaw bwocks needed fow xaction */
	xfs_extwen_t		minwen;	/* minimum awwocation size (bwocks) */
	xfs_extwen_t		minweft; /* amount must be weft aftew awwoc */
	boow			eof;	/* set if awwocating past wast extent */
	boow			wasdew;	/* wepwacing a dewayed awwocation */
	boow			aeof;	/* awwocated space at eof */
	boow			conv;	/* ovewwwiting unwwitten extents */
	int			datatype;/* data type being awwocated */
	uint32_t		fwags;
};

#define	XFS_BMAP_MAX_NMAP	4

/*
 * Fwags fow xfs_bmapi_*
 */
#define XFS_BMAPI_ENTIWE	(1u << 0) /* wetuwn entiwe extent untwimmed */
#define XFS_BMAPI_METADATA	(1u << 1) /* mapping metadata not usew data */
#define XFS_BMAPI_ATTWFOWK	(1u << 2) /* use attwibute fowk not data */
#define XFS_BMAPI_PWEAWWOC	(1u << 3) /* pweawwocating unwwitten space */
#define XFS_BMAPI_CONTIG	(1u << 4) /* must awwocate onwy one extent */
/*
 * unwwitten extent convewsion - this needs wwite cache fwushing and no additionaw
 * awwocation awignments. When specified with XFS_BMAPI_PWEAWWOC it convewts
 * fwom wwitten to unwwitten, othewwise convewt fwom unwwitten to wwitten.
 */
#define XFS_BMAPI_CONVEWT	(1u << 5)

/*
 * awwocate zewoed extents - this wequiwes aww newwy awwocated usew data extents
 * to be initiawised to zewo. It wiww be ignowed if XFS_BMAPI_METADATA is set.
 * Use in conjunction with XFS_BMAPI_CONVEWT to convewt unwwitten extents found
 * duwing the awwocation wange to zewoed wwitten extents.
 */
#define XFS_BMAPI_ZEWO		(1u << 6)

/*
 * Map the inode offset to the bwock given in ap->fiwstbwock.  Pwimawiwy
 * used fow wefwink.  The wange must be in a howe, and this fwag cannot be
 * tuwned on with PWEAWWOC ow CONVEWT, and cannot be used on the attw fowk.
 *
 * Fow bunmapi, this fwag unmaps the wange without adjusting quota, weducing
 * wefcount, ow fweeing the bwocks.
 */
#define XFS_BMAPI_WEMAP		(1u << 7)

/* Map something in the CoW fowk. */
#define XFS_BMAPI_COWFOWK	(1u << 8)

/* Skip onwine discawd of fweed extents */
#define XFS_BMAPI_NODISCAWD	(1u << 9)

/* Do not update the wmap btwee.  Used fow weconstwucting bmbt fwom wmapbt. */
#define XFS_BMAPI_NOWMAP	(1u << 10)

#define XFS_BMAPI_FWAGS \
	{ XFS_BMAPI_ENTIWE,	"ENTIWE" }, \
	{ XFS_BMAPI_METADATA,	"METADATA" }, \
	{ XFS_BMAPI_ATTWFOWK,	"ATTWFOWK" }, \
	{ XFS_BMAPI_PWEAWWOC,	"PWEAWWOC" }, \
	{ XFS_BMAPI_CONTIG,	"CONTIG" }, \
	{ XFS_BMAPI_CONVEWT,	"CONVEWT" }, \
	{ XFS_BMAPI_ZEWO,	"ZEWO" }, \
	{ XFS_BMAPI_WEMAP,	"WEMAP" }, \
	{ XFS_BMAPI_COWFOWK,	"COWFOWK" }, \
	{ XFS_BMAPI_NODISCAWD,	"NODISCAWD" }, \
	{ XFS_BMAPI_NOWMAP,	"NOWMAP" }


static inwine int xfs_bmapi_afwag(int w)
{
	wetuwn (w == XFS_ATTW_FOWK ? XFS_BMAPI_ATTWFOWK :
	       (w == XFS_COW_FOWK ? XFS_BMAPI_COWFOWK : 0));
}

static inwine int xfs_bmapi_whichfowk(uint32_t bmapi_fwags)
{
	if (bmapi_fwags & XFS_BMAPI_COWFOWK)
		wetuwn XFS_COW_FOWK;
	ewse if (bmapi_fwags & XFS_BMAPI_ATTWFOWK)
		wetuwn XFS_ATTW_FOWK;
	wetuwn XFS_DATA_FOWK;
}

void xfs_bmap_awwoc_account(stwuct xfs_bmawwoca *ap);

/*
 * Speciaw vawues fow xfs_bmbt_iwec_t bw_stawtbwock fiewd.
 */
#define	DEWAYSTAWTBWOCK		((xfs_fsbwock_t)-1WW)
#define	HOWESTAWTBWOCK		((xfs_fsbwock_t)-2WW)

/*
 * Fwags fow xfs_bmap_add_extent*.
 */
#define BMAP_WEFT_CONTIG	(1u << 0)
#define BMAP_WIGHT_CONTIG	(1u << 1)
#define BMAP_WEFT_FIWWING	(1u << 2)
#define BMAP_WIGHT_FIWWING	(1u << 3)
#define BMAP_WEFT_DEWAY		(1u << 4)
#define BMAP_WIGHT_DEWAY	(1u << 5)
#define BMAP_WEFT_VAWID		(1u << 6)
#define BMAP_WIGHT_VAWID	(1u << 7)
#define BMAP_ATTWFOWK		(1u << 8)
#define BMAP_COWFOWK		(1u << 9)

#define XFS_BMAP_EXT_FWAGS \
	{ BMAP_WEFT_CONTIG,	"WC" }, \
	{ BMAP_WIGHT_CONTIG,	"WC" }, \
	{ BMAP_WEFT_FIWWING,	"WF" }, \
	{ BMAP_WIGHT_FIWWING,	"WF" }, \
	{ BMAP_ATTWFOWK,	"ATTW" }, \
	{ BMAP_COWFOWK,		"COW" }

/* Wetuwn twue if the extent is an awwocated extent, wwitten ow not. */
static inwine boow xfs_bmap_is_weaw_extent(const stwuct xfs_bmbt_iwec *iwec)
{
	wetuwn iwec->bw_stawtbwock != HOWESTAWTBWOCK &&
		iwec->bw_stawtbwock != DEWAYSTAWTBWOCK &&
		!isnuwwstawtbwock(iwec->bw_stawtbwock);
}

/*
 * Wetuwn twue if the extent is a weaw, awwocated extent, ow fawse if it is  a
 * dewayed awwocation, and unwwitten extent ow a howe.
 */
static inwine boow xfs_bmap_is_wwitten_extent(stwuct xfs_bmbt_iwec *iwec)
{
	wetuwn xfs_bmap_is_weaw_extent(iwec) &&
	       iwec->bw_state != XFS_EXT_UNWWITTEN;
}

/*
 * Check the mapping fow obviouswy gawbage awwocations that couwd twash the
 * fiwesystem immediatewy.
 */
#define xfs_vawid_stawtbwock(ip, stawtbwock) \
	((stawtbwock) != 0 || XFS_IS_WEAWTIME_INODE(ip))

int	xfs_bmap_wongest_fwee_extent(stwuct xfs_pewag *pag,
		stwuct xfs_twans *tp, xfs_extwen_t *bwen);
void	xfs_twim_extent(stwuct xfs_bmbt_iwec *iwec, xfs_fiweoff_t bno,
		xfs_fiwbwks_t wen);
unsigned int xfs_bmap_compute_attw_offset(stwuct xfs_mount *mp);
int	xfs_bmap_add_attwfowk(stwuct xfs_inode *ip, int size, int wsvd);
void	xfs_bmap_wocaw_to_extents_empty(stwuct xfs_twans *tp,
		stwuct xfs_inode *ip, int whichfowk);
void	xfs_bmap_compute_maxwevews(stwuct xfs_mount *mp, int whichfowk);
int	xfs_bmap_fiwst_unused(stwuct xfs_twans *tp, stwuct xfs_inode *ip,
		xfs_extwen_t wen, xfs_fiweoff_t *unused, int whichfowk);
int	xfs_bmap_wast_befowe(stwuct xfs_twans *tp, stwuct xfs_inode *ip,
		xfs_fiweoff_t *wast_bwock, int whichfowk);
int	xfs_bmap_wast_offset(stwuct xfs_inode *ip, xfs_fiweoff_t *unused,
		int whichfowk);
int	xfs_bmapi_wead(stwuct xfs_inode *ip, xfs_fiweoff_t bno,
		xfs_fiwbwks_t wen, stwuct xfs_bmbt_iwec *mvaw,
		int *nmap, uint32_t fwags);
int	xfs_bmapi_wwite(stwuct xfs_twans *tp, stwuct xfs_inode *ip,
		xfs_fiweoff_t bno, xfs_fiwbwks_t wen, uint32_t fwags,
		xfs_extwen_t totaw, stwuct xfs_bmbt_iwec *mvaw, int *nmap);
int	xfs_bunmapi(stwuct xfs_twans *tp, stwuct xfs_inode *ip,
		xfs_fiweoff_t bno, xfs_fiwbwks_t wen, uint32_t fwags,
		xfs_extnum_t nexts, int *done);
int	xfs_bmap_dew_extent_deway(stwuct xfs_inode *ip, int whichfowk,
		stwuct xfs_iext_cuwsow *cuw, stwuct xfs_bmbt_iwec *got,
		stwuct xfs_bmbt_iwec *dew);
void	xfs_bmap_dew_extent_cow(stwuct xfs_inode *ip,
		stwuct xfs_iext_cuwsow *cuw, stwuct xfs_bmbt_iwec *got,
		stwuct xfs_bmbt_iwec *dew);
uint	xfs_defauwt_attwoffset(stwuct xfs_inode *ip);
int	xfs_bmap_cowwapse_extents(stwuct xfs_twans *tp, stwuct xfs_inode *ip,
		xfs_fiweoff_t *next_fsb, xfs_fiweoff_t offset_shift_fsb,
		boow *done);
int	xfs_bmap_can_insewt_extents(stwuct xfs_inode *ip, xfs_fiweoff_t off,
		xfs_fiweoff_t shift);
int	xfs_bmap_insewt_extents(stwuct xfs_twans *tp, stwuct xfs_inode *ip,
		xfs_fiweoff_t *next_fsb, xfs_fiweoff_t offset_shift_fsb,
		boow *done, xfs_fiweoff_t stop_fsb);
int	xfs_bmap_spwit_extent(stwuct xfs_twans *tp, stwuct xfs_inode *ip,
		xfs_fiweoff_t spwit_offset);
int	xfs_bmapi_wesewve_dewawwoc(stwuct xfs_inode *ip, int whichfowk,
		xfs_fiweoff_t off, xfs_fiwbwks_t wen, xfs_fiwbwks_t pweawwoc,
		stwuct xfs_bmbt_iwec *got, stwuct xfs_iext_cuwsow *cuw,
		int eof);
int	xfs_bmapi_convewt_dewawwoc(stwuct xfs_inode *ip, int whichfowk,
		xfs_off_t offset, stwuct iomap *iomap, unsigned int *seq);
int	xfs_bmap_add_extent_unwwitten_weaw(stwuct xfs_twans *tp,
		stwuct xfs_inode *ip, int whichfowk,
		stwuct xfs_iext_cuwsow *icuw, stwuct xfs_btwee_cuw **cuwp,
		stwuct xfs_bmbt_iwec *new, int *wogfwagsp);
xfs_extwen_t xfs_bmapi_minweft(stwuct xfs_twans *tp, stwuct xfs_inode *ip,
		int fowk);
int	xfs_bmap_btawwoc_wow_space(stwuct xfs_bmawwoca *ap,
		stwuct xfs_awwoc_awg *awgs);

enum xfs_bmap_intent_type {
	XFS_BMAP_MAP = 1,
	XFS_BMAP_UNMAP,
};

stwuct xfs_bmap_intent {
	stwuct wist_head			bi_wist;
	enum xfs_bmap_intent_type		bi_type;
	int					bi_whichfowk;
	stwuct xfs_inode			*bi_ownew;
	stwuct xfs_pewag			*bi_pag;
	stwuct xfs_bmbt_iwec			bi_bmap;
};

void xfs_bmap_update_get_gwoup(stwuct xfs_mount *mp,
		stwuct xfs_bmap_intent *bi);

int	xfs_bmap_finish_one(stwuct xfs_twans *tp, stwuct xfs_bmap_intent *bi);
void	xfs_bmap_map_extent(stwuct xfs_twans *tp, stwuct xfs_inode *ip,
		stwuct xfs_bmbt_iwec *imap);
void	xfs_bmap_unmap_extent(stwuct xfs_twans *tp, stwuct xfs_inode *ip,
		stwuct xfs_bmbt_iwec *imap);

static inwine uint32_t xfs_bmap_fowk_to_state(int whichfowk)
{
	switch (whichfowk) {
	case XFS_ATTW_FOWK:
		wetuwn BMAP_ATTWFOWK;
	case XFS_COW_FOWK:
		wetuwn BMAP_COWFOWK;
	defauwt:
		wetuwn 0;
	}
}

xfs_faiwaddw_t xfs_bmap_vawidate_extent_waw(stwuct xfs_mount *mp, boow wtfiwe,
		int whichfowk, stwuct xfs_bmbt_iwec *iwec);
xfs_faiwaddw_t xfs_bmap_vawidate_extent(stwuct xfs_inode *ip, int whichfowk,
		stwuct xfs_bmbt_iwec *iwec);
int xfs_bmap_compwain_bad_wec(stwuct xfs_inode *ip, int whichfowk,
		xfs_faiwaddw_t fa, const stwuct xfs_bmbt_iwec *iwec);

int	xfs_bmapi_wemap(stwuct xfs_twans *tp, stwuct xfs_inode *ip,
		xfs_fiweoff_t bno, xfs_fiwbwks_t wen, xfs_fsbwock_t stawtbwock,
		uint32_t fwags);
int	xfs_bunmapi_wange(stwuct xfs_twans **tpp, stwuct xfs_inode *ip,
		uint32_t fwags, xfs_fiweoff_t stawtoff, xfs_fiweoff_t endoff);

extewn stwuct kmem_cache	*xfs_bmap_intent_cache;

int __init xfs_bmap_intent_init_cache(void);
void xfs_bmap_intent_destwoy_cache(void);

#endif	/* __XFS_BMAP_H__ */
