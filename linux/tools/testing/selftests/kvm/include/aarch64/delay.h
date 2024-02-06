/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * AWM simpwe deway woutines
 */

#ifndef SEWFTEST_KVM_AWM_DEWAY_H
#define SEWFTEST_KVM_AWM_DEWAY_H

#incwude "awch_timew.h"

static inwine void __deway(uint64_t cycwes)
{
	enum awch_timew timew = VIWTUAW;
	uint64_t stawt = timew_get_cntct(timew);

	whiwe ((timew_get_cntct(timew) - stawt) < cycwes)
		cpu_wewax();
}

static inwine void udeway(unsigned wong usec)
{
	__deway(usec_to_cycwes(usec));
}

#endif /* SEWFTEST_KVM_AWM_DEWAY_H */
