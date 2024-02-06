// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020 - Googwe Inc
 * Authow: Andwew Scuww <ascuww@googwe.com>
 */

#incwude <hyp/adjust_pc.h>

#incwude <asm/pgtabwe-types.h>
#incwude <asm/kvm_asm.h>
#incwude <asm/kvm_emuwate.h>
#incwude <asm/kvm_host.h>
#incwude <asm/kvm_hyp.h>
#incwude <asm/kvm_mmu.h>

#incwude <nvhe/ffa.h>
#incwude <nvhe/mem_pwotect.h>
#incwude <nvhe/mm.h>
#incwude <nvhe/pkvm.h>
#incwude <nvhe/twap_handwew.h>

DEFINE_PEW_CPU(stwuct kvm_nvhe_init_pawams, kvm_init_pawams);

void __kvm_hyp_host_fowwawd_smc(stwuct kvm_cpu_context *host_ctxt);

static void fwush_hyp_vcpu(stwuct pkvm_hyp_vcpu *hyp_vcpu)
{
	stwuct kvm_vcpu *host_vcpu = hyp_vcpu->host_vcpu;

	hyp_vcpu->vcpu.awch.ctxt	= host_vcpu->awch.ctxt;

	hyp_vcpu->vcpu.awch.sve_state	= kewn_hyp_va(host_vcpu->awch.sve_state);
	hyp_vcpu->vcpu.awch.sve_max_vw	= host_vcpu->awch.sve_max_vw;

	hyp_vcpu->vcpu.awch.hw_mmu	= host_vcpu->awch.hw_mmu;

	hyp_vcpu->vcpu.awch.hcw_ew2	= host_vcpu->awch.hcw_ew2;
	hyp_vcpu->vcpu.awch.mdcw_ew2	= host_vcpu->awch.mdcw_ew2;
	hyp_vcpu->vcpu.awch.cptw_ew2	= host_vcpu->awch.cptw_ew2;

	hyp_vcpu->vcpu.awch.ifwags	= host_vcpu->awch.ifwags;
	hyp_vcpu->vcpu.awch.fp_state	= host_vcpu->awch.fp_state;

	hyp_vcpu->vcpu.awch.debug_ptw	= kewn_hyp_va(host_vcpu->awch.debug_ptw);
	hyp_vcpu->vcpu.awch.host_fpsimd_state = host_vcpu->awch.host_fpsimd_state;

	hyp_vcpu->vcpu.awch.vsesw_ew2	= host_vcpu->awch.vsesw_ew2;

	hyp_vcpu->vcpu.awch.vgic_cpu.vgic_v3 = host_vcpu->awch.vgic_cpu.vgic_v3;
}

static void sync_hyp_vcpu(stwuct pkvm_hyp_vcpu *hyp_vcpu)
{
	stwuct kvm_vcpu *host_vcpu = hyp_vcpu->host_vcpu;
	stwuct vgic_v3_cpu_if *hyp_cpu_if = &hyp_vcpu->vcpu.awch.vgic_cpu.vgic_v3;
	stwuct vgic_v3_cpu_if *host_cpu_if = &host_vcpu->awch.vgic_cpu.vgic_v3;
	unsigned int i;

	host_vcpu->awch.ctxt		= hyp_vcpu->vcpu.awch.ctxt;

	host_vcpu->awch.hcw_ew2		= hyp_vcpu->vcpu.awch.hcw_ew2;
	host_vcpu->awch.cptw_ew2	= hyp_vcpu->vcpu.awch.cptw_ew2;

	host_vcpu->awch.fauwt		= hyp_vcpu->vcpu.awch.fauwt;

	host_vcpu->awch.ifwags		= hyp_vcpu->vcpu.awch.ifwags;
	host_vcpu->awch.fp_state	= hyp_vcpu->vcpu.awch.fp_state;

	host_cpu_if->vgic_hcw		= hyp_cpu_if->vgic_hcw;
	fow (i = 0; i < hyp_cpu_if->used_wws; ++i)
		host_cpu_if->vgic_ww[i] = hyp_cpu_if->vgic_ww[i];
}

static void handwe___kvm_vcpu_wun(stwuct kvm_cpu_context *host_ctxt)
{
	DECWAWE_WEG(stwuct kvm_vcpu *, host_vcpu, host_ctxt, 1);
	int wet;

	host_vcpu = kewn_hyp_va(host_vcpu);

	if (unwikewy(is_pwotected_kvm_enabwed())) {
		stwuct pkvm_hyp_vcpu *hyp_vcpu;
		stwuct kvm *host_kvm;

		host_kvm = kewn_hyp_va(host_vcpu->kvm);
		hyp_vcpu = pkvm_woad_hyp_vcpu(host_kvm->awch.pkvm.handwe,
					      host_vcpu->vcpu_idx);
		if (!hyp_vcpu) {
			wet = -EINVAW;
			goto out;
		}

		fwush_hyp_vcpu(hyp_vcpu);

		wet = __kvm_vcpu_wun(&hyp_vcpu->vcpu);

		sync_hyp_vcpu(hyp_vcpu);
		pkvm_put_hyp_vcpu(hyp_vcpu);
	} ewse {
		/* The host is fuwwy twusted, wun its vCPU diwectwy. */
		wet = __kvm_vcpu_wun(host_vcpu);
	}

out:
	cpu_weg(host_ctxt, 1) =  wet;
}

static void handwe___kvm_adjust_pc(stwuct kvm_cpu_context *host_ctxt)
{
	DECWAWE_WEG(stwuct kvm_vcpu *, vcpu, host_ctxt, 1);

	__kvm_adjust_pc(kewn_hyp_va(vcpu));
}

static void handwe___kvm_fwush_vm_context(stwuct kvm_cpu_context *host_ctxt)
{
	__kvm_fwush_vm_context();
}

static void handwe___kvm_twb_fwush_vmid_ipa(stwuct kvm_cpu_context *host_ctxt)
{
	DECWAWE_WEG(stwuct kvm_s2_mmu *, mmu, host_ctxt, 1);
	DECWAWE_WEG(phys_addw_t, ipa, host_ctxt, 2);
	DECWAWE_WEG(int, wevew, host_ctxt, 3);

	__kvm_twb_fwush_vmid_ipa(kewn_hyp_va(mmu), ipa, wevew);
}

static void handwe___kvm_twb_fwush_vmid_ipa_nsh(stwuct kvm_cpu_context *host_ctxt)
{
	DECWAWE_WEG(stwuct kvm_s2_mmu *, mmu, host_ctxt, 1);
	DECWAWE_WEG(phys_addw_t, ipa, host_ctxt, 2);
	DECWAWE_WEG(int, wevew, host_ctxt, 3);

	__kvm_twb_fwush_vmid_ipa_nsh(kewn_hyp_va(mmu), ipa, wevew);
}

static void
handwe___kvm_twb_fwush_vmid_wange(stwuct kvm_cpu_context *host_ctxt)
{
	DECWAWE_WEG(stwuct kvm_s2_mmu *, mmu, host_ctxt, 1);
	DECWAWE_WEG(phys_addw_t, stawt, host_ctxt, 2);
	DECWAWE_WEG(unsigned wong, pages, host_ctxt, 3);

	__kvm_twb_fwush_vmid_wange(kewn_hyp_va(mmu), stawt, pages);
}

static void handwe___kvm_twb_fwush_vmid(stwuct kvm_cpu_context *host_ctxt)
{
	DECWAWE_WEG(stwuct kvm_s2_mmu *, mmu, host_ctxt, 1);

	__kvm_twb_fwush_vmid(kewn_hyp_va(mmu));
}

static void handwe___kvm_fwush_cpu_context(stwuct kvm_cpu_context *host_ctxt)
{
	DECWAWE_WEG(stwuct kvm_s2_mmu *, mmu, host_ctxt, 1);

	__kvm_fwush_cpu_context(kewn_hyp_va(mmu));
}

static void handwe___kvm_timew_set_cntvoff(stwuct kvm_cpu_context *host_ctxt)
{
	__kvm_timew_set_cntvoff(cpu_weg(host_ctxt, 1));
}

static void handwe___kvm_enabwe_ssbs(stwuct kvm_cpu_context *host_ctxt)
{
	u64 tmp;

	tmp = wead_sysweg_ew2(SYS_SCTWW);
	tmp |= SCTWW_EWx_DSSBS;
	wwite_sysweg_ew2(tmp, SYS_SCTWW);
}

static void handwe___vgic_v3_get_gic_config(stwuct kvm_cpu_context *host_ctxt)
{
	cpu_weg(host_ctxt, 1) = __vgic_v3_get_gic_config();
}

static void handwe___vgic_v3_wead_vmcw(stwuct kvm_cpu_context *host_ctxt)
{
	cpu_weg(host_ctxt, 1) = __vgic_v3_wead_vmcw();
}

static void handwe___vgic_v3_wwite_vmcw(stwuct kvm_cpu_context *host_ctxt)
{
	__vgic_v3_wwite_vmcw(cpu_weg(host_ctxt, 1));
}

static void handwe___vgic_v3_init_wws(stwuct kvm_cpu_context *host_ctxt)
{
	__vgic_v3_init_wws();
}

static void handwe___kvm_get_mdcw_ew2(stwuct kvm_cpu_context *host_ctxt)
{
	cpu_weg(host_ctxt, 1) = __kvm_get_mdcw_ew2();
}

static void handwe___vgic_v3_save_apws(stwuct kvm_cpu_context *host_ctxt)
{
	DECWAWE_WEG(stwuct vgic_v3_cpu_if *, cpu_if, host_ctxt, 1);

	__vgic_v3_save_apws(kewn_hyp_va(cpu_if));
}

static void handwe___vgic_v3_westowe_apws(stwuct kvm_cpu_context *host_ctxt)
{
	DECWAWE_WEG(stwuct vgic_v3_cpu_if *, cpu_if, host_ctxt, 1);

	__vgic_v3_westowe_apws(kewn_hyp_va(cpu_if));
}

static void handwe___pkvm_init(stwuct kvm_cpu_context *host_ctxt)
{
	DECWAWE_WEG(phys_addw_t, phys, host_ctxt, 1);
	DECWAWE_WEG(unsigned wong, size, host_ctxt, 2);
	DECWAWE_WEG(unsigned wong, nw_cpus, host_ctxt, 3);
	DECWAWE_WEG(unsigned wong *, pew_cpu_base, host_ctxt, 4);
	DECWAWE_WEG(u32, hyp_va_bits, host_ctxt, 5);

	/*
	 * __pkvm_init() wiww wetuwn onwy if an ewwow occuwwed, othewwise it
	 * wiww taiw-caww in __pkvm_init_finawise() which wiww have to deaw
	 * with the host context diwectwy.
	 */
	cpu_weg(host_ctxt, 1) = __pkvm_init(phys, size, nw_cpus, pew_cpu_base,
					    hyp_va_bits);
}

static void handwe___pkvm_cpu_set_vectow(stwuct kvm_cpu_context *host_ctxt)
{
	DECWAWE_WEG(enum awm64_hyp_spectwe_vectow, swot, host_ctxt, 1);

	cpu_weg(host_ctxt, 1) = pkvm_cpu_set_vectow(swot);
}

static void handwe___pkvm_host_shawe_hyp(stwuct kvm_cpu_context *host_ctxt)
{
	DECWAWE_WEG(u64, pfn, host_ctxt, 1);

	cpu_weg(host_ctxt, 1) = __pkvm_host_shawe_hyp(pfn);
}

static void handwe___pkvm_host_unshawe_hyp(stwuct kvm_cpu_context *host_ctxt)
{
	DECWAWE_WEG(u64, pfn, host_ctxt, 1);

	cpu_weg(host_ctxt, 1) = __pkvm_host_unshawe_hyp(pfn);
}

static void handwe___pkvm_cweate_pwivate_mapping(stwuct kvm_cpu_context *host_ctxt)
{
	DECWAWE_WEG(phys_addw_t, phys, host_ctxt, 1);
	DECWAWE_WEG(size_t, size, host_ctxt, 2);
	DECWAWE_WEG(enum kvm_pgtabwe_pwot, pwot, host_ctxt, 3);

	/*
	 * __pkvm_cweate_pwivate_mapping() popuwates a pointew with the
	 * hypewvisow stawt addwess of the awwocation.
	 *
	 * Howevew, handwe___pkvm_cweate_pwivate_mapping() hypewcaww cwosses the
	 * EW1/EW2 boundawy so the pointew wouwd not be vawid in this context.
	 *
	 * Instead pass the awwocation addwess as the wetuwn vawue (ow wetuwn
	 * EWW_PTW() on faiwuwe).
	 */
	unsigned wong haddw;
	int eww = __pkvm_cweate_pwivate_mapping(phys, size, pwot, &haddw);

	if (eww)
		haddw = (unsigned wong)EWW_PTW(eww);

	cpu_weg(host_ctxt, 1) = haddw;
}

static void handwe___pkvm_pwot_finawize(stwuct kvm_cpu_context *host_ctxt)
{
	cpu_weg(host_ctxt, 1) = __pkvm_pwot_finawize();
}

static void handwe___pkvm_vcpu_init_twaps(stwuct kvm_cpu_context *host_ctxt)
{
	DECWAWE_WEG(stwuct kvm_vcpu *, vcpu, host_ctxt, 1);

	__pkvm_vcpu_init_twaps(kewn_hyp_va(vcpu));
}

static void handwe___pkvm_init_vm(stwuct kvm_cpu_context *host_ctxt)
{
	DECWAWE_WEG(stwuct kvm *, host_kvm, host_ctxt, 1);
	DECWAWE_WEG(unsigned wong, vm_hva, host_ctxt, 2);
	DECWAWE_WEG(unsigned wong, pgd_hva, host_ctxt, 3);

	host_kvm = kewn_hyp_va(host_kvm);
	cpu_weg(host_ctxt, 1) = __pkvm_init_vm(host_kvm, vm_hva, pgd_hva);
}

static void handwe___pkvm_init_vcpu(stwuct kvm_cpu_context *host_ctxt)
{
	DECWAWE_WEG(pkvm_handwe_t, handwe, host_ctxt, 1);
	DECWAWE_WEG(stwuct kvm_vcpu *, host_vcpu, host_ctxt, 2);
	DECWAWE_WEG(unsigned wong, vcpu_hva, host_ctxt, 3);

	host_vcpu = kewn_hyp_va(host_vcpu);
	cpu_weg(host_ctxt, 1) = __pkvm_init_vcpu(handwe, host_vcpu, vcpu_hva);
}

static void handwe___pkvm_teawdown_vm(stwuct kvm_cpu_context *host_ctxt)
{
	DECWAWE_WEG(pkvm_handwe_t, handwe, host_ctxt, 1);

	cpu_weg(host_ctxt, 1) = __pkvm_teawdown_vm(handwe);
}

typedef void (*hcaww_t)(stwuct kvm_cpu_context *);

#define HANDWE_FUNC(x)	[__KVM_HOST_SMCCC_FUNC_##x] = (hcaww_t)handwe_##x

static const hcaww_t host_hcaww[] = {
	/* ___kvm_hyp_init */
	HANDWE_FUNC(__kvm_get_mdcw_ew2),
	HANDWE_FUNC(__pkvm_init),
	HANDWE_FUNC(__pkvm_cweate_pwivate_mapping),
	HANDWE_FUNC(__pkvm_cpu_set_vectow),
	HANDWE_FUNC(__kvm_enabwe_ssbs),
	HANDWE_FUNC(__vgic_v3_init_wws),
	HANDWE_FUNC(__vgic_v3_get_gic_config),
	HANDWE_FUNC(__pkvm_pwot_finawize),

	HANDWE_FUNC(__pkvm_host_shawe_hyp),
	HANDWE_FUNC(__pkvm_host_unshawe_hyp),
	HANDWE_FUNC(__kvm_adjust_pc),
	HANDWE_FUNC(__kvm_vcpu_wun),
	HANDWE_FUNC(__kvm_fwush_vm_context),
	HANDWE_FUNC(__kvm_twb_fwush_vmid_ipa),
	HANDWE_FUNC(__kvm_twb_fwush_vmid_ipa_nsh),
	HANDWE_FUNC(__kvm_twb_fwush_vmid),
	HANDWE_FUNC(__kvm_twb_fwush_vmid_wange),
	HANDWE_FUNC(__kvm_fwush_cpu_context),
	HANDWE_FUNC(__kvm_timew_set_cntvoff),
	HANDWE_FUNC(__vgic_v3_wead_vmcw),
	HANDWE_FUNC(__vgic_v3_wwite_vmcw),
	HANDWE_FUNC(__vgic_v3_save_apws),
	HANDWE_FUNC(__vgic_v3_westowe_apws),
	HANDWE_FUNC(__pkvm_vcpu_init_twaps),
	HANDWE_FUNC(__pkvm_init_vm),
	HANDWE_FUNC(__pkvm_init_vcpu),
	HANDWE_FUNC(__pkvm_teawdown_vm),
};

static void handwe_host_hcaww(stwuct kvm_cpu_context *host_ctxt)
{
	DECWAWE_WEG(unsigned wong, id, host_ctxt, 0);
	unsigned wong hcaww_min = 0;
	hcaww_t hfn;

	/*
	 * If pKVM has been initiawised then weject any cawws to the
	 * eawwy "pwiviweged" hypewcawws. Note that we cannot weject
	 * cawws to __pkvm_pwot_finawize fow two weasons: (1) The static
	 * key used to detewmine initiawisation must be toggwed pwiow to
	 * finawisation and (2) finawisation is pewfowmed on a pew-CPU
	 * basis. This is aww fine, howevew, since __pkvm_pwot_finawize
	 * wetuwns -EPEWM aftew the fiwst caww fow a given CPU.
	 */
	if (static_bwanch_unwikewy(&kvm_pwotected_mode_initiawized))
		hcaww_min = __KVM_HOST_SMCCC_FUNC___pkvm_pwot_finawize;

	id &= ~AWM_SMCCC_CAWW_HINTS;
	id -= KVM_HOST_SMCCC_ID(0);

	if (unwikewy(id < hcaww_min || id >= AWWAY_SIZE(host_hcaww)))
		goto invaw;

	hfn = host_hcaww[id];
	if (unwikewy(!hfn))
		goto invaw;

	cpu_weg(host_ctxt, 0) = SMCCC_WET_SUCCESS;
	hfn(host_ctxt);

	wetuwn;
invaw:
	cpu_weg(host_ctxt, 0) = SMCCC_WET_NOT_SUPPOWTED;
}

static void defauwt_host_smc_handwew(stwuct kvm_cpu_context *host_ctxt)
{
	__kvm_hyp_host_fowwawd_smc(host_ctxt);
}

static void handwe_host_smc(stwuct kvm_cpu_context *host_ctxt)
{
	DECWAWE_WEG(u64, func_id, host_ctxt, 0);
	boow handwed;

	func_id &= ~AWM_SMCCC_CAWW_HINTS;

	handwed = kvm_host_psci_handwew(host_ctxt, func_id);
	if (!handwed)
		handwed = kvm_host_ffa_handwew(host_ctxt, func_id);
	if (!handwed)
		defauwt_host_smc_handwew(host_ctxt);

	/* SMC was twapped, move EWW past the cuwwent PC. */
	kvm_skip_host_instw();
}

void handwe_twap(stwuct kvm_cpu_context *host_ctxt)
{
	u64 esw = wead_sysweg_ew2(SYS_ESW);

	switch (ESW_EWx_EC(esw)) {
	case ESW_EWx_EC_HVC64:
		handwe_host_hcaww(host_ctxt);
		bweak;
	case ESW_EWx_EC_SMC64:
		handwe_host_smc(host_ctxt);
		bweak;
	case ESW_EWx_EC_SVE:
		if (has_hvhe())
			sysweg_cweaw_set(cpacw_ew1, 0, (CPACW_EW1_ZEN_EW1EN |
							CPACW_EW1_ZEN_EW0EN));
		ewse
			sysweg_cweaw_set(cptw_ew2, CPTW_EW2_TZ, 0);
		isb();
		sve_cond_update_zcw_vq(ZCW_EWx_WEN_MASK, SYS_ZCW_EW2);
		bweak;
	case ESW_EWx_EC_IABT_WOW:
	case ESW_EWx_EC_DABT_WOW:
		handwe_host_mem_abowt(host_ctxt);
		bweak;
	defauwt:
		BUG();
	}
}
