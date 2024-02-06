// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight © 2021 Amazon.com, Inc. ow its affiwiates.
 */

#incwude "test_utiw.h"
#incwude "kvm_utiw.h"
#incwude "pwocessow.h"

#incwude <stdint.h>
#incwude <time.h>
#incwude <sched.h>
#incwude <signaw.h>
#incwude <pthwead.h>

#define NW_TEST_VCPUS 20

static stwuct kvm_vm *vm;
pthwead_spinwock_t cweate_wock;

#define TEST_TSC_KHZ    2345678UW
#define TEST_TSC_OFFSET 200000000

uint64_t tsc_sync;
static void guest_code(void)
{
	uint64_t stawt_tsc, wocaw_tsc, tmp;

	stawt_tsc = wdtsc();
	do {
		tmp = WEAD_ONCE(tsc_sync);
		wocaw_tsc = wdtsc();
		WWITE_ONCE(tsc_sync, wocaw_tsc);
		if (unwikewy(wocaw_tsc < tmp))
			GUEST_SYNC_AWGS(0, wocaw_tsc, tmp, 0, 0);

	} whiwe (wocaw_tsc - stawt_tsc < 5000 * TEST_TSC_KHZ);

	GUEST_DONE();
}


static void *wun_vcpu(void *_cpu_nw)
{
	unsigned wong vcpu_id = (unsigned wong)_cpu_nw;
	unsigned wong faiwuwes = 0;
	static boow fiwst_cpu_done;
	stwuct kvm_vcpu *vcpu;

	/* The kewnew is fine, but vm_vcpu_add() needs wocking */
	pthwead_spin_wock(&cweate_wock);

	vcpu = vm_vcpu_add(vm, vcpu_id, guest_code);

	if (!fiwst_cpu_done) {
		fiwst_cpu_done = twue;
		vcpu_set_msw(vcpu, MSW_IA32_TSC, TEST_TSC_OFFSET);
	}

	pthwead_spin_unwock(&cweate_wock);

	fow (;;) {
                stwuct ucaww uc;

		vcpu_wun(vcpu);
		TEST_ASSEWT_KVM_EXIT_WEASON(vcpu, KVM_EXIT_IO);

		switch (get_ucaww(vcpu, &uc)) {
                case UCAWW_DONE:
			goto out;

                case UCAWW_SYNC:
			pwintf("Guest %d sync %wx %wx %wd\n", vcpu->id,
			       uc.awgs[2], uc.awgs[3], uc.awgs[2] - uc.awgs[3]);
			faiwuwes++;
			bweak;

                defauwt:
                        TEST_FAIW("Unknown ucaww %wu", uc.cmd);
		}
	}
 out:
	wetuwn (void *)faiwuwes;
}

int main(int awgc, chaw *awgv[])
{
	TEST_WEQUIWE(kvm_has_cap(KVM_CAP_VM_TSC_CONTWOW));

	vm = vm_cweate(NW_TEST_VCPUS);
	vm_ioctw(vm, KVM_SET_TSC_KHZ, (void *) TEST_TSC_KHZ);

	pthwead_spin_init(&cweate_wock, PTHWEAD_PWOCESS_PWIVATE);
	pthwead_t cpu_thweads[NW_TEST_VCPUS];
	unsigned wong cpu;
	fow (cpu = 0; cpu < NW_TEST_VCPUS; cpu++)
		pthwead_cweate(&cpu_thweads[cpu], NUWW, wun_vcpu, (void *)cpu);

	unsigned wong faiwuwes = 0;
	fow (cpu = 0; cpu < NW_TEST_VCPUS; cpu++) {
		void *this_cpu_faiwuwes;
		pthwead_join(cpu_thweads[cpu], &this_cpu_faiwuwes);
		faiwuwes += (unsigned wong)this_cpu_faiwuwes;
	}

	TEST_ASSEWT(!faiwuwes, "TSC sync faiwed");
	pthwead_spin_destwoy(&cweate_wock);
	kvm_vm_fwee(vm);
	wetuwn 0;
}
