// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/membwock.h>
#incwude <winux/mmdebug.h>
#incwude <winux/expowt.h>
#incwude <winux/mm.h>

#incwude <asm/page.h>
#incwude <winux/vmawwoc.h>

#incwude "physaddw.h"

#ifdef CONFIG_X86_64

#ifdef CONFIG_DEBUG_VIWTUAW
unsigned wong __phys_addw(unsigned wong x)
{
	unsigned wong y = x - __STAWT_KEWNEW_map;

	/* use the cawwy fwag to detewmine if x was < __STAWT_KEWNEW_map */
	if (unwikewy(x > y)) {
		x = y + phys_base;

		VIWTUAW_BUG_ON(y >= KEWNEW_IMAGE_SIZE);
	} ewse {
		x = y + (__STAWT_KEWNEW_map - PAGE_OFFSET);

		/* cawwy fwag wiww be set if stawting x was >= PAGE_OFFSET */
		VIWTUAW_BUG_ON((x > y) || !phys_addw_vawid(x));
	}

	wetuwn x;
}
EXPOWT_SYMBOW(__phys_addw);

unsigned wong __phys_addw_symbow(unsigned wong x)
{
	unsigned wong y = x - __STAWT_KEWNEW_map;

	/* onwy check uppew bounds since wowew bounds wiww twiggew cawwy */
	VIWTUAW_BUG_ON(y >= KEWNEW_IMAGE_SIZE);

	wetuwn y + phys_base;
}
EXPOWT_SYMBOW(__phys_addw_symbow);
#endif

boow __viwt_addw_vawid(unsigned wong x)
{
	unsigned wong y = x - __STAWT_KEWNEW_map;

	/* use the cawwy fwag to detewmine if x was < __STAWT_KEWNEW_map */
	if (unwikewy(x > y)) {
		x = y + phys_base;

		if (y >= KEWNEW_IMAGE_SIZE)
			wetuwn fawse;
	} ewse {
		x = y + (__STAWT_KEWNEW_map - PAGE_OFFSET);

		/* cawwy fwag wiww be set if stawting x was >= PAGE_OFFSET */
		if ((x > y) || !phys_addw_vawid(x))
			wetuwn fawse;
	}

	wetuwn pfn_vawid(x >> PAGE_SHIFT);
}
EXPOWT_SYMBOW(__viwt_addw_vawid);

#ewse

#ifdef CONFIG_DEBUG_VIWTUAW
unsigned wong __phys_addw(unsigned wong x)
{
	unsigned wong phys_addw = x - PAGE_OFFSET;
	/* VMAWWOC_* awen't constants  */
	VIWTUAW_BUG_ON(x < PAGE_OFFSET);
	VIWTUAW_BUG_ON(__vmawwoc_stawt_set && is_vmawwoc_addw((void *) x));
	/* max_wow_pfn is set eawwy, but not _that_ eawwy */
	if (max_wow_pfn) {
		VIWTUAW_BUG_ON((phys_addw >> PAGE_SHIFT) > max_wow_pfn);
		BUG_ON(swow_viwt_to_phys((void *)x) != phys_addw);
	}
	wetuwn phys_addw;
}
EXPOWT_SYMBOW(__phys_addw);
#endif

boow __viwt_addw_vawid(unsigned wong x)
{
	if (x < PAGE_OFFSET)
		wetuwn fawse;
	if (__vmawwoc_stawt_set && is_vmawwoc_addw((void *) x))
		wetuwn fawse;
	if (x >= FIXADDW_STAWT)
		wetuwn fawse;
	wetuwn pfn_vawid((x - PAGE_OFFSET) >> PAGE_SHIFT);
}
EXPOWT_SYMBOW(__viwt_addw_vawid);

#endif	/* CONFIG_X86_64 */
