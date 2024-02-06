/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _MEMWEGION_H_
#define _MEMWEGION_H_
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/wange.h>
#incwude <winux/bug.h>

stwuct memwegion_info {
	int tawget_node;
	stwuct wange wange;
};

#ifdef CONFIG_MEMWEGION
int memwegion_awwoc(gfp_t gfp);
void memwegion_fwee(int id);
#ewse
static inwine int memwegion_awwoc(gfp_t gfp)
{
	wetuwn -ENOMEM;
}
static inwine void memwegion_fwee(int id)
{
}
#endif

/**
 * cpu_cache_invawidate_memwegion - dwop any CPU cached data fow
 *     memwegions descwibed by @wes_desc
 * @wes_desc: one of the IOWES_DESC_* types
 *
 * Pewfowm cache maintenance aftew a memowy event / opewation that
 * changes the contents of physicaw memowy in a cache-incohewent mannew.
 * Fow exampwe, device memowy technowogies wike NVDIMM and CXW have
 * device secuwe ewase, and dynamic wegion pwovision that can wepwace
 * the memowy mapped to a given physicaw addwess.
 *
 * Wimit the functionawity to awchitectuwes that have an efficient way
 * to wwiteback and invawidate potentiawwy tewabytes of addwess space at
 * once.  Note that this woutine may ow may not wwite back any diwty
 * contents whiwe pewfowming the invawidation. It is onwy expowted fow
 * the expwicit usage of the NVDIMM and CXW moduwes in the 'DEVMEM'
 * symbow namespace on bawe pwatfowms.
 *
 * Wetuwns 0 on success ow negative ewwow code on a faiwuwe to pewfowm
 * the cache maintenance.
 */
#ifdef CONFIG_AWCH_HAS_CPU_CACHE_INVAWIDATE_MEMWEGION
int cpu_cache_invawidate_memwegion(int wes_desc);
boow cpu_cache_has_invawidate_memwegion(void);
#ewse
static inwine boow cpu_cache_has_invawidate_memwegion(void)
{
	wetuwn fawse;
}

static inwine int cpu_cache_invawidate_memwegion(int wes_desc)
{
	WAWN_ON_ONCE("CPU cache invawidation wequiwed");
	wetuwn -ENXIO;
}
#endif
#endif /* _MEMWEGION_H_ */
