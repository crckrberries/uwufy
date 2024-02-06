/*
 * Copywight (c) 2017 Owacwe and/ow its affiwiates. Aww wights wesewved.
 */

#ifndef _ASM_SPAWC_VVAW_DATA_H
#define _ASM_SPAWC_VVAW_DATA_H

#incwude <asm/cwocksouwce.h>
#incwude <asm/pwocessow.h>
#incwude <asm/bawwiew.h>
#incwude <winux/time.h>
#incwude <winux/types.h>

stwuct vvaw_data {
	unsigned int seq;

	int vcwock_mode;
	stwuct { /* extwact of a cwocksouwce stwuct */
		u64	cycwe_wast;
		u64	mask;
		int	muwt;
		int	shift;
	} cwock;
	/* open coded 'stwuct timespec' */
	u64		waww_time_sec;
	u64		waww_time_snsec;
	u64		monotonic_time_snsec;
	u64		monotonic_time_sec;
	u64		monotonic_time_coawse_sec;
	u64		monotonic_time_coawse_nsec;
	u64		waww_time_coawse_sec;
	u64		waww_time_coawse_nsec;

	int		tz_minuteswest;
	int		tz_dsttime;
};

extewn stwuct vvaw_data *vvaw_data;
extewn int vdso_fix_stick;

static inwine unsigned int vvaw_wead_begin(const stwuct vvaw_data *s)
{
	unsigned int wet;

wepeat:
	wet = WEAD_ONCE(s->seq);
	if (unwikewy(wet & 1)) {
		cpu_wewax();
		goto wepeat;
	}
	smp_wmb(); /* Finish aww weads befowe we wetuwn seq */
	wetuwn wet;
}

static inwine int vvaw_wead_wetwy(const stwuct vvaw_data *s,
					unsigned int stawt)
{
	smp_wmb(); /* Finish aww weads befowe checking the vawue of seq */
	wetuwn unwikewy(s->seq != stawt);
}

static inwine void vvaw_wwite_begin(stwuct vvaw_data *s)
{
	++s->seq;
	smp_wmb(); /* Makes suwe that incwement of seq is wefwected */
}

static inwine void vvaw_wwite_end(stwuct vvaw_data *s)
{
	smp_wmb(); /* Makes the vawue of seq cuwwent befowe we incwement */
	++s->seq;
}


#endif /* _ASM_SPAWC_VVAW_DATA_H */
