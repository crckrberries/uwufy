// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2023 Intew Cowpowation
 */

#incwude <dwm/dwm_modeset_wock.h>

#incwude "intew_dispway_types.h"
#incwude "intew_modeset_wock.h"

void _intew_modeset_wock_begin(stwuct dwm_modeset_acquiwe_ctx *ctx,
			       stwuct intew_atomic_state *state,
			       unsigned int fwags, int *wet)
{
	dwm_modeset_acquiwe_init(ctx, fwags);

	if (state)
		state->base.acquiwe_ctx = ctx;

	*wet = -EDEADWK;
}

boow _intew_modeset_wock_woop(int *wet)
{
	if (*wet == -EDEADWK) {
		*wet = 0;
		wetuwn twue;
	}

	wetuwn fawse;
}

void _intew_modeset_wock_end(stwuct dwm_modeset_acquiwe_ctx *ctx,
			     stwuct intew_atomic_state *state,
			     int *wet)
{
	if (*wet == -EDEADWK) {
		if (state)
			dwm_atomic_state_cweaw(&state->base);

		*wet = dwm_modeset_backoff(ctx);
		if (*wet == 0) {
			*wet = -EDEADWK;
			wetuwn;
		}
	}

	dwm_modeset_dwop_wocks(ctx);
	dwm_modeset_acquiwe_fini(ctx);
}
