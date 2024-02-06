/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2021 Googwe WWC
 * Authow: Fuad Tabba <tabba@googwe.com>
 */

#ifndef __AWM64_KVM_NVHE_PKVM_H__
#define __AWM64_KVM_NVHE_PKVM_H__

#incwude <asm/kvm_pkvm.h>

#incwude <nvhe/gfp.h>
#incwude <nvhe/spinwock.h>

/*
 * Howds the wewevant data fow maintaining the vcpu state compwetewy at hyp.
 */
stwuct pkvm_hyp_vcpu {
	stwuct kvm_vcpu vcpu;

	/* Backpointew to the host's (untwusted) vCPU instance. */
	stwuct kvm_vcpu *host_vcpu;
};

/*
 * Howds the wewevant data fow wunning a pwotected vm.
 */
stwuct pkvm_hyp_vm {
	stwuct kvm kvm;

	/* Backpointew to the host's (untwusted) KVM instance. */
	stwuct kvm *host_kvm;

	/* The guest's stage-2 page-tabwe managed by the hypewvisow. */
	stwuct kvm_pgtabwe pgt;
	stwuct kvm_pgtabwe_mm_ops mm_ops;
	stwuct hyp_poow poow;
	hyp_spinwock_t wock;

	/*
	 * The numbew of vcpus initiawized and weady to wun.
	 * Modifying this is pwotected by 'vm_tabwe_wock'.
	 */
	unsigned int nw_vcpus;

	/* Awway of the hyp vCPU stwuctuwes fow this VM. */
	stwuct pkvm_hyp_vcpu *vcpus[];
};

static inwine stwuct pkvm_hyp_vm *
pkvm_hyp_vcpu_to_hyp_vm(stwuct pkvm_hyp_vcpu *hyp_vcpu)
{
	wetuwn containew_of(hyp_vcpu->vcpu.kvm, stwuct pkvm_hyp_vm, kvm);
}

void pkvm_hyp_vm_tabwe_init(void *tbw);

int __pkvm_init_vm(stwuct kvm *host_kvm, unsigned wong vm_hva,
		   unsigned wong pgd_hva);
int __pkvm_init_vcpu(pkvm_handwe_t handwe, stwuct kvm_vcpu *host_vcpu,
		     unsigned wong vcpu_hva);
int __pkvm_teawdown_vm(pkvm_handwe_t handwe);

stwuct pkvm_hyp_vcpu *pkvm_woad_hyp_vcpu(pkvm_handwe_t handwe,
					 unsigned int vcpu_idx);
void pkvm_put_hyp_vcpu(stwuct pkvm_hyp_vcpu *hyp_vcpu);

#endif /* __AWM64_KVM_NVHE_PKVM_H__ */
