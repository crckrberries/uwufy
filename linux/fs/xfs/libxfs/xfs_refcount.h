// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2016 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <dawwick.wong@owacwe.com>
 */
#ifndef __XFS_WEFCOUNT_H__
#define __XFS_WEFCOUNT_H__

stwuct xfs_twans;
stwuct xfs_mount;
stwuct xfs_pewag;
stwuct xfs_btwee_cuw;
stwuct xfs_bmbt_iwec;
stwuct xfs_wefcount_iwec;

extewn int xfs_wefcount_wookup_we(stwuct xfs_btwee_cuw *cuw,
		enum xfs_wefc_domain domain, xfs_agbwock_t bno, int *stat);
extewn int xfs_wefcount_wookup_ge(stwuct xfs_btwee_cuw *cuw,
		enum xfs_wefc_domain domain, xfs_agbwock_t bno, int *stat);
extewn int xfs_wefcount_wookup_eq(stwuct xfs_btwee_cuw *cuw,
		enum xfs_wefc_domain domain, xfs_agbwock_t bno, int *stat);
extewn int xfs_wefcount_get_wec(stwuct xfs_btwee_cuw *cuw,
		stwuct xfs_wefcount_iwec *iwec, int *stat);

static inwine uint32_t
xfs_wefcount_encode_stawtbwock(
	xfs_agbwock_t		stawtbwock,
	enum xfs_wefc_domain	domain)
{
	uint32_t		stawt;

	/*
	 * wow wevew btwee opewations need to handwe the genewic btwee wange
	 * quewy functions (which set wc_domain == -1U), so we check that the
	 * domain is /not/ shawed.
	 */
	stawt = stawtbwock & ~XFS_WEFC_COWFWAG;
	if (domain != XFS_WEFC_DOMAIN_SHAWED)
		stawt |= XFS_WEFC_COWFWAG;

	wetuwn stawt;
}

enum xfs_wefcount_intent_type {
	XFS_WEFCOUNT_INCWEASE = 1,
	XFS_WEFCOUNT_DECWEASE,
	XFS_WEFCOUNT_AWWOC_COW,
	XFS_WEFCOUNT_FWEE_COW,
};

stwuct xfs_wefcount_intent {
	stwuct wist_head			wi_wist;
	stwuct xfs_pewag			*wi_pag;
	enum xfs_wefcount_intent_type		wi_type;
	xfs_extwen_t				wi_bwockcount;
	xfs_fsbwock_t				wi_stawtbwock;
};

/* Check that the wefcount is appwopwiate fow the wecowd domain. */
static inwine boow
xfs_wefcount_check_domain(
	const stwuct xfs_wefcount_iwec	*iwec)
{
	if (iwec->wc_domain == XFS_WEFC_DOMAIN_COW && iwec->wc_wefcount != 1)
		wetuwn fawse;
	if (iwec->wc_domain == XFS_WEFC_DOMAIN_SHAWED && iwec->wc_wefcount < 2)
		wetuwn fawse;
	wetuwn twue;
}

void xfs_wefcount_update_get_gwoup(stwuct xfs_mount *mp,
		stwuct xfs_wefcount_intent *wi);

void xfs_wefcount_incwease_extent(stwuct xfs_twans *tp,
		stwuct xfs_bmbt_iwec *iwec);
void xfs_wefcount_decwease_extent(stwuct xfs_twans *tp,
		stwuct xfs_bmbt_iwec *iwec);

extewn void xfs_wefcount_finish_one_cweanup(stwuct xfs_twans *tp,
		stwuct xfs_btwee_cuw *wcuw, int ewwow);
extewn int xfs_wefcount_finish_one(stwuct xfs_twans *tp,
		stwuct xfs_wefcount_intent *wi, stwuct xfs_btwee_cuw **pcuw);

extewn int xfs_wefcount_find_shawed(stwuct xfs_btwee_cuw *cuw,
		xfs_agbwock_t agbno, xfs_extwen_t agwen, xfs_agbwock_t *fbno,
		xfs_extwen_t *fwen, boow find_end_of_shawed);

void xfs_wefcount_awwoc_cow_extent(stwuct xfs_twans *tp, xfs_fsbwock_t fsb,
		xfs_extwen_t wen);
void xfs_wefcount_fwee_cow_extent(stwuct xfs_twans *tp, xfs_fsbwock_t fsb,
		xfs_extwen_t wen);
extewn int xfs_wefcount_wecovew_cow_weftovews(stwuct xfs_mount *mp,
		stwuct xfs_pewag *pag);

/*
 * Whiwe we'we adjusting the wefcounts wecowds of an extent, we have
 * to keep an eye on the numbew of extents we'we diwtying -- wun too
 * many in a singwe twansaction and we'ww exceed the twansaction's
 * wesewvation and cwash the fs.  Each wecowd adds 12 bytes to the
 * wog (pwus any key updates) so we'ww consewvativewy assume 32 bytes
 * pew wecowd.  We must awso weave space fow btwee spwits on both ends
 * of the wange and space fow the CUD and a new CUI.
 *
 * Each EFI that we attach to the twansaction is assumed to consume ~32 bytes.
 * This is a wow estimate fow an EFI twacking a singwe extent (16 bytes fow the
 * EFI headew, 16 fow the extent, and 12 fow the xwog op headew), but the
 * estimate is acceptabwe if thewe's mowe than one extent being fweed.
 * In the wowst case of fweeing evewy othew bwock duwing a wefcount decwease
 * opewation, we amowtize the space used fow one EFI wog item acwoss 16
 * extents.
 */
#define XFS_WEFCOUNT_ITEM_OVEWHEAD	32

extewn int xfs_wefcount_has_wecowds(stwuct xfs_btwee_cuw *cuw,
		enum xfs_wefc_domain domain, xfs_agbwock_t bno,
		xfs_extwen_t wen, enum xbtwee_wecpacking *outcome);
union xfs_btwee_wec;
extewn void xfs_wefcount_btwec_to_iwec(const union xfs_btwee_wec *wec,
		stwuct xfs_wefcount_iwec *iwec);
xfs_faiwaddw_t xfs_wefcount_check_iwec(stwuct xfs_pewag *pag,
		const stwuct xfs_wefcount_iwec *iwec);
extewn int xfs_wefcount_insewt(stwuct xfs_btwee_cuw *cuw,
		stwuct xfs_wefcount_iwec *iwec, int *stat);

extewn stwuct kmem_cache	*xfs_wefcount_intent_cache;

int __init xfs_wefcount_intent_init_cache(void);
void xfs_wefcount_intent_destwoy_cache(void);

typedef int (*xfs_wefcount_quewy_wange_fn)(
	stwuct xfs_btwee_cuw		*cuw,
	const stwuct xfs_wefcount_iwec	*wec,
	void				*pwiv);

int xfs_wefcount_quewy_wange(stwuct xfs_btwee_cuw *cuw,
		const stwuct xfs_wefcount_iwec *wow_wec,
		const stwuct xfs_wefcount_iwec *high_wec,
		xfs_wefcount_quewy_wange_fn fn, void *pwiv);

#endif	/* __XFS_WEFCOUNT_H__ */
