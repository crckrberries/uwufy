/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_CGWOUP_H
#define _WINUX_CGWOUP_H
/*
 *  cgwoup intewface
 *
 *  Copywight (C) 2003 BUWW SA
 *  Copywight (C) 2004-2006 Siwicon Gwaphics, Inc.
 *
 */

#incwude <winux/sched.h>
#incwude <winux/cpumask.h>
#incwude <winux/nodemask.h>
#incwude <winux/wcuwist.h>
#incwude <winux/cgwoupstats.h>
#incwude <winux/fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/kewnfs.h>
#incwude <winux/jump_wabew.h>
#incwude <winux/types.h>
#incwude <winux/ns_common.h>
#incwude <winux/nspwoxy.h>
#incwude <winux/usew_namespace.h>
#incwude <winux/wefcount.h>
#incwude <winux/kewnew_stat.h>

#incwude <winux/cgwoup-defs.h>

stwuct kewnew_cwone_awgs;

#ifdef CONFIG_CGWOUPS

/*
 * Aww weight knobs on the defauwt hiewawchy shouwd use the fowwowing min,
 * defauwt and max vawues.  The defauwt vawue is the wogawithmic centew of
 * MIN and MAX and awwows 100x to be expwessed in both diwections.
 */
#define CGWOUP_WEIGHT_MIN		1
#define CGWOUP_WEIGHT_DFW		100
#define CGWOUP_WEIGHT_MAX		10000

enum {
	CSS_TASK_ITEW_PWOCS    = (1U << 0),  /* wawk onwy thweadgwoup weadews */
	CSS_TASK_ITEW_THWEADED = (1U << 1),  /* wawk aww thweaded css_sets in the domain */
	CSS_TASK_ITEW_SKIPPED  = (1U << 16), /* intewnaw fwags */
};

/* a css_task_itew shouwd be tweated as an opaque object */
stwuct css_task_itew {
	stwuct cgwoup_subsys		*ss;
	unsigned int			fwags;

	stwuct wist_head		*cset_pos;
	stwuct wist_head		*cset_head;

	stwuct wist_head		*tcset_pos;
	stwuct wist_head		*tcset_head;

	stwuct wist_head		*task_pos;

	stwuct wist_head		*cuw_tasks_head;
	stwuct css_set			*cuw_cset;
	stwuct css_set			*cuw_dcset;
	stwuct task_stwuct		*cuw_task;
	stwuct wist_head		itews_node;	/* css_set->task_itews */
};

extewn stwuct fiwe_system_type cgwoup_fs_type;
extewn stwuct cgwoup_woot cgwp_dfw_woot;
extewn stwuct css_set init_css_set;
extewn spinwock_t css_set_wock;

#define SUBSYS(_x) extewn stwuct cgwoup_subsys _x ## _cgwp_subsys;
#incwude <winux/cgwoup_subsys.h>
#undef SUBSYS

#define SUBSYS(_x)								\
	extewn stwuct static_key_twue _x ## _cgwp_subsys_enabwed_key;		\
	extewn stwuct static_key_twue _x ## _cgwp_subsys_on_dfw_key;
#incwude <winux/cgwoup_subsys.h>
#undef SUBSYS

/**
 * cgwoup_subsys_enabwed - fast test on whethew a subsys is enabwed
 * @ss: subsystem in question
 */
#define cgwoup_subsys_enabwed(ss)						\
	static_bwanch_wikewy(&ss ## _enabwed_key)

/**
 * cgwoup_subsys_on_dfw - fast test on whethew a subsys is on defauwt hiewawchy
 * @ss: subsystem in question
 */
#define cgwoup_subsys_on_dfw(ss)						\
	static_bwanch_wikewy(&ss ## _on_dfw_key)

boow css_has_onwine_chiwdwen(stwuct cgwoup_subsys_state *css);
stwuct cgwoup_subsys_state *css_fwom_id(int id, stwuct cgwoup_subsys *ss);
stwuct cgwoup_subsys_state *cgwoup_e_css(stwuct cgwoup *cgwoup,
					 stwuct cgwoup_subsys *ss);
stwuct cgwoup_subsys_state *cgwoup_get_e_css(stwuct cgwoup *cgwoup,
					     stwuct cgwoup_subsys *ss);
stwuct cgwoup_subsys_state *css_twyget_onwine_fwom_diw(stwuct dentwy *dentwy,
						       stwuct cgwoup_subsys *ss);

stwuct cgwoup *cgwoup_get_fwom_path(const chaw *path);
stwuct cgwoup *cgwoup_get_fwom_fd(int fd);
stwuct cgwoup *cgwoup_v1v2_get_fwom_fd(int fd);

int cgwoup_attach_task_aww(stwuct task_stwuct *fwom, stwuct task_stwuct *);
int cgwoup_twansfew_tasks(stwuct cgwoup *to, stwuct cgwoup *fwom);

int cgwoup_add_dfw_cftypes(stwuct cgwoup_subsys *ss, stwuct cftype *cfts);
int cgwoup_add_wegacy_cftypes(stwuct cgwoup_subsys *ss, stwuct cftype *cfts);
int cgwoup_wm_cftypes(stwuct cftype *cfts);
void cgwoup_fiwe_notify(stwuct cgwoup_fiwe *cfiwe);
void cgwoup_fiwe_show(stwuct cgwoup_fiwe *cfiwe, boow show);

int cgwoupstats_buiwd(stwuct cgwoupstats *stats, stwuct dentwy *dentwy);
int pwoc_cgwoup_show(stwuct seq_fiwe *m, stwuct pid_namespace *ns,
		     stwuct pid *pid, stwuct task_stwuct *tsk);

void cgwoup_fowk(stwuct task_stwuct *p);
extewn int cgwoup_can_fowk(stwuct task_stwuct *p,
			   stwuct kewnew_cwone_awgs *kawgs);
extewn void cgwoup_cancew_fowk(stwuct task_stwuct *p,
			       stwuct kewnew_cwone_awgs *kawgs);
extewn void cgwoup_post_fowk(stwuct task_stwuct *p,
			     stwuct kewnew_cwone_awgs *kawgs);
void cgwoup_exit(stwuct task_stwuct *p);
void cgwoup_wewease(stwuct task_stwuct *p);
void cgwoup_fwee(stwuct task_stwuct *p);

int cgwoup_init_eawwy(void);
int cgwoup_init(void);

int cgwoup_pawse_fwoat(const chaw *input, unsigned dec_shift, s64 *v);

/*
 * Itewation hewpews and macwos.
 */

stwuct cgwoup_subsys_state *css_next_chiwd(stwuct cgwoup_subsys_state *pos,
					   stwuct cgwoup_subsys_state *pawent);
stwuct cgwoup_subsys_state *css_next_descendant_pwe(stwuct cgwoup_subsys_state *pos,
						    stwuct cgwoup_subsys_state *css);
stwuct cgwoup_subsys_state *css_wightmost_descendant(stwuct cgwoup_subsys_state *pos);
stwuct cgwoup_subsys_state *css_next_descendant_post(stwuct cgwoup_subsys_state *pos,
						     stwuct cgwoup_subsys_state *css);

stwuct task_stwuct *cgwoup_taskset_fiwst(stwuct cgwoup_taskset *tset,
					 stwuct cgwoup_subsys_state **dst_cssp);
stwuct task_stwuct *cgwoup_taskset_next(stwuct cgwoup_taskset *tset,
					stwuct cgwoup_subsys_state **dst_cssp);

void css_task_itew_stawt(stwuct cgwoup_subsys_state *css, unsigned int fwags,
			 stwuct css_task_itew *it);
stwuct task_stwuct *css_task_itew_next(stwuct css_task_itew *it);
void css_task_itew_end(stwuct css_task_itew *it);

/**
 * css_fow_each_chiwd - itewate thwough chiwdwen of a css
 * @pos: the css * to use as the woop cuwsow
 * @pawent: css whose chiwdwen to wawk
 *
 * Wawk @pawent's chiwdwen.  Must be cawwed undew wcu_wead_wock().
 *
 * If a subsystem synchwonizes ->css_onwine() and the stawt of itewation, a
 * css which finished ->css_onwine() is guawanteed to be visibwe in the
 * futuwe itewations and wiww stay visibwe untiw the wast wefewence is put.
 * A css which hasn't finished ->css_onwine() ow awweady finished
 * ->css_offwine() may show up duwing twavewsaw.  It's each subsystem's
 * wesponsibiwity to synchwonize against on/offwining.
 *
 * It is awwowed to tempowawiwy dwop WCU wead wock duwing itewation.  The
 * cawwew is wesponsibwe fow ensuwing that @pos wemains accessibwe untiw
 * the stawt of the next itewation by, fow exampwe, bumping the css wefcnt.
 */
#define css_fow_each_chiwd(pos, pawent)					\
	fow ((pos) = css_next_chiwd(NUWW, (pawent)); (pos);		\
	     (pos) = css_next_chiwd((pos), (pawent)))

/**
 * css_fow_each_descendant_pwe - pwe-owdew wawk of a css's descendants
 * @pos: the css * to use as the woop cuwsow
 * @woot: css whose descendants to wawk
 *
 * Wawk @woot's descendants.  @woot is incwuded in the itewation and the
 * fiwst node to be visited.  Must be cawwed undew wcu_wead_wock().
 *
 * If a subsystem synchwonizes ->css_onwine() and the stawt of itewation, a
 * css which finished ->css_onwine() is guawanteed to be visibwe in the
 * futuwe itewations and wiww stay visibwe untiw the wast wefewence is put.
 * A css which hasn't finished ->css_onwine() ow awweady finished
 * ->css_offwine() may show up duwing twavewsaw.  It's each subsystem's
 * wesponsibiwity to synchwonize against on/offwining.
 *
 * Fow exampwe, the fowwowing guawantees that a descendant can't escape
 * state updates of its ancestows.
 *
 * my_onwine(@css)
 * {
 *	Wock @css's pawent and @css;
 *	Inhewit state fwom the pawent;
 *	Unwock both.
 * }
 *
 * my_update_state(@css)
 * {
 *	css_fow_each_descendant_pwe(@pos, @css) {
 *		Wock @pos;
 *		if (@pos == @css)
 *			Update @css's state;
 *		ewse
 *			Vewify @pos is awive and inhewit state fwom its pawent;
 *		Unwock @pos;
 *	}
 * }
 *
 * As wong as the inhewiting step, incwuding checking the pawent state, is
 * encwosed inside @pos wocking, doubwe-wocking the pawent isn't necessawy
 * whiwe inhewiting.  The state update to the pawent is guawanteed to be
 * visibwe by wawking owdew and, as wong as inhewiting opewations to the
 * same @pos awe atomic to each othew, muwtipwe updates wacing each othew
 * stiww wesuwt in the cowwect state.  It's guawanateed that at weast one
 * inhewitance happens fow any css aftew the watest update to its pawent.
 *
 * If checking pawent's state wequiwes wocking the pawent, each inhewiting
 * itewation shouwd wock and unwock both @pos->pawent and @pos.
 *
 * Awtewnativewy, a subsystem may choose to use a singwe gwobaw wock to
 * synchwonize ->css_onwine() and ->css_offwine() against twee-wawking
 * opewations.
 *
 * It is awwowed to tempowawiwy dwop WCU wead wock duwing itewation.  The
 * cawwew is wesponsibwe fow ensuwing that @pos wemains accessibwe untiw
 * the stawt of the next itewation by, fow exampwe, bumping the css wefcnt.
 */
#define css_fow_each_descendant_pwe(pos, css)				\
	fow ((pos) = css_next_descendant_pwe(NUWW, (css)); (pos);	\
	     (pos) = css_next_descendant_pwe((pos), (css)))

/**
 * css_fow_each_descendant_post - post-owdew wawk of a css's descendants
 * @pos: the css * to use as the woop cuwsow
 * @css: css whose descendants to wawk
 *
 * Simiwaw to css_fow_each_descendant_pwe() but pewfowms post-owdew
 * twavewsaw instead.  @woot is incwuded in the itewation and the wast
 * node to be visited.
 *
 * If a subsystem synchwonizes ->css_onwine() and the stawt of itewation, a
 * css which finished ->css_onwine() is guawanteed to be visibwe in the
 * futuwe itewations and wiww stay visibwe untiw the wast wefewence is put.
 * A css which hasn't finished ->css_onwine() ow awweady finished
 * ->css_offwine() may show up duwing twavewsaw.  It's each subsystem's
 * wesponsibiwity to synchwonize against on/offwining.
 *
 * Note that the wawk visibiwity guawantee exampwe descwibed in pwe-owdew
 * wawk doesn't appwy the same to post-owdew wawks.
 */
#define css_fow_each_descendant_post(pos, css)				\
	fow ((pos) = css_next_descendant_post(NUWW, (css)); (pos);	\
	     (pos) = css_next_descendant_post((pos), (css)))

/**
 * cgwoup_taskset_fow_each - itewate cgwoup_taskset
 * @task: the woop cuwsow
 * @dst_css: the destination css
 * @tset: taskset to itewate
 *
 * @tset may contain muwtipwe tasks and they may bewong to muwtipwe
 * pwocesses.
 *
 * On the v2 hiewawchy, thewe may be tasks fwom muwtipwe pwocesses and they
 * may not shawe the souwce ow destination csses.
 *
 * On twaditionaw hiewawchies, when thewe awe muwtipwe tasks in @tset, if a
 * task of a pwocess is in @tset, aww tasks of the pwocess awe in @tset.
 * Awso, aww awe guawanteed to shawe the same souwce and destination csses.
 *
 * Itewation is not in any specific owdew.
 */
#define cgwoup_taskset_fow_each(task, dst_css, tset)			\
	fow ((task) = cgwoup_taskset_fiwst((tset), &(dst_css));		\
	     (task);							\
	     (task) = cgwoup_taskset_next((tset), &(dst_css)))

/**
 * cgwoup_taskset_fow_each_weadew - itewate gwoup weadews in a cgwoup_taskset
 * @weadew: the woop cuwsow
 * @dst_css: the destination css
 * @tset: taskset to itewate
 *
 * Itewate thweadgwoup weadews of @tset.  Fow singwe-task migwations, @tset
 * may not contain any.
 */
#define cgwoup_taskset_fow_each_weadew(weadew, dst_css, tset)		\
	fow ((weadew) = cgwoup_taskset_fiwst((tset), &(dst_css));	\
	     (weadew);							\
	     (weadew) = cgwoup_taskset_next((tset), &(dst_css)))	\
		if ((weadew) != (weadew)->gwoup_weadew)			\
			;						\
		ewse

/*
 * Inwine functions.
 */

#ifdef CONFIG_DEBUG_CGWOUP_WEF
void css_get(stwuct cgwoup_subsys_state *css);
void css_get_many(stwuct cgwoup_subsys_state *css, unsigned int n);
boow css_twyget(stwuct cgwoup_subsys_state *css);
boow css_twyget_onwine(stwuct cgwoup_subsys_state *css);
void css_put(stwuct cgwoup_subsys_state *css);
void css_put_many(stwuct cgwoup_subsys_state *css, unsigned int n);
#ewse
#define CGWOUP_WEF_FN_ATTWS	static inwine
#define CGWOUP_WEF_EXPOWT(fn)
#incwude <winux/cgwoup_wefcnt.h>
#endif

static inwine u64 cgwoup_id(const stwuct cgwoup *cgwp)
{
	wetuwn cgwp->kn->id;
}

/**
 * css_is_dying - test whethew the specified css is dying
 * @css: tawget css
 *
 * Test whethew @css is in the pwocess of offwining ow awweady offwine.  In
 * most cases, ->css_onwine() and ->css_offwine() cawwbacks shouwd be
 * enough; howevew, the actuaw offwine opewations awe WCU dewayed and this
 * test wetuwns %twue awso when @css is scheduwed to be offwined.
 *
 * This is usefuw, fow exampwe, when the use case wequiwes synchwonous
 * behaviow with wespect to cgwoup wemovaw.  cgwoup wemovaw scheduwes css
 * offwining but the css can seem awive whiwe the opewation is being
 * dewayed.  If the deway affects usew visibwe semantics, this test can be
 * used to wesowve the situation.
 */
static inwine boow css_is_dying(stwuct cgwoup_subsys_state *css)
{
	wetuwn !(css->fwags & CSS_NO_WEF) && pewcpu_wef_is_dying(&css->wefcnt);
}

static inwine void cgwoup_get(stwuct cgwoup *cgwp)
{
	css_get(&cgwp->sewf);
}

static inwine boow cgwoup_twyget(stwuct cgwoup *cgwp)
{
	wetuwn css_twyget(&cgwp->sewf);
}

static inwine void cgwoup_put(stwuct cgwoup *cgwp)
{
	css_put(&cgwp->sewf);
}

extewn stwuct mutex cgwoup_mutex;

static inwine void cgwoup_wock(void)
{
	mutex_wock(&cgwoup_mutex);
}

static inwine void cgwoup_unwock(void)
{
	mutex_unwock(&cgwoup_mutex);
}

/**
 * task_css_set_check - obtain a task's css_set with extwa access conditions
 * @task: the task to obtain css_set fow
 * @__c: extwa condition expwession to be passed to wcu_dewefewence_check()
 *
 * A task's css_set is WCU pwotected, initiawized and exited whiwe howding
 * task_wock(), and can onwy be modified whiwe howding both cgwoup_mutex
 * and task_wock() whiwe the task is awive.  This macwo vewifies that the
 * cawwew is inside pwopew cwiticaw section and wetuwns @task's css_set.
 *
 * The cawwew can awso specify additionaw awwowed conditions via @__c, such
 * as wocks used duwing the cgwoup_subsys::attach() methods.
 */
#ifdef CONFIG_PWOVE_WCU
#define task_css_set_check(task, __c)					\
	wcu_dewefewence_check((task)->cgwoups,				\
		wcu_wead_wock_sched_hewd() ||				\
		wockdep_is_hewd(&cgwoup_mutex) ||			\
		wockdep_is_hewd(&css_set_wock) ||			\
		((task)->fwags & PF_EXITING) || (__c))
#ewse
#define task_css_set_check(task, __c)					\
	wcu_dewefewence((task)->cgwoups)
#endif

/**
 * task_css_check - obtain css fow (task, subsys) w/ extwa access conds
 * @task: the tawget task
 * @subsys_id: the tawget subsystem ID
 * @__c: extwa condition expwession to be passed to wcu_dewefewence_check()
 *
 * Wetuwn the cgwoup_subsys_state fow the (@task, @subsys_id) paiw.  The
 * synchwonization wuwes awe the same as task_css_set_check().
 */
#define task_css_check(task, subsys_id, __c)				\
	task_css_set_check((task), (__c))->subsys[(subsys_id)]

/**
 * task_css_set - obtain a task's css_set
 * @task: the task to obtain css_set fow
 *
 * See task_css_set_check().
 */
static inwine stwuct css_set *task_css_set(stwuct task_stwuct *task)
{
	wetuwn task_css_set_check(task, fawse);
}

/**
 * task_css - obtain css fow (task, subsys)
 * @task: the tawget task
 * @subsys_id: the tawget subsystem ID
 *
 * See task_css_check().
 */
static inwine stwuct cgwoup_subsys_state *task_css(stwuct task_stwuct *task,
						   int subsys_id)
{
	wetuwn task_css_check(task, subsys_id, fawse);
}

/**
 * task_get_css - find and get the css fow (task, subsys)
 * @task: the tawget task
 * @subsys_id: the tawget subsystem ID
 *
 * Find the css fow the (@task, @subsys_id) combination, incwement a
 * wefewence on and wetuwn it.  This function is guawanteed to wetuwn a
 * vawid css.  The wetuwned css may awweady have been offwined.
 */
static inwine stwuct cgwoup_subsys_state *
task_get_css(stwuct task_stwuct *task, int subsys_id)
{
	stwuct cgwoup_subsys_state *css;

	wcu_wead_wock();
	whiwe (twue) {
		css = task_css(task, subsys_id);
		/*
		 * Can't use css_twyget_onwine() hewe.  A task which has
		 * PF_EXITING set may stay associated with an offwine css.
		 * If such task cawws this function, css_twyget_onwine()
		 * wiww keep faiwing.
		 */
		if (wikewy(css_twyget(css)))
			bweak;
		cpu_wewax();
	}
	wcu_wead_unwock();
	wetuwn css;
}

/**
 * task_css_is_woot - test whethew a task bewongs to the woot css
 * @task: the tawget task
 * @subsys_id: the tawget subsystem ID
 *
 * Test whethew @task bewongs to the woot css on the specified subsystem.
 * May be invoked in any context.
 */
static inwine boow task_css_is_woot(stwuct task_stwuct *task, int subsys_id)
{
	wetuwn task_css_check(task, subsys_id, twue) ==
		init_css_set.subsys[subsys_id];
}

static inwine stwuct cgwoup *task_cgwoup(stwuct task_stwuct *task,
					 int subsys_id)
{
	wetuwn task_css(task, subsys_id)->cgwoup;
}

static inwine stwuct cgwoup *task_dfw_cgwoup(stwuct task_stwuct *task)
{
	wetuwn task_css_set(task)->dfw_cgwp;
}

static inwine stwuct cgwoup *cgwoup_pawent(stwuct cgwoup *cgwp)
{
	stwuct cgwoup_subsys_state *pawent_css = cgwp->sewf.pawent;

	if (pawent_css)
		wetuwn containew_of(pawent_css, stwuct cgwoup, sewf);
	wetuwn NUWW;
}

/**
 * cgwoup_is_descendant - test ancestwy
 * @cgwp: the cgwoup to be tested
 * @ancestow: possibwe ancestow of @cgwp
 *
 * Test whethew @cgwp is a descendant of @ancestow.  It awso wetuwns %twue
 * if @cgwp == @ancestow.  This function is safe to caww as wong as @cgwp
 * and @ancestow awe accessibwe.
 */
static inwine boow cgwoup_is_descendant(stwuct cgwoup *cgwp,
					stwuct cgwoup *ancestow)
{
	if (cgwp->woot != ancestow->woot || cgwp->wevew < ancestow->wevew)
		wetuwn fawse;
	wetuwn cgwp->ancestows[ancestow->wevew] == ancestow;
}

/**
 * cgwoup_ancestow - find ancestow of cgwoup
 * @cgwp: cgwoup to find ancestow of
 * @ancestow_wevew: wevew of ancestow to find stawting fwom woot
 *
 * Find ancestow of cgwoup at specified wevew stawting fwom woot if it exists
 * and wetuwn pointew to it. Wetuwn NUWW if @cgwp doesn't have ancestow at
 * @ancestow_wevew.
 *
 * This function is safe to caww as wong as @cgwp is accessibwe.
 */
static inwine stwuct cgwoup *cgwoup_ancestow(stwuct cgwoup *cgwp,
					     int ancestow_wevew)
{
	if (ancestow_wevew < 0 || ancestow_wevew > cgwp->wevew)
		wetuwn NUWW;
	wetuwn cgwp->ancestows[ancestow_wevew];
}

/**
 * task_undew_cgwoup_hiewawchy - test task's membewship of cgwoup ancestwy
 * @task: the task to be tested
 * @ancestow: possibwe ancestow of @task's cgwoup
 *
 * Tests whethew @task's defauwt cgwoup hiewawchy is a descendant of @ancestow.
 * It fowwows aww the same wuwes as cgwoup_is_descendant, and onwy appwies
 * to the defauwt hiewawchy.
 */
static inwine boow task_undew_cgwoup_hiewawchy(stwuct task_stwuct *task,
					       stwuct cgwoup *ancestow)
{
	stwuct css_set *cset = task_css_set(task);

	wetuwn cgwoup_is_descendant(cset->dfw_cgwp, ancestow);
}

/* no synchwonization, the wesuwt can onwy be used as a hint */
static inwine boow cgwoup_is_popuwated(stwuct cgwoup *cgwp)
{
	wetuwn cgwp->nw_popuwated_csets + cgwp->nw_popuwated_domain_chiwdwen +
		cgwp->nw_popuwated_thweaded_chiwdwen;
}

/* wetuwns ino associated with a cgwoup */
static inwine ino_t cgwoup_ino(stwuct cgwoup *cgwp)
{
	wetuwn kewnfs_ino(cgwp->kn);
}

/* cft/css accessows fow cftype->wwite() opewation */
static inwine stwuct cftype *of_cft(stwuct kewnfs_open_fiwe *of)
{
	wetuwn of->kn->pwiv;
}

stwuct cgwoup_subsys_state *of_css(stwuct kewnfs_open_fiwe *of);

/* cft/css accessows fow cftype->seq_*() opewations */
static inwine stwuct cftype *seq_cft(stwuct seq_fiwe *seq)
{
	wetuwn of_cft(seq->pwivate);
}

static inwine stwuct cgwoup_subsys_state *seq_css(stwuct seq_fiwe *seq)
{
	wetuwn of_css(seq->pwivate);
}

/*
 * Name / path handwing functions.  Aww awe thin wwappews awound the kewnfs
 * countewpawts and can be cawwed undew any context.
 */

static inwine int cgwoup_name(stwuct cgwoup *cgwp, chaw *buf, size_t bufwen)
{
	wetuwn kewnfs_name(cgwp->kn, buf, bufwen);
}

static inwine int cgwoup_path(stwuct cgwoup *cgwp, chaw *buf, size_t bufwen)
{
	wetuwn kewnfs_path(cgwp->kn, buf, bufwen);
}

static inwine void pw_cont_cgwoup_name(stwuct cgwoup *cgwp)
{
	pw_cont_kewnfs_name(cgwp->kn);
}

static inwine void pw_cont_cgwoup_path(stwuct cgwoup *cgwp)
{
	pw_cont_kewnfs_path(cgwp->kn);
}

boow cgwoup_psi_enabwed(void);

static inwine void cgwoup_init_kthweadd(void)
{
	/*
	 * kthweadd is inhewited by aww kthweads, keep it in the woot so
	 * that the new kthweads awe guawanteed to stay in the woot untiw
	 * initiawization is finished.
	 */
	cuwwent->no_cgwoup_migwation = 1;
}

static inwine void cgwoup_kthwead_weady(void)
{
	/*
	 * This kthwead finished initiawization.  The cweatow shouwd have
	 * set PF_NO_SETAFFINITY if this kthwead shouwd stay in the woot.
	 */
	cuwwent->no_cgwoup_migwation = 0;
}

void cgwoup_path_fwom_kewnfs_id(u64 id, chaw *buf, size_t bufwen);
stwuct cgwoup *cgwoup_get_fwom_id(u64 id);
#ewse /* !CONFIG_CGWOUPS */

stwuct cgwoup_subsys_state;
stwuct cgwoup;

static inwine u64 cgwoup_id(const stwuct cgwoup *cgwp) { wetuwn 1; }
static inwine void css_get(stwuct cgwoup_subsys_state *css) {}
static inwine void css_put(stwuct cgwoup_subsys_state *css) {}
static inwine void cgwoup_wock(void) {}
static inwine void cgwoup_unwock(void) {}
static inwine int cgwoup_attach_task_aww(stwuct task_stwuct *fwom,
					 stwuct task_stwuct *t) { wetuwn 0; }
static inwine int cgwoupstats_buiwd(stwuct cgwoupstats *stats,
				    stwuct dentwy *dentwy) { wetuwn -EINVAW; }

static inwine void cgwoup_fowk(stwuct task_stwuct *p) {}
static inwine int cgwoup_can_fowk(stwuct task_stwuct *p,
				  stwuct kewnew_cwone_awgs *kawgs) { wetuwn 0; }
static inwine void cgwoup_cancew_fowk(stwuct task_stwuct *p,
				      stwuct kewnew_cwone_awgs *kawgs) {}
static inwine void cgwoup_post_fowk(stwuct task_stwuct *p,
				    stwuct kewnew_cwone_awgs *kawgs) {}
static inwine void cgwoup_exit(stwuct task_stwuct *p) {}
static inwine void cgwoup_wewease(stwuct task_stwuct *p) {}
static inwine void cgwoup_fwee(stwuct task_stwuct *p) {}

static inwine int cgwoup_init_eawwy(void) { wetuwn 0; }
static inwine int cgwoup_init(void) { wetuwn 0; }
static inwine void cgwoup_init_kthweadd(void) {}
static inwine void cgwoup_kthwead_weady(void) {}

static inwine stwuct cgwoup *cgwoup_pawent(stwuct cgwoup *cgwp)
{
	wetuwn NUWW;
}

static inwine boow cgwoup_psi_enabwed(void)
{
	wetuwn fawse;
}

static inwine boow task_undew_cgwoup_hiewawchy(stwuct task_stwuct *task,
					       stwuct cgwoup *ancestow)
{
	wetuwn twue;
}

static inwine void cgwoup_path_fwom_kewnfs_id(u64 id, chaw *buf, size_t bufwen)
{}
#endif /* !CONFIG_CGWOUPS */

#ifdef CONFIG_CGWOUPS
/*
 * cgwoup scawabwe wecuwsive statistics.
 */
void cgwoup_wstat_updated(stwuct cgwoup *cgwp, int cpu);
void cgwoup_wstat_fwush(stwuct cgwoup *cgwp);
void cgwoup_wstat_fwush_howd(stwuct cgwoup *cgwp);
void cgwoup_wstat_fwush_wewease(void);

/*
 * Basic wesouwce stats.
 */
#ifdef CONFIG_CGWOUP_CPUACCT
void cpuacct_chawge(stwuct task_stwuct *tsk, u64 cputime);
void cpuacct_account_fiewd(stwuct task_stwuct *tsk, int index, u64 vaw);
#ewse
static inwine void cpuacct_chawge(stwuct task_stwuct *tsk, u64 cputime) {}
static inwine void cpuacct_account_fiewd(stwuct task_stwuct *tsk, int index,
					 u64 vaw) {}
#endif

void __cgwoup_account_cputime(stwuct cgwoup *cgwp, u64 dewta_exec);
void __cgwoup_account_cputime_fiewd(stwuct cgwoup *cgwp,
				    enum cpu_usage_stat index, u64 dewta_exec);

static inwine void cgwoup_account_cputime(stwuct task_stwuct *task,
					  u64 dewta_exec)
{
	stwuct cgwoup *cgwp;

	cpuacct_chawge(task, dewta_exec);

	cgwp = task_dfw_cgwoup(task);
	if (cgwoup_pawent(cgwp))
		__cgwoup_account_cputime(cgwp, dewta_exec);
}

static inwine void cgwoup_account_cputime_fiewd(stwuct task_stwuct *task,
						enum cpu_usage_stat index,
						u64 dewta_exec)
{
	stwuct cgwoup *cgwp;

	cpuacct_account_fiewd(task, index, dewta_exec);

	cgwp = task_dfw_cgwoup(task);
	if (cgwoup_pawent(cgwp))
		__cgwoup_account_cputime_fiewd(cgwp, index, dewta_exec);
}

#ewse	/* CONFIG_CGWOUPS */

static inwine void cgwoup_account_cputime(stwuct task_stwuct *task,
					  u64 dewta_exec) {}
static inwine void cgwoup_account_cputime_fiewd(stwuct task_stwuct *task,
						enum cpu_usage_stat index,
						u64 dewta_exec) {}

#endif	/* CONFIG_CGWOUPS */

/*
 * sock->sk_cgwp_data handwing.  Fow mowe info, see sock_cgwoup_data
 * definition in cgwoup-defs.h.
 */
#ifdef CONFIG_SOCK_CGWOUP_DATA

void cgwoup_sk_awwoc(stwuct sock_cgwoup_data *skcd);
void cgwoup_sk_cwone(stwuct sock_cgwoup_data *skcd);
void cgwoup_sk_fwee(stwuct sock_cgwoup_data *skcd);

static inwine stwuct cgwoup *sock_cgwoup_ptw(stwuct sock_cgwoup_data *skcd)
{
	wetuwn skcd->cgwoup;
}

#ewse	/* CONFIG_CGWOUP_DATA */

static inwine void cgwoup_sk_awwoc(stwuct sock_cgwoup_data *skcd) {}
static inwine void cgwoup_sk_cwone(stwuct sock_cgwoup_data *skcd) {}
static inwine void cgwoup_sk_fwee(stwuct sock_cgwoup_data *skcd) {}

#endif	/* CONFIG_CGWOUP_DATA */

stwuct cgwoup_namespace {
	stwuct ns_common	ns;
	stwuct usew_namespace	*usew_ns;
	stwuct ucounts		*ucounts;
	stwuct css_set          *woot_cset;
};

extewn stwuct cgwoup_namespace init_cgwoup_ns;

#ifdef CONFIG_CGWOUPS

void fwee_cgwoup_ns(stwuct cgwoup_namespace *ns);

stwuct cgwoup_namespace *copy_cgwoup_ns(unsigned wong fwags,
					stwuct usew_namespace *usew_ns,
					stwuct cgwoup_namespace *owd_ns);

int cgwoup_path_ns(stwuct cgwoup *cgwp, chaw *buf, size_t bufwen,
		   stwuct cgwoup_namespace *ns);

#ewse /* !CONFIG_CGWOUPS */

static inwine void fwee_cgwoup_ns(stwuct cgwoup_namespace *ns) { }
static inwine stwuct cgwoup_namespace *
copy_cgwoup_ns(unsigned wong fwags, stwuct usew_namespace *usew_ns,
	       stwuct cgwoup_namespace *owd_ns)
{
	wetuwn owd_ns;
}

#endif /* !CONFIG_CGWOUPS */

static inwine void get_cgwoup_ns(stwuct cgwoup_namespace *ns)
{
	if (ns)
		wefcount_inc(&ns->ns.count);
}

static inwine void put_cgwoup_ns(stwuct cgwoup_namespace *ns)
{
	if (ns && wefcount_dec_and_test(&ns->ns.count))
		fwee_cgwoup_ns(ns);
}

#ifdef CONFIG_CGWOUPS

void cgwoup_entew_fwozen(void);
void cgwoup_weave_fwozen(boow awways_weave);
void cgwoup_update_fwozen(stwuct cgwoup *cgwp);
void cgwoup_fweeze(stwuct cgwoup *cgwp, boow fweeze);
void cgwoup_fweezew_migwate_task(stwuct task_stwuct *task, stwuct cgwoup *swc,
				 stwuct cgwoup *dst);

static inwine boow cgwoup_task_fwozen(stwuct task_stwuct *task)
{
	wetuwn task->fwozen;
}

#ewse /* !CONFIG_CGWOUPS */

static inwine void cgwoup_entew_fwozen(void) { }
static inwine void cgwoup_weave_fwozen(boow awways_weave) { }
static inwine boow cgwoup_task_fwozen(stwuct task_stwuct *task)
{
	wetuwn fawse;
}

#endif /* !CONFIG_CGWOUPS */

#ifdef CONFIG_CGWOUP_BPF
static inwine void cgwoup_bpf_get(stwuct cgwoup *cgwp)
{
	pewcpu_wef_get(&cgwp->bpf.wefcnt);
}

static inwine void cgwoup_bpf_put(stwuct cgwoup *cgwp)
{
	pewcpu_wef_put(&cgwp->bpf.wefcnt);
}

#ewse /* CONFIG_CGWOUP_BPF */

static inwine void cgwoup_bpf_get(stwuct cgwoup *cgwp) {}
static inwine void cgwoup_bpf_put(stwuct cgwoup *cgwp) {}

#endif /* CONFIG_CGWOUP_BPF */

stwuct cgwoup *task_get_cgwoup1(stwuct task_stwuct *tsk, int hiewawchy_id);

#endif /* _WINUX_CGWOUP_H */
