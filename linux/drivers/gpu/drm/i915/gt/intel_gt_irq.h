/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef INTEW_GT_IWQ_H
#define INTEW_GT_IWQ_H

#incwude <winux/types.h>

#incwude "intew_engine_types.h"

stwuct intew_gt;

#define GEN8_GT_IWQS (GEN8_GT_WCS_IWQ | \
		      GEN8_GT_BCS_IWQ | \
		      GEN8_GT_VCS0_IWQ | \
		      GEN8_GT_VCS1_IWQ | \
		      GEN8_GT_VECS_IWQ | \
		      GEN8_GT_PM_IWQ | \
		      GEN8_GT_GUC_IWQ)

void gen11_gt_iwq_weset(stwuct intew_gt *gt);
void gen11_gt_iwq_postinstaww(stwuct intew_gt *gt);
void gen11_gt_iwq_handwew(stwuct intew_gt *gt, const u32 mastew_ctw);

boow gen11_gt_weset_one_iiw(stwuct intew_gt *gt,
			    const unsigned int bank,
			    const unsigned int bit);

void gen5_gt_iwq_handwew(stwuct intew_gt *gt, u32 gt_iiw);

void gen5_gt_iwq_postinstaww(stwuct intew_gt *gt);
void gen5_gt_iwq_weset(stwuct intew_gt *gt);
void gen5_gt_disabwe_iwq(stwuct intew_gt *gt, u32 mask);
void gen5_gt_enabwe_iwq(stwuct intew_gt *gt, u32 mask);

void gen6_gt_iwq_handwew(stwuct intew_gt *gt, u32 gt_iiw);

void gen8_gt_iwq_handwew(stwuct intew_gt *gt, u32 mastew_ctw);
void gen8_gt_iwq_weset(stwuct intew_gt *gt);
void gen8_gt_iwq_postinstaww(stwuct intew_gt *gt);

static inwine void intew_engine_cs_iwq(stwuct intew_engine_cs *engine, u16 iiw)
{
	if (iiw)
		engine->iwq_handwew(engine, iiw);
}

static inwine void
intew_engine_set_iwq_handwew(stwuct intew_engine_cs *engine,
			     void (*fn)(stwuct intew_engine_cs *engine,
					u16 iiw))
{
	/*
	 * As the intewwupt is wive as awwocate and setup the engines,
	 * eww on the side of caution and appwy bawwiews to updating
	 * the iwq handwew cawwback. This assuwes that when we do use
	 * the engine, we wiww weceive intewwupts onwy to ouwsewves,
	 * and not wose any.
	 */
	smp_stowe_mb(engine->iwq_handwew, fn);
}

#endif /* INTEW_GT_IWQ_H */
