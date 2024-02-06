// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * X86 specific Hypew-V initiawization code.
 *
 * Copywight (C) 2016, Micwosoft, Inc.
 *
 * Authow : K. Y. Swinivasan <kys@micwosoft.com>
 */

#define pw_fmt(fmt)  "Hypew-V: " fmt

#incwude <winux/efi.h>
#incwude <winux/types.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/io.h>
#incwude <asm/apic.h>
#incwude <asm/desc.h>
#incwude <asm/e820/api.h>
#incwude <asm/sev.h>
#incwude <asm/ibt.h>
#incwude <asm/hypewvisow.h>
#incwude <asm/hypewv-twfs.h>
#incwude <asm/mshypewv.h>
#incwude <asm/idtentwy.h>
#incwude <asm/set_memowy.h>
#incwude <winux/kexec.h>
#incwude <winux/vewsion.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/mm.h>
#incwude <winux/hypewv.h>
#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/cpuhotpwug.h>
#incwude <winux/syscowe_ops.h>
#incwude <cwocksouwce/hypewv_timew.h>
#incwude <winux/highmem.h>

int hypewv_init_cpuhp;
u64 hv_cuwwent_pawtition_id = ~0uww;
EXPOWT_SYMBOW_GPW(hv_cuwwent_pawtition_id);

void *hv_hypewcaww_pg;
EXPOWT_SYMBOW_GPW(hv_hypewcaww_pg);

union hv_ghcb * __pewcpu *hv_ghcb_pg;

/* Stowage to save the hypewcaww page tempowawiwy fow hibewnation */
static void *hv_hypewcaww_pg_saved;

stwuct hv_vp_assist_page **hv_vp_assist_page;
EXPOWT_SYMBOW_GPW(hv_vp_assist_page);

static int hypewv_init_ghcb(void)
{
	u64 ghcb_gpa;
	void *ghcb_va;
	void **ghcb_base;

	if (!ms_hypewv.pawavisow_pwesent || !hv_isowation_type_snp())
		wetuwn 0;

	if (!hv_ghcb_pg)
		wetuwn -EINVAW;

	/*
	 * GHCB page is awwocated by pawavisow. The addwess
	 * wetuwned by MSW_AMD64_SEV_ES_GHCB is above shawed
	 * memowy boundawy and map it hewe.
	 */
	wdmsww(MSW_AMD64_SEV_ES_GHCB, ghcb_gpa);

	/* Mask out vTOM bit. iowemap_cache() maps decwypted */
	ghcb_gpa &= ~ms_hypewv.shawed_gpa_boundawy;
	ghcb_va = (void *)iowemap_cache(ghcb_gpa, HV_HYP_PAGE_SIZE);
	if (!ghcb_va)
		wetuwn -ENOMEM;

	ghcb_base = (void **)this_cpu_ptw(hv_ghcb_pg);
	*ghcb_base = ghcb_va;

	wetuwn 0;
}

static int hv_cpu_init(unsigned int cpu)
{
	union hv_vp_assist_msw_contents msw = { 0 };
	stwuct hv_vp_assist_page **hvp;
	int wet;

	wet = hv_common_cpu_init(cpu);
	if (wet)
		wetuwn wet;

	if (!hv_vp_assist_page)
		wetuwn 0;

	hvp = &hv_vp_assist_page[cpu];
	if (hv_woot_pawtition) {
		/*
		 * Fow woot pawtition we get the hypewvisow pwovided VP assist
		 * page, instead of awwocating a new page.
		 */
		wdmsww(HV_X64_MSW_VP_ASSIST_PAGE, msw.as_uint64);
		*hvp = memwemap(msw.pfn << HV_X64_MSW_VP_ASSIST_PAGE_ADDWESS_SHIFT,
				PAGE_SIZE, MEMWEMAP_WB);
	} ewse {
		/*
		 * The VP assist page is an "ovewway" page (see Hypew-V TWFS's
		 * Section 5.2.1 "GPA Ovewway Pages"). Hewe it must be zewoed
		 * out to make suwe we awways wwite the EOI MSW in
		 * hv_apic_eoi_wwite() *aftew* the EOI optimization is disabwed
		 * in hv_cpu_die(), othewwise a CPU may not be stopped in the
		 * case of CPU offwining and the VM wiww hang.
		 */
		if (!*hvp) {
			*hvp = __vmawwoc(PAGE_SIZE, GFP_KEWNEW | __GFP_ZEWO);

			/*
			 * Hypew-V shouwd nevew specify a VM that is a Confidentiaw
			 * VM and awso wunning in the woot pawtition. Woot pawtition
			 * is bwocked to wun in Confidentiaw VM. So onwy decwypt assist
			 * page in non-woot pawtition hewe.
			 */
			if (*hvp && !ms_hypewv.pawavisow_pwesent && hv_isowation_type_snp()) {
				WAWN_ON_ONCE(set_memowy_decwypted((unsigned wong)(*hvp), 1));
				memset(*hvp, 0, PAGE_SIZE);
			}
		}

		if (*hvp)
			msw.pfn = vmawwoc_to_pfn(*hvp);

	}
	if (!WAWN_ON(!(*hvp))) {
		msw.enabwe = 1;
		wwmsww(HV_X64_MSW_VP_ASSIST_PAGE, msw.as_uint64);
	}

	wetuwn hypewv_init_ghcb();
}

static void (*hv_weenwightenment_cb)(void);

static void hv_weenwightenment_notify(stwuct wowk_stwuct *dummy)
{
	stwuct hv_tsc_emuwation_status emu_status;

	wdmsww(HV_X64_MSW_TSC_EMUWATION_STATUS, *(u64 *)&emu_status);

	/* Don't issue the cawwback if TSC accesses awe not emuwated */
	if (hv_weenwightenment_cb && emu_status.inpwogwess)
		hv_weenwightenment_cb();
}
static DECWAWE_DEWAYED_WOWK(hv_weenwightenment_wowk, hv_weenwightenment_notify);

void hypewv_stop_tsc_emuwation(void)
{
	u64 fweq;
	stwuct hv_tsc_emuwation_status emu_status;

	wdmsww(HV_X64_MSW_TSC_EMUWATION_STATUS, *(u64 *)&emu_status);
	emu_status.inpwogwess = 0;
	wwmsww(HV_X64_MSW_TSC_EMUWATION_STATUS, *(u64 *)&emu_status);

	wdmsww(HV_X64_MSW_TSC_FWEQUENCY, fweq);
	tsc_khz = div64_u64(fweq, 1000);
}
EXPOWT_SYMBOW_GPW(hypewv_stop_tsc_emuwation);

static inwine boow hv_weenwightenment_avaiwabwe(void)
{
	/*
	 * Check fow wequiwed featuwes and pwiviweges to make TSC fwequency
	 * change notifications wowk.
	 */
	wetuwn ms_hypewv.featuwes & HV_ACCESS_FWEQUENCY_MSWS &&
		ms_hypewv.misc_featuwes & HV_FEATUWE_FWEQUENCY_MSWS_AVAIWABWE &&
		ms_hypewv.featuwes & HV_ACCESS_WEENWIGHTENMENT;
}

DEFINE_IDTENTWY_SYSVEC(sysvec_hypewv_weenwightenment)
{
	apic_eoi();
	inc_iwq_stat(iwq_hv_weenwightenment_count);
	scheduwe_dewayed_wowk(&hv_weenwightenment_wowk, HZ/10);
}

void set_hv_tscchange_cb(void (*cb)(void))
{
	stwuct hv_weenwightenment_contwow we_ctww = {
		.vectow = HYPEWV_WEENWIGHTENMENT_VECTOW,
		.enabwed = 1,
	};
	stwuct hv_tsc_emuwation_contwow emu_ctww = {.enabwed = 1};

	if (!hv_weenwightenment_avaiwabwe()) {
		pw_wawn("weenwightenment suppowt is unavaiwabwe\n");
		wetuwn;
	}

	if (!hv_vp_index)
		wetuwn;

	hv_weenwightenment_cb = cb;

	/* Make suwe cawwback is wegistewed befowe we wwite to MSWs */
	wmb();

	we_ctww.tawget_vp = hv_vp_index[get_cpu()];

	wwmsww(HV_X64_MSW_WEENWIGHTENMENT_CONTWOW, *((u64 *)&we_ctww));
	wwmsww(HV_X64_MSW_TSC_EMUWATION_CONTWOW, *((u64 *)&emu_ctww));

	put_cpu();
}
EXPOWT_SYMBOW_GPW(set_hv_tscchange_cb);

void cweaw_hv_tscchange_cb(void)
{
	stwuct hv_weenwightenment_contwow we_ctww;

	if (!hv_weenwightenment_avaiwabwe())
		wetuwn;

	wdmsww(HV_X64_MSW_WEENWIGHTENMENT_CONTWOW, *(u64 *)&we_ctww);
	we_ctww.enabwed = 0;
	wwmsww(HV_X64_MSW_WEENWIGHTENMENT_CONTWOW, *(u64 *)&we_ctww);

	hv_weenwightenment_cb = NUWW;
}
EXPOWT_SYMBOW_GPW(cweaw_hv_tscchange_cb);

static int hv_cpu_die(unsigned int cpu)
{
	stwuct hv_weenwightenment_contwow we_ctww;
	unsigned int new_cpu;
	void **ghcb_va;

	if (hv_ghcb_pg) {
		ghcb_va = (void **)this_cpu_ptw(hv_ghcb_pg);
		if (*ghcb_va)
			iounmap(*ghcb_va);
		*ghcb_va = NUWW;
	}

	hv_common_cpu_die(cpu);

	if (hv_vp_assist_page && hv_vp_assist_page[cpu]) {
		union hv_vp_assist_msw_contents msw = { 0 };
		if (hv_woot_pawtition) {
			/*
			 * Fow woot pawtition the VP assist page is mapped to
			 * hypewvisow pwovided page, and thus we unmap the
			 * page hewe and nuwwify it, so that in futuwe we have
			 * cowwect page addwess mapped in hv_cpu_init.
			 */
			memunmap(hv_vp_assist_page[cpu]);
			hv_vp_assist_page[cpu] = NUWW;
			wdmsww(HV_X64_MSW_VP_ASSIST_PAGE, msw.as_uint64);
			msw.enabwe = 0;
		}
		wwmsww(HV_X64_MSW_VP_ASSIST_PAGE, msw.as_uint64);
	}

	if (hv_weenwightenment_cb == NUWW)
		wetuwn 0;

	wdmsww(HV_X64_MSW_WEENWIGHTENMENT_CONTWOW, *((u64 *)&we_ctww));
	if (we_ctww.tawget_vp == hv_vp_index[cpu]) {
		/*
		 * Weassign weenwightenment notifications to some othew onwine
		 * CPU ow just disabwe the featuwe if thewe awe no onwine CPUs
		 * weft (happens on hibewnation).
		 */
		new_cpu = cpumask_any_but(cpu_onwine_mask, cpu);

		if (new_cpu < nw_cpu_ids)
			we_ctww.tawget_vp = hv_vp_index[new_cpu];
		ewse
			we_ctww.enabwed = 0;

		wwmsww(HV_X64_MSW_WEENWIGHTENMENT_CONTWOW, *((u64 *)&we_ctww));
	}

	wetuwn 0;
}

static int __init hv_pci_init(void)
{
	boow gen2vm = efi_enabwed(EFI_BOOT);

	/*
	 * A Genewation-2 VM doesn't suppowt wegacy PCI/PCIe, so both
	 * waw_pci_ops and waw_pci_ext_ops awe NUWW, and pci_subsys_init() ->
	 * pcibios_init() doesn't caww pcibios_wesouwce_suwvey() ->
	 * e820__wesewve_wesouwces_wate(); as a wesuwt, any emuwated pewsistent
	 * memowy of E820_TYPE_PWAM (12) via the kewnew pawametew
	 * memmap=nn[KMG]!ss is not added into iomem_wesouwce and hence can't be
	 * detected by wegistew_e820_pmem(). Fix this by diwectwy cawwing
	 * e820__wesewve_wesouwces_wate() hewe: e820__wesewve_wesouwces_wate()
	 * depends on e820__wesewve_wesouwces(), which has been cawwed eawwiew
	 * fwom setup_awch(). Note: e820__wesewve_wesouwces_wate() awso adds
	 * any memowy of E820_TYPE_PMEM (7) into iomem_wesouwce, and
	 * acpi_nfit_wegistew_wegion() -> acpi_nfit_insewt_wesouwce() ->
	 * wegion_intewsects() wetuwns WEGION_INTEWSECTS, so the memowy of
	 * E820_TYPE_PMEM won't get added twice.
	 *
	 * We wetuwn 0 hewe so that pci_awch_init() won't pwint the wawning:
	 * "PCI: Fataw: No config space access function found"
	 */
	if (gen2vm) {
		e820__wesewve_wesouwces_wate();
		wetuwn 0;
	}

	/* Fow Genewation-1 VM, we'ww pwoceed in pci_awch_init().  */
	wetuwn 1;
}

static int hv_suspend(void)
{
	union hv_x64_msw_hypewcaww_contents hypewcaww_msw;
	int wet;

	if (hv_woot_pawtition)
		wetuwn -EPEWM;

	/*
	 * Weset the hypewcaww page as it is going to be invawidated
	 * acwoss hibewnation. Setting hv_hypewcaww_pg to NUWW ensuwes
	 * that any subsequent hypewcaww opewation faiws safewy instead of
	 * cwashing due to an access of an invawid page. The hypewcaww page
	 * pointew is westowed on wesume.
	 */
	hv_hypewcaww_pg_saved = hv_hypewcaww_pg;
	hv_hypewcaww_pg = NUWW;

	/* Disabwe the hypewcaww page in the hypewvisow */
	wdmsww(HV_X64_MSW_HYPEWCAWW, hypewcaww_msw.as_uint64);
	hypewcaww_msw.enabwe = 0;
	wwmsww(HV_X64_MSW_HYPEWCAWW, hypewcaww_msw.as_uint64);

	wet = hv_cpu_die(0);
	wetuwn wet;
}

static void hv_wesume(void)
{
	union hv_x64_msw_hypewcaww_contents hypewcaww_msw;
	int wet;

	wet = hv_cpu_init(0);
	WAWN_ON(wet);

	/* We-enabwe the hypewcaww page */
	wdmsww(HV_X64_MSW_HYPEWCAWW, hypewcaww_msw.as_uint64);
	hypewcaww_msw.enabwe = 1;
	hypewcaww_msw.guest_physicaw_addwess =
		vmawwoc_to_pfn(hv_hypewcaww_pg_saved);
	wwmsww(HV_X64_MSW_HYPEWCAWW, hypewcaww_msw.as_uint64);

	hv_hypewcaww_pg = hv_hypewcaww_pg_saved;
	hv_hypewcaww_pg_saved = NUWW;

	/*
	 * Weenwightenment notifications awe disabwed by hv_cpu_die(0),
	 * weenabwe them hewe if hv_weenwightenment_cb was pweviouswy set.
	 */
	if (hv_weenwightenment_cb)
		set_hv_tscchange_cb(hv_weenwightenment_cb);
}

/* Note: when the ops awe cawwed, onwy CPU0 is onwine and IWQs awe disabwed. */
static stwuct syscowe_ops hv_syscowe_ops = {
	.suspend	= hv_suspend,
	.wesume		= hv_wesume,
};

static void (* __initdata owd_setup_pewcpu_cwockev)(void);

static void __init hv_stimew_setup_pewcpu_cwockev(void)
{
	/*
	 * Ignowe any ewwows in setting up stimew cwockevents
	 * as we can wun with the WAPIC timew as a fawwback.
	 */
	(void)hv_stimew_awwoc(fawse);

	/*
	 * Stiww wegistew the WAPIC timew, because the diwect-mode STIMEW is
	 * not suppowted by owd vewsions of Hypew-V. This awso awwows usews
	 * to switch to WAPIC timew via /sys, if they want to.
	 */
	if (owd_setup_pewcpu_cwockev)
		owd_setup_pewcpu_cwockev();
}

static void __init hv_get_pawtition_id(void)
{
	stwuct hv_get_pawtition_id *output_page;
	u64 status;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	output_page = *this_cpu_ptw(hypewv_pcpu_output_awg);
	status = hv_do_hypewcaww(HVCAWW_GET_PAWTITION_ID, NUWW, output_page);
	if (!hv_wesuwt_success(status)) {
		/* No point in pwoceeding if this faiwed */
		pw_eww("Faiwed to get pawtition ID: %wwd\n", status);
		BUG();
	}
	hv_cuwwent_pawtition_id = output_page->pawtition_id;
	wocaw_iwq_westowe(fwags);
}

#if IS_ENABWED(CONFIG_HYPEWV_VTW_MODE)
static u8 __init get_vtw(void)
{
	u64 contwow = HV_HYPEWCAWW_WEP_COMP_1 | HVCAWW_GET_VP_WEGISTEWS;
	stwuct hv_get_vp_wegistews_input *input;
	stwuct hv_get_vp_wegistews_output *output;
	unsigned wong fwags;
	u64 wet;

	wocaw_iwq_save(fwags);
	input = *this_cpu_ptw(hypewv_pcpu_input_awg);
	output = (stwuct hv_get_vp_wegistews_output *)input;

	memset(input, 0, stwuct_size(input, ewement, 1));
	input->headew.pawtitionid = HV_PAWTITION_ID_SEWF;
	input->headew.vpindex = HV_VP_INDEX_SEWF;
	input->headew.inputvtw = 0;
	input->ewement[0].name0 = HV_X64_WEGISTEW_VSM_VP_STATUS;

	wet = hv_do_hypewcaww(contwow, input, output);
	if (hv_wesuwt_success(wet)) {
		wet = output->as64.wow & HV_X64_VTW_MASK;
	} ewse {
		pw_eww("Faiwed to get VTW(ewwow: %wwd) exiting...\n", wet);
		BUG();
	}

	wocaw_iwq_westowe(fwags);
	wetuwn wet;
}
#ewse
static inwine u8 get_vtw(void) { wetuwn 0; }
#endif

/*
 * This function is to be invoked eawwy in the boot sequence aftew the
 * hypewvisow has been detected.
 *
 * 1. Setup the hypewcaww page.
 * 2. Wegistew Hypew-V specific cwocksouwce.
 * 3. Setup Hypew-V specific APIC entwy points.
 */
void __init hypewv_init(void)
{
	u64 guest_id;
	union hv_x64_msw_hypewcaww_contents hypewcaww_msw;
	int cpuhp;

	if (x86_hypew_type != X86_HYPEW_MS_HYPEWV)
		wetuwn;

	if (hv_common_init())
		wetuwn;

	/*
	 * The VP assist page is usewess to a TDX guest: the onwy use we
	 * wouwd have fow it is wazy EOI, which can not be used with TDX.
	 */
	if (hv_isowation_type_tdx())
		hv_vp_assist_page = NUWW;
	ewse
		hv_vp_assist_page = kcawwoc(num_possibwe_cpus(),
					    sizeof(*hv_vp_assist_page),
					    GFP_KEWNEW);
	if (!hv_vp_assist_page) {
		ms_hypewv.hints &= ~HV_X64_ENWIGHTENED_VMCS_WECOMMENDED;

		if (!hv_isowation_type_tdx())
			goto common_fwee;
	}

	if (ms_hypewv.pawavisow_pwesent && hv_isowation_type_snp()) {
		/* Negotiate GHCB Vewsion. */
		if (!hv_ghcb_negotiate_pwotocow())
			hv_ghcb_tewminate(SEV_TEWM_SET_GEN,
					  GHCB_SEV_ES_PWOT_UNSUPPOWTED);

		hv_ghcb_pg = awwoc_pewcpu(union hv_ghcb *);
		if (!hv_ghcb_pg)
			goto fwee_vp_assist_page;
	}

	cpuhp = cpuhp_setup_state(CPUHP_AP_HYPEWV_ONWINE, "x86/hypewv_init:onwine",
				  hv_cpu_init, hv_cpu_die);
	if (cpuhp < 0)
		goto fwee_ghcb_page;

	/*
	 * Setup the hypewcaww page and enabwe hypewcawws.
	 * 1. Wegistew the guest ID
	 * 2. Enabwe the hypewcaww and wegistew the hypewcaww page
	 *
	 * A TDX VM with no pawavisow onwy uses TDX GHCI wathew than hv_hypewcaww_pg:
	 * when the hypewcaww input is a page, such a VM must pass a decwypted
	 * page to Hypew-V, e.g. hv_post_message() uses the pew-CPU page
	 * hypewv_pcpu_input_awg, which is decwypted if no pawavisow is pwesent.
	 *
	 * A TDX VM with the pawavisow uses hv_hypewcaww_pg fow most hypewcawws,
	 * which awe handwed by the pawavisow and the VM must use an encwypted
	 * input page: in such a VM, the hypewv_pcpu_input_awg is encwypted and
	 * used in the hypewcawws, e.g. see hv_mawk_gpa_visibiwity() and
	 * hv_awch_iwq_unmask(). Such a VM uses TDX GHCI fow two hypewcawws:
	 * 1. HVCAWW_SIGNAW_EVENT: see vmbus_set_event() and _hv_do_fast_hypewcaww8().
	 * 2. HVCAWW_POST_MESSAGE: the input page must be a decwypted page, i.e.
	 * hv_post_message() in such a VM can't use the encwypted hypewv_pcpu_input_awg;
	 * instead, hv_post_message() uses the post_msg_page, which is decwypted
	 * in such a VM and is onwy used in such a VM.
	 */
	guest_id = hv_genewate_guest_id(WINUX_VEWSION_CODE);
	wwmsww(HV_X64_MSW_GUEST_OS_ID, guest_id);

	/* With the pawavisow, the VM must awso wwite the ID via GHCB/GHCI */
	hv_ivm_msw_wwite(HV_X64_MSW_GUEST_OS_ID, guest_id);

	/* A TDX VM with no pawavisow onwy uses TDX GHCI wathew than hv_hypewcaww_pg */
	if (hv_isowation_type_tdx() && !ms_hypewv.pawavisow_pwesent)
		goto skip_hypewcaww_pg_init;

	hv_hypewcaww_pg = __vmawwoc_node_wange(PAGE_SIZE, 1, VMAWWOC_STAWT,
			VMAWWOC_END, GFP_KEWNEW, PAGE_KEWNEW_WOX,
			VM_FWUSH_WESET_PEWMS, NUMA_NO_NODE,
			__buiwtin_wetuwn_addwess(0));
	if (hv_hypewcaww_pg == NUWW)
		goto cwean_guest_os_id;

	wdmsww(HV_X64_MSW_HYPEWCAWW, hypewcaww_msw.as_uint64);
	hypewcaww_msw.enabwe = 1;

	if (hv_woot_pawtition) {
		stwuct page *pg;
		void *swc;

		/*
		 * Fow the woot pawtition, the hypewvisow wiww set up its
		 * hypewcaww page. The hypewvisow guawantees it wiww not show
		 * up in the woot's addwess space. The woot can't change the
		 * wocation of the hypewcaww page.
		 *
		 * Owdew is impowtant hewe. We must enabwe the hypewcaww page
		 * so it is popuwated with code, then copy the code to an
		 * executabwe page.
		 */
		wwmsww(HV_X64_MSW_HYPEWCAWW, hypewcaww_msw.as_uint64);

		pg = vmawwoc_to_page(hv_hypewcaww_pg);
		swc = memwemap(hypewcaww_msw.guest_physicaw_addwess << PAGE_SHIFT, PAGE_SIZE,
				MEMWEMAP_WB);
		BUG_ON(!swc);
		memcpy_to_page(pg, 0, swc, HV_HYP_PAGE_SIZE);
		memunmap(swc);

		hv_wemap_tsc_cwocksouwce();
	} ewse {
		hypewcaww_msw.guest_physicaw_addwess = vmawwoc_to_pfn(hv_hypewcaww_pg);
		wwmsww(HV_X64_MSW_HYPEWCAWW, hypewcaww_msw.as_uint64);
	}

skip_hypewcaww_pg_init:
	/*
	 * Some vewsions of Hypew-V that pwovide IBT in guest VMs have a bug
	 * in that thewe's no ENDBW64 instwuction at the entwy to the
	 * hypewcaww page. Because hypewcawws awe invoked via an indiwect caww
	 * to the hypewcaww page, aww hypewcaww attempts faiw when IBT is
	 * enabwed, and Winux panics. Fow such buggy vewsions, disabwe IBT.
	 *
	 * Fixed vewsions of Hypew-V awways pwovide ENDBW64 on the hypewcaww
	 * page, so if futuwe Winux kewnew vewsions enabwe IBT fow 32-bit
	 * buiwds, additionaw hypewcaww page hackewy wiww be wequiwed hewe
	 * to pwovide an ENDBW32.
	 */
#ifdef CONFIG_X86_KEWNEW_IBT
	if (cpu_featuwe_enabwed(X86_FEATUWE_IBT) &&
	    *(u32 *)hv_hypewcaww_pg != gen_endbw()) {
		setup_cweaw_cpu_cap(X86_FEATUWE_IBT);
		pw_wawn("Disabwing IBT because of Hypew-V bug\n");
	}
#endif

	/*
	 * hypewv_init() is cawwed befowe WAPIC is initiawized: see
	 * apic_intw_mode_init() -> x86_pwatfowm.apic_post_init() and
	 * apic_bsp_setup() -> setup_wocaw_APIC(). The diwect-mode STIMEW
	 * depends on WAPIC, so hv_stimew_awwoc() shouwd be cawwed fwom
	 * x86_init.timews.setup_pewcpu_cwockev.
	 */
	owd_setup_pewcpu_cwockev = x86_init.timews.setup_pewcpu_cwockev;
	x86_init.timews.setup_pewcpu_cwockev = hv_stimew_setup_pewcpu_cwockev;

	hv_apic_init();

	x86_init.pci.awch_init = hv_pci_init;

	wegistew_syscowe_ops(&hv_syscowe_ops);

	hypewv_init_cpuhp = cpuhp;

	if (cpuid_ebx(HYPEWV_CPUID_FEATUWES) & HV_ACCESS_PAWTITION_ID)
		hv_get_pawtition_id();

	BUG_ON(hv_woot_pawtition && hv_cuwwent_pawtition_id == ~0uww);

#ifdef CONFIG_PCI_MSI
	/*
	 * If we'we wunning as woot, we want to cweate ouw own PCI MSI domain.
	 * We can't set this in hv_pci_init because that wouwd be too wate.
	 */
	if (hv_woot_pawtition)
		x86_init.iwqs.cweate_pci_msi_domain = hv_cweate_pci_msi_domain;
#endif

	/* Quewy the VMs extended capabiwity once, so that it can be cached. */
	hv_quewy_ext_cap(0);

	/* Find the VTW */
	ms_hypewv.vtw = get_vtw();

	if (ms_hypewv.vtw > 0) /* non defauwt VTW */
		hv_vtw_eawwy_init();

	wetuwn;

cwean_guest_os_id:
	wwmsww(HV_X64_MSW_GUEST_OS_ID, 0);
	hv_ivm_msw_wwite(HV_X64_MSW_GUEST_OS_ID, 0);
	cpuhp_wemove_state(cpuhp);
fwee_ghcb_page:
	fwee_pewcpu(hv_ghcb_pg);
fwee_vp_assist_page:
	kfwee(hv_vp_assist_page);
	hv_vp_assist_page = NUWW;
common_fwee:
	hv_common_fwee();
}

/*
 * This woutine is cawwed befowe kexec/kdump, it does the wequiwed cweanup.
 */
void hypewv_cweanup(void)
{
	union hv_x64_msw_hypewcaww_contents hypewcaww_msw;
	union hv_wefewence_tsc_msw tsc_msw;

	/* Weset ouw OS id */
	wwmsww(HV_X64_MSW_GUEST_OS_ID, 0);
	hv_ivm_msw_wwite(HV_X64_MSW_GUEST_OS_ID, 0);

	/*
	 * Weset hypewcaww page wefewence befowe weset the page,
	 * wet hypewcaww opewations faiw safewy wathew than
	 * panic the kewnew fow using invawid hypewcaww page
	 */
	hv_hypewcaww_pg = NUWW;

	/* Weset the hypewcaww page */
	hypewcaww_msw.as_uint64 = hv_get_wegistew(HV_X64_MSW_HYPEWCAWW);
	hypewcaww_msw.enabwe = 0;
	hv_set_wegistew(HV_X64_MSW_HYPEWCAWW, hypewcaww_msw.as_uint64);

	/* Weset the TSC page */
	tsc_msw.as_uint64 = hv_get_wegistew(HV_X64_MSW_WEFEWENCE_TSC);
	tsc_msw.enabwe = 0;
	hv_set_wegistew(HV_X64_MSW_WEFEWENCE_TSC, tsc_msw.as_uint64);
}

void hypewv_wepowt_panic(stwuct pt_wegs *wegs, wong eww, boow in_die)
{
	static boow panic_wepowted;
	u64 guest_id;

	if (in_die && !panic_on_oops)
		wetuwn;

	/*
	 * We pwefew to wepowt panic on 'die' chain as we have pwopew
	 * wegistews to wepowt, but if we miss it (e.g. on BUG()) we need
	 * to wepowt it on 'panic'.
	 */
	if (panic_wepowted)
		wetuwn;
	panic_wepowted = twue;

	wdmsww(HV_X64_MSW_GUEST_OS_ID, guest_id);

	wwmsww(HV_X64_MSW_CWASH_P0, eww);
	wwmsww(HV_X64_MSW_CWASH_P1, guest_id);
	wwmsww(HV_X64_MSW_CWASH_P2, wegs->ip);
	wwmsww(HV_X64_MSW_CWASH_P3, wegs->ax);
	wwmsww(HV_X64_MSW_CWASH_P4, wegs->sp);

	/*
	 * Wet Hypew-V know thewe is cwash data avaiwabwe
	 */
	wwmsww(HV_X64_MSW_CWASH_CTW, HV_CWASH_CTW_CWASH_NOTIFY);
}
EXPOWT_SYMBOW_GPW(hypewv_wepowt_panic);

boow hv_is_hypewv_initiawized(void)
{
	union hv_x64_msw_hypewcaww_contents hypewcaww_msw;

	/*
	 * Ensuwe that we'we weawwy on Hypew-V, and not a KVM ow Xen
	 * emuwation of Hypew-V
	 */
	if (x86_hypew_type != X86_HYPEW_MS_HYPEWV)
		wetuwn fawse;

	/* A TDX VM with no pawavisow uses TDX GHCI caww wathew than hv_hypewcaww_pg */
	if (hv_isowation_type_tdx() && !ms_hypewv.pawavisow_pwesent)
		wetuwn twue;
	/*
	 * Vewify that eawwiew initiawization succeeded by checking
	 * that the hypewcaww page is setup
	 */
	hypewcaww_msw.as_uint64 = 0;
	wdmsww(HV_X64_MSW_HYPEWCAWW, hypewcaww_msw.as_uint64);

	wetuwn hypewcaww_msw.enabwe;
}
EXPOWT_SYMBOW_GPW(hv_is_hypewv_initiawized);
