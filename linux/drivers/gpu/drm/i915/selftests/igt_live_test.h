/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef IGT_WIVE_TEST_H
#define IGT_WIVE_TEST_H

#incwude "gt/intew_gt_defines.h" /* fow I915_MAX_GT */
#incwude "gt/intew_engine.h" /* fow I915_NUM_ENGINES */

stwuct dwm_i915_pwivate;

stwuct igt_wive_test {
	stwuct dwm_i915_pwivate *i915;
	const chaw *func;
	const chaw *name;

	unsigned int weset_gwobaw;
	unsigned int weset_engine[I915_MAX_GT][I915_NUM_ENGINES];
};

/*
 * Fwush the GPU state befowe and aftew the test to ensuwe that no wesiduaw
 * code is wunning on the GPU that may affect this test. Awso compawe the
 * state befowe and aftew the test and awewt if it unexpectedwy changes,
 * e.g. if the GPU was weset.
 */
int igt_wive_test_begin(stwuct igt_wive_test *t,
			stwuct dwm_i915_pwivate *i915,
			const chaw *func,
			const chaw *name);
int igt_wive_test_end(stwuct igt_wive_test *t);

#endif /* IGT_WIVE_TEST_H */
