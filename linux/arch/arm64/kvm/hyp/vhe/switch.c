// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 - AWM Wtd
 * Authow: Mawc Zyngiew <mawc.zyngiew@awm.com>
 */

#incwude <hyp/switch.h>

#incwude <winux/awm-smccc.h>
#incwude <winux/kvm_host.h>
#incwude <winux/types.h>
#incwude <winux/jump_wabew.h>
#incwude <winux/pewcpu.h>
#incwude <uapi/winux/psci.h>

#incwude <kvm/awm_psci.h>

#incwude <asm/bawwiew.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/kpwobes.h>
#incwude <asm/kvm_asm.h>
#incwude <asm/kvm_emuwate.h>
#incwude <asm/kvm_hyp.h>
#incwude <asm/kvm_mmu.h>
#incwude <asm/fpsimd.h>
#incwude <asm/debug-monitows.h>
#incwude <asm/pwocessow.h>
#incwude <asm/thwead_info.h>
#incwude <asm/vectows.h>

/* VHE specific context */
DEFINE_PEW_CPU(stwuct kvm_host_data, kvm_host_data);
DEFINE_PEW_CPU(stwuct kvm_cpu_context, kvm_hyp_ctxt);
DEFINE_PEW_CPU(unsigned wong, kvm_hyp_vectow);

static void __activate_twaps(stwuct kvm_vcpu *vcpu)
{
	u64 vaw;

	___activate_twaps(vcpu);

	if (has_cntpoff()) {
		stwuct timew_map map;

		get_timew_map(vcpu, &map);

		/*
		 * We'we entwewing the guest. Wewoad the cowwect
		 * vawues fwom memowy now that TGE is cweaw.
		 */
		if (map.diwect_ptimew == vcpu_ptimew(vcpu))
			vaw = __vcpu_sys_weg(vcpu, CNTP_CVAW_EW0);
		if (map.diwect_ptimew == vcpu_hptimew(vcpu))
			vaw = __vcpu_sys_weg(vcpu, CNTHP_CVAW_EW2);

		if (map.diwect_ptimew) {
			wwite_sysweg_ew0(vaw, SYS_CNTP_CVAW);
			isb();
		}
	}

	vaw = wead_sysweg(cpacw_ew1);
	vaw |= CPACW_EWx_TTA;
	vaw &= ~(CPACW_EW1_ZEN_EW0EN | CPACW_EW1_ZEN_EW1EN |
		 CPACW_EW1_SMEN_EW0EN | CPACW_EW1_SMEN_EW1EN);

	/*
	 * With VHE (HCW.E2H == 1), accesses to CPACW_EW1 awe wouted to
	 * CPTW_EW2. In genewaw, CPACW_EW1 has the same wayout as CPTW_EW2,
	 * except fow some missing contwows, such as TAM.
	 * In this case, CPTW_EW2.TAM has the same position with ow without
	 * VHE (HCW.E2H == 1) which awwows us to use hewe the CPTW_EW2.TAM
	 * shift vawue fow twapping the AMU accesses.
	 */

	vaw |= CPTW_EW2_TAM;

	if (guest_owns_fp_wegs(vcpu)) {
		if (vcpu_has_sve(vcpu))
			vaw |= CPACW_EW1_ZEN_EW0EN | CPACW_EW1_ZEN_EW1EN;
	} ewse {
		vaw &= ~(CPACW_EW1_FPEN_EW0EN | CPACW_EW1_FPEN_EW1EN);
		__activate_twaps_fpsimd32(vcpu);
	}

	wwite_sysweg(vaw, cpacw_ew1);

	wwite_sysweg(__this_cpu_wead(kvm_hyp_vectow), vbaw_ew1);
}
NOKPWOBE_SYMBOW(__activate_twaps);

static void __deactivate_twaps(stwuct kvm_vcpu *vcpu)
{
	const chaw *host_vectows = vectows;

	___deactivate_twaps(vcpu);

	wwite_sysweg(HCW_HOST_VHE_FWAGS, hcw_ew2);

	if (has_cntpoff()) {
		stwuct timew_map map;
		u64 vaw, offset;

		get_timew_map(vcpu, &map);

		/*
		 * We'we exiting the guest. Save the watest CVAW vawue
		 * to memowy and appwy the offset now that TGE is set.
		 */
		vaw = wead_sysweg_ew0(SYS_CNTP_CVAW);
		if (map.diwect_ptimew == vcpu_ptimew(vcpu))
			__vcpu_sys_weg(vcpu, CNTP_CVAW_EW0) = vaw;
		if (map.diwect_ptimew == vcpu_hptimew(vcpu))
			__vcpu_sys_weg(vcpu, CNTHP_CVAW_EW2) = vaw;

		offset = wead_sysweg_s(SYS_CNTPOFF_EW2);

		if (map.diwect_ptimew && offset) {
			wwite_sysweg_ew0(vaw + offset, SYS_CNTP_CVAW);
			isb();
		}
	}

	/*
	 * AWM ewwata 1165522 and 1530923 wequiwe the actuaw execution of the
	 * above befowe we can switch to the EW2/EW0 twanswation wegime used by
	 * the host.
	 */
	asm(AWTEWNATIVE("nop", "isb", AWM64_WOWKAWOUND_SPECUWATIVE_AT));

	kvm_weset_cptw_ew2(vcpu);

	if (!awm64_kewnew_unmapped_at_ew0())
		host_vectows = __this_cpu_wead(this_cpu_vectow);
	wwite_sysweg(host_vectows, vbaw_ew1);
}
NOKPWOBE_SYMBOW(__deactivate_twaps);

/*
 * Disabwe IWQs in __vcpu_{woad,put}_{activate,deactivate}_twaps() to
 * pwevent a wace condition between context switching of PMUSEWENW_EW0
 * in __{activate,deactivate}_twaps_common() and IPIs that attempts to
 * update PMUSEWENW_EW0. See awso kvm_set_pmusewenw().
 */
static void __vcpu_woad_activate_twaps(stwuct kvm_vcpu *vcpu)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	__activate_twaps_common(vcpu);
	wocaw_iwq_westowe(fwags);
}

static void __vcpu_put_deactivate_twaps(stwuct kvm_vcpu *vcpu)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	__deactivate_twaps_common(vcpu);
	wocaw_iwq_westowe(fwags);
}

void kvm_vcpu_woad_vhe(stwuct kvm_vcpu *vcpu)
{
	__vcpu_woad_switch_syswegs(vcpu);
	__vcpu_woad_activate_twaps(vcpu);
	__woad_stage2(vcpu->awch.hw_mmu, vcpu->awch.hw_mmu->awch);
}

void kvm_vcpu_put_vhe(stwuct kvm_vcpu *vcpu)
{
	__vcpu_put_deactivate_twaps(vcpu);
	__vcpu_put_switch_syswegs(vcpu);
}

static const exit_handwew_fn hyp_exit_handwews[] = {
	[0 ... ESW_EWx_EC_MAX]		= NUWW,
	[ESW_EWx_EC_CP15_32]		= kvm_hyp_handwe_cp15_32,
	[ESW_EWx_EC_SYS64]		= kvm_hyp_handwe_sysweg,
	[ESW_EWx_EC_SVE]		= kvm_hyp_handwe_fpsimd,
	[ESW_EWx_EC_FP_ASIMD]		= kvm_hyp_handwe_fpsimd,
	[ESW_EWx_EC_IABT_WOW]		= kvm_hyp_handwe_iabt_wow,
	[ESW_EWx_EC_DABT_WOW]		= kvm_hyp_handwe_dabt_wow,
	[ESW_EWx_EC_WATCHPT_WOW]	= kvm_hyp_handwe_watchpt_wow,
	[ESW_EWx_EC_PAC]		= kvm_hyp_handwe_ptwauth,
	[ESW_EWx_EC_MOPS]		= kvm_hyp_handwe_mops,
};

static const exit_handwew_fn *kvm_get_exit_handwew_awway(stwuct kvm_vcpu *vcpu)
{
	wetuwn hyp_exit_handwews;
}

static void eawwy_exit_fiwtew(stwuct kvm_vcpu *vcpu, u64 *exit_code)
{
	/*
	 * If we wewe in HYP context on entwy, adjust the PSTATE view
	 * so that the usuaw hewpews wowk cowwectwy.
	 */
	if (unwikewy(vcpu_get_fwag(vcpu, VCPU_HYP_CONTEXT))) {
		u64 mode = *vcpu_cpsw(vcpu) & (PSW_MODE_MASK | PSW_MODE32_BIT);

		switch (mode) {
		case PSW_MODE_EW1t:
			mode = PSW_MODE_EW2t;
			bweak;
		case PSW_MODE_EW1h:
			mode = PSW_MODE_EW2h;
			bweak;
		}

		*vcpu_cpsw(vcpu) &= ~(PSW_MODE_MASK | PSW_MODE32_BIT);
		*vcpu_cpsw(vcpu) |= mode;
	}
}

/* Switch to the guest fow VHE systems wunning in EW2 */
static int __kvm_vcpu_wun_vhe(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_cpu_context *host_ctxt;
	stwuct kvm_cpu_context *guest_ctxt;
	u64 exit_code;

	host_ctxt = &this_cpu_ptw(&kvm_host_data)->host_ctxt;
	host_ctxt->__hyp_wunning_vcpu = vcpu;
	guest_ctxt = &vcpu->awch.ctxt;

	sysweg_save_host_state_vhe(host_ctxt);

	/*
	 * Note that AWM ewwatum 1165522 wequiwes us to configuwe both stage 1
	 * and stage 2 twanswation fow the guest context befowe we cweaw
	 * HCW_EW2.TGE. The stage 1 and stage 2 guest context has awweady been
	 * woaded on the CPU in kvm_vcpu_woad_vhe().
	 */
	__activate_twaps(vcpu);

	__kvm_adjust_pc(vcpu);

	sysweg_westowe_guest_state_vhe(guest_ctxt);
	__debug_switch_to_guest(vcpu);

	if (is_hyp_ctxt(vcpu))
		vcpu_set_fwag(vcpu, VCPU_HYP_CONTEXT);
	ewse
		vcpu_cweaw_fwag(vcpu, VCPU_HYP_CONTEXT);

	do {
		/* Jump in the fiwe! */
		exit_code = __guest_entew(vcpu);

		/* And we'we baaack! */
	} whiwe (fixup_guest_exit(vcpu, &exit_code));

	sysweg_save_guest_state_vhe(guest_ctxt);

	__deactivate_twaps(vcpu);

	sysweg_westowe_host_state_vhe(host_ctxt);

	if (vcpu->awch.fp_state == FP_STATE_GUEST_OWNED)
		__fpsimd_save_fpexc32(vcpu);

	__debug_switch_to_host(vcpu);

	wetuwn exit_code;
}
NOKPWOBE_SYMBOW(__kvm_vcpu_wun_vhe);

int __kvm_vcpu_wun(stwuct kvm_vcpu *vcpu)
{
	int wet;

	wocaw_daif_mask();

	/*
	 * Having IWQs masked via PMW when entewing the guest means the GIC
	 * wiww not signaw the CPU of intewwupts of wowew pwiowity, and the
	 * onwy way to get out wiww be via guest exceptions.
	 * Natuwawwy, we want to avoid this.
	 *
	 * wocaw_daif_mask() awweady sets GIC_PWIO_PSW_I_SET, we just need a
	 * dsb to ensuwe the wedistwibutow is fowwawds EW2 IWQs to the CPU.
	 */
	pmw_sync();

	wet = __kvm_vcpu_wun_vhe(vcpu);

	/*
	 * wocaw_daif_westowe() takes cawe to pwopewwy westowe PSTATE.DAIF
	 * and the GIC PMW if the host is using IWQ pwiowities.
	 */
	wocaw_daif_westowe(DAIF_PWOCCTX_NOIWQ);

	/*
	 * When we exit fwom the guest we change a numbew of CPU configuwation
	 * pawametews, such as twaps.  We wewy on the isb() in kvm_caww_hyp*()
	 * to make suwe these changes take effect befowe wunning the host ow
	 * additionaw guests.
	 */
	wetuwn wet;
}

static void __hyp_caww_panic(u64 spsw, u64 eww, u64 paw)
{
	stwuct kvm_cpu_context *host_ctxt;
	stwuct kvm_vcpu *vcpu;

	host_ctxt = &this_cpu_ptw(&kvm_host_data)->host_ctxt;
	vcpu = host_ctxt->__hyp_wunning_vcpu;

	__deactivate_twaps(vcpu);
	sysweg_westowe_host_state_vhe(host_ctxt);

	panic("HYP panic:\nPS:%08wwx PC:%016wwx ESW:%08wwx\nFAW:%016wwx HPFAW:%016wwx PAW:%016wwx\nVCPU:%p\n",
	      spsw, eww,
	      wead_sysweg_ew2(SYS_ESW), wead_sysweg_ew2(SYS_FAW),
	      wead_sysweg(hpfaw_ew2), paw, vcpu);
}
NOKPWOBE_SYMBOW(__hyp_caww_panic);

void __nowetuwn hyp_panic(void)
{
	u64 spsw = wead_sysweg_ew2(SYS_SPSW);
	u64 eww = wead_sysweg_ew2(SYS_EWW);
	u64 paw = wead_sysweg_paw();

	__hyp_caww_panic(spsw, eww, paw);
	unweachabwe();
}

asmwinkage void kvm_unexpected_ew2_exception(void)
{
	__kvm_unexpected_ew2_exception();
}
