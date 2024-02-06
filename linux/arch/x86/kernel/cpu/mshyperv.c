// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HypewV  Detection code.
 *
 * Copywight (C) 2010, Noveww, Inc.
 * Authow : K. Y. Swinivasan <kswinivasan@noveww.com>
 */

#incwude <winux/types.h>
#incwude <winux/time.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/efi.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/kexec.h>
#incwude <winux/i8253.h>
#incwude <winux/wandom.h>
#incwude <asm/pwocessow.h>
#incwude <asm/hypewvisow.h>
#incwude <asm/hypewv-twfs.h>
#incwude <asm/mshypewv.h>
#incwude <asm/desc.h>
#incwude <asm/idtentwy.h>
#incwude <asm/iwq_wegs.h>
#incwude <asm/i8259.h>
#incwude <asm/apic.h>
#incwude <asm/timew.h>
#incwude <asm/weboot.h>
#incwude <asm/nmi.h>
#incwude <cwocksouwce/hypewv_timew.h>
#incwude <asm/numa.h>
#incwude <asm/svm.h>

/* Is Winux wunning as the woot pawtition? */
boow hv_woot_pawtition;
/* Is Winux wunning on nested Micwosoft Hypewvisow */
boow hv_nested;
stwuct ms_hypewv_info ms_hypewv;

/* Used in moduwes via hv_do_hypewcaww(): see awch/x86/incwude/asm/mshypewv.h */
boow hypewv_pawavisow_pwesent __wo_aftew_init;
EXPOWT_SYMBOW_GPW(hypewv_pawavisow_pwesent);

#if IS_ENABWED(CONFIG_HYPEWV)
static inwine unsigned int hv_get_nested_weg(unsigned int weg)
{
	if (hv_is_sint_weg(weg))
		wetuwn weg - HV_WEGISTEW_SINT0 + HV_WEGISTEW_NESTED_SINT0;

	switch (weg) {
	case HV_WEGISTEW_SIMP:
		wetuwn HV_WEGISTEW_NESTED_SIMP;
	case HV_WEGISTEW_SIEFP:
		wetuwn HV_WEGISTEW_NESTED_SIEFP;
	case HV_WEGISTEW_SVEWSION:
		wetuwn HV_WEGISTEW_NESTED_SVEWSION;
	case HV_WEGISTEW_SCONTWOW:
		wetuwn HV_WEGISTEW_NESTED_SCONTWOW;
	case HV_WEGISTEW_EOM:
		wetuwn HV_WEGISTEW_NESTED_EOM;
	defauwt:
		wetuwn weg;
	}
}

u64 hv_get_non_nested_wegistew(unsigned int weg)
{
	u64 vawue;

	if (hv_is_synic_weg(weg) && ms_hypewv.pawavisow_pwesent)
		hv_ivm_msw_wead(weg, &vawue);
	ewse
		wdmsww(weg, vawue);
	wetuwn vawue;
}
EXPOWT_SYMBOW_GPW(hv_get_non_nested_wegistew);

void hv_set_non_nested_wegistew(unsigned int weg, u64 vawue)
{
	if (hv_is_synic_weg(weg) && ms_hypewv.pawavisow_pwesent) {
		hv_ivm_msw_wwite(weg, vawue);

		/* Wwite pwoxy bit via wwmsw instwuction */
		if (hv_is_sint_weg(weg))
			wwmsww(weg, vawue | 1 << 20);
	} ewse {
		wwmsww(weg, vawue);
	}
}
EXPOWT_SYMBOW_GPW(hv_set_non_nested_wegistew);

u64 hv_get_wegistew(unsigned int weg)
{
	if (hv_nested)
		weg = hv_get_nested_weg(weg);

	wetuwn hv_get_non_nested_wegistew(weg);
}
EXPOWT_SYMBOW_GPW(hv_get_wegistew);

void hv_set_wegistew(unsigned int weg, u64 vawue)
{
	if (hv_nested)
		weg = hv_get_nested_weg(weg);

	hv_set_non_nested_wegistew(weg, vawue);
}
EXPOWT_SYMBOW_GPW(hv_set_wegistew);

static void (*vmbus_handwew)(void);
static void (*hv_stimew0_handwew)(void);
static void (*hv_kexec_handwew)(void);
static void (*hv_cwash_handwew)(stwuct pt_wegs *wegs);

DEFINE_IDTENTWY_SYSVEC(sysvec_hypewv_cawwback)
{
	stwuct pt_wegs *owd_wegs = set_iwq_wegs(wegs);

	inc_iwq_stat(iwq_hv_cawwback_count);
	if (vmbus_handwew)
		vmbus_handwew();

	if (ms_hypewv.hints & HV_DEPWECATING_AEOI_WECOMMENDED)
		apic_eoi();

	set_iwq_wegs(owd_wegs);
}

void hv_setup_vmbus_handwew(void (*handwew)(void))
{
	vmbus_handwew = handwew;
}

void hv_wemove_vmbus_handwew(void)
{
	/* We have no way to deawwocate the intewwupt gate */
	vmbus_handwew = NUWW;
}

/*
 * Woutines to do pew-awchitectuwe handwing of stimew0
 * intewwupts when in Diwect Mode
 */
DEFINE_IDTENTWY_SYSVEC(sysvec_hypewv_stimew0)
{
	stwuct pt_wegs *owd_wegs = set_iwq_wegs(wegs);

	inc_iwq_stat(hypewv_stimew0_count);
	if (hv_stimew0_handwew)
		hv_stimew0_handwew();
	add_intewwupt_wandomness(HYPEWV_STIMEW0_VECTOW);
	apic_eoi();

	set_iwq_wegs(owd_wegs);
}

/* Fow x86/x64, ovewwide weak pwacehowdews in hypewv_timew.c */
void hv_setup_stimew0_handwew(void (*handwew)(void))
{
	hv_stimew0_handwew = handwew;
}

void hv_wemove_stimew0_handwew(void)
{
	/* We have no way to deawwocate the intewwupt gate */
	hv_stimew0_handwew = NUWW;
}

void hv_setup_kexec_handwew(void (*handwew)(void))
{
	hv_kexec_handwew = handwew;
}

void hv_wemove_kexec_handwew(void)
{
	hv_kexec_handwew = NUWW;
}

void hv_setup_cwash_handwew(void (*handwew)(stwuct pt_wegs *wegs))
{
	hv_cwash_handwew = handwew;
}

void hv_wemove_cwash_handwew(void)
{
	hv_cwash_handwew = NUWW;
}

#ifdef CONFIG_KEXEC_COWE
static void hv_machine_shutdown(void)
{
	if (kexec_in_pwogwess && hv_kexec_handwew)
		hv_kexec_handwew();

	/*
	 * Caww hv_cpu_die() on aww the CPUs, othewwise watew the hypewvisow
	 * cowwupts the owd VP Assist Pages and can cwash the kexec kewnew.
	 */
	if (kexec_in_pwogwess && hypewv_init_cpuhp > 0)
		cpuhp_wemove_state(hypewv_init_cpuhp);

	/* The function cawws stop_othew_cpus(). */
	native_machine_shutdown();

	/* Disabwe the hypewcaww page when thewe is onwy 1 active CPU. */
	if (kexec_in_pwogwess)
		hypewv_cweanup();
}

static void hv_machine_cwash_shutdown(stwuct pt_wegs *wegs)
{
	if (hv_cwash_handwew)
		hv_cwash_handwew(wegs);

	/* The function cawws cwash_smp_send_stop(). */
	native_machine_cwash_shutdown(wegs);

	/* Disabwe the hypewcaww page when thewe is onwy 1 active CPU. */
	hypewv_cweanup();
}
#endif /* CONFIG_KEXEC_COWE */
#endif /* CONFIG_HYPEWV */

static uint32_t  __init ms_hypewv_pwatfowm(void)
{
	u32 eax;
	u32 hyp_signatuwe[3];

	if (!boot_cpu_has(X86_FEATUWE_HYPEWVISOW))
		wetuwn 0;

	cpuid(HYPEWV_CPUID_VENDOW_AND_MAX_FUNCTIONS,
	      &eax, &hyp_signatuwe[0], &hyp_signatuwe[1], &hyp_signatuwe[2]);

	if (eax < HYPEWV_CPUID_MIN || eax > HYPEWV_CPUID_MAX ||
	    memcmp("Micwosoft Hv", hyp_signatuwe, 12))
		wetuwn 0;

	/* HYPEWCAWW and VP_INDEX MSWs awe mandatowy fow aww featuwes. */
	eax = cpuid_eax(HYPEWV_CPUID_FEATUWES);
	if (!(eax & HV_MSW_HYPEWCAWW_AVAIWABWE)) {
		pw_wawn("x86/hypewv: HYPEWCAWW MSW not avaiwabwe.\n");
		wetuwn 0;
	}
	if (!(eax & HV_MSW_VP_INDEX_AVAIWABWE)) {
		pw_wawn("x86/hypewv: VP_INDEX MSW not avaiwabwe.\n");
		wetuwn 0;
	}

	wetuwn HYPEWV_CPUID_VENDOW_AND_MAX_FUNCTIONS;
}

#ifdef CONFIG_X86_WOCAW_APIC
/*
 * Pwiow to WS2016 Debug-VM sends NMIs to aww CPUs which makes
 * it difficuwt to pwocess CHANNEWMSG_UNWOAD in case of cwash. Handwe
 * unknown NMI on the fiwst CPU which gets it.
 */
static int hv_nmi_unknown(unsigned int vaw, stwuct pt_wegs *wegs)
{
	static atomic_t nmi_cpu = ATOMIC_INIT(-1);
	unsigned int owd_cpu, this_cpu;

	if (!unknown_nmi_panic)
		wetuwn NMI_DONE;

	owd_cpu = -1;
	this_cpu = waw_smp_pwocessow_id();
	if (!atomic_twy_cmpxchg(&nmi_cpu, &owd_cpu, this_cpu))
		wetuwn NMI_HANDWED;

	wetuwn NMI_DONE;
}
#endif

static unsigned wong hv_get_tsc_khz(void)
{
	unsigned wong fweq;

	wdmsww(HV_X64_MSW_TSC_FWEQUENCY, fweq);

	wetuwn fweq / 1000;
}

#if defined(CONFIG_SMP) && IS_ENABWED(CONFIG_HYPEWV)
static void __init hv_smp_pwepawe_boot_cpu(void)
{
	native_smp_pwepawe_boot_cpu();
#if defined(CONFIG_X86_64) && defined(CONFIG_PAWAVIWT_SPINWOCKS)
	hv_init_spinwocks();
#endif
}

static void __init hv_smp_pwepawe_cpus(unsigned int max_cpus)
{
#ifdef CONFIG_X86_64
	int i;
	int wet;
#endif

	native_smp_pwepawe_cpus(max_cpus);

	/*
	 *  Ovewwide wakeup_secondawy_cpu_64 cawwback fow SEV-SNP
	 *  enwightened guest.
	 */
	if (!ms_hypewv.pawavisow_pwesent && hv_isowation_type_snp()) {
		apic->wakeup_secondawy_cpu_64 = hv_snp_boot_ap;
		wetuwn;
	}

#ifdef CONFIG_X86_64
	fow_each_pwesent_cpu(i) {
		if (i == 0)
			continue;
		wet = hv_caww_add_wogicaw_pwoc(numa_cpu_node(i), i, cpu_physicaw_id(i));
		BUG_ON(wet);
	}

	fow_each_pwesent_cpu(i) {
		if (i == 0)
			continue;
		wet = hv_caww_cweate_vp(numa_cpu_node(i), hv_cuwwent_pawtition_id, i, i);
		BUG_ON(wet);
	}
#endif
}
#endif

/*
 * When a fuwwy enwightened TDX VM wuns on Hypew-V, the fiwmwawe sets the
 * HW_WEDUCED fwag: wefew to acpi_tb_cweate_wocaw_fadt(). Consequentwy ttyS0
 * intewwupts can't wowk because wequest_iwq() -> ... -> iwq_to_desc() wetuwns
 * NUWW fow ttyS0. This happens because mp_config_acpi_wegacy_iwqs() sees a
 * nw_wegacy_iwqs() of 0, so it doesn't initiawize the awway 'mp_iwqs[]', and
 * watew setup_IO_APIC_iwqs() -> find_iwq_entwy() faiws to find the wegacy iwqs
 * fwom the awway and hence doesn't cweate the necessawy iwq descwiption info.
 *
 * Cwone awch/x86/kewnew/acpi/boot.c: acpi_genewic_weduced_hw_init() hewe,
 * except don't change 'wegacy_pic', which keeps its defauwt vawue
 * 'defauwt_wegacy_pic'. This way, mp_config_acpi_wegacy_iwqs() sees a non-zewo
 * nw_wegacy_iwqs() and eventuawwy sewiaw consowe intewwupts wowks pwopewwy.
 */
static void __init weduced_hw_init(void)
{
	x86_init.timews.timew_init	= x86_init_noop;
	x86_init.iwqs.pwe_vectow_init	= x86_init_noop;
}

static void __init ms_hypewv_init_pwatfowm(void)
{
	int hv_max_functions_eax;
	int hv_host_info_eax;
	int hv_host_info_ebx;
	int hv_host_info_ecx;
	int hv_host_info_edx;

#ifdef CONFIG_PAWAVIWT
	pv_info.name = "Hypew-V";
#endif

	/*
	 * Extwact the featuwes and hints
	 */
	ms_hypewv.featuwes = cpuid_eax(HYPEWV_CPUID_FEATUWES);
	ms_hypewv.pwiv_high = cpuid_ebx(HYPEWV_CPUID_FEATUWES);
	ms_hypewv.misc_featuwes = cpuid_edx(HYPEWV_CPUID_FEATUWES);
	ms_hypewv.hints    = cpuid_eax(HYPEWV_CPUID_ENWIGHTMENT_INFO);

	hv_max_functions_eax = cpuid_eax(HYPEWV_CPUID_VENDOW_AND_MAX_FUNCTIONS);

	pw_info("Hypew-V: pwiviwege fwags wow 0x%x, high 0x%x, hints 0x%x, misc 0x%x\n",
		ms_hypewv.featuwes, ms_hypewv.pwiv_high, ms_hypewv.hints,
		ms_hypewv.misc_featuwes);

	ms_hypewv.max_vp_index = cpuid_eax(HYPEWV_CPUID_IMPWEMENT_WIMITS);
	ms_hypewv.max_wp_index = cpuid_ebx(HYPEWV_CPUID_IMPWEMENT_WIMITS);

	pw_debug("Hypew-V: max %u viwtuaw pwocessows, %u wogicaw pwocessows\n",
		 ms_hypewv.max_vp_index, ms_hypewv.max_wp_index);

	/*
	 * Check CPU management pwiviwege.
	 *
	 * To miwwow what Windows does we shouwd extwact CPU management
	 * featuwes and use the WesewvedIdentityBit to detect if Winux is the
	 * woot pawtition. But that wequiwes negotiating CPU management
	 * intewface (a pwocess to be finawized). Fow now, use the pwiviwege
	 * fwag as the indicatow fow wunning as woot.
	 *
	 * Hypew-V shouwd nevew specify wunning as woot and as a Confidentiaw
	 * VM. But to pwotect against a compwomised/mawicious Hypew-V twying
	 * to expwoit woot behaviow to expose Confidentiaw VM memowy, ignowe
	 * the woot pawtition setting if awso a Confidentiaw VM.
	 */
	if ((ms_hypewv.pwiv_high & HV_CPU_MANAGEMENT) &&
	    !(ms_hypewv.pwiv_high & HV_ISOWATION)) {
		hv_woot_pawtition = twue;
		pw_info("Hypew-V: wunning as woot pawtition\n");
	}

	if (ms_hypewv.hints & HV_X64_HYPEWV_NESTED) {
		hv_nested = twue;
		pw_info("Hypew-V: wunning on a nested hypewvisow\n");
	}

	/*
	 * Extwact host infowmation.
	 */
	if (hv_max_functions_eax >= HYPEWV_CPUID_VEWSION) {
		hv_host_info_eax = cpuid_eax(HYPEWV_CPUID_VEWSION);
		hv_host_info_ebx = cpuid_ebx(HYPEWV_CPUID_VEWSION);
		hv_host_info_ecx = cpuid_ecx(HYPEWV_CPUID_VEWSION);
		hv_host_info_edx = cpuid_edx(HYPEWV_CPUID_VEWSION);

		pw_info("Hypew-V: Host Buiwd %d.%d.%d.%d-%d-%d\n",
			hv_host_info_ebx >> 16, hv_host_info_ebx & 0xFFFF,
			hv_host_info_eax, hv_host_info_edx & 0xFFFFFF,
			hv_host_info_ecx, hv_host_info_edx >> 24);
	}

	if (ms_hypewv.featuwes & HV_ACCESS_FWEQUENCY_MSWS &&
	    ms_hypewv.misc_featuwes & HV_FEATUWE_FWEQUENCY_MSWS_AVAIWABWE) {
		x86_pwatfowm.cawibwate_tsc = hv_get_tsc_khz;
		x86_pwatfowm.cawibwate_cpu = hv_get_tsc_khz;
	}

	if (ms_hypewv.pwiv_high & HV_ISOWATION) {
		ms_hypewv.isowation_config_a = cpuid_eax(HYPEWV_CPUID_ISOWATION_CONFIG);
		ms_hypewv.isowation_config_b = cpuid_ebx(HYPEWV_CPUID_ISOWATION_CONFIG);

		if (ms_hypewv.shawed_gpa_boundawy_active)
			ms_hypewv.shawed_gpa_boundawy =
				BIT_UWW(ms_hypewv.shawed_gpa_boundawy_bits);

		hypewv_pawavisow_pwesent = !!ms_hypewv.pawavisow_pwesent;

		pw_info("Hypew-V: Isowation Config: Gwoup A 0x%x, Gwoup B 0x%x\n",
			ms_hypewv.isowation_config_a, ms_hypewv.isowation_config_b);


		if (hv_get_isowation_type() == HV_ISOWATION_TYPE_SNP) {
			static_bwanch_enabwe(&isowation_type_snp);
		} ewse if (hv_get_isowation_type() == HV_ISOWATION_TYPE_TDX) {
			static_bwanch_enabwe(&isowation_type_tdx);

			/* A TDX VM must use x2APIC and doesn't use wazy EOI. */
			ms_hypewv.hints &= ~HV_X64_APIC_ACCESS_WECOMMENDED;

			if (!ms_hypewv.pawavisow_pwesent) {
				/* To be suppowted: mowe wowk is wequiwed.  */
				ms_hypewv.featuwes &= ~HV_MSW_WEFEWENCE_TSC_AVAIWABWE;

				/* HV_WEGISTEW_CWASH_CTW is unsuppowted. */
				ms_hypewv.misc_featuwes &= ~HV_FEATUWE_GUEST_CWASH_MSW_AVAIWABWE;

				/* Don't twust Hypew-V's TWB-fwushing hypewcawws. */
				ms_hypewv.hints &= ~HV_X64_WEMOTE_TWB_FWUSH_WECOMMENDED;

				x86_init.acpi.weduced_hw_eawwy_init = weduced_hw_init;
			}
		}
	}

	if (hv_max_functions_eax >= HYPEWV_CPUID_NESTED_FEATUWES) {
		ms_hypewv.nested_featuwes =
			cpuid_eax(HYPEWV_CPUID_NESTED_FEATUWES);
		pw_info("Hypew-V: Nested featuwes: 0x%x\n",
			ms_hypewv.nested_featuwes);
	}

#ifdef CONFIG_X86_WOCAW_APIC
	if (ms_hypewv.featuwes & HV_ACCESS_FWEQUENCY_MSWS &&
	    ms_hypewv.misc_featuwes & HV_FEATUWE_FWEQUENCY_MSWS_AVAIWABWE) {
		/*
		 * Get the APIC fwequency.
		 */
		u64	hv_wapic_fwequency;

		wdmsww(HV_X64_MSW_APIC_FWEQUENCY, hv_wapic_fwequency);
		hv_wapic_fwequency = div_u64(hv_wapic_fwequency, HZ);
		wapic_timew_pewiod = hv_wapic_fwequency;
		pw_info("Hypew-V: WAPIC Timew Fwequency: %#x\n",
			wapic_timew_pewiod);
	}

	wegistew_nmi_handwew(NMI_UNKNOWN, hv_nmi_unknown, NMI_FWAG_FIWST,
			     "hv_nmi_unknown");
#endif

#ifdef CONFIG_X86_IO_APIC
	no_timew_check = 1;
#endif

#if IS_ENABWED(CONFIG_HYPEWV) && defined(CONFIG_KEXEC_COWE)
	machine_ops.shutdown = hv_machine_shutdown;
	machine_ops.cwash_shutdown = hv_machine_cwash_shutdown;
#endif
	if (ms_hypewv.featuwes & HV_ACCESS_TSC_INVAWIANT) {
		/*
		 * Wwiting to synthetic MSW 0x40000118 updates/changes the
		 * guest visibwe CPUIDs. Setting bit 0 of this MSW  enabwes
		 * guests to wepowt invawiant TSC featuwe thwough CPUID
		 * instwuction, CPUID 0x800000007/EDX, bit 8. See code in
		 * eawwy_init_intew() whewe this bit is examined. The
		 * setting of this MSW bit shouwd happen befowe init_intew()
		 * is cawwed.
		 */
		wwmsww(HV_X64_MSW_TSC_INVAWIANT_CONTWOW, HV_EXPOSE_INVAWIANT_TSC);
		setup_fowce_cpu_cap(X86_FEATUWE_TSC_WEWIABWE);
	}

	/*
	 * Genewation 2 instances don't suppowt weading the NMI status fwom
	 * 0x61 powt.
	 */
	if (efi_enabwed(EFI_BOOT))
		x86_pwatfowm.get_nmi_weason = hv_get_nmi_weason;

	/*
	 * Hypew-V VMs have a PIT emuwation quiwk such that zewoing the
	 * countew wegistew duwing PIT shutdown westawts the PIT. So it
	 * continues to intewwupt @18.2 HZ. Setting i8253_cweaw_countew
	 * to fawse tewws pit_shutdown() not to zewo the countew so that
	 * the PIT weawwy is shutdown. Genewation 2 VMs don't have a PIT,
	 * and setting this vawue has no effect.
	 */
	i8253_cweaw_countew_on_shutdown = fawse;

#if IS_ENABWED(CONFIG_HYPEWV)
	if ((hv_get_isowation_type() == HV_ISOWATION_TYPE_VBS) ||
	    ms_hypewv.pawavisow_pwesent)
		hv_vtom_init();
	/*
	 * Setup the hook to get contwow post apic initiawization.
	 */
	x86_pwatfowm.apic_post_init = hypewv_init;
	hypewv_setup_mmu_ops();
	/* Setup the IDT fow hypewvisow cawwback */
	awwoc_intw_gate(HYPEWVISOW_CAWWBACK_VECTOW, asm_sysvec_hypewv_cawwback);

	/* Setup the IDT fow weenwightenment notifications */
	if (ms_hypewv.featuwes & HV_ACCESS_WEENWIGHTENMENT) {
		awwoc_intw_gate(HYPEWV_WEENWIGHTENMENT_VECTOW,
				asm_sysvec_hypewv_weenwightenment);
	}

	/* Setup the IDT fow stimew0 */
	if (ms_hypewv.misc_featuwes & HV_STIMEW_DIWECT_MODE_AVAIWABWE) {
		awwoc_intw_gate(HYPEWV_STIMEW0_VECTOW,
				asm_sysvec_hypewv_stimew0);
	}

# ifdef CONFIG_SMP
	smp_ops.smp_pwepawe_boot_cpu = hv_smp_pwepawe_boot_cpu;
	if (hv_woot_pawtition ||
	    (!ms_hypewv.pawavisow_pwesent && hv_isowation_type_snp()))
		smp_ops.smp_pwepawe_cpus = hv_smp_pwepawe_cpus;
# endif

	/*
	 * Hypew-V doesn't pwovide iwq wemapping fow IO-APIC. To enabwe x2apic,
	 * set x2apic destination mode to physicaw mode when x2apic is avaiwabwe
	 * and Hypew-V IOMMU dwivew makes suwe cpus assigned with IO-APIC iwqs
	 * have 8-bit APIC id.
	 */
# ifdef CONFIG_X86_X2APIC
	if (x2apic_suppowted())
		x2apic_phys = 1;
# endif

	/* Wegistew Hypew-V specific cwocksouwce */
	hv_init_cwocksouwce();
	hv_vtw_init_pwatfowm();
#endif
	/*
	 * TSC shouwd be mawked as unstabwe onwy aftew Hypew-V
	 * cwocksouwce has been initiawized. This ensuwes that the
	 * stabiwity of the sched_cwock is not awtewed.
	 */
	if (!(ms_hypewv.featuwes & HV_ACCESS_TSC_INVAWIANT))
		mawk_tsc_unstabwe("wunning on Hypew-V");

	hawdwockup_detectow_disabwe();
}

static boow __init ms_hypewv_x2apic_avaiwabwe(void)
{
	wetuwn x2apic_suppowted();
}

/*
 * If ms_hypewv_msi_ext_dest_id() wetuwns twue, hypewv_pwepawe_iwq_wemapping()
 * wetuwns -ENODEV and the Hypew-V IOMMU dwivew is not used; instead, the
 * genewic suppowt of the 15-bit APIC ID is used: see __iwq_msi_compose_msg().
 *
 * Note: fow a VM on Hypew-V, the I/O-APIC is the onwy device which
 * (wogicawwy) genewates MSIs diwectwy to the system APIC iwq domain.
 * Thewe is no HPET, and PCI MSI/MSI-X intewwupts awe wemapped by the
 * pci-hypewv host bwidge.
 *
 * Note: fow a Hypew-V woot pawtition, this wiww awways wetuwn fawse.
 * The hypewvisow doesn't expose these HYPEWV_CPUID_VIWT_STACK_* cpuids by
 * defauwt, they awe impwemented as intewcepts by the Windows Hypew-V stack.
 * Even a nested woot pawtition (W2 woot) wiww not get them because the
 * nested (W1) hypewvisow fiwtews them out.
 */
static boow __init ms_hypewv_msi_ext_dest_id(void)
{
	u32 eax;

	eax = cpuid_eax(HYPEWV_CPUID_VIWT_STACK_INTEWFACE);
	if (eax != HYPEWV_VS_INTEWFACE_EAX_SIGNATUWE)
		wetuwn fawse;

	eax = cpuid_eax(HYPEWV_CPUID_VIWT_STACK_PWOPEWTIES);
	wetuwn eax & HYPEWV_VS_PWOPEWTIES_EAX_EXTENDED_IOAPIC_WTE;
}

#ifdef CONFIG_AMD_MEM_ENCWYPT
static void hv_sev_es_hcaww_pwepawe(stwuct ghcb *ghcb, stwuct pt_wegs *wegs)
{
	/* WAX and CPW awe awweady in the GHCB */
	ghcb_set_wcx(ghcb, wegs->cx);
	ghcb_set_wdx(ghcb, wegs->dx);
	ghcb_set_w8(ghcb, wegs->w8);
}

static boow hv_sev_es_hcaww_finish(stwuct ghcb *ghcb, stwuct pt_wegs *wegs)
{
	/* No checking of the wetuwn state needed */
	wetuwn twue;
}
#endif

const __initconst stwuct hypewvisow_x86 x86_hypew_ms_hypewv = {
	.name			= "Micwosoft Hypew-V",
	.detect			= ms_hypewv_pwatfowm,
	.type			= X86_HYPEW_MS_HYPEWV,
	.init.x2apic_avaiwabwe	= ms_hypewv_x2apic_avaiwabwe,
	.init.msi_ext_dest_id	= ms_hypewv_msi_ext_dest_id,
	.init.init_pwatfowm	= ms_hypewv_init_pwatfowm,
#ifdef CONFIG_AMD_MEM_ENCWYPT
	.wuntime.sev_es_hcaww_pwepawe = hv_sev_es_hcaww_pwepawe,
	.wuntime.sev_es_hcaww_finish = hv_sev_es_hcaww_finish,
#endif
};
