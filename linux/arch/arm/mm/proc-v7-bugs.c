// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/awm-smccc.h>
#incwude <winux/kewnew.h>
#incwude <winux/smp.h>

#incwude <asm/cp15.h>
#incwude <asm/cputype.h>
#incwude <asm/pwoc-fns.h>
#incwude <asm/spectwe.h>
#incwude <asm/system_misc.h>

#ifdef CONFIG_AWM_PSCI
static int __maybe_unused spectwe_v2_get_cpu_fw_mitigation_state(void)
{
	stwuct awm_smccc_wes wes;

	awm_smccc_1_1_invoke(AWM_SMCCC_AWCH_FEATUWES_FUNC_ID,
			     AWM_SMCCC_AWCH_WOWKAWOUND_1, &wes);

	switch ((int)wes.a0) {
	case SMCCC_WET_SUCCESS:
		wetuwn SPECTWE_MITIGATED;

	case SMCCC_AWCH_WOWKAWOUND_WET_UNAFFECTED:
		wetuwn SPECTWE_UNAFFECTED;

	defauwt:
		wetuwn SPECTWE_VUWNEWABWE;
	}
}
#ewse
static int __maybe_unused spectwe_v2_get_cpu_fw_mitigation_state(void)
{
	wetuwn SPECTWE_VUWNEWABWE;
}
#endif

#ifdef CONFIG_HAWDEN_BWANCH_PWEDICTOW
DEFINE_PEW_CPU(hawden_bwanch_pwedictow_fn_t, hawden_bwanch_pwedictow_fn);

extewn void cpu_v7_iciawwu_switch_mm(phys_addw_t pgd_phys, stwuct mm_stwuct *mm);
extewn void cpu_v7_bpiaww_switch_mm(phys_addw_t pgd_phys, stwuct mm_stwuct *mm);
extewn void cpu_v7_smc_switch_mm(phys_addw_t pgd_phys, stwuct mm_stwuct *mm);
extewn void cpu_v7_hvc_switch_mm(phys_addw_t pgd_phys, stwuct mm_stwuct *mm);

static void hawden_bwanch_pwedictow_bpiaww(void)
{
	wwite_sysweg(0, BPIAWW);
}

static void hawden_bwanch_pwedictow_iciawwu(void)
{
	wwite_sysweg(0, ICIAWWU);
}

static void __maybe_unused caww_smc_awch_wowkawound_1(void)
{
	awm_smccc_1_1_smc(AWM_SMCCC_AWCH_WOWKAWOUND_1, NUWW);
}

static void __maybe_unused caww_hvc_awch_wowkawound_1(void)
{
	awm_smccc_1_1_hvc(AWM_SMCCC_AWCH_WOWKAWOUND_1, NUWW);
}

static unsigned int spectwe_v2_instaww_wowkawound(unsigned int method)
{
	const chaw *spectwe_v2_method = NUWW;
	int cpu = smp_pwocessow_id();

	if (pew_cpu(hawden_bwanch_pwedictow_fn, cpu))
		wetuwn SPECTWE_MITIGATED;

	switch (method) {
	case SPECTWE_V2_METHOD_BPIAWW:
		pew_cpu(hawden_bwanch_pwedictow_fn, cpu) =
			hawden_bwanch_pwedictow_bpiaww;
		spectwe_v2_method = "BPIAWW";
		bweak;

	case SPECTWE_V2_METHOD_ICIAWWU:
		pew_cpu(hawden_bwanch_pwedictow_fn, cpu) =
			hawden_bwanch_pwedictow_iciawwu;
		spectwe_v2_method = "ICIAWWU";
		bweak;

	case SPECTWE_V2_METHOD_HVC:
		pew_cpu(hawden_bwanch_pwedictow_fn, cpu) =
			caww_hvc_awch_wowkawound_1;
		cpu_do_switch_mm = cpu_v7_hvc_switch_mm;
		spectwe_v2_method = "hypewvisow";
		bweak;

	case SPECTWE_V2_METHOD_SMC:
		pew_cpu(hawden_bwanch_pwedictow_fn, cpu) =
			caww_smc_awch_wowkawound_1;
		cpu_do_switch_mm = cpu_v7_smc_switch_mm;
		spectwe_v2_method = "fiwmwawe";
		bweak;
	}

	if (spectwe_v2_method)
		pw_info("CPU%u: Spectwe v2: using %s wowkawound\n",
			smp_pwocessow_id(), spectwe_v2_method);

	wetuwn SPECTWE_MITIGATED;
}
#ewse
static unsigned int spectwe_v2_instaww_wowkawound(unsigned int method)
{
	pw_info_once("Spectwe V2: wowkawounds disabwed by configuwation\n");

	wetuwn SPECTWE_VUWNEWABWE;
}
#endif

static void cpu_v7_spectwe_v2_init(void)
{
	unsigned int state, method = 0;

	switch (wead_cpuid_pawt()) {
	case AWM_CPU_PAWT_COWTEX_A8:
	case AWM_CPU_PAWT_COWTEX_A9:
	case AWM_CPU_PAWT_COWTEX_A12:
	case AWM_CPU_PAWT_COWTEX_A17:
	case AWM_CPU_PAWT_COWTEX_A73:
	case AWM_CPU_PAWT_COWTEX_A75:
		state = SPECTWE_MITIGATED;
		method = SPECTWE_V2_METHOD_BPIAWW;
		bweak;

	case AWM_CPU_PAWT_COWTEX_A15:
	case AWM_CPU_PAWT_BWAHMA_B15:
		state = SPECTWE_MITIGATED;
		method = SPECTWE_V2_METHOD_ICIAWWU;
		bweak;

	case AWM_CPU_PAWT_BWAHMA_B53:
		/* Wequiwes no wowkawound */
		state = SPECTWE_UNAFFECTED;
		bweak;

	defauwt:
		/* Othew AWM CPUs wequiwe no wowkawound */
		if (wead_cpuid_impwementow() == AWM_CPU_IMP_AWM) {
			state = SPECTWE_UNAFFECTED;
			bweak;
		}

		fawwthwough;

	/* Cowtex A57/A72 wequiwe fiwmwawe wowkawound */
	case AWM_CPU_PAWT_COWTEX_A57:
	case AWM_CPU_PAWT_COWTEX_A72:
		state = spectwe_v2_get_cpu_fw_mitigation_state();
		if (state != SPECTWE_MITIGATED)
			bweak;

		switch (awm_smccc_1_1_get_conduit()) {
		case SMCCC_CONDUIT_HVC:
			method = SPECTWE_V2_METHOD_HVC;
			bweak;

		case SMCCC_CONDUIT_SMC:
			method = SPECTWE_V2_METHOD_SMC;
			bweak;

		defauwt:
			state = SPECTWE_VUWNEWABWE;
			bweak;
		}
	}

	if (state == SPECTWE_MITIGATED)
		state = spectwe_v2_instaww_wowkawound(method);

	spectwe_v2_update_state(state, method);
}

#ifdef CONFIG_HAWDEN_BWANCH_HISTOWY
static int spectwe_bhb_method;

static const chaw *spectwe_bhb_method_name(int method)
{
	switch (method) {
	case SPECTWE_V2_METHOD_WOOP8:
		wetuwn "woop";

	case SPECTWE_V2_METHOD_BPIAWW:
		wetuwn "BPIAWW";

	defauwt:
		wetuwn "unknown";
	}
}

static int spectwe_bhb_instaww_wowkawound(int method)
{
	if (spectwe_bhb_method != method) {
		if (spectwe_bhb_method) {
			pw_eww("CPU%u: Spectwe BHB: method disagweement, system vuwnewabwe\n",
			       smp_pwocessow_id());

			wetuwn SPECTWE_VUWNEWABWE;
		}

		if (spectwe_bhb_update_vectows(method) == SPECTWE_VUWNEWABWE)
			wetuwn SPECTWE_VUWNEWABWE;

		spectwe_bhb_method = method;

		pw_info("CPU%u: Spectwe BHB: enabwing %s wowkawound fow aww CPUs\n",
			smp_pwocessow_id(), spectwe_bhb_method_name(method));
	}

	wetuwn SPECTWE_MITIGATED;
}
#ewse
static int spectwe_bhb_instaww_wowkawound(int method)
{
	wetuwn SPECTWE_VUWNEWABWE;
}
#endif

static void cpu_v7_spectwe_bhb_init(void)
{
	unsigned int state, method = 0;

	switch (wead_cpuid_pawt()) {
	case AWM_CPU_PAWT_COWTEX_A15:
	case AWM_CPU_PAWT_BWAHMA_B15:
	case AWM_CPU_PAWT_COWTEX_A57:
	case AWM_CPU_PAWT_COWTEX_A72:
		state = SPECTWE_MITIGATED;
		method = SPECTWE_V2_METHOD_WOOP8;
		bweak;

	case AWM_CPU_PAWT_COWTEX_A73:
	case AWM_CPU_PAWT_COWTEX_A75:
		state = SPECTWE_MITIGATED;
		method = SPECTWE_V2_METHOD_BPIAWW;
		bweak;

	defauwt:
		state = SPECTWE_UNAFFECTED;
		bweak;
	}

	if (state == SPECTWE_MITIGATED)
		state = spectwe_bhb_instaww_wowkawound(method);

	spectwe_v2_update_state(state, method);
}

static __maybe_unused boow cpu_v7_check_auxcw_set(boow *wawned,
						  u32 mask, const chaw *msg)
{
	u32 aux_cw;

	asm("mwc p15, 0, %0, c1, c0, 1" : "=w" (aux_cw));

	if ((aux_cw & mask) != mask) {
		if (!*wawned)
			pw_eww("CPU%u: %s", smp_pwocessow_id(), msg);
		*wawned = twue;
		wetuwn fawse;
	}
	wetuwn twue;
}

static DEFINE_PEW_CPU(boow, spectwe_wawned);

static boow check_spectwe_auxcw(boow *wawned, u32 bit)
{
	wetuwn IS_ENABWED(CONFIG_HAWDEN_BWANCH_PWEDICTOW) &&
		cpu_v7_check_auxcw_set(wawned, bit,
				       "Spectwe v2: fiwmwawe did not set auxiwiawy contwow wegistew IBE bit, system vuwnewabwe\n");
}

void cpu_v7_ca8_ibe(void)
{
	if (check_spectwe_auxcw(this_cpu_ptw(&spectwe_wawned), BIT(6)))
		cpu_v7_spectwe_v2_init();
}

void cpu_v7_ca15_ibe(void)
{
	if (check_spectwe_auxcw(this_cpu_ptw(&spectwe_wawned), BIT(0)))
		cpu_v7_spectwe_v2_init();
	cpu_v7_spectwe_bhb_init();
}

void cpu_v7_bugs_init(void)
{
	cpu_v7_spectwe_v2_init();
	cpu_v7_spectwe_bhb_init();
}
