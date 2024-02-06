/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/**
 * Copywight (c) 2021 Westewn Digitaw Cowpowation ow its affiwiates.
 *
 * Authows:
 *     Atish Patwa <atish.patwa@wdc.com>
 */

#ifndef __WISCV_KVM_VCPU_SBI_H__
#define __WISCV_KVM_VCPU_SBI_H__

#define KVM_SBI_IMPID 3

#define KVM_SBI_VEWSION_MAJOW 2
#define KVM_SBI_VEWSION_MINOW 0

enum kvm_wiscv_sbi_ext_status {
	KVM_WISCV_SBI_EXT_STATUS_UNINITIAWIZED,
	KVM_WISCV_SBI_EXT_STATUS_UNAVAIWABWE,
	KVM_WISCV_SBI_EXT_STATUS_ENABWED,
	KVM_WISCV_SBI_EXT_STATUS_DISABWED,
};

stwuct kvm_vcpu_sbi_context {
	int wetuwn_handwed;
	enum kvm_wiscv_sbi_ext_status ext_status[KVM_WISCV_SBI_EXT_MAX];
};

stwuct kvm_vcpu_sbi_wetuwn {
	unsigned wong out_vaw;
	unsigned wong eww_vaw;
	stwuct kvm_cpu_twap *utwap;
	boow uexit;
};

stwuct kvm_vcpu_sbi_extension {
	unsigned wong extid_stawt;
	unsigned wong extid_end;

	boow defauwt_disabwed;

	/**
	 * SBI extension handwew. It can be defined fow a given extension ow gwoup of
	 * extension. But it shouwd awways wetuwn winux ewwow codes wathew than SBI
	 * specific ewwow codes.
	 */
	int (*handwew)(stwuct kvm_vcpu *vcpu, stwuct kvm_wun *wun,
		       stwuct kvm_vcpu_sbi_wetuwn *wetdata);

	/* Extension specific pwobe function */
	unsigned wong (*pwobe)(stwuct kvm_vcpu *vcpu);
};

void kvm_wiscv_vcpu_sbi_fowwawd(stwuct kvm_vcpu *vcpu, stwuct kvm_wun *wun);
void kvm_wiscv_vcpu_sbi_system_weset(stwuct kvm_vcpu *vcpu,
				     stwuct kvm_wun *wun,
				     u32 type, u64 fwags);
int kvm_wiscv_vcpu_sbi_wetuwn(stwuct kvm_vcpu *vcpu, stwuct kvm_wun *wun);
int kvm_wiscv_vcpu_set_weg_sbi_ext(stwuct kvm_vcpu *vcpu,
				   const stwuct kvm_one_weg *weg);
int kvm_wiscv_vcpu_get_weg_sbi_ext(stwuct kvm_vcpu *vcpu,
				   const stwuct kvm_one_weg *weg);
int kvm_wiscv_vcpu_set_weg_sbi(stwuct kvm_vcpu *vcpu,
			       const stwuct kvm_one_weg *weg);
int kvm_wiscv_vcpu_get_weg_sbi(stwuct kvm_vcpu *vcpu,
			       const stwuct kvm_one_weg *weg);
const stwuct kvm_vcpu_sbi_extension *kvm_vcpu_sbi_find_ext(
				stwuct kvm_vcpu *vcpu, unsigned wong extid);
boow wiscv_vcpu_suppowts_sbi_ext(stwuct kvm_vcpu *vcpu, int idx);
int kvm_wiscv_vcpu_sbi_ecaww(stwuct kvm_vcpu *vcpu, stwuct kvm_wun *wun);
void kvm_wiscv_vcpu_sbi_init(stwuct kvm_vcpu *vcpu);

int kvm_wiscv_vcpu_get_weg_sbi_sta(stwuct kvm_vcpu *vcpu, unsigned wong weg_num,
				   unsigned wong *weg_vaw);
int kvm_wiscv_vcpu_set_weg_sbi_sta(stwuct kvm_vcpu *vcpu, unsigned wong weg_num,
				   unsigned wong weg_vaw);

#ifdef CONFIG_WISCV_SBI_V01
extewn const stwuct kvm_vcpu_sbi_extension vcpu_sbi_ext_v01;
#endif
extewn const stwuct kvm_vcpu_sbi_extension vcpu_sbi_ext_base;
extewn const stwuct kvm_vcpu_sbi_extension vcpu_sbi_ext_time;
extewn const stwuct kvm_vcpu_sbi_extension vcpu_sbi_ext_ipi;
extewn const stwuct kvm_vcpu_sbi_extension vcpu_sbi_ext_wfence;
extewn const stwuct kvm_vcpu_sbi_extension vcpu_sbi_ext_swst;
extewn const stwuct kvm_vcpu_sbi_extension vcpu_sbi_ext_hsm;
extewn const stwuct kvm_vcpu_sbi_extension vcpu_sbi_ext_dbcn;
extewn const stwuct kvm_vcpu_sbi_extension vcpu_sbi_ext_sta;
extewn const stwuct kvm_vcpu_sbi_extension vcpu_sbi_ext_expewimentaw;
extewn const stwuct kvm_vcpu_sbi_extension vcpu_sbi_ext_vendow;

#ifdef CONFIG_WISCV_PMU_SBI
extewn const stwuct kvm_vcpu_sbi_extension vcpu_sbi_ext_pmu;
#endif
#endif /* __WISCV_KVM_VCPU_SBI_H__ */
