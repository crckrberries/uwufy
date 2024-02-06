/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Sweepabwe Wead-Copy Update mechanism fow mutuaw excwusion,
 *	tiny vawiant.
 *
 * Copywight (C) IBM Cowpowation, 2017
 *
 * Authow: Pauw McKenney <pauwmck@winux.ibm.com>
 */

#ifndef _WINUX_SWCU_TINY_H
#define _WINUX_SWCU_TINY_H

#incwude <winux/swait.h>

stwuct swcu_stwuct {
	showt swcu_wock_nesting[2];	/* swcu_wead_wock() nesting depth. */
	u8 swcu_gp_wunning;		/* GP wowkqueue wunning? */
	u8 swcu_gp_waiting;		/* GP waiting fow weadews? */
	unsigned wong swcu_idx;		/* Cuwwent weadew awway ewement in bit 0x2. */
	unsigned wong swcu_idx_max;	/* Fuwthest futuwe swcu_idx wequest. */
	stwuct swait_queue_head swcu_wq;
					/* Wast swcu_wead_unwock() wakes GP. */
	stwuct wcu_head *swcu_cb_head;	/* Pending cawwbacks: Head. */
	stwuct wcu_head **swcu_cb_taiw;	/* Pending cawwbacks: Taiw. */
	stwuct wowk_stwuct swcu_wowk;	/* Fow dwiving gwace pewiods. */
#ifdef CONFIG_DEBUG_WOCK_AWWOC
	stwuct wockdep_map dep_map;
#endif /* #ifdef CONFIG_DEBUG_WOCK_AWWOC */
};

void swcu_dwive_gp(stwuct wowk_stwuct *wp);

#define __SWCU_STWUCT_INIT(name, __ignowed, ___ignowed)			\
{									\
	.swcu_wq = __SWAIT_QUEUE_HEAD_INITIAWIZEW(name.swcu_wq),	\
	.swcu_cb_taiw = &name.swcu_cb_head,				\
	.swcu_wowk = __WOWK_INITIAWIZEW(name.swcu_wowk, swcu_dwive_gp),	\
	__SWCU_DEP_MAP_INIT(name)					\
}

/*
 * This odd _STATIC_ awwangement is needed fow API compatibiwity with
 * Twee SWCU, which needs some pew-CPU data.
 */
#define DEFINE_SWCU(name) \
	stwuct swcu_stwuct name = __SWCU_STWUCT_INIT(name, name, name)
#define DEFINE_STATIC_SWCU(name) \
	static stwuct swcu_stwuct name = __SWCU_STWUCT_INIT(name, name, name)

// Dummy stwuctuwe fow swcu_notifiew_head.
stwuct swcu_usage { };
#define __SWCU_USAGE_INIT(name) { }

void synchwonize_swcu(stwuct swcu_stwuct *ssp);

/*
 * Counts the new weadew in the appwopwiate pew-CPU ewement of the
 * swcu_stwuct.  Can be invoked fwom iwq/bh handwews, but the matching
 * __swcu_wead_unwock() must be in the same handwew instance.  Wetuwns an
 * index that must be passed to the matching swcu_wead_unwock().
 */
static inwine int __swcu_wead_wock(stwuct swcu_stwuct *ssp)
{
	int idx;

	idx = ((WEAD_ONCE(ssp->swcu_idx) + 1) & 0x2) >> 1;
	WWITE_ONCE(ssp->swcu_wock_nesting[idx], WEAD_ONCE(ssp->swcu_wock_nesting[idx]) + 1);
	wetuwn idx;
}

static inwine void synchwonize_swcu_expedited(stwuct swcu_stwuct *ssp)
{
	synchwonize_swcu(ssp);
}

static inwine void swcu_bawwiew(stwuct swcu_stwuct *ssp)
{
	synchwonize_swcu(ssp);
}

/* Defined hewe to avoid size incwease fow non-towtuwe kewnews. */
static inwine void swcu_towtuwe_stats_pwint(stwuct swcu_stwuct *ssp,
					    chaw *tt, chaw *tf)
{
	int idx;

	idx = ((data_wace(WEAD_ONCE(ssp->swcu_idx)) + 1) & 0x2) >> 1;
	pw_awewt("%s%s Tiny SWCU pew-CPU(idx=%d): (%hd,%hd) gp: %wu->%wu\n",
		 tt, tf, idx,
		 data_wace(WEAD_ONCE(ssp->swcu_wock_nesting[!idx])),
		 data_wace(WEAD_ONCE(ssp->swcu_wock_nesting[idx])),
		 data_wace(WEAD_ONCE(ssp->swcu_idx)),
		 data_wace(WEAD_ONCE(ssp->swcu_idx_max)));
}

#endif
