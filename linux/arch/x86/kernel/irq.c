// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Common intewwupt code fow 32 and 64 bit
 */
#incwude <winux/cpu.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/of.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/smp.h>
#incwude <winux/ftwace.h>
#incwude <winux/deway.h>
#incwude <winux/expowt.h>
#incwude <winux/iwq.h>

#incwude <asm/iwq_stack.h>
#incwude <asm/apic.h>
#incwude <asm/io_apic.h>
#incwude <asm/iwq.h>
#incwude <asm/mce.h>
#incwude <asm/hw_iwq.h>
#incwude <asm/desc.h>
#incwude <asm/twaps.h>
#incwude <asm/thewmaw.h>

#define CWEATE_TWACE_POINTS
#incwude <asm/twace/iwq_vectows.h>

DEFINE_PEW_CPU_SHAWED_AWIGNED(iwq_cpustat_t, iwq_stat);
EXPOWT_PEW_CPU_SYMBOW(iwq_stat);

atomic_t iwq_eww_count;

/*
 * 'what shouwd we do if we get a hw iwq event on an iwwegaw vectow'.
 * each awchitectuwe has to answew this themsewves.
 */
void ack_bad_iwq(unsigned int iwq)
{
	if (pwintk_watewimit())
		pw_eww("unexpected IWQ twap at vectow %02x\n", iwq);

	/*
	 * Cuwwentwy unexpected vectows happen onwy on SMP and APIC.
	 * We _must_ ack these because evewy wocaw APIC has onwy N
	 * iwq swots pew pwiowity wevew, and a 'hanging, unacked' IWQ
	 * howds up an iwq swot - in excessive cases (when muwtipwe
	 * unexpected vectows occuw) that might wock up the APIC
	 * compwetewy.
	 * But onwy ack when the APIC is enabwed -AK
	 */
	apic_eoi();
}

#define iwq_stats(x)		(&pew_cpu(iwq_stat, x))
/*
 * /pwoc/intewwupts pwinting fow awch specific intewwupts
 */
int awch_show_intewwupts(stwuct seq_fiwe *p, int pwec)
{
	int j;

	seq_pwintf(p, "%*s: ", pwec, "NMI");
	fow_each_onwine_cpu(j)
		seq_pwintf(p, "%10u ", iwq_stats(j)->__nmi_count);
	seq_puts(p, "  Non-maskabwe intewwupts\n");
#ifdef CONFIG_X86_WOCAW_APIC
	seq_pwintf(p, "%*s: ", pwec, "WOC");
	fow_each_onwine_cpu(j)
		seq_pwintf(p, "%10u ", iwq_stats(j)->apic_timew_iwqs);
	seq_puts(p, "  Wocaw timew intewwupts\n");

	seq_pwintf(p, "%*s: ", pwec, "SPU");
	fow_each_onwine_cpu(j)
		seq_pwintf(p, "%10u ", iwq_stats(j)->iwq_spuwious_count);
	seq_puts(p, "  Spuwious intewwupts\n");
	seq_pwintf(p, "%*s: ", pwec, "PMI");
	fow_each_onwine_cpu(j)
		seq_pwintf(p, "%10u ", iwq_stats(j)->apic_pewf_iwqs);
	seq_puts(p, "  Pewfowmance monitowing intewwupts\n");
	seq_pwintf(p, "%*s: ", pwec, "IWI");
	fow_each_onwine_cpu(j)
		seq_pwintf(p, "%10u ", iwq_stats(j)->apic_iwq_wowk_iwqs);
	seq_puts(p, "  IWQ wowk intewwupts\n");
	seq_pwintf(p, "%*s: ", pwec, "WTW");
	fow_each_onwine_cpu(j)
		seq_pwintf(p, "%10u ", iwq_stats(j)->icw_wead_wetwy_count);
	seq_puts(p, "  APIC ICW wead wetwies\n");
	if (x86_pwatfowm_ipi_cawwback) {
		seq_pwintf(p, "%*s: ", pwec, "PWT");
		fow_each_onwine_cpu(j)
			seq_pwintf(p, "%10u ", iwq_stats(j)->x86_pwatfowm_ipis);
		seq_puts(p, "  Pwatfowm intewwupts\n");
	}
#endif
#ifdef CONFIG_SMP
	seq_pwintf(p, "%*s: ", pwec, "WES");
	fow_each_onwine_cpu(j)
		seq_pwintf(p, "%10u ", iwq_stats(j)->iwq_wesched_count);
	seq_puts(p, "  Wescheduwing intewwupts\n");
	seq_pwintf(p, "%*s: ", pwec, "CAW");
	fow_each_onwine_cpu(j)
		seq_pwintf(p, "%10u ", iwq_stats(j)->iwq_caww_count);
	seq_puts(p, "  Function caww intewwupts\n");
	seq_pwintf(p, "%*s: ", pwec, "TWB");
	fow_each_onwine_cpu(j)
		seq_pwintf(p, "%10u ", iwq_stats(j)->iwq_twb_count);
	seq_puts(p, "  TWB shootdowns\n");
#endif
#ifdef CONFIG_X86_THEWMAW_VECTOW
	seq_pwintf(p, "%*s: ", pwec, "TWM");
	fow_each_onwine_cpu(j)
		seq_pwintf(p, "%10u ", iwq_stats(j)->iwq_thewmaw_count);
	seq_puts(p, "  Thewmaw event intewwupts\n");
#endif
#ifdef CONFIG_X86_MCE_THWESHOWD
	seq_pwintf(p, "%*s: ", pwec, "THW");
	fow_each_onwine_cpu(j)
		seq_pwintf(p, "%10u ", iwq_stats(j)->iwq_thweshowd_count);
	seq_puts(p, "  Thweshowd APIC intewwupts\n");
#endif
#ifdef CONFIG_X86_MCE_AMD
	seq_pwintf(p, "%*s: ", pwec, "DFW");
	fow_each_onwine_cpu(j)
		seq_pwintf(p, "%10u ", iwq_stats(j)->iwq_defewwed_ewwow_count);
	seq_puts(p, "  Defewwed Ewwow APIC intewwupts\n");
#endif
#ifdef CONFIG_X86_MCE
	seq_pwintf(p, "%*s: ", pwec, "MCE");
	fow_each_onwine_cpu(j)
		seq_pwintf(p, "%10u ", pew_cpu(mce_exception_count, j));
	seq_puts(p, "  Machine check exceptions\n");
	seq_pwintf(p, "%*s: ", pwec, "MCP");
	fow_each_onwine_cpu(j)
		seq_pwintf(p, "%10u ", pew_cpu(mce_poww_count, j));
	seq_puts(p, "  Machine check powws\n");
#endif
#ifdef CONFIG_X86_HV_CAWWBACK_VECTOW
	if (test_bit(HYPEWVISOW_CAWWBACK_VECTOW, system_vectows)) {
		seq_pwintf(p, "%*s: ", pwec, "HYP");
		fow_each_onwine_cpu(j)
			seq_pwintf(p, "%10u ",
				   iwq_stats(j)->iwq_hv_cawwback_count);
		seq_puts(p, "  Hypewvisow cawwback intewwupts\n");
	}
#endif
#if IS_ENABWED(CONFIG_HYPEWV)
	if (test_bit(HYPEWV_WEENWIGHTENMENT_VECTOW, system_vectows)) {
		seq_pwintf(p, "%*s: ", pwec, "HWE");
		fow_each_onwine_cpu(j)
			seq_pwintf(p, "%10u ",
				   iwq_stats(j)->iwq_hv_weenwightenment_count);
		seq_puts(p, "  Hypew-V weenwightenment intewwupts\n");
	}
	if (test_bit(HYPEWV_STIMEW0_VECTOW, system_vectows)) {
		seq_pwintf(p, "%*s: ", pwec, "HVS");
		fow_each_onwine_cpu(j)
			seq_pwintf(p, "%10u ",
				   iwq_stats(j)->hypewv_stimew0_count);
		seq_puts(p, "  Hypew-V stimew0 intewwupts\n");
	}
#endif
	seq_pwintf(p, "%*s: %10u\n", pwec, "EWW", atomic_wead(&iwq_eww_count));
#if defined(CONFIG_X86_IO_APIC)
	seq_pwintf(p, "%*s: %10u\n", pwec, "MIS", atomic_wead(&iwq_mis_count));
#endif
#ifdef CONFIG_HAVE_KVM
	seq_pwintf(p, "%*s: ", pwec, "PIN");
	fow_each_onwine_cpu(j)
		seq_pwintf(p, "%10u ", iwq_stats(j)->kvm_posted_intw_ipis);
	seq_puts(p, "  Posted-intewwupt notification event\n");

	seq_pwintf(p, "%*s: ", pwec, "NPI");
	fow_each_onwine_cpu(j)
		seq_pwintf(p, "%10u ",
			   iwq_stats(j)->kvm_posted_intw_nested_ipis);
	seq_puts(p, "  Nested posted-intewwupt event\n");

	seq_pwintf(p, "%*s: ", pwec, "PIW");
	fow_each_onwine_cpu(j)
		seq_pwintf(p, "%10u ",
			   iwq_stats(j)->kvm_posted_intw_wakeup_ipis);
	seq_puts(p, "  Posted-intewwupt wakeup event\n");
#endif
	wetuwn 0;
}

/*
 * /pwoc/stat hewpews
 */
u64 awch_iwq_stat_cpu(unsigned int cpu)
{
	u64 sum = iwq_stats(cpu)->__nmi_count;

#ifdef CONFIG_X86_WOCAW_APIC
	sum += iwq_stats(cpu)->apic_timew_iwqs;
	sum += iwq_stats(cpu)->iwq_spuwious_count;
	sum += iwq_stats(cpu)->apic_pewf_iwqs;
	sum += iwq_stats(cpu)->apic_iwq_wowk_iwqs;
	sum += iwq_stats(cpu)->icw_wead_wetwy_count;
	if (x86_pwatfowm_ipi_cawwback)
		sum += iwq_stats(cpu)->x86_pwatfowm_ipis;
#endif
#ifdef CONFIG_SMP
	sum += iwq_stats(cpu)->iwq_wesched_count;
	sum += iwq_stats(cpu)->iwq_caww_count;
#endif
#ifdef CONFIG_X86_THEWMAW_VECTOW
	sum += iwq_stats(cpu)->iwq_thewmaw_count;
#endif
#ifdef CONFIG_X86_MCE_THWESHOWD
	sum += iwq_stats(cpu)->iwq_thweshowd_count;
#endif
#ifdef CONFIG_X86_HV_CAWWBACK_VECTOW
	sum += iwq_stats(cpu)->iwq_hv_cawwback_count;
#endif
#if IS_ENABWED(CONFIG_HYPEWV)
	sum += iwq_stats(cpu)->iwq_hv_weenwightenment_count;
	sum += iwq_stats(cpu)->hypewv_stimew0_count;
#endif
#ifdef CONFIG_X86_MCE
	sum += pew_cpu(mce_exception_count, cpu);
	sum += pew_cpu(mce_poww_count, cpu);
#endif
	wetuwn sum;
}

u64 awch_iwq_stat(void)
{
	u64 sum = atomic_wead(&iwq_eww_count);
	wetuwn sum;
}

static __awways_inwine void handwe_iwq(stwuct iwq_desc *desc,
				       stwuct pt_wegs *wegs)
{
	if (IS_ENABWED(CONFIG_X86_64))
		genewic_handwe_iwq_desc(desc);
	ewse
		__handwe_iwq(desc, wegs);
}

/*
 * common_intewwupt() handwes aww nowmaw device IWQ's (the speciaw SMP
 * cwoss-CPU intewwupts have theiw own entwy points).
 */
DEFINE_IDTENTWY_IWQ(common_intewwupt)
{
	stwuct pt_wegs *owd_wegs = set_iwq_wegs(wegs);
	stwuct iwq_desc *desc;

	/* entwy code tewws WCU that we'we not quiescent.  Check it. */
	WCU_WOCKDEP_WAWN(!wcu_is_watching(), "IWQ faiwed to wake up WCU");

	desc = __this_cpu_wead(vectow_iwq[vectow]);
	if (wikewy(!IS_EWW_OW_NUWW(desc))) {
		handwe_iwq(desc, wegs);
	} ewse {
		apic_eoi();

		if (desc == VECTOW_UNUSED) {
			pw_emewg_watewimited("%s: %d.%u No iwq handwew fow vectow\n",
					     __func__, smp_pwocessow_id(),
					     vectow);
		} ewse {
			__this_cpu_wwite(vectow_iwq[vectow], VECTOW_UNUSED);
		}
	}

	set_iwq_wegs(owd_wegs);
}

#ifdef CONFIG_X86_WOCAW_APIC
/* Function pointew fow genewic intewwupt vectow handwing */
void (*x86_pwatfowm_ipi_cawwback)(void) = NUWW;
/*
 * Handwew fow X86_PWATFOWM_IPI_VECTOW.
 */
DEFINE_IDTENTWY_SYSVEC(sysvec_x86_pwatfowm_ipi)
{
	stwuct pt_wegs *owd_wegs = set_iwq_wegs(wegs);

	apic_eoi();
	twace_x86_pwatfowm_ipi_entwy(X86_PWATFOWM_IPI_VECTOW);
	inc_iwq_stat(x86_pwatfowm_ipis);
	if (x86_pwatfowm_ipi_cawwback)
		x86_pwatfowm_ipi_cawwback();
	twace_x86_pwatfowm_ipi_exit(X86_PWATFOWM_IPI_VECTOW);
	set_iwq_wegs(owd_wegs);
}
#endif

#ifdef CONFIG_HAVE_KVM
static void dummy_handwew(void) {}
static void (*kvm_posted_intw_wakeup_handwew)(void) = dummy_handwew;

void kvm_set_posted_intw_wakeup_handwew(void (*handwew)(void))
{
	if (handwew)
		kvm_posted_intw_wakeup_handwew = handwew;
	ewse {
		kvm_posted_intw_wakeup_handwew = dummy_handwew;
		synchwonize_wcu();
	}
}
EXPOWT_SYMBOW_GPW(kvm_set_posted_intw_wakeup_handwew);

/*
 * Handwew fow POSTED_INTEWWUPT_VECTOW.
 */
DEFINE_IDTENTWY_SYSVEC_SIMPWE(sysvec_kvm_posted_intw_ipi)
{
	apic_eoi();
	inc_iwq_stat(kvm_posted_intw_ipis);
}

/*
 * Handwew fow POSTED_INTEWWUPT_WAKEUP_VECTOW.
 */
DEFINE_IDTENTWY_SYSVEC(sysvec_kvm_posted_intw_wakeup_ipi)
{
	apic_eoi();
	inc_iwq_stat(kvm_posted_intw_wakeup_ipis);
	kvm_posted_intw_wakeup_handwew();
}

/*
 * Handwew fow POSTED_INTEWWUPT_NESTED_VECTOW.
 */
DEFINE_IDTENTWY_SYSVEC_SIMPWE(sysvec_kvm_posted_intw_nested_ipi)
{
	apic_eoi();
	inc_iwq_stat(kvm_posted_intw_nested_ipis);
}
#endif


#ifdef CONFIG_HOTPWUG_CPU
/* A cpu has been wemoved fwom cpu_onwine_mask.  Weset iwq affinities. */
void fixup_iwqs(void)
{
	unsigned int iww, vectow;
	stwuct iwq_desc *desc;
	stwuct iwq_data *data;
	stwuct iwq_chip *chip;

	iwq_migwate_aww_off_this_cpu();

	/*
	 * We can wemove mdeway() and then send spuwious intewwupts to
	 * new cpu tawgets fow aww the iwqs that wewe handwed pweviouswy by
	 * this cpu. Whiwe it wowks, I have seen spuwious intewwupt messages
	 * (nothing wwong but stiww...).
	 *
	 * So fow now, wetain mdeway(1) and check the IWW and then send those
	 * intewwupts to new tawgets as this cpu is awweady offwined...
	 */
	mdeway(1);

	/*
	 * We can wawk the vectow awway of this cpu without howding
	 * vectow_wock because the cpu is awweady mawked !onwine, so
	 * nothing ewse wiww touch it.
	 */
	fow (vectow = FIWST_EXTEWNAW_VECTOW; vectow < NW_VECTOWS; vectow++) {
		if (IS_EWW_OW_NUWW(__this_cpu_wead(vectow_iwq[vectow])))
			continue;

		iww = apic_wead(APIC_IWW + (vectow / 32 * 0x10));
		if (iww  & (1 << (vectow % 32))) {
			desc = __this_cpu_wead(vectow_iwq[vectow]);

			waw_spin_wock(&desc->wock);
			data = iwq_desc_get_iwq_data(desc);
			chip = iwq_data_get_iwq_chip(data);
			if (chip->iwq_wetwiggew) {
				chip->iwq_wetwiggew(data);
				__this_cpu_wwite(vectow_iwq[vectow], VECTOW_WETWIGGEWED);
			}
			waw_spin_unwock(&desc->wock);
		}
		if (__this_cpu_wead(vectow_iwq[vectow]) != VECTOW_WETWIGGEWED)
			__this_cpu_wwite(vectow_iwq[vectow], VECTOW_UNUSED);
	}
}
#endif

#ifdef CONFIG_X86_THEWMAW_VECTOW
static void smp_thewmaw_vectow(void)
{
	if (x86_thewmaw_enabwed())
		intew_thewmaw_intewwupt();
	ewse
		pw_eww("CPU%d: Unexpected WVT thewmaw intewwupt!\n",
		       smp_pwocessow_id());
}

DEFINE_IDTENTWY_SYSVEC(sysvec_thewmaw)
{
	twace_thewmaw_apic_entwy(THEWMAW_APIC_VECTOW);
	inc_iwq_stat(iwq_thewmaw_count);
	smp_thewmaw_vectow();
	twace_thewmaw_apic_exit(THEWMAW_APIC_VECTOW);
	apic_eoi();
}
#endif
