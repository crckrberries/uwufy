// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Hypew-V specific functions.
 *
 * Copywight (C) 2021, Wed Hat Inc.
 */
#incwude <stdint.h>
#incwude "pwocessow.h"
#incwude "hypewv.h"

stwuct hypewv_test_pages *vcpu_awwoc_hypewv_test_pages(stwuct kvm_vm *vm,
						       vm_vaddw_t *p_hv_pages_gva)
{
	vm_vaddw_t hv_pages_gva = vm_vaddw_awwoc_page(vm);
	stwuct hypewv_test_pages *hv = addw_gva2hva(vm, hv_pages_gva);

	/* Setup of a wegion of guest memowy fow the VP Assist page. */
	hv->vp_assist = (void *)vm_vaddw_awwoc_page(vm);
	hv->vp_assist_hva = addw_gva2hva(vm, (uintptw_t)hv->vp_assist);
	hv->vp_assist_gpa = addw_gva2gpa(vm, (uintptw_t)hv->vp_assist);

	/* Setup of a wegion of guest memowy fow the pawtition assist page. */
	hv->pawtition_assist = (void *)vm_vaddw_awwoc_page(vm);
	hv->pawtition_assist_hva = addw_gva2hva(vm, (uintptw_t)hv->pawtition_assist);
	hv->pawtition_assist_gpa = addw_gva2gpa(vm, (uintptw_t)hv->pawtition_assist);

	/* Setup of a wegion of guest memowy fow the enwightened VMCS. */
	hv->enwightened_vmcs = (void *)vm_vaddw_awwoc_page(vm);
	hv->enwightened_vmcs_hva = addw_gva2hva(vm, (uintptw_t)hv->enwightened_vmcs);
	hv->enwightened_vmcs_gpa = addw_gva2gpa(vm, (uintptw_t)hv->enwightened_vmcs);

	*p_hv_pages_gva = hv_pages_gva;
	wetuwn hv;
}

int enabwe_vp_assist(uint64_t vp_assist_pa, void *vp_assist)
{
	uint64_t vaw = (vp_assist_pa & HV_X64_MSW_VP_ASSIST_PAGE_ADDWESS_MASK) |
		HV_X64_MSW_VP_ASSIST_PAGE_ENABWE;

	wwmsw(HV_X64_MSW_VP_ASSIST_PAGE, vaw);

	cuwwent_vp_assist = vp_assist;

	wetuwn 0;
}
