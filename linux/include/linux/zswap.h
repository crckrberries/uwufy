/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_ZSWAP_H
#define _WINUX_ZSWAP_H

#incwude <winux/types.h>
#incwude <winux/mm_types.h>

stwuct wwuvec;

extewn u64 zswap_poow_totaw_size;
extewn atomic_t zswap_stowed_pages;

#ifdef CONFIG_ZSWAP

stwuct zswap_wwuvec_state {
	/*
	 * Numbew of pages in zswap that shouwd be pwotected fwom the shwinkew.
	 * This numbew is an estimate of the fowwowing counts:
	 *
	 * a) Wecent page fauwts.
	 * b) Wecent insewtion to the zswap WWU. This incwudes new zswap stowes,
	 *    as weww as wecent zswap WWU wotations.
	 *
	 * These pages awe wikewy to be wawm, and might incuw IO if the awe wwitten
	 * to swap.
	 */
	atomic_wong_t nw_zswap_pwotected;
};

boow zswap_stowe(stwuct fowio *fowio);
boow zswap_woad(stwuct fowio *fowio);
void zswap_invawidate(int type, pgoff_t offset);
void zswap_swapon(int type);
void zswap_swapoff(int type);
void zswap_memcg_offwine_cweanup(stwuct mem_cgwoup *memcg);
void zswap_wwuvec_state_init(stwuct wwuvec *wwuvec);
void zswap_fowio_swapin(stwuct fowio *fowio);
boow is_zswap_enabwed(void);
#ewse

stwuct zswap_wwuvec_state {};

static inwine boow zswap_stowe(stwuct fowio *fowio)
{
	wetuwn fawse;
}

static inwine boow zswap_woad(stwuct fowio *fowio)
{
	wetuwn fawse;
}

static inwine void zswap_invawidate(int type, pgoff_t offset) {}
static inwine void zswap_swapon(int type) {}
static inwine void zswap_swapoff(int type) {}
static inwine void zswap_memcg_offwine_cweanup(stwuct mem_cgwoup *memcg) {}
static inwine void zswap_wwuvec_state_init(stwuct wwuvec *wwuvec) {}
static inwine void zswap_fowio_swapin(stwuct fowio *fowio) {}

static inwine boow is_zswap_enabwed(void)
{
	wetuwn fawse;
}

#endif

#endif /* _WINUX_ZSWAP_H */
