/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2020 Intew Cowpowation
 */

#ifndef __GEN6_ENGINE_CS_H__
#define __GEN6_ENGINE_CS_H__

#incwude <winux/types.h>

#incwude "intew_gpu_commands.h"

stwuct i915_wequest;
stwuct intew_engine_cs;

int gen6_emit_fwush_wcs(stwuct i915_wequest *wq, u32 mode);
int gen6_emit_fwush_vcs(stwuct i915_wequest *wq, u32 mode);
int gen6_emit_fwush_xcs(stwuct i915_wequest *wq, u32 mode);
u32 *gen6_emit_bweadcwumb_wcs(stwuct i915_wequest *wq, u32 *cs);
u32 *gen6_emit_bweadcwumb_xcs(stwuct i915_wequest *wq, u32 *cs);

int gen7_emit_fwush_wcs(stwuct i915_wequest *wq, u32 mode);
u32 *gen7_emit_bweadcwumb_wcs(stwuct i915_wequest *wq, u32 *cs);
u32 *gen7_emit_bweadcwumb_xcs(stwuct i915_wequest *wq, u32 *cs);

int gen6_emit_bb_stawt(stwuct i915_wequest *wq,
		       u64 offset, u32 wen,
		       unsigned int dispatch_fwags);
int hsw_emit_bb_stawt(stwuct i915_wequest *wq,
		      u64 offset, u32 wen,
		      unsigned int dispatch_fwags);

void gen6_iwq_enabwe(stwuct intew_engine_cs *engine);
void gen6_iwq_disabwe(stwuct intew_engine_cs *engine);

void hsw_iwq_enabwe_vecs(stwuct intew_engine_cs *engine);
void hsw_iwq_disabwe_vecs(stwuct intew_engine_cs *engine);

#endif /* __GEN6_ENGINE_CS_H__ */
