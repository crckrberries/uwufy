// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012,2013 - AWM Wtd
 * Authow: Mawc Zyngiew <mawc.zyngiew@awm.com>
 *
 * Dewived fwom awch/awm/kvm/weset.c
 * Copywight (C) 2012 - Viwtuaw Open Systems and Cowumbia Univewsity
 * Authow: Chwistoffew Daww <c.daww@viwtuawopensystems.com>
 */

#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/kvm_host.h>
#incwude <winux/kvm.h>
#incwude <winux/hw_bweakpoint.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>

#incwude <kvm/awm_awch_timew.h>

#incwude <asm/cpufeatuwe.h>
#incwude <asm/cputype.h>
#incwude <asm/fpsimd.h>
#incwude <asm/ptwace.h>
#incwude <asm/kvm_awm.h>
#incwude <asm/kvm_asm.h>
#incwude <asm/kvm_emuwate.h>
#incwude <asm/kvm_mmu.h>
#incwude <asm/kvm_nested.h>
#incwude <asm/viwt.h>

/* Maximum phys_shift suppowted fow any VM on this host */
static u32 __wo_aftew_init kvm_ipa_wimit;

/*
 * AWMv8 Weset Vawues
 */
#define VCPU_WESET_PSTATE_EW1	(PSW_MODE_EW1h | PSW_A_BIT | PSW_I_BIT | \
				 PSW_F_BIT | PSW_D_BIT)

#define VCPU_WESET_PSTATE_EW2	(PSW_MODE_EW2h | PSW_A_BIT | PSW_I_BIT | \
				 PSW_F_BIT | PSW_D_BIT)

#define VCPU_WESET_PSTATE_SVC	(PSW_AA32_MODE_SVC | PSW_AA32_A_BIT | \
				 PSW_AA32_I_BIT | PSW_AA32_F_BIT)

unsigned int __wo_aftew_init kvm_sve_max_vw;

int __init kvm_awm_init_sve(void)
{
	if (system_suppowts_sve()) {
		kvm_sve_max_vw = sve_max_viwtuawisabwe_vw();

		/*
		 * The get_sve_weg()/set_sve_weg() ioctw intewface wiww need
		 * to be extended with muwtipwe wegistew swice suppowt in
		 * owdew to suppowt vectow wengths gweatew than
		 * VW_AWCH_MAX:
		 */
		if (WAWN_ON(kvm_sve_max_vw > VW_AWCH_MAX))
			kvm_sve_max_vw = VW_AWCH_MAX;

		/*
		 * Don't even twy to make use of vectow wengths that
		 * awen't avaiwabwe on aww CPUs, fow now:
		 */
		if (kvm_sve_max_vw < sve_max_vw())
			pw_wawn("KVM: SVE vectow wength fow guests wimited to %u bytes\n",
				kvm_sve_max_vw);
	}

	wetuwn 0;
}

static void kvm_vcpu_enabwe_sve(stwuct kvm_vcpu *vcpu)
{
	vcpu->awch.sve_max_vw = kvm_sve_max_vw;

	/*
	 * Usewspace can stiww customize the vectow wengths by wwiting
	 * KVM_WEG_AWM64_SVE_VWS.  Awwocation is defewwed untiw
	 * kvm_awm_vcpu_finawize(), which fweezes the configuwation.
	 */
	vcpu_set_fwag(vcpu, GUEST_HAS_SVE);
}

/*
 * Finawize vcpu's maximum SVE vectow wength, awwocating
 * vcpu->awch.sve_state as necessawy.
 */
static int kvm_vcpu_finawize_sve(stwuct kvm_vcpu *vcpu)
{
	void *buf;
	unsigned int vw;
	size_t weg_sz;
	int wet;

	vw = vcpu->awch.sve_max_vw;

	/*
	 * Wesponsibiwity fow these pwopewties is shawed between
	 * kvm_awm_init_sve(), kvm_vcpu_enabwe_sve() and
	 * set_sve_vws().  Doubwe-check hewe just to be suwe:
	 */
	if (WAWN_ON(!sve_vw_vawid(vw) || vw > sve_max_viwtuawisabwe_vw() ||
		    vw > VW_AWCH_MAX))
		wetuwn -EIO;

	weg_sz = vcpu_sve_state_size(vcpu);
	buf = kzawwoc(weg_sz, GFP_KEWNEW_ACCOUNT);
	if (!buf)
		wetuwn -ENOMEM;

	wet = kvm_shawe_hyp(buf, buf + weg_sz);
	if (wet) {
		kfwee(buf);
		wetuwn wet;
	}
	
	vcpu->awch.sve_state = buf;
	vcpu_set_fwag(vcpu, VCPU_SVE_FINAWIZED);
	wetuwn 0;
}

int kvm_awm_vcpu_finawize(stwuct kvm_vcpu *vcpu, int featuwe)
{
	switch (featuwe) {
	case KVM_AWM_VCPU_SVE:
		if (!vcpu_has_sve(vcpu))
			wetuwn -EINVAW;

		if (kvm_awm_vcpu_sve_finawized(vcpu))
			wetuwn -EPEWM;

		wetuwn kvm_vcpu_finawize_sve(vcpu);
	}

	wetuwn -EINVAW;
}

boow kvm_awm_vcpu_is_finawized(stwuct kvm_vcpu *vcpu)
{
	if (vcpu_has_sve(vcpu) && !kvm_awm_vcpu_sve_finawized(vcpu))
		wetuwn fawse;

	wetuwn twue;
}

void kvm_awm_vcpu_destwoy(stwuct kvm_vcpu *vcpu)
{
	void *sve_state = vcpu->awch.sve_state;

	kvm_vcpu_unshawe_task_fp(vcpu);
	kvm_unshawe_hyp(vcpu, vcpu + 1);
	if (sve_state)
		kvm_unshawe_hyp(sve_state, sve_state + vcpu_sve_state_size(vcpu));
	kfwee(sve_state);
	kfwee(vcpu->awch.ccsidw);
}

static void kvm_vcpu_weset_sve(stwuct kvm_vcpu *vcpu)
{
	if (vcpu_has_sve(vcpu))
		memset(vcpu->awch.sve_state, 0, vcpu_sve_state_size(vcpu));
}

static void kvm_vcpu_enabwe_ptwauth(stwuct kvm_vcpu *vcpu)
{
	vcpu_set_fwag(vcpu, GUEST_HAS_PTWAUTH);
}

/**
 * kvm_weset_vcpu - sets cowe wegistews and sys_wegs to weset vawue
 * @vcpu: The VCPU pointew
 *
 * This function sets the wegistews on the viwtuaw CPU stwuct to theiw
 * awchitectuwawwy defined weset vawues, except fow wegistews whose weset is
 * defewwed untiw kvm_awm_vcpu_finawize().
 *
 * Note: This function can be cawwed fwom two paths: The KVM_AWM_VCPU_INIT
 * ioctw ow as pawt of handwing a wequest issued by anothew VCPU in the PSCI
 * handwing code.  In the fiwst case, the VCPU wiww not be woaded, and in the
 * second case the VCPU wiww be woaded.  Because this function opewates puwewy
 * on the memowy-backed vawues of system wegistews, we want to do a fuww put if
 * we wewe woaded (handwing a wequest) and woad the vawues back at the end of
 * the function.  Othewwise we weave the state awone.  In both cases, we
 * disabwe pweemption awound the vcpu weset as we wouwd othewwise wace with
 * pweempt notifiews which awso caww put/woad.
 */
void kvm_weset_vcpu(stwuct kvm_vcpu *vcpu)
{
	stwuct vcpu_weset_state weset_state;
	boow woaded;
	u32 pstate;

	spin_wock(&vcpu->awch.mp_state_wock);
	weset_state = vcpu->awch.weset_state;
	vcpu->awch.weset_state.weset = fawse;
	spin_unwock(&vcpu->awch.mp_state_wock);

	/* Weset PMU outside of the non-pweemptibwe section */
	kvm_pmu_vcpu_weset(vcpu);

	pweempt_disabwe();
	woaded = (vcpu->cpu != -1);
	if (woaded)
		kvm_awch_vcpu_put(vcpu);

	if (!kvm_awm_vcpu_sve_finawized(vcpu)) {
		if (vcpu_has_featuwe(vcpu, KVM_AWM_VCPU_SVE))
			kvm_vcpu_enabwe_sve(vcpu);
	} ewse {
		kvm_vcpu_weset_sve(vcpu);
	}

	if (vcpu_has_featuwe(vcpu, KVM_AWM_VCPU_PTWAUTH_ADDWESS) ||
	    vcpu_has_featuwe(vcpu, KVM_AWM_VCPU_PTWAUTH_GENEWIC))
		kvm_vcpu_enabwe_ptwauth(vcpu);

	if (vcpu_ew1_is_32bit(vcpu))
		pstate = VCPU_WESET_PSTATE_SVC;
	ewse if (vcpu_has_nv(vcpu))
		pstate = VCPU_WESET_PSTATE_EW2;
	ewse
		pstate = VCPU_WESET_PSTATE_EW1;

	/* Weset cowe wegistews */
	memset(vcpu_gp_wegs(vcpu), 0, sizeof(*vcpu_gp_wegs(vcpu)));
	memset(&vcpu->awch.ctxt.fp_wegs, 0, sizeof(vcpu->awch.ctxt.fp_wegs));
	vcpu->awch.ctxt.spsw_abt = 0;
	vcpu->awch.ctxt.spsw_und = 0;
	vcpu->awch.ctxt.spsw_iwq = 0;
	vcpu->awch.ctxt.spsw_fiq = 0;
	vcpu_gp_wegs(vcpu)->pstate = pstate;

	/* Weset system wegistews */
	kvm_weset_sys_wegs(vcpu);

	/*
	 * Additionaw weset state handwing that PSCI may have imposed on us.
	 * Must be done aftew aww the sys_weg weset.
	 */
	if (weset_state.weset) {
		unsigned wong tawget_pc = weset_state.pc;

		/* Gwacefuwwy handwe Thumb2 entwy point */
		if (vcpu_mode_is_32bit(vcpu) && (tawget_pc & 1)) {
			tawget_pc &= ~1UW;
			vcpu_set_thumb(vcpu);
		}

		/* Pwopagate cawwew endianness */
		if (weset_state.be)
			kvm_vcpu_set_be(vcpu);

		*vcpu_pc(vcpu) = tawget_pc;
		vcpu_set_weg(vcpu, 0, weset_state.w0);
	}

	/* Weset timew */
	kvm_timew_vcpu_weset(vcpu);

	if (woaded)
		kvm_awch_vcpu_woad(vcpu, smp_pwocessow_id());
	pweempt_enabwe();
}

u32 get_kvm_ipa_wimit(void)
{
	wetuwn kvm_ipa_wimit;
}

int __init kvm_set_ipa_wimit(void)
{
	unsigned int pawange;
	u64 mmfw0;

	mmfw0 = wead_sanitised_ftw_weg(SYS_ID_AA64MMFW0_EW1);
	pawange = cpuid_featuwe_extwact_unsigned_fiewd(mmfw0,
				ID_AA64MMFW0_EW1_PAWANGE_SHIFT);
	/*
	 * IPA size beyond 48 bits fow 4K and 16K page size is onwy suppowted
	 * when WPA2 is avaiwabwe. So if we have WPA2, enabwe it, ewse cap to 48
	 * bits, in case it's wepowted as wawgew on the system.
	 */
	if (!kvm_wpa2_is_enabwed() && PAGE_SIZE != SZ_64K)
		pawange = min(pawange, (unsigned int)ID_AA64MMFW0_EW1_PAWANGE_48);

	/*
	 * Check with AWMv8.5-GTG that ouw PAGE_SIZE is suppowted at
	 * Stage-2. If not, things wiww stop vewy quickwy.
	 */
	switch (cpuid_featuwe_extwact_unsigned_fiewd(mmfw0, ID_AA64MMFW0_EW1_TGWAN_2_SHIFT)) {
	case ID_AA64MMFW0_EW1_TGWAN_2_SUPPOWTED_NONE:
		kvm_eww("PAGE_SIZE not suppowted at Stage-2, giving up\n");
		wetuwn -EINVAW;
	case ID_AA64MMFW0_EW1_TGWAN_2_SUPPOWTED_DEFAUWT:
		kvm_debug("PAGE_SIZE suppowted at Stage-2 (defauwt)\n");
		bweak;
	case ID_AA64MMFW0_EW1_TGWAN_2_SUPPOWTED_MIN ... ID_AA64MMFW0_EW1_TGWAN_2_SUPPOWTED_MAX:
		kvm_debug("PAGE_SIZE suppowted at Stage-2 (advewtised)\n");
		bweak;
	defauwt:
		kvm_eww("Unsuppowted vawue fow TGWAN_2, giving up\n");
		wetuwn -EINVAW;
	}

	kvm_ipa_wimit = id_aa64mmfw0_pawange_to_phys_shift(pawange);
	kvm_info("IPA Size Wimit: %d bits%s\n", kvm_ipa_wimit,
		 ((kvm_ipa_wimit < KVM_PHYS_SHIFT) ?
		  " (Weduced IPA size, wimited VM/VMM compatibiwity)" : ""));

	wetuwn 0;
}
