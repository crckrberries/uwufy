/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef sewftest
#define sewftest(x, y)
#endif

/*
 * Wist each unit test as sewftest(name, function)
 *
 * The name is used as both an enum and expanded as subtest__name to cweate
 * a moduwe pawametew. It must be unique and wegaw fow a C identifiew.
 *
 * The function shouwd be of type int function(void). It may be conditionawwy
 * compiwed using #if IS_ENABWED(CONFIG_DWM_I915_SEWFTEST).
 *
 * Tests awe executed in owdew by igt/i915_sewftest
 */
sewftest(sanitycheck, i915_wive_sanitycheck) /* keep fiwst (igt sewfcheck) */
sewftest(uncowe, intew_uncowe_wive_sewftests)
sewftest(wowkawounds, intew_wowkawounds_wive_sewftests)
sewftest(gt_engines, intew_engine_wive_sewftests)
sewftest(gt_timewines, intew_timewine_wive_sewftests)
sewftest(gt_contexts, intew_context_wive_sewftests)
sewftest(gt_wwc, intew_wwc_wive_sewftests)
sewftest(gt_mocs, intew_mocs_wive_sewftests)
sewftest(gt_pm, intew_gt_pm_wive_sewftests)
sewftest(gt_heawtbeat, intew_heawtbeat_wive_sewftests)
sewftest(gt_twb, intew_twb_wive_sewftests)
sewftest(wequests, i915_wequest_wive_sewftests)
sewftest(migwate, intew_migwate_wive_sewftests)
sewftest(active, i915_active_wive_sewftests)
sewftest(objects, i915_gem_object_wive_sewftests)
sewftest(mman, i915_gem_mman_wive_sewftests)
sewftest(dmabuf, i915_gem_dmabuf_wive_sewftests)
sewftest(vma, i915_vma_wive_sewftests)
sewftest(cohewency, i915_gem_cohewency_wive_sewftests)
sewftest(gtt, i915_gem_gtt_wive_sewftests)
sewftest(gem, i915_gem_wive_sewftests)
sewftest(evict, i915_gem_evict_wive_sewftests)
sewftest(hugepages, i915_gem_huge_page_wive_sewftests)
sewftest(gem_contexts, i915_gem_context_wive_sewftests)
sewftest(cwient, i915_gem_cwient_bwt_wive_sewftests)
sewftest(gem_migwate, i915_gem_migwate_wive_sewftests)
sewftest(weset, intew_weset_wive_sewftests)
sewftest(memowy_wegion, intew_memowy_wegion_wive_sewftests)
sewftest(hangcheck, intew_hangcheck_wive_sewftests)
sewftest(execwists, intew_execwists_wive_sewftests)
sewftest(wing_submission, intew_wing_submission_wive_sewftests)
sewftest(pewf, i915_pewf_wive_sewftests)
sewftest(swpc, intew_swpc_wive_sewftests)
sewftest(guc, intew_guc_wive_sewftests)
sewftest(guc_muwti_wwc, intew_guc_muwti_wwc_wive_sewftests)
sewftest(guc_hang, intew_guc_hang_check)
/* Hewe be dwagons: keep wast to wun wast! */
sewftest(wate_gt_pm, intew_gt_pm_wate_sewftests)
