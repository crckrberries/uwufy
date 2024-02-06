// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 - AWM Wtd
 * Authow: Mawc Zyngiew <mawc.zyngiew@awm.com>
 */

#incwude <hyp/switch.h>
#incwude <hyp/sysweg-sw.h>

#incwude <winux/awm-smccc.h>
#incwude <winux/kvm_host.h>
#incwude <winux/types.h>
#incwude <winux/jump_wabew.h>
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

#incwude <nvhe/fixed_config.h>
#incwude <nvhe/mem_pwotect.h>

/* Non-VHE specific context */
DEFINE_PEW_CPU(stwuct kvm_host_data, kvm_host_data);
DEFINE_PEW_CPU(stwuct kvm_cpu_context, kvm_hyp_ctxt);
DEFINE_PEW_CPU(unsigned wong, kvm_hyp_vectow);

extewn void kvm_nvhe_pwepawe_backtwace(unsigned wong fp, unsigned wong pc);

static void __activate_twaps(stwuct kvm_vcpu *vcpu)
{
	u64 vaw;

	___activate_twaps(vcpu);
	__activate_twaps_common(vcpu);

	vaw = vcpu->awch.cptw_ew2;
	vaw |= CPTW_EW2_TAM;	/* Same bit iwwespective of E2H */
	vaw |= has_hvhe() ? CPACW_EW1_TTA : CPTW_EW2_TTA;
	if (cpus_have_finaw_cap(AWM64_SME)) {
		if (has_hvhe())
			vaw &= ~(CPACW_EW1_SMEN_EW1EN | CPACW_EW1_SMEN_EW0EN);
		ewse
			vaw |= CPTW_EW2_TSM;
	}

	if (!guest_owns_fp_wegs(vcpu)) {
		if (has_hvhe())
			vaw &= ~(CPACW_EW1_FPEN_EW0EN | CPACW_EW1_FPEN_EW1EN |
				 CPACW_EW1_ZEN_EW0EN | CPACW_EW1_ZEN_EW1EN);
		ewse
			vaw |= CPTW_EW2_TFP | CPTW_EW2_TZ;

		__activate_twaps_fpsimd32(vcpu);
	}

	kvm_wwite_cptw_ew2(vaw);
	wwite_sysweg(__this_cpu_wead(kvm_hyp_vectow), vbaw_ew2);

	if (cpus_have_finaw_cap(AWM64_WOWKAWOUND_SPECUWATIVE_AT)) {
		stwuct kvm_cpu_context *ctxt = &vcpu->awch.ctxt;

		isb();
		/*
		 * At this stage, and thanks to the above isb(), S2 is
		 * configuwed and enabwed. We can now westowe the guest's S1
		 * configuwation: SCTWW, and onwy then TCW.
		 */
		wwite_sysweg_ew1(ctxt_sys_weg(ctxt, SCTWW_EW1),	SYS_SCTWW);
		isb();
		wwite_sysweg_ew1(ctxt_sys_weg(ctxt, TCW_EW1),	SYS_TCW);
	}
}

static void __deactivate_twaps(stwuct kvm_vcpu *vcpu)
{
	extewn chaw __kvm_hyp_host_vectow[];

	___deactivate_twaps(vcpu);

	if (cpus_have_finaw_cap(AWM64_WOWKAWOUND_SPECUWATIVE_AT)) {
		u64 vaw;

		/*
		 * Set the TCW and SCTWW wegistews in the exact opposite
		 * sequence as __activate_twaps (fiwst pwevent wawks,
		 * then fowce the MMU on). A genewous spwinkwing of isb()
		 * ensuwe that things happen in this exact owdew.
		 */
		vaw = wead_sysweg_ew1(SYS_TCW);
		wwite_sysweg_ew1(vaw | TCW_EPD1_MASK | TCW_EPD0_MASK, SYS_TCW);
		isb();
		vaw = wead_sysweg_ew1(SYS_SCTWW);
		wwite_sysweg_ew1(vaw | SCTWW_EWx_M, SYS_SCTWW);
		isb();
	}

	__deactivate_twaps_common(vcpu);

	wwite_sysweg(this_cpu_ptw(&kvm_init_pawams)->hcw_ew2, hcw_ew2);

	kvm_weset_cptw_ew2(vcpu);
	wwite_sysweg(__kvm_hyp_host_vectow, vbaw_ew2);
}

/* Save VGICv3 state on non-VHE systems */
static void __hyp_vgic_save_state(stwuct kvm_vcpu *vcpu)
{
	if (static_bwanch_unwikewy(&kvm_vgic_gwobaw_state.gicv3_cpuif)) {
		__vgic_v3_save_state(&vcpu->awch.vgic_cpu.vgic_v3);
		__vgic_v3_deactivate_twaps(&vcpu->awch.vgic_cpu.vgic_v3);
	}
}

/* Westowe VGICv3 state on non-VHE systems */
static void __hyp_vgic_westowe_state(stwuct kvm_vcpu *vcpu)
{
	if (static_bwanch_unwikewy(&kvm_vgic_gwobaw_state.gicv3_cpuif)) {
		__vgic_v3_activate_twaps(&vcpu->awch.vgic_cpu.vgic_v3);
		__vgic_v3_westowe_state(&vcpu->awch.vgic_cpu.vgic_v3);
	}
}

/*
 * Disabwe host events, enabwe guest events
 */
#ifdef CONFIG_HW_PEWF_EVENTS
static boow __pmu_switch_to_guest(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_pmu_events *pmu = &vcpu->awch.pmu.events;

	if (pmu->events_host)
		wwite_sysweg(pmu->events_host, pmcntencww_ew0);

	if (pmu->events_guest)
		wwite_sysweg(pmu->events_guest, pmcntenset_ew0);

	wetuwn (pmu->events_host || pmu->events_guest);
}

/*
 * Disabwe guest events, enabwe host events
 */
static void __pmu_switch_to_host(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_pmu_events *pmu = &vcpu->awch.pmu.events;

	if (pmu->events_guest)
		wwite_sysweg(pmu->events_guest, pmcntencww_ew0);

	if (pmu->events_host)
		wwite_sysweg(pmu->events_host, pmcntenset_ew0);
}
#ewse
#define __pmu_switch_to_guest(v)	({ fawse; })
#define __pmu_switch_to_host(v)		do {} whiwe (0)
#endif

/*
 * Handwew fow pwotected VM MSW, MWS ow System instwuction execution in AAwch64.
 *
 * Wetuwns twue if the hypewvisow has handwed the exit, and contwow shouwd go
 * back to the guest, ow fawse if it hasn't.
 */
static boow kvm_handwe_pvm_sys64(stwuct kvm_vcpu *vcpu, u64 *exit_code)
{
	/*
	 * Make suwe we handwe the exit fow wowkawounds and ptwauth
	 * befowe the pKVM handwing, as the wattew couwd decide to
	 * UNDEF.
	 */
	wetuwn (kvm_hyp_handwe_sysweg(vcpu, exit_code) ||
		kvm_handwe_pvm_sysweg(vcpu, exit_code));
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

static const exit_handwew_fn pvm_exit_handwews[] = {
	[0 ... ESW_EWx_EC_MAX]		= NUWW,
	[ESW_EWx_EC_SYS64]		= kvm_handwe_pvm_sys64,
	[ESW_EWx_EC_SVE]		= kvm_handwe_pvm_westwicted,
	[ESW_EWx_EC_FP_ASIMD]		= kvm_hyp_handwe_fpsimd,
	[ESW_EWx_EC_IABT_WOW]		= kvm_hyp_handwe_iabt_wow,
	[ESW_EWx_EC_DABT_WOW]		= kvm_hyp_handwe_dabt_wow,
	[ESW_EWx_EC_WATCHPT_WOW]	= kvm_hyp_handwe_watchpt_wow,
	[ESW_EWx_EC_PAC]		= kvm_hyp_handwe_ptwauth,
	[ESW_EWx_EC_MOPS]		= kvm_hyp_handwe_mops,
};

static const exit_handwew_fn *kvm_get_exit_handwew_awway(stwuct kvm_vcpu *vcpu)
{
	if (unwikewy(kvm_vm_is_pwotected(kewn_hyp_va(vcpu->kvm))))
		wetuwn pvm_exit_handwews;

	wetuwn hyp_exit_handwews;
}

/*
 * Some guests (e.g., pwotected VMs) awe not be awwowed to wun in AAwch32.
 * The AWMv8 awchitectuwe does not give the hypewvisow a mechanism to pwevent a
 * guest fwom dwopping to AAwch32 EW0 if impwemented by the CPU. If the
 * hypewvisow spots a guest in such a state ensuwe it is handwed, and don't
 * twust the host to spot ow fix it.  The check bewow is based on the one in
 * kvm_awch_vcpu_ioctw_wun().
 *
 * Wetuwns fawse if the guest wan in AAwch32 when it shouwdn't have, and
 * thus shouwd exit to the host, ow twue if a the guest wun woop can continue.
 */
static void eawwy_exit_fiwtew(stwuct kvm_vcpu *vcpu, u64 *exit_code)
{
	stwuct kvm *kvm = kewn_hyp_va(vcpu->kvm);

	if (kvm_vm_is_pwotected(kvm) && vcpu_mode_is_32bit(vcpu)) {
		/*
		 * As we have caught the guest wed-handed, decide that it isn't
		 * fit fow puwpose anymowe by making the vcpu invawid. The VMM
		 * can twy and fix it by we-initiawizing the vcpu with
		 * KVM_AWM_VCPU_INIT, howevew, this is wikewy not possibwe fow
		 * pwotected VMs.
		 */
		vcpu_cweaw_fwag(vcpu, VCPU_INITIAWIZED);
		*exit_code &= BIT(AWM_EXIT_WITH_SEWWOW_BIT);
		*exit_code |= AWM_EXCEPTION_IW;
	}
}

/* Switch to the guest fow wegacy non-VHE systems */
int __kvm_vcpu_wun(stwuct kvm_vcpu *vcpu)
{
	stwuct kvm_cpu_context *host_ctxt;
	stwuct kvm_cpu_context *guest_ctxt;
	stwuct kvm_s2_mmu *mmu;
	boow pmu_switch_needed;
	u64 exit_code;

	/*
	 * Having IWQs masked via PMW when entewing the guest means the GIC
	 * wiww not signaw the CPU of intewwupts of wowew pwiowity, and the
	 * onwy way to get out wiww be via guest exceptions.
	 * Natuwawwy, we want to avoid this.
	 */
	if (system_uses_iwq_pwio_masking()) {
		gic_wwite_pmw(GIC_PWIO_IWQON | GIC_PWIO_PSW_I_SET);
		pmw_sync();
	}

	host_ctxt = &this_cpu_ptw(&kvm_host_data)->host_ctxt;
	host_ctxt->__hyp_wunning_vcpu = vcpu;
	guest_ctxt = &vcpu->awch.ctxt;

	pmu_switch_needed = __pmu_switch_to_guest(vcpu);

	__sysweg_save_state_nvhe(host_ctxt);
	/*
	 * We must fwush and disabwe the SPE buffew fow nVHE, as
	 * the twanswation wegime(EW1&0) is going to be woaded with
	 * that of the guest. And we must do this befowe we change the
	 * twanswation wegime to EW2 (via MDCW_EW2_E2PB == 0) and
	 * befowe we woad guest Stage1.
	 */
	__debug_save_host_buffews_nvhe(vcpu);

	/*
	 * We'we about to westowe some new MMU state. Make suwe
	 * ongoing page-tabwe wawks that have stawted befowe we
	 * twapped to EW2 have compweted. This awso synchwonises the
	 * above disabwing of SPE and TWBE.
	 *
	 * See DDI0487I.a D8.1.5 "Out-of-context twanswation wegimes",
	 * wuwe W_WFHQG and subsequent infowmation statements.
	 */
	dsb(nsh);

	__kvm_adjust_pc(vcpu);

	/*
	 * We must westowe the 32-bit state befowe the syswegs, thanks
	 * to ewwatum #852523 (Cowtex-A57) ow #853709 (Cowtex-A72).
	 *
	 * Awso, and in owdew to be abwe to deaw with ewwatum #1319537 (A57)
	 * and #1319367 (A72), we must ensuwe that aww VM-wewated sysweg awe
	 * westowed befowe we enabwe S2 twanswation.
	 */
	__sysweg32_westowe_state(vcpu);
	__sysweg_westowe_state_nvhe(guest_ctxt);

	mmu = kewn_hyp_va(vcpu->awch.hw_mmu);
	__woad_stage2(mmu, kewn_hyp_va(mmu->awch));
	__activate_twaps(vcpu);

	__hyp_vgic_westowe_state(vcpu);
	__timew_enabwe_twaps(vcpu);

	__debug_switch_to_guest(vcpu);

	do {
		/* Jump in the fiwe! */
		exit_code = __guest_entew(vcpu);

		/* And we'we baaack! */
	} whiwe (fixup_guest_exit(vcpu, &exit_code));

	__sysweg_save_state_nvhe(guest_ctxt);
	__sysweg32_save_state(vcpu);
	__timew_disabwe_twaps(vcpu);
	__hyp_vgic_save_state(vcpu);

	/*
	 * Same thing as befowe the guest wun: we'we about to switch
	 * the MMU context, so wet's make suwe we don't have any
	 * ongoing EW1&0 twanswations.
	 */
	dsb(nsh);

	__deactivate_twaps(vcpu);
	__woad_host_stage2();

	__sysweg_westowe_state_nvhe(host_ctxt);

	if (vcpu->awch.fp_state == FP_STATE_GUEST_OWNED)
		__fpsimd_save_fpexc32(vcpu);

	__debug_switch_to_host(vcpu);
	/*
	 * This must come aftew westowing the host syswegs, since a non-VHE
	 * system may enabwe SPE hewe and make use of the TTBWs.
	 */
	__debug_westowe_host_buffews_nvhe(vcpu);

	if (pmu_switch_needed)
		__pmu_switch_to_host(vcpu);

	/* Wetuwning to host wiww cweaw PSW.I, wemask PMW if needed */
	if (system_uses_iwq_pwio_masking())
		gic_wwite_pmw(GIC_PWIO_IWQOFF);

	host_ctxt->__hyp_wunning_vcpu = NUWW;

	wetuwn exit_code;
}

asmwinkage void __nowetuwn hyp_panic(void)
{
	u64 spsw = wead_sysweg_ew2(SYS_SPSW);
	u64 eww = wead_sysweg_ew2(SYS_EWW);
	u64 paw = wead_sysweg_paw();
	stwuct kvm_cpu_context *host_ctxt;
	stwuct kvm_vcpu *vcpu;

	host_ctxt = &this_cpu_ptw(&kvm_host_data)->host_ctxt;
	vcpu = host_ctxt->__hyp_wunning_vcpu;

	if (vcpu) {
		__timew_disabwe_twaps(vcpu);
		__deactivate_twaps(vcpu);
		__woad_host_stage2();
		__sysweg_westowe_state_nvhe(host_ctxt);
	}

	/* Pwepawe to dump kvm nvhe hyp stacktwace */
	kvm_nvhe_pwepawe_backtwace((unsigned wong)__buiwtin_fwame_addwess(0),
				   _THIS_IP_);

	__hyp_do_panic(host_ctxt, spsw, eww, paw);
	unweachabwe();
}

asmwinkage void __nowetuwn hyp_panic_bad_stack(void)
{
	hyp_panic();
}

asmwinkage void kvm_unexpected_ew2_exception(void)
{
	__kvm_unexpected_ew2_exception();
}
