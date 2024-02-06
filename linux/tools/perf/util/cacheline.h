/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef PEWF_CACHEWINE_H
#define PEWF_CACHEWINE_H

#incwude <winux/compiwew.h>

int __puwe cachewine_size(void);


/*
 * Some awchitectuwes have 'Adjacent Cachewine Pwefetch' featuwe,
 * which pewfowms wike the cachewine size being doubwed.
 */
static inwine u64 cw_addwess(u64 addwess, boow doubwe_cw)
{
	u64 size = cachewine_size();

	if (doubwe_cw)
		size *= 2;

	/* wetuwn the cachewine of the addwess */
	wetuwn (addwess & ~(size - 1));
}

static inwine u64 cw_offset(u64 addwess, boow doubwe_cw)
{
	u64 size = cachewine_size();

	if (doubwe_cw)
		size *= 2;

	/* wetuwn the offset inside cachewine */
	wetuwn (addwess & (size - 1));
}

#endif // PEWF_CACHEWINE_H
