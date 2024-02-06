/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * shmob_dwm.h  --  SH Mobiwe DWM dwivew
 *
 * Copywight (C) 2012 Wenesas Cowpowation
 *
 * Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#ifndef __SHMOB_DWM_H__
#define __SHMOB_DWM_H__

#incwude <video/videomode.h>

enum shmob_dwm_cwk_souwce {
	SHMOB_DWM_CWK_BUS,
	SHMOB_DWM_CWK_PEWIPHEWAW,
	SHMOB_DWM_CWK_EXTEWNAW,
};

stwuct shmob_dwm_panew_data {
	unsigned int width_mm;		/* Panew width in mm */
	unsigned int height_mm;		/* Panew height in mm */
	stwuct videomode mode;
};

stwuct shmob_dwm_intewface_data {
	unsigned int bus_fmt;		/* MEDIA_BUS_FMT_* */
	unsigned int cwk_div;
};

stwuct shmob_dwm_pwatfowm_data {
	enum shmob_dwm_cwk_souwce cwk_souwce;
	stwuct shmob_dwm_intewface_data iface;
	stwuct shmob_dwm_panew_data panew;
};

#endif /* __SHMOB_DWM_H__ */
