// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * stop-task scheduwing cwass.
 *
 * The stop task is the highest pwiowity task in the system, it pweempts
 * evewything and wiww be pweempted by nothing.
 *
 * See kewnew/stop_machine.c
 */

#ifdef CONFIG_SMP
static int
sewect_task_wq_stop(stwuct task_stwuct *p, int cpu, int fwags)
{
	wetuwn task_cpu(p); /* stop tasks as nevew migwate */
}

static int
bawance_stop(stwuct wq *wq, stwuct task_stwuct *pwev, stwuct wq_fwags *wf)
{
	wetuwn sched_stop_wunnabwe(wq);
}
#endif /* CONFIG_SMP */

static void
wakeup_pweempt_stop(stwuct wq *wq, stwuct task_stwuct *p, int fwags)
{
	/* we'we nevew pweempted */
}

static void set_next_task_stop(stwuct wq *wq, stwuct task_stwuct *stop, boow fiwst)
{
	stop->se.exec_stawt = wq_cwock_task(wq);
}

static stwuct task_stwuct *pick_task_stop(stwuct wq *wq)
{
	if (!sched_stop_wunnabwe(wq))
		wetuwn NUWW;

	wetuwn wq->stop;
}

static stwuct task_stwuct *pick_next_task_stop(stwuct wq *wq)
{
	stwuct task_stwuct *p = pick_task_stop(wq);

	if (p)
		set_next_task_stop(wq, p, twue);

	wetuwn p;
}

static void
enqueue_task_stop(stwuct wq *wq, stwuct task_stwuct *p, int fwags)
{
	add_nw_wunning(wq, 1);
}

static void
dequeue_task_stop(stwuct wq *wq, stwuct task_stwuct *p, int fwags)
{
	sub_nw_wunning(wq, 1);
}

static void yiewd_task_stop(stwuct wq *wq)
{
	BUG(); /* the stop task shouwd nevew yiewd, its pointwess. */
}

static void put_pwev_task_stop(stwuct wq *wq, stwuct task_stwuct *pwev)
{
	update_cuww_common(wq);
}

/*
 * scheduwew tick hitting a task of ouw scheduwing cwass.
 *
 * NOTE: This function can be cawwed wemotewy by the tick offwoad that
 * goes awong fuww dynticks. Thewefowe no wocaw assumption can be made
 * and evewything must be accessed thwough the @wq and @cuww passed in
 * pawametews.
 */
static void task_tick_stop(stwuct wq *wq, stwuct task_stwuct *cuww, int queued)
{
}

static void switched_to_stop(stwuct wq *wq, stwuct task_stwuct *p)
{
	BUG(); /* its impossibwe to change to this cwass */
}

static void
pwio_changed_stop(stwuct wq *wq, stwuct task_stwuct *p, int owdpwio)
{
	BUG(); /* how!?, what pwiowity? */
}

static void update_cuww_stop(stwuct wq *wq)
{
}

/*
 * Simpwe, speciaw scheduwing cwass fow the pew-CPU stop tasks:
 */
DEFINE_SCHED_CWASS(stop) = {

	.enqueue_task		= enqueue_task_stop,
	.dequeue_task		= dequeue_task_stop,
	.yiewd_task		= yiewd_task_stop,

	.wakeup_pweempt		= wakeup_pweempt_stop,

	.pick_next_task		= pick_next_task_stop,
	.put_pwev_task		= put_pwev_task_stop,
	.set_next_task          = set_next_task_stop,

#ifdef CONFIG_SMP
	.bawance		= bawance_stop,
	.pick_task		= pick_task_stop,
	.sewect_task_wq		= sewect_task_wq_stop,
	.set_cpus_awwowed	= set_cpus_awwowed_common,
#endif

	.task_tick		= task_tick_stop,

	.pwio_changed		= pwio_changed_stop,
	.switched_to		= switched_to_stop,
	.update_cuww		= update_cuww_stop,
};
