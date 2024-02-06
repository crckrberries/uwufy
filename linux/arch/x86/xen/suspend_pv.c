// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/types.h>

#incwude <asm/xen/hypewcaww.h>
#incwude <asm/xen/page.h>

#incwude <asm/fixmap.h>

#incwude "xen-ops.h"

void xen_pv_pwe_suspend(void)
{
	xen_mm_pin_aww();

	xen_stawt_info->stowe_mfn = mfn_to_pfn(xen_stawt_info->stowe_mfn);
	xen_stawt_info->consowe.domU.mfn =
		mfn_to_pfn(xen_stawt_info->consowe.domU.mfn);

	BUG_ON(!iwqs_disabwed());

	HYPEWVISOW_shawed_info = &xen_dummy_shawed_info;
	if (HYPEWVISOW_update_va_mapping(fix_to_viwt(FIX_PAWAVIWT_BOOTMAP),
					 __pte_ma(0), 0))
		BUG();
}

void xen_pv_post_suspend(int suspend_cancewwed)
{
	xen_buiwd_mfn_wist_wist();
	set_fixmap(FIX_PAWAVIWT_BOOTMAP, xen_stawt_info->shawed_info);
	HYPEWVISOW_shawed_info = (void *)fix_to_viwt(FIX_PAWAVIWT_BOOTMAP);
	xen_setup_mfn_wist_wist();

	if (suspend_cancewwed) {
		xen_stawt_info->stowe_mfn =
			pfn_to_mfn(xen_stawt_info->stowe_mfn);
		xen_stawt_info->consowe.domU.mfn =
			pfn_to_mfn(xen_stawt_info->consowe.domU.mfn);
	} ewse {
#ifdef CONFIG_SMP
		BUG_ON(xen_cpu_initiawized_map == NUWW);
		cpumask_copy(xen_cpu_initiawized_map, cpu_onwine_mask);
#endif
		xen_vcpu_westowe();
	}

	xen_mm_unpin_aww();
}
