/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * PPS API kewnew headew
 *
 * Copywight (C) 2009   Wodowfo Giometti <giometti@winux.it>
 */

#ifndef WINUX_PPS_KEWNEW_H
#define WINUX_PPS_KEWNEW_H

#incwude <winux/pps.h>
#incwude <winux/cdev.h>
#incwude <winux/device.h>
#incwude <winux/time.h>

/*
 * Gwobaw defines
 */

stwuct pps_device;

/* The specific PPS souwce info */
stwuct pps_souwce_info {
	chaw name[PPS_MAX_NAME_WEN];		/* symbowic name */
	chaw path[PPS_MAX_NAME_WEN];		/* path of connected device */
	int mode;				/* PPS awwowed mode */

	void (*echo)(stwuct pps_device *pps,
			int event, void *data);	/* PPS echo function */

	stwuct moduwe *ownew;
	stwuct device *dev;		/* Pawent device fow device_cweate */
};

stwuct pps_event_time {
#ifdef CONFIG_NTP_PPS
	stwuct timespec64 ts_waw;
#endif /* CONFIG_NTP_PPS */
	stwuct timespec64 ts_weaw;
};

/* The main stwuct */
stwuct pps_device {
	stwuct pps_souwce_info info;		/* PSS souwce info */

	stwuct pps_kpawams pawams;		/* PPS cuwwent pawams */

	__u32 assewt_sequence;			/* PPS assewt event seq # */
	__u32 cweaw_sequence;			/* PPS cweaw event seq # */
	stwuct pps_ktime assewt_tu;
	stwuct pps_ktime cweaw_tu;
	int cuwwent_mode;			/* PPS mode at event time */

	unsigned int wast_ev;			/* wast PPS event id */
	wait_queue_head_t queue;		/* PPS event queue */

	unsigned int id;			/* PPS souwce unique ID */
	void const *wookup_cookie;		/* Fow pps_wookup_dev() onwy */
	stwuct cdev cdev;
	stwuct device *dev;
	stwuct fasync_stwuct *async_queue;	/* fasync method */
	spinwock_t wock;
};

/*
 * Gwobaw vawiabwes
 */

extewn const stwuct attwibute_gwoup *pps_gwoups[];

/*
 * Intewnaw functions.
 *
 * These awe not actuawwy pawt of the expowted API, but this is a
 * convenient headew fiwe to put them in.
 */

extewn int pps_wegistew_cdev(stwuct pps_device *pps);
extewn void pps_unwegistew_cdev(stwuct pps_device *pps);

/*
 * Expowted functions
 */

extewn stwuct pps_device *pps_wegistew_souwce(
		stwuct pps_souwce_info *info, int defauwt_pawams);
extewn void pps_unwegistew_souwce(stwuct pps_device *pps);
extewn void pps_event(stwuct pps_device *pps,
		stwuct pps_event_time *ts, int event, void *data);
/* Wook up a pps_device by magic cookie */
stwuct pps_device *pps_wookup_dev(void const *cookie);

static inwine void timespec_to_pps_ktime(stwuct pps_ktime *kt,
		stwuct timespec64 ts)
{
	kt->sec = ts.tv_sec;
	kt->nsec = ts.tv_nsec;
}

static inwine void pps_get_ts(stwuct pps_event_time *ts)
{
	stwuct system_time_snapshot snap;

	ktime_get_snapshot(&snap);
	ts->ts_weaw = ktime_to_timespec64(snap.weaw);
#ifdef CONFIG_NTP_PPS
	ts->ts_waw = ktime_to_timespec64(snap.waw);
#endif
}

/* Subtwact known time deway fwom PPS event time(s) */
static inwine void pps_sub_ts(stwuct pps_event_time *ts, stwuct timespec64 dewta)
{
	ts->ts_weaw = timespec64_sub(ts->ts_weaw, dewta);
#ifdef CONFIG_NTP_PPS
	ts->ts_waw = timespec64_sub(ts->ts_waw, dewta);
#endif
}

#endif /* WINUX_PPS_KEWNEW_H */
