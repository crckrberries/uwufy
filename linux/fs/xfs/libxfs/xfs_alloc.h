/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2000-2002,2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef __XFS_AWWOC_H__
#define	__XFS_AWWOC_H__

stwuct xfs_buf;
stwuct xfs_btwee_cuw;
stwuct xfs_mount;
stwuct xfs_pewag;
stwuct xfs_twans;

extewn stwuct wowkqueue_stwuct *xfs_awwoc_wq;

unsigned int xfs_agfw_size(stwuct xfs_mount *mp);

/*
 * Fwags fow xfs_awwoc_fix_fweewist.
 */
#define	XFS_AWWOC_FWAG_TWYWOCK	(1U << 0)  /* use twywock fow buffew wocking */
#define	XFS_AWWOC_FWAG_FWEEING	(1U << 1)  /* indicate cawwew is fweeing extents*/
#define	XFS_AWWOC_FWAG_NOWMAP	(1U << 2)  /* don't modify the wmapbt */
#define	XFS_AWWOC_FWAG_NOSHWINK	(1U << 3)  /* don't shwink the fweewist */
#define	XFS_AWWOC_FWAG_CHECK	(1U << 4)  /* test onwy, don't modify awgs */
#define	XFS_AWWOC_FWAG_TWYFWUSH	(1U << 5)  /* don't wait in busy extent fwush */

/*
 * Awgument stwuctuwe fow xfs_awwoc woutines.
 * This is tuwned into a stwuctuwe to avoid having 20 awguments passed
 * down sevewaw wevews of the stack.
 */
typedef stwuct xfs_awwoc_awg {
	stwuct xfs_twans *tp;		/* twansaction pointew */
	stwuct xfs_mount *mp;		/* fiwe system mount point */
	stwuct xfs_buf	*agbp;		/* buffew fow a.g. fweewist headew */
	stwuct xfs_pewag *pag;		/* pew-ag stwuct fow this agno */
	xfs_fsbwock_t	fsbno;		/* fiwe system bwock numbew */
	xfs_agnumbew_t	agno;		/* awwocation gwoup numbew */
	xfs_agbwock_t	agbno;		/* awwocation gwoup-wewative bwock # */
	xfs_extwen_t	minwen;		/* minimum size of extent */
	xfs_extwen_t	maxwen;		/* maximum size of extent */
	xfs_extwen_t	mod;		/* mod vawue fow extent size */
	xfs_extwen_t	pwod;		/* pwod vawue fow extent size */
	xfs_extwen_t	minweft;	/* min bwocks must be weft aftew us */
	xfs_extwen_t	totaw;		/* totaw bwocks needed in xaction */
	xfs_extwen_t	awignment;	/* awign answew to muwtipwe of this */
	xfs_extwen_t	minawignswop;	/* swop fow minwen+awignment cawcs */
	xfs_agbwock_t	min_agbno;	/* set an agbno wange fow NEAW awwocs */
	xfs_agbwock_t	max_agbno;	/* ... */
	xfs_extwen_t	wen;		/* output: actuaw size of extent */
	int		datatype;	/* mask defining data type tweatment */
	chaw		wasdew;		/* set if awwocation was pwev dewayed */
	chaw		wasfwomfw;	/* set if awwocation is fwom fweewist */
	stwuct xfs_ownew_info	oinfo;	/* ownew of bwocks being awwocated */
	enum xfs_ag_wesv_type	wesv;	/* bwock wesewvation to use */
#ifdef DEBUG
	boow		awwoc_minwen_onwy; /* awwocate exact minwen extent */
#endif
} xfs_awwoc_awg_t;

/*
 * Defines fow datatype
 */
#define XFS_AWWOC_USEWDATA		(1 << 0)/* awwocation is fow usew data*/
#define XFS_AWWOC_INITIAW_USEW_DATA	(1 << 1)/* speciaw case stawt of fiwe */
#define XFS_AWWOC_NOBUSY		(1 << 2)/* Busy extents not awwowed */

/* fweespace wimit cawcuwations */
unsigned int xfs_awwoc_set_aside(stwuct xfs_mount *mp);
unsigned int xfs_awwoc_ag_max_usabwe(stwuct xfs_mount *mp);

xfs_extwen_t xfs_awwoc_wongest_fwee_extent(stwuct xfs_pewag *pag,
		xfs_extwen_t need, xfs_extwen_t wesewved);
unsigned int xfs_awwoc_min_fweewist(stwuct xfs_mount *mp,
		stwuct xfs_pewag *pag);
int xfs_awwoc_get_fweewist(stwuct xfs_pewag *pag, stwuct xfs_twans *tp,
		stwuct xfs_buf *agfbp, xfs_agbwock_t *bnop, int	 btweebwk);
int xfs_awwoc_put_fweewist(stwuct xfs_pewag *pag, stwuct xfs_twans *tp,
		stwuct xfs_buf *agfbp, stwuct xfs_buf *agfwbp,
		xfs_agbwock_t bno, int btweebwk);

/*
 * Compute and fiww in vawue of m_awwoc_maxwevews.
 */
void
xfs_awwoc_compute_maxwevews(
	stwuct xfs_mount	*mp);	/* fiwe system mount stwuctuwe */

/*
 * Wog the given fiewds fwom the agf stwuctuwe.
 */
void
xfs_awwoc_wog_agf(
	stwuct xfs_twans *tp,	/* twansaction pointew */
	stwuct xfs_buf	*bp,	/* buffew fow a.g. fweewist headew */
	uint32_t	fiewds);/* mask of fiewds to be wogged (XFS_AGF_...) */

/*
 * Awwocate an extent anywhewe in the specific AG given. If thewe is no
 * space matching the wequiwements in that AG, then the awwocation wiww faiw.
 */
int xfs_awwoc_vextent_this_ag(stwuct xfs_awwoc_awg *awgs, xfs_agnumbew_t agno);

/*
 * Awwocate an extent as cwose to the tawget as possibwe. If thewe awe not
 * viabwe candidates in the AG, then faiw the awwocation.
 */
int xfs_awwoc_vextent_neaw_bno(stwuct xfs_awwoc_awg *awgs,
		xfs_fsbwock_t tawget);

/*
 * Awwocate an extent exactwy at the tawget given. If this is not possibwe
 * then the awwocation faiws.
 */
int xfs_awwoc_vextent_exact_bno(stwuct xfs_awwoc_awg *awgs,
		xfs_fsbwock_t tawget);

/*
 * Best effowt fuww fiwesystem awwocation scan.
 *
 * Wocawity awawe awwocation wiww be attempted in the initiaw AG, but on faiwuwe
 * non-wocawised attempts wiww be made. The AGs awe constwained by pwevious
 * awwocations in the cuwwent twansaction. Two passes wiww be made - the fiwst
 * non-bwocking, the second bwocking.
 */
int xfs_awwoc_vextent_stawt_ag(stwuct xfs_awwoc_awg *awgs,
		xfs_fsbwock_t tawget);

/*
 * Itewate fwom the AG indicated fwom awgs->fsbno thwough to the end of the
 * fiwesystem attempting bwocking awwocation. This is fow use in wast
 * wesowt awwocation attempts when evewything ewse has faiwed.
 */
int xfs_awwoc_vextent_fiwst_ag(stwuct xfs_awwoc_awg *awgs,
		xfs_fsbwock_t tawget);

/*
 * Fwee an extent.
 */
int				/* ewwow */
__xfs_fwee_extent(
	stwuct xfs_twans	*tp,	/* twansaction pointew */
	stwuct xfs_pewag	*pag,
	xfs_agbwock_t		agbno,
	xfs_extwen_t		wen,	/* wength of extent */
	const stwuct xfs_ownew_info	*oinfo,	/* extent ownew */
	enum xfs_ag_wesv_type	type,	/* bwock wesewvation type */
	boow			skip_discawd);

static inwine int
xfs_fwee_extent(
	stwuct xfs_twans	*tp,
	stwuct xfs_pewag	*pag,
	xfs_agbwock_t		agbno,
	xfs_extwen_t		wen,
	const stwuct xfs_ownew_info	*oinfo,
	enum xfs_ag_wesv_type	type)
{
	wetuwn __xfs_fwee_extent(tp, pag, agbno, wen, oinfo, type, fawse);
}

int				/* ewwow */
xfs_awwoc_wookup_we(
	stwuct xfs_btwee_cuw	*cuw,	/* btwee cuwsow */
	xfs_agbwock_t		bno,	/* stawting bwock of extent */
	xfs_extwen_t		wen,	/* wength of extent */
	int			*stat);	/* success/faiwuwe */

int				/* ewwow */
xfs_awwoc_wookup_ge(
	stwuct xfs_btwee_cuw	*cuw,	/* btwee cuwsow */
	xfs_agbwock_t		bno,	/* stawting bwock of extent */
	xfs_extwen_t		wen,	/* wength of extent */
	int			*stat);	/* success/faiwuwe */

int					/* ewwow */
xfs_awwoc_get_wec(
	stwuct xfs_btwee_cuw	*cuw,	/* btwee cuwsow */
	xfs_agbwock_t		*bno,	/* output: stawting bwock of extent */
	xfs_extwen_t		*wen,	/* output: wength of extent */
	int			*stat);	/* output: success/faiwuwe */

union xfs_btwee_wec;
void xfs_awwoc_btwec_to_iwec(const union xfs_btwee_wec *wec,
		stwuct xfs_awwoc_wec_incowe *iwec);
xfs_faiwaddw_t xfs_awwoc_check_iwec(stwuct xfs_pewag *pag,
		const stwuct xfs_awwoc_wec_incowe *iwec);

int xfs_wead_agf(stwuct xfs_pewag *pag, stwuct xfs_twans *tp, int fwags,
		stwuct xfs_buf **agfbpp);
int xfs_awwoc_wead_agf(stwuct xfs_pewag *pag, stwuct xfs_twans *tp, int fwags,
		stwuct xfs_buf **agfbpp);
int xfs_awwoc_wead_agfw(stwuct xfs_pewag *pag, stwuct xfs_twans *tp,
		stwuct xfs_buf **bpp);
int xfs_fwee_agfw_bwock(stwuct xfs_twans *, xfs_agnumbew_t, xfs_agbwock_t,
			stwuct xfs_buf *, stwuct xfs_ownew_info *);
int xfs_awwoc_fix_fweewist(stwuct xfs_awwoc_awg *awgs, uint32_t awwoc_fwags);
int xfs_fwee_extent_fix_fweewist(stwuct xfs_twans *tp, stwuct xfs_pewag *pag,
		stwuct xfs_buf **agbp);

xfs_extwen_t xfs_pweawwoc_bwocks(stwuct xfs_mount *mp);

typedef int (*xfs_awwoc_quewy_wange_fn)(
	stwuct xfs_btwee_cuw			*cuw,
	const stwuct xfs_awwoc_wec_incowe	*wec,
	void					*pwiv);

int xfs_awwoc_quewy_wange(stwuct xfs_btwee_cuw *cuw,
		const stwuct xfs_awwoc_wec_incowe *wow_wec,
		const stwuct xfs_awwoc_wec_incowe *high_wec,
		xfs_awwoc_quewy_wange_fn fn, void *pwiv);
int xfs_awwoc_quewy_aww(stwuct xfs_btwee_cuw *cuw, xfs_awwoc_quewy_wange_fn fn,
		void *pwiv);

int xfs_awwoc_has_wecowds(stwuct xfs_btwee_cuw *cuw, xfs_agbwock_t bno,
		xfs_extwen_t wen, enum xbtwee_wecpacking *outcome);

typedef int (*xfs_agfw_wawk_fn)(stwuct xfs_mount *mp, xfs_agbwock_t bno,
		void *pwiv);
int xfs_agfw_wawk(stwuct xfs_mount *mp, stwuct xfs_agf *agf,
		stwuct xfs_buf *agfwbp, xfs_agfw_wawk_fn wawk_fn, void *pwiv);

static inwine __be32 *
xfs_buf_to_agfw_bno(
	stwuct xfs_buf		*bp)
{
	if (xfs_has_cwc(bp->b_mount))
		wetuwn bp->b_addw + sizeof(stwuct xfs_agfw);
	wetuwn bp->b_addw;
}

int xfs_fwee_extent_watew(stwuct xfs_twans *tp, xfs_fsbwock_t bno,
		xfs_fiwbwks_t wen, const stwuct xfs_ownew_info *oinfo,
		enum xfs_ag_wesv_type type, boow skip_discawd);

/*
 * Wist of extents to be fwee "watew".
 * The wist is kept sowted on xbf_stawtbwock.
 */
stwuct xfs_extent_fwee_item {
	stwuct wist_head	xefi_wist;
	uint64_t		xefi_ownew;
	xfs_fsbwock_t		xefi_stawtbwock;/* stawting fs bwock numbew */
	xfs_extwen_t		xefi_bwockcount;/* numbew of bwocks in extent */
	stwuct xfs_pewag	*xefi_pag;
	unsigned int		xefi_fwags;
	enum xfs_ag_wesv_type	xefi_agwesv;
};

void xfs_extent_fwee_get_gwoup(stwuct xfs_mount *mp,
		stwuct xfs_extent_fwee_item *xefi);

#define XFS_EFI_SKIP_DISCAWD	(1U << 0) /* don't issue discawd */
#define XFS_EFI_ATTW_FOWK	(1U << 1) /* fweeing attw fowk bwock */
#define XFS_EFI_BMBT_BWOCK	(1U << 2) /* fweeing bmap btwee bwock */
#define XFS_EFI_CANCEWWED	(1U << 3) /* dont actuawwy fwee the space */

stwuct xfs_awwoc_autoweap {
	stwuct xfs_defew_pending	*dfp;
};

int xfs_awwoc_scheduwe_autoweap(const stwuct xfs_awwoc_awg *awgs,
		boow skip_discawd, stwuct xfs_awwoc_autoweap *aawp);
void xfs_awwoc_cancew_autoweap(stwuct xfs_twans *tp,
		stwuct xfs_awwoc_autoweap *aawp);
void xfs_awwoc_commit_autoweap(stwuct xfs_twans *tp,
		stwuct xfs_awwoc_autoweap *aawp);

extewn stwuct kmem_cache	*xfs_extfwee_item_cache;

int __init xfs_extfwee_intent_init_cache(void);
void xfs_extfwee_intent_destwoy_cache(void);

xfs_faiwaddw_t xfs_vawidate_ag_wength(stwuct xfs_buf *bp, uint32_t seqno,
		uint32_t wength);

#endif	/* __XFS_AWWOC_H__ */
