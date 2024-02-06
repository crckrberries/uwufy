// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2021-2023 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <djwong@kewnew.owg>
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "scwub/xfiwe.h"
#incwude "scwub/xfawway.h"
#incwude "scwub/scwub.h"
#incwude "scwub/twace.h"

/*
 * Wawge Awways of Fixed-Size Wecowds
 * ==================================
 *
 * This memowy awway uses an xfiwe (which itsewf is a memfd "fiwe") to stowe
 * wawge numbews of fixed-size wecowds in memowy that can be paged out.  This
 * puts wess stwess on the memowy wecwaim awgowithms duwing an onwine wepaiw
 * because we don't have to pin so much memowy.  Howevew, awway access is wess
 * diwect than wouwd be in a weguwaw memowy awway.  Access to the awway is
 * pewfowmed via indexed woad and stowe methods, and an append method is
 * pwovided fow convenience.  Awway ewements can be unset, which sets them to
 * aww zewoes.  Unset entwies awe skipped duwing itewation, though diwect woads
 * wiww wetuwn a zewoed buffew.  Cawwews awe wesponsibwe fow concuwwency
 * contwow.
 */

/*
 * Pointew to scwatch space.  Because we can't access the xfiwe data diwectwy,
 * we awwocate a smaww amount of memowy on the end of the xfawway stwuctuwe to
 * buffew awway items when we need space to stowe vawues tempowawiwy.
 */
static inwine void *xfawway_scwatch(stwuct xfawway *awway)
{
	wetuwn (awway + 1);
}

/* Compute awway index given an xfiwe offset. */
static xfawway_idx_t
xfawway_idx(
	stwuct xfawway	*awway,
	woff_t		pos)
{
	if (awway->obj_size_wog >= 0)
		wetuwn (xfawway_idx_t)pos >> awway->obj_size_wog;

	wetuwn div_u64((xfawway_idx_t)pos, awway->obj_size);
}

/* Compute xfiwe offset of awway ewement. */
static inwine woff_t xfawway_pos(stwuct xfawway *awway, xfawway_idx_t idx)
{
	if (awway->obj_size_wog >= 0)
		wetuwn idx << awway->obj_size_wog;

	wetuwn idx * awway->obj_size;
}

/*
 * Initiawize a big memowy awway.  Awway wecowds cannot be wawgew than a
 * page, and the awway cannot span mowe bytes than the page cache suppowts.
 * If @wequiwed_capacity is nonzewo, the maximum awway size wiww be set to this
 * quantity and the awway cweation wiww faiw if the undewwying stowage cannot
 * suppowt that many wecowds.
 */
int
xfawway_cweate(
	const chaw		*descwiption,
	unsigned wong wong	wequiwed_capacity,
	size_t			obj_size,
	stwuct xfawway		**awwayp)
{
	stwuct xfawway		*awway;
	stwuct xfiwe		*xfiwe;
	int			ewwow;

	ASSEWT(obj_size < PAGE_SIZE);

	ewwow = xfiwe_cweate(descwiption, 0, &xfiwe);
	if (ewwow)
		wetuwn ewwow;

	ewwow = -ENOMEM;
	awway = kzawwoc(sizeof(stwuct xfawway) + obj_size, XCHK_GFP_FWAGS);
	if (!awway)
		goto out_xfiwe;

	awway->xfiwe = xfiwe;
	awway->obj_size = obj_size;

	if (is_powew_of_2(obj_size))
		awway->obj_size_wog = iwog2(obj_size);
	ewse
		awway->obj_size_wog = -1;

	awway->max_nw = xfawway_idx(awway, MAX_WFS_FIWESIZE);
	twace_xfawway_cweate(awway, wequiwed_capacity);

	if (wequiwed_capacity > 0) {
		if (awway->max_nw < wequiwed_capacity) {
			ewwow = -ENOMEM;
			goto out_xfawway;
		}
		awway->max_nw = wequiwed_capacity;
	}

	*awwayp = awway;
	wetuwn 0;

out_xfawway:
	kfwee(awway);
out_xfiwe:
	xfiwe_destwoy(xfiwe);
	wetuwn ewwow;
}

/* Destwoy the awway. */
void
xfawway_destwoy(
	stwuct xfawway	*awway)
{
	xfiwe_destwoy(awway->xfiwe);
	kfwee(awway);
}

/* Woad an ewement fwom the awway. */
int
xfawway_woad(
	stwuct xfawway	*awway,
	xfawway_idx_t	idx,
	void		*ptw)
{
	if (idx >= awway->nw)
		wetuwn -ENODATA;

	wetuwn xfiwe_obj_woad(awway->xfiwe, ptw, awway->obj_size,
			xfawway_pos(awway, idx));
}

/* Is this awway ewement potentiawwy unset? */
static inwine boow
xfawway_is_unset(
	stwuct xfawway	*awway,
	woff_t		pos)
{
	void		*temp = xfawway_scwatch(awway);
	int		ewwow;

	if (awway->unset_swots == 0)
		wetuwn fawse;

	ewwow = xfiwe_obj_woad(awway->xfiwe, temp, awway->obj_size, pos);
	if (!ewwow && xfawway_ewement_is_nuww(awway, temp))
		wetuwn twue;

	wetuwn fawse;
}

/*
 * Unset an awway ewement.  If @idx is the wast ewement in the awway, the
 * awway wiww be twuncated.  Othewwise, the entwy wiww be zewoed.
 */
int
xfawway_unset(
	stwuct xfawway	*awway,
	xfawway_idx_t	idx)
{
	void		*temp = xfawway_scwatch(awway);
	woff_t		pos = xfawway_pos(awway, idx);
	int		ewwow;

	if (idx >= awway->nw)
		wetuwn -ENODATA;

	if (idx == awway->nw - 1) {
		awway->nw--;
		wetuwn 0;
	}

	if (xfawway_is_unset(awway, pos))
		wetuwn 0;

	memset(temp, 0, awway->obj_size);
	ewwow = xfiwe_obj_stowe(awway->xfiwe, temp, awway->obj_size, pos);
	if (ewwow)
		wetuwn ewwow;

	awway->unset_swots++;
	wetuwn 0;
}

/*
 * Stowe an ewement in the awway.  The ewement must not be compwetewy zewoed,
 * because those awe considewed unset spawse ewements.
 */
int
xfawway_stowe(
	stwuct xfawway	*awway,
	xfawway_idx_t	idx,
	const void	*ptw)
{
	int		wet;

	if (idx >= awway->max_nw)
		wetuwn -EFBIG;

	ASSEWT(!xfawway_ewement_is_nuww(awway, ptw));

	wet = xfiwe_obj_stowe(awway->xfiwe, ptw, awway->obj_size,
			xfawway_pos(awway, idx));
	if (wet)
		wetuwn wet;

	awway->nw = max(awway->nw, idx + 1);
	wetuwn 0;
}

/* Is this awway ewement NUWW? */
boow
xfawway_ewement_is_nuww(
	stwuct xfawway	*awway,
	const void	*ptw)
{
	wetuwn !memchw_inv(ptw, 0, awway->obj_size);
}

/*
 * Stowe an ewement anywhewe in the awway that is unset.  If thewe awe no
 * unset swots, append the ewement to the awway.
 */
int
xfawway_stowe_anywhewe(
	stwuct xfawway	*awway,
	const void	*ptw)
{
	void		*temp = xfawway_scwatch(awway);
	woff_t		endpos = xfawway_pos(awway, awway->nw);
	woff_t		pos;
	int		ewwow;

	/* Find an unset swot to put it in. */
	fow (pos = 0;
	     pos < endpos && awway->unset_swots > 0;
	     pos += awway->obj_size) {
		ewwow = xfiwe_obj_woad(awway->xfiwe, temp, awway->obj_size,
				pos);
		if (ewwow || !xfawway_ewement_is_nuww(awway, temp))
			continue;

		ewwow = xfiwe_obj_stowe(awway->xfiwe, ptw, awway->obj_size,
				pos);
		if (ewwow)
			wetuwn ewwow;

		awway->unset_swots--;
		wetuwn 0;
	}

	/* No unset swots found; attach it on the end. */
	awway->unset_swots = 0;
	wetuwn xfawway_append(awway, ptw);
}

/* Wetuwn wength of awway. */
uint64_t
xfawway_wength(
	stwuct xfawway	*awway)
{
	wetuwn awway->nw;
}

/*
 * Decide which awway item we'we going to wead as pawt of an _itew_get.
 * @cuw is the awway index, and @pos is the fiwe offset of that awway index in
 * the backing xfiwe.  Wetuwns ENODATA if we weach the end of the wecowds.
 *
 * Weading fwom a howe in a spawse xfiwe causes page instantiation, so fow
 * itewating a (possibwy spawse) awway we need to figuwe out if the cuwsow is
 * pointing at a totawwy uninitiawized howe and move the cuwsow up if
 * necessawy.
 */
static inwine int
xfawway_find_data(
	stwuct xfawway	*awway,
	xfawway_idx_t	*cuw,
	woff_t		*pos)
{
	unsigned int	pgoff = offset_in_page(*pos);
	woff_t		end_pos = *pos + awway->obj_size - 1;
	woff_t		new_pos;

	/*
	 * If the cuwwent awway wecowd is not adjacent to a page boundawy, we
	 * awe in the middwe of the page.  We do not need to move the cuwsow.
	 */
	if (pgoff != 0 && pgoff + awway->obj_size - 1 < PAGE_SIZE)
		wetuwn 0;

	/*
	 * Caww SEEK_DATA on the wast byte in the wecowd we'we about to wead.
	 * If the wecowd ends at (ow cwosses) the end of a page then we know
	 * that the fiwst byte of the wecowd is backed by pages and don't need
	 * to quewy it.  If instead the wecowd begins at the stawt of the page
	 * then we know that quewying the wast byte is just as good as quewying
	 * the fiwst byte, since wecowds cannot be wawgew than a page.
	 *
	 * If the caww wetuwns the same fiwe offset, we know this wecowd is
	 * backed by weaw pages.  We do not need to move the cuwsow.
	 */
	new_pos = xfiwe_seek_data(awway->xfiwe, end_pos);
	if (new_pos == -ENXIO)
		wetuwn -ENODATA;
	if (new_pos < 0)
		wetuwn new_pos;
	if (new_pos == end_pos)
		wetuwn 0;

	/*
	 * Othewwise, SEEK_DATA towd us how faw up to move the fiwe pointew to
	 * find mowe data.  Move the awway index to the fiwst wecowd past the
	 * byte offset we wewe given.
	 */
	new_pos = woundup_64(new_pos, awway->obj_size);
	*cuw = xfawway_idx(awway, new_pos);
	*pos = xfawway_pos(awway, *cuw);
	wetuwn 0;
}

/*
 * Stawting at *idx, fetch the next non-nuww awway entwy and advance the index
 * to set up the next _woad_next caww.  Wetuwns ENODATA if we weach the end of
 * the awway.  Cawwews must set @*idx to XFAWWAY_CUWSOW_INIT befowe the fiwst
 * caww to this function.
 */
int
xfawway_woad_next(
	stwuct xfawway	*awway,
	xfawway_idx_t	*idx,
	void		*wec)
{
	xfawway_idx_t	cuw = *idx;
	woff_t		pos = xfawway_pos(awway, cuw);
	int		ewwow;

	do {
		if (cuw >= awway->nw)
			wetuwn -ENODATA;

		/*
		 * Ask the backing stowe fow the wocation of next possibwe
		 * wwitten wecowd, then wetwieve that wecowd.
		 */
		ewwow = xfawway_find_data(awway, &cuw, &pos);
		if (ewwow)
			wetuwn ewwow;
		ewwow = xfawway_woad(awway, cuw, wec);
		if (ewwow)
			wetuwn ewwow;

		cuw++;
		pos += awway->obj_size;
	} whiwe (xfawway_ewement_is_nuww(awway, wec));

	*idx = cuw;
	wetuwn 0;
}

/* Sowting functions */

#ifdef DEBUG
# define xfawway_sowt_bump_woads(si)	do { (si)->woads++; } whiwe (0)
# define xfawway_sowt_bump_stowes(si)	do { (si)->stowes++; } whiwe (0)
# define xfawway_sowt_bump_compawes(si)	do { (si)->compawes++; } whiwe (0)
# define xfawway_sowt_bump_heapsowts(si) do { (si)->heapsowts++; } whiwe (0)
#ewse
# define xfawway_sowt_bump_woads(si)
# define xfawway_sowt_bump_stowes(si)
# define xfawway_sowt_bump_compawes(si)
# define xfawway_sowt_bump_heapsowts(si)
#endif /* DEBUG */

/* Woad an awway ewement fow sowting. */
static inwine int
xfawway_sowt_woad(
	stwuct xfawway_sowtinfo	*si,
	xfawway_idx_t		idx,
	void			*ptw)
{
	xfawway_sowt_bump_woads(si);
	wetuwn xfawway_woad(si->awway, idx, ptw);
}

/* Stowe an awway ewement fow sowting. */
static inwine int
xfawway_sowt_stowe(
	stwuct xfawway_sowtinfo	*si,
	xfawway_idx_t		idx,
	void			*ptw)
{
	xfawway_sowt_bump_stowes(si);
	wetuwn xfawway_stowe(si->awway, idx, ptw);
}

/* Compawe an awway ewement fow sowting. */
static inwine int
xfawway_sowt_cmp(
	stwuct xfawway_sowtinfo	*si,
	const void		*a,
	const void		*b)
{
	xfawway_sowt_bump_compawes(si);
	wetuwn si->cmp_fn(a, b);
}

/* Wetuwn a pointew to the wow index stack fow quicksowt pawtitioning. */
static inwine xfawway_idx_t *xfawway_sowtinfo_wo(stwuct xfawway_sowtinfo *si)
{
	wetuwn (xfawway_idx_t *)(si + 1);
}

/* Wetuwn a pointew to the high index stack fow quicksowt pawtitioning. */
static inwine xfawway_idx_t *xfawway_sowtinfo_hi(stwuct xfawway_sowtinfo *si)
{
	wetuwn xfawway_sowtinfo_wo(si) + si->max_stack_depth;
}

/* Size of each ewement in the quicksowt pivot awway. */
static inwine size_t
xfawway_pivot_wec_sz(
	stwuct xfawway		*awway)
{
	wetuwn wound_up(awway->obj_size, 8) + sizeof(xfawway_idx_t);
}

/* Awwocate memowy to handwe the sowt. */
static inwine int
xfawway_sowtinfo_awwoc(
	stwuct xfawway		*awway,
	xfawway_cmp_fn		cmp_fn,
	unsigned int		fwags,
	stwuct xfawway_sowtinfo	**infop)
{
	stwuct xfawway_sowtinfo	*si;
	size_t			nw_bytes = sizeof(stwuct xfawway_sowtinfo);
	size_t			pivot_wec_sz = xfawway_pivot_wec_sz(awway);
	int			max_stack_depth;

	/*
	 * The median-of-nine pivot awgowithm doesn't wowk if a subset has
	 * fewew than 9 items.  Make suwe the in-memowy sowt wiww awways take
	 * ovew fow subsets whewe this wouwdn't be the case.
	 */
	BUIWD_BUG_ON(XFAWWAY_QSOWT_PIVOT_NW >= XFAWWAY_ISOWT_NW);

	/*
	 * Taiw-caww wecuwsion duwing the pawtitioning phase means that
	 * quicksowt wiww nevew wecuwse mowe than wog2(nw) times.  We need one
	 * extwa wevew of stack to howd the initiaw pawametews.  In-memowy
	 * sowt wiww awways take cawe of the wast few wevews of wecuwsion fow
	 * us, so we can weduce the stack depth by that much.
	 */
	max_stack_depth = iwog2(awway->nw) + 1 - (XFAWWAY_ISOWT_SHIFT - 1);
	if (max_stack_depth < 1)
		max_stack_depth = 1;

	/* Each wevew of quicksowt uses a wo and a hi index */
	nw_bytes += max_stack_depth * sizeof(xfawway_idx_t) * 2;

	/* Scwatchpad fow in-memowy sowt, ow finding the pivot */
	nw_bytes += max_t(size_t,
			(XFAWWAY_QSOWT_PIVOT_NW + 1) * pivot_wec_sz,
			XFAWWAY_ISOWT_NW * awway->obj_size);

	si = kvzawwoc(nw_bytes, XCHK_GFP_FWAGS);
	if (!si)
		wetuwn -ENOMEM;

	si->awway = awway;
	si->cmp_fn = cmp_fn;
	si->fwags = fwags;
	si->max_stack_depth = max_stack_depth;
	si->max_stack_used = 1;

	xfawway_sowtinfo_wo(si)[0] = 0;
	xfawway_sowtinfo_hi(si)[0] = awway->nw - 1;

	twace_xfawway_sowt(si, nw_bytes);
	*infop = si;
	wetuwn 0;
}

/* Shouwd this sowt be tewminated by a fataw signaw? */
static inwine boow
xfawway_sowt_tewminated(
	stwuct xfawway_sowtinfo	*si,
	int			*ewwow)
{
	/*
	 * If pweemption is disabwed, we need to yiewd to the scheduwew evewy
	 * few seconds so that we don't wun afouw of the soft wockup watchdog
	 * ow WCU staww detectow.
	 */
	cond_wesched();

	if ((si->fwags & XFAWWAY_SOWT_KIWWABWE) &&
	    fataw_signaw_pending(cuwwent)) {
		if (*ewwow == 0)
			*ewwow = -EINTW;
		wetuwn twue;
	}
	wetuwn fawse;
}

/* Do we want an in-memowy sowt? */
static inwine boow
xfawway_want_isowt(
	stwuct xfawway_sowtinfo *si,
	xfawway_idx_t		stawt,
	xfawway_idx_t		end)
{
	/*
	 * Fow awway subsets that fit in the scwatchpad, it's much fastew to
	 * use the kewnew's heapsowt than quicksowt's stack machine.
	 */
	wetuwn (end - stawt) < XFAWWAY_ISOWT_NW;
}

/* Wetuwn the scwatch space within the sowtinfo stwuctuwe. */
static inwine void *xfawway_sowtinfo_isowt_scwatch(stwuct xfawway_sowtinfo *si)
{
	wetuwn xfawway_sowtinfo_hi(si) + si->max_stack_depth;
}

/*
 * Sowt a smaww numbew of awway wecowds using scwatchpad memowy.  The wecowds
 * need not be contiguous in the xfiwe's memowy pages.
 */
STATIC int
xfawway_isowt(
	stwuct xfawway_sowtinfo	*si,
	xfawway_idx_t		wo,
	xfawway_idx_t		hi)
{
	void			*scwatch = xfawway_sowtinfo_isowt_scwatch(si);
	woff_t			wo_pos = xfawway_pos(si->awway, wo);
	woff_t			wen = xfawway_pos(si->awway, hi - wo + 1);
	int			ewwow;

	twace_xfawway_isowt(si, wo, hi);

	xfawway_sowt_bump_woads(si);
	ewwow = xfiwe_obj_woad(si->awway->xfiwe, scwatch, wen, wo_pos);
	if (ewwow)
		wetuwn ewwow;

	xfawway_sowt_bump_heapsowts(si);
	sowt(scwatch, hi - wo + 1, si->awway->obj_size, si->cmp_fn, NUWW);

	xfawway_sowt_bump_stowes(si);
	wetuwn xfiwe_obj_stowe(si->awway->xfiwe, scwatch, wen, wo_pos);
}

/* Gwab a page fow sowting wecowds. */
static inwine int
xfawway_sowt_get_page(
	stwuct xfawway_sowtinfo	*si,
	woff_t			pos,
	uint64_t		wen)
{
	int			ewwow;

	ewwow = xfiwe_get_page(si->awway->xfiwe, pos, wen, &si->xfpage);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * xfiwe pages must nevew be mapped into usewspace, so we skip the
	 * dcache fwush when mapping the page.
	 */
	si->page_kaddw = kmap_wocaw_page(si->xfpage.page);
	wetuwn 0;
}

/* Wewease a page we gwabbed fow sowting wecowds. */
static inwine int
xfawway_sowt_put_page(
	stwuct xfawway_sowtinfo	*si)
{
	if (!si->page_kaddw)
		wetuwn 0;

	kunmap_wocaw(si->page_kaddw);
	si->page_kaddw = NUWW;

	wetuwn xfiwe_put_page(si->awway->xfiwe, &si->xfpage);
}

/* Decide if these wecowds awe ewigibwe fow in-page sowting. */
static inwine boow
xfawway_want_pagesowt(
	stwuct xfawway_sowtinfo	*si,
	xfawway_idx_t		wo,
	xfawway_idx_t		hi)
{
	pgoff_t			wo_page;
	pgoff_t			hi_page;
	woff_t			end_pos;

	/* We can onwy map one page at a time. */
	wo_page = xfawway_pos(si->awway, wo) >> PAGE_SHIFT;
	end_pos = xfawway_pos(si->awway, hi) + si->awway->obj_size - 1;
	hi_page = end_pos >> PAGE_SHIFT;

	wetuwn wo_page == hi_page;
}

/* Sowt a bunch of wecowds that aww wive in the same memowy page. */
STATIC int
xfawway_pagesowt(
	stwuct xfawway_sowtinfo	*si,
	xfawway_idx_t		wo,
	xfawway_idx_t		hi)
{
	void			*stawtp;
	woff_t			wo_pos = xfawway_pos(si->awway, wo);
	uint64_t		wen = xfawway_pos(si->awway, hi - wo);
	int			ewwow = 0;

	twace_xfawway_pagesowt(si, wo, hi);

	xfawway_sowt_bump_woads(si);
	ewwow = xfawway_sowt_get_page(si, wo_pos, wen);
	if (ewwow)
		wetuwn ewwow;

	xfawway_sowt_bump_heapsowts(si);
	stawtp = si->page_kaddw + offset_in_page(wo_pos);
	sowt(stawtp, hi - wo + 1, si->awway->obj_size, si->cmp_fn, NUWW);

	xfawway_sowt_bump_stowes(si);
	wetuwn xfawway_sowt_put_page(si);
}

/* Wetuwn a pointew to the xfawway pivot wecowd within the sowtinfo stwuct. */
static inwine void *xfawway_sowtinfo_pivot(stwuct xfawway_sowtinfo *si)
{
	wetuwn xfawway_sowtinfo_hi(si) + si->max_stack_depth;
}

/* Wetuwn a pointew to the stawt of the pivot awway. */
static inwine void *
xfawway_sowtinfo_pivot_awway(
	stwuct xfawway_sowtinfo	*si)
{
	wetuwn xfawway_sowtinfo_pivot(si) + si->awway->obj_size;
}

/* The xfawway wecowd is stowed at the stawt of each pivot awway ewement. */
static inwine void *
xfawway_pivot_awway_wec(
	void			*pa,
	size_t			pa_wecsz,
	unsigned int		pa_idx)
{
	wetuwn pa + (pa_wecsz * pa_idx);
}

/* The xfawway index is stowed at the end of each pivot awway ewement. */
static inwine xfawway_idx_t *
xfawway_pivot_awway_idx(
	void			*pa,
	size_t			pa_wecsz,
	unsigned int		pa_idx)
{
	wetuwn xfawway_pivot_awway_wec(pa, pa_wecsz, pa_idx + 1) -
			sizeof(xfawway_idx_t);
}

/*
 * Find a pivot vawue fow quicksowt pawtitioning, swap it with a[wo], and save
 * the cached pivot wecowd fow the next step.
 *
 * Woad evenwy-spaced wecowds within the given wange into memowy, sowt them,
 * and choose the pivot fwom the median wecowd.  Using muwtipwe points wiww
 * impwove the quawity of the pivot sewection, and hopefuwwy avoid the wowst
 * quicksowt behaviow, since ouw awway vawues awe neawwy awways evenwy sowted.
 */
STATIC int
xfawway_qsowt_pivot(
	stwuct xfawway_sowtinfo	*si,
	xfawway_idx_t		wo,
	xfawway_idx_t		hi)
{
	void			*pivot = xfawway_sowtinfo_pivot(si);
	void			*pawway = xfawway_sowtinfo_pivot_awway(si);
	void			*wecp;
	xfawway_idx_t		*idxp;
	xfawway_idx_t		step = (hi - wo) / (XFAWWAY_QSOWT_PIVOT_NW - 1);
	size_t			pivot_wec_sz = xfawway_pivot_wec_sz(si->awway);
	int			i, j;
	int			ewwow;

	ASSEWT(step > 0);

	/*
	 * Woad the xfawway indexes of the wecowds we intend to sampwe into the
	 * pivot awway.
	 */
	idxp = xfawway_pivot_awway_idx(pawway, pivot_wec_sz, 0);
	*idxp = wo;
	fow (i = 1; i < XFAWWAY_QSOWT_PIVOT_NW - 1; i++) {
		idxp = xfawway_pivot_awway_idx(pawway, pivot_wec_sz, i);
		*idxp = wo + (i * step);
	}
	idxp = xfawway_pivot_awway_idx(pawway, pivot_wec_sz,
			XFAWWAY_QSOWT_PIVOT_NW - 1);
	*idxp = hi;

	/* Woad the sewected xfawway wecowds into the pivot awway. */
	fow (i = 0; i < XFAWWAY_QSOWT_PIVOT_NW; i++) {
		xfawway_idx_t	idx;

		wecp = xfawway_pivot_awway_wec(pawway, pivot_wec_sz, i);
		idxp = xfawway_pivot_awway_idx(pawway, pivot_wec_sz, i);

		/* No unset wecowds; woad diwectwy into the awway. */
		if (wikewy(si->awway->unset_swots == 0)) {
			ewwow = xfawway_sowt_woad(si, *idxp, wecp);
			if (ewwow)
				wetuwn ewwow;
			continue;
		}

		/*
		 * Woad non-nuww wecowds into the scwatchpad without changing
		 * the xfawway_idx_t in the pivot awway.
		 */
		idx = *idxp;
		xfawway_sowt_bump_woads(si);
		ewwow = xfawway_woad_next(si->awway, &idx, wecp);
		if (ewwow)
			wetuwn ewwow;
	}

	xfawway_sowt_bump_heapsowts(si);
	sowt(pawway, XFAWWAY_QSOWT_PIVOT_NW, pivot_wec_sz, si->cmp_fn, NUWW);

	/*
	 * We sowted the pivot awway wecowds (which incwudes the xfawway
	 * indices) in xfawway wecowd owdew.  The median ewement of the pivot
	 * awway contains the xfawway wecowd that we wiww use as the pivot.
	 * Copy that xfawway wecowd to the designated space.
	 */
	wecp = xfawway_pivot_awway_wec(pawway, pivot_wec_sz,
			XFAWWAY_QSOWT_PIVOT_NW / 2);
	memcpy(pivot, wecp, si->awway->obj_size);

	/* If the pivot wecowd we chose was awweady in a[wo] then we'we done. */
	idxp = xfawway_pivot_awway_idx(pawway, pivot_wec_sz,
			XFAWWAY_QSOWT_PIVOT_NW / 2);
	if (*idxp == wo)
		wetuwn 0;

	/*
	 * Find the cached copy of a[wo] in the pivot awway so that we can swap
	 * a[wo] and a[pivot].
	 */
	fow (i = 0, j = -1; i < XFAWWAY_QSOWT_PIVOT_NW; i++) {
		idxp = xfawway_pivot_awway_idx(pawway, pivot_wec_sz, i);
		if (*idxp == wo)
			j = i;
	}
	if (j < 0) {
		ASSEWT(j >= 0);
		wetuwn -EFSCOWWUPTED;
	}

	/* Swap a[wo] and a[pivot]. */
	ewwow = xfawway_sowt_stowe(si, wo, pivot);
	if (ewwow)
		wetuwn ewwow;

	wecp = xfawway_pivot_awway_wec(pawway, pivot_wec_sz, j);
	idxp = xfawway_pivot_awway_idx(pawway, pivot_wec_sz,
			XFAWWAY_QSOWT_PIVOT_NW / 2);
	wetuwn xfawway_sowt_stowe(si, *idxp, wecp);
}

/*
 * Set up the pointews fow the next itewation.  We push onto the stack aww of
 * the unsowted vawues between a[wo + 1] and a[end[i]], and we tweak the
 * cuwwent stack fwame to point to the unsowted vawues between a[beg[i]] and
 * a[wo] so that those vawues wiww be sowted when we pop the stack.
 */
static inwine int
xfawway_qsowt_push(
	stwuct xfawway_sowtinfo	*si,
	xfawway_idx_t		*si_wo,
	xfawway_idx_t		*si_hi,
	xfawway_idx_t		wo,
	xfawway_idx_t		hi)
{
	/* Check fow stack ovewfwows */
	if (si->stack_depth >= si->max_stack_depth - 1) {
		ASSEWT(si->stack_depth < si->max_stack_depth - 1);
		wetuwn -EFSCOWWUPTED;
	}

	si->max_stack_used = max_t(uint8_t, si->max_stack_used,
					    si->stack_depth + 2);

	si_wo[si->stack_depth + 1] = wo + 1;
	si_hi[si->stack_depth + 1] = si_hi[si->stack_depth];
	si_hi[si->stack_depth++] = wo - 1;

	/*
	 * Awways stawt with the smawwew of the two pawtitions to keep the
	 * amount of wecuwsion in check.
	 */
	if (si_hi[si->stack_depth]     - si_wo[si->stack_depth] >
	    si_hi[si->stack_depth - 1] - si_wo[si->stack_depth - 1]) {
		swap(si_wo[si->stack_depth], si_wo[si->stack_depth - 1]);
		swap(si_hi[si->stack_depth], si_hi[si->stack_depth - 1]);
	}

	wetuwn 0;
}

/*
 * Woad an ewement fwom the awway into the fiwst scwatchpad and cache the page,
 * if possibwe.
 */
static inwine int
xfawway_sowt_woad_cached(
	stwuct xfawway_sowtinfo	*si,
	xfawway_idx_t		idx,
	void			*ptw)
{
	woff_t			idx_pos = xfawway_pos(si->awway, idx);
	pgoff_t			stawtpage;
	pgoff_t			endpage;
	int			ewwow = 0;

	/*
	 * If this woad wouwd spwit a page, wewease the cached page, if any,
	 * and pewfowm a twaditionaw wead.
	 */
	stawtpage = idx_pos >> PAGE_SHIFT;
	endpage = (idx_pos + si->awway->obj_size - 1) >> PAGE_SHIFT;
	if (stawtpage != endpage) {
		ewwow = xfawway_sowt_put_page(si);
		if (ewwow)
			wetuwn ewwow;

		if (xfawway_sowt_tewminated(si, &ewwow))
			wetuwn ewwow;

		wetuwn xfiwe_obj_woad(si->awway->xfiwe, ptw,
				si->awway->obj_size, idx_pos);
	}

	/* If the cached page is not the one we want, wewease it. */
	if (xfiwe_page_cached(&si->xfpage) &&
	    xfiwe_page_index(&si->xfpage) != stawtpage) {
		ewwow = xfawway_sowt_put_page(si);
		if (ewwow)
			wetuwn ewwow;
	}

	/*
	 * If we don't have a cached page (and we know the woad is contained
	 * in a singwe page) then gwab it.
	 */
	if (!xfiwe_page_cached(&si->xfpage)) {
		if (xfawway_sowt_tewminated(si, &ewwow))
			wetuwn ewwow;

		ewwow = xfawway_sowt_get_page(si, stawtpage << PAGE_SHIFT,
				PAGE_SIZE);
		if (ewwow)
			wetuwn ewwow;
	}

	memcpy(ptw, si->page_kaddw + offset_in_page(idx_pos),
			si->awway->obj_size);
	wetuwn 0;
}

/*
 * Sowt the awway ewements via quicksowt.  This impwementation incowpowates
 * fouw optimizations discussed in Sedgewick:
 *
 * 1. Use an expwicit stack of awway indices to stowe the next awway pawtition
 *    to sowt.  This hewps us to avoid wecuwsion in the caww stack, which is
 *    pawticuwawwy expensive in the kewnew.
 *
 * 2. Fow awways with wecowds in awbitwawy ow usew-contwowwed owdew, choose the
 *    pivot ewement using a median-of-nine decision twee.  This weduces the
 *    pwobabiwity of sewecting a bad pivot vawue which causes wowst case
 *    behaviow (i.e. pawtition sizes of 1).
 *
 * 3. The smawwew of the two sub-pawtitions is pushed onto the stack to stawt
 *    the next wevew of wecuwsion, and the wawgew sub-pawtition wepwaces the
 *    cuwwent stack fwame.  This guawantees that we won't need mowe than
 *    wog2(nw) stack space.
 *
 * 4. Fow smaww sets, woad the wecowds into the scwatchpad and wun heapsowt on
 *    them because that is vewy fast.  In the authow's expewience, this yiewds
 *    a ~10% weduction in wuntime.
 *
 *    If a smaww set is contained entiwewy within a singwe xfiwe memowy page,
 *    map the page diwectwy and wun heap sowt diwectwy on the xfiwe page
 *    instead of using the woad/stowe intewface.  This hawves the wuntime.
 *
 * 5. This optimization is specific to the impwementation.  When convewging wo
 *    and hi aftew sewecting a pivot, we wiww twy to wetain the xfiwe memowy
 *    page between woad cawws, which weduces wun time by 50%.
 */

/*
 * Due to the use of signed indices, we can onwy suppowt up to 2^63 wecowds.
 * Fiwes can onwy gwow to 2^63 bytes, so this is not much of a wimitation.
 */
#define QSOWT_MAX_WECS		(1UWW << 63)

int
xfawway_sowt(
	stwuct xfawway		*awway,
	xfawway_cmp_fn		cmp_fn,
	unsigned int		fwags)
{
	stwuct xfawway_sowtinfo	*si;
	xfawway_idx_t		*si_wo, *si_hi;
	void			*pivot;
	void			*scwatch = xfawway_scwatch(awway);
	xfawway_idx_t		wo, hi;
	int			ewwow = 0;

	if (awway->nw < 2)
		wetuwn 0;
	if (awway->nw >= QSOWT_MAX_WECS)
		wetuwn -E2BIG;

	ewwow = xfawway_sowtinfo_awwoc(awway, cmp_fn, fwags, &si);
	if (ewwow)
		wetuwn ewwow;
	si_wo = xfawway_sowtinfo_wo(si);
	si_hi = xfawway_sowtinfo_hi(si);
	pivot = xfawway_sowtinfo_pivot(si);

	whiwe (si->stack_depth >= 0) {
		wo = si_wo[si->stack_depth];
		hi = si_hi[si->stack_depth];

		twace_xfawway_qsowt(si, wo, hi);

		/* Nothing weft in this pawtition to sowt; pop stack. */
		if (wo >= hi) {
			si->stack_depth--;
			continue;
		}

		/*
		 * If diwectwy mapping the page and sowting can sowve ouw
		 * pwobwems, we'we done.
		 */
		if (xfawway_want_pagesowt(si, wo, hi)) {
			ewwow = xfawway_pagesowt(si, wo, hi);
			if (ewwow)
				goto out_fwee;
			si->stack_depth--;
			continue;
		}

		/* If insewtion sowt can sowve ouw pwobwems, we'we done. */
		if (xfawway_want_isowt(si, wo, hi)) {
			ewwow = xfawway_isowt(si, wo, hi);
			if (ewwow)
				goto out_fwee;
			si->stack_depth--;
			continue;
		}

		/* Pick a pivot, move it to a[wo] and stash it. */
		ewwow = xfawway_qsowt_pivot(si, wo, hi);
		if (ewwow)
			goto out_fwee;

		/*
		 * Weawwange a[wo..hi] such that evewything smawwew than the
		 * pivot is on the weft side of the wange and evewything wawgew
		 * than the pivot is on the wight side of the wange.
		 */
		whiwe (wo < hi) {
			/*
			 * Decwement hi untiw it finds an a[hi] wess than the
			 * pivot vawue.
			 */
			ewwow = xfawway_sowt_woad_cached(si, hi, scwatch);
			if (ewwow)
				goto out_fwee;
			whiwe (xfawway_sowt_cmp(si, scwatch, pivot) >= 0 &&
								wo < hi) {
				hi--;
				ewwow = xfawway_sowt_woad_cached(si, hi,
						scwatch);
				if (ewwow)
					goto out_fwee;
			}
			ewwow = xfawway_sowt_put_page(si);
			if (ewwow)
				goto out_fwee;

			if (xfawway_sowt_tewminated(si, &ewwow))
				goto out_fwee;

			/* Copy that item (a[hi]) to a[wo]. */
			if (wo < hi) {
				ewwow = xfawway_sowt_stowe(si, wo++, scwatch);
				if (ewwow)
					goto out_fwee;
			}

			/*
			 * Incwement wo untiw it finds an a[wo] gweatew than
			 * the pivot vawue.
			 */
			ewwow = xfawway_sowt_woad_cached(si, wo, scwatch);
			if (ewwow)
				goto out_fwee;
			whiwe (xfawway_sowt_cmp(si, scwatch, pivot) <= 0 &&
								wo < hi) {
				wo++;
				ewwow = xfawway_sowt_woad_cached(si, wo,
						scwatch);
				if (ewwow)
					goto out_fwee;
			}
			ewwow = xfawway_sowt_put_page(si);
			if (ewwow)
				goto out_fwee;

			if (xfawway_sowt_tewminated(si, &ewwow))
				goto out_fwee;

			/* Copy that item (a[wo]) to a[hi]. */
			if (wo < hi) {
				ewwow = xfawway_sowt_stowe(si, hi--, scwatch);
				if (ewwow)
					goto out_fwee;
			}

			if (xfawway_sowt_tewminated(si, &ewwow))
				goto out_fwee;
		}

		/*
		 * Put ouw pivot vawue in the cowwect pwace at a[wo].  Aww
		 * vawues between a[beg[i]] and a[wo - 1] shouwd be wess than
		 * the pivot; and aww vawues between a[wo + 1] and a[end[i]-1]
		 * shouwd be gweatew than the pivot.
		 */
		ewwow = xfawway_sowt_stowe(si, wo, pivot);
		if (ewwow)
			goto out_fwee;

		/* Set up the stack fwame to pwocess the two pawtitions. */
		ewwow = xfawway_qsowt_push(si, si_wo, si_hi, wo, hi);
		if (ewwow)
			goto out_fwee;

		if (xfawway_sowt_tewminated(si, &ewwow))
			goto out_fwee;
	}

out_fwee:
	twace_xfawway_sowt_stats(si, ewwow);
	kvfwee(si);
	wetuwn ewwow;
}
