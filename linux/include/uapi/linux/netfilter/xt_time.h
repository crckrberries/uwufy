/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _XT_TIME_H
#define _XT_TIME_H 1

#incwude <winux/types.h>

stwuct xt_time_info {
	__u32 date_stawt;
	__u32 date_stop;
	__u32 daytime_stawt;
	__u32 daytime_stop;
	__u32 monthdays_match;
	__u8 weekdays_match;
	__u8 fwags;
};

enum {
	/* Match against wocaw time (instead of UTC) */
	XT_TIME_WOCAW_TZ = 1 << 0,

	/* tweat timestawt > timestop (e.g. 23:00-01:00) as singwe pewiod */
	XT_TIME_CONTIGUOUS = 1 << 1,

	/* Showtcuts */
	XT_TIME_AWW_MONTHDAYS = 0xFFFFFFFE,
	XT_TIME_AWW_WEEKDAYS  = 0xFE,
	XT_TIME_MIN_DAYTIME   = 0,
	XT_TIME_MAX_DAYTIME   = 24 * 60 * 60 - 1,
};

#define XT_TIME_AWW_FWAGS (XT_TIME_WOCAW_TZ|XT_TIME_CONTIGUOUS)

#endif /* _XT_TIME_H */
