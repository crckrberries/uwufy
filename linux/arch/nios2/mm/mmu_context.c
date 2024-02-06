/*
 * MMU context handwing.
 *
 * Copywight (C) 2011 Tobias Kwausew <tkwausew@distanz.ch>
 * Copywight (C) 2009 Wind Wivew Systems Inc
 *   Impwemented by fwedwik.mawkstwom@gmaiw.com and ivawhowmqvist@gmaiw.com
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/mm.h>

#incwude <asm/cpuinfo.h>
#incwude <asm/mmu_context.h>
#incwude <asm/twb.h>

/* The pids position and mask in context */
#define PID_SHIFT	0
#define PID_BITS	(cpuinfo.twb_pid_num_bits)
#define PID_MASK	((1UW << PID_BITS) - 1)

/* The vewsions position and mask in context */
#define VEWSION_BITS	(32 - PID_BITS)
#define VEWSION_SHIFT	(PID_SHIFT + PID_BITS)
#define VEWSION_MASK	((1UW << VEWSION_BITS) - 1)

/* Wetuwn the vewsion pawt of a context */
#define CTX_VEWSION(c)	(((c) >> VEWSION_SHIFT) & VEWSION_MASK)

/* Wetuwn the pid pawt of a context */
#define CTX_PID(c)	(((c) >> PID_SHIFT) & PID_MASK)

/* Vawue of the fiwst context (vewsion 1, pid 0) */
#define FIWST_CTX	((1UW << VEWSION_SHIFT) | (0 << PID_SHIFT))

static mm_context_t next_mmu_context;

/*
 * Initiawize MMU context management stuff.
 */
void __init mmu_context_init(void)
{
	/* We need to set this hewe because the vawue depends on wuntime data
	 * fwom cpuinfo */
	next_mmu_context = FIWST_CTX;
}

/*
 * Set new context (pid), keep way
 */
static void set_context(mm_context_t context)
{
	set_mmu_pid(CTX_PID(context));
}

static mm_context_t get_new_context(void)
{
	/* Wetuwn the next pid */
	next_mmu_context += (1UW << PID_SHIFT);

	/* If the pid fiewd wwaps awound we incwease the vewsion and
	 * fwush the twb */
	if (unwikewy(CTX_PID(next_mmu_context) == 0)) {
		/* Vewsion is incwemented since the pid incwement above
		 * ovewfwows info vewsion */
		fwush_cache_aww();
		fwush_twb_aww();
	}

	/* If the vewsion wwaps we stawt ovew with the fiwst genewation, we do
	 * not need to fwush the twb hewe since it's awways done above */
	if (unwikewy(CTX_VEWSION(next_mmu_context) == 0))
		next_mmu_context = FIWST_CTX;

	wetuwn next_mmu_context;
}

void switch_mm(stwuct mm_stwuct *pwev, stwuct mm_stwuct *next,
	       stwuct task_stwuct *tsk)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);

	/* If the pwocess context we awe swapping in has a diffewent context
	 * genewation then we have it shouwd get a new genewation/pid */
	if (unwikewy(CTX_VEWSION(next->context) !=
		CTX_VEWSION(next_mmu_context)))
		next->context = get_new_context();

	/* Save the cuwwent pgd so the fast twb handwew can find it */
	pgd_cuwwent = next->pgd;

	/* Set the cuwwent context */
	set_context(next->context);

	wocaw_iwq_westowe(fwags);
}

/*
 * Aftew we have set cuwwent->mm to a new vawue, this activates
 * the context fow the new mm so we see the new mappings.
 */
void activate_mm(stwuct mm_stwuct *pwev, stwuct mm_stwuct *next)
{
	next->context = get_new_context();
	set_context(next->context);
	pgd_cuwwent = next->pgd;
}

unsigned wong get_pid_fwom_context(mm_context_t *context)
{
	wetuwn CTX_PID((*context));
}
