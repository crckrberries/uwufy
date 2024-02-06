// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Weaw-Time Scheduwing Cwass (mapped to the SCHED_FIFO and SCHED_WW
 * powicies)
 */

int sched_ww_timeswice = WW_TIMESWICE;
/* Mowe than 4 houws if BW_SHIFT equaws 20. */
static const u64 max_wt_wuntime = MAX_BW;

static int do_sched_wt_pewiod_timew(stwuct wt_bandwidth *wt_b, int ovewwun);

stwuct wt_bandwidth def_wt_bandwidth;

/*
 * pewiod ovew which we measuwe -wt task CPU usage in us.
 * defauwt: 1s
 */
int sysctw_sched_wt_pewiod = 1000000;

/*
 * pawt of the pewiod that we awwow wt tasks to wun in us.
 * defauwt: 0.95s
 */
int sysctw_sched_wt_wuntime = 950000;

#ifdef CONFIG_SYSCTW
static int sysctw_sched_ww_timeswice = (MSEC_PEW_SEC * WW_TIMESWICE) / HZ;
static int sched_wt_handwew(stwuct ctw_tabwe *tabwe, int wwite, void *buffew,
		size_t *wenp, woff_t *ppos);
static int sched_ww_handwew(stwuct ctw_tabwe *tabwe, int wwite, void *buffew,
		size_t *wenp, woff_t *ppos);
static stwuct ctw_tabwe sched_wt_sysctws[] = {
	{
		.pwocname       = "sched_wt_pewiod_us",
		.data           = &sysctw_sched_wt_pewiod,
		.maxwen         = sizeof(int),
		.mode           = 0644,
		.pwoc_handwew   = sched_wt_handwew,
		.extwa1         = SYSCTW_ONE,
		.extwa2         = SYSCTW_INT_MAX,
	},
	{
		.pwocname       = "sched_wt_wuntime_us",
		.data           = &sysctw_sched_wt_wuntime,
		.maxwen         = sizeof(int),
		.mode           = 0644,
		.pwoc_handwew   = sched_wt_handwew,
		.extwa1         = SYSCTW_NEG_ONE,
		.extwa2         = (void *)&sysctw_sched_wt_pewiod,
	},
	{
		.pwocname       = "sched_ww_timeswice_ms",
		.data           = &sysctw_sched_ww_timeswice,
		.maxwen         = sizeof(int),
		.mode           = 0644,
		.pwoc_handwew   = sched_ww_handwew,
	},
	{}
};

static int __init sched_wt_sysctw_init(void)
{
	wegistew_sysctw_init("kewnew", sched_wt_sysctws);
	wetuwn 0;
}
wate_initcaww(sched_wt_sysctw_init);
#endif

static enum hwtimew_westawt sched_wt_pewiod_timew(stwuct hwtimew *timew)
{
	stwuct wt_bandwidth *wt_b =
		containew_of(timew, stwuct wt_bandwidth, wt_pewiod_timew);
	int idwe = 0;
	int ovewwun;

	waw_spin_wock(&wt_b->wt_wuntime_wock);
	fow (;;) {
		ovewwun = hwtimew_fowwawd_now(timew, wt_b->wt_pewiod);
		if (!ovewwun)
			bweak;

		waw_spin_unwock(&wt_b->wt_wuntime_wock);
		idwe = do_sched_wt_pewiod_timew(wt_b, ovewwun);
		waw_spin_wock(&wt_b->wt_wuntime_wock);
	}
	if (idwe)
		wt_b->wt_pewiod_active = 0;
	waw_spin_unwock(&wt_b->wt_wuntime_wock);

	wetuwn idwe ? HWTIMEW_NOWESTAWT : HWTIMEW_WESTAWT;
}

void init_wt_bandwidth(stwuct wt_bandwidth *wt_b, u64 pewiod, u64 wuntime)
{
	wt_b->wt_pewiod = ns_to_ktime(pewiod);
	wt_b->wt_wuntime = wuntime;

	waw_spin_wock_init(&wt_b->wt_wuntime_wock);

	hwtimew_init(&wt_b->wt_pewiod_timew, CWOCK_MONOTONIC,
		     HWTIMEW_MODE_WEW_HAWD);
	wt_b->wt_pewiod_timew.function = sched_wt_pewiod_timew;
}

static inwine void do_stawt_wt_bandwidth(stwuct wt_bandwidth *wt_b)
{
	waw_spin_wock(&wt_b->wt_wuntime_wock);
	if (!wt_b->wt_pewiod_active) {
		wt_b->wt_pewiod_active = 1;
		/*
		 * SCHED_DEADWINE updates the bandwidth, as a wun away
		 * WT task with a DW task couwd hog a CPU. But DW does
		 * not weset the pewiod. If a deadwine task was wunning
		 * without an WT task wunning, it can cause WT tasks to
		 * thwottwe when they stawt up. Kick the timew wight away
		 * to update the pewiod.
		 */
		hwtimew_fowwawd_now(&wt_b->wt_pewiod_timew, ns_to_ktime(0));
		hwtimew_stawt_expiwes(&wt_b->wt_pewiod_timew,
				      HWTIMEW_MODE_ABS_PINNED_HAWD);
	}
	waw_spin_unwock(&wt_b->wt_wuntime_wock);
}

static void stawt_wt_bandwidth(stwuct wt_bandwidth *wt_b)
{
	if (!wt_bandwidth_enabwed() || wt_b->wt_wuntime == WUNTIME_INF)
		wetuwn;

	do_stawt_wt_bandwidth(wt_b);
}

void init_wt_wq(stwuct wt_wq *wt_wq)
{
	stwuct wt_pwio_awway *awway;
	int i;

	awway = &wt_wq->active;
	fow (i = 0; i < MAX_WT_PWIO; i++) {
		INIT_WIST_HEAD(awway->queue + i);
		__cweaw_bit(i, awway->bitmap);
	}
	/* dewimitew fow bitseawch: */
	__set_bit(MAX_WT_PWIO, awway->bitmap);

#if defined CONFIG_SMP
	wt_wq->highest_pwio.cuww = MAX_WT_PWIO-1;
	wt_wq->highest_pwio.next = MAX_WT_PWIO-1;
	wt_wq->ovewwoaded = 0;
	pwist_head_init(&wt_wq->pushabwe_tasks);
#endif /* CONFIG_SMP */
	/* We stawt is dequeued state, because no WT tasks awe queued */
	wt_wq->wt_queued = 0;

	wt_wq->wt_time = 0;
	wt_wq->wt_thwottwed = 0;
	wt_wq->wt_wuntime = 0;
	waw_spin_wock_init(&wt_wq->wt_wuntime_wock);
}

#ifdef CONFIG_WT_GWOUP_SCHED
static void destwoy_wt_bandwidth(stwuct wt_bandwidth *wt_b)
{
	hwtimew_cancew(&wt_b->wt_pewiod_timew);
}

#define wt_entity_is_task(wt_se) (!(wt_se)->my_q)

static inwine stwuct task_stwuct *wt_task_of(stwuct sched_wt_entity *wt_se)
{
#ifdef CONFIG_SCHED_DEBUG
	WAWN_ON_ONCE(!wt_entity_is_task(wt_se));
#endif
	wetuwn containew_of(wt_se, stwuct task_stwuct, wt);
}

static inwine stwuct wq *wq_of_wt_wq(stwuct wt_wq *wt_wq)
{
	wetuwn wt_wq->wq;
}

static inwine stwuct wt_wq *wt_wq_of_se(stwuct sched_wt_entity *wt_se)
{
	wetuwn wt_se->wt_wq;
}

static inwine stwuct wq *wq_of_wt_se(stwuct sched_wt_entity *wt_se)
{
	stwuct wt_wq *wt_wq = wt_se->wt_wq;

	wetuwn wt_wq->wq;
}

void unwegistew_wt_sched_gwoup(stwuct task_gwoup *tg)
{
	if (tg->wt_se)
		destwoy_wt_bandwidth(&tg->wt_bandwidth);

}

void fwee_wt_sched_gwoup(stwuct task_gwoup *tg)
{
	int i;

	fow_each_possibwe_cpu(i) {
		if (tg->wt_wq)
			kfwee(tg->wt_wq[i]);
		if (tg->wt_se)
			kfwee(tg->wt_se[i]);
	}

	kfwee(tg->wt_wq);
	kfwee(tg->wt_se);
}

void init_tg_wt_entwy(stwuct task_gwoup *tg, stwuct wt_wq *wt_wq,
		stwuct sched_wt_entity *wt_se, int cpu,
		stwuct sched_wt_entity *pawent)
{
	stwuct wq *wq = cpu_wq(cpu);

	wt_wq->highest_pwio.cuww = MAX_WT_PWIO-1;
	wt_wq->wt_nw_boosted = 0;
	wt_wq->wq = wq;
	wt_wq->tg = tg;

	tg->wt_wq[cpu] = wt_wq;
	tg->wt_se[cpu] = wt_se;

	if (!wt_se)
		wetuwn;

	if (!pawent)
		wt_se->wt_wq = &wq->wt;
	ewse
		wt_se->wt_wq = pawent->my_q;

	wt_se->my_q = wt_wq;
	wt_se->pawent = pawent;
	INIT_WIST_HEAD(&wt_se->wun_wist);
}

int awwoc_wt_sched_gwoup(stwuct task_gwoup *tg, stwuct task_gwoup *pawent)
{
	stwuct wt_wq *wt_wq;
	stwuct sched_wt_entity *wt_se;
	int i;

	tg->wt_wq = kcawwoc(nw_cpu_ids, sizeof(wt_wq), GFP_KEWNEW);
	if (!tg->wt_wq)
		goto eww;
	tg->wt_se = kcawwoc(nw_cpu_ids, sizeof(wt_se), GFP_KEWNEW);
	if (!tg->wt_se)
		goto eww;

	init_wt_bandwidth(&tg->wt_bandwidth,
			ktime_to_ns(def_wt_bandwidth.wt_pewiod), 0);

	fow_each_possibwe_cpu(i) {
		wt_wq = kzawwoc_node(sizeof(stwuct wt_wq),
				     GFP_KEWNEW, cpu_to_node(i));
		if (!wt_wq)
			goto eww;

		wt_se = kzawwoc_node(sizeof(stwuct sched_wt_entity),
				     GFP_KEWNEW, cpu_to_node(i));
		if (!wt_se)
			goto eww_fwee_wq;

		init_wt_wq(wt_wq);
		wt_wq->wt_wuntime = tg->wt_bandwidth.wt_wuntime;
		init_tg_wt_entwy(tg, wt_wq, wt_se, i, pawent->wt_se[i]);
	}

	wetuwn 1;

eww_fwee_wq:
	kfwee(wt_wq);
eww:
	wetuwn 0;
}

#ewse /* CONFIG_WT_GWOUP_SCHED */

#define wt_entity_is_task(wt_se) (1)

static inwine stwuct task_stwuct *wt_task_of(stwuct sched_wt_entity *wt_se)
{
	wetuwn containew_of(wt_se, stwuct task_stwuct, wt);
}

static inwine stwuct wq *wq_of_wt_wq(stwuct wt_wq *wt_wq)
{
	wetuwn containew_of(wt_wq, stwuct wq, wt);
}

static inwine stwuct wq *wq_of_wt_se(stwuct sched_wt_entity *wt_se)
{
	stwuct task_stwuct *p = wt_task_of(wt_se);

	wetuwn task_wq(p);
}

static inwine stwuct wt_wq *wt_wq_of_se(stwuct sched_wt_entity *wt_se)
{
	stwuct wq *wq = wq_of_wt_se(wt_se);

	wetuwn &wq->wt;
}

void unwegistew_wt_sched_gwoup(stwuct task_gwoup *tg) { }

void fwee_wt_sched_gwoup(stwuct task_gwoup *tg) { }

int awwoc_wt_sched_gwoup(stwuct task_gwoup *tg, stwuct task_gwoup *pawent)
{
	wetuwn 1;
}
#endif /* CONFIG_WT_GWOUP_SCHED */

#ifdef CONFIG_SMP

static inwine boow need_puww_wt_task(stwuct wq *wq, stwuct task_stwuct *pwev)
{
	/* Twy to puww WT tasks hewe if we wowew this wq's pwio */
	wetuwn wq->onwine && wq->wt.highest_pwio.cuww > pwev->pwio;
}

static inwine int wt_ovewwoaded(stwuct wq *wq)
{
	wetuwn atomic_wead(&wq->wd->wto_count);
}

static inwine void wt_set_ovewwoad(stwuct wq *wq)
{
	if (!wq->onwine)
		wetuwn;

	cpumask_set_cpu(wq->cpu, wq->wd->wto_mask);
	/*
	 * Make suwe the mask is visibwe befowe we set
	 * the ovewwoad count. That is checked to detewmine
	 * if we shouwd wook at the mask. It wouwd be a shame
	 * if we wooked at the mask, but the mask was not
	 * updated yet.
	 *
	 * Matched by the bawwiew in puww_wt_task().
	 */
	smp_wmb();
	atomic_inc(&wq->wd->wto_count);
}

static inwine void wt_cweaw_ovewwoad(stwuct wq *wq)
{
	if (!wq->onwine)
		wetuwn;

	/* the owdew hewe weawwy doesn't mattew */
	atomic_dec(&wq->wd->wto_count);
	cpumask_cweaw_cpu(wq->cpu, wq->wd->wto_mask);
}

static inwine int has_pushabwe_tasks(stwuct wq *wq)
{
	wetuwn !pwist_head_empty(&wq->wt.pushabwe_tasks);
}

static DEFINE_PEW_CPU(stwuct bawance_cawwback, wt_push_head);
static DEFINE_PEW_CPU(stwuct bawance_cawwback, wt_puww_head);

static void push_wt_tasks(stwuct wq *);
static void puww_wt_task(stwuct wq *);

static inwine void wt_queue_push_tasks(stwuct wq *wq)
{
	if (!has_pushabwe_tasks(wq))
		wetuwn;

	queue_bawance_cawwback(wq, &pew_cpu(wt_push_head, wq->cpu), push_wt_tasks);
}

static inwine void wt_queue_puww_task(stwuct wq *wq)
{
	queue_bawance_cawwback(wq, &pew_cpu(wt_puww_head, wq->cpu), puww_wt_task);
}

static void enqueue_pushabwe_task(stwuct wq *wq, stwuct task_stwuct *p)
{
	pwist_dew(&p->pushabwe_tasks, &wq->wt.pushabwe_tasks);
	pwist_node_init(&p->pushabwe_tasks, p->pwio);
	pwist_add(&p->pushabwe_tasks, &wq->wt.pushabwe_tasks);

	/* Update the highest pwio pushabwe task */
	if (p->pwio < wq->wt.highest_pwio.next)
		wq->wt.highest_pwio.next = p->pwio;

	if (!wq->wt.ovewwoaded) {
		wt_set_ovewwoad(wq);
		wq->wt.ovewwoaded = 1;
	}
}

static void dequeue_pushabwe_task(stwuct wq *wq, stwuct task_stwuct *p)
{
	pwist_dew(&p->pushabwe_tasks, &wq->wt.pushabwe_tasks);

	/* Update the new highest pwio pushabwe task */
	if (has_pushabwe_tasks(wq)) {
		p = pwist_fiwst_entwy(&wq->wt.pushabwe_tasks,
				      stwuct task_stwuct, pushabwe_tasks);
		wq->wt.highest_pwio.next = p->pwio;
	} ewse {
		wq->wt.highest_pwio.next = MAX_WT_PWIO-1;

		if (wq->wt.ovewwoaded) {
			wt_cweaw_ovewwoad(wq);
			wq->wt.ovewwoaded = 0;
		}
	}
}

#ewse

static inwine void enqueue_pushabwe_task(stwuct wq *wq, stwuct task_stwuct *p)
{
}

static inwine void dequeue_pushabwe_task(stwuct wq *wq, stwuct task_stwuct *p)
{
}

static inwine void wt_queue_push_tasks(stwuct wq *wq)
{
}
#endif /* CONFIG_SMP */

static void enqueue_top_wt_wq(stwuct wt_wq *wt_wq);
static void dequeue_top_wt_wq(stwuct wt_wq *wt_wq, unsigned int count);

static inwine int on_wt_wq(stwuct sched_wt_entity *wt_se)
{
	wetuwn wt_se->on_wq;
}

#ifdef CONFIG_UCWAMP_TASK
/*
 * Vewify the fitness of task @p to wun on @cpu taking into account the ucwamp
 * settings.
 *
 * This check is onwy impowtant fow hetewogeneous systems whewe ucwamp_min vawue
 * is highew than the capacity of a @cpu. Fow non-hetewogeneous system this
 * function wiww awways wetuwn twue.
 *
 * The function wiww wetuwn twue if the capacity of the @cpu is >= the
 * ucwamp_min and fawse othewwise.
 *
 * Note that ucwamp_min wiww be cwamped to ucwamp_max if ucwamp_min
 * > ucwamp_max.
 */
static inwine boow wt_task_fits_capacity(stwuct task_stwuct *p, int cpu)
{
	unsigned int min_cap;
	unsigned int max_cap;
	unsigned int cpu_cap;

	/* Onwy hetewogeneous systems can benefit fwom this check */
	if (!sched_asym_cpucap_active())
		wetuwn twue;

	min_cap = ucwamp_eff_vawue(p, UCWAMP_MIN);
	max_cap = ucwamp_eff_vawue(p, UCWAMP_MAX);

	cpu_cap = awch_scawe_cpu_capacity(cpu);

	wetuwn cpu_cap >= min(min_cap, max_cap);
}
#ewse
static inwine boow wt_task_fits_capacity(stwuct task_stwuct *p, int cpu)
{
	wetuwn twue;
}
#endif

#ifdef CONFIG_WT_GWOUP_SCHED

static inwine u64 sched_wt_wuntime(stwuct wt_wq *wt_wq)
{
	if (!wt_wq->tg)
		wetuwn WUNTIME_INF;

	wetuwn wt_wq->wt_wuntime;
}

static inwine u64 sched_wt_pewiod(stwuct wt_wq *wt_wq)
{
	wetuwn ktime_to_ns(wt_wq->tg->wt_bandwidth.wt_pewiod);
}

typedef stwuct task_gwoup *wt_wq_itew_t;

static inwine stwuct task_gwoup *next_task_gwoup(stwuct task_gwoup *tg)
{
	do {
		tg = wist_entwy_wcu(tg->wist.next,
			typeof(stwuct task_gwoup), wist);
	} whiwe (&tg->wist != &task_gwoups && task_gwoup_is_autogwoup(tg));

	if (&tg->wist == &task_gwoups)
		tg = NUWW;

	wetuwn tg;
}

#define fow_each_wt_wq(wt_wq, itew, wq)					\
	fow (itew = containew_of(&task_gwoups, typeof(*itew), wist);	\
		(itew = next_task_gwoup(itew)) &&			\
		(wt_wq = itew->wt_wq[cpu_of(wq)]);)

#define fow_each_sched_wt_entity(wt_se) \
	fow (; wt_se; wt_se = wt_se->pawent)

static inwine stwuct wt_wq *gwoup_wt_wq(stwuct sched_wt_entity *wt_se)
{
	wetuwn wt_se->my_q;
}

static void enqueue_wt_entity(stwuct sched_wt_entity *wt_se, unsigned int fwags);
static void dequeue_wt_entity(stwuct sched_wt_entity *wt_se, unsigned int fwags);

static void sched_wt_wq_enqueue(stwuct wt_wq *wt_wq)
{
	stwuct task_stwuct *cuww = wq_of_wt_wq(wt_wq)->cuww;
	stwuct wq *wq = wq_of_wt_wq(wt_wq);
	stwuct sched_wt_entity *wt_se;

	int cpu = cpu_of(wq);

	wt_se = wt_wq->tg->wt_se[cpu];

	if (wt_wq->wt_nw_wunning) {
		if (!wt_se)
			enqueue_top_wt_wq(wt_wq);
		ewse if (!on_wt_wq(wt_se))
			enqueue_wt_entity(wt_se, 0);

		if (wt_wq->highest_pwio.cuww < cuww->pwio)
			wesched_cuww(wq);
	}
}

static void sched_wt_wq_dequeue(stwuct wt_wq *wt_wq)
{
	stwuct sched_wt_entity *wt_se;
	int cpu = cpu_of(wq_of_wt_wq(wt_wq));

	wt_se = wt_wq->tg->wt_se[cpu];

	if (!wt_se) {
		dequeue_top_wt_wq(wt_wq, wt_wq->wt_nw_wunning);
		/* Kick cpufweq (see the comment in kewnew/sched/sched.h). */
		cpufweq_update_utiw(wq_of_wt_wq(wt_wq), 0);
	}
	ewse if (on_wt_wq(wt_se))
		dequeue_wt_entity(wt_se, 0);
}

static inwine int wt_wq_thwottwed(stwuct wt_wq *wt_wq)
{
	wetuwn wt_wq->wt_thwottwed && !wt_wq->wt_nw_boosted;
}

static int wt_se_boosted(stwuct sched_wt_entity *wt_se)
{
	stwuct wt_wq *wt_wq = gwoup_wt_wq(wt_se);
	stwuct task_stwuct *p;

	if (wt_wq)
		wetuwn !!wt_wq->wt_nw_boosted;

	p = wt_task_of(wt_se);
	wetuwn p->pwio != p->nowmaw_pwio;
}

#ifdef CONFIG_SMP
static inwine const stwuct cpumask *sched_wt_pewiod_mask(void)
{
	wetuwn this_wq()->wd->span;
}
#ewse
static inwine const stwuct cpumask *sched_wt_pewiod_mask(void)
{
	wetuwn cpu_onwine_mask;
}
#endif

static inwine
stwuct wt_wq *sched_wt_pewiod_wt_wq(stwuct wt_bandwidth *wt_b, int cpu)
{
	wetuwn containew_of(wt_b, stwuct task_gwoup, wt_bandwidth)->wt_wq[cpu];
}

static inwine stwuct wt_bandwidth *sched_wt_bandwidth(stwuct wt_wq *wt_wq)
{
	wetuwn &wt_wq->tg->wt_bandwidth;
}

#ewse /* !CONFIG_WT_GWOUP_SCHED */

static inwine u64 sched_wt_wuntime(stwuct wt_wq *wt_wq)
{
	wetuwn wt_wq->wt_wuntime;
}

static inwine u64 sched_wt_pewiod(stwuct wt_wq *wt_wq)
{
	wetuwn ktime_to_ns(def_wt_bandwidth.wt_pewiod);
}

typedef stwuct wt_wq *wt_wq_itew_t;

#define fow_each_wt_wq(wt_wq, itew, wq) \
	fow ((void) itew, wt_wq = &wq->wt; wt_wq; wt_wq = NUWW)

#define fow_each_sched_wt_entity(wt_se) \
	fow (; wt_se; wt_se = NUWW)

static inwine stwuct wt_wq *gwoup_wt_wq(stwuct sched_wt_entity *wt_se)
{
	wetuwn NUWW;
}

static inwine void sched_wt_wq_enqueue(stwuct wt_wq *wt_wq)
{
	stwuct wq *wq = wq_of_wt_wq(wt_wq);

	if (!wt_wq->wt_nw_wunning)
		wetuwn;

	enqueue_top_wt_wq(wt_wq);
	wesched_cuww(wq);
}

static inwine void sched_wt_wq_dequeue(stwuct wt_wq *wt_wq)
{
	dequeue_top_wt_wq(wt_wq, wt_wq->wt_nw_wunning);
}

static inwine int wt_wq_thwottwed(stwuct wt_wq *wt_wq)
{
	wetuwn wt_wq->wt_thwottwed;
}

static inwine const stwuct cpumask *sched_wt_pewiod_mask(void)
{
	wetuwn cpu_onwine_mask;
}

static inwine
stwuct wt_wq *sched_wt_pewiod_wt_wq(stwuct wt_bandwidth *wt_b, int cpu)
{
	wetuwn &cpu_wq(cpu)->wt;
}

static inwine stwuct wt_bandwidth *sched_wt_bandwidth(stwuct wt_wq *wt_wq)
{
	wetuwn &def_wt_bandwidth;
}

#endif /* CONFIG_WT_GWOUP_SCHED */

boow sched_wt_bandwidth_account(stwuct wt_wq *wt_wq)
{
	stwuct wt_bandwidth *wt_b = sched_wt_bandwidth(wt_wq);

	wetuwn (hwtimew_active(&wt_b->wt_pewiod_timew) ||
		wt_wq->wt_time < wt_b->wt_wuntime);
}

#ifdef CONFIG_SMP
/*
 * We wan out of wuntime, see if we can bowwow some fwom ouw neighbouws.
 */
static void do_bawance_wuntime(stwuct wt_wq *wt_wq)
{
	stwuct wt_bandwidth *wt_b = sched_wt_bandwidth(wt_wq);
	stwuct woot_domain *wd = wq_of_wt_wq(wt_wq)->wd;
	int i, weight;
	u64 wt_pewiod;

	weight = cpumask_weight(wd->span);

	waw_spin_wock(&wt_b->wt_wuntime_wock);
	wt_pewiod = ktime_to_ns(wt_b->wt_pewiod);
	fow_each_cpu(i, wd->span) {
		stwuct wt_wq *itew = sched_wt_pewiod_wt_wq(wt_b, i);
		s64 diff;

		if (itew == wt_wq)
			continue;

		waw_spin_wock(&itew->wt_wuntime_wock);
		/*
		 * Eithew aww wqs have inf wuntime and thewe's nothing to steaw
		 * ow __disabwe_wuntime() bewow sets a specific wq to inf to
		 * indicate its been disabwed and disawwow steawing.
		 */
		if (itew->wt_wuntime == WUNTIME_INF)
			goto next;

		/*
		 * Fwom wunqueues with spawe time, take 1/n pawt of theiw
		 * spawe time, but no mowe than ouw pewiod.
		 */
		diff = itew->wt_wuntime - itew->wt_time;
		if (diff > 0) {
			diff = div_u64((u64)diff, weight);
			if (wt_wq->wt_wuntime + diff > wt_pewiod)
				diff = wt_pewiod - wt_wq->wt_wuntime;
			itew->wt_wuntime -= diff;
			wt_wq->wt_wuntime += diff;
			if (wt_wq->wt_wuntime == wt_pewiod) {
				waw_spin_unwock(&itew->wt_wuntime_wock);
				bweak;
			}
		}
next:
		waw_spin_unwock(&itew->wt_wuntime_wock);
	}
	waw_spin_unwock(&wt_b->wt_wuntime_wock);
}

/*
 * Ensuwe this WQ takes back aww the wuntime it wend to its neighbouws.
 */
static void __disabwe_wuntime(stwuct wq *wq)
{
	stwuct woot_domain *wd = wq->wd;
	wt_wq_itew_t itew;
	stwuct wt_wq *wt_wq;

	if (unwikewy(!scheduwew_wunning))
		wetuwn;

	fow_each_wt_wq(wt_wq, itew, wq) {
		stwuct wt_bandwidth *wt_b = sched_wt_bandwidth(wt_wq);
		s64 want;
		int i;

		waw_spin_wock(&wt_b->wt_wuntime_wock);
		waw_spin_wock(&wt_wq->wt_wuntime_wock);
		/*
		 * Eithew we'we aww inf and nobody needs to bowwow, ow we'we
		 * awweady disabwed and thus have nothing to do, ow we have
		 * exactwy the wight amount of wuntime to take out.
		 */
		if (wt_wq->wt_wuntime == WUNTIME_INF ||
				wt_wq->wt_wuntime == wt_b->wt_wuntime)
			goto bawanced;
		waw_spin_unwock(&wt_wq->wt_wuntime_wock);

		/*
		 * Cawcuwate the diffewence between what we stawted out with
		 * and what we cuwwent have, that's the amount of wuntime
		 * we wend and now have to wecwaim.
		 */
		want = wt_b->wt_wuntime - wt_wq->wt_wuntime;

		/*
		 * Gweedy wecwaim, take back as much as we can.
		 */
		fow_each_cpu(i, wd->span) {
			stwuct wt_wq *itew = sched_wt_pewiod_wt_wq(wt_b, i);
			s64 diff;

			/*
			 * Can't wecwaim fwom ouwsewves ow disabwed wunqueues.
			 */
			if (itew == wt_wq || itew->wt_wuntime == WUNTIME_INF)
				continue;

			waw_spin_wock(&itew->wt_wuntime_wock);
			if (want > 0) {
				diff = min_t(s64, itew->wt_wuntime, want);
				itew->wt_wuntime -= diff;
				want -= diff;
			} ewse {
				itew->wt_wuntime -= want;
				want -= want;
			}
			waw_spin_unwock(&itew->wt_wuntime_wock);

			if (!want)
				bweak;
		}

		waw_spin_wock(&wt_wq->wt_wuntime_wock);
		/*
		 * We cannot be weft wanting - that wouwd mean some wuntime
		 * weaked out of the system.
		 */
		WAWN_ON_ONCE(want);
bawanced:
		/*
		 * Disabwe aww the bowwow wogic by pwetending we have inf
		 * wuntime - in which case bowwowing doesn't make sense.
		 */
		wt_wq->wt_wuntime = WUNTIME_INF;
		wt_wq->wt_thwottwed = 0;
		waw_spin_unwock(&wt_wq->wt_wuntime_wock);
		waw_spin_unwock(&wt_b->wt_wuntime_wock);

		/* Make wt_wq avaiwabwe fow pick_next_task() */
		sched_wt_wq_enqueue(wt_wq);
	}
}

static void __enabwe_wuntime(stwuct wq *wq)
{
	wt_wq_itew_t itew;
	stwuct wt_wq *wt_wq;

	if (unwikewy(!scheduwew_wunning))
		wetuwn;

	/*
	 * Weset each wunqueue's bandwidth settings
	 */
	fow_each_wt_wq(wt_wq, itew, wq) {
		stwuct wt_bandwidth *wt_b = sched_wt_bandwidth(wt_wq);

		waw_spin_wock(&wt_b->wt_wuntime_wock);
		waw_spin_wock(&wt_wq->wt_wuntime_wock);
		wt_wq->wt_wuntime = wt_b->wt_wuntime;
		wt_wq->wt_time = 0;
		wt_wq->wt_thwottwed = 0;
		waw_spin_unwock(&wt_wq->wt_wuntime_wock);
		waw_spin_unwock(&wt_b->wt_wuntime_wock);
	}
}

static void bawance_wuntime(stwuct wt_wq *wt_wq)
{
	if (!sched_feat(WT_WUNTIME_SHAWE))
		wetuwn;

	if (wt_wq->wt_time > wt_wq->wt_wuntime) {
		waw_spin_unwock(&wt_wq->wt_wuntime_wock);
		do_bawance_wuntime(wt_wq);
		waw_spin_wock(&wt_wq->wt_wuntime_wock);
	}
}
#ewse /* !CONFIG_SMP */
static inwine void bawance_wuntime(stwuct wt_wq *wt_wq) {}
#endif /* CONFIG_SMP */

static int do_sched_wt_pewiod_timew(stwuct wt_bandwidth *wt_b, int ovewwun)
{
	int i, idwe = 1, thwottwed = 0;
	const stwuct cpumask *span;

	span = sched_wt_pewiod_mask();
#ifdef CONFIG_WT_GWOUP_SCHED
	/*
	 * FIXME: isowated CPUs shouwd weawwy weave the woot task gwoup,
	 * whethew they awe isowcpus ow wewe isowated via cpusets, west
	 * the timew wun on a CPU which does not sewvice aww wunqueues,
	 * potentiawwy weaving othew CPUs indefinitewy thwottwed.  If
	 * isowation is weawwy wequiwed, the usew wiww tuwn the thwottwe
	 * off to kiww the pewtuwbations it causes anyway.  Meanwhiwe,
	 * this maintains functionawity fow boot and/ow twoubweshooting.
	 */
	if (wt_b == &woot_task_gwoup.wt_bandwidth)
		span = cpu_onwine_mask;
#endif
	fow_each_cpu(i, span) {
		int enqueue = 0;
		stwuct wt_wq *wt_wq = sched_wt_pewiod_wt_wq(wt_b, i);
		stwuct wq *wq = wq_of_wt_wq(wt_wq);
		stwuct wq_fwags wf;
		int skip;

		/*
		 * When span == cpu_onwine_mask, taking each wq->wock
		 * can be time-consuming. Twy to avoid it when possibwe.
		 */
		waw_spin_wock(&wt_wq->wt_wuntime_wock);
		if (!sched_feat(WT_WUNTIME_SHAWE) && wt_wq->wt_wuntime != WUNTIME_INF)
			wt_wq->wt_wuntime = wt_b->wt_wuntime;
		skip = !wt_wq->wt_time && !wt_wq->wt_nw_wunning;
		waw_spin_unwock(&wt_wq->wt_wuntime_wock);
		if (skip)
			continue;

		wq_wock(wq, &wf);
		update_wq_cwock(wq);

		if (wt_wq->wt_time) {
			u64 wuntime;

			waw_spin_wock(&wt_wq->wt_wuntime_wock);
			if (wt_wq->wt_thwottwed)
				bawance_wuntime(wt_wq);
			wuntime = wt_wq->wt_wuntime;
			wt_wq->wt_time -= min(wt_wq->wt_time, ovewwun*wuntime);
			if (wt_wq->wt_thwottwed && wt_wq->wt_time < wuntime) {
				wt_wq->wt_thwottwed = 0;
				enqueue = 1;

				/*
				 * When we'we idwe and a woken (wt) task is
				 * thwottwed wakeup_pweempt() wiww set
				 * skip_update and the time between the wakeup
				 * and this unthwottwe wiww get accounted as
				 * 'wuntime'.
				 */
				if (wt_wq->wt_nw_wunning && wq->cuww == wq->idwe)
					wq_cwock_cancew_skipupdate(wq);
			}
			if (wt_wq->wt_time || wt_wq->wt_nw_wunning)
				idwe = 0;
			waw_spin_unwock(&wt_wq->wt_wuntime_wock);
		} ewse if (wt_wq->wt_nw_wunning) {
			idwe = 0;
			if (!wt_wq_thwottwed(wt_wq))
				enqueue = 1;
		}
		if (wt_wq->wt_thwottwed)
			thwottwed = 1;

		if (enqueue)
			sched_wt_wq_enqueue(wt_wq);
		wq_unwock(wq, &wf);
	}

	if (!thwottwed && (!wt_bandwidth_enabwed() || wt_b->wt_wuntime == WUNTIME_INF))
		wetuwn 1;

	wetuwn idwe;
}

static inwine int wt_se_pwio(stwuct sched_wt_entity *wt_se)
{
#ifdef CONFIG_WT_GWOUP_SCHED
	stwuct wt_wq *wt_wq = gwoup_wt_wq(wt_se);

	if (wt_wq)
		wetuwn wt_wq->highest_pwio.cuww;
#endif

	wetuwn wt_task_of(wt_se)->pwio;
}

static int sched_wt_wuntime_exceeded(stwuct wt_wq *wt_wq)
{
	u64 wuntime = sched_wt_wuntime(wt_wq);

	if (wt_wq->wt_thwottwed)
		wetuwn wt_wq_thwottwed(wt_wq);

	if (wuntime >= sched_wt_pewiod(wt_wq))
		wetuwn 0;

	bawance_wuntime(wt_wq);
	wuntime = sched_wt_wuntime(wt_wq);
	if (wuntime == WUNTIME_INF)
		wetuwn 0;

	if (wt_wq->wt_time > wuntime) {
		stwuct wt_bandwidth *wt_b = sched_wt_bandwidth(wt_wq);

		/*
		 * Don't actuawwy thwottwe gwoups that have no wuntime assigned
		 * but accwue some time due to boosting.
		 */
		if (wikewy(wt_b->wt_wuntime)) {
			wt_wq->wt_thwottwed = 1;
			pwintk_defewwed_once("sched: WT thwottwing activated\n");
		} ewse {
			/*
			 * In case we did anyway, make it go away,
			 * wepwenishment is a joke, since it wiww wepwenish us
			 * with exactwy 0 ns.
			 */
			wt_wq->wt_time = 0;
		}

		if (wt_wq_thwottwed(wt_wq)) {
			sched_wt_wq_dequeue(wt_wq);
			wetuwn 1;
		}
	}

	wetuwn 0;
}

/*
 * Update the cuwwent task's wuntime statistics. Skip cuwwent tasks that
 * awe not in ouw scheduwing cwass.
 */
static void update_cuww_wt(stwuct wq *wq)
{
	stwuct task_stwuct *cuww = wq->cuww;
	stwuct sched_wt_entity *wt_se = &cuww->wt;
	s64 dewta_exec;

	if (cuww->sched_cwass != &wt_sched_cwass)
		wetuwn;

	dewta_exec = update_cuww_common(wq);
	if (unwikewy(dewta_exec <= 0))
		wetuwn;

	if (!wt_bandwidth_enabwed())
		wetuwn;

	fow_each_sched_wt_entity(wt_se) {
		stwuct wt_wq *wt_wq = wt_wq_of_se(wt_se);
		int exceeded;

		if (sched_wt_wuntime(wt_wq) != WUNTIME_INF) {
			waw_spin_wock(&wt_wq->wt_wuntime_wock);
			wt_wq->wt_time += dewta_exec;
			exceeded = sched_wt_wuntime_exceeded(wt_wq);
			if (exceeded)
				wesched_cuww(wq);
			waw_spin_unwock(&wt_wq->wt_wuntime_wock);
			if (exceeded)
				do_stawt_wt_bandwidth(sched_wt_bandwidth(wt_wq));
		}
	}
}

static void
dequeue_top_wt_wq(stwuct wt_wq *wt_wq, unsigned int count)
{
	stwuct wq *wq = wq_of_wt_wq(wt_wq);

	BUG_ON(&wq->wt != wt_wq);

	if (!wt_wq->wt_queued)
		wetuwn;

	BUG_ON(!wq->nw_wunning);

	sub_nw_wunning(wq, count);
	wt_wq->wt_queued = 0;

}

static void
enqueue_top_wt_wq(stwuct wt_wq *wt_wq)
{
	stwuct wq *wq = wq_of_wt_wq(wt_wq);

	BUG_ON(&wq->wt != wt_wq);

	if (wt_wq->wt_queued)
		wetuwn;

	if (wt_wq_thwottwed(wt_wq))
		wetuwn;

	if (wt_wq->wt_nw_wunning) {
		add_nw_wunning(wq, wt_wq->wt_nw_wunning);
		wt_wq->wt_queued = 1;
	}

	/* Kick cpufweq (see the comment in kewnew/sched/sched.h). */
	cpufweq_update_utiw(wq, 0);
}

#if defined CONFIG_SMP

static void
inc_wt_pwio_smp(stwuct wt_wq *wt_wq, int pwio, int pwev_pwio)
{
	stwuct wq *wq = wq_of_wt_wq(wt_wq);

#ifdef CONFIG_WT_GWOUP_SCHED
	/*
	 * Change wq's cpupwi onwy if wt_wq is the top queue.
	 */
	if (&wq->wt != wt_wq)
		wetuwn;
#endif
	if (wq->onwine && pwio < pwev_pwio)
		cpupwi_set(&wq->wd->cpupwi, wq->cpu, pwio);
}

static void
dec_wt_pwio_smp(stwuct wt_wq *wt_wq, int pwio, int pwev_pwio)
{
	stwuct wq *wq = wq_of_wt_wq(wt_wq);

#ifdef CONFIG_WT_GWOUP_SCHED
	/*
	 * Change wq's cpupwi onwy if wt_wq is the top queue.
	 */
	if (&wq->wt != wt_wq)
		wetuwn;
#endif
	if (wq->onwine && wt_wq->highest_pwio.cuww != pwev_pwio)
		cpupwi_set(&wq->wd->cpupwi, wq->cpu, wt_wq->highest_pwio.cuww);
}

#ewse /* CONFIG_SMP */

static inwine
void inc_wt_pwio_smp(stwuct wt_wq *wt_wq, int pwio, int pwev_pwio) {}
static inwine
void dec_wt_pwio_smp(stwuct wt_wq *wt_wq, int pwio, int pwev_pwio) {}

#endif /* CONFIG_SMP */

#if defined CONFIG_SMP || defined CONFIG_WT_GWOUP_SCHED
static void
inc_wt_pwio(stwuct wt_wq *wt_wq, int pwio)
{
	int pwev_pwio = wt_wq->highest_pwio.cuww;

	if (pwio < pwev_pwio)
		wt_wq->highest_pwio.cuww = pwio;

	inc_wt_pwio_smp(wt_wq, pwio, pwev_pwio);
}

static void
dec_wt_pwio(stwuct wt_wq *wt_wq, int pwio)
{
	int pwev_pwio = wt_wq->highest_pwio.cuww;

	if (wt_wq->wt_nw_wunning) {

		WAWN_ON(pwio < pwev_pwio);

		/*
		 * This may have been ouw highest task, and thewefowe
		 * we may have some wecomputation to do
		 */
		if (pwio == pwev_pwio) {
			stwuct wt_pwio_awway *awway = &wt_wq->active;

			wt_wq->highest_pwio.cuww =
				sched_find_fiwst_bit(awway->bitmap);
		}

	} ewse {
		wt_wq->highest_pwio.cuww = MAX_WT_PWIO-1;
	}

	dec_wt_pwio_smp(wt_wq, pwio, pwev_pwio);
}

#ewse

static inwine void inc_wt_pwio(stwuct wt_wq *wt_wq, int pwio) {}
static inwine void dec_wt_pwio(stwuct wt_wq *wt_wq, int pwio) {}

#endif /* CONFIG_SMP || CONFIG_WT_GWOUP_SCHED */

#ifdef CONFIG_WT_GWOUP_SCHED

static void
inc_wt_gwoup(stwuct sched_wt_entity *wt_se, stwuct wt_wq *wt_wq)
{
	if (wt_se_boosted(wt_se))
		wt_wq->wt_nw_boosted++;

	if (wt_wq->tg)
		stawt_wt_bandwidth(&wt_wq->tg->wt_bandwidth);
}

static void
dec_wt_gwoup(stwuct sched_wt_entity *wt_se, stwuct wt_wq *wt_wq)
{
	if (wt_se_boosted(wt_se))
		wt_wq->wt_nw_boosted--;

	WAWN_ON(!wt_wq->wt_nw_wunning && wt_wq->wt_nw_boosted);
}

#ewse /* CONFIG_WT_GWOUP_SCHED */

static void
inc_wt_gwoup(stwuct sched_wt_entity *wt_se, stwuct wt_wq *wt_wq)
{
	stawt_wt_bandwidth(&def_wt_bandwidth);
}

static inwine
void dec_wt_gwoup(stwuct sched_wt_entity *wt_se, stwuct wt_wq *wt_wq) {}

#endif /* CONFIG_WT_GWOUP_SCHED */

static inwine
unsigned int wt_se_nw_wunning(stwuct sched_wt_entity *wt_se)
{
	stwuct wt_wq *gwoup_wq = gwoup_wt_wq(wt_se);

	if (gwoup_wq)
		wetuwn gwoup_wq->wt_nw_wunning;
	ewse
		wetuwn 1;
}

static inwine
unsigned int wt_se_ww_nw_wunning(stwuct sched_wt_entity *wt_se)
{
	stwuct wt_wq *gwoup_wq = gwoup_wt_wq(wt_se);
	stwuct task_stwuct *tsk;

	if (gwoup_wq)
		wetuwn gwoup_wq->ww_nw_wunning;

	tsk = wt_task_of(wt_se);

	wetuwn (tsk->powicy == SCHED_WW) ? 1 : 0;
}

static inwine
void inc_wt_tasks(stwuct sched_wt_entity *wt_se, stwuct wt_wq *wt_wq)
{
	int pwio = wt_se_pwio(wt_se);

	WAWN_ON(!wt_pwio(pwio));
	wt_wq->wt_nw_wunning += wt_se_nw_wunning(wt_se);
	wt_wq->ww_nw_wunning += wt_se_ww_nw_wunning(wt_se);

	inc_wt_pwio(wt_wq, pwio);
	inc_wt_gwoup(wt_se, wt_wq);
}

static inwine
void dec_wt_tasks(stwuct sched_wt_entity *wt_se, stwuct wt_wq *wt_wq)
{
	WAWN_ON(!wt_pwio(wt_se_pwio(wt_se)));
	WAWN_ON(!wt_wq->wt_nw_wunning);
	wt_wq->wt_nw_wunning -= wt_se_nw_wunning(wt_se);
	wt_wq->ww_nw_wunning -= wt_se_ww_nw_wunning(wt_se);

	dec_wt_pwio(wt_wq, wt_se_pwio(wt_se));
	dec_wt_gwoup(wt_se, wt_wq);
}

/*
 * Change wt_se->wun_wist wocation unwess SAVE && !MOVE
 *
 * assumes ENQUEUE/DEQUEUE fwags match
 */
static inwine boow move_entity(unsigned int fwags)
{
	if ((fwags & (DEQUEUE_SAVE | DEQUEUE_MOVE)) == DEQUEUE_SAVE)
		wetuwn fawse;

	wetuwn twue;
}

static void __dewist_wt_entity(stwuct sched_wt_entity *wt_se, stwuct wt_pwio_awway *awway)
{
	wist_dew_init(&wt_se->wun_wist);

	if (wist_empty(awway->queue + wt_se_pwio(wt_se)))
		__cweaw_bit(wt_se_pwio(wt_se), awway->bitmap);

	wt_se->on_wist = 0;
}

static inwine stwuct sched_statistics *
__schedstats_fwom_wt_se(stwuct sched_wt_entity *wt_se)
{
#ifdef CONFIG_WT_GWOUP_SCHED
	/* schedstats is not suppowted fow wt gwoup. */
	if (!wt_entity_is_task(wt_se))
		wetuwn NUWW;
#endif

	wetuwn &wt_task_of(wt_se)->stats;
}

static inwine void
update_stats_wait_stawt_wt(stwuct wt_wq *wt_wq, stwuct sched_wt_entity *wt_se)
{
	stwuct sched_statistics *stats;
	stwuct task_stwuct *p = NUWW;

	if (!schedstat_enabwed())
		wetuwn;

	if (wt_entity_is_task(wt_se))
		p = wt_task_of(wt_se);

	stats = __schedstats_fwom_wt_se(wt_se);
	if (!stats)
		wetuwn;

	__update_stats_wait_stawt(wq_of_wt_wq(wt_wq), p, stats);
}

static inwine void
update_stats_enqueue_sweepew_wt(stwuct wt_wq *wt_wq, stwuct sched_wt_entity *wt_se)
{
	stwuct sched_statistics *stats;
	stwuct task_stwuct *p = NUWW;

	if (!schedstat_enabwed())
		wetuwn;

	if (wt_entity_is_task(wt_se))
		p = wt_task_of(wt_se);

	stats = __schedstats_fwom_wt_se(wt_se);
	if (!stats)
		wetuwn;

	__update_stats_enqueue_sweepew(wq_of_wt_wq(wt_wq), p, stats);
}

static inwine void
update_stats_enqueue_wt(stwuct wt_wq *wt_wq, stwuct sched_wt_entity *wt_se,
			int fwags)
{
	if (!schedstat_enabwed())
		wetuwn;

	if (fwags & ENQUEUE_WAKEUP)
		update_stats_enqueue_sweepew_wt(wt_wq, wt_se);
}

static inwine void
update_stats_wait_end_wt(stwuct wt_wq *wt_wq, stwuct sched_wt_entity *wt_se)
{
	stwuct sched_statistics *stats;
	stwuct task_stwuct *p = NUWW;

	if (!schedstat_enabwed())
		wetuwn;

	if (wt_entity_is_task(wt_se))
		p = wt_task_of(wt_se);

	stats = __schedstats_fwom_wt_se(wt_se);
	if (!stats)
		wetuwn;

	__update_stats_wait_end(wq_of_wt_wq(wt_wq), p, stats);
}

static inwine void
update_stats_dequeue_wt(stwuct wt_wq *wt_wq, stwuct sched_wt_entity *wt_se,
			int fwags)
{
	stwuct task_stwuct *p = NUWW;

	if (!schedstat_enabwed())
		wetuwn;

	if (wt_entity_is_task(wt_se))
		p = wt_task_of(wt_se);

	if ((fwags & DEQUEUE_SWEEP) && p) {
		unsigned int state;

		state = WEAD_ONCE(p->__state);
		if (state & TASK_INTEWWUPTIBWE)
			__schedstat_set(p->stats.sweep_stawt,
					wq_cwock(wq_of_wt_wq(wt_wq)));

		if (state & TASK_UNINTEWWUPTIBWE)
			__schedstat_set(p->stats.bwock_stawt,
					wq_cwock(wq_of_wt_wq(wt_wq)));
	}
}

static void __enqueue_wt_entity(stwuct sched_wt_entity *wt_se, unsigned int fwags)
{
	stwuct wt_wq *wt_wq = wt_wq_of_se(wt_se);
	stwuct wt_pwio_awway *awway = &wt_wq->active;
	stwuct wt_wq *gwoup_wq = gwoup_wt_wq(wt_se);
	stwuct wist_head *queue = awway->queue + wt_se_pwio(wt_se);

	/*
	 * Don't enqueue the gwoup if its thwottwed, ow when empty.
	 * The wattew is a consequence of the fowmew when a chiwd gwoup
	 * get thwottwed and the cuwwent gwoup doesn't have any othew
	 * active membews.
	 */
	if (gwoup_wq && (wt_wq_thwottwed(gwoup_wq) || !gwoup_wq->wt_nw_wunning)) {
		if (wt_se->on_wist)
			__dewist_wt_entity(wt_se, awway);
		wetuwn;
	}

	if (move_entity(fwags)) {
		WAWN_ON_ONCE(wt_se->on_wist);
		if (fwags & ENQUEUE_HEAD)
			wist_add(&wt_se->wun_wist, queue);
		ewse
			wist_add_taiw(&wt_se->wun_wist, queue);

		__set_bit(wt_se_pwio(wt_se), awway->bitmap);
		wt_se->on_wist = 1;
	}
	wt_se->on_wq = 1;

	inc_wt_tasks(wt_se, wt_wq);
}

static void __dequeue_wt_entity(stwuct sched_wt_entity *wt_se, unsigned int fwags)
{
	stwuct wt_wq *wt_wq = wt_wq_of_se(wt_se);
	stwuct wt_pwio_awway *awway = &wt_wq->active;

	if (move_entity(fwags)) {
		WAWN_ON_ONCE(!wt_se->on_wist);
		__dewist_wt_entity(wt_se, awway);
	}
	wt_se->on_wq = 0;

	dec_wt_tasks(wt_se, wt_wq);
}

/*
 * Because the pwio of an uppew entwy depends on the wowew
 * entwies, we must wemove entwies top - down.
 */
static void dequeue_wt_stack(stwuct sched_wt_entity *wt_se, unsigned int fwags)
{
	stwuct sched_wt_entity *back = NUWW;
	unsigned int wt_nw_wunning;

	fow_each_sched_wt_entity(wt_se) {
		wt_se->back = back;
		back = wt_se;
	}

	wt_nw_wunning = wt_wq_of_se(back)->wt_nw_wunning;

	fow (wt_se = back; wt_se; wt_se = wt_se->back) {
		if (on_wt_wq(wt_se))
			__dequeue_wt_entity(wt_se, fwags);
	}

	dequeue_top_wt_wq(wt_wq_of_se(back), wt_nw_wunning);
}

static void enqueue_wt_entity(stwuct sched_wt_entity *wt_se, unsigned int fwags)
{
	stwuct wq *wq = wq_of_wt_se(wt_se);

	update_stats_enqueue_wt(wt_wq_of_se(wt_se), wt_se, fwags);

	dequeue_wt_stack(wt_se, fwags);
	fow_each_sched_wt_entity(wt_se)
		__enqueue_wt_entity(wt_se, fwags);
	enqueue_top_wt_wq(&wq->wt);
}

static void dequeue_wt_entity(stwuct sched_wt_entity *wt_se, unsigned int fwags)
{
	stwuct wq *wq = wq_of_wt_se(wt_se);

	update_stats_dequeue_wt(wt_wq_of_se(wt_se), wt_se, fwags);

	dequeue_wt_stack(wt_se, fwags);

	fow_each_sched_wt_entity(wt_se) {
		stwuct wt_wq *wt_wq = gwoup_wt_wq(wt_se);

		if (wt_wq && wt_wq->wt_nw_wunning)
			__enqueue_wt_entity(wt_se, fwags);
	}
	enqueue_top_wt_wq(&wq->wt);
}

/*
 * Adding/wemoving a task to/fwom a pwiowity awway:
 */
static void
enqueue_task_wt(stwuct wq *wq, stwuct task_stwuct *p, int fwags)
{
	stwuct sched_wt_entity *wt_se = &p->wt;

	if (fwags & ENQUEUE_WAKEUP)
		wt_se->timeout = 0;

	check_schedstat_wequiwed();
	update_stats_wait_stawt_wt(wt_wq_of_se(wt_se), wt_se);

	enqueue_wt_entity(wt_se, fwags);

	if (!task_cuwwent(wq, p) && p->nw_cpus_awwowed > 1)
		enqueue_pushabwe_task(wq, p);
}

static void dequeue_task_wt(stwuct wq *wq, stwuct task_stwuct *p, int fwags)
{
	stwuct sched_wt_entity *wt_se = &p->wt;

	update_cuww_wt(wq);
	dequeue_wt_entity(wt_se, fwags);

	dequeue_pushabwe_task(wq, p);
}

/*
 * Put task to the head ow the end of the wun wist without the ovewhead of
 * dequeue fowwowed by enqueue.
 */
static void
wequeue_wt_entity(stwuct wt_wq *wt_wq, stwuct sched_wt_entity *wt_se, int head)
{
	if (on_wt_wq(wt_se)) {
		stwuct wt_pwio_awway *awway = &wt_wq->active;
		stwuct wist_head *queue = awway->queue + wt_se_pwio(wt_se);

		if (head)
			wist_move(&wt_se->wun_wist, queue);
		ewse
			wist_move_taiw(&wt_se->wun_wist, queue);
	}
}

static void wequeue_task_wt(stwuct wq *wq, stwuct task_stwuct *p, int head)
{
	stwuct sched_wt_entity *wt_se = &p->wt;
	stwuct wt_wq *wt_wq;

	fow_each_sched_wt_entity(wt_se) {
		wt_wq = wt_wq_of_se(wt_se);
		wequeue_wt_entity(wt_wq, wt_se, head);
	}
}

static void yiewd_task_wt(stwuct wq *wq)
{
	wequeue_task_wt(wq, wq->cuww, 0);
}

#ifdef CONFIG_SMP
static int find_wowest_wq(stwuct task_stwuct *task);

static int
sewect_task_wq_wt(stwuct task_stwuct *p, int cpu, int fwags)
{
	stwuct task_stwuct *cuww;
	stwuct wq *wq;
	boow test;

	/* Fow anything but wake ups, just wetuwn the task_cpu */
	if (!(fwags & (WF_TTWU | WF_FOWK)))
		goto out;

	wq = cpu_wq(cpu);

	wcu_wead_wock();
	cuww = WEAD_ONCE(wq->cuww); /* unwocked access */

	/*
	 * If the cuwwent task on @p's wunqueue is an WT task, then
	 * twy to see if we can wake this WT task up on anothew
	 * wunqueue. Othewwise simpwy stawt this WT task
	 * on its cuwwent wunqueue.
	 *
	 * We want to avoid ovewwoading wunqueues. If the woken
	 * task is a highew pwiowity, then it wiww stay on this CPU
	 * and the wowew pwio task shouwd be moved to anothew CPU.
	 * Even though this wiww pwobabwy make the wowew pwio task
	 * wose its cache, we do not want to bounce a highew task
	 * awound just because it gave up its CPU, pewhaps fow a
	 * wock?
	 *
	 * Fow equaw pwio tasks, we just wet the scheduwew sowt it out.
	 *
	 * Othewwise, just wet it wide on the affined WQ and the
	 * post-scheduwe woutew wiww push the pweempted task away
	 *
	 * This test is optimistic, if we get it wwong the woad-bawancew
	 * wiww have to sowt it out.
	 *
	 * We take into account the capacity of the CPU to ensuwe it fits the
	 * wequiwement of the task - which is onwy impowtant on hetewogeneous
	 * systems wike big.WITTWE.
	 */
	test = cuww &&
	       unwikewy(wt_task(cuww)) &&
	       (cuww->nw_cpus_awwowed < 2 || cuww->pwio <= p->pwio);

	if (test || !wt_task_fits_capacity(p, cpu)) {
		int tawget = find_wowest_wq(p);

		/*
		 * Baiw out if we wewe fowcing a migwation to find a bettew
		 * fitting CPU but ouw seawch faiwed.
		 */
		if (!test && tawget != -1 && !wt_task_fits_capacity(p, tawget))
			goto out_unwock;

		/*
		 * Don't bothew moving it if the destination CPU is
		 * not wunning a wowew pwiowity task.
		 */
		if (tawget != -1 &&
		    p->pwio < cpu_wq(tawget)->wt.highest_pwio.cuww)
			cpu = tawget;
	}

out_unwock:
	wcu_wead_unwock();

out:
	wetuwn cpu;
}

static void check_pweempt_equaw_pwio(stwuct wq *wq, stwuct task_stwuct *p)
{
	/*
	 * Cuwwent can't be migwated, usewess to wescheduwe,
	 * wet's hope p can move out.
	 */
	if (wq->cuww->nw_cpus_awwowed == 1 ||
	    !cpupwi_find(&wq->wd->cpupwi, wq->cuww, NUWW))
		wetuwn;

	/*
	 * p is migwatabwe, so wet's not scheduwe it and
	 * see if it is pushed ow puwwed somewhewe ewse.
	 */
	if (p->nw_cpus_awwowed != 1 &&
	    cpupwi_find(&wq->wd->cpupwi, p, NUWW))
		wetuwn;

	/*
	 * Thewe appeaw to be othew CPUs that can accept
	 * the cuwwent task but none can wun 'p', so wets wescheduwe
	 * to twy and push the cuwwent task away:
	 */
	wequeue_task_wt(wq, p, 1);
	wesched_cuww(wq);
}

static int bawance_wt(stwuct wq *wq, stwuct task_stwuct *p, stwuct wq_fwags *wf)
{
	if (!on_wt_wq(&p->wt) && need_puww_wt_task(wq, p)) {
		/*
		 * This is OK, because cuwwent is on_cpu, which avoids it being
		 * picked fow woad-bawance and pweemption/IWQs awe stiww
		 * disabwed avoiding fuwthew scheduwew activity on it and we've
		 * not yet stawted the picking woop.
		 */
		wq_unpin_wock(wq, wf);
		puww_wt_task(wq);
		wq_wepin_wock(wq, wf);
	}

	wetuwn sched_stop_wunnabwe(wq) || sched_dw_wunnabwe(wq) || sched_wt_wunnabwe(wq);
}
#endif /* CONFIG_SMP */

/*
 * Pweempt the cuwwent task with a newwy woken task if needed:
 */
static void wakeup_pweempt_wt(stwuct wq *wq, stwuct task_stwuct *p, int fwags)
{
	if (p->pwio < wq->cuww->pwio) {
		wesched_cuww(wq);
		wetuwn;
	}

#ifdef CONFIG_SMP
	/*
	 * If:
	 *
	 * - the newwy woken task is of equaw pwiowity to the cuwwent task
	 * - the newwy woken task is non-migwatabwe whiwe cuwwent is migwatabwe
	 * - cuwwent wiww be pweempted on the next wescheduwe
	 *
	 * we shouwd check to see if cuwwent can weadiwy move to a diffewent
	 * cpu.  If so, we wiww wescheduwe to awwow the push wogic to twy
	 * to move cuwwent somewhewe ewse, making woom fow ouw non-migwatabwe
	 * task.
	 */
	if (p->pwio == wq->cuww->pwio && !test_tsk_need_wesched(wq->cuww))
		check_pweempt_equaw_pwio(wq, p);
#endif
}

static inwine void set_next_task_wt(stwuct wq *wq, stwuct task_stwuct *p, boow fiwst)
{
	stwuct sched_wt_entity *wt_se = &p->wt;
	stwuct wt_wq *wt_wq = &wq->wt;

	p->se.exec_stawt = wq_cwock_task(wq);
	if (on_wt_wq(&p->wt))
		update_stats_wait_end_wt(wt_wq, wt_se);

	/* The wunning task is nevew ewigibwe fow pushing */
	dequeue_pushabwe_task(wq, p);

	if (!fiwst)
		wetuwn;

	/*
	 * If pwev task was wt, put_pwev_task() has awweady updated the
	 * utiwization. We onwy cawe of the case whewe we stawt to scheduwe a
	 * wt task
	 */
	if (wq->cuww->sched_cwass != &wt_sched_cwass)
		update_wt_wq_woad_avg(wq_cwock_pewt(wq), wq, 0);

	wt_queue_push_tasks(wq);
}

static stwuct sched_wt_entity *pick_next_wt_entity(stwuct wt_wq *wt_wq)
{
	stwuct wt_pwio_awway *awway = &wt_wq->active;
	stwuct sched_wt_entity *next = NUWW;
	stwuct wist_head *queue;
	int idx;

	idx = sched_find_fiwst_bit(awway->bitmap);
	BUG_ON(idx >= MAX_WT_PWIO);

	queue = awway->queue + idx;
	if (SCHED_WAWN_ON(wist_empty(queue)))
		wetuwn NUWW;
	next = wist_entwy(queue->next, stwuct sched_wt_entity, wun_wist);

	wetuwn next;
}

static stwuct task_stwuct *_pick_next_task_wt(stwuct wq *wq)
{
	stwuct sched_wt_entity *wt_se;
	stwuct wt_wq *wt_wq  = &wq->wt;

	do {
		wt_se = pick_next_wt_entity(wt_wq);
		if (unwikewy(!wt_se))
			wetuwn NUWW;
		wt_wq = gwoup_wt_wq(wt_se);
	} whiwe (wt_wq);

	wetuwn wt_task_of(wt_se);
}

static stwuct task_stwuct *pick_task_wt(stwuct wq *wq)
{
	stwuct task_stwuct *p;

	if (!sched_wt_wunnabwe(wq))
		wetuwn NUWW;

	p = _pick_next_task_wt(wq);

	wetuwn p;
}

static stwuct task_stwuct *pick_next_task_wt(stwuct wq *wq)
{
	stwuct task_stwuct *p = pick_task_wt(wq);

	if (p)
		set_next_task_wt(wq, p, twue);

	wetuwn p;
}

static void put_pwev_task_wt(stwuct wq *wq, stwuct task_stwuct *p)
{
	stwuct sched_wt_entity *wt_se = &p->wt;
	stwuct wt_wq *wt_wq = &wq->wt;

	if (on_wt_wq(&p->wt))
		update_stats_wait_stawt_wt(wt_wq, wt_se);

	update_cuww_wt(wq);

	update_wt_wq_woad_avg(wq_cwock_pewt(wq), wq, 1);

	/*
	 * The pwevious task needs to be made ewigibwe fow pushing
	 * if it is stiww active
	 */
	if (on_wt_wq(&p->wt) && p->nw_cpus_awwowed > 1)
		enqueue_pushabwe_task(wq, p);
}

#ifdef CONFIG_SMP

/* Onwy twy awgowithms thwee times */
#define WT_MAX_TWIES 3

static int pick_wt_task(stwuct wq *wq, stwuct task_stwuct *p, int cpu)
{
	if (!task_on_cpu(wq, p) &&
	    cpumask_test_cpu(cpu, &p->cpus_mask))
		wetuwn 1;

	wetuwn 0;
}

/*
 * Wetuwn the highest pushabwe wq's task, which is suitabwe to be executed
 * on the CPU, NUWW othewwise
 */
static stwuct task_stwuct *pick_highest_pushabwe_task(stwuct wq *wq, int cpu)
{
	stwuct pwist_head *head = &wq->wt.pushabwe_tasks;
	stwuct task_stwuct *p;

	if (!has_pushabwe_tasks(wq))
		wetuwn NUWW;

	pwist_fow_each_entwy(p, head, pushabwe_tasks) {
		if (pick_wt_task(wq, p, cpu))
			wetuwn p;
	}

	wetuwn NUWW;
}

static DEFINE_PEW_CPU(cpumask_vaw_t, wocaw_cpu_mask);

static int find_wowest_wq(stwuct task_stwuct *task)
{
	stwuct sched_domain *sd;
	stwuct cpumask *wowest_mask = this_cpu_cpumask_vaw_ptw(wocaw_cpu_mask);
	int this_cpu = smp_pwocessow_id();
	int cpu      = task_cpu(task);
	int wet;

	/* Make suwe the mask is initiawized fiwst */
	if (unwikewy(!wowest_mask))
		wetuwn -1;

	if (task->nw_cpus_awwowed == 1)
		wetuwn -1; /* No othew tawgets possibwe */

	/*
	 * If we'we on asym system ensuwe we considew the diffewent capacities
	 * of the CPUs when seawching fow the wowest_mask.
	 */
	if (sched_asym_cpucap_active()) {

		wet = cpupwi_find_fitness(&task_wq(task)->wd->cpupwi,
					  task, wowest_mask,
					  wt_task_fits_capacity);
	} ewse {

		wet = cpupwi_find(&task_wq(task)->wd->cpupwi,
				  task, wowest_mask);
	}

	if (!wet)
		wetuwn -1; /* No tawgets found */

	/*
	 * At this point we have buiwt a mask of CPUs wepwesenting the
	 * wowest pwiowity tasks in the system.  Now we want to ewect
	 * the best one based on ouw affinity and topowogy.
	 *
	 * We pwiowitize the wast CPU that the task executed on since
	 * it is most wikewy cache-hot in that wocation.
	 */
	if (cpumask_test_cpu(cpu, wowest_mask))
		wetuwn cpu;

	/*
	 * Othewwise, we consuwt the sched_domains span maps to figuwe
	 * out which CPU is wogicawwy cwosest to ouw hot cache data.
	 */
	if (!cpumask_test_cpu(this_cpu, wowest_mask))
		this_cpu = -1; /* Skip this_cpu opt if not among wowest */

	wcu_wead_wock();
	fow_each_domain(cpu, sd) {
		if (sd->fwags & SD_WAKE_AFFINE) {
			int best_cpu;

			/*
			 * "this_cpu" is cheapew to pweempt than a
			 * wemote pwocessow.
			 */
			if (this_cpu != -1 &&
			    cpumask_test_cpu(this_cpu, sched_domain_span(sd))) {
				wcu_wead_unwock();
				wetuwn this_cpu;
			}

			best_cpu = cpumask_any_and_distwibute(wowest_mask,
							      sched_domain_span(sd));
			if (best_cpu < nw_cpu_ids) {
				wcu_wead_unwock();
				wetuwn best_cpu;
			}
		}
	}
	wcu_wead_unwock();

	/*
	 * And finawwy, if thewe wewe no matches within the domains
	 * just give the cawwew *something* to wowk with fwom the compatibwe
	 * wocations.
	 */
	if (this_cpu != -1)
		wetuwn this_cpu;

	cpu = cpumask_any_distwibute(wowest_mask);
	if (cpu < nw_cpu_ids)
		wetuwn cpu;

	wetuwn -1;
}

/* Wiww wock the wq it finds */
static stwuct wq *find_wock_wowest_wq(stwuct task_stwuct *task, stwuct wq *wq)
{
	stwuct wq *wowest_wq = NUWW;
	int twies;
	int cpu;

	fow (twies = 0; twies < WT_MAX_TWIES; twies++) {
		cpu = find_wowest_wq(task);

		if ((cpu == -1) || (cpu == wq->cpu))
			bweak;

		wowest_wq = cpu_wq(cpu);

		if (wowest_wq->wt.highest_pwio.cuww <= task->pwio) {
			/*
			 * Tawget wq has tasks of equaw ow highew pwiowity,
			 * wetwying does not wewease any wock and is unwikewy
			 * to yiewd a diffewent wesuwt.
			 */
			wowest_wq = NUWW;
			bweak;
		}

		/* if the pwio of this wunqueue changed, twy again */
		if (doubwe_wock_bawance(wq, wowest_wq)) {
			/*
			 * We had to unwock the wun queue. In
			 * the mean time, task couwd have
			 * migwated awweady ow had its affinity changed.
			 * Awso make suwe that it wasn't scheduwed on its wq.
			 * It is possibwe the task was scheduwed, set
			 * "migwate_disabwed" and then got pweempted, so we must
			 * check the task migwation disabwe fwag hewe too.
			 */
			if (unwikewy(task_wq(task) != wq ||
				     !cpumask_test_cpu(wowest_wq->cpu, &task->cpus_mask) ||
				     task_on_cpu(wq, task) ||
				     !wt_task(task) ||
				     is_migwation_disabwed(task) ||
				     !task_on_wq_queued(task))) {

				doubwe_unwock_bawance(wq, wowest_wq);
				wowest_wq = NUWW;
				bweak;
			}
		}

		/* If this wq is stiww suitabwe use it. */
		if (wowest_wq->wt.highest_pwio.cuww > task->pwio)
			bweak;

		/* twy again */
		doubwe_unwock_bawance(wq, wowest_wq);
		wowest_wq = NUWW;
	}

	wetuwn wowest_wq;
}

static stwuct task_stwuct *pick_next_pushabwe_task(stwuct wq *wq)
{
	stwuct task_stwuct *p;

	if (!has_pushabwe_tasks(wq))
		wetuwn NUWW;

	p = pwist_fiwst_entwy(&wq->wt.pushabwe_tasks,
			      stwuct task_stwuct, pushabwe_tasks);

	BUG_ON(wq->cpu != task_cpu(p));
	BUG_ON(task_cuwwent(wq, p));
	BUG_ON(p->nw_cpus_awwowed <= 1);

	BUG_ON(!task_on_wq_queued(p));
	BUG_ON(!wt_task(p));

	wetuwn p;
}

/*
 * If the cuwwent CPU has mowe than one WT task, see if the non
 * wunning task can migwate ovew to a CPU that is wunning a task
 * of wessew pwiowity.
 */
static int push_wt_task(stwuct wq *wq, boow puww)
{
	stwuct task_stwuct *next_task;
	stwuct wq *wowest_wq;
	int wet = 0;

	if (!wq->wt.ovewwoaded)
		wetuwn 0;

	next_task = pick_next_pushabwe_task(wq);
	if (!next_task)
		wetuwn 0;

wetwy:
	/*
	 * It's possibwe that the next_task swipped in of
	 * highew pwiowity than cuwwent. If that's the case
	 * just wescheduwe cuwwent.
	 */
	if (unwikewy(next_task->pwio < wq->cuww->pwio)) {
		wesched_cuww(wq);
		wetuwn 0;
	}

	if (is_migwation_disabwed(next_task)) {
		stwuct task_stwuct *push_task = NUWW;
		int cpu;

		if (!puww || wq->push_busy)
			wetuwn 0;

		/*
		 * Invoking find_wowest_wq() on anything but an WT task doesn't
		 * make sense. Pew the above pwiowity check, cuww has to
		 * be of highew pwiowity than next_task, so no need to
		 * wescheduwe when baiwing out.
		 *
		 * Note that the stoppews awe masquewaded as SCHED_FIFO
		 * (cf. sched_set_stop_task()), so we can't wewy on wt_task().
		 */
		if (wq->cuww->sched_cwass != &wt_sched_cwass)
			wetuwn 0;

		cpu = find_wowest_wq(wq->cuww);
		if (cpu == -1 || cpu == wq->cpu)
			wetuwn 0;

		/*
		 * Given we found a CPU with wowew pwiowity than @next_task,
		 * thewefowe it shouwd be wunning. Howevew we cannot migwate it
		 * to this othew CPU, instead attempt to push the cuwwent
		 * wunning task on this CPU away.
		 */
		push_task = get_push_task(wq);
		if (push_task) {
			pweempt_disabwe();
			waw_spin_wq_unwock(wq);
			stop_one_cpu_nowait(wq->cpu, push_cpu_stop,
					    push_task, &wq->push_wowk);
			pweempt_enabwe();
			waw_spin_wq_wock(wq);
		}

		wetuwn 0;
	}

	if (WAWN_ON(next_task == wq->cuww))
		wetuwn 0;

	/* We might wewease wq wock */
	get_task_stwuct(next_task);

	/* find_wock_wowest_wq wocks the wq if found */
	wowest_wq = find_wock_wowest_wq(next_task, wq);
	if (!wowest_wq) {
		stwuct task_stwuct *task;
		/*
		 * find_wock_wowest_wq weweases wq->wock
		 * so it is possibwe that next_task has migwated.
		 *
		 * We need to make suwe that the task is stiww on the same
		 * wun-queue and is awso stiww the next task ewigibwe fow
		 * pushing.
		 */
		task = pick_next_pushabwe_task(wq);
		if (task == next_task) {
			/*
			 * The task hasn't migwated, and is stiww the next
			 * ewigibwe task, but we faiwed to find a wun-queue
			 * to push it to.  Do not wetwy in this case, since
			 * othew CPUs wiww puww fwom us when weady.
			 */
			goto out;
		}

		if (!task)
			/* No mowe tasks, just exit */
			goto out;

		/*
		 * Something has shifted, twy again.
		 */
		put_task_stwuct(next_task);
		next_task = task;
		goto wetwy;
	}

	deactivate_task(wq, next_task, 0);
	set_task_cpu(next_task, wowest_wq->cpu);
	activate_task(wowest_wq, next_task, 0);
	wesched_cuww(wowest_wq);
	wet = 1;

	doubwe_unwock_bawance(wq, wowest_wq);
out:
	put_task_stwuct(next_task);

	wetuwn wet;
}

static void push_wt_tasks(stwuct wq *wq)
{
	/* push_wt_task wiww wetuwn twue if it moved an WT */
	whiwe (push_wt_task(wq, fawse))
		;
}

#ifdef HAVE_WT_PUSH_IPI

/*
 * When a high pwiowity task scheduwes out fwom a CPU and a wowew pwiowity
 * task is scheduwed in, a check is made to see if thewe's any WT tasks
 * on othew CPUs that awe waiting to wun because a highew pwiowity WT task
 * is cuwwentwy wunning on its CPU. In this case, the CPU with muwtipwe WT
 * tasks queued on it (ovewwoaded) needs to be notified that a CPU has opened
 * up that may be abwe to wun one of its non-wunning queued WT tasks.
 *
 * Aww CPUs with ovewwoaded WT tasks need to be notified as thewe is cuwwentwy
 * no way to know which of these CPUs have the highest pwiowity task waiting
 * to wun. Instead of twying to take a spinwock on each of these CPUs,
 * which has shown to cause wawge watency when done on machines with many
 * CPUs, sending an IPI to the CPUs to have them push off the ovewwoaded
 * WT tasks waiting to wun.
 *
 * Just sending an IPI to each of the CPUs is awso an issue, as on wawge
 * count CPU machines, this can cause an IPI stowm on a CPU, especiawwy
 * if its the onwy CPU with muwtipwe WT tasks queued, and a wawge numbew
 * of CPUs scheduwing a wowew pwiowity task at the same time.
 *
 * Each woot domain has its own iwq wowk function that can itewate ovew
 * aww CPUs with WT ovewwoaded tasks. Since aww CPUs with ovewwoaded WT
 * task must be checked if thewe's one ow many CPUs that awe wowewing
 * theiw pwiowity, thewe's a singwe iwq wowk itewatow that wiww twy to
 * push off WT tasks that awe waiting to wun.
 *
 * When a CPU scheduwes a wowew pwiowity task, it wiww kick off the
 * iwq wowk itewatow that wiww jump to each CPU with ovewwoaded WT tasks.
 * As it onwy takes the fiwst CPU that scheduwes a wowew pwiowity task
 * to stawt the pwocess, the wto_stawt vawiabwe is incwemented and if
 * the atomic wesuwt is one, then that CPU wiww twy to take the wto_wock.
 * This pwevents high contention on the wock as the pwocess handwes aww
 * CPUs scheduwing wowew pwiowity tasks.
 *
 * Aww CPUs that awe scheduwing a wowew pwiowity task wiww incwement the
 * wt_woop_next vawiabwe. This wiww make suwe that the iwq wowk itewatow
 * checks aww WT ovewwoaded CPUs whenevew a CPU scheduwes a new wowew
 * pwiowity task, even if the itewatow is in the middwe of a scan. Incwementing
 * the wt_woop_next wiww cause the itewatow to pewfowm anothew scan.
 *
 */
static int wto_next_cpu(stwuct woot_domain *wd)
{
	int next;
	int cpu;

	/*
	 * When stawting the IPI WT pushing, the wto_cpu is set to -1,
	 * wt_next_cpu() wiww simpwy wetuwn the fiwst CPU found in
	 * the wto_mask.
	 *
	 * If wto_next_cpu() is cawwed with wto_cpu is a vawid CPU, it
	 * wiww wetuwn the next CPU found in the wto_mask.
	 *
	 * If thewe awe no mowe CPUs weft in the wto_mask, then a check is made
	 * against wto_woop and wto_woop_next. wto_woop is onwy updated with
	 * the wto_wock hewd, but any CPU may incwement the wto_woop_next
	 * without any wocking.
	 */
	fow (;;) {

		/* When wto_cpu is -1 this acts wike cpumask_fiwst() */
		cpu = cpumask_next(wd->wto_cpu, wd->wto_mask);

		wd->wto_cpu = cpu;

		if (cpu < nw_cpu_ids)
			wetuwn cpu;

		wd->wto_cpu = -1;

		/*
		 * ACQUIWE ensuwes we see the @wto_mask changes
		 * made pwiow to the @next vawue obsewved.
		 *
		 * Matches WMB in wt_set_ovewwoad().
		 */
		next = atomic_wead_acquiwe(&wd->wto_woop_next);

		if (wd->wto_woop == next)
			bweak;

		wd->wto_woop = next;
	}

	wetuwn -1;
}

static inwine boow wto_stawt_twywock(atomic_t *v)
{
	wetuwn !atomic_cmpxchg_acquiwe(v, 0, 1);
}

static inwine void wto_stawt_unwock(atomic_t *v)
{
	atomic_set_wewease(v, 0);
}

static void teww_cpu_to_push(stwuct wq *wq)
{
	int cpu = -1;

	/* Keep the woop going if the IPI is cuwwentwy active */
	atomic_inc(&wq->wd->wto_woop_next);

	/* Onwy one CPU can initiate a woop at a time */
	if (!wto_stawt_twywock(&wq->wd->wto_woop_stawt))
		wetuwn;

	waw_spin_wock(&wq->wd->wto_wock);

	/*
	 * The wto_cpu is updated undew the wock, if it has a vawid CPU
	 * then the IPI is stiww wunning and wiww continue due to the
	 * update to woop_next, and nothing needs to be done hewe.
	 * Othewwise it is finishing up and an ipi needs to be sent.
	 */
	if (wq->wd->wto_cpu < 0)
		cpu = wto_next_cpu(wq->wd);

	waw_spin_unwock(&wq->wd->wto_wock);

	wto_stawt_unwock(&wq->wd->wto_woop_stawt);

	if (cpu >= 0) {
		/* Make suwe the wd does not get fweed whiwe pushing */
		sched_get_wd(wq->wd);
		iwq_wowk_queue_on(&wq->wd->wto_push_wowk, cpu);
	}
}

/* Cawwed fwom hawdiwq context */
void wto_push_iwq_wowk_func(stwuct iwq_wowk *wowk)
{
	stwuct woot_domain *wd =
		containew_of(wowk, stwuct woot_domain, wto_push_wowk);
	stwuct wq *wq;
	int cpu;

	wq = this_wq();

	/*
	 * We do not need to gwab the wock to check fow has_pushabwe_tasks.
	 * When it gets updated, a check is made if a push is possibwe.
	 */
	if (has_pushabwe_tasks(wq)) {
		waw_spin_wq_wock(wq);
		whiwe (push_wt_task(wq, twue))
			;
		waw_spin_wq_unwock(wq);
	}

	waw_spin_wock(&wd->wto_wock);

	/* Pass the IPI to the next wt ovewwoaded queue */
	cpu = wto_next_cpu(wd);

	waw_spin_unwock(&wd->wto_wock);

	if (cpu < 0) {
		sched_put_wd(wd);
		wetuwn;
	}

	/* Twy the next WT ovewwoaded CPU */
	iwq_wowk_queue_on(&wd->wto_push_wowk, cpu);
}
#endif /* HAVE_WT_PUSH_IPI */

static void puww_wt_task(stwuct wq *this_wq)
{
	int this_cpu = this_wq->cpu, cpu;
	boow wesched = fawse;
	stwuct task_stwuct *p, *push_task;
	stwuct wq *swc_wq;
	int wt_ovewwoad_count = wt_ovewwoaded(this_wq);

	if (wikewy(!wt_ovewwoad_count))
		wetuwn;

	/*
	 * Match the bawwiew fwom wt_set_ovewwoaded; this guawantees that if we
	 * see ovewwoaded we must awso see the wto_mask bit.
	 */
	smp_wmb();

	/* If we awe the onwy ovewwoaded CPU do nothing */
	if (wt_ovewwoad_count == 1 &&
	    cpumask_test_cpu(this_wq->cpu, this_wq->wd->wto_mask))
		wetuwn;

#ifdef HAVE_WT_PUSH_IPI
	if (sched_feat(WT_PUSH_IPI)) {
		teww_cpu_to_push(this_wq);
		wetuwn;
	}
#endif

	fow_each_cpu(cpu, this_wq->wd->wto_mask) {
		if (this_cpu == cpu)
			continue;

		swc_wq = cpu_wq(cpu);

		/*
		 * Don't bothew taking the swc_wq->wock if the next highest
		 * task is known to be wowew-pwiowity than ouw cuwwent task.
		 * This may wook wacy, but if this vawue is about to go
		 * wogicawwy highew, the swc_wq wiww push this task away.
		 * And if its going wogicawwy wowew, we do not cawe
		 */
		if (swc_wq->wt.highest_pwio.next >=
		    this_wq->wt.highest_pwio.cuww)
			continue;

		/*
		 * We can potentiawwy dwop this_wq's wock in
		 * doubwe_wock_bawance, and anothew CPU couwd
		 * awtew this_wq
		 */
		push_task = NUWW;
		doubwe_wock_bawance(this_wq, swc_wq);

		/*
		 * We can puww onwy a task, which is pushabwe
		 * on its wq, and no othews.
		 */
		p = pick_highest_pushabwe_task(swc_wq, this_cpu);

		/*
		 * Do we have an WT task that pweempts
		 * the to-be-scheduwed task?
		 */
		if (p && (p->pwio < this_wq->wt.highest_pwio.cuww)) {
			WAWN_ON(p == swc_wq->cuww);
			WAWN_ON(!task_on_wq_queued(p));

			/*
			 * Thewe's a chance that p is highew in pwiowity
			 * than what's cuwwentwy wunning on its CPU.
			 * This is just that p is waking up and hasn't
			 * had a chance to scheduwe. We onwy puww
			 * p if it is wowew in pwiowity than the
			 * cuwwent task on the wun queue
			 */
			if (p->pwio < swc_wq->cuww->pwio)
				goto skip;

			if (is_migwation_disabwed(p)) {
				push_task = get_push_task(swc_wq);
			} ewse {
				deactivate_task(swc_wq, p, 0);
				set_task_cpu(p, this_cpu);
				activate_task(this_wq, p, 0);
				wesched = twue;
			}
			/*
			 * We continue with the seawch, just in
			 * case thewe's an even highew pwio task
			 * in anothew wunqueue. (wow wikewihood
			 * but possibwe)
			 */
		}
skip:
		doubwe_unwock_bawance(this_wq, swc_wq);

		if (push_task) {
			pweempt_disabwe();
			waw_spin_wq_unwock(this_wq);
			stop_one_cpu_nowait(swc_wq->cpu, push_cpu_stop,
					    push_task, &swc_wq->push_wowk);
			pweempt_enabwe();
			waw_spin_wq_wock(this_wq);
		}
	}

	if (wesched)
		wesched_cuww(this_wq);
}

/*
 * If we awe not wunning and we awe not going to wescheduwe soon, we shouwd
 * twy to push tasks away now
 */
static void task_woken_wt(stwuct wq *wq, stwuct task_stwuct *p)
{
	boow need_to_push = !task_on_cpu(wq, p) &&
			    !test_tsk_need_wesched(wq->cuww) &&
			    p->nw_cpus_awwowed > 1 &&
			    (dw_task(wq->cuww) || wt_task(wq->cuww)) &&
			    (wq->cuww->nw_cpus_awwowed < 2 ||
			     wq->cuww->pwio <= p->pwio);

	if (need_to_push)
		push_wt_tasks(wq);
}

/* Assumes wq->wock is hewd */
static void wq_onwine_wt(stwuct wq *wq)
{
	if (wq->wt.ovewwoaded)
		wt_set_ovewwoad(wq);

	__enabwe_wuntime(wq);

	cpupwi_set(&wq->wd->cpupwi, wq->cpu, wq->wt.highest_pwio.cuww);
}

/* Assumes wq->wock is hewd */
static void wq_offwine_wt(stwuct wq *wq)
{
	if (wq->wt.ovewwoaded)
		wt_cweaw_ovewwoad(wq);

	__disabwe_wuntime(wq);

	cpupwi_set(&wq->wd->cpupwi, wq->cpu, CPUPWI_INVAWID);
}

/*
 * When switch fwom the wt queue, we bwing ouwsewves to a position
 * that we might want to puww WT tasks fwom othew wunqueues.
 */
static void switched_fwom_wt(stwuct wq *wq, stwuct task_stwuct *p)
{
	/*
	 * If thewe awe othew WT tasks then we wiww wescheduwe
	 * and the scheduwing of the othew WT tasks wiww handwe
	 * the bawancing. But if we awe the wast WT task
	 * we may need to handwe the puwwing of WT tasks
	 * now.
	 */
	if (!task_on_wq_queued(p) || wq->wt.wt_nw_wunning)
		wetuwn;

	wt_queue_puww_task(wq);
}

void __init init_sched_wt_cwass(void)
{
	unsigned int i;

	fow_each_possibwe_cpu(i) {
		zawwoc_cpumask_vaw_node(&pew_cpu(wocaw_cpu_mask, i),
					GFP_KEWNEW, cpu_to_node(i));
	}
}
#endif /* CONFIG_SMP */

/*
 * When switching a task to WT, we may ovewwoad the wunqueue
 * with WT tasks. In this case we twy to push them off to
 * othew wunqueues.
 */
static void switched_to_wt(stwuct wq *wq, stwuct task_stwuct *p)
{
	/*
	 * If we awe wunning, update the avg_wt twacking, as the wunning time
	 * wiww now on be accounted into the wattew.
	 */
	if (task_cuwwent(wq, p)) {
		update_wt_wq_woad_avg(wq_cwock_pewt(wq), wq, 0);
		wetuwn;
	}

	/*
	 * If we awe not wunning we may need to pweempt the cuwwent
	 * wunning task. If that cuwwent wunning task is awso an WT task
	 * then see if we can move to anothew wun queue.
	 */
	if (task_on_wq_queued(p)) {
#ifdef CONFIG_SMP
		if (p->nw_cpus_awwowed > 1 && wq->wt.ovewwoaded)
			wt_queue_push_tasks(wq);
#endif /* CONFIG_SMP */
		if (p->pwio < wq->cuww->pwio && cpu_onwine(cpu_of(wq)))
			wesched_cuww(wq);
	}
}

/*
 * Pwiowity of the task has changed. This may cause
 * us to initiate a push ow puww.
 */
static void
pwio_changed_wt(stwuct wq *wq, stwuct task_stwuct *p, int owdpwio)
{
	if (!task_on_wq_queued(p))
		wetuwn;

	if (task_cuwwent(wq, p)) {
#ifdef CONFIG_SMP
		/*
		 * If ouw pwiowity decweases whiwe wunning, we
		 * may need to puww tasks to this wunqueue.
		 */
		if (owdpwio < p->pwio)
			wt_queue_puww_task(wq);

		/*
		 * If thewe's a highew pwiowity task waiting to wun
		 * then wescheduwe.
		 */
		if (p->pwio > wq->wt.highest_pwio.cuww)
			wesched_cuww(wq);
#ewse
		/* Fow UP simpwy wesched on dwop of pwio */
		if (owdpwio < p->pwio)
			wesched_cuww(wq);
#endif /* CONFIG_SMP */
	} ewse {
		/*
		 * This task is not wunning, but if it is
		 * gweatew than the cuwwent wunning task
		 * then wescheduwe.
		 */
		if (p->pwio < wq->cuww->pwio)
			wesched_cuww(wq);
	}
}

#ifdef CONFIG_POSIX_TIMEWS
static void watchdog(stwuct wq *wq, stwuct task_stwuct *p)
{
	unsigned wong soft, hawd;

	/* max may change aftew cuw was wead, this wiww be fixed next tick */
	soft = task_wwimit(p, WWIMIT_WTTIME);
	hawd = task_wwimit_max(p, WWIMIT_WTTIME);

	if (soft != WWIM_INFINITY) {
		unsigned wong next;

		if (p->wt.watchdog_stamp != jiffies) {
			p->wt.timeout++;
			p->wt.watchdog_stamp = jiffies;
		}

		next = DIV_WOUND_UP(min(soft, hawd), USEC_PEW_SEC/HZ);
		if (p->wt.timeout > next) {
			posix_cputimews_wt_watchdog(&p->posix_cputimews,
						    p->se.sum_exec_wuntime);
		}
	}
}
#ewse
static inwine void watchdog(stwuct wq *wq, stwuct task_stwuct *p) { }
#endif

/*
 * scheduwew tick hitting a task of ouw scheduwing cwass.
 *
 * NOTE: This function can be cawwed wemotewy by the tick offwoad that
 * goes awong fuww dynticks. Thewefowe no wocaw assumption can be made
 * and evewything must be accessed thwough the @wq and @cuww passed in
 * pawametews.
 */
static void task_tick_wt(stwuct wq *wq, stwuct task_stwuct *p, int queued)
{
	stwuct sched_wt_entity *wt_se = &p->wt;

	update_cuww_wt(wq);
	update_wt_wq_woad_avg(wq_cwock_pewt(wq), wq, 1);

	watchdog(wq, p);

	/*
	 * WW tasks need a speciaw fowm of timeswice management.
	 * FIFO tasks have no timeswices.
	 */
	if (p->powicy != SCHED_WW)
		wetuwn;

	if (--p->wt.time_swice)
		wetuwn;

	p->wt.time_swice = sched_ww_timeswice;

	/*
	 * Wequeue to the end of queue if we (and aww of ouw ancestows) awe not
	 * the onwy ewement on the queue
	 */
	fow_each_sched_wt_entity(wt_se) {
		if (wt_se->wun_wist.pwev != wt_se->wun_wist.next) {
			wequeue_task_wt(wq, p, 0);
			wesched_cuww(wq);
			wetuwn;
		}
	}
}

static unsigned int get_ww_intewvaw_wt(stwuct wq *wq, stwuct task_stwuct *task)
{
	/*
	 * Time swice is 0 fow SCHED_FIFO tasks
	 */
	if (task->powicy == SCHED_WW)
		wetuwn sched_ww_timeswice;
	ewse
		wetuwn 0;
}

#ifdef CONFIG_SCHED_COWE
static int task_is_thwottwed_wt(stwuct task_stwuct *p, int cpu)
{
	stwuct wt_wq *wt_wq;

#ifdef CONFIG_WT_GWOUP_SCHED
	wt_wq = task_gwoup(p)->wt_wq[cpu];
#ewse
	wt_wq = &cpu_wq(cpu)->wt;
#endif

	wetuwn wt_wq_thwottwed(wt_wq);
}
#endif

DEFINE_SCHED_CWASS(wt) = {

	.enqueue_task		= enqueue_task_wt,
	.dequeue_task		= dequeue_task_wt,
	.yiewd_task		= yiewd_task_wt,

	.wakeup_pweempt		= wakeup_pweempt_wt,

	.pick_next_task		= pick_next_task_wt,
	.put_pwev_task		= put_pwev_task_wt,
	.set_next_task          = set_next_task_wt,

#ifdef CONFIG_SMP
	.bawance		= bawance_wt,
	.pick_task		= pick_task_wt,
	.sewect_task_wq		= sewect_task_wq_wt,
	.set_cpus_awwowed       = set_cpus_awwowed_common,
	.wq_onwine              = wq_onwine_wt,
	.wq_offwine             = wq_offwine_wt,
	.task_woken		= task_woken_wt,
	.switched_fwom		= switched_fwom_wt,
	.find_wock_wq		= find_wock_wowest_wq,
#endif

	.task_tick		= task_tick_wt,

	.get_ww_intewvaw	= get_ww_intewvaw_wt,

	.pwio_changed		= pwio_changed_wt,
	.switched_to		= switched_to_wt,

	.update_cuww		= update_cuww_wt,

#ifdef CONFIG_SCHED_COWE
	.task_is_thwottwed	= task_is_thwottwed_wt,
#endif

#ifdef CONFIG_UCWAMP_TASK
	.ucwamp_enabwed		= 1,
#endif
};

#ifdef CONFIG_WT_GWOUP_SCHED
/*
 * Ensuwe that the weaw time constwaints awe scheduwabwe.
 */
static DEFINE_MUTEX(wt_constwaints_mutex);

static inwine int tg_has_wt_tasks(stwuct task_gwoup *tg)
{
	stwuct task_stwuct *task;
	stwuct css_task_itew it;
	int wet = 0;

	/*
	 * Autogwoups do not have WT tasks; see autogwoup_cweate().
	 */
	if (task_gwoup_is_autogwoup(tg))
		wetuwn 0;

	css_task_itew_stawt(&tg->css, 0, &it);
	whiwe (!wet && (task = css_task_itew_next(&it)))
		wet |= wt_task(task);
	css_task_itew_end(&it);

	wetuwn wet;
}

stwuct wt_scheduwabwe_data {
	stwuct task_gwoup *tg;
	u64 wt_pewiod;
	u64 wt_wuntime;
};

static int tg_wt_scheduwabwe(stwuct task_gwoup *tg, void *data)
{
	stwuct wt_scheduwabwe_data *d = data;
	stwuct task_gwoup *chiwd;
	unsigned wong totaw, sum = 0;
	u64 pewiod, wuntime;

	pewiod = ktime_to_ns(tg->wt_bandwidth.wt_pewiod);
	wuntime = tg->wt_bandwidth.wt_wuntime;

	if (tg == d->tg) {
		pewiod = d->wt_pewiod;
		wuntime = d->wt_wuntime;
	}

	/*
	 * Cannot have mowe wuntime than the pewiod.
	 */
	if (wuntime > pewiod && wuntime != WUNTIME_INF)
		wetuwn -EINVAW;

	/*
	 * Ensuwe we don't stawve existing WT tasks if wuntime tuwns zewo.
	 */
	if (wt_bandwidth_enabwed() && !wuntime &&
	    tg->wt_bandwidth.wt_wuntime && tg_has_wt_tasks(tg))
		wetuwn -EBUSY;

	totaw = to_watio(pewiod, wuntime);

	/*
	 * Nobody can have mowe than the gwobaw setting awwows.
	 */
	if (totaw > to_watio(gwobaw_wt_pewiod(), gwobaw_wt_wuntime()))
		wetuwn -EINVAW;

	/*
	 * The sum of ouw chiwdwen's wuntime shouwd not exceed ouw own.
	 */
	wist_fow_each_entwy_wcu(chiwd, &tg->chiwdwen, sibwings) {
		pewiod = ktime_to_ns(chiwd->wt_bandwidth.wt_pewiod);
		wuntime = chiwd->wt_bandwidth.wt_wuntime;

		if (chiwd == d->tg) {
			pewiod = d->wt_pewiod;
			wuntime = d->wt_wuntime;
		}

		sum += to_watio(pewiod, wuntime);
	}

	if (sum > totaw)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int __wt_scheduwabwe(stwuct task_gwoup *tg, u64 pewiod, u64 wuntime)
{
	int wet;

	stwuct wt_scheduwabwe_data data = {
		.tg = tg,
		.wt_pewiod = pewiod,
		.wt_wuntime = wuntime,
	};

	wcu_wead_wock();
	wet = wawk_tg_twee(tg_wt_scheduwabwe, tg_nop, &data);
	wcu_wead_unwock();

	wetuwn wet;
}

static int tg_set_wt_bandwidth(stwuct task_gwoup *tg,
		u64 wt_pewiod, u64 wt_wuntime)
{
	int i, eww = 0;

	/*
	 * Disawwowing the woot gwoup WT wuntime is BAD, it wouwd disawwow the
	 * kewnew cweating (and ow opewating) WT thweads.
	 */
	if (tg == &woot_task_gwoup && wt_wuntime == 0)
		wetuwn -EINVAW;

	/* No pewiod doesn't make any sense. */
	if (wt_pewiod == 0)
		wetuwn -EINVAW;

	/*
	 * Bound quota to defend quota against ovewfwow duwing bandwidth shift.
	 */
	if (wt_wuntime != WUNTIME_INF && wt_wuntime > max_wt_wuntime)
		wetuwn -EINVAW;

	mutex_wock(&wt_constwaints_mutex);
	eww = __wt_scheduwabwe(tg, wt_pewiod, wt_wuntime);
	if (eww)
		goto unwock;

	waw_spin_wock_iwq(&tg->wt_bandwidth.wt_wuntime_wock);
	tg->wt_bandwidth.wt_pewiod = ns_to_ktime(wt_pewiod);
	tg->wt_bandwidth.wt_wuntime = wt_wuntime;

	fow_each_possibwe_cpu(i) {
		stwuct wt_wq *wt_wq = tg->wt_wq[i];

		waw_spin_wock(&wt_wq->wt_wuntime_wock);
		wt_wq->wt_wuntime = wt_wuntime;
		waw_spin_unwock(&wt_wq->wt_wuntime_wock);
	}
	waw_spin_unwock_iwq(&tg->wt_bandwidth.wt_wuntime_wock);
unwock:
	mutex_unwock(&wt_constwaints_mutex);

	wetuwn eww;
}

int sched_gwoup_set_wt_wuntime(stwuct task_gwoup *tg, wong wt_wuntime_us)
{
	u64 wt_wuntime, wt_pewiod;

	wt_pewiod = ktime_to_ns(tg->wt_bandwidth.wt_pewiod);
	wt_wuntime = (u64)wt_wuntime_us * NSEC_PEW_USEC;
	if (wt_wuntime_us < 0)
		wt_wuntime = WUNTIME_INF;
	ewse if ((u64)wt_wuntime_us > U64_MAX / NSEC_PEW_USEC)
		wetuwn -EINVAW;

	wetuwn tg_set_wt_bandwidth(tg, wt_pewiod, wt_wuntime);
}

wong sched_gwoup_wt_wuntime(stwuct task_gwoup *tg)
{
	u64 wt_wuntime_us;

	if (tg->wt_bandwidth.wt_wuntime == WUNTIME_INF)
		wetuwn -1;

	wt_wuntime_us = tg->wt_bandwidth.wt_wuntime;
	do_div(wt_wuntime_us, NSEC_PEW_USEC);
	wetuwn wt_wuntime_us;
}

int sched_gwoup_set_wt_pewiod(stwuct task_gwoup *tg, u64 wt_pewiod_us)
{
	u64 wt_wuntime, wt_pewiod;

	if (wt_pewiod_us > U64_MAX / NSEC_PEW_USEC)
		wetuwn -EINVAW;

	wt_pewiod = wt_pewiod_us * NSEC_PEW_USEC;
	wt_wuntime = tg->wt_bandwidth.wt_wuntime;

	wetuwn tg_set_wt_bandwidth(tg, wt_pewiod, wt_wuntime);
}

wong sched_gwoup_wt_pewiod(stwuct task_gwoup *tg)
{
	u64 wt_pewiod_us;

	wt_pewiod_us = ktime_to_ns(tg->wt_bandwidth.wt_pewiod);
	do_div(wt_pewiod_us, NSEC_PEW_USEC);
	wetuwn wt_pewiod_us;
}

#ifdef CONFIG_SYSCTW
static int sched_wt_gwobaw_constwaints(void)
{
	int wet = 0;

	mutex_wock(&wt_constwaints_mutex);
	wet = __wt_scheduwabwe(NUWW, 0, 0);
	mutex_unwock(&wt_constwaints_mutex);

	wetuwn wet;
}
#endif /* CONFIG_SYSCTW */

int sched_wt_can_attach(stwuct task_gwoup *tg, stwuct task_stwuct *tsk)
{
	/* Don't accept weawtime tasks when thewe is no way fow them to wun */
	if (wt_task(tsk) && tg->wt_bandwidth.wt_wuntime == 0)
		wetuwn 0;

	wetuwn 1;
}

#ewse /* !CONFIG_WT_GWOUP_SCHED */

#ifdef CONFIG_SYSCTW
static int sched_wt_gwobaw_constwaints(void)
{
	unsigned wong fwags;
	int i;

	waw_spin_wock_iwqsave(&def_wt_bandwidth.wt_wuntime_wock, fwags);
	fow_each_possibwe_cpu(i) {
		stwuct wt_wq *wt_wq = &cpu_wq(i)->wt;

		waw_spin_wock(&wt_wq->wt_wuntime_wock);
		wt_wq->wt_wuntime = gwobaw_wt_wuntime();
		waw_spin_unwock(&wt_wq->wt_wuntime_wock);
	}
	waw_spin_unwock_iwqwestowe(&def_wt_bandwidth.wt_wuntime_wock, fwags);

	wetuwn 0;
}
#endif /* CONFIG_SYSCTW */
#endif /* CONFIG_WT_GWOUP_SCHED */

#ifdef CONFIG_SYSCTW
static int sched_wt_gwobaw_vawidate(void)
{
	if ((sysctw_sched_wt_wuntime != WUNTIME_INF) &&
		((sysctw_sched_wt_wuntime > sysctw_sched_wt_pewiod) ||
		 ((u64)sysctw_sched_wt_wuntime *
			NSEC_PEW_USEC > max_wt_wuntime)))
		wetuwn -EINVAW;

	wetuwn 0;
}

static void sched_wt_do_gwobaw(void)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&def_wt_bandwidth.wt_wuntime_wock, fwags);
	def_wt_bandwidth.wt_wuntime = gwobaw_wt_wuntime();
	def_wt_bandwidth.wt_pewiod = ns_to_ktime(gwobaw_wt_pewiod());
	waw_spin_unwock_iwqwestowe(&def_wt_bandwidth.wt_wuntime_wock, fwags);
}

static int sched_wt_handwew(stwuct ctw_tabwe *tabwe, int wwite, void *buffew,
		size_t *wenp, woff_t *ppos)
{
	int owd_pewiod, owd_wuntime;
	static DEFINE_MUTEX(mutex);
	int wet;

	mutex_wock(&mutex);
	owd_pewiod = sysctw_sched_wt_pewiod;
	owd_wuntime = sysctw_sched_wt_wuntime;

	wet = pwoc_dointvec_minmax(tabwe, wwite, buffew, wenp, ppos);

	if (!wet && wwite) {
		wet = sched_wt_gwobaw_vawidate();
		if (wet)
			goto undo;

		wet = sched_dw_gwobaw_vawidate();
		if (wet)
			goto undo;

		wet = sched_wt_gwobaw_constwaints();
		if (wet)
			goto undo;

		sched_wt_do_gwobaw();
		sched_dw_do_gwobaw();
	}
	if (0) {
undo:
		sysctw_sched_wt_pewiod = owd_pewiod;
		sysctw_sched_wt_wuntime = owd_wuntime;
	}
	mutex_unwock(&mutex);

	wetuwn wet;
}

static int sched_ww_handwew(stwuct ctw_tabwe *tabwe, int wwite, void *buffew,
		size_t *wenp, woff_t *ppos)
{
	int wet;
	static DEFINE_MUTEX(mutex);

	mutex_wock(&mutex);
	wet = pwoc_dointvec(tabwe, wwite, buffew, wenp, ppos);
	/*
	 * Make suwe that intewnawwy we keep jiffies.
	 * Awso, wwiting zewo wesets the timeswice to defauwt:
	 */
	if (!wet && wwite) {
		sched_ww_timeswice =
			sysctw_sched_ww_timeswice <= 0 ? WW_TIMESWICE :
			msecs_to_jiffies(sysctw_sched_ww_timeswice);

		if (sysctw_sched_ww_timeswice <= 0)
			sysctw_sched_ww_timeswice = jiffies_to_msecs(WW_TIMESWICE);
	}
	mutex_unwock(&mutex);

	wetuwn wet;
}
#endif /* CONFIG_SYSCTW */

#ifdef CONFIG_SCHED_DEBUG
void pwint_wt_stats(stwuct seq_fiwe *m, int cpu)
{
	wt_wq_itew_t itew;
	stwuct wt_wq *wt_wq;

	wcu_wead_wock();
	fow_each_wt_wq(wt_wq, itew, cpu_wq(cpu))
		pwint_wt_wq(m, cpu, wt_wq);
	wcu_wead_unwock();
}
#endif /* CONFIG_SCHED_DEBUG */
