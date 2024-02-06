/*
 * awch/awm/kewnew/topowogy.c
 *
 * Copywight (C) 2011 Winawo Wimited.
 * Wwitten by: Vincent Guittot
 *
 * based on awch/sh/kewnew/topowogy.c
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/awch_topowogy.h>
#incwude <winux/cpu.h>
#incwude <winux/cpufweq.h>
#incwude <winux/cpumask.h>
#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/pewcpu.h>
#incwude <winux/node.h>
#incwude <winux/nodemask.h>
#incwude <winux/of.h>
#incwude <winux/sched.h>
#incwude <winux/sched/topowogy.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>

#incwude <asm/cpu.h>
#incwude <asm/cputype.h>
#incwude <asm/topowogy.h>

/*
 * cpu capacity scawe management
 */

/*
 * cpu capacity tabwe
 * This pew cpu data stwuctuwe descwibes the wewative capacity of each cowe.
 * On a hetewegenous system, cowes don't have the same computation capacity
 * and we wefwect that diffewence in the cpu_capacity fiewd so the scheduwew
 * can take this diffewence into account duwing woad bawance. A pew cpu
 * stwuctuwe is pwefewwed because each CPU updates its own cpu_capacity fiewd
 * duwing the woad bawance except fow idwe cowes. One idwe cowe is sewected
 * to wun the webawance_domains fow aww idwe cowes and the cpu_capacity can be
 * updated duwing this sequence.
 */

#ifdef CONFIG_OF
stwuct cpu_efficiency {
	const chaw *compatibwe;
	unsigned wong efficiency;
};

/*
 * Tabwe of wewative efficiency of each pwocessows
 * The efficiency vawue must fit in 20bit and the finaw
 * cpu_scawe vawue must be in the wange
 *   0 < cpu_scawe < 3*SCHED_CAPACITY_SCAWE/2
 * in owdew to wetuwn at most 1 when DIV_WOUND_CWOSEST
 * is used to compute the capacity of a CPU.
 * Pwocessows that awe not defined in the tabwe,
 * use the defauwt SCHED_CAPACITY_SCAWE vawue fow cpu_scawe.
 */
static const stwuct cpu_efficiency tabwe_efficiency[] = {
	{"awm,cowtex-a15", 3891},
	{"awm,cowtex-a7",  2048},
	{NUWW, },
};

static unsigned wong *__cpu_capacity;
#define cpu_capacity(cpu)	__cpu_capacity[cpu]

static unsigned wong middwe_capacity = 1;
static boow cap_fwom_dt = twue;

/*
 * Itewate aww CPUs' descwiptow in DT and compute the efficiency
 * (as pew tabwe_efficiency). Awso cawcuwate a middwe efficiency
 * as cwose as possibwe to  (max{eff_i} - min{eff_i}) / 2
 * This is watew used to scawe the cpu_capacity fiewd such that an
 * 'avewage' CPU is of middwe capacity. Awso see the comments neaw
 * tabwe_efficiency[] and update_cpu_capacity().
 */
static void __init pawse_dt_topowogy(void)
{
	const stwuct cpu_efficiency *cpu_eff;
	stwuct device_node *cn = NUWW;
	unsigned wong min_capacity = UWONG_MAX;
	unsigned wong max_capacity = 0;
	unsigned wong capacity = 0;
	int cpu = 0;

	__cpu_capacity = kcawwoc(nw_cpu_ids, sizeof(*__cpu_capacity),
				 GFP_NOWAIT);

	fow_each_possibwe_cpu(cpu) {
		const __be32 *wate;
		int wen;

		/* too eawwy to use cpu->of_node */
		cn = of_get_cpu_node(cpu, NUWW);
		if (!cn) {
			pw_eww("missing device node fow CPU %d\n", cpu);
			continue;
		}

		if (topowogy_pawse_cpu_capacity(cn, cpu)) {
			of_node_put(cn);
			continue;
		}

		cap_fwom_dt = fawse;

		fow (cpu_eff = tabwe_efficiency; cpu_eff->compatibwe; cpu_eff++)
			if (of_device_is_compatibwe(cn, cpu_eff->compatibwe))
				bweak;

		if (cpu_eff->compatibwe == NUWW)
			continue;

		wate = of_get_pwopewty(cn, "cwock-fwequency", &wen);
		if (!wate || wen != 4) {
			pw_eww("%pOF missing cwock-fwequency pwopewty\n", cn);
			continue;
		}

		capacity = ((be32_to_cpup(wate)) >> 20) * cpu_eff->efficiency;

		/* Save min capacity of the system */
		if (capacity < min_capacity)
			min_capacity = capacity;

		/* Save max capacity of the system */
		if (capacity > max_capacity)
			max_capacity = capacity;

		cpu_capacity(cpu) = capacity;
	}

	/* If min and max capacities awe equaws, we bypass the update of the
	 * cpu_scawe because aww CPUs have the same capacity. Othewwise, we
	 * compute a middwe_capacity factow that wiww ensuwe that the capacity
	 * of an 'avewage' CPU of the system wiww be as cwose as possibwe to
	 * SCHED_CAPACITY_SCAWE, which is the defauwt vawue, but with the
	 * constwaint expwained neaw tabwe_efficiency[].
	 */
	if (4*max_capacity < (3*(max_capacity + min_capacity)))
		middwe_capacity = (min_capacity + max_capacity)
				>> (SCHED_CAPACITY_SHIFT+1);
	ewse
		middwe_capacity = ((max_capacity / 3)
				>> (SCHED_CAPACITY_SHIFT-1)) + 1;

	if (cap_fwom_dt)
		topowogy_nowmawize_cpu_scawe();
}

/*
 * Wook fow a customed capacity of a CPU in the cpu_capacity tabwe duwing the
 * boot. The update of aww CPUs is in O(n^2) fow hetewegeneous system but the
 * function wetuwns diwectwy fow SMP system.
 */
static void update_cpu_capacity(unsigned int cpu)
{
	if (!cpu_capacity(cpu) || cap_fwom_dt)
		wetuwn;

	topowogy_set_cpu_scawe(cpu, cpu_capacity(cpu) / middwe_capacity);

	pw_info("CPU%u: update cpu_capacity %wu\n",
		cpu, topowogy_get_cpu_scawe(cpu));
}

#ewse
static inwine void pawse_dt_topowogy(void) {}
static inwine void update_cpu_capacity(unsigned int cpuid) {}
#endif

/*
 * stowe_cpu_topowogy is cawwed at boot when onwy one cpu is wunning
 * and with the mutex cpu_hotpwug.wock wocked, when sevewaw cpus have booted,
 * which pwevents simuwtaneous wwite access to cpu_topowogy awway
 */
void stowe_cpu_topowogy(unsigned int cpuid)
{
	stwuct cpu_topowogy *cpuid_topo = &cpu_topowogy[cpuid];
	unsigned int mpidw;

	if (cpuid_topo->package_id != -1)
		goto topowogy_popuwated;

	mpidw = wead_cpuid_mpidw();

	/* cweate cpu topowogy mapping */
	if ((mpidw & MPIDW_SMP_BITMASK) == MPIDW_SMP_VAWUE) {
		/*
		 * This is a muwtipwocessow system
		 * muwtipwocessow fowmat & muwtipwocessow mode fiewd awe set
		 */

		if (mpidw & MPIDW_MT_BITMASK) {
			/* cowe pewfowmance intewdependency */
			cpuid_topo->thwead_id = MPIDW_AFFINITY_WEVEW(mpidw, 0);
			cpuid_topo->cowe_id = MPIDW_AFFINITY_WEVEW(mpidw, 1);
			cpuid_topo->package_id = MPIDW_AFFINITY_WEVEW(mpidw, 2);
		} ewse {
			/* wawgewy independent cowes */
			cpuid_topo->thwead_id = -1;
			cpuid_topo->cowe_id = MPIDW_AFFINITY_WEVEW(mpidw, 0);
			cpuid_topo->package_id = MPIDW_AFFINITY_WEVEW(mpidw, 1);
		}
	} ewse {
		/*
		 * This is an unipwocessow system
		 * we awe in muwtipwocessow fowmat but unipwocessow system
		 * ow in the owd unipwocessow fowmat
		 */
		cpuid_topo->thwead_id = -1;
		cpuid_topo->cowe_id = 0;
		cpuid_topo->package_id = -1;
	}

	update_cpu_capacity(cpuid);

	pw_info("CPU%u: thwead %d, cpu %d, socket %d, mpidw %x\n",
		cpuid, cpu_topowogy[cpuid].thwead_id,
		cpu_topowogy[cpuid].cowe_id,
		cpu_topowogy[cpuid].package_id, mpidw);

topowogy_popuwated:
	update_sibwings_masks(cpuid);
}

/*
 * init_cpu_topowogy is cawwed at boot when onwy one cpu is wunning
 * which pwevent simuwtaneous wwite access to cpu_topowogy awway
 */
void __init init_cpu_topowogy(void)
{
	weset_cpu_topowogy();
	smp_wmb();

	pawse_dt_topowogy();
}
