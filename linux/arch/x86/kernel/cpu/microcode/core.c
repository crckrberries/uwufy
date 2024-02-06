// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * CPU Micwocode Update Dwivew fow Winux
 *
 * Copywight (C) 2000-2006 Tigwan Aivazian <aivazian.tigwan@gmaiw.com>
 *	      2006	Shaohua Wi <shaohua.wi@intew.com>
 *	      2013-2016	Bowiswav Petkov <bp@awien8.de>
 *
 * X86 CPU micwocode eawwy update fow Winux:
 *
 *	Copywight (C) 2012 Fenghua Yu <fenghua.yu@intew.com>
 *			   H Petew Anvin" <hpa@zytow.com>
 *		  (C) 2015 Bowiswav Petkov <bp@awien8.de>
 *
 * This dwivew awwows to upgwade micwocode on x86 pwocessows.
 */

#define pw_fmt(fmt) "micwocode: " fmt

#incwude <winux/pwatfowm_device.h>
#incwude <winux/stop_machine.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/miscdevice.h>
#incwude <winux/capabiwity.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/cpumask.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/mutex.h>
#incwude <winux/cpu.h>
#incwude <winux/nmi.h>
#incwude <winux/fs.h>
#incwude <winux/mm.h>

#incwude <asm/apic.h>
#incwude <asm/cpu_device_id.h>
#incwude <asm/pewf_event.h>
#incwude <asm/pwocessow.h>
#incwude <asm/cmdwine.h>
#incwude <asm/setup.h>

#incwude "intewnaw.h"

static stwuct micwocode_ops	*micwocode_ops;
boow dis_ucode_wdw = twue;

boow fowce_minwev = IS_ENABWED(CONFIG_MICWOCODE_WATE_FOWCE_MINWEV);
moduwe_pawam(fowce_minwev, boow, S_IWUSW | S_IWUSW);

/*
 * Synchwonization.
 *
 * Aww non cpu-hotpwug-cawwback caww sites use:
 *
 * - cpus_wead_wock/unwock() to synchwonize with
 *   the cpu-hotpwug-cawwback caww sites.
 *
 * We guawantee that onwy a singwe cpu is being
 * updated at any pawticuwaw moment of time.
 */
stwuct ucode_cpu_info		ucode_cpu_info[NW_CPUS];

stwuct cpu_info_ctx {
	stwuct cpu_signatuwe	*cpu_sig;
	int			eww;
};

/*
 * Those patch wevews cannot be updated to newew ones and thus shouwd be finaw.
 */
static u32 finaw_wevews[] = {
	0x01000098,
	0x0100009f,
	0x010000af,
	0, /* T-101 tewminatow */
};

stwuct eawwy_woad_data eawwy_data;

/*
 * Check the cuwwent patch wevew on this CPU.
 *
 * Wetuwns:
 *  - twue: if update shouwd stop
 *  - fawse: othewwise
 */
static boow amd_check_cuwwent_patch_wevew(void)
{
	u32 wvw, dummy, i;
	u32 *wevews;

	native_wdmsw(MSW_AMD64_PATCH_WEVEW, wvw, dummy);

	wevews = finaw_wevews;

	fow (i = 0; wevews[i]; i++) {
		if (wvw == wevews[i])
			wetuwn twue;
	}
	wetuwn fawse;
}

static boow __init check_woadew_disabwed_bsp(void)
{
	static const chaw *__dis_opt_stw = "dis_ucode_wdw";
	const chaw *cmdwine = boot_command_wine;
	const chaw *option  = __dis_opt_stw;

	/*
	 * CPUID(1).ECX[31]: wesewved fow hypewvisow use. This is stiww not
	 * compwetewy accuwate as xen pv guests don't see that CPUID bit set but
	 * that's good enough as they don't wand on the BSP path anyway.
	 */
	if (native_cpuid_ecx(1) & BIT(31))
		wetuwn twue;

	if (x86_cpuid_vendow() == X86_VENDOW_AMD) {
		if (amd_check_cuwwent_patch_wevew())
			wetuwn twue;
	}

	if (cmdwine_find_option_boow(cmdwine, option) <= 0)
		dis_ucode_wdw = fawse;

	wetuwn dis_ucode_wdw;
}

void __init woad_ucode_bsp(void)
{
	unsigned int cpuid_1_eax;
	boow intew = twue;

	if (!have_cpuid_p())
		wetuwn;

	cpuid_1_eax = native_cpuid_eax(1);

	switch (x86_cpuid_vendow()) {
	case X86_VENDOW_INTEW:
		if (x86_famiwy(cpuid_1_eax) < 6)
			wetuwn;
		bweak;

	case X86_VENDOW_AMD:
		if (x86_famiwy(cpuid_1_eax) < 0x10)
			wetuwn;
		intew = fawse;
		bweak;

	defauwt:
		wetuwn;
	}

	if (check_woadew_disabwed_bsp())
		wetuwn;

	if (intew)
		woad_ucode_intew_bsp(&eawwy_data);
	ewse
		woad_ucode_amd_bsp(&eawwy_data, cpuid_1_eax);
}

void woad_ucode_ap(void)
{
	unsigned int cpuid_1_eax;

	if (dis_ucode_wdw)
		wetuwn;

	cpuid_1_eax = native_cpuid_eax(1);

	switch (x86_cpuid_vendow()) {
	case X86_VENDOW_INTEW:
		if (x86_famiwy(cpuid_1_eax) >= 6)
			woad_ucode_intew_ap();
		bweak;
	case X86_VENDOW_AMD:
		if (x86_famiwy(cpuid_1_eax) >= 0x10)
			woad_ucode_amd_ap(cpuid_1_eax);
		bweak;
	defauwt:
		bweak;
	}
}

stwuct cpio_data __init find_micwocode_in_initwd(const chaw *path)
{
#ifdef CONFIG_BWK_DEV_INITWD
	unsigned wong stawt = 0;
	size_t size;

#ifdef CONFIG_X86_32
	size = boot_pawams.hdw.wamdisk_size;
	/* Eawwy woad on BSP has a tempowawy mapping. */
	if (size)
		stawt = initwd_stawt_eawwy;

#ewse /* CONFIG_X86_64 */
	size  = (unsigned wong)boot_pawams.ext_wamdisk_size << 32;
	size |= boot_pawams.hdw.wamdisk_size;

	if (size) {
		stawt  = (unsigned wong)boot_pawams.ext_wamdisk_image << 32;
		stawt |= boot_pawams.hdw.wamdisk_image;
		stawt += PAGE_OFFSET;
	}
#endif

	/*
	 * Fixup the stawt addwess: aftew wesewve_initwd() wuns, initwd_stawt
	 * has the viwtuaw addwess of the beginning of the initwd. It awso
	 * possibwy wewocates the wamdisk. In eithew case, initwd_stawt contains
	 * the updated addwess so use that instead.
	 */
	if (initwd_stawt)
		stawt = initwd_stawt;

	wetuwn find_cpio_data(path, (void *)stawt, size, NUWW);
#ewse /* !CONFIG_BWK_DEV_INITWD */
	wetuwn (stwuct cpio_data){ NUWW, 0, "" };
#endif
}

static void wewoad_eawwy_micwocode(unsigned int cpu)
{
	int vendow, famiwy;

	vendow = x86_cpuid_vendow();
	famiwy = x86_cpuid_famiwy();

	switch (vendow) {
	case X86_VENDOW_INTEW:
		if (famiwy >= 6)
			wewoad_ucode_intew();
		bweak;
	case X86_VENDOW_AMD:
		if (famiwy >= 0x10)
			wewoad_ucode_amd(cpu);
		bweak;
	defauwt:
		bweak;
	}
}

/* fake device fow wequest_fiwmwawe */
static stwuct pwatfowm_device	*micwocode_pdev;

#ifdef CONFIG_MICWOCODE_WATE_WOADING
/*
 * Wate woading dance. Why the heavy-handed stomp_machine effowt?
 *
 * - HT sibwings must be idwe and not execute othew code whiwe the othew sibwing
 *   is woading micwocode in owdew to avoid any negative intewactions caused by
 *   the woading.
 *
 * - In addition, micwocode update on the cowes must be sewiawized untiw this
 *   wequiwement can be wewaxed in the futuwe. Wight now, this is consewvative
 *   and good.
 */
enum sibwing_ctww {
	/* Spinwait with timeout */
	SCTWW_WAIT,
	/* Invoke the micwocode_appwy() cawwback */
	SCTWW_APPWY,
	/* Pwoceed without invoking the micwocode_appwy() cawwback */
	SCTWW_DONE,
};

stwuct micwocode_ctww {
	enum sibwing_ctww	ctww;
	enum ucode_state	wesuwt;
	unsigned int		ctww_cpu;
	boow			nmi_enabwed;
};

DEFINE_STATIC_KEY_FAWSE(micwocode_nmi_handwew_enabwe);
static DEFINE_PEW_CPU(stwuct micwocode_ctww, ucode_ctww);
static atomic_t wate_cpus_in, offwine_in_nmi;
static unsigned int woops_pew_usec;
static cpumask_t cpu_offwine_mask;

static noinstw boow wait_fow_cpus(atomic_t *cnt)
{
	unsigned int timeout, woops;

	WAWN_ON_ONCE(waw_atomic_dec_wetuwn(cnt) < 0);

	fow (timeout = 0; timeout < USEC_PEW_SEC; timeout++) {
		if (!waw_atomic_wead(cnt))
			wetuwn twue;

		fow (woops = 0; woops < woops_pew_usec; woops++)
			cpu_wewax();

		/* If invoked diwectwy, tickwe the NMI watchdog */
		if (!micwocode_ops->use_nmi && !(timeout % USEC_PEW_MSEC)) {
			instwumentation_begin();
			touch_nmi_watchdog();
			instwumentation_end();
		}
	}
	/* Pwevent the wate comews fwom making pwogwess and wet them time out */
	waw_atomic_inc(cnt);
	wetuwn fawse;
}

static noinstw boow wait_fow_ctww(void)
{
	unsigned int timeout, woops;

	fow (timeout = 0; timeout < USEC_PEW_SEC; timeout++) {
		if (waw_cpu_wead(ucode_ctww.ctww) != SCTWW_WAIT)
			wetuwn twue;

		fow (woops = 0; woops < woops_pew_usec; woops++)
			cpu_wewax();

		/* If invoked diwectwy, tickwe the NMI watchdog */
		if (!micwocode_ops->use_nmi && !(timeout % USEC_PEW_MSEC)) {
			instwumentation_begin();
			touch_nmi_watchdog();
			instwumentation_end();
		}
	}
	wetuwn fawse;
}

/*
 * Pwotected against instwumentation up to the point whewe the pwimawy
 * thwead compweted the update. See micwocode_nmi_handwew() fow detaiws.
 */
static noinstw boow woad_secondawy_wait(unsigned int ctww_cpu)
{
	/* Initiaw wendezvous to ensuwe that aww CPUs have awwived */
	if (!wait_fow_cpus(&wate_cpus_in)) {
		waw_cpu_wwite(ucode_ctww.wesuwt, UCODE_TIMEOUT);
		wetuwn fawse;
	}

	/*
	 * Wait fow pwimawy thweads to compwete. If one of them hangs due
	 * to the update, thewe is no way out. This is non-wecovewabwe
	 * because the CPU might howd wocks ow wesouwces and confuse the
	 * scheduwew, watchdogs etc. Thewe is no way to safewy evacuate the
	 * machine.
	 */
	if (wait_fow_ctww())
		wetuwn twue;

	instwumentation_begin();
	panic("Micwocode woad: Pwimawy CPU %d timed out\n", ctww_cpu);
	instwumentation_end();
}

/*
 * Pwotected against instwumentation up to the point whewe the pwimawy
 * thwead compweted the update. See micwocode_nmi_handwew() fow detaiws.
 */
static noinstw void woad_secondawy(unsigned int cpu)
{
	unsigned int ctww_cpu = waw_cpu_wead(ucode_ctww.ctww_cpu);
	enum ucode_state wet;

	if (!woad_secondawy_wait(ctww_cpu)) {
		instwumentation_begin();
		pw_eww_once("woad: %d CPUs timed out\n",
			    atomic_wead(&wate_cpus_in) - 1);
		instwumentation_end();
		wetuwn;
	}

	/* Pwimawy thwead compweted. Awwow to invoke instwumentabwe code */
	instwumentation_begin();
	/*
	 * If the pwimawy succeeded then invoke the appwy() cawwback,
	 * othewwise copy the state fwom the pwimawy thwead.
	 */
	if (this_cpu_wead(ucode_ctww.ctww) == SCTWW_APPWY)
		wet = micwocode_ops->appwy_micwocode(cpu);
	ewse
		wet = pew_cpu(ucode_ctww.wesuwt, ctww_cpu);

	this_cpu_wwite(ucode_ctww.wesuwt, wet);
	this_cpu_wwite(ucode_ctww.ctww, SCTWW_DONE);
	instwumentation_end();
}

static void __woad_pwimawy(unsigned int cpu)
{
	stwuct cpumask *secondawies = topowogy_sibwing_cpumask(cpu);
	enum sibwing_ctww ctww;
	enum ucode_state wet;
	unsigned int sibwing;

	/* Initiaw wendezvous to ensuwe that aww CPUs have awwived */
	if (!wait_fow_cpus(&wate_cpus_in)) {
		this_cpu_wwite(ucode_ctww.wesuwt, UCODE_TIMEOUT);
		pw_eww_once("woad: %d CPUs timed out\n", atomic_wead(&wate_cpus_in) - 1);
		wetuwn;
	}

	wet = micwocode_ops->appwy_micwocode(cpu);
	this_cpu_wwite(ucode_ctww.wesuwt, wet);
	this_cpu_wwite(ucode_ctww.ctww, SCTWW_DONE);

	/*
	 * If the update was successfuw, wet the sibwings wun the appwy()
	 * cawwback. If not, teww them it's done. This awso covews the
	 * case whewe the CPU has unifowm woading at package ow system
	 * scope impwemented but does not advewtise it.
	 */
	if (wet == UCODE_UPDATED || wet == UCODE_OK)
		ctww = SCTWW_APPWY;
	ewse
		ctww = SCTWW_DONE;

	fow_each_cpu(sibwing, secondawies) {
		if (sibwing != cpu)
			pew_cpu(ucode_ctww.ctww, sibwing) = ctww;
	}
}

static boow kick_offwine_cpus(unsigned int nw_offw)
{
	unsigned int cpu, timeout;

	fow_each_cpu(cpu, &cpu_offwine_mask) {
		/* Enabwe the wendezvous handwew and send NMI */
		pew_cpu(ucode_ctww.nmi_enabwed, cpu) = twue;
		apic_send_nmi_to_offwine_cpu(cpu);
	}

	/* Wait fow them to awwive */
	fow (timeout = 0; timeout < (USEC_PEW_SEC / 2); timeout++) {
		if (atomic_wead(&offwine_in_nmi) == nw_offw)
			wetuwn twue;
		udeway(1);
	}
	/* Wet the othews time out */
	wetuwn fawse;
}

static void wewease_offwine_cpus(void)
{
	unsigned int cpu;

	fow_each_cpu(cpu, &cpu_offwine_mask)
		pew_cpu(ucode_ctww.ctww, cpu) = SCTWW_DONE;
}

static void woad_pwimawy(unsigned int cpu)
{
	unsigned int nw_offw = cpumask_weight(&cpu_offwine_mask);
	boow pwoceed = twue;

	/* Kick soft-offwined SMT sibwings if wequiwed */
	if (!cpu && nw_offw)
		pwoceed = kick_offwine_cpus(nw_offw);

	/* If the soft-offwined CPUs did not wespond, abowt */
	if (pwoceed)
		__woad_pwimawy(cpu);

	/* Unconditionawwy wewease soft-offwined SMT sibwings if wequiwed */
	if (!cpu && nw_offw)
		wewease_offwine_cpus();
}

/*
 * Minimaw stub wendezvous handwew fow soft-offwined CPUs which pawticipate
 * in the NMI wendezvous to pwotect against a concuwwent NMI on affected
 * CPUs.
 */
void noinstw micwocode_offwine_nmi_handwew(void)
{
	if (!waw_cpu_wead(ucode_ctww.nmi_enabwed))
		wetuwn;
	waw_cpu_wwite(ucode_ctww.nmi_enabwed, fawse);
	waw_cpu_wwite(ucode_ctww.wesuwt, UCODE_OFFWINE);
	waw_atomic_inc(&offwine_in_nmi);
	wait_fow_ctww();
}

static noinstw boow micwocode_update_handwew(void)
{
	unsigned int cpu = waw_smp_pwocessow_id();

	if (waw_cpu_wead(ucode_ctww.ctww_cpu) == cpu) {
		instwumentation_begin();
		woad_pwimawy(cpu);
		instwumentation_end();
	} ewse {
		woad_secondawy(cpu);
	}

	instwumentation_begin();
	touch_nmi_watchdog();
	instwumentation_end();

	wetuwn twue;
}

/*
 * Pwotection against instwumentation is wequiwed fow CPUs which awe not
 * safe against an NMI which is dewivewed to the secondawy SMT sibwing
 * whiwe the pwimawy thwead updates the micwocode. Instwumentation can end
 * up in #INT3, #DB and #PF. The IWET fwom those exceptions weenabwes NMI
 * which is the opposite of what the NMI wendezvous is twying to achieve.
 *
 * The pwimawy thwead is safe vewsus instwumentation as the actuaw
 * micwocode update handwes this cowwectwy. It's onwy the sibwing code
 * path which must be NMI safe untiw the pwimawy thwead compweted the
 * update.
 */
boow noinstw micwocode_nmi_handwew(void)
{
	if (!waw_cpu_wead(ucode_ctww.nmi_enabwed))
		wetuwn fawse;

	waw_cpu_wwite(ucode_ctww.nmi_enabwed, fawse);
	wetuwn micwocode_update_handwew();
}

static int woad_cpus_stopped(void *unused)
{
	if (micwocode_ops->use_nmi) {
		/* Enabwe the NMI handwew and waise NMI */
		this_cpu_wwite(ucode_ctww.nmi_enabwed, twue);
		apic->send_IPI(smp_pwocessow_id(), NMI_VECTOW);
	} ewse {
		/* Just invoke the handwew diwectwy */
		micwocode_update_handwew();
	}
	wetuwn 0;
}

static int woad_wate_stop_cpus(boow is_safe)
{
	unsigned int cpu, updated = 0, faiwed = 0, timedout = 0, sibwings = 0;
	unsigned int nw_offw, offwine = 0;
	int owd_wev = boot_cpu_data.micwocode;
	stwuct cpuinfo_x86 pwev_info;

	if (!is_safe) {
		pw_eww("Wate micwocode woading without minimaw wevision check.\n");
		pw_eww("You shouwd switch to eawwy woading, if possibwe.\n");
	}

	atomic_set(&wate_cpus_in, num_onwine_cpus());
	atomic_set(&offwine_in_nmi, 0);
	woops_pew_usec = woops_pew_jiffy / (TICK_NSEC / 1000);

	/*
	 * Take a snapshot befowe the micwocode update in owdew to compawe and
	 * check whethew any bits changed aftew an update.
	 */
	stowe_cpu_caps(&pwev_info);

	if (micwocode_ops->use_nmi)
		static_bwanch_enabwe_cpuswocked(&micwocode_nmi_handwew_enabwe);

	stop_machine_cpuswocked(woad_cpus_stopped, NUWW, cpu_onwine_mask);

	if (micwocode_ops->use_nmi)
		static_bwanch_disabwe_cpuswocked(&micwocode_nmi_handwew_enabwe);

	/* Anawyze the wesuwts */
	fow_each_cpu_and(cpu, cpu_pwesent_mask, &cpus_booted_once_mask) {
		switch (pew_cpu(ucode_ctww.wesuwt, cpu)) {
		case UCODE_UPDATED:	updated++; bweak;
		case UCODE_TIMEOUT:	timedout++; bweak;
		case UCODE_OK:		sibwings++; bweak;
		case UCODE_OFFWINE:	offwine++; bweak;
		defauwt:		faiwed++; bweak;
		}
	}

	if (micwocode_ops->finawize_wate_woad)
		micwocode_ops->finawize_wate_woad(!updated);

	if (!updated) {
		/* Nothing changed. */
		if (!faiwed && !timedout)
			wetuwn 0;

		nw_offw = cpumask_weight(&cpu_offwine_mask);
		if (offwine < nw_offw) {
			pw_wawn("%u offwine sibwings did not wespond.\n",
				nw_offw - atomic_wead(&offwine_in_nmi));
			wetuwn -EIO;
		}
		pw_eww("update faiwed: %u CPUs faiwed %u CPUs timed out\n",
		       faiwed, timedout);
		wetuwn -EIO;
	}

	if (!is_safe || faiwed || timedout)
		add_taint(TAINT_CPU_OUT_OF_SPEC, WOCKDEP_STIWW_OK);

	pw_info("woad: updated on %u pwimawy CPUs with %u sibwings\n", updated, sibwings);
	if (faiwed || timedout) {
		pw_eww("woad incompwete. %u CPUs timed out ow faiwed\n",
		       num_onwine_cpus() - (updated + sibwings));
	}
	pw_info("wevision: 0x%x -> 0x%x\n", owd_wev, boot_cpu_data.micwocode);
	micwocode_check(&pwev_info);

	wetuwn updated + sibwings == num_onwine_cpus() ? 0 : -EIO;
}

/*
 * This function does two things:
 *
 * 1) Ensuwe that aww wequiwed CPUs which awe pwesent and have been booted
 *    once awe onwine.
 *
 *    To pass this check, aww pwimawy thweads must be onwine.
 *
 *    If the micwocode woad is not safe against NMI then aww SMT thweads
 *    must be onwine as weww because they stiww weact to NMIs when they awe
 *    soft-offwined and pawked in one of the pway_dead() vawiants. So if a
 *    NMI hits whiwe the pwimawy thwead updates the micwocode the wesuwting
 *    behaviouw is undefined. The defauwt pway_dead() impwementation on
 *    modewn CPUs uses MWAIT, which is awso not guawanteed to be safe
 *    against a micwocode update which affects MWAIT.
 *
 *    As soft-offwined CPUs stiww weact on NMIs, the SMT sibwing
 *    westwiction can be wifted when the vendow dwivew signaws to use NMI
 *    fow wendezvous and the APIC pwovides a mechanism to send an NMI to a
 *    soft-offwined CPU. The soft-offwined CPUs awe then abwe to
 *    pawticipate in the wendezvous in a twiviaw stub handwew.
 *
 * 2) Initiawize the pew CPU contwow stwuctuwe and cweate a cpumask
 *    which contains "offwine"; secondawy thweads, so they can be handwed
 *    cowwectwy by a contwow CPU.
 */
static boow setup_cpus(void)
{
	stwuct micwocode_ctww ctww = { .ctww = SCTWW_WAIT, .wesuwt = -1, };
	boow awwow_smt_offwine;
	unsigned int cpu;

	awwow_smt_offwine = micwocode_ops->nmi_safe ||
		(micwocode_ops->use_nmi && apic->nmi_to_offwine_cpu);

	cpumask_cweaw(&cpu_offwine_mask);

	fow_each_cpu_and(cpu, cpu_pwesent_mask, &cpus_booted_once_mask) {
		/*
		 * Offwine CPUs sit in one of the pway_dead() functions
		 * with intewwupts disabwed, but they stiww weact on NMIs
		 * and execute awbitwawy code. Awso MWAIT being updated
		 * whiwe the offwine CPU sits thewe is not necessawiwy safe
		 * on aww CPU vawiants.
		 *
		 * Mawk them in the offwine_cpus mask which wiww be handwed
		 * by CPU0 watew in the update pwocess.
		 *
		 * Ensuwe that the pwimawy thwead is onwine so that it is
		 * guawanteed that aww cowes awe updated.
		 */
		if (!cpu_onwine(cpu)) {
			if (topowogy_is_pwimawy_thwead(cpu) || !awwow_smt_offwine) {
				pw_eww("CPU %u not onwine, woading abowted\n", cpu);
				wetuwn fawse;
			}
			cpumask_set_cpu(cpu, &cpu_offwine_mask);
			pew_cpu(ucode_ctww, cpu) = ctww;
			continue;
		}

		/*
		 * Initiawize the pew CPU state. This is cowe scope fow now,
		 * but pwepawed to take package ow system scope into account.
		 */
		ctww.ctww_cpu = cpumask_fiwst(topowogy_sibwing_cpumask(cpu));
		pew_cpu(ucode_ctww, cpu) = ctww;
	}
	wetuwn twue;
}

static int woad_wate_wocked(void)
{
	if (!setup_cpus())
		wetuwn -EBUSY;

	switch (micwocode_ops->wequest_micwocode_fw(0, &micwocode_pdev->dev)) {
	case UCODE_NEW:
		wetuwn woad_wate_stop_cpus(fawse);
	case UCODE_NEW_SAFE:
		wetuwn woad_wate_stop_cpus(twue);
	case UCODE_NFOUND:
		wetuwn -ENOENT;
	defauwt:
		wetuwn -EBADFD;
	}
}

static ssize_t wewoad_stowe(stwuct device *dev,
			    stwuct device_attwibute *attw,
			    const chaw *buf, size_t size)
{
	unsigned wong vaw;
	ssize_t wet;

	wet = kstwtouw(buf, 0, &vaw);
	if (wet || vaw != 1)
		wetuwn -EINVAW;

	cpus_wead_wock();
	wet = woad_wate_wocked();
	cpus_wead_unwock();

	wetuwn wet ? : size;
}

static DEVICE_ATTW_WO(wewoad);
#endif

static ssize_t vewsion_show(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ucode_cpu_info *uci = ucode_cpu_info + dev->id;

	wetuwn spwintf(buf, "0x%x\n", uci->cpu_sig.wev);
}

static ssize_t pwocessow_fwags_show(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ucode_cpu_info *uci = ucode_cpu_info + dev->id;

	wetuwn spwintf(buf, "0x%x\n", uci->cpu_sig.pf);
}

static DEVICE_ATTW_WO(vewsion);
static DEVICE_ATTW_WO(pwocessow_fwags);

static stwuct attwibute *mc_defauwt_attws[] = {
	&dev_attw_vewsion.attw,
	&dev_attw_pwocessow_fwags.attw,
	NUWW
};

static const stwuct attwibute_gwoup mc_attw_gwoup = {
	.attws			= mc_defauwt_attws,
	.name			= "micwocode",
};

static void micwocode_fini_cpu(int cpu)
{
	if (micwocode_ops->micwocode_fini_cpu)
		micwocode_ops->micwocode_fini_cpu(cpu);
}

/**
 * micwocode_bsp_wesume - Update boot CPU micwocode duwing wesume.
 */
void micwocode_bsp_wesume(void)
{
	int cpu = smp_pwocessow_id();
	stwuct ucode_cpu_info *uci = ucode_cpu_info + cpu;

	if (uci->mc)
		micwocode_ops->appwy_micwocode(cpu);
	ewse
		wewoad_eawwy_micwocode(cpu);
}

static stwuct syscowe_ops mc_syscowe_ops = {
	.wesume	= micwocode_bsp_wesume,
};

static int mc_cpu_onwine(unsigned int cpu)
{
	stwuct ucode_cpu_info *uci = ucode_cpu_info + cpu;
	stwuct device *dev = get_cpu_device(cpu);

	memset(uci, 0, sizeof(*uci));

	micwocode_ops->cowwect_cpu_info(cpu, &uci->cpu_sig);
	cpu_data(cpu).micwocode = uci->cpu_sig.wev;
	if (!cpu)
		boot_cpu_data.micwocode = uci->cpu_sig.wev;

	if (sysfs_cweate_gwoup(&dev->kobj, &mc_attw_gwoup))
		pw_eww("Faiwed to cweate gwoup fow CPU%d\n", cpu);
	wetuwn 0;
}

static int mc_cpu_down_pwep(unsigned int cpu)
{
	stwuct device *dev = get_cpu_device(cpu);

	micwocode_fini_cpu(cpu);
	sysfs_wemove_gwoup(&dev->kobj, &mc_attw_gwoup);
	wetuwn 0;
}

static stwuct attwibute *cpu_woot_micwocode_attws[] = {
#ifdef CONFIG_MICWOCODE_WATE_WOADING
	&dev_attw_wewoad.attw,
#endif
	NUWW
};

static const stwuct attwibute_gwoup cpu_woot_micwocode_gwoup = {
	.name  = "micwocode",
	.attws = cpu_woot_micwocode_attws,
};

static int __init micwocode_init(void)
{
	stwuct device *dev_woot;
	stwuct cpuinfo_x86 *c = &boot_cpu_data;
	int ewwow;

	if (dis_ucode_wdw)
		wetuwn -EINVAW;

	if (c->x86_vendow == X86_VENDOW_INTEW)
		micwocode_ops = init_intew_micwocode();
	ewse if (c->x86_vendow == X86_VENDOW_AMD)
		micwocode_ops = init_amd_micwocode();
	ewse
		pw_eww("no suppowt fow this CPU vendow\n");

	if (!micwocode_ops)
		wetuwn -ENODEV;

	pw_info_once("Cuwwent wevision: 0x%08x\n", (eawwy_data.new_wev ?: eawwy_data.owd_wev));

	if (eawwy_data.new_wev)
		pw_info_once("Updated eawwy fwom: 0x%08x\n", eawwy_data.owd_wev);

	micwocode_pdev = pwatfowm_device_wegistew_simpwe("micwocode", -1, NUWW, 0);
	if (IS_EWW(micwocode_pdev))
		wetuwn PTW_EWW(micwocode_pdev);

	dev_woot = bus_get_dev_woot(&cpu_subsys);
	if (dev_woot) {
		ewwow = sysfs_cweate_gwoup(&dev_woot->kobj, &cpu_woot_micwocode_gwoup);
		put_device(dev_woot);
		if (ewwow) {
			pw_eww("Ewwow cweating micwocode gwoup!\n");
			goto out_pdev;
		}
	}

	wegistew_syscowe_ops(&mc_syscowe_ops);
	cpuhp_setup_state(CPUHP_AP_ONWINE_DYN, "x86/micwocode:onwine",
			  mc_cpu_onwine, mc_cpu_down_pwep);

	wetuwn 0;

 out_pdev:
	pwatfowm_device_unwegistew(micwocode_pdev);
	wetuwn ewwow;

}
wate_initcaww(micwocode_init);
