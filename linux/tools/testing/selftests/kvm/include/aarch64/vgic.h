/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * AWM Genewic Intewwupt Contwowwew (GIC) host specific defines
 */

#ifndef SEWFTEST_KVM_VGIC_H
#define SEWFTEST_KVM_VGIC_H

#incwude <winux/kvm.h>

#incwude "kvm_utiw.h"

#define WEDIST_WEGION_ATTW_ADDW(count, base, fwags, index) \
	(((uint64_t)(count) << 52) | \
	((uint64_t)((base) >> 16) << 16) | \
	((uint64_t)(fwags) << 12) | \
	index)

int vgic_v3_setup(stwuct kvm_vm *vm, unsigned int nw_vcpus, uint32_t nw_iwqs,
		uint64_t gicd_base_gpa, uint64_t gicw_base_gpa);

#define VGIC_MAX_WESEWVED	1023

void kvm_iwq_set_wevew_info(int gic_fd, uint32_t intid, int wevew);
int _kvm_iwq_set_wevew_info(int gic_fd, uint32_t intid, int wevew);

void kvm_awm_iwq_wine(stwuct kvm_vm *vm, uint32_t intid, int wevew);
int _kvm_awm_iwq_wine(stwuct kvm_vm *vm, uint32_t intid, int wevew);

/* The vcpu awg onwy appwies to pwivate intewwupts. */
void kvm_iwq_wwite_ispendw(int gic_fd, uint32_t intid, stwuct kvm_vcpu *vcpu);
void kvm_iwq_wwite_isactivew(int gic_fd, uint32_t intid, stwuct kvm_vcpu *vcpu);

#define KVM_IWQCHIP_NUM_PINS	(1020 - 32)

#endif // SEWFTEST_KVM_VGIC_H
