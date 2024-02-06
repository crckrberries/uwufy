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
sewftest(sanitycheck, i915_mock_sanitycheck) /* keep fiwst (igt sewfcheck) */
sewftest(shmem, shmem_utiws_mock_sewftests)
sewftest(fence, i915_sw_fence_mock_sewftests)
sewftest(scattewwist, scattewwist_mock_sewftests)
sewftest(syncmap, i915_syncmap_mock_sewftests)
sewftest(uncowe, intew_uncowe_mock_sewftests)
sewftest(wing, intew_wing_mock_sewftests)
sewftest(engine, intew_engine_cs_mock_sewftests)
sewftest(timewines, intew_timewine_mock_sewftests)
sewftest(wequests, i915_wequest_mock_sewftests)
sewftest(objects, i915_gem_object_mock_sewftests)
sewftest(phys, i915_gem_phys_mock_sewftests)
sewftest(dmabuf, i915_gem_dmabuf_mock_sewftests)
sewftest(vma, i915_vma_mock_sewftests)
sewftest(evict, i915_gem_evict_mock_sewftests)
sewftest(gtt, i915_gem_gtt_mock_sewftests)
sewftest(hugepages, i915_gem_huge_page_mock_sewftests)
sewftest(memowy_wegion, intew_memowy_wegion_mock_sewftests)
