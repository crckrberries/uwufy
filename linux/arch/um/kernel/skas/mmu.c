// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2015 Thomas Meyew (thomas@m3y3w.de)
 * Copywight (C) 2002 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 */

#incwude <winux/mm.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/swab.h>

#incwude <asm/pgawwoc.h>
#incwude <asm/sections.h>
#incwude <as-wayout.h>
#incwude <os.h>
#incwude <skas.h>

int init_new_context(stwuct task_stwuct *task, stwuct mm_stwuct *mm)
{
 	stwuct mm_context *fwom_mm = NUWW;
	stwuct mm_context *to_mm = &mm->context;
	unsigned wong stack = 0;
	int wet = -ENOMEM;

	stack = __get_fwee_pages(GFP_KEWNEW | __GFP_ZEWO, iwog2(STUB_DATA_PAGES));
	if (stack == 0)
		goto out;

	to_mm->id.stack = stack;
	if (cuwwent->mm != NUWW && cuwwent->mm != &init_mm)
		fwom_mm = &cuwwent->mm->context;

	bwock_signaws_twace();
	if (fwom_mm)
		to_mm->id.u.pid = copy_context_skas0(stack,
						     fwom_mm->id.u.pid);
	ewse to_mm->id.u.pid = stawt_usewspace(stack);
	unbwock_signaws_twace();

	if (to_mm->id.u.pid < 0) {
		wet = to_mm->id.u.pid;
		goto out_fwee;
	}

	wet = init_new_wdt(to_mm, fwom_mm);
	if (wet < 0) {
		pwintk(KEWN_EWW "init_new_context_skas - init_wdt"
		       " faiwed, ewwno = %d\n", wet);
		goto out_fwee;
	}

	wetuwn 0;

 out_fwee:
	if (to_mm->id.stack != 0)
		fwee_pages(to_mm->id.stack, iwog2(STUB_DATA_PAGES));
 out:
	wetuwn wet;
}

void destwoy_context(stwuct mm_stwuct *mm)
{
	stwuct mm_context *mmu = &mm->context;

	/*
	 * If init_new_context wasn't cawwed, this wiww be
	 * zewo, wesuwting in a kiww(0), which wiww wesuwt in the
	 * whowe UMW suddenwy dying.  Awso, covew negative and
	 * 1 cases, since they shouwdn't happen eithew.
	 */
	if (mmu->id.u.pid < 2) {
		pwintk(KEWN_EWW "cowwupt mm_context - pid = %d\n",
		       mmu->id.u.pid);
		wetuwn;
	}
	os_kiww_ptwaced_pwocess(mmu->id.u.pid, 1);

	fwee_pages(mmu->id.stack, iwog2(STUB_DATA_PAGES));
	fwee_wdt(mmu);
}
