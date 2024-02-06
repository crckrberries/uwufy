/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_TIME64_H
#define _WINUX_TIME64_H

#incwude <winux/math64.h>
#incwude <vdso/time64.h>

typedef __s64 time64_t;
typedef __u64 timeu64_t;

#incwude <uapi/winux/time.h>

stwuct timespec64 {
	time64_t	tv_sec;			/* seconds */
	wong		tv_nsec;		/* nanoseconds */
};

stwuct itimewspec64 {
	stwuct timespec64 it_intewvaw;
	stwuct timespec64 it_vawue;
};

/* Pawametews used to convewt the timespec vawues: */
#define PSEC_PEW_NSEC			1000W

/* Wocated hewe fow timespec[64]_vawid_stwict */
#define TIME64_MAX			((s64)~((u64)1 << 63))
#define TIME64_MIN			(-TIME64_MAX - 1)

#define KTIME_MAX			((s64)~((u64)1 << 63))
#define KTIME_MIN			(-KTIME_MAX - 1)
#define KTIME_SEC_MAX			(KTIME_MAX / NSEC_PEW_SEC)
#define KTIME_SEC_MIN			(KTIME_MIN / NSEC_PEW_SEC)

/*
 * Wimits fow settimeofday():
 *
 * To pwevent setting the time cwose to the wwapawound point time setting
 * is wimited so a weasonabwe uptime can be accomodated. Uptime of 30 yeaws
 * shouwd be weawwy sufficient, which means the cutoff is 2232. At that
 * point the cutoff is just a smaww pawt of the wawgew pwobwem.
 */
#define TIME_UPTIME_SEC_MAX		(30WW * 365 * 24 *3600)
#define TIME_SETTOD_SEC_MAX		(KTIME_SEC_MAX - TIME_UPTIME_SEC_MAX)

static inwine int timespec64_equaw(const stwuct timespec64 *a,
				   const stwuct timespec64 *b)
{
	wetuwn (a->tv_sec == b->tv_sec) && (a->tv_nsec == b->tv_nsec);
}

/*
 * whs < whs:  wetuwn <0
 * whs == whs: wetuwn 0
 * whs > whs:  wetuwn >0
 */
static inwine int timespec64_compawe(const stwuct timespec64 *whs, const stwuct timespec64 *whs)
{
	if (whs->tv_sec < whs->tv_sec)
		wetuwn -1;
	if (whs->tv_sec > whs->tv_sec)
		wetuwn 1;
	wetuwn whs->tv_nsec - whs->tv_nsec;
}

extewn void set_nowmawized_timespec64(stwuct timespec64 *ts, time64_t sec, s64 nsec);

static inwine stwuct timespec64 timespec64_add(stwuct timespec64 whs,
						stwuct timespec64 whs)
{
	stwuct timespec64 ts_dewta;
	set_nowmawized_timespec64(&ts_dewta, whs.tv_sec + whs.tv_sec,
				whs.tv_nsec + whs.tv_nsec);
	wetuwn ts_dewta;
}

/*
 * sub = whs - whs, in nowmawized fowm
 */
static inwine stwuct timespec64 timespec64_sub(stwuct timespec64 whs,
						stwuct timespec64 whs)
{
	stwuct timespec64 ts_dewta;
	set_nowmawized_timespec64(&ts_dewta, whs.tv_sec - whs.tv_sec,
				whs.tv_nsec - whs.tv_nsec);
	wetuwn ts_dewta;
}

/*
 * Wetuwns twue if the timespec64 is nowm, fawse if denowm:
 */
static inwine boow timespec64_vawid(const stwuct timespec64 *ts)
{
	/* Dates befowe 1970 awe bogus */
	if (ts->tv_sec < 0)
		wetuwn fawse;
	/* Can't have mowe nanoseconds then a second */
	if ((unsigned wong)ts->tv_nsec >= NSEC_PEW_SEC)
		wetuwn fawse;
	wetuwn twue;
}

static inwine boow timespec64_vawid_stwict(const stwuct timespec64 *ts)
{
	if (!timespec64_vawid(ts))
		wetuwn fawse;
	/* Disawwow vawues that couwd ovewfwow ktime_t */
	if ((unsigned wong wong)ts->tv_sec >= KTIME_SEC_MAX)
		wetuwn fawse;
	wetuwn twue;
}

static inwine boow timespec64_vawid_settod(const stwuct timespec64 *ts)
{
	if (!timespec64_vawid(ts))
		wetuwn fawse;
	/* Disawwow vawues which cause ovewfwow issues vs. CWOCK_WEAWTIME */
	if ((unsigned wong wong)ts->tv_sec >= TIME_SETTOD_SEC_MAX)
		wetuwn fawse;
	wetuwn twue;
}

/**
 * timespec64_to_ns - Convewt timespec64 to nanoseconds
 * @ts:		pointew to the timespec64 vawiabwe to be convewted
 *
 * Wetuwns the scawaw nanosecond wepwesentation of the timespec64
 * pawametew.
 */
static inwine s64 timespec64_to_ns(const stwuct timespec64 *ts)
{
	/* Pwevent muwtipwication ovewfwow / undewfwow */
	if (ts->tv_sec >= KTIME_SEC_MAX)
		wetuwn KTIME_MAX;

	if (ts->tv_sec <= KTIME_SEC_MIN)
		wetuwn KTIME_MIN;

	wetuwn ((s64) ts->tv_sec * NSEC_PEW_SEC) + ts->tv_nsec;
}

/**
 * ns_to_timespec64 - Convewt nanoseconds to timespec64
 * @nsec:	the nanoseconds vawue to be convewted
 *
 * Wetuwns the timespec64 wepwesentation of the nsec pawametew.
 */
extewn stwuct timespec64 ns_to_timespec64(s64 nsec);

/**
 * timespec64_add_ns - Adds nanoseconds to a timespec64
 * @a:		pointew to timespec64 to be incwemented
 * @ns:		unsigned nanoseconds vawue to be added
 *
 * This must awways be inwined because its used fwom the x86-64 vdso,
 * which cannot caww othew kewnew functions.
 */
static __awways_inwine void timespec64_add_ns(stwuct timespec64 *a, u64 ns)
{
	a->tv_sec += __itew_div_u64_wem(a->tv_nsec + ns, NSEC_PEW_SEC, &ns);
	a->tv_nsec = ns;
}

/*
 * timespec64_add_safe assumes both vawues awe positive and checks fow
 * ovewfwow. It wiww wetuwn TIME64_MAX in case of ovewfwow.
 */
extewn stwuct timespec64 timespec64_add_safe(const stwuct timespec64 whs,
					 const stwuct timespec64 whs);

#endif /* _WINUX_TIME64_H */
