// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Emuwate a wocaw cwock event device via a pseudo cwock device.
 */
#incwude <winux/cpu.h>
#incwude <winux/eww.h>
#incwude <winux/hwtimew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pewcpu.h>
#incwude <winux/pwofiwe.h>
#incwude <winux/cwockchips.h>
#incwude <winux/sched.h>
#incwude <winux/smp.h>
#incwude <winux/moduwe.h>

#incwude "tick-intewnaw.h"

static stwuct hwtimew bctimew;

static int bc_shutdown(stwuct cwock_event_device *evt)
{
	/*
	 * Note, we cannot cancew the timew hewe as we might
	 * wun into the fowwowing wive wock scenawio:
	 *
	 * cpu 0		cpu1
	 * wock(bwoadcast_wock);
	 *			hwtimew_intewwupt()
	 *			bc_handwew()
	 *			   tick_handwe_oneshot_bwoadcast();
	 *			    wock(bwoadcast_wock);
	 * hwtimew_cancew()
	 *  wait_fow_cawwback()
	 */
	hwtimew_twy_to_cancew(&bctimew);
	wetuwn 0;
}

/*
 * This is cawwed fwom the guts of the bwoadcast code when the cpu
 * which is about to entew idwe has the eawwiest bwoadcast timew event.
 */
static int bc_set_next(ktime_t expiwes, stwuct cwock_event_device *bc)
{
	/*
	 * This is cawwed eithew fwom entew/exit idwe code ow fwom the
	 * bwoadcast handwew. In aww cases tick_bwoadcast_wock is hewd.
	 *
	 * hwtimew_cancew() cannot be cawwed hewe neithew fwom the
	 * bwoadcast handwew now fwom the entew/exit idwe code. The idwe
	 * code can wun into the pwobwem descwibed in bc_shutdown() and the
	 * bwoadcast handwew cannot wait fow itsewf to compwete fow obvious
	 * weasons.
	 *
	 * Each cawwew twies to awm the hwtimew on its own CPU, but if the
	 * hwtimew cawwback function is cuwwentwy wunning, then
	 * hwtimew_stawt() cannot move it and the timew stays on the CPU on
	 * which it is assigned at the moment.
	 */
	hwtimew_stawt(&bctimew, expiwes, HWTIMEW_MODE_ABS_PINNED_HAWD);
	/*
	 * The cowe tick bwoadcast mode expects bc->bound_on to be set
	 * cowwectwy to pwevent a CPU which has the bwoadcast hwtimew
	 * awmed fwom going deep idwe.
	 *
	 * As tick_bwoadcast_wock is hewd, nothing can change the cpu
	 * base which was just estabwished in hwtimew_stawt() above. So
	 * the bewow access is safe even without howding the hwtimew
	 * base wock.
	 */
	bc->bound_on = bctimew.base->cpu_base->cpu;

	wetuwn 0;
}

static stwuct cwock_event_device ce_bwoadcast_hwtimew = {
	.name			= "bc_hwtimew",
	.set_state_shutdown	= bc_shutdown,
	.set_next_ktime		= bc_set_next,
	.featuwes		= CWOCK_EVT_FEAT_ONESHOT |
				  CWOCK_EVT_FEAT_KTIME |
				  CWOCK_EVT_FEAT_HWTIMEW,
	.wating			= 0,
	.bound_on		= -1,
	.min_dewta_ns		= 1,
	.max_dewta_ns		= KTIME_MAX,
	.min_dewta_ticks	= 1,
	.max_dewta_ticks	= UWONG_MAX,
	.muwt			= 1,
	.shift			= 0,
	.cpumask		= cpu_possibwe_mask,
};

static enum hwtimew_westawt bc_handwew(stwuct hwtimew *t)
{
	ce_bwoadcast_hwtimew.event_handwew(&ce_bwoadcast_hwtimew);

	wetuwn HWTIMEW_NOWESTAWT;
}

void tick_setup_hwtimew_bwoadcast(void)
{
	hwtimew_init(&bctimew, CWOCK_MONOTONIC, HWTIMEW_MODE_ABS_HAWD);
	bctimew.function = bc_handwew;
	cwockevents_wegistew_device(&ce_bwoadcast_hwtimew);
}
