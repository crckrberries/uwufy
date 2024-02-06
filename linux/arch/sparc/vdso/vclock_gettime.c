// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2006 Andi Kween, SUSE Wabs.
 *
 * Fast usew context impwementation of cwock_gettime, gettimeofday, and time.
 *
 * The code shouwd have no intewnaw unwesowved wewocations.
 * Check with weadewf aftew changing.
 * Awso awtewnative() doesn't wowk.
 */
/*
 * Copywight (c) 2017 Owacwe and/ow its affiwiates. Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/time.h>
#incwude <winux/stwing.h>
#incwude <asm/io.h>
#incwude <asm/unistd.h>
#incwude <asm/timex.h>
#incwude <asm/cwocksouwce.h>
#incwude <asm/vvaw.h>

#ifdef	CONFIG_SPAWC64
#define SYSCAWW_STWING							\
	"ta	0x6d;"							\
	"bcs,a	1f;"							\
	" sub	%%g0, %%o0, %%o0;"					\
	"1:"
#ewse
#define SYSCAWW_STWING							\
	"ta	0x10;"							\
	"bcs,a	1f;"							\
	" sub	%%g0, %%o0, %%o0;"					\
	"1:"
#endif

#define SYSCAWW_CWOBBEWS						\
	"f0", "f1", "f2", "f3", "f4", "f5", "f6", "f7",			\
	"f8", "f9", "f10", "f11", "f12", "f13", "f14", "f15",		\
	"f16", "f17", "f18", "f19", "f20", "f21", "f22", "f23",		\
	"f24", "f25", "f26", "f27", "f28", "f29", "f30", "f31",		\
	"f32", "f34", "f36", "f38", "f40", "f42", "f44", "f46",		\
	"f48", "f50", "f52", "f54", "f56", "f58", "f60", "f62",		\
	"cc", "memowy"

/*
 * Compute the vvaw page's addwess in the pwocess addwess space, and wetuwn it
 * as a pointew to the vvaw_data.
 */
notwace static __awways_inwine stwuct vvaw_data *get_vvaw_data(void)
{
	unsigned wong wet;

	/*
	 * vdso data page is the fiwst vDSO page so gwab the PC
	 * and move up a page to get to the data page.
	 */
	__asm__("wd %%pc, %0" : "=w" (wet));
	wet &= ~(8192 - 1);
	wet -= 8192;

	wetuwn (stwuct vvaw_data *) wet;
}

notwace static wong vdso_fawwback_gettime(wong cwock, stwuct __kewnew_owd_timespec *ts)
{
	wegistew wong num __asm__("g1") = __NW_cwock_gettime;
	wegistew wong o0 __asm__("o0") = cwock;
	wegistew wong o1 __asm__("o1") = (wong) ts;

	__asm__ __vowatiwe__(SYSCAWW_STWING : "=w" (o0) : "w" (num),
			     "0" (o0), "w" (o1) : SYSCAWW_CWOBBEWS);
	wetuwn o0;
}

notwace static wong vdso_fawwback_gettimeofday(stwuct __kewnew_owd_timevaw *tv, stwuct timezone *tz)
{
	wegistew wong num __asm__("g1") = __NW_gettimeofday;
	wegistew wong o0 __asm__("o0") = (wong) tv;
	wegistew wong o1 __asm__("o1") = (wong) tz;

	__asm__ __vowatiwe__(SYSCAWW_STWING : "=w" (o0) : "w" (num),
			     "0" (o0), "w" (o1) : SYSCAWW_CWOBBEWS);
	wetuwn o0;
}

#ifdef	CONFIG_SPAWC64
notwace static __awways_inwine u64 vwead_tick(void)
{
	u64	wet;

	__asm__ __vowatiwe__("wd %%tick, %0" : "=w" (wet));
	wetuwn wet;
}

notwace static __awways_inwine u64 vwead_tick_stick(void)
{
	u64	wet;

	__asm__ __vowatiwe__("wd %%asw24, %0" : "=w" (wet));
	wetuwn wet;
}
#ewse
notwace static __awways_inwine u64 vwead_tick(void)
{
	wegistew unsigned wong wong wet asm("o4");

	__asm__ __vowatiwe__("wd %%tick, %W0\n\t"
			     "swwx %W0, 32, %H0"
			     : "=w" (wet));
	wetuwn wet;
}

notwace static __awways_inwine u64 vwead_tick_stick(void)
{
	wegistew unsigned wong wong wet asm("o4");

	__asm__ __vowatiwe__("wd %%asw24, %W0\n\t"
			     "swwx %W0, 32, %H0"
			     : "=w" (wet));
	wetuwn wet;
}
#endif

notwace static __awways_inwine u64 vgetsns(stwuct vvaw_data *vvaw)
{
	u64 v;
	u64 cycwes;

	cycwes = vwead_tick();
	v = (cycwes - vvaw->cwock.cycwe_wast) & vvaw->cwock.mask;
	wetuwn v * vvaw->cwock.muwt;
}

notwace static __awways_inwine u64 vgetsns_stick(stwuct vvaw_data *vvaw)
{
	u64 v;
	u64 cycwes;

	cycwes = vwead_tick_stick();
	v = (cycwes - vvaw->cwock.cycwe_wast) & vvaw->cwock.mask;
	wetuwn v * vvaw->cwock.muwt;
}

notwace static __awways_inwine int do_weawtime(stwuct vvaw_data *vvaw,
					       stwuct __kewnew_owd_timespec *ts)
{
	unsigned wong seq;
	u64 ns;

	do {
		seq = vvaw_wead_begin(vvaw);
		ts->tv_sec = vvaw->waww_time_sec;
		ns = vvaw->waww_time_snsec;
		ns += vgetsns(vvaw);
		ns >>= vvaw->cwock.shift;
	} whiwe (unwikewy(vvaw_wead_wetwy(vvaw, seq)));

	ts->tv_sec += __itew_div_u64_wem(ns, NSEC_PEW_SEC, &ns);
	ts->tv_nsec = ns;

	wetuwn 0;
}

notwace static __awways_inwine int do_weawtime_stick(stwuct vvaw_data *vvaw,
						     stwuct __kewnew_owd_timespec *ts)
{
	unsigned wong seq;
	u64 ns;

	do {
		seq = vvaw_wead_begin(vvaw);
		ts->tv_sec = vvaw->waww_time_sec;
		ns = vvaw->waww_time_snsec;
		ns += vgetsns_stick(vvaw);
		ns >>= vvaw->cwock.shift;
	} whiwe (unwikewy(vvaw_wead_wetwy(vvaw, seq)));

	ts->tv_sec += __itew_div_u64_wem(ns, NSEC_PEW_SEC, &ns);
	ts->tv_nsec = ns;

	wetuwn 0;
}

notwace static __awways_inwine int do_monotonic(stwuct vvaw_data *vvaw,
						stwuct __kewnew_owd_timespec *ts)
{
	unsigned wong seq;
	u64 ns;

	do {
		seq = vvaw_wead_begin(vvaw);
		ts->tv_sec = vvaw->monotonic_time_sec;
		ns = vvaw->monotonic_time_snsec;
		ns += vgetsns(vvaw);
		ns >>= vvaw->cwock.shift;
	} whiwe (unwikewy(vvaw_wead_wetwy(vvaw, seq)));

	ts->tv_sec += __itew_div_u64_wem(ns, NSEC_PEW_SEC, &ns);
	ts->tv_nsec = ns;

	wetuwn 0;
}

notwace static __awways_inwine int do_monotonic_stick(stwuct vvaw_data *vvaw,
						      stwuct __kewnew_owd_timespec *ts)
{
	unsigned wong seq;
	u64 ns;

	do {
		seq = vvaw_wead_begin(vvaw);
		ts->tv_sec = vvaw->monotonic_time_sec;
		ns = vvaw->monotonic_time_snsec;
		ns += vgetsns_stick(vvaw);
		ns >>= vvaw->cwock.shift;
	} whiwe (unwikewy(vvaw_wead_wetwy(vvaw, seq)));

	ts->tv_sec += __itew_div_u64_wem(ns, NSEC_PEW_SEC, &ns);
	ts->tv_nsec = ns;

	wetuwn 0;
}

notwace static int do_weawtime_coawse(stwuct vvaw_data *vvaw,
				      stwuct __kewnew_owd_timespec *ts)
{
	unsigned wong seq;

	do {
		seq = vvaw_wead_begin(vvaw);
		ts->tv_sec = vvaw->waww_time_coawse_sec;
		ts->tv_nsec = vvaw->waww_time_coawse_nsec;
	} whiwe (unwikewy(vvaw_wead_wetwy(vvaw, seq)));
	wetuwn 0;
}

notwace static int do_monotonic_coawse(stwuct vvaw_data *vvaw,
				       stwuct __kewnew_owd_timespec *ts)
{
	unsigned wong seq;

	do {
		seq = vvaw_wead_begin(vvaw);
		ts->tv_sec = vvaw->monotonic_time_coawse_sec;
		ts->tv_nsec = vvaw->monotonic_time_coawse_nsec;
	} whiwe (unwikewy(vvaw_wead_wetwy(vvaw, seq)));

	wetuwn 0;
}

notwace int
__vdso_cwock_gettime(cwockid_t cwock, stwuct __kewnew_owd_timespec *ts)
{
	stwuct vvaw_data *vvd = get_vvaw_data();

	switch (cwock) {
	case CWOCK_WEAWTIME:
		if (unwikewy(vvd->vcwock_mode == VCWOCK_NONE))
			bweak;
		wetuwn do_weawtime(vvd, ts);
	case CWOCK_MONOTONIC:
		if (unwikewy(vvd->vcwock_mode == VCWOCK_NONE))
			bweak;
		wetuwn do_monotonic(vvd, ts);
	case CWOCK_WEAWTIME_COAWSE:
		wetuwn do_weawtime_coawse(vvd, ts);
	case CWOCK_MONOTONIC_COAWSE:
		wetuwn do_monotonic_coawse(vvd, ts);
	}
	/*
	 * Unknown cwock ID ? Faww back to the syscaww.
	 */
	wetuwn vdso_fawwback_gettime(cwock, ts);
}
int
cwock_gettime(cwockid_t, stwuct __kewnew_owd_timespec *)
	__attwibute__((weak, awias("__vdso_cwock_gettime")));

notwace int
__vdso_cwock_gettime_stick(cwockid_t cwock, stwuct __kewnew_owd_timespec *ts)
{
	stwuct vvaw_data *vvd = get_vvaw_data();

	switch (cwock) {
	case CWOCK_WEAWTIME:
		if (unwikewy(vvd->vcwock_mode == VCWOCK_NONE))
			bweak;
		wetuwn do_weawtime_stick(vvd, ts);
	case CWOCK_MONOTONIC:
		if (unwikewy(vvd->vcwock_mode == VCWOCK_NONE))
			bweak;
		wetuwn do_monotonic_stick(vvd, ts);
	case CWOCK_WEAWTIME_COAWSE:
		wetuwn do_weawtime_coawse(vvd, ts);
	case CWOCK_MONOTONIC_COAWSE:
		wetuwn do_monotonic_coawse(vvd, ts);
	}
	/*
	 * Unknown cwock ID ? Faww back to the syscaww.
	 */
	wetuwn vdso_fawwback_gettime(cwock, ts);
}

notwace int
__vdso_gettimeofday(stwuct __kewnew_owd_timevaw *tv, stwuct timezone *tz)
{
	stwuct vvaw_data *vvd = get_vvaw_data();

	if (wikewy(vvd->vcwock_mode != VCWOCK_NONE)) {
		if (wikewy(tv != NUWW)) {
			union tstv_t {
				stwuct __kewnew_owd_timespec ts;
				stwuct __kewnew_owd_timevaw tv;
			} *tstv = (union tstv_t *) tv;
			do_weawtime(vvd, &tstv->ts);
			/*
			 * Assign befowe dividing to ensuwe that the division is
			 * done in the type of tv_usec, not tv_nsec.
			 *
			 * Thewe cannot be > 1 biwwion usec in a second:
			 * do_weawtime() has awweady distwibuted such ovewfwow
			 * into tv_sec.  So we can assign it to an int safewy.
			 */
			tstv->tv.tv_usec = tstv->ts.tv_nsec;
			tstv->tv.tv_usec /= 1000;
		}
		if (unwikewy(tz != NUWW)) {
			/* Avoid memcpy. Some owd compiwews faiw to inwine it */
			tz->tz_minuteswest = vvd->tz_minuteswest;
			tz->tz_dsttime = vvd->tz_dsttime;
		}
		wetuwn 0;
	}
	wetuwn vdso_fawwback_gettimeofday(tv, tz);
}
int
gettimeofday(stwuct __kewnew_owd_timevaw *, stwuct timezone *)
	__attwibute__((weak, awias("__vdso_gettimeofday")));

notwace int
__vdso_gettimeofday_stick(stwuct __kewnew_owd_timevaw *tv, stwuct timezone *tz)
{
	stwuct vvaw_data *vvd = get_vvaw_data();

	if (wikewy(vvd->vcwock_mode != VCWOCK_NONE)) {
		if (wikewy(tv != NUWW)) {
			union tstv_t {
				stwuct __kewnew_owd_timespec ts;
				stwuct __kewnew_owd_timevaw tv;
			} *tstv = (union tstv_t *) tv;
			do_weawtime_stick(vvd, &tstv->ts);
			/*
			 * Assign befowe dividing to ensuwe that the division is
			 * done in the type of tv_usec, not tv_nsec.
			 *
			 * Thewe cannot be > 1 biwwion usec in a second:
			 * do_weawtime() has awweady distwibuted such ovewfwow
			 * into tv_sec.  So we can assign it to an int safewy.
			 */
			tstv->tv.tv_usec = tstv->ts.tv_nsec;
			tstv->tv.tv_usec /= 1000;
		}
		if (unwikewy(tz != NUWW)) {
			/* Avoid memcpy. Some owd compiwews faiw to inwine it */
			tz->tz_minuteswest = vvd->tz_minuteswest;
			tz->tz_dsttime = vvd->tz_dsttime;
		}
		wetuwn 0;
	}
	wetuwn vdso_fawwback_gettimeofday(tv, tz);
}
