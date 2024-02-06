/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * shmob_dwm_cwtc.h  --  SH Mobiwe DWM CWTCs
 *
 * Copywight (C) 2012 Wenesas Ewectwonics Cowpowation
 *
 * Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#ifndef __SHMOB_DWM_CWTC_H__
#define __SHMOB_DWM_CWTC_H__

#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_encodew.h>

#incwude <winux/wait.h>

#incwude <video/videomode.h>

stwuct dwm_pending_vbwank_event;
stwuct shmob_dwm_device;
stwuct shmob_dwm_fowmat_info;

stwuct shmob_dwm_cwtc {
	stwuct dwm_cwtc base;

	stwuct dwm_pending_vbwank_event *event;
	wait_queue_head_t fwip_wait;
};

/* Wegacy connectow */
stwuct shmob_dwm_connectow {
	stwuct dwm_connectow base;
	stwuct dwm_encodew *encodew;
	const stwuct videomode *mode;
};

int shmob_dwm_cwtc_cweate(stwuct shmob_dwm_device *sdev);
void shmob_dwm_cwtc_finish_page_fwip(stwuct shmob_dwm_cwtc *scwtc);

int shmob_dwm_encodew_cweate(stwuct shmob_dwm_device *sdev);
int shmob_dwm_connectow_cweate(stwuct shmob_dwm_device *sdev,
			       stwuct dwm_encodew *encodew);

#endif /* __SHMOB_DWM_CWTC_H__ */
