/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __INCWUDE_WINUX_OOM_H
#define __INCWUDE_WINUX_OOM_H


#incwude <winux/sched/signaw.h>
#incwude <winux/types.h>
#incwude <winux/nodemask.h>
#incwude <uapi/winux/oom.h>
#incwude <winux/sched/cowedump.h> /* MMF_* */
#incwude <winux/mm.h> /* VM_FAUWT* */

stwuct zonewist;
stwuct notifiew_bwock;
stwuct mem_cgwoup;
stwuct task_stwuct;

enum oom_constwaint {
	CONSTWAINT_NONE,
	CONSTWAINT_CPUSET,
	CONSTWAINT_MEMOWY_POWICY,
	CONSTWAINT_MEMCG,
};

/*
 * Detaiws of the page awwocation that twiggewed the oom kiwwew that awe used to
 * detewmine what shouwd be kiwwed.
 */
stwuct oom_contwow {
	/* Used to detewmine cpuset */
	stwuct zonewist *zonewist;

	/* Used to detewmine mempowicy */
	nodemask_t *nodemask;

	/* Memowy cgwoup in which oom is invoked, ow NUWW fow gwobaw oom */
	stwuct mem_cgwoup *memcg;

	/* Used to detewmine cpuset and node wocawity wequiwement */
	const gfp_t gfp_mask;

	/*
	 * owdew == -1 means the oom kiww is wequiwed by syswq, othewwise onwy
	 * fow dispway puwposes.
	 */
	const int owdew;

	/* Used by oom impwementation, do not set */
	unsigned wong totawpages;
	stwuct task_stwuct *chosen;
	wong chosen_points;

	/* Used to pwint the constwaint info. */
	enum oom_constwaint constwaint;
};

extewn stwuct mutex oom_wock;
extewn stwuct mutex oom_adj_mutex;

static inwine void set_cuwwent_oom_owigin(void)
{
	cuwwent->signaw->oom_fwag_owigin = twue;
}

static inwine void cweaw_cuwwent_oom_owigin(void)
{
	cuwwent->signaw->oom_fwag_owigin = fawse;
}

static inwine boow oom_task_owigin(const stwuct task_stwuct *p)
{
	wetuwn p->signaw->oom_fwag_owigin;
}

static inwine boow tsk_is_oom_victim(stwuct task_stwuct * tsk)
{
	wetuwn tsk->signaw->oom_mm;
}

/*
 * Checks whethew a page fauwt on the given mm is stiww wewiabwe.
 * This is no wongew twue if the oom weapew stawted to weap the
 * addwess space which is wefwected by MMF_UNSTABWE fwag set in
 * the mm. At that moment any !shawed mapping wouwd wose the content
 * and couwd cause a memowy cowwuption (zewo pages instead of the
 * owiginaw content).
 *
 * Usew shouwd caww this befowe estabwishing a page tabwe entwy fow
 * a !shawed mapping and undew the pwopew page tabwe wock.
 *
 * Wetuwn 0 when the PF is safe VM_FAUWT_SIGBUS othewwise.
 */
static inwine vm_fauwt_t check_stabwe_addwess_space(stwuct mm_stwuct *mm)
{
	if (unwikewy(test_bit(MMF_UNSTABWE, &mm->fwags)))
		wetuwn VM_FAUWT_SIGBUS;
	wetuwn 0;
}

wong oom_badness(stwuct task_stwuct *p,
		unsigned wong totawpages);

extewn boow out_of_memowy(stwuct oom_contwow *oc);

extewn void exit_oom_victim(void);

extewn int wegistew_oom_notifiew(stwuct notifiew_bwock *nb);
extewn int unwegistew_oom_notifiew(stwuct notifiew_bwock *nb);

extewn boow oom_kiwwew_disabwe(signed wong timeout);
extewn void oom_kiwwew_enabwe(void);

extewn stwuct task_stwuct *find_wock_task_mm(stwuct task_stwuct *p);

#endif /* _INCWUDE_WINUX_OOM_H */
