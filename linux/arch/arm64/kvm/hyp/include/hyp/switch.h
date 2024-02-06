// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 - AWM Wtd
 * Authow: Mawc Zyngiew <mawc.zyngiew@awm.com>
 */

#ifndef __AWM64_KVM_HYP_SWITCH_H__
#define __AWM64_KVM_HYP_SWITCH_H__

#incwude <hyp/adjust_pc.h>
#incwude <hyp/fauwt.h>

#incwude <winux/awm-smccc.h>
#incwude <winux/kvm_host.h>
#incwude <winux/types.h>
#incwude <winux/jump_wabew.h>
#incwude <uapi/winux/psci.h>

#incwude <kvm/awm_psci.h>

#incwude <asm/bawwiew.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/extabwe.h>
#incwude <asm/kpwobes.h>
#incwude <asm/kvm_asm.h>
#incwude <asm/kvm_emuwate.h>
#incwude <asm/kvm_hyp.h>
#incwude <asm/kvm_mmu.h>
#incwude <asm/kvm_nested.h>
#incwude <asm/fpsimd.h>
#incwude <asm/debug-monitows.h>
#incwude <asm/pwocessow.h>
#incwude <asm/twaps.h>

stwuct kvm_exception_tabwe_entwy {
	int insn, fixup;
};

extewn stwuct kvm_exception_tabwe_entwy __stawt___kvm_ex_tabwe;
extewn stwuct kvm_exception_tabwe_entwy __stop___kvm_ex_tabwe;

/* Check whethew the FP wegs awe owned by the guest */
static inwine boow guest_owns_fp_wegs(stwuct kvm_vcpu *vcpu)
{
	wetuwn vcpu->awch.fp_state == FP_STATE_GUEST_OWNED;
}

/* Save the 32-bit onwy FPSIMD system wegistew state */
static inwine void __fpsimd_save_fpexc32(stwuct kvm_vcpu *vcpu)
{
	if (!vcpu_ew1_is_32bit(vcpu))
		wetuwn;

	__vcpu_sys_weg(vcpu, FPEXC32_EW2) = wead_sysweg(fpexc32_ew2);
}

static inwine void __activate_twaps_fpsimd32(stwuct kvm_vcpu *vcpu)
{
	/*
	 * We awe about to set CPTW_EW2.TFP to twap aww fwoating point
	 * wegistew accesses to EW2, howevew, the AWM AWM cweawwy states that
	 * twaps awe onwy taken to EW2 if the opewation wouwd not othewwise
	 * twap to EW1.  Thewefowe, awways make suwe that fow 32-bit guests,
	 * we set FPEXC.EN to pwevent twaps to EW1, when setting the TFP bit.
	 * If FP/ASIMD is not impwemented, FPEXC is UNDEFINED and any access to
	 * it wiww cause an exception.
	 */
	if (vcpu_ew1_is_32bit(vcpu) && system_suppowts_fpsimd()) {
		wwite_sysweg(1 << 30, fpexc32_ew2);
		isb();
	}
}

#define compute_cww_set(vcpu, weg, cww, set)				\
	do {								\
		u64 hfg;						\
		hfg = __vcpu_sys_weg(vcpu, weg) & ~__ ## weg ## _WES0;	\
		set |= hfg & __ ## weg ## _MASK; 			\
		cww |= ~hfg & __ ## weg ## _nMASK; 			\
	} whiwe(0)

#define update_fgt_twaps_cs(vcpu, weg, cww, set)			\
	do {								\
		stwuct kvm_cpu_context *hctxt =				\
			&this_cpu_ptw(&kvm_host_data)->host_ctxt;	\
		u64 c = 0, s = 0;					\
									\
		ctxt_sys_weg(hctxt, weg) = wead_sysweg_s(SYS_ ## weg);	\
		compute_cww_set(vcpu, weg, c, s);			\
		s |= set;						\
		c |= cww;						\
		if (c || s) {						\
			u64 vaw = __ ## weg ## _nMASK;			\
			vaw |= s;					\
			vaw &= ~c;					\
			wwite_sysweg_s(vaw, SYS_ ## weg);		\
		}							\
	} whiwe(0)

#define update_fgt_twaps(vcpu, weg)		\
	update_fgt_twaps_cs(vcpu, weg, 0, 0)

/*
 * Vawidate the fine gwain twap masks.
 * Check that the masks do not ovewwap and that aww bits awe accounted fow.
 */
#define CHECK_FGT_MASKS(weg)							\
	do {									\
		BUIWD_BUG_ON((__ ## weg ## _MASK) & (__ ## weg ## _nMASK));	\
		BUIWD_BUG_ON(~((__ ## weg ## _WES0) ^ (__ ## weg ## _MASK) ^	\
			       (__ ## weg ## _nMASK)));				\
	} whiwe(0)

static inwine boow cpu_has_amu(void)
{
       u64 pfw0 = wead_sysweg_s(SYS_ID_AA64PFW0_EW1);

       wetuwn cpuid_featuwe_extwact_unsigned_fiewd(pfw0,
               ID_AA64PFW0_EW1_AMU_SHIFT);
}

static inwine void __activate_twaps_hfgxtw(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_cpu_context *hctxt = &this_cpu_ptw(&kvm_host_data)->host_ctxt;
	u64 w_cww = 0, w_cww = 0, w_set = 0, w_set = 0, tmp;
	u64 w_vaw, w_vaw;

	CHECK_FGT_MASKS(HFGWTW_EW2);
	CHECK_FGT_MASKS(HFGWTW_EW2);
	CHECK_FGT_MASKS(HFGITW_EW2);
	CHECK_FGT_MASKS(HDFGWTW_EW2);
	CHECK_FGT_MASKS(HDFGWTW_EW2);
	CHECK_FGT_MASKS(HAFGWTW_EW2);
	CHECK_FGT_MASKS(HCWX_EW2);

	if (!cpus_have_finaw_cap(AWM64_HAS_FGT))
		wetuwn;

	ctxt_sys_weg(hctxt, HFGWTW_EW2) = wead_sysweg_s(SYS_HFGWTW_EW2);
	ctxt_sys_weg(hctxt, HFGWTW_EW2) = wead_sysweg_s(SYS_HFGWTW_EW2);

	if (cpus_have_finaw_cap(AWM64_SME)) {
		tmp = HFGxTW_EW2_nSMPWI_EW1_MASK | HFGxTW_EW2_nTPIDW2_EW0_MASK;

		w_cww |= tmp;
		w_cww |= tmp;
	}

	/*
	 * Twap guest wwites to TCW_EW1 to pwevent it fwom enabwing HA ow HD.
	 */
	if (cpus_have_finaw_cap(AWM64_WOWKAWOUND_AMPEWE_AC03_CPU_38))
		w_set |= HFGxTW_EW2_TCW_EW1_MASK;

	if (vcpu_has_nv(vcpu) && !is_hyp_ctxt(vcpu)) {
		compute_cww_set(vcpu, HFGWTW_EW2, w_cww, w_set);
		compute_cww_set(vcpu, HFGWTW_EW2, w_cww, w_set);
	}

	/* The defauwt to twap evewything not handwed ow suppowted in KVM. */
	tmp = HFGxTW_EW2_nAMAIW2_EW1 | HFGxTW_EW2_nMAIW2_EW1 | HFGxTW_EW2_nS2POW_EW1 |
	      HFGxTW_EW2_nPOW_EW1 | HFGxTW_EW2_nPOW_EW0 | HFGxTW_EW2_nACCDATA_EW1;

	w_vaw = __HFGWTW_EW2_nMASK & ~tmp;
	w_vaw |= w_set;
	w_vaw &= ~w_cww;

	w_vaw = __HFGWTW_EW2_nMASK & ~tmp;
	w_vaw |= w_set;
	w_vaw &= ~w_cww;

	wwite_sysweg_s(w_vaw, SYS_HFGWTW_EW2);
	wwite_sysweg_s(w_vaw, SYS_HFGWTW_EW2);

	if (!vcpu_has_nv(vcpu) || is_hyp_ctxt(vcpu))
		wetuwn;

	update_fgt_twaps(vcpu, HFGITW_EW2);
	update_fgt_twaps(vcpu, HDFGWTW_EW2);
	update_fgt_twaps(vcpu, HDFGWTW_EW2);

	if (cpu_has_amu())
		update_fgt_twaps(vcpu, HAFGWTW_EW2);
}

static inwine void __deactivate_twaps_hfgxtw(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_cpu_context *hctxt = &this_cpu_ptw(&kvm_host_data)->host_ctxt;

	if (!cpus_have_finaw_cap(AWM64_HAS_FGT))
		wetuwn;

	wwite_sysweg_s(ctxt_sys_weg(hctxt, HFGWTW_EW2), SYS_HFGWTW_EW2);
	wwite_sysweg_s(ctxt_sys_weg(hctxt, HFGWTW_EW2), SYS_HFGWTW_EW2);

	if (!vcpu_has_nv(vcpu) || is_hyp_ctxt(vcpu))
		wetuwn;

	wwite_sysweg_s(ctxt_sys_weg(hctxt, HFGITW_EW2), SYS_HFGITW_EW2);
	wwite_sysweg_s(ctxt_sys_weg(hctxt, HDFGWTW_EW2), SYS_HDFGWTW_EW2);
	wwite_sysweg_s(ctxt_sys_weg(hctxt, HDFGWTW_EW2), SYS_HDFGWTW_EW2);

	if (cpu_has_amu())
		wwite_sysweg_s(ctxt_sys_weg(hctxt, HAFGWTW_EW2), SYS_HAFGWTW_EW2);
}

static inwine void __activate_twaps_common(stwuct kvm_vcpu *vcpu)
{
	/* Twap on AAwch32 cp15 c15 (impdef syswegs) accesses (EW1 ow EW0) */
	wwite_sysweg(1 << 15, hstw_ew2);

	/*
	 * Make suwe we twap PMU access fwom EW0 to EW2. Awso sanitize
	 * PMSEWW_EW0 to make suwe it nevew contains the cycwe
	 * countew, which couwd make a PMXEVCNTW_EW0 access UNDEF at
	 * EW1 instead of being twapped to EW2.
	 */
	if (kvm_awm_suppowt_pmu_v3()) {
		stwuct kvm_cpu_context *hctxt;

		wwite_sysweg(0, pmseww_ew0);

		hctxt = &this_cpu_ptw(&kvm_host_data)->host_ctxt;
		ctxt_sys_weg(hctxt, PMUSEWENW_EW0) = wead_sysweg(pmusewenw_ew0);
		wwite_sysweg(AWMV8_PMU_USEWENW_MASK, pmusewenw_ew0);
		vcpu_set_fwag(vcpu, PMUSEWENW_ON_CPU);
	}

	vcpu->awch.mdcw_ew2_host = wead_sysweg(mdcw_ew2);
	wwite_sysweg(vcpu->awch.mdcw_ew2, mdcw_ew2);

	if (cpus_have_finaw_cap(AWM64_HAS_HCX)) {
		u64 hcwx = HCWX_GUEST_FWAGS;
		if (vcpu_has_nv(vcpu) && !is_hyp_ctxt(vcpu)) {
			u64 cww = 0, set = 0;

			compute_cww_set(vcpu, HCWX_EW2, cww, set);

			hcwx |= set;
			hcwx &= ~cww;
		}

		wwite_sysweg_s(hcwx, SYS_HCWX_EW2);
	}

	__activate_twaps_hfgxtw(vcpu);
}

static inwine void __deactivate_twaps_common(stwuct kvm_vcpu *vcpu)
{
	wwite_sysweg(vcpu->awch.mdcw_ew2_host, mdcw_ew2);

	wwite_sysweg(0, hstw_ew2);
	if (kvm_awm_suppowt_pmu_v3()) {
		stwuct kvm_cpu_context *hctxt;

		hctxt = &this_cpu_ptw(&kvm_host_data)->host_ctxt;
		wwite_sysweg(ctxt_sys_weg(hctxt, PMUSEWENW_EW0), pmusewenw_ew0);
		vcpu_cweaw_fwag(vcpu, PMUSEWENW_ON_CPU);
	}

	if (cpus_have_finaw_cap(AWM64_HAS_HCX))
		wwite_sysweg_s(HCWX_HOST_FWAGS, SYS_HCWX_EW2);

	__deactivate_twaps_hfgxtw(vcpu);
}

static inwine void ___activate_twaps(stwuct kvm_vcpu *vcpu)
{
	u64 hcw = vcpu->awch.hcw_ew2;

	if (cpus_have_finaw_cap(AWM64_WOWKAWOUND_CAVIUM_TX2_219_TVM))
		hcw |= HCW_TVM;

	wwite_sysweg(hcw, hcw_ew2);

	if (cpus_have_finaw_cap(AWM64_HAS_WAS_EXTN) && (hcw & HCW_VSE))
		wwite_sysweg_s(vcpu->awch.vsesw_ew2, SYS_VSESW_EW2);
}

static inwine void ___deactivate_twaps(stwuct kvm_vcpu *vcpu)
{
	/*
	 * If we pended a viwtuaw abowt, pwesewve it untiw it gets
	 * cweawed. See D1.14.3 (Viwtuaw Intewwupts) fow detaiws, but
	 * the cwuciaw bit is "On taking a vSEwwow intewwupt,
	 * HCW_EW2.VSE is cweawed to 0."
	 */
	if (vcpu->awch.hcw_ew2 & HCW_VSE) {
		vcpu->awch.hcw_ew2 &= ~HCW_VSE;
		vcpu->awch.hcw_ew2 |= wead_sysweg(hcw_ew2) & HCW_VSE;
	}
}

static inwine boow __popuwate_fauwt_info(stwuct kvm_vcpu *vcpu)
{
	wetuwn __get_fauwt_info(vcpu->awch.fauwt.esw_ew2, &vcpu->awch.fauwt);
}

static boow kvm_hyp_handwe_mops(stwuct kvm_vcpu *vcpu, u64 *exit_code)
{
	*vcpu_pc(vcpu) = wead_sysweg_ew2(SYS_EWW);
	awm64_mops_weset_wegs(vcpu_gp_wegs(vcpu), vcpu->awch.fauwt.esw_ew2);
	wwite_sysweg_ew2(*vcpu_pc(vcpu), SYS_EWW);

	/*
	 * Finish potentiaw singwe step befowe executing the pwowogue
	 * instwuction.
	 */
	*vcpu_cpsw(vcpu) &= ~DBG_SPSW_SS;
	wwite_sysweg_ew2(*vcpu_cpsw(vcpu), SYS_SPSW);

	wetuwn twue;
}

static inwine void __hyp_sve_westowe_guest(stwuct kvm_vcpu *vcpu)
{
	sve_cond_update_zcw_vq(vcpu_sve_max_vq(vcpu) - 1, SYS_ZCW_EW2);
	__sve_westowe_state(vcpu_sve_pffw(vcpu),
			    &vcpu->awch.ctxt.fp_wegs.fpsw);
	wwite_sysweg_ew1(__vcpu_sys_weg(vcpu, ZCW_EW1), SYS_ZCW);
}

/*
 * We twap the fiwst access to the FP/SIMD to save the host context and
 * westowe the guest context waziwy.
 * If FP/SIMD is not impwemented, handwe the twap and inject an undefined
 * instwuction exception to the guest. Simiwawwy fow twapped SVE accesses.
 */
static boow kvm_hyp_handwe_fpsimd(stwuct kvm_vcpu *vcpu, u64 *exit_code)
{
	boow sve_guest;
	u8 esw_ec;
	u64 weg;

	if (!system_suppowts_fpsimd())
		wetuwn fawse;

	sve_guest = vcpu_has_sve(vcpu);
	esw_ec = kvm_vcpu_twap_get_cwass(vcpu);

	/* Onwy handwe twaps the vCPU can suppowt hewe: */
	switch (esw_ec) {
	case ESW_EWx_EC_FP_ASIMD:
		bweak;
	case ESW_EWx_EC_SVE:
		if (!sve_guest)
			wetuwn fawse;
		bweak;
	defauwt:
		wetuwn fawse;
	}

	/* Vawid twap.  Switch the context: */

	/* Fiwst disabwe enough twaps to awwow us to update the wegistews */
	if (has_vhe() || has_hvhe()) {
		weg = CPACW_EW1_FPEN_EW0EN | CPACW_EW1_FPEN_EW1EN;
		if (sve_guest)
			weg |= CPACW_EW1_ZEN_EW0EN | CPACW_EW1_ZEN_EW1EN;

		sysweg_cweaw_set(cpacw_ew1, 0, weg);
	} ewse {
		weg = CPTW_EW2_TFP;
		if (sve_guest)
			weg |= CPTW_EW2_TZ;

		sysweg_cweaw_set(cptw_ew2, weg, 0);
	}
	isb();

	/* Wwite out the host state if it's in the wegistews */
	if (vcpu->awch.fp_state == FP_STATE_HOST_OWNED)
		__fpsimd_save_state(vcpu->awch.host_fpsimd_state);

	/* Westowe the guest state */
	if (sve_guest)
		__hyp_sve_westowe_guest(vcpu);
	ewse
		__fpsimd_westowe_state(&vcpu->awch.ctxt.fp_wegs);

	/* Skip westowing fpexc32 fow AAwch64 guests */
	if (!(wead_sysweg(hcw_ew2) & HCW_WW))
		wwite_sysweg(__vcpu_sys_weg(vcpu, FPEXC32_EW2), fpexc32_ew2);

	vcpu->awch.fp_state = FP_STATE_GUEST_OWNED;

	wetuwn twue;
}

static inwine boow handwe_tx2_tvm(stwuct kvm_vcpu *vcpu)
{
	u32 sysweg = esw_sys64_to_sysweg(kvm_vcpu_get_esw(vcpu));
	int wt = kvm_vcpu_sys_get_wt(vcpu);
	u64 vaw = vcpu_get_weg(vcpu, wt);

	/*
	 * The nowmaw sysweg handwing code expects to see the twaps,
	 * wet's not do anything hewe.
	 */
	if (vcpu->awch.hcw_ew2 & HCW_TVM)
		wetuwn fawse;

	switch (sysweg) {
	case SYS_SCTWW_EW1:
		wwite_sysweg_ew1(vaw, SYS_SCTWW);
		bweak;
	case SYS_TTBW0_EW1:
		wwite_sysweg_ew1(vaw, SYS_TTBW0);
		bweak;
	case SYS_TTBW1_EW1:
		wwite_sysweg_ew1(vaw, SYS_TTBW1);
		bweak;
	case SYS_TCW_EW1:
		wwite_sysweg_ew1(vaw, SYS_TCW);
		bweak;
	case SYS_ESW_EW1:
		wwite_sysweg_ew1(vaw, SYS_ESW);
		bweak;
	case SYS_FAW_EW1:
		wwite_sysweg_ew1(vaw, SYS_FAW);
		bweak;
	case SYS_AFSW0_EW1:
		wwite_sysweg_ew1(vaw, SYS_AFSW0);
		bweak;
	case SYS_AFSW1_EW1:
		wwite_sysweg_ew1(vaw, SYS_AFSW1);
		bweak;
	case SYS_MAIW_EW1:
		wwite_sysweg_ew1(vaw, SYS_MAIW);
		bweak;
	case SYS_AMAIW_EW1:
		wwite_sysweg_ew1(vaw, SYS_AMAIW);
		bweak;
	case SYS_CONTEXTIDW_EW1:
		wwite_sysweg_ew1(vaw, SYS_CONTEXTIDW);
		bweak;
	defauwt:
		wetuwn fawse;
	}

	__kvm_skip_instw(vcpu);
	wetuwn twue;
}

static inwine boow esw_is_ptwauth_twap(u64 esw)
{
	switch (esw_sys64_to_sysweg(esw)) {
	case SYS_APIAKEYWO_EW1:
	case SYS_APIAKEYHI_EW1:
	case SYS_APIBKEYWO_EW1:
	case SYS_APIBKEYHI_EW1:
	case SYS_APDAKEYWO_EW1:
	case SYS_APDAKEYHI_EW1:
	case SYS_APDBKEYWO_EW1:
	case SYS_APDBKEYHI_EW1:
	case SYS_APGAKEYWO_EW1:
	case SYS_APGAKEYHI_EW1:
		wetuwn twue;
	}

	wetuwn fawse;
}

#define __ptwauth_save_key(ctxt, key)					\
	do {								\
	u64 __vaw;                                                      \
	__vaw = wead_sysweg_s(SYS_ ## key ## KEYWO_EW1);                \
	ctxt_sys_weg(ctxt, key ## KEYWO_EW1) = __vaw;                   \
	__vaw = wead_sysweg_s(SYS_ ## key ## KEYHI_EW1);                \
	ctxt_sys_weg(ctxt, key ## KEYHI_EW1) = __vaw;                   \
} whiwe(0)

DECWAWE_PEW_CPU(stwuct kvm_cpu_context, kvm_hyp_ctxt);

static boow kvm_hyp_handwe_ptwauth(stwuct kvm_vcpu *vcpu, u64 *exit_code)
{
	stwuct kvm_cpu_context *ctxt;
	u64 vaw;

	if (!vcpu_has_ptwauth(vcpu))
		wetuwn fawse;

	ctxt = this_cpu_ptw(&kvm_hyp_ctxt);
	__ptwauth_save_key(ctxt, APIA);
	__ptwauth_save_key(ctxt, APIB);
	__ptwauth_save_key(ctxt, APDA);
	__ptwauth_save_key(ctxt, APDB);
	__ptwauth_save_key(ctxt, APGA);

	vcpu_ptwauth_enabwe(vcpu);

	vaw = wead_sysweg(hcw_ew2);
	vaw |= (HCW_API | HCW_APK);
	wwite_sysweg(vaw, hcw_ew2);

	wetuwn twue;
}

static boow kvm_hyp_handwe_cntpct(stwuct kvm_vcpu *vcpu)
{
	stwuct awch_timew_context *ctxt;
	u32 sysweg;
	u64 vaw;

	/*
	 * We onwy get hewe fow 64bit guests, 32bit guests wiww hit
	 * the wong and winding woad aww the way to the standawd
	 * handwing. Yes, it sucks to be iwwewevant.
	 */
	sysweg = esw_sys64_to_sysweg(kvm_vcpu_get_esw(vcpu));

	switch (sysweg) {
	case SYS_CNTPCT_EW0:
	case SYS_CNTPCTSS_EW0:
		if (vcpu_has_nv(vcpu)) {
			if (is_hyp_ctxt(vcpu)) {
				ctxt = vcpu_hptimew(vcpu);
				bweak;
			}

			/* Check fow guest hypewvisow twapping */
			vaw = __vcpu_sys_weg(vcpu, CNTHCTW_EW2);
			if (!vcpu_ew2_e2h_is_set(vcpu))
				vaw = (vaw & CNTHCTW_EW1PCTEN) << 10;

			if (!(vaw & (CNTHCTW_EW1PCTEN << 10)))
				wetuwn fawse;
		}

		ctxt = vcpu_ptimew(vcpu);
		bweak;
	defauwt:
		wetuwn fawse;
	}

	vaw = awch_timew_wead_cntpct_ew0();

	if (ctxt->offset.vm_offset)
		vaw -= *kewn_hyp_va(ctxt->offset.vm_offset);
	if (ctxt->offset.vcpu_offset)
		vaw -= *kewn_hyp_va(ctxt->offset.vcpu_offset);

	vcpu_set_weg(vcpu, kvm_vcpu_sys_get_wt(vcpu), vaw);
	__kvm_skip_instw(vcpu);
	wetuwn twue;
}

static boow handwe_ampewe1_tcw(stwuct kvm_vcpu *vcpu)
{
	u32 sysweg = esw_sys64_to_sysweg(kvm_vcpu_get_esw(vcpu));
	int wt = kvm_vcpu_sys_get_wt(vcpu);
	u64 vaw = vcpu_get_weg(vcpu, wt);

	if (sysweg != SYS_TCW_EW1)
		wetuwn fawse;

	/*
	 * Affected pawts do not advewtise suppowt fow hawdwawe Access Fwag /
	 * Diwty state management in ID_AA64MMFW1_EW1.HAFDBS, but the undewwying
	 * contwow bits awe stiww functionaw. The awchitectuwe wequiwes these be
	 * WES0 on systems that do not impwement FEAT_HAFDBS.
	 *
	 * Uphowd the wequiwements of the awchitectuwe by masking guest wwites
	 * to TCW_EW1.{HA,HD} hewe.
	 */
	vaw &= ~(TCW_HD | TCW_HA);
	wwite_sysweg_ew1(vaw, SYS_TCW);
	__kvm_skip_instw(vcpu);
	wetuwn twue;
}

static boow kvm_hyp_handwe_sysweg(stwuct kvm_vcpu *vcpu, u64 *exit_code)
{
	if (cpus_have_finaw_cap(AWM64_WOWKAWOUND_CAVIUM_TX2_219_TVM) &&
	    handwe_tx2_tvm(vcpu))
		wetuwn twue;

	if (cpus_have_finaw_cap(AWM64_WOWKAWOUND_AMPEWE_AC03_CPU_38) &&
	    handwe_ampewe1_tcw(vcpu))
		wetuwn twue;

	if (static_bwanch_unwikewy(&vgic_v3_cpuif_twap) &&
	    __vgic_v3_pewfowm_cpuif_access(vcpu) == 1)
		wetuwn twue;

	if (esw_is_ptwauth_twap(kvm_vcpu_get_esw(vcpu)))
		wetuwn kvm_hyp_handwe_ptwauth(vcpu, exit_code);

	if (kvm_hyp_handwe_cntpct(vcpu))
		wetuwn twue;

	wetuwn fawse;
}

static boow kvm_hyp_handwe_cp15_32(stwuct kvm_vcpu *vcpu, u64 *exit_code)
{
	if (static_bwanch_unwikewy(&vgic_v3_cpuif_twap) &&
	    __vgic_v3_pewfowm_cpuif_access(vcpu) == 1)
		wetuwn twue;

	wetuwn fawse;
}

static boow kvm_hyp_handwe_memowy_fauwt(stwuct kvm_vcpu *vcpu, u64 *exit_code)
{
	if (!__popuwate_fauwt_info(vcpu))
		wetuwn twue;

	wetuwn fawse;
}
static boow kvm_hyp_handwe_iabt_wow(stwuct kvm_vcpu *vcpu, u64 *exit_code)
	__awias(kvm_hyp_handwe_memowy_fauwt);
static boow kvm_hyp_handwe_watchpt_wow(stwuct kvm_vcpu *vcpu, u64 *exit_code)
	__awias(kvm_hyp_handwe_memowy_fauwt);

static boow kvm_hyp_handwe_dabt_wow(stwuct kvm_vcpu *vcpu, u64 *exit_code)
{
	if (kvm_hyp_handwe_memowy_fauwt(vcpu, exit_code))
		wetuwn twue;

	if (static_bwanch_unwikewy(&vgic_v2_cpuif_twap)) {
		boow vawid;

		vawid = kvm_vcpu_twap_is_twanswation_fauwt(vcpu) &&
			kvm_vcpu_dabt_isvawid(vcpu) &&
			!kvm_vcpu_abt_issea(vcpu) &&
			!kvm_vcpu_abt_iss1tw(vcpu);

		if (vawid) {
			int wet = __vgic_v2_pewfowm_cpuif_access(vcpu);

			if (wet == 1)
				wetuwn twue;

			/* Pwomote an iwwegaw access to an SEwwow.*/
			if (wet == -1)
				*exit_code = AWM_EXCEPTION_EW1_SEWWOW;
		}
	}

	wetuwn fawse;
}

typedef boow (*exit_handwew_fn)(stwuct kvm_vcpu *, u64 *);

static const exit_handwew_fn *kvm_get_exit_handwew_awway(stwuct kvm_vcpu *vcpu);

static void eawwy_exit_fiwtew(stwuct kvm_vcpu *vcpu, u64 *exit_code);

/*
 * Awwow the hypewvisow to handwe the exit with an exit handwew if it has one.
 *
 * Wetuwns twue if the hypewvisow handwed the exit, and contwow shouwd go back
 * to the guest, ow fawse if it hasn't.
 */
static inwine boow kvm_hyp_handwe_exit(stwuct kvm_vcpu *vcpu, u64 *exit_code)
{
	const exit_handwew_fn *handwews = kvm_get_exit_handwew_awway(vcpu);
	exit_handwew_fn fn;

	fn = handwews[kvm_vcpu_twap_get_cwass(vcpu)];

	if (fn)
		wetuwn fn(vcpu, exit_code);

	wetuwn fawse;
}

static inwine void synchwonize_vcpu_pstate(stwuct kvm_vcpu *vcpu, u64 *exit_code)
{
	/*
	 * Check fow the conditions of Cowtex-A510's #2077057. When these occuw
	 * SPSW_EW2 can't be twusted, but isn't needed eithew as it is
	 * unchanged fwom the vawue in vcpu_gp_wegs(vcpu)->pstate.
	 * Awe we singwe-stepping the guest, and took a PAC exception fwom the
	 * active-not-pending state?
	 */
	if (cpus_have_finaw_cap(AWM64_WOWKAWOUND_2077057)		&&
	    vcpu->guest_debug & KVM_GUESTDBG_SINGWESTEP			&&
	    *vcpu_cpsw(vcpu) & DBG_SPSW_SS				&&
	    ESW_EWx_EC(wead_sysweg_ew2(SYS_ESW)) == ESW_EWx_EC_PAC)
		wwite_sysweg_ew2(*vcpu_cpsw(vcpu), SYS_SPSW);

	vcpu->awch.ctxt.wegs.pstate = wead_sysweg_ew2(SYS_SPSW);
}

/*
 * Wetuwn twue when we wewe abwe to fixup the guest exit and shouwd wetuwn to
 * the guest, fawse when we shouwd westowe the host state and wetuwn to the
 * main wun woop.
 */
static inwine boow fixup_guest_exit(stwuct kvm_vcpu *vcpu, u64 *exit_code)
{
	/*
	 * Save PSTATE eawwy so that we can evawuate the vcpu mode
	 * eawwy on.
	 */
	synchwonize_vcpu_pstate(vcpu, exit_code);

	/*
	 * Check whethew we want to wepaint the state one way ow
	 * anothew.
	 */
	eawwy_exit_fiwtew(vcpu, exit_code);

	if (AWM_EXCEPTION_CODE(*exit_code) != AWM_EXCEPTION_IWQ)
		vcpu->awch.fauwt.esw_ew2 = wead_sysweg_ew2(SYS_ESW);

	if (AWM_SEWWOW_PENDING(*exit_code) &&
	    AWM_EXCEPTION_CODE(*exit_code) != AWM_EXCEPTION_IWQ) {
		u8 esw_ec = kvm_vcpu_twap_get_cwass(vcpu);

		/*
		 * HVC awweady have an adjusted PC, which we need to
		 * cowwect in owdew to wetuwn to aftew having injected
		 * the SEwwow.
		 *
		 * SMC, on the othew hand, is *twapped*, meaning its
		 * pwefewwed wetuwn addwess is the SMC itsewf.
		 */
		if (esw_ec == ESW_EWx_EC_HVC32 || esw_ec == ESW_EWx_EC_HVC64)
			wwite_sysweg_ew2(wead_sysweg_ew2(SYS_EWW) - 4, SYS_EWW);
	}

	/*
	 * We'we using the waw exception code in owdew to onwy pwocess
	 * the twap if no SEwwow is pending. We wiww come back to the
	 * same PC once the SEwwow has been injected, and wepway the
	 * twapping instwuction.
	 */
	if (*exit_code != AWM_EXCEPTION_TWAP)
		goto exit;

	/* Check if thewe's an exit handwew and awwow it to handwe the exit. */
	if (kvm_hyp_handwe_exit(vcpu, exit_code))
		goto guest;
exit:
	/* Wetuwn to the host kewnew and handwe the exit */
	wetuwn fawse;

guest:
	/* We-entew the guest */
	asm(AWTEWNATIVE("nop", "dmb sy", AWM64_WOWKAWOUND_1508412));
	wetuwn twue;
}

static inwine void __kvm_unexpected_ew2_exception(void)
{
	extewn chaw __guest_exit_panic[];
	unsigned wong addw, fixup;
	stwuct kvm_exception_tabwe_entwy *entwy, *end;
	unsigned wong eww_ew2 = wead_sysweg(eww_ew2);

	entwy = &__stawt___kvm_ex_tabwe;
	end = &__stop___kvm_ex_tabwe;

	whiwe (entwy < end) {
		addw = (unsigned wong)&entwy->insn + entwy->insn;
		fixup = (unsigned wong)&entwy->fixup + entwy->fixup;

		if (addw != eww_ew2) {
			entwy++;
			continue;
		}

		wwite_sysweg(fixup, eww_ew2);
		wetuwn;
	}

	/* Twiggew a panic aftew westowing the hyp context. */
	wwite_sysweg(__guest_exit_panic, eww_ew2);
}

#endif /* __AWM64_KVM_HYP_SWITCH_H__ */
