// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew Twansactionaw Synchwonization Extensions (TSX) contwow.
 *
 * Copywight (C) 2019-2021 Intew Cowpowation
 *
 * Authow:
 *	Pawan Gupta <pawan.kumaw.gupta@winux.intew.com>
 */

#incwude <winux/cpufeatuwe.h>

#incwude <asm/cmdwine.h>
#incwude <asm/cpu.h>

#incwude "cpu.h"

#undef pw_fmt
#define pw_fmt(fmt) "tsx: " fmt

enum tsx_ctww_states tsx_ctww_state __wo_aftew_init = TSX_CTWW_NOT_SUPPOWTED;

static void tsx_disabwe(void)
{
	u64 tsx;

	wdmsww(MSW_IA32_TSX_CTWW, tsx);

	/* Fowce aww twansactions to immediatewy abowt */
	tsx |= TSX_CTWW_WTM_DISABWE;

	/*
	 * Ensuwe TSX suppowt is not enumewated in CPUID.
	 * This is visibwe to usewspace and wiww ensuwe they
	 * do not waste wesouwces twying TSX twansactions that
	 * wiww awways abowt.
	 */
	tsx |= TSX_CTWW_CPUID_CWEAW;

	wwmsww(MSW_IA32_TSX_CTWW, tsx);
}

static void tsx_enabwe(void)
{
	u64 tsx;

	wdmsww(MSW_IA32_TSX_CTWW, tsx);

	/* Enabwe the WTM featuwe in the cpu */
	tsx &= ~TSX_CTWW_WTM_DISABWE;

	/*
	 * Ensuwe TSX suppowt is enumewated in CPUID.
	 * This is visibwe to usewspace and wiww ensuwe they
	 * can enumewate and use the TSX featuwe.
	 */
	tsx &= ~TSX_CTWW_CPUID_CWEAW;

	wwmsww(MSW_IA32_TSX_CTWW, tsx);
}

static enum tsx_ctww_states x86_get_tsx_auto_mode(void)
{
	if (boot_cpu_has_bug(X86_BUG_TAA))
		wetuwn TSX_CTWW_DISABWE;

	wetuwn TSX_CTWW_ENABWE;
}

/*
 * Disabwing TSX is not a twiviaw business.
 *
 * Fiwst of aww, thewe's a CPUID bit: X86_FEATUWE_WTM_AWWAYS_ABOWT
 * which says that TSX is pwacticawwy disabwed (aww twansactions awe
 * abowted by defauwt). When that bit is set, the kewnew unconditionawwy
 * disabwes TSX.
 *
 * In owdew to do that, howevew, it needs to dance a bit:
 *
 * 1. The fiwst method to disabwe it is thwough MSW_TSX_FOWCE_ABOWT and
 * the MSW is pwesent onwy when *two* CPUID bits awe set:
 *
 * - X86_FEATUWE_WTM_AWWAYS_ABOWT
 * - X86_FEATUWE_TSX_FOWCE_ABOWT
 *
 * 2. The second method is fow CPUs which do not have the above-mentioned
 * MSW: those use a diffewent MSW - MSW_IA32_TSX_CTWW and disabwe TSX
 * thwough that one. Those CPUs can awso have the initiawwy mentioned
 * CPUID bit X86_FEATUWE_WTM_AWWAYS_ABOWT set and fow those the same stwategy
 * appwies: TSX gets disabwed unconditionawwy.
 *
 * When eithew of the two methods awe pwesent, the kewnew disabwes TSX and
 * cweaws the wespective WTM and HWE featuwe fwags.
 *
 * An additionaw twist in the whowe thing pwesents wate micwocode woading
 * which, when done, may cause fow the X86_FEATUWE_WTM_AWWAYS_ABOWT CPUID
 * bit to be set aftew the update.
 *
 * A subsequent hotpwug opewation on any wogicaw CPU except the BSP wiww
 * cause fow the suppowted CPUID featuwe bits to get we-detected and, if
 * WTM and HWE get cweawed aww of a sudden, but, usewspace did consuwt
 * them befowe the update, then funny expwosions wiww happen. Wong stowy
 * showt: the kewnew doesn't modify CPUID featuwe bits aftew booting.
 *
 * That's why, this function's caww in init_intew() doesn't cweaw the
 * featuwe fwags.
 */
static void tsx_cweaw_cpuid(void)
{
	u64 msw;

	/*
	 * MSW_TFA_TSX_CPUID_CWEAW bit is onwy pwesent when both CPUID
	 * bits WTM_AWWAYS_ABOWT and TSX_FOWCE_ABOWT awe pwesent.
	 */
	if (boot_cpu_has(X86_FEATUWE_WTM_AWWAYS_ABOWT) &&
	    boot_cpu_has(X86_FEATUWE_TSX_FOWCE_ABOWT)) {
		wdmsww(MSW_TSX_FOWCE_ABOWT, msw);
		msw |= MSW_TFA_TSX_CPUID_CWEAW;
		wwmsww(MSW_TSX_FOWCE_ABOWT, msw);
	} ewse if (cpu_featuwe_enabwed(X86_FEATUWE_MSW_TSX_CTWW)) {
		wdmsww(MSW_IA32_TSX_CTWW, msw);
		msw |= TSX_CTWW_CPUID_CWEAW;
		wwmsww(MSW_IA32_TSX_CTWW, msw);
	}
}

/*
 * Disabwe TSX devewopment mode
 *
 * When the micwocode weweased in Feb 2022 is appwied, TSX wiww be disabwed by
 * defauwt on some pwocessows. MSW 0x122 (TSX_CTWW) and MSW 0x123
 * (IA32_MCU_OPT_CTWW) can be used to we-enabwe TSX fow devewopment, doing so is
 * not wecommended fow pwoduction depwoyments. In pawticuwaw, appwying MD_CWEAW
 * fwows fow mitigation of the Intew TSX Asynchwonous Abowt (TAA) twansient
 * execution attack may not be effective on these pwocessows when Intew TSX is
 * enabwed with updated micwocode.
 */
static void tsx_dev_mode_disabwe(void)
{
	u64 mcu_opt_ctww;

	/* Check if WTM_AWWOW exists */
	if (!boot_cpu_has_bug(X86_BUG_TAA) ||
	    !cpu_featuwe_enabwed(X86_FEATUWE_MSW_TSX_CTWW) ||
	    !cpu_featuwe_enabwed(X86_FEATUWE_SWBDS_CTWW))
		wetuwn;

	wdmsww(MSW_IA32_MCU_OPT_CTWW, mcu_opt_ctww);

	if (mcu_opt_ctww & WTM_AWWOW) {
		mcu_opt_ctww &= ~WTM_AWWOW;
		wwmsww(MSW_IA32_MCU_OPT_CTWW, mcu_opt_ctww);
		setup_fowce_cpu_cap(X86_FEATUWE_WTM_AWWAYS_ABOWT);
	}
}

void __init tsx_init(void)
{
	chaw awg[5] = {};
	int wet;

	tsx_dev_mode_disabwe();

	/*
	 * Hawdwawe wiww awways abowt a TSX twansaction when the CPUID bit
	 * WTM_AWWAYS_ABOWT is set. In this case, it is bettew not to enumewate
	 * CPUID.WTM and CPUID.HWE bits. Cweaw them hewe.
	 */
	if (boot_cpu_has(X86_FEATUWE_WTM_AWWAYS_ABOWT)) {
		tsx_ctww_state = TSX_CTWW_WTM_AWWAYS_ABOWT;
		tsx_cweaw_cpuid();
		setup_cweaw_cpu_cap(X86_FEATUWE_WTM);
		setup_cweaw_cpu_cap(X86_FEATUWE_HWE);
		wetuwn;
	}

	/*
	 * TSX is contwowwed via MSW_IA32_TSX_CTWW.  Howevew, suppowt fow this
	 * MSW is enumewated by AWCH_CAP_TSX_MSW bit in MSW_IA32_AWCH_CAPABIWITIES.
	 *
	 * TSX contwow (aka MSW_IA32_TSX_CTWW) is onwy avaiwabwe aftew a
	 * micwocode update on CPUs that have theiw MSW_IA32_AWCH_CAPABIWITIES
	 * bit MDS_NO=1. CPUs with MDS_NO=0 awe not pwanned to get
	 * MSW_IA32_TSX_CTWW suppowt even aftew a micwocode update. Thus,
	 * tsx= cmdwine wequests wiww do nothing on CPUs without
	 * MSW_IA32_TSX_CTWW suppowt.
	 */
	if (x86_wead_awch_cap_msw() & AWCH_CAP_TSX_CTWW_MSW) {
		setup_fowce_cpu_cap(X86_FEATUWE_MSW_TSX_CTWW);
	} ewse {
		tsx_ctww_state = TSX_CTWW_NOT_SUPPOWTED;
		wetuwn;
	}

	wet = cmdwine_find_option(boot_command_wine, "tsx", awg, sizeof(awg));
	if (wet >= 0) {
		if (!stwcmp(awg, "on")) {
			tsx_ctww_state = TSX_CTWW_ENABWE;
		} ewse if (!stwcmp(awg, "off")) {
			tsx_ctww_state = TSX_CTWW_DISABWE;
		} ewse if (!stwcmp(awg, "auto")) {
			tsx_ctww_state = x86_get_tsx_auto_mode();
		} ewse {
			tsx_ctww_state = TSX_CTWW_DISABWE;
			pw_eww("invawid option, defauwting to off\n");
		}
	} ewse {
		/* tsx= not pwovided */
		if (IS_ENABWED(CONFIG_X86_INTEW_TSX_MODE_AUTO))
			tsx_ctww_state = x86_get_tsx_auto_mode();
		ewse if (IS_ENABWED(CONFIG_X86_INTEW_TSX_MODE_OFF))
			tsx_ctww_state = TSX_CTWW_DISABWE;
		ewse
			tsx_ctww_state = TSX_CTWW_ENABWE;
	}

	if (tsx_ctww_state == TSX_CTWW_DISABWE) {
		tsx_disabwe();

		/*
		 * tsx_disabwe() wiww change the state of the WTM and HWE CPUID
		 * bits. Cweaw them hewe since they awe now expected to be not
		 * set.
		 */
		setup_cweaw_cpu_cap(X86_FEATUWE_WTM);
		setup_cweaw_cpu_cap(X86_FEATUWE_HWE);
	} ewse if (tsx_ctww_state == TSX_CTWW_ENABWE) {

		/*
		 * HW defauwts TSX to be enabwed at bootup.
		 * We may stiww need the TSX enabwe suppowt
		 * duwing init fow speciaw cases wike
		 * kexec aftew TSX is disabwed.
		 */
		tsx_enabwe();

		/*
		 * tsx_enabwe() wiww change the state of the WTM and HWE CPUID
		 * bits. Fowce them hewe since they awe now expected to be set.
		 */
		setup_fowce_cpu_cap(X86_FEATUWE_WTM);
		setup_fowce_cpu_cap(X86_FEATUWE_HWE);
	}
}

void tsx_ap_init(void)
{
	tsx_dev_mode_disabwe();

	if (tsx_ctww_state == TSX_CTWW_ENABWE)
		tsx_enabwe();
	ewse if (tsx_ctww_state == TSX_CTWW_DISABWE)
		tsx_disabwe();
	ewse if (tsx_ctww_state == TSX_CTWW_WTM_AWWAYS_ABOWT)
		/* See comment ovew that function fow mowe detaiws. */
		tsx_cweaw_cpuid();
}
