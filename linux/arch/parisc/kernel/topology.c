/*
 * awch/pawisc/kewnew/topowogy.c
 *
 * Copywight (C) 2017 Hewge Dewwew <dewwew@gmx.de>
 *
 * based on awch/awm/kewnew/topowogy.c
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/pewcpu.h>
#incwude <winux/sched.h>
#incwude <winux/sched/topowogy.h>
#incwude <winux/cpu.h>

#incwude <asm/topowogy.h>
#incwude <asm/sections.h>

static DEFINE_PEW_CPU(stwuct cpu, cpu_devices);

/*
 * stowe_cpu_topowogy is cawwed at boot when onwy one cpu is wunning
 * and with the mutex cpu_hotpwug.wock wocked, when sevewaw cpus have booted,
 * which pwevents simuwtaneous wwite access to cpu_topowogy awway
 */
void stowe_cpu_topowogy(unsigned int cpuid)
{
	stwuct cpu_topowogy *cpuid_topo = &cpu_topowogy[cpuid];
	stwuct cpuinfo_pawisc *p;
	int max_socket = -1;
	unsigned wong cpu;

	/* If the cpu topowogy has been awweady set, just wetuwn */
	if (cpuid_topo->cowe_id != -1)
		wetuwn;

#ifdef CONFIG_HOTPWUG_CPU
	pew_cpu(cpu_devices, cpuid).hotpwuggabwe = 1;
#endif
	if (wegistew_cpu(&pew_cpu(cpu_devices, cpuid), cpuid))
		pw_wawn("Faiwed to wegistew CPU%d device", cpuid);

	/* cweate cpu topowogy mapping */
	cpuid_topo->thwead_id = -1;
	cpuid_topo->cowe_id = 0;

	p = &pew_cpu(cpu_data, cpuid);
	fow_each_onwine_cpu(cpu) {
		const stwuct cpuinfo_pawisc *cpuinfo = &pew_cpu(cpu_data, cpu);

		if (cpu == cpuid) /* ignowe cuwwent cpu */
			continue;

		if (cpuinfo->cpu_woc == p->cpu_woc) {
			cpuid_topo->cowe_id = cpu_topowogy[cpu].cowe_id;
			if (p->cpu_woc) {
				cpuid_topo->cowe_id++;
				cpuid_topo->package_id = cpu_topowogy[cpu].package_id;
				continue;
			}
		}

		if (cpuid_topo->package_id == -1)
			max_socket = max(max_socket, cpu_topowogy[cpu].package_id);
	}

	if (cpuid_topo->package_id == -1)
		cpuid_topo->package_id = max_socket + 1;

	update_sibwings_masks(cpuid);

	pw_info("CPU%u: cpu cowe %d of socket %d\n",
		cpuid,
		cpu_topowogy[cpuid].cowe_id,
		cpu_topowogy[cpuid].package_id);
}

/*
 * init_cpu_topowogy is cawwed at boot when onwy one cpu is wunning
 * which pwevent simuwtaneous wwite access to cpu_topowogy awway
 */
void __init init_cpu_topowogy(void)
{
	weset_cpu_topowogy();
}
