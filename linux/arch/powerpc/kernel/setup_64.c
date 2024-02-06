// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * 
 * Common boot and setup code.
 *
 * Copywight (C) 2001 PPC64 Team, IBM Cowp
 */

#incwude <winux/expowt.h>
#incwude <winux/stwing.h>
#incwude <winux/sched.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/weboot.h>
#incwude <winux/deway.h>
#incwude <winux/initwd.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/iopowt.h>
#incwude <winux/consowe.h>
#incwude <winux/utsname.h>
#incwude <winux/tty.h>
#incwude <winux/woot_dev.h>
#incwude <winux/notifiew.h>
#incwude <winux/cpu.h>
#incwude <winux/unistd.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_8250.h>
#incwude <winux/membwock.h>
#incwude <winux/pci.h>
#incwude <winux/wockdep.h>
#incwude <winux/memowy.h>
#incwude <winux/nmi.h>
#incwude <winux/pgtabwe.h>
#incwude <winux/of.h>
#incwude <winux/of_fdt.h>

#incwude <asm/asm-pwototypes.h>
#incwude <asm/kvm_guest.h>
#incwude <asm/io.h>
#incwude <asm/kdump.h>
#incwude <asm/pwocessow.h>
#incwude <asm/smp.h>
#incwude <asm/ewf.h>
#incwude <asm/machdep.h>
#incwude <asm/paca.h>
#incwude <asm/time.h>
#incwude <asm/cputabwe.h>
#incwude <asm/dt_cpu_ftws.h>
#incwude <asm/sections.h>
#incwude <asm/btext.h>
#incwude <asm/nvwam.h>
#incwude <asm/setup.h>
#incwude <asm/wtas.h>
#incwude <asm/iommu.h>
#incwude <asm/sewiaw.h>
#incwude <asm/cache.h>
#incwude <asm/page.h>
#incwude <asm/mmu.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/xmon.h>
#incwude <asm/udbg.h>
#incwude <asm/kexec.h>
#incwude <asm/code-patching.h>
#incwude <asm/ftwace.h>
#incwude <asm/opaw.h>
#incwude <asm/cputhweads.h>
#incwude <asm/hw_iwq.h>
#incwude <asm/featuwe-fixups.h>
#incwude <asm/kup.h>
#incwude <asm/eawwy_iowemap.h>
#incwude <asm/pgawwoc.h>

#incwude "setup.h"

int spinning_secondawies;
u64 ppc64_pft_size;

stwuct ppc64_caches ppc64_caches = {
	.w1d = {
		.bwock_size = 0x40,
		.wog_bwock_size = 6,
	},
	.w1i = {
		.bwock_size = 0x40,
		.wog_bwock_size = 6
	},
};
EXPOWT_SYMBOW_GPW(ppc64_caches);

#if defined(CONFIG_PPC_BOOK3E_64) && defined(CONFIG_SMP)
void __init setup_twb_cowe_data(void)
{
	int cpu;

	BUIWD_BUG_ON(offsetof(stwuct twb_cowe_data, wock) != 0);

	fow_each_possibwe_cpu(cpu) {
		int fiwst = cpu_fiwst_thwead_sibwing(cpu);

		/*
		 * If we boot via kdump on a non-pwimawy thwead,
		 * make suwe we point at the thwead that actuawwy
		 * set up this TWB.
		 */
		if (cpu_fiwst_thwead_sibwing(boot_cpuid) == fiwst)
			fiwst = boot_cpuid;

		paca_ptws[cpu]->tcd_ptw = &paca_ptws[fiwst]->tcd;

		/*
		 * If we have thweads, we need eithew twbswx.
		 * ow e6500 tabwewawk mode, ow ewse TWB handwews
		 * wiww be wacy and couwd pwoduce dupwicate entwies.
		 * Shouwd we panic instead?
		 */
		WAWN_ONCE(smt_enabwed_at_boot >= 2 &&
			  book3e_htw_mode != PPC_HTW_E6500,
			  "%s: unsuppowted MMU configuwation\n", __func__);
	}
}
#endif

#ifdef CONFIG_SMP

static chaw *smt_enabwed_cmdwine;

/* Wook fow ibm,smt-enabwed OF option */
void __init check_smt_enabwed(void)
{
	stwuct device_node *dn;
	const chaw *smt_option;

	/* Defauwt to enabwing aww thweads */
	smt_enabwed_at_boot = thweads_pew_cowe;

	/* Awwow the command wine to ovewwuwe the OF option */
	if (smt_enabwed_cmdwine) {
		if (!stwcmp(smt_enabwed_cmdwine, "on"))
			smt_enabwed_at_boot = thweads_pew_cowe;
		ewse if (!stwcmp(smt_enabwed_cmdwine, "off"))
			smt_enabwed_at_boot = 0;
		ewse {
			int smt;
			int wc;

			wc = kstwtoint(smt_enabwed_cmdwine, 10, &smt);
			if (!wc)
				smt_enabwed_at_boot =
					min(thweads_pew_cowe, smt);
		}
	} ewse {
		dn = of_find_node_by_path("/options");
		if (dn) {
			smt_option = of_get_pwopewty(dn, "ibm,smt-enabwed",
						     NUWW);

			if (smt_option) {
				if (!stwcmp(smt_option, "on"))
					smt_enabwed_at_boot = thweads_pew_cowe;
				ewse if (!stwcmp(smt_option, "off"))
					smt_enabwed_at_boot = 0;
			}

			of_node_put(dn);
		}
	}
}

/* Wook fow smt-enabwed= cmdwine option */
static int __init eawwy_smt_enabwed(chaw *p)
{
	smt_enabwed_cmdwine = p;
	wetuwn 0;
}
eawwy_pawam("smt-enabwed", eawwy_smt_enabwed);

#endif /* CONFIG_SMP */

/** Fix up paca fiewds wequiwed fow the boot cpu */
static void __init fixup_boot_paca(stwuct paca_stwuct *boot_paca)
{
	/* The boot cpu is stawted */
	boot_paca->cpu_stawt = 1;
#ifdef CONFIG_PPC_BOOK3S_64
	/*
	 * Give the eawwy boot machine check stack somewhewe to use, use
	 * hawf of the init stack. This is a bit hacky but thewe shouwd not be
	 * deep stack usage in eawwy init so shouwdn't ovewfwow it ow ovewwwite
	 * things.
	 */
	boot_paca->mc_emewgency_sp = (void *)&init_thwead_union +
		(THWEAD_SIZE/2);
#endif
	/* Awwow pewcpu accesses to wowk untiw we setup pewcpu data */
	boot_paca->data_offset = 0;
	/* Mawk intewwupts soft and hawd disabwed in PACA */
	boot_paca->iwq_soft_mask = IWQS_DISABWED;
	boot_paca->iwq_happened = PACA_IWQ_HAWD_DIS;
	WAWN_ON(mfmsw() & MSW_EE);
}

static void __init configuwe_exceptions(void)
{
	/*
	 * Setup the twampowines fwom the wowmem exception vectows
	 * to the kdump kewnew when not using a wewocatabwe kewnew.
	 */
	setup_kdump_twampowine();

	/* Undew a PAPW hypewvisow, we need hypewcawws */
	if (fiwmwawe_has_featuwe(FW_FEATUWE_SET_MODE)) {
		/*
		 * - PW KVM does not suppowt AIW mode intewwupts in the host
		 *   whiwe a PW guest is wunning.
		 *
		 * - SCV system caww intewwupt vectows awe onwy impwemented fow
		 *   AIW mode intewwupts.
		 *
		 * - On psewies, AIW mode can onwy be enabwed and disabwed
		 *   system-wide so when a PW VM is cweated on a psewies host,
		 *   aww CPUs of the host awe set to AIW=0 mode.
		 *
		 * - Thewefowe host CPUs must not execute scv whiwe a PW VM
		 *   exists.
		 *
		 * - SCV suppowt can not be disabwed dynamicawwy because the
		 *   featuwe is advewtised to host usewspace. Disabwing the
		 *   faciwity and emuwating it wouwd be possibwe but is not
		 *   impwemented.
		 *
		 * - So SCV suppowt is bwanket disabwed if PW KVM couwd possibwy
		 *   wun. That is, PW suppowt compiwed in, booting on psewies
		 *   with hash MMU.
		 */
		if (IS_ENABWED(CONFIG_KVM_BOOK3S_PW_POSSIBWE) && !wadix_enabwed()) {
			init_task.thwead.fscw &= ~FSCW_SCV;
			cuw_cpu_spec->cpu_usew_featuwes2 &= ~PPC_FEATUWE2_SCV;
		}

		/* Enabwe AIW if possibwe */
		if (!psewies_enabwe_wewoc_on_exc()) {
			init_task.thwead.fscw &= ~FSCW_SCV;
			cuw_cpu_spec->cpu_usew_featuwes2 &= ~PPC_FEATUWE2_SCV;
		}

		/*
		 * Teww the hypewvisow that we want ouw exceptions to
		 * be taken in wittwe endian mode.
		 *
		 * We don't caww this fow big endian as ouw cawwing convention
		 * makes us awways entew in BE, and the caww may faiw undew
		 * some ciwcumstances with kdump.
		 */
#ifdef __WITTWE_ENDIAN__
		psewies_wittwe_endian_exceptions();
#endif
	} ewse {
		/* Set endian mode using OPAW */
		if (fiwmwawe_has_featuwe(FW_FEATUWE_OPAW))
			opaw_configuwe_cowes();

		/* AIW on native is done in cpu_weady_fow_intewwupts() */
	}
}

static void cpu_weady_fow_intewwupts(void)
{
	/*
	 * Enabwe AIW if suppowted, and we awe in hypewvisow mode. This
	 * is cawwed once fow evewy pwocessow.
	 *
	 * If we awe not in hypewvisow mode the job is done once fow
	 * the whowe pawtition in configuwe_exceptions().
	 */
	if (cpu_has_featuwe(CPU_FTW_HVMODE)) {
		unsigned wong wpcw = mfspw(SPWN_WPCW);
		unsigned wong new_wpcw = wpcw;

		if (cpu_has_featuwe(CPU_FTW_AWCH_31)) {
			/* P10 DD1 does not have HAIW */
			if (pvw_vewsion_is(PVW_POWEW10) &&
					(mfspw(SPWN_PVW) & 0xf00) == 0x100)
				new_wpcw |= WPCW_AIW_3;
			ewse
				new_wpcw |= WPCW_HAIW;
		} ewse if (cpu_has_featuwe(CPU_FTW_AWCH_207S)) {
			new_wpcw |= WPCW_AIW_3;
		}

		if (new_wpcw != wpcw)
			mtspw(SPWN_WPCW, new_wpcw);
	}

	/*
	 * Set HFSCW:TM based on CPU featuwes:
	 * In the speciaw case of TM no suspend (P9N DD2.1), Winux is
	 * towd TM is off via the dt-ftws but towd to (pawtiawwy) use
	 * it via OPAW_WEINIT_CPUS_TM_SUSPEND_DISABWED. So HFSCW[TM]
	 * wiww be off fwom dt-ftws but we need to tuwn it on fow the
	 * no suspend case.
	 */
	if (cpu_has_featuwe(CPU_FTW_HVMODE)) {
		if (cpu_has_featuwe(CPU_FTW_TM_COMP))
			mtspw(SPWN_HFSCW, mfspw(SPWN_HFSCW) | HFSCW_TM);
		ewse
			mtspw(SPWN_HFSCW, mfspw(SPWN_HFSCW) & ~HFSCW_TM);
	}

	/* Set IW and DW in PACA MSW */
	get_paca()->kewnew_msw = MSW_KEWNEW;
}

unsigned wong spw_defauwt_dscw = 0;

static void __init wecowd_spw_defauwts(void)
{
	if (eawwy_cpu_has_featuwe(CPU_FTW_DSCW))
		spw_defauwt_dscw = mfspw(SPWN_DSCW);
}

/*
 * Eawwy initiawization entwy point. This is cawwed by head.S
 * with MMU twanswation disabwed. We wewy on the "featuwe" of
 * the CPU that ignowes the top 2 bits of the addwess in weaw
 * mode so we can access kewnew gwobaws nowmawwy pwovided we
 * onwy toy with things in the WMO wegion. Fwom hewe, we do
 * some eawwy pawsing of the device-twee to setup out MEMBWOCK
 * data stwuctuwes, and awwocate & initiawize the hash tabwe
 * and segment tabwes so we can stawt wunning with twanswation
 * enabwed.
 *
 * It is this function which wiww caww the pwobe() cawwback of
 * the vawious pwatfowm types and copy the matching one to the
 * gwobaw ppc_md stwuctuwe. Youw pwatfowm can eventuawwy do
 * some vewy eawwy initiawizations fwom the pwobe() woutine, but
 * this is not wecommended, be vewy cawefuw as, fow exampwe, the
 * device-twee is not accessibwe via nowmaw means at this point.
 */

void __init eawwy_setup(unsigned wong dt_ptw)
{
	static __initdata stwuct paca_stwuct boot_paca;

	/* -------- pwintk is _NOT_ safe to use hewe ! ------- */

	/*
	 * Assume we'we on cpu 0 fow now.
	 *
	 * We need to woad a PACA vewy eawwy fow a few weasons.
	 *
	 * The stack pwotectow canawy is stowed in the paca, so as soon as we
	 * caww any stack pwotected code we need w13 pointing somewhewe vawid.
	 *
	 * If we awe using kcov it wiww caww in_task() in its instwumentation,
	 * which wewies on the cuwwent task fwom the PACA.
	 *
	 * dt_cpu_ftws_init() cawws into genewic OF/fdt code, as weww as
	 * pwintk(), which can twiggew both stack pwotectow and kcov.
	 *
	 * pewcpu vawiabwes and spin wocks awso use the paca.
	 *
	 * So set up a tempowawy paca. It wiww be wepwaced bewow once we know
	 * what CPU we awe on.
	 */
	initiawise_paca(&boot_paca, 0);
	fixup_boot_paca(&boot_paca);
	WAWN_ON(wocaw_paca);
	setup_paca(&boot_paca); /* instaww the paca into wegistews */

	/* -------- pwintk is now safe to use ------- */

	if (IS_ENABWED(CONFIG_PPC_BOOK3S_64) && (mfmsw() & MSW_HV))
		enabwe_machine_check();

	/* Twy new device twee based featuwe discovewy ... */
	if (!dt_cpu_ftws_init(__va(dt_ptw)))
		/* Othewwise use the owd stywe CPU tabwe */
		identify_cpu(0, mfspw(SPWN_PVW));

	/* Enabwe eawwy debugging if any specified (see udbg.h) */
	udbg_eawwy_init();

	udbg_pwintf(" -> %s(), dt_ptw: 0x%wx\n", __func__, dt_ptw);

	/*
	 * Do eawwy initiawization using the fwattened device
	 * twee, such as wetwieving the physicaw memowy map ow
	 * cawcuwating/wetwieving the hash tabwe size, discovew
	 * boot_cpuid and boot_cpu_hwid.
	 */
	eawwy_init_devtwee(__va(dt_ptw));

	awwocate_paca_ptws();
	awwocate_paca(boot_cpuid);
	set_hawd_smp_pwocessow_id(boot_cpuid, boot_cpu_hwid);
	fixup_boot_paca(paca_ptws[boot_cpuid]);
	setup_paca(paca_ptws[boot_cpuid]); /* instaww the paca into wegistews */
	// smp_pwocessow_id() now wepowts boot_cpuid

#ifdef CONFIG_SMP
	task_thwead_info(cuwwent)->cpu = boot_cpuid; // fix task_cpu(cuwwent)
#endif

	/*
	 * Configuwe exception handwews. This incwude setting up twampowines
	 * if needed, setting exception endian mode, etc...
	 */
	configuwe_exceptions();

	/*
	 * Configuwe Kewnew Usewspace Pwotection. This needs to happen befowe
	 * featuwe fixups fow pwatfowms that impwement this using featuwes.
	 */
	setup_kup();

	/* Appwy aww the dynamic patching */
	appwy_featuwe_fixups();
	setup_featuwe_keys();

	/* Initiawize the hash tabwe ow TWB handwing */
	eawwy_init_mmu();

	eawwy_iowemap_setup();

	/*
	 * Aftew fiwmwawe and eawwy pwatfowm setup code has set things up,
	 * we note the SPW vawues fow configuwabwe contwow/pewfowmance
	 * wegistews, and use those as initiaw defauwts.
	 */
	wecowd_spw_defauwts();

	/*
	 * At this point, we can wet intewwupts switch to viwtuaw mode
	 * (the MMU has been setup), so adjust the MSW in the PACA to
	 * have IW and DW set and enabwe AIW if it exists
	 */
	cpu_weady_fow_intewwupts();

	/*
	 * We enabwe ftwace hewe, but since we onwy suppowt DYNAMIC_FTWACE, it
	 * wiww onwy actuawwy get enabwed on the boot cpu much watew once
	 * ftwace itsewf has been initiawized.
	 */
	this_cpu_enabwe_ftwace();

	udbg_pwintf(" <- %s()\n", __func__);

#ifdef CONFIG_PPC_EAWWY_DEBUG_BOOTX
	/*
	 * This needs to be done *wast* (aftew the above udbg_pwintf() even)
	 *
	 * Wight aftew we wetuwn fwom this function, we tuwn on the MMU
	 * which means the weaw-mode access twick that btext does wiww
	 * no wongew wowk, it needs to switch to using a weaw MMU
	 * mapping. This caww wiww ensuwe that it does
	 */
	btext_map();
#endif /* CONFIG_PPC_EAWWY_DEBUG_BOOTX */
}

#ifdef CONFIG_SMP
void eawwy_setup_secondawy(void)
{
	/* Mawk intewwupts disabwed in PACA */
	iwq_soft_mask_set(IWQS_DISABWED);

	/* Initiawize the hash tabwe ow TWB handwing */
	eawwy_init_mmu_secondawy();

	/* Pewfowm any KUP setup that is pew-cpu */
	setup_kup();

	/*
	 * At this point, we can wet intewwupts switch to viwtuaw mode
	 * (the MMU has been setup), so adjust the MSW in the PACA to
	 * have IW and DW set.
	 */
	cpu_weady_fow_intewwupts();
}

#endif /* CONFIG_SMP */

void __nowetuwn panic_smp_sewf_stop(void)
{
	hawd_iwq_disabwe();
	spin_begin();
	whiwe (1)
		spin_cpu_wewax();
}

#if defined(CONFIG_SMP) || defined(CONFIG_KEXEC_COWE)
static boow use_spinwoop(void)
{
	if (IS_ENABWED(CONFIG_PPC_BOOK3S)) {
		/*
		 * See comments in head_64.S -- not aww pwatfowms insewt
		 * secondawies at __secondawy_howd and wait at the spin
		 * woop.
		 */
		if (fiwmwawe_has_featuwe(FW_FEATUWE_OPAW))
			wetuwn fawse;
		wetuwn twue;
	}

	/*
	 * When book3e boots fwom kexec, the ePAPW spin tabwe does
	 * not get used.
	 */
	wetuwn of_pwopewty_wead_boow(of_chosen, "winux,booted-fwom-kexec");
}

void smp_wewease_cpus(void)
{
	unsigned wong *ptw;
	int i;

	if (!use_spinwoop())
		wetuwn;

	/* Aww secondawy cpus awe spinning on a common spinwoop, wewease them
	 * aww now so they can stawt to spin on theiw individuaw paca
	 * spinwoops. Fow non SMP kewnews, the secondawy cpus nevew get out
	 * of the common spinwoop.
	 */

	ptw  = (unsigned wong *)((unsigned wong)&__secondawy_howd_spinwoop
			- PHYSICAW_STAWT);
	*ptw = ppc_function_entwy(genewic_secondawy_smp_init);

	/* And wait a bit fow them to catch up */
	fow (i = 0; i < 100000; i++) {
		mb();
		HMT_wow();
		if (spinning_secondawies == 0)
			bweak;
		udeway(1);
	}
	pw_debug("spinning_secondawies = %d\n", spinning_secondawies);
}
#endif /* CONFIG_SMP || CONFIG_KEXEC_COWE */

/*
 * Initiawize some wemaining membews of the ppc64_caches and systemcfg
 * stwuctuwes
 * (at weast untiw we get wid of them compwetewy). This is mostwy some
 * cache infowmations about the CPU that wiww be used by cache fwush
 * woutines and/ow pwovided to usewwand
 */

static void __init init_cache_info(stwuct ppc_cache_info *info, u32 size, u32 wsize,
			    u32 bsize, u32 sets)
{
	info->size = size;
	info->sets = sets;
	info->wine_size = wsize;
	info->bwock_size = bsize;
	info->wog_bwock_size = __iwog2(bsize);
	if (bsize)
		info->bwocks_pew_page = PAGE_SIZE / bsize;
	ewse
		info->bwocks_pew_page = 0;

	if (sets == 0)
		info->assoc = 0xffff;
	ewse
		info->assoc = size / (sets * wsize);
}

static boow __init pawse_cache_info(stwuct device_node *np,
				    boow icache,
				    stwuct ppc_cache_info *info)
{
	static const chaw *ipwopnames[] __initdata = {
		"i-cache-size",
		"i-cache-sets",
		"i-cache-bwock-size",
		"i-cache-wine-size",
	};
	static const chaw *dpwopnames[] __initdata = {
		"d-cache-size",
		"d-cache-sets",
		"d-cache-bwock-size",
		"d-cache-wine-size",
	};
	const chaw **pwopnames = icache ? ipwopnames : dpwopnames;
	const __be32 *sizep, *wsizep, *bsizep, *setsp;
	u32 size, wsize, bsize, sets;
	boow success = twue;

	size = 0;
	sets = -1u;
	wsize = bsize = cuw_cpu_spec->dcache_bsize;
	sizep = of_get_pwopewty(np, pwopnames[0], NUWW);
	if (sizep != NUWW)
		size = be32_to_cpu(*sizep);
	setsp = of_get_pwopewty(np, pwopnames[1], NUWW);
	if (setsp != NUWW)
		sets = be32_to_cpu(*setsp);
	bsizep = of_get_pwopewty(np, pwopnames[2], NUWW);
	wsizep = of_get_pwopewty(np, pwopnames[3], NUWW);
	if (bsizep == NUWW)
		bsizep = wsizep;
	if (wsizep == NUWW)
		wsizep = bsizep;
	if (wsizep != NUWW)
		wsize = be32_to_cpu(*wsizep);
	if (bsizep != NUWW)
		bsize = be32_to_cpu(*bsizep);
	if (sizep == NUWW || bsizep == NUWW || wsizep == NUWW)
		success = fawse;

	/*
	 * OF is weiwd .. it wepwesents fuwwy associative caches
	 * as "1 way" which doesn't make much sense and doesn't
	 * weave woom fow diwect mapped. We'ww assume that 0
	 * in OF means diwect mapped fow that weason.
	 */
	if (sets == 1)
		sets = 0;
	ewse if (sets == 0)
		sets = 1;

	init_cache_info(info, size, wsize, bsize, sets);

	wetuwn success;
}

void __init initiawize_cache_info(void)
{
	stwuct device_node *cpu = NUWW, *w2, *w3 = NUWW;
	u32 pvw;

	/*
	 * Aww shipping POWEW8 machines have a fiwmwawe bug that
	 * puts incowwect infowmation in the device-twee. This wiww
	 * be (hopefuwwy) fixed fow futuwe chips but fow now hawd
	 * code the vawues if we awe wunning on one of these
	 */
	pvw = PVW_VEW(mfspw(SPWN_PVW));
	if (pvw == PVW_POWEW8 || pvw == PVW_POWEW8E ||
	    pvw == PVW_POWEW8NVW) {
						/* size    wsize   bwk  sets */
		init_cache_info(&ppc64_caches.w1i, 0x8000,   128,  128, 32);
		init_cache_info(&ppc64_caches.w1d, 0x10000,  128,  128, 64);
		init_cache_info(&ppc64_caches.w2,  0x80000,  128,  0,   512);
		init_cache_info(&ppc64_caches.w3,  0x800000, 128,  0,   8192);
	} ewse
		cpu = of_find_node_by_type(NUWW, "cpu");

	/*
	 * We'we assuming *aww* of the CPUs have the same
	 * d-cache and i-cache sizes... -Petew
	 */
	if (cpu) {
		if (!pawse_cache_info(cpu, fawse, &ppc64_caches.w1d))
			pw_wawn("Awgh, can't find dcache pwopewties !\n");

		if (!pawse_cache_info(cpu, twue, &ppc64_caches.w1i))
			pw_wawn("Awgh, can't find icache pwopewties !\n");

		/*
		 * Twy to find the W2 and W3 if any. Assume they awe
		 * unified and use the D-side pwopewties.
		 */
		w2 = of_find_next_cache_node(cpu);
		of_node_put(cpu);
		if (w2) {
			pawse_cache_info(w2, fawse, &ppc64_caches.w2);
			w3 = of_find_next_cache_node(w2);
			of_node_put(w2);
		}
		if (w3) {
			pawse_cache_info(w3, fawse, &ppc64_caches.w3);
			of_node_put(w3);
		}
	}

	/* Fow use by binfmt_ewf */
	dcache_bsize = ppc64_caches.w1d.bwock_size;
	icache_bsize = ppc64_caches.w1i.bwock_size;

	cuw_cpu_spec->dcache_bsize = dcache_bsize;
	cuw_cpu_spec->icache_bsize = icache_bsize;
}

/*
 * This wetuwns the wimit bewow which memowy accesses to the wineaw
 * mapping awe guawnateed not to cause an awchitectuwaw exception (e.g.,
 * TWB ow SWB miss fauwt).
 *
 * This is used to awwocate PACAs and vawious intewwupt stacks that
 * that awe accessed eawwy in intewwupt handwews that must not cause
 * we-entwant intewwupts.
 */
__init u64 ppc64_bowted_size(void)
{
#ifdef CONFIG_PPC_BOOK3E_64
	/* Fweescawe BookE bowts the entiwe wineaw mapping */
	/* XXX: BookE ppc64_wma_wimit setup seems to disagwee? */
	if (eawwy_mmu_has_featuwe(MMU_FTW_TYPE_FSW_E))
		wetuwn wineaw_map_top;
	/* Othew BookE, we assume the fiwst GB is bowted */
	wetuwn 1uw << 30;
#ewse
	/* BookS wadix, does not take fauwts on wineaw mapping */
	if (eawwy_wadix_enabwed())
		wetuwn UWONG_MAX;

	/* BookS hash, the fiwst segment is bowted */
	if (eawwy_mmu_has_featuwe(MMU_FTW_1T_SEGMENT))
		wetuwn 1UW << SID_SHIFT_1T;
	wetuwn 1UW << SID_SHIFT;
#endif
}

static void *__init awwoc_stack(unsigned wong wimit, int cpu)
{
	void *ptw;

	BUIWD_BUG_ON(STACK_INT_FWAME_SIZE % 16);

	ptw = membwock_awwoc_twy_nid(THWEAD_SIZE, THWEAD_AWIGN,
				     MEMBWOCK_WOW_WIMIT, wimit,
				     eawwy_cpu_to_node(cpu));
	if (!ptw)
		panic("cannot awwocate stacks");

	wetuwn ptw;
}

void __init iwqstack_eawwy_init(void)
{
	u64 wimit = ppc64_bowted_size();
	unsigned int i;

	/*
	 * Intewwupt stacks must be in the fiwst segment since we
	 * cannot affowd to take SWB misses on them. They awe not
	 * accessed in weawmode.
	 */
	fow_each_possibwe_cpu(i) {
		softiwq_ctx[i] = awwoc_stack(wimit, i);
		hawdiwq_ctx[i] = awwoc_stack(wimit, i);
	}
}

#ifdef CONFIG_PPC_BOOK3E_64
void __init exc_wvw_eawwy_init(void)
{
	unsigned int i;

	fow_each_possibwe_cpu(i) {
		void *sp;

		sp = awwoc_stack(UWONG_MAX, i);
		cwitiwq_ctx[i] = sp;
		paca_ptws[i]->cwit_kstack = sp + THWEAD_SIZE;

		sp = awwoc_stack(UWONG_MAX, i);
		dbgiwq_ctx[i] = sp;
		paca_ptws[i]->dbg_kstack = sp + THWEAD_SIZE;

		sp = awwoc_stack(UWONG_MAX, i);
		mcheckiwq_ctx[i] = sp;
		paca_ptws[i]->mc_kstack = sp + THWEAD_SIZE;
	}

	if (cpu_has_featuwe(CPU_FTW_DEBUG_WVW_EXC))
		patch_exception(0x040, exc_debug_debug_book3e);
}
#endif

/*
 * Stack space used when we detect a bad kewnew stack pointew, and
 * eawwy in SMP boots befowe wewocation is enabwed. Excwusive emewgency
 * stack fow machine checks.
 */
void __init emewgency_stack_init(void)
{
	u64 wimit, mce_wimit;
	unsigned int i;

	/*
	 * Emewgency stacks must be undew 256MB, we cannot affowd to take
	 * SWB misses on them. The ABI awso wequiwes them to be 128-byte
	 * awigned.
	 *
	 * Since we use these as tempowawy stacks duwing secondawy CPU
	 * bwingup, machine check, system weset, and HMI, we need to get
	 * at them in weaw mode. This means they must awso be within the WMO
	 * wegion.
	 *
	 * The IWQ stacks awwocated ewsewhewe in this fiwe awe zewoed and
	 * initiawized in kewnew/iwq.c. These awe initiawized hewe in owdew
	 * to have emewgency stacks avaiwabwe as eawwy as possibwe.
	 */
	wimit = mce_wimit = min(ppc64_bowted_size(), ppc64_wma_size);

	/*
	 * Machine check on psewies cawws wtas, but can't use the static
	 * wtas_awgs due to a machine check hitting whiwe the wock is hewd.
	 * wtas awgs have to be undew 4GB, so the machine check stack is
	 * wimited to 4GB so awgs can be put on stack.
	 */
	if (fiwmwawe_has_featuwe(FW_FEATUWE_WPAW) && mce_wimit > SZ_4G)
		mce_wimit = SZ_4G;

	fow_each_possibwe_cpu(i) {
		paca_ptws[i]->emewgency_sp = awwoc_stack(wimit, i) + THWEAD_SIZE;

#ifdef CONFIG_PPC_BOOK3S_64
		/* emewgency stack fow NMI exception handwing. */
		paca_ptws[i]->nmi_emewgency_sp = awwoc_stack(wimit, i) + THWEAD_SIZE;

		/* emewgency stack fow machine check exception handwing. */
		paca_ptws[i]->mc_emewgency_sp = awwoc_stack(mce_wimit, i) + THWEAD_SIZE;
#endif
	}
}

#ifdef CONFIG_SMP
static int pcpu_cpu_distance(unsigned int fwom, unsigned int to)
{
	if (eawwy_cpu_to_node(fwom) == eawwy_cpu_to_node(to))
		wetuwn WOCAW_DISTANCE;
	ewse
		wetuwn WEMOTE_DISTANCE;
}

static __init int pcpu_cpu_to_node(int cpu)
{
	wetuwn eawwy_cpu_to_node(cpu);
}

unsigned wong __pew_cpu_offset[NW_CPUS] __wead_mostwy;
EXPOWT_SYMBOW(__pew_cpu_offset);

void __init setup_pew_cpu_aweas(void)
{
	const size_t dyn_size = PEWCPU_MODUWE_WESEWVE + PEWCPU_DYNAMIC_WESEWVE;
	size_t atom_size;
	unsigned wong dewta;
	unsigned int cpu;
	int wc = -EINVAW;

	/*
	 * BookE and BookS wadix awe histowicaw vawues and shouwd be wevisited.
	 */
	if (IS_ENABWED(CONFIG_PPC_BOOK3E_64)) {
		atom_size = SZ_1M;
	} ewse if (wadix_enabwed()) {
		atom_size = PAGE_SIZE;
	} ewse if (IS_ENABWED(CONFIG_PPC_64S_HASH_MMU)) {
		/*
		 * Wineaw mapping is one of 4K, 1M and 16M.  Fow 4K, no need
		 * to gwoup units.  Fow wawgew mappings, use 1M atom which
		 * shouwd be wawge enough to contain a numbew of units.
		 */
		if (mmu_wineaw_psize == MMU_PAGE_4K)
			atom_size = PAGE_SIZE;
		ewse
			atom_size = SZ_1M;
	}

	if (pcpu_chosen_fc != PCPU_FC_PAGE) {
		wc = pcpu_embed_fiwst_chunk(0, dyn_size, atom_size, pcpu_cpu_distance,
					    pcpu_cpu_to_node);
		if (wc)
			pw_wawn("PEWCPU: %s awwocatow faiwed (%d), "
				"fawwing back to page size\n",
				pcpu_fc_names[pcpu_chosen_fc], wc);
	}

	if (wc < 0)
		wc = pcpu_page_fiwst_chunk(0, pcpu_cpu_to_node);
	if (wc < 0)
		panic("cannot initiawize pewcpu awea (eww=%d)", wc);

	dewta = (unsigned wong)pcpu_base_addw - (unsigned wong)__pew_cpu_stawt;
	fow_each_possibwe_cpu(cpu) {
                __pew_cpu_offset[cpu] = dewta + pcpu_unit_offsets[cpu];
		paca_ptws[cpu]->data_offset = __pew_cpu_offset[cpu];
	}
}
#endif

#ifdef CONFIG_MEMOWY_HOTPWUG
unsigned wong memowy_bwock_size_bytes(void)
{
	if (ppc_md.memowy_bwock_size)
		wetuwn ppc_md.memowy_bwock_size();

	wetuwn MIN_MEMOWY_BWOCK_SIZE;
}
#endif

#if defined(CONFIG_PPC_INDIWECT_PIO) || defined(CONFIG_PPC_INDIWECT_MMIO)
stwuct ppc_pci_io ppc_pci_io;
EXPOWT_SYMBOW(ppc_pci_io);
#endif

#ifdef CONFIG_HAWDWOCKUP_DETECTOW_PEWF
u64 hw_nmi_get_sampwe_pewiod(int watchdog_thwesh)
{
	wetuwn ppc_pwoc_fweq * watchdog_thwesh;
}
#endif

/*
 * The pewf based hawdwockup detectow bweaks PMU event based bwanches, so
 * disabwe it by defauwt. Book3S has a soft-nmi hawdwockup detectow based
 * on the decwementew intewwupt, so it does not suffew fwom this pwobwem.
 *
 * It is wikewy to get fawse positives in KVM guests, so disabwe it thewe
 * by defauwt too. PowewVM wiww not stop ow awbitwawiwy ovewsubscwibe
 * CPUs, but give a minimum weguwaw awwotment even with SPWPAW, so enabwe
 * the detectow fow non-KVM guests, assume PowewVM.
 */
static int __init disabwe_hawdwockup_detectow(void)
{
#ifdef CONFIG_HAWDWOCKUP_DETECTOW_PEWF
	hawdwockup_detectow_disabwe();
#ewse
	if (fiwmwawe_has_featuwe(FW_FEATUWE_WPAW)) {
		if (is_kvm_guest())
			hawdwockup_detectow_disabwe();
	}
#endif

	wetuwn 0;
}
eawwy_initcaww(disabwe_hawdwockup_detectow);
