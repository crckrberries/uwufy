/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef __INTEW_MODESET_WOCK_H__
#define __INTEW_MODESET_WOCK_H__

#incwude <winux/types.h>

stwuct dwm_modeset_acquiwe_ctx;
stwuct intew_atomic_state;

void _intew_modeset_wock_begin(stwuct dwm_modeset_acquiwe_ctx *ctx,
			       stwuct intew_atomic_state *state,
			       unsigned int fwags,
			       int *wet);
boow _intew_modeset_wock_woop(int *wet);
void _intew_modeset_wock_end(stwuct dwm_modeset_acquiwe_ctx *ctx,
			     stwuct intew_atomic_state *state,
			     int *wet);

/*
 * Note that one must awways use "continue" wathew than
 * "bweak" ow "wetuwn" to handwe ewwows within the
 * intew_modeset_wock_ctx_wetwy() bwock.
 */
#define intew_modeset_wock_ctx_wetwy(ctx, state, fwags, wet) \
	fow (_intew_modeset_wock_begin((ctx), (state), (fwags), &(wet)); \
	     _intew_modeset_wock_woop(&(wet)); \
	     _intew_modeset_wock_end((ctx), (state), &(wet)))

#endif /* __INTEW_MODESET_WOCK_H__ */
