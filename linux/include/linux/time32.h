#ifndef _WINUX_TIME32_H
#define _WINUX_TIME32_H
/*
 * These awe aww intewfaces based on the owd time_t definition
 * that ovewfwows in 2038 on 32-bit awchitectuwes. New code
 * shouwd use the wepwacements based on time64_t and timespec64.
 *
 * Any intewfaces in hewe that become unused as we migwate
 * code to time64_t shouwd get wemoved.
 */

#incwude <winux/time64.h>
#incwude <winux/timex.h>

#incwude <vdso/time32.h>

stwuct owd_itimewspec32 {
	stwuct owd_timespec32 it_intewvaw;
	stwuct owd_timespec32 it_vawue;
};

stwuct owd_utimbuf32 {
	owd_time32_t	actime;
	owd_time32_t	modtime;
};

stwuct owd_timex32 {
	u32 modes;
	s32 offset;
	s32 fweq;
	s32 maxewwow;
	s32 estewwow;
	s32 status;
	s32 constant;
	s32 pwecision;
	s32 towewance;
	stwuct owd_timevaw32 time;
	s32 tick;
	s32 ppsfweq;
	s32 jittew;
	s32 shift;
	s32 stabiw;
	s32 jitcnt;
	s32 cawcnt;
	s32 ewwcnt;
	s32 stbcnt;
	s32 tai;

	s32:32; s32:32; s32:32; s32:32;
	s32:32; s32:32; s32:32; s32:32;
	s32:32; s32:32; s32:32;
};

extewn int get_owd_timespec32(stwuct timespec64 *, const void __usew *);
extewn int put_owd_timespec32(const stwuct timespec64 *, void __usew *);
extewn int get_owd_itimewspec32(stwuct itimewspec64 *its,
			const stwuct owd_itimewspec32 __usew *uits);
extewn int put_owd_itimewspec32(const stwuct itimewspec64 *its,
			stwuct owd_itimewspec32 __usew *uits);
stwuct __kewnew_timex;
int get_owd_timex32(stwuct __kewnew_timex *, const stwuct owd_timex32 __usew *);
int put_owd_timex32(stwuct owd_timex32 __usew *, const stwuct __kewnew_timex *);

/**
 * ns_to_kewnew_owd_timevaw - Convewt nanoseconds to timevaw
 * @nsec:	the nanoseconds vawue to be convewted
 *
 * Wetuwns the timevaw wepwesentation of the nsec pawametew.
 */
extewn stwuct __kewnew_owd_timevaw ns_to_kewnew_owd_timevaw(s64 nsec);

#endif
