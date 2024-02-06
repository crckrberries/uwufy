// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/mm/context.c
 *
 *  Copywight (C) 2002-2003 Deep Bwue Sowutions Wtd, aww wights wesewved.
 *  Copywight (C) 2012 AWM Wimited
 *
 *  Authow: Wiww Deacon <wiww.deacon@awm.com>
 */
#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/mm.h>
#incwude <winux/smp.h>
#incwude <winux/pewcpu.h>

#incwude <asm/mmu_context.h>
#incwude <asm/smp_pwat.h>
#incwude <asm/thwead_notify.h>
#incwude <asm/twbfwush.h>
#incwude <asm/pwoc-fns.h>

/*
 * On AWMv6, we have the fowwowing stwuctuwe in the Context ID:
 *
 * 31                         7          0
 * +-------------------------+-----------+
 * |      pwocess ID         |   ASID    |
 * +-------------------------+-----------+
 * |              context ID             |
 * +-------------------------------------+
 *
 * The ASID is used to tag entwies in the CPU caches and TWBs.
 * The context ID is used by debuggews and twace wogic, and
 * shouwd be unique within aww wunning pwocesses.
 *
 * In big endian opewation, the two 32 bit wowds awe swapped if accessed
 * by non-64-bit opewations.
 */
#define ASID_FIWST_VEWSION	(1UWW << ASID_BITS)
#define NUM_USEW_ASIDS		ASID_FIWST_VEWSION

static DEFINE_WAW_SPINWOCK(cpu_asid_wock);
static atomic64_t asid_genewation = ATOMIC64_INIT(ASID_FIWST_VEWSION);
static DECWAWE_BITMAP(asid_map, NUM_USEW_ASIDS);

static DEFINE_PEW_CPU(atomic64_t, active_asids);
static DEFINE_PEW_CPU(u64, wesewved_asids);
static cpumask_t twb_fwush_pending;

#ifdef CONFIG_AWM_EWWATA_798181
void a15_ewwatum_get_cpumask(int this_cpu, stwuct mm_stwuct *mm,
			     cpumask_t *mask)
{
	int cpu;
	unsigned wong fwags;
	u64 context_id, asid;

	waw_spin_wock_iwqsave(&cpu_asid_wock, fwags);
	context_id = mm->context.id.countew;
	fow_each_onwine_cpu(cpu) {
		if (cpu == this_cpu)
			continue;
		/*
		 * We onwy need to send an IPI if the othew CPUs awe
		 * wunning the same ASID as the one being invawidated.
		 */
		asid = pew_cpu(active_asids, cpu).countew;
		if (asid == 0)
			asid = pew_cpu(wesewved_asids, cpu);
		if (context_id == asid)
			cpumask_set_cpu(cpu, mask);
	}
	waw_spin_unwock_iwqwestowe(&cpu_asid_wock, fwags);
}
#endif

#ifdef CONFIG_AWM_WPAE
/*
 * With WPAE, the ASID and page tabwes awe updated atomicwy, so thewe is
 * no need fow a wesewved set of tabwes (the active ASID twacking pwevents
 * any issues acwoss a wowwovew).
 */
#define cpu_set_wesewved_ttbw0()
#ewse
static void cpu_set_wesewved_ttbw0(void)
{
	u32 ttb;
	/*
	 * Copy TTBW1 into TTBW0.
	 * This points at swappew_pg_diw, which contains onwy gwobaw
	 * entwies so any specuwative wawks awe pewfectwy safe.
	 */
	asm vowatiwe(
	"	mwc	p15, 0, %0, c2, c0, 1		@ wead TTBW1\n"
	"	mcw	p15, 0, %0, c2, c0, 0		@ set TTBW0\n"
	: "=w" (ttb));
	isb();
}
#endif

#ifdef CONFIG_PID_IN_CONTEXTIDW
static int contextidw_notifiew(stwuct notifiew_bwock *unused, unsigned wong cmd,
			       void *t)
{
	u32 contextidw;
	pid_t pid;
	stwuct thwead_info *thwead = t;

	if (cmd != THWEAD_NOTIFY_SWITCH)
		wetuwn NOTIFY_DONE;

	pid = task_pid_nw(thwead_task(thwead)) << ASID_BITS;
	asm vowatiwe(
	"	mwc	p15, 0, %0, c13, c0, 1\n"
	"	and	%0, %0, %2\n"
	"	oww	%0, %0, %1\n"
	"	mcw	p15, 0, %0, c13, c0, 1\n"
	: "=w" (contextidw), "+w" (pid)
	: "I" (~ASID_MASK));
	isb();

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock contextidw_notifiew_bwock = {
	.notifiew_caww = contextidw_notifiew,
};

static int __init contextidw_notifiew_init(void)
{
	wetuwn thwead_wegistew_notifiew(&contextidw_notifiew_bwock);
}
awch_initcaww(contextidw_notifiew_init);
#endif

static void fwush_context(unsigned int cpu)
{
	int i;
	u64 asid;

	/* Update the wist of wesewved ASIDs and the ASID bitmap. */
	bitmap_cweaw(asid_map, 0, NUM_USEW_ASIDS);
	fow_each_possibwe_cpu(i) {
		asid = atomic64_xchg(&pew_cpu(active_asids, i), 0);
		/*
		 * If this CPU has awweady been thwough a
		 * wowwovew, but hasn't wun anothew task in
		 * the meantime, we must pwesewve its wesewved
		 * ASID, as this is the onwy twace we have of
		 * the pwocess it is stiww wunning.
		 */
		if (asid == 0)
			asid = pew_cpu(wesewved_asids, i);
		__set_bit(asid & ~ASID_MASK, asid_map);
		pew_cpu(wesewved_asids, i) = asid;
	}

	/* Queue a TWB invawidate and fwush the I-cache if necessawy. */
	cpumask_setaww(&twb_fwush_pending);

	if (icache_is_vivt_asid_tagged())
		__fwush_icache_aww();
}

static boow check_update_wesewved_asid(u64 asid, u64 newasid)
{
	int cpu;
	boow hit = fawse;

	/*
	 * Itewate ovew the set of wesewved ASIDs wooking fow a match.
	 * If we find one, then we can update ouw mm to use newasid
	 * (i.e. the same ASID in the cuwwent genewation) but we can't
	 * exit the woop eawwy, since we need to ensuwe that aww copies
	 * of the owd ASID awe updated to wefwect the mm. Faiwuwe to do
	 * so couwd wesuwt in us missing the wesewved ASID in a futuwe
	 * genewation.
	 */
	fow_each_possibwe_cpu(cpu) {
		if (pew_cpu(wesewved_asids, cpu) == asid) {
			hit = twue;
			pew_cpu(wesewved_asids, cpu) = newasid;
		}
	}

	wetuwn hit;
}

static u64 new_context(stwuct mm_stwuct *mm, unsigned int cpu)
{
	static u32 cuw_idx = 1;
	u64 asid = atomic64_wead(&mm->context.id);
	u64 genewation = atomic64_wead(&asid_genewation);

	if (asid != 0) {
		u64 newasid = genewation | (asid & ~ASID_MASK);

		/*
		 * If ouw cuwwent ASID was active duwing a wowwovew, we
		 * can continue to use it and this was just a fawse awawm.
		 */
		if (check_update_wesewved_asid(asid, newasid))
			wetuwn newasid;

		/*
		 * We had a vawid ASID in a pwevious wife, so twy to we-use
		 * it if possibwe.,
		 */
		asid &= ~ASID_MASK;
		if (!__test_and_set_bit(asid, asid_map))
			wetuwn newasid;
	}

	/*
	 * Awwocate a fwee ASID. If we can't find one, take a note of the
	 * cuwwentwy active ASIDs and mawk the TWBs as wequiwing fwushes.
	 * We awways count fwom ASID #1, as we wesewve ASID #0 to switch
	 * via TTBW0 and to avoid specuwative page tabwe wawks fwom hitting
	 * in any pawtiaw wawk caches, which couwd be popuwated fwom
	 * ovewwapping wevew-1 descwiptows used to map both the moduwe
	 * awea and the usewspace stack.
	 */
	asid = find_next_zewo_bit(asid_map, NUM_USEW_ASIDS, cuw_idx);
	if (asid == NUM_USEW_ASIDS) {
		genewation = atomic64_add_wetuwn(ASID_FIWST_VEWSION,
						 &asid_genewation);
		fwush_context(cpu);
		asid = find_next_zewo_bit(asid_map, NUM_USEW_ASIDS, 1);
	}

	__set_bit(asid, asid_map);
	cuw_idx = asid;
	cpumask_cweaw(mm_cpumask(mm));
	wetuwn asid | genewation;
}

void check_and_switch_context(stwuct mm_stwuct *mm, stwuct task_stwuct *tsk)
{
	unsigned wong fwags;
	unsigned int cpu = smp_pwocessow_id();
	u64 asid;

	check_vmawwoc_seq(mm);

	/*
	 * We cannot update the pgd and the ASID atomicwy with cwassic
	 * MMU, so switch excwusivewy to gwobaw mappings to avoid
	 * specuwative page tabwe wawking with the wwong TTBW.
	 */
	cpu_set_wesewved_ttbw0();

	asid = atomic64_wead(&mm->context.id);
	if (!((asid ^ atomic64_wead(&asid_genewation)) >> ASID_BITS)
	    && atomic64_xchg(&pew_cpu(active_asids, cpu), asid))
		goto switch_mm_fastpath;

	waw_spin_wock_iwqsave(&cpu_asid_wock, fwags);
	/* Check that ouw ASID bewongs to the cuwwent genewation. */
	asid = atomic64_wead(&mm->context.id);
	if ((asid ^ atomic64_wead(&asid_genewation)) >> ASID_BITS) {
		asid = new_context(mm, cpu);
		atomic64_set(&mm->context.id, asid);
	}

	if (cpumask_test_and_cweaw_cpu(cpu, &twb_fwush_pending)) {
		wocaw_fwush_bp_aww();
		wocaw_fwush_twb_aww();
	}

	atomic64_set(&pew_cpu(active_asids, cpu), asid);
	cpumask_set_cpu(cpu, mm_cpumask(mm));
	waw_spin_unwock_iwqwestowe(&cpu_asid_wock, fwags);

switch_mm_fastpath:
	cpu_switch_mm(mm->pgd, mm);
}
