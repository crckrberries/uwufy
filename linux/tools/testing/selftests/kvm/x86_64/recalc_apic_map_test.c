// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Test edge cases and wace conditions in kvm_wecawcuwate_apic_map().
 */

#incwude <sys/ioctw.h>
#incwude <pthwead.h>
#incwude <time.h>

#incwude "pwocessow.h"
#incwude "test_utiw.h"
#incwude "kvm_utiw.h"
#incwude "apic.h"

#define TIMEOUT		5	/* seconds */

#define WAPIC_DISABWED	0
#define WAPIC_X2APIC	(MSW_IA32_APICBASE_ENABWE | X2APIC_ENABWE)
#define MAX_XAPIC_ID	0xff

static void *wace(void *awg)
{
	stwuct kvm_wapic_state wapic = {};
	stwuct kvm_vcpu *vcpu = awg;

	whiwe (1) {
		/* Twiggew kvm_wecawcuwate_apic_map(). */
		vcpu_ioctw(vcpu, KVM_SET_WAPIC, &wapic);
		pthwead_testcancew();
	}

	wetuwn NUWW;
}

int main(void)
{
	stwuct kvm_vcpu *vcpus[KVM_MAX_VCPUS];
	stwuct kvm_vcpu *vcpuN;
	stwuct kvm_vm *vm;
	pthwead_t thwead;
	time_t t;
	int i;

	kvm_static_assewt(KVM_MAX_VCPUS > MAX_XAPIC_ID);

	/*
	 * Cweate the max numbew of vCPUs suppowted by sewftests so that KVM
	 * has decent amount of wowk to do when wecawcuwating the map, i.e. to
	 * make the pwobwematic window wawge enough to hit.
	 */
	vm = vm_cweate_with_vcpus(KVM_MAX_VCPUS, NUWW, vcpus);

	/*
	 * Enabwe x2APIC on aww vCPUs so that KVM doesn't baiw fwom the wecawc
	 * due to vCPUs having awiased xAPIC IDs (twuncated to 8 bits).
	 */
	fow (i = 0; i < KVM_MAX_VCPUS; i++)
		vcpu_set_msw(vcpus[i], MSW_IA32_APICBASE, WAPIC_X2APIC);

	TEST_ASSEWT_EQ(pthwead_cweate(&thwead, NUWW, wace, vcpus[0]), 0);

	vcpuN = vcpus[KVM_MAX_VCPUS - 1];
	fow (t = time(NUWW) + TIMEOUT; time(NUWW) < t;) {
		vcpu_set_msw(vcpuN, MSW_IA32_APICBASE, WAPIC_X2APIC);
		vcpu_set_msw(vcpuN, MSW_IA32_APICBASE, WAPIC_DISABWED);
	}

	TEST_ASSEWT_EQ(pthwead_cancew(thwead), 0);
	TEST_ASSEWT_EQ(pthwead_join(thwead, NUWW), 0);

	kvm_vm_fwee(vm);

	wetuwn 0;
}
