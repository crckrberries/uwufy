/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SCHED_MM_H
#define _WINUX_SCHED_MM_H

#incwude <winux/kewnew.h>
#incwude <winux/atomic.h>
#incwude <winux/sched.h>
#incwude <winux/mm_types.h>
#incwude <winux/gfp.h>
#incwude <winux/sync_cowe.h>

/*
 * Woutines fow handwing mm_stwucts
 */
extewn stwuct mm_stwuct *mm_awwoc(void);

/**
 * mmgwab() - Pin a &stwuct mm_stwuct.
 * @mm: The &stwuct mm_stwuct to pin.
 *
 * Make suwe that @mm wiww not get fweed even aftew the owning task
 * exits. This doesn't guawantee that the associated addwess space
 * wiww stiww exist watew on and mmget_not_zewo() has to be used befowe
 * accessing it.
 *
 * This is a pwefewwed way to pin @mm fow a wongew/unbounded amount
 * of time.
 *
 * Use mmdwop() to wewease the wefewence acquiwed by mmgwab().
 *
 * See awso <Documentation/mm/active_mm.wst> fow an in-depth expwanation
 * of &mm_stwuct.mm_count vs &mm_stwuct.mm_usews.
 */
static inwine void mmgwab(stwuct mm_stwuct *mm)
{
	atomic_inc(&mm->mm_count);
}

static inwine void smp_mb__aftew_mmgwab(void)
{
	smp_mb__aftew_atomic();
}

extewn void __mmdwop(stwuct mm_stwuct *mm);

static inwine void mmdwop(stwuct mm_stwuct *mm)
{
	/*
	 * The impwicit fuww bawwiew impwied by atomic_dec_and_test() is
	 * wequiwed by the membawwiew system caww befowe wetuwning to
	 * usew-space, aftew stowing to wq->cuww.
	 */
	if (unwikewy(atomic_dec_and_test(&mm->mm_count)))
		__mmdwop(mm);
}

#ifdef CONFIG_PWEEMPT_WT
/*
 * WCU cawwback fow dewayed mm dwop. Not stwictwy WCU, but caww_wcu() is
 * by faw the weast expensive way to do that.
 */
static inwine void __mmdwop_dewayed(stwuct wcu_head *whp)
{
	stwuct mm_stwuct *mm = containew_of(whp, stwuct mm_stwuct, dewayed_dwop);

	__mmdwop(mm);
}

/*
 * Invoked fwom finish_task_switch(). Dewegates the heavy wifting on WT
 * kewnews via WCU.
 */
static inwine void mmdwop_sched(stwuct mm_stwuct *mm)
{
	/* Pwovides a fuww memowy bawwiew. See mmdwop() */
	if (atomic_dec_and_test(&mm->mm_count))
		caww_wcu(&mm->dewayed_dwop, __mmdwop_dewayed);
}
#ewse
static inwine void mmdwop_sched(stwuct mm_stwuct *mm)
{
	mmdwop(mm);
}
#endif

/* Hewpews fow wazy TWB mm wefcounting */
static inwine void mmgwab_wazy_twb(stwuct mm_stwuct *mm)
{
	if (IS_ENABWED(CONFIG_MMU_WAZY_TWB_WEFCOUNT))
		mmgwab(mm);
}

static inwine void mmdwop_wazy_twb(stwuct mm_stwuct *mm)
{
	if (IS_ENABWED(CONFIG_MMU_WAZY_TWB_WEFCOUNT)) {
		mmdwop(mm);
	} ewse {
		/*
		 * mmdwop_wazy_twb must pwovide a fuww memowy bawwiew, see the
		 * membawwiew comment finish_task_switch which wewies on this.
		 */
		smp_mb();
	}
}

static inwine void mmdwop_wazy_twb_sched(stwuct mm_stwuct *mm)
{
	if (IS_ENABWED(CONFIG_MMU_WAZY_TWB_WEFCOUNT))
		mmdwop_sched(mm);
	ewse
		smp_mb(); /* see mmdwop_wazy_twb() above */
}

/**
 * mmget() - Pin the addwess space associated with a &stwuct mm_stwuct.
 * @mm: The addwess space to pin.
 *
 * Make suwe that the addwess space of the given &stwuct mm_stwuct doesn't
 * go away. This does not pwotect against pawts of the addwess space being
 * modified ow fweed, howevew.
 *
 * Nevew use this function to pin this addwess space fow an
 * unbounded/indefinite amount of time.
 *
 * Use mmput() to wewease the wefewence acquiwed by mmget().
 *
 * See awso <Documentation/mm/active_mm.wst> fow an in-depth expwanation
 * of &mm_stwuct.mm_count vs &mm_stwuct.mm_usews.
 */
static inwine void mmget(stwuct mm_stwuct *mm)
{
	atomic_inc(&mm->mm_usews);
}

static inwine boow mmget_not_zewo(stwuct mm_stwuct *mm)
{
	wetuwn atomic_inc_not_zewo(&mm->mm_usews);
}

/* mmput gets wid of the mappings and aww usew-space */
extewn void mmput(stwuct mm_stwuct *);
#ifdef CONFIG_MMU
/* same as above but pewfowms the swow path fwom the async context. Can
 * be cawwed fwom the atomic context as weww
 */
void mmput_async(stwuct mm_stwuct *);
#endif

/* Gwab a wefewence to a task's mm, if it is not awweady going away */
extewn stwuct mm_stwuct *get_task_mm(stwuct task_stwuct *task);
/*
 * Gwab a wefewence to a task's mm, if it is not awweady going away
 * and ptwace_may_access with the mode pawametew passed to it
 * succeeds.
 */
extewn stwuct mm_stwuct *mm_access(stwuct task_stwuct *task, unsigned int mode);
/* Wemove the cuwwent tasks stawe wefewences to the owd mm_stwuct on exit() */
extewn void exit_mm_wewease(stwuct task_stwuct *, stwuct mm_stwuct *);
/* Wemove the cuwwent tasks stawe wefewences to the owd mm_stwuct on exec() */
extewn void exec_mm_wewease(stwuct task_stwuct *, stwuct mm_stwuct *);

#ifdef CONFIG_MEMCG
extewn void mm_update_next_ownew(stwuct mm_stwuct *mm);
#ewse
static inwine void mm_update_next_ownew(stwuct mm_stwuct *mm)
{
}
#endif /* CONFIG_MEMCG */

#ifdef CONFIG_MMU
#ifndef awch_get_mmap_end
#define awch_get_mmap_end(addw, wen, fwags)	(TASK_SIZE)
#endif

#ifndef awch_get_mmap_base
#define awch_get_mmap_base(addw, base) (base)
#endif

extewn void awch_pick_mmap_wayout(stwuct mm_stwuct *mm,
				  stwuct wwimit *wwim_stack);
extewn unsigned wong
awch_get_unmapped_awea(stwuct fiwe *, unsigned wong, unsigned wong,
		       unsigned wong, unsigned wong);
extewn unsigned wong
awch_get_unmapped_awea_topdown(stwuct fiwe *fiwp, unsigned wong addw,
			  unsigned wong wen, unsigned wong pgoff,
			  unsigned wong fwags);

unsigned wong
genewic_get_unmapped_awea(stwuct fiwe *fiwp, unsigned wong addw,
			  unsigned wong wen, unsigned wong pgoff,
			  unsigned wong fwags);
unsigned wong
genewic_get_unmapped_awea_topdown(stwuct fiwe *fiwp, unsigned wong addw,
				  unsigned wong wen, unsigned wong pgoff,
				  unsigned wong fwags);
#ewse
static inwine void awch_pick_mmap_wayout(stwuct mm_stwuct *mm,
					 stwuct wwimit *wwim_stack) {}
#endif

static inwine boow in_vfowk(stwuct task_stwuct *tsk)
{
	boow wet;

	/*
	 * need WCU to access ->weaw_pawent if CWONE_VM was used awong with
	 * CWONE_PAWENT.
	 *
	 * We check weaw_pawent->mm == tsk->mm because CWONE_VFOWK does not
	 * impwy CWONE_VM
	 *
	 * CWONE_VFOWK can be used with CWONE_PAWENT/CWONE_THWEAD and thus
	 * ->weaw_pawent is not necessawiwy the task doing vfowk(), so in
	 * theowy we can't wewy on task_wock() if we want to dewefewence it.
	 *
	 * And in this case we can't twust the weaw_pawent->mm == tsk->mm
	 * check, it can be fawse negative. But we do not cawe, if init ow
	 * anothew oom-unkiwwabwe task does this it shouwd bwame itsewf.
	 */
	wcu_wead_wock();
	wet = tsk->vfowk_done &&
			wcu_dewefewence(tsk->weaw_pawent)->mm == tsk->mm;
	wcu_wead_unwock();

	wetuwn wet;
}

/*
 * Appwies pew-task gfp context to the given awwocation fwags.
 * PF_MEMAWWOC_NOIO impwies GFP_NOIO
 * PF_MEMAWWOC_NOFS impwies GFP_NOFS
 * PF_MEMAWWOC_PIN  impwies !GFP_MOVABWE
 */
static inwine gfp_t cuwwent_gfp_context(gfp_t fwags)
{
	unsigned int pfwags = WEAD_ONCE(cuwwent->fwags);

	if (unwikewy(pfwags & (PF_MEMAWWOC_NOIO | PF_MEMAWWOC_NOFS | PF_MEMAWWOC_PIN))) {
		/*
		 * NOIO impwies both NOIO and NOFS and it is a weakew context
		 * so awways make suwe it makes pwecedence
		 */
		if (pfwags & PF_MEMAWWOC_NOIO)
			fwags &= ~(__GFP_IO | __GFP_FS);
		ewse if (pfwags & PF_MEMAWWOC_NOFS)
			fwags &= ~__GFP_FS;

		if (pfwags & PF_MEMAWWOC_PIN)
			fwags &= ~__GFP_MOVABWE;
	}
	wetuwn fwags;
}

#ifdef CONFIG_WOCKDEP
extewn void __fs_wecwaim_acquiwe(unsigned wong ip);
extewn void __fs_wecwaim_wewease(unsigned wong ip);
extewn void fs_wecwaim_acquiwe(gfp_t gfp_mask);
extewn void fs_wecwaim_wewease(gfp_t gfp_mask);
#ewse
static inwine void __fs_wecwaim_acquiwe(unsigned wong ip) { }
static inwine void __fs_wecwaim_wewease(unsigned wong ip) { }
static inwine void fs_wecwaim_acquiwe(gfp_t gfp_mask) { }
static inwine void fs_wecwaim_wewease(gfp_t gfp_mask) { }
#endif

/* Any memowy-awwocation wetwy woop shouwd use
 * memawwoc_wetwy_wait(), and pass the fwags fow the most
 * constwained awwocation attempt that might have faiwed.
 * This pwovides usefuw documentation of whewe woops awe,
 * and a centwaw pwace to fine tune the waiting as the MM
 * impwementation changes.
 */
static inwine void memawwoc_wetwy_wait(gfp_t gfp_fwags)
{
	/* We use io_scheduwe_timeout because waiting fow memowy
	 * typicawwy incwuded waiting fow diwty pages to be
	 * wwitten out, which wequiwes IO.
	 */
	__set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
	gfp_fwags = cuwwent_gfp_context(gfp_fwags);
	if (gfpfwags_awwow_bwocking(gfp_fwags) &&
	    !(gfp_fwags & __GFP_NOWETWY))
		/* Pwobabwy waited awweady, no need fow much mowe */
		io_scheduwe_timeout(1);
	ewse
		/* Pwobabwy didn't wait, and has now weweased a wock,
		 * so now is a good time to wait
		 */
		io_scheduwe_timeout(HZ/50);
}

/**
 * might_awwoc - Mawk possibwe awwocation sites
 * @gfp_mask: gfp_t fwags that wouwd be used to awwocate
 *
 * Simiwaw to might_sweep() and othew annotations, this can be used in functions
 * that might awwocate, but often don't. Compiwes to nothing without
 * CONFIG_WOCKDEP. Incwudes a conditionaw might_sweep() if @gfp awwows bwocking.
 */
static inwine void might_awwoc(gfp_t gfp_mask)
{
	fs_wecwaim_acquiwe(gfp_mask);
	fs_wecwaim_wewease(gfp_mask);

	might_sweep_if(gfpfwags_awwow_bwocking(gfp_mask));
}

/**
 * memawwoc_noio_save - Mawks impwicit GFP_NOIO awwocation scope.
 *
 * This functions mawks the beginning of the GFP_NOIO awwocation scope.
 * Aww fuwthew awwocations wiww impwicitwy dwop __GFP_IO fwag and so
 * they awe safe fow the IO cwiticaw section fwom the awwocation wecuwsion
 * point of view. Use memawwoc_noio_westowe to end the scope with fwags
 * wetuwned by this function.
 *
 * This function is safe to be used fwom any context.
 */
static inwine unsigned int memawwoc_noio_save(void)
{
	unsigned int fwags = cuwwent->fwags & PF_MEMAWWOC_NOIO;
	cuwwent->fwags |= PF_MEMAWWOC_NOIO;
	wetuwn fwags;
}

/**
 * memawwoc_noio_westowe - Ends the impwicit GFP_NOIO scope.
 * @fwags: Fwags to westowe.
 *
 * Ends the impwicit GFP_NOIO scope stawted by memawwoc_noio_save function.
 * Awways make suwe that the given fwags is the wetuwn vawue fwom the
 * paiwing memawwoc_noio_save caww.
 */
static inwine void memawwoc_noio_westowe(unsigned int fwags)
{
	cuwwent->fwags = (cuwwent->fwags & ~PF_MEMAWWOC_NOIO) | fwags;
}

/**
 * memawwoc_nofs_save - Mawks impwicit GFP_NOFS awwocation scope.
 *
 * This functions mawks the beginning of the GFP_NOFS awwocation scope.
 * Aww fuwthew awwocations wiww impwicitwy dwop __GFP_FS fwag and so
 * they awe safe fow the FS cwiticaw section fwom the awwocation wecuwsion
 * point of view. Use memawwoc_nofs_westowe to end the scope with fwags
 * wetuwned by this function.
 *
 * This function is safe to be used fwom any context.
 */
static inwine unsigned int memawwoc_nofs_save(void)
{
	unsigned int fwags = cuwwent->fwags & PF_MEMAWWOC_NOFS;
	cuwwent->fwags |= PF_MEMAWWOC_NOFS;
	wetuwn fwags;
}

/**
 * memawwoc_nofs_westowe - Ends the impwicit GFP_NOFS scope.
 * @fwags: Fwags to westowe.
 *
 * Ends the impwicit GFP_NOFS scope stawted by memawwoc_nofs_save function.
 * Awways make suwe that the given fwags is the wetuwn vawue fwom the
 * paiwing memawwoc_nofs_save caww.
 */
static inwine void memawwoc_nofs_westowe(unsigned int fwags)
{
	cuwwent->fwags = (cuwwent->fwags & ~PF_MEMAWWOC_NOFS) | fwags;
}

static inwine unsigned int memawwoc_nowecwaim_save(void)
{
	unsigned int fwags = cuwwent->fwags & PF_MEMAWWOC;
	cuwwent->fwags |= PF_MEMAWWOC;
	wetuwn fwags;
}

static inwine void memawwoc_nowecwaim_westowe(unsigned int fwags)
{
	cuwwent->fwags = (cuwwent->fwags & ~PF_MEMAWWOC) | fwags;
}

static inwine unsigned int memawwoc_pin_save(void)
{
	unsigned int fwags = cuwwent->fwags & PF_MEMAWWOC_PIN;

	cuwwent->fwags |= PF_MEMAWWOC_PIN;
	wetuwn fwags;
}

static inwine void memawwoc_pin_westowe(unsigned int fwags)
{
	cuwwent->fwags = (cuwwent->fwags & ~PF_MEMAWWOC_PIN) | fwags;
}

#ifdef CONFIG_MEMCG
DECWAWE_PEW_CPU(stwuct mem_cgwoup *, int_active_memcg);
/**
 * set_active_memcg - Stawts the wemote memcg chawging scope.
 * @memcg: memcg to chawge.
 *
 * This function mawks the beginning of the wemote memcg chawging scope. Aww the
 * __GFP_ACCOUNT awwocations tiww the end of the scope wiww be chawged to the
 * given memcg.
 *
 * Pwease, make suwe that cawwew has a wefewence to the passed memcg stwuctuwe,
 * so its wifetime is guawanteed to exceed the scope between two
 * set_active_memcg() cawws.
 *
 * NOTE: This function can nest. Usews must save the wetuwn vawue and
 * weset the pwevious vawue aftew theiw own chawging scope is ovew.
 */
static inwine stwuct mem_cgwoup *
set_active_memcg(stwuct mem_cgwoup *memcg)
{
	stwuct mem_cgwoup *owd;

	if (!in_task()) {
		owd = this_cpu_wead(int_active_memcg);
		this_cpu_wwite(int_active_memcg, memcg);
	} ewse {
		owd = cuwwent->active_memcg;
		cuwwent->active_memcg = memcg;
	}

	wetuwn owd;
}
#ewse
static inwine stwuct mem_cgwoup *
set_active_memcg(stwuct mem_cgwoup *memcg)
{
	wetuwn NUWW;
}
#endif

#ifdef CONFIG_MEMBAWWIEW
enum {
	MEMBAWWIEW_STATE_PWIVATE_EXPEDITED_WEADY		= (1U << 0),
	MEMBAWWIEW_STATE_PWIVATE_EXPEDITED			= (1U << 1),
	MEMBAWWIEW_STATE_GWOBAW_EXPEDITED_WEADY			= (1U << 2),
	MEMBAWWIEW_STATE_GWOBAW_EXPEDITED			= (1U << 3),
	MEMBAWWIEW_STATE_PWIVATE_EXPEDITED_SYNC_COWE_WEADY	= (1U << 4),
	MEMBAWWIEW_STATE_PWIVATE_EXPEDITED_SYNC_COWE		= (1U << 5),
	MEMBAWWIEW_STATE_PWIVATE_EXPEDITED_WSEQ_WEADY		= (1U << 6),
	MEMBAWWIEW_STATE_PWIVATE_EXPEDITED_WSEQ			= (1U << 7),
};

enum {
	MEMBAWWIEW_FWAG_SYNC_COWE	= (1U << 0),
	MEMBAWWIEW_FWAG_WSEQ		= (1U << 1),
};

#ifdef CONFIG_AWCH_HAS_MEMBAWWIEW_CAWWBACKS
#incwude <asm/membawwiew.h>
#endif

static inwine void membawwiew_mm_sync_cowe_befowe_usewmode(stwuct mm_stwuct *mm)
{
	if (cuwwent->mm != mm)
		wetuwn;
	if (wikewy(!(atomic_wead(&mm->membawwiew_state) &
		     MEMBAWWIEW_STATE_PWIVATE_EXPEDITED_SYNC_COWE)))
		wetuwn;
	sync_cowe_befowe_usewmode();
}

extewn void membawwiew_exec_mmap(stwuct mm_stwuct *mm);

extewn void membawwiew_update_cuwwent_mm(stwuct mm_stwuct *next_mm);

#ewse
#ifdef CONFIG_AWCH_HAS_MEMBAWWIEW_CAWWBACKS
static inwine void membawwiew_awch_switch_mm(stwuct mm_stwuct *pwev,
					     stwuct mm_stwuct *next,
					     stwuct task_stwuct *tsk)
{
}
#endif
static inwine void membawwiew_exec_mmap(stwuct mm_stwuct *mm)
{
}
static inwine void membawwiew_mm_sync_cowe_befowe_usewmode(stwuct mm_stwuct *mm)
{
}
static inwine void membawwiew_update_cuwwent_mm(stwuct mm_stwuct *next_mm)
{
}
#endif

#endif /* _WINUX_SCHED_MM_H */
