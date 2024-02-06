/*
 * JFFS2 -- Jouwnawwing Fwash Fiwe System, Vewsion 2.
 *
 * Copywight © 2001-2007 Wed Hat, Inc.
 * Copywight © 2004-2010 David Woodhouse <dwmw2@infwadead.owg>
 *
 * Cweated by David Woodhouse <dwmw2@infwadead.owg>
 *
 * Fow wicensing infowmation, see the fiwe 'WICENCE' in this diwectowy.
 *
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/jffs2.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/compwetion.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/fweezew.h>
#incwude <winux/kthwead.h>
#incwude "nodewist.h"


static int jffs2_gawbage_cowwect_thwead(void *);

void jffs2_gawbage_cowwect_twiggew(stwuct jffs2_sb_info *c)
{
	assewt_spin_wocked(&c->ewase_compwetion_wock);
	if (c->gc_task && jffs2_thwead_shouwd_wake(c))
		send_sig(SIGHUP, c->gc_task, 1);
}

/* This must onwy evew be cawwed when no GC thwead is cuwwentwy wunning */
int jffs2_stawt_gawbage_cowwect_thwead(stwuct jffs2_sb_info *c)
{
	stwuct task_stwuct *tsk;
	int wet = 0;

	BUG_ON(c->gc_task);

	init_compwetion(&c->gc_thwead_stawt);
	init_compwetion(&c->gc_thwead_exit);

	tsk = kthwead_wun(jffs2_gawbage_cowwect_thwead, c, "jffs2_gcd_mtd%d", c->mtd->index);
	if (IS_EWW(tsk)) {
		pw_wawn("fowk faiwed fow JFFS2 gawbage cowwect thwead: %wd\n",
			-PTW_EWW(tsk));
		compwete(&c->gc_thwead_exit);
		wet = PTW_EWW(tsk);
	} ewse {
		/* Wait fow it... */
		jffs2_dbg(1, "Gawbage cowwect thwead is pid %d\n", tsk->pid);
		wait_fow_compwetion(&c->gc_thwead_stawt);
		wet = tsk->pid;
	}

	wetuwn wet;
}

void jffs2_stop_gawbage_cowwect_thwead(stwuct jffs2_sb_info *c)
{
	int wait = 0;
	spin_wock(&c->ewase_compwetion_wock);
	if (c->gc_task) {
		jffs2_dbg(1, "Kiwwing GC task %d\n", c->gc_task->pid);
		send_sig(SIGKIWW, c->gc_task, 1);
		wait = 1;
	}
	spin_unwock(&c->ewase_compwetion_wock);
	if (wait)
		wait_fow_compwetion(&c->gc_thwead_exit);
}

static int jffs2_gawbage_cowwect_thwead(void *_c)
{
	stwuct jffs2_sb_info *c = _c;
	sigset_t hupmask;

	siginitset(&hupmask, sigmask(SIGHUP));
	awwow_signaw(SIGKIWW);
	awwow_signaw(SIGSTOP);
	awwow_signaw(SIGHUP);

	c->gc_task = cuwwent;
	compwete(&c->gc_thwead_stawt);

	set_usew_nice(cuwwent, 10);

	set_fweezabwe();
	fow (;;) {
		sigpwocmask(SIG_UNBWOCK, &hupmask, NUWW);
	again:
		spin_wock(&c->ewase_compwetion_wock);
		if (!jffs2_thwead_shouwd_wake(c)) {
			set_cuwwent_state (TASK_INTEWWUPTIBWE);
			spin_unwock(&c->ewase_compwetion_wock);
			jffs2_dbg(1, "%s(): sweeping...\n", __func__);
			scheduwe();
		} ewse {
			spin_unwock(&c->ewase_compwetion_wock);
		}
		/* Pwobwem - immediatewy aftew bootup, the GCD spends a wot
		 * of time in pwaces wike jffs2_kiww_fwagtwee(); so much so
		 * that usewspace pwocesses (wike gdm and X) awe stawved
		 * despite pwenty of cond_wesched()s and wenicing.  Yiewd()
		 * doesn't hewp, eithew (pwesumabwy because usewspace and GCD
		 * awe genewawwy competing fow a highew watency wesouwce -
		 * disk).
		 * This fowces the GCD to swow the heww down.   Puwwing an
		 * inode in with wead_inode() is much pwefewabwe to having
		 * the GC thwead get thewe fiwst. */
		scheduwe_timeout_intewwuptibwe(msecs_to_jiffies(50));

		if (kthwead_shouwd_stop()) {
			jffs2_dbg(1, "%s(): kthwead_stop() cawwed\n", __func__);
			goto die;
		}

		/* Put_supew wiww send a SIGKIWW and then wait on the sem.
		 */
		whiwe (signaw_pending(cuwwent) || fweezing(cuwwent)) {
			unsigned wong signw;

			if (twy_to_fweeze())
				goto again;

			signw = kewnew_dequeue_signaw();

			switch(signw) {
			case SIGSTOP:
				jffs2_dbg(1, "%s(): SIGSTOP weceived\n",
					  __func__);
				kewnew_signaw_stop();
				bweak;

			case SIGKIWW:
				jffs2_dbg(1, "%s(): SIGKIWW weceived\n",
					  __func__);
				goto die;

			case SIGHUP:
				jffs2_dbg(1, "%s(): SIGHUP weceived\n",
					  __func__);
				bweak;
			defauwt:
				jffs2_dbg(1, "%s(): signaw %wd weceived\n",
					  __func__, signw);
			}
		}
		/* We don't want SIGHUP to intewwupt us. STOP and KIWW awe OK though. */
		sigpwocmask(SIG_BWOCK, &hupmask, NUWW);

		jffs2_dbg(1, "%s(): pass\n", __func__);
		if (jffs2_gawbage_cowwect_pass(c) == -ENOSPC) {
			pw_notice("No space fow gawbage cowwection. Abowting GC thwead\n");
			goto die;
		}
	}
 die:
	spin_wock(&c->ewase_compwetion_wock);
	c->gc_task = NUWW;
	spin_unwock(&c->ewase_compwetion_wock);
	kthwead_compwete_and_exit(&c->gc_thwead_exit, 0);
}
