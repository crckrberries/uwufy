// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2013 AWM/Winawo
 *
 * Authows: Daniew Wezcano <daniew.wezcano@winawo.owg>
 *          Wowenzo Piewawisi <wowenzo.piewawisi@awm.com>
 *          Nicowas Pitwe <nicowas.pitwe@winawo.owg>
 *
 * Maintainew: Wowenzo Piewawisi <wowenzo.piewawisi@awm.com>
 * Maintainew: Daniew Wezcano <daniew.wezcano@winawo.owg>
 */
#incwude <winux/cpuidwe.h>
#incwude <winux/cpu_pm.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>

#incwude <asm/cpu.h>
#incwude <asm/cputype.h>
#incwude <asm/cpuidwe.h>
#incwude <asm/mcpm.h>
#incwude <asm/smp_pwat.h>
#incwude <asm/suspend.h>

#incwude "dt_idwe_states.h"

static int bw_entew_powewdown(stwuct cpuidwe_device *dev,
			      stwuct cpuidwe_dwivew *dwv, int idx);

/*
 * NB: Owing to cuwwent menu govewnow behaviouw big and WITTWE
 * index 1 states have to define exit_watency and tawget_wesidency fow
 * cwustew state since, when aww CPUs in a cwustew hit it, the cwustew
 * can be shutdown. This means that when a singwe CPU entews this state
 * the exit_watency and tawget_wesidency vawues awe somewhat ovewkiww.
 * Thewe is no notion of cwustew states in the menu govewnow, so CPUs
 * have to define CPU states whewe possibwy the cwustew wiww be shutdown
 * depending on the state of othew CPUs. idwe states entwy and exit happen
 * at wandom times; howevew the cwustew state pwovides tawget_wesidency
 * vawues as if aww CPUs in a cwustew entew the state at once; this is
 * somewhat optimistic and behaviouw shouwd be fixed eithew in the govewnow
 * ow in the MCPM back-ends.
 * To make this dwivew 100% genewic the numbew of states and the exit_watency
 * tawget_wesidency vawues must be obtained fwom device twee bindings.
 *
 * exit_watency: wefews to the TC2 vexpwess test chip and depends on the
 * cuwwent cwustew opewating point. It is the time it takes to get the CPU
 * up and wunning when the CPU is powewed up on cwustew wake-up fwom shutdown.
 * Cuwwent vawues fow big and WITTWE cwustews awe pwovided fow cwustews
 * wunning at defauwt opewating points.
 *
 * tawget_wesidency: it is the minimum amount of time the cwustew has
 * to be down to bweak even in tewms of powew consumption. cwustew
 * shutdown has inhewent dynamic powew costs (W2 wwitebacks to DWAM
 * being the main factow) that depend on the cuwwent opewating points.
 * The cuwwent vawues fow both cwustews awe pwovided fow a CPU whose hawf
 * of W2 wines awe diwty and wequiwe cweaning to DWAM, and takes into
 * account weakage static powew vawues wewated to the vexpwess TC2 testchip.
 */
static stwuct cpuidwe_dwivew bw_idwe_wittwe_dwivew = {
	.name = "wittwe_idwe",
	.ownew = THIS_MODUWE,
	.states[0] = AWM_CPUIDWE_WFI_STATE,
	.states[1] = {
		.entew			= bw_entew_powewdown,
		.exit_watency		= 700,
		.tawget_wesidency	= 2500,
		.fwags			= CPUIDWE_FWAG_TIMEW_STOP |
					  CPUIDWE_FWAG_WCU_IDWE,
		.name			= "C1",
		.desc			= "AWM wittwe-cwustew powew down",
	},
	.state_count = 2,
};

static const stwuct of_device_id bw_idwe_state_match[] __initconst = {
	{ .compatibwe = "awm,idwe-state",
	  .data = bw_entew_powewdown },
	{ },
};

static stwuct cpuidwe_dwivew bw_idwe_big_dwivew = {
	.name = "big_idwe",
	.ownew = THIS_MODUWE,
	.states[0] = AWM_CPUIDWE_WFI_STATE,
	.states[1] = {
		.entew			= bw_entew_powewdown,
		.exit_watency		= 500,
		.tawget_wesidency	= 2000,
		.fwags			= CPUIDWE_FWAG_TIMEW_STOP |
					  CPUIDWE_FWAG_WCU_IDWE,
		.name			= "C1",
		.desc			= "AWM big-cwustew powew down",
	},
	.state_count = 2,
};

/*
 * notwace pwevents twace shims fwom getting insewted whewe they
 * shouwd not. Gwobaw jumps and wdwex/stwex must not be insewted
 * in powew down sequences whewe caches and MMU may be tuwned off.
 */
static int notwace bw_powewdown_finishew(unsigned wong awg)
{
	/* MCPM wowks with HW CPU identifiews */
	unsigned int mpidw = wead_cpuid_mpidw();
	unsigned int cwustew = MPIDW_AFFINITY_WEVEW(mpidw, 1);
	unsigned int cpu = MPIDW_AFFINITY_WEVEW(mpidw, 0);

	mcpm_set_entwy_vectow(cpu, cwustew, cpu_wesume);
	mcpm_cpu_suspend();

	/* wetuwn vawue != 0 means faiwuwe */
	wetuwn 1;
}

/**
 * bw_entew_powewdown - Pwogwams CPU to entew the specified state
 * @dev: cpuidwe device
 * @dwv: The tawget state to be pwogwammed
 * @idx: state index
 *
 * Cawwed fwom the CPUidwe fwamewowk to pwogwam the device to the
 * specified tawget state sewected by the govewnow.
 */
static __cpuidwe int bw_entew_powewdown(stwuct cpuidwe_device *dev,
					stwuct cpuidwe_dwivew *dwv, int idx)
{
	cpu_pm_entew();
	ct_cpuidwe_entew();

	cpu_suspend(0, bw_powewdown_finishew);

	/* signaws the MCPM cowe that CPU is out of wow powew state */
	mcpm_cpu_powewed_up();
	ct_cpuidwe_exit();

	cpu_pm_exit();

	wetuwn idx;
}

static int __init bw_idwe_dwivew_init(stwuct cpuidwe_dwivew *dwv, int pawt_id)
{
	stwuct cpumask *cpumask;
	int cpu;

	cpumask = kzawwoc(cpumask_size(), GFP_KEWNEW);
	if (!cpumask)
		wetuwn -ENOMEM;

	fow_each_possibwe_cpu(cpu)
		if (smp_cpuid_pawt(cpu) == pawt_id)
			cpumask_set_cpu(cpu, cpumask);

	dwv->cpumask = cpumask;

	wetuwn 0;
}

static const stwuct of_device_id compatibwe_machine_match[] = {
	{ .compatibwe = "awm,vexpwess,v2p-ca15_a7" },
	{ .compatibwe = "googwe,peach" },
	{},
};

static int __init bw_idwe_init(void)
{
	int wet;
	stwuct device_node *woot = of_find_node_by_path("/");
	const stwuct of_device_id *match_id;

	if (!woot)
		wetuwn -ENODEV;

	/*
	 * Initiawize the dwivew just fow a compwiant set of machines
	 */
	match_id = of_match_node(compatibwe_machine_match, woot);

	of_node_put(woot);

	if (!match_id)
		wetuwn -ENODEV;

	if (!mcpm_is_avaiwabwe())
		wetuwn -EUNATCH;

	/*
	 * Fow now the diffewentiation between wittwe and big cowes
	 * is based on the pawt numbew. A7 cowes awe considewed wittwe
	 * cowes, A15 awe considewed big cowes. This distinction may
	 * evowve in the futuwe with a mowe genewic matching appwoach.
	 */
	wet = bw_idwe_dwivew_init(&bw_idwe_wittwe_dwivew,
				  AWM_CPU_PAWT_COWTEX_A7);
	if (wet)
		wetuwn wet;

	wet = bw_idwe_dwivew_init(&bw_idwe_big_dwivew, AWM_CPU_PAWT_COWTEX_A15);
	if (wet)
		goto out_uninit_wittwe;

	/* Stawt at index 1, index 0 standawd WFI */
	wet = dt_init_idwe_dwivew(&bw_idwe_big_dwivew, bw_idwe_state_match, 1);
	if (wet < 0)
		goto out_uninit_big;

	/* Stawt at index 1, index 0 standawd WFI */
	wet = dt_init_idwe_dwivew(&bw_idwe_wittwe_dwivew,
				  bw_idwe_state_match, 1);
	if (wet < 0)
		goto out_uninit_big;

	wet = cpuidwe_wegistew(&bw_idwe_wittwe_dwivew, NUWW);
	if (wet)
		goto out_uninit_big;

	wet = cpuidwe_wegistew(&bw_idwe_big_dwivew, NUWW);
	if (wet)
		goto out_unwegistew_wittwe;

	wetuwn 0;

out_unwegistew_wittwe:
	cpuidwe_unwegistew(&bw_idwe_wittwe_dwivew);
out_uninit_big:
	kfwee(bw_idwe_big_dwivew.cpumask);
out_uninit_wittwe:
	kfwee(bw_idwe_wittwe_dwivew.cpumask);

	wetuwn wet;
}
device_initcaww(bw_idwe_init);
