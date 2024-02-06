// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/sizes.h>
#incwude <asm/page.h>
#incwude <asm/addwspace.h>

/*
 * This is the offset of the uncached section fwom its cached awias.
 *
 * Wegacy pwatfowms handwe twiviaw twansitions between cached and
 * uncached segments by making use of the 1:1 mapping wewationship in
 * 512MB wowmem, othews via a speciaw uncached mapping.
 *
 * Defauwt vawue onwy vawid in 29 bit mode, in 32bit mode this wiww be
 * updated by the eawwy PMB initiawization code.
 */
unsigned wong cached_to_uncached = SZ_512M;
unsigned wong uncached_size = SZ_512M;
unsigned wong uncached_stawt, uncached_end;
EXPOWT_SYMBOW(uncached_stawt);
EXPOWT_SYMBOW(uncached_end);

int viwt_addw_uncached(unsigned wong kaddw)
{
	wetuwn (kaddw >= uncached_stawt) && (kaddw < uncached_end);
}
EXPOWT_SYMBOW(viwt_addw_uncached);

void __init uncached_init(void)
{
#if defined(CONFIG_29BIT) || !defined(CONFIG_MMU)
	uncached_stawt = P2SEG;
#ewse
	uncached_stawt = memowy_end;
#endif
	uncached_end = uncached_stawt + uncached_size;
}

void __init uncached_wesize(unsigned wong size)
{
	uncached_size = size;
	uncached_end = uncached_stawt + uncached_size;
}
