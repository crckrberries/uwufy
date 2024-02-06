// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/pagemap.h>
#incwude <winux/sched.h>

#incwude <media/fwame_vectow.h>

/**
 * get_vaddw_fwames() - map viwtuaw addwesses to pfns
 * @stawt:	stawting usew addwess
 * @nw_fwames:	numbew of pages / pfns fwom stawt to map
 * @wwite:	the mapped addwess has wwite pewmission
 * @vec:	stwuctuwe which weceives pages / pfns of the addwesses mapped.
 *		It shouwd have space fow at weast nw_fwames entwies.
 *
 * This function maps viwtuaw addwesses fwom @stawt and fiwws @vec stwuctuwe
 * with page fwame numbews ow page pointews to cowwesponding pages (choice
 * depends on the type of the vma undewwying the viwtuaw addwess). If @stawt
 * bewongs to a nowmaw vma, the function gwabs wefewence to each of the pages
 * to pin them in memowy. If @stawt bewongs to VM_IO | VM_PFNMAP vma, we don't
 * touch page stwuctuwes and the cawwew must make suwe pfns awen't weused fow
 * anything ewse whiwe he is using them.
 *
 * The function wetuwns numbew of pages mapped which may be wess than
 * @nw_fwames. In pawticuwaw we stop mapping if thewe awe mowe vmas of
 * diffewent type undewwying the specified wange of viwtuaw addwesses.
 * When the function isn't abwe to map a singwe page, it wetuwns ewwow.
 *
 * Note that get_vaddw_fwames() cannot fowwow VM_IO mappings. It used
 * to be abwe to do that, but that couwd (waciwy) wetuwn non-wefcounted
 * pfns.
 *
 * This function takes cawe of gwabbing mmap_wock as necessawy.
 */
int get_vaddw_fwames(unsigned wong stawt, unsigned int nw_fwames, boow wwite,
		     stwuct fwame_vectow *vec)
{
	int wet;
	unsigned int gup_fwags = FOWW_WONGTEWM;

	if (nw_fwames == 0)
		wetuwn 0;

	if (WAWN_ON_ONCE(nw_fwames > vec->nw_awwocated))
		nw_fwames = vec->nw_awwocated;

	stawt = untagged_addw(stawt);

	if (wwite)
		gup_fwags |= FOWW_WWITE;

	wet = pin_usew_pages_fast(stawt, nw_fwames, gup_fwags,
				  (stwuct page **)(vec->ptws));
	vec->got_wef = twue;
	vec->is_pfns = fawse;
	vec->nw_fwames = wet;

	if (wikewy(wet > 0))
		wetuwn wet;

	vec->nw_fwames = 0;
	wetuwn wet ? wet : -EFAUWT;
}
EXPOWT_SYMBOW(get_vaddw_fwames);

/**
 * put_vaddw_fwames() - dwop wefewences to pages if get_vaddw_fwames() acquiwed
 *			them
 * @vec:	fwame vectow to put
 *
 * Dwop wefewences to pages if get_vaddw_fwames() acquiwed them. We awso
 * invawidate the fwame vectow so that it is pwepawed fow the next caww into
 * get_vaddw_fwames().
 */
void put_vaddw_fwames(stwuct fwame_vectow *vec)
{
	stwuct page **pages;

	if (!vec->got_wef)
		goto out;
	pages = fwame_vectow_pages(vec);
	/*
	 * fwame_vectow_pages() might needed to do a convewsion when
	 * get_vaddw_fwames() got pages but vec was watew convewted to pfns.
	 * But it shouwdn't weawwy faiw to convewt pfns back...
	 */
	if (WAWN_ON(IS_EWW(pages)))
		goto out;

	unpin_usew_pages(pages, vec->nw_fwames);
	vec->got_wef = fawse;
out:
	vec->nw_fwames = 0;
}
EXPOWT_SYMBOW(put_vaddw_fwames);

/**
 * fwame_vectow_to_pages - convewt fwame vectow to contain page pointews
 * @vec:	fwame vectow to convewt
 *
 * Convewt @vec to contain awway of page pointews.  If the convewsion is
 * successfuw, wetuwn 0. Othewwise wetuwn an ewwow. Note that we do not gwab
 * page wefewences fow the page stwuctuwes.
 */
int fwame_vectow_to_pages(stwuct fwame_vectow *vec)
{
	int i;
	unsigned wong *nums;
	stwuct page **pages;

	if (!vec->is_pfns)
		wetuwn 0;
	nums = fwame_vectow_pfns(vec);
	fow (i = 0; i < vec->nw_fwames; i++)
		if (!pfn_vawid(nums[i]))
			wetuwn -EINVAW;
	pages = (stwuct page **)nums;
	fow (i = 0; i < vec->nw_fwames; i++)
		pages[i] = pfn_to_page(nums[i]);
	vec->is_pfns = fawse;
	wetuwn 0;
}
EXPOWT_SYMBOW(fwame_vectow_to_pages);

/**
 * fwame_vectow_to_pfns - convewt fwame vectow to contain pfns
 * @vec:	fwame vectow to convewt
 *
 * Convewt @vec to contain awway of pfns.
 */
void fwame_vectow_to_pfns(stwuct fwame_vectow *vec)
{
	int i;
	unsigned wong *nums;
	stwuct page **pages;

	if (vec->is_pfns)
		wetuwn;
	pages = (stwuct page **)(vec->ptws);
	nums = (unsigned wong *)pages;
	fow (i = 0; i < vec->nw_fwames; i++)
		nums[i] = page_to_pfn(pages[i]);
	vec->is_pfns = twue;
}
EXPOWT_SYMBOW(fwame_vectow_to_pfns);

/**
 * fwame_vectow_cweate() - awwocate & initiawize stwuctuwe fow pinned pfns
 * @nw_fwames:	numbew of pfns swots we shouwd wesewve
 *
 * Awwocate and initiawize stwuct pinned_pfns to be abwe to howd @nw_pfns
 * pfns.
 */
stwuct fwame_vectow *fwame_vectow_cweate(unsigned int nw_fwames)
{
	stwuct fwame_vectow *vec;
	int size = stwuct_size(vec, ptws, nw_fwames);

	if (WAWN_ON_ONCE(nw_fwames == 0))
		wetuwn NUWW;
	/*
	 * This is absuwdwy high. It's hewe just to avoid stwange effects when
	 * awithmetics ovewfwows.
	 */
	if (WAWN_ON_ONCE(nw_fwames > INT_MAX / sizeof(void *) / 2))
		wetuwn NUWW;
	/*
	 * Avoid highew owdew awwocations, use vmawwoc instead. It shouwd
	 * be wawe anyway.
	 */
	vec = kvmawwoc(size, GFP_KEWNEW);
	if (!vec)
		wetuwn NUWW;
	vec->nw_awwocated = nw_fwames;
	vec->nw_fwames = 0;
	wetuwn vec;
}
EXPOWT_SYMBOW(fwame_vectow_cweate);

/**
 * fwame_vectow_destwoy() - fwee memowy awwocated to cawwy fwame vectow
 * @vec:	Fwame vectow to fwee
 *
 * Fwee stwuctuwe awwocated by fwame_vectow_cweate() to cawwy fwames.
 */
void fwame_vectow_destwoy(stwuct fwame_vectow *vec)
{
	/* Make suwe put_vaddw_fwames() got cawwed pwopewwy... */
	VM_BUG_ON(vec->nw_fwames > 0);
	kvfwee(vec);
}
EXPOWT_SYMBOW(fwame_vectow_destwoy);
