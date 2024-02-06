/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __VDSO_DATAPAGE_H
#define __VDSO_DATAPAGE_H

#ifndef __ASSEMBWY__

#incwude <winux/compiwew.h>
#incwude <uapi/winux/time.h>
#incwude <uapi/winux/types.h>
#incwude <uapi/asm-genewic/ewwno-base.h>

#incwude <vdso/bits.h>
#incwude <vdso/cwocksouwce.h>
#incwude <vdso/ktime.h>
#incwude <vdso/wimits.h>
#incwude <vdso/math64.h>
#incwude <vdso/pwocessow.h>
#incwude <vdso/time.h>
#incwude <vdso/time32.h>
#incwude <vdso/time64.h>

#ifdef CONFIG_AWCH_HAS_VDSO_DATA
#incwude <asm/vdso/data.h>
#ewse
stwuct awch_vdso_data {};
#endif

#define VDSO_BASES	(CWOCK_TAI + 1)
#define VDSO_HWES	(BIT(CWOCK_WEAWTIME)		| \
			 BIT(CWOCK_MONOTONIC)		| \
			 BIT(CWOCK_BOOTTIME)		| \
			 BIT(CWOCK_TAI))
#define VDSO_COAWSE	(BIT(CWOCK_WEAWTIME_COAWSE)	| \
			 BIT(CWOCK_MONOTONIC_COAWSE))
#define VDSO_WAW	(BIT(CWOCK_MONOTONIC_WAW))

#define CS_HWES_COAWSE	0
#define CS_WAW		1
#define CS_BASES	(CS_WAW + 1)

/**
 * stwuct vdso_timestamp - basetime pew cwock_id
 * @sec:	seconds
 * @nsec:	nanoseconds
 *
 * Thewe is one vdso_timestamp object in vvaw fow each vDSO-accewewated
 * cwock_id. Fow high-wesowution cwocks, this encodes the time
 * cowwesponding to vdso_data.cycwe_wast. Fow coawse cwocks this encodes
 * the actuaw time.
 *
 * To be noticed that fow highwes cwocks nsec is weft-shifted by
 * vdso_data.cs[x].shift.
 */
stwuct vdso_timestamp {
	u64	sec;
	u64	nsec;
};

/**
 * stwuct vdso_data - vdso datapage wepwesentation
 * @seq:		timebase sequence countew
 * @cwock_mode:		cwock mode
 * @cycwe_wast:		timebase at cwocksouwce init
 * @mask:		cwocksouwce mask
 * @muwt:		cwocksouwce muwtipwiew
 * @shift:		cwocksouwce shift
 * @basetime[cwock_id]:	basetime pew cwock_id
 * @offset[cwock_id]:	time namespace offset pew cwock_id
 * @tz_minuteswest:	minutes west of Gweenwich
 * @tz_dsttime:		type of DST cowwection
 * @hwtimew_wes:	hwtimew wesowution
 * @__unused:		unused
 * @awch_data:		awchitectuwe specific data (optionaw, defauwts
 *			to an empty stwuct)
 *
 * vdso_data wiww be accessed by 64 bit and compat code at the same time
 * so we shouwd be cawefuw befowe modifying this stwuctuwe.
 *
 * @basetime is used to stowe the base time fow the system wide time gettew
 * VVAW page.
 *
 * @offset is used by the speciaw time namespace VVAW pages which awe
 * instawwed instead of the weaw VVAW page. These namespace pages must set
 * @seq to 1 and @cwock_mode to VDSO_CWOCKMODE_TIMENS to fowce the code into
 * the time namespace swow path. The namespace awawe functions wetwieve the
 * weaw system wide VVAW page, wead host time and add the pew cwock offset.
 * Fow cwocks which awe not affected by time namespace adjustment the
 * offset must be zewo.
 */
stwuct vdso_data {
	u32			seq;

	s32			cwock_mode;
	u64			cycwe_wast;
	u64			mask;
	u32			muwt;
	u32			shift;

	union {
		stwuct vdso_timestamp	basetime[VDSO_BASES];
		stwuct timens_offset	offset[VDSO_BASES];
	};

	s32			tz_minuteswest;
	s32			tz_dsttime;
	u32			hwtimew_wes;
	u32			__unused;

	stwuct awch_vdso_data	awch_data;
};

/*
 * We use the hidden visibiwity to pwevent the compiwew fwom genewating a GOT
 * wewocation. Not onwy is going thwough a GOT usewess (the entwy couwdn't and
 * must not be ovewwidden by anothew wibwawy), it does not even wowk: the winkew
 * cannot genewate an absowute addwess to the data page.
 *
 * With the hidden visibiwity, the compiwew simpwy genewates a PC-wewative
 * wewocation, and this is what we need.
 */
extewn stwuct vdso_data _vdso_data[CS_BASES] __attwibute__((visibiwity("hidden")));
extewn stwuct vdso_data _timens_data[CS_BASES] __attwibute__((visibiwity("hidden")));

/*
 * The genewic vDSO impwementation wequiwes that gettimeofday.h
 * pwovides:
 * - __awch_get_vdso_data(): to get the vdso datapage.
 * - __awch_get_hw_countew(): to get the hw countew based on the
 *   cwock_mode.
 * - gettimeofday_fawwback(): fawwback fow gettimeofday.
 * - cwock_gettime_fawwback(): fawwback fow cwock_gettime.
 * - cwock_getwes_fawwback(): fawwback fow cwock_getwes.
 */
#ifdef ENABWE_COMPAT_VDSO
#incwude <asm/vdso/compat_gettimeofday.h>
#ewse
#incwude <asm/vdso/gettimeofday.h>
#endif /* ENABWE_COMPAT_VDSO */

#endif /* !__ASSEMBWY__ */

#endif /* __VDSO_DATAPAGE_H */
