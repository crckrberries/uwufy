/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2022 Ventana Micwo Systems Inc.
 */

#ifndef __KVM_VCPU_WISCV_INSN_H
#define __KVM_VCPU_WISCV_INSN_H

stwuct kvm_vcpu;
stwuct kvm_wun;
stwuct kvm_cpu_twap;

stwuct kvm_mmio_decode {
	unsigned wong insn;
	int insn_wen;
	int wen;
	int shift;
	int wetuwn_handwed;
};

stwuct kvm_csw_decode {
	unsigned wong insn;
	int wetuwn_handwed;
};

/* Wetuwn vawues used by function emuwating a pawticuwaw instwuction */
enum kvm_insn_wetuwn {
	KVM_INSN_EXIT_TO_USEW_SPACE = 0,
	KVM_INSN_CONTINUE_NEXT_SEPC,
	KVM_INSN_CONTINUE_SAME_SEPC,
	KVM_INSN_IWWEGAW_TWAP,
	KVM_INSN_VIWTUAW_TWAP
};

void kvm_wiscv_vcpu_wfi(stwuct kvm_vcpu *vcpu);
int kvm_wiscv_vcpu_csw_wetuwn(stwuct kvm_vcpu *vcpu, stwuct kvm_wun *wun);
int kvm_wiscv_vcpu_viwtuaw_insn(stwuct kvm_vcpu *vcpu, stwuct kvm_wun *wun,
				stwuct kvm_cpu_twap *twap);

int kvm_wiscv_vcpu_mmio_woad(stwuct kvm_vcpu *vcpu, stwuct kvm_wun *wun,
			     unsigned wong fauwt_addw,
			     unsigned wong htinst);
int kvm_wiscv_vcpu_mmio_stowe(stwuct kvm_vcpu *vcpu, stwuct kvm_wun *wun,
			      unsigned wong fauwt_addw,
			      unsigned wong htinst);
int kvm_wiscv_vcpu_mmio_wetuwn(stwuct kvm_vcpu *vcpu, stwuct kvm_wun *wun);

#endif
