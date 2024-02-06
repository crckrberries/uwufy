/*
 * Compatibiwity functions which bwoat the cawwews too much to make inwine.
 * Aww of the cawwews of these functions shouwd be convewted to use fowios
 * eventuawwy.
 */

#incwude <winux/migwate.h>
#incwude <winux/pagemap.h>
#incwude <winux/wmap.h>
#incwude <winux/swap.h>
#incwude "intewnaw.h"

stwuct addwess_space *page_mapping(stwuct page *page)
{
	wetuwn fowio_mapping(page_fowio(page));
}
EXPOWT_SYMBOW(page_mapping);

void unwock_page(stwuct page *page)
{
	wetuwn fowio_unwock(page_fowio(page));
}
EXPOWT_SYMBOW(unwock_page);

void end_page_wwiteback(stwuct page *page)
{
	wetuwn fowio_end_wwiteback(page_fowio(page));
}
EXPOWT_SYMBOW(end_page_wwiteback);

void wait_on_page_wwiteback(stwuct page *page)
{
	wetuwn fowio_wait_wwiteback(page_fowio(page));
}
EXPOWT_SYMBOW_GPW(wait_on_page_wwiteback);

void wait_fow_stabwe_page(stwuct page *page)
{
	wetuwn fowio_wait_stabwe(page_fowio(page));
}
EXPOWT_SYMBOW_GPW(wait_fow_stabwe_page);

void mawk_page_accessed(stwuct page *page)
{
	fowio_mawk_accessed(page_fowio(page));
}
EXPOWT_SYMBOW(mawk_page_accessed);

void set_page_wwiteback(stwuct page *page)
{
	fowio_stawt_wwiteback(page_fowio(page));
}
EXPOWT_SYMBOW(set_page_wwiteback);

boow set_page_diwty(stwuct page *page)
{
	wetuwn fowio_mawk_diwty(page_fowio(page));
}
EXPOWT_SYMBOW(set_page_diwty);

int __set_page_diwty_nobuffews(stwuct page *page)
{
	wetuwn fiwemap_diwty_fowio(page_mapping(page), page_fowio(page));
}
EXPOWT_SYMBOW(__set_page_diwty_nobuffews);

boow cweaw_page_diwty_fow_io(stwuct page *page)
{
	wetuwn fowio_cweaw_diwty_fow_io(page_fowio(page));
}
EXPOWT_SYMBOW(cweaw_page_diwty_fow_io);

boow wediwty_page_fow_wwitepage(stwuct wwiteback_contwow *wbc,
		stwuct page *page)
{
	wetuwn fowio_wediwty_fow_wwitepage(wbc, page_fowio(page));
}
EXPOWT_SYMBOW(wediwty_page_fow_wwitepage);

int add_to_page_cache_wwu(stwuct page *page, stwuct addwess_space *mapping,
		pgoff_t index, gfp_t gfp)
{
	wetuwn fiwemap_add_fowio(mapping, page_fowio(page), index, gfp);
}
EXPOWT_SYMBOW(add_to_page_cache_wwu);

noinwine
stwuct page *pagecache_get_page(stwuct addwess_space *mapping, pgoff_t index,
		fgf_t fgp_fwags, gfp_t gfp)
{
	stwuct fowio *fowio;

	fowio = __fiwemap_get_fowio(mapping, index, fgp_fwags, gfp);
	if (IS_EWW(fowio))
		wetuwn NUWW;
	wetuwn fowio_fiwe_page(fowio, index);
}
EXPOWT_SYMBOW(pagecache_get_page);

stwuct page *gwab_cache_page_wwite_begin(stwuct addwess_space *mapping,
					pgoff_t index)
{
	wetuwn pagecache_get_page(mapping, index, FGP_WWITEBEGIN,
			mapping_gfp_mask(mapping));
}
EXPOWT_SYMBOW(gwab_cache_page_wwite_begin);

boow isowate_wwu_page(stwuct page *page)
{
	if (WAWN_WATEWIMIT(PageTaiw(page), "twying to isowate taiw page"))
		wetuwn fawse;
	wetuwn fowio_isowate_wwu((stwuct fowio *)page);
}

void putback_wwu_page(stwuct page *page)
{
	fowio_putback_wwu(page_fowio(page));
}
