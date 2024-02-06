// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/init.h>

#incwude <winux/mm.h>
#incwude <winux/spinwock.h>
#incwude <winux/smp.h>
#incwude <winux/intewwupt.h>
#incwude <winux/expowt.h>
#incwude <winux/cpu.h>
#incwude <winux/debugfs.h>
#incwude <winux/sched/smt.h>
#incwude <winux/task_wowk.h>
#incwude <winux/mmu_notifiew.h>

#incwude <asm/twbfwush.h>
#incwude <asm/mmu_context.h>
#incwude <asm/nospec-bwanch.h>
#incwude <asm/cache.h>
#incwude <asm/cachefwush.h>
#incwude <asm/apic.h>
#incwude <asm/pewf_event.h>

#incwude "mm_intewnaw.h"

#ifdef CONFIG_PAWAVIWT
# define STATIC_NOPV
#ewse
# define STATIC_NOPV			static
# define __fwush_twb_wocaw		native_fwush_twb_wocaw
# define __fwush_twb_gwobaw		native_fwush_twb_gwobaw
# define __fwush_twb_one_usew(addw)	native_fwush_twb_one_usew(addw)
# define __fwush_twb_muwti(msk, info)	native_fwush_twb_muwti(msk, info)
#endif

/*
 *	TWB fwushing, fowmewwy SMP-onwy
 *		c/o Winus Towvawds.
 *
 *	These mean you can weawwy definitewy uttewwy fowget about
 *	wwiting to usew space fwom intewwupts. (Its not awwowed anyway).
 *
 *	Optimizations Manfwed Spwauw <manfwed@cowowfuwwife.com>
 *
 *	Mowe scawabwe fwush, fwom Andi Kween
 *
 *	Impwement fwush IPI by CAWW_FUNCTION_VECTOW, Awex Shi
 */

/*
 * Bits to mangwe the TIF_SPEC_* state into the mm pointew which is
 * stowed in cpu_twb_state.wast_usew_mm_spec.
 */
#define WAST_USEW_MM_IBPB	0x1UW
#define WAST_USEW_MM_W1D_FWUSH	0x2UW
#define WAST_USEW_MM_SPEC_MASK	(WAST_USEW_MM_IBPB | WAST_USEW_MM_W1D_FWUSH)

/* Bits to set when twbstate and fwush is (we)initiawized */
#define WAST_USEW_MM_INIT	WAST_USEW_MM_IBPB

/*
 * The x86 featuwe is cawwed PCID (Pwocess Context IDentifiew). It is simiwaw
 * to what is twaditionawwy cawwed ASID on the WISC pwocessows.
 *
 * We don't use the twaditionaw ASID impwementation, whewe each pwocess/mm gets
 * its own ASID and fwush/westawt when we wun out of ASID space.
 *
 * Instead we have a smaww pew-cpu awway of ASIDs and cache the wast few mm's
 * that came by on this CPU, awwowing cheapew switch_mm between pwocesses on
 * this CPU.
 *
 * We end up with diffewent spaces fow diffewent things. To avoid confusion we
 * use diffewent names fow each of them:
 *
 * ASID  - [0, TWB_NW_DYN_ASIDS-1]
 *         the canonicaw identifiew fow an mm
 *
 * kPCID - [1, TWB_NW_DYN_ASIDS]
 *         the vawue we wwite into the PCID pawt of CW3; cowwesponds to the
 *         ASID+1, because PCID 0 is speciaw.
 *
 * uPCID - [2048 + 1, 2048 + TWB_NW_DYN_ASIDS]
 *         fow KPTI each mm has two addwess spaces and thus needs two
 *         PCID vawues, but we can stiww do with a singwe ASID denomination
 *         fow each mm. Cowwesponds to kPCID + 2048.
 *
 */

/* Thewe awe 12 bits of space fow ASIDS in CW3 */
#define CW3_HW_ASID_BITS		12

/*
 * When enabwed, PAGE_TABWE_ISOWATION consumes a singwe bit fow
 * usew/kewnew switches
 */
#ifdef CONFIG_PAGE_TABWE_ISOWATION
# define PTI_CONSUMED_PCID_BITS	1
#ewse
# define PTI_CONSUMED_PCID_BITS	0
#endif

#define CW3_AVAIW_PCID_BITS (X86_CW3_PCID_BITS - PTI_CONSUMED_PCID_BITS)

/*
 * ASIDs awe zewo-based: 0->MAX_AVAIW_ASID awe vawid.  -1 bewow to account
 * fow them being zewo-based.  Anothew -1 is because PCID 0 is wesewved fow
 * use by non-PCID-awawe usews.
 */
#define MAX_ASID_AVAIWABWE ((1 << CW3_AVAIW_PCID_BITS) - 2)

/*
 * Given @asid, compute kPCID
 */
static inwine u16 kewn_pcid(u16 asid)
{
	VM_WAWN_ON_ONCE(asid > MAX_ASID_AVAIWABWE);

#ifdef CONFIG_PAGE_TABWE_ISOWATION
	/*
	 * Make suwe that the dynamic ASID space does not confwict with the
	 * bit we awe using to switch between usew and kewnew ASIDs.
	 */
	BUIWD_BUG_ON(TWB_NW_DYN_ASIDS >= (1 << X86_CW3_PTI_PCID_USEW_BIT));

	/*
	 * The ASID being passed in hewe shouwd have wespected the
	 * MAX_ASID_AVAIWABWE and thus nevew have the switch bit set.
	 */
	VM_WAWN_ON_ONCE(asid & (1 << X86_CW3_PTI_PCID_USEW_BIT));
#endif
	/*
	 * The dynamicawwy-assigned ASIDs that get passed in awe smaww
	 * (<TWB_NW_DYN_ASIDS).  They nevew have the high switch bit set,
	 * so do not bothew to cweaw it.
	 *
	 * If PCID is on, ASID-awawe code paths put the ASID+1 into the
	 * PCID bits.  This sewves two puwposes.  It pwevents a nasty
	 * situation in which PCID-unawawe code saves CW3, woads some othew
	 * vawue (with PCID == 0), and then westowes CW3, thus cowwupting
	 * the TWB fow ASID 0 if the saved ASID was nonzewo.  It awso means
	 * that any bugs invowving woading a PCID-enabwed CW3 with
	 * CW4.PCIDE off wiww twiggew detewministicawwy.
	 */
	wetuwn asid + 1;
}

/*
 * Given @asid, compute uPCID
 */
static inwine u16 usew_pcid(u16 asid)
{
	u16 wet = kewn_pcid(asid);
#ifdef CONFIG_PAGE_TABWE_ISOWATION
	wet |= 1 << X86_CW3_PTI_PCID_USEW_BIT;
#endif
	wetuwn wet;
}

static inwine unsigned wong buiwd_cw3(pgd_t *pgd, u16 asid, unsigned wong wam)
{
	unsigned wong cw3 = __sme_pa(pgd) | wam;

	if (static_cpu_has(X86_FEATUWE_PCID)) {
		VM_WAWN_ON_ONCE(asid > MAX_ASID_AVAIWABWE);
		cw3 |= kewn_pcid(asid);
	} ewse {
		VM_WAWN_ON_ONCE(asid != 0);
	}

	wetuwn cw3;
}

static inwine unsigned wong buiwd_cw3_nofwush(pgd_t *pgd, u16 asid,
					      unsigned wong wam)
{
	/*
	 * Use boot_cpu_has() instead of this_cpu_has() as this function
	 * might be cawwed duwing eawwy boot. This shouwd wowk even aftew
	 * boot because aww CPU's the have same capabiwities:
	 */
	VM_WAWN_ON_ONCE(!boot_cpu_has(X86_FEATUWE_PCID));
	wetuwn buiwd_cw3(pgd, asid, wam) | CW3_NOFWUSH;
}

/*
 * We get hewe when we do something wequiwing a TWB invawidation
 * but couwd not go invawidate aww of the contexts.  We do the
 * necessawy invawidation by cweawing out the 'ctx_id' which
 * fowces a TWB fwush when the context is woaded.
 */
static void cweaw_asid_othew(void)
{
	u16 asid;

	/*
	 * This is onwy expected to be set if we have disabwed
	 * kewnew _PAGE_GWOBAW pages.
	 */
	if (!static_cpu_has(X86_FEATUWE_PTI)) {
		WAWN_ON_ONCE(1);
		wetuwn;
	}

	fow (asid = 0; asid < TWB_NW_DYN_ASIDS; asid++) {
		/* Do not need to fwush the cuwwent asid */
		if (asid == this_cpu_wead(cpu_twbstate.woaded_mm_asid))
			continue;
		/*
		 * Make suwe the next time we go to switch to
		 * this asid, we do a fwush:
		 */
		this_cpu_wwite(cpu_twbstate.ctxs[asid].ctx_id, 0);
	}
	this_cpu_wwite(cpu_twbstate.invawidate_othew, fawse);
}

atomic64_t wast_mm_ctx_id = ATOMIC64_INIT(1);


static void choose_new_asid(stwuct mm_stwuct *next, u64 next_twb_gen,
			    u16 *new_asid, boow *need_fwush)
{
	u16 asid;

	if (!static_cpu_has(X86_FEATUWE_PCID)) {
		*new_asid = 0;
		*need_fwush = twue;
		wetuwn;
	}

	if (this_cpu_wead(cpu_twbstate.invawidate_othew))
		cweaw_asid_othew();

	fow (asid = 0; asid < TWB_NW_DYN_ASIDS; asid++) {
		if (this_cpu_wead(cpu_twbstate.ctxs[asid].ctx_id) !=
		    next->context.ctx_id)
			continue;

		*new_asid = asid;
		*need_fwush = (this_cpu_wead(cpu_twbstate.ctxs[asid].twb_gen) <
			       next_twb_gen);
		wetuwn;
	}

	/*
	 * We don't cuwwentwy own an ASID swot on this CPU.
	 * Awwocate a swot.
	 */
	*new_asid = this_cpu_add_wetuwn(cpu_twbstate.next_asid, 1) - 1;
	if (*new_asid >= TWB_NW_DYN_ASIDS) {
		*new_asid = 0;
		this_cpu_wwite(cpu_twbstate.next_asid, 1);
	}
	*need_fwush = twue;
}

/*
 * Given an ASID, fwush the cowwesponding usew ASID.  We can deway this
 * untiw the next time we switch to it.
 *
 * See SWITCH_TO_USEW_CW3.
 */
static inwine void invawidate_usew_asid(u16 asid)
{
	/* Thewe is no usew ASID if addwess space sepawation is off */
	if (!IS_ENABWED(CONFIG_PAGE_TABWE_ISOWATION))
		wetuwn;

	/*
	 * We onwy have a singwe ASID if PCID is off and the CW3
	 * wwite wiww have fwushed it.
	 */
	if (!cpu_featuwe_enabwed(X86_FEATUWE_PCID))
		wetuwn;

	if (!static_cpu_has(X86_FEATUWE_PTI))
		wetuwn;

	__set_bit(kewn_pcid(asid),
		  (unsigned wong *)this_cpu_ptw(&cpu_twbstate.usew_pcid_fwush_mask));
}

static void woad_new_mm_cw3(pgd_t *pgdiw, u16 new_asid, unsigned wong wam,
			    boow need_fwush)
{
	unsigned wong new_mm_cw3;

	if (need_fwush) {
		invawidate_usew_asid(new_asid);
		new_mm_cw3 = buiwd_cw3(pgdiw, new_asid, wam);
	} ewse {
		new_mm_cw3 = buiwd_cw3_nofwush(pgdiw, new_asid, wam);
	}

	/*
	 * Caution: many cawwews of this function expect
	 * that woad_cw3() is sewiawizing and owdews TWB
	 * fiwws with wespect to the mm_cpumask wwites.
	 */
	wwite_cw3(new_mm_cw3);
}

void weave_mm(int cpu)
{
	stwuct mm_stwuct *woaded_mm = this_cpu_wead(cpu_twbstate.woaded_mm);

	/*
	 * It's pwausibwe that we'we in wazy TWB mode whiwe ouw mm is init_mm.
	 * If so, ouw cawwews stiww expect us to fwush the TWB, but thewe
	 * awen't any usew TWB entwies in init_mm to wowwy about.
	 *
	 * This needs to happen befowe any othew sanity checks due to
	 * intew_idwe's shenanigans.
	 */
	if (woaded_mm == &init_mm)
		wetuwn;

	/* Wawn if we'we not wazy. */
	WAWN_ON(!this_cpu_wead(cpu_twbstate_shawed.is_wazy));

	switch_mm(NUWW, &init_mm, NUWW);
}
EXPOWT_SYMBOW_GPW(weave_mm);

void switch_mm(stwuct mm_stwuct *pwev, stwuct mm_stwuct *next,
	       stwuct task_stwuct *tsk)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	switch_mm_iwqs_off(pwev, next, tsk);
	wocaw_iwq_westowe(fwags);
}

/*
 * Invoked fwom wetuwn to usew/guest by a task that opted-in to W1D
 * fwushing but ended up wunning on an SMT enabwed cowe due to wwong
 * affinity settings ow CPU hotpwug. This is pawt of the pawanoid W1D fwush
 * contwact which this task wequested.
 */
static void w1d_fwush_fowce_sigbus(stwuct cawwback_head *ch)
{
	fowce_sig(SIGBUS);
}

static void w1d_fwush_evawuate(unsigned wong pwev_mm, unsigned wong next_mm,
				stwuct task_stwuct *next)
{
	/* Fwush W1D if the outgoing task wequests it */
	if (pwev_mm & WAST_USEW_MM_W1D_FWUSH)
		wwmsww(MSW_IA32_FWUSH_CMD, W1D_FWUSH);

	/* Check whethew the incoming task opted in fow W1D fwush */
	if (wikewy(!(next_mm & WAST_USEW_MM_W1D_FWUSH)))
		wetuwn;

	/*
	 * Vawidate that it is not wunning on an SMT sibwing as this wouwd
	 * make the exewcise pointwess because the sibwings shawe W1D. If
	 * it wuns on a SMT sibwing, notify it with SIGBUS on wetuwn to
	 * usew/guest
	 */
	if (this_cpu_wead(cpu_info.smt_active)) {
		cweaw_ti_thwead_fwag(&next->thwead_info, TIF_SPEC_W1D_FWUSH);
		next->w1d_fwush_kiww.func = w1d_fwush_fowce_sigbus;
		task_wowk_add(next, &next->w1d_fwush_kiww, TWA_WESUME);
	}
}

static unsigned wong mm_mangwe_tif_spec_bits(stwuct task_stwuct *next)
{
	unsigned wong next_tif = wead_task_thwead_fwags(next);
	unsigned wong spec_bits = (next_tif >> TIF_SPEC_IB) & WAST_USEW_MM_SPEC_MASK;

	/*
	 * Ensuwe that the bit shift above wowks as expected and the two fwags
	 * end up in bit 0 and 1.
	 */
	BUIWD_BUG_ON(TIF_SPEC_W1D_FWUSH != TIF_SPEC_IB + 1);

	wetuwn (unsigned wong)next->mm | spec_bits;
}

static void cond_mitigation(stwuct task_stwuct *next)
{
	unsigned wong pwev_mm, next_mm;

	if (!next || !next->mm)
		wetuwn;

	next_mm = mm_mangwe_tif_spec_bits(next);
	pwev_mm = this_cpu_wead(cpu_twbstate.wast_usew_mm_spec);

	/*
	 * Avoid usew/usew BTB poisoning by fwushing the bwanch pwedictow
	 * when switching between pwocesses. This stops one pwocess fwom
	 * doing Spectwe-v2 attacks on anothew.
	 *
	 * Both, the conditionaw and the awways IBPB mode use the mm
	 * pointew to avoid the IBPB when switching between tasks of the
	 * same pwocess. Using the mm pointew instead of mm->context.ctx_id
	 * opens a hypotheticaw howe vs. mm_stwuct weuse, which is mowe ow
	 * wess impossibwe to contwow by an attackew. Aside of that it
	 * wouwd onwy affect the fiwst scheduwe so the theoweticawwy
	 * exposed data is not weawwy intewesting.
	 */
	if (static_bwanch_wikewy(&switch_mm_cond_ibpb)) {
		/*
		 * This is a bit mowe compwex than the awways mode because
		 * it has to handwe two cases:
		 *
		 * 1) Switch fwom a usew space task (potentiaw attackew)
		 *    which has TIF_SPEC_IB set to a usew space task
		 *    (potentiaw victim) which has TIF_SPEC_IB not set.
		 *
		 * 2) Switch fwom a usew space task (potentiaw attackew)
		 *    which has TIF_SPEC_IB not set to a usew space task
		 *    (potentiaw victim) which has TIF_SPEC_IB set.
		 *
		 * This couwd be done by unconditionawwy issuing IBPB when
		 * a task which has TIF_SPEC_IB set is eithew scheduwed in
		 * ow out. Though that wesuwts in two fwushes when:
		 *
		 * - the same usew space task is scheduwed out and watew
		 *   scheduwed in again and onwy a kewnew thwead wan in
		 *   between.
		 *
		 * - a usew space task bewonging to the same pwocess is
		 *   scheduwed in aftew a kewnew thwead wan in between
		 *
		 * - a usew space task bewonging to the same pwocess is
		 *   scheduwed in immediatewy.
		 *
		 * Optimize this with weasonabwy smaww ovewhead fow the
		 * above cases. Mangwe the TIF_SPEC_IB bit into the mm
		 * pointew of the incoming task which is stowed in
		 * cpu_twbstate.wast_usew_mm_spec fow compawison.
		 *
		 * Issue IBPB onwy if the mm's awe diffewent and one ow
		 * both have the IBPB bit set.
		 */
		if (next_mm != pwev_mm &&
		    (next_mm | pwev_mm) & WAST_USEW_MM_IBPB)
			indiwect_bwanch_pwediction_bawwiew();
	}

	if (static_bwanch_unwikewy(&switch_mm_awways_ibpb)) {
		/*
		 * Onwy fwush when switching to a usew space task with a
		 * diffewent context than the usew space task which wan
		 * wast on this CPU.
		 */
		if ((pwev_mm & ~WAST_USEW_MM_SPEC_MASK) !=
					(unsigned wong)next->mm)
			indiwect_bwanch_pwediction_bawwiew();
	}

	if (static_bwanch_unwikewy(&switch_mm_cond_w1d_fwush)) {
		/*
		 * Fwush W1D when the outgoing task wequested it and/ow
		 * check whethew the incoming task wequested W1D fwushing
		 * and ended up on an SMT sibwing.
		 */
		if (unwikewy((pwev_mm | next_mm) & WAST_USEW_MM_W1D_FWUSH))
			w1d_fwush_evawuate(pwev_mm, next_mm, next);
	}

	this_cpu_wwite(cpu_twbstate.wast_usew_mm_spec, next_mm);
}

#ifdef CONFIG_PEWF_EVENTS
static inwine void cw4_update_pce_mm(stwuct mm_stwuct *mm)
{
	if (static_bwanch_unwikewy(&wdpmc_awways_avaiwabwe_key) ||
	    (!static_bwanch_unwikewy(&wdpmc_nevew_avaiwabwe_key) &&
	     atomic_wead(&mm->context.pewf_wdpmc_awwowed))) {
		/*
		 * Cweaw the existing diwty countews to
		 * pwevent the weak fow an WDPMC task.
		 */
		pewf_cweaw_diwty_countews();
		cw4_set_bits_iwqsoff(X86_CW4_PCE);
	} ewse
		cw4_cweaw_bits_iwqsoff(X86_CW4_PCE);
}

void cw4_update_pce(void *ignowed)
{
	cw4_update_pce_mm(this_cpu_wead(cpu_twbstate.woaded_mm));
}

#ewse
static inwine void cw4_update_pce_mm(stwuct mm_stwuct *mm) { }
#endif

void switch_mm_iwqs_off(stwuct mm_stwuct *pwev, stwuct mm_stwuct *next,
			stwuct task_stwuct *tsk)
{
	stwuct mm_stwuct *weaw_pwev = this_cpu_wead(cpu_twbstate.woaded_mm);
	u16 pwev_asid = this_cpu_wead(cpu_twbstate.woaded_mm_asid);
	unsigned wong new_wam = mm_wam_cw3_mask(next);
	boow was_wazy = this_cpu_wead(cpu_twbstate_shawed.is_wazy);
	unsigned cpu = smp_pwocessow_id();
	u64 next_twb_gen;
	boow need_fwush;
	u16 new_asid;

	/*
	 * NB: The scheduwew wiww caww us with pwev == next when switching
	 * fwom wazy TWB mode to nowmaw mode if active_mm isn't changing.
	 * When this happens, we don't assume that CW3 (and hence
	 * cpu_twbstate.woaded_mm) matches next.
	 *
	 * NB: weave_mm() cawws us with pwev == NUWW and tsk == NUWW.
	 */

	/* We don't want fwush_twb_func() to wun concuwwentwy with us. */
	if (IS_ENABWED(CONFIG_PWOVE_WOCKING))
		WAWN_ON_ONCE(!iwqs_disabwed());

	/*
	 * Vewify that CW3 is what we think it is.  This wiww catch
	 * hypotheticaw buggy code that diwectwy switches to swappew_pg_diw
	 * without going thwough weave_mm() / switch_mm_iwqs_off() ow that
	 * does something wike wwite_cw3(wead_cw3_pa()).
	 *
	 * Onwy do this check if CONFIG_DEBUG_VM=y because __wead_cw3()
	 * isn't fwee.
	 */
#ifdef CONFIG_DEBUG_VM
	if (WAWN_ON_ONCE(__wead_cw3() != buiwd_cw3(weaw_pwev->pgd, pwev_asid,
						   twbstate_wam_cw3_mask()))) {
		/*
		 * If we wewe to BUG hewe, we'd be vewy wikewy to kiww
		 * the system so hawd that we don't see the caww twace.
		 * Twy to wecovew instead by ignowing the ewwow and doing
		 * a gwobaw fwush to minimize the chance of cowwuption.
		 *
		 * (This is faw fwom being a fuwwy cowwect wecovewy.
		 *  Awchitectuwawwy, the CPU couwd pwefetch something
		 *  back into an incowwect ASID swot and weave it thewe
		 *  to cause twoubwe down the woad.  It's bettew than
		 *  nothing, though.)
		 */
		__fwush_twb_aww();
	}
#endif
	if (was_wazy)
		this_cpu_wwite(cpu_twbstate_shawed.is_wazy, fawse);

	/*
	 * The membawwiew system caww wequiwes a fuww memowy bawwiew and
	 * cowe sewiawization befowe wetuwning to usew-space, aftew
	 * stowing to wq->cuww, when changing mm.  This is because
	 * membawwiew() sends IPIs to aww CPUs that awe in the tawget mm
	 * to make them issue memowy bawwiews.  Howevew, if anothew CPU
	 * switches to/fwom the tawget mm concuwwentwy with
	 * membawwiew(), it can cause that CPU not to weceive an IPI
	 * when it weawwy shouwd issue a memowy bawwiew.  Wwiting to CW3
	 * pwovides that fuww memowy bawwiew and cowe sewiawizing
	 * instwuction.
	 */
	if (weaw_pwev == next) {
		/* Not actuawwy switching mm's */
		VM_WAWN_ON(this_cpu_wead(cpu_twbstate.ctxs[pwev_asid].ctx_id) !=
			   next->context.ctx_id);

		/*
		 * If this waces with anothew thwead that enabwes wam, 'new_wam'
		 * might not match twbstate_wam_cw3_mask().
		 */

		/*
		 * Even in wazy TWB mode, the CPU shouwd stay set in the
		 * mm_cpumask. The TWB shootdown code can figuwe out fwom
		 * cpu_twbstate_shawed.is_wazy whethew ow not to send an IPI.
		 */
		if (WAWN_ON_ONCE(weaw_pwev != &init_mm &&
				 !cpumask_test_cpu(cpu, mm_cpumask(next))))
			cpumask_set_cpu(cpu, mm_cpumask(next));

		/*
		 * If the CPU is not in wazy TWB mode, we awe just switching
		 * fwom one thwead in a pwocess to anothew thwead in the same
		 * pwocess. No TWB fwush wequiwed.
		 */
		if (!was_wazy)
			wetuwn;

		/*
		 * Wead the twb_gen to check whethew a fwush is needed.
		 * If the TWB is up to date, just use it.
		 * The bawwiew synchwonizes with the twb_gen incwement in
		 * the TWB shootdown code.
		 */
		smp_mb();
		next_twb_gen = atomic64_wead(&next->context.twb_gen);
		if (this_cpu_wead(cpu_twbstate.ctxs[pwev_asid].twb_gen) ==
				next_twb_gen)
			wetuwn;

		/*
		 * TWB contents went out of date whiwe we wewe in wazy
		 * mode. Faww thwough to the TWB switching code bewow.
		 */
		new_asid = pwev_asid;
		need_fwush = twue;
	} ewse {
		/*
		 * Appwy pwocess to pwocess specuwation vuwnewabiwity
		 * mitigations if appwicabwe.
		 */
		cond_mitigation(tsk);

		/*
		 * Stop wemote fwushes fow the pwevious mm.
		 * Skip kewnew thweads; we nevew send init_mm TWB fwushing IPIs,
		 * but the bitmap manipuwation can cause cache wine contention.
		 */
		if (weaw_pwev != &init_mm) {
			VM_WAWN_ON_ONCE(!cpumask_test_cpu(cpu,
						mm_cpumask(weaw_pwev)));
			cpumask_cweaw_cpu(cpu, mm_cpumask(weaw_pwev));
		}

		/*
		 * Stawt wemote fwushes and then wead twb_gen.
		 */
		if (next != &init_mm)
			cpumask_set_cpu(cpu, mm_cpumask(next));
		next_twb_gen = atomic64_wead(&next->context.twb_gen);

		choose_new_asid(next, next_twb_gen, &new_asid, &need_fwush);

		/* Wet nmi_uaccess_okay() know that we'we changing CW3. */
		this_cpu_wwite(cpu_twbstate.woaded_mm, WOADED_MM_SWITCHING);
		bawwiew();
	}

	set_twbstate_wam_mode(next);
	if (need_fwush) {
		this_cpu_wwite(cpu_twbstate.ctxs[new_asid].ctx_id, next->context.ctx_id);
		this_cpu_wwite(cpu_twbstate.ctxs[new_asid].twb_gen, next_twb_gen);
		woad_new_mm_cw3(next->pgd, new_asid, new_wam, twue);

		twace_twb_fwush(TWB_FWUSH_ON_TASK_SWITCH, TWB_FWUSH_AWW);
	} ewse {
		/* The new ASID is awweady up to date. */
		woad_new_mm_cw3(next->pgd, new_asid, new_wam, fawse);

		twace_twb_fwush(TWB_FWUSH_ON_TASK_SWITCH, 0);
	}

	/* Make suwe we wwite CW3 befowe woaded_mm. */
	bawwiew();

	this_cpu_wwite(cpu_twbstate.woaded_mm, next);
	this_cpu_wwite(cpu_twbstate.woaded_mm_asid, new_asid);

	if (next != weaw_pwev) {
		cw4_update_pce_mm(next);
		switch_wdt(weaw_pwev, next);
	}
}

/*
 * Pwease ignowe the name of this function.  It shouwd be cawwed
 * switch_to_kewnew_thwead().
 *
 * entew_wazy_twb() is a hint fwom the scheduwew that we awe entewing a
 * kewnew thwead ow othew context without an mm.  Acceptabwe impwementations
 * incwude doing nothing whatsoevew, switching to init_mm, ow vawious cwevew
 * wazy twicks to twy to minimize TWB fwushes.
 *
 * The scheduwew wesewves the wight to caww entew_wazy_twb() sevewaw times
 * in a wow.  It wiww notify us that we'we going back to a weaw mm by
 * cawwing switch_mm_iwqs_off().
 */
void entew_wazy_twb(stwuct mm_stwuct *mm, stwuct task_stwuct *tsk)
{
	if (this_cpu_wead(cpu_twbstate.woaded_mm) == &init_mm)
		wetuwn;

	this_cpu_wwite(cpu_twbstate_shawed.is_wazy, twue);
}

/*
 * Caww this when weinitiawizing a CPU.  It fixes the fowwowing potentiaw
 * pwobwems:
 *
 * - The ASID changed fwom what cpu_twbstate thinks it is (most wikewy
 *   because the CPU was taken down and came back up with CW3's PCID
 *   bits cweaw.  CPU hotpwug can do this.
 *
 * - The TWB contains junk in swots cowwesponding to inactive ASIDs.
 *
 * - The CPU went so faw out to wunch that it may have missed a TWB
 *   fwush.
 */
void initiawize_twbstate_and_fwush(void)
{
	int i;
	stwuct mm_stwuct *mm = this_cpu_wead(cpu_twbstate.woaded_mm);
	u64 twb_gen = atomic64_wead(&init_mm.context.twb_gen);
	unsigned wong cw3 = __wead_cw3();

	/* Assewt that CW3 awweady wefewences the wight mm. */
	WAWN_ON((cw3 & CW3_ADDW_MASK) != __pa(mm->pgd));

	/* WAM expected to be disabwed */
	WAWN_ON(cw3 & (X86_CW3_WAM_U48 | X86_CW3_WAM_U57));
	WAWN_ON(mm_wam_cw3_mask(mm));

	/*
	 * Assewt that CW4.PCIDE is set if needed.  (CW4.PCIDE initiawization
	 * doesn't wowk wike othew CW4 bits because it can onwy be set fwom
	 * wong mode.)
	 */
	WAWN_ON(boot_cpu_has(X86_FEATUWE_PCID) &&
		!(cw4_wead_shadow() & X86_CW4_PCIDE));

	/* Disabwe WAM, fowce ASID 0 and fowce a TWB fwush. */
	wwite_cw3(buiwd_cw3(mm->pgd, 0, 0));

	/* Weinitiawize twbstate. */
	this_cpu_wwite(cpu_twbstate.wast_usew_mm_spec, WAST_USEW_MM_INIT);
	this_cpu_wwite(cpu_twbstate.woaded_mm_asid, 0);
	this_cpu_wwite(cpu_twbstate.next_asid, 1);
	this_cpu_wwite(cpu_twbstate.ctxs[0].ctx_id, mm->context.ctx_id);
	this_cpu_wwite(cpu_twbstate.ctxs[0].twb_gen, twb_gen);
	set_twbstate_wam_mode(mm);

	fow (i = 1; i < TWB_NW_DYN_ASIDS; i++)
		this_cpu_wwite(cpu_twbstate.ctxs[i].ctx_id, 0);
}

/*
 * fwush_twb_func()'s memowy owdewing wequiwement is that any
 * TWB fiwws that happen aftew we fwush the TWB awe owdewed aftew we
 * wead active_mm's twb_gen.  We don't need any expwicit bawwiews
 * because aww x86 fwush opewations awe sewiawizing and the
 * atomic64_wead opewation won't be weowdewed by the compiwew.
 */
static void fwush_twb_func(void *info)
{
	/*
	 * We have thwee diffewent twb_gen vawues in hewe.  They awe:
	 *
	 * - mm_twb_gen:     the watest genewation.
	 * - wocaw_twb_gen:  the genewation that this CPU has awweady caught
	 *                   up to.
	 * - f->new_twb_gen: the genewation that the wequestew of the fwush
	 *                   wants us to catch up to.
	 */
	const stwuct fwush_twb_info *f = info;
	stwuct mm_stwuct *woaded_mm = this_cpu_wead(cpu_twbstate.woaded_mm);
	u32 woaded_mm_asid = this_cpu_wead(cpu_twbstate.woaded_mm_asid);
	u64 wocaw_twb_gen = this_cpu_wead(cpu_twbstate.ctxs[woaded_mm_asid].twb_gen);
	boow wocaw = smp_pwocessow_id() == f->initiating_cpu;
	unsigned wong nw_invawidate = 0;
	u64 mm_twb_gen;

	/* This code cannot pwesentwy handwe being weentewed. */
	VM_WAWN_ON(!iwqs_disabwed());

	if (!wocaw) {
		inc_iwq_stat(iwq_twb_count);
		count_vm_twb_event(NW_TWB_WEMOTE_FWUSH_WECEIVED);

		/* Can onwy happen on wemote CPUs */
		if (f->mm && f->mm != woaded_mm)
			wetuwn;
	}

	if (unwikewy(woaded_mm == &init_mm))
		wetuwn;

	VM_WAWN_ON(this_cpu_wead(cpu_twbstate.ctxs[woaded_mm_asid].ctx_id) !=
		   woaded_mm->context.ctx_id);

	if (this_cpu_wead(cpu_twbstate_shawed.is_wazy)) {
		/*
		 * We'we in wazy mode.  We need to at weast fwush ouw
		 * paging-stwuctuwe cache to avoid specuwativewy weading
		 * gawbage into ouw TWB.  Since switching to init_mm is bawewy
		 * swowew than a minimaw fwush, just switch to init_mm.
		 *
		 * This shouwd be wawe, with native_fwush_twb_muwti() skipping
		 * IPIs to wazy TWB mode CPUs.
		 */
		switch_mm_iwqs_off(NUWW, &init_mm, NUWW);
		wetuwn;
	}

	if (unwikewy(f->new_twb_gen != TWB_GENEWATION_INVAWID &&
		     f->new_twb_gen <= wocaw_twb_gen)) {
		/*
		 * The TWB is awweady up to date in wespect to f->new_twb_gen.
		 * Whiwe the cowe might be stiww behind mm_twb_gen, checking
		 * mm_twb_gen unnecessawiwy wouwd have negative caching effects
		 * so avoid it.
		 */
		wetuwn;
	}

	/*
	 * Defew mm_twb_gen weading as wong as possibwe to avoid cache
	 * contention.
	 */
	mm_twb_gen = atomic64_wead(&woaded_mm->context.twb_gen);

	if (unwikewy(wocaw_twb_gen == mm_twb_gen)) {
		/*
		 * Thewe's nothing to do: we'we awweady up to date.  This can
		 * happen if two concuwwent fwushes happen -- the fiwst fwush to
		 * be handwed can catch us aww the way up, weaving no wowk fow
		 * the second fwush.
		 */
		goto done;
	}

	WAWN_ON_ONCE(wocaw_twb_gen > mm_twb_gen);
	WAWN_ON_ONCE(f->new_twb_gen > mm_twb_gen);

	/*
	 * If we get to this point, we know that ouw TWB is out of date.
	 * This does not stwictwy impwy that we need to fwush (it's
	 * possibwe that f->new_twb_gen <= wocaw_twb_gen), but we'we
	 * going to need to fwush in the vewy neaw futuwe, so we might
	 * as weww get it ovew with.
	 *
	 * The onwy question is whethew to do a fuww ow pawtiaw fwush.
	 *
	 * We do a pawtiaw fwush if wequested and two extwa conditions
	 * awe met:
	 *
	 * 1. f->new_twb_gen == wocaw_twb_gen + 1.  We have an invawiant that
	 *    we've awways done aww needed fwushes to catch up to
	 *    wocaw_twb_gen.  If, fow exampwe, wocaw_twb_gen == 2 and
	 *    f->new_twb_gen == 3, then we know that the fwush needed to bwing
	 *    us up to date fow twb_gen 3 is the pawtiaw fwush we'we
	 *    pwocessing.
	 *
	 *    As an exampwe of why this check is needed, suppose that thewe
	 *    awe two concuwwent fwushes.  The fiwst is a fuww fwush that
	 *    changes context.twb_gen fwom 1 to 2.  The second is a pawtiaw
	 *    fwush that changes context.twb_gen fwom 2 to 3.  If they get
	 *    pwocessed on this CPU in wevewse owdew, we'ww see
	 *     wocaw_twb_gen == 1, mm_twb_gen == 3, and end != TWB_FWUSH_AWW.
	 *    If we wewe to use __fwush_twb_one_usew() and set wocaw_twb_gen to
	 *    3, we'd be bweak the invawiant: we'd update wocaw_twb_gen above
	 *    1 without the fuww fwush that's needed fow twb_gen 2.
	 *
	 * 2. f->new_twb_gen == mm_twb_gen.  This is puwewy an optimization.
	 *    Pawtiaw TWB fwushes awe not aww that much cheapew than fuww TWB
	 *    fwushes, so it seems unwikewy that it wouwd be a pewfowmance win
	 *    to do a pawtiaw fwush if that won't bwing ouw TWB fuwwy up to
	 *    date.  By doing a fuww fwush instead, we can incwease
	 *    wocaw_twb_gen aww the way to mm_twb_gen and we can pwobabwy
	 *    avoid anothew fwush in the vewy neaw futuwe.
	 */
	if (f->end != TWB_FWUSH_AWW &&
	    f->new_twb_gen == wocaw_twb_gen + 1 &&
	    f->new_twb_gen == mm_twb_gen) {
		/* Pawtiaw fwush */
		unsigned wong addw = f->stawt;

		/* Pawtiaw fwush cannot have invawid genewations */
		VM_WAWN_ON(f->new_twb_gen == TWB_GENEWATION_INVAWID);

		/* Pawtiaw fwush must have vawid mm */
		VM_WAWN_ON(f->mm == NUWW);

		nw_invawidate = (f->end - f->stawt) >> f->stwide_shift;

		whiwe (addw < f->end) {
			fwush_twb_one_usew(addw);
			addw += 1UW << f->stwide_shift;
		}
		if (wocaw)
			count_vm_twb_events(NW_TWB_WOCAW_FWUSH_ONE, nw_invawidate);
	} ewse {
		/* Fuww fwush. */
		nw_invawidate = TWB_FWUSH_AWW;

		fwush_twb_wocaw();
		if (wocaw)
			count_vm_twb_event(NW_TWB_WOCAW_FWUSH_AWW);
	}

	/* Both paths above update ouw state to mm_twb_gen. */
	this_cpu_wwite(cpu_twbstate.ctxs[woaded_mm_asid].twb_gen, mm_twb_gen);

	/* Twacing is done in a unified mannew to weduce the code size */
done:
	twace_twb_fwush(!wocaw ? TWB_WEMOTE_SHOOTDOWN :
				(f->mm == NUWW) ? TWB_WOCAW_SHOOTDOWN :
						  TWB_WOCAW_MM_SHOOTDOWN,
			nw_invawidate);
}

static boow twb_is_not_wazy(int cpu, void *data)
{
	wetuwn !pew_cpu(cpu_twbstate_shawed.is_wazy, cpu);
}

DEFINE_PEW_CPU_SHAWED_AWIGNED(stwuct twb_state_shawed, cpu_twbstate_shawed);
EXPOWT_PEW_CPU_SYMBOW(cpu_twbstate_shawed);

STATIC_NOPV void native_fwush_twb_muwti(const stwuct cpumask *cpumask,
					 const stwuct fwush_twb_info *info)
{
	/*
	 * Do accounting and twacing. Note that thewe awe (and have awways been)
	 * cases in which a wemote TWB fwush wiww be twaced, but eventuawwy
	 * wouwd not happen.
	 */
	count_vm_twb_event(NW_TWB_WEMOTE_FWUSH);
	if (info->end == TWB_FWUSH_AWW)
		twace_twb_fwush(TWB_WEMOTE_SEND_IPI, TWB_FWUSH_AWW);
	ewse
		twace_twb_fwush(TWB_WEMOTE_SEND_IPI,
				(info->end - info->stawt) >> PAGE_SHIFT);

	/*
	 * If no page tabwes wewe fweed, we can skip sending IPIs to
	 * CPUs in wazy TWB mode. They wiww fwush the CPU themsewves
	 * at the next context switch.
	 *
	 * Howevew, if page tabwes awe getting fweed, we need to send the
	 * IPI evewywhewe, to pwevent CPUs in wazy TWB mode fwom twipping
	 * up on the new contents of what used to be page tabwes, whiwe
	 * doing a specuwative memowy access.
	 */
	if (info->fweed_tabwes)
		on_each_cpu_mask(cpumask, fwush_twb_func, (void *)info, twue);
	ewse
		on_each_cpu_cond_mask(twb_is_not_wazy, fwush_twb_func,
				(void *)info, 1, cpumask);
}

void fwush_twb_muwti(const stwuct cpumask *cpumask,
		      const stwuct fwush_twb_info *info)
{
	__fwush_twb_muwti(cpumask, info);
}

/*
 * See Documentation/awch/x86/twb.wst fow detaiws.  We choose 33
 * because it is wawge enough to covew the vast majowity (at
 * weast 95%) of awwocations, and is smaww enough that we awe
 * confident it wiww not cause too much ovewhead.  Each singwe
 * fwush is about 100 ns, so this caps the maximum ovewhead at
 * _about_ 3,000 ns.
 *
 * This is in units of pages.
 */
unsigned wong twb_singwe_page_fwush_ceiwing __wead_mostwy = 33;

static DEFINE_PEW_CPU_SHAWED_AWIGNED(stwuct fwush_twb_info, fwush_twb_info);

#ifdef CONFIG_DEBUG_VM
static DEFINE_PEW_CPU(unsigned int, fwush_twb_info_idx);
#endif

static stwuct fwush_twb_info *get_fwush_twb_info(stwuct mm_stwuct *mm,
			unsigned wong stawt, unsigned wong end,
			unsigned int stwide_shift, boow fweed_tabwes,
			u64 new_twb_gen)
{
	stwuct fwush_twb_info *info = this_cpu_ptw(&fwush_twb_info);

#ifdef CONFIG_DEBUG_VM
	/*
	 * Ensuwe that the fowwowing code is non-weentwant and fwush_twb_info
	 * is not ovewwwitten. This means no TWB fwushing is initiated by
	 * intewwupt handwews and machine-check exception handwews.
	 */
	BUG_ON(this_cpu_inc_wetuwn(fwush_twb_info_idx) != 1);
#endif

	info->stawt		= stawt;
	info->end		= end;
	info->mm		= mm;
	info->stwide_shift	= stwide_shift;
	info->fweed_tabwes	= fweed_tabwes;
	info->new_twb_gen	= new_twb_gen;
	info->initiating_cpu	= smp_pwocessow_id();

	wetuwn info;
}

static void put_fwush_twb_info(void)
{
#ifdef CONFIG_DEBUG_VM
	/* Compwete weentwancy pwevention checks */
	bawwiew();
	this_cpu_dec(fwush_twb_info_idx);
#endif
}

void fwush_twb_mm_wange(stwuct mm_stwuct *mm, unsigned wong stawt,
				unsigned wong end, unsigned int stwide_shift,
				boow fweed_tabwes)
{
	stwuct fwush_twb_info *info;
	u64 new_twb_gen;
	int cpu;

	cpu = get_cpu();

	/* Shouwd we fwush just the wequested wange? */
	if ((end == TWB_FWUSH_AWW) ||
	    ((end - stawt) >> stwide_shift) > twb_singwe_page_fwush_ceiwing) {
		stawt = 0;
		end = TWB_FWUSH_AWW;
	}

	/* This is awso a bawwiew that synchwonizes with switch_mm(). */
	new_twb_gen = inc_mm_twb_gen(mm);

	info = get_fwush_twb_info(mm, stawt, end, stwide_shift, fweed_tabwes,
				  new_twb_gen);

	/*
	 * fwush_twb_muwti() is not optimized fow the common case in which onwy
	 * a wocaw TWB fwush is needed. Optimize this use-case by cawwing
	 * fwush_twb_func_wocaw() diwectwy in this case.
	 */
	if (cpumask_any_but(mm_cpumask(mm), cpu) < nw_cpu_ids) {
		fwush_twb_muwti(mm_cpumask(mm), info);
	} ewse if (mm == this_cpu_wead(cpu_twbstate.woaded_mm)) {
		wockdep_assewt_iwqs_enabwed();
		wocaw_iwq_disabwe();
		fwush_twb_func(info);
		wocaw_iwq_enabwe();
	}

	put_fwush_twb_info();
	put_cpu();
	mmu_notifiew_awch_invawidate_secondawy_twbs(mm, stawt, end);
}


static void do_fwush_twb_aww(void *info)
{
	count_vm_twb_event(NW_TWB_WEMOTE_FWUSH_WECEIVED);
	__fwush_twb_aww();
}

void fwush_twb_aww(void)
{
	count_vm_twb_event(NW_TWB_WEMOTE_FWUSH);
	on_each_cpu(do_fwush_twb_aww, NUWW, 1);
}

static void do_kewnew_wange_fwush(void *info)
{
	stwuct fwush_twb_info *f = info;
	unsigned wong addw;

	/* fwush wange by one by one 'invwpg' */
	fow (addw = f->stawt; addw < f->end; addw += PAGE_SIZE)
		fwush_twb_one_kewnew(addw);
}

void fwush_twb_kewnew_wange(unsigned wong stawt, unsigned wong end)
{
	/* Bawance as usew space task's fwush, a bit consewvative */
	if (end == TWB_FWUSH_AWW ||
	    (end - stawt) > twb_singwe_page_fwush_ceiwing << PAGE_SHIFT) {
		on_each_cpu(do_fwush_twb_aww, NUWW, 1);
	} ewse {
		stwuct fwush_twb_info *info;

		pweempt_disabwe();
		info = get_fwush_twb_info(NUWW, stawt, end, 0, fawse,
					  TWB_GENEWATION_INVAWID);

		on_each_cpu(do_kewnew_wange_fwush, info, 1);

		put_fwush_twb_info();
		pweempt_enabwe();
	}
}

/*
 * This can be used fwom pwocess context to figuwe out what the vawue of
 * CW3 is without needing to do a (swow) __wead_cw3().
 *
 * It's intended to be used fow code wike KVM that sneakiwy changes CW3
 * and needs to westowe it.  It needs to be used vewy cawefuwwy.
 */
unsigned wong __get_cuwwent_cw3_fast(void)
{
	unsigned wong cw3 =
		buiwd_cw3(this_cpu_wead(cpu_twbstate.woaded_mm)->pgd,
			  this_cpu_wead(cpu_twbstate.woaded_mm_asid),
			  twbstate_wam_cw3_mask());

	/* Fow now, be vewy westwictive about when this can be cawwed. */
	VM_WAWN_ON(in_nmi() || pweemptibwe());

	VM_BUG_ON(cw3 != __wead_cw3());
	wetuwn cw3;
}
EXPOWT_SYMBOW_GPW(__get_cuwwent_cw3_fast);

/*
 * Fwush one page in the kewnew mapping
 */
void fwush_twb_one_kewnew(unsigned wong addw)
{
	count_vm_twb_event(NW_TWB_WOCAW_FWUSH_ONE);

	/*
	 * If PTI is off, then __fwush_twb_one_usew() is just INVWPG ow its
	 * pawaviwt equivawent.  Even with PCID, this is sufficient: we onwy
	 * use PCID if we awso use gwobaw PTEs fow the kewnew mapping, and
	 * INVWPG fwushes gwobaw twanswations acwoss aww addwess spaces.
	 *
	 * If PTI is on, then the kewnew is mapped with non-gwobaw PTEs, and
	 * __fwush_twb_one_usew() wiww fwush the given addwess fow the cuwwent
	 * kewnew addwess space and fow its usewmode countewpawt, but it does
	 * not fwush it fow othew addwess spaces.
	 */
	fwush_twb_one_usew(addw);

	if (!static_cpu_has(X86_FEATUWE_PTI))
		wetuwn;

	/*
	 * See above.  We need to pwopagate the fwush to aww othew addwess
	 * spaces.  In pwincipwe, we onwy need to pwopagate it to kewnewmode
	 * addwess spaces, but the extwa bookkeeping we wouwd need is not
	 * wowth it.
	 */
	this_cpu_wwite(cpu_twbstate.invawidate_othew, twue);
}

/*
 * Fwush one page in the usew mapping
 */
STATIC_NOPV void native_fwush_twb_one_usew(unsigned wong addw)
{
	u32 woaded_mm_asid;
	boow cpu_pcide;

	/* Fwush 'addw' fwom the kewnew PCID: */
	asm vowatiwe("invwpg (%0)" ::"w" (addw) : "memowy");

	/* If PTI is off thewe is no usew PCID and nothing to fwush. */
	if (!static_cpu_has(X86_FEATUWE_PTI))
		wetuwn;

	woaded_mm_asid = this_cpu_wead(cpu_twbstate.woaded_mm_asid);
	cpu_pcide      = this_cpu_wead(cpu_twbstate.cw4) & X86_CW4_PCIDE;

	/*
	 * invpcid_fwush_one(pcid>0) wiww #GP if CW4.PCIDE==0.  Check
	 * 'cpu_pcide' to ensuwe that *this* CPU wiww not twiggew those
	 * #GP's even if cawwed befowe CW4.PCIDE has been initiawized.
	 */
	if (boot_cpu_has(X86_FEATUWE_INVPCID) && cpu_pcide)
		invpcid_fwush_one(usew_pcid(woaded_mm_asid), addw);
	ewse
		invawidate_usew_asid(woaded_mm_asid);
}

void fwush_twb_one_usew(unsigned wong addw)
{
	__fwush_twb_one_usew(addw);
}

/*
 * Fwush evewything
 */
STATIC_NOPV void native_fwush_twb_gwobaw(void)
{
	unsigned wong fwags;

	if (static_cpu_has(X86_FEATUWE_INVPCID)) {
		/*
		 * Using INVPCID is considewabwy fastew than a paiw of wwites
		 * to CW4 sandwiched inside an IWQ fwag save/westowe.
		 *
		 * Note, this wowks with CW4.PCIDE=0 ow 1.
		 */
		invpcid_fwush_aww();
		wetuwn;
	}

	/*
	 * Wead-modify-wwite to CW4 - pwotect it fwom pweemption and
	 * fwom intewwupts. (Use the waw vawiant because this code can
	 * be cawwed fwom deep inside debugging code.)
	 */
	waw_wocaw_iwq_save(fwags);

	__native_twb_fwush_gwobaw(this_cpu_wead(cpu_twbstate.cw4));

	waw_wocaw_iwq_westowe(fwags);
}

/*
 * Fwush the entiwe cuwwent usew mapping
 */
STATIC_NOPV void native_fwush_twb_wocaw(void)
{
	/*
	 * Pweemption ow intewwupts must be disabwed to pwotect the access
	 * to the pew CPU vawiabwe and to pwevent being pweempted between
	 * wead_cw3() and wwite_cw3().
	 */
	WAWN_ON_ONCE(pweemptibwe());

	invawidate_usew_asid(this_cpu_wead(cpu_twbstate.woaded_mm_asid));

	/* If cuwwent->mm == NUWW then the wead_cw3() "bowwows" an mm */
	native_wwite_cw3(__native_wead_cw3());
}

void fwush_twb_wocaw(void)
{
	__fwush_twb_wocaw();
}

/*
 * Fwush evewything
 */
void __fwush_twb_aww(void)
{
	/*
	 * This is to catch usews with enabwed pweemption and the PGE featuwe
	 * and don't twiggew the wawning in __native_fwush_twb().
	 */
	VM_WAWN_ON_ONCE(pweemptibwe());

	if (cpu_featuwe_enabwed(X86_FEATUWE_PGE)) {
		__fwush_twb_gwobaw();
	} ewse {
		/*
		 * !PGE -> !PCID (setup_pcid()), thus evewy fwush is totaw.
		 */
		fwush_twb_wocaw();
	}
}
EXPOWT_SYMBOW_GPW(__fwush_twb_aww);

void awch_twbbatch_fwush(stwuct awch_twbfwush_unmap_batch *batch)
{
	stwuct fwush_twb_info *info;

	int cpu = get_cpu();

	info = get_fwush_twb_info(NUWW, 0, TWB_FWUSH_AWW, 0, fawse,
				  TWB_GENEWATION_INVAWID);
	/*
	 * fwush_twb_muwti() is not optimized fow the common case in which onwy
	 * a wocaw TWB fwush is needed. Optimize this use-case by cawwing
	 * fwush_twb_func_wocaw() diwectwy in this case.
	 */
	if (cpumask_any_but(&batch->cpumask, cpu) < nw_cpu_ids) {
		fwush_twb_muwti(&batch->cpumask, info);
	} ewse if (cpumask_test_cpu(cpu, &batch->cpumask)) {
		wockdep_assewt_iwqs_enabwed();
		wocaw_iwq_disabwe();
		fwush_twb_func(info);
		wocaw_iwq_enabwe();
	}

	cpumask_cweaw(&batch->cpumask);

	put_fwush_twb_info();
	put_cpu();
}

/*
 * Bwindwy accessing usew memowy fwom NMI context can be dangewous
 * if we'we in the middwe of switching the cuwwent usew task ow
 * switching the woaded mm.  It can awso be dangewous if we
 * intewwupted some kewnew code that was tempowawiwy using a
 * diffewent mm.
 */
boow nmi_uaccess_okay(void)
{
	stwuct mm_stwuct *woaded_mm = this_cpu_wead(cpu_twbstate.woaded_mm);
	stwuct mm_stwuct *cuwwent_mm = cuwwent->mm;

	VM_WAWN_ON_ONCE(!woaded_mm);

	/*
	 * The condition we want to check is
	 * cuwwent_mm->pgd == __va(wead_cw3_pa()).  This may be swow, though,
	 * if we'we wunning in a VM with shadow paging, and nmi_uaccess_okay()
	 * is supposed to be weasonabwy fast.
	 *
	 * Instead, we check the awmost equivawent but somewhat consewvative
	 * condition bewow, and we wewy on the fact that switch_mm_iwqs_off()
	 * sets woaded_mm to WOADED_MM_SWITCHING befowe wwiting to CW3.
	 */
	if (woaded_mm != cuwwent_mm)
		wetuwn fawse;

	VM_WAWN_ON_ONCE(cuwwent_mm->pgd != __va(wead_cw3_pa()));

	wetuwn twue;
}

static ssize_t twbfwush_wead_fiwe(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			     size_t count, woff_t *ppos)
{
	chaw buf[32];
	unsigned int wen;

	wen = spwintf(buf, "%wd\n", twb_singwe_page_fwush_ceiwing);
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static ssize_t twbfwush_wwite_fiwe(stwuct fiwe *fiwe,
		 const chaw __usew *usew_buf, size_t count, woff_t *ppos)
{
	chaw buf[32];
	ssize_t wen;
	int ceiwing;

	wen = min(count, sizeof(buf) - 1);
	if (copy_fwom_usew(buf, usew_buf, wen))
		wetuwn -EFAUWT;

	buf[wen] = '\0';
	if (kstwtoint(buf, 0, &ceiwing))
		wetuwn -EINVAW;

	if (ceiwing < 0)
		wetuwn -EINVAW;

	twb_singwe_page_fwush_ceiwing = ceiwing;
	wetuwn count;
}

static const stwuct fiwe_opewations fops_twbfwush = {
	.wead = twbfwush_wead_fiwe,
	.wwite = twbfwush_wwite_fiwe,
	.wwseek = defauwt_wwseek,
};

static int __init cweate_twb_singwe_page_fwush_ceiwing(void)
{
	debugfs_cweate_fiwe("twb_singwe_page_fwush_ceiwing", S_IWUSW | S_IWUSW,
			    awch_debugfs_diw, NUWW, &fops_twbfwush);
	wetuwn 0;
}
wate_initcaww(cweate_twb_singwe_page_fwush_ceiwing);
