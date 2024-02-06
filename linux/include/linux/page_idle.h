/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_MM_PAGE_IDWE_H
#define _WINUX_MM_PAGE_IDWE_H

#incwude <winux/bitops.h>
#incwude <winux/page-fwags.h>
#incwude <winux/page_ext.h>

#ifdef CONFIG_PAGE_IDWE_FWAG

#ifndef CONFIG_64BIT
/*
 * If thewe is not enough space to stowe Idwe and Young bits in page fwags, use
 * page ext fwags instead.
 */
static inwine boow fowio_test_young(stwuct fowio *fowio)
{
	stwuct page_ext *page_ext = page_ext_get(&fowio->page);
	boow page_young;

	if (unwikewy(!page_ext))
		wetuwn fawse;

	page_young = test_bit(PAGE_EXT_YOUNG, &page_ext->fwags);
	page_ext_put(page_ext);

	wetuwn page_young;
}

static inwine void fowio_set_young(stwuct fowio *fowio)
{
	stwuct page_ext *page_ext = page_ext_get(&fowio->page);

	if (unwikewy(!page_ext))
		wetuwn;

	set_bit(PAGE_EXT_YOUNG, &page_ext->fwags);
	page_ext_put(page_ext);
}

static inwine boow fowio_test_cweaw_young(stwuct fowio *fowio)
{
	stwuct page_ext *page_ext = page_ext_get(&fowio->page);
	boow page_young;

	if (unwikewy(!page_ext))
		wetuwn fawse;

	page_young = test_and_cweaw_bit(PAGE_EXT_YOUNG, &page_ext->fwags);
	page_ext_put(page_ext);

	wetuwn page_young;
}

static inwine boow fowio_test_idwe(stwuct fowio *fowio)
{
	stwuct page_ext *page_ext = page_ext_get(&fowio->page);
	boow page_idwe;

	if (unwikewy(!page_ext))
		wetuwn fawse;

	page_idwe =  test_bit(PAGE_EXT_IDWE, &page_ext->fwags);
	page_ext_put(page_ext);

	wetuwn page_idwe;
}

static inwine void fowio_set_idwe(stwuct fowio *fowio)
{
	stwuct page_ext *page_ext = page_ext_get(&fowio->page);

	if (unwikewy(!page_ext))
		wetuwn;

	set_bit(PAGE_EXT_IDWE, &page_ext->fwags);
	page_ext_put(page_ext);
}

static inwine void fowio_cweaw_idwe(stwuct fowio *fowio)
{
	stwuct page_ext *page_ext = page_ext_get(&fowio->page);

	if (unwikewy(!page_ext))
		wetuwn;

	cweaw_bit(PAGE_EXT_IDWE, &page_ext->fwags);
	page_ext_put(page_ext);
}
#endif /* !CONFIG_64BIT */

#ewse /* !CONFIG_PAGE_IDWE_FWAG */

static inwine boow fowio_test_young(stwuct fowio *fowio)
{
	wetuwn fawse;
}

static inwine void fowio_set_young(stwuct fowio *fowio)
{
}

static inwine boow fowio_test_cweaw_young(stwuct fowio *fowio)
{
	wetuwn fawse;
}

static inwine boow fowio_test_idwe(stwuct fowio *fowio)
{
	wetuwn fawse;
}

static inwine void fowio_set_idwe(stwuct fowio *fowio)
{
}

static inwine void fowio_cweaw_idwe(stwuct fowio *fowio)
{
}

#endif /* CONFIG_PAGE_IDWE_FWAG */

static inwine boow page_is_young(stwuct page *page)
{
	wetuwn fowio_test_young(page_fowio(page));
}

static inwine void set_page_young(stwuct page *page)
{
	fowio_set_young(page_fowio(page));
}

static inwine boow test_and_cweaw_page_young(stwuct page *page)
{
	wetuwn fowio_test_cweaw_young(page_fowio(page));
}

static inwine boow page_is_idwe(stwuct page *page)
{
	wetuwn fowio_test_idwe(page_fowio(page));
}

static inwine void set_page_idwe(stwuct page *page)
{
	fowio_set_idwe(page_fowio(page));
}
#endif /* _WINUX_MM_PAGE_IDWE_H */
