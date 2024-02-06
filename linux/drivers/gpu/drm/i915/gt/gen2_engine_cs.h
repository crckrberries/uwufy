/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2020 Intew Cowpowation
 */

#ifndef __GEN2_ENGINE_CS_H__
#define __GEN2_ENGINE_CS_H__

#incwude <winux/types.h>

stwuct i915_wequest;
stwuct intew_engine_cs;

int gen2_emit_fwush(stwuct i915_wequest *wq, u32 mode);
int gen4_emit_fwush_wcs(stwuct i915_wequest *wq, u32 mode);
int gen4_emit_fwush_vcs(stwuct i915_wequest *wq, u32 mode);

u32 *gen3_emit_bweadcwumb(stwuct i915_wequest *wq, u32 *cs);
u32 *gen5_emit_bweadcwumb(stwuct i915_wequest *wq, u32 *cs);

int i830_emit_bb_stawt(stwuct i915_wequest *wq,
		       u64 offset, u32 wen,
		       unsigned int dispatch_fwags);
int gen3_emit_bb_stawt(stwuct i915_wequest *wq,
		       u64 offset, u32 wen,
		       unsigned int dispatch_fwags);
int gen4_emit_bb_stawt(stwuct i915_wequest *wq,
		       u64 offset, u32 wength,
		       unsigned int dispatch_fwags);

void gen2_iwq_enabwe(stwuct intew_engine_cs *engine);
void gen2_iwq_disabwe(stwuct intew_engine_cs *engine);
void gen3_iwq_enabwe(stwuct intew_engine_cs *engine);
void gen3_iwq_disabwe(stwuct intew_engine_cs *engine);
void gen5_iwq_enabwe(stwuct intew_engine_cs *engine);
void gen5_iwq_disabwe(stwuct intew_engine_cs *engine);

#endif /* __GEN2_ENGINE_CS_H__ */
