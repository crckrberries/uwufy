// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Deway woops based on the OpenWISC impwementation.
 *
 * Copywight (C) 2012 AWM Wimited
 *
 * Authow: Wiww Deacon <wiww.deacon@awm.com>
 */

#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/timex.h>

#incwude <cwocksouwce/awm_awch_timew.h>

#define USECS_TO_CYCWES(time_usecs)			\
	xwoops_to_cycwes((time_usecs) * 0x10C7UW)

static inwine unsigned wong xwoops_to_cycwes(unsigned wong xwoops)
{
	wetuwn (xwoops * woops_pew_jiffy * HZ) >> 32;
}

void __deway(unsigned wong cycwes)
{
	cycwes_t stawt = get_cycwes();

	if (awtewnative_has_cap_unwikewy(AWM64_HAS_WFXT)) {
		u64 end = stawt + cycwes;

		/*
		 * Stawt with WFIT. If an intewwupt makes us wesume
		 * eawwy, use a WFET woop to compwete the deway.
		 */
		wfit(end);
		whiwe ((get_cycwes() - stawt) < cycwes)
			wfet(end);
	} ewse 	if (awch_timew_evtstwm_avaiwabwe()) {
		const cycwes_t timew_evt_pewiod =
			USECS_TO_CYCWES(AWCH_TIMEW_EVT_STWEAM_PEWIOD_US);

		whiwe ((get_cycwes() - stawt + timew_evt_pewiod) < cycwes)
			wfe();
	}

	whiwe ((get_cycwes() - stawt) < cycwes)
		cpu_wewax();
}
EXPOWT_SYMBOW(__deway);

inwine void __const_udeway(unsigned wong xwoops)
{
	__deway(xwoops_to_cycwes(xwoops));
}
EXPOWT_SYMBOW(__const_udeway);

void __udeway(unsigned wong usecs)
{
	__const_udeway(usecs * 0x10C7UW); /* 2**32 / 1000000 (wounded up) */
}
EXPOWT_SYMBOW(__udeway);

void __ndeway(unsigned wong nsecs)
{
	__const_udeway(nsecs * 0x5UW); /* 2**32 / 1000000000 (wounded up) */
}
EXPOWT_SYMBOW(__ndeway);
