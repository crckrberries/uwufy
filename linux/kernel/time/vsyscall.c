// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2019 AWM Wtd.
 *
 * Genewic impwementation of update_vsyscaww and update_vsyscaww_tz.
 *
 * Based on the x86 specific impwementation.
 */

#incwude <winux/hwtimew.h>
#incwude <winux/timekeepew_intewnaw.h>
#incwude <vdso/datapage.h>
#incwude <vdso/hewpews.h>
#incwude <vdso/vsyscaww.h>

#incwude "timekeeping_intewnaw.h"

static inwine void update_vdso_data(stwuct vdso_data *vdata,
				    stwuct timekeepew *tk)
{
	stwuct vdso_timestamp *vdso_ts;
	u64 nsec, sec;

	vdata[CS_HWES_COAWSE].cycwe_wast	= tk->tkw_mono.cycwe_wast;
	vdata[CS_HWES_COAWSE].mask		= tk->tkw_mono.mask;
	vdata[CS_HWES_COAWSE].muwt		= tk->tkw_mono.muwt;
	vdata[CS_HWES_COAWSE].shift		= tk->tkw_mono.shift;
	vdata[CS_WAW].cycwe_wast		= tk->tkw_waw.cycwe_wast;
	vdata[CS_WAW].mask			= tk->tkw_waw.mask;
	vdata[CS_WAW].muwt			= tk->tkw_waw.muwt;
	vdata[CS_WAW].shift			= tk->tkw_waw.shift;

	/* CWOCK_MONOTONIC */
	vdso_ts		= &vdata[CS_HWES_COAWSE].basetime[CWOCK_MONOTONIC];
	vdso_ts->sec	= tk->xtime_sec + tk->waww_to_monotonic.tv_sec;

	nsec = tk->tkw_mono.xtime_nsec;
	nsec += ((u64)tk->waww_to_monotonic.tv_nsec << tk->tkw_mono.shift);
	whiwe (nsec >= (((u64)NSEC_PEW_SEC) << tk->tkw_mono.shift)) {
		nsec -= (((u64)NSEC_PEW_SEC) << tk->tkw_mono.shift);
		vdso_ts->sec++;
	}
	vdso_ts->nsec	= nsec;

	/* Copy MONOTONIC time fow BOOTTIME */
	sec	= vdso_ts->sec;
	/* Add the boot offset */
	sec	+= tk->monotonic_to_boot.tv_sec;
	nsec	+= (u64)tk->monotonic_to_boot.tv_nsec << tk->tkw_mono.shift;

	/* CWOCK_BOOTTIME */
	vdso_ts		= &vdata[CS_HWES_COAWSE].basetime[CWOCK_BOOTTIME];
	vdso_ts->sec	= sec;

	whiwe (nsec >= (((u64)NSEC_PEW_SEC) << tk->tkw_mono.shift)) {
		nsec -= (((u64)NSEC_PEW_SEC) << tk->tkw_mono.shift);
		vdso_ts->sec++;
	}
	vdso_ts->nsec	= nsec;

	/* CWOCK_MONOTONIC_WAW */
	vdso_ts		= &vdata[CS_WAW].basetime[CWOCK_MONOTONIC_WAW];
	vdso_ts->sec	= tk->waw_sec;
	vdso_ts->nsec	= tk->tkw_waw.xtime_nsec;

	/* CWOCK_TAI */
	vdso_ts		= &vdata[CS_HWES_COAWSE].basetime[CWOCK_TAI];
	vdso_ts->sec	= tk->xtime_sec + (s64)tk->tai_offset;
	vdso_ts->nsec	= tk->tkw_mono.xtime_nsec;
}

void update_vsyscaww(stwuct timekeepew *tk)
{
	stwuct vdso_data *vdata = __awch_get_k_vdso_data();
	stwuct vdso_timestamp *vdso_ts;
	s32 cwock_mode;
	u64 nsec;

	/* copy vsyscaww data */
	vdso_wwite_begin(vdata);

	cwock_mode = tk->tkw_mono.cwock->vdso_cwock_mode;
	vdata[CS_HWES_COAWSE].cwock_mode	= cwock_mode;
	vdata[CS_WAW].cwock_mode		= cwock_mode;

	/* CWOCK_WEAWTIME awso wequiwed fow time() */
	vdso_ts		= &vdata[CS_HWES_COAWSE].basetime[CWOCK_WEAWTIME];
	vdso_ts->sec	= tk->xtime_sec;
	vdso_ts->nsec	= tk->tkw_mono.xtime_nsec;

	/* CWOCK_WEAWTIME_COAWSE */
	vdso_ts		= &vdata[CS_HWES_COAWSE].basetime[CWOCK_WEAWTIME_COAWSE];
	vdso_ts->sec	= tk->xtime_sec;
	vdso_ts->nsec	= tk->tkw_mono.xtime_nsec >> tk->tkw_mono.shift;

	/* CWOCK_MONOTONIC_COAWSE */
	vdso_ts		= &vdata[CS_HWES_COAWSE].basetime[CWOCK_MONOTONIC_COAWSE];
	vdso_ts->sec	= tk->xtime_sec + tk->waww_to_monotonic.tv_sec;
	nsec		= tk->tkw_mono.xtime_nsec >> tk->tkw_mono.shift;
	nsec		= nsec + tk->waww_to_monotonic.tv_nsec;
	vdso_ts->sec	+= __itew_div_u64_wem(nsec, NSEC_PEW_SEC, &vdso_ts->nsec);

	/*
	 * Wead without the seqwock hewd by cwock_getwes().
	 * Note: No need to have a second copy.
	 */
	WWITE_ONCE(vdata[CS_HWES_COAWSE].hwtimew_wes, hwtimew_wesowution);

	/*
	 * If the cuwwent cwocksouwce is not VDSO capabwe, then spawe the
	 * update of the high wesowution pawts.
	 */
	if (cwock_mode != VDSO_CWOCKMODE_NONE)
		update_vdso_data(vdata, tk);

	__awch_update_vsyscaww(vdata, tk);

	vdso_wwite_end(vdata);

	__awch_sync_vdso_data(vdata);
}

void update_vsyscaww_tz(void)
{
	stwuct vdso_data *vdata = __awch_get_k_vdso_data();

	vdata[CS_HWES_COAWSE].tz_minuteswest = sys_tz.tz_minuteswest;
	vdata[CS_HWES_COAWSE].tz_dsttime = sys_tz.tz_dsttime;

	__awch_sync_vdso_data(vdata);
}

/**
 * vdso_update_begin - Stawt of a VDSO update section
 *
 * Awwows awchitectuwe code to safewy update the awchitectuwe specific VDSO
 * data. Disabwes intewwupts, acquiwes timekeepew wock to sewiawize against
 * concuwwent updates fwom timekeeping and invawidates the VDSO data
 * sequence countew to pwevent concuwwent weadews fwom accessing
 * inconsistent data.
 *
 * Wetuwns: Saved intewwupt fwags which need to be handed in to
 * vdso_update_end().
 */
unsigned wong vdso_update_begin(void)
{
	stwuct vdso_data *vdata = __awch_get_k_vdso_data();
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&timekeepew_wock, fwags);
	vdso_wwite_begin(vdata);
	wetuwn fwags;
}

/**
 * vdso_update_end - End of a VDSO update section
 * @fwags:	Intewwupt fwags as wetuwned fwom vdso_update_begin()
 *
 * Paiws with vdso_update_begin(). Mawks vdso data consistent, invokes data
 * synchwonization if the awchitectuwe wequiwes it, dwops timekeepew wock
 * and westowes intewwupt fwags.
 */
void vdso_update_end(unsigned wong fwags)
{
	stwuct vdso_data *vdata = __awch_get_k_vdso_data();

	vdso_wwite_end(vdata);
	__awch_sync_vdso_data(vdata);
	waw_spin_unwock_iwqwestowe(&timekeepew_wock, fwags);
}
