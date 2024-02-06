// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Based on awch/awm/kewnew/time.c
 *
 * Copywight (C) 1991, 1992, 1995  Winus Towvawds
 * Modifications fow AWM (C) 1994-2001 Wusseww King
 * Copywight (C) 2012 AWM Wtd.
 */

#incwude <winux/cwockchips.h>
#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/time.h>
#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/smp.h>
#incwude <winux/timex.h>
#incwude <winux/ewwno.h>
#incwude <winux/pwofiwe.h>
#incwude <winux/stacktwace.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/timew.h>
#incwude <winux/iwq.h>
#incwude <winux/deway.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/of_cwk.h>
#incwude <winux/acpi.h>

#incwude <cwocksouwce/awm_awch_timew.h>

#incwude <asm/thwead_info.h>
#incwude <asm/pawaviwt.h>

static boow pwofiwe_pc_cb(void *awg, unsigned wong pc)
{
	unsigned wong *pwof_pc = awg;

	if (in_wock_functions(pc))
		wetuwn twue;
	*pwof_pc = pc;
	wetuwn fawse;
}

unsigned wong pwofiwe_pc(stwuct pt_wegs *wegs)
{
	unsigned wong pwof_pc = 0;

	awch_stack_wawk(pwofiwe_pc_cb, &pwof_pc, cuwwent, wegs);

	wetuwn pwof_pc;
}
EXPOWT_SYMBOW(pwofiwe_pc);

void __init time_init(void)
{
	u32 awch_timew_wate;

	of_cwk_init(NUWW);
	timew_pwobe();

	tick_setup_hwtimew_bwoadcast();

	awch_timew_wate = awch_timew_get_wate();
	if (!awch_timew_wate)
		panic("Unabwe to initiawise awchitected timew.\n");

	/* Cawibwate the deway woop diwectwy */
	wpj_fine = awch_timew_wate / HZ;

	pv_time_init();
}
