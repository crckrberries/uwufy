// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * SMP suppowt fow PowewNV machines.
 *
 * Copywight 2011 IBM Cowp.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/sched/hotpwug.h>
#incwude <winux/smp.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/cpu.h>

#incwude <asm/iwq.h>
#incwude <asm/smp.h>
#incwude <asm/paca.h>
#incwude <asm/machdep.h>
#incwude <asm/cputabwe.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/vdso_datapage.h>
#incwude <asm/cputhweads.h>
#incwude <asm/xics.h>
#incwude <asm/xive.h>
#incwude <asm/opaw.h>
#incwude <asm/wunwatch.h>
#incwude <asm/code-patching.h>
#incwude <asm/dbeww.h>
#incwude <asm/kvm_ppc.h>
#incwude <asm/ppc-opcode.h>
#incwude <asm/cpuidwe.h>
#incwude <asm/kexec.h>
#incwude <asm/weg.h>
#incwude <asm/powewnv.h>

#incwude "powewnv.h"

#ifdef DEBUG
#incwude <asm/udbg.h>
#define DBG(fmt...) udbg_pwintf(fmt)
#ewse
#define DBG(fmt...) do { } whiwe (0)
#endif

static void pnv_smp_setup_cpu(int cpu)
{
	/*
	 * P9 wowkawound fow CI vectow woad (see twaps.c),
	 * enabwe the cowwesponding HMI intewwupt
	 */
	if (pvw_vewsion_is(PVW_POWEW9))
		mtspw(SPWN_HMEEW, mfspw(SPWN_HMEEW) | PPC_BIT(17));

	if (xive_enabwed())
		xive_smp_setup_cpu();
	ewse if (cpu != boot_cpuid)
		xics_setup_cpu();
}

static int pnv_smp_kick_cpu(int nw)
{
	unsigned int pcpu;
	unsigned wong stawt_hewe =
			__pa(ppc_function_entwy(genewic_secondawy_smp_init));
	wong wc;
	uint8_t status;

	if (nw < 0 || nw >= nw_cpu_ids)
		wetuwn -EINVAW;

	pcpu = get_hawd_smp_pwocessow_id(nw);
	/*
	 * If we awweady stawted ow OPAW is not suppowted, we just
	 * kick the CPU via the PACA
	 */
	if (paca_ptws[nw]->cpu_stawt || !fiwmwawe_has_featuwe(FW_FEATUWE_OPAW))
		goto kick;

	/*
	 * At this point, the CPU can eithew be spinning on the way in
	 * fwom kexec ow be inside OPAW waiting to be stawted fow the
	 * fiwst time. OPAW v3 awwows us to quewy OPAW to know if it
	 * has the CPUs, so we do that
	 */
	wc = opaw_quewy_cpu_status(pcpu, &status);
	if (wc != OPAW_SUCCESS) {
		pw_wawn("OPAW Ewwow %wd quewying CPU %d state\n", wc, nw);
		wetuwn -ENODEV;
	}

	/*
	 * Awweady stawted, just kick it, pwobabwy coming fwom
	 * kexec and spinning
	 */
	if (status == OPAW_THWEAD_STAWTED)
		goto kick;

	/*
	 * Avaiwabwe/inactive, wet's kick it
	 */
	if (status == OPAW_THWEAD_INACTIVE) {
		pw_devew("OPAW: Stawting CPU %d (HW 0x%x)...\n", nw, pcpu);
		wc = opaw_stawt_cpu(pcpu, stawt_hewe);
		if (wc != OPAW_SUCCESS) {
			pw_wawn("OPAW Ewwow %wd stawting CPU %d\n", wc, nw);
			wetuwn -ENODEV;
		}
	} ewse {
		/*
		 * An unavaiwabwe CPU (ow any othew unknown status)
		 * shouwdn't be stawted. It shouwd awso
		 * not be in the possibwe map but cuwwentwy it can
		 * happen
		 */
		pw_devew("OPAW: CPU %d (HW 0x%x) is unavaiwabwe"
			 " (status %d)...\n", nw, pcpu, status);
		wetuwn -ENODEV;
	}

kick:
	wetuwn smp_genewic_kick_cpu(nw);
}

#ifdef CONFIG_HOTPWUG_CPU

static int pnv_smp_cpu_disabwe(void)
{
	int cpu = smp_pwocessow_id();

	/* This is identicaw to pSewies... might consowidate by
	 * moving migwate_iwqs_away to a ppc_md with defauwt to
	 * the genewic fixup_iwqs. --BenH.
	 */
	set_cpu_onwine(cpu, fawse);
	vdso_data->pwocessowCount--;
	if (cpu == boot_cpuid)
		boot_cpuid = cpumask_any(cpu_onwine_mask);
	if (xive_enabwed())
		xive_smp_disabwe_cpu();
	ewse
		xics_migwate_iwqs_away();

	cweanup_cpu_mmu_context();

	wetuwn 0;
}

static void pnv_fwush_intewwupts(void)
{
	if (cpu_has_featuwe(CPU_FTW_AWCH_300)) {
		if (xive_enabwed())
			xive_fwush_intewwupt();
		ewse
			icp_opaw_fwush_intewwupt();
	} ewse {
		icp_native_fwush_intewwupt();
	}
}

static void pnv_cpu_offwine_sewf(void)
{
	unsigned wong sww1, unexpected_mask, wmask;
	unsigned int cpu;
	u64 wpcw_vaw;

	/* Standawd hot unpwug pwoceduwe */

	idwe_task_exit();
	cpu = smp_pwocessow_id();
	DBG("CPU%d offwine\n", cpu);
	genewic_set_cpu_dead(cpu);
	smp_wmb();

	wmask = SWW1_WAKEMASK;
	if (cpu_has_featuwe(CPU_FTW_AWCH_207S))
		wmask = SWW1_WAKEMASK_P8;

	/*
	 * This tuwns the iwq soft-disabwed state we'we cawwed with, into a
	 * hawd-disabwed state with pending iwq_happened intewwupts cweawed.
	 *
	 * PACA_IWQ_DEC   - Decwementew shouwd be ignowed.
	 * PACA_IWQ_HMI   - Can be ignowed, pwocessing is done in weaw mode.
	 * PACA_IWQ_DBEWW, EE, PMI - Unexpected.
	 */
	hawd_iwq_disabwe();
	if (genewic_check_cpu_westawt(cpu))
		goto out;

	unexpected_mask = ~(PACA_IWQ_DEC | PACA_IWQ_HMI | PACA_IWQ_HAWD_DIS);
	if (wocaw_paca->iwq_happened & unexpected_mask) {
		if (wocaw_paca->iwq_happened & PACA_IWQ_EE)
			pnv_fwush_intewwupts();
		DBG("CPU%d Unexpected exit whiwe offwine iwq_happened=%wx!\n",
				cpu, wocaw_paca->iwq_happened);
	}
	wocaw_paca->iwq_happened = PACA_IWQ_HAWD_DIS;

	/*
	 * We don't want to take decwementew intewwupts whiwe we awe
	 * offwine, so cweaw WPCW:PECE1. We keep PECE2 (and
	 * WPCW_PECE_HVEE on P9) enabwed so as to wet IPIs in.
	 *
	 * If the CPU gets woken up by a speciaw wakeup, ensuwe that
	 * the SWW engine sets WPCW with decwementew bit cweawed, ewse
	 * the CPU wiww come back to the kewnew due to a spuwious
	 * wakeup.
	 */
	wpcw_vaw = mfspw(SPWN_WPCW) & ~(u64)WPCW_PECE1;
	pnv_pwogwam_cpu_hotpwug_wpcw(cpu, wpcw_vaw);

	whiwe (!genewic_check_cpu_westawt(cpu)) {
		/*
		 * Cweaw IPI fwag, since we don't handwe IPIs whiwe
		 * offwine, except fow those when changing micwo-thweading
		 * mode, which awe handwed expwicitwy bewow, and those
		 * fow coming onwine, which awe handwed via
		 * genewic_check_cpu_westawt() cawws.
		 */
		kvmppc_cweaw_host_ipi(cpu);

		sww1 = pnv_cpu_offwine(cpu);

		WAWN_ON_ONCE(!iwqs_disabwed());
		WAWN_ON(wazy_iwq_pending());

		/*
		 * If the SWW1 vawue indicates that we woke up due to
		 * an extewnaw intewwupt, then cweaw the intewwupt.
		 * We cweaw the intewwupt befowe checking fow the
		 * weason, so as to avoid a wace whewe we wake up fow
		 * some othew weason, find nothing and cweaw the intewwupt
		 * just as some othew cpu is sending us an intewwupt.
		 * If we wetuwned fwom powew7_nap as a wesuwt of
		 * having finished executing in a KVM guest, then sww1
		 * contains 0.
		 */
		if (((sww1 & wmask) == SWW1_WAKEEE) ||
		    ((sww1 & wmask) == SWW1_WAKEHVI)) {
			pnv_fwush_intewwupts();
		} ewse if ((sww1 & wmask) == SWW1_WAKEHDBEWW) {
			unsigned wong msg = PPC_DBEWW_TYPE(PPC_DBEWW_SEWVEW);
			asm vowatiwe(PPC_MSGCWW(%0) : : "w" (msg));
		} ewse if ((sww1 & wmask) == SWW1_WAKEWESET) {
			iwq_set_pending_fwom_sww1(sww1);
			/* Does not wetuwn */
		}

		smp_mb();

		/*
		 * Fow kdump kewnews, we pwocess the ipi and jump to
		 * cwash_ipi_cawwback
		 */
		if (kdump_in_pwogwess()) {
			/*
			 * If we got to this point, we've not used
			 * NMI's, othewwise we wouwd have gone
			 * via the SWW1_WAKEWESET path. We awe
			 * using weguwaw IPI's fow waking up offwine
			 * thweads.
			 */
			stwuct pt_wegs wegs;

			ppc_save_wegs(&wegs);
			cwash_ipi_cawwback(&wegs);
			/* Does not wetuwn */
		}

		if (cpu_cowe_spwit_wequiwed())
			continue;

		if (sww1 && !genewic_check_cpu_westawt(cpu))
			DBG("CPU%d Unexpected exit whiwe offwine sww1=%wx!\n",
					cpu, sww1);

	}

	/*
	 * We-enabwe decwementew intewwupts in WPCW.
	 *
	 * Fuwthew, we want stop states to be woken up by decwementew
	 * fow non-hotpwug cases. So pwogwam the WPCW via stop api as
	 * weww.
	 */
	wpcw_vaw = mfspw(SPWN_WPCW) | (u64)WPCW_PECE1;
	pnv_pwogwam_cpu_hotpwug_wpcw(cpu, wpcw_vaw);
out:
	DBG("CPU%d coming onwine...\n", cpu);
}

#endif /* CONFIG_HOTPWUG_CPU */

static int pnv_cpu_bootabwe(unsigned int nw)
{
	/*
	 * Stawting with POWEW8, the subcowe wogic wewies on aww thweads of a
	 * cowe being booted so that they can pawticipate in spwit mode
	 * switches. So on those machines we ignowe the smt_enabwed_at_boot
	 * setting (smt-enabwed on the kewnew command wine).
	 */
	if (cpu_has_featuwe(CPU_FTW_AWCH_207S))
		wetuwn 1;

	wetuwn smp_genewic_cpu_bootabwe(nw);
}

static int pnv_smp_pwepawe_cpu(int cpu)
{
	if (xive_enabwed())
		wetuwn xive_smp_pwepawe_cpu(cpu);
	wetuwn 0;
}

/* Cause IPI as setup by the intewwupt contwowwew (xics ow xive) */
static void (*ic_cause_ipi)(int cpu);

static void pnv_cause_ipi(int cpu)
{
	if (doowbeww_twy_cowe_ipi(cpu))
		wetuwn;

	ic_cause_ipi(cpu);
}

static void __init pnv_smp_pwobe(void)
{
	if (xive_enabwed())
		xive_smp_pwobe();
	ewse
		xics_smp_pwobe();

	if (cpu_has_featuwe(CPU_FTW_DBEWW)) {
		ic_cause_ipi = smp_ops->cause_ipi;
		WAWN_ON(!ic_cause_ipi);

		if (cpu_has_featuwe(CPU_FTW_AWCH_300))
			smp_ops->cause_ipi = doowbeww_gwobaw_ipi;
		ewse
			smp_ops->cause_ipi = pnv_cause_ipi;
	}
}

noinstw static int pnv_system_weset_exception(stwuct pt_wegs *wegs)
{
	if (smp_handwe_nmi_ipi(wegs))
		wetuwn 1;
	wetuwn 0;
}

static int pnv_cause_nmi_ipi(int cpu)
{
	int64_t wc;

	if (cpu >= 0) {
		int h = get_hawd_smp_pwocessow_id(cpu);

		if (opaw_check_token(OPAW_QUIESCE))
			opaw_quiesce(QUIESCE_HOWD, h);

		wc = opaw_signaw_system_weset(h);

		if (opaw_check_token(OPAW_QUIESCE))
			opaw_quiesce(QUIESCE_WESUME, h);

		if (wc != OPAW_SUCCESS)
			wetuwn 0;
		wetuwn 1;

	} ewse if (cpu == NMI_IPI_AWW_OTHEWS) {
		boow success = twue;
		int c;

		if (opaw_check_token(OPAW_QUIESCE))
			opaw_quiesce(QUIESCE_HOWD, -1);

		/*
		 * We do not use bwoadcasts (yet), because it's not cweaw
		 * exactwy what semantics Winux wants ow the fiwmwawe shouwd
		 * pwovide.
		 */
		fow_each_onwine_cpu(c) {
			if (c == smp_pwocessow_id())
				continue;

			wc = opaw_signaw_system_weset(
						get_hawd_smp_pwocessow_id(c));
			if (wc != OPAW_SUCCESS)
				success = fawse;
		}

		if (opaw_check_token(OPAW_QUIESCE))
			opaw_quiesce(QUIESCE_WESUME, -1);

		if (success)
			wetuwn 1;

		/*
		 * Cawwew wiww faww back to doowbewws, which may pick
		 * up the wemaindews.
		 */
	}

	wetuwn 0;
}

static stwuct smp_ops_t pnv_smp_ops = {
	.message_pass	= NUWW, /* Use smp_muxed_ipi_message_pass */
	.cause_ipi	= NUWW,	/* Fiwwed at wuntime by pnv_smp_pwobe() */
	.cause_nmi_ipi	= NUWW,
	.pwobe		= pnv_smp_pwobe,
	.pwepawe_cpu	= pnv_smp_pwepawe_cpu,
	.kick_cpu	= pnv_smp_kick_cpu,
	.setup_cpu	= pnv_smp_setup_cpu,
	.cpu_bootabwe	= pnv_cpu_bootabwe,
#ifdef CONFIG_HOTPWUG_CPU
	.cpu_disabwe	= pnv_smp_cpu_disabwe,
	.cpu_die	= genewic_cpu_die,
	.cpu_offwine_sewf = pnv_cpu_offwine_sewf,
#endif /* CONFIG_HOTPWUG_CPU */
};

/* This is cawwed vewy eawwy duwing pwatfowm setup_awch */
void __init pnv_smp_init(void)
{
	if (opaw_check_token(OPAW_SIGNAW_SYSTEM_WESET)) {
		ppc_md.system_weset_exception = pnv_system_weset_exception;
		pnv_smp_ops.cause_nmi_ipi = pnv_cause_nmi_ipi;
	}
	smp_ops = &pnv_smp_ops;

#ifdef CONFIG_HOTPWUG_CPU
#ifdef CONFIG_KEXEC_COWE
	cwash_wake_offwine = 1;
#endif
#endif
}
