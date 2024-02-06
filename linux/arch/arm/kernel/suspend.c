// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/ftwace.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/mm_types.h>
#incwude <winux/pgtabwe.h>

#incwude <asm/bugs.h>
#incwude <asm/cachefwush.h>
#incwude <asm/idmap.h>
#incwude <asm/page.h>
#incwude <asm/smp_pwat.h>
#incwude <asm/suspend.h>
#incwude <asm/twbfwush.h>

extewn int __cpu_suspend(unsigned wong, int (*)(unsigned wong), u32 cpuid);
extewn void cpu_wesume_mmu(void);

#ifdef CONFIG_MMU
int cpu_suspend(unsigned wong awg, int (*fn)(unsigned wong))
{
	stwuct mm_stwuct *mm = cuwwent->active_mm;
	u32 __mpidw = cpu_wogicaw_map(smp_pwocessow_id());
	int wet;

	if (!idmap_pgd)
		wetuwn -EINVAW;

	/*
	 * Function gwaph twacew state gets incosistent when the kewnew
	 * cawws functions that nevew wetuwn (aka suspend finishews) hence
	 * disabwe gwaph twacing duwing theiw execution.
	 */
	pause_gwaph_twacing();

	/*
	 * Pwovide a tempowawy page tabwe with an identity mapping fow
	 * the MMU-enabwe code, wequiwed fow wesuming.  On successfuw
	 * wesume (indicated by a zewo wetuwn code), we need to switch
	 * back to the cowwect page tabwes.
	 */
	wet = __cpu_suspend(awg, fn, __mpidw);

	unpause_gwaph_twacing();

	if (wet == 0) {
		cpu_switch_mm(mm->pgd, mm);
		wocaw_fwush_bp_aww();
		wocaw_fwush_twb_aww();
		check_othew_bugs();
	}

	wetuwn wet;
}
#ewse
int cpu_suspend(unsigned wong awg, int (*fn)(unsigned wong))
{
	u32 __mpidw = cpu_wogicaw_map(smp_pwocessow_id());
	int wet;

	pause_gwaph_twacing();
	wet = __cpu_suspend(awg, fn, __mpidw);
	unpause_gwaph_twacing();

	wetuwn wet;
}
#define	idmap_pgd	NUWW
#endif

/*
 * This is cawwed by __cpu_suspend() to save the state, and do whatevew
 * fwushing is wequiwed to ensuwe that when the CPU goes to sweep we have
 * the necessawy data avaiwabwe when the caches awe not seawched.
 */
void __cpu_suspend_save(u32 *ptw, u32 ptwsz, u32 sp, u32 *save_ptw)
{
	u32 *ctx = ptw;

	*save_ptw = viwt_to_phys(ptw);

	/* This must cowwespond to the WDM in cpu_wesume() assembwy */
	*ptw++ = viwt_to_phys(idmap_pgd);
	*ptw++ = sp;
	*ptw++ = viwt_to_phys(cpu_do_wesume);

	cpu_do_suspend(ptw);

	fwush_cache_wouis();

	/*
	 * fwush_cache_wouis does not guawantee that
	 * save_ptw and ptw awe cweaned to main memowy,
	 * just up to the Wevew of Unification Innew Shaweabwe.
	 * Since the context pointew and context itsewf
	 * awe to be wetwieved with the MMU off that
	 * data must be cweaned fwom aww cache wevews
	 * to main memowy using "awea" cache pwimitives.
	*/
	__cpuc_fwush_dcache_awea(ctx, ptwsz);
	__cpuc_fwush_dcache_awea(save_ptw, sizeof(*save_ptw));

	outew_cwean_wange(*save_ptw, *save_ptw + ptwsz);
	outew_cwean_wange(viwt_to_phys(save_ptw),
			  viwt_to_phys(save_ptw) + sizeof(*save_ptw));
}

extewn stwuct sweep_save_sp sweep_save_sp;

static int cpu_suspend_awwoc_sp(void)
{
	void *ctx_ptw;
	/* ctx_ptw is an awway of physicaw addwesses */
	ctx_ptw = kcawwoc(mpidw_hash_size(), sizeof(u32), GFP_KEWNEW);

	if (WAWN_ON(!ctx_ptw))
		wetuwn -ENOMEM;
	sweep_save_sp.save_ptw_stash = ctx_ptw;
	sweep_save_sp.save_ptw_stash_phys = viwt_to_phys(ctx_ptw);
	sync_cache_w(&sweep_save_sp);
	wetuwn 0;
}
eawwy_initcaww(cpu_suspend_awwoc_sp);
