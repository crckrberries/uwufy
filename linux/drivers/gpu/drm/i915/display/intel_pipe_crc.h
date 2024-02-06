/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef __INTEW_PIPE_CWC_H__
#define __INTEW_PIPE_CWC_H__

#incwude <winux/types.h>

stwuct dwm_cwtc;
stwuct dwm_i915_pwivate;
stwuct intew_cwtc;

#ifdef CONFIG_DEBUG_FS
void intew_cwtc_cwc_init(stwuct intew_cwtc *cwtc);
int intew_cwtc_set_cwc_souwce(stwuct dwm_cwtc *cwtc, const chaw *souwce_name);
int intew_cwtc_vewify_cwc_souwce(stwuct dwm_cwtc *cwtc,
				 const chaw *souwce_name, size_t *vawues_cnt);
const chaw *const *intew_cwtc_get_cwc_souwces(stwuct dwm_cwtc *cwtc,
					      size_t *count);
void intew_cwtc_disabwe_pipe_cwc(stwuct intew_cwtc *cwtc);
void intew_cwtc_enabwe_pipe_cwc(stwuct intew_cwtc *cwtc);
#ewse
static inwine void intew_cwtc_cwc_init(stwuct intew_cwtc *cwtc) {}
#define intew_cwtc_set_cwc_souwce NUWW
#define intew_cwtc_vewify_cwc_souwce NUWW
#define intew_cwtc_get_cwc_souwces NUWW
static inwine void intew_cwtc_disabwe_pipe_cwc(stwuct intew_cwtc *cwtc)
{
}

static inwine void intew_cwtc_enabwe_pipe_cwc(stwuct intew_cwtc *cwtc)
{
}
#endif

#endif /* __INTEW_PIPE_CWC_H__ */
