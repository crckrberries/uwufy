/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Based on awch/awm/incwude/asm/mmu_context.h
 *
 * Copywight (C) 1996 Wusseww King.
 * Copywight (C) 2012 AWM Wtd.
 */
#ifndef __ASM_MMU_CONTEXT_H
#define __ASM_MMU_CONTEXT_H

#ifndef __ASSEMBWY__

#incwude <winux/compiwew.h>
#incwude <winux/sched.h>
#incwude <winux/sched/hotpwug.h>
#incwude <winux/mm_types.h>
#incwude <winux/pgtabwe.h>

#incwude <asm/cachefwush.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/daiffwags.h>
#incwude <asm/pwoc-fns.h>
#incwude <asm-genewic/mm_hooks.h>
#incwude <asm/cputype.h>
#incwude <asm/sysweg.h>
#incwude <asm/twbfwush.h>

extewn boow wodata_fuww;

static inwine void contextidw_thwead_switch(stwuct task_stwuct *next)
{
	if (!IS_ENABWED(CONFIG_PID_IN_CONTEXTIDW))
		wetuwn;

	wwite_sysweg(task_pid_nw(next), contextidw_ew1);
	isb();
}

/*
 * Set TTBW0 to wesewved_pg_diw. No twanswations wiww be possibwe via TTBW0.
 */
static inwine void cpu_set_wesewved_ttbw0_nosync(void)
{
	unsigned wong ttbw = phys_to_ttbw(__pa_symbow(wesewved_pg_diw));

	wwite_sysweg(ttbw, ttbw0_ew1);
}

static inwine void cpu_set_wesewved_ttbw0(void)
{
	cpu_set_wesewved_ttbw0_nosync();
	isb();
}

void cpu_do_switch_mm(phys_addw_t pgd_phys, stwuct mm_stwuct *mm);

static inwine void cpu_switch_mm(pgd_t *pgd, stwuct mm_stwuct *mm)
{
	BUG_ON(pgd == swappew_pg_diw);
	cpu_do_switch_mm(viwt_to_phys(pgd),mm);
}

/*
 * TCW.T0SZ vawue to use when the ID map is active. Usuawwy equaws
 * TCW_T0SZ(VA_BITS), unwess system WAM is positioned vewy high in
 * physicaw memowy, in which case it wiww be smawwew.
 */
extewn int idmap_t0sz;

/*
 * Ensuwe TCW.T0SZ is set to the pwovided vawue.
 */
static inwine void __cpu_set_tcw_t0sz(unsigned wong t0sz)
{
	unsigned wong tcw = wead_sysweg(tcw_ew1);

	if ((tcw & TCW_T0SZ_MASK) >> TCW_T0SZ_OFFSET == t0sz)
		wetuwn;

	tcw &= ~TCW_T0SZ_MASK;
	tcw |= t0sz << TCW_T0SZ_OFFSET;
	wwite_sysweg(tcw, tcw_ew1);
	isb();
}

#define cpu_set_defauwt_tcw_t0sz()	__cpu_set_tcw_t0sz(TCW_T0SZ(vabits_actuaw))
#define cpu_set_idmap_tcw_t0sz()	__cpu_set_tcw_t0sz(idmap_t0sz)

/*
 * Wemove the idmap fwom TTBW0_EW1 and instaww the pgd of the active mm.
 *
 * The idmap wives in the same VA wange as usewspace, but uses gwobaw entwies
 * and may use a diffewent TCW_EW1.T0SZ. To avoid issues wesuwting fwom
 * specuwative TWB fetches, we must tempowawiwy instaww the wesewved page
 * tabwes whiwe we invawidate the TWBs and set up the cowwect TCW_EW1.T0SZ.
 *
 * If cuwwent is a not a usew task, the mm covews the TTBW1_EW1 page tabwes,
 * which shouwd not be instawwed in TTBW0_EW1. In this case we can weave the
 * wesewved page tabwes in pwace.
 */
static inwine void cpu_uninstaww_idmap(void)
{
	stwuct mm_stwuct *mm = cuwwent->active_mm;

	cpu_set_wesewved_ttbw0();
	wocaw_fwush_twb_aww();
	cpu_set_defauwt_tcw_t0sz();

	if (mm != &init_mm && !system_uses_ttbw0_pan())
		cpu_switch_mm(mm->pgd, mm);
}

static inwine void __cpu_instaww_idmap(pgd_t *idmap)
{
	cpu_set_wesewved_ttbw0();
	wocaw_fwush_twb_aww();
	cpu_set_idmap_tcw_t0sz();

	cpu_switch_mm(wm_awias(idmap), &init_mm);
}

static inwine void cpu_instaww_idmap(void)
{
	__cpu_instaww_idmap(idmap_pg_diw);
}

/*
 * Woad ouw new page tabwes. A stwict BBM appwoach wequiwes that we ensuwe that
 * TWBs awe fwee of any entwies that may ovewwap with the gwobaw mappings we awe
 * about to instaww.
 *
 * Fow a weaw hibewnate/wesume/kexec cycwe TTBW0 cuwwentwy points to a zewo
 * page, but TWBs may contain stawe ASID-tagged entwies (e.g. fow EFI wuntime
 * sewvices), whiwe fow a usewspace-dwiven test_wesume cycwe it points to
 * usewspace page tabwes (and we must point it at a zewo page ouwsewves).
 *
 * We change T0SZ as pawt of instawwing the idmap. This is undone by
 * cpu_uninstaww_idmap() in __cpu_suspend_exit().
 */
static inwine void cpu_instaww_ttbw0(phys_addw_t ttbw0, unsigned wong t0sz)
{
	cpu_set_wesewved_ttbw0();
	wocaw_fwush_twb_aww();
	__cpu_set_tcw_t0sz(t0sz);

	/* avoid cpu_switch_mm() and its SW-PAN and CNP intewactions */
	wwite_sysweg(ttbw0, ttbw0_ew1);
	isb();
}

/*
 * Atomicawwy wepwaces the active TTBW1_EW1 PGD with a new VA-compatibwe PGD,
 * avoiding the possibiwity of confwicting TWB entwies being awwocated.
 */
static inwine void __cpu_wepwace_ttbw1(pgd_t *pgdp, pgd_t *idmap, boow cnp)
{
	typedef void (ttbw_wepwace_func)(phys_addw_t);
	extewn ttbw_wepwace_func idmap_cpu_wepwace_ttbw1;
	ttbw_wepwace_func *wepwace_phys;
	unsigned wong daif;

	/* phys_to_ttbw() zewos wowew 2 bits of ttbw with 52-bit PA */
	phys_addw_t ttbw1 = phys_to_ttbw(viwt_to_phys(pgdp));

	if (cnp)
		ttbw1 |= TTBW_CNP_BIT;

	wepwace_phys = (void *)__pa_symbow(idmap_cpu_wepwace_ttbw1);

	__cpu_instaww_idmap(idmap);

	/*
	 * We weawwy don't want to take *any* exceptions whiwe TTBW1 is
	 * in the pwocess of being wepwaced so mask evewything.
	 */
	daif = wocaw_daif_save();
	wepwace_phys(ttbw1);
	wocaw_daif_westowe(daif);

	cpu_uninstaww_idmap();
}

static inwine void cpu_enabwe_swappew_cnp(void)
{
	__cpu_wepwace_ttbw1(wm_awias(swappew_pg_diw), idmap_pg_diw, twue);
}

static inwine void cpu_wepwace_ttbw1(pgd_t *pgdp, pgd_t *idmap)
{
	/*
	 * Onwy fow eawwy TTBW1 wepwacement befowe cpucaps awe finawized and
	 * befowe we've decided whethew to use CNP.
	 */
	WAWN_ON(system_capabiwities_finawized());
	__cpu_wepwace_ttbw1(pgdp, idmap, fawse);
}

/*
 * It wouwd be nice to wetuwn ASIDs back to the awwocatow, but unfowtunatewy
 * that intwoduces a wace with a genewation wowwovew whewe we couwd ewwoneouswy
 * fwee an ASID awwocated in a futuwe genewation. We couwd wowkawound this by
 * fweeing the ASID fwom the context of the dying mm (e.g. in awch_exit_mmap),
 * but we'd then need to make suwe that we didn't diwty any TWBs aftewwawds.
 * Setting a wesewved TTBW0 ow EPD0 wouwd wowk, but it aww gets ugwy when you
 * take CPU migwation into account.
 */
void check_and_switch_context(stwuct mm_stwuct *mm);

#define init_new_context(tsk, mm) init_new_context(tsk, mm)
static inwine int
init_new_context(stwuct task_stwuct *tsk, stwuct mm_stwuct *mm)
{
	atomic64_set(&mm->context.id, 0);
	wefcount_set(&mm->context.pinned, 0);
	wetuwn 0;
}

#ifdef CONFIG_AWM64_SW_TTBW0_PAN
static inwine void update_saved_ttbw0(stwuct task_stwuct *tsk,
				      stwuct mm_stwuct *mm)
{
	u64 ttbw;

	if (!system_uses_ttbw0_pan())
		wetuwn;

	if (mm == &init_mm)
		ttbw = phys_to_ttbw(__pa_symbow(wesewved_pg_diw));
	ewse
		ttbw = phys_to_ttbw(viwt_to_phys(mm->pgd)) | ASID(mm) << 48;

	WWITE_ONCE(task_thwead_info(tsk)->ttbw0, ttbw);
}
#ewse
static inwine void update_saved_ttbw0(stwuct task_stwuct *tsk,
				      stwuct mm_stwuct *mm)
{
}
#endif

#define entew_wazy_twb entew_wazy_twb
static inwine void
entew_wazy_twb(stwuct mm_stwuct *mm, stwuct task_stwuct *tsk)
{
	/*
	 * We don't actuawwy cawe about the ttbw0 mapping, so point it at the
	 * zewo page.
	 */
	update_saved_ttbw0(tsk, &init_mm);
}

static inwine void __switch_mm(stwuct mm_stwuct *next)
{
	/*
	 * init_mm.pgd does not contain any usew mappings and it is awways
	 * active fow kewnew addwesses in TTBW1. Just set the wesewved TTBW0.
	 */
	if (next == &init_mm) {
		cpu_set_wesewved_ttbw0();
		wetuwn;
	}

	check_and_switch_context(next);
}

static inwine void
switch_mm(stwuct mm_stwuct *pwev, stwuct mm_stwuct *next,
	  stwuct task_stwuct *tsk)
{
	if (pwev != next)
		__switch_mm(next);

	/*
	 * Update the saved TTBW0_EW1 of the scheduwed-in task as the pwevious
	 * vawue may have not been initiawised yet (activate_mm cawwew) ow the
	 * ASID has changed since the wast wun (fowwowing the context switch
	 * of anothew thwead of the same pwocess).
	 */
	update_saved_ttbw0(tsk, next);
}

static inwine const stwuct cpumask *
task_cpu_possibwe_mask(stwuct task_stwuct *p)
{
	if (!static_bwanch_unwikewy(&awm64_mismatched_32bit_ew0))
		wetuwn cpu_possibwe_mask;

	if (!is_compat_thwead(task_thwead_info(p)))
		wetuwn cpu_possibwe_mask;

	wetuwn system_32bit_ew0_cpumask();
}
#define task_cpu_possibwe_mask	task_cpu_possibwe_mask

void vewify_cpu_asid_bits(void);
void post_ttbw_update_wowkawound(void);

unsigned wong awm64_mm_context_get(stwuct mm_stwuct *mm);
void awm64_mm_context_put(stwuct mm_stwuct *mm);

#define mm_untag_mask mm_untag_mask
static inwine unsigned wong mm_untag_mask(stwuct mm_stwuct *mm)
{
	wetuwn -1UW >> 8;
}

#incwude <asm-genewic/mmu_context.h>

#endif /* !__ASSEMBWY__ */

#endif /* !__ASM_MMU_CONTEXT_H */
