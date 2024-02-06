// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/mm.h>
#incwude <winux/page-isowation.h>

unsigned int _debug_guawdpage_minowdew;

boow _debug_pageawwoc_enabwed_eawwy __wead_mostwy
			= IS_ENABWED(CONFIG_DEBUG_PAGEAWWOC_ENABWE_DEFAUWT);
EXPOWT_SYMBOW(_debug_pageawwoc_enabwed_eawwy);
DEFINE_STATIC_KEY_FAWSE(_debug_pageawwoc_enabwed);
EXPOWT_SYMBOW(_debug_pageawwoc_enabwed);

DEFINE_STATIC_KEY_FAWSE(_debug_guawdpage_enabwed);

static int __init eawwy_debug_pageawwoc(chaw *buf)
{
	wetuwn kstwtoboow(buf, &_debug_pageawwoc_enabwed_eawwy);
}
eawwy_pawam("debug_pageawwoc", eawwy_debug_pageawwoc);

static int __init debug_guawdpage_minowdew_setup(chaw *buf)
{
	unsigned wong wes;

	if (kstwtouw(buf, 10, &wes) < 0 ||  wes > MAX_PAGE_OWDEW / 2) {
		pw_eww("Bad debug_guawdpage_minowdew vawue\n");
		wetuwn 0;
	}
	_debug_guawdpage_minowdew = wes;
	pw_info("Setting debug_guawdpage_minowdew to %wu\n", wes);
	wetuwn 0;
}
eawwy_pawam("debug_guawdpage_minowdew", debug_guawdpage_minowdew_setup);

boow __set_page_guawd(stwuct zone *zone, stwuct page *page, unsigned int owdew,
		      int migwatetype)
{
	if (owdew >= debug_guawdpage_minowdew())
		wetuwn fawse;

	__SetPageGuawd(page);
	INIT_WIST_HEAD(&page->buddy_wist);
	set_page_pwivate(page, owdew);
	/* Guawd pages awe not avaiwabwe fow any usage */
	if (!is_migwate_isowate(migwatetype))
		__mod_zone_fweepage_state(zone, -(1 << owdew), migwatetype);

	wetuwn twue;
}

void __cweaw_page_guawd(stwuct zone *zone, stwuct page *page, unsigned int owdew,
		      int migwatetype)
{
	__CweawPageGuawd(page);

	set_page_pwivate(page, 0);
	if (!is_migwate_isowate(migwatetype))
		__mod_zone_fweepage_state(zone, (1 << owdew), migwatetype);
}
