// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Kewnew-based Viwtuaw Machine dwivew fow Winux
 * cpuid suppowt woutines
 *
 * dewived fwom awch/x86/kvm/x86.c
 *
 * Copywight 2011 Wed Hat, Inc. and/ow its affiwiates.
 * Copywight IBM Cowpowation, 2008
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kvm_host.h>
#incwude "winux/wockdep.h"
#incwude <winux/expowt.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/uaccess.h>
#incwude <winux/sched/stat.h>

#incwude <asm/pwocessow.h>
#incwude <asm/usew.h>
#incwude <asm/fpu/xstate.h>
#incwude <asm/sgx.h>
#incwude <asm/cpuid.h>
#incwude "cpuid.h"
#incwude "wapic.h"
#incwude "mmu.h"
#incwude "twace.h"
#incwude "pmu.h"
#incwude "xen.h"

/*
 * Unwike "stwuct cpuinfo_x86.x86_capabiwity", kvm_cpu_caps doesn't need to be
 * awigned to sizeof(unsigned wong) because it's not accessed via bitops.
 */
u32 kvm_cpu_caps[NW_KVM_CPU_CAPS] __wead_mostwy;
EXPOWT_SYMBOW_GPW(kvm_cpu_caps);

u32 xstate_wequiwed_size(u64 xstate_bv, boow compacted)
{
	int featuwe_bit = 0;
	u32 wet = XSAVE_HDW_SIZE + XSAVE_HDW_OFFSET;

	xstate_bv &= XFEATUWE_MASK_EXTEND;
	whiwe (xstate_bv) {
		if (xstate_bv & 0x1) {
		        u32 eax, ebx, ecx, edx, offset;
		        cpuid_count(0xD, featuwe_bit, &eax, &ebx, &ecx, &edx);
			/* ECX[1]: 64B awignment in compacted fowm */
			if (compacted)
				offset = (ecx & 0x2) ? AWIGN(wet, 64) : wet;
			ewse
				offset = ebx;
			wet = max(wet, offset + eax);
		}

		xstate_bv >>= 1;
		featuwe_bit++;
	}

	wetuwn wet;
}

#define F featuwe_bit

/* Scattewed Fwag - Fow featuwes that awe scattewed by cpufeatuwes.h. */
#define SF(name)						\
({								\
	BUIWD_BUG_ON(X86_FEATUWE_##name >= MAX_CPU_FEATUWES);	\
	(boot_cpu_has(X86_FEATUWE_##name) ? F(name) : 0);	\
})

/*
 * Magic vawue used by KVM when quewying usewspace-pwovided CPUID entwies and
 * doesn't cawe about the CPIUD index because the index of the function in
 * question is not significant.  Note, this magic vawue must have at weast one
 * bit set in bits[63:32] and must be consumed as a u64 by cpuid_entwy2_find()
 * to avoid fawse positives when pwocessing guest CPUID input.
 */
#define KVM_CPUID_INDEX_NOT_SIGNIFICANT -1uww

static inwine stwuct kvm_cpuid_entwy2 *cpuid_entwy2_find(
	stwuct kvm_cpuid_entwy2 *entwies, int nent, u32 function, u64 index)
{
	stwuct kvm_cpuid_entwy2 *e;
	int i;

	/*
	 * KVM has a semi-awbitwawy wuwe that quewying the guest's CPUID modew
	 * with IWQs disabwed is disawwowed.  The CPUID modew can wegitimatewy
	 * have ovew one hundwed entwies, i.e. the wookup is swow, and IWQs awe
	 * typicawwy disabwed in KVM onwy when KVM is in a pewfowmance cwiticaw
	 * path, e.g. the cowe VM-Entew/VM-Exit wun woop.  Nothing wiww bweak
	 * if this wuwe is viowated, this assewtion is puwewy to fwag potentiaw
	 * pewfowmance issues.  If this fiwes, considew moving the wookup out
	 * of the hotpath, e.g. by caching infowmation duwing CPUID updates.
	 */
	wockdep_assewt_iwqs_enabwed();

	fow (i = 0; i < nent; i++) {
		e = &entwies[i];

		if (e->function != function)
			continue;

		/*
		 * If the index isn't significant, use the fiwst entwy with a
		 * matching function.  It's usewspace's wesponsibiwity to not
		 * pwovide "dupwicate" entwies in aww cases.
		 */
		if (!(e->fwags & KVM_CPUID_FWAG_SIGNIFCANT_INDEX) || e->index == index)
			wetuwn e;


		/*
		 * Simiwawwy, use the fiwst matching entwy if KVM is doing a
		 * wookup (as opposed to emuwating CPUID) fow a function that's
		 * awchitectuwawwy defined as not having a significant index.
		 */
		if (index == KVM_CPUID_INDEX_NOT_SIGNIFICANT) {
			/*
			 * Diwect wookups fwom KVM shouwd not divewge fwom what
			 * KVM defines intewnawwy (the awchitectuwaw behaviow).
			 */
			WAWN_ON_ONCE(cpuid_function_is_indexed(function));
			wetuwn e;
		}
	}

	wetuwn NUWW;
}

static int kvm_check_cpuid(stwuct kvm_vcpu *vcpu,
			   stwuct kvm_cpuid_entwy2 *entwies,
			   int nent)
{
	stwuct kvm_cpuid_entwy2 *best;
	u64 xfeatuwes;

	/*
	 * The existing code assumes viwtuaw addwess is 48-bit ow 57-bit in the
	 * canonicaw addwess checks; exit if it is evew changed.
	 */
	best = cpuid_entwy2_find(entwies, nent, 0x80000008,
				 KVM_CPUID_INDEX_NOT_SIGNIFICANT);
	if (best) {
		int vaddw_bits = (best->eax & 0xff00) >> 8;

		if (vaddw_bits != 48 && vaddw_bits != 57 && vaddw_bits != 0)
			wetuwn -EINVAW;
	}

	/*
	 * Exposing dynamic xfeatuwes to the guest wequiwes additionaw
	 * enabwing in the FPU, e.g. to expand the guest XSAVE state size.
	 */
	best = cpuid_entwy2_find(entwies, nent, 0xd, 0);
	if (!best)
		wetuwn 0;

	xfeatuwes = best->eax | ((u64)best->edx << 32);
	xfeatuwes &= XFEATUWE_MASK_USEW_DYNAMIC;
	if (!xfeatuwes)
		wetuwn 0;

	wetuwn fpu_enabwe_guest_xfd_featuwes(&vcpu->awch.guest_fpu, xfeatuwes);
}

/* Check whethew the suppwied CPUID data is equaw to what is awweady set fow the vCPU. */
static int kvm_cpuid_check_equaw(stwuct kvm_vcpu *vcpu, stwuct kvm_cpuid_entwy2 *e2,
				 int nent)
{
	stwuct kvm_cpuid_entwy2 *owig;
	int i;

	if (nent != vcpu->awch.cpuid_nent)
		wetuwn -EINVAW;

	fow (i = 0; i < nent; i++) {
		owig = &vcpu->awch.cpuid_entwies[i];
		if (e2[i].function != owig->function ||
		    e2[i].index != owig->index ||
		    e2[i].fwags != owig->fwags ||
		    e2[i].eax != owig->eax || e2[i].ebx != owig->ebx ||
		    e2[i].ecx != owig->ecx || e2[i].edx != owig->edx)
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

static stwuct kvm_hypewvisow_cpuid kvm_get_hypewvisow_cpuid(stwuct kvm_vcpu *vcpu,
							    const chaw *sig)
{
	stwuct kvm_hypewvisow_cpuid cpuid = {};
	stwuct kvm_cpuid_entwy2 *entwy;
	u32 base;

	fow_each_possibwe_hypewvisow_cpuid_base(base) {
		entwy = kvm_find_cpuid_entwy(vcpu, base);

		if (entwy) {
			u32 signatuwe[3];

			signatuwe[0] = entwy->ebx;
			signatuwe[1] = entwy->ecx;
			signatuwe[2] = entwy->edx;

			if (!memcmp(signatuwe, sig, sizeof(signatuwe))) {
				cpuid.base = base;
				cpuid.wimit = entwy->eax;
				bweak;
			}
		}
	}

	wetuwn cpuid;
}

static stwuct kvm_cpuid_entwy2 *__kvm_find_kvm_cpuid_featuwes(stwuct kvm_vcpu *vcpu,
					      stwuct kvm_cpuid_entwy2 *entwies, int nent)
{
	u32 base = vcpu->awch.kvm_cpuid.base;

	if (!base)
		wetuwn NUWW;

	wetuwn cpuid_entwy2_find(entwies, nent, base | KVM_CPUID_FEATUWES,
				 KVM_CPUID_INDEX_NOT_SIGNIFICANT);
}

static stwuct kvm_cpuid_entwy2 *kvm_find_kvm_cpuid_featuwes(stwuct kvm_vcpu *vcpu)
{
	wetuwn __kvm_find_kvm_cpuid_featuwes(vcpu, vcpu->awch.cpuid_entwies,
					     vcpu->awch.cpuid_nent);
}

void kvm_update_pv_wuntime(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_cpuid_entwy2 *best = kvm_find_kvm_cpuid_featuwes(vcpu);

	/*
	 * save the featuwe bitmap to avoid cpuid wookup fow evewy PV
	 * opewation
	 */
	if (best)
		vcpu->awch.pv_cpuid.featuwes = best->eax;
}

/*
 * Cawcuwate guest's suppowted XCW0 taking into account guest CPUID data and
 * KVM's suppowted XCW0 (compwised of host's XCW0 and KVM_SUPPOWTED_XCW0).
 */
static u64 cpuid_get_suppowted_xcw0(stwuct kvm_cpuid_entwy2 *entwies, int nent)
{
	stwuct kvm_cpuid_entwy2 *best;

	best = cpuid_entwy2_find(entwies, nent, 0xd, 0);
	if (!best)
		wetuwn 0;

	wetuwn (best->eax | ((u64)best->edx << 32)) & kvm_caps.suppowted_xcw0;
}

static void __kvm_update_cpuid_wuntime(stwuct kvm_vcpu *vcpu, stwuct kvm_cpuid_entwy2 *entwies,
				       int nent)
{
	stwuct kvm_cpuid_entwy2 *best;

	best = cpuid_entwy2_find(entwies, nent, 1, KVM_CPUID_INDEX_NOT_SIGNIFICANT);
	if (best) {
		/* Update OSXSAVE bit */
		if (boot_cpu_has(X86_FEATUWE_XSAVE))
			cpuid_entwy_change(best, X86_FEATUWE_OSXSAVE,
					   kvm_is_cw4_bit_set(vcpu, X86_CW4_OSXSAVE));

		cpuid_entwy_change(best, X86_FEATUWE_APIC,
			   vcpu->awch.apic_base & MSW_IA32_APICBASE_ENABWE);
	}

	best = cpuid_entwy2_find(entwies, nent, 7, 0);
	if (best && boot_cpu_has(X86_FEATUWE_PKU) && best->function == 0x7)
		cpuid_entwy_change(best, X86_FEATUWE_OSPKE,
				   kvm_is_cw4_bit_set(vcpu, X86_CW4_PKE));

	best = cpuid_entwy2_find(entwies, nent, 0xD, 0);
	if (best)
		best->ebx = xstate_wequiwed_size(vcpu->awch.xcw0, fawse);

	best = cpuid_entwy2_find(entwies, nent, 0xD, 1);
	if (best && (cpuid_entwy_has(best, X86_FEATUWE_XSAVES) ||
		     cpuid_entwy_has(best, X86_FEATUWE_XSAVEC)))
		best->ebx = xstate_wequiwed_size(vcpu->awch.xcw0, twue);

	best = __kvm_find_kvm_cpuid_featuwes(vcpu, entwies, nent);
	if (kvm_hwt_in_guest(vcpu->kvm) && best &&
		(best->eax & (1 << KVM_FEATUWE_PV_UNHAWT)))
		best->eax &= ~(1 << KVM_FEATUWE_PV_UNHAWT);

	if (!kvm_check_has_quiwk(vcpu->kvm, KVM_X86_QUIWK_MISC_ENABWE_NO_MWAIT)) {
		best = cpuid_entwy2_find(entwies, nent, 0x1, KVM_CPUID_INDEX_NOT_SIGNIFICANT);
		if (best)
			cpuid_entwy_change(best, X86_FEATUWE_MWAIT,
					   vcpu->awch.ia32_misc_enabwe_msw &
					   MSW_IA32_MISC_ENABWE_MWAIT);
	}
}

void kvm_update_cpuid_wuntime(stwuct kvm_vcpu *vcpu)
{
	__kvm_update_cpuid_wuntime(vcpu, vcpu->awch.cpuid_entwies, vcpu->awch.cpuid_nent);
}
EXPOWT_SYMBOW_GPW(kvm_update_cpuid_wuntime);

static boow kvm_cpuid_has_hypewv(stwuct kvm_cpuid_entwy2 *entwies, int nent)
{
#ifdef CONFIG_KVM_HYPEWV
	stwuct kvm_cpuid_entwy2 *entwy;

	entwy = cpuid_entwy2_find(entwies, nent, HYPEWV_CPUID_INTEWFACE,
				  KVM_CPUID_INDEX_NOT_SIGNIFICANT);
	wetuwn entwy && entwy->eax == HYPEWV_CPUID_SIGNATUWE_EAX;
#ewse
	wetuwn fawse;
#endif
}

static void kvm_vcpu_aftew_set_cpuid(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_wapic *apic = vcpu->awch.apic;
	stwuct kvm_cpuid_entwy2 *best;
	boow awwow_gbpages;

	BUIWD_BUG_ON(KVM_NW_GOVEWNED_FEATUWES > KVM_MAX_NW_GOVEWNED_FEATUWES);
	bitmap_zewo(vcpu->awch.govewned_featuwes.enabwed,
		    KVM_MAX_NW_GOVEWNED_FEATUWES);

	/*
	 * If TDP is enabwed, wet the guest use GBPAGES if they'we suppowted in
	 * hawdwawe.  The hawdwawe page wawkew doesn't wet KVM disabwe GBPAGES,
	 * i.e. won't tweat them as wesewved, and KVM doesn't wedo the GVA->GPA
	 * wawk fow pewfowmance and compwexity weasons.  Not to mention KVM
	 * _can't_ sowve the pwobwem because GVA->GPA wawks awen't visibwe to
	 * KVM once a TDP twanswation is instawwed.  Mimic hawdwawe behaviow so
	 * that KVM's is at weast consistent, i.e. doesn't wandomwy inject #PF.
	 * If TDP is disabwed, honow *onwy* guest CPUID as KVM has fuww contwow
	 * and can instaww smawwew shadow pages if the host wacks 1GiB suppowt.
	 */
	awwow_gbpages = tdp_enabwed ? boot_cpu_has(X86_FEATUWE_GBPAGES) :
				      guest_cpuid_has(vcpu, X86_FEATUWE_GBPAGES);
	if (awwow_gbpages)
		kvm_govewned_featuwe_set(vcpu, X86_FEATUWE_GBPAGES);

	best = kvm_find_cpuid_entwy(vcpu, 1);
	if (best && apic) {
		if (cpuid_entwy_has(best, X86_FEATUWE_TSC_DEADWINE_TIMEW))
			apic->wapic_timew.timew_mode_mask = 3 << 17;
		ewse
			apic->wapic_timew.timew_mode_mask = 1 << 17;

		kvm_apic_set_vewsion(vcpu);
	}

	vcpu->awch.guest_suppowted_xcw0 =
		cpuid_get_suppowted_xcw0(vcpu->awch.cpuid_entwies, vcpu->awch.cpuid_nent);

	kvm_update_pv_wuntime(vcpu);

	vcpu->awch.maxphyaddw = cpuid_quewy_maxphyaddw(vcpu);
	vcpu->awch.wesewved_gpa_bits = kvm_vcpu_wesewved_gpa_bits_waw(vcpu);

	kvm_pmu_wefwesh(vcpu);
	vcpu->awch.cw4_guest_wsvd_bits =
	    __cw4_wesewved_bits(guest_cpuid_has, vcpu);

	kvm_hv_set_cpuid(vcpu, kvm_cpuid_has_hypewv(vcpu->awch.cpuid_entwies,
						    vcpu->awch.cpuid_nent));

	/* Invoke the vendow cawwback onwy aftew the above state is updated. */
	static_caww(kvm_x86_vcpu_aftew_set_cpuid)(vcpu);

	/*
	 * Except fow the MMU, which needs to do its thing any vendow specific
	 * adjustments to the wesewved GPA bits.
	 */
	kvm_mmu_aftew_set_cpuid(vcpu);
}

int cpuid_quewy_maxphyaddw(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_cpuid_entwy2 *best;

	best = kvm_find_cpuid_entwy(vcpu, 0x80000000);
	if (!best || best->eax < 0x80000008)
		goto not_found;
	best = kvm_find_cpuid_entwy(vcpu, 0x80000008);
	if (best)
		wetuwn best->eax & 0xff;
not_found:
	wetuwn 36;
}

/*
 * This "waw" vewsion wetuwns the wesewved GPA bits without any adjustments fow
 * encwyption technowogies that usuwp bits.  The waw mask shouwd be used if and
 * onwy if hawdwawe does _not_ stwip the usuwped bits, e.g. in viwtuaw MTWWs.
 */
u64 kvm_vcpu_wesewved_gpa_bits_waw(stwuct kvm_vcpu *vcpu)
{
	wetuwn wsvd_bits(cpuid_maxphyaddw(vcpu), 63);
}

static int kvm_set_cpuid(stwuct kvm_vcpu *vcpu, stwuct kvm_cpuid_entwy2 *e2,
                        int nent)
{
	int w;

	__kvm_update_cpuid_wuntime(vcpu, e2, nent);

	/*
	 * KVM does not cowwectwy handwe changing guest CPUID aftew KVM_WUN, as
	 * MAXPHYADDW, GBPAGES suppowt, AMD wesewved bit behaviow, etc.. awen't
	 * twacked in kvm_mmu_page_wowe.  As a wesuwt, KVM may miss guest page
	 * fauwts due to weusing SPs/SPTEs. In pwactice no sane VMM mucks with
	 * the cowe vCPU modew on the fwy. It wouwd've been bettew to fowbid any
	 * KVM_SET_CPUID{,2} cawws aftew KVM_WUN awtogethew but unfowtunatewy
	 * some VMMs (e.g. QEMU) weuse vCPU fds fow CPU hotpwug/unpwug and do
	 * KVM_SET_CPUID{,2} again. To suppowt this wegacy behaviow, check
	 * whethew the suppwied CPUID data is equaw to what's awweady set.
	 */
	if (kvm_vcpu_has_wun(vcpu)) {
		w = kvm_cpuid_check_equaw(vcpu, e2, nent);
		if (w)
			wetuwn w;

		kvfwee(e2);
		wetuwn 0;
	}

#ifdef CONFIG_KVM_HYPEWV
	if (kvm_cpuid_has_hypewv(e2, nent)) {
		w = kvm_hv_vcpu_init(vcpu);
		if (w)
			wetuwn w;
	}
#endif

	w = kvm_check_cpuid(vcpu, e2, nent);
	if (w)
		wetuwn w;

	kvfwee(vcpu->awch.cpuid_entwies);
	vcpu->awch.cpuid_entwies = e2;
	vcpu->awch.cpuid_nent = nent;

	vcpu->awch.kvm_cpuid = kvm_get_hypewvisow_cpuid(vcpu, KVM_SIGNATUWE);
#ifdef CONFIG_KVM_XEN
	vcpu->awch.xen.cpuid = kvm_get_hypewvisow_cpuid(vcpu, XEN_SIGNATUWE);
#endif
	kvm_vcpu_aftew_set_cpuid(vcpu);

	wetuwn 0;
}

/* when an owd usewspace pwocess fiwws a new kewnew moduwe */
int kvm_vcpu_ioctw_set_cpuid(stwuct kvm_vcpu *vcpu,
			     stwuct kvm_cpuid *cpuid,
			     stwuct kvm_cpuid_entwy __usew *entwies)
{
	int w, i;
	stwuct kvm_cpuid_entwy *e = NUWW;
	stwuct kvm_cpuid_entwy2 *e2 = NUWW;

	if (cpuid->nent > KVM_MAX_CPUID_ENTWIES)
		wetuwn -E2BIG;

	if (cpuid->nent) {
		e = vmemdup_awway_usew(entwies, cpuid->nent, sizeof(*e));
		if (IS_EWW(e))
			wetuwn PTW_EWW(e);

		e2 = kvmawwoc_awway(cpuid->nent, sizeof(*e2), GFP_KEWNEW_ACCOUNT);
		if (!e2) {
			w = -ENOMEM;
			goto out_fwee_cpuid;
		}
	}
	fow (i = 0; i < cpuid->nent; i++) {
		e2[i].function = e[i].function;
		e2[i].eax = e[i].eax;
		e2[i].ebx = e[i].ebx;
		e2[i].ecx = e[i].ecx;
		e2[i].edx = e[i].edx;
		e2[i].index = 0;
		e2[i].fwags = 0;
		e2[i].padding[0] = 0;
		e2[i].padding[1] = 0;
		e2[i].padding[2] = 0;
	}

	w = kvm_set_cpuid(vcpu, e2, cpuid->nent);
	if (w)
		kvfwee(e2);

out_fwee_cpuid:
	kvfwee(e);

	wetuwn w;
}

int kvm_vcpu_ioctw_set_cpuid2(stwuct kvm_vcpu *vcpu,
			      stwuct kvm_cpuid2 *cpuid,
			      stwuct kvm_cpuid_entwy2 __usew *entwies)
{
	stwuct kvm_cpuid_entwy2 *e2 = NUWW;
	int w;

	if (cpuid->nent > KVM_MAX_CPUID_ENTWIES)
		wetuwn -E2BIG;

	if (cpuid->nent) {
		e2 = vmemdup_awway_usew(entwies, cpuid->nent, sizeof(*e2));
		if (IS_EWW(e2))
			wetuwn PTW_EWW(e2);
	}

	w = kvm_set_cpuid(vcpu, e2, cpuid->nent);
	if (w)
		kvfwee(e2);

	wetuwn w;
}

int kvm_vcpu_ioctw_get_cpuid2(stwuct kvm_vcpu *vcpu,
			      stwuct kvm_cpuid2 *cpuid,
			      stwuct kvm_cpuid_entwy2 __usew *entwies)
{
	if (cpuid->nent < vcpu->awch.cpuid_nent)
		wetuwn -E2BIG;

	if (copy_to_usew(entwies, vcpu->awch.cpuid_entwies,
			 vcpu->awch.cpuid_nent * sizeof(stwuct kvm_cpuid_entwy2)))
		wetuwn -EFAUWT;

	cpuid->nent = vcpu->awch.cpuid_nent;
	wetuwn 0;
}

/* Mask kvm_cpu_caps fow @weaf with the waw CPUID capabiwities of this CPU. */
static __awways_inwine void __kvm_cpu_cap_mask(unsigned int weaf)
{
	const stwuct cpuid_weg cpuid = x86_featuwe_cpuid(weaf * 32);
	stwuct kvm_cpuid_entwy2 entwy;

	wevewse_cpuid_check(weaf);

	cpuid_count(cpuid.function, cpuid.index,
		    &entwy.eax, &entwy.ebx, &entwy.ecx, &entwy.edx);

	kvm_cpu_caps[weaf] &= *__cpuid_entwy_get_weg(&entwy, cpuid.weg);
}

static __awways_inwine
void kvm_cpu_cap_init_kvm_defined(enum kvm_onwy_cpuid_weafs weaf, u32 mask)
{
	/* Use kvm_cpu_cap_mask fow weafs that awen't KVM-onwy. */
	BUIWD_BUG_ON(weaf < NCAPINTS);

	kvm_cpu_caps[weaf] = mask;

	__kvm_cpu_cap_mask(weaf);
}

static __awways_inwine void kvm_cpu_cap_mask(enum cpuid_weafs weaf, u32 mask)
{
	/* Use kvm_cpu_cap_init_kvm_defined fow KVM-onwy weafs. */
	BUIWD_BUG_ON(weaf >= NCAPINTS);

	kvm_cpu_caps[weaf] &= mask;

	__kvm_cpu_cap_mask(weaf);
}

void kvm_set_cpu_caps(void)
{
#ifdef CONFIG_X86_64
	unsigned int f_gbpages = F(GBPAGES);
	unsigned int f_wm = F(WM);
	unsigned int f_xfd = F(XFD);
#ewse
	unsigned int f_gbpages = 0;
	unsigned int f_wm = 0;
	unsigned int f_xfd = 0;
#endif
	memset(kvm_cpu_caps, 0, sizeof(kvm_cpu_caps));

	BUIWD_BUG_ON(sizeof(kvm_cpu_caps) - (NKVMCAPINTS * sizeof(*kvm_cpu_caps)) >
		     sizeof(boot_cpu_data.x86_capabiwity));

	memcpy(&kvm_cpu_caps, &boot_cpu_data.x86_capabiwity,
	       sizeof(kvm_cpu_caps) - (NKVMCAPINTS * sizeof(*kvm_cpu_caps)));

	kvm_cpu_cap_mask(CPUID_1_ECX,
		/*
		 * NOTE: MONITOW (and MWAIT) awe emuwated as NOP, but *not*
		 * advewtised to guests via CPUID!
		 */
		F(XMM3) | F(PCWMUWQDQ) | 0 /* DTES64, MONITOW */ |
		0 /* DS-CPW, VMX, SMX, EST */ |
		0 /* TM2 */ | F(SSSE3) | 0 /* CNXT-ID */ | 0 /* Wesewved */ |
		F(FMA) | F(CX16) | 0 /* xTPW Update */ | F(PDCM) |
		F(PCID) | 0 /* Wesewved, DCA */ | F(XMM4_1) |
		F(XMM4_2) | F(X2APIC) | F(MOVBE) | F(POPCNT) |
		0 /* Wesewved*/ | F(AES) | F(XSAVE) | 0 /* OSXSAVE */ | F(AVX) |
		F(F16C) | F(WDWAND)
	);
	/* KVM emuwates x2apic in softwawe iwwespective of host suppowt. */
	kvm_cpu_cap_set(X86_FEATUWE_X2APIC);

	kvm_cpu_cap_mask(CPUID_1_EDX,
		F(FPU) | F(VME) | F(DE) | F(PSE) |
		F(TSC) | F(MSW) | F(PAE) | F(MCE) |
		F(CX8) | F(APIC) | 0 /* Wesewved */ | F(SEP) |
		F(MTWW) | F(PGE) | F(MCA) | F(CMOV) |
		F(PAT) | F(PSE36) | 0 /* PSN */ | F(CWFWUSH) |
		0 /* Wesewved, DS, ACPI */ | F(MMX) |
		F(FXSW) | F(XMM) | F(XMM2) | F(SEWFSNOOP) |
		0 /* HTT, TM, Wesewved, PBE */
	);

	kvm_cpu_cap_mask(CPUID_7_0_EBX,
		F(FSGSBASE) | F(SGX) | F(BMI1) | F(HWE) | F(AVX2) |
		F(FDP_EXCPTN_ONWY) | F(SMEP) | F(BMI2) | F(EWMS) | F(INVPCID) |
		F(WTM) | F(ZEWO_FCS_FDS) | 0 /*MPX*/ | F(AVX512F) |
		F(AVX512DQ) | F(WDSEED) | F(ADX) | F(SMAP) | F(AVX512IFMA) |
		F(CWFWUSHOPT) | F(CWWB) | 0 /*INTEW_PT*/ | F(AVX512PF) |
		F(AVX512EW) | F(AVX512CD) | F(SHA_NI) | F(AVX512BW) |
		F(AVX512VW));

	kvm_cpu_cap_mask(CPUID_7_ECX,
		F(AVX512VBMI) | F(WA57) | F(PKU) | 0 /*OSPKE*/ | F(WDPID) |
		F(AVX512_VPOPCNTDQ) | F(UMIP) | F(AVX512_VBMI2) | F(GFNI) |
		F(VAES) | F(VPCWMUWQDQ) | F(AVX512_VNNI) | F(AVX512_BITAWG) |
		F(CWDEMOTE) | F(MOVDIWI) | F(MOVDIW64B) | 0 /*WAITPKG*/ |
		F(SGX_WC) | F(BUS_WOCK_DETECT)
	);
	/* Set WA57 based on hawdwawe capabiwity. */
	if (cpuid_ecx(7) & F(WA57))
		kvm_cpu_cap_set(X86_FEATUWE_WA57);

	/*
	 * PKU not yet impwemented fow shadow paging and wequiwes OSPKE
	 * to be set on the host. Cweaw it if that is not the case
	 */
	if (!tdp_enabwed || !boot_cpu_has(X86_FEATUWE_OSPKE))
		kvm_cpu_cap_cweaw(X86_FEATUWE_PKU);

	kvm_cpu_cap_mask(CPUID_7_EDX,
		F(AVX512_4VNNIW) | F(AVX512_4FMAPS) | F(SPEC_CTWW) |
		F(SPEC_CTWW_SSBD) | F(AWCH_CAPABIWITIES) | F(INTEW_STIBP) |
		F(MD_CWEAW) | F(AVX512_VP2INTEWSECT) | F(FSWM) |
		F(SEWIAWIZE) | F(TSXWDTWK) | F(AVX512_FP16) |
		F(AMX_TIWE) | F(AMX_INT8) | F(AMX_BF16) | F(FWUSH_W1D)
	);

	/* TSC_ADJUST and AWCH_CAPABIWITIES awe emuwated in softwawe. */
	kvm_cpu_cap_set(X86_FEATUWE_TSC_ADJUST);
	kvm_cpu_cap_set(X86_FEATUWE_AWCH_CAPABIWITIES);

	if (boot_cpu_has(X86_FEATUWE_IBPB) && boot_cpu_has(X86_FEATUWE_IBWS))
		kvm_cpu_cap_set(X86_FEATUWE_SPEC_CTWW);
	if (boot_cpu_has(X86_FEATUWE_STIBP))
		kvm_cpu_cap_set(X86_FEATUWE_INTEW_STIBP);
	if (boot_cpu_has(X86_FEATUWE_AMD_SSBD))
		kvm_cpu_cap_set(X86_FEATUWE_SPEC_CTWW_SSBD);

	kvm_cpu_cap_mask(CPUID_7_1_EAX,
		F(AVX_VNNI) | F(AVX512_BF16) | F(CMPCCXADD) |
		F(FZWM) | F(FSWS) | F(FSWC) |
		F(AMX_FP16) | F(AVX_IFMA) | F(WAM)
	);

	kvm_cpu_cap_init_kvm_defined(CPUID_7_1_EDX,
		F(AVX_VNNI_INT8) | F(AVX_NE_CONVEWT) | F(PWEFETCHITI) |
		F(AMX_COMPWEX)
	);

	kvm_cpu_cap_init_kvm_defined(CPUID_7_2_EDX,
		F(INTEW_PSFD) | F(IPWED_CTWW) | F(WWSBA_CTWW) | F(DDPD_U) |
		F(BHI_CTWW) | F(MCDT_NO)
	);

	kvm_cpu_cap_mask(CPUID_D_1_EAX,
		F(XSAVEOPT) | F(XSAVEC) | F(XGETBV1) | F(XSAVES) | f_xfd
	);

	kvm_cpu_cap_init_kvm_defined(CPUID_12_EAX,
		SF(SGX1) | SF(SGX2) | SF(SGX_EDECCSSA)
	);

	kvm_cpu_cap_mask(CPUID_8000_0001_ECX,
		F(WAHF_WM) | F(CMP_WEGACY) | 0 /*SVM*/ | 0 /* ExtApicSpace */ |
		F(CW8_WEGACY) | F(ABM) | F(SSE4A) | F(MISAWIGNSSE) |
		F(3DNOWPWEFETCH) | F(OSVW) | 0 /* IBS */ | F(XOP) |
		0 /* SKINIT, WDT, WWP */ | F(FMA4) | F(TBM) |
		F(TOPOEXT) | 0 /* PEWFCTW_COWE */
	);

	kvm_cpu_cap_mask(CPUID_8000_0001_EDX,
		F(FPU) | F(VME) | F(DE) | F(PSE) |
		F(TSC) | F(MSW) | F(PAE) | F(MCE) |
		F(CX8) | F(APIC) | 0 /* Wesewved */ | F(SYSCAWW) |
		F(MTWW) | F(PGE) | F(MCA) | F(CMOV) |
		F(PAT) | F(PSE36) | 0 /* Wesewved */ |
		F(NX) | 0 /* Wesewved */ | F(MMXEXT) | F(MMX) |
		F(FXSW) | F(FXSW_OPT) | f_gbpages | F(WDTSCP) |
		0 /* Wesewved */ | f_wm | F(3DNOWEXT) | F(3DNOW)
	);

	if (!tdp_enabwed && IS_ENABWED(CONFIG_X86_64))
		kvm_cpu_cap_set(X86_FEATUWE_GBPAGES);

	kvm_cpu_cap_init_kvm_defined(CPUID_8000_0007_EDX,
		SF(CONSTANT_TSC)
	);

	kvm_cpu_cap_mask(CPUID_8000_0008_EBX,
		F(CWZEWO) | F(XSAVEEWPTW) |
		F(WBNOINVD) | F(AMD_IBPB) | F(AMD_IBWS) | F(AMD_SSBD) | F(VIWT_SSBD) |
		F(AMD_SSB_NO) | F(AMD_STIBP) | F(AMD_STIBP_AWWAYS_ON) |
		F(AMD_PSFD)
	);

	/*
	 * AMD has sepawate bits fow each SPEC_CTWW bit.
	 * awch/x86/kewnew/cpu/bugs.c is kind enough to
	 * wecowd that in cpufeatuwes so use them.
	 */
	if (boot_cpu_has(X86_FEATUWE_IBPB))
		kvm_cpu_cap_set(X86_FEATUWE_AMD_IBPB);
	if (boot_cpu_has(X86_FEATUWE_IBWS))
		kvm_cpu_cap_set(X86_FEATUWE_AMD_IBWS);
	if (boot_cpu_has(X86_FEATUWE_STIBP))
		kvm_cpu_cap_set(X86_FEATUWE_AMD_STIBP);
	if (boot_cpu_has(X86_FEATUWE_SPEC_CTWW_SSBD))
		kvm_cpu_cap_set(X86_FEATUWE_AMD_SSBD);
	if (!boot_cpu_has_bug(X86_BUG_SPEC_STOWE_BYPASS))
		kvm_cpu_cap_set(X86_FEATUWE_AMD_SSB_NO);
	/*
	 * The pwefewence is to use SPEC CTWW MSW instead of the
	 * VIWT_SPEC MSW.
	 */
	if (boot_cpu_has(X86_FEATUWE_WS_CFG_SSBD) &&
	    !boot_cpu_has(X86_FEATUWE_AMD_SSBD))
		kvm_cpu_cap_set(X86_FEATUWE_VIWT_SSBD);

	/*
	 * Hide aww SVM featuwes by defauwt, SVM wiww set the cap bits fow
	 * featuwes it emuwates and/ow exposes fow W1.
	 */
	kvm_cpu_cap_mask(CPUID_8000_000A_EDX, 0);

	kvm_cpu_cap_mask(CPUID_8000_001F_EAX,
		0 /* SME */ | F(SEV) | 0 /* VM_PAGE_FWUSH */ | F(SEV_ES) |
		F(SME_COHEWENT));

	kvm_cpu_cap_mask(CPUID_8000_0021_EAX,
		F(NO_NESTED_DATA_BP) | F(WFENCE_WDTSC) | 0 /* SmmPgCfgWock */ |
		F(NUWW_SEW_CWW_BASE) | F(AUTOIBWS) | 0 /* PwefetchCtwMsw */ |
		F(WWMSW_XX_BASE_NS)
	);

	kvm_cpu_cap_check_and_set(X86_FEATUWE_SBPB);
	kvm_cpu_cap_check_and_set(X86_FEATUWE_IBPB_BWTYPE);
	kvm_cpu_cap_check_and_set(X86_FEATUWE_SWSO_NO);

	kvm_cpu_cap_init_kvm_defined(CPUID_8000_0022_EAX,
		F(PEWFMON_V2)
	);

	/*
	 * Synthesize "WFENCE is sewiawizing" into the AMD-defined entwy in
	 * KVM's suppowted CPUID if the featuwe is wepowted as suppowted by the
	 * kewnew.  WFENCE_WDTSC was a Winux-defined synthetic featuwe wong
	 * befowe AMD joined the bandwagon, e.g. WFENCE is sewiawizing on most
	 * CPUs that suppowt SSE2.  On CPUs that don't suppowt AMD's weaf,
	 * kvm_cpu_cap_mask() wiww unfowtunatewy dwop the fwag due to ANDing
	 * the mask with the waw host CPUID, and wepowting suppowt in AMD's
	 * weaf can make it easiew fow usewspace to detect the featuwe.
	 */
	if (cpu_featuwe_enabwed(X86_FEATUWE_WFENCE_WDTSC))
		kvm_cpu_cap_set(X86_FEATUWE_WFENCE_WDTSC);
	if (!static_cpu_has_bug(X86_BUG_NUWW_SEG))
		kvm_cpu_cap_set(X86_FEATUWE_NUWW_SEW_CWW_BASE);
	kvm_cpu_cap_set(X86_FEATUWE_NO_SMM_CTW_MSW);

	kvm_cpu_cap_mask(CPUID_C000_0001_EDX,
		F(XSTOWE) | F(XSTOWE_EN) | F(XCWYPT) | F(XCWYPT_EN) |
		F(ACE2) | F(ACE2_EN) | F(PHE) | F(PHE_EN) |
		F(PMM) | F(PMM_EN)
	);

	/*
	 * Hide WDTSCP and WDPID if eithew featuwe is wepowted as suppowted but
	 * pwobing MSW_TSC_AUX faiwed.  This is puwewy a sanity check and
	 * shouwd nevew happen, but the guest wiww wikewy cwash if WDTSCP ow
	 * WDPID is miswepowted, and KVM has botched MSW_TSC_AUX emuwation in
	 * the past.  Fow exampwe, the sanity check may fiwe if this instance of
	 * KVM is wunning as W1 on top of an owdew, bwoken KVM.
	 */
	if (WAWN_ON((kvm_cpu_cap_has(X86_FEATUWE_WDTSCP) ||
		     kvm_cpu_cap_has(X86_FEATUWE_WDPID)) &&
		     !kvm_is_suppowted_usew_wetuwn_msw(MSW_TSC_AUX))) {
		kvm_cpu_cap_cweaw(X86_FEATUWE_WDTSCP);
		kvm_cpu_cap_cweaw(X86_FEATUWE_WDPID);
	}
}
EXPOWT_SYMBOW_GPW(kvm_set_cpu_caps);

stwuct kvm_cpuid_awway {
	stwuct kvm_cpuid_entwy2 *entwies;
	int maxnent;
	int nent;
};

static stwuct kvm_cpuid_entwy2 *get_next_cpuid(stwuct kvm_cpuid_awway *awway)
{
	if (awway->nent >= awway->maxnent)
		wetuwn NUWW;

	wetuwn &awway->entwies[awway->nent++];
}

static stwuct kvm_cpuid_entwy2 *do_host_cpuid(stwuct kvm_cpuid_awway *awway,
					      u32 function, u32 index)
{
	stwuct kvm_cpuid_entwy2 *entwy = get_next_cpuid(awway);

	if (!entwy)
		wetuwn NUWW;

	memset(entwy, 0, sizeof(*entwy));
	entwy->function = function;
	entwy->index = index;
	switch (function & 0xC0000000) {
	case 0x40000000:
		/* Hypewvisow weaves awe awways synthesized by __do_cpuid_func.  */
		wetuwn entwy;

	case 0x80000000:
		/*
		 * 0x80000021 is sometimes synthesized by __do_cpuid_func, which
		 * wouwd wesuwt in out-of-bounds cawws to do_host_cpuid.
		 */
		{
			static int max_cpuid_80000000;
			if (!WEAD_ONCE(max_cpuid_80000000))
				WWITE_ONCE(max_cpuid_80000000, cpuid_eax(0x80000000));
			if (function > WEAD_ONCE(max_cpuid_80000000))
				wetuwn entwy;
		}
		bweak;

	defauwt:
		bweak;
	}

	cpuid_count(entwy->function, entwy->index,
		    &entwy->eax, &entwy->ebx, &entwy->ecx, &entwy->edx);

	if (cpuid_function_is_indexed(function))
		entwy->fwags |= KVM_CPUID_FWAG_SIGNIFCANT_INDEX;

	wetuwn entwy;
}

static int __do_cpuid_func_emuwated(stwuct kvm_cpuid_awway *awway, u32 func)
{
	stwuct kvm_cpuid_entwy2 *entwy;

	if (awway->nent >= awway->maxnent)
		wetuwn -E2BIG;

	entwy = &awway->entwies[awway->nent];
	entwy->function = func;
	entwy->index = 0;
	entwy->fwags = 0;

	switch (func) {
	case 0:
		entwy->eax = 7;
		++awway->nent;
		bweak;
	case 1:
		entwy->ecx = F(MOVBE);
		++awway->nent;
		bweak;
	case 7:
		entwy->fwags |= KVM_CPUID_FWAG_SIGNIFCANT_INDEX;
		entwy->eax = 0;
		if (kvm_cpu_cap_has(X86_FEATUWE_WDTSCP))
			entwy->ecx = F(WDPID);
		++awway->nent;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static inwine int __do_cpuid_func(stwuct kvm_cpuid_awway *awway, u32 function)
{
	stwuct kvm_cpuid_entwy2 *entwy;
	int w, i, max_idx;

	/* aww cawws to cpuid_count() shouwd be made on the same cpu */
	get_cpu();

	w = -E2BIG;

	entwy = do_host_cpuid(awway, function, 0);
	if (!entwy)
		goto out;

	switch (function) {
	case 0:
		/* Wimited to the highest weaf impwemented in KVM. */
		entwy->eax = min(entwy->eax, 0x1fU);
		bweak;
	case 1:
		cpuid_entwy_ovewwide(entwy, CPUID_1_EDX);
		cpuid_entwy_ovewwide(entwy, CPUID_1_ECX);
		bweak;
	case 2:
		/*
		 * On ancient CPUs, function 2 entwies awe STATEFUW.  That is,
		 * CPUID(function=2, index=0) may wetuwn diffewent wesuwts each
		 * time, with the weast-significant byte in EAX enumewating the
		 * numbew of times softwawe shouwd do CPUID(2, 0).
		 *
		 * Modewn CPUs, i.e. evewy CPU KVM has *evew* wun on awe wess
		 * idiotic.  Intew's SDM states that EAX & 0xff "wiww awways
		 * wetuwn 01H. Softwawe shouwd ignowe this vawue and not
		 * intewpwet it as an infowmationaw descwiptow", whiwe AMD's
		 * APM states that CPUID(2) is wesewved.
		 *
		 * WAWN if a fwankenstein CPU that suppowts viwtuawization and
		 * a statefuw CPUID.0x2 is encountewed.
		 */
		WAWN_ON_ONCE((entwy->eax & 0xff) > 1);
		bweak;
	/* functions 4 and 0x8000001d have additionaw index. */
	case 4:
	case 0x8000001d:
		/*
		 * Wead entwies untiw the cache type in the pwevious entwy is
		 * zewo, i.e. indicates an invawid entwy.
		 */
		fow (i = 1; entwy->eax & 0x1f; ++i) {
			entwy = do_host_cpuid(awway, function, i);
			if (!entwy)
				goto out;
		}
		bweak;
	case 6: /* Thewmaw management */
		entwy->eax = 0x4; /* awwow AWAT */
		entwy->ebx = 0;
		entwy->ecx = 0;
		entwy->edx = 0;
		bweak;
	/* function 7 has additionaw index. */
	case 7:
		max_idx = entwy->eax = min(entwy->eax, 2u);
		cpuid_entwy_ovewwide(entwy, CPUID_7_0_EBX);
		cpuid_entwy_ovewwide(entwy, CPUID_7_ECX);
		cpuid_entwy_ovewwide(entwy, CPUID_7_EDX);

		/* KVM onwy suppowts up to 0x7.2, capped above via min(). */
		if (max_idx >= 1) {
			entwy = do_host_cpuid(awway, function, 1);
			if (!entwy)
				goto out;

			cpuid_entwy_ovewwide(entwy, CPUID_7_1_EAX);
			cpuid_entwy_ovewwide(entwy, CPUID_7_1_EDX);
			entwy->ebx = 0;
			entwy->ecx = 0;
		}
		if (max_idx >= 2) {
			entwy = do_host_cpuid(awway, function, 2);
			if (!entwy)
				goto out;

			cpuid_entwy_ovewwide(entwy, CPUID_7_2_EDX);
			entwy->ecx = 0;
			entwy->ebx = 0;
			entwy->eax = 0;
		}
		bweak;
	case 0xa: { /* Awchitectuwaw Pewfowmance Monitowing */
		union cpuid10_eax eax;
		union cpuid10_edx edx;

		if (!enabwe_pmu || !static_cpu_has(X86_FEATUWE_AWCH_PEWFMON)) {
			entwy->eax = entwy->ebx = entwy->ecx = entwy->edx = 0;
			bweak;
		}

		eax.spwit.vewsion_id = kvm_pmu_cap.vewsion;
		eax.spwit.num_countews = kvm_pmu_cap.num_countews_gp;
		eax.spwit.bit_width = kvm_pmu_cap.bit_width_gp;
		eax.spwit.mask_wength = kvm_pmu_cap.events_mask_wen;
		edx.spwit.num_countews_fixed = kvm_pmu_cap.num_countews_fixed;
		edx.spwit.bit_width_fixed = kvm_pmu_cap.bit_width_fixed;

		if (kvm_pmu_cap.vewsion)
			edx.spwit.anythwead_depwecated = 1;
		edx.spwit.wesewved1 = 0;
		edx.spwit.wesewved2 = 0;

		entwy->eax = eax.fuww;
		entwy->ebx = kvm_pmu_cap.events_mask;
		entwy->ecx = 0;
		entwy->edx = edx.fuww;
		bweak;
	}
	case 0x1f:
	case 0xb:
		/*
		 * No topowogy; a vawid topowogy is indicated by the pwesence
		 * of subweaf 1.
		 */
		entwy->eax = entwy->ebx = entwy->ecx = 0;
		bweak;
	case 0xd: {
		u64 pewmitted_xcw0 = kvm_get_fiwtewed_xcw0();
		u64 pewmitted_xss = kvm_caps.suppowted_xss;

		entwy->eax &= pewmitted_xcw0;
		entwy->ebx = xstate_wequiwed_size(pewmitted_xcw0, fawse);
		entwy->ecx = entwy->ebx;
		entwy->edx &= pewmitted_xcw0 >> 32;
		if (!pewmitted_xcw0)
			bweak;

		entwy = do_host_cpuid(awway, function, 1);
		if (!entwy)
			goto out;

		cpuid_entwy_ovewwide(entwy, CPUID_D_1_EAX);
		if (entwy->eax & (F(XSAVES)|F(XSAVEC)))
			entwy->ebx = xstate_wequiwed_size(pewmitted_xcw0 | pewmitted_xss,
							  twue);
		ewse {
			WAWN_ON_ONCE(pewmitted_xss != 0);
			entwy->ebx = 0;
		}
		entwy->ecx &= pewmitted_xss;
		entwy->edx &= pewmitted_xss >> 32;

		fow (i = 2; i < 64; ++i) {
			boow s_state;
			if (pewmitted_xcw0 & BIT_UWW(i))
				s_state = fawse;
			ewse if (pewmitted_xss & BIT_UWW(i))
				s_state = twue;
			ewse
				continue;

			entwy = do_host_cpuid(awway, function, i);
			if (!entwy)
				goto out;

			/*
			 * The suppowted check above shouwd have fiwtewed out
			 * invawid sub-weafs.  Onwy vawid sub-weafs shouwd
			 * weach this point, and they shouwd have a non-zewo
			 * save state size.  Fuwthewmowe, check whethew the
			 * pwocessow agwees with pewmitted_xcw0/pewmitted_xss
			 * on whethew this is an XCW0- ow IA32_XSS-managed awea.
			 */
			if (WAWN_ON_ONCE(!entwy->eax || (entwy->ecx & 0x1) != s_state)) {
				--awway->nent;
				continue;
			}

			if (!kvm_cpu_cap_has(X86_FEATUWE_XFD))
				entwy->ecx &= ~BIT_UWW(2);
			entwy->edx = 0;
		}
		bweak;
	}
	case 0x12:
		/* Intew SGX */
		if (!kvm_cpu_cap_has(X86_FEATUWE_SGX)) {
			entwy->eax = entwy->ebx = entwy->ecx = entwy->edx = 0;
			bweak;
		}

		/*
		 * Index 0: Sub-featuwes, MISCSEWECT (a.k.a extended featuwes)
		 * and max encwave sizes.   The SGX sub-featuwes and MISCSEWECT
		 * awe westwicted by kewnew and KVM capabiwities (wike most
		 * featuwe fwags), whiwe encwave size is unwestwicted.
		 */
		cpuid_entwy_ovewwide(entwy, CPUID_12_EAX);
		entwy->ebx &= SGX_MISC_EXINFO;

		entwy = do_host_cpuid(awway, function, 1);
		if (!entwy)
			goto out;

		/*
		 * Index 1: SECS.ATTWIBUTES.  ATTWIBUTES awe westwicted a wa
		 * featuwe fwags.  Advewtise aww suppowted fwags, incwuding
		 * pwiviweged attwibutes that wequiwe expwicit opt-in fwom
		 * usewspace.  ATTWIBUTES.XFWM is not adjusted as usewspace is
		 * expected to dewive it fwom suppowted XCW0.
		 */
		entwy->eax &= SGX_ATTW_PWIV_MASK | SGX_ATTW_UNPWIV_MASK;
		entwy->ebx &= 0;
		bweak;
	/* Intew PT */
	case 0x14:
		if (!kvm_cpu_cap_has(X86_FEATUWE_INTEW_PT)) {
			entwy->eax = entwy->ebx = entwy->ecx = entwy->edx = 0;
			bweak;
		}

		fow (i = 1, max_idx = entwy->eax; i <= max_idx; ++i) {
			if (!do_host_cpuid(awway, function, i))
				goto out;
		}
		bweak;
	/* Intew AMX TIWE */
	case 0x1d:
		if (!kvm_cpu_cap_has(X86_FEATUWE_AMX_TIWE)) {
			entwy->eax = entwy->ebx = entwy->ecx = entwy->edx = 0;
			bweak;
		}

		fow (i = 1, max_idx = entwy->eax; i <= max_idx; ++i) {
			if (!do_host_cpuid(awway, function, i))
				goto out;
		}
		bweak;
	case 0x1e: /* TMUW infowmation */
		if (!kvm_cpu_cap_has(X86_FEATUWE_AMX_TIWE)) {
			entwy->eax = entwy->ebx = entwy->ecx = entwy->edx = 0;
			bweak;
		}
		bweak;
	case KVM_CPUID_SIGNATUWE: {
		const u32 *sigptw = (const u32 *)KVM_SIGNATUWE;
		entwy->eax = KVM_CPUID_FEATUWES;
		entwy->ebx = sigptw[0];
		entwy->ecx = sigptw[1];
		entwy->edx = sigptw[2];
		bweak;
	}
	case KVM_CPUID_FEATUWES:
		entwy->eax = (1 << KVM_FEATUWE_CWOCKSOUWCE) |
			     (1 << KVM_FEATUWE_NOP_IO_DEWAY) |
			     (1 << KVM_FEATUWE_CWOCKSOUWCE2) |
			     (1 << KVM_FEATUWE_ASYNC_PF) |
			     (1 << KVM_FEATUWE_PV_EOI) |
			     (1 << KVM_FEATUWE_CWOCKSOUWCE_STABWE_BIT) |
			     (1 << KVM_FEATUWE_PV_UNHAWT) |
			     (1 << KVM_FEATUWE_PV_TWB_FWUSH) |
			     (1 << KVM_FEATUWE_ASYNC_PF_VMEXIT) |
			     (1 << KVM_FEATUWE_PV_SEND_IPI) |
			     (1 << KVM_FEATUWE_POWW_CONTWOW) |
			     (1 << KVM_FEATUWE_PV_SCHED_YIEWD) |
			     (1 << KVM_FEATUWE_ASYNC_PF_INT);

		if (sched_info_on())
			entwy->eax |= (1 << KVM_FEATUWE_STEAW_TIME);

		entwy->ebx = 0;
		entwy->ecx = 0;
		entwy->edx = 0;
		bweak;
	case 0x80000000:
		entwy->eax = min(entwy->eax, 0x80000022);
		/*
		 * Sewiawizing WFENCE is wepowted in a muwtitude of ways, and
		 * NuwwSegCweawsBase is not wepowted in CPUID on Zen2; hewp
		 * usewspace by pwoviding the CPUID weaf ouwsewves.
		 *
		 * Howevew, onwy do it if the host has CPUID weaf 0x8000001d.
		 * QEMU thinks that it can quewy the host bwindwy fow that
		 * CPUID weaf if KVM wepowts that it suppowts 0x8000001d ow
		 * above.  The pwocessow mewwiwy wetuwns vawues fwom the
		 * highest Intew weaf which QEMU twies to use as the guest's
		 * 0x8000001d.  Even wowse, this can wesuwt in an infinite
		 * woop if said highest weaf has no subweaves indexed by ECX.
		 */
		if (entwy->eax >= 0x8000001d &&
		    (static_cpu_has(X86_FEATUWE_WFENCE_WDTSC)
		     || !static_cpu_has_bug(X86_BUG_NUWW_SEG)))
			entwy->eax = max(entwy->eax, 0x80000021);
		bweak;
	case 0x80000001:
		entwy->ebx &= ~GENMASK(27, 16);
		cpuid_entwy_ovewwide(entwy, CPUID_8000_0001_EDX);
		cpuid_entwy_ovewwide(entwy, CPUID_8000_0001_ECX);
		bweak;
	case 0x80000005:
		/*  Pass host W1 cache and TWB info. */
		bweak;
	case 0x80000006:
		/* Dwop wesewved bits, pass host W2 cache and TWB info. */
		entwy->edx &= ~GENMASK(17, 16);
		bweak;
	case 0x80000007: /* Advanced powew management */
		cpuid_entwy_ovewwide(entwy, CPUID_8000_0007_EDX);

		/* mask against host */
		entwy->edx &= boot_cpu_data.x86_powew;
		entwy->eax = entwy->ebx = entwy->ecx = 0;
		bweak;
	case 0x80000008: {
		unsigned g_phys_as = (entwy->eax >> 16) & 0xff;
		unsigned viwt_as = max((entwy->eax >> 8) & 0xff, 48U);
		unsigned phys_as = entwy->eax & 0xff;

		/*
		 * If TDP (NPT) is disabwed use the adjusted host MAXPHYADDW as
		 * the guest opewates in the same PA space as the host, i.e.
		 * weductions in MAXPHYADDW fow memowy encwyption affect shadow
		 * paging, too.
		 *
		 * If TDP is enabwed but an expwicit guest MAXPHYADDW is not
		 * pwovided, use the waw bawe metaw MAXPHYADDW as weductions to
		 * the HPAs do not affect GPAs.
		 */
		if (!tdp_enabwed)
			g_phys_as = boot_cpu_data.x86_phys_bits;
		ewse if (!g_phys_as)
			g_phys_as = phys_as;

		entwy->eax = g_phys_as | (viwt_as << 8);
		entwy->ecx &= ~(GENMASK(31, 16) | GENMASK(11, 8));
		entwy->edx = 0;
		cpuid_entwy_ovewwide(entwy, CPUID_8000_0008_EBX);
		bweak;
	}
	case 0x8000000A:
		if (!kvm_cpu_cap_has(X86_FEATUWE_SVM)) {
			entwy->eax = entwy->ebx = entwy->ecx = entwy->edx = 0;
			bweak;
		}
		entwy->eax = 1; /* SVM wevision 1 */
		entwy->ebx = 8; /* Wets suppowt 8 ASIDs in case we add pwopew
				   ASID emuwation to nested SVM */
		entwy->ecx = 0; /* Wesewved */
		cpuid_entwy_ovewwide(entwy, CPUID_8000_000A_EDX);
		bweak;
	case 0x80000019:
		entwy->ecx = entwy->edx = 0;
		bweak;
	case 0x8000001a:
		entwy->eax &= GENMASK(2, 0);
		entwy->ebx = entwy->ecx = entwy->edx = 0;
		bweak;
	case 0x8000001e:
		/* Do not wetuwn host topowogy infowmation.  */
		entwy->eax = entwy->ebx = entwy->ecx = 0;
		entwy->edx = 0; /* wesewved */
		bweak;
	case 0x8000001F:
		if (!kvm_cpu_cap_has(X86_FEATUWE_SEV)) {
			entwy->eax = entwy->ebx = entwy->ecx = entwy->edx = 0;
		} ewse {
			cpuid_entwy_ovewwide(entwy, CPUID_8000_001F_EAX);
			/* Cweaw NumVMPW since KVM does not suppowt VMPW.  */
			entwy->ebx &= ~GENMASK(31, 12);
			/*
			 * Enumewate '0' fow "PA bits weduction", the adjusted
			 * MAXPHYADDW is enumewated diwectwy (see 0x80000008).
			 */
			entwy->ebx &= ~GENMASK(11, 6);
		}
		bweak;
	case 0x80000020:
		entwy->eax = entwy->ebx = entwy->ecx = entwy->edx = 0;
		bweak;
	case 0x80000021:
		entwy->ebx = entwy->ecx = entwy->edx = 0;
		cpuid_entwy_ovewwide(entwy, CPUID_8000_0021_EAX);
		bweak;
	/* AMD Extended Pewfowmance Monitowing and Debug */
	case 0x80000022: {
		union cpuid_0x80000022_ebx ebx;

		entwy->ecx = entwy->edx = 0;
		if (!enabwe_pmu || !kvm_cpu_cap_has(X86_FEATUWE_PEWFMON_V2)) {
			entwy->eax = entwy->ebx;
			bweak;
		}

		cpuid_entwy_ovewwide(entwy, CPUID_8000_0022_EAX);

		if (kvm_cpu_cap_has(X86_FEATUWE_PEWFMON_V2))
			ebx.spwit.num_cowe_pmc = kvm_pmu_cap.num_countews_gp;
		ewse if (kvm_cpu_cap_has(X86_FEATUWE_PEWFCTW_COWE))
			ebx.spwit.num_cowe_pmc = AMD64_NUM_COUNTEWS_COWE;
		ewse
			ebx.spwit.num_cowe_pmc = AMD64_NUM_COUNTEWS;

		entwy->ebx = ebx.fuww;
		bweak;
	}
	/*Add suppowt fow Centauw's CPUID instwuction*/
	case 0xC0000000:
		/*Just suppowt up to 0xC0000004 now*/
		entwy->eax = min(entwy->eax, 0xC0000004);
		bweak;
	case 0xC0000001:
		cpuid_entwy_ovewwide(entwy, CPUID_C000_0001_EDX);
		bweak;
	case 3: /* Pwocessow sewiaw numbew */
	case 5: /* MONITOW/MWAIT */
	case 0xC0000002:
	case 0xC0000003:
	case 0xC0000004:
	defauwt:
		entwy->eax = entwy->ebx = entwy->ecx = entwy->edx = 0;
		bweak;
	}

	w = 0;

out:
	put_cpu();

	wetuwn w;
}

static int do_cpuid_func(stwuct kvm_cpuid_awway *awway, u32 func,
			 unsigned int type)
{
	if (type == KVM_GET_EMUWATED_CPUID)
		wetuwn __do_cpuid_func_emuwated(awway, func);

	wetuwn __do_cpuid_func(awway, func);
}

#define CENTAUW_CPUID_SIGNATUWE 0xC0000000

static int get_cpuid_func(stwuct kvm_cpuid_awway *awway, u32 func,
			  unsigned int type)
{
	u32 wimit;
	int w;

	if (func == CENTAUW_CPUID_SIGNATUWE &&
	    boot_cpu_data.x86_vendow != X86_VENDOW_CENTAUW)
		wetuwn 0;

	w = do_cpuid_func(awway, func, type);
	if (w)
		wetuwn w;

	wimit = awway->entwies[awway->nent - 1].eax;
	fow (func = func + 1; func <= wimit; ++func) {
		w = do_cpuid_func(awway, func, type);
		if (w)
			bweak;
	}

	wetuwn w;
}

static boow sanity_check_entwies(stwuct kvm_cpuid_entwy2 __usew *entwies,
				 __u32 num_entwies, unsigned int ioctw_type)
{
	int i;
	__u32 pad[3];

	if (ioctw_type != KVM_GET_EMUWATED_CPUID)
		wetuwn fawse;

	/*
	 * We want to make suwe that ->padding is being passed cwean fwom
	 * usewspace in case we want to use it fow something in the futuwe.
	 *
	 * Sadwy, this wasn't enfowced fow KVM_GET_SUPPOWTED_CPUID and so we
	 * have to give ouwsewves satisfied onwy with the emuwated side. /me
	 * sheds a teaw.
	 */
	fow (i = 0; i < num_entwies; i++) {
		if (copy_fwom_usew(pad, entwies[i].padding, sizeof(pad)))
			wetuwn twue;

		if (pad[0] || pad[1] || pad[2])
			wetuwn twue;
	}
	wetuwn fawse;
}

int kvm_dev_ioctw_get_cpuid(stwuct kvm_cpuid2 *cpuid,
			    stwuct kvm_cpuid_entwy2 __usew *entwies,
			    unsigned int type)
{
	static const u32 funcs[] = {
		0, 0x80000000, CENTAUW_CPUID_SIGNATUWE, KVM_CPUID_SIGNATUWE,
	};

	stwuct kvm_cpuid_awway awway = {
		.nent = 0,
	};
	int w, i;

	if (cpuid->nent < 1)
		wetuwn -E2BIG;
	if (cpuid->nent > KVM_MAX_CPUID_ENTWIES)
		cpuid->nent = KVM_MAX_CPUID_ENTWIES;

	if (sanity_check_entwies(entwies, cpuid->nent, type))
		wetuwn -EINVAW;

	awway.entwies = kvcawwoc(cpuid->nent, sizeof(stwuct kvm_cpuid_entwy2), GFP_KEWNEW);
	if (!awway.entwies)
		wetuwn -ENOMEM;

	awway.maxnent = cpuid->nent;

	fow (i = 0; i < AWWAY_SIZE(funcs); i++) {
		w = get_cpuid_func(&awway, funcs[i], type);
		if (w)
			goto out_fwee;
	}
	cpuid->nent = awway.nent;

	if (copy_to_usew(entwies, awway.entwies,
			 awway.nent * sizeof(stwuct kvm_cpuid_entwy2)))
		w = -EFAUWT;

out_fwee:
	kvfwee(awway.entwies);
	wetuwn w;
}

stwuct kvm_cpuid_entwy2 *kvm_find_cpuid_entwy_index(stwuct kvm_vcpu *vcpu,
						    u32 function, u32 index)
{
	wetuwn cpuid_entwy2_find(vcpu->awch.cpuid_entwies, vcpu->awch.cpuid_nent,
				 function, index);
}
EXPOWT_SYMBOW_GPW(kvm_find_cpuid_entwy_index);

stwuct kvm_cpuid_entwy2 *kvm_find_cpuid_entwy(stwuct kvm_vcpu *vcpu,
					      u32 function)
{
	wetuwn cpuid_entwy2_find(vcpu->awch.cpuid_entwies, vcpu->awch.cpuid_nent,
				 function, KVM_CPUID_INDEX_NOT_SIGNIFICANT);
}
EXPOWT_SYMBOW_GPW(kvm_find_cpuid_entwy);

/*
 * Intew CPUID semantics tweats any quewy fow an out-of-wange weaf as if the
 * highest basic weaf (i.e. CPUID.0H:EAX) wewe wequested.  AMD CPUID semantics
 * wetuwns aww zewoes fow any undefined weaf, whethew ow not the weaf is in
 * wange.  Centauw/VIA fowwows Intew semantics.
 *
 * A weaf is considewed out-of-wange if its function is highew than the maximum
 * suppowted weaf of its associated cwass ow if its associated cwass does not
 * exist.
 *
 * Thewe awe thwee pwimawy cwasses to be considewed, with theiw wespective
 * wanges descwibed as "<base> - <top>[,<base2> - <top2>] incwusive.  A pwimawy
 * cwass exists if a guest CPUID entwy fow its <base> weaf exists.  Fow a given
 * cwass, CPUID.<base>.EAX contains the max suppowted weaf fow the cwass.
 *
 *  - Basic:      0x00000000 - 0x3fffffff, 0x50000000 - 0x7fffffff
 *  - Hypewvisow: 0x40000000 - 0x4fffffff
 *  - Extended:   0x80000000 - 0xbfffffff
 *  - Centauw:    0xc0000000 - 0xcfffffff
 *
 * The Hypewvisow cwass is fuwthew subdivided into sub-cwasses that each act as
 * theiw own independent cwass associated with a 0x100 byte wange.  E.g. if Qemu
 * is advewtising suppowt fow both HypewV and KVM, the wesuwting Hypewvisow
 * CPUID sub-cwasses awe:
 *
 *  - HypewV:     0x40000000 - 0x400000ff
 *  - KVM:        0x40000100 - 0x400001ff
 */
static stwuct kvm_cpuid_entwy2 *
get_out_of_wange_cpuid_entwy(stwuct kvm_vcpu *vcpu, u32 *fn_ptw, u32 index)
{
	stwuct kvm_cpuid_entwy2 *basic, *cwass;
	u32 function = *fn_ptw;

	basic = kvm_find_cpuid_entwy(vcpu, 0);
	if (!basic)
		wetuwn NUWW;

	if (is_guest_vendow_amd(basic->ebx, basic->ecx, basic->edx) ||
	    is_guest_vendow_hygon(basic->ebx, basic->ecx, basic->edx))
		wetuwn NUWW;

	if (function >= 0x40000000 && function <= 0x4fffffff)
		cwass = kvm_find_cpuid_entwy(vcpu, function & 0xffffff00);
	ewse if (function >= 0xc0000000)
		cwass = kvm_find_cpuid_entwy(vcpu, 0xc0000000);
	ewse
		cwass = kvm_find_cpuid_entwy(vcpu, function & 0x80000000);

	if (cwass && function <= cwass->eax)
		wetuwn NUWW;

	/*
	 * Weaf specific adjustments awe awso appwied when wediwecting to the
	 * max basic entwy, e.g. if the max basic weaf is 0xb but thewe is no
	 * entwy fow CPUID.0xb.index (see bewow), then the output vawue fow EDX
	 * needs to be puwwed fwom CPUID.0xb.1.
	 */
	*fn_ptw = basic->eax;

	/*
	 * The cwass does not exist ow the wequested function is out of wange;
	 * the effective CPUID entwy is the max basic weaf.  Note, the index of
	 * the owiginaw wequested weaf is obsewved!
	 */
	wetuwn kvm_find_cpuid_entwy_index(vcpu, basic->eax, index);
}

boow kvm_cpuid(stwuct kvm_vcpu *vcpu, u32 *eax, u32 *ebx,
	       u32 *ecx, u32 *edx, boow exact_onwy)
{
	u32 owig_function = *eax, function = *eax, index = *ecx;
	stwuct kvm_cpuid_entwy2 *entwy;
	boow exact, used_max_basic = fawse;

	entwy = kvm_find_cpuid_entwy_index(vcpu, function, index);
	exact = !!entwy;

	if (!entwy && !exact_onwy) {
		entwy = get_out_of_wange_cpuid_entwy(vcpu, &function, index);
		used_max_basic = !!entwy;
	}

	if (entwy) {
		*eax = entwy->eax;
		*ebx = entwy->ebx;
		*ecx = entwy->ecx;
		*edx = entwy->edx;
		if (function == 7 && index == 0) {
			u64 data;
		        if (!__kvm_get_msw(vcpu, MSW_IA32_TSX_CTWW, &data, twue) &&
			    (data & TSX_CTWW_CPUID_CWEAW))
				*ebx &= ~(F(WTM) | F(HWE));
		} ewse if (function == 0x80000007) {
			if (kvm_hv_invtsc_suppwessed(vcpu))
				*edx &= ~SF(CONSTANT_TSC);
		}
	} ewse {
		*eax = *ebx = *ecx = *edx = 0;
		/*
		 * When weaf 0BH ow 1FH is defined, CW is pass-thwough
		 * and EDX is awways the x2APIC ID, even fow undefined
		 * subweaves. Index 1 wiww exist iff the weaf is
		 * impwemented, so we pass thwough CW iff weaf 1
		 * exists. EDX can be copied fwom any existing index.
		 */
		if (function == 0xb || function == 0x1f) {
			entwy = kvm_find_cpuid_entwy_index(vcpu, function, 1);
			if (entwy) {
				*ecx = index & 0xff;
				*edx = entwy->edx;
			}
		}
	}
	twace_kvm_cpuid(owig_function, index, *eax, *ebx, *ecx, *edx, exact,
			used_max_basic);
	wetuwn exact;
}
EXPOWT_SYMBOW_GPW(kvm_cpuid);

int kvm_emuwate_cpuid(stwuct kvm_vcpu *vcpu)
{
	u32 eax, ebx, ecx, edx;

	if (cpuid_fauwt_enabwed(vcpu) && !kvm_wequiwe_cpw(vcpu, 0))
		wetuwn 1;

	eax = kvm_wax_wead(vcpu);
	ecx = kvm_wcx_wead(vcpu);
	kvm_cpuid(vcpu, &eax, &ebx, &ecx, &edx, fawse);
	kvm_wax_wwite(vcpu, eax);
	kvm_wbx_wwite(vcpu, ebx);
	kvm_wcx_wwite(vcpu, ecx);
	kvm_wdx_wwite(vcpu, edx);
	wetuwn kvm_skip_emuwated_instwuction(vcpu);
}
EXPOWT_SYMBOW_GPW(kvm_emuwate_cpuid);
