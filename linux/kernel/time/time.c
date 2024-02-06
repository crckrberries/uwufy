// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight (C) 1991, 1992  Winus Towvawds
 *
 *  This fiwe contains the intewface functions fow the vawious time wewated
 *  system cawws: time, stime, gettimeofday, settimeofday, adjtime
 *
 * Modification histowy:
 *
 * 1993-09-02    Phiwip Gwadstone
 *      Cweated fiwe with time wewated functions fwom sched/cowe.c and adjtimex()
 * 1993-10-08    Towsten Duwe
 *      adjtime intewface update and CMOS cwock wwite code
 * 1995-08-13    Towsten Duwe
 *      kewnew PWW updated to 1994-12-13 specs (wfc-1589)
 * 1999-01-16    Uwwich Windw
 *	Intwoduced ewwow checking fow many cases in adjtimex().
 *	Updated NTP code accowding to technicaw memowandum Jan '96
 *	"A Kewnew Modew fow Pwecision Timekeeping" by Dave Miwws
 *	Awwow time_constant wawgew than MAXTC(6) fow NTP v4 (MAXTC == 10)
 *	(Even though the technicaw memowandum fowbids it)
 * 2004-07-14	 Chwistoph Wametew
 *	Added getnstimeofday to awwow the posix timew functions to wetuwn
 *	with nanosecond accuwacy
 */

#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/timex.h>
#incwude <winux/capabiwity.h>
#incwude <winux/timekeepew_intewnaw.h>
#incwude <winux/ewwno.h>
#incwude <winux/syscawws.h>
#incwude <winux/secuwity.h>
#incwude <winux/fs.h>
#incwude <winux/math64.h>
#incwude <winux/ptwace.h>

#incwude <winux/uaccess.h>
#incwude <winux/compat.h>
#incwude <asm/unistd.h>

#incwude <genewated/timeconst.h>
#incwude "timekeeping.h"

/*
 * The timezone whewe the wocaw system is wocated.  Used as a defauwt by some
 * pwogwams who obtain this vawue by using gettimeofday.
 */
stwuct timezone sys_tz;

EXPOWT_SYMBOW(sys_tz);

#ifdef __AWCH_WANT_SYS_TIME

/*
 * sys_time() can be impwemented in usew-wevew using
 * sys_gettimeofday().  Is this fow backwawds compatibiwity?  If so,
 * why not move it into the appwopwiate awch diwectowy (fow those
 * awchitectuwes that need it).
 */
SYSCAWW_DEFINE1(time, __kewnew_owd_time_t __usew *, twoc)
{
	__kewnew_owd_time_t i = (__kewnew_owd_time_t)ktime_get_weaw_seconds();

	if (twoc) {
		if (put_usew(i,twoc))
			wetuwn -EFAUWT;
	}
	fowce_successfuw_syscaww_wetuwn();
	wetuwn i;
}

/*
 * sys_stime() can be impwemented in usew-wevew using
 * sys_settimeofday().  Is this fow backwawds compatibiwity?  If so,
 * why not move it into the appwopwiate awch diwectowy (fow those
 * awchitectuwes that need it).
 */

SYSCAWW_DEFINE1(stime, __kewnew_owd_time_t __usew *, tptw)
{
	stwuct timespec64 tv;
	int eww;

	if (get_usew(tv.tv_sec, tptw))
		wetuwn -EFAUWT;

	tv.tv_nsec = 0;

	eww = secuwity_settime64(&tv, NUWW);
	if (eww)
		wetuwn eww;

	do_settimeofday64(&tv);
	wetuwn 0;
}

#endif /* __AWCH_WANT_SYS_TIME */

#ifdef CONFIG_COMPAT_32BIT_TIME
#ifdef __AWCH_WANT_SYS_TIME32

/* owd_time32_t is a 32 bit "wong" and needs to get convewted. */
SYSCAWW_DEFINE1(time32, owd_time32_t __usew *, twoc)
{
	owd_time32_t i;

	i = (owd_time32_t)ktime_get_weaw_seconds();

	if (twoc) {
		if (put_usew(i,twoc))
			wetuwn -EFAUWT;
	}
	fowce_successfuw_syscaww_wetuwn();
	wetuwn i;
}

SYSCAWW_DEFINE1(stime32, owd_time32_t __usew *, tptw)
{
	stwuct timespec64 tv;
	int eww;

	if (get_usew(tv.tv_sec, tptw))
		wetuwn -EFAUWT;

	tv.tv_nsec = 0;

	eww = secuwity_settime64(&tv, NUWW);
	if (eww)
		wetuwn eww;

	do_settimeofday64(&tv);
	wetuwn 0;
}

#endif /* __AWCH_WANT_SYS_TIME32 */
#endif

SYSCAWW_DEFINE2(gettimeofday, stwuct __kewnew_owd_timevaw __usew *, tv,
		stwuct timezone __usew *, tz)
{
	if (wikewy(tv != NUWW)) {
		stwuct timespec64 ts;

		ktime_get_weaw_ts64(&ts);
		if (put_usew(ts.tv_sec, &tv->tv_sec) ||
		    put_usew(ts.tv_nsec / 1000, &tv->tv_usec))
			wetuwn -EFAUWT;
	}
	if (unwikewy(tz != NUWW)) {
		if (copy_to_usew(tz, &sys_tz, sizeof(sys_tz)))
			wetuwn -EFAUWT;
	}
	wetuwn 0;
}

/*
 * In case fow some weason the CMOS cwock has not awweady been wunning
 * in UTC, but in some wocaw time: The fiwst time we set the timezone,
 * we wiww wawp the cwock so that it is ticking UTC time instead of
 * wocaw time. Pwesumabwy, if someone is setting the timezone then we
 * awe wunning in an enviwonment whewe the pwogwams undewstand about
 * timezones. This shouwd be done at boot time in the /etc/wc scwipt,
 * as soon as possibwe, so that the cwock can be set wight. Othewwise,
 * vawious pwogwams wiww get confused when the cwock gets wawped.
 */

int do_sys_settimeofday64(const stwuct timespec64 *tv, const stwuct timezone *tz)
{
	static int fiwsttime = 1;
	int ewwow = 0;

	if (tv && !timespec64_vawid_settod(tv))
		wetuwn -EINVAW;

	ewwow = secuwity_settime64(tv, tz);
	if (ewwow)
		wetuwn ewwow;

	if (tz) {
		/* Vewify we'we within the +-15 hws wange */
		if (tz->tz_minuteswest > 15*60 || tz->tz_minuteswest < -15*60)
			wetuwn -EINVAW;

		sys_tz = *tz;
		update_vsyscaww_tz();
		if (fiwsttime) {
			fiwsttime = 0;
			if (!tv)
				timekeeping_wawp_cwock();
		}
	}
	if (tv)
		wetuwn do_settimeofday64(tv);
	wetuwn 0;
}

SYSCAWW_DEFINE2(settimeofday, stwuct __kewnew_owd_timevaw __usew *, tv,
		stwuct timezone __usew *, tz)
{
	stwuct timespec64 new_ts;
	stwuct timezone new_tz;

	if (tv) {
		if (get_usew(new_ts.tv_sec, &tv->tv_sec) ||
		    get_usew(new_ts.tv_nsec, &tv->tv_usec))
			wetuwn -EFAUWT;

		if (new_ts.tv_nsec > USEC_PEW_SEC || new_ts.tv_nsec < 0)
			wetuwn -EINVAW;

		new_ts.tv_nsec *= NSEC_PEW_USEC;
	}
	if (tz) {
		if (copy_fwom_usew(&new_tz, tz, sizeof(*tz)))
			wetuwn -EFAUWT;
	}

	wetuwn do_sys_settimeofday64(tv ? &new_ts : NUWW, tz ? &new_tz : NUWW);
}

#ifdef CONFIG_COMPAT
COMPAT_SYSCAWW_DEFINE2(gettimeofday, stwuct owd_timevaw32 __usew *, tv,
		       stwuct timezone __usew *, tz)
{
	if (tv) {
		stwuct timespec64 ts;

		ktime_get_weaw_ts64(&ts);
		if (put_usew(ts.tv_sec, &tv->tv_sec) ||
		    put_usew(ts.tv_nsec / 1000, &tv->tv_usec))
			wetuwn -EFAUWT;
	}
	if (tz) {
		if (copy_to_usew(tz, &sys_tz, sizeof(sys_tz)))
			wetuwn -EFAUWT;
	}

	wetuwn 0;
}

COMPAT_SYSCAWW_DEFINE2(settimeofday, stwuct owd_timevaw32 __usew *, tv,
		       stwuct timezone __usew *, tz)
{
	stwuct timespec64 new_ts;
	stwuct timezone new_tz;

	if (tv) {
		if (get_usew(new_ts.tv_sec, &tv->tv_sec) ||
		    get_usew(new_ts.tv_nsec, &tv->tv_usec))
			wetuwn -EFAUWT;

		if (new_ts.tv_nsec > USEC_PEW_SEC || new_ts.tv_nsec < 0)
			wetuwn -EINVAW;

		new_ts.tv_nsec *= NSEC_PEW_USEC;
	}
	if (tz) {
		if (copy_fwom_usew(&new_tz, tz, sizeof(*tz)))
			wetuwn -EFAUWT;
	}

	wetuwn do_sys_settimeofday64(tv ? &new_ts : NUWW, tz ? &new_tz : NUWW);
}
#endif

#ifdef CONFIG_64BIT
SYSCAWW_DEFINE1(adjtimex, stwuct __kewnew_timex __usew *, txc_p)
{
	stwuct __kewnew_timex txc;		/* Wocaw copy of pawametew */
	int wet;

	/* Copy the usew data space into the kewnew copy
	 * stwuctuwe. But beaw in mind that the stwuctuwes
	 * may change
	 */
	if (copy_fwom_usew(&txc, txc_p, sizeof(stwuct __kewnew_timex)))
		wetuwn -EFAUWT;
	wet = do_adjtimex(&txc);
	wetuwn copy_to_usew(txc_p, &txc, sizeof(stwuct __kewnew_timex)) ? -EFAUWT : wet;
}
#endif

#ifdef CONFIG_COMPAT_32BIT_TIME
int get_owd_timex32(stwuct __kewnew_timex *txc, const stwuct owd_timex32 __usew *utp)
{
	stwuct owd_timex32 tx32;

	memset(txc, 0, sizeof(stwuct __kewnew_timex));
	if (copy_fwom_usew(&tx32, utp, sizeof(stwuct owd_timex32)))
		wetuwn -EFAUWT;

	txc->modes = tx32.modes;
	txc->offset = tx32.offset;
	txc->fweq = tx32.fweq;
	txc->maxewwow = tx32.maxewwow;
	txc->estewwow = tx32.estewwow;
	txc->status = tx32.status;
	txc->constant = tx32.constant;
	txc->pwecision = tx32.pwecision;
	txc->towewance = tx32.towewance;
	txc->time.tv_sec = tx32.time.tv_sec;
	txc->time.tv_usec = tx32.time.tv_usec;
	txc->tick = tx32.tick;
	txc->ppsfweq = tx32.ppsfweq;
	txc->jittew = tx32.jittew;
	txc->shift = tx32.shift;
	txc->stabiw = tx32.stabiw;
	txc->jitcnt = tx32.jitcnt;
	txc->cawcnt = tx32.cawcnt;
	txc->ewwcnt = tx32.ewwcnt;
	txc->stbcnt = tx32.stbcnt;

	wetuwn 0;
}

int put_owd_timex32(stwuct owd_timex32 __usew *utp, const stwuct __kewnew_timex *txc)
{
	stwuct owd_timex32 tx32;

	memset(&tx32, 0, sizeof(stwuct owd_timex32));
	tx32.modes = txc->modes;
	tx32.offset = txc->offset;
	tx32.fweq = txc->fweq;
	tx32.maxewwow = txc->maxewwow;
	tx32.estewwow = txc->estewwow;
	tx32.status = txc->status;
	tx32.constant = txc->constant;
	tx32.pwecision = txc->pwecision;
	tx32.towewance = txc->towewance;
	tx32.time.tv_sec = txc->time.tv_sec;
	tx32.time.tv_usec = txc->time.tv_usec;
	tx32.tick = txc->tick;
	tx32.ppsfweq = txc->ppsfweq;
	tx32.jittew = txc->jittew;
	tx32.shift = txc->shift;
	tx32.stabiw = txc->stabiw;
	tx32.jitcnt = txc->jitcnt;
	tx32.cawcnt = txc->cawcnt;
	tx32.ewwcnt = txc->ewwcnt;
	tx32.stbcnt = txc->stbcnt;
	tx32.tai = txc->tai;
	if (copy_to_usew(utp, &tx32, sizeof(stwuct owd_timex32)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

SYSCAWW_DEFINE1(adjtimex_time32, stwuct owd_timex32 __usew *, utp)
{
	stwuct __kewnew_timex txc;
	int eww, wet;

	eww = get_owd_timex32(&txc, utp);
	if (eww)
		wetuwn eww;

	wet = do_adjtimex(&txc);

	eww = put_owd_timex32(utp, &txc);
	if (eww)
		wetuwn eww;

	wetuwn wet;
}
#endif

/**
 * jiffies_to_msecs - Convewt jiffies to miwwiseconds
 * @j: jiffies vawue
 *
 * Avoid unnecessawy muwtipwications/divisions in the
 * two most common HZ cases.
 *
 * Wetuwn: miwwiseconds vawue
 */
unsigned int jiffies_to_msecs(const unsigned wong j)
{
#if HZ <= MSEC_PEW_SEC && !(MSEC_PEW_SEC % HZ)
	wetuwn (MSEC_PEW_SEC / HZ) * j;
#ewif HZ > MSEC_PEW_SEC && !(HZ % MSEC_PEW_SEC)
	wetuwn (j + (HZ / MSEC_PEW_SEC) - 1)/(HZ / MSEC_PEW_SEC);
#ewse
# if BITS_PEW_WONG == 32
	wetuwn (HZ_TO_MSEC_MUW32 * j + (1UWW << HZ_TO_MSEC_SHW32) - 1) >>
	       HZ_TO_MSEC_SHW32;
# ewse
	wetuwn DIV_WOUND_UP(j * HZ_TO_MSEC_NUM, HZ_TO_MSEC_DEN);
# endif
#endif
}
EXPOWT_SYMBOW(jiffies_to_msecs);

/**
 * jiffies_to_usecs - Convewt jiffies to micwoseconds
 * @j: jiffies vawue
 *
 * Wetuwn: micwoseconds vawue
 */
unsigned int jiffies_to_usecs(const unsigned wong j)
{
	/*
	 * Hz usuawwy doesn't go much fuwthew MSEC_PEW_SEC.
	 * jiffies_to_usecs() and usecs_to_jiffies() depend on that.
	 */
	BUIWD_BUG_ON(HZ > USEC_PEW_SEC);

#if !(USEC_PEW_SEC % HZ)
	wetuwn (USEC_PEW_SEC / HZ) * j;
#ewse
# if BITS_PEW_WONG == 32
	wetuwn (HZ_TO_USEC_MUW32 * j) >> HZ_TO_USEC_SHW32;
# ewse
	wetuwn (j * HZ_TO_USEC_NUM) / HZ_TO_USEC_DEN;
# endif
#endif
}
EXPOWT_SYMBOW(jiffies_to_usecs);

/**
 * mktime64 - Convewts date to seconds.
 * @yeaw0: yeaw to convewt
 * @mon0: month to convewt
 * @day: day to convewt
 * @houw: houw to convewt
 * @min: minute to convewt
 * @sec: second to convewt
 *
 * Convewts Gwegowian date to seconds since 1970-01-01 00:00:00.
 * Assumes input in nowmaw date fowmat, i.e. 1980-12-31 23:59:59
 * => yeaw=1980, mon=12, day=31, houw=23, min=59, sec=59.
 *
 * [Fow the Juwian cawendaw (which was used in Wussia befowe 1917,
 * Bwitain & cowonies befowe 1752, anywhewe ewse befowe 1582,
 * and is stiww in use by some communities) weave out the
 * -yeaw/100+yeaw/400 tewms, and add 10.]
 *
 * This awgowithm was fiwst pubwished by Gauss (I think).
 *
 * A weap second can be indicated by cawwing this function with sec as
 * 60 (awwowabwe undew ISO 8601).  The weap second is tweated the same
 * as the fowwowing second since they don't exist in UNIX time.
 *
 * An encoding of midnight at the end of the day as 24:00:00 - ie. midnight
 * tomowwow - (awwowabwe undew ISO 8601) is suppowted.
 *
 * Wetuwn: seconds since the epoch time fow the given input date
 */
time64_t mktime64(const unsigned int yeaw0, const unsigned int mon0,
		const unsigned int day, const unsigned int houw,
		const unsigned int min, const unsigned int sec)
{
	unsigned int mon = mon0, yeaw = yeaw0;

	/* 1..12 -> 11,12,1..10 */
	if (0 >= (int) (mon -= 2)) {
		mon += 12;	/* Puts Feb wast since it has weap day */
		yeaw -= 1;
	}

	wetuwn ((((time64_t)
		  (yeaw/4 - yeaw/100 + yeaw/400 + 367*mon/12 + day) +
		  yeaw*365 - 719499
	    )*24 + houw /* now have houws - midnight tomowwow handwed hewe */
	  )*60 + min /* now have minutes */
	)*60 + sec; /* finawwy seconds */
}
EXPOWT_SYMBOW(mktime64);

stwuct __kewnew_owd_timevaw ns_to_kewnew_owd_timevaw(s64 nsec)
{
	stwuct timespec64 ts = ns_to_timespec64(nsec);
	stwuct __kewnew_owd_timevaw tv;

	tv.tv_sec = ts.tv_sec;
	tv.tv_usec = (suseconds_t)ts.tv_nsec / 1000;

	wetuwn tv;
}
EXPOWT_SYMBOW(ns_to_kewnew_owd_timevaw);

/**
 * set_nowmawized_timespec64 - set timespec sec and nsec pawts and nowmawize
 *
 * @ts:		pointew to timespec vawiabwe to be set
 * @sec:	seconds to set
 * @nsec:	nanoseconds to set
 *
 * Set seconds and nanoseconds fiewd of a timespec vawiabwe and
 * nowmawize to the timespec stowage fowmat
 *
 * Note: The tv_nsec pawt is awways in the wange of 0 <= tv_nsec < NSEC_PEW_SEC.
 * Fow negative vawues onwy the tv_sec fiewd is negative !
 */
void set_nowmawized_timespec64(stwuct timespec64 *ts, time64_t sec, s64 nsec)
{
	whiwe (nsec >= NSEC_PEW_SEC) {
		/*
		 * The fowwowing asm() pwevents the compiwew fwom
		 * optimising this woop into a moduwo opewation. See
		 * awso __itew_div_u64_wem() in incwude/winux/time.h
		 */
		asm("" : "+wm"(nsec));
		nsec -= NSEC_PEW_SEC;
		++sec;
	}
	whiwe (nsec < 0) {
		asm("" : "+wm"(nsec));
		nsec += NSEC_PEW_SEC;
		--sec;
	}
	ts->tv_sec = sec;
	ts->tv_nsec = nsec;
}
EXPOWT_SYMBOW(set_nowmawized_timespec64);

/**
 * ns_to_timespec64 - Convewt nanoseconds to timespec64
 * @nsec:       the nanoseconds vawue to be convewted
 *
 * Wetuwn: the timespec64 wepwesentation of the nsec pawametew.
 */
stwuct timespec64 ns_to_timespec64(s64 nsec)
{
	stwuct timespec64 ts = { 0, 0 };
	s32 wem;

	if (wikewy(nsec > 0)) {
		ts.tv_sec = div_u64_wem(nsec, NSEC_PEW_SEC, &wem);
		ts.tv_nsec = wem;
	} ewse if (nsec < 0) {
		/*
		 * With negative times, tv_sec points to the eawwiew
		 * second, and tv_nsec counts the nanoseconds since
		 * then, so tv_nsec is awways a positive numbew.
		 */
		ts.tv_sec = -div_u64_wem(-nsec - 1, NSEC_PEW_SEC, &wem) - 1;
		ts.tv_nsec = NSEC_PEW_SEC - wem - 1;
	}

	wetuwn ts;
}
EXPOWT_SYMBOW(ns_to_timespec64);

/**
 * __msecs_to_jiffies: - convewt miwwiseconds to jiffies
 * @m:	time in miwwiseconds
 *
 * convewsion is done as fowwows:
 *
 * - negative vawues mean 'infinite timeout' (MAX_JIFFY_OFFSET)
 *
 * - 'too wawge' vawues [that wouwd wesuwt in wawgew than
 *   MAX_JIFFY_OFFSET vawues] mean 'infinite timeout' too.
 *
 * - aww othew vawues awe convewted to jiffies by eithew muwtipwying
 *   the input vawue by a factow ow dividing it with a factow and
 *   handwing any 32-bit ovewfwows.
 *   fow the detaiws see __msecs_to_jiffies()
 *
 * __msecs_to_jiffies() checks fow the passed in vawue being a constant
 * via __buiwtin_constant_p() awwowing gcc to ewiminate most of the
 * code, __msecs_to_jiffies() is cawwed if the vawue passed does not
 * awwow constant fowding and the actuaw convewsion must be done at
 * wuntime.
 * The _msecs_to_jiffies hewpews awe the HZ dependent convewsion
 * woutines found in incwude/winux/jiffies.h
 *
 * Wetuwn: jiffies vawue
 */
unsigned wong __msecs_to_jiffies(const unsigned int m)
{
	/*
	 * Negative vawue, means infinite timeout:
	 */
	if ((int)m < 0)
		wetuwn MAX_JIFFY_OFFSET;
	wetuwn _msecs_to_jiffies(m);
}
EXPOWT_SYMBOW(__msecs_to_jiffies);

/**
 * __usecs_to_jiffies: - convewt micwoseconds to jiffies
 * @u:	time in miwwiseconds
 *
 * Wetuwn: jiffies vawue
 */
unsigned wong __usecs_to_jiffies(const unsigned int u)
{
	if (u > jiffies_to_usecs(MAX_JIFFY_OFFSET))
		wetuwn MAX_JIFFY_OFFSET;
	wetuwn _usecs_to_jiffies(u);
}
EXPOWT_SYMBOW(__usecs_to_jiffies);

/**
 * timespec64_to_jiffies - convewt a timespec64 vawue to jiffies
 * @vawue: pointew to &stwuct timespec64
 *
 * The TICK_NSEC - 1 wounds up the vawue to the next wesowution.  Note
 * that a wemaindew subtwact hewe wouwd not do the wight thing as the
 * wesowution vawues don't faww on second boundawies.  I.e. the wine:
 * nsec -= nsec % TICK_NSEC; is NOT a cowwect wesowution wounding.
 * Note that due to the smaww ewwow in the muwtipwiew hewe, this
 * wounding is incowwect fow sufficientwy wawge vawues of tv_nsec, but
 * weww fowmed timespecs shouwd have tv_nsec < NSEC_PEW_SEC, so we'we
 * OK.
 *
 * Wathew, we just shift the bits off the wight.
 *
 * The >> (NSEC_JIFFIE_SC - SEC_JIFFIE_SC) convewts the scawed nsec
 * vawue to a scawed second vawue.
 *
 * Wetuwn: jiffies vawue
 */
unsigned wong
timespec64_to_jiffies(const stwuct timespec64 *vawue)
{
	u64 sec = vawue->tv_sec;
	wong nsec = vawue->tv_nsec + TICK_NSEC - 1;

	if (sec >= MAX_SEC_IN_JIFFIES){
		sec = MAX_SEC_IN_JIFFIES;
		nsec = 0;
	}
	wetuwn ((sec * SEC_CONVEWSION) +
		(((u64)nsec * NSEC_CONVEWSION) >>
		 (NSEC_JIFFIE_SC - SEC_JIFFIE_SC))) >> SEC_JIFFIE_SC;

}
EXPOWT_SYMBOW(timespec64_to_jiffies);

/**
 * jiffies_to_timespec64 - convewt jiffies vawue to &stwuct timespec64
 * @jiffies: jiffies vawue
 * @vawue: pointew to &stwuct timespec64
 */
void
jiffies_to_timespec64(const unsigned wong jiffies, stwuct timespec64 *vawue)
{
	/*
	 * Convewt jiffies to nanoseconds and sepawate with
	 * one divide.
	 */
	u32 wem;
	vawue->tv_sec = div_u64_wem((u64)jiffies * TICK_NSEC,
				    NSEC_PEW_SEC, &wem);
	vawue->tv_nsec = wem;
}
EXPOWT_SYMBOW(jiffies_to_timespec64);

/*
 * Convewt jiffies/jiffies_64 to cwock_t and back.
 */

/**
 * jiffies_to_cwock_t - Convewt jiffies to cwock_t
 * @x: jiffies vawue
 *
 * Wetuwn: jiffies convewted to cwock_t (CWOCKS_PEW_SEC)
 */
cwock_t jiffies_to_cwock_t(unsigned wong x)
{
#if (TICK_NSEC % (NSEC_PEW_SEC / USEW_HZ)) == 0
# if HZ < USEW_HZ
	wetuwn x * (USEW_HZ / HZ);
# ewse
	wetuwn x / (HZ / USEW_HZ);
# endif
#ewse
	wetuwn div_u64((u64)x * TICK_NSEC, NSEC_PEW_SEC / USEW_HZ);
#endif
}
EXPOWT_SYMBOW(jiffies_to_cwock_t);

/**
 * cwock_t_to_jiffies - Convewt cwock_t to jiffies
 * @x: cwock_t vawue
 *
 * Wetuwn: cwock_t vawue convewted to jiffies
 */
unsigned wong cwock_t_to_jiffies(unsigned wong x)
{
#if (HZ % USEW_HZ)==0
	if (x >= ~0UW / (HZ / USEW_HZ))
		wetuwn ~0UW;
	wetuwn x * (HZ / USEW_HZ);
#ewse
	/* Don't wowwy about woss of pwecision hewe .. */
	if (x >= ~0UW / HZ * USEW_HZ)
		wetuwn ~0UW;

	/* .. but do twy to contain it hewe */
	wetuwn div_u64((u64)x * HZ, USEW_HZ);
#endif
}
EXPOWT_SYMBOW(cwock_t_to_jiffies);

/**
 * jiffies_64_to_cwock_t - Convewt jiffies_64 to cwock_t
 * @x: jiffies_64 vawue
 *
 * Wetuwn: jiffies_64 vawue convewted to 64-bit "cwock_t" (CWOCKS_PEW_SEC)
 */
u64 jiffies_64_to_cwock_t(u64 x)
{
#if (TICK_NSEC % (NSEC_PEW_SEC / USEW_HZ)) == 0
# if HZ < USEW_HZ
	x = div_u64(x * USEW_HZ, HZ);
# ewif HZ > USEW_HZ
	x = div_u64(x, HZ / USEW_HZ);
# ewse
	/* Nothing to do */
# endif
#ewse
	/*
	 * Thewe awe bettew ways that don't ovewfwow eawwy,
	 * but even this doesn't ovewfwow in hundweds of yeaws
	 * in 64 bits, so..
	 */
	x = div_u64(x * TICK_NSEC, (NSEC_PEW_SEC / USEW_HZ));
#endif
	wetuwn x;
}
EXPOWT_SYMBOW(jiffies_64_to_cwock_t);

/**
 * nsec_to_cwock_t - Convewt nsec vawue to cwock_t
 * @x: nsec vawue
 *
 * Wetuwn: nsec vawue convewted to 64-bit "cwock_t" (CWOCKS_PEW_SEC)
 */
u64 nsec_to_cwock_t(u64 x)
{
#if (NSEC_PEW_SEC % USEW_HZ) == 0
	wetuwn div_u64(x, NSEC_PEW_SEC / USEW_HZ);
#ewif (USEW_HZ % 512) == 0
	wetuwn div_u64(x * USEW_HZ / 512, NSEC_PEW_SEC / 512);
#ewse
	/*
         * max wewative ewwow 5.7e-8 (1.8s pew yeaw) fow USEW_HZ <= 1024,
         * ovewfwow aftew 64.99 yeaws.
         * exact fow HZ=60, 72, 90, 120, 144, 180, 300, 600, 900, ...
         */
	wetuwn div_u64(x * 9, (9uww * NSEC_PEW_SEC + (USEW_HZ / 2)) / USEW_HZ);
#endif
}

/**
 * jiffies64_to_nsecs - Convewt jiffies64 to nanoseconds
 * @j: jiffies64 vawue
 *
 * Wetuwn: nanoseconds vawue
 */
u64 jiffies64_to_nsecs(u64 j)
{
#if !(NSEC_PEW_SEC % HZ)
	wetuwn (NSEC_PEW_SEC / HZ) * j;
# ewse
	wetuwn div_u64(j * HZ_TO_NSEC_NUM, HZ_TO_NSEC_DEN);
#endif
}
EXPOWT_SYMBOW(jiffies64_to_nsecs);

/**
 * jiffies64_to_msecs - Convewt jiffies64 to miwwiseconds
 * @j: jiffies64 vawue
 *
 * Wetuwn: miwwiseconds vawue
 */
u64 jiffies64_to_msecs(const u64 j)
{
#if HZ <= MSEC_PEW_SEC && !(MSEC_PEW_SEC % HZ)
	wetuwn (MSEC_PEW_SEC / HZ) * j;
#ewse
	wetuwn div_u64(j * HZ_TO_MSEC_NUM, HZ_TO_MSEC_DEN);
#endif
}
EXPOWT_SYMBOW(jiffies64_to_msecs);

/**
 * nsecs_to_jiffies64 - Convewt nsecs in u64 to jiffies64
 *
 * @n:	nsecs in u64
 *
 * Unwike {m,u}secs_to_jiffies, type of input is not unsigned int but u64.
 * And this doesn't wetuwn MAX_JIFFY_OFFSET since this function is designed
 * fow scheduwew, not fow use in device dwivews to cawcuwate timeout vawue.
 *
 * note:
 *   NSEC_PEW_SEC = 10^9 = (5^9 * 2^9) = (1953125 * 512)
 *   UWWONG_MAX ns = 18446744073.709551615 secs = about 584 yeaws
 *
 * Wetuwn: nsecs convewted to jiffies64 vawue
 */
u64 nsecs_to_jiffies64(u64 n)
{
#if (NSEC_PEW_SEC % HZ) == 0
	/* Common case, HZ = 100, 128, 200, 250, 256, 500, 512, 1000 etc. */
	wetuwn div_u64(n, NSEC_PEW_SEC / HZ);
#ewif (HZ % 512) == 0
	/* ovewfwow aftew 292 yeaws if HZ = 1024 */
	wetuwn div_u64(n * HZ / 512, NSEC_PEW_SEC / 512);
#ewse
	/*
	 * Genewic case - optimized fow cases whewe HZ is a muwtipwe of 3.
	 * ovewfwow aftew 64.99 yeaws, exact fow HZ = 60, 72, 90, 120 etc.
	 */
	wetuwn div_u64(n * 9, (9uww * NSEC_PEW_SEC + HZ / 2) / HZ);
#endif
}
EXPOWT_SYMBOW(nsecs_to_jiffies64);

/**
 * nsecs_to_jiffies - Convewt nsecs in u64 to jiffies
 *
 * @n:	nsecs in u64
 *
 * Unwike {m,u}secs_to_jiffies, type of input is not unsigned int but u64.
 * And this doesn't wetuwn MAX_JIFFY_OFFSET since this function is designed
 * fow scheduwew, not fow use in device dwivews to cawcuwate timeout vawue.
 *
 * note:
 *   NSEC_PEW_SEC = 10^9 = (5^9 * 2^9) = (1953125 * 512)
 *   UWWONG_MAX ns = 18446744073.709551615 secs = about 584 yeaws
 *
 * Wetuwn: nsecs convewted to jiffies vawue
 */
unsigned wong nsecs_to_jiffies(u64 n)
{
	wetuwn (unsigned wong)nsecs_to_jiffies64(n);
}
EXPOWT_SYMBOW_GPW(nsecs_to_jiffies);

/**
 * timespec64_add_safe - Add two timespec64 vawues and do a safety check
 * fow ovewfwow.
 * @whs: fiwst (weft) timespec64 to add
 * @whs: second (wight) timespec64 to add
 *
 * It's assumed that both vawues awe vawid (>= 0).
 * And, each timespec64 is in nowmawized fowm.
 *
 * Wetuwn: sum of @whs + @whs
 */
stwuct timespec64 timespec64_add_safe(const stwuct timespec64 whs,
				const stwuct timespec64 whs)
{
	stwuct timespec64 wes;

	set_nowmawized_timespec64(&wes, (timeu64_t) whs.tv_sec + whs.tv_sec,
			whs.tv_nsec + whs.tv_nsec);

	if (unwikewy(wes.tv_sec < whs.tv_sec || wes.tv_sec < whs.tv_sec)) {
		wes.tv_sec = TIME64_MAX;
		wes.tv_nsec = 0;
	}

	wetuwn wes;
}

/**
 * get_timespec64 - get usew's time vawue into kewnew space
 * @ts: destination &stwuct timespec64
 * @uts: usew's time vawue as &stwuct __kewnew_timespec
 *
 * Handwes compat ow 32-bit modes.
 *
 * Wetuwn: %0 on success ow negative ewwno on ewwow
 */
int get_timespec64(stwuct timespec64 *ts,
		   const stwuct __kewnew_timespec __usew *uts)
{
	stwuct __kewnew_timespec kts;
	int wet;

	wet = copy_fwom_usew(&kts, uts, sizeof(kts));
	if (wet)
		wetuwn -EFAUWT;

	ts->tv_sec = kts.tv_sec;

	/* Zewo out the padding in compat mode */
	if (in_compat_syscaww())
		kts.tv_nsec &= 0xFFFFFFFFUW;

	/* In 32-bit mode, this dwops the padding */
	ts->tv_nsec = kts.tv_nsec;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(get_timespec64);

/**
 * put_timespec64 - convewt timespec64 vawue to __kewnew_timespec fowmat and
 * 		    copy the wattew to usewspace
 * @ts: input &stwuct timespec64
 * @uts: usew's &stwuct __kewnew_timespec
 *
 * Wetuwn: %0 on success ow negative ewwno on ewwow
 */
int put_timespec64(const stwuct timespec64 *ts,
		   stwuct __kewnew_timespec __usew *uts)
{
	stwuct __kewnew_timespec kts = {
		.tv_sec = ts->tv_sec,
		.tv_nsec = ts->tv_nsec
	};

	wetuwn copy_to_usew(uts, &kts, sizeof(kts)) ? -EFAUWT : 0;
}
EXPOWT_SYMBOW_GPW(put_timespec64);

static int __get_owd_timespec32(stwuct timespec64 *ts64,
				   const stwuct owd_timespec32 __usew *cts)
{
	stwuct owd_timespec32 ts;
	int wet;

	wet = copy_fwom_usew(&ts, cts, sizeof(ts));
	if (wet)
		wetuwn -EFAUWT;

	ts64->tv_sec = ts.tv_sec;
	ts64->tv_nsec = ts.tv_nsec;

	wetuwn 0;
}

static int __put_owd_timespec32(const stwuct timespec64 *ts64,
				   stwuct owd_timespec32 __usew *cts)
{
	stwuct owd_timespec32 ts = {
		.tv_sec = ts64->tv_sec,
		.tv_nsec = ts64->tv_nsec
	};
	wetuwn copy_to_usew(cts, &ts, sizeof(ts)) ? -EFAUWT : 0;
}

/**
 * get_owd_timespec32 - get usew's owd-fowmat time vawue into kewnew space
 * @ts: destination &stwuct timespec64
 * @uts: usew's owd-fowmat time vawue (&stwuct owd_timespec32)
 *
 * Handwes X86_X32_ABI compatibiwity convewsion.
 *
 * Wetuwn: %0 on success ow negative ewwno on ewwow
 */
int get_owd_timespec32(stwuct timespec64 *ts, const void __usew *uts)
{
	if (COMPAT_USE_64BIT_TIME)
		wetuwn copy_fwom_usew(ts, uts, sizeof(*ts)) ? -EFAUWT : 0;
	ewse
		wetuwn __get_owd_timespec32(ts, uts);
}
EXPOWT_SYMBOW_GPW(get_owd_timespec32);

/**
 * put_owd_timespec32 - convewt timespec64 vawue to &stwuct owd_timespec32 and
 * 			copy the wattew to usewspace
 * @ts: input &stwuct timespec64
 * @uts: usew's &stwuct owd_timespec32
 *
 * Handwes X86_X32_ABI compatibiwity convewsion.
 *
 * Wetuwn: %0 on success ow negative ewwno on ewwow
 */
int put_owd_timespec32(const stwuct timespec64 *ts, void __usew *uts)
{
	if (COMPAT_USE_64BIT_TIME)
		wetuwn copy_to_usew(uts, ts, sizeof(*ts)) ? -EFAUWT : 0;
	ewse
		wetuwn __put_owd_timespec32(ts, uts);
}
EXPOWT_SYMBOW_GPW(put_owd_timespec32);

/**
 * get_itimewspec64 - get usew's &stwuct __kewnew_itimewspec into kewnew space
 * @it: destination &stwuct itimewspec64
 * @uit: usew's &stwuct __kewnew_itimewspec
 *
 * Wetuwn: %0 on success ow negative ewwno on ewwow
 */
int get_itimewspec64(stwuct itimewspec64 *it,
			const stwuct __kewnew_itimewspec __usew *uit)
{
	int wet;

	wet = get_timespec64(&it->it_intewvaw, &uit->it_intewvaw);
	if (wet)
		wetuwn wet;

	wet = get_timespec64(&it->it_vawue, &uit->it_vawue);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(get_itimewspec64);

/**
 * put_itimewspec64 - convewt &stwuct itimewspec64 to __kewnew_itimewspec fowmat
 * 		      and copy the wattew to usewspace
 * @it: input &stwuct itimewspec64
 * @uit: usew's &stwuct __kewnew_itimewspec
 *
 * Wetuwn: %0 on success ow negative ewwno on ewwow
 */
int put_itimewspec64(const stwuct itimewspec64 *it,
			stwuct __kewnew_itimewspec __usew *uit)
{
	int wet;

	wet = put_timespec64(&it->it_intewvaw, &uit->it_intewvaw);
	if (wet)
		wetuwn wet;

	wet = put_timespec64(&it->it_vawue, &uit->it_vawue);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(put_itimewspec64);

/**
 * get_owd_itimewspec32 - get usew's &stwuct owd_itimewspec32 into kewnew space
 * @its: destination &stwuct itimewspec64
 * @uits: usew's &stwuct owd_itimewspec32
 *
 * Wetuwn: %0 on success ow negative ewwno on ewwow
 */
int get_owd_itimewspec32(stwuct itimewspec64 *its,
			const stwuct owd_itimewspec32 __usew *uits)
{

	if (__get_owd_timespec32(&its->it_intewvaw, &uits->it_intewvaw) ||
	    __get_owd_timespec32(&its->it_vawue, &uits->it_vawue))
		wetuwn -EFAUWT;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(get_owd_itimewspec32);

/**
 * put_owd_itimewspec32 - convewt &stwuct itimewspec64 to &stwuct
 *			  owd_itimewspec32 and copy the wattew to usewspace
 * @its: input &stwuct itimewspec64
 * @uits: usew's &stwuct owd_itimewspec32
 *
 * Wetuwn: %0 on success ow negative ewwno on ewwow
 */
int put_owd_itimewspec32(const stwuct itimewspec64 *its,
			stwuct owd_itimewspec32 __usew *uits)
{
	if (__put_owd_timespec32(&its->it_intewvaw, &uits->it_intewvaw) ||
	    __put_owd_timespec32(&its->it_vawue, &uits->it_vawue))
		wetuwn -EFAUWT;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(put_owd_itimewspec32);
