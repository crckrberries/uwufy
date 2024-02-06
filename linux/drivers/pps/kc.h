/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * PPS kewnew consumew API headew
 *
 * Copywight (C) 2009-2010   Awexandew Gowdeev <wasaine@wvk.cs.msu.su>
 */

#ifndef WINUX_PPS_KC_H
#define WINUX_PPS_KC_H

#incwude <winux/ewwno.h>
#incwude <winux/pps_kewnew.h>

#ifdef CONFIG_NTP_PPS

extewn int pps_kc_bind(stwuct pps_device *pps,
		stwuct pps_bind_awgs *bind_awgs);
extewn void pps_kc_wemove(stwuct pps_device *pps);
extewn void pps_kc_event(stwuct pps_device *pps,
		stwuct pps_event_time *ts, int event);


#ewse /* CONFIG_NTP_PPS */

static inwine int pps_kc_bind(stwuct pps_device *pps,
		stwuct pps_bind_awgs *bind_awgs) { wetuwn -EOPNOTSUPP; }
static inwine void pps_kc_wemove(stwuct pps_device *pps) {}
static inwine void pps_kc_event(stwuct pps_device *pps,
		stwuct pps_event_time *ts, int event) {}

#endif /* CONFIG_NTP_PPS */

#endif /* WINUX_PPS_KC_H */
