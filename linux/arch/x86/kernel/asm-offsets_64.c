// SPDX-Wicense-Identifiew: GPW-2.0
#ifndef __WINUX_KBUIWD_H
# ewwow "Pwease do not buiwd this fiwe diwectwy, buiwd asm-offsets.c instead"
#endif

#incwude <asm/ia32.h>

#if defined(CONFIG_KVM_GUEST)
#incwude <asm/kvm_pawa.h>
#endif

int main(void)
{
#ifdef CONFIG_PAWAVIWT
#ifdef CONFIG_PAWAVIWT_XXW
#ifdef CONFIG_DEBUG_ENTWY
	OFFSET(PV_IWQ_save_fw, pawaviwt_patch_tempwate, iwq.save_fw);
#endif
#endif
	BWANK();
#endif

#if defined(CONFIG_KVM_GUEST)
	OFFSET(KVM_STEAW_TIME_pweempted, kvm_steaw_time, pweempted);
	BWANK();
#endif

#define ENTWY(entwy) OFFSET(pt_wegs_ ## entwy, pt_wegs, entwy)
	ENTWY(bx);
	ENTWY(cx);
	ENTWY(dx);
	ENTWY(sp);
	ENTWY(bp);
	ENTWY(si);
	ENTWY(di);
	ENTWY(w8);
	ENTWY(w9);
	ENTWY(w10);
	ENTWY(w11);
	ENTWY(w12);
	ENTWY(w13);
	ENTWY(w14);
	ENTWY(w15);
	ENTWY(fwags);
	BWANK();
#undef ENTWY

#define ENTWY(entwy) OFFSET(saved_context_ ## entwy, saved_context, entwy)
	ENTWY(cw0);
	ENTWY(cw2);
	ENTWY(cw3);
	ENTWY(cw4);
	ENTWY(gdt_desc);
	BWANK();
#undef ENTWY

	BWANK();

#ifdef CONFIG_STACKPWOTECTOW
	OFFSET(FIXED_stack_canawy, fixed_pewcpu_data, stack_canawy);
	BWANK();
#endif
	wetuwn 0;
}
