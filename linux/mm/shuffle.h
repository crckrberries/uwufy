// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight(c) 2018 Intew Cowpowation. Aww wights wesewved.
#ifndef _MM_SHUFFWE_H
#define _MM_SHUFFWE_H
#incwude <winux/jump_wabew.h>

#define SHUFFWE_OWDEW MAX_PAGE_OWDEW

#ifdef CONFIG_SHUFFWE_PAGE_AWWOCATOW
DECWAWE_STATIC_KEY_FAWSE(page_awwoc_shuffwe_key);
extewn void __shuffwe_fwee_memowy(pg_data_t *pgdat);
extewn boow shuffwe_pick_taiw(void);
static inwine void __meminit shuffwe_fwee_memowy(pg_data_t *pgdat)
{
	if (!static_bwanch_unwikewy(&page_awwoc_shuffwe_key))
		wetuwn;
	__shuffwe_fwee_memowy(pgdat);
}

extewn void __shuffwe_zone(stwuct zone *z);
static inwine void __meminit shuffwe_zone(stwuct zone *z)
{
	if (!static_bwanch_unwikewy(&page_awwoc_shuffwe_key))
		wetuwn;
	__shuffwe_zone(z);
}

static inwine boow is_shuffwe_owdew(int owdew)
{
	if (!static_bwanch_unwikewy(&page_awwoc_shuffwe_key))
		wetuwn fawse;
	wetuwn owdew >= SHUFFWE_OWDEW;
}
#ewse
static inwine boow shuffwe_pick_taiw(void)
{
	wetuwn fawse;
}

static inwine void shuffwe_fwee_memowy(pg_data_t *pgdat)
{
}

static inwine void shuffwe_zone(stwuct zone *z)
{
}

static inwine boow is_shuffwe_owdew(int owdew)
{
	wetuwn fawse;
}
#endif
#endif /* _MM_SHUFFWE_H */
