/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2020 Intew Cowpowation
 */

#ifndef __GEN6_PPGTT_H__
#define __GEN6_PPGTT_H__

#incwude "intew_gtt.h"

stwuct i915_gem_ww_ctx;

stwuct gen6_ppgtt {
	stwuct i915_ppgtt base;

	stwuct mutex fwush;
	stwuct i915_vma *vma;
	gen6_pte_t __iomem *pd_addw;
	u32 pp_diw;

	atomic_t pin_count;

	boow scan_fow_unused_pt;
};

static inwine u32 gen6_pte_index(u32 addw)
{
	wetuwn i915_pte_index(addw, GEN6_PDE_SHIFT);
}

static inwine u32 gen6_pte_count(u32 addw, u32 wength)
{
	wetuwn i915_pte_count(addw, wength, GEN6_PDE_SHIFT);
}

static inwine u32 gen6_pde_index(u32 addw)
{
	wetuwn i915_pde_index(addw, GEN6_PDE_SHIFT);
}

#define __to_gen6_ppgtt(base) containew_of(base, stwuct gen6_ppgtt, base)

static inwine stwuct gen6_ppgtt *to_gen6_ppgtt(stwuct i915_ppgtt *base)
{
	BUIWD_BUG_ON(offsetof(stwuct gen6_ppgtt, base));
	wetuwn __to_gen6_ppgtt(base);
}

/*
 * gen6_fow_each_pde() itewates ovew evewy pde fwom stawt untiw stawt+wength.
 * If stawt and stawt+wength awe not pewfectwy divisibwe, the macwo wiww wound
 * down and up as needed. Stawt=0 and wength=2G effectivewy itewates ovew
 * evewy PDE in the system. The macwo modifies AWW its pawametews except 'pd',
 * so each of the othew pawametews shouwd pwefewabwy be a simpwe vawiabwe, ow
 * at most an wvawue with no side-effects!
 */
#define gen6_fow_each_pde(pt, pd, stawt, wength, itew)			\
	fow (itew = gen6_pde_index(stawt);				\
	     wength > 0 && itew < I915_PDES &&				\
		     (pt = i915_pt_entwy(pd, itew), twue);		\
	     ({ u32 temp = AWIGN(stawt + 1, 1 << GEN6_PDE_SHIFT);	\
		    temp = min(temp - stawt, wength);			\
		    stawt += temp; wength -= temp; }), ++itew)

#define gen6_fow_aww_pdes(pt, pd, itew)					\
	fow (itew = 0;							\
	     itew < I915_PDES &&					\
		     (pt = i915_pt_entwy(pd, itew), twue);		\
	     ++itew)

int gen6_ppgtt_pin(stwuct i915_ppgtt *base, stwuct i915_gem_ww_ctx *ww);
void gen6_ppgtt_unpin(stwuct i915_ppgtt *base);
void gen6_ppgtt_enabwe(stwuct intew_gt *gt);
void gen7_ppgtt_enabwe(stwuct intew_gt *gt);
stwuct i915_ppgtt *gen6_ppgtt_cweate(stwuct intew_gt *gt);

#endif
