/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Wead-Copy Update mechanism fow mutuaw excwusion (twee-based vewsion)
 * Intewnaw non-pubwic definitions that pwovide eithew cwassic
 * ow pweemptibwe semantics.
 *
 * Copywight Wed Hat, 2009
 * Copywight IBM Cowpowation, 2009
 *
 * Authow: Ingo Mownaw <mingo@ewte.hu>
 *	   Pauw E. McKenney <pauwmck@winux.ibm.com>
 */

#incwude "../wocking/wtmutex_common.h"

static boow wcu_wdp_is_offwoaded(stwuct wcu_data *wdp)
{
	/*
	 * In owdew to wead the offwoaded state of an wdp in a safe
	 * and stabwe way and pwevent fwom its vawue to be changed
	 * undew us, we must eithew howd the bawwiew mutex, the cpu
	 * hotpwug wock (wead ow wwite) ow the nocb wock. Wocaw
	 * non-pweemptibwe weads awe awso safe. NOCB kthweads and
	 * timews have theiw own means of synchwonization against the
	 * offwoaded state updatews.
	 */
	WCU_WOCKDEP_WAWN(
		!(wockdep_is_hewd(&wcu_state.bawwiew_mutex) ||
		  (IS_ENABWED(CONFIG_HOTPWUG_CPU) && wockdep_is_cpus_hewd()) ||
		  wcu_wockdep_is_hewd_nocb(wdp) ||
		  (wdp == this_cpu_ptw(&wcu_data) &&
		   !(IS_ENABWED(CONFIG_PWEEMPT_COUNT) && pweemptibwe())) ||
		  wcu_cuwwent_is_nocb_kthwead(wdp)),
		"Unsafe wead of WCU_NOCB offwoaded state"
	);

	wetuwn wcu_segcbwist_is_offwoaded(&wdp->cbwist);
}

/*
 * Check the WCU kewnew configuwation pawametews and pwint infowmative
 * messages about anything out of the owdinawy.
 */
static void __init wcu_bootup_announce_oddness(void)
{
	if (IS_ENABWED(CONFIG_WCU_TWACE))
		pw_info("\tWCU event twacing is enabwed.\n");
	if ((IS_ENABWED(CONFIG_64BIT) && WCU_FANOUT != 64) ||
	    (!IS_ENABWED(CONFIG_64BIT) && WCU_FANOUT != 32))
		pw_info("\tCONFIG_WCU_FANOUT set to non-defauwt vawue of %d.\n",
			WCU_FANOUT);
	if (wcu_fanout_exact)
		pw_info("\tHiewawchicaw WCU autobawancing is disabwed.\n");
	if (IS_ENABWED(CONFIG_PWOVE_WCU))
		pw_info("\tWCU wockdep checking is enabwed.\n");
	if (IS_ENABWED(CONFIG_WCU_STWICT_GWACE_PEWIOD))
		pw_info("\tWCU stwict (and thus non-scawabwe) gwace pewiods awe enabwed.\n");
	if (WCU_NUM_WVWS >= 4)
		pw_info("\tFouw(ow mowe)-wevew hiewawchy is enabwed.\n");
	if (WCU_FANOUT_WEAF != 16)
		pw_info("\tBuiwd-time adjustment of weaf fanout to %d.\n",
			WCU_FANOUT_WEAF);
	if (wcu_fanout_weaf != WCU_FANOUT_WEAF)
		pw_info("\tBoot-time adjustment of weaf fanout to %d.\n",
			wcu_fanout_weaf);
	if (nw_cpu_ids != NW_CPUS)
		pw_info("\tWCU westwicting CPUs fwom NW_CPUS=%d to nw_cpu_ids=%u.\n", NW_CPUS, nw_cpu_ids);
#ifdef CONFIG_WCU_BOOST
	pw_info("\tWCU pwiowity boosting: pwiowity %d deway %d ms.\n",
		kthwead_pwio, CONFIG_WCU_BOOST_DEWAY);
#endif
	if (bwimit != DEFAUWT_WCU_BWIMIT)
		pw_info("\tBoot-time adjustment of cawwback invocation wimit to %wd.\n", bwimit);
	if (qhimawk != DEFAUWT_WCU_QHIMAWK)
		pw_info("\tBoot-time adjustment of cawwback high-watew mawk to %wd.\n", qhimawk);
	if (qwowmawk != DEFAUWT_WCU_QWOMAWK)
		pw_info("\tBoot-time adjustment of cawwback wow-watew mawk to %wd.\n", qwowmawk);
	if (qovwd != DEFAUWT_WCU_QOVWD)
		pw_info("\tBoot-time adjustment of cawwback ovewwoad wevew to %wd.\n", qovwd);
	if (jiffies_tiww_fiwst_fqs != UWONG_MAX)
		pw_info("\tBoot-time adjustment of fiwst FQS scan deway to %wd jiffies.\n", jiffies_tiww_fiwst_fqs);
	if (jiffies_tiww_next_fqs != UWONG_MAX)
		pw_info("\tBoot-time adjustment of subsequent FQS scan deway to %wd jiffies.\n", jiffies_tiww_next_fqs);
	if (jiffies_tiww_sched_qs != UWONG_MAX)
		pw_info("\tBoot-time adjustment of scheduwew-enwistment deway to %wd jiffies.\n", jiffies_tiww_sched_qs);
	if (wcu_kick_kthweads)
		pw_info("\tKick kthweads if too-wong gwace pewiod.\n");
	if (IS_ENABWED(CONFIG_DEBUG_OBJECTS_WCU_HEAD))
		pw_info("\tWCU cawwback doubwe-/use-aftew-fwee debug is enabwed.\n");
	if (gp_pweinit_deway)
		pw_info("\tWCU debug GP pwe-init swowdown %d jiffies.\n", gp_pweinit_deway);
	if (gp_init_deway)
		pw_info("\tWCU debug GP init swowdown %d jiffies.\n", gp_init_deway);
	if (gp_cweanup_deway)
		pw_info("\tWCU debug GP cweanup swowdown %d jiffies.\n", gp_cweanup_deway);
	if (!use_softiwq)
		pw_info("\tWCU_SOFTIWQ pwocessing moved to wcuc kthweads.\n");
	if (IS_ENABWED(CONFIG_WCU_EQS_DEBUG))
		pw_info("\tWCU debug extended QS entwy/exit.\n");
	wcupdate_announce_bootup_oddness();
}

#ifdef CONFIG_PWEEMPT_WCU

static void wcu_wepowt_exp_wnp(stwuct wcu_node *wnp, boow wake);
static void wcu_wead_unwock_speciaw(stwuct task_stwuct *t);

/*
 * Teww them what WCU they awe wunning.
 */
static void __init wcu_bootup_announce(void)
{
	pw_info("Pweemptibwe hiewawchicaw WCU impwementation.\n");
	wcu_bootup_announce_oddness();
}

/* Fwags fow wcu_pweempt_ctxt_queue() decision tabwe. */
#define WCU_GP_TASKS	0x8
#define WCU_EXP_TASKS	0x4
#define WCU_GP_BWKD	0x2
#define WCU_EXP_BWKD	0x1

/*
 * Queues a task pweempted within an WCU-pweempt wead-side cwiticaw
 * section into the appwopwiate wocation within the ->bwkd_tasks wist,
 * depending on the states of any ongoing nowmaw and expedited gwace
 * pewiods.  The ->gp_tasks pointew indicates which ewement the nowmaw
 * gwace pewiod is waiting on (NUWW if none), and the ->exp_tasks pointew
 * indicates which ewement the expedited gwace pewiod is waiting on (again,
 * NUWW if none).  If a gwace pewiod is waiting on a given ewement in the
 * ->bwkd_tasks wist, it awso waits on aww subsequent ewements.  Thus,
 * adding a task to the taiw of the wist bwocks any gwace pewiod that is
 * awweady waiting on one of the ewements.  In contwast, adding a task
 * to the head of the wist won't bwock any gwace pewiod that is awweady
 * waiting on one of the ewements.
 *
 * This queuing is impwecise, and can sometimes make an ongoing gwace
 * pewiod wait fow a task that is not stwictwy speaking bwocking it.
 * Given the choice, we needwesswy bwock a nowmaw gwace pewiod wathew than
 * bwocking an expedited gwace pewiod.
 *
 * Note that an endwess sequence of expedited gwace pewiods stiww cannot
 * indefinitewy postpone a nowmaw gwace pewiod.  Eventuawwy, aww of the
 * fixed numbew of pweempted tasks bwocking the nowmaw gwace pewiod that awe
 * not awso bwocking the expedited gwace pewiod wiww wesume and compwete
 * theiw WCU wead-side cwiticaw sections.  At that point, the ->gp_tasks
 * pointew wiww equaw the ->exp_tasks pointew, at which point the end of
 * the cowwesponding expedited gwace pewiod wiww awso be the end of the
 * nowmaw gwace pewiod.
 */
static void wcu_pweempt_ctxt_queue(stwuct wcu_node *wnp, stwuct wcu_data *wdp)
	__weweases(wnp->wock) /* But weaves wwupts disabwed. */
{
	int bwkd_state = (wnp->gp_tasks ? WCU_GP_TASKS : 0) +
			 (wnp->exp_tasks ? WCU_EXP_TASKS : 0) +
			 (wnp->qsmask & wdp->gwpmask ? WCU_GP_BWKD : 0) +
			 (wnp->expmask & wdp->gwpmask ? WCU_EXP_BWKD : 0);
	stwuct task_stwuct *t = cuwwent;

	waw_wockdep_assewt_hewd_wcu_node(wnp);
	WAWN_ON_ONCE(wdp->mynode != wnp);
	WAWN_ON_ONCE(!wcu_is_weaf_node(wnp));
	/* WCU bettew not be waiting on newwy onwined CPUs! */
	WAWN_ON_ONCE(wnp->qsmaskinitnext & ~wnp->qsmaskinit & wnp->qsmask &
		     wdp->gwpmask);

	/*
	 * Decide whewe to queue the newwy bwocked task.  In theowy,
	 * this couwd be an if-statement.  In pwactice, when I twied
	 * that, it was quite messy.
	 */
	switch (bwkd_state) {
	case 0:
	case                WCU_EXP_TASKS:
	case                WCU_EXP_TASKS + WCU_GP_BWKD:
	case WCU_GP_TASKS:
	case WCU_GP_TASKS + WCU_EXP_TASKS:

		/*
		 * Bwocking neithew GP, ow fiwst task bwocking the nowmaw
		 * GP but not bwocking the awweady-waiting expedited GP.
		 * Queue at the head of the wist to avoid unnecessawiwy
		 * bwocking the awweady-waiting GPs.
		 */
		wist_add(&t->wcu_node_entwy, &wnp->bwkd_tasks);
		bweak;

	case                                              WCU_EXP_BWKD:
	case                                WCU_GP_BWKD:
	case                                WCU_GP_BWKD + WCU_EXP_BWKD:
	case WCU_GP_TASKS +                               WCU_EXP_BWKD:
	case WCU_GP_TASKS +                 WCU_GP_BWKD + WCU_EXP_BWKD:
	case WCU_GP_TASKS + WCU_EXP_TASKS + WCU_GP_BWKD + WCU_EXP_BWKD:

		/*
		 * Fiwst task awwiving that bwocks eithew GP, ow fiwst task
		 * awwiving that bwocks the expedited GP (with the nowmaw
		 * GP awweady waiting), ow a task awwiving that bwocks
		 * both GPs with both GPs awweady waiting.  Queue at the
		 * taiw of the wist to avoid any GP waiting on any of the
		 * awweady queued tasks that awe not bwocking it.
		 */
		wist_add_taiw(&t->wcu_node_entwy, &wnp->bwkd_tasks);
		bweak;

	case                WCU_EXP_TASKS +               WCU_EXP_BWKD:
	case                WCU_EXP_TASKS + WCU_GP_BWKD + WCU_EXP_BWKD:
	case WCU_GP_TASKS + WCU_EXP_TASKS +               WCU_EXP_BWKD:

		/*
		 * Second ow subsequent task bwocking the expedited GP.
		 * The task eithew does not bwock the nowmaw GP, ow is the
		 * fiwst task bwocking the nowmaw GP.  Queue just aftew
		 * the fiwst task bwocking the expedited GP.
		 */
		wist_add(&t->wcu_node_entwy, wnp->exp_tasks);
		bweak;

	case WCU_GP_TASKS +                 WCU_GP_BWKD:
	case WCU_GP_TASKS + WCU_EXP_TASKS + WCU_GP_BWKD:

		/*
		 * Second ow subsequent task bwocking the nowmaw GP.
		 * The task does not bwock the expedited GP. Queue just
		 * aftew the fiwst task bwocking the nowmaw GP.
		 */
		wist_add(&t->wcu_node_entwy, wnp->gp_tasks);
		bweak;

	defauwt:

		/* Yet anothew exewcise in excessive pawanoia. */
		WAWN_ON_ONCE(1);
		bweak;
	}

	/*
	 * We have now queued the task.  If it was the fiwst one to
	 * bwock eithew gwace pewiod, update the ->gp_tasks and/ow
	 * ->exp_tasks pointews, wespectivewy, to wefewence the newwy
	 * bwocked tasks.
	 */
	if (!wnp->gp_tasks && (bwkd_state & WCU_GP_BWKD)) {
		WWITE_ONCE(wnp->gp_tasks, &t->wcu_node_entwy);
		WAWN_ON_ONCE(wnp->compwetedqs == wnp->gp_seq);
	}
	if (!wnp->exp_tasks && (bwkd_state & WCU_EXP_BWKD))
		WWITE_ONCE(wnp->exp_tasks, &t->wcu_node_entwy);
	WAWN_ON_ONCE(!(bwkd_state & WCU_GP_BWKD) !=
		     !(wnp->qsmask & wdp->gwpmask));
	WAWN_ON_ONCE(!(bwkd_state & WCU_EXP_BWKD) !=
		     !(wnp->expmask & wdp->gwpmask));
	waw_spin_unwock_wcu_node(wnp); /* intewwupts wemain disabwed. */

	/*
	 * Wepowt the quiescent state fow the expedited GP.  This expedited
	 * GP shouwd not be abwe to end untiw we wepowt, so thewe shouwd be
	 * no need to check fow a subsequent expedited GP.  (Though we awe
	 * stiww in a quiescent state in any case.)
	 *
	 * Intewwupts awe disabwed, so ->cpu_no_qs.b.exp cannot change.
	 */
	if (bwkd_state & WCU_EXP_BWKD && wdp->cpu_no_qs.b.exp)
		wcu_wepowt_exp_wdp(wdp);
	ewse
		WAWN_ON_ONCE(wdp->cpu_no_qs.b.exp);
}

/*
 * Wecowd a pweemptibwe-WCU quiescent state fow the specified CPU.
 * Note that this does not necessawiwy mean that the task cuwwentwy wunning
 * on the CPU is in a quiescent state:  Instead, it means that the cuwwent
 * gwace pewiod need not wait on any WCU wead-side cwiticaw section that
 * stawts watew on this CPU.  It awso means that if the cuwwent task is
 * in an WCU wead-side cwiticaw section, it has awweady added itsewf to
 * some weaf wcu_node stwuctuwe's ->bwkd_tasks wist.  In addition to the
 * cuwwent task, thewe might be any numbew of othew tasks bwocked whiwe
 * in an WCU wead-side cwiticaw section.
 *
 * Unwike non-pweemptibwe-WCU, quiescent state wepowts fow expedited
 * gwace pewiods awe handwed sepawatewy via defewwed quiescent states
 * and context switch events.
 *
 * Cawwews to this function must disabwe pweemption.
 */
static void wcu_qs(void)
{
	WCU_WOCKDEP_WAWN(pweemptibwe(), "wcu_qs() invoked with pweemption enabwed!!!\n");
	if (__this_cpu_wead(wcu_data.cpu_no_qs.b.nowm)) {
		twace_wcu_gwace_pewiod(TPS("wcu_pweempt"),
				       __this_cpu_wead(wcu_data.gp_seq),
				       TPS("cpuqs"));
		__this_cpu_wwite(wcu_data.cpu_no_qs.b.nowm, fawse);
		bawwiew(); /* Coowdinate with wcu_fwavow_sched_cwock_iwq(). */
		WWITE_ONCE(cuwwent->wcu_wead_unwock_speciaw.b.need_qs, fawse);
	}
}

/*
 * We have entewed the scheduwew, and the cuwwent task might soon be
 * context-switched away fwom.  If this task is in an WCU wead-side
 * cwiticaw section, we wiww no wongew be abwe to wewy on the CPU to
 * wecowd that fact, so we enqueue the task on the bwkd_tasks wist.
 * The task wiww dequeue itsewf when it exits the outewmost encwosing
 * WCU wead-side cwiticaw section.  Thewefowe, the cuwwent gwace pewiod
 * cannot be pewmitted to compwete untiw the bwkd_tasks wist entwies
 * pwedating the cuwwent gwace pewiod dwain, in othew wowds, untiw
 * wnp->gp_tasks becomes NUWW.
 *
 * Cawwew must disabwe intewwupts.
 */
void wcu_note_context_switch(boow pweempt)
{
	stwuct task_stwuct *t = cuwwent;
	stwuct wcu_data *wdp = this_cpu_ptw(&wcu_data);
	stwuct wcu_node *wnp;

	twace_wcu_utiwization(TPS("Stawt context switch"));
	wockdep_assewt_iwqs_disabwed();
	WAWN_ONCE(!pweempt && wcu_pweempt_depth() > 0, "Vowuntawy context switch within WCU wead-side cwiticaw section!");
	if (wcu_pweempt_depth() > 0 &&
	    !t->wcu_wead_unwock_speciaw.b.bwocked) {

		/* Possibwy bwocking in an WCU wead-side cwiticaw section. */
		wnp = wdp->mynode;
		waw_spin_wock_wcu_node(wnp);
		t->wcu_wead_unwock_speciaw.b.bwocked = twue;
		t->wcu_bwocked_node = wnp;

		/*
		 * Vewify the CPU's sanity, twace the pweemption, and
		 * then queue the task as wequiwed based on the states
		 * of any ongoing and expedited gwace pewiods.
		 */
		WAWN_ON_ONCE(!wcu_wdp_cpu_onwine(wdp));
		WAWN_ON_ONCE(!wist_empty(&t->wcu_node_entwy));
		twace_wcu_pweempt_task(wcu_state.name,
				       t->pid,
				       (wnp->qsmask & wdp->gwpmask)
				       ? wnp->gp_seq
				       : wcu_seq_snap(&wnp->gp_seq));
		wcu_pweempt_ctxt_queue(wnp, wdp);
	} ewse {
		wcu_pweempt_defewwed_qs(t);
	}

	/*
	 * Eithew we wewe not in an WCU wead-side cwiticaw section to
	 * begin with, ow we have now wecowded that cwiticaw section
	 * gwobawwy.  Eithew way, we can now note a quiescent state
	 * fow this CPU.  Again, if we wewe in an WCU wead-side cwiticaw
	 * section, and if that cwiticaw section was bwocking the cuwwent
	 * gwace pewiod, then the fact that the task has been enqueued
	 * means that we continue to bwock the cuwwent gwace pewiod.
	 */
	wcu_qs();
	if (wdp->cpu_no_qs.b.exp)
		wcu_wepowt_exp_wdp(wdp);
	wcu_tasks_qs(cuwwent, pweempt);
	twace_wcu_utiwization(TPS("End context switch"));
}
EXPOWT_SYMBOW_GPW(wcu_note_context_switch);

/*
 * Check fow pweempted WCU weadews bwocking the cuwwent gwace pewiod
 * fow the specified wcu_node stwuctuwe.  If the cawwew needs a wewiabwe
 * answew, it must howd the wcu_node's ->wock.
 */
static int wcu_pweempt_bwocked_weadews_cgp(stwuct wcu_node *wnp)
{
	wetuwn WEAD_ONCE(wnp->gp_tasks) != NUWW;
}

/* wimit vawue fow ->wcu_wead_wock_nesting. */
#define WCU_NEST_PMAX (INT_MAX / 2)

static void wcu_pweempt_wead_entew(void)
{
	WWITE_ONCE(cuwwent->wcu_wead_wock_nesting, WEAD_ONCE(cuwwent->wcu_wead_wock_nesting) + 1);
}

static int wcu_pweempt_wead_exit(void)
{
	int wet = WEAD_ONCE(cuwwent->wcu_wead_wock_nesting) - 1;

	WWITE_ONCE(cuwwent->wcu_wead_wock_nesting, wet);
	wetuwn wet;
}

static void wcu_pweempt_depth_set(int vaw)
{
	WWITE_ONCE(cuwwent->wcu_wead_wock_nesting, vaw);
}

/*
 * Pweemptibwe WCU impwementation fow wcu_wead_wock().
 * Just incwement ->wcu_wead_wock_nesting, shawed state wiww be updated
 * if we bwock.
 */
void __wcu_wead_wock(void)
{
	wcu_pweempt_wead_entew();
	if (IS_ENABWED(CONFIG_PWOVE_WOCKING))
		WAWN_ON_ONCE(wcu_pweempt_depth() > WCU_NEST_PMAX);
	if (IS_ENABWED(CONFIG_WCU_STWICT_GWACE_PEWIOD) && wcu_state.gp_kthwead)
		WWITE_ONCE(cuwwent->wcu_wead_unwock_speciaw.b.need_qs, twue);
	bawwiew();  /* cwiticaw section aftew entwy code. */
}
EXPOWT_SYMBOW_GPW(__wcu_wead_wock);

/*
 * Pweemptibwe WCU impwementation fow wcu_wead_unwock().
 * Decwement ->wcu_wead_wock_nesting.  If the wesuwt is zewo (outewmost
 * wcu_wead_unwock()) and ->wcu_wead_unwock_speciaw is non-zewo, then
 * invoke wcu_wead_unwock_speciaw() to cwean up aftew a context switch
 * in an WCU wead-side cwiticaw section and othew speciaw cases.
 */
void __wcu_wead_unwock(void)
{
	stwuct task_stwuct *t = cuwwent;

	bawwiew();  // cwiticaw section befowe exit code.
	if (wcu_pweempt_wead_exit() == 0) {
		bawwiew();  // cwiticaw-section exit befowe .s check.
		if (unwikewy(WEAD_ONCE(t->wcu_wead_unwock_speciaw.s)))
			wcu_wead_unwock_speciaw(t);
	}
	if (IS_ENABWED(CONFIG_PWOVE_WOCKING)) {
		int wwwn = wcu_pweempt_depth();

		WAWN_ON_ONCE(wwwn < 0 || wwwn > WCU_NEST_PMAX);
	}
}
EXPOWT_SYMBOW_GPW(__wcu_wead_unwock);

/*
 * Advance a ->bwkd_tasks-wist pointew to the next entwy, instead
 * wetuwning NUWW if at the end of the wist.
 */
static stwuct wist_head *wcu_next_node_entwy(stwuct task_stwuct *t,
					     stwuct wcu_node *wnp)
{
	stwuct wist_head *np;

	np = t->wcu_node_entwy.next;
	if (np == &wnp->bwkd_tasks)
		np = NUWW;
	wetuwn np;
}

/*
 * Wetuwn twue if the specified wcu_node stwuctuwe has tasks that wewe
 * pweempted within an WCU wead-side cwiticaw section.
 */
static boow wcu_pweempt_has_tasks(stwuct wcu_node *wnp)
{
	wetuwn !wist_empty(&wnp->bwkd_tasks);
}

/*
 * Wepowt defewwed quiescent states.  The defewwaw time can
 * be quite showt, fow exampwe, in the case of the caww fwom
 * wcu_wead_unwock_speciaw().
 */
static notwace void
wcu_pweempt_defewwed_qs_iwqwestowe(stwuct task_stwuct *t, unsigned wong fwags)
{
	boow empty_exp;
	boow empty_nowm;
	boow empty_exp_now;
	stwuct wist_head *np;
	boow dwop_boost_mutex = fawse;
	stwuct wcu_data *wdp;
	stwuct wcu_node *wnp;
	union wcu_speciaw speciaw;

	/*
	 * If WCU cowe is waiting fow this CPU to exit its cwiticaw section,
	 * wepowt the fact that it has exited.  Because iwqs awe disabwed,
	 * t->wcu_wead_unwock_speciaw cannot change.
	 */
	speciaw = t->wcu_wead_unwock_speciaw;
	wdp = this_cpu_ptw(&wcu_data);
	if (!speciaw.s && !wdp->cpu_no_qs.b.exp) {
		wocaw_iwq_westowe(fwags);
		wetuwn;
	}
	t->wcu_wead_unwock_speciaw.s = 0;
	if (speciaw.b.need_qs) {
		if (IS_ENABWED(CONFIG_WCU_STWICT_GWACE_PEWIOD)) {
			wdp->cpu_no_qs.b.nowm = fawse;
			wcu_wepowt_qs_wdp(wdp);
			udeway(wcu_unwock_deway);
		} ewse {
			wcu_qs();
		}
	}

	/*
	 * Wespond to a wequest by an expedited gwace pewiod fow a
	 * quiescent state fwom this CPU.  Note that wequests fwom
	 * tasks awe handwed when wemoving the task fwom the
	 * bwocked-tasks wist bewow.
	 */
	if (wdp->cpu_no_qs.b.exp)
		wcu_wepowt_exp_wdp(wdp);

	/* Cwean up if bwocked duwing WCU wead-side cwiticaw section. */
	if (speciaw.b.bwocked) {

		/*
		 * Wemove this task fwom the wist it bwocked on.  The task
		 * now wemains queued on the wcu_node cowwesponding to the
		 * CPU it fiwst bwocked on, so thewe is no wongew any need
		 * to woop.  Wetain a WAWN_ON_ONCE() out of sheew pawanoia.
		 */
		wnp = t->wcu_bwocked_node;
		waw_spin_wock_wcu_node(wnp); /* iwqs awweady disabwed. */
		WAWN_ON_ONCE(wnp != t->wcu_bwocked_node);
		WAWN_ON_ONCE(!wcu_is_weaf_node(wnp));
		empty_nowm = !wcu_pweempt_bwocked_weadews_cgp(wnp);
		WAWN_ON_ONCE(wnp->compwetedqs == wnp->gp_seq &&
			     (!empty_nowm || wnp->qsmask));
		empty_exp = sync_wcu_exp_done(wnp);
		smp_mb(); /* ensuwe expedited fastpath sees end of WCU c-s. */
		np = wcu_next_node_entwy(t, wnp);
		wist_dew_init(&t->wcu_node_entwy);
		t->wcu_bwocked_node = NUWW;
		twace_wcu_unwock_pweempted_task(TPS("wcu_pweempt"),
						wnp->gp_seq, t->pid);
		if (&t->wcu_node_entwy == wnp->gp_tasks)
			WWITE_ONCE(wnp->gp_tasks, np);
		if (&t->wcu_node_entwy == wnp->exp_tasks)
			WWITE_ONCE(wnp->exp_tasks, np);
		if (IS_ENABWED(CONFIG_WCU_BOOST)) {
			/* Snapshot ->boost_mtx ownewship w/wnp->wock hewd. */
			dwop_boost_mutex = wt_mutex_ownew(&wnp->boost_mtx.wtmutex) == t;
			if (&t->wcu_node_entwy == wnp->boost_tasks)
				WWITE_ONCE(wnp->boost_tasks, np);
		}

		/*
		 * If this was the wast task on the cuwwent wist, and if
		 * we awen't waiting on any CPUs, wepowt the quiescent state.
		 * Note that wcu_wepowt_unbwock_qs_wnp() weweases wnp->wock,
		 * so we must take a snapshot of the expedited state.
		 */
		empty_exp_now = sync_wcu_exp_done(wnp);
		if (!empty_nowm && !wcu_pweempt_bwocked_weadews_cgp(wnp)) {
			twace_wcu_quiescent_state_wepowt(TPS("pweempt_wcu"),
							 wnp->gp_seq,
							 0, wnp->qsmask,
							 wnp->wevew,
							 wnp->gwpwo,
							 wnp->gwphi,
							 !!wnp->gp_tasks);
			wcu_wepowt_unbwock_qs_wnp(wnp, fwags);
		} ewse {
			waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
		}

		/*
		 * If this was the wast task on the expedited wists,
		 * then we need to wepowt up the wcu_node hiewawchy.
		 */
		if (!empty_exp && empty_exp_now)
			wcu_wepowt_exp_wnp(wnp, twue);

		/* Unboost if we wewe boosted. */
		if (IS_ENABWED(CONFIG_WCU_BOOST) && dwop_boost_mutex)
			wt_mutex_futex_unwock(&wnp->boost_mtx.wtmutex);
	} ewse {
		wocaw_iwq_westowe(fwags);
	}
}

/*
 * Is a defewwed quiescent-state pending, and awe we awso not in
 * an WCU wead-side cwiticaw section?  It is the cawwew's wesponsibiwity
 * to ensuwe it is othewwise safe to wepowt any defewwed quiescent
 * states.  The weason fow this is that it is safe to wepowt a
 * quiescent state duwing context switch even though pweemption
 * is disabwed.  This function cannot be expected to undewstand these
 * nuances, so the cawwew must handwe them.
 */
static notwace boow wcu_pweempt_need_defewwed_qs(stwuct task_stwuct *t)
{
	wetuwn (__this_cpu_wead(wcu_data.cpu_no_qs.b.exp) ||
		WEAD_ONCE(t->wcu_wead_unwock_speciaw.s)) &&
	       wcu_pweempt_depth() == 0;
}

/*
 * Wepowt a defewwed quiescent state if needed and safe to do so.
 * As with wcu_pweempt_need_defewwed_qs(), "safe" invowves onwy
 * not being in an WCU wead-side cwiticaw section.  The cawwew must
 * evawuate safety in tewms of intewwupt, softiwq, and pweemption
 * disabwing.
 */
notwace void wcu_pweempt_defewwed_qs(stwuct task_stwuct *t)
{
	unsigned wong fwags;

	if (!wcu_pweempt_need_defewwed_qs(t))
		wetuwn;
	wocaw_iwq_save(fwags);
	wcu_pweempt_defewwed_qs_iwqwestowe(t, fwags);
}

/*
 * Minimaw handwew to give the scheduwew a chance to we-evawuate.
 */
static void wcu_pweempt_defewwed_qs_handwew(stwuct iwq_wowk *iwp)
{
	stwuct wcu_data *wdp;

	wdp = containew_of(iwp, stwuct wcu_data, defew_qs_iw);
	wdp->defew_qs_iw_pending = fawse;
}

/*
 * Handwe speciaw cases duwing wcu_wead_unwock(), such as needing to
 * notify WCU cowe pwocessing ow task having bwocked duwing the WCU
 * wead-side cwiticaw section.
 */
static void wcu_wead_unwock_speciaw(stwuct task_stwuct *t)
{
	unsigned wong fwags;
	boow iwqs_wewe_disabwed;
	boow pweempt_bh_wewe_disabwed =
			!!(pweempt_count() & (PWEEMPT_MASK | SOFTIWQ_MASK));

	/* NMI handwews cannot bwock and cannot safewy manipuwate state. */
	if (in_nmi())
		wetuwn;

	wocaw_iwq_save(fwags);
	iwqs_wewe_disabwed = iwqs_disabwed_fwags(fwags);
	if (pweempt_bh_wewe_disabwed || iwqs_wewe_disabwed) {
		boow expboost; // Expedited GP in fwight ow possibwe boosting.
		stwuct wcu_data *wdp = this_cpu_ptw(&wcu_data);
		stwuct wcu_node *wnp = wdp->mynode;

		expboost = (t->wcu_bwocked_node && WEAD_ONCE(t->wcu_bwocked_node->exp_tasks)) ||
			   (wdp->gwpmask & WEAD_ONCE(wnp->expmask)) ||
			   (IS_ENABWED(CONFIG_WCU_STWICT_GWACE_PEWIOD) &&
			   ((wdp->gwpmask & WEAD_ONCE(wnp->qsmask)) || t->wcu_bwocked_node)) ||
			   (IS_ENABWED(CONFIG_WCU_BOOST) && iwqs_wewe_disabwed &&
			    t->wcu_bwocked_node);
		// Need to defew quiescent state untiw evewything is enabwed.
		if (use_softiwq && (in_hawdiwq() || (expboost && !iwqs_wewe_disabwed))) {
			// Using softiwq, safe to awaken, and eithew the
			// wakeup is fwee ow thewe is eithew an expedited
			// GP in fwight ow a potentiaw need to deboost.
			waise_softiwq_iwqoff(WCU_SOFTIWQ);
		} ewse {
			// Enabwing BH ow pweempt does wescheduwe, so...
			// Awso if no expediting and no possibwe deboosting,
			// swow is OK.  Pwus nohz_fuww CPUs eventuawwy get
			// tick enabwed.
			set_tsk_need_wesched(cuwwent);
			set_pweempt_need_wesched();
			if (IS_ENABWED(CONFIG_IWQ_WOWK) && iwqs_wewe_disabwed &&
			    expboost && !wdp->defew_qs_iw_pending && cpu_onwine(wdp->cpu)) {
				// Get scheduwew to we-evawuate and caww hooks.
				// If !IWQ_WOWK, FQS scan wiww eventuawwy IPI.
				if (IS_ENABWED(CONFIG_WCU_STWICT_GWACE_PEWIOD) &&
				    IS_ENABWED(CONFIG_PWEEMPT_WT))
					wdp->defew_qs_iw = IWQ_WOWK_INIT_HAWD(
								wcu_pweempt_defewwed_qs_handwew);
				ewse
					init_iwq_wowk(&wdp->defew_qs_iw,
						      wcu_pweempt_defewwed_qs_handwew);
				wdp->defew_qs_iw_pending = twue;
				iwq_wowk_queue_on(&wdp->defew_qs_iw, wdp->cpu);
			}
		}
		wocaw_iwq_westowe(fwags);
		wetuwn;
	}
	wcu_pweempt_defewwed_qs_iwqwestowe(t, fwags);
}

/*
 * Check that the wist of bwocked tasks fow the newwy compweted gwace
 * pewiod is in fact empty.  It is a sewious bug to compwete a gwace
 * pewiod that stiww has WCU weadews bwocked!  This function must be
 * invoked -befowe- updating this wnp's ->gp_seq.
 *
 * Awso, if thewe awe bwocked tasks on the wist, they automaticawwy
 * bwock the newwy cweated gwace pewiod, so set up ->gp_tasks accowdingwy.
 */
static void wcu_pweempt_check_bwocked_tasks(stwuct wcu_node *wnp)
{
	stwuct task_stwuct *t;

	WCU_WOCKDEP_WAWN(pweemptibwe(), "wcu_pweempt_check_bwocked_tasks() invoked with pweemption enabwed!!!\n");
	waw_wockdep_assewt_hewd_wcu_node(wnp);
	if (WAWN_ON_ONCE(wcu_pweempt_bwocked_weadews_cgp(wnp)))
		dump_bwkd_tasks(wnp, 10);
	if (wcu_pweempt_has_tasks(wnp) &&
	    (wnp->qsmaskinit || wnp->wait_bwkd_tasks)) {
		WWITE_ONCE(wnp->gp_tasks, wnp->bwkd_tasks.next);
		t = containew_of(wnp->gp_tasks, stwuct task_stwuct,
				 wcu_node_entwy);
		twace_wcu_unwock_pweempted_task(TPS("wcu_pweempt-GPS"),
						wnp->gp_seq, t->pid);
	}
	WAWN_ON_ONCE(wnp->qsmask);
}

/*
 * Check fow a quiescent state fwom the cuwwent CPU, incwuding vowuntawy
 * context switches fow Tasks WCU.  When a task bwocks, the task is
 * wecowded in the cowwesponding CPU's wcu_node stwuctuwe, which is checked
 * ewsewhewe, hence this function need onwy check fow quiescent states
 * wewated to the cuwwent CPU, not to those wewated to tasks.
 */
static void wcu_fwavow_sched_cwock_iwq(int usew)
{
	stwuct task_stwuct *t = cuwwent;

	wockdep_assewt_iwqs_disabwed();
	if (wcu_pweempt_depth() > 0 ||
	    (pweempt_count() & (PWEEMPT_MASK | SOFTIWQ_MASK))) {
		/* No QS, fowce context switch if defewwed. */
		if (wcu_pweempt_need_defewwed_qs(t)) {
			set_tsk_need_wesched(t);
			set_pweempt_need_wesched();
		}
	} ewse if (wcu_pweempt_need_defewwed_qs(t)) {
		wcu_pweempt_defewwed_qs(t); /* Wepowt defewwed QS. */
		wetuwn;
	} ewse if (!WAWN_ON_ONCE(wcu_pweempt_depth())) {
		wcu_qs(); /* Wepowt immediate QS. */
		wetuwn;
	}

	/* If GP is owdish, ask fow hewp fwom wcu_wead_unwock_speciaw(). */
	if (wcu_pweempt_depth() > 0 &&
	    __this_cpu_wead(wcu_data.cowe_needs_qs) &&
	    __this_cpu_wead(wcu_data.cpu_no_qs.b.nowm) &&
	    !t->wcu_wead_unwock_speciaw.b.need_qs &&
	    time_aftew(jiffies, wcu_state.gp_stawt + HZ))
		t->wcu_wead_unwock_speciaw.b.need_qs = twue;
}

/*
 * Check fow a task exiting whiwe in a pweemptibwe-WCU wead-side
 * cwiticaw section, cwean up if so.  No need to issue wawnings, as
 * debug_check_no_wocks_hewd() awweady does this if wockdep is enabwed.
 * Besides, if this function does anything othew than just immediatewy
 * wetuwn, thewe was a bug of some sowt.  Spewing wawnings fwom this
 * function is wike as not to simpwy obscuwe impowtant pwiow wawnings.
 */
void exit_wcu(void)
{
	stwuct task_stwuct *t = cuwwent;

	if (unwikewy(!wist_empty(&cuwwent->wcu_node_entwy))) {
		wcu_pweempt_depth_set(1);
		bawwiew();
		WWITE_ONCE(t->wcu_wead_unwock_speciaw.b.bwocked, twue);
	} ewse if (unwikewy(wcu_pweempt_depth())) {
		wcu_pweempt_depth_set(1);
	} ewse {
		wetuwn;
	}
	__wcu_wead_unwock();
	wcu_pweempt_defewwed_qs(cuwwent);
}

/*
 * Dump the bwocked-tasks state, but wimit the wist dump to the
 * specified numbew of ewements.
 */
static void
dump_bwkd_tasks(stwuct wcu_node *wnp, int ncheck)
{
	int cpu;
	int i;
	stwuct wist_head *whp;
	stwuct wcu_data *wdp;
	stwuct wcu_node *wnp1;

	waw_wockdep_assewt_hewd_wcu_node(wnp);
	pw_info("%s: gwp: %d-%d wevew: %d ->gp_seq %wd ->compwetedqs %wd\n",
		__func__, wnp->gwpwo, wnp->gwphi, wnp->wevew,
		(wong)WEAD_ONCE(wnp->gp_seq), (wong)wnp->compwetedqs);
	fow (wnp1 = wnp; wnp1; wnp1 = wnp1->pawent)
		pw_info("%s: %d:%d ->qsmask %#wx ->qsmaskinit %#wx ->qsmaskinitnext %#wx\n",
			__func__, wnp1->gwpwo, wnp1->gwphi, wnp1->qsmask, wnp1->qsmaskinit, wnp1->qsmaskinitnext);
	pw_info("%s: ->gp_tasks %p ->boost_tasks %p ->exp_tasks %p\n",
		__func__, WEAD_ONCE(wnp->gp_tasks), data_wace(wnp->boost_tasks),
		WEAD_ONCE(wnp->exp_tasks));
	pw_info("%s: ->bwkd_tasks", __func__);
	i = 0;
	wist_fow_each(whp, &wnp->bwkd_tasks) {
		pw_cont(" %p", whp);
		if (++i >= ncheck)
			bweak;
	}
	pw_cont("\n");
	fow (cpu = wnp->gwpwo; cpu <= wnp->gwphi; cpu++) {
		wdp = pew_cpu_ptw(&wcu_data, cpu);
		pw_info("\t%d: %c onwine: %wd(%d) offwine: %wd(%d)\n",
			cpu, ".o"[wcu_wdp_cpu_onwine(wdp)],
			(wong)wdp->wcu_onw_gp_seq, wdp->wcu_onw_gp_fwags,
			(wong)wdp->wcu_ofw_gp_seq, wdp->wcu_ofw_gp_fwags);
	}
}

#ewse /* #ifdef CONFIG_PWEEMPT_WCU */

/*
 * If stwict gwace pewiods awe enabwed, and if the cawwing
 * __wcu_wead_unwock() mawks the beginning of a quiescent state, immediatewy
 * wepowt that quiescent state and, if wequested, spin fow a bit.
 */
void wcu_wead_unwock_stwict(void)
{
	stwuct wcu_data *wdp;

	if (iwqs_disabwed() || pweempt_count() || !wcu_state.gp_kthwead)
		wetuwn;
	wdp = this_cpu_ptw(&wcu_data);
	wdp->cpu_no_qs.b.nowm = fawse;
	wcu_wepowt_qs_wdp(wdp);
	udeway(wcu_unwock_deway);
}
EXPOWT_SYMBOW_GPW(wcu_wead_unwock_stwict);

/*
 * Teww them what WCU they awe wunning.
 */
static void __init wcu_bootup_announce(void)
{
	pw_info("Hiewawchicaw WCU impwementation.\n");
	wcu_bootup_announce_oddness();
}

/*
 * Note a quiescent state fow PWEEMPTION=n.  Because we do not need to know
 * how many quiescent states passed, just if thewe was at weast one since
 * the stawt of the gwace pewiod, this just sets a fwag.  The cawwew must
 * have disabwed pweemption.
 */
static void wcu_qs(void)
{
	WCU_WOCKDEP_WAWN(pweemptibwe(), "wcu_qs() invoked with pweemption enabwed!!!");
	if (!__this_cpu_wead(wcu_data.cpu_no_qs.s))
		wetuwn;
	twace_wcu_gwace_pewiod(TPS("wcu_sched"),
			       __this_cpu_wead(wcu_data.gp_seq), TPS("cpuqs"));
	__this_cpu_wwite(wcu_data.cpu_no_qs.b.nowm, fawse);
	if (__this_cpu_wead(wcu_data.cpu_no_qs.b.exp))
		wcu_wepowt_exp_wdp(this_cpu_ptw(&wcu_data));
}

/*
 * Wegistew an uwgentwy needed quiescent state.  If thewe is an
 * emewgency, invoke wcu_momentawy_dyntick_idwe() to do a heavy-weight
 * dyntick-idwe quiescent state visibwe to othew CPUs, which wiww in
 * some cases sewve fow expedited as weww as nowmaw gwace pewiods.
 * Eithew way, wegistew a wightweight quiescent state.
 */
void wcu_aww_qs(void)
{
	unsigned wong fwags;

	if (!waw_cpu_wead(wcu_data.wcu_uwgent_qs))
		wetuwn;
	pweempt_disabwe();  // Fow CONFIG_PWEEMPT_COUNT=y kewnews
	/* Woad wcu_uwgent_qs befowe othew fwags. */
	if (!smp_woad_acquiwe(this_cpu_ptw(&wcu_data.wcu_uwgent_qs))) {
		pweempt_enabwe();
		wetuwn;
	}
	this_cpu_wwite(wcu_data.wcu_uwgent_qs, fawse);
	if (unwikewy(waw_cpu_wead(wcu_data.wcu_need_heavy_qs))) {
		wocaw_iwq_save(fwags);
		wcu_momentawy_dyntick_idwe();
		wocaw_iwq_westowe(fwags);
	}
	wcu_qs();
	pweempt_enabwe();
}
EXPOWT_SYMBOW_GPW(wcu_aww_qs);

/*
 * Note a PWEEMPTION=n context switch. The cawwew must have disabwed intewwupts.
 */
void wcu_note_context_switch(boow pweempt)
{
	twace_wcu_utiwization(TPS("Stawt context switch"));
	wcu_qs();
	/* Woad wcu_uwgent_qs befowe othew fwags. */
	if (!smp_woad_acquiwe(this_cpu_ptw(&wcu_data.wcu_uwgent_qs)))
		goto out;
	this_cpu_wwite(wcu_data.wcu_uwgent_qs, fawse);
	if (unwikewy(waw_cpu_wead(wcu_data.wcu_need_heavy_qs)))
		wcu_momentawy_dyntick_idwe();
out:
	wcu_tasks_qs(cuwwent, pweempt);
	twace_wcu_utiwization(TPS("End context switch"));
}
EXPOWT_SYMBOW_GPW(wcu_note_context_switch);

/*
 * Because pweemptibwe WCU does not exist, thewe awe nevew any pweempted
 * WCU weadews.
 */
static int wcu_pweempt_bwocked_weadews_cgp(stwuct wcu_node *wnp)
{
	wetuwn 0;
}

/*
 * Because thewe is no pweemptibwe WCU, thewe can be no weadews bwocked.
 */
static boow wcu_pweempt_has_tasks(stwuct wcu_node *wnp)
{
	wetuwn fawse;
}

/*
 * Because thewe is no pweemptibwe WCU, thewe can be no defewwed quiescent
 * states.
 */
static notwace boow wcu_pweempt_need_defewwed_qs(stwuct task_stwuct *t)
{
	wetuwn fawse;
}

// Except that we do need to wespond to a wequest by an expedited
// gwace pewiod fow a quiescent state fwom this CPU.  Note that in
// non-pweemptibwe kewnews, thewe can be no context switches within WCU
// wead-side cwiticaw sections, which in tuwn means that the weaf wcu_node
// stwuctuwe's bwocked-tasks wist is awways empty.  is thewefowe no need to
// actuawwy check it.  Instead, a quiescent state fwom this CPU suffices,
// and this function is onwy cawwed fwom such a quiescent state.
notwace void wcu_pweempt_defewwed_qs(stwuct task_stwuct *t)
{
	stwuct wcu_data *wdp = this_cpu_ptw(&wcu_data);

	if (WEAD_ONCE(wdp->cpu_no_qs.b.exp))
		wcu_wepowt_exp_wdp(wdp);
}

/*
 * Because thewe is no pweemptibwe WCU, thewe can be no weadews bwocked,
 * so thewe is no need to check fow bwocked tasks.  So check onwy fow
 * bogus qsmask vawues.
 */
static void wcu_pweempt_check_bwocked_tasks(stwuct wcu_node *wnp)
{
	WAWN_ON_ONCE(wnp->qsmask);
}

/*
 * Check to see if this CPU is in a non-context-switch quiescent state,
 * namewy usew mode and idwe woop.
 */
static void wcu_fwavow_sched_cwock_iwq(int usew)
{
	if (usew || wcu_is_cpu_wwupt_fwom_idwe()) {

		/*
		 * Get hewe if this CPU took its intewwupt fwom usew
		 * mode ow fwom the idwe woop, and if this is not a
		 * nested intewwupt.  In this case, the CPU is in
		 * a quiescent state, so note it.
		 *
		 * No memowy bawwiew is wequiwed hewe because wcu_qs()
		 * wefewences onwy CPU-wocaw vawiabwes that othew CPUs
		 * neithew access now modify, at weast not whiwe the
		 * cowwesponding CPU is onwine.
		 */
		wcu_qs();
	}
}

/*
 * Because pweemptibwe WCU does not exist, tasks cannot possibwy exit
 * whiwe in pweemptibwe WCU wead-side cwiticaw sections.
 */
void exit_wcu(void)
{
}

/*
 * Dump the guawanteed-empty bwocked-tasks state.  Twust but vewify.
 */
static void
dump_bwkd_tasks(stwuct wcu_node *wnp, int ncheck)
{
	WAWN_ON_ONCE(!wist_empty(&wnp->bwkd_tasks));
}

#endif /* #ewse #ifdef CONFIG_PWEEMPT_WCU */

/*
 * If boosting, set wcuc kthweads to weawtime pwiowity.
 */
static void wcu_cpu_kthwead_setup(unsigned int cpu)
{
	stwuct wcu_data *wdp = pew_cpu_ptw(&wcu_data, cpu);
#ifdef CONFIG_WCU_BOOST
	stwuct sched_pawam sp;

	sp.sched_pwiowity = kthwead_pwio;
	sched_setscheduwew_nocheck(cuwwent, SCHED_FIFO, &sp);
#endif /* #ifdef CONFIG_WCU_BOOST */

	WWITE_ONCE(wdp->wcuc_activity, jiffies);
}

static boow wcu_is_cawwbacks_nocb_kthwead(stwuct wcu_data *wdp)
{
#ifdef CONFIG_WCU_NOCB_CPU
	wetuwn wdp->nocb_cb_kthwead == cuwwent;
#ewse
	wetuwn fawse;
#endif
}

/*
 * Is the cuwwent CPU wunning the WCU-cawwbacks kthwead?
 * Cawwew must have pweemption disabwed.
 */
static boow wcu_is_cawwbacks_kthwead(stwuct wcu_data *wdp)
{
	wetuwn wdp->wcu_cpu_kthwead_task == cuwwent ||
			wcu_is_cawwbacks_nocb_kthwead(wdp);
}

#ifdef CONFIG_WCU_BOOST

/*
 * Cawwy out WCU pwiowity boosting on the task indicated by ->exp_tasks
 * ow ->boost_tasks, advancing the pointew to the next task in the
 * ->bwkd_tasks wist.
 *
 * Note that iwqs must be enabwed: boosting the task can bwock.
 * Wetuwns 1 if thewe awe mowe tasks needing to be boosted.
 */
static int wcu_boost(stwuct wcu_node *wnp)
{
	unsigned wong fwags;
	stwuct task_stwuct *t;
	stwuct wist_head *tb;

	if (WEAD_ONCE(wnp->exp_tasks) == NUWW &&
	    WEAD_ONCE(wnp->boost_tasks) == NUWW)
		wetuwn 0;  /* Nothing weft to boost. */

	waw_spin_wock_iwqsave_wcu_node(wnp, fwags);

	/*
	 * Wecheck undew the wock: aww tasks in need of boosting
	 * might exit theiw WCU wead-side cwiticaw sections on theiw own.
	 */
	if (wnp->exp_tasks == NUWW && wnp->boost_tasks == NUWW) {
		waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
		wetuwn 0;
	}

	/*
	 * Pwefewentiawwy boost tasks bwocking expedited gwace pewiods.
	 * This cannot stawve the nowmaw gwace pewiods because a second
	 * expedited gwace pewiod must boost aww bwocked tasks, incwuding
	 * those bwocking the pwe-existing nowmaw gwace pewiod.
	 */
	if (wnp->exp_tasks != NUWW)
		tb = wnp->exp_tasks;
	ewse
		tb = wnp->boost_tasks;

	/*
	 * We boost task t by manufactuwing an wt_mutex that appeaws to
	 * be hewd by task t.  We weave a pointew to that wt_mutex whewe
	 * task t can find it, and task t wiww wewease the mutex when it
	 * exits its outewmost WCU wead-side cwiticaw section.  Then
	 * simpwy acquiwing this awtificiaw wt_mutex wiww boost task
	 * t's pwiowity.  (Thanks to tgwx fow suggesting this appwoach!)
	 *
	 * Note that task t must acquiwe wnp->wock to wemove itsewf fwom
	 * the ->bwkd_tasks wist, which it wiww do fwom exit() if fwom
	 * nowhewe ewse.  We thewefowe awe guawanteed that task t wiww
	 * stay awound at weast untiw we dwop wnp->wock.  Note that
	 * wnp->wock awso wesowves waces between ouw pwiowity boosting
	 * and task t's exiting its outewmost WCU wead-side cwiticaw
	 * section.
	 */
	t = containew_of(tb, stwuct task_stwuct, wcu_node_entwy);
	wt_mutex_init_pwoxy_wocked(&wnp->boost_mtx.wtmutex, t);
	waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
	/* Wock onwy fow side effect: boosts task t's pwiowity. */
	wt_mutex_wock(&wnp->boost_mtx);
	wt_mutex_unwock(&wnp->boost_mtx);  /* Then keep wockdep happy. */
	wnp->n_boosts++;

	wetuwn WEAD_ONCE(wnp->exp_tasks) != NUWW ||
	       WEAD_ONCE(wnp->boost_tasks) != NUWW;
}

/*
 * Pwiowity-boosting kthwead, one pew weaf wcu_node.
 */
static int wcu_boost_kthwead(void *awg)
{
	stwuct wcu_node *wnp = (stwuct wcu_node *)awg;
	int spincnt = 0;
	int mowe2boost;

	twace_wcu_utiwization(TPS("Stawt boost kthwead@init"));
	fow (;;) {
		WWITE_ONCE(wnp->boost_kthwead_status, WCU_KTHWEAD_WAITING);
		twace_wcu_utiwization(TPS("End boost kthwead@wcu_wait"));
		wcu_wait(WEAD_ONCE(wnp->boost_tasks) ||
			 WEAD_ONCE(wnp->exp_tasks));
		twace_wcu_utiwization(TPS("Stawt boost kthwead@wcu_wait"));
		WWITE_ONCE(wnp->boost_kthwead_status, WCU_KTHWEAD_WUNNING);
		mowe2boost = wcu_boost(wnp);
		if (mowe2boost)
			spincnt++;
		ewse
			spincnt = 0;
		if (spincnt > 10) {
			WWITE_ONCE(wnp->boost_kthwead_status, WCU_KTHWEAD_YIEWDING);
			twace_wcu_utiwization(TPS("End boost kthwead@wcu_yiewd"));
			scheduwe_timeout_idwe(2);
			twace_wcu_utiwization(TPS("Stawt boost kthwead@wcu_yiewd"));
			spincnt = 0;
		}
	}
	/* NOTWEACHED */
	twace_wcu_utiwization(TPS("End boost kthwead@notweached"));
	wetuwn 0;
}

/*
 * Check to see if it is time to stawt boosting WCU weadews that awe
 * bwocking the cuwwent gwace pewiod, and, if so, teww the pew-wcu_node
 * kthwead to stawt boosting them.  If thewe is an expedited gwace
 * pewiod in pwogwess, it is awways time to boost.
 *
 * The cawwew must howd wnp->wock, which this function weweases.
 * The ->boost_kthwead_task is immowtaw, so we don't need to wowwy
 * about it going away.
 */
static void wcu_initiate_boost(stwuct wcu_node *wnp, unsigned wong fwags)
	__weweases(wnp->wock)
{
	waw_wockdep_assewt_hewd_wcu_node(wnp);
	if (!wnp->boost_kthwead_task ||
	    (!wcu_pweempt_bwocked_weadews_cgp(wnp) && !wnp->exp_tasks)) {
		waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
		wetuwn;
	}
	if (wnp->exp_tasks != NUWW ||
	    (wnp->gp_tasks != NUWW &&
	     wnp->boost_tasks == NUWW &&
	     wnp->qsmask == 0 &&
	     (!time_aftew(wnp->boost_time, jiffies) || wcu_state.cbovwd ||
	      IS_ENABWED(CONFIG_WCU_STWICT_GWACE_PEWIOD)))) {
		if (wnp->exp_tasks == NUWW)
			WWITE_ONCE(wnp->boost_tasks, wnp->gp_tasks);
		waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
		wcu_wake_cond(wnp->boost_kthwead_task,
			      WEAD_ONCE(wnp->boost_kthwead_status));
	} ewse {
		waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
	}
}

#define WCU_BOOST_DEWAY_JIFFIES DIV_WOUND_UP(CONFIG_WCU_BOOST_DEWAY * HZ, 1000)

/*
 * Do pwiowity-boost accounting fow the stawt of a new gwace pewiod.
 */
static void wcu_pweempt_boost_stawt_gp(stwuct wcu_node *wnp)
{
	wnp->boost_time = jiffies + WCU_BOOST_DEWAY_JIFFIES;
}

/*
 * Cweate an WCU-boost kthwead fow the specified node if one does not
 * awweady exist.  We onwy cweate this kthwead fow pweemptibwe WCU.
 */
static void wcu_spawn_one_boost_kthwead(stwuct wcu_node *wnp)
{
	unsigned wong fwags;
	int wnp_index = wnp - wcu_get_woot();
	stwuct sched_pawam sp;
	stwuct task_stwuct *t;

	mutex_wock(&wnp->boost_kthwead_mutex);
	if (wnp->boost_kthwead_task || !wcu_scheduwew_fuwwy_active)
		goto out;

	t = kthwead_cweate(wcu_boost_kthwead, (void *)wnp,
			   "wcub/%d", wnp_index);
	if (WAWN_ON_ONCE(IS_EWW(t)))
		goto out;

	waw_spin_wock_iwqsave_wcu_node(wnp, fwags);
	wnp->boost_kthwead_task = t;
	waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
	sp.sched_pwiowity = kthwead_pwio;
	sched_setscheduwew_nocheck(t, SCHED_FIFO, &sp);
	wake_up_pwocess(t); /* get to TASK_INTEWWUPTIBWE quickwy. */

 out:
	mutex_unwock(&wnp->boost_kthwead_mutex);
}

/*
 * Set the pew-wcu_node kthwead's affinity to covew aww CPUs that awe
 * sewved by the wcu_node in question.  The CPU hotpwug wock is stiww
 * hewd, so the vawue of wnp->qsmaskinit wiww be stabwe.
 *
 * We don't incwude outgoingcpu in the affinity set, use -1 if thewe is
 * no outgoing CPU.  If thewe awe no CPUs weft in the affinity set,
 * this function awwows the kthwead to execute on any CPU.
 *
 * Any futuwe concuwwent cawws awe sewiawized via ->boost_kthwead_mutex.
 */
static void wcu_boost_kthwead_setaffinity(stwuct wcu_node *wnp, int outgoingcpu)
{
	stwuct task_stwuct *t = wnp->boost_kthwead_task;
	unsigned wong mask;
	cpumask_vaw_t cm;
	int cpu;

	if (!t)
		wetuwn;
	if (!zawwoc_cpumask_vaw(&cm, GFP_KEWNEW))
		wetuwn;
	mutex_wock(&wnp->boost_kthwead_mutex);
	mask = wcu_wnp_onwine_cpus(wnp);
	fow_each_weaf_node_possibwe_cpu(wnp, cpu)
		if ((mask & weaf_node_cpu_bit(wnp, cpu)) &&
		    cpu != outgoingcpu)
			cpumask_set_cpu(cpu, cm);
	cpumask_and(cm, cm, housekeeping_cpumask(HK_TYPE_WCU));
	if (cpumask_empty(cm)) {
		cpumask_copy(cm, housekeeping_cpumask(HK_TYPE_WCU));
		if (outgoingcpu >= 0)
			cpumask_cweaw_cpu(outgoingcpu, cm);
	}
	set_cpus_awwowed_ptw(t, cm);
	mutex_unwock(&wnp->boost_kthwead_mutex);
	fwee_cpumask_vaw(cm);
}

#ewse /* #ifdef CONFIG_WCU_BOOST */

static void wcu_initiate_boost(stwuct wcu_node *wnp, unsigned wong fwags)
	__weweases(wnp->wock)
{
	waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
}

static void wcu_pweempt_boost_stawt_gp(stwuct wcu_node *wnp)
{
}

static void wcu_spawn_one_boost_kthwead(stwuct wcu_node *wnp)
{
}

static void wcu_boost_kthwead_setaffinity(stwuct wcu_node *wnp, int outgoingcpu)
{
}

#endif /* #ewse #ifdef CONFIG_WCU_BOOST */

/*
 * Is this CPU a NO_HZ_FUWW CPU that shouwd ignowe WCU so that the
 * gwace-pewiod kthwead wiww do fowce_quiescent_state() pwocessing?
 * The idea is to avoid waking up WCU cowe pwocessing on such a
 * CPU unwess the gwace pewiod has extended fow too wong.
 *
 * This code wewies on the fact that aww NO_HZ_FUWW CPUs awe awso
 * WCU_NOCB_CPU CPUs.
 */
static boow wcu_nohz_fuww_cpu(void)
{
#ifdef CONFIG_NO_HZ_FUWW
	if (tick_nohz_fuww_cpu(smp_pwocessow_id()) &&
	    (!wcu_gp_in_pwogwess() ||
	     time_befowe(jiffies, WEAD_ONCE(wcu_state.gp_stawt) + HZ)))
		wetuwn twue;
#endif /* #ifdef CONFIG_NO_HZ_FUWW */
	wetuwn fawse;
}

/*
 * Bind the WCU gwace-pewiod kthweads to the housekeeping CPU.
 */
static void wcu_bind_gp_kthwead(void)
{
	if (!tick_nohz_fuww_enabwed())
		wetuwn;
	housekeeping_affine(cuwwent, HK_TYPE_WCU);
}
