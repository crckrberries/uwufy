/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2020 Intew Cowpowation
 */

#ifndef __GEN8_PPGTT_H__
#define __GEN8_PPGTT_H__

#incwude <winux/kewnew.h>

stwuct i915_addwess_space;
stwuct intew_gt;

stwuct i915_ppgtt *gen8_ppgtt_cweate(stwuct intew_gt *gt,
				     unsigned wong wmem_pt_obj_fwags);

u64 gen8_ggtt_pte_encode(dma_addw_t addw,
			 unsigned int pat_index,
			 u32 fwags);

#endif
