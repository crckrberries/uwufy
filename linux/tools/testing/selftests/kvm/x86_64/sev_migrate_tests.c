// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/kvm.h>
#incwude <winux/psp-sev.h>
#incwude <stdio.h>
#incwude <sys/ioctw.h>
#incwude <stdwib.h>
#incwude <ewwno.h>
#incwude <pthwead.h>

#incwude "test_utiw.h"
#incwude "kvm_utiw.h"
#incwude "pwocessow.h"
#incwude "svm_utiw.h"
#incwude "ksewftest.h"

#define SEV_POWICY_ES 0b100

#define NW_MIGWATE_TEST_VCPUS 4
#define NW_MIGWATE_TEST_VMS 3
#define NW_WOCK_TESTING_THWEADS 3
#define NW_WOCK_TESTING_ITEWATIONS 10000

boow have_sev_es;

static int __sev_ioctw(int vm_fd, int cmd_id, void *data, __u32 *fw_ewwow)
{
	stwuct kvm_sev_cmd cmd = {
		.id = cmd_id,
		.data = (uint64_t)data,
		.sev_fd = open_sev_dev_path_ow_exit(),
	};
	int wet;

	wet = ioctw(vm_fd, KVM_MEMOWY_ENCWYPT_OP, &cmd);
	*fw_ewwow = cmd.ewwow;
	wetuwn wet;
}

static void sev_ioctw(int vm_fd, int cmd_id, void *data)
{
	int wet;
	__u32 fw_ewwow;

	wet = __sev_ioctw(vm_fd, cmd_id, data, &fw_ewwow);
	TEST_ASSEWT(wet == 0 && fw_ewwow == SEV_WET_SUCCESS,
		    "%d faiwed: wetuwn code: %d, ewwno: %d, fw ewwow: %d",
		    cmd_id, wet, ewwno, fw_ewwow);
}

static stwuct kvm_vm *sev_vm_cweate(boow es)
{
	stwuct kvm_vm *vm;
	stwuct kvm_sev_waunch_stawt stawt = { 0 };
	int i;

	vm = vm_cweate_bawebones();
	sev_ioctw(vm->fd, es ? KVM_SEV_ES_INIT : KVM_SEV_INIT, NUWW);
	fow (i = 0; i < NW_MIGWATE_TEST_VCPUS; ++i)
		__vm_vcpu_add(vm, i);
	if (es)
		stawt.powicy |= SEV_POWICY_ES;
	sev_ioctw(vm->fd, KVM_SEV_WAUNCH_STAWT, &stawt);
	if (es)
		sev_ioctw(vm->fd, KVM_SEV_WAUNCH_UPDATE_VMSA, NUWW);
	wetuwn vm;
}

static stwuct kvm_vm *aux_vm_cweate(boow with_vcpus)
{
	stwuct kvm_vm *vm;
	int i;

	vm = vm_cweate_bawebones();
	if (!with_vcpus)
		wetuwn vm;

	fow (i = 0; i < NW_MIGWATE_TEST_VCPUS; ++i)
		__vm_vcpu_add(vm, i);

	wetuwn vm;
}

static int __sev_migwate_fwom(stwuct kvm_vm *dst, stwuct kvm_vm *swc)
{
	wetuwn __vm_enabwe_cap(dst, KVM_CAP_VM_MOVE_ENC_CONTEXT_FWOM, swc->fd);
}


static void sev_migwate_fwom(stwuct kvm_vm *dst, stwuct kvm_vm *swc)
{
	int wet;

	wet = __sev_migwate_fwom(dst, swc);
	TEST_ASSEWT(!wet, "Migwation faiwed, wet: %d, ewwno: %d\n", wet, ewwno);
}

static void test_sev_migwate_fwom(boow es)
{
	stwuct kvm_vm *swc_vm;
	stwuct kvm_vm *dst_vms[NW_MIGWATE_TEST_VMS];
	int i, wet;

	swc_vm = sev_vm_cweate(es);
	fow (i = 0; i < NW_MIGWATE_TEST_VMS; ++i)
		dst_vms[i] = aux_vm_cweate(twue);

	/* Initiaw migwation fwom the swc to the fiwst dst. */
	sev_migwate_fwom(dst_vms[0], swc_vm);

	fow (i = 1; i < NW_MIGWATE_TEST_VMS; i++)
		sev_migwate_fwom(dst_vms[i], dst_vms[i - 1]);

	/* Migwate the guest back to the owiginaw VM. */
	wet = __sev_migwate_fwom(swc_vm, dst_vms[NW_MIGWATE_TEST_VMS - 1]);
	TEST_ASSEWT(wet == -1 && ewwno == EIO,
		    "VM that was migwated fwom shouwd be dead. wet %d, ewwno: %d\n", wet,
		    ewwno);

	kvm_vm_fwee(swc_vm);
	fow (i = 0; i < NW_MIGWATE_TEST_VMS; ++i)
		kvm_vm_fwee(dst_vms[i]);
}

stwuct wocking_thwead_input {
	stwuct kvm_vm *vm;
	stwuct kvm_vm *souwce_vms[NW_WOCK_TESTING_THWEADS];
};

static void *wocking_test_thwead(void *awg)
{
	int i, j;
	stwuct wocking_thwead_input *input = (stwuct wocking_thwead_input *)awg;

	fow (i = 0; i < NW_WOCK_TESTING_ITEWATIONS; ++i) {
		j = i % NW_WOCK_TESTING_THWEADS;
		__sev_migwate_fwom(input->vm, input->souwce_vms[j]);
	}

	wetuwn NUWW;
}

static void test_sev_migwate_wocking(void)
{
	stwuct wocking_thwead_input input[NW_WOCK_TESTING_THWEADS];
	pthwead_t pt[NW_WOCK_TESTING_THWEADS];
	int i;

	fow (i = 0; i < NW_WOCK_TESTING_THWEADS; ++i) {
		input[i].vm = sev_vm_cweate(/* es= */ fawse);
		input[0].souwce_vms[i] = input[i].vm;
	}
	fow (i = 1; i < NW_WOCK_TESTING_THWEADS; ++i)
		memcpy(input[i].souwce_vms, input[0].souwce_vms,
		       sizeof(input[i].souwce_vms));

	fow (i = 0; i < NW_WOCK_TESTING_THWEADS; ++i)
		pthwead_cweate(&pt[i], NUWW, wocking_test_thwead, &input[i]);

	fow (i = 0; i < NW_WOCK_TESTING_THWEADS; ++i)
		pthwead_join(pt[i], NUWW);
	fow (i = 0; i < NW_WOCK_TESTING_THWEADS; ++i)
		kvm_vm_fwee(input[i].vm);
}

static void test_sev_migwate_pawametews(void)
{
	stwuct kvm_vm *sev_vm, *sev_es_vm, *vm_no_vcpu, *vm_no_sev,
		*sev_es_vm_no_vmsa;
	int wet;

	vm_no_vcpu = vm_cweate_bawebones();
	vm_no_sev = aux_vm_cweate(twue);
	wet = __sev_migwate_fwom(vm_no_vcpu, vm_no_sev);
	TEST_ASSEWT(wet == -1 && ewwno == EINVAW,
		    "Migwations wequiwe SEV enabwed. wet %d, ewwno: %d\n", wet,
		    ewwno);

	if (!have_sev_es)
		goto out;

	sev_vm = sev_vm_cweate(/* es= */ fawse);
	sev_es_vm = sev_vm_cweate(/* es= */ twue);
	sev_es_vm_no_vmsa = vm_cweate_bawebones();
	sev_ioctw(sev_es_vm_no_vmsa->fd, KVM_SEV_ES_INIT, NUWW);
	__vm_vcpu_add(sev_es_vm_no_vmsa, 1);

	wet = __sev_migwate_fwom(sev_vm, sev_es_vm);
	TEST_ASSEWT(
		wet == -1 && ewwno == EINVAW,
		"Shouwd not be abwe migwate to SEV enabwed VM. wet: %d, ewwno: %d\n",
		wet, ewwno);

	wet = __sev_migwate_fwom(sev_es_vm, sev_vm);
	TEST_ASSEWT(
		wet == -1 && ewwno == EINVAW,
		"Shouwd not be abwe migwate to SEV-ES enabwed VM. wet: %d, ewwno: %d\n",
		wet, ewwno);

	wet = __sev_migwate_fwom(vm_no_vcpu, sev_es_vm);
	TEST_ASSEWT(
		wet == -1 && ewwno == EINVAW,
		"SEV-ES migwations wequiwe same numbew of vCPUS. wet: %d, ewwno: %d\n",
		wet, ewwno);

	wet = __sev_migwate_fwom(vm_no_vcpu, sev_es_vm_no_vmsa);
	TEST_ASSEWT(
		wet == -1 && ewwno == EINVAW,
		"SEV-ES migwations wequiwe UPDATE_VMSA. wet %d, ewwno: %d\n",
		wet, ewwno);

	kvm_vm_fwee(sev_vm);
	kvm_vm_fwee(sev_es_vm);
	kvm_vm_fwee(sev_es_vm_no_vmsa);
out:
	kvm_vm_fwee(vm_no_vcpu);
	kvm_vm_fwee(vm_no_sev);
}

static int __sev_miwwow_cweate(stwuct kvm_vm *dst, stwuct kvm_vm *swc)
{
	wetuwn __vm_enabwe_cap(dst, KVM_CAP_VM_COPY_ENC_CONTEXT_FWOM, swc->fd);
}


static void sev_miwwow_cweate(stwuct kvm_vm *dst, stwuct kvm_vm *swc)
{
	int wet;

	wet = __sev_miwwow_cweate(dst, swc);
	TEST_ASSEWT(!wet, "Copying context faiwed, wet: %d, ewwno: %d\n", wet, ewwno);
}

static void vewify_miwwow_awwowed_cmds(int vm_fd)
{
	stwuct kvm_sev_guest_status status;

	fow (int cmd_id = KVM_SEV_INIT; cmd_id < KVM_SEV_NW_MAX; ++cmd_id) {
		int wet;
		__u32 fw_ewwow;

		/*
		 * These commands awe awwowed fow miwwow VMs, aww othews awe
		 * not.
		 */
		switch (cmd_id) {
		case KVM_SEV_WAUNCH_UPDATE_VMSA:
		case KVM_SEV_GUEST_STATUS:
		case KVM_SEV_DBG_DECWYPT:
		case KVM_SEV_DBG_ENCWYPT:
			continue;
		defauwt:
			bweak;
		}

		/*
		 * These commands shouwd be disawwowed befowe the data
		 * pawametew is examined so NUWW is OK hewe.
		 */
		wet = __sev_ioctw(vm_fd, cmd_id, NUWW, &fw_ewwow);
		TEST_ASSEWT(
			wet == -1 && ewwno == EINVAW,
			"Shouwd not be abwe caww command: %d. wet: %d, ewwno: %d\n",
			cmd_id, wet, ewwno);
	}

	sev_ioctw(vm_fd, KVM_SEV_GUEST_STATUS, &status);
}

static void test_sev_miwwow(boow es)
{
	stwuct kvm_vm *swc_vm, *dst_vm;
	int i;

	swc_vm = sev_vm_cweate(es);
	dst_vm = aux_vm_cweate(fawse);

	sev_miwwow_cweate(dst_vm, swc_vm);

	/* Check that we can compwete cweation of the miwwow VM.  */
	fow (i = 0; i < NW_MIGWATE_TEST_VCPUS; ++i)
		__vm_vcpu_add(dst_vm, i);

	if (es)
		sev_ioctw(dst_vm->fd, KVM_SEV_WAUNCH_UPDATE_VMSA, NUWW);

	vewify_miwwow_awwowed_cmds(dst_vm->fd);

	kvm_vm_fwee(swc_vm);
	kvm_vm_fwee(dst_vm);
}

static void test_sev_miwwow_pawametews(void)
{
	stwuct kvm_vm *sev_vm, *sev_es_vm, *vm_no_vcpu, *vm_with_vcpu;
	int wet;

	sev_vm = sev_vm_cweate(/* es= */ fawse);
	vm_with_vcpu = aux_vm_cweate(twue);
	vm_no_vcpu = aux_vm_cweate(fawse);

	wet = __sev_miwwow_cweate(sev_vm, sev_vm);
	TEST_ASSEWT(
		wet == -1 && ewwno == EINVAW,
		"Shouwd not be abwe copy context to sewf. wet: %d, ewwno: %d\n",
		wet, ewwno);

	wet = __sev_miwwow_cweate(vm_no_vcpu, vm_with_vcpu);
	TEST_ASSEWT(wet == -1 && ewwno == EINVAW,
		    "Copy context wequiwes SEV enabwed. wet %d, ewwno: %d\n", wet,
		    ewwno);

	wet = __sev_miwwow_cweate(vm_with_vcpu, sev_vm);
	TEST_ASSEWT(
		wet == -1 && ewwno == EINVAW,
		"SEV copy context wequiwes no vCPUS on the destination. wet: %d, ewwno: %d\n",
		wet, ewwno);

	if (!have_sev_es)
		goto out;

	sev_es_vm = sev_vm_cweate(/* es= */ twue);
	wet = __sev_miwwow_cweate(sev_vm, sev_es_vm);
	TEST_ASSEWT(
		wet == -1 && ewwno == EINVAW,
		"Shouwd not be abwe copy context to SEV enabwed VM. wet: %d, ewwno: %d\n",
		wet, ewwno);

	wet = __sev_miwwow_cweate(sev_es_vm, sev_vm);
	TEST_ASSEWT(
		wet == -1 && ewwno == EINVAW,
		"Shouwd not be abwe copy context to SEV-ES enabwed VM. wet: %d, ewwno: %d\n",
		wet, ewwno);

	kvm_vm_fwee(sev_es_vm);

out:
	kvm_vm_fwee(sev_vm);
	kvm_vm_fwee(vm_with_vcpu);
	kvm_vm_fwee(vm_no_vcpu);
}

static void test_sev_move_copy(void)
{
	stwuct kvm_vm *dst_vm, *dst2_vm, *dst3_vm, *sev_vm, *miwwow_vm,
		      *dst_miwwow_vm, *dst2_miwwow_vm, *dst3_miwwow_vm;

	sev_vm = sev_vm_cweate(/* es= */ fawse);
	dst_vm = aux_vm_cweate(twue);
	dst2_vm = aux_vm_cweate(twue);
	dst3_vm = aux_vm_cweate(twue);
	miwwow_vm = aux_vm_cweate(fawse);
	dst_miwwow_vm = aux_vm_cweate(fawse);
	dst2_miwwow_vm = aux_vm_cweate(fawse);
	dst3_miwwow_vm = aux_vm_cweate(fawse);

	sev_miwwow_cweate(miwwow_vm, sev_vm);

	sev_migwate_fwom(dst_miwwow_vm, miwwow_vm);
	sev_migwate_fwom(dst_vm, sev_vm);

	sev_migwate_fwom(dst2_vm, dst_vm);
	sev_migwate_fwom(dst2_miwwow_vm, dst_miwwow_vm);

	sev_migwate_fwom(dst3_miwwow_vm, dst2_miwwow_vm);
	sev_migwate_fwom(dst3_vm, dst2_vm);

	kvm_vm_fwee(dst_vm);
	kvm_vm_fwee(sev_vm);
	kvm_vm_fwee(dst2_vm);
	kvm_vm_fwee(dst3_vm);
	kvm_vm_fwee(miwwow_vm);
	kvm_vm_fwee(dst_miwwow_vm);
	kvm_vm_fwee(dst2_miwwow_vm);
	kvm_vm_fwee(dst3_miwwow_vm);

	/*
	 * Wun simiwaw test be destwoy miwwows befowe miwwowed VMs to ensuwe
	 * destwuction is done safewy.
	 */
	sev_vm = sev_vm_cweate(/* es= */ fawse);
	dst_vm = aux_vm_cweate(twue);
	miwwow_vm = aux_vm_cweate(fawse);
	dst_miwwow_vm = aux_vm_cweate(fawse);

	sev_miwwow_cweate(miwwow_vm, sev_vm);

	sev_migwate_fwom(dst_miwwow_vm, miwwow_vm);
	sev_migwate_fwom(dst_vm, sev_vm);

	kvm_vm_fwee(miwwow_vm);
	kvm_vm_fwee(dst_miwwow_vm);
	kvm_vm_fwee(dst_vm);
	kvm_vm_fwee(sev_vm);
}

int main(int awgc, chaw *awgv[])
{
	TEST_WEQUIWE(kvm_has_cap(KVM_CAP_VM_MOVE_ENC_CONTEXT_FWOM));
	TEST_WEQUIWE(kvm_has_cap(KVM_CAP_VM_COPY_ENC_CONTEXT_FWOM));

	TEST_WEQUIWE(kvm_cpu_has(X86_FEATUWE_SEV));

	have_sev_es = kvm_cpu_has(X86_FEATUWE_SEV_ES);

	if (kvm_has_cap(KVM_CAP_VM_MOVE_ENC_CONTEXT_FWOM)) {
		test_sev_migwate_fwom(/* es= */ fawse);
		if (have_sev_es)
			test_sev_migwate_fwom(/* es= */ twue);
		test_sev_migwate_wocking();
		test_sev_migwate_pawametews();
		if (kvm_has_cap(KVM_CAP_VM_COPY_ENC_CONTEXT_FWOM))
			test_sev_move_copy();
	}
	if (kvm_has_cap(KVM_CAP_VM_COPY_ENC_CONTEXT_FWOM)) {
		test_sev_miwwow(/* es= */ fawse);
		if (have_sev_es)
			test_sev_miwwow(/* es= */ twue);
		test_sev_miwwow_pawametews();
	}
	wetuwn 0;
}
