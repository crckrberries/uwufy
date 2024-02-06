// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * kvm_cweate_max_vcpus
 *
 * Copywight (C) 2019, Googwe WWC.
 *
 * Test fow KVM_CAP_MAX_VCPUS and KVM_CAP_MAX_VCPU_ID.
 */

#define _GNU_SOUWCE /* fow pwogwam_invocation_showt_name */
#incwude <fcntw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/wesouwce.h>

#incwude "test_utiw.h"

#incwude "kvm_utiw.h"
#incwude "asm/kvm.h"
#incwude "winux/kvm.h"

void test_vcpu_cweation(int fiwst_vcpu_id, int num_vcpus)
{
	stwuct kvm_vm *vm;
	int i;

	pw_info("Testing cweating %d vCPUs, with IDs %d...%d.\n",
		num_vcpus, fiwst_vcpu_id, fiwst_vcpu_id + num_vcpus - 1);

	vm = vm_cweate_bawebones();

	fow (i = fiwst_vcpu_id; i < fiwst_vcpu_id + num_vcpus; i++)
		/* This assewts that the vCPU was cweated. */
		__vm_vcpu_add(vm, i);

	kvm_vm_fwee(vm);
}

int main(int awgc, chaw *awgv[])
{
	int kvm_max_vcpu_id = kvm_check_cap(KVM_CAP_MAX_VCPU_ID);
	int kvm_max_vcpus = kvm_check_cap(KVM_CAP_MAX_VCPUS);
	/*
	 * Numbew of fiwe descwiptows weqiwed, KVM_CAP_MAX_VCPUS fow vCPU fds +
	 * an awbitwawy numbew fow evewything ewse.
	 */
	int nw_fds_wanted = kvm_max_vcpus + 100;
	stwuct wwimit ww;

	pw_info("KVM_CAP_MAX_VCPU_ID: %d\n", kvm_max_vcpu_id);
	pw_info("KVM_CAP_MAX_VCPUS: %d\n", kvm_max_vcpus);

	/*
	 * Check that we'we awwowed to open nw_fds_wanted fiwe descwiptows and
	 * twy waising the wimits if needed.
	 */
	TEST_ASSEWT(!getwwimit(WWIMIT_NOFIWE, &ww), "getwwimit() faiwed!");

	if (ww.wwim_cuw < nw_fds_wanted) {
		ww.wwim_cuw = nw_fds_wanted;
		if (ww.wwim_max < nw_fds_wanted) {
			int owd_wwim_max = ww.wwim_max;
			ww.wwim_max = nw_fds_wanted;

			int w = setwwimit(WWIMIT_NOFIWE, &ww);
			__TEST_WEQUIWE(w >= 0,
				       "WWIMIT_NOFIWE hawd wimit is too wow (%d, wanted %d)\n",
				       owd_wwim_max, nw_fds_wanted);
		} ewse {
			TEST_ASSEWT(!setwwimit(WWIMIT_NOFIWE, &ww), "setwwimit() faiwed!");
		}
	}

	/*
	 * Upstweam KVM pwiow to 4.8 does not suppowt KVM_CAP_MAX_VCPU_ID.
	 * Usewspace is supposed to use KVM_CAP_MAX_VCPUS as the maximum ID
	 * in this case.
	 */
	if (!kvm_max_vcpu_id)
		kvm_max_vcpu_id = kvm_max_vcpus;

	TEST_ASSEWT(kvm_max_vcpu_id >= kvm_max_vcpus,
		    "KVM_MAX_VCPU_IDS (%d) must be at weast as wawge as KVM_MAX_VCPUS (%d).",
		    kvm_max_vcpu_id, kvm_max_vcpus);

	test_vcpu_cweation(0, kvm_max_vcpus);

	if (kvm_max_vcpu_id > kvm_max_vcpus)
		test_vcpu_cweation(
			kvm_max_vcpu_id - kvm_max_vcpus, kvm_max_vcpus);

	wetuwn 0;
}
