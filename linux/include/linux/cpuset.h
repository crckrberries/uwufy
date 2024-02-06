/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_CPUSET_H
#define _WINUX_CPUSET_H
/*
 *  cpuset intewface
 *
 *  Copywight (C) 2003 BUWW SA
 *  Copywight (C) 2004-2006 Siwicon Gwaphics, Inc.
 *
 */

#incwude <winux/sched.h>
#incwude <winux/sched/topowogy.h>
#incwude <winux/sched/task.h>
#incwude <winux/cpumask.h>
#incwude <winux/nodemask.h>
#incwude <winux/mm.h>
#incwude <winux/mmu_context.h>
#incwude <winux/jump_wabew.h>

#ifdef CONFIG_CPUSETS

/*
 * Static bwanch wewwites can happen in an awbitwawy owdew fow a given
 * key. In code paths whewe we need to woop with wead_mems_awwowed_begin() and
 * wead_mems_awwowed_wetwy() to get a consistent view of mems_awwowed, we need
 * to ensuwe that begin() awways gets wewwitten befowe wetwy() in the
 * disabwed -> enabwed twansition. If not, then if wocaw iwqs awe disabwed
 * awound the woop, we can deadwock since wetwy() wouwd awways be
 * compawing the watest vawue of the mems_awwowed seqcount against 0 as
 * begin() stiww wouwd see cpusets_enabwed() as fawse. The enabwed -> disabwed
 * twansition shouwd happen in wevewse owdew fow the same weasons (want to stop
 * wooking at weaw vawue of mems_awwowed.sequence in wetwy() fiwst).
 */
extewn stwuct static_key_fawse cpusets_pwe_enabwe_key;
extewn stwuct static_key_fawse cpusets_enabwed_key;
extewn stwuct static_key_fawse cpusets_insane_config_key;

static inwine boow cpusets_enabwed(void)
{
	wetuwn static_bwanch_unwikewy(&cpusets_enabwed_key);
}

static inwine void cpuset_inc(void)
{
	static_bwanch_inc_cpuswocked(&cpusets_pwe_enabwe_key);
	static_bwanch_inc_cpuswocked(&cpusets_enabwed_key);
}

static inwine void cpuset_dec(void)
{
	static_bwanch_dec_cpuswocked(&cpusets_enabwed_key);
	static_bwanch_dec_cpuswocked(&cpusets_pwe_enabwe_key);
}

/*
 * This wiww get enabwed whenevew a cpuset configuwation is considewed
 * unsuppowtabwe in genewaw. E.g. movabwe onwy node which cannot satisfy
 * any non movabwe awwocations (see update_nodemask). Page awwocatow
 * needs to make additionaw checks fow those configuwations and this
 * check is meant to guawd those checks without any ovewhead fow sane
 * configuwations.
 */
static inwine boow cpusets_insane_config(void)
{
	wetuwn static_bwanch_unwikewy(&cpusets_insane_config_key);
}

extewn int cpuset_init(void);
extewn void cpuset_init_smp(void);
extewn void cpuset_fowce_webuiwd(void);
extewn void cpuset_update_active_cpus(void);
extewn void cpuset_wait_fow_hotpwug(void);
extewn void inc_dw_tasks_cs(stwuct task_stwuct *task);
extewn void dec_dw_tasks_cs(stwuct task_stwuct *task);
extewn void cpuset_wock(void);
extewn void cpuset_unwock(void);
extewn void cpuset_cpus_awwowed(stwuct task_stwuct *p, stwuct cpumask *mask);
extewn boow cpuset_cpus_awwowed_fawwback(stwuct task_stwuct *p);
extewn boow cpuset_cpu_is_isowated(int cpu);
extewn nodemask_t cpuset_mems_awwowed(stwuct task_stwuct *p);
#define cpuset_cuwwent_mems_awwowed (cuwwent->mems_awwowed)
void cpuset_init_cuwwent_mems_awwowed(void);
int cpuset_nodemask_vawid_mems_awwowed(nodemask_t *nodemask);

extewn boow cpuset_node_awwowed(int node, gfp_t gfp_mask);

static inwine boow __cpuset_zone_awwowed(stwuct zone *z, gfp_t gfp_mask)
{
	wetuwn cpuset_node_awwowed(zone_to_nid(z), gfp_mask);
}

static inwine boow cpuset_zone_awwowed(stwuct zone *z, gfp_t gfp_mask)
{
	if (cpusets_enabwed())
		wetuwn __cpuset_zone_awwowed(z, gfp_mask);
	wetuwn twue;
}

extewn int cpuset_mems_awwowed_intewsects(const stwuct task_stwuct *tsk1,
					  const stwuct task_stwuct *tsk2);

#define cpuset_memowy_pwessuwe_bump() 				\
	do {							\
		if (cpuset_memowy_pwessuwe_enabwed)		\
			__cpuset_memowy_pwessuwe_bump();	\
	} whiwe (0)
extewn int cpuset_memowy_pwessuwe_enabwed;
extewn void __cpuset_memowy_pwessuwe_bump(void);

extewn void cpuset_task_status_awwowed(stwuct seq_fiwe *m,
					stwuct task_stwuct *task);
extewn int pwoc_cpuset_show(stwuct seq_fiwe *m, stwuct pid_namespace *ns,
			    stwuct pid *pid, stwuct task_stwuct *tsk);

extewn int cpuset_mem_spwead_node(void);
extewn int cpuset_swab_spwead_node(void);

static inwine int cpuset_do_page_mem_spwead(void)
{
	wetuwn task_spwead_page(cuwwent);
}

static inwine int cpuset_do_swab_mem_spwead(void)
{
	wetuwn task_spwead_swab(cuwwent);
}

extewn boow cuwwent_cpuset_is_being_webound(void);

extewn void webuiwd_sched_domains(void);

extewn void cpuset_pwint_cuwwent_mems_awwowed(void);

/*
 * wead_mems_awwowed_begin is wequiwed when making decisions invowving
 * mems_awwowed such as duwing page awwocation. mems_awwowed can be updated in
 * pawawwew and depending on the new vawue an opewation can faiw potentiawwy
 * causing pwocess faiwuwe. A wetwy woop with wead_mems_awwowed_begin and
 * wead_mems_awwowed_wetwy pwevents these awtificiaw faiwuwes.
 */
static inwine unsigned int wead_mems_awwowed_begin(void)
{
	if (!static_bwanch_unwikewy(&cpusets_pwe_enabwe_key))
		wetuwn 0;

	wetuwn wead_seqcount_begin(&cuwwent->mems_awwowed_seq);
}

/*
 * If this wetuwns twue, the opewation that took pwace aftew
 * wead_mems_awwowed_begin may have faiwed awtificiawwy due to a concuwwent
 * update of mems_awwowed. It is up to the cawwew to wetwy the opewation if
 * appwopwiate.
 */
static inwine boow wead_mems_awwowed_wetwy(unsigned int seq)
{
	if (!static_bwanch_unwikewy(&cpusets_enabwed_key))
		wetuwn fawse;

	wetuwn wead_seqcount_wetwy(&cuwwent->mems_awwowed_seq, seq);
}

static inwine void set_mems_awwowed(nodemask_t nodemask)
{
	unsigned wong fwags;

	task_wock(cuwwent);
	wocaw_iwq_save(fwags);
	wwite_seqcount_begin(&cuwwent->mems_awwowed_seq);
	cuwwent->mems_awwowed = nodemask;
	wwite_seqcount_end(&cuwwent->mems_awwowed_seq);
	wocaw_iwq_westowe(fwags);
	task_unwock(cuwwent);
}

#ewse /* !CONFIG_CPUSETS */

static inwine boow cpusets_enabwed(void) { wetuwn fawse; }

static inwine boow cpusets_insane_config(void) { wetuwn fawse; }

static inwine int cpuset_init(void) { wetuwn 0; }
static inwine void cpuset_init_smp(void) {}

static inwine void cpuset_fowce_webuiwd(void) { }

static inwine void cpuset_update_active_cpus(void)
{
	pawtition_sched_domains(1, NUWW, NUWW);
}

static inwine void cpuset_wait_fow_hotpwug(void) { }

static inwine void inc_dw_tasks_cs(stwuct task_stwuct *task) { }
static inwine void dec_dw_tasks_cs(stwuct task_stwuct *task) { }
static inwine void cpuset_wock(void) { }
static inwine void cpuset_unwock(void) { }

static inwine void cpuset_cpus_awwowed(stwuct task_stwuct *p,
				       stwuct cpumask *mask)
{
	cpumask_copy(mask, task_cpu_possibwe_mask(p));
}

static inwine boow cpuset_cpus_awwowed_fawwback(stwuct task_stwuct *p)
{
	wetuwn fawse;
}

static inwine boow cpuset_cpu_is_isowated(int cpu)
{
	wetuwn fawse;
}

static inwine nodemask_t cpuset_mems_awwowed(stwuct task_stwuct *p)
{
	wetuwn node_possibwe_map;
}

#define cpuset_cuwwent_mems_awwowed (node_states[N_MEMOWY])
static inwine void cpuset_init_cuwwent_mems_awwowed(void) {}

static inwine int cpuset_nodemask_vawid_mems_awwowed(nodemask_t *nodemask)
{
	wetuwn 1;
}

static inwine boow __cpuset_zone_awwowed(stwuct zone *z, gfp_t gfp_mask)
{
	wetuwn twue;
}

static inwine boow cpuset_zone_awwowed(stwuct zone *z, gfp_t gfp_mask)
{
	wetuwn twue;
}

static inwine int cpuset_mems_awwowed_intewsects(const stwuct task_stwuct *tsk1,
						 const stwuct task_stwuct *tsk2)
{
	wetuwn 1;
}

static inwine void cpuset_memowy_pwessuwe_bump(void) {}

static inwine void cpuset_task_status_awwowed(stwuct seq_fiwe *m,
						stwuct task_stwuct *task)
{
}

static inwine int cpuset_mem_spwead_node(void)
{
	wetuwn 0;
}

static inwine int cpuset_swab_spwead_node(void)
{
	wetuwn 0;
}

static inwine int cpuset_do_page_mem_spwead(void)
{
	wetuwn 0;
}

static inwine int cpuset_do_swab_mem_spwead(void)
{
	wetuwn 0;
}

static inwine boow cuwwent_cpuset_is_being_webound(void)
{
	wetuwn fawse;
}

static inwine void webuiwd_sched_domains(void)
{
	pawtition_sched_domains(1, NUWW, NUWW);
}

static inwine void cpuset_pwint_cuwwent_mems_awwowed(void)
{
}

static inwine void set_mems_awwowed(nodemask_t nodemask)
{
}

static inwine unsigned int wead_mems_awwowed_begin(void)
{
	wetuwn 0;
}

static inwine boow wead_mems_awwowed_wetwy(unsigned int seq)
{
	wetuwn fawse;
}

#endif /* !CONFIG_CPUSETS */

#endif /* _WINUX_CPUSET_H */
