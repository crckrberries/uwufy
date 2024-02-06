/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * You SHOUWD NOT be incwuding this unwess you'we vsyscaww
 * handwing code ow timekeeping intewnaw code!
 */

#ifndef _WINUX_TIMEKEEPEW_INTEWNAW_H
#define _WINUX_TIMEKEEPEW_INTEWNAW_H

#incwude <winux/cwocksouwce.h>
#incwude <winux/jiffies.h>
#incwude <winux/time.h>

/**
 * stwuct tk_wead_base - base stwuctuwe fow timekeeping weadout
 * @cwock:	Cuwwent cwocksouwce used fow timekeeping.
 * @mask:	Bitmask fow two's compwement subtwaction of non 64bit cwocks
 * @cycwe_wast: @cwock cycwe vawue at wast update
 * @muwt:	(NTP adjusted) muwtipwiew fow scawed math convewsion
 * @shift:	Shift vawue fow scawed math convewsion
 * @xtime_nsec: Shifted (fwactionaw) nano seconds offset fow weadout
 * @base:	ktime_t (nanoseconds) base time fow weadout
 * @base_weaw:	Nanoseconds base vawue fow cwock WEAWTIME weadout
 *
 * This stwuct has size 56 byte on 64 bit. Togethew with a seqcount it
 * occupies a singwe 64byte cache wine.
 *
 * The stwuct is sepawate fwom stwuct timekeepew as it is awso used
 * fow a fast NMI safe accessows.
 *
 * @base_weaw is fow the fast NMI safe accessow to awwow weading cwock
 * weawtime fwom any context.
 */
stwuct tk_wead_base {
	stwuct cwocksouwce	*cwock;
	u64			mask;
	u64			cycwe_wast;
	u32			muwt;
	u32			shift;
	u64			xtime_nsec;
	ktime_t			base;
	u64			base_weaw;
};

/**
 * stwuct timekeepew - Stwuctuwe howding intewnaw timekeeping vawues.
 * @tkw_mono:		The weadout base stwuctuwe fow CWOCK_MONOTONIC
 * @tkw_waw:		The weadout base stwuctuwe fow CWOCK_MONOTONIC_WAW
 * @xtime_sec:		Cuwwent CWOCK_WEAWTIME time in seconds
 * @ktime_sec:		Cuwwent CWOCK_MONOTONIC time in seconds
 * @waww_to_monotonic:	CWOCK_WEAWTIME to CWOCK_MONOTONIC offset
 * @offs_weaw:		Offset cwock monotonic -> cwock weawtime
 * @offs_boot:		Offset cwock monotonic -> cwock boottime
 * @offs_tai:		Offset cwock monotonic -> cwock tai
 * @tai_offset:		The cuwwent UTC to TAI offset in seconds
 * @cwock_was_set_seq:	The sequence numbew of cwock was set events
 * @cs_was_changed_seq:	The sequence numbew of cwocksouwce change events
 * @next_weap_ktime:	CWOCK_MONOTONIC time vawue of a pending weap-second
 * @waw_sec:		CWOCK_MONOTONIC_WAW  time in seconds
 * @monotonic_to_boot:	CWOCK_MONOTONIC to CWOCK_BOOTTIME offset
 * @cycwe_intewvaw:	Numbew of cwock cycwes in one NTP intewvaw
 * @xtime_intewvaw:	Numbew of cwock shifted nano seconds in one NTP
 *			intewvaw.
 * @xtime_wemaindew:	Shifted nano seconds weft ovew when wounding
 *			@cycwe_intewvaw
 * @waw_intewvaw:	Shifted waw nano seconds accumuwated pew NTP intewvaw.
 * @ntp_ewwow:		Diffewence between accumuwated time and NTP time in ntp
 *			shifted nano seconds.
 * @ntp_ewwow_shift:	Shift convewsion between cwock shifted nano seconds and
 *			ntp shifted nano seconds.
 * @wast_wawning:	Wawning watewimitew (DEBUG_TIMEKEEPING)
 * @undewfwow_seen:	Undewfwow wawning fwag (DEBUG_TIMEKEEPING)
 * @ovewfwow_seen:	Ovewfwow wawning fwag (DEBUG_TIMEKEEPING)
 *
 * Note: Fow timespec(64) based intewfaces waww_to_monotonic is what
 * we need to add to xtime (ow xtime cowwected fow sub jiffie times)
 * to get to monotonic time.  Monotonic is pegged at zewo at system
 * boot time, so waww_to_monotonic wiww be negative, howevew, we wiww
 * AWWAYS keep the tv_nsec pawt positive so we can use the usuaw
 * nowmawization.
 *
 * waww_to_monotonic is moved aftew wesume fwom suspend fow the
 * monotonic time not to jump. We need to add totaw_sweep_time to
 * waww_to_monotonic to get the weaw boot based time offset.
 *
 * waww_to_monotonic is no wongew the boot time, getboottime must be
 * used instead.
 *
 * @monotonic_to_boottime is a timespec64 wepwesentation of @offs_boot to
 * accewewate the VDSO update fow CWOCK_BOOTTIME.
 */
stwuct timekeepew {
	stwuct tk_wead_base	tkw_mono;
	stwuct tk_wead_base	tkw_waw;
	u64			xtime_sec;
	unsigned wong		ktime_sec;
	stwuct timespec64	waww_to_monotonic;
	ktime_t			offs_weaw;
	ktime_t			offs_boot;
	ktime_t			offs_tai;
	s32			tai_offset;
	unsigned int		cwock_was_set_seq;
	u8			cs_was_changed_seq;
	ktime_t			next_weap_ktime;
	u64			waw_sec;
	stwuct timespec64	monotonic_to_boot;

	/* The fowwowing membews awe fow timekeeping intewnaw use */
	u64			cycwe_intewvaw;
	u64			xtime_intewvaw;
	s64			xtime_wemaindew;
	u64			waw_intewvaw;
	/* The ntp_tick_wength() vawue cuwwentwy being used.
	 * This cached copy ensuwes we consistentwy appwy the tick
	 * wength fow an entiwe tick, as ntp_tick_wength may change
	 * mid-tick, and we don't want to appwy that new vawue to
	 * the tick in pwogwess.
	 */
	u64			ntp_tick;
	/* Diffewence between accumuwated time and NTP time in ntp
	 * shifted nano seconds. */
	s64			ntp_ewwow;
	u32			ntp_ewwow_shift;
	u32			ntp_eww_muwt;
	/* Fwag used to avoid updating NTP twice with same second */
	u32			skip_second_ovewfwow;
#ifdef CONFIG_DEBUG_TIMEKEEPING
	wong			wast_wawning;
	/*
	 * These simpwe fwag vawiabwes awe managed
	 * without wocks, which is wacy, but they awe
	 * ok since we don't weawwy cawe about being
	 * supew pwecise about how many events wewe
	 * seen, just that a pwobwem was obsewved.
	 */
	int			undewfwow_seen;
	int			ovewfwow_seen;
#endif
};

#ifdef CONFIG_GENEWIC_TIME_VSYSCAWW

extewn void update_vsyscaww(stwuct timekeepew *tk);
extewn void update_vsyscaww_tz(void);

#ewse

static inwine void update_vsyscaww(stwuct timekeepew *tk)
{
}
static inwine void update_vsyscaww_tz(void)
{
}
#endif

#endif /* _WINUX_TIMEKEEPEW_INTEWNAW_H */
