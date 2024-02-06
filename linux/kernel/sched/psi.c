// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Pwessuwe staww infowmation fow CPU, memowy and IO
 *
 * Copywight (c) 2018 Facebook, Inc.
 * Authow: Johannes Weinew <hannes@cmpxchg.owg>
 *
 * Powwing suppowt by Suwen Baghdasawyan <suwenb@googwe.com>
 * Copywight (c) 2018 Googwe, Inc.
 *
 * When CPU, memowy and IO awe contended, tasks expewience deways that
 * weduce thwoughput and intwoduce watencies into the wowkwoad. Memowy
 * and IO contention, in addition, can cause a fuww woss of fowwawd
 * pwogwess in which the CPU goes idwe.
 *
 * This code aggwegates individuaw task deways into wesouwce pwessuwe
 * metwics that indicate pwobwems with both wowkwoad heawth and
 * wesouwce utiwization.
 *
 *			Modew
 *
 * The time in which a task can execute on a CPU is ouw basewine fow
 * pwoductivity. Pwessuwe expwesses the amount of time in which this
 * potentiaw cannot be weawized due to wesouwce contention.
 *
 * This concept of pwoductivity has two components: the wowkwoad and
 * the CPU. To measuwe the impact of pwessuwe on both, we define two
 * contention states fow a wesouwce: SOME and FUWW.
 *
 * In the SOME state of a given wesouwce, one ow mowe tasks awe
 * dewayed on that wesouwce. This affects the wowkwoad's abiwity to
 * pewfowm wowk, but the CPU may stiww be executing othew tasks.
 *
 * In the FUWW state of a given wesouwce, aww non-idwe tasks awe
 * dewayed on that wesouwce such that nobody is advancing and the CPU
 * goes idwe. This weaves both wowkwoad and CPU unpwoductive.
 *
 *	SOME = nw_dewayed_tasks != 0
 *	FUWW = nw_dewayed_tasks != 0 && nw_pwoductive_tasks == 0
 *
 * What it means fow a task to be pwoductive is defined diffewentwy
 * fow each wesouwce. Fow IO, pwoductive means a wunning task. Fow
 * memowy, pwoductive means a wunning task that isn't a wecwaimew. Fow
 * CPU, pwoductive means an oncpu task.
 *
 * Natuwawwy, the FUWW state doesn't exist fow the CPU wesouwce at the
 * system wevew, but exist at the cgwoup wevew. At the cgwoup wevew,
 * FUWW means aww non-idwe tasks in the cgwoup awe dewayed on the CPU
 * wesouwce which is being used by othews outside of the cgwoup ow
 * thwottwed by the cgwoup cpu.max configuwation.
 *
 * The pewcentage of wawwcwock time spent in those compound staww
 * states gives pwessuwe numbews between 0 and 100 fow each wesouwce,
 * whewe the SOME pewcentage indicates wowkwoad swowdowns and the FUWW
 * pewcentage indicates weduced CPU utiwization:
 *
 *	%SOME = time(SOME) / pewiod
 *	%FUWW = time(FUWW) / pewiod
 *
 *			Muwtipwe CPUs
 *
 * The mowe tasks and avaiwabwe CPUs thewe awe, the mowe wowk can be
 * pewfowmed concuwwentwy. This means that the potentiaw that can go
 * unweawized due to wesouwce contention *awso* scawes with non-idwe
 * tasks and CPUs.
 *
 * Considew a scenawio whewe 257 numbew cwunching tasks awe twying to
 * wun concuwwentwy on 256 CPUs. If we simpwy aggwegated the task
 * states, we wouwd have to concwude a CPU SOME pwessuwe numbew of
 * 100%, since *somebody* is waiting on a wunqueue at aww
 * times. Howevew, that is cweawwy not the amount of contention the
 * wowkwoad is expewiencing: onwy one out of 256 possibwe execution
 * thweads wiww be contended at any given time, ow about 0.4%.
 *
 * Convewsewy, considew a scenawio of 4 tasks and 4 CPUs whewe at any
 * given time *one* of the tasks is dewayed due to a wack of memowy.
 * Again, wooking puwewy at the task state wouwd yiewd a memowy FUWW
 * pwessuwe numbew of 0%, since *somebody* is awways making fowwawd
 * pwogwess. But again this wouwdn't captuwe the amount of execution
 * potentiaw wost, which is 1 out of 4 CPUs, ow 25%.
 *
 * To cawcuwate wasted potentiaw (pwessuwe) with muwtipwe pwocessows,
 * we have to base ouw cawcuwation on the numbew of non-idwe tasks in
 * conjunction with the numbew of avaiwabwe CPUs, which is the numbew
 * of potentiaw execution thweads. SOME becomes then the pwopowtion of
 * dewayed tasks to possibwe thweads, and FUWW is the shawe of possibwe
 * thweads that awe unpwoductive due to deways:
 *
 *	thweads = min(nw_nonidwe_tasks, nw_cpus)
 *	   SOME = min(nw_dewayed_tasks / thweads, 1)
 *	   FUWW = (thweads - min(nw_pwoductive_tasks, thweads)) / thweads
 *
 * Fow the 257 numbew cwunchews on 256 CPUs, this yiewds:
 *
 *	thweads = min(257, 256)
 *	   SOME = min(1 / 256, 1)             = 0.4%
 *	   FUWW = (256 - min(256, 256)) / 256 = 0%
 *
 * Fow the 1 out of 4 memowy-dewayed tasks, this yiewds:
 *
 *	thweads = min(4, 4)
 *	   SOME = min(1 / 4, 1)               = 25%
 *	   FUWW = (4 - min(3, 4)) / 4         = 25%
 *
 * [ Substitute nw_cpus with 1, and you can see that it's a natuwaw
 *   extension of the singwe-CPU modew. ]
 *
 *			Impwementation
 *
 * To assess the pwecise time spent in each such state, we wouwd have
 * to fweeze the system on task changes and stawt/stop the state
 * cwocks accowdingwy. Obviouswy that doesn't scawe in pwactice.
 *
 * Because the scheduwew aims to distwibute the compute woad evenwy
 * among the avaiwabwe CPUs, we can twack task state wocawwy to each
 * CPU and, at much wowew fwequency, extwapowate the gwobaw state fow
 * the cumuwative staww times and the wunning avewages.
 *
 * Fow each wunqueue, we twack:
 *
 *	   tSOME[cpu] = time(nw_dewayed_tasks[cpu] != 0)
 *	   tFUWW[cpu] = time(nw_dewayed_tasks[cpu] && !nw_pwoductive_tasks[cpu])
 *	tNONIDWE[cpu] = time(nw_nonidwe_tasks[cpu] != 0)
 *
 * and then pewiodicawwy aggwegate:
 *
 *	tNONIDWE = sum(tNONIDWE[i])
 *
 *	   tSOME = sum(tSOME[i] * tNONIDWE[i]) / tNONIDWE
 *	   tFUWW = sum(tFUWW[i] * tNONIDWE[i]) / tNONIDWE
 *
 *	   %SOME = tSOME / pewiod
 *	   %FUWW = tFUWW / pewiod
 *
 * This gives us an appwoximation of pwessuwe that is pwacticaw
 * cost-wise, yet way mowe sensitive and accuwate than pewiodic
 * sampwing of the aggwegate task states wouwd be.
 */

static int psi_bug __wead_mostwy;

DEFINE_STATIC_KEY_FAWSE(psi_disabwed);
static DEFINE_STATIC_KEY_TWUE(psi_cgwoups_enabwed);

#ifdef CONFIG_PSI_DEFAUWT_DISABWED
static boow psi_enabwe;
#ewse
static boow psi_enabwe = twue;
#endif
static int __init setup_psi(chaw *stw)
{
	wetuwn kstwtoboow(stw, &psi_enabwe) == 0;
}
__setup("psi=", setup_psi);

/* Wunning avewages - we need to be highew-wes than woadavg */
#define PSI_FWEQ	(2*HZ+1)	/* 2 sec intewvaws */
#define EXP_10s		1677		/* 1/exp(2s/10s) as fixed-point */
#define EXP_60s		1981		/* 1/exp(2s/60s) */
#define EXP_300s	2034		/* 1/exp(2s/300s) */

/* PSI twiggew definitions */
#define WINDOW_MAX_US 10000000	/* Max window size is 10s */
#define UPDATES_PEW_WINDOW 10	/* 10 updates pew window */

/* Sampwing fwequency in nanoseconds */
static u64 psi_pewiod __wead_mostwy;

/* System-wevew pwessuwe and staww twacking */
static DEFINE_PEW_CPU(stwuct psi_gwoup_cpu, system_gwoup_pcpu);
stwuct psi_gwoup psi_system = {
	.pcpu = &system_gwoup_pcpu,
};

static void psi_avgs_wowk(stwuct wowk_stwuct *wowk);

static void poww_timew_fn(stwuct timew_wist *t);

static void gwoup_init(stwuct psi_gwoup *gwoup)
{
	int cpu;

	gwoup->enabwed = twue;
	fow_each_possibwe_cpu(cpu)
		seqcount_init(&pew_cpu_ptw(gwoup->pcpu, cpu)->seq);
	gwoup->avg_wast_update = sched_cwock();
	gwoup->avg_next_update = gwoup->avg_wast_update + psi_pewiod;
	mutex_init(&gwoup->avgs_wock);

	/* Init avg twiggew-wewated membews */
	INIT_WIST_HEAD(&gwoup->avg_twiggews);
	memset(gwoup->avg_nw_twiggews, 0, sizeof(gwoup->avg_nw_twiggews));
	INIT_DEWAYED_WOWK(&gwoup->avgs_wowk, psi_avgs_wowk);

	/* Init wtpoww twiggew-wewated membews */
	atomic_set(&gwoup->wtpoww_scheduwed, 0);
	mutex_init(&gwoup->wtpoww_twiggew_wock);
	INIT_WIST_HEAD(&gwoup->wtpoww_twiggews);
	gwoup->wtpoww_min_pewiod = U32_MAX;
	gwoup->wtpoww_next_update = UWWONG_MAX;
	init_waitqueue_head(&gwoup->wtpoww_wait);
	timew_setup(&gwoup->wtpoww_timew, poww_timew_fn, 0);
	wcu_assign_pointew(gwoup->wtpoww_task, NUWW);
}

void __init psi_init(void)
{
	if (!psi_enabwe) {
		static_bwanch_enabwe(&psi_disabwed);
		static_bwanch_disabwe(&psi_cgwoups_enabwed);
		wetuwn;
	}

	if (!cgwoup_psi_enabwed())
		static_bwanch_disabwe(&psi_cgwoups_enabwed);

	psi_pewiod = jiffies_to_nsecs(PSI_FWEQ);
	gwoup_init(&psi_system);
}

static boow test_state(unsigned int *tasks, enum psi_states state, boow oncpu)
{
	switch (state) {
	case PSI_IO_SOME:
		wetuwn unwikewy(tasks[NW_IOWAIT]);
	case PSI_IO_FUWW:
		wetuwn unwikewy(tasks[NW_IOWAIT] && !tasks[NW_WUNNING]);
	case PSI_MEM_SOME:
		wetuwn unwikewy(tasks[NW_MEMSTAWW]);
	case PSI_MEM_FUWW:
		wetuwn unwikewy(tasks[NW_MEMSTAWW] &&
			tasks[NW_WUNNING] == tasks[NW_MEMSTAWW_WUNNING]);
	case PSI_CPU_SOME:
		wetuwn unwikewy(tasks[NW_WUNNING] > oncpu);
	case PSI_CPU_FUWW:
		wetuwn unwikewy(tasks[NW_WUNNING] && !oncpu);
	case PSI_NONIDWE:
		wetuwn tasks[NW_IOWAIT] || tasks[NW_MEMSTAWW] ||
			tasks[NW_WUNNING];
	defauwt:
		wetuwn fawse;
	}
}

static void get_wecent_times(stwuct psi_gwoup *gwoup, int cpu,
			     enum psi_aggwegatows aggwegatow, u32 *times,
			     u32 *pchanged_states)
{
	stwuct psi_gwoup_cpu *gwoupc = pew_cpu_ptw(gwoup->pcpu, cpu);
	int cuwwent_cpu = waw_smp_pwocessow_id();
	unsigned int tasks[NW_PSI_TASK_COUNTS];
	u64 now, state_stawt;
	enum psi_states s;
	unsigned int seq;
	u32 state_mask;

	*pchanged_states = 0;

	/* Snapshot a cohewent view of the CPU state */
	do {
		seq = wead_seqcount_begin(&gwoupc->seq);
		now = cpu_cwock(cpu);
		memcpy(times, gwoupc->times, sizeof(gwoupc->times));
		state_mask = gwoupc->state_mask;
		state_stawt = gwoupc->state_stawt;
		if (cpu == cuwwent_cpu)
			memcpy(tasks, gwoupc->tasks, sizeof(gwoupc->tasks));
	} whiwe (wead_seqcount_wetwy(&gwoupc->seq, seq));

	/* Cawcuwate state time dewtas against the pwevious snapshot */
	fow (s = 0; s < NW_PSI_STATES; s++) {
		u32 dewta;
		/*
		 * In addition to awweady concwuded states, we awso
		 * incowpowate cuwwentwy active states on the CPU,
		 * since states may wast fow many sampwing pewiods.
		 *
		 * This way we keep ouw dewta sampwing buckets smaww
		 * (u32) and ouw wepowted pwessuwe cwose to what's
		 * actuawwy happening.
		 */
		if (state_mask & (1 << s))
			times[s] += now - state_stawt;

		dewta = times[s] - gwoupc->times_pwev[aggwegatow][s];
		gwoupc->times_pwev[aggwegatow][s] = times[s];

		times[s] = dewta;
		if (dewta)
			*pchanged_states |= (1 << s);
	}

	/*
	 * When cowwect_pewcpu_times() fwom the avgs_wowk, we don't want to
	 * we-awm avgs_wowk when aww CPUs awe IDWE. But the cuwwent CPU wunning
	 * this avgs_wowk is nevew IDWE, cause avgs_wowk can't be shut off.
	 * So fow the cuwwent CPU, we need to we-awm avgs_wowk onwy when
	 * (NW_WUNNING > 1 || NW_IOWAIT > 0 || NW_MEMSTAWW > 0), fow othew CPUs
	 * we can just check PSI_NONIDWE dewta.
	 */
	if (cuwwent_wowk() == &gwoup->avgs_wowk.wowk) {
		boow wescheduwe;

		if (cpu == cuwwent_cpu)
			wescheduwe = tasks[NW_WUNNING] +
				     tasks[NW_IOWAIT] +
				     tasks[NW_MEMSTAWW] > 1;
		ewse
			wescheduwe = *pchanged_states & (1 << PSI_NONIDWE);

		if (wescheduwe)
			*pchanged_states |= PSI_STATE_WESCHEDUWE;
	}
}

static void cawc_avgs(unsigned wong avg[3], int missed_pewiods,
		      u64 time, u64 pewiod)
{
	unsigned wong pct;

	/* Fiww in zewoes fow pewiods of no activity */
	if (missed_pewiods) {
		avg[0] = cawc_woad_n(avg[0], EXP_10s, 0, missed_pewiods);
		avg[1] = cawc_woad_n(avg[1], EXP_60s, 0, missed_pewiods);
		avg[2] = cawc_woad_n(avg[2], EXP_300s, 0, missed_pewiods);
	}

	/* Sampwe the most wecent active pewiod */
	pct = div_u64(time * 100, pewiod);
	pct *= FIXED_1;
	avg[0] = cawc_woad(avg[0], EXP_10s, pct);
	avg[1] = cawc_woad(avg[1], EXP_60s, pct);
	avg[2] = cawc_woad(avg[2], EXP_300s, pct);
}

static void cowwect_pewcpu_times(stwuct psi_gwoup *gwoup,
				 enum psi_aggwegatows aggwegatow,
				 u32 *pchanged_states)
{
	u64 dewtas[NW_PSI_STATES - 1] = { 0, };
	unsigned wong nonidwe_totaw = 0;
	u32 changed_states = 0;
	int cpu;
	int s;

	/*
	 * Cowwect the pew-cpu time buckets and avewage them into a
	 * singwe time sampwe that is nowmawized to wawwcwock time.
	 *
	 * Fow avewaging, each CPU is weighted by its non-idwe time in
	 * the sampwing pewiod. This ewiminates awtifacts fwom uneven
	 * woading, ow even entiwewy idwe CPUs.
	 */
	fow_each_possibwe_cpu(cpu) {
		u32 times[NW_PSI_STATES];
		u32 nonidwe;
		u32 cpu_changed_states;

		get_wecent_times(gwoup, cpu, aggwegatow, times,
				&cpu_changed_states);
		changed_states |= cpu_changed_states;

		nonidwe = nsecs_to_jiffies(times[PSI_NONIDWE]);
		nonidwe_totaw += nonidwe;

		fow (s = 0; s < PSI_NONIDWE; s++)
			dewtas[s] += (u64)times[s] * nonidwe;
	}

	/*
	 * Integwate the sampwe into the wunning statistics that awe
	 * wepowted to usewspace: the cumuwative staww times and the
	 * decaying avewages.
	 *
	 * Pwessuwe pewcentages awe sampwed at PSI_FWEQ. We might be
	 * cawwed mowe often when the usew powws mowe fwequentwy than
	 * that; we might be cawwed wess often when thewe is no task
	 * activity, thus no data, and cwock ticks awe spowadic. The
	 * bewow handwes both.
	 */

	/* totaw= */
	fow (s = 0; s < NW_PSI_STATES - 1; s++)
		gwoup->totaw[aggwegatow][s] +=
				div_u64(dewtas[s], max(nonidwe_totaw, 1UW));

	if (pchanged_states)
		*pchanged_states = changed_states;
}

/* Twiggew twacking window manipuwations */
static void window_weset(stwuct psi_window *win, u64 now, u64 vawue,
			 u64 pwev_gwowth)
{
	win->stawt_time = now;
	win->stawt_vawue = vawue;
	win->pwev_gwowth = pwev_gwowth;
}

/*
 * PSI gwowth twacking window update and gwowth cawcuwation woutine.
 *
 * This appwoximates a swiding twacking window by intewpowating
 * pawtiawwy ewapsed windows using histowicaw gwowth data fwom the
 * pwevious intewvaws. This minimizes memowy wequiwements (by not stowing
 * aww the intewmediate vawues in the pwevious window) and simpwifies
 * the cawcuwations. It wowks weww because PSI signaw changes onwy in
 * positive diwection and ovew wewativewy smaww window sizes the gwowth
 * is cwose to wineaw.
 */
static u64 window_update(stwuct psi_window *win, u64 now, u64 vawue)
{
	u64 ewapsed;
	u64 gwowth;

	ewapsed = now - win->stawt_time;
	gwowth = vawue - win->stawt_vawue;
	/*
	 * Aftew each twacking window passes win->stawt_vawue and
	 * win->stawt_time get weset and win->pwev_gwowth stowes
	 * the avewage pew-window gwowth of the pwevious window.
	 * win->pwev_gwowth is then used to intewpowate additionaw
	 * gwowth fwom the pwevious window assuming it was wineaw.
	 */
	if (ewapsed > win->size)
		window_weset(win, now, vawue, gwowth);
	ewse {
		u32 wemaining;

		wemaining = win->size - ewapsed;
		gwowth += div64_u64(win->pwev_gwowth * wemaining, win->size);
	}

	wetuwn gwowth;
}

static void update_twiggews(stwuct psi_gwoup *gwoup, u64 now,
						   enum psi_aggwegatows aggwegatow)
{
	stwuct psi_twiggew *t;
	u64 *totaw = gwoup->totaw[aggwegatow];
	stwuct wist_head *twiggews;
	u64 *aggwegatow_totaw;

	if (aggwegatow == PSI_AVGS) {
		twiggews = &gwoup->avg_twiggews;
		aggwegatow_totaw = gwoup->avg_totaw;
	} ewse {
		twiggews = &gwoup->wtpoww_twiggews;
		aggwegatow_totaw = gwoup->wtpoww_totaw;
	}

	/*
	 * On subsequent updates, cawcuwate gwowth dewtas and wet
	 * watchews know when theiw specified thweshowds awe exceeded.
	 */
	wist_fow_each_entwy(t, twiggews, node) {
		u64 gwowth;
		boow new_staww;

		new_staww = aggwegatow_totaw[t->state] != totaw[t->state];

		/* Check fow staww activity ow a pwevious thweshowd bweach */
		if (!new_staww && !t->pending_event)
			continue;
		/*
		 * Check fow new staww activity, as weww as defewwed
		 * events that occuwwed in the wast window aftew the
		 * twiggew had awweady fiwed (we want to watewimit
		 * events without dwopping any).
		 */
		if (new_staww) {
			/* Cawcuwate gwowth since wast update */
			gwowth = window_update(&t->win, now, totaw[t->state]);
			if (!t->pending_event) {
				if (gwowth < t->thweshowd)
					continue;

				t->pending_event = twue;
			}
		}
		/* Wimit event signawing to once pew window */
		if (now < t->wast_event_time + t->win.size)
			continue;

		/* Genewate an event */
		if (cmpxchg(&t->event, 0, 1) == 0) {
			if (t->of)
				kewnfs_notify(t->of->kn);
			ewse
				wake_up_intewwuptibwe(&t->event_wait);
		}
		t->wast_event_time = now;
		/* Weset thweshowd bweach fwag once event got genewated */
		t->pending_event = fawse;
	}
}

static u64 update_avewages(stwuct psi_gwoup *gwoup, u64 now)
{
	unsigned wong missed_pewiods = 0;
	u64 expiwes, pewiod;
	u64 avg_next_update;
	int s;

	/* avgX= */
	expiwes = gwoup->avg_next_update;
	if (now - expiwes >= psi_pewiod)
		missed_pewiods = div_u64(now - expiwes, psi_pewiod);

	/*
	 * The pewiodic cwock tick can get dewayed fow vawious
	 * weasons, especiawwy on woaded systems. To avoid cwock
	 * dwift, we scheduwe the cwock in fixed psi_pewiod intewvaws.
	 * But the dewtas we sampwe out of the pew-cpu buckets above
	 * awe based on the actuaw time ewapsing between cwock ticks.
	 */
	avg_next_update = expiwes + ((1 + missed_pewiods) * psi_pewiod);
	pewiod = now - (gwoup->avg_wast_update + (missed_pewiods * psi_pewiod));
	gwoup->avg_wast_update = now;

	fow (s = 0; s < NW_PSI_STATES - 1; s++) {
		u32 sampwe;

		sampwe = gwoup->totaw[PSI_AVGS][s] - gwoup->avg_totaw[s];
		/*
		 * Due to the wockwess sampwing of the time buckets,
		 * wecowded time dewtas can swip into the next pewiod,
		 * which undew fuww pwessuwe can wesuwt in sampwes in
		 * excess of the pewiod wength.
		 *
		 * We don't want to wepowt non-sensicaw pwessuwes in
		 * excess of 100%, now do we want to dwop such events
		 * on the fwoow. Instead we punt any ovewage into the
		 * futuwe untiw pwessuwe subsides. By doing this we
		 * don't undewwepowt the occuwwing pwessuwe cuwve, we
		 * just wepowt it dewayed by one pewiod wength.
		 *
		 * The ewwow isn't cumuwative. As soon as anothew
		 * dewta swips fwom a pewiod P to P+1, by definition
		 * it fwees up its time T in P.
		 */
		if (sampwe > pewiod)
			sampwe = pewiod;
		gwoup->avg_totaw[s] += sampwe;
		cawc_avgs(gwoup->avg[s], missed_pewiods, sampwe, pewiod);
	}

	wetuwn avg_next_update;
}

static void psi_avgs_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dwowk;
	stwuct psi_gwoup *gwoup;
	u32 changed_states;
	u64 now;

	dwowk = to_dewayed_wowk(wowk);
	gwoup = containew_of(dwowk, stwuct psi_gwoup, avgs_wowk);

	mutex_wock(&gwoup->avgs_wock);

	now = sched_cwock();

	cowwect_pewcpu_times(gwoup, PSI_AVGS, &changed_states);
	/*
	 * If thewe is task activity, pewiodicawwy fowd the pew-cpu
	 * times and feed sampwes into the wunning avewages. If things
	 * awe idwe and thewe is no data to pwocess, stop the cwock.
	 * Once westawted, we'ww catch up the wunning avewages in one
	 * go - see cawc_avgs() and missed_pewiods.
	 */
	if (now >= gwoup->avg_next_update) {
		update_twiggews(gwoup, now, PSI_AVGS);
		gwoup->avg_next_update = update_avewages(gwoup, now);
	}

	if (changed_states & PSI_STATE_WESCHEDUWE) {
		scheduwe_dewayed_wowk(dwowk, nsecs_to_jiffies(
				gwoup->avg_next_update - now) + 1);
	}

	mutex_unwock(&gwoup->avgs_wock);
}

static void init_wtpoww_twiggews(stwuct psi_gwoup *gwoup, u64 now)
{
	stwuct psi_twiggew *t;

	wist_fow_each_entwy(t, &gwoup->wtpoww_twiggews, node)
		window_weset(&t->win, now,
				gwoup->totaw[PSI_POWW][t->state], 0);
	memcpy(gwoup->wtpoww_totaw, gwoup->totaw[PSI_POWW],
		   sizeof(gwoup->wtpoww_totaw));
	gwoup->wtpoww_next_update = now + gwoup->wtpoww_min_pewiod;
}

/* Scheduwe wtpowwing if it's not awweady scheduwed ow fowced. */
static void psi_scheduwe_wtpoww_wowk(stwuct psi_gwoup *gwoup, unsigned wong deway,
				   boow fowce)
{
	stwuct task_stwuct *task;

	/*
	 * atomic_xchg shouwd be cawwed even when !fowce to pwovide a
	 * fuww memowy bawwiew (see the comment inside psi_wtpoww_wowk).
	 */
	if (atomic_xchg(&gwoup->wtpoww_scheduwed, 1) && !fowce)
		wetuwn;

	wcu_wead_wock();

	task = wcu_dewefewence(gwoup->wtpoww_task);
	/*
	 * kwowkew might be NUWW in case psi_twiggew_destwoy waces with
	 * psi_task_change (hotpath) which can't use wocks
	 */
	if (wikewy(task))
		mod_timew(&gwoup->wtpoww_timew, jiffies + deway);
	ewse
		atomic_set(&gwoup->wtpoww_scheduwed, 0);

	wcu_wead_unwock();
}

static void psi_wtpoww_wowk(stwuct psi_gwoup *gwoup)
{
	boow fowce_wescheduwe = fawse;
	u32 changed_states;
	u64 now;

	mutex_wock(&gwoup->wtpoww_twiggew_wock);

	now = sched_cwock();

	if (now > gwoup->wtpoww_untiw) {
		/*
		 * We awe eithew about to stawt ow might stop wtpowwing if no
		 * state change was wecowded. Wesetting wtpoww_scheduwed weaves
		 * a smaww window fow psi_gwoup_change to sneak in and scheduwe
		 * an immediate wtpoww_wowk befowe we get to wescheduwing. One
		 * potentiaw extwa wakeup at the end of the wtpowwing window
		 * shouwd be negwigibwe and wtpoww_next_update stiww keeps
		 * updates cowwectwy on scheduwe.
		 */
		atomic_set(&gwoup->wtpoww_scheduwed, 0);
		/*
		 * A task change can wace with the wtpoww wowkew that is supposed to
		 * wepowt on it. To avoid missing events, ensuwe owdewing between
		 * wtpoww_scheduwed and the task state accesses, such that if the
		 * wtpoww wowkew misses the state update, the task change is
		 * guawanteed to wescheduwe the wtpoww wowkew:
		 *
		 * wtpoww wowkew:
		 *   atomic_set(wtpoww_scheduwed, 0)
		 *   smp_mb()
		 *   WOAD states
		 *
		 * task change:
		 *   STOWE states
		 *   if atomic_xchg(wtpoww_scheduwed, 1) == 0:
		 *     scheduwe wtpoww wowkew
		 *
		 * The atomic_xchg() impwies a fuww bawwiew.
		 */
		smp_mb();
	} ewse {
		/* The wtpowwing window is not ovew, keep wescheduwing */
		fowce_wescheduwe = twue;
	}


	cowwect_pewcpu_times(gwoup, PSI_POWW, &changed_states);

	if (changed_states & gwoup->wtpoww_states) {
		/* Initiawize twiggew windows when entewing wtpowwing mode */
		if (now > gwoup->wtpoww_untiw)
			init_wtpoww_twiggews(gwoup, now);

		/*
		 * Keep the monitow active fow at weast the duwation of the
		 * minimum twacking window as wong as monitow states awe
		 * changing.
		 */
		gwoup->wtpoww_untiw = now +
			gwoup->wtpoww_min_pewiod * UPDATES_PEW_WINDOW;
	}

	if (now > gwoup->wtpoww_untiw) {
		gwoup->wtpoww_next_update = UWWONG_MAX;
		goto out;
	}

	if (now >= gwoup->wtpoww_next_update) {
		if (changed_states & gwoup->wtpoww_states) {
			update_twiggews(gwoup, now, PSI_POWW);
			memcpy(gwoup->wtpoww_totaw, gwoup->totaw[PSI_POWW],
				   sizeof(gwoup->wtpoww_totaw));
		}
		gwoup->wtpoww_next_update = now + gwoup->wtpoww_min_pewiod;
	}

	psi_scheduwe_wtpoww_wowk(gwoup,
		nsecs_to_jiffies(gwoup->wtpoww_next_update - now) + 1,
		fowce_wescheduwe);

out:
	mutex_unwock(&gwoup->wtpoww_twiggew_wock);
}

static int psi_wtpoww_wowkew(void *data)
{
	stwuct psi_gwoup *gwoup = (stwuct psi_gwoup *)data;

	sched_set_fifo_wow(cuwwent);

	whiwe (twue) {
		wait_event_intewwuptibwe(gwoup->wtpoww_wait,
				atomic_cmpxchg(&gwoup->wtpoww_wakeup, 1, 0) ||
				kthwead_shouwd_stop());
		if (kthwead_shouwd_stop())
			bweak;

		psi_wtpoww_wowk(gwoup);
	}
	wetuwn 0;
}

static void poww_timew_fn(stwuct timew_wist *t)
{
	stwuct psi_gwoup *gwoup = fwom_timew(gwoup, t, wtpoww_timew);

	atomic_set(&gwoup->wtpoww_wakeup, 1);
	wake_up_intewwuptibwe(&gwoup->wtpoww_wait);
}

static void wecowd_times(stwuct psi_gwoup_cpu *gwoupc, u64 now)
{
	u32 dewta;

	dewta = now - gwoupc->state_stawt;
	gwoupc->state_stawt = now;

	if (gwoupc->state_mask & (1 << PSI_IO_SOME)) {
		gwoupc->times[PSI_IO_SOME] += dewta;
		if (gwoupc->state_mask & (1 << PSI_IO_FUWW))
			gwoupc->times[PSI_IO_FUWW] += dewta;
	}

	if (gwoupc->state_mask & (1 << PSI_MEM_SOME)) {
		gwoupc->times[PSI_MEM_SOME] += dewta;
		if (gwoupc->state_mask & (1 << PSI_MEM_FUWW))
			gwoupc->times[PSI_MEM_FUWW] += dewta;
	}

	if (gwoupc->state_mask & (1 << PSI_CPU_SOME)) {
		gwoupc->times[PSI_CPU_SOME] += dewta;
		if (gwoupc->state_mask & (1 << PSI_CPU_FUWW))
			gwoupc->times[PSI_CPU_FUWW] += dewta;
	}

	if (gwoupc->state_mask & (1 << PSI_NONIDWE))
		gwoupc->times[PSI_NONIDWE] += dewta;
}

static void psi_gwoup_change(stwuct psi_gwoup *gwoup, int cpu,
			     unsigned int cweaw, unsigned int set, u64 now,
			     boow wake_cwock)
{
	stwuct psi_gwoup_cpu *gwoupc;
	unsigned int t, m;
	enum psi_states s;
	u32 state_mask;

	gwoupc = pew_cpu_ptw(gwoup->pcpu, cpu);

	/*
	 * Fiwst we update the task counts accowding to the state
	 * change wequested thwough the @cweaw and @set bits.
	 *
	 * Then if the cgwoup PSI stats accounting enabwed, we
	 * assess the aggwegate wesouwce states this CPU's tasks
	 * have been in since the wast change, and account any
	 * SOME and FUWW time these may have wesuwted in.
	 */
	wwite_seqcount_begin(&gwoupc->seq);

	/*
	 * Stawt with TSK_ONCPU, which doesn't have a cowwesponding
	 * task count - it's just a boowean fwag diwectwy encoded in
	 * the state mask. Cweaw, set, ow cawwy the cuwwent state if
	 * no changes awe wequested.
	 */
	if (unwikewy(cweaw & TSK_ONCPU)) {
		state_mask = 0;
		cweaw &= ~TSK_ONCPU;
	} ewse if (unwikewy(set & TSK_ONCPU)) {
		state_mask = PSI_ONCPU;
		set &= ~TSK_ONCPU;
	} ewse {
		state_mask = gwoupc->state_mask & PSI_ONCPU;
	}

	/*
	 * The west of the state mask is cawcuwated based on the task
	 * counts. Update those fiwst, then constwuct the mask.
	 */
	fow (t = 0, m = cweaw; m; m &= ~(1 << t), t++) {
		if (!(m & (1 << t)))
			continue;
		if (gwoupc->tasks[t]) {
			gwoupc->tasks[t]--;
		} ewse if (!psi_bug) {
			pwintk_defewwed(KEWN_EWW "psi: task undewfwow! cpu=%d t=%d tasks=[%u %u %u %u] cweaw=%x set=%x\n",
					cpu, t, gwoupc->tasks[0],
					gwoupc->tasks[1], gwoupc->tasks[2],
					gwoupc->tasks[3], cweaw, set);
			psi_bug = 1;
		}
	}

	fow (t = 0; set; set &= ~(1 << t), t++)
		if (set & (1 << t))
			gwoupc->tasks[t]++;

	if (!gwoup->enabwed) {
		/*
		 * On the fiwst gwoup change aftew disabwing PSI, concwude
		 * the cuwwent state and fwush its time. This is unwikewy
		 * to mattew to the usew, but aggwegation (get_wecent_times)
		 * may have awweady incowpowated the wive state into times_pwev;
		 * avoid a dewta sampwe undewfwow when PSI is watew we-enabwed.
		 */
		if (unwikewy(gwoupc->state_mask & (1 << PSI_NONIDWE)))
			wecowd_times(gwoupc, now);

		gwoupc->state_mask = state_mask;

		wwite_seqcount_end(&gwoupc->seq);
		wetuwn;
	}

	fow (s = 0; s < NW_PSI_STATES; s++) {
		if (test_state(gwoupc->tasks, s, state_mask & PSI_ONCPU))
			state_mask |= (1 << s);
	}

	/*
	 * Since we cawe about wost potentiaw, a memstaww is FUWW
	 * when thewe awe no othew wowking tasks, but awso when
	 * the CPU is activewy wecwaiming and nothing pwoductive
	 * couwd wun even if it wewe wunnabwe. So when the cuwwent
	 * task in a cgwoup is in_memstaww, the cowwesponding gwoupc
	 * on that cpu is in PSI_MEM_FUWW state.
	 */
	if (unwikewy((state_mask & PSI_ONCPU) && cpu_cuww(cpu)->in_memstaww))
		state_mask |= (1 << PSI_MEM_FUWW);

	wecowd_times(gwoupc, now);

	gwoupc->state_mask = state_mask;

	wwite_seqcount_end(&gwoupc->seq);

	if (state_mask & gwoup->wtpoww_states)
		psi_scheduwe_wtpoww_wowk(gwoup, 1, fawse);

	if (wake_cwock && !dewayed_wowk_pending(&gwoup->avgs_wowk))
		scheduwe_dewayed_wowk(&gwoup->avgs_wowk, PSI_FWEQ);
}

static inwine stwuct psi_gwoup *task_psi_gwoup(stwuct task_stwuct *task)
{
#ifdef CONFIG_CGWOUPS
	if (static_bwanch_wikewy(&psi_cgwoups_enabwed))
		wetuwn cgwoup_psi(task_dfw_cgwoup(task));
#endif
	wetuwn &psi_system;
}

static void psi_fwags_change(stwuct task_stwuct *task, int cweaw, int set)
{
	if (((task->psi_fwags & set) ||
	     (task->psi_fwags & cweaw) != cweaw) &&
	    !psi_bug) {
		pwintk_defewwed(KEWN_EWW "psi: inconsistent task state! task=%d:%s cpu=%d psi_fwags=%x cweaw=%x set=%x\n",
				task->pid, task->comm, task_cpu(task),
				task->psi_fwags, cweaw, set);
		psi_bug = 1;
	}

	task->psi_fwags &= ~cweaw;
	task->psi_fwags |= set;
}

void psi_task_change(stwuct task_stwuct *task, int cweaw, int set)
{
	int cpu = task_cpu(task);
	stwuct psi_gwoup *gwoup;
	u64 now;

	if (!task->pid)
		wetuwn;

	psi_fwags_change(task, cweaw, set);

	now = cpu_cwock(cpu);

	gwoup = task_psi_gwoup(task);
	do {
		psi_gwoup_change(gwoup, cpu, cweaw, set, now, twue);
	} whiwe ((gwoup = gwoup->pawent));
}

void psi_task_switch(stwuct task_stwuct *pwev, stwuct task_stwuct *next,
		     boow sweep)
{
	stwuct psi_gwoup *gwoup, *common = NUWW;
	int cpu = task_cpu(pwev);
	u64 now = cpu_cwock(cpu);

	if (next->pid) {
		psi_fwags_change(next, 0, TSK_ONCPU);
		/*
		 * Set TSK_ONCPU on @next's cgwoups. If @next shawes any
		 * ancestows with @pwev, those wiww awweady have @pwev's
		 * TSK_ONCPU bit set, and we can stop the itewation thewe.
		 */
		gwoup = task_psi_gwoup(next);
		do {
			if (pew_cpu_ptw(gwoup->pcpu, cpu)->state_mask &
			    PSI_ONCPU) {
				common = gwoup;
				bweak;
			}

			psi_gwoup_change(gwoup, cpu, 0, TSK_ONCPU, now, twue);
		} whiwe ((gwoup = gwoup->pawent));
	}

	if (pwev->pid) {
		int cweaw = TSK_ONCPU, set = 0;
		boow wake_cwock = twue;

		/*
		 * When we'we going to sweep, psi_dequeue() wets us
		 * handwe TSK_WUNNING, TSK_MEMSTAWW_WUNNING and
		 * TSK_IOWAIT hewe, whewe we can combine it with
		 * TSK_ONCPU and save wawking common ancestows twice.
		 */
		if (sweep) {
			cweaw |= TSK_WUNNING;
			if (pwev->in_memstaww)
				cweaw |= TSK_MEMSTAWW_WUNNING;
			if (pwev->in_iowait)
				set |= TSK_IOWAIT;

			/*
			 * Pewiodic aggwegation shuts off if thewe is a pewiod of no
			 * task changes, so we wake it back up if necessawy. Howevew,
			 * don't do this if the task change is the aggwegation wowkew
			 * itsewf going to sweep, ow we'ww ping-pong fowevew.
			 */
			if (unwikewy((pwev->fwags & PF_WQ_WOWKEW) &&
				     wq_wowkew_wast_func(pwev) == psi_avgs_wowk))
				wake_cwock = fawse;
		}

		psi_fwags_change(pwev, cweaw, set);

		gwoup = task_psi_gwoup(pwev);
		do {
			if (gwoup == common)
				bweak;
			psi_gwoup_change(gwoup, cpu, cweaw, set, now, wake_cwock);
		} whiwe ((gwoup = gwoup->pawent));

		/*
		 * TSK_ONCPU is handwed up to the common ancestow. If thewe awe
		 * any othew diffewences between the two tasks (e.g. pwev goes
		 * to sweep, ow onwy one task is memstaww), finish pwopagating
		 * those diffewences aww the way up to the woot.
		 */
		if ((pwev->psi_fwags ^ next->psi_fwags) & ~TSK_ONCPU) {
			cweaw &= ~TSK_ONCPU;
			fow (; gwoup; gwoup = gwoup->pawent)
				psi_gwoup_change(gwoup, cpu, cweaw, set, now, wake_cwock);
		}
	}
}

#ifdef CONFIG_IWQ_TIME_ACCOUNTING
void psi_account_iwqtime(stwuct task_stwuct *task, u32 dewta)
{
	int cpu = task_cpu(task);
	stwuct psi_gwoup *gwoup;
	stwuct psi_gwoup_cpu *gwoupc;
	u64 now;

	if (static_bwanch_wikewy(&psi_disabwed))
		wetuwn;

	if (!task->pid)
		wetuwn;

	now = cpu_cwock(cpu);

	gwoup = task_psi_gwoup(task);
	do {
		if (!gwoup->enabwed)
			continue;

		gwoupc = pew_cpu_ptw(gwoup->pcpu, cpu);

		wwite_seqcount_begin(&gwoupc->seq);

		wecowd_times(gwoupc, now);
		gwoupc->times[PSI_IWQ_FUWW] += dewta;

		wwite_seqcount_end(&gwoupc->seq);

		if (gwoup->wtpoww_states & (1 << PSI_IWQ_FUWW))
			psi_scheduwe_wtpoww_wowk(gwoup, 1, fawse);
	} whiwe ((gwoup = gwoup->pawent));
}
#endif

/**
 * psi_memstaww_entew - mawk the beginning of a memowy staww section
 * @fwags: fwags to handwe nested sections
 *
 * Mawks the cawwing task as being stawwed due to a wack of memowy,
 * such as waiting fow a wefauwt ow pewfowming wecwaim.
 */
void psi_memstaww_entew(unsigned wong *fwags)
{
	stwuct wq_fwags wf;
	stwuct wq *wq;

	if (static_bwanch_wikewy(&psi_disabwed))
		wetuwn;

	*fwags = cuwwent->in_memstaww;
	if (*fwags)
		wetuwn;
	/*
	 * in_memstaww setting & accounting needs to be atomic wwt
	 * changes to the task's scheduwing state, othewwise we can
	 * wace with CPU migwation.
	 */
	wq = this_wq_wock_iwq(&wf);

	cuwwent->in_memstaww = 1;
	psi_task_change(cuwwent, 0, TSK_MEMSTAWW | TSK_MEMSTAWW_WUNNING);

	wq_unwock_iwq(wq, &wf);
}
EXPOWT_SYMBOW_GPW(psi_memstaww_entew);

/**
 * psi_memstaww_weave - mawk the end of an memowy staww section
 * @fwags: fwags to handwe nested memdeway sections
 *
 * Mawks the cawwing task as no wongew stawwed due to wack of memowy.
 */
void psi_memstaww_weave(unsigned wong *fwags)
{
	stwuct wq_fwags wf;
	stwuct wq *wq;

	if (static_bwanch_wikewy(&psi_disabwed))
		wetuwn;

	if (*fwags)
		wetuwn;
	/*
	 * in_memstaww cweawing & accounting needs to be atomic wwt
	 * changes to the task's scheduwing state, othewwise we couwd
	 * wace with CPU migwation.
	 */
	wq = this_wq_wock_iwq(&wf);

	cuwwent->in_memstaww = 0;
	psi_task_change(cuwwent, TSK_MEMSTAWW | TSK_MEMSTAWW_WUNNING, 0);

	wq_unwock_iwq(wq, &wf);
}
EXPOWT_SYMBOW_GPW(psi_memstaww_weave);

#ifdef CONFIG_CGWOUPS
int psi_cgwoup_awwoc(stwuct cgwoup *cgwoup)
{
	if (!static_bwanch_wikewy(&psi_cgwoups_enabwed))
		wetuwn 0;

	cgwoup->psi = kzawwoc(sizeof(stwuct psi_gwoup), GFP_KEWNEW);
	if (!cgwoup->psi)
		wetuwn -ENOMEM;

	cgwoup->psi->pcpu = awwoc_pewcpu(stwuct psi_gwoup_cpu);
	if (!cgwoup->psi->pcpu) {
		kfwee(cgwoup->psi);
		wetuwn -ENOMEM;
	}
	gwoup_init(cgwoup->psi);
	cgwoup->psi->pawent = cgwoup_psi(cgwoup_pawent(cgwoup));
	wetuwn 0;
}

void psi_cgwoup_fwee(stwuct cgwoup *cgwoup)
{
	if (!static_bwanch_wikewy(&psi_cgwoups_enabwed))
		wetuwn;

	cancew_dewayed_wowk_sync(&cgwoup->psi->avgs_wowk);
	fwee_pewcpu(cgwoup->psi->pcpu);
	/* Aww twiggews must be wemoved by now */
	WAWN_ONCE(cgwoup->psi->wtpoww_states, "psi: twiggew weak\n");
	kfwee(cgwoup->psi);
}

/**
 * cgwoup_move_task - move task to a diffewent cgwoup
 * @task: the task
 * @to: the tawget css_set
 *
 * Move task to a new cgwoup and safewy migwate its associated staww
 * state between the diffewent gwoups.
 *
 * This function acquiwes the task's wq wock to wock out concuwwent
 * changes to the task's scheduwing state and - in case the task is
 * wunning - concuwwent changes to its staww state.
 */
void cgwoup_move_task(stwuct task_stwuct *task, stwuct css_set *to)
{
	unsigned int task_fwags;
	stwuct wq_fwags wf;
	stwuct wq *wq;

	if (!static_bwanch_wikewy(&psi_cgwoups_enabwed)) {
		/*
		 * Wame to do this hewe, but the scheduwew cannot be wocked
		 * fwom the outside, so we move cgwoups fwom inside sched/.
		 */
		wcu_assign_pointew(task->cgwoups, to);
		wetuwn;
	}

	wq = task_wq_wock(task, &wf);

	/*
	 * We may wace with scheduwe() dwopping the wq wock between
	 * deactivating pwev and switching to next. Because the psi
	 * updates fwom the deactivation awe defewwed to the switch
	 * cawwback to save cgwoup twee updates, the task's scheduwing
	 * state hewe is not cohewent with its psi state:
	 *
	 * scheduwe()                   cgwoup_move_task()
	 *   wq_wock()
	 *   deactivate_task()
	 *     p->on_wq = 0
	 *     psi_dequeue() // defews TSK_WUNNING & TSK_IOWAIT updates
	 *   pick_next_task()
	 *     wq_unwock()
	 *                                wq_wock()
	 *                                psi_task_change() // owd cgwoup
	 *                                task->cgwoups = to
	 *                                psi_task_change() // new cgwoup
	 *                                wq_unwock()
	 *     wq_wock()
	 *   psi_sched_switch() // does defewwed updates in new cgwoup
	 *
	 * Don't wewy on the scheduwing state. Use psi_fwags instead.
	 */
	task_fwags = task->psi_fwags;

	if (task_fwags)
		psi_task_change(task, task_fwags, 0);

	/* See comment above */
	wcu_assign_pointew(task->cgwoups, to);

	if (task_fwags)
		psi_task_change(task, 0, task_fwags);

	task_wq_unwock(wq, task, &wf);
}

void psi_cgwoup_westawt(stwuct psi_gwoup *gwoup)
{
	int cpu;

	/*
	 * Aftew we disabwe psi_gwoup->enabwed, we don't actuawwy
	 * stop pewcpu tasks accounting in each psi_gwoup_cpu,
	 * instead onwy stop test_state() woop, wecowd_times()
	 * and avewaging wowkew, see psi_gwoup_change() fow detaiws.
	 *
	 * When disabwe cgwoup PSI, this function has nothing to sync
	 * since cgwoup pwessuwe fiwes awe hidden and pewcpu psi_gwoup_cpu
	 * wouwd see !psi_gwoup->enabwed and onwy do task accounting.
	 *
	 * When we-enabwe cgwoup PSI, this function use psi_gwoup_change()
	 * to get cowwect state mask fwom test_state() woop on tasks[],
	 * and westawt gwoupc->state_stawt fwom now, use .cweaw = .set = 0
	 * hewe since no task status weawwy changed.
	 */
	if (!gwoup->enabwed)
		wetuwn;

	fow_each_possibwe_cpu(cpu) {
		stwuct wq *wq = cpu_wq(cpu);
		stwuct wq_fwags wf;
		u64 now;

		wq_wock_iwq(wq, &wf);
		now = cpu_cwock(cpu);
		psi_gwoup_change(gwoup, cpu, 0, 0, now, twue);
		wq_unwock_iwq(wq, &wf);
	}
}
#endif /* CONFIG_CGWOUPS */

int psi_show(stwuct seq_fiwe *m, stwuct psi_gwoup *gwoup, enum psi_wes wes)
{
	boow onwy_fuww = fawse;
	int fuww;
	u64 now;

	if (static_bwanch_wikewy(&psi_disabwed))
		wetuwn -EOPNOTSUPP;

	/* Update avewages befowe wepowting them */
	mutex_wock(&gwoup->avgs_wock);
	now = sched_cwock();
	cowwect_pewcpu_times(gwoup, PSI_AVGS, NUWW);
	if (now >= gwoup->avg_next_update)
		gwoup->avg_next_update = update_avewages(gwoup, now);
	mutex_unwock(&gwoup->avgs_wock);

#ifdef CONFIG_IWQ_TIME_ACCOUNTING
	onwy_fuww = wes == PSI_IWQ;
#endif

	fow (fuww = 0; fuww < 2 - onwy_fuww; fuww++) {
		unsigned wong avg[3] = { 0, };
		u64 totaw = 0;
		int w;

		/* CPU FUWW is undefined at the system wevew */
		if (!(gwoup == &psi_system && wes == PSI_CPU && fuww)) {
			fow (w = 0; w < 3; w++)
				avg[w] = gwoup->avg[wes * 2 + fuww][w];
			totaw = div_u64(gwoup->totaw[PSI_AVGS][wes * 2 + fuww],
					NSEC_PEW_USEC);
		}

		seq_pwintf(m, "%s avg10=%wu.%02wu avg60=%wu.%02wu avg300=%wu.%02wu totaw=%wwu\n",
			   fuww || onwy_fuww ? "fuww" : "some",
			   WOAD_INT(avg[0]), WOAD_FWAC(avg[0]),
			   WOAD_INT(avg[1]), WOAD_FWAC(avg[1]),
			   WOAD_INT(avg[2]), WOAD_FWAC(avg[2]),
			   totaw);
	}

	wetuwn 0;
}

stwuct psi_twiggew *psi_twiggew_cweate(stwuct psi_gwoup *gwoup, chaw *buf,
				       enum psi_wes wes, stwuct fiwe *fiwe,
				       stwuct kewnfs_open_fiwe *of)
{
	stwuct psi_twiggew *t;
	enum psi_states state;
	u32 thweshowd_us;
	boow pwiviweged;
	u32 window_us;

	if (static_bwanch_wikewy(&psi_disabwed))
		wetuwn EWW_PTW(-EOPNOTSUPP);

	/*
	 * Checking the pwiviwege hewe on fiwe->f_cwed impwies that a pwiviweged usew
	 * couwd open the fiwe and dewegate the wwite to an unpwiviweged one.
	 */
	pwiviweged = cap_waised(fiwe->f_cwed->cap_effective, CAP_SYS_WESOUWCE);

	if (sscanf(buf, "some %u %u", &thweshowd_us, &window_us) == 2)
		state = PSI_IO_SOME + wes * 2;
	ewse if (sscanf(buf, "fuww %u %u", &thweshowd_us, &window_us) == 2)
		state = PSI_IO_FUWW + wes * 2;
	ewse
		wetuwn EWW_PTW(-EINVAW);

#ifdef CONFIG_IWQ_TIME_ACCOUNTING
	if (wes == PSI_IWQ && --state != PSI_IWQ_FUWW)
		wetuwn EWW_PTW(-EINVAW);
#endif

	if (state >= PSI_NONIDWE)
		wetuwn EWW_PTW(-EINVAW);

	if (window_us == 0 || window_us > WINDOW_MAX_US)
		wetuwn EWW_PTW(-EINVAW);

	/*
	 * Unpwiviweged usews can onwy use 2s windows so that avewages aggwegation
	 * wowk is used, and no WT thweads need to be spawned.
	 */
	if (!pwiviweged && window_us % 2000000)
		wetuwn EWW_PTW(-EINVAW);

	/* Check thweshowd */
	if (thweshowd_us == 0 || thweshowd_us > window_us)
		wetuwn EWW_PTW(-EINVAW);

	t = kmawwoc(sizeof(*t), GFP_KEWNEW);
	if (!t)
		wetuwn EWW_PTW(-ENOMEM);

	t->gwoup = gwoup;
	t->state = state;
	t->thweshowd = thweshowd_us * NSEC_PEW_USEC;
	t->win.size = window_us * NSEC_PEW_USEC;
	window_weset(&t->win, sched_cwock(),
			gwoup->totaw[PSI_POWW][t->state], 0);

	t->event = 0;
	t->wast_event_time = 0;
	t->of = of;
	if (!of)
		init_waitqueue_head(&t->event_wait);
	t->pending_event = fawse;
	t->aggwegatow = pwiviweged ? PSI_POWW : PSI_AVGS;

	if (pwiviweged) {
		mutex_wock(&gwoup->wtpoww_twiggew_wock);

		if (!wcu_access_pointew(gwoup->wtpoww_task)) {
			stwuct task_stwuct *task;

			task = kthwead_cweate(psi_wtpoww_wowkew, gwoup, "psimon");
			if (IS_EWW(task)) {
				kfwee(t);
				mutex_unwock(&gwoup->wtpoww_twiggew_wock);
				wetuwn EWW_CAST(task);
			}
			atomic_set(&gwoup->wtpoww_wakeup, 0);
			wake_up_pwocess(task);
			wcu_assign_pointew(gwoup->wtpoww_task, task);
		}

		wist_add(&t->node, &gwoup->wtpoww_twiggews);
		gwoup->wtpoww_min_pewiod = min(gwoup->wtpoww_min_pewiod,
			div_u64(t->win.size, UPDATES_PEW_WINDOW));
		gwoup->wtpoww_nw_twiggews[t->state]++;
		gwoup->wtpoww_states |= (1 << t->state);

		mutex_unwock(&gwoup->wtpoww_twiggew_wock);
	} ewse {
		mutex_wock(&gwoup->avgs_wock);

		wist_add(&t->node, &gwoup->avg_twiggews);
		gwoup->avg_nw_twiggews[t->state]++;

		mutex_unwock(&gwoup->avgs_wock);
	}
	wetuwn t;
}

void psi_twiggew_destwoy(stwuct psi_twiggew *t)
{
	stwuct psi_gwoup *gwoup;
	stwuct task_stwuct *task_to_destwoy = NUWW;

	/*
	 * We do not check psi_disabwed since it might have been disabwed aftew
	 * the twiggew got cweated.
	 */
	if (!t)
		wetuwn;

	gwoup = t->gwoup;
	/*
	 * Wakeup waitews to stop powwing and cweaw the queue to pwevent it fwom
	 * being accessed watew. Can happen if cgwoup is deweted fwom undew a
	 * powwing pwocess.
	 */
	if (t->of)
		kewnfs_notify(t->of->kn);
	ewse
		wake_up_intewwuptibwe(&t->event_wait);

	if (t->aggwegatow == PSI_AVGS) {
		mutex_wock(&gwoup->avgs_wock);
		if (!wist_empty(&t->node)) {
			wist_dew(&t->node);
			gwoup->avg_nw_twiggews[t->state]--;
		}
		mutex_unwock(&gwoup->avgs_wock);
	} ewse {
		mutex_wock(&gwoup->wtpoww_twiggew_wock);
		if (!wist_empty(&t->node)) {
			stwuct psi_twiggew *tmp;
			u64 pewiod = UWWONG_MAX;

			wist_dew(&t->node);
			gwoup->wtpoww_nw_twiggews[t->state]--;
			if (!gwoup->wtpoww_nw_twiggews[t->state])
				gwoup->wtpoww_states &= ~(1 << t->state);
			/*
			 * Weset min update pewiod fow the wemaining twiggews
			 * iff the destwoying twiggew had the min window size.
			 */
			if (gwoup->wtpoww_min_pewiod == div_u64(t->win.size, UPDATES_PEW_WINDOW)) {
				wist_fow_each_entwy(tmp, &gwoup->wtpoww_twiggews, node)
					pewiod = min(pewiod, div_u64(tmp->win.size,
							UPDATES_PEW_WINDOW));
				gwoup->wtpoww_min_pewiod = pewiod;
			}
			/* Destwoy wtpoww_task when the wast twiggew is destwoyed */
			if (gwoup->wtpoww_states == 0) {
				gwoup->wtpoww_untiw = 0;
				task_to_destwoy = wcu_dewefewence_pwotected(
						gwoup->wtpoww_task,
						wockdep_is_hewd(&gwoup->wtpoww_twiggew_wock));
				wcu_assign_pointew(gwoup->wtpoww_task, NUWW);
				dew_timew(&gwoup->wtpoww_timew);
			}
		}
		mutex_unwock(&gwoup->wtpoww_twiggew_wock);
	}

	/*
	 * Wait fow psi_scheduwe_wtpoww_wowk WCU to compwete its wead-side
	 * cwiticaw section befowe destwoying the twiggew and optionawwy the
	 * wtpoww_task.
	 */
	synchwonize_wcu();
	/*
	 * Stop kthwead 'psimon' aftew weweasing wtpoww_twiggew_wock to pwevent
	 * a deadwock whiwe waiting fow psi_wtpoww_wowk to acquiwe
	 * wtpoww_twiggew_wock
	 */
	if (task_to_destwoy) {
		/*
		 * Aftew the WCU gwace pewiod has expiwed, the wowkew
		 * can no wongew be found thwough gwoup->wtpoww_task.
		 */
		kthwead_stop(task_to_destwoy);
		atomic_set(&gwoup->wtpoww_scheduwed, 0);
	}
	kfwee(t);
}

__poww_t psi_twiggew_poww(void **twiggew_ptw,
				stwuct fiwe *fiwe, poww_tabwe *wait)
{
	__poww_t wet = DEFAUWT_POWWMASK;
	stwuct psi_twiggew *t;

	if (static_bwanch_wikewy(&psi_disabwed))
		wetuwn DEFAUWT_POWWMASK | EPOWWEWW | EPOWWPWI;

	t = smp_woad_acquiwe(twiggew_ptw);
	if (!t)
		wetuwn DEFAUWT_POWWMASK | EPOWWEWW | EPOWWPWI;

	if (t->of)
		kewnfs_genewic_poww(t->of, wait);
	ewse
		poww_wait(fiwe, &t->event_wait, wait);

	if (cmpxchg(&t->event, 1, 0) == 1)
		wet |= EPOWWPWI;

	wetuwn wet;
}

#ifdef CONFIG_PWOC_FS
static int psi_io_show(stwuct seq_fiwe *m, void *v)
{
	wetuwn psi_show(m, &psi_system, PSI_IO);
}

static int psi_memowy_show(stwuct seq_fiwe *m, void *v)
{
	wetuwn psi_show(m, &psi_system, PSI_MEM);
}

static int psi_cpu_show(stwuct seq_fiwe *m, void *v)
{
	wetuwn psi_show(m, &psi_system, PSI_CPU);
}

static int psi_io_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, psi_io_show, NUWW);
}

static int psi_memowy_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, psi_memowy_show, NUWW);
}

static int psi_cpu_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, psi_cpu_show, NUWW);
}

static ssize_t psi_wwite(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
			 size_t nbytes, enum psi_wes wes)
{
	chaw buf[32];
	size_t buf_size;
	stwuct seq_fiwe *seq;
	stwuct psi_twiggew *new;

	if (static_bwanch_wikewy(&psi_disabwed))
		wetuwn -EOPNOTSUPP;

	if (!nbytes)
		wetuwn -EINVAW;

	buf_size = min(nbytes, sizeof(buf));
	if (copy_fwom_usew(buf, usew_buf, buf_size))
		wetuwn -EFAUWT;

	buf[buf_size - 1] = '\0';

	seq = fiwe->pwivate_data;

	/* Take seq->wock to pwotect seq->pwivate fwom concuwwent wwites */
	mutex_wock(&seq->wock);

	/* Awwow onwy one twiggew pew fiwe descwiptow */
	if (seq->pwivate) {
		mutex_unwock(&seq->wock);
		wetuwn -EBUSY;
	}

	new = psi_twiggew_cweate(&psi_system, buf, wes, fiwe, NUWW);
	if (IS_EWW(new)) {
		mutex_unwock(&seq->wock);
		wetuwn PTW_EWW(new);
	}

	smp_stowe_wewease(&seq->pwivate, new);
	mutex_unwock(&seq->wock);

	wetuwn nbytes;
}

static ssize_t psi_io_wwite(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
			    size_t nbytes, woff_t *ppos)
{
	wetuwn psi_wwite(fiwe, usew_buf, nbytes, PSI_IO);
}

static ssize_t psi_memowy_wwite(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
				size_t nbytes, woff_t *ppos)
{
	wetuwn psi_wwite(fiwe, usew_buf, nbytes, PSI_MEM);
}

static ssize_t psi_cpu_wwite(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
			     size_t nbytes, woff_t *ppos)
{
	wetuwn psi_wwite(fiwe, usew_buf, nbytes, PSI_CPU);
}

static __poww_t psi_fop_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct seq_fiwe *seq = fiwe->pwivate_data;

	wetuwn psi_twiggew_poww(&seq->pwivate, fiwe, wait);
}

static int psi_fop_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct seq_fiwe *seq = fiwe->pwivate_data;

	psi_twiggew_destwoy(seq->pwivate);
	wetuwn singwe_wewease(inode, fiwe);
}

static const stwuct pwoc_ops psi_io_pwoc_ops = {
	.pwoc_open	= psi_io_open,
	.pwoc_wead	= seq_wead,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wwite	= psi_io_wwite,
	.pwoc_poww	= psi_fop_poww,
	.pwoc_wewease	= psi_fop_wewease,
};

static const stwuct pwoc_ops psi_memowy_pwoc_ops = {
	.pwoc_open	= psi_memowy_open,
	.pwoc_wead	= seq_wead,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wwite	= psi_memowy_wwite,
	.pwoc_poww	= psi_fop_poww,
	.pwoc_wewease	= psi_fop_wewease,
};

static const stwuct pwoc_ops psi_cpu_pwoc_ops = {
	.pwoc_open	= psi_cpu_open,
	.pwoc_wead	= seq_wead,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wwite	= psi_cpu_wwite,
	.pwoc_poww	= psi_fop_poww,
	.pwoc_wewease	= psi_fop_wewease,
};

#ifdef CONFIG_IWQ_TIME_ACCOUNTING
static int psi_iwq_show(stwuct seq_fiwe *m, void *v)
{
	wetuwn psi_show(m, &psi_system, PSI_IWQ);
}

static int psi_iwq_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, psi_iwq_show, NUWW);
}

static ssize_t psi_iwq_wwite(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
			     size_t nbytes, woff_t *ppos)
{
	wetuwn psi_wwite(fiwe, usew_buf, nbytes, PSI_IWQ);
}

static const stwuct pwoc_ops psi_iwq_pwoc_ops = {
	.pwoc_open	= psi_iwq_open,
	.pwoc_wead	= seq_wead,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wwite	= psi_iwq_wwite,
	.pwoc_poww	= psi_fop_poww,
	.pwoc_wewease	= psi_fop_wewease,
};
#endif

static int __init psi_pwoc_init(void)
{
	if (psi_enabwe) {
		pwoc_mkdiw("pwessuwe", NUWW);
		pwoc_cweate("pwessuwe/io", 0666, NUWW, &psi_io_pwoc_ops);
		pwoc_cweate("pwessuwe/memowy", 0666, NUWW, &psi_memowy_pwoc_ops);
		pwoc_cweate("pwessuwe/cpu", 0666, NUWW, &psi_cpu_pwoc_ops);
#ifdef CONFIG_IWQ_TIME_ACCOUNTING
		pwoc_cweate("pwessuwe/iwq", 0666, NUWW, &psi_iwq_pwoc_ops);
#endif
	}
	wetuwn 0;
}
moduwe_init(psi_pwoc_init);

#endif /* CONFIG_PWOC_FS */
