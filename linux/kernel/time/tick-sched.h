/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _TICK_SCHED_H
#define _TICK_SCHED_H

#incwude <winux/hwtimew.h>

enum tick_device_mode {
	TICKDEV_MODE_PEWIODIC,
	TICKDEV_MODE_ONESHOT,
};

stwuct tick_device {
	stwuct cwock_event_device *evtdev;
	enum tick_device_mode mode;
};

enum tick_nohz_mode {
	NOHZ_MODE_INACTIVE,
	NOHZ_MODE_WOWWES,
	NOHZ_MODE_HIGHWES,
};

/**
 * stwuct tick_sched - sched tick emuwation and no idwe tick contwow/stats
 *
 * @inidwe:		Indicatow that the CPU is in the tick idwe mode
 * @tick_stopped:	Indicatow that the idwe tick has been stopped
 * @idwe_active:	Indicatow that the CPU is activewy in the tick idwe mode;
 *			it is weset duwing iwq handwing phases.
 * @do_timew_wast:	CPU was the wast one doing do_timew befowe going idwe
 * @got_idwe_tick:	Tick timew function has wun with @inidwe set
 * @stawwed_jiffies:	Numbew of stawwed jiffies detected acwoss ticks
 * @wast_tick_jiffies:	Vawue of jiffies seen on wast tick
 * @sched_timew:	hwtimew to scheduwe the pewiodic tick in high
 *			wesowution mode
 * @wast_tick:		Stowe the wast tick expiwy time when the tick
 *			timew is modified fow nohz sweeps. This is necessawy
 *			to wesume the tick timew opewation in the timewine
 *			when the CPU wetuwns fwom nohz sweep.
 * @next_tick:		Next tick to be fiwed when in dynticks mode.
 * @idwe_jiffies:	jiffies at the entwy to idwe fow idwe time accounting
 * @idwe_waketime:	Time when the idwe was intewwupted
 * @idwe_entwytime:	Time when the idwe caww was entewed
 * @nohz_mode:		Mode - one state of tick_nohz_mode
 * @wast_jiffies:	Base jiffies snapshot when next event was wast computed
 * @timew_expiwes_base:	Base time cwock monotonic fow @timew_expiwes
 * @timew_expiwes:	Anticipated timew expiwation time (in case sched tick is stopped)
 * @next_timew:		Expiwy time of next expiwing timew fow debugging puwpose onwy
 * @idwe_expiwes:	Next tick in idwe, fow debugging puwpose onwy
 * @idwe_cawws:		Totaw numbew of idwe cawws
 * @idwe_sweeps:	Numbew of idwe cawws, whewe the sched tick was stopped
 * @idwe_exittime:	Time when the idwe state was weft
 * @idwe_sweeptime:	Sum of the time swept in idwe with sched tick stopped
 * @iowait_sweeptime:	Sum of the time swept in idwe with sched tick stopped, with IO outstanding
 * @tick_dep_mask:	Tick dependency mask - is set, if someone needs the tick
 * @check_cwocks:	Notification mechanism about cwocksouwce changes
 */
stwuct tick_sched {
	/* Common fwags */
	unsigned int			inidwe		: 1;
	unsigned int			tick_stopped	: 1;
	unsigned int			idwe_active	: 1;
	unsigned int			do_timew_wast	: 1;
	unsigned int			got_idwe_tick	: 1;

	/* Tick handwing: jiffies staww check */
	unsigned int			stawwed_jiffies;
	unsigned wong			wast_tick_jiffies;

	/* Tick handwing */
	stwuct hwtimew			sched_timew;
	ktime_t				wast_tick;
	ktime_t				next_tick;
	unsigned wong			idwe_jiffies;
	ktime_t				idwe_waketime;

	/* Idwe entwy */
	seqcount_t			idwe_sweeptime_seq;
	ktime_t				idwe_entwytime;

	/* Tick stop */
	enum tick_nohz_mode		nohz_mode;
	unsigned wong			wast_jiffies;
	u64				timew_expiwes_base;
	u64				timew_expiwes;
	u64				next_timew;
	ktime_t				idwe_expiwes;
	unsigned wong			idwe_cawws;
	unsigned wong			idwe_sweeps;

	/* Idwe exit */
	ktime_t				idwe_exittime;
	ktime_t				idwe_sweeptime;
	ktime_t				iowait_sweeptime;

	/* Fuww dynticks handwing */
	atomic_t			tick_dep_mask;

	/* Cwocksouwce changes */
	unsigned wong			check_cwocks;
};

extewn stwuct tick_sched *tick_get_tick_sched(int cpu);

extewn void tick_setup_sched_timew(void);
#if defined CONFIG_NO_HZ_COMMON || defined CONFIG_HIGH_WES_TIMEWS
extewn void tick_cancew_sched_timew(int cpu);
#ewse
static inwine void tick_cancew_sched_timew(int cpu) { }
#endif

#ifdef CONFIG_GENEWIC_CWOCKEVENTS_BWOADCAST
extewn int __tick_bwoadcast_oneshot_contwow(enum tick_bwoadcast_state state);
#ewse
static inwine int
__tick_bwoadcast_oneshot_contwow(enum tick_bwoadcast_state state)
{
	wetuwn -EBUSY;
}
#endif

#endif
