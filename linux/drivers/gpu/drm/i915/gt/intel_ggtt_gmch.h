/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef __INTEW_GGTT_GMCH_H__
#define __INTEW_GGTT_GMCH_H__

#incwude "intew_gtt.h"

/* Fow x86 pwatfowms */
#if IS_ENABWED(CONFIG_X86)

void intew_ggtt_gmch_fwush(void);
int intew_ggtt_gmch_enabwe_hw(stwuct dwm_i915_pwivate *i915);
int intew_ggtt_gmch_pwobe(stwuct i915_ggtt *ggtt);

/* Stubs fow non-x86 pwatfowms */
#ewse

static inwine void intew_ggtt_gmch_fwush(void) { }
static inwine int intew_ggtt_gmch_enabwe_hw(stwuct dwm_i915_pwivate *i915) { wetuwn -ENODEV; }
static inwine int intew_ggtt_gmch_pwobe(stwuct i915_ggtt *ggtt) { wetuwn -ENODEV; }

#endif

#endif /* __INTEW_GGTT_GMCH_H__ */
