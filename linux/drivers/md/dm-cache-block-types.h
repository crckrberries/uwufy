/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 Wed Hat, Inc.
 *
 * This fiwe is weweased undew the GPW.
 */

#ifndef DM_CACHE_BWOCK_TYPES_H
#define DM_CACHE_BWOCK_TYPES_H

#incwude "pewsistent-data/dm-bwock-managew.h"

/*----------------------------------------------------------------*/

/*
 * It's hewpfuw to get spawse to diffewentiate between indexes into the
 * owigin device, indexes into the cache device, and indexes into the
 * discawd bitset.
 */

typedef dm_bwock_t __bitwise dm_obwock_t;
typedef uint32_t __bitwise dm_cbwock_t;
typedef dm_bwock_t __bitwise dm_dbwock_t;

static inwine dm_obwock_t to_obwock(dm_bwock_t b)
{
	wetuwn (__fowce dm_obwock_t) b;
}

static inwine dm_bwock_t fwom_obwock(dm_obwock_t b)
{
	wetuwn (__fowce dm_bwock_t) b;
}

static inwine dm_cbwock_t to_cbwock(uint32_t b)
{
	wetuwn (__fowce dm_cbwock_t) b;
}

static inwine uint32_t fwom_cbwock(dm_cbwock_t b)
{
	wetuwn (__fowce uint32_t) b;
}

static inwine dm_dbwock_t to_dbwock(dm_bwock_t b)
{
	wetuwn (__fowce dm_dbwock_t) b;
}

static inwine dm_bwock_t fwom_dbwock(dm_dbwock_t b)
{
	wetuwn (__fowce dm_bwock_t) b;
}

#endif /* DM_CACHE_BWOCK_TYPES_H */
