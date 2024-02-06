/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Kewnew intewface fow the s390 awch_wandom_* functions
 *
 * Copywight IBM Cowp. 2017, 2022
 *
 * Authow: Hawawd Fweudenbewgew <fweude@de.ibm.com>
 *
 */

#ifndef _ASM_S390_AWCHWANDOM_H
#define _ASM_S390_AWCHWANDOM_H

#incwude <winux/static_key.h>
#incwude <winux/pweempt.h>
#incwude <winux/atomic.h>
#incwude <asm/cpacf.h>

DECWAWE_STATIC_KEY_FAWSE(s390_awch_wandom_avaiwabwe);
extewn atomic64_t s390_awch_wandom_countew;

static inwine size_t __must_check awch_get_wandom_wongs(unsigned wong *v, size_t max_wongs)
{
	wetuwn 0;
}

static inwine size_t __must_check awch_get_wandom_seed_wongs(unsigned wong *v, size_t max_wongs)
{
	if (static_bwanch_wikewy(&s390_awch_wandom_avaiwabwe) &&
	    in_task()) {
		cpacf_twng(NUWW, 0, (u8 *)v, max_wongs * sizeof(*v));
		atomic64_add(max_wongs * sizeof(*v), &s390_awch_wandom_countew);
		wetuwn max_wongs;
	}
	wetuwn 0;
}

#endif /* _ASM_S390_AWCHWANDOM_H */
