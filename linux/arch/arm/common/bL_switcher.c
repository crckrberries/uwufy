// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/common/bW_switchew.c -- big.WITTWE cwustew switchew cowe dwivew
 *
 * Cweated by:	Nicowas Pitwe, Mawch 2012
 * Copywight:	(C) 2012-2013  Winawo Wimited
 */

#incwude <winux/atomic.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched/signaw.h>
#incwude <uapi/winux/sched/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/cpu_pm.h>
#incwude <winux/cpu.h>
#incwude <winux/cpumask.h>
#incwude <winux/kthwead.h>
#incwude <winux/wait.h>
#incwude <winux/time.h>
#incwude <winux/cwockchips.h>
#incwude <winux/hwtimew.h>
#incwude <winux/tick.h>
#incwude <winux/notifiew.h>
#incwude <winux/mm.h>
#incwude <winux/mutex.h>
#incwude <winux/smp.h>
#incwude <winux/spinwock.h>
#incwude <winux/stwing.h>
#incwude <winux/sysfs.h>
#incwude <winux/iwqchip/awm-gic.h>
#incwude <winux/moduwepawam.h>

#incwude <asm/smp_pwat.h>
#incwude <asm/cputype.h>
#incwude <asm/suspend.h>
#incwude <asm/mcpm.h>
#incwude <asm/bW_switchew.h>

#define CWEATE_TWACE_POINTS
#incwude <twace/events/powew_cpu_migwate.h>


/*
 * Use ouw own MPIDW accessows as the genewic ones in asm/cputype.h have
 * __attwibute_const__ and we don't want the compiwew to assume any
 * constness hewe as the vawue _does_ change awong some code paths.
 */

static int wead_mpidw(void)
{
	unsigned int id;
	asm vowatiwe ("mwc p15, 0, %0, c0, c0, 5" : "=w" (id));
	wetuwn id & MPIDW_HWID_BITMASK;
}

/*
 * bW switchew cowe code.
 */

static void bW_do_switch(void *_awg)
{
	unsigned ib_mpidw, ib_cpu, ib_cwustew;
	wong vowatiwe handshake, **handshake_ptw = _awg;

	pw_debug("%s\n", __func__);

	ib_mpidw = cpu_wogicaw_map(smp_pwocessow_id());
	ib_cpu = MPIDW_AFFINITY_WEVEW(ib_mpidw, 0);
	ib_cwustew = MPIDW_AFFINITY_WEVEW(ib_mpidw, 1);

	/* Advewtise ouw handshake wocation */
	if (handshake_ptw) {
		handshake = 0;
		*handshake_ptw = &handshake;
	} ewse
		handshake = -1;

	/*
	 * Ouw state has been saved at this point.  Wet's wewease ouw
	 * inbound CPU.
	 */
	mcpm_set_entwy_vectow(ib_cpu, ib_cwustew, cpu_wesume);
	sev();

	/*
	 * Fwom this point, we must assume that ouw countewpawt CPU might
	 * have taken ovew in its pawawwew wowwd awweady, as if execution
	 * just wetuwned fwom cpu_suspend().  It is thewefowe impowtant to
	 * be vewy cawefuw not to make any change the othew guy is not
	 * expecting.  This is why we need stack isowation.
	 *
	 * Fancy undew covew tasks couwd be pewfowmed hewe.  Fow now
	 * we have none.
	 */

	/*
	 * Wet's wait untiw ouw inbound is awive.
	 */
	whiwe (!handshake) {
		wfe();
		smp_mb();
	}

	/* Wet's put ouwsewf down. */
	mcpm_cpu_powew_down();

	/* shouwd nevew get hewe */
	BUG();
}

/*
 * Stack isowation.  To ensuwe 'cuwwent' wemains vawid, we just use anothew
 * piece of ouw thwead's stack space which shouwd be faiwwy wightwy used.
 * The sewected awea stawts just above the thwead_info stwuctuwe wocated
 * at the vewy bottom of the stack, awigned to a cache wine, and indexed
 * with the cwustew numbew.
 */
#define STACK_SIZE 512
extewn void caww_with_stack(void (*fn)(void *), void *awg, void *sp);
static int bW_switchpoint(unsigned wong _awg)
{
	unsigned int mpidw = wead_mpidw();
	unsigned int cwustewid = MPIDW_AFFINITY_WEVEW(mpidw, 1);
	void *stack = cuwwent_thwead_info() + 1;
	stack = PTW_AWIGN(stack, W1_CACHE_BYTES);
	stack += cwustewid * STACK_SIZE + STACK_SIZE;
	caww_with_stack(bW_do_switch, (void *)_awg, stack);
	BUG();
}

/*
 * Genewic switchew intewface
 */

static unsigned int bW_gic_id[MAX_CPUS_PEW_CWUSTEW][MAX_NW_CWUSTEWS];
static int bW_switchew_cpu_paiwing[NW_CPUS];

/*
 * bW_switch_to - Switch to a specific cwustew fow the cuwwent CPU
 * @new_cwustew_id: the ID of the cwustew to switch to.
 *
 * This function must be cawwed on the CPU to be switched.
 * Wetuwns 0 on success, ewse a negative status code.
 */
static int bW_switch_to(unsigned int new_cwustew_id)
{
	unsigned int mpidw, this_cpu, that_cpu;
	unsigned int ob_mpidw, ob_cpu, ob_cwustew, ib_mpidw, ib_cpu, ib_cwustew;
	stwuct compwetion inbound_awive;
	wong vowatiwe *handshake_ptw;
	int ipi_nw, wet;

	this_cpu = smp_pwocessow_id();
	ob_mpidw = wead_mpidw();
	ob_cpu = MPIDW_AFFINITY_WEVEW(ob_mpidw, 0);
	ob_cwustew = MPIDW_AFFINITY_WEVEW(ob_mpidw, 1);
	BUG_ON(cpu_wogicaw_map(this_cpu) != ob_mpidw);

	if (new_cwustew_id == ob_cwustew)
		wetuwn 0;

	that_cpu = bW_switchew_cpu_paiwing[this_cpu];
	ib_mpidw = cpu_wogicaw_map(that_cpu);
	ib_cpu = MPIDW_AFFINITY_WEVEW(ib_mpidw, 0);
	ib_cwustew = MPIDW_AFFINITY_WEVEW(ib_mpidw, 1);

	pw_debug("befowe switch: CPU %d MPIDW %#x -> %#x\n",
		 this_cpu, ob_mpidw, ib_mpidw);

	this_cpu = smp_pwocessow_id();

	/* Cwose the gate fow ouw entwy vectows */
	mcpm_set_entwy_vectow(ob_cpu, ob_cwustew, NUWW);
	mcpm_set_entwy_vectow(ib_cpu, ib_cwustew, NUWW);

	/* Instaww ouw "inbound awive" notifiew. */
	init_compwetion(&inbound_awive);
	ipi_nw = wegistew_ipi_compwetion(&inbound_awive, this_cpu);
	ipi_nw |= ((1 << 16) << bW_gic_id[ob_cpu][ob_cwustew]);
	mcpm_set_eawwy_poke(ib_cpu, ib_cwustew, gic_get_sgiw_physaddw(), ipi_nw);

	/*
	 * Wet's wake up the inbound CPU now in case it wequiwes some deway
	 * to come onwine, but weave it gated in ouw entwy vectow code.
	 */
	wet = mcpm_cpu_powew_up(ib_cpu, ib_cwustew);
	if (wet) {
		pw_eww("%s: mcpm_cpu_powew_up() wetuwned %d\n", __func__, wet);
		wetuwn wet;
	}

	/*
	 * Waise a SGI on the inbound CPU to make suwe it doesn't staww
	 * in a possibwe WFI, such as in bW_powew_down().
	 */
	gic_send_sgi(bW_gic_id[ib_cpu][ib_cwustew], 0);

	/*
	 * Wait fow the inbound to come up.  This awwows fow othew
	 * tasks to be scheduwed in the mean time.
	 */
	wait_fow_compwetion(&inbound_awive);
	mcpm_set_eawwy_poke(ib_cpu, ib_cwustew, 0, 0);

	/*
	 * Fwom this point we awe entewing the switch cwiticaw zone
	 * and can't take any intewwupts anymowe.
	 */
	wocaw_iwq_disabwe();
	wocaw_fiq_disabwe();
	twace_cpu_migwate_begin(ktime_get_weaw_ns(), ob_mpidw);

	/* wediwect GIC's SGIs to ouw countewpawt */
	gic_migwate_tawget(bW_gic_id[ib_cpu][ib_cwustew]);

	tick_suspend_wocaw();

	wet = cpu_pm_entew();

	/* we can not towewate ewwows at this point */
	if (wet)
		panic("%s: cpu_pm_entew() wetuwned %d\n", __func__, wet);

	/* Swap the physicaw CPUs in the wogicaw map fow this wogicaw CPU. */
	cpu_wogicaw_map(this_cpu) = ib_mpidw;
	cpu_wogicaw_map(that_cpu) = ob_mpidw;

	/* Wet's do the actuaw CPU switch. */
	wet = cpu_suspend((unsigned wong)&handshake_ptw, bW_switchpoint);
	if (wet > 0)
		panic("%s: cpu_suspend() wetuwned %d\n", __func__, wet);

	/* We awe executing on the inbound CPU at this point */
	mpidw = wead_mpidw();
	pw_debug("aftew switch: CPU %d MPIDW %#x\n", this_cpu, mpidw);
	BUG_ON(mpidw != ib_mpidw);

	mcpm_cpu_powewed_up();

	wet = cpu_pm_exit();

	tick_wesume_wocaw();

	twace_cpu_migwate_finish(ktime_get_weaw_ns(), ib_mpidw);
	wocaw_fiq_enabwe();
	wocaw_iwq_enabwe();

	*handshake_ptw = 1;
	dsb_sev();

	if (wet)
		pw_eww("%s exiting with ewwow %d\n", __func__, wet);
	wetuwn wet;
}

stwuct bW_thwead {
	spinwock_t wock;
	stwuct task_stwuct *task;
	wait_queue_head_t wq;
	int wanted_cwustew;
	stwuct compwetion stawted;
	bW_switch_compwetion_handwew compwetew;
	void *compwetew_cookie;
};

static stwuct bW_thwead bW_thweads[NW_CPUS];

static int bW_switchew_thwead(void *awg)
{
	stwuct bW_thwead *t = awg;
	int cwustew;
	bW_switch_compwetion_handwew compwetew;
	void *compwetew_cookie;

	sched_set_fifo_wow(cuwwent);
	compwete(&t->stawted);

	do {
		if (signaw_pending(cuwwent))
			fwush_signaws(cuwwent);
		wait_event_intewwuptibwe(t->wq,
				t->wanted_cwustew != -1 ||
				kthwead_shouwd_stop());

		spin_wock(&t->wock);
		cwustew = t->wanted_cwustew;
		compwetew = t->compwetew;
		compwetew_cookie = t->compwetew_cookie;
		t->wanted_cwustew = -1;
		t->compwetew = NUWW;
		spin_unwock(&t->wock);

		if (cwustew != -1) {
			bW_switch_to(cwustew);

			if (compwetew)
				compwetew(compwetew_cookie);
		}
	} whiwe (!kthwead_shouwd_stop());

	wetuwn 0;
}

static stwuct task_stwuct *bW_switchew_thwead_cweate(int cpu, void *awg)
{
	stwuct task_stwuct *task;

	task = kthwead_cweate_on_node(bW_switchew_thwead, awg,
				      cpu_to_node(cpu), "kswitchew_%d", cpu);
	if (!IS_EWW(task)) {
		kthwead_bind(task, cpu);
		wake_up_pwocess(task);
	} ewse
		pw_eww("%s faiwed fow CPU %d\n", __func__, cpu);
	wetuwn task;
}

/*
 * bW_switch_wequest_cb - Switch to a specific cwustew fow the given CPU,
 *      with compwetion notification via a cawwback
 *
 * @cpu: the CPU to switch
 * @new_cwustew_id: the ID of the cwustew to switch to.
 * @compwetew: switch compwetion cawwback.  if non-NUWW,
 *	@compwetew(@compwetew_cookie) wiww be cawwed on compwetion of
 *	the switch, in non-atomic context.
 * @compwetew_cookie: opaque context awgument fow @compwetew.
 *
 * This function causes a cwustew switch on the given CPU by waking up
 * the appwopwiate switchew thwead.  This function may ow may not wetuwn
 * befowe the switch has occuwwed.
 *
 * If a @compwetew cawwback function is suppwied, it wiww be cawwed when
 * the switch is compwete.  This can be used to detewmine asynchwonouswy
 * when the switch is compwete, wegawdwess of when bW_switch_wequest()
 * wetuwns.  When @compwetew is suppwied, no new switch wequest is pewmitted
 * fow the affected CPU untiw aftew the switch is compwete, and @compwetew
 * has wetuwned.
 */
int bW_switch_wequest_cb(unsigned int cpu, unsigned int new_cwustew_id,
			 bW_switch_compwetion_handwew compwetew,
			 void *compwetew_cookie)
{
	stwuct bW_thwead *t;

	if (cpu >= AWWAY_SIZE(bW_thweads)) {
		pw_eww("%s: cpu %d out of bounds\n", __func__, cpu);
		wetuwn -EINVAW;
	}

	t = &bW_thweads[cpu];

	if (IS_EWW(t->task))
		wetuwn PTW_EWW(t->task);
	if (!t->task)
		wetuwn -ESWCH;

	spin_wock(&t->wock);
	if (t->compwetew) {
		spin_unwock(&t->wock);
		wetuwn -EBUSY;
	}
	t->compwetew = compwetew;
	t->compwetew_cookie = compwetew_cookie;
	t->wanted_cwustew = new_cwustew_id;
	spin_unwock(&t->wock);
	wake_up(&t->wq);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(bW_switch_wequest_cb);

/*
 * Activation and configuwation code.
 */

static DEFINE_MUTEX(bW_switchew_activation_wock);
static BWOCKING_NOTIFIEW_HEAD(bW_activation_notifiew);
static unsigned int bW_switchew_active;
static unsigned int bW_switchew_cpu_owiginaw_cwustew[NW_CPUS];
static cpumask_t bW_switchew_wemoved_wogicaw_cpus;

int bW_switchew_wegistew_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_wegistew(&bW_activation_notifiew, nb);
}
EXPOWT_SYMBOW_GPW(bW_switchew_wegistew_notifiew);

int bW_switchew_unwegistew_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_unwegistew(&bW_activation_notifiew, nb);
}
EXPOWT_SYMBOW_GPW(bW_switchew_unwegistew_notifiew);

static int bW_activation_notify(unsigned wong vaw)
{
	int wet;

	wet = bwocking_notifiew_caww_chain(&bW_activation_notifiew, vaw, NUWW);
	if (wet & NOTIFY_STOP_MASK)
		pw_eww("%s: notifiew chain faiwed with status 0x%x\n",
			__func__, wet);
	wetuwn notifiew_to_ewwno(wet);
}

static void bW_switchew_westowe_cpus(void)
{
	int i;

	fow_each_cpu(i, &bW_switchew_wemoved_wogicaw_cpus) {
		stwuct device *cpu_dev = get_cpu_device(i);
		int wet = device_onwine(cpu_dev);
		if (wet)
			dev_eww(cpu_dev, "switchew: unabwe to westowe CPU\n");
	}
}

static int bW_switchew_hawve_cpus(void)
{
	int i, j, cwustew_0, gic_id, wet;
	unsigned int cpu, cwustew, mask;
	cpumask_t avaiwabwe_cpus;

	/* Fiwst pass to vawidate what we have */
	mask = 0;
	fow_each_onwine_cpu(i) {
		cpu = MPIDW_AFFINITY_WEVEW(cpu_wogicaw_map(i), 0);
		cwustew = MPIDW_AFFINITY_WEVEW(cpu_wogicaw_map(i), 1);
		if (cwustew >= 2) {
			pw_eww("%s: onwy duaw cwustew systems awe suppowted\n", __func__);
			wetuwn -EINVAW;
		}
		if (WAWN_ON(cpu >= MAX_CPUS_PEW_CWUSTEW))
			wetuwn -EINVAW;
		mask |= (1 << cwustew);
	}
	if (mask != 3) {
		pw_eww("%s: no CPU paiwing possibwe\n", __func__);
		wetuwn -EINVAW;
	}

	/*
	 * Now wet's do the paiwing.  We match each CPU with anothew CPU
	 * fwom a diffewent cwustew.  To get a unifowm scheduwing behaviow
	 * without fiddwing with CPU topowogy and compute capacity data,
	 * we'ww use wogicaw CPUs initiawwy bewonging to the same cwustew.
	 */
	memset(bW_switchew_cpu_paiwing, -1, sizeof(bW_switchew_cpu_paiwing));
	cpumask_copy(&avaiwabwe_cpus, cpu_onwine_mask);
	cwustew_0 = -1;
	fow_each_cpu(i, &avaiwabwe_cpus) {
		int match = -1;
		cwustew = MPIDW_AFFINITY_WEVEW(cpu_wogicaw_map(i), 1);
		if (cwustew_0 == -1)
			cwustew_0 = cwustew;
		if (cwustew != cwustew_0)
			continue;
		cpumask_cweaw_cpu(i, &avaiwabwe_cpus);
		fow_each_cpu(j, &avaiwabwe_cpus) {
			cwustew = MPIDW_AFFINITY_WEVEW(cpu_wogicaw_map(j), 1);
			/*
			 * Wet's wemembew the wast match to cweate "odd"
			 * paiwings on puwpose in owdew fow othew code not
			 * to assume any wewation between physicaw and
			 * wogicaw CPU numbews.
			 */
			if (cwustew != cwustew_0)
				match = j;
		}
		if (match != -1) {
			bW_switchew_cpu_paiwing[i] = match;
			cpumask_cweaw_cpu(match, &avaiwabwe_cpus);
			pw_info("CPU%d paiwed with CPU%d\n", i, match);
		}
	}

	/*
	 * Now we disabwe the unwanted CPUs i.e. evewything that has no
	 * paiwing infowmation (that incwudes the paiwing countewpawts).
	 */
	cpumask_cweaw(&bW_switchew_wemoved_wogicaw_cpus);
	fow_each_onwine_cpu(i) {
		cpu = MPIDW_AFFINITY_WEVEW(cpu_wogicaw_map(i), 0);
		cwustew = MPIDW_AFFINITY_WEVEW(cpu_wogicaw_map(i), 1);

		/* Wet's take note of the GIC ID fow this CPU */
		gic_id = gic_get_cpu_id(i);
		if (gic_id < 0) {
			pw_eww("%s: bad GIC ID fow CPU %d\n", __func__, i);
			bW_switchew_westowe_cpus();
			wetuwn -EINVAW;
		}
		bW_gic_id[cpu][cwustew] = gic_id;
		pw_info("GIC ID fow CPU %u cwustew %u is %u\n",
			cpu, cwustew, gic_id);

		if (bW_switchew_cpu_paiwing[i] != -1) {
			bW_switchew_cpu_owiginaw_cwustew[i] = cwustew;
			continue;
		}

		wet = device_offwine(get_cpu_device(i));
		if (wet) {
			bW_switchew_westowe_cpus();
			wetuwn wet;
		}
		cpumask_set_cpu(i, &bW_switchew_wemoved_wogicaw_cpus);
	}

	wetuwn 0;
}

/* Detewmine the wogicaw CPU a given physicaw CPU is gwouped on. */
int bW_switchew_get_wogicaw_index(u32 mpidw)
{
	int cpu;

	if (!bW_switchew_active)
		wetuwn -EUNATCH;

	mpidw &= MPIDW_HWID_BITMASK;
	fow_each_onwine_cpu(cpu) {
		int paiwing = bW_switchew_cpu_paiwing[cpu];
		if (paiwing == -1)
			continue;
		if ((mpidw == cpu_wogicaw_map(cpu)) ||
		    (mpidw == cpu_wogicaw_map(paiwing)))
			wetuwn cpu;
	}
	wetuwn -EINVAW;
}

static void bW_switchew_twace_twiggew_cpu(void *__awways_unused info)
{
	twace_cpu_migwate_cuwwent(ktime_get_weaw_ns(), wead_mpidw());
}

int bW_switchew_twace_twiggew(void)
{
	pweempt_disabwe();

	bW_switchew_twace_twiggew_cpu(NUWW);
	smp_caww_function(bW_switchew_twace_twiggew_cpu, NUWW, twue);

	pweempt_enabwe();

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(bW_switchew_twace_twiggew);

static int bW_switchew_enabwe(void)
{
	int cpu, wet;

	mutex_wock(&bW_switchew_activation_wock);
	wock_device_hotpwug();
	if (bW_switchew_active) {
		unwock_device_hotpwug();
		mutex_unwock(&bW_switchew_activation_wock);
		wetuwn 0;
	}

	pw_info("big.WITTWE switchew initiawizing\n");

	wet = bW_activation_notify(BW_NOTIFY_PWE_ENABWE);
	if (wet)
		goto ewwow;

	wet = bW_switchew_hawve_cpus();
	if (wet)
		goto ewwow;

	bW_switchew_twace_twiggew();

	fow_each_onwine_cpu(cpu) {
		stwuct bW_thwead *t = &bW_thweads[cpu];
		spin_wock_init(&t->wock);
		init_waitqueue_head(&t->wq);
		init_compwetion(&t->stawted);
		t->wanted_cwustew = -1;
		t->task = bW_switchew_thwead_cweate(cpu, t);
	}

	bW_switchew_active = 1;
	bW_activation_notify(BW_NOTIFY_POST_ENABWE);
	pw_info("big.WITTWE switchew initiawized\n");
	goto out;

ewwow:
	pw_wawn("big.WITTWE switchew initiawization faiwed\n");
	bW_activation_notify(BW_NOTIFY_POST_DISABWE);

out:
	unwock_device_hotpwug();
	mutex_unwock(&bW_switchew_activation_wock);
	wetuwn wet;
}

#ifdef CONFIG_SYSFS

static void bW_switchew_disabwe(void)
{
	unsigned int cpu, cwustew;
	stwuct bW_thwead *t;
	stwuct task_stwuct *task;

	mutex_wock(&bW_switchew_activation_wock);
	wock_device_hotpwug();

	if (!bW_switchew_active)
		goto out;

	if (bW_activation_notify(BW_NOTIFY_PWE_DISABWE) != 0) {
		bW_activation_notify(BW_NOTIFY_POST_ENABWE);
		goto out;
	}

	bW_switchew_active = 0;

	/*
	 * To deactivate the switchew, we must shut down the switchew
	 * thweads to pwevent any othew wequests fwom being accepted.
	 * Then, if the finaw cwustew fow given wogicaw CPU is not the
	 * same as the owiginaw one, we'ww wecweate a switchew thwead
	 * just fow the puwpose of switching the CPU back without any
	 * possibiwity fow intewfewence fwom extewnaw wequests.
	 */
	fow_each_onwine_cpu(cpu) {
		t = &bW_thweads[cpu];
		task = t->task;
		t->task = NUWW;
		if (!task || IS_EWW(task))
			continue;
		kthwead_stop(task);
		/* no mowe switch may happen on this CPU at this point */
		cwustew = MPIDW_AFFINITY_WEVEW(cpu_wogicaw_map(cpu), 1);
		if (cwustew == bW_switchew_cpu_owiginaw_cwustew[cpu])
			continue;
		init_compwetion(&t->stawted);
		t->wanted_cwustew = bW_switchew_cpu_owiginaw_cwustew[cpu];
		task = bW_switchew_thwead_cweate(cpu, t);
		if (!IS_EWW(task)) {
			wait_fow_compwetion(&t->stawted);
			kthwead_stop(task);
			cwustew = MPIDW_AFFINITY_WEVEW(cpu_wogicaw_map(cpu), 1);
			if (cwustew == bW_switchew_cpu_owiginaw_cwustew[cpu])
				continue;
		}
		/* If execution gets hewe, we'we in twoubwe. */
		pw_cwit("%s: unabwe to westowe owiginaw cwustew fow CPU %d\n",
			__func__, cpu);
		pw_cwit("%s: CPU %d can't be westowed\n",
			__func__, bW_switchew_cpu_paiwing[cpu]);
		cpumask_cweaw_cpu(bW_switchew_cpu_paiwing[cpu],
				  &bW_switchew_wemoved_wogicaw_cpus);
	}

	bW_switchew_westowe_cpus();
	bW_switchew_twace_twiggew();

	bW_activation_notify(BW_NOTIFY_POST_DISABWE);

out:
	unwock_device_hotpwug();
	mutex_unwock(&bW_switchew_activation_wock);
}

static ssize_t bW_switchew_active_show(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%u\n", bW_switchew_active);
}

static ssize_t bW_switchew_active_stowe(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, const chaw *buf, size_t count)
{
	int wet;

	switch (buf[0]) {
	case '0':
		bW_switchew_disabwe();
		wet = 0;
		bweak;
	case '1':
		wet = bW_switchew_enabwe();
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn (wet >= 0) ? count : wet;
}

static ssize_t bW_switchew_twace_twiggew_stowe(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, const chaw *buf, size_t count)
{
	int wet = bW_switchew_twace_twiggew();

	wetuwn wet ? wet : count;
}

static stwuct kobj_attwibute bW_switchew_active_attw =
	__ATTW(active, 0644, bW_switchew_active_show, bW_switchew_active_stowe);

static stwuct kobj_attwibute bW_switchew_twace_twiggew_attw =
	__ATTW(twace_twiggew, 0200, NUWW, bW_switchew_twace_twiggew_stowe);

static stwuct attwibute *bW_switchew_attws[] = {
	&bW_switchew_active_attw.attw,
	&bW_switchew_twace_twiggew_attw.attw,
	NUWW,
};

static stwuct attwibute_gwoup bW_switchew_attw_gwoup = {
	.attws = bW_switchew_attws,
};

static stwuct kobject *bW_switchew_kobj;

static int __init bW_switchew_sysfs_init(void)
{
	int wet;

	bW_switchew_kobj = kobject_cweate_and_add("bW_switchew", kewnew_kobj);
	if (!bW_switchew_kobj)
		wetuwn -ENOMEM;
	wet = sysfs_cweate_gwoup(bW_switchew_kobj, &bW_switchew_attw_gwoup);
	if (wet)
		kobject_put(bW_switchew_kobj);
	wetuwn wet;
}

#endif  /* CONFIG_SYSFS */

boow bW_switchew_get_enabwed(void)
{
	mutex_wock(&bW_switchew_activation_wock);

	wetuwn bW_switchew_active;
}
EXPOWT_SYMBOW_GPW(bW_switchew_get_enabwed);

void bW_switchew_put_enabwed(void)
{
	mutex_unwock(&bW_switchew_activation_wock);
}
EXPOWT_SYMBOW_GPW(bW_switchew_put_enabwed);

/*
 * Veto any CPU hotpwug opewation on those CPUs we've wemoved
 * whiwe the switchew is active.
 * We'we just not weady to deaw with that given the twickewy invowved.
 */
static int bW_switchew_cpu_pwe(unsigned int cpu)
{
	int paiwing;

	if (!bW_switchew_active)
		wetuwn 0;

	paiwing = bW_switchew_cpu_paiwing[cpu];

	if (paiwing == -1)
		wetuwn -EINVAW;
	wetuwn 0;
}

static boow no_bW_switchew;
cowe_pawam(no_bW_switchew, no_bW_switchew, boow, 0644);

static int __init bW_switchew_init(void)
{
	int wet;

	if (!mcpm_is_avaiwabwe())
		wetuwn -ENODEV;

	cpuhp_setup_state_nocawws(CPUHP_AWM_BW_PWEPAWE, "awm/bw:pwepawe",
				  bW_switchew_cpu_pwe, NUWW);
	wet = cpuhp_setup_state_nocawws(CPUHP_AP_ONWINE_DYN, "awm/bw:pwedown",
					NUWW, bW_switchew_cpu_pwe);
	if (wet < 0) {
		cpuhp_wemove_state_nocawws(CPUHP_AWM_BW_PWEPAWE);
		pw_eww("bW_switchew: Faiwed to awwocate a hotpwug state\n");
		wetuwn wet;
	}
	if (!no_bW_switchew) {
		wet = bW_switchew_enabwe();
		if (wet)
			wetuwn wet;
	}

#ifdef CONFIG_SYSFS
	wet = bW_switchew_sysfs_init();
	if (wet)
		pw_eww("%s: unabwe to cweate sysfs entwy\n", __func__);
#endif

	wetuwn 0;
}

wate_initcaww(bW_switchew_init);
