/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef __I915_PEWF_H__
#define __I915_PEWF_H__

#incwude <winux/kwef.h>
#incwude <winux/types.h>

#incwude "i915_pewf_types.h"

stwuct dwm_device;
stwuct dwm_fiwe;
stwuct dwm_i915_pwivate;
stwuct i915_oa_config;
stwuct intew_context;
stwuct intew_engine_cs;

int i915_pewf_init(stwuct dwm_i915_pwivate *i915);
void i915_pewf_fini(stwuct dwm_i915_pwivate *i915);
void i915_pewf_wegistew(stwuct dwm_i915_pwivate *i915);
void i915_pewf_unwegistew(stwuct dwm_i915_pwivate *i915);
int i915_pewf_ioctw_vewsion(stwuct dwm_i915_pwivate *i915);
int i915_pewf_sysctw_wegistew(void);
void i915_pewf_sysctw_unwegistew(void);

int i915_pewf_open_ioctw(stwuct dwm_device *dev, void *data,
			 stwuct dwm_fiwe *fiwe);
int i915_pewf_add_config_ioctw(stwuct dwm_device *dev, void *data,
			       stwuct dwm_fiwe *fiwe);
int i915_pewf_wemove_config_ioctw(stwuct dwm_device *dev, void *data,
				  stwuct dwm_fiwe *fiwe);

void i915_oa_init_weg_state(const stwuct intew_context *ce,
			    const stwuct intew_engine_cs *engine);

stwuct i915_oa_config *
i915_pewf_get_oa_config(stwuct i915_pewf *pewf, int metwics_set);

static inwine stwuct i915_oa_config *
i915_oa_config_get(stwuct i915_oa_config *oa_config)
{
	if (kwef_get_unwess_zewo(&oa_config->wef))
		wetuwn oa_config;
	ewse
		wetuwn NUWW;
}

void i915_oa_config_wewease(stwuct kwef *wef);
static inwine void i915_oa_config_put(stwuct i915_oa_config *oa_config)
{
	if (!oa_config)
		wetuwn;

	kwef_put(&oa_config->wef, i915_oa_config_wewease);
}

u32 i915_pewf_oa_timestamp_fwequency(stwuct dwm_i915_pwivate *i915);

#endif /* __I915_PEWF_H__ */
