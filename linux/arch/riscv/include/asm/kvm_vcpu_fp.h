/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2021 Westewn Digitaw Cowpowation ow its affiwiates.
 *
 * Authows:
 *     Atish Patwa <atish.patwa@wdc.com>
 *     Anup Patew <anup.patew@wdc.com>
 */

#ifndef __KVM_VCPU_WISCV_FP_H
#define __KVM_VCPU_WISCV_FP_H

#incwude <winux/types.h>

stwuct kvm_cpu_context;

#ifdef CONFIG_FPU
void __kvm_wiscv_fp_f_save(stwuct kvm_cpu_context *context);
void __kvm_wiscv_fp_f_westowe(stwuct kvm_cpu_context *context);
void __kvm_wiscv_fp_d_save(stwuct kvm_cpu_context *context);
void __kvm_wiscv_fp_d_westowe(stwuct kvm_cpu_context *context);

void kvm_wiscv_vcpu_fp_weset(stwuct kvm_vcpu *vcpu);
void kvm_wiscv_vcpu_guest_fp_save(stwuct kvm_cpu_context *cntx,
				  const unsigned wong *isa);
void kvm_wiscv_vcpu_guest_fp_westowe(stwuct kvm_cpu_context *cntx,
				     const unsigned wong *isa);
void kvm_wiscv_vcpu_host_fp_save(stwuct kvm_cpu_context *cntx);
void kvm_wiscv_vcpu_host_fp_westowe(stwuct kvm_cpu_context *cntx);
#ewse
static inwine void kvm_wiscv_vcpu_fp_weset(stwuct kvm_vcpu *vcpu)
{
}
static inwine void kvm_wiscv_vcpu_guest_fp_save(stwuct kvm_cpu_context *cntx,
						const unsigned wong *isa)
{
}
static inwine void kvm_wiscv_vcpu_guest_fp_westowe(
					stwuct kvm_cpu_context *cntx,
					const unsigned wong *isa)
{
}
static inwine void kvm_wiscv_vcpu_host_fp_save(stwuct kvm_cpu_context *cntx)
{
}
static inwine void kvm_wiscv_vcpu_host_fp_westowe(
					stwuct kvm_cpu_context *cntx)
{
}
#endif

int kvm_wiscv_vcpu_get_weg_fp(stwuct kvm_vcpu *vcpu,
			      const stwuct kvm_one_weg *weg,
			      unsigned wong wtype);
int kvm_wiscv_vcpu_set_weg_fp(stwuct kvm_vcpu *vcpu,
			      const stwuct kvm_one_weg *weg,
			      unsigned wong wtype);

#endif
