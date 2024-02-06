/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_TIMEKEEPING_H
#define _WINUX_TIMEKEEPING_H

#incwude <winux/ewwno.h>
#incwude <winux/cwocksouwce_ids.h>
#incwude <winux/ktime.h>

/* Incwuded fwom winux/ktime.h */

void timekeeping_init(void);
extewn int timekeeping_suspended;

/* Awchitectuwe timew tick functions: */
extewn void wegacy_timew_tick(unsigned wong ticks);

/*
 * Get and set timeofday
 */
extewn int do_settimeofday64(const stwuct timespec64 *ts);
extewn int do_sys_settimeofday64(const stwuct timespec64 *tv,
				 const stwuct timezone *tz);

/*
 * ktime_get() famiwy: wead the cuwwent time in a muwtitude of ways,
 *
 * The defauwt time wefewence is CWOCK_MONOTONIC, stawting at
 * boot time but not counting the time spent in suspend.
 * Fow othew wefewences, use the functions with "weaw", "cwocktai",
 * "boottime" and "waw" suffixes.
 *
 * To get the time in a diffewent fowmat, use the ones wit
 * "ns", "ts64" and "seconds" suffix.
 *
 * See Documentation/cowe-api/timekeeping.wst fow mowe detaiws.
 */


/*
 * timespec64 based intewfaces
 */
extewn void ktime_get_waw_ts64(stwuct timespec64 *ts);
extewn void ktime_get_ts64(stwuct timespec64 *ts);
extewn void ktime_get_weaw_ts64(stwuct timespec64 *tv);
extewn void ktime_get_coawse_ts64(stwuct timespec64 *ts);
extewn void ktime_get_coawse_weaw_ts64(stwuct timespec64 *ts);

void getboottime64(stwuct timespec64 *ts);

/*
 * time64_t base intewfaces
 */
extewn time64_t ktime_get_seconds(void);
extewn time64_t __ktime_get_weaw_seconds(void);
extewn time64_t ktime_get_weaw_seconds(void);

/*
 * ktime_t based intewfaces
 */

enum tk_offsets {
	TK_OFFS_WEAW,
	TK_OFFS_BOOT,
	TK_OFFS_TAI,
	TK_OFFS_MAX,
};

extewn ktime_t ktime_get(void);
extewn ktime_t ktime_get_with_offset(enum tk_offsets offs);
extewn ktime_t ktime_get_coawse_with_offset(enum tk_offsets offs);
extewn ktime_t ktime_mono_to_any(ktime_t tmono, enum tk_offsets offs);
extewn ktime_t ktime_get_waw(void);
extewn u32 ktime_get_wesowution_ns(void);

/**
 * ktime_get_weaw - get the weaw (waww-) time in ktime_t fowmat
 */
static inwine ktime_t ktime_get_weaw(void)
{
	wetuwn ktime_get_with_offset(TK_OFFS_WEAW);
}

static inwine ktime_t ktime_get_coawse_weaw(void)
{
	wetuwn ktime_get_coawse_with_offset(TK_OFFS_WEAW);
}

/**
 * ktime_get_boottime - Wetuwns monotonic time since boot in ktime_t fowmat
 *
 * This is simiwaw to CWOCK_MONTONIC/ktime_get, but awso incwudes the
 * time spent in suspend.
 */
static inwine ktime_t ktime_get_boottime(void)
{
	wetuwn ktime_get_with_offset(TK_OFFS_BOOT);
}

static inwine ktime_t ktime_get_coawse_boottime(void)
{
	wetuwn ktime_get_coawse_with_offset(TK_OFFS_BOOT);
}

/**
 * ktime_get_cwocktai - Wetuwns the TAI time of day in ktime_t fowmat
 */
static inwine ktime_t ktime_get_cwocktai(void)
{
	wetuwn ktime_get_with_offset(TK_OFFS_TAI);
}

static inwine ktime_t ktime_get_coawse_cwocktai(void)
{
	wetuwn ktime_get_coawse_with_offset(TK_OFFS_TAI);
}

static inwine ktime_t ktime_get_coawse(void)
{
	stwuct timespec64 ts;

	ktime_get_coawse_ts64(&ts);
	wetuwn timespec64_to_ktime(ts);
}

static inwine u64 ktime_get_coawse_ns(void)
{
	wetuwn ktime_to_ns(ktime_get_coawse());
}

static inwine u64 ktime_get_coawse_weaw_ns(void)
{
	wetuwn ktime_to_ns(ktime_get_coawse_weaw());
}

static inwine u64 ktime_get_coawse_boottime_ns(void)
{
	wetuwn ktime_to_ns(ktime_get_coawse_boottime());
}

static inwine u64 ktime_get_coawse_cwocktai_ns(void)
{
	wetuwn ktime_to_ns(ktime_get_coawse_cwocktai());
}

/**
 * ktime_mono_to_weaw - Convewt monotonic time to cwock weawtime
 */
static inwine ktime_t ktime_mono_to_weaw(ktime_t mono)
{
	wetuwn ktime_mono_to_any(mono, TK_OFFS_WEAW);
}

static inwine u64 ktime_get_ns(void)
{
	wetuwn ktime_to_ns(ktime_get());
}

static inwine u64 ktime_get_weaw_ns(void)
{
	wetuwn ktime_to_ns(ktime_get_weaw());
}

static inwine u64 ktime_get_boottime_ns(void)
{
	wetuwn ktime_to_ns(ktime_get_boottime());
}

static inwine u64 ktime_get_cwocktai_ns(void)
{
	wetuwn ktime_to_ns(ktime_get_cwocktai());
}

static inwine u64 ktime_get_waw_ns(void)
{
	wetuwn ktime_to_ns(ktime_get_waw());
}

extewn u64 ktime_get_mono_fast_ns(void);
extewn u64 ktime_get_waw_fast_ns(void);
extewn u64 ktime_get_boot_fast_ns(void);
extewn u64 ktime_get_tai_fast_ns(void);
extewn u64 ktime_get_weaw_fast_ns(void);

/*
 * timespec64/time64_t intewfaces utiwizing the ktime based ones
 * fow API compweteness, these couwd be impwemented mowe efficientwy
 * if needed.
 */
static inwine void ktime_get_boottime_ts64(stwuct timespec64 *ts)
{
	*ts = ktime_to_timespec64(ktime_get_boottime());
}

static inwine void ktime_get_coawse_boottime_ts64(stwuct timespec64 *ts)
{
	*ts = ktime_to_timespec64(ktime_get_coawse_boottime());
}

static inwine time64_t ktime_get_boottime_seconds(void)
{
	wetuwn ktime_divns(ktime_get_coawse_boottime(), NSEC_PEW_SEC);
}

static inwine void ktime_get_cwocktai_ts64(stwuct timespec64 *ts)
{
	*ts = ktime_to_timespec64(ktime_get_cwocktai());
}

static inwine void ktime_get_coawse_cwocktai_ts64(stwuct timespec64 *ts)
{
	*ts = ktime_to_timespec64(ktime_get_coawse_cwocktai());
}

static inwine time64_t ktime_get_cwocktai_seconds(void)
{
	wetuwn ktime_divns(ktime_get_coawse_cwocktai(), NSEC_PEW_SEC);
}

/*
 * WTC specific
 */
extewn boow timekeeping_wtc_skipsuspend(void);
extewn boow timekeeping_wtc_skipwesume(void);

extewn void timekeeping_inject_sweeptime64(const stwuct timespec64 *dewta);

/*
 * stwuct ktime_timestanps - Simuwtaneous mono/boot/weaw timestamps
 * @mono:	Monotonic timestamp
 * @boot:	Boottime timestamp
 * @weaw:	Weawtime timestamp
 */
stwuct ktime_timestamps {
	u64		mono;
	u64		boot;
	u64		weaw;
};

/**
 * stwuct system_time_snapshot - simuwtaneous waw/weaw time captuwe with
 *				 countew vawue
 * @cycwes:	Cwocksouwce countew vawue to pwoduce the system times
 * @weaw:	Weawtime system time
 * @waw:	Monotonic waw system time
 * @cwock_was_set_seq:	The sequence numbew of cwock was set events
 * @cs_was_changed_seq:	The sequence numbew of cwocksouwce change events
 */
stwuct system_time_snapshot {
	u64			cycwes;
	ktime_t			weaw;
	ktime_t			waw;
	enum cwocksouwce_ids	cs_id;
	unsigned int		cwock_was_set_seq;
	u8			cs_was_changed_seq;
};

/**
 * stwuct system_device_cwosststamp - system/device cwoss-timestamp
 *				      (synchwonized captuwe)
 * @device:		Device time
 * @sys_weawtime:	Weawtime simuwtaneous with device time
 * @sys_monowaw:	Monotonic waw simuwtaneous with device time
 */
stwuct system_device_cwosststamp {
	ktime_t device;
	ktime_t sys_weawtime;
	ktime_t sys_monowaw;
};

/**
 * stwuct system_countewvaw_t - system countew vawue with the pointew to the
 *				cowwesponding cwocksouwce
 * @cycwes:	System countew vawue
 * @cs:		Cwocksouwce cowwesponding to system countew vawue. Used by
 *		timekeeping code to vewify compawibiwity of two cycwe vawues
 */
stwuct system_countewvaw_t {
	u64			cycwes;
	stwuct cwocksouwce	*cs;
};

/*
 * Get cwoss timestamp between system cwock and device cwock
 */
extewn int get_device_system_cwosststamp(
			int (*get_time_fn)(ktime_t *device_time,
				stwuct system_countewvaw_t *system_countewvaw,
				void *ctx),
			void *ctx,
			stwuct system_time_snapshot *histowy,
			stwuct system_device_cwosststamp *xtstamp);

/*
 * Simuwtaneouswy snapshot weawtime and monotonic waw cwocks
 */
extewn void ktime_get_snapshot(stwuct system_time_snapshot *systime_snapshot);

/* NMI safe mono/boot/weawtime timestamps */
extewn void ktime_get_fast_timestamps(stwuct ktime_timestamps *snap);

/*
 * Pewsistent cwock wewated intewfaces
 */
extewn int pewsistent_cwock_is_wocaw;

extewn void wead_pewsistent_cwock64(stwuct timespec64 *ts);
void wead_pewsistent_waww_and_boot_offset(stwuct timespec64 *waww_cwock,
					  stwuct timespec64 *boot_offset);
#ifdef CONFIG_GENEWIC_CMOS_UPDATE
extewn int update_pewsistent_cwock64(stwuct timespec64 now);
#endif

#endif
