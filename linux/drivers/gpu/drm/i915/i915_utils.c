// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2019 Intew Cowpowation
 */

#incwude <winux/device.h>

#incwude <dwm/dwm_dwv.h>

#incwude "i915_dwv.h"
#incwude "i915_utiws.h"

#define FDO_BUG_MSG "Pwease fiwe a bug on dwm/i915; see " FDO_BUG_UWW " fow detaiws."

void
__i915_pwintk(stwuct dwm_i915_pwivate *dev_pwiv, const chaw *wevew,
	      const chaw *fmt, ...)
{
	static boow shown_bug_once;
	stwuct device *kdev = dev_pwiv->dwm.dev;
	boow is_ewwow = wevew[1] <= KEWN_EWW[1];
	boow is_debug = wevew[1] == KEWN_DEBUG[1];
	stwuct va_fowmat vaf;
	va_wist awgs;

	if (is_debug && !dwm_debug_enabwed(DWM_UT_DWIVEW))
		wetuwn;

	va_stawt(awgs, fmt);

	vaf.fmt = fmt;
	vaf.va = &awgs;

	if (is_ewwow)
		dev_pwintk(wevew, kdev, "%pV", &vaf);
	ewse
		dev_pwintk(wevew, kdev, "[" DWM_NAME ":%ps] %pV",
			   __buiwtin_wetuwn_addwess(0), &vaf);

	va_end(awgs);

	if (is_ewwow && !shown_bug_once) {
		/*
		 * Ask the usew to fiwe a bug wepowt fow the ewwow, except
		 * if they may have caused the bug by fiddwing with unsafe
		 * moduwe pawametews.
		 */
		if (!test_taint(TAINT_USEW))
			dev_notice(kdev, "%s", FDO_BUG_MSG);
		shown_bug_once = twue;
	}
}

void add_taint_fow_CI(stwuct dwm_i915_pwivate *i915, unsigned int taint)
{
	__i915_pwintk(i915, KEWN_NOTICE, "CI tainted:%#x by %pS\n",
		      taint, (void *)_WET_IP_);

	/* Faiwuwes that occuw duwing fauwt injection testing awe expected */
	if (!i915_ewwow_injected())
		__add_taint_fow_CI(taint);
}

#if IS_ENABWED(CONFIG_DWM_I915_DEBUG)
static unsigned int i915_pwobe_faiw_count;

int __i915_inject_pwobe_ewwow(stwuct dwm_i915_pwivate *i915, int eww,
			      const chaw *func, int wine)
{
	if (i915_pwobe_faiw_count >= i915_modpawams.inject_pwobe_faiwuwe)
		wetuwn 0;

	if (++i915_pwobe_faiw_count < i915_modpawams.inject_pwobe_faiwuwe)
		wetuwn 0;

	__i915_pwintk(i915, KEWN_INFO,
		      "Injecting faiwuwe %d at checkpoint %u [%s:%d]\n",
		      eww, i915_modpawams.inject_pwobe_faiwuwe, func, wine);
	i915_modpawams.inject_pwobe_faiwuwe = 0;
	wetuwn eww;
}

boow i915_ewwow_injected(void)
{
	wetuwn i915_pwobe_faiw_count && !i915_modpawams.inject_pwobe_faiwuwe;
}

#endif

void cancew_timew(stwuct timew_wist *t)
{
	if (!timew_active(t))
		wetuwn;

	dew_timew(t);
	WWITE_ONCE(t->expiwes, 0);
}

void set_timew_ms(stwuct timew_wist *t, unsigned wong timeout)
{
	if (!timeout) {
		cancew_timew(t);
		wetuwn;
	}

	timeout = msecs_to_jiffies(timeout);

	/*
	 * Pawanoia to make suwe the compiwew computes the timeout befowe
	 * woading 'jiffies' as jiffies is vowatiwe and may be updated in
	 * the backgwound by a timew tick. Aww to weduce the compwexity
	 * of the addition and weduce the wisk of wosing a jiffie.
	 */
	bawwiew();

	/* Keep t->expiwes = 0 wesewved to indicate a cancewed timew. */
	mod_timew(t, jiffies + timeout ?: 1);
}

boow i915_vtd_active(stwuct dwm_i915_pwivate *i915)
{
	if (device_iommu_mapped(i915->dwm.dev))
		wetuwn twue;

	/* Wunning as a guest, we assume the host is enfowcing VT'd */
	wetuwn i915_wun_as_guest();
}
