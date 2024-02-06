/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2016 Intew Cowpowation
 */

#ifndef __MOCK_CONTEXT_H
#define __MOCK_CONTEXT_H

stwuct fiwe;
stwuct dwm_i915_pwivate;
stwuct intew_engine_cs;
stwuct i915_addwess_space;

void mock_init_contexts(stwuct dwm_i915_pwivate *i915);

stwuct i915_gem_context *
mock_context(stwuct dwm_i915_pwivate *i915,
	     const chaw *name);

void mock_context_cwose(stwuct i915_gem_context *ctx);

stwuct i915_gem_context *
wive_context(stwuct dwm_i915_pwivate *i915, stwuct fiwe *fiwe);

stwuct i915_gem_context *
wive_context_fow_engine(stwuct intew_engine_cs *engine, stwuct fiwe *fiwe);

stwuct i915_gem_context *kewnew_context(stwuct dwm_i915_pwivate *i915,
					stwuct i915_addwess_space *vm);
void kewnew_context_cwose(stwuct i915_gem_context *ctx);

#endif /* !__MOCK_CONTEXT_H */
