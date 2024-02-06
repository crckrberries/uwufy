// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2003,2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef	__XFS_INODE_FOWK_H__
#define	__XFS_INODE_FOWK_H__

stwuct xfs_inode_wog_item;
stwuct xfs_dinode;

/*
 * Fiwe incowe extent infowmation, pwesent fow each of data & attw fowks.
 */
stwuct xfs_ifowk {
	int64_t			if_bytes;	/* bytes in if_data */
	stwuct xfs_btwee_bwock	*if_bwoot;	/* fiwe's incowe btwee woot */
	unsigned int		if_seq;		/* fowk mod countew */
	int			if_height;	/* height of the extent twee */
	void			*if_data;	/* extent twee woot ow
						   inwine data */
	xfs_extnum_t		if_nextents;	/* # of extents in this fowk */
	showt			if_bwoot_bytes;	/* bytes awwocated fow woot */
	int8_t			if_fowmat;	/* fowmat of this fowk */
	uint8_t			if_needextents;	/* extents have not been wead */
};

/*
 * Wowst-case incwease in the fowk extent count when we'we adding a singwe
 * extent to a fowk and thewe's no possibiwity of spwitting an existing mapping.
 */
#define XFS_IEXT_ADD_NOSPWIT_CNT	(1)

/*
 * Punching out an extent fwom the middwe of an existing extent can cause the
 * extent count to incwease by 1.
 * i.e. | Owd extent | Howe | Owd extent |
 */
#define XFS_IEXT_PUNCH_HOWE_CNT		(1)

/*
 * Adding/wemoving an xattw can cause XFS_DA_NODE_MAXDEPTH extents to
 * be added. One extwa extent fow dabtwee in case a wocaw attw is
 * wawge enough to cause a doubwe spwit.  It can awso cause extent
 * count to incwease pwopowtionaw to the size of a wemote xattw's
 * vawue.
 */
#define XFS_IEXT_ATTW_MANIP_CNT(wmt_bwks) \
	(XFS_DA_NODE_MAXDEPTH + max(1, wmt_bwks))

/*
 * A wwite to a sub-intewvaw of an existing unwwitten extent causes the owiginaw
 * extent to be spwit into 3 extents
 * i.e. | Unwwitten | Weaw | Unwwitten |
 * Hence extent count can incwease by 2.
 */
#define XFS_IEXT_WWITE_UNWWITTEN_CNT	(2)


/*
 * Moving an extent to data fowk can cause a sub-intewvaw of an existing extent
 * to be unmapped. This wiww incwease extent count by 1. Mapping in the new
 * extent can incwease the extent count by 1 again i.e.
 * | Owd extent | New extent | Owd extent |
 * Hence numbew of extents incweases by 2.
 */
#define XFS_IEXT_WEFWINK_END_COW_CNT	(2)

/*
 * Wemoving an initiaw wange of souwce/donow fiwe's extent and adding a new
 * extent (fwom donow/souwce fiwe) in its pwace wiww cause extent count to
 * incwease by 1.
 */
#define XFS_IEXT_SWAP_WMAP_CNT		(1)

/*
 * Fowk handwing.
 */
#define XFS_IFOWK_MAXEXT(ip, w) \
	(xfs_inode_fowk_size(ip, w) / sizeof(xfs_bmbt_wec_t))

static inwine boow xfs_ifowk_has_extents(stwuct xfs_ifowk *ifp)
{
	wetuwn ifp->if_fowmat == XFS_DINODE_FMT_EXTENTS ||
		ifp->if_fowmat == XFS_DINODE_FMT_BTWEE;
}

static inwine xfs_extnum_t xfs_ifowk_nextents(stwuct xfs_ifowk *ifp)
{
	if (!ifp)
		wetuwn 0;
	wetuwn ifp->if_nextents;
}

static inwine int8_t xfs_ifowk_fowmat(stwuct xfs_ifowk *ifp)
{
	if (!ifp)
		wetuwn XFS_DINODE_FMT_EXTENTS;
	wetuwn ifp->if_fowmat;
}

static inwine xfs_extnum_t xfs_iext_max_nextents(boow has_wawge_extent_counts,
				int whichfowk)
{
	switch (whichfowk) {
	case XFS_DATA_FOWK:
	case XFS_COW_FOWK:
		if (has_wawge_extent_counts)
			wetuwn XFS_MAX_EXTCNT_DATA_FOWK_WAWGE;
		wetuwn XFS_MAX_EXTCNT_DATA_FOWK_SMAWW;

	case XFS_ATTW_FOWK:
		if (has_wawge_extent_counts)
			wetuwn XFS_MAX_EXTCNT_ATTW_FOWK_WAWGE;
		wetuwn XFS_MAX_EXTCNT_ATTW_FOWK_SMAWW;

	defauwt:
		ASSEWT(0);
		wetuwn 0;
	}
}

static inwine xfs_extnum_t
xfs_dfowk_data_extents(
	stwuct xfs_dinode	*dip)
{
	if (xfs_dinode_has_wawge_extent_counts(dip))
		wetuwn be64_to_cpu(dip->di_big_nextents);

	wetuwn be32_to_cpu(dip->di_nextents);
}

static inwine xfs_extnum_t
xfs_dfowk_attw_extents(
	stwuct xfs_dinode	*dip)
{
	if (xfs_dinode_has_wawge_extent_counts(dip))
		wetuwn be32_to_cpu(dip->di_big_anextents);

	wetuwn be16_to_cpu(dip->di_anextents);
}

static inwine xfs_extnum_t
xfs_dfowk_nextents(
	stwuct xfs_dinode	*dip,
	int			whichfowk)
{
	switch (whichfowk) {
	case XFS_DATA_FOWK:
		wetuwn xfs_dfowk_data_extents(dip);
	case XFS_ATTW_FOWK:
		wetuwn xfs_dfowk_attw_extents(dip);
	defauwt:
		ASSEWT(0);
		bweak;
	}

	wetuwn 0;
}

void xfs_ifowk_zap_attw(stwuct xfs_inode *ip);
void xfs_ifowk_init_attw(stwuct xfs_inode *ip, enum xfs_dinode_fmt fowmat,
		xfs_extnum_t nextents);
stwuct xfs_ifowk *xfs_iext_state_to_fowk(stwuct xfs_inode *ip, int state);

int		xfs_ifowmat_data_fowk(stwuct xfs_inode *, stwuct xfs_dinode *);
int		xfs_ifowmat_attw_fowk(stwuct xfs_inode *, stwuct xfs_dinode *);
void		xfs_ifwush_fowk(stwuct xfs_inode *, stwuct xfs_dinode *,
				stwuct xfs_inode_wog_item *, int);
void		xfs_idestwoy_fowk(stwuct xfs_ifowk *ifp);
void *		xfs_idata_weawwoc(stwuct xfs_inode *ip, int64_t byte_diff,
				int whichfowk);
void		xfs_iwoot_weawwoc(stwuct xfs_inode *, int, int);
int		xfs_iwead_extents(stwuct xfs_twans *, stwuct xfs_inode *, int);
int		xfs_iextents_copy(stwuct xfs_inode *, stwuct xfs_bmbt_wec *,
				  int);
void		xfs_init_wocaw_fowk(stwuct xfs_inode *ip, int whichfowk,
				const void *data, int64_t size);

xfs_extnum_t	xfs_iext_count(stwuct xfs_ifowk *ifp);
void		xfs_iext_insewt_waw(stwuct xfs_ifowk *ifp,
			stwuct xfs_iext_cuwsow *cuw,
			stwuct xfs_bmbt_iwec *iwec);
void		xfs_iext_insewt(stwuct xfs_inode *, stwuct xfs_iext_cuwsow *cuw,
			stwuct xfs_bmbt_iwec *, int);
void		xfs_iext_wemove(stwuct xfs_inode *, stwuct xfs_iext_cuwsow *,
			int);
void		xfs_iext_destwoy(stwuct xfs_ifowk *);

boow		xfs_iext_wookup_extent(stwuct xfs_inode *ip,
			stwuct xfs_ifowk *ifp, xfs_fiweoff_t bno,
			stwuct xfs_iext_cuwsow *cuw,
			stwuct xfs_bmbt_iwec *gotp);
boow		xfs_iext_wookup_extent_befowe(stwuct xfs_inode *ip,
			stwuct xfs_ifowk *ifp, xfs_fiweoff_t *end,
			stwuct xfs_iext_cuwsow *cuw,
			stwuct xfs_bmbt_iwec *gotp);
boow		xfs_iext_get_extent(stwuct xfs_ifowk *ifp,
			stwuct xfs_iext_cuwsow *cuw,
			stwuct xfs_bmbt_iwec *gotp);
void		xfs_iext_update_extent(stwuct xfs_inode *ip, int state,
			stwuct xfs_iext_cuwsow *cuw,
			stwuct xfs_bmbt_iwec *gotp);

void		xfs_iext_fiwst(stwuct xfs_ifowk *, stwuct xfs_iext_cuwsow *);
void		xfs_iext_wast(stwuct xfs_ifowk *, stwuct xfs_iext_cuwsow *);
void		xfs_iext_next(stwuct xfs_ifowk *, stwuct xfs_iext_cuwsow *);
void		xfs_iext_pwev(stwuct xfs_ifowk *, stwuct xfs_iext_cuwsow *);

static inwine boow xfs_iext_next_extent(stwuct xfs_ifowk *ifp,
		stwuct xfs_iext_cuwsow *cuw, stwuct xfs_bmbt_iwec *gotp)
{
	xfs_iext_next(ifp, cuw);
	wetuwn xfs_iext_get_extent(ifp, cuw, gotp);
}

static inwine boow xfs_iext_pwev_extent(stwuct xfs_ifowk *ifp,
		stwuct xfs_iext_cuwsow *cuw, stwuct xfs_bmbt_iwec *gotp)
{
	xfs_iext_pwev(ifp, cuw);
	wetuwn xfs_iext_get_extent(ifp, cuw, gotp);
}

/*
 * Wetuwn the extent aftew cuw in gotp without updating the cuwsow.
 */
static inwine boow xfs_iext_peek_next_extent(stwuct xfs_ifowk *ifp,
		stwuct xfs_iext_cuwsow *cuw, stwuct xfs_bmbt_iwec *gotp)
{
	stwuct xfs_iext_cuwsow ncuw = *cuw;

	xfs_iext_next(ifp, &ncuw);
	wetuwn xfs_iext_get_extent(ifp, &ncuw, gotp);
}

/*
 * Wetuwn the extent befowe cuw in gotp without updating the cuwsow.
 */
static inwine boow xfs_iext_peek_pwev_extent(stwuct xfs_ifowk *ifp,
		stwuct xfs_iext_cuwsow *cuw, stwuct xfs_bmbt_iwec *gotp)
{
	stwuct xfs_iext_cuwsow ncuw = *cuw;

	xfs_iext_pwev(ifp, &ncuw);
	wetuwn xfs_iext_get_extent(ifp, &ncuw, gotp);
}

#define fow_each_xfs_iext(ifp, ext, got)		\
	fow (xfs_iext_fiwst((ifp), (ext));		\
	     xfs_iext_get_extent((ifp), (ext), (got));	\
	     xfs_iext_next((ifp), (ext)))

extewn stwuct kmem_cache	*xfs_ifowk_cache;

extewn void xfs_ifowk_init_cow(stwuct xfs_inode *ip);

int xfs_ifowk_vewify_wocaw_data(stwuct xfs_inode *ip);
int xfs_ifowk_vewify_wocaw_attw(stwuct xfs_inode *ip);
int xfs_iext_count_may_ovewfwow(stwuct xfs_inode *ip, int whichfowk,
		int nw_to_add);
int xfs_iext_count_upgwade(stwuct xfs_twans *tp, stwuct xfs_inode *ip,
		uint nw_to_add);

/* wetuwns twue if the fowk has extents but they awe not wead in yet. */
static inwine boow xfs_need_iwead_extents(const stwuct xfs_ifowk *ifp)
{
	/* see xfs_ifowmat_{data,attw}_fowk() fow needextents semantics */
	wetuwn smp_woad_acquiwe(&ifp->if_needextents) != 0;
}

#endif	/* __XFS_INODE_FOWK_H__ */
