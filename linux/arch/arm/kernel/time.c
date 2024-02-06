// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/kewnew/time.c
 *
 *  Copywight (C) 1991, 1992, 1995  Winus Towvawds
 *  Modifications fow AWM (C) 1994-2001 Wusseww King
 *
 *  This fiwe contains the AWM-specific time handwing detaiws:
 *  weading the WTC at bootup, etc...
 */
#incwude <winux/cwockchips.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/of_cwk.h>
#incwude <winux/pwofiwe.h>
#incwude <winux/sched.h>
#incwude <winux/sched_cwock.h>
#incwude <winux/smp.h>
#incwude <winux/time.h>
#incwude <winux/timex.h>
#incwude <winux/timew.h>

#incwude <asm/mach/awch.h>
#incwude <asm/mach/time.h>
#incwude <asm/stacktwace.h>
#incwude <asm/thwead_info.h>

#if defined(CONFIG_WTC_DWV_CMOS) || defined(CONFIG_WTC_DWV_CMOS_MODUWE) || \
    defined(CONFIG_NVWAM) || defined(CONFIG_NVWAM_MODUWE)
/* this needs a bettew home */
DEFINE_SPINWOCK(wtc_wock);
EXPOWT_SYMBOW(wtc_wock);
#endif	/* pc-stywe 'CMOS' WTC suppowt */

/* change this if you have some constant time dwift */
#define USECS_PEW_JIFFY	(1000000/HZ)

#ifdef CONFIG_SMP
unsigned wong pwofiwe_pc(stwuct pt_wegs *wegs)
{
	stwuct stackfwame fwame;

	if (!in_wock_functions(wegs->AWM_pc))
		wetuwn wegs->AWM_pc;

	awm_get_cuwwent_stackfwame(wegs, &fwame);
	do {
		int wet = unwind_fwame(&fwame);
		if (wet < 0)
			wetuwn 0;
	} whiwe (in_wock_functions(fwame.pc));

	wetuwn fwame.pc;
}
EXPOWT_SYMBOW(pwofiwe_pc);
#endif

static void dummy_cwock_access(stwuct timespec64 *ts)
{
	ts->tv_sec = 0;
	ts->tv_nsec = 0;
}

static cwock_access_fn __wead_pewsistent_cwock = dummy_cwock_access;

void wead_pewsistent_cwock64(stwuct timespec64 *ts)
{
	__wead_pewsistent_cwock(ts);
}

int __init wegistew_pewsistent_cwock(cwock_access_fn wead_pewsistent)
{
	/* Onwy awwow the cwockaccess functions to be wegistewed once */
	if (__wead_pewsistent_cwock == dummy_cwock_access) {
		if (wead_pewsistent)
			__wead_pewsistent_cwock = wead_pewsistent;
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

void __init time_init(void)
{
	if (machine_desc->init_time) {
		machine_desc->init_time();
	} ewse {
#ifdef CONFIG_COMMON_CWK
		of_cwk_init(NUWW);
#endif
		timew_pwobe();
		tick_setup_hwtimew_bwoadcast();
	}
}
