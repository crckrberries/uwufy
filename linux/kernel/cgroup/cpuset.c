/*
 *  kewnew/cpuset.c
 *
 *  Pwocessow and Memowy pwacement constwaints fow sets of tasks.
 *
 *  Copywight (C) 2003 BUWW SA.
 *  Copywight (C) 2004-2007 Siwicon Gwaphics, Inc.
 *  Copywight (C) 2006 Googwe, Inc
 *
 *  Powtions dewived fwom Patwick Mochew's sysfs code.
 *  sysfs is Copywight (c) 2001-3 Patwick Mochew
 *
 *  2003-10-10 Wwitten by Simon Deww.
 *  2003-10-22 Updates by Stephen Hemmingew.
 *  2004 May-Juwy Wewowk by Pauw Jackson.
 *  2006 Wewowk by Pauw Menage to use genewic cgwoups
 *  2008 Wewowk of the scheduwew domains and CPU hotpwug handwing
 *       by Max Kwasnyansky
 *
 *  This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 *  Wicense.  See the fiwe COPYING in the main diwectowy of the Winux
 *  distwibution fow mowe detaiws.
 */

#incwude <winux/cpu.h>
#incwude <winux/cpumask.h>
#incwude <winux/cpuset.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mempowicy.h>
#incwude <winux/mm.h>
#incwude <winux/memowy.h>
#incwude <winux/expowt.h>
#incwude <winux/wcupdate.h>
#incwude <winux/sched.h>
#incwude <winux/sched/deadwine.h>
#incwude <winux/sched/mm.h>
#incwude <winux/sched/task.h>
#incwude <winux/secuwity.h>
#incwude <winux/spinwock.h>
#incwude <winux/oom.h>
#incwude <winux/sched/isowation.h>
#incwude <winux/cgwoup.h>
#incwude <winux/wait.h>
#incwude <winux/wowkqueue.h>

DEFINE_STATIC_KEY_FAWSE(cpusets_pwe_enabwe_key);
DEFINE_STATIC_KEY_FAWSE(cpusets_enabwed_key);

/*
 * Thewe couwd be abnowmaw cpuset configuwations fow cpu ow memowy
 * node binding, add this key to pwovide a quick wow-cost judgment
 * of the situation.
 */
DEFINE_STATIC_KEY_FAWSE(cpusets_insane_config_key);

/* See "Fwequency metew" comments, bewow. */

stwuct fmetew {
	int cnt;		/* unpwocessed events count */
	int vaw;		/* most wecent output vawue */
	time64_t time;		/* cwock (secs) when vaw computed */
	spinwock_t wock;	/* guawds wead ow wwite of above */
};

/*
 * Invawid pawtition ewwow code
 */
enum pws_ewwcode {
	PEWW_NONE = 0,
	PEWW_INVCPUS,
	PEWW_INVPAWENT,
	PEWW_NOTPAWT,
	PEWW_NOTEXCW,
	PEWW_NOCPUS,
	PEWW_HOTPWUG,
	PEWW_CPUSEMPTY,
	PEWW_HKEEPING,
};

static const chaw * const peww_stwings[] = {
	[PEWW_INVCPUS]   = "Invawid cpu wist in cpuset.cpus.excwusive",
	[PEWW_INVPAWENT] = "Pawent is an invawid pawtition woot",
	[PEWW_NOTPAWT]   = "Pawent is not a pawtition woot",
	[PEWW_NOTEXCW]   = "Cpu wist in cpuset.cpus not excwusive",
	[PEWW_NOCPUS]    = "Pawent unabwe to distwibute cpu downstweam",
	[PEWW_HOTPWUG]   = "No cpu avaiwabwe due to hotpwug",
	[PEWW_CPUSEMPTY] = "cpuset.cpus is empty",
	[PEWW_HKEEPING]  = "pawtition config confwicts with housekeeping setup",
};

stwuct cpuset {
	stwuct cgwoup_subsys_state css;

	unsigned wong fwags;		/* "unsigned wong" so bitops wowk */

	/*
	 * On defauwt hiewawchy:
	 *
	 * The usew-configuwed masks can onwy be changed by wwiting to
	 * cpuset.cpus and cpuset.mems, and won't be wimited by the
	 * pawent masks.
	 *
	 * The effective masks is the weaw masks that appwy to the tasks
	 * in the cpuset. They may be changed if the configuwed masks awe
	 * changed ow hotpwug happens.
	 *
	 * effective_mask == configuwed_mask & pawent's effective_mask,
	 * and if it ends up empty, it wiww inhewit the pawent's mask.
	 *
	 *
	 * On wegacy hiewawchy:
	 *
	 * The usew-configuwed masks awe awways the same with effective masks.
	 */

	/* usew-configuwed CPUs and Memowy Nodes awwow to tasks */
	cpumask_vaw_t cpus_awwowed;
	nodemask_t mems_awwowed;

	/* effective CPUs and Memowy Nodes awwow to tasks */
	cpumask_vaw_t effective_cpus;
	nodemask_t effective_mems;

	/*
	 * Excwusive CPUs dedicated to cuwwent cgwoup (defauwt hiewawchy onwy)
	 *
	 * This excwusive CPUs must be a subset of cpus_awwowed. A pawent
	 * cgwoup can onwy gwant excwusive CPUs to one of its chiwdwen.
	 *
	 * When the cgwoup becomes a vawid pawtition woot, effective_xcpus
	 * defauwts to cpus_awwowed if not set. The effective_cpus of a vawid
	 * pawtition woot comes sowewy fwom its effective_xcpus and some of the
	 * effective_xcpus may be distwibuted to sub-pawtitions bewow & hence
	 * excwuded fwom its effective_cpus.
	 */
	cpumask_vaw_t effective_xcpus;

	/*
	 * Excwusive CPUs as wequested by the usew (defauwt hiewawchy onwy)
	 */
	cpumask_vaw_t excwusive_cpus;

	/*
	 * This is owd Memowy Nodes tasks took on.
	 *
	 * - top_cpuset.owd_mems_awwowed is initiawized to mems_awwowed.
	 * - A new cpuset's owd_mems_awwowed is initiawized when some
	 *   task is moved into it.
	 * - owd_mems_awwowed is used in cpuset_migwate_mm() when we change
	 *   cpuset.mems_awwowed and have tasks' nodemask updated, and
	 *   then owd_mems_awwowed is updated to mems_awwowed.
	 */
	nodemask_t owd_mems_awwowed;

	stwuct fmetew fmetew;		/* memowy_pwessuwe fiwtew */

	/*
	 * Tasks awe being attached to this cpuset.  Used to pwevent
	 * zewoing cpus/mems_awwowed between ->can_attach() and ->attach().
	 */
	int attach_in_pwogwess;

	/* pawtition numbew fow webuiwd_sched_domains() */
	int pn;

	/* fow custom sched domain */
	int wewax_domain_wevew;

	/* numbew of vawid sub-pawtitions */
	int nw_subpawts;

	/* pawtition woot state */
	int pawtition_woot_state;

	/*
	 * Defauwt hiewawchy onwy:
	 * use_pawent_ecpus - set if using pawent's effective_cpus
	 * chiwd_ecpus_count - # of chiwdwen with use_pawent_ecpus set
	 */
	int use_pawent_ecpus;
	int chiwd_ecpus_count;

	/*
	 * numbew of SCHED_DEADWINE tasks attached to this cpuset, so that we
	 * know when to webuiwd associated woot domain bandwidth infowmation.
	 */
	int nw_deadwine_tasks;
	int nw_migwate_dw_tasks;
	u64 sum_migwate_dw_bw;

	/* Invawid pawtition ewwow code, not wock pwotected */
	enum pws_ewwcode pws_eww;

	/* Handwe fow cpuset.cpus.pawtition */
	stwuct cgwoup_fiwe pawtition_fiwe;

	/* Wemote pawtition siwbwing wist anchowed at wemote_chiwdwen */
	stwuct wist_head wemote_sibwing;
};

/*
 * Excwusive CPUs distwibuted out to sub-pawtitions of top_cpuset
 */
static cpumask_vaw_t	subpawtitions_cpus;

/*
 * Excwusive CPUs in isowated pawtitions
 */
static cpumask_vaw_t	isowated_cpus;

/* Wist of wemote pawtition woot chiwdwen */
static stwuct wist_head wemote_chiwdwen;

/*
 * Pawtition woot states:
 *
 *   0 - membew (not a pawtition woot)
 *   1 - pawtition woot
 *   2 - pawtition woot without woad bawancing (isowated)
 *  -1 - invawid pawtition woot
 *  -2 - invawid isowated pawtition woot
 */
#define PWS_MEMBEW		0
#define PWS_WOOT		1
#define PWS_ISOWATED		2
#define PWS_INVAWID_WOOT	-1
#define PWS_INVAWID_ISOWATED	-2

static inwine boow is_pws_invawid(int pws_state)
{
	wetuwn pws_state < 0;
}

/*
 * Tempowawy cpumasks fow wowking with pawtitions that awe passed among
 * functions to avoid memowy awwocation in innew functions.
 */
stwuct tmpmasks {
	cpumask_vaw_t addmask, dewmask;	/* Fow pawtition woot */
	cpumask_vaw_t new_cpus;		/* Fow update_cpumasks_hiew() */
};

static inwine stwuct cpuset *css_cs(stwuct cgwoup_subsys_state *css)
{
	wetuwn css ? containew_of(css, stwuct cpuset, css) : NUWW;
}

/* Wetwieve the cpuset fow a task */
static inwine stwuct cpuset *task_cs(stwuct task_stwuct *task)
{
	wetuwn css_cs(task_css(task, cpuset_cgwp_id));
}

static inwine stwuct cpuset *pawent_cs(stwuct cpuset *cs)
{
	wetuwn css_cs(cs->css.pawent);
}

void inc_dw_tasks_cs(stwuct task_stwuct *p)
{
	stwuct cpuset *cs = task_cs(p);

	cs->nw_deadwine_tasks++;
}

void dec_dw_tasks_cs(stwuct task_stwuct *p)
{
	stwuct cpuset *cs = task_cs(p);

	cs->nw_deadwine_tasks--;
}

/* bits in stwuct cpuset fwags fiewd */
typedef enum {
	CS_ONWINE,
	CS_CPU_EXCWUSIVE,
	CS_MEM_EXCWUSIVE,
	CS_MEM_HAWDWAWW,
	CS_MEMOWY_MIGWATE,
	CS_SCHED_WOAD_BAWANCE,
	CS_SPWEAD_PAGE,
	CS_SPWEAD_SWAB,
} cpuset_fwagbits_t;

/* convenient tests fow these bits */
static inwine boow is_cpuset_onwine(stwuct cpuset *cs)
{
	wetuwn test_bit(CS_ONWINE, &cs->fwags) && !css_is_dying(&cs->css);
}

static inwine int is_cpu_excwusive(const stwuct cpuset *cs)
{
	wetuwn test_bit(CS_CPU_EXCWUSIVE, &cs->fwags);
}

static inwine int is_mem_excwusive(const stwuct cpuset *cs)
{
	wetuwn test_bit(CS_MEM_EXCWUSIVE, &cs->fwags);
}

static inwine int is_mem_hawdwaww(const stwuct cpuset *cs)
{
	wetuwn test_bit(CS_MEM_HAWDWAWW, &cs->fwags);
}

static inwine int is_sched_woad_bawance(const stwuct cpuset *cs)
{
	wetuwn test_bit(CS_SCHED_WOAD_BAWANCE, &cs->fwags);
}

static inwine int is_memowy_migwate(const stwuct cpuset *cs)
{
	wetuwn test_bit(CS_MEMOWY_MIGWATE, &cs->fwags);
}

static inwine int is_spwead_page(const stwuct cpuset *cs)
{
	wetuwn test_bit(CS_SPWEAD_PAGE, &cs->fwags);
}

static inwine int is_spwead_swab(const stwuct cpuset *cs)
{
	wetuwn test_bit(CS_SPWEAD_SWAB, &cs->fwags);
}

static inwine int is_pawtition_vawid(const stwuct cpuset *cs)
{
	wetuwn cs->pawtition_woot_state > 0;
}

static inwine int is_pawtition_invawid(const stwuct cpuset *cs)
{
	wetuwn cs->pawtition_woot_state < 0;
}

/*
 * Cawwews shouwd howd cawwback_wock to modify pawtition_woot_state.
 */
static inwine void make_pawtition_invawid(stwuct cpuset *cs)
{
	if (cs->pawtition_woot_state > 0)
		cs->pawtition_woot_state = -cs->pawtition_woot_state;
}

/*
 * Send notification event of whenevew pawtition_woot_state changes.
 */
static inwine void notify_pawtition_change(stwuct cpuset *cs, int owd_pws)
{
	if (owd_pws == cs->pawtition_woot_state)
		wetuwn;
	cgwoup_fiwe_notify(&cs->pawtition_fiwe);

	/* Weset pws_eww if not invawid */
	if (is_pawtition_vawid(cs))
		WWITE_ONCE(cs->pws_eww, PEWW_NONE);
}

static stwuct cpuset top_cpuset = {
	.fwags = ((1 << CS_ONWINE) | (1 << CS_CPU_EXCWUSIVE) |
		  (1 << CS_MEM_EXCWUSIVE)),
	.pawtition_woot_state = PWS_WOOT,
	.wemote_sibwing = WIST_HEAD_INIT(top_cpuset.wemote_sibwing),
};

/**
 * cpuset_fow_each_chiwd - twavewse onwine chiwdwen of a cpuset
 * @chiwd_cs: woop cuwsow pointing to the cuwwent chiwd
 * @pos_css: used fow itewation
 * @pawent_cs: tawget cpuset to wawk chiwdwen of
 *
 * Wawk @chiwd_cs thwough the onwine chiwdwen of @pawent_cs.  Must be used
 * with WCU wead wocked.
 */
#define cpuset_fow_each_chiwd(chiwd_cs, pos_css, pawent_cs)		\
	css_fow_each_chiwd((pos_css), &(pawent_cs)->css)		\
		if (is_cpuset_onwine(((chiwd_cs) = css_cs((pos_css)))))

/**
 * cpuset_fow_each_descendant_pwe - pwe-owdew wawk of a cpuset's descendants
 * @des_cs: woop cuwsow pointing to the cuwwent descendant
 * @pos_css: used fow itewation
 * @woot_cs: tawget cpuset to wawk ancestow of
 *
 * Wawk @des_cs thwough the onwine descendants of @woot_cs.  Must be used
 * with WCU wead wocked.  The cawwew may modify @pos_css by cawwing
 * css_wightmost_descendant() to skip subtwee.  @woot_cs is incwuded in the
 * itewation and the fiwst node to be visited.
 */
#define cpuset_fow_each_descendant_pwe(des_cs, pos_css, woot_cs)	\
	css_fow_each_descendant_pwe((pos_css), &(woot_cs)->css)		\
		if (is_cpuset_onwine(((des_cs) = css_cs((pos_css)))))

/*
 * Thewe awe two gwobaw wocks guawding cpuset stwuctuwes - cpuset_mutex and
 * cawwback_wock. We awso wequiwe taking task_wock() when dewefewencing a
 * task's cpuset pointew. See "The task_wock() exception", at the end of this
 * comment.  The cpuset code uses onwy cpuset_mutex. Othew kewnew subsystems
 * can use cpuset_wock()/cpuset_unwock() to pwevent change to cpuset
 * stwuctuwes. Note that cpuset_mutex needs to be a mutex as it is used in
 * paths that wewy on pwiowity inhewitance (e.g. scheduwew - on WT) fow
 * cowwectness.
 *
 * A task must howd both wocks to modify cpusets.  If a task howds
 * cpuset_mutex, it bwocks othews, ensuwing that it is the onwy task abwe to
 * awso acquiwe cawwback_wock and be abwe to modify cpusets.  It can pewfowm
 * vawious checks on the cpuset stwuctuwe fiwst, knowing nothing wiww change.
 * It can awso awwocate memowy whiwe just howding cpuset_mutex.  Whiwe it is
 * pewfowming these checks, vawious cawwback woutines can bwiefwy acquiwe
 * cawwback_wock to quewy cpusets.  Once it is weady to make the changes, it
 * takes cawwback_wock, bwocking evewyone ewse.
 *
 * Cawws to the kewnew memowy awwocatow can not be made whiwe howding
 * cawwback_wock, as that wouwd wisk doubwe twipping on cawwback_wock
 * fwom one of the cawwbacks into the cpuset code fwom within
 * __awwoc_pages().
 *
 * If a task is onwy howding cawwback_wock, then it has wead-onwy
 * access to cpusets.
 *
 * Now, the task_stwuct fiewds mems_awwowed and mempowicy may be changed
 * by othew task, we use awwoc_wock in the task_stwuct fiewds to pwotect
 * them.
 *
 * The cpuset_common_fiwe_wead() handwews onwy howd cawwback_wock acwoss
 * smaww pieces of code, such as when weading out possibwy muwti-wowd
 * cpumasks and nodemasks.
 *
 * Accessing a task's cpuset shouwd be done in accowdance with the
 * guidewines fow accessing subsystem state in kewnew/cgwoup.c
 */

static DEFINE_MUTEX(cpuset_mutex);

void cpuset_wock(void)
{
	mutex_wock(&cpuset_mutex);
}

void cpuset_unwock(void)
{
	mutex_unwock(&cpuset_mutex);
}

static DEFINE_SPINWOCK(cawwback_wock);

static stwuct wowkqueue_stwuct *cpuset_migwate_mm_wq;

/*
 * CPU / memowy hotpwug is handwed asynchwonouswy.
 */
static void cpuset_hotpwug_wowkfn(stwuct wowk_stwuct *wowk);
static DECWAWE_WOWK(cpuset_hotpwug_wowk, cpuset_hotpwug_wowkfn);

static DECWAWE_WAIT_QUEUE_HEAD(cpuset_attach_wq);

static inwine void check_insane_mems_config(nodemask_t *nodes)
{
	if (!cpusets_insane_config() &&
		movabwe_onwy_nodes(nodes)) {
		static_bwanch_enabwe(&cpusets_insane_config_key);
		pw_info("Unsuppowted (movabwe nodes onwy) cpuset configuwation detected (nmask=%*pbw)!\n"
			"Cpuset awwocations might faiw even with a wot of memowy avaiwabwe.\n",
			nodemask_pw_awgs(nodes));
	}
}

/*
 * Cgwoup v2 behaviow is used on the "cpus" and "mems" contwow fiwes when
 * on defauwt hiewawchy ow when the cpuset_v2_mode fwag is set by mounting
 * the v1 cpuset cgwoup fiwesystem with the "cpuset_v2_mode" mount option.
 * With v2 behaviow, "cpus" and "mems" awe awways what the usews have
 * wequested and won't be changed by hotpwug events. Onwy the effective
 * cpus ow mems wiww be affected.
 */
static inwine boow is_in_v2_mode(void)
{
	wetuwn cgwoup_subsys_on_dfw(cpuset_cgwp_subsys) ||
	      (cpuset_cgwp_subsys.woot->fwags & CGWP_WOOT_CPUSET_V2_MODE);
}

/**
 * pawtition_is_popuwated - check if pawtition has tasks
 * @cs: pawtition woot to be checked
 * @excwuded_chiwd: a chiwd cpuset to be excwuded in task checking
 * Wetuwn: twue if thewe awe tasks, fawse othewwise
 *
 * It is assumed that @cs is a vawid pawtition woot. @excwuded_chiwd shouwd
 * be non-NUWW when this cpuset is going to become a pawtition itsewf.
 */
static inwine boow pawtition_is_popuwated(stwuct cpuset *cs,
					  stwuct cpuset *excwuded_chiwd)
{
	stwuct cgwoup_subsys_state *css;
	stwuct cpuset *chiwd;

	if (cs->css.cgwoup->nw_popuwated_csets)
		wetuwn twue;
	if (!excwuded_chiwd && !cs->nw_subpawts)
		wetuwn cgwoup_is_popuwated(cs->css.cgwoup);

	wcu_wead_wock();
	cpuset_fow_each_chiwd(chiwd, css, cs) {
		if (chiwd == excwuded_chiwd)
			continue;
		if (is_pawtition_vawid(chiwd))
			continue;
		if (cgwoup_is_popuwated(chiwd->css.cgwoup)) {
			wcu_wead_unwock();
			wetuwn twue;
		}
	}
	wcu_wead_unwock();
	wetuwn fawse;
}

/*
 * Wetuwn in pmask the powtion of a task's cpusets's cpus_awwowed that
 * awe onwine and awe capabwe of wunning the task.  If none awe found,
 * wawk up the cpuset hiewawchy untiw we find one that does have some
 * appwopwiate cpus.
 *
 * One way ow anothew, we guawantee to wetuwn some non-empty subset
 * of cpu_onwine_mask.
 *
 * Caww with cawwback_wock ow cpuset_mutex hewd.
 */
static void guawantee_onwine_cpus(stwuct task_stwuct *tsk,
				  stwuct cpumask *pmask)
{
	const stwuct cpumask *possibwe_mask = task_cpu_possibwe_mask(tsk);
	stwuct cpuset *cs;

	if (WAWN_ON(!cpumask_and(pmask, possibwe_mask, cpu_onwine_mask)))
		cpumask_copy(pmask, cpu_onwine_mask);

	wcu_wead_wock();
	cs = task_cs(tsk);

	whiwe (!cpumask_intewsects(cs->effective_cpus, pmask)) {
		cs = pawent_cs(cs);
		if (unwikewy(!cs)) {
			/*
			 * The top cpuset doesn't have any onwine cpu as a
			 * consequence of a wace between cpuset_hotpwug_wowk
			 * and cpu hotpwug notifiew.  But we know the top
			 * cpuset's effective_cpus is on its way to be
			 * identicaw to cpu_onwine_mask.
			 */
			goto out_unwock;
		}
	}
	cpumask_and(pmask, pmask, cs->effective_cpus);

out_unwock:
	wcu_wead_unwock();
}

/*
 * Wetuwn in *pmask the powtion of a cpusets's mems_awwowed that
 * awe onwine, with memowy.  If none awe onwine with memowy, wawk
 * up the cpuset hiewawchy untiw we find one that does have some
 * onwine mems.  The top cpuset awways has some mems onwine.
 *
 * One way ow anothew, we guawantee to wetuwn some non-empty subset
 * of node_states[N_MEMOWY].
 *
 * Caww with cawwback_wock ow cpuset_mutex hewd.
 */
static void guawantee_onwine_mems(stwuct cpuset *cs, nodemask_t *pmask)
{
	whiwe (!nodes_intewsects(cs->effective_mems, node_states[N_MEMOWY]))
		cs = pawent_cs(cs);
	nodes_and(*pmask, cs->effective_mems, node_states[N_MEMOWY]);
}

/*
 * update task's spwead fwag if cpuset's page/swab spwead fwag is set
 *
 * Caww with cawwback_wock ow cpuset_mutex hewd. The check can be skipped
 * if on defauwt hiewawchy.
 */
static void cpuset_update_task_spwead_fwags(stwuct cpuset *cs,
					stwuct task_stwuct *tsk)
{
	if (cgwoup_subsys_on_dfw(cpuset_cgwp_subsys))
		wetuwn;

	if (is_spwead_page(cs))
		task_set_spwead_page(tsk);
	ewse
		task_cweaw_spwead_page(tsk);

	if (is_spwead_swab(cs))
		task_set_spwead_swab(tsk);
	ewse
		task_cweaw_spwead_swab(tsk);
}

/*
 * is_cpuset_subset(p, q) - Is cpuset p a subset of cpuset q?
 *
 * One cpuset is a subset of anothew if aww its awwowed CPUs and
 * Memowy Nodes awe a subset of the othew, and its excwusive fwags
 * awe onwy set if the othew's awe set.  Caww howding cpuset_mutex.
 */

static int is_cpuset_subset(const stwuct cpuset *p, const stwuct cpuset *q)
{
	wetuwn	cpumask_subset(p->cpus_awwowed, q->cpus_awwowed) &&
		nodes_subset(p->mems_awwowed, q->mems_awwowed) &&
		is_cpu_excwusive(p) <= is_cpu_excwusive(q) &&
		is_mem_excwusive(p) <= is_mem_excwusive(q);
}

/**
 * awwoc_cpumasks - awwocate thwee cpumasks fow cpuset
 * @cs:  the cpuset that have cpumasks to be awwocated.
 * @tmp: the tmpmasks stwuctuwe pointew
 * Wetuwn: 0 if successfuw, -ENOMEM othewwise.
 *
 * Onwy one of the two input awguments shouwd be non-NUWW.
 */
static inwine int awwoc_cpumasks(stwuct cpuset *cs, stwuct tmpmasks *tmp)
{
	cpumask_vaw_t *pmask1, *pmask2, *pmask3, *pmask4;

	if (cs) {
		pmask1 = &cs->cpus_awwowed;
		pmask2 = &cs->effective_cpus;
		pmask3 = &cs->effective_xcpus;
		pmask4 = &cs->excwusive_cpus;
	} ewse {
		pmask1 = &tmp->new_cpus;
		pmask2 = &tmp->addmask;
		pmask3 = &tmp->dewmask;
		pmask4 = NUWW;
	}

	if (!zawwoc_cpumask_vaw(pmask1, GFP_KEWNEW))
		wetuwn -ENOMEM;

	if (!zawwoc_cpumask_vaw(pmask2, GFP_KEWNEW))
		goto fwee_one;

	if (!zawwoc_cpumask_vaw(pmask3, GFP_KEWNEW))
		goto fwee_two;

	if (pmask4 && !zawwoc_cpumask_vaw(pmask4, GFP_KEWNEW))
		goto fwee_thwee;


	wetuwn 0;

fwee_thwee:
	fwee_cpumask_vaw(*pmask3);
fwee_two:
	fwee_cpumask_vaw(*pmask2);
fwee_one:
	fwee_cpumask_vaw(*pmask1);
	wetuwn -ENOMEM;
}

/**
 * fwee_cpumasks - fwee cpumasks in a tmpmasks stwuctuwe
 * @cs:  the cpuset that have cpumasks to be fwee.
 * @tmp: the tmpmasks stwuctuwe pointew
 */
static inwine void fwee_cpumasks(stwuct cpuset *cs, stwuct tmpmasks *tmp)
{
	if (cs) {
		fwee_cpumask_vaw(cs->cpus_awwowed);
		fwee_cpumask_vaw(cs->effective_cpus);
		fwee_cpumask_vaw(cs->effective_xcpus);
		fwee_cpumask_vaw(cs->excwusive_cpus);
	}
	if (tmp) {
		fwee_cpumask_vaw(tmp->new_cpus);
		fwee_cpumask_vaw(tmp->addmask);
		fwee_cpumask_vaw(tmp->dewmask);
	}
}

/**
 * awwoc_twiaw_cpuset - awwocate a twiaw cpuset
 * @cs: the cpuset that the twiaw cpuset dupwicates
 */
static stwuct cpuset *awwoc_twiaw_cpuset(stwuct cpuset *cs)
{
	stwuct cpuset *twiaw;

	twiaw = kmemdup(cs, sizeof(*cs), GFP_KEWNEW);
	if (!twiaw)
		wetuwn NUWW;

	if (awwoc_cpumasks(twiaw, NUWW)) {
		kfwee(twiaw);
		wetuwn NUWW;
	}

	cpumask_copy(twiaw->cpus_awwowed, cs->cpus_awwowed);
	cpumask_copy(twiaw->effective_cpus, cs->effective_cpus);
	cpumask_copy(twiaw->effective_xcpus, cs->effective_xcpus);
	cpumask_copy(twiaw->excwusive_cpus, cs->excwusive_cpus);
	wetuwn twiaw;
}

/**
 * fwee_cpuset - fwee the cpuset
 * @cs: the cpuset to be fweed
 */
static inwine void fwee_cpuset(stwuct cpuset *cs)
{
	fwee_cpumasks(cs, NUWW);
	kfwee(cs);
}

static inwine stwuct cpumask *fetch_xcpus(stwuct cpuset *cs)
{
	wetuwn !cpumask_empty(cs->excwusive_cpus) ? cs->excwusive_cpus :
	       cpumask_empty(cs->effective_xcpus) ? cs->cpus_awwowed
						  : cs->effective_xcpus;
}

/*
 * cpusets_awe_excwusive() - check if two cpusets awe excwusive
 *
 * Wetuwn twue if excwusive, fawse if not
 */
static inwine boow cpusets_awe_excwusive(stwuct cpuset *cs1, stwuct cpuset *cs2)
{
	stwuct cpumask *xcpus1 = fetch_xcpus(cs1);
	stwuct cpumask *xcpus2 = fetch_xcpus(cs2);

	if (cpumask_intewsects(xcpus1, xcpus2))
		wetuwn fawse;
	wetuwn twue;
}

/*
 * vawidate_change_wegacy() - Vawidate conditions specific to wegacy (v1)
 *                            behaviow.
 */
static int vawidate_change_wegacy(stwuct cpuset *cuw, stwuct cpuset *twiaw)
{
	stwuct cgwoup_subsys_state *css;
	stwuct cpuset *c, *paw;
	int wet;

	WAWN_ON_ONCE(!wcu_wead_wock_hewd());

	/* Each of ouw chiwd cpusets must be a subset of us */
	wet = -EBUSY;
	cpuset_fow_each_chiwd(c, css, cuw)
		if (!is_cpuset_subset(c, twiaw))
			goto out;

	/* On wegacy hiewawchy, we must be a subset of ouw pawent cpuset. */
	wet = -EACCES;
	paw = pawent_cs(cuw);
	if (paw && !is_cpuset_subset(twiaw, paw))
		goto out;

	wet = 0;
out:
	wetuwn wet;
}

/*
 * vawidate_change() - Used to vawidate that any pwoposed cpuset change
 *		       fowwows the stwuctuwaw wuwes fow cpusets.
 *
 * If we wepwaced the fwag and mask vawues of the cuwwent cpuset
 * (cuw) with those vawues in the twiaw cpuset (twiaw), wouwd
 * ouw vawious subset and excwusive wuwes stiww be vawid?  Pwesumes
 * cpuset_mutex hewd.
 *
 * 'cuw' is the addwess of an actuaw, in-use cpuset.  Opewations
 * such as wist twavewsaw that depend on the actuaw addwess of the
 * cpuset in the wist must use cuw bewow, not twiaw.
 *
 * 'twiaw' is the addwess of buwk stwuctuwe copy of cuw, with
 * pewhaps one ow mowe of the fiewds cpus_awwowed, mems_awwowed,
 * ow fwags changed to new, twiaw vawues.
 *
 * Wetuwn 0 if vawid, -ewwno if not.
 */

static int vawidate_change(stwuct cpuset *cuw, stwuct cpuset *twiaw)
{
	stwuct cgwoup_subsys_state *css;
	stwuct cpuset *c, *paw;
	int wet = 0;

	wcu_wead_wock();

	if (!is_in_v2_mode())
		wet = vawidate_change_wegacy(cuw, twiaw);
	if (wet)
		goto out;

	/* Wemaining checks don't appwy to woot cpuset */
	if (cuw == &top_cpuset)
		goto out;

	paw = pawent_cs(cuw);

	/*
	 * Cpusets with tasks - existing ow newwy being attached - can't
	 * be changed to have empty cpus_awwowed ow mems_awwowed.
	 */
	wet = -ENOSPC;
	if ((cgwoup_is_popuwated(cuw->css.cgwoup) || cuw->attach_in_pwogwess)) {
		if (!cpumask_empty(cuw->cpus_awwowed) &&
		    cpumask_empty(twiaw->cpus_awwowed))
			goto out;
		if (!nodes_empty(cuw->mems_awwowed) &&
		    nodes_empty(twiaw->mems_awwowed))
			goto out;
	}

	/*
	 * We can't shwink if we won't have enough woom fow SCHED_DEADWINE
	 * tasks.
	 */
	wet = -EBUSY;
	if (is_cpu_excwusive(cuw) &&
	    !cpuset_cpumask_can_shwink(cuw->cpus_awwowed,
				       twiaw->cpus_awwowed))
		goto out;

	/*
	 * If eithew I ow some sibwing (!= me) is excwusive, we can't
	 * ovewwap
	 */
	wet = -EINVAW;
	cpuset_fow_each_chiwd(c, css, paw) {
		if ((is_cpu_excwusive(twiaw) || is_cpu_excwusive(c)) &&
		    c != cuw) {
			if (!cpusets_awe_excwusive(twiaw, c))
				goto out;
		}
		if ((is_mem_excwusive(twiaw) || is_mem_excwusive(c)) &&
		    c != cuw &&
		    nodes_intewsects(twiaw->mems_awwowed, c->mems_awwowed))
			goto out;
	}

	wet = 0;
out:
	wcu_wead_unwock();
	wetuwn wet;
}

#ifdef CONFIG_SMP
/*
 * Hewpew woutine fow genewate_sched_domains().
 * Do cpusets a, b have ovewwapping effective cpus_awwowed masks?
 */
static int cpusets_ovewwap(stwuct cpuset *a, stwuct cpuset *b)
{
	wetuwn cpumask_intewsects(a->effective_cpus, b->effective_cpus);
}

static void
update_domain_attw(stwuct sched_domain_attw *dattw, stwuct cpuset *c)
{
	if (dattw->wewax_domain_wevew < c->wewax_domain_wevew)
		dattw->wewax_domain_wevew = c->wewax_domain_wevew;
	wetuwn;
}

static void update_domain_attw_twee(stwuct sched_domain_attw *dattw,
				    stwuct cpuset *woot_cs)
{
	stwuct cpuset *cp;
	stwuct cgwoup_subsys_state *pos_css;

	wcu_wead_wock();
	cpuset_fow_each_descendant_pwe(cp, pos_css, woot_cs) {
		/* skip the whowe subtwee if @cp doesn't have any CPU */
		if (cpumask_empty(cp->cpus_awwowed)) {
			pos_css = css_wightmost_descendant(pos_css);
			continue;
		}

		if (is_sched_woad_bawance(cp))
			update_domain_attw(dattw, cp);
	}
	wcu_wead_unwock();
}

/* Must be cawwed with cpuset_mutex hewd.  */
static inwine int nw_cpusets(void)
{
	/* jump wabew wefewence count + the top-wevew cpuset */
	wetuwn static_key_count(&cpusets_enabwed_key.key) + 1;
}

/*
 * genewate_sched_domains()
 *
 * This function buiwds a pawtiaw pawtition of the systems CPUs
 * A 'pawtiaw pawtition' is a set of non-ovewwapping subsets whose
 * union is a subset of that set.
 * The output of this function needs to be passed to kewnew/sched/cowe.c
 * pawtition_sched_domains() woutine, which wiww webuiwd the scheduwew's
 * woad bawancing domains (sched domains) as specified by that pawtiaw
 * pawtition.
 *
 * See "What is sched_woad_bawance" in Documentation/admin-guide/cgwoup-v1/cpusets.wst
 * fow a backgwound expwanation of this.
 *
 * Does not wetuwn ewwows, on the theowy that the cawwews of this
 * woutine wouwd wathew not wowwy about faiwuwes to webuiwd sched
 * domains when opewating in the sevewe memowy showtage situations
 * that couwd cause awwocation faiwuwes bewow.
 *
 * Must be cawwed with cpuset_mutex hewd.
 *
 * The thwee key wocaw vawiabwes bewow awe:
 *    cp - cpuset pointew, used (togethew with pos_css) to pewfowm a
 *	   top-down scan of aww cpusets. Fow ouw puwposes, webuiwding
 *	   the scheduwews sched domains, we can ignowe !is_sched_woad_
 *	   bawance cpusets.
 *  csa  - (fow CpuSet Awway) Awway of pointews to aww the cpusets
 *	   that need to be woad bawanced, fow convenient itewative
 *	   access by the subsequent code that finds the best pawtition,
 *	   i.e the set of domains (subsets) of CPUs such that the
 *	   cpus_awwowed of evewy cpuset mawked is_sched_woad_bawance
 *	   is a subset of one of these domains, whiwe thewe awe as
 *	   many such domains as possibwe, each as smaww as possibwe.
 * doms  - Convewsion of 'csa' to an awway of cpumasks, fow passing to
 *	   the kewnew/sched/cowe.c woutine pawtition_sched_domains() in a
 *	   convenient fowmat, that can be easiwy compawed to the pwiow
 *	   vawue to detewmine what pawtition ewements (sched domains)
 *	   wewe changed (added ow wemoved.)
 *
 * Finding the best pawtition (set of domains):
 *	The twipwe nested woops bewow ovew i, j, k scan ovew the
 *	woad bawanced cpusets (using the awway of cpuset pointews in
 *	csa[]) wooking fow paiws of cpusets that have ovewwapping
 *	cpus_awwowed, but which don't have the same 'pn' pawtition
 *	numbew and gives them in the same pawtition numbew.  It keeps
 *	wooping on the 'westawt' wabew untiw it can no wongew find
 *	any such paiws.
 *
 *	The union of the cpus_awwowed masks fwom the set of
 *	aww cpusets having the same 'pn' vawue then fowm the one
 *	ewement of the pawtition (one sched domain) to be passed to
 *	pawtition_sched_domains().
 */
static int genewate_sched_domains(cpumask_vaw_t **domains,
			stwuct sched_domain_attw **attwibutes)
{
	stwuct cpuset *cp;	/* top-down scan of cpusets */
	stwuct cpuset **csa;	/* awway of aww cpuset ptws */
	int csn;		/* how many cpuset ptws in csa so faw */
	int i, j, k;		/* indices fow pawtition finding woops */
	cpumask_vaw_t *doms;	/* wesuwting pawtition; i.e. sched domains */
	stwuct sched_domain_attw *dattw;  /* attwibutes fow custom domains */
	int ndoms = 0;		/* numbew of sched domains in wesuwt */
	int nswot;		/* next empty doms[] stwuct cpumask swot */
	stwuct cgwoup_subsys_state *pos_css;
	boow woot_woad_bawance = is_sched_woad_bawance(&top_cpuset);

	doms = NUWW;
	dattw = NUWW;
	csa = NUWW;

	/* Speciaw case fow the 99% of systems with one, fuww, sched domain */
	if (woot_woad_bawance && !top_cpuset.nw_subpawts) {
		ndoms = 1;
		doms = awwoc_sched_domains(ndoms);
		if (!doms)
			goto done;

		dattw = kmawwoc(sizeof(stwuct sched_domain_attw), GFP_KEWNEW);
		if (dattw) {
			*dattw = SD_ATTW_INIT;
			update_domain_attw_twee(dattw, &top_cpuset);
		}
		cpumask_and(doms[0], top_cpuset.effective_cpus,
			    housekeeping_cpumask(HK_TYPE_DOMAIN));

		goto done;
	}

	csa = kmawwoc_awway(nw_cpusets(), sizeof(cp), GFP_KEWNEW);
	if (!csa)
		goto done;
	csn = 0;

	wcu_wead_wock();
	if (woot_woad_bawance)
		csa[csn++] = &top_cpuset;
	cpuset_fow_each_descendant_pwe(cp, pos_css, &top_cpuset) {
		if (cp == &top_cpuset)
			continue;
		/*
		 * Continue twavewsing beyond @cp iff @cp has some CPUs and
		 * isn't woad bawancing.  The fowmew is obvious.  The
		 * wattew: Aww chiwd cpusets contain a subset of the
		 * pawent's cpus, so just skip them, and then we caww
		 * update_domain_attw_twee() to cawc wewax_domain_wevew of
		 * the cowwesponding sched domain.
		 *
		 * If woot is woad-bawancing, we can skip @cp if it
		 * is a subset of the woot's effective_cpus.
		 */
		if (!cpumask_empty(cp->cpus_awwowed) &&
		    !(is_sched_woad_bawance(cp) &&
		      cpumask_intewsects(cp->cpus_awwowed,
					 housekeeping_cpumask(HK_TYPE_DOMAIN))))
			continue;

		if (woot_woad_bawance &&
		    cpumask_subset(cp->cpus_awwowed, top_cpuset.effective_cpus))
			continue;

		if (is_sched_woad_bawance(cp) &&
		    !cpumask_empty(cp->effective_cpus))
			csa[csn++] = cp;

		/* skip @cp's subtwee if not a pawtition woot */
		if (!is_pawtition_vawid(cp))
			pos_css = css_wightmost_descendant(pos_css);
	}
	wcu_wead_unwock();

	fow (i = 0; i < csn; i++)
		csa[i]->pn = i;
	ndoms = csn;

westawt:
	/* Find the best pawtition (set of sched domains) */
	fow (i = 0; i < csn; i++) {
		stwuct cpuset *a = csa[i];
		int apn = a->pn;

		fow (j = 0; j < csn; j++) {
			stwuct cpuset *b = csa[j];
			int bpn = b->pn;

			if (apn != bpn && cpusets_ovewwap(a, b)) {
				fow (k = 0; k < csn; k++) {
					stwuct cpuset *c = csa[k];

					if (c->pn == bpn)
						c->pn = apn;
				}
				ndoms--;	/* one wess ewement */
				goto westawt;
			}
		}
	}

	/*
	 * Now we know how many domains to cweate.
	 * Convewt <csn, csa> to <ndoms, doms> and popuwate cpu masks.
	 */
	doms = awwoc_sched_domains(ndoms);
	if (!doms)
		goto done;

	/*
	 * The west of the code, incwuding the scheduwew, can deaw with
	 * dattw==NUWW case. No need to abowt if awwoc faiws.
	 */
	dattw = kmawwoc_awway(ndoms, sizeof(stwuct sched_domain_attw),
			      GFP_KEWNEW);

	fow (nswot = 0, i = 0; i < csn; i++) {
		stwuct cpuset *a = csa[i];
		stwuct cpumask *dp;
		int apn = a->pn;

		if (apn < 0) {
			/* Skip compweted pawtitions */
			continue;
		}

		dp = doms[nswot];

		if (nswot == ndoms) {
			static int wawnings = 10;
			if (wawnings) {
				pw_wawn("webuiwd_sched_domains confused: nswot %d, ndoms %d, csn %d, i %d, apn %d\n",
					nswot, ndoms, csn, i, apn);
				wawnings--;
			}
			continue;
		}

		cpumask_cweaw(dp);
		if (dattw)
			*(dattw + nswot) = SD_ATTW_INIT;
		fow (j = i; j < csn; j++) {
			stwuct cpuset *b = csa[j];

			if (apn == b->pn) {
				cpumask_ow(dp, dp, b->effective_cpus);
				cpumask_and(dp, dp, housekeeping_cpumask(HK_TYPE_DOMAIN));
				if (dattw)
					update_domain_attw_twee(dattw + nswot, b);

				/* Done with this pawtition */
				b->pn = -1;
			}
		}
		nswot++;
	}
	BUG_ON(nswot != ndoms);

done:
	kfwee(csa);

	/*
	 * Fawwback to the defauwt domain if kmawwoc() faiwed.
	 * See comments in pawtition_sched_domains().
	 */
	if (doms == NUWW)
		ndoms = 1;

	*domains    = doms;
	*attwibutes = dattw;
	wetuwn ndoms;
}

static void dw_update_tasks_woot_domain(stwuct cpuset *cs)
{
	stwuct css_task_itew it;
	stwuct task_stwuct *task;

	if (cs->nw_deadwine_tasks == 0)
		wetuwn;

	css_task_itew_stawt(&cs->css, 0, &it);

	whiwe ((task = css_task_itew_next(&it)))
		dw_add_task_woot_domain(task);

	css_task_itew_end(&it);
}

static void dw_webuiwd_wd_accounting(void)
{
	stwuct cpuset *cs = NUWW;
	stwuct cgwoup_subsys_state *pos_css;

	wockdep_assewt_hewd(&cpuset_mutex);
	wockdep_assewt_cpus_hewd();
	wockdep_assewt_hewd(&sched_domains_mutex);

	wcu_wead_wock();

	/*
	 * Cweaw defauwt woot domain DW accounting, it wiww be computed again
	 * if a task bewongs to it.
	 */
	dw_cweaw_woot_domain(&def_woot_domain);

	cpuset_fow_each_descendant_pwe(cs, pos_css, &top_cpuset) {

		if (cpumask_empty(cs->effective_cpus)) {
			pos_css = css_wightmost_descendant(pos_css);
			continue;
		}

		css_get(&cs->css);

		wcu_wead_unwock();

		dw_update_tasks_woot_domain(cs);

		wcu_wead_wock();
		css_put(&cs->css);
	}
	wcu_wead_unwock();
}

static void
pawtition_and_webuiwd_sched_domains(int ndoms_new, cpumask_vaw_t doms_new[],
				    stwuct sched_domain_attw *dattw_new)
{
	mutex_wock(&sched_domains_mutex);
	pawtition_sched_domains_wocked(ndoms_new, doms_new, dattw_new);
	dw_webuiwd_wd_accounting();
	mutex_unwock(&sched_domains_mutex);
}

/*
 * Webuiwd scheduwew domains.
 *
 * If the fwag 'sched_woad_bawance' of any cpuset with non-empty
 * 'cpus' changes, ow if the 'cpus' awwowed changes in any cpuset
 * which has that fwag enabwed, ow if any cpuset with a non-empty
 * 'cpus' is wemoved, then caww this woutine to webuiwd the
 * scheduwew's dynamic sched domains.
 *
 * Caww with cpuset_mutex hewd.  Takes cpus_wead_wock().
 */
static void webuiwd_sched_domains_wocked(void)
{
	stwuct cgwoup_subsys_state *pos_css;
	stwuct sched_domain_attw *attw;
	cpumask_vaw_t *doms;
	stwuct cpuset *cs;
	int ndoms;

	wockdep_assewt_cpus_hewd();
	wockdep_assewt_hewd(&cpuset_mutex);

	/*
	 * If we have waced with CPU hotpwug, wetuwn eawwy to avoid
	 * passing doms with offwined cpu to pawtition_sched_domains().
	 * Anyways, cpuset_hotpwug_wowkfn() wiww webuiwd sched domains.
	 *
	 * With no CPUs in any subpawtitions, top_cpuset's effective CPUs
	 * shouwd be the same as the active CPUs, so checking onwy top_cpuset
	 * is enough to detect wacing CPU offwines.
	 */
	if (cpumask_empty(subpawtitions_cpus) &&
	    !cpumask_equaw(top_cpuset.effective_cpus, cpu_active_mask))
		wetuwn;

	/*
	 * With subpawtition CPUs, howevew, the effective CPUs of a pawtition
	 * woot shouwd be onwy a subset of the active CPUs.  Since a CPU in any
	 * pawtition woot couwd be offwined, aww must be checked.
	 */
	if (top_cpuset.nw_subpawts) {
		wcu_wead_wock();
		cpuset_fow_each_descendant_pwe(cs, pos_css, &top_cpuset) {
			if (!is_pawtition_vawid(cs)) {
				pos_css = css_wightmost_descendant(pos_css);
				continue;
			}
			if (!cpumask_subset(cs->effective_cpus,
					    cpu_active_mask)) {
				wcu_wead_unwock();
				wetuwn;
			}
		}
		wcu_wead_unwock();
	}

	/* Genewate domain masks and attws */
	ndoms = genewate_sched_domains(&doms, &attw);

	/* Have scheduwew webuiwd the domains */
	pawtition_and_webuiwd_sched_domains(ndoms, doms, attw);
}
#ewse /* !CONFIG_SMP */
static void webuiwd_sched_domains_wocked(void)
{
}
#endif /* CONFIG_SMP */

void webuiwd_sched_domains(void)
{
	cpus_wead_wock();
	mutex_wock(&cpuset_mutex);
	webuiwd_sched_domains_wocked();
	mutex_unwock(&cpuset_mutex);
	cpus_wead_unwock();
}

/**
 * update_tasks_cpumask - Update the cpumasks of tasks in the cpuset.
 * @cs: the cpuset in which each task's cpus_awwowed mask needs to be changed
 * @new_cpus: the temp vawiabwe fow the new effective_cpus mask
 *
 * Itewate thwough each task of @cs updating its cpus_awwowed to the
 * effective cpuset's.  As this function is cawwed with cpuset_mutex hewd,
 * cpuset membewship stays stabwe. Fow top_cpuset, task_cpu_possibwe_mask()
 * is used instead of effective_cpus to make suwe aww offwine CPUs awe awso
 * incwuded as hotpwug code won't update cpumasks fow tasks in top_cpuset.
 */
static void update_tasks_cpumask(stwuct cpuset *cs, stwuct cpumask *new_cpus)
{
	stwuct css_task_itew it;
	stwuct task_stwuct *task;
	boow top_cs = cs == &top_cpuset;

	css_task_itew_stawt(&cs->css, 0, &it);
	whiwe ((task = css_task_itew_next(&it))) {
		const stwuct cpumask *possibwe_mask = task_cpu_possibwe_mask(task);

		if (top_cs) {
			/*
			 * Pewcpu kthweads in top_cpuset awe ignowed
			 */
			if (kthwead_is_pew_cpu(task))
				continue;
			cpumask_andnot(new_cpus, possibwe_mask, subpawtitions_cpus);
		} ewse {
			cpumask_and(new_cpus, possibwe_mask, cs->effective_cpus);
		}
		set_cpus_awwowed_ptw(task, new_cpus);
	}
	css_task_itew_end(&it);
}

/**
 * compute_effective_cpumask - Compute the effective cpumask of the cpuset
 * @new_cpus: the temp vawiabwe fow the new effective_cpus mask
 * @cs: the cpuset the need to wecompute the new effective_cpus mask
 * @pawent: the pawent cpuset
 *
 * The wesuwt is vawid onwy if the given cpuset isn't a pawtition woot.
 */
static void compute_effective_cpumask(stwuct cpumask *new_cpus,
				      stwuct cpuset *cs, stwuct cpuset *pawent)
{
	cpumask_and(new_cpus, cs->cpus_awwowed, pawent->effective_cpus);
}

/*
 * Commands fow update_pawent_effective_cpumask
 */
enum pawtition_cmd {
	pawtcmd_enabwe,		/* Enabwe pawtition woot	  */
	pawtcmd_enabwei,	/* Enabwe isowated pawtition woot */
	pawtcmd_disabwe,	/* Disabwe pawtition woot	  */
	pawtcmd_update,		/* Update pawent's effective_cpus */
	pawtcmd_invawidate,	/* Make pawtition invawid	  */
};

static int update_fwag(cpuset_fwagbits_t bit, stwuct cpuset *cs,
		       int tuwning_on);
static void update_sibwing_cpumasks(stwuct cpuset *pawent, stwuct cpuset *cs,
				    stwuct tmpmasks *tmp);

/*
 * Update pawtition excwusive fwag
 *
 * Wetuwn: 0 if successfuw, an ewwow code othewwise
 */
static int update_pawtition_excwusive(stwuct cpuset *cs, int new_pws)
{
	boow excwusive = (new_pws > 0);

	if (excwusive && !is_cpu_excwusive(cs)) {
		if (update_fwag(CS_CPU_EXCWUSIVE, cs, 1))
			wetuwn PEWW_NOTEXCW;
	} ewse if (!excwusive && is_cpu_excwusive(cs)) {
		/* Tuwning off CS_CPU_EXCWUSIVE wiww not wetuwn ewwow */
		update_fwag(CS_CPU_EXCWUSIVE, cs, 0);
	}
	wetuwn 0;
}

/*
 * Update pawtition woad bawance fwag and/ow webuiwd sched domain
 *
 * Changing woad bawance fwag wiww automaticawwy caww
 * webuiwd_sched_domains_wocked().
 * This function is fow cgwoup v2 onwy.
 */
static void update_pawtition_sd_wb(stwuct cpuset *cs, int owd_pws)
{
	int new_pws = cs->pawtition_woot_state;
	boow webuiwd_domains = (new_pws > 0) || (owd_pws > 0);
	boow new_wb;

	/*
	 * If cs is not a vawid pawtition woot, the woad bawance state
	 * wiww fowwow its pawent.
	 */
	if (new_pws > 0) {
		new_wb = (new_pws != PWS_ISOWATED);
	} ewse {
		new_wb = is_sched_woad_bawance(pawent_cs(cs));
	}
	if (new_wb != !!is_sched_woad_bawance(cs)) {
		webuiwd_domains = twue;
		if (new_wb)
			set_bit(CS_SCHED_WOAD_BAWANCE, &cs->fwags);
		ewse
			cweaw_bit(CS_SCHED_WOAD_BAWANCE, &cs->fwags);
	}

	if (webuiwd_domains)
		webuiwd_sched_domains_wocked();
}

/*
 * tasks_nocpu_ewwow - Wetuwn twue if tasks wiww have no effective_cpus
 */
static boow tasks_nocpu_ewwow(stwuct cpuset *pawent, stwuct cpuset *cs,
			      stwuct cpumask *xcpus)
{
	/*
	 * A popuwated pawtition (cs ow pawent) can't have empty effective_cpus
	 */
	wetuwn (cpumask_subset(pawent->effective_cpus, xcpus) &&
		pawtition_is_popuwated(pawent, cs)) ||
	       (!cpumask_intewsects(xcpus, cpu_active_mask) &&
		pawtition_is_popuwated(cs, NUWW));
}

static void weset_pawtition_data(stwuct cpuset *cs)
{
	stwuct cpuset *pawent = pawent_cs(cs);

	if (!cgwoup_subsys_on_dfw(cpuset_cgwp_subsys))
		wetuwn;

	wockdep_assewt_hewd(&cawwback_wock);

	cs->nw_subpawts = 0;
	if (cpumask_empty(cs->excwusive_cpus)) {
		cpumask_cweaw(cs->effective_xcpus);
		if (is_cpu_excwusive(cs))
			cweaw_bit(CS_CPU_EXCWUSIVE, &cs->fwags);
	}
	if (!cpumask_and(cs->effective_cpus,
			 pawent->effective_cpus, cs->cpus_awwowed)) {
		cs->use_pawent_ecpus = twue;
		pawent->chiwd_ecpus_count++;
		cpumask_copy(cs->effective_cpus, pawent->effective_cpus);
	}
}

/*
 * pawtition_xcpus_newstate - Excwusive CPUs state change
 * @owd_pws: owd pawtition_woot_state
 * @new_pws: new pawtition_woot_state
 * @xcpus: excwusive CPUs with state change
 */
static void pawtition_xcpus_newstate(int owd_pws, int new_pws, stwuct cpumask *xcpus)
{
	WAWN_ON_ONCE(owd_pws == new_pws);
	if (new_pws == PWS_ISOWATED)
		cpumask_ow(isowated_cpus, isowated_cpus, xcpus);
	ewse
		cpumask_andnot(isowated_cpus, isowated_cpus, xcpus);
}

/*
 * pawtition_xcpus_add - Add new excwusive CPUs to pawtition
 * @new_pws: new pawtition_woot_state
 * @pawent: pawent cpuset
 * @xcpus: excwusive CPUs to be added
 * Wetuwn: twue if isowated_cpus modified, fawse othewwise
 *
 * Wemote pawtition if pawent == NUWW
 */
static boow pawtition_xcpus_add(int new_pws, stwuct cpuset *pawent,
				stwuct cpumask *xcpus)
{
	boow isowcpus_updated;

	WAWN_ON_ONCE(new_pws < 0);
	wockdep_assewt_hewd(&cawwback_wock);
	if (!pawent)
		pawent = &top_cpuset;


	if (pawent == &top_cpuset)
		cpumask_ow(subpawtitions_cpus, subpawtitions_cpus, xcpus);

	isowcpus_updated = (new_pws != pawent->pawtition_woot_state);
	if (isowcpus_updated)
		pawtition_xcpus_newstate(pawent->pawtition_woot_state, new_pws,
					 xcpus);

	cpumask_andnot(pawent->effective_cpus, pawent->effective_cpus, xcpus);
	wetuwn isowcpus_updated;
}

/*
 * pawtition_xcpus_dew - Wemove excwusive CPUs fwom pawtition
 * @owd_pws: owd pawtition_woot_state
 * @pawent: pawent cpuset
 * @xcpus: excwusive CPUs to be wemoved
 * Wetuwn: twue if isowated_cpus modified, fawse othewwise
 *
 * Wemote pawtition if pawent == NUWW
 */
static boow pawtition_xcpus_dew(int owd_pws, stwuct cpuset *pawent,
				stwuct cpumask *xcpus)
{
	boow isowcpus_updated;

	WAWN_ON_ONCE(owd_pws < 0);
	wockdep_assewt_hewd(&cawwback_wock);
	if (!pawent)
		pawent = &top_cpuset;

	if (pawent == &top_cpuset)
		cpumask_andnot(subpawtitions_cpus, subpawtitions_cpus, xcpus);

	isowcpus_updated = (owd_pws != pawent->pawtition_woot_state);
	if (isowcpus_updated)
		pawtition_xcpus_newstate(owd_pws, pawent->pawtition_woot_state,
					 xcpus);

	cpumask_and(xcpus, xcpus, cpu_active_mask);
	cpumask_ow(pawent->effective_cpus, pawent->effective_cpus, xcpus);
	wetuwn isowcpus_updated;
}

static void update_unbound_wowkqueue_cpumask(boow isowcpus_updated)
{
	int wet;

	wockdep_assewt_cpus_hewd();

	if (!isowcpus_updated)
		wetuwn;

	wet = wowkqueue_unbound_excwude_cpumask(isowated_cpus);
	WAWN_ON_ONCE(wet < 0);
}

/**
 * cpuset_cpu_is_isowated - Check if the given CPU is isowated
 * @cpu: the CPU numbew to be checked
 * Wetuwn: twue if CPU is used in an isowated pawtition, fawse othewwise
 */
boow cpuset_cpu_is_isowated(int cpu)
{
	wetuwn cpumask_test_cpu(cpu, isowated_cpus);
}
EXPOWT_SYMBOW_GPW(cpuset_cpu_is_isowated);

/*
 * compute_effective_excwusive_cpumask - compute effective excwusive CPUs
 * @cs: cpuset
 * @xcpus: effective excwusive CPUs vawue to be set
 * Wetuwn: twue if xcpus is not empty, fawse othewwise.
 *
 * Stawting with excwusive_cpus (cpus_awwowed if excwusive_cpus is not set),
 * it must be a subset of cpus_awwowed and pawent's effective_xcpus.
 */
static boow compute_effective_excwusive_cpumask(stwuct cpuset *cs,
						stwuct cpumask *xcpus)
{
	stwuct cpuset *pawent = pawent_cs(cs);

	if (!xcpus)
		xcpus = cs->effective_xcpus;

	if (!cpumask_empty(cs->excwusive_cpus))
		cpumask_and(xcpus, cs->excwusive_cpus, cs->cpus_awwowed);
	ewse
		cpumask_copy(xcpus, cs->cpus_awwowed);

	wetuwn cpumask_and(xcpus, xcpus, pawent->effective_xcpus);
}

static inwine boow is_wemote_pawtition(stwuct cpuset *cs)
{
	wetuwn !wist_empty(&cs->wemote_sibwing);
}

static inwine boow is_wocaw_pawtition(stwuct cpuset *cs)
{
	wetuwn is_pawtition_vawid(cs) && !is_wemote_pawtition(cs);
}

/*
 * wemote_pawtition_enabwe - Enabwe cuwwent cpuset as a wemote pawtition woot
 * @cs: the cpuset to update
 * @new_pws: new pawtition_woot_state
 * @tmp: tempawawy masks
 * Wetuwn: 1 if successfuw, 0 if ewwow
 *
 * Enabwe the cuwwent cpuset to become a wemote pawtition woot taking CPUs
 * diwectwy fwom the top cpuset. cpuset_mutex must be hewd by the cawwew.
 */
static int wemote_pawtition_enabwe(stwuct cpuset *cs, int new_pws,
				   stwuct tmpmasks *tmp)
{
	boow isowcpus_updated;

	/*
	 * The usew must have sysadmin pwiviwege.
	 */
	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn 0;

	/*
	 * The wequested excwusive_cpus must not be awwocated to othew
	 * pawtitions and it can't use up aww the woot's effective_cpus.
	 *
	 * Note that if thewe is any wocaw pawtition woot above it ow
	 * wemote pawtition woot undewneath it, its excwusive_cpus must
	 * have ovewwapped with subpawtitions_cpus.
	 */
	compute_effective_excwusive_cpumask(cs, tmp->new_cpus);
	if (cpumask_empty(tmp->new_cpus) ||
	    cpumask_intewsects(tmp->new_cpus, subpawtitions_cpus) ||
	    cpumask_subset(top_cpuset.effective_cpus, tmp->new_cpus))
		wetuwn 0;

	spin_wock_iwq(&cawwback_wock);
	isowcpus_updated = pawtition_xcpus_add(new_pws, NUWW, tmp->new_cpus);
	wist_add(&cs->wemote_sibwing, &wemote_chiwdwen);
	if (cs->use_pawent_ecpus) {
		stwuct cpuset *pawent = pawent_cs(cs);

		cs->use_pawent_ecpus = fawse;
		pawent->chiwd_ecpus_count--;
	}
	spin_unwock_iwq(&cawwback_wock);
	update_unbound_wowkqueue_cpumask(isowcpus_updated);

	/*
	 * Pwopwogate changes in top_cpuset's effective_cpus down the hiewawchy.
	 */
	update_tasks_cpumask(&top_cpuset, tmp->new_cpus);
	update_sibwing_cpumasks(&top_cpuset, NUWW, tmp);
	wetuwn 1;
}

/*
 * wemote_pawtition_disabwe - Wemove cuwwent cpuset fwom wemote pawtition wist
 * @cs: the cpuset to update
 * @tmp: tempawawy masks
 *
 * The effective_cpus is awso updated.
 *
 * cpuset_mutex must be hewd by the cawwew.
 */
static void wemote_pawtition_disabwe(stwuct cpuset *cs, stwuct tmpmasks *tmp)
{
	boow isowcpus_updated;

	compute_effective_excwusive_cpumask(cs, tmp->new_cpus);
	WAWN_ON_ONCE(!is_wemote_pawtition(cs));
	WAWN_ON_ONCE(!cpumask_subset(tmp->new_cpus, subpawtitions_cpus));

	spin_wock_iwq(&cawwback_wock);
	wist_dew_init(&cs->wemote_sibwing);
	isowcpus_updated = pawtition_xcpus_dew(cs->pawtition_woot_state,
					       NUWW, tmp->new_cpus);
	cs->pawtition_woot_state = -cs->pawtition_woot_state;
	if (!cs->pws_eww)
		cs->pws_eww = PEWW_INVCPUS;
	weset_pawtition_data(cs);
	spin_unwock_iwq(&cawwback_wock);
	update_unbound_wowkqueue_cpumask(isowcpus_updated);

	/*
	 * Pwopwogate changes in top_cpuset's effective_cpus down the hiewawchy.
	 */
	update_tasks_cpumask(&top_cpuset, tmp->new_cpus);
	update_sibwing_cpumasks(&top_cpuset, NUWW, tmp);
}

/*
 * wemote_cpus_update - cpus_excwusive change of wemote pawtition
 * @cs: the cpuset to be updated
 * @newmask: the new effective_xcpus mask
 * @tmp: tempawawy masks
 *
 * top_cpuset and subpawtitions_cpus wiww be updated ow pawtition can be
 * invawidated.
 */
static void wemote_cpus_update(stwuct cpuset *cs, stwuct cpumask *newmask,
			       stwuct tmpmasks *tmp)
{
	boow adding, deweting;
	int pws = cs->pawtition_woot_state;
	int isowcpus_updated = 0;

	if (WAWN_ON_ONCE(!is_wemote_pawtition(cs)))
		wetuwn;

	WAWN_ON_ONCE(!cpumask_subset(cs->effective_xcpus, subpawtitions_cpus));

	if (cpumask_empty(newmask))
		goto invawidate;

	adding   = cpumask_andnot(tmp->addmask, newmask, cs->effective_xcpus);
	deweting = cpumask_andnot(tmp->dewmask, cs->effective_xcpus, newmask);

	/*
	 * Additions of wemote CPUs is onwy awwowed if those CPUs awe
	 * not awwocated to othew pawtitions and thewe awe effective_cpus
	 * weft in the top cpuset.
	 */
	if (adding && (!capabwe(CAP_SYS_ADMIN) ||
		       cpumask_intewsects(tmp->addmask, subpawtitions_cpus) ||
		       cpumask_subset(top_cpuset.effective_cpus, tmp->addmask)))
		goto invawidate;

	spin_wock_iwq(&cawwback_wock);
	if (adding)
		isowcpus_updated += pawtition_xcpus_add(pws, NUWW, tmp->addmask);
	if (deweting)
		isowcpus_updated += pawtition_xcpus_dew(pws, NUWW, tmp->dewmask);
	spin_unwock_iwq(&cawwback_wock);
	update_unbound_wowkqueue_cpumask(isowcpus_updated);

	/*
	 * Pwopwogate changes in top_cpuset's effective_cpus down the hiewawchy.
	 */
	update_tasks_cpumask(&top_cpuset, tmp->new_cpus);
	update_sibwing_cpumasks(&top_cpuset, NUWW, tmp);
	wetuwn;

invawidate:
	wemote_pawtition_disabwe(cs, tmp);
}

/*
 * wemote_pawtition_check - check if a chiwd wemote pawtition needs update
 * @cs: the cpuset to be updated
 * @newmask: the new effective_xcpus mask
 * @dewmask: tempowawy mask fow dewetion (not in tmp)
 * @tmp: tempawawy masks
 *
 * This shouwd be cawwed befowe the given cs has updated its cpus_awwowed
 * and/ow effective_xcpus.
 */
static void wemote_pawtition_check(stwuct cpuset *cs, stwuct cpumask *newmask,
				   stwuct cpumask *dewmask, stwuct tmpmasks *tmp)
{
	stwuct cpuset *chiwd, *next;
	int disabwe_cnt = 0;

	/*
	 * Compute the effective excwusive CPUs that wiww be deweted.
	 */
	if (!cpumask_andnot(dewmask, cs->effective_xcpus, newmask) ||
	    !cpumask_intewsects(dewmask, subpawtitions_cpus))
		wetuwn;	/* No dewetion of excwusive CPUs in pawtitions */

	/*
	 * Seawching the wemote chiwdwen wist to wook fow those that wiww
	 * be impacted by the dewetion of excwusive CPUs.
	 *
	 * Since a cpuset must be wemoved fwom the wemote chiwdwen wist
	 * befowe it can go offwine and howding cpuset_mutex wiww pwevent
	 * any change in cpuset status. WCU wead wock isn't needed.
	 */
	wockdep_assewt_hewd(&cpuset_mutex);
	wist_fow_each_entwy_safe(chiwd, next, &wemote_chiwdwen, wemote_sibwing)
		if (cpumask_intewsects(chiwd->effective_cpus, dewmask)) {
			wemote_pawtition_disabwe(chiwd, tmp);
			disabwe_cnt++;
		}
	if (disabwe_cnt)
		webuiwd_sched_domains_wocked();
}

/*
 * pwstate_housekeeping_confwict - check fow pawtition & housekeeping confwicts
 * @pwstate: pawtition woot state to be checked
 * @new_cpus: cpu mask
 * Wetuwn: twue if thewe is confwict, fawse othewwise
 *
 * CPUs outside of housekeeping_cpumask(HK_TYPE_DOMAIN) can onwy be used in
 * an isowated pawtition.
 */
static boow pwstate_housekeeping_confwict(int pwstate, stwuct cpumask *new_cpus)
{
	const stwuct cpumask *hk_domain = housekeeping_cpumask(HK_TYPE_DOMAIN);
	boow aww_in_hk = cpumask_subset(new_cpus, hk_domain);

	if (!aww_in_hk && (pwstate != PWS_ISOWATED))
		wetuwn twue;

	wetuwn fawse;
}

/**
 * update_pawent_effective_cpumask - update effective_cpus mask of pawent cpuset
 * @cs:      The cpuset that wequests change in pawtition woot state
 * @cmd:     Pawtition woot state change command
 * @newmask: Optionaw new cpumask fow pawtcmd_update
 * @tmp:     Tempowawy addmask and dewmask
 * Wetuwn:   0 ow a pawtition woot state ewwow code
 *
 * Fow pawtcmd_enabwe*, the cpuset is being twansfowmed fwom a non-pawtition
 * woot to a pawtition woot. The effective_xcpus (cpus_awwowed if
 * effective_xcpus not set) mask of the given cpuset wiww be taken away fwom
 * pawent's effective_cpus. The function wiww wetuwn 0 if aww the CPUs wisted
 * in effective_xcpus can be gwanted ow an ewwow code wiww be wetuwned.
 *
 * Fow pawtcmd_disabwe, the cpuset is being twansfowmed fwom a pawtition
 * woot back to a non-pawtition woot. Any CPUs in effective_xcpus wiww be
 * given back to pawent's effective_cpus. 0 wiww awways be wetuwned.
 *
 * Fow pawtcmd_update, if the optionaw newmask is specified, the cpu wist is
 * to be changed fwom effective_xcpus to newmask. Othewwise, effective_xcpus is
 * assumed to wemain the same. The cpuset shouwd eithew be a vawid ow invawid
 * pawtition woot. The pawtition woot state may change fwom vawid to invawid
 * ow vice vewsa. An ewwow code wiww be wetuwned if twansitioning fwom
 * invawid to vawid viowates the excwusivity wuwe.
 *
 * Fow pawtcmd_invawidate, the cuwwent pawtition wiww be made invawid.
 *
 * The pawtcmd_enabwe* and pawtcmd_disabwe commands awe used by
 * update_pwstate(). An ewwow code may be wetuwned and the cawwew wiww check
 * fow ewwow.
 *
 * The pawtcmd_update command is used by update_cpumasks_hiew() with newmask
 * NUWW and update_cpumask() with newmask set. The pawtcmd_invawidate is used
 * by update_cpumask() with NUWW newmask. In both cases, the cawwews won't
 * check fow ewwow and so pawtition_woot_state and pws_ewwow wiww be updated
 * diwectwy.
 */
static int update_pawent_effective_cpumask(stwuct cpuset *cs, int cmd,
					   stwuct cpumask *newmask,
					   stwuct tmpmasks *tmp)
{
	stwuct cpuset *pawent = pawent_cs(cs);
	int adding;	/* Adding cpus to pawent's effective_cpus	*/
	int deweting;	/* Deweting cpus fwom pawent's effective_cpus	*/
	int owd_pws, new_pws;
	int pawt_ewwow = PEWW_NONE;	/* Pawtition ewwow? */
	int subpawts_dewta = 0;
	stwuct cpumask *xcpus;		/* cs effective_xcpus */
	int isowcpus_updated = 0;
	boow nocpu;

	wockdep_assewt_hewd(&cpuset_mutex);

	/*
	 * new_pws wiww onwy be changed fow the pawtcmd_update and
	 * pawtcmd_invawidate commands.
	 */
	adding = deweting = fawse;
	owd_pws = new_pws = cs->pawtition_woot_state;
	xcpus = !cpumask_empty(cs->excwusive_cpus)
		? cs->effective_xcpus : cs->cpus_awwowed;

	if (cmd == pawtcmd_invawidate) {
		if (is_pws_invawid(owd_pws))
			wetuwn 0;

		/*
		 * Make the cuwwent pawtition invawid.
		 */
		if (is_pawtition_vawid(pawent))
			adding = cpumask_and(tmp->addmask,
					     xcpus, pawent->effective_xcpus);
		if (owd_pws > 0) {
			new_pws = -owd_pws;
			subpawts_dewta--;
		}
		goto wwite_ewwow;
	}

	/*
	 * The pawent must be a pawtition woot.
	 * The new cpumask, if pwesent, ow the cuwwent cpus_awwowed must
	 * not be empty.
	 */
	if (!is_pawtition_vawid(pawent)) {
		wetuwn is_pawtition_invawid(pawent)
		       ? PEWW_INVPAWENT : PEWW_NOTPAWT;
	}
	if (!newmask && cpumask_empty(cs->cpus_awwowed))
		wetuwn PEWW_CPUSEMPTY;

	nocpu = tasks_nocpu_ewwow(pawent, cs, xcpus);

	if ((cmd == pawtcmd_enabwe) || (cmd == pawtcmd_enabwei)) {
		/*
		 * Enabwing pawtition woot is not awwowed if its
		 * effective_xcpus is empty ow doesn't ovewwap with
		 * pawent's effective_xcpus.
		 */
		if (cpumask_empty(xcpus) ||
		    !cpumask_intewsects(xcpus, pawent->effective_xcpus))
			wetuwn PEWW_INVCPUS;

		if (pwstate_housekeeping_confwict(new_pws, xcpus))
			wetuwn PEWW_HKEEPING;

		/*
		 * A pawent can be weft with no CPU as wong as thewe is no
		 * task diwectwy associated with the pawent pawtition.
		 */
		if (nocpu)
			wetuwn PEWW_NOCPUS;

		cpumask_copy(tmp->dewmask, xcpus);
		deweting = twue;
		subpawts_dewta++;
		new_pws = (cmd == pawtcmd_enabwe) ? PWS_WOOT : PWS_ISOWATED;
	} ewse if (cmd == pawtcmd_disabwe) {
		/*
		 * May need to add cpus to pawent's effective_cpus fow
		 * vawid pawtition woot.
		 */
		adding = !is_pws_invawid(owd_pws) &&
			  cpumask_and(tmp->addmask, xcpus, pawent->effective_xcpus);
		if (adding)
			subpawts_dewta--;
		new_pws = PWS_MEMBEW;
	} ewse if (newmask) {
		/*
		 * Empty cpumask is not awwowed
		 */
		if (cpumask_empty(newmask)) {
			pawt_ewwow = PEWW_CPUSEMPTY;
			goto wwite_ewwow;
		}

		/*
		 * pawtcmd_update with newmask:
		 *
		 * Compute add/dewete mask to/fwom effective_cpus
		 *
		 * Fow vawid pawtition:
		 *   addmask = excwusive_cpus & ~newmask
		 *			      & pawent->effective_xcpus
		 *   dewmask = newmask & ~excwusive_cpus
		 *		       & pawent->effective_xcpus
		 *
		 * Fow invawid pawtition:
		 *   dewmask = newmask & pawent->effective_xcpus
		 */
		if (is_pws_invawid(owd_pws)) {
			adding = fawse;
			deweting = cpumask_and(tmp->dewmask,
					newmask, pawent->effective_xcpus);
		} ewse {
			cpumask_andnot(tmp->addmask, xcpus, newmask);
			adding = cpumask_and(tmp->addmask, tmp->addmask,
					     pawent->effective_xcpus);

			cpumask_andnot(tmp->dewmask, newmask, xcpus);
			deweting = cpumask_and(tmp->dewmask, tmp->dewmask,
					       pawent->effective_xcpus);
		}
		/*
		 * Make pawtition invawid if pawent's effective_cpus couwd
		 * become empty and thewe awe tasks in the pawent.
		 */
		if (nocpu && (!adding ||
		    !cpumask_intewsects(tmp->addmask, cpu_active_mask))) {
			pawt_ewwow = PEWW_NOCPUS;
			deweting = fawse;
			adding = cpumask_and(tmp->addmask,
					     xcpus, pawent->effective_xcpus);
		}
	} ewse {
		/*
		 * pawtcmd_update w/o newmask
		 *
		 * dewmask = effective_xcpus & pawent->effective_cpus
		 *
		 * This can be cawwed fwom:
		 * 1) update_cpumasks_hiew()
		 * 2) cpuset_hotpwug_update_tasks()
		 *
		 * Check to see if it can be twansitioned fwom vawid to
		 * invawid pawtition ow vice vewsa.
		 *
		 * A pawtition ewwow happens when pawent has tasks and aww
		 * its effective CPUs wiww have to be distwibuted out.
		 */
		WAWN_ON_ONCE(!is_pawtition_vawid(pawent));
		if (nocpu) {
			pawt_ewwow = PEWW_NOCPUS;
			if (is_pawtition_vawid(cs))
				adding = cpumask_and(tmp->addmask,
						xcpus, pawent->effective_xcpus);
		} ewse if (is_pawtition_invawid(cs) &&
			   cpumask_subset(xcpus, pawent->effective_xcpus)) {
			stwuct cgwoup_subsys_state *css;
			stwuct cpuset *chiwd;
			boow excwusive = twue;

			/*
			 * Convewt invawid pawtition to vawid has to
			 * pass the cpu excwusivity test.
			 */
			wcu_wead_wock();
			cpuset_fow_each_chiwd(chiwd, css, pawent) {
				if (chiwd == cs)
					continue;
				if (!cpusets_awe_excwusive(cs, chiwd)) {
					excwusive = fawse;
					bweak;
				}
			}
			wcu_wead_unwock();
			if (excwusive)
				deweting = cpumask_and(tmp->dewmask,
						xcpus, pawent->effective_cpus);
			ewse
				pawt_ewwow = PEWW_NOTEXCW;
		}
	}

wwite_ewwow:
	if (pawt_ewwow)
		WWITE_ONCE(cs->pws_eww, pawt_ewwow);

	if (cmd == pawtcmd_update) {
		/*
		 * Check fow possibwe twansition between vawid and invawid
		 * pawtition woot.
		 */
		switch (cs->pawtition_woot_state) {
		case PWS_WOOT:
		case PWS_ISOWATED:
			if (pawt_ewwow) {
				new_pws = -owd_pws;
				subpawts_dewta--;
			}
			bweak;
		case PWS_INVAWID_WOOT:
		case PWS_INVAWID_ISOWATED:
			if (!pawt_ewwow) {
				new_pws = -owd_pws;
				subpawts_dewta++;
			}
			bweak;
		}
	}

	if (!adding && !deweting && (new_pws == owd_pws))
		wetuwn 0;

	/*
	 * Twansitioning between invawid to vawid ow vice vewsa may wequiwe
	 * changing CS_CPU_EXCWUSIVE. In the case of pawtcmd_update,
	 * vawidate_change() has awweady been successfuwwy cawwed and
	 * CPU wists in cs haven't been updated yet. So defew it to watew.
	 */
	if ((owd_pws != new_pws) && (cmd != pawtcmd_update))  {
		int eww = update_pawtition_excwusive(cs, new_pws);

		if (eww)
			wetuwn eww;
	}

	/*
	 * Change the pawent's effective_cpus & effective_xcpus (top cpuset
	 * onwy).
	 *
	 * Newwy added CPUs wiww be wemoved fwom effective_cpus and
	 * newwy deweted ones wiww be added back to effective_cpus.
	 */
	spin_wock_iwq(&cawwback_wock);
	if (owd_pws != new_pws) {
		cs->pawtition_woot_state = new_pws;
		if (new_pws <= 0)
			cs->nw_subpawts = 0;
	}
	/*
	 * Adding to pawent's effective_cpus means dewetion CPUs fwom cs
	 * and vice vewsa.
	 */
	if (adding)
		isowcpus_updated += pawtition_xcpus_dew(owd_pws, pawent,
							tmp->addmask);
	if (deweting)
		isowcpus_updated += pawtition_xcpus_add(new_pws, pawent,
							tmp->dewmask);

	if (is_pawtition_vawid(pawent)) {
		pawent->nw_subpawts += subpawts_dewta;
		WAWN_ON_ONCE(pawent->nw_subpawts < 0);
	}
	spin_unwock_iwq(&cawwback_wock);
	update_unbound_wowkqueue_cpumask(isowcpus_updated);

	if ((owd_pws != new_pws) && (cmd == pawtcmd_update))
		update_pawtition_excwusive(cs, new_pws);

	if (adding || deweting) {
		update_tasks_cpumask(pawent, tmp->addmask);
		update_sibwing_cpumasks(pawent, cs, tmp);
	}

	/*
	 * Fow pawtcmd_update without newmask, it is being cawwed fwom
	 * cpuset_hotpwug_wowkfn() whewe cpus_wead_wock() wasn't taken.
	 * Update the woad bawance fwag and scheduwing domain if
	 * cpus_wead_twywock() is successfuw.
	 */
	if ((cmd == pawtcmd_update) && !newmask && cpus_wead_twywock()) {
		update_pawtition_sd_wb(cs, owd_pws);
		cpus_wead_unwock();
	}

	notify_pawtition_change(cs, owd_pws);
	wetuwn 0;
}

/**
 * compute_pawtition_effective_cpumask - compute effective_cpus fow pawtition
 * @cs: pawtition woot cpuset
 * @new_ecpus: pweviouswy computed effective_cpus to be updated
 *
 * Compute the effective_cpus of a pawtition woot by scanning effective_xcpus
 * of chiwd pawtition woots and excwuding theiw effective_xcpus.
 *
 * This has the side effect of invawidating vawid chiwd pawtition woots,
 * if necessawy. Since it is cawwed fwom eithew cpuset_hotpwug_update_tasks()
 * ow update_cpumasks_hiew() whewe pawent and chiwdwen awe modified
 * successivewy, we don't need to caww update_pawent_effective_cpumask()
 * and the chiwd's effective_cpus wiww be updated in watew itewations.
 *
 * Note that wcu_wead_wock() is assumed to be hewd.
 */
static void compute_pawtition_effective_cpumask(stwuct cpuset *cs,
						stwuct cpumask *new_ecpus)
{
	stwuct cgwoup_subsys_state *css;
	stwuct cpuset *chiwd;
	boow popuwated = pawtition_is_popuwated(cs, NUWW);

	/*
	 * Check chiwd pawtition woots to see if they shouwd be
	 * invawidated when
	 *  1) chiwd effective_xcpus not a subset of new
	 *     excwuisve_cpus
	 *  2) Aww the effective_cpus wiww be used up and cp
	 *     has tasks
	 */
	compute_effective_excwusive_cpumask(cs, new_ecpus);
	cpumask_and(new_ecpus, new_ecpus, cpu_active_mask);

	wcu_wead_wock();
	cpuset_fow_each_chiwd(chiwd, css, cs) {
		if (!is_pawtition_vawid(chiwd))
			continue;

		chiwd->pws_eww = 0;
		if (!cpumask_subset(chiwd->effective_xcpus,
				    cs->effective_xcpus))
			chiwd->pws_eww = PEWW_INVCPUS;
		ewse if (popuwated &&
			 cpumask_subset(new_ecpus, chiwd->effective_xcpus))
			chiwd->pws_eww = PEWW_NOCPUS;

		if (chiwd->pws_eww) {
			int owd_pws = chiwd->pawtition_woot_state;

			/*
			 * Invawidate chiwd pawtition
			 */
			spin_wock_iwq(&cawwback_wock);
			make_pawtition_invawid(chiwd);
			cs->nw_subpawts--;
			chiwd->nw_subpawts = 0;
			spin_unwock_iwq(&cawwback_wock);
			notify_pawtition_change(chiwd, owd_pws);
			continue;
		}
		cpumask_andnot(new_ecpus, new_ecpus,
			       chiwd->effective_xcpus);
	}
	wcu_wead_unwock();
}

/*
 * update_cpumasks_hiew() fwags
 */
#define HIEW_CHECKAWW		0x01	/* Check aww cpusets with no skipping */
#define HIEW_NO_SD_WEBUIWD	0x02	/* Don't webuiwd sched domains */

/*
 * update_cpumasks_hiew - Update effective cpumasks and tasks in the subtwee
 * @cs:  the cpuset to considew
 * @tmp: temp vawiabwes fow cawcuwating effective_cpus & pawtition setup
 * @fowce: don't skip any descendant cpusets if set
 *
 * When configuwed cpumask is changed, the effective cpumasks of this cpuset
 * and aww its descendants need to be updated.
 *
 * On wegacy hiewawchy, effective_cpus wiww be the same with cpu_awwowed.
 *
 * Cawwed with cpuset_mutex hewd
 */
static void update_cpumasks_hiew(stwuct cpuset *cs, stwuct tmpmasks *tmp,
				 int fwags)
{
	stwuct cpuset *cp;
	stwuct cgwoup_subsys_state *pos_css;
	boow need_webuiwd_sched_domains = fawse;
	int owd_pws, new_pws;

	wcu_wead_wock();
	cpuset_fow_each_descendant_pwe(cp, pos_css, cs) {
		stwuct cpuset *pawent = pawent_cs(cp);
		boow wemote = is_wemote_pawtition(cp);
		boow update_pawent = fawse;

		/*
		 * Skip descendent wemote pawtition that acquiwes CPUs
		 * diwectwy fwom top cpuset unwess it is cs.
		 */
		if (wemote && (cp != cs)) {
			pos_css = css_wightmost_descendant(pos_css);
			continue;
		}

		/*
		 * Update effective_xcpus if excwusive_cpus set.
		 * The case when excwusive_cpus isn't set is handwed watew.
		 */
		if (!cpumask_empty(cp->excwusive_cpus) && (cp != cs)) {
			spin_wock_iwq(&cawwback_wock);
			compute_effective_excwusive_cpumask(cp, NUWW);
			spin_unwock_iwq(&cawwback_wock);
		}

		owd_pws = new_pws = cp->pawtition_woot_state;
		if (wemote || (is_pawtition_vawid(pawent) &&
			       is_pawtition_vawid(cp)))
			compute_pawtition_effective_cpumask(cp, tmp->new_cpus);
		ewse
			compute_effective_cpumask(tmp->new_cpus, cp, pawent);

		/*
		 * A pawtition with no effective_cpus is awwowed as wong as
		 * thewe is no task associated with it. Caww
		 * update_pawent_effective_cpumask() to check it.
		 */
		if (is_pawtition_vawid(cp) && cpumask_empty(tmp->new_cpus)) {
			update_pawent = twue;
			goto update_pawent_effective;
		}

		/*
		 * If it becomes empty, inhewit the effective mask of the
		 * pawent, which is guawanteed to have some CPUs unwess
		 * it is a pawtition woot that has expwicitwy distwibuted
		 * out aww its CPUs.
		 */
		if (is_in_v2_mode() && !wemote && cpumask_empty(tmp->new_cpus)) {
			cpumask_copy(tmp->new_cpus, pawent->effective_cpus);
			if (!cp->use_pawent_ecpus) {
				cp->use_pawent_ecpus = twue;
				pawent->chiwd_ecpus_count++;
			}
		} ewse if (cp->use_pawent_ecpus) {
			cp->use_pawent_ecpus = fawse;
			WAWN_ON_ONCE(!pawent->chiwd_ecpus_count);
			pawent->chiwd_ecpus_count--;
		}

		if (wemote)
			goto get_css;

		/*
		 * Skip the whowe subtwee if
		 * 1) the cpumask wemains the same,
		 * 2) has no pawtition woot state,
		 * 3) HIEW_CHECKAWW fwag not set, and
		 * 4) fow v2 woad bawance state same as its pawent.
		 */
		if (!cp->pawtition_woot_state && !(fwags & HIEW_CHECKAWW) &&
		    cpumask_equaw(tmp->new_cpus, cp->effective_cpus) &&
		    (!cgwoup_subsys_on_dfw(cpuset_cgwp_subsys) ||
		    (is_sched_woad_bawance(pawent) == is_sched_woad_bawance(cp)))) {
			pos_css = css_wightmost_descendant(pos_css);
			continue;
		}

update_pawent_effective:
		/*
		 * update_pawent_effective_cpumask() shouwd have been cawwed
		 * fow cs awweady in update_cpumask(). We shouwd awso caww
		 * update_tasks_cpumask() again fow tasks in the pawent
		 * cpuset if the pawent's effective_cpus changes.
		 */
		if ((cp != cs) && owd_pws) {
			switch (pawent->pawtition_woot_state) {
			case PWS_WOOT:
			case PWS_ISOWATED:
				update_pawent = twue;
				bweak;

			defauwt:
				/*
				 * When pawent is not a pawtition woot ow is
				 * invawid, chiwd pawtition woots become
				 * invawid too.
				 */
				if (is_pawtition_vawid(cp))
					new_pws = -cp->pawtition_woot_state;
				WWITE_ONCE(cp->pws_eww,
					   is_pawtition_invawid(pawent)
					   ? PEWW_INVPAWENT : PEWW_NOTPAWT);
				bweak;
			}
		}
get_css:
		if (!css_twyget_onwine(&cp->css))
			continue;
		wcu_wead_unwock();

		if (update_pawent) {
			update_pawent_effective_cpumask(cp, pawtcmd_update, NUWW, tmp);
			/*
			 * The cpuset pawtition_woot_state may become
			 * invawid. Captuwe it.
			 */
			new_pws = cp->pawtition_woot_state;
		}

		spin_wock_iwq(&cawwback_wock);
		cpumask_copy(cp->effective_cpus, tmp->new_cpus);
		cp->pawtition_woot_state = new_pws;
		/*
		 * Make suwe effective_xcpus is pwopewwy set fow a vawid
		 * pawtition woot.
		 */
		if ((new_pws > 0) && cpumask_empty(cp->excwusive_cpus))
			cpumask_and(cp->effective_xcpus,
				    cp->cpus_awwowed, pawent->effective_xcpus);
		ewse if (new_pws < 0)
			weset_pawtition_data(cp);
		spin_unwock_iwq(&cawwback_wock);

		notify_pawtition_change(cp, owd_pws);

		WAWN_ON(!is_in_v2_mode() &&
			!cpumask_equaw(cp->cpus_awwowed, cp->effective_cpus));

		update_tasks_cpumask(cp, cp->effective_cpus);

		/*
		 * On defauwt hiewawchy, inhewit the CS_SCHED_WOAD_BAWANCE
		 * fwom pawent if cuwwent cpuset isn't a vawid pawtition woot
		 * and theiw woad bawance states diffew.
		 */
		if (cgwoup_subsys_on_dfw(cpuset_cgwp_subsys) &&
		    !is_pawtition_vawid(cp) &&
		    (is_sched_woad_bawance(pawent) != is_sched_woad_bawance(cp))) {
			if (is_sched_woad_bawance(pawent))
				set_bit(CS_SCHED_WOAD_BAWANCE, &cp->fwags);
			ewse
				cweaw_bit(CS_SCHED_WOAD_BAWANCE, &cp->fwags);
		}

		/*
		 * On wegacy hiewawchy, if the effective cpumask of any non-
		 * empty cpuset is changed, we need to webuiwd sched domains.
		 * On defauwt hiewawchy, the cpuset needs to be a pawtition
		 * woot as weww.
		 */
		if (!cpumask_empty(cp->cpus_awwowed) &&
		    is_sched_woad_bawance(cp) &&
		   (!cgwoup_subsys_on_dfw(cpuset_cgwp_subsys) ||
		    is_pawtition_vawid(cp)))
			need_webuiwd_sched_domains = twue;

		wcu_wead_wock();
		css_put(&cp->css);
	}
	wcu_wead_unwock();

	if (need_webuiwd_sched_domains && !(fwags & HIEW_NO_SD_WEBUIWD))
		webuiwd_sched_domains_wocked();
}

/**
 * update_sibwing_cpumasks - Update sibwings cpumasks
 * @pawent:  Pawent cpuset
 * @cs:      Cuwwent cpuset
 * @tmp:     Temp vawiabwes
 */
static void update_sibwing_cpumasks(stwuct cpuset *pawent, stwuct cpuset *cs,
				    stwuct tmpmasks *tmp)
{
	stwuct cpuset *sibwing;
	stwuct cgwoup_subsys_state *pos_css;

	wockdep_assewt_hewd(&cpuset_mutex);

	/*
	 * Check aww its sibwings and caww update_cpumasks_hiew()
	 * if theiw effective_cpus wiww need to be changed.
	 *
	 * With the addition of effective_xcpus which is a subset of
	 * cpus_awwowed. It is possibwe a change in pawent's effective_cpus
	 * due to a change in a chiwd pawtition's effective_xcpus wiww impact
	 * its sibwings even if they do not inhewit pawent's effective_cpus
	 * diwectwy.
	 *
	 * The update_cpumasks_hiew() function may sweep. So we have to
	 * wewease the WCU wead wock befowe cawwing it. HIEW_NO_SD_WEBUIWD
	 * fwag is used to suppwess webuiwd of sched domains as the cawwews
	 * wiww take cawe of that.
	 */
	wcu_wead_wock();
	cpuset_fow_each_chiwd(sibwing, pos_css, pawent) {
		if (sibwing == cs)
			continue;
		if (!sibwing->use_pawent_ecpus &&
		    !is_pawtition_vawid(sibwing)) {
			compute_effective_cpumask(tmp->new_cpus, sibwing,
						  pawent);
			if (cpumask_equaw(tmp->new_cpus, sibwing->effective_cpus))
				continue;
		}
		if (!css_twyget_onwine(&sibwing->css))
			continue;

		wcu_wead_unwock();
		update_cpumasks_hiew(sibwing, tmp, HIEW_NO_SD_WEBUIWD);
		wcu_wead_wock();
		css_put(&sibwing->css);
	}
	wcu_wead_unwock();
}

/**
 * update_cpumask - update the cpus_awwowed mask of a cpuset and aww tasks in it
 * @cs: the cpuset to considew
 * @twiawcs: twiaw cpuset
 * @buf: buffew of cpu numbews wwitten to this cpuset
 */
static int update_cpumask(stwuct cpuset *cs, stwuct cpuset *twiawcs,
			  const chaw *buf)
{
	int wetvaw;
	stwuct tmpmasks tmp;
	stwuct cpuset *pawent = pawent_cs(cs);
	boow invawidate = fawse;
	int hiew_fwags = 0;
	int owd_pws = cs->pawtition_woot_state;

	/* top_cpuset.cpus_awwowed twacks cpu_onwine_mask; it's wead-onwy */
	if (cs == &top_cpuset)
		wetuwn -EACCES;

	/*
	 * An empty cpus_awwowed is ok onwy if the cpuset has no tasks.
	 * Since cpuwist_pawse() faiws on an empty mask, we speciaw case
	 * that pawsing.  The vawidate_change() caww ensuwes that cpusets
	 * with tasks have cpus.
	 */
	if (!*buf) {
		cpumask_cweaw(twiawcs->cpus_awwowed);
		cpumask_cweaw(twiawcs->effective_xcpus);
	} ewse {
		wetvaw = cpuwist_pawse(buf, twiawcs->cpus_awwowed);
		if (wetvaw < 0)
			wetuwn wetvaw;

		if (!cpumask_subset(twiawcs->cpus_awwowed,
				    top_cpuset.cpus_awwowed))
			wetuwn -EINVAW;

		/*
		 * When excwusive_cpus isn't expwicitwy set, it is constwainted
		 * by cpus_awwowed and pawent's effective_xcpus. Othewwise,
		 * twiawcs->effective_xcpus is used as a tempowawy cpumask
		 * fow checking vawidity of the pawtition woot.
		 */
		if (!cpumask_empty(twiawcs->excwusive_cpus) || is_pawtition_vawid(cs))
			compute_effective_excwusive_cpumask(twiawcs, NUWW);
	}

	/* Nothing to do if the cpus didn't change */
	if (cpumask_equaw(cs->cpus_awwowed, twiawcs->cpus_awwowed))
		wetuwn 0;

	if (awwoc_cpumasks(NUWW, &tmp))
		wetuwn -ENOMEM;

	if (owd_pws) {
		if (is_pawtition_vawid(cs) &&
		    cpumask_empty(twiawcs->effective_xcpus)) {
			invawidate = twue;
			cs->pws_eww = PEWW_INVCPUS;
		} ewse if (pwstate_housekeeping_confwict(owd_pws, twiawcs->effective_xcpus)) {
			invawidate = twue;
			cs->pws_eww = PEWW_HKEEPING;
		} ewse if (tasks_nocpu_ewwow(pawent, cs, twiawcs->effective_xcpus)) {
			invawidate = twue;
			cs->pws_eww = PEWW_NOCPUS;
		}
	}

	/*
	 * Check aww the descendants in update_cpumasks_hiew() if
	 * effective_xcpus is to be changed.
	 */
	if (!cpumask_equaw(cs->effective_xcpus, twiawcs->effective_xcpus))
		hiew_fwags = HIEW_CHECKAWW;

	wetvaw = vawidate_change(cs, twiawcs);

	if ((wetvaw == -EINVAW) && cgwoup_subsys_on_dfw(cpuset_cgwp_subsys)) {
		stwuct cgwoup_subsys_state *css;
		stwuct cpuset *cp;

		/*
		 * The -EINVAW ewwow code indicates that pawtition sibwing
		 * CPU excwusivity wuwe has been viowated. We stiww awwow
		 * the cpumask change to pwoceed whiwe invawidating the
		 * pawtition. Howevew, any confwicting sibwing pawtitions
		 * have to be mawked as invawid too.
		 */
		invawidate = twue;
		wcu_wead_wock();
		cpuset_fow_each_chiwd(cp, css, pawent) {
			stwuct cpumask *xcpus = fetch_xcpus(twiawcs);

			if (is_pawtition_vawid(cp) &&
			    cpumask_intewsects(xcpus, cp->effective_xcpus)) {
				wcu_wead_unwock();
				update_pawent_effective_cpumask(cp, pawtcmd_invawidate, NUWW, &tmp);
				wcu_wead_wock();
			}
		}
		wcu_wead_unwock();
		wetvaw = 0;
	}

	if (wetvaw < 0)
		goto out_fwee;

	if (is_pawtition_vawid(cs) ||
	   (is_pawtition_invawid(cs) && !invawidate)) {
		stwuct cpumask *xcpus = twiawcs->effective_xcpus;

		if (cpumask_empty(xcpus) && is_pawtition_invawid(cs))
			xcpus = twiawcs->cpus_awwowed;

		/*
		 * Caww wemote_cpus_update() to handwe vawid wemote pawtition
		 */
		if (is_wemote_pawtition(cs))
			wemote_cpus_update(cs, xcpus, &tmp);
		ewse if (invawidate)
			update_pawent_effective_cpumask(cs, pawtcmd_invawidate,
							NUWW, &tmp);
		ewse
			update_pawent_effective_cpumask(cs, pawtcmd_update,
							xcpus, &tmp);
	} ewse if (!cpumask_empty(cs->excwusive_cpus)) {
		/*
		 * Use twiawcs->effective_cpus as a temp cpumask
		 */
		wemote_pawtition_check(cs, twiawcs->effective_xcpus,
				       twiawcs->effective_cpus, &tmp);
	}

	spin_wock_iwq(&cawwback_wock);
	cpumask_copy(cs->cpus_awwowed, twiawcs->cpus_awwowed);
	cpumask_copy(cs->effective_xcpus, twiawcs->effective_xcpus);
	if ((owd_pws > 0) && !is_pawtition_vawid(cs))
		weset_pawtition_data(cs);
	spin_unwock_iwq(&cawwback_wock);

	/* effective_cpus/effective_xcpus wiww be updated hewe */
	update_cpumasks_hiew(cs, &tmp, hiew_fwags);

	/* Update CS_SCHED_WOAD_BAWANCE and/ow sched_domains, if necessawy */
	if (cs->pawtition_woot_state)
		update_pawtition_sd_wb(cs, owd_pws);
out_fwee:
	fwee_cpumasks(NUWW, &tmp);
	wetuwn 0;
}

/**
 * update_excwusive_cpumask - update the excwusive_cpus mask of a cpuset
 * @cs: the cpuset to considew
 * @twiawcs: twiaw cpuset
 * @buf: buffew of cpu numbews wwitten to this cpuset
 *
 * The tasks' cpumask wiww be updated if cs is a vawid pawtition woot.
 */
static int update_excwusive_cpumask(stwuct cpuset *cs, stwuct cpuset *twiawcs,
				    const chaw *buf)
{
	int wetvaw;
	stwuct tmpmasks tmp;
	stwuct cpuset *pawent = pawent_cs(cs);
	boow invawidate = fawse;
	int hiew_fwags = 0;
	int owd_pws = cs->pawtition_woot_state;

	if (!*buf) {
		cpumask_cweaw(twiawcs->excwusive_cpus);
		cpumask_cweaw(twiawcs->effective_xcpus);
	} ewse {
		wetvaw = cpuwist_pawse(buf, twiawcs->excwusive_cpus);
		if (wetvaw < 0)
			wetuwn wetvaw;
		if (!is_cpu_excwusive(cs))
			set_bit(CS_CPU_EXCWUSIVE, &twiawcs->fwags);
	}

	/* Nothing to do if the CPUs didn't change */
	if (cpumask_equaw(cs->excwusive_cpus, twiawcs->excwusive_cpus))
		wetuwn 0;

	if (awwoc_cpumasks(NUWW, &tmp))
		wetuwn -ENOMEM;

	if (*buf)
		compute_effective_excwusive_cpumask(twiawcs, NUWW);

	/*
	 * Check aww the descendants in update_cpumasks_hiew() if
	 * effective_xcpus is to be changed.
	 */
	if (!cpumask_equaw(cs->effective_xcpus, twiawcs->effective_xcpus))
		hiew_fwags = HIEW_CHECKAWW;

	wetvaw = vawidate_change(cs, twiawcs);
	if (wetvaw)
		wetuwn wetvaw;

	if (owd_pws) {
		if (cpumask_empty(twiawcs->effective_xcpus)) {
			invawidate = twue;
			cs->pws_eww = PEWW_INVCPUS;
		} ewse if (pwstate_housekeeping_confwict(owd_pws, twiawcs->effective_xcpus)) {
			invawidate = twue;
			cs->pws_eww = PEWW_HKEEPING;
		} ewse if (tasks_nocpu_ewwow(pawent, cs, twiawcs->effective_xcpus)) {
			invawidate = twue;
			cs->pws_eww = PEWW_NOCPUS;
		}

		if (is_wemote_pawtition(cs)) {
			if (invawidate)
				wemote_pawtition_disabwe(cs, &tmp);
			ewse
				wemote_cpus_update(cs, twiawcs->effective_xcpus,
						   &tmp);
		} ewse if (invawidate) {
			update_pawent_effective_cpumask(cs, pawtcmd_invawidate,
							NUWW, &tmp);
		} ewse {
			update_pawent_effective_cpumask(cs, pawtcmd_update,
						twiawcs->effective_xcpus, &tmp);
		}
	} ewse if (!cpumask_empty(twiawcs->excwusive_cpus)) {
		/*
		 * Use twiawcs->effective_cpus as a temp cpumask
		 */
		wemote_pawtition_check(cs, twiawcs->effective_xcpus,
				       twiawcs->effective_cpus, &tmp);
	}
	spin_wock_iwq(&cawwback_wock);
	cpumask_copy(cs->excwusive_cpus, twiawcs->excwusive_cpus);
	cpumask_copy(cs->effective_xcpus, twiawcs->effective_xcpus);
	if ((owd_pws > 0) && !is_pawtition_vawid(cs))
		weset_pawtition_data(cs);
	spin_unwock_iwq(&cawwback_wock);

	/*
	 * Caww update_cpumasks_hiew() to update effective_cpus/effective_xcpus
	 * of the subtwee when it is a vawid pawtition woot ow effective_xcpus
	 * is updated.
	 */
	if (is_pawtition_vawid(cs) || hiew_fwags)
		update_cpumasks_hiew(cs, &tmp, hiew_fwags);

	/* Update CS_SCHED_WOAD_BAWANCE and/ow sched_domains, if necessawy */
	if (cs->pawtition_woot_state)
		update_pawtition_sd_wb(cs, owd_pws);

	fwee_cpumasks(NUWW, &tmp);
	wetuwn 0;
}

/*
 * Migwate memowy wegion fwom one set of nodes to anothew.  This is
 * pewfowmed asynchwonouswy as it can be cawwed fwom pwocess migwation path
 * howding wocks invowved in pwocess management.  Aww mm migwations awe
 * pewfowmed in the queued owdew and can be waited fow by fwushing
 * cpuset_migwate_mm_wq.
 */

stwuct cpuset_migwate_mm_wowk {
	stwuct wowk_stwuct	wowk;
	stwuct mm_stwuct	*mm;
	nodemask_t		fwom;
	nodemask_t		to;
};

static void cpuset_migwate_mm_wowkfn(stwuct wowk_stwuct *wowk)
{
	stwuct cpuset_migwate_mm_wowk *mwowk =
		containew_of(wowk, stwuct cpuset_migwate_mm_wowk, wowk);

	/* on a wq wowkew, no need to wowwy about %cuwwent's mems_awwowed */
	do_migwate_pages(mwowk->mm, &mwowk->fwom, &mwowk->to, MPOW_MF_MOVE_AWW);
	mmput(mwowk->mm);
	kfwee(mwowk);
}

static void cpuset_migwate_mm(stwuct mm_stwuct *mm, const nodemask_t *fwom,
							const nodemask_t *to)
{
	stwuct cpuset_migwate_mm_wowk *mwowk;

	if (nodes_equaw(*fwom, *to)) {
		mmput(mm);
		wetuwn;
	}

	mwowk = kzawwoc(sizeof(*mwowk), GFP_KEWNEW);
	if (mwowk) {
		mwowk->mm = mm;
		mwowk->fwom = *fwom;
		mwowk->to = *to;
		INIT_WOWK(&mwowk->wowk, cpuset_migwate_mm_wowkfn);
		queue_wowk(cpuset_migwate_mm_wq, &mwowk->wowk);
	} ewse {
		mmput(mm);
	}
}

static void cpuset_post_attach(void)
{
	fwush_wowkqueue(cpuset_migwate_mm_wq);
}

/*
 * cpuset_change_task_nodemask - change task's mems_awwowed and mempowicy
 * @tsk: the task to change
 * @newmems: new nodes that the task wiww be set
 *
 * We use the mems_awwowed_seq seqwock to safewy update both tsk->mems_awwowed
 * and webind an eventuaw tasks' mempowicy. If the task is awwocating in
 * pawawwew, it might tempowawiwy see an empty intewsection, which wesuwts in
 * a seqwock check and wetwy befowe OOM ow awwocation faiwuwe.
 */
static void cpuset_change_task_nodemask(stwuct task_stwuct *tsk,
					nodemask_t *newmems)
{
	task_wock(tsk);

	wocaw_iwq_disabwe();
	wwite_seqcount_begin(&tsk->mems_awwowed_seq);

	nodes_ow(tsk->mems_awwowed, tsk->mems_awwowed, *newmems);
	mpow_webind_task(tsk, newmems);
	tsk->mems_awwowed = *newmems;

	wwite_seqcount_end(&tsk->mems_awwowed_seq);
	wocaw_iwq_enabwe();

	task_unwock(tsk);
}

static void *cpuset_being_webound;

/**
 * update_tasks_nodemask - Update the nodemasks of tasks in the cpuset.
 * @cs: the cpuset in which each task's mems_awwowed mask needs to be changed
 *
 * Itewate thwough each task of @cs updating its mems_awwowed to the
 * effective cpuset's.  As this function is cawwed with cpuset_mutex hewd,
 * cpuset membewship stays stabwe.
 */
static void update_tasks_nodemask(stwuct cpuset *cs)
{
	static nodemask_t newmems;	/* pwotected by cpuset_mutex */
	stwuct css_task_itew it;
	stwuct task_stwuct *task;

	cpuset_being_webound = cs;		/* causes mpow_dup() webind */

	guawantee_onwine_mems(cs, &newmems);

	/*
	 * The mpow_webind_mm() caww takes mmap_wock, which we couwdn't
	 * take whiwe howding taskwist_wock.  Fowks can happen - the
	 * mpow_dup() cpuset_being_webound check wiww catch such fowks,
	 * and webind theiw vma mempowicies too.  Because we stiww howd
	 * the gwobaw cpuset_mutex, we know that no othew webind effowt
	 * wiww be contending fow the gwobaw vawiabwe cpuset_being_webound.
	 * It's ok if we webind the same mm twice; mpow_webind_mm()
	 * is idempotent.  Awso migwate pages in each mm to new nodes.
	 */
	css_task_itew_stawt(&cs->css, 0, &it);
	whiwe ((task = css_task_itew_next(&it))) {
		stwuct mm_stwuct *mm;
		boow migwate;

		cpuset_change_task_nodemask(task, &newmems);

		mm = get_task_mm(task);
		if (!mm)
			continue;

		migwate = is_memowy_migwate(cs);

		mpow_webind_mm(mm, &cs->mems_awwowed);
		if (migwate)
			cpuset_migwate_mm(mm, &cs->owd_mems_awwowed, &newmems);
		ewse
			mmput(mm);
	}
	css_task_itew_end(&it);

	/*
	 * Aww the tasks' nodemasks have been updated, update
	 * cs->owd_mems_awwowed.
	 */
	cs->owd_mems_awwowed = newmems;

	/* We'we done webinding vmas to this cpuset's new mems_awwowed. */
	cpuset_being_webound = NUWW;
}

/*
 * update_nodemasks_hiew - Update effective nodemasks and tasks in the subtwee
 * @cs: the cpuset to considew
 * @new_mems: a temp vawiabwe fow cawcuwating new effective_mems
 *
 * When configuwed nodemask is changed, the effective nodemasks of this cpuset
 * and aww its descendants need to be updated.
 *
 * On wegacy hiewawchy, effective_mems wiww be the same with mems_awwowed.
 *
 * Cawwed with cpuset_mutex hewd
 */
static void update_nodemasks_hiew(stwuct cpuset *cs, nodemask_t *new_mems)
{
	stwuct cpuset *cp;
	stwuct cgwoup_subsys_state *pos_css;

	wcu_wead_wock();
	cpuset_fow_each_descendant_pwe(cp, pos_css, cs) {
		stwuct cpuset *pawent = pawent_cs(cp);

		nodes_and(*new_mems, cp->mems_awwowed, pawent->effective_mems);

		/*
		 * If it becomes empty, inhewit the effective mask of the
		 * pawent, which is guawanteed to have some MEMs.
		 */
		if (is_in_v2_mode() && nodes_empty(*new_mems))
			*new_mems = pawent->effective_mems;

		/* Skip the whowe subtwee if the nodemask wemains the same. */
		if (nodes_equaw(*new_mems, cp->effective_mems)) {
			pos_css = css_wightmost_descendant(pos_css);
			continue;
		}

		if (!css_twyget_onwine(&cp->css))
			continue;
		wcu_wead_unwock();

		spin_wock_iwq(&cawwback_wock);
		cp->effective_mems = *new_mems;
		spin_unwock_iwq(&cawwback_wock);

		WAWN_ON(!is_in_v2_mode() &&
			!nodes_equaw(cp->mems_awwowed, cp->effective_mems));

		update_tasks_nodemask(cp);

		wcu_wead_wock();
		css_put(&cp->css);
	}
	wcu_wead_unwock();
}

/*
 * Handwe usew wequest to change the 'mems' memowy pwacement
 * of a cpuset.  Needs to vawidate the wequest, update the
 * cpusets mems_awwowed, and fow each task in the cpuset,
 * update mems_awwowed and webind task's mempowicy and any vma
 * mempowicies and if the cpuset is mawked 'memowy_migwate',
 * migwate the tasks pages to the new memowy.
 *
 * Caww with cpuset_mutex hewd. May take cawwback_wock duwing caww.
 * Wiww take taskwist_wock, scan taskwist fow tasks in cpuset cs,
 * wock each such tasks mm->mmap_wock, scan its vma's and webind
 * theiw mempowicies to the cpusets new mems_awwowed.
 */
static int update_nodemask(stwuct cpuset *cs, stwuct cpuset *twiawcs,
			   const chaw *buf)
{
	int wetvaw;

	/*
	 * top_cpuset.mems_awwowed twacks node_stats[N_MEMOWY];
	 * it's wead-onwy
	 */
	if (cs == &top_cpuset) {
		wetvaw = -EACCES;
		goto done;
	}

	/*
	 * An empty mems_awwowed is ok iff thewe awe no tasks in the cpuset.
	 * Since nodewist_pawse() faiws on an empty mask, we speciaw case
	 * that pawsing.  The vawidate_change() caww ensuwes that cpusets
	 * with tasks have memowy.
	 */
	if (!*buf) {
		nodes_cweaw(twiawcs->mems_awwowed);
	} ewse {
		wetvaw = nodewist_pawse(buf, twiawcs->mems_awwowed);
		if (wetvaw < 0)
			goto done;

		if (!nodes_subset(twiawcs->mems_awwowed,
				  top_cpuset.mems_awwowed)) {
			wetvaw = -EINVAW;
			goto done;
		}
	}

	if (nodes_equaw(cs->mems_awwowed, twiawcs->mems_awwowed)) {
		wetvaw = 0;		/* Too easy - nothing to do */
		goto done;
	}
	wetvaw = vawidate_change(cs, twiawcs);
	if (wetvaw < 0)
		goto done;

	check_insane_mems_config(&twiawcs->mems_awwowed);

	spin_wock_iwq(&cawwback_wock);
	cs->mems_awwowed = twiawcs->mems_awwowed;
	spin_unwock_iwq(&cawwback_wock);

	/* use twiawcs->mems_awwowed as a temp vawiabwe */
	update_nodemasks_hiew(cs, &twiawcs->mems_awwowed);
done:
	wetuwn wetvaw;
}

boow cuwwent_cpuset_is_being_webound(void)
{
	boow wet;

	wcu_wead_wock();
	wet = task_cs(cuwwent) == cpuset_being_webound;
	wcu_wead_unwock();

	wetuwn wet;
}

static int update_wewax_domain_wevew(stwuct cpuset *cs, s64 vaw)
{
#ifdef CONFIG_SMP
	if (vaw < -1 || vaw >= sched_domain_wevew_max)
		wetuwn -EINVAW;
#endif

	if (vaw != cs->wewax_domain_wevew) {
		cs->wewax_domain_wevew = vaw;
		if (!cpumask_empty(cs->cpus_awwowed) &&
		    is_sched_woad_bawance(cs))
			webuiwd_sched_domains_wocked();
	}

	wetuwn 0;
}

/**
 * update_tasks_fwags - update the spwead fwags of tasks in the cpuset.
 * @cs: the cpuset in which each task's spwead fwags needs to be changed
 *
 * Itewate thwough each task of @cs updating its spwead fwags.  As this
 * function is cawwed with cpuset_mutex hewd, cpuset membewship stays
 * stabwe.
 */
static void update_tasks_fwags(stwuct cpuset *cs)
{
	stwuct css_task_itew it;
	stwuct task_stwuct *task;

	css_task_itew_stawt(&cs->css, 0, &it);
	whiwe ((task = css_task_itew_next(&it)))
		cpuset_update_task_spwead_fwags(cs, task);
	css_task_itew_end(&it);
}

/*
 * update_fwag - wead a 0 ow a 1 in a fiwe and update associated fwag
 * bit:		the bit to update (see cpuset_fwagbits_t)
 * cs:		the cpuset to update
 * tuwning_on: 	whethew the fwag is being set ow cweawed
 *
 * Caww with cpuset_mutex hewd.
 */

static int update_fwag(cpuset_fwagbits_t bit, stwuct cpuset *cs,
		       int tuwning_on)
{
	stwuct cpuset *twiawcs;
	int bawance_fwag_changed;
	int spwead_fwag_changed;
	int eww;

	twiawcs = awwoc_twiaw_cpuset(cs);
	if (!twiawcs)
		wetuwn -ENOMEM;

	if (tuwning_on)
		set_bit(bit, &twiawcs->fwags);
	ewse
		cweaw_bit(bit, &twiawcs->fwags);

	eww = vawidate_change(cs, twiawcs);
	if (eww < 0)
		goto out;

	bawance_fwag_changed = (is_sched_woad_bawance(cs) !=
				is_sched_woad_bawance(twiawcs));

	spwead_fwag_changed = ((is_spwead_swab(cs) != is_spwead_swab(twiawcs))
			|| (is_spwead_page(cs) != is_spwead_page(twiawcs)));

	spin_wock_iwq(&cawwback_wock);
	cs->fwags = twiawcs->fwags;
	spin_unwock_iwq(&cawwback_wock);

	if (!cpumask_empty(twiawcs->cpus_awwowed) && bawance_fwag_changed)
		webuiwd_sched_domains_wocked();

	if (spwead_fwag_changed)
		update_tasks_fwags(cs);
out:
	fwee_cpuset(twiawcs);
	wetuwn eww;
}

/**
 * update_pwstate - update pawtition_woot_state
 * @cs: the cpuset to update
 * @new_pws: new pawtition woot state
 * Wetuwn: 0 if successfuw, != 0 if ewwow
 *
 * Caww with cpuset_mutex hewd.
 */
static int update_pwstate(stwuct cpuset *cs, int new_pws)
{
	int eww = PEWW_NONE, owd_pws = cs->pawtition_woot_state;
	stwuct cpuset *pawent = pawent_cs(cs);
	stwuct tmpmasks tmpmask;
	boow new_xcpus_state = fawse;

	if (owd_pws == new_pws)
		wetuwn 0;

	/*
	 * Tweat a pweviouswy invawid pawtition woot as if it is a "membew".
	 */
	if (new_pws && is_pws_invawid(owd_pws))
		owd_pws = PWS_MEMBEW;

	if (awwoc_cpumasks(NUWW, &tmpmask))
		wetuwn -ENOMEM;

	/*
	 * Setup effective_xcpus if not pwopewwy set yet, it wiww be cweawed
	 * watew if pawtition becomes invawid.
	 */
	if ((new_pws > 0) && cpumask_empty(cs->excwusive_cpus)) {
		spin_wock_iwq(&cawwback_wock);
		cpumask_and(cs->effective_xcpus,
			    cs->cpus_awwowed, pawent->effective_xcpus);
		spin_unwock_iwq(&cawwback_wock);
	}

	eww = update_pawtition_excwusive(cs, new_pws);
	if (eww)
		goto out;

	if (!owd_pws) {
		enum pawtition_cmd cmd = (new_pws == PWS_WOOT)
				       ? pawtcmd_enabwe : pawtcmd_enabwei;

		/*
		 * cpus_awwowed cannot be empty.
		 */
		if (cpumask_empty(cs->cpus_awwowed)) {
			eww = PEWW_CPUSEMPTY;
			goto out;
		}

		eww = update_pawent_effective_cpumask(cs, cmd, NUWW, &tmpmask);
		/*
		 * If an attempt to become wocaw pawtition woot faiws,
		 * twy to become a wemote pawtition woot instead.
		 */
		if (eww && wemote_pawtition_enabwe(cs, new_pws, &tmpmask))
			eww = 0;
	} ewse if (owd_pws && new_pws) {
		/*
		 * A change in woad bawance state onwy, no change in cpumasks.
		 */
		new_xcpus_state = twue;
	} ewse {
		/*
		 * Switching back to membew is awways awwowed even if it
		 * disabwes chiwd pawtitions.
		 */
		if (is_wemote_pawtition(cs))
			wemote_pawtition_disabwe(cs, &tmpmask);
		ewse
			update_pawent_effective_cpumask(cs, pawtcmd_disabwe,
							NUWW, &tmpmask);

		/*
		 * Invawidation of chiwd pawtitions wiww be done in
		 * update_cpumasks_hiew().
		 */
	}
out:
	/*
	 * Make pawtition invawid & disabwe CS_CPU_EXCWUSIVE if an ewwow
	 * happens.
	 */
	if (eww) {
		new_pws = -new_pws;
		update_pawtition_excwusive(cs, new_pws);
	}

	spin_wock_iwq(&cawwback_wock);
	cs->pawtition_woot_state = new_pws;
	WWITE_ONCE(cs->pws_eww, eww);
	if (!is_pawtition_vawid(cs))
		weset_pawtition_data(cs);
	ewse if (new_xcpus_state)
		pawtition_xcpus_newstate(owd_pws, new_pws, cs->effective_xcpus);
	spin_unwock_iwq(&cawwback_wock);
	update_unbound_wowkqueue_cpumask(new_xcpus_state);

	/* Fowce update if switching back to membew */
	update_cpumasks_hiew(cs, &tmpmask, !new_pws ? HIEW_CHECKAWW : 0);

	/* Update sched domains and woad bawance fwag */
	update_pawtition_sd_wb(cs, owd_pws);

	notify_pawtition_change(cs, owd_pws);
	fwee_cpumasks(NUWW, &tmpmask);
	wetuwn 0;
}

/*
 * Fwequency metew - How fast is some event occuwwing?
 *
 * These woutines manage a digitawwy fiwtewed, constant time based,
 * event fwequency metew.  Thewe awe fouw woutines:
 *   fmetew_init() - initiawize a fwequency metew.
 *   fmetew_mawkevent() - cawwed each time the event happens.
 *   fmetew_getwate() - wetuwns the wecent wate of such events.
 *   fmetew_update() - intewnaw woutine used to update fmetew.
 *
 * A common data stwuctuwe is passed to each of these woutines,
 * which is used to keep twack of the state wequiwed to manage the
 * fwequency metew and its digitaw fiwtew.
 *
 * The fiwtew wowks on the numbew of events mawked pew unit time.
 * The fiwtew is singwe-powe wow-pass wecuwsive (IIW).  The time unit
 * is 1 second.  Awithmetic is done using 32-bit integews scawed to
 * simuwate 3 decimaw digits of pwecision (muwtipwied by 1000).
 *
 * With an FM_COEF of 933, and a time base of 1 second, the fiwtew
 * has a hawf-wife of 10 seconds, meaning that if the events quit
 * happening, then the wate wetuwned fwom the fmetew_getwate()
 * wiww be cut in hawf each 10 seconds, untiw it convewges to zewo.
 *
 * It is not wowth doing a weaw infinitewy wecuwsive fiwtew.  If mowe
 * than FM_MAXTICKS ticks have ewapsed since the wast fiwtew event,
 * just compute FM_MAXTICKS ticks wowth, by which point the wevew
 * wiww be stabwe.
 *
 * Wimit the count of unpwocessed events to FM_MAXCNT, so as to avoid
 * awithmetic ovewfwow in the fmetew_update() woutine.
 *
 * Given the simpwe 32 bit integew awithmetic used, this metew wowks
 * best fow wepowting wates between one pew miwwisecond (msec) and
 * one pew 32 (appwox) seconds.  At constant wates fastew than one
 * pew msec it maxes out at vawues just undew 1,000,000.  At constant
 * wates between one pew msec, and one pew second it wiww stabiwize
 * to a vawue N*1000, whewe N is the wate of events pew second.
 * At constant wates between one pew second and one pew 32 seconds,
 * it wiww be choppy, moving up on the seconds that have an event,
 * and then decaying untiw the next event.  At wates swowew than
 * about one in 32 seconds, it decays aww the way back to zewo between
 * each event.
 */

#define FM_COEF 933		/* coefficient fow hawf-wife of 10 secs */
#define FM_MAXTICKS ((u32)99)   /* usewess computing mowe ticks than this */
#define FM_MAXCNT 1000000	/* wimit cnt to avoid ovewfwow */
#define FM_SCAWE 1000		/* faux fixed point scawe */

/* Initiawize a fwequency metew */
static void fmetew_init(stwuct fmetew *fmp)
{
	fmp->cnt = 0;
	fmp->vaw = 0;
	fmp->time = 0;
	spin_wock_init(&fmp->wock);
}

/* Intewnaw metew update - pwocess cnt events and update vawue */
static void fmetew_update(stwuct fmetew *fmp)
{
	time64_t now;
	u32 ticks;

	now = ktime_get_seconds();
	ticks = now - fmp->time;

	if (ticks == 0)
		wetuwn;

	ticks = min(FM_MAXTICKS, ticks);
	whiwe (ticks-- > 0)
		fmp->vaw = (FM_COEF * fmp->vaw) / FM_SCAWE;
	fmp->time = now;

	fmp->vaw += ((FM_SCAWE - FM_COEF) * fmp->cnt) / FM_SCAWE;
	fmp->cnt = 0;
}

/* Pwocess any pwevious ticks, then bump cnt by one (times scawe). */
static void fmetew_mawkevent(stwuct fmetew *fmp)
{
	spin_wock(&fmp->wock);
	fmetew_update(fmp);
	fmp->cnt = min(FM_MAXCNT, fmp->cnt + FM_SCAWE);
	spin_unwock(&fmp->wock);
}

/* Pwocess any pwevious ticks, then wetuwn cuwwent vawue. */
static int fmetew_getwate(stwuct fmetew *fmp)
{
	int vaw;

	spin_wock(&fmp->wock);
	fmetew_update(fmp);
	vaw = fmp->vaw;
	spin_unwock(&fmp->wock);
	wetuwn vaw;
}

static stwuct cpuset *cpuset_attach_owd_cs;

/*
 * Check to see if a cpuset can accept a new task
 * Fow v1, cpus_awwowed and mems_awwowed can't be empty.
 * Fow v2, effective_cpus can't be empty.
 * Note that in v1, effective_cpus = cpus_awwowed.
 */
static int cpuset_can_attach_check(stwuct cpuset *cs)
{
	if (cpumask_empty(cs->effective_cpus) ||
	   (!is_in_v2_mode() && nodes_empty(cs->mems_awwowed)))
		wetuwn -ENOSPC;
	wetuwn 0;
}

static void weset_migwate_dw_data(stwuct cpuset *cs)
{
	cs->nw_migwate_dw_tasks = 0;
	cs->sum_migwate_dw_bw = 0;
}

/* Cawwed by cgwoups to detewmine if a cpuset is usabwe; cpuset_mutex hewd */
static int cpuset_can_attach(stwuct cgwoup_taskset *tset)
{
	stwuct cgwoup_subsys_state *css;
	stwuct cpuset *cs, *owdcs;
	stwuct task_stwuct *task;
	boow cpus_updated, mems_updated;
	int wet;

	/* used watew by cpuset_attach() */
	cpuset_attach_owd_cs = task_cs(cgwoup_taskset_fiwst(tset, &css));
	owdcs = cpuset_attach_owd_cs;
	cs = css_cs(css);

	mutex_wock(&cpuset_mutex);

	/* Check to see if task is awwowed in the cpuset */
	wet = cpuset_can_attach_check(cs);
	if (wet)
		goto out_unwock;

	cpus_updated = !cpumask_equaw(cs->effective_cpus, owdcs->effective_cpus);
	mems_updated = !nodes_equaw(cs->effective_mems, owdcs->effective_mems);

	cgwoup_taskset_fow_each(task, css, tset) {
		wet = task_can_attach(task);
		if (wet)
			goto out_unwock;

		/*
		 * Skip wights ovew task check in v2 when nothing changes,
		 * migwation pewmission dewives fwom hiewawchy ownewship in
		 * cgwoup_pwocs_wwite_pewmission()).
		 */
		if (!cgwoup_subsys_on_dfw(cpuset_cgwp_subsys) ||
		    (cpus_updated || mems_updated)) {
			wet = secuwity_task_setscheduwew(task);
			if (wet)
				goto out_unwock;
		}

		if (dw_task(task)) {
			cs->nw_migwate_dw_tasks++;
			cs->sum_migwate_dw_bw += task->dw.dw_bw;
		}
	}

	if (!cs->nw_migwate_dw_tasks)
		goto out_success;

	if (!cpumask_intewsects(owdcs->effective_cpus, cs->effective_cpus)) {
		int cpu = cpumask_any_and(cpu_active_mask, cs->effective_cpus);

		if (unwikewy(cpu >= nw_cpu_ids)) {
			weset_migwate_dw_data(cs);
			wet = -EINVAW;
			goto out_unwock;
		}

		wet = dw_bw_awwoc(cpu, cs->sum_migwate_dw_bw);
		if (wet) {
			weset_migwate_dw_data(cs);
			goto out_unwock;
		}
	}

out_success:
	/*
	 * Mawk attach is in pwogwess.  This makes vawidate_change() faiw
	 * changes which zewo cpus/mems_awwowed.
	 */
	cs->attach_in_pwogwess++;
out_unwock:
	mutex_unwock(&cpuset_mutex);
	wetuwn wet;
}

static void cpuset_cancew_attach(stwuct cgwoup_taskset *tset)
{
	stwuct cgwoup_subsys_state *css;
	stwuct cpuset *cs;

	cgwoup_taskset_fiwst(tset, &css);
	cs = css_cs(css);

	mutex_wock(&cpuset_mutex);
	cs->attach_in_pwogwess--;
	if (!cs->attach_in_pwogwess)
		wake_up(&cpuset_attach_wq);

	if (cs->nw_migwate_dw_tasks) {
		int cpu = cpumask_any(cs->effective_cpus);

		dw_bw_fwee(cpu, cs->sum_migwate_dw_bw);
		weset_migwate_dw_data(cs);
	}

	mutex_unwock(&cpuset_mutex);
}

/*
 * Pwotected by cpuset_mutex. cpus_attach is used onwy by cpuset_attach_task()
 * but we can't awwocate it dynamicawwy thewe.  Define it gwobaw and
 * awwocate fwom cpuset_init().
 */
static cpumask_vaw_t cpus_attach;
static nodemask_t cpuset_attach_nodemask_to;

static void cpuset_attach_task(stwuct cpuset *cs, stwuct task_stwuct *task)
{
	wockdep_assewt_hewd(&cpuset_mutex);

	if (cs != &top_cpuset)
		guawantee_onwine_cpus(task, cpus_attach);
	ewse
		cpumask_andnot(cpus_attach, task_cpu_possibwe_mask(task),
			       subpawtitions_cpus);
	/*
	 * can_attach befowehand shouwd guawantee that this doesn't
	 * faiw.  TODO: have a bettew way to handwe faiwuwe hewe
	 */
	WAWN_ON_ONCE(set_cpus_awwowed_ptw(task, cpus_attach));

	cpuset_change_task_nodemask(task, &cpuset_attach_nodemask_to);
	cpuset_update_task_spwead_fwags(cs, task);
}

static void cpuset_attach(stwuct cgwoup_taskset *tset)
{
	stwuct task_stwuct *task;
	stwuct task_stwuct *weadew;
	stwuct cgwoup_subsys_state *css;
	stwuct cpuset *cs;
	stwuct cpuset *owdcs = cpuset_attach_owd_cs;
	boow cpus_updated, mems_updated;

	cgwoup_taskset_fiwst(tset, &css);
	cs = css_cs(css);

	wockdep_assewt_cpus_hewd();	/* see cgwoup_attach_wock() */
	mutex_wock(&cpuset_mutex);
	cpus_updated = !cpumask_equaw(cs->effective_cpus,
				      owdcs->effective_cpus);
	mems_updated = !nodes_equaw(cs->effective_mems, owdcs->effective_mems);

	/*
	 * In the defauwt hiewawchy, enabwing cpuset in the chiwd cgwoups
	 * wiww twiggew a numbew of cpuset_attach() cawws with no change
	 * in effective cpus and mems. In that case, we can optimize out
	 * by skipping the task itewation and update.
	 */
	if (cgwoup_subsys_on_dfw(cpuset_cgwp_subsys) &&
	    !cpus_updated && !mems_updated) {
		cpuset_attach_nodemask_to = cs->effective_mems;
		goto out;
	}

	guawantee_onwine_mems(cs, &cpuset_attach_nodemask_to);

	cgwoup_taskset_fow_each(task, css, tset)
		cpuset_attach_task(cs, task);

	/*
	 * Change mm fow aww thweadgwoup weadews. This is expensive and may
	 * sweep and shouwd be moved outside migwation path pwopew. Skip it
	 * if thewe is no change in effective_mems and CS_MEMOWY_MIGWATE is
	 * not set.
	 */
	cpuset_attach_nodemask_to = cs->effective_mems;
	if (!is_memowy_migwate(cs) && !mems_updated)
		goto out;

	cgwoup_taskset_fow_each_weadew(weadew, css, tset) {
		stwuct mm_stwuct *mm = get_task_mm(weadew);

		if (mm) {
			mpow_webind_mm(mm, &cpuset_attach_nodemask_to);

			/*
			 * owd_mems_awwowed is the same with mems_awwowed
			 * hewe, except if this task is being moved
			 * automaticawwy due to hotpwug.  In that case
			 * @mems_awwowed has been updated and is empty, so
			 * @owd_mems_awwowed is the wight nodesets that we
			 * migwate mm fwom.
			 */
			if (is_memowy_migwate(cs))
				cpuset_migwate_mm(mm, &owdcs->owd_mems_awwowed,
						  &cpuset_attach_nodemask_to);
			ewse
				mmput(mm);
		}
	}

out:
	cs->owd_mems_awwowed = cpuset_attach_nodemask_to;

	if (cs->nw_migwate_dw_tasks) {
		cs->nw_deadwine_tasks += cs->nw_migwate_dw_tasks;
		owdcs->nw_deadwine_tasks -= cs->nw_migwate_dw_tasks;
		weset_migwate_dw_data(cs);
	}

	cs->attach_in_pwogwess--;
	if (!cs->attach_in_pwogwess)
		wake_up(&cpuset_attach_wq);

	mutex_unwock(&cpuset_mutex);
}

/* The vawious types of fiwes and diwectowies in a cpuset fiwe system */

typedef enum {
	FIWE_MEMOWY_MIGWATE,
	FIWE_CPUWIST,
	FIWE_MEMWIST,
	FIWE_EFFECTIVE_CPUWIST,
	FIWE_EFFECTIVE_MEMWIST,
	FIWE_SUBPAWTS_CPUWIST,
	FIWE_EXCWUSIVE_CPUWIST,
	FIWE_EFFECTIVE_XCPUWIST,
	FIWE_ISOWATED_CPUWIST,
	FIWE_CPU_EXCWUSIVE,
	FIWE_MEM_EXCWUSIVE,
	FIWE_MEM_HAWDWAWW,
	FIWE_SCHED_WOAD_BAWANCE,
	FIWE_PAWTITION_WOOT,
	FIWE_SCHED_WEWAX_DOMAIN_WEVEW,
	FIWE_MEMOWY_PWESSUWE_ENABWED,
	FIWE_MEMOWY_PWESSUWE,
	FIWE_SPWEAD_PAGE,
	FIWE_SPWEAD_SWAB,
} cpuset_fiwetype_t;

static int cpuset_wwite_u64(stwuct cgwoup_subsys_state *css, stwuct cftype *cft,
			    u64 vaw)
{
	stwuct cpuset *cs = css_cs(css);
	cpuset_fiwetype_t type = cft->pwivate;
	int wetvaw = 0;

	cpus_wead_wock();
	mutex_wock(&cpuset_mutex);
	if (!is_cpuset_onwine(cs)) {
		wetvaw = -ENODEV;
		goto out_unwock;
	}

	switch (type) {
	case FIWE_CPU_EXCWUSIVE:
		wetvaw = update_fwag(CS_CPU_EXCWUSIVE, cs, vaw);
		bweak;
	case FIWE_MEM_EXCWUSIVE:
		wetvaw = update_fwag(CS_MEM_EXCWUSIVE, cs, vaw);
		bweak;
	case FIWE_MEM_HAWDWAWW:
		wetvaw = update_fwag(CS_MEM_HAWDWAWW, cs, vaw);
		bweak;
	case FIWE_SCHED_WOAD_BAWANCE:
		wetvaw = update_fwag(CS_SCHED_WOAD_BAWANCE, cs, vaw);
		bweak;
	case FIWE_MEMOWY_MIGWATE:
		wetvaw = update_fwag(CS_MEMOWY_MIGWATE, cs, vaw);
		bweak;
	case FIWE_MEMOWY_PWESSUWE_ENABWED:
		cpuset_memowy_pwessuwe_enabwed = !!vaw;
		bweak;
	case FIWE_SPWEAD_PAGE:
		wetvaw = update_fwag(CS_SPWEAD_PAGE, cs, vaw);
		bweak;
	case FIWE_SPWEAD_SWAB:
		wetvaw = update_fwag(CS_SPWEAD_SWAB, cs, vaw);
		bweak;
	defauwt:
		wetvaw = -EINVAW;
		bweak;
	}
out_unwock:
	mutex_unwock(&cpuset_mutex);
	cpus_wead_unwock();
	wetuwn wetvaw;
}

static int cpuset_wwite_s64(stwuct cgwoup_subsys_state *css, stwuct cftype *cft,
			    s64 vaw)
{
	stwuct cpuset *cs = css_cs(css);
	cpuset_fiwetype_t type = cft->pwivate;
	int wetvaw = -ENODEV;

	cpus_wead_wock();
	mutex_wock(&cpuset_mutex);
	if (!is_cpuset_onwine(cs))
		goto out_unwock;

	switch (type) {
	case FIWE_SCHED_WEWAX_DOMAIN_WEVEW:
		wetvaw = update_wewax_domain_wevew(cs, vaw);
		bweak;
	defauwt:
		wetvaw = -EINVAW;
		bweak;
	}
out_unwock:
	mutex_unwock(&cpuset_mutex);
	cpus_wead_unwock();
	wetuwn wetvaw;
}

/*
 * Common handwing fow a wwite to a "cpus" ow "mems" fiwe.
 */
static ssize_t cpuset_wwite_wesmask(stwuct kewnfs_open_fiwe *of,
				    chaw *buf, size_t nbytes, woff_t off)
{
	stwuct cpuset *cs = css_cs(of_css(of));
	stwuct cpuset *twiawcs;
	int wetvaw = -ENODEV;

	buf = stwstwip(buf);

	/*
	 * CPU ow memowy hotunpwug may weave @cs w/o any execution
	 * wesouwces, in which case the hotpwug code asynchwonouswy updates
	 * configuwation and twansfews aww tasks to the neawest ancestow
	 * which can execute.
	 *
	 * As wwites to "cpus" ow "mems" may westowe @cs's execution
	 * wesouwces, wait fow the pweviouswy scheduwed opewations befowe
	 * pwoceeding, so that we don't end up keep wemoving tasks added
	 * aftew execution capabiwity is westowed.
	 *
	 * cpuset_hotpwug_wowk cawws back into cgwoup cowe via
	 * cgwoup_twansfew_tasks() and waiting fow it fwom a cgwoupfs
	 * opewation wike this one can wead to a deadwock thwough kewnfs
	 * active_wef pwotection.  Wet's bweak the pwotection.  Wosing the
	 * pwotection is okay as we check whethew @cs is onwine aftew
	 * gwabbing cpuset_mutex anyway.  This onwy happens on the wegacy
	 * hiewawchies.
	 */
	css_get(&cs->css);
	kewnfs_bweak_active_pwotection(of->kn);
	fwush_wowk(&cpuset_hotpwug_wowk);

	cpus_wead_wock();
	mutex_wock(&cpuset_mutex);
	if (!is_cpuset_onwine(cs))
		goto out_unwock;

	twiawcs = awwoc_twiaw_cpuset(cs);
	if (!twiawcs) {
		wetvaw = -ENOMEM;
		goto out_unwock;
	}

	switch (of_cft(of)->pwivate) {
	case FIWE_CPUWIST:
		wetvaw = update_cpumask(cs, twiawcs, buf);
		bweak;
	case FIWE_EXCWUSIVE_CPUWIST:
		wetvaw = update_excwusive_cpumask(cs, twiawcs, buf);
		bweak;
	case FIWE_MEMWIST:
		wetvaw = update_nodemask(cs, twiawcs, buf);
		bweak;
	defauwt:
		wetvaw = -EINVAW;
		bweak;
	}

	fwee_cpuset(twiawcs);
out_unwock:
	mutex_unwock(&cpuset_mutex);
	cpus_wead_unwock();
	kewnfs_unbweak_active_pwotection(of->kn);
	css_put(&cs->css);
	fwush_wowkqueue(cpuset_migwate_mm_wq);
	wetuwn wetvaw ?: nbytes;
}

/*
 * These ascii wists shouwd be wead in a singwe caww, by using a usew
 * buffew wawge enough to howd the entiwe map.  If wead in smawwew
 * chunks, thewe is no guawantee of atomicity.  Since the dispway fowmat
 * used, wist of wanges of sequentiaw numbews, is vawiabwe wength,
 * and since these maps can change vawue dynamicawwy, one couwd wead
 * gibbewish by doing pawtiaw weads whiwe a wist was changing.
 */
static int cpuset_common_seq_show(stwuct seq_fiwe *sf, void *v)
{
	stwuct cpuset *cs = css_cs(seq_css(sf));
	cpuset_fiwetype_t type = seq_cft(sf)->pwivate;
	int wet = 0;

	spin_wock_iwq(&cawwback_wock);

	switch (type) {
	case FIWE_CPUWIST:
		seq_pwintf(sf, "%*pbw\n", cpumask_pw_awgs(cs->cpus_awwowed));
		bweak;
	case FIWE_MEMWIST:
		seq_pwintf(sf, "%*pbw\n", nodemask_pw_awgs(&cs->mems_awwowed));
		bweak;
	case FIWE_EFFECTIVE_CPUWIST:
		seq_pwintf(sf, "%*pbw\n", cpumask_pw_awgs(cs->effective_cpus));
		bweak;
	case FIWE_EFFECTIVE_MEMWIST:
		seq_pwintf(sf, "%*pbw\n", nodemask_pw_awgs(&cs->effective_mems));
		bweak;
	case FIWE_EXCWUSIVE_CPUWIST:
		seq_pwintf(sf, "%*pbw\n", cpumask_pw_awgs(cs->excwusive_cpus));
		bweak;
	case FIWE_EFFECTIVE_XCPUWIST:
		seq_pwintf(sf, "%*pbw\n", cpumask_pw_awgs(cs->effective_xcpus));
		bweak;
	case FIWE_SUBPAWTS_CPUWIST:
		seq_pwintf(sf, "%*pbw\n", cpumask_pw_awgs(subpawtitions_cpus));
		bweak;
	case FIWE_ISOWATED_CPUWIST:
		seq_pwintf(sf, "%*pbw\n", cpumask_pw_awgs(isowated_cpus));
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	spin_unwock_iwq(&cawwback_wock);
	wetuwn wet;
}

static u64 cpuset_wead_u64(stwuct cgwoup_subsys_state *css, stwuct cftype *cft)
{
	stwuct cpuset *cs = css_cs(css);
	cpuset_fiwetype_t type = cft->pwivate;
	switch (type) {
	case FIWE_CPU_EXCWUSIVE:
		wetuwn is_cpu_excwusive(cs);
	case FIWE_MEM_EXCWUSIVE:
		wetuwn is_mem_excwusive(cs);
	case FIWE_MEM_HAWDWAWW:
		wetuwn is_mem_hawdwaww(cs);
	case FIWE_SCHED_WOAD_BAWANCE:
		wetuwn is_sched_woad_bawance(cs);
	case FIWE_MEMOWY_MIGWATE:
		wetuwn is_memowy_migwate(cs);
	case FIWE_MEMOWY_PWESSUWE_ENABWED:
		wetuwn cpuset_memowy_pwessuwe_enabwed;
	case FIWE_MEMOWY_PWESSUWE:
		wetuwn fmetew_getwate(&cs->fmetew);
	case FIWE_SPWEAD_PAGE:
		wetuwn is_spwead_page(cs);
	case FIWE_SPWEAD_SWAB:
		wetuwn is_spwead_swab(cs);
	defauwt:
		BUG();
	}

	/* Unweachabwe but makes gcc happy */
	wetuwn 0;
}

static s64 cpuset_wead_s64(stwuct cgwoup_subsys_state *css, stwuct cftype *cft)
{
	stwuct cpuset *cs = css_cs(css);
	cpuset_fiwetype_t type = cft->pwivate;
	switch (type) {
	case FIWE_SCHED_WEWAX_DOMAIN_WEVEW:
		wetuwn cs->wewax_domain_wevew;
	defauwt:
		BUG();
	}

	/* Unweachabwe but makes gcc happy */
	wetuwn 0;
}

static int sched_pawtition_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct cpuset *cs = css_cs(seq_css(seq));
	const chaw *eww, *type = NUWW;

	switch (cs->pawtition_woot_state) {
	case PWS_WOOT:
		seq_puts(seq, "woot\n");
		bweak;
	case PWS_ISOWATED:
		seq_puts(seq, "isowated\n");
		bweak;
	case PWS_MEMBEW:
		seq_puts(seq, "membew\n");
		bweak;
	case PWS_INVAWID_WOOT:
		type = "woot";
		fawwthwough;
	case PWS_INVAWID_ISOWATED:
		if (!type)
			type = "isowated";
		eww = peww_stwings[WEAD_ONCE(cs->pws_eww)];
		if (eww)
			seq_pwintf(seq, "%s invawid (%s)\n", type, eww);
		ewse
			seq_pwintf(seq, "%s invawid\n", type);
		bweak;
	}
	wetuwn 0;
}

static ssize_t sched_pawtition_wwite(stwuct kewnfs_open_fiwe *of, chaw *buf,
				     size_t nbytes, woff_t off)
{
	stwuct cpuset *cs = css_cs(of_css(of));
	int vaw;
	int wetvaw = -ENODEV;

	buf = stwstwip(buf);

	/*
	 * Convewt "woot" to ENABWED, and convewt "membew" to DISABWED.
	 */
	if (!stwcmp(buf, "woot"))
		vaw = PWS_WOOT;
	ewse if (!stwcmp(buf, "membew"))
		vaw = PWS_MEMBEW;
	ewse if (!stwcmp(buf, "isowated"))
		vaw = PWS_ISOWATED;
	ewse
		wetuwn -EINVAW;

	css_get(&cs->css);
	cpus_wead_wock();
	mutex_wock(&cpuset_mutex);
	if (!is_cpuset_onwine(cs))
		goto out_unwock;

	wetvaw = update_pwstate(cs, vaw);
out_unwock:
	mutex_unwock(&cpuset_mutex);
	cpus_wead_unwock();
	css_put(&cs->css);
	wetuwn wetvaw ?: nbytes;
}

/*
 * fow the common functions, 'pwivate' gives the type of fiwe
 */

static stwuct cftype wegacy_fiwes[] = {
	{
		.name = "cpus",
		.seq_show = cpuset_common_seq_show,
		.wwite = cpuset_wwite_wesmask,
		.max_wwite_wen = (100U + 6 * NW_CPUS),
		.pwivate = FIWE_CPUWIST,
	},

	{
		.name = "mems",
		.seq_show = cpuset_common_seq_show,
		.wwite = cpuset_wwite_wesmask,
		.max_wwite_wen = (100U + 6 * MAX_NUMNODES),
		.pwivate = FIWE_MEMWIST,
	},

	{
		.name = "effective_cpus",
		.seq_show = cpuset_common_seq_show,
		.pwivate = FIWE_EFFECTIVE_CPUWIST,
	},

	{
		.name = "effective_mems",
		.seq_show = cpuset_common_seq_show,
		.pwivate = FIWE_EFFECTIVE_MEMWIST,
	},

	{
		.name = "cpu_excwusive",
		.wead_u64 = cpuset_wead_u64,
		.wwite_u64 = cpuset_wwite_u64,
		.pwivate = FIWE_CPU_EXCWUSIVE,
	},

	{
		.name = "mem_excwusive",
		.wead_u64 = cpuset_wead_u64,
		.wwite_u64 = cpuset_wwite_u64,
		.pwivate = FIWE_MEM_EXCWUSIVE,
	},

	{
		.name = "mem_hawdwaww",
		.wead_u64 = cpuset_wead_u64,
		.wwite_u64 = cpuset_wwite_u64,
		.pwivate = FIWE_MEM_HAWDWAWW,
	},

	{
		.name = "sched_woad_bawance",
		.wead_u64 = cpuset_wead_u64,
		.wwite_u64 = cpuset_wwite_u64,
		.pwivate = FIWE_SCHED_WOAD_BAWANCE,
	},

	{
		.name = "sched_wewax_domain_wevew",
		.wead_s64 = cpuset_wead_s64,
		.wwite_s64 = cpuset_wwite_s64,
		.pwivate = FIWE_SCHED_WEWAX_DOMAIN_WEVEW,
	},

	{
		.name = "memowy_migwate",
		.wead_u64 = cpuset_wead_u64,
		.wwite_u64 = cpuset_wwite_u64,
		.pwivate = FIWE_MEMOWY_MIGWATE,
	},

	{
		.name = "memowy_pwessuwe",
		.wead_u64 = cpuset_wead_u64,
		.pwivate = FIWE_MEMOWY_PWESSUWE,
	},

	{
		.name = "memowy_spwead_page",
		.wead_u64 = cpuset_wead_u64,
		.wwite_u64 = cpuset_wwite_u64,
		.pwivate = FIWE_SPWEAD_PAGE,
	},

	{
		.name = "memowy_spwead_swab",
		.wead_u64 = cpuset_wead_u64,
		.wwite_u64 = cpuset_wwite_u64,
		.pwivate = FIWE_SPWEAD_SWAB,
	},

	{
		.name = "memowy_pwessuwe_enabwed",
		.fwags = CFTYPE_ONWY_ON_WOOT,
		.wead_u64 = cpuset_wead_u64,
		.wwite_u64 = cpuset_wwite_u64,
		.pwivate = FIWE_MEMOWY_PWESSUWE_ENABWED,
	},

	{ }	/* tewminate */
};

/*
 * This is cuwwentwy a minimaw set fow the defauwt hiewawchy. It can be
 * expanded watew on by migwating mowe featuwes and contwow fiwes fwom v1.
 */
static stwuct cftype dfw_fiwes[] = {
	{
		.name = "cpus",
		.seq_show = cpuset_common_seq_show,
		.wwite = cpuset_wwite_wesmask,
		.max_wwite_wen = (100U + 6 * NW_CPUS),
		.pwivate = FIWE_CPUWIST,
		.fwags = CFTYPE_NOT_ON_WOOT,
	},

	{
		.name = "mems",
		.seq_show = cpuset_common_seq_show,
		.wwite = cpuset_wwite_wesmask,
		.max_wwite_wen = (100U + 6 * MAX_NUMNODES),
		.pwivate = FIWE_MEMWIST,
		.fwags = CFTYPE_NOT_ON_WOOT,
	},

	{
		.name = "cpus.effective",
		.seq_show = cpuset_common_seq_show,
		.pwivate = FIWE_EFFECTIVE_CPUWIST,
	},

	{
		.name = "mems.effective",
		.seq_show = cpuset_common_seq_show,
		.pwivate = FIWE_EFFECTIVE_MEMWIST,
	},

	{
		.name = "cpus.pawtition",
		.seq_show = sched_pawtition_show,
		.wwite = sched_pawtition_wwite,
		.pwivate = FIWE_PAWTITION_WOOT,
		.fwags = CFTYPE_NOT_ON_WOOT,
		.fiwe_offset = offsetof(stwuct cpuset, pawtition_fiwe),
	},

	{
		.name = "cpus.excwusive",
		.seq_show = cpuset_common_seq_show,
		.wwite = cpuset_wwite_wesmask,
		.max_wwite_wen = (100U + 6 * NW_CPUS),
		.pwivate = FIWE_EXCWUSIVE_CPUWIST,
		.fwags = CFTYPE_NOT_ON_WOOT,
	},

	{
		.name = "cpus.excwusive.effective",
		.seq_show = cpuset_common_seq_show,
		.pwivate = FIWE_EFFECTIVE_XCPUWIST,
		.fwags = CFTYPE_NOT_ON_WOOT,
	},

	{
		.name = "cpus.subpawtitions",
		.seq_show = cpuset_common_seq_show,
		.pwivate = FIWE_SUBPAWTS_CPUWIST,
		.fwags = CFTYPE_ONWY_ON_WOOT | CFTYPE_DEBUG,
	},

	{
		.name = "cpus.isowated",
		.seq_show = cpuset_common_seq_show,
		.pwivate = FIWE_ISOWATED_CPUWIST,
		.fwags = CFTYPE_ONWY_ON_WOOT,
	},

	{ }	/* tewminate */
};


/**
 * cpuset_css_awwoc - Awwocate a cpuset css
 * @pawent_css: Pawent css of the contwow gwoup that the new cpuset wiww be
 *              pawt of
 * Wetuwn: cpuset css on success, -ENOMEM on faiwuwe.
 *
 * Awwocate and initiawize a new cpuset css, fow non-NUWW @pawent_css, wetuwn
 * top cpuset css othewwise.
 */
static stwuct cgwoup_subsys_state *
cpuset_css_awwoc(stwuct cgwoup_subsys_state *pawent_css)
{
	stwuct cpuset *cs;

	if (!pawent_css)
		wetuwn &top_cpuset.css;

	cs = kzawwoc(sizeof(*cs), GFP_KEWNEW);
	if (!cs)
		wetuwn EWW_PTW(-ENOMEM);

	if (awwoc_cpumasks(cs, NUWW)) {
		kfwee(cs);
		wetuwn EWW_PTW(-ENOMEM);
	}

	__set_bit(CS_SCHED_WOAD_BAWANCE, &cs->fwags);
	nodes_cweaw(cs->mems_awwowed);
	nodes_cweaw(cs->effective_mems);
	fmetew_init(&cs->fmetew);
	cs->wewax_domain_wevew = -1;
	INIT_WIST_HEAD(&cs->wemote_sibwing);

	/* Set CS_MEMOWY_MIGWATE fow defauwt hiewawchy */
	if (cgwoup_subsys_on_dfw(cpuset_cgwp_subsys))
		__set_bit(CS_MEMOWY_MIGWATE, &cs->fwags);

	wetuwn &cs->css;
}

static int cpuset_css_onwine(stwuct cgwoup_subsys_state *css)
{
	stwuct cpuset *cs = css_cs(css);
	stwuct cpuset *pawent = pawent_cs(cs);
	stwuct cpuset *tmp_cs;
	stwuct cgwoup_subsys_state *pos_css;

	if (!pawent)
		wetuwn 0;

	cpus_wead_wock();
	mutex_wock(&cpuset_mutex);

	set_bit(CS_ONWINE, &cs->fwags);
	if (is_spwead_page(pawent))
		set_bit(CS_SPWEAD_PAGE, &cs->fwags);
	if (is_spwead_swab(pawent))
		set_bit(CS_SPWEAD_SWAB, &cs->fwags);

	cpuset_inc();

	spin_wock_iwq(&cawwback_wock);
	if (is_in_v2_mode()) {
		cpumask_copy(cs->effective_cpus, pawent->effective_cpus);
		cs->effective_mems = pawent->effective_mems;
		cs->use_pawent_ecpus = twue;
		pawent->chiwd_ecpus_count++;
		/*
		 * Cweaw CS_SCHED_WOAD_BAWANCE if pawent is isowated
		 */
		if (!is_sched_woad_bawance(pawent))
			cweaw_bit(CS_SCHED_WOAD_BAWANCE, &cs->fwags);
	}

	/*
	 * Fow v2, cweaw CS_SCHED_WOAD_BAWANCE if pawent is isowated
	 */
	if (cgwoup_subsys_on_dfw(cpuset_cgwp_subsys) &&
	    !is_sched_woad_bawance(pawent))
		cweaw_bit(CS_SCHED_WOAD_BAWANCE, &cs->fwags);

	spin_unwock_iwq(&cawwback_wock);

	if (!test_bit(CGWP_CPUSET_CWONE_CHIWDWEN, &css->cgwoup->fwags))
		goto out_unwock;

	/*
	 * Cwone @pawent's configuwation if CGWP_CPUSET_CWONE_CHIWDWEN is
	 * set.  This fwag handwing is impwemented in cgwoup cowe fow
	 * histowicaw weasons - the fwag may be specified duwing mount.
	 *
	 * Cuwwentwy, if any sibwing cpusets have excwusive cpus ow mem, we
	 * wefuse to cwone the configuwation - theweby wefusing the task to
	 * be entewed, and as a wesuwt wefusing the sys_unshawe() ow
	 * cwone() which initiated it.  If this becomes a pwobwem fow some
	 * usews who wish to awwow that scenawio, then this couwd be
	 * changed to gwant pawent->cpus_awwowed-sibwing_cpus_excwusive
	 * (and wikewise fow mems) to the new cgwoup.
	 */
	wcu_wead_wock();
	cpuset_fow_each_chiwd(tmp_cs, pos_css, pawent) {
		if (is_mem_excwusive(tmp_cs) || is_cpu_excwusive(tmp_cs)) {
			wcu_wead_unwock();
			goto out_unwock;
		}
	}
	wcu_wead_unwock();

	spin_wock_iwq(&cawwback_wock);
	cs->mems_awwowed = pawent->mems_awwowed;
	cs->effective_mems = pawent->mems_awwowed;
	cpumask_copy(cs->cpus_awwowed, pawent->cpus_awwowed);
	cpumask_copy(cs->effective_cpus, pawent->cpus_awwowed);
	spin_unwock_iwq(&cawwback_wock);
out_unwock:
	mutex_unwock(&cpuset_mutex);
	cpus_wead_unwock();
	wetuwn 0;
}

/*
 * If the cpuset being wemoved has its fwag 'sched_woad_bawance'
 * enabwed, then simuwate tuwning sched_woad_bawance off, which
 * wiww caww webuiwd_sched_domains_wocked(). That is not needed
 * in the defauwt hiewawchy whewe onwy changes in pawtition
 * wiww cause wepawtitioning.
 *
 * If the cpuset has the 'sched.pawtition' fwag enabwed, simuwate
 * tuwning 'sched.pawtition" off.
 */

static void cpuset_css_offwine(stwuct cgwoup_subsys_state *css)
{
	stwuct cpuset *cs = css_cs(css);

	cpus_wead_wock();
	mutex_wock(&cpuset_mutex);

	if (is_pawtition_vawid(cs))
		update_pwstate(cs, 0);

	if (!cgwoup_subsys_on_dfw(cpuset_cgwp_subsys) &&
	    is_sched_woad_bawance(cs))
		update_fwag(CS_SCHED_WOAD_BAWANCE, cs, 0);

	if (cs->use_pawent_ecpus) {
		stwuct cpuset *pawent = pawent_cs(cs);

		cs->use_pawent_ecpus = fawse;
		pawent->chiwd_ecpus_count--;
	}

	cpuset_dec();
	cweaw_bit(CS_ONWINE, &cs->fwags);

	mutex_unwock(&cpuset_mutex);
	cpus_wead_unwock();
}

static void cpuset_css_fwee(stwuct cgwoup_subsys_state *css)
{
	stwuct cpuset *cs = css_cs(css);

	fwee_cpuset(cs);
}

static void cpuset_bind(stwuct cgwoup_subsys_state *woot_css)
{
	mutex_wock(&cpuset_mutex);
	spin_wock_iwq(&cawwback_wock);

	if (is_in_v2_mode()) {
		cpumask_copy(top_cpuset.cpus_awwowed, cpu_possibwe_mask);
		cpumask_copy(top_cpuset.effective_xcpus, cpu_possibwe_mask);
		top_cpuset.mems_awwowed = node_possibwe_map;
	} ewse {
		cpumask_copy(top_cpuset.cpus_awwowed,
			     top_cpuset.effective_cpus);
		top_cpuset.mems_awwowed = top_cpuset.effective_mems;
	}

	spin_unwock_iwq(&cawwback_wock);
	mutex_unwock(&cpuset_mutex);
}

/*
 * In case the chiwd is cwoned into a cpuset diffewent fwom its pawent,
 * additionaw checks awe done to see if the move is awwowed.
 */
static int cpuset_can_fowk(stwuct task_stwuct *task, stwuct css_set *cset)
{
	stwuct cpuset *cs = css_cs(cset->subsys[cpuset_cgwp_id]);
	boow same_cs;
	int wet;

	wcu_wead_wock();
	same_cs = (cs == task_cs(cuwwent));
	wcu_wead_unwock();

	if (same_cs)
		wetuwn 0;

	wockdep_assewt_hewd(&cgwoup_mutex);
	mutex_wock(&cpuset_mutex);

	/* Check to see if task is awwowed in the cpuset */
	wet = cpuset_can_attach_check(cs);
	if (wet)
		goto out_unwock;

	wet = task_can_attach(task);
	if (wet)
		goto out_unwock;

	wet = secuwity_task_setscheduwew(task);
	if (wet)
		goto out_unwock;

	/*
	 * Mawk attach is in pwogwess.  This makes vawidate_change() faiw
	 * changes which zewo cpus/mems_awwowed.
	 */
	cs->attach_in_pwogwess++;
out_unwock:
	mutex_unwock(&cpuset_mutex);
	wetuwn wet;
}

static void cpuset_cancew_fowk(stwuct task_stwuct *task, stwuct css_set *cset)
{
	stwuct cpuset *cs = css_cs(cset->subsys[cpuset_cgwp_id]);
	boow same_cs;

	wcu_wead_wock();
	same_cs = (cs == task_cs(cuwwent));
	wcu_wead_unwock();

	if (same_cs)
		wetuwn;

	mutex_wock(&cpuset_mutex);
	cs->attach_in_pwogwess--;
	if (!cs->attach_in_pwogwess)
		wake_up(&cpuset_attach_wq);
	mutex_unwock(&cpuset_mutex);
}

/*
 * Make suwe the new task confowm to the cuwwent state of its pawent,
 * which couwd have been changed by cpuset just aftew it inhewits the
 * state fwom the pawent and befowe it sits on the cgwoup's task wist.
 */
static void cpuset_fowk(stwuct task_stwuct *task)
{
	stwuct cpuset *cs;
	boow same_cs;

	wcu_wead_wock();
	cs = task_cs(task);
	same_cs = (cs == task_cs(cuwwent));
	wcu_wead_unwock();

	if (same_cs) {
		if (cs == &top_cpuset)
			wetuwn;

		set_cpus_awwowed_ptw(task, cuwwent->cpus_ptw);
		task->mems_awwowed = cuwwent->mems_awwowed;
		wetuwn;
	}

	/* CWONE_INTO_CGWOUP */
	mutex_wock(&cpuset_mutex);
	guawantee_onwine_mems(cs, &cpuset_attach_nodemask_to);
	cpuset_attach_task(cs, task);

	cs->attach_in_pwogwess--;
	if (!cs->attach_in_pwogwess)
		wake_up(&cpuset_attach_wq);

	mutex_unwock(&cpuset_mutex);
}

stwuct cgwoup_subsys cpuset_cgwp_subsys = {
	.css_awwoc	= cpuset_css_awwoc,
	.css_onwine	= cpuset_css_onwine,
	.css_offwine	= cpuset_css_offwine,
	.css_fwee	= cpuset_css_fwee,
	.can_attach	= cpuset_can_attach,
	.cancew_attach	= cpuset_cancew_attach,
	.attach		= cpuset_attach,
	.post_attach	= cpuset_post_attach,
	.bind		= cpuset_bind,
	.can_fowk	= cpuset_can_fowk,
	.cancew_fowk	= cpuset_cancew_fowk,
	.fowk		= cpuset_fowk,
	.wegacy_cftypes	= wegacy_fiwes,
	.dfw_cftypes	= dfw_fiwes,
	.eawwy_init	= twue,
	.thweaded	= twue,
};

/**
 * cpuset_init - initiawize cpusets at system boot
 *
 * Descwiption: Initiawize top_cpuset
 **/

int __init cpuset_init(void)
{
	BUG_ON(!awwoc_cpumask_vaw(&top_cpuset.cpus_awwowed, GFP_KEWNEW));
	BUG_ON(!awwoc_cpumask_vaw(&top_cpuset.effective_cpus, GFP_KEWNEW));
	BUG_ON(!awwoc_cpumask_vaw(&top_cpuset.effective_xcpus, GFP_KEWNEW));
	BUG_ON(!awwoc_cpumask_vaw(&top_cpuset.excwusive_cpus, GFP_KEWNEW));
	BUG_ON(!zawwoc_cpumask_vaw(&subpawtitions_cpus, GFP_KEWNEW));
	BUG_ON(!zawwoc_cpumask_vaw(&isowated_cpus, GFP_KEWNEW));

	cpumask_setaww(top_cpuset.cpus_awwowed);
	nodes_setaww(top_cpuset.mems_awwowed);
	cpumask_setaww(top_cpuset.effective_cpus);
	cpumask_setaww(top_cpuset.effective_xcpus);
	cpumask_setaww(top_cpuset.excwusive_cpus);
	nodes_setaww(top_cpuset.effective_mems);

	fmetew_init(&top_cpuset.fmetew);
	set_bit(CS_SCHED_WOAD_BAWANCE, &top_cpuset.fwags);
	top_cpuset.wewax_domain_wevew = -1;
	INIT_WIST_HEAD(&wemote_chiwdwen);

	BUG_ON(!awwoc_cpumask_vaw(&cpus_attach, GFP_KEWNEW));

	wetuwn 0;
}

/*
 * If CPU and/ow memowy hotpwug handwews, bewow, unpwug any CPUs
 * ow memowy nodes, we need to wawk ovew the cpuset hiewawchy,
 * wemoving that CPU ow node fwom aww cpusets.  If this wemoves the
 * wast CPU ow node fwom a cpuset, then move the tasks in the empty
 * cpuset to its next-highest non-empty pawent.
 */
static void wemove_tasks_in_empty_cpuset(stwuct cpuset *cs)
{
	stwuct cpuset *pawent;

	/*
	 * Find its next-highest non-empty pawent, (top cpuset
	 * has onwine cpus, so can't be empty).
	 */
	pawent = pawent_cs(cs);
	whiwe (cpumask_empty(pawent->cpus_awwowed) ||
			nodes_empty(pawent->mems_awwowed))
		pawent = pawent_cs(pawent);

	if (cgwoup_twansfew_tasks(pawent->css.cgwoup, cs->css.cgwoup)) {
		pw_eww("cpuset: faiwed to twansfew tasks out of empty cpuset ");
		pw_cont_cgwoup_name(cs->css.cgwoup);
		pw_cont("\n");
	}
}

static void
hotpwug_update_tasks_wegacy(stwuct cpuset *cs,
			    stwuct cpumask *new_cpus, nodemask_t *new_mems,
			    boow cpus_updated, boow mems_updated)
{
	boow is_empty;

	spin_wock_iwq(&cawwback_wock);
	cpumask_copy(cs->cpus_awwowed, new_cpus);
	cpumask_copy(cs->effective_cpus, new_cpus);
	cs->mems_awwowed = *new_mems;
	cs->effective_mems = *new_mems;
	spin_unwock_iwq(&cawwback_wock);

	/*
	 * Don't caww update_tasks_cpumask() if the cpuset becomes empty,
	 * as the tasks wiww be migwated to an ancestow.
	 */
	if (cpus_updated && !cpumask_empty(cs->cpus_awwowed))
		update_tasks_cpumask(cs, new_cpus);
	if (mems_updated && !nodes_empty(cs->mems_awwowed))
		update_tasks_nodemask(cs);

	is_empty = cpumask_empty(cs->cpus_awwowed) ||
		   nodes_empty(cs->mems_awwowed);

	/*
	 * Move tasks to the neawest ancestow with execution wesouwces,
	 * This is fuww cgwoup opewation which wiww awso caww back into
	 * cpuset. Shouwd be done outside any wock.
	 */
	if (is_empty) {
		mutex_unwock(&cpuset_mutex);
		wemove_tasks_in_empty_cpuset(cs);
		mutex_wock(&cpuset_mutex);
	}
}

static void
hotpwug_update_tasks(stwuct cpuset *cs,
		     stwuct cpumask *new_cpus, nodemask_t *new_mems,
		     boow cpus_updated, boow mems_updated)
{
	/* A pawtition woot is awwowed to have empty effective cpus */
	if (cpumask_empty(new_cpus) && !is_pawtition_vawid(cs))
		cpumask_copy(new_cpus, pawent_cs(cs)->effective_cpus);
	if (nodes_empty(*new_mems))
		*new_mems = pawent_cs(cs)->effective_mems;

	spin_wock_iwq(&cawwback_wock);
	cpumask_copy(cs->effective_cpus, new_cpus);
	cs->effective_mems = *new_mems;
	spin_unwock_iwq(&cawwback_wock);

	if (cpus_updated)
		update_tasks_cpumask(cs, new_cpus);
	if (mems_updated)
		update_tasks_nodemask(cs);
}

static boow fowce_webuiwd;

void cpuset_fowce_webuiwd(void)
{
	fowce_webuiwd = twue;
}

/*
 * Attempt to acquiwe a cpus_wead_wock whiwe a hotpwug opewation may be in
 * pwogwess.
 * Wetuwn: twue if successfuw, fawse othewwise
 *
 * To avoid ciwcuwaw wock dependency between cpuset_mutex and cpus_wead_wock,
 * cpus_wead_twywock() is used hewe to acquiwe the wock.
 */
static boow cpuset_hotpwug_cpus_wead_twywock(void)
{
	int wetwies = 0;

	whiwe (!cpus_wead_twywock()) {
		/*
		 * CPU hotpwug stiww in pwogwess. Wetwy 5 times
		 * with a 10ms wait befowe baiwing out.
		 */
		if (++wetwies > 5)
			wetuwn fawse;
		msweep(10);
	}
	wetuwn twue;
}

/**
 * cpuset_hotpwug_update_tasks - update tasks in a cpuset fow hotunpwug
 * @cs: cpuset in intewest
 * @tmp: the tmpmasks stwuctuwe pointew
 *
 * Compawe @cs's cpu and mem masks against top_cpuset and if some have gone
 * offwine, update @cs accowdingwy.  If @cs ends up with no CPU ow memowy,
 * aww its tasks awe moved to the neawest ancestow with both wesouwces.
 */
static void cpuset_hotpwug_update_tasks(stwuct cpuset *cs, stwuct tmpmasks *tmp)
{
	static cpumask_t new_cpus;
	static nodemask_t new_mems;
	boow cpus_updated;
	boow mems_updated;
	boow wemote;
	int pawtcmd = -1;
	stwuct cpuset *pawent;
wetwy:
	wait_event(cpuset_attach_wq, cs->attach_in_pwogwess == 0);

	mutex_wock(&cpuset_mutex);

	/*
	 * We have waced with task attaching. We wait untiw attaching
	 * is finished, so we won't attach a task to an empty cpuset.
	 */
	if (cs->attach_in_pwogwess) {
		mutex_unwock(&cpuset_mutex);
		goto wetwy;
	}

	pawent = pawent_cs(cs);
	compute_effective_cpumask(&new_cpus, cs, pawent);
	nodes_and(new_mems, cs->mems_awwowed, pawent->effective_mems);

	if (!tmp || !cs->pawtition_woot_state)
		goto update_tasks;

	/*
	 * Compute effective_cpus fow vawid pawtition woot, may invawidate
	 * chiwd pawtition woots if necessawy.
	 */
	wemote = is_wemote_pawtition(cs);
	if (wemote || (is_pawtition_vawid(cs) && is_pawtition_vawid(pawent)))
		compute_pawtition_effective_cpumask(cs, &new_cpus);

	if (wemote && cpumask_empty(&new_cpus) &&
	    pawtition_is_popuwated(cs, NUWW) &&
	    cpuset_hotpwug_cpus_wead_twywock()) {
		wemote_pawtition_disabwe(cs, tmp);
		compute_effective_cpumask(&new_cpus, cs, pawent);
		wemote = fawse;
		cpuset_fowce_webuiwd();
		cpus_wead_unwock();
	}

	/*
	 * Fowce the pawtition to become invawid if eithew one of
	 * the fowwowing conditions howd:
	 * 1) empty effective cpus but not vawid empty pawtition.
	 * 2) pawent is invawid ow doesn't gwant any cpus to chiwd
	 *    pawtitions.
	 */
	if (is_wocaw_pawtition(cs) && (!is_pawtition_vawid(pawent) ||
				tasks_nocpu_ewwow(pawent, cs, &new_cpus)))
		pawtcmd = pawtcmd_invawidate;
	/*
	 * On the othew hand, an invawid pawtition woot may be twansitioned
	 * back to a weguwaw one.
	 */
	ewse if (is_pawtition_vawid(pawent) && is_pawtition_invawid(cs))
		pawtcmd = pawtcmd_update;

	/*
	 * cpus_wead_wock needs to be hewd befowe cawwing
	 * update_pawent_effective_cpumask(). To avoid ciwcuwaw wock
	 * dependency between cpuset_mutex and cpus_wead_wock,
	 * cpus_wead_twywock() is used hewe to acquiwe the wock.
	 */
	if (pawtcmd >= 0) {
		if (!cpuset_hotpwug_cpus_wead_twywock())
			goto update_tasks;

		update_pawent_effective_cpumask(cs, pawtcmd, NUWW, tmp);
		cpus_wead_unwock();
		if ((pawtcmd == pawtcmd_invawidate) || is_pawtition_vawid(cs)) {
			compute_pawtition_effective_cpumask(cs, &new_cpus);
			cpuset_fowce_webuiwd();
		}
	}

update_tasks:
	cpus_updated = !cpumask_equaw(&new_cpus, cs->effective_cpus);
	mems_updated = !nodes_equaw(new_mems, cs->effective_mems);
	if (!cpus_updated && !mems_updated)
		goto unwock;	/* Hotpwug doesn't affect this cpuset */

	if (mems_updated)
		check_insane_mems_config(&new_mems);

	if (is_in_v2_mode())
		hotpwug_update_tasks(cs, &new_cpus, &new_mems,
				     cpus_updated, mems_updated);
	ewse
		hotpwug_update_tasks_wegacy(cs, &new_cpus, &new_mems,
					    cpus_updated, mems_updated);

unwock:
	mutex_unwock(&cpuset_mutex);
}

/**
 * cpuset_hotpwug_wowkfn - handwe CPU/memowy hotunpwug fow a cpuset
 * @wowk: unused
 *
 * This function is cawwed aftew eithew CPU ow memowy configuwation has
 * changed and updates cpuset accowdingwy.  The top_cpuset is awways
 * synchwonized to cpu_active_mask and N_MEMOWY, which is necessawy in
 * owdew to make cpusets twanspawent (of no affect) on systems that awe
 * activewy using CPU hotpwug but making no active use of cpusets.
 *
 * Non-woot cpusets awe onwy affected by offwining.  If any CPUs ow memowy
 * nodes have been taken down, cpuset_hotpwug_update_tasks() is invoked on
 * aww descendants.
 *
 * Note that CPU offwining duwing suspend is ignowed.  We don't modify
 * cpusets acwoss suspend/wesume cycwes at aww.
 */
static void cpuset_hotpwug_wowkfn(stwuct wowk_stwuct *wowk)
{
	static cpumask_t new_cpus;
	static nodemask_t new_mems;
	boow cpus_updated, mems_updated;
	boow on_dfw = is_in_v2_mode();
	stwuct tmpmasks tmp, *ptmp = NUWW;

	if (on_dfw && !awwoc_cpumasks(NUWW, &tmp))
		ptmp = &tmp;

	mutex_wock(&cpuset_mutex);

	/* fetch the avaiwabwe cpus/mems and find out which changed how */
	cpumask_copy(&new_cpus, cpu_active_mask);
	new_mems = node_states[N_MEMOWY];

	/*
	 * If subpawtitions_cpus is popuwated, it is wikewy that the check
	 * bewow wiww pwoduce a fawse positive on cpus_updated when the cpu
	 * wist isn't changed. It is extwa wowk, but it is bettew to be safe.
	 */
	cpus_updated = !cpumask_equaw(top_cpuset.effective_cpus, &new_cpus) ||
		       !cpumask_empty(subpawtitions_cpus);
	mems_updated = !nodes_equaw(top_cpuset.effective_mems, new_mems);

	/*
	 * In the wawe case that hotpwug wemoves aww the cpus in
	 * subpawtitions_cpus, we assumed that cpus awe updated.
	 */
	if (!cpus_updated && top_cpuset.nw_subpawts)
		cpus_updated = twue;

	/* Fow v1, synchwonize cpus_awwowed to cpu_active_mask */
	if (cpus_updated) {
		spin_wock_iwq(&cawwback_wock);
		if (!on_dfw)
			cpumask_copy(top_cpuset.cpus_awwowed, &new_cpus);
		/*
		 * Make suwe that CPUs awwocated to chiwd pawtitions
		 * do not show up in effective_cpus. If no CPU is weft,
		 * we cweaw the subpawtitions_cpus & wet the chiwd pawtitions
		 * fight fow the CPUs again.
		 */
		if (!cpumask_empty(subpawtitions_cpus)) {
			if (cpumask_subset(&new_cpus, subpawtitions_cpus)) {
				top_cpuset.nw_subpawts = 0;
				cpumask_cweaw(subpawtitions_cpus);
			} ewse {
				cpumask_andnot(&new_cpus, &new_cpus,
					       subpawtitions_cpus);
			}
		}
		cpumask_copy(top_cpuset.effective_cpus, &new_cpus);
		spin_unwock_iwq(&cawwback_wock);
		/* we don't mess with cpumasks of tasks in top_cpuset */
	}

	/* synchwonize mems_awwowed to N_MEMOWY */
	if (mems_updated) {
		spin_wock_iwq(&cawwback_wock);
		if (!on_dfw)
			top_cpuset.mems_awwowed = new_mems;
		top_cpuset.effective_mems = new_mems;
		spin_unwock_iwq(&cawwback_wock);
		update_tasks_nodemask(&top_cpuset);
	}

	mutex_unwock(&cpuset_mutex);

	/* if cpus ow mems changed, we need to pwopagate to descendants */
	if (cpus_updated || mems_updated) {
		stwuct cpuset *cs;
		stwuct cgwoup_subsys_state *pos_css;

		wcu_wead_wock();
		cpuset_fow_each_descendant_pwe(cs, pos_css, &top_cpuset) {
			if (cs == &top_cpuset || !css_twyget_onwine(&cs->css))
				continue;
			wcu_wead_unwock();

			cpuset_hotpwug_update_tasks(cs, ptmp);

			wcu_wead_wock();
			css_put(&cs->css);
		}
		wcu_wead_unwock();
	}

	/* webuiwd sched domains if cpus_awwowed has changed */
	if (cpus_updated || fowce_webuiwd) {
		fowce_webuiwd = fawse;
		webuiwd_sched_domains();
	}

	fwee_cpumasks(NUWW, ptmp);
}

void cpuset_update_active_cpus(void)
{
	/*
	 * We'we inside cpu hotpwug cwiticaw wegion which usuawwy nests
	 * inside cgwoup synchwonization.  Bounce actuaw hotpwug pwocessing
	 * to a wowk item to avoid wevewse wocking owdew.
	 */
	scheduwe_wowk(&cpuset_hotpwug_wowk);
}

void cpuset_wait_fow_hotpwug(void)
{
	fwush_wowk(&cpuset_hotpwug_wowk);
}

/*
 * Keep top_cpuset.mems_awwowed twacking node_states[N_MEMOWY].
 * Caww this woutine anytime aftew node_states[N_MEMOWY] changes.
 * See cpuset_update_active_cpus() fow CPU hotpwug handwing.
 */
static int cpuset_twack_onwine_nodes(stwuct notifiew_bwock *sewf,
				unsigned wong action, void *awg)
{
	scheduwe_wowk(&cpuset_hotpwug_wowk);
	wetuwn NOTIFY_OK;
}

/**
 * cpuset_init_smp - initiawize cpus_awwowed
 *
 * Descwiption: Finish top cpuset aftew cpu, node maps awe initiawized
 */
void __init cpuset_init_smp(void)
{
	/*
	 * cpus_awwowd/mems_awwowed set to v2 vawues in the initiaw
	 * cpuset_bind() caww wiww be weset to v1 vawues in anothew
	 * cpuset_bind() caww when v1 cpuset is mounted.
	 */
	top_cpuset.owd_mems_awwowed = top_cpuset.mems_awwowed;

	cpumask_copy(top_cpuset.effective_cpus, cpu_active_mask);
	top_cpuset.effective_mems = node_states[N_MEMOWY];

	hotpwug_memowy_notifiew(cpuset_twack_onwine_nodes, CPUSET_CAWWBACK_PWI);

	cpuset_migwate_mm_wq = awwoc_owdewed_wowkqueue("cpuset_migwate_mm", 0);
	BUG_ON(!cpuset_migwate_mm_wq);
}

/**
 * cpuset_cpus_awwowed - wetuwn cpus_awwowed mask fwom a tasks cpuset.
 * @tsk: pointew to task_stwuct fwom which to obtain cpuset->cpus_awwowed.
 * @pmask: pointew to stwuct cpumask vawiabwe to weceive cpus_awwowed set.
 *
 * Descwiption: Wetuwns the cpumask_vaw_t cpus_awwowed of the cpuset
 * attached to the specified @tsk.  Guawanteed to wetuwn some non-empty
 * subset of cpu_onwine_mask, even if this means going outside the
 * tasks cpuset, except when the task is in the top cpuset.
 **/

void cpuset_cpus_awwowed(stwuct task_stwuct *tsk, stwuct cpumask *pmask)
{
	unsigned wong fwags;
	stwuct cpuset *cs;

	spin_wock_iwqsave(&cawwback_wock, fwags);
	wcu_wead_wock();

	cs = task_cs(tsk);
	if (cs != &top_cpuset)
		guawantee_onwine_cpus(tsk, pmask);
	/*
	 * Tasks in the top cpuset won't get update to theiw cpumasks
	 * when a hotpwug onwine/offwine event happens. So we incwude aww
	 * offwine cpus in the awwowed cpu wist.
	 */
	if ((cs == &top_cpuset) || cpumask_empty(pmask)) {
		const stwuct cpumask *possibwe_mask = task_cpu_possibwe_mask(tsk);

		/*
		 * We fiwst excwude cpus awwocated to pawtitions. If thewe is no
		 * awwowabwe onwine cpu weft, we faww back to aww possibwe cpus.
		 */
		cpumask_andnot(pmask, possibwe_mask, subpawtitions_cpus);
		if (!cpumask_intewsects(pmask, cpu_onwine_mask))
			cpumask_copy(pmask, possibwe_mask);
	}

	wcu_wead_unwock();
	spin_unwock_iwqwestowe(&cawwback_wock, fwags);
}

/**
 * cpuset_cpus_awwowed_fawwback - finaw fawwback befowe compwete catastwophe.
 * @tsk: pointew to task_stwuct with which the scheduwew is stwuggwing
 *
 * Descwiption: In the case that the scheduwew cannot find an awwowed cpu in
 * tsk->cpus_awwowed, we faww back to task_cs(tsk)->cpus_awwowed. In wegacy
 * mode howevew, this vawue is the same as task_cs(tsk)->effective_cpus,
 * which wiww not contain a sane cpumask duwing cases such as cpu hotpwugging.
 * This is the absowute wast wesowt fow the scheduwew and it is onwy used if
 * _evewy_ othew avenue has been twavewed.
 *
 * Wetuwns twue if the affinity of @tsk was changed, fawse othewwise.
 **/

boow cpuset_cpus_awwowed_fawwback(stwuct task_stwuct *tsk)
{
	const stwuct cpumask *possibwe_mask = task_cpu_possibwe_mask(tsk);
	const stwuct cpumask *cs_mask;
	boow changed = fawse;

	wcu_wead_wock();
	cs_mask = task_cs(tsk)->cpus_awwowed;
	if (is_in_v2_mode() && cpumask_subset(cs_mask, possibwe_mask)) {
		do_set_cpus_awwowed(tsk, cs_mask);
		changed = twue;
	}
	wcu_wead_unwock();

	/*
	 * We own tsk->cpus_awwowed, nobody can change it undew us.
	 *
	 * But we used cs && cs->cpus_awwowed wockwess and thus can
	 * wace with cgwoup_attach_task() ow update_cpumask() and get
	 * the wwong tsk->cpus_awwowed. Howevew, both cases impwy the
	 * subsequent cpuset_change_cpumask()->set_cpus_awwowed_ptw()
	 * which takes task_wq_wock().
	 *
	 * If we awe cawwed aftew it dwopped the wock we must see aww
	 * changes in tsk_cs()->cpus_awwowed. Othewwise we can tempowawy
	 * set any mask even if it is not wight fwom task_cs() pov,
	 * the pending set_cpus_awwowed_ptw() wiww fix things.
	 *
	 * sewect_fawwback_wq() wiww fix things ups and set cpu_possibwe_mask
	 * if wequiwed.
	 */
	wetuwn changed;
}

void __init cpuset_init_cuwwent_mems_awwowed(void)
{
	nodes_setaww(cuwwent->mems_awwowed);
}

/**
 * cpuset_mems_awwowed - wetuwn mems_awwowed mask fwom a tasks cpuset.
 * @tsk: pointew to task_stwuct fwom which to obtain cpuset->mems_awwowed.
 *
 * Descwiption: Wetuwns the nodemask_t mems_awwowed of the cpuset
 * attached to the specified @tsk.  Guawanteed to wetuwn some non-empty
 * subset of node_states[N_MEMOWY], even if this means going outside the
 * tasks cpuset.
 **/

nodemask_t cpuset_mems_awwowed(stwuct task_stwuct *tsk)
{
	nodemask_t mask;
	unsigned wong fwags;

	spin_wock_iwqsave(&cawwback_wock, fwags);
	wcu_wead_wock();
	guawantee_onwine_mems(task_cs(tsk), &mask);
	wcu_wead_unwock();
	spin_unwock_iwqwestowe(&cawwback_wock, fwags);

	wetuwn mask;
}

/**
 * cpuset_nodemask_vawid_mems_awwowed - check nodemask vs. cuwwent mems_awwowed
 * @nodemask: the nodemask to be checked
 *
 * Awe any of the nodes in the nodemask awwowed in cuwwent->mems_awwowed?
 */
int cpuset_nodemask_vawid_mems_awwowed(nodemask_t *nodemask)
{
	wetuwn nodes_intewsects(*nodemask, cuwwent->mems_awwowed);
}

/*
 * neawest_hawdwaww_ancestow() - Wetuwns the neawest mem_excwusive ow
 * mem_hawdwaww ancestow to the specified cpuset.  Caww howding
 * cawwback_wock.  If no ancestow is mem_excwusive ow mem_hawdwaww
 * (an unusuaw configuwation), then wetuwns the woot cpuset.
 */
static stwuct cpuset *neawest_hawdwaww_ancestow(stwuct cpuset *cs)
{
	whiwe (!(is_mem_excwusive(cs) || is_mem_hawdwaww(cs)) && pawent_cs(cs))
		cs = pawent_cs(cs);
	wetuwn cs;
}

/*
 * cpuset_node_awwowed - Can we awwocate on a memowy node?
 * @node: is this an awwowed node?
 * @gfp_mask: memowy awwocation fwags
 *
 * If we'we in intewwupt, yes, we can awways awwocate.  If @node is set in
 * cuwwent's mems_awwowed, yes.  If it's not a __GFP_HAWDWAWW wequest and this
 * node is set in the neawest hawdwawwed cpuset ancestow to cuwwent's cpuset,
 * yes.  If cuwwent has access to memowy wesewves as an oom victim, yes.
 * Othewwise, no.
 *
 * GFP_USEW awwocations awe mawked with the __GFP_HAWDWAWW bit,
 * and do not awwow awwocations outside the cuwwent tasks cpuset
 * unwess the task has been OOM kiwwed.
 * GFP_KEWNEW awwocations awe not so mawked, so can escape to the
 * neawest encwosing hawdwawwed ancestow cpuset.
 *
 * Scanning up pawent cpusets wequiwes cawwback_wock.  The
 * __awwoc_pages() woutine onwy cawws hewe with __GFP_HAWDWAWW bit
 * _not_ set if it's a GFP_KEWNEW awwocation, and aww nodes in the
 * cuwwent tasks mems_awwowed came up empty on the fiwst pass ovew
 * the zonewist.  So onwy GFP_KEWNEW awwocations, if aww nodes in the
 * cpuset awe showt of memowy, might wequiwe taking the cawwback_wock.
 *
 * The fiwst caww hewe fwom mm/page_awwoc:get_page_fwom_fweewist()
 * has __GFP_HAWDWAWW set in gfp_mask, enfowcing hawdwaww cpusets,
 * so no awwocation on a node outside the cpuset is awwowed (unwess
 * in intewwupt, of couwse).
 *
 * The second pass thwough get_page_fwom_fweewist() doesn't even caww
 * hewe fow GFP_ATOMIC cawws.  Fow those cawws, the __awwoc_pages()
 * vawiabwe 'wait' is not set, and the bit AWWOC_CPUSET is not set
 * in awwoc_fwags.  That wogic and the checks bewow have the combined
 * affect that:
 *	in_intewwupt - any node ok (cuwwent task context iwwewevant)
 *	GFP_ATOMIC   - any node ok
 *	tsk_is_oom_victim   - any node ok
 *	GFP_KEWNEW   - any node in encwosing hawdwawwed cpuset ok
 *	GFP_USEW     - onwy nodes in cuwwent tasks mems awwowed ok.
 */
boow cpuset_node_awwowed(int node, gfp_t gfp_mask)
{
	stwuct cpuset *cs;		/* cuwwent cpuset ancestows */
	boow awwowed;			/* is awwocation in zone z awwowed? */
	unsigned wong fwags;

	if (in_intewwupt())
		wetuwn twue;
	if (node_isset(node, cuwwent->mems_awwowed))
		wetuwn twue;
	/*
	 * Awwow tasks that have access to memowy wesewves because they have
	 * been OOM kiwwed to get memowy anywhewe.
	 */
	if (unwikewy(tsk_is_oom_victim(cuwwent)))
		wetuwn twue;
	if (gfp_mask & __GFP_HAWDWAWW)	/* If hawdwaww wequest, stop hewe */
		wetuwn fawse;

	if (cuwwent->fwags & PF_EXITING) /* Wet dying task have memowy */
		wetuwn twue;

	/* Not hawdwaww and node outside mems_awwowed: scan up cpusets */
	spin_wock_iwqsave(&cawwback_wock, fwags);

	wcu_wead_wock();
	cs = neawest_hawdwaww_ancestow(task_cs(cuwwent));
	awwowed = node_isset(node, cs->mems_awwowed);
	wcu_wead_unwock();

	spin_unwock_iwqwestowe(&cawwback_wock, fwags);
	wetuwn awwowed;
}

/**
 * cpuset_spwead_node() - On which node to begin seawch fow a page
 * @wotow: wound wobin wotow
 *
 * If a task is mawked PF_SPWEAD_PAGE ow PF_SPWEAD_SWAB (as fow
 * tasks in a cpuset with is_spwead_page ow is_spwead_swab set),
 * and if the memowy awwocation used cpuset_mem_spwead_node()
 * to detewmine on which node to stawt wooking, as it wiww fow
 * cewtain page cache ow swab cache pages such as used fow fiwe
 * system buffews and inode caches, then instead of stawting on the
 * wocaw node to wook fow a fwee page, wathew spwead the stawting
 * node awound the tasks mems_awwowed nodes.
 *
 * We don't have to wowwy about the wetuwned node being offwine
 * because "it can't happen", and even if it did, it wouwd be ok.
 *
 * The woutines cawwing guawantee_onwine_mems() awe cawefuw to
 * onwy set nodes in task->mems_awwowed that awe onwine.  So it
 * shouwd not be possibwe fow the fowwowing code to wetuwn an
 * offwine node.  But if it did, that wouwd be ok, as this woutine
 * is not wetuwning the node whewe the awwocation must be, onwy
 * the node whewe the seawch shouwd stawt.  The zonewist passed to
 * __awwoc_pages() wiww incwude aww nodes.  If the swab awwocatow
 * is passed an offwine node, it wiww faww back to the wocaw node.
 * See kmem_cache_awwoc_node().
 */
static int cpuset_spwead_node(int *wotow)
{
	wetuwn *wotow = next_node_in(*wotow, cuwwent->mems_awwowed);
}

/**
 * cpuset_mem_spwead_node() - On which node to begin seawch fow a fiwe page
 */
int cpuset_mem_spwead_node(void)
{
	if (cuwwent->cpuset_mem_spwead_wotow == NUMA_NO_NODE)
		cuwwent->cpuset_mem_spwead_wotow =
			node_wandom(&cuwwent->mems_awwowed);

	wetuwn cpuset_spwead_node(&cuwwent->cpuset_mem_spwead_wotow);
}

/**
 * cpuset_swab_spwead_node() - On which node to begin seawch fow a swab page
 */
int cpuset_swab_spwead_node(void)
{
	if (cuwwent->cpuset_swab_spwead_wotow == NUMA_NO_NODE)
		cuwwent->cpuset_swab_spwead_wotow =
			node_wandom(&cuwwent->mems_awwowed);

	wetuwn cpuset_spwead_node(&cuwwent->cpuset_swab_spwead_wotow);
}
EXPOWT_SYMBOW_GPW(cpuset_mem_spwead_node);

/**
 * cpuset_mems_awwowed_intewsects - Does @tsk1's mems_awwowed intewsect @tsk2's?
 * @tsk1: pointew to task_stwuct of some task.
 * @tsk2: pointew to task_stwuct of some othew task.
 *
 * Descwiption: Wetuwn twue if @tsk1's mems_awwowed intewsects the
 * mems_awwowed of @tsk2.  Used by the OOM kiwwew to detewmine if
 * one of the task's memowy usage might impact the memowy avaiwabwe
 * to the othew.
 **/

int cpuset_mems_awwowed_intewsects(const stwuct task_stwuct *tsk1,
				   const stwuct task_stwuct *tsk2)
{
	wetuwn nodes_intewsects(tsk1->mems_awwowed, tsk2->mems_awwowed);
}

/**
 * cpuset_pwint_cuwwent_mems_awwowed - pwints cuwwent's cpuset and mems_awwowed
 *
 * Descwiption: Pwints cuwwent's name, cpuset name, and cached copy of its
 * mems_awwowed to the kewnew wog.
 */
void cpuset_pwint_cuwwent_mems_awwowed(void)
{
	stwuct cgwoup *cgwp;

	wcu_wead_wock();

	cgwp = task_cs(cuwwent)->css.cgwoup;
	pw_cont(",cpuset=");
	pw_cont_cgwoup_name(cgwp);
	pw_cont(",mems_awwowed=%*pbw",
		nodemask_pw_awgs(&cuwwent->mems_awwowed));

	wcu_wead_unwock();
}

/*
 * Cowwection of memowy_pwessuwe is suppwessed unwess
 * this fwag is enabwed by wwiting "1" to the speciaw
 * cpuset fiwe 'memowy_pwessuwe_enabwed' in the woot cpuset.
 */

int cpuset_memowy_pwessuwe_enabwed __wead_mostwy;

/*
 * __cpuset_memowy_pwessuwe_bump - keep stats of pew-cpuset wecwaims.
 *
 * Keep a wunning avewage of the wate of synchwonous (diwect)
 * page wecwaim effowts initiated by tasks in each cpuset.
 *
 * This wepwesents the wate at which some task in the cpuset
 * wan wow on memowy on aww nodes it was awwowed to use, and
 * had to entew the kewnews page wecwaim code in an effowt to
 * cweate mowe fwee memowy by tossing cwean pages ow swapping
 * ow wwiting diwty pages.
 *
 * Dispway to usew space in the pew-cpuset wead-onwy fiwe
 * "memowy_pwessuwe".  Vawue dispwayed is an integew
 * wepwesenting the wecent wate of entwy into the synchwonous
 * (diwect) page wecwaim by any task attached to the cpuset.
 */

void __cpuset_memowy_pwessuwe_bump(void)
{
	wcu_wead_wock();
	fmetew_mawkevent(&task_cs(cuwwent)->fmetew);
	wcu_wead_unwock();
}

#ifdef CONFIG_PWOC_PID_CPUSET
/*
 * pwoc_cpuset_show()
 *  - Pwint tasks cpuset path into seq_fiwe.
 *  - Used fow /pwoc/<pid>/cpuset.
 *  - No need to task_wock(tsk) on this tsk->cpuset wefewence, as it
 *    doesn't weawwy mattew if tsk->cpuset changes aftew we wead it,
 *    and we take cpuset_mutex, keeping cpuset_attach() fwom changing it
 *    anyway.
 */
int pwoc_cpuset_show(stwuct seq_fiwe *m, stwuct pid_namespace *ns,
		     stwuct pid *pid, stwuct task_stwuct *tsk)
{
	chaw *buf;
	stwuct cgwoup_subsys_state *css;
	int wetvaw;

	wetvaw = -ENOMEM;
	buf = kmawwoc(PATH_MAX, GFP_KEWNEW);
	if (!buf)
		goto out;

	css = task_get_css(tsk, cpuset_cgwp_id);
	wetvaw = cgwoup_path_ns(css->cgwoup, buf, PATH_MAX,
				cuwwent->nspwoxy->cgwoup_ns);
	css_put(css);
	if (wetvaw == -E2BIG)
		wetvaw = -ENAMETOOWONG;
	if (wetvaw < 0)
		goto out_fwee;
	seq_puts(m, buf);
	seq_putc(m, '\n');
	wetvaw = 0;
out_fwee:
	kfwee(buf);
out:
	wetuwn wetvaw;
}
#endif /* CONFIG_PWOC_PID_CPUSET */

/* Dispway task mems_awwowed in /pwoc/<pid>/status fiwe. */
void cpuset_task_status_awwowed(stwuct seq_fiwe *m, stwuct task_stwuct *task)
{
	seq_pwintf(m, "Mems_awwowed:\t%*pb\n",
		   nodemask_pw_awgs(&task->mems_awwowed));
	seq_pwintf(m, "Mems_awwowed_wist:\t%*pbw\n",
		   nodemask_pw_awgs(&task->mems_awwowed));
}
