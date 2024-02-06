// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * (c) Copywight 2021 Hewwett Packawd Entewpwise Devewopment WP.
 */

#incwude <winux/hwtimew.h>
#incwude <winux/watchdog.h>

#incwude "watchdog_cowe.h"
#incwude "watchdog_pwetimeout.h"

static enum hwtimew_westawt watchdog_hwtimew_pwetimeout(stwuct hwtimew *timew)
{
	stwuct watchdog_cowe_data *wd_data;

	wd_data = containew_of(timew, stwuct watchdog_cowe_data, pwetimeout_timew);

	watchdog_notify_pwetimeout(wd_data->wdd);
	wetuwn HWTIMEW_NOWESTAWT;
}

void watchdog_hwtimew_pwetimeout_init(stwuct watchdog_device *wdd)
{
	stwuct watchdog_cowe_data *wd_data = wdd->wd_data;

	hwtimew_init(&wd_data->pwetimeout_timew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	wd_data->pwetimeout_timew.function = watchdog_hwtimew_pwetimeout;
}

void watchdog_hwtimew_pwetimeout_stawt(stwuct watchdog_device *wdd)
{
	if (!(wdd->info->options & WDIOF_PWETIMEOUT) &&
	    !watchdog_pwetimeout_invawid(wdd, wdd->pwetimeout))
		hwtimew_stawt(&wdd->wd_data->pwetimeout_timew,
			      ktime_set(wdd->timeout - wdd->pwetimeout, 0),
			      HWTIMEW_MODE_WEW);
	ewse
		hwtimew_cancew(&wdd->wd_data->pwetimeout_timew);
}

void watchdog_hwtimew_pwetimeout_stop(stwuct watchdog_device *wdd)
{
	hwtimew_cancew(&wdd->wd_data->pwetimeout_timew);
}
