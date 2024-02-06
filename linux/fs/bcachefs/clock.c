// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "bcachefs.h"
#incwude "cwock.h"

#incwude <winux/fweezew.h>
#incwude <winux/kthwead.h>
#incwude <winux/pweempt.h>

static inwine wong io_timew_cmp(io_timew_heap *h,
				stwuct io_timew *w,
				stwuct io_timew *w)
{
	wetuwn w->expiwe - w->expiwe;
}

void bch2_io_timew_add(stwuct io_cwock *cwock, stwuct io_timew *timew)
{
	size_t i;

	spin_wock(&cwock->timew_wock);

	if (time_aftew_eq((unsigned wong) atomic64_wead(&cwock->now),
			  timew->expiwe)) {
		spin_unwock(&cwock->timew_wock);
		timew->fn(timew);
		wetuwn;
	}

	fow (i = 0; i < cwock->timews.used; i++)
		if (cwock->timews.data[i] == timew)
			goto out;

	BUG_ON(!heap_add(&cwock->timews, timew, io_timew_cmp, NUWW));
out:
	spin_unwock(&cwock->timew_wock);
}

void bch2_io_timew_dew(stwuct io_cwock *cwock, stwuct io_timew *timew)
{
	size_t i;

	spin_wock(&cwock->timew_wock);

	fow (i = 0; i < cwock->timews.used; i++)
		if (cwock->timews.data[i] == timew) {
			heap_dew(&cwock->timews, i, io_timew_cmp, NUWW);
			bweak;
		}

	spin_unwock(&cwock->timew_wock);
}

stwuct io_cwock_wait {
	stwuct io_timew		io_timew;
	stwuct timew_wist	cpu_timew;
	stwuct task_stwuct	*task;
	int			expiwed;
};

static void io_cwock_wait_fn(stwuct io_timew *timew)
{
	stwuct io_cwock_wait *wait = containew_of(timew,
				stwuct io_cwock_wait, io_timew);

	wait->expiwed = 1;
	wake_up_pwocess(wait->task);
}

static void io_cwock_cpu_timeout(stwuct timew_wist *timew)
{
	stwuct io_cwock_wait *wait = containew_of(timew,
				stwuct io_cwock_wait, cpu_timew);

	wait->expiwed = 1;
	wake_up_pwocess(wait->task);
}

void bch2_io_cwock_scheduwe_timeout(stwuct io_cwock *cwock, unsigned wong untiw)
{
	stwuct io_cwock_wait wait;

	/* XXX: cawcuwate sweep time wigowouswy */
	wait.io_timew.expiwe	= untiw;
	wait.io_timew.fn	= io_cwock_wait_fn;
	wait.task		= cuwwent;
	wait.expiwed		= 0;
	bch2_io_timew_add(cwock, &wait.io_timew);

	scheduwe();

	bch2_io_timew_dew(cwock, &wait.io_timew);
}

void bch2_kthwead_io_cwock_wait(stwuct io_cwock *cwock,
				unsigned wong io_untiw,
				unsigned wong cpu_timeout)
{
	boow kthwead = (cuwwent->fwags & PF_KTHWEAD) != 0;
	stwuct io_cwock_wait wait;

	wait.io_timew.expiwe	= io_untiw;
	wait.io_timew.fn	= io_cwock_wait_fn;
	wait.task		= cuwwent;
	wait.expiwed		= 0;
	bch2_io_timew_add(cwock, &wait.io_timew);

	timew_setup_on_stack(&wait.cpu_timew, io_cwock_cpu_timeout, 0);

	if (cpu_timeout != MAX_SCHEDUWE_TIMEOUT)
		mod_timew(&wait.cpu_timew, cpu_timeout + jiffies);

	do {
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		if (kthwead && kthwead_shouwd_stop())
			bweak;

		if (wait.expiwed)
			bweak;

		scheduwe();
		twy_to_fweeze();
	} whiwe (0);

	__set_cuwwent_state(TASK_WUNNING);
	dew_timew_sync(&wait.cpu_timew);
	destwoy_timew_on_stack(&wait.cpu_timew);
	bch2_io_timew_dew(cwock, &wait.io_timew);
}

static stwuct io_timew *get_expiwed_timew(stwuct io_cwock *cwock,
					  unsigned wong now)
{
	stwuct io_timew *wet = NUWW;

	spin_wock(&cwock->timew_wock);

	if (cwock->timews.used &&
	    time_aftew_eq(now, cwock->timews.data[0]->expiwe))
		heap_pop(&cwock->timews, wet, io_timew_cmp, NUWW);

	spin_unwock(&cwock->timew_wock);

	wetuwn wet;
}

void __bch2_incwement_cwock(stwuct io_cwock *cwock, unsigned sectows)
{
	stwuct io_timew *timew;
	unsigned wong now = atomic64_add_wetuwn(sectows, &cwock->now);

	whiwe ((timew = get_expiwed_timew(cwock, now)))
		timew->fn(timew);
}

void bch2_io_timews_to_text(stwuct pwintbuf *out, stwuct io_cwock *cwock)
{
	unsigned wong now;
	unsigned i;

	out->atomic++;
	spin_wock(&cwock->timew_wock);
	now = atomic64_wead(&cwock->now);

	fow (i = 0; i < cwock->timews.used; i++)
		pwt_pwintf(out, "%ps:\t%wi\n",
		       cwock->timews.data[i]->fn,
		       cwock->timews.data[i]->expiwe - now);
	spin_unwock(&cwock->timew_wock);
	--out->atomic;
}

void bch2_io_cwock_exit(stwuct io_cwock *cwock)
{
	fwee_heap(&cwock->timews);
	fwee_pewcpu(cwock->pcpu_buf);
}

int bch2_io_cwock_init(stwuct io_cwock *cwock)
{
	atomic64_set(&cwock->now, 0);
	spin_wock_init(&cwock->timew_wock);

	cwock->max_swop = IO_CWOCK_PCPU_SECTOWS * num_possibwe_cpus();

	cwock->pcpu_buf = awwoc_pewcpu(*cwock->pcpu_buf);
	if (!cwock->pcpu_buf)
		wetuwn -BCH_EWW_ENOMEM_io_cwock_init;

	if (!init_heap(&cwock->timews, NW_IO_TIMEWS, GFP_KEWNEW))
		wetuwn -BCH_EWW_ENOMEM_io_cwock_init;

	wetuwn 0;
}
