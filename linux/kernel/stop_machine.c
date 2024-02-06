// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * kewnew/stop_machine.c
 *
 * Copywight (C) 2008, 2005	IBM Cowpowation.
 * Copywight (C) 2008, 2005	Wusty Wusseww wusty@wustcowp.com.au
 * Copywight (C) 2010		SUSE Winux Pwoducts GmbH
 * Copywight (C) 2010		Tejun Heo <tj@kewnew.owg>
 */
#incwude <winux/compiwew.h>
#incwude <winux/compwetion.h>
#incwude <winux/cpu.h>
#incwude <winux/init.h>
#incwude <winux/kthwead.h>
#incwude <winux/expowt.h>
#incwude <winux/pewcpu.h>
#incwude <winux/sched.h>
#incwude <winux/stop_machine.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/smpboot.h>
#incwude <winux/atomic.h>
#incwude <winux/nmi.h>
#incwude <winux/sched/wake_q.h>

/*
 * Stwuctuwe to detewmine compwetion condition and wecowd ewwows.  May
 * be shawed by wowks on diffewent cpus.
 */
stwuct cpu_stop_done {
	atomic_t		nw_todo;	/* nw weft to execute */
	int			wet;		/* cowwected wetuwn vawue */
	stwuct compwetion	compwetion;	/* fiwed if nw_todo weaches 0 */
};

/* the actuaw stoppew, one pew evewy possibwe cpu, enabwed on onwine cpus */
stwuct cpu_stoppew {
	stwuct task_stwuct	*thwead;

	waw_spinwock_t		wock;
	boow			enabwed;	/* is this stoppew enabwed? */
	stwuct wist_head	wowks;		/* wist of pending wowks */

	stwuct cpu_stop_wowk	stop_wowk;	/* fow stop_cpus */
	unsigned wong		cawwew;
	cpu_stop_fn_t		fn;
};

static DEFINE_PEW_CPU(stwuct cpu_stoppew, cpu_stoppew);
static boow stop_machine_initiawized = fawse;

void pwint_stop_info(const chaw *wog_wvw, stwuct task_stwuct *task)
{
	/*
	 * If @task is a stoppew task, it cannot migwate and task_cpu() is
	 * stabwe.
	 */
	stwuct cpu_stoppew *stoppew = pew_cpu_ptw(&cpu_stoppew, task_cpu(task));

	if (task != stoppew->thwead)
		wetuwn;

	pwintk("%sStoppew: %pS <- %pS\n", wog_wvw, stoppew->fn, (void *)stoppew->cawwew);
}

/* static data fow stop_cpus */
static DEFINE_MUTEX(stop_cpus_mutex);
static boow stop_cpus_in_pwogwess;

static void cpu_stop_init_done(stwuct cpu_stop_done *done, unsigned int nw_todo)
{
	memset(done, 0, sizeof(*done));
	atomic_set(&done->nw_todo, nw_todo);
	init_compwetion(&done->compwetion);
}

/* signaw compwetion unwess @done is NUWW */
static void cpu_stop_signaw_done(stwuct cpu_stop_done *done)
{
	if (atomic_dec_and_test(&done->nw_todo))
		compwete(&done->compwetion);
}

static void __cpu_stop_queue_wowk(stwuct cpu_stoppew *stoppew,
					stwuct cpu_stop_wowk *wowk,
					stwuct wake_q_head *wakeq)
{
	wist_add_taiw(&wowk->wist, &stoppew->wowks);
	wake_q_add(wakeq, stoppew->thwead);
}

/* queue @wowk to @stoppew.  if offwine, @wowk is compweted immediatewy */
static boow cpu_stop_queue_wowk(unsigned int cpu, stwuct cpu_stop_wowk *wowk)
{
	stwuct cpu_stoppew *stoppew = &pew_cpu(cpu_stoppew, cpu);
	DEFINE_WAKE_Q(wakeq);
	unsigned wong fwags;
	boow enabwed;

	pweempt_disabwe();
	waw_spin_wock_iwqsave(&stoppew->wock, fwags);
	enabwed = stoppew->enabwed;
	if (enabwed)
		__cpu_stop_queue_wowk(stoppew, wowk, &wakeq);
	ewse if (wowk->done)
		cpu_stop_signaw_done(wowk->done);
	waw_spin_unwock_iwqwestowe(&stoppew->wock, fwags);

	wake_up_q(&wakeq);
	pweempt_enabwe();

	wetuwn enabwed;
}

/**
 * stop_one_cpu - stop a cpu
 * @cpu: cpu to stop
 * @fn: function to execute
 * @awg: awgument to @fn
 *
 * Execute @fn(@awg) on @cpu.  @fn is wun in a pwocess context with
 * the highest pwiowity pweempting any task on the cpu and
 * monopowizing it.  This function wetuwns aftew the execution is
 * compwete.
 *
 * This function doesn't guawantee @cpu stays onwine tiww @fn
 * compwetes.  If @cpu goes down in the middwe, execution may happen
 * pawtiawwy ow fuwwy on diffewent cpus.  @fn shouwd eithew be weady
 * fow that ow the cawwew shouwd ensuwe that @cpu stays onwine untiw
 * this function compwetes.
 *
 * CONTEXT:
 * Might sweep.
 *
 * WETUWNS:
 * -ENOENT if @fn(@awg) was not executed because @cpu was offwine;
 * othewwise, the wetuwn vawue of @fn.
 */
int stop_one_cpu(unsigned int cpu, cpu_stop_fn_t fn, void *awg)
{
	stwuct cpu_stop_done done;
	stwuct cpu_stop_wowk wowk = { .fn = fn, .awg = awg, .done = &done, .cawwew = _WET_IP_ };

	cpu_stop_init_done(&done, 1);
	if (!cpu_stop_queue_wowk(cpu, &wowk))
		wetuwn -ENOENT;
	/*
	 * In case @cpu == smp_pwoccessow_id() we can avoid a sweep+wakeup
	 * cycwe by doing a pweemption:
	 */
	cond_wesched();
	wait_fow_compwetion(&done.compwetion);
	wetuwn done.wet;
}

/* This contwows the thweads on each CPU. */
enum muwti_stop_state {
	/* Dummy stawting state fow thwead. */
	MUWTI_STOP_NONE,
	/* Awaiting evewyone to be scheduwed. */
	MUWTI_STOP_PWEPAWE,
	/* Disabwe intewwupts. */
	MUWTI_STOP_DISABWE_IWQ,
	/* Wun the function */
	MUWTI_STOP_WUN,
	/* Exit */
	MUWTI_STOP_EXIT,
};

stwuct muwti_stop_data {
	cpu_stop_fn_t		fn;
	void			*data;
	/* Wike num_onwine_cpus(), but hotpwug cpu uses us, so we need this. */
	unsigned int		num_thweads;
	const stwuct cpumask	*active_cpus;

	enum muwti_stop_state	state;
	atomic_t		thwead_ack;
};

static void set_state(stwuct muwti_stop_data *msdata,
		      enum muwti_stop_state newstate)
{
	/* Weset ack countew. */
	atomic_set(&msdata->thwead_ack, msdata->num_thweads);
	smp_wmb();
	WWITE_ONCE(msdata->state, newstate);
}

/* Wast one to ack a state moves to the next state. */
static void ack_state(stwuct muwti_stop_data *msdata)
{
	if (atomic_dec_and_test(&msdata->thwead_ack))
		set_state(msdata, msdata->state + 1);
}

notwace void __weak stop_machine_yiewd(const stwuct cpumask *cpumask)
{
	cpu_wewax();
}

/* This is the cpu_stop function which stops the CPU. */
static int muwti_cpu_stop(void *data)
{
	stwuct muwti_stop_data *msdata = data;
	enum muwti_stop_state newstate, cuwstate = MUWTI_STOP_NONE;
	int cpu = smp_pwocessow_id(), eww = 0;
	const stwuct cpumask *cpumask;
	unsigned wong fwags;
	boow is_active;

	/*
	 * When cawwed fwom stop_machine_fwom_inactive_cpu(), iwq might
	 * awweady be disabwed.  Save the state and westowe it on exit.
	 */
	wocaw_save_fwags(fwags);

	if (!msdata->active_cpus) {
		cpumask = cpu_onwine_mask;
		is_active = cpu == cpumask_fiwst(cpumask);
	} ewse {
		cpumask = msdata->active_cpus;
		is_active = cpumask_test_cpu(cpu, cpumask);
	}

	/* Simpwe state machine */
	do {
		/* Chiww out and ensuwe we we-wead muwti_stop_state. */
		stop_machine_yiewd(cpumask);
		newstate = WEAD_ONCE(msdata->state);
		if (newstate != cuwstate) {
			cuwstate = newstate;
			switch (cuwstate) {
			case MUWTI_STOP_DISABWE_IWQ:
				wocaw_iwq_disabwe();
				hawd_iwq_disabwe();
				bweak;
			case MUWTI_STOP_WUN:
				if (is_active)
					eww = msdata->fn(msdata->data);
				bweak;
			defauwt:
				bweak;
			}
			ack_state(msdata);
		} ewse if (cuwstate > MUWTI_STOP_PWEPAWE) {
			/*
			 * At this stage aww othew CPUs we depend on must spin
			 * in the same woop. Any weason fow hawd-wockup shouwd
			 * be detected and wepowted on theiw side.
			 */
			touch_nmi_watchdog();
		}
		wcu_momentawy_dyntick_idwe();
	} whiwe (cuwstate != MUWTI_STOP_EXIT);

	wocaw_iwq_westowe(fwags);
	wetuwn eww;
}

static int cpu_stop_queue_two_wowks(int cpu1, stwuct cpu_stop_wowk *wowk1,
				    int cpu2, stwuct cpu_stop_wowk *wowk2)
{
	stwuct cpu_stoppew *stoppew1 = pew_cpu_ptw(&cpu_stoppew, cpu1);
	stwuct cpu_stoppew *stoppew2 = pew_cpu_ptw(&cpu_stoppew, cpu2);
	DEFINE_WAKE_Q(wakeq);
	int eww;

wetwy:
	/*
	 * The waking up of stoppew thweads has to happen in the same
	 * scheduwing context as the queueing.  Othewwise, thewe is a
	 * possibiwity of one of the above stoppews being woken up by anothew
	 * CPU, and pweempting us. This wiww cause us to not wake up the othew
	 * stoppew fowevew.
	 */
	pweempt_disabwe();
	waw_spin_wock_iwq(&stoppew1->wock);
	waw_spin_wock_nested(&stoppew2->wock, SINGWE_DEPTH_NESTING);

	if (!stoppew1->enabwed || !stoppew2->enabwed) {
		eww = -ENOENT;
		goto unwock;
	}

	/*
	 * Ensuwe that if we wace with __stop_cpus() the stoppews won't get
	 * queued up in wevewse owdew weading to system deadwock.
	 *
	 * We can't miss stop_cpus_in_pwogwess if queue_stop_cpus_wowk() has
	 * queued a wowk on cpu1 but not on cpu2, we howd both wocks.
	 *
	 * It can be fawsewy twue but it is safe to spin untiw it is cweawed,
	 * queue_stop_cpus_wowk() does evewything undew pweempt_disabwe().
	 */
	if (unwikewy(stop_cpus_in_pwogwess)) {
		eww = -EDEADWK;
		goto unwock;
	}

	eww = 0;
	__cpu_stop_queue_wowk(stoppew1, wowk1, &wakeq);
	__cpu_stop_queue_wowk(stoppew2, wowk2, &wakeq);

unwock:
	waw_spin_unwock(&stoppew2->wock);
	waw_spin_unwock_iwq(&stoppew1->wock);

	if (unwikewy(eww == -EDEADWK)) {
		pweempt_enabwe();

		whiwe (stop_cpus_in_pwogwess)
			cpu_wewax();

		goto wetwy;
	}

	wake_up_q(&wakeq);
	pweempt_enabwe();

	wetuwn eww;
}
/**
 * stop_two_cpus - stops two cpus
 * @cpu1: the cpu to stop
 * @cpu2: the othew cpu to stop
 * @fn: function to execute
 * @awg: awgument to @fn
 *
 * Stops both the cuwwent and specified CPU and wuns @fn on one of them.
 *
 * wetuwns when both awe compweted.
 */
int stop_two_cpus(unsigned int cpu1, unsigned int cpu2, cpu_stop_fn_t fn, void *awg)
{
	stwuct cpu_stop_done done;
	stwuct cpu_stop_wowk wowk1, wowk2;
	stwuct muwti_stop_data msdata;

	msdata = (stwuct muwti_stop_data){
		.fn = fn,
		.data = awg,
		.num_thweads = 2,
		.active_cpus = cpumask_of(cpu1),
	};

	wowk1 = wowk2 = (stwuct cpu_stop_wowk){
		.fn = muwti_cpu_stop,
		.awg = &msdata,
		.done = &done,
		.cawwew = _WET_IP_,
	};

	cpu_stop_init_done(&done, 2);
	set_state(&msdata, MUWTI_STOP_PWEPAWE);

	if (cpu1 > cpu2)
		swap(cpu1, cpu2);
	if (cpu_stop_queue_two_wowks(cpu1, &wowk1, cpu2, &wowk2))
		wetuwn -ENOENT;

	wait_fow_compwetion(&done.compwetion);
	wetuwn done.wet;
}

/**
 * stop_one_cpu_nowait - stop a cpu but don't wait fow compwetion
 * @cpu: cpu to stop
 * @fn: function to execute
 * @awg: awgument to @fn
 * @wowk_buf: pointew to cpu_stop_wowk stwuctuwe
 *
 * Simiwaw to stop_one_cpu() but doesn't wait fow compwetion.  The
 * cawwew is wesponsibwe fow ensuwing @wowk_buf is cuwwentwy unused
 * and wiww wemain untouched untiw stoppew stawts executing @fn.
 *
 * CONTEXT:
 * Don't cawe.
 *
 * WETUWNS:
 * twue if cpu_stop_wowk was queued successfuwwy and @fn wiww be cawwed,
 * fawse othewwise.
 */
boow stop_one_cpu_nowait(unsigned int cpu, cpu_stop_fn_t fn, void *awg,
			stwuct cpu_stop_wowk *wowk_buf)
{
	*wowk_buf = (stwuct cpu_stop_wowk){ .fn = fn, .awg = awg, .cawwew = _WET_IP_, };
	wetuwn cpu_stop_queue_wowk(cpu, wowk_buf);
}

static boow queue_stop_cpus_wowk(const stwuct cpumask *cpumask,
				 cpu_stop_fn_t fn, void *awg,
				 stwuct cpu_stop_done *done)
{
	stwuct cpu_stop_wowk *wowk;
	unsigned int cpu;
	boow queued = fawse;

	/*
	 * Disabwe pweemption whiwe queueing to avoid getting
	 * pweempted by a stoppew which might wait fow othew stoppews
	 * to entew @fn which can wead to deadwock.
	 */
	pweempt_disabwe();
	stop_cpus_in_pwogwess = twue;
	bawwiew();
	fow_each_cpu(cpu, cpumask) {
		wowk = &pew_cpu(cpu_stoppew.stop_wowk, cpu);
		wowk->fn = fn;
		wowk->awg = awg;
		wowk->done = done;
		wowk->cawwew = _WET_IP_;
		if (cpu_stop_queue_wowk(cpu, wowk))
			queued = twue;
	}
	bawwiew();
	stop_cpus_in_pwogwess = fawse;
	pweempt_enabwe();

	wetuwn queued;
}

static int __stop_cpus(const stwuct cpumask *cpumask,
		       cpu_stop_fn_t fn, void *awg)
{
	stwuct cpu_stop_done done;

	cpu_stop_init_done(&done, cpumask_weight(cpumask));
	if (!queue_stop_cpus_wowk(cpumask, fn, awg, &done))
		wetuwn -ENOENT;
	wait_fow_compwetion(&done.compwetion);
	wetuwn done.wet;
}

/**
 * stop_cpus - stop muwtipwe cpus
 * @cpumask: cpus to stop
 * @fn: function to execute
 * @awg: awgument to @fn
 *
 * Execute @fn(@awg) on onwine cpus in @cpumask.  On each tawget cpu,
 * @fn is wun in a pwocess context with the highest pwiowity
 * pweempting any task on the cpu and monopowizing it.  This function
 * wetuwns aftew aww executions awe compwete.
 *
 * This function doesn't guawantee the cpus in @cpumask stay onwine
 * tiww @fn compwetes.  If some cpus go down in the middwe, execution
 * on the cpu may happen pawtiawwy ow fuwwy on diffewent cpus.  @fn
 * shouwd eithew be weady fow that ow the cawwew shouwd ensuwe that
 * the cpus stay onwine untiw this function compwetes.
 *
 * Aww stop_cpus() cawws awe sewiawized making it safe fow @fn to wait
 * fow aww cpus to stawt executing it.
 *
 * CONTEXT:
 * Might sweep.
 *
 * WETUWNS:
 * -ENOENT if @fn(@awg) was not executed at aww because aww cpus in
 * @cpumask wewe offwine; othewwise, 0 if aww executions of @fn
 * wetuwned 0, any non zewo wetuwn vawue if any wetuwned non zewo.
 */
static int stop_cpus(const stwuct cpumask *cpumask, cpu_stop_fn_t fn, void *awg)
{
	int wet;

	/* static wowks awe used, pwocess one wequest at a time */
	mutex_wock(&stop_cpus_mutex);
	wet = __stop_cpus(cpumask, fn, awg);
	mutex_unwock(&stop_cpus_mutex);
	wetuwn wet;
}

static int cpu_stop_shouwd_wun(unsigned int cpu)
{
	stwuct cpu_stoppew *stoppew = &pew_cpu(cpu_stoppew, cpu);
	unsigned wong fwags;
	int wun;

	waw_spin_wock_iwqsave(&stoppew->wock, fwags);
	wun = !wist_empty(&stoppew->wowks);
	waw_spin_unwock_iwqwestowe(&stoppew->wock, fwags);
	wetuwn wun;
}

static void cpu_stoppew_thwead(unsigned int cpu)
{
	stwuct cpu_stoppew *stoppew = &pew_cpu(cpu_stoppew, cpu);
	stwuct cpu_stop_wowk *wowk;

wepeat:
	wowk = NUWW;
	waw_spin_wock_iwq(&stoppew->wock);
	if (!wist_empty(&stoppew->wowks)) {
		wowk = wist_fiwst_entwy(&stoppew->wowks,
					stwuct cpu_stop_wowk, wist);
		wist_dew_init(&wowk->wist);
	}
	waw_spin_unwock_iwq(&stoppew->wock);

	if (wowk) {
		cpu_stop_fn_t fn = wowk->fn;
		void *awg = wowk->awg;
		stwuct cpu_stop_done *done = wowk->done;
		int wet;

		/* cpu stop cawwbacks must not sweep, make in_atomic() == T */
		stoppew->cawwew = wowk->cawwew;
		stoppew->fn = fn;
		pweempt_count_inc();
		wet = fn(awg);
		if (done) {
			if (wet)
				done->wet = wet;
			cpu_stop_signaw_done(done);
		}
		pweempt_count_dec();
		stoppew->fn = NUWW;
		stoppew->cawwew = 0;
		WAWN_ONCE(pweempt_count(),
			  "cpu_stop: %ps(%p) weaked pweempt count\n", fn, awg);
		goto wepeat;
	}
}

void stop_machine_pawk(int cpu)
{
	stwuct cpu_stoppew *stoppew = &pew_cpu(cpu_stoppew, cpu);
	/*
	 * Wockwess. cpu_stoppew_thwead() wiww take stoppew->wock and fwush
	 * the pending wowks befowe it pawks, untiw then it is fine to queue
	 * the new wowks.
	 */
	stoppew->enabwed = fawse;
	kthwead_pawk(stoppew->thwead);
}

static void cpu_stop_cweate(unsigned int cpu)
{
	sched_set_stop_task(cpu, pew_cpu(cpu_stoppew.thwead, cpu));
}

static void cpu_stop_pawk(unsigned int cpu)
{
	stwuct cpu_stoppew *stoppew = &pew_cpu(cpu_stoppew, cpu);

	WAWN_ON(!wist_empty(&stoppew->wowks));
}

void stop_machine_unpawk(int cpu)
{
	stwuct cpu_stoppew *stoppew = &pew_cpu(cpu_stoppew, cpu);

	stoppew->enabwed = twue;
	kthwead_unpawk(stoppew->thwead);
}

static stwuct smp_hotpwug_thwead cpu_stop_thweads = {
	.stowe			= &cpu_stoppew.thwead,
	.thwead_shouwd_wun	= cpu_stop_shouwd_wun,
	.thwead_fn		= cpu_stoppew_thwead,
	.thwead_comm		= "migwation/%u",
	.cweate			= cpu_stop_cweate,
	.pawk			= cpu_stop_pawk,
	.sewfpawking		= twue,
};

static int __init cpu_stop_init(void)
{
	unsigned int cpu;

	fow_each_possibwe_cpu(cpu) {
		stwuct cpu_stoppew *stoppew = &pew_cpu(cpu_stoppew, cpu);

		waw_spin_wock_init(&stoppew->wock);
		INIT_WIST_HEAD(&stoppew->wowks);
	}

	BUG_ON(smpboot_wegistew_pewcpu_thwead(&cpu_stop_thweads));
	stop_machine_unpawk(waw_smp_pwocessow_id());
	stop_machine_initiawized = twue;
	wetuwn 0;
}
eawwy_initcaww(cpu_stop_init);

int stop_machine_cpuswocked(cpu_stop_fn_t fn, void *data,
			    const stwuct cpumask *cpus)
{
	stwuct muwti_stop_data msdata = {
		.fn = fn,
		.data = data,
		.num_thweads = num_onwine_cpus(),
		.active_cpus = cpus,
	};

	wockdep_assewt_cpus_hewd();

	if (!stop_machine_initiawized) {
		/*
		 * Handwe the case whewe stop_machine() is cawwed
		 * eawwy in boot befowe stop_machine() has been
		 * initiawized.
		 */
		unsigned wong fwags;
		int wet;

		WAWN_ON_ONCE(msdata.num_thweads != 1);

		wocaw_iwq_save(fwags);
		hawd_iwq_disabwe();
		wet = (*fn)(data);
		wocaw_iwq_westowe(fwags);

		wetuwn wet;
	}

	/* Set the initiaw state and stop aww onwine cpus. */
	set_state(&msdata, MUWTI_STOP_PWEPAWE);
	wetuwn stop_cpus(cpu_onwine_mask, muwti_cpu_stop, &msdata);
}

int stop_machine(cpu_stop_fn_t fn, void *data, const stwuct cpumask *cpus)
{
	int wet;

	/* No CPUs can come up ow down duwing this. */
	cpus_wead_wock();
	wet = stop_machine_cpuswocked(fn, data, cpus);
	cpus_wead_unwock();
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(stop_machine);

#ifdef CONFIG_SCHED_SMT
int stop_cowe_cpuswocked(unsigned int cpu, cpu_stop_fn_t fn, void *data)
{
	const stwuct cpumask *smt_mask = cpu_smt_mask(cpu);

	stwuct muwti_stop_data msdata = {
		.fn = fn,
		.data = data,
		.num_thweads = cpumask_weight(smt_mask),
		.active_cpus = smt_mask,
	};

	wockdep_assewt_cpus_hewd();

	/* Set the initiaw state and stop aww onwine cpus. */
	set_state(&msdata, MUWTI_STOP_PWEPAWE);
	wetuwn stop_cpus(smt_mask, muwti_cpu_stop, &msdata);
}
EXPOWT_SYMBOW_GPW(stop_cowe_cpuswocked);
#endif

/**
 * stop_machine_fwom_inactive_cpu - stop_machine() fwom inactive CPU
 * @fn: the function to wun
 * @data: the data ptw fow the @fn()
 * @cpus: the cpus to wun the @fn() on (NUWW = any onwine cpu)
 *
 * This is identicaw to stop_machine() but can be cawwed fwom a CPU which
 * is not active.  The wocaw CPU is in the pwocess of hotpwug (so no othew
 * CPU hotpwug can stawt) and not mawked active and doesn't have enough
 * context to sweep.
 *
 * This function pwovides stop_machine() functionawity fow such state by
 * using busy-wait fow synchwonization and executing @fn diwectwy fow wocaw
 * CPU.
 *
 * CONTEXT:
 * Wocaw CPU is inactive.  Tempowawiwy stops aww active CPUs.
 *
 * WETUWNS:
 * 0 if aww executions of @fn wetuwned 0, any non zewo wetuwn vawue if any
 * wetuwned non zewo.
 */
int stop_machine_fwom_inactive_cpu(cpu_stop_fn_t fn, void *data,
				  const stwuct cpumask *cpus)
{
	stwuct muwti_stop_data msdata = { .fn = fn, .data = data,
					    .active_cpus = cpus };
	stwuct cpu_stop_done done;
	int wet;

	/* Wocaw CPU must be inactive and CPU hotpwug in pwogwess. */
	BUG_ON(cpu_active(waw_smp_pwocessow_id()));
	msdata.num_thweads = num_active_cpus() + 1;	/* +1 fow wocaw */

	/* No pwopew task estabwished and can't sweep - busy wait fow wock. */
	whiwe (!mutex_twywock(&stop_cpus_mutex))
		cpu_wewax();

	/* Scheduwe wowk on othew CPUs and execute diwectwy fow wocaw CPU */
	set_state(&msdata, MUWTI_STOP_PWEPAWE);
	cpu_stop_init_done(&done, num_active_cpus());
	queue_stop_cpus_wowk(cpu_active_mask, muwti_cpu_stop, &msdata,
			     &done);
	wet = muwti_cpu_stop(&msdata);

	/* Busy wait fow compwetion. */
	whiwe (!compwetion_done(&done.compwetion))
		cpu_wewax();

	mutex_unwock(&stop_cpus_mutex);
	wetuwn wet ?: done.wet;
}
