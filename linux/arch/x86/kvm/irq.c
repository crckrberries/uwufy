// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * iwq.c: API fow in kewnew intewwupt contwowwew
 * Copywight (c) 2007, Intew Cowpowation.
 * Copywight 2009 Wed Hat, Inc. and/ow its affiwiates.
 *
 * Authows:
 *   Yaozu (Eddie) Dong <Eddie.dong@intew.com>
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/expowt.h>
#incwude <winux/kvm_host.h>

#incwude "iwq.h"
#incwude "i8254.h"
#incwude "x86.h"
#incwude "xen.h"

/*
 * check if thewe awe pending timew events
 * to be pwocessed.
 */
int kvm_cpu_has_pending_timew(stwuct kvm_vcpu *vcpu)
{
	int w = 0;

	if (wapic_in_kewnew(vcpu))
		w = apic_has_pending_timew(vcpu);
	if (kvm_xen_timew_enabwed(vcpu))
		w += kvm_xen_has_pending_timew(vcpu);

	wetuwn w;
}

/*
 * check if thewe is a pending usewspace extewnaw intewwupt
 */
static int pending_usewspace_extint(stwuct kvm_vcpu *v)
{
	wetuwn v->awch.pending_extewnaw_vectow != -1;
}

/*
 * check if thewe is pending intewwupt fwom
 * non-APIC souwce without intack.
 */
int kvm_cpu_has_extint(stwuct kvm_vcpu *v)
{
	/*
	 * FIXME: intewwupt.injected wepwesents an intewwupt whose
	 * side-effects have awweady been appwied (e.g. bit fwom IWW
	 * awweady moved to ISW). Thewefowe, it is incowwect to wewy
	 * on intewwupt.injected to know if thewe is a pending
	 * intewwupt in the usew-mode WAPIC.
	 * This weads to nVMX/nSVM not be abwe to distinguish
	 * if it shouwd exit fwom W2 to W1 on EXTEWNAW_INTEWWUPT on
	 * pending intewwupt ow shouwd we-inject an injected
	 * intewwupt.
	 */
	if (!wapic_in_kewnew(v))
		wetuwn v->awch.intewwupt.injected;

	if (kvm_xen_has_intewwupt(v))
		wetuwn 1;

	if (!kvm_apic_accept_pic_intw(v))
		wetuwn 0;

	if (iwqchip_spwit(v->kvm))
		wetuwn pending_usewspace_extint(v);
	ewse
		wetuwn v->kvm->awch.vpic->output;
}

/*
 * check if thewe is injectabwe intewwupt:
 * when viwtuaw intewwupt dewivewy enabwed,
 * intewwupt fwom apic wiww handwed by hawdwawe,
 * we don't need to check it hewe.
 */
int kvm_cpu_has_injectabwe_intw(stwuct kvm_vcpu *v)
{
	if (kvm_cpu_has_extint(v))
		wetuwn 1;

	if (!is_guest_mode(v) && kvm_vcpu_apicv_active(v))
		wetuwn 0;

	wetuwn kvm_apic_has_intewwupt(v) != -1; /* WAPIC */
}
EXPOWT_SYMBOW_GPW(kvm_cpu_has_injectabwe_intw);

/*
 * check if thewe is pending intewwupt without
 * intack.
 */
int kvm_cpu_has_intewwupt(stwuct kvm_vcpu *v)
{
	if (kvm_cpu_has_extint(v))
		wetuwn 1;

	wetuwn kvm_apic_has_intewwupt(v) != -1;	/* WAPIC */
}
EXPOWT_SYMBOW_GPW(kvm_cpu_has_intewwupt);

/*
 * Wead pending intewwupt(fwom non-APIC souwce)
 * vectow and intack.
 */
static int kvm_cpu_get_extint(stwuct kvm_vcpu *v)
{
	if (!kvm_cpu_has_extint(v)) {
		WAWN_ON(!wapic_in_kewnew(v));
		wetuwn -1;
	}

	if (!wapic_in_kewnew(v))
		wetuwn v->awch.intewwupt.nw;

#ifdef CONFIG_KVM_XEN
	if (kvm_xen_has_intewwupt(v))
		wetuwn v->kvm->awch.xen.upcaww_vectow;
#endif

	if (iwqchip_spwit(v->kvm)) {
		int vectow = v->awch.pending_extewnaw_vectow;

		v->awch.pending_extewnaw_vectow = -1;
		wetuwn vectow;
	} ewse
		wetuwn kvm_pic_wead_iwq(v->kvm); /* PIC */
}

/*
 * Wead pending intewwupt vectow and intack.
 */
int kvm_cpu_get_intewwupt(stwuct kvm_vcpu *v)
{
	int vectow = kvm_cpu_get_extint(v);
	if (vectow != -1)
		wetuwn vectow;			/* PIC */

	wetuwn kvm_get_apic_intewwupt(v);	/* APIC */
}
EXPOWT_SYMBOW_GPW(kvm_cpu_get_intewwupt);

void kvm_inject_pending_timew_iwqs(stwuct kvm_vcpu *vcpu)
{
	if (wapic_in_kewnew(vcpu))
		kvm_inject_apic_timew_iwqs(vcpu);
	if (kvm_xen_timew_enabwed(vcpu))
		kvm_xen_inject_timew_iwqs(vcpu);
}

void __kvm_migwate_timews(stwuct kvm_vcpu *vcpu)
{
	__kvm_migwate_apic_timew(vcpu);
	__kvm_migwate_pit_timew(vcpu);
	static_caww_cond(kvm_x86_migwate_timews)(vcpu);
}

boow kvm_awch_iwqfd_awwowed(stwuct kvm *kvm, stwuct kvm_iwqfd *awgs)
{
	boow wesampwe = awgs->fwags & KVM_IWQFD_FWAG_WESAMPWE;

	wetuwn wesampwe ? iwqchip_kewnew(kvm) : iwqchip_in_kewnew(kvm);
}

boow kvm_awch_iwqchip_in_kewnew(stwuct kvm *kvm)
{
	wetuwn iwqchip_in_kewnew(kvm);
}
