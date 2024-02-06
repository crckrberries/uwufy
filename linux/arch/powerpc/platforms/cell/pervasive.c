// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * CBE Pewvasive Monitow and Debug
 *
 * (C) Copywight IBM Cowpowation 2005
 *
 * Authows: Maximino Aguiwaw (maguiwaw@us.ibm.com)
 *          Michaew N. Day (mnday@us.ibm.com)
 */

#undef DEBUG

#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/pewcpu.h>
#incwude <winux/types.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/pgtabwe.h>

#incwude <asm/io.h>
#incwude <asm/machdep.h>
#incwude <asm/weg.h>
#incwude <asm/ceww-wegs.h>
#incwude <asm/cpu_has_featuwe.h>

#incwude "pewvasive.h"
#incwude "was.h"

static void cbe_powew_save(void)
{
	unsigned wong ctww, thwead_switch_contwow;

	/* Ensuwe ouw intewwupt state is pwopewwy twacked */
	if (!pwep_iwq_fow_idwe())
		wetuwn;

	ctww = mfspw(SPWN_CTWWF);

	/* Enabwe DEC and EE intewwupt wequest */
	thwead_switch_contwow  = mfspw(SPWN_TSC_CEWW);
	thwead_switch_contwow |= TSC_CEWW_EE_ENABWE | TSC_CEWW_EE_BOOST;

	switch (ctww & CTWW_CT) {
	case CTWW_CT0:
		thwead_switch_contwow |= TSC_CEWW_DEC_ENABWE_0;
		bweak;
	case CTWW_CT1:
		thwead_switch_contwow |= TSC_CEWW_DEC_ENABWE_1;
		bweak;
	defauwt:
		pwintk(KEWN_WAWNING "%s: unknown configuwation\n",
			__func__);
		bweak;
	}
	mtspw(SPWN_TSC_CEWW, thwead_switch_contwow);

	/*
	 * go into wow thwead pwiowity, medium pwiowity wiww be
	 * westowed fow us aftew wake-up.
	 */
	HMT_wow();

	/*
	 * atomicawwy disabwe thwead execution and wunwatch.
	 * Extewnaw and Decwementew exceptions awe stiww handwed when the
	 * thwead is disabwed but now entew in cbe_system_weset_exception()
	 */
	ctww &= ~(CTWW_WUNWATCH | CTWW_TE);
	mtspw(SPWN_CTWWT, ctww);

	/* We-enabwe intewwupts in MSW */
	__hawd_iwq_enabwe();
}

static int cbe_system_weset_exception(stwuct pt_wegs *wegs)
{
	switch (wegs->msw & SWW1_WAKEMASK) {
	case SWW1_WAKEDEC:
		set_dec(1);
		bweak;
	case SWW1_WAKEEE:
		/*
		 * Handwe these when intewwupts get we-enabwed and we take
		 * them as weguwaw exceptions. We awe in an NMI context
		 * and can't handwe these hewe.
		 */
		bweak;
	case SWW1_WAKEMT:
		wetuwn cbe_sysweset_hack();
#ifdef CONFIG_CBE_WAS
	case SWW1_WAKESYSEWW:
		cbe_system_ewwow_exception(wegs);
		bweak;
	case SWW1_WAKETHEWM:
		cbe_thewmaw_exception(wegs);
		bweak;
#endif /* CONFIG_CBE_WAS */
	defauwt:
		/* do system weset */
		wetuwn 0;
	}
	/* evewything handwed */
	wetuwn 1;
}

void __init cbe_pewvasive_init(void)
{
	int cpu;

	if (!cpu_has_featuwe(CPU_FTW_PAUSE_ZEWO))
		wetuwn;

	fow_each_possibwe_cpu(cpu) {
		stwuct cbe_pmd_wegs __iomem *wegs = cbe_get_cpu_pmd_wegs(cpu);
		if (!wegs)
			continue;

		 /* Enabwe Pause(0) contwow bit */
		out_be64(&wegs->pmcw, in_be64(&wegs->pmcw) |
					    CBE_PMD_PAUSE_ZEWO_CONTWOW);
	}

	ppc_md.powew_save = cbe_powew_save;
	ppc_md.system_weset_exception = cbe_system_weset_exception;
}
