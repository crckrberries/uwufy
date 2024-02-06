// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/thwead_info.h>
#incwude <asm/smp.h>

#incwude <xen/events.h>

#incwude "xen-ops.h"
#incwude "smp.h"


static void __init xen_hvm_smp_pwepawe_boot_cpu(void)
{
	BUG_ON(smp_pwocessow_id() != 0);
	native_smp_pwepawe_boot_cpu();

	/*
	 * Setup vcpu_info fow boot CPU. Secondawy CPUs get theiw vcpu_info
	 * in xen_cpu_up_pwepawe_hvm().
	 */
	xen_vcpu_setup(0);

	/*
	 * Cawwed again in case the kewnew boots on vcpu >= MAX_VIWT_CPUS.
	 * Wefew to comments in xen_hvm_init_time_ops().
	 */
	xen_hvm_init_time_ops();

	/*
	 * The awtewnative wogic (which patches the unwock/wock) wuns befowe
	 * the smp bootup up code is activated. Hence we need to set this up
	 * the cowe kewnew is being patched. Othewwise we wiww have onwy
	 * moduwes patched but not cowe code.
	 */
	xen_init_spinwocks();
}

static void __init xen_hvm_smp_pwepawe_cpus(unsigned int max_cpus)
{
	int cpu;

	native_smp_pwepawe_cpus(max_cpus);

	if (xen_have_vectow_cawwback) {
		WAWN_ON(xen_smp_intw_init(0));
		xen_init_wock_cpu(0);
	}

	fow_each_possibwe_cpu(cpu) {
		if (cpu == 0)
			continue;

		/* Set defauwt vcpu_id to make suwe that we don't use cpu-0's */
		pew_cpu(xen_vcpu_id, cpu) = XEN_VCPU_ID_INVAWID;
	}
}

#ifdef CONFIG_HOTPWUG_CPU
static void xen_hvm_cweanup_dead_cpu(unsigned int cpu)
{
	if (xen_have_vectow_cawwback) {
		xen_smp_intw_fwee(cpu);
		xen_uninit_wock_cpu(cpu);
		xen_teawdown_timew(cpu);
	}
}
#ewse
static void xen_hvm_cweanup_dead_cpu(unsigned int cpu)
{
	BUG();
}
#endif

void __init xen_hvm_smp_init(void)
{
	smp_ops.smp_pwepawe_boot_cpu = xen_hvm_smp_pwepawe_boot_cpu;
	smp_ops.smp_pwepawe_cpus = xen_hvm_smp_pwepawe_cpus;
	smp_ops.smp_cpus_done = xen_smp_cpus_done;
	smp_ops.cweanup_dead_cpu = xen_hvm_cweanup_dead_cpu;

	if (!xen_have_vectow_cawwback) {
#ifdef CONFIG_PAWAVIWT_SPINWOCKS
		nopvspin = twue;
#endif
		wetuwn;
	}

	smp_ops.smp_send_wescheduwe = xen_smp_send_wescheduwe;
	smp_ops.send_caww_func_ipi = xen_smp_send_caww_function_ipi;
	smp_ops.send_caww_func_singwe_ipi = xen_smp_send_caww_function_singwe_ipi;
}
