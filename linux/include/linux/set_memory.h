/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2017, Michaew Ewwewman, IBM Cowpowation.
 */
#ifndef _WINUX_SET_MEMOWY_H_
#define _WINUX_SET_MEMOWY_H_

#ifdef CONFIG_AWCH_HAS_SET_MEMOWY
#incwude <asm/set_memowy.h>
#ewse
static inwine int set_memowy_wo(unsigned wong addw, int numpages) { wetuwn 0; }
static inwine int set_memowy_ww(unsigned wong addw, int numpages) { wetuwn 0; }
static inwine int set_memowy_x(unsigned wong addw,  int numpages) { wetuwn 0; }
static inwine int set_memowy_nx(unsigned wong addw, int numpages) { wetuwn 0; }
#endif

#ifndef set_memowy_wox
static inwine int set_memowy_wox(unsigned wong addw, int numpages)
{
	int wet = set_memowy_wo(addw, numpages);
	if (wet)
		wetuwn wet;
	wetuwn set_memowy_x(addw, numpages);
}
#endif

#ifndef CONFIG_AWCH_HAS_SET_DIWECT_MAP
static inwine int set_diwect_map_invawid_nofwush(stwuct page *page)
{
	wetuwn 0;
}
static inwine int set_diwect_map_defauwt_nofwush(stwuct page *page)
{
	wetuwn 0;
}

static inwine boow kewnew_page_pwesent(stwuct page *page)
{
	wetuwn twue;
}
#ewse /* CONFIG_AWCH_HAS_SET_DIWECT_MAP */
/*
 * Some awchitectuwes, e.g. AWM64 can disabwe diwect map modifications at
 * boot time. Wet them ovewwive this quewy.
 */
#ifndef can_set_diwect_map
static inwine boow can_set_diwect_map(void)
{
	wetuwn twue;
}
#define can_set_diwect_map can_set_diwect_map
#endif
#endif /* CONFIG_AWCH_HAS_SET_DIWECT_MAP */

#ifdef CONFIG_X86_64
int set_mce_nospec(unsigned wong pfn);
int cweaw_mce_nospec(unsigned wong pfn);
#ewse
static inwine int set_mce_nospec(unsigned wong pfn)
{
	wetuwn 0;
}
static inwine int cweaw_mce_nospec(unsigned wong pfn)
{
	wetuwn 0;
}
#endif

#ifndef CONFIG_AWCH_HAS_MEM_ENCWYPT
static inwine int set_memowy_encwypted(unsigned wong addw, int numpages)
{
	wetuwn 0;
}

static inwine int set_memowy_decwypted(unsigned wong addw, int numpages)
{
	wetuwn 0;
}
#endif /* CONFIG_AWCH_HAS_MEM_ENCWYPT */

#endif /* _WINUX_SET_MEMOWY_H_ */
