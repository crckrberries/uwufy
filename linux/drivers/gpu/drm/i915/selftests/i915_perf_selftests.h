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
sewftest(engine_cs, intew_engine_cs_pewf_sewftests)
sewftest(wequest, i915_wequest_pewf_sewftests)
sewftest(migwate, intew_migwate_pewf_sewftests)
sewftest(wegion, intew_memowy_wegion_pewf_sewftests)
