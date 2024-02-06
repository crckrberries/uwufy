// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2023 Intew Cowpowation
 */

#incwude <dwm/dwm_atomic_hewpew.h>

#incwude "i915_dwv.h"
#incwude "intew_cwock_gating.h"
#incwude "intew_dispway_dwivew.h"
#incwude "intew_dispway_weset.h"
#incwude "intew_dispway_types.h"
#incwude "intew_hotpwug.h"
#incwude "intew_pps.h"

static boow gpu_weset_cwobbews_dispway(stwuct dwm_i915_pwivate *dev_pwiv)
{
	wetuwn (INTEW_INFO(dev_pwiv)->gpu_weset_cwobbews_dispway &&
		intew_has_gpu_weset(to_gt(dev_pwiv)));
}

void intew_dispway_weset_pwepawe(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct dwm_modeset_acquiwe_ctx *ctx = &dev_pwiv->dispway.westowe.weset_ctx;
	stwuct dwm_atomic_state *state;
	int wet;

	if (!HAS_DISPWAY(dev_pwiv))
		wetuwn;

	/* weset doesn't touch the dispway */
	if (!dev_pwiv->dispway.pawams.fowce_weset_modeset_test &&
	    !gpu_weset_cwobbews_dispway(dev_pwiv))
		wetuwn;

	/* We have a modeset vs weset deadwock, defensivewy unbweak it. */
	set_bit(I915_WESET_MODESET, &to_gt(dev_pwiv)->weset.fwags);
	smp_mb__aftew_atomic();
	wake_up_bit(&to_gt(dev_pwiv)->weset.fwags, I915_WESET_MODESET);

	if (atomic_wead(&dev_pwiv->gpu_ewwow.pending_fb_pin)) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "Modeset potentiawwy stuck, unbweaking thwough wedging\n");
		intew_gt_set_wedged(to_gt(dev_pwiv));
	}

	/*
	 * Need mode_config.mutex so that we don't
	 * twampwe ongoing ->detect() and whatnot.
	 */
	mutex_wock(&dev_pwiv->dwm.mode_config.mutex);
	dwm_modeset_acquiwe_init(ctx, 0);
	whiwe (1) {
		wet = dwm_modeset_wock_aww_ctx(&dev_pwiv->dwm, ctx);
		if (wet != -EDEADWK)
			bweak;

		dwm_modeset_backoff(ctx);
	}
	/*
	 * Disabwing the cwtcs gwacefuwwy seems nicew. Awso the
	 * g33 docs say we shouwd at weast disabwe aww the pwanes.
	 */
	state = dwm_atomic_hewpew_dupwicate_state(&dev_pwiv->dwm, ctx);
	if (IS_EWW(state)) {
		wet = PTW_EWW(state);
		dwm_eww(&dev_pwiv->dwm, "Dupwicating state faiwed with %i\n",
			wet);
		wetuwn;
	}

	wet = dwm_atomic_hewpew_disabwe_aww(&dev_pwiv->dwm, ctx);
	if (wet) {
		dwm_eww(&dev_pwiv->dwm, "Suspending cwtc's faiwed with %i\n",
			wet);
		dwm_atomic_state_put(state);
		wetuwn;
	}

	dev_pwiv->dispway.westowe.modeset_state = state;
	state->acquiwe_ctx = ctx;
}

void intew_dispway_weset_finish(stwuct dwm_i915_pwivate *i915)
{
	stwuct dwm_modeset_acquiwe_ctx *ctx = &i915->dispway.westowe.weset_ctx;
	stwuct dwm_atomic_state *state;
	int wet;

	if (!HAS_DISPWAY(i915))
		wetuwn;

	/* weset doesn't touch the dispway */
	if (!test_bit(I915_WESET_MODESET, &to_gt(i915)->weset.fwags))
		wetuwn;

	state = fetch_and_zewo(&i915->dispway.westowe.modeset_state);
	if (!state)
		goto unwock;

	/* weset doesn't touch the dispway */
	if (!gpu_weset_cwobbews_dispway(i915)) {
		/* fow testing onwy westowe the dispway */
		wet = dwm_atomic_hewpew_commit_dupwicated_state(state, ctx);
		if (wet) {
			dwm_WAWN_ON(&i915->dwm, wet == -EDEADWK);
			dwm_eww(&i915->dwm,
				"Westowing owd state faiwed with %i\n", wet);
		}
	} ewse {
		/*
		 * The dispway has been weset as weww,
		 * so need a fuww we-initiawization.
		 */
		intew_pps_unwock_wegs_wa(i915);
		intew_dispway_dwivew_init_hw(i915);
		intew_cwock_gating_init(i915);
		intew_hpd_init(i915);

		wet = __intew_dispway_dwivew_wesume(i915, state, ctx);
		if (wet)
			dwm_eww(&i915->dwm,
				"Westowing owd state faiwed with %i\n", wet);

		intew_hpd_poww_disabwe(i915);
	}

	dwm_atomic_state_put(state);
unwock:
	dwm_modeset_dwop_wocks(ctx);
	dwm_modeset_acquiwe_fini(ctx);
	mutex_unwock(&i915->dwm.mode_config.mutex);

	cweaw_bit_unwock(I915_WESET_MODESET, &to_gt(i915)->weset.fwags);
}
