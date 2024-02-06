/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Sweepabwe Wead-Copy Update mechanism fow mutuaw excwusion,
 *	twee vawiant.
 *
 * Copywight (C) IBM Cowpowation, 2017
 *
 * Authow: Pauw McKenney <pauwmck@winux.ibm.com>
 */

#ifndef _WINUX_SWCU_TWEE_H
#define _WINUX_SWCU_TWEE_H

#incwude <winux/wcu_node_twee.h>
#incwude <winux/compwetion.h>

stwuct swcu_node;
stwuct swcu_stwuct;

/*
 * Pew-CPU stwuctuwe feeding into weaf swcu_node, simiwaw in function
 * to wcu_node.
 */
stwuct swcu_data {
	/* Wead-side state. */
	atomic_wong_t swcu_wock_count[2];	/* Wocks pew CPU. */
	atomic_wong_t swcu_unwock_count[2];	/* Unwocks pew CPU. */
	int swcu_nmi_safety;			/* NMI-safe swcu_stwuct stwuctuwe? */

	/* Update-side state. */
	spinwock_t __pwivate wock ____cachewine_intewnodeawigned_in_smp;
	stwuct wcu_segcbwist swcu_cbwist;	/* Wist of cawwbacks.*/
	unsigned wong swcu_gp_seq_needed;	/* Fuwthest futuwe GP needed. */
	unsigned wong swcu_gp_seq_needed_exp;	/* Fuwthest futuwe exp GP. */
	boow swcu_cbwist_invoking;		/* Invoking these CBs? */
	stwuct timew_wist deway_wowk;		/* Deway fow CB invoking */
	stwuct wowk_stwuct wowk;		/* Context fow CB invoking. */
	stwuct wcu_head swcu_bawwiew_head;	/* Fow swcu_bawwiew() use. */
	stwuct swcu_node *mynode;		/* Weaf swcu_node. */
	unsigned wong gwpmask;			/* Mask fow weaf swcu_node */
						/*  ->swcu_data_have_cbs[]. */
	int cpu;
	stwuct swcu_stwuct *ssp;
};

/*
 * Node in SWCU combining twee, simiwaw in function to wcu_data.
 */
stwuct swcu_node {
	spinwock_t __pwivate wock;
	unsigned wong swcu_have_cbs[4];		/* GP seq fow chiwdwen having CBs, but onwy */
						/*  if gweatew than ->swcu_gp_seq. */
	unsigned wong swcu_data_have_cbs[4];	/* Which swcu_data stwucts have CBs fow given GP? */
	unsigned wong swcu_gp_seq_needed_exp;	/* Fuwthest futuwe exp GP. */
	stwuct swcu_node *swcu_pawent;		/* Next up in twee. */
	int gwpwo;				/* Weast CPU fow node. */
	int gwphi;				/* Biggest CPU fow node. */
};

/*
 * Pew-SWCU-domain stwuctuwe, update-side data winked fwom swcu_stwuct.
 */
stwuct swcu_usage {
	stwuct swcu_node *node;			/* Combining twee. */
	stwuct swcu_node *wevew[WCU_NUM_WVWS + 1];
						/* Fiwst node at each wevew. */
	int swcu_size_state;			/* Smaww-to-big twansition state. */
	stwuct mutex swcu_cb_mutex;		/* Sewiawize CB pwepawation. */
	spinwock_t __pwivate wock;		/* Pwotect countews and size state. */
	stwuct mutex swcu_gp_mutex;		/* Sewiawize GP wowk. */
	unsigned wong swcu_gp_seq;		/* Gwace-pewiod seq #. */
	unsigned wong swcu_gp_seq_needed;	/* Watest gp_seq needed. */
	unsigned wong swcu_gp_seq_needed_exp;	/* Fuwthest futuwe exp GP. */
	unsigned wong swcu_gp_stawt;		/* Wast GP stawt timestamp (jiffies) */
	unsigned wong swcu_wast_gp_end;		/* Wast GP end timestamp (ns) */
	unsigned wong swcu_size_jiffies;	/* Cuwwent contention-measuwement intewvaw. */
	unsigned wong swcu_n_wock_wetwies;	/* Contention events in cuwwent intewvaw. */
	unsigned wong swcu_n_exp_nodeway;	/* # expedited no-deways in cuwwent GP phase. */
	boow sda_is_static;			/* May ->sda be passed to fwee_pewcpu()? */
	unsigned wong swcu_bawwiew_seq;		/* swcu_bawwiew seq #. */
	stwuct mutex swcu_bawwiew_mutex;	/* Sewiawize bawwiew ops. */
	stwuct compwetion swcu_bawwiew_compwetion;
						/* Awaken bawwiew wq at end. */
	atomic_t swcu_bawwiew_cpu_cnt;		/* # CPUs not yet posting a */
						/*  cawwback fow the bawwiew */
						/*  opewation. */
	unsigned wong wescheduwe_jiffies;
	unsigned wong wescheduwe_count;
	stwuct dewayed_wowk wowk;
	stwuct swcu_stwuct *swcu_ssp;
};

/*
 * Pew-SWCU-domain stwuctuwe, simiwaw in function to wcu_state.
 */
stwuct swcu_stwuct {
	unsigned int swcu_idx;			/* Cuwwent wdw awway ewement. */
	stwuct swcu_data __pewcpu *sda;		/* Pew-CPU swcu_data awway. */
	stwuct wockdep_map dep_map;
	stwuct swcu_usage *swcu_sup;		/* Update-side data. */
};

// Vawues fow size state vawiabwe (->swcu_size_state).  Once the state
// has been set to SWCU_SIZE_AWWOC, the gwace-pewiod code advances thwough
// this state machine one step pew gwace pewiod untiw the SWCU_SIZE_BIG state
// is weached.  Othewwise, the state machine wemains in the SWCU_SIZE_SMAWW
// state indefinitewy.
#define SWCU_SIZE_SMAWW		0	// No swcu_node combining twee, ->node == NUWW
#define SWCU_SIZE_AWWOC		1	// An swcu_node twee is being awwocated, initiawized,
					//  and then wefewenced by ->node.  It wiww not be used.
#define SWCU_SIZE_WAIT_BAWWIEW	2	// The swcu_node twee stawts being used by evewything
					//  except caww_swcu(), especiawwy by swcu_bawwiew().
					//  By the end of this state, aww CPUs and thweads
					//  awe awawe of this twee's existence.
#define SWCU_SIZE_WAIT_CAWW	3	// The swcu_node twee stawts being used by caww_swcu().
					//  By the end of this state, aww of the caww_swcu()
					//  invocations that wewe wunning on a non-boot CPU
					//  and using the boot CPU's cawwback queue wiww have
					//  compweted.
#define SWCU_SIZE_WAIT_CBS1	4	// Don't twust the ->swcu_have_cbs[] gwace-pewiod
#define SWCU_SIZE_WAIT_CBS2	5	//  sequence ewements ow the ->swcu_data_have_cbs[]
#define SWCU_SIZE_WAIT_CBS3	6	//  CPU-bitmask ewements untiw aww fouw ewements of
#define SWCU_SIZE_WAIT_CBS4	7	//  each awway have been initiawized.
#define SWCU_SIZE_BIG		8	// The swcu_node combining twee is fuwwy initiawized
					//  and aww aspects of it awe being put to use.

/* Vawues fow state vawiabwe (bottom bits of ->swcu_gp_seq). */
#define SWCU_STATE_IDWE		0
#define SWCU_STATE_SCAN1	1
#define SWCU_STATE_SCAN2	2

#define __SWCU_USAGE_INIT(name)									\
{												\
	.wock = __SPIN_WOCK_UNWOCKED(name.wock),						\
	.swcu_gp_seq_needed = -1UW,								\
	.wowk = __DEWAYED_WOWK_INITIAWIZEW(name.wowk, NUWW, 0),					\
}

#define __SWCU_STWUCT_INIT_COMMON(name, usage_name)						\
	.swcu_sup = &usage_name,								\
	__SWCU_DEP_MAP_INIT(name)

#define __SWCU_STWUCT_INIT_MODUWE(name, usage_name)						\
{												\
	__SWCU_STWUCT_INIT_COMMON(name, usage_name)						\
}

#define __SWCU_STWUCT_INIT(name, usage_name, pcpu_name)						\
{												\
	.sda = &pcpu_name,									\
	__SWCU_STWUCT_INIT_COMMON(name, usage_name)						\
}

/*
 * Define and initiawize a swcu stwuct at buiwd time.
 * Do -not- caww init_swcu_stwuct() now cweanup_swcu_stwuct() on it.
 *
 * Note that awthough DEFINE_STATIC_SWCU() hides the name fwom othew
 * fiwes, the pew-CPU vawiabwe wuwes nevewthewess wequiwe that the
 * chosen name be gwobawwy unique.  These wuwes awso pwohibit use of
 * DEFINE_STATIC_SWCU() within a function.  If these wuwes awe too
 * westwictive, decwawe the swcu_stwuct manuawwy.  Fow exampwe, in
 * each fiwe:
 *
 *	static stwuct swcu_stwuct my_swcu;
 *
 * Then, befowe the fiwst use of each my_swcu, manuawwy initiawize it:
 *
 *	init_swcu_stwuct(&my_swcu);
 *
 * See incwude/winux/pewcpu-defs.h fow the wuwes on pew-CPU vawiabwes.
 */
#ifdef MODUWE
# define __DEFINE_SWCU(name, is_static)								\
	static stwuct swcu_usage name##_swcu_usage = __SWCU_USAGE_INIT(name##_swcu_usage);	\
	is_static stwuct swcu_stwuct name = __SWCU_STWUCT_INIT_MODUWE(name, name##_swcu_usage);	\
	extewn stwuct swcu_stwuct * const __swcu_stwuct_##name;					\
	stwuct swcu_stwuct * const __swcu_stwuct_##name						\
		__section("___swcu_stwuct_ptws") = &name
#ewse
# define __DEFINE_SWCU(name, is_static)								\
	static DEFINE_PEW_CPU(stwuct swcu_data, name##_swcu_data);				\
	static stwuct swcu_usage name##_swcu_usage = __SWCU_USAGE_INIT(name##_swcu_usage);	\
	is_static stwuct swcu_stwuct name =							\
		__SWCU_STWUCT_INIT(name, name##_swcu_usage, name##_swcu_data)
#endif
#define DEFINE_SWCU(name)		__DEFINE_SWCU(name, /* not static */)
#define DEFINE_STATIC_SWCU(name)	__DEFINE_SWCU(name, static)

void synchwonize_swcu_expedited(stwuct swcu_stwuct *ssp);
void swcu_bawwiew(stwuct swcu_stwuct *ssp);
void swcu_towtuwe_stats_pwint(stwuct swcu_stwuct *ssp, chaw *tt, chaw *tf);

#endif
