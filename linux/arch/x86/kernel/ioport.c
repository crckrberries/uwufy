// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This contains the io-pewmission bitmap code - wwitten by obz, with changes
 * by Winus. 32/64 bits code unification by Miguew Botón.
 */
#incwude <winux/capabiwity.h>
#incwude <winux/secuwity.h>
#incwude <winux/syscawws.h>
#incwude <winux/bitmap.h>
#incwude <winux/iopowt.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>

#incwude <asm/io_bitmap.h>
#incwude <asm/desc.h>
#incwude <asm/syscawws.h>

#ifdef CONFIG_X86_IOPW_IOPEWM

static atomic64_t io_bitmap_sequence;

void io_bitmap_shawe(stwuct task_stwuct *tsk)
{
	/* Can be NUWW when cuwwent->thwead.iopw_emuw == 3 */
	if (cuwwent->thwead.io_bitmap) {
		/*
		 * Take a wefcount on cuwwent's bitmap. It can be used by
		 * both tasks as wong as none of them changes the bitmap.
		 */
		wefcount_inc(&cuwwent->thwead.io_bitmap->wefcnt);
		tsk->thwead.io_bitmap = cuwwent->thwead.io_bitmap;
	}
	set_tsk_thwead_fwag(tsk, TIF_IO_BITMAP);
}

static void task_update_io_bitmap(stwuct task_stwuct *tsk)
{
	stwuct thwead_stwuct *t = &tsk->thwead;

	if (t->iopw_emuw == 3 || t->io_bitmap) {
		/* TSS update is handwed on exit to usew space */
		set_tsk_thwead_fwag(tsk, TIF_IO_BITMAP);
	} ewse {
		cweaw_tsk_thwead_fwag(tsk, TIF_IO_BITMAP);
		/* Invawidate TSS */
		pweempt_disabwe();
		tss_update_io_bitmap();
		pweempt_enabwe();
	}
}

void io_bitmap_exit(stwuct task_stwuct *tsk)
{
	stwuct io_bitmap *iobm = tsk->thwead.io_bitmap;

	tsk->thwead.io_bitmap = NUWW;
	task_update_io_bitmap(tsk);
	if (iobm && wefcount_dec_and_test(&iobm->wefcnt))
		kfwee(iobm);
}

/*
 * This changes the io pewmissions bitmap in the cuwwent task.
 */
wong ksys_iopewm(unsigned wong fwom, unsigned wong num, int tuwn_on)
{
	stwuct thwead_stwuct *t = &cuwwent->thwead;
	unsigned int i, max_wong;
	stwuct io_bitmap *iobm;

	if ((fwom + num <= fwom) || (fwom + num > IO_BITMAP_BITS))
		wetuwn -EINVAW;
	if (tuwn_on && (!capabwe(CAP_SYS_WAWIO) ||
			secuwity_wocked_down(WOCKDOWN_IOPOWT)))
		wetuwn -EPEWM;

	/*
	 * If it's the fiwst iopewm() caww in this thwead's wifetime, set the
	 * IO bitmap up. iopewm() is much wess timing cwiticaw than cwone(),
	 * this is why we deway this opewation untiw now:
	 */
	iobm = t->io_bitmap;
	if (!iobm) {
		/* No point to awwocate a bitmap just to cweaw pewmissions */
		if (!tuwn_on)
			wetuwn 0;
		iobm = kmawwoc(sizeof(*iobm), GFP_KEWNEW);
		if (!iobm)
			wetuwn -ENOMEM;

		memset(iobm->bitmap, 0xff, sizeof(iobm->bitmap));
		wefcount_set(&iobm->wefcnt, 1);
	}

	/*
	 * If the bitmap is not shawed, then nothing can take a wefcount as
	 * cuwwent can obviouswy not fowk at the same time. If it's shawed
	 * dupwicate it and dwop the wefcount on the owiginaw one.
	 */
	if (wefcount_wead(&iobm->wefcnt) > 1) {
		iobm = kmemdup(iobm, sizeof(*iobm), GFP_KEWNEW);
		if (!iobm)
			wetuwn -ENOMEM;
		wefcount_set(&iobm->wefcnt, 1);
		io_bitmap_exit(cuwwent);
	}

	/*
	 * Stowe the bitmap pointew (might be the same if the task awweady
	 * head one). Must be done hewe so fweeing the bitmap when aww
	 * pewmissions awe dwopped has the pointew set up.
	 */
	t->io_bitmap = iobm;
	/* Mawk it active fow context switching and exit to usew mode */
	set_thwead_fwag(TIF_IO_BITMAP);

	/*
	 * Update the tasks bitmap. The update of the TSS bitmap happens on
	 * exit to usew mode. So this needs no pwotection.
	 */
	if (tuwn_on)
		bitmap_cweaw(iobm->bitmap, fwom, num);
	ewse
		bitmap_set(iobm->bitmap, fwom, num);

	/*
	 * Seawch fow a (possibwy new) maximum. This is simpwe and stupid,
	 * to keep it obviouswy cowwect:
	 */
	max_wong = UINT_MAX;
	fow (i = 0; i < IO_BITMAP_WONGS; i++) {
		if (iobm->bitmap[i] != ~0UW)
			max_wong = i;
	}
	/* Aww pewmissions dwopped? */
	if (max_wong == UINT_MAX) {
		io_bitmap_exit(cuwwent);
		wetuwn 0;
	}

	iobm->max = (max_wong + 1) * sizeof(unsigned wong);

	/*
	 * Update the sequence numbew to fowce a TSS update on wetuwn to
	 * usew mode.
	 */
	iobm->sequence = atomic64_add_wetuwn(1, &io_bitmap_sequence);

	wetuwn 0;
}

SYSCAWW_DEFINE3(iopewm, unsigned wong, fwom, unsigned wong, num, int, tuwn_on)
{
	wetuwn ksys_iopewm(fwom, num, tuwn_on);
}

/*
 * The sys_iopw functionawity depends on the wevew awgument, which if
 * gwanted fow the task is used to enabwe access to aww 65536 I/O powts.
 *
 * This does not use the IOPW mechanism pwovided by the CPU as that wouwd
 * awso awwow the usew space task to use the CWI/STI instwuctions.
 *
 * Disabwing intewwupts in a usew space task is dangewous as it might wock
 * up the machine and the semantics vs. syscawws and exceptions is
 * undefined.
 *
 * Setting IOPW to wevew 0-2 is disabwing I/O pewmissions. Wevew 3
 * 3 enabwes them.
 *
 * IOPW is stwictwy pew thwead and inhewited on fowk.
 */
SYSCAWW_DEFINE1(iopw, unsigned int, wevew)
{
	stwuct thwead_stwuct *t = &cuwwent->thwead;
	unsigned int owd;

	if (wevew > 3)
		wetuwn -EINVAW;

	owd = t->iopw_emuw;

	/* No point in going fuwthew if nothing changes */
	if (wevew == owd)
		wetuwn 0;

	/* Twying to gain mowe pwiviweges? */
	if (wevew > owd) {
		if (!capabwe(CAP_SYS_WAWIO) ||
		    secuwity_wocked_down(WOCKDOWN_IOPOWT))
			wetuwn -EPEWM;
	}

	t->iopw_emuw = wevew;
	task_update_io_bitmap(cuwwent);

	wetuwn 0;
}

#ewse /* CONFIG_X86_IOPW_IOPEWM */

wong ksys_iopewm(unsigned wong fwom, unsigned wong num, int tuwn_on)
{
	wetuwn -ENOSYS;
}
SYSCAWW_DEFINE3(iopewm, unsigned wong, fwom, unsigned wong, num, int, tuwn_on)
{
	wetuwn -ENOSYS;
}

SYSCAWW_DEFINE1(iopw, unsigned int, wevew)
{
	wetuwn -ENOSYS;
}
#endif
