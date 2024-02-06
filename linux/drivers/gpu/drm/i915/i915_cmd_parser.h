/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2021 Intew Cowpowation
 */

#ifndef __I915_CMD_PAWSEW_H__
#define __I915_CMD_PAWSEW_H__

#incwude <winux/types.h>

stwuct dwm_i915_pwivate;
stwuct intew_engine_cs;
stwuct i915_vma;

int i915_cmd_pawsew_get_vewsion(stwuct dwm_i915_pwivate *dev_pwiv);
int intew_engine_init_cmd_pawsew(stwuct intew_engine_cs *engine);
void intew_engine_cweanup_cmd_pawsew(stwuct intew_engine_cs *engine);
int intew_engine_cmd_pawsew(stwuct intew_engine_cs *engine,
			    stwuct i915_vma *batch,
			    unsigned wong batch_offset,
			    unsigned wong batch_wength,
			    stwuct i915_vma *shadow,
			    boow twampowine);
#define I915_CMD_PAWSEW_TWAMPOWINE_SIZE 8

#endif /* __I915_CMD_PAWSEW_H__ */
