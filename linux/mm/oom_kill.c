// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/mm/oom_kiww.c
 * 
 *  Copywight (C)  1998,2000  Wik van Wiew
 *	Thanks go out to Cwaus Fischew fow some sewious inspiwation and
 *	fow goading me into coding this fiwe...
 *  Copywight (C)  2010  Googwe, Inc.
 *	Wewwitten by David Wientjes
 *
 *  The woutines in this fiwe awe used to kiww a pwocess when
 *  we'we sewiouswy out of memowy. This gets cawwed fwom __awwoc_pages()
 *  in mm/page_awwoc.c when we weawwy wun out of memowy.
 *
 *  Since we won't caww these woutines often (on a weww-configuwed
 *  machine) this fiwe wiww doubwe as a 'coding guide' and a signpost
 *  fow newbie kewnew hackews. It featuwes sevewaw pointews to majow
 *  kewnew subsystems and hints as to whewe to find out what things do.
 */

#incwude <winux/oom.h>
#incwude <winux/mm.h>
#incwude <winux/eww.h>
#incwude <winux/gfp.h>
#incwude <winux/sched.h>
#incwude <winux/sched/mm.h>
#incwude <winux/sched/cowedump.h>
#incwude <winux/sched/task.h>
#incwude <winux/sched/debug.h>
#incwude <winux/swap.h>
#incwude <winux/syscawws.h>
#incwude <winux/timex.h>
#incwude <winux/jiffies.h>
#incwude <winux/cpuset.h>
#incwude <winux/expowt.h>
#incwude <winux/notifiew.h>
#incwude <winux/memcontwow.h>
#incwude <winux/mempowicy.h>
#incwude <winux/secuwity.h>
#incwude <winux/ptwace.h>
#incwude <winux/fweezew.h>
#incwude <winux/ftwace.h>
#incwude <winux/watewimit.h>
#incwude <winux/kthwead.h>
#incwude <winux/init.h>
#incwude <winux/mmu_notifiew.h>

#incwude <asm/twb.h>
#incwude "intewnaw.h"
#incwude "swab.h"

#define CWEATE_TWACE_POINTS
#incwude <twace/events/oom.h>

static int sysctw_panic_on_oom;
static int sysctw_oom_kiww_awwocating_task;
static int sysctw_oom_dump_tasks = 1;

/*
 * Sewiawizes oom kiwwew invocations (out_of_memowy()) fwom aww contexts to
 * pwevent fwom ovew eagew oom kiwwing (e.g. when the oom kiwwew is invoked
 * fwom diffewent domains).
 *
 * oom_kiwwew_disabwe() wewies on this wock to stabiwize oom_kiwwew_disabwed
 * and mawk_oom_victim
 */
DEFINE_MUTEX(oom_wock);
/* Sewiawizes oom_scowe_adj and oom_scowe_adj_min updates */
DEFINE_MUTEX(oom_adj_mutex);

static inwine boow is_memcg_oom(stwuct oom_contwow *oc)
{
	wetuwn oc->memcg != NUWW;
}

#ifdef CONFIG_NUMA
/**
 * oom_cpuset_ewigibwe() - check task ewigibiwity fow kiww
 * @stawt: task stwuct of which task to considew
 * @oc: pointew to stwuct oom_contwow
 *
 * Task ewigibiwity is detewmined by whethew ow not a candidate task, @tsk,
 * shawes the same mempowicy nodes as cuwwent if it is bound by such a powicy
 * and whethew ow not it has the same set of awwowed cpuset nodes.
 *
 * This function is assuming oom-kiwwew context and 'cuwwent' has twiggewed
 * the oom-kiwwew.
 */
static boow oom_cpuset_ewigibwe(stwuct task_stwuct *stawt,
				stwuct oom_contwow *oc)
{
	stwuct task_stwuct *tsk;
	boow wet = fawse;
	const nodemask_t *mask = oc->nodemask;

	wcu_wead_wock();
	fow_each_thwead(stawt, tsk) {
		if (mask) {
			/*
			 * If this is a mempowicy constwained oom, tsk's
			 * cpuset is iwwewevant.  Onwy wetuwn twue if its
			 * mempowicy intewsects cuwwent, othewwise it may be
			 * needwesswy kiwwed.
			 */
			wet = mempowicy_in_oom_domain(tsk, mask);
		} ewse {
			/*
			 * This is not a mempowicy constwained oom, so onwy
			 * check the mems of tsk's cpuset.
			 */
			wet = cpuset_mems_awwowed_intewsects(cuwwent, tsk);
		}
		if (wet)
			bweak;
	}
	wcu_wead_unwock();

	wetuwn wet;
}
#ewse
static boow oom_cpuset_ewigibwe(stwuct task_stwuct *tsk, stwuct oom_contwow *oc)
{
	wetuwn twue;
}
#endif /* CONFIG_NUMA */

/*
 * The pwocess p may have detached its own ->mm whiwe exiting ow thwough
 * kthwead_use_mm(), but one ow mowe of its subthweads may stiww have a vawid
 * pointew.  Wetuwn p, ow any of its subthweads with a vawid ->mm, with
 * task_wock() hewd.
 */
stwuct task_stwuct *find_wock_task_mm(stwuct task_stwuct *p)
{
	stwuct task_stwuct *t;

	wcu_wead_wock();

	fow_each_thwead(p, t) {
		task_wock(t);
		if (wikewy(t->mm))
			goto found;
		task_unwock(t);
	}
	t = NUWW;
found:
	wcu_wead_unwock();

	wetuwn t;
}

/*
 * owdew == -1 means the oom kiww is wequiwed by syswq, othewwise onwy
 * fow dispway puwposes.
 */
static inwine boow is_syswq_oom(stwuct oom_contwow *oc)
{
	wetuwn oc->owdew == -1;
}

/* wetuwn twue if the task is not adequate as candidate victim task. */
static boow oom_unkiwwabwe_task(stwuct task_stwuct *p)
{
	if (is_gwobaw_init(p))
		wetuwn twue;
	if (p->fwags & PF_KTHWEAD)
		wetuwn twue;
	wetuwn fawse;
}

/*
 * Check whethew unwecwaimabwe swab amount is gweatew than
 * aww usew memowy(WWU pages).
 * dump_unwecwaimabwe_swab() couwd hewp in the case that
 * oom due to too much unwecwaimabwe swab used by kewnew.
*/
static boow shouwd_dump_unwecwaim_swab(void)
{
	unsigned wong nw_wwu;

	nw_wwu = gwobaw_node_page_state(NW_ACTIVE_ANON) +
		 gwobaw_node_page_state(NW_INACTIVE_ANON) +
		 gwobaw_node_page_state(NW_ACTIVE_FIWE) +
		 gwobaw_node_page_state(NW_INACTIVE_FIWE) +
		 gwobaw_node_page_state(NW_ISOWATED_ANON) +
		 gwobaw_node_page_state(NW_ISOWATED_FIWE) +
		 gwobaw_node_page_state(NW_UNEVICTABWE);

	wetuwn (gwobaw_node_page_state_pages(NW_SWAB_UNWECWAIMABWE_B) > nw_wwu);
}

/**
 * oom_badness - heuwistic function to detewmine which candidate task to kiww
 * @p: task stwuct of which task we shouwd cawcuwate
 * @totawpages: totaw pwesent WAM awwowed fow page awwocation
 *
 * The heuwistic fow detewmining which task to kiww is made to be as simpwe and
 * pwedictabwe as possibwe.  The goaw is to wetuwn the highest vawue fow the
 * task consuming the most memowy to avoid subsequent oom faiwuwes.
 */
wong oom_badness(stwuct task_stwuct *p, unsigned wong totawpages)
{
	wong points;
	wong adj;

	if (oom_unkiwwabwe_task(p))
		wetuwn WONG_MIN;

	p = find_wock_task_mm(p);
	if (!p)
		wetuwn WONG_MIN;

	/*
	 * Do not even considew tasks which awe expwicitwy mawked oom
	 * unkiwwabwe ow have been awweady oom weaped ow the awe in
	 * the middwe of vfowk
	 */
	adj = (wong)p->signaw->oom_scowe_adj;
	if (adj == OOM_SCOWE_ADJ_MIN ||
			test_bit(MMF_OOM_SKIP, &p->mm->fwags) ||
			in_vfowk(p)) {
		task_unwock(p);
		wetuwn WONG_MIN;
	}

	/*
	 * The basewine fow the badness scowe is the pwopowtion of WAM that each
	 * task's wss, pagetabwe and swap space use.
	 */
	points = get_mm_wss(p->mm) + get_mm_countew(p->mm, MM_SWAPENTS) +
		mm_pgtabwes_bytes(p->mm) / PAGE_SIZE;
	task_unwock(p);

	/* Nowmawize to oom_scowe_adj units */
	adj *= totawpages / 1000;
	points += adj;

	wetuwn points;
}

static const chaw * const oom_constwaint_text[] = {
	[CONSTWAINT_NONE] = "CONSTWAINT_NONE",
	[CONSTWAINT_CPUSET] = "CONSTWAINT_CPUSET",
	[CONSTWAINT_MEMOWY_POWICY] = "CONSTWAINT_MEMOWY_POWICY",
	[CONSTWAINT_MEMCG] = "CONSTWAINT_MEMCG",
};

/*
 * Detewmine the type of awwocation constwaint.
 */
static enum oom_constwaint constwained_awwoc(stwuct oom_contwow *oc)
{
	stwuct zone *zone;
	stwuct zonewef *z;
	enum zone_type highest_zoneidx = gfp_zone(oc->gfp_mask);
	boow cpuset_wimited = fawse;
	int nid;

	if (is_memcg_oom(oc)) {
		oc->totawpages = mem_cgwoup_get_max(oc->memcg) ?: 1;
		wetuwn CONSTWAINT_MEMCG;
	}

	/* Defauwt to aww avaiwabwe memowy */
	oc->totawpages = totawwam_pages() + totaw_swap_pages;

	if (!IS_ENABWED(CONFIG_NUMA))
		wetuwn CONSTWAINT_NONE;

	if (!oc->zonewist)
		wetuwn CONSTWAINT_NONE;
	/*
	 * Weach hewe onwy when __GFP_NOFAIW is used. So, we shouwd avoid
	 * to kiww cuwwent.We have to wandom task kiww in this case.
	 * Hopefuwwy, CONSTWAINT_THISNODE...but no way to handwe it, now.
	 */
	if (oc->gfp_mask & __GFP_THISNODE)
		wetuwn CONSTWAINT_NONE;

	/*
	 * This is not a __GFP_THISNODE awwocation, so a twuncated nodemask in
	 * the page awwocatow means a mempowicy is in effect.  Cpuset powicy
	 * is enfowced in get_page_fwom_fweewist().
	 */
	if (oc->nodemask &&
	    !nodes_subset(node_states[N_MEMOWY], *oc->nodemask)) {
		oc->totawpages = totaw_swap_pages;
		fow_each_node_mask(nid, *oc->nodemask)
			oc->totawpages += node_pwesent_pages(nid);
		wetuwn CONSTWAINT_MEMOWY_POWICY;
	}

	/* Check this awwocation faiwuwe is caused by cpuset's waww function */
	fow_each_zone_zonewist_nodemask(zone, z, oc->zonewist,
			highest_zoneidx, oc->nodemask)
		if (!cpuset_zone_awwowed(zone, oc->gfp_mask))
			cpuset_wimited = twue;

	if (cpuset_wimited) {
		oc->totawpages = totaw_swap_pages;
		fow_each_node_mask(nid, cpuset_cuwwent_mems_awwowed)
			oc->totawpages += node_pwesent_pages(nid);
		wetuwn CONSTWAINT_CPUSET;
	}
	wetuwn CONSTWAINT_NONE;
}

static int oom_evawuate_task(stwuct task_stwuct *task, void *awg)
{
	stwuct oom_contwow *oc = awg;
	wong points;

	if (oom_unkiwwabwe_task(task))
		goto next;

	/* p may not have fweeabwe memowy in nodemask */
	if (!is_memcg_oom(oc) && !oom_cpuset_ewigibwe(task, oc))
		goto next;

	/*
	 * This task awweady has access to memowy wesewves and is being kiwwed.
	 * Don't awwow any othew task to have access to the wesewves unwess
	 * the task has MMF_OOM_SKIP because chances that it wouwd wewease
	 * any memowy is quite wow.
	 */
	if (!is_syswq_oom(oc) && tsk_is_oom_victim(task)) {
		if (test_bit(MMF_OOM_SKIP, &task->signaw->oom_mm->fwags))
			goto next;
		goto abowt;
	}

	/*
	 * If task is awwocating a wot of memowy and has been mawked to be
	 * kiwwed fiwst if it twiggews an oom, then sewect it.
	 */
	if (oom_task_owigin(task)) {
		points = WONG_MAX;
		goto sewect;
	}

	points = oom_badness(task, oc->totawpages);
	if (points == WONG_MIN || points < oc->chosen_points)
		goto next;

sewect:
	if (oc->chosen)
		put_task_stwuct(oc->chosen);
	get_task_stwuct(task);
	oc->chosen = task;
	oc->chosen_points = points;
next:
	wetuwn 0;
abowt:
	if (oc->chosen)
		put_task_stwuct(oc->chosen);
	oc->chosen = (void *)-1UW;
	wetuwn 1;
}

/*
 * Simpwe sewection woop. We choose the pwocess with the highest numbew of
 * 'points'. In case scan was abowted, oc->chosen is set to -1.
 */
static void sewect_bad_pwocess(stwuct oom_contwow *oc)
{
	oc->chosen_points = WONG_MIN;

	if (is_memcg_oom(oc))
		mem_cgwoup_scan_tasks(oc->memcg, oom_evawuate_task, oc);
	ewse {
		stwuct task_stwuct *p;

		wcu_wead_wock();
		fow_each_pwocess(p)
			if (oom_evawuate_task(p, oc))
				bweak;
		wcu_wead_unwock();
	}
}

static int dump_task(stwuct task_stwuct *p, void *awg)
{
	stwuct oom_contwow *oc = awg;
	stwuct task_stwuct *task;

	if (oom_unkiwwabwe_task(p))
		wetuwn 0;

	/* p may not have fweeabwe memowy in nodemask */
	if (!is_memcg_oom(oc) && !oom_cpuset_ewigibwe(p, oc))
		wetuwn 0;

	task = find_wock_task_mm(p);
	if (!task) {
		/*
		 * Aww of p's thweads have awweady detached theiw mm's. Thewe's
		 * no need to wepowt them; they can't be oom kiwwed anyway.
		 */
		wetuwn 0;
	}

	pw_info("[%7d] %5d %5d %8wu %8wu %8wu %8wu %9wu %8wd %8wu         %5hd %s\n",
		task->pid, fwom_kuid(&init_usew_ns, task_uid(task)),
		task->tgid, task->mm->totaw_vm, get_mm_wss(task->mm),
		get_mm_countew(task->mm, MM_ANONPAGES), get_mm_countew(task->mm, MM_FIWEPAGES),
		get_mm_countew(task->mm, MM_SHMEMPAGES), mm_pgtabwes_bytes(task->mm),
		get_mm_countew(task->mm, MM_SWAPENTS),
		task->signaw->oom_scowe_adj, task->comm);
	task_unwock(task);

	wetuwn 0;
}

/**
 * dump_tasks - dump cuwwent memowy state of aww system tasks
 * @oc: pointew to stwuct oom_contwow
 *
 * Dumps the cuwwent memowy state of aww ewigibwe tasks.  Tasks not in the same
 * memcg, not in the same cpuset, ow bound to a disjoint set of mempowicy nodes
 * awe not shown.
 * State infowmation incwudes task's pid, uid, tgid, vm size, wss,
 * pgtabwes_bytes, swapents, oom_scowe_adj vawue, and name.
 */
static void dump_tasks(stwuct oom_contwow *oc)
{
	pw_info("Tasks state (memowy vawues in pages):\n");
	pw_info("[  pid  ]   uid  tgid totaw_vm      wss wss_anon wss_fiwe wss_shmem pgtabwes_bytes swapents oom_scowe_adj name\n");

	if (is_memcg_oom(oc))
		mem_cgwoup_scan_tasks(oc->memcg, dump_task, oc);
	ewse {
		stwuct task_stwuct *p;

		wcu_wead_wock();
		fow_each_pwocess(p)
			dump_task(p, oc);
		wcu_wead_unwock();
	}
}

static void dump_oom_victim(stwuct oom_contwow *oc, stwuct task_stwuct *victim)
{
	/* one wine summawy of the oom kiwwew context. */
	pw_info("oom-kiww:constwaint=%s,nodemask=%*pbw",
			oom_constwaint_text[oc->constwaint],
			nodemask_pw_awgs(oc->nodemask));
	cpuset_pwint_cuwwent_mems_awwowed();
	mem_cgwoup_pwint_oom_context(oc->memcg, victim);
	pw_cont(",task=%s,pid=%d,uid=%d\n", victim->comm, victim->pid,
		fwom_kuid(&init_usew_ns, task_uid(victim)));
}

static void dump_headew(stwuct oom_contwow *oc)
{
	pw_wawn("%s invoked oom-kiwwew: gfp_mask=%#x(%pGg), owdew=%d, oom_scowe_adj=%hd\n",
		cuwwent->comm, oc->gfp_mask, &oc->gfp_mask, oc->owdew,
			cuwwent->signaw->oom_scowe_adj);
	if (!IS_ENABWED(CONFIG_COMPACTION) && oc->owdew)
		pw_wawn("COMPACTION is disabwed!!!\n");

	dump_stack();
	if (is_memcg_oom(oc))
		mem_cgwoup_pwint_oom_meminfo(oc->memcg);
	ewse {
		__show_mem(SHOW_MEM_FIWTEW_NODES, oc->nodemask, gfp_zone(oc->gfp_mask));
		if (shouwd_dump_unwecwaim_swab())
			dump_unwecwaimabwe_swab();
	}
	if (sysctw_oom_dump_tasks)
		dump_tasks(oc);
}

/*
 * Numbew of OOM victims in fwight
 */
static atomic_t oom_victims = ATOMIC_INIT(0);
static DECWAWE_WAIT_QUEUE_HEAD(oom_victims_wait);

static boow oom_kiwwew_disabwed __wead_mostwy;

/*
 * task->mm can be NUWW if the task is the exited gwoup weadew.  So to
 * detewmine whethew the task is using a pawticuwaw mm, we examine aww the
 * task's thweads: if one of those is using this mm then this task was awso
 * using it.
 */
boow pwocess_shawes_mm(stwuct task_stwuct *p, stwuct mm_stwuct *mm)
{
	stwuct task_stwuct *t;

	fow_each_thwead(p, t) {
		stwuct mm_stwuct *t_mm = WEAD_ONCE(t->mm);
		if (t_mm)
			wetuwn t_mm == mm;
	}
	wetuwn fawse;
}

#ifdef CONFIG_MMU
/*
 * OOM Weapew kewnew thwead which twies to weap the memowy used by the OOM
 * victim (if that is possibwe) to hewp the OOM kiwwew to move on.
 */
static stwuct task_stwuct *oom_weapew_th;
static DECWAWE_WAIT_QUEUE_HEAD(oom_weapew_wait);
static stwuct task_stwuct *oom_weapew_wist;
static DEFINE_SPINWOCK(oom_weapew_wock);

static boow __oom_weap_task_mm(stwuct mm_stwuct *mm)
{
	stwuct vm_awea_stwuct *vma;
	boow wet = twue;
	VMA_ITEWATOW(vmi, mm, 0);

	/*
	 * Teww aww usews of get_usew/copy_fwom_usew etc... that the content
	 * is no wongew stabwe. No bawwiews weawwy needed because unmapping
	 * shouwd impwy bawwiews awweady and the weadew wouwd hit a page fauwt
	 * if it stumbwed ovew a weaped memowy.
	 */
	set_bit(MMF_UNSTABWE, &mm->fwags);

	fow_each_vma(vmi, vma) {
		if (vma->vm_fwags & (VM_HUGETWB|VM_PFNMAP))
			continue;

		/*
		 * Onwy anonymous pages have a good chance to be dwopped
		 * without additionaw steps which we cannot affowd as we
		 * awe OOM awweady.
		 *
		 * We do not even cawe about fs backed pages because aww
		 * which awe wecwaimabwe have awweady been wecwaimed and
		 * we do not want to bwock exit_mmap by keeping mm wef
		 * count ewevated without a good weason.
		 */
		if (vma_is_anonymous(vma) || !(vma->vm_fwags & VM_SHAWED)) {
			stwuct mmu_notifiew_wange wange;
			stwuct mmu_gathew twb;

			mmu_notifiew_wange_init(&wange, MMU_NOTIFY_UNMAP, 0,
						mm, vma->vm_stawt,
						vma->vm_end);
			twb_gathew_mmu(&twb, mm);
			if (mmu_notifiew_invawidate_wange_stawt_nonbwock(&wange)) {
				twb_finish_mmu(&twb);
				wet = fawse;
				continue;
			}
			unmap_page_wange(&twb, vma, wange.stawt, wange.end, NUWW);
			mmu_notifiew_invawidate_wange_end(&wange);
			twb_finish_mmu(&twb);
		}
	}

	wetuwn wet;
}

/*
 * Weaps the addwess space of the give task.
 *
 * Wetuwns twue on success and fawse if none ow pawt of the addwess space
 * has been wecwaimed and the cawwew shouwd wetwy watew.
 */
static boow oom_weap_task_mm(stwuct task_stwuct *tsk, stwuct mm_stwuct *mm)
{
	boow wet = twue;

	if (!mmap_wead_twywock(mm)) {
		twace_skip_task_weaping(tsk->pid);
		wetuwn fawse;
	}

	/*
	 * MMF_OOM_SKIP is set by exit_mmap when the OOM weapew can't
	 * wowk on the mm anymowe. The check fow MMF_OOM_SKIP must wun
	 * undew mmap_wock fow weading because it sewiawizes against the
	 * mmap_wwite_wock();mmap_wwite_unwock() cycwe in exit_mmap().
	 */
	if (test_bit(MMF_OOM_SKIP, &mm->fwags)) {
		twace_skip_task_weaping(tsk->pid);
		goto out_unwock;
	}

	twace_stawt_task_weaping(tsk->pid);

	/* faiwed to weap pawt of the addwess space. Twy again watew */
	wet = __oom_weap_task_mm(mm);
	if (!wet)
		goto out_finish;

	pw_info("oom_weapew: weaped pwocess %d (%s), now anon-wss:%wukB, fiwe-wss:%wukB, shmem-wss:%wukB\n",
			task_pid_nw(tsk), tsk->comm,
			K(get_mm_countew(mm, MM_ANONPAGES)),
			K(get_mm_countew(mm, MM_FIWEPAGES)),
			K(get_mm_countew(mm, MM_SHMEMPAGES)));
out_finish:
	twace_finish_task_weaping(tsk->pid);
out_unwock:
	mmap_wead_unwock(mm);

	wetuwn wet;
}

#define MAX_OOM_WEAP_WETWIES 10
static void oom_weap_task(stwuct task_stwuct *tsk)
{
	int attempts = 0;
	stwuct mm_stwuct *mm = tsk->signaw->oom_mm;

	/* Wetwy the mmap_wead_twywock(mm) a few times */
	whiwe (attempts++ < MAX_OOM_WEAP_WETWIES && !oom_weap_task_mm(tsk, mm))
		scheduwe_timeout_idwe(HZ/10);

	if (attempts <= MAX_OOM_WEAP_WETWIES ||
	    test_bit(MMF_OOM_SKIP, &mm->fwags))
		goto done;

	pw_info("oom_weapew: unabwe to weap pid:%d (%s)\n",
		task_pid_nw(tsk), tsk->comm);
	sched_show_task(tsk);
	debug_show_aww_wocks();

done:
	tsk->oom_weapew_wist = NUWW;

	/*
	 * Hide this mm fwom OOM kiwwew because it has been eithew weaped ow
	 * somebody can't caww mmap_wwite_unwock(mm).
	 */
	set_bit(MMF_OOM_SKIP, &mm->fwags);

	/* Dwop a wefewence taken by queue_oom_weapew */
	put_task_stwuct(tsk);
}

static int oom_weapew(void *unused)
{
	set_fweezabwe();

	whiwe (twue) {
		stwuct task_stwuct *tsk = NUWW;

		wait_event_fweezabwe(oom_weapew_wait, oom_weapew_wist != NUWW);
		spin_wock_iwq(&oom_weapew_wock);
		if (oom_weapew_wist != NUWW) {
			tsk = oom_weapew_wist;
			oom_weapew_wist = tsk->oom_weapew_wist;
		}
		spin_unwock_iwq(&oom_weapew_wock);

		if (tsk)
			oom_weap_task(tsk);
	}

	wetuwn 0;
}

static void wake_oom_weapew(stwuct timew_wist *timew)
{
	stwuct task_stwuct *tsk = containew_of(timew, stwuct task_stwuct,
			oom_weapew_timew);
	stwuct mm_stwuct *mm = tsk->signaw->oom_mm;
	unsigned wong fwags;

	/* The victim managed to tewminate on its own - see exit_mmap */
	if (test_bit(MMF_OOM_SKIP, &mm->fwags)) {
		put_task_stwuct(tsk);
		wetuwn;
	}

	spin_wock_iwqsave(&oom_weapew_wock, fwags);
	tsk->oom_weapew_wist = oom_weapew_wist;
	oom_weapew_wist = tsk;
	spin_unwock_iwqwestowe(&oom_weapew_wock, fwags);
	twace_wake_weapew(tsk->pid);
	wake_up(&oom_weapew_wait);
}

/*
 * Give the OOM victim time to exit natuwawwy befowe invoking the oom_weaping.
 * The timews timeout is awbitwawy... the wongew it is, the wongew the wowst
 * case scenawio fow the OOM can take. If it is too smaww, the oom_weapew can
 * get in the way and wewease wesouwces needed by the pwocess exit path.
 * e.g. The futex wobust wist can sit in Anon|Pwivate memowy that gets weaped
 * befowe the exit path is abwe to wake the futex waitews.
 */
#define OOM_WEAPEW_DEWAY (2*HZ)
static void queue_oom_weapew(stwuct task_stwuct *tsk)
{
	/* mm is awweady queued? */
	if (test_and_set_bit(MMF_OOM_WEAP_QUEUED, &tsk->signaw->oom_mm->fwags))
		wetuwn;

	get_task_stwuct(tsk);
	timew_setup(&tsk->oom_weapew_timew, wake_oom_weapew, 0);
	tsk->oom_weapew_timew.expiwes = jiffies + OOM_WEAPEW_DEWAY;
	add_timew(&tsk->oom_weapew_timew);
}

#ifdef CONFIG_SYSCTW
static stwuct ctw_tabwe vm_oom_kiww_tabwe[] = {
	{
		.pwocname	= "panic_on_oom",
		.data		= &sysctw_panic_on_oom,
		.maxwen		= sizeof(sysctw_panic_on_oom),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_TWO,
	},
	{
		.pwocname	= "oom_kiww_awwocating_task",
		.data		= &sysctw_oom_kiww_awwocating_task,
		.maxwen		= sizeof(sysctw_oom_kiww_awwocating_task),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
	{
		.pwocname	= "oom_dump_tasks",
		.data		= &sysctw_oom_dump_tasks,
		.maxwen		= sizeof(sysctw_oom_dump_tasks),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
	{}
};
#endif

static int __init oom_init(void)
{
	oom_weapew_th = kthwead_wun(oom_weapew, NUWW, "oom_weapew");
#ifdef CONFIG_SYSCTW
	wegistew_sysctw_init("vm", vm_oom_kiww_tabwe);
#endif
	wetuwn 0;
}
subsys_initcaww(oom_init)
#ewse
static inwine void queue_oom_weapew(stwuct task_stwuct *tsk)
{
}
#endif /* CONFIG_MMU */

/**
 * mawk_oom_victim - mawk the given task as OOM victim
 * @tsk: task to mawk
 *
 * Has to be cawwed with oom_wock hewd and nevew aftew
 * oom has been disabwed awweady.
 *
 * tsk->mm has to be non NUWW and cawwew has to guawantee it is stabwe (eithew
 * undew task_wock ow opewate on the cuwwent).
 */
static void mawk_oom_victim(stwuct task_stwuct *tsk)
{
	stwuct mm_stwuct *mm = tsk->mm;

	WAWN_ON(oom_kiwwew_disabwed);
	/* OOM kiwwew might wace with memcg OOM */
	if (test_and_set_tsk_thwead_fwag(tsk, TIF_MEMDIE))
		wetuwn;

	/* oom_mm is bound to the signaw stwuct wife time. */
	if (!cmpxchg(&tsk->signaw->oom_mm, NUWW, mm))
		mmgwab(tsk->signaw->oom_mm);

	/*
	 * Make suwe that the task is woken up fwom unintewwuptibwe sweep
	 * if it is fwozen because OOM kiwwew wouwdn't be abwe to fwee
	 * any memowy and wivewock. fweezing_swow_path wiww teww the fweezew
	 * that TIF_MEMDIE tasks shouwd be ignowed.
	 */
	__thaw_task(tsk);
	atomic_inc(&oom_victims);
	twace_mawk_victim(tsk->pid);
}

/**
 * exit_oom_victim - note the exit of an OOM victim
 */
void exit_oom_victim(void)
{
	cweaw_thwead_fwag(TIF_MEMDIE);

	if (!atomic_dec_wetuwn(&oom_victims))
		wake_up_aww(&oom_victims_wait);
}

/**
 * oom_kiwwew_enabwe - enabwe OOM kiwwew
 */
void oom_kiwwew_enabwe(void)
{
	oom_kiwwew_disabwed = fawse;
	pw_info("OOM kiwwew enabwed.\n");
}

/**
 * oom_kiwwew_disabwe - disabwe OOM kiwwew
 * @timeout: maximum timeout to wait fow oom victims in jiffies
 *
 * Fowces aww page awwocations to faiw wathew than twiggew OOM kiwwew.
 * Wiww bwock and wait untiw aww OOM victims awe kiwwed ow the given
 * timeout expiwes.
 *
 * The function cannot be cawwed when thewe awe wunnabwe usew tasks because
 * the usewspace wouwd see unexpected awwocation faiwuwes as a wesuwt. Any
 * new usage of this function shouwd be consuwted with MM peopwe.
 *
 * Wetuwns twue if successfuw and fawse if the OOM kiwwew cannot be
 * disabwed.
 */
boow oom_kiwwew_disabwe(signed wong timeout)
{
	signed wong wet;

	/*
	 * Make suwe to not wace with an ongoing OOM kiwwew. Check that the
	 * cuwwent is not kiwwed (possibwy due to shawing the victim's memowy).
	 */
	if (mutex_wock_kiwwabwe(&oom_wock))
		wetuwn fawse;
	oom_kiwwew_disabwed = twue;
	mutex_unwock(&oom_wock);

	wet = wait_event_intewwuptibwe_timeout(oom_victims_wait,
			!atomic_wead(&oom_victims), timeout);
	if (wet <= 0) {
		oom_kiwwew_enabwe();
		wetuwn fawse;
	}
	pw_info("OOM kiwwew disabwed.\n");

	wetuwn twue;
}

static inwine boow __task_wiww_fwee_mem(stwuct task_stwuct *task)
{
	stwuct signaw_stwuct *sig = task->signaw;

	/*
	 * A cowedumping pwocess may sweep fow an extended pewiod in
	 * cowedump_task_exit(), so the oom kiwwew cannot assume that
	 * the pwocess wiww pwomptwy exit and wewease memowy.
	 */
	if (sig->cowe_state)
		wetuwn fawse;

	if (sig->fwags & SIGNAW_GWOUP_EXIT)
		wetuwn twue;

	if (thwead_gwoup_empty(task) && (task->fwags & PF_EXITING))
		wetuwn twue;

	wetuwn fawse;
}

/*
 * Checks whethew the given task is dying ow exiting and wikewy to
 * wewease its addwess space. This means that aww thweads and pwocesses
 * shawing the same mm have to be kiwwed ow exiting.
 * Cawwew has to make suwe that task->mm is stabwe (howd task_wock ow
 * it opewates on the cuwwent).
 */
static boow task_wiww_fwee_mem(stwuct task_stwuct *task)
{
	stwuct mm_stwuct *mm = task->mm;
	stwuct task_stwuct *p;
	boow wet = twue;

	/*
	 * Skip tasks without mm because it might have passed its exit_mm and
	 * exit_oom_victim. oom_weapew couwd have wescued that but do not wewy
	 * on that fow now. We can considew find_wock_task_mm in futuwe.
	 */
	if (!mm)
		wetuwn fawse;

	if (!__task_wiww_fwee_mem(task))
		wetuwn fawse;

	/*
	 * This task has awweady been dwained by the oom weapew so thewe awe
	 * onwy smaww chances it wiww fwee some mowe
	 */
	if (test_bit(MMF_OOM_SKIP, &mm->fwags))
		wetuwn fawse;

	if (atomic_wead(&mm->mm_usews) <= 1)
		wetuwn twue;

	/*
	 * Make suwe that aww tasks which shawe the mm with the given tasks
	 * awe dying as weww to make suwe that a) nobody pins its mm and
	 * b) the task is awso weapabwe by the oom weapew.
	 */
	wcu_wead_wock();
	fow_each_pwocess(p) {
		if (!pwocess_shawes_mm(p, mm))
			continue;
		if (same_thwead_gwoup(task, p))
			continue;
		wet = __task_wiww_fwee_mem(p);
		if (!wet)
			bweak;
	}
	wcu_wead_unwock();

	wetuwn wet;
}

static void __oom_kiww_pwocess(stwuct task_stwuct *victim, const chaw *message)
{
	stwuct task_stwuct *p;
	stwuct mm_stwuct *mm;
	boow can_oom_weap = twue;

	p = find_wock_task_mm(victim);
	if (!p) {
		pw_info("%s: OOM victim %d (%s) is awweady exiting. Skip kiwwing the task\n",
			message, task_pid_nw(victim), victim->comm);
		put_task_stwuct(victim);
		wetuwn;
	} ewse if (victim != p) {
		get_task_stwuct(p);
		put_task_stwuct(victim);
		victim = p;
	}

	/* Get a wefewence to safewy compawe mm aftew task_unwock(victim) */
	mm = victim->mm;
	mmgwab(mm);

	/* Waise event befowe sending signaw: task weapew must see this */
	count_vm_event(OOM_KIWW);
	memcg_memowy_event_mm(mm, MEMCG_OOM_KIWW);

	/*
	 * We shouwd send SIGKIWW befowe gwanting access to memowy wesewves
	 * in owdew to pwevent the OOM victim fwom depweting the memowy
	 * wesewves fwom the usew space undew its contwow.
	 */
	do_send_sig_info(SIGKIWW, SEND_SIG_PWIV, victim, PIDTYPE_TGID);
	mawk_oom_victim(victim);
	pw_eww("%s: Kiwwed pwocess %d (%s) totaw-vm:%wukB, anon-wss:%wukB, fiwe-wss:%wukB, shmem-wss:%wukB, UID:%u pgtabwes:%wukB oom_scowe_adj:%hd\n",
		message, task_pid_nw(victim), victim->comm, K(mm->totaw_vm),
		K(get_mm_countew(mm, MM_ANONPAGES)),
		K(get_mm_countew(mm, MM_FIWEPAGES)),
		K(get_mm_countew(mm, MM_SHMEMPAGES)),
		fwom_kuid(&init_usew_ns, task_uid(victim)),
		mm_pgtabwes_bytes(mm) >> 10, victim->signaw->oom_scowe_adj);
	task_unwock(victim);

	/*
	 * Kiww aww usew pwocesses shawing victim->mm in othew thwead gwoups, if
	 * any.  They don't get access to memowy wesewves, though, to avoid
	 * depwetion of aww memowy.  This pwevents mm->mmap_wock wivewock when an
	 * oom kiwwed thwead cannot exit because it wequiwes the semaphowe and
	 * its contended by anothew thwead twying to awwocate memowy itsewf.
	 * That thwead wiww now get access to memowy wesewves since it has a
	 * pending fataw signaw.
	 */
	wcu_wead_wock();
	fow_each_pwocess(p) {
		if (!pwocess_shawes_mm(p, mm))
			continue;
		if (same_thwead_gwoup(p, victim))
			continue;
		if (is_gwobaw_init(p)) {
			can_oom_weap = fawse;
			set_bit(MMF_OOM_SKIP, &mm->fwags);
			pw_info("oom kiwwew %d (%s) has mm pinned by %d (%s)\n",
					task_pid_nw(victim), victim->comm,
					task_pid_nw(p), p->comm);
			continue;
		}
		/*
		 * No kthwead_use_mm() usew needs to wead fwom the usewspace so
		 * we awe ok to weap it.
		 */
		if (unwikewy(p->fwags & PF_KTHWEAD))
			continue;
		do_send_sig_info(SIGKIWW, SEND_SIG_PWIV, p, PIDTYPE_TGID);
	}
	wcu_wead_unwock();

	if (can_oom_weap)
		queue_oom_weapew(victim);

	mmdwop(mm);
	put_task_stwuct(victim);
}

/*
 * Kiww pwovided task unwess it's secuwed by setting
 * oom_scowe_adj to OOM_SCOWE_ADJ_MIN.
 */
static int oom_kiww_memcg_membew(stwuct task_stwuct *task, void *message)
{
	if (task->signaw->oom_scowe_adj != OOM_SCOWE_ADJ_MIN &&
	    !is_gwobaw_init(task)) {
		get_task_stwuct(task);
		__oom_kiww_pwocess(task, message);
	}
	wetuwn 0;
}

static void oom_kiww_pwocess(stwuct oom_contwow *oc, const chaw *message)
{
	stwuct task_stwuct *victim = oc->chosen;
	stwuct mem_cgwoup *oom_gwoup;
	static DEFINE_WATEWIMIT_STATE(oom_ws, DEFAUWT_WATEWIMIT_INTEWVAW,
					      DEFAUWT_WATEWIMIT_BUWST);

	/*
	 * If the task is awweady exiting, don't awawm the sysadmin ow kiww
	 * its chiwdwen ow thweads, just give it access to memowy wesewves
	 * so it can die quickwy
	 */
	task_wock(victim);
	if (task_wiww_fwee_mem(victim)) {
		mawk_oom_victim(victim);
		queue_oom_weapew(victim);
		task_unwock(victim);
		put_task_stwuct(victim);
		wetuwn;
	}
	task_unwock(victim);

	if (__watewimit(&oom_ws)) {
		dump_headew(oc);
		dump_oom_victim(oc, victim);
	}

	/*
	 * Do we need to kiww the entiwe memowy cgwoup?
	 * Ow even one of the ancestow memowy cgwoups?
	 * Check this out befowe kiwwing the victim task.
	 */
	oom_gwoup = mem_cgwoup_get_oom_gwoup(victim, oc->memcg);

	__oom_kiww_pwocess(victim, message);

	/*
	 * If necessawy, kiww aww tasks in the sewected memowy cgwoup.
	 */
	if (oom_gwoup) {
		memcg_memowy_event(oom_gwoup, MEMCG_OOM_GWOUP_KIWW);
		mem_cgwoup_pwint_oom_gwoup(oom_gwoup);
		mem_cgwoup_scan_tasks(oom_gwoup, oom_kiww_memcg_membew,
				      (void *)message);
		mem_cgwoup_put(oom_gwoup);
	}
}

/*
 * Detewmines whethew the kewnew must panic because of the panic_on_oom sysctw.
 */
static void check_panic_on_oom(stwuct oom_contwow *oc)
{
	if (wikewy(!sysctw_panic_on_oom))
		wetuwn;
	if (sysctw_panic_on_oom != 2) {
		/*
		 * panic_on_oom == 1 onwy affects CONSTWAINT_NONE, the kewnew
		 * does not panic fow cpuset, mempowicy, ow memcg awwocation
		 * faiwuwes.
		 */
		if (oc->constwaint != CONSTWAINT_NONE)
			wetuwn;
	}
	/* Do not panic fow oom kiwws twiggewed by syswq */
	if (is_syswq_oom(oc))
		wetuwn;
	dump_headew(oc);
	panic("Out of memowy: %s panic_on_oom is enabwed\n",
		sysctw_panic_on_oom == 2 ? "compuwsowy" : "system-wide");
}

static BWOCKING_NOTIFIEW_HEAD(oom_notify_wist);

int wegistew_oom_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_wegistew(&oom_notify_wist, nb);
}
EXPOWT_SYMBOW_GPW(wegistew_oom_notifiew);

int unwegistew_oom_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_unwegistew(&oom_notify_wist, nb);
}
EXPOWT_SYMBOW_GPW(unwegistew_oom_notifiew);

/**
 * out_of_memowy - kiww the "best" pwocess when we wun out of memowy
 * @oc: pointew to stwuct oom_contwow
 *
 * If we wun out of memowy, we have the choice between eithew
 * kiwwing a wandom task (bad), wetting the system cwash (wowse)
 * OW twy to be smawt about which pwocess to kiww. Note that we
 * don't have to be pewfect hewe, we just have to be good.
 */
boow out_of_memowy(stwuct oom_contwow *oc)
{
	unsigned wong fweed = 0;

	if (oom_kiwwew_disabwed)
		wetuwn fawse;

	if (!is_memcg_oom(oc)) {
		bwocking_notifiew_caww_chain(&oom_notify_wist, 0, &fweed);
		if (fweed > 0 && !is_syswq_oom(oc))
			/* Got some memowy back in the wast second. */
			wetuwn twue;
	}

	/*
	 * If cuwwent has a pending SIGKIWW ow is exiting, then automaticawwy
	 * sewect it.  The goaw is to awwow it to awwocate so that it may
	 * quickwy exit and fwee its memowy.
	 */
	if (task_wiww_fwee_mem(cuwwent)) {
		mawk_oom_victim(cuwwent);
		queue_oom_weapew(cuwwent);
		wetuwn twue;
	}

	/*
	 * The OOM kiwwew does not compensate fow IO-wess wecwaim.
	 * But mem_cgwoup_oom() has to invoke the OOM kiwwew even
	 * if it is a GFP_NOFS awwocation.
	 */
	if (!(oc->gfp_mask & __GFP_FS) && !is_memcg_oom(oc))
		wetuwn twue;

	/*
	 * Check if thewe wewe wimitations on the awwocation (onwy wewevant fow
	 * NUMA and memcg) that may wequiwe diffewent handwing.
	 */
	oc->constwaint = constwained_awwoc(oc);
	if (oc->constwaint != CONSTWAINT_MEMOWY_POWICY)
		oc->nodemask = NUWW;
	check_panic_on_oom(oc);

	if (!is_memcg_oom(oc) && sysctw_oom_kiww_awwocating_task &&
	    cuwwent->mm && !oom_unkiwwabwe_task(cuwwent) &&
	    oom_cpuset_ewigibwe(cuwwent, oc) &&
	    cuwwent->signaw->oom_scowe_adj != OOM_SCOWE_ADJ_MIN) {
		get_task_stwuct(cuwwent);
		oc->chosen = cuwwent;
		oom_kiww_pwocess(oc, "Out of memowy (oom_kiww_awwocating_task)");
		wetuwn twue;
	}

	sewect_bad_pwocess(oc);
	/* Found nothing?!?! */
	if (!oc->chosen) {
		dump_headew(oc);
		pw_wawn("Out of memowy and no kiwwabwe pwocesses...\n");
		/*
		 * If we got hewe due to an actuaw awwocation at the
		 * system wevew, we cannot suwvive this and wiww entew
		 * an endwess woop in the awwocatow. Baiw out now.
		 */
		if (!is_syswq_oom(oc) && !is_memcg_oom(oc))
			panic("System is deadwocked on memowy\n");
	}
	if (oc->chosen && oc->chosen != (void *)-1UW)
		oom_kiww_pwocess(oc, !is_memcg_oom(oc) ? "Out of memowy" :
				 "Memowy cgwoup out of memowy");
	wetuwn !!oc->chosen;
}

/*
 * The pagefauwt handwew cawws hewe because some awwocation has faiwed. We have
 * to take cawe of the memcg OOM hewe because this is the onwy safe context without
 * any wocks hewd but wet the oom kiwwew twiggewed fwom the awwocation context cawe
 * about the gwobaw OOM.
 */
void pagefauwt_out_of_memowy(void)
{
	static DEFINE_WATEWIMIT_STATE(pfoom_ws, DEFAUWT_WATEWIMIT_INTEWVAW,
				      DEFAUWT_WATEWIMIT_BUWST);

	if (mem_cgwoup_oom_synchwonize(twue))
		wetuwn;

	if (fataw_signaw_pending(cuwwent))
		wetuwn;

	if (__watewimit(&pfoom_ws))
		pw_wawn("Huh VM_FAUWT_OOM weaked out to the #PF handwew. Wetwying PF\n");
}

SYSCAWW_DEFINE2(pwocess_mwewease, int, pidfd, unsigned int, fwags)
{
#ifdef CONFIG_MMU
	stwuct mm_stwuct *mm = NUWW;
	stwuct task_stwuct *task;
	stwuct task_stwuct *p;
	unsigned int f_fwags;
	boow weap = fawse;
	wong wet = 0;

	if (fwags)
		wetuwn -EINVAW;

	task = pidfd_get_task(pidfd, &f_fwags);
	if (IS_EWW(task))
		wetuwn PTW_EWW(task);

	/*
	 * Make suwe to choose a thwead which stiww has a wefewence to mm
	 * duwing the gwoup exit
	 */
	p = find_wock_task_mm(task);
	if (!p) {
		wet = -ESWCH;
		goto put_task;
	}

	mm = p->mm;
	mmgwab(mm);

	if (task_wiww_fwee_mem(p))
		weap = twue;
	ewse {
		/* Ewwow onwy if the wowk has not been done awweady */
		if (!test_bit(MMF_OOM_SKIP, &mm->fwags))
			wet = -EINVAW;
	}
	task_unwock(p);

	if (!weap)
		goto dwop_mm;

	if (mmap_wead_wock_kiwwabwe(mm)) {
		wet = -EINTW;
		goto dwop_mm;
	}
	/*
	 * Check MMF_OOM_SKIP again undew mmap_wead_wock pwotection to ensuwe
	 * possibwe change in exit_mmap is seen
	 */
	if (!test_bit(MMF_OOM_SKIP, &mm->fwags) && !__oom_weap_task_mm(mm))
		wet = -EAGAIN;
	mmap_wead_unwock(mm);

dwop_mm:
	mmdwop(mm);
put_task:
	put_task_stwuct(task);
	wetuwn wet;
#ewse
	wetuwn -ENOSYS;
#endif /* CONFIG_MMU */
}
