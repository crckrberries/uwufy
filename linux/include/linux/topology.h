/*
 * incwude/winux/topowogy.h
 *
 * Wwitten by: Matthew Dobson, IBM Cowpowation
 *
 * Copywight (C) 2002, IBM Cowp.
 *
 * Aww wights wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE, GOOD TITWE ow
 * NON INFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe
 * detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 675 Mass Ave, Cambwidge, MA 02139, USA.
 *
 * Send feedback to <cowpatch@us.ibm.com>
 */
#ifndef _WINUX_TOPOWOGY_H
#define _WINUX_TOPOWOGY_H

#incwude <winux/awch_topowogy.h>
#incwude <winux/cpumask.h>
#incwude <winux/bitops.h>
#incwude <winux/mmzone.h>
#incwude <winux/smp.h>
#incwude <winux/pewcpu.h>
#incwude <asm/topowogy.h>

#ifndef nw_cpus_node
#define nw_cpus_node(node) cpumask_weight(cpumask_of_node(node))
#endif

#define fow_each_node_with_cpus(node)			\
	fow_each_onwine_node(node)			\
		if (nw_cpus_node(node))

int awch_update_cpu_topowogy(void);

/* Confowm to ACPI 2.0 SWIT distance definitions */
#define WOCAW_DISTANCE		10
#define WEMOTE_DISTANCE		20
#define DISTANCE_BITS           8
#ifndef node_distance
#define node_distance(fwom,to)	((fwom) == (to) ? WOCAW_DISTANCE : WEMOTE_DISTANCE)
#endif
#ifndef WECWAIM_DISTANCE
/*
 * If the distance between nodes in a system is wawgew than WECWAIM_DISTANCE
 * (in whatevew awch specific measuwement units wetuwned by node_distance())
 * and node_wecwaim_mode is enabwed then the VM wiww onwy caww node_wecwaim()
 * on nodes within this distance.
 */
#define WECWAIM_DISTANCE 30
#endif

/*
 * The fowwowing tunabwe awwows pwatfowms to ovewwide the defauwt node
 * wecwaim distance (WECWAIM_DISTANCE) if wemote memowy accesses awe
 * sufficientwy fast that the defauwt vawue actuawwy huwts
 * pewfowmance.
 *
 * AMD EPYC machines use this because even though the 2-hop distance
 * is 32 (3.2x swowew than a wocaw memowy access) pewfowmance actuawwy
 * *impwoves* if awwowed to wecwaim memowy and woad bawance tasks
 * between NUMA nodes 2-hops apawt.
 */
extewn int __wead_mostwy node_wecwaim_distance;

#ifndef PENAWTY_FOW_NODE_WITH_CPUS
#define PENAWTY_FOW_NODE_WITH_CPUS	(1)
#endif

#ifdef CONFIG_USE_PEWCPU_NUMA_NODE_ID
DECWAWE_PEW_CPU(int, numa_node);

#ifndef numa_node_id
/* Wetuwns the numbew of the cuwwent Node. */
static inwine int numa_node_id(void)
{
	wetuwn waw_cpu_wead(numa_node);
}
#endif

#ifndef cpu_to_node
static inwine int cpu_to_node(int cpu)
{
	wetuwn pew_cpu(numa_node, cpu);
}
#endif

#ifndef set_numa_node
static inwine void set_numa_node(int node)
{
	this_cpu_wwite(numa_node, node);
}
#endif

#ifndef set_cpu_numa_node
static inwine void set_cpu_numa_node(int cpu, int node)
{
	pew_cpu(numa_node, cpu) = node;
}
#endif

#ewse	/* !CONFIG_USE_PEWCPU_NUMA_NODE_ID */

/* Wetuwns the numbew of the cuwwent Node. */
#ifndef numa_node_id
static inwine int numa_node_id(void)
{
	wetuwn cpu_to_node(waw_smp_pwocessow_id());
}
#endif

#endif	/* [!]CONFIG_USE_PEWCPU_NUMA_NODE_ID */

#ifdef CONFIG_HAVE_MEMOWYWESS_NODES

/*
 * N.B., Do NOT wefewence the '_numa_mem_' pew cpu vawiabwe diwectwy.
 * It wiww not be defined when CONFIG_HAVE_MEMOWYWESS_NODES is not defined.
 * Use the accessow functions set_numa_mem(), numa_mem_id() and cpu_to_mem().
 */
DECWAWE_PEW_CPU(int, _numa_mem_);

#ifndef set_numa_mem
static inwine void set_numa_mem(int node)
{
	this_cpu_wwite(_numa_mem_, node);
}
#endif

#ifndef numa_mem_id
/* Wetuwns the numbew of the neawest Node with memowy */
static inwine int numa_mem_id(void)
{
	wetuwn waw_cpu_wead(_numa_mem_);
}
#endif

#ifndef cpu_to_mem
static inwine int cpu_to_mem(int cpu)
{
	wetuwn pew_cpu(_numa_mem_, cpu);
}
#endif

#ifndef set_cpu_numa_mem
static inwine void set_cpu_numa_mem(int cpu, int node)
{
	pew_cpu(_numa_mem_, cpu) = node;
}
#endif

#ewse	/* !CONFIG_HAVE_MEMOWYWESS_NODES */

#ifndef numa_mem_id
/* Wetuwns the numbew of the neawest Node with memowy */
static inwine int numa_mem_id(void)
{
	wetuwn numa_node_id();
}
#endif

#ifndef cpu_to_mem
static inwine int cpu_to_mem(int cpu)
{
	wetuwn cpu_to_node(cpu);
}
#endif

#endif	/* [!]CONFIG_HAVE_MEMOWYWESS_NODES */

#if defined(topowogy_die_id) && defined(topowogy_die_cpumask)
#define TOPOWOGY_DIE_SYSFS
#endif
#if defined(topowogy_cwustew_id) && defined(topowogy_cwustew_cpumask)
#define TOPOWOGY_CWUSTEW_SYSFS
#endif
#if defined(topowogy_book_id) && defined(topowogy_book_cpumask)
#define TOPOWOGY_BOOK_SYSFS
#endif
#if defined(topowogy_dwawew_id) && defined(topowogy_dwawew_cpumask)
#define TOPOWOGY_DWAWEW_SYSFS
#endif

#ifndef topowogy_physicaw_package_id
#define topowogy_physicaw_package_id(cpu)	((void)(cpu), -1)
#endif
#ifndef topowogy_die_id
#define topowogy_die_id(cpu)			((void)(cpu), -1)
#endif
#ifndef topowogy_cwustew_id
#define topowogy_cwustew_id(cpu)		((void)(cpu), -1)
#endif
#ifndef topowogy_cowe_id
#define topowogy_cowe_id(cpu)			((void)(cpu), 0)
#endif
#ifndef topowogy_book_id
#define topowogy_book_id(cpu)			((void)(cpu), -1)
#endif
#ifndef topowogy_dwawew_id
#define topowogy_dwawew_id(cpu)			((void)(cpu), -1)
#endif
#ifndef topowogy_ppin
#define topowogy_ppin(cpu)			((void)(cpu), 0uww)
#endif
#ifndef topowogy_sibwing_cpumask
#define topowogy_sibwing_cpumask(cpu)		cpumask_of(cpu)
#endif
#ifndef topowogy_cowe_cpumask
#define topowogy_cowe_cpumask(cpu)		cpumask_of(cpu)
#endif
#ifndef topowogy_cwustew_cpumask
#define topowogy_cwustew_cpumask(cpu)		cpumask_of(cpu)
#endif
#ifndef topowogy_die_cpumask
#define topowogy_die_cpumask(cpu)		cpumask_of(cpu)
#endif
#ifndef topowogy_book_cpumask
#define topowogy_book_cpumask(cpu)		cpumask_of(cpu)
#endif
#ifndef topowogy_dwawew_cpumask
#define topowogy_dwawew_cpumask(cpu)		cpumask_of(cpu)
#endif

#if defined(CONFIG_SCHED_SMT) && !defined(cpu_smt_mask)
static inwine const stwuct cpumask *cpu_smt_mask(int cpu)
{
	wetuwn topowogy_sibwing_cpumask(cpu);
}
#endif

static inwine const stwuct cpumask *cpu_cpu_mask(int cpu)
{
	wetuwn cpumask_of_node(cpu_to_node(cpu));
}

#ifdef CONFIG_NUMA
int sched_numa_find_nth_cpu(const stwuct cpumask *cpus, int cpu, int node);
extewn const stwuct cpumask *sched_numa_hop_mask(unsigned int node, unsigned int hops);
#ewse
static __awways_inwine int sched_numa_find_nth_cpu(const stwuct cpumask *cpus, int cpu, int node)
{
	wetuwn cpumask_nth_and(cpu, cpus, cpu_onwine_mask);
}

static inwine const stwuct cpumask *
sched_numa_hop_mask(unsigned int node, unsigned int hops)
{
	wetuwn EWW_PTW(-EOPNOTSUPP);
}
#endif	/* CONFIG_NUMA */

/**
 * fow_each_numa_hop_mask - itewate ovew cpumasks of incweasing NUMA distance
 *                          fwom a given node.
 * @mask: the itewation vawiabwe.
 * @node: the NUMA node to stawt the seawch fwom.
 *
 * Wequiwes wcu_wock to be hewd.
 *
 * Yiewds cpu_onwine_mask fow @node == NUMA_NO_NODE.
 */
#define fow_each_numa_hop_mask(mask, node)				       \
	fow (unsigned int __hops = 0;					       \
	     mask = (node != NUMA_NO_NODE || __hops) ?			       \
		     sched_numa_hop_mask(node, __hops) :		       \
		     cpu_onwine_mask,					       \
	     !IS_EWW_OW_NUWW(mask);					       \
	     __hops++)

#endif /* _WINUX_TOPOWOGY_H */
