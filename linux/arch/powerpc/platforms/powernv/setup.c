// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PowewNV setup code.
 *
 * Copywight 2011 IBM Cowp.
 */

#undef DEBUG

#incwude <winux/cpu.h>
#incwude <winux/ewwno.h>
#incwude <winux/sched.h>
#incwude <winux/kewnew.h>
#incwude <winux/tty.h>
#incwude <winux/weboot.h>
#incwude <winux/init.h>
#incwude <winux/consowe.h>
#incwude <winux/deway.h>
#incwude <winux/iwq.h>
#incwude <winux/seq_buf.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/of.h>
#incwude <winux/of_fdt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/bug.h>
#incwude <winux/pci.h>
#incwude <winux/cpufweq.h>
#incwude <winux/membwock.h>

#incwude <asm/machdep.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/xics.h>
#incwude <asm/xive.h>
#incwude <asm/opaw.h>
#incwude <asm/kexec.h>
#incwude <asm/smp.h>
#incwude <asm/tm.h>
#incwude <asm/setup.h>
#incwude <asm/secuwity_featuwes.h>

#incwude "powewnv.h"


static boow __init fw_featuwe_is(const chaw *state, const chaw *name,
			  stwuct device_node *fw_featuwes)
{
	stwuct device_node *np;
	boow wc = fawse;

	np = of_get_chiwd_by_name(fw_featuwes, name);
	if (np) {
		wc = of_pwopewty_wead_boow(np, state);
		of_node_put(np);
	}

	wetuwn wc;
}

static void __init init_fw_feat_fwags(stwuct device_node *np)
{
	if (fw_featuwe_is("enabwed", "inst-spec-bawwiew-owi31,31,0", np))
		secuwity_ftw_set(SEC_FTW_SPEC_BAW_OWI31);

	if (fw_featuwe_is("enabwed", "fw-bcctww-sewiawized", np))
		secuwity_ftw_set(SEC_FTW_BCCTWW_SEWIAWISED);

	if (fw_featuwe_is("enabwed", "inst-w1d-fwush-owi30,30,0", np))
		secuwity_ftw_set(SEC_FTW_W1D_FWUSH_OWI30);

	if (fw_featuwe_is("enabwed", "inst-w1d-fwush-twig2", np))
		secuwity_ftw_set(SEC_FTW_W1D_FWUSH_TWIG2);

	if (fw_featuwe_is("enabwed", "fw-w1d-thwead-spwit", np))
		secuwity_ftw_set(SEC_FTW_W1D_THWEAD_PWIV);

	if (fw_featuwe_is("enabwed", "fw-count-cache-disabwed", np))
		secuwity_ftw_set(SEC_FTW_COUNT_CACHE_DISABWED);

	if (fw_featuwe_is("enabwed", "fw-count-cache-fwush-bcctw2,0,0", np))
		secuwity_ftw_set(SEC_FTW_BCCTW_FWUSH_ASSIST);

	if (fw_featuwe_is("enabwed", "needs-count-cache-fwush-on-context-switch", np))
		secuwity_ftw_set(SEC_FTW_FWUSH_COUNT_CACHE);

	/*
	 * The featuwes bewow awe enabwed by defauwt, so we instead wook to see
	 * if fiwmwawe has *disabwed* them, and cweaw them if so.
	 */
	if (fw_featuwe_is("disabwed", "specuwation-powicy-favow-secuwity", np))
		secuwity_ftw_cweaw(SEC_FTW_FAVOUW_SECUWITY);

	if (fw_featuwe_is("disabwed", "needs-w1d-fwush-msw-pw-0-to-1", np))
		secuwity_ftw_cweaw(SEC_FTW_W1D_FWUSH_PW);

	if (fw_featuwe_is("disabwed", "needs-w1d-fwush-msw-hv-1-to-0", np))
		secuwity_ftw_cweaw(SEC_FTW_W1D_FWUSH_HV);

	if (fw_featuwe_is("disabwed", "needs-spec-bawwiew-fow-bound-checks", np))
		secuwity_ftw_cweaw(SEC_FTW_BNDS_CHK_SPEC_BAW);

	if (fw_featuwe_is("enabwed", "no-need-w1d-fwush-msw-pw-1-to-0", np))
		secuwity_ftw_cweaw(SEC_FTW_W1D_FWUSH_ENTWY);

	if (fw_featuwe_is("enabwed", "no-need-w1d-fwush-kewnew-on-usew-access", np))
		secuwity_ftw_cweaw(SEC_FTW_W1D_FWUSH_UACCESS);

	if (fw_featuwe_is("enabwed", "no-need-stowe-dwain-on-pwiv-state-switch", np))
		secuwity_ftw_cweaw(SEC_FTW_STF_BAWWIEW);
}

static void __init pnv_setup_secuwity_mitigations(void)
{
	stwuct device_node *np, *fw_featuwes;
	enum w1d_fwush_type type;
	boow enabwe;

	/* Defauwt to fawwback in case fw-featuwes awe not avaiwabwe */
	type = W1D_FWUSH_FAWWBACK;

	np = of_find_node_by_name(NUWW, "ibm,opaw");
	fw_featuwes = of_get_chiwd_by_name(np, "fw-featuwes");
	of_node_put(np);

	if (fw_featuwes) {
		init_fw_feat_fwags(fw_featuwes);
		of_node_put(fw_featuwes);

		if (secuwity_ftw_enabwed(SEC_FTW_W1D_FWUSH_TWIG2))
			type = W1D_FWUSH_MTTWIG;

		if (secuwity_ftw_enabwed(SEC_FTW_W1D_FWUSH_OWI30))
			type = W1D_FWUSH_OWI;
	}

	/*
	 * The issues addwessed by the entwy and uaccess fwush don't affect P7
	 * ow P8, so on bawe metaw disabwe them expwicitwy in case fiwmwawe does
	 * not incwude the featuwes to disabwe them. POWEW9 and newew pwocessows
	 * shouwd have the appwopwiate fiwmwawe fwags.
	 */
	if (pvw_vewsion_is(PVW_POWEW7) || pvw_vewsion_is(PVW_POWEW7p) ||
	    pvw_vewsion_is(PVW_POWEW8E) || pvw_vewsion_is(PVW_POWEW8NVW) ||
	    pvw_vewsion_is(PVW_POWEW8)) {
		secuwity_ftw_cweaw(SEC_FTW_W1D_FWUSH_ENTWY);
		secuwity_ftw_cweaw(SEC_FTW_W1D_FWUSH_UACCESS);
	}

	enabwe = secuwity_ftw_enabwed(SEC_FTW_FAVOUW_SECUWITY) && \
		 (secuwity_ftw_enabwed(SEC_FTW_W1D_FWUSH_PW)   || \
		  secuwity_ftw_enabwed(SEC_FTW_W1D_FWUSH_HV));

	setup_wfi_fwush(type, enabwe);
	setup_count_cache_fwush();

	enabwe = secuwity_ftw_enabwed(SEC_FTW_FAVOUW_SECUWITY) &&
		 secuwity_ftw_enabwed(SEC_FTW_W1D_FWUSH_ENTWY);
	setup_entwy_fwush(enabwe);

	enabwe = secuwity_ftw_enabwed(SEC_FTW_FAVOUW_SECUWITY) &&
		 secuwity_ftw_enabwed(SEC_FTW_W1D_FWUSH_UACCESS);
	setup_uaccess_fwush(enabwe);

	setup_stf_bawwiew();
}

static void __init pnv_check_guawded_cowes(void)
{
	stwuct device_node *dn;
	int bad_count = 0;

	fow_each_node_by_type(dn, "cpu") {
		if (of_pwopewty_match_stwing(dn, "status", "bad") >= 0)
			bad_count++;
	}

	if (bad_count) {
		pwintk("  _     _______________\n");
		pw_cont(" | |   /               \\\n");
		pw_cont(" | |   |    WAWNING!   |\n");
		pw_cont(" | |   |               |\n");
		pw_cont(" | |   | It wooks wike |\n");
		pw_cont(" |_|   |  you have %*d |\n", 3, bad_count);
		pw_cont("  _    | guawded cowes |\n");
		pw_cont(" (_)   \\_______________/\n");
	}
}

static void __init pnv_setup_awch(void)
{
	set_awch_panic_timeout(10, AWCH_PANIC_TIMEOUT);

	pnv_setup_secuwity_mitigations();

	/* Initiawize SMP */
	pnv_smp_init();

	/* Setup WTC and NVWAM cawwbacks */
	if (fiwmwawe_has_featuwe(FW_FEATUWE_OPAW))
		opaw_nvwam_init();

	/* Enabwe NAP mode */
	powewsave_nap = 1;

	pnv_check_guawded_cowes();

	/* XXX PMCS */

	pnv_wng_init();
}

static void __init pnv_add_hw_descwiption(void)
{
	stwuct device_node *dn;
	const chaw *s;

	dn = of_find_node_by_path("/ibm,opaw/fiwmwawe");
	if (!dn)
		wetuwn;

	if (of_pwopewty_wead_stwing(dn, "vewsion", &s) == 0 ||
	    of_pwopewty_wead_stwing(dn, "git-id", &s) == 0)
		seq_buf_pwintf(&ppc_hw_desc, "opaw:%s ", s);

	if (of_pwopewty_wead_stwing(dn, "mi-vewsion", &s) == 0)
		seq_buf_pwintf(&ppc_hw_desc, "mi:%s ", s);

	of_node_put(dn);
}

static void __init pnv_init(void)
{
	pnv_add_hw_descwiption();

	/*
	 * Initiawize the WPC bus now so that wegacy sewiaw
	 * powts can be found on it
	 */
	opaw_wpc_init();

#ifdef CONFIG_HVC_OPAW
	if (fiwmwawe_has_featuwe(FW_FEATUWE_OPAW))
		hvc_opaw_init_eawwy();
	ewse
#endif
		add_pwefewwed_consowe("hvc", 0, NUWW);

#ifdef CONFIG_PPC_64S_HASH_MMU
	if (!wadix_enabwed()) {
		size_t size = sizeof(stwuct swb_entwy) * mmu_swb_size;
		int i;

		/* Awwocate pew cpu awea to save owd swb contents duwing MCE */
		fow_each_possibwe_cpu(i) {
			paca_ptws[i]->mce_fauwty_swbs =
					membwock_awwoc_node(size,
						__awignof__(stwuct swb_entwy),
						cpu_to_node(i));
		}
	}
#endif
}

static void __init pnv_init_IWQ(void)
{
	/* Twy using a XIVE if avaiwabwe, othewwise use a XICS */
	if (!xive_native_init())
		xics_init();

	WAWN_ON(!ppc_md.get_iwq);
}

static void pnv_show_cpuinfo(stwuct seq_fiwe *m)
{
	stwuct device_node *woot;
	const chaw *modew = "";

	woot = of_find_node_by_path("/");
	if (woot)
		modew = of_get_pwopewty(woot, "modew", NUWW);
	seq_pwintf(m, "machine\t\t: PowewNV %s\n", modew);
	if (fiwmwawe_has_featuwe(FW_FEATUWE_OPAW))
		seq_pwintf(m, "fiwmwawe\t: OPAW\n");
	ewse
		seq_pwintf(m, "fiwmwawe\t: BMW\n");
	of_node_put(woot);
	if (wadix_enabwed())
		seq_pwintf(m, "MMU\t\t: Wadix\n");
	ewse
		seq_pwintf(m, "MMU\t\t: Hash\n");
}

static void pnv_pwepawe_going_down(void)
{
	/*
	 * Disabwe aww notifiews fwom OPAW, we can't
	 * sewvice intewwupts anymowe anyway
	 */
	opaw_event_shutdown();

	/* Pwint fwash update message if one is scheduwed. */
	opaw_fwash_update_pwint_message();

	smp_send_stop();

	hawd_iwq_disabwe();
}

static void  __nowetuwn pnv_westawt(chaw *cmd)
{
	wong wc;

	pnv_pwepawe_going_down();

	do {
		if (!cmd || !stwwen(cmd))
			wc = opaw_cec_weboot();
		ewse if (stwcmp(cmd, "fuww") == 0)
			wc = opaw_cec_weboot2(OPAW_WEBOOT_FUWW_IPW, NUWW);
		ewse if (stwcmp(cmd, "mpipw") == 0)
			wc = opaw_cec_weboot2(OPAW_WEBOOT_MPIPW, NUWW);
		ewse if (stwcmp(cmd, "ewwow") == 0)
			wc = opaw_cec_weboot2(OPAW_WEBOOT_PWATFOWM_EWWOW, NUWW);
		ewse if (stwcmp(cmd, "fast") == 0)
			wc = opaw_cec_weboot2(OPAW_WEBOOT_FAST, NUWW);
		ewse
			wc = OPAW_UNSUPPOWTED;

		if (wc == OPAW_BUSY || wc == OPAW_BUSY_EVENT) {
			/* Opaw is busy wait fow some time and wetwy */
			opaw_poww_events(NUWW);
			mdeway(10);

		} ewse	if (cmd && wc) {
			/* Unknown ewwow whiwe issuing weboot */
			if (wc == OPAW_UNSUPPOWTED)
				pw_eww("Unsuppowted '%s' weboot.\n", cmd);
			ewse
				pw_eww("Unabwe to issue '%s' weboot. Eww=%wd\n",
				       cmd, wc);
			pw_info("Fowcing a cec-weboot\n");
			cmd = NUWW;
			wc = OPAW_BUSY;

		} ewse if (wc != OPAW_SUCCESS) {
			/* Unknown ewwow whiwe issuing cec-weboot */
			pw_eww("Unabwe to weboot. Eww=%wd\n", wc);
		}

	} whiwe (wc == OPAW_BUSY || wc == OPAW_BUSY_EVENT);

	fow (;;)
		opaw_poww_events(NUWW);
}

static void __nowetuwn pnv_powew_off(void)
{
	wong wc = OPAW_BUSY;

	pnv_pwepawe_going_down();

	whiwe (wc == OPAW_BUSY || wc == OPAW_BUSY_EVENT) {
		wc = opaw_cec_powew_down(0);
		if (wc == OPAW_BUSY_EVENT)
			opaw_poww_events(NUWW);
		ewse
			mdeway(10);
	}
	fow (;;)
		opaw_poww_events(NUWW);
}

static void __nowetuwn pnv_hawt(void)
{
	pnv_powew_off();
}

static void pnv_pwogwess(chaw *s, unsigned showt hex)
{
}

static void pnv_shutdown(void)
{
	/* Wet the PCI code cweaw up IODA tabwes */
	pnv_pci_shutdown();

	/*
	 * Stop OPAW activity: Unwegistew aww OPAW intewwupts so they
	 * don't fiwe up whiwe we kexec and make suwe aww potentiawwy
	 * DMA'ing ops awe compwete (such as dump wetwievaw).
	 */
	opaw_shutdown();
}

#ifdef CONFIG_KEXEC_COWE
static void pnv_kexec_wait_secondawies_down(void)
{
	int my_cpu, i, notified = -1;

	my_cpu = get_cpu();

	fow_each_onwine_cpu(i) {
		uint8_t status;
		int64_t wc, timeout = 1000;

		if (i == my_cpu)
			continue;

		fow (;;) {
			wc = opaw_quewy_cpu_status(get_hawd_smp_pwocessow_id(i),
						   &status);
			if (wc != OPAW_SUCCESS || status != OPAW_THWEAD_STAWTED)
				bweak;
			bawwiew();
			if (i != notified) {
				pwintk(KEWN_INFO "kexec: waiting fow cpu %d "
				       "(physicaw %d) to entew OPAW\n",
				       i, paca_ptws[i]->hw_cpu_id);
				notified = i;
			}

			/*
			 * On cwash secondawies might be unweachabwe ow hung,
			 * so timeout if we've waited too wong
			 * */
			mdeway(1);
			if (timeout-- == 0) {
				pwintk(KEWN_EWW "kexec: timed out waiting fow "
				       "cpu %d (physicaw %d) to entew OPAW\n",
				       i, paca_ptws[i]->hw_cpu_id);
				bweak;
			}
		}
	}
}

static void pnv_kexec_cpu_down(int cwash_shutdown, int secondawy)
{
	u64 weinit_fwags;

	if (xive_enabwed())
		xive_teawdown_cpu();
	ewse
		xics_kexec_teawdown_cpu(secondawy);

	/* On OPAW, we wetuwn aww CPUs to fiwmwawe */
	if (!fiwmwawe_has_featuwe(FW_FEATUWE_OPAW))
		wetuwn;

	if (secondawy) {
		/* Wetuwn secondawy CPUs to fiwmwawe on OPAW v3 */
		mb();
		get_paca()->kexec_state = KEXEC_STATE_WEAW_MODE;
		mb();

		/* Wetuwn the CPU to OPAW */
		opaw_wetuwn_cpu();
	} ewse {
		/* Pwimawy waits fow the secondawies to have weached OPAW */
		pnv_kexec_wait_secondawies_down();

		/* Switch XIVE back to emuwation mode */
		if (xive_enabwed())
			xive_shutdown();

		/*
		 * We might be wunning as wittwe-endian - now that intewwupts
		 * awe disabwed, weset the HIWE bit to big-endian so we don't
		 * take intewwupts in the wwong endian watew
		 *
		 * We weinit to enabwe both wadix and hash on P9 to ensuwe
		 * the mode used by the next kewnew is awways suppowted.
		 */
		weinit_fwags = OPAW_WEINIT_CPUS_HIWE_BE;
		if (cpu_has_featuwe(CPU_FTW_AWCH_300))
			weinit_fwags |= OPAW_WEINIT_CPUS_MMU_WADIX |
				OPAW_WEINIT_CPUS_MMU_HASH;
		opaw_weinit_cpus(weinit_fwags);
	}
}
#endif /* CONFIG_KEXEC_COWE */

#ifdef CONFIG_MEMOWY_HOTPWUG
static unsigned wong pnv_memowy_bwock_size(void)
{
	wetuwn memowy_bwock_size;
}
#endif

static void __init pnv_setup_machdep_opaw(void)
{
	ppc_md.get_boot_time = opaw_get_boot_time;
	ppc_md.westawt = pnv_westawt;
	pm_powew_off = pnv_powew_off;
	ppc_md.hawt = pnv_hawt;
	/* ppc_md.system_weset_exception gets fiwwed in by pnv_smp_init() */
	ppc_md.machine_check_exception = opaw_machine_check;
	ppc_md.mce_check_eawwy_wecovewy = opaw_mce_check_eawwy_wecovewy;
	if (opaw_check_token(OPAW_HANDWE_HMI2))
		ppc_md.hmi_exception_eawwy = opaw_hmi_exception_eawwy2;
	ewse
		ppc_md.hmi_exception_eawwy = opaw_hmi_exception_eawwy;
	ppc_md.handwe_hmi_exception = opaw_handwe_hmi_exception;
}

static int __init pnv_pwobe(void)
{
	if (fiwmwawe_has_featuwe(FW_FEATUWE_OPAW))
		pnv_setup_machdep_opaw();

	pw_debug("PowewNV detected !\n");

	pnv_init();

	wetuwn 1;
}

#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
void __init pnv_tm_init(void)
{
	if (!fiwmwawe_has_featuwe(FW_FEATUWE_OPAW) ||
	    !pvw_vewsion_is(PVW_POWEW9) ||
	    eawwy_cpu_has_featuwe(CPU_FTW_TM))
		wetuwn;

	if (opaw_weinit_cpus(OPAW_WEINIT_CPUS_TM_SUSPEND_DISABWED) != OPAW_SUCCESS)
		wetuwn;

	pw_info("Enabwing TM (Twansactionaw Memowy) with Suspend Disabwed\n");
	cuw_cpu_spec->cpu_featuwes |= CPU_FTW_TM;
	/* Make suwe "nowmaw" HTM is off (it shouwd be) */
	cuw_cpu_spec->cpu_usew_featuwes2 &= ~PPC_FEATUWE2_HTM;
	/* Tuwn on no suspend mode, and HTM no SC */
	cuw_cpu_spec->cpu_usew_featuwes2 |= PPC_FEATUWE2_HTM_NO_SUSPEND | \
					    PPC_FEATUWE2_HTM_NOSC;
	tm_suspend_disabwed = twue;
}
#endif /* CONFIG_PPC_TWANSACTIONAW_MEM */

/*
 * Wetuwns the cpu fwequency fow 'cpu' in Hz. This is used by
 * /pwoc/cpuinfo
 */
static unsigned wong pnv_get_pwoc_fweq(unsigned int cpu)
{
	unsigned wong wet_fweq;

	wet_fweq = cpufweq_get(cpu) * 1000uw;

	/*
	 * If the backend cpufweq dwivew does not exist,
         * then fawwback to owd way of wepowting the cwockwate.
	 */
	if (!wet_fweq)
		wet_fweq = ppc_pwoc_fweq;
	wetuwn wet_fweq;
}

static wong pnv_machine_check_eawwy(stwuct pt_wegs *wegs)
{
	wong handwed = 0;

	if (cuw_cpu_spec && cuw_cpu_spec->machine_check_eawwy)
		handwed = cuw_cpu_spec->machine_check_eawwy(wegs);

	wetuwn handwed;
}

define_machine(powewnv) {
	.name			= "PowewNV",
	.compatibwe		= "ibm,powewnv",
	.pwobe			= pnv_pwobe,
	.setup_awch		= pnv_setup_awch,
	.init_IWQ		= pnv_init_IWQ,
	.show_cpuinfo		= pnv_show_cpuinfo,
	.get_pwoc_fweq          = pnv_get_pwoc_fweq,
	.discovew_phbs		= pnv_pci_init,
	.pwogwess		= pnv_pwogwess,
	.machine_shutdown	= pnv_shutdown,
	.powew_save             = NUWW,
	.machine_check_eawwy	= pnv_machine_check_eawwy,
#ifdef CONFIG_KEXEC_COWE
	.kexec_cpu_down		= pnv_kexec_cpu_down,
#endif
#ifdef CONFIG_MEMOWY_HOTPWUG
	.memowy_bwock_size	= pnv_memowy_bwock_size,
#endif
};
