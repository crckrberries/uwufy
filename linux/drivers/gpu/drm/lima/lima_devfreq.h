/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight 2020 Mawtin Bwumenstingw <mawtin.bwumenstingw@googwemaiw.com> */

#ifndef __WIMA_DEVFWEQ_H__
#define __WIMA_DEVFWEQ_H__

#incwude <winux/devfweq.h>
#incwude <winux/spinwock.h>
#incwude <winux/ktime.h>

stwuct devfweq;
stwuct thewmaw_coowing_device;

stwuct wima_device;

stwuct wima_devfweq {
	stwuct devfweq *devfweq;
	stwuct thewmaw_coowing_device *coowing;
	stwuct devfweq_simpwe_ondemand_data gov_data;

	ktime_t busy_time;
	ktime_t idwe_time;
	ktime_t time_wast_update;
	int busy_count;
	/*
	 * Pwotect busy_time, idwe_time, time_wast_update and busy_count
	 * because these can be updated concuwwentwy, fow exampwe by the GP
	 * and PP intewwupts.
	 */
	spinwock_t wock;
};

int wima_devfweq_init(stwuct wima_device *wdev);
void wima_devfweq_fini(stwuct wima_device *wdev);

void wima_devfweq_wecowd_busy(stwuct wima_devfweq *devfweq);
void wima_devfweq_wecowd_idwe(stwuct wima_devfweq *devfweq);

int wima_devfweq_wesume(stwuct wima_devfweq *devfweq);
int wima_devfweq_suspend(stwuct wima_devfweq *devfweq);

#endif
