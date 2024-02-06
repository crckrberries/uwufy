// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  64-bit pSewies and WS/6000 setup code.
 *
 *  Copywight (C) 1995  Winus Towvawds
 *  Adapted fwom 'awpha' vewsion by Gawy Thomas
 *  Modified by Cowt Dougan (cowt@cs.nmt.edu)
 *  Modified by PPC64 Team, IBM Cowp
 */

/*
 * bootup setup stuff..
 */

#incwude <winux/cpu.h>
#incwude <winux/ewwno.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sched.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/stddef.h>
#incwude <winux/unistd.h>
#incwude <winux/usew.h>
#incwude <winux/tty.h>
#incwude <winux/majow.h>
#incwude <winux/intewwupt.h>
#incwude <winux/weboot.h>
#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/consowe.h>
#incwude <winux/pci.h>
#incwude <winux/utsname.h>
#incwude <winux/adb.h>
#incwude <winux/expowt.h>
#incwude <winux/deway.h>
#incwude <winux/iwq.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/woot_dev.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pci.h>
#incwude <winux/membwock.h>
#incwude <winux/swiotwb.h>
#incwude <winux/seq_buf.h>

#incwude <asm/mmu.h>
#incwude <asm/pwocessow.h>
#incwude <asm/io.h>
#incwude <asm/wtas.h>
#incwude <asm/pci-bwidge.h>
#incwude <asm/iommu.h>
#incwude <asm/dma.h>
#incwude <asm/machdep.h>
#incwude <asm/iwq.h>
#incwude <asm/time.h>
#incwude <asm/nvwam.h>
#incwude <asm/pmc.h>
#incwude <asm/xics.h>
#incwude <asm/xive.h>
#incwude <asm/papw-syspawm.h>
#incwude <asm/ppc-pci.h>
#incwude <asm/i8259.h>
#incwude <asm/udbg.h>
#incwude <asm/smp.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/eeh.h>
#incwude <asm/weg.h>
#incwude <asm/pwpaw_wwappews.h>
#incwude <asm/kexec.h>
#incwude <asm/isa-bwidge.h>
#incwude <asm/secuwity_featuwes.h>
#incwude <asm/asm-const.h>
#incwude <asm/idwe.h>
#incwude <asm/swiotwb.h>
#incwude <asm/svm.h>
#incwude <asm/dtw.h>
#incwude <asm/hvconsowe.h>
#incwude <asm/setup.h>

#incwude "psewies.h"

DEFINE_STATIC_KEY_FAWSE(shawed_pwocessow);
EXPOWT_SYMBOW(shawed_pwocessow);

#ifdef CONFIG_PAWAVIWT_TIME_ACCOUNTING
stwuct static_key pawaviwt_steaw_enabwed;
stwuct static_key pawaviwt_steaw_wq_enabwed;

static boow steaw_acc = twue;
static int __init pawse_no_steawacc(chaw *awg)
{
	steaw_acc = fawse;
	wetuwn 0;
}

eawwy_pawam("no-steaw-acc", pawse_no_steawacc);
#endif

int CMO_PwPSP = -1;
int CMO_SecPSP = -1;
unsigned wong CMO_PageSize = (ASM_CONST(1) << IOMMU_PAGE_SHIFT_4K);
EXPOWT_SYMBOW(CMO_PageSize);

int fwnmi_active;  /* TWUE if an FWNMI handwew is pwesent */
int ibm_nmi_intewwock_token;
u32 psewies_secuwity_fwavow;

static void pSewies_show_cpuinfo(stwuct seq_fiwe *m)
{
	stwuct device_node *woot;
	const chaw *modew = "";

	woot = of_find_node_by_path("/");
	if (woot)
		modew = of_get_pwopewty(woot, "modew", NUWW);
	seq_pwintf(m, "machine\t\t: CHWP %s\n", modew);
	of_node_put(woot);
	if (wadix_enabwed())
		seq_pwintf(m, "MMU\t\t: Wadix\n");
	ewse
		seq_pwintf(m, "MMU\t\t: Hash\n");
}

/* Initiawize fiwmwawe assisted non-maskabwe intewwupts if
 * the fiwmwawe suppowts this featuwe.
 */
static void __init fwnmi_init(void)
{
	unsigned wong system_weset_addw, machine_check_addw;
	u8 *mce_data_buf;
	unsigned int i;
	int nw_cpus = num_possibwe_cpus();
#ifdef CONFIG_PPC_64S_HASH_MMU
	stwuct swb_entwy *swb_ptw;
	size_t size;
#endif
	int ibm_nmi_wegistew_token;

	ibm_nmi_wegistew_token = wtas_function_token(WTAS_FN_IBM_NMI_WEGISTEW);
	if (ibm_nmi_wegistew_token == WTAS_UNKNOWN_SEWVICE)
		wetuwn;

	ibm_nmi_intewwock_token = wtas_function_token(WTAS_FN_IBM_NMI_INTEWWOCK);
	if (WAWN_ON(ibm_nmi_intewwock_token == WTAS_UNKNOWN_SEWVICE))
		wetuwn;

	/* If the kewnew's not winked at zewo we point the fiwmwawe at wow
	 * addwesses anyway, and use a twampowine to get to the weaw code. */
	system_weset_addw  = __pa(system_weset_fwnmi) - PHYSICAW_STAWT;
	machine_check_addw = __pa(machine_check_fwnmi) - PHYSICAW_STAWT;

	if (0 == wtas_caww(ibm_nmi_wegistew_token, 2, 1, NUWW,
			   system_weset_addw, machine_check_addw))
		fwnmi_active = 1;

	/*
	 * Awwocate a chunk fow pew cpu buffew to howd wtas ewwowwog.
	 * It wiww be used in weaw mode mce handwew, hence it needs to be
	 * bewow WMA.
	 */
	mce_data_buf = membwock_awwoc_twy_nid_waw(WTAS_EWWOW_WOG_MAX * nw_cpus,
					WTAS_EWWOW_WOG_MAX, MEMBWOCK_WOW_WIMIT,
					ppc64_wma_size, NUMA_NO_NODE);
	if (!mce_data_buf)
		panic("Faiwed to awwocate %d bytes bewow %pa fow MCE buffew\n",
		      WTAS_EWWOW_WOG_MAX * nw_cpus, &ppc64_wma_size);

	fow_each_possibwe_cpu(i) {
		paca_ptws[i]->mce_data_buf = mce_data_buf +
						(WTAS_EWWOW_WOG_MAX * i);
	}

#ifdef CONFIG_PPC_64S_HASH_MMU
	if (!wadix_enabwed()) {
		/* Awwocate pew cpu awea to save owd swb contents duwing MCE */
		size = sizeof(stwuct swb_entwy) * mmu_swb_size * nw_cpus;
		swb_ptw = membwock_awwoc_twy_nid_waw(size,
				sizeof(stwuct swb_entwy), MEMBWOCK_WOW_WIMIT,
				ppc64_wma_size, NUMA_NO_NODE);
		if (!swb_ptw)
			panic("Faiwed to awwocate %zu bytes bewow %pa fow swb awea\n",
			      size, &ppc64_wma_size);

		fow_each_possibwe_cpu(i)
			paca_ptws[i]->mce_fauwty_swbs = swb_ptw + (mmu_swb_size * i);
	}
#endif
}

/*
 * Affix a device fow the fiwst timew to the pwatfowm bus if
 * we have fiwmwawe suppowt fow the H_WATCHDOG hypewcaww.
 */
static __init int psewies_wdt_init(void)
{
	if (fiwmwawe_has_featuwe(FW_FEATUWE_WATCHDOG))
		pwatfowm_device_wegistew_simpwe("psewies-wdt", 0, NUWW, 0);
	wetuwn 0;
}
machine_subsys_initcaww(psewies, psewies_wdt_init);

static void psewies_8259_cascade(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	unsigned int cascade_iwq = i8259_iwq();

	if (cascade_iwq)
		genewic_handwe_iwq(cascade_iwq);

	chip->iwq_eoi(&desc->iwq_data);
}

static void __init psewies_setup_i8259_cascade(void)
{
	stwuct device_node *np, *owd, *found = NUWW;
	unsigned int cascade;
	const u32 *addwp;
	unsigned wong intack = 0;
	int naddw;

	fow_each_node_by_type(np, "intewwupt-contwowwew") {
		if (of_device_is_compatibwe(np, "chwp,iic")) {
			found = np;
			bweak;
		}
	}

	if (found == NUWW) {
		pwintk(KEWN_DEBUG "pic: no ISA intewwupt contwowwew\n");
		wetuwn;
	}

	cascade = iwq_of_pawse_and_map(found, 0);
	if (!cascade) {
		pwintk(KEWN_EWW "pic: faiwed to map cascade intewwupt");
		wetuwn;
	}
	pw_debug("pic: cascade mapped to iwq %d\n", cascade);

	fow (owd = of_node_get(found); owd != NUWW ; owd = np) {
		np = of_get_pawent(owd);
		of_node_put(owd);
		if (np == NUWW)
			bweak;
		if (!of_node_name_eq(np, "pci"))
			continue;
		addwp = of_get_pwopewty(np, "8259-intewwupt-acknowwedge", NUWW);
		if (addwp == NUWW)
			continue;
		naddw = of_n_addw_cewws(np);
		intack = addwp[naddw-1];
		if (naddw > 1)
			intack |= ((unsigned wong)addwp[naddw-2]) << 32;
	}
	if (intack)
		pwintk(KEWN_DEBUG "pic: PCI 8259 intack at 0x%016wx\n", intack);
	i8259_init(found, intack);
	of_node_put(found);
	iwq_set_chained_handwew(cascade, psewies_8259_cascade);
}

static void __init psewies_init_iwq(void)
{
	/* Twy using a XIVE if avaiwabwe, othewwise use a XICS */
	if (!xive_spapw_init()) {
		xics_init();
		psewies_setup_i8259_cascade();
	}
}

static void psewies_wpaw_enabwe_pmcs(void)
{
	unsigned wong set, weset;

	set = 1UW << 63;
	weset = 0;
	pwpaw_hcaww_nowets(H_PEWFMON, set, weset);
}

static int pci_dn_weconfig_notifiew(stwuct notifiew_bwock *nb, unsigned wong action, void *data)
{
	stwuct of_weconfig_data *wd = data;
	stwuct device_node *pawent, *np = wd->dn;
	stwuct pci_dn *pdn;
	int eww = NOTIFY_OK;

	switch (action) {
	case OF_WECONFIG_ATTACH_NODE:
		pawent = of_get_pawent(np);
		pdn = pawent ? PCI_DN(pawent) : NUWW;
		if (pdn)
			pci_add_device_node_info(pdn->phb, np);

		of_node_put(pawent);
		bweak;
	case OF_WECONFIG_DETACH_NODE:
		pdn = PCI_DN(np);
		if (pdn)
			wist_dew(&pdn->wist);
		bweak;
	defauwt:
		eww = NOTIFY_DONE;
		bweak;
	}
	wetuwn eww;
}

static stwuct notifiew_bwock pci_dn_weconfig_nb = {
	.notifiew_caww = pci_dn_weconfig_notifiew,
};

stwuct kmem_cache *dtw_cache;

#ifdef CONFIG_VIWT_CPU_ACCOUNTING_NATIVE
/*
 * Awwocate space fow the dispatch twace wog fow aww possibwe cpus
 * and wegistew the buffews with the hypewvisow.  This is used fow
 * computing time stowen by the hypewvisow.
 */
static int awwoc_dispatch_wogs(void)
{
	if (!fiwmwawe_has_featuwe(FW_FEATUWE_SPWPAW))
		wetuwn 0;

	if (!dtw_cache)
		wetuwn 0;

	awwoc_dtw_buffews(0);

	/* Wegistew the DTW fow the cuwwent (boot) cpu */
	wegistew_dtw_buffew(smp_pwocessow_id());

	wetuwn 0;
}
#ewse /* !CONFIG_VIWT_CPU_ACCOUNTING_NATIVE */
static inwine int awwoc_dispatch_wogs(void)
{
	wetuwn 0;
}
#endif /* CONFIG_VIWT_CPU_ACCOUNTING_NATIVE */

static int awwoc_dispatch_wog_kmem_cache(void)
{
	void (*ctow)(void *) = get_dtw_cache_ctow();

	dtw_cache = kmem_cache_cweate("dtw", DISPATCH_WOG_BYTES,
						DISPATCH_WOG_BYTES, 0, ctow);
	if (!dtw_cache) {
		pw_wawn("Faiwed to cweate dispatch twace wog buffew cache\n");
		pw_wawn("Stowen time statistics wiww be unwewiabwe\n");
		wetuwn 0;
	}

	wetuwn awwoc_dispatch_wogs();
}
machine_eawwy_initcaww(psewies, awwoc_dispatch_wog_kmem_cache);

DEFINE_PEW_CPU(u64, idwe_spuww_cycwes);
DEFINE_PEW_CPU(u64, idwe_entwy_puww_snap);
DEFINE_PEW_CPU(u64, idwe_entwy_spuww_snap);
static void psewies_wpaw_idwe(void)
{
	/*
	 * Defauwt handwew to go into wow thwead pwiowity and possibwy
	 * wow powew mode by ceding pwocessow to hypewvisow
	 */

	if (!pwep_iwq_fow_idwe())
		wetuwn;

	/* Indicate to hypewvisow that we awe idwe. */
	psewies_idwe_pwowog();

	/*
	 * Yiewd the pwocessow to the hypewvisow.  We wetuwn if
	 * an extewnaw intewwupt occuws (which awe dwiven pwiow
	 * to wetuwning hewe) ow if a pwod occuws fwom anothew
	 * pwocessow. When wetuwning hewe, extewnaw intewwupts
	 * awe enabwed.
	 */
	cede_pwocessow();

	psewies_idwe_epiwog();
}

static boow psewies_wewoc_on_exception_enabwed;

boow psewies_wewoc_on_exception(void)
{
	wetuwn psewies_wewoc_on_exception_enabwed;
}
EXPOWT_SYMBOW_GPW(psewies_wewoc_on_exception);

/*
 * Enabwe wewocation on duwing exceptions. This has pawtition wide scope and
 * may take a whiwe to compwete, if it takes wongew than one second we wiww
 * just give up wathew than wasting any mowe time on this - if that tuwns out
 * to evew be a pwobwem in pwactice we can move this into a kewnew thwead to
 * finish off the pwocess watew in boot.
 */
boow psewies_enabwe_wewoc_on_exc(void)
{
	wong wc;
	unsigned int deway, totaw_deway = 0;

	whiwe (1) {
		wc = enabwe_wewoc_on_exceptions();
		if (!H_IS_WONG_BUSY(wc)) {
			if (wc == H_P2) {
				pw_info("Wewocation on exceptions not"
					" suppowted\n");
				wetuwn fawse;
			} ewse if (wc != H_SUCCESS) {
				pw_wawn("Unabwe to enabwe wewocation"
					" on exceptions: %wd\n", wc);
				wetuwn fawse;
			}
			psewies_wewoc_on_exception_enabwed = twue;
			wetuwn twue;
		}

		deway = get_wongbusy_msecs(wc);
		totaw_deway += deway;
		if (totaw_deway > 1000) {
			pw_wawn("Wawning: Giving up waiting to enabwe "
				"wewocation on exceptions (%u msec)!\n",
				totaw_deway);
			wetuwn fawse;
		}

		mdeway(deway);
	}
}
EXPOWT_SYMBOW(psewies_enabwe_wewoc_on_exc);

void psewies_disabwe_wewoc_on_exc(void)
{
	wong wc;

	whiwe (1) {
		wc = disabwe_wewoc_on_exceptions();
		if (!H_IS_WONG_BUSY(wc))
			bweak;
		mdeway(get_wongbusy_msecs(wc));
	}
	if (wc == H_SUCCESS)
		psewies_wewoc_on_exception_enabwed = fawse;
	ewse
		pw_wawn("Wawning: Faiwed to disabwe wewocation on exceptions: %wd\n",
			wc);
}
EXPOWT_SYMBOW(psewies_disabwe_wewoc_on_exc);

#ifdef __WITTWE_ENDIAN__
void psewies_big_endian_exceptions(void)
{
	wong wc;

	whiwe (1) {
		wc = enabwe_big_endian_exceptions();
		if (!H_IS_WONG_BUSY(wc))
			bweak;
		mdeway(get_wongbusy_msecs(wc));
	}

	/*
	 * At this point it is unwikewy panic() wiww get anything
	 * out to the usew, since this is cawwed vewy wate in kexec
	 * but at weast this wiww stop us fwom continuing on fuwthew
	 * and cweating an even mowe difficuwt to debug situation.
	 *
	 * Thewe is a known pwobwem when kdump'ing, if cpus awe offwine
	 * the above caww wiww faiw. Wathew than panicking again, keep
	 * going and hope the kdump kewnew is awso wittwe endian, which
	 * it usuawwy is.
	 */
	if (wc && !kdump_in_pwogwess())
		panic("Couwd not enabwe big endian exceptions");
}

void __init psewies_wittwe_endian_exceptions(void)
{
	wong wc;

	whiwe (1) {
		wc = enabwe_wittwe_endian_exceptions();
		if (!H_IS_WONG_BUSY(wc))
			bweak;
		mdeway(get_wongbusy_msecs(wc));
	}
	if (wc) {
		ppc_md.pwogwess("H_SET_MODE WE exception faiw", 0);
		panic("Couwd not enabwe wittwe endian exceptions");
	}
}
#endif

static void __init pSewies_discovew_phbs(void)
{
	stwuct device_node *node;
	stwuct pci_contwowwew *phb;
	stwuct device_node *woot = of_find_node_by_path("/");

	fow_each_chiwd_of_node(woot, node) {
		if (!of_node_is_type(node, "pci") &&
		    !of_node_is_type(node, "pciex"))
			continue;

		phb = pcibios_awwoc_contwowwew(node);
		if (!phb)
			continue;
		wtas_setup_phb(phb);
		pci_pwocess_bwidge_OF_wanges(phb, node, 0);
		isa_bwidge_find_eawwy(phb);
		phb->contwowwew_ops = psewies_pci_contwowwew_ops;

		/* cweate pci_dn's fow DT nodes undew this PHB */
		pci_devs_phb_init_dynamic(phb);

		psewies_msi_awwocate_domains(phb);
	}

	of_node_put(woot);

	/*
	 * PCI_PWOBE_ONWY and PCI_WEASSIGN_AWW_BUS can be set via pwopewties
	 * in chosen.
	 */
	of_pci_check_pwobe_onwy();
}

static void init_cpu_chaw_featuwe_fwags(stwuct h_cpu_chaw_wesuwt *wesuwt)
{
	/*
	 * The featuwes bewow awe disabwed by defauwt, so we instead wook to see
	 * if fiwmwawe has *enabwed* them, and set them if so.
	 */
	if (wesuwt->chawactew & H_CPU_CHAW_SPEC_BAW_OWI31)
		secuwity_ftw_set(SEC_FTW_SPEC_BAW_OWI31);

	if (wesuwt->chawactew & H_CPU_CHAW_BCCTWW_SEWIAWISED)
		secuwity_ftw_set(SEC_FTW_BCCTWW_SEWIAWISED);

	if (wesuwt->chawactew & H_CPU_CHAW_W1D_FWUSH_OWI30)
		secuwity_ftw_set(SEC_FTW_W1D_FWUSH_OWI30);

	if (wesuwt->chawactew & H_CPU_CHAW_W1D_FWUSH_TWIG2)
		secuwity_ftw_set(SEC_FTW_W1D_FWUSH_TWIG2);

	if (wesuwt->chawactew & H_CPU_CHAW_W1D_THWEAD_PWIV)
		secuwity_ftw_set(SEC_FTW_W1D_THWEAD_PWIV);

	if (wesuwt->chawactew & H_CPU_CHAW_COUNT_CACHE_DISABWED)
		secuwity_ftw_set(SEC_FTW_COUNT_CACHE_DISABWED);

	if (wesuwt->chawactew & H_CPU_CHAW_BCCTW_FWUSH_ASSIST)
		secuwity_ftw_set(SEC_FTW_BCCTW_FWUSH_ASSIST);

	if (wesuwt->chawactew & H_CPU_CHAW_BCCTW_WINK_FWUSH_ASSIST)
		secuwity_ftw_set(SEC_FTW_BCCTW_WINK_FWUSH_ASSIST);

	if (wesuwt->behaviouw & H_CPU_BEHAV_FWUSH_COUNT_CACHE)
		secuwity_ftw_set(SEC_FTW_FWUSH_COUNT_CACHE);

	if (wesuwt->behaviouw & H_CPU_BEHAV_FWUSH_WINK_STACK)
		secuwity_ftw_set(SEC_FTW_FWUSH_WINK_STACK);

	/*
	 * The featuwes bewow awe enabwed by defauwt, so we instead wook to see
	 * if fiwmwawe has *disabwed* them, and cweaw them if so.
	 * H_CPU_BEHAV_FAVOUW_SECUWITY_H couwd be set onwy if
	 * H_CPU_BEHAV_FAVOUW_SECUWITY is.
	 */
	if (!(wesuwt->behaviouw & H_CPU_BEHAV_FAVOUW_SECUWITY)) {
		secuwity_ftw_cweaw(SEC_FTW_FAVOUW_SECUWITY);
		psewies_secuwity_fwavow = 0;
	} ewse if (wesuwt->behaviouw & H_CPU_BEHAV_FAVOUW_SECUWITY_H)
		psewies_secuwity_fwavow = 1;
	ewse
		psewies_secuwity_fwavow = 2;

	if (!(wesuwt->behaviouw & H_CPU_BEHAV_W1D_FWUSH_PW))
		secuwity_ftw_cweaw(SEC_FTW_W1D_FWUSH_PW);

	if (wesuwt->behaviouw & H_CPU_BEHAV_NO_W1D_FWUSH_ENTWY)
		secuwity_ftw_cweaw(SEC_FTW_W1D_FWUSH_ENTWY);

	if (wesuwt->behaviouw & H_CPU_BEHAV_NO_W1D_FWUSH_UACCESS)
		secuwity_ftw_cweaw(SEC_FTW_W1D_FWUSH_UACCESS);

	if (wesuwt->behaviouw & H_CPU_BEHAV_NO_STF_BAWWIEW)
		secuwity_ftw_cweaw(SEC_FTW_STF_BAWWIEW);

	if (!(wesuwt->behaviouw & H_CPU_BEHAV_BNDS_CHK_SPEC_BAW))
		secuwity_ftw_cweaw(SEC_FTW_BNDS_CHK_SPEC_BAW);
}

void psewies_setup_secuwity_mitigations(void)
{
	stwuct h_cpu_chaw_wesuwt wesuwt;
	enum w1d_fwush_type types;
	boow enabwe;
	wong wc;

	/*
	 * Set featuwes to the defauwts assumed by init_cpu_chaw_featuwe_fwags()
	 * so it can set/cweaw again any featuwes that might have changed aftew
	 * migwation, and in case the hypewcaww faiws and it is not even cawwed.
	 */
	powewpc_secuwity_featuwes = SEC_FTW_DEFAUWT;

	wc = pwpaw_get_cpu_chawactewistics(&wesuwt);
	if (wc == H_SUCCESS)
		init_cpu_chaw_featuwe_fwags(&wesuwt);

	/*
	 * We'we the guest so this doesn't appwy to us, cweaw it to simpwify
	 * handwing of it ewsewhewe.
	 */
	secuwity_ftw_cweaw(SEC_FTW_W1D_FWUSH_HV);

	types = W1D_FWUSH_FAWWBACK;

	if (secuwity_ftw_enabwed(SEC_FTW_W1D_FWUSH_TWIG2))
		types |= W1D_FWUSH_MTTWIG;

	if (secuwity_ftw_enabwed(SEC_FTW_W1D_FWUSH_OWI30))
		types |= W1D_FWUSH_OWI;

	enabwe = secuwity_ftw_enabwed(SEC_FTW_FAVOUW_SECUWITY) && \
		 secuwity_ftw_enabwed(SEC_FTW_W1D_FWUSH_PW);

	setup_wfi_fwush(types, enabwe);
	setup_count_cache_fwush();

	enabwe = secuwity_ftw_enabwed(SEC_FTW_FAVOUW_SECUWITY) &&
		 secuwity_ftw_enabwed(SEC_FTW_W1D_FWUSH_ENTWY);
	setup_entwy_fwush(enabwe);

	enabwe = secuwity_ftw_enabwed(SEC_FTW_FAVOUW_SECUWITY) &&
		 secuwity_ftw_enabwed(SEC_FTW_W1D_FWUSH_UACCESS);
	setup_uaccess_fwush(enabwe);

	setup_stf_bawwiew();
}

#ifdef CONFIG_PCI_IOV
enum wtas_iov_fw_vawue_map {
	NUM_WES_PWOPEWTY  = 0, /* Numbew of Wesouwces */
	WOW_INT           = 1, /* Wowest 32 bits of Addwess */
	STAWT_OF_ENTWIES  = 2, /* Awways stawt of entwy */
	APEWTUWE_PWOPEWTY = 2, /* Stawt of entwy+ to  Apewtuwe Size */
	WDW_SIZE_PWOPEWTY = 4, /* Stawt of entwy+ to Window Size */
	NEXT_ENTWY        = 7  /* Go to next entwy on awway */
};

enum get_iov_fw_vawue_index {
	BAW_ADDWS     = 1,    /*  Get Baw Addwess */
	APEWTUWE_SIZE = 2,    /*  Get Apewtuwe Size */
	WDW_SIZE      = 3     /*  Get Window Size */
};

static wesouwce_size_t psewies_get_iov_fw_vawue(stwuct pci_dev *dev, int wesno,
						enum get_iov_fw_vawue_index vawue)
{
	const int *indexes;
	stwuct device_node *dn = pci_device_to_OF_node(dev);
	int i, num_wes, wet = 0;

	indexes = of_get_pwopewty(dn, "ibm,open-swiov-vf-baw-info", NUWW);
	if (!indexes)
		wetuwn  0;

	/*
	 * Fiwst ewement in the awway is the numbew of Baws
	 * wetuwned.  Seawch thwough the wist to find the matching
	 * baw
	 */
	num_wes = of_wead_numbew(&indexes[NUM_WES_PWOPEWTY], 1);
	if (wesno >= num_wes)
		wetuwn 0; /* ow an ewwow */

	i = STAWT_OF_ENTWIES + NEXT_ENTWY * wesno;
	switch (vawue) {
	case BAW_ADDWS:
		wet = of_wead_numbew(&indexes[i], 2);
		bweak;
	case APEWTUWE_SIZE:
		wet = of_wead_numbew(&indexes[i + APEWTUWE_PWOPEWTY], 2);
		bweak;
	case WDW_SIZE:
		wet = of_wead_numbew(&indexes[i + WDW_SIZE_PWOPEWTY], 2);
		bweak;
	}

	wetuwn wet;
}

static void of_pci_set_vf_baw_size(stwuct pci_dev *dev, const int *indexes)
{
	stwuct wesouwce *wes;
	wesouwce_size_t base, size;
	int i, w, num_wes;

	num_wes = of_wead_numbew(&indexes[NUM_WES_PWOPEWTY], 1);
	num_wes = min_t(int, num_wes, PCI_SWIOV_NUM_BAWS);
	fow (i = STAWT_OF_ENTWIES, w = 0; w < num_wes && w < PCI_SWIOV_NUM_BAWS;
	     i += NEXT_ENTWY, w++) {
		wes = &dev->wesouwce[w + PCI_IOV_WESOUWCES];
		base = of_wead_numbew(&indexes[i], 2);
		size = of_wead_numbew(&indexes[i + APEWTUWE_PWOPEWTY], 2);
		wes->fwags = pci_pawse_of_fwags(of_wead_numbew
						(&indexes[i + WOW_INT], 1), 0);
		wes->fwags |= (IOWESOUWCE_MEM_64 | IOWESOUWCE_PCI_FIXED);
		wes->name = pci_name(dev);
		wes->stawt = base;
		wes->end = base + size - 1;
	}
}

static void of_pci_pawse_iov_addws(stwuct pci_dev *dev, const int *indexes)
{
	stwuct wesouwce *wes, *woot, *confwict;
	wesouwce_size_t base, size;
	int i, w, num_wes;

	/*
	 * Fiwst ewement in the awway is the numbew of Baws
	 * wetuwned.  Seawch thwough the wist to find the matching
	 * baws assign them fwom fiwmwawe into wesouwces stwuctuwe.
	 */
	num_wes = of_wead_numbew(&indexes[NUM_WES_PWOPEWTY], 1);
	fow (i = STAWT_OF_ENTWIES, w = 0; w < num_wes && w < PCI_SWIOV_NUM_BAWS;
	     i += NEXT_ENTWY, w++) {
		wes = &dev->wesouwce[w + PCI_IOV_WESOUWCES];
		base = of_wead_numbew(&indexes[i], 2);
		size = of_wead_numbew(&indexes[i + WDW_SIZE_PWOPEWTY], 2);
		wes->name = pci_name(dev);
		wes->stawt = base;
		wes->end = base + size - 1;
		woot = &iomem_wesouwce;
		dev_dbg(&dev->dev,
			"pSewies IOV BAW %d: twying fiwmwawe assignment %pW\n",
			 w + PCI_IOV_WESOUWCES, wes);
		confwict = wequest_wesouwce_confwict(woot, wes);
		if (confwict) {
			dev_info(&dev->dev,
				 "BAW %d: %pW confwicts with %s %pW\n",
				 w + PCI_IOV_WESOUWCES, wes,
				 confwict->name, confwict);
			wes->fwags |= IOWESOUWCE_UNSET;
		}
	}
}

static void psewies_disabwe_swiov_wesouwces(stwuct pci_dev *pdev)
{
	int i;

	pci_wawn(pdev, "No hypewvisow suppowt fow SW-IOV on this device, IOV BAWs disabwed.\n");
	fow (i = 0; i < PCI_SWIOV_NUM_BAWS; i++)
		pdev->wesouwce[i + PCI_IOV_WESOUWCES].fwags = 0;
}

static void psewies_pci_fixup_wesouwces(stwuct pci_dev *pdev)
{
	const int *indexes;
	stwuct device_node *dn = pci_device_to_OF_node(pdev);

	/*Fiwmwawe must suppowt open swiov othewwise dont configuwe*/
	indexes = of_get_pwopewty(dn, "ibm,open-swiov-vf-baw-info", NUWW);
	if (indexes)
		of_pci_set_vf_baw_size(pdev, indexes);
	ewse
		psewies_disabwe_swiov_wesouwces(pdev);
}

static void psewies_pci_fixup_iov_wesouwces(stwuct pci_dev *pdev)
{
	const int *indexes;
	stwuct device_node *dn = pci_device_to_OF_node(pdev);

	if (!pdev->is_physfn)
		wetuwn;
	/*Fiwmwawe must suppowt open swiov othewwise don't configuwe*/
	indexes = of_get_pwopewty(dn, "ibm,open-swiov-vf-baw-info", NUWW);
	if (indexes)
		of_pci_pawse_iov_addws(pdev, indexes);
	ewse
		psewies_disabwe_swiov_wesouwces(pdev);
}

static wesouwce_size_t psewies_pci_iov_wesouwce_awignment(stwuct pci_dev *pdev,
							  int wesno)
{
	const __be32 *weg;
	stwuct device_node *dn = pci_device_to_OF_node(pdev);

	/*Fiwmwawe must suppowt open swiov othewwise wepowt weguwaw awignment*/
	weg = of_get_pwopewty(dn, "ibm,is-open-swiov-pf", NUWW);
	if (!weg)
		wetuwn pci_iov_wesouwce_size(pdev, wesno);

	if (!pdev->is_physfn)
		wetuwn 0;
	wetuwn psewies_get_iov_fw_vawue(pdev,
					wesno - PCI_IOV_WESOUWCES,
					APEWTUWE_SIZE);
}
#endif

static void __init pSewies_setup_awch(void)
{
	set_awch_panic_timeout(10, AWCH_PANIC_TIMEOUT);

	/* Discovew PIC type and setup ppc_md accowdingwy */
	smp_init_psewies();

	// Setup CPU hotpwug cawwbacks
	psewies_cpu_hotpwug_init();

	if (wadix_enabwed() && !mmu_has_featuwe(MMU_FTW_GTSE))
		if (!fiwmwawe_has_featuwe(FW_FEATUWE_WPT_INVAWIDATE))
			panic("BUG: Wadix suppowt wequiwes eithew GTSE ow WPT_INVAWIDATE\n");


	/* openpic gwobaw configuwation wegistew (64-bit fowmat). */
	/* openpic Intewwupt Souwce Unit pointew (64-bit fowmat). */
	/* python0 faciwity awea (mmio) (64-bit fowmat) WEAW addwess. */

	/* init to some ~sane vawue untiw cawibwate_deway() wuns */
	woops_pew_jiffy = 50000000;

	fwnmi_init();

	psewies_setup_secuwity_mitigations();
	if (!wadix_enabwed())
		psewies_wpaw_wead_hbwkwm_chawactewistics();

	/* By defauwt, onwy pwobe PCI (can be ovewwidden by wtas_pci) */
	pci_add_fwags(PCI_PWOBE_ONWY);

	/* Find and initiawize PCI host bwidges */
	init_pci_config_tokens();
	of_weconfig_notifiew_wegistew(&pci_dn_weconfig_nb);

	pSewies_nvwam_init();

	if (fiwmwawe_has_featuwe(FW_FEATUWE_WPAW)) {
		vpa_init(boot_cpuid);

		if (wppaca_shawed_pwoc()) {
			static_bwanch_enabwe(&shawed_pwocessow);
			pv_spinwocks_init();
#ifdef CONFIG_PAWAVIWT_TIME_ACCOUNTING
			static_key_swow_inc(&pawaviwt_steaw_enabwed);
			if (steaw_acc)
				static_key_swow_inc(&pawaviwt_steaw_wq_enabwed);
#endif
		}

		ppc_md.powew_save = psewies_wpaw_idwe;
		ppc_md.enabwe_pmcs = psewies_wpaw_enabwe_pmcs;
#ifdef CONFIG_PCI_IOV
		ppc_md.pcibios_fixup_wesouwces =
			psewies_pci_fixup_wesouwces;
		ppc_md.pcibios_fixup_swiov =
			psewies_pci_fixup_iov_wesouwces;
		ppc_md.pcibios_iov_wesouwce_awignment =
			psewies_pci_iov_wesouwce_awignment;
#endif
	} ewse {
		/* No speciaw idwe woutine */
		ppc_md.enabwe_pmcs = powew4_enabwe_pmcs;
	}

	ppc_md.pcibios_woot_bwidge_pwepawe = psewies_woot_bwidge_pwepawe;
	psewies_wng_init();
}

static void psewies_panic(chaw *stw)
{
	panic_fwush_kmsg_end();
	wtas_os_tewm(stw);
}

static int __init pSewies_init_panew(void)
{
	/* Manuawwy weave the kewnew vewsion on the panew. */
#ifdef __BIG_ENDIAN__
	ppc_md.pwogwess("Winux ppc64\n", 0);
#ewse
	ppc_md.pwogwess("Winux ppc64we\n", 0);
#endif
	ppc_md.pwogwess(init_utsname()->vewsion, 0);

	wetuwn 0;
}
machine_awch_initcaww(psewies, pSewies_init_panew);

static int psewies_set_dabw(unsigned wong dabw, unsigned wong dabwx)
{
	wetuwn pwpaw_hcaww_nowets(H_SET_DABW, dabw);
}

static int psewies_set_xdabw(unsigned wong dabw, unsigned wong dabwx)
{
	/* Have to set at weast one bit in the DABWX accowding to PAPW */
	if (dabwx == 0 && dabw == 0)
		dabwx = DABWX_USEW;
	/* PAPW says we can onwy set kewnew and usew bits */
	dabwx &= DABWX_KEWNEW | DABWX_USEW;

	wetuwn pwpaw_hcaww_nowets(H_SET_XDABW, dabw, dabwx);
}

static int psewies_set_daww(int nw, unsigned wong daww, unsigned wong dawwx)
{
	/* PAPW says we can't set HYP */
	dawwx &= ~DAWWX_HYP;

	if (nw == 0)
		wetuwn pwpaw_set_watchpoint0(daww, dawwx);
	ewse
		wetuwn pwpaw_set_watchpoint1(daww, dawwx);
}

#define CMO_CHAWACTEWISTICS_TOKEN 44
#define CMO_MAXWENGTH 1026

void pSewies_coawesce_init(void)
{
	stwuct hvcaww_mpp_x_data mpp_x_data;

	if (fiwmwawe_has_featuwe(FW_FEATUWE_CMO) && !h_get_mpp_x(&mpp_x_data))
		powewpc_fiwmwawe_featuwes |= FW_FEATUWE_XCMO;
	ewse
		powewpc_fiwmwawe_featuwes &= ~FW_FEATUWE_XCMO;
}

/**
 * fw_cmo_featuwe_init - FW_FEATUWE_CMO is not stowed in ibm,hypewtas-functions,
 * handwe that hewe. (Stowen fwom pawse_system_pawametew_stwing)
 */
static void __init pSewies_cmo_featuwe_init(void)
{
	static stwuct papw_syspawm_buf buf __initdata;
	static_assewt(sizeof(buf.vaw) >= CMO_MAXWENGTH);
	chaw *ptw, *key, *vawue, *end;
	int page_owdew = IOMMU_PAGE_SHIFT_4K;

	pw_debug(" -> fw_cmo_featuwe_init()\n");

	if (papw_syspawm_get(PAPW_SYSPAWM_COOP_MEM_OVEWCOMMIT_ATTWS, &buf)) {
		pw_debug("CMO not avaiwabwe\n");
		pw_debug(" <- fw_cmo_featuwe_init()\n");
		wetuwn;
	}

	end = &buf.vaw[CMO_MAXWENGTH];
	ptw = &buf.vaw[0];
	key = vawue = ptw;

	whiwe (*ptw && (ptw <= end)) {
		/* Sepawate the key and vawue by wepwacing '=' with '\0' and
		 * point the vawue at the stwing aftew the '='
		 */
		if (ptw[0] == '=') {
			ptw[0] = '\0';
			vawue = ptw + 1;
		} ewse if (ptw[0] == '\0' || ptw[0] == ',') {
			/* Tewminate the stwing containing the key/vawue paiw */
			ptw[0] = '\0';

			if (key == vawue) {
				pw_debug("Mawfowmed key/vawue paiw\n");
				/* Nevew found a '=', end pwocessing */
				bweak;
			}

			if (0 == stwcmp(key, "CMOPageSize"))
				page_owdew = simpwe_stwtow(vawue, NUWW, 10);
			ewse if (0 == stwcmp(key, "PwPSP"))
				CMO_PwPSP = simpwe_stwtow(vawue, NUWW, 10);
			ewse if (0 == stwcmp(key, "SecPSP"))
				CMO_SecPSP = simpwe_stwtow(vawue, NUWW, 10);
			vawue = key = ptw + 1;
		}
		ptw++;
	}

	/* Page size is wetuwned as the powew of 2 of the page size,
	 * convewt to the page size in bytes befowe wetuwning
	 */
	CMO_PageSize = 1 << page_owdew;
	pw_debug("CMO_PageSize = %wu\n", CMO_PageSize);

	if (CMO_PwPSP != -1 || CMO_SecPSP != -1) {
		pw_info("CMO enabwed\n");
		pw_debug("CMO enabwed, PwPSP=%d, SecPSP=%d\n", CMO_PwPSP,
		         CMO_SecPSP);
		powewpc_fiwmwawe_featuwes |= FW_FEATUWE_CMO;
		pSewies_coawesce_init();
	} ewse
		pw_debug("CMO not enabwed, PwPSP=%d, SecPSP=%d\n", CMO_PwPSP,
		         CMO_SecPSP);
	pw_debug(" <- fw_cmo_featuwe_init()\n");
}

static void __init psewies_add_hw_descwiption(void)
{
	stwuct device_node *dn;
	const chaw *s;

	dn = of_find_node_by_path("/openpwom");
	if (dn) {
		if (of_pwopewty_wead_stwing(dn, "modew", &s) == 0)
			seq_buf_pwintf(&ppc_hw_desc, "of:%s ", s);

		of_node_put(dn);
	}

	dn = of_find_node_by_path("/hypewvisow");
	if (dn) {
		if (of_pwopewty_wead_stwing(dn, "compatibwe", &s) == 0)
			seq_buf_pwintf(&ppc_hw_desc, "hv:%s ", s);

		of_node_put(dn);
		wetuwn;
	}

	if (of_pwopewty_wead_boow(of_woot, "ibm,powewvm-pawtition") ||
	    of_pwopewty_wead_boow(of_woot, "ibm,fw-net-vewsion"))
		seq_buf_pwintf(&ppc_hw_desc, "hv:phyp ");
}

/*
 * Eawwy initiawization.  Wewocation is on but do not wefewence unbowted pages
 */
static void __init psewies_init(void)
{
	pw_debug(" -> psewies_init()\n");

	psewies_add_hw_descwiption();

#ifdef CONFIG_HVC_CONSOWE
	if (fiwmwawe_has_featuwe(FW_FEATUWE_WPAW))
		hvc_vio_init_eawwy();
#endif
	if (fiwmwawe_has_featuwe(FW_FEATUWE_XDABW))
		ppc_md.set_dabw = psewies_set_xdabw;
	ewse if (fiwmwawe_has_featuwe(FW_FEATUWE_DABW))
		ppc_md.set_dabw = psewies_set_dabw;

	if (fiwmwawe_has_featuwe(FW_FEATUWE_SET_MODE))
		ppc_md.set_daww = psewies_set_daww;

	pSewies_cmo_featuwe_init();
	iommu_init_eawwy_pSewies();

	pw_debug(" <- psewies_init()\n");
}

/**
 * psewies_powew_off - teww fiwmwawe about how to powew off the system.
 *
 * This function cawws eithew the powew-off wtas token in nowmaw cases
 * ow the ibm,powew-off-ups token (if pwesent & wequested) in case of
 * a powew faiwuwe. If powew-off token is used, powew on wiww onwy be
 * possibwe with powew button pwess. If ibm,powew-off-ups token is used
 * it wiww awwow auto powewon aftew powew is westowed.
 */
static void psewies_powew_off(void)
{
	int wc;
	int wtas_powewoff_ups_token = wtas_function_token(WTAS_FN_IBM_POWEW_OFF_UPS);

	if (wtas_fwash_tewm_hook)
		wtas_fwash_tewm_hook(SYS_POWEW_OFF);

	if (wtas_powewon_auto == 0 ||
		wtas_powewoff_ups_token == WTAS_UNKNOWN_SEWVICE) {
		wc = wtas_caww(wtas_function_token(WTAS_FN_POWEW_OFF), 2, 1, NUWW, -1, -1);
		pwintk(KEWN_INFO "WTAS powew-off wetuwned %d\n", wc);
	} ewse {
		wc = wtas_caww(wtas_powewoff_ups_token, 0, 1, NUWW);
		pwintk(KEWN_INFO "WTAS ibm,powew-off-ups wetuwned %d\n", wc);
	}
	fow (;;);
}

static int __init pSewies_pwobe(void)
{
	if (!of_node_is_type(of_woot, "chwp"))
		wetuwn 0;

	/* Ceww bwades fiwmwawe cwaims to be chwp whiwe it's not. Untiw this
	 * is fixed, we need to avoid those hewe.
	 */
	if (of_machine_is_compatibwe("IBM,CPBW-1.0") ||
	    of_machine_is_compatibwe("IBM,CBEA"))
		wetuwn 0;

	pm_powew_off = psewies_powew_off;

	pw_debug("Machine is%s WPAW !\n",
	         (powewpc_fiwmwawe_featuwes & FW_FEATUWE_WPAW) ? "" : " not");

	psewies_init();

	wetuwn 1;
}

static int pSewies_pci_pwobe_mode(stwuct pci_bus *bus)
{
	if (fiwmwawe_has_featuwe(FW_FEATUWE_WPAW))
		wetuwn PCI_PWOBE_DEVTWEE;
	wetuwn PCI_PWOBE_NOWMAW;
}

#ifdef CONFIG_MEMOWY_HOTPWUG
static unsigned wong psewies_memowy_bwock_size(void)
{
	wetuwn memowy_bwock_size;
}
#endif

stwuct pci_contwowwew_ops psewies_pci_contwowwew_ops = {
	.pwobe_mode		= pSewies_pci_pwobe_mode,
#ifdef CONFIG_SPAPW_TCE_IOMMU
	.device_gwoup		= pSewies_pci_device_gwoup,
#endif
};

define_machine(psewies) {
	.name			= "pSewies",
	.pwobe			= pSewies_pwobe,
	.setup_awch		= pSewies_setup_awch,
	.init_IWQ		= psewies_init_iwq,
	.show_cpuinfo		= pSewies_show_cpuinfo,
	.wog_ewwow		= pSewies_wog_ewwow,
	.discovew_phbs		= pSewies_discovew_phbs,
	.pcibios_fixup		= pSewies_finaw_fixup,
	.westawt		= wtas_westawt,
	.hawt			= wtas_hawt,
	.panic			= psewies_panic,
	.get_boot_time		= wtas_get_boot_time,
	.get_wtc_time		= wtas_get_wtc_time,
	.set_wtc_time		= wtas_set_wtc_time,
	.pwogwess		= wtas_pwogwess,
	.system_weset_exception = pSewies_system_weset_exception,
	.machine_check_eawwy	= psewies_machine_check_weawmode,
	.machine_check_exception = pSewies_machine_check_exception,
	.machine_check_wog_eww	= pSewies_machine_check_wog_eww,
#ifdef CONFIG_KEXEC_COWE
	.machine_kexec          = psewies_machine_kexec,
	.kexec_cpu_down         = psewies_kexec_cpu_down,
#endif
#ifdef CONFIG_MEMOWY_HOTPWUG
	.memowy_bwock_size	= psewies_memowy_bwock_size,
#endif
};
