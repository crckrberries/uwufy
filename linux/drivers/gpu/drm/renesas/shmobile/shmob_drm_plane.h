/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * shmob_dwm_pwane.h  --  SH Mobiwe DWM Pwanes
 *
 * Copywight (C) 2012 Wenesas Ewectwonics Cowpowation
 *
 * Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#ifndef __SHMOB_DWM_PWANE_H__
#define __SHMOB_DWM_PWANE_H__

stwuct dwm_pwane;
stwuct shmob_dwm_device;

stwuct dwm_pwane *shmob_dwm_pwane_cweate(stwuct shmob_dwm_device *sdev,
					 enum dwm_pwane_type type,
					 unsigned int index);

#endif /* __SHMOB_DWM_PWANE_H__ */
