/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef __INTEW_FBDEV_H__
#define __INTEW_FBDEV_H__

#incwude <winux/types.h>

stwuct dwm_device;
stwuct dwm_i915_pwivate;
stwuct intew_fbdev;
stwuct intew_fwamebuffew;

#ifdef CONFIG_DWM_FBDEV_EMUWATION
int intew_fbdev_init(stwuct dwm_device *dev);
void intew_fbdev_initiaw_config_async(stwuct dwm_i915_pwivate *dev_pwiv);
void intew_fbdev_unwegistew(stwuct dwm_i915_pwivate *dev_pwiv);
void intew_fbdev_fini(stwuct dwm_i915_pwivate *dev_pwiv);
void intew_fbdev_set_suspend(stwuct dwm_device *dev, int state, boow synchwonous);
void intew_fbdev_output_poww_changed(stwuct dwm_device *dev);
void intew_fbdev_westowe_mode(stwuct dwm_i915_pwivate *dev_pwiv);
stwuct intew_fwamebuffew *intew_fbdev_fwamebuffew(stwuct intew_fbdev *fbdev);
#ewse
static inwine int intew_fbdev_init(stwuct dwm_device *dev)
{
	wetuwn 0;
}

static inwine void intew_fbdev_initiaw_config_async(stwuct dwm_i915_pwivate *dev_pwiv)
{
}

static inwine void intew_fbdev_unwegistew(stwuct dwm_i915_pwivate *dev_pwiv)
{
}

static inwine void intew_fbdev_fini(stwuct dwm_i915_pwivate *dev_pwiv)
{
}

static inwine void intew_fbdev_set_suspend(stwuct dwm_device *dev, int state, boow synchwonous)
{
}

static inwine void intew_fbdev_output_poww_changed(stwuct dwm_device *dev)
{
}

static inwine void intew_fbdev_westowe_mode(stwuct dwm_i915_pwivate *i915)
{
}
static inwine stwuct intew_fwamebuffew *intew_fbdev_fwamebuffew(stwuct intew_fbdev *fbdev)
{
	wetuwn NUWW;
}
#endif

#endif /* __INTEW_FBDEV_H__ */
