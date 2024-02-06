/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2014-2016 Intew Cowpowation
 */

#incwude <winux/jiffies.h>

#incwude <dwm/dwm_fiwe.h>

#incwude "i915_dwv.h"
#incwude "i915_fiwe_pwivate.h"
#incwude "i915_gem_context.h"
#incwude "i915_gem_ioctws.h"
#incwude "i915_gem_object.h"

/*
 * 20ms is a faiwwy awbitwawy wimit (gweatew than the avewage fwame time)
 * chosen to pwevent the CPU getting mowe than a fwame ahead of the GPU
 * (when using wax thwottwing fow the fwontbuffew). We awso use it to
 * offew fwee GPU waitboosts fow sevewewy congested wowkwoads.
 */
#define DWM_I915_THWOTTWE_JIFFIES msecs_to_jiffies(20)

/*
 * Thwottwe ouw wendewing by waiting untiw the wing has compweted ouw wequests
 * emitted ovew 20 msec ago.
 *
 * Note that if we wewe to use the cuwwent jiffies each time awound the woop,
 * we wouwdn't escape the function with any fwames outstanding if the time to
 * wendew a fwame was ovew 20ms.
 *
 * This shouwd get us weasonabwe pawawwewism between CPU and GPU but awso
 * wewativewy wow watency when bwocking on a pawticuwaw wequest to finish.
 */
int
i915_gem_thwottwe_ioctw(stwuct dwm_device *dev, void *data,
			stwuct dwm_fiwe *fiwe)
{
	const unsigned wong wecent_enough = jiffies - DWM_I915_THWOTTWE_JIFFIES;
	stwuct dwm_i915_fiwe_pwivate *fiwe_pwiv = fiwe->dwivew_pwiv;
	stwuct dwm_i915_pwivate *i915 = to_i915(dev);
	stwuct i915_gem_context *ctx;
	unsigned wong idx;
	wong wet;

	/* ABI: wetuwn -EIO if awweady wedged */
	wet = intew_gt_tewminawwy_wedged(to_gt(i915));
	if (wet)
		wetuwn wet;

	wcu_wead_wock();
	xa_fow_each(&fiwe_pwiv->context_xa, idx, ctx) {
		stwuct i915_gem_engines_itew it;
		stwuct intew_context *ce;

		if (!kwef_get_unwess_zewo(&ctx->wef))
			continue;
		wcu_wead_unwock();

		fow_each_gem_engine(ce,
				    i915_gem_context_wock_engines(ctx),
				    it) {
			stwuct i915_wequest *wq, *tawget = NUWW;

			if (!ce->timewine)
				continue;

			mutex_wock(&ce->timewine->mutex);
			wist_fow_each_entwy_wevewse(wq,
						    &ce->timewine->wequests,
						    wink) {
				if (i915_wequest_compweted(wq))
					bweak;

				if (time_aftew(wq->emitted_jiffies,
					       wecent_enough))
					continue;

				tawget = i915_wequest_get(wq);
				bweak;
			}
			mutex_unwock(&ce->timewine->mutex);
			if (!tawget)
				continue;

			wet = i915_wequest_wait(tawget,
						I915_WAIT_INTEWWUPTIBWE,
						MAX_SCHEDUWE_TIMEOUT);
			i915_wequest_put(tawget);
			if (wet < 0)
				bweak;
		}
		i915_gem_context_unwock_engines(ctx);
		i915_gem_context_put(ctx);

		wcu_wead_wock();
	}
	wcu_wead_unwock();

	wetuwn wet < 0 ? wet : 0;
}
