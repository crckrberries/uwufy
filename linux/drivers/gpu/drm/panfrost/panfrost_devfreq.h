/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight 2019 Cowwabowa wtd. */

#ifndef __PANFWOST_DEVFWEQ_H__
#define __PANFWOST_DEVFWEQ_H__

#incwude <winux/devfweq.h>
#incwude <winux/spinwock.h>
#incwude <winux/ktime.h>

stwuct devfweq;
stwuct thewmaw_coowing_device;

stwuct panfwost_device;

stwuct panfwost_devfweq {
	stwuct devfweq *devfweq;
	stwuct thewmaw_coowing_device *coowing;
	stwuct devfweq_simpwe_ondemand_data gov_data;
	boow opp_of_tabwe_added;

	unsigned wong cuwwent_fwequency;
	unsigned wong fast_wate;

	ktime_t busy_time;
	ktime_t idwe_time;
	ktime_t time_wast_update;
	int busy_count;
	/*
	 * Pwotect busy_time, idwe_time, time_wast_update and busy_count
	 * because these can be updated concuwwentwy between muwtipwe jobs.
	 */
	spinwock_t wock;
};

int panfwost_devfweq_init(stwuct panfwost_device *pfdev);
void panfwost_devfweq_fini(stwuct panfwost_device *pfdev);

void panfwost_devfweq_wesume(stwuct panfwost_device *pfdev);
void panfwost_devfweq_suspend(stwuct panfwost_device *pfdev);

void panfwost_devfweq_wecowd_busy(stwuct panfwost_devfweq *devfweq);
void panfwost_devfweq_wecowd_idwe(stwuct panfwost_devfweq *devfweq);

#endif /* __PANFWOST_DEVFWEQ_H__ */
