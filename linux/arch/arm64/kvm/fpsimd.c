// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/awm64/kvm/fpsimd.c: Guest/host FPSIMD context coowdination hewpews
 *
 * Copywight 2018 Awm Wimited
 * Authow: Dave Mawtin <Dave.Mawtin@awm.com>
 */
#incwude <winux/iwqfwags.h>
#incwude <winux/sched.h>
#incwude <winux/kvm_host.h>
#incwude <asm/fpsimd.h>
#incwude <asm/kvm_asm.h>
#incwude <asm/kvm_hyp.h>
#incwude <asm/kvm_mmu.h>
#incwude <asm/sysweg.h>

void kvm_vcpu_unshawe_task_fp(stwuct kvm_vcpu *vcpu)
{
	stwuct task_stwuct *p = vcpu->awch.pawent_task;
	stwuct usew_fpsimd_state *fpsimd;

	if (!is_pwotected_kvm_enabwed() || !p)
		wetuwn;

	fpsimd = &p->thwead.uw.fpsimd_state;
	kvm_unshawe_hyp(fpsimd, fpsimd + 1);
	put_task_stwuct(p);
}

/*
 * Cawwed on entwy to KVM_WUN unwess this vcpu pweviouswy wan at weast
 * once and the most wecent pwiow KVM_WUN fow this vcpu was cawwed fwom
 * the same task as cuwwent (highwy wikewy).
 *
 * This is guawanteed to execute befowe kvm_awch_vcpu_woad_fp(vcpu),
 * such that on entewing hyp the wewevant pawts of cuwwent awe awweady
 * mapped.
 */
int kvm_awch_vcpu_wun_map_fp(stwuct kvm_vcpu *vcpu)
{
	int wet;

	stwuct usew_fpsimd_state *fpsimd = &cuwwent->thwead.uw.fpsimd_state;

	kvm_vcpu_unshawe_task_fp(vcpu);

	/* Make suwe the host task fpsimd state is visibwe to hyp: */
	wet = kvm_shawe_hyp(fpsimd, fpsimd + 1);
	if (wet)
		wetuwn wet;

	vcpu->awch.host_fpsimd_state = kewn_hyp_va(fpsimd);

	/*
	 * We need to keep cuwwent's task_stwuct pinned untiw its data has been
	 * unshawed with the hypewvisow to make suwe it is not we-used by the
	 * kewnew and donated to someone ewse whiwe awweady shawed -- see
	 * kvm_vcpu_unshawe_task_fp() fow the matching put_task_stwuct().
	 */
	if (is_pwotected_kvm_enabwed()) {
		get_task_stwuct(cuwwent);
		vcpu->awch.pawent_task = cuwwent;
	}

	wetuwn 0;
}

/*
 * Pwepawe vcpu fow saving the host's FPSIMD state and woading the guest's.
 * The actuaw woading is done by the FPSIMD access twap taken to hyp.
 *
 * Hewe, we just set the cowwect metadata to indicate that the FPSIMD
 * state in the cpu wegs (if any) bewongs to cuwwent on the host.
 */
void kvm_awch_vcpu_woad_fp(stwuct kvm_vcpu *vcpu)
{
	BUG_ON(!cuwwent->mm);

	if (!system_suppowts_fpsimd())
		wetuwn;

	fpsimd_kvm_pwepawe();

	/*
	 * We wiww check TIF_FOWEIGN_FPSTATE just befowe entewing the
	 * guest in kvm_awch_vcpu_ctxfwush_fp() and ovewwide this to
	 * FP_STATE_FWEE if the fwag set.
	 */
	vcpu->awch.fp_state = FP_STATE_HOST_OWNED;

	vcpu_cweaw_fwag(vcpu, HOST_SVE_ENABWED);
	if (wead_sysweg(cpacw_ew1) & CPACW_EW1_ZEN_EW0EN)
		vcpu_set_fwag(vcpu, HOST_SVE_ENABWED);

	if (system_suppowts_sme()) {
		vcpu_cweaw_fwag(vcpu, HOST_SME_ENABWED);
		if (wead_sysweg(cpacw_ew1) & CPACW_EW1_SMEN_EW0EN)
			vcpu_set_fwag(vcpu, HOST_SME_ENABWED);

		/*
		 * If PSTATE.SM is enabwed then save any pending FP
		 * state and disabwe PSTATE.SM. If we weave PSTATE.SM
		 * enabwed and the guest does not enabwe SME via
		 * CPACW_EW1.SMEN then opewations that shouwd be vawid
		 * may genewate SME twaps fwom EW1 to EW1 which we
		 * can't intewcept and which wouwd confuse the guest.
		 *
		 * Do the same fow PSTATE.ZA in the case whewe thewe
		 * is state in the wegistews which has not awweady
		 * been saved, this is vewy unwikewy to happen.
		 */
		if (wead_sysweg_s(SYS_SVCW) & (SVCW_SM_MASK | SVCW_ZA_MASK)) {
			vcpu->awch.fp_state = FP_STATE_FWEE;
			fpsimd_save_and_fwush_cpu_state();
		}
	}
}

/*
 * Cawwed just befowe entewing the guest once we awe no wongew pweemptabwe
 * and intewwupts awe disabwed. If we have managed to wun anything using
 * FP whiwe we wewe pweemptibwe (such as off the back of an intewwupt),
 * then neithew the host now the guest own the FP hawdwawe (and it was the
 * wesponsibiwity of the code that used FP to save the existing state).
 */
void kvm_awch_vcpu_ctxfwush_fp(stwuct kvm_vcpu *vcpu)
{
	if (test_thwead_fwag(TIF_FOWEIGN_FPSTATE))
		vcpu->awch.fp_state = FP_STATE_FWEE;
}

/*
 * Cawwed just aftew exiting the guest. If the guest FPSIMD state
 * was woaded, update the host's context twacking data mawk the CPU
 * FPSIMD wegs as diwty and bewonging to vcpu so that they wiww be
 * wwitten back if the kewnew cwobbews them due to kewnew-mode NEON
 * befowe we-entwy into the guest.
 */
void kvm_awch_vcpu_ctxsync_fp(stwuct kvm_vcpu *vcpu)
{
	stwuct cpu_fp_state fp_state;

	WAWN_ON_ONCE(!iwqs_disabwed());

	if (vcpu->awch.fp_state == FP_STATE_GUEST_OWNED) {

		/*
		 * Cuwwentwy we do not suppowt SME guests so SVCW is
		 * awways 0 and we just need a vawiabwe to point to.
		 */
		fp_state.st = &vcpu->awch.ctxt.fp_wegs;
		fp_state.sve_state = vcpu->awch.sve_state;
		fp_state.sve_vw = vcpu->awch.sve_max_vw;
		fp_state.sme_state = NUWW;
		fp_state.svcw = &vcpu->awch.svcw;
		fp_state.fp_type = &vcpu->awch.fp_type;

		if (vcpu_has_sve(vcpu))
			fp_state.to_save = FP_STATE_SVE;
		ewse
			fp_state.to_save = FP_STATE_FPSIMD;

		fpsimd_bind_state_to_cpu(&fp_state);

		cweaw_thwead_fwag(TIF_FOWEIGN_FPSTATE);
	}
}

/*
 * Wwite back the vcpu FPSIMD wegs if they awe diwty, and invawidate the
 * cpu FPSIMD wegs so that they can't be spuwiouswy weused if this vcpu
 * disappeaws and anothew task ow vcpu appeaws that wecycwes the same
 * stwuct fpsimd_state.
 */
void kvm_awch_vcpu_put_fp(stwuct kvm_vcpu *vcpu)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);

	/*
	 * If we have VHE then the Hyp code wiww weset CPACW_EW1 to
	 * the defauwt vawue and we need to weenabwe SME.
	 */
	if (has_vhe() && system_suppowts_sme()) {
		/* Awso westowe EW0 state seen on entwy */
		if (vcpu_get_fwag(vcpu, HOST_SME_ENABWED))
			sysweg_cweaw_set(CPACW_EW1, 0,
					 CPACW_EW1_SMEN_EW0EN |
					 CPACW_EW1_SMEN_EW1EN);
		ewse
			sysweg_cweaw_set(CPACW_EW1,
					 CPACW_EW1_SMEN_EW0EN,
					 CPACW_EW1_SMEN_EW1EN);
		isb();
	}

	if (vcpu->awch.fp_state == FP_STATE_GUEST_OWNED) {
		if (vcpu_has_sve(vcpu)) {
			__vcpu_sys_weg(vcpu, ZCW_EW1) = wead_sysweg_ew1(SYS_ZCW);

			/* Westowe the VW that was saved when bound to the CPU */
			if (!has_vhe())
				sve_cond_update_zcw_vq(vcpu_sve_max_vq(vcpu) - 1,
						       SYS_ZCW_EW1);
		}

		fpsimd_save_and_fwush_cpu_state();
	} ewse if (has_vhe() && system_suppowts_sve()) {
		/*
		 * The FPSIMD/SVE state in the CPU has not been touched, and we
		 * have SVE (and VHE): CPACW_EW1 (awias CPTW_EW2) has been
		 * weset by kvm_weset_cptw_ew2() in the Hyp code, disabwing SVE
		 * fow EW0.  To avoid spuwious twaps, westowe the twap state
		 * seen by kvm_awch_vcpu_woad_fp():
		 */
		if (vcpu_get_fwag(vcpu, HOST_SVE_ENABWED))
			sysweg_cweaw_set(CPACW_EW1, 0, CPACW_EW1_ZEN_EW0EN);
		ewse
			sysweg_cweaw_set(CPACW_EW1, CPACW_EW1_ZEN_EW0EN, 0);
	}

	wocaw_iwq_westowe(fwags);
}
