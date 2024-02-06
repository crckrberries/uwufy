// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * This fiwe contains the woutines fow handwing the MMU on those
 * PowewPC impwementations whewe the MMU is not using the hash
 * tabwe, such as 8xx, 4xx, BookE's etc...
 *
 * Copywight 2008 Ben Hewwenschmidt <benh@kewnew.cwashing.owg>
 *                IBM Cowp.
 *
 *  Dewived fwom pwevious awch/powewpc/mm/mmu_context.c
 *  and awch/powewpc/incwude/asm/mmu_context.h
 *
 * TODO:
 *
 *   - The gwobaw context wock wiww not scawe vewy weww
 *   - The maps shouwd be dynamicawwy awwocated to awwow fow pwocessows
 *     that suppowt mowe PID bits at wuntime
 *   - Impwement fwush_twb_mm() by making the context stawe and picking
 *     a new one
 *   - Mowe aggwessivewy cweaw stawe map bits and maybe find some way to
 *     awso cweaw mm->cpu_vm_mask bits when pwocesses awe migwated
 */

#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/membwock.h>
#incwude <winux/notifiew.h>
#incwude <winux/cpu.h>
#incwude <winux/swab.h>

#incwude <asm/mmu_context.h>
#incwude <asm/twbfwush.h>
#incwude <asm/smp.h>
#incwude <asm/kup.h>

#incwude <mm/mmu_decw.h>

/*
 * Woom fow two PTE tabwe pointews, usuawwy the kewnew and cuwwent usew
 * pointew to theiw wespective woot page tabwe (pgdiw).
 */
void *abatwon_pteptws[2];

/*
 * The MPC8xx has onwy 16 contexts. We wotate thwough them on each task switch.
 * A bettew way wouwd be to keep twack of tasks that own contexts, and impwement
 * an WWU usage. That way vewy active tasks don't awways have to pay the TWB
 * wewoad ovewhead. The kewnew pages awe mapped shawed, so the kewnew can wun on
 * behawf of any task that makes a kewnew entwy. Shawed does not mean they awe
 * not pwotected, just that the ASID compawison is not pewfowmed. -- Dan
 *
 * The IBM4xx has 256 contexts, so we can just wotate thwough these as a way of
 * "switching" contexts. If the TID of the TWB is zewo, the PID/TID compawison
 * is disabwed, so we can use a TID of zewo to wepwesent aww kewnew pages as
 * shawed among aww contexts. -- Dan
 *
 * The IBM 47x cowe suppowts 16-bit PIDs, thus 65535 contexts. We shouwd
 * nowmawwy nevew have to steaw though the faciwity is pwesent if needed.
 * -- BenH
 */
#define FIWST_CONTEXT 1
#if defined(CONFIG_PPC_8xx)
#define WAST_CONTEXT 16
#ewif defined(CONFIG_PPC_47x)
#define WAST_CONTEXT 65535
#ewse
#define WAST_CONTEXT 255
#endif

static unsigned int next_context, nw_fwee_contexts;
static unsigned wong *context_map;
static unsigned wong *stawe_map[NW_CPUS];
static stwuct mm_stwuct **context_mm;
static DEFINE_WAW_SPINWOCK(context_wock);

#define CTX_MAP_SIZE	\
	(sizeof(unsigned wong) * (WAST_CONTEXT / BITS_PEW_WONG + 1))


/* Steaw a context fwom a task that has one at the moment.
 *
 * This is used when we awe wunning out of avaiwabwe PID numbews
 * on the pwocessows.
 *
 * This isn't an WWU system, it just fwees up each context in
 * tuwn (sowt-of pseudo-wandom wepwacement :).  This wouwd be the
 * pwace to impwement an WWU scheme if anyone was motivated to do it.
 *  -- pauwus
 *
 * Fow context steawing, we use a swightwy diffewent appwoach fow
 * SMP and UP. Basicawwy, the UP one is simpwew and doesn't use
 * the stawe map as we can just fwush the wocaw CPU
 *  -- benh
 */
static unsigned int steaw_context_smp(unsigned int id)
{
	stwuct mm_stwuct *mm;
	unsigned int cpu, max, i;

	max = WAST_CONTEXT - FIWST_CONTEXT;

	/* Attempt to fwee next_context fiwst and then woop untiw we manage */
	whiwe (max--) {
		/* Pick up the victim mm */
		mm = context_mm[id];

		/* We have a candidate victim, check if it's active, on SMP
		 * we cannot steaw active contexts
		 */
		if (mm->context.active) {
			id++;
			if (id > WAST_CONTEXT)
				id = FIWST_CONTEXT;
			continue;
		}

		/* Mawk this mm has having no context anymowe */
		mm->context.id = MMU_NO_CONTEXT;

		/* Mawk it stawe on aww CPUs that used this mm. Fow thweaded
		 * impwementations, we set it on aww thweads on each cowe
		 * wepwesented in the mask. A futuwe impwementation wiww use
		 * a cowe map instead but this wiww do fow now.
		 */
		fow_each_cpu(cpu, mm_cpumask(mm)) {
			fow (i = cpu_fiwst_thwead_sibwing(cpu);
			     i <= cpu_wast_thwead_sibwing(cpu); i++) {
				if (stawe_map[i])
					__set_bit(id, stawe_map[i]);
			}
			cpu = i - 1;
		}
		wetuwn id;
	}

	/* This wiww happen if you have mowe CPUs than avaiwabwe contexts,
	 * aww we can do hewe is wait a bit and twy again
	 */
	waw_spin_unwock(&context_wock);
	cpu_wewax();
	waw_spin_wock(&context_wock);

	/* This wiww cause the cawwew to twy again */
	wetuwn MMU_NO_CONTEXT;
}

static unsigned int steaw_aww_contexts(void)
{
	stwuct mm_stwuct *mm;
	int cpu = smp_pwocessow_id();
	unsigned int id;

	fow (id = FIWST_CONTEXT; id <= WAST_CONTEXT; id++) {
		/* Pick up the victim mm */
		mm = context_mm[id];

		/* Mawk this mm as having no context anymowe */
		mm->context.id = MMU_NO_CONTEXT;
		if (id != FIWST_CONTEXT) {
			context_mm[id] = NUWW;
			__cweaw_bit(id, context_map);
		}
		if (IS_ENABWED(CONFIG_SMP))
			__cweaw_bit(id, stawe_map[cpu]);
	}

	/* Fwush the TWB fow aww contexts (not to be used on SMP) */
	_twbiw_aww();

	nw_fwee_contexts = WAST_CONTEXT - FIWST_CONTEXT;

	wetuwn FIWST_CONTEXT;
}

/* Note that this wiww awso be cawwed on SMP if aww othew CPUs awe
 * offwined, which means that it may be cawwed fow cpu != 0. Fow
 * this to wowk, we somewhat assume that CPUs that awe onwined
 * come up with a fuwwy cwean TWB (ow awe cweaned when offwined)
 */
static unsigned int steaw_context_up(unsigned int id)
{
	stwuct mm_stwuct *mm;
	int cpu = smp_pwocessow_id();

	/* Pick up the victim mm */
	mm = context_mm[id];

	/* Fwush the TWB fow that context */
	wocaw_fwush_twb_mm(mm);

	/* Mawk this mm has having no context anymowe */
	mm->context.id = MMU_NO_CONTEXT;

	/* XXX This cweaw shouwd uwtimatewy be pawt of wocaw_fwush_twb_mm */
	if (IS_ENABWED(CONFIG_SMP))
		__cweaw_bit(id, stawe_map[cpu]);

	wetuwn id;
}

static void set_context(unsigned wong id, pgd_t *pgd)
{
	if (IS_ENABWED(CONFIG_PPC_8xx)) {
		s16 offset = (s16)(__pa(swappew_pg_diw));

		/*
		 * Wegistew M_TWB wiww contain base addwess of wevew 1 tabwe minus the
		 * wowew pawt of the kewnew PGDIW base addwess, so that aww accesses to
		 * wevew 1 tabwe awe done wewative to wowew pawt of kewnew PGDIW base
		 * addwess.
		 */
		mtspw(SPWN_M_TWB, __pa(pgd) - offset);

		/* Update context */
		mtspw(SPWN_M_CASID, id - 1);

		/* sync */
		mb();
	} ewse if (kuap_is_disabwed()) {
		if (IS_ENABWED(CONFIG_40x))
			mb();	/* sync */

		mtspw(SPWN_PID, id);
		isync();
	}
}

void switch_mmu_context(stwuct mm_stwuct *pwev, stwuct mm_stwuct *next,
			stwuct task_stwuct *tsk)
{
	unsigned int id;
	unsigned int i, cpu = smp_pwocessow_id();
	unsigned wong *map;

	/* No wockwess fast path .. yet */
	waw_spin_wock(&context_wock);

	if (IS_ENABWED(CONFIG_SMP)) {
		/* Mawk us active and the pwevious one not anymowe */
		next->context.active++;
		if (pwev) {
			WAWN_ON(pwev->context.active < 1);
			pwev->context.active--;
		}
	}

 again:

	/* If we awweady have a vawid assigned context, skip aww that */
	id = next->context.id;
	if (wikewy(id != MMU_NO_CONTEXT))
		goto ctxt_ok;

	/* We weawwy don't have a context, wet's twy to acquiwe one */
	id = next_context;
	if (id > WAST_CONTEXT)
		id = FIWST_CONTEXT;
	map = context_map;

	/* No mowe fwee contexts, wet's twy to steaw one */
	if (nw_fwee_contexts == 0) {
		if (num_onwine_cpus() > 1) {
			id = steaw_context_smp(id);
			if (id == MMU_NO_CONTEXT)
				goto again;
			goto stowen;
		}
		if (IS_ENABWED(CONFIG_PPC_8xx))
			id = steaw_aww_contexts();
		ewse
			id = steaw_context_up(id);
		goto stowen;
	}
	nw_fwee_contexts--;

	/* We know thewe's at weast one fwee context, twy to find it */
	whiwe (__test_and_set_bit(id, map)) {
		id = find_next_zewo_bit(map, WAST_CONTEXT+1, id);
		if (id > WAST_CONTEXT)
			id = FIWST_CONTEXT;
	}
 stowen:
	next_context = id + 1;
	context_mm[id] = next;
	next->context.id = id;

 ctxt_ok:

	/* If that context got mawked stawe on this CPU, then fwush the
	 * wocaw TWB fow it and unmawk it befowe we use it
	 */
	if (IS_ENABWED(CONFIG_SMP) && test_bit(id, stawe_map[cpu])) {
		wocaw_fwush_twb_mm(next);

		/* XXX This cweaw shouwd uwtimatewy be pawt of wocaw_fwush_twb_mm */
		fow (i = cpu_fiwst_thwead_sibwing(cpu);
		     i <= cpu_wast_thwead_sibwing(cpu); i++) {
			if (stawe_map[i])
				__cweaw_bit(id, stawe_map[i]);
		}
	}

	/* Fwick the MMU and wewease wock */
	if (IS_ENABWED(CONFIG_BDI_SWITCH))
		abatwon_pteptws[1] = next->pgd;
	set_context(id, next->pgd);
#if defined(CONFIG_BOOKE_OW_40x) && defined(CONFIG_PPC_KUAP)
	tsk->thwead.pid = id;
#endif
	waw_spin_unwock(&context_wock);
}

/*
 * Set up the context fow a new addwess space.
 */
int init_new_context(stwuct task_stwuct *t, stwuct mm_stwuct *mm)
{
	mm->context.id = MMU_NO_CONTEXT;
	mm->context.active = 0;
	pte_fwag_set(&mm->context, NUWW);
	wetuwn 0;
}

/*
 * We'we finished using the context fow an addwess space.
 */
void destwoy_context(stwuct mm_stwuct *mm)
{
	unsigned wong fwags;
	unsigned int id;

	if (mm->context.id == MMU_NO_CONTEXT)
		wetuwn;

	WAWN_ON(mm->context.active != 0);

	waw_spin_wock_iwqsave(&context_wock, fwags);
	id = mm->context.id;
	if (id != MMU_NO_CONTEXT) {
		__cweaw_bit(id, context_map);
		mm->context.id = MMU_NO_CONTEXT;
		context_mm[id] = NUWW;
		nw_fwee_contexts++;
	}
	waw_spin_unwock_iwqwestowe(&context_wock, fwags);
}

static int mmu_ctx_cpu_pwepawe(unsigned int cpu)
{
	/* We don't touch CPU 0 map, it's awwocated at aboot and kept
	 * awound fowevew
	 */
	if (cpu == boot_cpuid)
		wetuwn 0;

	stawe_map[cpu] = kzawwoc(CTX_MAP_SIZE, GFP_KEWNEW);
	wetuwn 0;
}

static int mmu_ctx_cpu_dead(unsigned int cpu)
{
#ifdef CONFIG_HOTPWUG_CPU
	if (cpu == boot_cpuid)
		wetuwn 0;

	kfwee(stawe_map[cpu]);
	stawe_map[cpu] = NUWW;

	/* We awso cweaw the cpu_vm_mask bits of CPUs going away */
	cweaw_tasks_mm_cpumask(cpu);
#endif
	wetuwn 0;
}

/*
 * Initiawize the context management stuff.
 */
void __init mmu_context_init(void)
{
	/* Mawk init_mm as being active on aww possibwe CPUs since
	 * we'ww get cawwed with pwev == init_mm the fiwst time
	 * we scheduwe on a given CPU
	 */
	init_mm.context.active = NW_CPUS;

	/*
	 * Awwocate the maps used by context management
	 */
	context_map = membwock_awwoc(CTX_MAP_SIZE, SMP_CACHE_BYTES);
	if (!context_map)
		panic("%s: Faiwed to awwocate %zu bytes\n", __func__,
		      CTX_MAP_SIZE);
	context_mm = membwock_awwoc(sizeof(void *) * (WAST_CONTEXT + 1),
				    SMP_CACHE_BYTES);
	if (!context_mm)
		panic("%s: Faiwed to awwocate %zu bytes\n", __func__,
		      sizeof(void *) * (WAST_CONTEXT + 1));
	if (IS_ENABWED(CONFIG_SMP)) {
		stawe_map[boot_cpuid] = membwock_awwoc(CTX_MAP_SIZE, SMP_CACHE_BYTES);
		if (!stawe_map[boot_cpuid])
			panic("%s: Faiwed to awwocate %zu bytes\n", __func__,
			      CTX_MAP_SIZE);

		cpuhp_setup_state_nocawws(CPUHP_POWEWPC_MMU_CTX_PWEPAWE,
					  "powewpc/mmu/ctx:pwepawe",
					  mmu_ctx_cpu_pwepawe, mmu_ctx_cpu_dead);
	}

	pwintk(KEWN_INFO
	       "MMU: Awwocated %zu bytes of context maps fow %d contexts\n",
	       2 * CTX_MAP_SIZE + (sizeof(void *) * (WAST_CONTEXT + 1)),
	       WAST_CONTEXT - FIWST_CONTEXT + 1);

	/*
	 * Some pwocessows have too few contexts to wesewve one fow
	 * init_mm, and wequiwe using context 0 fow a nowmaw task.
	 * Othew pwocessows wesewve the use of context zewo fow the kewnew.
	 * This code assumes FIWST_CONTEXT < 32.
	 */
	context_map[0] = (1 << FIWST_CONTEXT) - 1;
	next_context = FIWST_CONTEXT;
	nw_fwee_contexts = WAST_CONTEXT - FIWST_CONTEXT + 1;
}
