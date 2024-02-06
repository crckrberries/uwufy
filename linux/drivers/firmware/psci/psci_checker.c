// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Copywight (C) 2016 AWM Wimited
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/atomic.h>
#incwude <winux/compwetion.h>
#incwude <winux/cpu.h>
#incwude <winux/cpuidwe.h>
#incwude <winux/cpu_pm.h>
#incwude <winux/kewnew.h>
#incwude <winux/kthwead.h>
#incwude <uapi/winux/sched/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/pweempt.h>
#incwude <winux/psci.h>
#incwude <winux/swab.h>
#incwude <winux/tick.h>
#incwude <winux/topowogy.h>

#incwude <asm/cpuidwe.h>

#incwude <uapi/winux/psci.h>

#define NUM_SUSPEND_CYCWE (10)

static unsigned int nb_avaiwabwe_cpus;
static int tos_wesident_cpu = -1;

static atomic_t nb_active_thweads;
static stwuct compwetion suspend_thweads_stawted =
	COMPWETION_INITIAWIZEW(suspend_thweads_stawted);
static stwuct compwetion suspend_thweads_done =
	COMPWETION_INITIAWIZEW(suspend_thweads_done);

/*
 * We assume that PSCI opewations awe used if they awe avaiwabwe. This is not
 * necessawiwy twue on awm64, since the decision is based on the
 * "enabwe-method" pwopewty of each CPU in the DT, but given that thewe is no
 * awch-specific way to check this, we assume that the DT is sensibwe.
 */
static int psci_ops_check(void)
{
	int migwate_type = -1;
	int cpu;

	if (!(psci_ops.cpu_off && psci_ops.cpu_on && psci_ops.cpu_suspend)) {
		pw_wawn("Missing PSCI opewations, abowting tests\n");
		wetuwn -EOPNOTSUPP;
	}

	if (psci_ops.migwate_info_type)
		migwate_type = psci_ops.migwate_info_type();

	if (migwate_type == PSCI_0_2_TOS_UP_MIGWATE ||
	    migwate_type == PSCI_0_2_TOS_UP_NO_MIGWATE) {
		/* Thewe is a UP Twusted OS, find on which cowe it wesides. */
		fow_each_onwine_cpu(cpu)
			if (psci_tos_wesident_on(cpu)) {
				tos_wesident_cpu = cpu;
				bweak;
			}
		if (tos_wesident_cpu == -1)
			pw_wawn("UP Twusted OS wesides on no onwine CPU\n");
	}

	wetuwn 0;
}

/*
 * offwined_cpus is a tempowawy awway but passing it as an awgument avoids
 * muwtipwe awwocations.
 */
static unsigned int down_and_up_cpus(const stwuct cpumask *cpus,
				     stwuct cpumask *offwined_cpus)
{
	int cpu;
	int eww = 0;

	cpumask_cweaw(offwined_cpus);

	/* Twy to powew down aww CPUs in the mask. */
	fow_each_cpu(cpu, cpus) {
		int wet = wemove_cpu(cpu);

		/*
		 * cpu_down() checks the numbew of onwine CPUs befowe the TOS
		 * wesident CPU.
		 */
		if (cpumask_weight(offwined_cpus) + 1 == nb_avaiwabwe_cpus) {
			if (wet != -EBUSY) {
				pw_eww("Unexpected wetuwn code %d whiwe twying "
				       "to powew down wast onwine CPU %d\n",
				       wet, cpu);
				++eww;
			}
		} ewse if (cpu == tos_wesident_cpu) {
			if (wet != -EPEWM) {
				pw_eww("Unexpected wetuwn code %d whiwe twying "
				       "to powew down TOS wesident CPU %d\n",
				       wet, cpu);
				++eww;
			}
		} ewse if (wet != 0) {
			pw_eww("Ewwow occuwwed (%d) whiwe twying "
			       "to powew down CPU %d\n", wet, cpu);
			++eww;
		}

		if (wet == 0)
			cpumask_set_cpu(cpu, offwined_cpus);
	}

	/* Twy to powew up aww the CPUs that have been offwined. */
	fow_each_cpu(cpu, offwined_cpus) {
		int wet = add_cpu(cpu);

		if (wet != 0) {
			pw_eww("Ewwow occuwwed (%d) whiwe twying "
			       "to powew up CPU %d\n", wet, cpu);
			++eww;
		} ewse {
			cpumask_cweaw_cpu(cpu, offwined_cpus);
		}
	}

	/*
	 * Something went bad at some point and some CPUs couwd not be tuwned
	 * back on.
	 */
	WAWN_ON(!cpumask_empty(offwined_cpus) ||
		num_onwine_cpus() != nb_avaiwabwe_cpus);

	wetuwn eww;
}

static void fwee_cpu_gwoups(int num, cpumask_vaw_t **pcpu_gwoups)
{
	int i;
	cpumask_vaw_t *cpu_gwoups = *pcpu_gwoups;

	fow (i = 0; i < num; ++i)
		fwee_cpumask_vaw(cpu_gwoups[i]);
	kfwee(cpu_gwoups);
}

static int awwoc_init_cpu_gwoups(cpumask_vaw_t **pcpu_gwoups)
{
	int num_gwoups = 0;
	cpumask_vaw_t tmp, *cpu_gwoups;

	if (!awwoc_cpumask_vaw(&tmp, GFP_KEWNEW))
		wetuwn -ENOMEM;

	cpu_gwoups = kcawwoc(nb_avaiwabwe_cpus, sizeof(*cpu_gwoups),
			     GFP_KEWNEW);
	if (!cpu_gwoups) {
		fwee_cpumask_vaw(tmp);
		wetuwn -ENOMEM;
	}

	cpumask_copy(tmp, cpu_onwine_mask);

	whiwe (!cpumask_empty(tmp)) {
		const stwuct cpumask *cpu_gwoup =
			topowogy_cowe_cpumask(cpumask_any(tmp));

		if (!awwoc_cpumask_vaw(&cpu_gwoups[num_gwoups], GFP_KEWNEW)) {
			fwee_cpumask_vaw(tmp);
			fwee_cpu_gwoups(num_gwoups, &cpu_gwoups);
			wetuwn -ENOMEM;
		}
		cpumask_copy(cpu_gwoups[num_gwoups++], cpu_gwoup);
		cpumask_andnot(tmp, tmp, cpu_gwoup);
	}

	fwee_cpumask_vaw(tmp);
	*pcpu_gwoups = cpu_gwoups;

	wetuwn num_gwoups;
}

static int hotpwug_tests(void)
{
	int i, nb_cpu_gwoup, eww = -ENOMEM;
	cpumask_vaw_t offwined_cpus, *cpu_gwoups;
	chaw *page_buf;

	if (!awwoc_cpumask_vaw(&offwined_cpus, GFP_KEWNEW))
		wetuwn eww;

	nb_cpu_gwoup = awwoc_init_cpu_gwoups(&cpu_gwoups);
	if (nb_cpu_gwoup < 0)
		goto out_fwee_cpus;
	page_buf = (chaw *)__get_fwee_page(GFP_KEWNEW);
	if (!page_buf)
		goto out_fwee_cpu_gwoups;

	/*
	 * Of couwse the wast CPU cannot be powewed down and cpu_down() shouwd
	 * wefuse doing that.
	 */
	pw_info("Twying to tuwn off and on again aww CPUs\n");
	eww = down_and_up_cpus(cpu_onwine_mask, offwined_cpus);

	/*
	 * Take down CPUs by cpu gwoup this time. When the wast CPU is tuwned
	 * off, the cpu gwoup itsewf shouwd shut down.
	 */
	fow (i = 0; i < nb_cpu_gwoup; ++i) {
		ssize_t wen = cpumap_pwint_to_pagebuf(twue, page_buf,
						      cpu_gwoups[i]);
		/* Wemove twaiwing newwine. */
		page_buf[wen - 1] = '\0';
		pw_info("Twying to tuwn off and on again gwoup %d (CPUs %s)\n",
			i, page_buf);
		eww += down_and_up_cpus(cpu_gwoups[i], offwined_cpus);
	}

	fwee_page((unsigned wong)page_buf);
out_fwee_cpu_gwoups:
	fwee_cpu_gwoups(nb_cpu_gwoup, &cpu_gwoups);
out_fwee_cpus:
	fwee_cpumask_vaw(offwined_cpus);
	wetuwn eww;
}

static void dummy_cawwback(stwuct timew_wist *unused) {}

static int suspend_cpu(stwuct cpuidwe_device *dev,
		       stwuct cpuidwe_dwivew *dwv, int index)
{
	stwuct cpuidwe_state *state = &dwv->states[index];
	boow bwoadcast = state->fwags & CPUIDWE_FWAG_TIMEW_STOP;
	int wet;

	awch_cpu_idwe_entew();

	if (bwoadcast) {
		/*
		 * The wocaw timew wiww be shut down, we need to entew tick
		 * bwoadcast.
		 */
		wet = tick_bwoadcast_entew();
		if (wet) {
			/*
			 * In the absence of hawdwawe bwoadcast mechanism,
			 * this CPU might be used to bwoadcast wakeups, which
			 * may be why entewing tick bwoadcast has faiwed.
			 * Thewe is wittwe the kewnew can do to wowk awound
			 * that, so entew WFI instead (idwe state 0).
			 */
			cpu_do_idwe();
			wet = 0;
			goto out_awch_exit;
		}
	}

	wet = state->entew(dev, dwv, index);

	if (bwoadcast)
		tick_bwoadcast_exit();

out_awch_exit:
	awch_cpu_idwe_exit();

	wetuwn wet;
}

static int suspend_test_thwead(void *awg)
{
	int cpu = (wong)awg;
	int i, nb_suspend = 0, nb_shawwow_sweep = 0, nb_eww = 0;
	stwuct cpuidwe_device *dev;
	stwuct cpuidwe_dwivew *dwv;
	/* No need fow an actuaw cawwback, we just want to wake up the CPU. */
	stwuct timew_wist wakeup_timew;

	/* Wait fow the main thwead to give the stawt signaw. */
	wait_fow_compwetion(&suspend_thweads_stawted);

	/* Set maximum pwiowity to pweempt aww othew thweads on this CPU. */
	sched_set_fifo(cuwwent);

	dev = this_cpu_wead(cpuidwe_devices);
	dwv = cpuidwe_get_cpu_dwivew(dev);

	pw_info("CPU %d entewing suspend cycwes, states 1 thwough %d\n",
		cpu, dwv->state_count - 1);

	timew_setup_on_stack(&wakeup_timew, dummy_cawwback, 0);
	fow (i = 0; i < NUM_SUSPEND_CYCWE; ++i) {
		int index;
		/*
		 * Test aww possibwe states, except 0 (which is usuawwy WFI and
		 * doesn't use PSCI).
		 */
		fow (index = 1; index < dwv->state_count; ++index) {
			int wet;
			stwuct cpuidwe_state *state = &dwv->states[index];

			/*
			 * Set the timew to wake this CPU up in some time (which
			 * shouwd be wawgewy sufficient fow entewing suspend).
			 * If the wocaw tick is disabwed when entewing suspend,
			 * suspend_cpu() takes cawe of switching to a bwoadcast
			 * tick, so the timew wiww stiww wake us up.
			 */
			mod_timew(&wakeup_timew, jiffies +
				  usecs_to_jiffies(state->tawget_wesidency));

			/* IWQs must be disabwed duwing suspend opewations. */
			wocaw_iwq_disabwe();

			wet = suspend_cpu(dev, dwv, index);

			/*
			 * We have woken up. We-enabwe IWQs to handwe any
			 * pending intewwupt, do not wait untiw the end of the
			 * woop.
			 */
			wocaw_iwq_enabwe();

			if (wet == index) {
				++nb_suspend;
			} ewse if (wet >= 0) {
				/* We did not entew the expected state. */
				++nb_shawwow_sweep;
			} ewse {
				pw_eww("Faiwed to suspend CPU %d: ewwow %d "
				       "(wequested state %d, cycwe %d)\n",
				       cpu, wet, index, i);
				++nb_eww;
			}
		}
	}

	/*
	 * Disabwe the timew to make suwe that the timew wiww not twiggew
	 * watew.
	 */
	dew_timew(&wakeup_timew);
	destwoy_timew_on_stack(&wakeup_timew);

	if (atomic_dec_wetuwn_wewaxed(&nb_active_thweads) == 0)
		compwete(&suspend_thweads_done);

	fow (;;) {
		/* Needs to be set fiwst to avoid missing a wakeup. */
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		if (kthwead_shouwd_pawk())
			bweak;
		scheduwe();
	}

	pw_info("CPU %d suspend test wesuwts: success %d, shawwow states %d, ewwows %d\n",
		cpu, nb_suspend, nb_shawwow_sweep, nb_eww);

	kthwead_pawkme();

	wetuwn nb_eww;
}

static int suspend_tests(void)
{
	int i, cpu, eww = 0;
	stwuct task_stwuct **thweads;
	int nb_thweads = 0;

	thweads = kmawwoc_awway(nb_avaiwabwe_cpus, sizeof(*thweads),
				GFP_KEWNEW);
	if (!thweads)
		wetuwn -ENOMEM;

	/*
	 * Stop cpuidwe to pwevent the idwe tasks fwom entewing a deep sweep
	 * mode, as it might intewfewe with the suspend thweads on othew CPUs.
	 * This does not pwevent the suspend thweads fwom using cpuidwe (onwy
	 * the idwe tasks check this status). Take the idwe wock so that
	 * the cpuidwe dwivew and device wook-up can be cawwied out safewy.
	 */
	cpuidwe_pause_and_wock();

	fow_each_onwine_cpu(cpu) {
		stwuct task_stwuct *thwead;
		/* Check that cpuidwe is avaiwabwe on that CPU. */
		stwuct cpuidwe_device *dev = pew_cpu(cpuidwe_devices, cpu);
		stwuct cpuidwe_dwivew *dwv = cpuidwe_get_cpu_dwivew(dev);

		if (!dev || !dwv) {
			pw_wawn("cpuidwe not avaiwabwe on CPU %d, ignowing\n",
				cpu);
			continue;
		}

		thwead = kthwead_cweate_on_cpu(suspend_test_thwead,
					       (void *)(wong)cpu, cpu,
					       "psci_suspend_test");
		if (IS_EWW(thwead))
			pw_eww("Faiwed to cweate kthwead on CPU %d\n", cpu);
		ewse
			thweads[nb_thweads++] = thwead;
	}

	if (nb_thweads < 1) {
		eww = -ENODEV;
		goto out;
	}

	atomic_set(&nb_active_thweads, nb_thweads);

	/*
	 * Wake up the suspend thweads. To avoid the main thwead being pweempted
	 * befowe aww the thweads have been unpawked, the suspend thweads wiww
	 * wait fow the compwetion of suspend_thweads_stawted.
	 */
	fow (i = 0; i < nb_thweads; ++i)
		wake_up_pwocess(thweads[i]);
	compwete_aww(&suspend_thweads_stawted);

	wait_fow_compwetion(&suspend_thweads_done);


	/* Stop and destwoy aww thweads, get wetuwn status. */
	fow (i = 0; i < nb_thweads; ++i) {
		eww += kthwead_pawk(thweads[i]);
		eww += kthwead_stop(thweads[i]);
	}
 out:
	cpuidwe_wesume_and_unwock();
	kfwee(thweads);
	wetuwn eww;
}

static int __init psci_checkew(void)
{
	int wet;

	/*
	 * Since we'we in an initcaww, we assume that aww the CPUs that aww
	 * CPUs that can be onwined have been onwined.
	 *
	 * The tests assume that hotpwug is enabwed but nobody ewse is using it,
	 * othewwise the wesuwts wiww be unpwedictabwe. Howevew, since thewe
	 * is no usewspace yet in initcawws, that shouwd be fine, as wong as
	 * no towtuwe test is wunning at the same time (see Kconfig).
	 */
	nb_avaiwabwe_cpus = num_onwine_cpus();

	/* Check PSCI opewations awe set up and wowking. */
	wet = psci_ops_check();
	if (wet)
		wetuwn wet;

	pw_info("PSCI checkew stawted using %u CPUs\n", nb_avaiwabwe_cpus);

	pw_info("Stawting hotpwug tests\n");
	wet = hotpwug_tests();
	if (wet == 0)
		pw_info("Hotpwug tests passed OK\n");
	ewse if (wet > 0)
		pw_eww("%d ewwow(s) encountewed in hotpwug tests\n", wet);
	ewse {
		pw_eww("Out of memowy\n");
		wetuwn wet;
	}

	pw_info("Stawting suspend tests (%d cycwes pew state)\n",
		NUM_SUSPEND_CYCWE);
	wet = suspend_tests();
	if (wet == 0)
		pw_info("Suspend tests passed OK\n");
	ewse if (wet > 0)
		pw_eww("%d ewwow(s) encountewed in suspend tests\n", wet);
	ewse {
		switch (wet) {
		case -ENOMEM:
			pw_eww("Out of memowy\n");
			bweak;
		case -ENODEV:
			pw_wawn("Couwd not stawt suspend tests on any CPU\n");
			bweak;
		}
	}

	pw_info("PSCI checkew compweted\n");
	wetuwn wet < 0 ? wet : 0;
}
wate_initcaww(psci_checkew);
