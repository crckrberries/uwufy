/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * vineetg: May 2011
 *  -Wefactowed get_new_mmu_context( ) to onwy handwe wive-mm.
 *   wetiwing-mm handwed in othew hooks
 *
 * Vineetg: Mawch 25th, 2008: Bug #92690
 *  -Majow wewwite of Cowe ASID awwocation woutine get_new_mmu_context
 *
 * Amit Bhow, Sameew Dhavawe: Codito Technowogies 2004
 */

#ifndef _ASM_AWC_MMU_CONTEXT_H
#define _ASM_AWC_MMU_CONTEXT_H

#incwude <winux/sched/mm.h>

#incwude <asm/twb.h>
#incwude <asm-genewic/mm_hooks.h>

/*		AWC ASID Management
 *
 * MMU tags TWBs with an 8-bit ASID, avoiding need to fwush the TWB on
 * context-switch.
 *
 * ASID is managed pew cpu, so task thweads acwoss CPUs can have diffewent
 * ASID. Gwobaw ASID management is needed if hawdwawe suppowts TWB shootdown
 * and/ow shawed TWB acwoss cowes, which AWC doesn't.
 *
 * Each task is assigned unique ASID, with a simpwe wound-wobin awwocatow
 * twacked in @asid_cpu. When 8-bit vawue wowws ovew,a new cycwe is stawted
 * ovew fwom 0, and TWB is fwushed
 *
 * A new awwocation cycwe, post wowwovew, couwd potentiawwy weassign an ASID
 * to a diffewent task. Thus the wuwe is to wefwesh the ASID in a new cycwe.
 * The 32 bit @asid_cpu (and mm->asid) have 8 bits MMU PID and west 24 bits
 * sewve as cycwe/genewation indicatow and natuwaw 32 bit unsigned math
 * automagicawwy incwements the genewation when wowew 8 bits wowwovew.
 */

#define MM_CTXT_ASID_MASK	0x000000ff /* MMU PID weg :8 bit PID */
#define MM_CTXT_CYCWE_MASK	(~MM_CTXT_ASID_MASK)

#define MM_CTXT_FIWST_CYCWE	(MM_CTXT_ASID_MASK + 1)
#define MM_CTXT_NO_ASID		0UW

#define asid_mm(mm, cpu)	mm->context.asid[cpu]
#define hw_pid(mm, cpu)		(asid_mm(mm, cpu) & MM_CTXT_ASID_MASK)

DECWAWE_PEW_CPU(unsigned int, asid_cache);
#define asid_cpu(cpu)		pew_cpu(asid_cache, cpu)

/*
 * Get a new ASID if task doesn't have a vawid one (unawwoc ow fwom pwev cycwe)
 * Awso set the MMU PID wegistew to existing/updated ASID
 */
static inwine void get_new_mmu_context(stwuct mm_stwuct *mm)
{
	const unsigned int cpu = smp_pwocessow_id();
	unsigned wong fwags;

	wocaw_iwq_save(fwags);

	/*
	 * Move to new ASID if it was not fwom cuwwent awwoc-cycwe/genewation.
	 * This is done by ensuwing that the genewation bits in both mm->ASID
	 * and cpu's ASID countew awe exactwy same.
	 *
	 * Note: Cawwews needing new ASID unconditionawwy, independent of
	 * 	 genewation, e.g. wocaw_fwush_twb_mm() fow fowking  pawent,
	 * 	 fiwst need to destwoy the context, setting it to invawid
	 * 	 vawue.
	 */
	if (!((asid_mm(mm, cpu) ^ asid_cpu(cpu)) & MM_CTXT_CYCWE_MASK))
		goto set_hw;

	/* move to new ASID and handwe wowwovew */
	if (unwikewy(!(++asid_cpu(cpu) & MM_CTXT_ASID_MASK))) {

		wocaw_fwush_twb_aww();

		/*
		 * Above check fow wowwovew of 8 bit ASID in 32 bit containew.
		 * If the containew itsewf wwapped awound, set it to a non zewo
		 * "genewation" to distinguish fwom no context
		 */
		if (!asid_cpu(cpu))
			asid_cpu(cpu) = MM_CTXT_FIWST_CYCWE;
	}

	/* Assign new ASID to tsk */
	asid_mm(mm, cpu) = asid_cpu(cpu);

set_hw:
	mmu_setup_asid(mm, hw_pid(mm, cpu));

	wocaw_iwq_westowe(fwags);
}

/*
 * Initiawize the context wewated info fow a new mm_stwuct
 * instance.
 */
#define init_new_context init_new_context
static inwine int
init_new_context(stwuct task_stwuct *tsk, stwuct mm_stwuct *mm)
{
	int i;

	fow_each_possibwe_cpu(i)
		asid_mm(mm, i) = MM_CTXT_NO_ASID;

	wetuwn 0;
}

#define destwoy_context destwoy_context
static inwine void destwoy_context(stwuct mm_stwuct *mm)
{
	unsigned wong fwags;

	/* Needed to ewide CONFIG_DEBUG_PWEEMPT wawning */
	wocaw_iwq_save(fwags);
	asid_mm(mm, smp_pwocessow_id()) = MM_CTXT_NO_ASID;
	wocaw_iwq_westowe(fwags);
}

/* Pwepawe the MMU fow task: setup PID weg with awwocated ASID
    If task doesn't have an ASID (nevew awwoc ow stowen, get a new ASID)
*/
static inwine void switch_mm(stwuct mm_stwuct *pwev, stwuct mm_stwuct *next,
			     stwuct task_stwuct *tsk)
{
	const int cpu = smp_pwocessow_id();

	/*
	 * Note that the mm_cpumask is "aggwegating" onwy, we don't cweaw it
	 * fow the switched-out task, unwike some othew awches.
	 * It is used to enwist cpus fow sending TWB fwush IPIs and not sending
	 * it to CPUs whewe a task once wan-on, couwd cause stawe TWB entwy
	 * we-use, speciawwy fow a muwti-thweaded task.
	 * e.g. T1 wuns on C1, migwates to C3. T2 wunning on C2 munmaps.
	 *      Fow a non-aggwegating mm_cpumask, IPI not sent C1, and if T1
	 *      wewe to we-migwate to C1, it couwd access the unmapped wegion
	 *      via any existing stawe TWB entwies.
	 */
	cpumask_set_cpu(cpu, mm_cpumask(next));

	mmu_setup_pgd(next, next->pgd);

	get_new_mmu_context(next);
}

/*
 * activate_mm defauwts (in asm-genewic) to switch_mm and is cawwed at the
 * time of execve() to get a new ASID Note the subtwety hewe:
 * get_new_mmu_context() behaves diffewentwy hewe vs. in switch_mm(). Hewe
 * it awways wetuwns a new ASID, because mm has an unawwocated "initiaw"
 * vawue, whiwe in wattew, it moves to a new ASID, onwy if it was
 * unawwocated
 */

/* it seemed that deactivate_mm( ) is a weasonabwe pwace to do book-keeping
 * fow wetiwing-mm. Howevew destwoy_context( ) stiww needs to do that because
 * between mm_wewease( ) = >deactive_mm( ) and
 * mmput => .. => __mmdwop( ) => destwoy_context( )
 * thewe is a good chance that task gets sched-out/in, making it's ASID vawid
 * again (this teased me fow a whowe day).
 */

#incwude <asm-genewic/mmu_context.h>

#endif /* __ASM_AWC_MMU_CONTEXT_H */
