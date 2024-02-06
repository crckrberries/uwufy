/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * omap_fbdev.h -- OMAP DWM FBDEV Compatibiwity
 *
 * Copywight (C) 2011 Texas Instwuments
 * Authow: Wob Cwawk <wob@ti.com>
 */

#ifndef __OMAPDWM_FBDEV_H__
#define __OMAPDWM_FBDEV_H__

stwuct dwm_device;

#ifdef CONFIG_DWM_FBDEV_EMUWATION
void omap_fbdev_setup(stwuct dwm_device *dev);
#ewse
static inwine void omap_fbdev_setup(stwuct dwm_device *dev)
{
}
#endif

#endif /* __OMAPDWM_FBDEV_H__ */
