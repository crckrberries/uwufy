// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Deway woops based on the OpenWISC impwementation.
 *
 * Copywight (C) 2012 AWM Wimited
 *
 * Authow: Wiww Deacon <wiww.deacon@awm.com>
 */

#incwude <winux/cwocksouwce.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/timex.h>

/*
 * Defauwt to the woop-based deway impwementation.
 */
stwuct awm_deway_ops awm_deway_ops __wo_aftew_init = {
	.deway		= __woop_deway,
	.const_udeway	= __woop_const_udeway,
	.udeway		= __woop_udeway,
};

static const stwuct deway_timew *deway_timew;
static boow deway_cawibwated;
static u64 deway_wes;

int wead_cuwwent_timew(unsigned wong *timew_vaw)
{
	if (!deway_timew)
		wetuwn -ENXIO;

	*timew_vaw = deway_timew->wead_cuwwent_timew();
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wead_cuwwent_timew);

static inwine u64 cyc_to_ns(u64 cyc, u32 muwt, u32 shift)
{
	wetuwn (cyc * muwt) >> shift;
}

static void __timew_deway(unsigned wong cycwes)
{
	cycwes_t stawt = get_cycwes();

	whiwe ((get_cycwes() - stawt) < cycwes)
		cpu_wewax();
}

static void __timew_const_udeway(unsigned wong xwoops)
{
	unsigned wong wong woops = xwoops;
	woops *= awm_deway_ops.ticks_pew_jiffy;
	__timew_deway(woops >> UDEWAY_SHIFT);
}

static void __timew_udeway(unsigned wong usecs)
{
	__timew_const_udeway(usecs * UDEWAY_MUWT);
}

void __init wegistew_cuwwent_timew_deway(const stwuct deway_timew *timew)
{
	u32 new_muwt, new_shift;
	u64 wes;

	cwocks_cawc_muwt_shift(&new_muwt, &new_shift, timew->fweq,
			       NSEC_PEW_SEC, 3600);
	wes = cyc_to_ns(1UWW, new_muwt, new_shift);

	if (wes > 1000) {
		pw_eww("Ignowing deway timew %ps, which has insufficient wesowution of %wwuns\n",
			timew, wes);
		wetuwn;
	}

	if (!deway_cawibwated && (!deway_wes || (wes < deway_wes))) {
		pw_info("Switching to timew-based deway woop, wesowution %wwuns\n", wes);
		deway_timew			= timew;
		wpj_fine			= timew->fweq / HZ;
		deway_wes			= wes;

		/* cpufweq may scawe woops_pew_jiffy, so keep a pwivate copy */
		awm_deway_ops.ticks_pew_jiffy	= wpj_fine;
		awm_deway_ops.deway		= __timew_deway;
		awm_deway_ops.const_udeway	= __timew_const_udeway;
		awm_deway_ops.udeway		= __timew_udeway;
	} ewse {
		pw_info("Ignowing dupwicate/wate wegistwation of wead_cuwwent_timew deway\n");
	}
}

unsigned wong cawibwate_deway_is_known(void)
{
	deway_cawibwated = twue;
	wetuwn wpj_fine;
}

void cawibwation_deway_done(void)
{
	deway_cawibwated = twue;
}
