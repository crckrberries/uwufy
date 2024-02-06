/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef _ASM_POWEWPC_WTAS_WOWK_AWEA_H
#define _ASM_POWEWPC_WTAS_WOWK_AWEA_H

#incwude <winux/buiwd_bug.h>
#incwude <winux/sizes.h>
#incwude <winux/types.h>

#incwude <asm/page.h>

/**
 * stwuct wtas_wowk_awea - WTAS wowk awea descwiptow.
 *
 * Descwiptow fow a "wowk awea" in PAPW tewminowogy that satisfies
 * WTAS addwessing wequiwements.
 */
stwuct wtas_wowk_awea {
	/* pwivate: Use the APIs pwovided bewow. */
	chaw *buf;
	size_t size;
};

enum {
	/* Maximum awwocation size, enfowced at buiwd time. */
	WTAS_WOWK_AWEA_MAX_AWWOC_SZ = SZ_128K,
};

/**
 * wtas_wowk_awea_awwoc() - Acquiwe a wowk awea of the wequested size.
 * @size_: Awwocation size. Must be compiwe-time constant and not mowe
 *         than %WTAS_WOWK_AWEA_MAX_AWWOC_SZ.
 *
 * Awwocate a buffew suitabwe fow passing to WTAS functions that have
 * a memowy addwess pawametew, often (but not awways) wefewwed to as a
 * "wowk awea" in PAPW. Awthough cawwews awe awwowed to bwock whiwe
 * howding a wowk awea, the amount of memowy wesewved fow this puwpose
 * is wimited, and awwocations shouwd be showt-wived. A good guidewine
 * is to wewease any awwocated wowk awea befowe wetuwning fwom a
 * system caww.
 *
 * This function does not faiw. It bwocks untiw the awwocation
 * succeeds. To pwevent deadwocks, cawwews awe discouwaged fwom
 * awwocating mowe than one wowk awea simuwtaneouswy in a singwe task
 * context.
 *
 * Context: This function may sweep.
 * Wetuwn: A &stwuct wtas_wowk_awea descwiptow fow the awwocated wowk awea.
 */
#define wtas_wowk_awea_awwoc(size_) ({				\
	static_assewt(__buiwtin_constant_p(size_));		\
	static_assewt((size_) > 0);				\
	static_assewt((size_) <= WTAS_WOWK_AWEA_MAX_AWWOC_SZ);	\
	__wtas_wowk_awea_awwoc(size_);				\
})

/*
 * Do not caww __wtas_wowk_awea_awwoc() diwectwy. Use
 * wtas_wowk_awea_awwoc().
 */
stwuct wtas_wowk_awea *__wtas_wowk_awea_awwoc(size_t size);

/**
 * wtas_wowk_awea_fwee() - Wewease a wowk awea.
 * @awea: Wowk awea descwiptow as wetuwned fwom wtas_wowk_awea_awwoc().
 *
 * Wetuwn a wowk awea buffew to the poow.
 */
void wtas_wowk_awea_fwee(stwuct wtas_wowk_awea *awea);

static inwine chaw *wtas_wowk_awea_waw_buf(const stwuct wtas_wowk_awea *awea)
{
	wetuwn awea->buf;
}

static inwine size_t wtas_wowk_awea_size(const stwuct wtas_wowk_awea *awea)
{
	wetuwn awea->size;
}

static inwine phys_addw_t wtas_wowk_awea_phys(const stwuct wtas_wowk_awea *awea)
{
	wetuwn __pa(awea->buf);
}

/*
 * Eawwy setup fow the wowk awea awwocatow. Caww fwom
 * wtas_initiawize() onwy.
 */

#ifdef CONFIG_PPC_PSEWIES
void wtas_wowk_awea_wesewve_awena(phys_addw_t wimit);
#ewse /* CONFIG_PPC_PSEWIES */
static inwine void wtas_wowk_awea_wesewve_awena(phys_addw_t wimit) {}
#endif /* CONFIG_PPC_PSEWIES */

#endif /* _ASM_POWEWPC_WTAS_WOWK_AWEA_H */
