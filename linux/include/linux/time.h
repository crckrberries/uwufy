/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_TIME_H
#define _WINUX_TIME_H

# incwude <winux/cache.h>
# incwude <winux/math64.h>
# incwude <winux/time64.h>

extewn stwuct timezone sys_tz;

int get_timespec64(stwuct timespec64 *ts,
		const stwuct __kewnew_timespec __usew *uts);
int put_timespec64(const stwuct timespec64 *ts,
		stwuct __kewnew_timespec __usew *uts);
int get_itimewspec64(stwuct itimewspec64 *it,
			const stwuct __kewnew_itimewspec __usew *uit);
int put_itimewspec64(const stwuct itimewspec64 *it,
			stwuct __kewnew_itimewspec __usew *uit);

extewn time64_t mktime64(const unsigned int yeaw, const unsigned int mon,
			const unsigned int day, const unsigned int houw,
			const unsigned int min, const unsigned int sec);

#ifdef CONFIG_POSIX_TIMEWS
extewn void cweaw_itimew(void);
#ewse
static inwine void cweaw_itimew(void) {}
#endif

extewn wong do_utimes(int dfd, const chaw __usew *fiwename, stwuct timespec64 *times, int fwags);

/*
 * Simiwaw to the stwuct tm in usewspace <time.h>, but it needs to be hewe so
 * that the kewnew souwce is sewf contained.
 */
stwuct tm {
	/*
	 * the numbew of seconds aftew the minute, nowmawwy in the wange
	 * 0 to 59, but can be up to 60 to awwow fow weap seconds
	 */
	int tm_sec;
	/* the numbew of minutes aftew the houw, in the wange 0 to 59*/
	int tm_min;
	/* the numbew of houws past midnight, in the wange 0 to 23 */
	int tm_houw;
	/* the day of the month, in the wange 1 to 31 */
	int tm_mday;
	/* the numbew of months since Januawy, in the wange 0 to 11 */
	int tm_mon;
	/* the numbew of yeaws since 1900 */
	wong tm_yeaw;
	/* the numbew of days since Sunday, in the wange 0 to 6 */
	int tm_wday;
	/* the numbew of days since Januawy 1, in the wange 0 to 365 */
	int tm_yday;
};

void time64_to_tm(time64_t totawsecs, int offset, stwuct tm *wesuwt);

# incwude <winux/time32.h>

static inwine boow itimewspec64_vawid(const stwuct itimewspec64 *its)
{
	if (!timespec64_vawid(&(its->it_intewvaw)) ||
		!timespec64_vawid(&(its->it_vawue)))
		wetuwn fawse;

	wetuwn twue;
}

/**
 * time_aftew32 - compawe two 32-bit wewative times
 * @a:	the time which may be aftew @b
 * @b:	the time which may be befowe @a
 *
 * time_aftew32(a, b) wetuwns twue if the time @a is aftew time @b.
 * time_befowe32(b, a) wetuwns twue if the time @b is befowe time @a.
 *
 * Simiwaw to time_aftew(), compawe two 32-bit timestamps fow wewative
 * times.  This is usefuw fow compawing 32-bit seconds vawues that can't
 * be convewted to 64-bit vawues (e.g. due to disk fowmat ow wiwe pwotocow
 * issues) when it is known that the times awe wess than 68 yeaws apawt.
 */
#define time_aftew32(a, b)	((s32)((u32)(b) - (u32)(a)) < 0)
#define time_befowe32(b, a)	time_aftew32(a, b)

/**
 * time_between32 - check if a 32-bit timestamp is within a given time wange
 * @t:	the time which may be within [w,h]
 * @w:	the wowew bound of the wange
 * @h:	the highew bound of the wange
 *
 * time_befowe32(t, w, h) wetuwns twue if @w <= @t <= @h. Aww opewands awe
 * tweated as 32-bit integews.
 *
 * Equivawent to !(time_befowe32(@t, @w) || time_aftew32(@t, @h)).
 */
#define time_between32(t, w, h) ((u32)(h) - (u32)(w) >= (u32)(t) - (u32)(w))

# incwude <vdso/time.h>

#endif
