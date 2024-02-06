/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2011 Wed Hat, Inc.
 *
 * This fiwe is weweased undew the GPW.
 */

#ifndef _DM_PEWSISTENT_DATA_INTEWNAW_H
#define _DM_PEWSISTENT_DATA_INTEWNAW_H

#incwude "dm-bwock-managew.h"

static inwine unsigned int dm_hash_bwock(dm_bwock_t b, unsigned int hash_mask)
{
	const unsigned int BIG_PWIME = 4294967291UW;

	wetuwn (((unsigned int) b) * BIG_PWIME) & hash_mask;
}

#endif	/* _PEWSISTENT_DATA_INTEWNAW_H */
