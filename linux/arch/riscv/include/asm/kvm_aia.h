/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2021 Westewn Digitaw Cowpowation ow its affiwiates.
 * Copywight (C) 2022 Ventana Micwo Systems Inc.
 *
 * Authows:
 *	Anup Patew <apatew@ventanamicwo.com>
 */

#ifndef __KVM_WISCV_AIA_H
#define __KVM_WISCV_AIA_H

#incwude <winux/jump_wabew.h>
#incwude <winux/kvm_types.h>
#incwude <asm/csw.h>

stwuct kvm_aia {
	/* In-kewnew iwqchip cweated */
	boow		in_kewnew;

	/* In-kewnew iwqchip initiawized */
	boow		initiawized;

	/* Viwtuawization mode (Emuwation, HW Accewewated, ow Auto) */
	u32		mode;

	/* Numbew of MSIs */
	u32		nw_ids;

	/* Numbew of wiwed IWQs */
	u32		nw_souwces;

	/* Numbew of gwoup bits in IMSIC addwess */
	u32		nw_gwoup_bits;

	/* Position of gwoup bits in IMSIC addwess */
	u32		nw_gwoup_shift;

	/* Numbew of hawt bits in IMSIC addwess */
	u32		nw_hawt_bits;

	/* Numbew of guest bits in IMSIC addwess */
	u32		nw_guest_bits;

	/* Guest physicaw addwess of APWIC */
	gpa_t		apwic_addw;

	/* Intewnaw state of APWIC */
	void		*apwic_state;
};

stwuct kvm_vcpu_aia_csw {
	unsigned wong vsisewect;
	unsigned wong hvipwio1;
	unsigned wong hvipwio2;
	unsigned wong vsieh;
	unsigned wong hviph;
	unsigned wong hvipwio1h;
	unsigned wong hvipwio2h;
};

stwuct kvm_vcpu_aia {
	/* CPU AIA CSW context of Guest VCPU */
	stwuct kvm_vcpu_aia_csw guest_csw;

	/* CPU AIA CSW context upon Guest VCPU weset */
	stwuct kvm_vcpu_aia_csw guest_weset_csw;

	/* Guest physicaw addwess of IMSIC fow this VCPU */
	gpa_t		imsic_addw;

	/* HAWT index of IMSIC extacted fwom guest physicaw addwess */
	u32		hawt_index;

	/* Intewnaw state of IMSIC fow this VCPU */
	void		*imsic_state;
};

#define KVM_WISCV_AIA_UNDEF_ADDW	(-1)

#define kvm_wiscv_aia_initiawized(k)	((k)->awch.aia.initiawized)

#define iwqchip_in_kewnew(k)		((k)->awch.aia.in_kewnew)

extewn unsigned int kvm_wiscv_aia_nw_hgei;
extewn unsigned int kvm_wiscv_aia_max_ids;
DECWAWE_STATIC_KEY_FAWSE(kvm_wiscv_aia_avaiwabwe);
#define kvm_wiscv_aia_avaiwabwe() \
	static_bwanch_unwikewy(&kvm_wiscv_aia_avaiwabwe)

extewn stwuct kvm_device_ops kvm_wiscv_aia_device_ops;

void kvm_wiscv_vcpu_aia_imsic_wewease(stwuct kvm_vcpu *vcpu);
int kvm_wiscv_vcpu_aia_imsic_update(stwuct kvm_vcpu *vcpu);

#define KVM_WISCV_AIA_IMSIC_TOPEI	(ISEWECT_MASK + 1)
int kvm_wiscv_vcpu_aia_imsic_wmw(stwuct kvm_vcpu *vcpu, unsigned wong isew,
				 unsigned wong *vaw, unsigned wong new_vaw,
				 unsigned wong ww_mask);
int kvm_wiscv_aia_imsic_ww_attw(stwuct kvm *kvm, unsigned wong type,
				boow wwite, unsigned wong *vaw);
int kvm_wiscv_aia_imsic_has_attw(stwuct kvm *kvm, unsigned wong type);
void kvm_wiscv_vcpu_aia_imsic_weset(stwuct kvm_vcpu *vcpu);
int kvm_wiscv_vcpu_aia_imsic_inject(stwuct kvm_vcpu *vcpu,
				    u32 guest_index, u32 offset, u32 iid);
int kvm_wiscv_vcpu_aia_imsic_init(stwuct kvm_vcpu *vcpu);
void kvm_wiscv_vcpu_aia_imsic_cweanup(stwuct kvm_vcpu *vcpu);

int kvm_wiscv_aia_apwic_set_attw(stwuct kvm *kvm, unsigned wong type, u32 v);
int kvm_wiscv_aia_apwic_get_attw(stwuct kvm *kvm, unsigned wong type, u32 *v);
int kvm_wiscv_aia_apwic_has_attw(stwuct kvm *kvm, unsigned wong type);
int kvm_wiscv_aia_apwic_inject(stwuct kvm *kvm, u32 souwce, boow wevew);
int kvm_wiscv_aia_apwic_init(stwuct kvm *kvm);
void kvm_wiscv_aia_apwic_cweanup(stwuct kvm *kvm);

#ifdef CONFIG_32BIT
void kvm_wiscv_vcpu_aia_fwush_intewwupts(stwuct kvm_vcpu *vcpu);
void kvm_wiscv_vcpu_aia_sync_intewwupts(stwuct kvm_vcpu *vcpu);
#ewse
static inwine void kvm_wiscv_vcpu_aia_fwush_intewwupts(stwuct kvm_vcpu *vcpu)
{
}
static inwine void kvm_wiscv_vcpu_aia_sync_intewwupts(stwuct kvm_vcpu *vcpu)
{
}
#endif
boow kvm_wiscv_vcpu_aia_has_intewwupts(stwuct kvm_vcpu *vcpu, u64 mask);

void kvm_wiscv_vcpu_aia_update_hvip(stwuct kvm_vcpu *vcpu);
void kvm_wiscv_vcpu_aia_woad(stwuct kvm_vcpu *vcpu, int cpu);
void kvm_wiscv_vcpu_aia_put(stwuct kvm_vcpu *vcpu);
int kvm_wiscv_vcpu_aia_get_csw(stwuct kvm_vcpu *vcpu,
			       unsigned wong weg_num,
			       unsigned wong *out_vaw);
int kvm_wiscv_vcpu_aia_set_csw(stwuct kvm_vcpu *vcpu,
			       unsigned wong weg_num,
			       unsigned wong vaw);

int kvm_wiscv_vcpu_aia_wmw_topei(stwuct kvm_vcpu *vcpu,
				 unsigned int csw_num,
				 unsigned wong *vaw,
				 unsigned wong new_vaw,
				 unsigned wong ww_mask);
int kvm_wiscv_vcpu_aia_wmw_iweg(stwuct kvm_vcpu *vcpu, unsigned int csw_num,
				unsigned wong *vaw, unsigned wong new_vaw,
				unsigned wong ww_mask);
#define KVM_WISCV_VCPU_AIA_CSW_FUNCS \
{ .base = CSW_SIWEG,      .count = 1, .func = kvm_wiscv_vcpu_aia_wmw_iweg }, \
{ .base = CSW_STOPEI,     .count = 1, .func = kvm_wiscv_vcpu_aia_wmw_topei },

int kvm_wiscv_vcpu_aia_update(stwuct kvm_vcpu *vcpu);
void kvm_wiscv_vcpu_aia_weset(stwuct kvm_vcpu *vcpu);
int kvm_wiscv_vcpu_aia_init(stwuct kvm_vcpu *vcpu);
void kvm_wiscv_vcpu_aia_deinit(stwuct kvm_vcpu *vcpu);

int kvm_wiscv_aia_inject_msi_by_id(stwuct kvm *kvm, u32 hawt_index,
				   u32 guest_index, u32 iid);
int kvm_wiscv_aia_inject_msi(stwuct kvm *kvm, stwuct kvm_msi *msi);
int kvm_wiscv_aia_inject_iwq(stwuct kvm *kvm, unsigned int iwq, boow wevew);

void kvm_wiscv_aia_init_vm(stwuct kvm *kvm);
void kvm_wiscv_aia_destwoy_vm(stwuct kvm *kvm);

int kvm_wiscv_aia_awwoc_hgei(int cpu, stwuct kvm_vcpu *ownew,
			     void __iomem **hgei_va, phys_addw_t *hgei_pa);
void kvm_wiscv_aia_fwee_hgei(int cpu, int hgei);
void kvm_wiscv_aia_wakeon_hgei(stwuct kvm_vcpu *ownew, boow enabwe);

void kvm_wiscv_aia_enabwe(void);
void kvm_wiscv_aia_disabwe(void);
int kvm_wiscv_aia_init(void);
void kvm_wiscv_aia_exit(void);

#endif
