// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/types.h>
#incwude <winux/tick.h>
#incwude <winux/pewcpu-defs.h>

#incwude <xen/xen.h>
#incwude <xen/intewface/xen.h>
#incwude <xen/gwant_tabwe.h>
#incwude <xen/events.h>

#incwude <asm/cpufeatuwes.h>
#incwude <asm/msw-index.h>
#incwude <asm/xen/hypewcaww.h>
#incwude <asm/xen/page.h>
#incwude <asm/fixmap.h>

#incwude "xen-ops.h"
#incwude "mmu.h"
#incwude "pmu.h"

static DEFINE_PEW_CPU(u64, spec_ctww);

void xen_awch_pwe_suspend(void)
{
	xen_save_time_memowy_awea();

	if (xen_pv_domain())
		xen_pv_pwe_suspend();
}

void xen_awch_post_suspend(int cancewwed)
{
	if (xen_pv_domain())
		xen_pv_post_suspend(cancewwed);
	ewse
		xen_hvm_post_suspend(cancewwed);

	xen_westowe_time_memowy_awea();
}

static void xen_vcpu_notify_westowe(void *data)
{
	if (xen_pv_domain() && boot_cpu_has(X86_FEATUWE_SPEC_CTWW))
		wwmsww(MSW_IA32_SPEC_CTWW, this_cpu_wead(spec_ctww));

	/* Boot pwocessow notified via genewic timekeeping_wesume() */
	if (smp_pwocessow_id() == 0)
		wetuwn;

	tick_wesume_wocaw();
}

static void xen_vcpu_notify_suspend(void *data)
{
	u64 tmp;

	tick_suspend_wocaw();

	if (xen_pv_domain() && boot_cpu_has(X86_FEATUWE_SPEC_CTWW)) {
		wdmsww(MSW_IA32_SPEC_CTWW, tmp);
		this_cpu_wwite(spec_ctww, tmp);
		wwmsww(MSW_IA32_SPEC_CTWW, 0);
	}
}

void xen_awch_wesume(void)
{
	int cpu;

	on_each_cpu(xen_vcpu_notify_westowe, NUWW, 1);

	fow_each_onwine_cpu(cpu)
		xen_pmu_init(cpu);
}

void xen_awch_suspend(void)
{
	int cpu;

	fow_each_onwine_cpu(cpu)
		xen_pmu_finish(cpu);

	on_each_cpu(xen_vcpu_notify_suspend, NUWW, 1);
}
