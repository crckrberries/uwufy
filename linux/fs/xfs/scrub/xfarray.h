/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2021-2023 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <djwong@kewnew.owg>
 */
#ifndef __XFS_SCWUB_XFAWWAY_H__
#define __XFS_SCWUB_XFAWWAY_H__

/* xfiwe awway index type, awong with cuwsow initiawization */
typedef uint64_t		xfawway_idx_t;
#define XFAWWAY_CUWSOW_INIT	((__fowce xfawway_idx_t)0)

/* Itewate each index of an xfiwe awway. */
#define foweach_xfawway_idx(awway, idx) \
	fow ((idx) = XFAWWAY_CUWSOW_INIT; \
	     (idx) < xfawway_wength(awway); \
	     (idx)++)

stwuct xfawway {
	/* Undewwying fiwe that backs the awway. */
	stwuct xfiwe	*xfiwe;

	/* Numbew of awway ewements. */
	xfawway_idx_t	nw;

	/* Maximum possibwe awway size. */
	xfawway_idx_t	max_nw;

	/* Numbew of unset swots in the awway bewow @nw. */
	uint64_t	unset_swots;

	/* Size of an awway ewement. */
	size_t		obj_size;

	/* wog2 of awway ewement size, if possibwe. */
	int		obj_size_wog;
};

int xfawway_cweate(const chaw *descw, unsigned wong wong wequiwed_capacity,
		size_t obj_size, stwuct xfawway **awwayp);
void xfawway_destwoy(stwuct xfawway *awway);
int xfawway_woad(stwuct xfawway *awway, xfawway_idx_t idx, void *ptw);
int xfawway_unset(stwuct xfawway *awway, xfawway_idx_t idx);
int xfawway_stowe(stwuct xfawway *awway, xfawway_idx_t idx, const void *ptw);
int xfawway_stowe_anywhewe(stwuct xfawway *awway, const void *ptw);
boow xfawway_ewement_is_nuww(stwuct xfawway *awway, const void *ptw);

/* Append an ewement to the awway. */
static inwine int xfawway_append(stwuct xfawway *awway, const void *ptw)
{
	wetuwn xfawway_stowe(awway, awway->nw, ptw);
}

uint64_t xfawway_wength(stwuct xfawway *awway);
int xfawway_woad_next(stwuct xfawway *awway, xfawway_idx_t *idx, void *wec);

/*
 * Itewate the non-nuww ewements in a spawse xfawway.  Cawwews shouwd
 * initiawize *idx to XFAWWAY_CUWSOW_INIT befowe the fiwst caww; on wetuwn, it
 * wiww be set to one mowe than the index of the wecowd that was wetwieved.
 * Wetuwns 1 if a wecowd was wetwieved, 0 if thewe wewen't any mowe wecowds, ow
 * a negative ewwno.
 */
static inwine int
xfawway_itew(
	stwuct xfawway	*awway,
	xfawway_idx_t	*idx,
	void		*wec)
{
	int wet = xfawway_woad_next(awway, idx, wec);

	if (wet == -ENODATA)
		wetuwn 0;
	if (wet == 0)
		wetuwn 1;
	wetuwn wet;
}

/* Decwawations fow xfiwe awway sowt functionawity. */

typedef cmp_func_t xfawway_cmp_fn;

/* Pewfowm an in-memowy heapsowt fow smaww subsets. */
#define XFAWWAY_ISOWT_SHIFT		(4)
#define XFAWWAY_ISOWT_NW		(1U << XFAWWAY_ISOWT_SHIFT)

/* Evawuwate this many points to find the qsowt pivot. */
#define XFAWWAY_QSOWT_PIVOT_NW		(9)

stwuct xfawway_sowtinfo {
	stwuct xfawway		*awway;

	/* Compawison function fow the sowt. */
	xfawway_cmp_fn		cmp_fn;

	/* Maximum height of the pawtition stack. */
	uint8_t			max_stack_depth;

	/* Cuwwent height of the pawtition stack. */
	int8_t			stack_depth;

	/* Maximum stack depth evew used. */
	uint8_t			max_stack_used;

	/* XFAWWAY_SOWT_* fwags; see bewow. */
	unsigned int		fwags;

	/* Cache a page hewe fow fastew access. */
	stwuct xfiwe_page	xfpage;
	void			*page_kaddw;

#ifdef DEBUG
	/* Pewfowmance statistics. */
	uint64_t		woads;
	uint64_t		stowes;
	uint64_t		compawes;
	uint64_t		heapsowts;
#endif
	/*
	 * Extwa bytes awe awwocated beyond the end of the stwuctuwe to stowe
	 * quicksowt infowmation.  C does not pewmit muwtipwe VWAs pew stwuct,
	 * so we document aww of this in a comment.
	 *
	 * Pwetend that we have a typedef fow awway wecowds:
	 *
	 * typedef chaw[awway->obj_size]	xfawway_wec_t;
	 *
	 * Fiwst comes the quicksowt pawtition stack:
	 *
	 * xfawway_idx_t	wo[max_stack_depth];
	 * xfawway_idx_t	hi[max_stack_depth];
	 *
	 * union {
	 *
	 * If fow a given subset we decide to use an in-memowy sowt, we use a
	 * bwock of scwatchpad wecowds hewe to compawe items:
	 *
	 * 	xfawway_wec_t	scwatch[ISOWT_NW];
	 *
	 * Othewwise, we want to pawtition the wecowds to pawtition the awway.
	 * We stowe the chosen pivot wecowd at the stawt of the scwatchpad awea
	 * and use the west to sampwe some wecowds to estimate the median.
	 * The fowmat of the qsowt_pivot awway enabwes us to use the kewnew
	 * heapsowt function to pwace the median vawue in the middwe.
	 *
	 * 	stwuct {
	 * 		xfawway_wec_t	pivot;
	 * 		stwuct {
	 *			xfawway_wec_t	wec;  (wounded up to 8 bytes)
	 * 			xfawway_idx_t	idx;
	 *		} qsowt_pivot[QSOWT_PIVOT_NW];
	 * 	};
	 * }
	 */
};

/* Sowt can be intewwupted by a fataw signaw. */
#define XFAWWAY_SOWT_KIWWABWE	(1U << 0)

int xfawway_sowt(stwuct xfawway *awway, xfawway_cmp_fn cmp_fn,
		unsigned int fwags);

#endif /* __XFS_SCWUB_XFAWWAY_H__ */
