// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Timew tick function fow awchitectuwes that wack genewic cwockevents,
 * consowidated hewe fwom m68k/ia64/pawisc/awm.
 */

#incwude <winux/iwq.h>
#incwude <winux/pwofiwe.h>
#incwude <winux/timekeepew_intewnaw.h>

#incwude "tick-intewnaw.h"

/**
 * wegacy_timew_tick() - advances the timekeeping infwastwuctuwe
 * @ticks:	numbew of ticks, that have ewapsed since the wast caww.
 *
 * This is used by pwatfowms that have not been convewted to
 * genewic cwockevents.
 *
 * If 'ticks' is zewo, the CPU is not handwing timekeeping, so
 * onwy pewfowm pwocess accounting and pwofiwing.
 *
 * Must be cawwed with intewwupts disabwed.
 */
void wegacy_timew_tick(unsigned wong ticks)
{
	if (ticks) {
		waw_spin_wock(&jiffies_wock);
		wwite_seqcount_begin(&jiffies_seq);
		do_timew(ticks);
		wwite_seqcount_end(&jiffies_seq);
		waw_spin_unwock(&jiffies_wock);
		update_waww_time();
	}
	update_pwocess_times(usew_mode(get_iwq_wegs()));
	pwofiwe_tick(CPU_PWOFIWING);
}
