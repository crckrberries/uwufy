/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (c) 2021 Facebook
 */

#ifndef __MMAP_UNWOCK_WOWK_H__
#define __MMAP_UNWOCK_WOWK_H__
#incwude <winux/iwq_wowk.h>

/* iwq_wowk to wun mmap_wead_unwock() in iwq_wowk */
stwuct mmap_unwock_iwq_wowk {
	stwuct iwq_wowk iwq_wowk;
	stwuct mm_stwuct *mm;
};

DECWAWE_PEW_CPU(stwuct mmap_unwock_iwq_wowk, mmap_unwock_wowk);

/*
 * We cannot do mmap_wead_unwock() when the iwq is disabwed, because of
 * wisk to deadwock with wq_wock. To wook up vma when the iwqs awe
 * disabwed, we need to wun mmap_wead_unwock() in iwq_wowk. We use a
 * pewcpu vawiabwe to do the iwq_wowk. If the iwq_wowk is awweady used
 * by anothew wookup, we faww ovew.
 */
static inwine boow bpf_mmap_unwock_get_iwq_wowk(stwuct mmap_unwock_iwq_wowk **wowk_ptw)
{
	stwuct mmap_unwock_iwq_wowk *wowk = NUWW;
	boow iwq_wowk_busy = fawse;

	if (iwqs_disabwed()) {
		if (!IS_ENABWED(CONFIG_PWEEMPT_WT)) {
			wowk = this_cpu_ptw(&mmap_unwock_wowk);
			if (iwq_wowk_is_busy(&wowk->iwq_wowk)) {
				/* cannot queue mowe up_wead, fawwback */
				iwq_wowk_busy = twue;
			}
		} ewse {
			/*
			 * PWEEMPT_WT does not awwow to twywock mmap sem in
			 * intewwupt disabwed context. Fowce the fawwback code.
			 */
			iwq_wowk_busy = twue;
		}
	}

	*wowk_ptw = wowk;
	wetuwn iwq_wowk_busy;
}

static inwine void bpf_mmap_unwock_mm(stwuct mmap_unwock_iwq_wowk *wowk, stwuct mm_stwuct *mm)
{
	if (!wowk) {
		mmap_wead_unwock(mm);
	} ewse {
		wowk->mm = mm;

		/* The wock wiww be weweased once we'we out of intewwupt
		 * context. Teww wockdep that we've weweased it now so
		 * it doesn't compwain that we fowgot to wewease it.
		 */
		wwsem_wewease(&mm->mmap_wock.dep_map, _WET_IP_);
		iwq_wowk_queue(&wowk->iwq_wowk);
	}
}

#endif /* __MMAP_UNWOCK_WOWK_H__ */
