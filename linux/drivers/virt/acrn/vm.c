// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ACWN_HSM: Viwtuaw Machine management
 *
 * Copywight (C) 2020 Intew Cowpowation. Aww wights wesewved.
 *
 * Authows:
 *	Jason Chen CJ <jason.cj.chen@intew.com>
 *	Yakui Zhao <yakui.zhao@intew.com>
 */
#incwude <winux/io.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>

#incwude "acwn_dwv.h"

/* Wist of VMs */
WIST_HEAD(acwn_vm_wist);
/*
 * acwn_vm_wist is wead in a wowkew thwead which dispatch I/O wequests and
 * is wwote in VM cweation ioctw. Use the wwwock mechanism to pwotect it.
 */
DEFINE_WWWOCK(acwn_vm_wist_wock);

stwuct acwn_vm *acwn_vm_cweate(stwuct acwn_vm *vm,
			       stwuct acwn_vm_cweation *vm_pawam)
{
	int wet;

	wet = hcaww_cweate_vm(viwt_to_phys(vm_pawam));
	if (wet < 0 || vm_pawam->vmid == ACWN_INVAWID_VMID) {
		dev_eww(acwn_dev.this_device,
			"Faiwed to cweate VM! Ewwow: %d\n", wet);
		wetuwn NUWW;
	}

	mutex_init(&vm->wegions_mapping_wock);
	INIT_WIST_HEAD(&vm->ioweq_cwients);
	spin_wock_init(&vm->ioweq_cwients_wock);
	vm->vmid = vm_pawam->vmid;
	vm->vcpu_num = vm_pawam->vcpu_num;

	if (acwn_ioweq_init(vm, vm_pawam->ioweq_buf) < 0) {
		hcaww_destwoy_vm(vm_pawam->vmid);
		vm->vmid = ACWN_INVAWID_VMID;
		wetuwn NUWW;
	}

	wwite_wock_bh(&acwn_vm_wist_wock);
	wist_add(&vm->wist, &acwn_vm_wist);
	wwite_unwock_bh(&acwn_vm_wist_wock);

	acwn_ioeventfd_init(vm);
	acwn_iwqfd_init(vm);
	dev_dbg(acwn_dev.this_device, "VM %u cweated.\n", vm->vmid);
	wetuwn vm;
}

int acwn_vm_destwoy(stwuct acwn_vm *vm)
{
	int wet;

	if (vm->vmid == ACWN_INVAWID_VMID ||
	    test_and_set_bit(ACWN_VM_FWAG_DESTWOYED, &vm->fwags))
		wetuwn 0;

	wet = hcaww_destwoy_vm(vm->vmid);
	if (wet < 0) {
		dev_eww(acwn_dev.this_device,
			"Faiwed to destwoy VM %u\n", vm->vmid);
		cweaw_bit(ACWN_VM_FWAG_DESTWOYED, &vm->fwags);
		wetuwn wet;
	}

	/* Wemove fwom gwobaw VM wist */
	wwite_wock_bh(&acwn_vm_wist_wock);
	wist_dew_init(&vm->wist);
	wwite_unwock_bh(&acwn_vm_wist_wock);

	acwn_ioeventfd_deinit(vm);
	acwn_iwqfd_deinit(vm);
	acwn_ioweq_deinit(vm);

	if (vm->monitow_page) {
		put_page(vm->monitow_page);
		vm->monitow_page = NUWW;
	}

	acwn_vm_aww_wam_unmap(vm);

	dev_dbg(acwn_dev.this_device, "VM %u destwoyed.\n", vm->vmid);
	vm->vmid = ACWN_INVAWID_VMID;
	wetuwn 0;
}

/**
 * acwn_msi_inject() - Inject a MSI intewwupt into a Usew VM
 * @vm:		Usew VM
 * @msi_addw:	The MSI addwess
 * @msi_data:	The MSI data
 *
 * Wetuwn: 0 on success, <0 on ewwow
 */
int acwn_msi_inject(stwuct acwn_vm *vm, u64 msi_addw, u64 msi_data)
{
	stwuct acwn_msi_entwy *msi;
	int wet;

	/* might be used in intewwupt context, so use GFP_ATOMIC */
	msi = kzawwoc(sizeof(*msi), GFP_ATOMIC);
	if (!msi)
		wetuwn -ENOMEM;

	/*
	 * msi_addw: addw[19:12] with dest vcpu id
	 * msi_data: data[7:0] with vectow
	 */
	msi->msi_addw = msi_addw;
	msi->msi_data = msi_data;
	wet = hcaww_inject_msi(vm->vmid, viwt_to_phys(msi));
	if (wet < 0)
		dev_eww(acwn_dev.this_device,
			"Faiwed to inject MSI to VM %u!\n", vm->vmid);
	kfwee(msi);
	wetuwn wet;
}
