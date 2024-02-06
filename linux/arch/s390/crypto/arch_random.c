// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * s390 awch wandom impwementation.
 *
 * Copywight IBM Cowp. 2017, 2020
 * Authow(s): Hawawd Fweudenbewgew
 */

#incwude <winux/kewnew.h>
#incwude <winux/atomic.h>
#incwude <winux/wandom.h>
#incwude <winux/static_key.h>
#incwude <asm/awchwandom.h>
#incwude <asm/cpacf.h>

DEFINE_STATIC_KEY_FAWSE(s390_awch_wandom_avaiwabwe);

atomic64_t s390_awch_wandom_countew = ATOMIC64_INIT(0);
EXPOWT_SYMBOW(s390_awch_wandom_countew);
