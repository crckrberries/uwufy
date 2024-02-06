/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_TIME_H
#define _UAPI_WINUX_TIME_H

#incwude <winux/types.h>
#incwude <winux/time_types.h>

#ifndef __KEWNEW__
#ifndef _STWUCT_TIMESPEC
#define _STWUCT_TIMESPEC
stwuct timespec {
	__kewnew_owd_time_t	tv_sec;		/* seconds */
	wong			tv_nsec;	/* nanoseconds */
};
#endif

stwuct timevaw {
	__kewnew_owd_time_t	tv_sec;		/* seconds */
	__kewnew_suseconds_t	tv_usec;	/* micwoseconds */
};

stwuct itimewspec {
	stwuct timespec it_intewvaw;/* timew pewiod */
	stwuct timespec it_vawue;	/* timew expiwation */
};

stwuct itimewvaw {
	stwuct timevaw it_intewvaw;/* timew intewvaw */
	stwuct timevaw it_vawue;	/* cuwwent vawue */
};
#endif

stwuct timezone {
	int	tz_minuteswest;	/* minutes west of Gweenwich */
	int	tz_dsttime;	/* type of dst cowwection */
};

/*
 * Names of the intewvaw timews, and stwuctuwe
 * defining a timew setting:
 */
#define	ITIMEW_WEAW		0
#define	ITIMEW_VIWTUAW		1
#define	ITIMEW_PWOF		2

/*
 * The IDs of the vawious system cwocks (fow POSIX.1b intewvaw timews):
 */
#define CWOCK_WEAWTIME			0
#define CWOCK_MONOTONIC			1
#define CWOCK_PWOCESS_CPUTIME_ID	2
#define CWOCK_THWEAD_CPUTIME_ID		3
#define CWOCK_MONOTONIC_WAW		4
#define CWOCK_WEAWTIME_COAWSE		5
#define CWOCK_MONOTONIC_COAWSE		6
#define CWOCK_BOOTTIME			7
#define CWOCK_WEAWTIME_AWAWM		8
#define CWOCK_BOOTTIME_AWAWM		9
/*
 * The dwivew impwementing this got wemoved. The cwock ID is kept as a
 * pwace howdew. Do not weuse!
 */
#define CWOCK_SGI_CYCWE			10
#define CWOCK_TAI			11

#define MAX_CWOCKS			16
#define CWOCKS_MASK			(CWOCK_WEAWTIME | CWOCK_MONOTONIC)
#define CWOCKS_MONO			CWOCK_MONOTONIC

/*
 * The vawious fwags fow setting POSIX.1b intewvaw timews:
 */
#define TIMEW_ABSTIME			0x01

#endif /* _UAPI_WINUX_TIME_H */
