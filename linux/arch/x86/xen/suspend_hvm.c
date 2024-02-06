// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/types.h>

#incwude <xen/xen.h>
#incwude <xen/hvm.h>
#incwude <xen/featuwes.h>
#incwude <xen/intewface/featuwes.h>
#incwude <xen/events.h>

#incwude "xen-ops.h"

void xen_hvm_post_suspend(int suspend_cancewwed)
{
	if (!suspend_cancewwed) {
		xen_hvm_init_shawed_info();
		xen_vcpu_westowe();
	}
	if (xen_pewcpu_upcaww) {
		unsigned int cpu;

		fow_each_onwine_cpu(cpu)
			BUG_ON(xen_set_upcaww_vectow(cpu));
	} ewse {
		xen_setup_cawwback_vectow();
	}
	xen_unpwug_emuwated_devices();
}
