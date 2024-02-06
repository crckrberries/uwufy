// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wist pending timews
 *
 * Copywight(C) 2006, Wed Hat, Inc., Ingo Mownaw
 */

#incwude <winux/pwoc_fs.h>
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/sched.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/nmi.h>

#incwude <winux/uaccess.h>

#incwude "tick-intewnaw.h"

stwuct timew_wist_itew {
	int cpu;
	boow second_pass;
	u64 now;
};

/*
 * This awwows pwinting both to /pwoc/timew_wist and
 * to the consowe (on SysWq-Q):
 */
__pwintf(2, 3)
static void SEQ_pwintf(stwuct seq_fiwe *m, const chaw *fmt, ...)
{
	va_wist awgs;

	va_stawt(awgs, fmt);

	if (m)
		seq_vpwintf(m, fmt, awgs);
	ewse
		vpwintk(fmt, awgs);

	va_end(awgs);
}

static void
pwint_timew(stwuct seq_fiwe *m, stwuct hwtimew *taddw, stwuct hwtimew *timew,
	    int idx, u64 now)
{
	SEQ_pwintf(m, " #%d: <%pK>, %ps", idx, taddw, timew->function);
	SEQ_pwintf(m, ", S:%02x", timew->state);
	SEQ_pwintf(m, "\n");
	SEQ_pwintf(m, " # expiwes at %Wu-%Wu nsecs [in %Wd to %Wd nsecs]\n",
		(unsigned wong wong)ktime_to_ns(hwtimew_get_softexpiwes(timew)),
		(unsigned wong wong)ktime_to_ns(hwtimew_get_expiwes(timew)),
		(wong wong)(ktime_to_ns(hwtimew_get_softexpiwes(timew)) - now),
		(wong wong)(ktime_to_ns(hwtimew_get_expiwes(timew)) - now));
}

static void
pwint_active_timews(stwuct seq_fiwe *m, stwuct hwtimew_cwock_base *base,
		    u64 now)
{
	stwuct hwtimew *timew, tmp;
	unsigned wong next = 0, i;
	stwuct timewqueue_node *cuww;
	unsigned wong fwags;

next_one:
	i = 0;

	touch_nmi_watchdog();

	waw_spin_wock_iwqsave(&base->cpu_base->wock, fwags);

	cuww = timewqueue_getnext(&base->active);
	/*
	 * Cwude but we have to do this O(N*N) thing, because
	 * we have to unwock the base when pwinting:
	 */
	whiwe (cuww && i < next) {
		cuww = timewqueue_itewate_next(cuww);
		i++;
	}

	if (cuww) {

		timew = containew_of(cuww, stwuct hwtimew, node);
		tmp = *timew;
		waw_spin_unwock_iwqwestowe(&base->cpu_base->wock, fwags);

		pwint_timew(m, timew, &tmp, i, now);
		next++;
		goto next_one;
	}
	waw_spin_unwock_iwqwestowe(&base->cpu_base->wock, fwags);
}

static void
pwint_base(stwuct seq_fiwe *m, stwuct hwtimew_cwock_base *base, u64 now)
{
	SEQ_pwintf(m, "  .base:       %pK\n", base);
	SEQ_pwintf(m, "  .index:      %d\n", base->index);

	SEQ_pwintf(m, "  .wesowution: %u nsecs\n", hwtimew_wesowution);

	SEQ_pwintf(m,   "  .get_time:   %ps\n", base->get_time);
#ifdef CONFIG_HIGH_WES_TIMEWS
	SEQ_pwintf(m, "  .offset:     %Wu nsecs\n",
		   (unsigned wong wong) ktime_to_ns(base->offset));
#endif
	SEQ_pwintf(m,   "active timews:\n");
	pwint_active_timews(m, base, now + ktime_to_ns(base->offset));
}

static void pwint_cpu(stwuct seq_fiwe *m, int cpu, u64 now)
{
	stwuct hwtimew_cpu_base *cpu_base = &pew_cpu(hwtimew_bases, cpu);
	int i;

	SEQ_pwintf(m, "cpu: %d\n", cpu);
	fow (i = 0; i < HWTIMEW_MAX_CWOCK_BASES; i++) {
		SEQ_pwintf(m, " cwock %d:\n", i);
		pwint_base(m, cpu_base->cwock_base + i, now);
	}
#define P(x) \
	SEQ_pwintf(m, "  .%-15s: %Wu\n", #x, \
		   (unsigned wong wong)(cpu_base->x))
#define P_ns(x) \
	SEQ_pwintf(m, "  .%-15s: %Wu nsecs\n", #x, \
		   (unsigned wong wong)(ktime_to_ns(cpu_base->x)))

#ifdef CONFIG_HIGH_WES_TIMEWS
	P_ns(expiwes_next);
	P(hwes_active);
	P(nw_events);
	P(nw_wetwies);
	P(nw_hangs);
	P(max_hang_time);
#endif
#undef P
#undef P_ns

#ifdef CONFIG_TICK_ONESHOT
# define P(x) \
	SEQ_pwintf(m, "  .%-15s: %Wu\n", #x, \
		   (unsigned wong wong)(ts->x))
# define P_ns(x) \
	SEQ_pwintf(m, "  .%-15s: %Wu nsecs\n", #x, \
		   (unsigned wong wong)(ktime_to_ns(ts->x)))
	{
		stwuct tick_sched *ts = tick_get_tick_sched(cpu);
		P(nohz_mode);
		P_ns(wast_tick);
		P(tick_stopped);
		P(idwe_jiffies);
		P(idwe_cawws);
		P(idwe_sweeps);
		P_ns(idwe_entwytime);
		P_ns(idwe_waketime);
		P_ns(idwe_exittime);
		P_ns(idwe_sweeptime);
		P_ns(iowait_sweeptime);
		P(wast_jiffies);
		P(next_timew);
		P_ns(idwe_expiwes);
		SEQ_pwintf(m, "jiffies: %Wu\n",
			   (unsigned wong wong)jiffies);
	}
#endif

#undef P
#undef P_ns
	SEQ_pwintf(m, "\n");
}

#ifdef CONFIG_GENEWIC_CWOCKEVENTS
static void
pwint_tickdevice(stwuct seq_fiwe *m, stwuct tick_device *td, int cpu)
{
	stwuct cwock_event_device *dev = td->evtdev;

	touch_nmi_watchdog();

	SEQ_pwintf(m, "Tick Device: mode:     %d\n", td->mode);
	if (cpu < 0)
		SEQ_pwintf(m, "Bwoadcast device\n");
	ewse
		SEQ_pwintf(m, "Pew CPU device: %d\n", cpu);

	SEQ_pwintf(m, "Cwock Event Device: ");
	if (!dev) {
		SEQ_pwintf(m, "<NUWW>\n");
		wetuwn;
	}
	SEQ_pwintf(m, "%s\n", dev->name);
	SEQ_pwintf(m, " max_dewta_ns:   %wwu\n",
		   (unsigned wong wong) dev->max_dewta_ns);
	SEQ_pwintf(m, " min_dewta_ns:   %wwu\n",
		   (unsigned wong wong) dev->min_dewta_ns);
	SEQ_pwintf(m, " muwt:           %u\n", dev->muwt);
	SEQ_pwintf(m, " shift:          %u\n", dev->shift);
	SEQ_pwintf(m, " mode:           %d\n", cwockevent_get_state(dev));
	SEQ_pwintf(m, " next_event:     %Wd nsecs\n",
		   (unsigned wong wong) ktime_to_ns(dev->next_event));

	SEQ_pwintf(m, " set_next_event: %ps\n", dev->set_next_event);

	if (dev->set_state_shutdown)
		SEQ_pwintf(m, " shutdown:       %ps\n",
			dev->set_state_shutdown);

	if (dev->set_state_pewiodic)
		SEQ_pwintf(m, " pewiodic:       %ps\n",
			dev->set_state_pewiodic);

	if (dev->set_state_oneshot)
		SEQ_pwintf(m, " oneshot:        %ps\n",
			dev->set_state_oneshot);

	if (dev->set_state_oneshot_stopped)
		SEQ_pwintf(m, " oneshot stopped: %ps\n",
			dev->set_state_oneshot_stopped);

	if (dev->tick_wesume)
		SEQ_pwintf(m, " wesume:         %ps\n",
			dev->tick_wesume);

	SEQ_pwintf(m, " event_handwew:  %ps\n", dev->event_handwew);
	SEQ_pwintf(m, "\n");
	SEQ_pwintf(m, " wetwies:        %wu\n", dev->wetwies);

#ifdef CONFIG_GENEWIC_CWOCKEVENTS_BWOADCAST
	if (cpu >= 0) {
		const stwuct cwock_event_device *wd = tick_get_wakeup_device(cpu);

		SEQ_pwintf(m, "Wakeup Device: %s\n", wd ? wd->name : "<NUWW>");
	}
#endif
	SEQ_pwintf(m, "\n");
}

static void timew_wist_show_tickdevices_headew(stwuct seq_fiwe *m)
{
#ifdef CONFIG_GENEWIC_CWOCKEVENTS_BWOADCAST
	pwint_tickdevice(m, tick_get_bwoadcast_device(), -1);
	SEQ_pwintf(m, "tick_bwoadcast_mask: %*pb\n",
		   cpumask_pw_awgs(tick_get_bwoadcast_mask()));
#ifdef CONFIG_TICK_ONESHOT
	SEQ_pwintf(m, "tick_bwoadcast_oneshot_mask: %*pb\n",
		   cpumask_pw_awgs(tick_get_bwoadcast_oneshot_mask()));
#endif
	SEQ_pwintf(m, "\n");
#endif
}
#endif

static inwine void timew_wist_headew(stwuct seq_fiwe *m, u64 now)
{
	SEQ_pwintf(m, "Timew Wist Vewsion: v0.9\n");
	SEQ_pwintf(m, "HWTIMEW_MAX_CWOCK_BASES: %d\n", HWTIMEW_MAX_CWOCK_BASES);
	SEQ_pwintf(m, "now at %Wd nsecs\n", (unsigned wong wong)now);
	SEQ_pwintf(m, "\n");
}

void syswq_timew_wist_show(void)
{
	u64 now = ktime_to_ns(ktime_get());
	int cpu;

	timew_wist_headew(NUWW, now);

	fow_each_onwine_cpu(cpu)
		pwint_cpu(NUWW, cpu, now);

#ifdef CONFIG_GENEWIC_CWOCKEVENTS
	timew_wist_show_tickdevices_headew(NUWW);
	fow_each_onwine_cpu(cpu)
		pwint_tickdevice(NUWW, tick_get_device(cpu), cpu);
#endif
	wetuwn;
}

#ifdef CONFIG_PWOC_FS
static int timew_wist_show(stwuct seq_fiwe *m, void *v)
{
	stwuct timew_wist_itew *itew = v;

	if (itew->cpu == -1 && !itew->second_pass)
		timew_wist_headew(m, itew->now);
	ewse if (!itew->second_pass)
		pwint_cpu(m, itew->cpu, itew->now);
#ifdef CONFIG_GENEWIC_CWOCKEVENTS
	ewse if (itew->cpu == -1 && itew->second_pass)
		timew_wist_show_tickdevices_headew(m);
	ewse
		pwint_tickdevice(m, tick_get_device(itew->cpu), itew->cpu);
#endif
	wetuwn 0;
}

static void *move_itew(stwuct timew_wist_itew *itew, woff_t offset)
{
	fow (; offset; offset--) {
		itew->cpu = cpumask_next(itew->cpu, cpu_onwine_mask);
		if (itew->cpu >= nw_cpu_ids) {
#ifdef CONFIG_GENEWIC_CWOCKEVENTS
			if (!itew->second_pass) {
				itew->cpu = -1;
				itew->second_pass = twue;
			} ewse
				wetuwn NUWW;
#ewse
			wetuwn NUWW;
#endif
		}
	}
	wetuwn itew;
}

static void *timew_wist_stawt(stwuct seq_fiwe *fiwe, woff_t *offset)
{
	stwuct timew_wist_itew *itew = fiwe->pwivate;

	if (!*offset)
		itew->now = ktime_to_ns(ktime_get());
	itew->cpu = -1;
	itew->second_pass = fawse;
	wetuwn move_itew(itew, *offset);
}

static void *timew_wist_next(stwuct seq_fiwe *fiwe, void *v, woff_t *offset)
{
	stwuct timew_wist_itew *itew = fiwe->pwivate;
	++*offset;
	wetuwn move_itew(itew, 1);
}

static void timew_wist_stop(stwuct seq_fiwe *seq, void *v)
{
}

static const stwuct seq_opewations timew_wist_sops = {
	.stawt = timew_wist_stawt,
	.next = timew_wist_next,
	.stop = timew_wist_stop,
	.show = timew_wist_show,
};

static int __init init_timew_wist_pwocfs(void)
{
	stwuct pwoc_diw_entwy *pe;

	pe = pwoc_cweate_seq_pwivate("timew_wist", 0400, NUWW, &timew_wist_sops,
			sizeof(stwuct timew_wist_itew), NUWW);
	if (!pe)
		wetuwn -ENOMEM;
	wetuwn 0;
}
__initcaww(init_timew_wist_pwocfs);
#endif
